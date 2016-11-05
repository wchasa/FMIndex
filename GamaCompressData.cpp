#include "stdafx.h"
#include "GamaCompressData.h"


GamaCompressData::GamaCompressData()
{
	//gamaHeader.init(3);
	gamaHeader = vectorBitHeader(3);
}

void GamaCompressData::Init(int bitLength)
{

	int SbitrunLength = log2((bitLength<<1)-1);
	int BbitrunLength = BRunlength;
//	SBmask =  (1 << SbitrunLength) - 1;
	
	SBrank = vectorBit(SbitrunLength);
	SB = vectorBit(SbitrunLength);
	B = vectorBit(BbitrunLength);
	Brank = vectorBit(BbitrunLength);
	SBrank.push_back(0);
	Brank.push_back(0);
	SB.push_back(0);
	B.push_back(0);
}

bool GamaCompressData::IsSuperBlock(int pos)
{
	int temp;
	//if(assembly_popcnt(pos)==1)
	//	temp = pos&SBmask;
	//else 
	//	temp = pos%SBSize; 
	//int i = BaisOperate::assembly_popcnt(pos);
	
	temp = pos % SBSize;
	if (temp == 0)
		return true;
	else
		return false;
}

void GamaCompressData::allocatMemeryForVectors(int i)
{
	int SBlength = i / SBSize;
	int Blength = i / BSize;
	SBrank.resize(SBlength);
	SB.resize(SBlength);
	Brank.resize(Blength);
	B.resize(Blength);
	gamacode.resize(i);
	gamaHeader.resize(i);
}

void GamaCompressData::CreateDate(vectorBitSingle& inarray)
{
	if (inarray.size() == 211)
		AtlTrace("123");
	Init(inarray.size());
	allocatMemeryForVectors(inarray.size());
	GAMACode gama;
	//gamaHeader;
	//gamacode;
	gama.Init();

	int i;
	int ranktemp;
	int SBrank_s = 0, SB_s = 0, Brank_s = 0, B_s = 0, SBrank_s_pre = 0, SB_s_pre = 0;
	//int sbLength = inarray.size() >> SBRunlength;
	int sbLength = inarray.size() / SBSize;
	SBrank.reserve(sbLength);
	SB.reserve(sbLength);
	//int bLength = inarray.size() >> BRunlength;
	//int bLength = inarray.size() / BSize;
	//Brank.reserve(bLength);
	//B.reserve(bLength);
	for (i = 0; i < inarray.size();)
	{
		//AtlTrace("%d,", i);
		vectorBitSingle bitetemp(BSize);
		//bitetemp.resize(BSize);
		GAMACode::HEADERTYPE headtemp;
		vectorBitSingle intemp = inarray.copy(i, BSize);
		gama.Encode(intemp, headtemp, bitetemp);
		//AtlTrace("beforeCompress-length:%d,afterCompress-length:%d\n", intemp.size(), bitetemp.size());
		//////////////////////////////////////////////////
		gamaHeader.push_back(static_cast<int>(headtemp));
		gamacode.push_back(bitetemp);
		//////////////////////////////////////////////////
		B_s = bitetemp.size() + B_s;
		if (headtemp == GAMACode::ALL1)
			ranktemp = BSize;
		else if (headtemp == GAMACode::ALL0)
			ranktemp = 0;
		else
		//todo need to change
			ranktemp = BaisOperate::rank1(inarray, i, BSize);
		Brank_s = ranktemp + Brank_s;

		//			AtlTrace("%d\n", Brank_s);
		i += BSize;
		//(pos + 1) & Bmask

		if (!IsSuperBlock(i))
		{
			Brank.push_back(Brank_s - SBrank_s_pre);
			B.push_back(B_s - SB_s_pre);
		}
		else
		{
			SBrank_s_pre = Brank_s;
			SB_s_pre = B_s;
			SBrank.push_back(Brank_s);
			Brank.push_back(Brank_s - SBrank_s_pre);
			SB.push_back(B_s);
			B.push_back(B_s - SB_s_pre);
		}
		SBrank_s += ranktemp;
		SB_s += ranktemp;
	}
	ResizeToRealsize();
	AtlTrace("beforeCompress-length:%d,afterCompress-length:%d\n", inarray.size() >> 3, GetSize());
}

void GamaCompressData::ResizeToRealsize()
{
	gamacode.resizeToRealSize();
	gamaHeader.resizeToRealSize();
	SBrank.resizeToRealSize();
	Brank.resizeToRealSize();
	SB.resizeToRealSize();
	B.resizeToRealSize();
}

int GamaCompressData::GetSize() const
{
	return (gamaHeader.sizeOfOccupyMemory()) + (gamacode.size() >> 3) + SBrank.sizeOfOccupyMemory() + Brank.sizeOfOccupyMemory() + SB.sizeOfOccupyMemory() + B.sizeOfOccupyMemory();
}

GamaCompressData::~GamaCompressData()
{
}
