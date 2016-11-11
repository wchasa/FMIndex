#pragma once
#include <vector>
#include "waveletTreeByBit.h"
#define  SAMPLESTEP 4
#define CSize 257
using namespace std;
class Transform
{
public:
	Transform();

	static int cmp(int* r, int a, int b, int l);
	static void da(unsigned char* r, int* sa, int n, int m);
	static void constructC(unsigned char* T, int* CTable, int length);
	static int constructBWT(unsigned char* T, unsigned char* L, unsigned length, int* sa = nullptr);
//	static int constructBWT(unsigned char* T, unsigned char* L, int length);
	static void ReconstructT(unsigned char* L, int* LF, int I, unsigned char* T, int length);
//	static unsigned char access(waveletTreeByBit& tree, int pos, vector<unsigned char> alphbetVector);
	static int GetExistAlphabet(unsigned char* list, unsigned char* resultlist, int size);
	static void quick_sort(unsigned char* s, int l, int r);
	static void computerLF(int* C, unsigned char* L, unsigned int* LF, int length);

	~Transform();
};

