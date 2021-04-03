/*++
access pci bus configuration
--*/

#include <ntddk.h>
#include <wdmguid.h>
#include "DebugPrint.h"

//gets the bus interface standard information from the PDO.
NTSTATUS GetBusInterface(IN PDEVICE_OBJECT pcifido,
	OUT PPCI_BUS_INTERFACE_STANDARD	busInterface)
{
	KEVENT event;
	NTSTATUS ntStatus;
	PIRP irp;
	IO_STATUS_BLOCK ioStatus;
	PIO_STACK_LOCATION irpStack;

	if (pcifido==NULL)
		return STATUS_UNSUCCESSFUL;

	KeInitializeEvent(&event, NotificationEvent, FALSE);

	irp=IoBuildSynchronousFsdRequest(IRP_MJ_PNP,
									 pcifido,
									 NULL,
									 0,
									 NULL,
									 &event,
									 &ioStatus);

	if (irp==NULL)
	{
		return STATUS_INSUFFICIENT_RESOURCES;
	}

	irpStack=IoGetNextIrpStackLocation(irp);
	irpStack->MinorFunction=IRP_MN_QUERY_INTERFACE;
	irpStack->Parameters.QueryInterface.InterfaceType=(LPGUID)&GUID_PCI_BUS_INTERFACE_STANDARD;
	irpStack->Parameters.QueryInterface.Size=sizeof(PCI_BUS_INTERFACE_STANDARD);
	irpStack->Parameters.QueryInterface.Version=PCI_BUS_INTERFACE_STANDARD_VERSION;
	irpStack->Parameters.QueryInterface.Interface=(PINTERFACE)busInterface;
	irpStack->Parameters.QueryInterface.InterfaceSpecificData=NULL;

	//initialize the status to error in case the bus driver does not 
	//set it correctly.
	irp->IoStatus.Status=STATUS_NOT_SUPPORTED ;

	ntStatus=IoCallDriver(pcifido, irp);

	if (ntStatus==STATUS_PENDING)
	{
		KeWaitForSingleObject(&event, Executive, KernelMode, FALSE, NULL);

		ntStatus=ioStatus.Status;
	}

	return ntStatus;
}
