#include <ntddk.h>

#define PROBE_DEVICE_NAME L"\\Device\\BlookProbe"
#define PROBE_SYMLINK_NAME L"\\DosDevices\\BlookProbe"
#define PROBE_IOCTL_MAGIC 0xB1000001u

extern "C" NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {
    UNREFERENCED_PARAMETER(RegistryPath);
    UNICODE_STRING deviceName, symlinkName;
    PDEVICE_OBJECT deviceObject = nullptr;
    RtlInitUnicodeString(&deviceName, PROBE_DEVICE_NAME);
    NTSTATUS status = IoCreateDevice(DriverObject, 0, &deviceName, FILE_DEVICE_UNKNOWN, 0, FALSE, &deviceObject);
    if (!NT_SUCCESS(status)) return status;
    RtlInitUnicodeString(&symlinkName, PROBE_SYMLINK_NAME);
    status = IoCreateSymbolicLink(&symlinkName, &deviceName);
    if (!NT_SUCCESS(status)) { IoDeleteDevice(deviceObject); return status; }
    DriverObject->Flags |= DO_BUFFERED_IO;
    DriverObject->DriverUnload = [](PDRIVER_OBJECT DriverObject) {
        UNICODE_STRING symlinkName;
        RtlInitUnicodeString(&symlinkName, PROBE_SYMLINK_NAME);
        IoDeleteSymbolicLink(&symlinkName);
        IoDeleteDevice(DriverObject->DeviceObject);
        DbgPrint("[blook-probe] unloaded\n");
    };
    DriverObject->MajorFunction[IRP_MJ_CREATE] = [](PDEVICE_OBJECT, PIRP Irp) -> NTSTATUS {
        Irp->IoStatus.Status = STATUS_SUCCESS; Irp->IoStatus.Information = 0; IoCompleteRequest(Irp, IO_NO_INCREMENT); return STATUS_SUCCESS; };
    DriverObject->MajorFunction[IRP_MJ_CLOSE] = DriverObject->MajorFunction[IRP_MJ_CREATE];
    DriverObject->MajorFunction[IRP_MJ_CLEANUP] = DriverObject->MajorFunction[IRP_MJ_CREATE];
    DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = [](PDEVICE_OBJECT, PIRP Irp) -> NTSTATUS {
        PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
        if (stack->Parameters.DeviceIoControl.IoControlCode == PROBE_IOCTL_MAGIC) {
            *reinterpret_cast<ULONG*>(Irp->AssociatedIrp.SystemBuffer) = 0x42454F52u; /* 'ROBE' */
            Irp->IoStatus.Information = sizeof(ULONG);
            Irp->IoStatus.Status = STATUS_SUCCESS;
        } else { Irp->IoStatus.Status = STATUS_INVALID_DEVICE_REQUEST; }
        IoCompleteRequest(Irp, IO_NO_INCREMENT); return Irp->IoStatus.Status; };
    DbgPrint("[blook-probe] loaded: \\Device\\BlookProbe\n");
    return STATUS_SUCCESS;
}
