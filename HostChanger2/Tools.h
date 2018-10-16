#pragma once
#include <string>

class Tools
{
public:
	static void WriteLog(std::wstring str);
	static void WriteLog(std::wstring str, bool anyways);
	static std::wstring GetMAC();
	static std::wstring OsVersion();
	static wchar_t* getExePath();
	static bool DownloadFile(std::wstring url, std::wstring path);
	static int createLink(std::wstring file, std::wstring name);
	static void KillProcessById(DWORD pid);
	static bool IsElevated();
	static bool runExe(const wchar_t* PATH, bool async);
};

