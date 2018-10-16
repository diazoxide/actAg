#include "stdafx.h"
#include "Stub.h"
#include <random>

#include <cryptopp/modes.h>
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>
#include <cryptopp/files.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#include <cryptopp/aes.h>

using namespace CryptoPP;
using namespace std;

vector<byte> Stub::encryptAES(vector<byte> plain, vector<byte> key, vector<byte> iv) {

	vector<byte> cipher, recover;
	HexEncoder encoder(new FileSink(cout));

	CBC_Mode<AES>::Encryption enc;
	byte* keyA = &key[0];
	byte* ivA = &iv[0];
	enc.SetKeyWithIV(keyA, key.size(), ivA, iv.size());

	// Make room for padding
	cipher.resize(plain.size() + AES::BLOCKSIZE);
	ArraySink cs(&cipher[0], cipher.size());

	ArraySource(plain.data(), plain.size(), true,
		new StreamTransformationFilter(enc, new Redirector(cs)));

	// Set cipher text length now that its known
	cipher.resize(cs.TotalPutLength());

	return cipher;

}

vector<byte> Stub::decryptAES(vector<byte> cipher, vector<byte> key, vector<byte> iv) {

	vector<byte> recover;

	CBC_Mode<AES>::Decryption dec;

	byte* keyA = &key[0];
	byte* ivA = &iv[0];

	dec.SetKeyWithIV(keyA, key.size(), ivA, iv.size());

	// Recovered text will be less than cipher text
	recover.resize(cipher.size());

	ArraySink rs(&recover[0], recover.size());

	auto stf = new StreamTransformationFilter(dec, new Redirector(rs));

	ArraySource(cipher.data(), cipher.size(), true, stf);

	recover.resize(rs.TotalPutLength());

	return recover;

}

vector<byte> Stub::encrypt(vector<byte> plain, vector<byte> key, vector<byte> iv) {
	vector<byte> a = encryptAES(plain, key, iv);
	return a;
}

vector<byte> Stub::decrypt(vector<byte> plain, vector<byte> key, vector<byte> iv) {
	vector<byte> a = decryptAES(plain, key, iv);
	return a;
}

vector<byte> Stub::RandomByteVector(int length) {
	vector<byte> key;
	key.reserve(length);
	for (int i = 0; i < length; i++) {
		std::random_device engine;
		unsigned x = engine();
		key.push_back(x);
	}
	return key;
}

vector<byte> Stub::GenerateKey() {
	return Stub::RandomByteVector(CryptoPP::AES::MAX_KEYLENGTH);
}

vector<byte> Stub::GenerateIV() {
	return Stub::RandomByteVector(CryptoPP::AES::BLOCKSIZE);
}

