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
//	CWndDcdGridInOutLinkCodeList.cpp
//	$Id: CWndDcdGridInOutLinkCodeList.cpp  $
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
#include "str\stringSplit.h"

#include "..\resource.h"
#include "..\entDed\CentDedRosen.h"
#include "..\entDed\CentDedDia.h"
#include "..\DiagramEdit.h"
#include "..\CRfEditCmdHolder.h"
#include "..\DedRosenFileData\EditCmd\EditCmd.h"
#include "CWndDcdGridInOutLinkCodeList.h"
#include "InOutLinkCodeListColSpec\InOutLinkCodeListColSpec.h"


// ****************************************************************
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
// ****************************************************************

namespace ViewInOutLinkCodeList {
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
const int YCOLUMNNNO_RESSYA_0 = 1 ;
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
CdInOutLinkCodeListXColSpecCont
CWndDcdGridInOutLinkCodeList::createXColSpecCont()
{
	CdInOutLinkCodeListXColSpecCont aSpecCont;
	return aSpecCont ;
}

CdInOutLinkCodeListYColSpecCont
CWndDcdGridInOutLinkCodeList::createYColSpecCont()
{
	CdInOutLinkCodeListYColSpecCont aSpecCont(
		m_iRessyaCount);
	return aSpecCont ;
}

CdInOutLinkCodeListXColSpec
CWndDcdGridInOutLinkCodeList::getXColSpecOfFocus()
{
	CdInOutLinkCodeListXColSpec aSpec ;
	CdDcdPosXy aPos = getCFocus()->getFocusCellColumnNumber() ;
	if ( aPos != getCFocus()->ColumnNumberPosXy_NULL() )
	{
		CdInOutLinkCodeListXColSpecCont aSpecCont;/*(
			getCDiagramEditDoc()->getCDedRosenFileData()
			->getCdDedDispProp().getDisplayRessyamei())*/
		aSpec = aSpecCont.ColumnNumberToSpec(aPos.getX());
	}
	return aSpec ;
}

CdInOutLinkCodeListYColSpec
CWndDcdGridInOutLinkCodeList::getYColSpecOfFocus()
{
	CdInOutLinkCodeListYColSpec aSpec ;
	CdDcdPosXy aPos = getCFocus()->getFocusCellColumnNumber() ;
	if ( aPos != getCFocus()->ColumnNumberPosXy_NULL() )
	{
		CdInOutLinkCodeListYColSpecCont aSpecCont(m_iRessyaCount);
		aSpec = aSpecCont.ColumnNumberToSpec( aPos.getY() ) ;
	}
	return aSpec ;
}
	
	// --------------------------------
	//@name OnUpdate の下請関数
	// --------------------------------


//void CWndDcdGridInOutLinkCodeList::OnUpdate_setOperationTableContent_To_Column(
//	int iYColumnNumber ,
//	const tstring strOperationNumber,
//	const list<OperationTableContent>& ListOperationTableContent)
//{
//	const Mu<const CentDedRessya*>* pCentDedRessyaConts[2];
//	for (int iRessyahoukou = Ressyahoukou_Kudari;
//		iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
//	{
//		pCentDedRessyaConts[iRessyahoukou] = getCentDedRessyaCont((ERessyahoukou)iRessyahoukou)->getMuPtr();
//	}
//
//
//	CdFontProp fontpropDefault = createFontProp() ;
//	CdColorProp colorpropDefault = createStringColorProp();
//	CdInOutLinkCodeListXColSpecCont aXColSpecCont = createXColSpecCont();
//
//	// --------------------------------
//	//	行のY方向サイズを設定
//	// --------------------------------
//	{
//		CDcdTargetGetDC	aCDcdTarget( NULL ) ;
//
//		CdDcdSizeXy	sizeRessyamei ;
//		CDcdTextbox	aCDcdTextbox(_T("京都京都京都") ,
//			fontpropDefault , 
//			_T("") , 1 , 2 , 2 ) ;
//		aCDcdTextbox.getItemSize( &aCDcdTarget , &sizeRessyamei) ;
//
//		getCXDcdGrid()->getYColumn( iYColumnNumber )->setColumnSize(sizeRessyamei.getY() ) ;
//	}
//
//
//	// --------------------------------
//	//	属性を設定
//	// --------------------------------
//	const Mu<CentDedEkiCont::CdDedEki>* pCdDedEkiConts[2];
//	for (int iRessyahoukou = Ressyahoukou_Kudari;
//		iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
//	{
//		pCdDedEkiConts[iRessyahoukou] =
//			getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont()->getMuPtr((ERessyahoukou)iRessyahoukou);
//	}
//
//	const CentDedRessyasyubetsuCont* pCentDedRessyasyubetsuCont =
//		getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedRessyasyubetsuCont();
//
//	const OperationTableContent aOperationTableContentOut = ListOperationTableContent.front();
//	const OperationTableContent aOperationTableContentIn = ListOperationTableContent.back();
//
//	const CentDedRessya* pCentDedRessyaOut =
//		pCentDedRessyaConts[aOperationTableContentOut.aRessyaProperty.getRessyahoukou()]
//		->get(aOperationTableContentOut.aRessyaProperty.getRessyaIndex());
//	const CentDedRessya* pCentDedRessyaIn =
//		pCentDedRessyaConts[aOperationTableContentIn.aRessyaProperty.getRessyahoukou()]
//		->get(aOperationTableContentIn.aRessyaProperty.getRessyaIndex());
//
//	const CentDedRessyasyubetsu* pCentDedRessyasyubetsuOut = pCentDedRessyasyubetsuCont
//		->getMuPtr()->get(pCentDedRessyaOut->getRessyasyubetsuIndex());
//	if (m_bDisplayParentSyubetsu && pCentDedRessyasyubetsuOut->getParentSyubetsuIndex() >= 0)
//	{
//		pCentDedRessyasyubetsuOut = pCentDedRessyasyubetsuCont
//			->getMuPtr()->get(pCentDedRessyasyubetsuOut->getParentSyubetsuIndex());
//	}
//	const CentDedRessyasyubetsu* pCentDedRessyasyubetsuIn = pCentDedRessyasyubetsuCont
//		->getMuPtr()->get(pCentDedRessyaIn->getRessyasyubetsuIndex());
//	if (m_bDisplayParentSyubetsu && pCentDedRessyasyubetsuIn->getParentSyubetsuIndex() >= 0)
//	{
//		pCentDedRessyasyubetsuIn = pCentDedRessyasyubetsuCont
//			->getMuPtr()->get(pCentDedRessyasyubetsuIn->getParentSyubetsuIndex());
//	}
//
//	tstring strRessyahoukouKudari;
//	tstring strRessyahoukouNobori;
//	CString strRessyahoukouTemp;
//	if (getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getKudariDiaAlias().empty())
//	{
//		strRessyahoukouTemp.LoadString(IDS_WORD_Kudari);
//		strRessyahoukouKudari = (LPCTSTR)strRessyahoukouTemp;
//	}
//	else
//	{
//		strRessyahoukouKudari = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getKudariDiaAlias().c_str();
//	}
//	if (getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getNoboriDiaAlias().empty())
//	{
//		strRessyahoukouTemp.LoadString(IDS_WORD_Nobori);
//		strRessyahoukouNobori = (LPCTSTR)strRessyahoukouTemp;
//	}
//	else
//	{
//		strRessyahoukouNobori = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getNoboriDiaAlias().c_str();
//	}
//
//	{
//		//	列番号
//		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
//			CdInOutLinkCodeListXColSpec::ColumnType_ColumnNumber));
//		Ou<CDcdTextbox> pCDcdTextbox =
//			getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
//		pCDcdTextbox->
//			setText(to_tstring(iYColumnNumber - YCOLUMNNNO_RESSYA_0 + 1));
//
//		//	フォント属性
//		CdDrawTextProp	aCdDrawTextProp =
//			pCDcdTextbox->getCdDrawTextProp();
//		aCdDrawTextProp.setCdFontProp(fontpropDefault);
//		aCdDrawTextProp.setTextColor(colorpropDefault);
//		aCdDrawTextProp.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
//		pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
//
//		//	セルを無効化
//		InvalidateCell(iXColumnNumber, iYColumnNumber);
//	}
//	{
//		//	運用番号
//		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
//			CdInOutLinkCodeListXColSpec::ColumnType_OperationNumber));
//		Ou<CDcdTextbox> pCDcdTextbox =
//			getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
//		pCDcdTextbox->
//			setText(strOperationNumber);
//
//		//	フォント属性
//		CdDrawTextProp	aCdDrawTextProp =
//			pCDcdTextbox->getCdDrawTextProp();
//		aCdDrawTextProp.setCdFontProp(fontpropDefault);
//		aCdDrawTextProp.setTextColor(colorpropDefault);
//		aCdDrawTextProp.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
//		pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
//
//		//	セルを無効化
//		InvalidateCell(iXColumnNumber, iYColumnNumber);
//	}
//	{
//		//	出区駅名&出区駅時刻
//		int iXColumnNumber1 = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
//			CdInOutLinkCodeListXColSpec::ColumnType_OutEkimei));
//		int iXColumnNumber2 = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
//			CdInOutLinkCodeListXColSpec::ColumnType_OutHatsujikoku));
//		Ou<CDcdTextbox> pCDcdTextbox1 =
//			getCXDcdGrid()->getCell(iXColumnNumber1, iYColumnNumber)->getIfDcDraw();
//		Ou<CDcdTextbox> pCDcdTextbox2 =
//			getCXDcdGrid()->getCell(iXColumnNumber2, iYColumnNumber)->getIfDcDraw();
//
//		tstring strEkimei;
//		CdDedJikoku aCdDedJikoku;
//		if (ListOperationTableContent.front().iOuterShihatsuekiIndex != INT_MIN)
//		{
//			int iOuterTerminalIndex = aOperationTableContentOut.iOuterShihatsuekiIndex;
//			strEkimei = pCdDedEkiConts[aOperationTableContentOut.aRessyaProperty.getRessyahoukou()]
//				->get(aOperationTableContentOut.iSihatsuEkiOrder).getOuterTerminalEkimei(iOuterTerminalIndex);
//			aCdDedJikoku = aOperationTableContentOut.OuterShihatsuJikoku;
//		}
//		else
//		{
//			int iSihatsuEkiOrder = aOperationTableContentOut.iSihatsuEkiOrder;
//			if (!pCentDedRessyaOut->isRunBetweenNextEki(iSihatsuEkiOrder))
//			{
//				iSihatsuEkiOrder = pCentDedRessyaOut->getRunBetweenEkiForward(iSihatsuEkiOrder);
//			}
//
//			strEkimei = pCdDedEkiConts[aOperationTableContentOut.aRessyaProperty.getRessyahoukou()]
//				->get(iSihatsuEkiOrder).getEkimei();
//			aCdDedJikoku = pCentDedRessyaOut->getCentDedEkiJikoku(iSihatsuEkiOrder).getHatsujikoku();
//		}
//		pCDcdTextbox1->setText(strEkimei);
//		pCDcdTextbox2->
//			setText(getCdDedJikokuConv().encode(aCdDedJikoku, false));
//
//		//	フォント属性
//		CdDrawTextProp	aCdDrawTextProp1 =
//			pCDcdTextbox1->getCdDrawTextProp();
//		aCdDrawTextProp1.setCdFontProp(fontpropDefault);
//		aCdDrawTextProp1.setTextColor(colorpropDefault);
//		aCdDrawTextProp1.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
//		pCDcdTextbox1->setCdDrawTextProp(aCdDrawTextProp1);
//
//		CdDrawTextProp	aCdDrawTextProp2 =
//			pCDcdTextbox2->getCdDrawTextProp();
//		aCdDrawTextProp2.setCdFontProp(fontpropDefault);
//		aCdDrawTextProp2.setTextColor(colorpropDefault);
//		aCdDrawTextProp2.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
//		pCDcdTextbox2->setCdDrawTextProp(aCdDrawTextProp2);
//
//		//	セルを無効化
//		InvalidateCell(iXColumnNumber1, iYColumnNumber);
//		InvalidateCell(iXColumnNumber2, iYColumnNumber);
//	}
//	{
//		//	矢印
//		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
//			CdInOutLinkCodeListXColSpec::ColumnType_Arrow));
//		Ou<CDcdTextbox> pCDcdTextbox =
//			getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
//
//		tstring strArrow = _T("→");
//		pCDcdTextbox->setText(strArrow);
//
//		//	フォント属性
//		CdDrawTextProp	aCdDrawTextProp =
//			pCDcdTextbox->getCdDrawTextProp();
//		aCdDrawTextProp.setCdFontProp(fontpropDefault);
//		aCdDrawTextProp.setTextColor(colorpropDefault);
//		aCdDrawTextProp.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
//		pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
//
//		//	セルを無効化
//		InvalidateCell(iXColumnNumber, iYColumnNumber);
//	}
//	{
//		//	入区列車始終着駅名&入区列車駅時刻
//		int iXColumnNumber1 = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
//			CdInOutLinkCodeListXColSpec::ColumnType_InEkimei));
//		int iXColumnNumber2 = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
//			CdInOutLinkCodeListXColSpec::ColumnType_InChakujikoku));
//		Ou<CDcdTextbox> pCDcdTextbox1 =
//			getCXDcdGrid()->getCell(iXColumnNumber1, iYColumnNumber)->getIfDcDraw();
//		Ou<CDcdTextbox> pCDcdTextbox2 =
//			getCXDcdGrid()->getCell(iXColumnNumber2, iYColumnNumber)->getIfDcDraw();
//
//		tstring strEkimei;
//		CdDedJikoku aCdDedJikoku;
//		if (aOperationTableContentIn.iOuterShuchakuekiIndex != INT_MIN)
//		{
//			int iOuterTerminalIndex = aOperationTableContentIn.iOuterShuchakuekiIndex;
//			strEkimei = pCdDedEkiConts[aOperationTableContentIn.aRessyaProperty.getRessyahoukou()]
//				->get(aOperationTableContentIn.iSyuuchakuEkiOrder).getOuterTerminalEkimei(iOuterTerminalIndex);
//			aCdDedJikoku = aOperationTableContentIn.OuterShuchakuJikoku;
//		}
//		else
//		{
//			int iSyuuchakuEkiOrder = aOperationTableContentIn.iSyuuchakuEkiOrder;
//			if (!pCentDedRessyaIn->isRunBetweenNextEki(iSyuuchakuEkiOrder - 1))
//			{
//				iSyuuchakuEkiOrder = pCentDedRessyaIn->getRunBetweenEkiBackward(iSyuuchakuEkiOrder);
//			}
//
//			strEkimei = pCdDedEkiConts[aOperationTableContentIn.aRessyaProperty.getRessyahoukou()]
//				->get(iSyuuchakuEkiOrder).getEkimei();
//			aCdDedJikoku = pCentDedRessyaIn->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getChakujikoku();
//		}
//		pCDcdTextbox1->setText(strEkimei);
//		pCDcdTextbox2->
//			setText(getCdDedJikokuConv().encode(aCdDedJikoku, true));
//
//		//	フォント属性
//		CdDrawTextProp	aCdDrawTextProp1 =
//			pCDcdTextbox1->getCdDrawTextProp();
//		aCdDrawTextProp1.setCdFontProp(fontpropDefault);
//		aCdDrawTextProp1.setTextColor(colorpropDefault);
//		aCdDrawTextProp1.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
//		pCDcdTextbox1->setCdDrawTextProp(aCdDrawTextProp1);
//
//		CdDrawTextProp	aCdDrawTextProp2 =
//			pCDcdTextbox2->getCdDrawTextProp();
//		aCdDrawTextProp2.setCdFontProp(fontpropDefault);
//		aCdDrawTextProp2.setTextColor(colorpropDefault);
//		aCdDrawTextProp2.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
//		pCDcdTextbox2->setCdDrawTextProp(aCdDrawTextProp2);
//
//		//	セルを無効化
//		InvalidateCell(iXColumnNumber1, iYColumnNumber);
//		InvalidateCell(iXColumnNumber2, iYColumnNumber);
//	}
//
//	if (m_bDisplayAllRessya)
//	{
//		int iRessyaIndex = 0;
//		for (auto itr = ListOperationTableContent.begin(); itr != ListOperationTableContent.end(); itr++, iRessyaIndex++)
//		{
//			const CentDedRessya* pCentDedRessya =
//				pCentDedRessyaConts[itr->aRessyaProperty.getRessyahoukou()]
//				->get(itr->aRessyaProperty.getRessyaIndex());
//
//			const CentDedRessyasyubetsu* pCentDedRessyasyubetsu = pCentDedRessyasyubetsuCont
//				->getMuPtr()->get(pCentDedRessya->getRessyasyubetsuIndex());
//			if (m_bDisplayParentSyubetsu && pCentDedRessyasyubetsu->getParentSyubetsuIndex() >= 0)
//			{
//				pCentDedRessyasyubetsu = pCentDedRessyasyubetsuCont
//					->getMuPtr()->get(pCentDedRessyasyubetsu->getParentSyubetsuIndex());
//			}
//
//			{
//				//	列車番号
//				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
//					CdInOutLinkCodeListXColSpec::ColumnType_Ressyabangou, iRessyaIndex));
//				Ou<CDcdTextbox> pCDcdTextbox =
//					getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
//				pCDcdTextbox->
//					setText(pCentDedRessya->getRessyabangou());
//
//				//	フォント属性
//				CdDrawTextProp	aCdDrawTextProp =
//					pCDcdTextbox->getCdDrawTextProp();
//				aCdDrawTextProp.setCdFontProp(fontpropDefault);
//				aCdDrawTextProp.setTextColor(colorpropDefault);
//				aCdDrawTextProp.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
//				pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
//
//				//	セルを無効化
//				InvalidateCell(iXColumnNumber, iYColumnNumber);
//			}
//			{
//				//	列車種別
//				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
//					CdInOutLinkCodeListXColSpec::ColumnType_Ressyasyubetsu, iRessyaIndex));
//				Ou<CDcdTextbox> pCDcdTextbox =
//					getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
//
//				//種別のテキスト
//				pCDcdTextbox->setText(pCentDedRessyasyubetsu->getSyubetsumei());
//
//				//種別のフォント属性
//				CdDrawTextProp	aCdDrawTextProp =
//					pCDcdTextbox->getCdDrawTextProp();
//				aCdDrawTextProp.setCdFontProp(fontpropDefault);
//				{
//					aCdDrawTextProp.setTextColor(pCentDedRessyasyubetsu->getJikokuhyouMojiColor());
//
//					int idxFont = pCentDedRessyasyubetsu->getJikokuhyouFontIndex();
//					aCdDrawTextProp.setCdFontProp(
//						getCDiagramEditDoc()->getCDedRosenFileData()
//						->getCdDedDispProp().getJikokuhyouFont(idxFont));
//				}
//				aCdDrawTextProp.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
//				pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
//
//				//	セルを無効化
//				InvalidateCell(iXColumnNumber, iYColumnNumber);
//			}
//			if (getCDiagramEditDoc()->getCDedRosenFileData()
//				->getCdDedDispProp().getDisplayRessyamei())
//			{
//				//	列車名
//				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
//					CdInOutLinkCodeListXColSpec::ColumnType_Ressyamei, iRessyaIndex));
//				Ou<CDcdTextbox> pCDcdTextbox =
//					getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
//
//				//列車名のテキスト
//				tstring strRessyamei = pCentDedRessya->getRessyamei();
//				if (!pCentDedRessya->getGousuu().empty())
//				{
//					strRessyamei += _T(" ");
//					strRessyamei += pCentDedRessya->getGousuu();
//					strRessyamei += _T("号");
//				}
//				pCDcdTextbox->setText(strRessyamei);
//
//				//列車名のフォント属性
//				CdDrawTextProp	aCdDrawTextProp =
//					pCDcdTextbox->getCdDrawTextProp();
//				aCdDrawTextProp.setCdFontProp(fontpropDefault);
//				{
//					aCdDrawTextProp.setTextColor(pCentDedRessyasyubetsu->getJikokuhyouMojiColor());
//
//					int idxFont = pCentDedRessyasyubetsu->getJikokuhyouFontIndex();
//					aCdDrawTextProp.setCdFontProp(
//						getCDiagramEditDoc()->getCDedRosenFileData()
//						->getCdDedDispProp().getJikokuhyouFont(idxFont));
//				}
//				pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
//
//				//	セルを無効化
//				InvalidateCell(iXColumnNumber, iYColumnNumber);
//			}
//
//			{
//				//	列車方向
//				/**
//					列車方向
//					全列車表示時の列車方向は、同一列車扱い設定を加味します
//					itr列車のAfterTypeがPropertySameの場合、itrnextとして次の列車を読み込み、そのBeforeTypeがPropertySameなら同一列車扱いとなります。
//					同一列車扱いの場合は先頭列車の始発駅Indexと末尾列車の終着駅Indexの大小関係で列車方向を決めます。
//				*/
//				ERessyahoukou eRessyahoukou = pCentDedRessya->getRessyahoukou();
//				if (itr->eAfterType == EBeforeAfterType::BeforeAfterType_PropertySame)
//				{
//					int iSihatsuEkiIndex = pCentDedRessya->EkiIndexOfEkiOrder(itr->iSihatsuEkiOrder);
//
//					int iSyuuchakuEkiIndex = pCentDedRessya->EkiIndexOfEkiOrder(itr->iSyuuchakuEkiOrder);
//					auto itrNext = itr;
//					do {
//						itrNext++;
//						if (itrNext == ListOperationTableContent.end() ||
//							itrNext->eBeforeType != EBeforeAfterType::BeforeAfterType_PropertySame)
//						{
//							//次の列車が末尾を超えた場合、もしくは
//							//次の列車の前タイプが同一列車扱い以外なら、一体化は無効その前の列車で終了します。
//							break;
//						}
//						else/* if (itrNext->eBeforeType == EBeforeAfterType::BeforeAfterType_PropertySame)*/
//						{
//							//次の列車の前タイプが同一列車扱いの場合、通常時および箱ダイヤで列車方向一致、終着→始発が駅順の場合は、次の列車は一体化が確定する。
//
//							itr++;
//							iSyuuchakuEkiIndex = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
//								->getCentDedEkiCont()->EkiIndexOfEkiOrder(itrNext->aRessyaProperty.getRessyahoukou(),
//									itrNext->iSyuuchakuEkiOrder);
//
//							if (itrNext->eAfterType == EBeforeAfterType::BeforeAfterType_PropertySame)
//							{
//								//次の列車の後タイプが同一列車扱いなら、さらに次の列車の検索を行う。
//								continue;
//							}
//							else
//							{
//								//次の列車の後タイプが同一列車扱い以外なら、この列車が一体化の末尾となる
//								break;
//							}
//						}
//					} while (itrNext != ListOperationTableContent.end());
//
//					if (iSihatsuEkiIndex < iSyuuchakuEkiIndex)
//					{
//						eRessyahoukou = ERessyahoukou::Ressyahoukou_Kudari;
//					}
//					else if (iSihatsuEkiIndex > iSyuuchakuEkiIndex)
//					{
//						eRessyahoukou = ERessyahoukou::Ressyahoukou_Nobori;
//					}
//					//iSihatsuEkiIndex と iSyuuchakuEkiIndex　が同値の場合は、最初の列車の列車方向をそのまま用います
//				}
//				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
//					CdInOutLinkCodeListXColSpec::ColumnType_Ressyahoukou, iRessyaIndex));
//				Ou<CDcdTextbox> pCDcdTextbox =
//					getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
//				tstring strRessyahoukou;
//				if (eRessyahoukou == Ressyahoukou_Kudari)
//				{
//					strRessyahoukou = strRessyahoukouKudari;
//				}
//				else
//				{
//					strRessyahoukou = strRessyahoukouNobori;
//				}
//				pCDcdTextbox->
//					setText(strRessyahoukou);
//
//				//	フォント属性
//				CdDrawTextProp	aCdDrawTextProp =
//					pCDcdTextbox->getCdDrawTextProp();
//				aCdDrawTextProp.setCdFontProp(fontpropDefault);
//				aCdDrawTextProp.setTextColor(colorpropDefault);
//				aCdDrawTextProp.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
//				pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
//
//				//	セルを無効化
//				InvalidateCell(iXColumnNumber, iYColumnNumber);
//			}
//
//			if (iRessyaIndex < m_iMaxRessyaCount - 1)
//			{
//				//	矢印
//				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
//					CdInOutLinkCodeListXColSpec::ColumnType_RessyaArrow, iRessyaIndex));
//				Ou<CDcdTextbox> pCDcdTextbox =
//					getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
//
//				if (iRessyaIndex < (int)ListOperationTableContent.size() - 1)
//				{
//					tstring strArrow = _T("→");
//					pCDcdTextbox->setText(strArrow);
//				}
//				else
//				{
//					pCDcdTextbox->setText(_T(""));
//				}
//
//				//	フォント属性
//				CdDrawTextProp	aCdDrawTextProp =
//					pCDcdTextbox->getCdDrawTextProp();
//				aCdDrawTextProp.setCdFontProp(fontpropDefault);
//				aCdDrawTextProp.setTextColor(colorpropDefault);
//				aCdDrawTextProp.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
//				pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
//
//				//	セルを無効化
//				InvalidateCell(iXColumnNumber, iYColumnNumber);
//			}
//		}
//		/**
//			列車本数がMaxRessyaCountよりも小さい場合は、空白スペースを埋めます。
//		*/
//		for (;iRessyaIndex < m_iMaxRessyaCount; iRessyaIndex++)
//		{
//			{
//				//	列車方向
//				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
//					CdInOutLinkCodeListXColSpec::ColumnType_Ressyahoukou, iRessyaIndex));
//				Ou<CDcdTextbox> pCDcdTextbox =
//					getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
//				pCDcdTextbox->setText(_T(""));
//				
//				//	セルを無効化
//				InvalidateCell(iXColumnNumber, iYColumnNumber);
//			}
//			{
//				//	列車番号
//				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
//					CdInOutLinkCodeListXColSpec::ColumnType_Ressyabangou, iRessyaIndex));
//				Ou<CDcdTextbox> pCDcdTextbox =
//					getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
//				pCDcdTextbox->setText(_T(""));
//
//				//	セルを無効化
//				InvalidateCell(iXColumnNumber, iYColumnNumber);
//			}
//			{
//				//	列車種別
//				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
//					CdInOutLinkCodeListXColSpec::ColumnType_Ressyasyubetsu, iRessyaIndex));
//				Ou<CDcdTextbox> pCDcdTextbox =
//					getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
//				pCDcdTextbox->setText(_T(""));
//
//				//	セルを無効化
//				InvalidateCell(iXColumnNumber, iYColumnNumber);
//			}
//			if (getCDiagramEditDoc()->getCDedRosenFileData()
//				->getCdDedDispProp().getDisplayRessyamei())
//			{
//				//	列車名
//				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
//					CdInOutLinkCodeListXColSpec::ColumnType_Ressyamei, iRessyaIndex));
//				Ou<CDcdTextbox> pCDcdTextbox =
//					getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
//				pCDcdTextbox->setText(_T(""));
//				
//				//	セルを無効化
//				InvalidateCell(iXColumnNumber, iYColumnNumber);
//			}
//
//			if (iRessyaIndex < m_iMaxRessyaCount - 1)
//			{
//				//	矢印
//				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
//					CdInOutLinkCodeListXColSpec::ColumnType_RessyaArrow, iRessyaIndex));
//				Ou<CDcdTextbox> pCDcdTextbox =
//					getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
//				pCDcdTextbox->setText(_T(""));
//
//				//	セルを無効化
//				InvalidateCell(iXColumnNumber, iYColumnNumber);
//			}
//		}
//	}
//	else
//	{
//		{
//			/**	
//				出区列車方向
//				先頭列車の次列車接続タイプが同一列車扱いでも、先頭列車の列車方向をそのまま
//			*/
//			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
//				CdInOutLinkCodeListXColSpec::ColumnType_Ressyahoukou, 0));
//			Ou<CDcdTextbox> pCDcdTextbox =
//				getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
//			tstring strRessyahoukou;
//			if (pCentDedRessyaOut->getRessyahoukou() == Ressyahoukou_Kudari)
//			{
//				strRessyahoukou = strRessyahoukouKudari;
//			}
//			else
//			{
//				strRessyahoukou = strRessyahoukouNobori;
//			}
//			pCDcdTextbox->
//				setText(strRessyahoukou);
//
//			//	フォント属性
//			CdDrawTextProp	aCdDrawTextProp =
//				pCDcdTextbox->getCdDrawTextProp();
//			aCdDrawTextProp.setCdFontProp(fontpropDefault);
//			aCdDrawTextProp.setTextColor(colorpropDefault);
//			aCdDrawTextProp.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
//			pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
//
//			//	セルを無効化
//			InvalidateCell(iXColumnNumber, iYColumnNumber);
//		}
//		{
//			//	出区列車番号
//			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
//				CdInOutLinkCodeListXColSpec::ColumnType_Ressyabangou, 0));
//			Ou<CDcdTextbox> pCDcdTextbox =
//				getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
//			pCDcdTextbox->
//				setText(pCentDedRessyaOut->getRessyabangou());
//
//			//	フォント属性
//			CdDrawTextProp	aCdDrawTextProp =
//				pCDcdTextbox->getCdDrawTextProp();
//			aCdDrawTextProp.setCdFontProp(fontpropDefault);
//			aCdDrawTextProp.setTextColor(colorpropDefault);
//			aCdDrawTextProp.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
//			pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
//
//			//	セルを無効化
//			InvalidateCell(iXColumnNumber, iYColumnNumber);
//		}
//		{
//			//	出区列車種別
//			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
//				CdInOutLinkCodeListXColSpec::ColumnType_Ressyasyubetsu, 0));
//			Ou<CDcdTextbox> pCDcdTextbox =
//				getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
//
//			//種別のテキスト
//			pCDcdTextbox->setText(pCentDedRessyasyubetsuOut->getSyubetsumei());
//
//			//種別のフォント属性
//			CdDrawTextProp	aCdDrawTextProp =
//				pCDcdTextbox->getCdDrawTextProp();
//			aCdDrawTextProp.setCdFontProp(fontpropDefault);
//			{
//				aCdDrawTextProp.setTextColor(pCentDedRessyasyubetsuOut->getJikokuhyouMojiColor());
//
//				int idxFont = pCentDedRessyasyubetsuOut->getJikokuhyouFontIndex();
//				aCdDrawTextProp.setCdFontProp(
//					getCDiagramEditDoc()->getCDedRosenFileData()
//					->getCdDedDispProp().getJikokuhyouFont(idxFont));
//			}
//			aCdDrawTextProp.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
//			pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
//
//			//	セルを無効化
//			InvalidateCell(iXColumnNumber, iYColumnNumber);
//		}
//		if (getCDiagramEditDoc()->getCDedRosenFileData()
//			->getCdDedDispProp().getDisplayRessyamei())
//		{
//			//	出区列車名
//			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
//				CdInOutLinkCodeListXColSpec::ColumnType_Ressyamei, 0));
//			Ou<CDcdTextbox> pCDcdTextbox =
//				getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
//
//			//列車名のテキスト
//			tstring strRessyamei = pCentDedRessyaOut->getRessyamei();
//			if (!pCentDedRessyaOut->getGousuu().empty())
//			{
//				strRessyamei += _T(" ");
//				strRessyamei += pCentDedRessyaOut->getGousuu();
//				strRessyamei += _T("号");
//			}
//			pCDcdTextbox->setText(strRessyamei);
//
//			//列車名のフォント属性
//			CdDrawTextProp	aCdDrawTextProp =
//				pCDcdTextbox->getCdDrawTextProp();
//			aCdDrawTextProp.setCdFontProp(fontpropDefault);
//			{
//				aCdDrawTextProp.setTextColor(pCentDedRessyasyubetsuOut->getJikokuhyouMojiColor());
//
//				int idxFont = pCentDedRessyasyubetsuOut->getJikokuhyouFontIndex();
//				aCdDrawTextProp.setCdFontProp(
//					getCDiagramEditDoc()->getCDedRosenFileData()
//					->getCdDedDispProp().getJikokuhyouFont(idxFont));
//			}
//			pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
//
//			//	セルを無効化
//			InvalidateCell(iXColumnNumber, iYColumnNumber);
//		}
//
//		{
//			//	矢印
//			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
//				CdInOutLinkCodeListXColSpec::ColumnType_RessyaArrow, 0));
//			Ou<CDcdTextbox> pCDcdTextbox =
//				getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
//
//			tstring strArrow = _T("→");
//			pCDcdTextbox->setText(strArrow);
//
//			//	フォント属性
//			CdDrawTextProp	aCdDrawTextProp =
//				pCDcdTextbox->getCdDrawTextProp();
//			aCdDrawTextProp.setCdFontProp(fontpropDefault);
//			aCdDrawTextProp.setTextColor(colorpropDefault);
//			aCdDrawTextProp.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
//			pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
//
//			//	セルを無効化
//			InvalidateCell(iXColumnNumber, iYColumnNumber);
//		}
//
//		//入区列車の属性については、同一列車扱いの指定を見ず、末尾列車とする。
//		{
//			//	入区列車方向
//			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
//				CdInOutLinkCodeListXColSpec::ColumnType_Ressyahoukou, 1));
//			Ou<CDcdTextbox> pCDcdTextbox =
//				getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
//			tstring strRessyahoukou;
//			if (pCentDedRessyaIn->getRessyahoukou() == Ressyahoukou_Kudari)
//			{
//				strRessyahoukou = strRessyahoukouKudari;
//			}
//			else
//			{
//				strRessyahoukou = strRessyahoukouNobori;
//			}
//			pCDcdTextbox->
//				setText(strRessyahoukou);
//
//			//	フォント属性
//			CdDrawTextProp	aCdDrawTextProp =
//				pCDcdTextbox->getCdDrawTextProp();
//			aCdDrawTextProp.setCdFontProp(fontpropDefault);
//			aCdDrawTextProp.setTextColor(colorpropDefault);
//			aCdDrawTextProp.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
//			pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
//
//			//	セルを無効化
//			InvalidateCell(iXColumnNumber, iYColumnNumber);
//		}
//		{
//			//	入区列車番号
//			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
//				CdInOutLinkCodeListXColSpec::ColumnType_Ressyabangou, 1));
//			Ou<CDcdTextbox> pCDcdTextbox =
//				getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
//			pCDcdTextbox->
//				setText(pCentDedRessyaIn->getRessyabangou());
//
//			//	フォント属性
//			CdDrawTextProp	aCdDrawTextProp =
//				pCDcdTextbox->getCdDrawTextProp();
//			aCdDrawTextProp.setCdFontProp(fontpropDefault);
//			aCdDrawTextProp.setTextColor(colorpropDefault);
//			aCdDrawTextProp.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
//			pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
//
//			//	セルを無効化
//			InvalidateCell(iXColumnNumber, iYColumnNumber);
//		}
//		{
//			//	入区列車種別
//			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
//				CdInOutLinkCodeListXColSpec::ColumnType_Ressyasyubetsu, 1));
//			Ou<CDcdTextbox> pCDcdTextbox =
//				getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
//
//			//種別のテキスト
//			pCDcdTextbox->setText(pCentDedRessyasyubetsuIn->getSyubetsumei());
//
//			//種別のフォント属性
//			CdDrawTextProp	aCdDrawTextProp =
//				pCDcdTextbox->getCdDrawTextProp();
//			aCdDrawTextProp.setCdFontProp(fontpropDefault);
//			{
//				aCdDrawTextProp.setTextColor(pCentDedRessyasyubetsuIn->getJikokuhyouMojiColor());
//
//				int idxFont = pCentDedRessyasyubetsuIn->getJikokuhyouFontIndex();
//				aCdDrawTextProp.setCdFontProp(
//					getCDiagramEditDoc()->getCDedRosenFileData()
//					->getCdDedDispProp().getJikokuhyouFont(idxFont));
//			}
//			aCdDrawTextProp.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
//			pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
//
//			//	セルを無効化
//			InvalidateCell(iXColumnNumber, iYColumnNumber);
//		}
//		if (getCDiagramEditDoc()->getCDedRosenFileData()
//			->getCdDedDispProp().getDisplayRessyamei())
//		{
//			//	入区列車名
//			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
//				CdInOutLinkCodeListXColSpec::ColumnType_Ressyamei, 1));
//			Ou<CDcdTextbox> pCDcdTextbox =
//				getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
//
//			//列車名のテキスト
//			tstring strRessyamei = pCentDedRessyaIn->getRessyamei();
//			if (!pCentDedRessyaIn->getGousuu().empty())
//			{
//				strRessyamei += _T(" ");
//				strRessyamei += pCentDedRessyaIn->getGousuu();
//				strRessyamei += _T("号");
//			}
//			pCDcdTextbox->setText(strRessyamei);
//
//			//列車名のフォント属性
//			CdDrawTextProp	aCdDrawTextProp =
//				pCDcdTextbox->getCdDrawTextProp();
//			aCdDrawTextProp.setCdFontProp(fontpropDefault);
//			{
//				aCdDrawTextProp.setTextColor(pCentDedRessyasyubetsuIn->getJikokuhyouMojiColor());
//
//				int idxFont = pCentDedRessyasyubetsuIn->getJikokuhyouFontIndex();
//				aCdDrawTextProp.setCdFontProp(
//					getCDiagramEditDoc()->getCDedRosenFileData()
//					->getCdDedDispProp().getJikokuhyouFont(idxFont));
//			}
//			pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
//
//			//	セルを無効化
//			InvalidateCell(iXColumnNumber, iYColumnNumber);
//		}
//	}
//
//}

void  CWndDcdGridInOutLinkCodeList::OnUpdate_All()
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

		map<tstring, InOutLinkCodeContent> contInOutLinkCodeContent =
			getCentDedDia()->getcontInOutLinkCodeContent();

		const CentDedEkiCont* pCentDedEkiCont = getCDiagramEditDoc()->
			getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont();
		const Mu<const CentDedRessya*>* pCentDedRessyaConts[2];
		for (int iRessyahoukou = Ressyahoukou_Kudari;
			iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
		{
			pCentDedRessyaConts[iRessyahoukou] = getCentDedRessyaCont((ERessyahoukou)iRessyahoukou)->getMuPtr();
		}
		//const CdDedJikoku KitenJikoku = getCDiagramEditDoc()->getCDedRosenFileData()
		//	->getCentDedRosen()->getKitenJikoku();

		m_iRessyaCount = 0;

		for (auto itr = contInOutLinkCodeContent.begin();
			itr != contInOutLinkCodeContent.end(); itr++)
		{
			InOutLinkCodeContent& aInOutLinkCodeContent = itr->second;
			m_iRessyaCount += max(aInOutLinkCodeContent.contInRessyaProperty.size(),
				aInOutLinkCodeContent.contOutRessyaProperty.size());
		}

		//	X列数を増減させる
		//CdInOutLinkCodeListXColSpecCont aXColSpecCont = createXColSpecCont();
		//int iXCount = getCXDcdGrid()->getXColumnCount();
		//if (iXCount != aXColSpecCont.size())
		//{
			//フォント変更の場合、ヘッダー更新する必要があるので、全更新時は常に更新するようにする。
			OnCreate_Header();
		//}

		getCXDcdGrid()->setYColumnCount(createYColSpecCont().size());

			//	各セルに、データを設定

		CdFontProp fontpropDefault = createFontProp();
		CdColorProp colorpropDefault = createStringColorProp();
		CdInOutLinkCodeListXColSpecCont aXColSpecCont = createXColSpecCont();

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

		const CentDedRessyasyubetsuCont* pCentDedRessyasyubetsuCont =
			getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedRessyasyubetsuCont();

		int iYColumnNumber =  YCOLUMNNNO_RESSYA_0;
		for (auto itr = contInOutLinkCodeContent.begin();
			itr != contInOutLinkCodeContent.end(); itr++)
		{
			InOutLinkCodeContent& aInOutLinkCodeContent = itr->second;
			int iRessyaCount = max(aInOutLinkCodeContent.contInRessyaProperty.size(),
				aInOutLinkCodeContent.contOutRessyaProperty.size());

			for (int iRessyaIndex = 0; iRessyaIndex < iRessyaCount; iRessyaIndex++)
			{
				// --------------------------------
				//	行のY方向サイズを設定
				// --------------------------------
				{
					CDcdTargetGetDC	aCDcdTarget(NULL);

					CdDcdSizeXy	sizeRessyamei;
					CDcdTextbox	aCDcdTextbox(_T("京都京都京都"),
						fontpropDefault,
						_T(""), 1, 2, 2);
					aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeRessyamei);

					getCXDcdGrid()->getYColumn(iYColumnNumber)->setColumnSize(sizeRessyamei.getY());
				}
				{
					//	入出区連携コード
					int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
						CdInOutLinkCodeListXColSpec::ColumnType_InOutLinkCode));
					Ou<CDcdTextbox> pCDcdTextbox =
						getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
					tstring strText = _T("");
					if (iRessyaIndex == 0)
					{
						strText = itr->first;
					}
					pCDcdTextbox->setText(strText);

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
					//	入区側方向・列車番号・種別
					int iXColumnNumber1 = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
						CdInOutLinkCodeListXColSpec::ColumnType_InRessyahoukou));
					int iXColumnNumber2 = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
						CdInOutLinkCodeListXColSpec::ColumnType_InRessyabangou));
					int iXColumnNumber3 = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
						CdInOutLinkCodeListXColSpec::ColumnType_InRessyasyubetsu));
					Ou<CDcdTextbox> pCDcdTextbox1 =
						getCXDcdGrid()->getCell(iXColumnNumber1, iYColumnNumber)->getIfDcDraw();
					Ou<CDcdTextbox> pCDcdTextbox2 =
						getCXDcdGrid()->getCell(iXColumnNumber2, iYColumnNumber)->getIfDcDraw();
					Ou<CDcdTextbox> pCDcdTextbox3 =
						getCXDcdGrid()->getCell(iXColumnNumber3, iYColumnNumber)->getIfDcDraw();

					tstring strRessyahoukou;
					tstring strRessyabangou;
					tstring strRessyaSyubetsu;

					if (iRessyaIndex < (int)aInOutLinkCodeContent.contInRessyaProperty.size())
					{
						if (aInOutLinkCodeContent.contInRessyaProperty[iRessyaIndex].getRessyahoukou()
							== ERessyahoukou::Ressyahoukou_Kudari)
						{
							strRessyahoukou = strRessyahoukouKudari;
						}
						else
						{
							strRessyahoukou = strRessyahoukouNobori;
						}
						const CentDedRessya* pCentDedRessya = pCentDedRessyaConts[(int)aInOutLinkCodeContent.contInRessyaProperty[iRessyaIndex].getRessyahoukou()]
							->get(aInOutLinkCodeContent.contInRessyaProperty[iRessyaIndex].getRessyaIndex());
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
					}
					pCDcdTextbox1->setText(strRessyahoukou);
					pCDcdTextbox2->setText(strRessyabangou);
					pCDcdTextbox3->setText(strRessyaSyubetsu);

					//	セルを無効化
					InvalidateCell(iXColumnNumber1, iYColumnNumber);
					InvalidateCell(iXColumnNumber2, iYColumnNumber);
					InvalidateCell(iXColumnNumber3, iYColumnNumber);
				}
				{
					//	矢印
					int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
						CdInOutLinkCodeListXColSpec::ColumnType_Arrow));
					Ou<CDcdTextbox> pCDcdTextbox =
						getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
					tstring strText = _T("");
					if (aInOutLinkCodeContent.iStatus == 2)
					{
						strText = _T("→");
					}
					pCDcdTextbox->setText(strText);

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
					//	出区側方向・列車番号・種別
					int iXColumnNumber1 = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
						CdInOutLinkCodeListXColSpec::ColumnType_OutRessyahoukou));
					int iXColumnNumber2 = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
						CdInOutLinkCodeListXColSpec::ColumnType_OutRessyabangou));
					int iXColumnNumber3 = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
						CdInOutLinkCodeListXColSpec::ColumnType_OutRessyasyubetsu));
					Ou<CDcdTextbox> pCDcdTextbox1 =
						getCXDcdGrid()->getCell(iXColumnNumber1, iYColumnNumber)->getIfDcDraw();
					Ou<CDcdTextbox> pCDcdTextbox2 =
						getCXDcdGrid()->getCell(iXColumnNumber2, iYColumnNumber)->getIfDcDraw();
					Ou<CDcdTextbox> pCDcdTextbox3 =
						getCXDcdGrid()->getCell(iXColumnNumber3, iYColumnNumber)->getIfDcDraw();

					tstring strRessyahoukou;
					tstring strRessyabangou;
					tstring strRessyaSyubetsu;

					if (iRessyaIndex < (int)aInOutLinkCodeContent.contOutRessyaProperty.size())
					{
						if (aInOutLinkCodeContent.contOutRessyaProperty[iRessyaIndex].getRessyahoukou()
							== ERessyahoukou::Ressyahoukou_Kudari)
						{
							strRessyahoukou = strRessyahoukouKudari;
						}
						else
						{
							strRessyahoukou = strRessyahoukouNobori;
						}
						const CentDedRessya* pCentDedRessya = pCentDedRessyaConts[(int)aInOutLinkCodeContent.contOutRessyaProperty[iRessyaIndex].getRessyahoukou()]
							->get(aInOutLinkCodeContent.contOutRessyaProperty[iRessyaIndex].getRessyaIndex());
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
					}
					pCDcdTextbox1->setText(strRessyahoukou);
					pCDcdTextbox2->setText(strRessyabangou);
					pCDcdTextbox3->setText(strRessyaSyubetsu);

					//	セルを無効化
					InvalidateCell(iXColumnNumber1, iYColumnNumber);
					InvalidateCell(iXColumnNumber2, iYColumnNumber);
					InvalidateCell(iXColumnNumber3, iYColumnNumber);
				}
				{
					//	運用番号
					int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
						CdInOutLinkCodeListXColSpec::ColumnType_OperationNumber));
					Ou<CDcdTextbox> pCDcdTextbox =
						getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
					tstring strOperationNumber;
					if (aInOutLinkCodeContent.iStatus == 2)
					{
						strOperationNumber = joinc('+', aInOutLinkCodeContent.strOperationNumber);
					}
					pCDcdTextbox->setText(strOperationNumber);

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
				iYColumnNumber++;
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

void CWndDcdGridInOutLinkCodeList::OnCreate_Header()
{
	// --------------------------------
	//	入出区連携コード一覧ビューに使用するフォント
	// --------------------------------
	CdFontProp fontpropDefault = createFontProp();
	CdColorProp colorpropDefault = createStringColorProp();

	CdInOutLinkCodeListXColSpecCont aXColSpecCont = createXColSpecCont();
	// --------------------------------
	//	列の数を指定
	// --------------------------------

	getCXDcdGrid()->setXColumnCount(aXColSpecCont.size());
	getCXDcdGrid()->setXFixColumnCount(1);

	//bool bDisplayRessyamei = getCDiagramEditDoc()->getCDedRosenFileData()
	//	->getCdDedDispProp().getDisplayRessyamei();

	// --------------------------------
	//	列のサイズを設定
	// --------------------------------
	{
		CDcdTargetGetDC	aCDcdTarget(NULL);
		// --------------------------------
		//	X列
		// --------------------------------
		tstring strCellInOutLinkCodeWidth(
			getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp().getJikokuhyouRessyaWidth(), '0');
		if (strCellInOutLinkCodeWidth.length() < 10)
		{
			strCellInOutLinkCodeWidth = tstring(10, '0');
		}

		tstring strCellRessyaBangouWidth(
			getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp().getJikokuhyouRessyaWidth(), '0');
		if (strCellRessyaBangouWidth.length() < 8)
		{
			strCellRessyaBangouWidth = tstring(8, '0');
		}


		tstring strCellOperationNumberWidth(
			getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp().getJikokuhyouRessyaWidth() *
			getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp().getOperationNumberRows(), '0');
		if (strCellOperationNumberWidth.length() < 8)
		{
			strCellOperationNumberWidth= _T("00000000");
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
		{
			//	入出区連携コード
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
				CdInOutLinkCodeListXColSpec::ColumnType_InOutLinkCode));
			CdDcdSizeXy	sizeOperationTable;
			CDcdTextbox	aCDcdTextbox(
				strCellInOutLinkCodeWidth,
				fontpropDefault,
				_T(""), 1, 2, 2);
			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeOperationTable);
			getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeOperationTable.getX());
		}
		{
			//	列車方向(入区側)
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
				CdInOutLinkCodeListXColSpec::ColumnType_InRessyahoukou));
			CdDcdSizeXy	sizeOperationTable;
			CDcdTextbox	aCDcdTextbox(
				strRessyahoukou,
				fontpropDefault,
				_T(""), 1, 2, 2);
			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeOperationTable);
			getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeOperationTable.getX());
		}
		{
			//	列車番号(入区側)
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
				CdInOutLinkCodeListXColSpec::ColumnType_InRessyabangou));
			CdDcdSizeXy	sizeOperationTable;
			CDcdTextbox	aCDcdTextbox(
				strCellRessyaBangouWidth,
				fontpropDefault,
				_T(""), 1, 2, 2);
			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeOperationTable);
			getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeOperationTable.getX());
		}
		{
			//	種別(入区側)
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
				CdInOutLinkCodeListXColSpec::ColumnType_InRessyasyubetsu));
			CdDcdSizeXy	sizeOperationTable;
			CDcdTextbox	aCDcdTextbox(
				strCellRessyasyubetsuWidth,
				fontpropDefault,
				_T(""), 1, 2, 2);
			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeOperationTable);
			getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeOperationTable.getX());
		}
		{
			//	矢印
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
				CdInOutLinkCodeListXColSpec::ColumnType_Arrow));
			CdDcdSizeXy	sizeOperationTable;

			CDcdTextbox	aCDcdTextbox(
				_T("京都"),
				fontpropDefault,
				_T(""), 1, 2, 2);
			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeOperationTable);

			getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeOperationTable.getX());
		}
		{
			//	列車方向(出区側)
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
				CdInOutLinkCodeListXColSpec::ColumnType_OutRessyahoukou));
			CdDcdSizeXy	sizeOperationTable;
			CDcdTextbox	aCDcdTextbox(
				strRessyahoukou,
				fontpropDefault,
				_T(""), 1, 2, 2);
			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeOperationTable);
			getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeOperationTable.getX());
		}
		{
			//	列車番号(出区側)
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
				CdInOutLinkCodeListXColSpec::ColumnType_OutRessyabangou));
			CdDcdSizeXy	sizeOperationTable;
			CDcdTextbox	aCDcdTextbox(
				strCellRessyaBangouWidth,
				fontpropDefault,
				_T(""), 1, 2, 2);
			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeOperationTable);
			getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeOperationTable.getX());
		}
		{
			//	種別(出区側)
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
				CdInOutLinkCodeListXColSpec::ColumnType_OutRessyasyubetsu));
			CdDcdSizeXy	sizeOperationTable;
			CDcdTextbox	aCDcdTextbox(
				strCellRessyasyubetsuWidth,
				fontpropDefault,
				_T(""), 1, 2, 2);
			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeOperationTable);
			getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeOperationTable.getX());
		}
		{
			//	運用番号
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
				CdInOutLinkCodeListXColSpec::ColumnType_OperationNumber));
			CdDcdSizeXy	sizeOperationTable;
			CDcdTextbox	aCDcdTextbox(
				strCellOperationNumberWidth,
				//"0" ,
				fontpropDefault,
				_T(""), 1, 2, 2);
			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeOperationTable);
			getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeOperationTable.getX());
		}
		// --------------------------------
		//	Y列
		// --------------------------------
		{
			CdDcdSizeXy	sizeOperationTable;
			CDcdTextbox	aCDcdTextbox(
				_T("京都京都"),
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
		// 入出区連携コード
		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
			CdInOutLinkCodeListXColSpec::ColumnType_InOutLinkCode));

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
		pCDcdTextbox->setText(_T("連携コード"));
	}
	{
		// 列車方向(入区側)
		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
			CdInOutLinkCodeListXColSpec::ColumnType_InRessyahoukou));

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
		pCDcdTextbox->setText(_T("入区"));

		Ou<CDcdLine>
			(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())
			->setCdPenProp(getCdPenPropDotLine());
	}
	{
		// 列車番号(入区側)
		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
			CdInOutLinkCodeListXColSpec::ColumnType_InRessyabangou));

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
		// 種別名(入区側)
		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
			CdInOutLinkCodeListXColSpec::ColumnType_InRessyasyubetsu));

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
		Ou<CDcdLine>
			(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())
			->setCdPenProp(getCdPenPropNarrowLine());
	}
	{
		// 矢印
		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
			CdInOutLinkCodeListXColSpec::ColumnType_Arrow));

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
	{
		// 列車方向(出区側)
		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
			CdInOutLinkCodeListXColSpec::ColumnType_OutRessyahoukou));

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
		pCDcdTextbox->setText(_T("出区"));

		Ou<CDcdLine>
			(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())
			->setCdPenProp(getCdPenPropDotLine());
	}
	{
		// 列車番号(出区側)
		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
			CdInOutLinkCodeListXColSpec::ColumnType_OutRessyabangou));

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
		// 種別名(出区側)
		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
			CdInOutLinkCodeListXColSpec::ColumnType_OutRessyasyubetsu));

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
		Ou<CDcdLine>
			(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())
			->setCdPenProp(getCdPenPropNarrowLine());
	}
	{
		// 運用番号
		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdInOutLinkCodeListXColSpec(
			CdInOutLinkCodeListXColSpec::ColumnType_OperationNumber));

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
		pCDcdTextbox->setText(_T("運用番号"));
	}
}

	// --------------------------------
	//@name メニューコマンドの下請関数
	// --------------------------------

int CWndDcdGridInOutLinkCodeList::OnInOutLinkCodeListMovetojikokuhyou_Process(BOOL bQueryEnable)
{
	int iRv = 0;
	if (iRv >= 0)
	{
		if (getCentDedDia()->getWaitOperationUpdate())
		{
			iRv = -1;	//運用更新抑止状態です
		}
	}
	CdInOutLinkCodeListYColSpec aCdInOutLinkCodeListYColSpec = getYColSpecOfFocus();
	if (iRv >= 0)
	{
		if (getCSelect()->getSelectedCellCount() == 0)
		{
			if (aCdInOutLinkCodeListYColSpec.getColumnType() !=
				CdInOutLinkCodeListYColSpec::ColumnType_Ressya)
			{
				iRv = -3;	//フォーカスが列車位置以外なら不可
			}
		}
		else
		{
			iRv = -4; //複数選択は不可
		}

	}
	CdInOutLinkCodeListXColSpec aCdInOutLinkCodeListXColSpec = getXColSpecOfFocus();
	if (iRv >= 0)
	{
		if (aCdInOutLinkCodeListXColSpec.getColumnType() != CdInOutLinkCodeListXColSpec::ColumnType_InRessyahoukou &&
			aCdInOutLinkCodeListXColSpec.getColumnType() != CdInOutLinkCodeListXColSpec::ColumnType_InRessyabangou &&
			aCdInOutLinkCodeListXColSpec.getColumnType() != CdInOutLinkCodeListXColSpec::ColumnType_InRessyasyubetsu &&
			aCdInOutLinkCodeListXColSpec.getColumnType() != CdInOutLinkCodeListXColSpec::ColumnType_OutRessyahoukou &&
			aCdInOutLinkCodeListXColSpec.getColumnType() != CdInOutLinkCodeListXColSpec::ColumnType_OutRessyabangou &&
			aCdInOutLinkCodeListXColSpec.getColumnType() != CdInOutLinkCodeListXColSpec::ColumnType_OutRessyasyubetsu)
		{
			iRv = -5;	//フォーカスが入区出区位置以外なら不可
		}
	}

	if (!bQueryEnable && iRv >= 0)
	{
		int iTargetIndex = aCdInOutLinkCodeListYColSpec.getRessyaIndex();
		ERessyahoukou eRessyahoukou;
		int iRessyaidx;

		map<tstring, InOutLinkCodeContent> contInOutLinkCodeContent =
			getCentDedDia()->getcontInOutLinkCodeContent();

		int iYColumnNumber = 0;
		for (auto itr = contInOutLinkCodeContent.begin();
			itr != contInOutLinkCodeContent.end(); itr++)
		{
			InOutLinkCodeContent& aInOutLinkCodeContent = itr->second;
			if (iYColumnNumber + (int)max(aInOutLinkCodeContent.contInRessyaProperty.size(),
				aInOutLinkCodeContent.contOutRessyaProperty.size()) <= iTargetIndex)
			{
				iYColumnNumber += max(aInOutLinkCodeContent.contInRessyaProperty.size(),
					aInOutLinkCodeContent.contOutRessyaProperty.size());
			}
			else
			{
				int iOffset = iTargetIndex - iYColumnNumber;
				if (aCdInOutLinkCodeListXColSpec.getColumnType() == CdInOutLinkCodeListXColSpec::ColumnType_InRessyahoukou ||
					aCdInOutLinkCodeListXColSpec.getColumnType() == CdInOutLinkCodeListXColSpec::ColumnType_InRessyabangou ||
					aCdInOutLinkCodeListXColSpec.getColumnType() == CdInOutLinkCodeListXColSpec::ColumnType_InRessyasyubetsu)
				{
					if ((int)aInOutLinkCodeContent.contInRessyaProperty.size() > iOffset)
					{
						eRessyahoukou = aInOutLinkCodeContent.contInRessyaProperty[iOffset].getRessyahoukou();
						iRessyaidx = aInOutLinkCodeContent.contInRessyaProperty[iOffset].getRessyaIndex();
					}
					else
					{
						iRv = -6;
					}
				}
				else if (aCdInOutLinkCodeListXColSpec.getColumnType() == CdInOutLinkCodeListXColSpec::ColumnType_OutRessyahoukou ||
					aCdInOutLinkCodeListXColSpec.getColumnType() == CdInOutLinkCodeListXColSpec::ColumnType_OutRessyabangou ||
					aCdInOutLinkCodeListXColSpec.getColumnType() == CdInOutLinkCodeListXColSpec::ColumnType_OutRessyasyubetsu)
				{
					if ((int)aInOutLinkCodeContent.contOutRessyaProperty.size() > iOffset)
					{
						eRessyahoukou = aInOutLinkCodeContent.contOutRessyaProperty[iOffset].getRessyahoukou();
						iRessyaidx = aInOutLinkCodeContent.contOutRessyaProperty[iOffset].getRessyaIndex();
					}
					else
					{
						iRv = -7;
					}
				}
				break;
			}
			m_iRessyaCount += max(aInOutLinkCodeContent.contInRessyaProperty.size(),
				aInOutLinkCodeContent.contOutRessyaProperty.size());
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

// ****************************************************************
//	CWndDcdGridEkiTrack2
// ****************************************************************


// ********************************
//	コンストラクタ
// ********************************
CWndDcdGridInOutLinkCodeList::CWndDcdGridInOutLinkCodeList()
	: m_bUpdate_All_Requested( false )
	, m_bInitialUpdateComplete(false)
	, m_iRessyaCount(0)
{
	//getCSelect()->setSelectMode( CSelect::SelectMode_YColumn ) ;
	getCSelect()->setSelectMode(CSelect::SelectMode_NONE);
}
CWndDcdGridInOutLinkCodeList::~CWndDcdGridInOutLinkCodeList()
{
}

// ********************************
//@name	CDcdGrid
// ********************************

// ********************************
//@name	CWndDcdGrid
// ********************************

	// ********************************
	//@name CWndDcdGridInOutLinkCodeList-操作
	// ********************************

CInOutLinkCodeListDoc * CWndDcdGridInOutLinkCodeList::GetDocument()
{
	CView* pCView = (CView*)GetParent();
	return (CInOutLinkCodeListDoc*)pCView->GetDocument();
}

const CentDedDia*	CWndDcdGridInOutLinkCodeList::getCentDedDia()
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

const CentDedRessyaCont*	CWndDcdGridInOutLinkCodeList::getCentDedRessyaCont(
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
BEGIN_MESSAGE_MAP(CWndDcdGridInOutLinkCodeList,CWndDcdGridInOutLinkCodeList::super)
	//{{AFX_MSG_MAP(CWndDcdGridInOutLinkCodeList)
	ON_WM_CREATE()
	ON_WM_KEYUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KEYDOWN()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_InOutLinkCodeList_MoveToJikokuhyou, &CWndDcdGridInOutLinkCodeList::OnInOutLinkCodeListMovetojikokuhyou)
	ON_UPDATE_COMMAND_UI(ID_InOutLinkCodeList_MoveToJikokuhyou, &CWndDcdGridInOutLinkCodeList::OnUpdateInOutLinkCodeListMovetojikokuhyou)
	END_MESSAGE_MAP()

int CWndDcdGridInOutLinkCodeList::OnCreate(LPCREATESTRUCT lpCreateStruct)
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
	getCXDcdGrid()->setYColumnCount(YCOLUMNNNO_RESSYA_0);
	getCXDcdGrid()->setYFixColumnCount(YCOLUMNNNO_RESSYA_0);
	OnCreate_Header();


	// --------------------------------
	//	フォーカスセルの初期位置を設定
	// --------------------------------
	getCFocus()->setFocusCell( getCXDcdGrid()->getCell( 0 , YCOLUMNNNO_RESSYA_0) ) ;
	// --------------------------------
	//	表示更新
	// --------------------------------
	InvalidateGrid() ;

	
	return 0;
}




void CWndDcdGridInOutLinkCodeList::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
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

		CInOutLinkCodeListDoc* pCInOutLinkCodeListDoc = (CInOutLinkCodeListDoc*)GetDocument();

		if ( GetParent() == pView )
		{
			OnUpdate_All() ;
		}
		else
		{
			LogMsg(_T("CWndDcdGridInOutLinkCodeList::OnUpdate()")
				_T("m_bUpdate_All_Requested=true") ) ;
			m_bUpdate_All_Requested = true ;
		}
	}
	
	int iYColumnBegin = createYColSpecCont().ColumnNumberFromSpec( 
		CdInOutLinkCodeListYColSpec(CdInOutLinkCodeListYColSpec::ColumnType_Ressya, 0 ) ) ;

	getCSelect()->setColumnNumberSelectLimit(
		CdDcdZoneXy( 
			CdDcdZone( 0 , INT_MAX ) ,
			CdDcdZone( iYColumnBegin , getCentDedDia()->getcontOperationTableContent().size())
		) );

}

void CWndDcdGridInOutLinkCodeList::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	LogMsg(_T("CWndDcdGridInOutLinkCodeList::OnActivateView(%d,,)") , bActivate ) ;
	
	if ( bActivate && m_bUpdate_All_Requested )
	{
		OnUpdate_All() ;
	}
}

void CWndDcdGridInOutLinkCodeList::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CMenu	aMenu ;
	aMenu.LoadMenu(IDR_MENU_INOUTLINKCODELIST_CONTEXT) ;
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

void CWndDcdGridInOutLinkCodeList::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	OnInOutLinkCodeListMovetojikokuhyou_Process(FALSE);
}

void CWndDcdGridInOutLinkCodeList::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
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
	//	CdInOutLinkCodeListYColSpec aCdInOutLinkCodeListYColSpec = getYColSpecOfFocus();
	//	if (iRv >= 0)
	//	{
	//		if (getCSelect()->getSelectedCellCount() == 0)
	//		{
	//			if (aCdInOutLinkCodeListYColSpec.getColumnType() !=
	//				CdInOutLinkCodeListYColSpec::ColumnType_Operation)
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


void CWndDcdGridInOutLinkCodeList::OnInOutLinkCodeListMovetojikokuhyou()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	OnInOutLinkCodeListMovetojikokuhyou_Process(FALSE);
}


void CWndDcdGridInOutLinkCodeList::OnUpdateInOutLinkCodeListMovetojikokuhyou(CCmdUI *pCmdUI)
{
	// TODO:ここにコマンド更新 UI ハンドラー コードを追加します。
	pCmdUI->Enable(OnInOutLinkCodeListMovetojikokuhyou_Process(TRUE) >= 0);
}

} //namespace ViewInOutLinkCodeList