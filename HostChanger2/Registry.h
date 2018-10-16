#include <string>
#pragma once

class Registry
{
public:
	Registry();
	~Registry();
	static HKEY OpenKey(HKEY hRootKey, const wchar_t* strKey);
	static void SetVal(HKEY hKey, LPCTSTR lpValue, const wchar_t* data);
	static std::wstring GetVal(HKEY hKey, LPCTSTR lpValue);
};

