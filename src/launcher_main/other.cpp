#include <cstdio>

void sub_140074C30()
{
    FILE* v0; // rax
    FILE* v1; // rax
    __int64 v2; // rdx

    if (!byte_15BF6BD50)
    {
        byte_15BF6BD50 = 1;
        v0 = _acrt_iob_func(1u);
        setvbuf(v0, 0i64, 4, 0i64);
        v1 = _acrt_iob_func(2u);
        setvbuf(v1, 0i64, 4, 0i64);
        LOBYTE(v2) = 1;
        LoggingSystem_PushLoggingState(0i64, v2);
        LoggingSystem_RegisterLoggingListener(&qword_15BF6B8A0);
        LoggingSystem_RegisterLoggingListener(&qword_15BF6B8C0);
    }
}

__int64 __fastcall sub_140074FB0(int a1, int a2, __int64 a3, int a4)
{
    __int64 result; // rax

    result = sub_140079640(a1, a2, 0, a4, 0);
    if (!qword_15BF6D6E8)
        sub_14007D500("CmdLib_InitFileSystem failed.");
    return result;
}

__int64 __fastcall sub_140084780(__int64 a1, __int64 a2, __int64 a3, unsigned int a4)
{
    float* v5; // rdi
    __int64 v6; // rbx
    __int64 v7; // rdx
    __int64 v8; // rcx
    __int64 v9; // r8
    float v10; // xmm0_4
    __int64 result; // rax

    if (!byte_15BF6E2E8)
    {
        v5 = (float*)&unk_15BF6E2F0;
        v6 = 0i64;
        byte_15BF6E2E8 = 1;
        do
        {
            v10 = sub_140084940();
            ++v6;
            *v5++ = v10;
        } while (v6 != 256);
        sub_14009F8F0(v8, v7, v9, a4);
        return sub_14009FD30(826366246i64);
    }
    return result;
}
char* __fastcall sub_140074DF0(char* Source)
{
    int v1; // eax
    __int64 v4; // rdx

    v1 = (unsigned __int8)*Source;
    if (v1 == 47 || v1 == 92 || Source[1] == 58)
    {
        sub_140098980(byte_15BF6BD60, Source, 1024i64);
    }
    else
    {
        Plat_getwd(byte_15BF6BD60, 1024i64);
        sub_140098B10(byte_15BF6BD60, "/");
        LOBYTE(v4) = 92;
        sub_140099080(byte_15BF6BD60, v4);
        sub_140098B10(byte_15BF6BD60, Source);
    }
    return byte_15BF6BD60;
}