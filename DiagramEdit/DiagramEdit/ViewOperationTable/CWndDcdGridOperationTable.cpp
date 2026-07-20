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
//	CWndDcdGridOperationTable.cpp
//	$Id: CWndDcdGridOperationTable.cpp  $
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

#include "..\resource.h"
#include "..\entDed\CentDedRosen.h"
#include "..\DiagramEdit.h"
#include "..\CRfEditCmdHolder.h"
#include "..\DedRosenFileData\EditCmd\EditCmd.h"
#include "CWndDcdGridOperationTable.h"
#include "OperationTableColSpec\OperationTableColSpec.h"
#include "MfcUtil/MfcUtil.h"
//#include "CDlgOperationTableCsvExport.h"
//#include "str\CsvDocument\CdCsvDocument.h"
#include "str\CsvDocument\CconvCsvDocument.h"
#include "str\vectorToFile.h"
#include "..\ViewDiagram\cdeddiagramview.h"
#include "DcDraw\CDcdLine.h"
//#include "DcdCd/DcDrawProp\cddcdfreelineprop.h"


// ****************************************************************
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
// ****************************************************************

namespace ViewOperationTable {
using namespace std ;

// --------------------------------
///@name	X列番号
// --------------------------------
///@{
/**
X列番号：列車番号
*/
//const int XCOLUMNNNO_RESSYANUM = 0 ;
/**
X列番号：種別
*/
//const int XCOLUMNNNO_SYUBETSU = 1 ;
/**
X列番号：列車名
*/
//const int XCOLUMNNNO_RESSYAMEI = 2 ;
/**
X列番号：起点側始終着駅名
*/
//const int XCOLUMNNNO_OSEKIMEI = 3 ;
/**
X列番号：起点側駅時刻
*/
//const int XCOLUMNNNO_OSEKIJIKOKU = 4;
/**
X列番号：列車方向(矢印)
*/
//const int XCOLUMNNNO_RESSYAHOUKOU = 5;
/**
X列番号：終点側始終着駅名
*/
//const int XCOLUMNNNO_TSEKIMEI = 6;
/**
X列番号：終点側駅時刻
*/
//const int XCOLUMNNNO_TSEKIJIKOKU = 7;
/**
X列番号：X列数
*/
//const int XCOLUMNNCOUNT = 8 ;
///@}


// --------------------------------
///@name	Y列番号
// --------------------------------
///@{
/**
Y列番号：ヘッダ列
*/
const int YCOLUMNNNO_HEADER = 0 ;
/**
Y列番号：列車の0番目
*/
const int YCOLUMNNNO_RESSYA_0 = 1 ;
/**
Y列番号：番線の後の列数
*/
//const int YCOLUMNNCOUNT_BLANK = 1 ;
///@}

/**
@return
	列車種別ビューのフォントの属性を返します。
*/
static CdFontProp createFontProp()
{
	CdDedDispProp aCdDedDispProp = getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
	return aCdDedDispProp.getOperationTableFont();
	//return aCdDedDispProp.getJikokuhyouFont(0);
	//return ( CConverter_WinGdi().CdFontPropOf( DEFAULT_GUI_FONT ) ) ;
}

static CdFontProp createBigFontProp()
{
	CdDedDispProp aCdDedDispProp = getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
	CdFontProp aCdFontProp = aCdDedDispProp.getOperationTableFont();
	aCdFontProp.setPointTextHeight(aCdFontProp.getPointTextHeight() * 2);
	return aCdDedDispProp.getOperationTableFont();
	//return aCdDedDispProp.getJikokuhyouFont(0);
	//return ( CConverter_WinGdi().CdFontPropOf( DEFAULT_GUI_FONT ) ) ;
}
/**
@return
	運用ビューの文字の色を返します。
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
	運用ビューの罫線の色を返します。
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
CdOperationTableXColSpecCont
CWndDcdGridOperationTable::createXColSpecCont()
{
	CdOperationTableXColSpecCont aSpecCont(
		getDisplayExtensionOperationTable(),
		getCDiagramEditDoc()->getCDedRosenFileData()
		->getCdDedDispProp().getDisplayRessyamei(),
		getDisplayTrackName(),
		m_iDisplayJikokuEkiIndex);
	return aSpecCont ;
}

CdOperationTableYColSpecCont
CWndDcdGridOperationTable::createYColSpecCont()
{
	CdOperationTableYColSpecCont aSpecCont(
		m_contOperationTable.size(),
		m_bDisplayExtensionOperationTable);
	return aSpecCont ;
}

CdOperationTableXColSpec
CWndDcdGridOperationTable::getXColSpecOfFocus()
{
	CdOperationTableXColSpec aSpec ;
	CdDcdPosXy aPos = getCFocus()->getFocusCellColumnNumber() ;
	if ( aPos != getCFocus()->ColumnNumberPosXy_NULL() )
	{
		CdOperationTableXColSpecCont aSpecCont(
			getDisplayExtensionOperationTable(),
			getCDiagramEditDoc()->getCDedRosenFileData()
			->getCdDedDispProp().getDisplayRessyamei(),
			getDisplayTrackName(),
			m_iDisplayJikokuEkiIndex);
		aSpec = aSpecCont.ColumnNumberToSpec( aPos.getX() ) ;
	}
	return aSpec ;
}

CdOperationTableYColSpec
CWndDcdGridOperationTable::getYColSpecOfFocus()
{
	CdOperationTableYColSpec aSpec ;
	CdDcdPosXy aPos = getCFocus()->getFocusCellColumnNumber() ;
	if ( aPos != getCFocus()->ColumnNumberPosXy_NULL() )
	{
		CdOperationTableYColSpecCont aSpecCont(
			m_contOperationTable.size(),
			m_bDisplayExtensionOperationTable);
		aSpec = aSpecCont.ColumnNumberToSpec( aPos.getY() ) ;
	}
	return aSpec ;
}
	
	// --------------------------------
	//@name OnUpdate の下請関数
	// --------------------------------

const CdDedJikoku::CConv
CWndDcdGridOperationTable::getCdDedJikokuConv()const
{
//	if (m_bDisplaySecondEkiJikoku)
//	{
//		if (m_bDisplayColonEkiJikoku)
//		{
//			static CdDedJikoku::CConv aConv(
//				false,		//	コロン有
//							// 時が 00 から 09 の場合、10の位の "0" をスペースにします。
//				CdDedJikoku::CConv::EHour_ZeroToSpace,
//				CdDedJikoku::CConv::ESecond_Output 	// 秒を表示します
//			);
//			return aConv;
//		}
//		else
//		{
//			static CdDedJikoku::CConv aConv(
//				true,		//	コロン無
//							// 時が 00 から 09 の場合、10の位の "0" をスペースにします。
//				CdDedJikoku::CConv::EHour_ZeroToSpace,
//				CdDedJikoku::CConv::ESecond_Output 	// 秒を表示します
//			);
//			return aConv;
//		}
//	}
//	else
//	{
//		if (m_bDisplayColonEkiJikoku)
//		{
//			static CdDedJikoku::CConv aConv(
//				false,		//	コロン有
//							// 時が 00 から 09 の場合、10の位の "0" をスペースにします。
//				CdDedJikoku::CConv::EHour_ZeroToSpace,
//				CdDedJikoku::CConv::ESecond_NoSecond 	// 秒を常に出力しません。
//			);
//			return aConv;
//		}
//		else
//		{
//			static CdDedJikoku::CConv aConv(
//				true,		//	コロン無
//							// 時が 00 から 09 の場合、10の位の "0" をスペースにします。
//				CdDedJikoku::CConv::EHour_ZeroToSpace,
//				CdDedJikoku::CConv::ESecond_NoSecond 	// 秒を常に出力しません。
//			);
//			return aConv;
//		}
//	}

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

void CWndDcdGridOperationTable::OnUpdate_setCentDedRessya_To_Column(
	int iYColumnNumber ,
	const CentDedRessya& aShihatsuRessya,
	const CentDedRessya& aShuchakuRessya,
	const OperationTableContent& aSihatsuOperationTableContent,
	const OperationTableContent& aShuchakuOperationTableContent,
	const ERessyahoukou eRessyahoukou)
{
	CdFontProp fontpropDefault = createFontProp() ;
	CdFontProp fontpropBig = createFontProp();
	//fontpropBig.setPointTextHeight(fontpropBig.getPointTextHeight() * 2);
	CdColorProp colorpropDefault = createStringColorProp();
	CdOperationTableXColSpecCont aXColSpecCont = createXColSpecCont();

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
	//const Mu<CentDedEkiCont::CdDedEki>* pCdDedEkiCont =
	//	getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(aCentDedRessya.getRessyahoukou());
	const CentDedEkiCont* pCentDedEkiCont =
		getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont();

	const CentDedRessyasyubetsuCont* pCentDedRessyasyubetsuCont =
		getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedRessyasyubetsuCont();
	const CentDedRessyasyubetsu* pCentDedRessyasyubetsu = pCentDedRessyasyubetsuCont
		->getMuPtr()->get(aShihatsuRessya.getRessyasyubetsuIndex());
	if (m_bDisplayParentSyubetsu && pCentDedRessyasyubetsu->getParentSyubetsuIndex() >= 0)
	{
		pCentDedRessyasyubetsu = pCentDedRessyasyubetsuCont
			->getMuPtr()->get(pCentDedRessyasyubetsu->getParentSyubetsuIndex());
	}

	int iSihatsuEkiOrder = aSihatsuOperationTableContent.iSihatsuEkiOrder;
	if (!aShihatsuRessya.isRunBetweenNextEki(iSihatsuEkiOrder))
	{
		iSihatsuEkiOrder = aShihatsuRessya.getRunBetweenEkiForward(iSihatsuEkiOrder);
	}
	int iSihatsuEkiIndex = aShihatsuRessya.EkiIndexOfEkiOrder(iSihatsuEkiOrder);




	int iSyuuchakuEkiOrder = aShuchakuOperationTableContent.iSyuuchakuEkiOrder;
	if (!aShuchakuRessya.isRunBetweenNextEki(iSyuuchakuEkiOrder - 1))
	{
		iSyuuchakuEkiOrder = aShuchakuRessya.getRunBetweenEkiBackward(iSyuuchakuEkiOrder);
	}
	int iSyuuchakuEkiIndex = aShuchakuRessya.EkiIndexOfEkiOrder(iSyuuchakuEkiOrder);
	
	/**
		複数列車を一本化している場合は、列車情報(列車番号等)は、aShihatsuRessya(先頭列車)からとります
	*/
	{
		//	列車番号
		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
			CdOperationTableXColSpec::EColumnType::ColumnType_Ressyabangou));
		Ou<CDcdTextbox> pCDcdTextbox = 
			getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber )->getIfDcDraw() ;
		pCDcdTextbox->
			setText(aShihatsuRessya.getRessyabangou() )  ;

		//	フォント属性
		CdDrawTextProp	aCdDrawTextProp = 
				pCDcdTextbox->getCdDrawTextProp() ;
		aCdDrawTextProp.setCdFontProp( fontpropDefault ) ;
		aCdDrawTextProp.setTextColor(colorpropDefault);
		aCdDrawTextProp.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
		pCDcdTextbox->setCdDrawTextProp( aCdDrawTextProp )  ;	

		getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->setAttachCellCount(1, 1);

		//	セルを無効化
		InvalidateCell(iXColumnNumber, iYColumnNumber ) ;
	}
	{
		//	種別
		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
			CdOperationTableXColSpec::EColumnType::ColumnType_Ressyasyubetsu));
		Ou<CDcdTextbox> pCDcdTextbox =
			getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
		
		//種別のテキスト
		//pCDcdTextbox->setText(
		//	pCentDedRessyasyubetsuCont->get(aCentDedRessya.getRessyasyubetsuIndex()).getRyakusyou());
		pCDcdTextbox->setText(pCentDedRessyasyubetsu->getSyubetsumei());
		
		//種別のフォント属性
		CdDrawTextProp	aCdDrawTextProp = 
				pCDcdTextbox->getCdDrawTextProp() ;
		aCdDrawTextProp.setCdFontProp(fontpropDefault);
		{
			aCdDrawTextProp.setTextColor(pCentDedRessyasyubetsu->getJikokuhyouMojiColor() ) ;

			int idxFont = pCentDedRessyasyubetsu->getJikokuhyouFontIndex();
			aCdDrawTextProp.setCdFontProp( 
				getCDiagramEditDoc()->getCDedRosenFileData()
					->getCdDedDispProp().getJikokuhyouFont( idxFont ) ) ;
		}
		aCdDrawTextProp.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
		pCDcdTextbox->setCdDrawTextProp( aCdDrawTextProp )  ;	

		getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->setAttachCellCount(1, 1);

		//	セルを無効化
		InvalidateCell(iXColumnNumber, iYColumnNumber ) ;
	}
	if(getCDiagramEditDoc()->getCDedRosenFileData()
		->getCdDedDispProp().getDisplayRessyamei())
	{
		//	列車名
		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
			CdOperationTableXColSpec::EColumnType::ColumnType_Ressyamei));
		Ou<CDcdTextbox> pCDcdTextbox =
			getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();

		//列車名のテキスト
		tstring strRessyamei = aShihatsuRessya.getRessyamei();
		if (!aShihatsuRessya.getGousuu().empty())
		{
			strRessyamei += _T(" ");
			strRessyamei += aShihatsuRessya.getGousuu();
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

		getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->setAttachCellCount(1, 1);

		//	セルを無効化
		InvalidateCell(iXColumnNumber, iYColumnNumber);
	}

	/**
		始発終着駅の駅名と時刻取得について
		・路線外始発の場合は、ほぼ従来通り。
			Before,AfterOperationから路線外始発/終着駅Indexを取得、駅Orderと合わせて、駅名を取得
		・入出区・前次列車接続の場合
			iEkiOrderをもとに、その駅の発/着時刻を取得するが、isRunBetweenNextEkiを見るようにする
	*/
	{
		//	始発駅名&始発駅時刻
		int iXColumnNumber1;
		int iXColumnNumber2;
		//bool bIsHatsuJikoku = eRessyahoukou == Ressyahoukou_Kudari ||
		//	getDisplayNoboriLeftToRight();
		if (eRessyahoukou == Ressyahoukou_Kudari ||
			getDisplayNoboriLeftToRight())
		{
			iXColumnNumber1 = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
				CdOperationTableXColSpec::EColumnType::ColumnType_OriginSideEkimei));
			iXColumnNumber2 = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
				CdOperationTableXColSpec::EColumnType::ColumnType_OriginSideEkijikoku));
		}
		else
		{
			iXColumnNumber1 = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
				CdOperationTableXColSpec::EColumnType::ColumnType_TerminalSideEkimei));
			iXColumnNumber2 = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
				CdOperationTableXColSpec::EColumnType::ColumnType_TerminalSideEkijikoku));
		}
		Ou<CDcdTextbox> pCDcdTextbox1 =
			getCXDcdGrid()->getCell(iXColumnNumber1, iYColumnNumber)->getIfDcDraw();
		Ou<CDcdTextbox> pCDcdTextbox2 =
			getCXDcdGrid()->getCell(iXColumnNumber2, iYColumnNumber)->getIfDcDraw();

		tstring strEkimei;
		CdDedJikoku aCdDedJikoku;
		//if (bIsHatsuJikoku)
		//{
			if (aSihatsuOperationTableContent.iOuterShihatsuekiIndex != INT_MIN)
			{
				int iOuterTerminalIndex = aSihatsuOperationTableContent.iOuterShihatsuekiIndex;
				strEkimei = pCentDedEkiCont->get(iSihatsuEkiIndex).getOuterTerminalEkimei(iOuterTerminalIndex);
				aCdDedJikoku = aSihatsuOperationTableContent.OuterShihatsuJikoku;
			}
			else
			{
				int iValidSihatsuEkiOrder = iSihatsuEkiOrder;
				if (!aShihatsuRessya.isRunBetweenNextEki(iSihatsuEkiOrder))
				{
					iValidSihatsuEkiOrder = aShihatsuRessya.getRunBetweenEkiForward(iSihatsuEkiOrder);
				}

				strEkimei = pCentDedEkiCont->get(iSihatsuEkiIndex).getEkimei();
				aCdDedJikoku = aShihatsuRessya.getCentDedEkiJikoku(iValidSihatsuEkiOrder).getHatsujikoku();
			}
		//}
		//else
		//{
		//	if (aShuchakuOperationTableContent.iOuterShuchakuekiIndex != INT_MIN)
		//	{
		//		int iOuterTerminalIndex = aSihatsuOperationTableContent.iOuterShuchakuekiIndex;
		//		strEkimei = pCentDedEkiCont->get(iSyuuchakuEkiIndex).getOuterTerminalEkimei(iOuterTerminalIndex);
		//		aCdDedJikoku = aShuchakuOperationTableContent.OuterShuchakuJikoku;
		//	}
		//	else
		//	{
		//		int iValidSyuuchakuEkiOrder = aShuchakuOperationTableContent.iSyuuchakuEkiOrder;
		//		if (!aShuchakuRessya.isRunBetweenNextEki(iSyuuchakuEkiOrder - 1))
		//		{
		//			iValidSyuuchakuEkiOrder = aShuchakuRessya.getRunBetweenEkiBackward(iSyuuchakuEkiOrder);
		//		}

		//		strEkimei = pCentDedEkiCont->get(iSyuuchakuEkiIndex).getEkimei();
		//		aCdDedJikoku = aShuchakuRessya.getCentDedEkiJikoku(iValidSyuuchakuEkiOrder).getChakujikoku();
		//	}
		//}
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

		getCXDcdGrid()->getCell(iXColumnNumber1, iYColumnNumber)->setAttachCellCount(1, 1);
		getCXDcdGrid()->getCell(iXColumnNumber2, iYColumnNumber)->setAttachCellCount(1, 1);
		//	セルを無効化
		InvalidateCell(iXColumnNumber1, iYColumnNumber);
		InvalidateCell(iXColumnNumber2, iYColumnNumber);

		if (getDisplayTrackName())
		{
			int iXColumnNumber3;

			if (eRessyahoukou == Ressyahoukou_Kudari ||
				getDisplayNoboriLeftToRight())
			{
				iXColumnNumber3 = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
					CdOperationTableXColSpec::EColumnType::ColumnType_OriginSideEkiTrack));
			}
			else
			{
				iXColumnNumber3 = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
					CdOperationTableXColSpec::EColumnType::ColumnType_TerminalSideEkiTrack));
			}
			Ou<CDcdTextbox> pCDcdTextbox3 =
				getCXDcdGrid()->getCell(iXColumnNumber3, iYColumnNumber)->getIfDcDraw();

			tstring strEkiTrackName;

			//路線外始発の場合は、空白のままにする
			if (aSihatsuOperationTableContent.iOuterShihatsuekiIndex == INT_MIN)
			{
				int iValidSihatsuEkiOrder = iSihatsuEkiOrder;
				if (!aShihatsuRessya.isRunBetweenNextEki(iSihatsuEkiOrder))
				{
					iValidSihatsuEkiOrder = aShihatsuRessya.getRunBetweenEkiForward(iSihatsuEkiOrder);
				}

				strEkiTrackName = pCentDedEkiCont->get(iSihatsuEkiIndex).getEkiTrack2Cont()->get(
					aShihatsuRessya.getCentDedEkiJikoku(iValidSihatsuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(aShihatsuRessya.getRessyahoukou());
				//strEkiTrackName = pCentDedEkiCont->get(iSihatsuEkiIndex).getEkiTrack2Cont()->get(
				//	aShihatsuRessya.getCentDedEkiJikoku(iValidSihatsuEkiOrder).getRessyaTrackIndex()).getTrackName();
			}

			pCDcdTextbox3->setText(strEkiTrackName);
			//	フォント属性
			CdDrawTextProp	aCdDrawTextProp3 =
				pCDcdTextbox3->getCdDrawTextProp();
			aCdDrawTextProp3.setCdFontProp(fontpropDefault);
			aCdDrawTextProp3.setTextColor(colorpropDefault);
			aCdDrawTextProp3.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
			pCDcdTextbox3->setCdDrawTextProp(aCdDrawTextProp3);

			getCXDcdGrid()->getCell(iXColumnNumber3, iYColumnNumber)->setAttachCellCount(1, 1);
			//	セルを無効化
			InvalidateCell(iXColumnNumber3, iYColumnNumber);
		}
	}
	{
		//	終着駅名&終着駅時刻
		int iXColumnNumber1;
		int iXColumnNumber2;
		if (eRessyahoukou == Ressyahoukou_Kudari ||
			getDisplayNoboriLeftToRight())
		{
			iXColumnNumber1 = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
				CdOperationTableXColSpec::EColumnType::ColumnType_TerminalSideEkimei));
			iXColumnNumber2 = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
				CdOperationTableXColSpec::EColumnType::ColumnType_TerminalSideEkijikoku));
		}
		else
		{
			iXColumnNumber1 = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
				CdOperationTableXColSpec::EColumnType::ColumnType_OriginSideEkimei));
			iXColumnNumber2 = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
				CdOperationTableXColSpec::EColumnType::ColumnType_OriginSideEkijikoku));
		}
		Ou<CDcdTextbox> pCDcdTextbox1 =
			getCXDcdGrid()->getCell(iXColumnNumber1, iYColumnNumber)->getIfDcDraw();
		Ou<CDcdTextbox> pCDcdTextbox2 =
			getCXDcdGrid()->getCell(iXColumnNumber2, iYColumnNumber)->getIfDcDraw();

		tstring strEkimei;
		CdDedJikoku aCdDedJikoku;
		//bool bIsChakuJikoku = aCentDedRessya.getRessyahoukou() == Ressyahoukou_Kudari ||
		//	getDisplayNoboriLeftToRight();
		//if (bIsChakuJikoku)
		//{
			if (aShuchakuOperationTableContent.iOuterShuchakuekiIndex != INT_MIN)
			{
				int iOuterTerminalIndex = aShuchakuOperationTableContent.iOuterShuchakuekiIndex;
				strEkimei = pCentDedEkiCont->get(iSyuuchakuEkiIndex).getOuterTerminalEkimei(iOuterTerminalIndex);
				aCdDedJikoku = aShuchakuOperationTableContent.OuterShuchakuJikoku;
			}
			else
			{
				int iValidSyuuchakuEkiOrder = iSyuuchakuEkiOrder;
				if (!aShuchakuRessya.isRunBetweenNextEki(iSyuuchakuEkiOrder - 1))
				{
					iValidSyuuchakuEkiOrder = aShuchakuRessya.getRunBetweenEkiBackward(iSyuuchakuEkiOrder);
				}

				strEkimei = pCentDedEkiCont->get(iSyuuchakuEkiIndex).getEkimei();
				aCdDedJikoku = aShuchakuRessya.getCentDedEkiJikoku(iValidSyuuchakuEkiOrder).getChakujikoku();
			}
		//}
		//else
		//{
		//	if (aOperationTableContent.iOuterShihatsuekiIndex != INT_MIN)
		//	{
		//		int iOuterTerminalIndex = aOperationTableContent.iOuterShihatsuekiIndex;
		//		strEkimei = pCdDedEkiCont->get(aOperationTableContent.iSihatsuEkiOrder).getOuterTerminalEkimei(iOuterTerminalIndex);
		//		aCdDedJikoku = aOperationTableContent.OuterShihatsuJikoku;
		//	}
		//	//if (aOperationTableContent.BeforeOperation->getBOperation()
		//	//	== CentDedBeforeOperation::BOperation_Outer)
		//	//{
		//	//	int iOuterTerminalIndex = aOperationTableContent.BeforeOperation->getOuterShihatsuekiIndex();
		//	//	strEkimei = pCdDedEkiCont->get(aOperationTableContent.iSihatsuEkiOrder).getOuterTerminalEkimei(iOuterTerminalIndex);
		//	//	aCdDedJikoku = aOperationTableContent.BeforeOperation->getOuterShihatsuJikoku();
		//	//}
		//	else
		//	{
		//		int iSihatsuEkiOrder = aOperationTableContent.iSihatsuEkiOrder;
		//		if (!aCentDedRessya.isRunBetweenNextEki(iSihatsuEkiOrder))
		//		{
		//			iSihatsuEkiOrder = aCentDedRessya.getRunBetweenEkiForward(iSihatsuEkiOrder);
		//		}

		//		strEkimei = pCdDedEkiCont->get(iSihatsuEkiOrder).getEkimei();
		//		aCdDedJikoku = aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getHatsujikoku();
		//	}
		//}
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
		aCdDrawTextProp2.setTextColor(colorpropDefault);
		aCdDrawTextProp2.setCdFontProp(fontpropDefault);
		aCdDrawTextProp2.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
		pCDcdTextbox2->setCdDrawTextProp(aCdDrawTextProp2);

		getCXDcdGrid()->getCell(iXColumnNumber1, iYColumnNumber)->setAttachCellCount(1, 1);
		getCXDcdGrid()->getCell(iXColumnNumber2, iYColumnNumber)->setAttachCellCount(1, 1);
		//	セルを無効化
		InvalidateCell(iXColumnNumber1, iYColumnNumber);
		InvalidateCell(iXColumnNumber2, iYColumnNumber);

		if (getDisplayTrackName())
		{
			int iXColumnNumber3;

			if (eRessyahoukou == Ressyahoukou_Kudari ||
				getDisplayNoboriLeftToRight())
			{
				iXColumnNumber3 = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
					CdOperationTableXColSpec::EColumnType::ColumnType_TerminalSideEkiTrack));
			}
			else
			{
				iXColumnNumber3 = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
					CdOperationTableXColSpec::EColumnType::ColumnType_OriginSideEkiTrack));
			}
			Ou<CDcdTextbox> pCDcdTextbox3 =
				getCXDcdGrid()->getCell(iXColumnNumber3, iYColumnNumber)->getIfDcDraw();

			tstring strEkiTrackName;

			//路線外終着の場合は、空白のままにする
			if (aShuchakuOperationTableContent.iOuterShuchakuekiIndex == INT_MIN)
			{
				int iValidSyuuchakuEkiOrder = iSyuuchakuEkiOrder;
				if (!aShuchakuRessya.isRunBetweenNextEki(iSyuuchakuEkiOrder - 1))
				{
					iValidSyuuchakuEkiOrder = aShuchakuRessya.getRunBetweenEkiBackward(iSyuuchakuEkiOrder);
				}

				strEkiTrackName = pCentDedEkiCont->get(iSyuuchakuEkiIndex).getEkiTrack2Cont()->get(
					aShuchakuRessya.getCentDedEkiJikoku(iValidSyuuchakuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(aShuchakuRessya.getRessyahoukou());

				//strEkiTrackName = pCentDedEkiCont->get(iSyuuchakuEkiIndex).getEkiTrack2Cont()->get(
				//	aShuchakuRessya.getCentDedEkiJikoku(iValidSyuuchakuEkiOrder).getRessyaTrackIndex()).getTrackName();
			}

			pCDcdTextbox3->setText(strEkiTrackName);
			//	フォント属性
			CdDrawTextProp	aCdDrawTextProp3 =
				pCDcdTextbox3->getCdDrawTextProp();
			aCdDrawTextProp3.setCdFontProp(fontpropDefault);
			aCdDrawTextProp3.setTextColor(colorpropDefault);
			aCdDrawTextProp3.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
			pCDcdTextbox3->setCdDrawTextProp(aCdDrawTextProp3);

			getCXDcdGrid()->getCell(iXColumnNumber3, iYColumnNumber)->setAttachCellCount(1, 1);
			//	セルを無効化
			InvalidateCell(iXColumnNumber3, iYColumnNumber);
		}
	}
	{
		//	列車方向(矢印)
		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
			CdOperationTableXColSpec::EColumnType::ColumnType_Ressyahoukou));
		Ou<CDcdTextbox> pCDcdTextbox =
			getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();

		tstring strArrow = _T("→");
		if (eRessyahoukou == Ressyahoukou_Nobori &&
			!getDisplayNoboriLeftToRight())
		{
			strArrow = _T("←");
		}
		pCDcdTextbox->setText(strArrow);

		//	フォント属性
		CdDrawTextProp	aCdDrawTextProp =
			pCDcdTextbox->getCdDrawTextProp();
		aCdDrawTextProp.setCdFontProp(fontpropDefault);
		aCdDrawTextProp.setTextColor(colorpropDefault);
		aCdDrawTextProp.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
		pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);

		getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->setAttachCellCount(1, 1);
		//	セルを無効化
		InvalidateCell(iXColumnNumber, iYColumnNumber);
	}
}

void CWndDcdGridOperationTable::OnUpdate_setCentDedRessya_To_Column_Extension(
	int iYColumnNumber,
	const CentDedRessya& aCentDedRessya,
	const OperationTableContent& aOperationTableContent,
	const int iPrevShuchakuEkiIndex,
	const int iNextShihatsuEkiIndex,
	const int iPrevContinueEkiIndex,
	const int iNextContinueEkiIndex,
	const bool bIsContinue)
{
	int iYColumnNumberLine = iYColumnNumber + 1;
	int iYColumnNumberHatsu = iYColumnNumber + 2;
	int iRessyaYColumnCount = 3;
	CdFontProp fontpropDefault = createFontProp();
	CdFontProp fontpropBig = createFontProp();
	//fontpropBig.setPointTextHeight(fontpropBig.getPointTextHeight() * 2);
	CdColorProp colorpropDefault = createStringColorProp();
	CdOperationTableXColSpecCont aXColSpecCont = createXColSpecCont();

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
		if (getDisplayExtensionOperationTable())
		{
			getCXDcdGrid()->getYColumn(iYColumnNumberLine)->setColumnSize(3);
			getCXDcdGrid()->getYColumn(iYColumnNumberHatsu)->setColumnSize(sizeRessyamei.getY());
		}
	}


	// --------------------------------
	//	属性を設定
	// --------------------------------
	const Mu<CentDedEkiCont::CdDedEki>* pCdDedEkiCont =
		getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(aCentDedRessya.getRessyahoukou());
	const CentDedEkiCont* pCentDedEkiCont =
		getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont();

	const CentDedRessyasyubetsuCont* pCentDedRessyasyubetsuCont =
		getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedRessyasyubetsuCont();
	const CentDedRessyasyubetsu* pCentDedRessyasyubetsu = pCentDedRessyasyubetsuCont
		->getMuPtr()->get(aCentDedRessya.getRessyasyubetsuIndex());
	//if (iContinueSyubetsuIndex != -1)
	//{
	//	pCentDedRessyasyubetsu = pCentDedRessyasyubetsuCont
	//		->getMuPtr()->get(iContinueSyubetsuIndex);
	//}
	if (m_bDisplayParentSyubetsu && pCentDedRessyasyubetsu->getParentSyubetsuIndex() >= 0)
	{
		pCentDedRessyasyubetsu = pCentDedRessyasyubetsuCont
			->getMuPtr()->get(pCentDedRessyasyubetsu->getParentSyubetsuIndex());
	}

	int iSihatsuEkiOrder = aOperationTableContent.iSihatsuEkiOrder;
	if (!aCentDedRessya.isRunBetweenNextEki(iSihatsuEkiOrder))
	{
		iSihatsuEkiOrder = aCentDedRessya.getRunBetweenEkiForward(iSihatsuEkiOrder);
	}
	int iSihatsuCoreEkiIndex =
		pCentDedEkiCont->get(pCentDedEkiCont->EkiIndexOfEkiOrder(aOperationTableContent.aRessyaProperty.getRessyahoukou(), iSihatsuEkiOrder)).getBrunchCoreEkiIndex();
	int iSihatsuEkiIndex = aCentDedRessya.EkiIndexOfEkiOrder(iSihatsuEkiOrder);
	int iSihatsuCoreEkiOrder = -1;
	if (iSihatsuCoreEkiIndex != -1)
	{
		iSihatsuCoreEkiOrder = aCentDedRessya.EkiOrderOfEkiIndex(iSihatsuCoreEkiIndex);
	}

	int iSyuuchakuEkiOrder = aOperationTableContent.iSyuuchakuEkiOrder;
	if (!aCentDedRessya.isRunBetweenNextEki(iSyuuchakuEkiOrder - 1))
	{
		iSyuuchakuEkiOrder = aCentDedRessya.getRunBetweenEkiBackward(iSyuuchakuEkiOrder);
	}
	int iSyuuchakuCoreEkiIndex =
		pCentDedEkiCont->get(pCentDedEkiCont->EkiIndexOfEkiOrder(aOperationTableContent.aRessyaProperty.getRessyahoukou(), iSyuuchakuEkiOrder)).getBrunchCoreEkiIndex();
	int iSyuuchakuEkiIndex = aCentDedRessya.EkiIndexOfEkiOrder(iSyuuchakuEkiOrder);
	int iSyuuchakuCoreEkiOrder = -1;
	if (iSyuuchakuCoreEkiIndex != -1)
	{
		iSyuuchakuCoreEkiOrder = aCentDedRessya.EkiOrderOfEkiIndex(iSyuuchakuCoreEkiIndex);
	}


	int iPrevContinueCoreEkiIndex = -1;
	if (iPrevContinueEkiIndex != -1)
	{
		iPrevContinueCoreEkiIndex = pCentDedEkiCont->get(iPrevContinueEkiIndex).getBrunchCoreEkiIndex();
	}

	int iNextContinueCoreEkiIndex = -1;
	if (iNextContinueEkiIndex != -1)
	{
		iNextContinueCoreEkiIndex = pCentDedEkiCont->get(iNextContinueEkiIndex).getBrunchCoreEkiIndex();
	}

	//列車番号等の表示処理は、iContinueEkiIndex == -1(他列車からの継続ではない場合)のみ実行します。
	if (iPrevContinueEkiIndex == -1)
	{
		{
			//	列車番号
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
				CdOperationTableXColSpec::EColumnType::ColumnType_Ressyabangou));
			Ou<CDcdTextbox> pCDcdTextbox =
				getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
			if (bIsContinue)
			{
				pCDcdTextbox->setText(_T("↓"));
			}
			else
			{
				pCDcdTextbox->
					setText(aCentDedRessya.getRessyabangou());
			}

			//	フォント属性
			CdDrawTextProp	aCdDrawTextProp =
				pCDcdTextbox->getCdDrawTextProp();
			aCdDrawTextProp.setCdFontProp(fontpropDefault);
			aCdDrawTextProp.setTextColor(colorpropDefault);
			aCdDrawTextProp.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
			pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);

			getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->setAttachCellCount(1, iRessyaYColumnCount);
			//	セルを無効化
			InvalidateCell(iXColumnNumber, iYColumnNumber);
		}
		{
			//	種別
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
				CdOperationTableXColSpec::EColumnType::ColumnType_Ressyasyubetsu));
			Ou<CDcdTextbox> pCDcdTextbox =
				getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();

			//種別のテキスト
			//pCDcdTextbox->setText(
			//	pCentDedRessyasyubetsuCont->get(aCentDedRessya.getRessyasyubetsuIndex()).getRyakusyou());
			if (bIsContinue)
			{
				pCDcdTextbox->setText(_T("↓"));
			}
			else
			{
				pCDcdTextbox->setText(pCentDedRessyasyubetsu->getSyubetsumei());
			}

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

			getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->setAttachCellCount(1, iRessyaYColumnCount);
			//	セルを無効化
			InvalidateCell(iXColumnNumber, iYColumnNumber);
		}
		if (getCDiagramEditDoc()->getCDedRosenFileData()
			->getCdDedDispProp().getDisplayRessyamei())
		{
			//	列車名
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
				CdOperationTableXColSpec::EColumnType::ColumnType_Ressyamei));
			Ou<CDcdTextbox> pCDcdTextbox =
				getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();

			//列車名のテキスト
			if (bIsContinue)
			{
				pCDcdTextbox->setText(_T("↓"));
			}
			else
			{
				tstring strRessyamei = aCentDedRessya.getRessyamei();
				if (!aCentDedRessya.getGousuu().empty())
				{
					strRessyamei += _T(" ");
					strRessyamei += aCentDedRessya.getGousuu();
					strRessyamei += _T("号");
				}
				pCDcdTextbox->setText(strRessyamei);
			}

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

			getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->setAttachCellCount(1, iRessyaYColumnCount);
			//	セルを無効化
			InvalidateCell(iXColumnNumber, iYColumnNumber);
		}
		{
			CdPenProp aCdPenProp =
				Ou<CDcdLine>(getCXDcdGrid()->getYBorder(iYColumnNumber)->getIfDcDraw())->getCdPenProp();
			aCdPenProp.setStyle(CdPenProp::EStyle::NULLPEN);
			Ou<CDcdLine>
				(getCXDcdGrid()->getYBorder(iYColumnNumber)->getIfDcDraw())
				->setCdPenProp(aCdPenProp);

			CDcdGridYBorder* pCDcdGridYBorder = getCXDcdGrid()->getYBorder(iYColumnNumber);
			pCDcdGridYBorder->setColumnBorderSize(0);
		}
		{
			CdPenProp aCdPenProp =
				Ou<CDcdLine>(getCXDcdGrid()->getYBorder(iYColumnNumberLine)->getIfDcDraw())->getCdPenProp();
			aCdPenProp.setStyle(CdPenProp::EStyle::NULLPEN);
			Ou<CDcdLine>
				(getCXDcdGrid()->getYBorder(iYColumnNumberLine)->getIfDcDraw())
				->setCdPenProp(aCdPenProp);

			CDcdGridYBorder* pCDcdGridYBorder = getCXDcdGrid()->getYBorder(iYColumnNumberLine);
			pCDcdGridYBorder->setColumnBorderSize(0);
		}
		{
			CdPenProp aCdPenProp =
				Ou<CDcdLine>(getCXDcdGrid()->getYBorder(iYColumnNumberHatsu)->getIfDcDraw())->getCdPenProp();
			aCdPenProp.setColor(createGridColorProp());
			aCdPenProp.setStyle(CdPenProp::EStyle::SOLID);
			Ou<CDcdLine>
				(getCXDcdGrid()->getYBorder(iYColumnNumberHatsu)->getIfDcDraw())
				->setCdPenProp(aCdPenProp);

			if (iYColumnNumberHatsu != createYColSpecCont().size() - 1)
			{
				CDcdGridYBorder* pCDcdGridYBorder = getCXDcdGrid()->getYBorder(iYColumnNumberHatsu);
				pCDcdGridYBorder->setColumnBorderSize(0);
			}
		}
	}


	for (int idx = 0; idx < (int)m_iDisplayJikokuEkiIndex.size(); idx++)
	{
		/**
			以下の条件を満たすときは、この列への描写処理をスキップします
			・iContinueEkiIndexが-1以外
			・下り列車の場合、m_iDisplayJikokuEkiIndex[idx]がiContinueEkiIndexよりも小さい場合
			・上り列車の場合、m_iDisplayJikokuEkiIndex[idx]がiContinueEkiIndexよりも大きい場合

			・iPrevContinueEkiIndexが-1以外かつiPrevContinueCoreEkiIndexが-1かつm_iDisplayJikokuEkiIndex[idx]がiPrevContinueEkiIndexよりも小さい
			・iPrevContinueEkiIndexが-1以外かつiPrevContinueCoreEkiIndexが-1以外かつm_iDisplayJikokuEkiIndex[idx]がiPrevContinueCoreEkiIndexよりも小さい
			・iNextContinueEkiIndexが-1以外かつiNextContinueCoreEkiIndexが-1かつm_iDisplayJikokuEkiIndex[idx]がiNextContinueEkiIndexよりも大きい
			・iNextContinueEkiIndexが-1以外かつiNextContinueCoreEkiIndexが-1以外かつm_iDisplayJikokuEkiIndex[idx]がiNextContinueCoreEkiIndexよりも大きい
		*/
		if (aOperationTableContent.aRessyaProperty.getRessyahoukou() == ERessyahoukou::Ressyahoukou_Kudari)
		{
			if (iPrevContinueEkiIndex != -1)
			{
				if (iPrevContinueCoreEkiIndex == -1 &&
					m_iDisplayJikokuEkiIndex[idx] < iPrevContinueEkiIndex)
				{
					continue;
				}
				else if (iPrevContinueCoreEkiIndex != -1 &&
					m_iDisplayJikokuEkiIndex[idx] < iPrevContinueCoreEkiIndex)
				{
					continue;
				}
			}

			if (iNextContinueEkiIndex != -1)
			{
				if (iNextContinueCoreEkiIndex == -1 &&
					m_iDisplayJikokuEkiIndex[idx] > iNextContinueEkiIndex)
				{
					continue;
				}
				else if (iNextContinueCoreEkiIndex != -1 &&
					m_iDisplayJikokuEkiIndex[idx] > iNextContinueCoreEkiIndex)
				{
					continue;
				}
			}
		}
		else if (aOperationTableContent.aRessyaProperty.getRessyahoukou() == ERessyahoukou::Ressyahoukou_Nobori)
		{
			if (iPrevContinueEkiIndex != -1)
			{
				if (iPrevContinueCoreEkiIndex == -1 &&
					m_iDisplayJikokuEkiIndex[idx] > iPrevContinueEkiIndex)
				{
					continue;
				}
				else if (iPrevContinueCoreEkiIndex != -1 &&
					m_iDisplayJikokuEkiIndex[idx] > iPrevContinueCoreEkiIndex)
				{
					continue;
				}
			}

			if (iNextContinueEkiIndex != -1)
			{
				if (iNextContinueCoreEkiIndex == -1 &&
					m_iDisplayJikokuEkiIndex[idx] < iNextContinueEkiIndex)
				{
					continue;
				}
				else if (iNextContinueCoreEkiIndex != -1 &&
					m_iDisplayJikokuEkiIndex[idx] < iNextContinueCoreEkiIndex)
				{
					continue;
				}
			}
		}
		/**
			ColumnType_JikokuDisplayEkiに表示するもの
			・運行範囲内の時刻表示駅→着発時刻
			・運行範囲内の非時刻表示駅(路線外発着以外の始発・終着駅を除く)→空白
			
		*/
		{
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
				CdOperationTableXColSpec::EColumnType::ColumnType_JikokuDisplayEki, m_iDisplayJikokuEkiIndex[idx]));

			Ou<CDcdTextbox> pCDcdTextboxChaku =
				getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
			Ou<CDcdTextbox> pCDcdTextboxLine =
				getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumberLine)->getIfDcDraw();
			Ou<CDcdTextbox> pCDcdTextboxHatsu =
				getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumberHatsu)->getIfDcDraw();

			//	フォント属性
			CdDrawTextProp	aCdDrawTextPropChaku =
				pCDcdTextboxChaku->getCdDrawTextProp();
			aCdDrawTextPropChaku.setCdFontProp(fontpropDefault);
			aCdDrawTextPropChaku.setTextColor(colorpropDefault);
			aCdDrawTextPropChaku.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));

			CdDrawTextProp	aCdDrawTextPropHatsu =
				pCDcdTextboxHatsu->getCdDrawTextProp();
			aCdDrawTextPropHatsu.setCdFontProp(fontpropDefault);
			aCdDrawTextPropHatsu.setTextColor(colorpropDefault);
			aCdDrawTextPropHatsu.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));

			getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->setAttachCellCount(1, 1);
			getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumberHatsu)->setAttachCellCount(1, 1);

			tstring strChaku;
			tstring strHatsu;
			/**
				当該セルにおける横線の形式
				-1:線無し
				0:横線全域
				1:右半分
				2:左半分
				3:全域(破線)(経由なし)
			*/
			int iHorizontalLineType = -1;
			/**
				当該セルにおける縦線の形式
				-1:上方向
				0:無し
				1:下方向
			*/
			int iVerticalLineType = 0;

			bool bSkipChaku = false;
			bool bSkipLine = false;
			bool bSkipHatsu = false;

			if (m_iDisplayJikokuEkiIndex[idx] == INT_MIN)
			{
				if (aOperationTableContent.aRessyaProperty.getRessyahoukou() == ERessyahoukou::Ressyahoukou_Kudari)
				{
					//路線外始発
					if (aOperationTableContent.iOuterShihatsuekiIndex != INT_MIN &&
						(iSihatsuEkiIndex <= m_iDisplayJikokuEkiIndex[idx + 1] ||
							(iSihatsuCoreEkiIndex != -1 &&
								iSihatsuCoreEkiIndex <= m_iDisplayJikokuEkiIndex[idx + 1])))
					{
						strChaku = pCdDedEkiCont->get(iSihatsuEkiOrder).getOuterTerminalEkimei(aOperationTableContent.iOuterShihatsuekiIndex);

						strHatsu = getCdDedJikokuConv().encode(aOperationTableContent.OuterShihatsuJikoku, false);
						iHorizontalLineType = 1;
					}
				}
				else
				{
					//路線外終着
					if (aOperationTableContent.iOuterShuchakuekiIndex != INT_MIN &&
						(iSyuuchakuEkiIndex <= m_iDisplayJikokuEkiIndex[idx + 1] ||
							(iSyuuchakuCoreEkiIndex != -1 &&
								iSyuuchakuCoreEkiIndex <= m_iDisplayJikokuEkiIndex[idx + 1])))
					{
						strHatsu = pCdDedEkiCont->get(iSyuuchakuEkiOrder).getOuterTerminalEkimei(aOperationTableContent.iOuterShuchakuekiIndex);

						strChaku = getCdDedJikokuConv().encode(aOperationTableContent.OuterShuchakuJikoku, true);
						iHorizontalLineType = 1;
					}

				}
			}
			else if (m_iDisplayJikokuEkiIndex[idx] == INT_MAX)
			{
				if (aOperationTableContent.aRessyaProperty.getRessyahoukou() == ERessyahoukou::Ressyahoukou_Kudari)
				{
					//路線外終着
					if (aOperationTableContent.iOuterShuchakuekiIndex != INT_MIN &&
						(iSyuuchakuEkiIndex >= m_iDisplayJikokuEkiIndex[idx - 1] ||
							(iSyuuchakuCoreEkiIndex != -1 &&
								iSyuuchakuCoreEkiIndex >= m_iDisplayJikokuEkiIndex[idx - 1])))
					{
						strHatsu = pCdDedEkiCont->get(iSyuuchakuEkiOrder).getOuterTerminalEkimei(aOperationTableContent.iOuterShuchakuekiIndex);

						strChaku = getCdDedJikokuConv().encode(aOperationTableContent.OuterShuchakuJikoku, true);
						iHorizontalLineType = 2;
					}
				}
				else
				{
					//路線外始発
					//int iSihatsuEkiIndex = aCentDedRessya.EkiIndexOfEkiOrder(iSihatsuEkiOrder);
					if (aOperationTableContent.iOuterShihatsuekiIndex != INT_MIN &&
						(iSihatsuEkiIndex >= m_iDisplayJikokuEkiIndex[idx - 1] ||
							(iSihatsuCoreEkiIndex != -1 &&
								iSihatsuCoreEkiIndex >= m_iDisplayJikokuEkiIndex[idx - 1])))
					{
						strChaku = pCdDedEkiCont->get(iSihatsuEkiOrder).getOuterTerminalEkimei(aOperationTableContent.iOuterShihatsuekiIndex);

						strHatsu = getCdDedJikokuConv().encode(aOperationTableContent.OuterShihatsuJikoku, false);
						iHorizontalLineType = 2;
					}

				}
			}
			else
			{
				if (aOperationTableContent.aRessyaProperty.getRessyahoukou() == ERessyahoukou::Ressyahoukou_Kudari)
				{
					/**
						表示駅が始発駅よりも前の場合、路線外始発かつ一つ右側の表示駅の駅Indexが始発駅の駅Indexと同じか大きい場合は、
						この項に路線外始発を表示します。
					*/
					if (iSihatsuEkiIndex > m_iDisplayJikokuEkiIndex[idx])
					{
						if (iSihatsuCoreEkiIndex != -1)
						{
							if (iSihatsuCoreEkiIndex > m_iDisplayJikokuEkiIndex[idx])
							{
								if (aOperationTableContent.iOuterShihatsuekiIndex != INT_MIN &&
									iSihatsuCoreEkiIndex <= m_iDisplayJikokuEkiIndex[idx + 1])
								{
									//路線外始発
									strChaku = pCdDedEkiCont->get(iSihatsuCoreEkiOrder).getOuterTerminalEkimei(aOperationTableContent.iOuterShihatsuekiIndex);

									strHatsu = getCdDedJikokuConv().encode(aOperationTableContent.OuterShihatsuJikoku, false);
									iHorizontalLineType = 1;
								}
								else if (iPrevContinueEkiIndex != -1)
								{
									/**
										同一行表示の前列車がある場合、
										表示駅が前列車終着駅の場合は、始発駅発時刻を表示する(着時刻およびラインは前列車の管轄)
										前列車終着駅とこの列車の始発駅の間の場合は破線だが、ここでは前列車の管轄となる。
										ただし、この駅が時刻非表示駅なら、時刻・番線は非表示にする
									*/
									if ((iPrevContinueCoreEkiIndex == -1 &&
										iPrevContinueEkiIndex == m_iDisplayJikokuEkiIndex[idx])|| 
										(iPrevContinueCoreEkiIndex != -1 &&
											iPrevContinueCoreEkiIndex == m_iDisplayJikokuEkiIndex[idx]))
									{
										if (pCentDedEkiCont->getMuPtr()->get(m_iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
											(getDisplayTsuukaEkiJikoku() ||
												aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya))
										{
											strHatsu = getCdDedJikokuConv().encode(
												aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getVirtualHatsujikoku(), false);
										}
										bSkipLine = true;
										bSkipChaku = true;
										if (aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
										{
											aCdDrawTextPropHatsu.setTextColor(CdColorProp(128, 128, 128));
										}
									}
									else if ((iPrevContinueCoreEkiIndex == -1 &&
										iPrevContinueEkiIndex < m_iDisplayJikokuEkiIndex[idx]) ||
										(iPrevContinueCoreEkiIndex != -1 &&
											iPrevContinueCoreEkiIndex < m_iDisplayJikokuEkiIndex[idx]))
									{
										//ここでは本来不要だが、CSV出力時はセル数合わせのため、スキップが必須となるので加えておく
										bSkipLine = true;
										bSkipChaku = true;
									}
								}
							}
							else if (iSihatsuCoreEkiIndex == m_iDisplayJikokuEkiIndex[idx])
							{
								if (aOperationTableContent.iOuterShihatsuekiIndex != INT_MIN)
								{
									if (pCentDedEkiCont->getMuPtr()->get(iSihatsuCoreEkiIndex)->getOperationTableDisplayJikoku())
									{
										//路線外始発のデータ上始発駅
										CdDedJikoku ChakuJikoku = aOperationTableContent.ChakuJikoku;
										CdDedJikoku HatsuJikoku = aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getHatsujikoku();
										if (!ChakuJikoku.isNull())
										{
											HatsuJikoku = aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getVirtualHatsujikoku();
										}

										strChaku = getCdDedJikokuConv().encode(ChakuJikoku, true, HatsuJikoku);
										strHatsu = getCdDedJikokuConv().encode(HatsuJikoku, false, ChakuJikoku);

										if (getDisplayTrackName())
										{
											//if (!strChaku.empty())
											//{
											//	strChaku += _T(" ");
											//}
											strChaku += _T("(");
											strChaku += pCdDedEkiCont->get(iSihatsuEkiOrder).getCentDedEkiTrack2Cont().get(
												aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(aCentDedRessya.getRessyahoukou());
											strChaku += _T(")");
										}
									}
									iHorizontalLineType = 0;
								}
								else
								{
									//始発駅
									//前列車と同一行に表示する場合、この駅が時刻非表示駅または駅扱い通過かつ通過駅時刻非表示の場合は、時刻を表示しません
									if (iPrevContinueEkiIndex == -1 ||
										(pCentDedEkiCont->getMuPtr()->get(m_iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
											(getDisplayTsuukaEkiJikoku() ||
												aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya)))
									{
										strHatsu = getCdDedJikokuConv().encode(
											aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getVirtualHatsujikoku(), false);
									}
									iHorizontalLineType = 1;
									//前列車と同一行に表示する場合、この駅の着時刻および横線は、前列車の管轄で描写します
									if (iPrevContinueEkiIndex != -1)
									{
										bSkipChaku = true;
										bSkipLine = true;
										if (aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
										{
											aCdDrawTextPropHatsu.setTextColor(CdColorProp(128, 128, 128));
										}
									}

									if (aOperationTableContent.eBeforeType == EBeforeAfterType::BeforeAfterType_OutIn)
									{
										iVerticalLineType = -2;
									}
									else if (iPrevShuchakuEkiIndex != -1 &&
										iPrevShuchakuEkiIndex == iSihatsuCoreEkiIndex)
									{
										iVerticalLineType = -1;
									}

									/**
										前列車と同一行に表示する場合、番線名表示は着時刻欄で行うので、ここでは不要です。
									*/
									if (getDisplayTrackName() &&
										iPrevContinueEkiIndex == -1)
									{
										if (iVerticalLineType == 0)
										{
											strChaku += _T("(");
											strChaku += pCdDedEkiCont->get(iSihatsuEkiOrder).getCentDedEkiTrack2Cont().get(
												aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(aCentDedRessya.getRessyahoukou());
											strChaku += _T(")");
										}
										else
										{
											//strHatsu += _T(" ");

											strHatsu += _T("(");
											strHatsu += pCdDedEkiCont->get(iSihatsuEkiOrder).getCentDedEkiTrack2Cont().get(
												aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(aCentDedRessya.getRessyahoukou());
											strHatsu += _T(")");
										}
									}
								}
							}
							else//sihatsuCore<m_iDisplayJikokuEkiIndex[idx]<Sihatsu
							{
								//経由無し
								iHorizontalLineType = 3;
							}

						}
						else if (aOperationTableContent.iOuterShihatsuekiIndex != INT_MIN &&
							iSihatsuEkiIndex <= m_iDisplayJikokuEkiIndex[idx + 1])
						{
							//路線外始発
							strChaku = pCdDedEkiCont->get(iSihatsuEkiOrder).getOuterTerminalEkimei(aOperationTableContent.iOuterShihatsuekiIndex);

							strHatsu = getCdDedJikokuConv().encode(aOperationTableContent.OuterShihatsuJikoku, false);
							iHorizontalLineType = 1;
						}
						else if (iPrevContinueEkiIndex != -1)
						{
							/**
								同一行表示の前列車がある場合、
								表示駅が前列車終着駅の場合は、始発駅発時刻を表示する(着時刻およびラインは前列車の管轄)
								前列車終着駅とこの列車の始発駅の間の場合は破線だが、ここでは前列車の管轄となる。
								ただし、この駅が時刻非表示駅なら、時刻・番線は非表示にする
							*/
							if ((iPrevContinueCoreEkiIndex == -1 &&
								iPrevContinueEkiIndex == m_iDisplayJikokuEkiIndex[idx]) ||
								(iPrevContinueCoreEkiIndex != -1 &&
									iPrevContinueCoreEkiIndex == m_iDisplayJikokuEkiIndex[idx]))
							{
								if (pCentDedEkiCont->getMuPtr()->get(m_iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
									(getDisplayTsuukaEkiJikoku() ||
										aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya))
								{
									strHatsu = getCdDedJikokuConv().encode(
										aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getVirtualHatsujikoku(), false);
								}
								bSkipLine = true;
								bSkipChaku = true;
								if (aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
								{
									aCdDrawTextPropHatsu.setTextColor(CdColorProp(128, 128, 128));
								}
							}
							else if ((iPrevContinueCoreEkiIndex == -1 &&
								iPrevContinueEkiIndex < m_iDisplayJikokuEkiIndex[idx]) ||
								(iPrevContinueCoreEkiIndex != -1 &&
									iPrevContinueCoreEkiIndex < m_iDisplayJikokuEkiIndex[idx]))
							{
								//ここでは本来不要だが、CSV出力時はセル数合わせのため、スキップが必須となるので加えておく
								bSkipLine = true;
								bSkipChaku = true;
							}
						}
					}
					/**
						表示駅が終着駅よりも後の場合、路線外終着かつ一つ左側の表示駅の駅Indexが終着駅の駅Indexと同じか小さい場合は、
						この項に路線外終着を表示します。
					*/
					else if (iSyuuchakuEkiIndex < m_iDisplayJikokuEkiIndex[idx])
					{
						if (iSyuuchakuCoreEkiIndex != -1)
						{
							if (iSyuuchakuCoreEkiIndex < m_iDisplayJikokuEkiIndex[idx])
							{
								if (aOperationTableContent.iOuterShuchakuekiIndex != INT_MIN &&
									iSyuuchakuCoreEkiIndex >= m_iDisplayJikokuEkiIndex[idx - 1])
								{
									//路線外終着
									strHatsu = pCdDedEkiCont->get(iSyuuchakuCoreEkiOrder).getOuterTerminalEkimei(aOperationTableContent.iOuterShuchakuekiIndex);

									strChaku = getCdDedJikokuConv().encode(aOperationTableContent.OuterShuchakuJikoku, true);
									iHorizontalLineType = 2;
								}
								else if (iNextContinueEkiIndex != -1)
								{
									/**
										同一行表示の次列車がある場合、
										表示駅が次列車始発駅の場合は、終着駅着時刻とラインを表示する(発時刻は次列車の管轄)
										この列車の終着駅と次列車始発駅との間の場合は破線となり、この列車が描写責任を持つ
										ただし、この駅が時刻非表示駅なら、時刻・番線は非表示にする
									*/
									if ((iNextContinueCoreEkiIndex == -1 &&
										iNextContinueEkiIndex == m_iDisplayJikokuEkiIndex[idx]) ||
										(iNextContinueCoreEkiIndex != -1 &&
											iNextContinueCoreEkiIndex == m_iDisplayJikokuEkiIndex[idx]))
									{
										if (pCentDedEkiCont->getMuPtr()->get(m_iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
											(getDisplayTsuukaEkiJikoku() ||
												aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya))
										{
											strChaku = getCdDedJikokuConv().encode(
												aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getVirtualChakujikoku(), true);
										}
										iHorizontalLineType = 0;

										if (getDisplayTrackName() &&
											pCentDedEkiCont->getMuPtr()->get(m_iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku())
										{
											strChaku += _T("(");
											strChaku += pCdDedEkiCont->get(iSyuuchakuEkiOrder).getCentDedEkiTrack2Cont().get(
												aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(aCentDedRessya.getRessyahoukou());
											strChaku += _T(")");
										}
										bSkipHatsu = true;
										if (aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
										{
											aCdDrawTextPropChaku.setTextColor(CdColorProp(128, 128, 128));
										}
									}
									else if ((iNextContinueCoreEkiIndex == -1 &&
										iNextContinueEkiIndex > m_iDisplayJikokuEkiIndex[idx]) ||
										(iNextContinueCoreEkiIndex != -1 &&
											iNextContinueCoreEkiIndex > m_iDisplayJikokuEkiIndex[idx]))
									{
										iHorizontalLineType = 3;
										//ここでは本来不要だが、CSV出力時はセル数合わせのため、スキップが必須となるので加えておく
										bSkipHatsu = true;
									}
								}

							}
							else if (iSyuuchakuCoreEkiIndex == m_iDisplayJikokuEkiIndex[idx])
							{
								if (aOperationTableContent.iOuterShuchakuekiIndex != INT_MIN)
								{
									if (pCentDedEkiCont->getMuPtr()->get(iSyuuchakuCoreEkiIndex)->getOperationTableDisplayJikoku())
									{
										//路線外終着のデータ上終着駅
										CdDedJikoku ChakuJikoku = aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getChakujikoku();
										CdDedJikoku HatsuJikoku = aOperationTableContent.HatsuJikoku;
										if (!HatsuJikoku.isNull())
										{
											ChakuJikoku = aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getVirtualChakujikoku();
										}

										strChaku = getCdDedJikokuConv().encode(ChakuJikoku, true, HatsuJikoku);
										strHatsu = getCdDedJikokuConv().encode(HatsuJikoku, false, ChakuJikoku);

										if (getDisplayTrackName())
										{
											if (strHatsu.empty())
											{
												strHatsu += _T("(");
												strHatsu += pCdDedEkiCont->get(iSyuuchakuEkiOrder).getCentDedEkiTrack2Cont().get(
													aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(aCentDedRessya.getRessyahoukou());
												strHatsu += _T(")");
											}
											else
											{
												//strChaku += _T(" ");

												strChaku += _T("(");
												strChaku += pCdDedEkiCont->get(iSyuuchakuEkiOrder).getCentDedEkiTrack2Cont().get(
													aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(aCentDedRessya.getRessyahoukou());
												strChaku += _T(")");
											}
										}
									}
									iHorizontalLineType = 0;
								}
								else
								{
									//終着駅
									//次列車と同一行に表示する場合、この駅が時刻非表示駅または駅扱い通過かつ通過駅時刻非表示の場合は、時刻を表示しません
									if (iNextContinueEkiIndex == -1 ||
										(pCentDedEkiCont->getMuPtr()->get(m_iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
											(getDisplayTsuukaEkiJikoku() ||
												aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya)))
									{
										strChaku = getCdDedJikokuConv().encode(
											aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getVirtualChakujikoku(), true);
									}
									iHorizontalLineType = 2;
									//次列車と同一行に表示する場合、この駅の発時刻は、次列車の管轄で描写します。横線は全域になります。
									if (iNextContinueEkiIndex != -1)
									{
										iHorizontalLineType = 0;
										bSkipHatsu = true;
										if (aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
										{
											aCdDrawTextPropChaku.setTextColor(CdColorProp(128, 128, 128));
										}
									}

									if (aOperationTableContent.eAfterType == EBeforeAfterType::BeforeAfterType_OutIn)
									{
										iVerticalLineType = 2;
									}
									else if (iNextShihatsuEkiIndex != -1 &&
										iNextShihatsuEkiIndex == iSyuuchakuCoreEkiIndex)
									{
										iVerticalLineType = 1;
									}

									if (getDisplayTrackName())
									{
										//次列車と同一行に表示する場合、着時刻欄に番線を表示します。ただし、時刻非表示駅の場合は表示しません。
										if (iVerticalLineType == 0 && 
											iNextContinueEkiIndex == -1)
										{
											strHatsu += _T("(");
											strHatsu += pCdDedEkiCont->get(iSyuuchakuEkiOrder).getCentDedEkiTrack2Cont().get(
												aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(aCentDedRessya.getRessyahoukou());
											strHatsu += _T(")");
										}
										else if (iVerticalLineType != 0 ||
											pCentDedEkiCont->getMuPtr()->get(m_iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku())
										{
											//strChaku += _T(" ");

											strChaku += _T("(");
											strChaku += pCdDedEkiCont->get(iSyuuchakuEkiOrder).getCentDedEkiTrack2Cont().get(
												aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(aCentDedRessya.getRessyahoukou());
											strChaku += _T(")");
										}
									}
								}
							}
							else//sihatsuCore<m_iDisplayJikokuEkiIndex[idx]<Sihatsu
							{
								//経由無し
								iHorizontalLineType = 3;
							}
						}
						else if (aOperationTableContent.iOuterShuchakuekiIndex != INT_MIN &&
							iSyuuchakuEkiIndex >= m_iDisplayJikokuEkiIndex[idx - 1])
						{
							//路線外終着
							strHatsu = pCdDedEkiCont->get(iSyuuchakuEkiOrder).getOuterTerminalEkimei(aOperationTableContent.iOuterShuchakuekiIndex);

							strChaku = getCdDedJikokuConv().encode(aOperationTableContent.OuterShuchakuJikoku, true);
							iHorizontalLineType = 2;
						}
						else if (iNextContinueEkiIndex != -1)
						{
							/**
								同一行表示の次列車がある場合、
								表示駅が次列車始発駅の場合は、終着駅着時刻とラインを表示する(発時刻は次列車の管轄)
								この列車の終着駅と次列車始発駅との間の場合は破線となり、この列車が描写責任を持つ
								ただし、この駅が時刻非表示駅なら、時刻・番線は非表示にする
							*/
							if ((iNextContinueCoreEkiIndex == -1 &&
								iNextContinueEkiIndex == m_iDisplayJikokuEkiIndex[idx]) ||
								(iNextContinueCoreEkiIndex != -1 &&
									iNextContinueCoreEkiIndex == m_iDisplayJikokuEkiIndex[idx]))
							{
								if (pCentDedEkiCont->getMuPtr()->get(m_iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
									(getDisplayTsuukaEkiJikoku() ||
										aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya))
								{
									strChaku = getCdDedJikokuConv().encode(
										aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getVirtualChakujikoku(), true);
								}
								iHorizontalLineType = 0;

								if (getDisplayTrackName() &&
									pCentDedEkiCont->getMuPtr()->get(m_iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku())
								{
									strChaku += _T("(");
									strChaku += pCdDedEkiCont->get(iSyuuchakuEkiOrder).getCentDedEkiTrack2Cont().get(
										aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(aCentDedRessya.getRessyahoukou());
									strChaku += _T(")");
								}
								bSkipHatsu = true;
								if (aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
								{
									aCdDrawTextPropChaku.setTextColor(CdColorProp(128, 128, 128));
								}
							}
							else if ((iNextContinueCoreEkiIndex == -1 &&
								iNextContinueEkiIndex > m_iDisplayJikokuEkiIndex[idx]) ||
								(iNextContinueCoreEkiIndex != -1 &&
									iNextContinueCoreEkiIndex > m_iDisplayJikokuEkiIndex[idx]))
							{
								iHorizontalLineType = 3;
								//ここでは本来不要だが、CSV出力時はセル数合わせのため、スキップが必須となるので加えておく
								bSkipHatsu = true;
							}
						}

					}
					/**
						表示駅が始発駅の場合、路線外始発なら、この駅の時刻表示は駅設定に依存します
						出区・前列車接続の場合は、発時刻を表示します。

						iSihatsuEkiIndexの描写がある場合は、iSihatsuCoreEkiIndexは必ず-1になるので、未考慮でよい
					*/
					else if (iSihatsuEkiIndex == m_iDisplayJikokuEkiIndex[idx])
					{
						if (aOperationTableContent.iOuterShihatsuekiIndex != INT_MIN)
						{
							if (pCentDedEkiCont->getMuPtr()->get(iSihatsuEkiIndex)->getOperationTableDisplayJikoku())
							{
								//路線外始発のデータ上始発駅
								CdDedJikoku ChakuJikoku = aOperationTableContent.ChakuJikoku;
								CdDedJikoku HatsuJikoku = aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getHatsujikoku();
								if (!ChakuJikoku.isNull())
								{
									HatsuJikoku = aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getVirtualHatsujikoku();
								}

								strChaku = getCdDedJikokuConv().encode(ChakuJikoku, true, HatsuJikoku);
								strHatsu = getCdDedJikokuConv().encode(HatsuJikoku, false, ChakuJikoku);

								if (getDisplayTrackName())
								{
									//if (!strChaku.empty())
									//{
									//	strChaku += _T(" ");
									//}
									strChaku += _T("(");
									strChaku += pCdDedEkiCont->get(iSihatsuEkiOrder).getCentDedEkiTrack2Cont().get(
										aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(aCentDedRessya.getRessyahoukou());
									strChaku += _T(")");
								}
							}
							iHorizontalLineType = 0;
						}
						else
						{
							//始発駅
							//前列車と同一行に表示する場合、この駅が時刻非表示駅または駅扱い通過かつ通過駅時刻非表示の場合は、時刻を表示しません
							if (iPrevContinueEkiIndex == -1 ||
								(pCentDedEkiCont->getMuPtr()->get(m_iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
									(getDisplayTsuukaEkiJikoku() ||
										aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya)))
							{
								strHatsu = getCdDedJikokuConv().encode(
									aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getVirtualHatsujikoku(), false);
							}
							iHorizontalLineType = 1;
							//前列車と同一行に表示する場合、この駅の着時刻および横線は、前列車の管轄で描写します
							if (iPrevContinueEkiIndex != -1)
							{
								bSkipChaku = true;
								bSkipLine = true;
								if (aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
								{
									aCdDrawTextPropHatsu.setTextColor(CdColorProp(128, 128, 128));
								}
							}

							if (aOperationTableContent.eBeforeType == EBeforeAfterType::BeforeAfterType_OutIn)
							{
								iVerticalLineType = -2;
							}
							else if (iPrevShuchakuEkiIndex != -1 &&
								iPrevShuchakuEkiIndex == iSihatsuEkiIndex)
							{
								iVerticalLineType = -1;
							}

							/**
								前列車と同一行に表示する場合、番線名表示は着時刻欄で行うので、ここでは不要です。
							*/
							if (getDisplayTrackName() &&
								iPrevContinueEkiIndex == -1)
							{
								if (iVerticalLineType == 0)
								{
									strChaku += _T("(");
									strChaku += pCdDedEkiCont->get(iSihatsuEkiOrder).getCentDedEkiTrack2Cont().get(
										aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(aCentDedRessya.getRessyahoukou());
									strChaku += _T(")");
								}
								else
								{
									//strHatsu += _T(" ");

									strHatsu += _T("(");
									strHatsu += pCdDedEkiCont->get(iSihatsuEkiOrder).getCentDedEkiTrack2Cont().get(
										aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(aCentDedRessya.getRessyahoukou());
									strHatsu += _T(")");
								}
							}
						}
					}
					/**
						表示駅が終着駅の場合、路線外終着なら、この駅の時刻表示は駅設定に依存します
						入区・次列車接続の場合は、着時刻を表示します。

						iSyuuchakuEkiIndexの描写がある場合は、iSyuuchakuCoreEkiIndexは必ず-1になるので、未考慮でよい
					*/
					else if (iSyuuchakuEkiIndex == m_iDisplayJikokuEkiIndex[idx])
					{
						if (aOperationTableContent.iOuterShuchakuekiIndex != INT_MIN)
						{
							if (pCentDedEkiCont->getMuPtr()->get(iSyuuchakuEkiIndex)->getOperationTableDisplayJikoku())
							{
								//路線外終着のデータ上終着駅
								CdDedJikoku ChakuJikoku = aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getChakujikoku();
								CdDedJikoku HatsuJikoku = aOperationTableContent.HatsuJikoku;
								if (!HatsuJikoku.isNull())
								{
									ChakuJikoku = aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getVirtualChakujikoku();
								}

								strChaku = getCdDedJikokuConv().encode(ChakuJikoku, true, HatsuJikoku);
								strHatsu = getCdDedJikokuConv().encode(HatsuJikoku, false, ChakuJikoku);

								if (getDisplayTrackName())
								{
									if (strHatsu.empty())
									{
										strHatsu += _T("(");
										strHatsu += pCdDedEkiCont->get(iSyuuchakuEkiOrder).getCentDedEkiTrack2Cont().get(
											aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(aCentDedRessya.getRessyahoukou());
										strHatsu += _T(")");
									}
									else
									{
										//strChaku += _T(" ");

										strChaku += _T("(");
										strChaku += pCdDedEkiCont->get(iSyuuchakuEkiOrder).getCentDedEkiTrack2Cont().get(
											aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(aCentDedRessya.getRessyahoukou());
										strChaku += _T(")");
									}
								}
							}
							iHorizontalLineType = 0;
						}
						else
						{
							//終着駅
							//次列車と同一行に表示する場合、この駅が時刻非表示駅または駅扱い通過かつ通過駅時刻非表示の場合は、時刻を表示しません
							if (iNextContinueEkiIndex == -1 ||
								(pCentDedEkiCont->getMuPtr()->get(m_iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
									(getDisplayTsuukaEkiJikoku() ||
										aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya)))
							{
								strChaku = getCdDedJikokuConv().encode(
									aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getVirtualChakujikoku(), true);
							}
							iHorizontalLineType = 2;
							//次列車と同一行に表示する場合、この駅の発時刻は、次列車の管轄で描写します。横線は全域になります。
							if (iNextContinueEkiIndex != -1)
							{
								iHorizontalLineType = 0;
								bSkipHatsu = true;
								if (aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
								{
									aCdDrawTextPropChaku.setTextColor(CdColorProp(128, 128, 128));
								}
							}

							if (aOperationTableContent.eAfterType == EBeforeAfterType::BeforeAfterType_OutIn)
							{
								iVerticalLineType = 2;
							}
							else if (iNextShihatsuEkiIndex != -1 &&
								iNextShihatsuEkiIndex == iSyuuchakuEkiIndex)
							{
								iVerticalLineType = 1;
							}

							if (getDisplayTrackName())
							{
								//次列車と同一行に表示する場合、着時刻欄に番線を表示します
								if (iVerticalLineType == 0 && 
									iNextContinueEkiIndex == -1)
								{
									strHatsu += _T("(");
									strHatsu += pCdDedEkiCont->get(iSyuuchakuEkiOrder).getCentDedEkiTrack2Cont().get(
										aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(aCentDedRessya.getRessyahoukou());
									strHatsu += _T(")");
								}
								else if(iVerticalLineType != 0 ||
									pCentDedEkiCont->getMuPtr()->get(m_iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku())
								{
									//strChaku += _T(" ");

									strChaku += _T("(");
									strChaku += pCdDedEkiCont->get(iSyuuchakuEkiOrder).getCentDedEkiTrack2Cont().get(
										aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(aCentDedRessya.getRessyahoukou());
									strChaku += _T(")");
								}
							}
						}
					}
					/**
						表示駅が始発駅から終着駅の間の場合、その駅が時刻表示駅なのかで、時刻を表示するかどうかが変わります

					*/
					else//sihatsu<m_iDisplayJikokuEkiIndex[idx]<syuchaku
					{
						int iEkiOrder = aCentDedRessya.EkiOrderOfEkiIndex(m_iDisplayJikokuEkiIndex[idx]);
						int iRessyaTrackIndex = -1;
						CentDedEkiJikoku aEkiJikoku = aCentDedRessya.getCentDedEkiJikoku(iEkiOrder);

						//着時刻側
						bool bChakuIsNone = true;
						CdDedJikoku ChakuJikoku;
						if (aCentDedRessya.isRunBetweenNextEki(iEkiOrder - 1))
						{
							bChakuIsNone = false;
							if (pCentDedEkiCont->getMuPtr()->get(m_iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
								(getDisplayTsuukaEkiJikoku() ||
									aEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya))
							{
								ChakuJikoku = aEkiJikoku.getVirtualChakujikoku();
							}
							iRessyaTrackIndex = aEkiJikoku.getRessyaTrackIndex();
							if (aEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
							{
								aCdDrawTextPropChaku.setTextColor(CdColorProp(128, 128, 128));
							}
						}
						else
						{
							int iPrevEkiOrder = aCentDedRessya.getRunBetweenEkiBackward(iEkiOrder);
							if (iPrevEkiOrder != -1)
							{
								if (pCentDedEkiCont->isSameBrunchLoopGroup(iPrevEkiOrder, iEkiOrder, aCentDedRessya.getRessyahoukou()))
								{
									bChakuIsNone = false;
									CentDedEkiJikoku aPrevEkiJikoku = aCentDedRessya.getCentDedEkiJikoku(iPrevEkiOrder);
									if (pCentDedEkiCont->getMuPtr()->get(m_iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
										(getDisplayTsuukaEkiJikoku() ||
											aPrevEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya))
									{
										ChakuJikoku = aPrevEkiJikoku.getVirtualChakujikoku();
									}
									iRessyaTrackIndex = aPrevEkiJikoku.getRessyaTrackIndex();
									if (aEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
									{
										aCdDrawTextPropChaku.setTextColor(CdColorProp(128, 128, 128));
									}
								}
							}
						}

						bool bHatsuIsNone = true;
						CdDedJikoku HatsuJikoku;
						if (aCentDedRessya.isRunBetweenNextEki(iEkiOrder))
						{
							bHatsuIsNone = false;
							if (pCentDedEkiCont->getMuPtr()->get(m_iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
								(getDisplayTsuukaEkiJikoku() ||
									aEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya))
							{
								HatsuJikoku = aEkiJikoku.getVirtualHatsujikoku();
							}
							iRessyaTrackIndex = aEkiJikoku.getRessyaTrackIndex();
							if (aEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
							{
								aCdDrawTextPropHatsu.setTextColor(CdColorProp(128, 128, 128));
							}
						}
						else
						{
							int iNextEkiOrder = aCentDedRessya.getRunBetweenEkiForward(iEkiOrder);
							if (iNextEkiOrder != -1)
							{
								if (pCentDedEkiCont->isSameBrunchLoopGroup(iNextEkiOrder, iEkiOrder, aCentDedRessya.getRessyahoukou()))
								{
									bHatsuIsNone = false;
									CentDedEkiJikoku aNextEkiJikoku = aCentDedRessya.getCentDedEkiJikoku(iNextEkiOrder);
									if (pCentDedEkiCont->getMuPtr()->get(m_iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
										(getDisplayTsuukaEkiJikoku() ||
											aNextEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya))
									{
										HatsuJikoku = aNextEkiJikoku.getVirtualHatsujikoku();
									}
									iRessyaTrackIndex = aNextEkiJikoku.getRessyaTrackIndex();
									if (aEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
									{
										aCdDrawTextPropHatsu.setTextColor(CdColorProp(128, 128, 128));
									}
								}
							}
						}
						if (bChakuIsNone && bHatsuIsNone)
						{
							iHorizontalLineType = 3;
						}
						else
						{
							iHorizontalLineType = 0;
						}

						strChaku = getCdDedJikokuConv().encode(ChakuJikoku, true, HatsuJikoku);
						strHatsu = getCdDedJikokuConv().encode(HatsuJikoku, false, ChakuJikoku);

						if (getDisplayTrackName() &&
							iRessyaTrackIndex != -1 &&
							pCentDedEkiCont->getMuPtr()->get(m_iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku())
						{
							if (!strChaku.empty() && strHatsu.empty())
							{
								strHatsu += _T("(");
								strHatsu += pCdDedEkiCont->get(iEkiOrder).getCentDedEkiTrack2Cont().
									get(iRessyaTrackIndex).getTrackRyakusyou(aCentDedRessya.getRessyahoukou());
								strHatsu += _T(")");
							}
							else
							{
								//if (!strChaku.empty())
								//{
								//	strChaku += _T(" ");
								//}
								strChaku += _T("(");
								strChaku += pCdDedEkiCont->get(iEkiOrder).getCentDedEkiTrack2Cont().
									get(iRessyaTrackIndex).getTrackRyakusyou(aCentDedRessya.getRessyahoukou());
								strChaku += _T(")");
							}
						}
					}
				}
				else// if(aOperationTableContent.aRessyaProperty.getRessyahoukou() == ERessyahoukou::Ressyahoukou_Nobori)
				{
					if (iSyuuchakuEkiIndex > m_iDisplayJikokuEkiIndex[idx])
					{
						if (iSyuuchakuCoreEkiIndex != -1)
						{
							if (iSyuuchakuCoreEkiIndex > m_iDisplayJikokuEkiIndex[idx])
							{
								if (aOperationTableContent.iOuterShuchakuekiIndex != INT_MIN &&
									iSyuuchakuCoreEkiIndex <= m_iDisplayJikokuEkiIndex[idx + 1])
								{
									//路線外終着
									strHatsu = pCdDedEkiCont->get(iSyuuchakuEkiOrder).getOuterTerminalEkimei(aOperationTableContent.iOuterShuchakuekiIndex);

									strChaku = getCdDedJikokuConv().encode(aOperationTableContent.OuterShuchakuJikoku, true);
									iHorizontalLineType = 1;
								}
								else if (iNextContinueEkiIndex != -1)
								{
									/**
										同一行表示の次列車がある場合、
										表示駅が次列車始発駅の場合は、終着駅着時刻とラインを表示する(発時刻は次列車の管轄)
										この列車の終着駅と次列車始発駅との間の場合は破線となり、この列車が描写責任を持つ
										ただし、この駅が時刻非表示駅なら、時刻・番線は非表示にする
									*/
									if ((iNextContinueCoreEkiIndex == -1 &&
										iNextContinueEkiIndex == m_iDisplayJikokuEkiIndex[idx]) ||
										(iNextContinueCoreEkiIndex != -1 &&
											iNextContinueCoreEkiIndex == m_iDisplayJikokuEkiIndex[idx]))
									{
										if (pCentDedEkiCont->getMuPtr()->get(m_iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
											(getDisplayTsuukaEkiJikoku() ||
												aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya))
										{
											strChaku = getCdDedJikokuConv().encode(
												aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getVirtualChakujikoku(), true);
										}
										iHorizontalLineType = 0;

										if (getDisplayTrackName() &&
											pCentDedEkiCont->getMuPtr()->get(m_iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku())
										{
											strChaku += _T("(");
											strChaku += pCdDedEkiCont->get(iSyuuchakuEkiOrder).getCentDedEkiTrack2Cont().get(
												aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(aCentDedRessya.getRessyahoukou());
											strChaku += _T(")");
										}
										bSkipHatsu = true;
										if (aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
										{
											aCdDrawTextPropChaku.setTextColor(CdColorProp(128, 128, 128));
										}
									}
									else if ((iNextContinueCoreEkiIndex == -1 &&
										iNextContinueEkiIndex < m_iDisplayJikokuEkiIndex[idx]) ||
										(iNextContinueCoreEkiIndex != -1 &&
											iNextContinueCoreEkiIndex < m_iDisplayJikokuEkiIndex[idx]))
									{
										iHorizontalLineType = 3;
										//ここでは本来不要だが、CSV出力時はセル数合わせのため、スキップが必須となるので加えておく
										bSkipHatsu = true;
									}
								}
							}
							else if (iSyuuchakuCoreEkiIndex == m_iDisplayJikokuEkiIndex[idx])
							{
								if (aOperationTableContent.iOuterShuchakuekiIndex != INT_MIN)
								{
									if (pCentDedEkiCont->getMuPtr()->get(iSyuuchakuCoreEkiIndex)->getOperationTableDisplayJikoku())
									{
										//路線外終着のデータ上終着駅
										CdDedJikoku ChakuJikoku = aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getChakujikoku();
										CdDedJikoku HatsuJikoku = aOperationTableContent.HatsuJikoku;
										if (!HatsuJikoku.isNull())
										{
											ChakuJikoku = aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getVirtualChakujikoku();
										}

										strChaku = getCdDedJikokuConv().encode(ChakuJikoku, true, HatsuJikoku);
										strHatsu = getCdDedJikokuConv().encode(HatsuJikoku, false, ChakuJikoku);

										if (getDisplayTrackName())
										{
											if (strHatsu.empty())
											{
												strHatsu += _T("(");
												strHatsu += pCdDedEkiCont->get(iSyuuchakuEkiOrder).getCentDedEkiTrack2Cont().get(
													aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(aCentDedRessya.getRessyahoukou());
												strHatsu += _T(")");
											}
											else
											{
												//strChaku += _T(" ");

												strChaku += _T("(");
												strChaku += pCdDedEkiCont->get(iSyuuchakuEkiOrder).getCentDedEkiTrack2Cont().get(
													aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(aCentDedRessya.getRessyahoukou());
												strChaku += _T(")");
											}
										}
									}
									iHorizontalLineType = 0;
								}
								else
								{
									//終着駅
									//次列車と同一行に表示する場合、この駅が時刻非表示駅または駅扱い通過かつ通過駅時刻非表示の場合は、時刻を表示しません
									if (iNextContinueEkiIndex == -1 ||
										(pCentDedEkiCont->getMuPtr()->get(m_iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
											(getDisplayTsuukaEkiJikoku() ||
												aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya)))
									{
										strChaku = getCdDedJikokuConv().encode(
											aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getVirtualChakujikoku(), true);
									}
									iHorizontalLineType = 1;
									//次列車と同一行に表示する場合、この駅の発時刻は、次列車の管轄で描写します。横線は全域になります。
									if (iNextContinueEkiIndex != -1)
									{
										iHorizontalLineType = 0;
										bSkipHatsu = true;
										if (aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
										{
											aCdDrawTextPropChaku.setTextColor(CdColorProp(128, 128, 128));
										}
									}

									if (aOperationTableContent.eAfterType == EBeforeAfterType::BeforeAfterType_OutIn)
									{
										iVerticalLineType = 2;
									}
									else if (iNextShihatsuEkiIndex != -1 &&
										iNextShihatsuEkiIndex == iSyuuchakuCoreEkiIndex)
									{
										iVerticalLineType = 1;
									}

									if (getDisplayTrackName())
									{
										//次列車と同一行に表示する場合、着時刻欄に番線を表示します。ただし、時刻非表示駅の場合は表示しません。
										if (iVerticalLineType == 0 &&
											iNextContinueEkiIndex == -1)
										{
											strHatsu += _T("(");
											strHatsu += pCdDedEkiCont->get(iSyuuchakuEkiOrder).getCentDedEkiTrack2Cont().get(
												aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(aCentDedRessya.getRessyahoukou());
											strHatsu += _T(")");
										}
										else if(iVerticalLineType != 0 ||
											pCentDedEkiCont->getMuPtr()->get(m_iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku())
										{
											//strChaku += _T(" ");

											strChaku += _T("(");
											strChaku += pCdDedEkiCont->get(iSyuuchakuEkiOrder).getCentDedEkiTrack2Cont().get(
												aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(aCentDedRessya.getRessyahoukou());
											strChaku += _T(")");
										}
									}
								}
							}
							else//sihatsu<m_iDisplayJikokuEkiIndex[idx]<syuchaku
							{
								//経由無し
								iHorizontalLineType = 3;
							}

						}
						else if (aOperationTableContent.iOuterShuchakuekiIndex != INT_MIN &&
							iSyuuchakuEkiIndex <= m_iDisplayJikokuEkiIndex[idx + 1])
						{
							//路線外終着
							strHatsu = pCdDedEkiCont->get(iSyuuchakuEkiOrder).getOuterTerminalEkimei(aOperationTableContent.iOuterShuchakuekiIndex);

							strChaku = getCdDedJikokuConv().encode(aOperationTableContent.OuterShuchakuJikoku, true);
							iHorizontalLineType = 1;
						}
						else if (iNextContinueEkiIndex != -1)
						{
							/**
								同一行表示の次列車がある場合、
								表示駅が次列車始発駅の場合は、終着駅着時刻とラインを表示する(発時刻は次列車の管轄)
								この列車の終着駅と次列車始発駅との間の場合は破線となり、この列車が描写責任を持つ
								ただし、この駅が時刻非表示駅なら、時刻・番線は非表示にする
							*/
							if ((iNextContinueCoreEkiIndex == -1 &&
								iNextContinueEkiIndex == m_iDisplayJikokuEkiIndex[idx]) ||
								(iNextContinueCoreEkiIndex != -1 &&
									iNextContinueCoreEkiIndex == m_iDisplayJikokuEkiIndex[idx]))
							{
								if (pCentDedEkiCont->getMuPtr()->get(m_iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
									(getDisplayTsuukaEkiJikoku() ||
										aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya))
								{
									strChaku = getCdDedJikokuConv().encode(
										aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getVirtualChakujikoku(), true);
								}
								iHorizontalLineType = 0;

								if (getDisplayTrackName() &&
									pCentDedEkiCont->getMuPtr()->get(m_iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku())
								{
									strChaku += _T("(");
									strChaku += pCdDedEkiCont->get(iSyuuchakuEkiOrder).getCentDedEkiTrack2Cont().get(
										aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(aCentDedRessya.getRessyahoukou());
									strChaku += _T(")");
								}
								bSkipHatsu = true;
								if (aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
								{
									aCdDrawTextPropChaku.setTextColor(CdColorProp(128, 128, 128));
								}
							}
							else if ((iNextContinueCoreEkiIndex == -1 &&
								iNextContinueEkiIndex < m_iDisplayJikokuEkiIndex[idx]) ||
								(iNextContinueCoreEkiIndex != -1 &&
									iNextContinueCoreEkiIndex < m_iDisplayJikokuEkiIndex[idx]))
							{
								iHorizontalLineType = 3;
								//ここでは本来不要だが、CSV出力時はセル数合わせのため、スキップが必須となるので加えておく
								bSkipHatsu = true;
							}
						}
					}
					else if (iSihatsuEkiIndex < m_iDisplayJikokuEkiIndex[idx])
					{
						if (iSihatsuCoreEkiIndex != -1)
						{
							if (iSihatsuCoreEkiIndex < m_iDisplayJikokuEkiIndex[idx])
							{
								if (aOperationTableContent.iOuterShihatsuekiIndex != INT_MIN &&
									iSihatsuCoreEkiIndex >= m_iDisplayJikokuEkiIndex[idx - 1])
								{
									//路線外始発
									strChaku = pCdDedEkiCont->get(iSihatsuEkiOrder).getOuterTerminalEkimei(aOperationTableContent.iOuterShihatsuekiIndex);

									strHatsu = getCdDedJikokuConv().encode(aOperationTableContent.OuterShihatsuJikoku, false);
									iHorizontalLineType = 2;
								}
								else if (iPrevContinueEkiIndex != -1)
								{
									/**
										同一行表示の前列車がある場合、
										表示駅が前列車終着駅の場合は、始発駅発時刻を表示する(着時刻およびラインは前列車の管轄)
										前列車終着駅とこの列車の始発駅の間の場合は破線だが、ここでは前列車の管轄となる。
										ただし、この駅が時刻非表示駅なら、時刻・番線は非表示にする
									*/
									if ((iPrevContinueCoreEkiIndex == -1 &&
										iPrevContinueEkiIndex == m_iDisplayJikokuEkiIndex[idx]) ||
										(iPrevContinueCoreEkiIndex != -1 &&
											iPrevContinueCoreEkiIndex == m_iDisplayJikokuEkiIndex[idx]))
									{
										if (pCentDedEkiCont->getMuPtr()->get(m_iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
											(getDisplayTsuukaEkiJikoku() ||
												aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya))
										{
											strHatsu = getCdDedJikokuConv().encode(
												aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getVirtualHatsujikoku(), false);
										}
										bSkipLine = true;
										bSkipChaku = true;
										if (aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
										{
											aCdDrawTextPropHatsu.setTextColor(CdColorProp(128, 128, 128));
										}
									}
									else if ((iPrevContinueCoreEkiIndex == -1 &&
										iPrevContinueEkiIndex > m_iDisplayJikokuEkiIndex[idx]) ||
										(iPrevContinueCoreEkiIndex != -1 &&
											iPrevContinueCoreEkiIndex > m_iDisplayJikokuEkiIndex[idx]))
									{
										//ここでは本来不要だが、CSV出力時はセル数合わせのため、スキップが必須となるので加えておく
										bSkipLine = true;
										bSkipChaku = true;
									}
								}
							}
							else if (iSihatsuCoreEkiIndex == m_iDisplayJikokuEkiIndex[idx])
							{
								if (aOperationTableContent.iOuterShihatsuekiIndex != INT_MIN)
								{
									if (pCentDedEkiCont->getMuPtr()->get(iSihatsuCoreEkiIndex)->getOperationTableDisplayJikoku())
									{
										//路線外始発のデータ上始発駅
										CdDedJikoku ChakuJikoku = aOperationTableContent.ChakuJikoku;
										CdDedJikoku HatsuJikoku = aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getHatsujikoku();
										if (!ChakuJikoku.isNull())
										{
											HatsuJikoku = aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getVirtualHatsujikoku();
										}

										strChaku = getCdDedJikokuConv().encode(ChakuJikoku, true, HatsuJikoku);
										strHatsu = getCdDedJikokuConv().encode(HatsuJikoku, false, ChakuJikoku);

										if (getDisplayTrackName())
										{
											//if (!strChaku.empty())
											//{
											//	strChaku += _T(" ");
											//}
											strChaku += _T("(");
											strChaku += pCdDedEkiCont->get(iSihatsuEkiOrder).getCentDedEkiTrack2Cont().get(
												aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(aCentDedRessya.getRessyahoukou());
											strChaku += _T(")");
										}
									}
									iHorizontalLineType = 0;
								}
								else
								{
									//始発駅
									//前列車と同一行に表示する場合、この駅が時刻非表示駅または駅扱い通過かつ通過駅時刻非表示の場合は、時刻を表示しません
									if (iPrevContinueEkiIndex == -1 ||
										(pCentDedEkiCont->getMuPtr()->get(m_iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
											(getDisplayTsuukaEkiJikoku() ||
												aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya)))
									{
										strHatsu = getCdDedJikokuConv().encode(
											aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getVirtualHatsujikoku(), false);
									}
									iHorizontalLineType = 2;
									//前列車と同一行に表示する場合、この駅の着時刻および横線は、前列車の管轄で描写します
									if (iPrevContinueEkiIndex != -1)
									{
										bSkipChaku = true;
										bSkipLine = true;
										if (aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
										{
											aCdDrawTextPropHatsu.setTextColor(CdColorProp(128, 128, 128));
										}
									}

									if (aOperationTableContent.eBeforeType == EBeforeAfterType::BeforeAfterType_OutIn)
									{
										iVerticalLineType = -2;
									}
									else if (iPrevShuchakuEkiIndex != -1 &&
										iPrevShuchakuEkiIndex == iSihatsuCoreEkiIndex)
									{
										iVerticalLineType = -1;
									}

									/**
										前列車と同一行に表示する場合、番線名表示は着時刻欄で行うので、ここでは不要です。
									*/
									if (getDisplayTrackName() &&
										iPrevContinueEkiIndex == -1)
									{
										if (iVerticalLineType == 0)
										{
											strChaku += _T("(");
											strChaku += pCdDedEkiCont->get(iSihatsuEkiOrder).getCentDedEkiTrack2Cont().get(
												aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(aCentDedRessya.getRessyahoukou());
											strChaku += _T(")");
										}
										else
										{
											//strHatsu += _T(" ");

											strHatsu += _T("(");
											strHatsu += pCdDedEkiCont->get(iSihatsuEkiOrder).getCentDedEkiTrack2Cont().get(
												aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(aCentDedRessya.getRessyahoukou());
											strHatsu += _T(")");
										}
									}
								}
							}
							else//sihatsu<m_iDisplayJikokuEkiIndex[idx]<syuchaku
							{
								//経由無し
								iHorizontalLineType = 3;
							}
						}
						else if (aOperationTableContent.iOuterShihatsuekiIndex != INT_MIN &&
							iSihatsuEkiIndex >= m_iDisplayJikokuEkiIndex[idx - 1])
						{
							//路線外始発
							strChaku = pCdDedEkiCont->get(iSihatsuEkiOrder).getOuterTerminalEkimei(aOperationTableContent.iOuterShihatsuekiIndex);

							strHatsu = getCdDedJikokuConv().encode(aOperationTableContent.OuterShihatsuJikoku, false);
							iHorizontalLineType = 2;
						}
						else if (iPrevContinueEkiIndex != -1)
						{
							/**
								同一行表示の前列車がある場合、
								表示駅が前列車終着駅の場合は、始発駅発時刻を表示する(着時刻およびラインは前列車の管轄)
								前列車終着駅とこの列車の始発駅の間の場合は破線だが、ここでは前列車の管轄となる。
								ただし、この駅が時刻非表示駅なら、時刻・番線は非表示にする
							*/
							if ((iPrevContinueCoreEkiIndex == -1 &&
								iPrevContinueEkiIndex == m_iDisplayJikokuEkiIndex[idx]) ||
								(iPrevContinueCoreEkiIndex != -1 &&
									iPrevContinueCoreEkiIndex == m_iDisplayJikokuEkiIndex[idx]))
							{
								if (pCentDedEkiCont->getMuPtr()->get(m_iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
									(getDisplayTsuukaEkiJikoku() ||
										aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya))
								{
									strHatsu = getCdDedJikokuConv().encode(
										aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getVirtualHatsujikoku(), false);
								}
								bSkipLine = true;
								bSkipChaku = true;
								if (aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
								{
									aCdDrawTextPropHatsu.setTextColor(CdColorProp(128, 128, 128));
								}
							}
							else if ((iPrevContinueCoreEkiIndex == -1 &&
								iPrevContinueEkiIndex > m_iDisplayJikokuEkiIndex[idx]) ||
								(iPrevContinueCoreEkiIndex != -1 &&
									iPrevContinueCoreEkiIndex > m_iDisplayJikokuEkiIndex[idx]))
							{
								//ここでは本来不要だが、CSV出力時はセル数合わせのため、スキップが必須となるので加えておく
								bSkipLine = true;
								bSkipChaku = true;
							}
						}

					}
					/**
						表示駅が始発駅の場合、路線外始発なら、この駅の時刻表示は駅設定に依存します
						出区・前列車接続の場合は、発時刻を表示します。

						iSihatsuEkiIndexの描写がある場合は、iSihatsuCoreEkiIndexは必ず-1になるので、未考慮でよい
					*/
					else if (iSihatsuEkiIndex == m_iDisplayJikokuEkiIndex[idx])
					{
						if (aOperationTableContent.iOuterShihatsuekiIndex != INT_MIN)
						{
							if (pCentDedEkiCont->getMuPtr()->get(iSihatsuEkiIndex)->getOperationTableDisplayJikoku())
							{
								//路線外始発のデータ上始発駅
								CdDedJikoku ChakuJikoku = aOperationTableContent.ChakuJikoku;
								CdDedJikoku HatsuJikoku = aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getHatsujikoku();
								if (!ChakuJikoku.isNull())
								{
									HatsuJikoku = aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getVirtualHatsujikoku();
								}

								strChaku = getCdDedJikokuConv().encode(ChakuJikoku, true, HatsuJikoku);
								strHatsu = getCdDedJikokuConv().encode(HatsuJikoku, false, ChakuJikoku);

								if (getDisplayTrackName())
								{
									//if (!strChaku.empty())
									//{
									//	strChaku += _T(" ");
									//}
									strChaku += _T("(");
									strChaku += pCdDedEkiCont->get(iSihatsuEkiOrder).getCentDedEkiTrack2Cont().get(
										aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(aCentDedRessya.getRessyahoukou());
									strChaku += _T(")");
								}
							}
							iHorizontalLineType = 0;
						}
						else
						{
							//始発駅
							//前列車と同一行に表示する場合、この駅が時刻非表示駅または駅扱い通過かつ通過駅時刻非表示の場合は、時刻を表示しません
							if (iPrevContinueEkiIndex == -1 ||
								(pCentDedEkiCont->getMuPtr()->get(m_iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
									(getDisplayTsuukaEkiJikoku() ||
										aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya)))
							{
								strHatsu = getCdDedJikokuConv().encode(
									aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getVirtualHatsujikoku(), false);
							}
							iHorizontalLineType = 2;
							//前列車と同一行に表示する場合、この駅の着時刻および横線は、前列車の管轄で描写します
							if (iPrevContinueEkiIndex != -1)
							{
								bSkipChaku = true;
								bSkipLine = true;
								if (aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
								{
									aCdDrawTextPropHatsu.setTextColor(CdColorProp(128, 128, 128));
								}
							}

							if (aOperationTableContent.eBeforeType == EBeforeAfterType::BeforeAfterType_OutIn)
							{
								iVerticalLineType = -2;
							}
							else if (iPrevShuchakuEkiIndex != -1 &&
								iPrevShuchakuEkiIndex == iSihatsuEkiIndex)
							{
								iVerticalLineType = -1;
							}

							/**
								前列車と同一行に表示する場合、番線名表示は着時刻欄で行うので、ここでは不要です。
							*/
							if (getDisplayTrackName() &&
								iPrevContinueEkiIndex == -1)
							{
								if (iVerticalLineType == 0)
								{
									strChaku += _T("(");
									strChaku += pCdDedEkiCont->get(iSihatsuEkiOrder).getCentDedEkiTrack2Cont().get(
										aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(aCentDedRessya.getRessyahoukou());
									strChaku += _T(")");
								}
								else
								{
									//strHatsu += _T(" ");

									strHatsu += _T("(");
									strHatsu += pCdDedEkiCont->get(iSihatsuEkiOrder).getCentDedEkiTrack2Cont().get(
										aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(aCentDedRessya.getRessyahoukou());
									strHatsu += _T(")");
								}
							}
						}
					}
					/**
						表示駅が終着駅の場合、路線外終着なら、この駅の時刻表示は駅設定に依存します
						入区・次列車接続の場合は、着時刻を表示します。

						iSyuuchakuEkiIndexの描写がある場合は、iSyuuchakuCoreEkiIndexは必ず-1になるので、未考慮でよい
					*/
					else if (iSyuuchakuEkiIndex == m_iDisplayJikokuEkiIndex[idx])
					{
						if (aOperationTableContent.iOuterShuchakuekiIndex != INT_MIN)
						{
							if (pCentDedEkiCont->getMuPtr()->get(iSyuuchakuEkiIndex)->getOperationTableDisplayJikoku())
							{
								//路線外終着のデータ上終着駅
								CdDedJikoku ChakuJikoku = aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getChakujikoku();
								CdDedJikoku HatsuJikoku = aOperationTableContent.HatsuJikoku;
								if (!HatsuJikoku.isNull())
								{
									ChakuJikoku = aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getVirtualChakujikoku();
								}

								strChaku = getCdDedJikokuConv().encode(ChakuJikoku, true, HatsuJikoku);
								strHatsu = getCdDedJikokuConv().encode(HatsuJikoku, false, ChakuJikoku);

								if (getDisplayTrackName())
								{
									if (strHatsu.empty())
									{
										strHatsu += _T("(");
										strHatsu += pCdDedEkiCont->get(iSyuuchakuEkiOrder).getCentDedEkiTrack2Cont().get(
											aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(aCentDedRessya.getRessyahoukou());
										strHatsu += _T(")");
									}
									else
									{
										//strChaku += _T(" ");

										strChaku += _T("(");
										strChaku += pCdDedEkiCont->get(iSyuuchakuEkiOrder).getCentDedEkiTrack2Cont().get(
											aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(aCentDedRessya.getRessyahoukou());
										strChaku += _T(")");
									}
								}
							}
							iHorizontalLineType = 0;
						}
						else
						{
							//終着駅
							//次列車と同一行に表示する場合、この駅が時刻非表示駅または駅扱い通過かつ通過駅時刻非表示の場合は、時刻を表示しません
							if (iNextContinueEkiIndex == -1 ||
								(pCentDedEkiCont->getMuPtr()->get(m_iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
									(getDisplayTsuukaEkiJikoku() ||
										aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya)))
							{
								strChaku = getCdDedJikokuConv().encode(
									aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getVirtualChakujikoku(), true);
							}
							iHorizontalLineType = 1;
							//次列車と同一行に表示する場合、この駅の発時刻は、次列車の管轄で描写します。横線は全域になります。
							if (iNextContinueEkiIndex != -1)
							{
								iHorizontalLineType = 0;
								bSkipHatsu = true;
								if (aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
								{
									aCdDrawTextPropChaku.setTextColor(CdColorProp(128, 128, 128));
								}
							}

							if (aOperationTableContent.eAfterType == EBeforeAfterType::BeforeAfterType_OutIn)
							{
								iVerticalLineType = 2;
							}
							else if (iNextShihatsuEkiIndex != -1 &&
								iNextShihatsuEkiIndex == iSyuuchakuEkiIndex)
							{
								iVerticalLineType = 1;
							}

							if (getDisplayTrackName())
							{
								//次列車と同一行に表示する場合、着時刻欄に番線を表示します。ただし、時刻非表示駅の場合は表示しません。
								if (iVerticalLineType == 0 &&
									iNextContinueEkiIndex == -1)
								{
									strHatsu += _T("(");
									strHatsu += pCdDedEkiCont->get(iSyuuchakuEkiOrder).getCentDedEkiTrack2Cont().get(
										aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(aCentDedRessya.getRessyahoukou());
									strHatsu += _T(")");
								}
								else if (iVerticalLineType != 0 ||
									pCentDedEkiCont->getMuPtr()->get(m_iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku())
								{
									//strChaku += _T(" ");

									strChaku += _T("(");
									strChaku += pCdDedEkiCont->get(iSyuuchakuEkiOrder).getCentDedEkiTrack2Cont().get(
										aCentDedRessya.getCentDedEkiJikoku(iSyuuchakuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(aCentDedRessya.getRessyahoukou());
									strChaku += _T(")");
								}
							}
						}
					}
					/**
						表示駅が始発駅から終着駅の間の場合、その駅が時刻表示駅なのかで、時刻を表示するかどうかが変わります

					*/
					else//sihatsu<m_iDisplayJikokuEkiIndex[idx]<syuchaku
					{
						int iEkiOrder = aCentDedRessya.EkiOrderOfEkiIndex(m_iDisplayJikokuEkiIndex[idx]);
						int iRessyaTrackIndex = -1;
						CentDedEkiJikoku aEkiJikoku = aCentDedRessya.getCentDedEkiJikoku(iEkiOrder);

						//着時刻側
						bool bChakuIsNone = true;
						CdDedJikoku ChakuJikoku;
						if (aCentDedRessya.isRunBetweenNextEki(iEkiOrder - 1))
						{
							bChakuIsNone = false;
							if (pCentDedEkiCont->getMuPtr()->get(m_iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
								(getDisplayTsuukaEkiJikoku() ||
									aEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya))
							{
								ChakuJikoku = aEkiJikoku.getVirtualChakujikoku();
							}
							iRessyaTrackIndex = aEkiJikoku.getRessyaTrackIndex();
							if (aEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
							{
								aCdDrawTextPropChaku.setTextColor(CdColorProp(128, 128, 128));
							}
						}
						else
						{
							int iPrevEkiOrder = aCentDedRessya.getRunBetweenEkiBackward(iEkiOrder);

							if (iPrevEkiOrder != -1)
							{
								if (pCentDedEkiCont->isSameBrunchLoopGroup(iPrevEkiOrder, iEkiOrder, aCentDedRessya.getRessyahoukou()))
								{
									bChakuIsNone = false;
									CentDedEkiJikoku aPrevEkiJikoku = aCentDedRessya.getCentDedEkiJikoku(iPrevEkiOrder);
									if (pCentDedEkiCont->getMuPtr()->get(m_iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
										(getDisplayTsuukaEkiJikoku() ||
											aPrevEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya))
									{
										ChakuJikoku = aPrevEkiJikoku.getVirtualChakujikoku();
									}
									iRessyaTrackIndex = aPrevEkiJikoku.getRessyaTrackIndex();
									if (aEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
									{
										aCdDrawTextPropChaku.setTextColor(CdColorProp(128, 128, 128));
									}
								}
							}
						}

						bool bHatsuIsNone = true;
						CdDedJikoku HatsuJikoku;
						if (aCentDedRessya.isRunBetweenNextEki(iEkiOrder))
						{
							bHatsuIsNone = false;
							if (pCentDedEkiCont->getMuPtr()->get(m_iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
								(getDisplayTsuukaEkiJikoku() ||
									aEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya))
							{
								HatsuJikoku = aEkiJikoku.getVirtualHatsujikoku();
							}
							iRessyaTrackIndex = aEkiJikoku.getRessyaTrackIndex();
							if (aEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
							{
								aCdDrawTextPropHatsu.setTextColor(CdColorProp(128, 128, 128));
							}
						}
						else
						{
							int iNextEkiOrder = aCentDedRessya.getRunBetweenEkiForward(iEkiOrder);
							if (iNextEkiOrder != -1)
							{
								if (pCentDedEkiCont->isSameBrunchLoopGroup(iNextEkiOrder, iEkiOrder, aCentDedRessya.getRessyahoukou()))
								{
									bHatsuIsNone = false;
									CentDedEkiJikoku aNextEkiJikoku = aCentDedRessya.getCentDedEkiJikoku(iNextEkiOrder);
									if (pCentDedEkiCont->getMuPtr()->get(m_iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
										(getDisplayTsuukaEkiJikoku() ||
											aNextEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya))
									{
										HatsuJikoku = aNextEkiJikoku.getVirtualHatsujikoku();
									}
									iRessyaTrackIndex = aNextEkiJikoku.getRessyaTrackIndex();
									if (aEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
									{
										aCdDrawTextPropHatsu.setTextColor(CdColorProp(128, 128, 128));
									}
								}
							}
						}
						if (bChakuIsNone && bHatsuIsNone)
						{
							iHorizontalLineType = 3;
						}
						else
						{
							iHorizontalLineType = 0;
						}

						strChaku = getCdDedJikokuConv().encode(ChakuJikoku, true, HatsuJikoku);
						strHatsu = getCdDedJikokuConv().encode(HatsuJikoku, false, ChakuJikoku);

						if (getDisplayTrackName() &&
							iRessyaTrackIndex != -1 &&
							pCentDedEkiCont->getMuPtr()->get(m_iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku())
						{
							if (!strChaku.empty() && strHatsu.empty())
							{
								strHatsu += _T("(");
								strHatsu += pCdDedEkiCont->get(iEkiOrder).getCentDedEkiTrack2Cont().
									get(iRessyaTrackIndex).getTrackRyakusyou(aCentDedRessya.getRessyahoukou());
								strHatsu += _T(")");
							}
							else
							{
								//if (!strChaku.empty())
								//{
								//	strChaku += _T(" ");
								//}
								strChaku += _T("(");
								strChaku += pCdDedEkiCont->get(iEkiOrder).getCentDedEkiTrack2Cont().
									get(iRessyaTrackIndex).getTrackRyakusyou(aCentDedRessya.getRessyahoukou());
								strChaku += _T(")");
							}
						}
					}
				}
			}

			pCDcdTextboxChaku->setCdDrawTextProp(aCdDrawTextPropChaku);
			pCDcdTextboxHatsu->setCdDrawTextProp(aCdDrawTextPropHatsu);

			if (!bSkipChaku)
			{
				pCDcdTextboxChaku->setText(strChaku);
			}
			if (!bSkipHatsu)
			{
				pCDcdTextboxHatsu->setText(strHatsu);
			}

			/**
				iHorizontalLineType
					0:横線(全域)
					1:横線(右半分)
					2:横線(左半分)
					3:横線(全域・点線)
			*/
			if (!bSkipLine)
			{
				if (iHorizontalLineType == 0)
				{
					CDcdGridCell* pCDcdGridCell = getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumberLine);
					Ou<CDcDraw_Extension>	pCDcDraw_ExtensionCentral =
						dynamic_castOu<CDcDraw_Extension>(
							pCDcdGridCell->getIfDcDraw());
					if (pCDcDraw_ExtensionCentral == NULL)
					{
						OuNew<CDcDraw_Extension>	pCDcDraw_ExtensionCentral =
							new CDcDraw_Extension(
								CDcDraw_Extension::EDrawType::DrawType_HorizontalLine,
								pCentDedRessyasyubetsu->getDiagramSenColor());

						pCDcdGridCell->setIfDcDraw(pCDcDraw_ExtensionCentral);
					}
				}
				if (iHorizontalLineType == 1)
				{
					CDcdGridCell* pCDcdGridCell = getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumberLine);
					Ou<CDcDraw_Extension>	pCDcDraw_ExtensionCentral =
						dynamic_castOu<CDcDraw_Extension>(
							pCDcdGridCell->getIfDcDraw());
					if (pCDcDraw_ExtensionCentral == NULL)
					{
						OuNew<CDcDraw_Extension>	pCDcDraw_ExtensionCentral =
							new CDcDraw_Extension(
								CDcDraw_Extension::EDrawType::DrawType_HorizontalRightLine,
								pCentDedRessyasyubetsu->getDiagramSenColor());

						pCDcdGridCell->setIfDcDraw(pCDcDraw_ExtensionCentral);
					}

				}
				if (iHorizontalLineType == 2)
				{
					CDcdGridCell* pCDcdGridCell = getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumberLine);
					Ou<CDcDraw_Extension>	pCDcDraw_ExtensionCentral =
						dynamic_castOu<CDcDraw_Extension>(
							pCDcdGridCell->getIfDcDraw());
					if (pCDcDraw_ExtensionCentral == NULL)
					{
						OuNew<CDcDraw_Extension>	pCDcDraw_ExtensionCentral =
							new CDcDraw_Extension(
								CDcDraw_Extension::EDrawType::DrawType_HorizontalLeftLine,
								pCentDedRessyasyubetsu->getDiagramSenColor());

						pCDcdGridCell->setIfDcDraw(pCDcDraw_ExtensionCentral);
					}

				}
				if (iHorizontalLineType == 3)
				{
					CDcdGridCell* pCDcdGridCell = getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumberLine);
					Ou<CDcDraw_Extension>	pCDcDraw_ExtensionCentral =
						dynamic_castOu<CDcDraw_Extension>(
							pCDcdGridCell->getIfDcDraw());
					if (pCDcDraw_ExtensionCentral == NULL)
					{
						OuNew<CDcDraw_Extension>	pCDcDraw_ExtensionCentral =
							new CDcDraw_Extension(
								CDcDraw_Extension::EDrawType::DrawType_HorizontalDotLine,
								pCentDedRessyasyubetsu->getDiagramSenColor());

						pCDcdGridCell->setIfDcDraw(pCDcDraw_ExtensionCentral);
					}

				}
			}

			/**
				iVerticalLineType
					0:縦線(着時刻欄)
					1:縦線(発時刻欄)
					2:出区○印
					3:入区△印
			*/
			if (iVerticalLineType == -1)
			{
				CDcdGridCell* pCDcdGridCell = getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber);
				Ou<CDcDraw_Extension>	pCDcDraw_ExtensionUpper =
					dynamic_castOu<CDcDraw_Extension>(
						pCDcdGridCell->getIfDcDraw());
				if (pCDcDraw_ExtensionUpper == NULL)
				{
					OuNew<CDcDraw_Extension>	pCDcDraw_ExtensionUpper =
						new CDcDraw_Extension(
							CDcDraw_Extension::EDrawType::DrawType_VerticalLine,
							pCentDedRessyasyubetsu->getDiagramSenColor());

					pCDcdGridCell->setIfDcDraw(pCDcDraw_ExtensionUpper);
				}
			}
			else if (iVerticalLineType == 1)
			{
				CDcdGridCell* pCDcdGridCell = getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumberHatsu);
				Ou<CDcDraw_Extension>	pCDcDraw_ExtensionLower =
					dynamic_castOu<CDcDraw_Extension>(
						pCDcdGridCell->getIfDcDraw());
				if (pCDcDraw_ExtensionLower == NULL)
				{
					OuNew<CDcDraw_Extension>	pCDcDraw_ExtensionLower =
						new CDcDraw_Extension(
							CDcDraw_Extension::EDrawType::DrawType_VerticalLine,
							pCentDedRessyasyubetsu->getDiagramSenColor());

					pCDcdGridCell->setIfDcDraw(pCDcDraw_ExtensionLower);
				}
			}
			else if (iVerticalLineType == -2)
			{
				CDcdGridCell* pCDcdGridCell = getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber);
				Ou<CDcDraw_Extension>	pCDcDraw_ExtensionUpper =
					dynamic_castOu<CDcDraw_Extension>(
						pCDcdGridCell->getIfDcDraw());
				if (pCDcDraw_ExtensionUpper == NULL)
				{
					OuNew<CDcDraw_Extension>	pCDcDraw_ExtensionUpper =
						new CDcDraw_Extension(
							CDcDraw_Extension::EDrawType::DrawType_UpperCircle,
							pCentDedRessyasyubetsu->getDiagramSenColor());

					pCDcdGridCell->setIfDcDraw(pCDcDraw_ExtensionUpper);
				}
			}
			else if (iVerticalLineType == 2)
			{
				CDcdGridCell* pCDcdGridCell = getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumberHatsu);
				Ou<CDcDraw_Extension>	pCDcDraw_ExtensionLower =
					dynamic_castOu<CDcDraw_Extension>(
						pCDcdGridCell->getIfDcDraw());
				if (pCDcDraw_ExtensionLower == NULL)
				{
					OuNew<CDcDraw_Extension>	pCDcDraw_ExtensionLower =
						new CDcDraw_Extension(
							CDcDraw_Extension::EDrawType::DrawType_LowerTriangle,
							pCentDedRessyasyubetsu->getDiagramSenColor());

					pCDcdGridCell->setIfDcDraw(pCDcDraw_ExtensionLower);
				}
			}

			//	セルを無効化
			InvalidateCell(iXColumnNumber, iYColumnNumber);
			InvalidateCell(iXColumnNumber, iYColumnNumberLine);
			InvalidateCell(iXColumnNumber, iYColumnNumberHatsu);
		}
	}
}

void  CWndDcdGridOperationTable::OnUpdate_All()
{
	CWaitCursor	aCWaitCursor ;	

	//CentDedDiaから該当運用番号の列車を抜出。
	//deque<RessyaProperty> sRessyaProperty;

	//int iRv = SearchOperationNumberRessya();
	//{

	//	int iYColumnBegin = createYColSpecCont().ColumnNumberFromSpec(
	//		CdOperationTableYColSpec(CdOperationTableYColSpec::ColumnType_Ressya, 0));

	//	getCSelect()->setColumnNumberSelectLimit(
	//		CdDcdZoneXy(
	//			CdDcdZone( 0 , INT_MAX ) ,
	//			//CdDcdZone(0, 1),
	//			//CdDcdZone(1, INT_MAX)
	//			CdDcdZone(iYColumnBegin, m_aRessyaProperty.size())
	//		));
	//}
	//if (iRv < 0)
	//{
	//	//COperationTableDoc*	pLDocument = GetDocument();
	//	GetDocument()->OnCloseDocument();
	//	return;
	//	//CDocument*	pLDocument = GetDocument();
	//	//pLDocument = NULL;
	//}

	const Mu<const CentDedRessya*>* pCentDedRessyaConts[2];
	for (int iRessyahoukou = Ressyahoukou_Kudari;
		iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
	{
		pCentDedRessyaConts[iRessyahoukou] = getCentDedRessyaCont((ERessyahoukou)iRessyahoukou)->getMuPtr();
	}

	const CentDedEkiCont* pCentDedEkiCont = getCDiagramEditDoc()->getCDedRosenFileData()
		->getCentDedRosen()->getCentDedEkiCont();

	/**
		箱ダイヤが有効な場合は、どの駅を表示するかを求める

	*/
	if (getDisplayExtensionOperationTable() &&
		m_ListOperationTableContent != NULL &&
		!m_contOperationTable.empty())
	{
		m_iDisplayJikokuEkiIndex.clear();
		//const Mu<const CentDedEki*>* pCentDedEkiCont = getCDiagramEditDoc()->getCDedRosenFileData()
		//	->getCentDedRosen()->getCentDedEkiCont()->getMuPtr();

		for (int iEkiIndex = 0; iEkiIndex < pCentDedEkiCont->size(); iEkiIndex++)
		{
			const CentDedEki* pCentDedEki = pCentDedEkiCont->getMuPtr()->get(iEkiIndex);
			if (pCentDedEki->getOperationTableDisplayJikoku())
			{
				m_iDisplayJikokuEkiIndex.push_back(iEkiIndex);
			}
		}

		vector<int> contOriginOuter;
		vector<int> contTerminalOuter;
		//for (auto itr = m_ListOperationTableContent->begin();
		//	itr != m_ListOperationTableContent->end(); itr++)
		auto itr = m_ListOperationTableContent->begin();
		for(int iOTIndex=0; iOTIndex< (int)m_contOperationTable.size(); iOTIndex++)
		{
			int iCombineCount = m_contOperationTable[iOTIndex].iCombineCount;
			for (int iCbIndex = 0; iCbIndex < iCombineCount; iCbIndex++, itr++)
			{
				const CentDedRessya* pCentDedRessya =
					pCentDedRessyaConts[itr->aRessyaProperty.getRessyahoukou()]
					->get(itr->aRessyaProperty.getRessyaIndex());

				int iSihatsuEkiOrder = itr->iSihatsuEkiOrder;
				if (!pCentDedRessya->isRunBetweenNextEki(iSihatsuEkiOrder))
				{
					iSihatsuEkiOrder = pCentDedRessya->getRunBetweenEkiForward(iSihatsuEkiOrder);
				}

				int iSyuuchakuEkiOrder = itr->iSyuuchakuEkiOrder;
				if (!pCentDedRessya->isRunBetweenNextEki(iSyuuchakuEkiOrder - 1))
				{
					iSyuuchakuEkiOrder = pCentDedRessya->getRunBetweenEkiBackward(iSyuuchakuEkiOrder);
				}

				/**
					1行に複数列車を表示する場合は、最初の列車の始発駅と、最後の列車の終着駅のみが追加対象となります。
					起点側発着駅では、下り方向の場合は先頭列車、上り方向の場合は末尾列車が対象です。
				*/
				if ((m_contOperationTable[iOTIndex].eRessyahoukou == ERessyahoukou::Ressyahoukou_Kudari &&
					iCbIndex == 0) ||
					(m_contOperationTable[iOTIndex].eRessyahoukou == ERessyahoukou::Ressyahoukou_Nobori &&
						iCbIndex == iCombineCount - 1))
				{
					/**
						まずは、下り列車の始発駅or上り列車の終着駅(起点側発着駅)について調べる。
						上り列車の場合は、駅Orderを駅Indexに直す。
					*/
					int iOriginEkiIndex;
					bool bOriginOuter;
					if (itr->aRessyaProperty.getRessyahoukou() == ERessyahoukou::Ressyahoukou_Kudari)
					{
						iOriginEkiIndex = iSihatsuEkiOrder;
						bOriginOuter = itr->iOuterShihatsuekiIndex != INT_MIN;
					}
					else
					{
						iOriginEkiIndex = pCentDedEkiCont->EkiIndexOfEkiOrder(itr->aRessyaProperty.getRessyahoukou(), iSyuuchakuEkiOrder);
						bOriginOuter = itr->iOuterShuchakuekiIndex != INT_MIN;
					}

					/**
						iOriginEkiIndexが分岐駅の場合、分岐元の駅に統合します。
					*/
					const CentDedEki* pCentDedEkiOrigin = pCentDedEkiCont->getMuPtr()->get(iOriginEkiIndex);
					if (pCentDedEkiOrigin->getBrunchCoreEkiIndex() != -1)
					{
						iOriginEkiIndex = pCentDedEkiOrigin->getBrunchCoreEkiIndex();
					}


					if (bOriginOuter)
					{
						/**
							路線外発着の場合は、一度駅Indexを、contOriginOuterに入れ、最後にチェックを行う。
						*/
						contOriginOuter.push_back(iOriginEkiIndex);
					}
					else
					{
						/**
							路線外発着ではない場合、起点側発着駅Indexがm_iDisplayJikokuEkiIndexの中にあるかを調べ、なかった場合は、挿入する。
						*/
						if (m_iDisplayJikokuEkiIndex.empty())
						{
							m_iDisplayJikokuEkiIndex.push_back(iOriginEkiIndex);
						}
						else
						{
							for (int idx = 0; idx < (int)m_iDisplayJikokuEkiIndex.size(); idx++)
							{
								if (m_iDisplayJikokuEkiIndex[idx] == iOriginEkiIndex)
								{
									//一致するものがあったら、何も行わず終了
									break;
								}
								else if (m_iDisplayJikokuEkiIndex[idx] > iOriginEkiIndex)
								{
									//一致するものがなく、idx番目の駅IndexがiOriginEkiIndexより大きくなってしまったら、idx番目にiOriginEkiIndexを挿入する
									m_iDisplayJikokuEkiIndex.insert(m_iDisplayJikokuEkiIndex.begin() + idx, iOriginEkiIndex);
									break;
								}
								else if (idx == (int)m_iDisplayJikokuEkiIndex.size() - 1)
								{
									//最終要素までにiOriginEkiIndex以上のものがなかった場合、末尾に挿入する
									m_iDisplayJikokuEkiIndex.push_back(iOriginEkiIndex);
								}

							}
						}
					}
				}

				/**
					1行に複数列車を表示する場合は、最初の列車の始発駅と、最後の列車の終着駅のみが追加対象となります。
					終点側発着駅では、下り方向の場合は末尾列車、上り方向の場合は先頭列車が対象です。
				*/
				if ((m_contOperationTable[iOTIndex].eRessyahoukou == ERessyahoukou::Ressyahoukou_Kudari &&
					iCbIndex == iCombineCount - 1) ||
					(m_contOperationTable[iOTIndex].eRessyahoukou == ERessyahoukou::Ressyahoukou_Nobori &&
						iCbIndex == 0))
				{
					/**
						次に、下り列車の終着駅or上り列車の始発駅(終点側発着駅)について調べる。
						上り列車の場合は、駅Orderを駅Indexに直す。
					*/
					int iTerminalEkiIndex;
					bool bTerminalOuter;
					if (itr->aRessyaProperty.getRessyahoukou() == ERessyahoukou::Ressyahoukou_Kudari)
					{
						iTerminalEkiIndex = iSyuuchakuEkiOrder;
						bTerminalOuter = itr->iOuterShuchakuekiIndex != INT_MIN;
					}
					else
					{
						iTerminalEkiIndex = pCentDedEkiCont->EkiIndexOfEkiOrder(itr->aRessyaProperty.getRessyahoukou(), iSihatsuEkiOrder);
						bTerminalOuter = itr->iOuterShihatsuekiIndex != INT_MIN;
					}

					/**
						iTerminalEkiIndexが分岐駅の場合、分岐元の駅に統合します。
					*/
					const CentDedEki* pCentDedEkiTerminal = pCentDedEkiCont->getMuPtr()->get(iTerminalEkiIndex);
					if (pCentDedEkiTerminal->getBrunchCoreEkiIndex() != -1)
					{
						iTerminalEkiIndex = pCentDedEkiTerminal->getBrunchCoreEkiIndex();
					}

					if (bTerminalOuter)
					{
						/**
							路線外発着の場合は、一度駅Indexを、iTerminalOuterに入れ、最後にチェックを行う。
						*/
						contTerminalOuter.push_back(iTerminalEkiIndex);
					}
					else
					{
						/**
							路線外発着ではない場合、終点側発着駅Indexがm_iDisplayJikokuEkiIndexの中にあるかを調べ、なかった場合は、挿入する。
						*/
						if (m_iDisplayJikokuEkiIndex.empty())
						{
							m_iDisplayJikokuEkiIndex.push_back(iTerminalEkiIndex);
						}
						else
						{
							for (int idx = 0; idx < (int)m_iDisplayJikokuEkiIndex.size(); idx++)
							{
								if (m_iDisplayJikokuEkiIndex[idx] == iTerminalEkiIndex)
								{
									//一致するものがあったら、何も行わず終了
									break;
								}
								else if (m_iDisplayJikokuEkiIndex[idx] > iTerminalEkiIndex)
								{
									//一致するものがなく、idx番目の駅IndexがiOriginEkiIndexより大きくなってしまったら、idx番目にiOriginEkiIndexを挿入する
									m_iDisplayJikokuEkiIndex.insert(m_iDisplayJikokuEkiIndex.begin() + idx, iTerminalEkiIndex);
									break;
								}
								else if (idx == (int)m_iDisplayJikokuEkiIndex.size() - 1)
								{
									//最終要素までにiOriginEkiIndex以上のものがなかった場合、末尾に挿入する
									m_iDisplayJikokuEkiIndex.push_back(iTerminalEkiIndex);
								}

							}
						}
					}
				}
			}
		}

		/**
			起点側路線外発着がある場合は、起点側スペースが必要か否かをチェックする
			必要なのは(1)m_iDisplayJikokuEkiIndexが空で、起点側路線外発着が存在する(運用が、路線外始発→路線外終着の一本しかない場合はありうる)
			(2)起点側発着駅が、m_iDisplayJikokuEkiIndexの先頭(最も起点側の表示駅)と同じもしくは起点側
		*/
		for (int iOuterOriginIndex = 0; iOuterOriginIndex < (int)contOriginOuter.size(); iOuterOriginIndex++)
		{
			if (m_iDisplayJikokuEkiIndex.empty())
			{
				m_iDisplayJikokuEkiIndex.push_front(INT_MIN);
				break;
			}
			else if (contOriginOuter[iOuterOriginIndex] <= m_iDisplayJikokuEkiIndex.front())
			{
				m_iDisplayJikokuEkiIndex.push_front(INT_MIN);
				break;
			}
		}
		/**
			終点側路線外発着についても同様に調べる。
			ただし、ここではm_iDisplayJikokuEkiIndexが空であることはない
			(一列車で、両側路線外の場合は、上でINT_MINを挿入ずみなので)
			m_iDisplayJikokuEkiIndexが一つのみの場合、入っているのは起点側駅か起点側路線外なので、いずれにしろINT_MAXを挿入する
		*/
		for (int iOuterTerminalIndex = 0; iOuterTerminalIndex < (int)contTerminalOuter.size(); iOuterTerminalIndex++)
		{
			if (m_iDisplayJikokuEkiIndex.size() == 1)
			{
				m_iDisplayJikokuEkiIndex.push_back(INT_MAX);
				break;
			}
			else if (contTerminalOuter[iOuterTerminalIndex] >= m_iDisplayJikokuEkiIndex.back())
			{
				m_iDisplayJikokuEkiIndex.push_back(INT_MAX);
				break;
			}
		}

	}

	{
		//	コマンドオブジェクト実行によるセル移動でセル選択にならないように、
		//	セル選択を解除し、セル選択機能も一時的に中止します。
		clearSelect() ;
		CPropStack aPropStack( this ) ;
		aPropStack
			.CBoxSelect_setIsEnable( false )
			.CRandomSelect_setIsEnable( false )  ;

		// --------------------------------		
		//	全要素を更新
		// --------------------------------
		//	X列数を増減させる
		//CdOperationTableXColSpecCont aXColSpecCont = createXColSpecCont();
		//int iXCount = getCXDcdGrid()->getXColumnCount();
		//if (iXCount != aXColSpecCont.size())
		//{
		//
		//フォント変更の場合、ヘッダー更新する必要があるので、全更新時は常に更新するようにする。
			OnCreate_Header();
		//}

		
		//COperationTableDoc* pCOperationTableDoc = (COperationTableDoc*)GetDocument();

		//const list<OperationTableContent>& ListOperationTableContent = getCentDedDia()->getcontOperationTableContent().at(pCOperationTableDoc->getOperationNumber());
		//	Y列数を増減させる
		if (m_ListOperationTableContent != NULL)
		{
			CdOperationTableYColSpecCont aCdOperationTableYColSpecCont = createYColSpecCont();

			getCXDcdGrid()->setYColumnCount(1);

			getCXDcdGrid()->setYColumnCount(aCdOperationTableYColSpecCont.size());
			//getCXDcdGrid()->setYColumnCount(
			//	m_ListOperationTableContent->size() + YCOLUMNNNO_RESSYA_0);

			//	各セルに、データを設定
			
			//int idxRessya = 0;
			//for (auto itr = m_ListOperationTableContent->begin();
			//	itr != m_ListOperationTableContent->end(); itr++, idxRessya++)
			auto itr = m_ListOperationTableContent->begin();
			for (int iOTIndex = 0; iOTIndex < (int)m_contOperationTable.size(); iOTIndex++)
			{
				/**
					箱ダイヤの列車間縦線のために、前列車の終着駅と次列車の始発駅を求めます
					次の場合は求める必要がありません
					前列車:この列車が先頭のとき、この列車が路線外始発の時、この列車が出区の時、前列車が路線外終着の時、前列車が入区の時、この列車が同一列車扱いの2列車目以降である
					次列車:この列車が末尾の時、この列車が路線外終着の時、この列車が入区の時、次列車が出区の時、次列車が路線外始発の時、この列車が同一列車扱いの末尾列車ではない
				*/
				if (getDisplayExtensionOperationTable()) 
				{
					for (int iCbIndex = 0; iCbIndex < m_contOperationTable[iOTIndex].iCombineCount; iCbIndex++, itr++)
					{
						const CentDedRessya* pCentDedRessya =
							pCentDedRessyaConts[itr->aRessyaProperty.getRessyahoukou()]
							->get(itr->aRessyaProperty.getRessyaIndex());

						int iYColumnNumber = aCdOperationTableYColSpecCont.ColumnNumberFromSpec(
							CdOperationTableYColSpec(CdOperationTableYColSpec::EColumnType::ColumnType_Ressya, iOTIndex));

						int iPrevShuchakuEkiIndex = -1;
						int iNextShihatsuEkiIndex = -1;
						int iPrevContinueEkiIndex = -1;
						int iNextContinueEkiIndex = -1;
						if (iCbIndex == 0 &&//m_contOperationTableの先頭である
							itr != m_ListOperationTableContent->begin() &&//先頭ではない
							itr->iOuterShihatsuekiIndex == INT_MIN &&//路線外始発ではない
							itr->eBeforeType != EBeforeAfterType::BeforeAfterType_OutIn)//出区ではない
						{
							auto itrPrev = itr;
							itrPrev--;
							if (itrPrev->iOuterShuchakuekiIndex == INT_MIN &&//前列車が路線外終着ではない
								itrPrev->eAfterType != EBeforeAfterType::BeforeAfterType_OutIn)//前列車が入区ではない
							{
								iPrevShuchakuEkiIndex =
									pCentDedEkiCont->EkiIndexOfEkiOrder(
										itrPrev->aRessyaProperty.getRessyahoukou(),
										itrPrev->iSyuuchakuEkiOrder);
								if (pCentDedEkiCont->get(iPrevShuchakuEkiIndex).getBrunchCoreEkiIndex() != -1)
								{
									iPrevShuchakuEkiIndex = pCentDedEkiCont->get(iPrevShuchakuEkiIndex).getBrunchCoreEkiIndex();
								}
							}
						}

						if (iCbIndex == m_contOperationTable[iOTIndex].iCombineCount - 1 &&//m_contOperationTableの末尾である
							itr->iOuterShuchakuekiIndex == INT_MIN &&//路線外終着ではない
							itr->eAfterType != EBeforeAfterType::BeforeAfterType_OutIn)//入区ではない
						{
							auto itrNext = itr;
							itrNext++;
							if (itrNext != m_ListOperationTableContent->end() &&//末尾ではない
								itrNext->iOuterShihatsuekiIndex == INT_MIN &&//次列車が路線外始発ではない
								itrNext->eBeforeType != EBeforeAfterType::BeforeAfterType_OutIn)//次列車が出区ではない
							{
								iNextShihatsuEkiIndex =
									pCentDedEkiCont->EkiIndexOfEkiOrder(
										itrNext->aRessyaProperty.getRessyahoukou(),
										itrNext->iSihatsuEkiOrder);
								if (pCentDedEkiCont->get(iNextShihatsuEkiIndex).getBrunchCoreEkiIndex() != -1)
								{
									iNextShihatsuEkiIndex = pCentDedEkiCont->get(iNextShihatsuEkiIndex).getBrunchCoreEkiIndex();
								}
							}
						}

						if (iCbIndex > 0)
						{
							auto itrPrev = itr;
							itrPrev--;
							int iPrevContinueEkiOrder = itrPrev->iSyuuchakuEkiOrder;
							iPrevContinueEkiIndex = pCentDedEkiCont->EkiIndexOfEkiOrder(
								itrPrev->aRessyaProperty.getRessyahoukou(), iPrevContinueEkiOrder);
						}

						if (iCbIndex < m_contOperationTable[iOTIndex].iCombineCount - 1)
						{
							auto itrNext = itr;
							itrNext++;
							int iNextContinueEkiOrder = itrNext->iSihatsuEkiOrder;
							iNextContinueEkiIndex = pCentDedEkiCont->EkiIndexOfEkiOrder(
								itrNext->aRessyaProperty.getRessyahoukou(), iNextContinueEkiOrder);
						}

						OnUpdate_setCentDedRessya_To_Column_Extension(
							iYColumnNumber, *pCentDedRessya,
							*itr,
							iPrevShuchakuEkiIndex,
							iNextShihatsuEkiIndex,
							iPrevContinueEkiIndex,
							iNextContinueEkiIndex,
							m_contOperationTable[iOTIndex].bIsContinue);

					}
				}
				else
				{
					const CentDedRessya* aShihatsuRessya =
						pCentDedRessyaConts[itr->aRessyaProperty.getRessyahoukou()]
						->get(itr->aRessyaProperty.getRessyaIndex());
					auto itrShihatsu = itr;
					auto itrShuchaku = itr;

					/**
						itrをiCombineCount回インクリメントします。その際、itrShuchakuをitrで書き換えることで、
						forが終わったとき、itrShuchakuは末尾(終着)の列車になり、itrはm_contOperationTable[iOTIndex+1]の先頭列車(もしくはend())になります。
					*/
					for (int iCbIndex = 0; iCbIndex < m_contOperationTable[iOTIndex].iCombineCount; iCbIndex++, itr++)
					{
						itrShuchaku = itr;
					}
					const CentDedRessya* aShuchakuRessya =
						pCentDedRessyaConts[itrShuchaku->aRessyaProperty.getRessyahoukou()]
						->get(itrShuchaku->aRessyaProperty.getRessyaIndex());

					int iYColumnNumber = aCdOperationTableYColSpecCont.ColumnNumberFromSpec(
						CdOperationTableYColSpec(CdOperationTableYColSpec::EColumnType::ColumnType_Ressya, iOTIndex));


					OnUpdate_setCentDedRessya_To_Column(
						iYColumnNumber, 
						*aShihatsuRessya,
						*aShuchakuRessya,
						*itrShihatsu,
						*itrShuchaku,
						m_contOperationTable[iOTIndex].eRessyahoukou);

				}

			}
		}
		//int idxRessya;
		//for (idxRessya = 0 ;
		//	idxRessya < (int)m_aRessyaProperty.size();
		//	idxRessya++ )
		//{
		//	const CentDedRessya* pCentDedRessya = 
		//		pCentDedRessyaConts[m_aRessyaProperty[idxRessya].getRessyahoukou()]
		//		->get(m_aRessyaProperty[idxRessya].getRessyaIndex());

		//	OnUpdate_setCentDedRessya_To_Column(
		//		idxRessya + YCOLUMNNNO_RESSYA_0, *pCentDedRessya) ;
		//} 

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
	//
}

void CWndDcdGridOperationTable::OnCreate_Header()
{
	// --------------------------------
	//	運用表ビューに使用するフォント
	// --------------------------------
	CdFontProp fontpropDefault = createFontProp();
	CdFontProp fontpropBig = createFontProp();
	fontpropBig.setPointTextHeight(fontpropBig.getPointTextHeight() * 2);
	CdColorProp colorpropDefault = createStringColorProp();

	CdOperationTableXColSpecCont aXColSpecCont = createXColSpecCont();
	// --------------------------------
	//	列の数を指定
	// --------------------------------

	getCXDcdGrid()->setXColumnCount(1);
	getCXDcdGrid()->setXColumnCount(aXColSpecCont.size());

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
		{
			//	列車番号
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
				CdOperationTableXColSpec::EColumnType::ColumnType_Ressyabangou));
			CdDcdSizeXy	sizeOperationTable;
			CDcdTextbox	aCDcdTextbox(
				strCellRessyaBangouWidth,
				//"0" ,
				fontpropDefault,
				_T(""), 1, 2, 2);
			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeOperationTable);
			getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeOperationTable.getX());

			CdPenProp aCdPenProp =
				Ou<CDcdLine>(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())->getCdPenProp();
			aCdPenProp.setColor(createGridColorProp());
			aCdPenProp.setStyle(CdPenProp::EStyle::SOLID);
			Ou<CDcdLine>
				(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())
				->setCdPenProp(aCdPenProp);
		}
		{
			//	種別
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
				CdOperationTableXColSpec::EColumnType::ColumnType_Ressyasyubetsu));
			CdDcdSizeXy	sizeOperationTable;
			CDcdTextbox	aCDcdTextbox(
				strCellRessyasyubetsuWidth,
				fontpropDefault,
				_T(""), 1, 2, 2);
			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeOperationTable);
			getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeOperationTable.getX());

			CdPenProp aCdPenProp =
				Ou<CDcdLine>(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())->getCdPenProp();
			aCdPenProp.setColor(createGridColorProp());
			aCdPenProp.setStyle(CdPenProp::EStyle::SOLID);
			Ou<CDcdLine>
				(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())
				->setCdPenProp(aCdPenProp);
		}
		if (getCDiagramEditDoc()->getCDedRosenFileData()
			->getCdDedDispProp().getDisplayRessyamei())
		{
			//	列車名
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
				CdOperationTableXColSpec::EColumnType::ColumnType_Ressyamei));
			CdDcdSizeXy	sizeOperationTable;

			CDcdTextbox	aCDcdTextbox(
				_T("京都京都京都京都京都京都"),
				fontpropDefault,
				_T(""), 1, 2, 2);
			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeOperationTable);

			getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeOperationTable.getX());

			CdPenProp aCdPenProp =
				Ou<CDcdLine>(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())->getCdPenProp();
			aCdPenProp.setColor(createGridColorProp());
			aCdPenProp.setStyle(CdPenProp::EStyle::SOLID);
			Ou<CDcdLine>
				(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())
				->setCdPenProp(aCdPenProp);
		}
		if (getDisplayExtensionOperationTable())
		{
			for (int idx = 0; idx < (int)m_iDisplayJikokuEkiIndex.size(); idx++)
			{
				{
					//	駅名
					int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
						CdOperationTableXColSpec::EColumnType::ColumnType_JikokuDisplayEki, m_iDisplayJikokuEkiIndex[idx]));
					CdDcdSizeXy	sizeOperationTable;

					CDcdTextbox	aCDcdTextbox(
						strCellEkimeiLength,
						//"京都京都京都",
						fontpropDefault,
						_T(""), 1, 2, 2);
					aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeOperationTable);

					getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeOperationTable.getX());

					if (idx != m_iDisplayJikokuEkiIndex.size() - 1)
					{
						CdPenProp aCdPenProp =
							Ou<CDcdLine>(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())->getCdPenProp();
						aCdPenProp.setStyle(CdPenProp::EStyle::NULLPEN);

						Ou<CDcdLine>
							(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())
							->setCdPenProp(aCdPenProp);

						CDcdGridXBorder* pCDcdGridXBorder = getCXDcdGrid()->getXBorder(iXColumnNumber);
						pCDcdGridXBorder->setColumnBorderSize(0);
					}
				}
				if (idx != m_iDisplayJikokuEkiIndex.size() - 1)
				{
					//	列車方向(矢印)
					int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
						CdOperationTableXColSpec::EColumnType::ColumnType_RessyahoukouExtension, m_iDisplayJikokuEkiIndex[idx]));
					if (iXColumnNumber != -1)
					{
						CdDcdSizeXy	sizeOperationTable;

						CDcdTextbox	aCDcdTextbox(
							_T("京都"),
							fontpropDefault,
							_T(""), 1, 2, 2);
						//CDcdTextbox	aCDcdTextbox(
						//	_T("京"),
						//	fontpropBig,
						//	_T(""), 1, 2, 2);
						aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeOperationTable);

						getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeOperationTable.getX());

						CdPenProp aCdPenProp =
							Ou<CDcdLine>(getCXDcdGrid()->getXBorder(idx)->getIfDcDraw())->getCdPenProp();
						aCdPenProp.setStyle(CdPenProp::EStyle::NULLPEN);

						Ou<CDcdLine>
							(getCXDcdGrid()->getXBorder(idx)->getIfDcDraw())
							->setCdPenProp(aCdPenProp);
					}
				}
			}
		}
		else
		{
			{
				//	起点側始終着駅名
				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
					CdOperationTableXColSpec::EColumnType::ColumnType_OriginSideEkimei));
				CdDcdSizeXy	sizeOperationTable;

				CDcdTextbox	aCDcdTextbox(
					strCellEkimeiLength,
					//"京都京都京都",
					fontpropDefault,
					_T(""), 1, 2, 2);
				aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeOperationTable);

				getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeOperationTable.getX());

				CdPenProp aCdPenProp =
					Ou<CDcdLine>(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())->getCdPenProp();
				aCdPenProp.setColor(createGridColorProp());
				aCdPenProp.setStyle(CdPenProp::EStyle::SOLID);
				Ou<CDcdLine>
					(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())
					->setCdPenProp(aCdPenProp);
			}

			if (getDisplayTrackName())
			{
				//	起点側着発番線
				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
					CdOperationTableXColSpec::EColumnType::ColumnType_OriginSideEkiTrack));
				CdDcdSizeXy	sizeOperationTable;

				CDcdTextbox	aCDcdTextbox(
					strCellEkijikokuWidth,
					//"京都京都京都",
					fontpropDefault,
					_T(""), 1, 2, 2);
				aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeOperationTable);

				getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeOperationTable.getX());

				CdPenProp aCdPenProp =
					Ou<CDcdLine>(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())->getCdPenProp();
				aCdPenProp.setColor(createGridColorProp());
				aCdPenProp.setStyle(CdPenProp::EStyle::SOLID);
				Ou<CDcdLine>
					(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())
					->setCdPenProp(aCdPenProp);
			}

			{
				//	起点側駅時刻
				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
					CdOperationTableXColSpec::EColumnType::ColumnType_OriginSideEkijikoku));
				CdDcdSizeXy	sizeOperationTable;

				CDcdTextbox	aCDcdTextbox(
					strCellEkijikokuWidth,
					//"京都京都京都",
					fontpropDefault,
					_T(""), 1, 2, 2);
				aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeOperationTable);

				getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeOperationTable.getX());

				CdPenProp aCdPenProp =
					Ou<CDcdLine>(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())->getCdPenProp();
				aCdPenProp.setColor(createGridColorProp());
				aCdPenProp.setStyle(CdPenProp::EStyle::SOLID);
				Ou<CDcdLine>
					(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())
					->setCdPenProp(aCdPenProp);
			}
			{
				//	列車方向(矢印)
				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
					CdOperationTableXColSpec::EColumnType::ColumnType_Ressyahoukou));
				CdDcdSizeXy	sizeOperationTable;

				CDcdTextbox	aCDcdTextbox(
					_T("京都"),
					fontpropDefault,
					_T(""), 1, 2, 2);
				aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeOperationTable);

				getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeOperationTable.getX());

				CdPenProp aCdPenProp =
					Ou<CDcdLine>(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())->getCdPenProp();
				aCdPenProp.setColor(createGridColorProp());
				aCdPenProp.setStyle(CdPenProp::EStyle::SOLID);
				Ou<CDcdLine>
					(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())
					->setCdPenProp(aCdPenProp);
			}
			{
				//	終点側始終着駅名
				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
					CdOperationTableXColSpec::EColumnType::ColumnType_TerminalSideEkimei));
				CdDcdSizeXy	sizeOperationTable;

				CDcdTextbox	aCDcdTextbox(
					strCellEkimeiLength,
					//"京都京都京都",
					fontpropDefault,
					_T(""), 1, 2, 2);
				aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeOperationTable);

				getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeOperationTable.getX());

				CdPenProp aCdPenProp =
					Ou<CDcdLine>(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())->getCdPenProp();
				aCdPenProp.setColor(createGridColorProp());
				aCdPenProp.setStyle(CdPenProp::EStyle::SOLID);
				Ou<CDcdLine>
					(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())
					->setCdPenProp(aCdPenProp);
			}

			if(getDisplayTrackName())
			{
				//	終点側着発番線
				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
					CdOperationTableXColSpec::EColumnType::ColumnType_TerminalSideEkiTrack));
				CdDcdSizeXy	sizeOperationTable;

				CDcdTextbox	aCDcdTextbox(
					strCellEkijikokuWidth,
					//"京都京都京都",
					fontpropDefault,
					_T(""), 1, 2, 2);
				aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeOperationTable);

				getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeOperationTable.getX());

				CdPenProp aCdPenProp =
					Ou<CDcdLine>(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())->getCdPenProp();
				aCdPenProp.setColor(createGridColorProp());
				aCdPenProp.setStyle(CdPenProp::EStyle::SOLID);
				Ou<CDcdLine>
					(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())
					->setCdPenProp(aCdPenProp);
			}

			{
				//	終点側駅時刻
				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
					CdOperationTableXColSpec::EColumnType::ColumnType_TerminalSideEkijikoku));
				CdDcdSizeXy	sizeOperationTable;

				CDcdTextbox	aCDcdTextbox(
					strCellEkijikokuWidth,
					//"京都京都京都",
					fontpropDefault,
					_T(""), 1, 2, 2);
				aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeOperationTable);

				getCXDcdGrid()->getXColumn(iXColumnNumber)->setColumnSize(sizeOperationTable.getX());

				CdPenProp aCdPenProp =
					Ou<CDcdLine>(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())->getCdPenProp();
				aCdPenProp.setColor(createGridColorProp());
				aCdPenProp.setStyle(CdPenProp::EStyle::SOLID);
				Ou<CDcdLine>
					(getCXDcdGrid()->getXBorder(iXColumnNumber)->getIfDcDraw())
					->setCdPenProp(aCdPenProp);
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
			/*
																									getCXDcdGrid()->getYColumn(YCOLUMNNNO_RESSYA_0)->setColumnSize(sizeOperationTable.getY() ) ;*/
		}
	}
	// --------------------------------
	//	最上列に属性とテキストを設定
	// --------------------------------
	{
		// 列車番号
		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
			CdOperationTableXColSpec::EColumnType::ColumnType_Ressyabangou));
		CString	aString;
		aString = _T("列車番号");

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
		// 種別名
		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
			CdOperationTableXColSpec::EColumnType::ColumnType_Ressyasyubetsu));
		CString	aString;
		aString = _T("種別");

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
	if (getCDiagramEditDoc()->getCDedRosenFileData()
		->getCdDedDispProp().getDisplayRessyamei())
	{
		// 列車名
		int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
			CdOperationTableXColSpec::EColumnType::ColumnType_Ressyamei));
		CString	aString;
		aString = _T("列車名");

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
	if (getDisplayExtensionOperationTable())
	{
		const Mu<const CentDedEki*>* pCentDedEkiCont = getCDiagramEditDoc()->getCDedRosenFileData()
			->getCentDedRosen()->getCentDedEkiCont()->getMuPtr();
		for (int idx = 0; idx < (int)m_iDisplayJikokuEkiIndex.size(); idx++)
		{
			{
				// 駅名
				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
					CdOperationTableXColSpec::EColumnType::ColumnType_JikokuDisplayEki, m_iDisplayJikokuEkiIndex[idx]));
				tstring strEkimei = _T("");
				if (m_iDisplayJikokuEkiIndex[idx] >= 0 &&
					m_iDisplayJikokuEkiIndex[idx] < pCentDedEkiCont->size())
				{
					strEkimei = pCentDedEkiCont->get(m_iDisplayJikokuEkiIndex[idx])->getEkimei();
				}

				Ou<CDcdTextbox>	pCDcdTextbox =
					getCXDcdGrid()->getCell(iXColumnNumber, YCOLUMNNNO_HEADER)->getIfDcDraw();

				CConverter_WinGdi aCConverter_WinGdi;

				CdDrawTextFormat	aCdDrawTextFormat;
				aCdDrawTextFormat.setHorizontal(CdDrawTextFormat::EHolizontal::H_CENTER);
				CdDrawTextProp	aCdDrawTextProp(
					fontpropDefault,
					colorpropDefault,
					aCdDrawTextFormat);

				CdBrushProp	aCdBrushProp(
					aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENU));

				pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
				pCDcdTextbox->setCdBrushProp(aCdBrushProp);
				pCDcdTextbox->setText(strEkimei);
			}
			if (idx != m_iDisplayJikokuEkiIndex.size() - 1)
			{
				// 列車方向(矢印)
				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
					CdOperationTableXColSpec::EColumnType::ColumnType_RessyahoukouExtension, m_iDisplayJikokuEkiIndex[idx]));
				if (iXColumnNumber != -1)
				{
					Ou<CDcdTextbox>	pCDcdTextbox =
						getCXDcdGrid()->getCell(iXColumnNumber, YCOLUMNNNO_HEADER)->getIfDcDraw();

					pCDcdTextbox->setText(_T(""));

					CConverter_WinGdi aCConverter_WinGdi;

					CdBrushProp	aCdBrushProp(
						aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENU));
					pCDcdTextbox->setCdBrushProp(aCdBrushProp);
				}
			}
		}
	}
	else
	{
		{
			// 駅名
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
				CdOperationTableXColSpec::EColumnType::ColumnType_OriginSideEkimei));
			CString	aString;
			aString = _T("駅名");

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
		if (getDisplayTrackName())
		{
			// 着発番線
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
				CdOperationTableXColSpec::EColumnType::ColumnType_OriginSideEkiTrack));
			CString	aString;
			aString = _T("番線");

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
			// 駅時刻
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
				CdOperationTableXColSpec::EColumnType::ColumnType_OriginSideEkijikoku));
			CString	aString;
			aString = _T("駅時刻");

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
			// 列車方向(矢印)
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
				CdOperationTableXColSpec::EColumnType::ColumnType_Ressyahoukou));
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
		}
		{
			// 駅名
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
				CdOperationTableXColSpec::EColumnType::ColumnType_TerminalSideEkimei));
			CString	aString;
			aString = _T("駅名");

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
		if (getDisplayTrackName())
		{
			// 着発番線
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
				CdOperationTableXColSpec::EColumnType::ColumnType_TerminalSideEkiTrack));
			CString	aString;
			aString = _T("番線");

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
			// 駅時刻
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
				CdOperationTableXColSpec::EColumnType::ColumnType_TerminalSideEkijikoku));
			CString	aString;
			aString = _T("駅時刻");

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
	}
}

	// --------------------------------
	//@name メニューコマンドの下請関数
	// --------------------------------

	//	[編集]-[コピー]	
int CWndDcdGridOperationTable::OnEditCopy_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;
	//iRv = -1;
	//Ou<CRfEditCmd_EkiTrack2> pCmd ;
	//Ou<CRfEditCmd_EkiTrack2>* ppCmd = NULL ;
	//if ( !bQueryEnable ){	ppCmd = &pCmd ;}

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
	if (iRv >= 0)
	{
		if (m_ListOperationTableContent->size() == 0)
		{
			iRv = -2;	//列車が表示されていません
		}
	}
	if (iRv >= 0)
	{
		if (getDisplayExtensionOperationTable())
		{
			iRv = -3;	//箱ダイヤ時はコピー無効とします
		}
	}
	// ****************************************************************
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		// -------------------------------- 
		//	クリップボードに転送
		// --------------------------------	

		tstring	strData;
		CdOperationTableYColSpecCont aCdOperationTableYColSpecCont = createYColSpecCont();
		CdOperationTableXColSpecCont aXColSpecCont = createXColSpecCont();
		for (int iOTIndex = 0; iOTIndex < (int)m_contOperationTable.size(); iOTIndex++)
		{
			int iYColumnNumber = aCdOperationTableYColSpecCont.ColumnNumberFromSpec(
				CdOperationTableYColSpec(CdOperationTableYColSpec::EColumnType::ColumnType_Ressya, iOTIndex));

			{
				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
					CdOperationTableXColSpec::EColumnType::ColumnType_Ressyabangou));
				Ou<CDcdTextbox> pCDcdTextbox =
					getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
				strData += pCDcdTextbox->getText(); 
				strData += _T(" ");

			}
			{
				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
					CdOperationTableXColSpec::EColumnType::ColumnType_Ressyasyubetsu));
				Ou<CDcdTextbox> pCDcdTextbox =
					getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
				strData += pCDcdTextbox->getText();
				strData += _T(" ");
			}
			if (getCDiagramEditDoc()->getCDedRosenFileData()
				->getCdDedDispProp().getDisplayRessyamei())
			{
				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
					CdOperationTableXColSpec::EColumnType::ColumnType_Ressyamei));
				Ou<CDcdTextbox> pCDcdTextbox =
					getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
				strData += pCDcdTextbox->getText();
				strData += _T(" ");
			}
			{
				int iXColumnNumber1 = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
					CdOperationTableXColSpec::EColumnType::ColumnType_OriginSideEkimei));
				int iXColumnNumber2 = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
					CdOperationTableXColSpec::EColumnType::ColumnType_OriginSideEkijikoku));
				Ou<CDcdTextbox> pCDcdTextbox1 =
					getCXDcdGrid()->getCell(iXColumnNumber1, iYColumnNumber)->getIfDcDraw();
				Ou<CDcdTextbox> pCDcdTextbox2 =
					getCXDcdGrid()->getCell(iXColumnNumber2, iYColumnNumber)->getIfDcDraw();
				strData += pCDcdTextbox1->getText();
				strData += _T(" ");
				if (getDisplayTrackName())
				{
					int iXColumnNumber3 = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
						CdOperationTableXColSpec::EColumnType::ColumnType_OriginSideEkiTrack));
					Ou<CDcdTextbox> pCDcdTextbox3 =
						getCXDcdGrid()->getCell(iXColumnNumber3, iYColumnNumber)->getIfDcDraw();
					strData += pCDcdTextbox3->getText();
					strData += _T(" ");

				}
				strData += pCDcdTextbox2->getText();
				strData += _T(" ");
			}
			{
				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
					CdOperationTableXColSpec::EColumnType::ColumnType_Ressyahoukou));
				Ou<CDcdTextbox> pCDcdTextbox =
					getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
				strData += pCDcdTextbox->getText();
				strData += _T(" ");
			}
			{
				int iXColumnNumber1 = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
					CdOperationTableXColSpec::EColumnType::ColumnType_TerminalSideEkimei));
				int iXColumnNumber2 = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
					CdOperationTableXColSpec::EColumnType::ColumnType_TerminalSideEkijikoku));
				Ou<CDcdTextbox> pCDcdTextbox1 =
					getCXDcdGrid()->getCell(iXColumnNumber1, iYColumnNumber)->getIfDcDraw();
				Ou<CDcdTextbox> pCDcdTextbox2 =
					getCXDcdGrid()->getCell(iXColumnNumber2, iYColumnNumber)->getIfDcDraw();
				strData += pCDcdTextbox1->getText();
				strData += _T(" ");
				if (getDisplayTrackName())
				{
					int iXColumnNumber3 = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
						CdOperationTableXColSpec::EColumnType::ColumnType_TerminalSideEkiTrack));
					Ou<CDcdTextbox> pCDcdTextbox3 =
						getCXDcdGrid()->getCell(iXColumnNumber3, iYColumnNumber)->getIfDcDraw();
					strData += pCDcdTextbox3->getText();
					strData += _T(" ");

				}
				strData += pCDcdTextbox2->getText();
			}

			strData += _T("\r\n");
		}

		//const CentDedRosen*	pCentDedRosen =
		//	getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen();
		//int iDiaIndex = pCentDedRosen->getCentDedDiaCont()->findCentDedDiaByName(
		//	GetDocument()->getDiaName());

		getCDiagramEditDoc()->CentDedOperationTable_To_Cliboard(
			strData) ;

	//	// -------------------------------- 
	//	//	フォーカスセルを、選択要素中で最大の番線Indexの次位に移動
	//	// --------------------------------
	//	{
	//		//	セル選択をクリアし、
	//		//	フォーカスセルの移動によるセル選択を無効化します。
	//		clearSelect() ;
	//		CPropStack	aPropStack( this ) ;
	//		aPropStack
	//			.CBoxSelect_setIsEnable( false )
	//			.CRandomSelect_setIsEnable( false )  ;
	//	
	//		//	選択要素中で最大の番線Index を求める
	//		int iEkiTrack2IndexMax = -1 ;
	//		{
	//			CaMuiSelect<CentDedEkiTrack2>* pCaMuiSelect = pCmd->getCaMuiSelect() ;
	//			for ( int iIndex = pCaMuiSelect->getAdapteeMu()->size() - 1  ; 
	//				iEkiTrack2IndexMax == -1 && iIndex >= 0 ; iIndex -- )
	//			{
	//				if ( pCaMuiSelect->getSelect( iIndex ) )
	//				{
	//					iEkiTrack2IndexMax = iIndex + pCmd->getIndexDst() ;
	//				}
	//			}
	//		}
	//		//iEkiTrack2IndexMax = 選択されている番線のうち、最大のIndex

	//		//	移動先のフォーカスセル位置を決定
	//		int iYColumnNmber = -1 ;
	//		{
	//			CdEkiTrack2YColSpecCont aCdYColSpecCont = createYColSpecCont() ;
	//			iYColumnNmber = aCdYColSpecCont.ColumnNumberFromSpec( 
	//				CdEkiTrack2YColSpec( CdEkiTrack2YColSpec::ColumnType_EkiTrack2, iEkiTrack2IndexMax ) ) + 1 ;
	//		}
	//		//	フォーカスを移動
	//		{
	//			CdDcdPosXy posxyFocusCellColumnNumber 
	//				= getCFocus()->getFocusCellColumnNumber() ;
	//			if ( iYColumnNmber >= 0 
	//				&& posxyFocusCellColumnNumber != getCFocus()->ColumnNumberPosXy_NULL() )
	//			{
	//				posxyFocusCellColumnNumber.setY( iYColumnNmber ) ;
	//				getCFocus()->setFocusCellColumnNumber( posxyFocusCellColumnNumber ) ;
	//			}
	//		}
	//	}
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv ;


}

int CWndDcdGridOperationTable::OnOperationtableMovetojikokuhyou_Process(BOOL bQueryEnable)
{
	int iRv = 0;
	if (iRv >= 0)
	{
		if (getCentDedDia()->getWaitOperationUpdate())
		{
			iRv = -1;	//運用更新抑止状態です
		}
	}
	if (iRv >= 0)
	{
		if (m_ListOperationTableContent->size() == 0)
		{
			iRv = -2;	//列車が表示されていません
		}
	}
	CdOperationTableYColSpec aCdOperationTableYColSpec = getYColSpecOfFocus();
	if (iRv >= 0)
	{
		if (getCSelect()->getSelectedCellCount() == 0)
		{
			if (aCdOperationTableYColSpec.getColumnType() !=
				CdOperationTableYColSpec::EColumnType::ColumnType_Ressya &&
				aCdOperationTableYColSpec.getColumnType() !=
				CdOperationTableYColSpec::EColumnType::ColumnType_Line &&
				aCdOperationTableYColSpec.getColumnType() !=
				CdOperationTableYColSpec::EColumnType::ColumnType_RessyaHatsu)
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
		auto itr = m_ListOperationTableContent->begin();
		for (int idx = 0; idx < aCdOperationTableYColSpec.getOperationTableContentIndex(); idx++)
		{
			for (int iCBIndex = 0; iCBIndex < m_contOperationTable[idx].iCombineCount; iCBIndex++)
			{
				itr++;
			}
		}
		CdOperationTableXColSpec aCdOperationTableXColSpec = getXColSpecOfFocus();
		OperationTable& pOperationTable = m_contOperationTable[aCdOperationTableYColSpec.getOperationTableContentIndex()];
		if (getDisplayExtensionOperationTable())
		{
			if (aCdOperationTableXColSpec.getColumnType() ==
				CdOperationTableXColSpec::EColumnType::ColumnType_JikokuDisplayEki)
			{
				if ((aCdOperationTableXColSpec.getEkiIndex() == INT_MAX &&
					pOperationTable.eRessyahoukou == ERessyahoukou::Ressyahoukou_Kudari)||
					(aCdOperationTableXColSpec.getEkiIndex() == INT_MIN &&
						pOperationTable.eRessyahoukou == ERessyahoukou::Ressyahoukou_Nobori))
				{
					/**
						下り路線外終着もしくは上り路線外始発欄の場合、複数列車同一行表示の場合、一番最後の列車をフォーカスします。
					*/
					for (int iCBIndex = 1; iCBIndex < pOperationTable.iCombineCount; iCBIndex++)
					{
						itr++;
					}
				}
				else if (aCdOperationTableXColSpec.getEkiIndex() != INT_MIN &&
					aCdOperationTableXColSpec.getEkiIndex() != INT_MAX)
				{
					int iEkiOrder = getCentDedRessyaCont(itr->aRessyaProperty.getRessyahoukou())
						->EkiOrderOfEkiIndex(aCdOperationTableXColSpec.getEkiIndex());
					for (int iCBIndex = 1; iCBIndex < pOperationTable.iCombineCount; iCBIndex++)
					{
						if (iEkiOrder <= itr->iSyuuchakuEkiOrder)
						{
							break;
						}
						itr++;
					}
				}
			}
		}
		else if ((pOperationTable.eRessyahoukou == ERessyahoukou::Ressyahoukou_Kudari ||
			getDisplayNoboriLeftToRight()) &&
			(aCdOperationTableXColSpec.getColumnType() ==
				CdOperationTableXColSpec::EColumnType::ColumnType_TerminalSideEkimei ||
				aCdOperationTableXColSpec.getColumnType() ==
				CdOperationTableXColSpec::EColumnType::ColumnType_TerminalSideEkiTrack ||
				aCdOperationTableXColSpec.getColumnType() ==
				CdOperationTableXColSpec::EColumnType::ColumnType_TerminalSideEkijikoku)|| 
			(pOperationTable.eRessyahoukou == ERessyahoukou::Ressyahoukou_Nobori &&
				!getDisplayNoboriLeftToRight()) &&
			(aCdOperationTableXColSpec.getColumnType() ==
				CdOperationTableXColSpec::EColumnType::ColumnType_OriginSideEkimei ||
				aCdOperationTableXColSpec.getColumnType() ==
				CdOperationTableXColSpec::EColumnType::ColumnType_OriginSideEkiTrack ||
				aCdOperationTableXColSpec.getColumnType() ==
				CdOperationTableXColSpec::EColumnType::ColumnType_OriginSideEkijikoku))
		{
			/**
				下りまたは上り列車左→右表記の場合は、終点側駅名・番線・時刻欄、
				上りかつ上り列車右→左表記の場合は、起点側駅名・番線・時刻欄を選択している場合、
				複数列車同一行表示の場合、一番最後の列車をフォーカスします。
			*/
			for (int iCBIndex = 1; iCBIndex < pOperationTable.iCombineCount; iCBIndex++)
			{
				itr++;
			}
		}
		ERessyahoukou eRessyahoukou = itr->aRessyaProperty.getRessyahoukou();
		int iRessyaidx = itr->aRessyaProperty.getRessyaIndex();
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
			int iEkiOrder = aCentDedRessya.getSihatsuEki();
			if (getDisplayExtensionOperationTable())
			{
				CdOperationTableXColSpec aCdOperationTableXColSpec = getXColSpecOfFocus();
				if (aCdOperationTableXColSpec.getColumnType() ==
					CdOperationTableXColSpec::EColumnType::ColumnType_JikokuDisplayEki &&
					aCdOperationTableXColSpec.getEkiIndex() != INT_MIN &&
					aCdOperationTableXColSpec.getEkiIndex() != INT_MAX)
				{
					iEkiOrder = aCentDedRessya.EkiOrderOfEkiIndex(aCdOperationTableXColSpec.getEkiIndex());
				}
			}
			pCJikokuhyouView->setFocusToRessyaIndex(iRessyaidx, iEkiOrder);
			iRv = 1;	//	時刻表ビューへ移動しました
		}

	}
	return iRv;
}

int CWndDcdGridOperationTable::OnOperationtableMovetojikokuhyouOpenDlg_Process(BOOL bQueryEnable)
{
	int iRv = 0;
	if (iRv >= 0)
	{
		if (getCentDedDia()->getWaitOperationUpdate())
		{
			iRv = -1;	//運用更新抑止状態です
		}
	}
	if (iRv >= 0)
	{
		if (m_ListOperationTableContent->size() == 0)
		{
			iRv = -2;	//列車が表示されていません
		}
	}

	CdOperationTableYColSpec aCdOperationTableYColSpec = getYColSpecOfFocus();
	if (iRv >= 0)
	{
		if (getCSelect()->getSelectedCellCount() == 0)
		{
			if (aCdOperationTableYColSpec.getColumnType() !=
				CdOperationTableYColSpec::EColumnType::ColumnType_Ressya &&
				aCdOperationTableYColSpec.getColumnType() !=
				CdOperationTableYColSpec::EColumnType::ColumnType_Line &&
				aCdOperationTableYColSpec.getColumnType() !=
				CdOperationTableYColSpec::EColumnType::ColumnType_RessyaHatsu)
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
		auto itr = m_ListOperationTableContent->begin();
		for (int idx = 0; idx < aCdOperationTableYColSpec.getOperationTableContentIndex(); idx++)
		{
			for (int iCBIndex = 0; iCBIndex < m_contOperationTable[idx].iCombineCount; iCBIndex++)
			{
				itr++;
			}
		}
		CdOperationTableXColSpec aCdOperationTableXColSpec = getXColSpecOfFocus();
		OperationTable& pOperationTable = m_contOperationTable[aCdOperationTableYColSpec.getOperationTableContentIndex()];
		if (getDisplayExtensionOperationTable())
		{
			if (aCdOperationTableXColSpec.getColumnType() ==
				CdOperationTableXColSpec::EColumnType::ColumnType_JikokuDisplayEki)
			{
				if ((aCdOperationTableXColSpec.getEkiIndex() == INT_MAX &&
					pOperationTable.eRessyahoukou == ERessyahoukou::Ressyahoukou_Kudari) ||
					(aCdOperationTableXColSpec.getEkiIndex() == INT_MIN &&
						pOperationTable.eRessyahoukou == ERessyahoukou::Ressyahoukou_Nobori))
				{
					/**
						下り路線外終着もしくは上り路線外始発欄の場合、複数列車同一行表示の場合、一番最後の列車をフォーカスします。
					*/
					for (int iCBIndex = 1; iCBIndex < pOperationTable.iCombineCount; iCBIndex++)
					{
						itr++;
					}
				}
				else if (aCdOperationTableXColSpec.getEkiIndex() != INT_MIN &&
					aCdOperationTableXColSpec.getEkiIndex() != INT_MAX)
				{
					int iEkiOrder = getCentDedRessyaCont(itr->aRessyaProperty.getRessyahoukou())
						->EkiOrderOfEkiIndex(aCdOperationTableXColSpec.getEkiIndex());
					for (int iCBIndex = 1; iCBIndex < pOperationTable.iCombineCount; iCBIndex++)
					{
						if (iEkiOrder <= itr->iSyuuchakuEkiOrder)
						{
							break;
						}
						itr++;
					}
				}
			}
		}
		else if ((pOperationTable.eRessyahoukou == ERessyahoukou::Ressyahoukou_Kudari ||
			getDisplayNoboriLeftToRight()) &&
			(aCdOperationTableXColSpec.getColumnType() ==
				CdOperationTableXColSpec::EColumnType::ColumnType_TerminalSideEkimei ||
				aCdOperationTableXColSpec.getColumnType() ==
				CdOperationTableXColSpec::EColumnType::ColumnType_TerminalSideEkiTrack ||
				aCdOperationTableXColSpec.getColumnType() ==
				CdOperationTableXColSpec::EColumnType::ColumnType_TerminalSideEkijikoku) ||
			(pOperationTable.eRessyahoukou == ERessyahoukou::Ressyahoukou_Nobori &&
				!getDisplayNoboriLeftToRight()) &&
			(aCdOperationTableXColSpec.getColumnType() ==
				CdOperationTableXColSpec::EColumnType::ColumnType_OriginSideEkimei ||
				aCdOperationTableXColSpec.getColumnType() ==
				CdOperationTableXColSpec::EColumnType::ColumnType_OriginSideEkiTrack ||
				aCdOperationTableXColSpec.getColumnType() ==
				CdOperationTableXColSpec::EColumnType::ColumnType_OriginSideEkijikoku))
		{
			/**
				下りまたは上り列車左→右表記の場合は、終点側駅名・時刻欄、
				上りかつ上り列車右→左表記の場合は、起点側駅名・時刻欄を選択している場合、
				複数列車同一行表示の場合、一番最後の列車をフォーカスします。
			*/
			for (int iCBIndex = 1; iCBIndex < pOperationTable.iCombineCount; iCBIndex++)
			{
				itr++;
			}
		}
		ERessyahoukou eRessyahoukou = itr->aRessyaProperty.getRessyahoukou();
		int iRessyaidx = itr->aRessyaProperty.getRessyaIndex();
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

			CdOperationTableXColSpec aCdOperationTableXColSpec = getXColSpecOfFocus();
			if (aCdOperationTableXColSpec.getColumnType() ==
				CdOperationTableXColSpec::EColumnType::ColumnType_Ressyabangou)
			{
				pCJikokuhyouView->openCDlgRessyaProp(iRessyaidx, 1);
			}
			else if (aCdOperationTableXColSpec.getColumnType() ==
				CdOperationTableXColSpec::EColumnType::ColumnType_Ressyasyubetsu)
			{
				pCJikokuhyouView->openCDlgRessyaProp(iRessyaidx, 2);
			}
			else if (aCdOperationTableXColSpec.getColumnType() ==
				CdOperationTableXColSpec::EColumnType::ColumnType_Ressyamei)
			{
				pCJikokuhyouView->openCDlgRessyaProp(iRessyaidx, 3);
			}
			else if (aCdOperationTableXColSpec.getColumnType() ==
				CdOperationTableXColSpec::EColumnType::ColumnType_OriginSideEkimei ||
				aCdOperationTableXColSpec.getColumnType() ==
				CdOperationTableXColSpec::EColumnType::ColumnType_OriginSideEkiTrack ||
				aCdOperationTableXColSpec.getColumnType() ==
				CdOperationTableXColSpec::EColumnType::ColumnType_OriginSideEkijikoku)
			{
				CentDedRessya aCentDedRessya = getCentDedRessyaCont(eRessyahoukou)->get(iRessyaidx);
				if (eRessyahoukou == ERessyahoukou::Ressyahoukou_Kudari ||
					getDisplayNoboriLeftToRight())
				{
					pCJikokuhyouView->openCDlgEkijikokuProp(iRessyaidx, aCentDedRessya.getValidSihatsuEki(), true);
				}
				else
				{
					pCJikokuhyouView->openCDlgEkijikokuProp(iRessyaidx, aCentDedRessya.getValidSyuuchakuEki(), false);
				}
			}
			else if (aCdOperationTableXColSpec.getColumnType() ==
				CdOperationTableXColSpec::EColumnType::ColumnType_TerminalSideEkimei ||
				aCdOperationTableXColSpec.getColumnType() ==
				CdOperationTableXColSpec::EColumnType::ColumnType_TerminalSideEkiTrack ||
				aCdOperationTableXColSpec.getColumnType() ==
				CdOperationTableXColSpec::EColumnType::ColumnType_TerminalSideEkijikoku)
			{
				CentDedRessya aCentDedRessya = getCentDedRessyaCont(eRessyahoukou)->get(iRessyaidx);
				if (eRessyahoukou == ERessyahoukou::Ressyahoukou_Kudari ||
					getDisplayNoboriLeftToRight())
				{
					pCJikokuhyouView->openCDlgEkijikokuProp(iRessyaidx, aCentDedRessya.getValidSyuuchakuEki(), false);
				}
				else
				{
					pCJikokuhyouView->openCDlgEkijikokuProp(iRessyaidx, aCentDedRessya.getValidSihatsuEki(), true);
				}
			}
			else
			{
				CentDedRessya aCentDedRessya = getCentDedRessyaCont(eRessyahoukou)->get(iRessyaidx);

				int iEkiOrder = aCentDedRessya.getSihatsuEki();
				if (getDisplayExtensionOperationTable())
				{
					CdOperationTableXColSpec aCdOperationTableXColSpec = getXColSpecOfFocus();
					if (aCdOperationTableXColSpec.getColumnType() ==
						CdOperationTableXColSpec::EColumnType::ColumnType_JikokuDisplayEki &&
						aCdOperationTableXColSpec.getEkiIndex() != INT_MIN &&
						aCdOperationTableXColSpec.getEkiIndex() != INT_MAX)
					{
						iEkiOrder = aCentDedRessya.EkiOrderOfEkiIndex(aCdOperationTableXColSpec.getEkiIndex());
					}
				}
				pCJikokuhyouView->setFocusToRessyaIndex(iRessyaidx, iEkiOrder);
			}
			iRv = 1;	//	時刻表ビューへ移動しました
		}

	}
	return iRv;
}

int CWndDcdGridOperationTable::OnOperationtableMovetodiagram_Process(BOOL bQueryEnable)
{
	int iRv = 0;
	if (iRv >= 0)
	{
		if (getCentDedDia()->getWaitOperationUpdate())
		{
			iRv = -5;	//運用更新抑止状態です
		}
	}
	CdOperationTableYColSpec aCdOperationTableYColSpec = getYColSpecOfFocus();
	if (iRv >= 0)
	{
		if (getCSelect()->getSelectedCellCount() == 0)
		{
			if (aCdOperationTableYColSpec.getColumnType() !=
				CdOperationTableYColSpec::EColumnType::ColumnType_Ressya &&
				aCdOperationTableYColSpec.getColumnType() !=
				CdOperationTableYColSpec::EColumnType::ColumnType_Line &&
				aCdOperationTableYColSpec.getColumnType() !=
				CdOperationTableYColSpec::EColumnType::ColumnType_RessyaHatsu)
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
		auto itr = m_ListOperationTableContent->begin();
		for (int idx = 0; idx < aCdOperationTableYColSpec.getOperationTableContentIndex(); idx++)
		{
			for (int iCBIndex = 0; iCBIndex < m_contOperationTable[idx].iCombineCount; iCBIndex++)
			{
				itr++;
			}
		}
		CdOperationTableXColSpec aCdOperationTableXColSpec = getXColSpecOfFocus();
		OperationTable& pOperationTable = m_contOperationTable[aCdOperationTableYColSpec.getOperationTableContentIndex()];
		if (getDisplayExtensionOperationTable())
		{
			if (aCdOperationTableXColSpec.getColumnType() ==
				CdOperationTableXColSpec::EColumnType::ColumnType_JikokuDisplayEki)
			{
				if ((aCdOperationTableXColSpec.getEkiIndex() == INT_MAX &&
					pOperationTable.eRessyahoukou == ERessyahoukou::Ressyahoukou_Kudari) ||
					(aCdOperationTableXColSpec.getEkiIndex() == INT_MIN &&
						pOperationTable.eRessyahoukou == ERessyahoukou::Ressyahoukou_Nobori))
				{
					/**
						下り路線外終着もしくは上り路線外始発欄の場合、複数列車同一行表示の場合、一番最後の列車をフォーカスします。
					*/
					for (int iCBIndex = 1; iCBIndex < pOperationTable.iCombineCount; iCBIndex++)
					{
						itr++;
					}
				}
				else if (aCdOperationTableXColSpec.getEkiIndex() != INT_MIN &&
					aCdOperationTableXColSpec.getEkiIndex() != INT_MAX)
				{
					int iEkiOrder = getCentDedRessyaCont(itr->aRessyaProperty.getRessyahoukou())
						->EkiOrderOfEkiIndex(aCdOperationTableXColSpec.getEkiIndex());
					for (int iCBIndex = 1; iCBIndex < pOperationTable.iCombineCount; iCBIndex++)
					{
						if (iEkiOrder <= itr->iSyuuchakuEkiOrder)
						{
							break;
						}
						itr++;
					}
				}
			}
		}
		else if ((pOperationTable.eRessyahoukou == ERessyahoukou::Ressyahoukou_Kudari ||
			getDisplayNoboriLeftToRight()) &&
			(aCdOperationTableXColSpec.getColumnType() ==
				CdOperationTableXColSpec::EColumnType::ColumnType_TerminalSideEkimei ||
				aCdOperationTableXColSpec.getColumnType() ==
				CdOperationTableXColSpec::EColumnType::ColumnType_TerminalSideEkiTrack ||
				aCdOperationTableXColSpec.getColumnType() ==
				CdOperationTableXColSpec::EColumnType::ColumnType_TerminalSideEkijikoku) ||
			(pOperationTable.eRessyahoukou == ERessyahoukou::Ressyahoukou_Nobori &&
				!getDisplayNoboriLeftToRight()) &&
			(aCdOperationTableXColSpec.getColumnType() ==
				CdOperationTableXColSpec::EColumnType::ColumnType_OriginSideEkimei ||
				aCdOperationTableXColSpec.getColumnType() ==
				CdOperationTableXColSpec::EColumnType::ColumnType_OriginSideEkiTrack ||
				aCdOperationTableXColSpec.getColumnType() ==
				CdOperationTableXColSpec::EColumnType::ColumnType_OriginSideEkijikoku))
		{
			/**
				下りまたは上り列車左→右表記の場合は、終点側駅名・時刻欄、
				上りかつ上り列車右→左表記の場合は、起点側駅名・時刻欄を選択している場合、
				複数列車同一行表示の場合、一番最後の列車をフォーカスします。
			*/
			for (int iCBIndex = 1; iCBIndex < pOperationTable.iCombineCount; iCBIndex++)
			{
				itr++;
			}
		}
		ERessyahoukou eRessyahoukou = itr->aRessyaProperty.getRessyahoukou();
		int iRessyaidx = itr->aRessyaProperty.getRessyaIndex();
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
			//pCJikokuhyouDoc = ダイヤグラムドキュメント
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
			int iEkiIndex = aCentDedRessya.EkiIndexOfEkiOrder(aCentDedRessya.getSihatsuEki());

			if (getDisplayExtensionOperationTable())
			{
				CdOperationTableXColSpec aCdOperationTableXColSpec = getXColSpecOfFocus();
				if (aCdOperationTableXColSpec.getColumnType() ==
					CdOperationTableXColSpec::EColumnType::ColumnType_JikokuDisplayEki &&
					aCdOperationTableXColSpec.getEkiIndex() != INT_MIN &&
					aCdOperationTableXColSpec.getEkiIndex() != INT_MAX)
				{
					iEkiIndex = aCdOperationTableXColSpec.getEkiIndex();
				}
			}
			pCDedDiagramView->setZone_Dgr(aCentDedRessya.getCentDedEkiJikoku(aCentDedRessya.getSihatsuEki()).getHatsujikoku(true),
				iEkiIndex,
				aCentDedRessya.getRessyahoukou() == Ressyahoukou_Nobori);
		}
	}
	return iRv;
}

int CWndDcdGridOperationTable::OnFileExportOperationTableCsv_Process(BOOL bQueryEnable)
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
	if (iRv >= 0)
	{
		if (m_ListOperationTableContent->size() == 0)
		{
			iRv = -2;	//列車が表示されていません
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

			CconvOperationTableCsv	aConv(getCDiagramEditApp()->createCconvOperationTableCsv());
			CdCsvDocument	aCdCsvDocument;
			int iResult = aConv.encode(
				*pCDedRosenFileData->getCentDedRosen(),
				*getCentDedDia(),
				getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp(),
				{ GetDocument()->getOperationNumber() },
				getDisplayExtensionOperationTable(),
				getDisplaySecondEkiJikoku(),
				getDisplayColonEkiJikoku(),
				getDisplayParentSyubetsu(),
				getDisplayNoboriLeftToRight(),
				getDisplayTrackName(),
				getDisplayTsuukaEkiJikoku(),
				&aCdCsvDocument);
			//iResult = 
			//	-1 ; // iDiaIndex が不正です。
			//	-2 ; // iRessyaIndex が不正です。
			//	-3 ; // iRessyaCount が不正です。 
			if (iResult < 0)
			{
				GetDlgItemText(IDC_TEXT_ENCODE_ERROR, strError);
				//strError="CSVへの変換に失敗しました。"

				strError.Format(_T("%s(%d)"), CString(strError), iResult);
				iRv = iResult - 10;
				//	-11 ; // iDiaIndex が不正です。
				//	-12 ; // iRessyaIndex が不正です。
				//	-13 ; // iRessyaCount が不正です。 
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
CWndDcdGridOperationTable::CWndDcdGridOperationTable()
	: m_bUpdate_All_Requested( false )
	, m_bInitialUpdateComplete(false)
	, m_bDisplayExtensionOperationTable(false)
	, m_bDisplaySecondEkiJikoku(false)
	, m_bDisplayColonEkiJikoku(false)
	, m_bDisplayParentSyubetsu(false)
	, m_bDisplayNoboriLeftToRight(false)
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
CWndDcdGridOperationTable::~CWndDcdGridOperationTable()
{
}

// ********************************
//@name	CDcdGrid
// ********************************

// ********************************
//@name	CWndDcdGrid
// ********************************

	// ********************************
	//@name CWndDcdGridRessyasyubetsu-操作
	// ********************************

COperationTableDoc * CWndDcdGridOperationTable::GetDocument()
{
	CView* pCView = (CView*)GetParent();
	return (COperationTableDoc*)pCView->GetDocument();
}

const CentDedDia*	CWndDcdGridOperationTable::getCentDedDia()
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

const CentDedRessyaCont*	CWndDcdGridOperationTable::getCentDedRessyaCont(
	ERessyahoukou eRessyahoukou)
{
	const CentDedDia* pCentDedDia = getCentDedDia();
	if (pCentDedDia == NULL) {
		return (NULL);
	}
	return (pCentDedDia->getCentDedRessyaCont(eRessyahoukou));
};


int CWndDcdGridOperationTable::OnViewDisplayExtensionOperationTable_Process(
	BOOL bQueryEnable)
{
	int iRv = 0;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (getDisplayExtensionOperationTable())
	{
		iRv = 1;	//(bQueryEnable==TRUEの場合)[箱ダイヤを有効にする]が有効です。
	}
	// ****************************************************************
	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドを実行
		// ****************************************************************
		setDisplayExtensionOperationTable(!getDisplayExtensionOperationTable());
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv;
}

int CWndDcdGridOperationTable::OnViewDisplaySecondEkijikoku_Process(
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

int CWndDcdGridOperationTable::OnViewDisplayColonEkijikoku_Process(
	BOOL bQueryEnable)
{
	int iRv = 0;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (getDisplayColonEkiJikoku())
	{
		iRv = 1;	//(bQueryEnable==TRUEの場合)[駅時刻をコロン付きで表示する]が有効です。
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

int CWndDcdGridOperationTable::OnViewDisplayParentSyubetsu_Process(
	BOOL bQueryEnable)
{
	int iRv = 0;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (getDisplayParentSyubetsu())
	{
		iRv = 1;	//(bQueryEnable==TRUEの場合)[列車の表示を親種別で行う]が有効です。
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

int CWndDcdGridOperationTable::OnViewDisplayNoboriLeftToRight_Process(
	BOOL bQueryEnable)
{
	int iRv = 0;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (getDisplayNoboriLeftToRight())
	{
		iRv = 1;	//(bQueryEnable==TRUEの場合)[上り列車の始発駅を左側にして描写する]が有効です。
	}
	// ****************************************************************
	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドを実行
		// ****************************************************************
		setDisplayNoboriLeftToRight(!getDisplayNoboriLeftToRight());
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv;
}

int CWndDcdGridOperationTable::OnViewDisplayTrackName_Process(
	BOOL bQueryEnable)
{
	int iRv = 0;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (getDisplayTrackName())
	{
		iRv = 1;	//(bQueryEnable==TRUEの場合)[着発番線名を表示する]が有効です。
	}
	// ****************************************************************
	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドを実行
		// ****************************************************************
		setDisplayTrackName(!getDisplayTrackName());
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv;
}

int CWndDcdGridOperationTable::OnViewDisplayTsuukaEkiJikoku_Process(
	BOOL bQueryEnable)
{
	int iRv = 0;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (getDisplayTsuukaEkiJikoku())
	{
		iRv = 1;	//(bQueryEnable==TRUEの場合)[着発番線名を表示する]が有効です。
	}
	// ****************************************************************
	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドを実行
		// ****************************************************************
		setDisplayTsuukaEkiJikoku(!getDisplayTsuukaEkiJikoku());
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv;
}


bool CWndDcdGridOperationTable::getDisplayExtensionOperationTable()const
{
	return m_bDisplayExtensionOperationTable;
}
int CWndDcdGridOperationTable::setDisplayExtensionOperationTable(bool value)
{
	int iRv = 0;
	if (m_bDisplayExtensionOperationTable != value)
	{
		m_bDisplayExtensionOperationTable = value;

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
		getCDiagramEditApp()->writeCWndDcdGridOperationTableViewProp(this);
	}
	return (iRv);
}

bool CWndDcdGridOperationTable::getDisplaySecondEkiJikoku()const
{
	return m_bDisplaySecondEkiJikoku;
}
int CWndDcdGridOperationTable::setDisplaySecondEkiJikoku(bool value)
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
		getCDiagramEditApp()->writeCWndDcdGridOperationTableViewProp(this);
	}
	return (iRv);
}

bool CWndDcdGridOperationTable::getDisplayColonEkiJikoku()const
{
	return m_bDisplayColonEkiJikoku;
}
int CWndDcdGridOperationTable::setDisplayColonEkiJikoku(bool value)
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
		getCDiagramEditApp()->writeCWndDcdGridOperationTableViewProp(this);
	}
	return (iRv);
}

bool CWndDcdGridOperationTable::getDisplayParentSyubetsu()const
{
	return m_bDisplayParentSyubetsu;
}
int CWndDcdGridOperationTable::setDisplayParentSyubetsu(bool value)
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
		getCDiagramEditApp()->writeCWndDcdGridOperationTableViewProp(this);
	}
	return (iRv);
}

bool CWndDcdGridOperationTable::getDisplayNoboriLeftToRight()const
{
	return m_bDisplayNoboriLeftToRight;
}
int CWndDcdGridOperationTable::setDisplayNoboriLeftToRight(bool value)
{
	int iRv = 0;
	if (m_bDisplayNoboriLeftToRight != value)
	{
		m_bDisplayNoboriLeftToRight = value;

		//	親種別機能の有効無効が変化した場合は、
		//	ビューを更新します。
		//	ただし、運用更新抑止状態かつ箱ダイヤ形式で表示の場合は、ビューの更新は行いません
		if (!getCentDedDia()->getWaitOperationUpdate() &&
			!getDisplayExtensionOperationTable())
		{
			OnUpdate_All();
			InvalidateGrid();
		}

		//	秒単位の表示の有無を、
		//	.ini ファイルに保存
		getCDiagramEditApp()->writeCWndDcdGridOperationTableViewProp(this);
	}
	return (iRv);
}

bool CWndDcdGridOperationTable::getDisplayTrackName()const
{
	return m_bDisplayTrackName;
}
int CWndDcdGridOperationTable::setDisplayTrackName(bool value)
{
	int iRv = 0;
	if (m_bDisplayTrackName != value)
	{
		m_bDisplayTrackName = value;

		//	着発番線名を表示が変化した場合は、
		//	ビューを更新します。
		//	ただし、運用更新抑止状態の場合は、ビューの更新は行いません
		if (!getCentDedDia()->getWaitOperationUpdate())
		{
			OnUpdate_All();
			InvalidateGrid();
		}

		//	着発番線名を表示を、
		//	.ini ファイルに保存
		getCDiagramEditApp()->writeCWndDcdGridOperationTableViewProp(this);
	}
	return (iRv);
}

bool CWndDcdGridOperationTable::getDisplayTsuukaEkiJikoku()const
{
	return m_bDisplayTsuukaEkiJikoku;
}
int CWndDcdGridOperationTable::setDisplayTsuukaEkiJikoku(bool value)
{
	int iRv = 0;
	if (m_bDisplayTsuukaEkiJikoku != value)
	{
		m_bDisplayTsuukaEkiJikoku = value;

		//	着発番線名を表示が変化した場合は、
		//	ビューを更新します。
		//	ただし、運用更新抑止状態かつ従来形式表示の場合は、ビューの更新は行いません
		if (!getCentDedDia()->getWaitOperationUpdate() &&
			getDisplayExtensionOperationTable())
		{
			OnUpdate_All();
			InvalidateGrid();
		}

		//	着発番線名を表示を、
		//	.ini ファイルに保存
		getCDiagramEditApp()->writeCWndDcdGridOperationTableViewProp(this);
	}
	return (iRv);
}


// ----------------------------------------------------------------
//	MFC
// ----------------------------------------------------------------
BEGIN_MESSAGE_MAP(CWndDcdGridOperationTable,CWndDcdGridOperationTable::super)
	//{{AFX_MSG_MAP(CWndDcdGridOperationTable)
	ON_WM_CREATE()
	ON_WM_KEYUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_OperationTable_MoveToJikokuhyou, &CWndDcdGridOperationTable::OnOperationtableMovetojikokuhyou)
	ON_UPDATE_COMMAND_UI(ID_OperationTable_MoveToJikokuhyou, &CWndDcdGridOperationTable::OnUpdateOperationtableMovetojikokuhyou)
	ON_COMMAND(ID_OperationTable_MoveToJikokuhyouOpenDlg, &CWndDcdGridOperationTable::OnOperationtableMovetojikokuhyouOpenDlg)
	ON_UPDATE_COMMAND_UI(ID_OperationTable_MoveToJikokuhyouOpenDlg, &CWndDcdGridOperationTable::OnUpdateOperationtableMovetojikokuhyouOpenDlg)
	ON_COMMAND(ID_OperationTable_MoveToDiagram, &CWndDcdGridOperationTable::OnOperationtableMovetodiagram)
	ON_UPDATE_COMMAND_UI(ID_OperationTable_MoveToDiagram, &CWndDcdGridOperationTable::OnUpdateOperationtableMovetodiagram)
	ON_COMMAND(ID_VIEW_DisplayExtensionOperationTable, &CWndDcdGridOperationTable::OnViewDisplayExtensionOperationTable)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DisplayExtensionOperationTable, &CWndDcdGridOperationTable::OnUpdateViewDisplayExtensionOperationTable)
	ON_COMMAND(ID_VIEW_DisplaySecondEkiJikoku, &CWndDcdGridOperationTable::OnViewDisplaySecondEkijikoku)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DisplaySecondEkiJikoku, &CWndDcdGridOperationTable::OnUpdateViewDisplaySecondEkijikoku)
	ON_COMMAND(ID_VIEW_DisplayColonEkiJikoku, &CWndDcdGridOperationTable::OnViewDisplayColonEkijikoku)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DisplayColonEkiJikoku, &CWndDcdGridOperationTable::OnUpdateViewDisplayColonEkijikoku)
	ON_COMMAND(ID_VIEW_DisplayParentSyubetsu, &CWndDcdGridOperationTable::OnViewDisplayParentSyubetsu)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DisplayParentSyubetsu, &CWndDcdGridOperationTable::OnUpdateViewDisplayParentSyubetsu)
	ON_COMMAND(ID_VIEW_DisplayNoboriLeftToRight, &CWndDcdGridOperationTable::OnViewDisplayNoboriLeftToRight)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DisplayNoboriLeftToRight, &CWndDcdGridOperationTable::OnUpdateViewDisplayNoboriLeftToRight)
	ON_COMMAND(ID_VIEW_DisplayTrackName, &CWndDcdGridOperationTable::OnViewDisplayTrackName)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DisplayTrackName, &CWndDcdGridOperationTable::OnUpdateViewDisplayTrackName)
	ON_COMMAND(ID_VIEW_DisplayTsuukaEkiJikoku, OnViewDisplayTsuukaEkiJikoku)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DisplayTsuukaEkiJikoku, OnUpdateViewDisplayTsuukaEkiJikoku)
	ON_COMMAND(ID_FILE_EXPORT_OPERATIONTABLECSV, &CWndDcdGridOperationTable::OnFileExportOperationtablecsv)
END_MESSAGE_MAP()

int CWndDcdGridOperationTable::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (super::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	//// --------------------------------
	////	列車種別ビューに使用するフォント
	//// --------------------------------
	//CdFontProp fontpropDefault = createFontProp() ;

	//CdOperationTableXColSpecCont aXColSpecCont = createXColSpecCont();
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




void CWndDcdGridOperationTable::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
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
		getCDiagramEditApp()->readCWndDcdGridOperationTableViewProp(this);
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
		//SearchOperationNumberRessya();

		CdDedDispProp aCdDedDispProp =
			getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
		m_iSecondRoundChaku = aCdDedDispProp.getSecondRoundChaku();
		m_iSecondRoundHatsu = aCdDedDispProp.getSecondRoundHatsu();
		m_bDisplay2400 = aCdDedDispProp.getDisplay2400();

		COperationTableDoc* pCOperationTableDoc = (COperationTableDoc*)GetDocument();

		tstring strOperationNumber = pCOperationTableDoc->getOperationNumber();
		//const unordered_map<tstring, list<OperationTableContent>>& MapListOperationTableContent =
		//	getCentDedDia()->getcontOperationTableContent();
		//list<OperationTableContent> ListOperationTableContent = MapListOperationTableContent.at(strOperationNumber);
		//m_ListOperationTableContent = &ListOperationTableContent;
		if (getCentDedDia()->getcontOperationTableContent().find(strOperationNumber) !=
			getCentDedDia()->getcontOperationTableContent().end())
		{
			m_ListOperationTableContent =
				&getCentDedDia()->getcontOperationTableContent().at(strOperationNumber);

			m_contOperationTable.clear();

			bool bIsContinue = false;
			for (auto itr = m_ListOperationTableContent->begin();
				itr != m_ListOperationTableContent->end(); itr++)
			{
				//前列車から受け取ったbIsContinueも書き込みます。書き込み後はbIsContinueをfalseに戻します。
				OperationTable aOperationTable(itr->aRessyaProperty.getRessyahoukou(), bIsContinue);
				bIsContinue = false;
				if (itr->eAfterType == EBeforeAfterType::BeforeAfterType_PropertySame)
				{
					int iSihatsuEkiIndex = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
						->getCentDedEkiCont()->EkiIndexOfEkiOrder(itr->aRessyaProperty.getRessyahoukou(),
							itr->iSihatsuEkiOrder);
					int iSyuuchakuEkiIndex = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
						->getCentDedEkiCont()->EkiIndexOfEkiOrder(itr->aRessyaProperty.getRessyahoukou(),
							itr->iSyuuchakuEkiOrder);
					ERessyahoukou eSihatsuRessyahoukou = itr->aRessyaProperty.getRessyahoukou();
					auto itrNext = itr;
					do {
						itrNext++;
						if (itrNext == m_ListOperationTableContent->end() ||
							itrNext->eBeforeType != EBeforeAfterType::BeforeAfterType_PropertySame)
						{
							//次の列車が末尾を超えた場合、もしくは
							//次の列車の前タイプが同一列車扱い以外なら、一体化は無効その前の列車で終了します。
							//1列車目の列車方向と、最後の列車の列車方向が同じ場合は、1列車目の列車方向をそのまま用いる。
							if (aOperationTable.eRessyahoukou != itrNext->aRessyaProperty.getRessyahoukou() &&
								iSihatsuEkiIndex > iSyuuchakuEkiIndex)
							{
								aOperationTable.eRessyahoukou = ERessyahoukou::Ressyahoukou_Nobori;
							}
							else if (aOperationTable.eRessyahoukou != itrNext->aRessyaProperty.getRessyahoukou() &&
								iSihatsuEkiIndex < iSyuuchakuEkiIndex)
							{
								aOperationTable.eRessyahoukou = ERessyahoukou::Ressyahoukou_Kudari;
							}
							m_contOperationTable.push_back(aOperationTable);
							break;
						}
						else/* if (itrNext->eBeforeType == EBeforeAfterType::BeforeAfterType_PropertySame)*/
						{
							//箱ダイヤの時、前列車と次列車の列車方向が違う、または前列車の終着駅が次列車の始発駅よりも後ろな場合は、
							//行はまとめず、次列車側のbIsContinueをtrueにします。
							if (getDisplayExtensionOperationTable() &&
								(itr->aRessyaProperty.getRessyahoukou() != itrNext->aRessyaProperty.getRessyahoukou() ||
								itr->iSyuuchakuEkiOrder > itrNext->iSihatsuEkiOrder))
							{
								bIsContinue = true;
								//前列車までの分をm_contOperationTableに入れて終了です。
								if (iSihatsuEkiIndex > iSyuuchakuEkiIndex)
								{
									aOperationTable.eRessyahoukou = ERessyahoukou::Ressyahoukou_Nobori;
								}
								else if (iSihatsuEkiIndex < iSyuuchakuEkiIndex)
								{
									aOperationTable.eRessyahoukou = ERessyahoukou::Ressyahoukou_Kudari;
								}
								m_contOperationTable.push_back(aOperationTable);
								break;
							}

							//次の列車の前タイプが同一列車扱いの場合、通常時および箱ダイヤで列車方向一致、終着→始発が駅順の場合は、次の列車は一体化が確定する。

							aOperationTable.iCombineCount++;
							itr++;

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
								//次の列車の後タイプが同一列車扱い以外なら、この列車が一体化の末尾となるので、aOperationTableを確定させる。
								//1列車目の列車方向と、最後の列車の列車方向が同じ場合は、1列車目の列車方向をそのまま用いる。
								if (aOperationTable.eRessyahoukou != itrNext->aRessyaProperty.getRessyahoukou() &&
									iSihatsuEkiIndex > iSyuuchakuEkiIndex)
								{
									aOperationTable.eRessyahoukou = ERessyahoukou::Ressyahoukou_Nobori;
								}
								else if (aOperationTable.eRessyahoukou != itrNext->aRessyaProperty.getRessyahoukou() && 
									iSihatsuEkiIndex < iSyuuchakuEkiIndex)
								{
									aOperationTable.eRessyahoukou = ERessyahoukou::Ressyahoukou_Kudari;
								}
								//一体化の結果、始発駅と終着駅が同じの場合は、1列車目の列車方向をそのまま用いる。
								m_contOperationTable.push_back(aOperationTable);
								break;
							}
						}
					} while (itrNext != m_ListOperationTableContent->end());
				}
				else
				{
					m_contOperationTable.push_back(aOperationTable);
				}
			}

		}
		if ( GetParent() == pView )
		{
			OnUpdate_All() ;
		}
		else
		{
			LogMsg(_T("CWndDcdGridOperationTable::OnUpdate()")
				_T("m_bUpdate_All_Requested=true") ) ;
			m_bUpdate_All_Requested = true ;
		}
	}
	
	int iYColumnBegin = createYColSpecCont().ColumnNumberFromSpec( 
		CdOperationTableYColSpec(CdOperationTableYColSpec::EColumnType::ColumnType_Ressya, 0 ) ) ;

	getCSelect()->setColumnNumberSelectLimit(
		CdDcdZoneXy( 
			CdDcdZone( 0 , INT_MAX ) ,
			CdDcdZone( iYColumnBegin , m_ListOperationTableContent->size()   )
		) );

}

void CWndDcdGridOperationTable::OnEditCopy()
{
	OnEditCopy_Process( FALSE );
}

void CWndDcdGridOperationTable::OnUpdateEditCopy(CCmdUI* pCmdUI)
{
	pCmdUI->Enable( OnEditCopy_Process( TRUE ) >= 0 ) ;
}


void CWndDcdGridOperationTable::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	LogMsg(_T("CWndDcdGridOperationTable::OnActivateView(%d,,)") , bActivate ) ;
	
	if ( bActivate && m_bUpdate_All_Requested )
	{
		OnUpdate_All() ;
	}
}

void CWndDcdGridOperationTable::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CMenu	aMenu ;
	aMenu.LoadMenu( IDR_MENU_OPERATIONTABLE_CONTEXT ) ;
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

void CWndDcdGridOperationTable::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	int iRv = 0;
	iRv = OnOperationtableMovetojikokuhyouOpenDlg_Process(FALSE);
	//if (iRv >= 0)
	//{
	//	if (getCentDedDia()->getWaitOperationUpdate())
	//	{
	//		iRv = -1;	//運用更新抑止状態です
	//	}
	//}
	//CdOperationTableYColSpec aCdOperationTableYColSpec = getYColSpecOfFocus();
	//if (iRv >= 0)
	//{
	//	if (getCSelect()->getSelectedCellCount() == 0)
	//	{
	//		if (aCdOperationTableYColSpec.getColumnType() !=
	//			CdOperationTableYColSpec::ColumnType_Ressya)
	//		{
	//			iRv = -2;	//フォーカスが列車位置以外なら不可
	//		}
	//	}
	//	else
	//	{
	//		iRv = -1; //複数選択は不可
	//	}

	//}
	//if (iRv >= 0)
	//{
	//	ERessyahoukou eRessyahoukou = m_aRessyaProperty[aCdOperationTableYColSpec.getRessyaPropertyIndex()].getRessyahoukou();
	//	int iRessyaidx = m_aRessyaProperty[aCdOperationTableYColSpec.getRessyaPropertyIndex()].getRessyaIndex();
	//	// --------------------------------
	//	//	時刻表ビューを開く
	//	// --------------------------------
	//	CJikokuhyouView* pCJikokuhyouView = NULL;
	//	if (iRv >= 0)
	//	{
	//		CJikokuhyouDoc* pCJikokuhyouDoc = NULL;
	//		if (iRv >= 0)
	//		{
	//			pCJikokuhyouDoc =
	//				getCDiagramEditApp()->openCJikokuhyouDoc(
	//					getCentDedDia(),
	//					eRessyahoukou,
	//					&pCJikokuhyouView);
	//			if (pCJikokuhyouView == NULL)
	//			{
	//				iRv = -3;	//	時刻表ビューのオープンに失敗しました
	//			}
	//		}
	//		//pCJikokuhyouDoc = 時刻表ドキュメント
	//		//pCJikokuhyouView = 時刻表ビュー
	//	}

	//	if (iRv >= 0)
	//	{

	//		CdOperationTableXColSpec aCdOperationTableXColSpec = getXColSpecOfFocus();
	//		if (aCdOperationTableXColSpec.getColumnType() ==
	//			CdOperationTableXColSpec::ColumnType_Ressyabangou)
	//		{
	//			pCJikokuhyouView->openCDlgRessyaProp(iRessyaidx, 1);
	//		}
	//		else if (aCdOperationTableXColSpec.getColumnType() ==
	//			CdOperationTableXColSpec::ColumnType_Ressyasyubetsu)
	//		{
	//			pCJikokuhyouView->openCDlgRessyaProp(iRessyaidx, 2);
	//		}
	//		else if (aCdOperationTableXColSpec.getColumnType() ==
	//			CdOperationTableXColSpec::ColumnType_Ressyamei)
	//		{
	//			pCJikokuhyouView->openCDlgRessyaProp(iRessyaidx, 3);
	//		}
	//		else if (aCdOperationTableXColSpec.getColumnType() ==
	//			CdOperationTableXColSpec::ColumnType_OriginSideEkimei ||
	//			aCdOperationTableXColSpec.getColumnType() ==
	//			CdOperationTableXColSpec::ColumnType_OriginSideEkijikoku)
	//		{
	//			CentDedRessya aCentDedRessya = getCentDedRessyaCont(eRessyahoukou)->get(iRessyaidx);
	//			if (eRessyahoukou == ERessyahoukou::Ressyahoukou_Kudari)
	//			{
	//				pCJikokuhyouView->openCDlgEkijikokuProp(iRessyaidx, aCentDedRessya.getSihatsuEki(),true);
	//			}
	//			else
	//			{
	//				pCJikokuhyouView->openCDlgEkijikokuProp(iRessyaidx, aCentDedRessya.getSyuuchakuEki(), false);
	//			}
	//		}
	//		else if (aCdOperationTableXColSpec.getColumnType() ==
	//			CdOperationTableXColSpec::ColumnType_TerminalSideEkimei ||
	//			aCdOperationTableXColSpec.getColumnType() ==
	//			CdOperationTableXColSpec::ColumnType_TerminalSideEkijikoku)
	//		{
	//			CentDedRessya aCentDedRessya = getCentDedRessyaCont(eRessyahoukou)->get(iRessyaidx);
	//			if (eRessyahoukou == ERessyahoukou::Ressyahoukou_Kudari)
	//			{
	//				pCJikokuhyouView->openCDlgEkijikokuProp(iRessyaidx, aCentDedRessya.getSyuuchakuEki(),false);
	//			}
	//			else
	//			{
	//				pCJikokuhyouView->openCDlgEkijikokuProp(iRessyaidx, aCentDedRessya.getSihatsuEki(), true);
	//			}
	//		}
	//		else
	//		{
	//			CentDedRessya aCentDedRessya = getCentDedRessyaCont(eRessyahoukou)->get(iRessyaidx);
	//			pCJikokuhyouView->setFocusToRessyaIndex(iRessyaidx, aCentDedRessya.getSihatsuEki());
	//		}
	//		iRv = 1;	//	時刻表ビューへ移動しました
	//	}

	//}
}

void CWndDcdGridOperationTable::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	int iRv = 0;

	if (iRv >= 0 && CKeyinputSenderToModalDlg::AnyLetterOrDigitKeyIsDown())
	{

		if (iRv >= 0)
		{
			if (getCentDedDia()->getWaitOperationUpdate())
			{
				iRv = -1;	//運用更新抑止状態です
			}
		}
		CdOperationTableYColSpec aCdOperationTableYColSpec = getYColSpecOfFocus();
		if (iRv >= 0)
		{
			if (getCSelect()->getSelectedCellCount() == 0)
			{
				if (aCdOperationTableYColSpec.getColumnType() !=
					CdOperationTableYColSpec::EColumnType::ColumnType_Ressya)
				{
					iRv = -2;	//フォーカスが列車位置以外なら不可
				}
			}
			else
			{
				iRv = -1; //複数選択は不可
			}
		}

		if (iRv >= 0)
		{
			auto itr = m_ListOperationTableContent->begin();
			for (int idx = 0; idx < aCdOperationTableYColSpec.getOperationTableContentIndex(); idx++)
			{
				itr++;
			}
			ERessyahoukou eRessyahoukou = itr->aRessyaProperty.getRessyahoukou();
			int iRessyaidx = itr->aRessyaProperty.getRessyaIndex();
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
						iRv = -3;	//	時刻表ビューのオープンに失敗しました
					}
				}
				//pCJikokuhyouDoc = 時刻表ドキュメント
				//pCJikokuhyouView = 時刻表ビュー
			}

			if (iRv >= 0)
			{

				CdOperationTableXColSpec aCdOperationTableXColSpec = getXColSpecOfFocus();
				if (aCdOperationTableXColSpec.getColumnType() ==
					CdOperationTableXColSpec::EColumnType::ColumnType_Ressyabangou)
				{
					pCJikokuhyouView->openCDlgRessyaPropKeyDown(iRessyaidx, 1, nChar, nRepCnt, nFlags);
				}
				else if (aCdOperationTableXColSpec.getColumnType() ==
					CdOperationTableXColSpec::EColumnType::ColumnType_Ressyasyubetsu)
				{
					pCJikokuhyouView->openCDlgRessyaPropKeyDown(iRessyaidx, 2, nChar, nRepCnt, nFlags);
				}
				else if (aCdOperationTableXColSpec.getColumnType() ==
					CdOperationTableXColSpec::EColumnType::ColumnType_Ressyamei)
				{
					pCJikokuhyouView->openCDlgRessyaPropKeyDown(iRessyaidx, 3, nChar, nRepCnt, nFlags);
				}
				else if (aCdOperationTableXColSpec.getColumnType() ==
					CdOperationTableXColSpec::EColumnType::ColumnType_OriginSideEkimei ||
					aCdOperationTableXColSpec.getColumnType() ==
					CdOperationTableXColSpec::EColumnType::ColumnType_OriginSideEkiTrack ||
					aCdOperationTableXColSpec.getColumnType() ==
					CdOperationTableXColSpec::EColumnType::ColumnType_OriginSideEkijikoku)
				{
					CentDedRessya aCentDedRessya = getCentDedRessyaCont(eRessyahoukou)->get(iRessyaidx);
					if (eRessyahoukou == ERessyahoukou::Ressyahoukou_Kudari ||
						getDisplayNoboriLeftToRight())
					{
						pCJikokuhyouView->openCDlgEkijikokuPropKeyDown(iRessyaidx, aCentDedRessya.getValidSihatsuEki(), true, nChar, nRepCnt, nFlags);
					}
					else
					{
						pCJikokuhyouView->openCDlgEkijikokuPropKeyDown(iRessyaidx, aCentDedRessya.getValidSyuuchakuEki(), false, nChar, nRepCnt, nFlags);
					}
				}
				else if (aCdOperationTableXColSpec.getColumnType() ==
					CdOperationTableXColSpec::EColumnType::ColumnType_TerminalSideEkimei ||
					aCdOperationTableXColSpec.getColumnType() ==
					CdOperationTableXColSpec::EColumnType::ColumnType_TerminalSideEkiTrack ||
					aCdOperationTableXColSpec.getColumnType() ==
					CdOperationTableXColSpec::EColumnType::ColumnType_TerminalSideEkijikoku)
				{
					CentDedRessya aCentDedRessya = getCentDedRessyaCont(eRessyahoukou)->get(iRessyaidx);
					if (eRessyahoukou == ERessyahoukou::Ressyahoukou_Kudari ||
						getDisplayNoboriLeftToRight())
					{
						pCJikokuhyouView->openCDlgEkijikokuPropKeyDown(iRessyaidx, aCentDedRessya.getValidSyuuchakuEki(), false, nChar, nRepCnt, nFlags);
					}
					else
					{
						pCJikokuhyouView->openCDlgEkijikokuPropKeyDown(iRessyaidx, aCentDedRessya.getValidSihatsuEki(), true, nChar, nRepCnt, nFlags);
					}
				}
				else
				{
					CentDedRessya aCentDedRessya = getCentDedRessyaCont(eRessyahoukou)->get(iRessyaidx);
					pCJikokuhyouView->setFocusToRessyaIndex(iRessyaidx, aCentDedRessya.getValidSihatsuEki());
				}
				iRv = 1;	//	時刻表ビューへ移動しました
			}
		}

	}
	else
	{
		//if (!m_CKeyinputSenderToModalDlg.OnKeyDown(nChar, nRepCnt, nFlags))
		//{
		super::OnKeyDown(nChar, nRepCnt, nFlags);
		//}
	}
}
} //namespace ViewEkiTrack2


void ViewOperationTable::CWndDcdGridOperationTable::OnOperationtableMovetojikokuhyou()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	OnOperationtableMovetojikokuhyou_Process(FALSE);
}


void ViewOperationTable::CWndDcdGridOperationTable::OnUpdateOperationtableMovetojikokuhyou(CCmdUI *pCmdUI)
{
	// TODO:ここにコマンド更新 UI ハンドラー コードを追加します。
	pCmdUI->Enable(OnOperationtableMovetojikokuhyou_Process(TRUE) >= 0);
}


void ViewOperationTable::CWndDcdGridOperationTable::OnOperationtableMovetojikokuhyouOpenDlg()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	OnOperationtableMovetojikokuhyouOpenDlg_Process(FALSE);
}


void ViewOperationTable::CWndDcdGridOperationTable::OnUpdateOperationtableMovetojikokuhyouOpenDlg(CCmdUI *pCmdUI)
{
	// TODO:ここにコマンド更新 UI ハンドラー コードを追加します。
	pCmdUI->Enable(OnOperationtableMovetojikokuhyouOpenDlg_Process(TRUE) >= 0);
}


void ViewOperationTable::CWndDcdGridOperationTable::OnOperationtableMovetodiagram()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	OnOperationtableMovetodiagram_Process(FALSE);
}


void ViewOperationTable::CWndDcdGridOperationTable::OnUpdateOperationtableMovetodiagram(CCmdUI *pCmdUI)
{
	// TODO:ここにコマンド更新 UI ハンドラー コードを追加します。
	pCmdUI->Enable(OnOperationtableMovetodiagram_Process(TRUE) >= 0);
}

void CWndDcdGridOperationTable::OnViewDisplayExtensionOperationTable()
{
	OnViewDisplayExtensionOperationTable_Process(FALSE);
}

void CWndDcdGridOperationTable::OnUpdateViewDisplayExtensionOperationTable(CCmdUI* pCmdUI)
{
	int iResult = OnViewDisplayExtensionOperationTable_Process(TRUE);
	pCmdUI->Enable(iResult >= 0);
	pCmdUI->SetCheck(iResult >= 1);
}

void CWndDcdGridOperationTable::OnViewDisplaySecondEkijikoku()
{
	OnViewDisplaySecondEkijikoku_Process(FALSE);
}

void CWndDcdGridOperationTable::OnUpdateViewDisplaySecondEkijikoku(CCmdUI *pCmdUI)
{
	int iResult = OnViewDisplaySecondEkijikoku_Process(TRUE);
	pCmdUI->Enable(iResult >= 0);
	pCmdUI->SetCheck(iResult >= 1);
}

void CWndDcdGridOperationTable::OnViewDisplayColonEkijikoku()
{
	OnViewDisplayColonEkijikoku_Process(FALSE);
}

void CWndDcdGridOperationTable::OnUpdateViewDisplayColonEkijikoku(CCmdUI *pCmdUI)
{
	int iResult = OnViewDisplayColonEkijikoku_Process(TRUE);
	pCmdUI->Enable(iResult >= 0);
	pCmdUI->SetCheck(iResult >= 1);
}

void CWndDcdGridOperationTable::OnViewDisplayParentSyubetsu()
{
	OnViewDisplayParentSyubetsu_Process(FALSE);
}

void CWndDcdGridOperationTable::OnUpdateViewDisplayParentSyubetsu(CCmdUI *pCmdUI)
{
	int iResult = OnViewDisplayParentSyubetsu_Process(TRUE);
	pCmdUI->Enable(iResult >= 0);
	pCmdUI->SetCheck(iResult >= 1);
}

void CWndDcdGridOperationTable::OnViewDisplayNoboriLeftToRight()
{
	OnViewDisplayNoboriLeftToRight_Process(FALSE);
}

void CWndDcdGridOperationTable::OnUpdateViewDisplayNoboriLeftToRight(CCmdUI* pCmdUI)
{
	int iResult = OnViewDisplayNoboriLeftToRight_Process(TRUE);
	pCmdUI->Enable(iResult >= 0);
	pCmdUI->SetCheck(iResult >= 1);
}

void CWndDcdGridOperationTable::OnViewDisplayTrackName()
{
	OnViewDisplayTrackName_Process(FALSE);
}

void CWndDcdGridOperationTable::OnUpdateViewDisplayTrackName(CCmdUI* pCmdUI)
{
	int iResult = OnViewDisplayTrackName_Process(TRUE);
	pCmdUI->Enable(iResult >= 0);
	pCmdUI->SetCheck(iResult >= 1);
}

void CWndDcdGridOperationTable::OnViewDisplayTsuukaEkiJikoku()
{
	OnViewDisplayTsuukaEkiJikoku_Process(FALSE);
}

void CWndDcdGridOperationTable::OnUpdateViewDisplayTsuukaEkiJikoku(CCmdUI* pCmdUI)
{
	int iResult = OnViewDisplayTsuukaEkiJikoku_Process(TRUE);
	pCmdUI->Enable(iResult >= 0);
	pCmdUI->SetCheck(iResult >= 1);

}



void ViewOperationTable::CWndDcdGridOperationTable::OnFileExportOperationtablecsv()
{
	OnFileExportOperationTableCsv_Process(FALSE);
}
