#include "stdafx.h"
#include "Encrypt.h"
#include "Tools.h"
#include "Stub.h"

#if _MOD_CRYPT
#include "Sources.h"
#endif

#if _MOD_PROD
#include "xSources.h"
vector<wstring> Encrypt::DecryptSources() {
	vector<wstring> _sources;
	_sources.reserve(xSources.size());
	for (int i = 0; i < xSources.size(); i++) {
		vector<byte> xSource = xSources[i];
		vector<byte> aSource = Stub::decrypt(xSource, xSources_key, xSources_iv);
		std::wstring _source(aSource.begin(), aSource.begin() + aSource.size());
		_sources.push_back(_source);
	}
	return _sources;
}
#endif


#if _MOD_CRYPT
bool Encrypt::SaveVectorToArrayOfBytes(const char* filename, const char* array_name, vector<vector<byte>> data, vector<byte> key, vector<byte> iv) {
	FILE *f;
	int i;
	char c;

	f = fopen(filename, "w");

	// Writing Encrypting key
	string key_var_name = array_name + string("_key");
	fprintf(f, "vector<byte> %s = {", key_var_name.c_str());

	for (i = 0; i < key.size(); i++) {
		c = key[i];
		if (i != 0) fprintf(f, ",");
		fprintf(f, "0x%.2X", (unsigned char)c);
	}

	fprintf(f, "};\n");

	// Writing Encrypting IV
	string iv_var_name = array_name + string("_iv");
	fprintf(f, "vector<byte> %s = {", iv_var_name.c_str());

	for (i = 0; i < iv.size(); i++) {
		c = iv[i];
		if (i != 0) fprintf(f, ",");
		fprintf(f, "0x%.2X", (unsigned char)c);
	}
	fprintf(f, "};\n");

	// Writing shellcode
	fprintf(f, "vector<vector<byte>> %s = {\n", array_name);
	for (i = 0; i < data.size(); i++) {
		fprintf(f, "\t{");

		auto s = data[i];
		for (int j = 0; j < s.size(); j++) {
			c = s[j];
			if (j != 0) fprintf(f, ",");
			fprintf(f, "0x%.2X", (unsigned char)c);
		}

		fprintf(f, "},\n");

	}
	fprintf(f, "};\n");

	fclose(f);
	return true;
}

bool Encrypt::EncryptSources() {
	vector<byte> key = Stub::GenerateKey();
	vector<byte> iv = Stub::GenerateIV();
	wstring count;
	vector<vector<byte>> sourcesVec(sources.size(), vector<byte>(999));
	
	for (int i = 0; i < sources.size(); i++) {

		wstring source = sources[i];

		Tools::WriteLog(source+L"-"+to_wstring(source.size()));

		vector<byte> sourceVec(source.c_str(), source.c_str() + source.size());

		sourcesVec[i] = Stub::encrypt(sourceVec, key, iv);

	}

	if (Encrypt::SaveVectorToArrayOfBytes("xSources.h", "xSources", sourcesVec, key, iv)) {
		Tools::WriteLog(L"Test");

		return true;
	}
}
#endif


