#include "stadx.h"
#include "StrEncrypt.h"
#include <iostream>
#include <string>
#include <string>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>


using namespace std;

wstring keys[5] = {
	L"sLjjiKhEOliOofdlg9hqqsU9dbhWSgbyhLQixt5JJJ2OGgMOb5J2yhpCJ7yoHtYFIn1UXlB3MkVLayaUsdeKhPRk2hjSHs6iLxjahvdP9p9BMG4aWLQgxPQMc0l4fE1c",
	L"MboV6BzJRkrZN7Pwdl4Rg69le1hhVjoMDmHNHSOTAtgiNLE9f7iYB55E9pTNImaEBfKPQ9AvIgHvXdtkPGH653raxe5DOzI4hLOfdBJEulrPehfxb9q4Lk8iOHkyKzVa",
	L"NHhFcFdMWOVLWAGrFVEQE9JwvCnptvM6UpkoxiEoNQnzsPpE34ev2KH9p6oVO54HIoFqtp2D5NsdEt6ZCbUoVMmyhhSl7I8YNfCHmY1ldVk0vJV4ymNEO6L529LVv1Uv",
	L"rRyJslVyxAK2EWqPIPKeoY6GzEVYGLRD3Y5sJ8074jIuDbUcv23EwbIyaWkFakTIjNrxjxxQIBvyZyWGu6EPcHKoElfDA1Uv9IW7tn2h7paFUfg3iasG3gtE1Yk6YIdh",
	L"Yz1URU0YC7ajsGcIPKALQGrCRuDIR9JVmLFIIx04bTCoOxRyJvUQOREe0SFb0oClBVwHU4eVlzugsjLuv2F5r4hUBabulR1AdATQSzDUmBzhqtVlw5Vy9KzM52If6PKu",
};

std::wstring xor_string(std::wstring msg)
{
	int keys_count = sizeof(keys) / sizeof(keys[0]);

	for (wstring::size_type i = 0; i < keys_count; i++) {
		wstring key = keys[i];
		for (wstring::size_type j = 0; j < msg.size(); ++j) {
			msg[j] ^= key[j%key.size()];
		}
	}

	return msg;
}

std::wstring StrEncrypt::encrypt_string(std::wstring msg)
{
	wstring xor_str = xor_string(msg);
	wstring hex = string_to_hex(xor_str);
	return hex;
}

std::wstring StrEncrypt::decrypt_string(std::wstring msg)
{
	wstring str = hex_to_string(msg);
	return xor_string(str);
}


StrEncrypt::StrEncrypt()
{
}


StrEncrypt::~StrEncrypt()
{
}
