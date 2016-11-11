#include "stdafx.h"
#include "BaisOperate.h"


BaisOperate::BaisOperate()
{
}


BaisOperate::~BaisOperate()
{
}

int ::BaisOperate::StupidRank(unsigned char* inarray, int length, unsigned char c, int pos)
{
	pos = length > pos ? pos : length;
	int icount = 0;
	for (int i = 0; i <= pos; i++)
		if (inarray[i] == c)
			icount++;
	return icount;
}

int ::BaisOperate::assembly_popcnt(unsigned n)
{
#ifdef _MSC_VER /* Intel style assembly */
	__asm popcnt eax, n;
#elif __GNUC__ /* AT&T style assembly */
		__asm__("popcnt %0,%%eax"::"r"(n));
#else
# error "which assembly style does your compiler support, Intel or AT&T?"
#endif
}

int ::BaisOperate::rank1(vectorBitSingle inarray, int pos)
{
	int count = 0;
	pos = pos < inarray.size() ? pos : inarray.size();
	for (int i = 0; i <= pos; i++)
		if (inarray[i] == 1)
			count++;
	return count;
}

int ::BaisOperate::rank1(vectorBitSingle& inarray, int startpos, int mount)
{
	//ranksize = ranksize < inarray.size() ? inarray.size() : ranksize;
	int count = 0;
	int endpos = startpos + mount;
	endpos = endpos < inarray.size() ? endpos : inarray.size();
	for (int i = startpos; i < endpos; i++)
	{
		if (inarray[i] == 1)
			count++;
	}
	return count;
}

int ::BaisOperate::rank1(vector<unsigned char> L, int size)
{
	int icount = 0;
	for (int i = 0; i < size; i++)
	{
		if (L[i] == L[size])
			icount++;
	}
	return icount;
}

int ::BaisOperate::rank1(unsigned char* L, int pos)
{
	int icount = 0;
	for (int i = 0; i < pos; i++)
	{
		if (L[i] == L[pos])
			icount++;
	}
	return icount;
}

int ::BaisOperate::GetRvalue(int i, int itemID)
{
	int result = 0;
	if (itemID == 1)
		result = (i >> 23) & 0x01;
	else if (itemID == 2)
		result = (i >> 16) & 0x10;
	else if (itemID == 1)
		result = (i >> 8) & 0xFF;
	else if (itemID == 0)
		result = (i) & 0xFF;

	return result;
}
