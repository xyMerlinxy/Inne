
#include "CubeHash.h"

CubeHash::CubeHash(int i, int r, int b, int f, int h) {
	// i - liczba rund inicjalizuj�cych
	// r - liczba rund na blok
	// b - d�ugo�� bloku w bajtach
	// f - liczba rund zaka�czaj�cych
	// h - d�ugo�� skr�tu w bitach
	if (i < 0) {
		throw std::invalid_argument("i must be positive integer");
	}
	if (r < 0) {
		throw std::invalid_argument("r must be positive integer");
	}
	if ((b < 1)||(b>128)) {
		throw std::invalid_argument("b must be beetwen 1 and 128");
	}
	if (f < 0) {
		throw std::invalid_argument("f must be positive integer");
	}
	if ((h < 8) || (h > 512)) {
	throw std::invalid_argument("h must be beetwen 8 and 512");
	}
	this->i = i;
	this->r = r;
	this->b = b;
	this->f = f;
	this->h = h;

	state = new unsigned int[32];
	tempState = new unsigned int[32];

	reset();
}

void CubeHash::reset() {
	for (int i = 0; i < 32; i++) {
		state[i] = 0;
	}

	state[0] = h / 8;
	state[1] = b;
	state[2] = r;

	// initialization
	for (int j = 0; j < this->i; j++)this->round();
}

void CubeHash::hash_one_block(unsigned char* msg) {
	unsigned char* temp_state = (unsigned char*)state;
	for (int i = 0; i < b; i++) {
		temp_state[i] ^= msg[i];
	}
	for (int i = 0; i < r; i++) {
		this->round();
	}
}

unsigned char* CubeHash::hashMessage(unsigned char* msg, int length) {
	int num_of_block = length / b;
	for (int i = 0; i < num_of_block; i++) {
		hash_one_block(msg + (i * b));
	}
	unsigned char* temp_block = new unsigned char[b];
	for (int i = 0; i < b; i++) {
		temp_block[i] = 0;
	}
	unsigned char* temp_msg = msg + num_of_block * b;
	int zostalo = length % b;
	for (int i = 0; i < zostalo; i++) {
		temp_block[i] = temp_msg[i];
	}
	temp_block[length % b] = 0x80;

	hash_one_block(temp_block);
	delete[] temp_block;

	state[31] ^= 0x1;
	for (int j = 0; j < this->f; j++)this->round();

	int hash_len = h / 8;
	unsigned char* hash = new unsigned char[hash_len];
	unsigned char* temp_state = (unsigned char*)state;
	for (int i = 0; i < hash_len; i++) {
		hash[i] = temp_state[i];
	}
	return hash;
}

void CubeHash::round() {
	step_1_2_3();
	step_4();
	step_5_6_7_8_10();
	step_9();
}

void CubeHash::step_1_2_3() {
	tempState[0b00000] = (state[0b01000] << 7) | (state[0b01000] >> (25));
	tempState[0b00001] = (state[0b01001] << 7) | (state[0b01001] >> (25));
	tempState[0b00010] = (state[0b01010] << 7) | (state[0b01010] >> (25));
	tempState[0b00011] = (state[0b01011] << 7) | (state[0b01011] >> (25));
	tempState[0b00100] = (state[0b01100] << 7) | (state[0b01100] >> (25));
	tempState[0b00101] = (state[0b01101] << 7) | (state[0b01101] >> (25));
	tempState[0b00110] = (state[0b01110] << 7) | (state[0b01110] >> (25));
	tempState[0b00111] = (state[0b01111] << 7) | (state[0b01111] >> (25));
	tempState[0b01000] = (state[0b00000] << 7) | (state[0b00000] >> (25));
	tempState[0b01001] = (state[0b00001] << 7) | (state[0b00001] >> (25));
	tempState[0b01010] = (state[0b00010] << 7) | (state[0b00010] >> (25));
	tempState[0b01011] = (state[0b00011] << 7) | (state[0b00011] >> (25));
	tempState[0b01100] = (state[0b00100] << 7) | (state[0b00100] >> (25));
	tempState[0b01101] = (state[0b00101] << 7) | (state[0b00101] >> (25));
	tempState[0b01110] = (state[0b00110] << 7) | (state[0b00110] >> (25));
	tempState[0b01111] = (state[0b00111] << 7) | (state[0b00111] >> (25));
	tempState[0b10000] = state[0b00000] + state[0b10000];
	tempState[0b10001] = state[0b00001] + state[0b10001];
	tempState[0b10010] = state[0b00010] + state[0b10010];
	tempState[0b10011] = state[0b00011] + state[0b10011];
	tempState[0b10100] = state[0b00100] + state[0b10100];
	tempState[0b10101] = state[0b00101] + state[0b10101];
	tempState[0b10110] = state[0b00110] + state[0b10110];
	tempState[0b10111] = state[0b00111] + state[0b10111];
	tempState[0b11000] = state[0b01000] + state[0b11000];
	tempState[0b11001] = state[0b01001] + state[0b11001];
	tempState[0b11010] = state[0b01010] + state[0b11010];
	tempState[0b11011] = state[0b01011] + state[0b11011];
	tempState[0b11100] = state[0b01100] + state[0b11100];
	tempState[0b11101] = state[0b01101] + state[0b11101];
	tempState[0b11110] = state[0b01110] + state[0b11110];
	tempState[0b11111] = state[0b01111] + state[0b11111];
}

void CubeHash::step_4() {
	tempState[0b00000] = tempState[0b00000] ^ tempState[0b10000];
	tempState[0b00001] = tempState[0b00001] ^ tempState[0b10001];
	tempState[0b00010] = tempState[0b00010] ^ tempState[0b10010];
	tempState[0b00011] = tempState[0b00011] ^ tempState[0b10011];
	tempState[0b00100] = tempState[0b00100] ^ tempState[0b10100];
	tempState[0b00101] = tempState[0b00101] ^ tempState[0b10101];
	tempState[0b00110] = tempState[0b00110] ^ tempState[0b10110];
	tempState[0b00111] = tempState[0b00111] ^ tempState[0b10111];
	tempState[0b01000] = tempState[0b01000] ^ tempState[0b11000];
	tempState[0b01001] = tempState[0b01001] ^ tempState[0b11001];
	tempState[0b01010] = tempState[0b01010] ^ tempState[0b11010];
	tempState[0b01011] = tempState[0b01011] ^ tempState[0b11011];
	tempState[0b01100] = tempState[0b01100] ^ tempState[0b11100];
	tempState[0b01101] = tempState[0b01101] ^ tempState[0b11101];
	tempState[0b01110] = tempState[0b01110] ^ tempState[0b11110];
	tempState[0b01111] = tempState[0b01111] ^ tempState[0b11111];
}

void CubeHash::step_5_6_7_8_10() {
	state[0b00000] = (tempState[0b00100] << 11) | (tempState[0b00100] >> (21));
	state[0b00001] = (tempState[0b00101] << 11) | (tempState[0b00101] >> (21));
	state[0b00010] = (tempState[0b00110] << 11) | (tempState[0b00110] >> (21));
	state[0b00011] = (tempState[0b00111] << 11) | (tempState[0b00111] >> (21));
	state[0b00100] = (tempState[0b00000] << 11) | (tempState[0b00000] >> (21));
	state[0b00101] = (tempState[0b00001] << 11) | (tempState[0b00001] >> (21));
	state[0b00110] = (tempState[0b00010] << 11) | (tempState[0b00010] >> (21));
	state[0b00111] = (tempState[0b00011] << 11) | (tempState[0b00011] >> (21));
	state[0b01000] = (tempState[0b01100] << 11) | (tempState[0b01100] >> (21));
	state[0b01001] = (tempState[0b01101] << 11) | (tempState[0b01101] >> (21));
	state[0b01010] = (tempState[0b01110] << 11) | (tempState[0b01110] >> (21));
	state[0b01011] = (tempState[0b01111] << 11) | (tempState[0b01111] >> (21));
	state[0b01100] = (tempState[0b01000] << 11) | (tempState[0b01000] >> (21));
	state[0b01101] = (tempState[0b01001] << 11) | (tempState[0b01001] >> (21));
	state[0b01110] = (tempState[0b01010] << 11) | (tempState[0b01010] >> (21));
	state[0b01111] = (tempState[0b01011] << 11) | (tempState[0b01011] >> (21));
	state[0b10000] = tempState[0b00001] + tempState[0b10011];
	state[0b10001] = tempState[0b00000] + tempState[0b10010];
	state[0b10010] = tempState[0b00011] + tempState[0b10001];
	state[0b10011] = tempState[0b00010] + tempState[0b10000];
	state[0b10100] = tempState[0b00101] + tempState[0b10111];
	state[0b10101] = tempState[0b00100] + tempState[0b10110];
	state[0b10110] = tempState[0b00111] + tempState[0b10101];
	state[0b10111] = tempState[0b00110] + tempState[0b10100];
	state[0b11000] = tempState[0b01001] + tempState[0b11011];
	state[0b11001] = tempState[0b01000] + tempState[0b11010];
	state[0b11010] = tempState[0b01011] + tempState[0b11001];
	state[0b11011] = tempState[0b01010] + tempState[0b11000];
	state[0b11100] = tempState[0b01101] + tempState[0b11111];
	state[0b11101] = tempState[0b01100] + tempState[0b11110];
	state[0b11110] = tempState[0b01111] + tempState[0b11101];
	state[0b11111] = tempState[0b01110] + tempState[0b11100];
}

void CubeHash::step_9() {
	// adresacja jest zmieniona, tak aby uwzgl�dni� wczesniejsze wyknonanie kroku 10
	state[0b00000] = state[0b00000] ^ state[0b10001];
	state[0b00001] = state[0b00001] ^ state[0b10000];
	state[0b00010] = state[0b00010] ^ state[0b10011];
	state[0b00011] = state[0b00011] ^ state[0b10010];
	state[0b00100] = state[0b00100] ^ state[0b10101];
	state[0b00101] = state[0b00101] ^ state[0b10100];
	state[0b00110] = state[0b00110] ^ state[0b10111];
	state[0b00111] = state[0b00111] ^ state[0b10110];
	state[0b01000] = state[0b01000] ^ state[0b11001];
	state[0b01001] = state[0b01001] ^ state[0b11000];
	state[0b01010] = state[0b01010] ^ state[0b11011];
	state[0b01011] = state[0b01011] ^ state[0b11010];
	state[0b01100] = state[0b01100] ^ state[0b11101];
	state[0b01101] = state[0b01101] ^ state[0b11100];
	state[0b01110] = state[0b01110] ^ state[0b11111];
	state[0b01111] = state[0b01111] ^ state[0b11110];

}

unsigned char* CubeHash::hashFile(std::string file_name) {
	return this->hashFile(file_name, false);
};

unsigned char* CubeHash::hashFile(std::string file_name, bool write) {
	std::fstream file;
	if (write) {
		file.open(file_name, std::ios::binary | std::ios::app | std::ios::in );
	}
	else
	{
		file.open(file_name, std::ios::binary | std::ios::in);
	}
	if (!file.good()) {
		throw std::invalid_argument("B��dny plik");
	}


	file.seekg(0, std::ios::end);
	unsigned long long length = (unsigned long long)file.tellg();
	file.seekg(0, std::ios::beg);
	unsigned char* msg = new unsigned char[b];
	unsigned long long num_of_block = length / b;

	for (int i = 0; i < num_of_block; i++) {
		file.read((char *)msg, b);
		hash_one_block(msg);
	}

	for (int i = 0; i < b; i++) {
		msg[i] = 0;
	}
	int zostalo = length % b;
	file.read((char *)msg, zostalo);

	// padding
	msg[length % b] = 0x80;

	hash_one_block(msg);
	delete[] msg;

	// xored 0x01 to last word in state
	state[31] ^= 0x1;

	// final rounds
	for (int j = 0; j < this->f; j++)this->round();

	int hash_len = h / 8;
	unsigned char* hash = new unsigned char[hash_len];
	unsigned char* temp_state = (unsigned char*)state;
	for (int i = 0; i < hash_len; i++) {
		hash[i] = temp_state[i];
	}
	int i = h % 8;
	if(i!=0)hash[hash_len - 1] = (hash[hash_len - 1] >> (8 - i)) << (8 - i);

	if (write) {
		file.seekg(0, std::ios::end);
		file.write((const char*)hash, hash_len);
	}

	file.close();
	this->reset();
	return hash;
}
