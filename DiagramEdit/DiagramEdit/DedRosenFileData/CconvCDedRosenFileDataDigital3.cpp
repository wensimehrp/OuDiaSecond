/*
	OuDiaSecond Copyright (C) 2017-2025 diagram_mania

このプログラムは、take-okm氏が作成したOuDiaを改造したソフトウェアです。
このプログラム利用については、take-okm氏記載の下記文書に準拠します。
*/
/*
	OuDia - Win32 Application Software to draw a "Train Service Planning
 Diagram" based on a "Train Timetable".

Copyright (C) 2006-2017 take-okm

This program is free software; you can redistribute it and/or modify it 
under the terms of the GNU General Public License as published by the Free 
Software Foundation; either version 3 of the License, or (at your option) 
any later version. 

This program is distributed in the hope that it will be useful, but WITHOUT 
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for 
more details. 

You should have received a copy of the GNU General Public License along with
 this program. If not, see <http://www.gnu.org/licenses/>.

  In addition, as a special exception, take-okm
  gives permission to link the code of this program with
  the "MFC(Microsoft Foundation Class library) Version 9.0" 
  (or with modified versions of "MFC Version 9.0" that use the same license as 
  "MFC Version 9.0" ), and distribute linked combinations including
  the two.  You must obey the GNU General Public License in all
  respects for all of the code used other than  "MFC".  If you modify
  this file, you may extend this exception to your version of the
  file, but you are not obligated to do so.  If you do not wish to
  do so, delete this exception statement from your version.


(訳: 

	OuDia - 列車時刻表をもとに、ダイヤグラムを描画するWin32アプリケーシ
ョン。

Copyright (C) 2006-2017 take-okm 

このプログラムはフリーソフトウェアです。あなたはこれを、フリーソフトウェア財
団によって発行されたGNU 一般公衆利用許諾書(バージョン3か、それ以降のバージョ
ンのうちどれか)が定める条件の下で再頒布または改変 することができます。

このプログラムは有用であることを願って頒布されますが、*全くの無保証 *です。
商業可能性の保証や特定目的への適合性は、言外に示されたものも 含め、全く存在
しません。詳しくはGNU 一般公衆利用許諾書をご覧ください。

あなたはこのプログラムと共に、GNU 一般公衆利用許諾書のコピーを一部 受け取っ
ているはずです。もし受け取っていなければ、<http://www.gnu.org/licenses/> を
ご覧ください。

)

  加えて、特別な例外として、take-okm はこのプログラムのコードを 
  "MFC(Microsoft Foundation Class library) Version 9.0" 
  (  あるいは "MFC Version 9.0" と同じライセンスが適用された
  "MFC Version 9.0" の改変されたバージョン)とリンクし、
  リンクされた両者を含む結合著作物を頒布する許可を与えます。
  あなたは "MFC" 以外で使われているすべて
  のコードに関しては全面的にGNU一般公衆利用許諾契約書に従わなければ
  なりません。あなたがこのファイルを改変したならば、あなたはこの例外
  をあなたのバージョンのファイルに引き続き設けることもできますが、そ
  うする義務はありません。もし例外を設けたくなければ、この例外条項を
  あなたのバージョンからは削除してください。)
*/
/*
// ****************************************************************
//	CconvCDedRosenFileDataDigital3.cpp
// ****************************************************************
*/
/** @file */
#include "stdafx.h"
#include "NsOu\OuNew.h"
#include "NsOu\dynamic_castOu.h"
#include "str\CdConnectedString2.h"
#include "str\strToInt.h"
#include "str\CConnectedStringCompress.h"
#include "str\OuPropertiesText\CConvNodeContainer.h"
#include "str\OuPropertiesText\CDirectory.h"
#include "str\OuPropertiesText\ErrorInfo\COuErrorInfoContainer.h"
#include "logmsg\LogMsg.h"

#include "CconvCdDedDispProp.h"
#include "CconvCDedRosenFileDataDigital3.h"
//#include "../CDiagramEditDoc.h"
#include "../DiagramEdit.h"

#include "NsMu\CaMui.h"
//#include "../entDed/CentDedEki.h"


/*delete 遅いので抑止
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static TCHAR THIS_FILE[] = __FILE__;
#endif
*/

namespace DedRosenFileData{
	using namespace std ;
	using namespace OuLib::NsOu ;
	using namespace OuLib::Str::OuPropertiesText;
	using namespace OuLib::Str::OuPropertiesText::ErrorInfo;
// ****************************************************************
//	CconvCDedRosenFileData
// ****************************************************************

int CconvCDedRosenFileDataDigital3::CDedRosenFileData_from_string( 
			CDedRosenFileData* pCDedRosenFileData ,
			const tstring& aString1 ,
			const tstring& aString2,
			const tstring& aString3,
			const tstring& aString4,
			const bool bInvalidateIndividualHandling/*,
			OuPropertiesText::ErrorInfo::COuErrorInfoContainer* pCOuErrorInfoContainer */) 
{

	vector<tstring> contString1 = splitc<vector<tstring>>('\n', aString1);
	vector<tstring> contString2 = splitc<vector<tstring>>('\n', aString2);
	vector<tstring> contString3 = splitc<vector<tstring>>('\n', aString3);
	vector<tstring> contString4 = splitc<vector<tstring>>('\n', aString4);




	//LogMsg( _T("CDedRosenFileData_from_string()") ) ;

	int iRv = 0 ;

	/**
		入力ファイルの整合性を確かめる
		・String1-4の路線が一致
		・String1・2の日付が一致、方面が逆
		・String3・4の日付が一致、方面が逆
		・String1・3の方面が一致
		・String2・4の方面が一致
	*/

	//日付、曜日の代わりに使用
	tstring strDate[4];//"20xx年x月x日(x)"
	const tstring strHtmlOnly = _T("日時不明");

	//tstring strRosenID=_T("");
	//見出しに表示されている、時刻表の範囲から、駅名を抜き出して並べたもの
	vector<deque<tstring>> strRoute;//"札幌/新千歳空港/苫小牧/東室蘭/室蘭"
	strRoute.assign(4, {});

	if (iRv >= 0)
	{
		tstring::size_type pos = aString1.find(_T("selected="));
		if (pos != tstring::npos)
		{
			tstring::size_type posA = aString1.find(_T(">"), pos);
			tstring::size_type posB = aString1.find(_T("<"), pos);

			strDate[0] = aString1.substr(posA + 1, posB - posA - 1);;
		}
		else if (aString1.find(_T(">全日<")) != tstring::npos)
		{
			strDate[0] = strHtmlOnly;
		}
		else
		{
			iRv = -21;//	ファイル1の路線データ無し。
		}
	}

	if (iRv >= 0)
	{
		tstring::size_type pos = aString1.find(_T("senkuName"));
		if (iRv >= 0 && pos != tstring::npos)
		{
			tstring::size_type posA = aString1.find(_T("</div>"), pos);
			tstring::size_type posB = aString1.rfind(_T(")"), posA);
			tstring::size_type posC = aString1.rfind(_T("("), posA);

			tstring strTemp = aString1.substr(posC + 1, posB - posC - 1);
			deque<tstring> contTempA;
			for (int idx = strTemp.size() - 1; idx >= 0; idx--)
			{
				if (strTemp[idx] == _T('―') ||
					strTemp[idx] == _T('・'))
				{
					contTempA.emplace_front(strTemp.substr(idx + 1));
					strTemp = strTemp.substr(0, idx);
				}
			}
			contTempA.emplace_front(strTemp);

			strRoute[0] = contTempA;
		}
		else
		{
			iRv = -21;//	ファイル1の路線データ無し。
		}
	}

	if (iRv >= 0 && !aString2.empty())
	{
		tstring::size_type pos = aString2.find(_T("selected="));
		if (pos != tstring::npos)
		{
			tstring::size_type posA = aString2.find(_T(">"), pos);
			tstring::size_type posB = aString2.find(_T("<"), pos);

			strDate[1] = aString2.substr(posA + 1, posB - posA-1);

		}
		else if (aString2.find(_T(">全日<")) != tstring::npos)
		{
			strDate[1] = strHtmlOnly;
		}
		else
		{
			iRv = -22;//	ファイル2の路線データ無し。
		}
	}

	if (iRv >= 0 && !aString2.empty() && strDate[0] != strDate[1])
	{
		iRv = -52;//	ファイル2の曜日がファイル1と不一致。(ここでは日付)
	}

	if (iRv >= 0 && !aString2.empty())
	{
		tstring::size_type pos = aString2.find(_T("senkuName"));
		if (iRv >= 0 && pos != tstring::npos)
		{
			tstring::size_type posA = aString2.find(_T("</div>"), pos);
			tstring::size_type posB = aString2.rfind(_T(")"), posA);
			tstring::size_type posC = aString2.rfind(_T("("), posA);

			tstring strTemp = aString2.substr(posC + 1, posB - posC - 1);
			deque<tstring> contTempA;
			for (int idx = strTemp.size() - 1; idx >= 0; idx--)
			{
				if (strTemp[idx] == _T('―') ||
					strTemp[idx] == _T('・'))
				{
					contTempA.emplace_front(strTemp.substr(idx + 1));
					strTemp = strTemp.substr(0, idx);
				}
			}
			contTempA.emplace_front(strTemp);
			strRoute[1] = contTempA;

			//ダイヤ1下りとダイヤ1上りの路線を比較、路線概要の駅数が異なる場合、路線概要が完全一致する場合、路線概要が逆向きになっていない場合はそれぞれエラー
			if (strRoute[0].size() != strRoute[1].size())
			{
				iRv = -32;//	ファイル2の路線がファイル1と不一致。
			}
			else if (strRoute[0] == strRoute[1])
			{
				iRv = -42;//	ファイル2の方向がファイル1と一致。
			}
			else
			{
				for (int idx1 = 0, idx2 = strRoute[1].size() - 1; idx1 < (int)strRoute[0].size() && iRv >= 0; idx1++, idx2--)
				{
					if (strRoute[0][idx1] != strRoute[1][idx2])
					{
						iRv = -32;//	ファイル2の路線がファイル1と不一致。
					}
				}
			}
		}
		else
		{
			iRv = -22;//	ファイル2の路線データ無し。
		}
	}

	if (iRv >= 0 && !aString3.empty())
	{
		tstring::size_type pos = aString3.find(_T("selected="));
		if (pos != tstring::npos)
		{
			tstring::size_type posA = aString3.find(_T(">"), pos);
			tstring::size_type posB = aString3.find(_T("<"), pos);

			strDate[2] = aString3.substr(posA + 1, posB - posA-1);
		}
		else if (aString3.find(_T(">全日<")) != tstring::npos)
		{
			strDate[2] = strHtmlOnly;
		}
		else
		{
			iRv = -23;//	ファイル3の路線データ無し。
		}
	}
	if (iRv >= 0 && !aString3.empty())
	{
		tstring::size_type pos = aString3.find(_T("senkuName"));
		if (iRv >= 0 && pos != tstring::npos)
		{
			tstring::size_type posA = aString3.find(_T("</div>"), pos);
			tstring::size_type posB = aString3.rfind(_T(")"), posA);
			tstring::size_type posC = aString3.rfind(_T("("), posA);

			tstring strTemp = aString3.substr(posC + 1, posB - posC - 1);
			deque<tstring> contTempA;
			for (int idx = strTemp.size() - 1; idx >= 0; idx--)
			{
				if (strTemp[idx] == _T('―') ||
					strTemp[idx] == _T('・'))
				{
					contTempA.emplace_front(strTemp.substr(idx + 1));
					strTemp = strTemp.substr(0, idx);
				}
			}
			contTempA.emplace_front(strTemp);
			strRoute[2] = contTempA;

			//ダイヤ1下りとダイヤ2下りの路線を比較、完全一致しない場合はエラーだが、路線が異なる場合と、上下逆向きの場合のそれぞれで異なるエラーとなる
			if (strRoute[0] == strRoute[2])
			{
				//continue;
			}
			else if (strRoute[0].size() != strRoute[2].size())
			{
				iRv = -33;//	ファイル3の路線がファイル1と不一致。
			}
			else
			{
				//エラーであること自体は決まっているので、先に上下逆向きと仮置きしておき、精査の結果路線が異なる場合は、エラーコードを上書きする
				iRv = -43;//	ファイル3の方向がファイル1と不一致。
				for (int idx1 = 0, idx2 = strRoute[2].size() - 1; idx1 < (int)strRoute[0].size(); idx1++, idx2--)
				{
					if (strRoute[0][idx1] != strRoute[2][idx2])
					{
						iRv = -33;//	ファイル3の路線がファイル1と不一致。
						break;
					}
				}
			}
		}
		else
		{
			iRv = -23;//	ファイル3の路線データ無し。
		}
	}

	if (iRv >= 0 && !aString4.empty())
	{
		tstring::size_type pos = aString4.find(_T("selected="));
		if (pos != tstring::npos)
		{
			tstring::size_type posA = aString4.find(_T(">"), pos);
			tstring::size_type posB = aString4.find(_T("<"), pos);

			strDate[3] = aString4.substr(posA + 1, posB - posA-1);

		}
		else if (aString4.find(_T(">全日<")) != tstring::npos)
		{
			strDate[3] = strHtmlOnly;
		}
		else
		{
			iRv = -24;//	ファイル4の路線データ無し。
		}
	}

	if (iRv >= 0 && !aString3.empty() && !aString4.empty() && strDate[3] != strDate[2])
	{
		iRv = -64;//	ファイル4の曜日がファイル3と不一致。(ここでは日付)
	}

	if (iRv >= 0 && !aString4.empty())
	{
		tstring::size_type pos = aString4.find(_T("senkuName"));
		if (iRv >= 0 && pos != tstring::npos)
		{
			tstring::size_type posA = aString4.find(_T("</div>"), pos);
			tstring::size_type posB = aString4.rfind(_T(")"), posA);
			tstring::size_type posC = aString4.rfind(_T("("), posA);

			tstring strTemp = aString4.substr(posC + 1, posB - posC - 1);
			deque<tstring> contTempA;
			for (int idx = strTemp.size() - 1; idx >= 0; idx--)
			{
				if (strTemp[idx] == _T('―') ||
					strTemp[idx] == _T('・'))
				{
					contTempA.emplace_front(strTemp.substr(idx + 1));
					strTemp = strTemp.substr(0, idx);
				}
			}
			contTempA.emplace_front(strTemp);
			strRoute[3] = contTempA;

			//ダイヤ1下りとダイヤ2上りの路線を比較、路線概要の駅数が異なる場合、路線概要が完全一致する場合、路線概要が逆向きになっていない場合はそれぞれエラー
			if (strRoute[0].size() != strRoute[3].size())
			{
				iRv = -34;//	ファイル4の路線がファイル1と不一致。
			}
			else if (strRoute[0] == strRoute[3])
			{
				iRv = -44;//	ファイル4の方向がファイル1と一致。
			}
			else
			{
				for (int idx1 = 0, idx2 = strRoute[3].size() - 1; idx1 < (int)strRoute[0].size() && iRv >= 0; idx1++, idx2--)
				{
					if (strRoute[0][idx1] != strRoute[3][idx2])
					{
						iRv = -34;//	ファイル4の路線がファイル1と不一致。
					}
				}
			}
		}
		else
		{
			iRv = -24;//	ファイル4の路線データ無し。
		}
	}



	//tstring	strRv ;

	//LogMsg( _T("CDedRosenFileData_from_string()1") ) ;

	if (iRv >= 0)
	{
		pCDedRosenFileData->clear();
	}


	CentDedRosen*	pCentDedRosen= pCDedRosenFileData->getCentDedRosen();
	/**
		tableを項目と列車ごとに分解していく、
		項目列1：(行のタイトル)列車番号、列車名、運転日。駅名
		項目列2：着・発・番線

	*/
	vector<vector<tstring>> contRessya1;
	vector<vector<tstring>> contRessya2;
	vector<vector<tstring>> contRessya3;
	vector<vector<tstring>> contRessya4;

	vector<DigitalContent> contDigitalContent1;
	vector<DigitalContent> contDigitalContent2;
	vector<DigitalContent> contDigitalContent3;
	vector<DigitalContent> contDigitalContent4;

	//個別処理は保留
	int iIndividualHandling1 = 0;
	int iIndividualHandling2 = 0;
	//if (!bInvalidateIndividualHandling && strRosenID == _T("003"))
	//{
	//	if (bIsDown[0])
	//	{
	//		iIndividualHandling2 = 1;
	//	}
	//	else
	//	{
	//		iIndividualHandling1 = 1;
	//	}
	//}
	//else if (!bInvalidateIndividualHandling && strRosenID == _T("279"))
	//{
	//	iIndividualHandling1 = 2;
	//	iIndividualHandling2 = 2;
	//}

	if (iRv >= 0)
	{
		if (!aString1.empty())
		{
			ReadDigital(aString1, contRessya1, contDigitalContent1, iIndividualHandling1);
		}
		if (!aString2.empty())
		{
			ReadDigital(aString2, contRessya2, contDigitalContent2, iIndividualHandling2);
		}
		if (!aString3.empty())
		{
			ReadDigital(aString3, contRessya3, contDigitalContent3, iIndividualHandling1);
		}
		if (!aString4.empty())
		{
			ReadDigital(aString4, contRessya4, contDigitalContent4, iIndividualHandling2);
		}
	}

	if (iRv >= 0)
	{
		/**
			contDigitalContent1を基にまずは駅の並びを確定させる
		*/
		int iEkiIndex = -1;
		tstring strEkimeiBefore = _T("");
		//予めstrContEkimeiRevに下りの駅を逆順に入れておく。上りのチェック用
		vector<tstring> strContEkimei;
		for (int idx = 0; idx < contDigitalContent1.size(); idx++)
		{
			if (contDigitalContent1[idx].strTh1 == _T("列車番号"))
			{
				contDigitalContent1[idx].eTrType = ETrType::TrType_RessyaBangou;
			}
			else if (contDigitalContent1[idx].strTh1 == _T("列車種別"))
			{
				contDigitalContent1[idx].eTrType = ETrType::TrType_Ressyasyubetsu;
			}
			else if (contDigitalContent1[idx].strTh1 == _T("列車名"))
			{
				contDigitalContent1[idx].eTrType = ETrType::TrType_RessyaMei;
			}
			else if (contDigitalContent1[idx].strTh1 == _T("号数"))
			{
				contDigitalContent1[idx].eTrType = ETrType::TrType_GouSuu;
			}
			else if (contDigitalContent1[idx].strTh1 == _T("運転日"))
			{
				contDigitalContent1[idx].eTrType = ETrType::TrType_UntenBi;
			}
			else if (contDigitalContent1[idx].strTh2 == _T("発"))
			{
				if (contDigitalContent1[idx].strTh1 == strEkimeiBefore)
				{
					contDigitalContent1[idx].eTrType = ETrType::TrType_EkiHatsu;
					contDigitalContent1[idx].iEkiIndex = iEkiIndex;
				}
				else
				{
					iEkiIndex++;
					strEkimeiBefore = contDigitalContent1[idx].strTh1;
					strContEkimei.push_back(contDigitalContent1[idx].strTh1);
					contDigitalContent1[idx].eTrType = ETrType::TrType_EkiHatsu;
					contDigitalContent1[idx].iEkiIndex = iEkiIndex;
				}
			}
			else if (contDigitalContent1[idx].strTh2 == _T("着"))
			{
				if (contDigitalContent1[idx].strTh1 == strEkimeiBefore)
				{
					contDigitalContent1[idx].eTrType = ETrType::TrType_EkiChaku;
					contDigitalContent1[idx].iEkiIndex = iEkiIndex;
				}
				else
				{
					iEkiIndex++;
					strEkimeiBefore = contDigitalContent1[idx].strTh1;
					strContEkimei.push_back(contDigitalContent1[idx].strTh1);
					contDigitalContent1[idx].eTrType = ETrType::TrType_EkiChaku;
					contDigitalContent1[idx].iEkiIndex = iEkiIndex;
				}
			}
			else if (contDigitalContent1[idx].strTh1.find(_T("番線")) != tstring::npos)
			{
				if (contDigitalContent1[idx - 1].eTrType == ETrType::TrType_EkiChaku)
				{
					contDigitalContent1[idx].eTrType = ETrType::TrType_EkiBansen;
					contDigitalContent1[idx].iEkiIndex = iEkiIndex;
				}
				else
				{
					//iEkiIndex++;
					//一つ前の欄が着時刻でない場合、ここでは駅名の取得や駅インデクスのインクリメントを行わず、駅インデクス+1を入れて置き、
					//次の発時刻欄で、着発の判定などを行う。
					contDigitalContent1[idx].eTrType = ETrType::TrType_EkiBansen;
					contDigitalContent1[idx].iEkiIndex = iEkiIndex + 1;

					//idx++;

					//strEkimeiBefore = contDigitalContent1[idx].strTh1;
					//strContEkimei.push_back(contDigitalContent1[idx].strTh1);
					//contDigitalContent1[idx].eTrType = ETrType::TrType_EkiHatsu;
					//contDigitalContent1[idx].iEkiIndex = iEkiIndex;
				}
			}
			else if (contDigitalContent1[idx].strTh1 == _T("始発"))
			{
				contDigitalContent1[idx].eTrType = ETrType::TrType_OuterShihatsu;
			}
			else if (contDigitalContent1[idx].strTh1 == _T("終着"))
			{
				contDigitalContent1[idx].eTrType = ETrType::TrType_OuterShuchaku;
			}
		}

		//上りダイヤ1が空の場合は、上りダイヤ2のcontDigitalContent4をcontDigitalContent2にコピーして、上りの駅の並びを確定させる。
		if (contDigitalContent2.empty())
		{
			contDigitalContent2 = contDigitalContent4;
		}
		if (!contDigitalContent2.empty())
		{
			int iEkiIndexNobori = strContEkimei.size() - 1;
			for (int idx = 0; idx < contDigitalContent2.size(); idx++)
			{
				if (contDigitalContent2[idx].strTh1 == _T("列車番号"))
				{
					contDigitalContent2[idx].eTrType = ETrType::TrType_RessyaBangou;
				}
				else if (contDigitalContent2[idx].strTh1 == _T("列車種別"))
				{
					contDigitalContent2[idx].eTrType = ETrType::TrType_Ressyasyubetsu;
				}
				else if (contDigitalContent2[idx].strTh1 == _T("列車名"))
				{
					contDigitalContent2[idx].eTrType = ETrType::TrType_RessyaMei;
				}
				else if (contDigitalContent2[idx].strTh1 == _T("号数"))
				{
					contDigitalContent2[idx].eTrType = ETrType::TrType_GouSuu;
				}
				else if (contDigitalContent2[idx].strTh1 == _T("運転日"))
				{
					contDigitalContent2[idx].eTrType = ETrType::TrType_UntenBi;
				}
				else if (contDigitalContent2[idx].strTh2 == _T("発"))
				{
					//strContEkimeiと比較し、下りと駅順が同じことを確かめる。
					if (contDigitalContent2[idx].strTh1 == strContEkimei[iEkiIndexNobori])
					{
						contDigitalContent2[idx].eTrType = ETrType::TrType_EkiHatsu;
						contDigitalContent2[idx].iEkiIndex = iEkiIndexNobori;
					}
					else
					{
						iEkiIndexNobori--;
						//もし、下りと駅順が違っていたら、エラーとする(検証用)
						if (iEkiIndexNobori < 0 || contDigitalContent2[idx].strTh1 == strContEkimei[iEkiIndexNobori])
						{
							contDigitalContent2[idx].eTrType = ETrType::TrType_EkiHatsu;
							contDigitalContent2[idx].iEkiIndex = iEkiIndexNobori;
						}
						else
						{
							iRv = -71;
						}
					}
				}
				else if (contDigitalContent2[idx].strTh2 == _T("着"))
				{
					//strContEkimeiと比較し、下りと駅順が同じことを確かめる。
					if (contDigitalContent2[idx].strTh1 == strContEkimei[iEkiIndexNobori])
					{
						contDigitalContent2[idx].eTrType = ETrType::TrType_EkiChaku;
						contDigitalContent2[idx].iEkiIndex = iEkiIndexNobori;
					}
					else
					{
						iEkiIndexNobori--;
						//もし、下りと駅順が違っていたら、エラーとする(検証用)
						if (iEkiIndexNobori < 0 || contDigitalContent2[idx].strTh1 == strContEkimei[iEkiIndexNobori])
						{
							contDigitalContent2[idx].eTrType = ETrType::TrType_EkiChaku;
							contDigitalContent2[idx].iEkiIndex = iEkiIndexNobori;
						}
						else
						{
							iRv = -72;
						}
					}
				}
				else if (contDigitalContent2[idx].strTh1.find(_T("番線")) != tstring::npos)
				{
					if (contDigitalContent2[idx - 1].eTrType == ETrType::TrType_EkiChaku)
					{
						tstring strEkimei = contDigitalContent2[idx - 1].strTh1;
						if (strEkimei == strContEkimei[iEkiIndexNobori])
						{
							contDigitalContent2[idx].eTrType = ETrType::TrType_EkiBansen;
							contDigitalContent2[idx].iEkiIndex = iEkiIndexNobori;
						}
						else
						{
							iRv = -74;
						}
					}
					else
					{
						tstring strEkimei = contDigitalContent2[idx + 1].strTh1;

						//strContEkimeiと比較し、下りと駅順が同じことを確かめる。
						if (strEkimei == strContEkimei[iEkiIndexNobori])
						{
							contDigitalContent2[idx].eTrType = ETrType::TrType_EkiBansen;
							contDigitalContent2[idx].iEkiIndex = iEkiIndexNobori;
						}
						else
						{
							iEkiIndexNobori--;
							//もし、下りと駅順が違っていたら、エラーとする(検証用)
							if (iEkiIndexNobori < 0 || strEkimei == strContEkimei[iEkiIndexNobori])
							{
								contDigitalContent2[idx].eTrType = ETrType::TrType_EkiBansen;
								contDigitalContent2[idx].iEkiIndex = iEkiIndexNobori;
							}
							else
							{
								iRv = -75;
							}
						}
					}
				}
				else if (contDigitalContent2[idx].strTh1 == _T("始発"))
				{
					contDigitalContent2[idx].eTrType = ETrType::TrType_OuterShihatsu;
				}
				else if (contDigitalContent2[idx].strTh1 == _T("終着"))
				{
					contDigitalContent2[idx].eTrType = ETrType::TrType_OuterShuchaku;
				}
			}
		}
	}
	/**
		EkiContを作る
	*/
	if (iRv >= 0)
	{

		CentDedEkiCont aCentDedEkiCont;

		/**
			各駅の駅の時刻形式
			下り着・発・上り着・発
			〇〇〇〇：発着
			〇〇〇×：※発着
			〇〇×〇：下り発着
			〇〇××：(発着)
			〇×〇〇：※発着
			〇×〇×：※発着
			〇××〇：下り着時刻
			〇×××：(下り着時刻)
			×〇〇〇：上り発着
			×〇〇×：上り着時刻
			×〇×〇：発時刻
			×〇××：(発時刻)
			××〇〇：(該当なし)
			××〇×：(該当なし)
			×××〇：(該当なし)
			××××：(該当なし)
		*/
		int iEkiCount;
		for (int idx = contDigitalContent1.size() - 1; idx >= 0; idx--)
		{
			if (contDigitalContent1[idx].iEkiIndex > 0)
			{
				iEkiCount = contDigitalContent1[idx].iEkiIndex + 1;
				break;
			}
		}
		for (int iEkiIndex = 0; iEkiIndex < iEkiCount; iEkiIndex++)
		{
			CentDedEki aCentDedEki;

			for (int idxk = 0; idxk < contDigitalContent1.size(); idxk++)
			{
				if (contDigitalContent1[idxk].iEkiIndex == iEkiIndex &&
					(contDigitalContent1[idxk].eTrType == ETrType::TrType_EkiChaku ||
						contDigitalContent1[idxk].eTrType == ETrType::TrType_EkiHatsu))
				{
					aCentDedEki.setEkimei(contDigitalContent1[idxk].strTh1);
					break;
				}
			}

			bool bKudariChaku = false;
			bool bKudariHatsu = false;
			bool bNoboriChaku = false;
			bool bNoboriHatsu = false;
			int iKudariTrackRow = -1;
			int iNoboriTrackRow = -1;

			for (int idxk = 0; idxk < contDigitalContent1.size(); idxk++)
			{
				if (contDigitalContent1[idxk].eTrType == ETrType::TrType_EkiChaku &&
					contDigitalContent1[idxk].iEkiIndex == iEkiIndex)
				{
					bKudariChaku = true;
				}
				if (contDigitalContent1[idxk].eTrType == ETrType::TrType_EkiHatsu &&
					contDigitalContent1[idxk].iEkiIndex == iEkiIndex)
				{
					bKudariHatsu = true;
				}
				if (contDigitalContent1[idxk].eTrType == ETrType::TrType_EkiBansen &&
					contDigitalContent1[idxk].iEkiIndex == iEkiIndex)
				{
					iKudariTrackRow = idxk;
				}
			}

			for (int idxn = 0; idxn < contDigitalContent2.size(); idxn++)
			{
				if (contDigitalContent2[idxn].eTrType == ETrType::TrType_EkiChaku &&
					contDigitalContent2[idxn].iEkiIndex == iEkiIndex)
				{
					bNoboriChaku = true;
				}
				if (contDigitalContent2[idxn].eTrType == ETrType::TrType_EkiHatsu &&
					contDigitalContent2[idxn].iEkiIndex == iEkiIndex)
				{
					bNoboriHatsu = true;
				}
				if (contDigitalContent2[idxn].eTrType == ETrType::TrType_EkiBansen &&
					contDigitalContent2[idxn].iEkiIndex == iEkiIndex)
				{
					iNoboriTrackRow = idxn;
				}
			}

			if (bKudariChaku)
			{
				if (bKudariHatsu || bNoboriChaku)
				{
					if (bKudariHatsu && !bNoboriChaku && bNoboriHatsu)
					{
						//下り発着
						aCentDedEki.setEkijikokukeisiki(CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku);
						aCentDedEki.setJikokuhyouChakuJikokuDisplayKudari(true);
						aCentDedEki.setJikokuhyouTrackOmit(true);
					}
					else
					{
						//発着
						aCentDedEki.setEkijikokukeisiki(CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku);
						aCentDedEki.setJikokuhyouChakuJikokuDisplayKudari(true);
						aCentDedEki.setJikokuhyouChakuJikokuDisplayNobori(true);
					}
				}
				else
				{
					//下り着時刻
					aCentDedEki.setEkijikokukeisiki(CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku);
					aCentDedEki.setJikokuhyouChakuJikokuDisplayKudari(true);
					aCentDedEki.setJikokuhyouHatsuJikokuDisplayKudari(false);
				}

			}
			else
			{
				if (bKudariHatsu && bNoboriChaku)
				{
					if (bNoboriHatsu)
					{
						//上り発着
						aCentDedEki.setEkijikokukeisiki(CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku);
						aCentDedEki.setJikokuhyouChakuJikokuDisplayNobori(true);
						aCentDedEki.setJikokuhyouTrackOmit(true);
					}
					else
					{
						//上り着時刻
						aCentDedEki.setEkijikokukeisiki(CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku);
						aCentDedEki.setJikokuhyouChakuJikokuDisplayNobori(true);
						aCentDedEki.setJikokuhyouHatsuJikokuDisplayNobori(false);
					}
				}
				else
				{
					//発時刻
					aCentDedEki.setEkijikokukeisiki(CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsu);
					aCentDedEki.setJikokuhyouTrackOmit(true);
				}
			}

			if (iKudariTrackRow >= 0 || iNoboriTrackRow >= 0)
			{
				vector<tstring> contTrackName;
				vector<int>contTrainCountKudari;
				vector<int>contTrainCountNobori;
				if (iKudariTrackRow >= 0)
				{
					for (int idxk = 0; idxk < contRessya1.size(); idxk++)
					{
						if (contRessya1[idxk][iKudariTrackRow].find('(') == tstring::npos)
						{
							continue;
						}
						bool bFound = false;
						tstring TrackNameThis = contRessya1[idxk][iKudariTrackRow].substr(1, contRessya1[idxk][iKudariTrackRow].length() - 2);

						for (int idxTN = 0; idxTN < contTrackName.size(); idxTN++)
						{
							if (contTrackName[idxTN] == TrackNameThis)
							{
								bFound = true;
								contTrainCountKudari[idxTN]++;
								//ここで、contRessya1[idxk][iKudariTrackRow]の中身を、(番線)→RessyaTrackIndex(idxTN)に書き換えてしまう。
								contRessya1[idxk][iKudariTrackRow] = to_tstring(idxTN);

								break;
							}
						}
						if (!bFound)
						{
							//ここで、contRessya1[idxk][iKudariTrackRow]の中身を、(番線)→RessyaTrackIndex(idxTN)に書き換えてしまう。
							contRessya1[idxk][iKudariTrackRow] = to_tstring(contTrackName.size());

							contTrackName.push_back(TrackNameThis);
							contTrainCountKudari.push_back(1);
						}
					}
					for (int idxk = 0; idxk < contRessya3.size(); idxk++)
					{
						if (contRessya3[idxk][iKudariTrackRow].find('(') == tstring::npos)
						{
							continue;
						}
						bool bFound = false;
						tstring TrackNameThis = contRessya3[idxk][iKudariTrackRow].substr(1, contRessya3[idxk][iKudariTrackRow].length() - 2);

						for (int idxTN = 0; idxTN < contTrackName.size(); idxTN++)
						{
							if (contTrackName[idxTN] == TrackNameThis)
							{
								bFound = true;
								contTrainCountKudari[idxTN]++;
								//ここで、contRessya[idxk][iKudariTrackRow]の中身を、(番線)→RessyaTrackIndex(idxTN)に書き換えてしまう。
								contRessya3[idxk][iKudariTrackRow] = to_tstring(idxTN);

								break;
							}
						}
						if (!bFound)
						{
							//ここで、contRessya[idxk][iKudariTrackRow]の中身を、(番線)→RessyaTrackIndex(idxTN)に書き換えてしまう。
							contRessya3[idxk][iKudariTrackRow] = to_tstring(contTrackName.size());

							contTrackName.push_back(TrackNameThis);
							contTrainCountKudari.push_back(1);
						}
					}
				}

				if (contTrainCountKudari.size() > 0)
				{
					contTrainCountNobori.assign(contTrainCountKudari.size(), 0);
				}

				if (iNoboriTrackRow >= 0)
				{
					for (int idxn = 0; idxn < contRessya2.size(); idxn++)
					{
						if (contRessya2[idxn][iNoboriTrackRow].find('(') == tstring::npos)
						{
							continue;
						}
						bool bFound = false;
						tstring TrackNameThis = contRessya2[idxn][iNoboriTrackRow].substr(1, contRessya2[idxn][iNoboriTrackRow].length() - 2);

						for (int idxTN = 0; idxTN < contTrackName.size(); idxTN++)
						{
							if (contTrackName[idxTN] == TrackNameThis)
							{
								bFound = true;
								contTrainCountNobori[idxTN]++;

								//ここで、contRessya[idxn][iNoboriTrackRow]の中身を、(番線)→RessyaTrackIndex(idxTN)に書き換えてしまう。
								contRessya2[idxn][iNoboriTrackRow] = to_tstring(idxTN);

								break;
							}
						}
						if (!bFound)
						{
							//ここで、contRessya[idxn][iNoboriTrackRow]の中身を、(番線)→RessyaTrackIndex(idxTN)に書き換えてしまう。
							contRessya2[idxn][iNoboriTrackRow] = to_tstring(contTrackName.size());

							contTrackName.push_back(TrackNameThis);
							contTrainCountNobori.push_back(1);
						}
					}
					for (int idxn = 0; idxn < contRessya4.size(); idxn++)
					{
						if (contRessya4[idxn][iNoboriTrackRow].find('(') == tstring::npos)
						{
							continue;
						}
						bool bFound = false;
						tstring TrackNameThis = contRessya4[idxn][iNoboriTrackRow].substr(1, contRessya4[idxn][iNoboriTrackRow].length() - 2);

						for (int idxTN = 0; idxTN < contTrackName.size(); idxTN++)
						{
							if (contTrackName[idxTN] == TrackNameThis)
							{
								bFound = true;
								contTrainCountNobori[idxTN]++;

								//ここで、contRessya[idxn][iNoboriTrackRow]の中身を、(番線)→RessyaTrackIndex(idxTN)に書き換えてしまう。
								contRessya4[idxn][iNoboriTrackRow] = to_tstring(idxTN);

								break;
							}
						}
						if (!bFound)
						{
							//ここで、contRessya[idxn][iNoboriTrackRow]の中身を、(番線)→RessyaTrackIndex(idxTN)に書き換えてしまう。
							contRessya4[idxn][iNoboriTrackRow] = to_tstring(contTrackName.size());

							contTrackName.push_back(TrackNameThis);
							contTrainCountNobori.push_back(1);
						}
					}
				}
				//※番線サイズが下り＜上りの場合有り
				if (contTrackName.size() > 0)
				{
					int iMainTrackKudari = 0;
					int iMainTrackNobori = 0;

					int iMax = -1;

					for (int idxk = 0; idxk < contTrainCountKudari.size(); idxk++)
					{
						if (contTrainCountKudari[idxk] > iMax)
						{
							iMainTrackKudari = idxk;
							iMax = contTrainCountKudari[idxk];
						}
					}
					iMax = -1;
					for (int idxn = 0; idxn < contTrainCountNobori.size(); idxn++)
					{
						if (contTrainCountNobori[idxn] > iMax)
						{
							iMainTrackNobori = idxn;
							iMax = contTrainCountNobori[idxn];
						}
					}

					//駅に番線を設定する
					CentDedEkiTrack2Cont* pCentDedEkiTrack2Cont = aCentDedEki.getEkiTrack2Cont();
					pCentDedEkiTrack2Cont->erase(0, INT_MAX);
					for (int idxTN = 0; idxTN < contTrackName.size(); idxTN++)
					{
						CentDedEkiTrack2 aCentDedEkiTrack2(contTrackName[idxTN], contTrackName[idxTN],_T(""));
						pCentDedEkiTrack2Cont->insert(aCentDedEkiTrack2);
					}
					aCentDedEki.setDownMain(iMainTrackKudari);
					aCentDedEki.setUpMain(iMainTrackNobori);
					aCentDedEki.setJikokuhyouTrackDisplayKudari(true);
					aCentDedEki.setJikokuhyouTrackDisplayNobori(true);
				}

			}

			aCentDedEkiCont.insert(aCentDedEki);
		}

		CaMui<CentDedEki>	aCaCont(pCentDedRosen->getCentDedEkiCont());
		aCaCont.insert(&aCentDedEkiCont);


	}
	/**
		SyubetsuContを作る
	*/
	if (iRv >= 0)
	{
		CentDedRessyasyubetsuCont aCentDedRessyasyubetsuCont;
		vector<tstring> contStrRessyasyubetsu;

		int iKudariRessyameiRow = -1;
		int iNoboriRessyameiRow = -1;

		for (int idxk = 0; idxk < contDigitalContent1.size(); idxk++)
		{
			if (contDigitalContent1[idxk].eTrType == ETrType::TrType_RessyaMei)
			{
				iKudariRessyameiRow = idxk;
			}
		}

		for (int idxn = 0; idxn < contDigitalContent2.size(); idxn++)
		{
			if (contDigitalContent2[idxn].eTrType == ETrType::TrType_RessyaMei)
			{
				iNoboriRessyameiRow = idxn;
			}
		}

		if (iKudariRessyameiRow >= 0)
		{
			for (int idxk = 0; idxk < contRessya1.size(); idxk++)
			{
				tstring strRessyasyubetsu = contRessya1[idxk][iKudariRessyameiRow];
				//tstring::size_type pos = strRessyasyubetsu.find(' ');
				//if (pos != tstring::npos)
				//{
				//	//strRessyasyubetsuに空白が含まれる場合、空白よりも前のみが種別名となる
				//	//(例)特急 踊り子53号→特急、はやぶさ 95→はやぶさ
				//	strRessyasyubetsu = strRessyasyubetsu.substr(0, pos);
				//}

				bool bFound = false;
				for (int idxs = 0; idxs < contStrRessyasyubetsu.size(); idxs++)
				{
					if (contStrRessyasyubetsu[idxs] == strRessyasyubetsu)
					{
						bFound = true;
						break;
					}
				}
				if (!bFound)
				{
					contStrRessyasyubetsu.push_back(strRessyasyubetsu);
				}
			}
			for (int idxk = 0; idxk < contRessya3.size(); idxk++)
			{
				tstring strRessyasyubetsu = contRessya3[idxk][iKudariRessyameiRow];
				//tstring::size_type pos = strRessyasyubetsu.find(' ');
				//if (pos != tstring::npos)
				//{
				//	//strRessyasyubetsuに空白が含まれる場合、空白よりも前のみが種別名となる
				//	//(例)特急 踊り子53号→特急、はやぶさ 95→はやぶさ
				//	strRessyasyubetsu = strRessyasyubetsu.substr(0, pos);
				//}

				bool bFound = false;
				for (int idxs = 0; idxs < contStrRessyasyubetsu.size(); idxs++)
				{
					if (contStrRessyasyubetsu[idxs] == strRessyasyubetsu)
					{
						bFound = true;
						break;
					}
				}
				if (!bFound)
				{
					contStrRessyasyubetsu.push_back(strRessyasyubetsu);
				}
			}
		}

		if (iNoboriRessyameiRow >= 0)
		{
			for (int idxn = 0; idxn < contRessya2.size(); idxn++)
			{
				tstring strRessyasyubetsu = contRessya2[idxn][iNoboriRessyameiRow];
				//tstring::size_type pos = strRessyasyubetsu.find(' ');
				//if (pos != tstring::npos)
				//{
				//	//strRessyasyubetsuに空白が含まれる場合、空白よりも前のみが種別名となる
				//	//(例)特急 踊り子53号→特急、はやぶさ 95→はやぶさ
				//	strRessyasyubetsu = strRessyasyubetsu.substr(0, pos);
				//}

				bool bFound = false;
				for (int idxs = 0; idxs < contStrRessyasyubetsu.size(); idxs++)
				{
					if (contStrRessyasyubetsu[idxs] == strRessyasyubetsu)
					{
						bFound = true;
						break;
					}
				}
				if (!bFound)
				{
					contStrRessyasyubetsu.push_back(strRessyasyubetsu);
				}
			}
			for (int idxn = 0; idxn < contRessya4.size(); idxn++)
			{
				tstring strRessyasyubetsu = contRessya4[idxn][iNoboriRessyameiRow];
				//tstring::size_type pos = strRessyasyubetsu.find(' ');
				//if (pos != tstring::npos)
				//{
				//	//strRessyasyubetsuに空白が含まれる場合、空白よりも前のみが種別名となる
				//	//(例)特急 踊り子53号→特急、はやぶさ 95→はやぶさ
				//	strRessyasyubetsu = strRessyasyubetsu.substr(0, pos);
				//}

				bool bFound = false;
				for (int idxs = 0; idxs < contStrRessyasyubetsu.size(); idxs++)
				{
					if (contStrRessyasyubetsu[idxs] == strRessyasyubetsu)
					{
						bFound = true;
						break;
					}
				}
				if (!bFound)
				{
					contStrRessyasyubetsu.push_back(strRessyasyubetsu);
				}
			}
		}
		for (int idxs = 0; idxs < contStrRessyasyubetsu.size(); idxs++)
		{
			CentDedRessyasyubetsu aCentDedRessyasyubetsu;
			aCentDedRessyasyubetsu.setSyubetsumei(contStrRessyasyubetsu[idxs]);
			aCentDedRessyasyubetsu.setRyakusyou(contStrRessyasyubetsu[idxs]);
			aCentDedRessyasyubetsuCont.insert(aCentDedRessyasyubetsu,INT_MAX);
		}
		*pCentDedRosen->getCentDedRessyasyubetsuCont() = aCentDedRessyasyubetsuCont;

	}
	/**
		Diaを作る
	*/
	if (iRv >= 0)
	{

		CentDedDiaCont aCentDedDiaCont;

		CentDedDia aCentDedDia1;
		int iEkiCount = aCentDedDia1.getEkiCount();
		aCentDedDia1.setName(strDate[0]);

		CentDedRessyaCont	aCentDedRessyaCont1Kudari(
			aCentDedDia1.getCentDedRessyaCont(ERessyahoukou::Ressyahoukou_Kudari)->createEmptyCont());
		CentDedRessyaCont	aCentDedRessyaCont1Nobori(
			aCentDedDia1.getCentDedRessyaCont(ERessyahoukou::Ressyahoukou_Nobori)->createEmptyCont());
		vector<int> MainTrackKudari;
		vector<int> MainTrackNobori;
		CentDedEkiCont* pCentDedEkiCont = pCentDedRosen->getCentDedEkiCont();
		vector<bool> iEkiIndexAddChakuKudari;
		iEkiIndexAddChakuKudari.assign(pCentDedEkiCont->size(), false);
		for (int idxe = 0; idxe < pCentDedEkiCont->size(); idxe++)
		{
			const CentDedEki* pCentDedEki = pCentDedEkiCont->getMuPtr()->get(idxe);
			MainTrackKudari.push_back(pCentDedEki->getDownMain());
			MainTrackNobori.push_back(pCentDedEki->getUpMain());
		}


		vector < vector<tstring>> strOuterEkimei;
		strOuterEkimei.assign(pCentDedEkiCont->size(), {});
		int iKudariOuterShihatsuRow = -1;
		int iKudariOuterShuchakuRow = -1;
		int iNoboriOuterShihatsuRow = -1;
		int iNoboriOuterShuchakuRow = -1;

		for (int idxo = 0; idxo < contDigitalContent1.size(); idxo++)
		{
			if (contDigitalContent1[idxo].eTrType == ETrType::TrType_OuterShihatsu)
			{
				iKudariOuterShihatsuRow = idxo;
			}
			else if (contDigitalContent1[idxo].eTrType == ETrType::TrType_OuterShuchaku)
			{
				iKudariOuterShuchakuRow = idxo;
			}
		}
		for (int idxo = 0; idxo < contDigitalContent2.size(); idxo++)
		{
			if (contDigitalContent2[idxo].eTrType == ETrType::TrType_OuterShihatsu)
			{
				iNoboriOuterShihatsuRow = idxo;
			}
			else if (contDigitalContent2[idxo].eTrType == ETrType::TrType_OuterShuchaku)
			{
				iNoboriOuterShuchakuRow = idxo;
			}
		}

		if (iKudariOuterShihatsuRow >= 0 || iNoboriOuterShuchakuRow >= 0)
		{
			CdDedDispProp aCdDedDispProp = pCDedRosenFileData->getCdDedDispProp();
			aCdDedDispProp.setDisplayOuterTerminalO(true);
			pCDedRosenFileData->setCdDedDispProp(aCdDedDispProp);

			CentDedEki aCentDedEki = pCentDedEkiCont->get(0);
			aCentDedEki.setJikokuhyouOuterSihatsuDisplayKudari(true);
			aCentDedEki.setJikokuhyouOuterShuchakuDisplayNobori(true);
			pCentDedEkiCont->set(aCentDedEki, 0);

		}
		if (iKudariOuterShuchakuRow >= 0 || iNoboriOuterShihatsuRow >= 0)
		{
			CdDedDispProp aCdDedDispProp = pCDedRosenFileData->getCdDedDispProp();
			aCdDedDispProp.setDisplayOuterTerminalT(true);
			pCDedRosenFileData->setCdDedDispProp(aCdDedDispProp);

			CentDedEki aCentDedEki = pCentDedEkiCont->get(INT_MAX);
			aCentDedEki.setJikokuhyouOuterShuchakuDisplayKudari(true);
			aCentDedEki.setJikokuhyouOuterSihatsuDisplayNobori(true);
			pCentDedEkiCont->set(aCentDedEki, INT_MAX);
		}




		for (int idxk = 0; idxk < contRessya1.size(); idxk++)
		{
			//CentDedRessya	aCentDedRessya(aCentDedRessyaCont1Kudari.createNullRessya());
			CentDedRessya	aCentDedRessya(pCentDedEkiCont->size(),ERessyahoukou::Ressyahoukou_Kudari);
			bool bIsSyubetsuChange = false;

			for (int idx = 0; idx < contDigitalContent1.size(); idx++)
			{
				if (contDigitalContent1[idx].eTrType == ETrType::TrType_RessyaBangou)
				{
					aCentDedRessya.setRessyabangou(contRessya1[idxk][idx]);
				}
				else if (contDigitalContent1[idx].eTrType == ETrType::TrType_Ressyasyubetsu)
				{
					tstring strRessyasyubetsu = contRessya1[idxk][idx];
					const CentDedRessyasyubetsuCont* pCentDedRessyasyubetsuCont = pCentDedRosen->getCentDedRessyasyubetsuCont();
					int iRessyasyubetsuIndex = 0;
					for (int idxs = 0; idxs < pCentDedRessyasyubetsuCont->size(); idxs++)
					{
						if (pCentDedRessyasyubetsuCont->get(idxs).getSyubetsumei() == strRessyasyubetsu)
						{
							iRessyasyubetsuIndex = idxs;
							break;
						}
					}
					aCentDedRessya.setRessyasyubetsuIndex(iRessyasyubetsuIndex);
				}
				else if (contDigitalContent1[idx].eTrType == ETrType::TrType_RessyaMei)
				{
					//JR北海道暫定処置、列車種別は、列車名から取る。
					tstring strRessyasyubetsu = contRessya1[idxk][idx];
					const CentDedRessyasyubetsuCont* pCentDedRessyasyubetsuCont = pCentDedRosen->getCentDedRessyasyubetsuCont();
					int iRessyasyubetsuIndex = 0;
					for (int idxs = 0; idxs < pCentDedRessyasyubetsuCont->size(); idxs++)
					{
						if (pCentDedRessyasyubetsuCont->get(idxs).getSyubetsumei() == strRessyasyubetsu)
						{
							iRessyasyubetsuIndex = idxs;
							break;
						}
					}
					aCentDedRessya.setRessyasyubetsuIndex(iRessyasyubetsuIndex);
					aCentDedRessya.setRessyamei(contRessya1[idxk][idx]);
				}
				else if (contDigitalContent1[idx].eTrType == ETrType::TrType_GouSuu)
				{
					//JR北海道暫定処置：号数が空の場合は、列車名を空にする。そのため、号数のない特急等は、列車名が空となる。
					if (contRessya1[idxk][idx].empty())
					{
						aCentDedRessya.setRessyamei(_T(""));
					}
					aCentDedRessya.setGousuu(contRessya1[idxk][idx]);
				}
				else if (contDigitalContent1[idx].eTrType == ETrType::TrType_UntenBi)
				{
					aCentDedRessya.setBikou(contRessya1[idxk][idx]);
				}
				else if (contDigitalContent1[idx].eTrType == ETrType::TrType_EkiChaku)
				{
					int iEkiOrder = pCentDedEkiCont->EkiOrderOfEkiIndex(ERessyahoukou::Ressyahoukou_Kudari, contDigitalContent1[idx].iEkiIndex);
					CentDedEkiJikoku	aCentDedEkiJikoku = aCentDedRessya.getCentDedEkiJikoku(iEkiOrder);

					if (contRessya1[idxk][idx] == _T("＝"))//前駅止まり
					{
						//一つ上の前の駅の発時刻を着時刻にコピーする
						CentDedEkiJikoku	aCentDedEkiJikokuBefore = aCentDedRessya.getCentDedEkiJikoku(iEkiOrder - 1);
						aCentDedEkiJikokuBefore.setChakujikoku(aCentDedEkiJikokuBefore.getHatsujikoku());
						aCentDedEkiJikokuBefore.setHatsujikoku(CdDedJikoku());
						aCentDedRessya.setCentDedEkiJikoku(iEkiOrder - 1, aCentDedEkiJikokuBefore);

						//一つ前の駅の駅時刻形式を着ありに変更させる
						iEkiIndexAddChakuKudari[contDigitalContent1[idx].iEkiIndex - 1] = true;

						//continue;
					}
					else if (contRessya1[idxk][idx] == _T("||"))//経由なし
					{
						//continue;
					}
					else if (contRessya1[idxk][idx] == _T("・"))//路線外発着
					{
						//continue;
					}
					else if (contRessya1[idxk][idx] == _T("┐"))//種別変更、分割
					{
						bIsSyubetsuChange = true;
					}
					else if (contRessya1[idxk][idx] == _T("┘"))//併合
					{
						//continue;
					}
					else if (contRessya1[idxk][idx] == _T("レ"))//通過
					{
						aCentDedEkiJikoku.setEkiatsukai(CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka);
						//通過の場合、番線表示がないので、主本線を設定しておく。
						aCentDedEkiJikoku.setRessyaTrackIndex(MainTrackKudari[contDigitalContent1[idx].iEkiIndex]);
					}
					else if (contRessya1[idxk][idx].empty())
					{
						//continue;
					}
					else
					{
						aCentDedEkiJikoku.setEkiatsukai(CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya);
						aCentDedEkiJikoku.setChakujikoku(CdDedJikoku(contRessya1[idxk][idx]));
						//停車の場合、番線表示がある可能を考慮し、番線が0未満(未設定)なら主本線を設定しておく。
						if (aCentDedEkiJikoku.getRessyaTrackIndex() < 0)
						{
							aCentDedEkiJikoku.setRessyaTrackIndex(MainTrackKudari[contDigitalContent1[idx].iEkiIndex]);
						}
					}
					aCentDedRessya.setCentDedEkiJikoku(contDigitalContent1[idx].iEkiIndex, aCentDedEkiJikoku);
				}
				else if (contDigitalContent1[idx].eTrType == ETrType::TrType_EkiBansen)
				{
					int iEkiOrder = pCentDedEkiCont->EkiOrderOfEkiIndex(ERessyahoukou::Ressyahoukou_Kudari, contDigitalContent1[idx].iEkiIndex);
					//contRessya1[idxk][idx]の中身が、(番線)だった場合は、番線Indexに置き換え済みなので、数字に変換して番線Indexとして指定する。
					if (!contRessya1[idxk][idx].empty() &&_istdigit(contRessya1[idxk][idx][0]) != 0)
					{
						CentDedEkiJikoku	aCentDedEkiJikoku = aCentDedRessya.getCentDedEkiJikoku(iEkiOrder);
						aCentDedEkiJikoku.setRessyaTrackIndex(_ttoi(contRessya1[idxk][idx].c_str()));
						aCentDedRessya.setCentDedEkiJikoku(iEkiOrder, aCentDedEkiJikoku);
					}
					else if (contRessya1[idxk][idx] == _T("＝"))//前駅止まり
					{
						//一つ上の前の駅の発時刻を着時刻にコピーする
						CentDedEkiJikoku	aCentDedEkiJikokuBefore = aCentDedRessya.getCentDedEkiJikoku(iEkiOrder - 1);
						aCentDedEkiJikokuBefore.setChakujikoku(aCentDedEkiJikokuBefore.getHatsujikoku());
						aCentDedEkiJikokuBefore.setHatsujikoku(CdDedJikoku());
						aCentDedRessya.setCentDedEkiJikoku(iEkiOrder - 1, aCentDedEkiJikokuBefore);

						//一つ前の駅の駅時刻形式を着ありに変更させる
						iEkiIndexAddChakuKudari[contDigitalContent1[idx].iEkiIndex - 1] = true;

						//continue;
					}
				}
				else if (contDigitalContent1[idx].eTrType == ETrType::TrType_EkiHatsu)
				{
					int iEkiOrder = pCentDedEkiCont->EkiOrderOfEkiIndex(ERessyahoukou::Ressyahoukou_Kudari, contDigitalContent1[idx].iEkiIndex);
					CentDedEkiJikoku	aCentDedEkiJikoku = aCentDedRessya.getCentDedEkiJikoku(iEkiOrder);
					if (contRessya1[idxk][idx] == _T("＝"))//前駅止まり
					{
						//おでかけネットの場合、着発時刻がある駅止まりでも、発時刻欄に＝を表示するので、一つ上の項目が同じ駅(の着時刻)がどうかを調べる
						if (contDigitalContent1[idx].iEkiIndex != contDigitalContent1[idx - 1].iEkiIndex)
						{
							//一つ上の前の駅の発時刻を着時刻にコピーする
							CentDedEkiJikoku	aCentDedEkiJikokuBefore = aCentDedRessya.getCentDedEkiJikoku(iEkiOrder - 1);
							aCentDedEkiJikokuBefore.setChakujikoku(aCentDedEkiJikokuBefore.getHatsujikoku());
							aCentDedEkiJikokuBefore.setHatsujikoku(CdDedJikoku());
							aCentDedRessya.setCentDedEkiJikoku(iEkiOrder - 1, aCentDedEkiJikokuBefore);

							//一つ前の駅の駅時刻形式を着ありに変更させる
							iEkiIndexAddChakuKudari[contDigitalContent1[idx].iEkiIndex - 1] = true;
						}

						//continue;
					}
					else if (contRessya1[idxk][idx] == _T("||"))//経由なし
					{
						//continue;
					}
					else if (contRessya1[idxk][idx] == _T("・"))//路線外発着
					{
						//continue;
					}
					else if (contRessya1[idxk][idx] == _T("┐"))//種別変更、分割
					{
						bIsSyubetsuChange = true;
					}
					else if (contRessya1[idxk][idx] == _T("┘"))//併合
					{
						//continue;
					}
					else if (contRessya1[idxk][idx] == _T("レ"))//通過
					{
						aCentDedEkiJikoku.setEkiatsukai(CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka);
						//通過の場合、番線表示がないので、主本線を設定しておく。
						aCentDedEkiJikoku.setRessyaTrackIndex(MainTrackKudari[contDigitalContent1[idx].iEkiIndex]);
					}
					else if (contRessya1[idxk][idx].empty())
					{
						//continue;
					}
					else
					{
						aCentDedEkiJikoku.setEkiatsukai(CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya);
						aCentDedEkiJikoku.setHatsujikoku(CdDedJikoku(contRessya1[idxk][idx]));
						//通過の場合、番線表示がある可能を考慮し、番線が0未満(未設定)なら主本線を設定しておく。
						if (aCentDedEkiJikoku.getRessyaTrackIndex() < 0)
						{
							aCentDedEkiJikoku.setRessyaTrackIndex(MainTrackKudari[contDigitalContent1[idx].iEkiIndex]);
						}
					}

					aCentDedRessya.setCentDedEkiJikoku(iEkiOrder, aCentDedEkiJikoku);
				}
			}

			if (bIsSyubetsuChange)
			{
				//bIsSyubetsuChangeなら一つ前の列の列車を呼び出し、その列車の終着駅とこの列車の始発駅が同一なら、
				//種別を確認し、種別が同じなら列車情報変更、異なるなら種別変更を前の列車に設定する。
				CentDedRessya* pCentDedRessyaBefore = aCentDedRessyaCont1Kudari.getMuPtr()->get(idxk - 1);
				if (aCentDedRessya.getValidSihatsuEki() == pCentDedRessyaBefore->getValidSyuuchakuEki())
				{
					if (aCentDedRessya.getRessyasyubetsuIndex() == pCentDedRessyaBefore->getRessyasyubetsuIndex())
					{
						CentDedEkiJikoku aCentDedEkiJikoku = pCentDedRessyaBefore->getCentDedEkiJikoku(pCentDedRessyaBefore->getValidSyuuchakuEki());
						CentDedAfterOperation aCentDedAfterOperation(
							CentDedAfterOperation::EAOperation::AOperation_Junction,
							CdDedJikoku(),
							2);
						aCentDedEkiJikoku.getCentDedAfterOperationCont()->insert(aCentDedAfterOperation, 0);
						pCentDedRessyaBefore->setCentDedEkiJikoku(pCentDedRessyaBefore->getValidSyuuchakuEki(), aCentDedEkiJikoku);
					}
					else
					{
						CentDedEkiJikoku aCentDedEkiJikoku = pCentDedRessyaBefore->getCentDedEkiJikoku(pCentDedRessyaBefore->getValidSyuuchakuEki());
						CentDedAfterOperation aCentDedAfterOperation(
							CentDedAfterOperation::EAOperation::AOperation_Junction,
							CdDedJikoku(),
							1);
						aCentDedEkiJikoku.getCentDedAfterOperationCont()->insert(aCentDedAfterOperation, 0);
						pCentDedRessyaBefore->setCentDedEkiJikoku(pCentDedRessyaBefore->getValidSyuuchakuEki(), aCentDedEkiJikoku);
					}
				}
			}

			if (iKudariOuterShihatsuRow >= 0 &&!contRessya1[idxk][iKudariOuterShihatsuRow].empty())
			{
				tstring strEkimei = contRessya1[idxk][iKudariOuterShihatsuRow];
				tstring strJikoku;
				if (_istdigit(strEkimei[strEkimei.size() - 4]) != 0)
				{
					strJikoku = strEkimei.substr(strEkimei.size() - 4, 4);
					strEkimei = strEkimei.substr(0, strEkimei.size() - 4);
				}
				else
				{
					strJikoku = strEkimei.substr(strEkimei.size() - 3, 3);
					strEkimei = strEkimei.substr(0, strEkimei.size() - 3);
				}

				bool bFound = false;
				for (int idxe = 0; idxe < pCentDedEkiCont->size(); idxe++)
				{
					const CentDedEki* pCentDedEki = pCentDedEkiCont->getMuPtr()->get(idxe);
					if (strEkimei == pCentDedEki->getEkimei())
					{
						bFound = true;
						break;
					}
				}

				if (!bFound)
				{
					int iShihatsuEkiOrder = aCentDedRessya.getSihatsuEki();
					if (iShihatsuEkiOrder >= 0)
					{
						int iShihatsuEkiIndex = aCentDedRessya.EkiIndexOfEkiOrder(iShihatsuEkiOrder);
						int iOuterIndex = -1;
						for (int idxo = 0; idxo < strOuterEkimei[iShihatsuEkiIndex].size(); idxo++)
						{
							if (strOuterEkimei[iShihatsuEkiIndex][idxo] == strEkimei)
							{
								iOuterIndex = idxo;
								break;
							}
						}
						if (iOuterIndex == -1)
						{
							iOuterIndex = strOuterEkimei[iShihatsuEkiIndex].size();
							CentDedEki aCentDedEki = pCentDedEkiCont->get(iShihatsuEkiIndex);
							aCentDedEki.addOuterTerminalEkimei(OuterTerminal(strEkimei, strEkimei, strEkimei.substr(0, 1)));
							pCentDedEkiCont->set(aCentDedEki, iShihatsuEkiIndex);

							strOuterEkimei[iShihatsuEkiIndex].push_back(strEkimei);
						}

						CentDedEkiJikoku aCentDedEkiJikoku = aCentDedRessya.getCentDedEkiJikoku(iShihatsuEkiOrder);
						CentDedBeforeOperation aCentDedBeforeOperation(
							CentDedBeforeOperation::EBOperation::BOperation_Outer,
							iOuterIndex,
							CdDedJikoku(strJikoku),
							aCentDedEkiJikoku.getChakujikoku(true),
							vector<tstring>(),
							tstring());
						aCentDedEkiJikoku.setChakujikoku(CdDedJikoku());
						aCentDedEkiJikoku.getCentDedBeforeOperationCont()->insert(aCentDedBeforeOperation, 0);
						aCentDedRessya.setCentDedEkiJikoku(iShihatsuEkiOrder, aCentDedEkiJikoku);
					}
				}
			}

			if (iKudariOuterShuchakuRow >= 0 && !contRessya1[idxk][iKudariOuterShuchakuRow].empty())
			{
				tstring strEkimei = contRessya1[idxk][iKudariOuterShuchakuRow];
				tstring strJikoku;
				if (_istdigit(strEkimei[strEkimei.size() - 4]) != 0)
				{
					strJikoku = strEkimei.substr(strEkimei.size() - 4, 4);
					strEkimei = strEkimei.substr(0, strEkimei.size() - 4);
				}
				else
				{
					strJikoku = strEkimei.substr(strEkimei.size() - 3, 3);
					strEkimei = strEkimei.substr(0, strEkimei.size() - 3);
				}

				bool bFound = false;
				for (int idxe = 0; idxe < pCentDedEkiCont->size(); idxe++)
				{
					const CentDedEki* pCentDedEki = pCentDedEkiCont->getMuPtr()->get(idxe);
					if (strEkimei == pCentDedEki->getEkimei())
					{
						bFound = true;
						break;
					}
				}

				if (!bFound)
				{
					int iShuchakuEkiOrder = aCentDedRessya.getSyuuchakuEki();
					if (iShuchakuEkiOrder >= 0)
					{
						int iShuchakuEkiIndex = aCentDedRessya.EkiIndexOfEkiOrder(iShuchakuEkiOrder);
						int iOuterIndex = -1;
						for (int idxo = 0; idxo < strOuterEkimei[iShuchakuEkiIndex].size(); idxo++)
						{
							if (strOuterEkimei[iShuchakuEkiIndex][idxo] == strEkimei)
							{
								iOuterIndex = idxo;
								break;
							}
						}
						if (iOuterIndex == -1)
						{
							iOuterIndex = strOuterEkimei[iShuchakuEkiIndex].size();
							CentDedEki aCentDedEki = pCentDedEkiCont->get(iShuchakuEkiIndex);
							aCentDedEki.addOuterTerminalEkimei(OuterTerminal(strEkimei, strEkimei, strEkimei.substr(0, 1)));
							pCentDedEkiCont->set(aCentDedEki, iShuchakuEkiIndex);

							strOuterEkimei[iShuchakuEkiIndex].push_back(strEkimei);
						}

						CentDedEkiJikoku aCentDedEkiJikoku = aCentDedRessya.getCentDedEkiJikoku(iShuchakuEkiOrder);
						//着時刻がない場合を考慮し、着時刻がNULLの場合は、発時刻を着時刻にコピーする。
						if (aCentDedEkiJikoku.getChakujikoku().isNull())
						{
							aCentDedEkiJikoku.setChakujikoku(aCentDedEkiJikoku.getHatsujikoku());
						}
						CentDedAfterOperation aCentDedAfterOperation(
							CentDedAfterOperation::EAOperation::AOperation_Outer,
							iOuterIndex,
							aCentDedEkiJikoku.getHatsujikoku(true),
							CdDedJikoku(strJikoku),
							tstring());
						aCentDedEkiJikoku.setHatsujikoku(CdDedJikoku());
						aCentDedEkiJikoku.getCentDedAfterOperationCont()->insert(aCentDedAfterOperation, 0);
						aCentDedRessya.setCentDedEkiJikoku(iShuchakuEkiOrder, aCentDedEkiJikoku);
					}
				}
			}

			aCentDedRessyaCont1Kudari.insert(aCentDedRessya);

			//一つ前の駅の駅時刻形式を着ありに変更させる
			for (int idxe = 0; idxe < iEkiIndexAddChakuKudari.size(); idxe++)
			{
				if (iEkiIndexAddChakuKudari[idxe])
				{
					CentDedEki aCentDedEki = pCentDedEkiCont->get(idxe);

					if (aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsu)
					{
						aCentDedEki.setEkijikokukeisiki(CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku);
					}
					else if (aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
					{
						aCentDedEki.setEkijikokukeisiki(CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku);
					}
					else if (aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku)
					{
						aCentDedEki.setEkijikokukeisiki(CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku);
					}

					pCentDedEkiCont->set(aCentDedEki, idxe);
				}
			}
		}


		//ここから上りダイヤ1
		vector<bool> iEkiIndexAddChakuNobori;
		iEkiIndexAddChakuNobori.assign(pCentDedEkiCont->size(), false);

		for (int idxn = 0; idxn < contRessya2.size(); idxn++)
		{
			//CentDedRessya	aCentDedRessya(aCentDedRessyaCont1Kudari.createNullRessya());
			CentDedRessya	aCentDedRessya(pCentDedEkiCont->size(), ERessyahoukou::Ressyahoukou_Nobori);
			bool bIsSyubetsuChange = false;

			for (int idx = 0; idx < contDigitalContent2.size(); idx++)
			{
				if (contDigitalContent2[idx].eTrType == ETrType::TrType_RessyaBangou)
				{
					aCentDedRessya.setRessyabangou(contRessya2[idxn][idx]);
				}
				else if (contDigitalContent2[idx].eTrType == ETrType::TrType_Ressyasyubetsu)
				{
					tstring strRessyasyubetsu = contRessya2[idxn][idx];
					const CentDedRessyasyubetsuCont* pCentDedRessyasyubetsuCont = pCentDedRosen->getCentDedRessyasyubetsuCont();
					int iRessyasyubetsuIndex = 0;
					for (int idxs = 0; idxs < pCentDedRessyasyubetsuCont->size(); idxs++)
					{
						if (pCentDedRessyasyubetsuCont->get(idxs).getSyubetsumei() == strRessyasyubetsu)
						{
							iRessyasyubetsuIndex = idxs;
							break;
						}
					}
					aCentDedRessya.setRessyasyubetsuIndex(iRessyasyubetsuIndex);
				}
				else if (contDigitalContent2[idx].eTrType == ETrType::TrType_RessyaMei)
				{
					//JR北海道暫定処置、列車種別は、列車名から取る。
					tstring strRessyasyubetsu = contRessya2[idxn][idx];
					const CentDedRessyasyubetsuCont* pCentDedRessyasyubetsuCont = pCentDedRosen->getCentDedRessyasyubetsuCont();
					int iRessyasyubetsuIndex = 0;
					for (int idxs = 0; idxs < pCentDedRessyasyubetsuCont->size(); idxs++)
					{
						if (pCentDedRessyasyubetsuCont->get(idxs).getSyubetsumei() == strRessyasyubetsu)
						{
							iRessyasyubetsuIndex = idxs;
							break;
						}
					}
					aCentDedRessya.setRessyasyubetsuIndex(iRessyasyubetsuIndex);
					aCentDedRessya.setRessyamei(contRessya2[idxn][idx]);
				}
				else if (contDigitalContent2[idx].eTrType == ETrType::TrType_GouSuu)
				{
					//JR北海道暫定処置：号数が空の場合は、列車名を空にする。そのため、号数のない特急等は、列車名が空となる。
					if (contRessya2[idxn][idx].empty())
					{
						aCentDedRessya.setRessyamei(_T(""));
					}
					aCentDedRessya.setGousuu(contRessya2[idxn][idx]);
				}
				else if (contDigitalContent2[idx].eTrType == ETrType::TrType_UntenBi)
				{
					aCentDedRessya.setBikou(contRessya2[idxn][idx]);
				}
				else if (contDigitalContent2[idx].eTrType == ETrType::TrType_EkiChaku)
				{
					int iEkiOrder = pCentDedEkiCont->EkiOrderOfEkiIndex(ERessyahoukou::Ressyahoukou_Nobori, contDigitalContent2[idx].iEkiIndex);
					CentDedEkiJikoku	aCentDedEkiJikoku = aCentDedRessya.getCentDedEkiJikoku(iEkiOrder);
					if (contRessya2[idxn][idx] == _T("＝"))//前駅止まり
					{
						//一つ上の前の駅の発時刻を着時刻にコピーする
						CentDedEkiJikoku	aCentDedEkiJikokuBefore = aCentDedRessya.getCentDedEkiJikoku(iEkiOrder - 1);
						aCentDedEkiJikokuBefore.setChakujikoku(aCentDedEkiJikokuBefore.getHatsujikoku());
						aCentDedEkiJikokuBefore.setHatsujikoku(CdDedJikoku());
						aCentDedRessya.setCentDedEkiJikoku(iEkiOrder - 1, aCentDedEkiJikokuBefore);

						//一つ前(上りなのでIndexは+1)の駅の駅時刻形式を着ありに変更させる
						iEkiIndexAddChakuNobori[contDigitalContent2[idx].iEkiIndex + 1] = true;

						//continue;
					}
					else if (contRessya2[idxn][idx] == _T("||"))//経由なし
					{
						//continue;
					}
					else if (contRessya2[idxn][idx] == _T("・"))//路線外発着
					{
						//continue;
					}
					else if (contRessya2[idxn][idx] == _T("┐"))//種別変更、分割
					{
						bIsSyubetsuChange = true;
					}
					else if (contRessya2[idxn][idx] == _T("┘"))//併合
					{
						//continue;
					}
					else if (contRessya2[idxn][idx] == _T("レ"))//通過
					{
						aCentDedEkiJikoku.setEkiatsukai(CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka);
						//通過の場合、番線表示がないので、主本線を設定しておく。
						aCentDedEkiJikoku.setRessyaTrackIndex(MainTrackNobori[contDigitalContent2[idx].iEkiIndex]);
					}
					else if (contRessya2[idxn][idx].empty())
					{
						//continue;
					}
					else
					{
						aCentDedEkiJikoku.setEkiatsukai(CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya);
						aCentDedEkiJikoku.setChakujikoku(CdDedJikoku(contRessya2[idxn][idx]));
						//停車の場合、番線表示がある可能を考慮し、番線が0未満(未設定)なら主本線を設定しておく。
						if (aCentDedEkiJikoku.getRessyaTrackIndex() < 0)
						{
							aCentDedEkiJikoku.setRessyaTrackIndex(MainTrackNobori[contDigitalContent2[idx].iEkiIndex]);
						}
					}
					aCentDedRessya.setCentDedEkiJikoku(iEkiOrder, aCentDedEkiJikoku);
				}
				else if (contDigitalContent2[idx].eTrType == ETrType::TrType_EkiBansen)
				{
					int iEkiOrder = pCentDedEkiCont->EkiOrderOfEkiIndex(ERessyahoukou::Ressyahoukou_Nobori, contDigitalContent2[idx].iEkiIndex);
					//contRessya2[idxk][idx]の中身が、(番線)だった場合は、番線Indexに置き換え済みなので、数字に変換して番線Indexとして指定する。
					if (!contRessya2[idxn][idx].empty() && _istdigit(contRessya2[idxn][idx][0]) != 0)
					{
						CentDedEkiJikoku	aCentDedEkiJikoku = aCentDedRessya.getCentDedEkiJikoku(iEkiOrder);
						if (aCentDedRessya.getCentDedEkiJikokuCount() == iEkiOrder + 1)
						{
							aCentDedEkiJikoku = aCentDedRessya.getCentDedEkiJikoku(iEkiOrder);
						}
						aCentDedEkiJikoku.setRessyaTrackIndex(_ttoi(contRessya2[idxn][idx].c_str()));

						aCentDedRessya.setCentDedEkiJikoku(iEkiOrder, aCentDedEkiJikoku);
					}
					else if (contRessya2[idxn][idx] == _T("＝"))//前駅止まり
					{
						//一つ上の前の駅の発時刻を着時刻にコピーする
						CentDedEkiJikoku	aCentDedEkiJikokuBefore = aCentDedRessya.getCentDedEkiJikoku(iEkiOrder - 1);
						aCentDedEkiJikokuBefore.setChakujikoku(aCentDedEkiJikokuBefore.getHatsujikoku());
						aCentDedEkiJikokuBefore.setHatsujikoku(CdDedJikoku());
						aCentDedRessya.setCentDedEkiJikoku(iEkiOrder - 1, aCentDedEkiJikokuBefore);

						//一つ前(上りなのでIndexは+1)の駅の駅時刻形式を着ありに変更させる
						iEkiIndexAddChakuNobori[contDigitalContent2[idx].iEkiIndex + 1] = true;

						//continue;
					}
				}
				else if (contDigitalContent2[idx].eTrType == ETrType::TrType_EkiHatsu)
				{
					int iEkiOrder = pCentDedEkiCont->EkiOrderOfEkiIndex(ERessyahoukou::Ressyahoukou_Nobori, contDigitalContent2[idx].iEkiIndex);
					CentDedEkiJikoku	aCentDedEkiJikoku = aCentDedRessya.getCentDedEkiJikoku(iEkiOrder);
					if (contRessya2[idxn][idx] == _T("＝"))//前駅止まり
					{
						//おでかけネットの場合、着発時刻がある駅止まりでも、発時刻欄に＝を表示するので、一つ上の項目が同じ駅(の着時刻)がどうかを調べる
						if (contDigitalContent2[idx].iEkiIndex != contDigitalContent2[idx - 1].iEkiIndex)
						{
							//一つ上の前の駅の発時刻を着時刻にコピーする
							CentDedEkiJikoku	aCentDedEkiJikokuBefore = aCentDedRessya.getCentDedEkiJikoku(iEkiOrder - 1);
							aCentDedEkiJikokuBefore.setChakujikoku(aCentDedEkiJikokuBefore.getHatsujikoku());
							aCentDedEkiJikokuBefore.setHatsujikoku(CdDedJikoku());
							aCentDedRessya.setCentDedEkiJikoku(iEkiOrder - 1, aCentDedEkiJikokuBefore);

							//一つ前(上りなのでIndexは+1)の駅の駅時刻形式を着ありに変更させる
							iEkiIndexAddChakuNobori[contDigitalContent2[idx].iEkiIndex + 1] = true;
						}

						//continue;
					}
					else if (contRessya2[idxn][idx] == _T("||"))//経由なし
					{
						//continue;
					}
					else if (contRessya2[idxn][idx] == _T("・"))//路線外発着
					{
						//continue;
					}
					else if (contRessya2[idxn][idx] == _T("┐"))//種別変更、分割
					{
						bIsSyubetsuChange = true;
					}
					else if (contRessya2[idxn][idx] == _T("┘"))//併合
					{
						//continue;
					}
					else if (contRessya2[idxn][idx] == _T("レ"))//通過
					{
						aCentDedEkiJikoku.setEkiatsukai(CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka);
						//通過の場合、番線表示がないので、主本線を設定しておく。
						aCentDedEkiJikoku.setRessyaTrackIndex(MainTrackNobori[contDigitalContent2[idx].iEkiIndex]);
					}
					else if (contRessya2[idxn][idx].empty())
					{
						//continue;
					}
					else
					{
						aCentDedEkiJikoku.setEkiatsukai(CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya);
						aCentDedEkiJikoku.setHatsujikoku(CdDedJikoku(contRessya2[idxn][idx]));
						//番線表示がある可能を考慮し、番線が0未満(未設定)なら主本線を設定しておく。
						if (aCentDedEkiJikoku.getRessyaTrackIndex() < 0)
						{
							aCentDedEkiJikoku.setRessyaTrackIndex(MainTrackNobori[contDigitalContent2[idx].iEkiIndex]);
						}
					}
					aCentDedRessya.setCentDedEkiJikoku(iEkiOrder, aCentDedEkiJikoku);
				}
			}

			if (bIsSyubetsuChange)
			{
				//bIsSyubetsuChangeなら一つ前の列の列車を呼び出し、その列車の終着駅とこの列車の始発駅が同一なら、
				//種別を確認し、種別が同じなら列車情報変更、異なるなら種別変更を前の列車に設定する。
				CentDedRessya* pCentDedRessyaBefore = aCentDedRessyaCont1Nobori.getMuPtr()->get(idxn - 1);
				if (aCentDedRessya.getValidSihatsuEki() == pCentDedRessyaBefore->getValidSyuuchakuEki())
				{
					if (aCentDedRessya.getRessyasyubetsuIndex() == pCentDedRessyaBefore->getRessyasyubetsuIndex())
					{
						CentDedEkiJikoku aCentDedEkiJikoku = pCentDedRessyaBefore->getCentDedEkiJikoku(pCentDedRessyaBefore->getValidSyuuchakuEki());
						CentDedAfterOperation aCentDedAfterOperation(
							CentDedAfterOperation::EAOperation::AOperation_Junction,
							CdDedJikoku(),
							2);
						aCentDedEkiJikoku.getCentDedAfterOperationCont()->insert(aCentDedAfterOperation, 0);
						pCentDedRessyaBefore->setCentDedEkiJikoku(pCentDedRessyaBefore->getValidSyuuchakuEki(), aCentDedEkiJikoku);
					}
					else
					{
						CentDedEkiJikoku aCentDedEkiJikoku = pCentDedRessyaBefore->getCentDedEkiJikoku(pCentDedRessyaBefore->getValidSyuuchakuEki());
						CentDedAfterOperation aCentDedAfterOperation(
							CentDedAfterOperation::EAOperation::AOperation_Junction,
							CdDedJikoku(),
							1);
						aCentDedEkiJikoku.getCentDedAfterOperationCont()->insert(aCentDedAfterOperation, 0);
						pCentDedRessyaBefore->setCentDedEkiJikoku(pCentDedRessyaBefore->getValidSyuuchakuEki(), aCentDedEkiJikoku);
					}
				}
			}

			if (iNoboriOuterShihatsuRow >= 0 && !contRessya2[idxn][iNoboriOuterShihatsuRow].empty())
			{
				tstring strEkimei = contRessya2[idxn][iNoboriOuterShihatsuRow];
				tstring strJikoku;
				if (_istdigit(strEkimei[strEkimei.size() - 4]) != 0)
				{
					strJikoku = strEkimei.substr(strEkimei.size() - 4, 4);
					strEkimei = strEkimei.substr(0, strEkimei.size() - 4);
				}
				else
				{
					strJikoku = strEkimei.substr(strEkimei.size() - 3, 3);
					strEkimei = strEkimei.substr(0, strEkimei.size() - 3);
				}

				bool bFound = false;
				for (int idxe = 0; idxe < pCentDedEkiCont->size(); idxe++)
				{
					const CentDedEki* pCentDedEki = pCentDedEkiCont->getMuPtr()->get(idxe);
					if (strEkimei == pCentDedEki->getEkimei())
					{
						bFound = true;
						break;
					}
				}

				if (!bFound)
				{
					int iShihatsuEkiOrder = aCentDedRessya.getSihatsuEki();
					if (iShihatsuEkiOrder >= 0)
					{
						int iShihatsuEkiIndex = aCentDedRessya.EkiIndexOfEkiOrder(iShihatsuEkiOrder);
						int iOuterIndex = -1;
						for (int idxo = 0; idxo < strOuterEkimei[iShihatsuEkiIndex].size(); idxo++)
						{
							if (strOuterEkimei[iShihatsuEkiIndex][idxo] == strEkimei)
							{
								iOuterIndex = idxo;
								break;
							}
						}
						if (iOuterIndex == -1)
						{
							iOuterIndex = strOuterEkimei[iShihatsuEkiIndex].size();
							CentDedEki aCentDedEki = pCentDedEkiCont->get(iShihatsuEkiIndex);
							aCentDedEki.addOuterTerminalEkimei(OuterTerminal(strEkimei, strEkimei, strEkimei.substr(0, 1)));
							pCentDedEkiCont->set(aCentDedEki, iShihatsuEkiIndex);

							strOuterEkimei[iShihatsuEkiIndex].push_back(strEkimei);
						}

						CentDedEkiJikoku aCentDedEkiJikoku = aCentDedRessya.getCentDedEkiJikoku(iShihatsuEkiOrder);
						CentDedBeforeOperation aCentDedBeforeOperation(
							CentDedBeforeOperation::EBOperation::BOperation_Outer,
							iOuterIndex,
							CdDedJikoku(strJikoku),
							aCentDedEkiJikoku.getChakujikoku(true),
							vector<tstring>(),
							tstring());
						aCentDedEkiJikoku.setChakujikoku(CdDedJikoku());
						aCentDedEkiJikoku.getCentDedBeforeOperationCont()->insert(aCentDedBeforeOperation, 0);
						aCentDedRessya.setCentDedEkiJikoku(iShihatsuEkiOrder, aCentDedEkiJikoku);
					}
				}
			}

			if (iNoboriOuterShuchakuRow >= 0 && !contRessya2[idxn][iNoboriOuterShuchakuRow].empty())
			{
				tstring strEkimei = contRessya2[idxn][iNoboriOuterShuchakuRow];
				tstring strJikoku;
				if (_istdigit(strEkimei[strEkimei.size() - 4]) != 0)
				{
					strJikoku = strEkimei.substr(strEkimei.size() - 4, 4);
					strEkimei = strEkimei.substr(0, strEkimei.size() - 4);
				}
				else
				{
					strJikoku = strEkimei.substr(strEkimei.size() - 3, 3);
					strEkimei = strEkimei.substr(0, strEkimei.size() - 3);
				}

				bool bFound = false;
				for (int idxe = 0; idxe < pCentDedEkiCont->size(); idxe++)
				{
					const CentDedEki* pCentDedEki = pCentDedEkiCont->getMuPtr()->get(idxe);
					if (strEkimei == pCentDedEki->getEkimei())
					{
						bFound = true;
						break;
					}
				}

				if (!bFound)
				{
					int iShuchakuEkiOrder = aCentDedRessya.getSyuuchakuEki();
					if (iShuchakuEkiOrder >= 0)
					{
						int iShuchakuEkiIndex = aCentDedRessya.EkiIndexOfEkiOrder(iShuchakuEkiOrder);
						int iOuterIndex = -1;
						for (int idxo = 0; idxo < strOuterEkimei[iShuchakuEkiIndex].size(); idxo++)
						{
							if (strOuterEkimei[iShuchakuEkiIndex][idxo] == strEkimei)
							{
								iOuterIndex = idxo;
								break;
							}
						}
						if (iOuterIndex == -1)
						{
							iOuterIndex = strOuterEkimei[iShuchakuEkiIndex].size();
							CentDedEki aCentDedEki = pCentDedEkiCont->get(iShuchakuEkiIndex);
							aCentDedEki.addOuterTerminalEkimei(OuterTerminal(strEkimei, strEkimei, strEkimei.substr(0, 1)));
							pCentDedEkiCont->set(aCentDedEki, iShuchakuEkiIndex);

							strOuterEkimei[iShuchakuEkiIndex].push_back(strEkimei);
						}

						CentDedEkiJikoku aCentDedEkiJikoku = aCentDedRessya.getCentDedEkiJikoku(iShuchakuEkiOrder);
						//着時刻がない場合を考慮し、着時刻がNULLの場合は、発時刻を着時刻にコピーする。
						if (aCentDedEkiJikoku.getChakujikoku().isNull())
						{
							aCentDedEkiJikoku.setChakujikoku(aCentDedEkiJikoku.getHatsujikoku());
						}
						CentDedAfterOperation aCentDedAfterOperation(
							CentDedAfterOperation::EAOperation::AOperation_Outer,
							iOuterIndex,
							aCentDedEkiJikoku.getHatsujikoku(true),
							CdDedJikoku(strJikoku),
							tstring());
						aCentDedEkiJikoku.setHatsujikoku(CdDedJikoku());
						aCentDedEkiJikoku.getCentDedAfterOperationCont()->insert(aCentDedAfterOperation, 0);
						aCentDedRessya.setCentDedEkiJikoku(iShuchakuEkiOrder, aCentDedEkiJikoku);
					}
				}
			}

			aCentDedRessyaCont1Nobori.insert(aCentDedRessya);



			//一つ前の駅の駅時刻形式を着ありに変更させる
			for (int idxe = 0; idxe < iEkiIndexAddChakuNobori.size(); idxe++)
			{
				if (iEkiIndexAddChakuNobori[idxe])
				{
					CentDedEki aCentDedEki = pCentDedEkiCont->get(idxe);

					if (aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsu)
					{
						aCentDedEki.setEkijikokukeisiki(CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku);
					}
					else if (aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku)
					{
						aCentDedEki.setEkijikokukeisiki(CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku);
					}
					else if (aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku)
					{
						aCentDedEki.setEkijikokukeisiki(CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku);
					}

					pCentDedEkiCont->set(aCentDedEki, idxe);
				}
			}
		}



		*aCentDedDia1.getCentDedRessyaCont(ERessyahoukou::Ressyahoukou_Kudari) = aCentDedRessyaCont1Kudari;
		*aCentDedDia1.getCentDedRessyaCont(ERessyahoukou::Ressyahoukou_Nobori) = aCentDedRessyaCont1Nobori;

		aCentDedDiaCont.insert(aCentDedDia1);


		if (!aString3.empty() || !aString4.empty())
		{
			CentDedDia aCentDedDia2;
			//二つのダイヤは同名に出来ないので、ダイヤ1の逆にする。
			if (!aString3.empty())
			{
				aCentDedDia2.setName(strDate[2]);
			}
			else
			{
				aCentDedDia2.setName(strDate[3]);
			}

			CentDedRessyaCont	aCentDedRessyaCont2Kudari(
				aCentDedDia2.getCentDedRessyaCont(ERessyahoukou::Ressyahoukou_Kudari)->createEmptyCont());
			CentDedRessyaCont	aCentDedRessyaCont2Nobori(
				aCentDedDia2.getCentDedRessyaCont(ERessyahoukou::Ressyahoukou_Nobori)->createEmptyCont());

			vector<bool> iEkiIndexAddChakuKudari;
			iEkiIndexAddChakuKudari.assign(pCentDedEkiCont->size(), false);

			for (int idxk = 0; idxk < contRessya3.size(); idxk++)
			{
				CentDedRessya	aCentDedRessya(pCentDedEkiCont->size(), ERessyahoukou::Ressyahoukou_Kudari);
				bool bIsSyubetsuChange = false;
				for (int idx = 0; idx < contDigitalContent1.size(); idx++)
				{
					if (contDigitalContent1[idx].eTrType == ETrType::TrType_RessyaBangou)
					{
						aCentDedRessya.setRessyabangou(contRessya3[idxk][idx]);
					}
					else if (contDigitalContent1[idx].eTrType == ETrType::TrType_Ressyasyubetsu)
					{
						tstring strRessyasyubetsu = contRessya3[idxk][idx];
						const CentDedRessyasyubetsuCont* pCentDedRessyasyubetsuCont = pCentDedRosen->getCentDedRessyasyubetsuCont();
						int iRessyasyubetsuIndex = 0;
						for (int idxs = 0; idxs < pCentDedRessyasyubetsuCont->size(); idxs++)
						{
							if (pCentDedRessyasyubetsuCont->get(idxs).getSyubetsumei() == strRessyasyubetsu)
							{
								iRessyasyubetsuIndex = idxs;
								break;
							}
						}
						aCentDedRessya.setRessyasyubetsuIndex(iRessyasyubetsuIndex);
					}
					else if (contDigitalContent1[idx].eTrType == ETrType::TrType_RessyaMei)
					{
						//JR北海道暫定処置、列車種別は、列車名から取る。
						tstring strRessyasyubetsu = contRessya3[idxk][idx];
						const CentDedRessyasyubetsuCont* pCentDedRessyasyubetsuCont = pCentDedRosen->getCentDedRessyasyubetsuCont();
						int iRessyasyubetsuIndex = 0;
						for (int idxs = 0; idxs < pCentDedRessyasyubetsuCont->size(); idxs++)
						{
							if (pCentDedRessyasyubetsuCont->get(idxs).getSyubetsumei() == strRessyasyubetsu)
							{
								iRessyasyubetsuIndex = idxs;
								break;
							}
						}
						aCentDedRessya.setRessyasyubetsuIndex(iRessyasyubetsuIndex);
						aCentDedRessya.setRessyamei(contRessya3[idxk][idx]);
					}
					else if (contDigitalContent1[idx].eTrType == ETrType::TrType_GouSuu)
					{
						//JR北海道暫定処置：号数が空の場合は、列車名を空にする。そのため、号数のない特急等は、列車名が空となる。
						if (contRessya3[idxk][idx].empty())
						{
							aCentDedRessya.setRessyamei(_T(""));
						}
						aCentDedRessya.setGousuu(contRessya3[idxk][idx]);
					}
					else if (contDigitalContent1[idx].eTrType == ETrType::TrType_UntenBi)
					{
						aCentDedRessya.setBikou(contRessya3[idxk][idx]);
					}
					else if (contDigitalContent1[idx].eTrType == ETrType::TrType_EkiChaku)
					{
						int iEkiOrder = pCentDedEkiCont->EkiOrderOfEkiIndex(ERessyahoukou::Ressyahoukou_Kudari, contDigitalContent1[idx].iEkiIndex);
						CentDedEkiJikoku	aCentDedEkiJikoku = aCentDedRessya.getCentDedEkiJikoku(iEkiOrder);

						if (contRessya3[idxk][idx] == _T("＝"))//前駅止まり
						{
							//一つ上の前の駅の発時刻を着時刻にコピーする
							CentDedEkiJikoku	aCentDedEkiJikokuBefore = aCentDedRessya.getCentDedEkiJikoku(iEkiOrder - 1);
							aCentDedEkiJikokuBefore.setChakujikoku(aCentDedEkiJikokuBefore.getHatsujikoku());
							aCentDedEkiJikokuBefore.setHatsujikoku(CdDedJikoku());
							aCentDedRessya.setCentDedEkiJikoku(iEkiOrder - 1, aCentDedEkiJikokuBefore);

							//一つ前の駅の駅時刻形式を着ありに変更させる
							iEkiIndexAddChakuKudari[contDigitalContent1[idx].iEkiIndex - 1] = true;

							//continue;
						}
						else if (contRessya3[idxk][idx] == _T("||"))//経由なし
						{
							//continue;
						}
						else if (contRessya3[idxk][idx] == _T("・"))//路線外発着
						{
							//continue;
						}
						else if (contRessya3[idxk][idx] == _T("┐"))//種別変更、分割
						{
							bIsSyubetsuChange = true;
						}
						else if (contRessya3[idxk][idx] == _T("┘"))//併合
						{
							//continue;
						}
						else if (contRessya3[idxk][idx] == _T("レ"))//通過
						{
							aCentDedEkiJikoku.setEkiatsukai(CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka);
							//通過の場合、番線表示がないので、主本線を設定しておく。
							aCentDedEkiJikoku.setRessyaTrackIndex(MainTrackKudari[contDigitalContent1[idx].iEkiIndex]);
						}
						else if (contRessya3[idxk][idx].empty())
						{
							//continue;
						}
						else
						{
							aCentDedEkiJikoku.setEkiatsukai(CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya);
							aCentDedEkiJikoku.setChakujikoku(CdDedJikoku(contRessya3[idxk][idx]));
							//停車の場合、番線表示がある可能を考慮し、番線が0未満(未設定)なら主本線を設定しておく。
							if (aCentDedEkiJikoku.getRessyaTrackIndex() < 0)
							{
								aCentDedEkiJikoku.setRessyaTrackIndex(MainTrackKudari[contDigitalContent1[idx].iEkiIndex]);
							}
						}
						aCentDedRessya.setCentDedEkiJikoku(iEkiOrder, aCentDedEkiJikoku);
					}
					else if (contDigitalContent1[idx].eTrType == ETrType::TrType_EkiBansen)
					{
						int iEkiOrder = pCentDedEkiCont->EkiOrderOfEkiIndex(ERessyahoukou::Ressyahoukou_Kudari, contDigitalContent1[idx].iEkiIndex);
						//contRessya3[idxk][idx]の中身が、(番線)だった場合は、番線Indexに置き換え済みなので、数字に変換して番線Indexとして指定する。
						if (!contRessya3[idxk][idx].empty() && _istdigit(contRessya3[idxk][idx][0]) != 0)
						{
							CentDedEkiJikoku	aCentDedEkiJikoku = aCentDedRessya.getCentDedEkiJikoku(iEkiOrder);
							aCentDedEkiJikoku.setRessyaTrackIndex(_ttoi(contRessya3[idxk][idx].c_str()));
							aCentDedRessya.setCentDedEkiJikoku(iEkiOrder, aCentDedEkiJikoku);
						}
						else if (contRessya3[idxk][idx] == _T("＝"))//前駅止まり
						{
							//一つ上の前の駅の発時刻を着時刻にコピーする
							CentDedEkiJikoku	aCentDedEkiJikokuBefore = aCentDedRessya.getCentDedEkiJikoku(iEkiOrder - 1);
							aCentDedEkiJikokuBefore.setChakujikoku(aCentDedEkiJikokuBefore.getHatsujikoku());
							aCentDedEkiJikokuBefore.setHatsujikoku(CdDedJikoku());
							aCentDedRessya.setCentDedEkiJikoku(iEkiOrder - 1, aCentDedEkiJikokuBefore);

							//一つ前の駅の駅時刻形式を着ありに変更させる
							iEkiIndexAddChakuKudari[contDigitalContent1[idx].iEkiIndex - 1] = true;

							//continue;
						}
					}
					else if (contDigitalContent1[idx].eTrType == ETrType::TrType_EkiHatsu)
					{
						int iEkiOrder = pCentDedEkiCont->EkiOrderOfEkiIndex(ERessyahoukou::Ressyahoukou_Kudari, contDigitalContent1[idx].iEkiIndex);
						CentDedEkiJikoku	aCentDedEkiJikoku = aCentDedRessya.getCentDedEkiJikoku(iEkiOrder);
						if (contRessya3[idxk][idx] == _T("＝"))//前駅止まり
						{
							//おでかけネットの場合、着発時刻がある駅止まりでも、発時刻欄に＝を表示するので、一つ上の項目が同じ駅(の着時刻)がどうかを調べる
							if (contDigitalContent1[idx].iEkiIndex != contDigitalContent1[idx - 1].iEkiIndex)
							{
								//一つ上の前の駅の発時刻を着時刻にコピーする
								CentDedEkiJikoku	aCentDedEkiJikokuBefore = aCentDedRessya.getCentDedEkiJikoku(iEkiOrder - 1);
								aCentDedEkiJikokuBefore.setChakujikoku(aCentDedEkiJikokuBefore.getHatsujikoku());
								aCentDedEkiJikokuBefore.setHatsujikoku(CdDedJikoku());
								aCentDedRessya.setCentDedEkiJikoku(iEkiOrder - 1, aCentDedEkiJikokuBefore);

								//一つ前の駅の駅時刻形式を着ありに変更させる
								iEkiIndexAddChakuKudari[contDigitalContent1[idx].iEkiIndex - 1] = true;
							}

							//continue;
						}
						else if (contRessya3[idxk][idx] == _T("||"))//経由なし
						{
							//continue;
						}
						else if (contRessya3[idxk][idx] == _T("・"))//路線外発着
						{
							//continue;
						}
						else if (contRessya3[idxk][idx] == _T("┐"))//種別変更、分割
						{
							bIsSyubetsuChange = true;
						}
						else if (contRessya3[idxk][idx] == _T("┘"))//併合
						{
							//continue;
						}
						else if (contRessya3[idxk][idx] == _T("レ"))//通過
						{
							aCentDedEkiJikoku.setEkiatsukai(CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka);
							//通過の場合、番線表示がないので、主本線を設定しておく。
							aCentDedEkiJikoku.setRessyaTrackIndex(MainTrackKudari[contDigitalContent1[idx].iEkiIndex]);
						}
						else if (contRessya3[idxk][idx].empty())
						{
							//continue;
						}
						else
						{
							aCentDedEkiJikoku.setEkiatsukai(CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya);
							aCentDedEkiJikoku.setHatsujikoku(CdDedJikoku(contRessya3[idxk][idx]));
							//通過の場合、番線表示がある可能を考慮し、番線が0未満(未設定)なら主本線を設定しておく。
							if (aCentDedEkiJikoku.getRessyaTrackIndex() < 0)
							{
								aCentDedEkiJikoku.setRessyaTrackIndex(MainTrackKudari[contDigitalContent1[idx].iEkiIndex]);
							}
						}
						aCentDedRessya.setCentDedEkiJikoku(iEkiOrder, aCentDedEkiJikoku);
					}

				}

				if (bIsSyubetsuChange)
				{
					//bIsSyubetsuChangeなら一つ前の列の列車を呼び出し、その列車の終着駅とこの列車の始発駅が同一なら、
					//種別を確認し、種別が同じなら列車情報変更、異なるなら種別変更を前の列車に設定する。
					CentDedRessya* pCentDedRessyaBefore = aCentDedRessyaCont2Kudari.getMuPtr()->get(idxk - 1);
					if (aCentDedRessya.getValidSihatsuEki() == pCentDedRessyaBefore->getValidSyuuchakuEki())
					{
						if (aCentDedRessya.getRessyasyubetsuIndex() == pCentDedRessyaBefore->getRessyasyubetsuIndex())
						{
							CentDedEkiJikoku aCentDedEkiJikoku = pCentDedRessyaBefore->getCentDedEkiJikoku(pCentDedRessyaBefore->getValidSyuuchakuEki());
							CentDedAfterOperation aCentDedAfterOperation(
								CentDedAfterOperation::EAOperation::AOperation_Junction,
								CdDedJikoku(),
								2);
							aCentDedEkiJikoku.getCentDedAfterOperationCont()->insert(aCentDedAfterOperation, 0);
							pCentDedRessyaBefore->setCentDedEkiJikoku(pCentDedRessyaBefore->getValidSyuuchakuEki(), aCentDedEkiJikoku);
						}
						else
						{
							CentDedEkiJikoku aCentDedEkiJikoku = pCentDedRessyaBefore->getCentDedEkiJikoku(pCentDedRessyaBefore->getValidSyuuchakuEki());
							CentDedAfterOperation aCentDedAfterOperation(
								CentDedAfterOperation::EAOperation::AOperation_Junction,
								CdDedJikoku(),
								1);
							aCentDedEkiJikoku.getCentDedAfterOperationCont()->insert(aCentDedAfterOperation, 0);
							pCentDedRessyaBefore->setCentDedEkiJikoku(pCentDedRessyaBefore->getValidSyuuchakuEki(), aCentDedEkiJikoku);
						}
					}
				}

				if (iKudariOuterShihatsuRow >= 0 && !contRessya3[idxk][iKudariOuterShihatsuRow].empty())
				{
					tstring strEkimei = contRessya3[idxk][iKudariOuterShihatsuRow];
					tstring strJikoku;
					if (_istdigit(strEkimei[strEkimei.size() - 4]) != 0)
					{
						strJikoku = strEkimei.substr(strEkimei.size() - 4, 4);
						strEkimei = strEkimei.substr(0, strEkimei.size() - 4);
					}
					else
					{
						strJikoku = strEkimei.substr(strEkimei.size() - 3, 3);
						strEkimei = strEkimei.substr(0, strEkimei.size() - 3);
					}

					bool bFound = false;
					for (int idxe = 0; idxe < pCentDedEkiCont->size(); idxe++)
					{
						const CentDedEki* pCentDedEki = pCentDedEkiCont->getMuPtr()->get(idxe);
						if (strEkimei == pCentDedEki->getEkimei())
						{
							bFound = true;
							break;
						}
					}

					if (!bFound)
					{
						int iShihatsuEkiOrder = aCentDedRessya.getSihatsuEki();
						if (iShihatsuEkiOrder >= 0)
						{
							int iShihatsuEkiIndex = aCentDedRessya.EkiIndexOfEkiOrder(iShihatsuEkiOrder);
							int iOuterIndex = -1;
							for (int idxo = 0; idxo < strOuterEkimei[iShihatsuEkiIndex].size(); idxo++)
							{
								if (strOuterEkimei[iShihatsuEkiIndex][idxo] == strEkimei)
								{
									iOuterIndex = idxo;
									break;
								}
							}
							if (iOuterIndex == -1)
							{
								iOuterIndex = strOuterEkimei[iShihatsuEkiIndex].size();
								CentDedEki aCentDedEki = pCentDedEkiCont->get(iShihatsuEkiIndex);
								aCentDedEki.addOuterTerminalEkimei(OuterTerminal(strEkimei, strEkimei, strEkimei.substr(0, 1)));
								pCentDedEkiCont->set(aCentDedEki, iShihatsuEkiIndex);

								strOuterEkimei[iShihatsuEkiIndex].push_back(strEkimei);
							}

							CentDedEkiJikoku aCentDedEkiJikoku = aCentDedRessya.getCentDedEkiJikoku(iShihatsuEkiOrder);
							CentDedBeforeOperation aCentDedBeforeOperation(
								CentDedBeforeOperation::EBOperation::BOperation_Outer,
								iOuterIndex,
								CdDedJikoku(strJikoku),
								aCentDedEkiJikoku.getChakujikoku(true),
								vector<tstring>(),
								tstring());
							aCentDedEkiJikoku.setChakujikoku(CdDedJikoku());
							aCentDedEkiJikoku.getCentDedBeforeOperationCont()->insert(aCentDedBeforeOperation, 0);
							aCentDedRessya.setCentDedEkiJikoku(iShihatsuEkiOrder, aCentDedEkiJikoku);
						}

					}
				}

				if (iKudariOuterShuchakuRow >= 0 && !contRessya3[idxk][iKudariOuterShuchakuRow].empty())
				{
					tstring strEkimei = contRessya3[idxk][iKudariOuterShuchakuRow];
					tstring strJikoku;
					if (_istdigit(strEkimei[strEkimei.size() - 4]) != 0)
					{
						strJikoku = strEkimei.substr(strEkimei.size() - 4, 4);
						strEkimei = strEkimei.substr(0, strEkimei.size() - 4);
					}
					else
					{
						strJikoku = strEkimei.substr(strEkimei.size() - 3, 3);
						strEkimei = strEkimei.substr(0, strEkimei.size() - 3);
					}

					bool bFound = false;
					for (int idxe = 0; idxe < pCentDedEkiCont->size(); idxe++)
					{
						const CentDedEki* pCentDedEki = pCentDedEkiCont->getMuPtr()->get(idxe);
						if (strEkimei == pCentDedEki->getEkimei())
						{
							bFound = true;
							break;
						}
					}

					if (!bFound)
					{
						int iShuchakuEkiOrder = aCentDedRessya.getSyuuchakuEki();
						if (iShuchakuEkiOrder >= 0)
						{
							int iShuchakuEkiIndex = aCentDedRessya.EkiIndexOfEkiOrder(iShuchakuEkiOrder);
							int iOuterIndex = -1;
							for (int idxo = 0; idxo < strOuterEkimei[iShuchakuEkiIndex].size(); idxo++)
							{
								if (strOuterEkimei[iShuchakuEkiIndex][idxo] == strEkimei)
								{
									iOuterIndex = idxo;
									break;
								}
							}
							if (iOuterIndex == -1)
							{
								iOuterIndex = strOuterEkimei[iShuchakuEkiIndex].size();
								CentDedEki aCentDedEki = pCentDedEkiCont->get(iShuchakuEkiIndex);
								aCentDedEki.addOuterTerminalEkimei(OuterTerminal(strEkimei, strEkimei, strEkimei.substr(0, 1)));
								pCentDedEkiCont->set(aCentDedEki, iShuchakuEkiIndex);

								strOuterEkimei[iShuchakuEkiIndex].push_back(strEkimei);
							}

							CentDedEkiJikoku aCentDedEkiJikoku = aCentDedRessya.getCentDedEkiJikoku(iShuchakuEkiOrder);
							//着時刻がない場合を考慮し、着時刻がNULLの場合は、発時刻を着時刻にコピーする。
							if (aCentDedEkiJikoku.getChakujikoku().isNull())
							{
								aCentDedEkiJikoku.setChakujikoku(aCentDedEkiJikoku.getHatsujikoku());
							}
							CentDedAfterOperation aCentDedAfterOperation(
								CentDedAfterOperation::EAOperation::AOperation_Outer,
								iOuterIndex,
								aCentDedEkiJikoku.getHatsujikoku(true),
								CdDedJikoku(strJikoku),
								tstring());
							aCentDedEkiJikoku.setHatsujikoku(CdDedJikoku());
							aCentDedEkiJikoku.getCentDedAfterOperationCont()->insert(aCentDedAfterOperation, 0);
							aCentDedRessya.setCentDedEkiJikoku(iShuchakuEkiOrder, aCentDedEkiJikoku);
						}
					}
				}

				aCentDedRessyaCont2Kudari.insert(aCentDedRessya);



				//一つ前の駅の駅時刻形式を着ありに変更させる
				for (int idxe = 0; idxe < iEkiIndexAddChakuKudari.size(); idxe++)
				{
					if (iEkiIndexAddChakuKudari[idxe])
					{
						CentDedEki aCentDedEki = pCentDedEkiCont->get(idxe);

						if (aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsu)
						{
							aCentDedEki.setEkijikokukeisiki(CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku);
						}
						else if (aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
						{
							aCentDedEki.setEkijikokukeisiki(CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku);
						}
						else if (aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku)
						{
							aCentDedEki.setEkijikokukeisiki(CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku);
						}

						pCentDedEkiCont->set(aCentDedEki, idxe);
					}
				}
			}


			//ここから上りダイヤ2
			vector<bool> iEkiIndexAddChakuNobori;
			iEkiIndexAddChakuNobori.assign(pCentDedEkiCont->size(), false);

			for (int idxn = 0; idxn < contRessya4.size(); idxn++)
			{
				//CentDedRessya	aCentDedRessya(aCentDedRessyaCont1Kudari.createNullRessya());
				CentDedRessya	aCentDedRessya(pCentDedEkiCont->size(), ERessyahoukou::Ressyahoukou_Nobori);
				bool bIsSyubetsuChange = false;

				for (int idx = 0; idx < contDigitalContent2.size(); idx++)
				{
					if (contDigitalContent2[idx].eTrType == ETrType::TrType_RessyaBangou)
					{
						aCentDedRessya.setRessyabangou(contRessya4[idxn][idx]);
					}
					else if (contDigitalContent2[idx].eTrType == ETrType::TrType_Ressyasyubetsu)
					{
						tstring strRessyasyubetsu = contRessya4[idxn][idx];
						const CentDedRessyasyubetsuCont* pCentDedRessyasyubetsuCont = pCentDedRosen->getCentDedRessyasyubetsuCont();
						int iRessyasyubetsuIndex = 0;
						for (int idxs = 0; idxs < pCentDedRessyasyubetsuCont->size(); idxs++)
						{
							if (pCentDedRessyasyubetsuCont->get(idxs).getSyubetsumei() == strRessyasyubetsu)
							{
								iRessyasyubetsuIndex = idxs;
								break;
							}
						}
						aCentDedRessya.setRessyasyubetsuIndex(iRessyasyubetsuIndex);
					}
					else if (contDigitalContent2[idx].eTrType == ETrType::TrType_RessyaMei)
					{
						//JR北海道暫定処置、列車種別は、列車名から取る。
						tstring strRessyasyubetsu = contRessya4[idxn][idx];
						const CentDedRessyasyubetsuCont* pCentDedRessyasyubetsuCont = pCentDedRosen->getCentDedRessyasyubetsuCont();
						int iRessyasyubetsuIndex = 0;
						for (int idxs = 0; idxs < pCentDedRessyasyubetsuCont->size(); idxs++)
						{
							if (pCentDedRessyasyubetsuCont->get(idxs).getSyubetsumei() == strRessyasyubetsu)
							{
								iRessyasyubetsuIndex = idxs;
								break;
							}
						}
						aCentDedRessya.setRessyasyubetsuIndex(iRessyasyubetsuIndex);
						aCentDedRessya.setRessyamei(contRessya4[idxn][idx]);
					}
					else if (contDigitalContent2[idx].eTrType == ETrType::TrType_GouSuu)
					{
						//JR北海道暫定処置：号数が空の場合は、列車名を空にする。そのため、号数のない特急等は、列車名が空となる。
						if (contRessya4[idxn][idx].empty())
						{
							aCentDedRessya.setRessyamei(_T(""));
						}
						aCentDedRessya.setGousuu(contRessya4[idxn][idx]);
					}
					else if (contDigitalContent2[idx].eTrType == ETrType::TrType_UntenBi)
					{
						aCentDedRessya.setBikou(contRessya4[idxn][idx]);
					}
					else if (contDigitalContent2[idx].eTrType == ETrType::TrType_EkiChaku)
					{
						int iEkiOrder = pCentDedEkiCont->EkiOrderOfEkiIndex(ERessyahoukou::Ressyahoukou_Nobori, contDigitalContent2[idx].iEkiIndex);
						CentDedEkiJikoku	aCentDedEkiJikoku = aCentDedRessya.getCentDedEkiJikoku(iEkiOrder);
						if (contRessya4[idxn][idx] == _T("＝"))//前駅止まり
						{
							//一つ上の前の駅の発時刻を着時刻にコピーする
							CentDedEkiJikoku	aCentDedEkiJikokuBefore = aCentDedRessya.getCentDedEkiJikoku(iEkiOrder - 1);
							aCentDedEkiJikokuBefore.setChakujikoku(aCentDedEkiJikokuBefore.getHatsujikoku());
							aCentDedEkiJikokuBefore.setHatsujikoku(CdDedJikoku());
							aCentDedRessya.setCentDedEkiJikoku(iEkiOrder - 1, aCentDedEkiJikokuBefore);

							//一つ前(上りなのでIndexは+1)の駅の駅時刻形式を着ありに変更させる
							iEkiIndexAddChakuNobori[contDigitalContent2[idx].iEkiIndex + 1] = true;

							//continue;
						}
						else if (contRessya4[idxn][idx] == _T("||"))//経由なし
						{
							//continue;
						}
						else if (contRessya4[idxn][idx] == _T("・"))//路線外発着
						{
							//continue;
						}
						else if (contRessya4[idxn][idx] == _T("┐"))//種別変更、分割
						{
							bIsSyubetsuChange = true;
						}
						else if (contRessya4[idxn][idx] == _T("┘"))//併合
						{
							//continue;
						}
						else if (contRessya4[idxn][idx] == _T("レ"))//通過
						{
							aCentDedEkiJikoku.setEkiatsukai(CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka);
							//通過の場合、番線表示がないので、主本線を設定しておく。
							aCentDedEkiJikoku.setRessyaTrackIndex(MainTrackNobori[contDigitalContent2[idx].iEkiIndex]);
						}
						else if (contRessya4[idxn][idx].empty())
						{
							//continue;
						}
						else
						{
							aCentDedEkiJikoku.setEkiatsukai(CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya);
							aCentDedEkiJikoku.setChakujikoku(CdDedJikoku(contRessya4[idxn][idx]));
							//停車の場合、番線表示がある可能を考慮し、番線が0未満(未設定)なら主本線を設定しておく。
							if (aCentDedEkiJikoku.getRessyaTrackIndex() < 0)
							{
								aCentDedEkiJikoku.setRessyaTrackIndex(MainTrackNobori[contDigitalContent2[idx].iEkiIndex]);
							}
						}
						aCentDedRessya.setCentDedEkiJikoku(iEkiOrder, aCentDedEkiJikoku);
					}
					else if (contDigitalContent2[idx].eTrType == ETrType::TrType_EkiBansen)
					{
						int iEkiOrder = pCentDedEkiCont->EkiOrderOfEkiIndex(ERessyahoukou::Ressyahoukou_Nobori, contDigitalContent2[idx].iEkiIndex);
						//contRessya4[idxk][idx]の中身が、(番線)だった場合は、番線Indexに置き換え済みなので、数字に変換して番線Indexとして指定する。
						if (!contRessya4[idxn][idx].empty() && _istdigit(contRessya4[idxn][idx][0]) != 0)
						{
							CentDedEkiJikoku	aCentDedEkiJikoku = aCentDedRessya.getCentDedEkiJikoku(iEkiOrder);
							if (aCentDedRessya.getCentDedEkiJikokuCount() == iEkiOrder + 1)
							{
								aCentDedEkiJikoku = aCentDedRessya.getCentDedEkiJikoku(iEkiOrder);
							}
							aCentDedEkiJikoku.setRessyaTrackIndex(_ttoi(contRessya4[idxn][idx].c_str()));

							aCentDedRessya.setCentDedEkiJikoku(iEkiOrder, aCentDedEkiJikoku);
						}
						else if (contRessya4[idxn][idx] == _T("＝"))//前駅止まり
						{
							//一つ上の前の駅の発時刻を着時刻にコピーする
							CentDedEkiJikoku	aCentDedEkiJikokuBefore = aCentDedRessya.getCentDedEkiJikoku(iEkiOrder - 1);
							aCentDedEkiJikokuBefore.setChakujikoku(aCentDedEkiJikokuBefore.getHatsujikoku());
							aCentDedEkiJikokuBefore.setHatsujikoku(CdDedJikoku());
							aCentDedRessya.setCentDedEkiJikoku(iEkiOrder - 1, aCentDedEkiJikokuBefore);

							//一つ前(上りなのでIndexは+1)の駅の駅時刻形式を着ありに変更させる
							iEkiIndexAddChakuNobori[contDigitalContent2[idx].iEkiIndex + 1] = true;

							//continue;
						}
					}
					else if (contDigitalContent2[idx].eTrType == ETrType::TrType_EkiHatsu)
					{
						int iEkiOrder = pCentDedEkiCont->EkiOrderOfEkiIndex(ERessyahoukou::Ressyahoukou_Nobori, contDigitalContent2[idx].iEkiIndex);
						CentDedEkiJikoku	aCentDedEkiJikoku = aCentDedRessya.getCentDedEkiJikoku(iEkiOrder);
						if (contRessya4[idxn][idx] == _T("＝"))//前駅止まり
						{
							//おでかけネットの場合、着発時刻がある駅止まりでも、発時刻欄に＝を表示するので、一つ上の項目が同じ駅(の着時刻)がどうかを調べる
							if (contDigitalContent2[idx].iEkiIndex != contDigitalContent2[idx - 1].iEkiIndex)
							{
								//一つ上の前の駅の発時刻を着時刻にコピーする
								CentDedEkiJikoku	aCentDedEkiJikokuBefore = aCentDedRessya.getCentDedEkiJikoku(iEkiOrder - 1);
								aCentDedEkiJikokuBefore.setChakujikoku(aCentDedEkiJikokuBefore.getHatsujikoku());
								aCentDedEkiJikokuBefore.setHatsujikoku(CdDedJikoku());
								aCentDedRessya.setCentDedEkiJikoku(iEkiOrder - 1, aCentDedEkiJikokuBefore);

								//一つ前(上りなのでIndexは+1)の駅の駅時刻形式を着ありに変更させる
								iEkiIndexAddChakuNobori[contDigitalContent2[idx].iEkiIndex + 1] = true;
							}

							//continue;
						}
						else if (contRessya4[idxn][idx] == _T("||"))//経由なし
						{
							//continue;
						}
						else if (contRessya4[idxn][idx] == _T("・"))//路線外発着
						{
							//continue;
						}
						else if (contRessya4[idxn][idx] == _T("┐"))//種別変更、分割
						{
							bIsSyubetsuChange = true;
						}
						else if (contRessya4[idxn][idx] == _T("┘"))//併合
						{
							//continue;
						}
						else if (contRessya4[idxn][idx] == _T("レ"))//通過
						{
							aCentDedEkiJikoku.setEkiatsukai(CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka);
							//通過の場合、番線表示がないので、主本線を設定しておく。
							aCentDedEkiJikoku.setRessyaTrackIndex(MainTrackNobori[contDigitalContent2[idx].iEkiIndex]);
						}
						else if (contRessya4[idxn][idx].empty())
						{
							//continue;
						}
						else
						{
							aCentDedEkiJikoku.setEkiatsukai(CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya);
							aCentDedEkiJikoku.setHatsujikoku(CdDedJikoku(contRessya4[idxn][idx]));
							//番線表示がある可能を考慮し、番線が0未満(未設定)なら主本線を設定しておく。
							if (aCentDedEkiJikoku.getRessyaTrackIndex() < 0)
							{
								aCentDedEkiJikoku.setRessyaTrackIndex(MainTrackNobori[contDigitalContent2[idx].iEkiIndex]);
							}
						}
						aCentDedRessya.setCentDedEkiJikoku(iEkiOrder, aCentDedEkiJikoku);
					}

				}

				if (bIsSyubetsuChange)
				{
					//bIsSyubetsuChangeなら一つ前の列の列車を呼び出し、その列車の終着駅とこの列車の始発駅が同一なら、
					//種別を確認し、種別が同じなら列車情報変更、異なるなら種別変更を前の列車に設定する。
					CentDedRessya* pCentDedRessyaBefore = aCentDedRessyaCont2Nobori.getMuPtr()->get(idxn - 1);
					if (aCentDedRessya.getValidSihatsuEki() == pCentDedRessyaBefore->getValidSyuuchakuEki())
					{
						if (aCentDedRessya.getRessyasyubetsuIndex() == pCentDedRessyaBefore->getRessyasyubetsuIndex())
						{
							CentDedEkiJikoku aCentDedEkiJikoku = pCentDedRessyaBefore->getCentDedEkiJikoku(pCentDedRessyaBefore->getValidSyuuchakuEki());
							CentDedAfterOperation aCentDedAfterOperation(
								CentDedAfterOperation::EAOperation::AOperation_Junction,
								CdDedJikoku(),
								2);
							aCentDedEkiJikoku.getCentDedAfterOperationCont()->insert(aCentDedAfterOperation, 0);
							pCentDedRessyaBefore->setCentDedEkiJikoku(pCentDedRessyaBefore->getValidSyuuchakuEki(), aCentDedEkiJikoku);
						}
						else
						{
							CentDedEkiJikoku aCentDedEkiJikoku = pCentDedRessyaBefore->getCentDedEkiJikoku(pCentDedRessyaBefore->getValidSyuuchakuEki());
							CentDedAfterOperation aCentDedAfterOperation(
								CentDedAfterOperation::EAOperation::AOperation_Junction,
								CdDedJikoku(),
								1);
							aCentDedEkiJikoku.getCentDedAfterOperationCont()->insert(aCentDedAfterOperation, 0);
							pCentDedRessyaBefore->setCentDedEkiJikoku(pCentDedRessyaBefore->getValidSyuuchakuEki(), aCentDedEkiJikoku);
						}
					}
				}

				if (iNoboriOuterShihatsuRow >= 0 && !contRessya4[idxn][iNoboriOuterShihatsuRow].empty())
				{
					tstring strEkimei = contRessya4[idxn][iNoboriOuterShihatsuRow];
					tstring strJikoku;
					if (_istdigit(strEkimei[strEkimei.size() - 4]) != 0)
					{
						strJikoku = strEkimei.substr(strEkimei.size() - 4, 4);
						strEkimei = strEkimei.substr(0, strEkimei.size() - 4);
					}
					else
					{
						strJikoku = strEkimei.substr(strEkimei.size() - 3, 3);
						strEkimei = strEkimei.substr(0, strEkimei.size() - 3);
					}

					bool bFound = false;
					for (int idxe = 0; idxe < pCentDedEkiCont->size(); idxe++)
					{
						const CentDedEki* pCentDedEki = pCentDedEkiCont->getMuPtr()->get(idxe);
						if (strEkimei == pCentDedEki->getEkimei())
						{
							bFound = true;
							break;
						}
					}

					if (!bFound)
					{
						int iShihatsuEkiOrder = aCentDedRessya.getSihatsuEki();
						if (iShihatsuEkiOrder >= 0)
						{
							int iShihatsuEkiIndex = aCentDedRessya.EkiIndexOfEkiOrder(iShihatsuEkiOrder);
							int iOuterIndex = -1;
							for (int idxo = 0; idxo < strOuterEkimei[iShihatsuEkiIndex].size(); idxo++)
							{
								if (strOuterEkimei[iShihatsuEkiIndex][idxo] == strEkimei)
								{
									iOuterIndex = idxo;
									break;
								}
							}
							if (iOuterIndex == -1)
							{
								iOuterIndex = strOuterEkimei[iShihatsuEkiIndex].size();
								CentDedEki aCentDedEki = pCentDedEkiCont->get(iShihatsuEkiIndex);
								aCentDedEki.addOuterTerminalEkimei(OuterTerminal(strEkimei, strEkimei, strEkimei.substr(0, 1)));
								pCentDedEkiCont->set(aCentDedEki, iShihatsuEkiIndex);

								strOuterEkimei[iShihatsuEkiIndex].push_back(strEkimei);
							}

							CentDedEkiJikoku aCentDedEkiJikoku = aCentDedRessya.getCentDedEkiJikoku(iShihatsuEkiOrder);
							CentDedBeforeOperation aCentDedBeforeOperation(
								CentDedBeforeOperation::EBOperation::BOperation_Outer,
								iOuterIndex,
								CdDedJikoku(strJikoku),
								aCentDedEkiJikoku.getChakujikoku(true),
								vector<tstring>(),
								tstring());
							aCentDedEkiJikoku.setChakujikoku(CdDedJikoku());
							aCentDedEkiJikoku.getCentDedBeforeOperationCont()->insert(aCentDedBeforeOperation, 0);
							aCentDedRessya.setCentDedEkiJikoku(iShihatsuEkiOrder, aCentDedEkiJikoku);
						}
					}
				}

				if (iNoboriOuterShuchakuRow >= 0 && !contRessya4[idxn][iNoboriOuterShuchakuRow].empty())
				{
					tstring strEkimei = contRessya4[idxn][iNoboriOuterShuchakuRow];
					tstring strJikoku;
					if (_istdigit(strEkimei[strEkimei.size() - 4]) != 0)
					{
						strJikoku = strEkimei.substr(strEkimei.size() - 4, 4);
						strEkimei = strEkimei.substr(0, strEkimei.size() - 4);
					}
					else
					{
						strJikoku = strEkimei.substr(strEkimei.size() - 3, 3);
						strEkimei = strEkimei.substr(0, strEkimei.size() - 3);
					}

					bool bFound = false;
					for (int idxe = 0; idxe < pCentDedEkiCont->size(); idxe++)
					{
						const CentDedEki* pCentDedEki = pCentDedEkiCont->getMuPtr()->get(idxe);
						if (strEkimei == pCentDedEki->getEkimei())
						{
							bFound = true;
							break;
						}
					}

					if (!bFound)
					{
						int iShuchakuEkiOrder = aCentDedRessya.getSyuuchakuEki();
						if (iShuchakuEkiOrder >= 0)
						{
							int iShuchakuEkiIndex = aCentDedRessya.EkiIndexOfEkiOrder(iShuchakuEkiOrder);
							int iOuterIndex = -1;
							for (int idxo = 0; idxo < strOuterEkimei[iShuchakuEkiIndex].size(); idxo++)
							{
								if (strOuterEkimei[iShuchakuEkiIndex][idxo] == strEkimei)
								{
									iOuterIndex = idxo;
									break;
								}
							}
							if (iOuterIndex == -1)
							{
								iOuterIndex = strOuterEkimei[iShuchakuEkiIndex].size();
								CentDedEki aCentDedEki = pCentDedEkiCont->get(iShuchakuEkiIndex);
								aCentDedEki.addOuterTerminalEkimei(OuterTerminal(strEkimei, strEkimei, strEkimei.substr(0, 1)));
								pCentDedEkiCont->set(aCentDedEki, iShuchakuEkiIndex);

								strOuterEkimei[iShuchakuEkiIndex].push_back(strEkimei);
							}

							CentDedEkiJikoku aCentDedEkiJikoku = aCentDedRessya.getCentDedEkiJikoku(iShuchakuEkiOrder);
							//着時刻がない場合を考慮し、着時刻がNULLの場合は、発時刻を着時刻にコピーする。
							if (aCentDedEkiJikoku.getChakujikoku().isNull())
							{
								aCentDedEkiJikoku.setChakujikoku(aCentDedEkiJikoku.getHatsujikoku());
							}
							CentDedAfterOperation aCentDedAfterOperation(
								CentDedAfterOperation::EAOperation::AOperation_Outer,
								iOuterIndex,
								aCentDedEkiJikoku.getHatsujikoku(true),
								CdDedJikoku(strJikoku),
								tstring());
							aCentDedEkiJikoku.setHatsujikoku(CdDedJikoku());
							aCentDedEkiJikoku.getCentDedAfterOperationCont()->insert(aCentDedAfterOperation, 0);
							aCentDedRessya.setCentDedEkiJikoku(iShuchakuEkiOrder, aCentDedEkiJikoku);
						}
					}
				}

				aCentDedRessyaCont2Nobori.insert(aCentDedRessya);



				//一つ前の駅の駅時刻形式を着ありに変更させる
				for (int idxe = 0; idxe < iEkiIndexAddChakuNobori.size(); idxe++)
				{
					if (iEkiIndexAddChakuNobori[idxe])
					{
						CentDedEki aCentDedEki = pCentDedEkiCont->get(idxe);

						if (aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsu)
						{
							aCentDedEki.setEkijikokukeisiki(CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku);
						}
						else if (aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku)
						{
							aCentDedEki.setEkijikokukeisiki(CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku);
						}
						else if (aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku)
						{
							aCentDedEki.setEkijikokukeisiki(CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku);
						}

						pCentDedEkiCont->set(aCentDedEki, idxe);
					}
				}
			}

			*aCentDedDia2.getCentDedRessyaCont(ERessyahoukou::Ressyahoukou_Kudari) = aCentDedRessyaCont2Kudari;
			*aCentDedDia2.getCentDedRessyaCont(ERessyahoukou::Ressyahoukou_Nobori) = aCentDedRessyaCont2Nobori;

			aCentDedDiaCont.insert(aCentDedDia2);

		}

		CaMui<CentDedDia>	aCaCont(pCentDedRosen->getCentDedDiaCont());
		aCaCont.insert(&aCentDedDiaCont);

	}
	return ( iRv ) ;
}


void DedRosenFileData::CconvCDedRosenFileDataDigital3::ReadDigital(
	const tstring& aString,
	vector<vector<tstring>>& contRessya,
	vector<DigitalContent>& contDigitalContent,
	const int iIndividualHandling )
{
	tstring aStringTemp = aString;

	int iShihatsuRow = -1;
	int iShuchakuRow = -1;
	int iUntenBiRow = -1;

	int iTrIndexL = 0;
	int iTrIndexR = 0;

	tstring::size_type posTb = aStringTemp.find(_T("<table>"));
	tstring::size_type posTbEnd = aStringTemp.find(_T("</table>"), posTb);

	//一つ目のTableは、項目の上部
	if (posTb != tstring::npos)
	{
		tstring strTb = aStringTemp.substr(posTb, posTbEnd - posTb + 7);
		tstring::size_type posTr = strTb.find(_T("<tr"));
		tstring strBeforeTh1 = _T("");
		while (posTr != tstring::npos)
		{
			tstring::size_type posTrEnd = strTb.find(_T("/tr>"));
			tstring strTr = strTb.substr(posTr, posTrEnd - posTr + 4);
			strTb = strTb.substr(posTrEnd + 4);

			tstring::size_type posTd = strTr.find(_T("<td"));
			tstring::size_type posTdEnd = strTr.find(_T("/td>"));
			tstring strTd = strTr.substr(posTd, posTdEnd - posTd + 4);
			strTr = strTr.substr(posTdEnd + 4);
			//一つ目のstrTdは行の項目名「列車番号」など
				//display: noneが含まれるTr行は、前の行が列車名の場合は列車号数、それ以外の場合は着発両方の時刻がある駅の発時刻欄
			if (strBeforeTh1 == _T("列車名") && TrimTag(strTd).empty())
			{
				if (contDigitalContent.size() <= iTrIndexL)
				{
					DigitalContent sDigitalContent;
					strBeforeTh1 = _T("号数");
					sDigitalContent.strTh1 = strBeforeTh1;
					contDigitalContent.push_back(sDigitalContent);
				}
				else
				{
					strBeforeTh1 = _T("号数");
					contDigitalContent[iTrIndexL].strTh1 = strBeforeTh1;
				}
			}
			else if (contDigitalContent.size() <= iTrIndexL)
			{
				DigitalContent sDigitalContent;
				strBeforeTh1 = TrimTag(strTd);
				sDigitalContent.strTh1 = strBeforeTh1;
				contDigitalContent.push_back(sDigitalContent);
			}
			else
			{
				strBeforeTh1 = TrimTag(strTd);
				contDigitalContent[iTrIndexL].strTh1 = strBeforeTh1;
			}

			posTd = strTr.find(_T("<td"));
			posTdEnd = strTr.find(_T("/td>"));
			strTd = strTr.substr(posTd, posTdEnd - posTd + 4);
			strTr = strTr.substr(posTdEnd + 4);
			//二つ目のstrTdは駅時刻の発・着
			if (contDigitalContent.size() <= iTrIndexL)
			{
				DigitalContent sDigitalContent;
				sDigitalContent.strTh2 = TrimTag(strTd);
				contDigitalContent.push_back(sDigitalContent);
			}
			else
			{
				contDigitalContent[iTrIndexL].strTh2 = TrimTag(strTd);
			}

			posTr = strTb.find(_T("<tr")); 
			iTrIndexL++;
		}
	}

	posTb = aStringTemp.find(_T("<table>"), posTbEnd);
	posTbEnd = aStringTemp.find(_T("</table>"), posTb);

	//二つ目のTableは列車の上部
	if (posTb != tstring::npos)
	{
		tstring strTb = aStringTemp.substr(posTb, posTbEnd - posTb + 7);
		tstring::size_type posTr = strTb.find(_T("<tr"));
		//tstring strBeforeTh1 = _T("");
		while (posTr != tstring::npos)
		{
			tstring::size_type posTrEnd = strTb.find(_T("/tr>"));
			tstring strTr = strTb.substr(posTr, posTrEnd - posTr + 4);
			strTb = strTb.substr(posTrEnd + 4);

			tstring::size_type posTd = strTr.find(_T("<td"));
			tstring::size_type posTdEnd = strTr.find(_T("/td>"));

			for (int iTdIndex = 0; posTd != tstring::npos; iTdIndex++)
			{
				tstring strTd = strTr.substr(posTd, posTdEnd - posTd + 4);
				strTr = strTr.substr(posTdEnd + 4);

				posTd = strTr.find(_T("<td"));
				posTdEnd = strTr.find(_T("/td>"));

				if (contRessya.size() <= iTdIndex)
				{
					contRessya.push_back({ TrimTag(strTd) });
				}
				else
				{
					contRessya[iTdIndex].push_back(TrimTag(strTd));
				}
			}
			posTr = strTb.find(_T("<tr"));
			iTrIndexR++;
		}

	}

	posTb = aStringTemp.find(_T("<table>"), posTbEnd);
	posTbEnd = aStringTemp.find(_T("</table>"), posTb);

	//三つ目のTableは、項目の下部
	if (posTb != tstring::npos)
	{
		tstring strTb = aStringTemp.substr(posTb, posTbEnd - posTb + 7);
		tstring::size_type posTr = strTb.find(_T("<tr"));
		tstring strBeforeTh1 = _T("");
		while (posTr != tstring::npos)
		{
			tstring::size_type posTrEnd = strTb.find(_T("/tr>"));
			tstring strTr = strTb.substr(posTr, posTrEnd - posTr + 4);
			strTb = strTb.substr(posTrEnd + 4);

			tstring::size_type posTd = strTr.find(_T("<td"));
			tstring::size_type posTdEnd = strTr.find(_T("/td>"));
			tstring strTd = strTr.substr(posTd, posTdEnd - posTd + 4);
			strTr = strTr.substr(posTdEnd + 4);
			if (contDigitalContent.size() <= iTrIndexL)
			{
				DigitalContent sDigitalContent;
				strBeforeTh1 = TrimTag(strTd);
				sDigitalContent.strTh1 = strBeforeTh1;
				contDigitalContent.push_back(sDigitalContent);
				if (strBeforeTh1 == _T("始発"))
				{
					iShihatsuRow = iTrIndexL;
				}
				else if (strBeforeTh1 == _T("終着"))
				{
					iShuchakuRow = iTrIndexL;
				}
				else if (strBeforeTh1 == _T("運転日"))
				{
					iUntenBiRow = iTrIndexL;
				}
			}
			else
			{
				strBeforeTh1 = TrimTag(strTd);
				contDigitalContent[iTrIndexL].strTh1 = strBeforeTh1;
			}

			posTd = strTr.find(_T("<td"));
			posTdEnd = strTr.find(_T("/td>"));
			strTd = strTr.substr(posTd, posTdEnd - posTd + 4);
			strTr = strTr.substr(posTdEnd + 4);
			//二つ目のstrTdは駅時刻の発・着
			if (contDigitalContent.size() <= iTrIndexL)
			{
				DigitalContent sDigitalContent;
				sDigitalContent.strTh2 = TrimTag(strTd);
				contDigitalContent.push_back(sDigitalContent);
			}
			else
			{
				contDigitalContent[iTrIndexL].strTh2 = TrimTag(strTd);
			}
			posTr = strTb.find(_T("<tr"));
			iTrIndexL++;
		}
	}

	posTb = aStringTemp.find(_T("<table>"), posTbEnd);
	posTbEnd = aStringTemp.find(_T("</table>"), posTb);

	//四つ目のTableは列車の下部
	if (posTb != tstring::npos)
	{
		tstring strTb = aStringTemp.substr(posTb, posTbEnd - posTb + 7);
		tstring::size_type posTr = strTb.find(_T("<tr"));
		//tstring strBeforeTh1 = _T("");
		while (posTr != tstring::npos)
		{
			tstring::size_type posTrEnd = strTb.find(_T("/tr>"));
			tstring strTr = strTb.substr(posTr, posTrEnd - posTr + 4);
			strTb = strTb.substr(posTrEnd + 4);

			tstring::size_type posTd = strTr.find(_T("<td"));
			tstring::size_type posTdEnd = strTr.find(_T("/td>"));

			for (int iTdIndex = 0; posTd != tstring::npos; iTdIndex++)
			{
				tstring strTd = strTr.substr(posTd, posTdEnd - posTd + 4);
				strTr = strTr.substr(posTdEnd + 4);

				posTd = strTr.find(_T("<td"));
				posTdEnd = strTr.find(_T("/td>"));

				//路線外発着、予め路線外発着が表示される行番号を保持しておく。
				if (iTrIndexR == iShihatsuRow ||
					iTrIndexR == iShuchakuRow)
				{
					tstring strTemp=_T("");

					tstring::size_type posDD = strTd.find(_T("displayDialog"));

					if (posDD != tstring::npos)
					{
						//駅名を、ポップアップの内容から取得する

						tstring::size_type posSC = strTd.find(_T(";"), posDD);

						strTemp = strTd.substr(posDD + 30, posSC - posDD - 32);//駅名

						tstring::size_type pos2 = strTd.find(_T("<br"));
						strTemp += TrimTag(strTd.substr(pos2));//時刻
					}
					else
					{
						strTemp = TrimTag(strTd);//駅名

						tstring::size_type pos2 = strTd.find(_T("<br"));
						strTemp += TrimTag(strTd.substr(pos2));//時刻
					}

					if (contRessya.size() <= iTdIndex)
					{
						contRessya.push_back({ strTemp });
					}
					else
					{
						contRessya[iTdIndex].push_back(strTemp);
					}

					continue;
				}

				if (iTrIndexR == iUntenBiRow)
				{
					tstring strTemp = _T("");

					tstring::size_type posDD = strTd.find(_T("displayDialog"));

					if (posDD != tstring::npos)
					{
						//駅名を、ポップアップの内容から取得する

						tstring::size_type posSC = strTd.find(_T(";"), posDD);

						strTemp = strTd.substr(posDD + 32, posSC - posDD - 34);//駅名
					}
					else
					{
						strTemp = TrimTag(strTd);//運転日
					}

					if (contRessya.size() <= iTdIndex)
					{
						contRessya.push_back({ strTemp });
					}
					else
					{
						contRessya[iTdIndex].push_back(strTemp);
					}

					continue;
				}
				if (contRessya.size() <= iTdIndex)
				{
					contRessya.push_back({ TrimTag(strTd) });
				}
				else
				{
					contRessya[iTdIndex].push_back(TrimTag(strTd));
				}
			}
			posTr = strTb.find(_T("<tr"));
			iTrIndexR++;
		}

	}


	//ここから、路線ごとの個別取り扱い
	//if (iIndividualHandling == 1)
	//{
	//}
	//else if (iIndividualHandling == 2)
	//{
	//}
}

tstring CconvCDedRosenFileDataDigital3::TrimTag(const tstring strInput)
{
	tstring strRv = strInput;
	if (strInput.empty())
	{
		return tstring();
	}
	tstring::size_type pos = 0;
	tstring::size_type pos2 = 0;
	pos = strInput.find('<');
	pos2 = strInput.find('>');
	if (pos != tstring::npos && pos2 != tstring::npos && pos < pos2)
	{
		if (pos == 0) 
		{
			return(TrimTag(strInput.substr(pos2 + 1)));
		}
		else
		{
			return(TrimTag(strInput.substr(0 , pos)));
		}
	}

	return strInput;
}

} //namespace DedRosenFileData

