/*++

Copyright (c) 1993  Microsoft Corporation

Module Name:

    mapmem.c

Abstract:

    A simple driver sample which shows how to map physical memory
    into a user-mode process's adrress space using the
    Zw*MapViewOfSection APIs.

Environment:

    kernel mode only

Notes:

    For the sake of simplicity this sample does not attempt to
    recognize resource conflicts with other drivers/devices. A
    real-world driver would call IoReportResource usage to
    determine whether or not the resource is available, and if
    so, register the resource under it's name.

Revision History:

--*/


#include "ntddk.h"
#include "mapmem.h"
#include "stdarg.h"



NTSTATUS
MapMemDispatch(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    );

VOID
MapMemUnload(
    IN PDRIVER_OBJECT DriverObject
    );

NTSTATUS
MapMemMapTheMemory(
    IN PDEVICE_OBJECT DeviceObject,
    IN OUT PVOID      ioBuffer,
    IN ULONG          inputBufferLength,
    IN ULONG          outputBufferLength
    );



#if DBG
#define MapMemKdPrint(arg) DbgPrint arg
#else
#define MapMemKdPrint(arg)
#endif



NTSTATUS
DriverEntry(
    IN PDRIVER_OBJECT  DriverObject,
    IN PUNICODE_STRING RegistryPath
    )
/*++

Routine Description:

    Installable driver initialization entry point.
    This entry point is called directly by the I/O system.

Arguments:

    DriverObject - pointer to the driver object

    RegistryPath - pointer to a unicode string representing the path
                   to driver-specific key in the registry

Return Value:

    STATUS_SUCCESS if successful,
    STATUS_UNSUCCESSFUL otherwise

--*/
{

    PDEVICE_OBJECT deviceObject = NULL;
    NTSTATUS       ntStatus;
    WCHAR          deviceNameBuffer[] = L"\\Device\\MapMem";
    UNICODE_STRING deviceNameUnicodeString;
    WCHAR          deviceLinkBuffer[] = L"\\DosDevices\\MAPMEM";
    UNICODE_STRING deviceLinkUnicodeString;



    MapMemKdPrint (("MAPMEM.SYS: entering DriverEntry\n"));


    //
    // Create an EXCLUSIVE device object (only 1 thread at a time
    // can make requests to this device)
    //

    RtlInitUnicodeString (&deviceNameUnicodeString,
                          deviceNameBuffer);

    ntStatus = IoCreateDevice (DriverObject,
                               0,
                               &deviceNameUnicodeString,
                               FILE_DEVICE_MAPMEM,
                               0,
                               TRUE,
                               &deviceObject
                               );

    if (NT_SUCCESS(ntStatus))
    {
        //
        // Create dispatch points for device control, create, close.
        //

        DriverObject->MajorFunction[IRP_MJ_CREATE]         =
        DriverObject->MajorFunction[IRP_MJ_CLOSE]          =
        DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = MapMemDispatch;
        DriverObject->DriverUnload                         = MapMemUnload;



        //
        // Create a symbolic link, e.g. a name that a Win32 app can specify
        // to open the device
        //

        RtlInitUnicodeString(&deviceLinkUnicodeString,
                             deviceLinkBuffer);

        ntStatus = IoCreateSymbolicLink (&deviceLinkUnicodeString,
                                         &deviceNameUnicodeString);

        if (!NT_SUCCESS(ntStatus))
        {
            //
            // Symbolic link creation failed- note this & then delete the
            // device object (it's useless if a Win32 app can't get at it).
            //

            MapMemKdPrint (("MAPMEM.SYS: IoCreateSymbolicLink failed\n"));

            IoDeleteDevice (deviceObject);
        }
    }
    else
    {
        MapMemKdPrint (("MAPMEM.SYS: IoCreateDevice failed\n"));
    }

    return ntStatus;
}



NTSTATUS
MapMemDispatch(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    )
/*++

Routine Description:

    Process the IRPs sent to this device.

Arguments:

    DeviceObject - pointer to a device object

    Irp          - pointer to an I/O Request Packet

Return Value:


--*/
{
    PIO_STACK_LOCATION irpStack;
    PVOID              ioBuffer;
    ULONG              inputBufferLength;
    ULONG              outputBufferLength;
    ULONG              ioControlCode;
    NTSTATUS           ntStatus;


    //
    // Init to default settings- we only expect 1 type of
    //     IOCTL to roll through here, all others an error.
    //

    Irp->IoStatus.Status      = STATUS_SUCCESS;
    Irp->IoStatus.Information = 0;


    //
    // Get a pointer to the current location in the Irp. This is where
    //     the function codes and parameters are located.
    //

    irpStack = IoGetCurrentIrpStackLocation(Irp);


    //
    // Get the pointer to the input/output buffer and it's length
    //

    ioBuffer           = Irp->AssociatedIrp.SystemBuffer;
    inputBufferLength  = irpStack->Parameters.DeviceIoControl.InputBufferLength;
    outputBufferLength = irpStack->Parameters.DeviceIoControl.OutputBufferLength;


    switch (irpStack->MajorFunction)
    {
    case IRP_MJ_CREATE:

        MapMemKdPrint (("MAPMEM.SYS: IRP_MJ_CREATE\n"));

        break;



    case IRP_MJ_CLOSE:

        MapMemKdPrint (("MAPMEM.SYS: IRP_MJ_CLOSE\n"));

        break;



    case IRP_MJ_DEVICE_CONTROL:

        ioControlCode = irpStack->Parameters.DeviceIoControl.IoControlCode;

        switch (ioControlCode)
        {
        case IOCTL_MAPMEM_MAP_USER_PHYSICAL_MEMORY:

            Irp->IoStatus.Status = MapMemMapTheMemory (DeviceObject,
                                                       ioBuffer,
                                                       inputBufferLength,
                                                       outputBufferLength
                                                       );

            if (NT_SUCCESS(Irp->IoStatus.Status))
            {
                //
                // Success! Set the following to sizeof(PVOID) to
                //     indicate we're passing valid data back.
                //

                Irp->IoStatus.Information = sizeof(PVOID);

                MapMemKdPrint (("MAPMEM.SYS: memory successfully mapped\n"));
            }

            else
            {
                Irp->IoStatus.Status = STATUS_INVALID_PARAMETER;

                MapMemKdPrint (("MAPMEM.SYS: memory map failed :(\n"));
            }

            break;



        case IOCTL_MAPMEM_UNMAP_USER_PHYSICAL_MEMORY:

            if (inputBufferLength >= sizeof(PVOID))
            {
                Irp->IoStatus.Status = ZwUnmapViewOfSection ((HANDLE) -1,
                                                             *((PVOID *) ioBuffer)
                                                             );

                MapMemKdPrint (("MAPMEM.SYS: memory successfully unmapped\n"));
            }
            else
            {
                Irp->IoStatus.Status = STATUS_INSUFFICIENT_RESOURCES;

                MapMemKdPrint (("MAPMEM.SYS: ZwUnmapViewOfSection failed\n"));
            }

            break;



        default:

            MapMemKdPrint (("MAPMEM.SYS: unknown IRP_MJ_DEVICE_CONTROL\n"));

            Irp->IoStatus.Status = STATUS_INVALID_PARAMETER;

            break;

        }

        break;
    }


    //
    // DON'T get cute and try to use the status field of
    // the irp in the return status.  That IRP IS GONE as
    // soon as you call IoCompleteRequest.
    //

    ntStatus = Irp->IoStatus.Status;

    IoCompleteRequest(Irp,
                      IO_NO_INCREMENT);


    //
    // We never have pending operation so always return the status code.
    //

    return ntStatus;
}



VOID
MapMemUnload(
    IN PDRIVER_OBJECT DriverObject
    )
/*++

Routine Description:

    Just delete the associated device & return.

Arguments:

    DriverObject - pointer to a driver object

Return Value:


--*/
{
    WCHAR                  deviceLinkBuffer[]  = L"\\DosDevices\\MAPMEM";
    UNICODE_STRING         deviceLinkUnicodeString;



    //
    // Free any resources
    //



    //
    // Delete the symbolic link
    //

    RtlInitUnicodeString (&deviceLinkUnicodeString,
                          deviceLinkBuffer
                          );

    IoDeleteSymbolicLink (&deviceLinkUnicodeString);



    //
    // Delete the device object
    //

    MapMemKdPrint (("MAPMEM.SYS: unloading\n"));

    IoDeleteDevice (DriverObject->DeviceObject);
}



NTSTATUS
MapMemMapTheMemory(
    IN PDEVICE_OBJECT DeviceObject,
    IN OUT PVOID      IoBuffer,
    IN ULONG          InputBufferLength,
    IN ULONG          OutputBufferLength
    )
/*++

Routine Description:

    Given a physical address, maps this address into a user mode process's
    address space

Arguments:

    DeviceObject       - pointer to a device object

    IoBuffer           - pointer to the I/O buffer

    InputBufferLength  - input buffer length

    OutputBufferLength - output buffer length

Return Value:

    STATUS_SUCCESS if sucessful, otherwise
    STATUS_UNSUCCESSFUL,
    STATUS_INSUFFICIENT_RESOURCES,
    (other STATUS_* as returned by kernel APIs)

--*/
{

    PPHYSICAL_MEMORY_INFO ppmi = (PPHYSICAL_MEMORY_INFO) IoBuffer;

    INTERFACE_TYPE     interfaceType;
    ULONG              busNumber;
    PHYSICAL_ADDRESS   physicalAddress;
    ULONG              length;
    UNICODE_STRING     physicalMemoryUnicodeString;
    OBJECT_ATTRIBUTES  objectAttributes;
    HANDLE             physicalMemoryHandle  = NULL;
    PVOID              PhysicalMemorySection = NULL;
    ULONG              inIoSpace, inIoSpace2;
    NTSTATUS           ntStatus;
    PHYSICAL_ADDRESS   physicalAddressBase;
    PHYSICAL_ADDRESS   physicalAddressEnd;
    PHYSICAL_ADDRESS   viewBase;
    PHYSICAL_ADDRESS   mappedLength;
    BOOLEAN            translateBaseAddress;
    BOOLEAN            translateEndAddress;
    PVOID              virtualAddress;



    if ( ( InputBufferLength  < sizeof (PHYSICAL_MEMORY_INFO) ) ||
         ( OutputBufferLength < sizeof (PVOID) ) )
    {
       MapMemKdPrint (("MAPMEM.SYS: Insufficient input or output buffer\n"));

       ntStatus = STATUS_INSUFFICIENT_RESOURCES;

       goto done;
    }

    interfaceType          = ppmi->InterfaceType;
    busNumber              = ppmi->BusNumber;
    physicalAddress        = ppmi->BusAddress;
    inIoSpace = inIoSpace2 = ppmi->AddressSpace;
    length                 = ppmi->Length;


    //
    // Get a pointer to physical memory...
    //
    // - Create the name
    // - Initialize the data to find the object
    // - Open a handle to the oject and check the status
    // - Get a pointer to the object
    // - Free the handle
    //

    RtlInitUnicodeString (&physicalMemoryUnicodeString,
                          L"\\Device\\PhysicalMemory");

    InitializeObjectAttributes (&objectAttributes,
                                &physicalMemoryUnicodeString,
                                OBJ_CASE_INSENSITIVE,
                                (HANDLE) NULL,
                                (PSECURITY_DESCRIPTOR) NULL);

    ntStatus = ZwOpenSection (&physicalMemoryHandle,
                              SECTION_ALL_ACCESS,
                              &objectAttributes);

    if (!NT_SUCCESS(ntStatus))
    {
        MapMemKdPrint (("MAPMEM.SYS: ZwOpenSection failed\n"));

        goto done;
    }

    ntStatus = ObReferenceObjectByHandle (physicalMemoryHandle,
                                          SECTION_ALL_ACCESS,
                                          (POBJECT_TYPE) NULL,
                                          KernelMode,
                                          &PhysicalMemorySection,
                                          (POBJECT_HANDLE_INFORMATION) NULL);

    if (!NT_SUCCESS(ntStatus))
    {
        MapMemKdPrint (("MAPMEM.SYS: ObReferenceObjectByHandle failed\n"));

        goto close_handle;
    }


    //
    // Initialize the physical addresses that will be translated
    //

    physicalAddressEnd = RtlLargeIntegerAdd (physicalAddress,
                                             RtlConvertUlongToLargeInteger(
                                             length));

    //
    // Translate the physical addresses.
    //

    translateBaseAddress =
        HalTranslateBusAddress (interfaceType,
                                busNumber,
                                physicalAddress,
                                &inIoSpace,
                                &physicalAddressBase);

    translateEndAddress =
        HalTranslateBusAddress (interfaceType,
                                busNumber,
                                physicalAddressEnd,
                                &inIoSpace2,
                                &physicalAddressEnd);

    if ( !(translateBaseAddress && translateEndAddress) )
    {
        MapMemKdPrint (("MAPMEM.SYS: HalTranslatephysicalAddress failed\n"));

        ntStatus = STATUS_UNSUCCESSFUL;

        goto close_handle;
    }

    //
    // Calculate the length of the memory to be mapped
    //

    mappedLength = RtlLargeIntegerSubtract (physicalAddressEnd,
                                            physicalAddressBase);


    //
    // If the mappedlength is zero, somthing very weird happened in the HAL
    // since the Length was checked against zero.
    //

    if (mappedLength.LowPart == 0)
    {
        MapMemKdPrint (("MAPMEM.SYS: mappedLength.LowPart == 0\n"));

        ntStatus = STATUS_UNSUCCESSFUL;

        goto close_handle;
    }

    length = mappedLength.LowPart;


    //
    // If the address is in io space, just return the address, otherwise
    // go through the mapping mechanism
    //

    if (inIoSpace)
    {
        *((PVOID *) IoBuffer) = (PVOID) physicalAddressBase.LowPart;
    }

    else
    {
        //
        // initialize view base that will receive the physical mapped
        // address after the MapViewOfSection call.
        //

        viewBase = physicalAddressBase;


        //
        // Let ZwMapViewOfSection pick an address
        //

        virtualAddress = NULL;



        //
        // Map the section
        //

        ntStatus = ZwMapViewOfSection (physicalMemoryHandle,
                                       (HANDLE) -1,
                                       &virtualAddress,
                                       0L,
                                       length,
                                       &viewBase,
                                       &length,
                                       ViewShare,
                                       0,
                                       PAGE_READWRITE | PAGE_NOCACHE);

        if (!NT_SUCCESS(ntStatus))
        {
            MapMemKdPrint (("MAPMEM.SYS: ZwMapViewOfSection failed\n"));

            goto close_handle;
        }

        //
        // Mapping the section above rounded the physical address down to the
        // nearest 64 K boundary. Now return a virtual address that sits where
        // we wnat by adding in the offset from the beginning of the section.
        //


        (ULONG) virtualAddress += (ULONG)physicalAddressBase.LowPart -
                                  (ULONG)viewBase.LowPart;

        *((PVOID *) IoBuffer) = virtualAddress;

    }

    ntStatus = STATUS_SUCCESS;



close_handle:

    ZwClose (physicalMemoryHandle);



done:

    return ntStatus;
}
