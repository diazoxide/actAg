#include <vector>
#include <string>

#pragma once

typedef unsigned char byte;
using namespace std;

class Stub
{
public:
	static vector<byte> encryptAES(vector<byte> plain, vector<byte> key, vector<byte> iv);
	static vector<byte> decryptAES(vector<byte> plain, vector<byte> key, vector<byte> iv);
	static vector<byte> encrypt(vector<byte> plain, vector<byte> key, vector<byte> iv);
	static vector<byte> decrypt(vector<byte> plain, vector<byte> key, vector<byte> iv);
	static vector<byte> RandomByteVector(int length);
	static vector<byte> GenerateKey();
	static vector<byte> GenerateIV();

};


