#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <string>
#include <thread>

DWORD GetPIDByName(const std::wstring& processName) {
    DWORD pid = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 pe;
        pe.dwSize = sizeof(PROCESSENTRY32);
        if (Process32First(hSnapshot, &pe)) {
            do {
                if (_wcsicmp(processName.c_str(), pe.szExeFile) == 0) {
                    pid = pe.th32ProcessID;
                    break;
                }
            } while (Process32Next(hSnapshot, &pe));
        }
        CloseHandle(hSnapshot);
    }
    return pid;
}

struct EnumData {
    DWORD pid;
    HWND hwnd;
};

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    EnumData* data = (EnumData*)lParam;
    DWORD procId = 0;
    GetWindowThreadProcessId(hwnd, &procId);
    if (procId == data->pid && IsWindowVisible(hwnd)) {
        data->hwnd = hwnd;
        return FALSE;
    }
    return TRUE;
}

HWND GetWindowOfProcess(DWORD pid) {
    EnumData data{ pid, NULL };
    EnumWindows(EnumWindowsProc, (LPARAM)&data);
    return data.hwnd;
}

int main() {
    std::wstring processName;
    std::wstring newTitle;

    std::wcout << L"Enter the process name (example: Procmon.exe): ";
    std::getline(std::wcin, processName);

    DWORD pid = GetPIDByName(processName);
    if (pid == 0) {
        std::wcout << L"Process not found!" << std::endl;
        return 1;
    }

    std::wcout << L"Found PID: " << pid << std::endl;

    HWND hwnd = GetWindowOfProcess(pid);
    if (!hwnd) {
        std::wcout << L"No window found for this process." << std::endl;
        return 1;
    }

    std::wcout << L"Enter the new window title: ";
    std::getline(std::wcin, newTitle);

        SetWindowTextW(hwnd, newTitle.c_str());
        printf("Renamed");
        system("pause");
    return 0;
}
