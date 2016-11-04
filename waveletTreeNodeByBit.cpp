#include "stdafx.h"
#include "waveletTreeNodeByBit.h"




waveletTreeNodeByBit::waveletTreeNodeByBit() : ch(0)
{
	//tData(0);
	l = nullptr;
	r = nullptr;
	p = nullptr;
}


waveletTreeNodeByBit::waveletTreeNodeByBit(waveletTreeNodeByBit& parentNode): waveletTreeNodeByBit()
{
	p = &parentNode;
}

waveletTreeNodeByBit::~waveletTreeNodeByBit()
{
	if (l != nullptr)
	{
		delete l;
		l = nullptr;
	}

	if (r != nullptr)
	{
		delete r;
		r = nullptr;
	}
}

CString waveletTreeNodeByBit::showNodeData()
{
	CString str;
	int i;
//	AtlTrace("Tdata:\n");
	str = "\nTdata:\n";
	for (i = 0; i < tData.size();i++)
	{
		if ((i & 0x7) == 0)
			str += ",";
			//AtlTrace(",");
		if (tData[i] == 0)
			str += "0";
			//AtlTrace("0");
		else
			str += "1";
			//AtlTrace("1");
		
	}
	str+="\nGamaData\n";
	str += "gamacode:";
	for (i = 0; i < GamaData.gamacode.size(); i++)
	{
		if ((i & 0x7) == 0)
			str += ",";//AtlTrace(",");
		if (GamaData.gamacode[i] == 0)
			str += "0";//AtlTrace("0");
		else
			str += "1"; AtlTrace("1");
		
	}
	AtlTrace("header:");
	for (i = 0; i < GamaData.gamaHeader.size(); i++)
	{
		switch (GamaData.gamaHeader[i])
		{
		case GAMACode::Plain:
			str += "Plain";// AtlTrace("Plain");
				break;
		case GAMACode::RLG0:
			str += "RLG0"; //AtlTrace("RLG0");
			break;
		case GAMACode::RLG1:
			str += "RLG1";// AtlTrace("RLG1");
			break;
		case GAMACode::ALL0:
			str += "ALL0"; //AtlTrace("ALL0");
			break;
		case GAMACode::ALL1:
			str += "ALL1"; //AtlTrace("ALL1");
			break;
		}
		str += ",";// AtlTrace(",");
	}
	str += "\nSBrank:"; //AtlTrace("\nSBrank:");
	CString strtemp;
	for (i = 0; i < GamaData.SBrank.size(); i++)
	{
		strtemp.Format(_T("%d,"), GamaData.SBrank[i]);
		str += strtemp;
		//AtlTrace("%d,", GamaData.SBrank[i]);
	}
	str += "\nBrank:";//AtlTrace("\nBrank:");
	for (i = 0; i < GamaData.Brank.size(); i++)
	{
		strtemp.Format(_T("%d,"), GamaData.Brank[i]);
		str += strtemp;
	//	AtlTrace("%d,", GamaData.Brank[i]);
	}
	str += "\nSB:";// AtlTrace("\nSB:");
	for (i = 0; i < GamaData.SB.size(); i++)
	{
		strtemp.Format(_T("%d,"), GamaData.SB[i]);
		str += strtemp;
		//AtlTrace("%d,", GamaData.SB[i]);
	}
	str += "\nB:";//AtlTrace("\nB:");
	for (i = 0; i < GamaData.B.size(); i++)
	{
		strtemp.Format(_T("%d,"), GamaData.B[i]);
		str += strtemp;
		//AtlTrace("%d,", GamaData.B[i]);
	}
	return str;
}
