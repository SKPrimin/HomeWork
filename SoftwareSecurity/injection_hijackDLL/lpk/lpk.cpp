#include <Windows.h>
#include "pch.h"
#include <stdio.h>

// µ¼³öº¯Êý
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


DWORD WINAPI ThreadWorking(LPVOID lpParameters)
{
	MessageBox(NULL, TEXT("Hello World"), TEXT("Pratice"), MB_OK);
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