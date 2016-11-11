#include "stdafx.h"
#include "waveletTreeByBit.h"
#include "Transform.h"


waveletTreeByBit::waveletTreeByBit(int alphbetCount): waveletTreeByBit()
{
	//layer = (int)ceil(float(log2(alphbetCount))) + 1;
}

unsigned char* waveletTreeByBit::getBWT()
{
	return  BWT;
}

waveletTreeNodeByBit* waveletTreeByBit::getRoot() const
{
	return root;
}

void waveletTreeByBit::computerLF(int* C, unsigned char* L, unsigned* LF, int length)
{
	int i;
	LF[0] = C[L[0]];
//	int start = RA[0];

//	LF[start] = 0;
	for (i = 0; i < length; i++)
	{
		int temp = (i - 1 >= 0) ? (i - 1) : (i + length - 1);
		LF[RA[i]] = RA[temp];
		//ATLTRACE("i = %d,C[L[i]] = %d, Rank(L[i], i)) = %d\n",i, C[L[i]], Rank(L[i], i));
		//LF[i] = (C[L[i]] + Rank(L[i], i-1)) % length;
	}
}

void waveletTreeByBit::proccessForCounstructWaveletTree(unsigned char* inarray, int length)
{
	//CTable[CSize];
	Length = length;
	SA = new int[length];
	RA = new int[length];
	CTable = new int[CSize];
	SASample = new unsigned int[length / SAMPLESTEP];
	LF = new unsigned int[length];
	unsigned char* alphbetList = new unsigned char[256];
	BWT = new unsigned char[length];
	auto posOfend = Transform::constructBWT(inarray, BWT, length,SA );
	
	int alCount = Transform::GetExistAlphabet(inarray, alphbetList, length);
	Transform::quick_sort(alphbetList, 0, alCount - 1);
	Transform::constructC(inarray, CTable, length);
	//Transform::computerLF(CTable, BWT, LF, length);
	vector<unsigned char> alphbetVector(alphbetList, alphbetList + alCount);
	vector<unsigned char> BWTvector(BWT, BWT + length);
	this->CounstructWaveletTree(BWTvector, alphbetVector, *this->getRoot());
	for (int i = 0; i < length; i++)
	{
		RA[SA[i]] = i;
	}
	computerLF(CTable, BWT, LF, length);
	for (int i = 0; i < length / SAMPLESTEP; i++)
	{
		SASample[i] = SA[i*SAMPLESTEP];
	}
	

}
void waveletTreeByBit::CounstructWaveletTree(const vector<unsigned char> inarray, const vector<unsigned char> alphbetList, waveletTreeNodeByBit& wt) const
{
	//map<unsigned char, int> allist;
	unsigned int i;
	int icount = 0;
	wt.tData.resize(inarray.size());
	vector<unsigned char> lCharArray, rCharArray;
	typedef pair<unsigned char, int> In_Pair;
	if (alphbetList.size() > 1)
	{
		int countlevel = ((alphbetList.size()+1) / 2);
		for (i = 0; i < countlevel; i++)
			wt.allist.insert(In_Pair(alphbetList[i], 0));
		vector<unsigned char> lalphbetList(alphbetList.begin(), alphbetList.begin() + i);
		vector<unsigned char> ralphbetList(alphbetList.begin() + i, alphbetList.end());
		for (; i < alphbetList.size(); i++)
			wt.allist.insert(In_Pair(alphbetList[i], 1));
		for (i = 0; i < inarray.size(); i++)
			if (wt.allist[inarray[i]] == 0)
			{
				wt.tData.push_back(0);
				lCharArray.push_back(inarray[i]);
			}
			else
			{
				wt.tData.push_back(1);
				rCharArray.push_back(inarray[i]);
			}
		wt.GamaData.CreateDate(wt.tData);
		/*if (wt.GamaData.gamacode.size() == 477)
		AtlTrace("here");*/
		wt.GamaData.ResizeToRealsize();
		wt.l = new waveletTreeNodeByBit(wt);
		wt.r = new waveletTreeNodeByBit(wt);
		icount++;
		CounstructWaveletTree(lCharArray, lalphbetList, *wt.l);
		CounstructWaveletTree(rCharArray, ralphbetList, *wt.r);
	}
	else
	{
		wt.allist.insert(In_Pair(alphbetList[0],1));
		vectorBitSingle vector(static_cast<int>(inarray.size()), '1');
		wt.tData = vector;
		wt.ch = inarray[0];
	}
}

bool waveletTreeByBit::ContainChar(const map<unsigned char, int>& allist, unsigned char c)
{
	if (allist.find(c) == allist.end())
		return false;
	else
		return true;
}

unsigned char waveletTreeByBit::Access(const int& pos) const
{
	//		unsigned char  ch;
	int ipos = pos;
	waveletTreeNodeByBit* nodetemp = root;
	while (true)
	{
		if (nodetemp->tData[ipos] == 0)
		{
			ipos = ipos - BaisOperate::rank1(nodetemp->tData, ipos);
			if (nodetemp->l != nullptr)
				nodetemp = nodetemp->l;
			else
				break;
		}
		else
		{
			ipos = BaisOperate::rank1(nodetemp->tData, ipos);
			if (nodetemp->r != nullptr)
				nodetemp = nodetemp->r;
			else
				break;
		}
	}

	return nodetemp->ch;
}
//tuple<int, int> waveletTreeByBit::count(vector<unsigned char> Patten, vector<int> Ctable)
//{
//	int i = Patten.size() - 1;
//	unsigned char c = Patten[i];
//	int l = Ctable[i];
//	int r = Ctable[i+1]-1;
//	while ((l<=r) && (i>=1))
//	{
//		i--;
//		c = Patten[i];
//		l = Ctable[c] + Rank(c, l - 1);
//		l = Ctable[c] + Rank(c, r)-1;
//	}
//	if (l>r)
//	{
//		l = -1; r = -1;
//	}
//	tuple<int, int> result(l,r);
//	return result;
//		
//}
tuple<int, int> waveletTreeByBit::count(string Patten/*, int* Ctable*/)
{
	int i = Patten.size() - 1;
	unsigned char c = Patten[i];
	int l = CTable[c];
	int r = CTable[c + 1] - 1;
	while ((l <= r) && (i >= 1))
	{//todo need change
		i--;
		c = Patten[i];
		l = CTable[c] + RankOFGama(c, l - 1);
		r = CTable[c] + RankOFGama(c, r) - 1;
		//l = CTable[c] + Rank(c, l - 1);
		//r = CTable[c] + Rank(c, r) - 1;
	}
	if (l>r)
	{
		l = -1; r = -1;
	}
	tuple<int, int> result(l, r);
	return result;

}
int waveletTreeByBit::Rank(const unsigned char c, const int& pos) const
{
	//AtlTrace("Start Rank: now pos =%d,c=%c\n", pos,c);
	waveletTreeNodeByBit* nodetemp = root;
	if (!ContainChar(nodetemp->allist, c))
		return -1;
	int ipos = pos;
	//typedef pair <unsigned char, int> In_Pair;
	while (nodetemp->l != nullptr)
	{
		//Divedepos = i;

		if (nodetemp->allist[c] == 0)
		{
			ipos = ipos - BaisOperate::rank1(nodetemp->tData, ipos);//rank0
		//	AtlTrace("lnode,:now pos =%d\n", ipos);
			nodetemp = nodetemp->l;
		}
		else
		{
			ipos = BaisOperate::rank1(nodetemp->tData, ipos)-1;
		//	AtlTrace("rnode,:now pos =%d\n", ipos);
			nodetemp = nodetemp->r;
			
		}
	}
	int count = ipos + 1;
	//AtlTrace("End Rank,result = %d\n", count);
	return count;
}

int waveletTreeByBit::RankOFGama(const unsigned char c, const int& pos) const
{
//	AtlTrace("Start RankOFGama:now pos =%d,c=%c\n ", pos,c);
	waveletTreeNodeByBit* nodetemp = root;
	if (!ContainChar(nodetemp->allist, c))
		return -1;
	int ipos = pos;
	while (nodetemp->l != nullptr)
	{
		//Divedepos = i;
		if (nodetemp->allist[c] == 0) //c is 0
		{
			ipos = ipos - rankOfCurrentGama(nodetemp->GamaData, ipos);
//			AtlTrace("lnode,:now pos =%d\n", ipos);
			nodetemp = nodetemp->l;
		}
		else//c is 1
		{
			ipos = rankOfCurrentGama(nodetemp->GamaData, ipos )-1;
//			AtlTrace("rnode,:now pos =%d\n", ipos);
			nodetemp = nodetemp->r;
		}
	}
	int count = ipos + 1;
//	AtlTrace("End RankOFGama,result = %d\n", count);
	
	return count;
}

int waveletTreeByBit::rankOfCurrentGama(GamaCompressData& GamaData, const int& pos)
{
	//waveletTreeNodeByBit* nodetemp = root;
	int sbindex = (pos + 1) / SBSize;
	int bindex  = (pos + 1) / BSize;
	int mod = (pos + 1) % BSize;//todo mod
	int offset = GamaData.SB[sbindex] + GamaData.B[bindex];
	int header = GamaData.gamaHeader[(pos + 1) / BSize];
	int rankresult = GamaData.SBrank[sbindex] + GamaData.Brank[bindex] + lrank(GamaData.gamacode, offset, header, mod);
	return rankresult;
}

int waveletTreeByBit::lrank(vectorBitSingle s, int offset, int headertype, int mount)
{
	//todo finish lrank with lookuptable
	//int rankval = 0;

	//return rankval;
	bool bval;
	//const int compareNum =0;
	int count0 = 0;
	int Bpos = 0;
	int rankval = 0;
	switch (headertype)
	{
	case GAMACode::Plain:
		return BaisOperate::rank1(s, offset, mount);
	case GAMACode::RLG0:
	case GAMACode::RLG1:
		bval = GAMACode::RLG0 == headertype ? false : true;
		//int i = offset;
		//while (i+16)
		for (int i = offset; i<s.size()&&Bpos <= mount;)
		{
			if (s[i++] == 0)
				count0++;
			else
			{
				//todo wodo
				count0++;
				int m1 = 1;//count of runlength;
				for (int j = 0; j < count0 - 1; j++)
				{
					m1 = (m1 << 1) + s[i++];
				}
				if (bval)
				{
					if (Bpos + m1 > mount)
						rankval += m1 - (Bpos + m1 - mount);
					else
						rankval += m1;
				}
				bval = bval ? false : true;

				count0 = 0;
				Bpos += m1;
			}
		}

		break;
	case GAMACode::ALL0:
		return 0;
	case GAMACode::ALL1:
		return mount;
	default: break;
	}

	return rankval;
}

int waveletTreeByBit::Select(const unsigned char c, const int& pos) const
{
	int count;
	int postCur = 0;
	int postPre = pos;
	waveletTreeNodeByBit* nodetemp = root;
	if (!ContainChar(nodetemp->allist, c))
		return -1;
	while (nodetemp->l != nullptr)
	{
		if (nodetemp->allist[c] == 0)
			nodetemp = nodetemp->l;
		else
			nodetemp = nodetemp->r;
	}
	postPre = nodetemp->tData.size() < postPre ? nodetemp->tData.size() : postPre;

	while (nodetemp->p != nullptr)
	{
		nodetemp = nodetemp->p;
		postCur = 0;
		count = 0;
		while (count < postPre)
		{
			if (nodetemp->tData[postCur++] == nodetemp->allist[c])
				count++;
		}
		postPre = postCur;
	}
	return postCur - 1;
}

int waveletTreeByBit::calculateGamaCodeSize(waveletTreeNodeByBit& wt)
{
	int count = 0;
	if (wt.l != nullptr)
		count = calculateGamaCodeSize(*wt.l) + calculateGamaCodeSize(*wt.r);


	count += wt.GamaData.GetSize();

	return count;
}

void waveletTreeByBit::destory(waveletTreeNodeByBit* child, waveletTreeNodeByBit* parent)
{
	if (!child) return;
	destory(child->l, child);
	destory(child->r, child);
	if (parent == nullptr)
	{
		root = nullptr;
		delete child;
		//child = nullptr;
	}
	else if (parent->l == child)
	{
		parent->l = nullptr;
		delete child;
		//child = nullptr;
	}
	else
	{
		parent->r = nullptr;
		delete child;
		//child = nullptr;
	}
}

vector<unsigned int> waveletTreeByBit::locate(tuple<int, int> rangeLtoR)
{
	
	vector<unsigned int> result;
	int l = get<0>(rangeLtoR);
	int r = get<1>(rangeLtoR);
	for (int i = l; i <= r;i++)
	{
		AtlTrace("i =%d\n", i);
		result.push_back(getpos2(i));
	}
	return result;
}

unsigned waveletTreeByBit::getpos2(int pos)
{
	int tep = pos;
	//AtlTrace("SA[%d] = ", pos);
	int step = 0;
	int outpos = 0;
	while ((pos % SAMPLESTEP) != 0)
	{
		//if (step==4)
		//	AtlTrace("SA[%d] = ", pos);
		pos = LF[pos];
		step++;
		
	}
	pos = pos / SAMPLESTEP;
	outpos = (SASample[pos] + step) % Length;
	AtlTrace("SA[%d] = %d ,real = %d", tep, outpos, SA[tep] );
	return outpos;
	
}

waveletTreeByBit::waveletTreeByBit()
{
	root = new waveletTreeNodeByBit();
}

waveletTreeByBit::~waveletTreeByBit()
{
}
