#pragma once
class CubeHash
{
private:
	unsigned int* state;
	unsigned int* tempState;
	int i, r, b, f, h;
public:
	CubeHash(int i, int r, int b, int f, int h);
	unsigned char* hashMessage(unsigned char* msg, int length);

	void reset();

private:
	void step_1_2_3();
	void step_4();
	void step_5_6_7_8_10();
	void step_9();
	void hash_one_block(unsigned char* msg);
	void round();
};