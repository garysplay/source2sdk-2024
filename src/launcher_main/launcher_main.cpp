#include <WinSock2.h>
#include <Windows.h>
#include <Shlwapi.h>
#include "launcher_main.h"
#include <iostream>
#pragma comment(lib, "Shlwapi.lib")


// Global variable to store launch parameters
const char* launchParameters = nullptr;

typedef void(__fastcall* WinMainFunction)(HINSTANCE, HINSTANCE, LPSTR, DWORD, CHAR*, char*);

typedef void(__fastcall* WinMainFunction)(HINSTANCE, HINSTANCE, LPSTR, DWORD, CHAR*, char*);
FARPROC __fastcall LoadFunctionFromLibrary(LPSTR lpMultiByteStr, int cbMultiByte, LPCCH a3, LPCSTR lpProcName);
void LoadLaunchParameters();  // Function prototype

int main() {

    LoadLaunchParameters();

    HINSTANCE hInstance = GetModuleHandle(NULL);
    LPSTR lpCmdLine = GetCommandLineA();
    int nCmdShow = SW_SHOWDEFAULT;

    CHAR moduleName[272];
#ifdef _M_IX86
    WinMainFunction winMainFunc = (WinMainFunction)LoadFunctionFromLibrary(moduleName, 260, "launcher", "LauncherMain"); // Source 1
#elif defined(_M_X64)
    WinMainFunction winMainFunc = (WinMainFunction)LoadFunctionFromLibrary(moduleName, 260, "engine2", "Source2Main"); // Source 2
#endif
    if (!winMainFunc)
        return 1;
    const char* off_14001E008 = "csgo";

    winMainFunc(hInstance, NULL, lpCmdLine, static_cast<DWORD>(nCmdShow), moduleName, const_cast<char*>(off_14001E008));

    return 0;
}

void LoadLaunchParameters() {
    // Simulating loading launch parameters from settings
    launchParameters = " -dev -insecure -tools";
}

FARPROC __fastcall LoadFunctionFromLibrary(LPSTR lpMultiByteStr, int cbMultiByte, LPCCH a3, LPCSTR lpProcName) {
    WCHAR moduleName[MAX_PATH];
    WCHAR libFileName[MAX_PATH];
    WCHAR wideCharStr[MAX_PATH];
    CHAR text[1024];
    DWORD lastError;

    // Get the path of the current module
    if (!GetModuleFileNameW(nullptr, moduleName, MAX_PATH)) {
        MessageBoxA(nullptr, "Failed to locate the module path", "Launcher Error", 0);
        return nullptr;
    }

    // Extract the directory from the path
    PathRemoveFileSpecW(moduleName);

    // Convert the module path to multi-byte string
    if (!lpMultiByteStr || !WideCharToMultiByte(CP_UTF8, 0, moduleName, -1, const_cast<char*>(lpMultiByteStr), cbMultiByte, nullptr, nullptr)) {
        MessageBoxA(nullptr, "Unable to convert path to multi-byte string", "Launcher Error", 0);
        return nullptr;
    }


    // Convert the library name to wide-char string
    MultiByteToWideChar(CP_UTF8, 0, a3, -1, wideCharStr, MAX_PATH);

    // Construct the library file path
#ifdef _M_IX86
    swprintf(libFileName, MAX_PATH, L"%s\\bin\\%s.dll", moduleName, wideCharStr); // Source 1
#elif defined(_M_X64)
    swprintf(libFileName, MAX_PATH, L"%s\\%s.dll", moduleName, wideCharStr); // Source 2
#endif

    // Load the library
    HMODULE library = LoadLibraryExW(libFileName, nullptr, LOAD_WITH_ALTERED_SEARCH_PATH);
    if (!library) {
        lastError = GetLastError();
#ifdef _M_IX86
        MessageBoxA(nullptr, "Failed to load the launcher DLL", "Launcher Error", 0);
#elif defined(_M_X64)
        MessageBoxA(nullptr, "Failed to load the engine2 DLL", "Launcher Error", 0);
#endif

        LPVOID buffer;
        if (FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr, lastError, 0, (LPSTR)&buffer, 0, nullptr)) {
            swprintf_s(libFileName, MAX_PATH, L"%s\\%s.dll", moduleName, wideCharStr);
            MessageBoxA(nullptr, text, "Launcher Error", 0);
            LocalFree(buffer);
        }
        else {
            MessageBoxA(nullptr, "[Failed To Resolve Error Code.]", "Launcher Error", 0);
        }

        return nullptr;
    }

    // Get the address of the function
    FARPROC functionAddress = GetProcAddress(library, lpProcName);

    if (!functionAddress) {
        MessageBoxA(nullptr, "Failed to get the address of the function from the library", "Launcher Error", 0);
    }

    return functionAddress;
}
