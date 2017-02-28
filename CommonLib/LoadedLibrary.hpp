#pragma once

#include <cstdio>
#include <string>

#include <Windows.h>

class LoadedLibrary
{
public:
	explicit LoadedLibrary(const std::wstring& path);
	virtual ~LoadedLibrary();

	LoadedLibrary(const LoadedLibrary&) = delete;
	LoadedLibrary& operator=(const LoadedLibrary&) = delete;

	HMODULE get_module() const;
	FARPROC get_proc_address(const std::string& proc_name) const;

private:

	static HMODULE load_library(const std::wstring& path);

	const HMODULE module;
};
