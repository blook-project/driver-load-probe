#include <windows.h>
#include <cstdio>
int main() {
    HANDLE h = CreateFileW(L"\\\\.\\BlookProbe", GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, 0, nullptr);
    if (h == INVALID_HANDLE_VALUE) { std::printf("OPEN_FAILED err=%lu\n", GetLastError()); return 1; }
    DWORD out = 0, bytes = 0;
    BOOL ok = DeviceIoControl(h, 0xB1000001u, nullptr, 0, &out, sizeof(out), &bytes, nullptr);
    std::printf("IOCTL_%s magic=0x%08X bytes=%lu\n", ok ? "OK" : "FAIL", out, bytes);
    CloseHandle(h);
    return ok && out == 0x42454F52u ? 0 : 2;
}
