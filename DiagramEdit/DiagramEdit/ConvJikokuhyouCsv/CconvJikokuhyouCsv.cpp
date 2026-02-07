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
// ****************************************************************
// $Id: CconvJikokuhyouCsv.cpp 
// ****************************************************************
#include "stdafx.h"
#include "CconvJikokuhyouCsv.h"
#include "str¥strprintf.h"
//#include "..¥ViewJikokuhyou¥JikokuhyouColSpec¥CdYColSpecCont.h"
#include "Str/stringSplit.h"
#include "..¥entDed¥CentDedBeforeOperation.h"
#include "..¥entDed¥CentDedAfterOperation.h"
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
const TCHAR* const nameFileTypeValue = _T("OuDiaSecond.JikokuhyouCsv.2") ;

const int CSVROWINDEX_Ressyabangou = 4 ;
const int CSVROWINDEX_Ressyasyubetsu = 5 ;
const int CSVROWINDEX_Ressyamei = 6 ;
const int CSVROWINDEX_Gousuu = 7 ;
const int CSVROWINDEX_Gou = 8 ;
const int CSVROWINDEX_Ekijikoku0 = 9 ;
const int CSVCOLUMNINDEX_Ressya0 = 2 ;

const tstring nameShunt(_T("換 "));
const tstring nameConnect(_T("増 "));
const tstring nameConnectFront(_T("前方"));
const tstring nameConnectBack(_T("後方"));
const tstring nameRelease(_T("解 "));
const tstring nameReleaseFront(_T("前"));
const tstring nameReleaseBack(_T("後"));
const tstring nameReleaseLeave(_T("以外"));
const tstring nameNumberChange(_T("運番変更"));
const tstring nameNumberReverse(_T("運番反転"));
const tstring nameOut(_T("出区"));
const tstring nameIn(_T("入区"));
const tstring nameClassChange(_T("種別変更"));
const tstring namePropertyChange(_T("列車情報変更"));
const tstring namePropertySame(_T("同一列車扱い"));

/** 時刻の書式を保持します。 */
//const CdDedJikoku::CConv
//CconvJikokuhyouCsv::getCdDedJikokuConv(
//	const bool bDisplaySecondEkiJikoku,
//	const bool bDisplayColonEkiJikoku,
//	const int iSecondRoundChaku,
//	const int iSecondRoundHatsu,
//	const bool bDisplay2400)const
//{
//	CdDedJikoku::CConv::ESecond eSecond = CdDedJikoku::CConv::ESecond_NoSecond;
//	if (bDisplaySecondEkiJikoku)
//	{
//		eSecond = CdDedJikoku::CConv::ESecond_Output;
//	}
//
//	CdDedJikoku::CConv aConv(
//		!bDisplayColonEkiJikoku,
//		CdDedJikoku::CConv::EHour_ZeroToSpace,
//		eSecond,
//		(CdDedJikoku::CConv::ESecondRound)iSecondRoundChaku,
//		(CdDedJikoku::CConv::ESecondRound)iSecondRoundHatsu,
//		bDisplay2400
//	);
//	return aConv;
//}
//
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
tstring CconvJikokuhyouCsv::encode_Ekijikoku( 
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
	tstring strValue ;

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

void CconvJikokuhyouCsv::encode_BeforeOperation(
	const CentDedRessya* pCentDedRessya,
	const int& iEkiOrder,
	const int& iOperationIndex, 
	const CentDedEkiCont::CdDedEki& aCdDedEki,
	const bool bDisplayTsuukaEkiJikoku,
	const bool bDisplaySecondEkiJikoku, 
	const bool bDisplayColonEkiJikoku,
	const bool bDisplayOuterTerminalShihatsu,
	const bool bDisplayOuterTerminalShuchaku,
	const int iSecondRoundChaku,
	const int iSecondRoundHatsu,
	const bool bDisplay2400,
	tstring& strText1,
	tstring& strText2)
{
	const CentDedEkiJikoku aCentDedEkiJikoku = pCentDedRessya->getCentDedEkiJikoku(iEkiOrder);
	const CentDedBeforeOperationCont* pBeforeOperationCont = aCentDedEkiJikoku.getCentDedBeforeOperationCont();
	if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_None)
	{
		if (iEkiOrder < pCentDedRessya->getValidSihatsuEki() && pCentDedRessya->getValidSihatsuEki() != -1)
		{
			if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer
				&& bDisplayOuterTerminalShihatsu)
			{
				strText1 = m_nameKeiyunasi;
				strText2 = m_nameKeiyunasi;
			}
			else
			{
				strText1 = _T("");
				strText2 = _T("");
			}
		}
		else if (iEkiOrder > pCentDedRessya->getValidSyuuchakuEki() && pCentDedRessya->getValidSyuuchakuEki() != -1)
		{
			if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer
				&& bDisplayOuterTerminalShuchaku)
			{
				strText1 = m_nameKeiyunasi;
				strText2 = m_nameKeiyunasi;
			}
			else
			{
				strText1 = _T("");
				strText2 = _T("");
			}
		}
		else if (iEkiOrder > pCentDedRessya->getSihatsuEki() && pCentDedRessya->getSihatsuEki() != -1 &&
			iEkiOrder < pCentDedRessya->getSyuuchakuEki())
		{
			strText1 = m_nameKeiyunasi;
			strText2 = m_nameKeiyunasi;
		}

	}
	else if (pBeforeOperationCont->size() == 0)
	{
		strText1 = _T("");
		strText2 = _T("");
	}
	/**
		作業欄に表示する前作業は、BeforeContの下から作業欄個、ただし、出区等の列車先端は除く。
		秒単位処理は、着時刻設定に基づき行います。
	*/
	else if (pBeforeOperationCont->getMuPtr()->get(0)->isFirstOperation())
	{
		/**
			まずは、作業欄に表示する範囲の最上位を求める
			idx=0は列車先端なので除き、idx=1と作業数-表示数のどちらか大きい方が、最上位位置になります。
			その後、idxb(表示箇所のidx)を足し、BeforeContでその値をidxとする作業が存在する場合は、その作業を表示します
			表示数2の場合
			作業数1	:iTargetPos1,2	ただし、1,2の位置に作業が無いので、表示項目なし
			2		:iTargetPos1,2	ただし、2の位置に作業が無いので、1作業目のみ表示
			3		:iTargetPos1,2
			4		:iTargetPos2,3
		*/
		int iTargetPos = max(pBeforeOperationCont->size() - aCdDedEki.getJikokuhyouBeforeOperation(), 1);
		iTargetPos += iOperationIndex;

		if (iTargetPos < pBeforeOperationCont->size())
		{
			const CentDedBeforeOperation* pBeforeOperation
				= pBeforeOperationCont->getMuPtr()->get(iTargetPos);
			if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
			{
				strText1 = nameShunt;
				CentDedEkiTrack2Cont aCentDedEkiTrack2Cont = aCdDedEki.getCentDedEkiTrack2Cont();
				strText1 += aCentDedEkiTrack2Cont.get(pBeforeOperation->getShuntTrackIndex())
					.getTrackRyakusyou(pCentDedRessya->getRessyahoukou());

				strText2 = encode_Ekijikoku(
					CentDedEkiJikoku::Ekiatsukai_Teisya,
					pBeforeOperation->getOperationHatsuJikoku(),
					bDisplaySecondEkiJikoku,
					bDisplayColonEkiJikoku,
					iSecondRoundChaku,
					iSecondRoundHatsu,
					bDisplay2400,
					true);
			}
			else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
			{
				strText1 = nameConnect;
				if (pBeforeOperation->getIsConnectToFront())
				{
					strText1 += nameConnectFront;
				}
				else
				{
					strText1 += nameConnectBack;
				}

				strText2 = encode_Ekijikoku(
					CentDedEkiJikoku::Ekiatsukai_Teisya,
					pBeforeOperation->getConnectJikoku(),
					bDisplaySecondEkiJikoku,
					bDisplayColonEkiJikoku,
					iSecondRoundChaku,
					iSecondRoundHatsu,
					bDisplay2400,
					true);
			}
			else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
			{
				strText1 = nameRelease;
				if (pBeforeOperation->getReleasePos() == 0)//Back
				{
					strText1 += nameReleaseBack;
					strText1 += to_tstring(pBeforeOperation->getReleaseIndexCount());
				}
				else if (pBeforeOperation->getReleasePos() == 1)//Front
				{
					strText1 += nameReleaseFront;
					strText1 += to_tstring(pBeforeOperation->getReleaseIndexCount());
				}
				else if (pBeforeOperation->getReleasePos() == 2)//FrontLeave
				{
					strText1 += nameReleaseFront;
					strText1 += to_tstring(pBeforeOperation->getReleaseIndexCount());
					strText1 += nameReleaseLeave;
				}
				strText2 = encode_Ekijikoku(
					CentDedEkiJikoku::Ekiatsukai_Teisya,
					pBeforeOperation->getReleaseJikoku(),
					bDisplaySecondEkiJikoku,
					bDisplayColonEkiJikoku,
					iSecondRoundChaku,
					iSecondRoundHatsu,
					bDisplay2400,
					true);
			}
			//Ver2.00.05 運用番号変更対応
			//Ver2.06.05 運用番号順反転対応
			else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_NumberChange)
			{
				if (pBeforeOperation->getOperationNumberReverse())
				{
					strText1 = nameNumberReverse;
					strText2 = _T("");
				}
				else
				{
					strText1 = nameNumberChange;
					strText2 = joinc(';', pBeforeOperation->getOperationNumber());
				}
			}
			else
			{
				strText1 = _T("");
				strText2 = _T("");
			}
		}
		else
		{
			strText1 = _T("");
			strText2 = _T("");
		}
	}
	else
	{
		/**
			まずは、作業欄に表示する範囲の最上位を求める
			idx=0と作業数-表示数のどちらか大きい方が、最上位位置になります。
			その後、idxb(表示箇所のidx)を足し、BeforeContでその値をidxとする作業が存在する場合は、その作業を表示します
			表示数2の場合
			作業数1	:iTargetPos0,1	ただし、1の位置に作業が無いので、1作業目のみ表示
			2		:iTargetPos0,1
			3		:iTargetPos1,2
			4		:iTargetPos2,3
		*/
		int iTargetPos = max(pBeforeOperationCont->size() - aCdDedEki.getJikokuhyouBeforeOperation(), 0);
		iTargetPos += iOperationIndex;

		if (iTargetPos < pBeforeOperationCont->size())
		{
			const CentDedBeforeOperation* pBeforeOperation
				= pBeforeOperationCont->getMuPtr()->get(iTargetPos);
			if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
			{
				strText1 = nameShunt;
				CentDedEkiTrack2Cont aCentDedEkiTrack2Cont = aCdDedEki.getCentDedEkiTrack2Cont();
				strText1 += aCentDedEkiTrack2Cont.get(pBeforeOperation->getShuntTrackIndex())
					.getTrackRyakusyou(pCentDedRessya->getRessyahoukou());

				strText2 = encode_Ekijikoku(
					CentDedEkiJikoku::Ekiatsukai_Teisya,
					pBeforeOperation->getOperationHatsuJikoku(),
					bDisplaySecondEkiJikoku,
					bDisplayColonEkiJikoku,
					iSecondRoundChaku,
					iSecondRoundHatsu,
					bDisplay2400,
					true);
			}
			else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
			{
				strText1 = nameConnect;
				if (pBeforeOperation->getIsConnectToFront())
				{
					strText1 += nameConnectFront;
				}
				else
				{
					strText1 += nameConnectBack;
				}

				strText2 = encode_Ekijikoku(
					CentDedEkiJikoku::Ekiatsukai_Teisya,
					pBeforeOperation->getConnectJikoku(),
					bDisplaySecondEkiJikoku,
					bDisplayColonEkiJikoku,
					iSecondRoundChaku,
					iSecondRoundHatsu,
					bDisplay2400,
					true);
			}
			else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
			{
				strText1 = nameRelease;
				if (pBeforeOperation->getReleasePos() == 0)//Back
				{
					strText1 += nameReleaseBack;
					strText1 += to_tstring(pBeforeOperation->getReleaseIndexCount());
				}
				else if (pBeforeOperation->getReleasePos() == 1)//Front
				{
					strText1 += nameReleaseFront;
					strText1 += to_tstring(pBeforeOperation->getReleaseIndexCount());
				}
				else if (pBeforeOperation->getReleasePos() == 2)//FrontLeave
				{
					strText1 += nameReleaseFront;
					strText1 += to_tstring(pBeforeOperation->getReleaseIndexCount());
					strText1 += nameReleaseLeave;
				}
				strText2 = encode_Ekijikoku(
					CentDedEkiJikoku::Ekiatsukai_Teisya,
					pBeforeOperation->getReleaseJikoku(),
					bDisplaySecondEkiJikoku,
					bDisplayColonEkiJikoku,
					iSecondRoundChaku,
					iSecondRoundHatsu,
					bDisplay2400,
					true);
			}
			//Ver2.00.05 運用番号変更対応
			//Ver2.06.05 運用番号順反転対応
			else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_NumberChange)
			{
				if (pBeforeOperation->getOperationNumberReverse())
				{
					strText1 = nameNumberReverse;
					strText2 = _T("");
				}
				else
				{
					strText1 = nameNumberChange;
					strText2 = joinc(';', pBeforeOperation->getOperationNumber());
				}
			}
			else
			{
				strText1 = _T("");
				strText2 = _T("");
			}
		}
		else
		{
			strText1 = _T("");
			strText2 = _T("");
		}
	}

	//  １．Ａ駅の『駅時刻形式』が『発着』
	//  ２．列車Ｆの、Ａ駅での駅扱が『停車』か『通過』のいずれか
	//  ３．列車Ｆの、Ａ駅の着時刻が空
	//  ４．列車Ｆの、Ａ駅の前の駅での駅扱が『経由なし』
	//
	//  この場合は、時刻表ビュー上では、列車ＦのＡ駅での着時刻は " || " 表示とします。
	{
		CentDedEkiJikoku aCentDedEkijikokuPrev;
		if (0 <= iEkiOrder - 1
			&& iEkiOrder - 1 < pCentDedRessya->getCentDedEkiJikokuCount())
		{
			aCentDedEkijikokuPrev =
				pCentDedRessya->getCentDedEkiJikoku(
					iEkiOrder - 1);
		}
		//aCentDedEkijikokuPrev = 前の駅の駅時刻

		if ((aCentDedEkiJikoku.getEkiatsukai() ==
				CentDedEkiJikoku::Ekiatsukai_Teisya ||
				aCentDedEkiJikoku.getEkiatsukai() ==
				CentDedEkiJikoku::Ekiatsukai_Tsuuka) &&
			aCentDedEkiJikoku.getChakujikoku().isNull() &&
			aCentDedEkijikokuPrev.getEkiatsukai() ==
			CentDedEkiJikoku::Ekiatsukai_None &&
			pCentDedRessya->getSihatsuEki() < iEkiOrder)
		{
			strText1 = m_nameKeiyunasi;
			strText2 = m_nameKeiyunasi;
		}
	}
}

void CconvJikokuhyouCsv::encode_AfterOperation(
	const CentDedRessya* pCentDedRessya, 
	const int& iEkiOrder, 
	const int& iOperationIndex, 
	const CentDedEkiCont::CdDedEki& aCdDedEki,
	const bool bDisplayTsuukaEkiJikoku,
	const bool bDisplaySecondEkiJikoku, 
	const bool bDisplayColonEkiJikoku, 
	const bool bDisplayOuterTerminalShihatsu, 
	const bool bDisplayOuterTerminalShuchaku,
	const int iSecondRoundChaku,
	const int iSecondRoundHatsu,
	const bool bDisplay2400,
	tstring& strText1, 
	tstring& strText2)
{
	const CentDedEkiJikoku aCentDedEkiJikoku = pCentDedRessya->getCentDedEkiJikoku(iEkiOrder);
	const CentDedAfterOperationCont* pAfterOperationCont = aCentDedEkiJikoku.getCentDedAfterOperationCont();
	if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_None)
	{
		if (iEkiOrder < pCentDedRessya->getValidSihatsuEki() && pCentDedRessya->getValidSihatsuEki() != -1)
		{
			if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer
				&& bDisplayOuterTerminalShihatsu)
			{
				strText1 = m_nameKeiyunasi;
				strText2 = m_nameKeiyunasi;
			}
			else
			{
				strText1 = _T("");
				strText2 = _T("");
			}
		}
		else if (iEkiOrder > pCentDedRessya->getValidSyuuchakuEki() && pCentDedRessya->getValidSyuuchakuEki() != -1)
		{
			if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer
				&& bDisplayOuterTerminalShuchaku)
			{
				strText1 = m_nameKeiyunasi;
				strText2 = m_nameKeiyunasi;
			}
			else
			{
				strText1 = _T("");
				strText2 = _T("");
			}
		}
		else if (iEkiOrder > pCentDedRessya->getSihatsuEki() && pCentDedRessya->getSihatsuEki() != -1 &&
			iEkiOrder < pCentDedRessya->getSyuuchakuEki())
		{
			strText1 = m_nameKeiyunasi;
			strText2 = m_nameKeiyunasi;
		}

	}
	else if (pAfterOperationCont->size() <= iOperationIndex)
	{
		strText1 = _T("");
		strText2 = _T("");
	}
	else if (!pAfterOperationCont->getMuPtr()->get(iOperationIndex)->isLastOperation())
	{
		/**
			後作業を、表示欄数だけ、前方から表示する
			秒単位処理は、発時刻設定に基づき行います。
		*/
		const CentDedAfterOperation* pAfterOperation
			= pAfterOperationCont->getMuPtr()->get(iOperationIndex);
		if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
		{
			strText1 = nameShunt;
			CentDedEkiTrack2Cont aCentDedEkiTrack2Cont = aCdDedEki.getCentDedEkiTrack2Cont();
			strText1 += aCentDedEkiTrack2Cont.get(pAfterOperation->getShuntTrackIndex())
				.getTrackRyakusyou(pCentDedRessya->getRessyahoukou());

			strText2 = encode_Ekijikoku(
				CentDedEkiJikoku::Ekiatsukai_Teisya,
				pAfterOperation->getOperationHatsuJikoku(),
				bDisplaySecondEkiJikoku,
				bDisplayColonEkiJikoku,
				iSecondRoundChaku,
				iSecondRoundHatsu,
				bDisplay2400,
				false);
		}
		else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
		{
			strText1 = nameConnect;
			if (pAfterOperation->getIsConnectToFront())
			{
				strText1 += nameConnectFront;
			}
			else
			{
				strText1 += nameConnectBack;
			}

			strText2 = encode_Ekijikoku(
				CentDedEkiJikoku::Ekiatsukai_Teisya,
				pAfterOperation->getConnectJikoku(),
				bDisplaySecondEkiJikoku,
				bDisplayColonEkiJikoku,
				iSecondRoundChaku,
				iSecondRoundHatsu,
				bDisplay2400,
				false);
		}
		else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
		{
			strText1 = nameRelease;
			if (pAfterOperation->getReleasePos() == 0)//Back
			{
				strText1 += _T("後");
				strText1 += to_tstring(pAfterOperation->getReleaseIndexCount());
			}
			else if (pAfterOperation->getReleasePos() == 1)//Front
			{
				strText1 += nameReleaseFront;
				strText1 += to_tstring(pAfterOperation->getReleaseIndexCount());
			}
			else if (pAfterOperation->getReleasePos() == 2)//FrontLeave
			{
				strText1 += nameReleaseFront;
				strText1 += to_tstring(pAfterOperation->getReleaseIndexCount());
				strText1 += nameReleaseLeave;
			}

			strText2 = encode_Ekijikoku(
				CentDedEkiJikoku::Ekiatsukai_Teisya,
				pAfterOperation->getReleaseJikoku(),
				bDisplaySecondEkiJikoku,
				bDisplayColonEkiJikoku,
				iSecondRoundChaku,
				iSecondRoundHatsu,
				bDisplay2400,
				false);
		}
		//Ver2.00.05 運用番号変更対応
		//Ver2.06.05 運用番号順反転対応
		else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_NumberChange)
		{
			if (pAfterOperation->getOperationNumberReverse())
			{
				strText1 = nameNumberReverse;
				strText2 = _T("");
			}
			else
			{
				strText1 = nameNumberChange;
				strText2 = joinc(';', pAfterOperation->getOperationNumber());
			}
		}
		else
		{
			strText1 = _T("");
			strText2 = _T("");
		}
	}
	else
	{
		strText1 = _T("");
		strText2 = _T("");
	}

	//  １．Ａ駅の『駅時刻形式』が『発着』
	//  ２．列車Ｆの、Ａ駅での駅扱が『停車』か『通過』のいずれか
	//  ３．列車Ｆの、Ａ駅の発時刻が空
	//  ４．列車Ｆの、Ａ駅の次の駅での駅扱が『経由なし』
	//
	//	  この場合は、時刻表ビュー上では、列車ＦのＡ駅での発時刻は 
	//	" || " 表示とします
	{
		CentDedEkiJikoku aCentDedEkijikokuNext;
		if (0 <= iEkiOrder + 1
			&& iEkiOrder + 1 < pCentDedRessya->getCentDedEkiJikokuCount())
		{
			aCentDedEkijikokuNext =
				pCentDedRessya->getCentDedEkiJikoku(
					iEkiOrder + 1);
		}
		//aCentDedEkijikokuNext = 次の駅の駅時刻

		if ((aCentDedEkiJikoku.getEkiatsukai() ==
				CentDedEkiJikoku::Ekiatsukai_Teisya ||
			aCentDedEkiJikoku.getEkiatsukai() ==
				CentDedEkiJikoku::Ekiatsukai_Tsuuka) &&
			aCentDedEkiJikoku.getHatsujikoku().isNull() &&
			aCentDedEkijikokuNext.getEkiatsukai() ==
				CentDedEkiJikoku::Ekiatsukai_None &&
			pCentDedRessya->getSyuuchakuEki() > iEkiOrder)
		{
			strText1 = m_nameKeiyunasi;
			strText2 = m_nameKeiyunasi;
		}

	}
}

// --------------------------------
	//@name encode() の下請関数	
	// --------------------------------

int CconvJikokuhyouCsv::encode_AddRessya( 
		const Mu<const CentDedRessyasyubetsu*>* pCentDedRessyasyubetsuContGet ,
		const CentDedRessya* pCentDedRessya , 
		CdCsvDocument* pCdCsvDocument ,
		const CentDedEkiCont* pCentDedEkiCont,
		const Mu<CentDedEkiCont::CdDedEki>* pCdDedEkiCont,
		const bool bDisplayTsuukaEkiJikoku,
		const bool bDisplaySecondEkiJikoku,
		const bool bDisplayColonEkiJikoku,
		const bool bDisplayParentSyubetsu,
		const bool bDisplayRessyamei,
		const int iEnableOperation,
		const bool bDisplayOuterTerminalShihatsu,
		const bool bDisplayOuterTerminalShuchaku,
		const int iSecondRoundChaku,
		const int iSecondRoundHatsu,
		const bool bDisplay2400,
		const int iOperationNumberRows,
		const bool bDisplayInOutLinkCode)
{
	int iRv = 0 ;

	if ( iRv >= 0 )
	{
		if ( pCentDedRessya->isNull() )
		{
			iRv = -1 ;	//	pCentDedRessya は Null です。
		}
	}
	// --------------------------------
	const CentDedRessyasyubetsu* pCentDedRessyasyubetsu = NULL ;
	if ( iRv >= 0 )
	{
		pCentDedRessyasyubetsu 	= pCentDedRessyasyubetsuContGet
			->get( pCentDedRessya->getRessyasyubetsuIndex() ) ;
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
		aRow.getCellCont()->insert( CdCsvCell( pCentDedRessya->getRessyabangou() ) ) ;
		pCdCsvDocument->getRowCont()->set( aRow , iRowIndex) ;
		iRowIndex++;
	}

	//＜2.6＞ <運用番号>
	if (iRv >= 0 && iEnableOperation > 1)
	{
		vector<tstring> strOperationNumber = pCentDedRessya->getOperationNumber(pCentDedRessya->getValidSihatsuEki());
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
		aRow.getCellCont()->insert(CdCsvCell(pCentDedRessyasyubetsu->getRyakusyou()));
		pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
		iRowIndex++;
	}

	//＜2.8＞<列車名>
	if ( iRv >= 0 && bDisplayRessyamei)
	{
		CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex) ;
		aRow.getCellCont()->insert( CdCsvCell( pCentDedRessya->getRessyamei() ) ) ;
		pCdCsvDocument->getRowCont()->set( aRow , iRowIndex) ;
		iRowIndex++;
	}

	//＜2.9＞<号数>
	if ( iRv >= 0 && bDisplayRessyamei)
	{
		CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex) ;
		aRow.getCellCont()->insert( CdCsvCell( pCentDedRessya->getGousuu() ) ) ;
		pCdCsvDocument->getRowCont()->set( aRow , iRowIndex) ;
		iRowIndex++;
	}
	//＜2.10＞<号表示>
	if ( iRv >= 0 && bDisplayRessyamei)
	{
		tstring	strValue ;
		if ( !pCentDedRessya->getGousuu().empty() )
		{
			strValue = m_nameGou ;
		}
		CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex) ;
		aRow.getCellCont()->insert( CdCsvCell( strValue ) ) ;
		pCdCsvDocument->getRowCont()->set( aRow , iRowIndex) ;
		iRowIndex++;
	}

	//＜2.11＞ <始発駅名>
	if (iRv >= 0)
	{
		tstring strText;
		if (pCentDedRessya->getValidSihatsuEki() != -1)
		{
			strText = pCdDedEkiCont->get(pCentDedRessya->getValidSihatsuEki()).getEkimeiJikokuhyouRyaku(true);
		}
		CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
		aRow.getCellCont()->insert(CdCsvCell(strText));
		pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
		iRowIndex++;
	}

	//＜2.12＞ <始発駅作業>
	if (iRv >= 0)
	{
		tstring strText1;
		tstring strText2;
		tstring strText3;
		tstring strText4;

		const CentDedBeforeOperation aFirstOperation = pCentDedRessya->getFirstOperation();
		if (aFirstOperation.getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Out)
		{
			strText1 = nameOut;
			strText2 = encode_Ekijikoku(
				CentDedEkiJikoku::Ekiatsukai_Teisya,
				aFirstOperation.getOutJikoku(),
				bDisplaySecondEkiJikoku,
				bDisplayColonEkiJikoku,
				iSecondRoundChaku,
				iSecondRoundHatsu,
				bDisplay2400,
				true);
			strText3 = joinc(';', aFirstOperation.getOperationNumberOriginal(),true);
			strText4 = aFirstOperation.getInOutLinkCode();
		}
		else if (aFirstOperation.getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
		{
			CentDedEkiCont::CdDedEki aCdDedEki = pCdDedEkiCont->get(pCentDedRessya->getValidSihatsuEki());
			strText1 = aCdDedEki.getOuterTerminalJikokuRyaku(aFirstOperation.getOuterShihatsuekiIndex(), true);
			CdDedJikoku aCdDedJikoku = aFirstOperation.getChakuJikoku();
			if (aCdDedJikoku.isNull())
			{
				aCdDedJikoku = pCentDedRessya->getCentDedEkiJikoku(
					pCentDedRessya->getValidSihatsuEki()).getHatsujikoku();
				strText2 = encode_Ekijikoku(
					CentDedEkiJikoku::Ekiatsukai_Tsuuka,
					aCdDedJikoku,
					bDisplaySecondEkiJikoku,
					bDisplayColonEkiJikoku,
					iSecondRoundChaku,
					iSecondRoundHatsu,
					bDisplay2400,
					true);
			}
			else
			{
				strText2 = encode_Ekijikoku(
					CentDedEkiJikoku::Ekiatsukai_Teisya,
					aCdDedJikoku,
					bDisplaySecondEkiJikoku,
					bDisplayColonEkiJikoku,
					iSecondRoundChaku,
					iSecondRoundHatsu,
					bDisplay2400,
					true);
			}
			strText2 += m_nameChaku;
			strText3 = joinc(';', aFirstOperation.getOperationNumberOriginal(), true);
			strText4 = aFirstOperation.getInOutLinkCode();
		}
		//2.00.05 仮運用番号に対応
		else if (aFirstOperation.getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Junction)
		{
			strText1 = _T("");
			strText2 = encode_Ekijikoku(
				CentDedEkiJikoku::Ekiatsukai_Teisya,
				aFirstOperation.getOriginJikoku(),
				bDisplaySecondEkiJikoku,
				bDisplayColonEkiJikoku,
				iSecondRoundChaku,
				iSecondRoundHatsu,
				bDisplay2400,
				true);
			strText3 = joinc(';', aFirstOperation.getOperationNumberTemp());
			strText4 = _T("");
		}

		CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
		aRow.getCellCont()->insert(CdCsvCell(strText1));
		pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
		iRowIndex++;
		CdCsvRow	aRow2 = pCdCsvDocument->getRowCont()->get(iRowIndex);
		aRow2.getCellCont()->insert(CdCsvCell(strText2));
		pCdCsvDocument->getRowCont()->set(aRow2, iRowIndex);
		iRowIndex++;
		if (iEnableOperation > 1)
		{
			CdCsvRow	aRow3 = pCdCsvDocument->getRowCont()->get(iRowIndex);
			aRow3.getCellCont()->insert(CdCsvCell(strText3));
			pCdCsvDocument->getRowCont()->set(aRow3, iRowIndex);
			iRowIndex++;
			if (bDisplayInOutLinkCode)
			{
				CdCsvRow	aRow4 = pCdCsvDocument->getRowCont()->get(iRowIndex);
				aRow4.getCellCont()->insert(CdCsvCell(strText4));
				pCdCsvDocument->getRowCont()->set(aRow4, iRowIndex);
				iRowIndex++;
			}
		}
	}

	//＜2.13＞ <終着駅名>
	if (iRv >= 0)
	{
		tstring strText;
		if (pCentDedRessya->getValidSyuuchakuEki() != -1)
		{
			strText = pCdDedEkiCont->get(pCentDedRessya->getValidSyuuchakuEki()).getEkimeiJikokuhyouRyaku(true);
		}
		CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
		aRow.getCellCont()->insert(CdCsvCell(strText));
		pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
		iRowIndex++;
	}

	//＜2.14＞ <終着駅作業>
	if (iRv >= 0)
	{
		tstring strText1;
		tstring strText2;
		tstring strText3;

		const CentDedAfterOperation aLastOperation = pCentDedRessya->getLastOperation();
		if (aLastOperation.getAOperation() == CentDedAfterOperation::EAOperation::AOperation_In)
		{
			strText1 = nameIn;
			strText2 = encode_Ekijikoku(
				CentDedEkiJikoku::Ekiatsukai_Teisya,
				aLastOperation.getInJikoku(),
				bDisplaySecondEkiJikoku,
				bDisplayColonEkiJikoku,
				iSecondRoundChaku,
				iSecondRoundHatsu,
				bDisplay2400,
				false);
			strText3 = aLastOperation.getInOutLinkCode();

		}
		else if (aLastOperation.getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
		{
			CentDedEkiCont::CdDedEki aCdDedEki = pCdDedEkiCont->get(pCentDedRessya->getValidSyuuchakuEki());
			strText1 = aCdDedEki.getOuterTerminalJikokuRyaku(aLastOperation.getOuterShuchakuekiIndex(), true);
			CdDedJikoku aCdDedJikoku = aLastOperation.getHatsuJikoku();
			if (aCdDedJikoku.isNull())
			{
				aCdDedJikoku = pCentDedRessya->getCentDedEkiJikoku(
					pCentDedRessya->getValidSyuuchakuEki()).getChakujikoku();
				strText2 = encode_Ekijikoku(
					CentDedEkiJikoku::Ekiatsukai_Tsuuka,
					aCdDedJikoku,
					bDisplaySecondEkiJikoku,
					bDisplayColonEkiJikoku,
					iSecondRoundChaku,
					iSecondRoundHatsu,
					bDisplay2400,
					false);
			}
			else
			{
				strText2 = encode_Ekijikoku(
					CentDedEkiJikoku::Ekiatsukai_Teisya,
					aCdDedJikoku,
					bDisplaySecondEkiJikoku,
					bDisplayColonEkiJikoku,
					iSecondRoundChaku,
					iSecondRoundHatsu,
					bDisplay2400,
					false);
			}
			strText2 += m_nameHatsu;
			strText3 = aLastOperation.getInOutLinkCode();

		}
		else if (aLastOperation.getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Junction)
		{
			//Ver2.05 1行目には、次列車接続タイプを表示する
			if (aLastOperation.getNextJunctionType() == 1)
			{
				strText1 = nameClassChange;
			}
			else if (aLastOperation.getNextJunctionType() == 2)
			{
				strText1 = namePropertyChange;
			}
			else if (aLastOperation.getNextJunctionType() == 3)
			{
				strText1 = namePropertySame;
			}
			else
			{
				strText1 = _T("");
			}
			strText2 = encode_Ekijikoku(
				CentDedEkiJikoku::Ekiatsukai_Teisya,
				aLastOperation.getTerminalJikoku(),
				bDisplaySecondEkiJikoku,
				bDisplayColonEkiJikoku,
				iSecondRoundChaku,
				iSecondRoundHatsu,
				bDisplay2400,
				false);
		}

		CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
		aRow.getCellCont()->insert(CdCsvCell(strText1));
		pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
		iRowIndex++;
		CdCsvRow	aRow2 = pCdCsvDocument->getRowCont()->get(iRowIndex);
		aRow2.getCellCont()->insert(CdCsvCell(strText2));
		pCdCsvDocument->getRowCont()->set(aRow2, iRowIndex);
		iRowIndex++;
		if (iEnableOperation > 1 && bDisplayInOutLinkCode)
		{
			CdCsvRow	aRow3 = pCdCsvDocument->getRowCont()->get(iRowIndex);
			aRow3.getCellCont()->insert(CdCsvCell(strText3));
			pCdCsvDocument->getRowCont()->set(aRow3, iRowIndex);
			iRowIndex++;
		}
	}

	//＜2.15＞ <路線外始発駅>
	if (iRv >= 0 && bDisplayOuterTerminalShihatsu)
	{
		tstring strText1;
		tstring strText2;

		const CentDedBeforeOperation aFirstOperation = pCentDedRessya->getFirstOperation();
		if (aFirstOperation.getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
		{
			CentDedEkiCont::CdDedEki aCdDedEki = pCdDedEkiCont->get(pCentDedRessya->getValidSihatsuEki());
			strText1 = aCdDedEki.getOuterTerminalJikokuRyaku(aFirstOperation.getOuterShihatsuekiIndex(), true);

			if (!(aFirstOperation.getOuterShihatsuJikoku().isNull()))
			{
				CdDedJikoku aCdDedJikoku
					= aFirstOperation.getOuterShihatsuJikoku();
				strText2 = encode_Ekijikoku(
					CentDedEkiJikoku::Ekiatsukai_Teisya,
					aCdDedJikoku,
					bDisplaySecondEkiJikoku,
					bDisplayColonEkiJikoku,
					iSecondRoundChaku,
					iSecondRoundHatsu,
					bDisplay2400,
					false);
			}
		}

		CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
		aRow.getCellCont()->insert(CdCsvCell(strText1));
		pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
		iRowIndex++;
		CdCsvRow	aRow2 = pCdCsvDocument->getRowCont()->get(iRowIndex);
		aRow2.getCellCont()->insert(CdCsvCell(strText2));
		pCdCsvDocument->getRowCont()->set(aRow2, iRowIndex);
		iRowIndex++;
	}


	//＜2.10＞10行目〜 駅時刻
	
	if (iRv >= 0)
	{
		for (int idx = m_CdYColSpecCont.getColumnNumber_Ekijikoku_begin();
			idx < m_CdYColSpecCont.getColumnNumber_Ekijikoku_end(); idx++)
		{
			const CdYColSpec aCdYColSpec = m_CdYColSpecCont.ColumnNumberToSpec(idx);
			int iEkiOrder = aCdYColSpec.getEkiOrder();
			CentDedEkiCont::CdDedEki aCdDedEki = pCdDedEkiCont->get(iEkiOrder);

			CentDedEkiJikoku aCentDedEkiJikoku
				= pCentDedRessya->getCentDedEkiJikoku(iEkiOrder);

			if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_Ekijikoku_Chaku)
			{
				tstring	strText = _T("");
				switch (aCentDedEkiJikoku.getEkiatsukai())
				{
				case CentDedEkiJikoku::Ekiatsukai_None:
				{
					if (iEkiOrder < pCentDedRessya->getSihatsuEki() && pCentDedRessya->getSihatsuEki() != -1)
					{
						if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer
							&& bDisplayOuterTerminalShihatsu)
						{
							strText = m_nameKeiyunasi;

						}
					}
					else if (iEkiOrder > pCentDedRessya->getSyuuchakuEki() && pCentDedRessya->getSyuuchakuEki() != -1)
					{
						if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer
							&& bDisplayOuterTerminalShuchaku)
						{
							strText = m_nameKeiyunasi;

						}
					}
					else if (iEkiOrder > pCentDedRessya->getSihatsuEki() && pCentDedRessya->getSihatsuEki() != -1 &&
						iEkiOrder < pCentDedRessya->getSyuuchakuEki())
					{
						strText = m_nameKeiyunasi;
					}
				}
				break;
				case CentDedEkiJikoku::Ekiatsukai_Tsuuka:
				{
					if (!aCentDedEkiJikoku.getChakujikoku().isNull() && bDisplayTsuukaEkiJikoku)
					{
						/**
							秒単位表示OFFの場合は、切り上げ・切り捨ての処理を行いますが、
							その補助のため、着時刻が切り上げで、発時刻が30秒以上切り上げまたは切り捨ての場合は、発時刻の取得を行います。
							この駅と次の駅の間が運行なしの場合は、運行なしを超えた先の駅から時刻を取得します。
						*/
						CdDedJikoku aHatsuJikoku;
						if (!bDisplaySecondEkiJikoku &&
							iSecondRoundChaku == 2 &&
							iSecondRoundHatsu <= 1)
						{
							if (iEkiOrder < pCentDedRessya->getValidSyuuchakuEki() && pCentDedRessya->getValidSyuuchakuEki() != -1)
							{
								if (pCentDedRessya->isRunBetweenNextEki(iEkiOrder))
								{
									aHatsuJikoku = aCentDedEkiJikoku.getHatsujikoku();
								}
								else
								{
									int iHatsuEkiOrder = pCentDedRessya->getRunBetweenEkiForward(iEkiOrder);
									if (iHatsuEkiOrder != -1 &&
										pCentDedEkiCont->isSameBrunchLoopGroup(
											iEkiOrder, iHatsuEkiOrder, pCentDedRessya->getRessyahoukou()))
									{
										aHatsuJikoku = pCentDedRessya->getCentDedEkiJikoku(iHatsuEkiOrder).getHatsujikoku();
									}
								}
							}
						}
						//	通過駅の駅時刻が設定されており、
						//	『通過駅の駅時刻を表示する』指定になっている場合は
						//	時刻を表示
						strText = encode_Ekijikoku(
							aCentDedEkiJikoku.getEkiatsukai(),
							aCentDedEkiJikoku.getChakujikoku(),
							bDisplaySecondEkiJikoku,
							bDisplayColonEkiJikoku,
							iSecondRoundChaku,
							iSecondRoundHatsu,
							bDisplay2400,
							true,
							aHatsuJikoku);
					}
					//始発駅かつ路線外発着設定で、駅時刻なしor通過駅時刻表示なしなら、経由無しマークを表示
					else if (iEkiOrder == pCentDedRessya->getSihatsuEki() &&
						pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer &&
						bDisplayOuterTerminalShihatsu)
					{

						strText = m_nameKeiyunasi;
					}
					else
					{
						strText = m_nameTsuuka;
					}
				}
				break;
				case CentDedEkiJikoku::Ekiatsukai_Teisya:
				{
					//	停車駅の駅時刻が指定されている
					if (!aCentDedEkiJikoku.getChakujikoku().isNull())
					{
						/**
							秒単位表示OFFの場合は、切り上げ・切り捨ての処理を行いますが、
							その補助のため、着時刻が切り上げで、発時刻が30秒以上切り上げまたは切り捨ての場合は、発時刻の取得を行います。
							この駅と次の駅の間が運行なしの場合は、運行なしを超えた先の駅から時刻を取得します。
						*/
						CdDedJikoku aHatsuJikoku;
						if (!bDisplaySecondEkiJikoku &&
							iSecondRoundChaku == 2 &&
							iSecondRoundHatsu <= 1)
						{
							if (iEkiOrder < pCentDedRessya->getValidSyuuchakuEki() && pCentDedRessya->getValidSyuuchakuEki() != -1)
							{
								if (pCentDedRessya->isRunBetweenNextEki(iEkiOrder))
								{
									aHatsuJikoku = aCentDedEkiJikoku.getHatsujikoku();
								}
								else
								{
									int iHatsuEkiOrder = pCentDedRessya->getRunBetweenEkiForward(iEkiOrder);
									if (iHatsuEkiOrder != -1 &&
										pCentDedEkiCont->isSameBrunchLoopGroup(
											iEkiOrder, iHatsuEkiOrder, pCentDedRessya->getRessyahoukou()))
									{
										aHatsuJikoku = pCentDedRessya->getCentDedEkiJikoku(iHatsuEkiOrder).getHatsujikoku();
									}
								}
							}
						}
						strText = encode_Ekijikoku(
							aCentDedEkiJikoku.getEkiatsukai(),
							aCentDedEkiJikoku.getChakujikoku(),
							bDisplaySecondEkiJikoku,
							bDisplayColonEkiJikoku,
							iSecondRoundChaku,
							iSecondRoundHatsu,
							bDisplay2400,
							true,
							aHatsuJikoku);
					}
					//始発駅かつ路線外発着設定で、駅時刻なしなら、経由無しマークを表示
					else if (iEkiOrder == pCentDedRessya->getSihatsuEki() &&
						pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer &&
						bDisplayOuterTerminalShihatsu)
					{
						strText = m_nameKeiyunasi;
					}
				}
				break;
				}


				//  １．Ａ駅の『駅時刻形式』が『発着』
				//  ２．列車Ｆの、Ａ駅での駅扱が『停車』か『通過』のいずれか
				//  ３．列車Ｆの、Ａ駅の着時刻が空
				//  ４．列車Ｆの、Ａ駅の前の駅での駅扱が『経由なし』
				//
				//  この場合は、時刻表ビュー上では、列車ＦのＡ駅での着時刻は " || " 表示とします。
				{
					CentDedEkiJikoku aCentDedEkijikokuPrev;
					if (0 <= iEkiOrder - 1
						&& iEkiOrder - 1 < pCdDedEkiCont->size())
					{
						aCentDedEkijikokuPrev =
							pCentDedRessya->getCentDedEkiJikoku(
								iEkiOrder - 1);
					}
					//aCentDedEkijikokuPrev = 前の駅の駅時刻

					if (aCdDedEki.isHatsuChakuHyouji() &&
						(aCentDedEkiJikoku.getEkiatsukai() ==
							CentDedEkiJikoku::Ekiatsukai_Teisya ||
							aCentDedEkiJikoku.getEkiatsukai() ==
							CentDedEkiJikoku::Ekiatsukai_Tsuuka) &&
						aCentDedEkiJikoku.getChakujikoku().isNull() &&
						aCentDedEkijikokuPrev.getEkiatsukai() ==
						CentDedEkiJikoku::Ekiatsukai_None &&
						pCentDedRessya->getSihatsuEki() < iEkiOrder)
					{
						strText = m_nameKeiyunasi;
					}
				}

				CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
				aRow.getCellCont()->insert(CdCsvCell(strText));
				pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
				iRowIndex++;
			}
			else if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_Ekijikoku_Hatsu)
			{
				tstring	strText = _T("");

				switch (aCentDedEkiJikoku.getEkiatsukai())
				{
				case CentDedEkiJikoku::Ekiatsukai_None:
				{
					if (iEkiOrder < pCentDedRessya->getSihatsuEki() && pCentDedRessya->getSihatsuEki() != -1)
					{
						if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer
							&& bDisplayOuterTerminalShihatsu)
						{
							strText = m_nameKeiyunasi;
						}
					}
					else if (iEkiOrder > pCentDedRessya->getSyuuchakuEki() && pCentDedRessya->getSyuuchakuEki() != -1)
					{
						if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer
							&& bDisplayOuterTerminalShuchaku)
						{
							strText = m_nameKeiyunasi;
						}
					}
					else if (iEkiOrder > pCentDedRessya->getSihatsuEki() && pCentDedRessya->getSihatsuEki() != -1 &&
						iEkiOrder < pCentDedRessya->getSyuuchakuEki())
					{
						strText = m_nameKeiyunasi;
					}
				}
				break;
				case CentDedEkiJikoku::Ekiatsukai_Tsuuka:
				{
					if (!aCentDedEkiJikoku.getHatsujikoku().isNull() && bDisplayTsuukaEkiJikoku)
					{
						/**
							秒単位表示OFFの場合は、切り上げ・切り捨ての処理を行いますが、
							その補助のため、発時刻が切り捨てで、着時刻が30秒以上切り上げまたは切り上げの場合は、着時刻の取得を行います。
							この駅と前の駅の間が運行なしの場合は、運行なしを超えた先の駅から時刻を取得します。
						*/
						CdDedJikoku aChakuJikoku;
						if (!bDisplaySecondEkiJikoku &&
							iSecondRoundChaku >= 1 &&
							iSecondRoundHatsu == 0)
						{
							if (iEkiOrder > pCentDedRessya->getValidSihatsuEki() && pCentDedRessya->getValidSihatsuEki() != -1)
							{
								if (pCentDedRessya->isRunBetweenNextEki(iEkiOrder - 1))
								{
									aChakuJikoku = aCentDedEkiJikoku.getChakujikoku();
								}
								else
								{
									int iChakuEkiOrder = pCentDedRessya->getRunBetweenEkiBackward(iEkiOrder);
									if (iChakuEkiOrder != -1 &&
										pCentDedEkiCont->isSameBrunchLoopGroup(
											iEkiOrder, iChakuEkiOrder, pCentDedRessya->getRessyahoukou()))
									{
										aChakuJikoku = pCentDedRessya->getCentDedEkiJikoku(iChakuEkiOrder).getChakujikoku();
									}
								}
							}
						}

						//	通過駅の駅時刻が設定されており、
						//	『通過駅の駅時刻を表示する』指定になっている場合は
						//	時刻を表示
						strText = encode_Ekijikoku(
							aCentDedEkiJikoku.getEkiatsukai(),
							aCentDedEkiJikoku.getHatsujikoku(),
							bDisplaySecondEkiJikoku,
							bDisplayColonEkiJikoku,
							iSecondRoundChaku,
							iSecondRoundHatsu,
							bDisplay2400,
							false,
							aChakuJikoku);
					}
					//終着駅かつ路線外発着設定で、駅時刻なしor通過駅時刻表示なしなら、経由無しマークを表示
					else if (iEkiOrder == pCentDedRessya->getSyuuchakuEki() &&
						pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer &&
						bDisplayOuterTerminalShuchaku)
					{
						strText = m_nameKeiyunasi;
					}
					else
					{
						strText = m_nameTsuuka;
					}
				}
				break;
				case CentDedEkiJikoku::Ekiatsukai_Teisya:
				{
					//	停車駅の駅時刻が指定されている
					if (!aCentDedEkiJikoku.getHatsujikoku().isNull())
					{
						/**
							秒単位表示OFFの場合は、切り上げ・切り捨ての処理を行いますが、
							その補助のため、発時刻が切り捨てで、着時刻が30秒以上切り上げまたは切り上げの場合は、着時刻の取得を行います。
							この駅と前の駅の間が運行なしの場合は、運行なしを超えた先の駅から時刻を取得します。
						*/
						CdDedJikoku aChakuJikoku;
						if (!bDisplaySecondEkiJikoku &&
							iSecondRoundChaku >= 1 &&
							iSecondRoundHatsu == 0)
						{
							if (iEkiOrder > pCentDedRessya->getValidSihatsuEki() && pCentDedRessya->getValidSihatsuEki() != -1)
							{
								if (pCentDedRessya->isRunBetweenNextEki(iEkiOrder - 1))
								{
									aChakuJikoku = aCentDedEkiJikoku.getChakujikoku();
								}
								else
								{
									int iChakuEkiOrder = pCentDedRessya->getRunBetweenEkiBackward(iEkiOrder);
									if (iChakuEkiOrder != -1 &&
										pCentDedEkiCont->isSameBrunchLoopGroup(
											iEkiOrder, iChakuEkiOrder, pCentDedRessya->getRessyahoukou()))
									{
										aChakuJikoku = pCentDedRessya->getCentDedEkiJikoku(iChakuEkiOrder).getChakujikoku();
									}
								}
							}
						}

						strText = encode_Ekijikoku(
							aCentDedEkiJikoku.getEkiatsukai(),
							aCentDedEkiJikoku.getHatsujikoku(),
							bDisplaySecondEkiJikoku,
							bDisplayColonEkiJikoku,
							iSecondRoundChaku,
							iSecondRoundHatsu,
							bDisplay2400,
							false,
							aChakuJikoku);
					}
					//終着駅かつ路線外発着設定で、駅時刻なしなら、経由無しマークを表示
					else if (iEkiOrder == pCentDedRessya->getSyuuchakuEki() &&
						pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer &&
						bDisplayOuterTerminalShuchaku)
					{

						strText = m_nameKeiyunasi;
					}
				}
				break;
				}


				//  １．Ａ駅の『駅時刻形式』が『発着』
				//  ２．列車Ｆの、Ａ駅での駅扱が『停車』か『通過』のいずれか
				//  ３．列車Ｆの、Ａ駅の発時刻が空
				//  ４．列車Ｆの、Ａ駅の次の駅での駅扱が『経由なし』
				//
				//	  この場合は、時刻表ビュー上では、列車ＦのＡ駅での発時刻は 
				//	" || " 表示とします
				{
					CentDedEkiJikoku aCentDedEkijikokuNext;
					if (0 <= iEkiOrder + 1
						&& iEkiOrder + 1 < pCdDedEkiCont->size())
					{
						aCentDedEkijikokuNext =
							pCentDedRessya->getCentDedEkiJikoku(
								iEkiOrder + 1);
					}
					//aCentDedEkijikokuNext = 次の駅の駅時刻

					if (aCdDedEki.isHatsuChakuHyouji() &&
						(aCentDedEkiJikoku.getEkiatsukai() ==
							CentDedEkiJikoku::Ekiatsukai_Teisya ||
							aCentDedEkiJikoku.getEkiatsukai() ==
							CentDedEkiJikoku::Ekiatsukai_Tsuuka) &&
						aCentDedEkiJikoku.getHatsujikoku().isNull() &&
						aCentDedEkijikokuNext.getEkiatsukai() ==
						CentDedEkiJikoku::Ekiatsukai_None &&
						pCentDedRessya->getSyuuchakuEki() > iEkiOrder)
					{
						strText = m_nameKeiyunasi;
					}

				}

				CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
				aRow.getCellCont()->insert(CdCsvCell(strText));
				pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
				iRowIndex++;
			}
			else if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_Track)
			{
				tstring strText = _T("");

				if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_None)
				{
					if (iEkiOrder < pCentDedRessya->getSihatsuEki())
					{
						if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer
							&& bDisplayOuterTerminalShihatsu)
						{
							strText = m_nameKeiyunasi;
						}
					}
					else if (iEkiOrder > pCentDedRessya->getSyuuchakuEki())
					{
						if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer
							&& bDisplayOuterTerminalShuchaku)
						{
							strText = m_nameKeiyunasi;
						}
					}
					else if (iEkiOrder > pCentDedRessya->getSihatsuEki() && pCentDedRessya->getSihatsuEki() != -1 &&
						iEkiOrder < pCentDedRessya->getSyuuchakuEki())
					{
						strText = m_nameKeiyunasi;
					}
				}
				else
				{
					CentDedEkiTrack2Cont aCentDedEkiTrack2Cont = aCdDedEki.getCentDedEkiTrack2Cont();
					strText = aCentDedEkiTrack2Cont.get(
						aCentDedEkiJikoku.getRessyaTrackIndex()).getTrackRyakusyou(pCentDedRessya->getRessyahoukou());
				}

				CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
				aRow.getCellCont()->insert(CdCsvCell(strText));
				pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
				iRowIndex++;
			}
			//BeforeOperation2およびAfterOperation2については、1で表示を行い、iRowIndexを二つ進める
			//BeforeOperationBefore2等も同様

			else if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore1)
			{
				tstring strText1;
				tstring strText2;
				tstring strText3;
				tstring strText4;

				const CentDedBeforeOperationCont* pBeforeOperationCont = aCentDedEkiJikoku.getCentDedBeforeOperationCont();
				const CentDedBeforeOperation* pFirstOperation = NULL;
				CdDedJikoku ConnectJikoku;
				for (int idx = pBeforeOperationCont->size() - 1; idx >= 0; idx--)
				{
					if (pBeforeOperationCont->get(idx).getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
					{
						const CentDedBeforeOperationCont* pBeforeOperationOfConnectCont = pBeforeOperationCont->getMuPtr()->get(idx)->getCentDedBeforeOperationCont();
						pFirstOperation = pBeforeOperationOfConnectCont->getMuPtr()->get(0);
						ConnectJikoku = pBeforeOperationCont->get(idx).getConnectJikoku();
						break;
					}
				}

				if (pFirstOperation != NULL)
				{
					if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Out)
					{
						strText1 = nameOut;
						strText2 = encode_Ekijikoku(
							CentDedEkiJikoku::Ekiatsukai_Teisya,
							pFirstOperation->getOutJikoku(),
							bDisplaySecondEkiJikoku,
							bDisplayColonEkiJikoku,
							iSecondRoundChaku,
							iSecondRoundHatsu,
							bDisplay2400,
							true);
						strText3 = joinc(';', pFirstOperation->getOperationNumberOriginal(), true);
						strText4 = pFirstOperation->getInOutLinkCode();
					}
					else if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
					{
						CentDedEkiCont::CdDedEki aCdDedEki = pCdDedEkiCont->get(pCentDedRessya->getValidSihatsuEki());
						strText1 = aCdDedEki.getOuterTerminalJikokuRyaku(pFirstOperation->getOuterShihatsuekiIndex(), true);
						CdDedJikoku aCdDedJikoku = pFirstOperation->getChakuJikoku();
						if (aCdDedJikoku.isNull())
						{
							aCdDedJikoku = pCentDedRessya->getCentDedEkiJikoku(
								pCentDedRessya->getValidSihatsuEki()).getHatsujikoku();
							strText2 = encode_Ekijikoku(
								CentDedEkiJikoku::Ekiatsukai_Tsuuka,
								aCdDedJikoku,
								bDisplaySecondEkiJikoku,
								bDisplayColonEkiJikoku,
								iSecondRoundChaku,
								iSecondRoundHatsu,
								bDisplay2400,
								true);
						}
						else
						{
							strText2 = encode_Ekijikoku(
								CentDedEkiJikoku::Ekiatsukai_Teisya,
								aCdDedJikoku,
								bDisplaySecondEkiJikoku,
								bDisplayColonEkiJikoku,
								iSecondRoundChaku,
								iSecondRoundHatsu,
								bDisplay2400,
								true);
						}
						strText2 += m_nameChaku;
						strText3 = joinc(';', pFirstOperation->getOperationNumberOriginal(), true);
						strText4 = pFirstOperation->getInOutLinkCode();
					}
					//2.00.05 仮運用番号に対応
					else if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Junction)
					{
						strText1 = _T("");
						strText2 = encode_Ekijikoku(
							CentDedEkiJikoku::Ekiatsukai_Teisya,
							pFirstOperation->getOriginJikoku(),
							bDisplaySecondEkiJikoku,
							bDisplayColonEkiJikoku,
							iSecondRoundChaku,
							iSecondRoundHatsu,
							bDisplay2400,
							true);
						strText3 = joinc(';', pFirstOperation->getOperationNumberTemp());
						strText4 = _T("");
					}
				}
				else if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_None)
				{
					if (iEkiOrder < pCentDedRessya->getValidSihatsuEki() && pCentDedRessya->getValidSihatsuEki() != -1)
					{
						if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer
							&& bDisplayOuterTerminalShihatsu)
						{
							strText1 = m_nameKeiyunasi;
							strText2 = m_nameKeiyunasi;
							strText3 = m_nameKeiyunasi;
							strText4 = m_nameKeiyunasi;
						}
						else
						{
							strText1 = _T("");
							strText2 = _T("");
							strText3 = _T("");
							strText4 = _T("");
						}
					}
					else if (iEkiOrder > pCentDedRessya->getValidSyuuchakuEki() && pCentDedRessya->getValidSyuuchakuEki() != -1)
					{
						if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer
							&& bDisplayOuterTerminalShuchaku)
						{
							strText1 = m_nameKeiyunasi;
							strText2 = m_nameKeiyunasi;
							strText3 = m_nameKeiyunasi;
							strText4 = m_nameKeiyunasi;
						}
						else
						{
							strText1 = _T("");
							strText2 = _T("");
							strText3 = _T("");
							strText4 = _T("");
						}
					}
					else if (iEkiOrder > pCentDedRessya->getSihatsuEki() && pCentDedRessya->getSihatsuEki() != -1 &&
						iEkiOrder < pCentDedRessya->getSyuuchakuEki())
					{
						strText1 = m_nameKeiyunasi;
						strText2 = m_nameKeiyunasi;
						strText3 = m_nameKeiyunasi;
						strText4 = m_nameKeiyunasi;
					}

				}

				//  １．Ａ駅の『駅時刻形式』が『発着』
				//  ２．列車Ｆの、Ａ駅での駅扱が『停車』か『通過』のいずれか
				//  ３．列車Ｆの、Ａ駅の着時刻が空
				//  ４．列車Ｆの、Ａ駅の前の駅での駅扱が『経由なし』
				//
				//  この場合は、時刻表ビュー上では、列車ＦのＡ駅での着時刻は " || " 表示とします。
				{
					CentDedEkiJikoku aCentDedEkijikokuPrev;
					if (0 <= iEkiOrder - 1
						&& iEkiOrder - 1 < pCentDedRessya->getCentDedEkiJikokuCount())
					{
						aCentDedEkijikokuPrev =
							pCentDedRessya->getCentDedEkiJikoku(
								iEkiOrder - 1);
					}
					//aCentDedEkijikokuPrev = 前の駅の駅時刻

					if ((aCentDedEkiJikoku.getEkiatsukai() ==
						CentDedEkiJikoku::Ekiatsukai_Teisya ||
						aCentDedEkiJikoku.getEkiatsukai() ==
						CentDedEkiJikoku::Ekiatsukai_Tsuuka) &&
						aCentDedEkiJikoku.getChakujikoku().isNull() &&
						aCentDedEkijikokuPrev.getEkiatsukai() ==
						CentDedEkiJikoku::Ekiatsukai_None &&
						pCentDedRessya->getSihatsuEki() < iEkiOrder)
					{
						strText1 = m_nameKeiyunasi;
						strText2 = m_nameKeiyunasi;
						strText3 = m_nameKeiyunasi;
						strText4 = m_nameKeiyunasi;
					}
				}

				CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
				aRow.getCellCont()->insert(CdCsvCell(strText1));
				pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
				iRowIndex++;
				CdCsvRow	aRow2 = pCdCsvDocument->getRowCont()->get(iRowIndex);
				aRow2.getCellCont()->insert(CdCsvCell(strText2));
				pCdCsvDocument->getRowCont()->set(aRow2, iRowIndex);
				iRowIndex++;
				if (iEnableOperation > 1)
				{
					CdCsvRow	aRow3 = pCdCsvDocument->getRowCont()->get(iRowIndex);
					aRow3.getCellCont()->insert(CdCsvCell(strText3));
					pCdCsvDocument->getRowCont()->set(aRow3, iRowIndex);
					iRowIndex++;
					if (bDisplayInOutLinkCode)
					{
						CdCsvRow	aRow4 = pCdCsvDocument->getRowCont()->get(iRowIndex);
						aRow4.getCellCont()->insert(CdCsvCell(strText4));
						pCdCsvDocument->getRowCont()->set(aRow4, iRowIndex);
						iRowIndex++;
					}
				}
			}
			else if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperation1)
			{
				tstring strText1;
				tstring strText2;

				encode_BeforeOperation(
					pCentDedRessya,
					iEkiOrder,
					aCdYColSpec.getOperationIndex(),
					aCdDedEki,
					bDisplayTsuukaEkiJikoku,
					bDisplaySecondEkiJikoku,
					bDisplayColonEkiJikoku,
					bDisplayOuterTerminalShihatsu,
					bDisplayOuterTerminalShuchaku,
					iSecondRoundChaku,
					iSecondRoundHatsu,
					bDisplay2400,
					strText1,
					strText2);

				CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
				aRow.getCellCont()->insert(CdCsvCell(strText1));
				pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
				iRowIndex++;
				CdCsvRow	aRow2 = pCdCsvDocument->getRowCont()->get(iRowIndex);
				aRow2.getCellCont()->insert(CdCsvCell(strText2));
				pCdCsvDocument->getRowCont()->set(aRow2, iRowIndex);
				iRowIndex++;
			}
			else if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter1)
			{
				tstring strText1;
				tstring strText2;
				tstring strText3;

				const CentDedBeforeOperationCont* pBeforeOperationCont = aCentDedEkiJikoku.getCentDedBeforeOperationCont();
				const CentDedAfterOperation* pLastOperation = NULL;
				CdDedJikoku ReleaseJikoku;
				for (int idx = pBeforeOperationCont->size() - 1; idx >= 0; idx--)
				{
					if (pBeforeOperationCont->get(idx).getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
					{
						const CentDedAfterOperationCont* pAfterOperationOfReleaseCont = pBeforeOperationCont->getMuPtr()->get(idx)->getCentDedAfterOperationCont();
						pLastOperation = pAfterOperationOfReleaseCont->getMuPtr()->get(INT_MAX);
						ReleaseJikoku = pBeforeOperationCont->get(idx).getReleaseJikoku();
						break;
					}
				}
				if (pLastOperation != NULL)
				{
					if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_In)
					{
						strText1 = nameIn;
						strText2 = encode_Ekijikoku(
							CentDedEkiJikoku::Ekiatsukai_Teisya,
							pLastOperation->getInJikoku(),
							bDisplaySecondEkiJikoku,
							bDisplayColonEkiJikoku,
							iSecondRoundChaku,
							iSecondRoundHatsu,
							bDisplay2400,
							false);
						strText3 = pLastOperation->getInOutLinkCode();

					}
					else if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
					{
						CentDedEkiCont::CdDedEki aCdDedEki = pCdDedEkiCont->get(pCentDedRessya->getValidSyuuchakuEki());
						strText1 = aCdDedEki.getOuterTerminalJikokuRyaku(pLastOperation->getOuterShuchakuekiIndex(), true);
						CdDedJikoku aCdDedJikoku = pLastOperation->getHatsuJikoku();
						if (aCdDedJikoku.isNull())
						{
							aCdDedJikoku = pCentDedRessya->getCentDedEkiJikoku(
								pCentDedRessya->getValidSyuuchakuEki()).getChakujikoku();
							strText2 = encode_Ekijikoku(
								CentDedEkiJikoku::Ekiatsukai_Tsuuka,
								aCdDedJikoku,
								bDisplaySecondEkiJikoku,
								bDisplayColonEkiJikoku,
								iSecondRoundChaku,
								iSecondRoundHatsu,
								bDisplay2400,
								false);
						}
						else
						{
							strText2 = encode_Ekijikoku(
								CentDedEkiJikoku::Ekiatsukai_Teisya,
								aCdDedJikoku,
								bDisplaySecondEkiJikoku,
								bDisplayColonEkiJikoku,
								iSecondRoundChaku,
								iSecondRoundHatsu,
								bDisplay2400,
								false);
						}
						strText2 += m_nameHatsu;
						strText3 = pLastOperation->getInOutLinkCode();

					}
					else if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Junction)
					{
						//Ver2.05 1行目には、次列車接続タイプを表示する
						if (pLastOperation->getNextJunctionType() == 1)
						{
							strText1 = nameClassChange;
						}
						else if (pLastOperation->getNextJunctionType() == 2)
						{
							strText1 = namePropertyChange;
						}
						else if (pLastOperation->getNextJunctionType() == 3)
						{
							strText1 = namePropertySame;
						}
						else
						{
							strText1 = _T("");
						}
						strText2 = encode_Ekijikoku(
							CentDedEkiJikoku::Ekiatsukai_Teisya,
							pLastOperation->getTerminalJikoku(),
							bDisplaySecondEkiJikoku,
							bDisplayColonEkiJikoku,
							iSecondRoundChaku,
							iSecondRoundHatsu,
							bDisplay2400,
							false);
					}
				}
				else if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_None)
				{
					if (iEkiOrder < pCentDedRessya->getValidSihatsuEki() && pCentDedRessya->getValidSihatsuEki() != -1)
					{
						if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer
							&& bDisplayOuterTerminalShihatsu)
						{
							strText1 = m_nameKeiyunasi;
							strText2 = m_nameKeiyunasi;
							strText3 = m_nameKeiyunasi;
						}
						else
						{
							strText1 = _T("");
							strText2 = _T("");
							strText3 = _T("");
						}
					}
					else if (iEkiOrder > pCentDedRessya->getValidSyuuchakuEki() && pCentDedRessya->getValidSyuuchakuEki() != -1)
					{
						if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer
							&& bDisplayOuterTerminalShuchaku)
						{
							strText1 = m_nameKeiyunasi;
							strText2 = m_nameKeiyunasi;
							strText3 = m_nameKeiyunasi;
						}
						else
						{
							strText1 = _T("");
							strText2 = _T("");
							strText3 = _T("");
						}
					}
					else if (iEkiOrder > pCentDedRessya->getSihatsuEki() && pCentDedRessya->getSihatsuEki() != -1 &&
						iEkiOrder < pCentDedRessya->getSyuuchakuEki())
					{
						strText1 = m_nameKeiyunasi;
						strText2 = m_nameKeiyunasi;
						strText3 = m_nameKeiyunasi;
					}
				}

				//  １．Ａ駅の『駅時刻形式』が『発着』
				//  ２．列車Ｆの、Ａ駅での駅扱が『停車』か『通過』のいずれか
				//  ３．列車Ｆの、Ａ駅の着時刻が空
				//  ４．列車Ｆの、Ａ駅の前の駅での駅扱が『経由なし』
				//
				//  この場合は、時刻表ビュー上では、列車ＦのＡ駅での着時刻は " || " 表示とします。
				{
					CentDedEkiJikoku aCentDedEkijikokuPrev;
					if (0 <= iEkiOrder - 1
						&& iEkiOrder - 1 < pCentDedRessya->getCentDedEkiJikokuCount())
					{
						aCentDedEkijikokuPrev =
							pCentDedRessya->getCentDedEkiJikoku(
								iEkiOrder - 1);
					}
					//aCentDedEkijikokuPrev = 前の駅の駅時刻

					if ((aCentDedEkiJikoku.getEkiatsukai() ==
						CentDedEkiJikoku::Ekiatsukai_Teisya ||
						aCentDedEkiJikoku.getEkiatsukai() ==
						CentDedEkiJikoku::Ekiatsukai_Tsuuka) &&
						aCentDedEkiJikoku.getChakujikoku().isNull() &&
						aCentDedEkijikokuPrev.getEkiatsukai() ==
						CentDedEkiJikoku::Ekiatsukai_None &&
						pCentDedRessya->getSihatsuEki() < iEkiOrder)
					{
						strText1 = m_nameKeiyunasi;
						strText2 = m_nameKeiyunasi;
						strText3 = m_nameKeiyunasi;
					}
				}

				CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
				aRow.getCellCont()->insert(CdCsvCell(strText1));
				pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
				iRowIndex++;
				CdCsvRow	aRow2 = pCdCsvDocument->getRowCont()->get(iRowIndex);
				aRow2.getCellCont()->insert(CdCsvCell(strText2));
				pCdCsvDocument->getRowCont()->set(aRow2, iRowIndex);
				iRowIndex++;
				if (iEnableOperation > 1 && bDisplayInOutLinkCode)
				{
					CdCsvRow	aRow3 = pCdCsvDocument->getRowCont()->get(iRowIndex);
					aRow3.getCellCont()->insert(CdCsvCell(strText3));
					pCdCsvDocument->getRowCont()->set(aRow3, iRowIndex);
					iRowIndex++;
				}
			}
			else if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore1)
			{
				tstring strText1;
				tstring strText2;
				tstring strText3;
				tstring strText4;

				const CentDedAfterOperationCont* pAfterOperationCont = aCentDedEkiJikoku.getCentDedAfterOperationCont();
				const CentDedBeforeOperation* pFirstOperation = NULL;
				CdDedJikoku ConnectJikoku;
				for (int idx = 0; idx < pAfterOperationCont->size(); idx++)
				{
					if (pAfterOperationCont->get(idx).getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
					{
						const CentDedBeforeOperationCont* pBeforeOperationOfConnectCont = pAfterOperationCont->getMuPtr()->get(idx)->getCentDedBeforeOperationCont();
						pFirstOperation = pBeforeOperationOfConnectCont->getMuPtr()->get(0);
						ConnectJikoku = pAfterOperationCont->get(idx).getConnectJikoku();
						break;
					}
				}

				if (pFirstOperation != NULL)
				{
					if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Out)
					{
						strText1 = nameOut;
						strText2 = encode_Ekijikoku(
							CentDedEkiJikoku::Ekiatsukai_Teisya,
							pFirstOperation->getOutJikoku(),
							bDisplaySecondEkiJikoku,
							bDisplayColonEkiJikoku,
							iSecondRoundChaku,
							iSecondRoundHatsu,
							bDisplay2400,
							true);
						strText3 = joinc(';', pFirstOperation->getOperationNumberOriginal(), true);
						strText4 = pFirstOperation->getInOutLinkCode();
					}
					else if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
					{
						CentDedEkiCont::CdDedEki aCdDedEki = pCdDedEkiCont->get(pCentDedRessya->getValidSihatsuEki());
						strText1 = aCdDedEki.getOuterTerminalJikokuRyaku(pFirstOperation->getOuterShihatsuekiIndex(), true);
						CdDedJikoku aCdDedJikoku = pFirstOperation->getChakuJikoku();
						if (aCdDedJikoku.isNull())
						{
							aCdDedJikoku = pCentDedRessya->getCentDedEkiJikoku(
								pCentDedRessya->getValidSihatsuEki()).getHatsujikoku();
							strText2 = encode_Ekijikoku(
								CentDedEkiJikoku::Ekiatsukai_Tsuuka,
								aCdDedJikoku,
								bDisplaySecondEkiJikoku,
								bDisplayColonEkiJikoku,
								iSecondRoundChaku,
								iSecondRoundHatsu,
								bDisplay2400,
								true);
						}
						else
						{
							strText2 = encode_Ekijikoku(
								CentDedEkiJikoku::Ekiatsukai_Teisya,
								aCdDedJikoku,
								bDisplaySecondEkiJikoku,
								bDisplayColonEkiJikoku,
								iSecondRoundChaku,
								iSecondRoundHatsu,
								bDisplay2400,
								true);
						}
						strText2 += m_nameChaku;
						strText3 = joinc(';', pFirstOperation->getOperationNumberOriginal(), true);
						strText4 = pFirstOperation->getInOutLinkCode();
					}
					//2.00.05 仮運用番号に対応
					else if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Junction)
					{
						strText1 = _T("");
						strText2 = encode_Ekijikoku(
							CentDedEkiJikoku::Ekiatsukai_Teisya,
							pFirstOperation->getOriginJikoku(),
							bDisplaySecondEkiJikoku,
							bDisplayColonEkiJikoku,
							iSecondRoundChaku,
							iSecondRoundHatsu,
							bDisplay2400,
							true);
						strText3 = joinc(';', pFirstOperation->getOperationNumberTemp());
						strText4 = _T("");
					}
				}
				else if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_None)
				{
					if (iEkiOrder < pCentDedRessya->getValidSihatsuEki() && pCentDedRessya->getValidSihatsuEki() != -1)
					{
						if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer
							&& bDisplayOuterTerminalShihatsu)
						{
							strText1 = m_nameKeiyunasi;
							strText2 = m_nameKeiyunasi;
							strText3 = m_nameKeiyunasi;
							strText4 = m_nameKeiyunasi;
						}
						else
						{
							strText1 = _T("");
							strText2 = _T("");
							strText3 = _T("");
							strText4 = _T("");
						}
					}
					else if (iEkiOrder > pCentDedRessya->getValidSyuuchakuEki() && pCentDedRessya->getValidSyuuchakuEki() != -1)
					{
						if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer
							&& bDisplayOuterTerminalShuchaku)
						{
							strText1 = m_nameKeiyunasi;
							strText2 = m_nameKeiyunasi;
							strText3 = m_nameKeiyunasi;
							strText4 = m_nameKeiyunasi;
						}
						else
						{
							strText1 = _T("");
							strText2 = _T("");
							strText3 = _T("");
							strText4 = _T("");
						}
					}
					else if (iEkiOrder > pCentDedRessya->getSihatsuEki() && pCentDedRessya->getSihatsuEki() != -1 &&
						iEkiOrder < pCentDedRessya->getSyuuchakuEki())
					{
						strText1 = m_nameKeiyunasi;
						strText2 = m_nameKeiyunasi;
						strText3 = m_nameKeiyunasi;
						strText4 = m_nameKeiyunasi;
					}

				}

				//  １．Ａ駅の『駅時刻形式』が『発着』
				//  ２．列車Ｆの、Ａ駅での駅扱が『停車』か『通過』のいずれか
				//  ３．列車Ｆの、Ａ駅の発時刻が空
				//  ４．列車Ｆの、Ａ駅の次の駅での駅扱が『経由なし』
				//
				//	  この場合は、時刻表ビュー上では、列車ＦのＡ駅での発時刻は 
				//	" || " 表示とします
				{
					CentDedEkiJikoku aCentDedEkijikokuNext;
					if (0 <= iEkiOrder + 1
						&& iEkiOrder + 1 < pCentDedRessya->getCentDedEkiJikokuCount())
					{
						aCentDedEkijikokuNext =
							pCentDedRessya->getCentDedEkiJikoku(
								iEkiOrder + 1);
					}
					//aCentDedEkijikokuNext = 次の駅の駅時刻

					if ((aCentDedEkiJikoku.getEkiatsukai() ==
						CentDedEkiJikoku::Ekiatsukai_Teisya ||
						aCentDedEkiJikoku.getEkiatsukai() ==
						CentDedEkiJikoku::Ekiatsukai_Tsuuka) &&
						aCentDedEkiJikoku.getHatsujikoku().isNull() &&
						aCentDedEkijikokuNext.getEkiatsukai() ==
						CentDedEkiJikoku::Ekiatsukai_None &&
						pCentDedRessya->getSyuuchakuEki() > iEkiOrder)
					{
						strText1 = m_nameKeiyunasi;
						strText2 = m_nameKeiyunasi;
						strText3 = m_nameKeiyunasi;
						strText4 = m_nameKeiyunasi;
					}
				}

				CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
				aRow.getCellCont()->insert(CdCsvCell(strText1));
				pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
				iRowIndex++;
				CdCsvRow	aRow2 = pCdCsvDocument->getRowCont()->get(iRowIndex);
				aRow2.getCellCont()->insert(CdCsvCell(strText2));
				pCdCsvDocument->getRowCont()->set(aRow2, iRowIndex);
				iRowIndex++;
				if (iEnableOperation > 1)
				{
					CdCsvRow	aRow3 = pCdCsvDocument->getRowCont()->get(iRowIndex);
					aRow3.getCellCont()->insert(CdCsvCell(strText3));
					pCdCsvDocument->getRowCont()->set(aRow3, iRowIndex);
					iRowIndex++;
					if (bDisplayInOutLinkCode)
					{
						CdCsvRow	aRow4 = pCdCsvDocument->getRowCont()->get(iRowIndex);
						aRow4.getCellCont()->insert(CdCsvCell(strText4));
						pCdCsvDocument->getRowCont()->set(aRow4, iRowIndex);
						iRowIndex++;
					}
				}
			}
			else if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperation1)
			{
				tstring strText1;
				tstring strText2;

				encode_AfterOperation(
					pCentDedRessya,
					iEkiOrder,
					aCdYColSpec.getOperationIndex(),
					aCdDedEki,
					bDisplayTsuukaEkiJikoku,
					bDisplaySecondEkiJikoku,
					bDisplayColonEkiJikoku,
					bDisplayOuterTerminalShihatsu,
					bDisplayOuterTerminalShuchaku,
					iSecondRoundChaku,
					iSecondRoundHatsu,
					bDisplay2400,
					strText1,
					strText2);

				CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
				aRow.getCellCont()->insert(CdCsvCell(strText1));
				pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
				iRowIndex++;
				CdCsvRow	aRow2 = pCdCsvDocument->getRowCont()->get(iRowIndex);
				aRow2.getCellCont()->insert(CdCsvCell(strText2));
				pCdCsvDocument->getRowCont()->set(aRow2, iRowIndex);
				iRowIndex++;
			}
			else if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter1)
			{
				tstring strText1;
				tstring strText2;
				tstring strText3;

				const CentDedAfterOperationCont* pAfterOperationCont = aCentDedEkiJikoku.getCentDedAfterOperationCont();
				const CentDedAfterOperation* pLastOperation = NULL;
				CdDedJikoku ReleaseJikoku;
				for (int idx = 0; idx < pAfterOperationCont->size(); idx++)
				{
					if (pAfterOperationCont->get(idx).getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
					{
						const CentDedAfterOperationCont* pAfterOperationOfReleaseCont = pAfterOperationCont->getMuPtr()->get(idx)->getCentDedAfterOperationCont();
						pLastOperation = pAfterOperationOfReleaseCont->getMuPtr()->get(INT_MAX);
						ReleaseJikoku = pAfterOperationCont->get(idx).getReleaseJikoku();
						break;
					}
				}

				if (pLastOperation != NULL)
				{
					if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_In)
					{
						strText1 = nameIn;
						strText2 = encode_Ekijikoku(
							CentDedEkiJikoku::Ekiatsukai_Teisya,
							pLastOperation->getInJikoku(),
							bDisplaySecondEkiJikoku,
							bDisplayColonEkiJikoku,
							iSecondRoundChaku,
							iSecondRoundHatsu,
							bDisplay2400,
							false);
						strText3 = pLastOperation->getInOutLinkCode();

					}
					else if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
					{
						CentDedEkiCont::CdDedEki aCdDedEki = pCdDedEkiCont->get(pCentDedRessya->getValidSyuuchakuEki());
						strText1 = aCdDedEki.getOuterTerminalJikokuRyaku(pLastOperation->getOuterShuchakuekiIndex(), true);
						CdDedJikoku aCdDedJikoku = pLastOperation->getHatsuJikoku();
						if (aCdDedJikoku.isNull())
						{
							aCdDedJikoku = pCentDedRessya->getCentDedEkiJikoku(
								pCentDedRessya->getValidSyuuchakuEki()).getChakujikoku();
							strText2 = encode_Ekijikoku(
								CentDedEkiJikoku::Ekiatsukai_Tsuuka,
								aCdDedJikoku,
								bDisplaySecondEkiJikoku,
								bDisplayColonEkiJikoku,
								iSecondRoundChaku,
								iSecondRoundHatsu,
								bDisplay2400,
								false);
						}
						else
						{
							strText2 = encode_Ekijikoku(
								CentDedEkiJikoku::Ekiatsukai_Teisya,
								aCdDedJikoku,
								bDisplaySecondEkiJikoku,
								bDisplayColonEkiJikoku,
								iSecondRoundChaku,
								iSecondRoundHatsu,
								bDisplay2400,
								false);
						}
						strText2 += m_nameHatsu;
						strText3 = pLastOperation->getInOutLinkCode();

					}
					else if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Junction)
					{
						//Ver2.05 1行目には、次列車接続タイプを表示する
						if (pLastOperation->getNextJunctionType() == 1)
						{
							strText1 = nameClassChange;
						}
						else if (pLastOperation->getNextJunctionType() == 2)
						{
							strText1 = namePropertyChange;
						}
						else if (pLastOperation->getNextJunctionType() == 3)
						{
							strText1 = namePropertySame;
						}
						else
						{
							strText1 = _T("");
						}
						strText2 = encode_Ekijikoku(
							CentDedEkiJikoku::Ekiatsukai_Teisya,
							pLastOperation->getTerminalJikoku(),
							bDisplaySecondEkiJikoku,
							bDisplayColonEkiJikoku,
							iSecondRoundChaku,
							iSecondRoundHatsu,
							bDisplay2400,
							false);
					}
				}
				else if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_None)
				{
					if (iEkiOrder < pCentDedRessya->getValidSihatsuEki() && pCentDedRessya->getValidSihatsuEki() != -1)
					{
						if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer
							&& bDisplayOuterTerminalShihatsu)
						{
							strText1 = m_nameKeiyunasi;
							strText2 = m_nameKeiyunasi;
							strText3 = m_nameKeiyunasi;
						}
						else
						{
							strText1 = _T("");
							strText2 = _T("");
							strText3 = _T("");
						}
					}
					else if (iEkiOrder > pCentDedRessya->getValidSyuuchakuEki() && pCentDedRessya->getValidSyuuchakuEki() != -1)
					{
						if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer
							&& bDisplayOuterTerminalShuchaku)
						{
							strText1 = m_nameKeiyunasi;
							strText2 = m_nameKeiyunasi;
							strText3 = m_nameKeiyunasi;
						}
						else
						{
							strText1 = _T("");
							strText2 = _T("");
							strText3 = _T("");
						}
					}
					else if (iEkiOrder > pCentDedRessya->getSihatsuEki() && pCentDedRessya->getSihatsuEki() != -1 &&
						iEkiOrder < pCentDedRessya->getSyuuchakuEki())
					{
						strText1 = m_nameKeiyunasi;
						strText2 = m_nameKeiyunasi;
						strText3 = m_nameKeiyunasi;
					}

				}

				//  １．Ａ駅の『駅時刻形式』が『発着』
				//  ２．列車Ｆの、Ａ駅での駅扱が『停車』か『通過』のいずれか
				//  ３．列車Ｆの、Ａ駅の発時刻が空
				//  ４．列車Ｆの、Ａ駅の次の駅での駅扱が『経由なし』
				//
				//	  この場合は、時刻表ビュー上では、列車ＦのＡ駅での発時刻は 
				//	" || " 表示とします
				{
					CentDedEkiJikoku aCentDedEkijikokuNext;
					if (0 <= iEkiOrder + 1
						&& iEkiOrder + 1 < pCentDedRessya->getCentDedEkiJikokuCount())
					{
						aCentDedEkijikokuNext =
							pCentDedRessya->getCentDedEkiJikoku(
								iEkiOrder + 1);
					}
					//aCentDedEkijikokuNext = 次の駅の駅時刻

					if ((aCentDedEkiJikoku.getEkiatsukai() ==
						CentDedEkiJikoku::Ekiatsukai_Teisya ||
						aCentDedEkiJikoku.getEkiatsukai() ==
						CentDedEkiJikoku::Ekiatsukai_Tsuuka) &&
						aCentDedEkiJikoku.getHatsujikoku().isNull() &&
						aCentDedEkijikokuNext.getEkiatsukai() ==
						CentDedEkiJikoku::Ekiatsukai_None &&
						pCentDedRessya->getSyuuchakuEki() > iEkiOrder)
					{
						strText1 = m_nameKeiyunasi;
						strText2 = m_nameKeiyunasi;
						strText3 = m_nameKeiyunasi;
					}
				}

				CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
				aRow.getCellCont()->insert(CdCsvCell(strText1));
				pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
				iRowIndex++;
				CdCsvRow	aRow2 = pCdCsvDocument->getRowCont()->get(iRowIndex);
				aRow2.getCellCont()->insert(CdCsvCell(strText2));
				pCdCsvDocument->getRowCont()->set(aRow2, iRowIndex);
				iRowIndex++;
				if (iEnableOperation > 1 && bDisplayInOutLinkCode)
				{
					CdCsvRow	aRow3 = pCdCsvDocument->getRowCont()->get(iRowIndex);
					aRow3.getCellCont()->insert(CdCsvCell(strText3));
					pCdCsvDocument->getRowCont()->set(aRow3, iRowIndex);
					iRowIndex++;
				}
			}
		}
	}

	//＜2.17＞ <路線外終着駅>
	if (iRv >= 0 && bDisplayOuterTerminalShuchaku)
	{
		tstring strText1;
		tstring strText2;

		const CentDedAfterOperation aLastOperation = pCentDedRessya->getLastOperation();
		if (aLastOperation.getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
		{
			CentDedEkiCont::CdDedEki aCdDedEki = pCdDedEkiCont->get(pCentDedRessya->getValidSyuuchakuEki());
			strText1 = aCdDedEki.getOuterTerminalJikokuRyaku(aLastOperation.getOuterShuchakuekiIndex(), true);

			if (!(aLastOperation.getOuterShuchakuJikoku().isNull()))
			{
				CdDedJikoku aCdDedJikoku
					= aLastOperation.getOuterShuchakuJikoku();
				strText2 = encode_Ekijikoku(
					CentDedEkiJikoku::Ekiatsukai_Teisya,
					aCdDedJikoku,
					bDisplaySecondEkiJikoku,
					bDisplayColonEkiJikoku,
					iSecondRoundChaku,
					iSecondRoundHatsu,
					bDisplay2400,
					true);
			}
		}

		CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
		aRow.getCellCont()->insert(CdCsvCell(strText1));
		pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
		iRowIndex++;
		CdCsvRow	aRow2 = pCdCsvDocument->getRowCont()->get(iRowIndex);
		aRow2.getCellCont()->insert(CdCsvCell(strText2));
		pCdCsvDocument->getRowCont()->set(aRow2, iRowIndex);
		iRowIndex++;
	}
	//＜2.11＞[列1="備考" AND 列2=""]の列　備考列
	if ( iRv >= 0 )
	{
			CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex) ;
			aRow.getCellCont()->insert( CdCsvCell( pCentDedRessya->getBikou() ) ) ;
			pCdCsvDocument->getRowCont()->set( aRow , iRowIndex) ;
	}
	return iRv ;
}

int CconvJikokuhyouCsv::encode_AddRessyaNull(
	CdCsvDocument* pCdCsvDocument,
	const bool bDisplayRessyamei,
	const int iEnableOperation,
	const bool bDisplayOuterTerminalShihatsu,
	const bool bDisplayOuterTerminalShuchaku)
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
	if (iRv >= 0 && iEnableOperation > 1)
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
	if (iRv >= 0)
	{
		CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
		aRow.getCellCont()->insert(CdCsvCell());
		pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
		iRowIndex++;
	}

	//＜2.12＞ <始発駅作業>
	if (iRv >= 0)
	{
		CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
		aRow.getCellCont()->insert(CdCsvCell());
		pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
		iRowIndex++;
		CdCsvRow	aRow2 = pCdCsvDocument->getRowCont()->get(iRowIndex);
		aRow2.getCellCont()->insert(CdCsvCell());
		pCdCsvDocument->getRowCont()->set(aRow2, iRowIndex);
		iRowIndex++;
		if (iEnableOperation > 1)
		{
			CdCsvRow	aRow3 = pCdCsvDocument->getRowCont()->get(iRowIndex);
			aRow3.getCellCont()->insert(CdCsvCell());
			pCdCsvDocument->getRowCont()->set(aRow3, iRowIndex);
			iRowIndex++;
		}
	}

	//＜2.13＞ <終着駅名>
	if (iRv >= 0)
	{
		CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
		aRow.getCellCont()->insert(CdCsvCell());
		pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
		iRowIndex++;
	}

	//＜2.14＞ <終着駅作業>
	if (iRv >= 0)
	{

		CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
		aRow.getCellCont()->insert(CdCsvCell());
		pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
		iRowIndex++;
		CdCsvRow	aRow2 = pCdCsvDocument->getRowCont()->get(iRowIndex);
		aRow2.getCellCont()->insert(CdCsvCell());
		pCdCsvDocument->getRowCont()->set(aRow2, iRowIndex);
		iRowIndex++;
	}

	//＜2.15＞ <路線外始発駅>
	if (iRv >= 0 && bDisplayOuterTerminalShihatsu)
	{
		CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
		aRow.getCellCont()->insert(CdCsvCell());
		pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
		iRowIndex++;
		CdCsvRow	aRow2 = pCdCsvDocument->getRowCont()->get(iRowIndex);
		aRow2.getCellCont()->insert(CdCsvCell());
		pCdCsvDocument->getRowCont()->set(aRow2, iRowIndex);
		iRowIndex++;
	}
	//＜2.16＞10行目〜 駅時刻
	
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
	//＜2.17＞ <路線外終着駅>
	if (iRv >= 0 && bDisplayOuterTerminalShuchaku)
	{
		CdCsvRow	aRow = pCdCsvDocument->getRowCont()->get(iRowIndex);
		aRow.getCellCont()->insert(CdCsvCell());
		pCdCsvDocument->getRowCont()->set(aRow, iRowIndex);
		iRowIndex++;
		CdCsvRow	aRow2 = pCdCsvDocument->getRowCont()->get(iRowIndex);
		aRow2.getCellCont()->insert(CdCsvCell());
		pCdCsvDocument->getRowCont()->set(aRow2, iRowIndex);
		iRowIndex++;
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
CconvJikokuhyouCsv::CconvJikokuhyouCsv(
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
	//@name	CconvJikokuhyouCsv
	// ********************************
int CconvJikokuhyouCsv::encode( 
		const CentDedRosen& aCentDedRosen , 
		int iDiaIndex , 
		ERessyahoukou eRessyahoukou ,
		int iRessyaIndex , int iRessyaCount ,
		const bool bDisplayTsuukaEkiJikoku,
		const bool bDisplaySecondEkiJikoku,
		const bool bDisplayColonEkiJikoku,
		const bool bDisplayParentSyubetsu,
		const bool bDisplayRessyamei,
		const int iEnableOperation,
		const bool bDisplayOuterTerminalShihatsu,
		const bool bDisplayOuterTerminalShuchaku,
		const int iSecondRoundChaku,
		const int iSecondRoundHatsu,
		const bool bDisplay2400,
		const int iOperationNumberRows,
		const bool bDisplayInOutLinkCode,
		CdCsvDocument* pCdCsvDocument ) 
{
	int iRv = 0 ;
	
	const CentDedEkiCont* pCentDedEkiCont = NULL ;
	const Mu<CentDedEkiCont::CdDedEki>* pCdDedEkiCont = NULL ;
	const Mu<const CentDedRessyasyubetsu*>* pCentDedRessyasyubetsuContGet = NULL ;
	const CentDedDia* pCentDedDia = NULL ;
	const Mu<const CentDedRessya*>* pCentDedRessyaCont = NULL ;

	// --------------------------------
	//	オブジェクトCdCsvDocument をクリア
	// --------------------------------
	if ( iRv >= 0 )
	{
		pCentDedEkiCont = aCentDedRosen.getCentDedEkiCont() ;
		pCdDedEkiCont = aCentDedRosen.getCentDedEkiCont()
			->getMuPtr( eRessyahoukou ) ;
		pCentDedRessyasyubetsuContGet = aCentDedRosen.getCentDedRessyasyubetsuCont()->getMuPtr() ; 
		pCentDedDia = aCentDedRosen.getCentDedDiaCont()->getMuPtr()->get( iDiaIndex ) ;
		if ( pCentDedDia == NULL )
		{
			iRv = -1 ;	//	iDiaIndex が不正です。
		}
	}
	if ( iRv >= 0 )
	{
		pCentDedRessyaCont = pCentDedDia->getCentDedRessyaCont( eRessyahoukou )->getMuPtr() ;
	}
	//pCentDedRessyaCont = 列車のコンテナ
	if ( iRv >= 0 )
	{
		if ( !( 0 <= iRessyaIndex && iRessyaIndex < pCentDedRessyaCont->size() ) 
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
			iRessyaIndex + iRessyaCount <= pCentDedRessyaCont->size() ) )
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
	if (iRv >= 0)
	{
		CdCsvRow	aRow;
		aRow.getCellCont()->insert(CdCsvCell(m_nameShihatsuEkimei));
		aRow.getCellCont()->insert(CdCsvCell());
		pCdCsvDocument->getRowCont()->insert(aRow);
	}
	//＜2.12＞12行目 <始発駅作業>
	if (iRv >= 0)
	{
		CdCsvRow	aRow;
		aRow.getCellCont()->insert(CdCsvCell(m_nameOperation_Shihatsu));
		aRow.getCellCont()->insert(CdCsvCell());
		pCdCsvDocument->getRowCont()->insert(aRow);
		CdCsvRow	aRow2;
		aRow2.getCellCont()->insert(CdCsvCell());
		aRow2.getCellCont()->insert(CdCsvCell());
		pCdCsvDocument->getRowCont()->insert(aRow2);
		if (iEnableOperation > 1)
		{
			CdCsvRow	aRow3;
			aRow3.getCellCont()->insert(CdCsvCell());
			aRow3.getCellCont()->insert(CdCsvCell());
			pCdCsvDocument->getRowCont()->insert(aRow3);
			if (bDisplayInOutLinkCode)
			{
				CdCsvRow	aRow4;
				aRow4.getCellCont()->insert(CdCsvCell());
				aRow4.getCellCont()->insert(CdCsvCell());
				pCdCsvDocument->getRowCont()->insert(aRow4);
			}
		}
	}
	//＜2.13＞13行目 <終着駅名>
	if (iRv >= 0)
	{
		CdCsvRow	aRow;
		aRow.getCellCont()->insert(CdCsvCell(m_nameShuchakuEkimei));
		aRow.getCellCont()->insert(CdCsvCell());
		pCdCsvDocument->getRowCont()->insert(aRow);
	}
	//＜2.14＞14行目 <終着駅作業>
	if (iRv >= 0)
	{
		CdCsvRow	aRow;
		aRow.getCellCont()->insert(CdCsvCell(m_nameOperation_Shuchaku));
		aRow.getCellCont()->insert(CdCsvCell());
		pCdCsvDocument->getRowCont()->insert(aRow);
		CdCsvRow	aRow2;
		aRow2.getCellCont()->insert(CdCsvCell());
		aRow2.getCellCont()->insert(CdCsvCell());
		pCdCsvDocument->getRowCont()->insert(aRow2);
		if (iEnableOperation > 1 && bDisplayInOutLinkCode)
		{
			CdCsvRow	aRow3;
			aRow3.getCellCont()->insert(CdCsvCell());
			aRow3.getCellCont()->insert(CdCsvCell());
			pCdCsvDocument->getRowCont()->insert(aRow3);
		}
	}
	//＜2.15＞15行目 <路線外始発駅>
	if (iRv >= 0 && bDisplayOuterTerminalShihatsu)
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

	//始発駅・終着駅
	//路線外始発
	//前後作業
	//＜2.16＞16行目〜 駅時刻
	if (iRv >= 0)
	{
		m_CdYColSpecCont =
			CdYColSpecCont(
				pCentDedEkiCont, eRessyahoukou,
				false, //AllJikoku
				false, //Customize
				false, //ShihatsuShuchakuEkimei
				true,  //Ressyamei
				iEnableOperation, //Operation
				false, //OuterShihatsu
				false,//OuterSyuchaku
				1,//iOperationNumberRows
				false);

		for (int idx = m_CdYColSpecCont.getColumnNumber_Ekijikoku_begin();
			idx < m_CdYColSpecCont.getColumnNumber_Ekijikoku_end(); idx++)
		{
			CdYColSpec aCdYColSpec = m_CdYColSpecCont.ColumnNumberToSpec(idx);

			CentDedEkiCont::CdDedEki aCdDedEki = pCdDedEkiCont->get(aCdYColSpec.getEkiOrder());

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
			else if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperation1)
			{
				strChakuHatsu = m_nameBeforeOperation;
				strChakuHatsu += to_tstring(aCdYColSpec.getOperationIndex() + 1);
				CdCsvRow	aRow;
				aRow.getCellCont()->insert(CdCsvCell(strEkimei));
				aRow.getCellCont()->insert(CdCsvCell(strChakuHatsu));
				pCdCsvDocument->getRowCont()->insert(aRow);
				CdCsvRow	aRow2;
				aRow2.getCellCont()->insert(CdCsvCell());
				aRow2.getCellCont()->insert(CdCsvCell());
				pCdCsvDocument->getRowCont()->insert(aRow2);
			}
			else if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperation1)
			{
				strChakuHatsu = m_nameAfterOperation;
				strChakuHatsu += to_tstring(aCdYColSpec.getOperationIndex() + 1);
				CdCsvRow	aRow;
				aRow.getCellCont()->insert(CdCsvCell(strEkimei));
				aRow.getCellCont()->insert(CdCsvCell(strChakuHatsu));
				pCdCsvDocument->getRowCont()->insert(aRow);
				CdCsvRow	aRow2;
				aRow2.getCellCont()->insert(CdCsvCell());
				aRow2.getCellCont()->insert(CdCsvCell());
				pCdCsvDocument->getRowCont()->insert(aRow2);
			}
			else if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore1)
			{
				strChakuHatsu = m_nameOperationConnectBefore;
				CdCsvRow	aRow;
				aRow.getCellCont()->insert(CdCsvCell(strEkimei));
				aRow.getCellCont()->insert(CdCsvCell(strChakuHatsu));
				pCdCsvDocument->getRowCont()->insert(aRow);
				CdCsvRow	aRow2;
				aRow2.getCellCont()->insert(CdCsvCell());
				aRow2.getCellCont()->insert(CdCsvCell());
				pCdCsvDocument->getRowCont()->insert(aRow2);
				if (iEnableOperation > 1)
				{
					pCdCsvDocument->getRowCont()->insert(aRow2);
					if (bDisplayInOutLinkCode)
					{
						pCdCsvDocument->getRowCont()->insert(aRow2);
					}
				}
			}
			else if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter1)
			{
				strChakuHatsu = m_nameOperationReleaseAfter;
				CdCsvRow	aRow;
				aRow.getCellCont()->insert(CdCsvCell(strEkimei));
				aRow.getCellCont()->insert(CdCsvCell(strChakuHatsu));
				pCdCsvDocument->getRowCont()->insert(aRow);
				CdCsvRow	aRow2;
				aRow2.getCellCont()->insert(CdCsvCell());
				aRow2.getCellCont()->insert(CdCsvCell());
				pCdCsvDocument->getRowCont()->insert(aRow2);
				if (iEnableOperation > 1 && bDisplayInOutLinkCode)
				{
					pCdCsvDocument->getRowCont()->insert(aRow2);
				}
			}
			else if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore1)
			{
				strChakuHatsu = m_nameOperationConnectBefore;
				CdCsvRow	aRow;
				aRow.getCellCont()->insert(CdCsvCell(strEkimei));
				aRow.getCellCont()->insert(CdCsvCell(strChakuHatsu));
				pCdCsvDocument->getRowCont()->insert(aRow);
				CdCsvRow	aRow2;
				aRow2.getCellCont()->insert(CdCsvCell());
				aRow2.getCellCont()->insert(CdCsvCell());
				pCdCsvDocument->getRowCont()->insert(aRow2);
				if (iEnableOperation > 1)
				{
					pCdCsvDocument->getRowCont()->insert(aRow2);
					if (bDisplayInOutLinkCode)
					{
						pCdCsvDocument->getRowCont()->insert(aRow2);
					}
				}
			}
			else if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter1)
			{
				strChakuHatsu = m_nameOperationReleaseAfter;
				CdCsvRow	aRow;
				aRow.getCellCont()->insert(CdCsvCell(strEkimei));
				aRow.getCellCont()->insert(CdCsvCell(strChakuHatsu));
				pCdCsvDocument->getRowCont()->insert(aRow);
				CdCsvRow	aRow2;
				aRow2.getCellCont()->insert(CdCsvCell());
				aRow2.getCellCont()->insert(CdCsvCell());
				pCdCsvDocument->getRowCont()->insert(aRow2);
				if (iEnableOperation > 1 && bDisplayInOutLinkCode)
				{
					pCdCsvDocument->getRowCont()->insert(aRow2);
				}
			}

		}
	}

	//＜2.17＞<路線外終着駅>
	if (iRv >= 0 && bDisplayOuterTerminalShuchaku)
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
	for ( int idxRessya = iRessyaIndex ; 
		iRv >= 0 && idxRessya < iRessyaIndex + iRessyaCount ; 
		idxRessya ++ )
	{
		const CentDedRessya* pCentDedRessya = pCentDedRessyaCont->get( idxRessya ) ; 

		if ( pCentDedRessya->isNull() )
		{
			iRv = encode_AddRessyaNull( 
					pCdCsvDocument,
					bDisplayRessyamei,
					iEnableOperation,
					bDisplayOuterTerminalShihatsu,
					bDisplayOuterTerminalShuchaku) ;
		}
		else
		{
			iRv = encode_AddRessya( 
					pCentDedRessyasyubetsuContGet , 
					pCentDedRessya , 
					pCdCsvDocument ,
					pCentDedEkiCont,
					pCdDedEkiCont,
					bDisplayTsuukaEkiJikoku,
					bDisplaySecondEkiJikoku,
					bDisplayColonEkiJikoku,
					bDisplayParentSyubetsu,
					bDisplayRessyamei,
					iEnableOperation,
					bDisplayOuterTerminalShihatsu,
					bDisplayOuterTerminalShuchaku,
					iSecondRoundChaku,
					iSecondRoundHatsu,
					bDisplay2400,
					iOperationNumberRows,
					bDisplayInOutLinkCode) ;
		}
	}
	
	return iRv ;
}
} //namespace ConvJikokuhyouCsv

