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
/*
// ****************************************************************
//	CWndDcdGridEkiJikokuhyou.cpp
//	$Id: CWndDcdGridEkiJikokuhyou.cpp  $
// ****************************************************************
*/
/** @file */
#include "stdafx.h"

#include "logmsg\LogMsg.h"
#include "NsOu\OuNew.h"
#include "NsOu\dynamic_castOu.h"
#include "str\strtoint.h"
#include "DcDraw\CDcdTargetGetDC.h"
#include "DcDraw\CConverter_WinGdi.h"
#include "MfcUtil/MfcUtil.h"
#include "Str/strToWstr.h"
#include "DcDraw\CDcdLine.h"
#include "str\strprintf.h"

#include "..\resource.h"
#include "..\entDed\CentDedRosen.h"
#include "..\entDed\CentDedDia.h"
#include "..\DiagramEdit.h"
#include "..\CRfEditCmdHolder.h"
#include "..\DedRosenFileData\EditCmd\EditCmd.h"
#include "CWndDcdGridEkiJikokuhyou.h"
#include "EkiJikokuhyouColSpec\EkiJikokuhyouColSpec.h"
//#include "CDlgOperationTableCsvExport.h"
//#include "CDlgEkiJikokuhyouProp.h"
//#include "..\ViewOperationTable\COperationTableView.h"
#include "..\ViewDiagram\cdeddiagramview.h"
#include "CconvEkiJikokuhyouCsv.h"
#include "str\CsvDocument\CconvCsvDocument.h"
#include "str\vectorToFile.h"


// ****************************************************************
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
// ****************************************************************

namespace ViewEkiJikokuhyou {
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
	return aCdDedDispProp.getJikokuhyouFont(0);
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
CdEkiJikokuhyouXColSpecCont
CWndDcdGridEkiJikokuhyou::createXColSpecCont()
{
	CdEkiJikokuhyouXColSpecCont aSpecCont(
		m_iMaxRessyaCount);
	return aSpecCont ;
}

CdEkiJikokuhyouYColSpecCont
CWndDcdGridEkiJikokuhyou::createYColSpecCont()
{
	CdEkiJikokuhyouYColSpecCont aSpecCont(
		m_iFirstHour,
		m_iHourCount,
		m_bDisplayTrack);
	return aSpecCont ;
}

CdEkiJikokuhyouXColSpec
CWndDcdGridEkiJikokuhyou::getXColSpecOfFocus()
{
	CdEkiJikokuhyouXColSpec aSpec ;
	CdDcdPosXy aPos = getCFocus()->getFocusCellColumnNumber() ;
	if ( aPos != getCFocus()->ColumnNumberPosXy_NULL() )
	{
		CdEkiJikokuhyouXColSpecCont aSpecCont(
			m_iMaxRessyaCount);
		aSpec = aSpecCont.ColumnNumberToSpec(aPos.getX());
	}
	return aSpec ;
}

CdEkiJikokuhyouYColSpec
CWndDcdGridEkiJikokuhyou::getYColSpecOfFocus()
{
	CdEkiJikokuhyouYColSpec aSpec ;
	CdDcdPosXy aPos = getCFocus()->getFocusCellColumnNumber() ;
	if ( aPos != getCFocus()->ColumnNumberPosXy_NULL() )
	{
		CdEkiJikokuhyouYColSpecCont aSpecCont(
			m_iFirstHour,
			m_iHourCount,
			m_bDisplayTrack);
		aSpec = aSpecCont.ColumnNumberToSpec( aPos.getY() ) ;
	}
	return aSpec ;
}
	
	// --------------------------------
	//@name OnUpdate の下請関数
	// --------------------------------

//const CdDedJikoku::CConv
//CWndDcdGridEkiJikokuhyou::getCdDedJikokuConv()const
//{
//	//if (m_bDisplaySecondEkiJikoku)
//	//{
//	//	if (m_bDisplayColonEkiJikoku)
//	//	{
//	//		static CdDedJikoku::CConv aConv(
//	//			false,		//	コロン有
//	//						// 時が 00 から 09 の場合、10の位の "0" をスペースにします。
//	//			CdDedJikoku::CConv::EHour_ZeroToSpace,
//	//			CdDedJikoku::CConv::ESecond_Output 	// 秒を表示します
//	//		);
//	//		return aConv;
//	//	}
//	//	else
//	//	{
//	//		static CdDedJikoku::CConv aConv(
//	//			true,		//	コロン無
//	//						// 時が 00 から 09 の場合、10の位の "0" をスペースにします。
//	//			CdDedJikoku::CConv::EHour_ZeroToSpace,
//	//			CdDedJikoku::CConv::ESecond_Output 	// 秒を表示します
//	//		);
//	//		return aConv;
//	//	}
//	//}
//	//else
//	//{
//	//	if (m_bDisplayColonEkiJikoku)
//	//	{
//	//		static CdDedJikoku::CConv aConv(
//	//			false,		//	コロン有
//	//						// 時が 00 から 09 の場合、10の位の "0" をスペースにします。
//	//			CdDedJikoku::CConv::EHour_ZeroToSpace,
//	//			CdDedJikoku::CConv::ESecond_NoSecond 	// 秒を常に出力しません。
//	//		);
//	//		return aConv;
//	//	}
//	//	else
//	//	{
//	//		static CdDedJikoku::CConv aConv(
//	//			true,		//	コロン無
//	//						// 時が 00 から 09 の場合、10の位の "0" をスペースにします。
//	//			CdDedJikoku::CConv::EHour_ZeroToSpace,
//	//			CdDedJikoku::CConv::ESecond_NoSecond 	// 秒を常に出力しません。
//	//		);
//	//		return aConv;
//	//	}
//	//}
//
//	CdDedJikoku::CConv::ESecond eSecond = CdDedJikoku::CConv::ESecond_NoSecond;
//	if (m_bDisplaySecondEkiJikoku)
//	{
//		eSecond = CdDedJikoku::CConv::ESecond_Output;
//	}
//
//	CdDedJikoku::CConv aConv(
//		!m_bDisplayColonEkiJikoku,
//		CdDedJikoku::CConv::EHour_ZeroToSpace,
//		eSecond,
//		(CdDedJikoku::CConv::ESecondRound)m_iSecondRoundChaku,
//		(CdDedJikoku::CConv::ESecondRound)m_iSecondRoundHatsu,
//		m_bDisplay2400
//	);
//	return aConv;
//}

void CWndDcdGridEkiJikokuhyou::OnUpdate_setEkiJikokuhyouContent_To_Column(
	int iHour ,
	const list<EkiJikokuhyouContent>& ListEkiJikokuhyouContent)
{
	//const Mu<const CentDedRessya*>* pCentDedRessyaConts[2];
	//for (int iRessyahoukou = Ressyahoukou_Kudari;
	//	iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
	//{
	//	pCentDedRessyaConts[iRessyahoukou] = getCentDedRessyaCont((ERessyahoukou)iRessyahoukou)->getMuPtr();
	//}


	CdFontProp fontpropDefault = createFontProp() ;
	CdColorProp colorpropDefault = createStringColorProp();
	CdEkiJikokuhyouYColSpecCont aYColSpecCont = createYColSpecCont();

	int iYColumnNumber = createYColSpecCont().ColumnNumberFromSpec(
		CdEkiJikokuhyouYColSpec(CdEkiJikokuhyouYColSpec::EColumnType::ColumnType_RessyaSyubetsu, iHour));

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
		getCXDcdGrid()->getYColumn(iYColumnNumber + 1)->setColumnSize(sizeRessya.getY());
		getCXDcdGrid()->getYColumn(iYColumnNumber + 2)->setColumnSize(sizeRessya.getY());
		if (m_bDisplayTrack)
		{
			getCXDcdGrid()->getYColumn(iYColumnNumber + 3)->setColumnSize(sizeRessya.getY());
		}

		Ou<CDcdLine>
			(getCXDcdGrid()->getYBorder(iYColumnNumber)->getIfDcDraw())
			->setCdPenProp(getCdPenPropNullLine());
		Ou<CDcdLine>
			(getCXDcdGrid()->getYBorder(iYColumnNumber+1)->getIfDcDraw())
			->setCdPenProp(getCdPenPropNullLine());
		if (m_bDisplayTrack)
		{
			Ou<CDcdLine>
				(getCXDcdGrid()->getYBorder(iYColumnNumber + 2)->getIfDcDraw())
				->setCdPenProp(getCdPenPropNullLine());
			Ou<CDcdLine>
				(getCXDcdGrid()->getYBorder(iYColumnNumber + 3)->getIfDcDraw())
				->setCdPenProp(getCdPenPropNarrowLine());
		}
		else
		{
			Ou<CDcdLine>
				(getCXDcdGrid()->getYBorder(iYColumnNumber + 2)->getIfDcDraw())
				->setCdPenProp(getCdPenPropNarrowLine());

		}
	}


	// --------------------------------
	//	属性を設定
	// --------------------------------
	const Mu<CentDedEkiCont::CdDedEki>* pCdDedEkiConts[2];
	for (int iRessyahoukou = Ressyahoukou_Kudari;
		iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
	{
		pCdDedEkiConts[iRessyahoukou] =
			getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont()->getMuPtr((ERessyahoukou)iRessyahoukou);
	}

	const CentDedRessyasyubetsuCont* pCentDedRessyasyubetsuCont =
		getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedRessyasyubetsuCont();

	const CentDedEkiCont* pCentDedEkiCont = getCDiagramEditDoc()->
		getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont();
	int iEkiIndex = pCentDedEkiCont->EkiIndexOfEkiID(GetDocument()->getEkiID());
	int iEkiOrder = pCentDedEkiCont->EkiOrderOfEkiIndex(GetDocument()->getRessyahoukou(),iEkiIndex);
	const CentDedEkiCont::CdDedEki aCdDedEki = 
		pCdDedEkiConts[(int)GetDocument()->getRessyahoukou()]->get(iEkiOrder);
	const CentDedEkiTrack2Cont aCentDedEkiTrack2Cont = aCdDedEki.getCentDedEkiTrack2Cont();

	//const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont(
	//	GetDocument()->getRessyahoukou());

	//const OperationTableContent aOperationTableContentOut = ListOperationTableContent.front();
	//const OperationTableContent aOperationTableContentIn = ListOperationTableContent.back();

	//const CentDedRessya* pCentDedRessyaIn =
	//	pCentDedRessyaConts[aOperationTableContentIn.aRessyaProperty.getRessyahoukou()]
	//	->get(aOperationTableContentIn.aRessyaProperty.getRessyaIndex());

	//const CentDedRessyasyubetsu* pCentDedRessyasyubetsuOut = pCentDedRessyasyubetsuCont
	//	->getMuPtr()->get(pCentDedRessyaOut->getRessyasyubetsuIndex());
	//if (m_bDisplayParentSyubetsu && pCentDedRessyasyubetsuOut->getParentSyubetsuIndex() >= 0)
	//{
	//	pCentDedRessyasyubetsuOut = pCentDedRessyasyubetsuCont
	//		->getMuPtr()->get(pCentDedRessyasyubetsuOut->getParentSyubetsuIndex());
	//}
	//const CentDedRessyasyubetsu* pCentDedRessyasyubetsuIn = pCentDedRessyasyubetsuCont
	//	->getMuPtr()->get(pCentDedRessyaIn->getRessyasyubetsuIndex());
	//if (m_bDisplayParentSyubetsu && pCentDedRessyasyubetsuIn->getParentSyubetsuIndex() >= 0)
	//{
	//	pCentDedRessyasyubetsuIn = pCentDedRessyasyubetsuCont
	//		->getMuPtr()->get(pCentDedRessyasyubetsuIn->getParentSyubetsuIndex());
	//}

	tstring strRessya = _T("京都京");

	CdEkiJikokuhyouXColSpecCont aCdEkiJikokuhyouXColSpecCont = createXColSpecCont();

	{
		//	時
		int iXColumnNumber = aCdEkiJikokuhyouXColSpecCont.ColumnNumberFromSpec(
			CdEkiJikokuhyouXColSpec(CdEkiJikokuhyouXColSpec::EColumnType::ColumnType_Hour));
		Ou<CDcdTextbox> pCDcdTextbox =
			getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
		pCDcdTextbox->
			setText(to_tstring(iHour));

		//	フォント属性
		CdDrawTextProp	aCdDrawTextProp =
			pCDcdTextbox->getCdDrawTextProp();
		aCdDrawTextProp.setCdFontProp(fontpropDefault);
		aCdDrawTextProp.setTextColor(colorpropDefault);
		aCdDrawTextProp.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
		pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);

		if (m_bDisplayTrack)
		{
			getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->setAttachCellCount(1, 4);
		}
		else
		{
			getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->setAttachCellCount(1, 3);
		}

		//	セルを無効化
		InvalidateCell(iXColumnNumber, iYColumnNumber);
	}

	int iRessyaIndex = 0;
	for (auto itr = ListEkiJikokuhyouContent.begin(); 
		itr != ListEkiJikokuhyouContent.end(); itr++,iRessyaIndex++)
	{
		int iXColumnNumber = aCdEkiJikokuhyouXColSpecCont.ColumnNumberFromSpec(
			CdEkiJikokuhyouXColSpec(CdEkiJikokuhyouXColSpec::EColumnType::ColumnType_Ressya, iRessyaIndex));

		const CentDedRessyasyubetsu* pCentDedRessyasyubetsu = pCentDedRessyasyubetsuCont
			->getMuPtr()->get(itr->iRessyaSyubetsu);
		if (m_bDisplayParentSyubetsu && pCentDedRessyasyubetsu->getParentSyubetsuIndex() >= 0)
		{
			pCentDedRessyasyubetsu = pCentDedRessyasyubetsuCont
				->getMuPtr()->get(pCentDedRessyasyubetsu->getParentSyubetsuIndex());
		}
		if (itr->iMinute >= 0)
		{
			{
				//	列車種別
				Ou<CDcdTextbox> pCDcdTextbox =
					getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();

				//種別のテキスト
				pCDcdTextbox->setText(pCentDedRessyasyubetsu->getRyakusyou());

				//種別のフォント属性
				CdDrawTextProp	aCdDrawTextProp =
					pCDcdTextbox->getCdDrawTextProp();
				aCdDrawTextProp.setCdFontProp(fontpropDefault);
				aCdDrawTextProp.setTextColor(pCentDedRessyasyubetsu->getJikokuhyouMojiColor());

				int idxFont = pCentDedRessyasyubetsu->getJikokuhyouFontIndex();
				aCdDrawTextProp.setCdFontProp(
					getCDiagramEditDoc()->getCDedRosenFileData()
					->getCdDedDispProp().getJikokuhyouFont(idxFont));
				aCdDrawTextProp.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
				pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);

				//	セルを無効化
				InvalidateCell(iXColumnNumber, iYColumnNumber);
			}
			{
				//	発時刻
				Ou<CDcdTextbox> pCDcdTextbox =
					getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber + 1)->getIfDcDraw();
				tstring strTemp =_T("");
				if (getDisplayIsShihatsu() && itr->bIsShihatsu)
				{
					strTemp += _T("●");
				}
				strTemp += strprintf(_T("%02d"), itr->iMinute);
				pCDcdTextbox->setText(strTemp);

				//種別のフォント属性
				CdDrawTextProp	aCdDrawTextProp =
					pCDcdTextbox->getCdDrawTextProp();
				aCdDrawTextProp.setCdFontProp(fontpropDefault);
				aCdDrawTextProp.setTextColor(pCentDedRessyasyubetsu->getJikokuhyouMojiColor());

				int idxFont = pCentDedRessyasyubetsu->getJikokuhyouFontIndex();
				aCdDrawTextProp.setCdFontProp(
					getCDiagramEditDoc()->getCDedRosenFileData()
					->getCdDedDispProp().getJikokuhyouFont(idxFont));
				aCdDrawTextProp.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
				pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);

				//	セルを無効化
				InvalidateCell(iXColumnNumber, iYColumnNumber + 1);
			}
			{
				//	行き先駅名
				Ou<CDcdTextbox> pCDcdTextbox =
					getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber + 2)->getIfDcDraw();

				tstring strEkimei;
				if (itr->iSyuuchakuEkiOrder == -1)
				{
					CString strTemp;
					strTemp.LoadString(IDS_WORD_EkiJikokuhyou_Loop);
					strEkimei = (LPCTSTR)strTemp;

				}
				else if (itr->iSyuuchakuEkiOrder == -2)
				{
					CString strTemp;
					strTemp.LoadString(IDS_WORD_EkiJikokuhyou_ForLoop);
					strEkimei = (LPCTSTR)strTemp;

				}
				else if (itr->iOuterShuchakuekiIndex != INT_MIN)
				{
					int iOuterTerminalIndex = itr->iOuterShuchakuekiIndex;
					//strEkimei = pCdDedEkiConts[GetDocument()->getRessyahoukou()]
					//	->get(itr->iSyuuchakuEkiOrder).getOuterTerminalEkimei(iOuterTerminalIndex);
					strEkimei = pCdDedEkiConts[GetDocument()->getRessyahoukou()]
						->get(itr->iSyuuchakuEkiOrder).getOuterTerminalJikokuRyaku(iOuterTerminalIndex, true);
				}
				else
				{
					//strEkimei = pCdDedEkiConts[GetDocument()->getRessyahoukou()]
					//	->get(itr->iSyuuchakuEkiOrder).getEkimei();
					strEkimei = pCdDedEkiConts[GetDocument()->getRessyahoukou()]
						->get(itr->iSyuuchakuEkiOrder).getEkimeiJikokuhyouRyaku(true);
				}
				pCDcdTextbox->setText(strEkimei);

				//	フォント属性
				CdDrawTextProp	aCdDrawTextProp =
					pCDcdTextbox->getCdDrawTextProp();
				aCdDrawTextProp.setCdFontProp(fontpropDefault);
				aCdDrawTextProp.setTextColor(pCentDedRessyasyubetsu->getJikokuhyouMojiColor());

				aCdDrawTextProp.setCdFontProp(
					getCDiagramEditDoc()->getCDedRosenFileData()
					->getCdDedDispProp().getJikokuhyouFont(0));
				aCdDrawTextProp.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
				pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);

				//	セルを無効化
				InvalidateCell(iXColumnNumber, iYColumnNumber + 2);
			}
			if(m_bDisplayTrack)
			{
				//	列車番線
				Ou<CDcdTextbox> pCDcdTextbox =
					getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber + 3)->getIfDcDraw();

				tstring strTrackName = aCentDedEkiTrack2Cont.get(
					itr->iRessyaTrackIndex).getTrackRyakusyou(GetDocument()->getRessyahoukou());
				pCDcdTextbox->setText(strTrackName);

				//	フォント属性
				CdDrawTextProp	aCdDrawTextProp =
					pCDcdTextbox->getCdDrawTextProp();
				aCdDrawTextProp.setCdFontProp(fontpropDefault);
				aCdDrawTextProp.setTextColor(pCentDedRessyasyubetsu->getJikokuhyouMojiColor());

				aCdDrawTextProp.setCdFontProp(
					getCDiagramEditDoc()->getCDedRosenFileData()
					->getCdDedDispProp().getJikokuhyouFont(0));
				aCdDrawTextProp.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
				pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);

				//	セルを無効化
				InvalidateCell(iXColumnNumber, iYColumnNumber + 3);
			}
		}
		else
		{
			{
				//	種別変更駅名
				Ou<CDcdTextbox> pCDcdTextbox =
					getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();

				tstring strEkimei = pCdDedEkiConts[GetDocument()->getRessyahoukou()]
						->get(itr->iSyuuchakuEkiOrder).getEkimeiJikokuhyouRyaku(true);
				pCDcdTextbox->setText(strEkimei);

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
				//	"から"
				Ou<CDcdTextbox> pCDcdTextbox =
					getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber + 1)->getIfDcDraw();

				CString strTemp;
				strTemp.LoadString(IDS_WORD_ClassChange_From);
				pCDcdTextbox->setText((LPCTSTR)strTemp);

				//	フォント属性
				CdDrawTextProp	aCdDrawTextProp =
					pCDcdTextbox->getCdDrawTextProp();
				aCdDrawTextProp.setCdFontProp(fontpropDefault);
				aCdDrawTextProp.setTextColor(colorpropDefault);
				aCdDrawTextProp.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
				pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);

				//	セルを無効化
				InvalidateCell(iXColumnNumber, iYColumnNumber + 1);
			}
			{
				//	列車種別
				Ou<CDcdTextbox> pCDcdTextbox =
					getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber + 2)->getIfDcDraw();

				//種別のテキスト
				pCDcdTextbox->setText(pCentDedRessyasyubetsu->getRyakusyou());

				//種別のフォント属性
				CdDrawTextProp	aCdDrawTextProp =
					pCDcdTextbox->getCdDrawTextProp();
				aCdDrawTextProp.setCdFontProp(fontpropDefault);
				aCdDrawTextProp.setTextColor(pCentDedRessyasyubetsu->getJikokuhyouMojiColor());

				int idxFont = pCentDedRessyasyubetsu->getJikokuhyouFontIndex();
				aCdDrawTextProp.setCdFontProp(
					getCDiagramEditDoc()->getCDedRosenFileData()
					->getCdDedDispProp().getJikokuhyouFont(idxFont));
				aCdDrawTextProp.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
				pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);

				//	セルを無効化
				InvalidateCell(iXColumnNumber, iYColumnNumber + 2);
			}
			if (m_bDisplayTrack)
			{
				//	列車番線
				Ou<CDcdTextbox> pCDcdTextbox =
					getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber + 3)->getIfDcDraw();

				//テキスト
				pCDcdTextbox->setText(_T(""));

				//	セルを無効化
				InvalidateCell(iXColumnNumber, iYColumnNumber + 3);
			}
		}
	}
	/**
		列車本数がMaxRessyaCountよりも小さい場合は、空白スペースを埋めます。
	*/
	for (; iRessyaIndex < m_iMaxRessyaCount; iRessyaIndex++)
	{
		int iXColumnNumber = aCdEkiJikokuhyouXColSpecCont.ColumnNumberFromSpec(
			CdEkiJikokuhyouXColSpec(CdEkiJikokuhyouXColSpec::EColumnType::ColumnType_Ressya, iRessyaIndex));
		{
			//	列車種別
			Ou<CDcdTextbox> pCDcdTextbox =
				getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();

			//テキスト
			pCDcdTextbox->setText(_T(""));

			//	セルを無効化
			InvalidateCell(iXColumnNumber, iYColumnNumber);
		}
		{
			//	発時刻
			Ou<CDcdTextbox> pCDcdTextbox =
				getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber + 1)->getIfDcDraw();

			//テキスト
			pCDcdTextbox->setText(_T(""));

			//	セルを無効化
			InvalidateCell(iXColumnNumber, iYColumnNumber + 1);
		}
		{
			//	行き先駅名
			Ou<CDcdTextbox> pCDcdTextbox =
				getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber + 2)->getIfDcDraw();

			//テキスト
			pCDcdTextbox->setText(_T(""));

			//	セルを無効化
			InvalidateCell(iXColumnNumber, iYColumnNumber + 2);
		}
		if (m_bDisplayTrack)
		{
			//	列車番線
			Ou<CDcdTextbox> pCDcdTextbox =
				getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber + 3)->getIfDcDraw();

			//テキスト
			pCDcdTextbox->setText(_T(""));

			//	セルを無効化
			InvalidateCell(iXColumnNumber, iYColumnNumber + 3);
		}
	}
}

void CWndDcdGridEkiJikokuhyou::OnUpdate_setEmptyEkiJikokuhyouContent_To_Column(int iHour)
{
	CdFontProp fontpropDefault = createFontProp(); 
	int iYColumnNumber = createYColSpecCont().ColumnNumberFromSpec(
		CdEkiJikokuhyouYColSpec(CdEkiJikokuhyouYColSpec::EColumnType::ColumnType_RessyaSyubetsu, iHour));

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
		getCXDcdGrid()->getYColumn(iYColumnNumber + 1)->setColumnSize(sizeRessya.getY());
		getCXDcdGrid()->getYColumn(iYColumnNumber + 2)->setColumnSize(sizeRessya.getY());
		if (m_bDisplayTrack)
		{
			getCXDcdGrid()->getYColumn(iYColumnNumber + 3)->setColumnSize(sizeRessya.getY());
		}

		Ou<CDcdLine>
			(getCXDcdGrid()->getYBorder(iYColumnNumber)->getIfDcDraw())
			->setCdPenProp(getCdPenPropNullLine());
		Ou<CDcdLine>
			(getCXDcdGrid()->getYBorder(iYColumnNumber + 1)->getIfDcDraw())
			->setCdPenProp(getCdPenPropNullLine());
		if (m_bDisplayTrack)
		{
			Ou<CDcdLine>
				(getCXDcdGrid()->getYBorder(iYColumnNumber + 2)->getIfDcDraw())
				->setCdPenProp(getCdPenPropNullLine());
			Ou<CDcdLine>
				(getCXDcdGrid()->getYBorder(iYColumnNumber + 3)->getIfDcDraw())
				->setCdPenProp(getCdPenPropNarrowLine());
		}
		else
		{
			Ou<CDcdLine>
				(getCXDcdGrid()->getYBorder(iYColumnNumber + 2)->getIfDcDraw())
				->setCdPenProp(getCdPenPropNarrowLine());

		}
	}
	// --------------------------------
	//	属性を設定
	// --------------------------------
	CdEkiJikokuhyouXColSpecCont aCdEkiJikokuhyouXColSpecCont = createXColSpecCont();
	{
		//	時
		int iXColumnNumber = aCdEkiJikokuhyouXColSpecCont.ColumnNumberFromSpec(
			CdEkiJikokuhyouXColSpec(CdEkiJikokuhyouXColSpec::EColumnType::ColumnType_Hour));
		Ou<CDcdTextbox> pCDcdTextbox =
			getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
		pCDcdTextbox->
			setText(to_tstring(iHour));

		//	フォント属性
		CdDrawTextProp	aCdDrawTextProp =
			pCDcdTextbox->getCdDrawTextProp();
		aCdDrawTextProp.setCdFontProp(fontpropDefault);
		aCdDrawTextProp.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
		pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);

		if (m_bDisplayTrack)
		{
			getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->setAttachCellCount(1, 4);
		}
		else
		{
			getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->setAttachCellCount(1, 3);
		}

		//	セルを無効化
		InvalidateCell(iXColumnNumber, iYColumnNumber);
	}
	for (int iRessyaIndex = 0; iRessyaIndex < m_iMaxRessyaCount; iRessyaIndex++)
	{
		int iXColumnNumber = aCdEkiJikokuhyouXColSpecCont.ColumnNumberFromSpec(
			CdEkiJikokuhyouXColSpec(CdEkiJikokuhyouXColSpec::EColumnType::ColumnType_Ressya, iRessyaIndex));
		{
			//	列車種別
			Ou<CDcdTextbox> pCDcdTextbox =
				getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();

			//テキスト
			pCDcdTextbox->setText(_T(""));

			//	セルを無効化
			InvalidateCell(iXColumnNumber, iYColumnNumber);
		}
		{
			//	発時刻
			Ou<CDcdTextbox> pCDcdTextbox =
				getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber + 1)->getIfDcDraw();

			//テキスト
			pCDcdTextbox->setText(_T(""));

			//	セルを無効化
			InvalidateCell(iXColumnNumber, iYColumnNumber + 1);
		}
		{
			//	行き先駅名
			Ou<CDcdTextbox> pCDcdTextbox =
				getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber + 2)->getIfDcDraw();

			//テキスト
			pCDcdTextbox->setText(_T(""));

			//	セルを無効化
			InvalidateCell(iXColumnNumber, iYColumnNumber + 2);
		}
		if (m_bDisplayTrack)
		{
			//	列車番線
			Ou<CDcdTextbox> pCDcdTextbox =
				getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber + 3)->getIfDcDraw();

			//テキスト
			pCDcdTextbox->setText(_T(""));

			//	セルを無効化
			InvalidateCell(iXColumnNumber, iYColumnNumber + 3);
		}
	}

}


void  CWndDcdGridEkiJikokuhyou::OnUpdate_All()
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

		int iEnableOperation = getCDiagramEditDoc()->
			getCDedRosenFileData()->getCentDedRosen()->getEnableOperation();
		const Mu<const CentDedRessya*>* pCentDedRessyaConts[2];
		for (int iRessyahoukou = Ressyahoukou_Kudari;
			iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
		{
			pCentDedRessyaConts[iRessyahoukou] = getCentDedRessyaCont((ERessyahoukou)iRessyahoukou)->getMuPtr();
		}
		const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont(
			GetDocument()->getRessyahoukou());

		unordered_map<tstring, list<OperationTableContent>> contOperationTableContent =
			getCentDedDia()->getcontOperationTableContent();

		const CentDedEkiCont* pCentDedEkiCont = getCDiagramEditDoc()->
			getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont();
		//const Mu<const CentDedRessya*>* pCentDedRessyaConts[2];
		//for (int iRessyahoukou = Ressyahoukou_Kudari;
		//	iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
		//{
		//	pCentDedRessyaConts[iRessyahoukou] = getCentDedRessyaCont((ERessyahoukou)iRessyahoukou)->getMuPtr();
		//}
		const CdDedJikoku KitenJikoku = getCDiagramEditDoc()->getCDedRosenFileData()
			->getCentDedRosen()->getKitenJikoku();
		CdDedJikoku::CConv::ESecondRound eSecondRound = (CdDedJikoku::CConv::ESecondRound)m_iSecondRound;

		/**
			iEkiOrder->iEkiIndex対応表(分岐・環状対応)
			下り・上りの2方面×駅数のコンテナ
			[iEkiOrder][iRessyahoukou]でアクセスすると、contRessyaExistに対応するiEkiIndexを返します
			また、分岐環状駅については、iEkiIndexLoop[0]駅に集約します。従って、上り列車の場合はiEkiOrderLoop.back()に当たります
		*/
		vector<vector<int>> iEkiOrderTable;
		iEkiOrderTable.resize(pCentDedEkiCont->size());

		for (int iEki = 0; iEki < pCentDedEkiCont->size(); iEki++)
		{
			const CentDedEki aEki = pCentDedEkiCont->get(iEki);

			if (aEki.getBrunchLoopPosition() == -1)
			{
				iEkiOrderTable[iEki].insert(iEkiOrderTable[iEki].begin(), iEki);
				iEkiOrderTable[pCentDedEkiCont->size() - 1 - iEki].push_back(iEki);
			}
			else
			{
				deque<int> iEkiIndexLoop = aEki.getEkiIndexLoop();
				iEkiOrderTable[iEki].insert(iEkiOrderTable[iEki].begin(), iEkiIndexLoop[0]);
				iEkiOrderTable[pCentDedEkiCont->size() - 1 - iEki].push_back(iEkiIndexLoop[0]);
			}
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

		m_contListEkiJikokuhyouContent.clear();
		m_iFirstHour = INT_MIN;
		m_iHourCount = INT_MIN;
		m_iMaxRessyaCount = 0;

		//int iEkiOrder = pCentDedRessyaCont->EkiOrderOfEkiIndex(GetDocument()->getEkiIndex());
		int iEkiIndex = pCentDedEkiCont->EkiIndexOfEkiID(GetDocument()->getEkiID());
		int iEkiOrder = pCentDedRessyaCont->EkiOrderOfEkiIndex(iEkiIndex);

		//この駅と、分岐駅・環状線設定で関連付けられた駅のIndexです。環状列車判定に用います
		deque<int> iEkiIndexBrunchLoop;
		pCentDedEkiCont->getEkiIndexBrunchLoop(iEkiIndex, iEkiIndexBrunchLoop);

		const CentDedRessyasyubetsuCont* pCentDedRessyasyubetsuCont =
			getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedRessyasyubetsuCont();

		vector<bool> contHidden;
		contHidden.assign(pCentDedRessyasyubetsuCont->size(), false);
		if (!getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getDisableHiddenSyubetsu())
		{
			for (int iRessyaSyubetsuIndex = 0; iRessyaSyubetsuIndex < pCentDedRessyasyubetsuCont->size(); iRessyaSyubetsuIndex++)
			{
				contHidden[iRessyaSyubetsuIndex] = pCentDedRessyasyubetsuCont->get(iRessyaSyubetsuIndex).getHidden();
			}
		}

		for (int iRessyaIndex = 0; iRessyaIndex < pCentDedRessyaCont->size(); iRessyaIndex++)
		{
			const CentDedRessya* pCentDedRessya = pCentDedRessyaCont->getMuPtr()->get(iRessyaIndex);
			if (pCentDedRessya->isCanceled())
			{
				continue;
			}
			if (contHidden[pCentDedRessya->getRessyasyubetsuIndex()])
			{
				continue;
			}

			if (pCentDedRessya->getCentDedEkiJikoku(iEkiOrder).getEkiatsukai() != CentDedEkiJikoku::Ekiatsukai_Teisya ||
				pCentDedRessya->getCentDedEkiJikoku(iEkiOrder).getHatsujikoku().isNull())
			{
				continue;
			}
			if (!pCentDedRessya->isRunBetweenNextEki(iEkiOrder))
			{
				continue;
			}
			if (iEnableOperation == 0)
			{
				int iSyuuchakuEkiOrder = pCentDedRessya->getValidSyuuchakuEki();
				if (iSyuuchakuEkiOrder == -1)
				{
					continue;
				}
				EkiJikokuhyouContent aEkiJikokuhyouContent;
				aEkiJikokuhyouContent.iRessyaSyubetsu = pCentDedRessya->getRessyasyubetsuIndex();
				CdDedJikoku aHatsuJikoku = pCentDedRessya->getCentDedEkiJikoku(iEkiOrder).getVirtualHatsujikoku();
				//CdDedJikoku aHatsuJikoku = pCentDedRessya->getCentDedEkiJikoku(iEkiOrder).getHatsujikoku();
				aHatsuJikoku.round(eSecondRound);
				aEkiJikokuhyouContent.iMinute = aHatsuJikoku.getMinute();

				aEkiJikokuhyouContent.iRessyaTrackIndex = pCentDedRessya->getCentDedEkiJikoku(iEkiOrder).getRessyaTrackIndex();

				aEkiJikokuhyouContent.iSyuuchakuEkiOrder = iSyuuchakuEkiOrder;
				const CentDedAfterOperation aLastOperation = pCentDedRessya->getLastOperation();
				if (aLastOperation.getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
				{
					aEkiJikokuhyouContent.iOuterShuchakuekiIndex = aLastOperation.getOuterShuchakuekiIndex();
				}
				aEkiJikokuhyouContent.aRessyaProperty = 
					CdDedRessyaProperty(GetDocument()->getRessyahoukou(), iRessyaIndex);

				bool bIsShihatsu = pCentDedRessya->getValidSihatsuEki() == iEkiOrder;
				if (bIsShihatsu)
				{
					if (pCentDedRessya->getFirstOperation().getBOperation()== CentDedBeforeOperation::EBOperation::BOperation_Outer)
					{
						bIsShihatsu = false;
					}
				}
				aEkiJikokuhyouContent.bIsShihatsu = bIsShihatsu;

				if (m_contListEkiJikokuhyouContent.find(aHatsuJikoku.getHour()) == m_contListEkiJikokuhyouContent.end())
				{
					m_contListEkiJikokuhyouContent[aHatsuJikoku.getHour()] = list<EkiJikokuhyouContent>(1, aEkiJikokuhyouContent);
				}
				else
				{
					list<EkiJikokuhyouContent>& ListEkiJikokuhyouContent =
						m_contListEkiJikokuhyouContent[aHatsuJikoku.getHour()];
					bool bInsert = false;
					for (auto itr = ListEkiJikokuhyouContent.begin(); itr != ListEkiJikokuhyouContent.end(); itr++)
					{
						if (aEkiJikokuhyouContent.iMinute >= itr->iMinute)
						{
							continue;
						}
						ListEkiJikokuhyouContent.insert(itr, aEkiJikokuhyouContent);
						bInsert = true;
						break;
					}
					if (!bInsert)
					{
						ListEkiJikokuhyouContent.push_back(aEkiJikokuhyouContent);
					}
				}

				//パターンダイヤプレビュー機能対応、上記の作業を、パターンダイヤの範囲分繰り返す
				if (m_iPatternDiagramPreviewCycleSecond > 0)
				{
					for (int iShiftSecond = m_iPatternDiagramPreviewCycleSecond; iShiftSecond <= m_iPatternDiagramPreviewRange; iShiftSecond += m_iPatternDiagramPreviewCycleSecond)
					{
						CdDedJikoku aHatsuJikokuTemp = aHatsuJikoku;
						aHatsuJikokuTemp.addSeconds(iShiftSecond);

						aEkiJikokuhyouContent.iMinute = aHatsuJikokuTemp.getMinute();

						if (m_contListEkiJikokuhyouContent.find(aHatsuJikokuTemp.getHour()) == m_contListEkiJikokuhyouContent.end())
						{
							m_contListEkiJikokuhyouContent[aHatsuJikokuTemp.getHour()] = list<EkiJikokuhyouContent>(1, aEkiJikokuhyouContent);
						}
						else
						{
							list<EkiJikokuhyouContent>& ListEkiJikokuhyouContent =
								m_contListEkiJikokuhyouContent[aHatsuJikokuTemp.getHour()];
							bool bInsert = false;
							for (auto itr = ListEkiJikokuhyouContent.begin(); itr != ListEkiJikokuhyouContent.end(); itr++)
							{
								if (aEkiJikokuhyouContent.iMinute >= itr->iMinute)
								{
									continue;
								}
								ListEkiJikokuhyouContent.insert(itr, aEkiJikokuhyouContent);
								bInsert = true;
								break;
							}
							if (!bInsert)
							{
								ListEkiJikokuhyouContent.push_back(aEkiJikokuhyouContent);
							}
						}
						
						aHatsuJikokuTemp = aHatsuJikoku;
						aHatsuJikokuTemp.addSeconds(-iShiftSecond);

						aEkiJikokuhyouContent.iMinute = aHatsuJikokuTemp.getMinute();

						if (m_contListEkiJikokuhyouContent.find(aHatsuJikokuTemp.getHour()) == m_contListEkiJikokuhyouContent.end())
						{
							m_contListEkiJikokuhyouContent[aHatsuJikokuTemp.getHour()] = list<EkiJikokuhyouContent>(1, aEkiJikokuhyouContent);
						}
						else
						{
							list<EkiJikokuhyouContent>& ListEkiJikokuhyouContent =
								m_contListEkiJikokuhyouContent[aHatsuJikokuTemp.getHour()];
							bool bInsert = false;
							for (auto itr = ListEkiJikokuhyouContent.begin(); itr != ListEkiJikokuhyouContent.end(); itr++)
							{
								if (aEkiJikokuhyouContent.iMinute >= itr->iMinute)
								{
									continue;
								}
								ListEkiJikokuhyouContent.insert(itr, aEkiJikokuhyouContent);
								bInsert = true;
								break;
							}
							if (!bInsert)
							{
								ListEkiJikokuhyouContent.push_back(aEkiJikokuhyouContent);
							}
						}
					}
				}

			}
			else if (iEnableOperation == 1 || m_iPatternDiagramPreviewCycleSecond != 0)
			{
				int iSyuuchakuEkiOrder = pCentDedRessya->getValidSyuuchakuEki();
				if (iSyuuchakuEkiOrder == -1)
				{
					continue;
				}
				EkiJikokuhyouContent aEkiJikokuhyouContent;
				list<EkiJikokuhyouContent> ListEkiJikokuhyouContentTemp;
				aEkiJikokuhyouContent.iRessyaSyubetsu = pCentDedRessya->getRessyasyubetsuIndex();
				CdDedJikoku aHatsuJikoku = pCentDedRessya->getCentDedEkiJikoku(iEkiOrder).getVirtualHatsujikoku();
				//CdDedJikoku aHatsuJikoku = pCentDedRessya->getCentDedEkiJikoku(iEkiOrder).getHatsujikoku();
				aHatsuJikoku.round(eSecondRound);
				aEkiJikokuhyouContent.iMinute = aHatsuJikoku.getMinute();

				aEkiJikokuhyouContent.iRessyaTrackIndex = pCentDedRessya->getCentDedEkiJikoku(iEkiOrder).getRessyaTrackIndex();

				//簡易モード時の終着駅は、カスタマイズ時刻表で同じ列にまとめて表示するもののみを考慮する
				//簡易モードの場合の始発駅判定は、有効始発駅かつ路線外始発ではないかつ、この列車がCustomizeJikokuhyouContentのiRessyaIndexContの先頭にあることです。
				bool bIsShihatsu = pCentDedRessya->getValidSihatsuEki() == iEkiOrder;
				if (bIsShihatsu)
				{
					if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
					{
						bIsShihatsu = false;
					}
				}
				const vector<CustomizeJikokuhyouContent>& contCustomizeJikokuhyouContent =
					getCentDedDia()->getcontCustomizeRessyaIndex(GetDocument()->getRessyahoukou());
				bool bFound = false;
				for (int iCustomizeJikokuhyouContent = 0; iCustomizeJikokuhyouContent < (int)contCustomizeJikokuhyouContent.size() && !bFound; iCustomizeJikokuhyouContent++)
				{
					const CustomizeJikokuhyouContent& aCustomizeJikokuhyouContent = contCustomizeJikokuhyouContent[iCustomizeJikokuhyouContent];
					if (aCustomizeJikokuhyouContent.iRessyaIndexCont.empty())
					{
						continue;
					}
					for (int idx = 0; idx < (int)aCustomizeJikokuhyouContent.iRessyaIndexCont.size() && !bFound; idx++)
					{
						if (aCustomizeJikokuhyouContent.iRessyaIndexCont[idx] == iRessyaIndex)
						{
							if (idx == 0)
							{
								//先頭にある場合は、bIsShihatsuがそのまま入ります
								aEkiJikokuhyouContent.bIsShihatsu = bIsShihatsu;
							}
							else
							{
								//先頭以外の場合は、無条件でfalseになります
								aEkiJikokuhyouContent.bIsShihatsu = false;
							}
							
							if (idx == aCustomizeJikokuhyouContent.iRessyaIndexCont.size() - 1)
							{
								//iRessyaIndexContの末尾にある場合(size1で先頭にある場合を含む)は、この列車の行き先がそのまま使われます。

								aEkiJikokuhyouContent.iSyuuchakuEkiOrder = iSyuuchakuEkiOrder;
								const CentDedAfterOperation aLastOperation = pCentDedRessya->getLastOperation();
								if (aLastOperation.getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
								{
									aEkiJikokuhyouContent.iOuterShuchakuekiIndex = aLastOperation.getOuterShuchakuekiIndex();
								}
							}
							else
							{
								//この列車よりも後ろに列車がある場合、最終列車の行き先を表示します。また、種別変更がある場合はそれを表示します
								bool bIsClassChange = pCentDedRessya->getLastOperation().getNextJunctionType() == 1;
								for (int idx2 = idx + 1; idx2 < (int)aCustomizeJikokuhyouContent.iRessyaIndexCont.size(); idx2++)
								{
									const CentDedRessya* pCentDedRessyaNext = pCentDedRessyaCont->getMuPtr()->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[idx2]);
									if (bIsClassChange && getDisplayClassChange())
									{
										/**
											前後タイプが種別変更の場合は、種別変更表示を作成する。
										*/
										EkiJikokuhyouContent aEkiJikokuhyouContentClassChange;
										aEkiJikokuhyouContentClassChange.iMinute = -1;//種別変更
										aEkiJikokuhyouContentClassChange.iRessyaSyubetsu = pCentDedRessyaNext->getRessyasyubetsuIndex();
										aEkiJikokuhyouContentClassChange.iSyuuchakuEkiOrder = pCentDedRessyaNext->getValidSihatsuEki();//簡易モードの場合、列車方向は必ず同じなので、そのまま入れる
										aEkiJikokuhyouContentClassChange.aRessyaProperty = 
											CdDedRessyaProperty(GetDocument()->getRessyahoukou(), aCustomizeJikokuhyouContent.iRessyaIndexCont[idx2]);

										ListEkiJikokuhyouContentTemp.push_back(aEkiJikokuhyouContentClassChange);

									}
									//末尾列車の場合は、終着駅と路線外終着駅を取得、
									//末尾ではない場合は、種別変更か否かを取得
									if (idx2 == (int)aCustomizeJikokuhyouContent.iRessyaIndexCont.size() - 1)
									{
										aEkiJikokuhyouContent.iSyuuchakuEkiOrder = pCentDedRessyaNext->getValidSyuuchakuEki();
										const CentDedAfterOperation aLastOperation = pCentDedRessyaNext->getLastOperation();
										if (aLastOperation.getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
										{
											aEkiJikokuhyouContent.iOuterShuchakuekiIndex = aLastOperation.getOuterShuchakuekiIndex();
										}
									}
									else
									{
										bIsClassChange = pCentDedRessyaNext->getLastOperation().getNextJunctionType() == 1;
									}
								}
							}
							bFound = true;
						}
					}
				}


				//aEkiJikokuhyouContent.iSyuuchakuEkiOrder = iSyuuchakuEkiOrder;
				//const CentDedAfterOperation aLastOperation = pCentDedRessya->getLastOperation();
				//if (aLastOperation.getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
				//{
				//	aEkiJikokuhyouContent.iOuterShuchakuekiIndex = aLastOperation.getOuterShuchakuekiIndex();
				//}
				aEkiJikokuhyouContent.aRessyaProperty =
					CdDedRessyaProperty(GetDocument()->getRessyahoukou(), iRessyaIndex);

				//簡易モードの場合の始発駅判定は、有効始発駅かつ路線外始発ではないかつ、この列車がCustomizeJikokuhyouContentのiRessyaIndexContの先頭にあることです。
				//bool bIsShihatsu = pCentDedRessya->getValidSihatsuEki() == iEkiOrder;
				//if (bIsShihatsu)
				//{
				//	if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
				//	{
				//		bIsShihatsu = false;
				//	}
				//}
				//if (bIsShihatsu)
				//{
				//	const vector<CustomizeJikokuhyouContent>& contCustomizeJikokuhyouContent =
				//		getCentDedDia()->getcontCustomizeRessyaIndex(GetDocument()->getRessyahoukou());
				//	bool bFound = false;
				//	//CustomizeJikokuhyouContentのiRessyaIndexContの先頭要素だけを確認、先頭になければbIsShihatsuをfalseにします。
				//	for (int iCustomizeJikokuhyouContent = 0; iCustomizeJikokuhyouContent < (int)contCustomizeJikokuhyouContent.size() && !bFound; iCustomizeJikokuhyouContent++)
				//	{
				//		const CustomizeJikokuhyouContent& aCustomizeJikokuhyouContent = contCustomizeJikokuhyouContent[iCustomizeJikokuhyouContent];
				//		if (aCustomizeJikokuhyouContent.iRessyaIndexCont.empty())
				//		{
				//			continue;
				//		}
				//		if (aCustomizeJikokuhyouContent.iRessyaIndexCont.front() == iRessyaIndex)
				//		{
				//			bFound = true;
				//		}
				//	}
				//	bIsShihatsu = bFound;
				//}
				//aEkiJikokuhyouContent.bIsShihatsu = bIsShihatsu;

				ListEkiJikokuhyouContentTemp.push_front(aEkiJikokuhyouContent);

				if (m_contListEkiJikokuhyouContent.find(aHatsuJikoku.getHour()) == m_contListEkiJikokuhyouContent.end())
				{
					m_contListEkiJikokuhyouContent[aHatsuJikoku.getHour()] = ListEkiJikokuhyouContentTemp;
				}
				else
				{
					list<EkiJikokuhyouContent>& ListEkiJikokuhyouContent =
						m_contListEkiJikokuhyouContent[aHatsuJikoku.getHour()];
					bool bInsert = false;
					for (auto itr = ListEkiJikokuhyouContent.begin(); itr != ListEkiJikokuhyouContent.end(); itr++)
					{
						if (aHatsuJikoku.getMinute() >= itr->iMinute)
						{
							continue;
						}
						ListEkiJikokuhyouContent.insert(itr, ListEkiJikokuhyouContentTemp.begin(), ListEkiJikokuhyouContentTemp.end());
						bInsert = true;
						break;
					}
					if (!bInsert)
					{
						ListEkiJikokuhyouContent.insert(
							ListEkiJikokuhyouContent.end(), ListEkiJikokuhyouContentTemp.begin(), ListEkiJikokuhyouContentTemp.end());
					}
				}


				//パターンダイヤプレビュー機能対応、上記の作業を、パターンダイヤの範囲分繰り返す
				if (m_iPatternDiagramPreviewCycleSecond > 0)
				{
					for (int iShiftSecond = m_iPatternDiagramPreviewCycleSecond; iShiftSecond <= m_iPatternDiagramPreviewRange; iShiftSecond += m_iPatternDiagramPreviewCycleSecond)
					{
						CdDedJikoku aHatsuJikokuTemp = aHatsuJikoku;
						aHatsuJikokuTemp.addSeconds(iShiftSecond);

						//ListEkiJikokuhyouContentTempの先頭が、時刻表示なので、そこを書き換える
						ListEkiJikokuhyouContentTemp.front().iMinute = aHatsuJikokuTemp.getMinute();

						if (m_contListEkiJikokuhyouContent.find(aHatsuJikokuTemp.getHour()) == m_contListEkiJikokuhyouContent.end())
						{
							m_contListEkiJikokuhyouContent[aHatsuJikokuTemp.getHour()] = ListEkiJikokuhyouContentTemp;
						}
						else
						{
							list<EkiJikokuhyouContent>& ListEkiJikokuhyouContent =
								m_contListEkiJikokuhyouContent[aHatsuJikokuTemp.getHour()];
							bool bInsert = false;
							for (auto itr = ListEkiJikokuhyouContent.begin(); itr != ListEkiJikokuhyouContent.end(); itr++)
							{
								if (aHatsuJikokuTemp.getMinute() >= itr->iMinute)
								{
									continue;
								}
								ListEkiJikokuhyouContent.insert(itr, ListEkiJikokuhyouContentTemp.begin(), ListEkiJikokuhyouContentTemp.end());
								bInsert = true;
								break;
							}
							if (!bInsert)
							{
								ListEkiJikokuhyouContent.insert(
									ListEkiJikokuhyouContent.end(), ListEkiJikokuhyouContentTemp.begin(), ListEkiJikokuhyouContentTemp.end());
							}
						}

						aHatsuJikokuTemp = aHatsuJikoku;
						aHatsuJikokuTemp.addSeconds(-iShiftSecond);

						ListEkiJikokuhyouContentTemp.front().iMinute = aHatsuJikokuTemp.getMinute();

						if (m_contListEkiJikokuhyouContent.find(aHatsuJikokuTemp.getHour()) == m_contListEkiJikokuhyouContent.end())
						{
							m_contListEkiJikokuhyouContent[aHatsuJikokuTemp.getHour()] = ListEkiJikokuhyouContentTemp;
						}
						else
						{
							list<EkiJikokuhyouContent>& ListEkiJikokuhyouContent =
								m_contListEkiJikokuhyouContent[aHatsuJikokuTemp.getHour()];
							bool bInsert = false;
							for (auto itr = ListEkiJikokuhyouContent.begin(); itr != ListEkiJikokuhyouContent.end(); itr++)
							{
								if (aHatsuJikokuTemp.getMinute() >= itr->iMinute)
								{
									continue;
								}
								ListEkiJikokuhyouContent.insert(itr, ListEkiJikokuhyouContentTemp.begin(), ListEkiJikokuhyouContentTemp.end());
								bInsert = true;
								break;
							}
							if (!bInsert)
							{
								ListEkiJikokuhyouContent.insert(
									ListEkiJikokuhyouContent.end(), ListEkiJikokuhyouContentTemp.begin(), ListEkiJikokuhyouContentTemp.end());
							}
						}
					}
				}
			}
			else
			{
				vector<tstring> strContOperationNumber = pCentDedRessya->getOperationNumber(iEkiOrder);

				CdDedJikoku aHatsuJikoku = pCentDedRessya->getCentDedEkiJikoku(iEkiOrder).getVirtualHatsujikoku();
				//CdDedJikoku aHatsuJikoku = pCentDedRessya->getCentDedEkiJikoku(iEkiOrder).getHatsujikoku();
				aHatsuJikoku.round(eSecondRound);
				CdDedRessyaProperty aRessyaProperty(
					GetDocument()->getRessyahoukou(),
					iRessyaIndex);
				list<EkiJikokuhyouContent> ListEkiJikokuhyouContentTemp;

				unordered_map<tstring, vector<RessyaPropertyBuffer>> MapContRessyaPropertyBuffer;
				unordered_map<tstring, list<EkiJikokuhyouContent>> MapListEkiJikokuhyouContentBuffer;

				/**
					まず最初に、運用機能OFF時と同様の方法で終着駅を取得して、ListEkiJikokuhyouContentTempに収める
				*/
				int iSyuuchakuEkiOrder = pCentDedRessya->getValidSyuuchakuEki();
				if (iSyuuchakuEkiOrder == -1)
				{
					continue;
				}
				
				bool bIsShihatsu = pCentDedRessya->getValidSihatsuEki() == iEkiOrder;
				if (bIsShihatsu)
				{
					if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
					{
						bIsShihatsu = false;
					}
				}

				//仮の運用番号、運用番号には使えない";"を用いておく。
				tstring strOperationNumberMain = _T(";");
				{
					EkiJikokuhyouContent aEkiJikokuhyouContentMain;
					RessyaPropertyBuffer aRessyaPropertyBufferMain;
					aEkiJikokuhyouContentMain.iRessyaSyubetsu = pCentDedRessya->getRessyasyubetsuIndex();
					aEkiJikokuhyouContentMain.iMinute = aHatsuJikoku.getMinute();

					aEkiJikokuhyouContentMain.iRessyaTrackIndex = pCentDedRessya->getCentDedEkiJikoku(iEkiOrder).getRessyaTrackIndex();

					aEkiJikokuhyouContentMain.iSyuuchakuEkiOrder = iSyuuchakuEkiOrder;
					aRessyaPropertyBufferMain.iSyuuchakuEkiOrder = iSyuuchakuEkiOrder;

					/**
						この列車のルートを調べる、ルートに輪ができ、輪の終点が当駅なら、この列車の行き先は"環状"になる。
						輪の終点が当駅以外なら、この列車の行き先は"環状線"になる。
					*/
					vector<int> RouteEkiIndex;

					bool bLoop = false;
					for (int ord = iEkiOrder; ord < iSyuuchakuEkiOrder; ord++)
					{
						if (!pCentDedRessya->isRunBetweenNextEki(ord))
						{
							/**
								idxと次の駅間を運転していない場合は、
								運行なし区間を飛ばし、次に運行ありになる区間へ移る、
								その際、運行なしの前後が同一駅(分岐・環状関係)であることを確認する。
							*/
							int iEkiOrderNext = pCentDedRessya->getRunBetweenEkiForward(ord);
							if (iEkiOrderNext != -1 &&
								iEkiOrderNext < iSyuuchakuEkiOrder &&
								pCentDedEkiCont->isSameBrunchLoopGroup(ord, iEkiOrderNext, pCentDedRessya->getRessyahoukou()))
							{
								ord = iEkiOrderNext;
							}
							else
							{
								break;
							}
						}

						int iEkiIndexPrev = iEkiOrderTable[ord][(int)pCentDedRessya->getRessyahoukou()];
						int iEkiIndexNext = iEkiOrderTable[ord + 1][(int)pCentDedRessya->getRessyahoukou()];
						int iPosition = -1;
						for (int iSearchIndex = 0; iSearchIndex < (int)RouteEkiIndex.size(); iSearchIndex++)
						{
							if (RouteEkiIndex[iSearchIndex] == iEkiIndexNext)
							{
								iPosition = iSearchIndex;
								break;
							}
						}
						if (iPosition == -1)
						{
							/**
								iPositionが-1の場合は、RouteEkiIndexに前駅のIndexを追加して次へ
							*/
							RouteEkiIndex.push_back(iEkiIndexPrev);
						}
						else if (iPosition == RouteEkiIndex.size() - 1)
						{
							/**
								iPositionが末尾の場合は、折り返している状態なので、RouteEkiIndexの末尾要素を削除して次へ。
							*/
							RouteEkiIndex.pop_back();
						}
						else if (iPosition == 0)
						{
							/**
								iPositionが先頭(かつ末尾ではない)の場合は、この列車の行き先は"環状"になる。
							*/
							bLoop = true;
							aEkiJikokuhyouContentMain.iSyuuchakuEkiOrder = -1;
							aRessyaPropertyBufferMain.iSyuuchakuEkiOrder = ord + 1;
							aRessyaPropertyBufferMain.bLoop = true;
							break;
						}
						else
						{
							/**
								iPositionが中間の場合は、この列車の行き先は"環状線"になる。
							*/
							bLoop = true;
							aEkiJikokuhyouContentMain.iSyuuchakuEkiOrder = -2;
							aRessyaPropertyBufferMain.iSyuuchakuEkiOrder = ord + 1;
							aRessyaPropertyBufferMain.bLoop = true;
							break;
						}
					}

					const CentDedAfterOperation aLastOperation = pCentDedRessya->getLastOperation();
					if (!bLoop && aLastOperation.getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
					{
						aEkiJikokuhyouContentMain.iOuterShuchakuekiIndex = aLastOperation.getOuterShuchakuekiIndex();
						aRessyaPropertyBufferMain.iOuterShuchakuekiIndex = aLastOperation.getOuterShuchakuekiIndex();
					}
					aEkiJikokuhyouContentMain.aRessyaProperty = aRessyaProperty;
					aRessyaPropertyBufferMain.aRessyaProperty = aRessyaProperty;

					//aEkiJikokuhyouContentMain.bIsShihatsu = bIsSihatsu;

					MapListEkiJikokuhyouContentBuffer[strOperationNumberMain] = { aEkiJikokuhyouContentMain };
					MapContRessyaPropertyBuffer[strOperationNumberMain] = { aRessyaPropertyBufferMain };
				}

				///**
				//	次に、各運用番号に対して行き先を取得する。
				//	その際、主編成の終点から、種別変更・分割で先の列車につながっている場合、
				//	終点で解結して路線外終着になる場合は、上で獲得した主編成の終着駅を置き換える。
				//	なお、主編成が路線外終着の場合は置き換えは起こらない。
				//*/

				for (int idx = 0; idx < (int)strContOperationNumber.size(); idx++)
				{
					tstring strOperationNumber = strContOperationNumber[idx]; 

					if (strOperationNumber.empty())
					{
						continue;
					}
					list<OperationTableContent>& ListOperationTableContent = contOperationTableContent[strOperationNumber];
					auto itr = ListOperationTableContent.begin();
					for (; itr != ListOperationTableContent.end(); itr++)
					{
						if (!itr->aRessyaProperty.isEqualTo(aRessyaProperty, false))
						{
							continue;
						}
						if (itr->iSihatsuEkiOrder > iEkiOrder ||
							itr->iSyuuchakuEkiOrder < iEkiOrder)
						{
							continue;
						}
						break;
					}
					if (itr == ListOperationTableContent.end())
					{
						continue;
					}
					list<EkiJikokuhyouContent> ListEkiJikokuhyouContentTempPerON;
					vector<RessyaPropertyBuffer > ContRessyaPropertyBuffer;

					EkiJikokuhyouContent aEkiJikokuhyouContent;
					aEkiJikokuhyouContent.iRessyaSyubetsu = pCentDedRessya->getRessyasyubetsuIndex();
					aEkiJikokuhyouContent.iMinute = aHatsuJikoku.getMinute();
					aEkiJikokuhyouContent.iRessyaTrackIndex = pCentDedRessya->getCentDedEkiJikoku(iEkiOrder).getRessyaTrackIndex();
					aEkiJikokuhyouContent.iSyuuchakuEkiOrder = itr->iSyuuchakuEkiOrder;
					aEkiJikokuhyouContent.iOuterShuchakuekiIndex = itr->iOuterShuchakuekiIndex;
					aEkiJikokuhyouContent.aRessyaProperty = aRessyaProperty;


					/**
						bIsShihatsuを求める
						通常モードにおいては、(1)bIsSihatsu(ローカル変数の)がfalseな場合(有効始発駅ではないor主編成が路線外始発ではない場合)は、false確定
						(2)bIsSihatsuがtrueの場合、OperationTableContentを見て、eBeforeTypeが種別変更・列車情報変更・同一列車扱い・路線外始発・運用番号変更の場合は
								false確定となり、bIsShihatsuをfalseにします。
							それ以外(別列車・出区)の場合は、bIsShihatsuをtrueのままとし、全ての運用番号が、eBeforeTypeが別列車・出区で、bIsShihatsuがtrueのままだった時、
								この列車についてbIsShihatsuがtrueと確定します

						つまり、bIsShihatsu=falseが一つでもあったらfalseとなる
					*/

					if (bIsShihatsu)
					{
						if (itr->eBeforeType != EBeforeAfterType::BeforeAfterType_Unrelated &&
							itr->eBeforeType != EBeforeAfterType::BeforeAfterType_OutIn)
						{
							bIsShihatsu = false;
						}
					}
					//bIsShihatsuは最後に書き込む

					/**
						この列車のルートを調べる、ルートに輪ができ、輪の終点が当駅なら、この列車の行き先は"環状"になる。
						輪の終点が当駅以外なら、この列車の行き先は"環状線"になる。
					*/
					vector<int> RouteEkiIndex;
					bool bLoop = false;
					bool bFirst = true;

					for (; itr != ListOperationTableContent.end(); itr++)
					{

						const CentDedRessya* pCentDedRessyaSearch =
							pCentDedRessyaConts[itr->aRessyaProperty.getRessyahoukou()]
							->get(itr->aRessyaProperty.getRessyaIndex());

						//行き先をitrで上書きする。
						//終着駅Orderは、一度駅Indexに直してから、元々の列車方向に合わせたOrderに変更しなおす。
						int iSyuuchakuEkiIndexSearch = pCentDedRessyaSearch->EkiIndexOfEkiOrder(itr->iSyuuchakuEkiOrder);
						aEkiJikokuhyouContent.iSyuuchakuEkiOrder = pCentDedRessya->EkiOrderOfEkiIndex(iSyuuchakuEkiIndexSearch);
						aEkiJikokuhyouContent.iOuterShuchakuekiIndex = itr->iOuterShuchakuekiIndex;

						RessyaPropertyBuffer aRessyaPropertyBuffer;
						//aRessyaPropertyBufferの終着駅Orderはその列車基準でokとする(同じ列車同士で比較し、終着駅の遠さを見る必要があるので)
						aRessyaPropertyBuffer.iSyuuchakuEkiOrder = itr->iSyuuchakuEkiOrder;
						aRessyaPropertyBuffer.iOuterShuchakuekiIndex = itr->iOuterShuchakuekiIndex;
						aRessyaPropertyBuffer.aRessyaProperty = itr->aRessyaProperty;
						/**
							前後タイプが種別変更の場合は、種別変更表示を作成する。
						*/
						if (!bFirst &&
							itr->eBeforeType == EBeforeAfterType::BeforeAfterType_ClassChange && 
							getDisplayClassChange())
						{
							EkiJikokuhyouContent aEkiJikokuhyouContentClassChange;
							aEkiJikokuhyouContentClassChange.iMinute = -1;//種別変更
							aEkiJikokuhyouContentClassChange.iRessyaSyubetsu = pCentDedRessyaSearch->getRessyasyubetsuIndex();
							int iClassChangeEkiIndex = pCentDedRessyaSearch->EkiIndexOfEkiOrder(itr->iSihatsuEkiOrder);
							aEkiJikokuhyouContentClassChange.iSyuuchakuEkiOrder = pCentDedRessya->EkiOrderOfEkiIndex(iClassChangeEkiIndex);
							aEkiJikokuhyouContentClassChange.aRessyaProperty = itr->aRessyaProperty;

							ListEkiJikokuhyouContentTempPerON.push_back(aEkiJikokuhyouContentClassChange);
						}

						int ord = itr->iSihatsuEkiOrder;
						if (bFirst)
						{
							ord = iEkiOrder;
							bFirst = false;
						}
						for (; ord < itr->iSyuuchakuEkiOrder; ord++)
						{
							if (!pCentDedRessyaSearch->isRunBetweenNextEki(ord))
							{
								/**
									idxと次の駅間を運転していない場合は、
									運行なし区間を飛ばし、次に運行ありになる区間へ移る、
									その際、運行なしの前後が同一駅(分岐・環状関係)であることを確認する。
								*/
								int iEkiOrderNext = pCentDedRessyaSearch->getRunBetweenEkiForward(ord);
								if (iEkiOrderNext != -1 &&
									iEkiOrderNext < itr->iSyuuchakuEkiOrder &&
									pCentDedEkiCont->isSameBrunchLoopGroup(ord, iEkiOrderNext, pCentDedRessyaSearch->getRessyahoukou()))
								{
									ord = iEkiOrderNext;
								}
								else
								{
									break;
								}
							}

							int iEkiIndexPrev = iEkiOrderTable[ord][(int)pCentDedRessyaSearch->getRessyahoukou()];
							int iEkiIndexNext = iEkiOrderTable[ord + 1][(int)pCentDedRessyaSearch->getRessyahoukou()];
							int iPosition = -1;
							for (int iSearchIndex = 0; iSearchIndex < (int)RouteEkiIndex.size(); iSearchIndex++)
							{
								if (RouteEkiIndex[iSearchIndex] == iEkiIndexNext)
								{
									iPosition = iSearchIndex;
									break;
								}
							}
							if (iPosition == -1)
							{
								/**
									iPositionが-1の場合は、RouteEkiIndexに前駅のIndexを追加して次へ
								*/
								RouteEkiIndex.push_back(iEkiIndexPrev);
							}
							else if (iPosition == RouteEkiIndex.size() - 1)
							{
								/**
									iPositionが末尾の場合は、折り返している状態なので、RouteEkiIndexの末尾要素を削除して次へ。
								*/
								RouteEkiIndex.pop_back();
							}
							else if (iPosition == 0)
							{
								/**
									iPositionが先頭(かつ末尾ではない)の場合は、この列車の行き先は"環状"になる。
								*/
								bLoop = true;
								aEkiJikokuhyouContent.iSyuuchakuEkiOrder = -1;
								ListEkiJikokuhyouContentTempPerON.push_front(aEkiJikokuhyouContent);
								//aRessyaPropertyBufferの終着駅Orderはその列車基準でokとする(同じ列車同士で比較し、終着駅の遠さを見る必要があるので)
								aRessyaPropertyBuffer.iSyuuchakuEkiOrder = ord + 1;
								aRessyaPropertyBuffer.bLoop = true;
								//iLoop = -1;
								break;
							}
							else
							{
								/**
									iPositionが中間の場合は、この列車の行き先は"環状線"になる。
								*/
								bLoop = true;
								aEkiJikokuhyouContent.iSyuuchakuEkiOrder = -2;
								ListEkiJikokuhyouContentTempPerON.push_front(aEkiJikokuhyouContent);
								aRessyaPropertyBuffer.iSyuuchakuEkiOrder = ord + 1;
								aRessyaPropertyBuffer.bLoop = true;
								//iLoop = -2;
								break;
							}
						}
						ContRessyaPropertyBuffer.push_back(aRessyaPropertyBuffer);
						/**
							itrの終着駅まで検索しても、環状にならなかった場合は、
							次列車接続タイプを見て、次列車探索に入るかここで終了するかを決める
						*/
						if (bLoop)
						{
							break;
						}
						auto itrNext = itr;
						itrNext++;
						if (itrNext != ListOperationTableContent.end() &&
							(itr->eAfterType == EBeforeAfterType::BeforeAfterType_ClassChange ||
							itr->eAfterType == EBeforeAfterType::BeforeAfterType_PropertyChange ||
							itr->eAfterType == EBeforeAfterType::BeforeAfterType_PropertySame) &&
							itrNext->eBeforeType == itr->eAfterType)
						{
							//この列車が末尾ではなく、後タイプが種別変更・列車情報変更・同一列車扱いのいずれかで、
							//次の列車と一致しているのなら、次の列車の検索を行う。
							continue;
						}
						else
						{
							//この列車が末尾、または後タイプが同一列車扱い以外、または次列車の前タイプと一致しない場合、
							//この列車が一体化の末尾となるので
							//aEkiJikokuhyouContentをListの先頭に入れる。
							ListEkiJikokuhyouContentTempPerON.push_front(aEkiJikokuhyouContent);
							break;
						}
					}

					/**
						ListEkiJikokuhyouContentTempPerONが組みあがったら、
						ContRessyaPropertyBufferとMapContRessyaPropertyBufferを突き合わせて
						必要に応じて置き換える
						また、この運番を内包するものがあったら、追加を行わない(bAddをfalseにする)
					*/
					bool bAdd = true;
					tstring strReplace = _T("");
					for (auto itr = MapContRessyaPropertyBuffer.begin(); itr != MapContRessyaPropertyBuffer.end() 
						&& strReplace.empty() && bAdd; itr++)
					{
						vector<RessyaPropertyBuffer>& contRessyaPropertyBufferSearch = itr->second;
						for (int idxRPB = 0; idxRPB < (int)ContRessyaPropertyBuffer.size(); idxRPB++)
						{
							if (!ContRessyaPropertyBuffer[idxRPB].aRessyaProperty.isEqualTo(
								contRessyaPropertyBufferSearch[idxRPB].aRessyaProperty, false))
							{
								//idxRPB番目の列車自体が異なる場合は、異なる行き先(具体的には、前列車の終着駅で分割しているパターン)なので、
								//置き換え対象にはならない。
								break;
							}
							else if (ContRessyaPropertyBuffer[idxRPB].iSyuuchakuEkiOrder >
								contRessyaPropertyBufferSearch[idxRPB].iSyuuchakuEkiOrder)
							{
								/**
									この運番の方が長い区間で運行されている場合、
									探索運番が路線外終着ではないかつ、
									探索運番の次列車がない場合(idxRPBが末尾の場合)
									(完全に探索運番がiSyuuchakuEkiOrderで終了している場合) 
									この運番で探索運番を置き換えます
									探索の次列車がある場合・探索運番が路線外終着の場合は、次運用の探索に映る
								*/
								if (contRessyaPropertyBufferSearch[idxRPB].iOuterShuchakuekiIndex < 0 &&
									contRessyaPropertyBufferSearch.size() == idxRPB + 1)
								{
									strReplace = itr->first;
								}
								break;
							}
							else if (ContRessyaPropertyBuffer[idxRPB].iSyuuchakuEkiOrder <
								contRessyaPropertyBufferSearch[idxRPB].iSyuuchakuEkiOrder)
							{
								/**
									この運番の方が短い区間で運行されている場合、
									この運番の次列車がない場合(idxRPBが末尾の場合)、路線外終着でもない場合は
									この運番は置き換えも追加も行いません
									この運番の次列車がある場合・この運番が路線外終着の場合は、次運用の探索に映る

								*/
								if (ContRessyaPropertyBuffer[idxRPB].iOuterShuchakuekiIndex < 0 &&
									ContRessyaPropertyBuffer.size() == idxRPB + 1)
								{
									bAdd = false;
								}
								break;
							}
							//この運番と探索運番の終着駅が同じ場合
							else if (ContRessyaPropertyBuffer[idxRPB].iOuterShuchakuekiIndex < 0 &&
								ContRessyaPropertyBuffer.size() == idxRPB + 1)
							{
								/**
									この運番の最終列車の場合(除く路線外終着)は、
									この運番は探索運番に内包されている、もしくは一致しているので、
									置き換えも追加も行いません
								*/
								bAdd = false;
								break;
							}
							else if (contRessyaPropertyBufferSearch[idxRPB].iOuterShuchakuekiIndex < 0 &&
								contRessyaPropertyBufferSearch.size() == idxRPB + 1)
							{
								/**
									探索運番の最終列車の場合(除く路線外終着)は、
									探索運番はこの運番に内包されているので、
									置き換えます
								*/
								strReplace = itr->first;
								break;
							}
							//この運番と探索運番が次列車ありと路線外終着のいずれか
							else if (ContRessyaPropertyBuffer[idxRPB].iOuterShuchakuekiIndex >= 0)
							{
								/**
									この運番が路線外終着の場合、
									探索運番も路線外終着で、終着駅が同じ場合は、一致しているの置き換えも追加も行いません
									それ以外の場合は、分岐しているので、次運用の探索に移ります
								*/
								if (ContRessyaPropertyBuffer[idxRPB].iOuterShuchakuekiIndex ==
									contRessyaPropertyBufferSearch[idxRPB].iOuterShuchakuekiIndex)
								{
									bAdd = false;
								}
								break;
							}
							else if (contRessyaPropertyBufferSearch[idxRPB].iOuterShuchakuekiIndex >= 0)
							{
								/**
									この運番が、次列車につながっていて、
									かつ探索運番が路線外終着の場合は、分岐しているので、次運用の探索に移ります
								*/
								break;
							}
							/**
								この運番と探索運番が共に次列車につながっている場合は、
								次列車同士での比較になります。
							*/
						}
					}

					if (!strReplace.empty())
					{
						MapListEkiJikokuhyouContentBuffer.erase(strReplace);
						MapContRessyaPropertyBuffer.erase(strReplace);
					}
					if (bAdd)
					{
						MapListEkiJikokuhyouContentBuffer[strOperationNumber] = ListEkiJikokuhyouContentTempPerON;
						MapContRessyaPropertyBuffer[strOperationNumber] = ContRessyaPropertyBuffer;
					}
				}

				/**
					一本の列車の全ての運番＆主行き先についての探索が終わったら、MapListEkiJikokuhyouContentBufferに収められたものを
					一つに並び替え、m_contListEkiJikokuhyouContentに挿入します。

					並び替え順
						(1)この列車内で終着駅Orderが大きい順
						(2)種別変更の少ない順
						(3)運用番号順
				*/
				while (!MapListEkiJikokuhyouContentBuffer.empty())
				{
					auto itrFirst = MapListEkiJikokuhyouContentBuffer.begin();
					auto itrNext = itrFirst;
					itrNext++;
					while (itrNext != MapListEkiJikokuhyouContentBuffer.end())
					{
						const list<EkiJikokuhyouContent>& ListEkiJikokuhyouContentBufferFirst = itrFirst->second;
						const vector<RessyaPropertyBuffer>& ContRessyaPropertyBufferFirst =
							MapContRessyaPropertyBuffer[itrFirst->first];
						const list<EkiJikokuhyouContent>& ListEkiJikokuhyouContentBufferNext = itrNext->second;
						const vector<RessyaPropertyBuffer>& ContRessyaPropertyBufferNext =
							MapContRessyaPropertyBuffer[itrNext->first];
						if (ContRessyaPropertyBufferFirst.front().iSyuuchakuEkiOrder <
							ContRessyaPropertyBufferNext.front().iSyuuchakuEkiOrder)
						{
							itrFirst = itrNext;
						}
						else if (ContRessyaPropertyBufferFirst.front().iSyuuchakuEkiOrder >
							ContRessyaPropertyBufferNext.front().iSyuuchakuEkiOrder)
						{
							//itrFirstの方が前方
						}
						else if (ListEkiJikokuhyouContentBufferFirst.size() >
							ListEkiJikokuhyouContentBufferNext.size())
						{
							itrFirst = itrNext;
						}
						else if (ListEkiJikokuhyouContentBufferFirst.size() <
							ListEkiJikokuhyouContentBufferNext.size())
						{
							//itrFirstの方が前方
						}
						else if (itrFirst->first == strOperationNumberMain)
						{
							itrFirst = itrNext;
						}
						else if (itrNext->first == strOperationNumberMain)
						{
							//itrFirstの方が前方
						}
						else
						{
							for (int idx = 0; idx < (int)strContOperationNumber.size(); idx++)
							{
								if (itrFirst->first == strContOperationNumber[idx])
								{
									//itrFirstの方が前方
									break;

								}
								else if (itrNext->first == strContOperationNumber[idx])
								{
									itrFirst = itrNext;
									break;

								}
							}
						}
						itrNext++;
					}

					tstring strOperationNumberFirst = itrFirst->first;
					ListEkiJikokuhyouContentTemp.splice(ListEkiJikokuhyouContentTemp.end(),
						MapListEkiJikokuhyouContentBuffer[strOperationNumberFirst]);
					MapListEkiJikokuhyouContentBuffer.erase(strOperationNumberFirst);
					MapContRessyaPropertyBuffer.erase(strOperationNumberFirst);
				}

				/**
					ここで、bIsShihatsuを書き込む。
				*/
				for (auto itrListEkiJikokuhyouContent = ListEkiJikokuhyouContentTemp.begin();
					itrListEkiJikokuhyouContent != ListEkiJikokuhyouContentTemp.end();
					itrListEkiJikokuhyouContent++)
				{
					if (itrListEkiJikokuhyouContent->iMinute >= 0)
					{
						itrListEkiJikokuhyouContent->bIsShihatsu = bIsShihatsu;
					}
				}


				/**
					ListEkiJikokuhyouContentTempへの読み取りが終わったら、m_contListEkiJikokuhyouContentに挿入する。
				*/
				if (m_contListEkiJikokuhyouContent.find(aHatsuJikoku.getHour()) == m_contListEkiJikokuhyouContent.end())
				{
					m_contListEkiJikokuhyouContent[aHatsuJikoku.getHour()] = ListEkiJikokuhyouContentTemp;
				}
				else
				{
					list<EkiJikokuhyouContent>& ListEkiJikokuhyouContent =
						m_contListEkiJikokuhyouContent[aHatsuJikoku.getHour()];
					bool bInsert = false;
					for (auto itr = ListEkiJikokuhyouContent.begin(); itr != ListEkiJikokuhyouContent.end(); itr++)
					{
						if (aHatsuJikoku.getMinute() >= itr->iMinute)
						{
							continue;
						}
						ListEkiJikokuhyouContent.insert(itr, ListEkiJikokuhyouContentTemp.begin(), ListEkiJikokuhyouContentTemp.end());
						bInsert = true;
						break;
					}
					if (!bInsert)
					{
						ListEkiJikokuhyouContent.insert(
							ListEkiJikokuhyouContent.end(), ListEkiJikokuhyouContentTemp.begin(), ListEkiJikokuhyouContentTemp.end());
					}
				}
			}
		}

		/**
			駅時刻表コンテンツの読み取りが終わったら、
			各時帯の列車本数を調べ、実際の駅時刻表の表示範囲を決める。
			起点時刻のある時間帯→起点時刻のある時間帯-1の順で調べる。
			最初に列車がある時間帯がm_iFirstHourとなり、最後に列車がある時間帯までの時数がm_iHourCountとなる
			ここでは、途中に列車がない時間帯があっても、表示のスキップはしない。
			また、m_iMaxRessyaCount(最も列車本数が多い時間の列車本数)も求める
		*/
		int iOffset = 0;
		int iBlankHourCount = 0;
		for (int iHour = KitenJikoku.getHour(); iHour < KitenJikoku.getHour() + 24; iHour++)
		{
			if (iHour == 24)
			{
				iOffset = -24;
			}
			if (m_contListEkiJikokuhyouContent.find(iHour + iOffset) == m_contListEkiJikokuhyouContent.end())
			{
				iBlankHourCount++;
				continue;
			}
			if (m_iMaxRessyaCount < (int)m_contListEkiJikokuhyouContent[iHour + iOffset].size())
			{
				m_iMaxRessyaCount = m_contListEkiJikokuhyouContent[iHour + iOffset].size();
			}
			if (m_iFirstHour == INT_MIN)
			{
				m_iFirstHour = iHour + iOffset;
				m_iHourCount = 1;
				iBlankHourCount = 0;
			}
			else
			{
				if (iBlankHourCount != 0)
				{
					m_iHourCount += iBlankHourCount;
					iBlankHourCount = 0;
				}
				m_iHourCount++;
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

		CdEkiJikokuhyouYColSpecCont aCdEkiJikokuhyouYColSpecCont = createYColSpecCont();
		getCXDcdGrid()->setYColumnCount(
			aCdEkiJikokuhyouYColSpecCont.size());

			//	各セルに、データを設定
		if (m_iFirstHour != INT_MIN && m_iHourCount != INT_MIN)
		{
			iOffset = 0;
			for (int idx = 0; idx < m_iHourCount; idx++)
			{
				if (m_iFirstHour + idx == 24)
				{
					iOffset = -24;
				}
				if (m_contListEkiJikokuhyouContent.find(m_iFirstHour + iOffset + idx) == m_contListEkiJikokuhyouContent.end())
				{
					OnUpdate_setEmptyEkiJikokuhyouContent_To_Column(
						m_iFirstHour + iOffset + idx);
				}
				else
				{
					OnUpdate_setEkiJikokuhyouContent_To_Column(
						m_iFirstHour + iOffset + idx,
						m_contListEkiJikokuhyouContent[m_iFirstHour + iOffset + idx]);
				}
			}
		}
		else
		{
			getCXDcdGrid()->setXFixColumnCount(0);
			getCXDcdGrid()->setYFixColumnCount(0);
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

void CWndDcdGridEkiJikokuhyou::OnCreate_Header()
{
	// --------------------------------
	//	運用表ビューに使用するフォント
	// --------------------------------
	CdFontProp fontpropDefault = createFontProp();
	//CdColorProp colorpropDefault = createStringColorProp();

	CdEkiJikokuhyouXColSpecCont aXColSpecCont = createXColSpecCont();
	// --------------------------------
	//	列の数を指定
	// --------------------------------

	getCXDcdGrid()->setXColumnCount(aXColSpecCont.size());
	getCXDcdGrid()->setXFixColumnCount(1);

	// --------------------------------
	//	列のサイズを設定
	// --------------------------------
	{
		CDcdTargetGetDC	aCDcdTarget(NULL);
		// --------------------------------
		//	X列
		// --------------------------------
		tstring strCellHourWidth(_T("00"));

		CdDedDispProp aCdDedDispProp =
			getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
		tstring strCellRessyaWidth(aCdDedDispProp.getJikokuhyouRessyaWidth(), '0');
		//tstring strCellRessyaWidth = _T("京都京");

		{
			//	列番号
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdEkiJikokuhyouXColSpec(
				CdEkiJikokuhyouXColSpec::EColumnType::ColumnType_Hour));
			CdDcdSizeXy	sizeHour;
			CDcdTextbox	aCDcdTextbox(
				strCellHourWidth,
				fontpropDefault,
				_T(""), 1, 2, 2);
			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeHour);
			getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeHour.getX());
		}
		for (int idx = 0; idx < m_iMaxRessyaCount; idx++)
		{
			//	列車方向
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdEkiJikokuhyouXColSpec(
				CdEkiJikokuhyouXColSpec::EColumnType::ColumnType_Ressya, idx));
			CdDcdSizeXy	sizeRessya;
			CDcdTextbox	aCDcdTextbox(
				strCellRessyaWidth,
				fontpropDefault,
				_T(""), 1, 2, 2);
			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeRessya);
			getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeRessya.getX());
			if (idx < m_iMaxRessyaCount - 1)
			{
				Ou<CDcdLine>
					(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())
					->setCdPenProp(getCdPenPropNullLine());
			}
			else
			{
				Ou<CDcdLine>
					(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())
					->setCdPenProp(getCdPenPropNarrowLine());

			}
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
		// 列番号
		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdEkiJikokuhyouXColSpec(
			CdEkiJikokuhyouXColSpec::EColumnType::ColumnType_Hour));


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
		tstring strHeader = GetDocument()->GetTitle();
		pCDcdTextbox->setText(strHeader);

		getCXDcdGrid()->getCell(iXColumnNumber, YCOLUMNNNO_HEADER)->setAttachCellCount( m_iMaxRessyaCount+1,1);
	}
	//for (int idx = 0; idx < m_iMaxRessyaCount; idx++)
	//{
	//	{
	//		// 列車方向
	//		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
	//			CdAllOperationTableXColSpec::ColumnType_Ressyahoukou, idx));

	//		Ou<CDcdTextbox>	pCDcdTextbox =
	//			getCXDcdGrid()->getCell(iXColumnNumber, YCOLUMNNNO_HEADER)->getIfDcDraw();

	//		CConverter_WinGdi aCConverter_WinGdi;

	//		CdDrawTextProp	aCdDrawTextProp(
	//			fontpropDefault,
	//			colorpropDefault);
	//			//aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENUTEXT));
	//		aCdDrawTextProp.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
	//		CdBrushProp	aCdBrushProp(
	//			aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENU));

	//		pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
	//		pCDcdTextbox->setCdBrushProp(aCdBrushProp);
	//		pCDcdTextbox->setText(to_tstring(idx + 1));

	//		Ou<CDcdLine>
	//			(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())
	//			->setCdPenProp(getCdPenPropDotLine());
	//	}
	//}
}

	// --------------------------------
	//@name メニューコマンドの下請関数
	// --------------------------------

int CWndDcdGridEkiJikokuhyou::OnEkiJikokuhyouMovetojikokuhyou_Process(BOOL bQueryEnable)
{
	int iRv = 0;
	if (iRv >= 0)
	{
		if (getCentDedDia()->getWaitOperationUpdate())
		{
			iRv = -1;	//運用更新抑止状態です
		}
	}
	CdEkiJikokuhyouYColSpec aCdEkiJikokuhyouYColSpec = getYColSpecOfFocus();
	CdEkiJikokuhyouXColSpec aCdEkiJikokuhyouXColSpec = getXColSpecOfFocus();
	if (iRv >= 0)
	{
		if (getCSelect()->getSelectedCellCount() == 0)
		{
			if (aCdEkiJikokuhyouYColSpec.getColumnType() ==
				CdEkiJikokuhyouYColSpec::EColumnType::ColumnType_Head)
			{
				iRv = -3;	//フォーカスが列車位置以外なら不可
			}
			else if (aCdEkiJikokuhyouXColSpec.getColumnType() ==
				CdEkiJikokuhyouXColSpec::EColumnType::ColumnType_Hour)
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
		int iHour = aCdEkiJikokuhyouYColSpec.getHour();
		if (m_contListEkiJikokuhyouContent.find(iHour) != m_contListEkiJikokuhyouContent.end())
		{
			const list<EkiJikokuhyouContent>& ListEkiJikokuhyouContent =
				m_contListEkiJikokuhyouContent[iHour];

			if ((int)ListEkiJikokuhyouContent.size() > aCdEkiJikokuhyouXColSpec.getRessyaIndex())
			{
				auto itr = ListEkiJikokuhyouContent.begin();
				for (int idx = 0; idx < aCdEkiJikokuhyouXColSpec.getRessyaIndex(); idx++)
				{
					itr++;
				}

				ERessyahoukou eRessyahoukou = itr->aRessyaProperty.getRessyahoukou();
				int iRessyaidx = itr->aRessyaProperty.getRessyaIndex();
				int iEkiIndex;
				if (itr->iMinute >= 0)
				{
					iEkiIndex = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
						->getCentDedEkiCont()->EkiIndexOfEkiID(GetDocument()->getEkiID());
				}
				else
				{
					//iEkiIndexは種別変更駅の駅Index
					iEkiIndex = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
						->getCentDedEkiCont()->EkiIndexOfEkiOrder(GetDocument()->getRessyahoukou(), itr->iSyuuchakuEkiOrder);
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
								eRessyahoukou,
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
					pCJikokuhyouView->setFocusToRessyaIndex(iRessyaidx, 
						getCentDedDia()->getCentDedRessyaCont(eRessyahoukou)
						->EkiOrderOfEkiIndex(iEkiIndex));
					iRv = 1;	//	時刻表ビューへ移動しました
				}


			}


		}

	}
	return iRv;
}

int CWndDcdGridEkiJikokuhyou::OnEkiJikokuhyouMovetodiagram_Process(BOOL bQueryEnable)
{
	int iRv = 0;
	if (iRv >= 0)
	{
		if (getCentDedDia()->getWaitOperationUpdate())
		{
			iRv = -1;	//運用更新抑止状態です
		}
	}
	CdEkiJikokuhyouYColSpec aCdEkiJikokuhyouYColSpec = getYColSpecOfFocus();
	CdEkiJikokuhyouXColSpec aCdEkiJikokuhyouXColSpec = getXColSpecOfFocus();
	if (iRv >= 0)
	{
		if (getCSelect()->getSelectedCellCount() == 0)
		{
			if (aCdEkiJikokuhyouYColSpec.getColumnType() ==
				CdEkiJikokuhyouYColSpec::EColumnType::ColumnType_Head)
			{
				iRv = -3;	//フォーカスが列車位置以外なら不可
			}
			else if (aCdEkiJikokuhyouXColSpec.getColumnType() ==
				CdEkiJikokuhyouXColSpec::EColumnType::ColumnType_Hour)
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
		int iHour = aCdEkiJikokuhyouYColSpec.getHour();
		if (m_contListEkiJikokuhyouContent.find(iHour) != m_contListEkiJikokuhyouContent.end())
		{
			const list<EkiJikokuhyouContent>& ListEkiJikokuhyouContent =
				m_contListEkiJikokuhyouContent[iHour];

			if ((int)ListEkiJikokuhyouContent.size() > aCdEkiJikokuhyouXColSpec.getRessyaIndex())
			{
				auto itr = ListEkiJikokuhyouContent.begin();
				for (int idx = 0; idx < aCdEkiJikokuhyouXColSpec.getRessyaIndex(); idx++)
				{
					itr++;
				}

				ERessyahoukou eRessyahoukou = itr->aRessyaProperty.getRessyahoukou();
				int iRessyaidx = itr->aRessyaProperty.getRessyaIndex();
				int iEkiIndex;
				if (itr->iMinute >= 0)
				{
					iEkiIndex = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
						->getCentDedEkiCont()->EkiIndexOfEkiID(GetDocument()->getEkiID());
				}
				else
				{
					//iEkiIndexは種別変更駅の駅Index
					iEkiIndex = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
						->getCentDedEkiCont()->EkiIndexOfEkiOrder(GetDocument()->getRessyahoukou(), itr->iSyuuchakuEkiOrder);
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
					CentDedRessya aCentDedRessya = getCentDedRessyaCont(eRessyahoukou)->get(iRessyaidx);
					//int iEkiIndex = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
					//	->getCentDedEkiCont()->EkiIndexOfEkiID(GetDocument()->getEkiID());
					pCDedDiagramView->setZone_Dgr(aCentDedRessya.getCentDedEkiJikoku(aCentDedRessya.EkiOrderOfEkiIndex(iEkiIndex)).getHatsujikoku(true),
						iEkiIndex, eRessyahoukou == ERessyahoukou::Ressyahoukou_Nobori);
				}
			}
		}
	}
	return iRv;
}

int CWndDcdGridEkiJikokuhyou::OnFileExportEkiJikokuhyouCsv_Process(BOOL bQueryEnable)
{
	int iRv = 0;
	CString	strError;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (getCentDedDia()->getWaitOperationUpdate())
		{
			iRv = -1;	//運用更新抑止状態です
		}
	}

	// ****************************************************************
	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************

	// --------------------------------
	//	出力ファイル名入力値の取得
	// --------------------------------
		if (iRv >= 0)
		{
			CFileDialog aDlg(
				FALSE,
				_T("csv"),
				m_strCsvFilename,
				OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
				getCDiagramEditApp()->getCFileDialogFilterCsv(),
				this);
			if (aDlg.DoModal() != IDOK)
			{
				iRv = -2;	//	Cancelされました。
			}
			else
			{
				m_strCsvFilename = aDlg.GetPathName();
			}
		}
		//m_strCsvFilename = 指定されたCSVファイル名

		// --------------------------------
		//	CSVファイルの出力
		// --------------------------------
		CWaitCursor aCursor;
		if (iRv >= 0)
		{
			CconvEkiJikokuhyouCsv	aConv;
			CdCsvDocument	aCdCsvDocument;
			int iEkiIndex = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
				->getCentDedEkiCont()->EkiIndexOfEkiID(GetDocument()->getEkiID());
			int iEkiOrder = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
				->getCentDedEkiCont()->EkiOrderOfEkiIndex(GetDocument()->getRessyahoukou(),iEkiIndex);
			int iResult = aConv.encode(
				GetDocument()->getRessyahoukou(),
				iEkiOrder,
				m_contListEkiJikokuhyouContent,
				(LPCTSTR)GetDocument()->GetTitle(),
				m_iFirstHour,
				m_iHourCount,
				m_bDisplayParentSyubetsu,
				false,
				getDisplayTrack(),
				getDisplayIsShihatsu(),
				&aCdCsvDocument);
			if (iResult < 0)
			{
				GetDlgItemText(IDC_TEXT_ENCODE_ERROR, strError);
				//strError="CSVへの変換に失敗しました。"

				strError.Format(_T("%s(%d)"), CString(strError), iResult);
				iRv = iResult - 10;
			}
			else
			{
				tstring strCsvDocument;
				CConvCsvDocument	aCConvCsvDocument;
				strCsvDocument = aCConvCsvDocument.encode(&aCdCsvDocument);
				int iResult = stringToFile(strCsvDocument, (LPCTSTR)m_strCsvFilename);
				if (iResult < 0)
				{
					GetDlgItemText(IDC_TEXT_FILE_SAVE_FAILED, strError);
					//strError="ファイルへの保存に失敗しました。"

					iRv = -21; // ファイルへの保存に失敗しました。

				}
			}
		}

		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv;
}

//int CWndDcdGridEkiJikokuhyou::OnFileExportAllOperationTableCsv_Process(BOOL bQueryEnable)
//{
//	int iRv = 0;
//	// ****************************************************************
//	//	コマンドの有効・無効判定
//	// ****************************************************************
//	if (iRv >= 0)
//	{
//		if (getCentDedDia()->getWaitOperationUpdate())
//		{
//			iRv = -1;	//運用更新抑止状態です
//		}
//	}
//
//	// ****************************************************************
//	if (!bQueryEnable && iRv >= 0)
//	{
//		// ****************************************************************
//		//	コマンドの実行
//		// ****************************************************************
//
//		CString	strError;
//		if (iRv >= 0)
//		{
//			CFileDialog aDlg(
//				FALSE,
//				_T("csv"),
//				m_strCsvFilename,
//				OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
//				getCDiagramEditApp()->getCFileDialogFilterCsv(),
//				this);
//			if (aDlg.DoModal() != IDOK)
//			{
//				iRv = -2;	//	Cancelされました。
//			}
//			else
//			{
//				m_strCsvFilename = aDlg.GetPathName();
//			}
//		}
//		//m_strCsvFilename = 指定されたCSVファイル名
//
//
//
//		// --------------------------------
//		//	CSVファイルの出力
//		// --------------------------------
//		CWaitCursor aCursor;
//		if (iRv >= 0)
//		{
//			const CDedRosenFileData* pCDedRosenFileData =
//				getCDiagramEditDoc()->getCDedRosenFileData();
//
//			CconvAllOperationTableCsv	aConv;
//			CdCsvDocument	aCdCsvDocument;
//			int iResult = aConv.encode(
//				*pCDedRosenFileData->getCentDedRosen(),
//				*getCentDedDia(),
//				m_strOperationNumber,
//				getDisplaySecondEkiJikoku(),
//				getDisplayColonEkiJikoku(),
//				getDisplayParentSyubetsu(),
//				getDisplayAllRessya(),
//				m_iMaxRessyaCount,
//				&aCdCsvDocument);
//			if (iResult < 0)
//			{
//				GetDlgItemText(IDC_TEXT_ENCODE_ERROR, strError);
//				//strError="CSVへの変換に失敗しました。"
//
//				strError.Format(_T("%s(%d)"), CString(strError), iResult);
//				iRv = iResult - 10;
//			}
//			else
//			{
//				tstring strCsvDocument;
//				CConvCsvDocument	aCConvCsvDocument;
//				strCsvDocument = aCConvCsvDocument.encode(&aCdCsvDocument);
//				int iResult = stringToFile(strCsvDocument, (LPCTSTR)m_strCsvFilename);
//				if (iResult < 0)
//				{
//					GetDlgItemText(IDC_TEXT_FILE_SAVE_FAILED, strError);
//					//strError="ファイルへの保存に失敗しました。"
//
//					iRv = -21; // ファイルへの保存に失敗しました。
//
//				}
//			}
//		}
//		// ****************************************************************
//		//	エラーメッセージ
//		// ****************************************************************
//
//		// ****************************************************************
//	}
//	return iRv;
//}

// ****************************************************************
//	CWndDcdGridEkiTrack2
// ****************************************************************


// ********************************
//	コンストラクタ
// ********************************
CWndDcdGridEkiJikokuhyou::CWndDcdGridEkiJikokuhyou()
	: m_bUpdate_All_Requested( false )
	, m_bInitialUpdateComplete(false)
	, m_iMaxRessyaCount(0)
	, m_iFirstHour(0)
	, m_iHourCount(0)
	, m_bDisplayParentSyubetsu(false)
	, m_bDisplayTrack(false)
	, m_strCsvFilename(_T(""))
	, m_iSecondRound(0)
	, m_bDisplayIsShihatsu(false)
	, m_bDisplayClassChange(true)
{
	//getCSelect()->setSelectMode( CSelect::SelectMode_YColumn ) ;
	getCSelect()->setSelectMode(CSelect::SelectMode_NONE);
}
CWndDcdGridEkiJikokuhyou::~CWndDcdGridEkiJikokuhyou()
{
}

// ********************************
//@name	CDcdGrid
// ********************************

// ********************************
//@name	CWndDcdGrid
// ********************************

	// ********************************
	//@name CWndDcdGridEkiJikokuhyou-操作
	// ********************************

CEkiJikokuhyouDoc * CWndDcdGridEkiJikokuhyou::GetDocument()
{
	CView* pCView = (CView*)GetParent();
	return (CEkiJikokuhyouDoc*)pCView->GetDocument();
}

const CentDedDia*	CWndDcdGridEkiJikokuhyou::getCentDedDia()
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

const CentDedRessyaCont*	CWndDcdGridEkiJikokuhyou::getCentDedRessyaCont(
	ERessyahoukou eRessyahoukou)
{
	const CentDedDia* pCentDedDia = getCentDedDia();
	if (pCentDedDia == NULL) {
		return (NULL);
	}
	return (pCentDedDia->getCentDedRessyaCont(eRessyahoukou));
};


//int CWndDcdGridEkiJikokuhyou::OnAllOperationTableProp_Process(BOOL bQueryEnable)
//{
//	int iRv = 0;
//	// ****************************************************************
//	//	コマンドの有効・無効判定
//	// ****************************************************************
//	if (iRv >= 0)
//	{
//	}
//	// ****************************************************************
//	if (!bQueryEnable && iRv >= 0)
//	{
//		// ****************************************************************
//		//	コマンドの実行
//		// ****************************************************************
//		CDlgAllOperationTableProp aDlg(
//			m_eOperationSort,
//			m_bCompareBottom,
//			this);
//		if (aDlg.DoModal() == IDOK)
//		{
//			setOperationSort(aDlg.getOperationSort());
//			setCompareBottom(aDlg.getCompareBottom());
//
//			//	EkijikokuSort の設定を、
//			//	.ini ファイルに保存
//			getCDiagramEditApp()->writeCWndDcdGridEkiJikokuhyouViewProp(this);
//
//			iRv = 1;	//	ダイアログボックスでの入力が適用されました。
//		}
//		// ****************************************************************
//		//	エラーメッセージ
//		// ****************************************************************
//
//		// ****************************************************************
//	}
//	return iRv;
//}


//int CWndDcdGridEkiJikokuhyou::OnViewDisplaySecondEkijikoku_Process(
//	BOOL bQueryEnable)
//{
//	int iRv = 0;
//	// ****************************************************************
//	//	コマンドの有効・無効判定
//	// ****************************************************************
//	if (getDisplaySecondEkiJikoku())
//	{
//		iRv = 1;	//(bQueryEnable==TRUEの場合)[秒単位の時刻を表示]が有効です。
//	}
//	// ****************************************************************
//	if (!bQueryEnable && iRv >= 0)
//	{
//		// ****************************************************************
//		//	コマンドを実行
//		// ****************************************************************
//		setDisplaySecondEkiJikoku(!getDisplaySecondEkiJikoku());
//		// ****************************************************************
//		//	エラーメッセージ
//		// ****************************************************************
//
//		// ****************************************************************
//	}
//	return iRv;
//}

int CWndDcdGridEkiJikokuhyou::OnViewDisplayParentSyubetsu_Process(
	BOOL bQueryEnable)
{
	int iRv = 0;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (getDisplayParentSyubetsu())
	{
		iRv = 1;	//(bQueryEnable==TRUEの場合)[親種別を有効にする]が有効です。
	}
	// ****************************************************************
	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドを実行
		// ****************************************************************
		setDisplayParentSyubetsu(!getDisplayParentSyubetsu());
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv;
}

int CWndDcdGridEkiJikokuhyou::OnViewDisplayTrack_Process(
	BOOL bQueryEnable)
{
	int iRv = 0;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (getDisplayTrack())
	{
		iRv = 1;	//(bQueryEnable==TRUEの場合)[発車番線を表示]が有効です。
	}
	// ****************************************************************
	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドを実行
		// ****************************************************************
		setDisplayTrack(!getDisplayTrack());
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv;
}

int CWndDcdGridEkiJikokuhyou::OnViewDisplayIsShihatsu_Process(
	BOOL bQueryEnable)
{
	int iRv = 0;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (getDisplayIsShihatsu())
	{
		iRv = 1;	//(bQueryEnable==TRUEの場合)[当駅始発の列車に●印を表示]が有効です。
	}
	// ****************************************************************
	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドを実行
		// ****************************************************************
		setDisplayIsShihatsu(!getDisplayIsShihatsu());
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv;
}

int CWndDcdGridEkiJikokuhyou::OnViewDisplayClassChange_Process(
	BOOL bQueryEnable)
{
	int iRv = 0;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (getDisplayClassChange())
	{
		iRv = 1;	//(bQueryEnable==TRUEの場合)[種別変更を表示]が有効です。
	}
	// ****************************************************************
	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドを実行
		// ****************************************************************
		setDisplayClassChange(!getDisplayClassChange());
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv;
}


//bool CWndDcdGridEkiJikokuhyou::getDisplaySecondEkiJikoku()const
//{
//	return m_bDisplaySecondEkiJikoku;
//}
//int CWndDcdGridEkiJikokuhyou::setDisplaySecondEkiJikoku(bool value)
//{
//	int iRv = 0;
//	if (m_bDisplaySecondEkiJikoku != value)
//	{
//		m_bDisplaySecondEkiJikoku = value;
//
//		//	秒単位の表示の有無が変化した場合は、
//		//	ビューを更新します。
//		//	ただし、運用更新抑止状態の場合は、ビューの更新は行いません
//
//		if (!getCentDedDia()->getWaitOperationUpdate())
//		{
//			OnUpdate_All();
//			InvalidateGrid();
//		}
//
//		//	秒単位の表示の有無を、
//		//	.ini ファイルに保存
//		getCDiagramEditApp()->writeCWndDcdGridEkiJikokuhyouViewProp(this);
//	}
//	return (iRv);
//}

bool CWndDcdGridEkiJikokuhyou::getDisplayParentSyubetsu()const
{
	return m_bDisplayParentSyubetsu;
}
int CWndDcdGridEkiJikokuhyou::setDisplayParentSyubetsu(bool value)
{
	int iRv = 0;
	if (m_bDisplayParentSyubetsu != value)
	{
		m_bDisplayParentSyubetsu = value;

		//	親種別機能の有効無効が変化した場合は、
		//	ビューを更新します。
		//	ただし、運用更新抑止状態の場合は、ビューの更新は行いません
		if (!getCentDedDia()->getWaitOperationUpdate())
		{
			OnUpdate_All();
			InvalidateGrid();
		}

		//	秒単位の表示の有無を、
		//	.ini ファイルに保存
		getCDiagramEditApp()->writeCWndDcdGridEkiJikokuhyouProp(this);
	}
	return (iRv);
}

bool CWndDcdGridEkiJikokuhyou::getDisplayTrack()const
{
	return m_bDisplayTrack;
}
int CWndDcdGridEkiJikokuhyou::setDisplayTrack(bool value)
{
	int iRv = 0;
	if (m_bDisplayTrack != value)
	{
		m_bDisplayTrack = value;

		//	親種別機能の有効無効が変化した場合は、
		//	ビューを更新します。
		//	ただし、運用更新抑止状態の場合は、ビューの更新は行いません
		if (!getCentDedDia()->getWaitOperationUpdate())
		{
			OnUpdate_All();
			InvalidateGrid();
		}

		//	秒単位の表示の有無を、
		//	.ini ファイルに保存
		getCDiagramEditApp()->writeCWndDcdGridEkiJikokuhyouProp(this);
	}
	return (iRv);
}

bool CWndDcdGridEkiJikokuhyou::getDisplayIsShihatsu()const
{
	return m_bDisplayIsShihatsu;
}
int CWndDcdGridEkiJikokuhyou::setDisplayIsShihatsu(bool value)
{
	int iRv = 0;
	if (m_bDisplayIsShihatsu != value)
	{
		m_bDisplayIsShihatsu = value;

		//	始発列車に印を表示する機能の有効無効が変化した場合は、
		//	ビューを更新します。
		//	ただし、運用更新抑止状態の場合は、ビューの更新は行いません
		if (!getCentDedDia()->getWaitOperationUpdate())
		{
			OnUpdate_All();
			InvalidateGrid();
		}

		//	秒単位の表示の有無を、
		//	.ini ファイルに保存
		getCDiagramEditApp()->writeCWndDcdGridEkiJikokuhyouProp(this);
	}
	return (iRv);
}

bool CWndDcdGridEkiJikokuhyou::getDisplayClassChange()const
{
	return m_bDisplayClassChange;
}
int CWndDcdGridEkiJikokuhyou::setDisplayClassChange(bool value)
{
	int iRv = 0;
	if (m_bDisplayClassChange != value)
	{
		m_bDisplayClassChange = value;

		//	始発列車に印を表示する機能の有効無効が変化した場合は、
		//	ビューを更新します。
		//	ただし、運用更新抑止状態の場合は、ビューの更新は行いません
		if (!getCentDedDia()->getWaitOperationUpdate())
		{
			OnUpdate_All();
			InvalidateGrid();
		}

		//	秒単位の表示の有無を、
		//	.ini ファイルに保存
		getCDiagramEditApp()->writeCWndDcdGridEkiJikokuhyouProp(this);
	}
	return (iRv);
}

// ----------------------------------------------------------------
//	MFC
// ----------------------------------------------------------------
BEGIN_MESSAGE_MAP(CWndDcdGridEkiJikokuhyou,CWndDcdGridEkiJikokuhyou::super)
	//{{AFX_MSG_MAP(CWndDcdGridEkiJikokuhyou)
	ON_WM_CREATE()
	ON_WM_KEYUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KEYDOWN()
	ON_WM_HSCROLL()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
	//ON_COMMAND(ID_AllOperationTableProp, &CWndDcdGridEkiJikokuhyou::OnAllOperationtableProp)
	//ON_UPDATE_COMMAND_UI(ID_AllOperationTableProp, &CWndDcdGridEkiJikokuhyou::OnUpdateAllOperationtableProp)
	ON_COMMAND(ID_EkiJikokuhyou_MoveToJikokuhyou, &CWndDcdGridEkiJikokuhyou::OnEkiJikokuhyouMovetojikokuhyou)
	ON_UPDATE_COMMAND_UI(ID_EkiJikokuhyou_MoveToJikokuhyou, &CWndDcdGridEkiJikokuhyou::OnUpdateEkiJikokuhyouMovetojikokuhyou)
	ON_COMMAND(ID_EkiJikokuhyou_MoveToDiagram, &CWndDcdGridEkiJikokuhyou::OnEkiJikokuhyouMovetodiagram)
	ON_UPDATE_COMMAND_UI(ID_EkiJikokuhyou_MoveToDiagram, &CWndDcdGridEkiJikokuhyou::OnUpdateEkiJikokuhyouMovetodiagram)
	//ON_COMMAND(ID_VIEW_DisplaySecondEkiJikoku, &CWndDcdGridEkiJikokuhyou::OnViewDisplaySecondEkijikoku)
	//ON_UPDATE_COMMAND_UI(ID_VIEW_DisplaySecondEkiJikoku, &CWndDcdGridEkiJikokuhyou::OnUpdateViewDisplaySecondEkijikoku)
	ON_COMMAND(ID_VIEW_DisplayParentSyubetsu, &CWndDcdGridEkiJikokuhyou::OnViewDisplayParentSyubetsu)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DisplayParentSyubetsu, &CWndDcdGridEkiJikokuhyou::OnUpdateViewDisplayParentSyubetsu)
	ON_COMMAND(ID_VIEW_DisplayTrack, &CWndDcdGridEkiJikokuhyou::OnViewDisplayTrack)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DisplayTrack, &CWndDcdGridEkiJikokuhyou::OnUpdateViewDisplayTrack)
	ON_COMMAND(ID_VIEW_DisplayIsShihatsu, &CWndDcdGridEkiJikokuhyou::OnViewDisplayIsShihatsu)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DisplayIsShihatsu, &CWndDcdGridEkiJikokuhyou::OnUpdateViewDisplayIsShihatsu)
	ON_COMMAND(ID_VIEW_DisplayClassChange, &CWndDcdGridEkiJikokuhyou::OnViewDisplayClassChange)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DisplayClassChange, &CWndDcdGridEkiJikokuhyou::OnUpdateViewDisplayClassChange)
	ON_COMMAND(ID_FILE_EXPORT_EKIJIKOKUHYOUCSV, &CWndDcdGridEkiJikokuhyou::OnFileExportEkiJikokuhyoucsv)
	//ON_COMMAND(ID_FILE_EXPORT_ALLOPERATIONTABLECSV, &CWndDcdGridEkiJikokuhyou::OnFileExportAllOperationtablecsv)
END_MESSAGE_MAP()

int CWndDcdGridEkiJikokuhyou::OnCreate(LPCREATESTRUCT lpCreateStruct)
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




void CWndDcdGridEkiJikokuhyou::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
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
		getCDiagramEditApp()->readCWndDcdGridEkiJikokuhyouProp(this);
		CdDedDispProp aCdDedDispProp =
			getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
		m_iSecondRound = aCdDedDispProp.getSecondRoundHatsu();
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
	if ( pCmd != NULL )
	{
		if ( dynamic_castOu<CRfEditCmd_Comment>( pCmd ) || 
			//dynamic_castOu<CRfEditCmd_DiaProp>(pCmd) ||
			dynamic_castOu<CRfEditCmd_RessyasyubetsuSwap>( pCmd ))
		{
			//	このビューは、
			//		コメントの変更
			//		ダイヤの変更
			//		列車種別の入換
			//	の場合は、更新を行いません。
		}
		else if (dynamic_castOu<CRfEditCmd_Ressya>(pCmd))
		{
			const CentDedRosen*	pCentDedRosen =
				getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen();
			int iDiaIndex = pCentDedRosen->getCentDedDiaCont()->findCentDedDiaByName(
				GetDocument()->getDiaName());
			Ou<CRfEditCmd_Ressya>	pCommand =
				dynamic_castOu<CRfEditCmd_Ressya>(pCmd);
			if (pCommand->getDiaIndex() == iDiaIndex && !pCommand->getWaitOperationConnect())
			{
				pHint = NULL;
			}
		}
		else if (dynamic_castOu<CRfEditCmd_Operation>(pCmd))
		{
			const CentDedRosen*	pCentDedRosen =
				getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen();
			int iDiaIndex = pCentDedRosen->getCentDedDiaCont()->findCentDedDiaByName(
				GetDocument()->getDiaName());
			Ou<CRfEditCmd_Operation>	pCommand =
				dynamic_castOu<CRfEditCmd_Operation>(pCmd);
			if (pCommand->getDiaIndex() == iDiaIndex)
			{
				pHint = NULL;
			}
		}
		else if (dynamic_castOu<CRfEditCmd_DiaProp>(pCmd))
		{
			const CentDedRosen* pCentDedRosen =
				getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen();
			int iDiaIndex = pCentDedRosen->getCentDedDiaCont()->findCentDedDiaByName(
				GetDocument()->getDiaName());
			Ou<CRfEditCmd_DiaProp>	pCommand =
				dynamic_castOu<CRfEditCmd_DiaProp>(pCmd);
			if (pCommand->getDiaIndex() == iDiaIndex)
			{
				pHint = NULL;
			}
		}
		else
		{
			//CRfEditCmd_DedRosenFileDataProp
			//	  路線ファイルのプロパティの変更は、
			//	フォントの変化を伴うため、全更新が必要です。
			//CRfEditCmd_Eki
			//CRfEditCmd_RessyaSyubetsu
			//CRfEditCmd_Rosen
			//CRfEditCmd_RosenFileData
			//CRfEditCmd_Dia
			//	列車種別を包含するオブジェクトです。これが更新された場合は、
			//	全更新が必要です。
			pHint = NULL ;
		}
	}
	if ( pHint == NULL )
	{
		// --------------------------------		
		//	全要素を更新
		// --------------------------------
		CView *pView = getCDiagramEditApp()->getCMainFrame()->
			getMDIChildActiveView() ;

		CdDedDispProp aCdDedDispProp =
			getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
		m_iSecondRound = aCdDedDispProp.getSecondRoundHatsu();

		CEkiJikokuhyouDoc* pCEkiJikokuhyouDoc = (CEkiJikokuhyouDoc*)GetDocument();

		if ( GetParent() == pView )
		{
			OnUpdate_All() ;
		}
		else
		{
			LogMsg(_T("CWndDcdGridEkiJikokuhyou::OnUpdate()")
				_T("m_bUpdate_All_Requested=true") ) ;
			m_bUpdate_All_Requested = true ;
		}
	}
	
	int iYColumnBegin = createYColSpecCont().ColumnNumberFromSpec( 
		CdEkiJikokuhyouYColSpec(CdEkiJikokuhyouYColSpec::EColumnType::ColumnType_RessyaSyubetsu, 0 ) ) ;
	
	getCSelect()->setColumnNumberSelectLimit(
		CdDcdZoneXy( 
			CdDcdZone( 0 , INT_MAX ) ,
			CdDcdZone( iYColumnBegin , getCentDedDia()->getcontOperationTableContent().size())
		) );

}

void CWndDcdGridEkiJikokuhyou::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	LogMsg(_T("CWndDcdGridEkiJikokuhyou::OnActivateView(%d,,)") , bActivate ) ;
	
	if ( bActivate && m_bUpdate_All_Requested )
	{
		OnUpdate_All() ;
	}
}

void CWndDcdGridEkiJikokuhyou::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CMenu	aMenu ;
	aMenu.LoadMenu( IDR_MENU_EKIJIKOKUHYOU_CONTEXT ) ;
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

void CWndDcdGridEkiJikokuhyou::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	OnEkiJikokuhyouMovetojikokuhyou_Process(FALSE);
}

void CWndDcdGridEkiJikokuhyou::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
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

void CWndDcdGridEkiJikokuhyou::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	//OnCreate_Header();
	CdEkiJikokuhyouXColSpecCont aXColSpecCont = createXColSpecCont();
	int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdEkiJikokuhyouXColSpec(
		CdEkiJikokuhyouXColSpec::EColumnType::ColumnType_Hour));
	InvalidateCell(iXColumnNumber, YCOLUMNNNO_HEADER);
	super::OnHScroll(nSBCode, nPos, pScrollBar);
}

//void CWndDcdGridEkiJikokuhyou::OnAllOperationtableProp()
//{
//	// TODO: ここにコマンド ハンドラー コードを追加します。
//	OnAllOperationTableProp_Process(FALSE);
//}
//
//
//void CWndDcdGridEkiJikokuhyou::OnUpdateAllOperationtableProp(CCmdUI* pCmdUI)
//{
//	// TODO:ここにコマンド更新 UI ハンドラー コードを追加します。
//	pCmdUI->Enable(OnAllOperationTableProp_Process(TRUE) >= 0);
//}



void CWndDcdGridEkiJikokuhyou::OnEkiJikokuhyouMovetojikokuhyou()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	OnEkiJikokuhyouMovetojikokuhyou_Process(FALSE);
}


void CWndDcdGridEkiJikokuhyou::OnUpdateEkiJikokuhyouMovetojikokuhyou(CCmdUI *pCmdUI)
{
	// TODO:ここにコマンド更新 UI ハンドラー コードを追加します。
	pCmdUI->Enable(OnEkiJikokuhyouMovetojikokuhyou_Process(TRUE) >= 0);
}


void CWndDcdGridEkiJikokuhyou::OnEkiJikokuhyouMovetodiagram()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	OnEkiJikokuhyouMovetodiagram_Process(FALSE);
}


void CWndDcdGridEkiJikokuhyou::OnUpdateEkiJikokuhyouMovetodiagram(CCmdUI *pCmdUI)
{
	// TODO:ここにコマンド更新 UI ハンドラー コードを追加します。
	pCmdUI->Enable(OnEkiJikokuhyouMovetodiagram_Process(TRUE) >= 0);
}

//void CWndDcdGridEkiJikokuhyou::OnViewDisplaySecondEkijikoku()
//{
//	OnViewDisplaySecondEkijikoku_Process(FALSE);
//}
//
//void CWndDcdGridEkiJikokuhyou::OnUpdateViewDisplaySecondEkijikoku(CCmdUI *pCmdUI)
//{
//	int iResult = OnViewDisplaySecondEkijikoku_Process(TRUE);
//	pCmdUI->Enable(iResult >= 0);
//	pCmdUI->SetCheck(iResult >= 1);
//}

void CWndDcdGridEkiJikokuhyou::OnViewDisplayParentSyubetsu()
{
	OnViewDisplayParentSyubetsu_Process(FALSE);
}

void CWndDcdGridEkiJikokuhyou::OnUpdateViewDisplayParentSyubetsu(CCmdUI *pCmdUI)
{
	int iResult = OnViewDisplayParentSyubetsu_Process(TRUE);
	pCmdUI->Enable(iResult >= 0);
	pCmdUI->SetCheck(iResult >= 1);
}

void CWndDcdGridEkiJikokuhyou::OnViewDisplayTrack()
{
	OnViewDisplayTrack_Process(FALSE);
}

void CWndDcdGridEkiJikokuhyou::OnUpdateViewDisplayTrack(CCmdUI* pCmdUI)
{
	int iResult = OnViewDisplayTrack_Process(TRUE);
	pCmdUI->Enable(iResult >= 0);
	pCmdUI->SetCheck(iResult >= 1);
}

void CWndDcdGridEkiJikokuhyou::OnViewDisplayIsShihatsu()
{
	OnViewDisplayIsShihatsu_Process(FALSE);
}

void CWndDcdGridEkiJikokuhyou::OnUpdateViewDisplayIsShihatsu(CCmdUI* pCmdUI)
{
	int iResult = OnViewDisplayIsShihatsu_Process(TRUE);
	pCmdUI->Enable(iResult >= 0);
	pCmdUI->SetCheck(iResult >= 1);
}

void CWndDcdGridEkiJikokuhyou::OnViewDisplayClassChange()
{
	OnViewDisplayClassChange_Process(FALSE);
}

void CWndDcdGridEkiJikokuhyou::OnUpdateViewDisplayClassChange(CCmdUI* pCmdUI)
{
	int iResult = OnViewDisplayClassChange_Process(TRUE);
	pCmdUI->Enable(iResult >= 0);
	pCmdUI->SetCheck(iResult >= 1);
}

void CWndDcdGridEkiJikokuhyou::OnFileExportEkiJikokuhyoucsv()
{
	OnFileExportEkiJikokuhyouCsv_Process(FALSE);
}
//
//void CWndDcdGridEkiJikokuhyou::OnFileExportAllOperationtablecsv()
//{
//	OnFileExportAllOperationTableCsv_Process(FALSE);
//}

} //namespace ViewEkiJikokuhyou