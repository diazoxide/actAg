#pragma once
#include <vector>
#include <map>

typedef unsigned char byte;

using namespace std;

class Encrypt
{
public:
#if _MOD_CRYPT
	static bool SaveVectorToArrayOfBytes(const char* filename, const char* array_name, vector<vector<byte>> data);
	static bool SaveKeys(vector<byte> key, vector<byte> iv);
	static bool SaveVariables(map<wstring, vector<byte>> data);
	static bool start();
	static bool EncryptSources(vector<byte> key, vector<byte> iv);
	static bool EncryptVariables(vector<byte> key, vector<byte> iv);
#endif

	static vector<wstring> DecryptSources();
	static wstring DecryptVariable(vector<byte> data);

};

