#pragma once
#include"vectorBitSingle.h"

class vectorBit
{
public:
private:
	vector<byte> tData;
	int bitcapacity = 1;
	int CurrentPos;//denote this is the CurrentPos,th int the vector
	int TheLogicAndNumberArray[64];
public:
	int getbitcapacity() const;
	vectorBit();
	vectorBit(int bitlength);
	void init(int bitlength);
	void init(int bitlength, int vectorsize);
	void reserve(int length);
	vectorBit(int bitlength, int vectorsize);
	int getcapacity() const;
	inline int getCorrectLengthInput(int input);
	void push_back(UINT64 input);
	inline int getLengthInBit() const;
	vectorBit copy();
	int size() const;
	int sizeOfOccupyMemory() const;
	void resize(unsigned int newSize);
	void resizeToRealSize();
	void SetPos(int size);
	UINT64 vectorBit::operator[](int i);
	UINT64 vectorBit::at(int i);
	void copy(vectorBitSingle& vbsingle, int BitRunlength);
	~vectorBit();
};

