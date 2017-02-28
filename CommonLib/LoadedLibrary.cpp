
#include <cstdio>
#include <string>

#include <Windows.h>

#include "LoadedLibrary.hpp"

LoadedLibrary::LoadedLibrary(const std::wstring& path) :
	module(load_library(path))
{ }

HMODULE LoadedLibrary::load_library(const std::wstring& path)
{
	HMODULE mod = LoadLibraryW(path.c_str());

	if (nullptr == mod)
	{
		throw std::exception("LoadLibrary failed", GetLastError());
	}

	return mod;
}

LoadedLibrary::~LoadedLibrary()
{
	if(!FreeLibrary(module))
	{
		OutputDebugString(L"LoadedLibrary failed");
	}
}

HMODULE LoadedLibrary::get_module() const
{
	return module;
}

FARPROC LoadedLibrary::get_proc_address(const std::string& proc_name) const
{
	FARPROC proc = GetProcAddress(module, proc_name.c_str());

	if (nullptr == proc)
	{
		throw std::exception("GetProcAddress failed", GetLastError());
	}

	return proc;
}




