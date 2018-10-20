#include "stdafx.h"
#include "Encrypt.h"
#include "Tools.h"
#include "Stub.h"

#if _MOD_CRYPT
#include "Sources.h"
#include "Variables.h"
#endif


#include "xSources.h"
#include "EncryptKeys.h"

vector<wstring> Encrypt::DecryptSources() {
	vector<wstring> _sources;
	_sources.reserve(xSources.size());
	for (int i = 0; i < xSources.size(); i++) {
		vector<byte> xSource = xSources[i];
		vector<byte> aSource = Stub::decrypt(xSource, EncryptKeys_key, EncryptKeys_iv);
		std::wstring _source(aSource.begin(), aSource.begin() + aSource.size());
		_sources.push_back(_source);
	}
	return _sources;
}

wstring Encrypt::DecryptVariable(vector<byte> data) {
	vector<byte> aVariable = Stub::decrypt(data, EncryptKeys_key, EncryptKeys_iv);
	std::wstring variable(aVariable.begin(), aVariable.begin() + aVariable.size());
	return variable;
}


#if _MOD_CRYPT
bool Encrypt::SaveVectorToArrayOfBytes(const char* filename, const char* array_name, vector<vector<byte>> data) {
	FILE *f;
	int i;
	char c;
	f = fopen(filename, "w");
	// Writing shellcode
	fprintf(f, "vector<vector<unsigned char>> %s = {\n", array_name);
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

bool Encrypt::SaveVariables(map<wstring,vector<byte>> data) {
	FILE *f;
	char c;
	f = _wfopen(L"xVariables.h", L"w");
	// Writing shellcode

	for (auto const& it : data) {
		wstring varName = it.first;

		fwprintf(f, L"const vector<unsigned char> %s = {", varName.c_str());

		auto s = it.second;
		for (int j = 0; j < s.size(); j++) {
			c = s[j];
			if (j != 0) fprintf(f, ",");
			fwprintf(f, L"0x%.2X", (unsigned char)c);
		}

		fwprintf(f, L"};\n");
	}


	fclose(f);
	return true;
}

bool Encrypt::SaveKeys(vector<byte> key, vector<byte> iv) {
	FILE *f;
	int i;
	char c;
	wstring key_var_name;

	f = _wfopen(L"EncryptKeys.h", L"w");

	// Writing Encrypting key
	key_var_name = L"EncryptKeys_key";
	fwprintf(f, L"vector<unsigned char> %s = {", key_var_name.c_str());

	for (i = 0; i < key.size(); i++) {
		c = key[i];
		if (i != 0) fprintf(f, ",");
		fprintf(f, "0x%.2X", (unsigned char)c);
	}

	fprintf(f, "};\n");

	// IV
	// Writing Encrypting key
	key_var_name = L"EncryptKeys_iv";
	fwprintf(f, L"vector<byte> %s = {", key_var_name.c_str());

	for (i = 0; i < iv.size(); i++) {
		c = iv[i];
		if (i != 0) fprintf(f, ",");
		fprintf(f, "0x%.2X", (unsigned char)c);
	}

	fprintf(f, "};\n");
}

bool Encrypt::start() {

	vector<byte> key = Stub::GenerateKey();
	vector<byte> iv = Stub::GenerateIV();

	Encrypt::SaveKeys(key, iv);

	Encrypt::EncryptSources(key, iv);
	Encrypt::EncryptVariables(key, iv);

}


bool Encrypt::EncryptSources(vector<byte> key, vector<byte> iv) {

	wstring count;
	vector<vector<byte>> sourcesVec(sources.size(), vector<byte>(999));
	
	for (int i = 0; i < sources.size(); i++) {

		wstring source = sources[i];

		vector<byte> sourceVec(source.c_str(), source.c_str() + source.size());

		sourcesVec[i] = Stub::encrypt(sourceVec, key, iv);

	}

	if (Encrypt::SaveVectorToArrayOfBytes("xSources.h", "xSources", sourcesVec)) {
		Tools::WriteLog(L"EncrypteSources: Done");
		return true;
	}
}

bool Encrypt::EncryptVariables(vector<byte> key, vector<byte> iv) {
	map<wstring, vector<byte>> xVariables;
	for (auto const& it : variables) {
		wstring name = it.first;
		wstring value = it.second;
		vector<byte> valueVec(value.c_str(), value.c_str() + value.size());
		vector<byte> xValueVec = Stub::encrypt(valueVec, key, iv);
		xVariables.insert(std::pair<wstring,vector<byte>>(name, xValueVec));
	}
	if (Encrypt::SaveVariables(xVariables)) {
		Tools::WriteLog(L"EncryptVariables: Done");
		return true;
	}
		
}
#endif