#pragma once
#include "vectorBitSingle.h"
#include "vectorBit.h"
#include "BaisOperate.h"
#include "GAMACode.h"

class GamaCompressData
{
public:
	typedef  vectorBit vectorBitHeader;
	vectorBitHeader gamaHeader;
	vectorBitSingle	gamacode;
	vectorBit		SBrank;
	vectorBit		Brank;
	vectorBit		SB;
	vectorBit		B;
	 int SBmask;
	GamaCompressData();
	void Init(int bitLength);
	bool IsSuperBlock(int pos);
	void allocatMemeryForVectors(int i);
	void CreateDate(vectorBitSingle& inarray);
	void ResizeToRealsize();
	int GetSize() const;
	~GamaCompressData();
	};
	


