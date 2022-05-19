#pragma once

#include <fstream>
#include <stdexcept>
#include <string>

class CubeHash
{
private:
	unsigned int* state;
	unsigned int* tempState;
	int i, r, b, f, h;
public:
	CubeHash(int i, int r, int b, int f, int h);
	unsigned char* hashMessage(unsigned char* msg, int length);
	unsigned char* hashFile(std::string file, bool write);
	unsigned char* hashFile(std::string file);

	void reset();

private:
	void step_1_2_3();
	void step_4();
	void step_5_6_7_8_10();
	void step_9();
	void hash_one_block(unsigned char* msg);
	void round();
};