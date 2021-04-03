#ifndef	__PMDLL_H
#define	__PMDLL_H

#ifdef	PMDLL_EXPORTS
#define	DLL_DECLARE __declspec(dllexport)
#else
#define	DLL_DECLARE __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C"
{
#endif

//driver initialize
DLL_DECLARE BOOL LoadPhyMemDriver();
DLL_DECLARE VOID UnloadPhyMemDriver();

//map physical memory to user space
DLL_DECLARE PVOID MapPhyMem(DWORD phyAddr, DWORD memSize);
DLL_DECLARE VOID  UnmapPhyMem(PVOID pVirAddr, DWORD memSize);

//access port
DLL_DECLARE BYTE  ReadPortByte(WORD portAddr);
DLL_DECLARE WORD  ReadPortWord(WORD portAddr);
DLL_DECLARE DWORD ReadPortLong(WORD portAddr);
DLL_DECLARE VOID  WritePortByte(WORD portAddr, BYTE portValue);
DLL_DECLARE VOID  WritePortWord(WORD portAddr, WORD portValue);
DLL_DECLARE VOID  WritePortLong(WORD portAddr, DWORD portValue);

//access PCI bus
DLL_DECLARE BOOL ReadPCI(DWORD busNum, DWORD devNum, DWORD funcNum,
						 DWORD regOff, DWORD bytes, PVOID pValue);
DLL_DECLARE BOOL WritePCI(DWORD busNum, DWORD devNum, DWORD funcNum,
						  DWORD regOff, DWORD bytes, PVOID pValue);

#ifdef __cplusplus
}
#endif

#endif	//__PMDLL_H