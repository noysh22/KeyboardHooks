// HookDLL.cpp : Defines the exported functions for the DLL application.
//

#include <cstdio>
#include <iostream>

#include <array>
#include <Windows.h>
#include "HookDLL.h"

HMODULE g_hMod = nullptr;

char get_ascii_char(const PKBDLLHOOKSTRUCT& hook_struct)
{
	static const uint32_t BYTE_ARRAY_SIZE = 256;
	static const uint32_t FLAGS_PARAM_NO_MENU = 0;
	static const char NULL_TERMINATOR = '\0';

	std::array<byte, BYTE_ARRAY_SIZE> keyboard_state;
	
	if (!GetKeyboardState(keyboard_state.data()))
	{
		throw std::exception("GetKeyboardState failed", GetLastError());
	}

	uint16_t char_value = 0;

	int ret_value = ToAscii(
		hook_struct->vkCode,
		hook_struct->scanCode,
		keyboard_state.data(),
		&char_value,
		FLAGS_PARAM_NO_MENU);

	if ( 0 > ret_value)
	{
		return NULL_TERMINATOR;
	}

	return static_cast<char>(char_value);
}

LRESULT CALLBACK KeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	static const char NULL_TERMINATOR = '\0';

	// Trying process which key was pressed
	if (HC_ACTION == nCode)
	{
		auto hook_struct = reinterpret_cast<PKBDLLHOOKSTRUCT>(lParam);
		char pressed_key = NULL_TERMINATOR;

		switch (wParam)
		{
			case WM_KEYDOWN:
			case WM_SYSKEYDOWN:
				pressed_key = get_ascii_char(hook_struct);
				if (NULL_TERMINATOR != pressed_key)
					std::cout << "key pressed: " << pressed_key << std::endl;
				break;
			default:
			// Ignore different events for now, extend in the future
				break;
		}
	}

	return CallNextHookEx(nullptr, nCode, wParam, lParam);
}

BOOL HOOKDLL_API WINAPI InstallKeyboardHook(HHOOK* phHook)
{
	HHOOK hHook = SetWindowsHookEx(WH_KEYBOARD_LL, static_cast<HOOKPROC>(KeyboardHookProc), g_hMod, 0);
	
	if (nullptr == hHook)
	{
		wprintf_s(L"Failed calling SetWindowsHookEx with LE = %d", GetLastError());
		return FALSE;
	}

	std::wcout << L"This is an entry point" << std::endl;

	*phHook = hHook;

	return TRUE;
}

BOOL HOOKDLL_API WINAPI UninstallKeyboardHook(HHOOK hHook)
{
	BOOL ret_val = UnhookWindowsHookEx(hHook);

	if (!ret_val)
	{
		wprintf_s(L"UnhookWindowsHookEx failed with %d\n", GetLastError());
	}

	return ret_val;
}
