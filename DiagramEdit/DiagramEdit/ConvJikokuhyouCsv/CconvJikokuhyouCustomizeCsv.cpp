/*
OuDiaSecond Copyright (C) 2017-2026 diagram_mania

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
// ****************************************************************
// $Id: CconvJikokuhyouCustomizeCsv.cpp 
// ****************************************************************
#include "stdafx.h"
#include "CconvJikokuhyouCustomizeCsv.h"
#include "str\strprintf.h"
//#include "..\ViewJikokuhyou\JikokuhyouColSpec\CdYColSpecCont.h"
#include "Str/stringSplit.h"
#include "..\entDed\CentDedBeforeOperation.h"
#include "..\entDed\CentDedAfterOperation.h"
#include <algorithm>

namespace ConvJikokuhyouCsv{

using namespace std ;
using namespace OuLib ;
using namespace OuLib::Str ;

//using ViewJikokuhyou::JikokuhyouColSpec::CdYColSpecCont;
//using ViewJikokuhyou::JikokuhyouColSpec::CdYColSpec;

/**
	FileTypeの 名前
*/
const TCHAR* const nameFileType = _T("FileType") ;

/**
	FileType の値
*/
const TCHAR* const nameFileTypeValue = _T("OuDiaSecond.JikokuhyouCsv.3") ;

const int CSVROWINDEX_Ressyabangou = 4 ;
const int CSVROWINDEX_Ressyasyubetsu = 5 ;
const int CSVROWINDEX_Ressyamei = 6 ;
const int CSVROWINDEX_Gousuu = 7 ;
const int CSVROWINDEX_Gou = 8 ;
const int CSVROWINDEX_Ekijikoku0 = 9 ;
const int CSVCOLUMNINDEX_Ressya0 = 2 ;

/** 時刻の書式を保持します。 */
//const CdDedJikoku::CConv	g_CdDedJikokuConv(
//	true ,		//	NoColon 
//	// 時が 00 から 09 の場合、10の位の "0" を削除します。
//	CdDedJikoku::CConv::EHour_ZeroToNone ,	
//	CdDedJikoku::CConv::ESecond_NoSecond 	// 秒を常に出力しません。 
//	) ;
//
//const CdDedJikoku::CConv	g_CdDedJikokuConvSecond(
//	true,		//	NoColon 
//				// 時が 00 から 09 の場合、10の位の "0" を削除します。
//	CdDedJikoku::CConv::EHour_ZeroToNone,
//	CdDedJikoku::CConv::ESecond_Output 	
//);
//const CdDedJikoku::CConv	g_CdDedJikokuConvColon(
//	false,		//	Colon 
//				// 時が 00 から 09 の場合、10の位の "0" を削除します。
//	CdDedJikoku::CConv::EHour_ZeroToNone,
//	CdDedJikoku::CConv::ESecond_NoSecond 	// 秒を常に出力しません。 
//);
//
//const CdDedJikoku::CConv	g_CdDedJikokuConvSecondColon(
//	false,		//	Colon 
//				// 時が 00 から 09 の場合、10の位の "0" を削除します。
//	CdDedJikoku::CConv::EHour_ZeroToNone,
//	CdDedJikoku::CConv::ESecond_Output
//);

	// --------------------------------
	//@name	駅時刻セルの文字列の解釈
	// --------------------------------
tstring CconvJikokuhyouCustomizeCsv::encode_Ekijikoku( 
		CentDedEkiJikoku::EEkiatsukai eEkiatsukai , 
		const CdDedJikoku& aCdDedJikoku ,
		const bool bDisplaySecondEkiJikoku,
		const bool bDisplayColonEkiJikoku,
	const int iSecondRoundChaku,
	const int iSecondRoundHatsu,
	const bool bDisplay2400,
	const bool bIsChakuJikoku,
	const CdDedJikoku& ReferJikoku)
{
	tstring strValue = _T("");

	CdDedJikoku::CConv::ESecond eSecond = CdDedJikoku::CConv::ESecond_NoSecond;
	if (bDisplaySecondEkiJikoku)
	{
		eSecond = CdDedJikoku::CConv::ESecond_Output;
	}

	CdDedJikoku::CConv aConv(
		!bDisplayColonEkiJikoku,
		CdDedJikoku::CConv::EHour_ZeroToSpace,
		eSecond,
		(CdDedJikoku::CConv::ESecondRound)iSecondRoundChaku,
		(CdDedJikoku::CConv::ESecondRound)iSecondRoundHatsu,
		bDisplay2400
	);

	switch( eEkiatsukai )
	{
	case CentDedEkiJikoku::Ekiatsukai_Teisya:
		{
			strValue = aConv.encode(aCdDedJikoku, bIsChakuJikoku, ReferJikoku);
			//if (bDisplaySecondEkiJikoku) {
			//	if (bDisplayColonEkiJikoku)
			//	{
			//		strValue = g_CdDedJikokuConvSecondColon.encode(aCdDedJikoku);
			//	}
			//	else
			//	{
			//		strValue = g_CdDedJikokuConvSecond.encode(aCdDedJikoku);
			//	}
			//}
			//else 
			//{
			//	if (bDisplayColonEkiJikoku)
			//	{
			//		strValue = g_CdDedJikokuConvColon.encode(aCdDedJikoku);
			//	}
			//	else
			//	{
			//		strValue = g_CdDedJikokuConv.encode(aCdDedJikoku);
			//	}
			//}
		}
		break ;
	case CentDedEkiJikoku::Ekiatsukai_Tsuuka:
		{
			strValue = aConv.encode(aCdDedJikoku, bIsChakuJikoku, ReferJikoku);
			strValue += _T("?");
			//if (bDisplaySecondEkiJikoku) {
			//	strValue = _T("");
			//	if (bDisplayColonEkiJikoku)
			//	{
			//		strValue += g_CdDedJikokuConvSecondColon.encode(aCdDedJikoku);
			//	}
			//	else
			//	{
			//		strValue += g_CdDedJikokuConvSecond.encode(aCdDedJikoku);
			//	}
			//	strValue += _T("?");
			//}
			//else
			//{
			//	strValue = _T("");
			//	if (bDisplayColonEkiJikoku)
			//	{
			//		strValue += g_CdDedJikokuConvColon.encode(aCdDedJikoku);

			//	}
			//	else
			//	{
			//		strValue += g_CdDedJikokuConv.encode(aCdDedJikoku);
			//	}
			//	strValue += _T("?");
			//}
		}
		break ;
	}

	return strValue ;
}

// --------------------------------
	//@name encode() の下請関数	
	// --------------------------------

int CconvJikokuhyouCustomizeCsv::encode_AddRessya( 
		const Mu<const CentDedRessyasyubetsu*>* pCentDedRessyasyubetsuContGet ,
		const Mu<const CentDedRessya*>* pCentDedRessyaCont,
		const CustomizeJikokuhyouContent& aCustomizeJikokuhyouContent,
		CdCsvDocument* pCdCsvDocument ,
		const CentDedEkiCont* pCentDedEkiCont,
		const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki,
		const bool bDisplayTsuukaEkiJikoku,
		const bool bDisplaySecondEkiJikoku,
		const bool bDisplayColonEkiJikoku,
		const bool bDisplayShihatsuShuchakuEkimei,
		const bool bDisplayParentSyubetsu,
		const bool bDisplayRessyamei,
		const int iEnableOperation,
		const int iSecondRoundChaku,
		const int iSecondRoundHatsu,
		const bool bDisplay2400,
		const int iOperationNumberRows,
		const deque<int> m_iOuterShihatsuDisplayEkiOrder,
		const deque<int> m_iOuterShuchakuDisplayEkiOrder)
{
	int iRv = 0 ;

	int iRessyaIndexContIndex = 0;
	const CentDedRessya* pCentDedRessya = NULL;
	//暫定措置(もっといい方法があるか考える)
	//aCentDedRessya:パターンダイヤプレビュー機能が有効なとき、aCentDedRessyaに対象列車をコピーしてから、modifyRessyaJikokuを実施し、そのアドレスでpCentDedRessyaに上書きする
	CentDedRessya aCentDedRessya(pCentDedEkiCont->size(), ERessyahoukou::Ressyahoukou_Kudari);
	if (!aCustomizeJikokuhyouContent.iRessyaIndexCont.empty())
	{
		pCentDedRessya = pCentDedRessyaCont->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex]);
		if (aCustomizeJikokuhyouContent.iShiftSecond != 0)
		{
			aCentDedRessya = CentDedRessya(*pCentDedRessya);
			aCentDedRessya.modifyRessyaJikoku(
				aCustomizeJikokuhyouContent.iShiftSecond,
				CdDedJikokuOrder(0, CdDedJikokuOrder::EkiJikokuItem_Chaku));
			pCentDedRessya = &aCentDedRessya;
		}
	}
	if ( iRv >= 0 )
	{
		bool bDisplayNullRessya = false;
		if (aCustomizeJikokuhyouContent.iRessyaIndexCont.empty())
		{
			if (aCustomizeJikokuhyouContent.iReleaseEkiOrder >= 0)
			{
				if (m_iOuterShuchakuDisplayEkiOrder[aCustomizeJikokuhyouContent.iReleaseEkiOrder] < 0)
				{
					bDisplayNullRessya = true;
				}
			}
			else if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
			{
				if (m_iOuterShihatsuDisplayEkiOrder[aCustomizeJikokuhyouContent.iConnectEkiOrder] < 0)
				{
					bDisplayNullRessya = true;
				}
			}
		}
		else if(pCentDedRessya->isNull() ||
			pCentDedRessya->getValidSihatsuEki() == -1 ||
			pCentDedRessya->getValidSyuuchakuEki() == -1)
		{
			bDisplayNullRessya = true;
		}
		if (bDisplayNullRessya)
		{
			encode_AddRessyaNull(
				pCdCsvDocument,
				bDisplayShihatsuShuchakuEkimei,
				bDisplayRessyamei,
				iEnableOperation) ;
			return iRv;
		}
	}
	// --------------------------------
	const CentDedRessyasyubetsu* pCentDedRessyasyubetsu = NULL ;
	if ( iRv >= 0 )
	{
		if (pCentDedRessya == NULL)
		{
			if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
			{
				pCentDedRessyasyubetsu = pCentDedRessyasyubetsuContGet
					->get(aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex);
			}
			else
			{
				pCentDedRessyasyubetsu = pCentDedRessyasyubetsuContGet
					->get(aCustomizeJikokuhyouContent.iRessyasyubetsuIndex);
			}
		}
		else
		{
			pCentDedRessyasyubetsu = pCentDedRessyasyubetsuContGet
				->get(pCentDedRessya->getRessyasyubetsuIndex());
		}
		if (bDisplayParentSyubetsu && pCentDedRessyasyubetsu->getParentSyubetsuIndex() >= 0)
		{
			pCentDedRessyasyubetsu = pCentDedRessyasyubetsuContGet
				->get(pCentDedRessyasyubetsu->getParentSyubetsuIndex());
		}
	}
	//pCentDedRessysyubetsu = 列車種別オブジェクト

	int iRowIndex = CSVROWINDEX_Ressyabangou;
	//＜2.5＞5行目 <列車番号>
	if ( iRv >= 0 )
	{
		CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex) ;
		if (pCentDedRessya == NULL)
		{
			aRow.getCellCont()->insert(CdCsvCell(aCustomizeJikokuhyouContent.strRessyabangou));
		}
		else
		{
			aRow.getCellCont()->insert(CdCsvCell(pCentDedRessya->getRessyabangou()));
		}
		pCdCsvDocument->getRowCont()->set( aRow , iRowIndex) ;
		iRowIndex++;
	}

	//＜2.6＞ <運用番号>
	if (iRv >= 0 && iEnableOperation > 1)
	{
		vector<tstring> strOperationNumber;

		if (pCentDedRessya == NULL)
		{
			strOperationNumber = aCustomizeJikokuhyouContent.strOperationNumber;
		}
		else
		{
			strOperationNumber = pCentDedRessya->getOperationNumber(
				pCentDedRessya->getValidSihatsuEki());
		}
		for (int idx = 0; idx < iOperationNumberRows; idx++)
		{
			tstring strText;
			if (strOperationNumber.empty())
			{
				strText = _T("");
			}
			else if (idx == iOperationNumberRows - 1)
			{
				if (idx != 0)
				{
					strText = _T("+";)
				}
				strText += joinc('+', strOperationNumber);
			}
			else
			{
				if (idx != 0)
				{
					strText = _T("+";)
				}
				strText += strOperationNumber.front();
				strOperationNumber.erase(strOperationNumber.begin());
			}

			CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
			aRow.getCellCont()->insert(CdCsvCell(strText));
			pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
			iRowIndex++;
		}
	}

	//＜2.7＞ <列車種別>
	if (iRv >= 0)
	{
		CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
		if ((pCentDedRessya != NULL && !pCentDedRessya->isNull()) ||
			aCustomizeJikokuhyouContent.iRessyasyubetsuIndex != -1 ||
			aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex != -1)
		{
			aRow.getCellCont()->insert(CdCsvCell(pCentDedRessyasyubetsu->getRyakusyou()));
		}
		else
		{
			aRow.getCellCont()->insert(CdCsvCell());
		}
		pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
		iRowIndex++;
	}

	//＜2.8＞<列車名>
	if ( iRv >= 0 && bDisplayRessyamei)
	{
		CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex) ;
		if (pCentDedRessya == NULL)
		{
			aRow.getCellCont()->insert(CdCsvCell(aCustomizeJikokuhyouContent.strRessyamei));
		}
		else if (!pCentDedRessya->isNull())
		{
			aRow.getCellCont()->insert(CdCsvCell(pCentDedRessya->getRessyamei()));
		}
		else
		{
			aRow.getCellCont()->insert(CdCsvCell());
		}
		pCdCsvDocument->getRowCont()->set( aRow , iRowIndex) ;
		iRowIndex++;
	}

	//＜2.9＞<号数>
	if ( iRv >= 0 && bDisplayRessyamei)
	{
		CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex) ;
		if (pCentDedRessya == NULL)
		{
			aRow.getCellCont()->insert(CdCsvCell(aCustomizeJikokuhyouContent.strGousuu));
		}
		else if (!pCentDedRessya->isNull())
		{
			aRow.getCellCont()->insert(CdCsvCell(pCentDedRessya->getGousuu()));
		}
		else
		{
			aRow.getCellCont()->insert(CdCsvCell());
		}
		pCdCsvDocument->getRowCont()->set( aRow , iRowIndex) ;
		iRowIndex++;
	}
	//＜2.10＞<号表示>
	if ( iRv >= 0 && bDisplayRessyamei)
	{
		tstring	strValue ;
		if (pCentDedRessya == NULL)
		{
			if (!aCustomizeJikokuhyouContent.strGousuu.empty())
			{
				strValue = m_nameGou;
			}
		}
		else
		{
			if (!pCentDedRessya->isNull() && !pCentDedRessya->getGousuu().empty())
			{
				strValue = m_nameGou;
			}
		}
		CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex) ;
		aRow.getCellCont()->insert( CdCsvCell( strValue ) ) ;
		pCdCsvDocument->getRowCont()->set( aRow , iRowIndex) ;
		iRowIndex++;
	}

	//＜2.11＞ <始発駅名>
	if (iRv >= 0&& bDisplayShihatsuShuchakuEkimei)
	{
		tstring strText;
		if (aCustomizeJikokuhyouContent.iSihatsuEkiOrder >= -2)
		{
			//路線外始発扱い

			if (aCustomizeJikokuhyouContent.iSihatsuEkiOrder < 0)
			{
				strText = m_nameLoop;
			}
			else if (aCustomizeJikokuhyouContent.iOuterShihatsuEkiIndex >= 0)
			{
				strText = muCdDedEki->get(aCustomizeJikokuhyouContent.iSihatsuEkiOrder).getOuterTerminalJikokuRyaku(
					aCustomizeJikokuhyouContent.iOuterShihatsuEkiIndex, true);
			}
			else
			{
				strText = muCdDedEki->get(aCustomizeJikokuhyouContent.iSihatsuEkiOrder).getEkimeiJikokuhyouRyaku(true);
			}
		}
		else if (aCustomizeJikokuhyouContent.iReleaseEkiOrder >= 0)
		{
			//分割列車(当面は分割駅を表示)
			strText = muCdDedEki->get(aCustomizeJikokuhyouContent.iReleaseEkiOrder).getEkimeiJikokuhyouRyaku(true);

		}
		else if (pCentDedRessya->getValidSihatsuEki() >= 0)
		{
			if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
			{
				strText = muCdDedEki->get(pCentDedRessya->getValidSihatsuEki()).getOuterTerminalJikokuRyaku(
					pCentDedRessya->getFirstOperation().getOuterShihatsuekiIndex(), true);
			}
			else
			{
				strText = muCdDedEki->get(pCentDedRessya->getValidSihatsuEki()).getEkimeiJikokuhyouRyaku(true);
			}
		}
		CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
		aRow.getCellCont()->insert(CdCsvCell(strText));
		pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
		iRowIndex++;
	}
	
	//＜2.13＞ <終着駅名>
	if (iRv >= 0&& bDisplayShihatsuShuchakuEkimei)
	{
		tstring strText;
		if (aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder >= -2)
		{
			//路線外終着扱い
			if (aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder < 0)
			{
				strText = m_nameLoop;
			}
			else if (aCustomizeJikokuhyouContent.iOuterShuchakuEkiIndex >= 0)
			{
				strText = muCdDedEki->get(aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder).getOuterTerminalJikokuRyaku(
					aCustomizeJikokuhyouContent.iOuterShuchakuEkiIndex, true);
			}
			else
			{
				strText = muCdDedEki->get(aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder).getEkimeiJikokuhyouRyaku(true);
			}
		}
		else if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
		{
			//併合列車(当面は併合駅を表示)
			strText = muCdDedEki->get(aCustomizeJikokuhyouContent.iConnectEkiOrder).getEkimeiJikokuhyouRyaku(true);

		}
		else if (pCentDedRessya->getValidSyuuchakuEki() >= 0)
		{
			if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
			{
				strText = muCdDedEki->get(pCentDedRessya->getValidSyuuchakuEki()).getOuterTerminalJikokuRyaku(
					pCentDedRessya->getLastOperation().getOuterShuchakuekiIndex(), true);
			}
			else
			{
				strText = muCdDedEki->get(pCentDedRessya->getValidSyuuchakuEki()).getEkimeiJikokuhyouRyaku(true);
			}
		}
		CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
		aRow.getCellCont()->insert(CdCsvCell(strText));
		pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
		iRowIndex++;
	}
	
	//＜2.10＞10行目～ 駅時刻
	
	if ( iRv >= 0 )
	{
		int iValidSyuuchakuEki = -1;
		if (pCentDedRessya != NULL)
		{
			iValidSyuuchakuEki = pCentDedRessya->getValidSyuuchakuEki();
		}
		int iCurrentRessyaShihatsuEkiOrder = -1;
		for (int iYColumnNumber = m_CdYColSpecCont.getColumnNumber_Ekijikoku_begin();
			iYColumnNumber < m_CdYColSpecCont.getColumnNumber_Ekijikoku_end(); iYColumnNumber++)
		{
			const CdYColSpec aCdYColSpec = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumber);
			int iEkiOrder = aCdYColSpec.getEkiOrder();

			CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(aCdYColSpec.getEkiOrder());

			/**
				種別変更により、同一列に複数の列車を表示するとき、
				表示対象の列車を切り替えます。
				切り替えは、列車の有効終着駅の列車番号欄以降の描写を最初に行うときに行います。
			*/
			if (!aCustomizeJikokuhyouContent.iRessyaIndexCont.empty() &&
				iRessyaIndexContIndex < (int)aCustomizeJikokuhyouContent.iRessyaIndexCont.size() - 1 &&
				((aCdYColSpec.getColumnType() >= CdYColSpec::ColumnType_EkiRessyabangou &&
				aCdYColSpec.getEkiOrder() == iValidSyuuchakuEki) ||
				(aCdYColSpec.getEkiOrder() > iValidSyuuchakuEki &&
				iValidSyuuchakuEki != -1)))
			{
				iRessyaIndexContIndex++;
				pCentDedRessya = pCentDedRessyaCont->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex]);

				pCentDedRessyasyubetsu = pCentDedRessyasyubetsuContGet
					->get(pCentDedRessya->getRessyasyubetsuIndex());
				if (bDisplayParentSyubetsu && pCentDedRessyasyubetsu->getParentSyubetsuIndex() >= 0)
				{
					pCentDedRessyasyubetsu = pCentDedRessyasyubetsuContGet
						->get(pCentDedRessyasyubetsu->getParentSyubetsuIndex());
				}

				iCurrentRessyaShihatsuEkiOrder = iValidSyuuchakuEki;
				iValidSyuuchakuEki = pCentDedRessya->getValidSyuuchakuEki();
			}


			//CentDedEkiJikoku aCentDedEkiJikoku
			//	= pCentDedRessya->getCentDedEkiJikoku(aCdYColSpec.getEkiOrder());

			if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_Ekijikoku_Chaku)
			{
				tstring	strText = _T("");
				if (pCentDedRessya == NULL)
				{
					/**
						pCentDedRessya == NULLの場合は、
						分割+路線外終着または路線外始発+増結のどちらかのパターンです。
						なお、分割駅に対応する路線外終着表示欄、もしくは解結駅に対応する路線外始発表示欄がない場合は、この列車の描写は行わず、空行となります。
					*/
					if (aCustomizeJikokuhyouContent.iReleaseEkiOrder >= 0)
					{
						/**
							分割+路線外終着の場合、
							分割駅ならば↴を表示します。(当駅発時刻の表示は無しに)
							分割駅より後かつ、路線外終着表示駅までの場合は、経由なしを表示します。
							分割駅より一つ上の駅の場合、分割駅が発時刻のみ表示で、この項が分割駅の項の直上なら、ここで↴を表示します。
							それ以外の場合は、----もしくは・・を表示します
						*/
						if (iEkiOrder + 1 == aCustomizeJikokuhyouContent.iReleaseEkiOrder)
						{
							CentDedEkiCont::CdDedEki aCdDedEkiNext = muCdDedEki->get(iEkiOrder + 1);
							if (!aCdDedEkiNext.getJikokuhyouChakuJikokuDisplay() &&
								aCdDedEkiNext.getJikokuhyouHatsuJikokuDisplay())
							{
								int iYColumnNumberNext = iYColumnNumber + 1;
								CdYColSpec aCdYColSpecNext = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberNext);
								if (aCdYColSpecNext.getEkiOrder() == iEkiOrder + 1)
								{
									strText = m_nameRelease;
								}
							}
						}
						else if (iEkiOrder == aCustomizeJikokuhyouContent.iReleaseEkiOrder)
						{
							strText = m_nameRelease;
						}
						else if (iEkiOrder > aCustomizeJikokuhyouContent.iReleaseEkiOrder &&
							iEkiOrder <= m_iOuterShuchakuDisplayEkiOrder[aCustomizeJikokuhyouContent.iReleaseEkiOrder])
						{
							strText = m_nameKeiyunasi;

						}
					}
					else if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
					{
						/**
							路線外始発+併合の場合
							併合駅ならば当駅着時刻を表示します。
							路線外始発表示駅から併合駅の前までなら、経由なしを表示します。
							併合駅の次の駅の場合、併合駅が着時刻のみ表示かつ、この項が併合駅の直下なら、この項に↳を表示します。
							それ以外の場合は、----もしくは・・を表示します
						*/
						if (iEkiOrder - 1 == aCustomizeJikokuhyouContent.iConnectEkiOrder)
						{
							CentDedEkiCont::CdDedEki aCdDedEkiPrev = muCdDedEki->get(iEkiOrder - 1);
							if (aCdDedEkiPrev.getJikokuhyouChakuJikokuDisplay() &&
								!aCdDedEkiPrev.getJikokuhyouHatsuJikokuDisplay())
							{
								int iYColumnNumberPrev = iYColumnNumber - 1;
								CdYColSpec aCdYColSpecPrev = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberPrev);
								if (aCdYColSpecPrev.getEkiOrder() == iEkiOrder - 1)
								{
									strText = m_nameConnect;
								}
							}
						}
						else if (iEkiOrder == aCustomizeJikokuhyouContent.iConnectEkiOrder)
						{
							strText = encode_Ekijikoku(
								aCustomizeJikokuhyouContent.eEkiatsukai,
								aCustomizeJikokuhyouContent.ChakuJikoku,
								bDisplaySecondEkiJikoku,
								bDisplayColonEkiJikoku,
								iSecondRoundChaku,
								iSecondRoundHatsu,
								bDisplay2400,
								true);
						}
						else if (iEkiOrder >= m_iOuterShihatsuDisplayEkiOrder[aCustomizeJikokuhyouContent.iConnectEkiOrder] &&
							iEkiOrder < aCustomizeJikokuhyouContent.iConnectEkiOrder)
						{
							strText = m_nameKeiyunasi;
						}
					}
				}
				else
				{
					CentDedEkiJikoku	aCentDedEkiJikoku =
						pCentDedRessya->getCentDedEkiJikoku(iEkiOrder);
					CdDedJikoku aCdDedJikoku
						= aCentDedEkiJikoku.getChakujikoku();

					// --------------------------------
					//	駅時刻に合わせて、セルに文字を表示
					// --------------------------------
					int iValidSihatsuEki = pCentDedRessya->getValidSihatsuEki();
					int iValidSyuuchakuEki = pCentDedRessya->getValidSyuuchakuEki();
					if (iValidSihatsuEki == -1 || iValidSyuuchakuEki == -1)
					{
						//空白のまま
					}
					else if (iEkiOrder < iValidSihatsuEki)
					{
						if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] <= iEkiOrder)
						{
							//路線外始発
							strText = m_nameKeiyunasi;

						}
						else if (aCustomizeJikokuhyouContent.iSihatsuEkiOrder >= -2 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] <= iEkiOrder)
						{
							//路線外始発相当
							strText = m_nameKeiyunasi;
						}
						else if (iCurrentRessyaShihatsuEkiOrder != -1)
						{
							//一体化の2列車目以降(前の列車との間に、経由なし区間がある場合)
							strText = m_nameKeiyunasi;
						}
						else if (iEkiOrder == aCustomizeJikokuhyouContent.iReleaseEkiOrder)
						{
							/**
								発時刻表示の有無にかかわらず、この欄に「↴」を表示する
							*/
							strText = m_nameRelease;
						}
						else if (aCustomizeJikokuhyouContent.iReleaseEkiOrder < iEkiOrder &&
							aCustomizeJikokuhyouContent.iReleaseEkiOrder >= 0)
						{
							strText = m_nameKeiyunasi;
						}
					}
					else if (iEkiOrder == iValidSihatsuEki)
					{
						if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0)
						{
							/**
								路線外始発の場合、当駅着時刻の設定の有無で変化します
								設定あり：停車・運転停車とみなします。従来通りの処理です。
								設定なし：駅扱い通過の場合は通過とみなします。路線外始発以外の作業は全て無効扱いになります
									通過をみなしているときは、当駅着時刻部は経由無し表記にします
										Ver2.06.04 修正　当駅に発時刻欄がない場合は、着時刻欄に発時刻(通過時刻)を表示します
									駅扱い停車の場合は、着時刻欄は経由無し表記にします。
							*/
							if (pCentDedRessya->getFirstOperation().getChakuJikoku().isNull() ||
								aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka &&
								!bDisplayTsuukaEkiJikoku)
							{
								if (aCdDedEki.getJikokuhyouHatsuJikokuDisplay())
								{
									strText = m_nameKeiyunasi;
								}
								else
								{
									aCdDedJikoku = aCentDedEkiJikoku.getHatsujikoku();
									strText = encode_Ekijikoku(
										CentDedEkiJikoku::Ekiatsukai_Tsuuka,
										aCdDedJikoku,
										bDisplaySecondEkiJikoku,
										bDisplayColonEkiJikoku,
										iSecondRoundChaku,
										iSecondRoundHatsu,
										bDisplay2400,
										false);
								}
							}
							else
							{
								/**
									秒単位表示OFFの場合は、切り上げ・切り捨ての処理を行いますが、
									その補助のため、着時刻が切り上げで、発時刻が30秒以上切り上げまたは切り捨ての場合は、発時刻の取得を行います。
								*/
								CdDedJikoku aHatsuJikoku;
								if (!bDisplaySecondEkiJikoku &&
									iSecondRoundChaku == 2 &&
									iSecondRoundHatsu <= 1)
								{
									aHatsuJikoku = aCentDedEkiJikoku.getVirtualHatsujikoku();
								}

								strText = encode_Ekijikoku(
									aCentDedEkiJikoku.getEkiatsukai(),
									pCentDedRessya->getFirstOperation().getChakuJikoku(),
									bDisplaySecondEkiJikoku,
									bDisplayColonEkiJikoku,
									iSecondRoundChaku,
									iSecondRoundHatsu,
									bDisplay2400,
									true,
									aHatsuJikoku);
							}
						}
						else if (aCustomizeJikokuhyouContent.iSihatsuEkiOrder >= -2 &&
							iRessyaIndexContIndex == 0 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0)
						{
							//路線外始発相当
							if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka &&
								!bDisplayTsuukaEkiJikoku)
							{
								strText = m_nameKeiyunasi;
							}
							else
							{
								/**
									秒単位表示OFFの場合は、切り上げ・切り捨ての処理を行いますが、
									その補助のため、着時刻が切り上げで、発時刻が30秒以上切り上げまたは切り捨ての場合は、発時刻の取得を行います。
								*/
								CdDedJikoku aHatsuJikoku;
								if (!bDisplaySecondEkiJikoku &&
									iSecondRoundChaku == 2 &&
									iSecondRoundHatsu <= 1)
								{
									aHatsuJikoku = aCentDedEkiJikoku.getVirtualHatsujikoku();
								}

								strText = encode_Ekijikoku(
									aCentDedEkiJikoku.getEkiatsukai(),
									aCustomizeJikokuhyouContent.ChakuJikoku,
									bDisplaySecondEkiJikoku,
									bDisplayColonEkiJikoku,
									iSecondRoundChaku,
									iSecondRoundHatsu,
									bDisplay2400,
									true,
									aHatsuJikoku);
							}
						}
						else if (iCurrentRessyaShihatsuEkiOrder >= 0 &&
							iCurrentRessyaShihatsuEkiOrder < iEkiOrder)
						{
							/**
								この列車が2列車目以降かつ、前列車の終着駅との間に経由なし区間がある場合、
								当駅に着時刻が設定されている場合は、この項に前列車の終着駅着時刻を表示します。
								されていない場合、この駅の発時刻表示が無い場合は、この項に発時刻を表示し、ある場合は経由なし表示とします。
							*/
							if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka &&
								!bDisplayTsuukaEkiJikoku)
							{
								//運転停車かつ通過駅時刻非表示の場合、発時刻表示が無い場合はレ印を、ある場合は経由なし表示とします。
								if (aCdDedEki.getJikokuhyouHatsuJikokuDisplay())
								{
									strText = m_nameKeiyunasi;
								}
								else//if(!aCdDedEki.getJikokuhyouHatsuJikokuDisplay())
								{
									strText = m_nameTsuuka;
								}
							}
							else if (!aCdDedJikoku.isNull())
							{
								const CentDedRessya* pPrevRessya =
									pCentDedRessyaCont->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex - 1]);
								CdDedJikoku aChakuJikoku = pPrevRessya->getCentDedEkiJikoku(pPrevRessya->getValidSyuuchakuEki()).getVirtualChakujikoku();

								/**
									秒単位表示OFFの場合は、切り上げ・切り捨ての処理を行いますが、
									その補助のため、着時刻が切り上げで、発時刻が30秒以上切り上げまたは切り捨ての場合、発時刻の取得を行います。(着時刻表示時)
								*/
								CdDedJikoku aHatsuJikoku;
								if (!bDisplaySecondEkiJikoku &&
									iSecondRoundChaku == 2 &&
									iSecondRoundHatsu <= 1)
								{
									aHatsuJikoku = aCentDedEkiJikoku.getVirtualHatsujikoku();
								}

								strText = encode_Ekijikoku(
									aCentDedEkiJikoku.getEkiatsukai(),
									aChakuJikoku,
									bDisplaySecondEkiJikoku,
									bDisplayColonEkiJikoku,
									iSecondRoundChaku,
									iSecondRoundHatsu,
									bDisplay2400,
									true,
									aHatsuJikoku);
							}
							else if (aCdDedEki.getJikokuhyouHatsuJikokuDisplay())
							{
								strText = m_nameKeiyunasi;
							}
							else//if(!aCdDedEki.getJikokuhyouHatsuJikokuDisplay())
							{
								/**
									秒単位表示OFFの場合は、切り上げ・切り捨ての処理を行いますが、
									その補助のため、着時刻が30秒以上切り上げまたは切り上げで、発時刻が切り捨ての場合、
									前列車の終着駅着時刻の取得を行います。(発時刻表示)
								*/
								CdDedJikoku aChakuJikoku;
								if (!bDisplaySecondEkiJikoku &&
									iSecondRoundChaku >= 1 &&
									iSecondRoundHatsu == 0)
								{
									const CentDedRessya* pPrevRessya =
										pCentDedRessyaCont->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex - 1]);
									aChakuJikoku = pPrevRessya->getCentDedEkiJikoku(pPrevRessya->getValidSyuuchakuEki()).getVirtualChakujikoku();
								}
								CdDedJikoku aHatsuJikoku = aCentDedEkiJikoku.getVirtualHatsujikoku();
								strText = encode_Ekijikoku(
									aCentDedEkiJikoku.getEkiatsukai(),
									aHatsuJikoku,
									bDisplaySecondEkiJikoku,
									bDisplayColonEkiJikoku,
									iSecondRoundChaku,
									iSecondRoundHatsu,
									bDisplay2400,
									false,
									aChakuJikoku);
							}
						}
						else if (aCustomizeJikokuhyouContent.iReleaseEkiOrder >= 0 &&
							aCustomizeJikokuhyouContent.iReleaseEkiOrder < iEkiOrder &&
							aCdDedEki.getJikokuhyouHatsuJikokuDisplay())
						{
							/**
								Ver2.06.03 修正
								始発駅だが、分割駅が前にある場合、この項には||を表示する、
								ただし、発時刻表示が無い場合は、発時刻を優先する。
							*/
							strText = m_nameKeiyunasi;
							}
						else if (aCustomizeJikokuhyouContent.iReleaseEkiOrder == iEkiOrder/* &&
							aCdDedEki.getJikokuhyouHatsuJikokuDisplay()*/)
						{
							/**
								発時刻表示の有無で変わる
								発時刻表示がある場合は、この欄に「↴」を表示する
								発時刻表示がない場合は、この欄には、発時刻を入れ、一つ上の欄に、表示を行う。
								Ver2.05 発時刻表示が無くても、この欄には常に「↴」を表示する
							*/
							strText = m_nameRelease;
						}
						//この駅が着時刻のみ表示の場合は、着時刻欄に発時刻を表示する
						else if (!aCdDedEki.getJikokuhyouHatsuJikokuDisplay())
						{
							aCdDedJikoku = aCentDedEkiJikoku.getVirtualHatsujikoku();
							strText = encode_Ekijikoku(
								aCentDedEkiJikoku.getEkiatsukai(),
								aCdDedJikoku,
								bDisplaySecondEkiJikoku,
								bDisplayColonEkiJikoku,
								iSecondRoundChaku,
								iSecondRoundHatsu,
								bDisplay2400,
								false);
						}
					}
					//有効終着駅の場合
					else if (iEkiOrder == iValidSyuuchakuEki)
					{
						/**
							基本的に着時刻を表示、先に続く場合(路線外終着・路線外終着相当・複数列車表示の最終列車以外)は発時刻を取得し秒単位処理に用いる
							通過駅時刻非表示の場合、先に続く場合
						*/
						if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
						{
							//路線外終着

							if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka &&
								!bDisplayTsuukaEkiJikoku &&
								m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0)
							{
								//路線外表示スペースがない場合は、レ印ではなく時刻を表示する。
								strText = m_nameTsuuka;
							}
							else
							{
								CdDedJikoku aHatsuJikoku = pCentDedRessya->getLastOperation().getHatsuJikoku();
								//当駅発時刻を確認、時刻がない場合、駅扱い通過の時は通過とみなす(運転停車ではない)
								if (!aHatsuJikoku.isNull())
								{
									aCdDedJikoku = aCentDedEkiJikoku.getVirtualChakujikoku();
								}

								strText = encode_Ekijikoku(
									aCentDedEkiJikoku.getEkiatsukai(),
									aCdDedJikoku,
									bDisplaySecondEkiJikoku,
									bDisplayColonEkiJikoku,
									iSecondRoundChaku,
									iSecondRoundHatsu,
									bDisplay2400,
									true,
									aHatsuJikoku);
							}
						}
						else if (iRessyaIndexContIndex == aCustomizeJikokuhyouContent.iRessyaIndexCont.size() - 1 &&
							aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder >= -2)
						{
							//路線外終着相当
							if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka &&
								!bDisplayTsuukaEkiJikoku &&
								m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0)
							{
								//路線外表示スペースがない場合は、レ印ではなく時刻を表示する。
								strText = m_nameTsuuka;
							}
							else
							{
								CdDedJikoku aHatsuJikoku = aCustomizeJikokuhyouContent.HatsuJikoku;
								aCdDedJikoku = aCentDedEkiJikoku.getVirtualChakujikoku();

								strText = encode_Ekijikoku(
									aCentDedEkiJikoku.getEkiatsukai(),
									aCdDedJikoku,
									bDisplaySecondEkiJikoku,
									bDisplayColonEkiJikoku,
									iSecondRoundChaku,
									iSecondRoundHatsu,
									bDisplay2400,
									true,
									aHatsuJikoku);
							}
						}
						else if (iRessyaIndexContIndex < (int)aCustomizeJikokuhyouContent.iRessyaIndexCont.size() - 1)
						{
							//次列車あり
							if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka &&
								!bDisplayTsuukaEkiJikoku)
							{
								strText = m_nameTsuuka;
							}
							else
							{
								/**
									秒単位表示OFFの場合は、切り上げ・切り捨ての処理を行いますが、
									その補助のため、着時刻が切り上げで、発時刻が30秒以上切り上げまたは切り捨ての場合、
									次列車の始発駅発時刻の取得を行います。(着時刻表示時)
								*/
								CdDedJikoku aHatsuJikoku;
								if (!bDisplaySecondEkiJikoku &&
									iSecondRoundChaku == 2 &&
									iSecondRoundHatsu <= 1)
								{
									const CentDedRessya* pNextRessya =
										pCentDedRessyaCont->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex + 1]);
									aHatsuJikoku = pNextRessya->getCentDedEkiJikoku(pNextRessya->getValidSihatsuEki()).getVirtualHatsujikoku();
								}
								aCdDedJikoku = aCentDedEkiJikoku.getVirtualChakujikoku();

								strText = encode_Ekijikoku(
									aCentDedEkiJikoku.getEkiatsukai(),
									aCdDedJikoku,
									bDisplaySecondEkiJikoku,
									bDisplayColonEkiJikoku,
									iSecondRoundChaku,
									iSecondRoundHatsu,
									bDisplay2400,
									true,
									aHatsuJikoku);
							}

						}
						else
						{
							aCdDedJikoku = aCentDedEkiJikoku.getVirtualChakujikoku();

							strText = encode_Ekijikoku(
								aCentDedEkiJikoku.getEkiatsukai(),
								aCdDedJikoku,
								bDisplaySecondEkiJikoku,
								bDisplayColonEkiJikoku,
								iSecondRoundChaku,
								iSecondRoundHatsu,
								bDisplay2400,
								true);
						}
					}
					else if (iEkiOrder > iValidSyuuchakuEki)
					{
						if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= iEkiOrder)
						{
							//路線外終着
							strText = m_nameKeiyunasi;

						}
						else if (aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder >= -2 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= iEkiOrder)
						{
							//路線外終着相当
							strText = m_nameKeiyunasi;

						}
						else if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= iEkiOrder &&
							aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
						{
							if (aCustomizeJikokuhyouContent.iConnectEkiOrder == iEkiOrder &&
								!aCdDedEki.getJikokuhyouHatsuJikokuDisplay())
							{
								strText = m_nameConnect;
							}
							else
							{
								strText = m_nameKeiyunasi;
							}
						}
						//csv出力では、終着駅下の"===="は表示しません
					}
					//中間駅の場合
					else
					{
						if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_None)
						{
							strText = m_nameKeiyunasi;
						}
						else if (pCentDedRessya->isRunBetweenNextEki(iEkiOrder - 1))
						{
							if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka &&
								!bDisplayTsuukaEkiJikoku)
							{
								strText = m_nameTsuuka;
							}
							else if (aCdDedJikoku.isNull())
							{
								//着時刻がない場合、この駅と次の駅の間が運行ありの場合は、通過の場合はレ印、停車の場合は発時刻または○印を表示します
								if (pCentDedRessya->isRunBetweenNextEki(iEkiOrder))
								{
									if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
									{
										strText = m_nameTsuuka;
									}
									else if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya)
									{
										CdDedJikoku aHatsuJikoku = aCentDedEkiJikoku.getVirtualHatsujikoku();
										if (!aHatsuJikoku.isNull() &&
											!aCdDedEki.getJikokuhyouHatsuJikokuDisplay())
										{
											//	時刻が設定されているかつ発時刻表示が無い場合は時刻を表示
											strText = encode_Ekijikoku(
												CentDedEkiJikoku::Ekiatsukai_Teisya,
												aHatsuJikoku,
												bDisplaySecondEkiJikoku,
												bDisplayColonEkiJikoku,
												iSecondRoundChaku,
												iSecondRoundHatsu,
												bDisplay2400,
												false);
										}
										//csv出力では○印表示なし
									}
								}
								//この駅と次の駅の間が運行なしの場合は、終点側発時刻を取得し時刻表示を行う、ない場合はレ印または○印
								else//if(!pCentDedRessya->isRunBetweenNextEki(iEkiOrder))
								{
									CdDedJikoku aHatsuJikoku;
									int iHatsuEkiOrder = pCentDedRessya->getRunBetweenEkiForward(iEkiOrder);
									if (pCentDedEkiCont->isSameBrunchLoopGroup(iEkiOrder, iHatsuEkiOrder, pCentDedRessya->getRessyahoukou()))
									{
										aHatsuJikoku = pCentDedRessya->getCentDedEkiJikoku(iHatsuEkiOrder).getVirtualHatsujikoku();
									}
									if (!aHatsuJikoku.isNull())
									{
										strText = encode_Ekijikoku(
											aCentDedEkiJikoku.getEkiatsukai(),
											aHatsuJikoku,
											bDisplaySecondEkiJikoku,
											bDisplayColonEkiJikoku,
											iSecondRoundChaku,
											iSecondRoundHatsu,
											bDisplay2400,
											false);
									}
									else//if (aHatsuJikoku.isNull())
									{
										if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
										{
											strText = m_nameTsuuka;
										}
										//csv出力では○印表示なし
									}
								}
							}
							else //if (!aCdDedJikoku.isNull())
							{
								//着時刻がある場合は、通過を考慮せず、Virtual着時刻を取得して表示する。(編集段階でのadjustを信用する)
								aCdDedJikoku = aCentDedEkiJikoku.getVirtualChakujikoku();

								/**
									秒単位表示OFFの場合は、切り上げ・切り捨ての処理を行いますが、
									その補助のため、着時刻が切り上げで、発時刻が30秒以上切り上げまたは切り捨ての場合、発時刻の取得を行います。(着時刻表示時)
									この駅と次の駅の間が運行なしの場合は、運行なしを超えた先の駅から時刻を取得します。
								*/
								CdDedJikoku aHatsuJikoku;
								if (!bDisplaySecondEkiJikoku &&
									iSecondRoundChaku == 2 &&
									iSecondRoundHatsu <= 1)
								{
									if (pCentDedRessya->isRunBetweenNextEki(iEkiOrder))
									{
										aHatsuJikoku = aCentDedEkiJikoku.getVirtualHatsujikoku();
									}
									else
									{
										int iHatsuEkiOrder = pCentDedRessya->getRunBetweenEkiForward(iEkiOrder);
										if (pCentDedEkiCont->isSameBrunchLoopGroup(iEkiOrder, iHatsuEkiOrder, pCentDedRessya->getRessyahoukou()))
										{
											aHatsuJikoku = pCentDedRessya->getCentDedEkiJikoku(iHatsuEkiOrder).getVirtualHatsujikoku();
										}

									}
								}

								strText = encode_Ekijikoku(
									aCentDedEkiJikoku.getEkiatsukai(),
									aCdDedJikoku,
									bDisplaySecondEkiJikoku,
									bDisplayColonEkiJikoku,
									iSecondRoundChaku,
									iSecondRoundHatsu,
									bDisplay2400,
									true,
									aHatsuJikoku);
							}
						}
						else if (pCentDedRessya->isRunBetweenNextEki(iEkiOrder))
						{
							//この駅と前の駅の間が運行なし、この駅と次の駅の間が運行ありの場合
							if (aCdDedEki.getJikokuhyouHatsuJikokuDisplay())
							{
								//この駅が発着表示の場合、基本的には経由なし表示になります。
								//ただし、この駅に発着両時刻が設定されている場合、起点側着時刻を取得して表示します
								if (aCdDedJikoku.isNull() || aCentDedEkiJikoku.getHatsujikoku().isNull())
								{
									strText = m_nameKeiyunasi;
								}
								else//if (!aCdDedJikoku.isNull() &&!aCentDedEkiJikoku.getHatsujikoku().isNull())
								{
									CdDedJikoku aChakuJikoku;
									int iChakuEkiOrder = pCentDedRessya->getRunBetweenEkiBackward(iEkiOrder);
									if (pCentDedEkiCont->isSameBrunchLoopGroup(iEkiOrder, iChakuEkiOrder, pCentDedRessya->getRessyahoukou()))
									{
										aChakuJikoku = pCentDedRessya->getCentDedEkiJikoku(iChakuEkiOrder).getVirtualChakujikoku();
									}
									/**
										秒単位表示OFFの場合は、切り上げ・切り捨ての処理を行いますが、
										その補助のため、着時刻が切り上げで、発時刻が30秒以上切り上げまたは切り捨ての場合、発時刻の取得を行います。(着時刻表示時)
									*/
									CdDedJikoku aHatsuJikoku;
									if (!bDisplaySecondEkiJikoku &&
										iSecondRoundChaku == 2 &&
										iSecondRoundHatsu <= 1)
									{
										aHatsuJikoku = aCentDedEkiJikoku.getVirtualHatsujikoku();
									}

									if (aChakuJikoku.isNull())
									{
										strText = m_nameKeiyunasi;
									}
									else
									{
										strText = encode_Ekijikoku(
											aCentDedEkiJikoku.getEkiatsukai(),
											aChakuJikoku,
											bDisplaySecondEkiJikoku,
											bDisplayColonEkiJikoku,
											iSecondRoundChaku,
											iSecondRoundHatsu,
											bDisplay2400,
											true,
											aHatsuJikoku);
									}
								}
							}
							else//if (!aCdDedEki.getJikokuhyouHatsuJikokuDisplay())
							{
								//この駅が着時刻のみ表示の場合、当駅発時刻がある場合はそれを表示し、ない場合は起点方着時刻を取得して表示する。
								//ただし、着時刻が設定されている場合は、起点方着時刻を優先する。
								CdDedJikoku aHatsuJikoku = aCentDedEkiJikoku.getVirtualHatsujikoku();
								if (aHatsuJikoku.isNull())
								{
									//当駅発時刻がない場合は、起点方着時刻を取得して表示する。
									CdDedJikoku aChakuJikoku;
									int iChakuEkiOrder = pCentDedRessya->getRunBetweenEkiBackward(iEkiOrder);
									if (pCentDedEkiCont->isSameBrunchLoopGroup(iEkiOrder, iChakuEkiOrder, pCentDedRessya->getRessyahoukou()))
									{
										aChakuJikoku = pCentDedRessya->getCentDedEkiJikoku(iChakuEkiOrder).getVirtualChakujikoku();
									}

									if (!aChakuJikoku.isNull())
									{
										strText = encode_Ekijikoku(
											aCentDedEkiJikoku.getEkiatsukai(),
											aChakuJikoku,
											bDisplaySecondEkiJikoku,
											bDisplayColonEkiJikoku,
											iSecondRoundChaku,
											iSecondRoundHatsu,
											bDisplay2400,
											true);
									}
									else//if (aChakuJikoku.isNull())
									{
										if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
										{
											strText = m_nameTsuuka;
										}
										//csv出力では○印表示なし
									}
								}
								else if (aCdDedJikoku.isNull())
								{
									//発時刻あり・着時刻なしの場合は、発時刻を表示します。ただし、起点方着時刻を取得し、秒単位処理に用います。

									/**
										秒単位表示OFFの場合は、切り上げ・切り捨ての処理を行いますが、
										その補助のため、着時刻が30秒以上切り上げまたは切り上げで、発時刻が切り捨ての場合、(発時刻表示時)
										着時刻の取得を行います。
										この駅と前の駅の間が運行なしの場合は、運行なしを超えた先の駅から時刻を取得します。
									*/
									CdDedJikoku aChakuJikoku;
									if (!bDisplaySecondEkiJikoku &&
										iSecondRoundChaku >= 1 &&
										iSecondRoundHatsu == 0)
									{
										int iChakuEkiOrder = pCentDedRessya->getRunBetweenEkiBackward(iEkiOrder);
										if (pCentDedEkiCont->isSameBrunchLoopGroup(iEkiOrder, iChakuEkiOrder, pCentDedRessya->getRessyahoukou()))
										{
											aChakuJikoku = pCentDedRessya->getCentDedEkiJikoku(iChakuEkiOrder).getVirtualChakujikoku();
										}
									}

									strText = encode_Ekijikoku(
										aCentDedEkiJikoku.getEkiatsukai(),
										aHatsuJikoku,
										bDisplaySecondEkiJikoku,
										bDisplayColonEkiJikoku,
										iSecondRoundChaku,
										iSecondRoundHatsu,
										bDisplay2400,
										false,
										aChakuJikoku);
								}
								else// if (!aCdDedJikoku.isNull())
								{
									//発時刻・着時刻ともにある場合は、起点方着時刻の取得を試み、ある場合はそれを表示、ない場合は発時刻を表示します。
									CdDedJikoku aChakuJikoku;
									int iChakuEkiOrder = pCentDedRessya->getRunBetweenEkiBackward(iEkiOrder);
									if (pCentDedEkiCont->isSameBrunchLoopGroup(iEkiOrder, iChakuEkiOrder, pCentDedRessya->getRessyahoukou()))
									{
										aChakuJikoku = pCentDedRessya->getCentDedEkiJikoku(iChakuEkiOrder).getVirtualChakujikoku();
									}
									if (!aChakuJikoku.isNull())
									{
										strText = encode_Ekijikoku(
											aCentDedEkiJikoku.getEkiatsukai(),
											aChakuJikoku,
											bDisplaySecondEkiJikoku,
											bDisplayColonEkiJikoku,
											iSecondRoundChaku,
											iSecondRoundHatsu,
											bDisplay2400,
											true,
											aHatsuJikoku);
									}
									else// (aChakuJikoku.isNull())
									{
										strText = encode_Ekijikoku(
											aCentDedEkiJikoku.getEkiatsukai(),
											aHatsuJikoku,
											bDisplaySecondEkiJikoku,
											bDisplayColonEkiJikoku,
											iSecondRoundChaku,
											iSecondRoundHatsu,
											bDisplay2400,
											false);
									}
								}
							}
						}
						else//if (!pCentDedRessya->isRunBetweenNextEki(iEkiOrder-1)&&!pCentDedRessya->isRunBetweenNextEki(iEkiOrder))
						{
							//この駅の前後ともに運行なし(経由なし)の場合、この項は経由なし表示となります。
							strText = m_nameKeiyunasi;
						}
					}

					/**
						次駅が解結駅の場合、この欄に↴印を表示することがあります
						(1)次駅が解結駅かつ有効な始発駅
						(2)次駅が着時刻又は発時刻のどちらかのみ表示→Ver2.05 次駅が発時刻のみ表示の場合のみに変更
						(3)この欄の直下が、次駅の項な場合。
					*/
					if (iEkiOrder + 1 == iValidSihatsuEki &&
						iEkiOrder + 1 == aCustomizeJikokuhyouContent.iReleaseEkiOrder)
					{
						CentDedEkiCont::CdDedEki aCdDedEkiNext = muCdDedEki->get(iEkiOrder + 1);
						//現在の仕様では、着時刻非表示の時は必ず発時刻表示だが、念のため
						if (!aCdDedEkiNext.getJikokuhyouChakuJikokuDisplay() &&
							aCdDedEkiNext.getJikokuhyouHatsuJikokuDisplay())
						{
							int iYColumnNumberNext = iYColumnNumber + 1;
							CdYColSpec aCdYColSpecNext = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberNext);
							if (aCdYColSpecNext.getEkiOrder() == iEkiOrder + 1)
							{
								strText = m_nameRelease;
							}
						}
					}
					/**
						前駅が増結駅の場合、この欄に↳印を表示することがあります
						(1)前駅が増結駅かつ有効な終着駅
						(2)前駅が着時刻又は発時刻のどちらかのみ表示→Ver2.05 前駅が着時刻のみ表示の場合のみに変更
						(3)この欄の直上が、前駅の項な場合。
					*/
					if (iEkiOrder - 1 == iValidSyuuchakuEki &&
						iEkiOrder - 1 == aCustomizeJikokuhyouContent.iConnectEkiOrder &&
						iValidSyuuchakuEki != -1)
					{
						CentDedEkiCont::CdDedEki aCdDedEkiPrev = muCdDedEki->get(iEkiOrder - 1);
						if (aCdDedEkiPrev.getJikokuhyouChakuJikokuDisplay() &&
							!aCdDedEkiPrev.getJikokuhyouHatsuJikokuDisplay())
						{
							int iYColumnNumberPrev = iYColumnNumber - 1;
							CdYColSpec aCdYColSpecPrev = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberPrev);
							if (aCdYColSpecPrev.getEkiOrder() == iEkiOrder - 1)
							{
								strText = m_nameConnect;
							}
						}
					}
				}

				CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
				aRow.getCellCont()->insert(CdCsvCell(strText));
				pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
				iRowIndex++;
			}
			else if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_Ekijikoku_Hatsu)
			{
				tstring	strText;

				if (pCentDedRessya == NULL)
				{
					/**
						pCentDedRessya == NULLの場合は、
						分割+路線外終着または路線外始発+増結のどちらかのパターンです。
						なお、分割駅に対応する路線外終着表示欄、もしくは解結駅に対応する路線外始発表示欄がない場合は、この列車の描写は行わず、空行となります。
					*/
					if (aCustomizeJikokuhyouContent.iReleaseEkiOrder >= 0)
					{
						/**
							分割+路線外終着の場合、
							分割駅ならば当駅発時刻を表示します。
							分割駅より後かつ、路線外終着表示駅までの場合は、経由なしを表示します。
							分割駅より一つ上の駅の場合、分割駅が発時刻のみ表示で、この項が分割駅の項の直上なら、ここで↴を表示します。
							それ以外の場合は、----もしくは・・を表示します
						*/
						if (iEkiOrder + 1 == aCustomizeJikokuhyouContent.iReleaseEkiOrder)
						{
							CentDedEkiCont::CdDedEki aCdDedEkiNext = muCdDedEki->get(iEkiOrder + 1);
							if (!aCdDedEkiNext.getJikokuhyouChakuJikokuDisplay() &&
								aCdDedEkiNext.getJikokuhyouHatsuJikokuDisplay())
							{
								int iYColumnNumberNext = iYColumnNumber + 1;
								CdYColSpec aCdYColSpecNext = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberNext);
								if (aCdYColSpecNext.getEkiOrder() == iEkiOrder + 1)
								{
									strText = m_nameRelease;
								}
							}
						}
						else if (iEkiOrder == aCustomizeJikokuhyouContent.iReleaseEkiOrder)
						{
							strText = encode_Ekijikoku(
								aCustomizeJikokuhyouContent.eEkiatsukai,
								aCustomizeJikokuhyouContent.HatsuJikoku,
								bDisplaySecondEkiJikoku,
								bDisplayColonEkiJikoku,
								iSecondRoundChaku,
								iSecondRoundHatsu,
								bDisplay2400,
								false);
						}
						else if (iEkiOrder > aCustomizeJikokuhyouContent.iReleaseEkiOrder &&
							iEkiOrder <= m_iOuterShuchakuDisplayEkiOrder[aCustomizeJikokuhyouContent.iReleaseEkiOrder])
						{
							strText = m_nameKeiyunasi;

						}
					}
					else if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
					{
						/**
							路線外始発+併合の場合
							併合駅ならば↳を表示します。(当駅着時刻の表示は無しに)
							路線外始発表示駅から併合駅の前までなら、経由なしを表示します。
							併合駅の次の駅の場合、併合駅が着時刻のみ表示かつ、この項が併合駅の直下なら、この項に↳を表示します。
							それ以外の場合は、----もしくは・・を表示します
						*/
						if (iEkiOrder - 1 == aCustomizeJikokuhyouContent.iConnectEkiOrder)
						{
							CentDedEkiCont::CdDedEki aCdDedEkiPrev = muCdDedEki->get(iEkiOrder - 1);
							if (aCdDedEkiPrev.getJikokuhyouChakuJikokuDisplay() &&
								!aCdDedEkiPrev.getJikokuhyouHatsuJikokuDisplay())
							{
								int iYColumnNumberPrev = iYColumnNumber - 1;
								CdYColSpec aCdYColSpecPrev = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberPrev);
								if (aCdYColSpecPrev.getEkiOrder() == iEkiOrder - 1)
								{
									strText = m_nameConnect;
								}
							}
						}
						else if (iEkiOrder == aCustomizeJikokuhyouContent.iConnectEkiOrder)
						{
							strText = m_nameConnect;
						}
						else if (iEkiOrder >= m_iOuterShihatsuDisplayEkiOrder[aCustomizeJikokuhyouContent.iConnectEkiOrder] &&
							iEkiOrder < aCustomizeJikokuhyouContent.iConnectEkiOrder)
						{
							strText = m_nameKeiyunasi;
						}
					}
				}
				else
				{
					CentDedEkiJikoku	aCentDedEkiJikoku =
						pCentDedRessya->getCentDedEkiJikoku(iEkiOrder);
					CdDedJikoku aCdDedJikoku
						= aCentDedEkiJikoku.getHatsujikoku();

					// --------------------------------
					//	駅時刻に合わせて、セルに文字を表示
					// --------------------------------
					int iValidSihatsuEki = pCentDedRessya->getValidSihatsuEki();
					int iValidSyuuchakuEki = pCentDedRessya->getValidSyuuchakuEki();
					if (iValidSihatsuEki == -1 || iValidSyuuchakuEki == -1)
					{
						//空白のまま
					}
					else if (iEkiOrder < iValidSihatsuEki)
					{
						if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] <= iEkiOrder)
						{
							//路線外始発
							strText = m_nameKeiyunasi;

						}
						else if (aCustomizeJikokuhyouContent.iSihatsuEkiOrder >= -2 &&
							iRessyaIndexContIndex == 0 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] <= iEkiOrder)
						{
							//路線外始発相当
							strText = m_nameKeiyunasi;
						}
						else if (iCurrentRessyaShihatsuEkiOrder >= 0)
						{
							/**
								複数列車表示で、列車間に経由なし区間がある場合
								前列車終着駅(この列車の最初の"描写"駅の場合は、"前列車の終着駅"に発時刻が設定されている場合は、この項に"この列車の始発駅の"発時刻を描写します
								設定されていない場合は、この駅に着時刻欄がない場合は、この項に前列車の終着駅着時刻を表示します、ある場合は経由なし表示とします。
							*/
							if (iCurrentRessyaShihatsuEkiOrder == iEkiOrder)
							{
								const CentDedRessya* pPrevRessya =
									pCentDedRessyaCont->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex - 1]);
								const CentDedEkiJikoku aSyuuchakuEkiJikoku = pPrevRessya->getCentDedEkiJikoku(pPrevRessya->getValidSyuuchakuEki());
								if (aSyuuchakuEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka &&
									!bDisplayTsuukaEkiJikoku)
								{
									//運転停車かつ通過駅時刻非表示の場合、着時刻表示が無い場合はレ印を、ある場合は経由なし表示とします。
									if (aCdDedEki.getJikokuhyouChakuJikokuDisplay())
									{
										strText = m_nameKeiyunasi;
									}
									else//if(!aCdDedEki.getJikokuhyouChakuJikokuDisplay())
									{
										strText = m_nameTsuuka;
									}
								}
								else
								{
									CdDedJikoku aHatsuJikoku = aSyuuchakuEkiJikoku.getHatsujikoku();
									if (!aHatsuJikoku.isNull())
									{
										//この列車の始発駅発時刻を表示します。
									/**
										秒単位表示OFFの場合は、切り上げ・切り捨ての処理を行いますが、
										その補助のため、着時刻が30秒以上切り上げまたは切り上げで、発時刻が切り捨ての場合、
										前列車の終着駅着時刻の取得を行います。(発時刻表示)
									*/
										CdDedJikoku aChakuJikoku;
										if (!bDisplaySecondEkiJikoku &&
											iSecondRoundChaku >= 1 &&
											iSecondRoundHatsu == 0)
										{
											aChakuJikoku = pPrevRessya->getCentDedEkiJikoku(pPrevRessya->getValidSyuuchakuEki()).getVirtualChakujikoku();
										}
										CdDedJikoku aHatsuJikoku = pCentDedRessya->getCentDedEkiJikoku(iValidSihatsuEki).getVirtualHatsujikoku();

										strText = encode_Ekijikoku(
											aSyuuchakuEkiJikoku.getEkiatsukai(),
											aHatsuJikoku,
											bDisplaySecondEkiJikoku,
											bDisplayColonEkiJikoku,
											iSecondRoundChaku,
											iSecondRoundHatsu,
											bDisplay2400,
											false,
											aChakuJikoku);
									}
									else if (aCdDedEki.getJikokuhyouChakuJikokuDisplay())
									{
										strText = m_nameKeiyunasi;
									}
									else// if (!aCdDedEki.getJikokuhyouChakuJikokuDisplay())
									{
										//前列車の終着駅着時刻を表示します。
										CdDedJikoku aChakuJikoku = aSyuuchakuEkiJikoku.getVirtualChakujikoku();

										/**
											秒単位表示OFFの場合は、切り上げ・切り捨ての処理を行いますが、
											その補助のため、着時刻が切り上げで、発時刻が30秒以上切り上げまたは切り捨ての場合、始発駅発時刻の取得を行います。(着時刻表示時)
										*/
										CdDedJikoku aHatsuJikoku;
										if (!bDisplaySecondEkiJikoku &&
											iSecondRoundChaku == 2 &&
											iSecondRoundHatsu <= 1)
										{
											aHatsuJikoku = pCentDedRessya->getCentDedEkiJikoku(iValidSihatsuEki).getVirtualHatsujikoku();
										}

										strText = encode_Ekijikoku(
											aSyuuchakuEkiJikoku.getEkiatsukai(),
											aChakuJikoku,
											bDisplaySecondEkiJikoku,
											bDisplayColonEkiJikoku,
											iSecondRoundChaku,
											iSecondRoundHatsu,
											bDisplay2400,
											true,
											aHatsuJikoku);
									}
								}
							}
							else
							{
								strText = m_nameKeiyunasi;
							}
						}
						else if (aCustomizeJikokuhyouContent.iReleaseEkiOrder <= iEkiOrder &&
							aCustomizeJikokuhyouContent.iReleaseEkiOrder >= 0)
						{
							/**
								解結駅かつ、着時刻表示がない場合は、発時刻欄に↴を表示する。
							*/
							if (iEkiOrder == aCustomizeJikokuhyouContent.iReleaseEkiOrder &&
								!aCdDedEki.getJikokuhyouChakuJikokuDisplay())
							{
								strText = m_nameRelease;
							}
							else
							{
								strText = m_nameKeiyunasi;
							}
						}
					}
					//有効始発駅の場合
					else if (iEkiOrder == iValidSihatsuEki)
					{
						if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
						{
							//路線外始発
							if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka &&
								!bDisplayTsuukaEkiJikoku &&
								m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0)
							{
								//路線外表示スペースがない場合は、レ印ではなく時刻を表示する。
								strText = m_nameTsuuka;
							}
							else
							{
								CdDedJikoku aChakuJikoku = pCentDedRessya->getFirstOperation().getChakuJikoku();
								//当駅着時刻を確認、時刻がない場合、駅扱い通過の時は通過とみなす(運転停車ではない)
								if (!aChakuJikoku.isNull())
								{
									aCdDedJikoku = aCentDedEkiJikoku.getVirtualHatsujikoku();
								}

								strText = encode_Ekijikoku(
									aCentDedEkiJikoku.getEkiatsukai(),
									aCdDedJikoku,
									bDisplaySecondEkiJikoku,
									bDisplayColonEkiJikoku,
									iSecondRoundChaku,
									iSecondRoundHatsu,
									bDisplay2400,
									false,
									aChakuJikoku);
							}
						}
						else if (iRessyaIndexContIndex == 0 &&
							aCustomizeJikokuhyouContent.iSihatsuEkiOrder >= -2)
						{
							//路線外始発相当
							if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka &&
								!bDisplayTsuukaEkiJikoku &&
								m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0)
							{
								//路線外表示スペースがない場合は、レ印ではなく時刻を表示する。
								strText = m_nameTsuuka;
							}
							else
							{
								CdDedJikoku aChakuJikoku = aCustomizeJikokuhyouContent.ChakuJikoku;
								aCdDedJikoku = aCentDedEkiJikoku.getVirtualHatsujikoku();

								strText = encode_Ekijikoku(
									aCentDedEkiJikoku.getEkiatsukai(),
									aCdDedJikoku,
									bDisplaySecondEkiJikoku,
									bDisplayColonEkiJikoku,
									iSecondRoundChaku,
									iSecondRoundHatsu,
									bDisplay2400,
									false,
									aChakuJikoku);
							}
						}
						else if (iRessyaIndexContIndex > 0)
						{
							//前列車あり
							if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka &&
								!bDisplayTsuukaEkiJikoku)
							{
								strText = m_nameTsuuka;
							}
							else
							{

								/**
									秒単位表示OFFの場合は、切り上げ・切り捨ての処理を行いますが、
									その補助のため、着時刻が30秒以上切り上げまたは切り上げで、発時刻が切り捨ての場合、
									前列車の終着駅着時刻の取得を行います。(発時刻表示)
								*/
								CdDedJikoku aChakuJikoku;
								if (!bDisplaySecondEkiJikoku &&
									iSecondRoundChaku >= 1 &&
									iSecondRoundHatsu == 0)
								{
									const CentDedRessya* pPrevRessya =
										pCentDedRessyaCont->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex - 1]);
									aChakuJikoku = pPrevRessya->getCentDedEkiJikoku(pPrevRessya->getValidSyuuchakuEki()).getVirtualChakujikoku();
								}
								aCdDedJikoku = aCentDedEkiJikoku.getVirtualHatsujikoku();

								strText = encode_Ekijikoku(
									aCentDedEkiJikoku.getEkiatsukai(),
									aCdDedJikoku,
									bDisplaySecondEkiJikoku,
									bDisplayColonEkiJikoku,
									iSecondRoundChaku,
									iSecondRoundHatsu,
									bDisplay2400,
									false,
									aChakuJikoku);
							}
						}
						else
						{
							aCdDedJikoku = aCentDedEkiJikoku.getVirtualHatsujikoku();

							strText = encode_Ekijikoku(
								aCentDedEkiJikoku.getEkiatsukai(),
								aCdDedJikoku,
								bDisplaySecondEkiJikoku,
								bDisplayColonEkiJikoku,
								iSecondRoundChaku,
								iSecondRoundHatsu,
								bDisplay2400,
								false);
						}
					}
					else if (iEkiOrder == iValidSyuuchakuEki)
					{
						if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0)
						{
							/**
								路線外終着の場合、当駅発時刻の設定の有無で変化します
								設定あり：停車・運転停車とみなします。従来通りの処理です。
								設定なし：駅扱い通過の場合は通過とみなします。路線外終着以外の作業は全て無効扱いになります
									通過をみなしているときは、当駅発時刻部は経由無し表記にします
										Ver2.06.04 修正　当駅に着時刻表示が無い場合は、着時刻(通過時刻)をこの欄に表示します
									駅扱い停車の場合は、着時刻欄は経由無し表記にします。
							*/
							if (pCentDedRessya->getLastOperation().getHatsuJikoku().isNull() ||
								aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka &&
								!bDisplayTsuukaEkiJikoku)
							{
								if (aCdDedEki.getJikokuhyouChakuJikokuDisplay())
								{
									strText = m_nameKeiyunasi;
								}
								else
								{
									aCdDedJikoku = aCentDedEkiJikoku.getChakujikoku();
									strText = encode_Ekijikoku(
										CentDedEkiJikoku::Ekiatsukai_Tsuuka,
										aCdDedJikoku,
										bDisplaySecondEkiJikoku,
										bDisplayColonEkiJikoku,
										iSecondRoundChaku,
										iSecondRoundHatsu,
										bDisplay2400,
										true);
								}
							}
							else
							{
								/**
									秒単位表示OFFの場合は、切り上げ・切り捨ての処理を行いますが、
									その補助のため、着時刻が切り上げまたは30秒以上切り上げで、発時刻が切り捨ての場合は、着時刻の取得を行います。
								*/
								CdDedJikoku aChakuJikoku;
								if (!bDisplaySecondEkiJikoku &&
									iSecondRoundChaku >= 1 &&
									iSecondRoundHatsu == 0)
								{
									aChakuJikoku = aCentDedEkiJikoku.getVirtualChakujikoku();
								}
								strText = encode_Ekijikoku(
									aCentDedEkiJikoku.getEkiatsukai(),
									pCentDedRessya->getLastOperation().getHatsuJikoku(),
									bDisplaySecondEkiJikoku,
									bDisplayColonEkiJikoku,
									iSecondRoundChaku,
									iSecondRoundHatsu,
									bDisplay2400,
									false,
									aChakuJikoku);
							}
						}
						else if (aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder >= -2 &&
							iRessyaIndexContIndex == aCustomizeJikokuhyouContent.iRessyaIndexCont.size() - 1 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0)
						{
							//路線外終着相当
							if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka &&
								!bDisplayTsuukaEkiJikoku)
							{
								strText = m_nameKeiyunasi;
							}
							else
							{

								/**
									秒単位表示OFFの場合は、切り上げ・切り捨ての処理を行いますが、
									その補助のため、着時刻が切り上げまたは30秒以上切り上げで、発時刻が切り捨ての場合は、着時刻の取得を行います。
								*/
								CdDedJikoku aChakuJikoku;
								if (!bDisplaySecondEkiJikoku &&
									iSecondRoundChaku >= 1 &&
									iSecondRoundHatsu == 0)
								{
									aChakuJikoku = aCentDedEkiJikoku.getVirtualChakujikoku();
								}
								strText = encode_Ekijikoku(
									aCentDedEkiJikoku.getEkiatsukai(),
									aCustomizeJikokuhyouContent.HatsuJikoku,
									bDisplaySecondEkiJikoku,
									bDisplayColonEkiJikoku,
									iSecondRoundChaku,
									iSecondRoundHatsu,
									bDisplay2400,
									false,
									aChakuJikoku);
							}
						}
						else if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0 &&
							iEkiOrder < aCustomizeJikokuhyouContent.iConnectEkiOrder &&
							aCdDedEki.getJikokuhyouChakuJikokuDisplay())
						{
							/**
								Ver2.06.03 修正
								終着駅だが、併合駅が先にある場合、この項には||を表示する
								ただし、着時刻表示が無い場合は、着時刻を優先する
							*/

							strText = m_nameKeiyunasi;
						}
						else if (iEkiOrder == aCustomizeJikokuhyouContent.iConnectEkiOrder /*&&
							aCdDedEki.getJikokuhyouChakuJikokuDisplay()*/)
						{
							/**
								着時刻表示の有無で変わる
								着時刻表示がある場合は、この欄に「↳」を表示する
								着時刻表示がない場合は、この欄には着時刻を入れ、一つ下の欄に表示を行う。
								Ver2.05 着時刻表示が無くても、常に「↳」を表示する。
							*/
							strText = m_nameConnect;
						}
						//この駅が発時刻のみ表示の場合は、発時刻欄に着時刻を表示する
						else if (!aCdDedEki.getJikokuhyouChakuJikokuDisplay())
						{
							aCdDedJikoku = aCentDedEkiJikoku.getVirtualChakujikoku();
							strText = encode_Ekijikoku(
								aCentDedEkiJikoku.getEkiatsukai(),
								aCdDedJikoku,
								bDisplaySecondEkiJikoku,
								bDisplayColonEkiJikoku,
								iSecondRoundChaku,
								iSecondRoundHatsu,
								bDisplay2400,
								true);
						}
					}
					else if (iEkiOrder > iValidSyuuchakuEki)
					{
						if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= iEkiOrder)
						{
							//路線外終着
							strText = m_nameKeiyunasi;

						}
						else if (aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder >= -2 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= iEkiOrder)
						{
							//路線外終着相当
							strText = m_nameKeiyunasi;

						}
						else if (aCustomizeJikokuhyouContent.iConnectEkiOrder > iEkiOrder &&
							aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
						{
							strText = m_nameKeiyunasi;
						}
						else if (aCustomizeJikokuhyouContent.iConnectEkiOrder == iEkiOrder)
						{
							strText = m_nameConnect;
						}
						//csv出力では"===="表示なし
					}
					//中間駅の場合
					else
					{
						if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_None)
						{
							strText = m_nameKeiyunasi;
						}
						else if (pCentDedRessya->isRunBetweenNextEki(iEkiOrder))
						{
							if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka &&
								!bDisplayTsuukaEkiJikoku)
							{
								strText = m_nameTsuuka;
							}
							else if (aCdDedJikoku.isNull())
							{
								//発時刻がない場合、この駅と前の駅の間が運行ありの場合は、通過の場合はレ印、停車の場合は着時刻または○印を表示します
								if (pCentDedRessya->isRunBetweenNextEki(iEkiOrder - 1))
								{
									if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
									{
										strText = m_nameTsuuka;
									}
									else if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya)
									{
										CdDedJikoku aChakuJikoku = aCentDedEkiJikoku.getVirtualChakujikoku();
										if (!aChakuJikoku.isNull() &&
											!aCdDedEki.getJikokuhyouChakuJikokuDisplay())
										{
											//	時刻が設定されているかつ着時刻表示が無い場合は時刻を表示
											strText = encode_Ekijikoku(
												CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya,
												aChakuJikoku,
												bDisplaySecondEkiJikoku,
												bDisplayColonEkiJikoku,
												iSecondRoundChaku,
												iSecondRoundHatsu,
												bDisplay2400,
												true);
										}
										//csv出力では○印表示なし
									}
								}
								//この駅と前の駅の間が運行なしの場合は、起点側着時刻を取得し時刻表示を行う、ない場合はレ印または○印
								else//if(!pCentDedRessya->isRunBetweenNextEki(iEkiOrder-1))
								{
									CdDedJikoku aChakuJikoku;
									int iChakuEkiOrder = pCentDedRessya->getRunBetweenEkiBackward(iEkiOrder);
									if (pCentDedEkiCont->isSameBrunchLoopGroup(iEkiOrder, iChakuEkiOrder, pCentDedRessya->getRessyahoukou()))
									{
										aChakuJikoku = pCentDedRessya->getCentDedEkiJikoku(iChakuEkiOrder).getVirtualChakujikoku();
									}
									if (!aChakuJikoku.isNull())
									{
										strText = encode_Ekijikoku(
											aCentDedEkiJikoku.getEkiatsukai(),
											aChakuJikoku,
											bDisplaySecondEkiJikoku,
											bDisplayColonEkiJikoku,
											iSecondRoundChaku,
											iSecondRoundHatsu,
											bDisplay2400,
											true);
									}
									else//if (aChakuJikoku.isNull())
									{
										if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
										{
											strText = m_nameTsuuka;
										}
										//csv出力では○印表示なし

									}
								}

							}
							else //if (!aCdDedJikoku.isNull())
							{
								//発時刻がある場合は、通過を考慮せず、Virtual発時刻を取得して表示する。(編集段階でのadjustを信用する)
								aCdDedJikoku = aCentDedEkiJikoku.getVirtualHatsujikoku();

								/**
									秒単位表示OFFの場合は、切り上げ・切り捨ての処理を行いますが、
									その補助のため、着時刻が30秒以上切り上げまたは切り上げで、発時刻が切り捨ての場合、(発時刻表示時)
									着時刻の取得を行います。
									この駅と前の駅の間が運行なしの場合は、運行なしを超えた先の駅から時刻を取得します。
								*/
								CdDedJikoku aChakuJikoku;
								if (!bDisplaySecondEkiJikoku &&
									iSecondRoundChaku >= 1 &&
									iSecondRoundHatsu == 0)
								{
									if (pCentDedRessya->isRunBetweenNextEki(iEkiOrder - 1))
									{
										aChakuJikoku = aCentDedEkiJikoku.getVirtualChakujikoku();
									}
									else
									{
										int iChakuEkiOrder = pCentDedRessya->getRunBetweenEkiBackward(iEkiOrder);
										if (pCentDedEkiCont->isSameBrunchLoopGroup(iEkiOrder, iChakuEkiOrder, pCentDedRessya->getRessyahoukou()))
										{
											aChakuJikoku = pCentDedRessya->getCentDedEkiJikoku(iChakuEkiOrder).getVirtualChakujikoku();
										}
									}
								}

								strText = encode_Ekijikoku(
									aCentDedEkiJikoku.getEkiatsukai(),
									aCdDedJikoku,
									bDisplaySecondEkiJikoku,
									bDisplayColonEkiJikoku,
									iSecondRoundChaku,
									iSecondRoundHatsu,
									bDisplay2400,
									false,
									aChakuJikoku);
							}
						}
						else if (pCentDedRessya->isRunBetweenNextEki(iEkiOrder - 1))
						{
							//この駅と前の駅の間が運行あり、この駅と次の駅の間が運行なしの場合
							if (aCdDedEki.getJikokuhyouChakuJikokuDisplay())
							{
								//この駅が発着表示の場合、基本的には経由なし表示になります。
								//ただし、この駅に発着両時刻が設定されている場合、終点側発時刻を取得して表示します
								if (aCdDedJikoku.isNull() || aCentDedEkiJikoku.getChakujikoku().isNull())
								{
									strText = m_nameKeiyunasi;
								}
								else//if (!aCdDedJikoku.isNull() &&!aCentDedEkiJikoku.getChakujikoku().isNull())
								{
									CdDedJikoku aHatsuJikoku;
									int iHatsuEkiOrder = pCentDedRessya->getRunBetweenEkiForward(iEkiOrder);
									if (pCentDedEkiCont->isSameBrunchLoopGroup(iEkiOrder, iHatsuEkiOrder, pCentDedRessya->getRessyahoukou()))
									{
										aHatsuJikoku = pCentDedRessya->getCentDedEkiJikoku(iHatsuEkiOrder).getVirtualHatsujikoku();
									}
									/**
										秒単位表示OFFの場合は、切り上げ・切り捨ての処理を行いますが、
										その補助のため、着時刻が30秒以上切り上げまたは切り上げで、発時刻が切り捨ての場合、着時刻の取得を行います。(発時刻表示)
									*/
									CdDedJikoku aChakuJikoku;
									if (!bDisplaySecondEkiJikoku &&
										iSecondRoundChaku >= 1 &&
										iSecondRoundHatsu == 0)
									{
										aChakuJikoku = aCentDedEkiJikoku.getVirtualChakujikoku();
									}

									if (aHatsuJikoku.isNull())
									{
										strText = m_nameKeiyunasi;
									}
									else
									{
										strText = encode_Ekijikoku(
											aCentDedEkiJikoku.getEkiatsukai(),
											aHatsuJikoku,
											bDisplaySecondEkiJikoku,
											bDisplayColonEkiJikoku,
											iSecondRoundChaku,
											iSecondRoundHatsu,
											bDisplay2400,
											false,
											aChakuJikoku);
									}
								}
							}
							else//if (!aCdDedEki.getJikokuhyouChakuJikokuDisplay())
							{
								//この駅が発時刻のみ表示の場合、当駅着時刻がある場合はそれを表示し、ない場合は終点方発時刻を取得して表示する。
								//ただし、発時刻が設定されている場合は、終点方発時刻を優先する。
								CdDedJikoku aChakuJikoku = aCentDedEkiJikoku.getVirtualChakujikoku();
								if (aChakuJikoku.isNull())
								{
									//当駅着時刻がない場合は、終点方発時刻を取得して表示する。
									CdDedJikoku aHatsuJikoku;
									int iHatsuEkiOrder = pCentDedRessya->getRunBetweenEkiForward(iEkiOrder);
									if (pCentDedEkiCont->isSameBrunchLoopGroup(iEkiOrder, iHatsuEkiOrder, pCentDedRessya->getRessyahoukou()))
									{
										aHatsuJikoku = pCentDedRessya->getCentDedEkiJikoku(iHatsuEkiOrder).getVirtualHatsujikoku();
									}

									if (!aHatsuJikoku.isNull())
									{
										strText = encode_Ekijikoku(
											aCentDedEkiJikoku.getEkiatsukai(),
											aHatsuJikoku,
											bDisplaySecondEkiJikoku,
											bDisplayColonEkiJikoku,
											iSecondRoundChaku,
											iSecondRoundHatsu,
											bDisplay2400,
											false);
									}
									else//if (aHatsuJikoku.isNull())
									{
										if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
										{
											strText = m_nameTsuuka;
										}
										//csv出力では○印表示なし

									}
								}
								else if (aCdDedJikoku.isNull())
								{
									//発時刻なし・着時刻ありの場合は、着時刻を表示します。ただし、終点方発時刻を取得し、秒単位処理に用います。

									/**
										秒単位表示OFFの場合は、切り上げ・切り捨ての処理を行いますが、
										その補助のため、着時刻が切り上げで、発時刻が30秒以上切り上げまたは切り捨ての場合、発時刻の取得を行います。(着時刻表示時)
										この駅と次の駅の間が運行なしの場合は、運行なしを超えた先の駅から時刻を取得します。
									*/
									CdDedJikoku aHatsuJikoku;
									if (!bDisplaySecondEkiJikoku &&
										iSecondRoundChaku == 2 &&
										iSecondRoundHatsu <= 1)
									{
										int iHatsuEkiOrder = pCentDedRessya->getRunBetweenEkiForward(iEkiOrder);
										if (pCentDedEkiCont->isSameBrunchLoopGroup(iEkiOrder, iHatsuEkiOrder, pCentDedRessya->getRessyahoukou()))
										{
											aHatsuJikoku = pCentDedRessya->getCentDedEkiJikoku(iHatsuEkiOrder).getVirtualHatsujikoku();
										}
									}

									strText = encode_Ekijikoku(
										aCentDedEkiJikoku.getEkiatsukai(),
										aChakuJikoku,
										bDisplaySecondEkiJikoku,
										bDisplayColonEkiJikoku,
										iSecondRoundChaku,
										iSecondRoundHatsu,
										bDisplay2400,
										true,
										aHatsuJikoku);
								}
								else// if (!aCdDedJikoku.isNull())
								{
									//発時刻・着時刻ともにある場合は、終点方発時刻の取得を試み、ある場合はそれを表示、ない場合は着時刻を表示します。
									CdDedJikoku aHatsuJikoku;
									int iHatsuEkiOrder = pCentDedRessya->getRunBetweenEkiForward(iEkiOrder);
									if (pCentDedEkiCont->isSameBrunchLoopGroup(iEkiOrder, iHatsuEkiOrder, pCentDedRessya->getRessyahoukou()))
									{
										aHatsuJikoku = pCentDedRessya->getCentDedEkiJikoku(iHatsuEkiOrder).getVirtualHatsujikoku();
									}
									if (!aHatsuJikoku.isNull())
									{
										strText = encode_Ekijikoku(
											aCentDedEkiJikoku.getEkiatsukai(),
											aHatsuJikoku,
											bDisplaySecondEkiJikoku,
											bDisplayColonEkiJikoku,
											iSecondRoundChaku,
											iSecondRoundHatsu,
											bDisplay2400,
											false,
											aChakuJikoku);
									}
									else// (aHatsuJikoku.isNull())
									{
										strText = encode_Ekijikoku(
											aCentDedEkiJikoku.getEkiatsukai(),
											aChakuJikoku,
											bDisplaySecondEkiJikoku,
											bDisplayColonEkiJikoku,
											iSecondRoundChaku,
											iSecondRoundHatsu,
											bDisplay2400,
											true);
									}
								}
							}
						}
						else//if (!pCentDedRessya->isRunBetweenNextEki(iEkiOrder)&&!pCentDedRessya->isRunBetweenNextEki(iEkiOrder-1))
						{
							//この駅の前後ともに運行なし(経由なし)の場合、この項は経由なし表示となります。

							strText = m_nameKeiyunasi;
						}
					}
					/**
						次駅が解結駅の場合、この欄に↴印を表示することがあります
						(1)次駅が解結駅かつ有効な始発駅
						(2)次駅が着時刻又は発時刻のどちらかのみ表示→Ver2.05 次駅が発時刻のみ表示の場合のみに変更
						(3)この欄の直下が、次駅の項な場合。
					*/
					if (iEkiOrder + 1 == iValidSihatsuEki &&
						iEkiOrder + 1 == aCustomizeJikokuhyouContent.iReleaseEkiOrder)
					{
						CentDedEkiCont::CdDedEki aCdDedEkiNext = muCdDedEki->get(iEkiOrder + 1);
						if (!aCdDedEkiNext.getJikokuhyouChakuJikokuDisplay() &&
							aCdDedEkiNext.getJikokuhyouHatsuJikokuDisplay())
						{
							int iYColumnNumberNext = iYColumnNumber + 1;
							CdYColSpec aCdYColSpecNext = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberNext);
							if (aCdYColSpecNext.getEkiOrder() == iEkiOrder + 1)
							{
								strText = m_nameRelease;
							}
						}
					}
					/**
						前駅が増結駅の場合、この欄に↳印を表示することがあります
						(1)前駅が増結駅かつ有効な終着駅
						(2)前駅が着時刻又は発時刻のどちらかのみ表示→Ver2.05 前駅が着時刻のみ表示の場合のみに変更
						(3)この欄の直上が、前駅の項な場合。
					*/
					if (iEkiOrder - 1 == iValidSyuuchakuEki &&
						iEkiOrder - 1 == aCustomizeJikokuhyouContent.iConnectEkiOrder &&
						iValidSyuuchakuEki != -1)
					{
						CentDedEkiCont::CdDedEki aCdDedEkiPrev = muCdDedEki->get(iEkiOrder - 1);
						if (aCdDedEkiPrev.getJikokuhyouChakuJikokuDisplay() &&
							!aCdDedEkiPrev.getJikokuhyouHatsuJikokuDisplay())
						{
							int iYColumnNumberPrev = iYColumnNumber - 1;
							CdYColSpec aCdYColSpecPrev = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberPrev);
							if (aCdYColSpecPrev.getEkiOrder() == iEkiOrder - 1)
							{
								strText = m_nameConnect;
							}
						}
					}
				}

				CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
				aRow.getCellCont()->insert(CdCsvCell(strText));
				pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
				iRowIndex++;
			}
			else if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_Track)
			{
				tstring strText;
				if (pCentDedRessya == NULL)
				{
					/**
						pCentDedRessya == NULLの場合は、
						分割+路線外終着または路線外始発+増結のどちらかのパターンです。
						なお、分割駅に対応する路線外終着表示欄、もしくは解結駅に対応する路線外始発表示欄がない場合は、この列車の描写は行わず、空行となります。
					*/
					if (aCustomizeJikokuhyouContent.iReleaseEkiOrder >= 0)
					{
						/**
							分割+路線外終着の場合、
							分割駅ならば番線略称を表示します。(当駅発時刻の表示は無しに)
							分割駅より後かつ、路線外終着表示駅までの場合は、経由なしを表示します。
							分割駅より一つ上の駅の場合、分割駅が発時刻のみ表示で、この項が分割駅の項の直上なら、ここで↴を表示します。
							それ以外の場合は、空白となります
						*/
						if (iEkiOrder + 1 == aCustomizeJikokuhyouContent.iReleaseEkiOrder)
						{
							CentDedEkiCont::CdDedEki aCdDedEkiNext = muCdDedEki->get(iEkiOrder + 1);
							if (!aCdDedEkiNext.getJikokuhyouChakuJikokuDisplay() &&
								aCdDedEkiNext.getJikokuhyouHatsuJikokuDisplay())
							{
								int iYColumnNumberNext = iYColumnNumber + 1;
								CdYColSpec aCdYColSpecNext = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberNext);
								if (aCdYColSpecNext.getEkiOrder() == iEkiOrder + 1)
								{
									strText = m_nameRelease;
								}
							}
						}
						else if (iEkiOrder == aCustomizeJikokuhyouContent.iReleaseEkiOrder)
						{
							CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);
							CentDedEkiTrack2Cont aCentDedEkiTrack2Cont = aCdDedEki.getCentDedEkiTrack2Cont();

							strText = aCentDedEkiTrack2Cont.get(
								aCustomizeJikokuhyouContent.iRessyaTrackIndex).getTrackRyakusyou(m_CdYColSpecCont.getRessyahoukou());
						}
						else if (iEkiOrder > aCustomizeJikokuhyouContent.iReleaseEkiOrder &&
							iEkiOrder <= m_iOuterShuchakuDisplayEkiOrder[aCustomizeJikokuhyouContent.iReleaseEkiOrder])
						{
							strText = m_nameKeiyunasi;
						}
					}
					else if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
					{
						/**
							路線外始発+併合の場合
							併合駅ならば番線略称を表示します。
							路線外始発表示駅から併合駅の前までなら、経由なしを表示します。
							併合駅の次の駅の場合、併合駅が着時刻のみ表示かつ、この項が併合駅の直下なら、この項に↳を表示します。
							それ以外の場合は、空白となります
						*/
						if (iEkiOrder - 1 == aCustomizeJikokuhyouContent.iConnectEkiOrder)
						{
							CentDedEkiCont::CdDedEki aCdDedEkiPrev = muCdDedEki->get(iEkiOrder - 1);
							if (aCdDedEkiPrev.getJikokuhyouChakuJikokuDisplay() &&
								!aCdDedEkiPrev.getJikokuhyouHatsuJikokuDisplay())
							{
								int iYColumnNumberPrev = iYColumnNumber - 1;
								CdYColSpec aCdYColSpecPrev = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberPrev);
								if (aCdYColSpecPrev.getEkiOrder() == iEkiOrder - 1)
								{
									strText = m_nameConnect;
								}
							}
						}
						else if (iEkiOrder == aCustomizeJikokuhyouContent.iConnectEkiOrder)
						{
							CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);
							CentDedEkiTrack2Cont aCentDedEkiTrack2Cont = aCdDedEki.getCentDedEkiTrack2Cont();

							strText = aCentDedEkiTrack2Cont.get(
								aCustomizeJikokuhyouContent.iRessyaTrackIndex).getTrackRyakusyou(m_CdYColSpecCont.getRessyahoukou());
						}
						else if (iEkiOrder >= m_iOuterShihatsuDisplayEkiOrder[aCustomizeJikokuhyouContent.iConnectEkiOrder] &&
							iEkiOrder < aCustomizeJikokuhyouContent.iConnectEkiOrder)
						{
							strText = m_nameKeiyunasi;
						}
					}
				}
				else
				{
					CentDedEkiJikoku	aCentDedEkiJikoku =
						pCentDedRessya->getCentDedEkiJikoku(iEkiOrder);
					int iValidSihatsuEki = pCentDedRessya->getValidSihatsuEki();
					int iValidSyuuchakuEki = pCentDedRessya->getValidSyuuchakuEki();

					if (iValidSihatsuEki < 0 || iValidSyuuchakuEki < 0)
					{
						strText = _T("");
					}
					else if (iEkiOrder < iValidSihatsuEki)
					{
						if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] <= iEkiOrder)
						{
							//路線外始発
							strText = m_nameKeiyunasi;
						}
						else if (aCustomizeJikokuhyouContent.iSihatsuEkiOrder >= -2 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] <= iEkiOrder)
						{
							//路線外始発相当
							strText = m_nameKeiyunasi;
						}
						else if (iCurrentRessyaShihatsuEkiOrder >= 0)
						{
							strText = m_nameKeiyunasi;
						}
						else if (aCustomizeJikokuhyouContent.iReleaseEkiOrder == iEkiOrder &&
							aCdDedEki.getJikokuhyouChakuJikokuDisplay())
						{
							strText = m_nameKeiyunasi;
						}
						else if (aCustomizeJikokuhyouContent.iReleaseEkiOrder < iEkiOrder &&
							aCustomizeJikokuhyouContent.iReleaseEkiOrder >= 0)
						{
							strText = m_nameKeiyunasi;
						}
					}
					else if (iEkiOrder > iValidSyuuchakuEki)
					{
						if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= iEkiOrder)
						{
							//路線外終着
							strText = m_nameKeiyunasi;
						}
						else if (aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder >= -2 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= iEkiOrder)
						{
							//路線外終着相当
							strText = m_nameKeiyunasi;

						}
						else if (aCustomizeJikokuhyouContent.iConnectEkiOrder > iEkiOrder &&
							aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
						{
							strText = m_nameKeiyunasi;
						}
						else if (aCustomizeJikokuhyouContent.iConnectEkiOrder == iEkiOrder &&
							aCdDedEki.getJikokuhyouHatsuJikokuDisplay())
						{
							strText = m_nameKeiyunasi;
						}
					}
					else if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_None)
					{
						//始発駅から終着駅の間は、運行なし駅に経由なしマークを表示します
						strText = m_nameKeiyunasi;
					}
					/**
						停車・通過の場合
						前後のいずれかが、停車または通過であるもしくは、
						路線の始発駅もしくは終着駅である
						(iEkiOrder==0の時に、isRunBetweenNextEki(iEkiOrder)がfalseな場合は、iValidSihatsuEkiが0にならない
							→iEkiOrder < iValidSihatsuEkiのif節に引っかかるから、終着駅の場合も同様)
					*/
					else if (iEkiOrder == 0 ||
						iEkiOrder == muCdDedEki->size() - 1 ||
						pCentDedRessya->isRunBetweenNextEki(iEkiOrder - 1) ||
						pCentDedRessya->isRunBetweenNextEki(iEkiOrder))
					{
						CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);
						CentDedEkiTrack2Cont aCentDedEkiTrack2Cont = aCdDedEki.getCentDedEkiTrack2Cont();

						strText = aCentDedEkiTrack2Cont.get(
							aCentDedEkiJikoku.getRessyaTrackIndex()).getTrackRyakusyou(pCentDedRessya->getRessyahoukou());
						/*int idxRessyasyubetsu
							= pCentDedRessya->getRessyasyubetsuIndex();
						*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu);*/
					}
					/**
						前後ともにisRunBetweenNextEki=falseの場合、この欄を経由無し表示にします。
					*/
					else
					{
						strText = m_nameKeiyunasi;
					}

					/**
						次駅が解結駅の場合、この欄に↴印を表示することがあります
						(1)次駅が解結駅かつ有効な始発駅
						(2)次駅が着時刻又は発時刻のどちらかのみ表示→Ver2.05 次駅が発時刻のみ表示の場合のみに変更
						(3)この欄の直下が、次駅の項な場合。
					*/
					if (iEkiOrder + 1 == iValidSihatsuEki &&
						iEkiOrder + 1 == aCustomizeJikokuhyouContent.iReleaseEkiOrder)
					{
						CentDedEkiCont::CdDedEki aCdDedEkiNext = muCdDedEki->get(iEkiOrder + 1);
						if (!aCdDedEkiNext.getJikokuhyouChakuJikokuDisplay() &&
							aCdDedEkiNext.getJikokuhyouHatsuJikokuDisplay())
						{
							int iYColumnNumberNext = iYColumnNumber + 1;
							CdYColSpec aCdYColSpecNext = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberNext);
							if (aCdYColSpecNext.getEkiOrder() == iEkiOrder + 1)
							{
								strText = m_nameRelease;
							}
						}
					}
					/**
						前駅が増結駅の場合、この欄に↳印を表示することがあります
						(1)前駅が増結駅かつ有効な終着駅
						(2)前駅が着時刻又は発時刻のどちらかのみ表示→Ver2.05 前駅が着時刻のみ表示の場合のみに変更
						(3)この欄の直上が、前駅の項な場合。
					*/
					if (iEkiOrder - 1 == iValidSyuuchakuEki &&
						iEkiOrder - 1 == aCustomizeJikokuhyouContent.iConnectEkiOrder &&
						iValidSyuuchakuEki != -1)
					{
						CentDedEkiCont::CdDedEki aCdDedEkiPrev = muCdDedEki->get(iEkiOrder - 1);
						if (aCdDedEkiPrev.getJikokuhyouChakuJikokuDisplay() &&
							!aCdDedEkiPrev.getJikokuhyouHatsuJikokuDisplay())
						{
							int iYColumnNumberPrev = iYColumnNumber - 1;
							CdYColSpec aCdYColSpecPrev = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberPrev);
							if (aCdYColSpecPrev.getEkiOrder() == iEkiOrder - 1)
							{
								strText = m_nameConnect;
							}
						}
					}
				}

				CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
				aRow.getCellCont()->insert(CdCsvCell(strText));
				pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
				iRowIndex++;
			}
			else if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_EkiRessyabangou)
			{
				tstring strText;
				if (pCentDedRessya == NULL)
				{
					/**
						pCentDedRessya == NULLの場合は、
						分割+路線外終着または路線外始発+増結のどちらかのパターンです。
						なお、分割駅に対応する路線外終着表示欄、もしくは解結駅に対応する路線外始発表示欄がない場合は、この列車の描写は行わず、空行となります。
					*/
					if (aCustomizeJikokuhyouContent.iReleaseEkiOrder >= 0)
					{
						if (iEkiOrder + 1 == aCustomizeJikokuhyouContent.iReleaseEkiOrder)
						{
							CentDedEkiCont::CdDedEki aCdDedEkiNext = muCdDedEki->get(iEkiOrder + 1);
							if (!aCdDedEkiNext.getJikokuhyouChakuJikokuDisplay() &&
								aCdDedEkiNext.getJikokuhyouHatsuJikokuDisplay())
							{
								int iYColumnNumberNext = iYColumnNumber + 1;
								CdYColSpec aCdYColSpecNext = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberNext);
								if (aCdYColSpecNext.getEkiOrder() == iEkiOrder + 1)
								{
									strText = m_nameRelease;
								}
							}
						}
						else if (iEkiOrder == aCustomizeJikokuhyouContent.iReleaseEkiOrder)
						{
							if (aCdDedEki.getJikokuhyouRessyabangouDisplay() == 3)
							{
								strText = aCustomizeJikokuhyouContent.strRessyabangou;
							}
							else
							{
								strText = m_nameContinue;
							}
						}
						else if (iEkiOrder > aCustomizeJikokuhyouContent.iReleaseEkiOrder &&
							iEkiOrder <= m_iOuterShuchakuDisplayEkiOrder[aCustomizeJikokuhyouContent.iReleaseEkiOrder])
						{
							strText = m_nameKeiyunasi;

						}
					}
					else if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
					{
						if (iEkiOrder - 1 == aCustomizeJikokuhyouContent.iConnectEkiOrder)
						{
							CentDedEkiCont::CdDedEki aCdDedEkiPrev = muCdDedEki->get(iEkiOrder - 1);
							if (aCdDedEkiPrev.getJikokuhyouChakuJikokuDisplay() &&
								!aCdDedEkiPrev.getJikokuhyouHatsuJikokuDisplay())
							{
								int iYColumnNumberPrev = iYColumnNumber - 1;
								CdYColSpec aCdYColSpecPrev = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberPrev);
								if (aCdYColSpecPrev.getEkiOrder() == iEkiOrder - 1)
								{
									strText = m_nameConnect;
								}
							}
						}
						else if (iEkiOrder >= m_iOuterShihatsuDisplayEkiOrder[aCustomizeJikokuhyouContent.iConnectEkiOrder] &&
							iEkiOrder < aCustomizeJikokuhyouContent.iConnectEkiOrder)
						{
							strText = m_nameKeiyunasi;
						}
					}
				}
				else
				{
					int iValidSihatsuEki = pCentDedRessya->getValidSihatsuEki();
					int iValidSyuuchakuEki = pCentDedRessya->getValidSyuuchakuEki();
					if (iValidSihatsuEki == -1 || iValidSyuuchakuEki == -1)
					{
						strText = _T("");
					}
					else if (iEkiOrder < iValidSihatsuEki)
					{
						if (iCurrentRessyaShihatsuEkiOrder >= 0)
						{
							//iEkiOrder = iCurrentRessyaShihatsuEkiOrderで、この駅に発時刻を表示しているときは、経由なしではなく矢印を表示します。
							if (iEkiOrder == iCurrentRessyaShihatsuEkiOrder &&
								aCdDedEki.getJikokuhyouHatsuJikokuDisplay())
							{
								//発時刻欄に時刻が表示されるのは、着時刻表示が無い場合もしくは、前列車の終着駅発時刻が入力されている場合です。
								if (aCdDedEki.getJikokuhyouChakuJikokuDisplay())
								{
									const CentDedRessya* pPrevRessya =
										pCentDedRessyaCont->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex - 1]);
									if (pPrevRessya->getCentDedEkiJikoku(iEkiOrder).getHatsujikoku().isNull())
									{
										strText = m_nameKeiyunasi;
									}
								}
							}
							else
							{
								strText = m_nameKeiyunasi;
							}
						}
						//iCurrentRessyaShihatsuEkiOrder < 0(1列車目)
						else if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] <= iEkiOrder)
						{
							//路線外始発
							strText = m_nameKeiyunasi;
						}

						else if (aCustomizeJikokuhyouContent.iSihatsuEkiOrder >= -2 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] <= iEkiOrder)
						{
							//路線外始発相当
							strText = m_nameKeiyunasi;
						}
						else if (aCustomizeJikokuhyouContent.iReleaseEkiOrder <= iEkiOrder &&
							aCustomizeJikokuhyouContent.iReleaseEkiOrder >= 0)
						{
							//分割列車
							strText = m_nameKeiyunasi;
						}
					}
					else if (iValidSihatsuEki == iEkiOrder)
					{
						if (aCdDedEki.getJikokuhyouRessyabangouDisplay() == 3)
						{
							strText = pCentDedRessya->getRessyabangou();
						}
						else if (iCurrentRessyaShihatsuEkiOrder >= 0)
						{
							const CentDedRessya* pPrevRessya =
								pCentDedRessyaCont->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex - 1]);
							if (pPrevRessya->getLastOperation().getNextJunctionType() == 1)
							{
								strText = pCentDedRessya->getRessyabangou();
							}
							else if (pPrevRessya->getLastOperation().getNextJunctionType() == 2 &&
								aCdDedEki.getJikokuhyouRessyabangouDisplay() == 2)
							{
								strText = pCentDedRessya->getRessyabangou();
							}
							else
							{
								strText = m_nameContinue;
							}
						}
					}
					else if (iValidSihatsuEki < iEkiOrder &&
						iEkiOrder < iValidSyuuchakuEki)
					{
						if (pCentDedRessya->isRunBetweenNextEki(iEkiOrder) ||
							(!aCdDedEki.getJikokuhyouChakuJikokuDisplay() &&
								pCentDedRessya->isRunBetweenNextEki(iEkiOrder - 1)))
						{
							if (aCdDedEki.getJikokuhyouRessyabangouDisplay() == 3)
							{
								strText = pCentDedRessya->getRessyabangou();
							}
							else
							{
								strText = m_nameContinue;
							}
						}
						else
						{
							strText = m_nameKeiyunasi;
						}
					}
					else if (iValidSyuuchakuEki == iEkiOrder)
					{
						if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0)
						{
							//路線外終着
							strText = m_nameContinue;
						}
						else if (aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder >= -2 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0)
						{
							//路線外終着相当
							if (aCdDedEki.getJikokuhyouRessyabangouDisplay() == 3)
							{
								strText = aCustomizeJikokuhyouContent.strRessyabangou;
							}
							else if (aCustomizeJikokuhyouContent.eEAfterType == EBeforeAfterType::BeforeAfterType_ClassChange)
							{
								strText = aCustomizeJikokuhyouContent.strRessyabangou;
							}
							else if (aCustomizeJikokuhyouContent.eEAfterType == EBeforeAfterType::BeforeAfterType_PropertyChange &&
								aCdDedEki.getJikokuhyouRessyabangouDisplay() == 2)
							{
								strText = aCustomizeJikokuhyouContent.strRessyabangou;
							}
							else
							{
								strText = m_nameContinue;
							}

						}
						else if (aCustomizeJikokuhyouContent.iConnectEkiOrder > iEkiOrder &&
							aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
						{
							strText = m_nameKeiyunasi;
						}
					}
					else if (iValidSyuuchakuEki < iEkiOrder)
					{
						if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= iEkiOrder)
						{
							//路線外終着
							strText = m_nameKeiyunasi;
						}
						else if (aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder >= -2 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= iEkiOrder)
						{
							//路線外終着相当
							strText = m_nameKeiyunasi;

						}
						else if (aCustomizeJikokuhyouContent.iConnectEkiOrder > iEkiOrder &&
							aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
						{
							strText = m_nameKeiyunasi;
						}
					}

					/**
						次駅が解結駅の場合、この欄に↴印を表示することがあります
						(1)次駅が解結駅かつ有効な始発駅
						(2)次駅が着時刻又は発時刻のどちらかのみ表示→Ver2.05 次駅が発時刻のみ表示の場合のみに変更
						(3)この欄の直下が、次駅の項な場合。
					*/
					if (iEkiOrder + 1 == iValidSihatsuEki &&
						iEkiOrder + 1 == aCustomizeJikokuhyouContent.iReleaseEkiOrder)
					{
						CentDedEkiCont::CdDedEki aCdDedEkiNext = muCdDedEki->get(iEkiOrder + 1);
						if (!aCdDedEkiNext.getJikokuhyouChakuJikokuDisplay() &&
							aCdDedEkiNext.getJikokuhyouHatsuJikokuDisplay())
						{
							int iYColumnNumberNext = iYColumnNumber + 1;
							CdYColSpec aCdYColSpecNext = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberNext);
							if (aCdYColSpecNext.getEkiOrder() == iEkiOrder + 1)
							{
								strText = m_nameRelease;
							}
						}
					}
					/**
						前駅が増結駅の場合、この欄に↳印を表示することがあります
						(1)前駅が増結駅かつ有効な終着駅
						(2)前駅が着時刻又は発時刻のどちらかのみ表示→Ver2.05 前駅が着時刻のみ表示の場合のみに変更
						(3)この欄の直上が、前駅の項な場合。
					*/
					if (iEkiOrder - 1 == iValidSyuuchakuEki &&
						iEkiOrder - 1 == aCustomizeJikokuhyouContent.iConnectEkiOrder &&
						iValidSyuuchakuEki != -1)
					{
						CentDedEkiCont::CdDedEki aCdDedEkiPrev = muCdDedEki->get(iEkiOrder - 1);
						if (aCdDedEkiPrev.getJikokuhyouChakuJikokuDisplay() &&
							!aCdDedEkiPrev.getJikokuhyouHatsuJikokuDisplay())
						{
							int iYColumnNumberPrev = iYColumnNumber - 1;
							CdYColSpec aCdYColSpecPrev = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberPrev);
							if (aCdYColSpecPrev.getEkiOrder() == iEkiOrder - 1)
							{
								strText = m_nameConnect;
							}
						}
					}
				}

				CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
				aRow.getCellCont()->insert(CdCsvCell(strText));
				pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
				iRowIndex++;
			}
			else if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_EkiOperationNumber &&
				aCdYColSpec.getOperationIndex() == 0)
			{
				//0:空白、1:運番、2:経由なし、3:↓、4:分割、5:併合
				int iDisplayType = 0;
				vector<tstring> strOperationNumber;
				if (pCentDedRessya == NULL)
				{
					/**
						pCentDedRessya == NULLの場合は、
						分割+路線外終着または路線外始発+増結のどちらかのパターンです。
						なお、分割駅に対応する路線外終着表示欄、もしくは解結駅に対応する路線外始発表示欄がない場合は、この列車の描写は行わず、空行となります。
					*/
					if (aCustomizeJikokuhyouContent.iReleaseEkiOrder >= 0)
					{
						if (iEkiOrder + 1 == aCustomizeJikokuhyouContent.iReleaseEkiOrder)
						{
							CentDedEkiCont::CdDedEki aCdDedEkiNext = muCdDedEki->get(iEkiOrder + 1);
							if (!aCdDedEkiNext.getJikokuhyouChakuJikokuDisplay() &&
								aCdDedEkiNext.getJikokuhyouHatsuJikokuDisplay())
							{
								int iYColumnNumberNext = iYColumnNumber + aCdDedEki.getJikokuhyouOperationNumberDisplayRows() + 1;
								CdYColSpec aCdYColSpecNext = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberNext);
								if (aCdYColSpecNext.getEkiOrder() == iEkiOrder + 1)
								{
									iDisplayType = 4;
								}
							}
						}
						else if (iEkiOrder == aCustomizeJikokuhyouContent.iReleaseEkiOrder)
						{
							if (aCdDedEki.getJikokuhyouOperationNumberDisplay() == 1 ||
								aCdDedEki.getJikokuhyouOperationNumberDisplay() == 4)
							{
								iDisplayType = 1;//運番
								strOperationNumber = aCustomizeJikokuhyouContent.strOperationNumber;
							}
							else
							{
								iDisplayType = 3;//↓
							}
						}
						else if (iEkiOrder > aCustomizeJikokuhyouContent.iReleaseEkiOrder &&
							iEkiOrder <= m_iOuterShuchakuDisplayEkiOrder[aCustomizeJikokuhyouContent.iReleaseEkiOrder])
						{
							iDisplayType = 2;//||
						}
					}
					else if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
					{
						if (iEkiOrder - 1 == aCustomizeJikokuhyouContent.iConnectEkiOrder)
						{
							CentDedEkiCont::CdDedEki aCdDedEkiPrev = muCdDedEki->get(iEkiOrder - 1);
							if (aCdDedEkiPrev.getJikokuhyouChakuJikokuDisplay() &&
								!aCdDedEkiPrev.getJikokuhyouHatsuJikokuDisplay())
							{
								int iYColumnNumberPrev = iYColumnNumber - 1;
								CdYColSpec aCdYColSpecPrev = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberPrev);
								if (aCdYColSpecPrev.getEkiOrder() == iEkiOrder - 1)
								{
									iDisplayType = 5;
								}
							}
						}
						else if (iEkiOrder >= m_iOuterShihatsuDisplayEkiOrder[aCustomizeJikokuhyouContent.iConnectEkiOrder] &&
							iEkiOrder < aCustomizeJikokuhyouContent.iConnectEkiOrder)
						{
							iDisplayType = 2;//||
						}
					}
				}
				else
				{
					int iValidSihatsuEki = pCentDedRessya->getValidSihatsuEki();
					int iValidSyuuchakuEki = pCentDedRessya->getValidSyuuchakuEki();
					if (iValidSihatsuEki == -1 || iValidSyuuchakuEki == -1)
					{
						iDisplayType = 0;
					}
					else if (iEkiOrder < iValidSihatsuEki)
					{
						if (iCurrentRessyaShihatsuEkiOrder >= 0)
						{
							//iEkiOrder = iCurrentRessyaShihatsuEkiOrderで、この駅に発時刻を表示しているときは、経由なしではなく空白にします。
							if (iEkiOrder == iCurrentRessyaShihatsuEkiOrder &&
								aCdDedEki.getJikokuhyouHatsuJikokuDisplay())
							{
								//発時刻欄に時刻が表示されるのは、着時刻表示が無い場合もしくは、前列車の終着駅発時刻が入力されている場合です。
								if (aCdDedEki.getJikokuhyouChakuJikokuDisplay())
								{
									const CentDedRessya* pPrevRessya =
										pCentDedRessyaCont->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex - 1]);
									if (pPrevRessya->getCentDedEkiJikoku(iEkiOrder).getHatsujikoku().isNull())
									{
										iDisplayType = 2;//||
									}
								}
							}
							else
							{
								iDisplayType = 2;//||
							}
						}
						//iCurrentRessyaShihatsuEkiOrder < 0(1列車目)
						else if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] <= iEkiOrder)
						{
							//路線外始発
							iDisplayType = 2;//||
						}

						else if (aCustomizeJikokuhyouContent.iSihatsuEkiOrder >= -2 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] <= iEkiOrder)
						{
							//路線外始発相当
							iDisplayType = 2;//||
						}
						else if (aCustomizeJikokuhyouContent.iReleaseEkiOrder <= iEkiOrder &&
							aCustomizeJikokuhyouContent.iReleaseEkiOrder >= 0)
						{
							//分割列車
							iDisplayType = 2;//||
						}
					}
					else if (iValidSihatsuEki == iEkiOrder)
					{
						if (aCdDedEki.getJikokuhyouOperationNumberDisplay() == 4)
						{
							iDisplayType = 1;//運番
							strOperationNumber = pCentDedRessya->getOperationNumber(iEkiOrder);
						}
						else if (iCurrentRessyaShihatsuEkiOrder >= 0 &&
							aCdDedEki.getJikokuhyouOperationNumberDisplay() >= 2)
						{
							const CentDedRessya* pPrevRessya =
								pCentDedRessyaCont->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex - 1]);
							if (pPrevRessya->getLastOperation().getNextJunctionType() == 1)
							{
								iDisplayType = 1;//運番
								strOperationNumber = pCentDedRessya->getOperationNumber(iEkiOrder);
							}
							else if (pPrevRessya->getLastOperation().getNextJunctionType() == 2 &&
								aCdDedEki.getJikokuhyouOperationNumberDisplay() == 3)
							{
								iDisplayType = 1;//運番
								strOperationNumber = pCentDedRessya->getOperationNumber(iEkiOrder);
							}
							else
							{
								iDisplayType = 3;//↓
							}
						}
						else if (iCurrentRessyaShihatsuEkiOrder >= 0 &&
							aCdDedEki.getJikokuhyouOperationNumberDisplay() == 1)
						{
							const CentDedRessya* pPrevRessya =
								pCentDedRessyaCont->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex - 1]);
							vector<tstring> strOperationNumberArrive =
								pPrevRessya->getOperationNumber(pPrevRessya->getValidSyuuchakuEki() - 1);
							vector<tstring> strOperationNumberDeparture =
								pCentDedRessya->getOperationNumber(iEkiOrder);
							if (strOperationNumberArrive != strOperationNumberDeparture)
							{
								iDisplayType = 1;//運番
								strOperationNumber = strOperationNumberDeparture;
							}
							else
							{
								iDisplayType = 3;//↓
							}
						}
					}
					else if (iValidSihatsuEki < iEkiOrder &&
						iEkiOrder < iValidSyuuchakuEki)
					{
						if (pCentDedRessya->isRunBetweenNextEki(iEkiOrder) ||
							(!aCdDedEki.getJikokuhyouChakuJikokuDisplay() &&
								pCentDedRessya->isRunBetweenNextEki(iEkiOrder - 1)))
						{
							if (aCdDedEki.getJikokuhyouOperationNumberDisplay() == 4)
							{
								iDisplayType = 1;//運番
								strOperationNumber = pCentDedRessya->getOperationNumber(iEkiOrder);
							}
							else if (aCdDedEki.getJikokuhyouOperationNumberDisplay() == 1)
							{
								vector<tstring> strOperationNumberArrive =
									pCentDedRessya->getOperationNumber(iEkiOrder - 1);
								vector<tstring> strOperationNumberDeparture =
									pCentDedRessya->getOperationNumber(iEkiOrder);
								if (strOperationNumberArrive != strOperationNumberDeparture)
								{
									iDisplayType = 1;//運番
									strOperationNumber = strOperationNumberDeparture;
								}
								else
								{
									iDisplayType = 3;//↓
								}
							}
							else
							{
								iDisplayType = 3;//↓
							}
						}
						else
						{
							iDisplayType = 2;//||
						}
					}
					else if (iValidSyuuchakuEki == iEkiOrder)
					{
						if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0)
						{
							//路線外終着「↓」
							iDisplayType = 3;//↓
						}
						else if (aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder >= -2 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0)
						{
							//路線外終着相当
							if (aCdDedEki.getJikokuhyouOperationNumberDisplay() == 4)
							{
								iDisplayType = 1;//運番
								strOperationNumber = aCustomizeJikokuhyouContent.strOperationNumber;
							}
							else if (aCdDedEki.getJikokuhyouOperationNumberDisplay() == 1)
							{
								vector<tstring> strOperationNumberArrive =
									pCentDedRessya->getOperationNumber(iEkiOrder - 1);
								if (strOperationNumberArrive != aCustomizeJikokuhyouContent.strOperationNumber)
								{
									iDisplayType = 1;//運番
									strOperationNumber = aCustomizeJikokuhyouContent.strOperationNumber;
								}
								else
								{
									iDisplayType = 3;//↓
								}
							}
							else if (aCustomizeJikokuhyouContent.eEAfterType == EBeforeAfterType::BeforeAfterType_ClassChange)
							{
								iDisplayType = 1;//運番
								strOperationNumber = aCustomizeJikokuhyouContent.strOperationNumber;
							}
							else if (aCustomizeJikokuhyouContent.eEAfterType == EBeforeAfterType::BeforeAfterType_PropertyChange &&
								aCdDedEki.getJikokuhyouOperationNumberDisplay() == 3)
							{
								iDisplayType = 1;//運番
								strOperationNumber = aCustomizeJikokuhyouContent.strOperationNumber;
							}
							else
							{
								iDisplayType = 3;//↓
							}

						}
						else if (aCustomizeJikokuhyouContent.iConnectEkiOrder > iEkiOrder &&
							aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
						{
							iDisplayType = 2;//||
						}
					}
					else if (iValidSyuuchakuEki < iEkiOrder)
					{
						if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= iEkiOrder)
						{
							//路線外終着
							iDisplayType = 2;//||
						}
						else if (aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder >= -2 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= iEkiOrder)
						{
							iDisplayType = 2;//||
						}
						else if (aCustomizeJikokuhyouContent.iConnectEkiOrder > iEkiOrder &&
							aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
						{
							iDisplayType = 2;//||
						}
					}

					/**
						次駅が解結駅の場合、この欄に↴印を表示することがあります
						(1)次駅が解結駅かつ有効な始発駅
						(2)次駅が着時刻又は発時刻のどちらかのみ表示→Ver2.05 次駅が発時刻のみ表示の場合のみに変更
						(3)この欄の直下が、次駅の項な場合。
						(4)この欄が運用番号の最下段の場合
					*/
					if (iEkiOrder + 1 == iValidSihatsuEki &&
						iEkiOrder + 1 == aCustomizeJikokuhyouContent.iReleaseEkiOrder)
					{
						CentDedEkiCont::CdDedEki aCdDedEkiNext = muCdDedEki->get(iEkiOrder + 1);
						if (!aCdDedEkiNext.getJikokuhyouChakuJikokuDisplay() &&
							aCdDedEkiNext.getJikokuhyouHatsuJikokuDisplay())
						{
							int iYColumnNumberNext = iYColumnNumber + aCdDedEki.getJikokuhyouOperationNumberDisplayRows();
							CdYColSpec aCdYColSpecNext = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberNext);
							if (aCdYColSpecNext.getEkiOrder() == iEkiOrder + 1)
							{
								iDisplayType = 4;
							}
						}
					}
					/**
						前駅が増結駅の場合、この欄に↳印を表示することがあります
						(1)前駅が増結駅かつ有効な終着駅
						(2)前駅が着時刻又は発時刻のどちらかのみ表示→Ver2.05 前駅が着時刻のみ表示の場合のみに変更
						(3)この欄の直上が、前駅の項な場合。
						(4)この欄が運用番号の最上段の場合
					*/
					if (iEkiOrder - 1 == iValidSyuuchakuEki &&
						iEkiOrder - 1 == aCustomizeJikokuhyouContent.iConnectEkiOrder &&
						iValidSyuuchakuEki != -1)
					{
						CentDedEkiCont::CdDedEki aCdDedEkiPrev = muCdDedEki->get(iEkiOrder - 1);
						if (aCdDedEkiPrev.getJikokuhyouChakuJikokuDisplay() &&
							!aCdDedEkiPrev.getJikokuhyouHatsuJikokuDisplay())
						{
							int iYColumnNumberPrev = iYColumnNumber - 1;
							CdYColSpec aCdYColSpecPrev = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberPrev);
							if (aCdYColSpecPrev.getEkiOrder() == iEkiOrder - 1)
							{
								iDisplayType = 5;
							}
						}
					}
				}

				for (int idx = 0; idx < aCdDedEki.getJikokuhyouOperationNumberDisplayRows(); idx++)
				{
					tstring strText;
					if (iDisplayType == 1)
					{
						/**
							運用番号描写手順
							1.最初にstrOperationNumberに運番を読み込む
							2.運番が空の場合は空白を描写する
							3.空でない場合、表示段数の最下段以外の場合は、strOperationNumberの先頭要素を描写し、先頭要素を削除して次の段へ
							4.空でない場合、表示段数の最下段に到達したら、strOperationNumberに残っている要素を、'+'で連結して描写する。
						*/
						if (strOperationNumber.empty())
						{
							strText = _T("");
						}
						else if (idx == aCdDedEki.getJikokuhyouOperationNumberDisplayRows() - 1)
						{
							if (idx != 0)
							{
								strText = _T("+";)
							}
							strText += joinc('+', strOperationNumber);
						}
						else
						{
							if (idx != 0)
							{
								strText = _T("+";)
							}
							strText += strOperationNumber.front();
							strOperationNumber.erase(strOperationNumber.begin());
						}
					}
					else if (iDisplayType == 2)
					{
						strText = m_nameKeiyunasi;
					}
					else if (iDisplayType == 3)
					{
						strText = _T("↓";)
					}
					else if (iDisplayType == 4 &&
						idx == aCdDedEki.getJikokuhyouOperationNumberDisplayRows() - 1)
					{
						strText = m_nameRelease;
					}
					else if (iDisplayType == 5 &&
						idx == 0)
					{
						strText = m_nameConnect;
					}

					CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
					aRow.getCellCont()->insert(CdCsvCell(strText));
					pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
					iRowIndex++;
				}

			}
			else if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_EkiRessyasyubetsu)
			{
				tstring strRessyasyubetsu;
				if (pCentDedRessya == NULL || !pCentDedRessya->isNull())
				{
					strRessyasyubetsu = pCentDedRessyasyubetsu->getRyakusyou();
				}

				tstring strText;
				if (pCentDedRessya == NULL)
				{
					/**
						pCentDedRessya == NULLの場合は、
						分割+路線外終着または路線外始発+増結のどちらかのパターンです。
						なお、分割駅に対応する路線外終着表示欄、もしくは解結駅に対応する路線外始発表示欄がない場合は、この列車の描写は行わず、空行となります。
					*/
					if (aCustomizeJikokuhyouContent.iReleaseEkiOrder >= 0)
					{
						if (iEkiOrder + 1 == aCustomizeJikokuhyouContent.iReleaseEkiOrder)
						{
							CentDedEkiCont::CdDedEki aCdDedEkiNext = muCdDedEki->get(iEkiOrder + 1);
							if (!aCdDedEkiNext.getJikokuhyouChakuJikokuDisplay() &&
								aCdDedEkiNext.getJikokuhyouHatsuJikokuDisplay())
							{
								int iYColumnNumberNext = iYColumnNumber + 1;
								CdYColSpec aCdYColSpecNext = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberNext);
								if (aCdYColSpecNext.getEkiOrder() == iEkiOrder + 1)
								{
									strText = m_nameRelease;
								}
							}
						}
						else if (iEkiOrder == aCustomizeJikokuhyouContent.iReleaseEkiOrder)
						{
							if (aCdDedEki.getJikokuhyouRessyaSyubetsuDisplay() == 3)
							{
								strText = strRessyasyubetsu;
							}
							else
							{
								strText = m_nameContinue;
							}
						}
						else if (iEkiOrder > aCustomizeJikokuhyouContent.iReleaseEkiOrder &&
							iEkiOrder <= m_iOuterShuchakuDisplayEkiOrder[aCustomizeJikokuhyouContent.iReleaseEkiOrder])
						{
							strText = m_nameKeiyunasi;
						}
					}
					else if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
					{
						if (iEkiOrder - 1 == aCustomizeJikokuhyouContent.iConnectEkiOrder)
						{
							CentDedEkiCont::CdDedEki aCdDedEkiPrev = muCdDedEki->get(iEkiOrder - 1);
							if (aCdDedEkiPrev.getJikokuhyouChakuJikokuDisplay() &&
								!aCdDedEkiPrev.getJikokuhyouHatsuJikokuDisplay())
							{
								int iYColumnNumberPrev = iYColumnNumber - 1;
								CdYColSpec aCdYColSpecPrev = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberPrev);
								if (aCdYColSpecPrev.getEkiOrder() == iEkiOrder - 1)
								{
									strText = m_nameConnect;
								}
							}
						}
						else if (iEkiOrder >= m_iOuterShihatsuDisplayEkiOrder[aCustomizeJikokuhyouContent.iConnectEkiOrder] &&
							iEkiOrder < aCustomizeJikokuhyouContent.iConnectEkiOrder)
						{
							strText = m_nameKeiyunasi;
						}
					}
				}
				else
				{
					int iValidSihatsuEki = pCentDedRessya->getValidSihatsuEki();
					int iValidSyuuchakuEki = pCentDedRessya->getValidSyuuchakuEki();
					if (iValidSihatsuEki == -1 || iValidSyuuchakuEki == -1)
					{
						strText = _T("");
					}
					else if (iEkiOrder < iValidSihatsuEki)
					{
						if (iCurrentRessyaShihatsuEkiOrder >= 0)
						{
							//iEkiOrder = iCurrentRessyaShihatsuEkiOrderで、この駅に発時刻を表示しているときは、経由なしではなく矢印を表示します。
							if (iEkiOrder == iCurrentRessyaShihatsuEkiOrder &&
								aCdDedEki.getJikokuhyouHatsuJikokuDisplay())
							{
								//発時刻欄に時刻が表示されるのは、着時刻表示が無い場合もしくは、前列車の終着駅発時刻が入力されている場合です。
								if (aCdDedEki.getJikokuhyouChakuJikokuDisplay())
								{
									const CentDedRessya* pPrevRessya =
										pCentDedRessyaCont->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex - 1]);
									if (pPrevRessya->getCentDedEkiJikoku(iEkiOrder).getHatsujikoku().isNull())
									{
										strText = m_nameKeiyunasi;
									}
								}
							}
							else
							{
								strText = m_nameKeiyunasi;
							}
						}
						//iCurrentRessyaShihatsuEkiOrder < 0(1列車目)
						else if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] <= iEkiOrder)
						{
							//路線外始発
							strText = m_nameKeiyunasi;
						}

						else if (aCustomizeJikokuhyouContent.iSihatsuEkiOrder >= -2 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] <= iEkiOrder)
						{
							//路線外始発相当
							strText = m_nameKeiyunasi;
						}
						else if (aCustomizeJikokuhyouContent.iReleaseEkiOrder <= iEkiOrder &&
							aCustomizeJikokuhyouContent.iReleaseEkiOrder >= 0)
						{
							//分割列車
							strText = m_nameKeiyunasi;
						}
					}
					else if (iValidSihatsuEki == iEkiOrder)
					{
						if (aCdDedEki.getJikokuhyouRessyaSyubetsuDisplay() == 3)
						{
							strText = strRessyasyubetsu;
						}
						else if (iCurrentRessyaShihatsuEkiOrder >= 0)
						{
							const CentDedRessya* pPrevRessya =
								pCentDedRessyaCont->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex - 1]);
							if (pPrevRessya->getLastOperation().getNextJunctionType() == 1)
							{
								strText = strRessyasyubetsu;
							}
							else if (pPrevRessya->getLastOperation().getNextJunctionType() == 2 &&
								aCdDedEki.getJikokuhyouRessyaSyubetsuDisplay() == 2)
							{
								strText = strRessyasyubetsu;
							}
							else
							{
								strText = m_nameContinue;
							}
						}
					}
					else if (iValidSihatsuEki < iEkiOrder &&
						iEkiOrder < iValidSyuuchakuEki)
					{
						if (pCentDedRessya->isRunBetweenNextEki(iEkiOrder) ||
							(!aCdDedEki.getJikokuhyouChakuJikokuDisplay() &&
								pCentDedRessya->isRunBetweenNextEki(iEkiOrder - 1)))
						{
							if (aCdDedEki.getJikokuhyouRessyaSyubetsuDisplay() == 3)
							{
								strText = strRessyasyubetsu;
							}
							else
							{
								strText = m_nameContinue;
							}
						}
						else
						{
							strText = m_nameKeiyunasi;
						}
					}
					else if (iValidSyuuchakuEki == iEkiOrder)
					{
						if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0)
						{
							//路線外終着
							//Ver2.06.21 この項は↓とします。(単純化)
							strText = m_nameContinue;
						}
						else if (aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder >= -2 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0)
						{
							//路線外終着相当
							const CentDedRessyasyubetsu* pCentDedRessyasyubetsuNext = pCentDedRessyasyubetsuContGet
								->get(aCustomizeJikokuhyouContent.iRessyasyubetsuIndex);
							if (bDisplayParentSyubetsu && pCentDedRessyasyubetsuNext->getParentSyubetsuIndex() >= 0)
							{
								pCentDedRessyasyubetsuNext = pCentDedRessyasyubetsuContGet
									->get(pCentDedRessyasyubetsuNext->getParentSyubetsuIndex());
							}

							strRessyasyubetsu = pCentDedRessyasyubetsuNext->getRyakusyou();

							if (aCdDedEki.getJikokuhyouRessyaSyubetsuDisplay() == 3)
							{
								strText = strRessyasyubetsu;
							}
							else if (aCustomizeJikokuhyouContent.eEAfterType == EBeforeAfterType::BeforeAfterType_ClassChange)
							{
								strText = strRessyasyubetsu;
							}
							else if (aCustomizeJikokuhyouContent.eEAfterType == EBeforeAfterType::BeforeAfterType_PropertyChange &&
								aCdDedEki.getJikokuhyouRessyaSyubetsuDisplay() == 2)
							{
								strText = strRessyasyubetsu;
							}
							else
							{
								strText = m_nameContinue;
							}

						}
						else if (aCustomizeJikokuhyouContent.iConnectEkiOrder > iEkiOrder &&
							aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
						{
							strText = m_nameKeiyunasi;
						}
					}
					else if (iValidSyuuchakuEki < iEkiOrder)
					{
						if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= iEkiOrder)
						{
							//路線外終着
							strText = m_nameKeiyunasi;
						}
						else if (aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder >= -2 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= iEkiOrder)
						{
							//路線外終着相当
							strText = m_nameKeiyunasi;
						}
						else if (aCustomizeJikokuhyouContent.iConnectEkiOrder > iEkiOrder &&
							aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
						{
							strText = m_nameKeiyunasi;
						}
					}
					/**
						次駅が解結駅の場合、この欄に↴印を表示することがあります
						(1)次駅が解結駅かつ有効な始発駅
						(2)次駅が着時刻又は発時刻のどちらかのみ表示→Ver2.05 次駅が発時刻のみ表示の場合のみに変更
						(3)この欄の直下が、次駅の項な場合。
					*/
					if (iEkiOrder + 1 == iValidSihatsuEki &&
						iEkiOrder + 1 == aCustomizeJikokuhyouContent.iReleaseEkiOrder)
					{
						CentDedEkiCont::CdDedEki aCdDedEkiNext = muCdDedEki->get(iEkiOrder + 1);
						if (!aCdDedEkiNext.getJikokuhyouChakuJikokuDisplay() &&
							aCdDedEkiNext.getJikokuhyouHatsuJikokuDisplay())
						{
							int iYColumnNumberNext = iYColumnNumber + 1;
							CdYColSpec aCdYColSpecNext = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberNext);
							if (aCdYColSpecNext.getEkiOrder() == iEkiOrder + 1)
							{
								strText = m_nameRelease;
							}
						}
					}
					/**
						前駅が増結駅の場合、この欄に↳印を表示することがあります
						(1)前駅が増結駅かつ有効な終着駅
						(2)前駅が着時刻又は発時刻のどちらかのみ表示→Ver2.05 前駅が着時刻のみ表示の場合のみに変更
						(3)この欄の直上が、前駅の項な場合。
					*/
					if (iEkiOrder - 1 == iValidSyuuchakuEki &&
						iEkiOrder - 1 == aCustomizeJikokuhyouContent.iConnectEkiOrder &&
						iValidSyuuchakuEki != -1)
					{
						CentDedEkiCont::CdDedEki aCdDedEkiPrev = muCdDedEki->get(iEkiOrder - 1);
						if (aCdDedEkiPrev.getJikokuhyouChakuJikokuDisplay() &&
							!aCdDedEkiPrev.getJikokuhyouHatsuJikokuDisplay())
						{
							int iYColumnNumberPrev = iYColumnNumber - 1;
							CdYColSpec aCdYColSpecPrev = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberPrev);
							if (aCdYColSpecPrev.getEkiOrder() == iEkiOrder - 1)
							{
								strText = m_nameConnect;
							}
						}
					}
				}

				CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
				aRow.getCellCont()->insert(CdCsvCell(strText));
				pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
				iRowIndex++;

			}
			else if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_EkiRessyamei)
			{
				tstring strText = _T("");
				tstring strText2 = _T("");
				tstring strText3 = _T("");
				if (pCentDedRessya == NULL)
				{
					/**
						pCentDedRessya == NULLの場合は、
						分割+路線外終着または路線外始発+増結のどちらかのパターンです。
						なお、分割駅に対応する路線外終着表示欄、もしくは解結駅に対応する路線外始発表示欄がない場合は、この列車の描写は行わず、空行となります。
					*/
					if (aCustomizeJikokuhyouContent.iReleaseEkiOrder >= 0)
					{
						if (iEkiOrder + 1 == aCustomizeJikokuhyouContent.iReleaseEkiOrder)
						{
							CentDedEkiCont::CdDedEki aCdDedEkiNext = muCdDedEki->get(iEkiOrder + 1);
							if (!aCdDedEkiNext.getJikokuhyouChakuJikokuDisplay() &&
								aCdDedEkiNext.getJikokuhyouHatsuJikokuDisplay())
							{
								int iYColumnNumberNext = iYColumnNumber + 3;
								CdYColSpec aCdYColSpecNext = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberNext);
								if (aCdYColSpecNext.getEkiOrder() == iEkiOrder + 1)
								{
									strText3 = m_nameRelease;
								}
							}
						}
						else if (iEkiOrder == aCustomizeJikokuhyouContent.iReleaseEkiOrder)
						{
							if (aCdDedEki.getJikokuhyouRessyameiDisplay() == 3)
							{
								strText = aCustomizeJikokuhyouContent.strRessyamei;
								strText2 = aCustomizeJikokuhyouContent.strGousuu;
								if (!strText2.empty())
								{
									strText3 = m_nameGou;
								}
							}
						}
					}
					else if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
					{
						if (iEkiOrder - 1 == aCustomizeJikokuhyouContent.iConnectEkiOrder)
						{
							CentDedEkiCont::CdDedEki aCdDedEkiPrev = muCdDedEki->get(iEkiOrder - 1);
							if (aCdDedEkiPrev.getJikokuhyouChakuJikokuDisplay() &&
								!aCdDedEkiPrev.getJikokuhyouHatsuJikokuDisplay())
							{
								int iYColumnNumberPrev = iYColumnNumber - 1;
								CdYColSpec aCdYColSpecPrev = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberPrev);
								if (aCdYColSpecPrev.getEkiOrder() == iEkiOrder - 1)
								{
									strText = m_nameConnect;
								}
							}
						}
					}
				}
				else
				{
					int iValidSihatsuEki = pCentDedRessya->getValidSihatsuEki();
					int iValidSyuuchakuEki = pCentDedRessya->getValidSyuuchakuEki();
					if (iValidSihatsuEki == -1 || iValidSyuuchakuEki == -1)
					{
						strText = _T("");
						strText2 = _T("");
						strText3 = _T("");
					}
					else if (iValidSihatsuEki == iEkiOrder)
					{
						if (aCdDedEki.getJikokuhyouRessyameiDisplay() == 3)
						{
							strText = pCentDedRessya->getRessyamei();
							strText2 = pCentDedRessya->getGousuu();
							if (!strText2.empty())
							{
								strText3 = m_nameGou;
							}
						}
						else if (iCurrentRessyaShihatsuEkiOrder >= 0 &&
							aCdDedEki.getJikokuhyouRessyameiDisplay() >= 1)
						{
							const CentDedRessya* pPrevRessya =
								pCentDedRessyaCont->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex - 1]);
							if (pPrevRessya->getLastOperation().getNextJunctionType() == 1 &&
								aCdDedEki.getJikokuhyouRessyameiDisplay() >= 1)
							{
								strText = pCentDedRessya->getRessyamei();
								strText2 = pCentDedRessya->getGousuu();
								if (!strText2.empty())
								{
									strText3 = m_nameGou;
								}
							}
							else if (pPrevRessya->getLastOperation().getNextJunctionType() == 2 &&
								aCdDedEki.getJikokuhyouRessyameiDisplay() == 2)
							{
								strText = pCentDedRessya->getRessyamei();
								strText2 = pCentDedRessya->getGousuu();
								if (!strText2.empty())
								{
									strText3 = m_nameGou;
								}
							}
						}
					}
					else if (iValidSihatsuEki < iEkiOrder &&
						iEkiOrder < iValidSyuuchakuEki &&
						aCdDedEki.getJikokuhyouRessyameiDisplay() == 3 &&
						(pCentDedRessya->isRunBetweenNextEki(iEkiOrder) ||
							(!aCdDedEki.getJikokuhyouChakuJikokuDisplay() &&
								pCentDedRessya->isRunBetweenNextEki(iEkiOrder - 1))))
					{
						strText = pCentDedRessya->getRessyamei();
						strText2 = pCentDedRessya->getGousuu();
						if (!strText2.empty())
						{
							strText3 = m_nameGou;
						}
					}
					else if (iValidSyuuchakuEki == iEkiOrder &&
						aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder >= -2 &&
						m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0)
					{
						//路線外終着相当

						if (aCdDedEki.getJikokuhyouRessyameiDisplay() == 3)
						{
							strText = aCustomizeJikokuhyouContent.strRessyamei;
							strText2 = aCustomizeJikokuhyouContent.strGousuu;
							if (!strText2.empty())
							{
								strText3 = m_nameGou;
							}
						}
						else if (aCustomizeJikokuhyouContent.eEAfterType == EBeforeAfterType::BeforeAfterType_ClassChange)
						{
							strText = aCustomizeJikokuhyouContent.strRessyamei;
							strText2 = aCustomizeJikokuhyouContent.strGousuu;
							if (!strText2.empty())
							{
								strText3 = m_nameGou;
							}
						}
						else if (aCustomizeJikokuhyouContent.eEAfterType == EBeforeAfterType::BeforeAfterType_PropertyChange &&
							aCdDedEki.getJikokuhyouRessyameiDisplay() == 2)
						{
							strText = aCustomizeJikokuhyouContent.strRessyamei;
							strText2 = aCustomizeJikokuhyouContent.strGousuu;
							if (!strText2.empty())
							{
								strText3 = m_nameGou;
							}
						}
					}

					/**
						次駅が解結駅の場合、この欄に↴印を表示することがあります
						(1)次駅が解結駅かつ有効な始発駅
						(2)次駅が着時刻又は発時刻のどちらかのみ表示→Ver2.05 次駅が発時刻のみ表示の場合のみに変更
						(3)この欄の直下が、次駅の項な場合。
					*/
					if (iEkiOrder + 1 == iValidSihatsuEki &&
						iEkiOrder + 1 == aCustomizeJikokuhyouContent.iReleaseEkiOrder)
					{
						CentDedEkiCont::CdDedEki aCdDedEkiNext = muCdDedEki->get(iEkiOrder + 1);
						if (!aCdDedEkiNext.getJikokuhyouChakuJikokuDisplay() &&
							aCdDedEkiNext.getJikokuhyouHatsuJikokuDisplay())
						{
							int iYColumnNumberNext = iYColumnNumber + 3;
							CdYColSpec aCdYColSpecNext = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberNext);
							if (aCdYColSpecNext.getEkiOrder() == iEkiOrder + 1)
							{
								strText3 = m_nameRelease;
							}
						}
					}
					/**
						前駅が増結駅の場合、この欄に↳印を表示することがあります
						(1)前駅が増結駅かつ有効な終着駅
						(2)前駅が着時刻又は発時刻のどちらかのみ表示→Ver2.05 前駅が着時刻のみ表示の場合のみに変更
						(3)この欄の直上が、前駅の項な場合。
					*/
					if (iEkiOrder - 1 == iValidSyuuchakuEki &&
						iEkiOrder - 1 == aCustomizeJikokuhyouContent.iConnectEkiOrder &&
						iValidSyuuchakuEki != -1)
					{
						CentDedEkiCont::CdDedEki aCdDedEkiPrev = muCdDedEki->get(iEkiOrder - 1);
						if (aCdDedEkiPrev.getJikokuhyouChakuJikokuDisplay() &&
							!aCdDedEkiPrev.getJikokuhyouHatsuJikokuDisplay())
						{
							int iYColumnNumberPrev = iYColumnNumber - 1;
							CdYColSpec aCdYColSpecPrev = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberPrev);
							if (aCdYColSpecPrev.getEkiOrder() == iEkiOrder - 1)
							{
								strText = m_nameConnect;
							}
						}
					}
				}

				CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
				aRow.getCellCont()->insert(CdCsvCell(strText));
				pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
				iRowIndex++;
				CdCsvRow	aRow2 = pCdCsvDocument->getRowCont()->get(iRowIndex);
				aRow2.getCellCont()->insert(CdCsvCell(strText2));
				pCdCsvDocument->getRowCont()->set(aRow2, iRowIndex);
				iRowIndex++;
				CdCsvRow	aRow3 = pCdCsvDocument->getRowCont()->get(iRowIndex);
				aRow3.getCellCont()->insert(CdCsvCell(strText3));
				pCdCsvDocument->getRowCont()->set(aRow3, iRowIndex);
				iRowIndex++;

			}
			else if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_EkiOuter_Shihatsu1)
			{
				tstring strText;
				tstring strText2;
				/**
					路線外始発欄
					(1)駅作業で路線外始発が設定されている場合(基本)
					(2)前列車の始発駅が、路線外始発相当で表示されている場合(主編成)
					(3)前列車の始発駅が、路線外始発相当で表示されている場合(併合)
				*/
				if (pCentDedRessya == NULL)
				{
					/**
						(3)のパターン　aCustomizeJikokuhyouContentのiConnectEkiOrderで
						m_iOuterShihatsuDisplayEkiOrderから路線外始発表示駅を取得し、
						それが当駅ならば、ここで路線外始発表示を行う
					*/
					if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0 &&
						iEkiOrder == m_iOuterShihatsuDisplayEkiOrder[aCustomizeJikokuhyouContent.iConnectEkiOrder])
					{
						if (aCustomizeJikokuhyouContent.iSihatsuEkiOrder < 0)
						{
							strText = m_nameLoop;
						}
						else if (aCustomizeJikokuhyouContent.iOuterShihatsuEkiIndex >= 0)
						{
							strText = muCdDedEki->get(aCustomizeJikokuhyouContent.iSihatsuEkiOrder).getOuterTerminalJikokuRyaku(
								aCustomizeJikokuhyouContent.iOuterShihatsuEkiIndex, true);
						}
						else
						{
							strText = muCdDedEki->get(aCustomizeJikokuhyouContent.iSihatsuEkiOrder).getEkimeiJikokuhyouRyaku(true);
						}
						CdDedJikoku aCdDedJikoku
							= aCustomizeJikokuhyouContent.OuterShihatsuJikoku;
						strText2 = encode_Ekijikoku(
							CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya,
							aCdDedJikoku,
							bDisplaySecondEkiJikoku,
							bDisplayColonEkiJikoku,
							iSecondRoundChaku,
							iSecondRoundHatsu,
							bDisplay2400,
							false);
					}
					/**
						この列が分割表示の場合、分割表示が有効・この駅が分割駅よりも下・この駅が分割表示駅であるかここよりも上ならば、
						この項には経由なしを表示する。
					*/
					else if (aCustomizeJikokuhyouContent.iReleaseEkiOrder >= 0 &&
						iEkiOrder > aCustomizeJikokuhyouContent.iReleaseEkiOrder &&
						iEkiOrder <= m_iOuterShuchakuDisplayEkiOrder[aCustomizeJikokuhyouContent.iReleaseEkiOrder])
					{
						strText = m_nameKeiyunasi;
						strText2 = m_nameKeiyunasi;
					}
				}
				else
				{
					int iValidSihatsuEki = pCentDedRessya->getValidSihatsuEki();
					int iValidSyuuchakuEki = pCentDedRessya->getValidSyuuchakuEki();
					if (iValidSihatsuEki == -1 || iValidSyuuchakuEki == -1)
					{
						strText = _T("");
						strText2 = _T("");
					}
					else if (iEkiOrder <= iValidSihatsuEki)
					{
						if (iCurrentRessyaShihatsuEkiOrder >= 0/* &&
							iEkiOrder < iValidSihatsuEki*/)
						{
							strText = m_nameKeiyunasi;
							strText2 = m_nameKeiyunasi;
						}
						/**
							(2)のパターン　pCentDedRessyaの始発駅Orderで
							m_iOuterShihatsuDisplayEkiOrderから路線外始発表示駅を取得し、
							それが当駅ならば、ここで路線外始発表示を行う
						*/
						else if (aCustomizeJikokuhyouContent.iSihatsuEkiOrder >= -2 &&
							iEkiOrder == m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki])
						{
							if (aCustomizeJikokuhyouContent.iSihatsuEkiOrder < 0)
							{
								strText = m_nameLoop;
							}
							else if (aCustomizeJikokuhyouContent.iOuterShihatsuEkiIndex >= 0)
							{
								strText = muCdDedEki->get(aCustomizeJikokuhyouContent.iSihatsuEkiOrder).getOuterTerminalJikokuRyaku(
									aCustomizeJikokuhyouContent.iOuterShihatsuEkiIndex, true);
							}
							else
							{
								strText = muCdDedEki->get(aCustomizeJikokuhyouContent.iSihatsuEkiOrder).getEkimeiJikokuhyouRyaku(true);
							}
							CdDedJikoku aCdDedJikoku
								= aCustomizeJikokuhyouContent.OuterShihatsuJikoku;
							strText2 = encode_Ekijikoku(
								CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya,
								aCdDedJikoku,
								bDisplaySecondEkiJikoku,
								bDisplayColonEkiJikoku,
								iSecondRoundChaku,
								iSecondRoundHatsu,
								bDisplay2400,
								false);
						}
						/**
							(1)のパターン　pCentDedRessyaの始発駅Orderで
							m_iOuterShihatsuDisplayEkiOrderから路線外始発表示駅を取得し、
							それが当駅ならば、ここで路線外始発表示を行う
						*/
						else if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer &&
							iEkiOrder == m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki])
						{
							const CentDedBeforeOperation aFirstOperation = pCentDedRessya->getFirstOperation();
							CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iValidSihatsuEki);
							strText = aCdDedEki.getOuterTerminalJikokuRyaku(aFirstOperation.getOuterShihatsuekiIndex(), true);
							if (!(aFirstOperation.getOuterShihatsuJikoku().isNull()))
							{
								CdDedJikoku aCdDedJikoku
									= aFirstOperation.getOuterShihatsuJikoku();
								strText2 = encode_Ekijikoku(
									CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya,
									aCdDedJikoku,
									bDisplaySecondEkiJikoku,
									bDisplayColonEkiJikoku,
									iSecondRoundChaku,
									iSecondRoundHatsu,
									bDisplay2400,
									false);
							}
						}
						else if (aCustomizeJikokuhyouContent.iReleaseEkiOrder < iEkiOrder &&
							aCustomizeJikokuhyouContent.iReleaseEkiOrder >= 0)
						{
							strText = m_nameKeiyunasi;
							strText2 = m_nameKeiyunasi;
						}
					}
					else if (iValidSihatsuEki < iEkiOrder &&
						iEkiOrder <= iValidSyuuchakuEki)
					{
						if (!pCentDedRessya->isRunBetweenNextEki(iEkiOrder - 1))
						{
							strText = m_nameKeiyunasi;
							strText2 = m_nameKeiyunasi;
						}
					}
					else if (iValidSyuuchakuEki < iEkiOrder)
					{
						if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= iEkiOrder)
						{
							strText = m_nameKeiyunasi;
							strText2 = m_nameKeiyunasi;
						}
						else if (aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder >= -2 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= iEkiOrder)
						{
							strText = m_nameKeiyunasi;
							strText2 = m_nameKeiyunasi;
						}
						else if (aCustomizeJikokuhyouContent.iConnectEkiOrder > iEkiOrder &&
							aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
						{
							strText = m_nameKeiyunasi;
							strText2 = m_nameKeiyunasi;
						}
					}
				}

				CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
				aRow.getCellCont()->insert(CdCsvCell(strText));
				pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
				iRowIndex++;
				CdCsvRow	aRow2 = pCdCsvDocument->getRowCont()->get(iRowIndex);
				aRow2.getCellCont()->insert(CdCsvCell(strText2));
				pCdCsvDocument->getRowCont()->set(aRow2, iRowIndex);
				iRowIndex++;
			}
			else if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_EkiOuter_Shuchaku1)
			{
				tstring strText;
				tstring strText2;

				/**
					路線外終着欄
					(1)駅作業で路線外終着が設定されている場合(基本)
					(2)次列車の終着駅が、路線外終着相当で表示されている場合(主編成)
					(3)次列車の終着駅が、路線外終着相当で表示されている場合(分割)
				*/
				if (pCentDedRessya == NULL)
				{
					/**
						(3)のパターン　aCustomizeJikokuhyouContentのiReleaseEkiOrderで
						m_iOuterShuchakuDisplayEkiOrderから路線外終着表示駅を取得し、
						それが当駅ならば、ここで路線外終着表示を行う
					*/
					if (aCustomizeJikokuhyouContent.iReleaseEkiOrder >= 0 &&
						iEkiOrder == m_iOuterShuchakuDisplayEkiOrder[aCustomizeJikokuhyouContent.iReleaseEkiOrder])
					{
						if (aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder < 0)
						{
							strText = m_nameLoop;
						}
						else if (aCustomizeJikokuhyouContent.iOuterShuchakuEkiIndex >= 0)
						{
							strText = muCdDedEki->get(aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder).getOuterTerminalJikokuRyaku(
								aCustomizeJikokuhyouContent.iOuterShuchakuEkiIndex, true);
						}
						else
						{
							strText = muCdDedEki->get(aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder).getEkimeiJikokuhyouRyaku(true);
						}
						CdDedJikoku aCdDedJikoku
							= aCustomizeJikokuhyouContent.OuterShuchakuJikoku;
						strText2 = encode_Ekijikoku(
							CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya,
							aCdDedJikoku,
							bDisplaySecondEkiJikoku,
							bDisplayColonEkiJikoku,
							iSecondRoundChaku,
							iSecondRoundHatsu,
							bDisplay2400,
							true);
					}
					/**
						この列が併合表示の場合、併合表示が有効・この駅が併合駅よりも上・この駅が併合表示駅であるかここよりも下ならば、
						この項には経由なしを表示する。
					*/
					else if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0 &&
						iEkiOrder < aCustomizeJikokuhyouContent.iConnectEkiOrder &&
						iEkiOrder >= m_iOuterShihatsuDisplayEkiOrder[aCustomizeJikokuhyouContent.iConnectEkiOrder])
					{
						strText = m_nameKeiyunasi;
						strText2 = m_nameKeiyunasi;
					}
				}
				else
				{
					int iValidSihatsuEki = pCentDedRessya->getValidSihatsuEki();
					int iValidSyuuchakuEki = pCentDedRessya->getValidSyuuchakuEki();
					if (iValidSihatsuEki == -1 || iValidSyuuchakuEki == -1)
					{
						strText = _T("");
						strText2 = _T("");
					}
					else if (iEkiOrder < iValidSihatsuEki)
					{
						if (iCurrentRessyaShihatsuEkiOrder >= 0/* &&
							iEkiOrder < iValidSihatsuEki*/)
						{
							strText = m_nameKeiyunasi;
							strText2 = m_nameKeiyunasi;
						}
						else if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] <= iEkiOrder)
						{
							strText = m_nameKeiyunasi;
							strText2 = m_nameKeiyunasi;
						}
						else if (aCustomizeJikokuhyouContent.iSihatsuEkiOrder >= -2 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] <= iEkiOrder)
						{
							strText = m_nameKeiyunasi;
							strText2 = m_nameKeiyunasi;
						}
						else if (aCustomizeJikokuhyouContent.iReleaseEkiOrder < iEkiOrder &&
							aCustomizeJikokuhyouContent.iReleaseEkiOrder >= 0)
						{
							strText = m_nameKeiyunasi;
							strText2 = m_nameKeiyunasi;
						}
					}
					else if (iValidSihatsuEki <= iEkiOrder &&
						iEkiOrder < iValidSyuuchakuEki)
					{
						if (!pCentDedRessya->isRunBetweenNextEki(iEkiOrder))
						{
							strText = m_nameKeiyunasi;
							strText2 = m_nameKeiyunasi;
						}
					}
					else if (iEkiOrder >= iValidSyuuchakuEki)
					{
						/**
							(2)のパターン　pCentDedRessyaの終着駅Orderで
							m_iOuterShihatsuDisplayEkiOrderから路線外終着表示駅を取得し、
							それが当駅ならば、ここで路線外終着表示を行う
						*/
						if (aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder >= -2 &&
							iEkiOrder == m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki])
						{
							if (aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder < 0)
							{
								strText = m_nameLoop;
							}
							else if (aCustomizeJikokuhyouContent.iOuterShuchakuEkiIndex >= 0)
							{
								strText = muCdDedEki->get(aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder).getOuterTerminalJikokuRyaku(
									aCustomizeJikokuhyouContent.iOuterShuchakuEkiIndex, true);
							}
							else
							{
								strText = muCdDedEki->get(aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder).getEkimeiJikokuhyouRyaku(true);
							}
							CdDedJikoku aCdDedJikoku
								= aCustomizeJikokuhyouContent.OuterShuchakuJikoku;
							strText2 = encode_Ekijikoku(
								CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya,
								aCustomizeJikokuhyouContent.OuterShuchakuJikoku,
								bDisplaySecondEkiJikoku,
								bDisplayColonEkiJikoku,
								iSecondRoundChaku,
								iSecondRoundHatsu,
								bDisplay2400,
								true);

						}
						/**
							(1)のパターン　pCentDedRessyaの終着駅Orderで
							m_iOuterShihatsuDisplayEkiOrderから路線外終着表示駅を取得し、
							それが当駅ならば、ここで路線外終着表示を行う
						*/
						else if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer &&
							iEkiOrder == m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki])
						{
							const CentDedAfterOperation aLastOperation = pCentDedRessya->getLastOperation();
							CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(pCentDedRessya->getValidSyuuchakuEki());
							strText = aCdDedEki.getOuterTerminalJikokuRyaku(aLastOperation.getOuterShuchakuekiIndex(), true);
							if (!(aLastOperation.getOuterShuchakuJikoku().isNull()))
							{
								CdDedJikoku aCdDedJikoku
									= aLastOperation.getOuterShuchakuJikoku();
								strText2 = encode_Ekijikoku(
									CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya,
									aCdDedJikoku,
									bDisplaySecondEkiJikoku,
									bDisplayColonEkiJikoku,
									iSecondRoundChaku,
									iSecondRoundHatsu,
									bDisplay2400,
									true);
							}
						}
						else if (aCustomizeJikokuhyouContent.iConnectEkiOrder > iEkiOrder &&
							aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
						{
							strText = m_nameKeiyunasi;
							strText2 = m_nameKeiyunasi;
						}
					}
				}

				CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
				aRow.getCellCont()->insert(CdCsvCell(strText));
				pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
				iRowIndex++;
				CdCsvRow	aRow2 = pCdCsvDocument->getRowCont()->get(iRowIndex);
				aRow2.getCellCont()->insert(CdCsvCell(strText2));
				pCdCsvDocument->getRowCont()->set(aRow2, iRowIndex);
				iRowIndex++;
			}
			else if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_Ekijikoku_Nyuusen)
			{
				tstring	strText = _T("");

				if (pCentDedRessya == NULL)
				{
					/**
						pCentDedRessya == NULLの場合は、
						分割+路線外終着または路線外始発+増結のどちらかのパターンです。
						なお、分割駅に対応する路線外終着表示欄、もしくは解結駅に対応する路線外始発表示欄がない場合は、この列車の描写は行わず、空行となります。
					*/
					if (aCustomizeJikokuhyouContent.iReleaseEkiOrder >= 0)
					{
						/**
							分割+路線外終着の場合、
							分割駅ならば↴を表示します。(当駅発時刻の表示は無しに)
							分割駅より後かつ、路線外終着表示駅までの場合は、経由なしを表示します。
							分割駅より一つ上の駅の場合、分割駅が発時刻のみ表示で、この項が分割駅の項の直上なら、ここで↴を表示します。
						*/
						if (iEkiOrder + 1 == aCustomizeJikokuhyouContent.iReleaseEkiOrder)
						{
							CentDedEkiCont::CdDedEki aCdDedEkiNext = muCdDedEki->get(iEkiOrder + 1);
							if (!aCdDedEkiNext.getJikokuhyouChakuJikokuDisplay() &&
								aCdDedEkiNext.getJikokuhyouHatsuJikokuDisplay())
							{
								int iYColumnNumberNext = iYColumnNumber + 1;
								CdYColSpec aCdYColSpecNext = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberNext);
								if (aCdYColSpecNext.getEkiOrder() == iEkiOrder + 1)
								{
									strText = m_nameRelease;
								}
							}
						}
						else if (iEkiOrder > aCustomizeJikokuhyouContent.iReleaseEkiOrder &&
							iEkiOrder <= m_iOuterShuchakuDisplayEkiOrder[aCustomizeJikokuhyouContent.iReleaseEkiOrder])
						{
							strText = m_nameKeiyunasi;//"||"

						}
					}
					else if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
					{
						/**
							路線外始発+併合の場合
							併合駅ならば当駅着時刻を表示します。
							路線外始発表示駅から併合駅の前までなら、経由なしを表示します。
							併合駅の次の駅の場合、併合駅が着時刻のみ表示かつ、この項が併合駅の直下なら、この項に↳を表示します。
							それ以外の場合は、----もしくは・・を表示します
						*/
						if (iEkiOrder - 1 == aCustomizeJikokuhyouContent.iConnectEkiOrder)
						{
							CentDedEkiCont::CdDedEki aCdDedEkiPrev = muCdDedEki->get(iEkiOrder - 1);
							if (aCdDedEkiPrev.getJikokuhyouChakuJikokuDisplay() &&
								!aCdDedEkiPrev.getJikokuhyouHatsuJikokuDisplay())
							{
								int iYColumnNumberPrev = iYColumnNumber - 1;
								CdYColSpec aCdYColSpecPrev = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberPrev);
								if (aCdYColSpecPrev.getEkiOrder() == iEkiOrder - 1)
								{
									strText = m_nameConnect;
								}
							}
						}
						else if (iEkiOrder >= m_iOuterShihatsuDisplayEkiOrder[aCustomizeJikokuhyouContent.iConnectEkiOrder] &&
							iEkiOrder < aCustomizeJikokuhyouContent.iConnectEkiOrder)
						{
							strText = m_nameKeiyunasi;
						}
					}
				}
				else
				{

					// --------------------------------
					//	駅時刻に合わせて、セルに文字を表示
					// --------------------------------
					int iValidSihatsuEki = pCentDedRessya->getValidSihatsuEki();
					int iValidSyuuchakuEki = pCentDedRessya->getValidSyuuchakuEki();
					if (iValidSihatsuEki == -1 || iValidSyuuchakuEki == -1)
					{
						//空白
						strText = _T("");
					}
					else if (iEkiOrder < iValidSihatsuEki)
					{
						if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] <= iEkiOrder)
						{
							//路線外始発
							strText = m_nameKeiyunasi;//"||"

						}
						else if (aCustomizeJikokuhyouContent.iSihatsuEkiOrder >= -2 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] <= iEkiOrder)
						{
							//路線外始発相当
							strText = m_nameKeiyunasi;//"||"
						}
						else if (iCurrentRessyaShihatsuEkiOrder != -1)
						{
							//一体化の2列車目以降(前の列車との間に、経由なし区間がある場合)
							strText = m_nameKeiyunasi;//"||"
						}
						else if (aCustomizeJikokuhyouContent.iReleaseEkiOrder < iEkiOrder &&
							aCustomizeJikokuhyouContent.iReleaseEkiOrder >= 0)
						{
							strText = m_nameKeiyunasi;//"||"
						}
					}
					else if (iEkiOrder == iValidSihatsuEki)
					{
						/**
							始発駅
							2列車目以降：iCurrentRessyaShihatsuEkiOrderが当駅の場合空白、当駅より前の場合経由なし
							路線外始発：当駅が路線外表示の場合空白、当駅より前の場合経由なし
							路線外始発相当：同上
							分割列車：分割駅が当駅より前なら経由なし、当駅の場合は着時刻欄がない場合、この項に分割矢印を表示

							それ以外：入線時刻を表示
						*/
						if (iCurrentRessyaShihatsuEkiOrder >= 0)
						{
							if (iCurrentRessyaShihatsuEkiOrder < iEkiOrder)
							{
								strText = m_nameKeiyunasi;//"||"
							}
						}
						else if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0)
						{
							if (m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] < iEkiOrder)
							{
								strText = m_nameKeiyunasi;//"||"
							}
						}
						else if (aCustomizeJikokuhyouContent.iSihatsuEkiOrder >= -2 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0)
						{
							if (m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] < iEkiOrder)
							{
								strText = m_nameKeiyunasi;//"||"
							}
						}
						else if (aCustomizeJikokuhyouContent.iReleaseEkiOrder >= 0)
						{
							if (aCustomizeJikokuhyouContent.iReleaseEkiOrder < iEkiOrder)
							{
								strText = m_nameKeiyunasi;//"||"
							}
							else if (aCustomizeJikokuhyouContent.iReleaseEkiOrder == iEkiOrder &&
								!aCdDedEki.getJikokuhyouChakuJikokuDisplay())
							{
								strText = m_nameRelease;
							}
						}
						else
						{
							CentDedEkiJikoku	aCentDedEkiJikoku =
								pCentDedRessya->getCentDedEkiJikoku(iEkiOrder);
							CdDedJikoku aCdDedJikoku = CdDedJikoku();
							const CentDedBeforeOperationCont* pBeforeOperationCont = aCentDedEkiJikoku.getCentDedBeforeOperationCont();

							int iRessyaTrackIndex = aCentDedEkiJikoku.getRessyaTrackIndex();
							for (int iOperationIndex = pBeforeOperationCont->size() - 1; iOperationIndex >= 0 && aCdDedJikoku.isNull(); iOperationIndex--)
							{
								const CentDedBeforeOperation* pBeforeOperation
									= pBeforeOperationCont->getMuPtr()->get(iOperationIndex);
								if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
								{
									if (iRessyaTrackIndex != pBeforeOperation->getShuntTrackIndex())
									{
										aCdDedJikoku = pBeforeOperation->getOperationChakuJikoku(true);
									}
								}
								else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Out)
								{
									aCdDedJikoku = pBeforeOperation->getOutJikoku();
								}
								else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Junction)
								{
									aCdDedJikoku = pBeforeOperation->getJunctionJikoku();
								}
							}
							if (!aCdDedJikoku.isNull())
							{
								strText = encode_Ekijikoku(
									CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya,
									aCdDedJikoku,
									bDisplaySecondEkiJikoku,
									bDisplayColonEkiJikoku,
									iSecondRoundChaku,
									iSecondRoundHatsu,
									bDisplay2400,
									true);
							}
						}
					}
					else if (iValidSihatsuEki < iEkiOrder &&
						iEkiOrder < iValidSyuuchakuEki)
					{
						if (!pCentDedRessya->isRunBetweenNextEki(iEkiOrder - 1))
						{
							strText = m_nameKeiyunasi;//"||"
						}
					}
					else if (iEkiOrder == iValidSyuuchakuEki)
					{
						//空白
						strText = _T("");
					}
					else if (iEkiOrder > iValidSyuuchakuEki)
					{
						if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= iEkiOrder)
						{
							//路線外終着
							strText = m_nameKeiyunasi;//"||"

						}
						else if (aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder >= -2 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= iEkiOrder)
						{
							//路線外終着相当
							strText = m_nameKeiyunasi;//"||"

						}
						else if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= iEkiOrder &&
							aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
						{
							strText = m_nameKeiyunasi;//"||"
						}
					}

					/**
						前駅が増結駅の場合、この欄に↳印を表示することがあります
						(1)前駅が増結駅かつ有効な終着駅
						(2)前駅が着時刻又は発時刻のどちらかのみ表示→Ver2.05 前駅が着時刻のみ表示の場合のみに変更
						(3)この欄の直上が、前駅の項な場合。
					*/
					if (iEkiOrder - 1 == iValidSyuuchakuEki &&
						iEkiOrder - 1 == aCustomizeJikokuhyouContent.iConnectEkiOrder &&
						iValidSyuuchakuEki != -1)
					{
						CentDedEkiCont::CdDedEki aCdDedEkiPrev = muCdDedEki->get(iEkiOrder - 1);
						if (aCdDedEkiPrev.getJikokuhyouChakuJikokuDisplay() &&
							!aCdDedEkiPrev.getJikokuhyouHatsuJikokuDisplay())
						{
							int iYColumnNumberPrev = iYColumnNumber - 1;
							CdYColSpec aCdYColSpecPrev = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberPrev);
							if (aCdYColSpecPrev.getEkiOrder() == iEkiOrder - 1)
							{
								strText = m_nameConnect;
							}
						}
					}
				}

				CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
				aRow.getCellCont()->insert(CdCsvCell(strText));
				pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
				iRowIndex++;
			}
			else if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_EkiPrevRessyabangou)
			{
				tstring strText;
				if (pCentDedRessya == NULL)
				{
					/**
						pCentDedRessya == NULLの場合は、
						分割+路線外終着または路線外始発+増結のどちらかのパターンです。
						なお、分割駅に対応する路線外終着表示欄、もしくは解結駅に対応する路線外始発表示欄がない場合は、この列車の描写は行わず、空行となります。
					*/
					if (aCustomizeJikokuhyouContent.iReleaseEkiOrder >= 0)
					{
						if (iEkiOrder > aCustomizeJikokuhyouContent.iReleaseEkiOrder &&
							iEkiOrder <= m_iOuterShuchakuDisplayEkiOrder[aCustomizeJikokuhyouContent.iReleaseEkiOrder])
						{
							strText = m_nameKeiyunasi;//"||"

						}
					}
					else if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
					{
						if (iEkiOrder - 1 == aCustomizeJikokuhyouContent.iConnectEkiOrder)
						{
							CentDedEkiCont::CdDedEki aCdDedEkiPrev = muCdDedEki->get(iEkiOrder - 1);
							if (aCdDedEkiPrev.getJikokuhyouChakuJikokuDisplay() &&
								!aCdDedEkiPrev.getJikokuhyouHatsuJikokuDisplay())
							{
								int iYColumnNumberPrev = iYColumnNumber - 1;
								CdYColSpec aCdYColSpecPrev = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberPrev);
								if (aCdYColSpecPrev.getEkiOrder() == iEkiOrder - 1)
								{
									strText = m_nameConnect;
								}
							}
						}
					}
				}
				else
				{
					int iValidSihatsuEki = pCentDedRessya->getValidSihatsuEki();
					int iValidSyuuchakuEki = pCentDedRessya->getValidSyuuchakuEki();
					if (iValidSihatsuEki == -1 || iValidSyuuchakuEki == -1)
					{
						strText = _T("");
					}
					else if (iEkiOrder < iValidSihatsuEki)
					{
						if (iCurrentRessyaShihatsuEkiOrder >= 0)
						{
							strText = m_nameKeiyunasi;//"||"
						}
						//iCurrentRessyaShihatsuEkiOrder < 0(1列車目)
						else if (aCustomizeJikokuhyouContent.iSihatsuEkiOrder >= -2 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] == iEkiOrder)
						{
							//路線外始発相当で、この駅が路線外始発表示駅の場合
							if (aCdDedEki.getJikokuhyouPrevRessyabangouDisplay() == 3)
							{
								strText = aCustomizeJikokuhyouContent.strPrevRessyabangou;
							}
							else if (aCustomizeJikokuhyouContent.eEBeforeType == EBeforeAfterType::BeforeAfterType_ClassChange)
							{
								strText = aCustomizeJikokuhyouContent.strPrevRessyabangou;
							}
							else if (aCustomizeJikokuhyouContent.eEBeforeType == EBeforeAfterType::BeforeAfterType_PropertyChange &&
								aCdDedEki.getJikokuhyouPrevRessyabangouDisplay() == 2)
							{
								strText = aCustomizeJikokuhyouContent.strPrevRessyabangou;
							}
						}
						else if (aCustomizeJikokuhyouContent.iReleaseEkiOrder < iEkiOrder &&
							aCustomizeJikokuhyouContent.iReleaseEkiOrder >= 0)
						{
							//分割列車
							strText = m_nameKeiyunasi;//"||"
						}
					}
					else if (iValidSihatsuEki == iEkiOrder)
					{
						//2列車目以降かつ、1列車目の終着駅との間に、経由なしがある場合
						if (iCurrentRessyaShihatsuEkiOrder >= 0 &&
							iCurrentRessyaShihatsuEkiOrder < iEkiOrder)
						{
							strText = m_nameKeiyunasi;//"||"
						}
						//路線外始発相当かつ、始発駅にこの項がある場合は、路線外始発表示も当然この駅にあるので、前列車接続タイプに基づいて表示を行う
						else if (aCustomizeJikokuhyouContent.iSihatsuEkiOrder >= -2)
						{
							if (aCdDedEki.getJikokuhyouPrevRessyabangouDisplay() == 3)
							{
								strText = aCustomizeJikokuhyouContent.strPrevRessyabangou;
							}
							else if (aCustomizeJikokuhyouContent.eEBeforeType == EBeforeAfterType::BeforeAfterType_ClassChange)
							{
								strText = aCustomizeJikokuhyouContent.strPrevRessyabangou;
							}
							else if (aCustomizeJikokuhyouContent.eEBeforeType == EBeforeAfterType::BeforeAfterType_PropertyChange &&
								aCdDedEki.getJikokuhyouPrevRessyabangouDisplay() == 2)
							{
								strText = aCustomizeJikokuhyouContent.strPrevRessyabangou;
							}
						}
					}
					else if (iValidSihatsuEki < iEkiOrder &&
						iEkiOrder < iValidSyuuchakuEki)
					{
						if (!pCentDedRessya->isRunBetweenNextEki(iEkiOrder - 1))
						{
							strText = m_nameKeiyunasi;
						}
					}
					else if (iValidSyuuchakuEki < iEkiOrder)
					{
						if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= iEkiOrder)
						{
							//路線外終着
							strText = m_nameKeiyunasi;
						}
						else if (aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder >= -2 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= iEkiOrder)
						{
							//路線外終着相当
							strText = m_nameKeiyunasi;

						}
						else if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= iEkiOrder &&
							aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
						{
							strText = m_nameKeiyunasi;//"||"
						}
					}

					/**
						前駅が増結駅の場合、この欄に↳印を表示することがあります
						(1)前駅が増結駅かつ有効な終着駅
						(2)前駅が着時刻又は発時刻のどちらかのみ表示→Ver2.05 前駅が着時刻のみ表示の場合のみに変更
						(3)この欄の直上が、前駅の項な場合。
					*/
					if (iEkiOrder - 1 == iValidSyuuchakuEki &&
						iEkiOrder - 1 == aCustomizeJikokuhyouContent.iConnectEkiOrder &&
						iValidSyuuchakuEki != -1)
					{
						CentDedEkiCont::CdDedEki aCdDedEkiPrev = muCdDedEki->get(iEkiOrder - 1);
						if (aCdDedEkiPrev.getJikokuhyouChakuJikokuDisplay() &&
							!aCdDedEkiPrev.getJikokuhyouHatsuJikokuDisplay())
						{
							int iYColumnNumberPrev = iYColumnNumber - 1;
							CdYColSpec aCdYColSpecPrev = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberPrev);
							if (aCdYColSpecPrev.getEkiOrder() == iEkiOrder - 1)
							{
								strText = m_nameConnect;
							}
						}
					}
				}

				CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
				aRow.getCellCont()->insert(CdCsvCell(strText));
				pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
				iRowIndex++;
			}
			else if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_EkiPrevOperationNumber &&
				aCdYColSpec.getOperationIndex() == 0)
			{
				//0:空白、1:運番、2:経由なし、3:↓、4:分割、5:併合
				int iDisplayType = 0;
				vector<tstring> strOperationNumber;
				if (pCentDedRessya == NULL)
				{
					/**
						pCentDedRessya == NULLの場合は、
						分割+路線外終着または路線外始発+増結のどちらかのパターンです。
						なお、分割駅に対応する路線外終着表示欄、もしくは解結駅に対応する路線外始発表示欄がない場合は、この列車の描写は行わず、空行となります。
					*/
					if (aCustomizeJikokuhyouContent.iReleaseEkiOrder >= 0)
					{
						if (iEkiOrder > aCustomizeJikokuhyouContent.iReleaseEkiOrder &&
							iEkiOrder <= m_iOuterShuchakuDisplayEkiOrder[aCustomizeJikokuhyouContent.iReleaseEkiOrder])
						{
							iDisplayType = 2;//||
						}
					}
					else if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
					{
						if (iEkiOrder - 1 == aCustomizeJikokuhyouContent.iConnectEkiOrder)
						{
							CentDedEkiCont::CdDedEki aCdDedEkiPrev = muCdDedEki->get(iEkiOrder - 1);
							if (aCdDedEkiPrev.getJikokuhyouChakuJikokuDisplay() &&
								!aCdDedEkiPrev.getJikokuhyouHatsuJikokuDisplay())
							{
								int iYColumnNumberPrev = iYColumnNumber - 1;
								CdYColSpec aCdYColSpecPrev = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberPrev);
								if (aCdYColSpecPrev.getEkiOrder() == iEkiOrder - 1)
								{
									iDisplayType = 5;
								}
							}
						}
					}
				}
				else
				{
					int iValidSihatsuEki = pCentDedRessya->getValidSihatsuEki();
					int iValidSyuuchakuEki = pCentDedRessya->getValidSyuuchakuEki();
					if (iValidSihatsuEki == -1 || iValidSyuuchakuEki == -1)
					{
						iDisplayType = 0;
					}
					else if (iEkiOrder < iValidSihatsuEki)
					{
						if (iCurrentRessyaShihatsuEkiOrder >= 0)
						{
							iDisplayType = 2;//||
						}
						//iCurrentRessyaShihatsuEkiOrder < 0(1列車目)
						else if (aCustomizeJikokuhyouContent.iSihatsuEkiOrder >= -2 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] == iEkiOrder)
						{
							//路線外始発相当
							if (aCdDedEki.getJikokuhyouPrevOperationNumberDisplay() == 4)
							{
								iDisplayType = 1;//運番
								strOperationNumber = aCustomizeJikokuhyouContent.strPrevOperationNumber;

							}
							else if (aCdDedEki.getJikokuhyouPrevOperationNumberDisplay() == 1)
							{
								if (aCustomizeJikokuhyouContent.strPrevOperationNumber != pCentDedRessya->getOperationNumber(iEkiOrder))
								{
									iDisplayType = 1;//運番
									strOperationNumber = aCustomizeJikokuhyouContent.strPrevOperationNumber;
								}
							}
							else if (aCustomizeJikokuhyouContent.eEBeforeType == EBeforeAfterType::BeforeAfterType_ClassChange)
							{
								iDisplayType = 1;//運番
								strOperationNumber = aCustomizeJikokuhyouContent.strPrevOperationNumber;

							}
							else if (aCustomizeJikokuhyouContent.eEBeforeType == EBeforeAfterType::BeforeAfterType_PropertyChange &&
								aCdDedEki.getJikokuhyouPrevOperationNumberDisplay() == 3)
							{
								iDisplayType = 1;//運番
								strOperationNumber = aCustomizeJikokuhyouContent.strPrevOperationNumber;
							}
						}
						else if (aCustomizeJikokuhyouContent.iReleaseEkiOrder < iEkiOrder &&
							aCustomizeJikokuhyouContent.iReleaseEkiOrder >= 0)
						{
							//分割列車
							iDisplayType = 2;//||
						}
					}
					else if (iValidSihatsuEki == iEkiOrder)
					{
						//2列車目以降かつ、1列車目の終着駅との間に、経由なしがある場合
						if (iCurrentRessyaShihatsuEkiOrder >= 0 &&
							iCurrentRessyaShihatsuEkiOrder < iEkiOrder)
						{
							iDisplayType = 2;//||
						}
						else if (aCustomizeJikokuhyouContent.iSihatsuEkiOrder >= -2)
						{
							//路線外始発相当
							if (aCdDedEki.getJikokuhyouPrevOperationNumberDisplay() == 4)
							{
								iDisplayType = 1;//運番
								strOperationNumber = aCustomizeJikokuhyouContent.strPrevOperationNumber;

							}
							else if (aCdDedEki.getJikokuhyouPrevOperationNumberDisplay() == 1)
							{
								if (aCustomizeJikokuhyouContent.strPrevOperationNumber != pCentDedRessya->getOperationNumber(iEkiOrder))
								{
									iDisplayType = 1;//運番
									strOperationNumber = aCustomizeJikokuhyouContent.strPrevOperationNumber;
								}
							}
							else if (aCustomizeJikokuhyouContent.eEBeforeType == EBeforeAfterType::BeforeAfterType_ClassChange)
							{
								iDisplayType = 1;//運番
								strOperationNumber = aCustomizeJikokuhyouContent.strPrevOperationNumber;

							}
							else if (aCustomizeJikokuhyouContent.eEBeforeType == EBeforeAfterType::BeforeAfterType_PropertyChange &&
								aCdDedEki.getJikokuhyouPrevOperationNumberDisplay() == 3)
							{
								iDisplayType = 1;//運番
								strOperationNumber = aCustomizeJikokuhyouContent.strPrevOperationNumber;
							}
						}
					}
					else if (iValidSihatsuEki < iEkiOrder &&
						iEkiOrder < iValidSyuuchakuEki)
					{
						if (!pCentDedRessya->isRunBetweenNextEki(iEkiOrder - 1))
						{
							iDisplayType = 2;//||
						}
					}
					else if (iValidSyuuchakuEki < iEkiOrder)
					{
						if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= iEkiOrder)
						{
							//路線外終着
							iDisplayType = 2;//||
						}
						else if (aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder >= -2 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= iEkiOrder)
						{
							//路線外終着相当
							iDisplayType = 2;//||
						}
						else if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= iEkiOrder &&
							aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
						{
							iDisplayType = 2;//||
						}
					}

					/**
						前駅が増結駅の場合、この欄に↳印を表示することがあります
						(1)前駅が増結駅かつ有効な終着駅
						(2)前駅が着時刻又は発時刻のどちらかのみ表示→Ver2.05 前駅が着時刻のみ表示の場合のみに変更
						(3)この欄の直上が、前駅の項な場合。
						(4)この欄が運用番号の最上段の場合
					*/
					if (iEkiOrder - 1 == iValidSyuuchakuEki &&
						iEkiOrder - 1 == aCustomizeJikokuhyouContent.iConnectEkiOrder &&
						iValidSyuuchakuEki != -1)
					{
						CentDedEkiCont::CdDedEki aCdDedEkiPrev = muCdDedEki->get(iEkiOrder - 1);
						if (aCdDedEkiPrev.getJikokuhyouChakuJikokuDisplay() &&
							!aCdDedEkiPrev.getJikokuhyouHatsuJikokuDisplay())
						{
							int iYColumnNumberPrev = iYColumnNumber - 1;
							CdYColSpec aCdYColSpecPrev = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberPrev);
							if (aCdYColSpecPrev.getEkiOrder() == iEkiOrder - 1)
							{
								iDisplayType = 5;
							}
						}
					}
				}

				for (int idx = 0; idx < aCdDedEki.getJikokuhyouOperationNumberDisplayRows(); idx++)
				{
					tstring strText;
					if (iDisplayType == 1)
					{
						/**
							運用番号描写手順
							1.最初にstrOperationNumberに運番を読み込む
							2.運番が空の場合は空白を描写する
							3.空でない場合、表示段数の最下段以外の場合は、strOperationNumberの先頭要素を描写し、先頭要素を削除して次の段へ
							4.空でない場合、表示段数の最下段に到達したら、strOperationNumberに残っている要素を、'+'で連結して描写する。
						*/
						if (strOperationNumber.empty())
						{
							strText = _T("");
						}
						else if (idx == aCdDedEki.getJikokuhyouOperationNumberDisplayRows() - 1)
						{
							if (idx != 0)
							{
								strText = _T("+";)
							}
							strText += joinc('+', strOperationNumber);
						}
						else
						{
							if (idx != 0)
							{
								strText = _T("+";)
							}
							strText += strOperationNumber.front();
							strOperationNumber.erase(strOperationNumber.begin());
						}
					}
					else if (iDisplayType == 2)
					{
						strText = m_nameKeiyunasi;
					}
					else if (iDisplayType == 3)
					{
						strText = _T("↓";)
					}
					else if (iDisplayType == 4 &&
						idx == aCdDedEki.getJikokuhyouOperationNumberDisplayRows() - 1)
					{
						strText = m_nameRelease;
					}
					else if (iDisplayType == 5 &&
						idx == 0)
					{
						strText = m_nameConnect;
					}

					CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
					aRow.getCellCont()->insert(CdCsvCell(strText));
					pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
					iRowIndex++;
				}

			}
			else if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_EkiPrevRessyasyubetsu)
			{
				tstring strRessyasyubetsu;
				if (pCentDedRessya == NULL || !pCentDedRessya->isNull())
				{
					strRessyasyubetsu = pCentDedRessyasyubetsu->getRyakusyou();
				}

				tstring strText;
				if (pCentDedRessya == NULL)
				{
					/**
						pCentDedRessya == NULLの場合は、
						分割+路線外終着または路線外始発+増結のどちらかのパターンです。
						なお、分割駅に対応する路線外終着表示欄、もしくは解結駅に対応する路線外始発表示欄がない場合は、この列車の描写は行わず、空行となります。
					*/
					if (aCustomizeJikokuhyouContent.iReleaseEkiOrder >= 0)
					{
						if (iEkiOrder > aCustomizeJikokuhyouContent.iReleaseEkiOrder &&
							iEkiOrder <= m_iOuterShuchakuDisplayEkiOrder[aCustomizeJikokuhyouContent.iReleaseEkiOrder])
						{
							strText = m_nameKeiyunasi;//"||"

						}
					}
					else if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
					{
						if (iEkiOrder - 1 == aCustomizeJikokuhyouContent.iConnectEkiOrder)
						{
							CentDedEkiCont::CdDedEki aCdDedEkiPrev = muCdDedEki->get(iEkiOrder - 1);
							if (aCdDedEkiPrev.getJikokuhyouChakuJikokuDisplay() &&
								!aCdDedEkiPrev.getJikokuhyouHatsuJikokuDisplay())
							{
								int iYColumnNumberPrev = iYColumnNumber - 1;
								CdYColSpec aCdYColSpecPrev = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberPrev);
								if (aCdYColSpecPrev.getEkiOrder() == iEkiOrder - 1)
								{
									strText = m_nameConnect;
								}
							}
						}
					}
				}
				else
				{
					int iValidSihatsuEki = pCentDedRessya->getValidSihatsuEki();
					int iValidSyuuchakuEki = pCentDedRessya->getValidSyuuchakuEki();
					if (iValidSihatsuEki == -1 || iValidSyuuchakuEki == -1)
					{
						strText = _T("");
					}
					else if (iEkiOrder < iValidSihatsuEki)
					{
						/*
							始発駅より前の場合
							1.二列車目
							→前列車の終着駅では、この項は前列車の責任範囲なので、必然的に前列車終着駅とこの列車の始発駅の"間"になる→経由無し
							2.路線外始発
							→大前提として、この項がある＝この駅には路線外始発表示欄がある、ということになる
							→この項より上にある路線外始発表示欄が使われることはない(少なくともこの項の下にある当駅の表示欄)ので、経由なしを表示することはない
							→この項は常時空白でOK(要検討)
							3.路線外始発相当
							→路線外始発と上記前提は同じ、よって空白OR情報表記
						*/
						if (iCurrentRessyaShihatsuEkiOrder >= 0)
						{
							//2列車目以降で、始発駅より前の場合は、経由なしになります
							strText = m_nameKeiyunasi;//"||"
						}
						//iCurrentRessyaShihatsuEkiOrder < 0(1列車目)
						else if (aCustomizeJikokuhyouContent.iSihatsuEkiOrder >= -2 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] == iEkiOrder)
						{
							//路線外始発相当で、この駅が路線外始発表示駅の場合
							const CentDedRessyasyubetsu* pCentDedRessyasyubetsuPrev = pCentDedRessyasyubetsuContGet
								->get(aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex);
							if (bDisplayParentSyubetsu && pCentDedRessyasyubetsuPrev->getParentSyubetsuIndex() >= 0)
							{
								pCentDedRessyasyubetsuPrev = pCentDedRessyasyubetsuContGet
									->get(pCentDedRessyasyubetsuPrev->getParentSyubetsuIndex());
							}

							strRessyasyubetsu = pCentDedRessyasyubetsuPrev->getRyakusyou();

							if (aCdDedEki.getJikokuhyouPrevRessyaSyubetsuDisplay() == 3)
							{
								strText = strRessyasyubetsu;
							}
							else if (aCustomizeJikokuhyouContent.eEBeforeType == EBeforeAfterType::BeforeAfterType_ClassChange)
							{
								strText = strRessyasyubetsu;
							}
							else if (aCustomizeJikokuhyouContent.eEBeforeType == EBeforeAfterType::BeforeAfterType_PropertyChange &&
								aCdDedEki.getJikokuhyouPrevRessyaSyubetsuDisplay() == 2)
							{
								strText = strRessyasyubetsu;
							}
						}

						else if (aCustomizeJikokuhyouContent.iReleaseEkiOrder < iEkiOrder &&
							aCustomizeJikokuhyouContent.iReleaseEkiOrder >= 0)
						{
							//分割列車
							strText = m_nameKeiyunasi;//"||"
						}
					}
					else if (iValidSihatsuEki == iEkiOrder)
					{
						//2列車目以降かつ、1列車目の終着駅との間に、経由なしがある場合
						if (iCurrentRessyaShihatsuEkiOrder >= 0 &&
							iCurrentRessyaShihatsuEkiOrder < iEkiOrder)
						{
							strText = m_nameKeiyunasi;//"||"
						}
						//路線外始発相当かつ、始発駅にこの項がある場合は、路線外始発表示も当然この駅にあるので、前列車接続タイプに基づいて表示を行う
						else if (aCustomizeJikokuhyouContent.iSihatsuEkiOrder >= -2)
						{
							const CentDedRessyasyubetsu* pCentDedRessyasyubetsuPrev = pCentDedRessyasyubetsuContGet
								->get(aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex);
							if (bDisplayParentSyubetsu && pCentDedRessyasyubetsuPrev->getParentSyubetsuIndex() >= 0)
							{
								pCentDedRessyasyubetsuPrev = pCentDedRessyasyubetsuContGet
									->get(pCentDedRessyasyubetsuPrev->getParentSyubetsuIndex());
							}

							strRessyasyubetsu = pCentDedRessyasyubetsuPrev->getRyakusyou();

							if (aCdDedEki.getJikokuhyouPrevRessyaSyubetsuDisplay() == 3)
							{
								strText = strRessyasyubetsu;
							}
							else if (aCustomizeJikokuhyouContent.eEBeforeType == EBeforeAfterType::BeforeAfterType_ClassChange)
							{
								strText = strRessyasyubetsu;
							}
							else if (aCustomizeJikokuhyouContent.eEBeforeType == EBeforeAfterType::BeforeAfterType_PropertyChange &&
								aCdDedEki.getJikokuhyouPrevRessyaSyubetsuDisplay() == 2)
							{
								strText = strRessyasyubetsu;
							}
						}
					}
					else if (iValidSihatsuEki < iEkiOrder &&
						iEkiOrder < iValidSyuuchakuEki)
					{
						if (!pCentDedRessya->isRunBetweenNextEki(iEkiOrder - 1))
						{
							strText = m_nameKeiyunasi;
						}
					}
					else if (iValidSyuuchakuEki < iEkiOrder)
					{
						if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= iEkiOrder)
						{
							//路線外終着
							strText = m_nameKeiyunasi;
						}
						else if (aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder >= -2 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= iEkiOrder)
						{
							//路線外終着相当
							strText = m_nameKeiyunasi;//"||"

						}
						else if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= iEkiOrder &&
							aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
						{
							strText = m_nameKeiyunasi;//"||"
						}
					}
					/**
						前駅が増結駅の場合、この欄に↳印を表示することがあります
						(1)前駅が増結駅かつ有効な終着駅
						(2)前駅が着時刻又は発時刻のどちらかのみ表示→Ver2.05 前駅が着時刻のみ表示の場合のみに変更
						(3)この欄の直上が、前駅の項な場合。
					*/
					if (iEkiOrder - 1 == iValidSyuuchakuEki &&
						iEkiOrder - 1 == aCustomizeJikokuhyouContent.iConnectEkiOrder &&
						iValidSyuuchakuEki != -1)
					{
						CentDedEkiCont::CdDedEki aCdDedEkiPrev = muCdDedEki->get(iEkiOrder - 1);
						if (aCdDedEkiPrev.getJikokuhyouChakuJikokuDisplay() &&
							!aCdDedEkiPrev.getJikokuhyouHatsuJikokuDisplay())
						{
							int iYColumnNumberPrev = iYColumnNumber - 1;
							CdYColSpec aCdYColSpecPrev = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberPrev);
							if (aCdYColSpecPrev.getEkiOrder() == iEkiOrder - 1)
							{
								strText = m_nameConnect;
							}
						}
					}
				}

				CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
				aRow.getCellCont()->insert(CdCsvCell(strText));
				pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
				iRowIndex++;

			}
			else if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_EkiRessyamei)
			{
				tstring strText = _T("");
				tstring strText2 = _T("");
				tstring strText3 = _T("");
				if (pCentDedRessya == NULL)
				{
					/**
						pCentDedRessya == NULLの場合は、
						分割+路線外終着または路線外始発+増結のどちらかのパターンです。
						なお、分割駅に対応する路線外終着表示欄、もしくは解結駅に対応する路線外始発表示欄がない場合は、この列車の描写は行わず、空行となります。
					*/
					if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
					{
						if (iEkiOrder - 1 == aCustomizeJikokuhyouContent.iConnectEkiOrder)
						{
							CentDedEkiCont::CdDedEki aCdDedEkiPrev = muCdDedEki->get(iEkiOrder - 1);
							if (aCdDedEkiPrev.getJikokuhyouChakuJikokuDisplay() &&
								!aCdDedEkiPrev.getJikokuhyouHatsuJikokuDisplay())
							{
								int iYColumnNumberPrev = iYColumnNumber - 1;
								CdYColSpec aCdYColSpecPrev = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberPrev);
								if (aCdYColSpecPrev.getEkiOrder() == iEkiOrder - 1)
								{
									strText = m_nameConnect;
								}
							}
						}
					}
				}
				else
				{
					int iValidSihatsuEki = pCentDedRessya->getValidSihatsuEki();
					int iValidSyuuchakuEki = pCentDedRessya->getValidSyuuchakuEki();
					if (iValidSihatsuEki == -1 || iValidSyuuchakuEki == -1)
					{
						strText = _T("");
						strText2 = _T("");
						strText3 = _T("");
					}
					else if (iEkiOrder < iValidSihatsuEki)
					{
						if (iCurrentRessyaShihatsuEkiOrder < 0 &&
							aCustomizeJikokuhyouContent.iSihatsuEkiOrder >= -2 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] == iEkiOrder)
						{
							//路線外始発相当で、この駅が路線外始発表示駅の場合
							if (aCdDedEki.getJikokuhyouPrevRessyameiDisplay() == 3)
							{
								strText = aCustomizeJikokuhyouContent.strPrevRessyamei;
								strText2 = aCustomizeJikokuhyouContent.strPrevGousuu;
								if (!strText2.empty())
								{
									strText3 = m_nameGou;
								}
							}
							else if (aCustomizeJikokuhyouContent.eEBeforeType == EBeforeAfterType::BeforeAfterType_ClassChange)
							{
								strText = aCustomizeJikokuhyouContent.strPrevRessyamei;
								strText2 = aCustomizeJikokuhyouContent.strPrevGousuu;
								if (!strText2.empty())
								{
									strText3 = m_nameGou;
								}
							}
							else if (aCustomizeJikokuhyouContent.eEBeforeType == EBeforeAfterType::BeforeAfterType_PropertyChange &&
								aCdDedEki.getJikokuhyouPrevRessyameiDisplay() == 2)
							{
								strText = aCustomizeJikokuhyouContent.strPrevRessyamei;
								strText2 = aCustomizeJikokuhyouContent.strPrevGousuu;
								if (!strText2.empty())
								{
									strText3 = m_nameGou;
								}
							}
						}
					}
					else if (iValidSihatsuEki == iEkiOrder)
					{
						//路線外始発相当かつ、始発駅にこの項がある場合は、路線外始発表示も当然この駅にあるので、前列車接続タイプに基づいて表示を行う
						if (aCustomizeJikokuhyouContent.iSihatsuEkiOrder >= -2)
						{
							if (aCdDedEki.getJikokuhyouPrevRessyameiDisplay() == 3)
							{
								strText = aCustomizeJikokuhyouContent.strPrevRessyamei;
								strText2 = aCustomizeJikokuhyouContent.strPrevGousuu;
								if (!strText2.empty())
								{
									strText3 = m_nameGou;
								}
							}
							else if (aCustomizeJikokuhyouContent.eEBeforeType == EBeforeAfterType::BeforeAfterType_ClassChange)
							{
								strText = aCustomizeJikokuhyouContent.strPrevRessyamei;
								strText2 = aCustomizeJikokuhyouContent.strPrevGousuu;
								if (!strText2.empty())
								{
									strText3 = m_nameGou;
								}
							}
							else if (aCustomizeJikokuhyouContent.eEBeforeType == EBeforeAfterType::BeforeAfterType_PropertyChange &&
								aCdDedEki.getJikokuhyouPrevRessyameiDisplay() == 2)
							{
								strText = aCustomizeJikokuhyouContent.strPrevRessyamei;
								strText2 = aCustomizeJikokuhyouContent.strPrevGousuu;
								if (!strText2.empty())
								{
									strText3 = m_nameGou;
								}
							}
						}
					}

					/**
						前駅が増結駅の場合、この欄に↳印を表示することがあります
						(1)前駅が増結駅かつ有効な終着駅
						(2)前駅が着時刻又は発時刻のどちらかのみ表示→Ver2.05 前駅が着時刻のみ表示の場合のみに変更
						(3)この欄の直上が、前駅の項な場合。
					*/
					if (iEkiOrder - 1 == iValidSyuuchakuEki &&
						iEkiOrder - 1 == aCustomizeJikokuhyouContent.iConnectEkiOrder &&
						iValidSyuuchakuEki != -1)
					{
						CentDedEkiCont::CdDedEki aCdDedEkiPrev = muCdDedEki->get(iEkiOrder - 1);
						if (aCdDedEkiPrev.getJikokuhyouChakuJikokuDisplay() &&
							!aCdDedEkiPrev.getJikokuhyouHatsuJikokuDisplay())
						{
							int iYColumnNumberPrev = iYColumnNumber - 1;
							CdYColSpec aCdYColSpecPrev = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberPrev);
							if (aCdYColSpecPrev.getEkiOrder() == iEkiOrder - 1)
							{
								strText = m_nameConnect;
							}
						}
					}
				}

				CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
				aRow.getCellCont()->insert(CdCsvCell(strText));
				pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
				iRowIndex++;
				CdCsvRow	aRow2 = pCdCsvDocument->getRowCont()->get(iRowIndex);
				aRow2.getCellCont()->insert(CdCsvCell(strText2));
				pCdCsvDocument->getRowCont()->set(aRow2, iRowIndex);
				iRowIndex++;
				CdCsvRow	aRow3 = pCdCsvDocument->getRowCont()->get(iRowIndex);
				aRow3.getCellCont()->insert(CdCsvCell(strText3));
				pCdCsvDocument->getRowCont()->set(aRow3, iRowIndex);
				iRowIndex++;

			}
		}
	}

	//＜2.11＞[列1="備考" AND 列2=""]の列　備考列
	if (iRv >= 0)
	{
		CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
		if (pCentDedRessya == NULL)
		{
			aRow.getCellCont()->insert(CdCsvCell());
		}
		else
		{
			aRow.getCellCont()->insert(CdCsvCell(pCentDedRessya->getBikou()));
		}
		pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
	}
	return iRv ;
}

int CconvJikokuhyouCustomizeCsv::encode_AddRessyaNull(
	CdCsvDocument* pCdCsvDocument,
	const bool bDisplayShihatsuShuchakuEkimei,
	const bool bDisplayRessyamei,
	const int iEnableOperation)
{
	int iRv = 0 ;
	// --------------------------------

	int iRowIndex = CSVROWINDEX_Ressyabangou;
	//＜2.5＞5行目 <列車番号>
	if ( iRv >= 0 )
	{
		CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex) ;
		aRow.getCellCont()->insert( CdCsvCell() ) ;
		pCdCsvDocument->getRowCont()->set( aRow , iRowIndex) ;
		iRowIndex++;
	}

	//＜2.6＞ <運用番号>
	if (iRv >= 0 && iEnableOperation>1)
	{
		CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
		aRow.getCellCont()->insert(CdCsvCell());
		pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
		iRowIndex++;
	}

	//＜2.6＞6行目 <列車種別>
	if ( iRv >= 0 )
	{
		CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex) ;
		aRow.getCellCont()->insert( CdCsvCell() ) ;
		pCdCsvDocument->getRowCont()->set( aRow , iRowIndex) ;
		iRowIndex++;
	}

	//＜2.7＞7行目 <列車名>
	if ( iRv >= 0 && bDisplayRessyamei)
	{
		CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex) ;
		aRow.getCellCont()->insert( CdCsvCell() ) ;
		pCdCsvDocument->getRowCont()->set( aRow , iRowIndex) ;
		iRowIndex++;
	}

	//＜2.8＞8行目 <号数>
	if ( iRv >= 0 && bDisplayRessyamei)
	{
		CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex) ;
		aRow.getCellCont()->insert( CdCsvCell() ) ;
		pCdCsvDocument->getRowCont()->set( aRow , iRowIndex) ;
		iRowIndex++;
	}
	//＜2.9＞9行目 <号表示>
	if ( iRv >= 0 && bDisplayRessyamei)
	{
		CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex) ;
		aRow.getCellCont()->insert( CdCsvCell() ) ;
		pCdCsvDocument->getRowCont()->set( aRow , iRowIndex) ;
		iRowIndex++;
	}

	//＜2.11＞ <始発駅名>
	if (iRv >= 0 && bDisplayShihatsuShuchakuEkimei)
	{
		CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
		aRow.getCellCont()->insert(CdCsvCell());
		pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
		iRowIndex++;
	}
	
	//＜2.13＞ <終着駅名>
	if (iRv >= 0 && bDisplayShihatsuShuchakuEkimei)
	{
		CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
		aRow.getCellCont()->insert(CdCsvCell());
		pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
		iRowIndex++;
	}

	//＜2.16＞10行目～ 駅時刻
	
	//contiJikokuOrderOfJikokuhyouIndex = 
	//	 contiJikokuOrderOfJjikokuhyouIndex[<時刻表Index>]=<時刻Order> の法則を持ちます。
	//	要素の数は、時刻表の列数です。

	if ( iRv >= 0 )
	{
		for (int idx = m_CdYColSpecCont.getColumnNumber_Ekijikoku_begin();
			idx < m_CdYColSpecCont.getColumnNumber_Ekijikoku_end(); idx++)
		{
			CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex) ;
			aRow.getCellCont()->insert( CdCsvCell(  ) ) ;
			pCdCsvDocument->getRowCont()->set( aRow , iRowIndex) ;
			iRowIndex++;
		}
	}
	//＜2.18＞[列1="備考" AND 列2=""]の列　備考列
	if ( iRv >= 0 )
	{
			CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex) ;
			aRow.getCellCont()->insert( CdCsvCell() ) ;
			pCdCsvDocument->getRowCont()->set( aRow , iRowIndex) ;
	}
	return iRv ;
}

	// ********************************
	//	コンストラクタ
	// ********************************
CconvJikokuhyouCustomizeCsv::CconvJikokuhyouCustomizeCsv(
		const tstring& nameKudari ,
		const tstring& nameNobori ,
		const tstring& nameRessyabangou ,
		const tstring& nameRessyasyubetsu ,
		const tstring& nameRessyamei ,
		const tstring& nameGousuu ,
		const tstring& nameGou ,
		const tstring& nameBikou ,
		const tstring& nameChaku ,
		const tstring& nameHatsu ,
		const tstring& nameTsuuka ,
		const tstring& nameKeiyunasi,
		const tstring& nameTrack,
		const tstring& nameOperationNumber,
		const tstring& nameShihatsuEkimei,
		const tstring& nameOperation_Shihatsu,
		const tstring& nameShuchakuEkimei,
		const tstring& nameOperation_Shuchaku,
		const tstring& nameJikoku,
		const tstring& nameBeforeOperation,
		const tstring& nameAfterOperation) :
	m_nameKudari( nameKudari ) , 
	m_nameNobori( nameNobori ) ,
	m_nameRessyabangou( nameRessyabangou ),
	m_nameRessyasyubetsu( nameRessyasyubetsu ),
	m_nameRessyamei( nameRessyamei ),
	m_nameGousuu( nameGousuu ),
	m_nameGou( nameGou ),
	m_nameBikou( nameBikou ) ,
	m_nameChaku( nameChaku ) ,
	m_nameHatsu( nameHatsu ) ,
	m_nameTsuuka( nameTsuuka ) ,
	m_nameKeiyunasi( nameKeiyunasi ),
	m_nameTrack(nameTrack),
	m_nameOperationNumber(nameOperationNumber),
	m_nameShihatsuEkimei(nameShihatsuEkimei),
	m_nameOperation_Shihatsu(nameOperation_Shihatsu),
	m_nameShuchakuEkimei(nameShuchakuEkimei),
	m_nameOperation_Shuchaku(nameOperation_Shuchaku),
	m_nameJikoku(nameJikoku),
	m_nameBeforeOperation(nameBeforeOperation),
	m_nameAfterOperation(nameAfterOperation)
{
}


	// ********************************
	//@name	CconvJikokuhyouCustomizeCsv
	// ********************************
int CconvJikokuhyouCustomizeCsv::encode( 
		const CentDedRosen& aCentDedRosen , 
		int iDiaIndex , 
		ERessyahoukou eRessyahoukou ,
		int iRessyaIndex , int iRessyaCount ,
		const bool bDisplayTsuukaEkiJikoku,
		const bool bDisplaySecondEkiJikoku,
		const bool bDisplayColonEkiJikoku,
		const bool bDisplayShihatsuShuchakuEkimei,
		const bool bDisplayParentSyubetsu,
		const bool bDisplayRessyamei,
		const int iEnableOperation,
		const int iSecondRoundChaku,
		const int iSecondRoundHatsu,
		const bool bDisplay2400,
		const int iOperationNumberRows,
		CdCsvDocument* pCdCsvDocument ) 
{
	int iRv = 0 ;
	
	const CentDedEkiCont* pCentDedEkiCont = NULL ;
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki = NULL ;
	const Mu<const CentDedRessyasyubetsu*>* pCentDedRessyasyubetsuContGet = NULL ;
	const CentDedDia* pCentDedDia = NULL ;
	const Mu<const CentDedRessya*>* pCentDedRessyaCont = NULL ;

	/**
		各駅を始発・終着とする列車が、路線外始発終着もしくは路線外相当の場合に、
		路線外始発・終着駅・時刻を表示する駅がどこにあるかを保持します。
		-1の場合は、その駅より始発側(終着側)に、路線外始発(終着)を表示する駅がないことを意味します。
	*/
	deque<int> m_iOuterShihatsuDisplayEkiOrder;
	deque<int> m_iOuterShuchakuDisplayEkiOrder;

	// --------------------------------
	//	オブジェクトCdCsvDocument をクリア
	// --------------------------------
	if ( iRv >= 0 )
	{
		pCentDedEkiCont = aCentDedRosen.getCentDedEkiCont() ;
		muCdDedEki = aCentDedRosen.getCentDedEkiCont()
			->getMuPtr( eRessyahoukou ) ;
		pCentDedRessyasyubetsuContGet = aCentDedRosen.getCentDedRessyasyubetsuCont()->getMuPtr() ; 
		pCentDedDia = aCentDedRosen.getCentDedDiaCont()->getMuPtr()->get( iDiaIndex ) ;
		if ( pCentDedDia == NULL )
		{
			iRv = -1 ;	//	iDiaIndex が不正です。
		}

		int iOuterShihatsuDisplayEkiOrder = -1;
		for (int iEkiOrder = 0; iEkiOrder < muCdDedEki->size(); iEkiOrder++)
		{
			CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);
			if (aCdDedEki.getJikokuhyouOuterSihatsuDisplay())
			{
				iOuterShihatsuDisplayEkiOrder = iEkiOrder;

			}
			m_iOuterShihatsuDisplayEkiOrder.push_back(iOuterShihatsuDisplayEkiOrder);
		}

		int iOuterShuchakuDisplayEkiOrder = -1;
		for (int iEkiOrder = muCdDedEki->size() - 1; iEkiOrder >= 0; iEkiOrder--)
		{
			CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);
			if (aCdDedEki.getJikokuhyouOuterShuchakuDisplay())
			{
				iOuterShuchakuDisplayEkiOrder = iEkiOrder;

			}
			m_iOuterShuchakuDisplayEkiOrder.push_front(iOuterShuchakuDisplayEkiOrder);
		}
	}
	const vector<CustomizeJikokuhyouContent>& contCustomizeRessyaIndex = pCentDedDia->getcontCustomizeRessyaIndex(eRessyahoukou);
	if ( iRv >= 0 )
	{
		pCentDedRessyaCont = pCentDedDia->getCentDedRessyaCont( eRessyahoukou )->getMuPtr() ;
	}
	//pCentDedRessyaCont = 列車のコンテナ
	if ( iRv >= 0 )
	{
		if ( !( 0 <= iRessyaIndex && iRessyaIndex < (int)contCustomizeRessyaIndex.size() )
			&& iRessyaIndex != 0 )
		{
			iRv = -2 ;	//	iRessyaIndex が不正です。
		}
	}
	if ( iRv >= 0 )
	{
		if ( iRessyaCount == INT_MAX )
		{
			iRessyaCount = pCentDedRessyaCont->size() - iRessyaIndex ;
		}
		if ( !( 0 <= iRessyaIndex + iRessyaCount && 
			iRessyaIndex + iRessyaCount <= (int)contCustomizeRessyaIndex.size()) )
		{
			iRv = -3 ;	//	iRessyaCount が不正です。
		}
	}

	// --------------------------------
	//	CdCsvDocument をクリア
	// --------------------------------
	if ( iRv >= 0 )
	{
		pCdCsvDocument->getRowCont()->erase( 0 , INT_MAX ) ;
	}

	// --------------------------------
	//	ヘッダ列
	// --------------------------------
	//	1行目 FileType行
	if ( iRv >= 0 )
	{
		CdCsvRow	aRow ;
		aRow.getCellCont()->insert( CdCsvCell( nameFileType ) ) ;
		aRow.getCellCont()->insert( CdCsvCell( nameFileTypeValue ) ) ;
		pCdCsvDocument->getRowCont()->insert( aRow ) ;
	}	
	//	2行目 DiaName行
	if ( iRv >= 0 )
	{
		CdCsvRow	aRow ;
		aRow.getCellCont()->insert( CdCsvCell( pCentDedDia->getName() ) ) ;
		pCdCsvDocument->getRowCont()->insert( aRow ) ;
	}	
	//＜2.3＞ 3行目 <下り,上り>
	if ( iRv >= 0 )
	{
		tstring strValue ;
		if ( eRessyahoukou == Ressyahoukou_Kudari )
		{
			strValue = m_nameKudari ;
		}
		else
		{
			strValue = m_nameNobori ;
		}
		strValue += _T("カスタマイズ");
		
		CdCsvRow	aRow ;
		aRow.getCellCont()->insert( CdCsvCell( strValue ) ) ;
		pCdCsvDocument->getRowCont()->insert( aRow ) ;
	}
	//＜2.4＞4行目 
	if ( iRv >= 0 )
	{
		CdCsvRow	aRow ;
		pCdCsvDocument->getRowCont()->insert( aRow ) ;
	}

	// --------------------------------
	//	時刻表部分の左側2列
	// --------------------------------
	//＜2.5＞5行目 <列車番号>
	if ( iRv >= 0 )
	{
		CdCsvRow	aRow ;
		aRow.getCellCont()->insert( CdCsvCell( m_nameRessyabangou ) ) ;
		aRow.getCellCont()->insert( CdCsvCell( ) ) ;
		pCdCsvDocument->getRowCont()->insert( aRow ) ;
	}

	//＜2.6＞6行目 <運用番号>
	if (iRv >= 0 && iEnableOperation > 1)
	{
		CdCsvRow	aRow;
		aRow.getCellCont()->insert(CdCsvCell(m_nameOperationNumber));
		aRow.getCellCont()->insert(CdCsvCell());
		pCdCsvDocument->getRowCont()->insert(aRow);
		for (int idx = 1; idx < iOperationNumberRows; idx++)
		{
			CdCsvRow	aRow2;
			aRow2.getCellCont()->insert(CdCsvCell());
			aRow2.getCellCont()->insert(CdCsvCell());
			pCdCsvDocument->getRowCont()->insert(aRow2);

		}
	}

	//＜2.7＞7行目 <列車種別>
	if ( iRv >= 0 )
	{
		CdCsvRow	aRow ;
		aRow.getCellCont()->insert( CdCsvCell( m_nameRessyasyubetsu ) ) ;
		aRow.getCellCont()->insert( CdCsvCell( ) ) ;
		pCdCsvDocument->getRowCont()->insert( aRow ) ;
	}

	//＜2.8＞8行目 <列車名>
	if ( iRv >= 0 && bDisplayRessyamei)
	{
		CdCsvRow	aRow ;
		aRow.getCellCont()->insert( CdCsvCell( m_nameRessyamei ) ) ;
		aRow.getCellCont()->insert( CdCsvCell( ) ) ;
		pCdCsvDocument->getRowCont()->insert( aRow ) ;
	}

	//＜2.9＞9行目 <号数>
	if ( iRv >= 0 && bDisplayRessyamei)
	{
		CdCsvRow	aRow ;
		aRow.getCellCont()->insert( CdCsvCell( m_nameGousuu ) ) ;
		aRow.getCellCont()->insert( CdCsvCell( ) ) ;
		pCdCsvDocument->getRowCont()->insert( aRow ) ;
	}
	//＜2.10＞10行目 <号表示>
	if ( iRv >= 0 && bDisplayRessyamei)
	{
		CdCsvRow	aRow ;
		aRow.getCellCont()->insert( CdCsvCell() ) ;
		aRow.getCellCont()->insert( CdCsvCell() ) ;
		pCdCsvDocument->getRowCont()->insert( aRow ) ;
	}
	//＜2.11＞11行目 <始発駅名>
	if (iRv >= 0 && bDisplayShihatsuShuchakuEkimei)
	{
		CdCsvRow	aRow;
		aRow.getCellCont()->insert(CdCsvCell(m_nameShihatsuEkimei));
		aRow.getCellCont()->insert(CdCsvCell());
		pCdCsvDocument->getRowCont()->insert(aRow);
	}
	//＜2.13＞13行目 <終着駅名>
	if (iRv >= 0 && bDisplayShihatsuShuchakuEkimei)
	{
		CdCsvRow	aRow;
		aRow.getCellCont()->insert(CdCsvCell(m_nameShuchakuEkimei));
		aRow.getCellCont()->insert(CdCsvCell());
		pCdCsvDocument->getRowCont()->insert(aRow);
	}
	//始発駅・終着駅
	//路線外始発
	//前後作業
	//＜2.16＞16行目～ 駅時刻
	if (iRv >= 0)
	{
		m_CdYColSpecCont =
			CdYColSpecCont(
				pCentDedEkiCont, eRessyahoukou,
				false, //AllJikoku
				true, //Customize
				false, //ShihatsuShuchakuEkimei
				true,  //Ressyamei
				iEnableOperation, //Operation
				false, //OuterShihatsu
				false,//OuterSyuchaku
				1,
				false);

		for (int idx = m_CdYColSpecCont.getColumnNumber_Ekijikoku_begin();
			idx < m_CdYColSpecCont.getColumnNumber_Ekijikoku_end(); idx++)
		{
			CdYColSpec aCdYColSpec = m_CdYColSpecCont.ColumnNumberToSpec(idx);

			CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(aCdYColSpec.getEkiOrder());

			tstring	strEkimei = aCdDedEki.getEkimei();
			tstring	strChakuHatsu;
			if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_Ekijikoku_Chaku)
			{
				strChakuHatsu = m_nameChaku;
				CdCsvRow	aRow;
				aRow.getCellCont()->insert(CdCsvCell(strEkimei));
				aRow.getCellCont()->insert(CdCsvCell(strChakuHatsu));
				pCdCsvDocument->getRowCont()->insert(aRow);
			}
			else if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_Ekijikoku_Hatsu)
			{
				strChakuHatsu = m_nameHatsu;
				CdCsvRow	aRow;
				aRow.getCellCont()->insert(CdCsvCell(strEkimei));
				aRow.getCellCont()->insert(CdCsvCell(strChakuHatsu));
				pCdCsvDocument->getRowCont()->insert(aRow);
			}
			else if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_Track)
			{
				strChakuHatsu = m_nameTrack;
				CdCsvRow	aRow;
				aRow.getCellCont()->insert(CdCsvCell(strEkimei));
				aRow.getCellCont()->insert(CdCsvCell(strChakuHatsu));
				pCdCsvDocument->getRowCont()->insert(aRow);
			}
			else if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_EkiRessyabangou)
			{
				CdCsvRow	aRow;
				aRow.getCellCont()->insert(CdCsvCell(m_nameRessyabangou));
				aRow.getCellCont()->insert(CdCsvCell());
				pCdCsvDocument->getRowCont()->insert(aRow);
			}
			else if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_EkiOperationNumber)
			{
				CdCsvRow	aRow;
				if (aCdYColSpec.getOperationIndex() == 0)
				{
					aRow.getCellCont()->insert(CdCsvCell(m_nameOperationNumber));
				}
				else
				{
					aRow.getCellCont()->insert(CdCsvCell());
				}
				aRow.getCellCont()->insert(CdCsvCell());
				pCdCsvDocument->getRowCont()->insert(aRow);
			}
			else if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_EkiRessyasyubetsu)
			{
				CdCsvRow	aRow;
				aRow.getCellCont()->insert(CdCsvCell(m_nameRessyasyubetsu));
				aRow.getCellCont()->insert(CdCsvCell());
				pCdCsvDocument->getRowCont()->insert(aRow);
			}
			else if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_EkiRessyamei)
			{
				CdCsvRow	aRow;
				aRow.getCellCont()->insert(CdCsvCell(m_nameRessyamei));
				aRow.getCellCont()->insert(CdCsvCell());
				pCdCsvDocument->getRowCont()->insert(aRow);

				CdCsvRow	aRow2;
				aRow.getCellCont()->insert(CdCsvCell(m_nameGousuu));
				aRow.getCellCont()->insert(CdCsvCell());
				pCdCsvDocument->getRowCont()->insert(aRow2);

				CdCsvRow	aRow3;
				aRow.getCellCont()->insert(CdCsvCell());
				aRow.getCellCont()->insert(CdCsvCell());
				pCdCsvDocument->getRowCont()->insert(aRow3);
			}
			else if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_EkiOuter_Shihatsu1)
			{
				CdCsvRow	aRow;
				aRow.getCellCont()->insert(CdCsvCell(m_nameShihatsuEkimei));
				aRow.getCellCont()->insert(CdCsvCell());
				pCdCsvDocument->getRowCont()->insert(aRow);
				CdCsvRow	aRow2;
				aRow2.getCellCont()->insert(CdCsvCell(m_nameJikoku));
				aRow2.getCellCont()->insert(CdCsvCell());
				pCdCsvDocument->getRowCont()->insert(aRow2);
			}
			else if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_EkiOuter_Shuchaku1)
			{
				CdCsvRow	aRow;
				aRow.getCellCont()->insert(CdCsvCell(m_nameShuchakuEkimei));
				aRow.getCellCont()->insert(CdCsvCell());
				pCdCsvDocument->getRowCont()->insert(aRow);
				CdCsvRow	aRow2;
				aRow2.getCellCont()->insert(CdCsvCell(m_nameJikoku));
				aRow2.getCellCont()->insert(CdCsvCell());
				pCdCsvDocument->getRowCont()->insert(aRow2);
			}
			else if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_Ekijikoku_Nyuusen)
			{
				CdCsvRow	aRow;
				aRow.getCellCont()->insert(CdCsvCell(m_nameNyuusen));
				aRow.getCellCont()->insert(CdCsvCell());
				pCdCsvDocument->getRowCont()->insert(aRow);
			}
			else if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_EkiPrevRessyabangou)
			{
				CdCsvRow	aRow;
				aRow.getCellCont()->insert(CdCsvCell(m_namePrevRessyabangou));
				aRow.getCellCont()->insert(CdCsvCell());
				pCdCsvDocument->getRowCont()->insert(aRow);
			}
			else if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_EkiPrevOperationNumber)
			{
				CdCsvRow	aRow;
				if (aCdYColSpec.getOperationIndex() == 0)
				{
					aRow.getCellCont()->insert(CdCsvCell(m_namePrevOperationNumber));
				}
				else
				{
					aRow.getCellCont()->insert(CdCsvCell());
				}
				aRow.getCellCont()->insert(CdCsvCell());
				pCdCsvDocument->getRowCont()->insert(aRow);
			}
			else if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_EkiPrevRessyasyubetsu)
			{
				CdCsvRow	aRow;
				aRow.getCellCont()->insert(CdCsvCell(m_namePrevRessyasyubetsu));
				aRow.getCellCont()->insert(CdCsvCell());
				pCdCsvDocument->getRowCont()->insert(aRow);
			}
			else if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_EkiPrevRessyamei)
			{
				CdCsvRow	aRow;
				aRow.getCellCont()->insert(CdCsvCell(m_namePrevRessyamei));
				aRow.getCellCont()->insert(CdCsvCell());
				pCdCsvDocument->getRowCont()->insert(aRow);

				CdCsvRow	aRow2;
				aRow.getCellCont()->insert(CdCsvCell(m_nameGousuu));
				aRow.getCellCont()->insert(CdCsvCell());
				pCdCsvDocument->getRowCont()->insert(aRow2);

				CdCsvRow	aRow3;
				aRow.getCellCont()->insert(CdCsvCell());
				aRow.getCellCont()->insert(CdCsvCell());
				pCdCsvDocument->getRowCont()->insert(aRow3);
			}

		}
	}

	//＜2.118＞[列1="備考" AND 列2=""]の列　備考列
	if ( iRv >= 0 )
	{
		CdCsvRow	aRow ;
		aRow.getCellCont()->insert( CdCsvCell( m_nameBikou ) ) ;
		aRow.getCellCont()->insert( CdCsvCell() ) ;
		pCdCsvDocument->getRowCont()->insert( aRow ) ;
	}
	// --------------------------------
	//	列車を出力(時刻表部分の3列目以降)
	// --------------------------------
	for (int idxRessya = iRessyaIndex;
		iRv >= 0 && idxRessya < iRessyaIndex + iRessyaCount;
		idxRessya++)
	{
		iRv = encode_AddRessya(
			pCentDedRessyasyubetsuContGet,
			pCentDedRessyaCont,
			contCustomizeRessyaIndex[idxRessya],
			pCdCsvDocument,
			pCentDedEkiCont,
			muCdDedEki,
			bDisplayTsuukaEkiJikoku,
			bDisplaySecondEkiJikoku,
			bDisplayColonEkiJikoku, 
			bDisplayShihatsuShuchakuEkimei,
			bDisplayParentSyubetsu,
			bDisplayRessyamei,
			iEnableOperation,
			iSecondRoundChaku,
			iSecondRoundHatsu,
			bDisplay2400,
			iOperationNumberRows,
			m_iOuterShihatsuDisplayEkiOrder,
			m_iOuterShuchakuDisplayEkiOrder);
	}
	
	return iRv ;
}
} //namespace ConvJikokuhyouCsv

