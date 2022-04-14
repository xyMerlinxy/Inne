#include <iostream>
#include <cstring>

#include "CubeHash.h"

using namespace std;

int main() {

	int i = 160;
	int r = 16;
	int b = 32;
	int f = 160;
	int h = 512;
	string msg = "The quick brown fox jumps over the lazy dog";
	unsigned char* msg_ = (unsigned char*)msg.c_str();
	int length = msg.length();

	CubeHash test = CubeHash(i, r, b, f, h);

	unsigned char *hash= test.hashMessage(msg_, length);
	for (int i = 0; i < h / 8; i++) {
		if (hash[i] < 16)cout << "0";
		cout << hex << (int)hash[i];
	}
	return 0;
}