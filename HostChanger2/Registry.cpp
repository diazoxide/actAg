#include "stdafx.h"
#include "Registry.h"
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <iostream>
using std::cout; using std::endl; using std::wstring;


Registry::Registry()
{
}

HKEY Registry::OpenKey(HKEY hRootKey, const wchar_t* strKey)
{
	HKEY hKey;
	LONG nError = RegOpenKeyEx(hRootKey, strKey, NULL, KEY_ALL_ACCESS, &hKey);

	if (nError == ERROR_FILE_NOT_FOUND)
	{
		nError = RegCreateKeyEx(hRootKey, strKey, NULL, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
	}

	if (nError) {}

	return hKey;
}

void Registry::SetVal(HKEY hKey, LPCTSTR lpValue, const wchar_t* data)
{
	LONG nError = RegSetValueEx(hKey, lpValue, NULL, REG_SZ, (LPBYTE)data, sizeof(wchar_t)*(wcslen(data) + 1));

	if (nError) {}
	//cout << "Error: " << nError << " Could not set registry value: " << (char*)lpValue << endl;
}

wstring Registry::GetVal(HKEY hKey, LPCTSTR lpValue)
{
	DWORD type;
	DWORD cbData;
	if (RegQueryValueEx(hKey, lpValue, NULL, &type, NULL, &cbData) != ERROR_SUCCESS)
	{
		return L"";
	}

	if (type != REG_SZ)
	{
		return L"";
	}

	wstring value(cbData / sizeof(wchar_t), L'\0');
	if (RegQueryValueEx(hKey, lpValue, NULL, NULL, reinterpret_cast<LPBYTE>(&value[0]), &cbData) != ERROR_SUCCESS)
	{
		return L"";
	}

	//RegCloseKey(hKey);

	size_t firstNull = value.find_first_of(L'\0');
	if (firstNull != std::string::npos)
		value.resize(firstNull);

	return value;
}


Registry::~Registry()
{
}
