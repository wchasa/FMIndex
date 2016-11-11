// FM_Index.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <time.h>
#include <algorithm>  
#include "Transform.h"
using namespace std;
#define SIZE 1024
int main9()
{
	CString str;
	waveletTreeByBit* tree = new waveletTreeByBit();
	unsigned char* alphbetList = new unsigned char[256];
	unsigned char* T = new unsigned char[21]{'a', 's', 'a', 'k', 'a', 'k', 'r', 'h', 'a', 'k', 'a', 'k', 'r', 'h', 'a', 'k', 'a', 's', 'a', 'k', '#'};
	int length = 21;
	int ii = 0;
	tree->proccessForCounstructWaveletTree(T, length);
	for (ii = 2; ii < length; ii++)
	{
		if (tree->SA[ii] != tree->getpos2(ii))
			printf("wrong pos=%d\n", ii);
	}
	return 0;
}
int _tmain(int argc, _TCHAR* argv[])
{
	CString str;
	waveletTreeByBit* tree = new waveletTreeByBit();
	unsigned char* alphbetList = new unsigned char[256];
	FILE* fp;
	//const char* strpath = "E:\\测试数据\\测试数据\\normal\\mybook1";
   //const char* strpath = "J:\\测试数据\\small\\book1";
	const char* strpath = "J:\\测试数据\\normal\\dna";
	errno_t err;
	if (fopen_s(&fp, strpath, "r"))
	{
		printf("The file %s is not exist.", strpath);
		return 0;
	}
	err = fseek(fp, 0L, SEEK_END);
	long size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	size = size < SIZE ? size : SIZE;
	unsigned char* list = new unsigned char[size];
	
	long count = fread(list, sizeof(char), size, fp);
	str = list;
	auto strpatten = _T("AA");
	int ipos = str.Find(strpatten);
	vector<int> strvector;
	printf("using string\n");
	while (ipos!=-1)
	{
		printf("pos=%d,", ipos);
		strvector.push_back(ipos);
		ipos = str.Find(strpatten, ipos + 1);
	}
	tree->proccessForCounstructWaveletTree(list, count);
	int ii = 0;
	int pos = 0;
	tuple<int, int> postuple = tree->count("AA");
	printf(" \n");
	for (ii = 54; ii < count; ii++)
	{
		if (tree->SA[ii]!=tree->getpos2(ii))
			printf("wrong pos=%d\n", ii);
	}
	printf(" \n");
	//for (int i2 = 0; i2 < 100; i2++)
	//{
	//	printf("i=%d,sa = %d,LF=%d", i2, tree->SA[i2], tree->LF[i2]);
	//	for (int tt = 0; tt < 10; tt++)
	//		printf(" %c", list[(tree->SA[i2] + tt) % count]);
	//	printf(" \n");
	//}
	//auto iii = tree->getpos2(2);
	if (get<0>(postuple) != -1)
	{
		auto i = tree->locate(postuple);
		//printf("bug = %c", get<0>(postuple), get<1>(postuple));
		printf("\nl=%d,r=%d\n", get<0>(postuple), get<1>(postuple));
		sort(i.begin(), i.end());
		printf("using wavelet\n");
		for (int i1 = 0; i1 < i.size(); i1++)
			printf("pos=%d,", i[i1]);
			/*if (i[i1] != strvector[i1])
				printf("pos=%d,", i1);*/
	}
}
int _tmain33(int argc, _TCHAR* argv[])
{
	clock_t start, end;
	clock_t startall, endall;
	double duration;
	FILE* fp;
	unsigned char* alphbetList = new unsigned char[256];
	int CTable[CSize];
	//vector<int> CTable(CSize,0);
	int posOfend;
	//unsigned char* T = new unsigned char[21]{'a','s','a','k','a','k','r','h','a','k','a','k','r','h','a','k','a','s'
	const char* strpath = "E:\\测试数据\\测试数据\\normal\\\para";
	//TCHAR* strpath = _T("E:\\测试数据\\测试数据\\english");
	errno_t err;
	//err = fopen_s(&fp, strpath, "r");
	if (fopen_s(&fp, strpath, "r"))
	{
		printf("The file %s is not exist.", strpath);
		return 0;
	}
	// ReSharper disable once CppEntityNeverUsed
	err = fseek(fp, 0L, SEEK_END);

	long size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	size = size < SIZE ? size : SIZE;
	unsigned char* list = new unsigned char[size];
	long count = fread(list, sizeof(char), size, fp);
	//unsigned char* inarray = new int[size];
	printf("File Name ;%s,\nFile Size :%d M\n", strpath, count / 1024 / 1024);
	//unsigned char* list = new unsigned char[size];
	std::vector<unsigned char> Tvector;
	unsigned char* T2 = new unsigned char[size];
	const int length = size;
	unsigned char* BWT = new unsigned char[length];
	//vector<unsigned char> BWT(length,0);
	int* LF = new int[length];
	start = clock();
	startall = clock();
	posOfend = Transform::constructBWT(list, BWT, length);
	end = clock();
	duration = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	printf("durationOF constructBWT %f\n", duration);
	start = clock();
	//vector<unsigned char> listvector(list, count + list);
	Transform::constructC(list, CTable,length);
	end = clock();
	duration = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	//printf("durationOF constructC %f\n", duration);
	start = clock();
	//computerLF(CTable, BWT, LF, length);
	end = clock();
	duration = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	printf("durationOF computerLF %f\n", duration);
	start = clock();
	//ReconstructT(BWT, LF, posOfend, T2,length);
	end = clock();
	duration = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	//printf("durationOF ReconstructT %f\n", duration);
	int alCount = Transform::GetExistAlphabet(list, alphbetList, length);
	Transform::quick_sort(alphbetList, 0, alCount - 1);
	waveletTreeByBit* tree = new waveletTreeByBit();
	vector<unsigned char> alphbetVector(alphbetList, alphbetList +alCount);
	vector<unsigned char> BWTvector(BWT, BWT + length);
	start = clock();
	tree->CounstructWaveletTree(BWTvector, alphbetVector, *tree->getRoot());
	end = clock();
	endall = clock();
	duration = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	printf("durationOF CounstructWaveletTree %f\n", duration);
	duration = static_cast<double>(endall - startall) / CLOCKS_PER_SEC;
	printf("durationOF ALlProcess %f\n", duration);
	auto node = tree->getRoot();

	int size1 = waveletTreeByBit::calculateGamaCodeSize(*node);
	duration = static_cast<double>(size1 / length);
	printf("durationOF ALlProcess %f\n", duration);
	double per = static_cast<double>(size1) / static_cast<double>(length);
	printf("new size is  %d\n,old is %d\n,%f\n", size1, length, per);
	return 0;
}


int main11()
{
	CString str;
	waveletTreeByBit* tree = new waveletTreeByBit();
	unsigned char* alphbetList = new unsigned char[256];
	FILE* fp;
//	unsigned char* T = new unsigned char[21]{'a', 's', 'a', 'k', 'a', 'k', 'r', 'h', 'a', 'k', 'a', 'k', 'r', 'h', 'a', 'k', 'a', 's', 'a', 'k', '#'};
//	int length  =21;

	const char* strpath = "J:\\测试数据\\small\\book1";
	//TCHAR* strpath = _T("E:\\测试数据\\测试数据\\english");
	errno_t err;
	//	err = fopen_s(&fp, strpath, "r");
	if (fopen_s(&fp, strpath, "r"))
	{
		printf("The file %s is not exist.", strpath);
		return 0;
	}
	// ReSharper disable once CppEntityNeverUsed
	err = fseek(fp, 0L, SEEK_END);
	long size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	size = size < SIZE ? size : SIZE;
	unsigned char* list = new unsigned char[size];

	long count = fread(list, sizeof(char), size, fp);
	str = list;
	auto strpatten = _T("the");
	int ipos = str.Find(strpatten);
	printf("using string\n");
	vector<int> strvector,waveletvector;
	while (ipos != -1)
	{
		printf("pos=%d,", ipos);
		strvector.push_back(ipos);
		ipos = str.Find(strpatten, ipos + 1);
	}
	tree->proccessForCounstructWaveletTree(list, count);
	for (int ii = 0; ii < count; ii++)
		if (tree->BWT[ii] != list[tree->SA[tree->LF[ii]]])
			AtlTrace("Wrong pos %d\n",ii);
	waveletTreeNodeByBit* w = tree->getRoot()->r;
	CString str2 =w->showNodeData();
	AtlTrace(str2);
	int i1 =tree->RankOFGama('e', 209);
	int i2 = tree->Rank('e', 209);
//	int i3 = Transform::computerLF(tree->BWT,)
//	int i3 = BaisOperate::StupidRank(tree->getBWT(), count, 'e', 209);
//	int i4 =tree->rankOfCurrentGama(w->GamaData, 137);
//	int i5 = BaisOperate::rank1(w->tData, 137);

	
}