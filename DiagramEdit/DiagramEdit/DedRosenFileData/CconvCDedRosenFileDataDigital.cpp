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
//	CconvCDedRosenFileDataDigital.cpp
// ****************************************************************
*/
/** @file */
#include "stdafx.h"
#include "NsOu¥OuNew.h"
#include "NsOu¥dynamic_castOu.h"
#include "str¥CdConnectedString2.h"
#include "str¥strToInt.h"
#include "str¥CConnectedStringCompress.h"
#include "str¥OuPropertiesText¥CConvNodeContainer.h"
#include "str¥OuPropertiesText¥CDirectory.h"
#include "str¥OuPropertiesText¥ErrorInfo¥COuErrorInfoContainer.h"
#include "logmsg¥LogMsg.h"

#include "CconvCdDedDispProp.h"
#include "CconvCDedRosenFileDataDigital.h"
//#include "../CDiagramEditDoc.h"
#include "../DiagramEdit.h"
#include "../ViewDiagram¥CDedDiagramView.h"
#include "../ViewAllOperationTable¥CAllOperationTableView.h"
#include "../ViewAllOperationTable2¥CDedAllOperationTable2View.h"

#include "NsMu¥CaMui.h"
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


int CconvCDedRosenFileDataDigital::CDedRosenFileData_from_string( 
			CDedRosenFileData* pCDedRosenFileData ,
			const tstring& aString1 ,
			const tstring& aString2,
			const tstring& aString3,
			const tstring& aString4,
			const bool bInvalidateIndividualHandling/*,
			OuPropertiesText::ErrorInfo::COuErrorInfoContainer* pCOuErrorInfoContainer */) 
{

	vector<tstring> contString1 = splitc<vector<tstring>>('¥n', aString1);
	vector<tstring> contString2 = splitc<vector<tstring>>('¥n', aString2);
	vector<tstring> contString3 = splitc<vector<tstring>>('¥n', aString3);
	vector<tstring> contString4 = splitc<vector<tstring>>('¥n', aString4);




	//LogMsg( _T("CDedRosenFileData_from_string()") ) ;

	int iRv = 0 ;

	/**
		入力ファイルの整合性を確かめる
		・String1-4の路線が一致
		・String1・2の平日/土休日が一致、方面が逆
		・String3・4の平日/土休日が一致、方面が逆
		・String1・3の方面が一致
		・String2・4の方面が一致
	*/
	//下りならTrue、上りならFalse
	bool bIsDown[4] = { false };
	//平日ならTrue、休日ならFalse
	bool bIsWeekday[4] = { false };

	tstring strRosenID=_T("");

	if (iRv >= 0)
	{
		bool bFound = false;
		for (int idx = 0; idx < (int)contString1.size(); idx++)
		{
			tstring::size_type pos = contString1[idx].find(_T("announce_INIT"));
			if (pos != tstring::npos)
			{
				vector<tstring> contRosen = splitc<vector<tstring>>('¥'', contString1[idx]);
				if (contRosen.size() >= 8)
				{
					//路線ID
					strRosenID = contRosen[7].substr(0, 3);
					bIsDown[0] = contRosen[7].substr(3, 1) == _T("d");
					bIsWeekday[0] = contRosen[7].substr(4, 1) == _T("1");
					bFound = true;
				}
				break;
			}
		}
		if (!bFound)
		{
			iRv = -21;
		}
	}
	if (iRv >= 0 && !aString2.empty())
	{
		bool bFound = false;
		for (int idx = 0; idx < (int)contString2.size(); idx++)
		{
			tstring::size_type pos = contString2[idx].find(_T("announce_INIT"));
			if (pos != tstring::npos)
			{
				vector<tstring> contRosen = splitc<vector<tstring>>('¥'', contString2[idx]);
				if (contRosen.size() >= 8)
				{
					//路線IDが不一致の場合は、エラーとする。
					if (strRosenID != contRosen[7].substr(0, 3))
					{
						iRv = -32;
					}
					bIsDown[1] = contRosen[7].substr(3, 1) == _T("d");
					bIsWeekday[1] = contRosen[7].substr(4, 1) == _T("1");
					bFound = true;
				}
				break;
			}
		}
		if (!bFound)
		{
			iRv = -22;
		}
	}
	if (iRv >= 0 && !aString3.empty())
	{
		bool bFound = false;
		for (int idx = 0; idx < (int)contString3.size(); idx++)
		{
			tstring::size_type pos = contString3[idx].find(_T("announce_INIT"));
			if (pos != tstring::npos)
			{
				vector<tstring> contRosen = splitc<vector<tstring>>('¥'', contString3[idx]);
				if (contRosen.size() >= 8)
				{
					//路線IDが不一致の場合は、エラーとする。
					if (strRosenID != contRosen[7].substr(0, 3))
					{
						iRv = -33;
					}
					bIsDown[2] = contRosen[7].substr(3, 1) == _T("d");
					bIsWeekday[2] = contRosen[7].substr(4, 1) == _T("1");
					bFound = true;
				}
				break;
			}
		}
		if (!bFound)
		{
			iRv = -23;
		}
	}
	if (iRv >= 0 && !aString4.empty())
	{
		bool bFound = false;
		for (int idx = 0; idx < (int)contString4.size(); idx++)
		{
			tstring::size_type pos = contString4[idx].find(_T("announce_INIT"));
			if (pos != tstring::npos)
			{
				vector<tstring> contRosen = splitc<vector<tstring>>('¥'', contString4[idx]);
				if (contRosen.size() >= 8)
				{
					//路線IDが不一致の場合は、エラーとする。
					if (strRosenID != contRosen[7].substr(0, 3))
					{
						iRv = -34;
					}
					bIsDown[3] = contRosen[7].substr(3, 1) == _T("d");
					bIsWeekday[3] = contRosen[7].substr(4, 1) == _T("1");
					bFound = true;
				}
				break;
			}
		}
		if (!bFound)
		{
			iRv = -24;
		}
	}
	//String1・2の方面が逆、平日/土休日が一致
	if (iRv >= 0)
	{
		if (!aString2.empty())
		{
			if (bIsDown[0] == bIsDown[1])
			{
				iRv = -42;
			}
			else if (bIsWeekday[0] != bIsWeekday[1])
			{
				iRv = -52;
			}
		}
	}
	//String1・3の方面が一致・平日/土休日が逆
	if (iRv >= 0)
	{
		if (!aString3.empty())
		{
			if (bIsDown[0] != bIsDown[2])
			{
				iRv = -43;
			}
			else if (bIsWeekday[0] == bIsWeekday[2])
			{
				iRv = -53;
			}
		}
	}
	//String1・4の方面が逆、平日/土休日が逆
	if (iRv >= 0)
	{
		if (!aString4.empty())
		{
			if (bIsDown[0] == bIsDown[3])
			{
				iRv = -44;
			}
			else if (bIsWeekday[0] == bIsWeekday[3])
			{
				iRv = -54;
			}
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

	int iIndividualHandling1 = 0;
	int iIndividualHandling2 = 0;
	if (!bInvalidateIndividualHandling && strRosenID == _T("003"))
	{
		if (bIsDown[0])
		{
			iIndividualHandling2 = 1;
		}
		else
		{
			iIndividualHandling1 = 1;
		}
	}
	else if (!bInvalidateIndividualHandling && strRosenID == _T("279"))
	{
		iIndividualHandling1 = 2;
		iIndividualHandling2 = 2;
	}
	else if (!bInvalidateIndividualHandling && strRosenID == _T("004"))
	{
		if (bIsDown[0])
		{
			iIndividualHandling2 = 3;
		}
		else
		{
			iIndividualHandling1 = 3;
		}
	}

	if (iRv >= 0)
	{
		if (!aString1.empty())
		{
			ReadDigital(contString1, contRessya1, contDigitalContent1, iIndividualHandling1);
		}
		if (!aString2.empty())
		{
			ReadDigital(contString2, contRessya2, contDigitalContent2, iIndividualHandling2);
		}
		if (!aString3.empty())
		{
			ReadDigital(contString3, contRessya3, contDigitalContent3, iIndividualHandling1);
		}
		if (!aString4.empty())
		{
			ReadDigital(contString4, contRessya4, contDigitalContent4, iIndividualHandling2);
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
			else if (contDigitalContent1[idx].strTh1 == _T("列車名"))
			{
				contDigitalContent1[idx].eTrType = ETrType::TrType_RessyaMei;
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
				tstring strEkimei = contDigitalContent1[idx].strTh1.substr(0, contDigitalContent1[idx].strTh1.length() - 2);
				if (strEkimei == strEkimeiBefore)
				{
					contDigitalContent1[idx].eTrType = ETrType::TrType_EkiBansen;
					contDigitalContent1[idx].iEkiIndex = iEkiIndex;
				}
				else
				{
					iEkiIndex++;
					strEkimeiBefore = strEkimei;
					strContEkimei.push_back(strEkimei);
					contDigitalContent1[idx].eTrType = ETrType::TrType_EkiBansen;
					contDigitalContent1[idx].iEkiIndex = iEkiIndex;
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
				else if (contDigitalContent2[idx].strTh1 == _T("列車名"))
				{
					contDigitalContent2[idx].eTrType = ETrType::TrType_RessyaMei;
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
					tstring strEkimei = contDigitalContent2[idx].strTh1.substr(0, contDigitalContent2[idx].strTh1.length() - 2);

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
							iRv = -73;
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

		int iKudariRessyasyubetsuRow = -1;
		int iNoboriRessyasyubetsuRow = -1;

		for (int idxk = 0; idxk < contDigitalContent1.size(); idxk++)
		{
			if (contDigitalContent1[idxk].eTrType == ETrType::TrType_RessyaMei)
			{
				iKudariRessyasyubetsuRow = idxk;
			}
		}

		for (int idxn = 0; idxn < contDigitalContent2.size(); idxn++)
		{
			if (contDigitalContent2[idxn].eTrType == ETrType::TrType_RessyaMei )
			{
				iNoboriRessyasyubetsuRow = idxn;
			}
		}

		if (iKudariRessyasyubetsuRow >= 0)
		{
			for (int idxk = 0; idxk < contRessya1.size(); idxk++)
			{
				tstring strRessyasyubetsu = contRessya1[idxk][iKudariRessyasyubetsuRow];
				tstring::size_type pos = strRessyasyubetsu.find(' ');
				if (pos != tstring::npos)
				{
					//strRessyasyubetsuに空白が含まれる場合、空白よりも前のみが種別名となる
					//(例)特急 踊り子53号→特急、はやぶさ 95→はやぶさ
					strRessyasyubetsu = strRessyasyubetsu.substr(0, pos);
				}

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
				tstring strRessyasyubetsu = contRessya3[idxk][iKudariRessyasyubetsuRow];
				tstring::size_type pos = strRessyasyubetsu.find(' ');
				if (pos != tstring::npos)
				{
					//strRessyasyubetsuに空白が含まれる場合、空白よりも前のみが種別名となる
					//(例)特急 踊り子53号→特急、はやぶさ 95→はやぶさ
					strRessyasyubetsu = strRessyasyubetsu.substr(0, pos);
				}

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

		if (iNoboriRessyasyubetsuRow >= 0)
		{
			for (int idxn = 0; idxn < contRessya2.size(); idxn++)
			{
				tstring strRessyasyubetsu = contRessya2[idxn][iNoboriRessyasyubetsuRow];
				tstring::size_type pos = strRessyasyubetsu.find(' ');
				if (pos != tstring::npos)
				{
					//strRessyasyubetsuに空白が含まれる場合、空白よりも前のみが種別名となる
					//(例)特急 踊り子53号→特急、はやぶさ 95→はやぶさ
					strRessyasyubetsu = strRessyasyubetsu.substr(0, pos);
				}

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
				tstring strRessyasyubetsu = contRessya4[idxn][iNoboriRessyasyubetsuRow];
				tstring::size_type pos = strRessyasyubetsu.find(' ');
				if (pos != tstring::npos)
				{
					//strRessyasyubetsuに空白が含まれる場合、空白よりも前のみが種別名となる
					//(例)特急 踊り子53号→特急、はやぶさ 95→はやぶさ
					strRessyasyubetsu = strRessyasyubetsu.substr(0, pos);
				}

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
		if (bIsWeekday[0])
		{
			aCentDedDia1.setName(_T("平日ダイヤ"));
		}
		else
		{
			aCentDedDia1.setName(_T("土曜・休日ダイヤ"));
		}

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
				else if (contDigitalContent1[idx].eTrType == ETrType::TrType_RessyaMei)
				{
					tstring strRessyasyubetsu = contRessya1[idxk][idx];
					tstring::size_type pos = strRessyasyubetsu.find(' ');
					if (pos != tstring::npos)
					{
						if (strRessyasyubetsu.find(_T("号")) != tstring::npos)
						{
							//号が含まれる場合は、在来線特急などです、従って、種別→スペースの前、列車名→スペースの後、数字の前まで、号数→最後の数字から号を取り除く、となります
							tstring strRessyaMei = strRessyasyubetsu.substr(pos+1);
							strRessyasyubetsu = strRessyasyubetsu.substr(0, pos);
							tstring strGouSuu;
							for (int idxd = 0; idxd < strRessyaMei.length(); idxd++)
							{
								if (_istdigit(strRessyaMei[idxd]) != 0)
								{
									strGouSuu = strRessyaMei.substr(idxd, strRessyaMei.length() - idxd - 1);
									strRessyaMei = strRessyaMei.substr(0, idxd);
									aCentDedRessya.setRessyamei(strRessyaMei);
									aCentDedRessya.setGousuu(strGouSuu);
									break;
								}
							}


						}
						else
						{
							//号が含まれない場合は、新幹線及び、号数のない在来線列車です。従って、種別→スペースの前、スペースの後が数字なら号数かつ種別→列車名、スペースの後が数字以外なら列車名、となります
							tstring strRessyaMei = strRessyasyubetsu.substr(pos + 1);
							strRessyasyubetsu = strRessyasyubetsu.substr(0, pos);
							if (_istdigit(strRessyaMei[0]) != 0)
							{
								//数字なので新幹線パターン
								aCentDedRessya.setRessyamei(strRessyasyubetsu);
								aCentDedRessya.setGousuu(strRessyaMei);
							}
							else
							{
								//数字ではないので号数無しパターン
								aCentDedRessya.setRessyamei(strRessyaMei);
							}
						}
					}
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
				tstring strJikoku = strEkimei.substr(strEkimei.size() - 4, 4);
				strEkimei= strEkimei.substr(0, strEkimei.size() - 4);

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

			if (iKudariOuterShuchakuRow >= 0 && !contRessya1[idxk][iKudariOuterShuchakuRow].empty())
			{
				tstring strEkimei = contRessya1[idxk][iKudariOuterShuchakuRow];
				tstring strJikoku = strEkimei.substr(strEkimei.size() - 4, 4);
				strEkimei = strEkimei.substr(0, strEkimei.size() - 4);

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
				else if (contDigitalContent2[idx].eTrType == ETrType::TrType_RessyaMei)
				{
					tstring strRessyasyubetsu = contRessya2[idxn][idx];
					tstring::size_type pos = strRessyasyubetsu.find(' ');
					if (pos != tstring::npos)
					{
						if (strRessyasyubetsu.find(_T("号")) != tstring::npos)
						{
							//号が含まれる場合は、在来線特急などです、従って、種別→スペースの前、列車名→スペースの後、数字の前まで、号数→最後の数字から号を取り除く、となります
							tstring strRessyaMei = strRessyasyubetsu.substr(pos + 1);
							strRessyasyubetsu = strRessyasyubetsu.substr(0, pos);
							tstring strGouSuu;
							for (int idxd = 0; idxd < strRessyaMei.length(); idxd++)
							{
								if (_istdigit(strRessyaMei[idxd]) != 0)
								{
									strGouSuu = strRessyaMei.substr(idxd, strRessyaMei.length() - idxd - 1);
									strRessyaMei = strRessyaMei.substr(0, idxd);
									aCentDedRessya.setRessyamei(strRessyaMei);
									aCentDedRessya.setGousuu(strGouSuu);
									break;
								}
							}


						}
						else
						{
							//号が含まれない場合は、新幹線及び、号数のない在来線列車です。従って、種別→スペースの前、スペースの後が数字なら号数かつ種別→列車名、スペースの後が数字以外なら列車名、となります
							tstring strRessyaMei = strRessyasyubetsu.substr(pos + 1);
							strRessyasyubetsu = strRessyasyubetsu.substr(0, pos);
							if (_istdigit(strRessyaMei[0]) != 0)
							{
								//数字なので新幹線パターン
								aCentDedRessya.setRessyamei(strRessyasyubetsu);
								aCentDedRessya.setGousuu(strRessyaMei);
							}
							else
							{
								//数字ではないので号数無しパターン
								aCentDedRessya.setRessyamei(strRessyaMei);
							}
						}
					}
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
				tstring strJikoku = strEkimei.substr(strEkimei.size() - 4, 4);
				strEkimei = strEkimei.substr(0, strEkimei.size() - 4);

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

			if (iNoboriOuterShuchakuRow >= 0 && !contRessya2[idxn][iNoboriOuterShuchakuRow].empty())
			{
				tstring strEkimei = contRessya2[idxn][iNoboriOuterShuchakuRow];
				tstring strJikoku = strEkimei.substr(strEkimei.size() - 4, 4);
				strEkimei = strEkimei.substr(0, strEkimei.size() - 4);

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
			if (bIsWeekday[0])
			{
				aCentDedDia2.setName(_T("土曜・休日ダイヤ"));
			}
			else
			{
				aCentDedDia2.setName(_T("平日ダイヤ"));
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
					else if (contDigitalContent1[idx].eTrType == ETrType::TrType_RessyaMei)
					{
						tstring strRessyasyubetsu = contRessya3[idxk][idx];
						tstring::size_type pos = strRessyasyubetsu.find(' ');
						if (pos != tstring::npos)
						{
							if (strRessyasyubetsu.find(_T("号")) != tstring::npos)
							{
								//号が含まれる場合は、在来線特急などです、従って、種別→スペースの前、列車名→スペースの後、数字の前まで、号数→最後の数字から号を取り除く、となります
								tstring strRessyaMei = strRessyasyubetsu.substr(pos + 1);
								strRessyasyubetsu = strRessyasyubetsu.substr(0, pos);
								tstring strGouSuu;
								for (int idxd = 0; idxd < strRessyaMei.length(); idxd++)
								{
									if (_istdigit(strRessyaMei[idxd]) != 0)
									{
										strGouSuu = strRessyaMei.substr(idxd, strRessyaMei.length() - idxd - 1);
										strRessyaMei = strRessyaMei.substr(0, idxd);
										aCentDedRessya.setRessyamei(strRessyaMei);
										aCentDedRessya.setGousuu(strGouSuu);
										break;
									}
								}


							}
							else
							{
								//号が含まれない場合は、新幹線及び、号数のない在来線列車です。従って、種別→スペースの前、スペースの後が数字なら号数かつ種別→列車名、スペースの後が数字以外なら列車名、となります
								tstring strRessyaMei = strRessyasyubetsu.substr(pos + 1);
								strRessyasyubetsu = strRessyasyubetsu.substr(0, pos);
								if (_istdigit(strRessyaMei[0]) != 0)
								{
									//数字なので新幹線パターン
									aCentDedRessya.setRessyamei(strRessyasyubetsu);
									aCentDedRessya.setGousuu(strRessyaMei);
								}
								else
								{
									//数字ではないので号数無しパターン
									aCentDedRessya.setRessyamei(strRessyaMei);
								}
							}
						}
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
					tstring strJikoku = strEkimei.substr(strEkimei.size() - 4, 4);
					strEkimei = strEkimei.substr(0, strEkimei.size() - 4);

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

				if (iKudariOuterShuchakuRow >= 0 && !contRessya3[idxk][iKudariOuterShuchakuRow].empty())
				{
					tstring strEkimei = contRessya3[idxk][iKudariOuterShuchakuRow];
					tstring strJikoku = strEkimei.substr(strEkimei.size() - 4, 4);
					strEkimei = strEkimei.substr(0, strEkimei.size() - 4);

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
					else if (contDigitalContent2[idx].eTrType == ETrType::TrType_RessyaMei)
					{
						tstring strRessyasyubetsu = contRessya4[idxn][idx];
						tstring::size_type pos = strRessyasyubetsu.find(' ');
						if (pos != tstring::npos)
						{
							if (strRessyasyubetsu.find(_T("号")) != tstring::npos)
							{
								//号が含まれる場合は、在来線特急などです、従って、種別→スペースの前、列車名→スペースの後、数字の前まで、号数→最後の数字から号を取り除く、となります
								tstring strRessyaMei = strRessyasyubetsu.substr(pos + 1);
								strRessyasyubetsu = strRessyasyubetsu.substr(0, pos);
								tstring strGouSuu;
								for (int idxd = 0; idxd < strRessyaMei.length(); idxd++)
								{
									if (_istdigit(strRessyaMei[idxd]) != 0)
									{
										strGouSuu = strRessyaMei.substr(idxd, strRessyaMei.length() - idxd - 1);
										strRessyaMei = strRessyaMei.substr(0, idxd);
										aCentDedRessya.setRessyamei(strRessyaMei);
										aCentDedRessya.setGousuu(strGouSuu);
										break;
									}
								}


							}
							else
							{
								//号が含まれない場合は、新幹線及び、号数のない在来線列車です。従って、種別→スペースの前、スペースの後が数字なら号数かつ種別→列車名、スペースの後が数字以外なら列車名、となります
								tstring strRessyaMei = strRessyasyubetsu.substr(pos + 1);
								strRessyasyubetsu = strRessyasyubetsu.substr(0, pos);
								if (_istdigit(strRessyaMei[0]) != 0)
								{
									//数字なので新幹線パターン
									aCentDedRessya.setRessyamei(strRessyasyubetsu);
									aCentDedRessya.setGousuu(strRessyaMei);
								}
								else
								{
									//数字ではないので号数無しパターン
									aCentDedRessya.setRessyamei(strRessyaMei);
								}
							}
						}
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
					tstring strJikoku = strEkimei.substr(strEkimei.size() - 4, 4);
					strEkimei = strEkimei.substr(0, strEkimei.size() - 4);

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

				if (iNoboriOuterShuchakuRow >= 0 && !contRessya4[idxn][iNoboriOuterShuchakuRow].empty())
				{
					tstring strEkimei = contRessya4[idxn][iNoboriOuterShuchakuRow];
					tstring strJikoku = strEkimei.substr(strEkimei.size() - 4, 4);
					strEkimei = strEkimei.substr(0, strEkimei.size() - 4);

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
	//if (iRv >= 0)
	//{
	//	pCDedRosenFileData->getCentDedRosen()-> = aCentDedRosen;
	//}
	//if (iRv >= 0)
	//{
	//	CconvCentDedDigital aCconvCentDed;
	//	vector<tstring>* pContDia1Kudari = NULL;
	//	if (!aString1.empty())
	//	{
	//		pContDia1Kudari = &contString1;
	//	}
	//	vector<tstring>* pContDia1Nobori = NULL;
	//	if (!aString2.empty())
	//	{
	//		pContDia1Nobori = &contString2;
	//	}
	//	vector<tstring>* pContDia2Kudari = NULL;
	//	if (!aString3.empty())
	//	{
	//		pContDia2Kudari = &contString3;
	//	}
	//	vector<tstring>* pContDia2Nobori = NULL;
	//	if (!aString4.empty())
	//	{
	//		pContDia2Nobori = &contString4;
	//	}
	//	int iResult = aCconvCentDed.CentDedRosen_From_OuPropertiesText(
	//		&aCentDedRosen,
	//		pContDia1Kudari,
	//		pContDia1Nobori,
	//		pContDia2Kudari,
	//		pContDia2Nobori);
	//}



	//CNodeContainer aCNodeContainer ;
	//if ( iRv >= 0 )
	//{
	//	tstring strErrorInfostring ;
	//	CConvNodeContainer	aConv ;
	//	int iResult = aConv.decode( aString , &aCNodeContainer , &strErrorInfostring ) ;
	//	//	-	-1 ;	//	ディレクトリが途中で閉じています。
	//	if ( iResult < 0 )
	//	{
	//		iRv = -1 ;	//	ディレクトリが途中で閉じています。	
	//	}
	//}
	//if ( iRv >= 0 )
	//{
	//	int iResult = CDedRosenFileData_from_OuPropertiesText( 
	//		pCDedRosenFileData , 
	//		&aCNodeContainer , 
	//		pCOuErrorInfoContainer ) ;
	//	//iResult = 
	//	//-	-1 ;	//	FileType が正しくありません。
	//	//-	-2 ;	//	Rosen Directoryが見つかりません。
	//	//-	-22 ;	//	Ekijikokukeisiki の値が不正です。
	//	//-	-32 ;	//	Ekikibo の値が不正です。
	//	//-	-41 ;	//	DiagramRessyajouhouHyoujiKudari の値が不正です。
	//	//-	-42 ;	//	DiagramRessyajouhouHyoujiNobori の値が不正です。
	//	//-	-101 ;	//	Eki がディレクトリではありません。
	//	//-	-111 ;	//	Syubetsumei が指定されていません。
	//	//-	-152 ;	//	DiagramSenStyle の値が不正です。
	//	//-	-201 ;	//	Ressyasyubetsu がディレクトリではありません。
	//	//-	-211 ;	//	DiaName が指定されていません。
	//	//-	-212 ;	//	RessyaContが見つかりません。
	//	//-	-352 ;	//	起点時刻の設定が不適切です。
	//	//-	-3 ;	//	DispProp Directoryが見つかりません。
	//	//-	-512 ;	//	JikokuhyouFont の内容が不正です。
	//	//-	-522 ;	//	DiaEkimeiFont の内容が不正です。
	//	//-	-532 ;	//	DiaJikokuFont の内容が不正です。
	//	//-	-582 ;	//	DisplayRessyabangou が不正です。
	//	//-	-592 ;	//	DisplayRessyamei が不正です。
	//	//-	-602 ;	//	DiaRessyajouhouHyoujiEkiOrderKudari が不正です。
	//	//-	-612 ;	//	DiaRessyajouhouHyoujiEkiOrderNobori が不正です。
	//	if ( iResult < 0 )
	//	{
	//		//-	-1001 ;	//	FileType が正しくありません。
	//		//-	-1002 ;	//	Rosen Directoryが見つかりません。
	//		//-	-1022 ;	//	Ekijikokukeisiki の値が不正です。
	//		//-	-1032 ;	//	Ekikibo の値が不正です。
	//		//-	-1041 ;	//	DiagramRessyajouhouHyoujiKudari の値が不正です。
	//		//-	-1042 ;	//	DiagramRessyajouhouHyoujiNobori の値が不正です。
	//		//-	-1101 ;	//	Eki がディレクトリではありません。
	//		//-	-1111 ;	//	Syubetsumei が指定されていません。
	//		//-	-1152 ;	//	DiagramSenStyle の値が不正です。
	//		//-	-1201 ;	//	Ressyasyubetsu がディレクトリではありません。
	//		//-	-1211 ;	//	DiaName が指定されていません。
	//		//-	-1212 ;	//	RessyaContが見つかりません。
	//		//-	-1352 ;	//	起点時刻の設定が不適切です。
	//		//-	-1003 ;	//	DispProp Directoryが見つかりません。
	//		//-	-1512 ;	//	JikokuhyouFont の内容が不正です。
	//		//-	-1522 ;	//	DiaEkimeiFont の内容が不正です。
	//		//-	-1532 ;	//	DiaJikokuFont の内容が不正です。
	//		//-	-1582 ;	//	DisplayRessyabangou が不正です。
	//		//-	-1592 ;	//	DisplayRessyamei が不正です。
	//		//-	-1602 ;	//	DiaRessyajouhouHyoujiEkiOrderKudari が不正です。
	//		//-	-1612 ;	//	DiaRessyajouhouHyoujiEkiOrderNobori が不正です。
	//		iRv = iResult - 1000 ;
	//	}
	//}
	//LogMsg( _T("CDedRosenFileData_from_string()=%d") , iRv ) ;
	return ( iRv ) ;
}


void DedRosenFileData::CconvCDedRosenFileDataDigital::ReadDigital(const vector<tstring>& contString,
	vector<vector<tstring>>& contRessya,
	vector<DigitalContent>& contDigitalContent,
	const int iIndividualHandling )
{
	int iTrIndex = -1;
	int iTdIndex = -1;
	for (int idx = 0; idx < (int)contString.size(); idx++)
	{
		tstring::size_type pos = contString[idx].find(_T("<tr"));
		if (pos != tstring::npos)
		{
			iTrIndex++;
			continue;
		}
		pos = contString[idx].find(_T("</tr"));
		if (pos != tstring::npos)
		{
			iTdIndex = -1;
			continue;
		}
		pos = contString[idx].find(_T("<th"));
		if (pos != tstring::npos)
		{
			tstring::size_type pos2 = contString[idx].find(_T("table_th01"));
			if (pos2 != tstring::npos)
			{
				if (contDigitalContent.size() <= iTrIndex)
				{
					DigitalContent sDigitalContent;
					sDigitalContent.strTh1 = TrimTag(contString[idx]);
					contDigitalContent.push_back(sDigitalContent);
				}
				else
				{
					contDigitalContent[iTrIndex].strTh1 = TrimTag(contString[idx]);
				}
			}

			pos2 = contString[idx].find(_T("table_th02"));
			if (pos2 != tstring::npos)
			{
				if (contDigitalContent.size() <= iTrIndex)
				{
					DigitalContent sDigitalContent;
					sDigitalContent.strTh2 = TrimTag(contString[idx]);
					contDigitalContent.push_back(sDigitalContent);
				}
				else
				{
					contDigitalContent[iTrIndex].strTh2 = TrimTag(contString[idx]);
				}
			}
			continue;
		}

		pos = contString[idx].find(_T("<td"));
		if (pos != tstring::npos)
		{
			iTdIndex++;
			tstring::size_type pos2 = contString[idx].find(_T("operating_box"));
			if (pos2 != tstring::npos)
			{
				//operating_boxの場合は、ポップアップする側の値を取得する
				tstring strTemp = _T("");
				for(; idx < (int)contString.size(); idx++)
				{
					tstring::size_type pos3 = contString[idx].find(_T("operating_text"));
					if (pos3 != tstring::npos)
					{
						strTemp = TrimTag(contString[idx]);
					}
					pos3 = contString[idx].find(_T("</td"));
					if (pos3 != tstring::npos)
					{
						break;
					}
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

			pos2 = contString[idx].find(_T("change"));
			if (pos2 != tstring::npos)
			{
				//changeの場合は、表示されている文字列(時刻)を取得する
				tstring strTemp = _T("");
				for (; idx < (int)contString.size(); idx++)
				{
					tstring::size_type pos3 = contString[idx].find(_T("operating_btn"));
					if (pos3 != tstring::npos)
					{
						strTemp = TrimTag(contString[idx]);
					}
					pos3 = contString[idx].find(_T("</td"));
					if (pos3 != tstring::npos)
					{
						break;
					}
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


			pos2 = contString[idx].find(_T("trainNo"));
			if (pos2 != tstring::npos)
			{
				//"trainNo"の場合は、列車名と号数を取得する
				tstring strTemp = TrimTag(contString[idx]);
				strTemp += _T(" ");
				tstring strTemp2 = contString[idx].substr(pos2 + 9);
				strTemp += TrimTag(strTemp2);

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

			pos2 = contString[idx].find(_T("f_trainText"));
			if (pos2 != tstring::npos)
			{
				//"f_trainText"の場合は、始発駅名と始発時刻を取得する
				tstring strTemp = TrimTag(contString[idx]);
				idx++;
				strTemp += TrimTag(contString[idx]);

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

			pos2 = contString[idx].find(_T("e_trainText"));
			if (pos2 != tstring::npos)
			{
				//"e_trainText"の場合は、終着駅名と終着時刻を取得する
				tstring strTemp = TrimTag(contString[idx]);
				idx++;
				strTemp += TrimTag(contString[idx]);

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
				contRessya.push_back({ TrimTag(contString[idx]) });
			}
			else
			{
				contRessya[iTdIndex].push_back(TrimTag(contString[idx]));
			}
			continue;

		}

	}

	{
		//設備欄がある場合はそれを削除する

		int iSetsubiRow = -1;
		for (int idxd = 0; idxd < contDigitalContent.size(); idxd++)
		{
			if (contDigitalContent[idxd].strTh1 == _T("設備"))
			{
				iSetsubiRow = idxd;
				break;
			}
		}

		if (iSetsubiRow >= 0)
		{
			contDigitalContent.erase(contDigitalContent.begin() + iSetsubiRow);

			for (int idxr = 0; idxr < contRessya.size(); idxr++)
			{
				if (contRessya[idxr].size() <= iSetsubiRow)
				{
					continue;
				}
				contRessya[idxr].erase(contRessya[idxr].begin() + iSetsubiRow);
			}
		}
	}

	//ここから、路線ごとの個別取り扱い
	if (iIndividualHandling == 1)
	{
		//東北新幹線上りにおいて、秋田新幹線用の盛岡駅着時刻欄を追加する。
		//1.contDigitalContentの「雫石駅発時刻」の次の行に、「盛岡駅着時刻」を挿入する
		//"元々の"盛岡着時刻の位置。秋田新幹線用を挿入する前に、元々の位置を保存しておく
		int iTohokuMoriokaChakuRow = -1;
		for (int idxd = 0; idxd < contDigitalContent.size(); idxd++)
		{
			if (contDigitalContent[idxd].strTh1 == _T("盛岡") && contDigitalContent[idxd].strTh2 == _T("着"))
			{
				iTohokuMoriokaChakuRow = idxd;
				break;
			}
		}
		//秋田新幹線用の盛岡着時刻の位置
		int iAkitaMoriokaChakuRow = -1;
		if (iTohokuMoriokaChakuRow >= 0)
		{
			for (int idxd = 0; idxd < contDigitalContent.size(); idxd++)
			{
				if (contDigitalContent[idxd].strTh1 == _T("雫石") && contDigitalContent[idxd].strTh2 == _T("発"))
				{
					iAkitaMoriokaChakuRow = idxd + 1;

					DigitalContent sDigitalContent;
					sDigitalContent.strTh1 = _T("盛岡");
					sDigitalContent.strTh2 = _T("着");
					contDigitalContent.insert(contDigitalContent.begin() + iAkitaMoriokaChakuRow, sDigitalContent);
					break;
				}
			}
		}

		if (iTohokuMoriokaChakuRow >= 0 && iAkitaMoriokaChakuRow >= 0)
		{
			for (int idxr = 0; idxr < contRessya.size(); idxr++)
			{
				if (contRessya[idxr].size() <= iTohokuMoriokaChakuRow)
				{
					continue;
				}
				tstring strTohokuMoriokaChaku = contRessya[idxr][iTohokuMoriokaChakuRow];
				if (contRessya[idxr][iAkitaMoriokaChakuRow - 1].empty() || strTohokuMoriokaChaku.empty())
				{
					//雫石発が空なら、秋田新幹線用の盛岡着の位置に、空行を挿入する。
					//また、もし東北盛岡着が空でも、秋田新幹線用の盛岡着の位置に、空行を挿入する。
					contRessya[idxr].insert(contRessya[idxr].begin() + iAkitaMoriokaChakuRow, tstring());
				}
				else
				{
					//雫石発、東北盛岡着共に空ではないなら、東北盛岡着を!!(経由なし)にして、予めコピーしておいた東北盛岡着を秋田盛岡着として挿入。
					contRessya[idxr][iTohokuMoriokaChakuRow] = _T("||");
					contRessya[idxr].insert(contRessya[idxr].begin() + iAkitaMoriokaChakuRow, strTohokuMoriokaChaku);

				}



			}
		}
	}
	else if (iIndividualHandling == 2)
	{
		//ＩＧＲいわて銀河鉄道・青い森鉄道において、設備欄がある場合はそれを削除する
		//Ver2.06.17 設備欄削除は、全路線で行うことにする

		//int iSetsubiRow = -1;
		//for (int idxd = 0; idxd < contDigitalContent.size(); idxd++)
		//{
		//	if (contDigitalContent[idxd].strTh1 == _T("設備"))
		//	{
		//		iSetsubiRow = idxd;
		//		break;
		//	}
		//}

		//if (iSetsubiRow >= 0)
		//{
		//	contDigitalContent.erase(contDigitalContent.begin() + iSetsubiRow);

		//	for (int idxr = 0; idxr < contRessya.size(); idxr++)
		//	{
		//		if (contRessya[idxr].size() <= iSetsubiRow)
		//		{
		//			continue;
		//		}
		//		contRessya[idxr].erase(contRessya[idxr].begin() + iSetsubiRow);
		//	}
		//}

		//ＩＧＲいわて銀河鉄道・青い森鉄道において、前の区間・始発欄がない場合は、それを追加する

		int iUntenbiRow = -1;
		int iMaeNoKukanRow = -1;
		for (int idxd = 0; idxd < contDigitalContent.size(); idxd++)
		{
			if (contDigitalContent[idxd].strTh1 == _T("運転日"))
			{
				iUntenbiRow = idxd;
			}
			if (contDigitalContent[idxd].strTh1 == _T("前の区間"))
			{
				iMaeNoKukanRow = idxd;
			}
		}

		if (iMaeNoKukanRow < 0 && iUntenbiRow >= 0)
		{
			DigitalContent sDigitalContent;
			sDigitalContent.strTh1 = _T("前の区間");
			contDigitalContent.insert(contDigitalContent.begin() + iUntenbiRow + 1, sDigitalContent);

			sDigitalContent.strTh1 = _T("始発");
			contDigitalContent.insert(contDigitalContent.begin() + iUntenbiRow + 2, sDigitalContent);

			for (int idxr = 0; idxr < contRessya.size(); idxr++)
			{
				if (contRessya[idxr].size() <= iUntenbiRow)
				{
					continue;
				}
				contRessya[idxr].insert(contRessya[idxr].begin() + iUntenbiRow + 1, _T(""));
				contRessya[idxr].insert(contRessya[idxr].begin() + iUntenbiRow + 1, _T(""));
			}
		}
	}
	else if (iIndividualHandling == 3)
	{
		//上越・北陸新幹線上りにおいて、新潟方面からの越後湯沢駅着時刻欄を追加する。
		//1.contDigitalContentの「浦佐駅発時刻」の次の行に、「越後湯沢駅着時刻」を挿入する
		//"元々の"越後湯沢着時刻の位置。新潟方面用を挿入する前に、元々の位置を保存しておく
		int iGalaEchigoYuzawaChakuRow = -1;
		for (int idxd = 0; idxd < contDigitalContent.size(); idxd++)
		{
			if (contDigitalContent[idxd].strTh1 == _T("越後湯沢") && contDigitalContent[idxd].strTh2 == _T("着"))
			{
				iGalaEchigoYuzawaChakuRow = idxd;
				break;
			}
		}
		//新潟方面用の越後湯沢着時刻の位置
		int iNiigataEchigoYuzawaChakuRow = -1;
		if (iGalaEchigoYuzawaChakuRow >= 0)
		{
			for (int idxd = 0; idxd < contDigitalContent.size(); idxd++)
			{
				if (contDigitalContent[idxd].strTh1 == _T("浦佐") && contDigitalContent[idxd].strTh2 == _T("発"))
				{
					iNiigataEchigoYuzawaChakuRow = idxd + 1;

					DigitalContent sDigitalContent;
					sDigitalContent.strTh1 = _T("越後湯沢");
					sDigitalContent.strTh2 = _T("着");
					contDigitalContent.insert(contDigitalContent.begin() + iNiigataEchigoYuzawaChakuRow, sDigitalContent);
					break;
				}
			}
		}

		if (iGalaEchigoYuzawaChakuRow >= 0 && iNiigataEchigoYuzawaChakuRow >= 0)
		{
			for (int idxr = 0; idxr < contRessya.size(); idxr++)
			{
				if (contRessya[idxr].size() <= iGalaEchigoYuzawaChakuRow)
				{
					continue;
				}
				tstring strGalaEchigoYuzawaChaku = contRessya[idxr][iGalaEchigoYuzawaChakuRow];
				if (contRessya[idxr][iNiigataEchigoYuzawaChakuRow - 1].empty() || strGalaEchigoYuzawaChaku.empty())
				{
					//浦佐発が空なら、新潟方面用の越後湯沢着の位置に、空行を挿入する。
					//また、もしガーラ湯沢方面の越後湯沢着が空でも、新潟方面用の越後湯沢着の位置に、空行を挿入する。
					contRessya[idxr].insert(contRessya[idxr].begin() + iNiigataEchigoYuzawaChakuRow, tstring());
				}
				else
				{
					//浦佐発、ガーラ湯沢方面の越後湯沢着共に空ではないなら、ガーラ湯沢方面の越後湯沢着を!!(経由なし)にして、予めコピーしておいたガーラ湯沢方面の越後湯沢着を新潟方面用の越後湯沢着として挿入。
					contRessya[idxr][iGalaEchigoYuzawaChakuRow] = _T("||");
					contRessya[idxr].insert(contRessya[idxr].begin() + iNiigataEchigoYuzawaChakuRow, strGalaEchigoYuzawaChaku);

				}



			}
		}
	}
}

tstring CconvCDedRosenFileDataDigital::TrimTag(const tstring strInput)
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

