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
//	CWndDcdGridCrossingCheck.cpp
//	$Id: CWndDcdGridCrossingCheck.cpp  $
// ****************************************************************
*/
/** @file */
#include "stdafx.h"

#include "logmsg¥LogMsg.h"
#include "NsOu¥OuNew.h"
#include "NsOu¥dynamic_castOu.h"
#include "str¥strtoint.h"
#include "DcDraw¥CDcdTargetGetDC.h"
#include "DcDraw¥CConverter_WinGdi.h"
#include "MfcUtil/MfcUtil.h"
#include "Str/strToWstr.h"
#include "DcDraw¥CDcdLine.h"
#include "str¥strprintf.h"

#include "..¥resource.h"
#include "..¥entDed¥CentDedRosen.h"
#include "..¥entDed¥CentDedDia.h"
#include "..¥DiagramEdit.h"
#include "..¥CRfEditCmdHolder.h"
//#include "..¥DedRosenFileData¥EditCmd¥EditCmd.h"
#include "CWndDcdGridCrossingCheck.h"
#include "CrossingCheckColSpec¥CrossingCheckColSpec.h"


// ****************************************************************
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
// ****************************************************************

namespace ViewCrossingCheck {
using namespace std ;


// --------------------------------
///@name	Y列番号
// --------------------------------
///@{
/**
Y列番号：ヘッダ列
*/
const int YCOLUMNNNO_HEADER = 0 ;
/**
Y列番号：運用の0番目
*/
const int YCOLUMNNNO_OPERATION_0 = 1 ;
///@}

/**
@return
	駅時刻表ビューのフォントの属性を返します。
*/
static CdFontProp createFontProp()
{
	CdDedDispProp aCdDedDispProp = getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
	return aCdDedDispProp.getOperationTableFont();
	//CdDedDispProp aCdDedDispProp = getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
	//return aCdDedDispProp.getJikokuhyouFont(0);
}
/**
@return
	駅時刻表ビューの文字の色を返します。
*/
static CdColorProp createStringColorProp()
{
	CdDedDispProp aCdDedDispProp = getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
	return aCdDedDispProp.getOperationStringColor();
	//return aCdDedDispProp.getJikokuhyouFont(0);
	//return ( CConverter_WinGdi().CdFontPropOf( DEFAULT_GUI_FONT ) ) ;
}
/**
@return
	駅時刻表ビューの罫線の色を返します。
*/
static CdColorProp createGridColorProp()
{
	CdDedDispProp aCdDedDispProp = getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
	return aCdDedDispProp.getOperationGridColor();
	//return aCdDedDispProp.getJikokuhyouFont(0);
	//return ( CConverter_WinGdi().CdFontPropOf( DEFAULT_GUI_FONT ) ) ;
}


	// --------------------------------
	//@name	下請関数
	// --------------------------------
CdCrossingCheckXColSpecCont
CWndDcdGridCrossingCheck::createXColSpecCont()
{
	CdCrossingCheckXColSpecCont aSpecCont;
	return aSpecCont ;
}

CdCrossingCheckYColSpecCont
CWndDcdGridCrossingCheck::createYColSpecCont()
{
	vector<int> iRessyaCountCont;
	for (int idx = 0; idx < (int)m_CrossingCheckContentCont.size(); idx++)
	{
		iRessyaCountCont.push_back(m_CrossingCheckContentCont[idx].size());
	}
	CdCrossingCheckYColSpecCont aSpecCont(
		iRessyaCountCont);
	return aSpecCont ;
}

CdCrossingCheckXColSpec
CWndDcdGridCrossingCheck::getXColSpecOfFocus()
{
	CdCrossingCheckXColSpec aSpec ;
	CdDcdPosXy aPos = getCFocus()->getFocusCellColumnNumber() ;
	if ( aPos != getCFocus()->ColumnNumberPosXy_NULL() )
	{
		CdCrossingCheckXColSpecCont aSpecCont;
		aSpec = aSpecCont.ColumnNumberToSpec(aPos.getX());
	}
	return aSpec ;
}

CdCrossingCheckYColSpec
CWndDcdGridCrossingCheck::getYColSpecOfFocus()
{
	CdCrossingCheckYColSpec aSpec ;
	CdDcdPosXy aPos = getCFocus()->getFocusCellColumnNumber() ;
	if ( aPos != getCFocus()->ColumnNumberPosXy_NULL() )
	{
		vector<int> iRessyaCountCont;
		for (int idx = 0; idx < (int)m_CrossingCheckContentCont.size(); idx++)
		{
			iRessyaCountCont.push_back(m_CrossingCheckContentCont[idx].size());
		}
		CdCrossingCheckYColSpecCont aSpecCont(
			iRessyaCountCont);
		aSpec = aSpecCont.ColumnNumberToSpec( aPos.getY() ) ;
	}
	return aSpec ;
}

void CWndDcdGridCrossingCheck::InsertCrossingCheckSearch(
	const int iFromTrackContentIndex, 
	const int iToTrackContentIndex, 
	const CrossingCheckSearch aCrossingCheckSearch,
	const int iType)
{
	list<CrossingCheckSearch >* pListCrossingCheckSearch;
	if (iType == 0)
	{
		pListCrossingCheckSearch = &m_CrossingCheckSearchContArrival[iFromTrackContentIndex][iToTrackContentIndex];

	}
	else if (iType == 1)
	{
		pListCrossingCheckSearch = &m_CrossingCheckSearchContDeparture[iFromTrackContentIndex][iToTrackContentIndex];

	}
	else if (iType == 2)
	{
		pListCrossingCheckSearch = &m_CrossingCheckSearchContTsuuka[iFromTrackContentIndex][iToTrackContentIndex];

	}

	bool bInsert = false;
	if (pListCrossingCheckSearch->empty())
	{
		pListCrossingCheckSearch->push_back(aCrossingCheckSearch);
		bInsert = true;
	}
	for (list<CrossingCheckSearch>::iterator itr = pListCrossingCheckSearch->begin();
		itr != pListCrossingCheckSearch->end() && !bInsert; itr++)
	{
		if (aCrossingCheckSearch.aRessyaProperty.getJikoku().compare(itr->aRessyaProperty.getJikoku(), m_KitenJikoku) <= 0)
		{
			//aCrossingCheckSearchが比較対象よりも前方・同時刻にある場合、その位置に挿入します
			pListCrossingCheckSearch->insert(itr, aCrossingCheckSearch);
			bInsert = true;
			break;
		}
		//aCrossingCheckSearchが比較対象よりも後方にある場合、次の比較に移ります
	}

	//forを抜けた場合は、List中のどれよりも後の時刻であるということなので、Listの最後尾に追加して戻る
	if (!bInsert)
	{
		pListCrossingCheckSearch->push_back(aCrossingCheckSearch);
	}

	//パターンダイヤプレビュー機能対応、上記の作業を、パターンダイヤの範囲分繰り返す
	if (m_iPatternDiagramPreviewCycleSecond > 0)
	{
		for (int iShiftSecond = m_iPatternDiagramPreviewCycleSecond; iShiftSecond <= m_iPatternDiagramPreviewRange; iShiftSecond += m_iPatternDiagramPreviewCycleSecond)
		{
			CrossingCheckSearch aCrossingCheckSearchTemp = aCrossingCheckSearch;
			aCrossingCheckSearchTemp.aRessyaProperty.setJikoku(aCrossingCheckSearchTemp.aRessyaProperty.getJikoku().addSeconds(iShiftSecond));
			aCrossingCheckSearchTemp.iShiftSecond = iShiftSecond;

			bInsert = false;
			for (list<CrossingCheckSearch>::iterator itr = pListCrossingCheckSearch->begin();
				itr != pListCrossingCheckSearch->end(); itr++)
			{
				if (aCrossingCheckSearchTemp.aRessyaProperty.getJikoku().compare(itr->aRessyaProperty.getJikoku(), m_KitenJikoku) <= 0)
				{
					//aCrossingCheckSearchが比較対象よりも前方・同時刻にある場合、その位置に挿入します
					pListCrossingCheckSearch->insert(itr, aCrossingCheckSearchTemp);
					bInsert = true;
					break;
				}
				//aCrossingCheckSearchが比較対象よりも後方にある場合、次の比較に移ります
			}

			//forを抜けた場合は、List中のどれよりも後の時刻であるということなので、Listの最後尾に追加して戻る
			if (!bInsert)
			{
				pListCrossingCheckSearch->push_back(aCrossingCheckSearchTemp);
			}


			aCrossingCheckSearchTemp = aCrossingCheckSearch;
			aCrossingCheckSearchTemp.aRessyaProperty.setJikoku(aCrossingCheckSearchTemp.aRessyaProperty.getJikoku().addSeconds(-iShiftSecond));
			aCrossingCheckSearchTemp.iShiftSecond = -iShiftSecond;

			bInsert = false;
			for (list<CrossingCheckSearch>::iterator itr = pListCrossingCheckSearch->begin();
				itr != pListCrossingCheckSearch->end(); itr++)
			{
				if (aCrossingCheckSearchTemp.aRessyaProperty.getJikoku().compare(itr->aRessyaProperty.getJikoku(), m_KitenJikoku) <= 0)
				{
					//aCrossingCheckSearchが比較対象よりも前方・同時刻にある場合、その位置に挿入します
					pListCrossingCheckSearch->insert(itr, aCrossingCheckSearchTemp);
					bInsert = true;
					break;
				}
				//aCrossingCheckSearchが比較対象よりも後方にある場合、次の比較に移ります
			}

			//forを抜けた場合は、List中のどれよりも後の時刻であるということなので、Listの最後尾に追加して戻る
			if (!bInsert)
			{
				pListCrossingCheckSearch->push_back(aCrossingCheckSearchTemp);
			}

		}
	}

}

void CWndDcdGridCrossingCheck::SearchBeforeOperationCont(
	const CentDedBeforeOperationCont* pBeforeCont, 
	const CdDedRessyaProperty aRessyaProperty, 
	const CentDedRessya* pCentDedRessya, 
	const int iRessyaTrackIndex, 
	const int iEkiIndex,
	const CdDedJikoku aCdDedJikoku)
{
	/**
		aCdDedJikokuについて、
		pBeforeContの先頭が、開始作業の場合(=増結編成前作業)は、増結時刻を意味します。
		それ以外の場合は、当駅着時刻を意味します。
	*/
	//iNextRessyaTrackIndex　各作業後の番線です。入換作業について、iNextRessyaTrackIndexと入換元番線が等しい場合は、入換作業自体が無効となります。
	//また、駅構外・路線外から当駅に到着したときの番線は、これになります。
	int iNextRessyaTrackIndex = iRessyaTrackIndex;
	//OperationJikokuTemp 開始作業が路線外始発かつ、当駅着時刻が空の場合は、この時刻を着時刻とみなします。入換時刻や増結時刻等で上書きしていきます。
	CdDedJikoku OperationJikokuTemp = aCdDedJikoku;
	for (int idxb = pBeforeCont->size() - 1; idxb >= 0; idxb--)
	{
		const CentDedBeforeOperation* pBeforeOperation = pBeforeCont->getMuPtr()->get(idxb);
		if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
		{
			SearchBeforeOperationCont(
				pBeforeOperation->getCentDedBeforeOperationCont(),
				aRessyaProperty,
				pCentDedRessya,
				iNextRessyaTrackIndex,
				iEkiIndex,
				pBeforeOperation->getConnectJikoku());
			OperationJikokuTemp = pBeforeOperation->getConnectJikoku();
		}
		else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
		{
			SearchAfterOperationCont(
				pBeforeOperation->getCentDedAfterOperationCont(),
				aRessyaProperty,
				pCentDedRessya,
				iNextRessyaTrackIndex,
				iEkiIndex,
				pBeforeOperation->getReleaseJikoku());
			OperationJikokuTemp = pBeforeOperation->getReleaseJikoku();
		}
		else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
		{
			if (iNextRessyaTrackIndex != pBeforeOperation->getShuntTrackIndex())
			{
				CrossingCheckSearch aCrossingCheckSearch;
				TrackContent FromTrackContent(ETrackType::TrackType_Track, pBeforeOperation->getShuntTrackIndex());
				TrackContent ToTrackContent(ETrackType::TrackType_Track, iNextRessyaTrackIndex);
				aCrossingCheckSearch.aRessyaProperty = aRessyaProperty;
				aCrossingCheckSearch.iEkiIndex = iEkiIndex;
				aCrossingCheckSearch.FromTrackContent = FromTrackContent;
				aCrossingCheckSearch.ToTrackContent = ToTrackContent;

				int iFromTrackContentIndex = m_MapTrackContentToList[(int)FromTrackContent.eTrackType][FromTrackContent.iTrackIndex];
				int iToTrackContentIndex = m_MapTrackContentToList[(int)ToTrackContent.eTrackType][ToTrackContent.iTrackIndex];


				aCrossingCheckSearch.aRessyaProperty.setJikoku(pBeforeOperation->getOperationChakuJikoku(true));
				InsertCrossingCheckSearch(
					iFromTrackContentIndex,
					iToTrackContentIndex,
					aCrossingCheckSearch,
					0);

				aCrossingCheckSearch.aRessyaProperty.setJikoku(pBeforeOperation->getOperationHatsuJikoku());
				InsertCrossingCheckSearch(
					iFromTrackContentIndex,
					iToTrackContentIndex,
					aCrossingCheckSearch,
					1);

				iNextRessyaTrackIndex = pBeforeOperation->getShuntTrackIndex();
				OperationJikokuTemp = pBeforeOperation->getOperationHatsuJikoku();
			}
		}
	}

	if (pBeforeCont->size() == 0 ||
		!pBeforeCont->getMuPtr()->get(0)->isFirstOperation())
	{
		/**
			pBeforeContが空、もしくは先頭要素が開始作業ではない場合は、このpBeforeContは途中駅・終着駅の前作業なので、
			駅構外からiNextRessyaTrackIndexへの到着動作をInsertCrossingCheckSearchします。
		*/

		CrossingCheckSearch aCrossingCheckSearch;
		TrackContent FromTrackContent;
		if (pCentDedRessya->getRessyahoukou() == ERessyahoukou::Ressyahoukou_Kudari)
		{
			FromTrackContent.eTrackType = ETrackType::TrackType_Origin;
		}
		else
		{
			FromTrackContent.eTrackType = ETrackType::TrackType_Terminal;
		}
		FromTrackContent.iTrackIndex = iEkiIndex;

		TrackContent ToTrackContent(ETrackType::TrackType_Track, iNextRessyaTrackIndex);
		aCrossingCheckSearch.aRessyaProperty = aRessyaProperty;
		aCrossingCheckSearch.iEkiIndex = iEkiIndex;
		aCrossingCheckSearch.FromTrackContent = FromTrackContent;
		aCrossingCheckSearch.ToTrackContent = ToTrackContent;

		int iFromTrackContentIndex = m_MapTrackContentToList[(int)FromTrackContent.eTrackType][FromTrackContent.iTrackIndex];
		int iToTrackContentIndex = m_MapTrackContentToList[(int)ToTrackContent.eTrackType][ToTrackContent.iTrackIndex];

		aCrossingCheckSearch.aRessyaProperty.setJikoku(aCdDedJikoku);
		InsertCrossingCheckSearch(
			iFromTrackContentIndex,
			iToTrackContentIndex,
			aCrossingCheckSearch,
			0);
	}
	else if (pBeforeCont->getMuPtr()->get(0)->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
	{
		/**
			先頭要素が路線外始発の場合は、路線外からiNextRessyaTrackIndexへの到着動作をInsertCrossingCheckSearchします。
		*/
		const CentDedBeforeOperation* pBeforeOperation = pBeforeCont->getMuPtr()->get(0);

		CrossingCheckSearch aCrossingCheckSearch;
		TrackContent FromTrackContent(ETrackType::TrackType_Outer, pBeforeOperation->getOuterShihatsuekiIndex());
		TrackContent ToTrackContent(ETrackType::TrackType_Track, iNextRessyaTrackIndex);
		aCrossingCheckSearch.aRessyaProperty = aRessyaProperty;
		aCrossingCheckSearch.iEkiIndex = iEkiIndex;
		aCrossingCheckSearch.FromTrackContent = FromTrackContent;
		aCrossingCheckSearch.ToTrackContent = ToTrackContent;

		int iFromTrackContentIndex = m_MapTrackContentToList[(int)FromTrackContent.eTrackType][FromTrackContent.iTrackIndex];
		int iToTrackContentIndex = m_MapTrackContentToList[(int)ToTrackContent.eTrackType][ToTrackContent.iTrackIndex];

		aCrossingCheckSearch.aRessyaProperty.setJikoku(pBeforeOperation->getChakuJikoku());
		if (pBeforeOperation->getChakuJikoku().isNull())
		{
			aCrossingCheckSearch.aRessyaProperty.setJikoku(OperationJikokuTemp);
		}

		InsertCrossingCheckSearch(
			iFromTrackContentIndex,
			iToTrackContentIndex,
			aCrossingCheckSearch,
			0);

	}
}

void CWndDcdGridCrossingCheck::SearchAfterOperationCont(
	const CentDedAfterOperationCont* pAfterCont,
	const CdDedRessyaProperty aRessyaProperty,
	const CentDedRessya* pCentDedRessya,
	const int iRessyaTrackIndex,
	const int iEkiIndex,
	const CdDedJikoku aCdDedJikoku)
{
	/**
		aCdDedJikokuについて、
		pAfterContの末尾が、終了作業の場合(=解結編成後作業)は、解結時刻を意味します。
		それ以外の場合は、当駅発時刻を意味します。
	*/
	//iPrevRessyaTrackIndex　各作業前の番線です。入換作業について、iPrevRessyaTrackIndexと入換先番線が等しい場合は、入換作業自体が無効となります。
	//また、当駅から駅構外・路線外へ出発するときの番線は、これになります。
	int iPrevRessyaTrackIndex = iRessyaTrackIndex;
	//OperationJikokuTemp 終了作業が路線外終着かつ、当駅発時刻が空の場合は、この時刻を発時刻とみなします。入換時刻や増結時刻等で上書きしていきます。
	CdDedJikoku OperationJikokuTemp = aCdDedJikoku;
	for (int idxa = 0; idxa < pAfterCont->size(); idxa++)
	{
		const CentDedAfterOperation* pAfterOperation = pAfterCont->getMuPtr()->get(idxa);
		if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
		{
			SearchBeforeOperationCont(
				pAfterOperation->getCentDedBeforeOperationCont(),
				aRessyaProperty,
				pCentDedRessya,
				iPrevRessyaTrackIndex,
				iEkiIndex,
				pAfterOperation->getConnectJikoku());
			OperationJikokuTemp = pAfterOperation->getConnectJikoku();
		}
		else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
		{
			SearchAfterOperationCont(
				pAfterOperation->getCentDedAfterOperationCont(),
				aRessyaProperty,
				pCentDedRessya,
				iPrevRessyaTrackIndex,
				iEkiIndex,
				pAfterOperation->getReleaseJikoku());
			OperationJikokuTemp = pAfterOperation->getReleaseJikoku();
		}
		else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
		{
			if (iPrevRessyaTrackIndex != pAfterOperation->getShuntTrackIndex())
			{
				CrossingCheckSearch aCrossingCheckSearch;
				TrackContent FromTrackContent(ETrackType::TrackType_Track, iPrevRessyaTrackIndex);
				TrackContent ToTrackContent(ETrackType::TrackType_Track, pAfterOperation->getShuntTrackIndex());
				aCrossingCheckSearch.aRessyaProperty = aRessyaProperty;
				aCrossingCheckSearch.iEkiIndex = iEkiIndex;
				aCrossingCheckSearch.FromTrackContent = FromTrackContent;
				aCrossingCheckSearch.ToTrackContent = ToTrackContent;

				int iFromTrackContentIndex = m_MapTrackContentToList[(int)FromTrackContent.eTrackType][FromTrackContent.iTrackIndex];
				int iToTrackContentIndex = m_MapTrackContentToList[(int)ToTrackContent.eTrackType][ToTrackContent.iTrackIndex];


				aCrossingCheckSearch.aRessyaProperty.setJikoku(pAfterOperation->getOperationChakuJikoku(true));
				InsertCrossingCheckSearch(
					iFromTrackContentIndex,
					iToTrackContentIndex,
					aCrossingCheckSearch,
					0);

				aCrossingCheckSearch.aRessyaProperty.setJikoku(pAfterOperation->getOperationHatsuJikoku());
				InsertCrossingCheckSearch(
					iFromTrackContentIndex,
					iToTrackContentIndex,
					aCrossingCheckSearch,
					1);

				iPrevRessyaTrackIndex = pAfterOperation->getShuntTrackIndex();
				OperationJikokuTemp = pAfterOperation->getOperationChakuJikoku(true);
			}
		}
	}

	if (pAfterCont->size() == 0 ||
		!pAfterCont->getMuPtr()->get(INT_MAX)->isLastOperation())
	{
		/**
			pAfterContが空、もしくは末尾要素が終了作業ではない場合は、このpAfterContは始発駅・途中駅の後作業なので、
			最後に、iPrevRessyaTrackIndexから駅構外への出発動作をInsertCrossingCheckSearchします。
		*/

		CrossingCheckSearch aCrossingCheckSearch;

		TrackContent FromTrackContent(ETrackType::TrackType_Track, iPrevRessyaTrackIndex);

		TrackContent ToTrackContent;
		if (pCentDedRessya->getRessyahoukou() == ERessyahoukou::Ressyahoukou_Kudari)
		{
			ToTrackContent.eTrackType = ETrackType::TrackType_Terminal;
		}
		else
		{
			ToTrackContent.eTrackType = ETrackType::TrackType_Origin;
		}
		ToTrackContent.iTrackIndex = iEkiIndex;
		aCrossingCheckSearch.aRessyaProperty = aRessyaProperty;
		aCrossingCheckSearch.iEkiIndex = iEkiIndex;
		aCrossingCheckSearch.FromTrackContent = FromTrackContent;
		aCrossingCheckSearch.ToTrackContent = ToTrackContent;

		int iFromTrackContentIndex = m_MapTrackContentToList[(int)FromTrackContent.eTrackType][FromTrackContent.iTrackIndex];
		int iToTrackContentIndex = m_MapTrackContentToList[(int)ToTrackContent.eTrackType][ToTrackContent.iTrackIndex];

		aCrossingCheckSearch.aRessyaProperty.setJikoku(aCdDedJikoku);
		InsertCrossingCheckSearch(
			iFromTrackContentIndex,
			iToTrackContentIndex,
			aCrossingCheckSearch,
			1);
	}
	else if (pAfterCont->getMuPtr()->get(INT_MAX)->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
	{
		/**
			末尾要素が路線外終着の場合は、iPrevRessyaTrackIndexから路線外への出発動作をInsertCrossingCheckSearchします。
		*/
		const CentDedAfterOperation* pAfterOperation = pAfterCont->getMuPtr()->get(INT_MAX);

		CrossingCheckSearch aCrossingCheckSearch;
		TrackContent FromTrackContent(ETrackType::TrackType_Track, iPrevRessyaTrackIndex);
		TrackContent ToTrackContent(ETrackType::TrackType_Outer, pAfterOperation->getOuterShuchakuekiIndex());
		aCrossingCheckSearch.aRessyaProperty = aRessyaProperty;
		aCrossingCheckSearch.iEkiIndex = iEkiIndex;
		aCrossingCheckSearch.FromTrackContent = FromTrackContent;
		aCrossingCheckSearch.ToTrackContent = ToTrackContent;

		int iFromTrackContentIndex = m_MapTrackContentToList[(int)FromTrackContent.eTrackType][FromTrackContent.iTrackIndex];
		int iToTrackContentIndex = m_MapTrackContentToList[(int)ToTrackContent.eTrackType][ToTrackContent.iTrackIndex];

		aCrossingCheckSearch.aRessyaProperty.setJikoku(pAfterOperation->getHatsuJikoku());
		if (pAfterOperation->getHatsuJikoku().isNull())
		{
			aCrossingCheckSearch.aRessyaProperty.setJikoku(OperationJikokuTemp);
		}

		InsertCrossingCheckSearch(
			iFromTrackContentIndex,
			iToTrackContentIndex,
			aCrossingCheckSearch,
			1);

	}
}

void CWndDcdGridCrossingCheck::MergeCrossingCheckSearchCont(
	list<CrossingCheckSearch>* CrossingCheckSearchContA, 
	list<CrossingCheckSearch>* CrossingCheckSearchContB)
{
	if (CrossingCheckSearchContA->empty())
	{
		CrossingCheckSearchContA->insert(CrossingCheckSearchContA->begin(), CrossingCheckSearchContB->begin(), CrossingCheckSearchContB->end());
	}
	else
	{
		auto itrB = CrossingCheckSearchContB->begin();
		for (auto itrA = CrossingCheckSearchContA->begin(); itrA != CrossingCheckSearchContA->end(); itrA++)
		{
			for (; itrB != CrossingCheckSearchContB->end(); itrB++)
			{
				if (itrB->aRessyaProperty.getJikoku().compare(itrA->aRessyaProperty.getJikoku(), m_KitenJikoku) <= 0)
				{
					CrossingCheckSearchContA->insert(itrA, *itrB);
				}
				else
				{
					auto itrANext = itrA;
					itrANext++;
					if(itrANext == CrossingCheckSearchContA->end())
					{
						CrossingCheckSearchContA->insert(CrossingCheckSearchContA->end(), itrB, CrossingCheckSearchContB->end());
						return;
					}
					break;
				}
			}
			//int a = 0;
		}
	}
}
	
	// --------------------------------
	//@name OnUpdate の下請関数
	// --------------------------------

const CdDedJikoku::CConv
CWndDcdGridCrossingCheck::getCdDedJikokuConv()const
{
	//if (m_bDisplaySecondEkiJikoku)
	//{
	//	if (m_bDisplayColonEkiJikoku)
	//	{
	//		static CdDedJikoku::CConv aConv(
	//			false,		//	コロン有
	//						// 時が 00 から 09 の場合、10の位の "0" をスペースにします。
	//			CdDedJikoku::CConv::EHour_ZeroToSpace,
	//			CdDedJikoku::CConv::ESecond_Output 	// 秒を表示します
	//		);
	//		return aConv;
	//	}
	//	else
	//	{
			static CdDedJikoku::CConv aConv(
				false,		//	コロン無
							// 時が 00 から 09 の場合、10の位の "0" をスペースにします。
				CdDedJikoku::CConv::EHour_ZeroToSpace,
				CdDedJikoku::CConv::ESecond_Output 	// 秒を表示します
			);
			return aConv;
	//	}
	//}
	//else
	//{
	//	if (m_bDisplayColonEkiJikoku)
	//	{
	//		static CdDedJikoku::CConv aConv(
	//			false,		//	コロン有
	//						// 時が 00 から 09 の場合、10の位の "0" をスペースにします。
	//			CdDedJikoku::CConv::EHour_ZeroToSpace,
	//			CdDedJikoku::CConv::ESecond_NoSecond 	// 秒を常に出力しません。
	//		);
	//		return aConv;
	//	}
	//	else
	//	{
	//		static CdDedJikoku::CConv aConv(
	//			true,		//	コロン無
	//						// 時が 00 から 09 の場合、10の位の "0" をスペースにします。
	//			CdDedJikoku::CConv::EHour_ZeroToSpace,
	//			CdDedJikoku::CConv::ESecond_NoSecond 	// 秒を常に出力しません。
	//		);
	//		return aConv;
	//	}
	//}

	//CdDedJikoku::CConv::ESecond eSecond = CdDedJikoku::CConv::ESecond_NoSecond;
	//if (m_bDisplaySecondEkiJikoku)
	//{
	//	eSecond = CdDedJikoku::CConv::ESecond_Output;
	//}

	//CdDedJikoku::CConv aConv(
	//	!m_bDisplayColonEkiJikoku,
	//	CdDedJikoku::CConv::EHour_ZeroToSpace,
	//	eSecond,
	//	(CdDedJikoku::CConv::ESecondRound)m_iSecondRoundChaku,
	//	(CdDedJikoku::CConv::ESecondRound)m_iSecondRoundHatsu,
	//	m_bDisplay2400
	//);
	//return aConv;
}

void CWndDcdGridCrossingCheck::OnUpdate_setCrossingCheckContent_To_Column(
	int iRuleIndex ,
	int iRessyaIndex,
	const CrossingCheckContent& aCrossingCheckContent)
{
	const Mu<const CentDedRessya*>* pCentDedRessyaConts[2];
	for (int iRessyahoukou = Ressyahoukou_Kudari;
		iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
	{
		pCentDedRessyaConts[iRessyahoukou] = getCentDedRessyaCont((ERessyahoukou)iRessyahoukou)->getMuPtr();
	}


	CdFontProp fontpropDefault = createFontProp() ;
	CdColorProp colorpropDefault = createStringColorProp();
	CdCrossingCheckYColSpecCont aYColSpecCont = createYColSpecCont();

	int iYColumnNumber = createYColSpecCont().ColumnNumberFromSpec(
		CdCrossingCheckYColSpec(CdCrossingCheckYColSpec::EColumnType::ColumnType_Ressya, iRuleIndex, iRessyaIndex));

	// --------------------------------
	//	行のY方向サイズを設定
	// --------------------------------
	{
		CDcdTargetGetDC	aCDcdTarget( NULL ) ;

		CdDcdSizeXy	sizeRessya ;
		CDcdTextbox	aCDcdTextbox(_T("京都京") ,
			fontpropDefault , 
			_T("") , 1 , 2 , 2 ) ;
		aCDcdTextbox.getItemSize( &aCDcdTarget , &sizeRessya) ;

		getCXDcdGrid()->getYColumn(iYColumnNumber)->setColumnSize(sizeRessya.getY());

		Ou<CDcdLine>
			(getCXDcdGrid()->getYBorder(iYColumnNumber)->getIfDcDraw())
			->setCdPenProp(getCdPenPropNarrowLine());
	}


	// --------------------------------
	//	属性を設定
	// --------------------------------
	//const Mu<CentDedEkiCont::CdDedEki>* pCdDedEkiConts[2];
	//for (int iRessyahoukou = Ressyahoukou_Kudari;
	//	iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
	//{
	//	pCdDedEkiConts[iRessyahoukou] =
	//		getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont()->getMuPtr((ERessyahoukou)iRessyahoukou);
	//}

	const CentDedRessyasyubetsuCont* pCentDedRessyasyubetsuCont =
		getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedRessyasyubetsuCont();

	//const CentDedEkiCont* pCentDedEkiCont = getCDiagramEditDoc()->
	//	getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont();
	//int iEkiIndex = pCentDedEkiCont->EkiIndexOfEkiID(GetDocument()->getEkiID());
	//int iEkiOrder = pCentDedEkiCont->EkiOrderOfEkiIndex(GetDocument()->getRessyahoukou(),iEkiIndex);
	//const CentDedEkiCont::CdDedEki aCdDedEki = 
	//	pCdDedEkiConts[(int)GetDocument()->getRessyahoukou()]->get(iEkiOrder);
	//const CentDedEkiTrack2Cont aCentDedEkiTrack2Cont = aCdDedEki.getCentDedEkiTrack2Cont();

	tstring strRessyahoukouKudari;
	tstring strRessyahoukouNobori;
	CString strTemp;
	strTemp.LoadString(IDS_WORD_Kudari);
	strRessyahoukouKudari = (LPCTSTR)strTemp;
	strTemp.LoadString(IDS_WORD_Nobori);
	strRessyahoukouNobori = (LPCTSTR)strTemp;
	if (!getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getKudariDiaAlias().empty())
	{
		strRessyahoukouKudari = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getKudariDiaAlias();
	}
	if (!getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getNoboriDiaAlias().empty())
	{
		strRessyahoukouNobori = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getNoboriDiaAlias();
	}

	//const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont(
	//	GetDocument()->getRessyahoukou());
	//tstring strRessya = _T("京都京");

	CdCrossingCheckXColSpecCont aXColSpecCont = createXColSpecCont();

	{
		//	前動作側方向・列車番号・種別
		int iXColumnNumber1 = aXColSpecCont.ColumnNumberFromSpec(CdCrossingCheckXColSpec(
			CdCrossingCheckXColSpec::EColumnType::ColumnType_BeforeRessyahoukou));
		int iXColumnNumber2 = aXColSpecCont.ColumnNumberFromSpec(CdCrossingCheckXColSpec(
			CdCrossingCheckXColSpec::EColumnType::ColumnType_BeforeRessyabangou));
		int iXColumnNumber3 = aXColSpecCont.ColumnNumberFromSpec(CdCrossingCheckXColSpec(
			CdCrossingCheckXColSpec::EColumnType::ColumnType_BeforeRessyasyubetsu));
		Ou<CDcdTextbox> pCDcdTextbox1 =
			getCXDcdGrid()->getCell(iXColumnNumber1, iYColumnNumber)->getIfDcDraw();
		Ou<CDcdTextbox> pCDcdTextbox2 =
			getCXDcdGrid()->getCell(iXColumnNumber2, iYColumnNumber)->getIfDcDraw();
		Ou<CDcdTextbox> pCDcdTextbox3 =
			getCXDcdGrid()->getCell(iXColumnNumber3, iYColumnNumber)->getIfDcDraw();

		tstring strRessyahoukou;
		tstring strRessyabangou;
		tstring strRessyaSyubetsu;

		if (aCrossingCheckContent.BeforeRessyaProperty.getRessyahoukou()
			== ERessyahoukou::Ressyahoukou_Kudari)
		{
			strRessyahoukou = strRessyahoukouKudari;
		}
		else
		{
			strRessyahoukou = strRessyahoukouNobori;
		}
		const CentDedRessya* pCentDedRessya = pCentDedRessyaConts[(int)aCrossingCheckContent.BeforeRessyaProperty.getRessyahoukou()]
			->get(aCrossingCheckContent.BeforeRessyaProperty.getRessyaIndex());
		strRessyabangou = pCentDedRessya->getRessyabangou();
		const CentDedRessyasyubetsu* pCentDedRessyasyubetsu =
			pCentDedRessyasyubetsuCont->getMuPtr()->get(pCentDedRessya->getRessyasyubetsuIndex());
		strRessyaSyubetsu = pCentDedRessyasyubetsu->getSyubetsumei();

		//	フォント属性
		CdDrawTextProp	aCdDrawTextProp =
			pCDcdTextbox1->getCdDrawTextProp();
		aCdDrawTextProp.setCdFontProp(fontpropDefault);
		aCdDrawTextProp.setTextColor(colorpropDefault);
		aCdDrawTextProp.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
		pCDcdTextbox1->setCdDrawTextProp(aCdDrawTextProp);

		CdDrawTextProp	aCdDrawTextProp2 =
			pCDcdTextbox2->getCdDrawTextProp();
		aCdDrawTextProp2.setCdFontProp(fontpropDefault);
		aCdDrawTextProp2.setTextColor(colorpropDefault);
		aCdDrawTextProp2.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
		pCDcdTextbox2->setCdDrawTextProp(aCdDrawTextProp2);

		//種別のフォント属性
		CdDrawTextProp	aCdDrawTextProp3 =
			pCDcdTextbox3->getCdDrawTextProp();
		aCdDrawTextProp3.setCdFontProp(fontpropDefault);
		{
			aCdDrawTextProp3.setTextColor(pCentDedRessyasyubetsu->getJikokuhyouMojiColor());

			int idxFont = pCentDedRessyasyubetsu->getJikokuhyouFontIndex();
			aCdDrawTextProp3.setCdFontProp(
				getCDiagramEditDoc()->getCDedRosenFileData()
				->getCdDedDispProp().getJikokuhyouFont(idxFont));
		}
		aCdDrawTextProp3.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
		pCDcdTextbox3->setCdDrawTextProp(aCdDrawTextProp3);

		pCDcdTextbox1->setText(strRessyahoukou);
		pCDcdTextbox2->setText(strRessyabangou);
		pCDcdTextbox3->setText(strRessyaSyubetsu);

		//	セルを無効化
		InvalidateCell(iXColumnNumber1, iYColumnNumber);
		InvalidateCell(iXColumnNumber2, iYColumnNumber);
		InvalidateCell(iXColumnNumber3, iYColumnNumber);
	}
	{
		//		時刻(前動作側)
		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdCrossingCheckXColSpec(
			CdCrossingCheckXColSpec::EColumnType::ColumnType_BeforeJikoku));
		Ou<CDcdTextbox> pCDcdTextbox =
			getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();

		pCDcdTextbox->
			setText(getCdDedJikokuConv().encode(aCrossingCheckContent.BeforeRessyaProperty.getJikoku()));

		//	フォント属性
		CdDrawTextProp	aCdDrawTextProp =
			pCDcdTextbox->getCdDrawTextProp();
		aCdDrawTextProp.setCdFontProp(fontpropDefault);
		aCdDrawTextProp.setTextColor(colorpropDefault);
		aCdDrawTextProp.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
		pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);


		//	セルを無効化
		InvalidateCell(iXColumnNumber, iYColumnNumber);
	}
	{
		//	移動元番線・⇒・移動先番線
		int iXColumnNumber1 = aXColSpecCont.ColumnNumberFromSpec(CdCrossingCheckXColSpec(
			CdCrossingCheckXColSpec::EColumnType::ColumnType_BeforeFrom));
		int iXColumnNumber2 = aXColSpecCont.ColumnNumberFromSpec(CdCrossingCheckXColSpec(
			CdCrossingCheckXColSpec::EColumnType::ColumnType_BeforeArrow));
		int iXColumnNumber3 = aXColSpecCont.ColumnNumberFromSpec(CdCrossingCheckXColSpec(
			CdCrossingCheckXColSpec::EColumnType::ColumnType_BeforeTo));
		Ou<CDcdTextbox> pCDcdTextbox1 =
			getCXDcdGrid()->getCell(iXColumnNumber1, iYColumnNumber)->getIfDcDraw();
		Ou<CDcdTextbox> pCDcdTextbox2 =
			getCXDcdGrid()->getCell(iXColumnNumber2, iYColumnNumber)->getIfDcDraw();
		Ou<CDcdTextbox> pCDcdTextbox3 =
			getCXDcdGrid()->getCell(iXColumnNumber3, iYColumnNumber)->getIfDcDraw();

		pCDcdTextbox1->
			setText(m_strTrackNameCont[m_MapTrackContentToList[(int)aCrossingCheckContent.BeforeFromTrackContent.eTrackType]
				[aCrossingCheckContent.BeforeFromTrackContent.iTrackIndex]]);
		pCDcdTextbox2->
			setText(_T("→"));
		pCDcdTextbox3->
			setText(m_strTrackNameCont[m_MapTrackContentToList[(int)aCrossingCheckContent.BeforeToTrackContent.eTrackType]
				[aCrossingCheckContent.BeforeToTrackContent.iTrackIndex]]);

		//	フォント属性
		CdDrawTextProp	aCdDrawTextProp1 =
			pCDcdTextbox1->getCdDrawTextProp();
		aCdDrawTextProp1.setCdFontProp(fontpropDefault);
		aCdDrawTextProp1.setTextColor(colorpropDefault);
		aCdDrawTextProp1.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
		pCDcdTextbox1->setCdDrawTextProp(aCdDrawTextProp1);

		CdDrawTextProp	aCdDrawTextProp2 =
			pCDcdTextbox2->getCdDrawTextProp();
		aCdDrawTextProp2.setCdFontProp(fontpropDefault);
		aCdDrawTextProp2.setTextColor(colorpropDefault);
		aCdDrawTextProp2.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
		pCDcdTextbox2->setCdDrawTextProp(aCdDrawTextProp2);

		CdDrawTextProp	aCdDrawTextProp3 =
			pCDcdTextbox3->getCdDrawTextProp();
		aCdDrawTextProp3.setCdFontProp(fontpropDefault);
		aCdDrawTextProp3.setTextColor(colorpropDefault);
		aCdDrawTextProp3.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
		pCDcdTextbox3->setCdDrawTextProp(aCdDrawTextProp3);


		//	セルを無効化
		InvalidateCell(iXColumnNumber1, iYColumnNumber);
		InvalidateCell(iXColumnNumber2, iYColumnNumber);
		InvalidateCell(iXColumnNumber3, iYColumnNumber);
	}
	{
		//	時隔
		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdCrossingCheckXColSpec(
			CdCrossingCheckXColSpec::EColumnType::ColumnType_Headway));
		Ou<CDcdTextbox> pCDcdTextbox =
			getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();

		pCDcdTextbox->
			setText(to_tstring(aCrossingCheckContent.iHeadway));

		//	フォント属性
		CdDrawTextProp	aCdDrawTextProp =
			pCDcdTextbox->getCdDrawTextProp();
		aCdDrawTextProp.setCdFontProp(fontpropDefault);
		aCdDrawTextProp.setTextColor(colorpropDefault);
		aCdDrawTextProp.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
		pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);


		//	セルを無効化
		InvalidateCell(iXColumnNumber, iYColumnNumber);
	}
	{
		//	後動作側方向・列車番号・種別
		int iXColumnNumber1 = aXColSpecCont.ColumnNumberFromSpec(CdCrossingCheckXColSpec(
			CdCrossingCheckXColSpec::EColumnType::ColumnType_AfterRessyahoukou));
		int iXColumnNumber2 = aXColSpecCont.ColumnNumberFromSpec(CdCrossingCheckXColSpec(
			CdCrossingCheckXColSpec::EColumnType::ColumnType_AfterRessyabangou));
		int iXColumnNumber3 = aXColSpecCont.ColumnNumberFromSpec(CdCrossingCheckXColSpec(
			CdCrossingCheckXColSpec::EColumnType::ColumnType_AfterRessyasyubetsu));
		Ou<CDcdTextbox> pCDcdTextbox1 =
			getCXDcdGrid()->getCell(iXColumnNumber1, iYColumnNumber)->getIfDcDraw();
		Ou<CDcdTextbox> pCDcdTextbox2 =
			getCXDcdGrid()->getCell(iXColumnNumber2, iYColumnNumber)->getIfDcDraw();
		Ou<CDcdTextbox> pCDcdTextbox3 =
			getCXDcdGrid()->getCell(iXColumnNumber3, iYColumnNumber)->getIfDcDraw();

		tstring strRessyahoukou;
		tstring strRessyabangou;
		tstring strRessyaSyubetsu;

		if (aCrossingCheckContent.AfterRessyaProperty.getRessyahoukou()
			== ERessyahoukou::Ressyahoukou_Kudari)
		{
			strRessyahoukou = strRessyahoukouKudari;
		}
		else
		{
			strRessyahoukou = strRessyahoukouNobori;
		}
		const CentDedRessya* pCentDedRessya = pCentDedRessyaConts[(int)aCrossingCheckContent.AfterRessyaProperty.getRessyahoukou()]
			->get(aCrossingCheckContent.AfterRessyaProperty.getRessyaIndex());
		strRessyabangou = pCentDedRessya->getRessyabangou();
		const CentDedRessyasyubetsu* pCentDedRessyasyubetsu =
			pCentDedRessyasyubetsuCont->getMuPtr()->get(pCentDedRessya->getRessyasyubetsuIndex());
		strRessyaSyubetsu = pCentDedRessyasyubetsu->getSyubetsumei();

		//	フォント属性
		CdDrawTextProp	aCdDrawTextProp =
			pCDcdTextbox1->getCdDrawTextProp();
		aCdDrawTextProp.setCdFontProp(fontpropDefault);
		aCdDrawTextProp.setTextColor(colorpropDefault);
		aCdDrawTextProp.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
		pCDcdTextbox1->setCdDrawTextProp(aCdDrawTextProp);

		CdDrawTextProp	aCdDrawTextProp2 =
			pCDcdTextbox2->getCdDrawTextProp();
		aCdDrawTextProp2.setCdFontProp(fontpropDefault);
		aCdDrawTextProp2.setTextColor(colorpropDefault);
		aCdDrawTextProp2.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
		pCDcdTextbox2->setCdDrawTextProp(aCdDrawTextProp2);

		//種別のフォント属性
		CdDrawTextProp	aCdDrawTextProp3 =
			pCDcdTextbox3->getCdDrawTextProp();
		aCdDrawTextProp3.setCdFontProp(fontpropDefault);
		{
			aCdDrawTextProp3.setTextColor(pCentDedRessyasyubetsu->getJikokuhyouMojiColor());

			int idxFont = pCentDedRessyasyubetsu->getJikokuhyouFontIndex();
			aCdDrawTextProp3.setCdFontProp(
				getCDiagramEditDoc()->getCDedRosenFileData()
				->getCdDedDispProp().getJikokuhyouFont(idxFont));
		}
		aCdDrawTextProp3.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
		pCDcdTextbox3->setCdDrawTextProp(aCdDrawTextProp3);

		pCDcdTextbox1->setText(strRessyahoukou);
		pCDcdTextbox2->setText(strRessyabangou);
		pCDcdTextbox3->setText(strRessyaSyubetsu);

		//	セルを無効化
		InvalidateCell(iXColumnNumber1, iYColumnNumber);
		InvalidateCell(iXColumnNumber2, iYColumnNumber);
		InvalidateCell(iXColumnNumber3, iYColumnNumber);
	}
	{
		//		時刻(前動作側)
		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdCrossingCheckXColSpec(
			CdCrossingCheckXColSpec::EColumnType::ColumnType_AfterJikoku));
		Ou<CDcdTextbox> pCDcdTextbox =
			getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();

		pCDcdTextbox->
			setText(getCdDedJikokuConv().encode(aCrossingCheckContent.AfterRessyaProperty.getJikoku()));

		//	フォント属性
		CdDrawTextProp	aCdDrawTextProp =
			pCDcdTextbox->getCdDrawTextProp();
		aCdDrawTextProp.setCdFontProp(fontpropDefault);
		aCdDrawTextProp.setTextColor(colorpropDefault);
		aCdDrawTextProp.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
		pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);


		//	セルを無効化
		InvalidateCell(iXColumnNumber, iYColumnNumber);
	}
	{
		//	移動元番線・⇒・移動先番線
		int iXColumnNumber1 = aXColSpecCont.ColumnNumberFromSpec(CdCrossingCheckXColSpec(
			CdCrossingCheckXColSpec::EColumnType::ColumnType_AfterFrom));
		int iXColumnNumber2 = aXColSpecCont.ColumnNumberFromSpec(CdCrossingCheckXColSpec(
			CdCrossingCheckXColSpec::EColumnType::ColumnType_AfterArrow));
		int iXColumnNumber3 = aXColSpecCont.ColumnNumberFromSpec(CdCrossingCheckXColSpec(
			CdCrossingCheckXColSpec::EColumnType::ColumnType_AfterTo));
		Ou<CDcdTextbox> pCDcdTextbox1 =
			getCXDcdGrid()->getCell(iXColumnNumber1, iYColumnNumber)->getIfDcDraw();
		Ou<CDcdTextbox> pCDcdTextbox2 =
			getCXDcdGrid()->getCell(iXColumnNumber2, iYColumnNumber)->getIfDcDraw();
		Ou<CDcdTextbox> pCDcdTextbox3 =
			getCXDcdGrid()->getCell(iXColumnNumber3, iYColumnNumber)->getIfDcDraw();

		pCDcdTextbox1->
			setText(m_strTrackNameCont[m_MapTrackContentToList[(int)aCrossingCheckContent.AfterFromTrackContent.eTrackType]
				[aCrossingCheckContent.AfterFromTrackContent.iTrackIndex]]);
		pCDcdTextbox2->
			setText(_T("→"));
		pCDcdTextbox3->
			setText(m_strTrackNameCont[m_MapTrackContentToList[(int)aCrossingCheckContent.AfterToTrackContent.eTrackType]
				[aCrossingCheckContent.AfterToTrackContent.iTrackIndex]]);

		//	フォント属性
		CdDrawTextProp	aCdDrawTextProp1 =
			pCDcdTextbox1->getCdDrawTextProp();
		aCdDrawTextProp1.setCdFontProp(fontpropDefault);
		aCdDrawTextProp1.setTextColor(colorpropDefault);
		aCdDrawTextProp1.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
		pCDcdTextbox1->setCdDrawTextProp(aCdDrawTextProp1);

		CdDrawTextProp	aCdDrawTextProp2 =
			pCDcdTextbox2->getCdDrawTextProp();
		aCdDrawTextProp2.setCdFontProp(fontpropDefault);
		aCdDrawTextProp2.setTextColor(colorpropDefault);
		aCdDrawTextProp2.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
		pCDcdTextbox2->setCdDrawTextProp(aCdDrawTextProp2);

		CdDrawTextProp	aCdDrawTextProp3 =
			pCDcdTextbox3->getCdDrawTextProp();
		aCdDrawTextProp3.setCdFontProp(fontpropDefault);
		aCdDrawTextProp3.setTextColor(colorpropDefault);
		aCdDrawTextProp3.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
		pCDcdTextbox3->setCdDrawTextProp(aCdDrawTextProp3);


		//	セルを無効化
		InvalidateCell(iXColumnNumber1, iYColumnNumber);
		InvalidateCell(iXColumnNumber2, iYColumnNumber);
		InvalidateCell(iXColumnNumber3, iYColumnNumber);
	}
}

void CWndDcdGridCrossingCheck::OnUpdate_setCrossingCheckRule_To_Column(
	int iRuleIndex, 
	const CrossingCheckRule& aCrossingCheckRule)
{
	CdFontProp fontpropDefault = createFontProp();
	CdColorProp colorpropDefault = createStringColorProp();
	CdCrossingCheckYColSpecCont aYColSpecCont = createYColSpecCont();

	int iYColumnNumber = createYColSpecCont().ColumnNumberFromSpec(
		CdCrossingCheckYColSpec(CdCrossingCheckYColSpec::EColumnType::ColumnType_Caption, iRuleIndex));

	// --------------------------------
	//	行のY方向サイズを設定
	// --------------------------------
	{
		CDcdTargetGetDC	aCDcdTarget(NULL);

		CdDcdSizeXy	sizeRessya;
		CDcdTextbox	aCDcdTextbox(_T("京都京"),
			fontpropDefault,
			_T(""), 1, 2, 2);
		aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeRessya);

		getCXDcdGrid()->getYColumn(iYColumnNumber)->setColumnSize(sizeRessya.getY());

		Ou<CDcdLine>
			(getCXDcdGrid()->getYBorder(iYColumnNumber)->getIfDcDraw())
			->setCdPenProp(getCdPenPropNarrowLine());
	}


	// --------------------------------
	//	属性を設定
	// --------------------------------
	CdCrossingCheckXColSpecCont aXColSpecCont = createXColSpecCont();

	{
		//	前動作側方向・列車番号・種別
		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdCrossingCheckXColSpec(
			CdCrossingCheckXColSpec::EColumnType::ColumnType_BeforeRessyahoukou));
		Ou<CDcdTextbox> pCDcdTextbox =
			getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();

		tstring strCaption;
		if (!aCrossingCheckRule.bEnable)
		{
			strCaption += _T("[無効] ");

		}
		strCaption += _T("[");
		strCaption += to_tstring(iRuleIndex + 1);
		strCaption += _T("] ");

		strCaption += aCrossingCheckRule.strCaption;

		strCaption += _T(" (");
		if (aCrossingCheckRule.bBeforeIsArrival)
		{
			strCaption += _T("到着時刻・");
		}
		else
		{
			strCaption += _T("出発時刻・");
		}
		if (aCrossingCheckRule.bBeforeIsTsuuka)
		{
			strCaption += _T("通過→");
		}
		else
		{
			strCaption += _T("停車→");
		}
		if (aCrossingCheckRule.bAfterIsArrival)
		{
			strCaption += _T("到着時刻・");
		}
		else
		{
			strCaption += _T("出発時刻・");
		}
		if (aCrossingCheckRule.bAfterIsTsuuka)
		{
			strCaption += _T("通過 ");
		}
		else
		{
			strCaption += _T("停車 ");
		}
		strCaption += to_tstring(aCrossingCheckRule.iHeadwaySecondMinimum);
		strCaption += _T("〜");
		strCaption += to_tstring(aCrossingCheckRule.iHeadwaySecond);
		strCaption += _T("秒)");

		//	フォント属性
		CdDrawTextProp	aCdDrawTextProp =
			pCDcdTextbox->getCdDrawTextProp();
		aCdDrawTextProp.setCdFontProp(fontpropDefault);
		aCdDrawTextProp.setTextColor(colorpropDefault);
		aCdDrawTextProp.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_LEFT));
		pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);

		pCDcdTextbox->setText(strCaption);

		getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->setAttachCellCount(aXColSpecCont.size(), 1);

		//	セルを無効化
		InvalidateCell(iXColumnNumber, iYColumnNumber);
	}
}

void  CWndDcdGridCrossingCheck::OnUpdate_All()
{
	CWaitCursor	aCWaitCursor ;	
	
	{
		//	コマンドオブジェクト実行によるセル移動でセル選択にならないように、
		//	セル選択を解除し、セル選択機能も一時的に中止します。
		clearSelect();
		CPropStack aPropStack(this);
		aPropStack
			.CBoxSelect_setIsEnable(false)
			.CRandomSelect_setIsEnable(false);

		// --------------------------------		
		//	全要素を更新
		// --------------------------------
		m_KitenJikoku = getCDiagramEditDoc()->
			getCDedRosenFileData()->getCentDedRosen()->getKitenJikoku();

		const CentDedEkiCont* pCentDedEkiCont = getCDiagramEditDoc()->
			getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont();
		int iEkiIndex = pCentDedEkiCont->EkiIndexOfEkiID(GetDocument()->getEkiID());
		const CentDedEki* pCentDedEki = pCentDedEkiCont->getMuPtr()->get(iEkiIndex);

		/**
			m_MapTrackContentToList,m_MapListToTrackContentを初期化
		*/

		m_MapTrackContentToList.clear();
		m_MapListToTrackContent.clear();
		m_strTrackNameCont.clear();
		int iListIndex = 0;

		//Track
		const CentDedEkiTrack2Cont* pCentDedEkiTrack2Cont = pCentDedEki->getEkiTrack2Cont();
		vector<int> MapTrackContentToList0;
		for (int iEkiTrack2Index = 0; iEkiTrack2Index < pCentDedEkiTrack2Cont->size(); iEkiTrack2Index++)
		{
			MapTrackContentToList0.push_back(iListIndex);
			m_MapListToTrackContent[iListIndex] = TrackContent(ETrackType::TrackType_Track, iEkiTrack2Index);
			tstring strTemp = pCentDedEkiTrack2Cont->get(iEkiTrack2Index).getTrackName();
			m_strTrackNameCont.push_back(strTemp);
			iListIndex++;
		}
		m_MapTrackContentToList.push_back(MapTrackContentToList0);

		deque<int> iEkiIndexBranchLoop;
		pCentDedEkiCont->getEkiIndexBrunchLoop(iEkiIndex, iEkiIndexBranchLoop);
		sort(iEkiIndexBranchLoop.begin(), iEkiIndexBranchLoop.end());

		//MapTrackContentToListの内、当駅と関係ない駅の部分を埋めるために用います。
		//int iPrevPushBack = 0;
		vector<int> MapTrackContentToList1;
		vector<int> MapTrackContentToList2;
		MapTrackContentToList1.assign(pCentDedEkiCont->size(), -1);
		MapTrackContentToList2.assign(pCentDedEkiCont->size(), -1);
		for (int idx = 0; idx < (int)iEkiIndexBranchLoop.size(); idx++)
		{
			const CentDedEki* pCentDedEki = pCentDedEkiCont->getMuPtr()->get(iEkiIndexBranchLoop[idx]);
			if (iEkiIndexBranchLoop[idx] > 0 && pCentDedEki->getEkijikokukeisiki() != CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku)
			{
				MapTrackContentToList1[iEkiIndexBranchLoop[idx]] = iListIndex;
				m_MapListToTrackContent[iListIndex] = TrackContent(ETrackType::TrackType_Origin, iEkiIndexBranchLoop[idx]);

				/**
					移動元・先番線欄に表示するための文字列を求める。
					〜〜方面(起点側)の、〜〜に入る駅は、この駅から遡って一番近い主要駅を用います。ただし、iEkiIndexBranchLoop[idx - 1]よりも後ろ(含む)は除きます
					主要駅が見つからない場合は、直前の駅を用います
				*/
				int iEkiIndexLoopPrev = -1;
				if (idx > 0)
				{
					iEkiIndexLoopPrev = iEkiIndexBranchLoop[idx - 1];
				}
				tstring strTemp;
				for (int iPrevEkiIndex = iEkiIndexBranchLoop[idx] - 1; iPrevEkiIndex > iEkiIndexLoopPrev; iPrevEkiIndex--)
				{
					const CentDedEki* pCentDedEkiPrev = pCentDedEkiCont->getMuPtr()->get(iPrevEkiIndex);
					if (pCentDedEkiPrev->getEkikibo() == CentDedEki::EEkikibo::Ekikibo_Syuyou)
					{
						strTemp = pCentDedEkiPrev->getEkimei();
						break;
					}
				}
				if (strTemp.empty())
				{
					const CentDedEki* pCentDedEkiPrev = pCentDedEkiCont->getMuPtr()->get(iEkiIndexBranchLoop[idx] - 1);
					strTemp = pCentDedEkiPrev->getEkimei();
				}
				strTemp += _T("方面(起)");
				m_strTrackNameCont.push_back(strTemp);
				iListIndex++;
			}

			if (iEkiIndexBranchLoop[idx] < pCentDedEkiCont->size() - 1 &&
				pCentDedEki->getEkijikokukeisiki() != CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku)
			{
				MapTrackContentToList2[iEkiIndexBranchLoop[idx]] = iListIndex;
				m_MapListToTrackContent[iListIndex] = TrackContent(ETrackType::TrackType_Terminal, iEkiIndexBranchLoop[idx]);

				/**
					移動元・先番線欄に表示するための文字列を求める。
					〜〜方面(起点側)の、〜〜に入る駅は、この駅から遡って一番近い主要駅を用います。ただし、iEkiIndexBranchLoop[idx - 1]よりも後ろ(含む)は除きます
					主要駅が見つからない場合は、直前の駅を用います
				*/
				int iEkiIndexLoopNext = pCentDedEkiCont->size();
				if (idx < (int)iEkiIndexBranchLoop.size() - 1)
				{
					iEkiIndexLoopNext = iEkiIndexBranchLoop[idx + 1];
				}
				tstring strTemp;
				for (int iNextEkiIndex = iEkiIndexBranchLoop[idx] + 1; iNextEkiIndex < iEkiIndexLoopNext; iNextEkiIndex++)
				{
					const CentDedEki* pCentDedEkiNext = pCentDedEkiCont->getMuPtr()->get(iNextEkiIndex);
					if (pCentDedEkiNext->getEkikibo() == CentDedEki::EEkikibo::Ekikibo_Syuyou)
					{
						strTemp = pCentDedEkiNext->getEkimei();
						break;
					}
				}
				if (strTemp.empty())
				{
					const CentDedEki* pCentDedEkiNext = pCentDedEkiCont->getMuPtr()->get(iEkiIndexBranchLoop[idx] + 1);
					strTemp = pCentDedEkiNext->getEkimei();
				}
				strTemp += _T("方面(終)");
				m_strTrackNameCont.push_back(strTemp);
				iListIndex++;

			}
		}
		m_MapTrackContentToList.push_back(MapTrackContentToList1);
		m_MapTrackContentToList.push_back(MapTrackContentToList2);

		//路線外終着駅
		const vector<OuterTerminal> OuterTerminalCont = pCentDedEki->getOuterTerminalEkimeiCont();
		vector<int> MapTrackContentToList3;
		for (int iOuterTerminalIndex = 0; iOuterTerminalIndex < (int)OuterTerminalCont.size(); iOuterTerminalIndex++)
		{
			MapTrackContentToList3.push_back(iListIndex);
			m_MapListToTrackContent[iListIndex] = TrackContent(ETrackType::TrackType_Outer, iOuterTerminalIndex);
			tstring strTemp = OuterTerminalCont[iOuterTerminalIndex].OuterTerminalEkimei;
			strTemp += _T("方面(外)");
			m_strTrackNameCont.push_back(strTemp);
			iListIndex++;
		}
		m_MapTrackContentToList.push_back(MapTrackContentToList3);

		m_CrossingCheckSearchContArrival.resize(iListIndex);
		m_CrossingCheckSearchContDeparture.resize(iListIndex);
		m_CrossingCheckSearchContTsuuka.resize(iListIndex);
		for (int idx = 0; idx < iListIndex; idx++)
		{
			m_CrossingCheckSearchContArrival[idx].assign(iListIndex, list<CrossingCheckSearch>());
			m_CrossingCheckSearchContDeparture[idx].assign(iListIndex, list<CrossingCheckSearch>());
			m_CrossingCheckSearchContTsuuka[idx].assign(iListIndex, list<CrossingCheckSearch>());
		}

		//パターンダイヤプレビュー機能対応
		//有効な場合は、m_iPatternDiagramPreviewCycleSecondに秒数を代入しておく
		if (getCentDedDia()->getPatternDiagramPreviewEnable())
		{
			m_iPatternDiagramPreviewCycleSecond = getCentDedDia()->getPatternDiagramPreviewCycleSecond();
			m_iPatternDiagramPreviewRange = getCentDedDia()->getPatternDiagramPreviewRange();
		}
		else
		{
			m_iPatternDiagramPreviewCycleSecond = 0;
		}

		for (int iRessyahoukou = (int)ERessyahoukou::Ressyahoukou_Kudari; iRessyahoukou <= (int)ERessyahoukou::Ressyahoukou_Nobori; iRessyahoukou++)
		{
			const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont(
				(ERessyahoukou)iRessyahoukou);
			vector<int> iEkiOrderBranchLoop;
			if (iRessyahoukou == (int)ERessyahoukou::Ressyahoukou_Kudari)
			{
				iEkiOrderBranchLoop.insert(iEkiOrderBranchLoop.begin(),iEkiIndexBranchLoop.begin(), iEkiIndexBranchLoop.end());
			}
			else
			{
				for (int idx = (int)iEkiIndexBranchLoop.size()-1; idx >=0; idx--)
				{
					iEkiOrderBranchLoop.push_back(pCentDedRessyaCont->EkiOrderOfEkiIndex(iEkiIndexBranchLoop[idx]));
				}
			}
			for (int iRessyaIndex = 0; iRessyaIndex < pCentDedRessyaCont->size(); iRessyaIndex++)
			{
				const CentDedRessya* pCentDedRessya = pCentDedRessyaCont->getMuPtr()->get(iRessyaIndex);
				CdDedRessyaProperty aRessyaProperty((ERessyahoukou)iRessyahoukou, iRessyaIndex);

				if (pCentDedRessya->isNull() || pCentDedRessya->isCanceled())
				{
					continue;
				}

				int iValidSihatsuEkiOrder = pCentDedRessya->getValidSihatsuEki();
				int iValidSyuuchakuEkiOrder = pCentDedRessya->getValidSyuuchakuEki(); 
				if (iValidSihatsuEkiOrder < 0 || iValidSyuuchakuEkiOrder < 0)
				{
					continue;
				}

				for (int idx = 0; idx < (int)iEkiOrderBranchLoop.size(); idx++)
				{
					int iSearchEkiOrder = iEkiOrderBranchLoop[idx];
					int iSearchEkiIndex = pCentDedRessya->EkiIndexOfEkiOrder(iSearchEkiOrder);
					if (iSearchEkiOrder< iValidSihatsuEkiOrder || iSearchEkiOrder>iValidSyuuchakuEkiOrder)
					{
						continue;
					}
					if (iSearchEkiOrder == iValidSihatsuEkiOrder)
					{
						/**
							始発駅
							まずは、路線外始発+通過(当駅着時刻なし)を区別します。
						*/
						const CentDedEkiJikoku* pEkiJikoku =
							pCentDedRessya->getCentDedEkiJikokuCont()->getMuPtr()->get(iSearchEkiOrder);
						const CentDedBeforeOperationCont* pBeforeCont = pEkiJikoku->getCentDedBeforeOperationCont();
						const CentDedBeforeOperation* pFirstOperation = pBeforeCont->getMuPtr()->get(0);
						if (pEkiJikoku->getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka &&
							pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer &&
							pFirstOperation->getChakuJikoku().isNull())
						{
							CrossingCheckSearch aCrossingCheckSearch;
							TrackContent FromTrackContent(ETrackType::TrackType_Outer, pFirstOperation->getOuterShihatsuekiIndex());
							TrackContent ToTrackContent(ETrackType::TrackType_Track, pEkiJikoku->getRessyaTrackIndex());
							aCrossingCheckSearch.aRessyaProperty = aRessyaProperty;
							aCrossingCheckSearch.iEkiIndex = iSearchEkiIndex;
							aCrossingCheckSearch.FromTrackContent = FromTrackContent;
							aCrossingCheckSearch.ToTrackContent = ToTrackContent;

							int iFromTrackContentIndex = m_MapTrackContentToList[(int)FromTrackContent.eTrackType][FromTrackContent.iTrackIndex];
							int iToTrackContentIndex = m_MapTrackContentToList[(int)ToTrackContent.eTrackType][ToTrackContent.iTrackIndex];

							aCrossingCheckSearch.aRessyaProperty.setJikoku(pEkiJikoku->getHatsujikoku());

							InsertCrossingCheckSearch(
								iFromTrackContentIndex,
								iToTrackContentIndex,
								aCrossingCheckSearch,
								2);

						}
						else
						{
							/**
								先に後作業から行います。これは、路線外始発かつ当駅着時刻がない場合に代用する時刻を取得する必要があるからです。
								後作業は前方から検査するので、最初に見つかった時刻のみ取得します。後作業中に時刻がない場合は、当駅発時刻を取得します。
								いずれの場合も、前作業に時刻があればそれで上書きしていきます。
							*/
							const CentDedAfterOperationCont* pAfterCont = pEkiJikoku->getCentDedAfterOperationCont();
							//iPrevRessyaTrackIndex　各作業前の番線です。入換作業について、iPrevRessyaTrackIndexと入換先番線が等しい場合は、入換作業自体が無効となります。
							//また、当駅から駅構外・路線外へ出発するときの番線は、これになります。
							int iPrevRessyaTrackIndex = pEkiJikoku->getRessyaTrackIndex();

							//OperationJikokuTemp 開始作業が路線外始発かつ、当駅着時刻が空の場合は、この時刻を着時刻とみなします。入換時刻や増結時刻等で上書きしていきます。
							CdDedJikoku OperationJikokuTemp;
							for (int idxa = 0; idxa < pAfterCont->size(); idxa++)
							{
								const CentDedAfterOperation* pAfterOperation = pAfterCont->getMuPtr()->get(idxa);
								if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
								{
									SearchBeforeOperationCont(
										pAfterOperation->getCentDedBeforeOperationCont(),
										aRessyaProperty,
										pCentDedRessya,
										iPrevRessyaTrackIndex,
										iSearchEkiIndex,
										pAfterOperation->getConnectJikoku());
									if (OperationJikokuTemp.isNull())
									{
										OperationJikokuTemp = pAfterOperation->getConnectJikoku();
									}
								}
								else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
								{
									SearchAfterOperationCont(
										pAfterOperation->getCentDedAfterOperationCont(),
										aRessyaProperty,
										pCentDedRessya,
										iPrevRessyaTrackIndex,
										iSearchEkiIndex,
										pAfterOperation->getReleaseJikoku());
									if (OperationJikokuTemp.isNull())
									{
										OperationJikokuTemp = pAfterOperation->getReleaseJikoku();
									}
								}
								else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
								{
									if (iPrevRessyaTrackIndex != pAfterOperation->getShuntTrackIndex())
									{
										CrossingCheckSearch aCrossingCheckSearch;
										TrackContent FromTrackContent(ETrackType::TrackType_Track, iPrevRessyaTrackIndex);
										TrackContent ToTrackContent(ETrackType::TrackType_Track, pAfterOperation->getShuntTrackIndex());
										aCrossingCheckSearch.aRessyaProperty = aRessyaProperty;
										aCrossingCheckSearch.iEkiIndex = iSearchEkiIndex;
										aCrossingCheckSearch.FromTrackContent = FromTrackContent;
										aCrossingCheckSearch.ToTrackContent = ToTrackContent;

										int iFromTrackContentIndex = m_MapTrackContentToList[(int)FromTrackContent.eTrackType][FromTrackContent.iTrackIndex];
										int iToTrackContentIndex = m_MapTrackContentToList[(int)ToTrackContent.eTrackType][ToTrackContent.iTrackIndex];


										aCrossingCheckSearch.aRessyaProperty.setJikoku(pAfterOperation->getOperationChakuJikoku(true));
										InsertCrossingCheckSearch(
											iFromTrackContentIndex,
											iToTrackContentIndex,
											aCrossingCheckSearch,
											0);

										aCrossingCheckSearch.aRessyaProperty.setJikoku(pAfterOperation->getOperationHatsuJikoku());
										InsertCrossingCheckSearch(
											iFromTrackContentIndex,
											iToTrackContentIndex,
											aCrossingCheckSearch,
											1);

										iPrevRessyaTrackIndex = pAfterOperation->getShuntTrackIndex();
										if (OperationJikokuTemp.isNull())
										{
											OperationJikokuTemp = pAfterOperation->getOperationHatsuJikoku();
										}
									}
								}
							}

							/**
								iPrevRessyaTrackIndexから駅構外への出発動作をInsertCrossingCheckSearchします。
							*/

							CrossingCheckSearch aCrossingCheckSearch;

							TrackContent FromTrackContent(ETrackType::TrackType_Track, iPrevRessyaTrackIndex);

							TrackContent ToTrackContent;
							if (pCentDedRessya->getRessyahoukou() == ERessyahoukou::Ressyahoukou_Kudari)
							{
								ToTrackContent.eTrackType = ETrackType::TrackType_Terminal;
							}
							else
							{
								ToTrackContent.eTrackType = ETrackType::TrackType_Origin;
							}
							ToTrackContent.iTrackIndex = iSearchEkiIndex;
							aCrossingCheckSearch.aRessyaProperty = aRessyaProperty;
							aCrossingCheckSearch.iEkiIndex = iSearchEkiIndex;
							aCrossingCheckSearch.FromTrackContent = FromTrackContent;
							aCrossingCheckSearch.ToTrackContent = ToTrackContent;

							int iFromTrackContentIndex = m_MapTrackContentToList[(int)FromTrackContent.eTrackType][FromTrackContent.iTrackIndex];
							int iToTrackContentIndex = m_MapTrackContentToList[(int)ToTrackContent.eTrackType][ToTrackContent.iTrackIndex];

							aCrossingCheckSearch.aRessyaProperty.setJikoku(pEkiJikoku->getHatsujikoku());
							InsertCrossingCheckSearch(
								iFromTrackContentIndex,
								iToTrackContentIndex,
								aCrossingCheckSearch,
								1);

							if (OperationJikokuTemp.isNull())
							{
								OperationJikokuTemp = pEkiJikoku->getHatsujikoku();
							}


							//iNextRessyaTrackIndex　各作業後の番線です。入換作業について、iNextRessyaTrackIndexと入換元番線が等しい場合は、入換作業自体が無効となります。
							//また、駅構外・路線外から当駅に到着したときの番線は、これになります。
							int iNextRessyaTrackIndex = pEkiJikoku->getRessyaTrackIndex();

							for (int idxb = pBeforeCont->size() - 1; idxb > 0; idxb--)
							{
								const CentDedBeforeOperation* pBeforeOperation = pBeforeCont->getMuPtr()->get(idxb);
								if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
								{
									SearchBeforeOperationCont(
										pBeforeOperation->getCentDedBeforeOperationCont(),
										aRessyaProperty,
										pCentDedRessya,
										iNextRessyaTrackIndex,
										iSearchEkiIndex,
										pBeforeOperation->getConnectJikoku());
									OperationJikokuTemp = pBeforeOperation->getConnectJikoku();
								}
								else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
								{
									SearchAfterOperationCont(
										pBeforeOperation->getCentDedAfterOperationCont(),
										aRessyaProperty,
										pCentDedRessya,
										iNextRessyaTrackIndex,
										iSearchEkiIndex,
										pBeforeOperation->getReleaseJikoku());
									OperationJikokuTemp = pBeforeOperation->getReleaseJikoku();
								}
								else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
								{
									if (iNextRessyaTrackIndex != pBeforeOperation->getShuntTrackIndex())
									{
										CrossingCheckSearch aCrossingCheckSearch;
										TrackContent FromTrackContent(ETrackType::TrackType_Track, pBeforeOperation->getShuntTrackIndex());
										TrackContent ToTrackContent(ETrackType::TrackType_Track, iNextRessyaTrackIndex);
										aCrossingCheckSearch.aRessyaProperty = aRessyaProperty;
										aCrossingCheckSearch.iEkiIndex = iSearchEkiIndex;
										aCrossingCheckSearch.FromTrackContent = FromTrackContent;
										aCrossingCheckSearch.ToTrackContent = ToTrackContent;

										int iFromTrackContentIndex = m_MapTrackContentToList[(int)FromTrackContent.eTrackType][FromTrackContent.iTrackIndex];
										int iToTrackContentIndex = m_MapTrackContentToList[(int)ToTrackContent.eTrackType][ToTrackContent.iTrackIndex];

										aCrossingCheckSearch.aRessyaProperty.setJikoku(pBeforeOperation->getOperationChakuJikoku(true));
										InsertCrossingCheckSearch(
											iFromTrackContentIndex,
											iToTrackContentIndex,
											aCrossingCheckSearch,
											0);

										aCrossingCheckSearch.aRessyaProperty.setJikoku(pBeforeOperation->getOperationHatsuJikoku());
										InsertCrossingCheckSearch(
											iFromTrackContentIndex,
											iToTrackContentIndex,
											aCrossingCheckSearch,
											1);

										iNextRessyaTrackIndex = pBeforeOperation->getShuntTrackIndex();
										OperationJikokuTemp = pBeforeOperation->getOperationHatsuJikoku();
									}
								}
							}

							if (pBeforeCont->getMuPtr()->get(0)->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
							{
								/**
									先頭要素が路線外始発の場合は、路線外からiNextRessyaTrackIndexへの到着動作をInsertCrossingCheckSearchします。
								*/
								const CentDedBeforeOperation* pBeforeOperation = pBeforeCont->getMuPtr()->get(0);

								CrossingCheckSearch aCrossingCheckSearch;
								TrackContent FromTrackContent(ETrackType::TrackType_Outer, pBeforeOperation->getOuterShihatsuekiIndex());
								TrackContent ToTrackContent(ETrackType::TrackType_Track, iNextRessyaTrackIndex);
								aCrossingCheckSearch.aRessyaProperty = aRessyaProperty;
								aCrossingCheckSearch.iEkiIndex = iSearchEkiIndex;
								aCrossingCheckSearch.FromTrackContent = FromTrackContent;
								aCrossingCheckSearch.ToTrackContent = ToTrackContent;

								int iFromTrackContentIndex = m_MapTrackContentToList[(int)FromTrackContent.eTrackType][FromTrackContent.iTrackIndex];
								int iToTrackContentIndex = m_MapTrackContentToList[(int)ToTrackContent.eTrackType][ToTrackContent.iTrackIndex];

								aCrossingCheckSearch.aRessyaProperty.setJikoku(pBeforeOperation->getChakuJikoku());
								if (pBeforeOperation->getChakuJikoku().isNull())
								{
									aCrossingCheckSearch.aRessyaProperty.setJikoku(OperationJikokuTemp);
								}

								InsertCrossingCheckSearch(
									iFromTrackContentIndex,
									iToTrackContentIndex,
									aCrossingCheckSearch,
									0);
							}
						}
					}
					else if (iSearchEkiOrder == iValidSyuuchakuEkiOrder)
					{
						/**
							終着駅
							まずは、路線外終着+通過(当駅発時刻なし)を区別します。
						*/
						const CentDedEkiJikoku* pEkiJikoku =
							pCentDedRessya->getCentDedEkiJikokuCont()->getMuPtr()->get(iSearchEkiOrder);
						const CentDedAfterOperationCont* pAfterCont = pEkiJikoku->getCentDedAfterOperationCont();
						const CentDedAfterOperation* pLastOperation = pAfterCont->getMuPtr()->get(INT_MAX);
						if (pEkiJikoku->getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka &&
							pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer &&
							pLastOperation->getHatsuJikoku().isNull())
						{
							CrossingCheckSearch aCrossingCheckSearch;
							TrackContent FromTrackContent(ETrackType::TrackType_Track, pEkiJikoku->getRessyaTrackIndex());
							TrackContent ToTrackContent(ETrackType::TrackType_Outer, pLastOperation->getOuterShuchakuekiIndex());
							aCrossingCheckSearch.aRessyaProperty = aRessyaProperty;
							aCrossingCheckSearch.iEkiIndex = iSearchEkiIndex;
							aCrossingCheckSearch.FromTrackContent = FromTrackContent;
							aCrossingCheckSearch.ToTrackContent = ToTrackContent;

							int iFromTrackContentIndex = m_MapTrackContentToList[(int)FromTrackContent.eTrackType][FromTrackContent.iTrackIndex];
							int iToTrackContentIndex = m_MapTrackContentToList[(int)ToTrackContent.eTrackType][ToTrackContent.iTrackIndex];

							aCrossingCheckSearch.aRessyaProperty.setJikoku(pEkiJikoku->getChakujikoku());

							InsertCrossingCheckSearch(
								iFromTrackContentIndex,
								iToTrackContentIndex,
								aCrossingCheckSearch,
								2);
						}
						else
						{
							/**
								先に前作業から行います。これは、路線外終着かつ当駅発時刻がない場合に代用する時刻を取得する必要があるからです。
								前作業は後方から検査するので、最初に見つかった時刻のみ取得します。前作業中に時刻がない場合は、当駅着時刻を取得します。
								いずれの場合も、後作業に時刻があればそれで上書きしていきます。
							*/
							const CentDedBeforeOperationCont* pBeforeCont = pEkiJikoku->getCentDedBeforeOperationCont();

							//iNextRessyaTrackIndex　各作業後の番線です。入換作業について、iNextRessyaTrackIndexと入換元番線が等しい場合は、入換作業自体が無効となります。
							//また、駅構外・路線外から当駅に到着したときの番線は、これになります。
							int iNextRessyaTrackIndex = pEkiJikoku->getRessyaTrackIndex();
							//OperationJikokuTemp 終了作業が路線外終着かつ、当駅発時刻が空の場合は、この時刻を発時刻とみなします。入換時刻や増結時刻等で上書きしていきます。
							CdDedJikoku OperationJikokuTemp;
							for (int idxb = pBeforeCont->size() - 1; idxb >= 0; idxb--)
							{
								const CentDedBeforeOperation* pBeforeOperation = pBeforeCont->getMuPtr()->get(idxb);
								if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
								{
									SearchBeforeOperationCont(
										pBeforeOperation->getCentDedBeforeOperationCont(),
										aRessyaProperty,
										pCentDedRessya,
										iNextRessyaTrackIndex,
										iSearchEkiIndex,
										pBeforeOperation->getConnectJikoku());
									if (OperationJikokuTemp.isNull())
									{
										OperationJikokuTemp = pBeforeOperation->getConnectJikoku();
									}
								}
								else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
								{
									SearchAfterOperationCont(
										pBeforeOperation->getCentDedAfterOperationCont(),
										aRessyaProperty,
										pCentDedRessya,
										iNextRessyaTrackIndex,
										iSearchEkiIndex,
										pBeforeOperation->getReleaseJikoku());
									if (OperationJikokuTemp.isNull())
									{
										OperationJikokuTemp = pBeforeOperation->getReleaseJikoku();
									}
								}
								else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
								{
									if (iNextRessyaTrackIndex != pBeforeOperation->getShuntTrackIndex())
									{
										CrossingCheckSearch aCrossingCheckSearch;
										TrackContent FromTrackContent(ETrackType::TrackType_Track, pBeforeOperation->getShuntTrackIndex());
										TrackContent ToTrackContent(ETrackType::TrackType_Track, iNextRessyaTrackIndex);
										aCrossingCheckSearch.aRessyaProperty = aRessyaProperty;
										aCrossingCheckSearch.iEkiIndex = iSearchEkiIndex;
										aCrossingCheckSearch.FromTrackContent = FromTrackContent;
										aCrossingCheckSearch.ToTrackContent = ToTrackContent;

										int iFromTrackContentIndex = m_MapTrackContentToList[(int)FromTrackContent.eTrackType][FromTrackContent.iTrackIndex];
										int iToTrackContentIndex = m_MapTrackContentToList[(int)ToTrackContent.eTrackType][ToTrackContent.iTrackIndex];


										aCrossingCheckSearch.aRessyaProperty.setJikoku(pBeforeOperation->getOperationChakuJikoku(true));
										InsertCrossingCheckSearch(
											iFromTrackContentIndex,
											iToTrackContentIndex,
											aCrossingCheckSearch,
											0);

										aCrossingCheckSearch.aRessyaProperty.setJikoku(pBeforeOperation->getOperationHatsuJikoku());
										InsertCrossingCheckSearch(
											iFromTrackContentIndex,
											iToTrackContentIndex,
											aCrossingCheckSearch,
											1);

										iNextRessyaTrackIndex = pBeforeOperation->getShuntTrackIndex();
										if (OperationJikokuTemp.isNull())
										{
											OperationJikokuTemp = pBeforeOperation->getOperationHatsuJikoku();
										}
									}
								}
							}

							/**
								駅構外からiNextRessyaTrackIndexへの到着動作をInsertCrossingCheckSearchします。
							*/

							CrossingCheckSearch aCrossingCheckSearch;
							TrackContent FromTrackContent;
							if (pCentDedRessya->getRessyahoukou() == ERessyahoukou::Ressyahoukou_Kudari)
							{
								FromTrackContent.eTrackType = ETrackType::TrackType_Origin;
							}
							else
							{
								FromTrackContent.eTrackType = ETrackType::TrackType_Terminal;
							}
							FromTrackContent.iTrackIndex = iSearchEkiIndex;

							TrackContent ToTrackContent(ETrackType::TrackType_Track, iNextRessyaTrackIndex);
							aCrossingCheckSearch.aRessyaProperty = aRessyaProperty;
							aCrossingCheckSearch.iEkiIndex = iSearchEkiIndex;
							aCrossingCheckSearch.FromTrackContent = FromTrackContent;
							aCrossingCheckSearch.ToTrackContent = ToTrackContent;

							int iFromTrackContentIndex = m_MapTrackContentToList[(int)FromTrackContent.eTrackType][FromTrackContent.iTrackIndex];
							int iToTrackContentIndex = m_MapTrackContentToList[(int)ToTrackContent.eTrackType][ToTrackContent.iTrackIndex];

							aCrossingCheckSearch.aRessyaProperty.setJikoku(pEkiJikoku->getChakujikoku());
							InsertCrossingCheckSearch(
								iFromTrackContentIndex,
								iToTrackContentIndex,
								aCrossingCheckSearch,
								0);

							if (OperationJikokuTemp.isNull())
							{
								OperationJikokuTemp = pEkiJikoku->getChakujikoku();
							}

							//iPrevRessyaTrackIndex　各作業前の番線です。入換作業について、iPrevRessyaTrackIndexと入換先番線が等しい場合は、入換作業自体が無効となります。
							//また、当駅から駅構外・路線外へ出発するときの番線は、これになります。
							int iPrevRessyaTrackIndex = pEkiJikoku->getRessyaTrackIndex();

							//OperationJikokuTemp 開始作業が路線外始発かつ、当駅着時刻が空の場合は、この時刻を着時刻とみなします。入換時刻や増結時刻等で上書きしていきます。
							for (int idxa = 0; idxa < pAfterCont->size()-1; idxa++)
							{
								const CentDedAfterOperation* pAfterOperation = pAfterCont->getMuPtr()->get(idxa);
								if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
								{
									SearchBeforeOperationCont(
										pAfterOperation->getCentDedBeforeOperationCont(),
										aRessyaProperty,
										pCentDedRessya,
										iPrevRessyaTrackIndex,
										iSearchEkiIndex,
										pAfterOperation->getConnectJikoku());
									OperationJikokuTemp = pAfterOperation->getConnectJikoku();
								}
								else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
								{
									SearchAfterOperationCont(
										pAfterOperation->getCentDedAfterOperationCont(),
										aRessyaProperty,
										pCentDedRessya,
										iPrevRessyaTrackIndex,
										iSearchEkiIndex,
										pAfterOperation->getReleaseJikoku());
									OperationJikokuTemp = pAfterOperation->getReleaseJikoku();
								}
								else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
								{
									if (iPrevRessyaTrackIndex != pAfterOperation->getShuntTrackIndex())
									{
										CrossingCheckSearch aCrossingCheckSearch;
										TrackContent FromTrackContent(ETrackType::TrackType_Track, iPrevRessyaTrackIndex);
										TrackContent ToTrackContent(ETrackType::TrackType_Track, pAfterOperation->getShuntTrackIndex());
										aCrossingCheckSearch.aRessyaProperty = aRessyaProperty;
										aCrossingCheckSearch.iEkiIndex = iSearchEkiIndex;
										aCrossingCheckSearch.FromTrackContent = FromTrackContent;
										aCrossingCheckSearch.ToTrackContent = ToTrackContent;

										int iFromTrackContentIndex = m_MapTrackContentToList[(int)FromTrackContent.eTrackType][FromTrackContent.iTrackIndex];
										int iToTrackContentIndex = m_MapTrackContentToList[(int)ToTrackContent.eTrackType][ToTrackContent.iTrackIndex];

										aCrossingCheckSearch.aRessyaProperty.setJikoku(pAfterOperation->getOperationChakuJikoku(true));
										InsertCrossingCheckSearch(
											iFromTrackContentIndex,
											iToTrackContentIndex,
											aCrossingCheckSearch,
											0);

										aCrossingCheckSearch.aRessyaProperty.setJikoku(pAfterOperation->getOperationHatsuJikoku());
										InsertCrossingCheckSearch(
											iFromTrackContentIndex,
											iToTrackContentIndex,
											aCrossingCheckSearch,
											1);

										iPrevRessyaTrackIndex = pAfterOperation->getShuntTrackIndex();
										OperationJikokuTemp = pAfterOperation->getOperationChakuJikoku(true);
									}
								}
							}

							if (pAfterCont->getMuPtr()->get(INT_MAX)->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
							{
								/**
									末尾要素が路線外終着の場合は、iPrevRessyaTrackIndexから路線外への出発動作をInsertCrossingCheckSearchします。
								*/
								const CentDedAfterOperation* pAfterOperation = pAfterCont->getMuPtr()->get(INT_MAX);

								CrossingCheckSearch aCrossingCheckSearch;
								TrackContent FromTrackContent(ETrackType::TrackType_Track, iPrevRessyaTrackIndex);
								TrackContent ToTrackContent(ETrackType::TrackType_Outer, pAfterOperation->getOuterShuchakuekiIndex());
								aCrossingCheckSearch.aRessyaProperty = aRessyaProperty;
								aCrossingCheckSearch.iEkiIndex = iSearchEkiIndex;
								aCrossingCheckSearch.FromTrackContent = FromTrackContent;
								aCrossingCheckSearch.ToTrackContent = ToTrackContent;

								int iFromTrackContentIndex = m_MapTrackContentToList[(int)FromTrackContent.eTrackType][FromTrackContent.iTrackIndex];
								int iToTrackContentIndex = m_MapTrackContentToList[(int)ToTrackContent.eTrackType][ToTrackContent.iTrackIndex];

								aCrossingCheckSearch.aRessyaProperty.setJikoku(pAfterOperation->getHatsuJikoku());
								if (pAfterOperation->getHatsuJikoku().isNull())
								{
									aCrossingCheckSearch.aRessyaProperty.setJikoku(OperationJikokuTemp);
								}

								InsertCrossingCheckSearch(
									iFromTrackContentIndex,
									iToTrackContentIndex,
									aCrossingCheckSearch,
									1);
							}
						}
					}
					/**
						始発駅以外で、前の駅からこの駅の間が運行なしの場合は、飛ばします(分岐駅関係の場合は、着側の段階で行うので)
					*/
					else if (pCentDedRessya->isRunBetweenNextEki(iSearchEkiOrder - 1))
					{
						/**
							この駅から次の駅の間が運行なしの場合は、終点側からisRunBetweenNextEkiがtrueの駅を探し、その駅とこの駅が分岐・環状関係であるかどうかを確かめます。
							分岐・環状関係なら、その駅から発側(発時刻・後作業)を取得します。
						*/
						int iHatsuEkiOrder = iSearchEkiOrder;
						if (!pCentDedRessya->isRunBetweenNextEki(iSearchEkiOrder))
						{
							iHatsuEkiOrder = pCentDedRessya->getRunBetweenEkiForward(iSearchEkiOrder);
							if (iHatsuEkiOrder < 0 ||
								!pCentDedEkiCont->isSameBrunchLoopGroup(iSearchEkiOrder, iHatsuEkiOrder, pCentDedRessya->getRessyahoukou()))
							{
								continue;
							}
							else
							{
								//idxをiHatsuEkiOrderの位置まで進めておきます

								for (idx++; idx < (int)iEkiOrderBranchLoop.size(); idx++)
								{
									if (iEkiOrderBranchLoop[idx] == iHatsuEkiOrder)
									{
										break;
									}
								}
							}
						}
						int iHatsuEkiIndex = pCentDedRessya->EkiIndexOfEkiOrder(iHatsuEkiOrder);
						const CentDedEkiJikoku* pEkiJikokuChaku =
							pCentDedRessya->getCentDedEkiJikokuCont()->getMuPtr()->get(iSearchEkiOrder);
						const CentDedEkiJikoku* pEkiJikokuHatsu =
							pCentDedRessya->getCentDedEkiJikokuCont()->getMuPtr()->get(iHatsuEkiOrder);
						/**
							停車・運転停車と通過の区別を行います。また、通過の場合、着側発側ともに時刻なしの場合は飛ばします。
							停車の場合は、両方とも時刻があることを必須とします。
						*/
						if (pEkiJikokuChaku->getChakujikoku().isNull() &&
							pEkiJikokuHatsu->getHatsujikoku().isNull())
						{
							//両時刻とも無いので通過かつ飛ばし
							continue;
						}
						else if (!pEkiJikokuChaku->getChakujikoku().isNull() &&
							!pEkiJikokuHatsu->getHatsujikoku().isNull())
						{

							SearchBeforeOperationCont(
								pEkiJikokuChaku->getCentDedBeforeOperationCont(),
								aRessyaProperty,
								pCentDedRessya,
								pEkiJikokuChaku->getRessyaTrackIndex(),
								iSearchEkiIndex,
								pEkiJikokuChaku->getChakujikoku());

							SearchAfterOperationCont(
								pEkiJikokuHatsu->getCentDedAfterOperationCont(),
								aRessyaProperty,
								pCentDedRessya,
								pEkiJikokuChaku->getRessyaTrackIndex(),
								iHatsuEkiIndex,
								pEkiJikokuHatsu->getHatsujikoku());
						}
						else if (pEkiJikokuChaku->getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
						{
							CdDedJikoku aCdDedJikoku = pEkiJikokuChaku->getChakujikoku();
							if (aCdDedJikoku.isNull())
							{
								aCdDedJikoku = pEkiJikokuHatsu->getHatsujikoku();
							}

							{
								/**
									駅構外からの到着動作をInsertCrossingCheckSearchします。
								*/

								CrossingCheckSearch aCrossingCheckSearch;
								TrackContent FromTrackContent;
								if (pCentDedRessya->getRessyahoukou() == ERessyahoukou::Ressyahoukou_Kudari)
								{
									FromTrackContent.eTrackType = ETrackType::TrackType_Origin;
								}
								else
								{
									FromTrackContent.eTrackType = ETrackType::TrackType_Terminal;
								}
								FromTrackContent.iTrackIndex = iSearchEkiIndex;

								TrackContent ToTrackContent(ETrackType::TrackType_Track, pEkiJikokuChaku->getRessyaTrackIndex());
								aCrossingCheckSearch.aRessyaProperty = aRessyaProperty;
								aCrossingCheckSearch.iEkiIndex = iSearchEkiIndex;
								aCrossingCheckSearch.FromTrackContent = FromTrackContent;
								aCrossingCheckSearch.ToTrackContent = ToTrackContent;

								int iFromTrackContentIndex = m_MapTrackContentToList[(int)FromTrackContent.eTrackType][FromTrackContent.iTrackIndex];
								int iToTrackContentIndex = m_MapTrackContentToList[(int)ToTrackContent.eTrackType][ToTrackContent.iTrackIndex];

								aCrossingCheckSearch.aRessyaProperty.setJikoku(aCdDedJikoku);
								InsertCrossingCheckSearch(
									iFromTrackContentIndex,
									iToTrackContentIndex,
									aCrossingCheckSearch,
									2);
							}
							{
								/**
									駅構外への出発動作をInsertCrossingCheckSearchします。
								*/
								CrossingCheckSearch aCrossingCheckSearch;

								TrackContent FromTrackContent(ETrackType::TrackType_Track, pEkiJikokuHatsu->getRessyaTrackIndex());

								TrackContent ToTrackContent;
								if (pCentDedRessya->getRessyahoukou() == ERessyahoukou::Ressyahoukou_Kudari)
								{
									ToTrackContent.eTrackType = ETrackType::TrackType_Terminal;
								}
								else
								{
									ToTrackContent.eTrackType = ETrackType::TrackType_Origin;
								}
								ToTrackContent.iTrackIndex = iHatsuEkiIndex;
								aCrossingCheckSearch.aRessyaProperty = aRessyaProperty;
								aCrossingCheckSearch.iEkiIndex = iHatsuEkiIndex;
								aCrossingCheckSearch.FromTrackContent = FromTrackContent;
								aCrossingCheckSearch.ToTrackContent = ToTrackContent;

								int iFromTrackContentIndex = m_MapTrackContentToList[(int)FromTrackContent.eTrackType][FromTrackContent.iTrackIndex];
								int iToTrackContentIndex = m_MapTrackContentToList[(int)ToTrackContent.eTrackType][ToTrackContent.iTrackIndex];

								aCrossingCheckSearch.aRessyaProperty.setJikoku(aCdDedJikoku);
								InsertCrossingCheckSearch(
									iFromTrackContentIndex,
									iToTrackContentIndex,
									aCrossingCheckSearch,
									2);
							}
						}
						else
						{
							if (pEkiJikokuChaku->getChakujikoku().isNull())
							{
								/**
									駅構外への出発動作をInsertCrossingCheckSearchします。
								*/
								CrossingCheckSearch aCrossingCheckSearch;

								TrackContent FromTrackContent(ETrackType::TrackType_Track, pEkiJikokuHatsu->getRessyaTrackIndex());

								TrackContent ToTrackContent;
								if (pCentDedRessya->getRessyahoukou() == ERessyahoukou::Ressyahoukou_Kudari)
								{
									FromTrackContent.eTrackType = ETrackType::TrackType_Terminal;
								}
								else
								{
									FromTrackContent.eTrackType = ETrackType::TrackType_Origin;
								}
								FromTrackContent.iTrackIndex = iHatsuEkiIndex;
								aCrossingCheckSearch.aRessyaProperty = aRessyaProperty;
								aCrossingCheckSearch.iEkiIndex = iHatsuEkiIndex;
								aCrossingCheckSearch.FromTrackContent = FromTrackContent;
								aCrossingCheckSearch.ToTrackContent = ToTrackContent;

								int iFromTrackContentIndex = m_MapTrackContentToList[(int)FromTrackContent.eTrackType][FromTrackContent.iTrackIndex];
								int iToTrackContentIndex = m_MapTrackContentToList[(int)ToTrackContent.eTrackType][ToTrackContent.iTrackIndex];

								aCrossingCheckSearch.aRessyaProperty.setJikoku(pEkiJikokuChaku->getHatsujikoku());
								InsertCrossingCheckSearch(
									iFromTrackContentIndex,
									iToTrackContentIndex,
									aCrossingCheckSearch,
									0);
							}
							else
							{
								/**
									駅構外からの到着動作をInsertCrossingCheckSearchします。
								*/

								CrossingCheckSearch aCrossingCheckSearch;
								TrackContent FromTrackContent;
								if (pCentDedRessya->getRessyahoukou() == ERessyahoukou::Ressyahoukou_Kudari)
								{
									FromTrackContent.eTrackType = ETrackType::TrackType_Origin;
								}
								else
								{
									FromTrackContent.eTrackType = ETrackType::TrackType_Terminal;
								}
								FromTrackContent.iTrackIndex = iSearchEkiIndex;

								TrackContent ToTrackContent(ETrackType::TrackType_Track, pEkiJikokuChaku->getRessyaTrackIndex());
								aCrossingCheckSearch.aRessyaProperty = aRessyaProperty;
								aCrossingCheckSearch.iEkiIndex = iSearchEkiIndex;
								aCrossingCheckSearch.FromTrackContent = FromTrackContent;
								aCrossingCheckSearch.ToTrackContent = ToTrackContent;

								int iFromTrackContentIndex = m_MapTrackContentToList[(int)FromTrackContent.eTrackType][FromTrackContent.iTrackIndex];
								int iToTrackContentIndex = m_MapTrackContentToList[(int)ToTrackContent.eTrackType][ToTrackContent.iTrackIndex];

								aCrossingCheckSearch.aRessyaProperty.setJikoku(pEkiJikokuChaku->getChakujikoku());
								InsertCrossingCheckSearch(
									iFromTrackContentIndex,
									iToTrackContentIndex,
									aCrossingCheckSearch,
									1);

							}
						}
					}
				}
			}
		}

		/**
			各ルールに基づき、前動作と後動作に該当する動作をそれぞれ一つにまとめ、時間順に並べます。
		*/
		m_CrossingCheckContentCont.clear();
		m_CrossingCheckContentCont.assign(pCentDedEki->getCrossingCheckRuleSize(), vector< CrossingCheckContent>());
		for (int idx = 0; idx < pCentDedEki->getCrossingCheckRuleSize(); idx++)
		{
			CrossingCheckRule aCrossingCheckRule = pCentDedEki->getCrossingCheckRule(idx);

			if (!aCrossingCheckRule.bEnable)
			{
				continue;
			}
			list<CrossingCheckSearch> BeforeCrossingCheckSearchCont;
			list<CrossingCheckSearch> AfterCrossingCheckSearchCont;

			for (int idxbf = 0; idxbf < (int)aCrossingCheckRule.BeforeFromTrackContentCont.size(); idxbf++)
			{
				int iBFIndex = m_MapTrackContentToList[(int)aCrossingCheckRule.BeforeFromTrackContentCont[idxbf].eTrackType][aCrossingCheckRule.BeforeFromTrackContentCont[idxbf].iTrackIndex];
				for (int idxbt = 0; idxbt < (int)aCrossingCheckRule.BeforeToTrackContentCont.size(); idxbt++)
				{
					int iBTIndex = m_MapTrackContentToList[(int)aCrossingCheckRule.BeforeToTrackContentCont[idxbt].eTrackType][aCrossingCheckRule.BeforeToTrackContentCont[idxbt].iTrackIndex];
					if (aCrossingCheckRule.bBeforeIsTsuuka)
					{
						MergeCrossingCheckSearchCont(&BeforeCrossingCheckSearchCont,
							&m_CrossingCheckSearchContTsuuka[iBFIndex][iBTIndex]);
					}
					else if (aCrossingCheckRule.bBeforeIsArrival)
					{
						MergeCrossingCheckSearchCont(&BeforeCrossingCheckSearchCont,
							&m_CrossingCheckSearchContArrival[iBFIndex][iBTIndex]);
					}
					else
					{
						MergeCrossingCheckSearchCont(&BeforeCrossingCheckSearchCont,
							&m_CrossingCheckSearchContDeparture[iBFIndex][iBTIndex]);
					}
				}
			}

			for (int idxaf = 0; idxaf < (int)aCrossingCheckRule.AfterFromTrackContentCont.size(); idxaf++)
			{
				int iAFIndex = m_MapTrackContentToList[(int)aCrossingCheckRule.AfterFromTrackContentCont[idxaf].eTrackType][aCrossingCheckRule.AfterFromTrackContentCont[idxaf].iTrackIndex];
				for (int idxat = 0; idxat < (int)aCrossingCheckRule.AfterToTrackContentCont.size(); idxat++)
				{
					int iATIndex = m_MapTrackContentToList[(int)aCrossingCheckRule.AfterToTrackContentCont[idxat].eTrackType][aCrossingCheckRule.AfterToTrackContentCont[idxat].iTrackIndex];
					if (aCrossingCheckRule.bAfterIsTsuuka)
					{
						MergeCrossingCheckSearchCont(&AfterCrossingCheckSearchCont,
							&m_CrossingCheckSearchContTsuuka[iAFIndex][iATIndex]);
					}
					else if (aCrossingCheckRule.bAfterIsArrival)
					{
						MergeCrossingCheckSearchCont(&AfterCrossingCheckSearchCont,
							&m_CrossingCheckSearchContArrival[iAFIndex][iATIndex]);
					}
					else
					{
						MergeCrossingCheckSearchCont(&AfterCrossingCheckSearchCont,
							&m_CrossingCheckSearchContDeparture[iAFIndex][iATIndex]);
					}
				}
			}
			if (BeforeCrossingCheckSearchCont.empty() || AfterCrossingCheckSearchCont.empty())
			{
				continue;
			}
			/**
				itrAfterTemp
				リストの探索量を減らすために用います。
				Before,Afterともに、リストは時刻順に並んでいます。
				従って、BeforeListの任意の要素の時刻よりも、時刻が前のAfterListの要素は、
				BeforeListのそれ以降の要素の時刻よりも、必ず時刻が前になります。
				従って、一度時刻が前になったAfterの要素は、それ以降参照する必要が無くなります。
				なので、時刻が前になったものをitrAfterTempに収めておき、itrBeforeの探索が次要素に移ったときは、After要素をitrAfterTempから探索します。
			*/
			auto itrAfterTemp = AfterCrossingCheckSearchCont.begin();
			for (auto itrBefore = BeforeCrossingCheckSearchCont.begin(); itrBefore != BeforeCrossingCheckSearchCont.end(); itrBefore++)
			{
				//パターンダイヤプレビュー機能が有効な場合、CrossingCheckContentを生成するのは、前作業が元列車(iShiftSecond==0)の場合のみです。
				if (itrBefore->iShiftSecond != 0)
				{
					continue;
				}
				CdDedJikoku MinimumJikoku = itrBefore->aRessyaProperty.getJikoku();
				MinimumJikoku.addSeconds(aCrossingCheckRule.iHeadwaySecondMinimum);
				CdDedJikoku MaximumJikoku = itrBefore->aRessyaProperty.getJikoku();
				MaximumJikoku.addSeconds(aCrossingCheckRule.iHeadwaySecond);
				for (auto itrAfter = itrAfterTemp; itrAfter != AfterCrossingCheckSearchCont.end(); itrAfter++)
				{
					if (itrAfter->aRessyaProperty.getJikoku().compare(MinimumJikoku, m_KitenJikoku) < 0)
					{
						itrAfterTemp = itrAfter;
					}
					else if (itrAfter->aRessyaProperty.getJikoku().compare(MaximumJikoku, m_KitenJikoku) < 0)
					{
						/**
							同一の動作同士の場合はスルーします
							・列車プロパティが一致(時刻含む)
							・前動作と後動作の、移動元・移動先番線がそれぞれ一致。
						*/
						if (itrBefore->aRessyaProperty == itrAfter->aRessyaProperty &&
							itrBefore->FromTrackContent.equal(itrAfter->FromTrackContent) &&
							itrBefore->ToTrackContent.equal(itrAfter->ToTrackContent))
						{
							continue;
						}
						CrossingCheckContent aCrossingCheckContent;
						aCrossingCheckContent.BeforeRessyaProperty = itrBefore->aRessyaProperty;
						aCrossingCheckContent.iBeforeEkiIndex = itrBefore->iEkiIndex;
						aCrossingCheckContent.BeforeFromTrackContent = itrBefore->FromTrackContent;
						aCrossingCheckContent.BeforeToTrackContent = itrBefore->ToTrackContent;
						aCrossingCheckContent.AfterRessyaProperty = itrAfter->aRessyaProperty;
						aCrossingCheckContent.iAfterEkiIndex = itrAfter->iEkiIndex;
						aCrossingCheckContent.AfterFromTrackContent = itrAfter->FromTrackContent;
						aCrossingCheckContent.AfterToTrackContent = itrAfter->ToTrackContent;;
						aCrossingCheckContent.iHeadway = itrAfter->aRessyaProperty.getJikoku().subJikoku(itrBefore->aRessyaProperty.getJikoku());

						m_CrossingCheckContentCont[idx].push_back(aCrossingCheckContent);
					}
					else
					{
						break;
					}

					//if (itrBefore->aRessyaProperty.getJikoku().compare(itrAfter->aRessyaProperty.getJikoku(),m_KitenJikoku) <= 0)
					//{
					//	int iHeadway = itrAfter->aRessyaProperty.getJikoku().subJikoku(itrBefore->aRessyaProperty.getJikoku());
					//	if (iHeadway >= 0 && iHeadway < aCrossingCheckRule.iHeadwaySecond)
					//	{
					//		/**
					//			同一の動作同士の場合はスルーします
					//			・列車プロパティが一致(時刻含む)
					//			・前動作と後動作の、移動元・移動先番線がそれぞれ一致。
					//		*/
					//		if (itrBefore->aRessyaProperty == itrAfter->aRessyaProperty &&
					//			itrBefore->FromTrackContent.equal(itrAfter->FromTrackContent) &&
					//			itrBefore->ToTrackContent.equal(itrAfter->ToTrackContent))
					//		{
					//			continue;
					//		}
					//		CrossingCheckContent aCrossingCheckContent;
					//		aCrossingCheckContent.BeforeRessyaProperty = itrBefore->aRessyaProperty;
					//		aCrossingCheckContent.iBeforeEkiIndex = itrBefore->iEkiIndex;
					//		aCrossingCheckContent.BeforeFromTrackContent = itrBefore->FromTrackContent;
					//		aCrossingCheckContent.BeforeToTrackContent = itrBefore->ToTrackContent;
					//		aCrossingCheckContent.AfterRessyaProperty = itrAfter->aRessyaProperty;
					//		aCrossingCheckContent.iAfterEkiIndex = itrAfter->iEkiIndex;
					//		aCrossingCheckContent.AfterFromTrackContent = itrAfter->FromTrackContent;
					//		aCrossingCheckContent.AfterToTrackContent = itrAfter->ToTrackContent;;
					//		aCrossingCheckContent.iHeadway = itrAfter->aRessyaProperty.getJikoku().subJikoku(itrBefore->aRessyaProperty.getJikoku());

					//		m_CrossingCheckContentCont[idx].push_back(aCrossingCheckContent);
					//	}
					//	else
					//	{
					//		break;
					//	}
					//}
					//else
					//{
					//	itrAfterTemp = itrAfter;
					//}


				}
			}
		}



		//	X列数を増減させる
		//CdAllOperationTableXColSpecCont aXColSpecCont = createXColSpecCont();
		//int iXCount = getCXDcdGrid()->getXColumnCount();
		//if (iXCount != aXColSpecCont.size())
		//{
			//フォント変更の場合、ヘッダー更新する必要があるので、全更新時は常に更新するようにする。
			OnCreate_Header();
		//}

		CdCrossingCheckYColSpecCont aCdEkiJikokuhyouYColSpecCont = createYColSpecCont();
		getCXDcdGrid()->setYColumnCount(
			aCdEkiJikokuhyouYColSpecCont.size());

			//	各セルに、データを設定

		for (int idx = 0; idx < pCentDedEki->getCrossingCheckRuleSize(); idx++)
		{
			CrossingCheckRule aCrossingCheckRule = pCentDedEki->getCrossingCheckRule(idx);
			{

				OnUpdate_setCrossingCheckRule_To_Column(
					idx,
					aCrossingCheckRule);
				for (int idx2 = 0; idx2 < (int)m_CrossingCheckContentCont[idx].size(); idx2++)
				{
					OnUpdate_setCrossingCheckContent_To_Column(
						idx,
						idx2,
						m_CrossingCheckContentCont[idx][idx2]);
				}
			}
		}

		// --------------------------------		
		//	罫線の色を設定
		// --------------------------------
		for (int idx = -1; idx < getCXDcdGrid()->getXColumnCount(); idx++)
		{
			CdPenProp aCdPenProp = 
				Ou<CDcdLine>(getCXDcdGrid()->getXBorder(idx)->getIfDcDraw())->getCdPenProp();
			aCdPenProp.setColor(createGridColorProp());

			Ou<CDcdLine>
				(getCXDcdGrid()->getXBorder(idx)->getIfDcDraw())
				->setCdPenProp(aCdPenProp);
		}

		for (int idx = -1; idx < getCXDcdGrid()->getYColumnCount(); idx++)
		{
			CdPenProp aCdPenProp =
				Ou<CDcdLine>(getCXDcdGrid()->getYBorder(idx)->getIfDcDraw())->getCdPenProp();
			aCdPenProp.setColor(createGridColorProp());

			Ou<CDcdLine>
				(getCXDcdGrid()->getYBorder(idx)->getIfDcDraw())
				->setCdPenProp(aCdPenProp);
		}

	}
	m_bUpdate_All_Requested = false ;
}

void CWndDcdGridCrossingCheck::OnCreate_Header()
{
	// --------------------------------
	//	交差支障チェックビューに使用するフォント
	// --------------------------------
	CdFontProp fontpropDefault = createFontProp();
	//CdColorProp colorpropDefault = createStringColorProp();

	CdCrossingCheckXColSpecCont aXColSpecCont = createXColSpecCont();
	// --------------------------------
	//	列の数を指定
	// --------------------------------

	getCXDcdGrid()->setXColumnCount(aXColSpecCont.size());
	getCXDcdGrid()->setXFixColumnCount(0);

	// --------------------------------
	//	列のサイズを設定
	// --------------------------------
	{
		CDcdTargetGetDC	aCDcdTarget(NULL);
		// --------------------------------
		//	X列
		// --------------------------------
		tstring strCellHeadwayWidth(_T("0000"));

		CdDedDispProp aCdDedDispProp =
			getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
		tstring strCellRessyaWidth(aCdDedDispProp.getJikokuhyouRessyaWidth(), '0');
		//tstring strCellRessyaWidth = _T("京都京");


		tstring strCellRessyaBangouWidth(
			getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp().getJikokuhyouRessyaWidth(), '0');
		if (strCellRessyaBangouWidth.length() < 8)
		{
			strCellRessyaBangouWidth = tstring(8, '0');
		}

		const CentDedRessyasyubetsuCont* pRessyasyubetsuCont = getCDiagramEditDoc()->getCDedRosenFileData()
			->getCentDedRosen()->getCentDedRessyasyubetsuCont();
		tstring strCellRessyasyubetsuWidth = _T("京都京都京都");
		for (int idxSyubetsu = 0; idxSyubetsu < pRessyasyubetsuCont->size(); idxSyubetsu++)
		{
			if (strCellRessyasyubetsuWidth.length() < pRessyasyubetsuCont->get(idxSyubetsu).getSyubetsumei().length())
			{
				strCellRessyasyubetsuWidth = pRessyasyubetsuCont->get(idxSyubetsu).getSyubetsumei();
			}
		}

		tstring strRessyahoukou = _T("0000");
		if (getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getKudariDiaAlias().length()
			> strRessyahoukou.length())
		{
			strRessyahoukou = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getKudariDiaAlias();
		}
		if (getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getNoboriDiaAlias().length()
			> strRessyahoukou.length())
		{
			strRessyahoukou = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getNoboriDiaAlias();
		}

		tstring strCellEkijikokuWidth(
			getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp().getJikokuhyouRessyaWidth(), '0');
		if (strCellEkijikokuWidth.length() < 8)
		{
			strCellEkijikokuWidth = tstring(8, '0');
		}

		tstring strCellEkimeiLength(
			getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp().getEkimeiLength() * 2, '0');

		{
			//	列車方向(前動作側)
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdCrossingCheckXColSpec(
				CdCrossingCheckXColSpec::EColumnType::ColumnType_BeforeRessyahoukou));
			CdDcdSizeXy	sizeRessyahoukou;
			CDcdTextbox	aCDcdTextbox(
				strRessyahoukou,
				fontpropDefault,
				_T(""), 1, 2, 2);
			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeRessyahoukou);
			getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeRessyahoukou.getX());
		}
		{
			//	列車番号(前動作側)
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdCrossingCheckXColSpec(
				CdCrossingCheckXColSpec::EColumnType::ColumnType_BeforeRessyabangou));
			CdDcdSizeXy	sizeRessyaBangou;
			CDcdTextbox	aCDcdTextbox(
				strCellRessyaBangouWidth,
				fontpropDefault,
				_T(""), 1, 2, 2);
			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeRessyaBangou);
			getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeRessyaBangou.getX());
		}
		{
			//	種別(前動作側)
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdCrossingCheckXColSpec(
				CdCrossingCheckXColSpec::EColumnType::ColumnType_BeforeRessyasyubetsu));
			CdDcdSizeXy	sizeRessyasyubetsu;
			CDcdTextbox	aCDcdTextbox(
				strCellRessyasyubetsuWidth,
				fontpropDefault,
				_T(""), 1, 2, 2);
			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeRessyasyubetsu);
			getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeRessyasyubetsu.getX());
		}
		{
			//	時刻(前動作側)
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdCrossingCheckXColSpec(
				CdCrossingCheckXColSpec::EColumnType::ColumnType_BeforeJikoku));
			CdDcdSizeXy	sizeEkijikoku;
			CDcdTextbox	aCDcdTextbox(
				strCellEkijikokuWidth,
				fontpropDefault,
				_T(""), 1, 2, 2);
			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeEkijikoku);
			getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeEkijikoku.getX());
		}
		{
			//	移動元番線
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdCrossingCheckXColSpec(
				CdCrossingCheckXColSpec::EColumnType::ColumnType_BeforeFrom));
			CdDcdSizeXy	sizeTrackContent;
			CDcdTextbox	aCDcdTextbox(
				strCellEkimeiLength,
				fontpropDefault,
				_T(""), 1, 2, 2);
			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeTrackContent);
			getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeTrackContent.getX());
		}
		{
			//	矢印
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdCrossingCheckXColSpec(
				CdCrossingCheckXColSpec::EColumnType::ColumnType_BeforeArrow));
			CdDcdSizeXy	sizeArrow;
			CDcdTextbox	aCDcdTextbox(
				_T("→"),
				fontpropDefault,
				_T(""), 1, 2, 2);
			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeArrow);
			getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeArrow.getX());
		}
		{
			//	移動先番線
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdCrossingCheckXColSpec(
				CdCrossingCheckXColSpec::EColumnType::ColumnType_BeforeTo));
			CdDcdSizeXy	sizeTrackContent;
			CDcdTextbox	aCDcdTextbox(
				strCellEkimeiLength,
				fontpropDefault,
				_T(""), 1, 2, 2);
			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeTrackContent);
			getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeTrackContent.getX());
		}

		{
			//	時隔
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdCrossingCheckXColSpec(
				CdCrossingCheckXColSpec::EColumnType::ColumnType_Headway));
			CdDcdSizeXy	sizeHeadway;
			CDcdTextbox	aCDcdTextbox(
				strCellHeadwayWidth,
				fontpropDefault,
				_T(""), 1, 2, 2);
			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeHeadway);
			getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeHeadway.getX());
		}

		{
			//	列車方向(後動作側)
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdCrossingCheckXColSpec(
				CdCrossingCheckXColSpec::EColumnType::ColumnType_AfterRessyahoukou));
			CdDcdSizeXy	sizeRessyahoukou;
			CDcdTextbox	aCDcdTextbox(
				strRessyahoukou,
				fontpropDefault,
				_T(""), 1, 2, 2);
			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeRessyahoukou);
			getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeRessyahoukou.getX());
		}
		{
			//	列車番号(後動作側)
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdCrossingCheckXColSpec(
				CdCrossingCheckXColSpec::EColumnType::ColumnType_AfterRessyabangou));
			CdDcdSizeXy	sizeRessyaBangou;
			CDcdTextbox	aCDcdTextbox(
				strCellRessyaBangouWidth,
				fontpropDefault,
				_T(""), 1, 2, 2);
			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeRessyaBangou);
			getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeRessyaBangou.getX());
		}
		{
			//	種別(後動作側)
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdCrossingCheckXColSpec(
				CdCrossingCheckXColSpec::EColumnType::ColumnType_AfterRessyasyubetsu));
			CdDcdSizeXy	sizeRessyasyubetsu;
			CDcdTextbox	aCDcdTextbox(
				strCellRessyasyubetsuWidth,
				fontpropDefault,
				_T(""), 1, 2, 2);
			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeRessyasyubetsu);
			getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeRessyasyubetsu.getX());
		}
		{
			//	時刻(後動作側)
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdCrossingCheckXColSpec(
				CdCrossingCheckXColSpec::EColumnType::ColumnType_AfterJikoku));
			CdDcdSizeXy	sizeEkijikoku;
			CDcdTextbox	aCDcdTextbox(
				strCellEkijikokuWidth,
				fontpropDefault,
				_T(""), 1, 2, 2);
			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeEkijikoku);
			getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeEkijikoku.getX());
		}
		{
			//	移動元番線
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdCrossingCheckXColSpec(
				CdCrossingCheckXColSpec::EColumnType::ColumnType_AfterFrom));
			CdDcdSizeXy	sizeTrackContent;
			CDcdTextbox	aCDcdTextbox(
				strCellEkimeiLength,
				fontpropDefault,
				_T(""), 1, 2, 2);
			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeTrackContent);
			getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeTrackContent.getX());
		}
		{
			//	矢印
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdCrossingCheckXColSpec(
				CdCrossingCheckXColSpec::EColumnType::ColumnType_AfterArrow));
			CdDcdSizeXy	sizeArrow;
			CDcdTextbox	aCDcdTextbox(
				_T("→"),
				fontpropDefault,
				_T(""), 1, 2, 2);
			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeArrow);
			getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeArrow.getX());
		}
		{
			//	移動先番線
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdCrossingCheckXColSpec(
				CdCrossingCheckXColSpec::EColumnType::ColumnType_AfterTo));
			CdDcdSizeXy	sizeTrackContent;
			CDcdTextbox	aCDcdTextbox(
				strCellEkimeiLength,
				fontpropDefault,
				_T(""), 1, 2, 2);
			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeTrackContent);
			getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeTrackContent.getX());
		}

		// --------------------------------
		//	Y列
		// --------------------------------
		{
			CdDcdSizeXy	sizeHeader;
			CDcdTextbox	aCDcdTextbox(
				_T("京都京"),
				fontpropDefault,
				_T(""), 1, 2, 2);
			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeHeader);

			getCXDcdGrid()->getYColumn(YCOLUMNNNO_HEADER)->setColumnSize(sizeHeader.getY());
		}
	}
	// --------------------------------
	//	最上列に属性とテキストを設定
	// --------------------------------
	{
		// 列車方向(前動作側)
		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdCrossingCheckXColSpec(
			CdCrossingCheckXColSpec::EColumnType::ColumnType_BeforeRessyahoukou));


		Ou<CDcdTextbox>	pCDcdTextbox =
			getCXDcdGrid()->getCell(iXColumnNumber, YCOLUMNNNO_HEADER)->getIfDcDraw();

		CConverter_WinGdi aCConverter_WinGdi;

		CdDrawTextProp	aCdDrawTextProp(
			fontpropDefault);
			//aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENUTEXT));
		CdBrushProp	aCdBrushProp(
			aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENU));

		pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
		pCDcdTextbox->setCdBrushProp(aCdBrushProp);
		pCDcdTextbox->setText(_T("前"));
		Ou<CDcdLine>
			(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())
			->setCdPenProp(getCdPenPropDotLine());
	}
	{
		// 列車番号(前動作側)
		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdCrossingCheckXColSpec(
			CdCrossingCheckXColSpec::EColumnType::ColumnType_BeforeRessyabangou));


		Ou<CDcdTextbox>	pCDcdTextbox =
			getCXDcdGrid()->getCell(iXColumnNumber, YCOLUMNNNO_HEADER)->getIfDcDraw();

		CConverter_WinGdi aCConverter_WinGdi;

		CdDrawTextProp	aCdDrawTextProp(
			fontpropDefault);
		//aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENUTEXT));
		CdBrushProp	aCdBrushProp(
			aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENU));

		pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
		pCDcdTextbox->setCdBrushProp(aCdBrushProp);
		pCDcdTextbox->setText(_T("列車番号"));
		Ou<CDcdLine>
			(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())
			->setCdPenProp(getCdPenPropDotLine());
	}
	{
		// 種別(前動作側)
		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdCrossingCheckXColSpec(
			CdCrossingCheckXColSpec::EColumnType::ColumnType_BeforeRessyasyubetsu));


		Ou<CDcdTextbox>	pCDcdTextbox =
			getCXDcdGrid()->getCell(iXColumnNumber, YCOLUMNNNO_HEADER)->getIfDcDraw();

		CConverter_WinGdi aCConverter_WinGdi;

		CdDrawTextProp	aCdDrawTextProp(
			fontpropDefault);
		//aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENUTEXT));
		CdBrushProp	aCdBrushProp(
			aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENU));

		pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
		pCDcdTextbox->setCdBrushProp(aCdBrushProp);
		pCDcdTextbox->setText(_T("種別"));
		Ou<CDcdLine>
			(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())
			->setCdPenProp(getCdPenPropDotLine());
	}
	{
		// 時刻(前動作側)
		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdCrossingCheckXColSpec(
			CdCrossingCheckXColSpec::EColumnType::ColumnType_BeforeJikoku));


		Ou<CDcdTextbox>	pCDcdTextbox =
			getCXDcdGrid()->getCell(iXColumnNumber, YCOLUMNNNO_HEADER)->getIfDcDraw();

		CConverter_WinGdi aCConverter_WinGdi;

		CdDrawTextProp	aCdDrawTextProp(
			fontpropDefault);
		//aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENUTEXT));
		CdBrushProp	aCdBrushProp(
			aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENU));

		pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
		pCDcdTextbox->setCdBrushProp(aCdBrushProp);
		pCDcdTextbox->setText(_T("時刻"));
		Ou<CDcdLine>
			(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())
			->setCdPenProp(getCdPenPropDotLine());
	}
	{
		// 移動元番線(前動作側)
		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdCrossingCheckXColSpec(
			CdCrossingCheckXColSpec::EColumnType::ColumnType_BeforeFrom));


		Ou<CDcdTextbox>	pCDcdTextbox =
			getCXDcdGrid()->getCell(iXColumnNumber, YCOLUMNNNO_HEADER)->getIfDcDraw();

		CConverter_WinGdi aCConverter_WinGdi;

		CdDrawTextProp	aCdDrawTextProp(
			fontpropDefault);
		//aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENUTEXT));
		CdBrushProp	aCdBrushProp(
			aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENU));

		pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
		pCDcdTextbox->setCdBrushProp(aCdBrushProp);
		pCDcdTextbox->setText(_T("前動作番線移動"));

		Ou<CDcdLine>
			(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())
			->setCdPenProp(getCdPenPropNullLine());
		Ou<CDcdLine>
			(getCXDcdGrid()->getXBorder(iXColumnNumber+1)->getIfDcDraw())
			->setCdPenProp(getCdPenPropNullLine());

		getCXDcdGrid()->getCell(iXColumnNumber, YCOLUMNNNO_HEADER)->setAttachCellCount(3, 1);
	}

	{
		// 時隔
		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdCrossingCheckXColSpec(
			CdCrossingCheckXColSpec::EColumnType::ColumnType_Headway));


		Ou<CDcdTextbox>	pCDcdTextbox =
			getCXDcdGrid()->getCell(iXColumnNumber, YCOLUMNNNO_HEADER)->getIfDcDraw();

		CConverter_WinGdi aCConverter_WinGdi;

		CdDrawTextProp	aCdDrawTextProp(
			fontpropDefault);
		//aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENUTEXT));
		CdBrushProp	aCdBrushProp(
			aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENU));

		pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
		pCDcdTextbox->setCdBrushProp(aCdBrushProp);
		pCDcdTextbox->setText(_T("時隔"));
	}

	{
		// 列車方向(後動作側)
		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdCrossingCheckXColSpec(
			CdCrossingCheckXColSpec::EColumnType::ColumnType_AfterRessyahoukou));


		Ou<CDcdTextbox>	pCDcdTextbox =
			getCXDcdGrid()->getCell(iXColumnNumber, YCOLUMNNNO_HEADER)->getIfDcDraw();

		CConverter_WinGdi aCConverter_WinGdi;

		CdDrawTextProp	aCdDrawTextProp(
			fontpropDefault);
		//aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENUTEXT));
		CdBrushProp	aCdBrushProp(
			aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENU));

		pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
		pCDcdTextbox->setCdBrushProp(aCdBrushProp);
		pCDcdTextbox->setText(_T("後"));
		Ou<CDcdLine>
			(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())
			->setCdPenProp(getCdPenPropDotLine());
	}
	{
		// 列車番号(後動作側)
		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdCrossingCheckXColSpec(
			CdCrossingCheckXColSpec::EColumnType::ColumnType_AfterRessyabangou));


		Ou<CDcdTextbox>	pCDcdTextbox =
			getCXDcdGrid()->getCell(iXColumnNumber, YCOLUMNNNO_HEADER)->getIfDcDraw();

		CConverter_WinGdi aCConverter_WinGdi;

		CdDrawTextProp	aCdDrawTextProp(
			fontpropDefault);
		//aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENUTEXT));
		CdBrushProp	aCdBrushProp(
			aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENU));

		pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
		pCDcdTextbox->setCdBrushProp(aCdBrushProp);
		pCDcdTextbox->setText(_T("列車番号"));
		Ou<CDcdLine>
			(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())
			->setCdPenProp(getCdPenPropDotLine());
	}
	{
		// 種別(後動作側)
		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdCrossingCheckXColSpec(
			CdCrossingCheckXColSpec::EColumnType::ColumnType_AfterRessyasyubetsu));


		Ou<CDcdTextbox>	pCDcdTextbox =
			getCXDcdGrid()->getCell(iXColumnNumber, YCOLUMNNNO_HEADER)->getIfDcDraw();

		CConverter_WinGdi aCConverter_WinGdi;

		CdDrawTextProp	aCdDrawTextProp(
			fontpropDefault);
		//aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENUTEXT));
		CdBrushProp	aCdBrushProp(
			aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENU));

		pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
		pCDcdTextbox->setCdBrushProp(aCdBrushProp);
		pCDcdTextbox->setText(_T("種別"));
		Ou<CDcdLine>
			(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())
			->setCdPenProp(getCdPenPropDotLine());
	}
	{
		// 時刻(後動作側)
		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdCrossingCheckXColSpec(
			CdCrossingCheckXColSpec::EColumnType::ColumnType_AfterJikoku));


		Ou<CDcdTextbox>	pCDcdTextbox =
			getCXDcdGrid()->getCell(iXColumnNumber, YCOLUMNNNO_HEADER)->getIfDcDraw();

		CConverter_WinGdi aCConverter_WinGdi;

		CdDrawTextProp	aCdDrawTextProp(
			fontpropDefault);
		//aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENUTEXT));
		CdBrushProp	aCdBrushProp(
			aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENU));

		pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
		pCDcdTextbox->setCdBrushProp(aCdBrushProp);
		pCDcdTextbox->setText(_T("時刻"));
		Ou<CDcdLine>
			(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())
			->setCdPenProp(getCdPenPropDotLine());
	}
	{
		// 移動元番線(前動作側)
		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdCrossingCheckXColSpec(
			CdCrossingCheckXColSpec::EColumnType::ColumnType_AfterFrom));


		Ou<CDcdTextbox>	pCDcdTextbox =
			getCXDcdGrid()->getCell(iXColumnNumber, YCOLUMNNNO_HEADER)->getIfDcDraw();

		CConverter_WinGdi aCConverter_WinGdi;

		CdDrawTextProp	aCdDrawTextProp(
			fontpropDefault);
		//aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENUTEXT));
		CdBrushProp	aCdBrushProp(
			aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENU));

		pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
		pCDcdTextbox->setCdBrushProp(aCdBrushProp);
		pCDcdTextbox->setText(_T("後動作番線移動"));

		Ou<CDcdLine>
			(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())
			->setCdPenProp(getCdPenPropNullLine());
		Ou<CDcdLine>
			(getCXDcdGrid()->getXBorder(iXColumnNumber + 1)->getIfDcDraw())
			->setCdPenProp(getCdPenPropNullLine());

		getCXDcdGrid()->getCell(iXColumnNumber, YCOLUMNNNO_HEADER)->setAttachCellCount(3, 1);
	}
}

	// --------------------------------
	//@name メニューコマンドの下請関数
	// --------------------------------

int CWndDcdGridCrossingCheck::OnCrossingCheckMovetojikokuhyou_Process(BOOL bQueryEnable)
{
	int iRv = 0;
	//if (iRv >= 0)
	//{
	//	if (getCentDedDia()->getWaitOperationUpdate())
	//	{
	//		iRv = -1;	//運用更新抑止状態です
	//	}
	//}
	CdCrossingCheckYColSpec aCdCrossingCheckYColSpec = getYColSpecOfFocus();
	CdCrossingCheckXColSpec aCdCrossingCheckXColSpec = getXColSpecOfFocus();
	if (iRv >= 0)
	{
		if (getCSelect()->getSelectedCellCount() == 0)
		{
			if (aCdCrossingCheckYColSpec.getColumnType() !=
				CdCrossingCheckYColSpec::EColumnType::ColumnType_Ressya)
			{
				iRv = -3;	//フォーカスが列車位置以外なら不可
			}
			else if (aCdCrossingCheckXColSpec.getColumnType() ==
				CdCrossingCheckXColSpec::EColumnType::ColumnType_Headway)
			{
				iRv = -4;
			}
		}
		else
		{
			iRv = -5; //複数選択は不可
		}

	}
	if (!bQueryEnable && iRv >= 0)
	{
		const CrossingCheckContent aCrossingCheckContent =
			m_CrossingCheckContentCont[aCdCrossingCheckYColSpec.getRuleIndex()][aCdCrossingCheckYColSpec.getRessyaIndex()];
		CdDedRessyaProperty aRessyaProperty;
		int iEkiIndex;
		if (aCdCrossingCheckXColSpec.getColumnType() < CdCrossingCheckXColSpec::EColumnType::ColumnType_Headway)
		{
			aRessyaProperty = aCrossingCheckContent.BeforeRessyaProperty;
			iEkiIndex = aCrossingCheckContent.iBeforeEkiIndex;
		}
		else
		{
			aRessyaProperty = aCrossingCheckContent.AfterRessyaProperty;
			iEkiIndex = aCrossingCheckContent.iAfterEkiIndex;
		}
		// --------------------------------
		//	時刻表ビューを開く
		// --------------------------------
		CJikokuhyouView* pCJikokuhyouView = NULL;
		if (iRv >= 0)
		{
			CJikokuhyouDoc* pCJikokuhyouDoc = NULL;
			if (iRv >= 0)
			{
				pCJikokuhyouDoc =
					getCDiagramEditApp()->openCJikokuhyouDoc(
						getCentDedDia(),
						aRessyaProperty.getRessyahoukou(),
						false,
						&pCJikokuhyouView);
				if (pCJikokuhyouView == NULL)
				{
					iRv = -11;	//	時刻表ビューのオープンに失敗しました
				}
			}
			//pCJikokuhyouDoc = 時刻表ドキュメント
			//pCJikokuhyouView = 時刻表ビュー
		}

		if (iRv >= 0)
		{
			//CentDedRessya aCentDedRessya = getCentDedRessyaCont(eRessyahoukou)->get(iRessyaidx);
			//int iEkiIndex = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
			//	->getCentDedEkiCont()->EkiIndexOfEkiID(GetDocument()->getEkiID());
			pCJikokuhyouView->setFocusToRessyaIndex(aRessyaProperty.getRessyaIndex(),
				getCentDedDia()->getCentDedRessyaCont(aRessyaProperty.getRessyahoukou())
				->EkiOrderOfEkiIndex(iEkiIndex));
			iRv = 1;	//	時刻表ビューへ移動しました
		}
	}
	return iRv;
}

int CWndDcdGridCrossingCheck::OnCrossingCheckMovetodiagram_Process(BOOL bQueryEnable)
{
	int iRv = 0;
	//if (iRv >= 0)
	//{
	//	if (getCentDedDia()->getWaitOperationUpdate())
	//	{
	//		iRv = -1;	//運用更新抑止状態です
	//	}
	//}
	CdCrossingCheckYColSpec aCdCrossingCheckYColSpec = getYColSpecOfFocus();
	CdCrossingCheckXColSpec aCdCrossingCheckXColSpec = getXColSpecOfFocus();
	if (iRv >= 0)
	{
		if (getCSelect()->getSelectedCellCount() == 0)
		{
			if (aCdCrossingCheckYColSpec.getColumnType() !=
				CdCrossingCheckYColSpec::EColumnType::ColumnType_Ressya)
			{
				iRv = -3;	//フォーカスが列車位置以外なら不可
			}
			else if (aCdCrossingCheckXColSpec.getColumnType() ==
				CdCrossingCheckXColSpec::EColumnType::ColumnType_Headway)
			{
				iRv = -4;
			}
		}
		else
		{
			iRv = -5; //複数選択は不可
		}

	}
	if (!bQueryEnable && iRv >= 0)
	{
		const CrossingCheckContent aCrossingCheckContent =
			m_CrossingCheckContentCont[aCdCrossingCheckYColSpec.getRuleIndex()][aCdCrossingCheckYColSpec.getRessyaIndex()];
		CdDedRessyaProperty aRessyaProperty;
		int iEkiIndex;
		if (aCdCrossingCheckXColSpec.getColumnType() < CdCrossingCheckXColSpec::EColumnType::ColumnType_Headway)
		{
			aRessyaProperty = aCrossingCheckContent.BeforeRessyaProperty;
			iEkiIndex = aCrossingCheckContent.iBeforeEkiIndex;
		}
		else
		{
			aRessyaProperty = aCrossingCheckContent.AfterRessyaProperty;
			iEkiIndex = aCrossingCheckContent.iAfterEkiIndex;
		}
		// --------------------------------
		//	ダイヤグラムビューを開く
		// --------------------------------
		CDedDiagramView* pCDedDiagramView = NULL;
		if (iRv >= 0) {

			const CDedDiagramDoc* pCDedDiagramDoc = NULL;
			if (iRv >= 0) {
				pCDedDiagramDoc =
					getCDiagramEditApp()->openCDedDiagramDoc(
						getCentDedDia());
				if (pCDedDiagramDoc == NULL) {
					iRv = -11;	//	ダイヤグラムビューのオープンに失敗しました
				}
			}
			//pCDedDiagramDoc = ダイヤグラムドキュメント
			//	ビューがアクティブになっています。

			if (iRv >= 0) {
				POSITION aPOSITION = pCDedDiagramDoc->GetFirstViewPosition();
				if (aPOSITION != NULL) {
					pCDedDiagramView = (CDedDiagramView*)pCDedDiagramDoc->GetNextView(aPOSITION);
				}
				if (pCDedDiagramView == NULL) {
					iRv = -4;	//	ダイヤグラムビューのオープンに失敗しました
				}
			}
		}
		//pCDedDiagramView = ダイヤグラムビュー
		if (iRv >= 0) {
		//	pCDedDiagramView->setZone_Dgr(aRessyaProperty.getJikoku(),
		//		iEkiIndex, aRessyaProperty.getRessyahoukou() == ERessyahoukou::Ressyahoukou_Nobori);
			pCDedDiagramView->setZoneCenter_Dgr(aRessyaProperty.getJikoku(),
				iEkiIndex);
		}
	}
	return iRv;
}

// ********************************
//	コンストラクタ
// ********************************
CWndDcdGridCrossingCheck::CWndDcdGridCrossingCheck()
	: m_bUpdate_All_Requested( false )
	, m_bInitialUpdateComplete(false)
{
	//getCSelect()->setSelectMode( CSelect::SelectMode_YColumn ) ;
	getCSelect()->setSelectMode(CSelect::SelectMode_NONE);
}
CWndDcdGridCrossingCheck::‾CWndDcdGridCrossingCheck()
{
}

// ********************************
//@name	CDcdGrid
// ********************************

// ********************************
//@name	CWndDcdGrid
// ********************************

	// ********************************
	//@name CWndDcdGridCrossingCheck-操作
	// ********************************

CCrossingCheckDoc * CWndDcdGridCrossingCheck::GetDocument()
{
	CView* pCView = (CView*)GetParent();
	return (CCrossingCheckDoc*)pCView->GetDocument();
}

const CentDedDia*	CWndDcdGridCrossingCheck::getCentDedDia()
{
	const CentDedRosen*	pCentDedRosen =
		getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen();
	int iDiaIndex = pCentDedRosen->getCentDedDiaCont()->findCentDedDiaByName(
		GetDocument()->getDiaName());
	if (iDiaIndex < 0) {
		return (NULL);
	}
	const CentDedDia* pCentDedDia = pCentDedRosen->getCentDedDiaCont()->getMuPtr()->get(iDiaIndex);
	return (pCentDedDia);
};

const CentDedRessyaCont*	CWndDcdGridCrossingCheck::getCentDedRessyaCont(
	ERessyahoukou eRessyahoukou)
{
	const CentDedDia* pCentDedDia = getCentDedDia();
	if (pCentDedDia == NULL) {
		return (NULL);
	}
	return (pCentDedDia->getCentDedRessyaCont(eRessyahoukou));
};

// ----------------------------------------------------------------
//	MFC
// ----------------------------------------------------------------
BEGIN_MESSAGE_MAP(CWndDcdGridCrossingCheck,CWndDcdGridCrossingCheck::super)
	//{{AFX_MSG_MAP(CWndDcdGridCrossingCheck)
	ON_WM_CREATE()
	ON_WM_KEYUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KEYDOWN()
	ON_WM_HSCROLL()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_CrossingCheck_MoveToJikokuhyou, &CWndDcdGridCrossingCheck::OnCrossingCheckMovetojikokuhyou)
	ON_UPDATE_COMMAND_UI(ID_CrossingCheck_MoveToJikokuhyou, &CWndDcdGridCrossingCheck::OnUpdateCrossingCheckMovetojikokuhyou)
	ON_COMMAND(ID_CrossingCheck_MoveToDiagram, &CWndDcdGridCrossingCheck::OnCrossingCheckMovetodiagram)
	ON_UPDATE_COMMAND_UI(ID_CrossingCheck_MoveToDiagram, &CWndDcdGridCrossingCheck::OnUpdateCrossingCheckMovetodiagram)
END_MESSAGE_MAP()

int CWndDcdGridCrossingCheck::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (super::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	//// --------------------------------
	////	列車種別ビューに使用するフォント
	//// --------------------------------
	//CdFontProp fontpropDefault = createFontProp() ;
	//CdOperationTableXColSSpecCont = createXColSpecCont();
	//// --------------------------------
	////	列の数を指定
	//// --------------------------------

	//getCXDcdGrid()->setXColumnCount(aXColSpecCont.size()) ;
	getCXDcdGrid()->setYColumnCount(YCOLUMNNNO_OPERATION_0);
	getCXDcdGrid()->setYFixColumnCount(YCOLUMNNNO_OPERATION_0);
	OnCreate_Header();


	// --------------------------------
	//	フォーカスセルの初期位置を設定
	// --------------------------------
	getCFocus()->setFocusCell( getCXDcdGrid()->getCell( 0 , YCOLUMNNNO_OPERATION_0) ) ;
	// --------------------------------
	//	表示更新
	// --------------------------------
	InvalidateGrid() ;

	
	return 0;
}




void CWndDcdGridCrossingCheck::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	if (lHint == LHINT_SUBVIEW_TO_ROOTDOC)
	{
		return;
	}
	// --------------------------------

	// --------------------------------
	//	初回のOnUpdate()
	//	.iniファイルからプロパティを読み込み
	// --------------------------------
	if (!m_bInitialUpdateComplete)
	{
		//getCDiagramEditApp()->readCWndDcdGridCrossingCheckProp(this);
		//CdDedDispProp aCdDedDispProp =
		//	getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
		//m_iSecondRound = aCdDedDispProp.getSecondRoundHatsu();
		// --------------------------------
		m_bInitialUpdateComplete = true;
	}

	//pHint= 
	//	pHintが CRfEditCmdHolder オブジェクトなら、
	//	対応する編集コマンド CRfEditCmd を保持しています。
	//	この場合、this は CRfEditCmd の内容に最適化した
	//	更新を行います。
	//	NULLなら、全更新が要求されています。
	if (m_bUpdate_All_Requested)
	{
		//	全更新が保留されている場合は、
		//	その後はコマンドによる最適化された単体のいかなる更新要求に対しても、全更新を行います。
		pHint = NULL;
	}


	Ou<CRfEditCmd> pCmd;
	if (pHint != NULL && pHint->IsKindOf(RUNTIME_CLASS(CRfEditCmdHolder)))
	{

		CRfEditCmdHolder* pHolder =
			(CRfEditCmdHolder*)pHint;
		pCmd = pHolder->getCmd();
	}

	//
	//	
	//	
	//if ( pCmd != NULL )
	//{
	//	if ( dynamic_castOu<CRfEditCmd_Comment>( pCmd ) || 
	//		dynamic_castOu<CRfEditCmd_DiaProp>(pCmd) ||
	//		dynamic_castOu<CRfEditCmd_RessyasyubetsuSwap>( pCmd ))
	//	{
	//		//	このビューは、
	//		//		コメントの変更
	//		//		ダイヤの変更
	//		//		ダイヤの属性の変更
	//		//		駅番線の変更
	//		//		駅番線の入換
	//		//		列車種別の入換
	//		//	の場合は、更新を行いません。
	//	}
	//	else if (dynamic_castOu<CRfEditCmd_Ressya>(pCmd))
	//	{
	//		const CentDedRosen*	pCentDedRosen =
	//			getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen();
	//		int iDiaIndex = pCentDedRosen->getCentDedDiaCont()->findCentDedDiaByName(
	//			GetDocument()->getDiaName());
	//		Ou<CRfEditCmd_Ressya>	pCommand =
	//			dynamic_castOu<CRfEditCmd_Ressya>(pCmd);
	//		if (pCommand->getDiaIndex() == iDiaIndex && !pCommand->getWaitOperationConnect())
	//		{
	//			pHint = NULL;
	//		}
	//	}
	//	else if (dynamic_castOu<CRfEditCmd_Operation>(pCmd))
	//	{
	//		const CentDedRosen*	pCentDedRosen =
	//			getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen();
	//		int iDiaIndex = pCentDedRosen->getCentDedDiaCont()->findCentDedDiaByName(
	//			GetDocument()->getDiaName());
	//		Ou<CRfEditCmd_Operation>	pCommand =
	//			dynamic_castOu<CRfEditCmd_Operation>(pCmd);
	//		if (pCommand->getDiaIndex() == iDiaIndex)
	//		{
	//			pHint = NULL;
	//		}
	//	}
	//	else
	//	{
	//		//CRfEditCmd_DedRosenFileDataProp
	//		//	  路線ファイルのプロパティの変更は、
	//		//	フォントの変化を伴うため、全更新が必要です。
	//		//CRfEditCmd_Eki
	//		//CRfEditCmd_RessyaSyubetsu
	//		//CRfEditCmd_Rosen
	//		//CRfEditCmd_RosenFileData
	//		//CRfEditCmd_Dia
	//		//	列車種別を包含するオブジェクトです。これが更新された場合は、
	//		//	全更新が必要です。
	//		pHint = NULL ;
	//	}
	//}
	if ( pHint == NULL )
	{
		// --------------------------------		
		//	全要素を更新
		// --------------------------------
		CView *pView = getCDiagramEditApp()->getCMainFrame()->
			getMDIChildActiveView() ;

		//CdDedDispProp aCdDedDispProp =
		//	getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
		//m_iSecondRound = aCdDedDispProp.getSecondRoundHatsu();

		CCrossingCheckDoc* pCCrossingCheckDoc = (CCrossingCheckDoc*)GetDocument();

		if ( GetParent() == pView )
		{
			OnUpdate_All() ;
		}
		else
		{
			LogMsg(_T("CWndDcdGridCrossingCheck::OnUpdate()")
				_T("m_bUpdate_All_Requested=true") ) ;
			m_bUpdate_All_Requested = true ;
		}
	}
	
	//int iYColumnBegin = createYColSpecCont().ColumnNumberFromSpec( 
	//	CdCrossingCheckYColSpec(CdCrossingCheckYColSpec::EColumnType::ColumnType_Caption, 0 ) ) ;
	//
	//getCSelect()->setColumnNumberSelectLimit(
	//	CdDcdZoneXy( 
	//		CdDcdZone( 0 , INT_MAX ) ,
	//		CdDcdZone( iYColumnBegin , getCentDedDia()->getcontOperationTableContent().size())
	//	) );

}

void CWndDcdGridCrossingCheck::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	LogMsg(_T("CWndDcdGridCrossingCheck::OnActivateView(%d,,)") , bActivate ) ;
	
	if ( bActivate && m_bUpdate_All_Requested )
	{
		OnUpdate_All() ;
	}
}

void CWndDcdGridCrossingCheck::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CMenu	aMenu ;
	aMenu.LoadMenu( IDR_MENU_CROSSINGCHECK_CONTEXT ) ;
	CMenu* pContextMenu = aMenu.GetSubMenu( 0 ) ;

	//	コンテキストメニューがマウス以外で呼び出された場合は、
	//	コンテキストメニューの表示位置は、フォーカスセルの中央の位置とします。
	if ( point.x ==-1 || point.y == -1 )
	{
		//	コンテキストメニューがマウス以外で呼び出されました
		CdDcdPosXy posxyFocusCellColumnNumber = getCFocus()->getFocusCellColumnNumber() ;
		if ( posxyFocusCellColumnNumber !=  
				CFocus::ColumnNumberPosXy_NULL() )
		{
			CdDcdZoneXy	zonexyFocusCell = getCellZone( 
				posxyFocusCellColumnNumber.getX() , 
				posxyFocusCellColumnNumber.getY() ) ;
			point.x = zonexyFocusCell.getX().getPos() + zonexyFocusCell.getX().getSize() / 2 ;
			point.y = zonexyFocusCell.getY().getPos() + zonexyFocusCell.getY().getSize() / 2 ;
			ClientToScreen( &point ) ;
		}
	}
	//point = コンテキストメニューの表示位置。
	//	-1の場合は、コンテキストメニューは表示できません。

	if ( point.x >= 0 &&  point.y >= 0 )
	{
		pContextMenu->TrackPopupMenu( 
			TPM_LEFTALIGN | TPM_RIGHTBUTTON ,
			point.x , point.y , 
			AfxGetMainWnd() ) ;	//	this を指定すると、App→Doc→View の
								//コマンドチェーンが動作しません。
	}
	else
	{
		super::OnContextMenu(pWnd, point);
	}
}

void CWndDcdGridCrossingCheck::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	OnCrossingCheckMovetojikokuhyou_Process(FALSE);
}

void CWndDcdGridCrossingCheck::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	int iRv = 0;

	//if (iRv >= 0 && CKeyinputSenderToModalDlg::AnyLetterOrDigitKeyIsDown())
	//{

	//	if (iRv >= 0)
	//	{
	//		if (getCentDedDia()->getWaitOperationUpdate())
	//		{
	//			iRv = -1;	//運用更新抑止状態です
	//		}
	//	}
	//	CdAllOperationTableYColSpec aCdAllOperationTableYColSpec = getYColSpecOfFocus();
	//	if (iRv >= 0)
	//	{
	//		if (getCSelect()->getSelectedCellCount() == 0)
	//		{
	//			if (aCdAllOperationTableYColSpec.getColumnType() !=
	//				CdAllOperationTableYColSpec::ColumnType_Operation)
	//			{
	//				iRv = -2;	//フォーカスが列車位置以外なら不可
	//			}
	//		}
	//		else
	//		{
	//			iRv = -1; //複数選択は不可
	//		}
	//	}

	//	//if (iRv >= 0)
	//	//{
	//	//	auto itr = m_ListOperationTableContent->begin();
	//	//	for (int idx = 0; idx < aCdOperationTableYColSpec.getOperationTableContentIndex(); idx++)
	//	//	{
	//	//		itr++;
	//	//	}
	//	//	ERessyahoukou eRessyahoukou = itr->aRessyaProperty.getRessyahoukou();
	//	//	int iRessyaidx = itr->aRessyaProperty.getRessyaIndex();
	//	//	// --------------------------------
	//	//	//	時刻表ビューを開く
	//	//	// --------------------------------
	//	//	CJikokuhyouView* pCJikokuhyouView = NULL;
	//	//	if (iRv >= 0)
	//	//	{
	//	//		CJikokuhyouDoc* pCJikokuhyouDoc = NULL;
	//	//		if (iRv >= 0)
	//	//		{
	//	//			pCJikokuhyouDoc =
	//	//				getCDiagramEditApp()->openCJikokuhyouDoc(
	//	//					getCentDedDia(),
	//	//					eRessyahoukou,
	//	//					false,
	//	//					&pCJikokuhyouView);
	//	//			if (pCJikokuhyouView == NULL)
	//	//			{
	//	//				iRv = -3;	//	時刻表ビューのオープンに失敗しました
	//	//			}
	//	//		}
	//	//		//pCJikokuhyouDoc = 時刻表ドキュメント
	//	//		//pCJikokuhyouView = 時刻表ビュー
	//	//	}

	//	//	if (iRv >= 0)
	//	//	{

	//	//		CdOperationTableXColSpec aCdOperationTableXColSpec = getXColSpecOfFocus();
	//	//		if (aCdOperationTableXColSpec.getColumnType() ==
	//	//			CdOperationTableXColSpec::ColumnType_Ressyabangou)
	//	//		{
	//	//			pCJikokuhyouView->openCDlgRessyaPropKeyDown(iRessyaidx, 1, nChar, nRepCnt, nFlags);
	//	//		}
	//	//		else if (aCdOperationTableXColSpec.getColumnType() ==
	//	//			CdOperationTableXColSpec::ColumnType_Ressyasyubetsu)
	//	//		{
	//	//			pCJikokuhyouView->openCDlgRessyaPropKeyDown(iRessyaidx, 2, nChar, nRepCnt, nFlags);
	//	//		}
	//	//		else if (aCdOperationTableXColSpec.getColumnType() ==
	//	//			CdOperationTableXColSpec::ColumnType_Ressyamei)
	//	//		{
	//	//			pCJikokuhyouView->openCDlgRessyaPropKeyDown(iRessyaidx, 3, nChar, nRepCnt, nFlags);
	//	//		}
	//	//		else if (aCdOperationTableXColSpec.getColumnType() ==
	//	//			CdOperationTableXColSpec::ColumnType_OriginSideEkimei ||
	//	//			aCdOperationTableXColSpec.getColumnType() ==
	//	//			CdOperationTableXColSpec::ColumnType_OriginSideEkijikoku)
	//	//		{
	//	//			CentDedRessya aCentDedRessya = getCentDedRessyaCont(eRessyahoukou)->get(iRessyaidx);
	//	//			if (eRessyahoukou == ERessyahoukou::Ressyahoukou_Kudari ||
	//	//				getDisplayNoboriLeftToRight())
	//	//			{
	//	//				pCJikokuhyouView->openCDlgEkijikokuPropKeyDown(iRessyaidx, aCentDedRessya.getValidSihatsuEki(), true, nChar, nRepCnt, nFlags);
	//	//			}
	//	//			else
	//	//			{
	//	//				pCJikokuhyouView->openCDlgEkijikokuPropKeyDown(iRessyaidx, aCentDedRessya.getValidSyuuchakuEki(), false, nChar, nRepCnt, nFlags);
	//	//			}
	//	//		}
	//	//		else if (aCdOperationTableXColSpec.getColumnType() ==
	//	//			CdOperationTableXColSpec::ColumnType_TerminalSideEkimei ||
	//	//			aCdOperationTableXColSpec.getColumnType() ==
	//	//			CdOperationTableXColSpec::ColumnType_TerminalSideEkijikoku)
	//	//		{
	//	//			CentDedRessya aCentDedRessya = getCentDedRessyaCont(eRessyahoukou)->get(iRessyaidx);
	//	//			if (eRessyahoukou == ERessyahoukou::Ressyahoukou_Kudari ||
	//	//				getDisplayNoboriLeftToRight())
	//	//			{
	//	//				pCJikokuhyouView->openCDlgEkijikokuPropKeyDown(iRessyaidx, aCentDedRessya.getValidSyuuchakuEki(), false, nChar, nRepCnt, nFlags);
	//	//			}
	//	//			else
	//	//			{
	//	//				pCJikokuhyouView->openCDlgEkijikokuPropKeyDown(iRessyaidx, aCentDedRessya.getValidSihatsuEki(), true, nChar, nRepCnt, nFlags);
	//	//			}
	//	//		}
	//	//		else
	//	//		{
	//	//			CentDedRessya aCentDedRessya = getCentDedRessyaCont(eRessyahoukou)->get(iRessyaidx);
	//	//			pCJikokuhyouView->setFocusToRessyaIndex(iRessyaidx, aCentDedRessya.getValidSihatsuEki());
	//	//		}
	//	//		iRv = 1;	//	時刻表ビューへ移動しました
	//	//	}
	//	//}

	//}
	//else
	//{
		//if (!m_CKeyinputSenderToModalDlg.OnKeyDown(nChar, nRepCnt, nFlags))
		//{
		super::OnKeyDown(nChar, nRepCnt, nFlags);
		//}
	//}
}

//void CWndDcdGridCrossingCheck::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
//{
//	//OnCreate_Header();
//	CdEkiJikokuhyouXColSpecCont aXColSpecCont = createXColSpecCont();
//	int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdEkiJikokuhyouXColSpec(
//		CdEkiJikokuhyouXColSpec::EColumnType::ColumnType_Hour));
//	InvalidateCell(iXColumnNumber, YCOLUMNNNO_HEADER);
//	super::OnHScroll(nSBCode, nPos, pScrollBar);
//}

//void CWndDcdGridCrossingCheck::OnAllOperationtableProp()
//{
//	// TODO: ここにコマンド ハンドラー コードを追加します。
//	OnAllOperationTableProp_Process(FALSE);
//}
//
//
//void CWndDcdGridCrossingCheck::OnUpdateAllOperationtableProp(CCmdUI* pCmdUI)
//{
//	// TODO:ここにコマンド更新 UI ハンドラー コードを追加します。
//	pCmdUI->Enable(OnAllOperationTableProp_Process(TRUE) >= 0);
//}



void CWndDcdGridCrossingCheck::OnCrossingCheckMovetojikokuhyou()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	OnCrossingCheckMovetojikokuhyou_Process(FALSE);
}


void CWndDcdGridCrossingCheck::OnUpdateCrossingCheckMovetojikokuhyou(CCmdUI *pCmdUI)
{
	// TODO:ここにコマンド更新 UI ハンドラー コードを追加します。
	pCmdUI->Enable(OnCrossingCheckMovetojikokuhyou_Process(TRUE) >= 0);
}


void CWndDcdGridCrossingCheck::OnCrossingCheckMovetodiagram()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	OnCrossingCheckMovetodiagram_Process(FALSE);
}


void CWndDcdGridCrossingCheck::OnUpdateCrossingCheckMovetodiagram(CCmdUI *pCmdUI)
{
	// TODO:ここにコマンド更新 UI ハンドラー コードを追加します。
	pCmdUI->Enable(OnCrossingCheckMovetodiagram_Process(TRUE) >= 0);
}

} //namespace ViewEkiJikokuhyou