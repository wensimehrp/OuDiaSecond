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
//	ViewJikokuhyou\WndJikokuhyou\CCellBuilder.cpp
//	$Id: CCellBuilder.cpp 366 2016-08-18 20:26:22Z okm $
// ****************************************************************
*/
/** @file */
#include "stdafx.h"
//#include "..\..\StdAfx.h"
#include "CCellBuilder.h"
#include "..\..\resource.h"
#include "DcDraw\DcDraw.h"
#include "NsOu/dynamic_castOu.h"
#include "..\..\entDed\entDed.h"
#include "str\stringSplit.h"
#include "MfcUtil/MfcUtil.h"
#include "NsOu\OuNew.h"
#include "Str/strToWstr.h"
//#include "DcdGrid/WndDcdGrid3/WndDcdGrid3.h"
//#include "DcdGrid/CDcdGrid.h"
//#include "DcdGrid/CDcdGridXBorder.h"

namespace ViewJikokuhyou{
namespace WndJikokuhyou{
	//using namespace OuLib::Str;
	//using DcDraw::CDcdTextboxV3 ;

// --------------------------------
//@name 描画処理に使用する テキスト描画属性
// --------------------------------

CdDrawTextProp	CCellBuilder::getCdDrawTextPropMenutext()const
{ 
	CdDedDispProp aCdDedDispProp = m_pCDedRosenFileData->getCdDedDispProp() ;

	CConverter_WinGdi	aConv ;
	return CdDrawTextProp( 
		aCdDedDispProp.getJikokuhyouFont(0) ,
		aConv.CdColorPropOfSysColor( COLOR_MENUTEXT ) ) ;
}

CdDrawTextProp	CCellBuilder::getCdDrawTextPropStandard()const
{ 
	CdDedDispProp aCdDedDispProp = m_pCDedRosenFileData->getCdDedDispProp() ;

	return CdDrawTextProp( 
		aCdDedDispProp.getJikokuhyouFont(0) ,
		CdColorProp( 0 , 0 , 0 ) ) ;
}

CdDrawTextProp	CCellBuilder::getCdDrawTextPropOperation()const
{
	CdDedDispProp aCdDedDispProp = m_pCDedRosenFileData->getCdDedDispProp();

	return CdDrawTextProp(
		aCdDedDispProp.getJikokuhyouFont(0),
		CdColorProp(0, 0, 0),
		CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
}

CdDrawTextProp	CCellBuilder::getCdDrawTextPropTsuuka()const
{ 
	CdDedDispProp aCdDedDispProp = m_pCDedRosenFileData->getCdDedDispProp() ;

	return CdDrawTextProp( 
		aCdDedDispProp.getJikokuhyouFont(0) ,
		CdColorProp( 128 , 128 , 128 ) ,
		CdDrawTextFormat( CdDrawTextFormat::H_CENTER ) ) ;
}

//edit_by_d_mania
const CdDedJikoku::CConv	
CCellBuilder::getCdDedJikokuConv()const 
{
	//if( m_bDisplaySecondEkiJikoku )
	//{
	//	if (m_bDisplayColonEkiJikoku)
	//	{
	//		static CdDedJikoku::CConv aConv(
	//			false,		//	コロン有
	//											// 時が 00 から 09 の場合、10の位の "0" をスペースにします。
	//			CdDedJikoku::CConv::EHour_ZeroToSpace,
	//			CdDedJikoku::CConv::ESecond_Output, 	// 秒を表示します
	//			(CdDedJikoku::CConv::ESecondRound)m_iSecondRoundChaku,
	//			(CdDedJikoku::CConv::ESecondRound)m_iSecondRoundHatsu,
	//			m_bDisplay2400
	//		);
	//		return aConv;
	//	}
	//	else
	//	{
	//		static CdDedJikoku::CConv aConv(
	//			true,		//	コロン無
	//											// 時が 00 から 09 の場合、10の位の "0" をスペースにします。
	//			CdDedJikoku::CConv::EHour_ZeroToSpace,
	//			CdDedJikoku::CConv::ESecond_Output, 	// 秒を表示します
	//			(CdDedJikoku::CConv::ESecondRound)m_iSecondRoundChaku,
	//			(CdDedJikoku::CConv::ESecondRound)m_iSecondRoundHatsu,
	//			m_bDisplay2400
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
	//			CdDedJikoku::CConv::ESecond_NoSecond, 	// 秒を常に出力しません。
	//			(CdDedJikoku::CConv::ESecondRound)m_iSecondRoundChaku,
	//			(CdDedJikoku::CConv::ESecondRound)m_iSecondRoundHatsu,
	//			m_bDisplay2400
	//		);
	//		return aConv;
	//	}
	//	else
	//	{
	//		static CdDedJikoku::CConv aConv(
	//			true,		//	コロン無
	//						// 時が 00 から 09 の場合、10の位の "0" をスペースにします。
	//			CdDedJikoku::CConv::EHour_ZeroToSpace,
	//			CdDedJikoku::CConv::ESecond_NoSecond, 	// 秒を常に出力しません。
	//			(CdDedJikoku::CConv::ESecondRound)m_iSecondRoundChaku,
	//			(CdDedJikoku::CConv::ESecondRound)m_iSecondRoundHatsu,
	//			m_bDisplay2400
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
	// --------------------------------
	//@name 描画処理に使用する ブラシ属性
	// --------------------------------

CdBrushProp CCellBuilder::getCdBrushPropMenutext()const
{
	CConverter_WinGdi	aConv ;
	return CdBrushProp( aConv.CdColorPropOfSysColor( COLOR_MENU ) ) ;
}

CdBrushProp	CCellBuilder::getCdBrushPropStandard()const
{
	return CdBrushProp( CdColorProp( 255 , 255 , 255 ) ) ;
}

	// --------------------------------
	//@name 描画処理に使用する DcDrawオブジェクトのプロトタイプ
	// --------------------------------

CDcdTextbox CCellBuilder::createCDcdXColumn0()const
{
	tstring strExtent = m_pCDedRosenFileData->
		getCdDedDispProp().createEkimeiExtentString() ;
	//strExtent = 路線ファイルデータに保存されている値をもとにして、
	//	作成した、文字列幅の基準文字列です。

	CDcdTextbox aCDcd( 
		_T("") ,
		getCdDrawTextPropMenutext() ,
		strExtent ,
		1 ,
		RectangleTextFrameWidth , RectangleTextFrameWidth ,
		CdPenProp() ,
		getCdBrushPropMenutext() 
	) ;
	return ( aCDcd ) ;
}

CDcdTextboxV3 CCellBuilder::createCDcdXColumn0V()const
{
	tstring strExtent = m_pCDedRosenFileData->
		getCdDedDispProp().createEkimeiExtentString() ;
	//strExtent = 路線ファイルデータに保存されている値をもとにして、
	//	作成した、文字列幅の基準文字列です。

	CdDedDispProp	aCdDedDispProp = m_pCDedRosenFileData->getCdDedDispProp() ;

	CConverter_WinGdi	aConv ;

	CDcdTextboxV3 aCDcd( 
		_T("") ,
		aCdDedDispProp.getJikokuhyouVFont() ,
		getRessyameiTextExtent().getX() ,
		getRessyameiTextExtent().getY() ,
		aConv.CdColorPropOfSysColor( COLOR_MENUTEXT ) ,
		RectangleTextFrameWidth , RectangleTextFrameWidth ,
		CdPenProp() ,
		getCdBrushPropMenutext() ) ;
	return ( aCDcd ) ;
}


CDcdTextbox CCellBuilder::createCDcdEkimei()const
{
	tstring strExtent = m_pCDedRosenFileData->
		getCdDedDispProp().createEkimeiExtentString() ;
	//strExtent = 路線ファイルデータに保存されている値をもとにして、
	//	作成した、文字列幅の基準文字列です。

	CDcdTextbox aCDcd( 
		_T("") ,
		getCdDrawTextPropStandard() ,
		strExtent ,
		1 ,
		RectangleTextFrameWidth , RectangleTextFrameWidth ,
		CdPenProp() ,
		getCdBrushPropStandard() ) ;
	return ( aCDcd ) ;
}


CDcdTextbox CCellBuilder::createCDcdHatsuchaku()const
{
	tstring strExtent;
	//if (m_bDisplayAllTrack) 
	//{
		strExtent = MfcUtil::LoadCString(IDS_WORD_Track);
	//}
	//else 
	//{
	//	strExtent = MfcUtil::LoadCString( IDS_WORD_Chaku );
	//}

	//strExtent = 路線ファイルデータに保存されている値をもとにして、
	//	作成した、文字列幅の基準文字列です。


	CDcdTextbox aCDcd( 
		_T("") ,
		getCdDrawTextPropStandard() ,
		strExtent ,
		1 ,
		RectangleTextFrameWidth , RectangleTextFrameWidth ,
		CdPenProp() ,
		getCdBrushPropStandard() ) ;
	return ( aCDcd ) ;
}

CDcdTextbox CCellBuilder::createCDcdRessyabangou(
	int iRessyasyubetsuIndex )const
{
	CdDedDispProp	aCdDedDispProp = m_pCDedRosenFileData->getCdDedDispProp() ;
	tstring strCellExtent( aCdDedDispProp.getJikokuhyouRessyaWidth() , '0' ) ;
	//strCellExtent = セルの大きさの目安となる文字列です。
	//	時刻表列車セルの幅(文字数) CdDedDispProp::m_iJikokuhyouRessyaWidth
	//	の数だけ '0' が並んだ文字列です

	const CentDedRessyasyubetsu* pCentDedRessyasyubetsu
		= m_pCDedRosenFileData->getCentDedRosen()->getCentDedRessyasyubetsuCont()
		->getMuPtr()->get( iRessyasyubetsuIndex ) ;
	if (m_bDisplayParentSyubetsu && pCentDedRessyasyubetsu->getParentSyubetsuIndex() >= 0)
	{
		pCentDedRessyasyubetsu
			= m_pCDedRosenFileData->getCentDedRosen()->getCentDedRessyasyubetsuCont()
			->getMuPtr()->get(pCentDedRessyasyubetsu->getParentSyubetsuIndex());
	}

	CdDrawTextProp aCdDrawTextProp = getCdDrawTextPropStandard() ;

	aCdDrawTextProp.setCdDrawTextFormat( CdDrawTextFormat( CdDrawTextFormat::H_CENTER ) ) ;
	aCdDrawTextProp.setTextColor( 
		pCentDedRessyasyubetsu->getJikokuhyouMojiColor() ) ;


	CDcdTextbox aCDcd( 
		_T("") ,
		aCdDrawTextProp ,
		strCellExtent ,
		1 ,
		RectangleTextFrameWidth , RectangleTextFrameWidth ,
		CdPenProp() ,
		getCdBrushPropStandard() ) ;
	return ( aCDcd ) ;
}

CDcdTextboxV3 CCellBuilder::createCDcdRessyamei(
	int iRessyasyubetsuIndex )const
{
	const CentDedRessyasyubetsu* pCentDedRessyasyubetsu
		= m_pCDedRosenFileData->getCentDedRosen()->getCentDedRessyasyubetsuCont()
		->getMuPtr()->get( iRessyasyubetsuIndex ) ;
	if (m_bDisplayParentSyubetsu && pCentDedRessyasyubetsu->getParentSyubetsuIndex() >= 0)
	{
		pCentDedRessyasyubetsu
			= m_pCDedRosenFileData->getCentDedRosen()->getCentDedRessyasyubetsuCont()
			->getMuPtr()->get(pCentDedRessyasyubetsu->getParentSyubetsuIndex());
	}

	CdDedDispProp	aCdDedDispProp = m_pCDedRosenFileData->getCdDedDispProp() ;

	CDcdTextboxV3 aCDcd( 
		_T("") ,
		aCdDedDispProp.getJikokuhyouVFont(),
		getRessyameiTextExtent().getX() ,
		getRessyameiTextExtent().getY() ,
		pCentDedRessyasyubetsu->getJikokuhyouMojiColor() ,
		RectangleTextFrameWidth , RectangleTextFrameWidth ,
		CdPenProp() ,
		getCdBrushPropStandard() ) ;
	return ( aCDcd ) ;
}

CDcdTextbox CCellBuilder::createCDcdEkijikoku(
	int iRessyasyubetsuIndex,
	CentDedEkiJikoku::EEkiatsukai eEkiatsukai)const
{
	const CentDedRessyasyubetsu* pCentDedRessyasyubetsu
		= m_pCDedRosenFileData->getCentDedRosen()->getCentDedRessyasyubetsuCont()
		->getMuPtr()->get( iRessyasyubetsuIndex ) ;
	if (m_bDisplayParentSyubetsu && pCentDedRessyasyubetsu->getParentSyubetsuIndex() >= 0)
	{
		pCentDedRessyasyubetsu
			= m_pCDedRosenFileData->getCentDedRosen()->getCentDedRessyasyubetsuCont()
			->getMuPtr()->get(pCentDedRessyasyubetsu->getParentSyubetsuIndex());
	}
	int idxFont = pCentDedRessyasyubetsu->getJikokuhyouFontIndex() ;
	

	CDcdTextbox aCDcd 
		= createCDcdRessyabangou( iRessyasyubetsuIndex ) ;
		
	CdDrawTextProp	aCdDrawTextProp = aCDcd.getCdDrawTextProp() ;
	if (eEkiatsukai == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya ||
		m_bDisplayTsuukaFontPerSyubetsu)
	{
		aCdDrawTextProp.setCdFontProp(
			m_pCDedRosenFileData
			->getCdDedDispProp().getJikokuhyouFont(idxFont));
	}

	if (eEkiatsukai == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
	{
		aCdDrawTextProp.setTextColor(CdColorProp(128, 128, 128));
	}
	aCDcd.setCdDrawTextProp( aCdDrawTextProp ) ;

	return ( aCDcd ) ;
}

	// --------------------------------
	//@name update() の下請関数
	// --------------------------------
void CCellBuilder::update01_updateWithoutRessya(
		CWndJikokuhyou* pCWndJikokuhyou ) 
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid() ;
	CDcdTargetGetDC	aCDcdTarget( NULL ) ;

	// ********************************
	//(1.1)　CWndDcdGrid の外枠線のDcDrawオブジェクトと、列幅を設定
	// ********************************
	update01_01_setGridBorder( 
		pCWndJikokuhyou ) ;


	// ********************************
	//(1.2)　列の数を設定します。
	//	X列数が2未満なら2にします。
	//	Y列数は、CdYColSpecCont で
	//	導出された列数とします。
	// ********************************
	{
		int iXColumnNumberMax = -1 ;
		{
			int iXColumnNumber = m_CdXColSpecCont.ColumnNumberFromSpec( 
				CdXColSpec( 
					CdXColSpec::ColumnType_Ekimei ) ) ;
			iXColumnNumberMax = max( iXColumnNumberMax , iXColumnNumber ) ;
		}
		{
			int iXColumnNumber = m_CdXColSpecCont.ColumnNumberFromSpec( 
				CdXColSpec( 
					CdXColSpec::ColumnType_Chakuhatsu ) ) ;
			iXColumnNumberMax = max( iXColumnNumberMax , iXColumnNumber ) ;
		}

		pCDcdGrid->setXColumnCount( max( iXColumnNumberMax + 1 , 
			pCDcdGrid->getXColumnCount() ) ) ;
		pCDcdGrid->setYColumnCount( m_CdYColSpecCont.size() ) ;
	}
 
	// ********************************
	//(1.3)　X列(ColumnType_Ekimei) の各セルと、すべてのY列の高さ・
	//	Y列境界線・Y列境界線の高さ設定
	// ********************************
	{
		CdXColSpec aCdXColSpec( 
			CdXColSpec::ColumnType_Ekimei ) ;
		int iXColumnNumber = 
			m_CdXColSpecCont.ColumnNumberFromSpec( aCdXColSpec ) ;

		// ================================
		//(1.3.1)　セル(ColumnType_Ekimei,ColumnType_Ressyabangou) と、
		//	Y列(ColumnType_Ressyabangou)の高さ・Y列境界線・Y列境界線の高さ設定
		// ================================
		update01_03_01_setEkimei_Ressyabangou( 
			pCWndJikokuhyou ) ;

		// ================================
		//	(1.3.2)　同様に、セル(ColumnType_Ekimei, 
		//	ColumnType_Ressyasyubetsu～ ColumnType_Bikou ) と、
		//	Y列(ColumnType_Ressyasyubetsu～ ColumnType_Bikou)の高さ・
		//	Y列境界線・Y列境界線の高さを設定。
		// ================================
		// --------------------------------
		//	(1.3.2.12)セル(ColumnType_Ekimei, ColumnType_OperationNumber)
		// --------------------------------
		update01_03_02_12_setEkimei_OperationNumber(
			pCWndJikokuhyou);

		// --------------------------------
		//	(1.3.2.2)セル(ColumnType_Ekimei, ColumnType_Ressyasyubetsu)
		// --------------------------------
		update01_03_02_02_setEkimei_Ressyasyubetsu( 
			pCWndJikokuhyou ) ;

		// --------------------------------
		//	(1.3.2.3)セル(ColumnType_Ekimei, ColumnType_Ressyamei)
		// --------------------------------
		update01_03_02_03_setEkimei_Ressyamei( 
			pCWndJikokuhyou ) ;


		// --------------------------------
		//	(1.3.2.4)セル(ColumnType_Ekimei, ColumnType_Gousuu)
		// --------------------------------
		update01_03_02_04_setEkimei_Gousuu( 
			pCWndJikokuhyou ) ;

		
		// --------------------------------
		//	(1.3.2.5)セル(ColumnType_Ekimei, ColumnType_Gou)
		// --------------------------------
		update01_03_02_05_setEkimei_Gou( 
			pCWndJikokuhyou ) ;

		// --------------------------------
		//	(1.3.2.10)セル(ColumnType_Ekimei, ColumnType_Operation_Shihatsu)
		// --------------------------------
		update01_03_02_13_setShihatsuEkimei(
			pCWndJikokuhyou);

		// --------------------------------
		//	(1.3.2.10)セル(ColumnType_Ekimei, ColumnType_Operation_Shihatsu)
		// --------------------------------
		update01_03_02_10_setEkimei_Operation_Shihatsu(
			pCWndJikokuhyou);

		// --------------------------------
		//	(1.3.2.10)セル(ColumnType_Ekimei, ColumnType_Operation_Shuchaku)
		// --------------------------------
		update01_03_02_14_setShuchakuEkimei(
			pCWndJikokuhyou);

		// --------------------------------
		//	(1.3.2.10)セル(ColumnType_Ekimei, ColumnType_Operation_Shuchaku)
		// --------------------------------
		update01_03_02_11_setEkimei_Operation_Shuchaku(
			pCWndJikokuhyou);

		// --------------------------------
		//	(1.3.2.15)セル(ColumnType_Ekimei, ColumnType_Outer_Shihatsu)
		// --------------------------------
		update01_03_02_15_setEkimei_OuterTerminal_Shihatsu(
			pCWndJikokuhyou);
		
		// --------------------------------
		//	セル(ColumnType_Ekimei,ColumnType_Ekijikoku_Chaku)
		//	セル(ColumnType_Ekimei,ColumnType_Track)
		//	セル(ColumnType_Ekimei,ColumnType_Ekijikoku_Hatsu)
		// --------------------------------
		update01_03_02_06_setEkimei_Chaku( 
			pCWndJikokuhyou ) ;
		update01_03_02_09_setEkimei_Track(
			pCWndJikokuhyou);
		update01_03_02_07_setEkimei_Hatsu( 
			pCWndJikokuhyou ) ;

		//if (m_bDisplayAllTrack)
		//{
			update01_03_02_17_setEkimei_BeforeOperation(
				pCWndJikokuhyou);
			update01_03_02_18_setEkimei_AfterOperation(
				pCWndJikokuhyou);

			update01_03_02_19_setEkimei_BeforeOperationBefore(
				pCWndJikokuhyou);
			update01_03_02_20_setEkimei_BeforeOperationAfter(
				pCWndJikokuhyou);
			update01_03_02_21_setEkimei_AfterOperationBefore(
				pCWndJikokuhyou);
			update01_03_02_22_setEkimei_AfterOperationAfter(
				pCWndJikokuhyou);
		//}


		// --------------------------------
		//	(1.3.2.16)セル(ColumnType_Ekimei, ColumnType_Outer_Shuchaku)
		// --------------------------------
		update01_03_02_16_setEkimei_OuterTerminal_Shuchaku(
			pCWndJikokuhyou);

		// --------------------------------
		//	(1.3.2.8)セル(ColumnType_Ekimei,ColumnType_Bikou)
		// --------------------------------
		update01_03_02_08_setEkimei_Bikou( 
			pCWndJikokuhyou ) ;
		
		// ================================
		//(1.3.3)　X列(ColumnType_Ekimei ) の幅を設定。
		//	幅は、駅名列の DcDraw オブジェクトの幅とします。
		// ================================
		CDcdGridXColumn* pCDcdGridXColumn = pCDcdGrid->getXColumn( 
			iXColumnNumber ) ;
		if ( pCDcdGridXColumn )
		{
			CDcdTextbox aCDcdTextbox =createCDcdXColumn0() ;
			CdDcdSizeXy aCdDcdSizeXy ;
			if ( aCDcdTextbox.getItemSize( 
				&aCDcdTarget , &aCdDcdSizeXy ) )
			{
				pCDcdGridXColumn->setColumnSize( aCdDcdSizeXy.getX() ) ;
			}
		}
		// ================================
		//	(1.3.4)　X列(ColumnType_Ekimei ) の境界線の DcDrawオブジェクトの
		//	属性を設定。
		//	(1.3.5)　X列(ColumnType_Ekimei ) の境界線の幅を設定。
		// ================================
		{
			CDcdGridXBorder* pCDcdGridXBorder 
				= pCDcdGridXColumn->getCDcdGridXBorder() ;
			Ou<CDcdLine> pCDcdLine = pCDcdGridXBorder->getIfDcDraw() ;

			pCDcdLine->setCdPenProp( CdPenProp() ) ;	//NULLPEN

			CdDcdSizeXy aCdDcdSizeXy ;
			if ( pCDcdLine->getItemSize( &aCDcdTarget , &aCdDcdSizeXy ) )
			{
				pCDcdGridXBorder->setColumnBorderSize( aCdDcdSizeXy.getX() ) ;
			}
		}
	}

	// ********************************
	//(1.4)　X列(ColumnType_Chakuhatsu) の各セルを設定
	// ********************************
	{
		CdXColSpec aCdXColSpec( 
			CdXColSpec::ColumnType_Chakuhatsu ) ;
		int iXColumnNumber = 
			m_CdXColSpecCont.ColumnNumberFromSpec( aCdXColSpec ) ;
		// ================================
		//(1.4.1)　セル(ColumnType_Chakuhatsu, 
		//	ColumnType_Ekijikoku_Chaku～ ColumnType_Ekijikoku_Hatsu) を設定。
		// ================================
		update01_04_01_06_setChakuhatsu_Chaku( 
			pCWndJikokuhyou ) ;
		update01_04_01_09_setChakuhatsu_Track(
			pCWndJikokuhyou);
		update01_04_01_07_setChakuhatsu_Hatsu( 
			pCWndJikokuhyou ) ;

		update01_04_01_17_setChakuhatsu_BeforeOperation(
			pCWndJikokuhyou);
		update01_04_01_18_setChakuhatsu_AfterOperation(
			pCWndJikokuhyou);

		update01_04_01_19_setChakuhatsu_BeforeOperationBefore(
			pCWndJikokuhyou);
		update01_04_01_20_setChakuhatsu_BeforeOperationAfter(
			pCWndJikokuhyou);
		update01_04_01_21_setChakuhatsu_AfterOperationBefore(
			pCWndJikokuhyou);
		update01_04_01_22_setChakuhatsu_AfterOperationAfter(
			pCWndJikokuhyou);
		// ================================
		//	(1.4.3)　X列(ColumnType_Chakuhatsu ) の幅を設定。
		//	幅は、着発列の DcDraw オブジェクトの幅とします。
		// ================================
		CDcdGridXColumn* pCDcdGridXColumn = pCDcdGrid->getXColumn( 
			iXColumnNumber ) ;
		if ( pCDcdGridXColumn )
		{
			CDcdTextbox aCDcdTextbox = 
				createCDcdHatsuchaku() ;
			CdDcdSizeXy aCdDcdSizeXy ;
			if ( aCDcdTextbox.getItemSize( 
				&aCDcdTarget , &aCdDcdSizeXy ) )
			{
				pCDcdGridXColumn->setColumnSize( aCdDcdSizeXy.getX() ) ;
			}
		}

		// ================================
		//	(1.4.4)　X列(ColumnType_Chakuhatsu ) の境界線の 
		//	DcDrawオブジェクトの属性を設定。
		//(1.4.5)　X列(ColumnType_Chakuhatsu ) の境界線の幅を設定。
		// ================================
		{
			CDcdGridXBorder* pCDcdGridXBorder 
				= pCDcdGridXColumn->getCDcdGridXBorder() ;
			Ou<CDcdLine> pCDcdLine = pCDcdGridXBorder->getIfDcDraw() ;

			pCDcdLine->setCdPenProp( getCdPenPropBoldLine() ) ;	

			CdDcdSizeXy aCdDcdSizeXy ;
			if ( pCDcdLine->getItemSize( &aCDcdTarget , &aCdDcdSizeXy ) )
			{
				pCDcdGridXBorder->setColumnBorderSize( aCdDcdSizeXy.getX() ) ;
			}
		}
	}
}

void CCellBuilder::update01_01_setGridBorder( 
	CWndJikokuhyou* pCWndJikokuhyou ) 
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid() ;
	CDcdTargetGetDC	aCDcdTarget( NULL ) ;


	//	左
	{
		CDcdGridXBorder* pCDcdGridXBorder = pCDcdGrid->getCDcdGridXBorderTop() ;
		Ou<CDcdLine> pCDcdLine = pCDcdGridXBorder->getIfDcDraw();
		pCDcdLine->setCdPenProp( getCdPenPropBoldLine() ) ;

		CdDcdSizeXy aCdDcdSizeXy ;
		if ( pCDcdLine->getItemSize( &aCDcdTarget , &aCdDcdSizeXy ) )
		{
			pCDcdGridXBorder->setColumnBorderSize( aCdDcdSizeXy.getX() ) ;
		}
	}
	//	右
	{
		CDcdGridXBorder* pCDcdGridXBorder 
			= pCDcdGrid->getCDcdGridXBorderBottom() ;
		Ou<CDcdLine> pCDcdLine = pCDcdGridXBorder->getIfDcDraw();
		pCDcdLine->setCdPenProp( getCdPenPropBoldLine() ) ;

		CdDcdSizeXy aCdDcdSizeXy ;
		if ( pCDcdLine->getItemSize( &aCDcdTarget , &aCdDcdSizeXy ) )
		{
			pCDcdGridXBorder->setColumnBorderSize( aCdDcdSizeXy.getX() ) ;
		}
	}
	//	上
	{
		CDcdGridYBorder* pCDcdGridYBorder = pCDcdGrid->getCDcdGridYBorderTop() ;
		Ou<CDcdLine> pCDcdLine = pCDcdGridYBorder->getIfDcDraw();
		pCDcdLine->setCdPenProp( getCdPenPropBoldLine() ) ;

		CdDcdSizeXy aCdDcdSizeXy ;
		if ( pCDcdLine->getItemSize( &aCDcdTarget , &aCdDcdSizeXy ) )
		{
			pCDcdGridYBorder->setColumnBorderSize( aCdDcdSizeXy.getY() ) ;
		}
	}
	//	下
	{
		CDcdGridYBorder* pCDcdGridYBorder 
			= pCDcdGrid->getCDcdGridYBorderBottom() ;
		Ou<CDcdLine> pCDcdLine = pCDcdGridYBorder->getIfDcDraw();
		pCDcdLine->setCdPenProp( getCdPenPropBoldLine() ) ;

		CdDcdSizeXy aCdDcdSizeXy ;
		if ( pCDcdLine->getItemSize( &aCDcdTarget , &aCdDcdSizeXy ) )
		{
			pCDcdGridYBorder->setColumnBorderSize( aCdDcdSizeXy.getY() ) ;
		}
	}
}

void CCellBuilder::update01_03_01_setEkimei_Ressyabangou( 
	CWndJikokuhyou* pCWndJikokuhyou ) 
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid() ;
	CDcdTargetGetDC	aCDcdTarget( NULL ) ;

	// --------------------------------
	CdXColSpec aCdXColSpec( 
		CdXColSpec::ColumnType_Ekimei ) ;
	int iXColumnNumber = 
		m_CdXColSpecCont.ColumnNumberFromSpec( aCdXColSpec ) ;

	if ( iXColumnNumber >= 0 )
	{
		CdYColSpec aCdYColSpec( 
			CdYColSpec::ColumnType_Ressyabangou ) ;
		int iYColumnNumber = m_CdYColSpecCont.ColumnNumberFromSpec( 
			aCdYColSpec , false ) ;
		CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell( 
			iXColumnNumber , iYColumnNumber ) ;

		typedef CDcdTextbox CDcDrawCell ;
		Ou<CDcDrawCell> pCDcDrawCell ;

		if ( pCDcdGridCell != 0 )
		{
			//(1.3.*.1)　セル(ColumnType_Ekimei,ColumnType_Ressyabangou) 
			//	の結合セルの属性を設定。
			pCDcdGridCell->setAttachCellCount( 2 , 1 ) ;

			//	(1.3.*.2)　セル(ColumnType_Ekimei,ColumnType_Ressyabangou) 
			//	のDcDrawオブジェクトの型を設定
			//	( CDcdTextbox とする)。
			{
				pCDcDrawCell = dynamic_castOu<CDcDrawCell>( 
					pCDcdGridCell->getIfDcDraw() ) ;
				if ( pCDcDrawCell == NULL )
				{
					pCDcDrawCell = OuNew<CDcDrawCell>( new CDcDrawCell ) ;
					pCDcdGridCell->setIfDcDraw( pCDcDrawCell ) ;
				}
			}

			//(1.3.*.3)　セル(ColumnType_Ekimei,ColumnType_Ressyabangou) 
			//	DcDrawオブジェクトに、属性を設定。
			{
				*pCDcDrawCell = createCDcdXColumn0() ;
				pCDcDrawCell->setText( tstringOf( 
					(LPCTSTR)MfcUtil::LoadCString( 
						IDS_WORD_Ressyabangou ) ) ) ;
			}
		}

		CDcdGridYColumn* pCDcdGridYColumn = pCDcdGrid->getYColumn( 
			iYColumnNumber ) ;
		if ( pCDcdGridYColumn )
		{
			//(1.3.*.4)　Y列(ColumnType_Ressyabangou) のセルの高さを設定
			{
				CdDcdSizeXy aCdDcdSizeXy ;
				if ( pCDcDrawCell->getItemSize( 
					&aCDcdTarget , &aCdDcdSizeXy ) )
				{
					pCDcdGridYColumn->setColumnSize( aCdDcdSizeXy.getY() ) ;
				}
			}
			//	　(1.3.*.5)　Y列(ColumnType_Ressyabangou) の境界線の
			//	DcDrawオブジェクト に属性を設定。
			//	　(1.3.*.6)　Y列ColumnType_Ressyabangou) の境界線の
			//	高さを設定
			{
				CDcdGridYBorder* pCDcdGridYBorder 
					= pCDcdGridYColumn->getCDcdGridYBorder() ;
				Ou<CDcdLine> pCDcdLine = pCDcdGridYBorder->getIfDcDraw() ;
				pCDcdLine->setCdPenProp( getCdPenPropNarrowLine() ) ;

				CdDcdSizeXy aCdDcdSizeXy ;
				if ( pCDcdLine->getItemSize( 
					&aCDcdTarget , &aCdDcdSizeXy ) )
				{
					pCDcdGridYBorder->setColumnBorderSize( 
						aCdDcdSizeXy.getX() ) ;
				}
			}
		}
	}
}

void CCellBuilder::update01_03_02_12_setEkimei_OperationNumber(
	CWndJikokuhyou * pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	CDcdTargetGetDC	aCDcdTarget(NULL);

	// --------------------------------
	CdXColSpec aCdXColSpec(
		CdXColSpec::ColumnType_Ekimei);
	int iXColumnNumber =
		m_CdXColSpecCont.ColumnNumberFromSpec(aCdXColSpec);


	if (iXColumnNumber >= 0)
	{
		for (int idx = 0; idx < m_iOperationNumberRows; idx++)
		{
			CdYColSpec aCdYColSpec(
				CdYColSpec::ColumnType_OperationNumber, -1, idx);
			int iYColumnNumber = m_CdYColSpecCont.ColumnNumberFromSpec(
				aCdYColSpec, false);
			CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell(
				iXColumnNumber, iYColumnNumber);

			typedef CDcdTextbox CDcDrawCell;
			Ou<CDcDrawCell> pCDcDrawCell;

			if (pCDcdGridCell != NULL)
			{
				//(1.3.*.1)　結合セルの属性を設定。
				if (idx == 0)
				{
					pCDcdGridCell->setAttachCellCount(2, m_iOperationNumberRows);
				}

				//	(1.3.*.2)　セル 
				//	のDcDrawオブジェクトの型を設定
				//	( CDcdTextbox とする)。
				{
					pCDcDrawCell = dynamic_castOu<CDcDrawCell>(
						pCDcdGridCell->getIfDcDraw());
					if (pCDcDrawCell == NULL)
					{
						pCDcDrawCell = OuNew<CDcDrawCell>(new CDcDrawCell);
						pCDcdGridCell->setIfDcDraw(pCDcDrawCell);
					}
				}
				//(1.3.*.3)　セルの DcDrawオブジェクトに、属性を設定。
				{
					*pCDcDrawCell = createCDcdXColumn0();
					pCDcDrawCell->setText(tstringOf(
						(LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_OperationNumber)));
				}
			}
			CDcdGridYColumn* pCDcdGridYColumn = pCDcdGrid->getYColumn(
				iYColumnNumber);
			if (pCDcdGridYColumn != NULL)
			{
				//(1.3.*.4)　Y列 のセルの高さを設定
				{
					CdDcdSizeXy aCdDcdSizeXy;
					if (pCDcDrawCell->getItemSize(
						&aCDcdTarget, &aCdDcdSizeXy))
					{
						pCDcdGridYColumn->setColumnSize(aCdDcdSizeXy.getY());
					}
				}
				//	　(1.3.*.5)　Y列 の境界線の
				//	DcDrawオブジェクト に属性を設定。
				//	　(1.3.*.6)　Y列 の境界線の
				//	高さを設定
				{
					CDcdGridYBorder* pCDcdGridYBorder
						= pCDcdGridYColumn->getCDcdGridYBorder();
					Ou<CDcdLine> pCDcdLine = pCDcdGridYBorder->getIfDcDraw();
					if (idx == m_iOperationNumberRows-1)
					{
						pCDcdLine->setCdPenProp(getCdPenPropNarrowLine());
					}
					else
					{
						pCDcdLine->setCdPenProp(getCdPenPropNullLine());
					}

					CdDcdSizeXy aCdDcdSizeXy;
					if (pCDcdLine->getItemSize(
						&aCDcdTarget, &aCdDcdSizeXy))
					{
						pCDcdGridYBorder->setColumnBorderSize(
							aCdDcdSizeXy.getX());
					}
				}
			}
		}
	}
}


void CCellBuilder::update01_03_02_02_setEkimei_Ressyasyubetsu(
	CWndJikokuhyou* pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	CDcdTargetGetDC	aCDcdTarget(NULL);

	// --------------------------------
	CdXColSpec aCdXColSpec(
		CdXColSpec::ColumnType_Ekimei);
	int iXColumnNumber =
		m_CdXColSpecCont.ColumnNumberFromSpec(aCdXColSpec);


	if (iXColumnNumber >= 0)
	{
		CdYColSpec aCdYColSpec(
			CdYColSpec::ColumnType_Ressyasyubetsu);
		int iYColumnNumber = m_CdYColSpecCont.ColumnNumberFromSpec(
			aCdYColSpec, false);
		CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell(
			iXColumnNumber, iYColumnNumber);

		typedef CDcdTextbox CDcDrawCell;
		Ou<CDcDrawCell> pCDcDrawCell;

		if (pCDcdGridCell != NULL)
		{
			//(1.3.*.1)　結合セルの属性を設定。
			pCDcdGridCell->setAttachCellCount(2, 1);

			//	(1.3.*.2)　セル 
			//	のDcDrawオブジェクトの型を設定
			//	( CDcdTextbox とする)。
			{
				pCDcDrawCell = dynamic_castOu<CDcDrawCell>(
					pCDcdGridCell->getIfDcDraw());
				if (pCDcDrawCell == NULL)
				{
					pCDcDrawCell = OuNew<CDcDrawCell>(new CDcDrawCell);
					pCDcdGridCell->setIfDcDraw(pCDcDrawCell);
				}
			}
			//(1.3.*.3)　セルの DcDrawオブジェクトに、属性を設定。
			{
				*pCDcDrawCell = createCDcdXColumn0();
				pCDcDrawCell->setText(tstringOf(
					(LPCTSTR)MfcUtil::LoadCString(
						IDS_WORD_RESSYASYUBETSU)));
			}
		}
		CDcdGridYColumn* pCDcdGridYColumn = pCDcdGrid->getYColumn(
			iYColumnNumber);
		if (pCDcdGridYColumn != NULL)
		{
			//(1.3.*.4)　Y列 のセルの高さを設定
			{
				CdDcdSizeXy aCdDcdSizeXy;
				if (pCDcDrawCell->getItemSize(
					&aCDcdTarget, &aCdDcdSizeXy))
				{
					pCDcdGridYColumn->setColumnSize(aCdDcdSizeXy.getY());
				}
			}
			//	　(1.3.*.5)　Y列 の境界線の
			//	DcDrawオブジェクト に属性を設定。
			//	　(1.3.*.6)　Y列 の境界線の
			//	高さを設定
			{
				CDcdGridYBorder* pCDcdGridYBorder
					= pCDcdGridYColumn->getCDcdGridYBorder();
				Ou<CDcdLine> pCDcdLine = pCDcdGridYBorder->getIfDcDraw();
				pCDcdLine->setCdPenProp(getCdPenPropNarrowLine());

				CdDcdSizeXy aCdDcdSizeXy;
				if (pCDcdLine->getItemSize(
					&aCDcdTarget, &aCdDcdSizeXy))
				{
					pCDcdGridYBorder->setColumnBorderSize(
						aCdDcdSizeXy.getX());
				}
			}
		}
	}
}


void CCellBuilder::update01_03_02_03_setEkimei_Ressyamei( 
	CWndJikokuhyou* pCWndJikokuhyou ) 
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid() ;
	CDcdTargetGetDC	aCDcdTarget( NULL ) ;

	// --------------------------------
	CdXColSpec aCdXColSpec( 
		CdXColSpec::ColumnType_Ekimei ) ;
	int iXColumnNumber = 
		m_CdXColSpecCont.ColumnNumberFromSpec( aCdXColSpec ) ;

	if ( iXColumnNumber >= 0 )
	{
		CdYColSpec aCdYColSpec( 
			CdYColSpec::ColumnType_Ressyamei ) ;
		int iYColumnNumber = m_CdYColSpecCont.ColumnNumberFromSpec( 
			aCdYColSpec , false ) ;
		CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell( 
			iXColumnNumber , iYColumnNumber ) ;

		typedef CDcdTextboxV3 CDcDrawCell ;
		Ou<CDcDrawCell> pCDcDrawCell ;

		if ( pCDcdGridCell != NULL )
		{
			//(1.3.*.1)　結合セルの属性を設定。
			pCDcdGridCell->setAttachCellCount( 2 , 3 ) ;

			//	(1.3.*.2)　セル(ColumnType_Ekimei,ColumnType_Ressyabangou) 
			//	のDcDrawオブジェクトの型を設定
			//	( CDcdTextbox とする)。
			{
				pCDcDrawCell = dynamic_castOu<CDcDrawCell>( 
					pCDcdGridCell->getIfDcDraw() ) ;
				if ( pCDcDrawCell == NULL )
				{
					pCDcDrawCell = OuNew<CDcDrawCell>( new CDcDrawCell ) ;
					pCDcdGridCell->setIfDcDraw( pCDcDrawCell ) ;
				}
			}
			//(1.3.*.3)　セル(ColumnType_Ekimei,ColumnType_Ressyabangou) 
			//	DcDrawオブジェクトに、属性を設定。
			{
				*pCDcDrawCell = createCDcdXColumn0V() ;
				pCDcDrawCell->setText( tstringOf( 
					(LPCTSTR)MfcUtil::LoadCString( 
						IDS_WORD_Ressyamei ) ) ) ;
			}
		}
		CDcdGridYColumn* pCDcdGridYColumn = pCDcdGrid->getYColumn( 
			iYColumnNumber ) ;
		if ( pCDcdGridYColumn != NULL )
		{
			//(1.3.*.4)　Y列 のセルの高さを設定
			{
				CdDcdSizeXy aCdDcdSizeXy ;
				if ( pCDcDrawCell->getItemSize( 
					&aCDcdTarget , &aCdDcdSizeXy ) )
				{
					pCDcdGridYColumn->setColumnSize( aCdDcdSizeXy.getY() ) ;					}
			}
			//	　(1.3.*.5)　Y列 の境界線の
			//	DcDrawオブジェクト に属性を設定。
			//	　(1.3.*.6)　Y列 の境界線の
			//	高さを設定
			{
				CDcdGridYBorder* pCDcdGridYBorder 
					= pCDcdGridYColumn->getCDcdGridYBorder() ;
				Ou<CDcdLine> pCDcdLine = pCDcdGridYBorder->getIfDcDraw() ;
				pCDcdLine->setCdPenProp( getCdPenPropNullLine() ) ;

				CdDcdSizeXy aCdDcdSizeXy ;
				if ( pCDcdLine->getItemSize( 
					&aCDcdTarget , &aCdDcdSizeXy ) )
				{
					pCDcdGridYBorder->setColumnBorderSize( 
						aCdDcdSizeXy.getX() ) ;
				}
			}
		}
	}
}


void CCellBuilder::update01_03_02_04_setEkimei_Gousuu( 
	CWndJikokuhyou* pCWndJikokuhyou ) 
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid() ;
	CDcdTargetGetDC	aCDcdTarget( NULL ) ;

	// --------------------------------
	CdXColSpec aCdXColSpec( 
		CdXColSpec::ColumnType_Ekimei ) ;
	int iXColumnNumber = 
		m_CdXColSpecCont.ColumnNumberFromSpec( aCdXColSpec ) ;

	if ( iXColumnNumber >= 0 )
	{
		CdYColSpec aCdYColSpec( 
			CdYColSpec::ColumnType_Gousuu ) ;
		int iYColumnNumber = m_CdYColSpecCont.ColumnNumberFromSpec( 
			aCdYColSpec , false ) ;
		CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell( 
			iXColumnNumber , iYColumnNumber ) ;

		typedef CDcdTextbox CDcDrawCell ;
		Ou<CDcDrawCell> pCDcDrawCell ;

		if ( pCDcdGridCell != NULL )
		{
			//(1.3.*.1)　結合セルの属性を設定。
			pCDcdGridCell->setAttachCellCount( 2 , 1 ) ;

			//	(1.3.*.2)　セルのDcDrawオブジェクトの型を設定
			{
				pCDcDrawCell = dynamic_castOu<CDcDrawCell>( 
					pCDcdGridCell->getIfDcDraw() ) ;
				if ( pCDcDrawCell == NULL )
				{
					pCDcDrawCell = OuNew<CDcDrawCell>( new CDcDrawCell ) ;
					pCDcdGridCell->setIfDcDraw( pCDcDrawCell ) ;
				}
			}
			//(1.3.*.3)　セルのDcDrawオブジェクトに、属性を設定。
			{
				*pCDcDrawCell = createCDcdXColumn0() ;
			}
		}
		CDcdGridYColumn* pCDcdGridYColumn = pCDcdGrid->getYColumn( 
			iYColumnNumber ) ;
		if ( pCDcdGridYColumn != NULL )
		{
			//(1.3.*.4)　Y列 のセルの高さを設定
			{
				CdDcdSizeXy aCdDcdSizeXy ;
				if ( pCDcDrawCell->getItemSize( 
					&aCDcdTarget , &aCdDcdSizeXy ) )
				{
					pCDcdGridYColumn->setColumnSize( aCdDcdSizeXy.getY() ) ;					}
			}
			//	　(1.3.*.5)　Y列 の境界線の
			//	DcDrawオブジェクト に属性を設定。
			//	　(1.3.*.6)　Y列 の境界線の
			//	高さを設定
			{
				CDcdGridYBorder* pCDcdGridYBorder 
					= pCDcdGridYColumn->getCDcdGridYBorder() ;
				Ou<CDcdLine> pCDcdLine = pCDcdGridYBorder->getIfDcDraw() ;
				pCDcdLine->setCdPenProp( getCdPenPropNullLine() ) ;

				CdDcdSizeXy aCdDcdSizeXy ;
				if ( pCDcdLine->getItemSize( 
					&aCDcdTarget , &aCdDcdSizeXy ) )
				{
					pCDcdGridYBorder->setColumnBorderSize( 
						aCdDcdSizeXy.getX() ) ;
				}
			}
		}
	}
}


void CCellBuilder::update01_03_02_05_setEkimei_Gou( 
	CWndJikokuhyou* pCWndJikokuhyou ) 
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid() ;
	CDcdTargetGetDC	aCDcdTarget( NULL ) ;

	// --------------------------------
	CdXColSpec aCdXColSpec( 
		CdXColSpec::ColumnType_Ekimei ) ;
	int iXColumnNumber = 
		m_CdXColSpecCont.ColumnNumberFromSpec( aCdXColSpec ) ;

	if ( iXColumnNumber >= 0 )
	{
		CdYColSpec aCdYColSpec( 
			CdYColSpec::ColumnType_Gou ) ;
		int iYColumnNumber = m_CdYColSpecCont.ColumnNumberFromSpec( 
			aCdYColSpec , false ) ;
		CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell( 
			iXColumnNumber , iYColumnNumber ) ;

		typedef CDcdTextbox CDcDrawCell ;
		Ou<CDcDrawCell> pCDcDrawCell ;

		if ( pCDcdGridCell != NULL )
		{
			//(1.3.*.1)　結合セルの属性を設定。
			pCDcdGridCell->setAttachCellCount( 2 , 1 ) ;

			//	(1.3.*.2)　セルのDcDrawオブジェクトの型を設定
			{
				pCDcDrawCell = dynamic_castOu<CDcDrawCell>( 
					pCDcdGridCell->getIfDcDraw() ) ;
				if ( pCDcDrawCell == NULL )
				{
					pCDcDrawCell = OuNew<CDcDrawCell>( new CDcDrawCell ) ;
					pCDcdGridCell->setIfDcDraw( pCDcDrawCell ) ;
				}
			}
			//(1.3.*.3)　セルのDcDrawオブジェクトに、属性を設定。
			{
				*pCDcDrawCell = createCDcdXColumn0() ;
			}
		}
		CDcdGridYColumn* pCDcdGridYColumn = pCDcdGrid->getYColumn( 
			iYColumnNumber ) ;
		if ( pCDcdGridYColumn != NULL )
		{
			//(1.3.*.4)　Y列 のセルの高さを設定
			{
				CdDcdSizeXy aCdDcdSizeXy ;
				if ( pCDcDrawCell->getItemSize( 
					&aCDcdTarget , &aCdDcdSizeXy ) )
				{
					pCDcdGridYColumn->setColumnSize( aCdDcdSizeXy.getY() ) ;					}
			}
			//	　(1.3.*.5)　Y列 の境界線の
			//	DcDrawオブジェクト に属性を設定。
			//	　(1.3.*.6)　Y列 の境界線の
			//	高さを設定
			{
				CDcdGridYBorder* pCDcdGridYBorder 
					= pCDcdGridYColumn->getCDcdGridYBorder() ;
				Ou<CDcdLine> pCDcdLine = pCDcdGridYBorder->getIfDcDraw() ;
				pCDcdLine->setCdPenProp( getCdPenPropNarrowLine() ) ;

				CdDcdSizeXy aCdDcdSizeXy ;
				if ( pCDcdLine->getItemSize( 
					&aCDcdTarget , &aCdDcdSizeXy ) )
				{
					pCDcdGridYBorder->setColumnBorderSize( 
						aCdDcdSizeXy.getX() ) ;
				}
			}
		}
	}
}

void CCellBuilder::update01_03_02_13_setShihatsuEkimei(
	CWndJikokuhyou* pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	CDcdTargetGetDC	aCDcdTarget(NULL);

	// --------------------------------
	/*const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
	m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(
	m_pCentDedRessyaCont->getRessyahoukou());*/

	// --------------------------------
	CdXColSpec aCdXColSpec(
		CdXColSpec::ColumnType_Ekimei);
	int iXColumnNumber =
		m_CdXColSpecCont.ColumnNumberFromSpec(aCdXColSpec);
	if (iXColumnNumber >= 0)
	{
		CdYColSpec aCdYColSpec(
			CdYColSpec::ColumnType_ShihatsuEkimei);
		int iYColumnNumber =
			m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec, false);
		CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell(
			iXColumnNumber, iYColumnNumber);

		typedef CDcdTextbox CDcDrawCell;
		Ou<CDcDrawCell> pCDcDrawCell;
		if (pCDcdGridCell != 0)
		{
			//(1.3.*.1)　セルの結合セルの属性を設定。

			pCDcdGridCell->setAttachCellCount(2, 1);

			//	(1.3.*.2)　セルのDcDrawオブジェクトの型を設定
			//	( CDcdTextbox とする)。
			{
				pCDcDrawCell = dynamic_castOu<CDcDrawCell>(
					pCDcdGridCell->getIfDcDraw());
				if (pCDcDrawCell == NULL)
				{
					pCDcDrawCell = OuNew<CDcDrawCell>(new CDcDrawCell);
					pCDcdGridCell->setIfDcDraw(pCDcDrawCell);
				}
			}
			//(1.3.*.3)　セルのDcDrawオブジェクトに、属性を設定。
			{
				*pCDcDrawCell = createCDcdEkimei();
				pCDcDrawCell->setText(tstringOf(
					(LPCTSTR)MfcUtil::LoadCString(
						IDS_WORD_ShihatsuEkimei)));
			}
		}

		CDcdGridYColumn* pCDcdGridYColumn = pCDcdGrid->getYColumn(
			iYColumnNumber);
		if (pCDcdGridYColumn)
		{
			//(1.3.*.4)　Y列のセルの高さを設定
			{
				CdDcdSizeXy aCdDcdSizeXy;
				if (pCDcDrawCell->getItemSize(
					&aCDcdTarget, &aCdDcdSizeXy))
				{
					pCDcdGridYColumn->setColumnSize(
						aCdDcdSizeXy.getY());
				}
			}
			//	　(1.3.*.5)　Y列(ColumnType_Ressyabangou) の境界線の
			//	DcDrawオブジェクト に属性を設定。
			//	　(1.3.*.6)　Y列ColumnType_Ressyabangou) の境界線の
			//	高さを設定
			{
				CDcdGridYBorder* pCDcdGridYBorder
					= pCDcdGridYColumn->getCDcdGridYBorder();
				Ou<CDcdLine> pCDcdLine =
					pCDcdGridYBorder->getIfDcDraw();
				pCDcdLine->setCdPenProp(getCdPenPropNarrowLine());


				// --------------------------------
				//	線の幅から、列幅を設定
				CdDcdSizeXy aCdDcdSizeXy;
				if (pCDcdLine->getItemSize(
					&aCDcdTarget, &aCdDcdSizeXy))
				{
					pCDcdGridYBorder->setColumnBorderSize(
						aCdDcdSizeXy.getX());
				}
			}
		}
	}
}

void CCellBuilder::update01_03_02_10_setEkimei_Operation_Shihatsu(
	CWndJikokuhyou* pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	CDcdTargetGetDC	aCDcdTarget(NULL);

	// --------------------------------
	/*const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou());*/

	// --------------------------------
	CdXColSpec aCdXColSpec(
		CdXColSpec::ColumnType_Ekimei);
	int iXColumnNumber =
		m_CdXColSpecCont.ColumnNumberFromSpec(aCdXColSpec);
	if (iXColumnNumber >= 0)
	{
		CdYColSpec aCdYColSpec1(
			CdYColSpec::ColumnType_Operation_Shihatsu1);
		CdYColSpec aCdYColSpec2(
			CdYColSpec::ColumnType_Operation_Shihatsu2);
		CdYColSpec aCdYColSpec3(
			CdYColSpec::ColumnType_Operation_Shihatsu3);
		CdYColSpec aCdYColSpec4(
			CdYColSpec::ColumnType_Operation_Shihatsu4);
		int iYColumnNumber1 =
			m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec1, false);
		int iYColumnNumber2 =
			m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec2, false);
		int iYColumnNumber3 =
			m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec3, false);
		int iYColumnNumber4 =
			m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec4, false);
		CDcdGridCell* pCDcdGridCell1 = pCDcdGrid->getCell(
			iXColumnNumber, iYColumnNumber1);
		CDcdGridCell* pCDcdGridCell2 = pCDcdGrid->getCell(
			iXColumnNumber, iYColumnNumber2);
		CDcdGridCell* pCDcdGridCell3 = pCDcdGrid->getCell(
			iXColumnNumber, iYColumnNumber3);
		CDcdGridCell* pCDcdGridCell4 = pCDcdGrid->getCell(
			iXColumnNumber, iYColumnNumber4);

		typedef CDcdTextbox CDcDrawCell;
		Ou<CDcDrawCell> pCDcDrawCell1;
		Ou<CDcDrawCell> pCDcDrawCell2;
		Ou<CDcDrawCell> pCDcDrawCell3;
		Ou<CDcDrawCell> pCDcDrawCell4;
		if (pCDcdGridCell1 != 0)
		{
			//(1.3.*.1)　セルの結合セルの属性を設定。

			if (m_iEnableOperation > 1)
			{
				if (m_bDisplayInOutLinkCode)
				{
					pCDcdGridCell1->setAttachCellCount(2, 4);
				}
				else
				{
					pCDcdGridCell1->setAttachCellCount(2, 3);
				}
			}
			else 
			{
				pCDcdGridCell1->setAttachCellCount(2, 2);
			}

			//	(1.3.*.2)　セルのDcDrawオブジェクトの型を設定
			//	( CDcdTextbox とする)。
			{
				pCDcDrawCell1 = dynamic_castOu<CDcDrawCell>(
					pCDcdGridCell1->getIfDcDraw());
				pCDcDrawCell2 = dynamic_castOu<CDcDrawCell>(
					pCDcdGridCell2->getIfDcDraw());
				if (pCDcDrawCell1 == NULL)
				{
					pCDcDrawCell1 = OuNew<CDcDrawCell>(new CDcDrawCell);
					pCDcdGridCell1->setIfDcDraw(pCDcDrawCell1);
				}
				if (pCDcDrawCell2 == NULL)
				{
					pCDcDrawCell2 = OuNew<CDcDrawCell>(new CDcDrawCell);
					pCDcdGridCell2->setIfDcDraw(pCDcDrawCell2);
				}

				if (m_iEnableOperation > 1)
				{
					pCDcDrawCell3 = dynamic_castOu<CDcDrawCell>(
						pCDcdGridCell3->getIfDcDraw());
					if (pCDcDrawCell3 == NULL)
					{
						pCDcDrawCell3 = OuNew<CDcDrawCell>(new CDcDrawCell);
						pCDcdGridCell3->setIfDcDraw(pCDcDrawCell3);
					}
					if (m_bDisplayInOutLinkCode)
					{
						pCDcDrawCell4 = dynamic_castOu<CDcDrawCell>(
							pCDcdGridCell4->getIfDcDraw());
						if (pCDcDrawCell4 == NULL)
						{
							pCDcDrawCell4 = OuNew<CDcDrawCell>(new CDcDrawCell);
							pCDcdGridCell4->setIfDcDraw(pCDcDrawCell4);
						}
					}
				}
			}
			//(1.3.*.3)　セルのDcDrawオブジェクトに、属性を設定。
			{
				*pCDcDrawCell1 = createCDcdEkimei();
				pCDcDrawCell1->setText(tstringOf(
					(LPCTSTR)MfcUtil::LoadCString(
						IDS_WORD_ShihatsuOperation)));
				*pCDcDrawCell2 = createCDcdEkimei();
				if (m_iEnableOperation > 1)
				{
					*pCDcDrawCell3 = createCDcdEkimei();
					if (m_bDisplayInOutLinkCode)
					{
						*pCDcDrawCell4 = createCDcdEkimei();
					}
				}
			}
		}

		CDcdGridYColumn* pCDcdGridYColumn1 = pCDcdGrid->getYColumn(
			iYColumnNumber1);
		if (pCDcdGridYColumn1)
		{
			//(1.3.*.4)　Y列のセルの高さを設定
			{
				CdDcdSizeXy aCdDcdSizeXy;
				if (pCDcDrawCell1->getItemSize(
					&aCDcdTarget, &aCdDcdSizeXy))
				{
					pCDcdGridYColumn1->setColumnSize(
						aCdDcdSizeXy.getY());
				}
			}
			//	　(1.3.*.5)　Y列(ColumnType_Ressyabangou) の境界線の
			//	DcDrawオブジェクト に属性を設定。
			//	　(1.3.*.6)　Y列ColumnType_Ressyabangou) の境界線の
			//	高さを設定
			{
				CDcdGridYBorder* pCDcdGridYBorder1
					= pCDcdGridYColumn1->getCDcdGridYBorder();
				Ou<CDcdLine> pCDcdLine =
					pCDcdGridYBorder1->getIfDcDraw();
				pCDcdLine->setCdPenProp(getCdPenPropNullLine());
				//pCDcdLine->setCdPenProp(getCdPenPropNarrowLine());


				// --------------------------------
				//	線の幅から、列幅を設定
				CdDcdSizeXy aCdDcdSizeXy;
				if (pCDcdLine->getItemSize(
					&aCDcdTarget, &aCdDcdSizeXy))
				{
					pCDcdGridYBorder1->setColumnBorderSize(
						aCdDcdSizeXy.getX());
				}
			}
		}

		CDcdGridYColumn* pCDcdGridYColumn2 = pCDcdGrid->getYColumn(
			iYColumnNumber2);
		if (pCDcdGridYColumn2)
		{
			//(1.3.*.4)　Y列のセルの高さを設定
			{
				CdDcdSizeXy aCdDcdSizeXy;
				if (pCDcDrawCell2->getItemSize(
					&aCDcdTarget, &aCdDcdSizeXy))
				{
					pCDcdGridYColumn2->setColumnSize(
						aCdDcdSizeXy.getY());
				}
			}
			//	　(1.3.*.5)　Y列(ColumnType_Ressyabangou) の境界線の
			//	DcDrawオブジェクト に属性を設定。
			//	　(1.3.*.6)　Y列ColumnType_Ressyabangou) の境界線の
			//	高さを設定
			{
				CDcdGridYBorder* pCDcdGridYBorder2
					= pCDcdGridYColumn2->getCDcdGridYBorder();
				Ou<CDcdLine> pCDcdLine =
					pCDcdGridYBorder2->getIfDcDraw();
				if (m_iEnableOperation > 1)
				{
					pCDcdLine->setCdPenProp(getCdPenPropNullLine());
				}
				else
				{
					pCDcdLine->setCdPenProp(getCdPenPropNarrowLine());
				}
				
				// --------------------------------
				//	線の幅から、列幅を設定
				CdDcdSizeXy aCdDcdSizeXy;
				if (pCDcdLine->getItemSize(
					&aCDcdTarget, &aCdDcdSizeXy))
				{
					pCDcdGridYBorder2->setColumnBorderSize(
						aCdDcdSizeXy.getX());
				}
			}
		}

		CDcdGridYColumn* pCDcdGridYColumn3 = pCDcdGrid->getYColumn(
			iYColumnNumber3);
		if (pCDcdGridYColumn3)
		{
			//(1.3.*.4)　Y列のセルの高さを設定
			{
				CdDcdSizeXy aCdDcdSizeXy;
				if (pCDcDrawCell3->getItemSize(
					&aCDcdTarget, &aCdDcdSizeXy))
				{
					pCDcdGridYColumn3->setColumnSize(
						aCdDcdSizeXy.getY());
				}
			}
			//	　(1.3.*.5)　Y列(ColumnType_Ressyabangou) の境界線の
			//	DcDrawオブジェクト に属性を設定。
			//	　(1.3.*.6)　Y列ColumnType_Ressyabangou) の境界線の
			//	高さを設定
			{
				CDcdGridYBorder* pCDcdGridYBorder3
					= pCDcdGridYColumn3->getCDcdGridYBorder();
				Ou<CDcdLine> pCDcdLine =
					pCDcdGridYBorder3->getIfDcDraw();
				if (m_bDisplayInOutLinkCode)
				{
					pCDcdLine->setCdPenProp(getCdPenPropNullLine());
				}
				else
				{
					pCDcdLine->setCdPenProp(getCdPenPropNarrowLine());
				}

				// --------------------------------
				//	線の幅から、列幅を設定
				CdDcdSizeXy aCdDcdSizeXy;
				if (pCDcdLine->getItemSize(
					&aCDcdTarget, &aCdDcdSizeXy))
				{
					pCDcdGridYBorder3->setColumnBorderSize(
						aCdDcdSizeXy.getX());
				}
			}
		}

		CDcdGridYColumn* pCDcdGridYColumn4 = pCDcdGrid->getYColumn(
			iYColumnNumber4);
		if (pCDcdGridYColumn4)
		{
			//(1.3.*.4)　Y列のセルの高さを設定
			{
				CdDcdSizeXy aCdDcdSizeXy;
				if (pCDcDrawCell4->getItemSize(
					&aCDcdTarget, &aCdDcdSizeXy))
				{
					pCDcdGridYColumn4->setColumnSize(
						aCdDcdSizeXy.getY());
				}
			}
			//	　(1.3.*.5)　Y列(ColumnType_Ressyabangou) の境界線の
			//	DcDrawオブジェクト に属性を設定。
			//	　(1.3.*.6)　Y列ColumnType_Ressyabangou) の境界線の
			//	高さを設定
			{
				CDcdGridYBorder* pCDcdGridYBorder4
					= pCDcdGridYColumn4->getCDcdGridYBorder();
				Ou<CDcdLine> pCDcdLine =
					pCDcdGridYBorder4->getIfDcDraw();
				pCDcdLine->setCdPenProp(getCdPenPropNarrowLine());
				//pCDcdLine->setCdPenProp(getCdPenPropNullLine());

				// --------------------------------
				//	線の幅から、列幅を設定
				CdDcdSizeXy aCdDcdSizeXy;
				if (pCDcdLine->getItemSize(
					&aCDcdTarget, &aCdDcdSizeXy))
				{
					pCDcdGridYBorder4->setColumnBorderSize(
						aCdDcdSizeXy.getX());
				}
			}
		}
	}
}

void CCellBuilder::update01_03_02_14_setShuchakuEkimei(
	CWndJikokuhyou* pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	CDcdTargetGetDC	aCDcdTarget(NULL);

	// --------------------------------
	/*const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
	m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(
	m_pCentDedRessyaCont->getRessyahoukou());*/

	// --------------------------------
	CdXColSpec aCdXColSpec(
		CdXColSpec::ColumnType_Ekimei);
	int iXColumnNumber =
		m_CdXColSpecCont.ColumnNumberFromSpec(aCdXColSpec);
	if (iXColumnNumber >= 0)
	{
		CdYColSpec aCdYColSpec(
			CdYColSpec::ColumnType_ShuchakuEkimei);
		int iYColumnNumber =
			m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec, false);
		CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell(
			iXColumnNumber, iYColumnNumber);

		typedef CDcdTextbox CDcDrawCell;
		Ou<CDcDrawCell> pCDcDrawCell;
		if (pCDcdGridCell != 0)
		{
			//(1.3.*.1)　セルの結合セルの属性を設定。

			pCDcdGridCell->setAttachCellCount(2, 1);

			//	(1.3.*.2)　セルのDcDrawオブジェクトの型を設定
			//	( CDcdTextbox とする)。
			{
				pCDcDrawCell = dynamic_castOu<CDcDrawCell>(
					pCDcdGridCell->getIfDcDraw());
				if (pCDcDrawCell == NULL)
				{
					pCDcDrawCell = OuNew<CDcDrawCell>(new CDcDrawCell);
					pCDcdGridCell->setIfDcDraw(pCDcDrawCell);
				}
			}
			//(1.3.*.3)　セルのDcDrawオブジェクトに、属性を設定。
			{
				*pCDcDrawCell = createCDcdEkimei();
				pCDcDrawCell->setText(tstringOf(
					(LPCTSTR)MfcUtil::LoadCString(
						IDS_WORD_ShuchakuEkimei)));
			}
		}

		CDcdGridYColumn* pCDcdGridYColumn = pCDcdGrid->getYColumn(
			iYColumnNumber);
		if (pCDcdGridYColumn)
		{
			//(1.3.*.4)　Y列のセルの高さを設定
			{
				CdDcdSizeXy aCdDcdSizeXy;
				if (pCDcDrawCell->getItemSize(
					&aCDcdTarget, &aCdDcdSizeXy))
				{
					pCDcdGridYColumn->setColumnSize(
						aCdDcdSizeXy.getY());
				}
			}
			//	　(1.3.*.5)　Y列(ColumnType_Ressyabangou) の境界線の
			//	DcDrawオブジェクト に属性を設定。
			//	　(1.3.*.6)　Y列ColumnType_Ressyabangou) の境界線の
			//	高さを設定
			{
				CDcdGridYBorder* pCDcdGridYBorder
					= pCDcdGridYColumn->getCDcdGridYBorder();
				Ou<CDcdLine> pCDcdLine =
					pCDcdGridYBorder->getIfDcDraw();
				pCDcdLine->setCdPenProp(getCdPenPropNarrowLine());


				// --------------------------------
				//	線の幅から、列幅を設定
				CdDcdSizeXy aCdDcdSizeXy;
				if (pCDcdLine->getItemSize(
					&aCDcdTarget, &aCdDcdSizeXy))
				{
					pCDcdGridYBorder->setColumnBorderSize(
						aCdDcdSizeXy.getX());
				}
			}
		}
	}
}

void CCellBuilder::update01_03_02_11_setEkimei_Operation_Shuchaku(
	CWndJikokuhyou* pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	CDcdTargetGetDC	aCDcdTarget(NULL);

	// --------------------------------
	/*const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
	m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(
	m_pCentDedRessyaCont->getRessyahoukou());*/

	// --------------------------------
	CdXColSpec aCdXColSpec(
		CdXColSpec::ColumnType_Ekimei);
	int iXColumnNumber =
		m_CdXColSpecCont.ColumnNumberFromSpec(aCdXColSpec);
	if (iXColumnNumber >= 0)
	{
		CdYColSpec aCdYColSpec1(
			CdYColSpec::ColumnType_Operation_Shuchaku1);
		CdYColSpec aCdYColSpec2(
			CdYColSpec::ColumnType_Operation_Shuchaku2);
		CdYColSpec aCdYColSpec3(
			CdYColSpec::ColumnType_Operation_Shuchaku3);
		int iYColumnNumber1 =
			m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec1, false);
		int iYColumnNumber2 =
			m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec2, false);
		int iYColumnNumber3 =
			m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec3, false);
		CDcdGridCell* pCDcdGridCell1 = pCDcdGrid->getCell(
			iXColumnNumber, iYColumnNumber1);
		CDcdGridCell* pCDcdGridCell2 = pCDcdGrid->getCell(
			iXColumnNumber, iYColumnNumber2);
		CDcdGridCell* pCDcdGridCell3 = pCDcdGrid->getCell(
			iXColumnNumber, iYColumnNumber3);

		typedef CDcdTextbox CDcDrawCell;
		Ou<CDcDrawCell> pCDcDrawCell1;
		Ou<CDcDrawCell> pCDcDrawCell2;
		Ou<CDcDrawCell> pCDcDrawCell3;
		if (pCDcdGridCell1 != 0)
		{
			//(1.3.*.1)　セルの結合セルの属性を設定。

			if (m_iEnableOperation > 1 && m_bDisplayInOutLinkCode)
			{
				pCDcdGridCell1->setAttachCellCount(2, 3);
			}
			else
			{
				pCDcdGridCell1->setAttachCellCount(2, 2);
			}

			//	(1.3.*.2)　セルのDcDrawオブジェクトの型を設定
			//	( CDcdTextbox とする)。
			{
				pCDcDrawCell1 = dynamic_castOu<CDcDrawCell>(
					pCDcdGridCell1->getIfDcDraw());
				pCDcDrawCell2 = dynamic_castOu<CDcDrawCell>(
					pCDcdGridCell2->getIfDcDraw());
				if (pCDcDrawCell1 == NULL)
				{
					pCDcDrawCell1 = OuNew<CDcDrawCell>(new CDcDrawCell);
					pCDcdGridCell1->setIfDcDraw(pCDcDrawCell1);
				}
				if (pCDcDrawCell2 == NULL)
				{
					pCDcDrawCell2 = OuNew<CDcDrawCell>(new CDcDrawCell);
					pCDcdGridCell2->setIfDcDraw(pCDcDrawCell2);
				}
				if (m_iEnableOperation > 1 && m_bDisplayInOutLinkCode)
				{
					pCDcDrawCell3 = dynamic_castOu<CDcDrawCell>(
						pCDcdGridCell3->getIfDcDraw());
					if (pCDcDrawCell3 == NULL)
					{
						pCDcDrawCell3 = OuNew<CDcDrawCell>(new CDcDrawCell);
						pCDcdGridCell3->setIfDcDraw(pCDcDrawCell3);
					}
				}
			}
			//(1.3.*.3)　セルのDcDrawオブジェクトに、属性を設定。
			{
				*pCDcDrawCell1 = createCDcdEkimei();
				pCDcDrawCell1->setText(tstringOf(
					(LPCTSTR)MfcUtil::LoadCString(
						IDS_WORD_ShuchakuOperation)));
				*pCDcDrawCell2 = createCDcdEkimei();
				if (m_iEnableOperation > 1 && m_bDisplayInOutLinkCode)
				{
					*pCDcDrawCell3 = createCDcdEkimei();
				}
			}
		}

		CDcdGridYColumn* pCDcdGridYColumn1 = pCDcdGrid->getYColumn(
			iYColumnNumber1);
		if (pCDcdGridYColumn1)
		{
			//(1.3.*.4)　Y列のセルの高さを設定
			{
				CdDcdSizeXy aCdDcdSizeXy;
				if (pCDcDrawCell1->getItemSize(
					&aCDcdTarget, &aCdDcdSizeXy))
				{
					pCDcdGridYColumn1->setColumnSize(
						aCdDcdSizeXy.getY());
				}
			}
			//	　(1.3.*.5)　Y列(ColumnType_Ressyabangou) の境界線の
			//	DcDrawオブジェクト に属性を設定。
			//	　(1.3.*.6)　Y列ColumnType_Ressyabangou) の境界線の
			//	高さを設定
			{
				CDcdGridYBorder* pCDcdGridYBorder1
					= pCDcdGridYColumn1->getCDcdGridYBorder();
				Ou<CDcdLine> pCDcdLine =
					pCDcdGridYBorder1->getIfDcDraw();
				pCDcdLine->setCdPenProp(getCdPenPropNullLine());


				// --------------------------------
				//	線の幅から、列幅を設定
				CdDcdSizeXy aCdDcdSizeXy;
				if (pCDcdLine->getItemSize(
					&aCDcdTarget, &aCdDcdSizeXy))
				{
					pCDcdGridYBorder1->setColumnBorderSize(
						aCdDcdSizeXy.getX());
				}
			}
		}

		CDcdGridYColumn* pCDcdGridYColumn2 = pCDcdGrid->getYColumn(
			iYColumnNumber2);
		if (pCDcdGridYColumn2)
		{
			//(1.3.*.4)　Y列のセルの高さを設定
			{
				CdDcdSizeXy aCdDcdSizeXy;
				if (pCDcDrawCell2->getItemSize(
					&aCDcdTarget, &aCdDcdSizeXy))
				{
					pCDcdGridYColumn2->setColumnSize(
						aCdDcdSizeXy.getY());
				}
			}
			//	　(1.3.*.5)　Y列(ColumnType_Ressyabangou) の境界線の
			//	DcDrawオブジェクト に属性を設定。
			//	　(1.3.*.6)　Y列ColumnType_Ressyabangou) の境界線の
			//	高さを設定
			{
				CDcdGridYBorder* pCDcdGridYBorder2
					= pCDcdGridYColumn2->getCDcdGridYBorder();
				Ou<CDcdLine> pCDcdLine =
					pCDcdGridYBorder2->getIfDcDraw();
				if (m_iEnableOperation > 1 && m_bDisplayInOutLinkCode)
				{
					pCDcdLine->setCdPenProp(getCdPenPropNullLine());
				}
				else
				{
					pCDcdLine->setCdPenProp(getCdPenPropNarrowLine());
				}

				// --------------------------------
				//	線の幅から、列幅を設定
				CdDcdSizeXy aCdDcdSizeXy;
				if (pCDcdLine->getItemSize(
					&aCDcdTarget, &aCdDcdSizeXy))
				{
					pCDcdGridYBorder2->setColumnBorderSize(
						aCdDcdSizeXy.getX());
				}
			}
		}

		CDcdGridYColumn* pCDcdGridYColumn3 = pCDcdGrid->getYColumn(
			iYColumnNumber3);
		if (pCDcdGridYColumn3)
		{
			//(1.3.*.4)　Y列のセルの高さを設定
			{
				CdDcdSizeXy aCdDcdSizeXy;
				if (pCDcDrawCell3->getItemSize(
					&aCDcdTarget, &aCdDcdSizeXy))
				{
					pCDcdGridYColumn3->setColumnSize(
						aCdDcdSizeXy.getY());
				}
			}
			//	　(1.3.*.5)　Y列(ColumnType_Ressyabangou) の境界線の
			//	DcDrawオブジェクト に属性を設定。
			//	　(1.3.*.6)　Y列ColumnType_Ressyabangou) の境界線の
			//	高さを設定
			{
				CDcdGridYBorder* pCDcdGridYBorder3
					= pCDcdGridYColumn3->getCDcdGridYBorder();
				Ou<CDcdLine> pCDcdLine =
					pCDcdGridYBorder3->getIfDcDraw();
				pCDcdLine->setCdPenProp(getCdPenPropNarrowLine());


				// --------------------------------
				//	線の幅から、列幅を設定
				CdDcdSizeXy aCdDcdSizeXy;
				if (pCDcdLine->getItemSize(
					&aCDcdTarget, &aCdDcdSizeXy))
				{
					pCDcdGridYBorder3->setColumnBorderSize(
						aCdDcdSizeXy.getX());
				}
			}
		}
	}
}

void CCellBuilder::update01_03_02_15_setEkimei_OuterTerminal_Shihatsu(
	CWndJikokuhyou* pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	CDcdTargetGetDC	aCDcdTarget(NULL);

	// --------------------------------
	/*const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
	m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(
	m_pCentDedRessyaCont->getRessyahoukou());*/

	// --------------------------------
	CdXColSpec aCdXColSpec(
		CdXColSpec::ColumnType_Ekimei);
	int iXColumnNumber =
		m_CdXColSpecCont.ColumnNumberFromSpec(aCdXColSpec);
	if (iXColumnNumber >= 0)
	{
		CdYColSpec aCdYColSpec1(
			CdYColSpec::ColumnType_Outer_Shihatsu1);
		CdYColSpec aCdYColSpec2(
			CdYColSpec::ColumnType_Outer_Shihatsu2);
		int iYColumnNumber1 =
			m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec1, false);
		int iYColumnNumber2 =
			m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec2, false);
		CDcdGridCell* pCDcdGridCell1 = pCDcdGrid->getCell(
			iXColumnNumber, iYColumnNumber1);
		CDcdGridCell* pCDcdGridCell2 = pCDcdGrid->getCell(
			iXColumnNumber, iYColumnNumber2);

		typedef CDcdTextbox CDcDrawCell;
		Ou<CDcDrawCell> pCDcDrawCell1;
		Ou<CDcDrawCell> pCDcDrawCell2;
		if (pCDcdGridCell1 != 0)
		{
			//(1.3.*.1)　セルの結合セルの属性を設定。

			pCDcdGridCell1->setAttachCellCount(2, 1);
			pCDcdGridCell2->setAttachCellCount(2, 1);

			//	(1.3.*.2)　セルのDcDrawオブジェクトの型を設定
			//	( CDcdTextbox とする)。
			{
				pCDcDrawCell1 = dynamic_castOu<CDcDrawCell>(
					pCDcdGridCell1->getIfDcDraw());
				pCDcDrawCell2 = dynamic_castOu<CDcDrawCell>(
					pCDcdGridCell2->getIfDcDraw());
				if (pCDcDrawCell1 == NULL)
				{
					pCDcDrawCell1 = OuNew<CDcDrawCell>(new CDcDrawCell);
					pCDcdGridCell1->setIfDcDraw(pCDcDrawCell1);
				}
				if (pCDcDrawCell2 == NULL)
				{
					pCDcDrawCell2 = OuNew<CDcDrawCell>(new CDcDrawCell);
					pCDcdGridCell2->setIfDcDraw(pCDcDrawCell2);
				}
			}
			//(1.3.*.3)　セルのDcDrawオブジェクトに、属性を設定。
			{
				*pCDcDrawCell1 = createCDcdEkimei();
				pCDcDrawCell1->setText(tstringOf(
					(LPCTSTR)MfcUtil::LoadCString(
						IDS_WORD_ShihatsuEkimei)));
				*pCDcDrawCell2 = createCDcdEkimei();
				pCDcDrawCell2->setText(tstringOf(
					(LPCTSTR)MfcUtil::LoadCString(
						IDS_WORD_Jikoku)));
			}
		}

		CDcdGridYColumn* pCDcdGridYColumn1 = pCDcdGrid->getYColumn(
			iYColumnNumber1);
		if (pCDcdGridYColumn1)
		{
			//(1.3.*.4)　Y列のセルの高さを設定
			{
				CdDcdSizeXy aCdDcdSizeXy;
				if (pCDcDrawCell1->getItemSize(
					&aCDcdTarget, &aCdDcdSizeXy))
				{
					pCDcdGridYColumn1->setColumnSize(
						aCdDcdSizeXy.getY());
				}
			}
			//	　(1.3.*.5)　Y列(ColumnType_Ressyabangou) の境界線の
			//	DcDrawオブジェクト に属性を設定。
			//	　(1.3.*.6)　Y列ColumnType_Ressyabangou) の境界線の
			//	高さを設定
			{
				CDcdGridYBorder* pCDcdGridYBorder1
					= pCDcdGridYColumn1->getCDcdGridYBorder();
				Ou<CDcdLine> pCDcdLine =
					pCDcdGridYBorder1->getIfDcDraw();
				pCDcdLine->setCdPenProp(getCdPenPropNullLine());
				//pCDcdLine->setCdPenProp(getCdPenPropNarrowLine());


				// --------------------------------
				//	線の幅から、列幅を設定
				CdDcdSizeXy aCdDcdSizeXy;
				if (pCDcdLine->getItemSize(
					&aCDcdTarget, &aCdDcdSizeXy))
				{
					pCDcdGridYBorder1->setColumnBorderSize(
						aCdDcdSizeXy.getX());
				}
			}
		}

		CDcdGridYColumn* pCDcdGridYColumn2 = pCDcdGrid->getYColumn(
			iYColumnNumber2);
		if (pCDcdGridYColumn2)
		{
			//(1.3.*.4)　Y列のセルの高さを設定
			{
				CdDcdSizeXy aCdDcdSizeXy;
				if (pCDcDrawCell2->getItemSize(
					&aCDcdTarget, &aCdDcdSizeXy))
				{
					pCDcdGridYColumn2->setColumnSize(
						aCdDcdSizeXy.getY());
				}
			}
			//	　(1.3.*.5)　Y列(ColumnType_Ressyabangou) の境界線の
			//	DcDrawオブジェクト に属性を設定。
			//	　(1.3.*.6)　Y列ColumnType_Ressyabangou) の境界線の
			//	高さを設定
			{
				CDcdGridYBorder* pCDcdGridYBorder2
					= pCDcdGridYColumn2->getCDcdGridYBorder();
				Ou<CDcdLine> pCDcdLine =
					pCDcdGridYBorder2->getIfDcDraw();
				pCDcdLine->setCdPenProp(getCdPenPropNarrowLine());
				//pCDcdLine->setCdPenProp(getCdPenPropNullLine());

				// --------------------------------
				//	線の幅から、列幅を設定
				CdDcdSizeXy aCdDcdSizeXy;
				if (pCDcdLine->getItemSize(
					&aCDcdTarget, &aCdDcdSizeXy))
				{
					pCDcdGridYBorder2->setColumnBorderSize(
						aCdDcdSizeXy.getX());
				}
			}
		}

	}
}

void CCellBuilder::update01_03_02_06_setEkimei_Chaku( 
	CWndJikokuhyou* pCWndJikokuhyou ) 
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid() ;
	CDcdTargetGetDC	aCDcdTarget( NULL ) ;

	// --------------------------------
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki = 
		m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(
		m_pCentDedRessyaCont->getRessyahoukou() ) ;

	// --------------------------------
	CdXColSpec aCdXColSpec( 
		CdXColSpec::ColumnType_Ekimei ) ;
	int iXColumnNumber = 
		m_CdXColSpecCont.ColumnNumberFromSpec( aCdXColSpec ) ;
	if ( iXColumnNumber >= 0 )
	{
		for ( int iEkiOrder = 0 ; iEkiOrder < muCdDedEki->size() ; 
			iEkiOrder ++ )
		{
			CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get( iEkiOrder ) ;

			CdYColSpec aCdYColSpec( 
				CdYColSpec::ColumnType_Ekijikoku_Chaku , 
				iEkiOrder ) ;
			int iYColumnNumber = 
				m_CdYColSpecCont.ColumnNumberFromSpec( aCdYColSpec , false ) ;
			CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell( 
				iXColumnNumber , iYColumnNumber ) ;

			typedef CDcdTextbox CDcDrawCell ;
			Ou<CDcDrawCell> pCDcDrawCell ;
			if ( pCDcdGridCell != 0 )
			{
				//(1.3.*.1)　セルの結合セルの属性を設定。
				/**
					2.0Update
					・編集モード時
						同一駅の物は全て結合する(前作業・番線・後作業・発時刻)
				*/
				int iYCount = 1;
				for (int idxy = iYColumnNumber + 1; idxy < m_CdYColSpecCont.size(); idxy++)
				{
					CdYColSpec aCdYColSpecSearch
						= m_CdYColSpecCont.ColumnNumberToSpec(idxy);
					if (iEkiOrder == aCdYColSpecSearch.getEkiOrder())
					{
						iYCount++;
					}
					else
					{
						break;
					}
				}
				pCDcdGridCell->setAttachCellCount(1, iYCount);

				//	(1.3.*.2)　セルのDcDrawオブジェクトの型を設定
				//	( CDcdTextbox とする)。
				{
					pCDcDrawCell = dynamic_castOu<CDcDrawCell>( 
						pCDcdGridCell->getIfDcDraw() ) ;
					if ( pCDcDrawCell == NULL )
					{
						pCDcDrawCell = OuNew<CDcDrawCell>( new CDcDrawCell ) ;
						pCDcdGridCell->setIfDcDraw( pCDcDrawCell ) ;
					}
				}
				//(1.3.*.3)　セルのDcDrawオブジェクトに、属性を設定。
				{
					*pCDcDrawCell = createCDcdEkimei() ;
					pCDcDrawCell->setText( aCdDedEki.getEkimei() );
				}
			}
			CDcdGridYColumn* pCDcdGridYColumn = pCDcdGrid->getYColumn( 
				iYColumnNumber ) ;
			if ( pCDcdGridYColumn )
			{
				//(1.3.*.4)　Y列のセルの高さを設定
				{
					CdDcdSizeXy aCdDcdSizeXy ;
					if ( pCDcDrawCell->getItemSize( 
						&aCDcdTarget , &aCdDcdSizeXy ) )
					{
						pCDcdGridYColumn->setColumnSize( 
							aCdDcdSizeXy.getY() ) ;
					}
				}
				//	　(1.3.*.5)　Y列(ColumnType_Ressyabangou) の境界線の
				//	DcDrawオブジェクト に属性を設定。
				//	　(1.3.*.6)　Y列ColumnType_Ressyabangou) の境界線の
				//	高さを設定
				{
					CDcdGridYBorder* pCDcdGridYBorder 
						= pCDcdGridYColumn->getCDcdGridYBorder() ;
					Ou<CDcdLine> pCDcdLine = 
						pCDcdGridYBorder->getIfDcDraw() ;

					//	この駅の駅時刻形式が「着発」 AND
					//	この列が着で、次の列が発なら、下に罫線
					CdYColSpec aCdYColSpecNext  
						= m_CdYColSpecCont.ColumnNumberToSpec( 
							iYColumnNumber + 1 ) ;
					if ( aCdDedEki.getChakujikokuHyouji() &&
						aCdDedEki.getHatsujikokuHyouji() &&
						aCdYColSpec.getColumnType() 
							== aCdYColSpec.ColumnType_Ekijikoku_Chaku && 
						aCdYColSpecNext.getColumnType() 
							== aCdYColSpecNext.ColumnType_Ekijikoku_Hatsu && 
						aCdYColSpec.getEkiOrder() 
							== aCdYColSpecNext.getEkiOrder() )
					{
						pCDcdLine->setCdPenProp( 
							getCdPenPropNarrowLine() ) ;
					}
					//	次の列が異なる駅の列。 AND
					//	当駅に『境界線』属性がある。
					//
					//	これら条件を満たす場合は、
					//	下（次の駅との間）に太線
					else if ( aCdYColSpecNext.isEkiJikoku() 
						&& aCdYColSpec.getEkiOrder() 
							!= aCdYColSpecNext.getEkiOrder() 
						&& aCdDedEki.getKyoukaisen() ) 
					{
						//pCDcdLine->setCdPenProp( 
						//	getCdPenPropNarrowLine() ) ;
						pCDcdLine->setCdPenProp(getCdPenPropBoldLine());
					}
					//　次の列が同じ駅の番線表示、前作業、増結編成前作業なら下に罫線
					else if (aCdYColSpec.getEkiOrder() == aCdYColSpecNext.getEkiOrder() &&
						(aCdYColSpecNext.getColumnType() == aCdYColSpecNext.ColumnType_Track ||
							aCdYColSpecNext.getColumnType() == aCdYColSpecNext.ColumnType_BeforeOperation1 ||
							aCdYColSpecNext.getColumnType() == aCdYColSpecNext.ColumnType_BeforeOperationBefore1))
					{
						pCDcdLine->setCdPenProp(
							getCdPenPropNarrowLine());
					}
					//	次の列が路線外終着駅の場合は、罫線
					else if (aCdYColSpecNext.getColumnType() == aCdYColSpecNext.ColumnType_Outer_Shuchaku1)
					{
						pCDcdLine->setCdPenProp(
							getCdPenPropNarrowLine());
					}
					//	次の列が駅時刻以外の場合は、太線
					else if ( !aCdYColSpecNext.isEkiJikoku() )
					{
						pCDcdLine->setCdPenProp( getCdPenPropBoldLine() ) ;
					}
					else
					{
						pCDcdLine->setCdPenProp( getCdPenPropNullLine() ) ;
					}

					// --------------------------------
					//	線の幅から、列幅を設定
					CdDcdSizeXy aCdDcdSizeXy ;
					if ( pCDcdLine->getItemSize( 
						&aCDcdTarget , &aCdDcdSizeXy ) )
					{
						if (pCDcdLine->getCdPenProp().getLogicalunitWidth() >0)
						{
							pCDcdGridYBorder->setColumnBorderSize(
								aCdDcdSizeXy.getX());
						}
						else
						{
							pCDcdGridYBorder->setColumnBorderSize((DcdSize)0);
						}
					}
				}
			}
		}
	}
}

void CCellBuilder::update01_03_02_19_setEkimei_BeforeOperationBefore(
	CWndJikokuhyou* pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	CDcdTargetGetDC	aCDcdTarget(NULL);

	// --------------------------------
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou());

	// --------------------------------
	CdXColSpec aCdXColSpec(
		CdXColSpec::ColumnType_Ekimei);
	int iXColumnNumber =
		m_CdXColSpecCont.ColumnNumberFromSpec(aCdXColSpec);
	if (iXColumnNumber >= 0)
	{
		for (int iEkiOrder = 0; iEkiOrder < muCdDedEki->size();
			iEkiOrder++)
		{
			CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);

			if (aCdDedEki.getJikokuhyouBeforeOperationBefore())
			{
				CdYColSpec aCdYColSpec1(
					CdYColSpec::ColumnType_BeforeOperationBefore1,
					iEkiOrder);
				CdYColSpec aCdYColSpec2(
					CdYColSpec::ColumnType_BeforeOperationBefore2,
					iEkiOrder);
				CdYColSpec aCdYColSpec3(
					CdYColSpec::ColumnType_BeforeOperationBefore3,
					iEkiOrder);
				CdYColSpec aCdYColSpec4(
					CdYColSpec::ColumnType_BeforeOperationBefore4,
					iEkiOrder);
				int iYColumnNumber1 =
					m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec1, false);
				int iYColumnNumber2 =
					m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec2, false);
				int iYColumnNumber3 =
					m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec3, false);
				int iYColumnNumber4 =
					m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec4, false);
				CDcdGridCell* pCDcdGridCell1 = pCDcdGrid->getCell(
					iXColumnNumber, iYColumnNumber1);
				CDcdGridCell* pCDcdGridCell2 = pCDcdGrid->getCell(
					iXColumnNumber, iYColumnNumber2);
				CDcdGridCell* pCDcdGridCell3 = pCDcdGrid->getCell(
					iXColumnNumber, iYColumnNumber3);
				CDcdGridCell* pCDcdGridCell4 = pCDcdGrid->getCell(
					iXColumnNumber, iYColumnNumber4);

				typedef CDcdTextbox CDcDrawCell;
				Ou<CDcDrawCell> pCDcDrawCell1;
				Ou<CDcDrawCell> pCDcDrawCell2;
				Ou<CDcDrawCell> pCDcDrawCell3;
				Ou<CDcDrawCell> pCDcDrawCell4;
				if (pCDcdGridCell1 != 0)
				{
					//(1.3.*.1)　セルの結合セルの属性を設定。
					/**
						2.0Update
						・編集モード時
							同一駅の物は全て結合する(番線・後作業・発時刻)
					*/
					int iYCount = 1;
					for (int idxy = iYColumnNumber1 + 1; idxy < m_CdYColSpecCont.size(); idxy++)
					{
						CdYColSpec aCdYColSpecSearch
							= m_CdYColSpecCont.ColumnNumberToSpec(idxy);
						if (iEkiOrder == aCdYColSpecSearch.getEkiOrder())
						{
							iYCount++;
						}
						else
						{
							break;
						}
					}
					pCDcdGridCell1->setAttachCellCount(1, iYCount);

					//	(1.3.*.2)　セルのDcDrawオブジェクトの型を設定
					//	( CDcdTextbox とする)。
					{
						pCDcDrawCell1 = dynamic_castOu<CDcDrawCell>(
							pCDcdGridCell1->getIfDcDraw());
						pCDcDrawCell2 = dynamic_castOu<CDcDrawCell>(
							pCDcdGridCell2->getIfDcDraw());
						if (pCDcDrawCell1 == NULL)
						{
							pCDcDrawCell1 = OuNew<CDcDrawCell>(new CDcDrawCell);
							pCDcdGridCell1->setIfDcDraw(pCDcDrawCell1);
						}
						if (pCDcDrawCell2 == NULL)
						{
							pCDcDrawCell2 = OuNew<CDcDrawCell>(new CDcDrawCell);
							pCDcdGridCell2->setIfDcDraw(pCDcDrawCell2);
						}

						if (m_iEnableOperation > 1)
						{
							pCDcDrawCell3 = dynamic_castOu<CDcDrawCell>(
								pCDcdGridCell3->getIfDcDraw());
							if (pCDcDrawCell3 == NULL)
							{
								pCDcDrawCell3 = OuNew<CDcDrawCell>(new CDcDrawCell);
								pCDcdGridCell3->setIfDcDraw(pCDcDrawCell3);
							}
							if (m_bDisplayInOutLinkCode)
							{
								pCDcDrawCell4 = dynamic_castOu<CDcDrawCell>(
									pCDcdGridCell4->getIfDcDraw());
								if (pCDcDrawCell4 == NULL)
								{
									pCDcDrawCell4 = OuNew<CDcDrawCell>(new CDcDrawCell);
									pCDcdGridCell4->setIfDcDraw(pCDcDrawCell4);
								}
							}
						}
					}
					//(1.3.*.3)　セルのDcDrawオブジェクトに、属性を設定。
					{
						*pCDcDrawCell1 = createCDcdEkimei();
						pCDcDrawCell1->setText(aCdDedEki.getEkimei());
						*pCDcDrawCell2 = createCDcdEkimei();
						pCDcDrawCell2->setText(_T(""));
						if (m_iEnableOperation > 1)
						{
							*pCDcDrawCell3 = createCDcdEkimei();
							if (m_bDisplayInOutLinkCode)
							{
								*pCDcDrawCell4 = createCDcdEkimei();
							}
						}
					}
				}

				CDcdGridYColumn* pCDcdGridYColumn1 = pCDcdGrid->getYColumn(
					iYColumnNumber1);
				if (pCDcdGridYColumn1)
				{
					//(1.3.*.4)　Y列のセルの高さを設定
					{
						CdDcdSizeXy aCdDcdSizeXy;
						if (pCDcDrawCell1->getItemSize(
							&aCDcdTarget, &aCdDcdSizeXy))
						{
							pCDcdGridYColumn1->setColumnSize(
								aCdDcdSizeXy.getY());
						}
					}
					//	　(1.3.*.5)　Y列(ColumnType_Ressyabangou) の境界線の
					//	DcDrawオブジェクト に属性を設定。
					//	　(1.3.*.6)　Y列ColumnType_Ressyabangou) の境界線の
					//	高さを設定
					{
						CDcdGridYBorder* pCDcdGridYBorder1
							= pCDcdGridYColumn1->getCDcdGridYBorder();
						Ou<CDcdLine> pCDcdLine1 =
							pCDcdGridYBorder1->getIfDcDraw();
						pCDcdLine1->setCdPenProp(getCdPenPropNullLine());

						// --------------------------------
						//	線の幅から、列幅を設定
						CdDcdSizeXy aCdDcdSizeXy;
						if (pCDcdLine1->getItemSize(
							&aCDcdTarget, &aCdDcdSizeXy))
						{
							pCDcdGridYBorder1->setColumnBorderSize(
								aCdDcdSizeXy.getX());
						}
					}
				}

				CDcdGridYColumn* pCDcdGridYColumn2 = pCDcdGrid->getYColumn(
					iYColumnNumber2);
				if (pCDcdGridYColumn2)
				{
					//(1.3.*.4)　Y列のセルの高さを設定
					{
						CdDcdSizeXy aCdDcdSizeXy;
						if (pCDcDrawCell2->getItemSize(
							&aCDcdTarget, &aCdDcdSizeXy))
						{
							pCDcdGridYColumn2->setColumnSize(
								aCdDcdSizeXy.getY());
						}
					}
					//	　(1.3.*.5)　Y列(ColumnType_Ressyabangou) の境界線の
					//	DcDrawオブジェクト に属性を設定。
					//	　(1.3.*.6)　Y列ColumnType_Ressyabangou) の境界線の
					//	高さを設定
					{
						CDcdGridYBorder* pCDcdGridYBorder2
							= pCDcdGridYColumn2->getCDcdGridYBorder();
						Ou<CDcdLine> pCDcdLine2 =
							pCDcdGridYBorder2->getIfDcDraw();

						if (m_iEnableOperation > 1)
						{
							pCDcdLine2->setCdPenProp(getCdPenPropNullLine());
						}
						else
						{
							CdYColSpec aCdYColSpecNext
								= m_CdYColSpecCont.ColumnNumberToSpec(
									iYColumnNumber2 + 1);
							//	次の列が異なる駅の列。
							//	当駅に『境界線』属性がある。
							//
							//	これら条件を満たす場合は、
							//	下（次の駅との間）に罫線
							if ((aCdYColSpecNext.isEkiJikoku() ||
								aCdYColSpecNext.getColumnType() == aCdYColSpecNext.ColumnType_Track)
								&& aCdYColSpec2.getEkiOrder()
								!= aCdYColSpecNext.getEkiOrder()
								&& aCdDedEki.getKyoukaisen())
							{
								//pCDcdLine->setCdPenProp(
								//	getCdPenPropNarrowLine());
								//暫定的に境界線を太線にしてみる
								pCDcdLine2->setCdPenProp(getCdPenPropBoldLine());
							}
							//　次の列が同じ駅の前作業または番線なら罫線
							else if (aCdYColSpec2.getEkiOrder() == aCdYColSpecNext.getEkiOrder() &&
								(aCdYColSpecNext.getColumnType()
									== aCdYColSpecNext.ColumnType_Track ||
									aCdYColSpecNext.getColumnType()
									== aCdYColSpecNext.ColumnType_BeforeOperation1))
							{
								pCDcdLine2->setCdPenProp(getCdPenPropNarrowLine());
							}
							//　次の列が路線外終着駅欄なら罫線
							else if (aCdYColSpecNext.getColumnType()
								== aCdYColSpecNext.ColumnType_Outer_Shuchaku1)
							{
								pCDcdLine2->setCdPenProp(getCdPenPropNarrowLine());
							}
							//	次の列が駅時刻以外の場合は、太線
							else if (!aCdYColSpecNext.isEkiJikoku())
							{
								pCDcdLine2->setCdPenProp(getCdPenPropBoldLine());
							}
							else
							{
								pCDcdLine2->setCdPenProp(getCdPenPropNarrowLine());
							}
						}
						// --------------------------------
						//	線の幅から、列幅を設定
						CdDcdSizeXy aCdDcdSizeXy;
						if (pCDcdLine2->getItemSize(
							&aCDcdTarget, &aCdDcdSizeXy))
						{
							pCDcdGridYBorder2->setColumnBorderSize(
								aCdDcdSizeXy.getX());
						}
					}
				}

				CDcdGridYColumn* pCDcdGridYColumn3 = pCDcdGrid->getYColumn(
					iYColumnNumber3);
				if (pCDcdGridYColumn3)
				{
					//(1.3.*.4)　Y列のセルの高さを設定
					{
						CdDcdSizeXy aCdDcdSizeXy;
						if (pCDcDrawCell3->getItemSize(
							&aCDcdTarget, &aCdDcdSizeXy))
						{
							pCDcdGridYColumn3->setColumnSize(
								aCdDcdSizeXy.getY());
						}
					}
					//	　(1.3.*.5)　Y列(ColumnType_Ressyabangou) の境界線の
					//	DcDrawオブジェクト に属性を設定。
					//	　(1.3.*.6)　Y列ColumnType_Ressyabangou) の境界線の
					//	高さを設定
					{
						CDcdGridYBorder* pCDcdGridYBorder3
							= pCDcdGridYColumn3->getCDcdGridYBorder();
						Ou<CDcdLine> pCDcdLine3 =
							pCDcdGridYBorder3->getIfDcDraw();

						if (m_bDisplayInOutLinkCode)
						{
							pCDcdLine3->setCdPenProp(getCdPenPropNullLine());
						}
						else
						{
							CdYColSpec aCdYColSpecNext
								= m_CdYColSpecCont.ColumnNumberToSpec(
									iYColumnNumber3 + 1);
							//	次の列が異なる駅の列。
							//	当駅に『境界線』属性がある。
							//
							//	これら条件を満たす場合は、
							//	下（次の駅との間）に罫線
							if ((aCdYColSpecNext.isEkiJikoku() ||
								aCdYColSpecNext.getColumnType() == aCdYColSpecNext.ColumnType_Track)
								&& aCdYColSpec3.getEkiOrder()
								!= aCdYColSpecNext.getEkiOrder()
								&& aCdDedEki.getKyoukaisen())
							{
								//pCDcdLine->setCdPenProp(
								//	getCdPenPropNarrowLine());
								//暫定的に境界線を太線にしてみる
								pCDcdLine3->setCdPenProp(getCdPenPropBoldLine());
							}
							//　次の列が同じ駅の前作業または番線なら罫線
							else if (aCdYColSpec3.getEkiOrder() == aCdYColSpecNext.getEkiOrder() &&
								(aCdYColSpecNext.getColumnType()
									== aCdYColSpecNext.ColumnType_Track ||
									aCdYColSpecNext.getColumnType()
									== aCdYColSpecNext.ColumnType_BeforeOperation1))
							{
								pCDcdLine3->setCdPenProp(getCdPenPropNarrowLine());
							}
							//　次の列が路線外終着駅欄なら罫線
							else if (aCdYColSpecNext.getColumnType()
								== aCdYColSpecNext.ColumnType_Outer_Shuchaku1)
							{
								pCDcdLine3->setCdPenProp(getCdPenPropNarrowLine());
							}
							//	次の列が駅時刻以外の場合は、太線
							else if (!aCdYColSpecNext.isEkiJikoku())
							{
								pCDcdLine3->setCdPenProp(getCdPenPropBoldLine());
							}
							else
							{
								pCDcdLine3->setCdPenProp(getCdPenPropNarrowLine());
							}
						}

						// --------------------------------
						//	線の幅から、列幅を設定
						CdDcdSizeXy aCdDcdSizeXy;
						if (pCDcdLine3->getItemSize(
							&aCDcdTarget, &aCdDcdSizeXy))
						{
							pCDcdGridYBorder3->setColumnBorderSize(
								aCdDcdSizeXy.getX());
						}
					}
				}

				CDcdGridYColumn* pCDcdGridYColumn4 = pCDcdGrid->getYColumn(
					iYColumnNumber4);
				if (pCDcdGridYColumn4)
				{
					//(1.3.*.4)　Y列のセルの高さを設定
					{
						CdDcdSizeXy aCdDcdSizeXy;
						if (pCDcDrawCell4->getItemSize(
							&aCDcdTarget, &aCdDcdSizeXy))
						{
							pCDcdGridYColumn4->setColumnSize(
								aCdDcdSizeXy.getY());
						}
					}
					//	　(1.3.*.5)　Y列(ColumnType_Ressyabangou) の境界線の
					//	DcDrawオブジェクト に属性を設定。
					//	　(1.3.*.6)　Y列ColumnType_Ressyabangou) の境界線の
					//	高さを設定
					{
						CDcdGridYBorder* pCDcdGridYBorder4
							= pCDcdGridYColumn4->getCDcdGridYBorder();
						Ou<CDcdLine> pCDcdLine4 =
							pCDcdGridYBorder4->getIfDcDraw();

						CdYColSpec aCdYColSpecNext
							= m_CdYColSpecCont.ColumnNumberToSpec(
								iYColumnNumber4 + 1);
						//	次の列が異なる駅の列。
						//	当駅に『境界線』属性がある。
						//
						//	これら条件を満たす場合は、
						//	下（次の駅との間）に罫線
						if ((aCdYColSpecNext.isEkiJikoku() ||
							aCdYColSpecNext.getColumnType() == aCdYColSpecNext.ColumnType_Track)
							&& aCdYColSpec4.getEkiOrder()
							!= aCdYColSpecNext.getEkiOrder()
							&& aCdDedEki.getKyoukaisen())
						{
							//pCDcdLine->setCdPenProp(
							//	getCdPenPropNarrowLine());
							//暫定的に境界線を太線にしてみる
							pCDcdLine4->setCdPenProp(getCdPenPropBoldLine());
						}
						//　次の列が同じ駅の前作業または番線なら罫線
						else if (aCdYColSpec4.getEkiOrder() == aCdYColSpecNext.getEkiOrder() &&
							(aCdYColSpecNext.getColumnType()
								== aCdYColSpecNext.ColumnType_Track ||
								aCdYColSpecNext.getColumnType()
								== aCdYColSpecNext.ColumnType_BeforeOperation1))
						{
							pCDcdLine4->setCdPenProp(getCdPenPropNarrowLine());
						}
						//　次の列が路線外終着駅欄なら罫線
						else if (aCdYColSpecNext.getColumnType()
							== aCdYColSpecNext.ColumnType_Outer_Shuchaku1)
						{
							pCDcdLine4->setCdPenProp(getCdPenPropNarrowLine());
						}
						//	次の列が駅時刻以外の場合は、太線
						else if (!aCdYColSpecNext.isEkiJikoku())
						{
							pCDcdLine4->setCdPenProp(getCdPenPropBoldLine());
						}
						else
						{
							pCDcdLine4->setCdPenProp(getCdPenPropNarrowLine());
						}

						// --------------------------------
						//	線の幅から、列幅を設定
						CdDcdSizeXy aCdDcdSizeXy;
						if (pCDcdLine4->getItemSize(
							&aCDcdTarget, &aCdDcdSizeXy))
						{
							pCDcdGridYBorder4->setColumnBorderSize(
								aCdDcdSizeXy.getX());
						}
					}
				}
			}
		}
	}
}


void CCellBuilder::update01_03_02_17_setEkimei_BeforeOperation(
	CWndJikokuhyou * pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	CDcdTargetGetDC	aCDcdTarget(NULL);

	// --------------------------------
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou());

	// --------------------------------
	CdXColSpec aCdXColSpec(
		CdXColSpec::ColumnType_Ekimei);
	int iXColumnNumber =
		m_CdXColSpecCont.ColumnNumberFromSpec(aCdXColSpec);
	if (iXColumnNumber >= 0)
	{
		for (int iEkiOrder = 0; iEkiOrder < muCdDedEki->size();
			iEkiOrder++)
		{
			CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);

			for (int idx = 0;idx<aCdDedEki.getJikokuhyouBeforeOperation();idx++)
			{
				CdYColSpec aCdYColSpec1(
					CdYColSpec::ColumnType_BeforeOperation1,
					iEkiOrder,
					idx);
				CdYColSpec aCdYColSpec2(
					CdYColSpec::ColumnType_BeforeOperation2,
					iEkiOrder,
					idx);
				int iYColumnNumber1 =
					m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec1, false);
				int iYColumnNumber2 =
					m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec2, false);
				CDcdGridCell* pCDcdGridCell1 = pCDcdGrid->getCell(
					iXColumnNumber, iYColumnNumber1);
				CDcdGridCell* pCDcdGridCell2 = pCDcdGrid->getCell(
					iXColumnNumber, iYColumnNumber2);

				typedef CDcdTextbox CDcDrawCell;
				Ou<CDcDrawCell> pCDcDrawCell1;
				Ou<CDcDrawCell> pCDcDrawCell2;
				if (pCDcdGridCell1 != 0)
				{
					//(1.3.*.1)　セルの結合セルの属性を設定。
					/**
						2.0Update
						・編集モード時
							同一駅の物は全て結合する(番線・後作業・発時刻)
					*/
					int iYCount = 1;
					for (int idxy = iYColumnNumber1 + 1; idxy < m_CdYColSpecCont.size(); idxy++)
					{
						CdYColSpec aCdYColSpecSearch
							= m_CdYColSpecCont.ColumnNumberToSpec(idxy);
						if (iEkiOrder == aCdYColSpecSearch.getEkiOrder())
						{
							iYCount++;
						}
						else
						{
							break;
						}
					}
					pCDcdGridCell1->setAttachCellCount(1, iYCount);

					//	(1.3.*.2)　セルのDcDrawオブジェクトの型を設定
					//	( CDcdTextbox とする)。
					{
						pCDcDrawCell1 = dynamic_castOu<CDcDrawCell>(
							pCDcdGridCell1->getIfDcDraw());
						pCDcDrawCell2 = dynamic_castOu<CDcDrawCell>(
							pCDcdGridCell2->getIfDcDraw());
						if (pCDcDrawCell1 == NULL)
						{
							pCDcDrawCell1 = OuNew<CDcDrawCell>(new CDcDrawCell);
							pCDcdGridCell1->setIfDcDraw(pCDcDrawCell1);
						}
						if (pCDcDrawCell2 == NULL)
						{
							pCDcDrawCell2 = OuNew<CDcDrawCell>(new CDcDrawCell);
							pCDcdGridCell2->setIfDcDraw(pCDcDrawCell2);
						}
					}
					//(1.3.*.3)　セルのDcDrawオブジェクトに、属性を設定。
					{
						*pCDcDrawCell1 = createCDcdEkimei();
						pCDcDrawCell1->setText(aCdDedEki.getEkimei());
						*pCDcDrawCell2 = createCDcdEkimei();
						pCDcDrawCell2->setText(_T(""));
					}
				}

				CDcdGridYColumn* pCDcdGridYColumn1 = pCDcdGrid->getYColumn(
					iYColumnNumber1);
				if (pCDcdGridYColumn1)
				{
					//(1.3.*.4)　Y列のセルの高さを設定
					{
						CdDcdSizeXy aCdDcdSizeXy;
						if (pCDcDrawCell1->getItemSize(
							&aCDcdTarget, &aCdDcdSizeXy))
						{
							pCDcdGridYColumn1->setColumnSize(
								aCdDcdSizeXy.getY());
						}
					}
					//	　(1.3.*.5)　Y列(ColumnType_Ressyabangou) の境界線の
					//	DcDrawオブジェクト に属性を設定。
					//	　(1.3.*.6)　Y列ColumnType_Ressyabangou) の境界線の
					//	高さを設定
					{
						CDcdGridYBorder* pCDcdGridYBorder1
							= pCDcdGridYColumn1->getCDcdGridYBorder();
						Ou<CDcdLine> pCDcdLine1 =
							pCDcdGridYBorder1->getIfDcDraw();
						pCDcdLine1->setCdPenProp(getCdPenPropNullLine());

						// --------------------------------
						//	線の幅から、列幅を設定
						CdDcdSizeXy aCdDcdSizeXy;
						if (pCDcdLine1->getItemSize(
							&aCDcdTarget, &aCdDcdSizeXy))
						{
							pCDcdGridYBorder1->setColumnBorderSize(
								aCdDcdSizeXy.getX());
						}
					}
				}

				CDcdGridYColumn* pCDcdGridYColumn2 = pCDcdGrid->getYColumn(
					iYColumnNumber2);
				if (pCDcdGridYColumn2)
				{
					//(1.3.*.4)　Y列のセルの高さを設定
					{
						CdDcdSizeXy aCdDcdSizeXy;
						if (pCDcDrawCell2->getItemSize(
							&aCDcdTarget, &aCdDcdSizeXy))
						{
							pCDcdGridYColumn2->setColumnSize(
								aCdDcdSizeXy.getY());
						}
					}
					//	　(1.3.*.5)　Y列(ColumnType_Ressyabangou) の境界線の
					//	DcDrawオブジェクト に属性を設定。
					//	　(1.3.*.6)　Y列ColumnType_Ressyabangou) の境界線の
					//	高さを設定
					{
						CDcdGridYBorder* pCDcdGridYBorder2
							= pCDcdGridYColumn2->getCDcdGridYBorder();
						Ou<CDcdLine> pCDcdLine2 =
							pCDcdGridYBorder2->getIfDcDraw();

						CdYColSpec aCdYColSpecNext
							= m_CdYColSpecCont.ColumnNumberToSpec(
								iYColumnNumber2 + 1);
						//	次の列が異なる駅の列。
						//	当駅に『境界線』属性がある。
						//
						//	これら条件を満たす場合は、
						//	下（次の駅との間）に罫線
						if ((aCdYColSpecNext.isEkiJikoku() ||
							aCdYColSpecNext.getColumnType() == aCdYColSpecNext.ColumnType_Track)
							&& aCdYColSpec2.getEkiOrder()
							!= aCdYColSpecNext.getEkiOrder()
							&& aCdDedEki.getKyoukaisen())
						{
							//pCDcdLine->setCdPenProp(
							//	getCdPenPropNarrowLine());
							//暫定的に境界線を太線にしてみる
							pCDcdLine2->setCdPenProp(getCdPenPropBoldLine());
						}
						//　次の列が同じ駅の前作業、解結編成後作業または番線なら罫線
						else if (aCdYColSpec2.getEkiOrder() == aCdYColSpecNext.getEkiOrder() &&
							(aCdYColSpecNext.getColumnType()
							== aCdYColSpecNext.ColumnType_Track || 
							aCdYColSpecNext.getColumnType()
							== aCdYColSpecNext.ColumnType_BeforeOperation1 ||
							aCdYColSpecNext.getColumnType()
							== aCdYColSpecNext.ColumnType_BeforeOperationAfter1))
						{
							pCDcdLine2->setCdPenProp(getCdPenPropNarrowLine());
						}
						//　次の列が路線外終着駅欄なら罫線
						else if (aCdYColSpecNext.getColumnType()
							== aCdYColSpecNext.ColumnType_Outer_Shuchaku1)
						{
							pCDcdLine2->setCdPenProp(getCdPenPropNarrowLine());
						}
						//	次の列が駅時刻以外の場合は、太線
						else if (!aCdYColSpecNext.isEkiJikoku())
						{
							pCDcdLine2->setCdPenProp(getCdPenPropBoldLine());
						}
						else
						{
							pCDcdLine2->setCdPenProp(getCdPenPropNarrowLine());
						}

						// --------------------------------
						//	線の幅から、列幅を設定
						CdDcdSizeXy aCdDcdSizeXy;
						if (pCDcdLine2->getItemSize(
							&aCDcdTarget, &aCdDcdSizeXy))
						{
							pCDcdGridYBorder2->setColumnBorderSize(
								aCdDcdSizeXy.getX());
						}
					}
				}
			}
		}
	}
}

void CCellBuilder::update01_03_02_20_setEkimei_BeforeOperationAfter(
	CWndJikokuhyou* pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	CDcdTargetGetDC	aCDcdTarget(NULL);

	// --------------------------------
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou());

	// --------------------------------
	CdXColSpec aCdXColSpec(
		CdXColSpec::ColumnType_Ekimei);
	int iXColumnNumber =
		m_CdXColSpecCont.ColumnNumberFromSpec(aCdXColSpec);
	if (iXColumnNumber >= 0)
	{
		for (int iEkiOrder = 0; iEkiOrder < muCdDedEki->size();
			iEkiOrder++)
		{
			CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);

			if (aCdDedEki.getJikokuhyouBeforeOperationAfter())
			{
				CdYColSpec aCdYColSpec1(
					CdYColSpec::ColumnType_BeforeOperationAfter1,
					iEkiOrder);
				CdYColSpec aCdYColSpec2(
					CdYColSpec::ColumnType_BeforeOperationAfter2,
					iEkiOrder);
				CdYColSpec aCdYColSpec3(
					CdYColSpec::ColumnType_BeforeOperationAfter3,
					iEkiOrder);
				int iYColumnNumber1 =
					m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec1, false);
				int iYColumnNumber2 =
					m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec2, false);
				int iYColumnNumber3 =
					m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec3, false);
				CDcdGridCell* pCDcdGridCell1 = pCDcdGrid->getCell(
					iXColumnNumber, iYColumnNumber1);
				CDcdGridCell* pCDcdGridCell2 = pCDcdGrid->getCell(
					iXColumnNumber, iYColumnNumber2);
				CDcdGridCell* pCDcdGridCell3 = pCDcdGrid->getCell(
					iXColumnNumber, iYColumnNumber3);

				typedef CDcdTextbox CDcDrawCell;
				Ou<CDcDrawCell> pCDcDrawCell1;
				Ou<CDcDrawCell> pCDcDrawCell2;
				Ou<CDcDrawCell> pCDcDrawCell3;
				if (pCDcdGridCell1 != 0)
				{
					//(1.3.*.1)　セルの結合セルの属性を設定。
					/**
						2.0Update
						・編集モード時
							同一駅の物は全て結合する(番線・後作業・発時刻)
					*/
					int iYCount = 1;
					for (int idxy = iYColumnNumber1 + 1; idxy < m_CdYColSpecCont.size(); idxy++)
					{
						CdYColSpec aCdYColSpecSearch
							= m_CdYColSpecCont.ColumnNumberToSpec(idxy);
						if (iEkiOrder == aCdYColSpecSearch.getEkiOrder())
						{
							iYCount++;
						}
						else
						{
							break;
						}
					}
					pCDcdGridCell1->setAttachCellCount(1, iYCount);

					//	(1.3.*.2)　セルのDcDrawオブジェクトの型を設定
					//	( CDcdTextbox とする)。
					{
						pCDcDrawCell1 = dynamic_castOu<CDcDrawCell>(
							pCDcdGridCell1->getIfDcDraw());
						pCDcDrawCell2 = dynamic_castOu<CDcDrawCell>(
							pCDcdGridCell2->getIfDcDraw());
						if (pCDcDrawCell1 == NULL)
						{
							pCDcDrawCell1 = OuNew<CDcDrawCell>(new CDcDrawCell);
							pCDcdGridCell1->setIfDcDraw(pCDcDrawCell1);
						}
						if (pCDcDrawCell2 == NULL)
						{
							pCDcDrawCell2 = OuNew<CDcDrawCell>(new CDcDrawCell);
							pCDcdGridCell2->setIfDcDraw(pCDcDrawCell2);
						}
						if (m_iEnableOperation > 1 && m_bDisplayInOutLinkCode)
						{
							pCDcDrawCell3 = dynamic_castOu<CDcDrawCell>(
								pCDcdGridCell3->getIfDcDraw());
							if (pCDcDrawCell3 == NULL)
							{
								pCDcDrawCell3 = OuNew<CDcDrawCell>(new CDcDrawCell);
								pCDcdGridCell3->setIfDcDraw(pCDcDrawCell3);
							}
						}
					}
					//(1.3.*.3)　セルのDcDrawオブジェクトに、属性を設定。
					{
						*pCDcDrawCell1 = createCDcdEkimei();
						pCDcDrawCell1->setText(aCdDedEki.getEkimei());
						*pCDcDrawCell2 = createCDcdEkimei();
						pCDcDrawCell2->setText(_T(""));
						if (m_iEnableOperation > 1 && m_bDisplayInOutLinkCode)
						{
							*pCDcDrawCell3 = createCDcdEkimei();
							pCDcDrawCell3->setText(_T(""));
						}
					}
				}

				CDcdGridYColumn* pCDcdGridYColumn1 = pCDcdGrid->getYColumn(
					iYColumnNumber1);
				if (pCDcdGridYColumn1)
				{
					//(1.3.*.4)　Y列のセルの高さを設定
					{
						CdDcdSizeXy aCdDcdSizeXy;
						if (pCDcDrawCell1->getItemSize(
							&aCDcdTarget, &aCdDcdSizeXy))
						{
							pCDcdGridYColumn1->setColumnSize(
								aCdDcdSizeXy.getY());
						}
					}
					//	　(1.3.*.5)　Y列(ColumnType_Ressyabangou) の境界線の
					//	DcDrawオブジェクト に属性を設定。
					//	　(1.3.*.6)　Y列ColumnType_Ressyabangou) の境界線の
					//	高さを設定
					{
						CDcdGridYBorder* pCDcdGridYBorder1
							= pCDcdGridYColumn1->getCDcdGridYBorder();
						Ou<CDcdLine> pCDcdLine1 =
							pCDcdGridYBorder1->getIfDcDraw();
						pCDcdLine1->setCdPenProp(getCdPenPropNullLine());

						// --------------------------------
						//	線の幅から、列幅を設定
						CdDcdSizeXy aCdDcdSizeXy;
						if (pCDcdLine1->getItemSize(
							&aCDcdTarget, &aCdDcdSizeXy))
						{
							pCDcdGridYBorder1->setColumnBorderSize(
								aCdDcdSizeXy.getX());
						}
					}
				}

				CDcdGridYColumn* pCDcdGridYColumn2 = pCDcdGrid->getYColumn(
					iYColumnNumber2);
				if (pCDcdGridYColumn2)
				{
					//(1.3.*.4)　Y列のセルの高さを設定
					{
						CdDcdSizeXy aCdDcdSizeXy;
						if (pCDcDrawCell2->getItemSize(
							&aCDcdTarget, &aCdDcdSizeXy))
						{
							pCDcdGridYColumn2->setColumnSize(
								aCdDcdSizeXy.getY());
						}
					}
					//	　(1.3.*.5)　Y列(ColumnType_Ressyabangou) の境界線の
					//	DcDrawオブジェクト に属性を設定。
					//	　(1.3.*.6)　Y列ColumnType_Ressyabangou) の境界線の
					//	高さを設定
					{
						CDcdGridYBorder* pCDcdGridYBorder2
							= pCDcdGridYColumn2->getCDcdGridYBorder();
						Ou<CDcdLine> pCDcdLine2 =
							pCDcdGridYBorder2->getIfDcDraw();

						if (m_iEnableOperation > 1 && m_bDisplayInOutLinkCode)
						{
							pCDcdLine2->setCdPenProp(getCdPenPropNullLine());
						}
						else
						{
							CdYColSpec aCdYColSpecNext
								= m_CdYColSpecCont.ColumnNumberToSpec(
									iYColumnNumber2 + 1);
							//	次の列が異なる駅の列。
							//	当駅に『境界線』属性がある。
							//
							//	これら条件を満たす場合は、
							//	下（次の駅との間）に罫線
							if ((aCdYColSpecNext.isEkiJikoku() ||
								aCdYColSpecNext.getColumnType() == aCdYColSpecNext.ColumnType_Track)
								&& aCdYColSpec2.getEkiOrder()
								!= aCdYColSpecNext.getEkiOrder()
								&& aCdDedEki.getKyoukaisen())
							{
								//pCDcdLine->setCdPenProp(
								//	getCdPenPropNarrowLine());
								//暫定的に境界線を太線にしてみる
								pCDcdLine2->setCdPenProp(getCdPenPropBoldLine());
							}
							//　次の列が同じ駅の前作業または番線なら罫線
							else if (aCdYColSpec2.getEkiOrder() == aCdYColSpecNext.getEkiOrder() &&
								(aCdYColSpecNext.getColumnType()
									== aCdYColSpecNext.ColumnType_Track ||
									aCdYColSpecNext.getColumnType()
									== aCdYColSpecNext.ColumnType_BeforeOperation1))
							{
								pCDcdLine2->setCdPenProp(getCdPenPropNarrowLine());
							}
							//　次の列が路線外終着駅欄なら罫線
							else if (aCdYColSpecNext.getColumnType()
								== aCdYColSpecNext.ColumnType_Outer_Shuchaku1)
							{
								pCDcdLine2->setCdPenProp(getCdPenPropNarrowLine());
							}
							//	次の列が駅時刻以外の場合は、太線
							else if (!aCdYColSpecNext.isEkiJikoku())
							{
								pCDcdLine2->setCdPenProp(getCdPenPropBoldLine());
							}
							else
							{
								pCDcdLine2->setCdPenProp(getCdPenPropNarrowLine());
							}
						}

						// --------------------------------
						//	線の幅から、列幅を設定
						CdDcdSizeXy aCdDcdSizeXy;
						if (pCDcdLine2->getItemSize(
							&aCDcdTarget, &aCdDcdSizeXy))
						{
							pCDcdGridYBorder2->setColumnBorderSize(
								aCdDcdSizeXy.getX());
						}
					}
				}

				CDcdGridYColumn* pCDcdGridYColumn3 = pCDcdGrid->getYColumn(
					iYColumnNumber3);
				if (pCDcdGridYColumn3)
				{
					//(1.3.*.4)　Y列のセルの高さを設定
					{
						CdDcdSizeXy aCdDcdSizeXy;
						if (pCDcDrawCell3->getItemSize(
							&aCDcdTarget, &aCdDcdSizeXy))
						{
							pCDcdGridYColumn3->setColumnSize(
								aCdDcdSizeXy.getY());
						}
					}
					//	　(1.3.*.5)　Y列(ColumnType_Ressyabangou) の境界線の
					//	DcDrawオブジェクト に属性を設定。
					//	　(1.3.*.6)　Y列ColumnType_Ressyabangou) の境界線の
					//	高さを設定
					{
						CDcdGridYBorder* pCDcdGridYBorder3
							= pCDcdGridYColumn3->getCDcdGridYBorder();
						Ou<CDcdLine> pCDcdLine3 =
							pCDcdGridYBorder3->getIfDcDraw();

						CdYColSpec aCdYColSpecNext
							= m_CdYColSpecCont.ColumnNumberToSpec(
								iYColumnNumber3 + 1);
						//	次の列が異なる駅の列。
						//	当駅に『境界線』属性がある。
						//
						//	これら条件を満たす場合は、
						//	下（次の駅との間）に罫線
						if ((aCdYColSpecNext.isEkiJikoku() ||
							aCdYColSpecNext.getColumnType() == aCdYColSpecNext.ColumnType_Track)
							&& aCdYColSpec3.getEkiOrder()
							!= aCdYColSpecNext.getEkiOrder()
							&& aCdDedEki.getKyoukaisen())
						{
							//pCDcdLine->setCdPenProp(
							//	getCdPenPropNarrowLine());
							//暫定的に境界線を太線にしてみる
							pCDcdLine3->setCdPenProp(getCdPenPropBoldLine());
						}
						//　次の列が同じ駅の前作業または番線なら罫線
						else if (aCdYColSpec3.getEkiOrder() == aCdYColSpecNext.getEkiOrder() &&
							(aCdYColSpecNext.getColumnType()
								== aCdYColSpecNext.ColumnType_Track ||
								aCdYColSpecNext.getColumnType()
								== aCdYColSpecNext.ColumnType_BeforeOperation1))
						{
							pCDcdLine3->setCdPenProp(getCdPenPropNarrowLine());
						}
						//　次の列が路線外終着駅欄なら罫線
						else if (aCdYColSpecNext.getColumnType()
							== aCdYColSpecNext.ColumnType_Outer_Shuchaku1)
						{
							pCDcdLine3->setCdPenProp(getCdPenPropNarrowLine());
						}
						//	次の列が駅時刻以外の場合は、太線
						else if (!aCdYColSpecNext.isEkiJikoku())
						{
							pCDcdLine3->setCdPenProp(getCdPenPropBoldLine());
						}
						else
						{
							pCDcdLine3->setCdPenProp(getCdPenPropNarrowLine());
						}

						// --------------------------------
						//	線の幅から、列幅を設定
						CdDcdSizeXy aCdDcdSizeXy;
						if (pCDcdLine3->getItemSize(
							&aCDcdTarget, &aCdDcdSizeXy))
						{
							pCDcdGridYBorder3->setColumnBorderSize(
								aCdDcdSizeXy.getX());
						}
					}
				}
			}
		}
	}
}

void CCellBuilder::update01_03_02_09_setEkimei_Track(
	CWndJikokuhyou* pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	CDcdTargetGetDC	aCDcdTarget(NULL);

	// --------------------------------
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou());

	// --------------------------------
	CdXColSpec aCdXColSpec(
		CdXColSpec::ColumnType_Ekimei);
	int iXColumnNumber =
		m_CdXColSpecCont.ColumnNumberFromSpec(aCdXColSpec);
	if (iXColumnNumber >= 0)
	{
		for (int iEkiOrder = 0; iEkiOrder < muCdDedEki->size();
			iEkiOrder++)
		{
			CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);

			CdYColSpec aCdYColSpec(
				CdYColSpec::ColumnType_Track,
				iEkiOrder);
			int iYColumnNumber =
				m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec, false);
			CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell(
				iXColumnNumber, iYColumnNumber);

			typedef CDcdTextbox CDcDrawCell;
			Ou<CDcDrawCell> pCDcDrawCell;
			if (pCDcdGridCell != 0)
			{
				//(1.3.*.1)　セルの結合セルの属性を設定。
				/**
					2.0Update
					・編集モード時
						同一駅の物は全て結合する(後作業・発時刻)
				*/
				int iYCount = 1;
				for (int idxy = iYColumnNumber + 1; idxy < m_CdYColSpecCont.size(); idxy++)
				{
					CdYColSpec aCdYColSpecSearch
						= m_CdYColSpecCont.ColumnNumberToSpec(idxy);
					if (iEkiOrder == aCdYColSpecSearch.getEkiOrder())
					{
						iYCount++;
					}
					else
					{
						break;
					}
				}
				pCDcdGridCell->setAttachCellCount(1, iYCount);

				//	(1.3.*.2)　セルのDcDrawオブジェクトの型を設定
				//	( CDcdTextbox とする)。
				{
					pCDcDrawCell = dynamic_castOu<CDcDrawCell>(
						pCDcdGridCell->getIfDcDraw());
					if (pCDcDrawCell == NULL)
					{
						pCDcDrawCell = OuNew<CDcDrawCell>(new CDcDrawCell);
						pCDcdGridCell->setIfDcDraw(pCDcDrawCell);
					}
				}
				//(1.3.*.3)　セルのDcDrawオブジェクトに、属性を設定。
				{
					*pCDcDrawCell = createCDcdEkimei();
					pCDcDrawCell->setText(aCdDedEki.getEkimei());
				}
			}

			CDcdGridYColumn* pCDcdGridYColumn = pCDcdGrid->getYColumn(
				iYColumnNumber);
			if (pCDcdGridYColumn)
			{
				//(1.3.*.4)　Y列のセルの高さを設定
				{
					CdDcdSizeXy aCdDcdSizeXy;
					if (pCDcDrawCell->getItemSize(
						&aCDcdTarget, &aCdDcdSizeXy))
					{
						pCDcdGridYColumn->setColumnSize(
							aCdDcdSizeXy.getY());
					}
				}
				//	　(1.3.*.5)　Y列(ColumnType_Ressyabangou) の境界線の
				//	DcDrawオブジェクト に属性を設定。
				//	　(1.3.*.6)　Y列ColumnType_Ressyabangou) の境界線の
				//	高さを設定
				{
					CDcdGridYBorder* pCDcdGridYBorder
						= pCDcdGridYColumn->getCDcdGridYBorder();
					Ou<CDcdLine> pCDcdLine =
						pCDcdGridYBorder->getIfDcDraw();

					CdYColSpec aCdYColSpecNext
						= m_CdYColSpecCont.ColumnNumberToSpec(
							iYColumnNumber + 1);
					//	次の列が異なる駅の列。
					//	当駅に『境界線』属性がある。
					//
					//	これら条件を満たす場合は、
					//	下（次の駅との間）に罫線
					if ((aCdYColSpecNext.isEkiJikoku() ||
						aCdYColSpecNext.getColumnType() == aCdYColSpecNext.ColumnType_Track)
						&& aCdYColSpec.getEkiOrder()
						!= aCdYColSpecNext.getEkiOrder()
						&& aCdDedEki.getKyoukaisen())
					{
						//pCDcdLine->setCdPenProp(
						//	getCdPenPropNarrowLine());
						//暫定的に境界線を太線にしてみる
						pCDcdLine->setCdPenProp(getCdPenPropBoldLine());
					}
					//　次の列が同じ駅の発時刻、後作業、増結編成前作業なら罫線
					else if (aCdYColSpec.getEkiOrder()== aCdYColSpecNext.getEkiOrder() &&
						(aCdYColSpecNext.getColumnType()
						== aCdYColSpecNext.ColumnType_Ekijikoku_Hatsu ||
							aCdYColSpecNext.getColumnType()
							== aCdYColSpecNext.ColumnType_AfterOperation1 ||
							aCdYColSpecNext.getColumnType()
							== aCdYColSpecNext.ColumnType_AfterOperationBefore1))
					{
						pCDcdLine->setCdPenProp(getCdPenPropNarrowLine());
					}
					//　次の列が路線外終着駅欄なら罫線
					else if (aCdYColSpecNext.getColumnType()
						== aCdYColSpecNext.ColumnType_Outer_Shuchaku1)
					{
						pCDcdLine->setCdPenProp(getCdPenPropNarrowLine());
					}
					//	次の列が駅時刻以外の場合は、太線
					else if (!aCdYColSpecNext.isEkiJikoku())
					{
						pCDcdLine->setCdPenProp(getCdPenPropBoldLine());
					}
					//次の列が次の駅で、この駅または次の駅の行数が4以上の場合は、破線
					else if (aCdYColSpec.getEkiOrder() + 1
						== aCdYColSpecNext.getEkiOrder())
					{
						CdYColSpec aCdYColSpecBackward
							= m_CdYColSpecCont.ColumnNumberToSpec(
								iYColumnNumber - 3);
						CdYColSpec aCdYColSpecForward
							= m_CdYColSpecCont.ColumnNumberToSpec(
								iYColumnNumber + 4);
						if (aCdYColSpec.getEkiOrder()
							== aCdYColSpecBackward.getEkiOrder())
						{
							pCDcdLine->setCdPenProp(getCdPenPropDotLine());
						}
						else if (aCdYColSpec.getEkiOrder() + 1
							== aCdYColSpecForward.getEkiOrder())
						{
							pCDcdLine->setCdPenProp(getCdPenPropDotLine());
						}
						else
						{
							pCDcdLine->setCdPenProp(getCdPenPropNullLine());
						}
					}
					else
					{
						pCDcdLine->setCdPenProp(getCdPenPropNullLine());
					}

					// --------------------------------
					//	線の幅から、列幅を設定
					CdDcdSizeXy aCdDcdSizeXy;
					if (pCDcdLine->getItemSize(
						&aCDcdTarget, &aCdDcdSizeXy))
					{
						pCDcdGridYBorder->setColumnBorderSize(
							aCdDcdSizeXy.getX());
					}
				}
			}
		}
	}
}

void CCellBuilder::update01_03_02_21_setEkimei_AfterOperationBefore(
	CWndJikokuhyou* pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	CDcdTargetGetDC	aCDcdTarget(NULL);

	// --------------------------------
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou());

	// --------------------------------
	CdXColSpec aCdXColSpec(
		CdXColSpec::ColumnType_Ekimei);
	int iXColumnNumber =
		m_CdXColSpecCont.ColumnNumberFromSpec(aCdXColSpec);
	if (iXColumnNumber >= 0)
	{
		for (int iEkiOrder = 0; iEkiOrder < muCdDedEki->size();
			iEkiOrder++)
		{
			CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);

			if (aCdDedEki.getJikokuhyouAfterOperationBefore())
			{
				CdYColSpec aCdYColSpec1(
					CdYColSpec::ColumnType_AfterOperationBefore1,
					iEkiOrder);
				CdYColSpec aCdYColSpec2(
					CdYColSpec::ColumnType_AfterOperationBefore2,
					iEkiOrder);
				CdYColSpec aCdYColSpec3(
					CdYColSpec::ColumnType_AfterOperationBefore3,
					iEkiOrder);
				CdYColSpec aCdYColSpec4(
					CdYColSpec::ColumnType_AfterOperationBefore4,
					iEkiOrder);
				int iYColumnNumber1 =
					m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec1, false);
				int iYColumnNumber2 =
					m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec2, false);
				int iYColumnNumber3 =
					m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec3, false);
				int iYColumnNumber4 =
					m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec4, false);
				CDcdGridCell* pCDcdGridCell1 = pCDcdGrid->getCell(
					iXColumnNumber, iYColumnNumber1);
				CDcdGridCell* pCDcdGridCell2 = pCDcdGrid->getCell(
					iXColumnNumber, iYColumnNumber2);
				CDcdGridCell* pCDcdGridCell3 = pCDcdGrid->getCell(
					iXColumnNumber, iYColumnNumber3);
				CDcdGridCell* pCDcdGridCell4 = pCDcdGrid->getCell(
					iXColumnNumber, iYColumnNumber4);

				typedef CDcdTextbox CDcDrawCell;
				Ou<CDcDrawCell> pCDcDrawCell1;
				Ou<CDcDrawCell> pCDcDrawCell2;
				Ou<CDcDrawCell> pCDcDrawCell3;
				Ou<CDcDrawCell> pCDcDrawCell4;
				if (pCDcdGridCell1 != 0)
				{
					//(1.3.*.1)　セルの結合セルの属性を設定。
					/**
						2.0Update
						・編集モード時
							同一駅の物は全て結合する(番線・後作業・発時刻)
					*/
					int iYCount = 1;
					for (int idxy = iYColumnNumber1 + 1; idxy < m_CdYColSpecCont.size(); idxy++)
					{
						CdYColSpec aCdYColSpecSearch
							= m_CdYColSpecCont.ColumnNumberToSpec(idxy);
						if (iEkiOrder == aCdYColSpecSearch.getEkiOrder())
						{
							iYCount++;
						}
						else
						{
							break;
						}
					}
					pCDcdGridCell1->setAttachCellCount(1, iYCount);

					//	(1.3.*.2)　セルのDcDrawオブジェクトの型を設定
					//	( CDcdTextbox とする)。
					{
						pCDcDrawCell1 = dynamic_castOu<CDcDrawCell>(
							pCDcdGridCell1->getIfDcDraw());
						pCDcDrawCell2 = dynamic_castOu<CDcDrawCell>(
							pCDcdGridCell2->getIfDcDraw());
						if (pCDcDrawCell1 == NULL)
						{
							pCDcDrawCell1 = OuNew<CDcDrawCell>(new CDcDrawCell);
							pCDcdGridCell1->setIfDcDraw(pCDcDrawCell1);
						}
						if (pCDcDrawCell2 == NULL)
						{
							pCDcDrawCell2 = OuNew<CDcDrawCell>(new CDcDrawCell);
							pCDcdGridCell2->setIfDcDraw(pCDcDrawCell2);
						}

						if (m_iEnableOperation > 1)
						{
							pCDcDrawCell3 = dynamic_castOu<CDcDrawCell>(
								pCDcdGridCell3->getIfDcDraw());
							if (pCDcDrawCell3 == NULL)
							{
								pCDcDrawCell3 = OuNew<CDcDrawCell>(new CDcDrawCell);
								pCDcdGridCell3->setIfDcDraw(pCDcDrawCell3);
							}
							if (m_bDisplayInOutLinkCode)
							{
								pCDcDrawCell4 = dynamic_castOu<CDcDrawCell>(
									pCDcdGridCell4->getIfDcDraw());
								if (pCDcDrawCell4 == NULL)
								{
									pCDcDrawCell4 = OuNew<CDcDrawCell>(new CDcDrawCell);
									pCDcdGridCell4->setIfDcDraw(pCDcDrawCell4);
								}
							}
						}
					}
					//(1.3.*.3)　セルのDcDrawオブジェクトに、属性を設定。
					{
						*pCDcDrawCell1 = createCDcdEkimei();
						pCDcDrawCell1->setText(aCdDedEki.getEkimei());
						*pCDcDrawCell2 = createCDcdEkimei();
						pCDcDrawCell2->setText(_T(""));
						if (m_iEnableOperation > 1)
						{
							*pCDcDrawCell3 = createCDcdEkimei();
							if (m_bDisplayInOutLinkCode)
							{
								*pCDcDrawCell4 = createCDcdEkimei();
							}
						}
					}
				}

				CDcdGridYColumn* pCDcdGridYColumn1 = pCDcdGrid->getYColumn(
					iYColumnNumber1);
				if (pCDcdGridYColumn1)
				{
					//(1.3.*.4)　Y列のセルの高さを設定
					{
						CdDcdSizeXy aCdDcdSizeXy;
						if (pCDcDrawCell1->getItemSize(
							&aCDcdTarget, &aCdDcdSizeXy))
						{
							pCDcdGridYColumn1->setColumnSize(
								aCdDcdSizeXy.getY());
						}
					}
					//	　(1.3.*.5)　Y列(ColumnType_Ressyabangou) の境界線の
					//	DcDrawオブジェクト に属性を設定。
					//	　(1.3.*.6)　Y列ColumnType_Ressyabangou) の境界線の
					//	高さを設定
					{
						CDcdGridYBorder* pCDcdGridYBorder1
							= pCDcdGridYColumn1->getCDcdGridYBorder();
						Ou<CDcdLine> pCDcdLine1 =
							pCDcdGridYBorder1->getIfDcDraw();
						pCDcdLine1->setCdPenProp(getCdPenPropNullLine());

						// --------------------------------
						//	線の幅から、列幅を設定
						CdDcdSizeXy aCdDcdSizeXy;
						if (pCDcdLine1->getItemSize(
							&aCDcdTarget, &aCdDcdSizeXy))
						{
							pCDcdGridYBorder1->setColumnBorderSize(
								aCdDcdSizeXy.getX());
						}
					}
				}

				CDcdGridYColumn* pCDcdGridYColumn2 = pCDcdGrid->getYColumn(
					iYColumnNumber2);
				if (pCDcdGridYColumn2)
				{
					//(1.3.*.4)　Y列のセルの高さを設定
					{
						CdDcdSizeXy aCdDcdSizeXy;
						if (pCDcDrawCell2->getItemSize(
							&aCDcdTarget, &aCdDcdSizeXy))
						{
							pCDcdGridYColumn2->setColumnSize(
								aCdDcdSizeXy.getY());
						}
					}
					//	　(1.3.*.5)　Y列(ColumnType_Ressyabangou) の境界線の
					//	DcDrawオブジェクト に属性を設定。
					//	　(1.3.*.6)　Y列ColumnType_Ressyabangou) の境界線の
					//	高さを設定
					{
						CDcdGridYBorder* pCDcdGridYBorder2
							= pCDcdGridYColumn2->getCDcdGridYBorder();
						Ou<CDcdLine> pCDcdLine2 =
							pCDcdGridYBorder2->getIfDcDraw();

						if (m_iEnableOperation > 1)
						{
							pCDcdLine2->setCdPenProp(getCdPenPropNullLine());
						}
						else
						{
							CdYColSpec aCdYColSpecNext
								= m_CdYColSpecCont.ColumnNumberToSpec(
									iYColumnNumber2 + 1);
							//	次の列が異なる駅の列。
							//	当駅に『境界線』属性がある。
							//
							//	これら条件を満たす場合は、
							//	下（次の駅との間）に罫線
							if ((aCdYColSpecNext.isEkiJikoku() ||
								aCdYColSpecNext.getColumnType() == aCdYColSpecNext.ColumnType_Track)
								&& aCdYColSpec2.getEkiOrder()
								!= aCdYColSpecNext.getEkiOrder()
								&& aCdDedEki.getKyoukaisen())
							{
								//pCDcdLine->setCdPenProp(
								//	getCdPenPropNarrowLine());
								//暫定的に境界線を太線にしてみる
								pCDcdLine2->setCdPenProp(getCdPenPropBoldLine());
							}
							//　次の列が同じ駅の後作業なら罫線
							else if (aCdYColSpec2.getEkiOrder() == aCdYColSpecNext.getEkiOrder() &&
								aCdYColSpecNext.getColumnType()
									== aCdYColSpecNext.ColumnType_AfterOperation1)
							{
								pCDcdLine2->setCdPenProp(getCdPenPropNarrowLine());
							}
							//　次の列が路線外終着駅欄なら罫線
							else if (aCdYColSpecNext.getColumnType()
								== aCdYColSpecNext.ColumnType_Outer_Shuchaku1)
							{
								pCDcdLine2->setCdPenProp(getCdPenPropNarrowLine());
							}
							//	次の列が駅時刻以外の場合は、太線
							else if (!aCdYColSpecNext.isEkiJikoku())
							{
								pCDcdLine2->setCdPenProp(getCdPenPropBoldLine());
							}
							else
							{
								pCDcdLine2->setCdPenProp(getCdPenPropNarrowLine());
							}
						}
						// --------------------------------
						//	線の幅から、列幅を設定
						CdDcdSizeXy aCdDcdSizeXy;
						if (pCDcdLine2->getItemSize(
							&aCDcdTarget, &aCdDcdSizeXy))
						{
							pCDcdGridYBorder2->setColumnBorderSize(
								aCdDcdSizeXy.getX());
						}
					}
				}

				CDcdGridYColumn* pCDcdGridYColumn3 = pCDcdGrid->getYColumn(
					iYColumnNumber3);
				if (pCDcdGridYColumn3)
				{
					//(1.3.*.4)　Y列のセルの高さを設定
					{
						CdDcdSizeXy aCdDcdSizeXy;
						if (pCDcDrawCell3->getItemSize(
							&aCDcdTarget, &aCdDcdSizeXy))
						{
							pCDcdGridYColumn3->setColumnSize(
								aCdDcdSizeXy.getY());
						}
					}
					//	　(1.3.*.5)　Y列(ColumnType_Ressyabangou) の境界線の
					//	DcDrawオブジェクト に属性を設定。
					//	　(1.3.*.6)　Y列ColumnType_Ressyabangou) の境界線の
					//	高さを設定
					{
						CDcdGridYBorder* pCDcdGridYBorder3
							= pCDcdGridYColumn3->getCDcdGridYBorder();
						Ou<CDcdLine> pCDcdLine3 =
							pCDcdGridYBorder3->getIfDcDraw();

						if (m_bDisplayInOutLinkCode)
						{
							pCDcdLine3->setCdPenProp(getCdPenPropNullLine());
						}
						else
						{
							CdYColSpec aCdYColSpecNext
								= m_CdYColSpecCont.ColumnNumberToSpec(
									iYColumnNumber3 + 1);
							//	次の列が異なる駅の列。
							//	当駅に『境界線』属性がある。
							//
							//	これら条件を満たす場合は、
							//	下（次の駅との間）に罫線
							if ((aCdYColSpecNext.isEkiJikoku() ||
								aCdYColSpecNext.getColumnType() == aCdYColSpecNext.ColumnType_Track)
								&& aCdYColSpec3.getEkiOrder()
								!= aCdYColSpecNext.getEkiOrder()
								&& aCdDedEki.getKyoukaisen())
							{
								//pCDcdLine->setCdPenProp(
								//	getCdPenPropNarrowLine());
								//暫定的に境界線を太線にしてみる
								pCDcdLine3->setCdPenProp(getCdPenPropBoldLine());
							}
							//　次の列が同じ駅の後作業なら罫線
							else if (aCdYColSpec3.getEkiOrder() == aCdYColSpecNext.getEkiOrder() &&
								aCdYColSpecNext.getColumnType()
								== aCdYColSpecNext.ColumnType_AfterOperation1)
							{
								pCDcdLine3->setCdPenProp(getCdPenPropNarrowLine());
							}
							//　次の列が路線外終着駅欄なら罫線
							else if (aCdYColSpecNext.getColumnType()
								== aCdYColSpecNext.ColumnType_Outer_Shuchaku1)
							{
								pCDcdLine3->setCdPenProp(getCdPenPropNarrowLine());
							}
							//	次の列が駅時刻以外の場合は、太線
							else if (!aCdYColSpecNext.isEkiJikoku())
							{
								pCDcdLine3->setCdPenProp(getCdPenPropBoldLine());
							}
							else
							{
								pCDcdLine3->setCdPenProp(getCdPenPropNarrowLine());
							}
						}

						// --------------------------------
						//	線の幅から、列幅を設定
						CdDcdSizeXy aCdDcdSizeXy;
						if (pCDcdLine3->getItemSize(
							&aCDcdTarget, &aCdDcdSizeXy))
						{
							pCDcdGridYBorder3->setColumnBorderSize(
								aCdDcdSizeXy.getX());
						}
					}
				}

				CDcdGridYColumn* pCDcdGridYColumn4 = pCDcdGrid->getYColumn(
					iYColumnNumber4);
				if (pCDcdGridYColumn4)
				{
					//(1.3.*.4)　Y列のセルの高さを設定
					{
						CdDcdSizeXy aCdDcdSizeXy;
						if (pCDcDrawCell4->getItemSize(
							&aCDcdTarget, &aCdDcdSizeXy))
						{
							pCDcdGridYColumn4->setColumnSize(
								aCdDcdSizeXy.getY());
						}
					}
					//	　(1.3.*.5)　Y列(ColumnType_Ressyabangou) の境界線の
					//	DcDrawオブジェクト に属性を設定。
					//	　(1.3.*.6)　Y列ColumnType_Ressyabangou) の境界線の
					//	高さを設定
					{
						CDcdGridYBorder* pCDcdGridYBorder4
							= pCDcdGridYColumn4->getCDcdGridYBorder();
						Ou<CDcdLine> pCDcdLine4 =
							pCDcdGridYBorder4->getIfDcDraw();

						CdYColSpec aCdYColSpecNext
							= m_CdYColSpecCont.ColumnNumberToSpec(
								iYColumnNumber4 + 1);
						//	次の列が異なる駅の列。
						//	当駅に『境界線』属性がある。
						//
						//	これら条件を満たす場合は、
						//	下（次の駅との間）に罫線
						if ((aCdYColSpecNext.isEkiJikoku() ||
							aCdYColSpecNext.getColumnType() == aCdYColSpecNext.ColumnType_Track)
							&& aCdYColSpec4.getEkiOrder()
							!= aCdYColSpecNext.getEkiOrder()
							&& aCdDedEki.getKyoukaisen())
						{
							//pCDcdLine->setCdPenProp(
							//	getCdPenPropNarrowLine());
							//暫定的に境界線を太線にしてみる
							pCDcdLine4->setCdPenProp(getCdPenPropBoldLine());
						}
						//　次の列が同じ駅の前作業または番線なら罫線
						else if (aCdYColSpec4.getEkiOrder() == aCdYColSpecNext.getEkiOrder() &&
							(aCdYColSpecNext.getColumnType()
								== aCdYColSpecNext.ColumnType_Track ||
								aCdYColSpecNext.getColumnType()
								== aCdYColSpecNext.ColumnType_AfterOperation1))
						{
							pCDcdLine4->setCdPenProp(getCdPenPropNarrowLine());
						}
						//　次の列が路線外終着駅欄なら罫線
						else if (aCdYColSpecNext.getColumnType()
							== aCdYColSpecNext.ColumnType_Outer_Shuchaku1)
						{
							pCDcdLine4->setCdPenProp(getCdPenPropNarrowLine());
						}
						//	次の列が駅時刻以外の場合は、太線
						else if (!aCdYColSpecNext.isEkiJikoku())
						{
							pCDcdLine4->setCdPenProp(getCdPenPropBoldLine());
						}
						else
						{
							pCDcdLine4->setCdPenProp(getCdPenPropNarrowLine());
						}

						// --------------------------------
						//	線の幅から、列幅を設定
						CdDcdSizeXy aCdDcdSizeXy;
						if (pCDcdLine4->getItemSize(
							&aCDcdTarget, &aCdDcdSizeXy))
						{
							pCDcdGridYBorder4->setColumnBorderSize(
								aCdDcdSizeXy.getX());
						}
					}
				}
			}
		}
	}
}


void CCellBuilder::update01_03_02_18_setEkimei_AfterOperation(
	CWndJikokuhyou * pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	CDcdTargetGetDC	aCDcdTarget(NULL);

	// --------------------------------
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou());

	// --------------------------------
	CdXColSpec aCdXColSpec(
		CdXColSpec::ColumnType_Ekimei);
	int iXColumnNumber =
		m_CdXColSpecCont.ColumnNumberFromSpec(aCdXColSpec);
	if (iXColumnNumber >= 0)
	{
		for (int iEkiOrder = 0; iEkiOrder < muCdDedEki->size();
			iEkiOrder++)
		{
			CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);

			for (int idx = 0; idx < aCdDedEki.getJikokuhyouAfterOperation(); idx++)
			{
				CdYColSpec aCdYColSpec1(
					CdYColSpec::ColumnType_AfterOperation1,
					iEkiOrder,
					idx);
				CdYColSpec aCdYColSpec2(
					CdYColSpec::ColumnType_AfterOperation2,
					iEkiOrder,
					idx);
				int iYColumnNumber1 =
					m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec1, false);
				int iYColumnNumber2 =
					m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec2, false);
				CDcdGridCell* pCDcdGridCell1 = pCDcdGrid->getCell(
					iXColumnNumber, iYColumnNumber1);
				CDcdGridCell* pCDcdGridCell2 = pCDcdGrid->getCell(
					iXColumnNumber, iYColumnNumber2);

				typedef CDcdTextbox CDcDrawCell;
				Ou<CDcDrawCell> pCDcDrawCell1;
				Ou<CDcDrawCell> pCDcDrawCell2;
				if (pCDcdGridCell1 != 0)
				{
					//(1.3.*.1)　セルの結合セルの属性を設定。
					/**
						2.0Update
						・編集モード時
							同一駅の物は全て結合する(番線・後作業・発時刻)
					*/
					int iYCount = 1;
					for (int idxy = iYColumnNumber1 + 1; idxy < m_CdYColSpecCont.size(); idxy++)
					{
						CdYColSpec aCdYColSpecSearch
							= m_CdYColSpecCont.ColumnNumberToSpec(idxy);
						if (iEkiOrder == aCdYColSpecSearch.getEkiOrder())
						{
							iYCount++;
						}
						else
						{
							break;
						}
					}
					pCDcdGridCell1->setAttachCellCount(1, iYCount);
					
					//	(1.3.*.2)　セルのDcDrawオブジェクトの型を設定
					//	( CDcdTextbox とする)。
					{
						pCDcDrawCell1 = dynamic_castOu<CDcDrawCell>(
							pCDcdGridCell1->getIfDcDraw());
						pCDcDrawCell2 = dynamic_castOu<CDcDrawCell>(
							pCDcdGridCell2->getIfDcDraw());
						if (pCDcDrawCell1 == NULL)
						{
							pCDcDrawCell1 = OuNew<CDcDrawCell>(new CDcDrawCell);
							pCDcdGridCell1->setIfDcDraw(pCDcDrawCell1);
						}
						if (pCDcDrawCell2 == NULL)
						{
							pCDcDrawCell2 = OuNew<CDcDrawCell>(new CDcDrawCell);
							pCDcdGridCell2->setIfDcDraw(pCDcDrawCell2);
						}
					}
					//(1.3.*.3)　セルのDcDrawオブジェクトに、属性を設定。
					{
						*pCDcDrawCell1 = createCDcdEkimei();
						pCDcDrawCell1->setText(aCdDedEki.getEkimei());
						*pCDcDrawCell2 = createCDcdEkimei();
						pCDcDrawCell2->setText(_T(""));
					}
				}

				CDcdGridYColumn* pCDcdGridYColumn1 = pCDcdGrid->getYColumn(
					iYColumnNumber1);
				if (pCDcdGridYColumn1)
				{
					//(1.3.*.4)　Y列のセルの高さを設定
					{
						CdDcdSizeXy aCdDcdSizeXy;
						if (pCDcDrawCell1->getItemSize(
							&aCDcdTarget, &aCdDcdSizeXy))
						{
							pCDcdGridYColumn1->setColumnSize(
								aCdDcdSizeXy.getY());
						}
					}
					//	　(1.3.*.5)　Y列(ColumnType_Ressyabangou) の境界線の
					//	DcDrawオブジェクト に属性を設定。
					//	　(1.3.*.6)　Y列ColumnType_Ressyabangou) の境界線の
					//	高さを設定
					{
						CDcdGridYBorder* pCDcdGridYBorder1
							= pCDcdGridYColumn1->getCDcdGridYBorder();
						Ou<CDcdLine> pCDcdLine1 =
							pCDcdGridYBorder1->getIfDcDraw();
						pCDcdLine1->setCdPenProp(getCdPenPropNullLine());
						
						// --------------------------------
						//	線の幅から、列幅を設定
						CdDcdSizeXy aCdDcdSizeXy;
						if (pCDcdLine1->getItemSize(
							&aCDcdTarget, &aCdDcdSizeXy))
						{
							pCDcdGridYBorder1->setColumnBorderSize(
								aCdDcdSizeXy.getX());
						}
					}
				}

				CDcdGridYColumn* pCDcdGridYColumn2 = pCDcdGrid->getYColumn(
					iYColumnNumber2);
				if (pCDcdGridYColumn2)
				{
					//(1.3.*.4)　Y列のセルの高さを設定
					{
						CdDcdSizeXy aCdDcdSizeXy;
						if (pCDcDrawCell2->getItemSize(
							&aCDcdTarget, &aCdDcdSizeXy))
						{
							pCDcdGridYColumn2->setColumnSize(
								aCdDcdSizeXy.getY());
						}
					}
					//	　(1.3.*.5)　Y列(ColumnType_Ressyabangou) の境界線の
					//	DcDrawオブジェクト に属性を設定。
					//	　(1.3.*.6)　Y列ColumnType_Ressyabangou) の境界線の
					//	高さを設定
					{
						CDcdGridYBorder* pCDcdGridYBorder2
							= pCDcdGridYColumn2->getCDcdGridYBorder();
						Ou<CDcdLine> pCDcdLine2 =
							pCDcdGridYBorder2->getIfDcDraw();

						CdYColSpec aCdYColSpecNext
							= m_CdYColSpecCont.ColumnNumberToSpec(
								iYColumnNumber2 + 1);
						//	次の列が異なる駅の列。
						//	当駅に『境界線』属性がある。
						//
						//	これら条件を満たす場合は、
						//	下（次の駅との間）に罫線
						if ((aCdYColSpecNext.isEkiJikoku() ||
							aCdYColSpecNext.getColumnType() == aCdYColSpecNext.ColumnType_Track)
							&& aCdYColSpec2.getEkiOrder()
							!= aCdYColSpecNext.getEkiOrder()
							&& aCdDedEki.getKyoukaisen())
						{
							//pCDcdLine->setCdPenProp(
							//	getCdPenPropNarrowLine());
							//暫定的に境界線を太線にしてみる
							pCDcdLine2->setCdPenProp(getCdPenPropBoldLine());
						}
						//　次の列が同じ駅の発時刻、後作業または解結編成後作業なら罫線
						else if (aCdYColSpec2.getEkiOrder() == aCdYColSpecNext.getEkiOrder() &&
							(aCdYColSpecNext.getColumnType()
							== aCdYColSpecNext.ColumnType_Ekijikoku_Hatsu||
							aCdYColSpecNext.getColumnType()
							== aCdYColSpecNext.ColumnType_AfterOperation1 ||
							aCdYColSpecNext.getColumnType()
							== aCdYColSpecNext.ColumnType_AfterOperationAfter1))
						{
							pCDcdLine2->setCdPenProp(getCdPenPropNarrowLine());
						}
						//　次の列が路線外終着駅欄なら罫線
						else if (aCdYColSpecNext.getColumnType()
							== aCdYColSpecNext.ColumnType_Outer_Shuchaku1)
						{
							pCDcdLine2->setCdPenProp(getCdPenPropNarrowLine());
						}
						//	次の列が駅時刻以外の場合は、太線
						else if (!aCdYColSpecNext.isEkiJikoku())
						{
							pCDcdLine2->setCdPenProp(getCdPenPropBoldLine());
						}
						else
						{
							pCDcdLine2->setCdPenProp(getCdPenPropNarrowLine());
						}

						// --------------------------------
						//	線の幅から、列幅を設定
						CdDcdSizeXy aCdDcdSizeXy;
						if (pCDcdLine2->getItemSize(
							&aCDcdTarget, &aCdDcdSizeXy))
						{
							pCDcdGridYBorder2->setColumnBorderSize(
								aCdDcdSizeXy.getX());
						}
					}
				}
			}
		}
	}
}

void CCellBuilder::update01_03_02_22_setEkimei_AfterOperationAfter(
	CWndJikokuhyou* pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	CDcdTargetGetDC	aCDcdTarget(NULL);

	// --------------------------------
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou());

	// --------------------------------
	CdXColSpec aCdXColSpec(
		CdXColSpec::ColumnType_Ekimei);
	int iXColumnNumber =
		m_CdXColSpecCont.ColumnNumberFromSpec(aCdXColSpec);
	if (iXColumnNumber >= 0)
	{
		for (int iEkiOrder = 0; iEkiOrder < muCdDedEki->size();
			iEkiOrder++)
		{
			CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);

			if (aCdDedEki.getJikokuhyouAfterOperationAfter())
			{
				CdYColSpec aCdYColSpec1(
					CdYColSpec::ColumnType_AfterOperationAfter1,
					iEkiOrder);
				CdYColSpec aCdYColSpec2(
					CdYColSpec::ColumnType_AfterOperationAfter2,
					iEkiOrder);
				CdYColSpec aCdYColSpec3(
					CdYColSpec::ColumnType_AfterOperationAfter3,
					iEkiOrder);
				int iYColumnNumber1 =
					m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec1, false);
				int iYColumnNumber2 =
					m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec2, false);
				int iYColumnNumber3 =
					m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec3, false);
				CDcdGridCell* pCDcdGridCell1 = pCDcdGrid->getCell(
					iXColumnNumber, iYColumnNumber1);
				CDcdGridCell* pCDcdGridCell2 = pCDcdGrid->getCell(
					iXColumnNumber, iYColumnNumber2);
				CDcdGridCell* pCDcdGridCell3 = pCDcdGrid->getCell(
					iXColumnNumber, iYColumnNumber3);

				typedef CDcdTextbox CDcDrawCell;
				Ou<CDcDrawCell> pCDcDrawCell1;
				Ou<CDcDrawCell> pCDcDrawCell2;
				Ou<CDcDrawCell> pCDcDrawCell3;
				if (pCDcdGridCell1 != 0)
				{
					//(1.3.*.1)　セルの結合セルの属性を設定。
					/**
						2.0Update
						・編集モード時
							同一駅の物は全て結合する(番線・後作業・発時刻)
					*/
					int iYCount = 1;
					for (int idxy = iYColumnNumber1 + 1; idxy < m_CdYColSpecCont.size(); idxy++)
					{
						CdYColSpec aCdYColSpecSearch
							= m_CdYColSpecCont.ColumnNumberToSpec(idxy);
						if (iEkiOrder == aCdYColSpecSearch.getEkiOrder())
						{
							iYCount++;
						}
						else
						{
							break;
						}
					}
					pCDcdGridCell1->setAttachCellCount(1, iYCount);

					//	(1.3.*.2)　セルのDcDrawオブジェクトの型を設定
					//	( CDcdTextbox とする)。
					{
						pCDcDrawCell1 = dynamic_castOu<CDcDrawCell>(
							pCDcdGridCell1->getIfDcDraw());
						pCDcDrawCell2 = dynamic_castOu<CDcDrawCell>(
							pCDcdGridCell2->getIfDcDraw());
						if (pCDcDrawCell1 == NULL)
						{
							pCDcDrawCell1 = OuNew<CDcDrawCell>(new CDcDrawCell);
							pCDcdGridCell1->setIfDcDraw(pCDcDrawCell1);
						}
						if (pCDcDrawCell2 == NULL)
						{
							pCDcDrawCell2 = OuNew<CDcDrawCell>(new CDcDrawCell);
							pCDcdGridCell2->setIfDcDraw(pCDcDrawCell2);
						}
						if (m_iEnableOperation > 1 && m_bDisplayInOutLinkCode)
						{
							pCDcDrawCell3 = dynamic_castOu<CDcDrawCell>(
								pCDcdGridCell3->getIfDcDraw());
							if (pCDcDrawCell3 == NULL)
							{
								pCDcDrawCell3 = OuNew<CDcDrawCell>(new CDcDrawCell);
								pCDcdGridCell3->setIfDcDraw(pCDcDrawCell3);
							}
						}
					}
					//(1.3.*.3)　セルのDcDrawオブジェクトに、属性を設定。
					{
						*pCDcDrawCell1 = createCDcdEkimei();
						pCDcDrawCell1->setText(aCdDedEki.getEkimei());
						*pCDcDrawCell2 = createCDcdEkimei();
						pCDcDrawCell2->setText(_T(""));
						if (m_iEnableOperation > 1 && m_bDisplayInOutLinkCode)
						{
							*pCDcDrawCell3 = createCDcdEkimei();
							pCDcDrawCell3->setText(_T(""));
						}
					}
				}

				CDcdGridYColumn* pCDcdGridYColumn1 = pCDcdGrid->getYColumn(
					iYColumnNumber1);
				if (pCDcdGridYColumn1)
				{
					//(1.3.*.4)　Y列のセルの高さを設定
					{
						CdDcdSizeXy aCdDcdSizeXy;
						if (pCDcDrawCell1->getItemSize(
							&aCDcdTarget, &aCdDcdSizeXy))
						{
							pCDcdGridYColumn1->setColumnSize(
								aCdDcdSizeXy.getY());
						}
					}
					//	　(1.3.*.5)　Y列(ColumnType_Ressyabangou) の境界線の
					//	DcDrawオブジェクト に属性を設定。
					//	　(1.3.*.6)　Y列ColumnType_Ressyabangou) の境界線の
					//	高さを設定
					{
						CDcdGridYBorder* pCDcdGridYBorder1
							= pCDcdGridYColumn1->getCDcdGridYBorder();
						Ou<CDcdLine> pCDcdLine1 =
							pCDcdGridYBorder1->getIfDcDraw();
						pCDcdLine1->setCdPenProp(getCdPenPropNullLine());

						// --------------------------------
						//	線の幅から、列幅を設定
						CdDcdSizeXy aCdDcdSizeXy;
						if (pCDcdLine1->getItemSize(
							&aCDcdTarget, &aCdDcdSizeXy))
						{
							pCDcdGridYBorder1->setColumnBorderSize(
								aCdDcdSizeXy.getX());
						}
					}
				}

				CDcdGridYColumn* pCDcdGridYColumn2 = pCDcdGrid->getYColumn(
					iYColumnNumber2);
				if (pCDcdGridYColumn2)
				{
					//(1.3.*.4)　Y列のセルの高さを設定
					{
						CdDcdSizeXy aCdDcdSizeXy;
						if (pCDcDrawCell2->getItemSize(
							&aCDcdTarget, &aCdDcdSizeXy))
						{
							pCDcdGridYColumn2->setColumnSize(
								aCdDcdSizeXy.getY());
						}
					}
					//	　(1.3.*.5)　Y列(ColumnType_Ressyabangou) の境界線の
					//	DcDrawオブジェクト に属性を設定。
					//	　(1.3.*.6)　Y列ColumnType_Ressyabangou) の境界線の
					//	高さを設定
					{
						CDcdGridYBorder* pCDcdGridYBorder2
							= pCDcdGridYColumn2->getCDcdGridYBorder();
						Ou<CDcdLine> pCDcdLine2 =
							pCDcdGridYBorder2->getIfDcDraw();

						if (m_iEnableOperation > 1 && m_bDisplayInOutLinkCode)
						{
							pCDcdLine2->setCdPenProp(getCdPenPropNullLine());
						}
						else
						{
							CdYColSpec aCdYColSpecNext
								= m_CdYColSpecCont.ColumnNumberToSpec(
									iYColumnNumber2 + 1);
							//	次の列が異なる駅の列。
							//	当駅に『境界線』属性がある。
							//
							//	これら条件を満たす場合は、
							//	下（次の駅との間）に罫線
							if ((aCdYColSpecNext.isEkiJikoku() ||
								aCdYColSpecNext.getColumnType() == aCdYColSpecNext.ColumnType_Track)
								&& aCdYColSpec2.getEkiOrder()
								!= aCdYColSpecNext.getEkiOrder()
								&& aCdDedEki.getKyoukaisen())
							{
								//pCDcdLine->setCdPenProp(
								//	getCdPenPropNarrowLine());
								//暫定的に境界線を太線にしてみる
								pCDcdLine2->setCdPenProp(getCdPenPropBoldLine());
							}
							//　次の列が同じ駅の前作業または番線なら罫線
							else if (aCdYColSpec2.getEkiOrder() == aCdYColSpecNext.getEkiOrder() &&
								(aCdYColSpecNext.getColumnType()
									== aCdYColSpecNext.ColumnType_Track ||
									aCdYColSpecNext.getColumnType()
									== aCdYColSpecNext.ColumnType_BeforeOperation1))
							{
								pCDcdLine2->setCdPenProp(getCdPenPropNarrowLine());
							}
							//　次の列が路線外終着駅欄なら罫線
							else if (aCdYColSpecNext.getColumnType()
								== aCdYColSpecNext.ColumnType_Outer_Shuchaku1)
							{
								pCDcdLine2->setCdPenProp(getCdPenPropNarrowLine());
							}
							//	次の列が駅時刻以外の場合は、太線
							else if (!aCdYColSpecNext.isEkiJikoku())
							{
								pCDcdLine2->setCdPenProp(getCdPenPropBoldLine());
							}
							else
							{
								pCDcdLine2->setCdPenProp(getCdPenPropNarrowLine());
							}
						}

						// --------------------------------
						//	線の幅から、列幅を設定
						CdDcdSizeXy aCdDcdSizeXy;
						if (pCDcdLine2->getItemSize(
							&aCDcdTarget, &aCdDcdSizeXy))
						{
							pCDcdGridYBorder2->setColumnBorderSize(
								aCdDcdSizeXy.getX());
						}
					}
				}

				CDcdGridYColumn* pCDcdGridYColumn3 = pCDcdGrid->getYColumn(
					iYColumnNumber3);
				if (pCDcdGridYColumn3)
				{
					//(1.3.*.4)　Y列のセルの高さを設定
					{
						CdDcdSizeXy aCdDcdSizeXy;
						if (pCDcDrawCell3->getItemSize(
							&aCDcdTarget, &aCdDcdSizeXy))
						{
							pCDcdGridYColumn3->setColumnSize(
								aCdDcdSizeXy.getY());
						}
					}
					//	　(1.3.*.5)　Y列(ColumnType_Ressyabangou) の境界線の
					//	DcDrawオブジェクト に属性を設定。
					//	　(1.3.*.6)　Y列ColumnType_Ressyabangou) の境界線の
					//	高さを設定
					{
						CDcdGridYBorder* pCDcdGridYBorder3
							= pCDcdGridYColumn3->getCDcdGridYBorder();
						Ou<CDcdLine> pCDcdLine3 =
							pCDcdGridYBorder3->getIfDcDraw();

						CdYColSpec aCdYColSpecNext
							= m_CdYColSpecCont.ColumnNumberToSpec(
								iYColumnNumber3 + 1);
						//	次の列が異なる駅の列。
						//	当駅に『境界線』属性がある。
						//
						//	これら条件を満たす場合は、
						//	下（次の駅との間）に罫線
						if ((aCdYColSpecNext.isEkiJikoku() ||
							aCdYColSpecNext.getColumnType() == aCdYColSpecNext.ColumnType_Track)
							&& aCdYColSpec3.getEkiOrder()
							!= aCdYColSpecNext.getEkiOrder()
							&& aCdDedEki.getKyoukaisen())
						{
							//pCDcdLine->setCdPenProp(
							//	getCdPenPropNarrowLine());
							//暫定的に境界線を太線にしてみる
							pCDcdLine3->setCdPenProp(getCdPenPropBoldLine());
						}
						//　次の列が同じ駅の前作業または番線なら罫線
						else if (aCdYColSpec3.getEkiOrder() == aCdYColSpecNext.getEkiOrder() &&
							(aCdYColSpecNext.getColumnType()
								== aCdYColSpecNext.ColumnType_Track ||
								aCdYColSpecNext.getColumnType()
								== aCdYColSpecNext.ColumnType_BeforeOperation1))
						{
							pCDcdLine3->setCdPenProp(getCdPenPropNarrowLine());
						}
						//　次の列が路線外終着駅欄なら罫線
						else if (aCdYColSpecNext.getColumnType()
							== aCdYColSpecNext.ColumnType_Outer_Shuchaku1)
						{
							pCDcdLine3->setCdPenProp(getCdPenPropNarrowLine());
						}
						//	次の列が駅時刻以外の場合は、太線
						else if (!aCdYColSpecNext.isEkiJikoku())
						{
							pCDcdLine3->setCdPenProp(getCdPenPropBoldLine());
						}
						else
						{
							pCDcdLine3->setCdPenProp(getCdPenPropNarrowLine());
						}

						// --------------------------------
						//	線の幅から、列幅を設定
						CdDcdSizeXy aCdDcdSizeXy;
						if (pCDcdLine3->getItemSize(
							&aCDcdTarget, &aCdDcdSizeXy))
						{
							pCDcdGridYBorder3->setColumnBorderSize(
								aCdDcdSizeXy.getX());
						}
					}
				}
			}
		}
	}
}

void CCellBuilder::update01_03_02_07_setEkimei_Hatsu(
	CWndJikokuhyou* pCWndJikokuhyou ) 
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid() ;
	CDcdTargetGetDC	aCDcdTarget( NULL ) ;

	// --------------------------------
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki = 
		m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(
		m_pCentDedRessyaCont->getRessyahoukou() ) ;

	// --------------------------------
	CdXColSpec aCdXColSpec( 
		CdXColSpec::ColumnType_Ekimei ) ;
	int iXColumnNumber = 
		m_CdXColSpecCont.ColumnNumberFromSpec( aCdXColSpec ) ;
	if ( iXColumnNumber >= 0 )
	{
		for ( int iEkiOrder = 0 ; iEkiOrder < muCdDedEki->size() ; 
			iEkiOrder ++ )
		{
			CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get( iEkiOrder ) ;

			CdYColSpec aCdYColSpec( 
				CdYColSpec::ColumnType_Ekijikoku_Hatsu , 
				iEkiOrder ) ;
			int iYColumnNumber = 
				m_CdYColSpecCont.ColumnNumberFromSpec( aCdYColSpec , false ) ;
			CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell( 
				iXColumnNumber , iYColumnNumber ) ;

			typedef CDcdTextbox CDcDrawCell ;
			Ou<CDcDrawCell> pCDcDrawCell ;
			if ( pCDcdGridCell != 0 )
			{
				//(1.3.*.1)　セルの結合セルの属性を設定。
				
				pCDcdGridCell->setAttachCellCount( 1 , 1 ) ;

				//	(1.3.*.2)　セルのDcDrawオブジェクトの型を設定
				//	( CDcdTextbox とする)。
				{
					pCDcDrawCell = dynamic_castOu<CDcDrawCell>( 
						pCDcdGridCell->getIfDcDraw() ) ;
					if ( pCDcDrawCell == NULL )
					{
						pCDcDrawCell = OuNew<CDcDrawCell>( new CDcDrawCell ) ;
						pCDcdGridCell->setIfDcDraw( pCDcDrawCell ) ;
					}
				}
				//(1.3.*.3)　セルのDcDrawオブジェクトに、属性を設定。
				{
					*pCDcDrawCell = createCDcdEkimei() ;
					pCDcDrawCell->setText( aCdDedEki.getEkimei() );
				}
			}

			CDcdGridYColumn* pCDcdGridYColumn = pCDcdGrid->getYColumn( 
				iYColumnNumber ) ;
			if ( pCDcdGridYColumn )
			{
				//(1.3.*.4)　Y列のセルの高さを設定
				{
					CdDcdSizeXy aCdDcdSizeXy ;
					if ( pCDcDrawCell->getItemSize( 
						&aCDcdTarget , &aCdDcdSizeXy ) )
					{
						pCDcdGridYColumn->setColumnSize( 
							aCdDcdSizeXy.getY() ) ;
					}
				}
				//	　(1.3.*.5)　Y列(ColumnType_Ressyabangou) の境界線の
				//	DcDrawオブジェクト に属性を設定。
				//	　(1.3.*.6)　Y列ColumnType_Ressyabangou) の境界線の
				//	高さを設定
				{
					CDcdGridYBorder* pCDcdGridYBorder 
						= pCDcdGridYColumn->getCDcdGridYBorder() ;
					Ou<CDcdLine> pCDcdLine = 
						pCDcdGridYBorder->getIfDcDraw() ;

					CdYColSpec aCdYColSpecNext  
						= m_CdYColSpecCont.ColumnNumberToSpec( 
							iYColumnNumber + 1 ) ;
					//	次の列が異なる駅の列。
					//	当駅に『境界線』属性がある。
					//	次の列が路線外終着駅表示
					//
					//	これら条件を満たす場合は、
					//	下（次の駅との間）に罫線
					if ( aCdYColSpecNext.isEkiJikoku() 
						&& aCdYColSpec.getEkiOrder() 
							!= aCdYColSpecNext.getEkiOrder() 
						&& aCdDedEki.getKyoukaisen() ) 
					{
						pCDcdLine->setCdPenProp(getCdPenPropBoldLine());
					}
					//	次の列が路線外終着駅表示の場合は、細線
					else if (aCdYColSpecNext.getColumnType() == aCdYColSpecNext.ColumnType_Outer_Shuchaku1)
					{
						pCDcdLine->setCdPenProp(getCdPenPropNarrowLine());
					}
					//	次の列が駅時刻、番線表示以外の場合は、太線
					else if ( !aCdYColSpecNext.isEkiJikoku() &&
						aCdYColSpecNext.getColumnType() != aCdYColSpecNext.ColumnType_Track)
					{
						pCDcdLine->setCdPenProp( getCdPenPropBoldLine() ) ;
					}
					//次の列が次の駅で、この駅または次の駅の行数が4以上の場合は、破線
					else if (aCdYColSpec.getEkiOrder() + 1
						== aCdYColSpecNext.getEkiOrder())
					{
						CdYColSpec aCdYColSpecBackward
							= m_CdYColSpecCont.ColumnNumberToSpec(
								iYColumnNumber - 3);
						CdYColSpec aCdYColSpecForward
							= m_CdYColSpecCont.ColumnNumberToSpec(
								iYColumnNumber + 4);
						if (aCdYColSpec.getEkiOrder()
							== aCdYColSpecBackward.getEkiOrder())
						{
							pCDcdLine->setCdPenProp(getCdPenPropDotLine());
						}
						else if (aCdYColSpec.getEkiOrder() + 1
							== aCdYColSpecForward.getEkiOrder())
						{
							pCDcdLine->setCdPenProp(getCdPenPropDotLine());
						}
						else
						{
							pCDcdLine->setCdPenProp(getCdPenPropNullLine());
						}
					}
					else
					{
						pCDcdLine->setCdPenProp( getCdPenPropNullLine() ) ;
					}

					// --------------------------------
					//	線の幅から、列幅を設定
					CdDcdSizeXy aCdDcdSizeXy ;
					if ( pCDcdLine->getItemSize( 
						&aCDcdTarget , &aCdDcdSizeXy ) )
					{
						if(pCDcdLine->getCdPenProp().getLogicalunitWidth() >0)
						{
							pCDcdGridYBorder->setColumnBorderSize(
								aCdDcdSizeXy.getX());
						}
						else
						{
							pCDcdGridYBorder->setColumnBorderSize((DcdSize)0);
						}
					}
				}
			}
		}
	}
}

void CCellBuilder::update01_03_02_16_setEkimei_OuterTerminal_Shuchaku(
	CWndJikokuhyou* pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	CDcdTargetGetDC	aCDcdTarget(NULL);

	// --------------------------------
	/*const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
	m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(
	m_pCentDedRessyaCont->getRessyahoukou());*/

	// --------------------------------
	CdXColSpec aCdXColSpec(
		CdXColSpec::ColumnType_Ekimei);
	int iXColumnNumber =
		m_CdXColSpecCont.ColumnNumberFromSpec(aCdXColSpec);
	if (iXColumnNumber >= 0)
	{
		CdYColSpec aCdYColSpec1(
			CdYColSpec::ColumnType_Outer_Shuchaku1);
		CdYColSpec aCdYColSpec2(
			CdYColSpec::ColumnType_Outer_Shuchaku2);
		int iYColumnNumber1 =
			m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec1, false);
		int iYColumnNumber2 =
			m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec2, false);
		CDcdGridCell* pCDcdGridCell1 = pCDcdGrid->getCell(
			iXColumnNumber, iYColumnNumber1);
		CDcdGridCell* pCDcdGridCell2 = pCDcdGrid->getCell(
			iXColumnNumber, iYColumnNumber2);

		typedef CDcdTextbox CDcDrawCell;
		Ou<CDcDrawCell> pCDcDrawCell1;
		Ou<CDcDrawCell> pCDcDrawCell2;
		if (pCDcdGridCell1 != 0)
		{
			//(1.3.*.1)　セルの結合セルの属性を設定。

			pCDcdGridCell1->setAttachCellCount(2, 1);
			pCDcdGridCell2->setAttachCellCount(2, 1);

			//	(1.3.*.2)　セルのDcDrawオブジェクトの型を設定
			//	( CDcdTextbox とする)。
			{
				pCDcDrawCell1 = dynamic_castOu<CDcDrawCell>(
					pCDcdGridCell1->getIfDcDraw());
				pCDcDrawCell2 = dynamic_castOu<CDcDrawCell>(
					pCDcdGridCell2->getIfDcDraw());
				if (pCDcDrawCell1 == NULL)
				{
					pCDcDrawCell1 = OuNew<CDcDrawCell>(new CDcDrawCell);
					pCDcdGridCell1->setIfDcDraw(pCDcDrawCell1);
				}
				if (pCDcDrawCell2 == NULL)
				{
					pCDcDrawCell2 = OuNew<CDcDrawCell>(new CDcDrawCell);
					pCDcdGridCell2->setIfDcDraw(pCDcDrawCell2);
				}
			}
			//(1.3.*.3)　セルのDcDrawオブジェクトに、属性を設定。
			{
				*pCDcDrawCell1 = createCDcdEkimei();
				pCDcDrawCell1->setText(tstringOf(
					(LPCTSTR)MfcUtil::LoadCString(
						IDS_WORD_ShuchakuEkimei)));
				*pCDcDrawCell2 = createCDcdEkimei();
				pCDcDrawCell2->setText(tstringOf(
					(LPCTSTR)MfcUtil::LoadCString(
						IDS_WORD_Jikoku)));
			}
		}

		CDcdGridYColumn* pCDcdGridYColumn1 = pCDcdGrid->getYColumn(
			iYColumnNumber1);
		if (pCDcdGridYColumn1)
		{
			//(1.3.*.4)　Y列のセルの高さを設定
			{
				CdDcdSizeXy aCdDcdSizeXy;
				if (pCDcDrawCell1->getItemSize(
					&aCDcdTarget, &aCdDcdSizeXy))
				{
					pCDcdGridYColumn1->setColumnSize(
						aCdDcdSizeXy.getY());
				}
			}
			//	　(1.3.*.5)　Y列(ColumnType_Ressyabangou) の境界線の
			//	DcDrawオブジェクト に属性を設定。
			//	　(1.3.*.6)　Y列ColumnType_Ressyabangou) の境界線の
			//	高さを設定
			{
				CDcdGridYBorder* pCDcdGridYBorder1
					= pCDcdGridYColumn1->getCDcdGridYBorder();
				Ou<CDcdLine> pCDcdLine =
					pCDcdGridYBorder1->getIfDcDraw();
				pCDcdLine->setCdPenProp(getCdPenPropNullLine());


				// --------------------------------
				//	線の幅から、列幅を設定
				CdDcdSizeXy aCdDcdSizeXy;
				if (pCDcdLine->getItemSize(
					&aCDcdTarget, &aCdDcdSizeXy))
				{
					pCDcdGridYBorder1->setColumnBorderSize(
						aCdDcdSizeXy.getX());
				}
			}
		}

		CDcdGridYColumn* pCDcdGridYColumn2 = pCDcdGrid->getYColumn(
			iYColumnNumber2);
		if (pCDcdGridYColumn2)
		{
			//(1.3.*.4)　Y列のセルの高さを設定
			{
				CdDcdSizeXy aCdDcdSizeXy;
				if (pCDcDrawCell2->getItemSize(
					&aCDcdTarget, &aCdDcdSizeXy))
				{
					pCDcdGridYColumn2->setColumnSize(
						aCdDcdSizeXy.getY());
				}
			}
			//	　(1.3.*.5)　Y列(ColumnType_Ressyabangou) の境界線の
			//	DcDrawオブジェクト に属性を設定。
			//	　(1.3.*.6)　Y列ColumnType_Ressyabangou) の境界線の
			//	高さを設定
			{
				CDcdGridYBorder* pCDcdGridYBorder2
					= pCDcdGridYColumn2->getCDcdGridYBorder();
				Ou<CDcdLine> pCDcdLine =
					pCDcdGridYBorder2->getIfDcDraw();
				//pCDcdLine->setCdPenProp(getCdPenPropNarrowLine());
				pCDcdLine->setCdPenProp(getCdPenPropBoldLine());


				// --------------------------------
				//	線の幅から、列幅を設定
				CdDcdSizeXy aCdDcdSizeXy;
				if (pCDcdLine->getItemSize(
					&aCDcdTarget, &aCdDcdSizeXy))
				{
					pCDcdGridYBorder2->setColumnBorderSize(
						aCdDcdSizeXy.getX());
				}
			}
		}
	}
}

void CCellBuilder::update01_03_02_08_setEkimei_Bikou( 
		CWndJikokuhyou* pCWndJikokuhyou ) 
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid() ;
	CDcdTargetGetDC	aCDcdTarget( NULL ) ;
	// --------------------------------
	CdXColSpec aCdXColSpec( 
		CdXColSpec::ColumnType_Ekimei ) ;
	int iXColumnNumber = 
		m_CdXColSpecCont.ColumnNumberFromSpec( aCdXColSpec ) ;

	if ( iXColumnNumber >= 0 )
	{
		CdYColSpec aCdYColSpec( 
			CdYColSpec::ColumnType_Bikou ) ;
		int iYColumnNumber = m_CdYColSpecCont.ColumnNumberFromSpec( 
			aCdYColSpec , false ) ;
		CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell( 
			iXColumnNumber , iYColumnNumber ) ;

		typedef CDcdTextboxV3 CDcDrawCell ;
		Ou<CDcDrawCell> pCDcDrawCell ;
		if ( pCDcdGridCell != NULL )
		{
			//(1.3.*.1)　結合セルの属性を設定。
			pCDcdGridCell->setAttachCellCount( 2 , 1 ) ;

			//	(1.3.*.2)　セル(ColumnType_Ekimei,ColumnType_Ressyabangou) 
			//	のDcDrawオブジェクトの型を設定
			//	( CDcdTextbox とする)。
			{
				pCDcDrawCell = dynamic_castOu<CDcDrawCell>( 
					pCDcdGridCell->getIfDcDraw() ) ;
				if ( pCDcDrawCell == NULL )
				{
					pCDcDrawCell = OuNew<CDcDrawCell>( new CDcDrawCell ) ;
					pCDcdGridCell->setIfDcDraw( pCDcDrawCell ) ;
				}
			}
			//(1.3.*.3)　セル(ColumnType_Ekimei,ColumnType_Ressyabangou) 
			//	DcDrawオブジェクトに、属性を設定。
			{
				*pCDcDrawCell = createCDcdXColumn0V() ;
				pCDcDrawCell->setLinesExtentX ( getBikouTextExtent().getX() ) ;
				pCDcDrawCell->setLinesExtentY ( getBikouTextExtent().getY() ) ;
				pCDcDrawCell->setText( tstringOf( 
					(LPCTSTR)MfcUtil::LoadCString( 
					IDS_WORD_Bikou ) ) ) ;
			}
		}
		CDcdGridYColumn* pCDcdGridYColumn = pCDcdGrid->getYColumn( 
			iYColumnNumber ) ;
		if ( pCDcdGridYColumn != NULL )
		{
			//(1.3.*.4)　Y列 のセルの高さを設定
			{
				CdDcdSizeXy aCdDcdSizeXy ;
				if ( pCDcDrawCell->getItemSize( 
					&aCDcdTarget , &aCdDcdSizeXy ) )
				{
					pCDcdGridYColumn->setColumnSize( aCdDcdSizeXy.getY() ) ;
				}
			}
			//	　(1.3.*.5)　Y列 の境界線の
			//	DcDrawオブジェクト に属性を設定。
			//	　(1.3.*.6)　Y列 の境界線の
			//	高さを設定
			{
				CDcdGridYBorder* pCDcdGridYBorder 
					= pCDcdGridYColumn->getCDcdGridYBorder() ;
				Ou<CDcdLine> pCDcdLine = pCDcdGridYBorder->getIfDcDraw() ;
				pCDcdLine->setCdPenProp( getCdPenPropNullLine() ) ;

				CdDcdSizeXy aCdDcdSizeXy ;
				if ( pCDcdLine->getItemSize( 
					&aCDcdTarget , &aCdDcdSizeXy ) )
				{
					pCDcdGridYBorder->setColumnBorderSize( 
						aCdDcdSizeXy.getX() ) ;
				}
			}
		}
	}
}

void CCellBuilder::update01_04_01_06_setChakuhatsu_Chaku( 
		CWndJikokuhyou* pCWndJikokuhyou ) 
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid() ;
	CDcdTargetGetDC	aCDcdTarget( NULL ) ;

	// --------------------------------
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki = 
		m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(
		m_pCentDedRessyaCont->getRessyahoukou() ) ;
	// --------------------------------
	CdXColSpec aCdXColSpec( 
		CdXColSpec::ColumnType_Chakuhatsu ) ;
	int iXColumnNumber = 
		m_CdXColSpecCont.ColumnNumberFromSpec( aCdXColSpec ) ;
	if ( iXColumnNumber >= 0 )
	{
		for ( int iEkiOrder = 0 ; iEkiOrder < muCdDedEki->size() ; 
			iEkiOrder ++ )
		{
			CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get( iEkiOrder ) ;

			CdYColSpec aCdYColSpec( 
				CdYColSpec::ColumnType_Ekijikoku_Chaku , 
				iEkiOrder ) ;
			int iYColumnNumber = 
				m_CdYColSpecCont.ColumnNumberFromSpec( aCdYColSpec , false ) ;
			CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell( 
				iXColumnNumber , iYColumnNumber ) ;

			typedef CDcdTextbox CDcDrawCell ;
			Ou<CDcDrawCell> pCDcDrawCell ;
			if ( pCDcdGridCell != 0 )
			{
				//(1.4.1.*.1)　セルの結合セルの属性を設定。
				pCDcdGridCell->setAttachCellCount( 1 , 1 ) ;
			
				//	(1.4.1.*.2)　セルのDcDrawオブジェクトの型を設定
				//	( CDcdTextbox とする)。
				{
					pCDcDrawCell = dynamic_castOu<CDcDrawCell>( 
						pCDcdGridCell->getIfDcDraw() ) ;
					if ( pCDcDrawCell == NULL )
					{
						pCDcDrawCell = OuNew<CDcDrawCell>( new CDcDrawCell ) ;
						pCDcdGridCell->setIfDcDraw( pCDcDrawCell ) ;
					}
				}
				//(1.4.1.*.3)　セルのDcDrawオブジェクトに、属性を設定。
				{
					*pCDcDrawCell = createCDcdHatsuchaku();
					pCDcDrawCell->setText( tstringOf( 
						(LPCTSTR)MfcUtil::LoadCString( 
						IDS_WORD_Chaku ) ) );
				}
			}
		}
	}
}

void CCellBuilder::update01_04_01_19_setChakuhatsu_BeforeOperationBefore(
	CWndJikokuhyou* pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	CDcdTargetGetDC	aCDcdTarget(NULL);

	// --------------------------------
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou());
	// --------------------------------
	CdXColSpec aCdXColSpec(
		CdXColSpec::ColumnType_Chakuhatsu);
	int iXColumnNumber =
		m_CdXColSpecCont.ColumnNumberFromSpec(aCdXColSpec);
	if (iXColumnNumber >= 0)
	{
		for (int iEkiOrder = 0; iEkiOrder < muCdDedEki->size();
			iEkiOrder++)
		{
			CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);

			if (aCdDedEki.getJikokuhyouBeforeOperationBefore())
			{
				CdYColSpec aCdYColSpec(
					CdYColSpec::ColumnType_BeforeOperationBefore1,
					iEkiOrder);
				int iYColumnNumber =
					m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec, false);
				CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell(
					iXColumnNumber, iYColumnNumber);

				typedef CDcdTextbox CDcDrawCell;
				Ou<CDcDrawCell> pCDcDrawCell;
				if (pCDcdGridCell != 0)
				{
					//(1.4.1.*.1)　セルの結合セルの属性を設定。
					if (m_iEnableOperation > 1)
					{
						if (m_bDisplayInOutLinkCode)
						{
							pCDcdGridCell->setAttachCellCount(1, 4);
						}
						else
						{
							pCDcdGridCell->setAttachCellCount(1, 3);
						}
					}
					else
					{
						pCDcdGridCell->setAttachCellCount(1, 2);
					}

					//	(1.4.1.*.2)　セルのDcDrawオブジェクトの型を設定
					//	( CDcdTextbox とする)。
					{
						pCDcDrawCell = dynamic_castOu<CDcDrawCell>(
							pCDcdGridCell->getIfDcDraw());
						if (pCDcDrawCell == NULL)
						{
							pCDcDrawCell = OuNew<CDcDrawCell>(new CDcDrawCell);
							pCDcdGridCell->setIfDcDraw(pCDcDrawCell);
						}
					}
					//(1.4.1.*.3)　セルのDcDrawオブジェクトに、属性を設定。
					{
						*pCDcDrawCell = createCDcdHatsuchaku();
						pCDcDrawCell->setText(_T("増前"));
						//pCDcDrawCell->setText(tstringOf(
						//	(LPCTSTR)MfcUtil::LoadCString(
						//		IDS_WORD_Chaku)));
					}
				}
			}
		}
	}
}

void CCellBuilder::update01_04_01_17_setChakuhatsu_BeforeOperation(
	CWndJikokuhyou * pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	CDcdTargetGetDC	aCDcdTarget(NULL);

	// --------------------------------
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou());
	// --------------------------------
	CdXColSpec aCdXColSpec(
		CdXColSpec::ColumnType_Chakuhatsu);
	int iXColumnNumber =
		m_CdXColSpecCont.ColumnNumberFromSpec(aCdXColSpec);
	if (iXColumnNumber >= 0)
	{
		for (int iEkiOrder = 0; iEkiOrder < muCdDedEki->size();
			iEkiOrder++)
		{
			CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);

			for (int idxb = 0; idxb < aCdDedEki.getJikokuhyouBeforeOperation(); idxb++)
			{
				CdYColSpec aCdYColSpec(
					CdYColSpec::ColumnType_BeforeOperation1,
					iEkiOrder,
					idxb);
				int iYColumnNumber =
					m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec, false);
				CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell(
					iXColumnNumber, iYColumnNumber);

				typedef CDcdTextbox CDcDrawCell;
				Ou<CDcDrawCell> pCDcDrawCell;
				if (pCDcdGridCell != 0)
				{
					//(1.4.1.*.1)　セルの結合セルの属性を設定。
					pCDcdGridCell->setAttachCellCount(1, 2);

					//	(1.4.1.*.2)　セルのDcDrawオブジェクトの型を設定
					//	( CDcdTextbox とする)。
					{
						pCDcDrawCell = dynamic_castOu<CDcDrawCell>(
							pCDcdGridCell->getIfDcDraw());
						if (pCDcDrawCell == NULL)
						{
							pCDcDrawCell = OuNew<CDcDrawCell>(new CDcDrawCell);
							pCDcdGridCell->setIfDcDraw(pCDcDrawCell);
						}
					}
					//(1.4.1.*.3)　セルのDcDrawオブジェクトに、属性を設定。
					{
						*pCDcDrawCell = createCDcdHatsuchaku();
						pCDcDrawCell->setText(_T("前") + to_tstring(idxb + 1));
						//pCDcDrawCell->setText(tstringOf(
						//	(LPCTSTR)MfcUtil::LoadCString(
						//		IDS_WORD_Chaku)));
					}
				}
			}
		}
	}
}

void CCellBuilder::update01_04_01_20_setChakuhatsu_BeforeOperationAfter(
	CWndJikokuhyou* pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	CDcdTargetGetDC	aCDcdTarget(NULL);

	// --------------------------------
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou());
	// --------------------------------
	CdXColSpec aCdXColSpec(
		CdXColSpec::ColumnType_Chakuhatsu);
	int iXColumnNumber =
		m_CdXColSpecCont.ColumnNumberFromSpec(aCdXColSpec);
	if (iXColumnNumber >= 0)
	{
		for (int iEkiOrder = 0; iEkiOrder < muCdDedEki->size();
			iEkiOrder++)
		{
			CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);

			if (aCdDedEki.getJikokuhyouBeforeOperationAfter())
			{
				CdYColSpec aCdYColSpec(
					CdYColSpec::ColumnType_BeforeOperationAfter1,
					iEkiOrder);
				int iYColumnNumber =
					m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec, false);
				CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell(
					iXColumnNumber, iYColumnNumber);

				typedef CDcdTextbox CDcDrawCell;
				Ou<CDcDrawCell> pCDcDrawCell;
				if (pCDcdGridCell != 0)
				{
					//(1.4.1.*.1)　セルの結合セルの属性を設定。
					if (m_iEnableOperation > 1 && m_bDisplayInOutLinkCode)
					{
						pCDcdGridCell->setAttachCellCount(1, 3);
					}
					else
					{
						pCDcdGridCell->setAttachCellCount(1, 2);
					}

					//	(1.4.1.*.2)　セルのDcDrawオブジェクトの型を設定
					//	( CDcdTextbox とする)。
					{
						pCDcDrawCell = dynamic_castOu<CDcDrawCell>(
							pCDcdGridCell->getIfDcDraw());
						if (pCDcDrawCell == NULL)
						{
							pCDcDrawCell = OuNew<CDcDrawCell>(new CDcDrawCell);
							pCDcdGridCell->setIfDcDraw(pCDcDrawCell);
						}
					}
					//(1.4.1.*.3)　セルのDcDrawオブジェクトに、属性を設定。
					{
						*pCDcDrawCell = createCDcdHatsuchaku();
						pCDcDrawCell->setText(_T("解後"));
					}
				}
			}
		}
	}
}

void CCellBuilder::update01_04_01_09_setChakuhatsu_Track(
	CWndJikokuhyou* pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	CDcdTargetGetDC	aCDcdTarget(NULL);

	// --------------------------------
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou());
	// --------------------------------
	CdXColSpec aCdXColSpec(
		CdXColSpec::ColumnType_Chakuhatsu);
	int iXColumnNumber =
		m_CdXColSpecCont.ColumnNumberFromSpec(aCdXColSpec);
	if (iXColumnNumber >= 0)
	{
		for (int iEkiOrder = 0; iEkiOrder < muCdDedEki->size();
			iEkiOrder++)
		{
			CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);

			CdYColSpec aCdYColSpec(
				CdYColSpec::ColumnType_Track,
				iEkiOrder);
			int iYColumnNumber =
				m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec, false);
			CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell(
				iXColumnNumber, iYColumnNumber);

			typedef CDcdTextbox CDcDrawCell;
			Ou<CDcDrawCell> pCDcDrawCell;
			if (pCDcdGridCell != 0)
			{
				//(1.4.1.*.1)　セルの結合セルの属性を設定。
				pCDcdGridCell->setAttachCellCount(1, 1);

				//	(1.4.1.*.2)　セルのDcDrawオブジェクトの型を設定
				//	( CDcdTextbox とする)。
				{
					pCDcDrawCell = dynamic_castOu<CDcDrawCell>(
						pCDcdGridCell->getIfDcDraw());
					if (pCDcDrawCell == NULL)
					{
						pCDcDrawCell = OuNew<CDcDrawCell>(new CDcDrawCell);
						pCDcdGridCell->setIfDcDraw(pCDcDrawCell);
					}
				}
				//(1.4.1.*.3)　セルのDcDrawオブジェクトに、属性を設定。
				{
					*pCDcDrawCell = createCDcdHatsuchaku();
					//if(m_bDisplayAllTrack)
					//{
						pCDcDrawCell->setText(tstringOf(
							(LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_Track)));
					//}
				}
			}
		}
	}
}

void CCellBuilder::update01_04_01_21_setChakuhatsu_AfterOperationBefore(
	CWndJikokuhyou* pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	CDcdTargetGetDC	aCDcdTarget(NULL);

	// --------------------------------
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou());
	// --------------------------------
	CdXColSpec aCdXColSpec(
		CdXColSpec::ColumnType_Chakuhatsu);
	int iXColumnNumber =
		m_CdXColSpecCont.ColumnNumberFromSpec(aCdXColSpec);
	if (iXColumnNumber >= 0)
	{
		for (int iEkiOrder = 0; iEkiOrder < muCdDedEki->size();
			iEkiOrder++)
		{
			CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);

			if (aCdDedEki.getJikokuhyouAfterOperationBefore())
			{
				CdYColSpec aCdYColSpec(
					CdYColSpec::ColumnType_AfterOperationBefore1,
					iEkiOrder);
				int iYColumnNumber =
					m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec, false);
				CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell(
					iXColumnNumber, iYColumnNumber);

				typedef CDcdTextbox CDcDrawCell;
				Ou<CDcDrawCell> pCDcDrawCell;
				if (pCDcdGridCell != 0)
				{
					//(1.4.1.*.1)　セルの結合セルの属性を設定。
					if (m_iEnableOperation > 1)
					{
						if (m_bDisplayInOutLinkCode)
						{
							pCDcdGridCell->setAttachCellCount(1, 4);
						}
						else
						{
							pCDcdGridCell->setAttachCellCount(1, 3);
						}
					}
					else
					{
						pCDcdGridCell->setAttachCellCount(1, 2);
					}

					//	(1.4.1.*.2)　セルのDcDrawオブジェクトの型を設定
					//	( CDcdTextbox とする)。
					{
						pCDcDrawCell = dynamic_castOu<CDcDrawCell>(
							pCDcdGridCell->getIfDcDraw());
						if (pCDcDrawCell == NULL)
						{
							pCDcDrawCell = OuNew<CDcDrawCell>(new CDcDrawCell);
							pCDcdGridCell->setIfDcDraw(pCDcDrawCell);
						}
					}
					//(1.4.1.*.3)　セルのDcDrawオブジェクトに、属性を設定。
					{
						*pCDcDrawCell = createCDcdHatsuchaku();
						pCDcDrawCell->setText(_T("増前"));
					}
				}
			}
		}
	}
}


void CCellBuilder::update01_04_01_18_setChakuhatsu_AfterOperation(
	CWndJikokuhyou * pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	CDcdTargetGetDC	aCDcdTarget(NULL);

	// --------------------------------
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou());
	// --------------------------------
	CdXColSpec aCdXColSpec(
		CdXColSpec::ColumnType_Chakuhatsu);
	int iXColumnNumber =
		m_CdXColSpecCont.ColumnNumberFromSpec(aCdXColSpec);
	if (iXColumnNumber >= 0)
	{
		for (int iEkiOrder = 0; iEkiOrder < muCdDedEki->size();
			iEkiOrder++)
		{
			CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);

			for (int idxa = 0; idxa < aCdDedEki.getJikokuhyouAfterOperation(); idxa++)
			{
				CdYColSpec aCdYColSpec(
					CdYColSpec::ColumnType_AfterOperation1,
					iEkiOrder,
					idxa);
				int iYColumnNumber =
					m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec, false);
				CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell(
					iXColumnNumber, iYColumnNumber);

				typedef CDcdTextbox CDcDrawCell;
				Ou<CDcDrawCell> pCDcDrawCell;
				if (pCDcdGridCell != 0)
				{
					//(1.4.1.*.1)　セルの結合セルの属性を設定。
					pCDcdGridCell->setAttachCellCount(1, 2);

					//	(1.4.1.*.2)　セルのDcDrawオブジェクトの型を設定
					//	( CDcdTextbox とする)。
					{
						pCDcDrawCell = dynamic_castOu<CDcDrawCell>(
							pCDcdGridCell->getIfDcDraw());
						if (pCDcDrawCell == NULL)
						{
							pCDcDrawCell = OuNew<CDcDrawCell>(new CDcDrawCell);
							pCDcdGridCell->setIfDcDraw(pCDcDrawCell);
						}
					}
					//(1.4.1.*.3)　セルのDcDrawオブジェクトに、属性を設定。
					{
						*pCDcDrawCell = createCDcdHatsuchaku();
						pCDcDrawCell->setText(_T("後") + to_tstring(idxa + 1));
						//pCDcDrawCell->setText(tstringOf(
						//	(LPCTSTR)MfcUtil::LoadCString(
						//		IDS_WORD_Chaku)));
					}
				}
			}
		}
	}
}

void CCellBuilder::update01_04_01_22_setChakuhatsu_AfterOperationAfter(
	CWndJikokuhyou* pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	CDcdTargetGetDC	aCDcdTarget(NULL);

	// --------------------------------
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou());
	// --------------------------------
	CdXColSpec aCdXColSpec(
		CdXColSpec::ColumnType_Chakuhatsu);
	int iXColumnNumber =
		m_CdXColSpecCont.ColumnNumberFromSpec(aCdXColSpec);
	if (iXColumnNumber >= 0)
	{
		for (int iEkiOrder = 0; iEkiOrder < muCdDedEki->size();
			iEkiOrder++)
		{
			CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);

			if (aCdDedEki.getJikokuhyouAfterOperationAfter())
			{
				CdYColSpec aCdYColSpec(
					CdYColSpec::ColumnType_AfterOperationAfter1,
					iEkiOrder);
				int iYColumnNumber =
					m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec, false);
				CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell(
					iXColumnNumber, iYColumnNumber);

				typedef CDcdTextbox CDcDrawCell;
				Ou<CDcDrawCell> pCDcDrawCell;
				if (pCDcdGridCell != 0)
				{
					//(1.4.1.*.1)　セルの結合セルの属性を設定。
					if (m_iEnableOperation > 1 && m_bDisplayInOutLinkCode)
					{
						pCDcdGridCell->setAttachCellCount(1, 3);
					}
					else
					{
						pCDcdGridCell->setAttachCellCount(1, 2);
					}

					//	(1.4.1.*.2)　セルのDcDrawオブジェクトの型を設定
					//	( CDcdTextbox とする)。
					{
						pCDcDrawCell = dynamic_castOu<CDcDrawCell>(
							pCDcdGridCell->getIfDcDraw());
						if (pCDcDrawCell == NULL)
						{
							pCDcDrawCell = OuNew<CDcDrawCell>(new CDcDrawCell);
							pCDcdGridCell->setIfDcDraw(pCDcDrawCell);
						}
					}
					//(1.4.1.*.3)　セルのDcDrawオブジェクトに、属性を設定。
					{
						*pCDcDrawCell = createCDcdHatsuchaku();
						pCDcDrawCell->setText(_T("解後"));
					}
				}
			}
		}
	}
}


void CCellBuilder::update01_04_01_07_setChakuhatsu_Hatsu( 
		CWndJikokuhyou* pCWndJikokuhyou ) 
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid() ;
	CDcdTargetGetDC	aCDcdTarget( NULL ) ;

	// --------------------------------
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki = 
		m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(
		m_pCentDedRessyaCont->getRessyahoukou() ) ;
	// --------------------------------
	CdXColSpec aCdXColSpec( 
		CdXColSpec::ColumnType_Chakuhatsu ) ;
	int iXColumnNumber = 
		m_CdXColSpecCont.ColumnNumberFromSpec( aCdXColSpec ) ;
	if ( iXColumnNumber >= 0 )
	{
		for ( int iEkiOrder = 0 ; iEkiOrder < muCdDedEki->size() ; 
			iEkiOrder ++ )
		{
			CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get( iEkiOrder ) ;

			CdYColSpec aCdYColSpec( 
				CdYColSpec::ColumnType_Ekijikoku_Hatsu , 
				iEkiOrder ) ;
			int iYColumnNumber = 
				m_CdYColSpecCont.ColumnNumberFromSpec( aCdYColSpec , false ) ;
			CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell( 
				iXColumnNumber , iYColumnNumber ) ;

			typedef CDcdTextbox CDcDrawCell ;
			Ou<CDcDrawCell> pCDcDrawCell ;
			if ( pCDcdGridCell != 0 )
			{
				//(1.4.1.*.1)　セルの結合セルの属性を設定。
				pCDcdGridCell->setAttachCellCount( 1 , 1 ) ;
			
				//	(1.4.1.*.2)　セルのDcDrawオブジェクトの型を設定
				//	( CDcdTextbox とする)。
				{
					pCDcDrawCell = dynamic_castOu<CDcDrawCell>( 
						pCDcdGridCell->getIfDcDraw() ) ;
					if ( pCDcDrawCell == NULL )
					{
						pCDcDrawCell = OuNew<CDcDrawCell>( new CDcDrawCell ) ;
						pCDcdGridCell->setIfDcDraw( pCDcDrawCell ) ;
					}
				}
				//(1.4.1.*.3)　セルのDcDrawオブジェクトに、属性を設定。
				{
					*pCDcDrawCell = createCDcdHatsuchaku();
					pCDcDrawCell->setText( tstringOf( 
						(LPCTSTR)MfcUtil::LoadCString( 
						IDS_WORD_Hatsu ) ) );
				}
			}
		}
	}
}


void CCellBuilder::update02_02_updateRessya( 
		int iXColumnNumber , 
		const CentDedRessya* pCentDedRessya ,
		CWndJikokuhyou* pCWndJikokuhyou ) 
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid() ;
	CDcdTargetGetDC	aCDcdTarget( NULL ) ;

	for (int iYColumnNumber = 0; iYColumnNumber < m_CdYColSpecCont.size(); iYColumnNumber++)
	{
		CdYColSpec aCdYColSpec = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumber);

		switch (aCdYColSpec.getColumnType())
		{
			case CdYColSpec::ColumnType_Ressyabangou:
			{
				// ================================
				//　(2.2.1)　セル(ColumnType_Ressya ,
				//	ColumnType_Ressyabangou) を設定
				// ================================
				update02_02_01_setRessya_Ressyabangou(
					iXColumnNumber,
					iYColumnNumber,
					pCentDedRessya,
					pCWndJikokuhyou);

			}
			break;
			case CdYColSpec::ColumnType_OperationNumber:
			{
				// --------------------------------
				//	(2.2.2.12)セル(ColumnType_Ressya, ColumnType_OperationNumber)
				// --------------------------------
				update02_02_02_12_setRessya_OperationNumber(
					iXColumnNumber,
					iYColumnNumber,
					pCentDedRessya,
					pCWndJikokuhyou);
				iYColumnNumber += m_iOperationNumberRows - 1;
			}
			break;
			case CdYColSpec::ColumnType_Ressyasyubetsu:
			{
				// --------------------------------
				//	(2.2.2.2)セル(ColumnType_Ressya, ColumnType_Ressyasyubetsu)
				// --------------------------------
				update02_02_02_02_setRessya_Ressyasyubetsu(
					iXColumnNumber,
					iYColumnNumber,
					pCentDedRessya,
					pCWndJikokuhyou);

			}
			break;
			case CdYColSpec::ColumnType_Ressyamei:
			{
				// --------------------------------
				//	(2.2.2.3)セル(ColumnType_Ressya, ColumnType_Ressyamei)
				// --------------------------------
				update02_02_02_03_setRessya_Ressyamei(
					iXColumnNumber,
					iYColumnNumber,
					pCentDedRessya,
					pCWndJikokuhyou);

			}
			break;
			case CdYColSpec::ColumnType_Gousuu:
			{
				// --------------------------------
				//	(2.2.2.4)セル(ColumnType_Ressya, ColumnType_Gousuu)
				// --------------------------------
				update02_02_02_04_setRessya_Gousuu(
					iXColumnNumber,
					iYColumnNumber,
					pCentDedRessya,
					pCWndJikokuhyou);

			}
			break;
			case CdYColSpec::ColumnType_Gou:
			{
				// --------------------------------
				//	(2.2.2.5)セル(ColumnType_Ressya, ColumnType_Gou)
				// --------------------------------
				update02_02_02_05_setRessya_Gou(
					iXColumnNumber,
					iYColumnNumber,
					pCentDedRessya,
					pCWndJikokuhyou);

			}
			break;
			case CdYColSpec::ColumnType_ShihatsuEkimei:
			{
				// --------------------------------
				//	(2.2.2.13)セル(ColumnType_Ressya, ColumnType_ShihatsuEkimei)
				// --------------------------------
				update02_02_02_13_setRessya_ShihatsuEkimei(
					iXColumnNumber,
					iYColumnNumber,
					pCentDedRessya,
					pCWndJikokuhyou);
			}
			break;
			case CdYColSpec::ColumnType_Operation_Shihatsu1:
			{
				// --------------------------------
				//	(2.2.2.10)セル(ColumnType_Ressya, ColumnType_Operation_Shihatsu)
				// --------------------------------
				update02_02_02_10_setRessya_Operation_Shihatsu(
					iXColumnNumber,
					iYColumnNumber,
					pCentDedRessya,
					pCWndJikokuhyou);
				if (m_iEnableOperation == 2)
				{
					iYColumnNumber += 2;
				}
				else
				{
					iYColumnNumber += 1;
				}
			}
			break;
			case CdYColSpec::ColumnType_ShuchakuEkimei:
			{
				// --------------------------------
				//	(2.2.2.14)セル(ColumnType_Ressya, ColumnType_ShuchakuEkimei)
				// --------------------------------
				update02_02_02_14_setRessya_ShuchakuEkimei(
					iXColumnNumber,
					iYColumnNumber,
					pCentDedRessya,
					pCWndJikokuhyou);
			}
			break;
			case CdYColSpec::ColumnType_Operation_Shuchaku1:
			{
				// --------------------------------
				//	(2.2.2.11)セル(ColumnType_Ressya, ColumnType_Operation_Shuchaku)
				// --------------------------------
				update02_02_02_11_setRessya_Operation_Shuchaku(
					iXColumnNumber,
					iYColumnNumber,
					pCentDedRessya,
					pCWndJikokuhyou);
				iYColumnNumber += 1;
			}
			break;
			case CdYColSpec::ColumnType_Outer_Shihatsu1:
			{
				// --------------------------------
				//	(2.2.2.15)セル(ColumnType_Ressya, ColumnType_Outer_Shihatsu)
				// --------------------------------
				update02_02_02_15_setRessya_OuterTerminal_Shihatsu(
					iXColumnNumber,
					iYColumnNumber,
					pCentDedRessya,
					pCWndJikokuhyou);
				iYColumnNumber += 1;
			}
			break;
			case CdYColSpec::ColumnType_Ekijikoku_Chaku:
			{
				update02_02_02_06_setRessya_Chaku(
					iXColumnNumber,
					iYColumnNumber,
					pCentDedRessya,
					aCdYColSpec.getEkiOrder(),
					pCWndJikokuhyou);
			}
			break;
			case CdYColSpec::ColumnType_BeforeOperationBefore1:
			{
				update02_02_02_19_setRessya_BeforeOperationBefore(
					iXColumnNumber,
					iYColumnNumber,
					pCentDedRessya,
					aCdYColSpec.getEkiOrder(),
					pCWndJikokuhyou);
				if (m_iEnableOperation == 2)
				{
					iYColumnNumber += 2;
				}
				else
				{
					iYColumnNumber += 1;
				}
			}
			break;
			case CdYColSpec::ColumnType_BeforeOperation1:
			{
				if (aCdYColSpec.getOperationIndex() > 0)
				{
					iYColumnNumber += 1;
					continue;
				}
				update02_02_02_17_setRessya_BeforeOperation(
					iXColumnNumber,
					iYColumnNumber,
					pCentDedRessya,
					aCdYColSpec.getEkiOrder(),
					pCWndJikokuhyou);
				iYColumnNumber += 1;
			}
			break;
			case CdYColSpec::ColumnType_BeforeOperationAfter1:
			{
				update02_02_02_20_setRessya_BeforeOperationAfter(
					iXColumnNumber,
					iYColumnNumber,
					pCentDedRessya,
					aCdYColSpec.getEkiOrder(),
					pCWndJikokuhyou);
				iYColumnNumber += 1;
			}
			break;
			case CdYColSpec::ColumnType_Track:
			{
				update02_02_02_09_setRessya_Track(
					iXColumnNumber,
					iYColumnNumber,
					pCentDedRessya,
					aCdYColSpec.getEkiOrder(),
					pCWndJikokuhyou);
			}
			break;
			case CdYColSpec::ColumnType_AfterOperationBefore1:
			{
				update02_02_02_21_setRessya_AfterOperationBefore(
					iXColumnNumber,
					iYColumnNumber,
					pCentDedRessya,
					aCdYColSpec.getEkiOrder(),
					pCWndJikokuhyou);
				if (m_iEnableOperation == 2)
				{
					iYColumnNumber += 2;
				}
				else
				{
					iYColumnNumber += 1;
				}
			}
			break;
			case CdYColSpec::ColumnType_AfterOperation1:
			{
				if (aCdYColSpec.getOperationIndex() > 0)
				{
					iYColumnNumber += 1;
					continue;
				}
				update02_02_02_18_setRessya_AfterOperation(
					iXColumnNumber,
					iYColumnNumber,
					pCentDedRessya,
					aCdYColSpec.getEkiOrder(),
					pCWndJikokuhyou);
				iYColumnNumber += 1;
			}
			break;
			case CdYColSpec::ColumnType_AfterOperationAfter1:
			{
				update02_02_02_22_setRessya_AfterOperationAfter(
					iXColumnNumber,
					iYColumnNumber,
					pCentDedRessya,
					aCdYColSpec.getEkiOrder(),
					pCWndJikokuhyou);
				iYColumnNumber += 1;
			}
			break;
			case CdYColSpec::ColumnType_Ekijikoku_Hatsu:
			{
				update02_02_02_07_setRessya_Hatsu(
					iXColumnNumber,
					iYColumnNumber,
					pCentDedRessya,
					aCdYColSpec.getEkiOrder(),
					pCWndJikokuhyou);
			}
			break;
			case CdYColSpec::ColumnType_Outer_Shuchaku1:
			{
				// --------------------------------
				//	(2.2.2.16)セル(ColumnType_Ressya, ColumnType_Outer_Shuchaku)
				// --------------------------------
				update02_02_02_16_setRessya_OuterTerminal_Shuchaku(
					iXColumnNumber,
					iYColumnNumber,
					pCentDedRessya,
					pCWndJikokuhyou);
				iYColumnNumber += 1;
			}
			break;
			case CdYColSpec::ColumnType_Bikou:
			{
				// --------------------------------
				//	(2.2.2.8)セル(ColumnType_Ressya,ColumnType_Bikou)
				// --------------------------------
				update02_02_02_08_setRessya_Bikou(
					iXColumnNumber,
					iYColumnNumber,
					pCentDedRessya,
					pCWndJikokuhyou);
			}
			break;
		}
	}
	
	// ================================
	//　(2.2.3)　X列(ColumnType_Ressya ) の幅を設定。
	//	幅は、駅時刻列の DcDraw オブジェクトの幅とします。
	// ================================
	CDcdGridXColumn* pCDcdGridXColumn 
		= pCDcdGrid->getXColumn( iXColumnNumber ) ;
	{
		{
			CDcdGridCell* pCDcdGridCell 
				= pCDcdGrid->getCell( iXColumnNumber , 0 ) ;
			CdDcdSizeXy	aCdDcdSizeXy ;
			if ( pCDcdGridCell->getIfDcDraw()->getItemSize( 
					&aCDcdTarget , &aCdDcdSizeXy ) ){
				pCDcdGridXColumn->setColumnSize( aCdDcdSizeXy.getX() ) ;
			}
		}
	}

	// ================================
	//　(2.2.4)　X列(ColumnType_Ressya ) の境界線の 
	//	DcDrawオブジェクトの属性を設定。
	//　(2.2.5)　X列(ColumnType_Ressya ) の境界線の幅を設定。
	// ================================
	{
		CDcdGridXBorder* pCDcdGridXBorder 
			= pCDcdGridXColumn->getCDcdGridXBorder() ;
		Ou<CDcdLine> pCDcdLine = pCDcdGridXBorder->getIfDcDraw() ;

		pCDcdLine->setCdPenProp( getCdPenPropNarrowLine() ) ;

		CdDcdSizeXy aCdDcdSizeXy ;
		if ( pCDcdLine->getItemSize( &aCDcdTarget , &aCdDcdSizeXy ) )
		{
			pCDcdGridXBorder->setColumnBorderSize( aCdDcdSizeXy.getX() ) ;
		}
	}
	// ================================
	//	X列を再描画領域とします。
	// ================================
	{
		CdDcdZoneXy	aCdDcdZoneXy ;
		//X列の範囲
		{
			CdDcdZone	zoneXColumnZone = pCDcdGrid->getXColumnZone( 
				&aCDcdTarget , 
				iXColumnNumber ) ;
			CdDcdZone	zoneXColumnBorderZone = pCDcdGrid->getXColumnBorderZone( 
				&aCDcdTarget , 
				iXColumnNumber ) ;
			
			aCdDcdZoneXy.setX( 
				zoneXColumnZone.ZoneOr( zoneXColumnBorderZone ) ) ;
		}
		//Y列の範囲
		{
			CdDcdZone	zoneYColumnTop = pCDcdGrid->getYColumnZone( 
				&aCDcdTarget , 
				0 ) ;
			CdDcdZone	zoneYColumnBottom = pCDcdGrid->getYColumnZone( 
				&aCDcdTarget , 
				INT_MAX ) ;
			aCdDcdZoneXy.setY( 
				zoneYColumnTop.ZoneOr( zoneYColumnBottom ) ) ;
		}
		CConverter_WinGdi	aConv ;
		pCWndJikokuhyou->InvalidateRect( 
			&aConv.RECTOf( aCdDcdZoneXy ) ) ; 
	}
}

void CCellBuilder::update02_02_01_setRessya_Ressyabangou( 
		int iXColumnNumber ,
		int iYColumnNumber,
		const CentDedRessya* pCentDedRessya ,
		CWndJikokuhyou* pCWndJikokuhyou ) 
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid() ;
	//CDcdTargetGetDC	aCDcdTarget( NULL ) ;
	// --------------------------------
	//CdYColSpec aCdYColSpec( 
	//	CdYColSpec::ColumnType_Ressyabangou ) ;
	//int iYColumnNumber = 
	//	m_CdYColSpecCont.ColumnNumberFromSpec( aCdYColSpec , false ) ;
	CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell( 
		iXColumnNumber , iYColumnNumber ) ;
	// --------------------------------
	//CdDedDispProp	aCdDedDispProp = m_pCDedRosenFileData->getCdDedDispProp() ;
	//tstring strCellExtent( aCdDedDispProp.getJikokuhyouRessyaWidth() , '0' ) ;
	//strCellExtent = セルの大きさの目安となる文字列です。
	//	時刻表列車セルの幅(文字数) CdDedDispProp::m_iJikokuhyouRessyaWidth
	//	の数だけ '0' が並んだ文字列です

	if ( pCDcdGridCell != 0 )
	{
		typedef CDcdTextbox CDcDrawCell ;
		Ou<CDcDrawCell> pCDcDrawCell ;
		// --------------------------------
		//　(2.2.*.1)　セル(ColumnType_Ressya,ColumnType_Ressyabangou) の
		//	結合セルを設定
		pCDcdGridCell->setAttachCellCount( 1 , 1 ) ;

		//　(2.2.*.2)　セル の	DcDrawオブジェクトの型を設定
		//	( CDcdTextbox とする)。
		{
			pCDcDrawCell = dynamic_castOu<CDcDrawCell>( 
				pCDcdGridCell->getIfDcDraw() ) ;
			if ( pCDcDrawCell == NULL )
			{
				pCDcDrawCell = OuNew<CDcDrawCell>( new CDcDrawCell ) ;
				pCDcdGridCell->setIfDcDraw( pCDcDrawCell ) ;
			}
		}

		//　(2.2.*.3)　セルの DcDrawオブジェクトに、属性を設定。
		{
			int idxRessyasyubetsu 
					= pCentDedRessya->getRessyasyubetsuIndex() ;
			tstring strText = pCentDedRessya->getRessyabangou() ;
			
			*pCDcDrawCell = createCDcdRessyabangou( idxRessyasyubetsu ) ;
			pCDcDrawCell->setText( strText );
		}

		//セルの背景色を指定します。
		{
			if (pCentDedRessya->isCanceled())
			{
				pCDcDrawCell->setCdBrushProp(CdColorProp(128, 128, 128));
			}
			else
			{
				pCDcDrawCell->setCdBrushProp(CdColorProp(255, 255, 255));
			}
		}
	}
}

void CCellBuilder::update02_02_02_12_setRessya_OperationNumber(
	int iXColumnNumber,
	int iYColumnNumber,
	const CentDedRessya * pCentDedRessya, 
	CWndJikokuhyou * pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	//CDcdTargetGetDC	aCDcdTarget(NULL);
	// --------------------------------
	//CdYColSpec aCdYColSpec(
	//	CdYColSpec::ColumnType_OperationNumber);
	//int iYColumnNumber =
	//	m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec, false);

	int idxRessyasyubetsu
		= pCentDedRessya->getRessyasyubetsuIndex();
	vector<tstring> strOperationNumber = vector<tstring>();
	if (!pCentDedRessya->isCanceled())
	{
		strOperationNumber = pCentDedRessya->getOperationNumber(
			pCentDedRessya->getValidSihatsuEki());
	}
	for (int idx = 0; idx < m_iOperationNumberRows; idx++)
	{
		CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell(
			iXColumnNumber, iYColumnNumber+ idx);
		// --------------------------------
		if (pCDcdGridCell != 0)
		{
			typedef CDcdTextbox CDcDrawCell;
			Ou<CDcDrawCell> pCDcDrawCell;
			// --------------------------------
			//　(2.2.*.1)　セル(ColumnType_Ressya,ColumnType_Ressyabangou) の
			//	結合セルを設定
			pCDcdGridCell->setAttachCellCount(1, 1);

			//　(2.2.*.2)　セル の	DcDrawオブジェクトの型を設定
			//	( CDcdTextbox とする)。
			{
				pCDcDrawCell = dynamic_castOu<CDcDrawCell>(
					pCDcdGridCell->getIfDcDraw());
				if (pCDcDrawCell == NULL)
				{
					pCDcDrawCell = OuNew<CDcDrawCell>(new CDcDrawCell);
					pCDcdGridCell->setIfDcDraw(pCDcDrawCell);
				}
			}

			//　(2.2.*.3)　セルの DcDrawオブジェクトに、属性を設定。
			{
				/**
					運用番号描写手順
					1.最初にstrOperationNumberに運番を読み込む
					2.運番が空の場合は空白を描写する
					3.空でない場合、表示段数の最下段以外の場合は、strOperationNumberの先頭要素を描写し、先頭要素を削除して次の段へ
					4.空でない場合、表示段数の最下段に到達したら、strOperationNumberに残っている要素を、'+'で連結して描写する。
				*/
				tstring strText;
				if (strOperationNumber.empty())
				{
					strText = _T("");
				}
				else if (idx == m_iOperationNumberRows - 1)
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

				*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
				pCDcDrawCell->setText(strText);
			}

			//セルの背景色を指定します。
			{
				pCDcDrawCell->setCdBrushProp(CdColorProp(255, 255, 255));
			}
		}
	}
}


void CCellBuilder::update02_02_02_02_setRessya_Ressyasyubetsu( 
		int iXColumnNumber ,
		int iYColumnNumber,
		const CentDedRessya* pCentDedRessya ,
		CWndJikokuhyou* pCWndJikokuhyou ) 
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid() ;
	const CentDedRosen* pCentDedRosen = 
		m_pCDedRosenFileData->getCentDedRosen() ;
	// --------------------------------
	//CDcdTargetGetDC	aCDcdTarget( NULL ) ;
	// --------------------------------
	//CdYColSpec aCdYColSpec( 
	//	CdYColSpec::ColumnType_Ressyasyubetsu ) ;
	//int iYColumnNumber = 
	//	m_CdYColSpecCont.ColumnNumberFromSpec( aCdYColSpec , false ) ;
	CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell( 
		iXColumnNumber , iYColumnNumber ) ;
	// --------------------------------
	if ( pCDcdGridCell != 0 )
	{
		typedef CDcdTextbox CDcDrawCell ;
		Ou<CDcDrawCell> pCDcDrawCell ;
		// --------------------------------
		//　(2.2.*.1)　セル(ColumnType_Ressya,ColumnType_Ressyabangou) の
		//	結合セルを設定
		pCDcdGridCell->setAttachCellCount( 1 , 1 ) ;

		//　(2.2.*.2)　セル の	DcDrawオブジェクトの型を設定
		//	( CDcdTextbox とする)。
		{
			pCDcDrawCell = dynamic_castOu<CDcDrawCell>( 
				pCDcdGridCell->getIfDcDraw() ) ;
			if ( pCDcDrawCell == NULL )
			{
				pCDcDrawCell = OuNew<CDcDrawCell>( new CDcDrawCell ) ;
				pCDcdGridCell->setIfDcDraw( pCDcDrawCell ) ;
			}
		}

		//　(2.2.*.3)　セルの DcDrawオブジェクトに、属性を設定。
		{
			int idxRessyasyubetsu 
				= pCentDedRessya->getRessyasyubetsuIndex() ;
			const CentDedRessyasyubetsu* pCentDedRessyasyubetsu = NULL ;
			{
				pCentDedRessyasyubetsu = 
					pCentDedRosen->getCentDedRessyasyubetsuCont()->getMuPtr()
						->get( idxRessyasyubetsu ) ;
				if (m_bDisplayParentSyubetsu && pCentDedRessyasyubetsu->getParentSyubetsuIndex() >= 0)
				{
					pCentDedRessyasyubetsu
						= pCentDedRosen->getCentDedRessyasyubetsuCont()->getMuPtr()
						->get(pCentDedRessyasyubetsu->getParentSyubetsuIndex());
				}
				if ( pCentDedRessyasyubetsu == NULL )
				{
					pCentDedRessyasyubetsu = 
						pCentDedRosen->getCentDedRessyasyubetsuCont()
						->getMuPtr()->get( 0 ) ;
				}
			}
			//pCentDedRessyasyubetsu = 列車種別オブジェクト
			//	(指定がないなら、列車種別[0])

			tstring strText ;
			if ( !pCentDedRessya->isNull() )
			{
				strText = pCentDedRessyasyubetsu->getRyakusyou() ;
			}
			*pCDcDrawCell = createCDcdEkijikoku( idxRessyasyubetsu );
			pCDcDrawCell->setText( strText );
		}

		//セルの背景色を指定します。
		{
			pCDcDrawCell->setCdBrushProp(CdColorProp(255, 255, 255));
		}
	}

}
	
void CCellBuilder::update02_02_02_03_setRessya_Ressyamei( 
		int iXColumnNumber ,
		int iYColumnNumber,
		const CentDedRessya* pCentDedRessya ,
		CWndJikokuhyou* pCWndJikokuhyou ) 
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid() ;
	//const CentDedRosen* pCentDedRosen = 
	//	m_pCDedRosenFileData->getCentDedRosen() ;
	// --------------------------------
	//CDcdTargetGetDC	aCDcdTarget( NULL ) ;
	// --------------------------------
	//CdYColSpec aCdYColSpec( 
	//	CdYColSpec::ColumnType_Ressyamei ) ;
	//int iYColumnNumber = 
	//	m_CdYColSpecCont.ColumnNumberFromSpec( aCdYColSpec , false ) ;
	CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell( 
		iXColumnNumber , iYColumnNumber ) ;
	// --------------------------------
	if ( pCDcdGridCell != 0 )
	{
		typedef CDcdTextboxV3 CDcDrawCell ;
		Ou<CDcDrawCell> pCDcDrawCell ;
		// --------------------------------
		//　(2.2.*.1)　セル(ColumnType_Ressya,ColumnType_Ressyabangou) の
		//	結合セルを設定
		pCDcdGridCell->setAttachCellCount( 1 , 1 ) ;

		//　(2.2.*.2)　セル の	DcDrawオブジェクトの型を設定
		//	( CDcdTextbox とする)。
		{
			pCDcDrawCell = dynamic_castOu<CDcDrawCell>( 
				pCDcdGridCell->getIfDcDraw() ) ;
			if ( pCDcDrawCell == NULL )
			{
				pCDcDrawCell = OuNew<CDcDrawCell>( new CDcDrawCell ) ;
				pCDcdGridCell->setIfDcDraw( pCDcDrawCell ) ;
			}
		}
		//　(2.2.*.3)　セルの DcDrawオブジェクトに、属性を設定。
		{
			int idxRessyasyubetsu 
				= pCentDedRessya->getRessyasyubetsuIndex() ;
			tstring strText ;
			if ( !pCentDedRessya->isNull() )
			{
				strText = pCentDedRessya->getRessyamei() ;
			}
			*pCDcDrawCell = createCDcdRessyamei( idxRessyasyubetsu );
			pCDcDrawCell->setText( strText );
		}

		//セルの背景色を指定します。
		{
			pCDcDrawCell->setCdBrushProp(CdColorProp(255, 255, 255));
		}
	}


}
	
void CCellBuilder::update02_02_02_04_setRessya_Gousuu( 
		int iXColumnNumber ,
		int iYColumnNumber,
		const CentDedRessya* pCentDedRessya ,
		CWndJikokuhyou* pCWndJikokuhyou ) 
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid() ;
	//const CentDedRosen* pCentDedRosen = 
	//	m_pCDedRosenFileData->getCentDedRosen() ;
	// --------------------------------
	//CDcdTargetGetDC	aCDcdTarget( NULL ) ;
	// --------------------------------
	//CdYColSpec aCdYColSpec( 
	//	CdYColSpec::ColumnType_Gousuu ) ;
	//int iYColumnNumber = 
	//	m_CdYColSpecCont.ColumnNumberFromSpec( aCdYColSpec , false ) ;
	CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell( 
		iXColumnNumber , iYColumnNumber ) ;
	// --------------------------------
	if ( pCDcdGridCell != 0 )
	{
		typedef CDcdTextbox CDcDrawCell ;
		Ou<CDcDrawCell> pCDcDrawCell ;
		// --------------------------------
		//　(2.2.*.1)　セル(ColumnType_Ressya,ColumnType_Ressyabangou) の
		//	結合セルを設定
		pCDcdGridCell->setAttachCellCount( 1 , 1 ) ;

		//　(2.2.*.2)　セル の	DcDrawオブジェクトの型を設定
		//	( CDcdTextbox とする)。
		{
			pCDcDrawCell = dynamic_castOu<CDcDrawCell>( 
				pCDcdGridCell->getIfDcDraw() ) ;
			if ( pCDcDrawCell == NULL )
			{
				pCDcDrawCell = OuNew<CDcDrawCell>( new CDcDrawCell ) ;
				pCDcdGridCell->setIfDcDraw( pCDcDrawCell ) ;
			}
		}
		//　(2.2.*.3)　セルの DcDrawオブジェクトに、属性を設定。
		{
			int idxRessyasyubetsu 
				= pCentDedRessya->getRessyasyubetsuIndex() ;
			tstring strText = pCentDedRessya->getGousuu() ;
			*pCDcDrawCell = createCDcdRessyabangou( idxRessyasyubetsu );
			pCDcDrawCell->setText( strText );
		}

		//セルの背景色を指定します。
		{
			pCDcDrawCell->setCdBrushProp(CdColorProp(255, 255, 255));
		}
	}
}
	
void CCellBuilder::update02_02_02_05_setRessya_Gou( 
		int iXColumnNumber ,
		int iYColumnNumber,
		const CentDedRessya* pCentDedRessya ,
		CWndJikokuhyou* pCWndJikokuhyou ) 
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid() ;
	//const CentDedRosen* pCentDedRosen = 
	//	m_pCDedRosenFileData->getCentDedRosen() ;
	// --------------------------------
	//CDcdTargetGetDC	aCDcdTarget( NULL ) ;
	// --------------------------------
	//CdYColSpec aCdYColSpec( 
	//	CdYColSpec::ColumnType_Gou ) ;
	//int iYColumnNumber = 
	//	m_CdYColSpecCont.ColumnNumberFromSpec( aCdYColSpec , false ) ;
	CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell( 
		iXColumnNumber , iYColumnNumber ) ;
	// --------------------------------
	if ( pCDcdGridCell != 0 )
	{
		typedef CDcdTextbox CDcDrawCell ;
		Ou<CDcDrawCell> pCDcDrawCell ;
		// --------------------------------
		//　(2.2.*.1)　セルの結合セルを設定
		pCDcdGridCell->setAttachCellCount( 1 , 1 ) ;

		//　(2.2.*.2)　セル の	DcDrawオブジェクトの型を設定
		//	( CDcdTextbox とする)。
		{
			pCDcDrawCell = dynamic_castOu<CDcDrawCell>( 
				pCDcdGridCell->getIfDcDraw() ) ;
			if ( pCDcDrawCell == NULL )
			{
				pCDcDrawCell = OuNew<CDcDrawCell>( new CDcDrawCell ) ;
				pCDcdGridCell->setIfDcDraw( pCDcDrawCell ) ;
			}
		}
		//　(2.2.*.3)　セルの DcDrawオブジェクトに、属性を設定。
		{
			int idxRessyasyubetsu 
				= pCentDedRessya->getRessyasyubetsuIndex() ;

			CString	strText ;
			if ( !pCentDedRessya->getGousuu().empty() )
			{
				strText.LoadString( IDS_WORD_GOUSUU2 ) ;
			}

			*pCDcDrawCell = createCDcdRessyabangou( idxRessyasyubetsu );
			pCDcDrawCell->setText( (LPCTSTR)strText );
		}

		//セルの背景色を指定します。
		{
			pCDcDrawCell->setCdBrushProp(CdColorProp(255, 255, 255));
		}
	}
}

void CCellBuilder::update02_02_02_13_setRessya_ShihatsuEkimei(
	int iXColumnNumber,
	int iYColumnNumber,
	const CentDedRessya * pCentDedRessya,
	CWndJikokuhyou * pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	const CentDedRosen* pCentDedRosen =
		m_pCDedRosenFileData->getCentDedRosen();
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		pCentDedRosen->getCentDedEkiCont()->getMuPtr(
			pCentDedRessya->getRessyahoukou());
	// --------------------------------
	//CDcdTargetGetDC	aCDcdTarget(NULL);
	// --------------------------------
	{
		//CdYColSpec aCdYColSpec(
		//	CdYColSpec::ColumnType_ShihatsuEkimei);
		//int iYColumnNumber =
		//	m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec, false);
		CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell(
			iXColumnNumber, iYColumnNumber);
		// --------------------------------
		if (pCDcdGridCell != 0)
		{
			typedef CDcdTextbox CDcDrawCell;
			Ou<CDcDrawCell> pCDcDrawCell;
			// --------------------------------
			//　(2.2.*.1)　セルの結合セルを設定
			pCDcdGridCell->setAttachCellCount(1, 1);

			//　(2.2.*.2)　セル の	DcDrawオブジェクトの型を設定
			//	( CDcdTextbox とする)。
			{
				pCDcDrawCell = dynamic_castOu<CDcDrawCell>(
					pCDcdGridCell->getIfDcDraw());
				if (pCDcDrawCell == NULL)
				{
					pCDcDrawCell = OuNew<CDcDrawCell>(new CDcDrawCell);
					pCDcdGridCell->setIfDcDraw(pCDcDrawCell);
				}
			}
			//　(2.2.*.3)　セルの DcDrawオブジェクトに、属性を設定。
			{
				//pCDcDrawCell->setText("");
				pCDcDrawCell->setCdDrawTextProp(getCdDrawTextPropOperation());
				tstring strText = _T("");
				//ここでの始発駅は、先端作業がある駅という意味があるので、Validを用いる
				if (pCentDedRessya->getValidSihatsuEki() >= 0 && pCentDedRessya->getValidSihatsuEki() < muCdDedEki->size())
				{
					strText = muCdDedEki->get(pCentDedRessya->getValidSihatsuEki()).getEkimeiJikokuhyouRyaku(true);
				}
				pCDcDrawCell->setText(strText);
			}

			//セルの背景色を指定します。
			{
				pCDcDrawCell->setCdBrushProp(CdColorProp(255, 255, 255));
			}
		}
	}
}

void CCellBuilder::update02_02_02_10_setRessya_Operation_Shihatsu(
	int iXColumnNumber,
	int iYColumnNumber,
	const CentDedRessya * pCentDedRessya,
	CWndJikokuhyou * pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	const CentDedRosen* pCentDedRosen =
		m_pCDedRosenFileData->getCentDedRosen();
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		pCentDedRosen->getCentDedEkiCont()->getMuPtr(
			pCentDedRessya->getRessyahoukou());
	// --------------------------------
	//CDcdTargetGetDC	aCDcdTarget(NULL);
	// --------------------------------
	{
		//CdYColSpec aCdYColSpec1(
		//	CdYColSpec::ColumnType_Operation_Shihatsu1);
		//CdYColSpec aCdYColSpec2(
		//	CdYColSpec::ColumnType_Operation_Shihatsu2);
		//CdYColSpec aCdYColSpec3(
		//	CdYColSpec::ColumnType_Operation_Shihatsu3);
		//int iYColumnNumber1 =
		//	m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec1, false);
		//int iYColumnNumber2 =
		//	m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec2, false);
		//int iYColumnNumber3 =
		//	m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec3, false);
		CDcdGridCell* pCDcdGridCell1 = pCDcdGrid->getCell(
			iXColumnNumber, iYColumnNumber);
		CDcdGridCell* pCDcdGridCell2 = pCDcdGrid->getCell(
			iXColumnNumber, iYColumnNumber+1);
		CDcdGridCell* pCDcdGridCell3 = NULL;
		CDcdGridCell* pCDcdGridCell4 = NULL;
		if (m_iEnableOperation > 1)
		{
			pCDcdGridCell3 = pCDcdGrid->getCell(
				iXColumnNumber, iYColumnNumber + 2);
			if (m_bDisplayInOutLinkCode)
			{
				pCDcdGridCell4 = pCDcdGrid->getCell(
					iXColumnNumber, iYColumnNumber + 3);
			}
		}
		// --------------------------------
		if (pCDcdGridCell1 != 0 && pCDcdGridCell2 != 0)
		{
			typedef CDcdTextbox CDcDrawCell;
			Ou<CDcDrawCell> pCDcDrawCell1;
			Ou<CDcDrawCell> pCDcDrawCell2;
			Ou<CDcDrawCell> pCDcDrawCell3;
			Ou<CDcDrawCell> pCDcDrawCell4;
			// --------------------------------
			//　(2.2.*.1)　セルの結合セルを設定
			pCDcdGridCell1->setAttachCellCount(1, 1);
			pCDcdGridCell2->setAttachCellCount(1, 1);
			if (pCDcdGridCell3 != 0)
			{
				pCDcdGridCell3->setAttachCellCount(1, 1);
			}
			if (pCDcdGridCell4 != 0)
			{
				pCDcdGridCell4->setAttachCellCount(1, 1);
			}

			//　(2.2.*.2)　セル の	DcDrawオブジェクトの型を設定
			//	( CDcdTextbox とする)。
			{
				pCDcDrawCell1 = dynamic_castOu<CDcDrawCell>(
					pCDcdGridCell1->getIfDcDraw());
				pCDcDrawCell2 = dynamic_castOu<CDcDrawCell>(
					pCDcdGridCell2->getIfDcDraw());
				if (pCDcDrawCell1 == NULL)
				{
					pCDcDrawCell1 = OuNew<CDcDrawCell>(new CDcDrawCell);
					pCDcdGridCell1->setIfDcDraw(pCDcDrawCell2);
				}
				if (pCDcDrawCell2 == NULL)
				{
					pCDcDrawCell2 = OuNew<CDcDrawCell>(new CDcDrawCell);
					pCDcdGridCell2->setIfDcDraw(pCDcDrawCell2);
				}
				if (pCDcdGridCell3 != 0)
				{
					pCDcDrawCell3 = dynamic_castOu<CDcDrawCell>(
						pCDcdGridCell3->getIfDcDraw());
					if (pCDcDrawCell3 == NULL)
					{
						pCDcDrawCell3 = OuNew<CDcDrawCell>(new CDcDrawCell);
						pCDcdGridCell3->setIfDcDraw(pCDcDrawCell3);
					}
				}
				if (pCDcdGridCell4 != 0)
				{
					pCDcDrawCell4 = dynamic_castOu<CDcDrawCell>(
						pCDcdGridCell4->getIfDcDraw());
					if (pCDcDrawCell4 == NULL)
					{
						pCDcDrawCell4 = OuNew<CDcDrawCell>(new CDcDrawCell);
						pCDcdGridCell4->setIfDcDraw(pCDcDrawCell4);
					}
				}
			}
			//　(2.2.*.3)　セルの DcDrawオブジェクトに、属性を設定。
			{
				pCDcDrawCell1->setCdDrawTextProp(getCdDrawTextPropOperation());
				pCDcDrawCell2->setCdDrawTextProp(getCdDrawTextPropOperation());
				if (pCDcDrawCell3 != NULL)
				{
					pCDcDrawCell3->setCdDrawTextProp(getCdDrawTextPropOperation());
				}
				if (pCDcDrawCell4 != NULL)
				{
					pCDcDrawCell4->setCdDrawTextProp(getCdDrawTextPropOperation());
				}
				tstring strText1 = _T("");
				tstring strText2 = _T("");
				tstring strText3 = _T("");
				tstring strText4 = _T("");

				/**
					開始作業の秒単位処理は、着時刻設定に基づき行います。
				*/

				const CentDedBeforeOperation aFirstOperation = pCentDedRessya->getFirstOperation();
				if (aFirstOperation.getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Out)
				{
					strText1 = tstringOf(
						(LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_OperationOut));
					//Ver2.05 運用機能が通常モードかつ入出区連携コードが入力されている場合は、"出区"の後に入出区連携コードを表示します。
					//	→単独欄表示に変更
					//if (m_iEnableOperation > 1 && !aFirstOperation.getInOutLinkCode().empty())
					//{
					//	strText1 += _T("/");
					//	strText1 += aFirstOperation.getInOutLinkCode();
					//}

					CdDedJikoku aCdDedJikoku
						= aFirstOperation.getOutJikoku();
					strText2 = getCdDedJikokuConv().encode(aCdDedJikoku,true);

					strText3 = joinc(';', aFirstOperation.getOperationNumberOriginal());

					strText4 = aFirstOperation.getInOutLinkCode();
				}
				else if (aFirstOperation.getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
				{
					CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(pCentDedRessya->getValidSihatsuEki());
					//Ver2.05 運用機能が通常モードかつ入出区連携コードが入力されている場合は、路線外始発駅名欄を、ダイヤ略称+入出区連携コードに変更します。
					//	→単独欄表示に変更
					//if (m_iEnableOperation > 1 && !aFirstOperation.getInOutLinkCode().empty())
					//{
					//	strText1 = aCdDedEki.getOuterTerminalDiaRyaku(aFirstOperation.getOuterShihatsuekiIndex(), true);
					//	strText1 += _T("/");
					//	strText1 += aFirstOperation.getInOutLinkCode();
					//}
					//else
					//{
					strText1 = aCdDedEki.getOuterTerminalJikokuRyaku(aFirstOperation.getOuterShihatsuekiIndex(), true);
					//}

					CdDedJikoku aCdDedJikoku
						= aFirstOperation.getChakuJikoku();
					if (aCdDedJikoku.isNull())
					{
						aCdDedJikoku = pCentDedRessya->getCentDedEkiJikoku(
							pCentDedRessya->getValidSihatsuEki()).getHatsujikoku();
						pCDcDrawCell2->setCdDrawTextProp(
							getCdDrawTextPropTsuuka());
					}
					strText2 = getCdDedJikokuConv().encode(aCdDedJikoku, true);
					strText2 += tstringOf(
						(LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_Chaku));
					//strText2 += _T("着");

					strText3 = joinc(';', aFirstOperation.getOperationNumberOriginal());

					strText4 = aFirstOperation.getInOutLinkCode();
				}
				//2.00.05 仮運用番号に対応
				else if (aFirstOperation.getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Junction)
				{
					strText1 = _T("");

					CdDedJikoku aCdDedJikoku
						= aFirstOperation.getOriginJikoku();
					strText2 = getCdDedJikokuConv().encode(aCdDedJikoku, true);

					strText3 = joinc(';', aFirstOperation.getOperationNumberTemp());
					if (pCDcDrawCell3 != NULL)
					{
						pCDcDrawCell3->setCdDrawTextProp(
							getCdDrawTextPropTsuuka());
					}
				}
				pCDcDrawCell1->setText(strText1);
				pCDcDrawCell2->setText(strText2);
				if (pCDcDrawCell3 != NULL)
				{
					pCDcDrawCell3->setText(strText3);
				}
				if (pCDcDrawCell4 != NULL)
				{
					pCDcDrawCell4->setText(strText4);
				}

			}

			//セルの背景色を指定します。
			{
				pCDcDrawCell1->setCdBrushProp(CdColorProp(255, 255, 255));
				pCDcDrawCell2->setCdBrushProp(CdColorProp(255, 255, 255));
				if (pCDcDrawCell3 != NULL)
				{
					pCDcDrawCell3->setCdBrushProp(CdColorProp(255, 255, 255));
				}
				if (pCDcDrawCell4 != NULL)
				{
					pCDcDrawCell4->setCdBrushProp(CdColorProp(255, 255, 255));
				}
			}
		}
	}
}

void CCellBuilder::update02_02_02_14_setRessya_ShuchakuEkimei(
	int iXColumnNumber,
	int iYColumnNumber,
	const CentDedRessya * pCentDedRessya,
	CWndJikokuhyou * pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	const CentDedRosen* pCentDedRosen =
		m_pCDedRosenFileData->getCentDedRosen();
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		pCentDedRosen->getCentDedEkiCont()->getMuPtr(
			pCentDedRessya->getRessyahoukou());
	// --------------------------------
	//CDcdTargetGetDC	aCDcdTarget(NULL);
	// --------------------------------
	{
		//CdYColSpec aCdYColSpec(
		//	CdYColSpec::ColumnType_ShuchakuEkimei);
		//int iYColumnNumber =
		//	m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec, false);
		CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell(
			iXColumnNumber, iYColumnNumber);
		// --------------------------------
		if (pCDcdGridCell != 0)
		{
			typedef CDcdTextbox CDcDrawCell;
			Ou<CDcDrawCell> pCDcDrawCell;
			// --------------------------------
			//　(2.2.*.1)　セルの結合セルを設定
			pCDcdGridCell->setAttachCellCount(1, 1);

			//　(2.2.*.2)　セル の	DcDrawオブジェクトの型を設定
			//	( CDcdTextbox とする)。
			{
				pCDcDrawCell = dynamic_castOu<CDcDrawCell>(
					pCDcdGridCell->getIfDcDraw());
				if (pCDcDrawCell == NULL)
				{
					pCDcDrawCell = OuNew<CDcDrawCell>(new CDcDrawCell);
					pCDcdGridCell->setIfDcDraw(pCDcDrawCell);
				}
			}
			//　(2.2.*.3)　セルの DcDrawオブジェクトに、属性を設定。
			{
				//pCDcDrawCell->setText("");
				pCDcDrawCell->setCdDrawTextProp(getCdDrawTextPropOperation());
				tstring strText = _T("");
				//ここでの終着駅は、末端作業がある駅という意味があるので、Validを用いる。
				if (pCentDedRessya->getValidSyuuchakuEki() >= 0 && pCentDedRessya->getValidSyuuchakuEki() < muCdDedEki->size())
				{
					strText = muCdDedEki->get(pCentDedRessya->getValidSyuuchakuEki()).getEkimeiJikokuhyouRyaku(true);
				}
				pCDcDrawCell->setText(strText);
			}

			//セルの背景色を指定します。
			{
				pCDcDrawCell->setCdBrushProp(CdColorProp(255, 255, 255));
			}
		}
	}
}

void CCellBuilder::update02_02_02_11_setRessya_Operation_Shuchaku(
	int iXColumnNumber,
	int iYColumnNumber,
	const CentDedRessya * pCentDedRessya,
	CWndJikokuhyou * pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	const CentDedRosen* pCentDedRosen =
		m_pCDedRosenFileData->getCentDedRosen();
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		pCentDedRosen->getCentDedEkiCont()->getMuPtr(
			pCentDedRessya->getRessyahoukou());
	// --------------------------------
	//CDcdTargetGetDC	aCDcdTarget(NULL);
	// --------------------------------
	{
		//CdYColSpec aCdYColSpec1(
		//	CdYColSpec::ColumnType_Operation_Shuchaku1);
		//CdYColSpec aCdYColSpec2(
		//	CdYColSpec::ColumnType_Operation_Shuchaku2);
		//int iYColumnNumber1 =
		//	m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec1, false);
		//int iYColumnNumber2 =
		//	m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec2, false);
		CDcdGridCell* pCDcdGridCell1 = pCDcdGrid->getCell(
			iXColumnNumber, iYColumnNumber);
		CDcdGridCell* pCDcdGridCell2 = pCDcdGrid->getCell(
			iXColumnNumber, iYColumnNumber+1);
		CDcdGridCell* pCDcdGridCell3 = NULL;
		if (m_iEnableOperation > 1 && m_bDisplayInOutLinkCode)
		{
			pCDcdGridCell3 = pCDcdGrid->getCell(
				iXColumnNumber, iYColumnNumber + 2);
		}
		// --------------------------------
		if (pCDcdGridCell1 != 0 && pCDcdGridCell2 != 0)
		{
			typedef CDcdTextbox CDcDrawCell;
			Ou<CDcDrawCell> pCDcDrawCell1;
			Ou<CDcDrawCell> pCDcDrawCell2;
			Ou<CDcDrawCell> pCDcDrawCell3;
			// --------------------------------
			//　(2.2.*.1)　セルの結合セルを設定
			pCDcdGridCell1->setAttachCellCount(1, 1);
			pCDcdGridCell2->setAttachCellCount(1, 1);
			if (pCDcdGridCell3 != 0)
			{
				pCDcdGridCell3->setAttachCellCount(1, 1);
			}

			//　(2.2.*.2)　セル の	DcDrawオブジェクトの型を設定
			//	( CDcdTextbox とする)。
			{
				pCDcDrawCell1 = dynamic_castOu<CDcDrawCell>(
					pCDcdGridCell1->getIfDcDraw());
				pCDcDrawCell2 = dynamic_castOu<CDcDrawCell>(
					pCDcdGridCell2->getIfDcDraw());
				if (pCDcDrawCell1 == NULL)
				{
					pCDcDrawCell1 = OuNew<CDcDrawCell>(new CDcDrawCell);
					pCDcdGridCell1->setIfDcDraw(pCDcDrawCell2);
				}
				if (pCDcDrawCell2 == NULL)
				{
					pCDcDrawCell2 = OuNew<CDcDrawCell>(new CDcDrawCell);
					pCDcdGridCell2->setIfDcDraw(pCDcDrawCell2);
				}
				if (pCDcdGridCell3 != 0)
				{
					pCDcDrawCell3 = dynamic_castOu<CDcDrawCell>(
						pCDcdGridCell3->getIfDcDraw());
					if (pCDcDrawCell3 == NULL)
					{
						pCDcDrawCell3 = OuNew<CDcDrawCell>(new CDcDrawCell);
						pCDcdGridCell3->setIfDcDraw(pCDcDrawCell3);
					}
				}
			}
			//　(2.2.*.3)　セルの DcDrawオブジェクトに、属性を設定。
			{
				pCDcDrawCell1->setCdDrawTextProp(getCdDrawTextPropOperation());
				pCDcDrawCell2->setCdDrawTextProp(getCdDrawTextPropOperation());
				if (pCDcDrawCell3 != NULL)
				{
					pCDcDrawCell3->setCdDrawTextProp(getCdDrawTextPropOperation());
				}
				tstring strText1 = _T("");
				tstring strText2 = _T("");
				tstring strText3 = _T("");

				/**
					終了作業の秒単位処理は、発時刻設定に基づき行います。
				*/

				const CentDedAfterOperation aLastOperation = pCentDedRessya->getLastOperation();
				if (aLastOperation.getAOperation() == CentDedAfterOperation::EAOperation::AOperation_In)
				{
					strText1 = tstringOf(
						(LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_OperationIn));
					//Ver2.05 運用機能が通常モードかつ入出区連携コードが入力されている場合は、"入区"の後に入出区連携コードを表示します。
					//	→単独欄表示に変更
					//if (m_iEnableOperation > 1 && !aLastOperation.getInOutLinkCode().empty())
					//{
					//	strText1 += _T("/");
					//	strText1 += aLastOperation.getInOutLinkCode();
					//}

					CdDedJikoku aCdDedJikoku
						= aLastOperation.getInJikoku();
					strText2 = getCdDedJikokuConv().encode(aCdDedJikoku,false);

					strText3 = aLastOperation.getInOutLinkCode();
				}
				else if (aLastOperation.getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
				{
					CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(pCentDedRessya->getValidSyuuchakuEki());
					//Ver2.05 運用機能が通常モードかつ入出区連携コードが入力されている場合は、路線外終着駅名欄を、ダイヤ略称+入出区連携コードに変更します。
					//	→単独欄表示に変更
					//if (m_iEnableOperation > 1 && !aLastOperation.getInOutLinkCode().empty())
					//{
					//	strText1 = aCdDedEki.getOuterTerminalDiaRyaku(aLastOperation.getOuterShuchakuekiIndex(), true);
					//	strText1 += _T("/");
					//	strText1 += aLastOperation.getInOutLinkCode();
					//}
					//else
					//{
					strText1 = aCdDedEki.getOuterTerminalJikokuRyaku(aLastOperation.getOuterShuchakuekiIndex(), true);
					//}

					CdDedJikoku aCdDedJikoku
						= aLastOperation.getHatsuJikoku();
					if (aCdDedJikoku.isNull())
					{
						aCdDedJikoku = pCentDedRessya->getCentDedEkiJikoku(
							pCentDedRessya->getValidSyuuchakuEki()).getChakujikoku();
						pCDcDrawCell2->setCdDrawTextProp(
							getCdDrawTextPropTsuuka());
					}
					strText2 = getCdDedJikokuConv().encode(aCdDedJikoku, false);
					strText2 += tstringOf(
						(LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_Hatsu));
					//strText2 += _T("発");

					strText3 = aLastOperation.getInOutLinkCode();
				}
				else if (aLastOperation.getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Junction)
				{
					//Ver2.05 1行目には、次列車接続タイプを表示する
					if (aLastOperation.getNextJunctionType() == 1)
					{
						strText1 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_SYUBETSUCHANGE);
					}
					else if (aLastOperation.getNextJunctionType() == 2) 
					{
						strText1 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_PROPERTYCHANGE);
					}
					else if (aLastOperation.getNextJunctionType() == 3)
					{
						strText1 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_PROPERTYSAME);
					}
					else
					{
						strText1 = _T("");
					}

					CdDedJikoku aCdDedJikoku
						= aLastOperation.getTerminalJikoku();
					strText2 = getCdDedJikokuConv().encode(aCdDedJikoku, false);
				}

				pCDcDrawCell1->setText(strText1);
				pCDcDrawCell2->setText(strText2);
				if (pCDcDrawCell3 != NULL)
				{
					pCDcDrawCell3->setText(strText3);
				}
			}

			//セルの背景色を指定します。
			{
				pCDcDrawCell1->setCdBrushProp(CdColorProp(255, 255, 255));
				pCDcDrawCell2->setCdBrushProp(CdColorProp(255, 255, 255));
				if (pCDcDrawCell3 != NULL)
				{
					pCDcDrawCell3->setCdBrushProp(CdColorProp(255, 255, 255));
				}
			}
		}
	}
}

void CCellBuilder::update02_02_02_15_setRessya_OuterTerminal_Shihatsu(
	int iXColumnNumber,
	int iYColumnNumber,
	const CentDedRessya * pCentDedRessya,
	CWndJikokuhyou * pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	const CentDedRosen* pCentDedRosen =
		m_pCDedRosenFileData->getCentDedRosen();
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		pCentDedRosen->getCentDedEkiCont()->getMuPtr(
			pCentDedRessya->getRessyahoukou());
	// --------------------------------
	//CDcdTargetGetDC	aCDcdTarget(NULL);
	// --------------------------------
	{
		//CdYColSpec aCdYColSpec1(
		//	CdYColSpec::ColumnType_Outer_Shihatsu1);
		//CdYColSpec aCdYColSpec2(
		//	CdYColSpec::ColumnType_Outer_Shihatsu2);
		//int iYColumnNumber1 =
		//	m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec1, false);
		//int iYColumnNumber2 =
		//	m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec2, false);
		CDcdGridCell* pCDcdGridCell1 = pCDcdGrid->getCell(
			iXColumnNumber, iYColumnNumber);
		CDcdGridCell* pCDcdGridCell2 = pCDcdGrid->getCell(
			iXColumnNumber, iYColumnNumber+1);
		// --------------------------------
		if (pCDcdGridCell1 != 0 && pCDcdGridCell2 != 0)
		{
			typedef CDcdTextbox CDcDrawCell;
			Ou<CDcDrawCell> pCDcDrawCell1;
			Ou<CDcDrawCell> pCDcDrawCell2;
			// --------------------------------
			//　(2.2.*.1)　セルの結合セルを設定
			pCDcdGridCell1->setAttachCellCount(1, 1);
			pCDcdGridCell2->setAttachCellCount(1, 1);

			//　(2.2.*.2)　セル の	DcDrawオブジェクトの型を設定
			//	( CDcdTextbox とする)。
			{
				pCDcDrawCell1 = dynamic_castOu<CDcDrawCell>(
					pCDcdGridCell1->getIfDcDraw());
				pCDcDrawCell2 = dynamic_castOu<CDcDrawCell>(
					pCDcdGridCell2->getIfDcDraw());
				if (pCDcDrawCell1 == NULL)
				{
					pCDcDrawCell1 = OuNew<CDcDrawCell>(new CDcDrawCell);
					pCDcdGridCell1->setIfDcDraw(pCDcDrawCell1);
				}
				if (pCDcDrawCell2 == NULL)
				{
					pCDcDrawCell2 = OuNew<CDcDrawCell>(new CDcDrawCell);
					pCDcdGridCell2->setIfDcDraw(pCDcDrawCell2);
				}
			}
			//　(2.2.*.3)　セルの DcDrawオブジェクトに、属性を設定。
			{
				int idxRessyasyubetsu
					= pCentDedRessya->getRessyasyubetsuIndex();
				*pCDcDrawCell1 = createCDcdRessyabangou(idxRessyasyubetsu);
				*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);
				//pCDcDrawCell1->setCdDrawTextProp(getCdDrawTextPropOperation());
				//pCDcDrawCell2->setCdDrawTextProp(getCdDrawTextPropOperation());
				tstring strText1;
				tstring strText2;

				const CentDedBeforeOperation aFirstOperation = pCentDedRessya->getFirstOperation();
				if (aFirstOperation.getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
				{
					CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(pCentDedRessya->getValidSihatsuEki());
					strText1 = aCdDedEki.getOuterTerminalJikokuRyaku(aFirstOperation.getOuterShihatsuekiIndex(),true);
					if (!(aFirstOperation.getOuterShihatsuJikoku().isNull()))
					{
						CdDedJikoku aCdDedJikoku
							= aFirstOperation.getOuterShihatsuJikoku();
						strText2 = getCdDedJikokuConv().encode(aCdDedJikoku, false);
					}
				}
				pCDcDrawCell1->setText(strText1);
				pCDcDrawCell2->setText(strText2);

			}

			//セルの背景色を指定します。
			{
				pCDcDrawCell1->setCdBrushProp(CdColorProp(255, 255, 255));
				pCDcDrawCell2->setCdBrushProp(CdColorProp(255, 255, 255));
			}
		}
	}
}

void CCellBuilder::update02_02_02_06_setRessya_Chaku( 
		int iXColumnNumber ,
	int iYColumnNumber,
		const CentDedRessya* pCentDedRessya ,
		int iEkiOrder ,
		CWndJikokuhyou* pCWndJikokuhyou ) 
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid() ;
	const CentDedRosen* pCentDedRosen = 
		m_pCDedRosenFileData->getCentDedRosen() ;
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki = 
		pCentDedRosen->getCentDedEkiCont()->getMuPtr(
			pCentDedRessya->getRessyahoukou() ) ;
	// --------------------------------
	//CDcdTargetGetDC	aCDcdTarget( NULL ) ;
	// --------------------------------
	{
		//CdYColSpec aCdYColSpec( 
		//	CdYColSpec::ColumnType_Ekijikoku_Chaku , 
		//	iEkiOrder ) ;
		//int iYColumnNumber = 
		//	m_CdYColSpecCont.ColumnNumberFromSpec( aCdYColSpec , false ) ;
		CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell( 
			iXColumnNumber , iYColumnNumber ) ;
		// --------------------------------
		if ( pCDcdGridCell != 0 )
		{
			typedef CDcdTextbox CDcDrawCell ;
			Ou<CDcDrawCell> pCDcDrawCell ;
			// --------------------------------
			//　(2.2.*.1)　セルの結合セルを設定
			pCDcdGridCell->setAttachCellCount( 1 , 1 ) ;

			//　(2.2.*.2)　セル の	DcDrawオブジェクトの型を設定
			//	( CDcdTextbox とする)。
			{
				pCDcDrawCell = dynamic_castOu<CDcDrawCell>( 
					pCDcdGridCell->getIfDcDraw() ) ;
				if ( pCDcDrawCell == NULL )
				{
					pCDcDrawCell = OuNew<CDcDrawCell>( new CDcDrawCell ) ;
					pCDcdGridCell->setIfDcDraw( pCDcDrawCell ) ;
				}
			}
			//　(2.2.*.3)　セルの DcDrawオブジェクトに、属性を設定。
			{
				CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get( iEkiOrder ) ;

				int idxRessyasyubetsu 
					= pCentDedRessya->getRessyasyubetsuIndex() ;
				
				//	主要駅では、空欄に主要駅表記を行います。
				//	起点・終点・着発駅のいずれかである場合、
				//	境界線に接している駅である場合は除きます。
				bool bIsSyuyouEkiHyouki = false ;
				if ( aCdDedEki.getEkikibo() == CentDedEki::EEkikibo::Ekikibo_Syuyou 
					&&	0 < iEkiOrder 
					&& iEkiOrder < muCdDedEki->size() - 1 
					&& 	!aCdDedEki.isHatsuChakuHyouji() )
				{
					//	境界線に接している駅である場合は除きます。
					CentDedEkiCont::CdDedEki aCentDedEkiTonari ;
					if ( iEkiOrder > 0 )
					{
						aCentDedEkiTonari = muCdDedEki->get( iEkiOrder - 1 ) ;
					}

					if ( !aCentDedEkiTonari.getKyoukaisen()  && 
						!aCdDedEki.getKyoukaisen() )
					{
						bIsSyuyouEkiHyouki = true ;
					}
				}
				//bIsSyuyouEkiHyouji = 空欄に主要駅表記を行います。

				CentDedEkiJikoku	aCentDedEkiJikoku =
					pCentDedRessya->getCentDedEkiJikoku( iEkiOrder ) ;
				CdDedJikoku aCdDedJikoku 
							= aCentDedEkiJikoku.getChakujikoku() ;


				// --------------------------------
				//	駅時刻に合わせて、セルに文字を表示
				// --------------------------------
				switch( aCentDedEkiJikoku.getEkiatsukai() )
				{
				case CentDedEkiJikoku::Ekiatsukai_None :
					{
						if (iEkiOrder < pCentDedRessya->getSihatsuEki() && pCentDedRessya->getSihatsuEki() != -1)
						{
							if(pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer
								&& m_bDisplayOuterTerminalShihatsu)
							{
								*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
								pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"

							}
							else if (bIsSyuyouEkiHyouki)
							{
								//	主要駅での表記（着発の場合は除く）
								//	"----"
								*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
								pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_UNKOUNASI_SYUYOU));
							}
							else
							{
								//	その他の駅での表記
								//	"・・"
								*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
								pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_UNKOUNASI_IPPAN));
							}
						}
						else if(iEkiOrder>pCentDedRessya->getSyuuchakuEki() && pCentDedRessya->getSyuuchakuEki() != -1)
						{
							if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer
								&& m_bDisplayOuterTerminalShuchaku)
							{
								*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
								pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"

							}
							else if (bIsSyuyouEkiHyouki)
							{
								//	主要駅での表記（着発の場合は除く）
								//	"----"
								*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
								pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_UNKOUNASI_SYUYOU));
							}
							else
							{
								//	その他の駅での表記
								//	"・・"
								*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
								pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_UNKOUNASI_IPPAN));
							}
						}
						else if (iEkiOrder > pCentDedRessya->getSihatsuEki() && pCentDedRessya->getSihatsuEki() != -1 &&
							iEkiOrder < pCentDedRessya->getSyuuchakuEki())
						{
							*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
							pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"
						}
						else if ( bIsSyuyouEkiHyouki )
						{
							//	主要駅での表記（着発の場合は除く）
							//	"----"
							*pCDcDrawCell = createCDcdRessyabangou( idxRessyasyubetsu );
							pCDcDrawCell->setText( (LPCTSTR)MfcUtil::LoadCString( 
									IDS_WORD_JIKOKUHYOU_UNKOUNASI_SYUYOU ) ) ;
						}
						else
						{
							//	その他の駅での表記
							//	"・・"
							*pCDcDrawCell = createCDcdRessyabangou(  idxRessyasyubetsu );
							pCDcDrawCell->setText( (LPCTSTR)MfcUtil::LoadCString( 
									IDS_WORD_JIKOKUHYOU_UNKOUNASI_IPPAN ) ) ;
						}
					}
					break ;
					case CentDedEkiJikoku::Ekiatsukai_Tsuuka :
					{
						if (!aCdDedJikoku.isNull() && m_bDisplayTsuukaEkiJikoku)
						{
							/**
								秒単位表示OFFの場合は、切り上げ・切り捨ての処理を行いますが、
								その補助のため、着時刻が切り上げで、発時刻が30秒以上切り上げまたは切り捨ての場合は、発時刻の取得を行います。
								この駅と次の駅の間が運行なしの場合は、運行なしを超えた先の駅から時刻を取得します。
							*/
							CdDedJikoku aHatsuJikoku;
							if (!getDisplaySecondEkiJikoku() &&
								m_iSecondRoundChaku == 2 &&
								m_iSecondRoundHatsu <= 1)
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
											m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()
											->isSameBrunchLoopGroup(iEkiOrder, iHatsuEkiOrder, pCentDedRessya->getRessyahoukou()))
										{
											aHatsuJikoku = pCentDedRessya->getCentDedEkiJikoku(iHatsuEkiOrder).getHatsujikoku();
										}
									}
								}
							}

							//	通過駅の駅時刻が設定されており、
							//	『通過駅の駅時刻を表示する』指定になっている場合は
							//	時刻を表示

							*pCDcDrawCell = createCDcdEkijikoku(
								idxRessyasyubetsu, 
								CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka);
							tstring strText = getCdDedJikokuConv().encode(aCdDedJikoku, true, aHatsuJikoku);
							pCDcDrawCell->setText(strText);
							pCDcDrawCell->setCdBrushProp(CdColorProp(255, 255, 255));
							//基準運転時分機能Update_by_d_mania 17.4.17
							//Ver2.06.07 基準運転時分取得元ダイヤインデクス機能追加に伴う変更
							int iKijunDiaIndex = m_pCDedRosenFileData->getCentDedRosen()->getKijunDiaIndex();
							//機能が有効かつ基準運転時分取得元ダイヤ以外かつ、列車の始発駅ではない
							if (m_bStandardOperationTimeFunction &&
								iEkiOrder > pCentDedRessya->getSihatsuEki() &&
								iEkiOrder <= pCentDedRessya->getSyuuchakuEki() &&
								m_pCDedRosenFileData->getCentDedRosen()->getCentDedDiaCont()->findCentDedDiaByName(
									m_pCentDedRessyaCont->getDia()->getName()) != iKijunDiaIndex)
							{
								pCDcDrawCell->setCdBrushProp(update02_02_02_StdOpeTimeFunc(
									true,
									iKijunDiaIndex,
									iEkiOrder,
									pCentDedRessya,
									muCdDedEki));
							}
						}
						//始発駅かつ路線外発着設定で、駅時刻なしor通過駅時刻表示なしなら、経由無しマークを表示
						else if (iEkiOrder == pCentDedRessya->getSihatsuEki() &&
							pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer &&
							m_bDisplayOuterTerminalShihatsu)
						{

							*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
							pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"
						}
						else
						{
							*pCDcDrawCell = createCDcdRessyabangou(
								idxRessyasyubetsu);
							pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_TSUUKA));	//" ﾚ"
						}
					}
					break ;
					case CentDedEkiJikoku::Ekiatsukai_Teisya :
					{
						//	停車駅の駅時刻が指定されている
						if ( !aCdDedJikoku.isNull() )
						{
							/**
								秒単位表示OFFの場合は、切り上げ・切り捨ての処理を行いますが、
								その補助のため、着時刻が切り上げで、発時刻が30秒以上切り上げまたは切り捨ての場合は、発時刻の取得を行います。
								この駅と次の駅の間が運行なしの場合は、運行なしを超えた先の駅から時刻を取得します。
							*/
							CdDedJikoku aHatsuJikoku;
							if (!getDisplaySecondEkiJikoku() &&
								m_iSecondRoundChaku == 2 &&
								m_iSecondRoundHatsu <= 1)
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
											m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()
											->isSameBrunchLoopGroup(iEkiOrder, iHatsuEkiOrder, pCentDedRessya->getRessyahoukou()))
										{
											aHatsuJikoku = pCentDedRessya->getCentDedEkiJikoku(iHatsuEkiOrder).getHatsujikoku();
										}
									}
								}
							}

							*pCDcDrawCell = createCDcdEkijikoku( 
								idxRessyasyubetsu ,
								CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya);
							tstring strText = getCdDedJikokuConv().encode(aCdDedJikoku, true, aHatsuJikoku);
							pCDcDrawCell->setText(strText ) ;
							//基準運転時分機能Update_by_d_mania 17.4.17
							//Ver2.06.07 基準運転時分取得元ダイヤインデクス機能追加に伴う変更
							int iKijunDiaIndex = m_pCDedRosenFileData->getCentDedRosen()->getKijunDiaIndex();
							//機能が有効かつ通過駅時刻表示が有効かつ
							//基準運転時分取得元ダイヤ以外かつ、列車の始発駅ではない
							if( m_bStandardOperationTimeFunction &&
								m_bDisplayTsuukaEkiJikoku &&
								iEkiOrder > pCentDedRessya->getSihatsuEki() &&
								iEkiOrder <= pCentDedRessya->getSyuuchakuEki() &&
								m_pCDedRosenFileData->getCentDedRosen()->getCentDedDiaCont()->findCentDedDiaByName(
									m_pCentDedRessyaCont->getDia()->getName()) != iKijunDiaIndex)
							{
								pCDcDrawCell->setCdBrushProp( update02_02_02_StdOpeTimeFunc(
									true ,
									iKijunDiaIndex ,
									iEkiOrder ,
									pCentDedRessya ,
									muCdDedEki ) ) ;
							}
							//Updateここまで
						}
							//始発駅かつ路線外発着設定で、駅時刻なしなら、経由無しマークを表示
						else if (iEkiOrder == pCentDedRessya->getSihatsuEki() &&
							pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer &&
							m_bDisplayOuterTerminalShihatsu)
						{

							*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
							pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"
						}
						//	停車駅の駅時刻が指定されていない
						else 
						{
							*pCDcDrawCell = createCDcdRessyabangou(
								idxRessyasyubetsu );

							//	[時刻表ビュー上の発時刻の表示列を算出
							CdYColSpec aCdYColSpec( 
								CdYColSpec::ColumnType_Ekijikoku_Hatsu , 
								iEkiOrder ) ;
							int iYColumnNumberHatsu = 
								m_CdYColSpecCont.ColumnNumberFromSpec( aCdYColSpec , false ) ;


							//	時刻表ビュー上発時刻の表示あり AND 
							//	始発駅の場合は "・・" 表示
							if ( iYColumnNumberHatsu >= 0 && 
								pCentDedRessya->getSihatsuEki() == iEkiOrder )
							{
								pCDcDrawCell->setText( (LPCTSTR)MfcUtil::LoadCString( 
									IDS_WORD_JIKOKUHYOU_UNKOUNASI_IPPAN ) ) ;
							}
							//	途中・終着駅の場合・着時刻のみ表示の場合は " ○ " 表示
							else	
							{
								pCDcDrawCell->setText( (LPCTSTR)MfcUtil::LoadCString( 
									IDS_WORD_JIKOKUHYOU_TEISYA ) ) ;
							}
						}
					}
					break ;
				}

				//セルの背景色を指定します。
				if(!m_bStandardOperationTimeFunction)
				{
					pCDcDrawCell->setCdBrushProp(getBackColor(
						iXColumnNumber,
						iEkiOrder,
						idxRessyasyubetsu));
				}

				//  1．	この駅の『駅時刻形式』が『発着』
				//  2．	この列車の、この駅での駅扱が『停車』か『通過』のいずれか
				//  3．	この列車の、この駅の着時刻が空
				//  4．	この列車の、この駅の前の駅での駅扱が『運行なし』
				//	5.	この列車の始発駅よりも終点方(getSihatsuEkiは「最初の運行なしではない」駅を返すので、-1チェックは不要
				//
				//  この場合は、時刻表ビュー上では、この列車のこの駅での着時刻は " || " 表示とします。
				{
					CentDedEkiJikoku aCentDedEkijikokuPrev ;
					if ( 0 <= iEkiOrder - 1 
						&& iEkiOrder - 1 < muCdDedEki->size() ) 
					{
						aCentDedEkijikokuPrev = 
							pCentDedRessya->getCentDedEkiJikoku(
								iEkiOrder - 1 ) ;
					}
					//aCentDedEkijikokuPrev = 前の駅の駅時刻

					if ( aCdDedEki.isHatsuChakuHyouji() && 
						( aCentDedEkiJikoku.getEkiatsukai() == 
								CentDedEkiJikoku::Ekiatsukai_Teisya || 
							aCentDedEkiJikoku.getEkiatsukai() == 
								CentDedEkiJikoku::Ekiatsukai_Tsuuka ) && 
						aCentDedEkiJikoku.getChakujikoku().isNull() && 
						aCentDedEkijikokuPrev.getEkiatsukai() == 
								CentDedEkiJikoku::Ekiatsukai_None &&
						pCentDedRessya->getSihatsuEki() < iEkiOrder)
					{
						pCDcDrawCell->setText( (LPCTSTR)MfcUtil::LoadCString( 
							IDS_WORD_JIKOKUHYOU_KEIYUNASI ) );	//"||"
					}
				}
			}
		}
	}
}

void CCellBuilder::update02_02_02_19_setRessya_BeforeOperationBefore(
	int iXColumnNumber,
	int iYColumnNumber,
	const CentDedRessya* pCentDedRessya,
	int iEkiOrder,
	CWndJikokuhyou* pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	const CentDedRosen* pCentDedRosen =
		m_pCDedRosenFileData->getCentDedRosen();
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		pCentDedRosen->getCentDedEkiCont()->getMuPtr(
			pCentDedRessya->getRessyahoukou());
	// --------------------------------
	//CDcdTargetGetDC	aCDcdTarget(NULL);
	// --------------------------------
	{
		CDcdGridCell* pCDcdGridCell1 = pCDcdGrid->getCell(
			iXColumnNumber, iYColumnNumber);
		CDcdGridCell* pCDcdGridCell2 = pCDcdGrid->getCell(
			iXColumnNumber, iYColumnNumber + 1);
		CDcdGridCell* pCDcdGridCell3 = NULL;
		CDcdGridCell* pCDcdGridCell4 = NULL;
		if (m_iEnableOperation > 1)
		{
			pCDcdGridCell3 = pCDcdGrid->getCell(
				iXColumnNumber, iYColumnNumber + 2);
			if (m_bDisplayInOutLinkCode)
			{
				pCDcdGridCell4 = pCDcdGrid->getCell(
					iXColumnNumber, iYColumnNumber + 3);
			}
		}
		// --------------------------------
		if (pCDcdGridCell1 != 0 && pCDcdGridCell2 != 0)
		{
			typedef CDcdTextbox CDcDrawCell;
			Ou<CDcDrawCell> pCDcDrawCell1;
			Ou<CDcDrawCell> pCDcDrawCell2;
			Ou<CDcDrawCell> pCDcDrawCell3;
			Ou<CDcDrawCell> pCDcDrawCell4;
			// --------------------------------
			//　(2.2.*.1)　セルの結合セルを設定
			pCDcdGridCell1->setAttachCellCount(1, 1);
			pCDcdGridCell2->setAttachCellCount(1, 1);
			if (pCDcdGridCell3 != 0)
			{
				pCDcdGridCell3->setAttachCellCount(1, 1);
			}
			if (pCDcdGridCell4 != 0)
			{
				pCDcdGridCell4->setAttachCellCount(1, 1);
			}

			//　(2.2.*.2)　セル の	DcDrawオブジェクトの型を設定
			//	( CDcdTextbox とする)。
			{
				pCDcDrawCell1 = dynamic_castOu<CDcDrawCell>(
					pCDcdGridCell1->getIfDcDraw());
				pCDcDrawCell2 = dynamic_castOu<CDcDrawCell>(
					pCDcdGridCell2->getIfDcDraw());
				if (pCDcDrawCell1 == NULL)
				{
					pCDcDrawCell1 = OuNew<CDcDrawCell>(new CDcDrawCell);
					pCDcdGridCell1->setIfDcDraw(pCDcDrawCell2);
				}
				if (pCDcDrawCell2 == NULL)
				{
					pCDcDrawCell2 = OuNew<CDcDrawCell>(new CDcDrawCell);
					pCDcdGridCell2->setIfDcDraw(pCDcDrawCell2);
				}
				if (pCDcdGridCell3 != 0)
				{
					pCDcDrawCell3 = dynamic_castOu<CDcDrawCell>(
						pCDcdGridCell3->getIfDcDraw());
					if (pCDcDrawCell3 == NULL)
					{
						pCDcDrawCell3 = OuNew<CDcDrawCell>(new CDcDrawCell);
						pCDcdGridCell3->setIfDcDraw(pCDcDrawCell3);
					}
				}
				if (pCDcdGridCell4 != 0)
				{
					pCDcDrawCell4 = dynamic_castOu<CDcDrawCell>(
						pCDcdGridCell4->getIfDcDraw());
					if (pCDcDrawCell4 == NULL)
					{
						pCDcDrawCell4 = OuNew<CDcDrawCell>(new CDcDrawCell);
						pCDcdGridCell4->setIfDcDraw(pCDcDrawCell4);
					}
				}
			}
			//　(2.2.*.3)　セルの DcDrawオブジェクトに、属性を設定。
			{
				CentDedEkiJikoku	aCentDedEkiJikoku =
					pCentDedRessya->getCentDedEkiJikoku(iEkiOrder);
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

				pCDcDrawCell1->setCdDrawTextProp(getCdDrawTextPropOperation());
				pCDcDrawCell2->setCdDrawTextProp(getCdDrawTextPropOperation());
				if (pCDcDrawCell3 != NULL)
				{
					pCDcDrawCell3->setCdDrawTextProp(getCdDrawTextPropOperation());
				}
				if (pCDcDrawCell4 != NULL)
				{
					pCDcDrawCell4->setCdDrawTextProp(getCdDrawTextPropOperation());
				}
				tstring strText1 = _T("");
				tstring strText2 = _T("");
				tstring strText3 = _T("");
				tstring strText4 = _T("");

				if (pFirstOperation != NULL)
				{
					/**
						開始作業の秒単位処理は、着時刻設定に基づき行います。
					*/
					if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Out)
					{
						strText1 = tstringOf(
							(LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_OperationOut));
						//Ver2.05 運用機能が通常モードかつ入出区連携コードが入力されている場合は、"出区"の後に入出区連携コードを表示します。
						//	→単独欄表示に変更
						//if (m_iEnableOperation > 1 && !pFirstOperation->getInOutLinkCode().empty())
						//{
						//	strText1 += _T("/");
						//	strText1 += pFirstOperation->getInOutLinkCode();
						//}

						CdDedJikoku aCdDedJikoku
							= pFirstOperation->getOutJikoku();
						strText2 = getCdDedJikokuConv().encode(aCdDedJikoku, true);

						strText3 = joinc(';', pFirstOperation->getOperationNumberOriginal());

						strText4 = pFirstOperation->getInOutLinkCode();
					}
					else if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
					{
						CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);
						//Ver2.05 運用機能が通常モードかつ入出区連携コードが入力されている場合は、路線外始発駅名欄を、ダイヤ略称+入出区連携コードに変更します。
						//	→単独欄表示に変更
						//if (m_iEnableOperation > 1 && !pFirstOperation->getInOutLinkCode().empty())
						//{
						//	strText1 = aCdDedEki.getOuterTerminalDiaRyaku(pFirstOperation->getOuterShihatsuekiIndex(), true);
						//	strText1 += _T("/");
						//	strText1 += pFirstOperation->getInOutLinkCode();
						//}
						//else
						//{
						strText1 = aCdDedEki.getOuterTerminalJikokuRyaku(pFirstOperation->getOuterShihatsuekiIndex(), true);
						//}

						CdDedJikoku aCdDedJikoku
							= pFirstOperation->getChakuJikoku();
						if (aCdDedJikoku.isNull())
						{
							aCdDedJikoku = ConnectJikoku;
							//pCDcDrawCell2->setCdDrawTextProp(
							//	getCdDrawTextPropTsuuka());
						}
						strText2 = getCdDedJikokuConv().encode(aCdDedJikoku, true);
						strText2 += tstringOf(
							(LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_Chaku));
						//strText2 += _T("着");

						strText3 = joinc(';', pFirstOperation->getOperationNumberOriginal());

						strText4 = pFirstOperation->getInOutLinkCode();
					}
					//2.00.05 仮運用番号に対応
					else if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Junction)
					{
						//視認性向上のため、"前接続"と表示させる
						strText1 = _T("前接続");

						CdDedJikoku aCdDedJikoku
							= pFirstOperation->getOriginJikoku();
						strText2 = getCdDedJikokuConv().encode(aCdDedJikoku, true);

						strText3 = joinc(';', pFirstOperation->getOperationNumberTemp());
						if (pCDcDrawCell3 != NULL)
						{
							pCDcDrawCell3->setCdDrawTextProp(
								getCdDrawTextPropTsuuka());
						}
					}
				}
				else if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_None)
				{
					if (iEkiOrder < pCentDedRessya->getValidSihatsuEki() && pCentDedRessya->getValidSihatsuEki() != -1)
					{
						if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer
							&& m_bDisplayOuterTerminalShihatsu)
						{
							int idxRessyasyubetsu
								= pCentDedRessya->getRessyasyubetsuIndex();
							*pCDcDrawCell1 = createCDcdRessyabangou(idxRessyasyubetsu);
							*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);
							if (pCDcDrawCell3 != NULL)
							{
								*pCDcDrawCell3 = createCDcdRessyabangou(idxRessyasyubetsu);
							}
							if (pCDcDrawCell4 != NULL)
							{
								*pCDcDrawCell4 = createCDcdRessyabangou(idxRessyasyubetsu);
							}
							strText1 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);
							strText2 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);
							strText3 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);
							strText4 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);
						}
					}
					else if (iEkiOrder > pCentDedRessya->getValidSyuuchakuEki() && pCentDedRessya->getValidSyuuchakuEki() != -1)
					{
						if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer
							&& m_bDisplayOuterTerminalShuchaku)
						{
							int idxRessyasyubetsu
								= pCentDedRessya->getRessyasyubetsuIndex();
							*pCDcDrawCell1 = createCDcdRessyabangou(idxRessyasyubetsu);
							*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);
							if (pCDcDrawCell3 != NULL)
							{
								*pCDcDrawCell3 = createCDcdRessyabangou(idxRessyasyubetsu);
							}
							if (pCDcDrawCell4 != NULL)
							{
								*pCDcDrawCell4 = createCDcdRessyabangou(idxRessyasyubetsu);
							}
							strText1 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);
							strText2 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);
							strText3 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);
							strText4 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);
						}
					}
					else if (iEkiOrder > pCentDedRessya->getSihatsuEki() && pCentDedRessya->getSihatsuEki() != -1 &&
						iEkiOrder < pCentDedRessya->getSyuuchakuEki())
					{
						int idxRessyasyubetsu
							= pCentDedRessya->getRessyasyubetsuIndex();
						*pCDcDrawCell1 = createCDcdRessyabangou(idxRessyasyubetsu);
						*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);
						if (pCDcDrawCell3 != NULL)
						{
							*pCDcDrawCell3 = createCDcdRessyabangou(idxRessyasyubetsu);
						}
						if (pCDcDrawCell4 != NULL)
						{
							*pCDcDrawCell4 = createCDcdRessyabangou(idxRessyasyubetsu);
						}
						strText1 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
						strText2 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
						strText3 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
						strText4 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
					}

				}

				//  1．	この駅の『駅時刻形式』が『発着』
				//  2．	この列車の、この駅での駅扱が『停車』か『通過』のいずれか
				//  3．	この列車の、この駅の着時刻が空
				//  4．	この列車の、この駅の前の駅での駅扱が『運行なし』
				//	5.	この列車の始発駅よりも終点方(getSihatsuEkiは「最初の運行なしではない」駅を返すので、-1チェックは不要
				//
				//  この場合は、時刻表ビュー上では、この列車のこの駅での前作業欄は " || " 表示とします。
				{
					CentDedEkiJikoku aCentDedEkijikokuPrev;
					if (0 <= iEkiOrder - 1
						&& iEkiOrder - 1 < muCdDedEki->size())
					{
						aCentDedEkijikokuPrev =
							pCentDedRessya->getCentDedEkiJikoku(
								iEkiOrder - 1);
					}
					//aCentDedEkijikokuPrev = 前の駅の駅時刻

					//CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);
					if (/*aCdDedEki.isHatsuChakuHyouji() &&*/
						(aCentDedEkiJikoku.getEkiatsukai() ==
							CentDedEkiJikoku::Ekiatsukai_Teisya ||
							aCentDedEkiJikoku.getEkiatsukai() ==
							CentDedEkiJikoku::Ekiatsukai_Tsuuka) &&
						aCentDedEkiJikoku.getChakujikoku().isNull() &&
						aCentDedEkijikokuPrev.getEkiatsukai() ==
						CentDedEkiJikoku::Ekiatsukai_None &&
						pCentDedRessya->getSihatsuEki() < iEkiOrder)
					{
						int idxRessyasyubetsu
							= pCentDedRessya->getRessyasyubetsuIndex();
						*pCDcDrawCell1 = createCDcdRessyabangou(idxRessyasyubetsu);
						*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);
						if (pCDcDrawCell3 != NULL)
						{
							*pCDcDrawCell3 = createCDcdRessyabangou(idxRessyasyubetsu);
						}
						if (pCDcDrawCell4 != NULL)
						{
							*pCDcDrawCell4 = createCDcdRessyabangou(idxRessyasyubetsu);
						}
						strText1 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
						strText2 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
						strText3 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
						strText4 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
					}
				}

				pCDcDrawCell1->setText(strText1);
				pCDcDrawCell2->setText(strText2);
				if (pCDcDrawCell3 != NULL)
				{
					pCDcDrawCell3->setText(strText3);
				}
				if (pCDcDrawCell4 != NULL)
				{
					pCDcDrawCell4->setText(strText4);
				}

			}

			//セルの背景色を指定します。
			{
				pCDcDrawCell1->setCdBrushProp(CdColorProp(255, 255, 255));
				pCDcDrawCell2->setCdBrushProp(CdColorProp(255, 255, 255));
				if (pCDcDrawCell3 != NULL)
				{
					pCDcDrawCell3->setCdBrushProp(CdColorProp(255, 255, 255));
				}
				if (pCDcDrawCell4 != NULL)
				{
					pCDcDrawCell4->setCdBrushProp(CdColorProp(255, 255, 255));
				}
			}
		}
	}
}


void CCellBuilder::update02_02_02_17_setRessya_BeforeOperation(
	int iXColumnNumber,
	int iYColumnNumber,
	const CentDedRessya * pCentDedRessya, 
	int iEkiOrder, 
	CWndJikokuhyou * pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	const CentDedRosen* pCentDedRosen =
		m_pCDedRosenFileData->getCentDedRosen();
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		pCentDedRosen->getCentDedEkiCont()->getMuPtr(
			pCentDedRessya->getRessyahoukou());
	// --------------------------------
	//CDcdTargetGetDC	aCDcdTarget(NULL);
	// --------------------------------

	CentDedEkiCont::CdDedEki aEki = muCdDedEki->get(iEkiOrder);

	for(int idxb=0;idxb< aEki.getJikokuhyouBeforeOperation();idxb++)
	{
		CDcdGridCell* pCDcdGridCell1 = pCDcdGrid->getCell(
			iXColumnNumber, iYColumnNumber + (idxb * 2));
		CDcdGridCell* pCDcdGridCell2 = pCDcdGrid->getCell(
			iXColumnNumber, iYColumnNumber + (idxb * 2) + 1);
		// --------------------------------
		if (pCDcdGridCell1 != 0 && pCDcdGridCell2 != 0)
		{
			typedef CDcdTextbox CDcDrawCell;
			Ou<CDcDrawCell> pCDcDrawCell1;
			Ou<CDcDrawCell> pCDcDrawCell2;
			// --------------------------------
			//　(2.2.*.1)　セルの結合セルを設定
			pCDcdGridCell1->setAttachCellCount(1, 1);
			pCDcdGridCell2->setAttachCellCount(1, 1);

			//　(2.2.*.2)　セル の	DcDrawオブジェクトの型を設定
			//	( CDcdTextbox とする)。
			{
				pCDcDrawCell1 = dynamic_castOu<CDcDrawCell>(
					pCDcdGridCell1->getIfDcDraw());
				pCDcDrawCell2 = dynamic_castOu<CDcDrawCell>(
					pCDcdGridCell2->getIfDcDraw());
				if (pCDcDrawCell1 == NULL)
				{
					pCDcDrawCell1 = OuNew<CDcDrawCell>(new CDcDrawCell);
					pCDcdGridCell1->setIfDcDraw(pCDcDrawCell2);
				}
				if (pCDcDrawCell2 == NULL)
				{
					pCDcDrawCell2 = OuNew<CDcDrawCell>(new CDcDrawCell);
					pCDcdGridCell2->setIfDcDraw(pCDcDrawCell2);
				}
			}
			//　(2.2.*.3)　セルの DcDrawオブジェクトに、属性を設定。
			{
				CentDedEkiJikoku	aCentDedEkiJikoku =
					pCentDedRessya->getCentDedEkiJikoku(iEkiOrder);
				const CentDedBeforeOperationCont* pBeforeOperationCont = aCentDedEkiJikoku.getCentDedBeforeOperationCont();
				/*int idxRessyasyubetsu
					= pCentDedRessya->getRessyasyubetsuIndex();
				*pCDcDrawCell1 = createCDcdRessyabangou(idxRessyasyubetsu);
				*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);*/
				pCDcDrawCell1->setCdDrawTextProp(getCdDrawTextPropOperation());
				pCDcDrawCell2->setCdDrawTextProp(getCdDrawTextPropOperation());
				tstring strText1 = _T("");
				tstring strText2 = _T("");

				if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_None)
				{
					if (iEkiOrder < pCentDedRessya->getValidSihatsuEki() && pCentDedRessya->getValidSihatsuEki() != -1)
					{
						if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer
							&& m_bDisplayOuterTerminalShihatsu)
						{
							int idxRessyasyubetsu
								= pCentDedRessya->getRessyasyubetsuIndex();
							*pCDcDrawCell1 = createCDcdRessyabangou(idxRessyasyubetsu);
							*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);
							strText1 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);
							strText2 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);
						}
					}
					else if (iEkiOrder > pCentDedRessya->getValidSyuuchakuEki() && pCentDedRessya->getValidSyuuchakuEki() != -1)
					{
						if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer
							&& m_bDisplayOuterTerminalShuchaku)
						{
							int idxRessyasyubetsu
								= pCentDedRessya->getRessyasyubetsuIndex();
							*pCDcDrawCell1 = createCDcdRessyabangou(idxRessyasyubetsu);
							*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);
							strText1 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);
							strText2 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);
						}
					}
					else if (iEkiOrder > pCentDedRessya->getSihatsuEki() && pCentDedRessya->getSihatsuEki() != -1 &&
						iEkiOrder < pCentDedRessya->getSyuuchakuEki())
					{
						int idxRessyasyubetsu
							= pCentDedRessya->getRessyasyubetsuIndex();
						*pCDcDrawCell1 = createCDcdRessyabangou(idxRessyasyubetsu);
						*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);
						strText1 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
						strText2 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
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
				else if(pBeforeOperationCont->getMuPtr()->get(0)->isFirstOperation())
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
					int iTargetPos = max(pBeforeOperationCont->size() - aEki.getJikokuhyouBeforeOperation(), 1);
					iTargetPos += idxb;

					if (iTargetPos < pBeforeOperationCont->size())
					{
						const CentDedBeforeOperation* pBeforeOperation
							= pBeforeOperationCont->getMuPtr()->get(iTargetPos);
						if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
						{
							//strText1 = _T("換 ");
							strText1 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_SHUNT_RYAKU);
							strText1 += _T(" ");
							CentDedEkiTrack2Cont aCentDedEkiTrack2Cont = aEki.getCentDedEkiTrack2Cont();
							strText1+= aCentDedEkiTrack2Cont.get(pBeforeOperation->getShuntTrackIndex())
								.getTrackRyakusyou(pCentDedRessya->getRessyahoukou());

							strText2 = getCdDedJikokuConv().encode(pBeforeOperation->getOperationHatsuJikoku(), true);
						}
						else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
						{
							//strText1 = _T("増 ");
							strText1 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_CONNECT_RYAKU);
							strText1 += _T(" ");
							if (pBeforeOperation->getIsConnectToFront())
							{
								//strText1 += _T("前方");
								strText1 += (LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_CONNECT_FRONT);
							}
							else
							{
								//strText1 += _T("後方");
								strText1 += (LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_CONNECT_BACK);
							}

							strText2 = getCdDedJikokuConv().encode(pBeforeOperation->getConnectJikoku(), true);
						}
						else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
						{
							//strText1 = _T("解 ");
							strText1 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_RELEASE_RYAKU);
							strText1 += _T(" ");
							if (pBeforeOperation->getReleasePos() == 0)//Back
							{
								//strText1 += _T("後");
								strText1 += (LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_RELEASE_BACK);
								strText1 += to_tstring(pBeforeOperation->getReleaseIndexCount());
							}
							else if (pBeforeOperation->getReleasePos() == 1)//Front
							{
								//strText1 += _T("前");
								strText1 += (LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_RELEASE_FRONT);
								strText1 += to_tstring(pBeforeOperation->getReleaseIndexCount());
							}
							else if (pBeforeOperation->getReleasePos() == 2)//FrontLeave
							{
								//strText1 += _T("前");
								strText1 += (LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_RELEASE_FRONT);
								strText1 += to_tstring(pBeforeOperation->getReleaseIndexCount());
								//strText1 += _T("以外");
								strText1 += (LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_RELEASE_LEAVE);
							}
							strText2 = getCdDedJikokuConv().encode(pBeforeOperation->getReleaseJikoku(), true);
						}
						//Ver2.00.05 運用番号変更対応
						//Ver2.06.05 運用番号順反転対応
						else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_NumberChange)
						{
							//strText1 = _T("運番変更");
							if (pBeforeOperation->getOperationNumberReverse())
							{
								strText1 = (LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_NUMBERREVERSE);
							}
							else
							{
								strText1 = (LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_NUMBERCHANGE);
								strText2 = joinc(';', pBeforeOperation->getOperationNumber());
							}
						}
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
					int iTargetPos = max(pBeforeOperationCont->size() - aEki.getJikokuhyouBeforeOperation(), 0);
					iTargetPos += idxb;

					if (iTargetPos < pBeforeOperationCont->size())
					{
						const CentDedBeforeOperation* pBeforeOperation
							= pBeforeOperationCont->getMuPtr()->get(iTargetPos);
						if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
						{
							//strText1 = _T("換 ");
							strText1 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_SHUNT_RYAKU);
							strText1 += _T(" ");
							CentDedEkiTrack2Cont aCentDedEkiTrack2Cont = aEki.getCentDedEkiTrack2Cont();
							strText1 += aCentDedEkiTrack2Cont.get(pBeforeOperation->getShuntTrackIndex())
								.getTrackRyakusyou(pCentDedRessya->getRessyahoukou());

							strText2 = getCdDedJikokuConv().encode(pBeforeOperation->getOperationHatsuJikoku(), true);
						}
						else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
						{
							//strText1 = _T("増 ");
							strText1 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_CONNECT_RYAKU);
							strText1 += _T(" ");
							if (pBeforeOperation->getIsConnectToFront())
							{
								//strText1 += _T("前方");
								strText1 += (LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_CONNECT_FRONT);
							}
							else
							{
								//strText1 += _T("後方");
								strText1 += (LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_CONNECT_BACK);
							}

							strText2 = getCdDedJikokuConv().encode(pBeforeOperation->getConnectJikoku(), true);
						}
						else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
						{
							//strText1 = _T("解 ");
							strText1 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_RELEASE_RYAKU);
							strText1 += _T(" ");
							if (pBeforeOperation->getReleasePos() == 0)//Back
							{
								//strText1 += _T("後");
								strText1 += (LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_RELEASE_BACK);
								strText1 += to_tstring(pBeforeOperation->getReleaseIndexCount());
							}
							else if (pBeforeOperation->getReleasePos() == 1)//Front
							{
								//strText1 += _T("前");
								strText1 += (LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_RELEASE_FRONT);
								strText1 += to_tstring(pBeforeOperation->getReleaseIndexCount());
							}
							else if (pBeforeOperation->getReleasePos() == 2)//FrontLeave
							{
								//strText1 += _T("前");
								strText1 += (LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_RELEASE_FRONT);
								strText1 += to_tstring(pBeforeOperation->getReleaseIndexCount());
								//strText1 += _T("以外");
								strText1 += (LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_RELEASE_LEAVE);
							}
							strText2 = getCdDedJikokuConv().encode(pBeforeOperation->getReleaseJikoku(), true);
						}
						//Ver2.00.05 運用番号変更対応
						else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_NumberChange)
						{
							//strText1 = _T("運番変更");
							if (pBeforeOperation->getOperationNumberReverse())
							{
								strText1 = (LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_NUMBERREVERSE);
							}
							else
							{
								strText1 = (LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_NUMBERCHANGE);
								strText2 = joinc(';', pBeforeOperation->getOperationNumber());
							}
						}
					}
				}

				//  1．	この駅の『駅時刻形式』が『発着』
				//  2．	この列車の、この駅での駅扱が『停車』か『通過』のいずれか
				//  3．	この列車の、この駅の着時刻が空
				//  4．	この列車の、この駅の前の駅での駅扱が『運行なし』
				//	5.	この列車の始発駅よりも終点方(getSihatsuEkiは「最初の運行なしではない」駅を返すので、-1チェックは不要
				//
				//  この場合は、時刻表ビュー上では、この列車のこの駅での前作業欄は " || " 表示とします。
				{
					CentDedEkiJikoku aCentDedEkijikokuPrev;
					if (0 <= iEkiOrder - 1
						&& iEkiOrder - 1 < muCdDedEki->size())
					{
						aCentDedEkijikokuPrev =
							pCentDedRessya->getCentDedEkiJikoku(
								iEkiOrder - 1);
					}
					//aCentDedEkijikokuPrev = 前の駅の駅時刻

					//CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);
					if (/*aCdDedEki.isHatsuChakuHyouji() &&*/
						(aCentDedEkiJikoku.getEkiatsukai() ==
							CentDedEkiJikoku::Ekiatsukai_Teisya ||
							aCentDedEkiJikoku.getEkiatsukai() ==
							CentDedEkiJikoku::Ekiatsukai_Tsuuka) &&
						aCentDedEkiJikoku.getChakujikoku().isNull() &&
						aCentDedEkijikokuPrev.getEkiatsukai() ==
						CentDedEkiJikoku::Ekiatsukai_None &&
						pCentDedRessya->getSihatsuEki() < iEkiOrder)
					{
						int idxRessyasyubetsu
							= pCentDedRessya->getRessyasyubetsuIndex();
						*pCDcDrawCell1 = createCDcdRessyabangou(idxRessyasyubetsu);
						*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);
						strText1 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
						strText2 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
						//pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
						//	IDS_WORD_JIKOKUHYOU_KEIYUNASI));	//"||"
					}
				}
				pCDcDrawCell1->setText(strText1);
				pCDcDrawCell2->setText(strText2);

			}

			//セルの背景色を指定します。
			{
				pCDcDrawCell1->setCdBrushProp(CdColorProp(255, 255, 255));
				pCDcDrawCell2->setCdBrushProp(CdColorProp(255, 255, 255));
			}
		}
	}
}

void CCellBuilder::update02_02_02_20_setRessya_BeforeOperationAfter(
	int iXColumnNumber,
	int iYColumnNumber,
	const CentDedRessya* pCentDedRessya,
	int iEkiOrder,
	CWndJikokuhyou* pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	const CentDedRosen* pCentDedRosen =
		m_pCDedRosenFileData->getCentDedRosen();
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		pCentDedRosen->getCentDedEkiCont()->getMuPtr(
			pCentDedRessya->getRessyahoukou());
	// --------------------------------
	//CDcdTargetGetDC	aCDcdTarget(NULL);
	// --------------------------------
	{
		CDcdGridCell* pCDcdGridCell1 = pCDcdGrid->getCell(
			iXColumnNumber, iYColumnNumber);
		CDcdGridCell* pCDcdGridCell2 = pCDcdGrid->getCell(
			iXColumnNumber, iYColumnNumber + 1);
		CDcdGridCell* pCDcdGridCell3 = NULL;
		if (m_iEnableOperation > 1 && m_bDisplayInOutLinkCode)
		{
			pCDcdGridCell3 = pCDcdGrid->getCell(
				iXColumnNumber, iYColumnNumber + 2);
		}
		// --------------------------------
		if (pCDcdGridCell1 != 0 && pCDcdGridCell2 != 0)
		{
			typedef CDcdTextbox CDcDrawCell;
			Ou<CDcDrawCell> pCDcDrawCell1;
			Ou<CDcDrawCell> pCDcDrawCell2;
			Ou<CDcDrawCell> pCDcDrawCell3;
			// --------------------------------
			//　(2.2.*.1)　セルの結合セルを設定
			pCDcdGridCell1->setAttachCellCount(1, 1);
			pCDcdGridCell2->setAttachCellCount(1, 1);
			if (pCDcdGridCell3 != 0)
			{
				pCDcdGridCell3->setAttachCellCount(1, 1);
			}

			//　(2.2.*.2)　セル の	DcDrawオブジェクトの型を設定
			//	( CDcdTextbox とする)。
			{
				pCDcDrawCell1 = dynamic_castOu<CDcDrawCell>(
					pCDcdGridCell1->getIfDcDraw());
				pCDcDrawCell2 = dynamic_castOu<CDcDrawCell>(
					pCDcdGridCell2->getIfDcDraw());
				if (pCDcDrawCell1 == NULL)
				{
					pCDcDrawCell1 = OuNew<CDcDrawCell>(new CDcDrawCell);
					pCDcdGridCell1->setIfDcDraw(pCDcDrawCell2);
				}
				if (pCDcDrawCell2 == NULL)
				{
					pCDcDrawCell2 = OuNew<CDcDrawCell>(new CDcDrawCell);
					pCDcdGridCell2->setIfDcDraw(pCDcDrawCell2);
				}
				if (pCDcdGridCell3 != 0)
				{
					pCDcDrawCell3 = dynamic_castOu<CDcDrawCell>(
						pCDcdGridCell3->getIfDcDraw());
					if (pCDcDrawCell3 == NULL)
					{
						pCDcDrawCell3 = OuNew<CDcDrawCell>(new CDcDrawCell);
						pCDcdGridCell3->setIfDcDraw(pCDcDrawCell3);
					}
				}
			}
			//　(2.2.*.3)　セルの DcDrawオブジェクトに、属性を設定。
			{
				CentDedEkiJikoku	aCentDedEkiJikoku =
					pCentDedRessya->getCentDedEkiJikoku(iEkiOrder);
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

				pCDcDrawCell1->setCdDrawTextProp(getCdDrawTextPropOperation());
				pCDcDrawCell2->setCdDrawTextProp(getCdDrawTextPropOperation());
				if (pCDcDrawCell3 != NULL)
				{
					pCDcDrawCell3->setCdDrawTextProp(getCdDrawTextPropOperation());
				}
				tstring strText1 = _T("");
				tstring strText2 = _T("");
				tstring strText3 = _T("");

				if (pLastOperation != NULL)
				{
					/**
						終了作業の秒単位処理は、発時刻設定に基づき行います。
					*/

					if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_In)
					{
						strText1 = tstringOf(
							(LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_OperationIn));
						//Ver2.05 運用機能が通常モードかつ入出区連携コードが入力されている場合は、"入区"の後に入出区連携コードを表示します。
						//	→単独欄表示に変更
						//if (m_iEnableOperation > 1 && !pLastOperation->getInOutLinkCode().empty())
						//{
						//	strText1 += _T("/");
						//	strText1 += pLastOperation->getInOutLinkCode();
						//}

						CdDedJikoku aCdDedJikoku
							= pLastOperation->getInJikoku();
						strText2 = getCdDedJikokuConv().encode(aCdDedJikoku, false);

						strText3 = pLastOperation->getInOutLinkCode();
					}
					else if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
					{
						CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);
						//Ver2.05 運用機能が通常モードかつ入出区連携コードが入力されている場合は、路線外終着駅名欄を、ダイヤ略称+入出区連携コードに変更します。
						//	→単独欄表示に変更
						//if (m_iEnableOperation > 1 && !pLastOperation->getInOutLinkCode().empty())
						//{
						//	strText1 = aCdDedEki.getOuterTerminalDiaRyaku(pLastOperation->getOuterShuchakuekiIndex(), true);
						//	strText1 += _T("/");
						//	strText1 += pLastOperation->getInOutLinkCode();
						//}
						//else
						//{
							strText1 = aCdDedEki.getOuterTerminalJikokuRyaku(pLastOperation->getOuterShuchakuekiIndex(), true);
						//}

						CdDedJikoku aCdDedJikoku
							= pLastOperation->getHatsuJikoku();
						if (aCdDedJikoku.isNull())
						{
							aCdDedJikoku = ReleaseJikoku;
							//pCDcDrawCell2->setCdDrawTextProp(
							//	getCdDrawTextPropTsuuka());
						}
						strText2 = getCdDedJikokuConv().encode(aCdDedJikoku, false);
						strText2 += tstringOf(
							(LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_Hatsu));
						//strText2 += _T("発");

						strText3 = pLastOperation->getInOutLinkCode();
					}
					else if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Junction)
					{
						//Ver2.05 1行目には、次列車接続タイプを表示する。視認性向上のため、別列車の場合は"次接続"と表示させる
						if (pLastOperation->getNextJunctionType() == 1)
						{
							strText1 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_SYUBETSUCHANGE);
						}
						else if (pLastOperation->getNextJunctionType() == 2)
						{
							strText1 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_PROPERTYCHANGE);
						}
						else if (pLastOperation->getNextJunctionType() == 3)
						{
							strText1 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_PROPERTYSAME);
						}
						else
						{
							strText1 = _T("次接続");
						}

						CdDedJikoku aCdDedJikoku
							= pLastOperation->getTerminalJikoku();
						strText2 = getCdDedJikokuConv().encode(aCdDedJikoku, false);
					}
				}
				else if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_None)
				{
					if (iEkiOrder < pCentDedRessya->getValidSihatsuEki() && pCentDedRessya->getValidSihatsuEki() != -1)
					{
						if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer
							&& m_bDisplayOuterTerminalShihatsu)
						{
							int idxRessyasyubetsu
								= pCentDedRessya->getRessyasyubetsuIndex();
							*pCDcDrawCell1 = createCDcdRessyabangou(idxRessyasyubetsu);
							*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);
							if (pCDcDrawCell3 != NULL)
							{
								*pCDcDrawCell3 = createCDcdRessyabangou(idxRessyasyubetsu);
							}
							strText1 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);
							strText2 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);
							strText3 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);
						}
					}
					else if (iEkiOrder > pCentDedRessya->getValidSyuuchakuEki() && pCentDedRessya->getValidSyuuchakuEki() != -1)
					{
						if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer
							&& m_bDisplayOuterTerminalShuchaku)
						{
							int idxRessyasyubetsu
								= pCentDedRessya->getRessyasyubetsuIndex();
							*pCDcDrawCell1 = createCDcdRessyabangou(idxRessyasyubetsu);
							*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);
							if (pCDcDrawCell3 != NULL)
							{
								*pCDcDrawCell3 = createCDcdRessyabangou(idxRessyasyubetsu);
							}
							strText1 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);
							strText2 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);
							strText3 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);
						}
					}
					else if (iEkiOrder > pCentDedRessya->getSihatsuEki() && pCentDedRessya->getSihatsuEki() != -1 &&
						iEkiOrder < pCentDedRessya->getSyuuchakuEki())
					{
						int idxRessyasyubetsu
							= pCentDedRessya->getRessyasyubetsuIndex();
						*pCDcDrawCell1 = createCDcdRessyabangou(idxRessyasyubetsu);
						*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);
						if (pCDcDrawCell3 != NULL)
						{
							*pCDcDrawCell3 = createCDcdRessyabangou(idxRessyasyubetsu);
						}
						strText1 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
						strText2 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
						strText3 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
					}

				}

				//  1．	この駅の『駅時刻形式』が『発着』
				//  2．	この列車の、この駅での駅扱が『停車』か『通過』のいずれか
				//  3．	この列車の、この駅の着時刻が空
				//  4．	この列車の、この駅の前の駅での駅扱が『運行なし』
				//	5.	この列車の始発駅よりも終点方(getSihatsuEkiは「最初の運行なしではない」駅を返すので、-1チェックは不要
				//
				//  この場合は、時刻表ビュー上では、この列車のこの駅での前作業欄は " || " 表示とします。
				{
					CentDedEkiJikoku aCentDedEkijikokuPrev;
					if (0 <= iEkiOrder - 1
						&& iEkiOrder - 1 < muCdDedEki->size())
					{
						aCentDedEkijikokuPrev =
							pCentDedRessya->getCentDedEkiJikoku(
								iEkiOrder - 1);
					}
					//aCentDedEkijikokuPrev = 前の駅の駅時刻

					//CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);
					if (/*aCdDedEki.isHatsuChakuHyouji() &&*/
						(aCentDedEkiJikoku.getEkiatsukai() ==
							CentDedEkiJikoku::Ekiatsukai_Teisya ||
							aCentDedEkiJikoku.getEkiatsukai() ==
							CentDedEkiJikoku::Ekiatsukai_Tsuuka) &&
						aCentDedEkiJikoku.getChakujikoku().isNull() &&
						aCentDedEkijikokuPrev.getEkiatsukai() ==
						CentDedEkiJikoku::Ekiatsukai_None &&
						pCentDedRessya->getSihatsuEki() < iEkiOrder)
					{
						int idxRessyasyubetsu
							= pCentDedRessya->getRessyasyubetsuIndex();
						*pCDcDrawCell1 = createCDcdRessyabangou(idxRessyasyubetsu);
						*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);
						if (pCDcDrawCell3 != NULL)
						{
							*pCDcDrawCell3 = createCDcdRessyabangou(idxRessyasyubetsu);
						}
						strText1 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
						strText2 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
						strText3 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
					}
				}

				pCDcDrawCell1->setText(strText1);
				pCDcDrawCell2->setText(strText2);
				if (pCDcDrawCell3 != NULL)
				{
					pCDcDrawCell3->setText(strText3);
				}
			}

			//セルの背景色を指定します。
			{
				pCDcDrawCell1->setCdBrushProp(CdColorProp(255, 255, 255));
				pCDcDrawCell2->setCdBrushProp(CdColorProp(255, 255, 255));
				if (pCDcDrawCell3 != NULL)
				{
					pCDcDrawCell3->setCdBrushProp(CdColorProp(255, 255, 255));
				}
			}
		}
	}
}

void CCellBuilder::update02_02_02_09_setRessya_Track(
		int iXColumnNumber,
	int iYColumnNumber,
		const CentDedRessya * pCentDedRessya, 
		int iEkiOrder, 
		CWndJikokuhyou * pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	const CentDedRosen* pCentDedRosen =
		m_pCDedRosenFileData->getCentDedRosen();
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		pCentDedRosen->getCentDedEkiCont()->getMuPtr(
			pCentDedRessya->getRessyahoukou());
	// --------------------------------
	//CDcdTargetGetDC	aCDcdTarget(NULL);
	// --------------------------------
	{
		//CdYColSpec aCdYColSpec(
		//	CdYColSpec::ColumnType_Track,
		//	iEkiOrder);
		//int iYColumnNumber =
		//	m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec, false);
		CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell(
			iXColumnNumber, iYColumnNumber);
		// --------------------------------
		if (pCDcdGridCell != 0)
		{
			typedef CDcdTextbox CDcDrawCell;
			Ou<CDcDrawCell> pCDcDrawCell;
			// --------------------------------
			//　(2.2.*.1)　セルの結合セルを設定
			pCDcdGridCell->setAttachCellCount(1, 1);

			//　(2.2.*.2)　セル の	DcDrawオブジェクトの型を設定
			//	( CDcdTextbox とする)。
			{
				pCDcDrawCell = dynamic_castOu<CDcDrawCell>(
					pCDcdGridCell->getIfDcDraw());
				if (pCDcDrawCell == NULL)
				{
					pCDcDrawCell = OuNew<CDcDrawCell>(new CDcDrawCell);
					pCDcdGridCell->setIfDcDraw(pCDcDrawCell);
				}
			}
			//　(2.2.*.3)　セルの DcDrawオブジェクトに、属性を設定。
			{
				CentDedEkiJikoku	aCentDedEkiJikoku =
					pCentDedRessya->getCentDedEkiJikoku(iEkiOrder);
				int idxRessyasyubetsu
					= pCentDedRessya->getRessyasyubetsuIndex();
				*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
				if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_None)
				{
					tstring strText = _T("");
					if (iEkiOrder < pCentDedRessya->getSihatsuEki())
					{
						if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer
							&& m_bDisplayOuterTerminalShihatsu)
						{
							strText = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
						}
						else
						{
							strText = _T("");
						}
					}
					else if (iEkiOrder>pCentDedRessya->getSyuuchakuEki())
					{
						if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer
							&& m_bDisplayOuterTerminalShuchaku)
						{
							strText = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
						}
						else
						{
							strText = _T("");
						}
					}
					else if (iEkiOrder > pCentDedRessya->getSihatsuEki() && pCentDedRessya->getSihatsuEki() != -1 &&
						iEkiOrder < pCentDedRessya->getSyuuchakuEki())
					{
						strText = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
					}
					
					//int idxRessyasyubetsu
					//	= pCentDedRessya->getRessyasyubetsuIndex();
					//*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
					pCDcDrawCell->setText(strText);

				}
				else
				{
					pCDcDrawCell->setCdDrawTextProp(getCdDrawTextPropOperation());
					CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);
					CentDedEkiTrack2Cont aCentDedEkiTrack2Cont = aCdDedEki.getCentDedEkiTrack2Cont();

					tstring strText = aCentDedEkiTrack2Cont.get(
						aCentDedEkiJikoku.getRessyaTrackIndex()).getTrackRyakusyou(pCentDedRessya->getRessyahoukou());
					/*int idxRessyasyubetsu
						= pCentDedRessya->getRessyasyubetsuIndex();
					*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu);*/
					pCDcDrawCell->setText(strText);
				}
				
			}
		}
	}
}

void CCellBuilder::update02_02_02_21_setRessya_AfterOperationBefore(
	int iXColumnNumber,
	int iYColumnNumber,
	const CentDedRessya* pCentDedRessya,
	int iEkiOrder,
	CWndJikokuhyou* pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	const CentDedRosen* pCentDedRosen =
		m_pCDedRosenFileData->getCentDedRosen();
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		pCentDedRosen->getCentDedEkiCont()->getMuPtr(
			pCentDedRessya->getRessyahoukou());
	// --------------------------------
	//CDcdTargetGetDC	aCDcdTarget(NULL);
	// --------------------------------
	{
		CDcdGridCell* pCDcdGridCell1 = pCDcdGrid->getCell(
			iXColumnNumber, iYColumnNumber);
		CDcdGridCell* pCDcdGridCell2 = pCDcdGrid->getCell(
			iXColumnNumber, iYColumnNumber + 1);
		CDcdGridCell* pCDcdGridCell3 = NULL;
		CDcdGridCell* pCDcdGridCell4 = NULL;
		if (m_iEnableOperation > 1)
		{
			pCDcdGridCell3 = pCDcdGrid->getCell(
				iXColumnNumber, iYColumnNumber + 2);
			if (m_bDisplayInOutLinkCode)
			{
				pCDcdGridCell4 = pCDcdGrid->getCell(
					iXColumnNumber, iYColumnNumber + 3);
			}
		}
		// --------------------------------
		if (pCDcdGridCell1 != 0 && pCDcdGridCell2 != 0)
		{
			typedef CDcdTextbox CDcDrawCell;
			Ou<CDcDrawCell> pCDcDrawCell1;
			Ou<CDcDrawCell> pCDcDrawCell2;
			Ou<CDcDrawCell> pCDcDrawCell3;
			Ou<CDcDrawCell> pCDcDrawCell4;
			// --------------------------------
			//　(2.2.*.1)　セルの結合セルを設定
			pCDcdGridCell1->setAttachCellCount(1, 1);
			pCDcdGridCell2->setAttachCellCount(1, 1);
			if (pCDcdGridCell3 != 0)
			{
				pCDcdGridCell3->setAttachCellCount(1, 1);
			}
			if (pCDcdGridCell4 != 0)
			{
				pCDcdGridCell4->setAttachCellCount(1, 1);
			}

			//　(2.2.*.2)　セル の	DcDrawオブジェクトの型を設定
			//	( CDcdTextbox とする)。
			{
				pCDcDrawCell1 = dynamic_castOu<CDcDrawCell>(
					pCDcdGridCell1->getIfDcDraw());
				pCDcDrawCell2 = dynamic_castOu<CDcDrawCell>(
					pCDcdGridCell2->getIfDcDraw());
				if (pCDcDrawCell1 == NULL)
				{
					pCDcDrawCell1 = OuNew<CDcDrawCell>(new CDcDrawCell);
					pCDcdGridCell1->setIfDcDraw(pCDcDrawCell2);
				}
				if (pCDcDrawCell2 == NULL)
				{
					pCDcDrawCell2 = OuNew<CDcDrawCell>(new CDcDrawCell);
					pCDcdGridCell2->setIfDcDraw(pCDcDrawCell2);
				}
				if (pCDcdGridCell3 != 0)
				{
					pCDcDrawCell3 = dynamic_castOu<CDcDrawCell>(
						pCDcdGridCell3->getIfDcDraw());
					if (pCDcDrawCell3 == NULL)
					{
						pCDcDrawCell3 = OuNew<CDcDrawCell>(new CDcDrawCell);
						pCDcdGridCell3->setIfDcDraw(pCDcDrawCell3);
					}
				}
				if (pCDcdGridCell4 != 0)
				{
					pCDcDrawCell4 = dynamic_castOu<CDcDrawCell>(
						pCDcdGridCell4->getIfDcDraw());
					if (pCDcDrawCell4 == NULL)
					{
						pCDcDrawCell4 = OuNew<CDcDrawCell>(new CDcDrawCell);
						pCDcdGridCell4->setIfDcDraw(pCDcDrawCell4);
					}
				}
			}
			//　(2.2.*.3)　セルの DcDrawオブジェクトに、属性を設定。
			{
				CentDedEkiJikoku	aCentDedEkiJikoku =
					pCentDedRessya->getCentDedEkiJikoku(iEkiOrder);
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

				pCDcDrawCell1->setCdDrawTextProp(getCdDrawTextPropOperation());
				pCDcDrawCell2->setCdDrawTextProp(getCdDrawTextPropOperation());
				if (pCDcDrawCell3 != NULL)
				{
					pCDcDrawCell3->setCdDrawTextProp(getCdDrawTextPropOperation());
				}
				if (pCDcDrawCell4 != NULL)
				{
					pCDcDrawCell4->setCdDrawTextProp(getCdDrawTextPropOperation());
				}
				tstring strText1 = _T("");
				tstring strText2 = _T("");
				tstring strText3 = _T("");
				tstring strText4 = _T("");

				if (pFirstOperation != NULL)
				{
					/**
						開始作業の秒単位処理は、着時刻設定に基づき行います。
					*/
					if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Out)
					{
						strText1 = tstringOf(
							(LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_OperationOut));
						//Ver2.05 運用機能が通常モードかつ入出区連携コードが入力されている場合は、"出区"の後に入出区連携コードを表示します。
						//	→単独欄表示に変更
						//if (m_iEnableOperation > 1 && !pFirstOperation->getInOutLinkCode().empty())
						//{
						//	strText1 += _T("/");
						//	strText1 += pFirstOperation->getInOutLinkCode();
						//}

						CdDedJikoku aCdDedJikoku
							= pFirstOperation->getOutJikoku();
						strText2 = getCdDedJikokuConv().encode(aCdDedJikoku, true);

						strText3 = joinc(';', pFirstOperation->getOperationNumberOriginal());

						strText4 = pFirstOperation->getInOutLinkCode();
					}
					else if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
					{
						CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);
						//Ver2.05 運用機能が通常モードかつ入出区連携コードが入力されている場合は、路線外始発駅名欄を、ダイヤ略称+入出区連携コードに変更します。
						//	→単独欄表示に変更
						//if (m_iEnableOperation > 1 && !pFirstOperation->getInOutLinkCode().empty())
						//{
						//	strText1 = aCdDedEki.getOuterTerminalDiaRyaku(pFirstOperation->getOuterShihatsuekiIndex(), true);
						//	strText1 += _T("/");
						//	strText1 += pFirstOperation->getInOutLinkCode();
						//}
						//else
						//{
						strText1 = aCdDedEki.getOuterTerminalJikokuRyaku(pFirstOperation->getOuterShihatsuekiIndex(), true);
						//}

						CdDedJikoku aCdDedJikoku
							= pFirstOperation->getChakuJikoku();
						if (aCdDedJikoku.isNull())
						{
							aCdDedJikoku = ConnectJikoku;
							//pCDcDrawCell2->setCdDrawTextProp(
							//	getCdDrawTextPropTsuuka());
						}
						strText2 = getCdDedJikokuConv().encode(aCdDedJikoku, true);
						strText2 += tstringOf(
							(LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_Chaku));
						//strText2 += _T("着");

						strText3 = joinc(';', pFirstOperation->getOperationNumberOriginal());

						strText4 = pFirstOperation->getInOutLinkCode();
					}
					//2.00.05 仮運用番号に対応
					else if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Junction)
					{
						//視認性向上のため、"前接続"と表示させる
						strText1 = _T("前接続");

						CdDedJikoku aCdDedJikoku
							= pFirstOperation->getOriginJikoku();
						strText2 = getCdDedJikokuConv().encode(aCdDedJikoku, true);

						strText3 = joinc(';', pFirstOperation->getOperationNumberTemp());
						if (pCDcDrawCell3 != NULL)
						{
							pCDcDrawCell3->setCdDrawTextProp(
								getCdDrawTextPropTsuuka());
						}
					}
				}
				else if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_None)
				{
					if (iEkiOrder < pCentDedRessya->getValidSihatsuEki() && pCentDedRessya->getValidSihatsuEki() != -1)
					{
						if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer
							&& m_bDisplayOuterTerminalShihatsu)
						{
							int idxRessyasyubetsu
								= pCentDedRessya->getRessyasyubetsuIndex();
							*pCDcDrawCell1 = createCDcdRessyabangou(idxRessyasyubetsu);
							*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);
							if (pCDcDrawCell3 != NULL)
							{
								*pCDcDrawCell3 = createCDcdRessyabangou(idxRessyasyubetsu);
							}
							if (pCDcDrawCell4 != NULL)
							{
								*pCDcDrawCell4 = createCDcdRessyabangou(idxRessyasyubetsu);
							}
							strText1 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);
							strText2 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);
							strText3 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);
							strText4 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);
						}
					}
					else if (iEkiOrder > pCentDedRessya->getValidSyuuchakuEki() && pCentDedRessya->getValidSyuuchakuEki() != -1)
					{
						if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer
							&& m_bDisplayOuterTerminalShuchaku)
						{
							int idxRessyasyubetsu
								= pCentDedRessya->getRessyasyubetsuIndex();
							*pCDcDrawCell1 = createCDcdRessyabangou(idxRessyasyubetsu);
							*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);
							if (pCDcDrawCell3 != NULL)
							{
								*pCDcDrawCell3 = createCDcdRessyabangou(idxRessyasyubetsu);
							}
							if (pCDcDrawCell4 != NULL)
							{
								*pCDcDrawCell4 = createCDcdRessyabangou(idxRessyasyubetsu);
							}
							strText1 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);
							strText2 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);
							strText3 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);
							strText4 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);
						}
					}
					else if (iEkiOrder > pCentDedRessya->getSihatsuEki() && pCentDedRessya->getSihatsuEki() != -1 &&
						iEkiOrder < pCentDedRessya->getSyuuchakuEki())
					{
						int idxRessyasyubetsu
							= pCentDedRessya->getRessyasyubetsuIndex();
						*pCDcDrawCell1 = createCDcdRessyabangou(idxRessyasyubetsu);
						*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);
						if (pCDcDrawCell3 != NULL)
						{
							*pCDcDrawCell3 = createCDcdRessyabangou(idxRessyasyubetsu);
						}
						if (pCDcDrawCell4 != NULL)
						{
							*pCDcDrawCell4 = createCDcdRessyabangou(idxRessyasyubetsu);
						}
						strText1 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
						strText2 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
						strText3 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
						strText4 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
					}

				}

				//  1．	この駅の『駅時刻形式』が『発着』
				//  2．	この列車の、この駅での駅扱が『停車』か『通過』のいずれか
				//  3．	この列車の、この駅の発時刻が空
				//  4．	この列車の、この駅の次の駅での駅扱が『運行なし』
				//	5.	この列車の終点駅よりも起点方(getSyuuchakuEkiは「最後の運行なしではない」駅を返すので、-1チェックは不要)
				//
				//  この場合は、時刻表ビュー上では、この列車のこの駅での後作業欄は " || " 表示とします。
				{
					CentDedEkiJikoku aCentDedEkijikokuNext;
					if (0 <= iEkiOrder + 1
						&& iEkiOrder + 1 < muCdDedEki->size())
					{
						aCentDedEkijikokuNext =
							pCentDedRessya->getCentDedEkiJikoku(
								iEkiOrder + 1);
					}
					//aCentDedEkijikokuNext = 次の駅の駅時刻

					//CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);
					if (/*aCdDedEki.isHatsuChakuHyouji() &&*/
						(aCentDedEkiJikoku.getEkiatsukai() ==
							CentDedEkiJikoku::Ekiatsukai_Teisya ||
							aCentDedEkiJikoku.getEkiatsukai() ==
							CentDedEkiJikoku::Ekiatsukai_Tsuuka) &&
						aCentDedEkiJikoku.getHatsujikoku().isNull() &&
						aCentDedEkijikokuNext.getEkiatsukai() ==
						CentDedEkiJikoku::Ekiatsukai_None &&
						pCentDedRessya->getSyuuchakuEki() > iEkiOrder)
					{
						int idxRessyasyubetsu
							= pCentDedRessya->getRessyasyubetsuIndex();
						*pCDcDrawCell1 = createCDcdRessyabangou(idxRessyasyubetsu);
						*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);
						if (pCDcDrawCell3 != NULL)
						{
							*pCDcDrawCell3 = createCDcdRessyabangou(idxRessyasyubetsu);
						}
						if (pCDcDrawCell4 != NULL)
						{
							*pCDcDrawCell4 = createCDcdRessyabangou(idxRessyasyubetsu);
						}
						strText1 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
						strText2 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
						strText3 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
						strText4 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
					}
				}

				pCDcDrawCell1->setText(strText1);
				pCDcDrawCell2->setText(strText2);
				if (pCDcDrawCell3 != NULL)
				{
					pCDcDrawCell3->setText(strText3);
				}
				if (pCDcDrawCell4 != NULL)
				{
					pCDcDrawCell4->setText(strText4);
				}

			}

			//セルの背景色を指定します。
			{
				pCDcDrawCell1->setCdBrushProp(CdColorProp(255, 255, 255));
				pCDcDrawCell2->setCdBrushProp(CdColorProp(255, 255, 255));
				if (pCDcDrawCell3 != NULL)
				{
					pCDcDrawCell3->setCdBrushProp(CdColorProp(255, 255, 255));
				}
				if (pCDcDrawCell4 != NULL)
				{
					pCDcDrawCell4->setCdBrushProp(CdColorProp(255, 255, 255));
				}
			}
		}
	}
}

void CCellBuilder::update02_02_02_18_setRessya_AfterOperation(
	int iXColumnNumber,
	int iYColumnNumber,
	const CentDedRessya * pCentDedRessya, 
	int iEkiOrder, 
	CWndJikokuhyou * pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	const CentDedRosen* pCentDedRosen =
		m_pCDedRosenFileData->getCentDedRosen();
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		pCentDedRosen->getCentDedEkiCont()->getMuPtr(
			pCentDedRessya->getRessyahoukou());
	// --------------------------------
	//CDcdTargetGetDC	aCDcdTarget(NULL);
	// --------------------------------

	CentDedEkiCont::CdDedEki aEki = muCdDedEki->get(iEkiOrder);

	for(int idxa=0;idxa< aEki.getJikokuhyouAfterOperation();idxa++)
	{
		//CdYColSpec aCdYColSpec1(
		//	CdYColSpec::ColumnType_AfterOperation1,
		//	iEkiOrder,
		//	idxa);
		//CdYColSpec aCdYColSpec2(
		//	CdYColSpec::ColumnType_AfterOperation2,
		//	iEkiOrder,
		//	idxa);
		//int iYColumnNumber1 =
		//	m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec1, false);
		//int iYColumnNumber2 =
		//	m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec2, false);
		CDcdGridCell* pCDcdGridCell1 = pCDcdGrid->getCell(
			iXColumnNumber, iYColumnNumber + (idxa * 2));
		CDcdGridCell* pCDcdGridCell2 = pCDcdGrid->getCell(
			iXColumnNumber, iYColumnNumber + (idxa * 2) + 1);
		// --------------------------------
		if (pCDcdGridCell1 != 0 && pCDcdGridCell2 != 0)
		{
			typedef CDcdTextbox CDcDrawCell;
			Ou<CDcDrawCell> pCDcDrawCell1;
			Ou<CDcDrawCell> pCDcDrawCell2;
			// --------------------------------
			//　(2.2.*.1)　セルの結合セルを設定
			pCDcdGridCell1->setAttachCellCount(1, 1);
			pCDcdGridCell2->setAttachCellCount(1, 1);

			//　(2.2.*.2)　セル の	DcDrawオブジェクトの型を設定
			//	( CDcdTextbox とする)。
			{
				pCDcDrawCell1 = dynamic_castOu<CDcDrawCell>(
					pCDcdGridCell1->getIfDcDraw());
				pCDcDrawCell2 = dynamic_castOu<CDcDrawCell>(
					pCDcdGridCell2->getIfDcDraw());
				if (pCDcDrawCell1 == NULL)
				{
					pCDcDrawCell1 = OuNew<CDcDrawCell>(new CDcDrawCell);
					pCDcdGridCell1->setIfDcDraw(pCDcDrawCell2);
				}
				if (pCDcDrawCell2 == NULL)
				{
					pCDcDrawCell2 = OuNew<CDcDrawCell>(new CDcDrawCell);
					pCDcdGridCell2->setIfDcDraw(pCDcDrawCell2);
				}
			}
			//　(2.2.*.3)　セルの DcDrawオブジェクトに、属性を設定。
			{
				CentDedEkiJikoku	aCentDedEkiJikoku =
					pCentDedRessya->getCentDedEkiJikoku(iEkiOrder);
				const CentDedAfterOperationCont* pAfterOperationCont = aCentDedEkiJikoku.getCentDedAfterOperationCont();
				/*int idxRessyasyubetsu
					= pCentDedRessya->getRessyasyubetsuIndex();
				*pCDcDrawCell1 = createCDcdRessyabangou(idxRessyasyubetsu);
				*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);*/
				pCDcDrawCell1->setCdDrawTextProp(getCdDrawTextPropOperation());
				pCDcDrawCell2->setCdDrawTextProp(getCdDrawTextPropOperation());
				tstring strText1 = _T("");
				tstring strText2 = _T("");

				if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_None)
				{
					if (iEkiOrder < pCentDedRessya->getValidSihatsuEki() && pCentDedRessya->getValidSihatsuEki() != -1)
					{
						if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer
							&& m_bDisplayOuterTerminalShihatsu)
						{
							int idxRessyasyubetsu
								= pCentDedRessya->getRessyasyubetsuIndex();
							*pCDcDrawCell1 = createCDcdRessyabangou(idxRessyasyubetsu);
							*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);
							strText1 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);
							strText2 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);
						}
					}
					else if (iEkiOrder > pCentDedRessya->getValidSyuuchakuEki() && pCentDedRessya->getValidSyuuchakuEki() != -1)
					{
						if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer
							&& m_bDisplayOuterTerminalShuchaku)
						{
							int idxRessyasyubetsu
								= pCentDedRessya->getRessyasyubetsuIndex();
							*pCDcDrawCell1 = createCDcdRessyabangou(idxRessyasyubetsu);
							*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);
							strText1 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);
							strText2 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);
						}
					}
					else if (iEkiOrder > pCentDedRessya->getSihatsuEki() && pCentDedRessya->getSihatsuEki() != -1 &&
						iEkiOrder < pCentDedRessya->getSyuuchakuEki())
					{
						int idxRessyasyubetsu
							= pCentDedRessya->getRessyasyubetsuIndex();
						*pCDcDrawCell1 = createCDcdRessyabangou(idxRessyasyubetsu);
						*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);
						strText1 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
						strText2 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
					}
				}
				else if (pAfterOperationCont->size() <= idxa)
				{
					strText1 = _T("");
					strText2 = _T("");
				}
				else if(!pAfterOperationCont->getMuPtr()->get(idxa)->isLastOperation())
				{
					/**
						後作業を、表示欄数だけ、前方から表示する
						秒単位処理は、発時刻設定に基づき行います。
					*/
					const CentDedAfterOperation* pAfterOperation
							= pAfterOperationCont->getMuPtr()->get(idxa);
					if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
					{
						//strText1 = _T("換 ");
						strText1 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_SHUNT_RYAKU);
						strText1 += _T(" ");
						CentDedEkiTrack2Cont aCentDedEkiTrack2Cont = aEki.getCentDedEkiTrack2Cont();
						strText1 += aCentDedEkiTrack2Cont.get(pAfterOperation->getShuntTrackIndex())
							.getTrackRyakusyou(pCentDedRessya->getRessyahoukou());

						strText2 = getCdDedJikokuConv().encode(pAfterOperation->getOperationHatsuJikoku(),false);
					}
					else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
					{
						//strText1 = _T("増 ");
						strText1 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_CONNECT_RYAKU);
						strText1 += _T(" ");
						if (pAfterOperation->getIsConnectToFront())
						{
							//strText1 += _T("前方");
							strText1 += (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_CONNECT_FRONT);
						}
						else
						{
							//strText1 += _T("後方");
							strText1 += (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_CONNECT_BACK);
						}

						strText2 = getCdDedJikokuConv().encode(pAfterOperation->getConnectJikoku(), false);
					}
					else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
					{
						//strText1 = _T("解 ");
						strText1 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_RELEASE_RYAKU);
						strText1 += _T(" ");
						if (pAfterOperation->getReleasePos() == 0)//Back
						{
							//strText1 += _T("後");
							strText1 += (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_RELEASE_BACK);
							strText1 += to_tstring(pAfterOperation->getReleaseIndexCount());
						}
						else if (pAfterOperation->getReleasePos() == 1)//Front
						{
							//strText1 += _T("前");
							strText1 += (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_RELEASE_FRONT);
							strText1 += to_tstring(pAfterOperation->getReleaseIndexCount());
						}
						else if (pAfterOperation->getReleasePos() == 2)//FrontLeave
						{
							//strText1 += _T("前");
							strText1 += (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_RELEASE_FRONT);
							strText1 += to_tstring(pAfterOperation->getReleaseIndexCount());
							//strText1 += _T("以外");
							strText1 += (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_RELEASE_LEAVE);
						}

						strText2 = getCdDedJikokuConv().encode(pAfterOperation->getReleaseJikoku(), false);
					}
					//Ver2.00.05 運用番号順変更対応
					else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_NumberChange)
					{
						//strText1 = _T("運番変更");
						if (pAfterOperation->getOperationNumberReverse())
						{
							strText1 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_NUMBERREVERSE);
						}
						else
						{
							strText1 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_NUMBERCHANGE);
							strText2 = joinc(';', pAfterOperation->getOperationNumber());
						}
					}
				}


				//  1．	この駅の『駅時刻形式』が『発着』
				//  2．	この列車の、この駅での駅扱が『停車』か『通過』のいずれか
				//  3．	この列車の、この駅の発時刻が空
				//  4．	この列車の、この駅の次の駅での駅扱が『運行なし』
				//	5.	この列車の終点駅よりも起点方(getSyuuchakuEkiは「最後の運行なしではない」駅を返すので、-1チェックは不要)
				//
				//  この場合は、時刻表ビュー上では、この列車のこの駅での後作業欄は " || " 表示とします。
				{
					CentDedEkiJikoku aCentDedEkijikokuNext;
					if (0 <= iEkiOrder + 1
						&& iEkiOrder + 1 < muCdDedEki->size())
					{
						aCentDedEkijikokuNext =
							pCentDedRessya->getCentDedEkiJikoku(
								iEkiOrder + 1);
					}
					//aCentDedEkijikokuNext = 次の駅の駅時刻

					//CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);
					if (/*aCdDedEki.isHatsuChakuHyouji() &&*/
						(aCentDedEkiJikoku.getEkiatsukai() ==
							CentDedEkiJikoku::Ekiatsukai_Teisya ||
						aCentDedEkiJikoku.getEkiatsukai() ==
							CentDedEkiJikoku::Ekiatsukai_Tsuuka) &&
						aCentDedEkiJikoku.getHatsujikoku().isNull() &&
						aCentDedEkijikokuNext.getEkiatsukai() ==
							CentDedEkiJikoku::Ekiatsukai_None &&
						pCentDedRessya->getSyuuchakuEki() > iEkiOrder)
					{
						int idxRessyasyubetsu
							= pCentDedRessya->getRessyasyubetsuIndex();
						*pCDcDrawCell1 = createCDcdRessyabangou(idxRessyasyubetsu);
						*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);
						strText1 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
						strText2 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
						//pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
						//	IDS_WORD_JIKOKUHYOU_KEIYUNASI));	//"||"
					}

				}
				pCDcDrawCell1->setText(strText1);
				pCDcDrawCell2->setText(strText2);

			}

			//セルの背景色を指定します。
			{
				pCDcDrawCell1->setCdBrushProp(CdColorProp(255, 255, 255));
				pCDcDrawCell2->setCdBrushProp(CdColorProp(255, 255, 255));
			}
		}
	}
}

void CCellBuilder::update02_02_02_22_setRessya_AfterOperationAfter(
	int iXColumnNumber,
	int iYColumnNumber,
	const CentDedRessya* pCentDedRessya,
	int iEkiOrder,
	CWndJikokuhyou* pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	const CentDedRosen* pCentDedRosen =
		m_pCDedRosenFileData->getCentDedRosen();
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		pCentDedRosen->getCentDedEkiCont()->getMuPtr(
			pCentDedRessya->getRessyahoukou());
	// --------------------------------
	//CDcdTargetGetDC	aCDcdTarget(NULL);
	// --------------------------------
	{
		CDcdGridCell* pCDcdGridCell1 = pCDcdGrid->getCell(
			iXColumnNumber, iYColumnNumber);
		CDcdGridCell* pCDcdGridCell2 = pCDcdGrid->getCell(
			iXColumnNumber, iYColumnNumber + 1);
		CDcdGridCell* pCDcdGridCell3 = NULL;
		if (m_iEnableOperation > 1 && m_bDisplayInOutLinkCode)
		{
			pCDcdGridCell3 = pCDcdGrid->getCell(
				iXColumnNumber, iYColumnNumber + 2);
		}
		// --------------------------------
		if (pCDcdGridCell1 != 0 && pCDcdGridCell2 != 0)
		{
			typedef CDcdTextbox CDcDrawCell;
			Ou<CDcDrawCell> pCDcDrawCell1;
			Ou<CDcDrawCell> pCDcDrawCell2;
			Ou<CDcDrawCell> pCDcDrawCell3;
			// --------------------------------
			//　(2.2.*.1)　セルの結合セルを設定
			pCDcdGridCell1->setAttachCellCount(1, 1);
			pCDcdGridCell2->setAttachCellCount(1, 1);
			if (pCDcdGridCell3 != 0)
			{
				pCDcdGridCell3->setAttachCellCount(1, 1);
			}

			//　(2.2.*.2)　セル の	DcDrawオブジェクトの型を設定
			//	( CDcdTextbox とする)。
			{
				pCDcDrawCell1 = dynamic_castOu<CDcDrawCell>(
					pCDcdGridCell1->getIfDcDraw());
				pCDcDrawCell2 = dynamic_castOu<CDcDrawCell>(
					pCDcdGridCell2->getIfDcDraw());
				if (pCDcDrawCell1 == NULL)
				{
					pCDcDrawCell1 = OuNew<CDcDrawCell>(new CDcDrawCell);
					pCDcdGridCell1->setIfDcDraw(pCDcDrawCell2);
				}
				if (pCDcDrawCell2 == NULL)
				{
					pCDcDrawCell2 = OuNew<CDcDrawCell>(new CDcDrawCell);
					pCDcdGridCell2->setIfDcDraw(pCDcDrawCell2);
				}
				if (pCDcdGridCell3 != 0)
				{
					pCDcDrawCell3 = dynamic_castOu<CDcDrawCell>(
						pCDcdGridCell3->getIfDcDraw());
					if (pCDcDrawCell3 == NULL)
					{
						pCDcDrawCell3 = OuNew<CDcDrawCell>(new CDcDrawCell);
						pCDcdGridCell3->setIfDcDraw(pCDcDrawCell3);
					}
				}
			}
			//　(2.2.*.3)　セルの DcDrawオブジェクトに、属性を設定。
			{
				CentDedEkiJikoku	aCentDedEkiJikoku =
					pCentDedRessya->getCentDedEkiJikoku(iEkiOrder);
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

				pCDcDrawCell1->setCdDrawTextProp(getCdDrawTextPropOperation());
				pCDcDrawCell2->setCdDrawTextProp(getCdDrawTextPropOperation());
				if (pCDcDrawCell3 != NULL)
				{
					pCDcDrawCell3->setCdDrawTextProp(getCdDrawTextPropOperation());
				}
				tstring strText1 = _T("");
				tstring strText2 = _T("");
				tstring strText3 = _T("");

				if (pLastOperation != NULL)
				{
					/**
						終了作業の秒単位処理は、発時刻設定に基づき行います。
					*/

					if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_In)
					{
						strText1 = tstringOf(
							(LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_OperationIn));
						//Ver2.05 運用機能が通常モードかつ入出区連携コードが入力されている場合は、"入区"の後に入出区連携コードを表示します。
						//	→単独欄表示に変更
						//if (m_iEnableOperation > 1 && !pLastOperation->getInOutLinkCode().empty())
						//{
						//	strText1 += _T("/");
						//	strText1 += pLastOperation->getInOutLinkCode();
						//}

						CdDedJikoku aCdDedJikoku
							= pLastOperation->getInJikoku();
						strText2 = getCdDedJikokuConv().encode(aCdDedJikoku, false);

						strText3 = pLastOperation->getInOutLinkCode();
					}
					else if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
					{
						CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);
						//Ver2.05 運用機能が通常モードかつ入出区連携コードが入力されている場合は、路線外終着駅名欄を、ダイヤ略称+入出区連携コードに変更します。
						//	→単独欄表示に変更
						//if (m_iEnableOperation > 1 && !pLastOperation->getInOutLinkCode().empty())
						//{
						//	strText1 = aCdDedEki.getOuterTerminalDiaRyaku(pLastOperation->getOuterShuchakuekiIndex(), true);
						//	strText1 += _T("/");
						//	strText1 += pLastOperation->getInOutLinkCode();
						//}
						//else
						//{
							strText1 = aCdDedEki.getOuterTerminalJikokuRyaku(pLastOperation->getOuterShuchakuekiIndex(), true);
						//}

						CdDedJikoku aCdDedJikoku
							= pLastOperation->getHatsuJikoku();
						if (aCdDedJikoku.isNull())
						{
							aCdDedJikoku = ReleaseJikoku;
							//pCDcDrawCell2->setCdDrawTextProp(
							//	getCdDrawTextPropTsuuka());
						}
						strText2 = getCdDedJikokuConv().encode(aCdDedJikoku, false);
						strText2 += tstringOf(
							(LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_Hatsu));
						//strText2 += _T("発");

						strText3 = pLastOperation->getInOutLinkCode();
					}
					else if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Junction)
					{
						//Ver2.05 1行目には、次列車接続タイプを表示する。視認性向上のため、別列車の場合は"次接続"と表示させる
						if (pLastOperation->getNextJunctionType() == 1)
						{
							strText1 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_SYUBETSUCHANGE);
						}
						else if (pLastOperation->getNextJunctionType() == 2)
						{
							strText1 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_PROPERTYCHANGE);
						}
						else if (pLastOperation->getNextJunctionType() == 3)
						{
							strText1 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_PROPERTYSAME);
						}
						else
						{
							strText1 = _T("次接続");
						}

						CdDedJikoku aCdDedJikoku
							= pLastOperation->getTerminalJikoku();
						strText2 = getCdDedJikokuConv().encode(aCdDedJikoku, false);
					}
				}
				else if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_None)
				{
					if (iEkiOrder < pCentDedRessya->getValidSihatsuEki() && pCentDedRessya->getValidSihatsuEki() != -1)
					{
						if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer
							&& m_bDisplayOuterTerminalShihatsu)
						{
							int idxRessyasyubetsu
								= pCentDedRessya->getRessyasyubetsuIndex();
							*pCDcDrawCell1 = createCDcdRessyabangou(idxRessyasyubetsu);
							*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);
							if (pCDcDrawCell3 != NULL)
							{
								*pCDcDrawCell3 = createCDcdRessyabangou(idxRessyasyubetsu);
							}
							strText1 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);
							strText2 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);
							strText3 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);
						}
					}
					else if (iEkiOrder > pCentDedRessya->getValidSyuuchakuEki() && pCentDedRessya->getValidSyuuchakuEki() != -1)
					{
						if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer
							&& m_bDisplayOuterTerminalShuchaku)
						{
							int idxRessyasyubetsu
								= pCentDedRessya->getRessyasyubetsuIndex();
							*pCDcDrawCell1 = createCDcdRessyabangou(idxRessyasyubetsu);
							*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);
							if (pCDcDrawCell3 != NULL)
							{
								*pCDcDrawCell3 = createCDcdRessyabangou(idxRessyasyubetsu);
							}
							strText1 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);
							strText2 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);
							strText3 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);
						}
					}
					else if (iEkiOrder > pCentDedRessya->getSihatsuEki() && pCentDedRessya->getSihatsuEki() != -1 &&
						iEkiOrder < pCentDedRessya->getSyuuchakuEki())
					{
						int idxRessyasyubetsu
							= pCentDedRessya->getRessyasyubetsuIndex();
						*pCDcDrawCell1 = createCDcdRessyabangou(idxRessyasyubetsu);
						*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);
						if (pCDcDrawCell3 != NULL)
						{
							*pCDcDrawCell3 = createCDcdRessyabangou(idxRessyasyubetsu);
						}
						strText1 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
						strText2 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
						strText3 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
					}
				}

				//  1．	この駅の『駅時刻形式』が『発着』
				//  2．	この列車の、この駅での駅扱が『停車』か『通過』のいずれか
				//  3．	この列車の、この駅の発時刻が空
				//  4．	この列車の、この駅の次の駅での駅扱が『運行なし』
				//	5.	この列車の終点駅よりも起点方(getSyuuchakuEkiは「最後の運行なしではない」駅を返すので、-1チェックは不要)
				//
				//  この場合は、時刻表ビュー上では、この列車のこの駅での後作業欄は " || " 表示とします。
				{
					CentDedEkiJikoku aCentDedEkijikokuNext;
					if (0 <= iEkiOrder + 1
						&& iEkiOrder + 1 < muCdDedEki->size())
					{
						aCentDedEkijikokuNext =
							pCentDedRessya->getCentDedEkiJikoku(
								iEkiOrder + 1);
					}
					//aCentDedEkijikokuNext = 次の駅の駅時刻

					//CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);
					if (/*aCdDedEki.isHatsuChakuHyouji() &&*/
						(aCentDedEkiJikoku.getEkiatsukai() ==
							CentDedEkiJikoku::Ekiatsukai_Teisya ||
							aCentDedEkiJikoku.getEkiatsukai() ==
							CentDedEkiJikoku::Ekiatsukai_Tsuuka) &&
						aCentDedEkiJikoku.getHatsujikoku().isNull() &&
						aCentDedEkijikokuNext.getEkiatsukai() ==
						CentDedEkiJikoku::Ekiatsukai_None &&
						pCentDedRessya->getSyuuchakuEki() > iEkiOrder)
					{
						int idxRessyasyubetsu
							= pCentDedRessya->getRessyasyubetsuIndex();
						*pCDcDrawCell1 = createCDcdRessyabangou(idxRessyasyubetsu);
						*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);
						if (pCDcDrawCell3 != NULL)
						{
							*pCDcDrawCell3 = createCDcdRessyabangou(idxRessyasyubetsu);
						}
						strText1 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
						strText2 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
						strText3 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
					}
				}

				pCDcDrawCell1->setText(strText1);
				pCDcDrawCell2->setText(strText2);
				if (pCDcDrawCell3 != NULL)
				{
					pCDcDrawCell3->setText(strText3);
				}
			}

			//セルの背景色を指定します。
			{
				pCDcDrawCell1->setCdBrushProp(CdColorProp(255, 255, 255));
				pCDcDrawCell2->setCdBrushProp(CdColorProp(255, 255, 255));
				if (pCDcDrawCell3 != NULL)
				{
					pCDcDrawCell3->setCdBrushProp(CdColorProp(255, 255, 255));
				}
			}
		}
	}
}

	

void CCellBuilder::update02_02_02_07_setRessya_Hatsu(
		int iXColumnNumber ,
	int iYColumnNumber,
		const CentDedRessya* pCentDedRessya ,
		int iEkiOrder ,
		CWndJikokuhyou* pCWndJikokuhyou ) 
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid() ;
	const CentDedRosen* pCentDedRosen = 
		m_pCDedRosenFileData->getCentDedRosen() ;
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki = 
		pCentDedRosen->getCentDedEkiCont()->getMuPtr(
			pCentDedRessya->getRessyahoukou() ) ;
	// --------------------------------
	//CDcdTargetGetDC	aCDcdTarget( NULL ) ;
	// --------------------------------
	{
		//CdYColSpec aCdYColSpec( 
		//	CdYColSpec::ColumnType_Ekijikoku_Hatsu , 
		//	iEkiOrder ) ;
		//int iYColumnNumber = 
		//	m_CdYColSpecCont.ColumnNumberFromSpec( aCdYColSpec , false ) ;
		CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell( 
			iXColumnNumber , iYColumnNumber ) ;
		// --------------------------------
		if ( pCDcdGridCell != 0 )
		{
			typedef CDcdTextbox CDcDrawCell ;
			Ou<CDcDrawCell> pCDcDrawCell ;
			// --------------------------------
			//　(2.2.*.1)　セルの結合セルを設定
			pCDcdGridCell->setAttachCellCount( 1 , 1 ) ;

			//　(2.2.*.2)　セル の	DcDrawオブジェクトの型を設定
			//	( CDcdTextbox とする)。
			{
				pCDcDrawCell = dynamic_castOu<CDcDrawCell>( 
					pCDcdGridCell->getIfDcDraw() ) ;
				if ( pCDcDrawCell == NULL )
				{
					pCDcDrawCell = OuNew<CDcDrawCell>( new CDcDrawCell ) ;
					pCDcdGridCell->setIfDcDraw( pCDcDrawCell ) ;
				}
			}
			//　(2.2.*.3)　セルの DcDrawオブジェクトに、属性を設定。
			{
				CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get( iEkiOrder ) ;
				int idxRessyasyubetsu 
					= pCentDedRessya->getRessyasyubetsuIndex() ;
				//	主要駅では、空欄に主要駅表記を行います。
				//	起点・終点・着発駅のいずれかである場合、
				//	境界線に接している駅である場合は除きます。
				bool bIsSyuyouEkiHyouki = false ;
				if ( aCdDedEki.getEkikibo() == CentDedEki::EEkikibo::Ekikibo_Syuyou 
					&&	0 < iEkiOrder 
					&& iEkiOrder < muCdDedEki->size() - 1 
					&& 	!aCdDedEki.isHatsuChakuHyouji() )
				{
					//	境界線に接している駅である場合は除きます。
					CentDedEkiCont::CdDedEki aCentDedEkiTonari ;
					if ( iEkiOrder > 0 )
					{
						aCentDedEkiTonari = muCdDedEki->get( iEkiOrder - 1 ) ;
					}

					if ( !aCentDedEkiTonari.getKyoukaisen()  && 
						!aCdDedEki.getKyoukaisen() )
					{
						bIsSyuyouEkiHyouki = true ;
					}
				}
				//bIsSyuyouEkiHyouji = 空欄に主要駅表記を行います。

				CentDedEkiJikoku	aCentDedEkiJikoku =
					pCentDedRessya->getCentDedEkiJikoku( iEkiOrder ) ;
				CdDedJikoku aCdDedJikoku 
					= aCentDedEkiJikoku.getHatsujikoku() ;

				// --------------------------------
				//	駅時刻に合わせて、セルに文字を表示
				// --------------------------------
				switch( aCentDedEkiJikoku.getEkiatsukai() )
				{
				case CentDedEkiJikoku::Ekiatsukai_None :
					{
						if (iEkiOrder < pCentDedRessya->getSihatsuEki() && pCentDedRessya->getSihatsuEki() != -1)
						{
							if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer
								&& m_bDisplayOuterTerminalShihatsu)
							{
								*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
								pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"

							}
							else if (bIsSyuyouEkiHyouki)
							{
								//	主要駅での表記（着発の場合は除く）
								//	"----"
								*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
								pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_UNKOUNASI_SYUYOU));
							}
							else
							{
								//	その他の駅での表記
								//	"・・"
								*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
								pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_UNKOUNASI_IPPAN));
							}
						}
						else if (iEkiOrder>pCentDedRessya->getSyuuchakuEki() && pCentDedRessya->getSyuuchakuEki() !=-1)
						{
							if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer
								&& m_bDisplayOuterTerminalShuchaku)
							{
								*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
								pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"

							}
							else if (bIsSyuyouEkiHyouki)
							{
								//	主要駅での表記（着発の場合は除く）
								//	"----"
								*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
								pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_UNKOUNASI_SYUYOU));
							}
							else
							{
								//	その他の駅での表記
								//	"・・"
								*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
								pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_UNKOUNASI_IPPAN));
							}
						}
						else if (iEkiOrder > pCentDedRessya->getSihatsuEki() && pCentDedRessya->getSihatsuEki() != -1 &&
							iEkiOrder < pCentDedRessya->getSyuuchakuEki())
						{
							*pCDcDrawCell = createCDcdRessyabangou(
								idxRessyasyubetsu);
							pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"
						}
						else if ( bIsSyuyouEkiHyouki )
						{
							//	主要駅での表記（着発の場合は除く）
							//	"----"
							*pCDcDrawCell = createCDcdRessyabangou(
								idxRessyasyubetsu );
							pCDcDrawCell->setText( (LPCTSTR)MfcUtil::LoadCString( 
									IDS_WORD_JIKOKUHYOU_UNKOUNASI_SYUYOU ) ) ;
						}
						else
						{
							//	その他の駅での表記
							//	"・・"
							*pCDcDrawCell = createCDcdRessyabangou( 
								idxRessyasyubetsu );
							pCDcDrawCell->setText( (LPCTSTR)MfcUtil::LoadCString( 
									IDS_WORD_JIKOKUHYOU_UNKOUNASI_IPPAN ) ) ;
						}
					}
					break ;
				 case CentDedEkiJikoku::Ekiatsukai_Tsuuka :
					{
						if ( !aCdDedJikoku.isNull() && m_bDisplayTsuukaEkiJikoku )
						{
							/**
								秒単位表示OFFの場合は、切り上げ・切り捨ての処理を行いますが、
								その補助のため、発時刻が切り捨てで、着時刻が30秒以上切り上げまたは切り上げの場合は、着時刻の取得を行います。
								この駅と前の駅の間が運行なしの場合は、運行なしを超えた先の駅から時刻を取得します。
							*/
							CdDedJikoku aChakuJikoku;
							if (!getDisplaySecondEkiJikoku() &&
								m_iSecondRoundChaku >= 1 &&
								m_iSecondRoundHatsu == 0)
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
											m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()
											->isSameBrunchLoopGroup(iEkiOrder, iChakuEkiOrder, pCentDedRessya->getRessyahoukou()))
										{
											aChakuJikoku = pCentDedRessya->getCentDedEkiJikoku(iChakuEkiOrder).getChakujikoku();
										}
									}
								}
							}

							//	通過駅の駅時刻が設定されており、
							//	『通過駅の駅時刻を表示する』指定になっている場合は
							//	時刻を表示
							*pCDcDrawCell = createCDcdEkijikoku(
								idxRessyasyubetsu,
								CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka);
							tstring strText = getCdDedJikokuConv().encode( aCdDedJikoku , false, aChakuJikoku) ;
							pCDcDrawCell->setText(strText ) ;
							pCDcDrawCell->setCdBrushProp( CdColorProp( 255 , 255 , 255 ) ) ;
							//基準運転時分機能Update_by_d_mania 17.4.17
							//Ver2.06.07 基準運転時分取得元ダイヤインデクス機能追加に伴う変更
							int iKijunDiaIndex = m_pCDedRosenFileData->getCentDedRosen()->getKijunDiaIndex();
							//機能が有効かつ基準運転時分取得元ダイヤ以外かつ、列車の始発駅ではない
							if( m_bStandardOperationTimeFunction &&
								iEkiOrder > pCentDedRessya->getSihatsuEki() &&
								iEkiOrder < pCentDedRessya->getSyuuchakuEki() &&
								m_pCDedRosenFileData->getCentDedRosen()->getCentDedDiaCont()->findCentDedDiaByName(
									m_pCentDedRessyaCont->getDia()->getName()) != iKijunDiaIndex)
							{
								pCDcDrawCell->setCdBrushProp( update02_02_02_StdOpeTimeFunc(
									false ,
									iKijunDiaIndex ,
									iEkiOrder ,
									pCentDedRessya ,
									muCdDedEki ) ) ;
							}
						}
							//終着駅かつ路線外発着設定で、駅時刻なしor通過駅時刻表示なしなら、経由無しマークを表示
						else if (iEkiOrder == pCentDedRessya->getSyuuchakuEki() &&
							pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer &&
							m_bDisplayOuterTerminalShuchaku)
						{

							*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
							pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"
						}
						else
						{
							*pCDcDrawCell = createCDcdRessyabangou( 
								idxRessyasyubetsu );
							pCDcDrawCell->setText( (LPCTSTR)MfcUtil::LoadCString( 
								IDS_WORD_JIKOKUHYOU_TSUUKA ) );	//" ﾚ"
						}
					}
					break ;
				 case CentDedEkiJikoku::Ekiatsukai_Teisya :
					{
						//	停車駅の駅時刻が指定されている
						if ( !aCdDedJikoku.isNull() )
						{
							/**
								秒単位表示OFFの場合は、切り上げ・切り捨ての処理を行いますが、
								その補助のため、発時刻が切り捨てで、着時刻が30秒以上切り上げまたは切り上げの場合は、着時刻の取得を行います。
								この駅と前の駅の間が運行なしの場合は、運行なしを超えた先の駅から時刻を取得します。
							*/
							CdDedJikoku aChakuJikoku;
							if (!getDisplaySecondEkiJikoku() &&
								m_iSecondRoundChaku >= 1 &&
								m_iSecondRoundHatsu == 0)
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
											m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()
											->isSameBrunchLoopGroup(iEkiOrder, iChakuEkiOrder, pCentDedRessya->getRessyahoukou()))
										{
											aChakuJikoku = pCentDedRessya->getCentDedEkiJikoku(iChakuEkiOrder).getChakujikoku();
										}
									}
								}
							}

							*pCDcDrawCell = createCDcdEkijikoku( 
								idxRessyasyubetsu ,
								CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya);
							tstring strText = getCdDedJikokuConv().encode( aCdDedJikoku, false, aChakuJikoku) ;
							pCDcDrawCell->setText(strText ) ;
							//基準運転時分機能Update_by_d_mania 17.4.17
							//Ver2.06.07 基準運転時分取得元ダイヤインデクス機能追加に伴う変更
							int iKijunDiaIndex = m_pCDedRosenFileData->getCentDedRosen()->getKijunDiaIndex();
							//機能が有効かつ通過駅時刻表示が有効かつ
							//基準運転時分取得元ダイヤ以外かつ、列車の始発駅ではない
							if( m_bStandardOperationTimeFunction &&
								m_bDisplayTsuukaEkiJikoku &&
								iEkiOrder > pCentDedRessya->getSihatsuEki() &&
								iEkiOrder < pCentDedRessya->getSyuuchakuEki() &&
								m_pCDedRosenFileData->getCentDedRosen()->getCentDedDiaCont()->findCentDedDiaByName(
									m_pCentDedRessyaCont->getDia()->getName()) != iKijunDiaIndex)
							{
								pCDcDrawCell->setCdBrushProp( update02_02_02_StdOpeTimeFunc(
									false ,
									iKijunDiaIndex ,
									iEkiOrder ,
									pCentDedRessya ,
									muCdDedEki ) ) ;
							}
							//Updateここまで
						}
							//終着駅かつ路線外発着設定で、駅時刻なしなら、経由無しマークを表示
						else if (iEkiOrder == pCentDedRessya->getSyuuchakuEki() &&
							pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer &&
							m_bDisplayOuterTerminalShuchaku)
						{

							*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
							pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"
						}
						//	停車駅の駅時刻が指定されていない
						else 
						{
							*pCDcDrawCell = createCDcdRessyabangou( 
								idxRessyasyubetsu );

							//	[時刻表ビュー上の着時刻の表示列を算出
							CdYColSpec aCdYColSpec( 
								CdYColSpec::ColumnType_Ekijikoku_Chaku , 
								iEkiOrder ) ;
							int iYColumnNumberChaku = 
								m_CdYColSpecCont.ColumnNumberFromSpec( aCdYColSpec , false ) ;

							//	時刻表ビュー上に着時刻の表示あり AND 
							//	終着駅の場合は "・・" 表示
							if ( iYColumnNumberChaku >= 0 && 
								pCentDedRessya->getSyuuchakuEki() == iEkiOrder )
							{
								pCDcDrawCell->setText( (LPCTSTR)MfcUtil::LoadCString( 
									IDS_WORD_JIKOKUHYOU_UNKOUNASI_IPPAN ) ) ;
							}
							//	始発・途中駅の場合・発時刻のみ表示の場合は " ○ " 表示
							else	
							{
								pCDcDrawCell->setText( (LPCTSTR)MfcUtil::LoadCString( 
									IDS_WORD_JIKOKUHYOU_TEISYA ) ) ;
							}
						}
					}
					break ;
				}

				//セルの背景色を指定します。
				if (!m_bStandardOperationTimeFunction)
				{
					pCDcDrawCell->setCdBrushProp(getBackColor(
						iXColumnNumber,
						iEkiOrder,
						idxRessyasyubetsu));
				}

				//  1．	この駅の『駅時刻形式』が『発着』
				//  2．	この列車の、この駅での駅扱が『停車』か『通過』のいずれか
				//  3．	この列車の、この駅の着時刻が空
				//  4．	この列車の、この駅の前の駅での駅扱が『運行なし』
				//	5.	この列車の始発駅よりも終点方(getSihatsuEkiは「最初の運行なしではない」駅を返すので、-1チェックは不要
				//
				//  この場合は、時刻表ビュー上では、この列車のこの駅での発時刻は " || " 表示とします。
				{
					CentDedEkiJikoku aCentDedEkijikokuNext ;
					if ( 0 <= iEkiOrder + 1 
						&& iEkiOrder + 1 < muCdDedEki->size() ) 
					{
						aCentDedEkijikokuNext = 
							pCentDedRessya->getCentDedEkiJikoku( 
								iEkiOrder + 1 ) ;
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
						pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI));	//"||"
					}

				}
			}
		}
	}
}

void CCellBuilder::update02_02_02_16_setRessya_OuterTerminal_Shuchaku(
	int iXColumnNumber,
	int iYColumnNumber,
	const CentDedRessya * pCentDedRessya,
	CWndJikokuhyou * pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	const CentDedRosen* pCentDedRosen =
		m_pCDedRosenFileData->getCentDedRosen();
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		pCentDedRosen->getCentDedEkiCont()->getMuPtr(
			pCentDedRessya->getRessyahoukou());
	// --------------------------------
	//CDcdTargetGetDC	aCDcdTarget(NULL);
	// --------------------------------
	{
		//CdYColSpec aCdYColSpec1(
		//	CdYColSpec::ColumnType_Outer_Shuchaku1);
		//CdYColSpec aCdYColSpec2(
		//	CdYColSpec::ColumnType_Outer_Shuchaku2);
		//int iYColumnNumber1 =
		//	m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec1, false);
		//int iYColumnNumber2 =
		//	m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec2, false);
		CDcdGridCell* pCDcdGridCell1 = pCDcdGrid->getCell(
			iXColumnNumber, iYColumnNumber);
		CDcdGridCell* pCDcdGridCell2 = pCDcdGrid->getCell(
			iXColumnNumber, iYColumnNumber+1);
		// --------------------------------
		if (pCDcdGridCell1 != 0 && pCDcdGridCell2 != 0)
		{
			typedef CDcdTextbox CDcDrawCell;
			Ou<CDcDrawCell> pCDcDrawCell1;
			Ou<CDcDrawCell> pCDcDrawCell2;
			// --------------------------------
			//　(2.2.*.1)　セルの結合セルを設定
			pCDcdGridCell1->setAttachCellCount(1, 1);
			pCDcdGridCell2->setAttachCellCount(1, 1);

			//　(2.2.*.2)　セル の	DcDrawオブジェクトの型を設定
			//	( CDcdTextbox とする)。
			{
				pCDcDrawCell1 = dynamic_castOu<CDcDrawCell>(
					pCDcdGridCell1->getIfDcDraw());
				pCDcDrawCell2 = dynamic_castOu<CDcDrawCell>(
					pCDcdGridCell2->getIfDcDraw());
				if (pCDcDrawCell1 == NULL)
				{
					pCDcDrawCell1 = OuNew<CDcDrawCell>(new CDcDrawCell);
					pCDcdGridCell1->setIfDcDraw(pCDcDrawCell1);
				}
				if (pCDcDrawCell2 == NULL)
				{
					pCDcDrawCell2 = OuNew<CDcDrawCell>(new CDcDrawCell);
					pCDcdGridCell2->setIfDcDraw(pCDcDrawCell2);
				}
			}
			//　(2.2.*.3)　セルの DcDrawオブジェクトに、属性を設定。
			{
				int idxRessyasyubetsu
				= pCentDedRessya->getRessyasyubetsuIndex();
				*pCDcDrawCell1 = createCDcdRessyabangou(idxRessyasyubetsu);
				*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);
				//pCDcDrawCell1->setCdDrawTextProp(getCdDrawTextPropOperation());
				//pCDcDrawCell2->setCdDrawTextProp(getCdDrawTextPropOperation());
				tstring strText1;
				tstring strText2;

				const CentDedAfterOperation aLastOperation = pCentDedRessya->getLastOperation();
				if (aLastOperation.getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
				{
					CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(pCentDedRessya->getValidSyuuchakuEki());
					strText1 = aCdDedEki.getOuterTerminalJikokuRyaku(aLastOperation.getOuterShuchakuekiIndex(),true);
					if (!(aLastOperation.getOuterShuchakuJikoku().isNull()))
					{
						CdDedJikoku aCdDedJikoku
							= aLastOperation.getOuterShuchakuJikoku();
						strText2 = getCdDedJikokuConv().encode(aCdDedJikoku,true);
					}
				}
				pCDcDrawCell1->setText(strText1);
				pCDcDrawCell2->setText(strText2);
			}

			//セルの背景色を指定します。
			{
				pCDcDrawCell1->setCdBrushProp(CdColorProp(255, 255, 255));
				pCDcDrawCell2->setCdBrushProp(CdColorProp(255, 255, 255));
			}
		}
	}
}

void CCellBuilder::update02_02_02_08_setRessya_Bikou( 
		int iXColumnNumber ,
		int iYColumnNumber,
		const CentDedRessya* pCentDedRessya ,
		CWndJikokuhyou* pCWndJikokuhyou ) 
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid() ;
/*	const CentDedRosen* pCentDedRosen = 
		m_pCDedRosenFileData->getCentDedRosen() */;
	// --------------------------------
	//CDcdTargetGetDC	aCDcdTarget( NULL ) ;
	// --------------------------------
	//CdYColSpec aCdYColSpec( 
	//	CdYColSpec::ColumnType_Bikou ) ;
	//int iYColumnNumber = 
	//	m_CdYColSpecCont.ColumnNumberFromSpec( aCdYColSpec , false ) ;
	CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell( 
		iXColumnNumber , iYColumnNumber ) ;
	// --------------------------------
	if ( pCDcdGridCell != 0 )
	{
		typedef CDcdTextboxV3 CDcDrawCell ;
		Ou<CDcDrawCell> pCDcDrawCell ;
		// --------------------------------
		//　(2.2.*.1)　セル(ColumnType_Ressya,ColumnType_Ressyabangou) の
		//	結合セルを設定
		pCDcdGridCell->setAttachCellCount( 1 , 1 ) ;

		//　(2.2.*.2)　セル の	DcDrawオブジェクトの型を設定
		//	( CDcdTextbox とする)。
		{
			pCDcDrawCell = dynamic_castOu<CDcDrawCell>( 
				pCDcdGridCell->getIfDcDraw() ) ;
			if ( pCDcDrawCell == NULL )
			{
				pCDcDrawCell = OuNew<CDcDrawCell>( new CDcDrawCell ) ;
				pCDcdGridCell->setIfDcDraw( pCDcDrawCell ) ;
			}
		}
		//　(2.2.*.3)　セルの DcDrawオブジェクトに、属性を設定。
		{
			int idxRessyasyubetsu 
				= pCentDedRessya->getRessyasyubetsuIndex() ;
			tstring strText = pCentDedRessya->getBikou() ;
			*pCDcDrawCell = createCDcdRessyamei( 
				idxRessyasyubetsu );
			pCDcDrawCell->setLinesExtentX ( getBikouTextExtent().getX() ) ;
			pCDcDrawCell->setLinesExtentY ( getBikouTextExtent().getY() ) ;
			pCDcDrawCell->setText( strText );
		}
	}
}

CdColorProp CCellBuilder::getBackColor(int iXColumnNumber, int iEkiOrder, int idxRessyasyubetsu)
{
	int iBackColorPattern = m_pCentDedRessyaCont->getDia()->getBackPatternIndex();
	if (iBackColorPattern == 0 || m_bStandardOperationTimeFunction)
	{
		int iJikokuhyouMainBackColorIndex = m_pCentDedRessyaCont->getDia()->getMainBackColorIndex();
		CdColorProp aCdColorProp = m_pCDedRosenFileData->
			getCdDedDispProp().getJikokuhyouBackColor(iJikokuhyouMainBackColorIndex);
		return aCdColorProp;
	}
	else if (iBackColorPattern == 1)//種別色
	{

		const CentDedRessyasyubetsu* pCentDedRessyasyubetsu
			= m_pCDedRosenFileData->getCentDedRosen()->getCentDedRessyasyubetsuCont()
			->getMuPtr()->get(idxRessyasyubetsu);
		if (m_bDisplayParentSyubetsu && pCentDedRessyasyubetsu->getParentSyubetsuIndex() >= 0)
		{
			pCentDedRessyasyubetsu
				= m_pCDedRosenFileData->getCentDedRosen()->getCentDedRessyasyubetsuCont()
				->getMuPtr()->get(pCentDedRessyasyubetsu->getParentSyubetsuIndex());
		}
		CdColorProp aCdColorProp = pCentDedRessyasyubetsu->getJikokuhyouBackColor();
		return aCdColorProp;
	}
	else if (iBackColorPattern == 2)//縦縞
	{
		int iJikokuhyouBackColorIndex;
		if (iXColumnNumber % 2 == 0)
		{
			iJikokuhyouBackColorIndex = m_pCentDedRessyaCont->getDia()->getSubBackColorIndex();

		}
		else
		{
			iJikokuhyouBackColorIndex = m_pCentDedRessyaCont->getDia()->getMainBackColorIndex();
		}
		CdColorProp aCdColorProp = m_pCDedRosenFileData->
			getCdDedDispProp().getJikokuhyouBackColor(iJikokuhyouBackColorIndex);
		return aCdColorProp;

	}
	else if (iBackColorPattern == 3)//横縞
	{
		int iJikokuhyouBackColorIndex;
		if (iEkiOrder % 2 == 0)
		{
			iJikokuhyouBackColorIndex = m_pCentDedRessyaCont->getDia()->getSubBackColorIndex();

		}
		else
		{
			iJikokuhyouBackColorIndex = m_pCentDedRessyaCont->getDia()->getMainBackColorIndex();
		}
		CdColorProp aCdColorProp = m_pCDedRosenFileData->
			getCdDedDispProp().getJikokuhyouBackColor(iJikokuhyouBackColorIndex);
		return aCdColorProp;
	}
	else if (iBackColorPattern == 4)//市松模様
	{
		int iJikokuhyouBackColorIndex;
		if ((iEkiOrder % 2 == 0) == (iXColumnNumber % 2 == 0))
		{

			iJikokuhyouBackColorIndex = m_pCentDedRessyaCont->getDia()->getSubBackColorIndex();
		}
		else
		{
			iJikokuhyouBackColorIndex = m_pCentDedRessyaCont->getDia()->getMainBackColorIndex();

		}
		CdColorProp aCdColorProp = m_pCDedRosenFileData->
			getCdDedDispProp().getJikokuhyouBackColor(iJikokuhyouBackColorIndex);
		return aCdColorProp;
	}
	else
	{
		int iJikokuhyouMainBackColorIndex = m_pCentDedRessyaCont->getDia()->getMainBackColorIndex();
		CdColorProp aCdColorProp = m_pCDedRosenFileData->
			getCdDedDispProp().getJikokuhyouBackColor(iJikokuhyouMainBackColorIndex);
		return aCdColorProp;
	}
}

CdColorProp CCellBuilder::update02_02_02_StdOpeTimeFunc(
	bool isChakujikoku,
	int iKijunDiaIndex,
	int iEkiOrder,
	const CentDedRessya* pCentDedRessya,
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki
)
{
	//不適切形式をここではじき出す
//ALL
	bool SkipFor = false;

	//着時刻の場合、一つ前が運行なしなら、この時刻は意味を持たない。
	if (isChakujikoku &&
		!pCentDedRessya->isRunBetweenNextEki(iEkiOrder - 1))
	{
		return m_pCDedRosenFileData->getCdDedDispProp().getStdOpeTimeIllegalColor();
	}
	//発時刻の場合、一つ後が運行なしなら、この時刻は意味を持たない。
	else if (!isChakujikoku &&
		!pCentDedRessya->isRunBetweenNextEki(iEkiOrder))
	{
		return m_pCDedRosenFileData->getCdDedDispProp().getStdOpeTimeIllegalColor();
	}

	int iSearchEkiOrder = iEkiOrder;
	if (!isChakujikoku)
	{
		if (!pCentDedRessya->isRunBetweenNextEki(iSearchEkiOrder - 1))
		{
			//一つ前の駅が運行なしの場合は、この駅の着時刻は意味を持たないので、
			//運行なしを挟んで時刻がある駅を見つける。
			//見つかった駅とこの駅が、分岐・環状線設定で同グループではない場合は、illegalとする
			//同グループの場合は、iSearchEkiOrderを見つかった駅で上書きし、着時刻検査を行う。
			int iPrevEkiOrder = pCentDedRessya->getRunBetweenEkiBackward(iSearchEkiOrder);
			if (m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()
				->isSameBrunchLoopGroup(iPrevEkiOrder, iSearchEkiOrder, pCentDedRessya->getRessyahoukou()))
			{
				iSearchEkiOrder = iPrevEkiOrder;
			}
			else
			{
				return m_pCDedRosenFileData->getCdDedDispProp().getStdOpeTimeIllegalColor();
			}
		}

		const CentDedEkiJikoku aSearchEkiJikoku = pCentDedRessya->getCentDedEkiJikoku(iSearchEkiOrder);
		const CentDedEkiCont::CdDedEki aSearchEki = muCdDedEki->get(iSearchEkiOrder);

		if (aSearchEki.getChakujikokuHyouji())
		{
			if (aSearchEkiJikoku.getChakujikoku().isNull())
			{
				if (aSearchEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya)
				{
					//停車かつ、着時刻が無いなら
					//return CdColorProp( 255 , 0 , 0 ) ;//強い赤色
					//return CdColorProp( 160 , 160 , 160 ) ;
					return m_pCDedRosenFileData->getCdDedDispProp().getStdOpeTimeIllegalColor();
				}
				//else 前駅へ 通過
			}
			else
			{
				SkipFor = true;
				//評価 着時刻が存在するので、停車時間評価可能、forに入らないようにflagをOnに。
			}
		}
	}
	for (iSearchEkiOrder--; iSearchEkiOrder >= pCentDedRessya->getSihatsuEki() && !SkipFor; iSearchEkiOrder--)
	{
		//前提条件　この駅は停車または通過・一つ次の駅も停車または通過→発時刻が有効
		const CentDedEkiJikoku aSearchHatsuEkiJikoku = pCentDedRessya->getCentDedEkiJikoku(iSearchEkiOrder);
		const CentDedEkiCont::CdDedEki aSearchHatsuEki = muCdDedEki->get(iSearchEkiOrder);

		if (aSearchHatsuEki.getHatsujikokuHyouji())
		{
			//駅扱いは停車・通過、発時刻表示有
			if (aSearchHatsuEkiJikoku.getHatsujikoku().isNull())
			{
				if (aSearchHatsuEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya)
				{
					//return CdColorProp( 0 , 0 , 255 ) ;//強い青色
					//return CdColorProp( 160 , 160 , 160 ) ; //発時刻なしで、停車駅なのに、次駅が停車・通過なら
					return m_pCDedRosenFileData->getCdDedDispProp().getStdOpeTimeIllegalColor();
					//(通過駅の場合と、次駅が経由無しの場合、発時刻が無くても問題なし)
				}
				//通過の場合は着時刻検査へ
			}
			else
			{
				break; //評価可能なので、forを抜けて本体へ
			}
		}
		//ここまでは発時刻に着目

		//一つ前の駅が運行なしの場合は、この駅の着時刻は意味を持たないので、
		//運行なしを挟んで時刻がある駅を見つける。
		//見つかった駅とこの駅が、分岐・環状線設定で同グループではない場合は、illegalとする
		//同グループの場合は、iSearchEkiOrderを見つかった駅で上書きし、着時刻検査を行う。
		if (!pCentDedRessya->isRunBetweenNextEki(iSearchEkiOrder-1))
		{
			int iPrevEkiOrder = pCentDedRessya->getRunBetweenEkiBackward(iSearchEkiOrder);
			if (m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()
				->isSameBrunchLoopGroup(iPrevEkiOrder, iSearchEkiOrder, pCentDedRessya->getRessyahoukou()))
			{
				iSearchEkiOrder = iPrevEkiOrder;
			}
			else
			{
				return m_pCDedRosenFileData->getCdDedDispProp().getStdOpeTimeIllegalColor();
			}
		}

		const CentDedEkiJikoku aSearchChakuEkiJikoku = pCentDedRessya->getCentDedEkiJikoku(iSearchEkiOrder);
		const CentDedEkiCont::CdDedEki aSearchChakuEki = muCdDedEki->get(iSearchEkiOrder);
		if (aSearchChakuEki.getChakujikokuHyouji())
		{
			//着時刻表示有
			if (aSearchChakuEkiJikoku.getChakujikoku().isNull())
			{
				if (aSearchChakuEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya)
				{
					//return CdColorProp( 0 , 0 , 0 ) ; //黒
					//return CdColorProp( 160 , 160 , 160 ) ; //着時刻無しかつ停車なら
					return m_pCDedRosenFileData->getCdDedDispProp().getStdOpeTimeIllegalColor();
				}
			}
			else
			{
				break; //評価可能なので、forを抜けて本体へ
			}
		}
	}
	//ここまで事前確認

	//まずは基準側列車コンテナまで定義
	const CentDedRessyaCont* pKijunCentDedRessyaCont =
		m_pCDedRosenFileData->getCentDedRosen()->getCentDedDiaCont()
		->getMuPtr()->get( iKijunDiaIndex )->getCentDedRessyaCont( pCentDedRessya->getRessyahoukou() ) ; 
	//対象列車種別を取得(引数から外した)
	int idxRessyasyubetsu = pCentDedRessya->getRessyasyubetsuIndex() ;
	//対象列車と同じ種別を基準側で探索
	for(int iKijunRessyaIndex = 0 ; 
		iKijunRessyaIndex < pKijunCentDedRessyaCont->size()/*コンテナ内列車数*/ ; 
		iKijunRessyaIndex++ )
	{
		//対象列車と同じ種別かどうか確認
		if( pKijunCentDedRessyaCont->getMuPtr()->get( iKijunRessyaIndex )->getRessyasyubetsuIndex() != idxRessyasyubetsu )
		{
			continue ; //次列車に移行
		}
	//同じ種別
		iSearchEkiOrder = iEkiOrder;
		const CentDedEkiJikoku aEkiJikoku = pCentDedRessya->getCentDedEkiJikoku(iSearchEkiOrder);
		//基準側列車コンテナ取得
		const CentDedRessya* pCentDedRessyaStandard = pKijunCentDedRessyaCont->getMuPtr()->get( iKijunRessyaIndex ) ;
		const CentDedEkiJikoku aStandardEkiJikoku = pCentDedRessyaStandard->getCentDedEkiJikoku(iSearchEkiOrder);
		//まずは当駅でのふるい分け
	//ALL
		if(aEkiJikoku.getEkiatsukai() !=
			aStandardEkiJikoku.getEkiatsukai()  )
		{
			//駅扱いが一致しない場合は次列車
			continue ;
		}
	//駅扱いは一致している
		if( isChakujikoku && aStandardEkiJikoku.getChakujikoku().isNull() )
		{ 
			//評価対象が着時刻なのに、基準側にはないので、次列車
			continue ;
		}
	//評価対象が発時刻の場合と、着時刻なら基準側にも存在している
		if( !isChakujikoku && aStandardEkiJikoku.getHatsujikoku().isNull() )
		{
			//評価対象が発時刻なのに、基準側にはないので、次列車
			continue ;
		}
	//着時刻の場合、評価対象の一つ前が運行なしなら、この時刻は意味を持たないので、次列車へ
		if (isChakujikoku &&
			!pCentDedRessyaStandard->isRunBetweenNextEki(iSearchEkiOrder - 1))
		{
			continue;
		}
	//発時刻の場合、評価対象の一つ後が運行なしなら、この時刻は意味を持たないので、次列車へ
		if (!isChakujikoku && 
			!pCentDedRessyaStandard->isRunBetweenNextEki(iSearchEkiOrder))
		{
			continue;
		}
	//評価対象と同じポジションの時刻が存在して、有効。

		if (!isChakujikoku)
		{
			if (pCentDedRessya->isRunBetweenNextEki(iSearchEkiOrder - 1) !=
				pCentDedRessyaStandard->isRunBetweenNextEki(iSearchEkiOrder - 1))
			{
				//前駅が運行なしか否かが異なる場合は次列車へ
				continue;
			}

			if (!pCentDedRessya->isRunBetweenNextEki(iSearchEkiOrder - 1))
			{
				//一つ前の駅が運行なしの場合は、この駅の着時刻は意味を持たないので、
				//運行なしを挟んで時刻がある駅を見つける。
				//見つかった駅とこの駅が、分岐・環状線設定で同グループではない場合は、illegalとする
				//同グループの場合は、iSearchEkiOrderを見つかった駅で上書きし、着時刻検査を行う。
				int iPrevEkiOrder = pCentDedRessya->getRunBetweenEkiBackward(iSearchEkiOrder);
				int iPrevEkiOrderStandard = pCentDedRessyaStandard->getRunBetweenEkiBackward(iSearchEkiOrder);
				if (iPrevEkiOrder != iPrevEkiOrderStandard)
				{
					//運行なしの連続が異なっているので次列車へ
					continue;
				}

				//先のチェックで、iPrevEkiOrderがiSearchEkiOrderと同一駅扱いなのは確認済みなので、iSearchEkiOrderを上書きし、着時刻チェックへ。
				iSearchEkiOrder = iPrevEkiOrder;
			}

			const CentDedEkiJikoku aSearchEkiJikoku = pCentDedRessya->getCentDedEkiJikoku(iSearchEkiOrder);
			const CentDedEkiJikoku aStandardSearchEkiJikoku = pCentDedRessyaStandard->getCentDedEkiJikoku(iSearchEkiOrder);
			const CentDedEkiCont::CdDedEki aSearchEki = muCdDedEki->get(iSearchEkiOrder);

			if (aSearchEki.getChakujikokuHyouji())
			{
				if (aSearchEkiJikoku.getEkiatsukai() ==
					aStandardSearchEkiJikoku.getEkiatsukai() &&
					aSearchEkiJikoku.getChakujikoku().isNull() ==
					aStandardSearchEkiJikoku.getChakujikoku().isNull())
				{
					if (!aSearchEkiJikoku.getChakujikoku().isNull())
						//一致し、それが有りなら
					{
						//評価
						int iElapsedTime = aEkiJikoku.getHatsujikoku().subJikoku(
							aSearchEkiJikoku.getChakujikoku());
						int iElapsedTimeStandard = aStandardEkiJikoku.getHatsujikoku().subJikoku(
							aStandardSearchEkiJikoku.getChakujikoku());

						if (iElapsedTime < iElapsedTimeStandard)//比較
						{
							//return CdColorProp(255, 223, 223); //赤色
							return m_pCDedRosenFileData->getCdDedDispProp().getStdOpeTimeLowerColor();

						}
						else if (iElapsedTime > iElapsedTimeStandard)
						{
							//return CdColorProp(223, 255, 255); //水色
							return m_pCDedRosenFileData->getCdDedDispProp().getStdOpeTimeHigherColor();

						}
						else
						{
							//return CdColorProp( 128 , 255 , 128 ) ; //緑色・確認のための暫定配置
							return CdColorProp(255, 255, 255); //白色;
							/*return m_pCDedRosenFileData->getCdDedDispProp().getJikokuhyouBackColor(
								m_pCentDedRessyaCont->getDia()->getMainBackColorIndex());*/

						}
					}
					//else※1 着時刻有無が無しで一致の場合前駅へ、不適切ケースは洗い出し済み。
				}
				else
				{
					//駅扱い不一致または着時刻の有無が不一致の場合は、次列車へ
					continue;
				}
			}
		}
		for (iSearchEkiOrder--; iSearchEkiOrder >= pCentDedRessya->getSihatsuEki() && !SkipFor; iSearchEkiOrder--)
		{
			//前提条件　この駅は停車または通過・一つ次の駅も停車または通過→発時刻が有効
			const CentDedEkiJikoku aSearchHatsuEkiJikoku = pCentDedRessya->getCentDedEkiJikoku(iSearchEkiOrder);
			const CentDedEkiJikoku aStandardSearchHatsuEkiJikoku = pCentDedRessyaStandard->getCentDedEkiJikoku(iSearchEkiOrder);
			const CentDedEkiCont::CdDedEki aSearchHatsuEki = muCdDedEki->get(iSearchEkiOrder);

			if (aSearchHatsuEkiJikoku.getEkiatsukai() !=
				aStandardSearchHatsuEkiJikoku.getEkiatsukai())
			{
				break; //駅扱いが一致しなかったので次列車へ
			}

			if (aSearchHatsuEki.getHatsujikokuHyouji())
			{
				//駅扱いは停車・通過で一致、発時刻表示有
				if (aSearchHatsuEkiJikoku.getHatsujikoku().isNull() !=
					aStandardSearchHatsuEkiJikoku.getHatsujikoku().isNull())
				{
					break; //時刻有無が不一致の場合は、次列車へ
				}
				//駅扱いは停車・通過で一致、発時刻の有無は一致(停車の場合は必ず時刻あり)
				if (!aSearchHatsuEkiJikoku.getHatsujikoku().isNull())
				{
					//発時刻が存在するなら
					int iElapsedTime;
					int iElapsedTimeStandard;
					if (isChakujikoku)
					{
						iElapsedTime = aEkiJikoku.getChakujikoku().subJikoku(aSearchHatsuEkiJikoku.getHatsujikoku());
						iElapsedTimeStandard = aStandardEkiJikoku.getChakujikoku().subJikoku(aStandardSearchHatsuEkiJikoku.getHatsujikoku());
					}
					else
					{
						iElapsedTime = aEkiJikoku.getHatsujikoku().subJikoku(aSearchHatsuEkiJikoku.getHatsujikoku());
						iElapsedTimeStandard = aStandardEkiJikoku.getHatsujikoku().subJikoku(aStandardSearchHatsuEkiJikoku.getHatsujikoku());
					}
					if (iElapsedTime < iElapsedTimeStandard)//比較
					{
						//return CdColorProp(255, 223, 223); //赤色
						return m_pCDedRosenFileData->getCdDedDispProp().getStdOpeTimeLowerColor();

					}
					else if (iElapsedTime > iElapsedTimeStandard)
					{
						//return CdColorProp(223, 255, 255); //水色
						return m_pCDedRosenFileData->getCdDedDispProp().getStdOpeTimeHigherColor();

					}
					else
					{
						//return CdColorProp( 128 , 255 , 128 ) ; //緑色・確認のための暫定配置
						return CdColorProp(255, 255, 255); //白色
						//return m_pCDedRosenFileData->getCdDedDispProp().getJikokuhyouBackColor(
						//	m_pCentDedRessyaCont->getDia()->getMainBackColorIndex());
					}
				}
				//else 通過&時刻なしの場合は着時刻検査へ。ここで不適切ケースになるものは、事前洗い出し済み
			}
			//ここまでは発時刻に着目

			//一つ前の駅が運行なしの場合は、この駅の着時刻は意味を持たないので、
			//運行なしを挟んで時刻がある駅を見つける。
			//見つかった駅とこの駅が、分岐・環状線設定で同グループではない場合は、illegalとする
			//同グループの場合は、iSearchEkiOrderを見つかった駅で上書きし、着時刻検査を行う。
			if (!pCentDedRessya->isRunBetweenNextEki(iSearchEkiOrder - 1))
			{
				int iPrevEkiOrder = pCentDedRessya->getRunBetweenEkiBackward(iSearchEkiOrder);
				int iPrevEkiOrderStandard = pCentDedRessyaStandard->getRunBetweenEkiBackward(iSearchEkiOrder);
				if (iPrevEkiOrder != iPrevEkiOrderStandard)
				{
					//運行なしの連続が異なっているので次列車へ
					break;
				}
				iSearchEkiOrder = iPrevEkiOrder;
			}

			const CentDedEkiJikoku aSearchChakuEkiJikoku = pCentDedRessya->getCentDedEkiJikoku(iSearchEkiOrder);
			const CentDedEkiJikoku aStandardSearchChakuEkiJikoku = pCentDedRessyaStandard->getCentDedEkiJikoku(iSearchEkiOrder);
			const CentDedEkiCont::CdDedEki aSearchChakuEki = muCdDedEki->get(iSearchEkiOrder);
			//発側と着側は、同一駅もしくは同一駅扱いなので、駅扱いは同じなので、不要ではあるが一応チェックする。
			if (aSearchChakuEkiJikoku.getEkiatsukai() !=
				aStandardSearchChakuEkiJikoku.getEkiatsukai())
			{
				break; //駅扱いが一致しなかったので次列車へ
			}

			if (aSearchChakuEki.getChakujikokuHyouji())
			{

				//駅扱いは停車・通過で一致、着時刻表示有
				if (aSearchChakuEkiJikoku.getChakujikoku().isNull() !=
					aStandardSearchChakuEkiJikoku.getChakujikoku().isNull())
				{
					break; //時刻有無が不一致の場合は、次列車へ
				}
				//駅扱いは停車・通過で一致、着時刻の有無が一致(停車の場合は必ず時刻あり)
				if (!aSearchChakuEkiJikoku.getChakujikoku().isNull())
				{
					//着時刻が存在するなら
					int iElapsedTime;
					int iElapsedTimeStandard;
					if (isChakujikoku)
					{
						iElapsedTime = aEkiJikoku.getChakujikoku().subJikoku(aSearchChakuEkiJikoku.getChakujikoku());
						iElapsedTimeStandard = aStandardEkiJikoku.getChakujikoku().subJikoku(aStandardSearchChakuEkiJikoku.getChakujikoku());
					}
					else
					{
						iElapsedTime = aEkiJikoku.getHatsujikoku().subJikoku(aSearchChakuEkiJikoku.getChakujikoku());
						iElapsedTimeStandard = aStandardEkiJikoku.getHatsujikoku().subJikoku(aStandardSearchChakuEkiJikoku.getChakujikoku());
					}
					if (iElapsedTime < iElapsedTimeStandard)//比較
					{
						//return CdColorProp(255, 223, 223); //赤色 
						return m_pCDedRosenFileData->getCdDedDispProp().getStdOpeTimeLowerColor();
					}
					else if (iElapsedTime > iElapsedTimeStandard)
					{
						//return CdColorProp(223, 255, 255); //水色
						return m_pCDedRosenFileData->getCdDedDispProp().getStdOpeTimeHigherColor();
					}
					else
					{
						//return CdColorProp( 128 , 255 , 128 ) ; //緑色・確認のための暫定配置
						return CdColorProp(255, 255, 255); //白色
						//return m_pCDedRosenFileData->getCdDedDispProp().getJikokuhyouBackColor(
						//	m_pCentDedRessyaCont->getDia()->getMainBackColorIndex());
					}
				}
				//通過・着時刻なしの場合は、前駅へ
			}
		}
	}
	//不適切に当てはまらず、なおかつ見つからなかった場合
	//return CdColorProp( 255 , 255 , 127 ) ; //黄色
	return m_pCDedRosenFileData->getCdDedDispProp().getStdOpeTimeUndefColor();
}

	// ********************************
	//	コンストラクタ
	// ********************************
CCellBuilder::CCellBuilder( 
	const CDedRosenFileData* pCDedRosenFileData ,
	const CentDedRessyaCont* pCentDedRessyaCont,
	bool bDisplayTsuukaEkiJikoku ,
	bool bDisplayAllJikoku ,
	//add_by_d_mania
	bool bDisplaySecondEkiJikoku ,
	bool bDisplayColonEkiJikoku,
	bool bStandardOperationTimeFunction ,
	bool bDisplayShihatsuShuchakuEkimei,
	bool bDisplayParentSyubetsu,
	bool bDisplayTsuukaFontPerSyubetsu,
	int iEnableOperation) :
	m_pCentDedRessyaCont( pCentDedRessyaCont ) ,
	m_pCDedRosenFileData( pCDedRosenFileData ) , 
	m_CdXColSpecCont( pCentDedRessyaCont ,false) ,
	m_bDisplayTsuukaEkiJikoku( bDisplayTsuukaEkiJikoku ) ,
	m_bDisplaySecondEkiJikoku( bDisplaySecondEkiJikoku ) ,
	m_bDisplayColonEkiJikoku(bDisplayColonEkiJikoku),
	m_bStandardOperationTimeFunction( bStandardOperationTimeFunction ),
	m_bDisplayShihatsuShuchakuEkimei(bDisplayShihatsuShuchakuEkimei),
	m_bDisplayParentSyubetsu(bDisplayParentSyubetsu),
	m_bDisplayTsuukaFontPerSyubetsu(bDisplayTsuukaFontPerSyubetsu),
	m_iEnableOperation(iEnableOperation)
{
	CdDedDispProp	aCdDedDispProp = m_pCDedRosenFileData->getCdDedDispProp();
	m_bDisplayRessyamei = aCdDedDispProp.getDisplayRessyamei();
	m_bDisplayOuterTerminalShihatsu = aCdDedDispProp.getDisplayOuterTerminalShihatsu(pCentDedRessyaCont->getRessyahoukou());
	m_bDisplayOuterTerminalShuchaku = aCdDedDispProp.getDisplayOuterTerminalShuchaku(pCentDedRessyaCont->getRessyahoukou());
	m_iSecondRoundChaku = aCdDedDispProp.getSecondRoundChaku();
	m_iSecondRoundHatsu = aCdDedDispProp.getSecondRoundHatsu();
	m_bDisplay2400 = aCdDedDispProp.getDisplay2400();
	m_iOperationNumberRows = aCdDedDispProp.getOperationNumberRows();
	m_bDisplayInOutLinkCode = aCdDedDispProp.getDisplayInOutLinkCode();


	m_CdYColSpecCont = CdYColSpecCont(
		pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont(),
		pCentDedRessyaCont->getRessyahoukou(),
		bDisplayAllJikoku, false,
		bDisplayShihatsuShuchakuEkimei,
		m_bDisplayRessyamei, iEnableOperation,
		m_bDisplayOuterTerminalShihatsu, m_bDisplayOuterTerminalShuchaku,
		m_iOperationNumberRows, m_bDisplayInOutLinkCode);
}

	// ********************************
	//@name	CCellBuilder-操作
	// ********************************
void CCellBuilder::update( 
		CWndJikokuhyou* pCWndJikokuhyou ) 
{

	//　(1)　グリッドのうち、列車情報以外のすべての部分を設定します。
	update01_updateWithoutRessya(
		pCWndJikokuhyou ) ;

	//　(2)　列車情報を設定します。
	updateAllRessya( 
		pCWndJikokuhyou ) ;
	
	// --------------------------------
	pCWndJikokuhyou->InvalidateGrid() ;
}

void CCellBuilder::updateAllRessya( 
		CWndJikokuhyou* pCWndJikokuhyou ) 
{
	//　(2.1)　X列の数を設定します。CdXColSpecCont 
	//	で指定された列数とします。
	CDcdGrid*	pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid() ;
	pCDcdGrid->setXColumnCount( m_CdXColSpecCont.size() ) ;

	//　(2.2)　X列(ColumnType_Ressya )に、列車情報を設定
	int iRessyaSize = m_pCentDedRessyaCont->size();
#pragma omp parallel for schedule(guided)
	for ( int iRessyaIndex = 0 ; iRessyaIndex < iRessyaSize;
		iRessyaIndex ++ )
	{
		int iXColumnNumber = m_CdXColSpecCont.ColumnNumberFromSpec(
			CdXColSpec( 
				CdXColSpec::ColumnType_Ressya ,
				iRessyaIndex ) ) ;
		if ( iXColumnNumber >= 0 )
		{
			update02_02_updateRessya( 
				iXColumnNumber , 
				m_pCentDedRessyaCont->getMuPtr()->get( iRessyaIndex ) ,
				pCWndJikokuhyou ) ;
		}
	}

	//　(2.3)　X列(ColumnType_NewRessya )に、列車情報を設定。
	//	X列(ColumnType_Ressya )と同様。
	{
		int iXColumnNumber = m_CdXColSpecCont.ColumnNumberFromSpec(
			CdXColSpec( 
				CdXColSpec::ColumnType_NewRessya  ) ) ;
		if ( iXColumnNumber >= 0 )
		{
			CentDedRessya aRessya( m_pCentDedRessyaCont->createNullRessya() ) ;

			update02_02_updateRessya( 
				iXColumnNumber , 
				&aRessya ,
				pCWndJikokuhyou ) ;
		}
	}
}


void CCellBuilder::replaceRessya( 
		int iDstRessyaIndex , 
		int iDstDelCount , 
		int iInsertCount ,
		CWndJikokuhyou* pCWndJikokuhyou ) 
{
	CDcdGrid*	pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid() ;

	// --------------------------------
	//	減少分の要素の削除
	// --------------------------------
	int iGensyouSize = iDstDelCount - iInsertCount ;
	if ( iGensyouSize > 0 )
	{
		int iXColumnNumberToDelete = m_CdXColSpecCont.ColumnNumberFromSpec( 
			CdXColSpec( 
				CdXColSpec::ColumnType_Ressya ,
				iDstRessyaIndex ) ) ;
		if ( iXColumnNumberToDelete == -1 )
		{
			iXColumnNumberToDelete = m_CdXColSpecCont.ColumnNumberFromSpec( 
			CdXColSpec( 
				CdXColSpec::ColumnType_NewRessya ) ) ;
		}
		for ( int cnt = 0 ; cnt < iGensyouSize ; cnt ++ )
		{
			pCWndJikokuhyou->getCXDcdGrid()->eraseXColumn( 
				iXColumnNumberToDelete ) ;
		}
	}
	// --------------------------------
	//	増加分の要素の追加
	// --------------------------------
	int iZoukaSize = iInsertCount - iDstDelCount ;
	if ( iZoukaSize > 0 )
	{
		int iXColumnNumberToInsert = m_CdXColSpecCont.ColumnNumberFromSpec( 
			CdXColSpec( 
				CdXColSpec::ColumnType_Ressya ,
				iDstRessyaIndex + iDstDelCount ) ) ;
		for ( int cnt = 0 ; cnt < iZoukaSize ; cnt ++ ){
			pCWndJikokuhyou->getCXDcdGrid()->insertXColumn( 
				iXColumnNumberToInsert , 
				true ) ; 
		}
	}
	// --------------------------------
	//	要素の更新
	// --------------------------------
	{					
		for ( int cnt = 0 ; cnt < iInsertCount ; cnt ++ )
		{
			int iXColumnNumber = m_CdXColSpecCont.ColumnNumberFromSpec( 
				CdXColSpec( 
					CdXColSpec::ColumnType_Ressya ,
					iDstRessyaIndex + cnt ) ) ;

			update02_02_updateRessya( 
				iXColumnNumber , 
				m_pCentDedRessyaCont->getMuPtr()->get( iDstRessyaIndex + cnt ) ,
				pCWndJikokuhyou ) ;
		}
	}
	// --------------------------------
	//	グリッドの更新
	// --------------------------------
	CdDcdZone	zoneX ;
	if ( iInsertCount > 0 )
	{
		int iXColumnNumber1 = m_CdXColSpecCont.ColumnNumberFromSpec( 
			CdXColSpec( 
				CdXColSpec::ColumnType_Ressya ,
				iDstRessyaIndex ) ) ;
		int iXColumnNumber2 = m_CdXColSpecCont.ColumnNumberFromSpec( 
			CdXColSpec( 
				CdXColSpec::ColumnType_Ressya ,
				iDstRessyaIndex + iInsertCount - 1 ) )  ;
		CdDcdZone	zoneX1 = pCWndJikokuhyou->getXColumnZone( iXColumnNumber1 ) ;
		CdDcdZone	zoneX2 = pCWndJikokuhyou->getXColumnZone( iXColumnNumber2 ) ;
		zoneX.setBeginEndPos( zoneX1.getPos() , zoneX2.getEndPos() ) ; 

	}
	CdDcdZone	zoneY ;
	{
		CdDcdZone	zoneY1 = pCWndJikokuhyou->getYColumnBorderZone( 0 ) ;
		CdDcdZone	zoneY2 = pCWndJikokuhyou->getYColumnBorderZone( pCDcdGrid->getYColumnCount() - 1 ) ;
		zoneY.setBeginEndPos( zoneY1.getPos() , zoneY2.getEndPos() ) ;
		//zoneRessya = グリッド上の列車の領域
	}
	CdDcdZoneXy	zonexyInvalidate( zoneX , zoneY ) ;
	// --------------------------------
	pCWndJikokuhyou->InvalidateRect( 
		&CConverter_WinGdi().RECTOf( zonexyInvalidate ) , TRUE ) ;
}


void CCellBuilder::replaceRessyaAndAllOperationNumber(
	int iDstRessyaIndex,
	int iDstDelCount,
	int iInsertCount,
	CWndJikokuhyou* pCWndJikokuhyou)
{
	replaceRessya(
		iDstRessyaIndex,
		iDstDelCount,
		iInsertCount,
		pCWndJikokuhyou);


	updateAllOperationNumber(
		pCWndJikokuhyou);

	//	//　(2.1)　X列の数を設定します。CdXColSpecCont 
	//	//	で指定された列数とします。
	//CDcdGrid*	pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	//pCDcdGrid->setXColumnCount(m_CdXColSpecCont.size());

	////　(2.2)　X列(ColumnType_Ressya )に、列車情報を設定
	//for (int iRessyaIndex = 0; iRessyaIndex < m_pCentDedRessyaCont->size();
	//	iRessyaIndex++)
	//{
	//	int iXColumnNumber = m_CdXColSpecCont.ColumnNumberFromSpec(
	//		CdXColSpec(
	//			CdXColSpec::ColumnType_Ressya,
	//			iRessyaIndex));
	//	if (iXColumnNumber >= 0)
	//	{
	//		CDcdTargetGetDC	aCDcdTarget(NULL);
	//		// --------------------------------
	//		//	(2.2.2.12)セル(ColumnType_Ressya, ColumnType_OperationNumber)
	//		// --------------------------------
	//		update02_02_02_12_setRessya_OperationNumber(
	//			iXColumnNumber,
	//			m_pCentDedRessyaCont->getMuPtr()->get(iRessyaIndex),
	//			pCWndJikokuhyou);

	//		// ================================
	//		//	X列を再描画領域とします。
	//		// ================================
	//		CdYColSpec aCdYColSpec(
	//			CdYColSpec::ColumnType_OperationNumber);
	//		int iYColumnNumber = m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec, false);
	//		if (iYColumnNumber >= 0)
	//		{
	//			CdDcdZoneXy	aCdDcdZoneXy;
	//			//X列の範囲
	//			{
	//				CdDcdZone	zoneXColumnZone = pCDcdGrid->getXColumnZone(
	//					&aCDcdTarget,
	//					iXColumnNumber);
	//				CdDcdZone	zoneXColumnBorderZone = pCDcdGrid->getXColumnBorderZone(
	//					&aCDcdTarget,
	//					iXColumnNumber);

	//				aCdDcdZoneXy.setX(
	//					zoneXColumnZone.ZoneOr(zoneXColumnBorderZone));
	//			}
	//			//Y列の範囲
	//			{
	//				CdDcdZone	zoneYColumn = pCDcdGrid->getYColumnZone(
	//					&aCDcdTarget,
	//					iYColumnNumber);
	//				aCdDcdZoneXy.setY(zoneYColumn);
	//			}
	//			CConverter_WinGdi	aConv;
	//			pCWndJikokuhyou->InvalidateRect(
	//				&aConv.RECTOf(aCdDcdZoneXy));
	//		}
	//	}
	//}
}

void CCellBuilder::updateAllOperationNumber(
	CWndJikokuhyou* pCWndJikokuhyou)
{
	//　(2.1)　X列の数を設定します。CdXColSpecCont 
	//	で指定された列数とします。
	CDcdGrid*	pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	pCDcdGrid->setXColumnCount(m_CdXColSpecCont.size());

	//　(2.2)　X列(ColumnType_Ressya )に、列車情報を設定
	int iRessyaSize = m_pCentDedRessyaCont->size();
#pragma omp parallel for schedule(guided)
	for (int iRessyaIndex = 0; iRessyaIndex < iRessyaSize;
		iRessyaIndex++)
	{
		int iXColumnNumber = m_CdXColSpecCont.ColumnNumberFromSpec(
			CdXColSpec(
				CdXColSpec::ColumnType_Ressya,
				iRessyaIndex));
		int iYColumnNumber = m_CdYColSpecCont.ColumnNumberFromSpec(
			CdYColSpec(CdYColSpec::ColumnType_OperationNumber),false);
		if (iXColumnNumber >= 0 && iYColumnNumber >= 0)
		{
			CDcdTargetGetDC	aCDcdTarget(NULL);
			// --------------------------------
			//	(2.2.2.12)セル(ColumnType_Ressya, ColumnType_OperationNumber)
			// --------------------------------
			update02_02_02_12_setRessya_OperationNumber(
				iXColumnNumber,
				iYColumnNumber,
				m_pCentDedRessyaCont->getMuPtr()->get(iRessyaIndex),
				pCWndJikokuhyou);

			// ================================
			//	X列を再描画領域とします。
			// ================================
			CdDcdZoneXy	aCdDcdZoneXy;
			//X列の範囲
			{
				CdDcdZone	zoneXColumnZone = pCDcdGrid->getXColumnZone(
					&aCDcdTarget,
					iXColumnNumber);
				CdDcdZone	zoneXColumnBorderZone = pCDcdGrid->getXColumnBorderZone(
					&aCDcdTarget,
					iXColumnNumber);

				aCdDcdZoneXy.setX(
					zoneXColumnZone.ZoneOr(zoneXColumnBorderZone));
			}
			//Y列の範囲
			{
				CdDcdZone	zoneYColumn = pCDcdGrid->getYColumnZone(
					&aCDcdTarget,
					iYColumnNumber);
				aCdDcdZoneXy.setY(zoneYColumn);
			}
			CConverter_WinGdi	aConv;
			pCWndJikokuhyou->InvalidateRect(
				&aConv.RECTOf(aCdDcdZoneXy));
		}
	}
}

} //namespace ViewJikokuhyou
} //namespace WndJikokuhyou

