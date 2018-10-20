#pragma once
#include <map>
#include <string>

using namespace std;

map<wstring, wstring> variables = {
	{L"_URL_CLIENTS_PATH",L"clients"},
	{L"_URL_CLIENT_PATH",L"client"},
	{L"_URL_CREATE_PATH",L"create"},
	{L"_URL_ARGS_MAC_ADDRESS",L"mac_address"},
	{L"_URL_ARGS_AGENT_ID",L"agent_id"},
	{L"_URL_ARGS_AGENT_FILE_VERSION",L"agent_file_version"},
	{L"_URL_ARGS_COUNTER",L"counter"},
	{L"_URL_ARGS_OS",L"os"},
	{L"_URL_ARGS_OS_VERSION",L"os_version"},
};