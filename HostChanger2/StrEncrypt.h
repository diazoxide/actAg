#include <string>
#pragma once
using namespace std;
class StrEncrypt
{
public:
	StrEncrypt();
	~StrEncrypt();
	static wstring encrypt_string(wstring msg);
	static wstring decrypt_string(wstring msg);
};

