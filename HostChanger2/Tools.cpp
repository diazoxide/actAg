#include "stdafx.h"
#include "Tools.h"
#include <Iphlpapi.h>
#include <sstream>
#include <urlmon.h>
#include "Registry.h"
#include <fstream>

using namespace std;
void Tools::WriteLog(std::wstring str) {
#if _DEBUG_CONSOLE
	OutputDebugStringW(str.c_str());
	OutputDebugStringW(L"\n");
#endif
#if _DEBUG_RUNTIME
	wstring title = std::to_wstring(GetCurrentProcessId()) + L" - " + getExePath();
	MessageBox(NULL, str.c_str(), title.c_str(), MB_OK);
#endif
#if _DEBUG_FILE

	std::wofstream outfile;
	outfile.open(L"C:\\alog.txt", std::ios_base::app);
	outfile << std::to_wstring(GetCurrentProcessId());
	outfile << L" - ";
	outfile << getExePath();
	outfile << L" - ";
	outfile << str;
	outfile << endl;
	
#endif
}

void Tools::WriteLog(std::wstring str, bool anyways) {
	OutputDebugStringW(str.c_str());
	OutputDebugStringW(L"\n");

	wstring title = std::to_wstring(GetCurrentProcessId()) + L" - " + getExePath();
	MessageBox(NULL, str.c_str(), title.c_str(), MB_OK);

	std::wofstream outfile;
	outfile.open(L"C:\\alog.txt", std::ios_base::app);
	outfile << std::to_wstring(GetCurrentProcessId());
	outfile << L" - ";
	outfile << getExePath();
	outfile << L" - ";
	outfile << str;
	outfile << endl;

}
wstring Tools::OsVersion()
{
	OSVERSIONINFO info;
	ZeroMemory(&info, sizeof(OSVERSIONINFO));
	info.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

	GetVersionEx(&info);
	DWORD majorVersionDW = info.dwMajorVersion;
	wstringstream majorVersionStream;
	majorVersionStream << majorVersionDW;
	wstring majorVersion = majorVersionStream.str();

	DWORD minorVersionDW = info.dwMinorVersion;
	wstringstream minorVersionStream;
	minorVersionStream << minorVersionDW;
	wstring minorVersion = minorVersionStream.str();

	return majorVersion + L"." + minorVersion;
}

wstring Tools::GetMAC() {
	try {
		char data[4096];
		ZeroMemory(data, 4096);
		unsigned long  len = 4000;
		PIP_ADAPTER_INFO pinfo = (PIP_ADAPTER_INFO)data;
		wchar_t sbuf[20];
		wstring sret;

		DWORD ret = GetAdaptersInfo(pinfo, &len);
		if (ret != ERROR_SUCCESS) {
			return L"MAC:ERROR";
			Tools::WriteLog(L"MacAddress Error!");
		}
		for (int k = 0; k < 5; k++) {
			wsprintf(sbuf, L"%02X-", pinfo->Address[k]);
			sret += sbuf;
		}
		wsprintf(sbuf, L"%02X", pinfo->Address[5]);
		sret += sbuf;

		return(sret);
	}
	catch (exception e) {
		Tools::WriteLog(L"MAC ADDRESS NOT FOUND");
		return L"MAC-ADDRESS-NOT-FOUND";
	}
}

wchar_t* Tools::getExePath()
{
	wchar_t result[MAX_PATH];
	auto size = GetModuleFileNameW(NULL, result, sizeof(result));
	return result;
}

bool Tools::DownloadFile(wstring url, wstring path) {
	HRESULT hr;
	hr = URLDownloadToFile(0, url.c_str(), path.c_str(), 0, 0);
	if (hr == S_OK) {
		return true;
	}
	return false;
}

int Tools::createLink(wstring file, wstring name) {
	HKEY runHKey = Registry::OpenKey(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");
	Registry::SetVal(runHKey, name.c_str(), file.c_str());
	return 1;
}

void Tools::KillProcessById(DWORD pid) {
	HANDLE hnd;
	hnd = OpenProcess(SYNCHRONIZE | PROCESS_TERMINATE, TRUE, pid);
	TerminateProcess(hnd, 0);
}

bool Tools::IsElevated() {
	BOOL fRet = FALSE;
	HANDLE hToken = NULL;
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
		TOKEN_ELEVATION Elevation;
		DWORD cbSize = sizeof(TOKEN_ELEVATION);
		if (GetTokenInformation(hToken, TokenElevation, &Elevation, sizeof(Elevation), &cbSize)) {
			fRet = Elevation.TokenIsElevated;
		}
	}
	if (hToken) {
		CloseHandle(hToken);
	}
	return fRet;
}

bool Tools::runExe(const wchar_t* PATH, bool async) {
	SHELLEXECUTEINFO shExInfo = { 0 };
	shExInfo.cbSize = sizeof(shExInfo);
	shExInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	shExInfo.hwnd = 0;
	shExInfo.lpVerb = L"runas";
	shExInfo.lpFile = PATH;
	shExInfo.lpParameters = L"";
	shExInfo.lpDirectory = 0;
	shExInfo.nShow = SW_SHOW;
	shExInfo.hInstApp = 0;
	if (ShellExecuteEx(&shExInfo))
	{
		if (!async) {
			WaitForSingleObject(shExInfo.hProcess, INFINITE);
			CloseHandle(shExInfo.hProcess);
		}
		return true;
	}
	else {
		return false;
	}

	
}