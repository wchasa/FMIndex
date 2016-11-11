#include "stdafx.h"
#include "Transform.h"
#include "divsufsort//divsufsort.h"

Transform::Transform()
{
}

int Transform::cmp(int* r, int a, int b, int l)
{
	return r[a] == r[b] && r[a + l] == r[b + l];
}

void Transform::da(unsigned char* r, int* sa, int n, int m)
{
	//n = n > m ? n : m;
	int* x = new int[n];
	int* y = new int[n];
	int* wv = new int[n > m ? n : m];
	int* ws = new int[n > m ? n : m];
	int i, j, p, *t;
	for (i = 0; i < m; i++) ws[i] = 0;
	for (i = 0; i < n; i++) ws[x[i] = r[i]]++;
	for (i = 1; i < m; i++) ws[i] += ws[i - 1];
	for (i = n - 1; i >= 0; i--)
		sa[--ws[x[i]]] = i;
	for (j = 1 , p = 1; p < n; j *= 2 , m = p)
	{
		for (p = 0 , i = n - j; i < n; i++) y[p++] = i;
		for (i = 0; i < n; i++) if (sa[i] >= j) y[p++] = sa[i] - j;
		for (i = 0; i < n; i++) wv[i] = x[y[i]];
		for (i = 0; i < m; i++) ws[i] = 0;
		for (i = 0; i < n; i++) ws[wv[i]]++;
		for (i = 1; i < m; i++) ws[i] += ws[i - 1];
		for (i = n - 1; i >= 0; i--) sa[--ws[wv[i]]] = y[i];
		for (t = x , x = y , y = t , p = 1 , x[sa[0]] = 0 , i = 1; i < n; i++)
		{
			x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
		}
	}
	delete[] wv;
	delete[] ws;
	delete[] x;
	delete[] y;
	return;
}

void Transform::constructC(unsigned char* T, int* CTable, int length)
{
	int i;
	memset(CTable, 0, CSize * sizeof(int));
	for (i = 0; i < length; i++)
	{
		CTable[T[i] + 1]++;
	}
	for (i = 1; i < CSize; i++)
	{
		CTable[i] += CTable[i - 1];
	}
}

int Transform::constructBWT(unsigned char* T, unsigned char* L, unsigned int length, int* sa)
{
	//	int pos = 0;
	int posofend = 0;
	if (sa==nullptr)
	  sa = new int[length];
	//da(T, sa, length, 256);
	divsufsort(T, sa, length);
	for (int i = 0; i < length; i++)
	{
		//L[i] = T[(sa[i] - 1<0 ? sa[i] - 1 + length : sa[i] - 1) % length];
		if (sa[i] == 0)
		{
			posofend = i;
			L[i] = T[(sa[i] - 1 + length) % length];
		}
		else
			L[i] = T[(sa[i] - 1) % length];
	}
	return posofend;
}

void Transform::ReconstructT(unsigned char* L, int* LF, int I, unsigned char* T, int length)
{
	int i = I;
	for (int k = length - 1; k >= 0; k--)
	{
		T[k] = L[i];
		i = LF[i];
	}
}

//unsigned char Transform::access(waveletTreeByBit& tree, int pos, vector<unsigned char> alphbetVector)
//{
//	//todo
//	return ' ';
//}

int Transform::GetExistAlphabet(unsigned char* list, unsigned char* resultlist, int size)
{
	int result = 0;
	vector<bool> b(256);
	for (int i = 0; i < size; i++)
	{
		if (!b[list[i]])
			resultlist[result++] = (list[i]);

		b[list[i]] = true;
	}
	return result;
}


void Transform::quick_sort(unsigned char* s, int l, int r) 
{
	if (l < r)
	{
		//Swap(s[l], s[(l + r) / 2]); //将中间的这个数和第一个数交换 参见注1  
		int i = l, j = r, x = s[l];
		while (i < j)
		{
			while (i < j && s[j] >= x) // 从右向左找第一个小于x的数  
				j--;
			if (i < j)
				s[i++] = s[j];

			while (i < j && s[i] < x) // 从左向右找第一个大于等于x的数  
				i++;
			if (i < j)
				s[j--] = s[i];
		}
		s[i] = x;
		quick_sort(s, l, i - 1); // 递归调用   
		quick_sort(s, i + 1, r);
	}
}

void Transform::computerLF(int* C, unsigned char* L, unsigned int* LF, int length)
{
	int i;
	LF[0] = C[L[0]];
	for (i = 1; i < length; i++)
	{
		ATLTRACE("i = %d,C[L[i]] = %d, BaisOperate::rank1(L[i], i)) = %d\n", i, C[L[i]], BaisOperate::rank1(L, i));
		LF[i] = (C[L[i]] + BaisOperate::rank1(L, i)) % length;
	}
}


Transform::~Transform()
{
}
