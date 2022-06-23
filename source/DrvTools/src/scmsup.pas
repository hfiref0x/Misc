{*******************************************************************************
*
*  (C) COPYRIGHT AUTHORS, 2006 - 2021
*
*  TITLE:       scmsup.pas
*
*  VERSION:     5.51
*
*  DATE:        17 May 2021
*
*  SCM support routines for drivers load/unload.
*  ObjFPC variant
*
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
* TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
*******************************************************************************}
unit scmsup;

{$mode objfpc}{$H+}

interface

uses
  Windows, jwawinsvc, Classes, SysUtils;

function scmOpenManager(DesiredAccess: DWORD; var schSCManager: THANDLE;
  var lpStatus: DWORD): boolean;

function scmCloseManager(var schSCManager: THANDLE; var lpStatus: DWORD): boolean;

function scmInstallDriver(SchSCManager: SC_HANDLE; Name: LPCTSTR;
  DisplayName: LPCTSTR; StartType: DWORD; ErrorControl: DWORD;
  DriverBinary: LPCTSTR; var lpStatus: DWORD): boolean;

function scmRemoveDriver(SchSCManager: SC_HANDLE; DriverName: LPCTSTR;
  var lpStatus: DWORD): boolean;

function scmStartDriver(SchSCManager: SC_HANDLE; DriverName: LPCTSTR;
  var lpStatus: DWORD): boolean;

function scmStopDriver(SchSCManager: SC_HANDLE; DriverName: LPCTSTR;
  var lpStatus: DWORD): boolean;

implementation

{*
* scmOpenManager
*
* Purpose:
*
* Open handle for local SCM database.
*
*}
function scmOpenManager(DesiredAccess: DWORD; var schSCManager: THANDLE;
  var lpStatus: DWORD): boolean;
begin
  schSCManager := OpenSCManager(nil, nil, DesiredAccess);
  lpStatus := GetLastError();
  Result := (lpStatus = ERROR_SUCCESS);
end;

{*
* scmCloseManager
*
* Purpose:
*
* Close handle for local SCM database.
*
*}
function scmCloseManager(var schSCManager: THANDLE; var lpStatus: DWORD): boolean;
begin
  if (schSCManager <> 0) then
  begin
    if (CloseServiceHandle(schSCManager)) then
      schSCManager := 0;
    lpStatus := GetLastError();
  end
  else
  begin
    lpStatus := ERROR_INVALID_PARAMETER;
  end;
  Result := (lpStatus = ERROR_SUCCESS);
end;

{*
* scmInstallDriver
*
* Purpose:
*
* Create SCM service entry describing kernel driver.
*
*}
function scmInstallDriver(SchSCManager: SC_HANDLE; Name: LPCTSTR;
  DisplayName: LPCTSTR; StartType: DWORD; ErrorControl: DWORD;
  DriverBinary: LPCTSTR; var lpStatus: DWORD): boolean;
var
  schService: SC_HANDLE;
begin

  schService := CreateService(SchSCManager, // SCManager database
    Name, // name of service
    DisplayName, // name to display
    SERVICE_ALL_ACCESS, // desired access
    SERVICE_KERNEL_DRIVER, // service type
    StartType, // start type
    ErrorControl, // error control type
    DriverBinary, // service's binary
    nil, // no load ordering group
    nil, // no tag identifier
    nil, // no dependencies
    nil, // LocalSystem account
    nil // no password
    );

  lpStatus := GetLastError();

  if (schService <> 0) then
    CloseServiceHandle(schService);

  Result := (lpStatus = ERROR_SUCCESS);
end;

{*
* scmStartDriver
*
* Purpose:
*
* Start service, resulting in SCM drvier load.
*
*}
function scmStartDriver(SchSCManager: SC_HANDLE; DriverName: LPCTSTR;
  var lpStatus: DWORD): boolean;
var
  bResult: boolean;
  schService: SC_HANDLE;
begin
  schService := OpenService(SchSCManager, DriverName, SERVICE_ALL_ACCESS);

  lpStatus := GetLastError();

  if (schService <> 0) then
  begin
    bResult := StartService(schService, 0, nil);
    lpStatus := GetLastError();
    if (lpStatus = ERROR_SERVICE_ALREADY_RUNNING) then
    begin
      bResult := True;
      lpStatus := ERROR_SUCCESS;
    end;
    CloseServiceHandle(schService);
  end;

  Result := (bResult <> False);
end;

{*
* scmStopDriver
*
* Purpose:
*
* Command SCM to stop service, resulting in driver unload.
*
*}
function scmStopDriver(SchSCManager: SC_HANDLE; DriverName: LPCTSTR;
  var lpStatus: DWORD): boolean;
var
  bResult: boolean;
  schService: SC_HANDLE;
  iRetryCount: integer;
  serviceStatus: SERVICE_STATUS;
begin
  schService := OpenService(SchSCManager, DriverName, SERVICE_ALL_ACCESS);

  lpStatus := GetLastError();

  if (schService <> 0) then
  begin
    for iRetryCount := 5 downto 0 do
    begin

      SetLastError(ERROR_SUCCESS);

      ZeroMemory(@serviceStatus, sizeof(serviceStatus));

      bResult := ControlService(schService, SERVICE_CONTROL_STOP, serviceStatus);

      lpStatus := GetLastError();

      if (bResult <> False) then
        break;
      if (lpStatus <> ERROR_DEPENDENT_SERVICES_RUNNING) then
        break;

      Sleep(1000);

    end;
    CloseServiceHandle(schService);
  end;

  Result := (bResult <> False);
end;

{*
* scmRemoveDriver
*
* Purpose:
*
* Remove service entry from SCM database.
*
*}
function scmRemoveDriver(SchSCManager: SC_HANDLE; DriverName: LPCTSTR;
  var lpStatus: DWORD): boolean;
var
  bResult: boolean;
  schService: SC_HANDLE;
begin
  schService := OpenService(SchSCManager, DriverName, SERVICE_ALL_ACCESS);

  lpStatus := GetLastError();

  if (schService <> 0) then
  begin
    bResult := DeleteService(schService);
    lpStatus := GetLastError();
    CloseServiceHandle(schService);
  end;

  Result := (bResult <> False);
end;

{*
* scmUnloadDeviceDriver
*
* Purpose:
*
* Combines scmStopDriver and scmRemoveDriver.
*
*}
function scmUnloadDeviceDriver(DriverName: LPCTSTR; var lpStatus: DWORD): boolean;
var
  schSCManager: SC_HANDLE;
begin
  Result := False;
  lpStatus := ERROR_SUCCESS;

  if (DriverName <> nil) then
  begin
    schSCManager := OpenSCManager(nil, nil, SC_MANAGER_ALL_ACCESS);
    if (schSCManager <> 0) then
    begin
      scmStopDriver(schSCManager, DriverName, lpStatus);
      Result := scmRemoveDriver(schSCManager, DriverName, lpStatus);
      CloseServiceHandle(schSCManager);
    end;
  end
  else
  begin
    lpStatus := ERROR_INVALID_PARAMETER;
  end;

end;

{*
* scmOpenDevice
*
* Purpose:
*
* Open driver device by symbolic link.
*
*}
function scmOpenDevice(DriverName: LPCTSTR; var lpDeviceHandle: THANDLE;
  var lpStatus: DWORD): boolean;
var
  DeviceName: string;
begin
  if (DriverName <> nil) then
  begin
    try
      DeviceName := Format('\\.\%s:', [DriverName]);
    except
      Result := False;
      lpStatus := ERROR_INTERNAL_ERROR;
      exit;
    end;
    lpDeviceHandle := CreateFile(PChar(DeviceName), GENERIC_READ or
      GENERIC_WRITE, 0, nil, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    Result := (lpDeviceHandle <> INVALID_HANDLE_VALUE);
  end
  else
  begin
    Result := False;
    lpStatus := ERROR_INVALID_PARAMETER;
  end;
end;

{*
* scmLoadDeviceDriver
*
* Purpose:
*
* Unload if already exists, Create, Load and Open driver instance.
*
*}
function scmLoadDeviceDriver(DriverName: LPCTSTR; DisplayName: LPCTSTR;
  DriverPath: LPCTSTR; StartType: DWORD; ErrorControlType: DWORD;
  ForceReload: boolean; var lpDeviceHandle: THANDLE; var lpStatus: DWORD): boolean;
var
  schSCManager: SC_HANDLE;
begin
  Result := False;
  lpStatus := ERROR_INVALID_PARAMETER;
  lpDeviceHandle := 0;

  if (DriverName = nil) then
    exit;

  schSCManager := OpenSCManager(nil, nil, SC_MANAGER_ALL_ACCESS);
  if (schSCManager <> 0) then
  begin
    if (ForceReload) then
      scmRemoveDriver(schSCManager, DriverName, lpStatus);

    if (scmInstallDriver(schSCManager, DriverName, DisplayName,
      StartType, ErrorControlType, DriverPath, lpStatus)) then
    begin
      if (scmStartDriver(schSCManager, DriverName, lpStatus)) then
      begin
        Result := scmOpenDevice(DriverName, lpDeviceHandle, lpStatus);

      end;
    end;

    CloseServiceHandle(schSCManager);

  end
  else
  begin
    lpStatus := GetLastError();
  end;
end;


end.

