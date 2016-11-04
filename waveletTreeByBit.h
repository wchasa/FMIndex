#pragma once
#include "stdafx.h"
#include <vector>
#include"waveletTreeNodeByBit.h"
#include <map>
#include "BaisOperate.h"
#include "GamaCompressData.h"
#include "GAMACode.h"
#include "vectorBitSingle.h"
#include "Transform.h"
using namespace std;
class waveletTreeByBit
{
private:
	waveletTreeNodeByBit* root;
	unsigned int* SASample;
	unsigned int* LF;
	int* CTable;
	int Length;
	unsigned char* BWT;
public:

	waveletTreeByBit();
	waveletTreeByBit(int alphbetCount);
	unsigned char* getBWT();
	waveletTreeNodeByBit* getRoot() const;
	void computerLF(int* C, unsigned char* L, unsigned* LF, int length);
	void proccessForCounstructWaveletTree(unsigned char* inarray, int length);
	void CounstructWaveletTree(const vector<unsigned char> inarray, const vector<unsigned char> alphbetList, waveletTreeNodeByBit& wt) const;
	static bool ContainChar(const map<unsigned char, int>& allist, unsigned char c);
	unsigned char Access(const int& pos) const;
	tuple<int, int> count(string Patten);
	int Rank(const unsigned char c, const int& pos) const;
	int RankOFGama(const unsigned char c, const int& pos) const;
	static int rankOfCurrentGama(GamaCompressData& GamaData, const int& pos );
	static int lrank(vectorBitSingle s, int offset, int headertype, int mount);
	int Select(const unsigned char c, const int& pos) const;
	static int calculateGamaCodeSize(waveletTreeNodeByBit& wt);
	void destory(waveletTreeNodeByBit* child, waveletTreeNodeByBit* parent);
	vector<unsigned int> locate(tuple<int, int> rangeLtoR);
	unsigned getpos2(int pos);

	~waveletTreeByBit();
};

