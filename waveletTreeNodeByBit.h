#pragma once
#include "vectorBitSingle.h"
#include "GamaCompressData.h"
#include <map>

class waveletTreeNodeByBit
{
public:
	vectorBitSingle tData;
	map<unsigned char, int> allist;
	char ch;
	GamaCompressData GamaData;
	waveletTreeNodeByBit *l, *r, *p;
	waveletTreeNodeByBit();
	waveletTreeNodeByBit(waveletTreeNodeByBit& parentNode);
	~waveletTreeNodeByBit();
	CString showNodeData();
};

