#include <windows.h>
#include <stdio.h>

typedef struct _THREAD_PARAM
{
	FARPROC pFunc[2];		// LoadLibraryA(), GetProcAddress()
	char szBuf[4][128];		// "user32.dll", "MessageBoxA",  "text", "caption"
} THREAD_PARAM, * PTHREAD_PARAM;

typedef HMODULE(WINAPI* pfnLoadLibrary)(LPCSTR lpLibFileName);
typedef FARPROC(WINAPI* pfnGetProcAddress)(HMODULE hModule, LPCSTR lpProcName);
typedef int(WINAPI* pfnMsgBox)(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType);

BOOL SetPrivilege(LPCTSTR lpszPrivilege, BOOL bEnablePrivilege)
{
	HANDLE hToken;
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
	{
		printf("OpenProcessToken error:%d\n", GetLastError());
		return FALSE;
	}

	LUID luid;
	if (!LookupPrivilegeValue(NULL, lpszPrivilege, &luid))
	{
		printf("LookupPrivilegeValue error:%d\n", GetLastError());
		return FALSE;
	}

	TOKEN_PRIVILEGES NewState;
	NewState.PrivilegeCount = 1;
	NewState.Privileges[0].Luid = luid;
	if (bEnablePrivilege)
		NewState.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	else
		NewState.Privileges[0].Attributes = 0;

	if (!AdjustTokenPrivileges(hToken, FALSE, &NewState, sizeof(TOKEN_PRIVILEGES), NULL, NULL))
	{
		printf("AdjustTokenPrivileges error:%d\n", GetLastError());
		return FALSE;
	}
	return TRUE;
}

DWORD WINAPI ThreadProc(LPVOID lParam)
{
	PTHREAD_PARAM pParam = (PTHREAD_PARAM)lParam;
	// "user32.dll"
	HMODULE hMod = ((pfnLoadLibrary)pParam->pFunc[0])(pParam->szBuf[0]);
	if (!hMod)
		return 1;

	// "MessageBoxA"
	pfnMsgBox pFunc = (pfnMsgBox)((pfnGetProcAddress)pParam->pFunc[1])(hMod, pParam->szBuf[1]);
	if (!pFunc)
		return 1;

	pFunc(NULL, pParam->szBuf[2], pParam->szBuf[3], MB_OK);
	return 0;
}

BOOL InjectCode(DWORD dwPID)
{
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID);
	if (!hProcess)
	{
		printf("OpneProcess Error:%d\n", GetLastError());
		return FALSE;
	}

	// 写入线程函数所用的参数
	THREAD_PARAM param = { 0 };
	HMODULE hMod = GetModuleHandleA("Kernel32.dll");
	param.pFunc[0] = GetProcAddress(hMod, "LoadLibraryA");
	param.pFunc[1] = GetProcAddress(hMod, "GetProcAddress");
	strcpy_s(param.szBuf[0], "user32.dll");
	strcpy_s(param.szBuf[1], "MessageBoxA");
	strcpy_s(param.szBuf[2], "Hello, World");
	strcpy_s(param.szBuf[3], "AHU");

	DWORD dwSize = sizeof(THREAD_PARAM);
	VOID* pParam = VirtualAllocEx(hProcess, NULL, dwSize, MEM_COMMIT, PAGE_READWRITE);
	if (!pParam)
	{
		printf("VirtualAllocEx+ for parameter Error:%d\n", GetLastError());
		return FALSE;
	}

	if (!WriteProcessMemory(hProcess, pParam, &param, dwSize, NULL))
	{
		printf("WriteProcessMemory Error:%d\n", GetLastError());
		return FALSE;
	}

	// 写入远程线程函数
	dwSize = (DWORD)InjectCode - (DWORD)ThreadProc;
	VOID* pThreadAddr = VirtualAllocEx(hProcess, NULL, dwSize, MEM_COMMIT, PAGE_READWRITE);
	if (!pThreadAddr)
	{
		printf("VirtualAllocEx for Thread Error:%d\n", GetLastError());
		return FALSE;
	}

	if (!WriteProcessMemory(hProcess, pThreadAddr, ThreadProc, dwSize, NULL))
	{
		printf("WriteProcessMemory for Thread Error:%d\n", GetLastError());
		return FALSE;
	}

	HANDLE hThread = CreateRemoteThread(hProcess, NULL, dwSize, (LPTHREAD_START_ROUTINE)pThreadAddr, pParam, 0, NULL);
	if (!hThread)
	{
		printf("CreateRemoteThread Error:%d\n", GetLastError());
		return FALSE;
	}

	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	CloseHandle(hProcess);
	return TRUE;
}


int main(int argc, char** argv)
{
	if (argc != 2)
	{
		printf("\n USAGE: %s <PID>\n", argv[0]);
		return 1;
	}

	if (!SetPrivilege(SE_DEBUG_NAME, TRUE))
		return 1;

	DWORD dwPid = atoi(argv[1]);
	InjectCode(dwPid);

	return 0;
}