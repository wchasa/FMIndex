// FM_Index.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <time.h>
#include "Transform.h"
using namespace std;
#define SIZE 1024
/*
int _tmain(int argc, _TCHAR* argv[])
{
	CString str;
	waveletTreeByBit* tree = new waveletTreeByBit();
	unsigned char* alphbetList = new unsigned char[256];
	FILE* fp;
	//unsigned char* T = new unsigned char[21]{'a', 's', 'a', 'k', 'a', 'k', 'r', 'h', 'a', 'k', 'a', 'k', 'r', 'h', 'a', 'k', 'a', 's', 'a', 'k', '#'};
	//int length  =21;

	const char* strpath = "E:\\测试数据\\测试数据\\normal\\mybook1";
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
	while (ipos!=-1)
	{
		printf("pos=%d,", ipos);
		ipos = str.Find(strpatten, ipos + 1);
	}
	tree->proccessForCounstructWaveletTree(list, count);
	tuple<int, int> postuple = tree->count("the");
	if (get<0>(postuple) != -1)
	{
		auto i = tree->locate(postuple);
		//printf("bug = %c", get<0>(postuple), get<1>(postuple));
		printf("\nl=%d,r=%d\n", get<0>(postuple), get<1>(postuple));
		printf("using wavelet\n");
		for (int i1 = 0; i1 < i.size(); i1++)
			printf("pos=%d,", i[i1]);
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
*/

int main()
{
	CString str;
	waveletTreeByBit* tree = new waveletTreeByBit();
	unsigned char* alphbetList = new unsigned char[256];
	FILE* fp;
	//unsigned char* T = new unsigned char[21]{'a', 's', 'a', 'k', 'a', 'k', 'r', 'h', 'a', 'k', 'a', 'k', 'r', 'h', 'a', 'k', 'a', 's', 'a', 'k', '#'};
	//int length  =21;

	const char* strpath = "E:\\测试数据\\测试数据\\normal\\mybook1";
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
	while (ipos != -1)
	{
		printf("pos=%d,", ipos);
		ipos = str.Find(strpatten, ipos + 1);
	}
	tree->proccessForCounstructWaveletTree(list, count);
	waveletTreeNodeByBit* w = tree->getRoot()->r->l;
	CString str2 =w->showNodeData();
	AtlTrace(str2);
	int i1 =tree->RankOFGama('e', 122);
	int i2 = tree->Rank('e', 122);
	int i3 = BaisOperate::StupidRank(tree->getBWT(), count, 'e', 122);
	for (int i = 0; i < count;i++)
	{
		if (tree->Rank('e', i) != tree->RankOFGama('e', i))
			printf("pos=%d,", i);
	}
	
}