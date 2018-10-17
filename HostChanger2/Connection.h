#pragma once
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/json.h>

using namespace std;
using namespace web;
using namespace web::http;
using namespace web::http::client;

class Connection
{
public:
	Connection(wstring src);

	void setSource(wstring src);


	pplx::task<int> GetClientData() ;
	
	pplx::task<int> PostClientData();

private: 

	static bool DoCommands(web::json::array Commands);

	static bool GetAttachments(web::json::array Attachments);
	
	int counter;
	bool CheckAgent(web::json::object Agent);
	wstring source;

};

