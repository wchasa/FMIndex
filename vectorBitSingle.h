#pragma once
#include <vector>
#include <bitset>
#define BSize 64
#define SBSize 256


const int BRunlength = ceil(log2(BSize));
const int Bmask = (1 << BRunlength) - 1;
const int SBRunlength = ceil(log2(SBSize));
const int SBmask = (1 << SBRunlength) - 1;
using namespace std;
class vectorBitSingle
{
public:
	~vectorBitSingle();
protected:
	vector<byte> tData;
	int CurrentPos;
public:
	friend class vectorBit;
	vectorBitSingle();
	vectorBitSingle(int sizeInBit);
	vectorBitSingle(int length, byte val);
	void reserve(int input);
	void push_back(const unsigned char* input);
	void push_back(string input);
	int getcapacity() const;
	void vectorBitSingle::push_back(bitset<16> input);
	void push_back(int input);
	void push_back(int count, bool value);
	void push_back(vectorBitSingle input);
	vectorBitSingle copy(int startpos, int count);
	vectorBitSingle copy();
	int size() const;
	void resize(unsigned int newSizeInbit);
	void resizeToRealSize();
	void SetPos(int size);
	int vectorBitSingle::operator[](int i);
	int vectorBitSingle::at(int i);
	vectorBitSingle& vectorBitSingle::operator=(const vectorBitSingle &temp);
};


