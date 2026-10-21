{
    files = {
        [[build\.objs\probe_min\windows\x64\release\src\probe_min.cpp.obj]]
    },
    values = {
        [[Y:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.50.35717\bin\HostX64\x64\link.exe]],
        {
            "-nologo",
            "-dynamicbase",
            "-nxcompat",
            "-machine:x64",
            [[-libpath:Y:\Program Files (x86)\Windows Kits\10\Lib\10.0.26100.0\km\x64]],
            [[-libpath:Y:\Program Files (x86)\Windows Kits\10\Lib\wdf\kmdf\x64\1.11]],
            "/opt:ref",
            "/opt:icf",
            "ntoskrnl.lib",
            "hal.lib",
            "wmilib.lib",
            "ntstrsafe.lib",
            "BufferOverflowK.lib",
            "WdfDriverEntry.lib",
            "-kernel",
            "-driver",
            "-nodefaultlib",
            "-entry:GsDriverEntry",
            "/SUBSYSTEM:NATIVE,10.00"
        }
    }
}