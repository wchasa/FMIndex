#include "stdafx.h"
#include "vectorBitSingle.h"

#define setbit(x,y) x|=(1<<y) //将X的第Y位置1
#define clrbit(x,y) x&=~(1<<y) //将X的第Y位清0


vectorBitSingle::vectorBitSingle(int sizeInBit): vectorBitSingle()
{
	tData.resize((sizeInBit >> 3) + 1, 0);
}

vectorBitSingle::vectorBitSingle(int length, byte val): vectorBitSingle()
{
	byte val1 = val == 0 ? 0x00 : 0xFF;
	//int i1 = ceil(float(length) / 8);
	int i1 = (length >> 3) + ((length & 0x7) == 0 ? 0 : 1);
	CurrentPos = length;
	vector<byte> temp(i1, val1);
	tData = temp;
	tData.resize((length >> 3) + 1, val1);
}

vectorBitSingle vectorBitSingle::copy(int startpos, int count)
{
	vectorBitSingle temp(count);
	count = CurrentPos > startpos + count ? count : CurrentPos - startpos;
	for (int i = 0; i < count; i++)
		temp.push_back(at(i + startpos));
	return temp;
}

vectorBitSingle vectorBitSingle::copy()
{
	vectorBitSingle temp(CurrentPos);
	for (int i = 0; i < CurrentPos; i++)
		temp.push_back(at(i));
	return temp;
}

int vectorBitSingle::size() const
{
	return CurrentPos;
}

void vectorBitSingle::resize(unsigned newSizeInbit)
{
	tData.resize((newSizeInbit >> 3) + 1);
	//return CurrentPos;
}

void vectorBitSingle::resizeToRealSize()
{
	tData.resize((CurrentPos >> 3) + 1);
	//return CurrentPos;
}

void vectorBitSingle::SetPos(int size)
{
	CurrentPos = size;
}

vectorBitSingle::~vectorBitSingle()
{
}

vectorBitSingle::vectorBitSingle()
{
	CurrentPos = 0;
}
int vectorBitSingle::at(int i){
	if (i < 0 || i >= CurrentPos)
		return 0;
	int currentPosInVectorByte = i >> 3;//
	int currentPosInByte = i & 0x7;//求8的模
	return (tData[currentPosInVectorByte] >> currentPosInByte) & 0x01;
}	
vectorBitSingle& vectorBitSingle::operator=(const vectorBitSingle &temp){
	tData = temp.tData;
	CurrentPos = temp.CurrentPos;
	return *this;;
}



void vectorBitSingle::reserve(int input)
{
	tData.reserve(input >> 3);
}
void vectorBitSingle::push_back(const unsigned char* input)
{
	int i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '1')
			this->push_back(1);
		else if (input[i] == '0')
			this->push_back(0);
		i++;
	}
}
void vectorBitSingle::push_back(bitset<16> input)
{
	//input.reve
	for (int i = 0; i < input.size(); i++)
	{
		push_back(input[input.size() - 1 - i]);
	}
}
void vectorBitSingle::push_back(int input)
{
	int i1 = CurrentPos >> 3;//
	int i2 = CurrentPos & 0x7;//求8的模
	if (i1 + 1 > tData.size())
	{
		tData.push_back(0);
	}
	CurrentPos++;
	tData[i1] = input ? setbit(tData[i1], i2) : clrbit(tData[i1], i2);
}/**
 * \brief push the number of count bits into vectorBitSingle
 * \param count 0 or 1,the value pushed is value
 * \param value the number of bit pushed in
 */
void vectorBitSingle::push_back(int count, bool value)
{
	for (int i = 0; i < count; i++)
		this->push_back(value);

}

void vectorBitSingle::push_back(vectorBitSingle input)
{
	int i1 = CurrentPos >> 3;//
	int i2 = CurrentPos & 0x7;//求8的模
	for (int i = 0; i < input.CurrentPos; i++)
	{
		//if (i2 == 0)
		//{
		//	tData.push_back(0);
		//}
		CurrentPos++;
		tData[i1] = input[i] ? setbit(tData[i1], i2) : clrbit(tData[i1], i2);
		if (i2++ == 7)
		{
			i2 = 0;
			i1++;
		}
	}
}
int vectorBitSingle::getcapacity() const
{
	return tData.capacity();
}

int vectorBitSingle::operator[](int i){
	return at(i);
}