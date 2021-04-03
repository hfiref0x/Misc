/*++
Install and remove driver at runtime
--*/

#include <windows.h>

BOOL InstallDriver(PCSTR pszDriverPath, PCSTR pszDriverName);
BOOL RemoveDriver(PCSTR pszDriverName);
BOOL StartDriver(PCSTR pszDriverName);
BOOL StopDriver(PCSTR pszDriverName);

BOOL InstallDriver(PCSTR pszDriverPath, PCSTR pszDriverName)
{
	SC_HANDLE hSCManager;
	SC_HANDLE hService;

	//Remove any previous instance of the driver
	RemoveDriver(pszDriverName);

	hSCManager=OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

	if (hSCManager)
	{
		//Install the driver
		hService=CreateService( hSCManager,
								pszDriverName,
								pszDriverName,
								SERVICE_ALL_ACCESS,
								SERVICE_KERNEL_DRIVER,
								SERVICE_DEMAND_START,
								SERVICE_ERROR_NORMAL,
								pszDriverPath,
								NULL,
								NULL,
								NULL,
								NULL,
								NULL);

		CloseServiceHandle(hSCManager);
	
		if (hService==NULL)
			return FALSE;
	}
	else
		return FALSE;

	CloseServiceHandle(hService);

	return TRUE;
}

BOOL RemoveDriver(PCSTR pszDriverName)
{
	SC_HANDLE hSCManager;
	SC_HANDLE hService;
	BOOL bResult;

	StopDriver(pszDriverName);

	hSCManager=OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

	if (hSCManager)
	{
		hService=OpenService(hSCManager, pszDriverName, SERVICE_ALL_ACCESS);

		CloseServiceHandle(hSCManager);

		if (hService)
		{
			bResult=DeleteService(hService);

			CloseServiceHandle(hService);
		}
		else
			return FALSE;
	}
	else
		return FALSE;

	return bResult;
}

BOOL StartDriver(PCSTR pszDriverName)
{
	SC_HANDLE hSCManager;
	SC_HANDLE hService;
	BOOL bResult;

	hSCManager=OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

	if (hSCManager)
	{
		hService=OpenService(hSCManager, pszDriverName, SERVICE_ALL_ACCESS);

		CloseServiceHandle(hSCManager);

		if (hService)
		{
			bResult=StartService(hService, 0, NULL);
			if (bResult==FALSE)
			{
				if (GetLastError()==ERROR_SERVICE_ALREADY_RUNNING)
					bResult=TRUE;
			}

			CloseServiceHandle(hService);
		}
		else
			return FALSE;
	}
	else
		return FALSE;

	return bResult;
}

BOOL StopDriver(PCSTR pszDriverName)
{
	SC_HANDLE hSCManager;
	SC_HANDLE hService;
	SERVICE_STATUS ServiceStatus;
	BOOL bResult;

	hSCManager=OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

	if (hSCManager)
	{
		hService=OpenService(hSCManager, pszDriverName, SERVICE_ALL_ACCESS);

		CloseServiceHandle(hSCManager);

		if (hService)
		{
			bResult=ControlService(hService, SERVICE_CONTROL_STOP, &ServiceStatus);

			CloseServiceHandle(hService);
		}
		else
			return FALSE;
	}
	else
		return FALSE;

	return bResult;
}
