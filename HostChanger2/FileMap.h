#include <windows.h>
#include <vector>
#pragma once
class FileMap
{
public:
	FileMap();
	static std::vector<BYTE> FileToVector(const char* filename);
	static bool SaveVectorToArrayOfBytes(const char* filename, const char* array_name, std::vector<byte> rawdata, std::vector<byte> key, std::vector<byte> iv);
	~FileMap();
};

