/*++
PhyMem Driver
Ver: 1.0
Author: akui
Date: 2009/3/5
--*/

#include <windows.h>
#include <winioctl.h>
#include "pmdll.h"
#include "phymem.h"

HANDLE hDriver=INVALID_HANDLE_VALUE;

BOOL InstallDriver(PCSTR pszDriverPath, PCSTR pszDriverName);
BOOL RemoveDriver(PCSTR pszDriverName);
BOOL StartDriver(PCSTR pszDriverName);
BOOL StopDriver(PCSTR pszDriverName);

//get driver(phymem.sys) full path
static BOOL GetDriverPath(PSTR szDriverPath)
{
	PSTR pszSlash;

	if (!GetModuleFileName(GetModuleHandle(NULL), szDriverPath, MAX_PATH))
		return FALSE;

	pszSlash=strrchr(szDriverPath, '\\');

	if (pszSlash)
		pszSlash[1]='\0';
	else
		return FALSE;

	return TRUE;
}

//install and start driver
BOOL LoadPhyMemDriver()
{
	BOOL bResult;
	CHAR szDriverPath[MAX_PATH];

	hDriver=CreateFile( "\\\\.\\PhyMem",
						GENERIC_READ|GENERIC_WRITE,
						0,
						NULL,
						OPEN_EXISTING,
						FILE_ATTRIBUTE_NORMAL,
						NULL);

	//If the driver is not running, install it
	if (hDriver==INVALID_HANDLE_VALUE)
	{
		GetDriverPath(szDriverPath);
		strcat(szDriverPath, "phymem.sys");

		bResult=InstallDriver(szDriverPath, "PHYMEM");

		if (!bResult)
			return FALSE;

		bResult=StartDriver("PHYMEM");

		if (!bResult)
			return FALSE;

		hDriver=CreateFile( "\\\\.\\PhyMem",
							GENERIC_READ | GENERIC_WRITE,
							0,
							NULL,
							OPEN_EXISTING,
							FILE_ATTRIBUTE_NORMAL,
							NULL);

		if (hDriver==INVALID_HANDLE_VALUE)
			return FALSE;
	}

	return TRUE;
}

//stop and remove driver
VOID UnloadPhyMemDriver()
{
	if (hDriver!=INVALID_HANDLE_VALUE)
	{
		CloseHandle(hDriver);
		hDriver=INVALID_HANDLE_VALUE;
	}

	RemoveDriver("PHYMEM");
}

//map physical memory to user space
PVOID MapPhyMem(DWORD phyAddr, DWORD memSize)
{
	PVOID pVirAddr=NULL;	//mapped virtual addr
	PHYMEM_MEM pm;
	DWORD dwBytes=0;
	BOOL bRet=FALSE;

	pm.pvAddr=(PVOID)phyAddr;	//physical address
	pm.dwSize=memSize;	//memory size

	if (hDriver!=INVALID_HANDLE_VALUE)
	{
		bRet=DeviceIoControl(hDriver, IOCTL_PHYMEM_MAP, &pm,
			sizeof(PHYMEM_MEM), &pVirAddr, sizeof(PVOID), &dwBytes, NULL);
	}

	if (bRet && dwBytes==sizeof(PVOID))
		return pVirAddr;
	else
		return NULL;
}

//unmap memory
VOID UnmapPhyMem(PVOID pVirAddr, DWORD memSize)
{
	PHYMEM_MEM pm;
	DWORD dwBytes=0;

	pm.pvAddr=pVirAddr;	//virtual address
	pm.dwSize=memSize;	//memory size

	if (hDriver!=INVALID_HANDLE_VALUE)
	{
		DeviceIoControl(hDriver, IOCTL_PHYMEM_UNMAP, &pm,
			sizeof(PHYMEM_MEM), NULL, 0, &dwBytes, NULL);
	}
}

//read 1 byte from port
BYTE ReadPortByte(WORD portAddr)
{
	PHYMEM_PORT pp;
	DWORD pv=0;	//returned port value
	DWORD dwBytes;

	pp.dwPort=portAddr;
	pp.dwSize=1;	//1 byte

	if (hDriver!=INVALID_HANDLE_VALUE)
	{
		DeviceIoControl(hDriver, IOCTL_PHYMEM_GETPORT, &pp,
			sizeof(PHYMEM_PORT), &pv, sizeof(DWORD), &dwBytes, NULL);
	}

	return (BYTE)pv;
}

//read 2 bytes from port
WORD ReadPortWord(WORD portAddr)
{
	PHYMEM_PORT pp;
	DWORD pv=0;	//returned port value
	DWORD dwBytes;

	pp.dwPort=portAddr;
	pp.dwSize=2;	//2 bytes

	if (hDriver!=INVALID_HANDLE_VALUE)
	{
		DeviceIoControl(hDriver, IOCTL_PHYMEM_GETPORT, &pp,
			sizeof(PHYMEM_PORT), &pv, sizeof(DWORD), &dwBytes, NULL);
	}

	return (WORD)pv;
}

//read 4 bytes from port
DWORD ReadPortLong(WORD portAddr)
{
	PHYMEM_PORT pp;
	DWORD pv=0;	//returned port value
	DWORD dwBytes;

	pp.dwPort=portAddr;
	pp.dwSize=4;	//4 bytes

	if (hDriver!=INVALID_HANDLE_VALUE)
	{
		DeviceIoControl(hDriver, IOCTL_PHYMEM_GETPORT, &pp,
			sizeof(PHYMEM_PORT), &pv, sizeof(DWORD), &dwBytes, NULL);
	}

	return pv;
}

//write 1 byte to port
VOID WritePortByte(WORD portAddr, BYTE portValue)
{
	PHYMEM_PORT pp;
	DWORD dwBytes;

	pp.dwPort=portAddr;
	pp.dwValue=portValue;
	pp.dwSize=1;	//1 byte

	if (hDriver!=INVALID_HANDLE_VALUE)
	{
		DeviceIoControl(hDriver, IOCTL_PHYMEM_SETPORT, &pp,
			sizeof(PHYMEM_PORT), NULL, 0, &dwBytes, NULL);
	}
}

//write 2 bytes to port
VOID WritePortWord(WORD portAddr, WORD portValue)
{
	PHYMEM_PORT pp;
	DWORD dwBytes;

	pp.dwPort=portAddr;
	pp.dwValue=portValue;
	pp.dwSize=2;	//2 bytes

	if (hDriver!=INVALID_HANDLE_VALUE)
	{
		DeviceIoControl(hDriver, IOCTL_PHYMEM_SETPORT, &pp,
			sizeof(PHYMEM_PORT), NULL, 0, &dwBytes, NULL);
	}
}

//write 4 bytes to port
VOID WritePortLong(WORD portAddr, DWORD portValue)
{
	PHYMEM_PORT pp;
	DWORD dwBytes;

	pp.dwPort=portAddr;
	pp.dwValue=portValue;
	pp.dwSize=4;	//4 bytes

	if (hDriver!=INVALID_HANDLE_VALUE)
	{
		DeviceIoControl(hDriver, IOCTL_PHYMEM_SETPORT, &pp,
			sizeof(PHYMEM_PORT), NULL, 0, &dwBytes, NULL);
	}
}

//read pci configuration
BOOL ReadPCI(DWORD busNum, DWORD devNum, DWORD funcNum,
			 DWORD regOff, DWORD bytes, PVOID pValue)
{
	BOOL bRet=FALSE;
	DWORD dwBytes;
	PHYMEM_PCI pp;

	pp.dwBusNum=busNum;
	pp.dwDevNum=devNum;
	pp.dwFuncNum=funcNum;
	pp.dwRegOff=regOff;
	pp.dwBytes=bytes;
//	pp.pValue=NULL;

	if (hDriver!=INVALID_HANDLE_VALUE)
	{
		bRet=DeviceIoControl(hDriver, IOCTL_PHYMEM_GETPCI, &pp,
			sizeof(PHYMEM_PCI), pValue, bytes, &dwBytes, NULL);
	}

	if (bRet && dwBytes==bytes)
		return TRUE;
	else
		return FALSE;
}

//write pci configuration
BOOL WritePCI(DWORD busNum, DWORD devNum, DWORD funcNum,
			  DWORD regOff, DWORD bytes, PVOID pValue)
{
	BOOL bRet=FALSE;
	DWORD dwBytes;
	PHYMEM_PCI pp;

	pp.dwBusNum=busNum;
	pp.dwDevNum=devNum;
	pp.dwFuncNum=funcNum;
	pp.dwRegOff=regOff;
	pp.dwBytes=bytes;

	if (hDriver!=INVALID_HANDLE_VALUE)
	{
		//we use out buffer for storing the new values to write
		//it's strange but it works (METHOD_OUT_DIRECT) and ease the driver
		bRet=DeviceIoControl(hDriver, IOCTL_PHYMEM_SETPCI, &pp,
			sizeof(PHYMEM_PCI), pValue, bytes, &dwBytes, NULL);
	}

	if (bRet && dwBytes==bytes)
		return TRUE;
	else
		return FALSE;
}
