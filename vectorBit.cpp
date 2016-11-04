#include "stdafx.h"
#include "vectorBit.h"


vectorBit::vectorBit(int bitlength): vectorBit()
{
	//bitcapacity = 1;
	bitcapacity = bitlength;
}

void vectorBit::init(int bitlength)
{
	bitcapacity = bitlength;
}

void vectorBit::init(int bitlength, int vectorsize)
{
	init(bitlength);
	tData.resize(((getLengthInBit()) >> 3) + 1, 0);
}

void vectorBit::reserve(int length)
{
	tData.reserve(((getLengthInBit()) >> 3) + 1);
}

vectorBit::vectorBit(int bitlength, int vectorsize): vectorBit(bitlength)
{
	tData.resize(((getLengthInBit()) >> 3) + 1, 0);
}

int vectorBit::getcapacity() const
{
	//(tData.capacity() << 3) / bitcapacity)
	return ((tData.capacity() << 3) / bitcapacity) + ((tData.capacity() << 3) % bitcapacity == 0 ? 0 : 1);
}

int vectorBit::getCorrectLengthInput(int input)
{
	return input & TheLogicAndNumberArray[bitcapacity];
}

void vectorBit::push_back(UINT64 input)
{
	input = getCorrectLengthInput(input);
	int currentPosInVectorByte = getLengthInBit() >> 3;
	int currentPosInByte = getLengthInBit() & 0x7;
	byte lowByte = input & TheLogicAndNumberArray[8 - currentPosInByte];
	int size = tData.size();
	for (; getLengthInBit() + bitcapacity >= size << 3; size++)
	{
		tData.push_back(0);
	}
	tData[currentPosInVectorByte] = tData[currentPosInVectorByte] | (lowByte << currentPosInByte);
	currentPosInVectorByte++;
	input = input >> (8 - currentPosInByte);
	int i = 8 - currentPosInByte;//i denote the mount of bit pushed into the vector;
	for (; i < bitcapacity; i += 8)
	{
		tData[currentPosInVectorByte++] = input & TheLogicAndNumberArray[8];
		input = input >> 8;
	}
	//currentPosInByte = ((bitcapacity & 0x07) + currentPosInByte) & 0x07;//new 
	CurrentPos++;
}

int vectorBit::getLengthInBit() const
{
	return CurrentPos * bitcapacity;
}

vectorBit vectorBit::copy()
{
	vectorBit temp(CurrentPos);
	for (int i = 0; i < CurrentPos; i++)
		temp.push_back(at(i));
	return temp;
}

int vectorBit::size() const
{
	return CurrentPos;
}

int vectorBit::sizeOfOccupyMemory() const
{
	return tData.size();
}

void vectorBit::resize(unsigned newSize)
{
	tData.resize(((newSize * bitcapacity) >> 3) + 1);
}

void vectorBit::resizeToRealSize()
{
	tData.resize((getLengthInBit() >> 3) + 1);
}

void vectorBit::SetPos(int size)
{
	CurrentPos = size;
}

int vectorBit::getbitcapacity() const
{
	return bitcapacity;
}

vectorBit::vectorBit(): CurrentPos(0)
{
	for (int i = 0; i < 64; i++)
		TheLogicAndNumberArray[i] = (1 << i) - 1;
}

void vectorBit::copy(vectorBitSingle& vbsingle, int BitRunlength)
{
	tData = vbsingle.tData;
	CurrentPos = (vbsingle.size() + BitRunlength - 1) / BitRunlength;
	bitcapacity = BitRunlength;
}

vectorBit::~vectorBit()
{
}
UINT64 vectorBit::at(int i)
{
	if (i < 0 || i >= CurrentPos)
		return 0;

	UINT64 result;
	int highPosInbit = i*bitcapacity + bitcapacity;
	int currentPosInVectorByte = (highPosInbit) >> 3;
	int currentPosInByte = (highPosInbit & 0x7);
	int Length = currentPosInByte;
	int movebitPace = Length > bitcapacity ? Length - bitcapacity : 0;
	result = (tData[currentPosInVectorByte--]) & TheLogicAndNumberArray[Length];
	result = result >> movebitPace;
	int mountsOfPushIntoResult = Length;//mountsOfPushIntoResult denote the mount of bit pushed into the vector;
	for (; mountsOfPushIntoResult < bitcapacity;)
	{
		movebitPace = mountsOfPushIntoResult <bitcapacity - 8 ? 8 : bitcapacity - mountsOfPushIntoResult;
		result = result << movebitPace;
		result += (tData[currentPosInVectorByte] >> (8 - movebitPace)) & TheLogicAndNumberArray[movebitPace];
		--currentPosInVectorByte;
		mountsOfPushIntoResult += movebitPace;
	}
	return 	result;
}
UINT64 vectorBit::operator[](int i){
	return at(i);
}