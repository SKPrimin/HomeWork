#include <windows.h>
#include <stdio.h>
typedef BOOL(*WINAPI pfnHookProc)();

int ModifyRegKey()
{
	HKEY hKey = NULL;
	RegOpenKeyEx(HKEY_CLASSES_ROOT, TEXT("txtfile\\shell\\Open\\command"), 0, KEY_WRITE, &hKey) != ERROR_SUCCESS;
	int nRet = 0;
	TCHAR strPath[260] = { 0 };
	GetModuleFileName(NULL, strPath, 260);
	wsprintf(strPath, TEXT("%s %%1"), strPath);
	if (RegSetKeyValue(hKey, NULL, NULL, REG_EXPAND_SZ, strPath, lstrlen(strPath)) != ERROR_SUCCESS) {
		nRet = 1;
		MessageBox(NULL, strPath, TEXT("notice"), MB_OK);
	}
	else
		nRet = 0;
	RegCloseKey(hKey);
	return nRet;
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	HANDLE hEvent = CreateEvent(NULL, FALSE, TRUE, TEXT("singleton"));
	if (GetLastError() == ERROR_ALREADY_EXISTS)
		return 0;
	HMODULE hModule = LoadLibrary(TEXT("HookDll.dll"));
	if (hModule == NULL)
		return 0;
	pfnHookProc pfnInstall = (pfnHookProc)GetProcAddress(hModule, "InstallHook");
	pfnHookProc pfnUnInstall = (pfnHookProc)GetProcAddress(hModule, "UnInstallHook");
	pfnInstall();

	int ret = ModifyRegKey();

	TCHAR strDir[260] = { 0 };
	TCHAR strPath[260] = { 0 };

	GetSystemDirectory(strDir, 260);
	wsprintf(strPath, TEXT("%s\\notepad.exe"), strDir);
	GetCurrentDirectory(260, strDir);
	MessageBox(NULL, strDir, TEXT("notice"), MB_OK);
	HWND hDesk = GetDesktopWindow();
	ShellExecute(hDesk, TEXT("open"), strPath, lpCmdLine, strDir, SW_SHOWNORMAL);

	do
	{
		int nRet = MessageBox(NULL, TEXT("ÍË³ö?"), TEXT("Tips"), MB_YESNO);
		if (nRet == IDYES)
			pfnUnInstall();
		break;
	} while (TRUE);
	FreeLibrary(hModule);
	CloseHandle(hEvent);
	return 0;
}
