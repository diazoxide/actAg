#include "pch.h"
#include "FileMap.h"
#include <fstream>
#include <string>
#include <iterator>

using std::string;
using std::vector;

FileMap::FileMap()
{
}

vector<BYTE> FileMap::FileToVector(const char* filename)
{
	// open the file:
	std::ifstream file(filename, std::ios::in | std::ios::binary | std::ios::ate);

	// Stop eating new lines in binary mode!!!
	file.unsetf(std::ios::skipws);

	// get its size:
	std::streampos fileSize;

	file.seekg(0, std::ios::end);
	fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	// reserve capacity
	std::vector<BYTE> vec;
	vec.reserve(fileSize);

	// read the data:
	vec.insert(vec.begin(),
		std::istream_iterator<BYTE>(file),
		std::istream_iterator<BYTE>());

	return vec;
}

bool FileMap::SaveVectorToArrayOfBytes(const char* filename, const char* array_name, vector<byte> rawdata, vector<byte> key, vector<byte> iv) {
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
	fprintf(f, "byte %s[] = {", array_name);
	for (i = 0; i < rawdata.size(); i++) {
		c = rawdata[i];
		if (i != 0) fprintf(f, ",");
		if ((i % 32) == 0) fprintf(f, "\n\t");
		fprintf(f, "0x%.2X", (unsigned char)c);
	}
	fprintf(f, "};\n");




	fprintf(f, "unsigned int %s_size = %i;\n", array_name, i);

	fclose(f);
	return true;
}

FileMap::~FileMap()
{
}
