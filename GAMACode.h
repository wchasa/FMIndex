#pragma once
#include "vectorBitSingle.h"

class GAMACode
{
public:

	static vector<vectorBitSingle> GamaCodeToBitVector;
	static vector<int> lookupTableOfR;
public:
	enum HEADERTYPE{ Plain, RLG0, RLG1, ALL0, ALL1 };
	static void EncodeSingle(vectorBitSingle& outarray, int Length);
	static vectorBitSingle EncodeSingle(const int& Length);
	static void Encode(vectorBitSingle inarray, HEADERTYPE& header, vectorBitSingle& Outvector);
	static tuple<int, int, int, int> Decode(vectorBitSingle& inarray, const HEADERTYPE& header, vectorBitSingle& Outvector, int length);
	static void GenerateGamaCodeToBitVector();
	static void GeneratelookupTableOfR();
	static void Init();
	~GAMACode();
};

