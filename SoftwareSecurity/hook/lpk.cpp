#include <Windows.h>
#include "pch.h"
#include <stdio.h>

// 导出函数
#pragma comment(linker, "/EXPORT:LpkTabbedTextOut=lpkOrg.LpkTabbedTextOut,@1")
#pragma comment(linker, "/EXPORT:LpkDllInitialize=lpkOrg.LpkDllInitialize,@2")
#pragma comment(linker, "/EXPORT:LpkDrawTextEx=lpkOrg.LpkDrawTextEx,@3")
#pragma comment(linker, "/EXPORT:LpkPSMTextOut=lpkOrg.LpkPSMTextOut,@9")
#pragma comment(linker, "/EXPORT:LpkUseGDIWidthCache=lpkOrg.LpkUseGDIWidthCache,@10")
#pragma comment(linker, "/EXPORT:LpkGetCharacterPlacement=lpkOrg.LpkGetCharacterPlacement,@6")
#pragma comment(linker, "/EXPORT:LpkGetTextExtentExPoint=lpkOrg.LpkGetTextExtentExPoint,@7")
#pragma comment(linker, "/EXPORT:LpkInitialize=lpkOrg.LpkInitialize,@8")
#pragma comment(linker, "/EXPORT:ftsWordBreak=lpkOrg.ftsWordBreak,@11")
#pragma comment(linker, "/EXPORT:LpkEditControl=lpkOrg.LpkEditControl,@4")
#pragma comment(linker, "/EXPORT:LpkExtTextOut=lpkOrg.LpkExtTextOut,@5")

unsigned long g_backPos = 0;
void _stdcall DoSomething(ULONG sid)
{
	TCHAR strText[16] = {0};
	wsprintf(strText, TEXT("%d"), sid);
	MessageBox(NULL, strText, TEXT("tips"), MB_OK);
}
_declspec(naked) void DetourFunction()
{
	_asm
	{
		push [esp + 8]
		call DoSomething

		add esp, 0xc
		push edi
		push dword ptr[ebp + 8]
		jmp g_backPos
	}
}

int InstallInlineHook()
{
	unsigned char nOriginalLen = 7; //被替换指令的长度
	HMODULE hMod = GetModuleHandle(NULL);
	unsigned long nHookPos = (unsigned long)hMod + 0x10CC; // Hook的目标地址
	g_backPos = nHookPos + nOriginalLen;
	unsigned char nHookCodeLen = 5;			// Hook指令的长度
	unsigned char chHookCodes[16] = {0xE9}; // JMP
	*((ULONG *)(chHookCodes + 1)) = (ULONG)DetourFunction - nHookPos - 5;
	memset(chHookCodes + nHookCodeLen, 0x90, sizeof(chHookCodes) - nHookCodeLen);
	ULONG nWrite = 0;
	HANDLE hProcess = GetCurrentProcess();
	int nRet = WriteProcessMemory(hProcess, (void *)nHookPos, (void *)chHookCodes, nOriginalLen, &nWrite);
	if (nRet)
		return 0;
	else
		return 1;
}
DWORD WINAPI ThreadWorking(LPVOID lpParameters)
{
	InstallInlineHook();
	return 0;
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, PVOID pvReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		CreateThread(NULL, 0, ThreadWorking, NULL, 0, NULL);
		DisableThreadLibraryCalls(hModule);
	}
	return TRUE;
}