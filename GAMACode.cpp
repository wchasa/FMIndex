#include "stdafx.h"
#include "GAMACode.h"
#include <tuple>
#include "BaisOperate.h"


void GAMACode::EncodeSingle(vectorBitSingle& outarray, int Length)
{
	//todo first
	//int i;
	//int size = log2(Length) + 1;
	outarray.push_back(GamaCodeToBitVector[Length]);
}

vectorBitSingle GAMACode::EncodeSingle(const int& RunLength)
{

	int i;

	int size = log2(RunLength) + 1;
	vectorBitSingle outarray(size << 1);
	for (i = 0; i < size - 1; i++)
	{
		outarray.push_back(0);
	}
	for (i = 0; i < size; i++)
	{
		int t = (RunLength >> (size - i - 1)) & 0x01;
		outarray.push_back(t);
	}
	//AtlTrace("beforeCompress-length:%d,afterCompress-length:%d\n", RunLength, size * 2 -1);
	return outarray;
}
void GAMACode::Encode(vectorBitSingle inarray, HEADERTYPE& header, vectorBitSingle& Outvector)
{
	//AtlTrace("-------------------\n");
	if (inarray.size() < 1)
		return;
	int compareNum = inarray[0];
	if (compareNum == 1)
		header = RLG1;
	else
		header = RLG0;
	int count = 1;
	for (int i = 1; i < inarray.size(); i++)
	{
		if (inarray[i] == compareNum)
			count++;
		else
		{
			EncodeSingle(Outvector, count);
			count = 1;
			compareNum = inarray[i];

		}
		if (inarray.size() <= Outvector.size())
		{
			header = Plain;
			Outvector.SetPos(0);
			Outvector = inarray.copy();
			return;
		}
	}
	if (count == inarray.size())//ALL 0/1
	{
		header = header == RLG1 ? ALL1 : ALL0;
		Outvector.SetPos(0);
		return;
	}
	EncodeSingle(Outvector, count);
	//mount.push_back(count);
	if (inarray.size() < Outvector.size())//plain
	{
		header = Plain;
		Outvector.SetPos(inarray.size());
		Outvector = inarray.copy();
	}

}
//tuple<int, int, int, int> GetLookupTableElement(vectorBitSingle& inarray, HEADERTYPE& header, int length)
//{
//	int r1, r2, r3, r4;
//	switch (header)
//	{
//		case HEADERTYPE::Plain:
//			r1 = 0; r2 = 0; r3 = 16; r4 = BaisOperate::rank1(inarray, inarray.size());
//			break;
//
//	}
//	tuple<int, int, int, int> result(r1, r2, r3, r4);
//	return result;
//}
tuple<int, int, int, int> GAMACode::Decode(vectorBitSingle& inarray, const HEADERTYPE& header, vectorBitSingle& Outvector, int length)
{
	int r1 = 0, r2 = 0, r3 = 0, r4 = 0;
	int PrePos = 0;
	bool bval;
	//const int compareNum =0;
	int count0 = 0;
	switch (header)
	{
	case HEADERTYPE::Plain:
		r1 = 0; r2 = 0; r3 = 16; r4 = BaisOperate::rank1(inarray, inarray.size());
		Outvector = inarray;
		break;
	case HEADERTYPE::RLG0:
	case HEADERTYPE::RLG1:
		bval = HEADERTYPE::RLG0 == header ? false : true;
		for (int i = 0; i + count0 < inarray.size();)
		{
			if (inarray[i++] == 0)
				count0++;
			else
			{
				//todo wodo
				count0++;
				int mount = 1;
				for (int j = 0; j < count0 - 1 & i< inarray.size(); j++)
				{
					mount = (mount << 1) + inarray[i++];
				}
				if (bval)
				{
					r4 += mount;
				}
				r2 += mount;
				r3 = i;
				r1++;
				//	AtlTrace("mount = %d\n", mount);
				Outvector.push_back(mount, bval);
				bval = bval ? false : true;
				PrePos = i;
				count0 = 0;

			}
		}
		break;
	case HEADERTYPE::ALL0:
		r1 = 0; r2 = 0; r3 = 0; r4 = 0;
		Outvector = *(new vectorBitSingle(length, 0));
		break;
	case HEADERTYPE::ALL1:
		r1 = 0; r2 = 16; r3 = 16; r4 = 8;
		Outvector = *(new vectorBitSingle(length, 1));
		break;
	default: break;
	}
	tuple<int, int, int, int> result(r1, r2, r3, r4);
	return result;
}


void GAMACode::GenerateGamaCodeToBitVector()
{
	if (GamaCodeToBitVector.size() > 0)
		return;
	GamaCodeToBitVector.push_back(EncodeSingle(1));
	for (int i = 1; i <= BSize; i++)
		GamaCodeToBitVector.push_back(EncodeSingle(i));
}

void GAMACode::GeneratelookupTableOfR()
{
	if (lookupTableOfR.size() > 0)
		return;
	int looptimes = 1 << 16;
	lookupTableOfR.reserve(looptimes);
	for (int i = 0; i <= looptimes; i++)
	{
		vectorBitSingle vbSingle;
		vbSingle.push_back(bitset<16>(i));
		vectorBitSingle out;
		tuple<int, int, int, int> RvalueTuple = Decode(vbSingle, GAMACode::RLG1, out, BSize);
		int rvale = ((get<0>(RvalueTuple) & 0x01) << 23) | ((get<2>(RvalueTuple) & 0xff) << 16) | ((get<1>(RvalueTuple) & 0xff) << 8) | (get<3>(RvalueTuple) & 0xff);
		lookupTableOfR.push_back(rvale);
		//GamaCodeToBitVector.push_back(Decode());
	}
}
vector<vectorBitSingle> GAMACode::GamaCodeToBitVector;
vector<int> GAMACode::lookupTableOfR;
void GAMACode::Init()
{
	GeneratelookupTableOfR();
	GenerateGamaCodeToBitVector();
}

GAMACode::~GAMACode()
{
}

