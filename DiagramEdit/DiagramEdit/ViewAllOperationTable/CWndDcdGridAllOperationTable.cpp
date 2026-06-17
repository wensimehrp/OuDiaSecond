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
//	CWndDcdGridAllOperationTable.cpp
//	$Id: CWndDcdGridAllOperationTable.cpp  $
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

#include "..\resource.h"
#include "..\entDed\CentDedRosen.h"
#include "..\entDed\CentDedDia.h"
#include "..\DiagramEdit.h"
#include "..\CRfEditCmdHolder.h"
#include "..\DedRosenFileData\EditCmd\EditCmd.h"
#include "CWndDcdGridAllOperationTable.h"
#include "AllOperationTableColSpec\AllOperationTableColSpec.h"
#include "CDlgOperationTableCsvExport.h"
#include "CDlgAllOperationTableProp.h"
#include "..\ViewOperationTable\COperationTableView.h"
#include "..\ViewDiagram\cdeddiagramview.h"
#include "CconvAllOperationTableCsv.h"
#include "str\CsvDocument\CconvCsvDocument.h"
#include "str\vectorToFile.h"


// ****************************************************************
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
// ****************************************************************

namespace ViewAllOperationTable {
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
	運用一覧ビューのフォントの属性を返します。
*/
static CdFontProp createFontProp()
{
	CdDedDispProp aCdDedDispProp = getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
	return aCdDedDispProp.getOperationTableFont();
	//return aCdDedDispProp.getJikokuhyouFont(0);
	//return ( CConverter_WinGdi().CdFontPropOf( DEFAULT_GUI_FONT ) ) ;
}
/**
@return
	運用一覧ビューの文字の色を返します。
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
	運用一覧ビューの罫線の色を返します。
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
CdAllOperationTableXColSpecCont
CWndDcdGridAllOperationTable::createXColSpecCont()
{
	CdAllOperationTableXColSpecCont aSpecCont(
		getCDiagramEditDoc()->getCDedRosenFileData()
		->getCdDedDispProp().getDisplayRessyamei(),
		m_bDisplayAllRessya,
		m_iMaxRessyaCount);
	return aSpecCont ;
}

CdAllOperationTableYColSpecCont
CWndDcdGridAllOperationTable::createYColSpecCont()
{
	CdAllOperationTableYColSpecCont aSpecCont(
		m_strOperationNumber.size());
	return aSpecCont ;
}

CdAllOperationTableXColSpec
CWndDcdGridAllOperationTable::getXColSpecOfFocus()
{
	CdAllOperationTableXColSpec aSpec ;
	CdDcdPosXy aPos = getCFocus()->getFocusCellColumnNumber() ;
	if ( aPos != getCFocus()->ColumnNumberPosXy_NULL() )
	{
		CdAllOperationTableXColSpecCont aSpecCont(
			getCDiagramEditDoc()->getCDedRosenFileData()
			->getCdDedDispProp().getDisplayRessyamei(),
			m_bDisplayAllRessya,
			m_iMaxRessyaCount);
		aSpec = aSpecCont.ColumnNumberToSpec(aPos.getX());
	}
	return aSpec ;
}

CdAllOperationTableYColSpec
CWndDcdGridAllOperationTable::getYColSpecOfFocus()
{
	CdAllOperationTableYColSpec aSpec ;
	CdDcdPosXy aPos = getCFocus()->getFocusCellColumnNumber() ;
	if ( aPos != getCFocus()->ColumnNumberPosXy_NULL() )
	{
		CdAllOperationTableYColSpecCont aSpecCont(
			m_strOperationNumber.size());
		aSpec = aSpecCont.ColumnNumberToSpec( aPos.getY() ) ;
	}
	return aSpec ;
}
	
	// --------------------------------
	//@name OnUpdate の下請関数
	// --------------------------------

const CdDedJikoku::CConv
CWndDcdGridAllOperationTable::getCdDedJikokuConv()const
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
	//		static CdDedJikoku::CConv aConv(
	//			true,		//	コロン無
	//						// 時が 00 から 09 の場合、10の位の "0" をスペースにします。
	//			CdDedJikoku::CConv::EHour_ZeroToSpace,
	//			CdDedJikoku::CConv::ESecond_Output 	// 秒を表示します
	//		);
	//		return aConv;
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

	CdDedJikoku::CConv::ESecond eSecond = CdDedJikoku::CConv::ESecond_NoSecond;
	if (m_bDisplaySecondEkiJikoku)
	{
		eSecond = CdDedJikoku::CConv::ESecond_Output;
	}

	CdDedJikoku::CConv aConv(
		!m_bDisplayColonEkiJikoku,
		CdDedJikoku::CConv::EHour_ZeroToSpace,
		eSecond,
		(CdDedJikoku::CConv::ESecondRound)m_iSecondRoundChaku,
		(CdDedJikoku::CConv::ESecondRound)m_iSecondRoundHatsu,
		m_bDisplay2400
	);
	return aConv;
}

void CWndDcdGridAllOperationTable::OnUpdate_setOperationTableContent_To_Column(
	int iYColumnNumber ,
	const tstring strOperationNumber,
	const list<OperationTableContent>& ListOperationTableContent)
{
	const Mu<const CentDedRessya*>* pCentDedRessyaConts[2];
	for (int iRessyahoukou = Ressyahoukou_Kudari;
		iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
	{
		pCentDedRessyaConts[iRessyahoukou] = getCentDedRessyaCont((ERessyahoukou)iRessyahoukou)->getMuPtr();
	}


	CdFontProp fontpropDefault = createFontProp() ;
	CdColorProp colorpropDefault = createStringColorProp();
	CdAllOperationTableXColSpecCont aXColSpecCont = createXColSpecCont();

	// --------------------------------
	//	行のY方向サイズを設定
	// --------------------------------
	{
		CDcdTargetGetDC	aCDcdTarget( NULL ) ;

		CdDcdSizeXy	sizeRessyamei ;
		CDcdTextbox	aCDcdTextbox(_T("京都京都京都") ,
			fontpropDefault , 
			_T("") , 1 , 2 , 2 ) ;
		aCDcdTextbox.getItemSize( &aCDcdTarget , &sizeRessyamei) ;

		getCXDcdGrid()->getYColumn( iYColumnNumber )->setColumnSize(sizeRessyamei.getY() ) ;
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

	const OperationTableContent aOperationTableContentOut = ListOperationTableContent.front();
	const OperationTableContent aOperationTableContentIn = ListOperationTableContent.back();

	const CentDedRessya* pCentDedRessyaOut =
		pCentDedRessyaConts[aOperationTableContentOut.aRessyaProperty.getRessyahoukou()]
		->get(aOperationTableContentOut.aRessyaProperty.getRessyaIndex());
	const CentDedRessya* pCentDedRessyaIn =
		pCentDedRessyaConts[aOperationTableContentIn.aRessyaProperty.getRessyahoukou()]
		->get(aOperationTableContentIn.aRessyaProperty.getRessyaIndex());

	const CentDedRessyasyubetsu* pCentDedRessyasyubetsuOut = pCentDedRessyasyubetsuCont
		->getMuPtr()->get(pCentDedRessyaOut->getRessyasyubetsuIndex());
	if (m_bDisplayParentSyubetsu && pCentDedRessyasyubetsuOut->getParentSyubetsuIndex() >= 0)
	{
		pCentDedRessyasyubetsuOut = pCentDedRessyasyubetsuCont
			->getMuPtr()->get(pCentDedRessyasyubetsuOut->getParentSyubetsuIndex());
	}
	const CentDedRessyasyubetsu* pCentDedRessyasyubetsuIn = pCentDedRessyasyubetsuCont
		->getMuPtr()->get(pCentDedRessyaIn->getRessyasyubetsuIndex());
	if (m_bDisplayParentSyubetsu && pCentDedRessyasyubetsuIn->getParentSyubetsuIndex() >= 0)
	{
		pCentDedRessyasyubetsuIn = pCentDedRessyasyubetsuCont
			->getMuPtr()->get(pCentDedRessyasyubetsuIn->getParentSyubetsuIndex());
	}

	tstring strRessyahoukouKudari;
	tstring strRessyahoukouNobori;
	CString strRessyahoukouTemp;
	if (getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getKudariDiaAlias().empty())
	{
		strRessyahoukouTemp.LoadString(IDS_WORD_Kudari);
		strRessyahoukouKudari = (LPCTSTR)strRessyahoukouTemp;
	}
	else
	{
		strRessyahoukouKudari = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getKudariDiaAlias().c_str();
	}
	if (getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getNoboriDiaAlias().empty())
	{
		strRessyahoukouTemp.LoadString(IDS_WORD_Nobori);
		strRessyahoukouNobori = (LPCTSTR)strRessyahoukouTemp;
	}
	else
	{
		strRessyahoukouNobori = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getNoboriDiaAlias().c_str();
	}

	{
		//	列番号
		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
			CdAllOperationTableXColSpec::ColumnType_ColumnNumber));
		Ou<CDcdTextbox> pCDcdTextbox =
			getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
		pCDcdTextbox->
			setText(to_tstring(iYColumnNumber - YCOLUMNNNO_OPERATION_0 + 1));

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
		//	運用番号
		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
			CdAllOperationTableXColSpec::ColumnType_OperationNumber));
		Ou<CDcdTextbox> pCDcdTextbox =
			getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
		pCDcdTextbox->
			setText(strOperationNumber);

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
		//	出区駅名&出区駅時刻
		int iXColumnNumber1 = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
			CdAllOperationTableXColSpec::ColumnType_OutEkimei));
		int iXColumnNumber2 = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
			CdAllOperationTableXColSpec::ColumnType_OutHatsujikoku));
		Ou<CDcdTextbox> pCDcdTextbox1 =
			getCXDcdGrid()->getCell(iXColumnNumber1, iYColumnNumber)->getIfDcDraw();
		Ou<CDcdTextbox> pCDcdTextbox2 =
			getCXDcdGrid()->getCell(iXColumnNumber2, iYColumnNumber)->getIfDcDraw();

		tstring strEkimei;
		CdDedJikoku aCdDedJikoku;
		if (ListOperationTableContent.front().iOuterShihatsuekiIndex != INT_MIN)
		{
			int iOuterTerminalIndex = aOperationTableContentOut.iOuterShihatsuekiIndex;
			strEkimei = pCdDedEkiConts[aOperationTableContentOut.aRessyaProperty.getRessyahoukou()]
				->get(aOperationTableContentOut.iSihatsuEkiOrder).getOuterTerminalEkimei(iOuterTerminalIndex);
			aCdDedJikoku = aOperationTableContentOut.OuterShihatsuJikoku;
		}
		else
		{
			int iSihatsuEkiOrder = aOperationTableContentOut.iSihatsuEkiOrder;
			if (!pCentDedRessyaOut->isRunBetweenNextEki(iSihatsuEkiOrder))
			{
				iSihatsuEkiOrder = pCentDedRessyaOut->getRunBetweenEkiForward(iSihatsuEkiOrder);
			}

			strEkimei = pCdDedEkiConts[aOperationTableContentOut.aRessyaProperty.getRessyahoukou()]
				->get(iSihatsuEkiOrder).getEkimei();
			aCdDedJikoku = pCentDedRessyaOut->getCentDedEkiJikoku(iSihatsuEkiOrder).getHatsujikoku();
		}
		pCDcdTextbox1->setText(strEkimei);
		pCDcdTextbox2->
			setText(getCdDedJikokuConv().encode(aCdDedJikoku, false));

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

		//	セルを無効化
		InvalidateCell(iXColumnNumber1, iYColumnNumber);
		InvalidateCell(iXColumnNumber2, iYColumnNumber);
	}
	{
		//	矢印
		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
			CdAllOperationTableXColSpec::ColumnType_Arrow));
		Ou<CDcdTextbox> pCDcdTextbox =
			getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();

		tstring strArrow = _T("→");
		pCDcdTextbox->setText(strArrow);

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
		//	入区列車始終着駅名&入区列車駅時刻
		int iXColumnNumber1 = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
			CdAllOperationTableXColSpec::ColumnType_InEkimei));
		int iXColumnNumber2 = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
			CdAllOperationTableXColSpec::ColumnType_InChakujikoku));
		Ou<CDcdTextbox> pCDcdTextbox1 =
			getCXDcdGrid()->getCell(iXColumnNumber1, iYColumnNumber)->getIfDcDraw();
		Ou<CDcdTextbox> pCDcdTextbox2 =
			getCXDcdGrid()->getCell(iXColumnNumber2, iYColumnNumber)->getIfDcDraw();

		tstring strEkimei;
		CdDedJikoku aCdDedJikoku;
		if (aOperationTableContentIn.iOuterShuchakuekiIndex != INT_MIN)
		{
			int iOuterTerminalIndex = aOperationTableContentIn.iOuterShuchakuekiIndex;
			strEkimei = pCdDedEkiConts[aOperationTableContentIn.aRessyaProperty.getRessyahoukou()]
				->get(aOperationTableContentIn.iSyuuchakuEkiOrder).getOuterTerminalEkimei(iOuterTerminalIndex);
			aCdDedJikoku = aOperationTableContentIn.OuterShuchakuJikoku;
		}
		else
		{
			int iSyuuchakuEkiOrder = aOperationTableContentIn.iSyuuchakuEkiOrder;
			if (!pCentDedRessyaIn->isRunBetweenNextEki(iSyuuchakuEkiOrder - 1))
			{
				iSyuuchakuEkiOrder = pCentDedRessyaIn->getRunBetweenEkiBackward(iSyuuchakuEkiOrder);
			}

			strEkimei = pCdDedEkiConts[aOperationTableContentIn.aRessyaProperty.getRessyahoukou()]
				->get(iSyuuchakuEkiOrder).getEkimei();
			aCdDedJikoku = pCentDedRessyaIn->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getChakujikoku();
		}
		pCDcdTextbox1->setText(strEkimei);
		pCDcdTextbox2->
			setText(getCdDedJikokuConv().encode(aCdDedJikoku, true));

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

		//	セルを無効化
		InvalidateCell(iXColumnNumber1, iYColumnNumber);
		InvalidateCell(iXColumnNumber2, iYColumnNumber);
	}

	if (m_bDisplayAllRessya)
	{
		int iRessyaIndex = 0;
		int iPropertySameCount = 0;
		for (auto itr = ListOperationTableContent.begin(); itr != ListOperationTableContent.end(); itr++, iRessyaIndex++)
		{
			const CentDedRessya* pCentDedRessya =
				pCentDedRessyaConts[itr->aRessyaProperty.getRessyahoukou()]
				->get(itr->aRessyaProperty.getRessyaIndex());

			const CentDedRessyasyubetsu* pCentDedRessyasyubetsu = pCentDedRessyasyubetsuCont
				->getMuPtr()->get(pCentDedRessya->getRessyasyubetsuIndex());
			if (m_bDisplayParentSyubetsu && pCentDedRessyasyubetsu->getParentSyubetsuIndex() >= 0)
			{
				pCentDedRessyasyubetsu = pCentDedRessyasyubetsuCont
					->getMuPtr()->get(pCentDedRessyasyubetsu->getParentSyubetsuIndex());
			}

			{
				//	列車番号
				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
					CdAllOperationTableXColSpec::ColumnType_Ressyabangou, iRessyaIndex));
				Ou<CDcdTextbox> pCDcdTextbox =
					getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
				pCDcdTextbox->
					setText(pCentDedRessya->getRessyabangou());

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
				//	列車種別
				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
					CdAllOperationTableXColSpec::ColumnType_Ressyasyubetsu, iRessyaIndex));
				Ou<CDcdTextbox> pCDcdTextbox =
					getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();

				//種別のテキスト
				pCDcdTextbox->setText(pCentDedRessyasyubetsu->getSyubetsumei());

				//種別のフォント属性
				CdDrawTextProp	aCdDrawTextProp =
					pCDcdTextbox->getCdDrawTextProp();
				aCdDrawTextProp.setCdFontProp(fontpropDefault);
				{
					aCdDrawTextProp.setTextColor(pCentDedRessyasyubetsu->getJikokuhyouMojiColor());

					int idxFont = pCentDedRessyasyubetsu->getJikokuhyouFontIndex();
					aCdDrawTextProp.setCdFontProp(
						getCDiagramEditDoc()->getCDedRosenFileData()
						->getCdDedDispProp().getJikokuhyouFont(idxFont));
				}
				aCdDrawTextProp.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
				pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);

				//	セルを無効化
				InvalidateCell(iXColumnNumber, iYColumnNumber);
			}
			if (getCDiagramEditDoc()->getCDedRosenFileData()
				->getCdDedDispProp().getDisplayRessyamei())
			{
				//	列車名
				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
					CdAllOperationTableXColSpec::ColumnType_Ressyamei, iRessyaIndex));
				Ou<CDcdTextbox> pCDcdTextbox =
					getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();

				//列車名のテキスト
				tstring strRessyamei = pCentDedRessya->getRessyamei();
				if (!pCentDedRessya->getGousuu().empty())
				{
					strRessyamei += _T(" ");
					strRessyamei += pCentDedRessya->getGousuu();
					strRessyamei += _T("号");
				}
				pCDcdTextbox->setText(strRessyamei);

				//列車名のフォント属性
				CdDrawTextProp	aCdDrawTextProp =
					pCDcdTextbox->getCdDrawTextProp();
				aCdDrawTextProp.setCdFontProp(fontpropDefault);
				{
					aCdDrawTextProp.setTextColor(pCentDedRessyasyubetsu->getJikokuhyouMojiColor());

					int idxFont = pCentDedRessyasyubetsu->getJikokuhyouFontIndex();
					aCdDrawTextProp.setCdFontProp(
						getCDiagramEditDoc()->getCDedRosenFileData()
						->getCdDedDispProp().getJikokuhyouFont(idxFont));
				}
				pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);

				//	セルを無効化
				InvalidateCell(iXColumnNumber, iYColumnNumber);
			}

			{
				//	列車方向
				/**
					列車方向
					全列車表示時の列車方向は、同一列車扱い設定を加味します
					itr列車のAfterTypeがPropertySameの場合、itrnextとして次の列車を読み込み、そのBeforeTypeがPropertySameなら同一列車扱いとなります。
					同一列車扱いの場合は先頭列車の始発駅Indexと末尾列車の終着駅Indexの大小関係で列車方向を決めます。
				*/
				ERessyahoukou eRessyahoukou = pCentDedRessya->getRessyahoukou();
				if (itr->eAfterType == EBeforeAfterType::BeforeAfterType_PropertySame)
				{
					int iSihatsuEkiIndex = pCentDedRessya->EkiIndexOfEkiOrder(itr->iSihatsuEkiOrder);

					int iSyuuchakuEkiIndex = pCentDedRessya->EkiIndexOfEkiOrder(itr->iSyuuchakuEkiOrder);
					auto itrNext = itr;
					do {
						itrNext++;
						if (itrNext == ListOperationTableContent.end() ||
							itrNext->eBeforeType != EBeforeAfterType::BeforeAfterType_PropertySame)
						{
							//次の列車が末尾を超えた場合、もしくは
							//次の列車の前タイプが同一列車扱い以外なら、一体化は無効その前の列車で終了します。
							break;
						}
						else/* if (itrNext->eBeforeType == EBeforeAfterType::BeforeAfterType_PropertySame)*/
						{
							//次の列車の前タイプが同一列車扱いの場合、通常時および箱ダイヤで列車方向一致、終着→始発が駅順の場合は、次の列車は一体化が確定する。

							itr++;
							iPropertySameCount++;
							iSyuuchakuEkiIndex = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
								->getCentDedEkiCont()->EkiIndexOfEkiOrder(itrNext->aRessyaProperty.getRessyahoukou(),
									itrNext->iSyuuchakuEkiOrder);

							if (itrNext->eAfterType == EBeforeAfterType::BeforeAfterType_PropertySame)
							{
								//次の列車の後タイプが同一列車扱いなら、さらに次の列車の検索を行う。
								continue;
							}
							else
							{
								//次の列車の後タイプが同一列車扱い以外なら、この列車が一体化の末尾となる
								break;
							}
						}
					} while (itrNext != ListOperationTableContent.end());

					if (iSihatsuEkiIndex < iSyuuchakuEkiIndex)
					{
						eRessyahoukou = ERessyahoukou::Ressyahoukou_Kudari;
					}
					else if (iSihatsuEkiIndex > iSyuuchakuEkiIndex)
					{
						eRessyahoukou = ERessyahoukou::Ressyahoukou_Nobori;
					}
					//iSihatsuEkiIndex と iSyuuchakuEkiIndex　が同値の場合は、最初の列車の列車方向をそのまま用います
				}
				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
					CdAllOperationTableXColSpec::ColumnType_Ressyahoukou, iRessyaIndex));
				Ou<CDcdTextbox> pCDcdTextbox =
					getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
				tstring strRessyahoukou;
				if (eRessyahoukou == Ressyahoukou_Kudari)
				{
					strRessyahoukou = strRessyahoukouKudari;
				}
				else
				{
					strRessyahoukou = strRessyahoukouNobori;
				}
				pCDcdTextbox->
					setText(strRessyahoukou);

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

			if (iRessyaIndex  < m_iMaxRessyaCount - 1)
			{
				//	矢印
				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
					CdAllOperationTableXColSpec::ColumnType_RessyaArrow, iRessyaIndex));
				Ou<CDcdTextbox> pCDcdTextbox =
					getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();

				if (iRessyaIndex + iPropertySameCount < (int)ListOperationTableContent.size() - 1)
				{
					tstring strArrow = _T("→");
					pCDcdTextbox->setText(strArrow);
				}
				else
				{
					pCDcdTextbox->setText(_T(""));
				}

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
		}
		/**
			列車本数がMaxRessyaCountよりも小さい場合は、空白スペースを埋めます。
		*/
		for (;iRessyaIndex < m_iMaxRessyaCount; iRessyaIndex++)
		{
			{
				//	列車方向
				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
					CdAllOperationTableXColSpec::ColumnType_Ressyahoukou, iRessyaIndex));
				Ou<CDcdTextbox> pCDcdTextbox =
					getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
				pCDcdTextbox->setText(_T(""));
				
				//	セルを無効化
				InvalidateCell(iXColumnNumber, iYColumnNumber);
			}
			{
				//	列車番号
				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
					CdAllOperationTableXColSpec::ColumnType_Ressyabangou, iRessyaIndex));
				Ou<CDcdTextbox> pCDcdTextbox =
					getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
				pCDcdTextbox->setText(_T(""));

				//	セルを無効化
				InvalidateCell(iXColumnNumber, iYColumnNumber);
			}
			{
				//	列車種別
				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
					CdAllOperationTableXColSpec::ColumnType_Ressyasyubetsu, iRessyaIndex));
				Ou<CDcdTextbox> pCDcdTextbox =
					getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
				pCDcdTextbox->setText(_T(""));

				//	セルを無効化
				InvalidateCell(iXColumnNumber, iYColumnNumber);
			}
			if (getCDiagramEditDoc()->getCDedRosenFileData()
				->getCdDedDispProp().getDisplayRessyamei())
			{
				//	列車名
				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
					CdAllOperationTableXColSpec::ColumnType_Ressyamei, iRessyaIndex));
				Ou<CDcdTextbox> pCDcdTextbox =
					getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
				pCDcdTextbox->setText(_T(""));
				
				//	セルを無効化
				InvalidateCell(iXColumnNumber, iYColumnNumber);
			}

			if (iRessyaIndex < m_iMaxRessyaCount - 1)
			{
				//	矢印
				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
					CdAllOperationTableXColSpec::ColumnType_RessyaArrow, iRessyaIndex));
				Ou<CDcdTextbox> pCDcdTextbox =
					getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
				pCDcdTextbox->setText(_T(""));

				//	セルを無効化
				InvalidateCell(iXColumnNumber, iYColumnNumber);
			}
		}
	}
	else
	{
		{
			/**	
				出区列車方向
				先頭列車の次列車接続タイプが同一列車扱いでも、先頭列車の列車方向をそのまま
			*/
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
				CdAllOperationTableXColSpec::ColumnType_Ressyahoukou, 0));
			Ou<CDcdTextbox> pCDcdTextbox =
				getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
			tstring strRessyahoukou;
			if (pCentDedRessyaOut->getRessyahoukou() == Ressyahoukou_Kudari)
			{
				strRessyahoukou = strRessyahoukouKudari;
			}
			else
			{
				strRessyahoukou = strRessyahoukouNobori;
			}
			pCDcdTextbox->
				setText(strRessyahoukou);

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
			//	出区列車番号
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
				CdAllOperationTableXColSpec::ColumnType_Ressyabangou, 0));
			Ou<CDcdTextbox> pCDcdTextbox =
				getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
			pCDcdTextbox->
				setText(pCentDedRessyaOut->getRessyabangou());

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
			//	出区列車種別
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
				CdAllOperationTableXColSpec::ColumnType_Ressyasyubetsu, 0));
			Ou<CDcdTextbox> pCDcdTextbox =
				getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();

			//種別のテキスト
			pCDcdTextbox->setText(pCentDedRessyasyubetsuOut->getSyubetsumei());

			//種別のフォント属性
			CdDrawTextProp	aCdDrawTextProp =
				pCDcdTextbox->getCdDrawTextProp();
			aCdDrawTextProp.setCdFontProp(fontpropDefault);
			{
				aCdDrawTextProp.setTextColor(pCentDedRessyasyubetsuOut->getJikokuhyouMojiColor());

				int idxFont = pCentDedRessyasyubetsuOut->getJikokuhyouFontIndex();
				aCdDrawTextProp.setCdFontProp(
					getCDiagramEditDoc()->getCDedRosenFileData()
					->getCdDedDispProp().getJikokuhyouFont(idxFont));
			}
			aCdDrawTextProp.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
			pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);

			//	セルを無効化
			InvalidateCell(iXColumnNumber, iYColumnNumber);
		}
		if (getCDiagramEditDoc()->getCDedRosenFileData()
			->getCdDedDispProp().getDisplayRessyamei())
		{
			//	出区列車名
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
				CdAllOperationTableXColSpec::ColumnType_Ressyamei, 0));
			Ou<CDcdTextbox> pCDcdTextbox =
				getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();

			//列車名のテキスト
			tstring strRessyamei = pCentDedRessyaOut->getRessyamei();
			if (!pCentDedRessyaOut->getGousuu().empty())
			{
				strRessyamei += _T(" ");
				strRessyamei += pCentDedRessyaOut->getGousuu();
				strRessyamei += _T("号");
			}
			pCDcdTextbox->setText(strRessyamei);

			//列車名のフォント属性
			CdDrawTextProp	aCdDrawTextProp =
				pCDcdTextbox->getCdDrawTextProp();
			aCdDrawTextProp.setCdFontProp(fontpropDefault);
			{
				aCdDrawTextProp.setTextColor(pCentDedRessyasyubetsuOut->getJikokuhyouMojiColor());

				int idxFont = pCentDedRessyasyubetsuOut->getJikokuhyouFontIndex();
				aCdDrawTextProp.setCdFontProp(
					getCDiagramEditDoc()->getCDedRosenFileData()
					->getCdDedDispProp().getJikokuhyouFont(idxFont));
			}
			pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);

			//	セルを無効化
			InvalidateCell(iXColumnNumber, iYColumnNumber);
		}

		{
			//	矢印
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
				CdAllOperationTableXColSpec::ColumnType_RessyaArrow, 0));
			Ou<CDcdTextbox> pCDcdTextbox =
				getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();

			tstring strArrow = _T("→");
			pCDcdTextbox->setText(strArrow);

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

		//入区列車の属性については、同一列車扱いの指定を見ず、末尾列車とする。
		{
			//	入区列車方向
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
				CdAllOperationTableXColSpec::ColumnType_Ressyahoukou, 1));
			Ou<CDcdTextbox> pCDcdTextbox =
				getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
			tstring strRessyahoukou;
			if (pCentDedRessyaIn->getRessyahoukou() == Ressyahoukou_Kudari)
			{
				strRessyahoukou = strRessyahoukouKudari;
			}
			else
			{
				strRessyahoukou = strRessyahoukouNobori;
			}
			pCDcdTextbox->
				setText(strRessyahoukou);

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
			//	入区列車番号
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
				CdAllOperationTableXColSpec::ColumnType_Ressyabangou, 1));
			Ou<CDcdTextbox> pCDcdTextbox =
				getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
			pCDcdTextbox->
				setText(pCentDedRessyaIn->getRessyabangou());

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
			//	入区列車種別
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
				CdAllOperationTableXColSpec::ColumnType_Ressyasyubetsu, 1));
			Ou<CDcdTextbox> pCDcdTextbox =
				getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();

			//種別のテキスト
			pCDcdTextbox->setText(pCentDedRessyasyubetsuIn->getSyubetsumei());

			//種別のフォント属性
			CdDrawTextProp	aCdDrawTextProp =
				pCDcdTextbox->getCdDrawTextProp();
			aCdDrawTextProp.setCdFontProp(fontpropDefault);
			{
				aCdDrawTextProp.setTextColor(pCentDedRessyasyubetsuIn->getJikokuhyouMojiColor());

				int idxFont = pCentDedRessyasyubetsuIn->getJikokuhyouFontIndex();
				aCdDrawTextProp.setCdFontProp(
					getCDiagramEditDoc()->getCDedRosenFileData()
					->getCdDedDispProp().getJikokuhyouFont(idxFont));
			}
			aCdDrawTextProp.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
			pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);

			//	セルを無効化
			InvalidateCell(iXColumnNumber, iYColumnNumber);
		}
		if (getCDiagramEditDoc()->getCDedRosenFileData()
			->getCdDedDispProp().getDisplayRessyamei())
		{
			//	入区列車名
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
				CdAllOperationTableXColSpec::ColumnType_Ressyamei, 1));
			Ou<CDcdTextbox> pCDcdTextbox =
				getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();

			//列車名のテキスト
			tstring strRessyamei = pCentDedRessyaIn->getRessyamei();
			if (!pCentDedRessyaIn->getGousuu().empty())
			{
				strRessyamei += _T(" ");
				strRessyamei += pCentDedRessyaIn->getGousuu();
				strRessyamei += _T("号");
			}
			pCDcdTextbox->setText(strRessyamei);

			//列車名のフォント属性
			CdDrawTextProp	aCdDrawTextProp =
				pCDcdTextbox->getCdDrawTextProp();
			aCdDrawTextProp.setCdFontProp(fontpropDefault);
			{
				aCdDrawTextProp.setTextColor(pCentDedRessyasyubetsuIn->getJikokuhyouMojiColor());

				int idxFont = pCentDedRessyasyubetsuIn->getJikokuhyouFontIndex();
				aCdDrawTextProp.setCdFontProp(
					getCDiagramEditDoc()->getCDedRosenFileData()
					->getCdDedDispProp().getJikokuhyouFont(idxFont));
			}
			pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);

			//	セルを無効化
			InvalidateCell(iXColumnNumber, iYColumnNumber);
		}
	}

}

void CWndDcdGridAllOperationTable::splitOperationNumber(
	const tstring strOperationNumberIn,
	vector<int>& iOperationNumber,
	vector<tstring>& strOperationNumberOut) const
{
	iOperationNumber.clear();
	strOperationNumberOut.clear();
	bool bIsDigit = false;
	bool bIsNotDigit = false;
	tstring strOperationNumberTemp = strOperationNumberIn;
	while (!strOperationNumberTemp.empty())
	{
		int idx = 0;
		if (_istdigit(strOperationNumberTemp[idx]) != 0)
		{
			if ((int)strOperationNumberTemp.size() == 1)
			{
				iOperationNumber.push_back(
					_ttoi(strOperationNumberTemp.c_str()));
				strOperationNumberOut.push_back(tstring());
				break;
			}
			//数字の場合
			bIsDigit = true;
		}
		else
		{
			if ((int)strOperationNumberTemp.size() == 1)
			{
				iOperationNumber.push_back(INT_MIN);
				strOperationNumberOut.push_back(strOperationNumberTemp);
				break;
			}
			//それ以外の場合
			bIsDigit = false;
		}
		idx++;
		for (; idx < (int)strOperationNumberTemp.size(); idx++)
		{
			if (idx == (int)strOperationNumberTemp.size() - 1)
			{
				if (bIsDigit && _istdigit(strOperationNumberTemp[idx]) != 0)
				{
					iOperationNumber.push_back(
						_ttoi(strOperationNumberTemp.c_str()));
					strOperationNumberOut.push_back(tstring());

					strOperationNumberTemp.clear();
					break;
				}
				else if (!bIsDigit && _istdigit(strOperationNumberTemp[idx]) == 0)
				{
					iOperationNumber.push_back(INT_MIN);
					strOperationNumberOut.push_back(strOperationNumberTemp);

					strOperationNumberTemp.clear();
					break;
				}

			}
			if (_istdigit(strOperationNumberTemp[idx]) != 0)
			{
				//idx位置が数字で、先頭が文字の場合
				if (!bIsDigit)
				{
					iOperationNumber.push_back(INT_MIN);
					strOperationNumberOut.push_back(strOperationNumberTemp.substr(0, idx));

					strOperationNumberTemp = strOperationNumberTemp.substr(idx);
					break;
				}
			}
			else
			{
				//idx位置が文字で、先頭が数字の場合
				if (bIsDigit)
				{
					iOperationNumber.push_back(
						_ttoi(strOperationNumberTemp.substr(0, idx).c_str()));
					strOperationNumberOut.push_back(tstring());

					strOperationNumberTemp = strOperationNumberTemp.substr(idx);
					break;
				}
			}
		}
	}
}

bool CWndDcdGridAllOperationTable::SortOperationNumber(
	const tstring strOperationNumber1, 
	const tstring strOperationNumber2)
{
	if (strOperationNumber2.empty())
	{
		return true;
	}
	if (strOperationNumber1.empty())
	{
		return false;
	}


	vector<int> iOperationNumber1;
	vector<int> iOperationNumber2;
	vector<tstring> strOperationNumber1Part;
	vector<tstring> strOperationNumber2Part;
	splitOperationNumber(strOperationNumber1, iOperationNumber1, strOperationNumber1Part);
	splitOperationNumber(strOperationNumber2, iOperationNumber2, strOperationNumber2Part);

	if (m_bCompareBottom)
	{
		int iSize1 = iOperationNumber1.size();
		int iSize2 = iOperationNumber2.size();
		int iMin = min(iSize1, iSize2);
		for (int idx = 1; idx <= iMin; idx++)
		{
			// --------------------------------
			//	- 数字とそれ以外では数字の方が先
			// --------------------------------
			{
				if (iOperationNumber1[iSize1 - idx] != INT_MIN && iOperationNumber2[iSize2 - idx] == INT_MIN)
				{
					return true;
				}
				else if (iOperationNumber1[iSize1 - idx] == INT_MIN && iOperationNumber2[iSize2 - idx] != INT_MIN)
				{
					return false;
				}
			}

			if (iOperationNumber1[iSize1 - idx] == INT_MIN)
			{
				//共に数字以外の場合、文字数→辞書順
				// --------------------------------
				//	- 文字部の長さが短い方が先
				// --------------------------------
				{
					if (strOperationNumber1Part[iSize1 - idx].length() < strOperationNumber2Part[iSize2 - idx].length())
					{
						return true;
					}
					else if (strOperationNumber1Part[iSize1 - idx].length() > strOperationNumber2Part[iSize2 - idx].length())
					{
						return false;
					}
				}
				// --------------------------------
				//	- 文字部が辞書順で早い方が先。
				// --------------------------------
				{
					if (strOperationNumber1Part[iSize1 - idx] < strOperationNumber2Part[iSize2 - idx])
					{
						return true;
					}
					else if (strOperationNumber1Part[iSize1 - idx] > strOperationNumber2Part[iSize2 - idx])
					{
						return false;
					}
				}
			}
			else
			{
				//共に数字の場合、数字の大小
				// --------------------------------
				//	- 数字が小さいものが先
				// --------------------------------
				{
					if (iOperationNumber1[iSize1 - idx] < iOperationNumber2[iSize2 - idx])
					{
						return true;
					}
					else if (iOperationNumber1[iSize1 - idx] > iOperationNumber2[iSize2 - idx])
					{
						return false;
					}
				}
			}

		}
	}
	else
	{
		int iMin = min(iOperationNumber1.size(), iOperationNumber2.size());
		for (int idx = 0; idx < iMin; idx++)
		{
			// --------------------------------
			//	- 数字とそれ以外では数字の方が先
			// --------------------------------
			{
				if (iOperationNumber1[idx] != INT_MIN && iOperationNumber2[idx] == INT_MIN)
				{
					return true;
				}
				else if (iOperationNumber1[idx] == INT_MIN && iOperationNumber2[idx] != INT_MIN)
				{
					return false;
				}
			}

			if (iOperationNumber1[idx] == INT_MIN)
			{
				//共に数字以外の場合、文字数→辞書順
				// --------------------------------
				//	- 文字部の長さが短い方が先
				// --------------------------------
				{
					if (strOperationNumber1Part[idx].length() < strOperationNumber2Part[idx].length())
					{
						return true;
					}
					else if (strOperationNumber1Part[idx].length() > strOperationNumber2Part[idx].length())
					{
						return false;
					}
				}
				// --------------------------------
				//	- 文字部が辞書順で早い方が先。
				// --------------------------------
				{
					if (strOperationNumber1Part[idx] < strOperationNumber2Part[idx])
					{
						return true;
					}
					else if (strOperationNumber1Part[idx] > strOperationNumber2Part[idx])
					{
						return false;
					}
				}
			}
			else
			{
				//共に数字の場合、数字の大小
				// --------------------------------
				//	- 数字が小さいものが先
				// --------------------------------
				{
					if (iOperationNumber1[idx] < iOperationNumber2[idx])
					{
						return true;
					}
					else if (iOperationNumber1[idx] > iOperationNumber2[idx])
					{
						return false;
					}
				}
			}

		}
	}
	// --------------------------------
	//	- 要素数が少ないものが先
	// --------------------------------
	{
		if (iOperationNumber1.size() < iOperationNumber2.size())
		{
			return true;
		}
		else if (iOperationNumber1.size() > iOperationNumber2.size())
		{
			return false;
		}
	}

	return false;
}

bool CWndDcdGridAllOperationTable::SortOperation(
	const tstring strOperationNumber1,
	const int& iEkiIndex1,
	const int& iOuterIndex1,
	const CdDedJikoku& Jikoku1,
	const tstring strOperationNumber2,
	const int& iEkiIndex2,
	const int& iOuterIndex2,
	const CdDedJikoku& Jikoku2,
	const CdDedJikoku& KitenJikoku)
{
	if (strOperationNumber1.empty())
	{
		return false;
	}
	if (m_eOperationSort == EOperationSort_OperationNumber)
	{
		/**
			運用番号順
			運用番号をCompareBottomに基づく順で判定します
			同一の運用番号は無いので、結果は一意に決まります
		*/
		return SortOperationNumber(strOperationNumber1, strOperationNumber2);
	}
	else if (m_eOperationSort == EOperationSort_OutEki ||
		m_eOperationSort == EOperationSort_InEki)
	{
		/**
			出区駅順
			(1)出区駅順
			(2)発時刻順
			(3)運用番号順で並べます
			(1)出区駅順は、分岐駅の場合iPosition=0の駅に集約します。
				また、路線外始発の場合、純粋な出区よりも後になり、
				路線外始発同士の場合、路線外始発駅Indexが小さいものが先になります
			(2)出区駅が一致している場合、発時刻順で並べます。
				なお、路線外始発駅が一致している場合は、路線外始発駅発時刻で比較します
			(3)出区駅（路線外始発駅）、発時刻が一致している場合は、運用番号順で並べます。
		*/

		if (iEkiIndex1 < iEkiIndex2)
		{
			return true;
		}
		else if (iEkiIndex1 > iEkiIndex2)
		{
			return false;
		}

		if (iOuterIndex1 < iOuterIndex2)
		{
			return true;
		}
		else if (iOuterIndex1 > iOuterIndex2)
		{
			return false;
		}

		if (Jikoku1.compare(Jikoku2, KitenJikoku) < 0)
		{
			return true;
		}
		else if (Jikoku1.compare(Jikoku2, KitenJikoku) > 0)
		{
			return false;
		}

		return SortOperationNumber(strOperationNumber1, strOperationNumber2);
	}
	else if (m_eOperationSort == EOperationSort_OutJikoku ||
	m_eOperationSort == EOperationSort_InJikoku)
	{
	/**
		発時刻順
		(1)発時刻順
		(2)運用番号順で並べます。
		(1)発時刻順は、路線外始発の場合、路線外始発駅発時刻を用いて比較します
	*/

	if (Jikoku1.compare(Jikoku2, KitenJikoku) < 0)
	{
		return true;
	}
	else if (Jikoku1.compare(Jikoku2, KitenJikoku) > 0)
	{
		return false;
	}

	return SortOperationNumber(strOperationNumber1, strOperationNumber2);
	}
	return false;
}


void  CWndDcdGridAllOperationTable::OnUpdate_All()
{
	CWaitCursor	aCWaitCursor;

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

		unordered_map<tstring, list<OperationTableContent>> contOperationTableContent =
			getCentDedDia()->getcontOperationTableContent();

		const CentDedEkiCont* pCentDedEkiCont = getCDiagramEditDoc()->
			getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont();
		const Mu<const CentDedRessya*>* pCentDedRessyaConts[2];
		for (int iRessyahoukou = Ressyahoukou_Kudari;
			iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
		{
			pCentDedRessyaConts[iRessyahoukou] = getCentDedRessyaCont((ERessyahoukou)iRessyahoukou)->getMuPtr();
		}
		const CdDedJikoku KitenJikoku = getCDiagramEditDoc()->getCDedRosenFileData()
			->getCentDedRosen()->getKitenJikoku();

		m_strOperationNumber.clear();
		vector<int> iEkiIndexCont;
		vector<int> iOuterIndexCont;
		vector<CdDedJikoku> JikokuCont;


		int iMaxRessyaCount = 0;
		for (auto itr = contOperationTableContent.begin();
			itr != contOperationTableContent.end(); itr++)
		{
			/**
				次列車接続タイプを考慮した、運用中の列車本数を求めます。
			*/
			list<OperationTableContent>& listOperationTableContent = itr->second;
			int iRessyaCount = (int)itr->second.size();
			for (auto itrOTC = listOperationTableContent.begin(); itrOTC != listOperationTableContent.end(); itrOTC++)
			{
				//itrOTCとその次の列車の前次列車接続タイプを見て、共に同一列車扱いの場合は、iRessyaCountを一つ減算します
				if (itrOTC->eAfterType != EBeforeAfterType::BeforeAfterType_PropertySame)
				{
					continue;
				}
				auto itrOTCNext = itrOTC;
				itrOTCNext++;
				if (itrOTCNext != listOperationTableContent.end() &&
					itrOTCNext->eBeforeType == EBeforeAfterType::BeforeAfterType_PropertySame)
				{
					iRessyaCount--;
				}
			}
			if (iRessyaCount > iMaxRessyaCount)
			{
				iMaxRessyaCount = iRessyaCount;
			}

			int iEkiIndexTemp;
			int iOuterIndexTemp;
			CdDedJikoku JikokuTemp;
			if (m_eOperationSort == EOperationSort_OutEki)
			{
				OperationTableContent aShihatsuOperationTableContent = itr->second.front();
				iEkiIndexTemp = pCentDedEkiCont->EkiIndexOfEkiOrder(
					aShihatsuOperationTableContent.aRessyaProperty.getRessyahoukou(),
					aShihatsuOperationTableContent.iSihatsuEkiOrder);
				const CentDedEki* pSihatsuEki = pCentDedEkiCont->getMuPtr()->get(iEkiIndexTemp);

				if (pSihatsuEki->getBrunchLoopPosition() != -1)
				{
					iEkiIndexTemp = pSihatsuEki->getEkiIndexLoop().front();
				}
				iOuterIndexTemp = aShihatsuOperationTableContent.iOuterShihatsuekiIndex;
				if (iOuterIndexTemp != INT_MIN)
				{
					JikokuTemp = aShihatsuOperationTableContent.OuterShihatsuJikoku;
				}
				else
				{
					int iSihatsuEkiOrder = aShihatsuOperationTableContent.iSihatsuEkiOrder;
					const CentDedRessya* pCentDedRessya =
						pCentDedRessyaConts[aShihatsuOperationTableContent.aRessyaProperty.getRessyahoukou()]
						->get(aShihatsuOperationTableContent.aRessyaProperty.getRessyaIndex());

					if (!pCentDedRessya->isRunBetweenNextEki(iSihatsuEkiOrder))
					{
						iSihatsuEkiOrder = pCentDedRessya->getRunBetweenEkiForward(iSihatsuEkiOrder);
					}

					JikokuTemp = pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getHatsujikoku();
				}
			}
			else if (m_eOperationSort == EOperationSort_OutJikoku)
			{
				OperationTableContent aShihatsuOperationTableContent = itr->second.front();
				if (aShihatsuOperationTableContent.iOuterShihatsuekiIndex != INT_MIN)
				{
					JikokuTemp = aShihatsuOperationTableContent.OuterShihatsuJikoku;
				}
				else
				{
					int iSihatsuEkiOrder = aShihatsuOperationTableContent.iSihatsuEkiOrder;
					const CentDedRessya* pCentDedRessya =
						pCentDedRessyaConts[aShihatsuOperationTableContent.aRessyaProperty.getRessyahoukou()]
						->get(aShihatsuOperationTableContent.aRessyaProperty.getRessyaIndex());

					if (!pCentDedRessya->isRunBetweenNextEki(iSihatsuEkiOrder))
					{
						iSihatsuEkiOrder = pCentDedRessya->getRunBetweenEkiForward(iSihatsuEkiOrder);
					}

					JikokuTemp = pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getHatsujikoku();
				}
			}
			else if (m_eOperationSort == EOperationSort_InEki)
			{
				OperationTableContent aSyuchakuOperationTableContent = itr->second.back();
				iEkiIndexTemp = pCentDedEkiCont->EkiIndexOfEkiOrder(
					aSyuchakuOperationTableContent.aRessyaProperty.getRessyahoukou(),
					aSyuchakuOperationTableContent.iSyuuchakuEkiOrder);
				const CentDedEki* pSyuchakuEki = pCentDedEkiCont->getMuPtr()->get(iEkiIndexTemp);

				if (pSyuchakuEki->getBrunchLoopPosition() != -1)
				{
					iEkiIndexTemp = pSyuchakuEki->getEkiIndexLoop().front();
				}
				iOuterIndexTemp = aSyuchakuOperationTableContent.iOuterShuchakuekiIndex;
				if (iOuterIndexTemp != INT_MIN)
				{
					JikokuTemp = aSyuchakuOperationTableContent.OuterShuchakuJikoku;
				}
				else
				{
					int iSyuuchakuEkiOrder = aSyuchakuOperationTableContent.iSyuuchakuEkiOrder;
					const CentDedRessya* pCentDedRessya =
						pCentDedRessyaConts[aSyuchakuOperationTableContent.aRessyaProperty.getRessyahoukou()]
						->get(aSyuchakuOperationTableContent.aRessyaProperty.getRessyaIndex());

					if (!pCentDedRessya->isRunBetweenNextEki(iSyuuchakuEkiOrder - 1))
					{
						iSyuuchakuEkiOrder = pCentDedRessya->getRunBetweenEkiBackward(iSyuuchakuEkiOrder);
					}

					JikokuTemp = pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getChakujikoku();
				}
			}
			else if (m_eOperationSort == EOperationSort_InJikoku)
			{
				OperationTableContent aSyuchakuOperationTableContent = itr->second.back();
				if (aSyuchakuOperationTableContent.iOuterShuchakuekiIndex != INT_MIN)
				{
					JikokuTemp = aSyuchakuOperationTableContent.OuterShuchakuJikoku;
				}
				else
				{
					int iSyuuchakuEkiOrder = aSyuchakuOperationTableContent.iSyuuchakuEkiOrder;
					const CentDedRessya* pCentDedRessya =
						pCentDedRessyaConts[aSyuchakuOperationTableContent.aRessyaProperty.getRessyahoukou()]
						->get(aSyuchakuOperationTableContent.aRessyaProperty.getRessyaIndex());

					if (!pCentDedRessya->isRunBetweenNextEki(iSyuuchakuEkiOrder - 1))
					{
						iSyuuchakuEkiOrder = pCentDedRessya->getRunBetweenEkiBackward(iSyuuchakuEkiOrder);
					}

					JikokuTemp = pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getChakujikoku();
				}
			}

			bool bInsert = false;
			for (int idx = 0; idx < (int)m_strOperationNumber.size(); idx++)
			{
				if (SortOperation(itr->first,iEkiIndexTemp, 
					iOuterIndexTemp, JikokuTemp,
					m_strOperationNumber[idx],iEkiIndexCont[idx], 
					iOuterIndexCont[idx], JikokuCont[idx],
					KitenJikoku))
				{
					m_strOperationNumber.insert(m_strOperationNumber.begin() + idx, itr->first);
					iEkiIndexCont.insert(iEkiIndexCont.begin() + idx, iEkiIndexTemp);
					iOuterIndexCont.insert(iOuterIndexCont.begin() + idx, iOuterIndexTemp);
					JikokuCont.insert(JikokuCont.begin() + idx, JikokuTemp);
					bInsert = true;
					break;
				}
			}
			if (!bInsert)
			{
				m_strOperationNumber.push_back(itr->first);
				iEkiIndexCont.push_back(iEkiIndexTemp);
				iOuterIndexCont.push_back(iOuterIndexTemp);
				JikokuCont.push_back(JikokuTemp);
			}
		}
		m_iMaxRessyaCount = iMaxRessyaCount;

		//	X列数を増減させる
		//CdAllOperationTableXColSpecCont aXColSpecCont = createXColSpecCont();
		//int iXCount = getCXDcdGrid()->getXColumnCount();
		//if (iXCount != aXColSpecCont.size())
		//{
			//フォント変更の場合、ヘッダー更新する必要があるので、全更新時は常に更新するようにする。
			OnCreate_Header();
		//}

		getCXDcdGrid()->setYColumnCount(
			contOperationTableContent.size() + YCOLUMNNNO_OPERATION_0);

			//	各セルに、データを設定
		for (int idxOperation = 0; idxOperation < (int)m_strOperationNumber.size(); idxOperation++)
		{
			OnUpdate_setOperationTableContent_To_Column(
				idxOperation + YCOLUMNNNO_OPERATION_0,
				m_strOperationNumber[idxOperation],
				contOperationTableContent[m_strOperationNumber[idxOperation]]);
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

void CWndDcdGridAllOperationTable::OnCreate_Header()
{
	// --------------------------------
	//	運用表ビューに使用するフォント
	// --------------------------------
	CdFontProp fontpropDefault = createFontProp();
	CdColorProp colorpropDefault = createStringColorProp();

	CdAllOperationTableXColSpecCont aXColSpecCont = createXColSpecCont();
	// --------------------------------
	//	列の数を指定
	// --------------------------------

	getCXDcdGrid()->setXColumnCount(aXColSpecCont.size());
	getCXDcdGrid()->setXFixColumnCount(aXColSpecCont.ColumnNumberFromSpec(
		CdAllOperationTableXColSpec::ColumnType_InChakujikoku) + 1);

	bool bDisplayRessyamei = getCDiagramEditDoc()->getCDedRosenFileData()
		->getCdDedDispProp().getDisplayRessyamei();

	// --------------------------------
	//	列のサイズを設定
	// --------------------------------
	{
		CDcdTargetGetDC	aCDcdTarget(NULL);
		// --------------------------------
		//	X列
		// --------------------------------
		tstring strCellRessyaBangouWidth(
			getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp().getJikokuhyouRessyaWidth(), '0');
		if (strCellRessyaBangouWidth.length() < 8)
		{
			strCellRessyaBangouWidth = tstring(8, '0');
		}
		tstring strCellEkijikokuWidth(
			getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp().getJikokuhyouRessyaWidth(), '0');
		if (strCellEkijikokuWidth.length() < 6)
		{
			strCellEkijikokuWidth = tstring(6, '0');
		}
		tstring strCellEkimeiLength(
			getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp().getEkimeiLength() * 2, '0');
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
		//CString strCRessyahoukou;
		//strCRessyahoukou.LoadString(IDS_WORD_Kudari);
		//tstring strRessyahoukou = (LPCTSTR)strCRessyahoukou;
		tstring strRessyahoukou = _T("出区列車");
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
		{
			//	列番号
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
				CdAllOperationTableXColSpec::ColumnType_ColumnNumber));
			CdDcdSizeXy	sizeOperationTable;
			CDcdTextbox	aCDcdTextbox(
				_T("000") ,
				fontpropDefault,
				_T(""), 1, 2, 2);
			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeOperationTable);
			getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeOperationTable.getX());
		}
		{
			//	運用番号
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
				CdAllOperationTableXColSpec::ColumnType_OperationNumber));
			CdDcdSizeXy	sizeOperationTable;
			CDcdTextbox	aCDcdTextbox(
				strCellRessyaBangouWidth,
				//"0" ,
				fontpropDefault,
				_T(""), 1, 2, 2);
			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeOperationTable);
			getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeOperationTable.getX());
		}
		{
			//	出区入区始終着駅名
			int iXColumnNumber1 = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
				CdAllOperationTableXColSpec::ColumnType_OutEkimei));
			int iXColumnNumber2 = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
				CdAllOperationTableXColSpec::ColumnType_InEkimei));
			CdDcdSizeXy	sizeOperationTable;

			CDcdTextbox	aCDcdTextbox(
				strCellEkimeiLength,
				//"京都京都京都",
				fontpropDefault,
				_T(""), 1, 2, 2);
			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeOperationTable);

			getCXDcdGrid()->getXColumn(iXColumnNumber1)->setColumnSize(sizeOperationTable.getX());
			getCXDcdGrid()->getXColumn(iXColumnNumber2)->setColumnSize(sizeOperationTable.getX());
		}
		{
			//	出区入区駅時刻
			int iXColumnNumber1 = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
				CdAllOperationTableXColSpec::ColumnType_OutHatsujikoku));
			int iXColumnNumber2 = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
				CdAllOperationTableXColSpec::ColumnType_InChakujikoku));
			CdDcdSizeXy	sizeOperationTable;

			CDcdTextbox	aCDcdTextbox(
				strCellEkijikokuWidth,
				//"京都京都京都",
				fontpropDefault,
				_T(""), 1, 2, 2);
			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeOperationTable);

			getCXDcdGrid()->getXColumn(iXColumnNumber1)->setColumnSize(sizeOperationTable.getX());
			getCXDcdGrid()->getXColumn(iXColumnNumber2)->setColumnSize(sizeOperationTable.getX());
		}
		{
			//	矢印
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
				CdAllOperationTableXColSpec::ColumnType_Arrow));
			CdDcdSizeXy	sizeOperationTable;

			CDcdTextbox	aCDcdTextbox(
				_T("京都"),
				fontpropDefault,
				_T(""), 1, 2, 2);
			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeOperationTable);

			getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeOperationTable.getX());
		}

		if (m_bDisplayAllRessya)
		{
			for (int idx = 0; idx < m_iMaxRessyaCount; idx++)
			{
				{
					//	列車方向
					int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
						CdAllOperationTableXColSpec::ColumnType_Ressyahoukou, idx));
					CdDcdSizeXy	sizeOperationTable;
					CDcdTextbox	aCDcdTextbox(
						strRessyahoukou,
						fontpropDefault,
						_T(""), 1, 2, 2);
					aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeOperationTable);
					getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeOperationTable.getX());
				}
				{
					//	列車番号
					int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
						CdAllOperationTableXColSpec::ColumnType_Ressyabangou, idx));
					CdDcdSizeXy	sizeOperationTable;
					CDcdTextbox	aCDcdTextbox(
						strCellRessyaBangouWidth,
						//"0" ,
						fontpropDefault,
						_T(""), 1, 2, 2);
					aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeOperationTable);
					getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeOperationTable.getX());
				}
				{
					//	出区入区種別
					int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
						CdAllOperationTableXColSpec::ColumnType_Ressyasyubetsu, idx));
					CdDcdSizeXy	sizeOperationTable;
					CDcdTextbox	aCDcdTextbox(
						strCellRessyasyubetsuWidth,
						fontpropDefault,
						_T(""), 1, 2, 2);
					aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeOperationTable);
					getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeOperationTable.getX());
				}
				if (getCDiagramEditDoc()->getCDedRosenFileData()
					->getCdDedDispProp().getDisplayRessyamei())
				{
					//	出区入区列車名
					int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
						CdAllOperationTableXColSpec::ColumnType_Ressyamei, idx));
					CdDcdSizeXy	sizeOperationTable;

					CDcdTextbox	aCDcdTextbox(
						_T("京都京都京都京都京都京都"),
						fontpropDefault,
						_T(""), 1, 2, 2);
					aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeOperationTable);

					getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeOperationTable.getX());
				}
				if (idx < m_iMaxRessyaCount - 1)
				{
					//	矢印
					int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
						CdAllOperationTableXColSpec::ColumnType_RessyaArrow, idx));
					CdDcdSizeXy	sizeOperationTable;

					CDcdTextbox	aCDcdTextbox(
						_T("京都"),
						fontpropDefault,
						_T(""), 1, 2, 2);
					aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeOperationTable);

					getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeOperationTable.getX());
				}
			}
		}
		else
		{
			{
				//	出区入区列車方向
				int iXColumnNumber1 = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
					CdAllOperationTableXColSpec::ColumnType_Ressyahoukou, 0));
				int iXColumnNumber2 = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
					CdAllOperationTableXColSpec::ColumnType_Ressyahoukou, 1));
				CdDcdSizeXy	sizeOperationTable;
				CDcdTextbox	aCDcdTextbox(
					strRessyahoukou,
					fontpropDefault,
					_T(""), 1, 2, 2);
				aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeOperationTable);
				getCXDcdGrid()->getXColumn(iXColumnNumber1)->setColumnSize(sizeOperationTable.getX());
				getCXDcdGrid()->getXColumn(iXColumnNumber2)->setColumnSize(sizeOperationTable.getX());
			}
			{
				//	出区入区列車番号
				int iXColumnNumber1 = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
					CdAllOperationTableXColSpec::ColumnType_Ressyabangou, 0));
				int iXColumnNumber2 = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
					CdAllOperationTableXColSpec::ColumnType_Ressyabangou, 1));
				CdDcdSizeXy	sizeOperationTable;
				CDcdTextbox	aCDcdTextbox(
					strCellRessyaBangouWidth,
					//"0" ,
					fontpropDefault,
					_T(""), 1, 2, 2);
				aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeOperationTable);
				getCXDcdGrid()->getXColumn(iXColumnNumber1)->setColumnSize(sizeOperationTable.getX());
				getCXDcdGrid()->getXColumn(iXColumnNumber2)->setColumnSize(sizeOperationTable.getX());
			}
			{
				//	出区入区種別
				int iXColumnNumber1 = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
					CdAllOperationTableXColSpec::ColumnType_Ressyasyubetsu, 0));
				int iXColumnNumber2 = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
					CdAllOperationTableXColSpec::ColumnType_Ressyasyubetsu, 1));
				CdDcdSizeXy	sizeOperationTable;
				CDcdTextbox	aCDcdTextbox(
					strCellRessyasyubetsuWidth,
					fontpropDefault,
					_T(""), 1, 2, 2);
				aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeOperationTable);
				getCXDcdGrid()->getXColumn(iXColumnNumber1)->setColumnSize(sizeOperationTable.getX());
				getCXDcdGrid()->getXColumn(iXColumnNumber2)->setColumnSize(sizeOperationTable.getX());
			}
			if (getCDiagramEditDoc()->getCDedRosenFileData()
				->getCdDedDispProp().getDisplayRessyamei())
			{
				//	出区入区列車名
				int iXColumnNumber1 = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
					CdAllOperationTableXColSpec::ColumnType_Ressyamei, 0));
				int iXColumnNumber2 = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
					CdAllOperationTableXColSpec::ColumnType_Ressyamei, 1));
				CdDcdSizeXy	sizeOperationTable;

				CDcdTextbox	aCDcdTextbox(
					_T("京都京都京都京都京都京都"),
					fontpropDefault,
					_T(""), 1, 2, 2);
				aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeOperationTable);

				getCXDcdGrid()->getXColumn(iXColumnNumber1)->setColumnSize(sizeOperationTable.getX());
				getCXDcdGrid()->getXColumn(iXColumnNumber2)->setColumnSize(sizeOperationTable.getX());
			}
			{
				//	矢印
				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
					CdAllOperationTableXColSpec::ColumnType_RessyaArrow, 0));
				CdDcdSizeXy	sizeOperationTable;

				CDcdTextbox	aCDcdTextbox(
					_T("京都"),
					fontpropDefault,
					_T(""), 1, 2, 2);
				aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeOperationTable);

				getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeOperationTable.getX());
			}
		}
		// --------------------------------
		//	Y列
		// --------------------------------
		{
			CdDcdSizeXy	sizeOperationTable;
			CDcdTextbox	aCDcdTextbox(
				_T("京都京都京都京都京都京都"),
				fontpropDefault,
				_T(""), 1, 2, 2);
			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeOperationTable);

			getCXDcdGrid()->getYColumn(YCOLUMNNNO_HEADER)->setColumnSize(sizeOperationTable.getY());
		}
	}
	// --------------------------------
	//	最上列に属性とテキストを設定
	// --------------------------------
	{
		// 列番号
		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
			CdAllOperationTableXColSpec::ColumnType_ColumnNumber));

		Ou<CDcdTextbox>	pCDcdTextbox =
			getCXDcdGrid()->getCell(iXColumnNumber, YCOLUMNNNO_HEADER)->getIfDcDraw();

		CConverter_WinGdi aCConverter_WinGdi;

		CdDrawTextProp	aCdDrawTextProp(
			fontpropDefault,
			colorpropDefault);
			//aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENUTEXT));
		CdBrushProp	aCdBrushProp(
			aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENU));

		pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
		pCDcdTextbox->setCdBrushProp(aCdBrushProp);
		pCDcdTextbox->setText(_T(""));
	}
	{
		// 運用番号
		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
			CdAllOperationTableXColSpec::ColumnType_OperationNumber));
		CString	aString;
		aString = _T("運用番号");

		Ou<CDcdTextbox>	pCDcdTextbox =
			getCXDcdGrid()->getCell(iXColumnNumber, YCOLUMNNNO_HEADER)->getIfDcDraw();

		CConverter_WinGdi aCConverter_WinGdi;

		CdDrawTextProp	aCdDrawTextProp(
			fontpropDefault,
			colorpropDefault);
			//aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENUTEXT));
		CdBrushProp	aCdBrushProp(
			aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENU));

		pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
		pCDcdTextbox->setCdBrushProp(aCdBrushProp);
		pCDcdTextbox->setText((LPCTSTR)aString);
	}
	{
		// 出区駅名
		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
			CdAllOperationTableXColSpec::ColumnType_OutEkimei));
		CString	aString;
		aString = _T("出区駅名");

		Ou<CDcdTextbox>	pCDcdTextbox =
			getCXDcdGrid()->getCell(iXColumnNumber, YCOLUMNNNO_HEADER)->getIfDcDraw();

		CConverter_WinGdi aCConverter_WinGdi;

		CdDrawTextProp	aCdDrawTextProp(
			fontpropDefault,
			colorpropDefault);
			//aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENUTEXT));
		CdBrushProp	aCdBrushProp(
			aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENU));

		pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
		pCDcdTextbox->setCdBrushProp(aCdBrushProp);
		pCDcdTextbox->setText((LPCTSTR)aString);
		Ou<CDcdLine>
			(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())
			->setCdPenProp(getCdPenPropDotLine());
	}
	{
		// 発時刻
		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
			CdAllOperationTableXColSpec::ColumnType_OutHatsujikoku));
		CString	aString;
		aString = _T("発時刻");

		Ou<CDcdTextbox>	pCDcdTextbox =
			getCXDcdGrid()->getCell(iXColumnNumber, YCOLUMNNNO_HEADER)->getIfDcDraw();

		CConverter_WinGdi aCConverter_WinGdi;

		CdDrawTextProp	aCdDrawTextProp(
			fontpropDefault,
			colorpropDefault);
			//aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENUTEXT));
		CdBrushProp	aCdBrushProp(
			aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENU));

		pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
		pCDcdTextbox->setCdBrushProp(aCdBrushProp);
		pCDcdTextbox->setText((LPCTSTR)aString);
	}
	{
		// 矢印
		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
			CdAllOperationTableXColSpec::ColumnType_Arrow));

		Ou<CDcdTextbox>	pCDcdTextbox =
			getCXDcdGrid()->getCell(iXColumnNumber, YCOLUMNNNO_HEADER)->getIfDcDraw();

		CConverter_WinGdi aCConverter_WinGdi;

		CdDrawTextProp	aCdDrawTextProp(
			fontpropDefault,
			colorpropDefault);
			//aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENUTEXT));
		CdBrushProp	aCdBrushProp(
			aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENU));

		pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
		pCDcdTextbox->setCdBrushProp(aCdBrushProp);
		pCDcdTextbox->setText(_T(""));
	}
	{
		// 入区駅名
		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
			CdAllOperationTableXColSpec::ColumnType_InEkimei));
		CString	aString;
		aString = _T("入区駅名");

		Ou<CDcdTextbox>	pCDcdTextbox =
			getCXDcdGrid()->getCell(iXColumnNumber, YCOLUMNNNO_HEADER)->getIfDcDraw();

		CConverter_WinGdi aCConverter_WinGdi;

		CdDrawTextProp	aCdDrawTextProp(
			fontpropDefault,
			colorpropDefault);
			//aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENUTEXT));
		CdBrushProp	aCdBrushProp(
			aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENU));

		pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
		pCDcdTextbox->setCdBrushProp(aCdBrushProp);
		pCDcdTextbox->setText((LPCTSTR)aString);
		Ou<CDcdLine>
			(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())
			->setCdPenProp(getCdPenPropDotLine());
	}
	{
		// 着時刻
		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
			CdAllOperationTableXColSpec::ColumnType_InChakujikoku));
		CString	aString;
		aString = _T("着時刻");

		Ou<CDcdTextbox>	pCDcdTextbox =
			getCXDcdGrid()->getCell(iXColumnNumber, YCOLUMNNNO_HEADER)->getIfDcDraw();

		CConverter_WinGdi aCConverter_WinGdi;

		CdDrawTextProp	aCdDrawTextProp(
			fontpropDefault,
			colorpropDefault);
			//aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENUTEXT));
		CdBrushProp	aCdBrushProp(
			aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENU));

		pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
		pCDcdTextbox->setCdBrushProp(aCdBrushProp);
		pCDcdTextbox->setText((LPCTSTR)aString);

		Ou<CDcdLine>
			(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())
			->setCdPenProp(getCdPenPropBoldLine());
	}

	if (m_bDisplayAllRessya)
	{
		for (int idx = 0; idx < m_iMaxRessyaCount; idx++)
		{
			{
				// 列車方向
				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
					CdAllOperationTableXColSpec::ColumnType_Ressyahoukou, idx));

				Ou<CDcdTextbox>	pCDcdTextbox =
					getCXDcdGrid()->getCell(iXColumnNumber, YCOLUMNNNO_HEADER)->getIfDcDraw();

				CConverter_WinGdi aCConverter_WinGdi;

				CdDrawTextProp	aCdDrawTextProp(
					fontpropDefault,
					colorpropDefault);
					//aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENUTEXT));
				aCdDrawTextProp.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
				CdBrushProp	aCdBrushProp(
					aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENU));

				pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
				pCDcdTextbox->setCdBrushProp(aCdBrushProp);
				pCDcdTextbox->setText(to_tstring(idx + 1));

				Ou<CDcdLine>
					(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())
					->setCdPenProp(getCdPenPropDotLine());
			}
			{
				// 列車番号
				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
					CdAllOperationTableXColSpec::ColumnType_Ressyabangou, idx));

				Ou<CDcdTextbox>	pCDcdTextbox =
					getCXDcdGrid()->getCell(iXColumnNumber, YCOLUMNNNO_HEADER)->getIfDcDraw();

				CConverter_WinGdi aCConverter_WinGdi;

				CdDrawTextProp	aCdDrawTextProp(
					fontpropDefault,
					colorpropDefault);
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
				// 種別名
				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
					CdAllOperationTableXColSpec::ColumnType_Ressyasyubetsu, idx));

				Ou<CDcdTextbox>	pCDcdTextbox =
					getCXDcdGrid()->getCell(iXColumnNumber, YCOLUMNNNO_HEADER)->getIfDcDraw();

				CConverter_WinGdi aCConverter_WinGdi;

				CdDrawTextProp	aCdDrawTextProp(
					fontpropDefault,
					colorpropDefault);
					//aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENUTEXT));
				CdBrushProp	aCdBrushProp(
					aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENU));

				pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
				pCDcdTextbox->setCdBrushProp(aCdBrushProp);
				pCDcdTextbox->setText(_T("種別"));
				if (bDisplayRessyamei)
				{
					Ou<CDcdLine>
						(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())
						->setCdPenProp(getCdPenPropDotLine());
				}
				else
				{
					Ou<CDcdLine>
						(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())
						->setCdPenProp(getCdPenPropNarrowLine());
				}
			}
			if (bDisplayRessyamei)
			{
				// 列車名
				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
					CdAllOperationTableXColSpec::ColumnType_Ressyamei, idx));

				Ou<CDcdTextbox>	pCDcdTextbox =
					getCXDcdGrid()->getCell(iXColumnNumber, YCOLUMNNNO_HEADER)->getIfDcDraw();

				CConverter_WinGdi aCConverter_WinGdi;

				CdDrawTextProp	aCdDrawTextProp(
					fontpropDefault,
					colorpropDefault);
					//aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENUTEXT));
				CdBrushProp	aCdBrushProp(
					aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENU));

				pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
				pCDcdTextbox->setCdBrushProp(aCdBrushProp);
				pCDcdTextbox->setText(_T("列車名"));

				Ou<CDcdLine>
					(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())
					->setCdPenProp(getCdPenPropNarrowLine());
			}
			if (idx < m_iMaxRessyaCount - 1)
			{
				// 矢印
				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
					CdAllOperationTableXColSpec::ColumnType_RessyaArrow, idx));

				Ou<CDcdTextbox>	pCDcdTextbox =
					getCXDcdGrid()->getCell(iXColumnNumber, YCOLUMNNNO_HEADER)->getIfDcDraw();

				CConverter_WinGdi aCConverter_WinGdi;

				CdDrawTextProp	aCdDrawTextProp(
					fontpropDefault,
					colorpropDefault);
				//aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENUTEXT));
				CdBrushProp	aCdBrushProp(
					aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENU));

				pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
				pCDcdTextbox->setCdBrushProp(aCdBrushProp);
				pCDcdTextbox->setText(_T(""));

				Ou<CDcdLine>
					(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())
					->setCdPenProp(getCdPenPropNarrowLine());
			}
		}
	}
	else
	{
		{
			// 列車方向
			int iXColumnNumber1 = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
				CdAllOperationTableXColSpec::ColumnType_Ressyahoukou, 0));
			int iXColumnNumber2 = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
				CdAllOperationTableXColSpec::ColumnType_Ressyahoukou, 1));

			Ou<CDcdTextbox>	pCDcdTextbox1 =
				getCXDcdGrid()->getCell(iXColumnNumber1, YCOLUMNNNO_HEADER)->getIfDcDraw();
			Ou<CDcdTextbox>	pCDcdTextbox2 =
				getCXDcdGrid()->getCell(iXColumnNumber2, YCOLUMNNNO_HEADER)->getIfDcDraw();

			CConverter_WinGdi aCConverter_WinGdi;

			CdDrawTextProp	aCdDrawTextProp(
				fontpropDefault,
				colorpropDefault);
			//aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENUTEXT));
			CdBrushProp	aCdBrushProp(
				aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENU));

			pCDcdTextbox1->setCdDrawTextProp(aCdDrawTextProp);
			pCDcdTextbox1->setCdBrushProp(aCdBrushProp);
			pCDcdTextbox1->setText(_T("出区列車"));
			pCDcdTextbox2->setCdDrawTextProp(aCdDrawTextProp);
			pCDcdTextbox2->setCdBrushProp(aCdBrushProp);
			pCDcdTextbox2->setText(_T("入区列車"));
			Ou<CDcdLine>
				(getCXDcdGrid()->getXBorder(iXColumnNumber1)->getIfDcDraw())
				->setCdPenProp(getCdPenPropDotLine());
			Ou<CDcdLine>
				(getCXDcdGrid()->getXBorder(iXColumnNumber2)->getIfDcDraw())
				->setCdPenProp(getCdPenPropDotLine());
		}
		{
			// 列車番号
			int iXColumnNumber1 = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
				CdAllOperationTableXColSpec::ColumnType_Ressyabangou, 0));
			int iXColumnNumber2 = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
				CdAllOperationTableXColSpec::ColumnType_Ressyabangou, 1));
			CString	aString;
			aString = _T("列車番号");

			Ou<CDcdTextbox>	pCDcdTextbox1 =
				getCXDcdGrid()->getCell(iXColumnNumber1, YCOLUMNNNO_HEADER)->getIfDcDraw();
			Ou<CDcdTextbox>	pCDcdTextbox2 =
				getCXDcdGrid()->getCell(iXColumnNumber2, YCOLUMNNNO_HEADER)->getIfDcDraw();

			CConverter_WinGdi aCConverter_WinGdi;

			CdDrawTextProp	aCdDrawTextProp(
				fontpropDefault,
				colorpropDefault);
			//aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENUTEXT));
			CdBrushProp	aCdBrushProp(
				aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENU));

			pCDcdTextbox1->setCdDrawTextProp(aCdDrawTextProp);
			pCDcdTextbox1->setCdBrushProp(aCdBrushProp);
			pCDcdTextbox1->setText((LPCTSTR)aString);
			pCDcdTextbox2->setCdDrawTextProp(aCdDrawTextProp);
			pCDcdTextbox2->setCdBrushProp(aCdBrushProp);
			pCDcdTextbox2->setText((LPCTSTR)aString);
			Ou<CDcdLine>
				(getCXDcdGrid()->getXBorder(iXColumnNumber1)->getIfDcDraw())
				->setCdPenProp(getCdPenPropDotLine());
			Ou<CDcdLine>
				(getCXDcdGrid()->getXBorder(iXColumnNumber2)->getIfDcDraw())
				->setCdPenProp(getCdPenPropDotLine());
		}
		{
			// 種別名
			int iXColumnNumber1 = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
				CdAllOperationTableXColSpec::ColumnType_Ressyasyubetsu, 0));
			int iXColumnNumber2 = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
				CdAllOperationTableXColSpec::ColumnType_Ressyasyubetsu, 1));
			CString	aString;
			aString = _T("種別");

			Ou<CDcdTextbox>	pCDcdTextbox1 =
				getCXDcdGrid()->getCell(iXColumnNumber1, YCOLUMNNNO_HEADER)->getIfDcDraw();
			Ou<CDcdTextbox>	pCDcdTextbox2 =
				getCXDcdGrid()->getCell(iXColumnNumber2, YCOLUMNNNO_HEADER)->getIfDcDraw();

			CConverter_WinGdi aCConverter_WinGdi;

			CdDrawTextProp	aCdDrawTextProp(
				fontpropDefault,
				colorpropDefault);
			//aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENUTEXT));
			CdBrushProp	aCdBrushProp(
				aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENU));

			pCDcdTextbox1->setCdDrawTextProp(aCdDrawTextProp);
			pCDcdTextbox1->setCdBrushProp(aCdBrushProp);
			pCDcdTextbox1->setText((LPCTSTR)aString);
			pCDcdTextbox2->setCdDrawTextProp(aCdDrawTextProp);
			pCDcdTextbox2->setCdBrushProp(aCdBrushProp);
			pCDcdTextbox2->setText((LPCTSTR)aString);
			if (bDisplayRessyamei)
			{
				Ou<CDcdLine>
					(getCXDcdGrid()->getXBorder(iXColumnNumber1)->getIfDcDraw())
					->setCdPenProp(getCdPenPropDotLine());
				Ou<CDcdLine>
					(getCXDcdGrid()->getXBorder(iXColumnNumber2)->getIfDcDraw())
					->setCdPenProp(getCdPenPropDotLine());
			}
			else
			{
				Ou<CDcdLine>
					(getCXDcdGrid()->getXBorder(iXColumnNumber1)->getIfDcDraw())
					->setCdPenProp(getCdPenPropNarrowLine());
				Ou<CDcdLine>
					(getCXDcdGrid()->getXBorder(iXColumnNumber2)->getIfDcDraw())
					->setCdPenProp(getCdPenPropNarrowLine());
			}
		}
		if (bDisplayRessyamei)
		{
			// 列車名
			int iXColumnNumber1 = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
				CdAllOperationTableXColSpec::ColumnType_Ressyamei, 0));
			int iXColumnNumber2 = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
				CdAllOperationTableXColSpec::ColumnType_Ressyamei, 1));
			CString	aString;
			aString = _T("列車名");

			Ou<CDcdTextbox>	pCDcdTextbox1 =
				getCXDcdGrid()->getCell(iXColumnNumber1, YCOLUMNNNO_HEADER)->getIfDcDraw();
			Ou<CDcdTextbox>	pCDcdTextbox2 =
				getCXDcdGrid()->getCell(iXColumnNumber2, YCOLUMNNNO_HEADER)->getIfDcDraw();

			CConverter_WinGdi aCConverter_WinGdi;

			CdDrawTextProp	aCdDrawTextProp(
				fontpropDefault,
				colorpropDefault);
			//aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENUTEXT));
			CdBrushProp	aCdBrushProp(
				aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENU));

			pCDcdTextbox1->setCdDrawTextProp(aCdDrawTextProp);
			pCDcdTextbox1->setCdBrushProp(aCdBrushProp);
			pCDcdTextbox1->setText((LPCTSTR)aString);
			pCDcdTextbox2->setCdDrawTextProp(aCdDrawTextProp);
			pCDcdTextbox2->setCdBrushProp(aCdBrushProp);
			pCDcdTextbox2->setText((LPCTSTR)aString);
			Ou<CDcdLine>
				(getCXDcdGrid()->getXBorder(iXColumnNumber1)->getIfDcDraw())
				->setCdPenProp(getCdPenPropNarrowLine());
			Ou<CDcdLine>
				(getCXDcdGrid()->getXBorder(iXColumnNumber2)->getIfDcDraw())
				->setCdPenProp(getCdPenPropNarrowLine());
		}
		{
			// 矢印
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdAllOperationTableXColSpec(
				CdAllOperationTableXColSpec::ColumnType_RessyaArrow, 0));

			Ou<CDcdTextbox>	pCDcdTextbox =
				getCXDcdGrid()->getCell(iXColumnNumber, YCOLUMNNNO_HEADER)->getIfDcDraw();

			CConverter_WinGdi aCConverter_WinGdi;

			CdDrawTextProp	aCdDrawTextProp(
				fontpropDefault,
				colorpropDefault);
			//aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENUTEXT));
			CdBrushProp	aCdBrushProp(
				aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENU));

			pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
			pCDcdTextbox->setCdBrushProp(aCdBrushProp);
			pCDcdTextbox->setText(_T(""));
			Ou<CDcdLine>
				(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())
				->setCdPenProp(getCdPenPropNarrowLine());
		}
	}
}

	// --------------------------------
	//@name メニューコマンドの下請関数
	// --------------------------------

int CWndDcdGridAllOperationTable::OnAllOperationtableMovetojikokuhyou_Process(BOOL bQueryEnable)
{
	int iRv = 0;
	if (iRv >= 0)
	{
		if (getCentDedDia()->getWaitOperationUpdate())
		{
			iRv = -1;	//運用更新抑止状態です
		}
	}
	CdAllOperationTableYColSpec aCdAllOperationTableYColSpec = getYColSpecOfFocus();
	if (iRv >= 0)
	{
		if (getCSelect()->getSelectedCellCount() == 0)
		{
			if (aCdAllOperationTableYColSpec.getColumnType() !=
				CdAllOperationTableYColSpec::ColumnType_Operation)
			{
				iRv = -3;	//フォーカスが列車位置以外なら不可
			}
		}
		else
		{
			iRv = -4; //複数選択は不可
		}

	}
	if (!bQueryEnable && iRv >= 0)
	{
		int idxOperation = aCdAllOperationTableYColSpec.getOperationIndex();
		const list <OperationTableContent> OperationTableContents =
			getCentDedDia()->getcontOperationTableContent().at(m_strOperationNumber[idxOperation]);

		OperationTableContent aOperationTableContent = OperationTableContents.front();

		CdAllOperationTableXColSpec aCdAllOperationTableXColSpec = getXColSpecOfFocus();
		/**
			移動先の列車
			・入区駅名・入区駅着時刻と
				全列車表示OFFかつRessyaIndexが1(入区列車)かつ列車方向～列車名の場合は、入区列車を開く
			・全列車表示がONかつRessyaIndexが1以上列車数未満かつ列車方向～矢印の場合は、RessyaIndex番目の列車を開く
		*/
		if (aCdAllOperationTableXColSpec.getColumnType() == CdAllOperationTableXColSpec::ColumnType_InEkimei ||
			aCdAllOperationTableXColSpec.getColumnType() == CdAllOperationTableXColSpec::ColumnType_InChakujikoku ||
			(!getDisplayAllRessya() && aCdAllOperationTableXColSpec.getRessyaIndex() == 1 &&
			(aCdAllOperationTableXColSpec.getColumnType() == CdAllOperationTableXColSpec::ColumnType_Ressyahoukou ||
				aCdAllOperationTableXColSpec.getColumnType() == CdAllOperationTableXColSpec::ColumnType_Ressyabangou ||
				aCdAllOperationTableXColSpec.getColumnType() == CdAllOperationTableXColSpec::ColumnType_Ressyasyubetsu ||
				aCdAllOperationTableXColSpec.getColumnType() == CdAllOperationTableXColSpec::ColumnType_Ressyamei)))
		{
			aOperationTableContent = OperationTableContents.back();
		}
		else if (getDisplayAllRessya() &&
			aCdAllOperationTableXColSpec.getRessyaIndex() >= 1 && 
			aCdAllOperationTableXColSpec.getRessyaIndex() < (int)OperationTableContents.size() &&
			(aCdAllOperationTableXColSpec.getColumnType() == CdAllOperationTableXColSpec::ColumnType_Ressyahoukou ||
				aCdAllOperationTableXColSpec.getColumnType() == CdAllOperationTableXColSpec::ColumnType_Ressyabangou ||
				aCdAllOperationTableXColSpec.getColumnType() == CdAllOperationTableXColSpec::ColumnType_Ressyasyubetsu ||
				aCdAllOperationTableXColSpec.getColumnType() == CdAllOperationTableXColSpec::ColumnType_Ressyamei ||
				aCdAllOperationTableXColSpec.getColumnType() == CdAllOperationTableXColSpec::ColumnType_RessyaArrow))
		{
			auto itr = OperationTableContents.begin();
			for (int idx = 0; idx < aCdAllOperationTableXColSpec.getRessyaIndex(); idx++)
			{
				do {
					auto itrNext = itr;
					itrNext++;
					if (itrNext != OperationTableContents.end() &&
						itr->eAfterType == EBeforeAfterType::BeforeAfterType_PropertySame &&
						itrNext->eBeforeType == EBeforeAfterType::BeforeAfterType_PropertySame)
					{
						//この列車が末尾ではなく、後タイプが列車情報引継で、
						//次の列車と一致しているのなら、次の列車の検索を行う。
						itr++;
					}
					else
					{
						break;
					}
				} while (itr != OperationTableContents.end());
				itr++;
			}
			aOperationTableContent = *itr;
		}

		ERessyahoukou eRessyahoukou = aOperationTableContent.aRessyaProperty.getRessyahoukou();
		int iRessyaidx = aOperationTableContent.aRessyaProperty.getRessyaIndex();
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
					iRv = -5;	//	時刻表ビューのオープンに失敗しました
				}
			}
			//pCJikokuhyouDoc = 時刻表ドキュメント
			//pCJikokuhyouView = 時刻表ビュー
		}

		if (iRv >= 0)
		{
			CentDedRessya aCentDedRessya = getCentDedRessyaCont(eRessyahoukou)->get(iRessyaidx);
			pCJikokuhyouView->setFocusToRessyaIndex(iRessyaidx, aCentDedRessya.getSihatsuEki());
			iRv = 1;	//	時刻表ビューへ移動しました
		}

	}
	return iRv;
}

int CWndDcdGridAllOperationTable::OnAllOperationtableMovetojikokuhyouOpenOperationDlg_Process(BOOL bQueryEnable)
{
	int iRv = 0;
	if (iRv >= 0)
	{
		if (getCentDedDia()->getWaitOperationUpdate())
		{
			iRv = -1;	//運用更新抑止状態です
		}
	}
	CdAllOperationTableYColSpec aCdAllOperationTableYColSpec = getYColSpecOfFocus();
	if (iRv >= 0)
	{
		if (getCSelect()->getSelectedCellCount() == 0)
		{
			if (aCdAllOperationTableYColSpec.getColumnType() !=
				CdAllOperationTableYColSpec::ColumnType_Operation)
			{
				iRv = -3;	//フォーカスが列車位置以外なら不可
			}
		}
		else
		{
			iRv = -4; //複数選択は不可
		}

	}
	if (!bQueryEnable && iRv >= 0)
	{
		int idxOperation = aCdAllOperationTableYColSpec.getOperationIndex();
		const list <OperationTableContent> OperationTableContents =
			getCentDedDia()->getcontOperationTableContent().at(m_strOperationNumber[idxOperation]);

		OperationTableContent aOperationTableContent = OperationTableContents.front();

		CdAllOperationTableXColSpec aCdAllOperationTableXColSpec = getXColSpecOfFocus();

		ERessyahoukou eRessyahoukou = aOperationTableContent.aRessyaProperty.getRessyahoukou();
		int iRessyaidx = aOperationTableContent.aRessyaProperty.getRessyaIndex();
		int iOutEkiOrder = aOperationTableContent.iSihatsuEkiOrder;
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
					iRv = -5;	//	時刻表ビューのオープンに失敗しました
				}
			}
			//pCJikokuhyouDoc = 時刻表ドキュメント
			//pCJikokuhyouView = 時刻表ビュー
		}

		if (iRv >= 0)
		{
			CentDedRessya aCentDedRessya = getCentDedRessyaCont(eRessyahoukou)->get(iRessyaidx);

			pCJikokuhyouView->openCDlgOperationProp(
				iRessyaidx, iOutEkiOrder, aCentDedRessya.getValidSihatsuEki() == iOutEkiOrder);

			iRv = 1;	//	時刻表ビューへ移動しました
		}

	}
	return iRv;
}

int CWndDcdGridAllOperationTable::OnAllOperationtableMovetoOperationTable_Process(BOOL bQueryEnable)
{
	int iRv = 0;
	if (iRv >= 0)
	{
		if (getCentDedDia()->getWaitOperationUpdate())
		{
			iRv = -1;	//運用更新抑止状態です
		}
	}
	CdAllOperationTableYColSpec aCdAllOperationTableYColSpec = getYColSpecOfFocus();
	if (iRv >= 0)
	{
		if (getCSelect()->getSelectedCellCount() == 0)
		{
			if (aCdAllOperationTableYColSpec.getColumnType() !=
				CdAllOperationTableYColSpec::ColumnType_Operation)
			{
				iRv = -3;	//フォーカスが列車位置以外なら不可
			}
		}
		else
		{
			iRv = -4; //複数選択は不可
		}

	}
	if (!bQueryEnable && iRv >= 0)
	{
		int idxOperation = aCdAllOperationTableYColSpec.getOperationIndex();
		
		if (!m_strOperationNumber[idxOperation].empty())
		{
			COperationTableView* pCOperationTableView = NULL;
			if (iRv >= 0)
			{
				COperationTableDoc* pCOperationTableDoc = NULL;
				if (iRv >= 0)
				{
					pCOperationTableDoc =
						getCDiagramEditApp()->openCOperationTableDoc(
							getCentDedDia(),
							m_strOperationNumber[idxOperation]);
					//if (pCOperationTableView == NULL)
					//{
					//	iRv = -4;	//	運用表ビューのオープンに失敗しました
					//}
				}
				//pCOperationTableDoc = 運用表ドキュメント
				//pCOperationTableView = 運用表ビュー
			}
		}
	}
	return iRv;
}

int CWndDcdGridAllOperationTable::OnAllOperationtableMovetodiagram_Process(BOOL bQueryEnable)
{
	int iRv = 0;
	if (iRv >= 0)
	{
		if (getCentDedDia()->getWaitOperationUpdate())
		{
			iRv = -5;	//運用更新抑止状態です
		}
	}
	CdAllOperationTableYColSpec aCdAllOperationTableYColSpec = getYColSpecOfFocus();
	if (iRv >= 0)
	{
		if (getCSelect()->getSelectedCellCount() == 0)
		{
			if (aCdAllOperationTableYColSpec.getColumnType() !=
				CdAllOperationTableYColSpec::ColumnType_Operation)
			{
				iRv = -2;	//フォーカスが列車位置以外なら不可
			}
		}
		else
		{
			iRv = -1; //複数選択は不可
		}

	}
	if (!bQueryEnable && iRv >= 0)
	{
		int idxOperation = aCdAllOperationTableYColSpec.getOperationIndex();
		const list <OperationTableContent> OperationTableContents =
			getCentDedDia()->getcontOperationTableContent().at(m_strOperationNumber[idxOperation]);

		OperationTableContent aOperationTableContent = OperationTableContents.front();

		CdAllOperationTableXColSpec aCdAllOperationTableXColSpec = getXColSpecOfFocus();
		/**
			移動先の列車
			・入区駅名・入区駅着時刻と
				全列車表示OFFかつRessyaIndexが1(入区列車)かつ列車方向～列車名の場合は、入区列車を開く
			・全列車表示がONかつRessyaIndexが1以上列車数未満かつ列車方向～矢印の場合は、RessyaIndex番目の列車を開く
			・それ以外の場合は出区列車を開く
		*/
		if (aCdAllOperationTableXColSpec.getColumnType() == CdAllOperationTableXColSpec::ColumnType_InEkimei ||
			aCdAllOperationTableXColSpec.getColumnType() == CdAllOperationTableXColSpec::ColumnType_InChakujikoku ||
			(!getDisplayAllRessya() && aCdAllOperationTableXColSpec.getRessyaIndex() == 1 &&
			(aCdAllOperationTableXColSpec.getColumnType() == CdAllOperationTableXColSpec::ColumnType_Ressyahoukou ||
				aCdAllOperationTableXColSpec.getColumnType() == CdAllOperationTableXColSpec::ColumnType_Ressyabangou ||
				aCdAllOperationTableXColSpec.getColumnType() == CdAllOperationTableXColSpec::ColumnType_Ressyasyubetsu ||
				aCdAllOperationTableXColSpec.getColumnType() == CdAllOperationTableXColSpec::ColumnType_Ressyamei)))
		{
			aOperationTableContent = OperationTableContents.back();
		}
		else if (getDisplayAllRessya() &&
			aCdAllOperationTableXColSpec.getRessyaIndex() >= 1 &&
			aCdAllOperationTableXColSpec.getRessyaIndex() < (int)OperationTableContents.size() &&
			(aCdAllOperationTableXColSpec.getColumnType() == CdAllOperationTableXColSpec::ColumnType_Ressyahoukou ||
				aCdAllOperationTableXColSpec.getColumnType() == CdAllOperationTableXColSpec::ColumnType_Ressyabangou ||
				aCdAllOperationTableXColSpec.getColumnType() == CdAllOperationTableXColSpec::ColumnType_Ressyasyubetsu ||
				aCdAllOperationTableXColSpec.getColumnType() == CdAllOperationTableXColSpec::ColumnType_Ressyamei ||
				aCdAllOperationTableXColSpec.getColumnType() == CdAllOperationTableXColSpec::ColumnType_RessyaArrow))
		{
			auto itr = OperationTableContents.begin();
			for (int idx = 0; idx < aCdAllOperationTableXColSpec.getRessyaIndex(); idx++)
			{
				do {
					auto itrNext = itr;
					itrNext++;
					if (itrNext != OperationTableContents.end() &&
						itr->eAfterType == EBeforeAfterType::BeforeAfterType_PropertySame &&
						itrNext->eBeforeType == EBeforeAfterType::BeforeAfterType_PropertySame)
					{
						//この列車が末尾ではなく、後タイプが列車情報引継で、
						//次の列車と一致しているのなら、次の列車の検索を行う。
						itr++;
					}
					else
					{
						break;
					}
				} while (itr != OperationTableContents.end());
				itr++;
			}
			aOperationTableContent = *itr;
		}

		ERessyahoukou eRessyahoukou = aOperationTableContent.aRessyaProperty.getRessyahoukou();
		int iRessyaidx = aOperationTableContent.aRessyaProperty.getRessyaIndex();
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
					iRv = -3;	//	ダイヤグラムビューのオープンに失敗しました
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
			pCDedDiagramView->setZone_Dgr(aCentDedRessya.getCentDedEkiJikoku(aCentDedRessya.getSihatsuEki()).getHatsujikoku(true),
				aCentDedRessya.EkiIndexOfEkiOrder(aCentDedRessya.getValidSihatsuEki()),
				aCentDedRessya.getRessyahoukou() == Ressyahoukou_Nobori);
		}
	}
	return iRv;
}

int CWndDcdGridAllOperationTable::OnFileExportOperationTableCsv_Process(BOOL bQueryEnable)
{
	int iRv = 0;
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
		CdAllOperationTableXColSpec aCdAllOperationTableXColSpec = getXColSpecOfFocus();
		CdAllOperationTableYColSpec aCdAllOperationTableYColSpec = getYColSpecOfFocus();
		tstring strDefaultOperationNumber;
		int iDefalutEkiIndex = 0;
		if (aCdAllOperationTableYColSpec.getColumnType() == CdAllOperationTableYColSpec::ColumnType_Operation &&
			aCdAllOperationTableYColSpec.getOperationIndex() < (int)m_strOperationNumber.size())
		{
			strDefaultOperationNumber = m_strOperationNumber[aCdAllOperationTableYColSpec.getOperationIndex()];
			const list <OperationTableContent> OperationTableContents =
				getCentDedDia()->getcontOperationTableContent().at(strDefaultOperationNumber);

			if (m_eOperationSort == EOperationSort_InEki ||
				m_eOperationSort == EOperationSort_InJikoku)
			{
				OperationTableContent aOperationTableContent = OperationTableContents.back();

				iDefalutEkiIndex = getCentDedRessyaCont(aOperationTableContent.aRessyaProperty.getRessyahoukou())
					->EkiIndexOfEkiOrder(aOperationTableContent.iSyuuchakuEkiOrder);
			}
			else
			{
				OperationTableContent aOperationTableContent = OperationTableContents.front();

				iDefalutEkiIndex = getCentDedRessyaCont(aOperationTableContent.aRessyaProperty.getRessyahoukou())
					->EkiIndexOfEkiOrder(aOperationTableContent.iSihatsuEkiOrder);
			}
		}
		const CDedRosenFileData* pCDedRosenFileData =
			getCDiagramEditDoc()->getCDedRosenFileData();
		
		CDlgOperationTableCsvExport	aDlg(
			pCDedRosenFileData->getCentDedRosen(),
			getCentDedDia(),
			pCDedRosenFileData->getCdDedDispProp(),
			strDefaultOperationNumber,
			iDefalutEkiIndex,
			getDisplaySecondEkiJikoku(),
			getDisplayColonEkiJikoku(),
			getDisplayParentSyubetsu(),
			getDisplayNoboriLeftToRight(),
			getCompareBottom(),
			m_eOperationSort,
			getDisplayExtensionOperationTable(),
			getDisplayTrackName(),
			getDisplayTsuukaEkiJikoku(),
			this);
		aDlg.DoModal();

		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv;
}

int CWndDcdGridAllOperationTable::OnFileExportAllOperationTableCsv_Process(BOOL bQueryEnable)
{
	int iRv = 0;
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

		CString	strError;
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
			const CDedRosenFileData* pCDedRosenFileData =
				getCDiagramEditDoc()->getCDedRosenFileData();

			CconvAllOperationTableCsv	aConv;
			CdCsvDocument	aCdCsvDocument;
			int iResult = aConv.encode(
				*pCDedRosenFileData->getCentDedRosen(),
				*getCentDedDia(),
				m_strOperationNumber,
				getDisplaySecondEkiJikoku(),
				getDisplayColonEkiJikoku(),
				getDisplayParentSyubetsu(),
				getDisplayAllRessya(),
				m_iMaxRessyaCount,
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

// ****************************************************************
//	CWndDcdGridEkiTrack2
// ****************************************************************


// ********************************
//	コンストラクタ
// ********************************
CWndDcdGridAllOperationTable::CWndDcdGridAllOperationTable()
	: m_bUpdate_All_Requested( false )
	, m_bInitialUpdateComplete(false)
	, m_bDisplayAllRessya(false)
	, m_iMaxRessyaCount(0)
	, m_eOperationSort(EOperationSort::EOperationSort_OperationNumber)
	, m_bCompareBottom(false)
	, m_bDisplaySecondEkiJikoku(false)
	, m_bDisplayColonEkiJikoku(false)
	, m_bDisplayParentSyubetsu(false)
	, m_bDisplayNoboriLeftToRight(false)
	, m_bDisplayExtensionOperationTable(false)
	, m_bDisplayTrackName(false)
	, m_bDisplayTsuukaEkiJikoku(false)
	, m_strCsvFilename(_T(""))
	, m_iSecondRoundChaku(0)
	, m_iSecondRoundHatsu(0)
	, m_bDisplay2400(false)
{
	//getCSelect()->setSelectMode( CSelect::SelectMode_YColumn ) ;
	getCSelect()->setSelectMode(CSelect::SelectMode_NONE);
}
CWndDcdGridAllOperationTable::~CWndDcdGridAllOperationTable()
{
}

// ********************************
//@name	CDcdGrid
// ********************************

// ********************************
//@name	CWndDcdGrid
// ********************************

	// ********************************
	//@name CWndDcdGridAllOperationTable-操作
	// ********************************

CAllOperationTableDoc * CWndDcdGridAllOperationTable::GetDocument()
{
	CView* pCView = (CView*)GetParent();
	return (CAllOperationTableDoc*)pCView->GetDocument();
}

const CentDedDia*	CWndDcdGridAllOperationTable::getCentDedDia()
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

const CentDedRessyaCont*	CWndDcdGridAllOperationTable::getCentDedRessyaCont(
	ERessyahoukou eRessyahoukou)
{
	const CentDedDia* pCentDedDia = getCentDedDia();
	if (pCentDedDia == NULL) {
		return (NULL);
	}
	return (pCentDedDia->getCentDedRessyaCont(eRessyahoukou));
};


int CWndDcdGridAllOperationTable::OnAllOperationTableProp_Process(BOOL bQueryEnable)
{
	int iRv = 0;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
	}
	// ****************************************************************
	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		CDlgAllOperationTableProp aDlg(
			m_eOperationSort,
			m_bCompareBottom,
			this);
		if (aDlg.DoModal() == IDOK)
		{
			setOperationSort(aDlg.getOperationSort());
			setCompareBottom(aDlg.getCompareBottom());

			//	EkijikokuSort の設定を、
			//	.ini ファイルに保存
			getCDiagramEditApp()->writeCWndDcdGridAllOperationTableViewProp(this);

			iRv = 1;	//	ダイアログボックスでの入力が適用されました。
		}
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv;
}

int CWndDcdGridAllOperationTable::OnViewDisplayAllRessya_Process(
	BOOL bQueryEnable)
{
	int iRv = 0;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (getDisplayAllRessya())
	{
		iRv = 1;	//(bQueryEnable==TRUEの場合)[秒単位の時刻を表示]が有効です。
	}
	// ****************************************************************
	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドを実行
		// ****************************************************************
		setDisplayAllRessya(!getDisplayAllRessya());
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv;
}

int CWndDcdGridAllOperationTable::OnViewDisplaySecondEkijikoku_Process(
	BOOL bQueryEnable)
{
	int iRv = 0;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (getDisplaySecondEkiJikoku())
	{
		iRv = 1;	//(bQueryEnable==TRUEの場合)[秒単位の時刻を表示]が有効です。
	}
	// ****************************************************************
	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドを実行
		// ****************************************************************
		setDisplaySecondEkiJikoku(!getDisplaySecondEkiJikoku());
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv;
}

int CWndDcdGridAllOperationTable::OnViewDisplayColonEkijikoku_Process(
	BOOL bQueryEnable)
{
	int iRv = 0;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (getDisplayColonEkiJikoku())
	{
		iRv = 1;	//(bQueryEnable==TRUEの場合)[秒単位の時刻を表示]が有効です。
	}
	// ****************************************************************
	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドを実行
		// ****************************************************************
		setDisplayColonEkiJikoku(!getDisplayColonEkiJikoku());
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv;
}

int CWndDcdGridAllOperationTable::OnViewDisplayParentSyubetsu_Process(
	BOOL bQueryEnable)
{
	int iRv = 0;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (getDisplayParentSyubetsu())
	{
		iRv = 1;	//(bQueryEnable==TRUEの場合)[秒単位の時刻を表示]が有効です。
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

CWndDcdGridAllOperationTable::EOperationSort CWndDcdGridAllOperationTable::getOperationSort()const
{
	return m_eOperationSort;
}
int CWndDcdGridAllOperationTable::setOperationSort(EOperationSort value)
{
	int iRv = 0;
	if (m_eOperationSort != value)
	{
		m_eOperationSort = value;

		//	秒単位の表示の有無が変化した場合は、
		//	ビューを更新します。
		//	ただし、運用更新抑止状態の場合は、ビューの更新は行いません

		if (!getCentDedDia()->getWaitOperationUpdate())
		{
			OnUpdate_All();
			InvalidateGrid();
		}

		//	秒単位の表示の有無を、
		//	.ini ファイルに保存
		getCDiagramEditApp()->writeCWndDcdGridAllOperationTableViewProp(this);
	}
	return (iRv);
}

bool CWndDcdGridAllOperationTable::getCompareBottom()const
{
	return m_bCompareBottom;
}
int CWndDcdGridAllOperationTable::setCompareBottom(bool value)
{
	int iRv = 0;
	if (m_bCompareBottom != value)
	{
		m_bCompareBottom = value;

		//	秒単位の表示の有無が変化した場合は、
		//	ビューを更新します。
		//	ただし、運用更新抑止状態の場合は、ビューの更新は行いません

		if (!getCentDedDia()->getWaitOperationUpdate())
		{
			OnUpdate_All();
			InvalidateGrid();
		}

		//	秒単位の表示の有無を、
		//	.ini ファイルに保存
		getCDiagramEditApp()->writeCWndDcdGridAllOperationTableViewProp(this);
	}
	return (iRv);
}

bool CWndDcdGridAllOperationTable::getDisplayAllRessya()const
{
	return m_bDisplayAllRessya;
}
int CWndDcdGridAllOperationTable::setDisplayAllRessya(bool value)
{
	int iRv = 0;
	if (m_bDisplayAllRessya != value)
	{
		m_bDisplayAllRessya = value;

		//	秒単位の表示の有無が変化した場合は、
		//	ビューを更新します。
		//	ただし、運用更新抑止状態の場合は、ビューの更新は行いません

		if (!getCentDedDia()->getWaitOperationUpdate())
		{
			OnUpdate_All();
			InvalidateGrid();
		}

		//	秒単位の表示の有無を、
		//	.ini ファイルに保存
		getCDiagramEditApp()->writeCWndDcdGridAllOperationTableViewProp(this);
	}
	return (iRv);
}

bool CWndDcdGridAllOperationTable::getDisplaySecondEkiJikoku()const
{
	return m_bDisplaySecondEkiJikoku;
}
int CWndDcdGridAllOperationTable::setDisplaySecondEkiJikoku(bool value)
{
	int iRv = 0;
	if (m_bDisplaySecondEkiJikoku != value)
	{
		m_bDisplaySecondEkiJikoku = value;

		//	秒単位の表示の有無が変化した場合は、
		//	ビューを更新します。
		//	ただし、運用更新抑止状態の場合は、ビューの更新は行いません

		if (!getCentDedDia()->getWaitOperationUpdate())
		{
			OnUpdate_All();
			InvalidateGrid();
		}

		//	秒単位の表示の有無を、
		//	.ini ファイルに保存
		getCDiagramEditApp()->writeCWndDcdGridAllOperationTableViewProp(this);
	}
	return (iRv);
}

bool CWndDcdGridAllOperationTable::getDisplayColonEkiJikoku()const
{
	return m_bDisplayColonEkiJikoku;
}
int CWndDcdGridAllOperationTable::setDisplayColonEkiJikoku(bool value)
{
	int iRv = 0;
	if (m_bDisplayColonEkiJikoku != value)
	{
		m_bDisplayColonEkiJikoku = value;

		//	秒単位の表示の有無が変化した場合は、
		//	ビューを更新します。
		//	ただし、運用更新抑止状態の場合は、ビューの更新は行いません

		if (!getCentDedDia()->getWaitOperationUpdate())
		{
			OnUpdate_All();
			InvalidateGrid();
		}

		//	秒単位の表示の有無を、
		//	.ini ファイルに保存
		getCDiagramEditApp()->writeCWndDcdGridAllOperationTableViewProp(this);
	}
	return (iRv);
}

bool CWndDcdGridAllOperationTable::getDisplayParentSyubetsu()const
{
	return m_bDisplayParentSyubetsu;
}
int CWndDcdGridAllOperationTable::setDisplayParentSyubetsu(bool value)
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
		getCDiagramEditApp()->writeCWndDcdGridAllOperationTableViewProp(this);
	}
	return (iRv);
}


bool CWndDcdGridAllOperationTable::getDisplayNoboriLeftToRight()const
{
	return m_bDisplayNoboriLeftToRight;
}
int CWndDcdGridAllOperationTable::setDisplayNoboriLeftToRight(bool value)
{
	int iRv = 0;

	m_bDisplayNoboriLeftToRight = value;

	return (iRv);
}
bool CWndDcdGridAllOperationTable::getDisplayExtensionOperationTable()const
{
	return m_bDisplayExtensionOperationTable;
}
int CWndDcdGridAllOperationTable::setDisplayExtensionOperationTable(bool value)
{
	int iRv = 0;

	m_bDisplayExtensionOperationTable = value;

	return (iRv);
}
bool CWndDcdGridAllOperationTable::getDisplayTrackName()const
{
	return m_bDisplayTrackName;
}
int CWndDcdGridAllOperationTable::setDisplayTrackName(bool value)
{
	int iRv = 0;

	m_bDisplayTrackName = value;

	return (iRv);
}
bool CWndDcdGridAllOperationTable::getDisplayTsuukaEkiJikoku()const
{
	return m_bDisplayTsuukaEkiJikoku;
}
int CWndDcdGridAllOperationTable::setDisplayTsuukaEkiJikoku(bool value)
{
	int iRv = 0;

	m_bDisplayTsuukaEkiJikoku = value;

	return (iRv);
}


// ----------------------------------------------------------------
//	MFC
// ----------------------------------------------------------------
BEGIN_MESSAGE_MAP(CWndDcdGridAllOperationTable,CWndDcdGridAllOperationTable::super)
	//{{AFX_MSG_MAP(CWndDcdGridAllOperationTable)
	ON_WM_CREATE()
	ON_WM_KEYUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KEYDOWN()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_AllOperationTableProp, &CWndDcdGridAllOperationTable::OnAllOperationtableProp)
	ON_UPDATE_COMMAND_UI(ID_AllOperationTableProp, &CWndDcdGridAllOperationTable::OnUpdateAllOperationtableProp)
	ON_COMMAND(ID_AllOperationTable_MoveToOperationTable, &CWndDcdGridAllOperationTable::OnAllOperationtableMovetoOperationTable)
	ON_UPDATE_COMMAND_UI(ID_AllOperationTable_MoveToOperationTable, &CWndDcdGridAllOperationTable::OnUpdateAllOperationtableMovetoOperationTable)
	ON_COMMAND(ID_OperationTable_MoveToJikokuhyou, &CWndDcdGridAllOperationTable::OnAllOperationtableMovetojikokuhyou)
	ON_UPDATE_COMMAND_UI(ID_OperationTable_MoveToJikokuhyou, &CWndDcdGridAllOperationTable::OnUpdateAllOperationtableMovetojikokuhyou)
	ON_COMMAND(ID_OperationTable_MoveToJikokuhyouOpenOperationDlg, &CWndDcdGridAllOperationTable::OnAllOperationtableMovetojikokuhyouOpenOperationDlg)
	ON_UPDATE_COMMAND_UI(ID_OperationTable_MoveToJikokuhyouOpenOperationDlg, &CWndDcdGridAllOperationTable::OnUpdateAllOperationtableMovetojikokuhyouOpenOperationDlg)
	ON_COMMAND(ID_OperationTable_MoveToDiagram, &CWndDcdGridAllOperationTable::OnAllOperationtableMovetodiagram)
	ON_UPDATE_COMMAND_UI(ID_OperationTable_MoveToDiagram, &CWndDcdGridAllOperationTable::OnUpdateAllOperationtableMovetodiagram)
	ON_COMMAND(ID_VIEW_DisplayAllRessya, &CWndDcdGridAllOperationTable::OnViewDisplayAllRessya)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DisplayAllRessya, &CWndDcdGridAllOperationTable::OnUpdateViewDisplayAllRessya)
	ON_COMMAND(ID_VIEW_DisplaySecondEkiJikoku, &CWndDcdGridAllOperationTable::OnViewDisplaySecondEkijikoku)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DisplaySecondEkiJikoku, &CWndDcdGridAllOperationTable::OnUpdateViewDisplaySecondEkijikoku)
	ON_COMMAND(ID_VIEW_DisplayColonEkiJikoku, &CWndDcdGridAllOperationTable::OnViewDisplayColonEkijikoku)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DisplayColonEkiJikoku, &CWndDcdGridAllOperationTable::OnUpdateViewDisplayColonEkijikoku)
	ON_COMMAND(ID_VIEW_DisplayParentSyubetsu, &CWndDcdGridAllOperationTable::OnViewDisplayParentSyubetsu)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DisplayParentSyubetsu, &CWndDcdGridAllOperationTable::OnUpdateViewDisplayParentSyubetsu)
	ON_COMMAND(ID_FILE_EXPORT_OPERATIONTABLECSV, &CWndDcdGridAllOperationTable::OnFileExportOperationtablecsv)
	ON_COMMAND(ID_FILE_EXPORT_ALLOPERATIONTABLECSV, &CWndDcdGridAllOperationTable::OnFileExportAllOperationtablecsv)
END_MESSAGE_MAP()

int CWndDcdGridAllOperationTable::OnCreate(LPCREATESTRUCT lpCreateStruct)
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




void CWndDcdGridAllOperationTable::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
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
		getCDiagramEditApp()->readCWndDcdGridAllOperationTableViewProp(this);
		CdDedDispProp aCdDedDispProp =
			getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
		m_iSecondRoundChaku = aCdDedDispProp.getSecondRoundChaku();
		m_iSecondRoundHatsu = aCdDedDispProp.getSecondRoundHatsu();
		m_bDisplay2400 = aCdDedDispProp.getDisplay2400();
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
			dynamic_castOu<CRfEditCmd_Dia>(pCmd) ||
			dynamic_castOu<CRfEditCmd_DiaProp>(pCmd) ||
			dynamic_castOu<CRfEditCmd_RessyasyubetsuSwap>( pCmd ))
		{
			//	このビューは、
			//		コメントの変更
			//		ダイヤの変更
			//		ダイヤの属性の変更
			//		駅番線の変更
			//		駅番線の入換
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
		else
		{
			//CRfEditCmd_DedRosenFileDataProp
			//	  路線ファイルのプロパティの変更は、
			//	フォントの変化を伴うため、全更新が必要です。
			//CRfEditCmd_Eki
			//CRfEditCmd_RessyaSyubetsu
			//CRfEditCmd_Rosen
			//CRfEditCmd_RosenFileData
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
		m_iSecondRoundChaku = aCdDedDispProp.getSecondRoundChaku();
		m_iSecondRoundHatsu = aCdDedDispProp.getSecondRoundHatsu();
		m_bDisplay2400 = aCdDedDispProp.getDisplay2400();

		CAllOperationTableDoc* pCAllOperationTableDoc = (CAllOperationTableDoc*)GetDocument();

		if ( GetParent() == pView )
		{
			OnUpdate_All() ;
		}
		else
		{
			LogMsg(_T("CWndDcdGridAllOperationTable::OnUpdate()")
				_T("m_bUpdate_All_Requested=true") ) ;
			m_bUpdate_All_Requested = true ;
		}
	}
	
	int iYColumnBegin = createYColSpecCont().ColumnNumberFromSpec( 
		CdAllOperationTableYColSpec(CdAllOperationTableYColSpec::ColumnType_Operation, 0 ) ) ;

	getCSelect()->setColumnNumberSelectLimit(
		CdDcdZoneXy( 
			CdDcdZone( 0 , INT_MAX ) ,
			CdDcdZone( iYColumnBegin , getCentDedDia()->getcontOperationTableContent().size())
		) );

}

void CWndDcdGridAllOperationTable::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	LogMsg(_T("CWndDcdGridAllOperationTable::OnActivateView(%d,,)") , bActivate ) ;
	
	if ( bActivate && m_bUpdate_All_Requested )
	{
		OnUpdate_All() ;
	}
}

void CWndDcdGridAllOperationTable::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CMenu	aMenu ;
	aMenu.LoadMenu( IDR_MENU_ALLOPERATIONTABLE_CONTEXT ) ;
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

void CWndDcdGridAllOperationTable::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	OnAllOperationtableMovetoOperationTable_Process(FALSE);
}

void CWndDcdGridAllOperationTable::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
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


void CWndDcdGridAllOperationTable::OnAllOperationtableProp()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	OnAllOperationTableProp_Process(FALSE);
}


void CWndDcdGridAllOperationTable::OnUpdateAllOperationtableProp(CCmdUI* pCmdUI)
{
	// TODO:ここにコマンド更新 UI ハンドラー コードを追加します。
	pCmdUI->Enable(OnAllOperationTableProp_Process(TRUE) >= 0);
}


void CWndDcdGridAllOperationTable::OnAllOperationtableMovetoOperationTable()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	OnAllOperationtableMovetoOperationTable_Process(FALSE);
}


void CWndDcdGridAllOperationTable::OnUpdateAllOperationtableMovetoOperationTable(CCmdUI *pCmdUI)
{
	// TODO:ここにコマンド更新 UI ハンドラー コードを追加します。
	pCmdUI->Enable(OnAllOperationtableMovetoOperationTable_Process(TRUE) >= 0);
}

void CWndDcdGridAllOperationTable::OnAllOperationtableMovetojikokuhyou()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	OnAllOperationtableMovetojikokuhyou_Process(FALSE);
}

void CWndDcdGridAllOperationTable::OnUpdateAllOperationtableMovetojikokuhyou(CCmdUI *pCmdUI)
{
	// TODO:ここにコマンド更新 UI ハンドラー コードを追加します。
	pCmdUI->Enable(OnAllOperationtableMovetojikokuhyou_Process(TRUE) >= 0);
}

void CWndDcdGridAllOperationTable::OnAllOperationtableMovetojikokuhyouOpenOperationDlg()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	OnAllOperationtableMovetojikokuhyouOpenOperationDlg_Process(FALSE);
}

void CWndDcdGridAllOperationTable::OnUpdateAllOperationtableMovetojikokuhyouOpenOperationDlg(CCmdUI* pCmdUI)
{
	// TODO:ここにコマンド更新 UI ハンドラー コードを追加します。
	pCmdUI->Enable(OnAllOperationtableMovetojikokuhyouOpenOperationDlg_Process(TRUE) >= 0);
}


void CWndDcdGridAllOperationTable::OnAllOperationtableMovetodiagram()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	OnAllOperationtableMovetodiagram_Process(FALSE);
}


void CWndDcdGridAllOperationTable::OnUpdateAllOperationtableMovetodiagram(CCmdUI *pCmdUI)
{
	// TODO:ここにコマンド更新 UI ハンドラー コードを追加します。
	pCmdUI->Enable(OnAllOperationtableMovetodiagram_Process(TRUE) >= 0);
}

void CWndDcdGridAllOperationTable::OnViewDisplayAllRessya()
{
	OnViewDisplayAllRessya_Process(FALSE);
}

void CWndDcdGridAllOperationTable::OnUpdateViewDisplayAllRessya(CCmdUI* pCmdUI)
{
	int iResult = OnViewDisplayAllRessya_Process(TRUE);
	pCmdUI->Enable(iResult >= 0);
	pCmdUI->SetCheck(iResult >= 1);
}

void CWndDcdGridAllOperationTable::OnViewDisplaySecondEkijikoku()
{
	OnViewDisplaySecondEkijikoku_Process(FALSE);
}

void CWndDcdGridAllOperationTable::OnUpdateViewDisplaySecondEkijikoku(CCmdUI *pCmdUI)
{
	int iResult = OnViewDisplaySecondEkijikoku_Process(TRUE);
	pCmdUI->Enable(iResult >= 0);
	pCmdUI->SetCheck(iResult >= 1);
}

void CWndDcdGridAllOperationTable::OnViewDisplayColonEkijikoku()
{
	OnViewDisplayColonEkijikoku_Process(FALSE);
}

void CWndDcdGridAllOperationTable::OnUpdateViewDisplayColonEkijikoku(CCmdUI *pCmdUI)
{
	int iResult = OnViewDisplayColonEkijikoku_Process(TRUE);
	pCmdUI->Enable(iResult >= 0);
	pCmdUI->SetCheck(iResult >= 1);
}

void CWndDcdGridAllOperationTable::OnViewDisplayParentSyubetsu()
{
	OnViewDisplayParentSyubetsu_Process(FALSE);
}

void CWndDcdGridAllOperationTable::OnUpdateViewDisplayParentSyubetsu(CCmdUI *pCmdUI)
{
	int iResult = OnViewDisplayParentSyubetsu_Process(TRUE);
	pCmdUI->Enable(iResult >= 0);
	pCmdUI->SetCheck(iResult >= 1);
}

void CWndDcdGridAllOperationTable::OnFileExportOperationtablecsv()
{
	OnFileExportOperationTableCsv_Process(FALSE);
}

void CWndDcdGridAllOperationTable::OnFileExportAllOperationtablecsv()
{
	OnFileExportAllOperationTableCsv_Process(FALSE);
}

} //namespace ViewAllOperationTable