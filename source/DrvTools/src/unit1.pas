{*******************************************************************************
*
*  (C) COPYRIGHT AUTHORS, 2021 - 2023
*
*  TITLE:       Unit1.pas
*
*  VERSION:     1.00
*
*  DATE:        13 Mar 2023
*
*  MainForm implementation.
*
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
* TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
*******************************************************************************}
unit Unit1;

{$mode objfpc}{$H+}
{ignore nonmeaningful warnings}
{$WARN 5024 off : Parameter "$1" not used}
{$WARN 4055 off : Conversion between ordinals and pointers is not portable}
interface

uses
  Windows, ShellApi, Classes, SysUtils, Forms, Controls, Graphics,
  Dialogs, StdCtrls, ComCtrls,
  ExtCtrls, Spin, Buttons, Menus, LazFileUtils, scmsup, nativesup, Types;

type

  TChangeWindowMessageFilter = function(msg: cardinal; Action: Dword): BOOL; stdcall;

  { TMainForm }

  TMainForm = class(TForm)
    BitBtn1: TBitBtn;
    ButtonCallDriver: TButton;
    ButtonInBufferBrowse: TButton;
    ButtonIoctlReset: TButton;
    ButtonNativeUnload: TButton;
    ButtonOutBufferBrowse: TButton;
    ButtonScmRemove: TButton;
    ButtonNativeRemove: TButton;
    ButtonNativeInstall: TButton;
    ButtonNativeOpenFile: TButton;
    ButtonNativeLoad: TButton;
    ButtonScmUnload: TButton;
    ButtonScmLoad: TButton;
    ButtonScmInstall: TButton;
    ButtonScmOpenFile: TButton;
    CheckBoxFillByte: TCheckBox;
    CheckBoxForceLoad: TCheckBox;
    CheckBoxOutBuffer: TCheckBox;
    CheckBoxSymLink: TCheckBox;
    CheckBoxUseFiles: TCheckBox;
    EditDeviceName: TComboBox;
    ComboBoxIoAccess: TComboBox;
    ComboBoxIoMethod: TComboBox;
    ComboBoxScmErrorControl: TComboBox;
    ComboBoxNativeErrorControl: TComboBox;
    ComboBoxScmStartType: TComboBox;
    ComboBoxNativeStartType: TComboBox;
    EditDevType: TEdit;
    EditFunctionId: TEdit;
    EditInBufferName: TEdit;
    EditIoctlFill: TEdit;
    EditIoctlValue: TEdit;
    EditNativeSymLink: TEdit;
    EditOutBufferName: TEdit;
    EditScmDisplayName: TEdit;
    EditNativeDisplayName: TEdit;
    EditNativeFileName: TEdit;
    EditScmName: TEdit;
    EditScmFileName: TEdit;
    EditNativeName: TEdit;
    GroupBox1: TGroupBox;
    GroupBox2: TGroupBox;
    GroupBox3: TGroupBox;
    GroupBox4: TGroupBox;
    GroupBox5: TGroupBox;
    GroupBox7: TGroupBox;
    GroupBox9: TGroupBox;
    Image1: TImage;
    Label1: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    Label13: TLabel;
    Label14: TLabel;
    Label15: TLabel;
    MenuItem1: TMenuItem;
    PopupMenu1: TPopupMenu;
    VersionLabel: TLabel;
    Label17: TLabel;
    Label18: TLabel;
    Label19: TLabel;
    Label2: TLabel;
    Label20: TLabel;
    Label21: TLabel;
    Label22: TLabel;
    Label23: TLabel;
    Label24: TLabel;
    Label25: TLabel;
    Label26: TLabel;
    CompilerLabel: TLabel;
    Label28: TLabel;
    BuildDateLabel: TLabel;
    Label30: TLabel;
    OSNameLabel: TLabel;
    LabelPrivInfo: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    LabelPrivInfoScm: TLabel;
    ListViewPrivSet: TListView;
    MemoLog: TMemo;
    OpenDialog1: TOpenDialog;
    PageControl1: TPageControl;
    PageControl2: TPageControl;
    PageControl3: TPageControl;
    SaveDialog1: TSaveDialog;
    ScmTabSheet: TTabSheet;
    NativeTabSheet: TTabSheet;
    IoctlSheet: TTabSheet;
    OptionsSheet: TTabSheet;
    SpinEditInputBuffer: TSpinEdit;
    SpinEditOutputBuffer: TSpinEdit;
    StatusBar1: TStatusBar;
    TabSheet1: TTabSheet;
    TabSheet2: TTabSheet;
    AboutSheet: TTabSheet;
    procedure AboutSheetShow(Sender: TObject);
    procedure ButtonCallDriverClick(Sender: TObject);
    procedure ButtonInBufferBrowseClick(Sender: TObject);
    procedure ButtonIoctlResetClick(Sender: TObject);
    procedure ButtonNativeInstallClick(Sender: TObject);
    procedure ButtonNativeLoadClick(Sender: TObject);
    procedure ButtonNativeRemoveClick(Sender: TObject);
    procedure ButtonNativeUnloadClick(Sender: TObject);
    procedure ButtonScmInstallClick(Sender: TObject);
    procedure CheckBoxOutBufferChange(Sender: TObject);
    procedure CheckBoxSymLinkClick(Sender: TObject);
    procedure CheckBoxUseFilesChange(Sender: TObject);
    procedure EditDevTypeKeyUp(Sender: TObject; var Key: word; Shift: TShiftState);
    procedure EditIoCtlCodeKeyPress(Sender: TObject; var Key: char);
    procedure EditIoctlValueChange(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormDropFiles(Sender: TObject; const FileNames: array of string);
    procedure Image1Click(Sender: TObject);
    procedure IoctlSheetShow(Sender: TObject);
    procedure ListViewPrivSetMouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: integer);
    procedure MenuItem1Click(Sender: TObject);
    procedure NativeTabSheetHide(Sender: TObject);
    procedure NativeTabSheetShow(Sender: TObject);
    procedure OptionsSheetShow(Sender: TObject);
    procedure ScmTabSheetShow(Sender: TObject);
    procedure ShowStatus(Status: DWORD);
    procedure ShowStatus(Status: NTSTATUS); overload;
    procedure PrintToLog(LogEntry: string);
    procedure ManageInstalledDriverSCM(Sender: TObject);
    procedure ButtonOpenFileClick(Sender: TObject);
    procedure SpinEditInputBufferChange(Sender: TObject);
    procedure BuildIoCtl(Sender: TObject);
    procedure ElevateButtonClick(Sender: TObject);
  private

  public
    IsFullAdmin: boolean;
  end;

const
  BCM_SETSHIELD = $160C;

const
  PROGRAM_VERSION_MAJOR = 1;
  PROGRAM_VERSION_MINOR = 0;
  PROGRAM_VERSION_BUILD = 2303;
  PROGRAM_COMPILER = 'Lazarus FPC v';

var
  MainForm: TMainForm;
  g_DataBuffer: PChar = nil;
  g_DataSize: DWORD = 0;

implementation

const
  RTL_16MEG: DWORD = (1024 * 1024) * 16;
  DefaultExt: string = '.*.sys';
  DefaultDialogFilter: string = 'All files (*.*)|*.*';
  DrvLoadDialogFilter: string = 'Drivers (*.sys)|*.sys|All files (*.*)|*.*';

{$R *.lfm}
function RunAsAdmin(const ParentWindow: HWND; const FileName: string;
  const Parameters: string): boolean;
var
  sei: TShellExecuteInfoW;
begin

  ZeroMemory(@sei, SizeOf(sei));

  with sei do
  begin
    cbSize := SizeOf(sei);
    Wnd := ParentWindow;
    fMask := SEE_MASK_FLAG_DDEWAIT or SEE_MASK_FLAG_NO_UI;
    lpVerb := 'runas';
    lpFile := PWideChar(WideString(Filename));
    if Parameters <> '' then
      lpParameters := PWideChar(WideString(Parameters));
    nShow := SW_SHOWNORMAL;
  end;

  Result := ShellExecuteExW(@sei);
end;

function IsCurrentUserFullAdmin(): boolean;
const
  NtAuthority: TSidIdentifierAuthority = (Value: (0, 0, 0, 0, 0, 5));
var
  adminSid: Pointer;
  tokenHandle: THandle;
  i: integer;
  ptkGroups: PTokenGroups;
  dwLength, dwAttributes: DWORD;
begin

  Result := False;
  tokenHandle := 0;
  adminSid := nil;
  dwLength := 0;
  ptkGroups := nil;

  try

    if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, tokenHandle)) then
    begin

      Win32Check(AllocateAndInitializeSid(NtAuthority, 2,
        SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0,
        0, 0, 0, 0, adminSid));

      if (GetTokenInformation(tokenHandle, TokenGroups, nil, 0, @dwLength)) or
        (GetLastError <> ERROR_INSUFFICIENT_BUFFER) then
        RaiseLastOsError();

      ptkGroups := PTokenGroups(AllocMem(dwLength));

      Win32Check(GetTokenInformation(tokenHandle, TokenGroups,
        ptkGroups, dwLength, @dwLength));

      {$r-}//range check off for anysize array
      for i := 0 to ptkGroups^.GroupCount - 1 do
      begin
        if (EqualSid(adminSid, ptkGroups^.Groups[i].Sid)) then
        begin

          dwAttributes := ptkGroups^.Groups[i].Attributes;
          if ((dwAttributes and SE_GROUP_ENABLED) = SE_GROUP_ENABLED) then
            if ((dwAttributes and SE_GROUP_USE_FOR_DENY_ONLY) <>
              SE_GROUP_USE_FOR_DENY_ONLY) then
            begin
              Result := True;
              break;
            end;

        end;
      end;
      {$r+}
    end;

  finally
    if (tokenHandle <> 0) then
      CloseHandle(tokenHandle);
    if (adminSid <> nil) then
      FreeSid(adminSid);
    if (ptkGroups <> nil) then
      FreeMem(ptkGroups);
  end;

end;

function ReadInputBuffer(FileName: string; var Buffer: PChar;
  var BufferSize: DWORD): boolean;
var
  fileHandle: THandle;
  bytesIO: DWORD;
begin
  Result := False;

  fileHandle := CreateFileW(PWideChar(WideString(FileName)), GENERIC_READ,
    FILE_SHARE_READ, nil, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

  if (fileHandle <> INVALID_HANDLE_VALUE) then
  begin

    BufferSize := GetFileSize(fileHandle, nil);

    if (BufferSize > 0) and (BufferSize < RTL_16MEG) then
    begin
      Buffer := PChar(HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, BufferSize));
      if (Buffer <> nil) then
      begin
        bytesIO := 0;
        if (_ReadFile(fileHandle, Buffer, BufferSize, @bytesIO, nil)) then
        begin
          Result := (bytesIO = BufferSize);
        end;
      end;
    end
    else
    begin
      if (BufferSize = 0) then
        SetLastError(ERROR_INSUFFICIENT_BUFFER)
      else
      if (BufferSize >= RTL_16MEG) then
        SetLastError(ERROR_BUFFER_OVERFLOW);
    end;

    CloseHandle(fileHandle);

  end;
end;

function WriteOutputBuffer(FileName: string; lpBuffer: PChar;
  BufferSize: DWORD): boolean;
var
  fileHandle: THandle;
  bytesIO: DWORD;
begin
  Result := False;

  fileHandle := CreateFileW(PWideChar(WideString(FileName)), GENERIC_WRITE,
    0, nil, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

  if (fileHandle <> INVALID_HANDLE_VALUE) then
  begin
    bytesIO := 0;
    if (_WriteFile(fileHandle, lpBuffer, BufferSize, @bytesIO, nil)) then
      Result := (bytesIO = BufferSize);

    CloseHandle(fileHandle);
  end;
end;

function IoctlToCode(DeviceType, FunctionCode, Method, Access: longword): longword;
begin
  Result := (DeviceType shl 16) or (Access shl 14) or (FunctionCode shl 2) or Method;
end;

function HexToDword(S: string): longword;
var
  HexStr: string;
begin
  if Pos('$', S) = 0 then
    HexStr := '$' + S
  else
    HexStr := S;

  Result := StrToDword(HexStr);
end;

{ TMainForm }
procedure TMainForm.ElevateButtonClick(Sender: TObject);
begin
  RunAsAdmin(GetParent(MainForm.Handle), Application.ExeName,
    IntToStr(PageControl1.ActivePageIndex));
  MainForm.Close();
end;

function ObjectEnumProc(Entry: POBJECT_DIRECTORY_INFORMATION;
  Context: PEnumObjectsContext): BOOL; stdcall;
var
  pusTypeName: PUNICODE_STRING;
begin
  pusTypeName := PUNICODE_STRING(Context^.UserContext);
  if (RtlEqualUnicodeString(@Entry^.TypeName, pusTypeName, True)) then
  begin
    MainForm.EditDeviceName.Items.Add(Context^.ObjectPathName);
  end;

  Result := False;
end;

procedure TMainForm.BuildIoctl(Sender: TObject);
var
  ioctl, devtype, method, funcid, access: DWORD;
begin
  devtype := HexToDword(EditDevType.Text);
  method := ComboBoxIoMethod.ItemIndex;
  funcid := HexToDword(EditFunctionId.Text);
  access := ComboBoxIoAccess.ItemIndex;
  ioctl := IoctlToCode(devtype, funcid, method, access);
  EditIoctlValue.Text := IntToHex(ioctl, 8);
end;

procedure TMainForm.ButtonOpenFileClick(Sender: TObject);
var
  drvNameNoExt, drvName, oldName: string;
  cbStartType, cbErrorControl: TComboBox;
  editFile, editName, editDisplayName: TEdit;
begin
  if (PageControl1.ActivePage <> ScmTabSheet) and
    (PageControl1.ActivePage <> NativeTabSheet) then
  begin
    exit;
  end;

  OpenDialog1.Filter := DrvLoadDialogFilter;
  OpenDialog1.DefaultExt := DefaultExt;
  if OpenDialog1.Execute() then
  begin
    drvName := ExtractFileName(OpenDialog1.FileName);
    drvNameNoExt := ExtractFileNameWithoutExt(drvName);

    if (PageControl1.ActivePage = ScmTabSheet) then
    begin
      oldName := EditScmFileName.Text;
      cbStartType := ComboBoxScmStartType;
      cbErrorControl := ComboBoxScmErrorControl;
      editFile := EditScmFileName;
      editName := EditScmName;
      editDisplayName := EditScmDisplayName;
    end
    else
    if (PageControl1.ActivePage = NativeTabSheet) then
    begin
      oldName := EditNativeFileName.Text;
      cbStartType := ComboBoxNativeStartType;
      cbErrorControl := ComboBoxNativeErrorControl;
      editFile := EditNativeFileName;
      editName := EditNativeName;
      editDisplayName := EditNativeDisplayName;
    end;

    oldName := editFile.Text;
    if (OpenDialog1.FileName <> oldName) then
    begin
      cbStartType.ItemIndex := 3;
      cbErrorControl.ItemIndex := 0;
    end;

    editFile.Text := OpenDialog1.FileName;
    editName.Text := drvNameNoExt;
    editDisplayName.Text := drvName;

  end;
end;

procedure TMainForm.SpinEditInputBufferChange(Sender: TObject);
begin
  if (CheckBoxOutBuffer.Checked) then
    SpinEditOutputBuffer.Value := SpinEditInputBuffer.Value;
end;

procedure TMainForm.ManageInstalledDriverSCM(Sender: TObject);
var
  schSCManager: SC_HANDLE;
  scmStatus: DWORD;
  drvName: PChar;
  drvEntryName: string;
begin

  drvEntryName := EditScmName.Text;

  //mandatory
  if (drvEntryName = '') then
  begin
    ShowStatus(ERROR_INVALID_SERVICENAME);
    exit;
  end;

  scmStatus := ERROR_SUCCESS;
  schSCManager := 0;

  try

    drvName := PChar(drvEntryName);

    if scmOpenManager(SC_MANAGER_ALL_ACCESS, schSCManager, scmStatus) then
    begin

      case TComponent(Sender).Tag of
        1:  //start
        begin
          MemoLog.Lines.Add('Loading driver: ' + drvEntryName);
          scmStartDriver(schSCManager, drvName, scmStatus);
        end;
        2:  //stop
        begin
          MemoLog.Lines.Add('Unloading driver: ' + drvEntryName);
          scmStopDriver(schSCManager, drvName, scmStatus);
        end;

        3: //remove
        begin
          MemoLog.Lines.Add('Removing driver entry: ' + drvEntryName);
          scmRemoveDriver(schSCManager, drvName, scmStatus);
        end;
        else
          scmStatus := ERROR_INVALID_PARAMETER;
      end;
    end;

  finally
    ShowStatus(scmStatus);
    scmCloseManager(schSCManager, scmStatus);
  end;

end;

procedure TMainForm.PrintToLog(LogEntry: string);
begin
  MemoLog.Lines.Add(LogEntry);
end;

procedure TMainForm.ShowStatus(Status: DWORD);
begin
  PrintToLog(Format('Error code: %d', [Status]) + Format(' [0x%x]', [Status]));
  PrintToLog(SysErrorMessage(Status));
end;

procedure TMainForm.ShowStatus(Status: NTSTATUS);
var
  Buffer: PWideChar;
  dwMessageId, Length, dwFlags: ULONG;
  hDll: HMODULE;
  s: UnicodeString;
begin
  Buffer := nil;

  dwMessageId := Status and FACILITY_NT_BIT;

  // hr to exception
  if (dwMessageId <> 0) then
    dwMessageId := DWORD(Status and not FACILITY_NT_BIT)
  else
    dwMessageId := DWORD(Status);

  dwFlags := FORMAT_MESSAGE_ALLOCATE_BUFFER or FORMAT_MESSAGE_FROM_HMODULE;

  hDll := GetModuleHandle(ntdll);
  Length := FormatMessageW(
                    dwFlags,
                    LPCVOID(hDll),
                    dwMessageId,
                    0,
                    @Buffer,
                    0,
                    nil);

  try
     while (Length > 0) and ((Buffer[Length - 1] <= WideChar(#32)) or
       (Buffer[Length - 1] = WideChar('.'))) do Dec(Length);

     SetString(s, Buffer, Length);

     PrintToLog(Format('Error code: %d', [Status]) + Format(' [0x%x]', [Status]));
     PrintToLog(string(s));

  finally
    LocalFree(HLOCAL(Buffer));
  end;
end;

procedure TMainForm.ButtonNativeInstallClick(Sender: TObject);
var
  StartType: DWORD;
  ErrorControl: DWORD;
  DisplayName: PWideChar;
  DrvName: PWideChar;
  ImagePath: PWideChar;
  SymLink: PWideChar;
  Status: NTSTATUS;
  SymLinkHandle: THANDLE;
  bSymLink: boolean;
  S: string;
  drvEntryName: string;
begin

  drvEntryName := EditNativeName.Text;

  //mandatory
  if (drvEntryName = '') then
  begin
    ShowStatus(STATUS_OBJECT_NAME_NOT_FOUND);
    exit;
  end;

  bSymLink := CheckBoxSymLink.Checked;

  if (bSymLink) then
  begin

    if (EditNativeSymLink.Text = '') then
    begin
      PrintToLog('Specify symbolic link name');
      exit;
    end;

    SymLink := PWideChar(WideString(EditNativeSymLink.Text));

    PrintToLog('Installing driver entry: ' + drvEntryName +
      ' using symbolic link ' + EditNativeSymLink.Text);
  end
  else
  begin
    PrintToLog('Installing driver entry: ' + drvEntryName);
  end;


  DisplayName := nil;
  ImagePath := nil;

  StartType := ComboBoxNativeStartType.ItemIndex;
  ErrorControl := ComboBoxNativeErrorControl.ItemIndex;

  if (EditNativeDisplayName.Text <> '') then
  begin
    DisplayName := PWideChar(WideString(EditNativeDisplayName.Text));
  end;

  if (EditNativeFileName.Text <> '') then
  begin
    ImagePath := PWideChar(WideString(EditNativeFileName.Text));
  end;

  try

    S := Format(WIN32_CURRENTCONTROL_SERVICES, [drvEntryName]);

  except
    ShowStatus(STATUS_INTERNAL_ERROR);
    exit;
  end;

  DrvName := PWideChar(WideString(S));

  if (bSymLink) then
  begin
    SymLinkHandle := 0;
    Status := ntsupCreateSymbolicLink(SymLinkHandle, SymLink, ImagePath);
    if (NT_SUCCESS(Status)) then
    begin
      Status := ntsupCreateDriverEntry(DrvName, ErrorControl, StartType,
        SymLink, DisplayName, False);
    end;
  end
  else
  begin
    Status := ntsupCreateDriverEntry(DrvName, ErrorControl, StartType,
      ImagePath, DisplayName, True);
  end;

  ShowStatus(Status);

end;

procedure TMainForm.ButtonInBufferBrowseClick(Sender: TObject);
var
  lpBuffer: PChar;
  BufferSize: DWORD;
begin
  case TComponent(Sender).Tag of
    1:
    begin
      OpenDialog1.Filter := DefaultDialogFilter;
      if (OpenDialog1.Execute) then
      begin
        lpBuffer := nil;
        BufferSize := 0;

        if (ReadInputBuffer(OpenDialog1.FileName, lpBuffer, BufferSize)) then
        begin
          if (g_DataBuffer <> nil) then
          begin
            HeapFree(GetProcessHeap(), 0, g_DataBuffer);
          end;
          g_DataBuffer := lpBuffer;
          g_DataSize := BufferSize;
          SpinEditInputBuffer.Value := BufferSize;
        end
        else
          ShowStatus(GetLastError());

        EditInBufferName.Text := OpenDialog1.FileName;
      end;
    end;
    2:
    begin
      SaveDialog1.Filter := DefaultDialogFilter;
      if (SaveDialog1.Execute) then
      begin
        EditOutBufferName.Text := SaveDialog1.FileName;
        if CheckBoxOutBuffer.Checked then
        begin
          CheckBoxOutBuffer.Checked := False;
          SpinEditOutputBuffer.Enabled := True;
          SpinEditOutputBuffer.Value := 0;
        end;
      end;
    end;
    else
      exit;
  end;

end;

procedure TMainForm.ButtonCallDriverClick(Sender: TObject);
var
  Status: NTSTATUS;
  SingleBuffer: boolean;
  processHeap, devHandle: THandle;
  IoControlCode: DWORD;
  InputSize, OutputSize, sz: DWORD;
  devName, s: string;
  InputBuffer, OutputBuffer: PChar;
  iost: IO_STATUS_BLOCK;
  dwError: DWORD;
  k: byte;
begin

  try

    processHeap := GetProcessHeap();

    SingleBuffer := CheckBoxOutBuffer.Checked;

    // Read DeviceName
    devName := EditDeviceName.Text;
    if (devName = '') then
    begin
      PrintToLog('Device name is not specified');
      exit;
    end;

    // Read IOCTL value
    s := EditIoctlValue.Text;
    if (s = '') then
    begin
      PrintToLog('Control code is not specified');
      exit;
    end;

    IoControlCode := HexToDword(s);

    // Open device handle
    devHandle := 0;
    Status := ntsupOpenDeviceEx(PWideChar(WideString(devName)),
      GENERIC_READ or GENERIC_WRITE, devHandle);
    if (not NT_SUCCESS(Status)) then
    begin
      PrintToLog('Failed to open ' + devName);
      ShowStatus(Status);
      exit;
    end;

    // Allocate input buffer
    InputSize := SpinEditInputBuffer.Value;
    if (InputSize <> 0) then
    begin
      InputBuffer := PChar(HeapAlloc(processHeap, HEAP_ZERO_MEMORY, InputSize));
      if (InputBuffer = nil) then
      begin
        dwError := GetLastError();
        PrintToLog('InputBuffer is NULL');
        ShowStatus(dwError);
      end;
    end
    else
    begin
      InputBuffer := nil;
    end;

    // In/out buffers are the same
    if (SingleBuffer) then
    begin
      OutputBuffer := InputBuffer;
      OutputSize := InputSize;
    end
    else
    begin

      // Allocate ouput buffer
      OutputSize := SpinEditOutputBuffer.Value;
      if (OutputSize <> 0) then
      begin
        OutputBuffer := PChar(HeapAlloc(processHeap, HEAP_ZERO_MEMORY, OutputSize));
        if (OutputBuffer = nil) then
        begin
          dwError := GetLastError();
          PrintToLog('OutputBuffer is NULL');
          ShowStatus(dwError);
        end;
      end
      else
      begin
        OutputBuffer := nil;
      end;

    end;

    // Fill Byte is checked
    if (CheckBoxFillByte.Checked) then
    begin
      if ((InputBuffer <> nil) and (InputSize > 0)) then
      begin
        s := EditIoctlFill.Text;
        k := byte(HexToDword(s));
        FillMemory(InputBuffer, InputSize, k);
      end;
    end
    else
    begin
      // Otherwise use supplied data from file
      sz := InputSize;
      if (sz > g_DataSize) then
        sz := g_DataSize;

      CopyMemory(InputBuffer, g_DataBuffer, sz);

    end;

    // Call driver
    ZeroMemory(@iost, sizeof(iost));
    Status := NtDeviceIoControlFile(devHandle, 0, nil, nil, @iost,
      IoControlCode, InputBuffer, InputSize, OutputBuffer, OutputSize);

    // Free resources
    NtClose(devHandle);

    PrintToLog('NtDeviceIoControlFile(' + devName + ') result: ');
    ShowStatus(Status);

    if (NT_SUCCESS(Status)) then
    begin
      s := EditOutBufferName.Text;
      if ((s <> '') and (OutputBuffer <> nil)) then
        if (not WriteOutputBuffer(s, OutputBuffer, OutputSize)) then
        begin
          ShowStatus(GetLastError());
        end;
    end;

    if (not SingleBuffer) then
      HeapFree(processHeap, 0, OutputBuffer);

    HeapFree(processHeap, 0, InputBuffer);

  except
    on E: Exception do
    begin
      PrintToLog(E.Message);
    end;
  end;
end;

procedure TMainForm.AboutSheetShow(Sender: TObject);
var
  osver: OSVERSIONINFOW;
begin
  VersionLabel.Caption := IntToStr(PROGRAM_VERSION_MAJOR) + '.' +
    IntToStr(PROGRAM_VERSION_MINOR) + '.' + IntToStr(PROGRAM_VERSION_BUILD);

  CompilerLabel.Caption := PROGRAM_COMPILER + {$I %FPCVERSION%};
  BuildDateLabel.Caption := {$I %DATE% } + ' ' + {$I %TIME%};

  ZeroMemory(@osver, sizeof(osver));
  RtlGetVersion(@osver);

  OSNameLabel.Caption := 'Windows NT ' + IntToStr(osver.dwMajorVersion) +
    '.' + IntToStr(osver.dwMinorVersion) + '.' + IntToStr(osver.dwBuildNumber);
end;

procedure TMainForm.ButtonIoctlResetClick(Sender: TObject);
begin
  SpinEditInputBuffer.Value := 0;
  SpinEditOutputBuffer.Value := 0;
  CheckBoxFillByte.Checked := False;
  EditIoctlFill.Text := 'a';
  CheckBoxOutBuffer.Checked := False;
  CheckBoxUseFiles.Checked := False;
  if (g_DataBuffer <> nil) then
  begin
    HeapFree(GetProcessHeap(), 0, g_DataBuffer);
    g_DataBuffer := nil;
    g_DataSize := 0;
  end;
end;

procedure TMainForm.ButtonNativeLoadClick(Sender: TObject);
var
  Status: NTSTATUS;
  bForceLoad: boolean;
  drvName: string;
begin
  bForceLoad := CheckBoxForceLoad.Checked;
  drvName := EditNativeName.Text;

  //mandatory
  if (drvName = '') then
  begin
    ShowStatus(STATUS_OBJECT_NAME_NOT_FOUND);
    exit;
  end;

  drvName := EditNativeName.Text;

  PrintToLog('Loading driver: ' + drvName);
  if (bForceLoad) then
    PrintToLog('Unload previous instance enabled');

  Status := ntsupLoadDriver(PWideChar(WideString(drvName)), bForceLoad);

  ShowStatus(Status);
end;

procedure TMainForm.ButtonNativeRemoveClick(Sender: TObject);
var
  Status: NTSTATUS;
  drvName: string;
begin

  drvName := EditNativeName.Text;

  //mandatory
  if (drvName = '') then
  begin
    ShowStatus(STATUS_OBJECT_NAME_NOT_FOUND);
    exit;
  end;

  PrintToLog('Removing driver entry: ' + drvName);

  Status := ntsupRemoveDriverEntry(PWideChar(WideString(drvName)));
  ShowStatus(Status);
end;

procedure TMainForm.ButtonNativeUnloadClick(Sender: TObject);
var
  Status: NTSTATUS;
  drvName: string;
begin
  drvName := EditNativeName.Text;

  //mandatory
  if (drvName = '') then
  begin
    ShowStatus(STATUS_OBJECT_NAME_NOT_FOUND);
    exit;
  end;

  PrintToLog('Unloading driver: ' + drvName);

  Status := ntsupUnloadDriver(PWideChar(WideString(drvName)));
  ShowStatus(Status);

  if (Status = STATUS_OBJECT_NAME_NOT_FOUND) then
  begin
    PrintToLog(
      'Hint: It is possible that driver entry in registry deleted/not exist.' +
      #13#10'In this case you can use "Install" button to create new.');
  end;
end;

procedure TMainForm.ButtonScmInstallClick(Sender: TObject);
var
  schSCManager: SC_HANDLE;
  scmStatus: DWORD;
  drvName, displayName, binaryPath: PChar;
  drvEntryName: string;
begin

  drvEntryName := EditScmName.Text;

  //mandatory
  if (drvEntryName = '') then
  begin
    ShowStatus(ERROR_INVALID_SERVICENAME);
    exit;
  end;

  //mandatory
  if (EditScmFileName.Text = '') then
  begin
    ShowStatus(ERROR_FILE_NOT_FOUND);
    exit;
  end;

  scmStatus := ERROR_SUCCESS;
  schSCManager := 0;
  PrintToLog('Installing driver entry: ' + drvEntryName);

  try

    drvName := PChar(drvEntryName);
    binaryPath := PChar(EditScmFileName.Text);

    //optional
    if (EditScmDisplayName.Text = '') then
      displayName := nil
    else
      displayName := PChar(EditScmDisplayName.Text);

    if (scmOpenManager(SC_MANAGER_ALL_ACCESS, schSCManager, scmStatus)) then
    begin
      scmInstallDriver(schSCManager, drvName, displayName,
        ComboBoxScmStartType.ItemIndex, ComboBoxScmErrorControl.ItemIndex,
        binaryPath, scmStatus);
    end;

    ShowStatus(scmStatus);

  finally
    scmCloseManager(schSCManager, scmStatus);
  end;

end;

procedure TMainForm.CheckBoxOutBufferChange(Sender: TObject);
begin
  if (CheckBoxOutBuffer.Checked) then
    SpinEditOutputBuffer.Value := SpinEditInputBuffer.Value;
  SpinEditOutputBuffer.Enabled := not CheckBoxOutBuffer.Checked;
end;

procedure TMainForm.CheckBoxSymLinkClick(Sender: TObject);
begin
  EditNativeSymLink.Enabled := CheckBoxSymLink.Checked;
end;

procedure TMainForm.CheckBoxUseFilesChange(Sender: TObject);
begin
  EditInBufferName.Enabled := CheckBoxUseFiles.Checked;
  EditOutBufferName.Enabled := CheckBoxUseFiles.Checked;
  ButtonInBufferBrowse.Enabled := CheckBoxUseFiles.Checked;
  ButtonOutBufferBrowse.Enabled := CheckBoxUseFiles.Checked;
end;

procedure TMainForm.EditDevTypeKeyUp(Sender: TObject; var Key: word;
  Shift: TShiftState);
begin
  BuildIoctl(Sender);
end;

procedure TMainForm.EditIoCtlCodeKeyPress(Sender: TObject; var Key: char);
begin
  if not (Key in [#8, #22, 'a'..'f', 'A'..'F', '0'..'9']) then
  begin
    Key := #0;
  end;
end;

procedure TMainForm.EditIoctlValueChange(Sender: TObject);
var
  S: string;
  ioctl, method, access: DWORD;
begin
  try
    S := EditIoctlValue.Text;

    ioctl := HexToDword(S);
    access := (ioctl and $c000) shr 14;
    method := (ioctl and $3);

    if (access > DWORD(ComboBoxIoAccess.Items.Count)) then
    begin
      ShowMessage('Invalid access value in supplied IOCTL');
      exit;
    end;

    ComboBoxIoAccess.ItemIndex := access;

    if (method > DWORD(ComboBoxIoMethod.Items.Count)) then
    begin
      ShowMessage('Invalid method value in supplied IOCTL');
      exit;
    end;

    ComboBoxIoMethod.ItemIndex := method;

    EditFunctionId.Text := Format('%x', [(ioctl and $3ffc) shr 2]);
    EditDevType.Text := Format('%x', [(ioctl and $ffff0000) shr 16]);
  except

    on E: Exception do
    begin
      PrintToLog(E.Message);
    end;

  end;
end;

procedure TMainForm.FormCreate(Sender: TObject);
var
  i: integer;
  ChangeWindowMessageFilter: TChangeWindowMessageFilter;
  hUser32: Thandle;
const
  MSGFLT_ADD = 1;
  WM_COPYGLOBALDATA = 73;
begin

  try
    i := 0;
    if (ParamCount > 0) then
      i := StrToInt(ParamStr(1));

    if (i < PageControl1.PageCount) then
      PageControl1.ActivePageIndex := i
    else
      PageControl1.ActivePage := ScmTabSheet;

  except
    PageControl1.ActivePage := ScmTabSheet;
  end;

  IsFullAdmin := IsCurrentUserFullAdmin();
  if (not IsFullAdmin) then
  begin
    SendMessage(ButtonNativeInstall.Handle, BCM_SETSHIELD, WParam(0), LParam(True));
    SendMessage(ButtonNativeLoad.Handle, BCM_SETSHIELD, WParam(0), LParam(True));
    SendMessage(ButtonNativeUnload.Handle, BCM_SETSHIELD, WParam(0), LParam(True));
    SendMessage(ButtonNativeRemove.Handle, BCM_SETSHIELD, WParam(0), LParam(True));

    ButtonNativeInstall.OnClick := @ElevateButtonClick;
    ButtonNativeLoad.OnClick := @ElevateButtonClick;
    ButtonNativeUnload.OnClick := @ElevateButtonClick;
    ButtonNativeRemove.OnClick := @ElevateButtonClick;
  end
  else
  begin
    MainForm.Caption := MainForm.Caption + ' (elevated)';
  end;


  // Fix for elevation.

  hUser32 := LoadLibrary('user32.dll');
  if (hUser32 <> 0) then
  begin
    ChangeWindowMessageFilter :=
      TChangeWindowMessageFilter(GetProcAddress(hUser32, 'ChangeWindowMessageFilter'));
    if Assigned(ChangeWindowMessageFilter) then
    begin
      ChangeWindowMessageFilter(WM_DROPFILES, MSGFLT_ADD);
      ChangeWindowMessageFilter(WM_COPYGLOBALDATA, MSGFLT_ADD);
    end;
  end;

end;

procedure TMainForm.FormDropFiles(Sender: TObject; const FileNames: array of string);
var
  l: integer;
  drvName, drvNameNotExt: string;
begin
  l := Length(FileNames);
  if (l > 0) then
  begin

    drvName := ExtractFileName(FileNames[0]);
    drvNameNotExt := ExtractFileNameWithoutExt(drvName);
    if (PageControl1.ActivePage = ScmTabSheet) then
    begin
      EditScmFileName.Text := FileNames[0];
      if (EditScmDisplayName.Text = '') then
        EditScmDisplayName.Text := drvName;
      if (EditScmName.Text = '') then
        EditScmName.Text := drvNameNotExt;
    end
    else
    if (PageControl1.ActivePage = NativeTabSheet) then
    begin
      EditNativeFileName.Text := FileNames[0];
      if (EditNativeDisplayName.Text = '') then
        EditNativeDisplayName.Text := drvName;
      if (EditNativeName.Text = '') then
        EditNativeName.Text := drvNameNotExt;
    end;

  end;
end;

procedure TMainForm.Image1Click(Sender: TObject);
begin

end;

procedure TMainForm.IoctlSheetShow(Sender: TObject);
var
  usTypeName: UNICODE_STRING;
  enumContext: EnumObjectsContext;
begin
  EditDeviceName.Items.Clear();
  RtlInitUnicodeString(@usTypeName, PWideChar(OBJECT_TYPE_DEVICE));

  enumContext.UserContext := @usTypeName;
  enumContext.ObjectPathName := nil;

  ntsupEnumerateObjects(PwideChar('\'), PEnumObjectsCallback(@ObjectEnumProc),
    @enumContext);

  if (EditDeviceName.Items.Count > 0) then
    EditDeviceName.ItemIndex := 0;
end;

function EnablePrivilegeByName(lpPrivilegeName: LPCTSTR; fEnable: boolean): DWORD;

var
  TokenHandle: THANDLE;
  TokenPriv: TOKEN_PRIVILEGES;
  PrevTokenPriv: TOKEN_PRIVILEGES;
  ReturnLength: cardinal;
begin
  Result := ERROR_PRIVILEGE_NOT_HELD;
  TokenHandle := 0;
  if OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES or
    TOKEN_QUERY, TokenHandle) then
  begin
    try
      TokenPriv.Privileges[0].Luid := 0;

      if LookupPrivilegeValue(nil, lpPrivilegeName,
        TokenPriv.Privileges[0].Luid) then
      begin

        TokenPriv.PrivilegeCount := 1;

        if fEnable then
          TokenPriv.Privileges[0].Attributes := SE_PRIVILEGE_ENABLED
        else
          TokenPriv.Privileges[0].Attributes := 0;

        ReturnLength := 0;

        PrevTokenPriv := TokenPriv;

        AdjustTokenPrivileges(TokenHandle, False, TokenPriv,
          SizeOf(TokenPriv), PrevTokenPriv, ReturnLength);
        Result := GetLastError();

      end
      else
      begin
        Result := GetLastError();
      end;

    finally
      CloseHandle(TokenHandle);
    end;
  end
  else
  begin
    Result := GetLastError();
  end;

end;

procedure TMainForm.ListViewPrivSetMouseDown(Sender: TObject;
  Button: TMouseButton; Shift: TShiftState; X, Y: integer);
var
  Item: TListItem;
  Status: DWORD;
begin
  if Button = mbLeft then
    with Sender as TListView do
    begin
      Item := GetItemAt(X, Y);
      if Assigned(Item) then
        if htOnStateIcon in GetHitTestInfoAt(X, Y) then
        begin
          Status := EnablePrivilegeByName(PChar(Item.Caption), Item.Checked);
          if (Status <> ERROR_SUCCESS) then
          begin
            Item.Checked := not Item.Checked;
            if (Status = ERROR_NOT_ALL_ASSIGNED) then
              PrintToLog(PChar(Item.Caption) +
                ': The token does not have the specified privilege.')
            else
              ShowStatus(Status);
          end;
        end;
    end;
end;

procedure TMainForm.MenuItem1Click(Sender: TObject);
begin
  MemoLog.Clear();
end;

procedure TMainForm.NativeTabSheetHide(Sender: TObject);
var
  oldValue: boolean;
begin
  oldValue := False;
  RtlAdjustPrivilege(SE_LOAD_DRIVER_PRIVILEGE, False, False, oldValue);
end;

procedure TMainForm.NativeTabSheetShow(Sender: TObject);
var
  Status: NTSTATUS;
  oldValue: boolean;
begin
  if (not IsFullAdmin) then
  begin
    LabelPrivInfo.Caption :=
      'Hint: Elevation is required to access this page';
  end
  else
  begin

    oldValue := False;
    Status := RtlAdjustPrivilege(SE_LOAD_DRIVER_PRIVILEGE, True, False, oldValue);
    if not NT_SUCCESS(Status) then
    begin
      PrintToLog('Could not adjust SeLoadDriverPrivilege');
      ShowStatus(Status);
    end
    else
      LabelPrivInfo.Caption :=
        'Hint: SeLoadDriverPrivilege is auto adjusted when this this page is shown';

  end;
end;

procedure TMainForm.OptionsSheetShow(Sender: TObject);
var
  TokenHandle: THANDLE;
  TokenPriv: PRIVILEGE_SET;
  i: integer;
  fResult: boolean;
begin
  TokenHandle := 0;
  if OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, TokenHandle) then
  begin

    for i := 0 to ListViewPrivSet.Items.Count - 1 do
    begin

      TokenPriv.Privilege[0].Luid := 0;

      if (LookupPrivilegeValue(nil, PChar(ListViewPrivSet.Items[i].Caption),
        TokenPriv.Privilege[0].Luid)) then
      begin
        TokenPriv.Control := 0;
        TokenPriv.PrivilegeCount := 1;
        TokenPriv.Privilege[0].Attributes := SE_PRIVILEGE_ENABLED;
        fResult := False;
        if (PrivilegeCheck(TokenHandle, @TokenPriv, @fResult)) then
        begin
          ListViewPrivSet.Items[i].StateIndex := integer(fResult);
        end;

      end;

    end;

    CloseHandle(TokenHandle);
  end;

end;

procedure TMainForm.ScmTabSheetShow(Sender: TObject);
begin
  if (not IsFullAdmin) then
  begin
    LabelPrivInfoScm.Caption :=
      'Hint: Elevation is required to access this page';

    SendMessage(ButtonScmInstall.Handle, BCM_SETSHIELD, WParam(0), LParam(True));
    SendMessage(ButtonScmLoad.Handle, BCM_SETSHIELD, WParam(0), LParam(True));
    SendMessage(ButtonScmUnload.Handle, BCM_SETSHIELD, WParam(0), LParam(True));
    SendMessage(ButtonScmRemove.Handle, BCM_SETSHIELD, WParam(0), LParam(True));

    ButtonScmInstall.OnClick := @ElevateButtonClick;
    ButtonScmLoad.OnClick := @ElevateButtonClick;
    ButtonScmUnload.OnClick := @ElevateButtonClick;
    ButtonScmRemove.OnClick := @ElevateButtonClick;
  end
  else
  begin
    LabelPrivInfoScm.Caption := '';
  end;
end;

end.
