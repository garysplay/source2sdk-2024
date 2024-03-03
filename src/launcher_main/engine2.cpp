#include "engine2.h"
#include "csteam3client.h"  // Include necessary headers

void MinidumpLog(const char* format, ...);  // Forward declaration for MinidumpLog
void RegisterAssertionFailureListener(DWORD* listener);  // Forward declaration for RegisterAssertionFailureListener
void SetDefaultMiniDumpHandler(DWORD preHandlerCallback, char value);  // Forward declaration for SetDefaultMiniDumpHandler
unsigned __int8 LoggingSystem_IsChannelEnabled(unsigned int channel, DWORD param);  // Forward declaration for LoggingSystem_IsChannelEnabled
void LoggingSystem_Log(unsigned int channel, DWORD param, const char* format, ...);  // Forward declaration for LoggingSystem_Log
void Tier0GenericMiniDumpHandler_SetOptions(DWORD, DWORD);  // Forward declaration for Tier0GenericMiniDumpHandler_SetOptions
void Tier0GenericMiniDumpHandler_SetPreHandlerCallback(DWORD preHandlerCallback);  // Forward declaration for Tier0GenericMiniDumpHandler_SetPreHandlerCallback

__int64 __fastcall sub_1801D69F0(int a1, int a2, __int64 a3, int a4, __int64 a5, __int64 a6) {
    // Implement sub_1801D69F0 if it's not provided
    return 0;
}

void CThreadLocalScope_CThreadLocalScope(char* scope, DWORD param1, DWORD param2);  // Forward declaration for CThreadLocalScope_CThreadLocalScope
void CThreadLocalScope___CThreadLocalScope(char* scope);  // Forward declaration for CThreadLocalScope___CThreadLocalScope
unsigned int CommandLine();  // Forward declaration for CommandLine
void Plat_AttachDebuggerToProcess(char debugger, DWORD param);  // Forward declaration for Plat_AttachDebuggerToProcess
void MiniDumpCommentEnsureOSDescription();  // Forward declaration for MiniDumpCommentEnsureOSDescription
void MinidumpLog(const char* format, ...);  // Forward declaration for MinidumpLog
unsigned int LoggingSystem_IsChannelEnabled(unsigned int channel, DWORD param);  // Forward declaration for LoggingSystem_IsChannelEnabled
void LoggingSystem_Log(unsigned int channel, DWORD param, const char* format, ...);  // Forward declaration for LoggingSystem_Log

// Global variables
extern DWORD* g_pMemAlloc;
extern DWORD off_180519BE0;
extern DWORD dword_180578B04;
extern DWORD word_180515B34;

__int64 __fastcall Source2Main(int a1, int a2, __int64 a3, int a4, __int64 a5, __int64 a6) {
    char v12; // bl
    unsigned __int8 v14; // al
    DWORD v17; // rdx
    unsigned int v19; // ebx
    char v21[48]; // Local variable

    CThreadLocalScope_CThreadLocalScope(v21, 0i64, 0);
    CommandLine();
    (*(void(__fastcall**)(__int64, __int64))(*(DWORD*)CommandLine() + 16i64))(CommandLine(), a3);
    CommandLine();
    v12 = (*(__int64(__fastcall**)(__int64, const char*))(*(DWORD*)CommandLine() + 32i64))(CommandLine(), "-attachtodebugger");
    CommandLine();
    v14 = (*(__int64(__fastcall**)(__int64, const char*))(*(DWORD*)CommandLine() + 32i64))(CommandLine(), "-breakimmediately");
    if (v12 || v14)
        Plat_AttachDebuggerToProcess(v14, 0i64);
    MiniDumpCommentEnsureOSDescription();
    CommandLine();
    if (!(*(unsigned int(__fastcall**)(__int64, const char*, DWORD))(*(DWORD*)CommandLine() + 48i64))(
        CommandLine(),
        "-nominidumps",
        0i64))
    {
        MinidumpLog("Overriding minidump handler with Engine2MinidumpFunction\n");
        Tier0GenericMiniDumpHandler_SetOptions(0i64, 1i64);
        Tier0GenericMiniDumpHandler_SetPreHandlerCallback(sub_1801D9660);
        CommandLine();
        if (!(*(unsigned int(__fastcall**)(__int64, const char*, DWORD))(*(DWORD*)CommandLine() + 48i64))(
            CommandLine(),
            "-nobreakpad",
            0i64))
        {
            LOBYTE(v17) = 1;
            SetDefaultMiniDumpHandler(sub_1801D9690, v17);
            CommandLine();
            if (!(*(unsigned __int8(__fastcall**)(__int64, const char*))(*(DWORD*)CommandLine() + 32i64))(
                CommandLine(),
                "-nopassiveasserts"))
                RegisterAssertionFailureListener(&off_180519BE0);
        }
    }
    if ((*(unsigned __int8(__fastcall**)(DWORD))(*g_pMemAlloc + 288i64))(g_pMemAlloc))
        (*(void(__fastcall**)(DWORD, const char*))(*g_pMemAlloc + 152i64))(g_pMemAlloc, "Engine_Startup");
    MinidumpLog(
        "MINIDUMP_WRAP_CODE: Entering [%s(%u):%s:]\n",
        "C:\\buildworker\\csgo_rel_win64\\build\\src\\engine2\\engine2.cpp",
        6278i64,
        "Source2Main");
    MinidumpLog("MINIDUMP_WRAP_CODE: Wrapped execution\n");
    v19 = sub_1801D69F0(a1, a2, a3, a4, a5, a6);
    if ((_BYTE)word_180515B34) {
        if ((unsigned __int8)LoggingSystem_IsChannelEnabled((unsigned int)dword_180578B04, 2i64))
            LoggingSystem_Log((unsigned int)dword_180578B04, 2i64, "CSteam3Client::Shutdown\n");
        LOBYTE(word_180515B34) = 0;
        SteamAPI_Shutdown();
    }
    if ((*(unsigned __int8(__fastcall**)(DWORD))(*g_pMemAlloc + 288i64))(g_pMemAlloc))
        (*(void(__fastcall**)(DWORD, const char*))(*g_pMemAlloc + 152i64))(g_pMemAlloc, "Engine_Shutdown");
    CThreadLocalScope___CThreadLocalScope(v21);
    return v19;
}
