/*++
PhyMem Driver
Ver: 1.0
Author: akui
Date: 2009/3/2
--*/

#include <ntddk.h>
#include "phymem.h"
#include "DebugPrint.h"

//Mapped memory information list
typedef struct tagMAPINFO
{
	SINGLE_LIST_ENTRY	link;
	PMDL				pMdl;	//allocated mdl
	PVOID				pvk;	//kernel mode virtual address
	PVOID				pvu;	//user mode virtual address
	ULONG				memSize;//memory size in bytes
} MAPINFO, *PMAPINFO;

SINGLE_LIST_ENTRY lstMapInfo;	//mapped memory information
PFILE_OBJECT pcifo=NULL;		//pci bus filter driver file object
PDEVICE_OBJECT pcifido=NULL;	//pci bus filter driver device object
PPCI_BUS_INTERFACE_STANDARD busInterface=NULL;	//pci driver interface

//forward function declaration
NTSTATUS PhyMemCreate(IN PDEVICE_OBJECT fdo, IN PIRP irp);
NTSTATUS PhyMemClose(IN PDEVICE_OBJECT fdo, IN PIRP irp);
NTSTATUS PhyMemIoCtl(IN PDEVICE_OBJECT fdo, IN PIRP irp);
VOID PhyMemUnload(IN PDRIVER_OBJECT dro);

NTSTATUS GetBusInterface(IN PDEVICE_OBJECT pcifido,
	OUT PPCI_BUS_INTERFACE_STANDARD	busInterface);

//local functions
static NTSTATUS PreGetBus();
static NTSTATUS ReadWriteConfig(PIRP irp, PPHYMEM_PCI pPci, BOOLEAN isRead);


/*++
DriverEntry routine
--*/
NTSTATUS DriverEntry (IN PDRIVER_OBJECT DriverObject,
					  IN PUNICODE_STRING RegistryPath)
{
	UNICODE_STRING DeviceNameU;
	UNICODE_STRING DeviceLinkU;
	NTSTATUS ntStatus;
	PDEVICE_OBJECT fdo=NULL;

	UNREFERENCED_PARAMETER(RegistryPath);

	DebugPrintInit("PhyMem");
	DebugPrintMsg("Entering DriverEntry");

	lstMapInfo.Next=NULL;

	//initialize pci bus interface buffer
	busInterface=(PPCI_BUS_INTERFACE_STANDARD)ExAllocatePool(NonPagedPool,
		sizeof(PCI_BUS_INTERFACE_STANDARD));
	if (busInterface==NULL)
	{
		return STATUS_INSUFFICIENT_RESOURCES;
	}
	RtlZeroMemory(busInterface, sizeof(PCI_BUS_INTERFACE_STANDARD));

	RtlInitUnicodeString(&DeviceNameU, L"\\Device\\PhyMem");

	//Create an EXCLUSIVE device object
	ntStatus=IoCreateDevice(DriverObject,		//IN: Driver Object
							0,					//IN: Device Extension Size
							&DeviceNameU,		//IN: Device Name
							FILE_DEVICE_PHYMEM,	//IN: Device Type
							0,					//IN: Device Characteristics
							TRUE,				//IN: Exclusive
							&fdo);				//OUT:Created Device Object

	if (NT_SUCCESS(ntStatus))
	{
		if (NT_SUCCESS(ntStatus))
		{
			//Dispatch functions
			DriverObject->MajorFunction[IRP_MJ_CREATE]=PhyMemCreate;
			DriverObject->MajorFunction[IRP_MJ_CLOSE]=PhyMemClose;
			DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL]=PhyMemIoCtl;
			DriverObject->DriverUnload=PhyMemUnload;

			//Create a symbolic link
			RtlInitUnicodeString(&DeviceLinkU, L"\\DosDevices\\PhyMem");
			ntStatus=IoCreateSymbolicLink(&DeviceLinkU, &DeviceNameU);

			if (!NT_SUCCESS(ntStatus))
			{
				DebugPrintMsg("Error: IoCreateSymbolicLink failed");

				IoDeleteDevice(fdo);
			}
		}
		else
		{
			DebugPrintMsg("Error: IoGetDeviceObjectPointer failed");

			IoDeleteDevice(fdo);
		}
	}
	else
		DebugPrintMsg("Error: IoCreateDevice failed");

	DebugPrintMsg("Leaving DriverEntry");

	return ntStatus;
}

/*++
IRP_MJ_CREATE dispatch routine
--*/
NTSTATUS PhyMemCreate(IN PDEVICE_OBJECT fdo, IN PIRP irp)
{
	UNREFERENCED_PARAMETER(fdo);

	irp->IoStatus.Status=STATUS_SUCCESS;
	irp->IoStatus.Information=0;

	IoCompleteRequest(irp, IO_NO_INCREMENT);

	DebugPrintMsg("IRP_MJ_CREATE");

	return STATUS_SUCCESS;
}

/*++
IRP_MJ_CLOSE dispatch routine
--*/
NTSTATUS PhyMemClose(IN PDEVICE_OBJECT fdo, IN PIRP irp)
{
	UNREFERENCED_PARAMETER(fdo);

	irp->IoStatus.Status=STATUS_SUCCESS;
	irp->IoStatus.Information=0;

	IoCompleteRequest(irp, IO_NO_INCREMENT);

	DebugPrintMsg("IRP_MJ_CLOSE");

	return STATUS_SUCCESS;
}

/*++
IRP_MJ_DEVICE_CONTROL dispatch routine
--*/
NTSTATUS PhyMemIoCtl(IN PDEVICE_OBJECT fdo, IN PIRP irp)
{
	PIO_STACK_LOCATION irpStack;
	ULONG dwInBufLen;
	ULONG dwOutBufLen;
	ULONG dwIoCtlCode;
	NTSTATUS ntStatus;
	PVOID pSysBuf;
	PPHYMEM_MEM pMem;
	PPHYMEM_PORT pPort;
	PPHYMEM_PCI pPci;

	DebugPrintMsg("Entering PhyMemIoCtl");

	//Init to default settings
	irp->IoStatus.Status=STATUS_SUCCESS;
	irp->IoStatus.Information=0;

	irpStack=IoGetCurrentIrpStackLocation(irp);

	//Get the pointer to the input/output buffer and it's length
	pSysBuf=(PVOID)irp->AssociatedIrp.SystemBuffer;
	pMem=(PPHYMEM_MEM)pSysBuf;
	pPort=(PPHYMEM_PORT)pSysBuf;
	pPci=(PPHYMEM_PCI)pSysBuf;
	dwInBufLen=irpStack->Parameters.DeviceIoControl.InputBufferLength;
	dwOutBufLen=irpStack->Parameters.DeviceIoControl.OutputBufferLength;

	switch (irpStack->MajorFunction)
	{
	case IRP_MJ_DEVICE_CONTROL:

		dwIoCtlCode=irpStack->Parameters.DeviceIoControl.IoControlCode;

		switch (dwIoCtlCode)
		{
		case IOCTL_PHYMEM_MAP:

			if (dwInBufLen==sizeof(PHYMEM_MEM) && dwOutBufLen==sizeof(PVOID))
			{
				PHYSICAL_ADDRESS phyAddr;
				PVOID pvk, pvu;

				phyAddr.QuadPart=(ULONGLONG)pMem->pvAddr;

				//get mapped kernel address
				pvk=MmMapIoSpace(phyAddr, pMem->dwSize, MmNonCached);

				if (pvk)
				{
					//allocate mdl for the mapped kernel address
					PMDL pMdl=IoAllocateMdl(pvk, pMem->dwSize, FALSE, FALSE, NULL);
					if (pMdl)
					{
						PMAPINFO pMapInfo;

						//build mdl and map to user space
						MmBuildMdlForNonPagedPool(pMdl);
						pvu=MmMapLockedPages(pMdl, UserMode);

						//insert mapped infomation to list
						pMapInfo=(PMAPINFO)ExAllocatePool(\
							NonPagedPool, sizeof(MAPINFO));
						pMapInfo->pMdl=pMdl;
						pMapInfo->pvk=pvk;
						pMapInfo->pvu=pvu;
						pMapInfo->memSize=pMem->dwSize;
						PushEntryList(&lstMapInfo, &pMapInfo->link);

						DebugPrint("Map physical 0x%x to virtual 0x%x, size %u", \
							pMem->pvAddr, pvu, pMem->dwSize);

						RtlCopyMemory(pSysBuf, &pvu, sizeof(PVOID));

						irp->IoStatus.Information=sizeof(PVOID);
					}
					else
					{
						//allocate mdl error, unmap the mapped physical memory
						MmUnmapIoSpace(pvk, pMem->dwSize);

						irp->IoStatus.Status=STATUS_INSUFFICIENT_RESOURCES;
					}
				}
				else
					irp->IoStatus.Status=STATUS_INSUFFICIENT_RESOURCES;
			}
			else
				irp->IoStatus.Status=STATUS_INVALID_PARAMETER;

			break;

	    case IOCTL_PHYMEM_UNMAP:

			DebugPrintMsg("IOCTL_PHYMEM_UNMAP");

			if (dwInBufLen==sizeof(PHYMEM_MEM))
			{
				PMAPINFO pMapInfo;
				PSINGLE_LIST_ENTRY pLink, pPrevLink;

				//initialize to head
				pPrevLink=pLink=lstMapInfo.Next;
				while(pLink)
				{
					pMapInfo=CONTAINING_RECORD(pLink, MAPINFO, link);

					if (pMapInfo->pvu==pMem->pvAddr)
					{
						if (pMapInfo->memSize==pMem->dwSize)
						{
							//free mdl, unmap mapped memory
							MmUnmapLockedPages(pMapInfo->pvu, pMapInfo->pMdl); 
							IoFreeMdl(pMapInfo->pMdl);
							MmUnmapIoSpace(pMapInfo->pvk, pMapInfo->memSize);

							DebugPrint("Unmap virtual address 0x%x, size %u",\
								pMapInfo->pvu, pMapInfo->memSize);

							//delete matched element from the list
							if (pLink==lstMapInfo.Next)
								lstMapInfo.Next=pLink->Next;	//delete head elememt
							else
								pPrevLink->Next=pLink->Next;

							ExFreePool(pMapInfo);
						}
						else
							irp->IoStatus.Status=STATUS_INVALID_PARAMETER;

						break;
					}

					pPrevLink=pLink;
					pLink=pLink->Next;
				}
			}
			else
				irp->IoStatus.Status=STATUS_INVALID_PARAMETER;

			break;

		case IOCTL_PHYMEM_GETPORT:

			DebugPrintMsg("IOCTL_PHYMEM_GETPORT");

			if (dwInBufLen==sizeof(PHYMEM_PORT) && dwOutBufLen==sizeof(ULONG))
			{
				irp->IoStatus.Information=sizeof(ULONG);

				if (pPort->dwSize==1)
				{
					*(PULONG)pSysBuf=(ULONG)READ_PORT_UCHAR((PUCHAR)pPort->dwPort);
				}
				else if (pPort->dwSize==2)
				{
					*(PULONG)pSysBuf=(ULONG)READ_PORT_USHORT((PUSHORT)pPort->dwPort);
				}
				else if (pPort->dwSize==4)
				{
					*(PULONG)pSysBuf=READ_PORT_ULONG((PULONG)pPort->dwPort);
				}
				else
					irp->IoStatus.Status=STATUS_INVALID_PARAMETER;
			}
			else
				irp->IoStatus.Status=STATUS_INVALID_PARAMETER;

			break;

		case IOCTL_PHYMEM_SETPORT:

			DebugPrintMsg("IOCTL_PHYMEM_SETPORT");

			if (dwInBufLen==sizeof(PHYMEM_PORT))
			{
				if (pPort->dwSize==1)
				{
					WRITE_PORT_UCHAR((PUCHAR)pPort->dwPort, (UCHAR)pPort->dwValue);
				}
				else if (pPort->dwSize==2)
				{
					WRITE_PORT_USHORT((PUSHORT)pPort->dwPort, (USHORT)pPort->dwValue);
				}
				else if (pPort->dwSize==4)
				{
					WRITE_PORT_ULONG((PULONG)pPort->dwPort, pPort->dwValue);
				}
				else
					irp->IoStatus.Status=STATUS_INVALID_PARAMETER;
			}
			else
				irp->IoStatus.Status=STATUS_INVALID_PARAMETER;

			break;

		case IOCTL_PHYMEM_GETPCI:

			DebugPrintMsg("IOCTL_PHYMEM_GETPCI");

			//register offset + bytes to read cannnot exceed 256(pci config space limit)
			if (dwInBufLen==sizeof(PHYMEM_PCI) &&
				((pPci->dwRegOff + pPci->dwBytes)<=256) && (dwOutBufLen>=pPci->dwBytes))
			{
				irp->IoStatus.Status=ReadWriteConfig(irp, pPci, TRUE);

				if (NT_SUCCESS(irp->IoStatus.Status))
				{
					irp->IoStatus.Information=pPci->dwBytes;
				}
			}
			else
				irp->IoStatus.Status=STATUS_INVALID_PARAMETER;

			break;

		case IOCTL_PHYMEM_SETPCI:

			DebugPrintMsg("IOCTL_PHYMEM_SETPCI");

			//register offset + bytes to write cannnot exceed 256(pci config space limit)
			//new values to write are stored in out buffer(strange but it works)
			if (dwInBufLen==sizeof(PHYMEM_PCI) &&
				((pPci->dwRegOff + pPci->dwBytes)<=256) && (dwOutBufLen>=pPci->dwBytes))
			{
				irp->IoStatus.Status=ReadWriteConfig(irp, pPci, FALSE);

				if (NT_SUCCESS(irp->IoStatus.Status))
				{
					irp->IoStatus.Information=pPci->dwBytes;
				}
			}
			else
				irp->IoStatus.Status=STATUS_INVALID_PARAMETER;

			break;

		default:

			DebugPrintMsg("Error: Unknown IO CONTROL CODE");

			break;
		}

		break;
	}

	ntStatus=irp->IoStatus.Status;

	IoCompleteRequest(irp, IO_NO_INCREMENT);

	DebugPrintMsg("Leaving PhyMemIoCtl");

	return ntStatus;
}

/*++
Driver Unload routine
--*/
VOID PhyMemUnload(IN PDRIVER_OBJECT dro)
{
	UNICODE_STRING DeviceLinkU;
	NTSTATUS ntStatus;
	PMAPINFO pMapInfo;
	PSINGLE_LIST_ENTRY pLink;

	DebugPrintMsg("Entering PhyMemUnload");

	//free resources
	pLink=PopEntryList(&lstMapInfo);
	while(pLink)
	{
		pMapInfo=CONTAINING_RECORD(pLink, MAPINFO, link);

		MmUnmapLockedPages(pMapInfo->pvu, pMapInfo->pMdl); 
		IoFreeMdl(pMapInfo->pMdl);
		MmUnmapIoSpace(pMapInfo->pvk, pMapInfo->memSize);

		ExFreePool(pMapInfo);

		pLink=PopEntryList(&lstMapInfo);
	}

	if (busInterface && busInterface->InterfaceDereference)
	{
		(*busInterface->InterfaceDereference)(busInterface->Context);

		ExFreePool(busInterface);
	}

	RtlInitUnicodeString(&DeviceLinkU, L"\\DosDevices\\PhyMem");

	ntStatus=IoDeleteSymbolicLink(&DeviceLinkU);

	if (NT_SUCCESS(ntStatus))
	{
		IoDeleteDevice(dro->DeviceObject);
	}
	else
	{
		DebugPrintMsg("Error: IoDeleteSymbolicLink failed");
	}

	DebugPrintMsg("Leaving PhyMemUnload");

	DebugPrintClose();
}

//prepare to get bus interface
static NTSTATUS PreGetBus()
{
	NTSTATUS ntStatus;
	UNICODE_STRING pcifidoNameU;

	ntStatus=STATUS_SUCCESS;

	//get pci filter driver do
	if (pcifido==NULL)
	{
		RtlInitUnicodeString(&pcifidoNameU, L"\\Device\\PhyMemPCIFilter");

		ntStatus=IoGetDeviceObjectPointer(&pcifidoNameU,
										  FILE_READ_DATA|FILE_WRITE_DATA,
										  &pcifo,
										  &pcifido);

		if (NT_SUCCESS(ntStatus))
		{
			DebugPrint("Got pci filter device object: 0x%x", pcifido);
		}
		else
		{
			DebugPrint("Get pci filter device object failed, code=0x%x", ntStatus);

			return STATUS_UNSUCCESSFUL;
		}
	}

	//get bus interface
	if (busInterface->ReadConfig==NULL)
	{
		ntStatus=GetBusInterface(pcifido, busInterface);

		if (NT_SUCCESS(ntStatus))
		{
			DebugPrint("Got pci bus filter driver interface");
		}
		else
		{
			DebugPrint("Get pci bus driver interface failed, code=0x%x", ntStatus);
		}
	}

	return ntStatus;
}

//read pci configuration
static NTSTATUS ReadWriteConfig(PIRP irp, PPHYMEM_PCI pPci, BOOLEAN isRead)
{
	NTSTATUS ntStatus;

	//get pci filter driver interface
	ntStatus=PreGetBus();

	if (NT_SUCCESS(ntStatus))
	{
		PVOID pValue;

		//get out buffer kernel address
		pValue=(PVOID)MmGetSystemAddressForMdlSafe(irp->MdlAddress,
			NormalPagePriority);

		if (pValue)
		{
			PCI_SLOT_NUMBER slot;
			ULONG ulRet;

			slot.u.AsULONG=0;
			slot.u.bits.DeviceNumber=pPci->dwDevNum;
			slot.u.bits.FunctionNumber=pPci->dwFuncNum;

			if (isRead)
				ulRet=(*busInterface->ReadConfig)(busInterface->Context,	//context
												  (UCHAR)pPci->dwBusNum,	//busoffset
												  slot.u.AsULONG,			//slot
												  pValue,					//buffer
												  pPci->dwRegOff,			//offset
												  pPci->dwBytes);			//length

			else
				ulRet=(*busInterface->WriteConfig)(busInterface->Context,	//context
												   (UCHAR)pPci->dwBusNum,	//busoffset
												   slot.u.AsULONG,			//slot
												   pValue,					//buffer
												   pPci->dwRegOff,			//offset
												   pPci->dwBytes);			//length

			if (ulRet==pPci->dwBytes)
			{
				ntStatus=STATUS_SUCCESS;

				if (isRead)
					DebugPrint("Read %d bytes from pci config space", ulRet);
				else
					DebugPrint("Write %d bytes to pci config space", ulRet);
			}
			else
				ntStatus=STATUS_UNSUCCESSFUL;
		}
		else
			ntStatus=STATUS_INVALID_PARAMETER;
	}

	return ntStatus;
}