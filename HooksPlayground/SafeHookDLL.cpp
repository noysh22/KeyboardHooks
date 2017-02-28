#include "SafeHookDLL.hpp"

SafeHookDLL::SafeHookDLL() :
	LoadedLibrary(LIBRARY())
{
	_install_proc = reinterpret_cast<HOOKDLLINSTALLPROC>(get_proc_address(INSTALL_HOOK()));
	_uninstall_proc = reinterpret_cast<HOOKDLLUNINSTALLPROC>(get_proc_address(UNINSTALL_HOOK()));

	if (!_install_proc(&_hHook))
	{
		wprintf_s(L"Failed calling dll install hook function function\n");
		throw std::exception("Failed installing hook", GetLastError());
	}
}

SafeHookDLL::~SafeHookDLL()
{
	try
	{
		if (!_uninstall_proc(_hHook))
		{
			wprintf_s(L"Failed calling dll uninstall hook function function\n");
		}
	}
	catch(...)
	{
		wprintf_s(L"Exception thrown in SafeHookDLL dtor\n");
	}
}

