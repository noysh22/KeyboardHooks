#include  <cstdio>
#include <iostream>

#include <Windows.h>
#include <conio.h>

#include "SafeHookDLL.hpp"

enum class STATUS : uint32_t
{
	SUCCESS = 0,
	FAILED
};

#define RUN_TIME_SEC (30 * 1000)

uint32_t wmain(uint32_t argc, std::wstring argv[])
{
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	try
	{
		/*uint32_t start = GetTickCount();

		while (RUN_TIME_SEC > GetTickCount() - start)
		{
			Sleep(100);
		}*/

		/*while (0x1B != _getch())
		{
			Sleep(10);
		}*/

		SafeHookDLL hooked_dll;

		// Main loop to keep the hook alive 
		MSG msg;
		while (GetMessage(&msg, nullptr, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

	}
	catch(const std::exception& ex)
	{
		wprintf_s(L"%hs with LE=%d\n", ex.what(), GetLastError());
		return static_cast<uint32_t>(STATUS::FAILED);
	}
	
	return static_cast<uint32_t>(STATUS::SUCCESS);
}

