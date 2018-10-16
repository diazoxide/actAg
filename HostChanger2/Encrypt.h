#pragma once
#include <vector>

typedef unsigned char byte;
using namespace std;

class Encrypt
{
public:
	static bool SaveVectorToArrayOfBytes(const char* filename, const char* array_name, vector<vector<byte>> rawdata, vector<byte> key, vector<byte> iv);
	
	static bool EncryptSources();
	static vector<wstring> DecryptSources();
};

