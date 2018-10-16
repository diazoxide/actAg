#pragma once
#include "stdafx.h"
#include "SourceGen.h"
#include "Stub.h"
#include "Sources.h"

using namespace std;
using namespace CryptoPP;

//using random_bytes_engine = std::independent_bits_engine<std::default_random_engine, CHAR_BIT, unsigned char>;


bool SaveVectorToArrayOfBytes(const char* filename, const char* array_name, vector<vector<byte>> rawdata, vector<byte> key, vector<byte> iv) {
	FILE *f;
	int i;
	char c;

	f = fopen(filename, "w");

	// Writing Encrypting key
	string key_var_name = array_name + string("_key");
	fprintf(f, "byte %s[] = {", key_var_name.c_str());

	for (i = 0; i < key.size(); i++) {
		c = key[i];
		if (i != 0) fprintf(f, ",");
		fprintf(f, "0x%.2X", (unsigned char)c);
	}

	fprintf(f, "\n\t};\n");

	// Writing Encrypting IV
	string iv_var_name = array_name + string("_iv");
	fprintf(f, "byte %s[] = {", iv_var_name.c_str());

	for (i = 0; i < iv.size(); i++) {
		c = iv[i];
		if (i != 0) fprintf(f, ",");
		fprintf(f, "0x%.2X", (unsigned char)c);
	}
	fprintf(f, "};\n");

	// Writing shellcode
	fprintf(f, "vector<vector<byte>> %s = {", array_name);
	for (i = 0; i < rawdata.size(); i++) {
		fprintf(f, "{\n");

		auto s = rawdata[i];
		for (int j = 0; j < s.size(); i++) {
			c = s[i];
			if (i != 0) fprintf(f, ",");
			if ((i % 32) == 0) fprintf(f, "\n\t");
			fprintf(f, "0x%.2X", (unsigned char)c);
		}

		fprintf(f, "},\n");

	}
	fprintf(f, "};\n");

	fprintf(f, "unsigned int %s_size = %i;\n", array_name, i);

	fclose(f);
	return true;
}


int wmain(){

	vector<byte> key = Stub::GenerateKey(CryptoPP::AES::MAX_KEYLENGTH);
	vector<byte> iv = Stub::GenerateKey(CryptoPP::AES::BLOCKSIZE);

	wstring count;
	vector<vector<byte>> sourcesVec(sources.size(), vector<byte>(count.max_size()));

	for (int i = 0; i < sources.size(); i++) {

		vector<byte> sourceXVec;

		sourceXVec.reserve(sources[i].size());

		for (int j = 0; j < sources[i].size(); j++) {

			sourceXVec[j] = (byte)sources[i][j];
		}
		sourcesVec[i] = Stub::encrypt(sourceXVec, key, iv);

	}


	if (SaveVectorToArrayOfBytes("xSh.h", "xSh", sourcesVec, key, iv)) {
		
	}

}
