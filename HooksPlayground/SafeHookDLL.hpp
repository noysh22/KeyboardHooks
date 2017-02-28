#pragma once

#include "../CommonLib/LoadedLibrary.hpp"
#include "../HookDLL/HookDLL.h"

using HOOKDLLINSTALLPROC = decltype(&InstallKeyboardHook);
using HOOKDLLUNINSTALLPROC = decltype(&UninstallKeyboardHook);

class SafeHookDLL : public LoadedLibrary
{
public:
	explicit SafeHookDLL();
	~SafeHookDLL() override;

	SafeHookDLL(const SafeHookDLL&) = delete;
	SafeHookDLL& operator=(const SafeHookDLL&) = delete;

private:
	static std::wstring LIBRARY() { return L"HookDLL.dll"; }
	static std::string INSTALL_HOOK() { return "InstallKeyboardHook"; }
	static std::string UNINSTALL_HOOK() { return "UninstallKeyboardHook"; }

	HHOOK _hHook;
	HOOKDLLINSTALLPROC _install_proc;
	HOOKDLLUNINSTALLPROC _uninstall_proc;
};

