#pragma once
#include"vectorBitSingle.h"
class BaisOperate
{//todo rank need to change to popcount
public:
	BaisOperate();
	~BaisOperate();
public:
	static int assembly_popcnt(unsigned int n);
	static int StupidRank(unsigned char* inarray, int length, unsigned char c, int pos);
	static int rank1(vectorBitSingle inarray, int pos);
	static int rank1(vectorBitSingle& inarray, int startpos, int mount);
	static int rank1(vector<unsigned char> L, int size);
	static int rank1(unsigned char* L, int size);
	static int GetRvalue(int i, int itemID);
};
