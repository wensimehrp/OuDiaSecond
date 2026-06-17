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
//	ViewJikokuhyou\WndJikokuhyou\CCellBuilderCustomize.cpp
//	$Id: CCellBuilderCustomize.cpp 366 2016-08-18 20:26:22Z okm $
// ****************************************************************
*/
/** @file */
#include "stdafx.h"
//#include "..\..\StdAfx.h"
#include "CCellBuilderCustomize.h"
#include "..\..\resource.h"
#include "DcDraw\DcDraw.h"
#include "NsOu/dynamic_castOu.h"
#include "..\..\entDed\entDed.h"
#include "str\stringSplit.h"
#include "MfcUtil/MfcUtil.h"
#include <NsOu\OuNew.h>
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

CdDrawTextProp	CCellBuilderCustomize::getCdDrawTextPropMenutext()const
{ 
	CdDedDispProp aCdDedDispProp = m_pCDedRosenFileData->getCdDedDispProp() ;

	CConverter_WinGdi	aConv ;
	return CdDrawTextProp( 
		aCdDedDispProp.getJikokuhyouFont(0) ,
		aConv.CdColorPropOfSysColor( COLOR_MENUTEXT ) ) ;
}

CdDrawTextProp	CCellBuilderCustomize::getCdDrawTextPropStandard()const
{ 
	CdDedDispProp aCdDedDispProp = m_pCDedRosenFileData->getCdDedDispProp() ;

	return CdDrawTextProp( 
		aCdDedDispProp.getJikokuhyouFont(0) ,
		CdColorProp( 0 , 0 , 0 ) ) ;
}

CdDrawTextProp	CCellBuilderCustomize::getCdDrawTextPropOperation()const
{
	CdDedDispProp aCdDedDispProp = m_pCDedRosenFileData->getCdDedDispProp();

	return CdDrawTextProp(
		aCdDedDispProp.getJikokuhyouFont(0),
		CdColorProp(0, 0, 0),
		CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
}

CdDrawTextProp	CCellBuilderCustomize::getCdDrawTextPropTsuuka()const
{ 
	CdDedDispProp aCdDedDispProp = m_pCDedRosenFileData->getCdDedDispProp() ;

	return CdDrawTextProp( 
		aCdDedDispProp.getJikokuhyouFont(0) ,
		CdColorProp( 128 , 128 , 128 ) ,
		CdDrawTextFormat( CdDrawTextFormat::H_CENTER ) ) ;
}

//edit_by_d_mania
const CdDedJikoku::CConv
CCellBuilderCustomize::getCdDedJikokuConv()const 
{
	//if( m_bDisplaySecondEkiJikoku )
	//{
	//	if (m_bDisplayColonEkiJikoku)
	//	{
	//		static CdDedJikoku::CConv aConv(
	//			false,		//	コロン有
	//											// 時が 00 から 09 の場合、10の位の "0" をスペースにします。
	//			CdDedJikoku::CConv::EHour_ZeroToSpace,
	//			CdDedJikoku::CConv::ESecond_Output 	// 秒を表示します
	//		);
	//		return aConv;
	//	}
	//	else
	//	{
	//		static CdDedJikoku::CConv aConv(
	//			true,		//	コロン無
	//											// 時が 00 から 09 の場合、10の位の "0" をスペースにします。
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
	// --------------------------------
	//@name 描画処理に使用する ブラシ属性
	// --------------------------------

CdBrushProp CCellBuilderCustomize::getCdBrushPropMenutext()const
{
	CConverter_WinGdi	aConv ;
	return CdBrushProp( aConv.CdColorPropOfSysColor( COLOR_MENU ) ) ;
}

CdBrushProp	CCellBuilderCustomize::getCdBrushPropStandard()const
{
	return CdBrushProp( CdColorProp( 255 , 255 , 255 ) ) ;
}

	// --------------------------------
	//@name 描画処理に使用する DcDrawオブジェクトのプロトタイプ
	// --------------------------------

CDcdTextbox CCellBuilderCustomize::createCDcdXColumn0()const
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

CDcdTextboxV3 CCellBuilderCustomize::createCDcdXColumn0V()const
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


CDcdTextbox CCellBuilderCustomize::createCDcdEkimei()const
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


CDcdTextbox CCellBuilderCustomize::createCDcdHatsuchaku()const
{
	tstring strExtent;
	//if (m_bDisplayAllTrack) 
	//{
	//	strExtent = MfcUtil::LoadCString(IDS_WORD_Track);
	//}
	//else 
	//{
		strExtent = MfcUtil::LoadCString( IDS_WORD_Chaku );
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

CDcdTextbox CCellBuilderCustomize::createCDcdRessyabangou(
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

CDcdTextboxV3 CCellBuilderCustomize::createCDcdRessyamei(
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

CDcdTextbox CCellBuilderCustomize::createCDcdEkijikoku(
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
void CCellBuilderCustomize::update01_updateWithoutRessya(
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
		//update01_03_02_10_setEkimei_Operation_Shihatsu(
		//	pCWndJikokuhyou);

		// --------------------------------
		//	(1.3.2.10)セル(ColumnType_Ekimei, ColumnType_Operation_Shuchaku)
		// --------------------------------
		update01_03_02_14_setShuchakuEkimei(
			pCWndJikokuhyou);

		// --------------------------------
		//	(1.3.2.10)セル(ColumnType_Ekimei, ColumnType_Operation_Shuchaku)
		// --------------------------------
		//update01_03_02_11_setEkimei_Operation_Shuchaku(
		//	pCWndJikokuhyou);

		// --------------------------------
		//	(1.3.2.15)セル(ColumnType_Ekimei, ColumnType_Outer_Shihatsu)
		// --------------------------------
		//update01_03_02_15_setEkimei_OuterTerminal_Shihatsu(
		//	pCWndJikokuhyou);
		
		// --------------------------------
		//	セル(ColumnType_Ekimei,ColumnType_Ekijikoku_Chaku)
		//	セル(ColumnType_Ekimei,ColumnType_Track)
		//	セル(ColumnType_Ekimei,ColumnType_Ekijikoku_Hatsu)
		// --------------------------------

		update01_03_02_27_setEkimei_PrevRessyabangou(
			pCWndJikokuhyou);
		update01_03_02_28_setEkimei_PrevOperationNumber(
			pCWndJikokuhyou);
		update01_03_02_29_setEkimei_PrevRessyasyubetsu(
			pCWndJikokuhyou);
		update01_03_02_30_setEkimei_PrevRessyamei(
			pCWndJikokuhyou);
		update01_03_02_31_setEkimei_PrevGousuu(
			pCWndJikokuhyou);
		update01_03_02_32_setEkimei_PrevGou(
			pCWndJikokuhyou);

		update01_03_02_25_setEkimei_OuterSihatsu(
			pCWndJikokuhyou);

		update01_03_02_33_setEkimei_Nyuusen(
			pCWndJikokuhyou);

		update01_03_02_06_setEkimei_Chaku( 
			pCWndJikokuhyou ) ;
		update01_03_02_09_setEkimei_Track(
			pCWndJikokuhyou);

		update01_03_02_19_setEkimei_Ressyabangou(
			pCWndJikokuhyou);
		update01_03_02_20_setEkimei_OperationNumber(
			pCWndJikokuhyou);
		update01_03_02_21_setEkimei_Ressyasyubetsu(
			pCWndJikokuhyou);
		update01_03_02_22_setEkimei_Ressyamei(
			pCWndJikokuhyou);
		update01_03_02_23_setEkimei_Gousuu(
			pCWndJikokuhyou);
		update01_03_02_24_setEkimei_Gou(
			pCWndJikokuhyou);

		update01_03_02_07_setEkimei_Hatsu( 
			pCWndJikokuhyou ) ;

		update01_03_02_26_setEkimei_OuterShuchaku(
			pCWndJikokuhyou);
		

		// --------------------------------
		//	(1.3.2.16)セル(ColumnType_Ekimei, ColumnType_Outer_Shuchaku)
		// --------------------------------
		//update01_03_02_16_setEkimei_OuterTerminal_Shuchaku(
		//	pCWndJikokuhyou);

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

void CCellBuilderCustomize::update01_01_setGridBorder( 
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

void CCellBuilderCustomize::update01_03_01_setEkimei_Ressyabangou( 
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

void CCellBuilderCustomize::update01_03_02_12_setEkimei_OperationNumber(
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
					if (idx == m_iOperationNumberRows - 1)
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


void CCellBuilderCustomize::update01_03_02_02_setEkimei_Ressyasyubetsu(
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


void CCellBuilderCustomize::update01_03_02_03_setEkimei_Ressyamei( 
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


void CCellBuilderCustomize::update01_03_02_04_setEkimei_Gousuu( 
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


void CCellBuilderCustomize::update01_03_02_05_setEkimei_Gou( 
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

void CCellBuilderCustomize::update01_03_02_13_setShihatsuEkimei(
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

void CCellBuilderCustomize::update01_03_02_14_setShuchakuEkimei(
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

void CCellBuilderCustomize::update01_03_02_27_setEkimei_PrevRessyabangou(
	CWndJikokuhyou* pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	CDcdTargetGetDC	aCDcdTarget(NULL);

	// --------------------------------
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou());
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
				CdYColSpec::ColumnType_EkiPrevRessyabangou,
				iEkiOrder);
			int iYColumnNumber = m_CdYColSpecCont.ColumnNumberFromSpec(
				aCdYColSpec, false);
			CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell(
				iXColumnNumber, iYColumnNumber);

			typedef CDcdTextbox CDcDrawCell;
			Ou<CDcDrawCell> pCDcDrawCell;

			if (pCDcdGridCell != 0)
			{
				//(1.3.*.1)　セル(ColumnType_Ekimei,ColumnType_Ressyabangou) 
				//	の結合セルの属性を設定。
				pCDcdGridCell->setAttachCellCount(2, 1);

				//	(1.3.*.2)　セル(ColumnType_Ekimei,ColumnType_Ressyabangou) 
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

				//(1.3.*.3)　セル(ColumnType_Ekimei,ColumnType_Ressyabangou) 
				//	DcDrawオブジェクトに、属性を設定。
				{
					*pCDcDrawCell = createCDcdXColumn0();
					pCDcDrawCell->setText(tstringOf(
						(LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_PrevRessyabangou)));
				}
			}

			CDcdGridYColumn* pCDcdGridYColumn = pCDcdGrid->getYColumn(
				iYColumnNumber);
			if (pCDcdGridYColumn)
			{
				//(1.3.*.4)　Y列(ColumnType_Ressyabangou) のセルの高さを設定
				{
					CdDcdSizeXy aCdDcdSizeXy;
					if (pCDcDrawCell->getItemSize(
						&aCDcdTarget, &aCdDcdSizeXy))
					{
						pCDcdGridYColumn->setColumnSize(aCdDcdSizeXy.getY());
					}
				}
				//	　(1.3.*.5)　Y列(ColumnType_Ressyabangou) の境界線の
				//	DcDrawオブジェクト に属性を設定。
				//	　(1.3.*.6)　Y列ColumnType_Ressyabangou) の境界線の
				//	高さを設定
				{
					CDcdGridYBorder* pCDcdGridYBorder
						= pCDcdGridYColumn->getCDcdGridYBorder();
					Ou<CDcdLine> pCDcdLine = pCDcdGridYBorder->getIfDcDraw();

					CdYColSpec aCdYColSpecNext
						= m_CdYColSpecCont.ColumnNumberToSpec(
							iYColumnNumber + 1);
					if (aCdYColSpecNext.getColumnType() == aCdYColSpec.ColumnType_Bikou)
					{
						pCDcdLine->setCdPenProp(getCdPenPropBoldLine());
					}
					else if (aCdYColSpec.getEkiOrder()
						!= aCdYColSpecNext.getEkiOrder()
						&& aCdDedEki.getKyoukaisen())
					{
						pCDcdLine->setCdPenProp(getCdPenPropBoldLine());
					}
					else
					{
						pCDcdLine->setCdPenProp(getCdPenPropNarrowLine());
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

void CCellBuilderCustomize::update01_03_02_28_setEkimei_PrevOperationNumber(
	CWndJikokuhyou* pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	CDcdTargetGetDC	aCDcdTarget(NULL);

	// --------------------------------
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou());
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
			for (int idx = 0; aCdDedEki.getJikokuhyouPrevOperationNumberDisplay() > 0 &&
				idx < aCdDedEki.getJikokuhyouPrevOperationNumberDisplayRows(); idx++)
			{
				CdYColSpec aCdYColSpec(
					CdYColSpec::ColumnType_EkiPrevOperationNumber,
					iEkiOrder, idx);
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
						pCDcdGridCell->setAttachCellCount(2, aCdDedEki.getJikokuhyouPrevOperationNumberDisplayRows());
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
								IDS_WORD_PrevOperationNumber)));
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

						CdYColSpec aCdYColSpecNext
							= m_CdYColSpecCont.ColumnNumberToSpec(
								iYColumnNumber + 1);
						if (idx < aCdDedEki.getJikokuhyouPrevOperationNumberDisplayRows() - 1)
						{
							pCDcdLine->setCdPenProp(getCdPenPropNullLine());
						}
						else if (aCdYColSpecNext.getColumnType() == aCdYColSpec.ColumnType_Bikou)
						{
							pCDcdLine->setCdPenProp(getCdPenPropBoldLine());
						}
						else if (aCdYColSpec.getEkiOrder()
							!= aCdYColSpecNext.getEkiOrder()
							&& aCdDedEki.getKyoukaisen())
						{
							pCDcdLine->setCdPenProp(getCdPenPropBoldLine());
						}
						else
						{
							pCDcdLine->setCdPenProp(getCdPenPropNarrowLine());
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
}


void CCellBuilderCustomize::update01_03_02_29_setEkimei_PrevRessyasyubetsu(
	CWndJikokuhyou* pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	CDcdTargetGetDC	aCDcdTarget(NULL);

	// --------------------------------
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou());
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
				CdYColSpec::ColumnType_EkiPrevRessyasyubetsu,
				iEkiOrder);
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
							IDS_WORD_PrevRESSYASYUBETSU)));
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

					CdYColSpec aCdYColSpecNext
						= m_CdYColSpecCont.ColumnNumberToSpec(
							iYColumnNumber + 1);
					if (aCdYColSpecNext.getColumnType() == aCdYColSpec.ColumnType_Bikou)
					{
						pCDcdLine->setCdPenProp(getCdPenPropBoldLine());
					}
					else if (aCdYColSpec.getEkiOrder()
						!= aCdYColSpecNext.getEkiOrder()
						&& aCdDedEki.getKyoukaisen())
					{
						pCDcdLine->setCdPenProp(getCdPenPropBoldLine());
					}
					else
					{
						pCDcdLine->setCdPenProp(getCdPenPropNarrowLine());
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


void CCellBuilderCustomize::update01_03_02_30_setEkimei_PrevRessyamei(
	CWndJikokuhyou* pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	CDcdTargetGetDC	aCDcdTarget(NULL);

	// --------------------------------
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou());
	CdXColSpec aCdXColSpec(
		CdXColSpec::ColumnType_Ekimei);
	int iXColumnNumber =
		m_CdXColSpecCont.ColumnNumberFromSpec(aCdXColSpec);

	if (iXColumnNumber >= 0)
	{
		for (int iEkiOrder = 0; iEkiOrder < muCdDedEki->size();
			iEkiOrder++)
		{
			CdYColSpec aCdYColSpec(
				CdYColSpec::ColumnType_EkiPrevRessyamei,
				iEkiOrder);
			int iYColumnNumber = m_CdYColSpecCont.ColumnNumberFromSpec(
				aCdYColSpec, false);
			CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell(
				iXColumnNumber, iYColumnNumber);

			typedef CDcdTextboxV3 CDcDrawCell;
			Ou<CDcDrawCell> pCDcDrawCell;

			if (pCDcdGridCell != NULL)
			{
				//(1.3.*.1)　結合セルの属性を設定。
				pCDcdGridCell->setAttachCellCount(2, 3);

				//	(1.3.*.2)　セル(ColumnType_Ekimei,ColumnType_Ressyabangou) 
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
				//(1.3.*.3)　セル(ColumnType_Ekimei,ColumnType_Ressyabangou) 
				//	DcDrawオブジェクトに、属性を設定。
				{
					*pCDcDrawCell = createCDcdXColumn0V();
					pCDcDrawCell->setText(tstringOf(
						(LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_PrevRessyamei)));
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
					pCDcdLine->setCdPenProp(getCdPenPropNullLine());

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


void CCellBuilderCustomize::update01_03_02_31_setEkimei_PrevGousuu(
	CWndJikokuhyou* pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	CDcdTargetGetDC	aCDcdTarget(NULL);

	// --------------------------------
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou());
	CdXColSpec aCdXColSpec(
		CdXColSpec::ColumnType_Ekimei);
	int iXColumnNumber =
		m_CdXColSpecCont.ColumnNumberFromSpec(aCdXColSpec);

	if (iXColumnNumber >= 0)
	{
		for (int iEkiOrder = 0; iEkiOrder < muCdDedEki->size();
			iEkiOrder++)
		{
			CdYColSpec aCdYColSpec(
				CdYColSpec::ColumnType_EkiPrevGousuu,
				iEkiOrder);
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

				//	(1.3.*.2)　セルのDcDrawオブジェクトの型を設定
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
					*pCDcDrawCell = createCDcdXColumn0();
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
					pCDcdLine->setCdPenProp(getCdPenPropNullLine());

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


void CCellBuilderCustomize::update01_03_02_32_setEkimei_PrevGou(
	CWndJikokuhyou* pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	CDcdTargetGetDC	aCDcdTarget(NULL);

	// --------------------------------
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou());
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
				CdYColSpec::ColumnType_EkiPrevGou,
				iEkiOrder);
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

				//	(1.3.*.2)　セルのDcDrawオブジェクトの型を設定
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
					*pCDcDrawCell = createCDcdXColumn0();
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

					CdYColSpec aCdYColSpecNext
						= m_CdYColSpecCont.ColumnNumberToSpec(
							iYColumnNumber + 1);
					if (aCdYColSpecNext.getColumnType() == aCdYColSpec.ColumnType_Bikou)
					{
						pCDcdLine->setCdPenProp(getCdPenPropBoldLine());
					}
					else if (aCdYColSpec.getEkiOrder()
						!= aCdYColSpecNext.getEkiOrder()
						&& aCdDedEki.getKyoukaisen())
					{
						pCDcdLine->setCdPenProp(getCdPenPropBoldLine());
					}
					else
					{
						pCDcdLine->setCdPenProp(getCdPenPropNarrowLine());
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

void CCellBuilderCustomize::update01_03_02_25_setEkimei_OuterSihatsu(
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

			CdYColSpec aCdYColSpec1(
				CdYColSpec::ColumnType_EkiOuter_Shihatsu1,
				iEkiOrder);
			CdYColSpec aCdYColSpec2(
				CdYColSpec::ColumnType_EkiOuter_Shihatsu2,
				iEkiOrder);
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
					/**
						この項の下には、着時刻・番線・種別変更表示・発時刻のいずれかが来るので、いずれにしろ通常罫線でよい。
					*/
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
}

void CCellBuilderCustomize::update01_03_02_06_setEkimei_Chaku( 
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
					・カスタマイズ時刻表
						次の列が発時刻の場合のみ結合する
				*/

				CdYColSpec aCdYColSpecNext
					= m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumber + 1);
				if (aCdYColSpec.getColumnType() == aCdYColSpec.ColumnType_Ekijikoku_Chaku
					&& aCdYColSpecNext.getColumnType() == aCdYColSpecNext.ColumnType_Ekijikoku_Hatsu
					&& aCdYColSpec.getEkiOrder() == aCdYColSpecNext.getEkiOrder())
				{
					pCDcdGridCell->setAttachCellCount(1, 2);
				}
				else
				{
					pCDcdGridCell->setAttachCellCount(1, 1);
				}


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
					if (aCdYColSpecNext.getColumnType() == aCdYColSpec.ColumnType_Bikou)
					{
						pCDcdLine->setCdPenProp(getCdPenPropBoldLine());
					}
					else if (aCdYColSpec.getEkiOrder()
						!= aCdYColSpecNext.getEkiOrder()
						&& aCdDedEki.getKyoukaisen())
					{
						pCDcdLine->setCdPenProp(getCdPenPropBoldLine());
					}
					else if (aCdYColSpec.getEkiOrder()
						!= aCdYColSpecNext.getEkiOrder() &&
						aCdYColSpecNext.isEkiJikoku())
					{
						pCDcdLine->setCdPenProp(getCdPenPropNullLine());
					}
					else
					{
						pCDcdLine->setCdPenProp(getCdPenPropNarrowLine());
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

void CCellBuilderCustomize::update01_03_02_33_setEkimei_Nyuusen(
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
				CdYColSpec::ColumnType_Ekijikoku_Nyuusen,
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
							IDS_WORD_NyuusenJikoku)));
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

					//	この駅の駅時刻形式が「着発」 AND
					//	この列が着で、次の列が発なら、下に罫線
					CdYColSpec aCdYColSpecNext
						= m_CdYColSpecCont.ColumnNumberToSpec(
							iYColumnNumber + 1);
					if (aCdYColSpecNext.getColumnType() == aCdYColSpec.ColumnType_Bikou)
					{
						pCDcdLine->setCdPenProp(getCdPenPropBoldLine());
					}
					else if (aCdYColSpec.getEkiOrder()
						!= aCdYColSpecNext.getEkiOrder()
						&& aCdDedEki.getKyoukaisen())
					{
						pCDcdLine->setCdPenProp(getCdPenPropBoldLine());
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
						pCDcdGridYBorder->setColumnBorderSize(
							aCdDcdSizeXy.getX());
					}
				}
			}
		}
	}
}

void CCellBuilderCustomize::update01_03_02_09_setEkimei_Track(
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
					・カスタマイズ時刻表
						右側着発の表示セルと、結合
				*/
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
					//AllTrackの場合、駅名、そうでない場合、着発番線・発車番線・到着番線のいずれか
					//if (m_bDisplayAllTrack)
					//{
					//	pCDcDrawCell->setText(aCdDedEki.getEkimei());
					//}
					//else 
					if(aCdDedEki.isHatsuChakuHyouji())
					{
						pCDcDrawCell->setText(tstringOf(
							(LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_TrackChakuHatsu)));
					}
					else if (aCdDedEki.getChakujikokuHyouji())
					{
						pCDcDrawCell->setText(tstringOf(
							(LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_TrackChaku)));
					}
					else
					{
						pCDcDrawCell->setText(tstringOf(
							(LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_TrackHatsu)));
					}
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
					if (aCdYColSpecNext.getColumnType() == aCdYColSpec.ColumnType_Bikou)
					{
						pCDcdLine->setCdPenProp(getCdPenPropBoldLine());
					}
					else if (aCdYColSpec.getEkiOrder()
						!= aCdYColSpecNext.getEkiOrder()
						&& aCdDedEki.getKyoukaisen())
					{
						pCDcdLine->setCdPenProp(getCdPenPropBoldLine());
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
						pCDcdGridYBorder->setColumnBorderSize(
							aCdDcdSizeXy.getX());
					}
				}
			}
		}
	}
}

void CCellBuilderCustomize::update01_03_02_19_setEkimei_Ressyabangou(
	CWndJikokuhyou* pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	CDcdTargetGetDC	aCDcdTarget(NULL);

	// --------------------------------
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou());
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
				CdYColSpec::ColumnType_EkiRessyabangou,
				iEkiOrder);
			int iYColumnNumber = m_CdYColSpecCont.ColumnNumberFromSpec(
				aCdYColSpec, false);
			CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell(
				iXColumnNumber, iYColumnNumber);

			typedef CDcdTextbox CDcDrawCell;
			Ou<CDcDrawCell> pCDcDrawCell;

			if (pCDcdGridCell != 0)
			{
				//(1.3.*.1)　セル(ColumnType_Ekimei,ColumnType_Ressyabangou) 
				//	の結合セルの属性を設定。
				pCDcdGridCell->setAttachCellCount(2, 1);

				//	(1.3.*.2)　セル(ColumnType_Ekimei,ColumnType_Ressyabangou) 
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

				//(1.3.*.3)　セル(ColumnType_Ekimei,ColumnType_Ressyabangou) 
				//	DcDrawオブジェクトに、属性を設定。
				{
					*pCDcDrawCell = createCDcdXColumn0();
					pCDcDrawCell->setText(tstringOf(
						(LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_Ressyabangou)));
				}
			}

			CDcdGridYColumn* pCDcdGridYColumn = pCDcdGrid->getYColumn(
				iYColumnNumber);
			if (pCDcdGridYColumn)
			{
				//(1.3.*.4)　Y列(ColumnType_Ressyabangou) のセルの高さを設定
				{
					CdDcdSizeXy aCdDcdSizeXy;
					if (pCDcDrawCell->getItemSize(
						&aCDcdTarget, &aCdDcdSizeXy))
					{
						pCDcdGridYColumn->setColumnSize(aCdDcdSizeXy.getY());
					}
				}
				//	　(1.3.*.5)　Y列(ColumnType_Ressyabangou) の境界線の
				//	DcDrawオブジェクト に属性を設定。
				//	　(1.3.*.6)　Y列ColumnType_Ressyabangou) の境界線の
				//	高さを設定
				{
					CDcdGridYBorder* pCDcdGridYBorder
						= pCDcdGridYColumn->getCDcdGridYBorder();
					Ou<CDcdLine> pCDcdLine = pCDcdGridYBorder->getIfDcDraw();

					CdYColSpec aCdYColSpecNext
						= m_CdYColSpecCont.ColumnNumberToSpec(
							iYColumnNumber + 1);
					if (aCdYColSpecNext.getColumnType() == aCdYColSpec.ColumnType_Bikou)
					{
						pCDcdLine->setCdPenProp(getCdPenPropBoldLine());
					}
					else if (aCdYColSpec.getEkiOrder()
						!= aCdYColSpecNext.getEkiOrder()
						&& aCdDedEki.getKyoukaisen())
					{
						pCDcdLine->setCdPenProp(getCdPenPropBoldLine());
					}
					else
					{
						pCDcdLine->setCdPenProp(getCdPenPropNarrowLine());
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

void CCellBuilderCustomize::update01_03_02_20_setEkimei_OperationNumber(
	CWndJikokuhyou * pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	CDcdTargetGetDC	aCDcdTarget(NULL);

	// --------------------------------
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou());
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
			for (int idx = 0; aCdDedEki.getJikokuhyouOperationNumberDisplay() > 0 &&
				idx < aCdDedEki.getJikokuhyouOperationNumberDisplayRows(); idx++)
			{
				CdYColSpec aCdYColSpec(
					CdYColSpec::ColumnType_EkiOperationNumber,
					iEkiOrder,idx);
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
						pCDcdGridCell->setAttachCellCount(2, aCdDedEki.getJikokuhyouOperationNumberDisplayRows());
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

						CdYColSpec aCdYColSpecNext
							= m_CdYColSpecCont.ColumnNumberToSpec(
								iYColumnNumber + 1);
						if (idx < aCdDedEki.getJikokuhyouOperationNumberDisplayRows() - 1)
						{
							pCDcdLine->setCdPenProp(getCdPenPropNullLine());
						}
						else if (aCdYColSpecNext.getColumnType() == aCdYColSpec.ColumnType_Bikou)
						{
							pCDcdLine->setCdPenProp(getCdPenPropBoldLine());
						}
						else if (aCdYColSpec.getEkiOrder()
							!= aCdYColSpecNext.getEkiOrder()
							&& aCdDedEki.getKyoukaisen())
						{
							pCDcdLine->setCdPenProp(getCdPenPropBoldLine());
						}
						else
						{
							pCDcdLine->setCdPenProp(getCdPenPropNarrowLine());
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
}


void CCellBuilderCustomize::update01_03_02_21_setEkimei_Ressyasyubetsu(
	CWndJikokuhyou* pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	CDcdTargetGetDC	aCDcdTarget(NULL);

	// --------------------------------
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou());
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
				CdYColSpec::ColumnType_EkiRessyasyubetsu,
				iEkiOrder);
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

					CdYColSpec aCdYColSpecNext
						= m_CdYColSpecCont.ColumnNumberToSpec(
							iYColumnNumber + 1);
					if (aCdYColSpecNext.getColumnType() == aCdYColSpec.ColumnType_Bikou)
					{
						pCDcdLine->setCdPenProp(getCdPenPropBoldLine());
					}
					else if (aCdYColSpec.getEkiOrder()
						!= aCdYColSpecNext.getEkiOrder()
						&& aCdDedEki.getKyoukaisen())
					{
						pCDcdLine->setCdPenProp(getCdPenPropBoldLine());
					}
					else
					{
						pCDcdLine->setCdPenProp(getCdPenPropNarrowLine());
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


void CCellBuilderCustomize::update01_03_02_22_setEkimei_Ressyamei(
	CWndJikokuhyou* pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	CDcdTargetGetDC	aCDcdTarget(NULL);

	// --------------------------------
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou());
	CdXColSpec aCdXColSpec(
		CdXColSpec::ColumnType_Ekimei);
	int iXColumnNumber =
		m_CdXColSpecCont.ColumnNumberFromSpec(aCdXColSpec);

	if (iXColumnNumber >= 0)
	{
		for (int iEkiOrder = 0; iEkiOrder < muCdDedEki->size();
			iEkiOrder++)
		{
			CdYColSpec aCdYColSpec(
				CdYColSpec::ColumnType_EkiRessyamei,
				iEkiOrder);
			int iYColumnNumber = m_CdYColSpecCont.ColumnNumberFromSpec(
				aCdYColSpec, false);
			CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell(
				iXColumnNumber, iYColumnNumber);

			typedef CDcdTextboxV3 CDcDrawCell;
			Ou<CDcDrawCell> pCDcDrawCell;

			if (pCDcdGridCell != NULL)
			{
				//(1.3.*.1)　結合セルの属性を設定。
				pCDcdGridCell->setAttachCellCount(2, 3);

				//	(1.3.*.2)　セル(ColumnType_Ekimei,ColumnType_Ressyabangou) 
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
				//(1.3.*.3)　セル(ColumnType_Ekimei,ColumnType_Ressyabangou) 
				//	DcDrawオブジェクトに、属性を設定。
				{
					*pCDcDrawCell = createCDcdXColumn0V();
					pCDcDrawCell->setText(tstringOf(
						(LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_Ressyamei)));
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
					pCDcdLine->setCdPenProp(getCdPenPropNullLine());

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


void CCellBuilderCustomize::update01_03_02_23_setEkimei_Gousuu(
	CWndJikokuhyou* pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	CDcdTargetGetDC	aCDcdTarget(NULL);

	// --------------------------------
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou());
	CdXColSpec aCdXColSpec(
		CdXColSpec::ColumnType_Ekimei);
	int iXColumnNumber =
		m_CdXColSpecCont.ColumnNumberFromSpec(aCdXColSpec);

	if (iXColumnNumber >= 0)
	{
		for (int iEkiOrder = 0; iEkiOrder < muCdDedEki->size();
			iEkiOrder++)
		{
			CdYColSpec aCdYColSpec(
				CdYColSpec::ColumnType_EkiGousuu,
				iEkiOrder);
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

				//	(1.3.*.2)　セルのDcDrawオブジェクトの型を設定
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
					*pCDcDrawCell = createCDcdXColumn0();
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
					pCDcdLine->setCdPenProp(getCdPenPropNullLine());

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


void CCellBuilderCustomize::update01_03_02_24_setEkimei_Gou(
	CWndJikokuhyou* pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	CDcdTargetGetDC	aCDcdTarget(NULL);

	// --------------------------------
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou());
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
				CdYColSpec::ColumnType_EkiGou,
				iEkiOrder);
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

				//	(1.3.*.2)　セルのDcDrawオブジェクトの型を設定
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
					*pCDcDrawCell = createCDcdXColumn0();
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

					CdYColSpec aCdYColSpecNext
						= m_CdYColSpecCont.ColumnNumberToSpec(
							iYColumnNumber + 1);
					if (aCdYColSpecNext.getColumnType() == aCdYColSpec.ColumnType_Bikou)
					{
						pCDcdLine->setCdPenProp(getCdPenPropBoldLine());
					}
					else if (aCdYColSpec.getEkiOrder()
						!= aCdYColSpecNext.getEkiOrder()
						&& aCdDedEki.getKyoukaisen())
					{
						pCDcdLine->setCdPenProp(getCdPenPropBoldLine());
					}
					else
					{
						pCDcdLine->setCdPenProp(getCdPenPropNarrowLine());
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

void CCellBuilderCustomize::update01_03_02_07_setEkimei_Hatsu(
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
					if (aCdYColSpecNext.getColumnType() == aCdYColSpec.ColumnType_Bikou)
					{
						pCDcdLine->setCdPenProp(getCdPenPropBoldLine());
					}
					else if (aCdYColSpec.getEkiOrder()
						!= aCdYColSpecNext.getEkiOrder()
						&& aCdDedEki.getKyoukaisen())
					{
						pCDcdLine->setCdPenProp(getCdPenPropBoldLine());
					}
					else if (aCdYColSpecNext.isEkiJikoku())
					{
						pCDcdLine->setCdPenProp(getCdPenPropNullLine());
					}
					else
					{
						pCDcdLine->setCdPenProp(getCdPenPropNarrowLine());
					}

					//	次の列が異なる駅の列。
					//	当駅に『境界線』属性がある。
					//	次の列が路線外終着駅表示
					//
					//	これら条件を満たす場合は、
					//	下（次の駅との間）に罫線
					//if ( aCdYColSpecNext.isEkiJikoku() 
					//	&& aCdYColSpec.getEkiOrder() 
					//		!= aCdYColSpecNext.getEkiOrder() 
					//	&& aCdDedEki.getKyoukaisen() ) 
					//{
					//	/*pCDcdLine->setCdPenProp( 
					//		getCdPenPropNarrowLine() ) ;*/
					//	pCDcdLine->setCdPenProp(getCdPenPropBoldLine());
					//}
					////	次の列が路線外終着駅表示の場合は、細線
					//else if (aCdYColSpecNext.getColumnType() == aCdYColSpecNext.ColumnType_Outer_Shuchaku1)
					//{
					//	pCDcdLine->setCdPenProp(getCdPenPropNarrowLine());
					//}
					////	次の列が駅時刻、番線表示以外の場合は、太線
					//else if ( !aCdYColSpecNext.isEkiJikoku() &&
					//	aCdYColSpecNext.getColumnType() != aCdYColSpecNext.ColumnType_Track)
					//{
					//	pCDcdLine->setCdPenProp( getCdPenPropBoldLine() ) ;
					//}
					//else
					//{
					//	pCDcdLine->setCdPenProp( getCdPenPropNullLine() ) ;
					//}

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

void CCellBuilderCustomize::update01_03_02_26_setEkimei_OuterShuchaku(
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

			CdYColSpec aCdYColSpec1(
				CdYColSpec::ColumnType_EkiOuter_Shuchaku1,
				iEkiOrder);
			CdYColSpec aCdYColSpec2(
				CdYColSpec::ColumnType_EkiOuter_Shuchaku2,
				iEkiOrder);
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
					/**
						この項の下に来るのは、次駅の項もしくは、備考となる。
						備考な場合またはこの駅と次駅の間に境界線がある場合は太線となり、
						それ以外の場合は通常罫線となる。
					*/
					CdYColSpec aCdYColSpecNext
						= m_CdYColSpecCont.ColumnNumberToSpec(
							iYColumnNumber2 + 1);
					if (aCdYColSpecNext.getColumnType() == aCdYColSpecNext.ColumnType_Bikou)
					{
						pCDcdLine->setCdPenProp(getCdPenPropBoldLine());
					}
					else if (aCdYColSpec2.getEkiOrder()
						!= aCdYColSpecNext.getEkiOrder()
						&& aCdDedEki.getKyoukaisen())
					{
						pCDcdLine->setCdPenProp(getCdPenPropBoldLine());
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
		}
	}
}

void CCellBuilderCustomize::update01_03_02_08_setEkimei_Bikou( 
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

void CCellBuilderCustomize::update01_04_01_06_setChakuhatsu_Chaku( 
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

void CCellBuilderCustomize::update01_04_01_09_setChakuhatsu_Track(
	CWndJikokuhyou* pCWndJikokuhyou)
{
	//不要そうなので一旦コメントアウト
	//CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	//CDcdTargetGetDC	aCDcdTarget(NULL);

	//// --------------------------------
	//const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
	//	m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(
	//		m_pCentDedRessyaCont->getRessyahoukou());
	//// --------------------------------
	//CdXColSpec aCdXColSpec(
	//	CdXColSpec::ColumnType_Chakuhatsu);
	//int iXColumnNumber =
	//	m_CdXColSpecCont.ColumnNumberFromSpec(aCdXColSpec);
	//if (iXColumnNumber >= 0)
	//{
	//	for (int iEkiOrder = 0; iEkiOrder < muCdDedEki->size();
	//		iEkiOrder++)
	//	{
	//		CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);

	//		CdYColSpec aCdYColSpec(
	//			CdYColSpec::ColumnType_Track,
	//			iEkiOrder);
	//		int iYColumnNumber =
	//			m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec, false);
	//		CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell(
	//			iXColumnNumber, iYColumnNumber);

	//		typedef CDcdTextbox CDcDrawCell;
	//		Ou<CDcDrawCell> pCDcDrawCell;
	//		if (pCDcdGridCell != 0)
	//		{
	//			//(1.4.1.*.1)　セルの結合セルの属性を設定。
	//			pCDcdGridCell->setAttachCellCount(1, 1);

	//			//	(1.4.1.*.2)　セルのDcDrawオブジェクトの型を設定
	//			//	( CDcdTextbox とする)。
	//			{
	//				pCDcDrawCell = dynamic_castOu<CDcDrawCell>(
	//					pCDcdGridCell->getIfDcDraw());
	//				if (pCDcDrawCell == NULL)
	//				{
	//					pCDcDrawCell = OuNew<CDcDrawCell>(new CDcDrawCell);
	//					pCDcdGridCell->setIfDcDraw(pCDcDrawCell);
	//				}
	//			}
	//			//(1.4.1.*.3)　セルのDcDrawオブジェクトに、属性を設定。
	//			{
	//				*pCDcDrawCell = createCDcdHatsuchaku();
	//				if(m_bDisplayAllTrack)
	//				{
	//					pCDcDrawCell->setText(tstringOf(
	//						(LPCTSTR)MfcUtil::LoadCString(
	//							IDS_WORD_Track)));
	//				}
	//			}
	//		}
	//	}
	//}
}

void CCellBuilderCustomize::update01_04_01_07_setChakuhatsu_Hatsu( 
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


void CCellBuilderCustomize::update02_02_updateRessya( 
		int iXColumnNumber ,
		const CustomizeJikokuhyouContent& aCustomizeJikokuhyouContent,
		//const CentDedRessya* pCentDedRessya ,
		CWndJikokuhyou* pCWndJikokuhyou ) 
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid() ;
	CDcdTargetGetDC	aCDcdTarget( NULL ) ;

	int iRessyaIndexContIndex = 0;
	const CentDedRessya* pCentDedRessya = NULL; 
	//暫定措置(もっといい方法があるか考える)
	//aCentDedRessya:パターンダイヤプレビュー機能が有効なとき、aCentDedRessyaに対象列車をコピーしてから、modifyRessyaJikokuを実施し、そのアドレスでpCentDedRessyaに上書きする
	CentDedRessya aCentDedRessya(m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()->size(), m_pCentDedRessyaCont->getRessyahoukou());

	//CustomizeJikokuhyouContent aCustomizeJikokuhyouContent;
	//if (aCustomizeJikokuhyouContent.iRessyaIndexCont.empty())
	//{
	//	if (aCustomizeJikokuhyouContent.iReleaseEkiOrder >= 0)
	//	{
	//		if (m_iOuterShuchakuDisplayEkiOrder[aCustomizeJikokuhyouContent.iReleaseEkiOrder] >= 0)
	//		{
	//			aCustomizeJikokuhyouContentTemp = aCustomizeJikokuhyouContent;
	//		}
	//	}
	//	else if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
	//	{
	//		if (m_iOuterShihatsuDisplayEkiOrder[aCustomizeJikokuhyouContent.iConnectEkiOrder] >= 0)
	//		{
	//			aCustomizeJikokuhyouContentTemp = aCustomizeJikokuhyouContent;
	//		}
	//	}
	//}
	//else
	//{
	//	aCustomizeJikokuhyouContentTemp = aCustomizeJikokuhyouContent;
	//}
	if (!aCustomizeJikokuhyouContent.iRessyaIndexCont.empty()/* || aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex] < 0 ||
		aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex] >= m_pCentDedRessyaCont->size()*/)
	{
	//	CentDedRessya aRessya(m_pCentDedRessyaCont->createNullRessya());
	//	pCentDedRessya = &aRessya;
	//}
	//else
	//{
		pCentDedRessya = m_pCentDedRessyaCont->getMuPtr()->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex]);
		if (aCustomizeJikokuhyouContent.iShiftSecond != 0)
		{
			aCentDedRessya = CentDedRessya(*pCentDedRessya);
			aCentDedRessya.modifyRessyaJikoku(
				aCustomizeJikokuhyouContent.iShiftSecond,
				CdDedJikokuOrder(0, CdDedJikokuOrder::EkiJikokuItem_Chaku));
			pCentDedRessya = &aCentDedRessya;
		}
	}

	int iValidSyuuchakuEki = -1;
	if (pCentDedRessya != NULL)
	{
		iValidSyuuchakuEki = pCentDedRessya->getValidSyuuchakuEki();
	}
	int iCurrentRessyaShihatsuEkiOrder = -1;
	//int iConnectEkiOrder = -1;
	//int iReleaseEkiOrder = -1;
	//if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Junction &&
	//	m_iEnableOperation > 0)
	//{
	//	iConnectEkiOrder = pCentDedRessya->getLastOperation().getConnectEkiOrder();
	//}
	//if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Junction &&
	//	m_iEnableOperation > 0)
	//{
	//	iReleaseEkiOrder = pCentDedRessya->getFirstOperation().getReleaseEkiOrder();
	//}

	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		m_pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou());
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
					aCustomizeJikokuhyouContent,
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
					aCustomizeJikokuhyouContent,
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
					aCustomizeJikokuhyouContent,
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
					aCustomizeJikokuhyouContent,
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
					aCustomizeJikokuhyouContent,
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
					aCustomizeJikokuhyouContent,
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
					aCustomizeJikokuhyouContent,
					pCWndJikokuhyou);
			}
			break;
			//終着駅名表示は最後に行います。
			//case CdYColSpec::ColumnType_ShuchakuEkimei:
			//{
			//	// --------------------------------
			//	//	(2.2.2.14)セル(ColumnType_Ressya, ColumnType_ShuchakuEkimei)
			//	// --------------------------------
			//	update02_02_02_14_setRessya_ShuchakuEkimei(
			//		iXColumnNumber,
			//		iYColumnNumber,
			//		pCentDedRessya,
			//		aCustomizeJikokuhyouContent,
			//		pCWndJikokuhyou);
			//}
			//break;
			case CdYColSpec::ColumnType_EkiPrevRessyabangou:
			{
				if (!aCustomizeJikokuhyouContent.iRessyaIndexCont.empty() &&
					iRessyaIndexContIndex < (int)aCustomizeJikokuhyouContent.iRessyaIndexCont.size() - 1 &&
					aCdYColSpec.getEkiOrder() > iValidSyuuchakuEki &&
					iValidSyuuchakuEki != -1)
				{
					iRessyaIndexContIndex++;
					pCentDedRessya =
						m_pCentDedRessyaCont->getMuPtr()->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex]);
					iCurrentRessyaShihatsuEkiOrder = iValidSyuuchakuEki;
					iValidSyuuchakuEki = pCentDedRessya->getValidSyuuchakuEki();

					if (aCustomizeJikokuhyouContent.iShiftSecond != 0)
					{
						aCentDedRessya = CentDedRessya(*pCentDedRessya);
						aCentDedRessya.modifyRessyaJikoku(
							aCustomizeJikokuhyouContent.iShiftSecond,
							CdDedJikokuOrder(0, CdDedJikokuOrder::EkiJikokuItem_Chaku));
						pCentDedRessya = &aCentDedRessya;
					}
				}
				update02_02_02_27_setRessya_PrevRessyabangou(
					iXColumnNumber,
					iYColumnNumber,
					pCentDedRessya,
					aCustomizeJikokuhyouContent,
					aCdYColSpec.getEkiOrder(),
					iCurrentRessyaShihatsuEkiOrder,
					iRessyaIndexContIndex,
					pCWndJikokuhyou);
			}
			break;
			case CdYColSpec::ColumnType_EkiPrevRessyasyubetsu:
			{
				// --------------------------------
				//	(2.2.2.29)セル(ColumnType_Ressya, ColumnType_EkiPrevRessyasyubetsu)
				// --------------------------------
				if (!aCustomizeJikokuhyouContent.iRessyaIndexCont.empty() &&
					iRessyaIndexContIndex < (int)aCustomizeJikokuhyouContent.iRessyaIndexCont.size() - 1 &&
					aCdYColSpec.getEkiOrder() > iValidSyuuchakuEki &&
					iValidSyuuchakuEki != -1)
				{
					iRessyaIndexContIndex++;
					pCentDedRessya =
						m_pCentDedRessyaCont->getMuPtr()->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex]);
					iCurrentRessyaShihatsuEkiOrder = iValidSyuuchakuEki;
					iValidSyuuchakuEki = pCentDedRessya->getValidSyuuchakuEki();

					if (aCustomizeJikokuhyouContent.iShiftSecond != 0)
					{
						aCentDedRessya = CentDedRessya(*pCentDedRessya);
						aCentDedRessya.modifyRessyaJikoku(
							aCustomizeJikokuhyouContent.iShiftSecond,
							CdDedJikokuOrder(0, CdDedJikokuOrder::EkiJikokuItem_Chaku));
						pCentDedRessya = &aCentDedRessya;
					}

				}
				update02_02_02_29_setRessya_PrevRessyasyubetsu(
					iXColumnNumber,
					iYColumnNumber,
					pCentDedRessya,
					aCustomizeJikokuhyouContent,
					aCdYColSpec.getEkiOrder(),
					iCurrentRessyaShihatsuEkiOrder,
					iRessyaIndexContIndex,
					pCWndJikokuhyou);
			}
			break;
			case CdYColSpec::ColumnType_EkiPrevOperationNumber:
			{
				if (!aCustomizeJikokuhyouContent.iRessyaIndexCont.empty() &&
					iRessyaIndexContIndex < (int)aCustomizeJikokuhyouContent.iRessyaIndexCont.size() - 1 &&
					aCdYColSpec.getEkiOrder() > iValidSyuuchakuEki &&
					iValidSyuuchakuEki != -1)
				{
					iRessyaIndexContIndex++;
					pCentDedRessya =
						m_pCentDedRessyaCont->getMuPtr()->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex]);
					iCurrentRessyaShihatsuEkiOrder = iValidSyuuchakuEki;
					iValidSyuuchakuEki = pCentDedRessya->getValidSyuuchakuEki();

					if (aCustomizeJikokuhyouContent.iShiftSecond != 0)
					{
						aCentDedRessya = CentDedRessya(*pCentDedRessya);
						aCentDedRessya.modifyRessyaJikoku(
							aCustomizeJikokuhyouContent.iShiftSecond,
							CdDedJikokuOrder(0, CdDedJikokuOrder::EkiJikokuItem_Chaku));
						pCentDedRessya = &aCentDedRessya;
					}
				}
				update02_02_02_28_setRessya_PrevOperationNumber(
					iXColumnNumber,
					iYColumnNumber,
					pCentDedRessya,
					aCustomizeJikokuhyouContent,
					aCdYColSpec.getEkiOrder(),
					iCurrentRessyaShihatsuEkiOrder,
					iRessyaIndexContIndex,
					pCWndJikokuhyou);
				//運用番号段数-1の分だけ、iYColumnNumberに加算します
				iYColumnNumber += muCdDedEki->get(aCdYColSpec.getEkiOrder()).getJikokuhyouPrevOperationNumberDisplayRows() - 1;
			}
			break;
			case CdYColSpec::ColumnType_EkiPrevRessyamei:
			{
				if (!aCustomizeJikokuhyouContent.iRessyaIndexCont.empty() &&
					iRessyaIndexContIndex < (int)aCustomizeJikokuhyouContent.iRessyaIndexCont.size() - 1 &&
					aCdYColSpec.getEkiOrder() > iValidSyuuchakuEki &&
					iValidSyuuchakuEki != -1)
				{
					iRessyaIndexContIndex++;
					pCentDedRessya =
						m_pCentDedRessyaCont->getMuPtr()->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex]);
					iCurrentRessyaShihatsuEkiOrder = iValidSyuuchakuEki;
					iValidSyuuchakuEki = pCentDedRessya->getValidSyuuchakuEki();

					if (aCustomizeJikokuhyouContent.iShiftSecond != 0)
					{
						aCentDedRessya = CentDedRessya(*pCentDedRessya);
						aCentDedRessya.modifyRessyaJikoku(
							aCustomizeJikokuhyouContent.iShiftSecond,
							CdDedJikokuOrder(0, CdDedJikokuOrder::EkiJikokuItem_Chaku));
						pCentDedRessya = &aCentDedRessya;
					}
				}
				update02_02_02_30_setRessya_PrevRessyamei(
					iXColumnNumber,
					iYColumnNumber,
					pCentDedRessya,
					aCustomizeJikokuhyouContent,
					aCdYColSpec.getEkiOrder(),
					iCurrentRessyaShihatsuEkiOrder,
					iRessyaIndexContIndex,
					pCWndJikokuhyou);
			}
			break;
			case CdYColSpec::ColumnType_EkiOuter_Shihatsu1:
			{
				// --------------------------------
				//	(2.2.2.15)セル(ColumnType_Ressya, ColumnType_Outer_Shihatsu)
				// --------------------------------
				if (!aCustomizeJikokuhyouContent.iRessyaIndexCont.empty() &&
					iRessyaIndexContIndex < (int)aCustomizeJikokuhyouContent.iRessyaIndexCont.size() - 1 &&
					aCdYColSpec.getEkiOrder() > iValidSyuuchakuEki &&
					iValidSyuuchakuEki != -1)
				{
					iRessyaIndexContIndex++;
					pCentDedRessya =
						m_pCentDedRessyaCont->getMuPtr()->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex]);
					iCurrentRessyaShihatsuEkiOrder = iValidSyuuchakuEki;
					iValidSyuuchakuEki = pCentDedRessya->getValidSyuuchakuEki();

					if (aCustomizeJikokuhyouContent.iShiftSecond != 0)
					{
						aCentDedRessya = CentDedRessya(*pCentDedRessya);
						aCentDedRessya.modifyRessyaJikoku(
							aCustomizeJikokuhyouContent.iShiftSecond,
							CdDedJikokuOrder(0, CdDedJikokuOrder::EkiJikokuItem_Chaku));
						pCentDedRessya = &aCentDedRessya;
					}

				}
				update02_02_02_25_setRessya_EkiOuterTerminal_Shihatsu(
					iXColumnNumber,
					iYColumnNumber,
					pCentDedRessya,
					aCustomizeJikokuhyouContent,
					aCdYColSpec.getEkiOrder(),
					iCurrentRessyaShihatsuEkiOrder,
					pCWndJikokuhyou);
				iYColumnNumber += 1;
			}
			break;
			case CdYColSpec::ColumnType_Ekijikoku_Nyuusen:
			{
				if (!aCustomizeJikokuhyouContent.iRessyaIndexCont.empty() &&
					iRessyaIndexContIndex < (int)aCustomizeJikokuhyouContent.iRessyaIndexCont.size() - 1 &&
					aCdYColSpec.getEkiOrder() > iValidSyuuchakuEki &&
					iValidSyuuchakuEki != -1)
				{
					iRessyaIndexContIndex++;
					pCentDedRessya =
						m_pCentDedRessyaCont->getMuPtr()->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex]);
					iCurrentRessyaShihatsuEkiOrder = iValidSyuuchakuEki;
					iValidSyuuchakuEki = pCentDedRessya->getValidSyuuchakuEki();

					if (aCustomizeJikokuhyouContent.iShiftSecond != 0)
					{
						aCentDedRessya = CentDedRessya(*pCentDedRessya);
						aCentDedRessya.modifyRessyaJikoku(
							aCustomizeJikokuhyouContent.iShiftSecond,
							CdDedJikokuOrder(0, CdDedJikokuOrder::EkiJikokuItem_Chaku));
						pCentDedRessya = &aCentDedRessya;
					}
				}
				update02_02_02_31_setRessya_Nyuusen(
					iXColumnNumber,
					iYColumnNumber,
					pCentDedRessya,
					aCustomizeJikokuhyouContent,
					aCdYColSpec.getEkiOrder(),
					iCurrentRessyaShihatsuEkiOrder,
					iRessyaIndexContIndex,
					pCWndJikokuhyou);
			}
			break;
			case CdYColSpec::ColumnType_Ekijikoku_Chaku:
			{
				if (!aCustomizeJikokuhyouContent.iRessyaIndexCont.empty() &&
					iRessyaIndexContIndex < (int)aCustomizeJikokuhyouContent.iRessyaIndexCont.size() - 1 &&
					aCdYColSpec.getEkiOrder() > iValidSyuuchakuEki &&
					iValidSyuuchakuEki != -1)
				{
					iRessyaIndexContIndex++;
					pCentDedRessya =
						m_pCentDedRessyaCont->getMuPtr()->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex]);
					iCurrentRessyaShihatsuEkiOrder = iValidSyuuchakuEki;
					iValidSyuuchakuEki = pCentDedRessya->getValidSyuuchakuEki();

					if (aCustomizeJikokuhyouContent.iShiftSecond != 0)
					{
						aCentDedRessya = CentDedRessya(*pCentDedRessya);
						aCentDedRessya.modifyRessyaJikoku(
							aCustomizeJikokuhyouContent.iShiftSecond,
							CdDedJikokuOrder(0, CdDedJikokuOrder::EkiJikokuItem_Chaku));
						pCentDedRessya = &aCentDedRessya;
					}
					//if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Junction &&
					//	m_iEnableOperation > 0)
					//{
					//	iConnectEkiOrder = pCentDedRessya->getLastOperation().getConnectEkiOrder();
					//}
					//iReleaseEkiOrder = -1;
				}
				update02_02_02_06_setRessya_Chaku(
					iXColumnNumber,
					iYColumnNumber,
					pCentDedRessya,
					aCustomizeJikokuhyouContent,
					aCdYColSpec.getEkiOrder(),
					iCurrentRessyaShihatsuEkiOrder,
					iRessyaIndexContIndex,
					pCWndJikokuhyou);
			}
			break;
			case CdYColSpec::ColumnType_Track:
			{
				if (!aCustomizeJikokuhyouContent.iRessyaIndexCont.empty() &&
					iRessyaIndexContIndex < (int)aCustomizeJikokuhyouContent.iRessyaIndexCont.size() - 1 &&
					aCdYColSpec.getEkiOrder() > iValidSyuuchakuEki &&
					iValidSyuuchakuEki != -1)
				{
					iRessyaIndexContIndex++;
					pCentDedRessya =
						m_pCentDedRessyaCont->getMuPtr()->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex]);
					iCurrentRessyaShihatsuEkiOrder = iValidSyuuchakuEki;
					iValidSyuuchakuEki = pCentDedRessya->getValidSyuuchakuEki();

					if (aCustomizeJikokuhyouContent.iShiftSecond != 0)
					{
						aCentDedRessya = CentDedRessya(*pCentDedRessya);
						aCentDedRessya.modifyRessyaJikoku(
							aCustomizeJikokuhyouContent.iShiftSecond,
							CdDedJikokuOrder(0, CdDedJikokuOrder::EkiJikokuItem_Chaku));
						pCentDedRessya = &aCentDedRessya;
					}
					//if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Junction &&
					//	m_iEnableOperation > 0)
					//{
					//	iConnectEkiOrder = pCentDedRessya->getLastOperation().getConnectEkiOrder();
					//}
					//iReleaseEkiOrder = -1;
				}
				update02_02_02_09_setRessya_Track(
					iXColumnNumber,
					iYColumnNumber,
					pCentDedRessya,
					aCustomizeJikokuhyouContent,
					aCdYColSpec.getEkiOrder(),
					iCurrentRessyaShihatsuEkiOrder,
					pCWndJikokuhyou);
			}
			break;
			case CdYColSpec::ColumnType_EkiRessyabangou:
			{
				if (!aCustomizeJikokuhyouContent.iRessyaIndexCont.empty() &&
					iRessyaIndexContIndex < (int)aCustomizeJikokuhyouContent.iRessyaIndexCont.size() - 1 &&
					aCdYColSpec.getEkiOrder() >= iValidSyuuchakuEki &&
					iValidSyuuchakuEki != -1)
				{
					iRessyaIndexContIndex++;
					pCentDedRessya =
						m_pCentDedRessyaCont->getMuPtr()->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex]);
					iCurrentRessyaShihatsuEkiOrder = iValidSyuuchakuEki;
					iValidSyuuchakuEki = pCentDedRessya->getValidSyuuchakuEki();

					if (aCustomizeJikokuhyouContent.iShiftSecond != 0)
					{
						aCentDedRessya = CentDedRessya(*pCentDedRessya);
						aCentDedRessya.modifyRessyaJikoku(
							aCustomizeJikokuhyouContent.iShiftSecond,
							CdDedJikokuOrder(0, CdDedJikokuOrder::EkiJikokuItem_Chaku));
						pCentDedRessya = &aCentDedRessya;
					}
					//if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Junction &&
					//	m_iEnableOperation > 0)
					//{
					//	iConnectEkiOrder = pCentDedRessya->getLastOperation().getConnectEkiOrder();
					//}
					//iReleaseEkiOrder = -1;
				}
				update02_02_02_19_setRessya_Ressyabangou(
					iXColumnNumber,
					iYColumnNumber,
					pCentDedRessya,
					aCustomizeJikokuhyouContent,
					aCdYColSpec.getEkiOrder(),
					iCurrentRessyaShihatsuEkiOrder,
					iRessyaIndexContIndex,
					pCWndJikokuhyou);
			}
			break;
			case CdYColSpec::ColumnType_EkiOperationNumber:
			{
				if (!aCustomizeJikokuhyouContent.iRessyaIndexCont.empty() &&
					iRessyaIndexContIndex < (int)aCustomizeJikokuhyouContent.iRessyaIndexCont.size() - 1 &&
					aCdYColSpec.getEkiOrder() >= iValidSyuuchakuEki &&
					iValidSyuuchakuEki != -1)
				{
					iRessyaIndexContIndex++;
					pCentDedRessya =
						m_pCentDedRessyaCont->getMuPtr()->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex]);
					iCurrentRessyaShihatsuEkiOrder = iValidSyuuchakuEki;
					iValidSyuuchakuEki = pCentDedRessya->getValidSyuuchakuEki();

					if (aCustomizeJikokuhyouContent.iShiftSecond != 0)
					{
						aCentDedRessya = CentDedRessya(*pCentDedRessya);
						aCentDedRessya.modifyRessyaJikoku(
							aCustomizeJikokuhyouContent.iShiftSecond,
							CdDedJikokuOrder(0, CdDedJikokuOrder::EkiJikokuItem_Chaku));
						pCentDedRessya = &aCentDedRessya;
					}
					//if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Junction &&
					//	m_iEnableOperation > 0)
					//{
					//	iConnectEkiOrder = pCentDedRessya->getLastOperation().getConnectEkiOrder();
					//}
					//iReleaseEkiOrder = -1;
				}
				update02_02_02_20_setRessya_OperationNumber(
					iXColumnNumber,
					iYColumnNumber,
					pCentDedRessya,
					aCustomizeJikokuhyouContent,
					aCdYColSpec.getEkiOrder(),
					iCurrentRessyaShihatsuEkiOrder,
					iRessyaIndexContIndex,
					pCWndJikokuhyou);
				//運用番号段数-1の分だけ、iYColumnNumberに加算します
				iYColumnNumber += muCdDedEki->get(aCdYColSpec.getEkiOrder()).getJikokuhyouOperationNumberDisplayRows() - 1;
			}
			break;
			case CdYColSpec::ColumnType_EkiRessyasyubetsu:
			{
				if (!aCustomizeJikokuhyouContent.iRessyaIndexCont.empty() &&
					iRessyaIndexContIndex < (int)aCustomizeJikokuhyouContent.iRessyaIndexCont.size() - 1 &&
					aCdYColSpec.getEkiOrder() >= iValidSyuuchakuEki &&
					iValidSyuuchakuEki != -1)
				{
					iRessyaIndexContIndex++;
					pCentDedRessya =
						m_pCentDedRessyaCont->getMuPtr()->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex]);
					iCurrentRessyaShihatsuEkiOrder = iValidSyuuchakuEki;
					iValidSyuuchakuEki = pCentDedRessya->getValidSyuuchakuEki();

					if (aCustomizeJikokuhyouContent.iShiftSecond != 0)
					{
						aCentDedRessya = CentDedRessya(*pCentDedRessya);
						aCentDedRessya.modifyRessyaJikoku(
							aCustomizeJikokuhyouContent.iShiftSecond,
							CdDedJikokuOrder(0, CdDedJikokuOrder::EkiJikokuItem_Chaku));
						pCentDedRessya = &aCentDedRessya;
					}
					//if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Junction &&
					//	m_iEnableOperation > 0)
					//{
					//	iConnectEkiOrder = pCentDedRessya->getLastOperation().getConnectEkiOrder();
					//}
					//iReleaseEkiOrder = -1;
				}
				update02_02_02_21_setRessya_Ressyasyubetsu(
					iXColumnNumber,
					iYColumnNumber,
					pCentDedRessya,
					aCustomizeJikokuhyouContent,
					aCdYColSpec.getEkiOrder(),
					iCurrentRessyaShihatsuEkiOrder,
					iRessyaIndexContIndex,
					pCWndJikokuhyou);
			}
			break;
			case CdYColSpec::ColumnType_EkiRessyamei:
			{
				if (!aCustomizeJikokuhyouContent.iRessyaIndexCont.empty() &&
					iRessyaIndexContIndex < (int)aCustomizeJikokuhyouContent.iRessyaIndexCont.size() - 1 &&
					aCdYColSpec.getEkiOrder() >= iValidSyuuchakuEki &&
					iValidSyuuchakuEki != -1)
				{
					iRessyaIndexContIndex++;
					pCentDedRessya =
						m_pCentDedRessyaCont->getMuPtr()->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex]);
					iCurrentRessyaShihatsuEkiOrder = iValidSyuuchakuEki;
					iValidSyuuchakuEki = pCentDedRessya->getValidSyuuchakuEki();

					if (aCustomizeJikokuhyouContent.iShiftSecond != 0)
					{
						aCentDedRessya = CentDedRessya(*pCentDedRessya);
						aCentDedRessya.modifyRessyaJikoku(
							aCustomizeJikokuhyouContent.iShiftSecond,
							CdDedJikokuOrder(0, CdDedJikokuOrder::EkiJikokuItem_Chaku));
						pCentDedRessya = &aCentDedRessya;
					}
					//if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Junction &&
					//	m_iEnableOperation > 0)
					//{
					//	iConnectEkiOrder = pCentDedRessya->getLastOperation().getConnectEkiOrder();
					//}
					//iReleaseEkiOrder = -1;
				}
				update02_02_02_22_setRessya_Ressyamei(
					iXColumnNumber,
					iYColumnNumber,
					pCentDedRessya,
					aCustomizeJikokuhyouContent,
					aCdYColSpec.getEkiOrder(),
					iCurrentRessyaShihatsuEkiOrder,
					iRessyaIndexContIndex,
					pCWndJikokuhyou);
			}
			break;
			//case CdYColSpec::ColumnType_EkiGousuu:
			//{
			//	if (iRessyaIndexContIndex < (int)aCustomizeJikokuhyouContent.iRessyaIndexCont.size() - 1 &&
			//		aCdYColSpec.getEkiOrder() >= iValidSyuuchakuEki &&
			//		iValidSyuuchakuEki != -1)
			//	{
			//		iRessyaIndexContIndex++;
			//		pCentDedRessya =
			//			m_pCentDedRessyaCont->getMuPtr()->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex]);
			//		iCurrentRessyaShihatsuEkiOrder = iValidSyuuchakuEki;
			//		iValidSyuuchakuEki = pCentDedRessya->getValidSyuuchakuEki();

			//		if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Junction &&
			//			m_iEnableOperation > 0)
			//		{
			//			iConnectEkiOrder = pCentDedRessya->getLastOperation().getConnectEkiOrder();
			//		}
			//		iReleaseEkiOrder = -1;
			//	}
			//	update02_02_02_23_setRessya_Gousuu(
			//		iXColumnNumber,
			//		iYColumnNumber,
			//		pCentDedRessya,
			//		aCustomizeJikokuhyouContent,
			//		aCdYColSpec.getEkiOrder(),
			//		iCurrentRessyaShihatsuEkiOrder,
			//		iConnectEkiOrder,
			//		iReleaseEkiOrder,
			//		pCWndJikokuhyou);
			//}
			//break;
			//case CdYColSpec::ColumnType_EkiGou:
			//{
			//	if (iRessyaIndexContIndex < (int)aCustomizeJikokuhyouContent.iRessyaIndexCont.size() - 1 &&
			//		aCdYColSpec.getEkiOrder() >= iValidSyuuchakuEki &&
			//		iValidSyuuchakuEki != -1)
			//	{
			//		iRessyaIndexContIndex++;
			//		pCentDedRessya =
			//			m_pCentDedRessyaCont->getMuPtr()->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex]);
			//		iCurrentRessyaShihatsuEkiOrder = iValidSyuuchakuEki;
			//		iValidSyuuchakuEki = pCentDedRessya->getValidSyuuchakuEki();

			//		if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Junction &&
			//			m_iEnableOperation > 0)
			//		{
			//			iConnectEkiOrder = pCentDedRessya->getLastOperation().getConnectEkiOrder();
			//		}
			//		iReleaseEkiOrder = -1;
			//	}
			//	update02_02_02_24_setRessya_Gou(
			//		iXColumnNumber,
			//		iYColumnNumber,
			//		pCentDedRessya,
			//		aCdYColSpec.getEkiOrder(),
			//		iCurrentRessyaShihatsuEkiOrder,
			//		iConnectEkiOrder,
			//		iReleaseEkiOrder,
			//		pCWndJikokuhyou);
			//}
			//break;
			case CdYColSpec::ColumnType_Ekijikoku_Hatsu:
			{
				if (!aCustomizeJikokuhyouContent.iRessyaIndexCont.empty() &&
					iRessyaIndexContIndex < (int)aCustomizeJikokuhyouContent.iRessyaIndexCont.size() - 1 &&
					aCdYColSpec.getEkiOrder() >= iValidSyuuchakuEki &&
					iValidSyuuchakuEki != -1)
				{
					iRessyaIndexContIndex++;
					pCentDedRessya =
						m_pCentDedRessyaCont->getMuPtr()->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex]);
					iCurrentRessyaShihatsuEkiOrder = iValidSyuuchakuEki;
					iValidSyuuchakuEki = pCentDedRessya->getValidSyuuchakuEki();

					if (aCustomizeJikokuhyouContent.iShiftSecond != 0)
					{
						aCentDedRessya = CentDedRessya(*pCentDedRessya);
						aCentDedRessya.modifyRessyaJikoku(
							aCustomizeJikokuhyouContent.iShiftSecond,
							CdDedJikokuOrder(0, CdDedJikokuOrder::EkiJikokuItem_Chaku));
						pCentDedRessya = &aCentDedRessya;
					}
					//if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Junction &&
					//	m_iEnableOperation > 0)
					//{
					//	iConnectEkiOrder = pCentDedRessya->getLastOperation().getConnectEkiOrder();
					//}
					//iReleaseEkiOrder = -1;
				}
				update02_02_02_07_setRessya_Hatsu(
					iXColumnNumber,
					iYColumnNumber,
					pCentDedRessya,
					aCustomizeJikokuhyouContent,
					aCdYColSpec.getEkiOrder(),
					iCurrentRessyaShihatsuEkiOrder,
					iRessyaIndexContIndex,
					pCWndJikokuhyou);
			}
			break;
			case CdYColSpec::ColumnType_EkiOuter_Shuchaku1:
			{
				// --------------------------------
				//	(2.2.2.16)セル(ColumnType_Ressya, ColumnType_Outer_Shuchaku)
				// --------------------------------
				if (!aCustomizeJikokuhyouContent.iRessyaIndexCont.empty() &&
					iRessyaIndexContIndex < (int)aCustomizeJikokuhyouContent.iRessyaIndexCont.size() - 1 &&
					aCdYColSpec.getEkiOrder() >= iValidSyuuchakuEki &&
					iValidSyuuchakuEki != -1)
				{
					iRessyaIndexContIndex++;
					pCentDedRessya =
						m_pCentDedRessyaCont->getMuPtr()->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex]);
					iCurrentRessyaShihatsuEkiOrder = iValidSyuuchakuEki;
					iValidSyuuchakuEki = pCentDedRessya->getValidSyuuchakuEki();

					if (aCustomizeJikokuhyouContent.iShiftSecond != 0)
					{
						aCentDedRessya = CentDedRessya(*pCentDedRessya);
						aCentDedRessya.modifyRessyaJikoku(
							aCustomizeJikokuhyouContent.iShiftSecond,
							CdDedJikokuOrder(0, CdDedJikokuOrder::EkiJikokuItem_Chaku));
						pCentDedRessya = &aCentDedRessya;
					}
				}
				update02_02_02_26_setRessya_EkiOuterTerminal_Shuchaku(
					iXColumnNumber,
					iYColumnNumber,
					pCentDedRessya,
					aCustomizeJikokuhyouContent,
					aCdYColSpec.getEkiOrder(),
					iCurrentRessyaShihatsuEkiOrder,
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
					aCustomizeJikokuhyouContent,
					pCWndJikokuhyou);
			}
			break;
		}

		//終着駅名表示は最後に行います。
		int iYColumnNumberShuchakuEkimei = m_CdYColSpecCont.ColumnNumberFromSpec(
			CdYColSpec(CdYColSpec::ColumnType_ShuchakuEkimei), false);
		if (iYColumnNumberShuchakuEkimei >= 0)
		{
			// --------------------------------
			//	(2.2.2.14)セル(ColumnType_Ressya, ColumnType_ShuchakuEkimei)
			// --------------------------------
			update02_02_02_14_setRessya_ShuchakuEkimei(
				iXColumnNumber,
				iYColumnNumberShuchakuEkimei,
				pCentDedRessya,
				aCustomizeJikokuhyouContent,
				pCWndJikokuhyou);
		}
	}
	//種別変更が行われた場合は、終着駅名欄を修正する。pCentDedRessyaは、ここまでくれば末尾になっているはずなので、そのまま渡す
	if ((int)aCustomizeJikokuhyouContent.iRessyaIndexCont.size() > 1)
	{
		int iYColumnNumber = m_CdYColSpecCont.ColumnNumberFromSpec(
			CdYColSpec(CdYColSpec::ColumnType_ShuchakuEkimei),false);
		if (iYColumnNumber >= 0)
		{
			// --------------------------------
			//	(2.2.2.14)セル(ColumnType_Ressya, ColumnType_ShuchakuEkimei)
			// --------------------------------
			update02_02_02_14_setRessya_ShuchakuEkimei(
				iXColumnNumber,
				iYColumnNumber,
				pCentDedRessya,
				aCustomizeJikokuhyouContent,
				pCWndJikokuhyou);
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

void CCellBuilderCustomize::update02_02_01_setRessya_Ressyabangou( 
	int iXColumnNumber ,
	int iYColumnNumber,
	const CentDedRessya* pCentDedRessya ,
	const CustomizeJikokuhyouContent& aCustomizeJikokuhyouContent,
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
			int idxRessyasyubetsu;
			tstring strText;
			if (pCentDedRessya == NULL)
			{
				if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
				{
					idxRessyasyubetsu = aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex;
					strText = aCustomizeJikokuhyouContent.strPrevRessyabangou;
				}
				else
				{
					idxRessyasyubetsu = aCustomizeJikokuhyouContent.iRessyasyubetsuIndex;
					strText = aCustomizeJikokuhyouContent.strRessyabangou;
				}
			}
			else
			{
				idxRessyasyubetsu = pCentDedRessya->getRessyasyubetsuIndex();
				strText = pCentDedRessya->getRessyabangou();
			}
			
			*pCDcDrawCell = createCDcdRessyabangou( idxRessyasyubetsu ) ;
			pCDcDrawCell->setText( strText );
		}

		//セルの背景色を指定します。
		{
			pCDcDrawCell->setCdBrushProp(CdColorProp(255, 255, 255));
		}
	}
}

void CCellBuilderCustomize::update02_02_02_12_setRessya_OperationNumber(
	int iXColumnNumber,
	int iYColumnNumber,
	const CentDedRessya * pCentDedRessya,
	const CustomizeJikokuhyouContent& aCustomizeJikokuhyouContent,
	CWndJikokuhyou * pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	//CDcdTargetGetDC	aCDcdTarget(NULL);
	// --------------------------------
	//CdYColSpec aCdYColSpec(
	//	CdYColSpec::ColumnType_OperationNumber);
	//int iYColumnNumber =
	//	m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec, false);
	int idxRessyasyubetsu;
	vector<tstring> strOperationNumber;
	if (pCentDedRessya == NULL)
	{
		if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
		{
			idxRessyasyubetsu = aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex;
			strOperationNumber = aCustomizeJikokuhyouContent.strPrevOperationNumber;
		}
		else
		{
			idxRessyasyubetsu = aCustomizeJikokuhyouContent.iRessyasyubetsuIndex;
			strOperationNumber = aCustomizeJikokuhyouContent.strOperationNumber;
		}
	}
	else
	{
		idxRessyasyubetsu = pCentDedRessya->getRessyasyubetsuIndex();
		strOperationNumber = pCentDedRessya->getOperationNumber(
			pCentDedRessya->getValidSihatsuEki());
	}
	for (int idx = 0; idx < m_iOperationNumberRows; idx++)
	{
		CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell(
			iXColumnNumber, iYColumnNumber + idx);
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


void CCellBuilderCustomize::update02_02_02_02_setRessya_Ressyasyubetsu( 
	int iXColumnNumber ,
	int iYColumnNumber,
	const CentDedRessya* pCentDedRessya ,
	const CustomizeJikokuhyouContent& aCustomizeJikokuhyouContent,
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
			int idxRessyasyubetsu;
			if (pCentDedRessya == NULL)
			{
				if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
				{
					idxRessyasyubetsu = aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex;
				}
				else
				{
					idxRessyasyubetsu = aCustomizeJikokuhyouContent.iRessyasyubetsuIndex;
				}
			}
			else
			{
				idxRessyasyubetsu = pCentDedRessya->getRessyasyubetsuIndex();
			}

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
			if ((pCentDedRessya != NULL && !pCentDedRessya->isNull() ) ||
				aCustomizeJikokuhyouContent.iRessyasyubetsuIndex != -1 ||
				aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex != -1)
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
	
void CCellBuilderCustomize::update02_02_02_03_setRessya_Ressyamei( 
	int iXColumnNumber ,
	int iYColumnNumber,
	const CentDedRessya* pCentDedRessya ,
	const CustomizeJikokuhyouContent& aCustomizeJikokuhyouContent,
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
			int idxRessyasyubetsu;
			tstring strText ;
			if (pCentDedRessya == NULL)
			{
				if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
				{
					idxRessyasyubetsu = aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex;
					strText = aCustomizeJikokuhyouContent.strPrevRessyamei;
				}
				else
				{
					idxRessyasyubetsu = aCustomizeJikokuhyouContent.iRessyasyubetsuIndex;
					strText = aCustomizeJikokuhyouContent.strRessyamei;
				}
			}
			else
			{
				idxRessyasyubetsu = pCentDedRessya->getRessyasyubetsuIndex();
				if (!pCentDedRessya->isNull())
				{
					strText = pCentDedRessya->getRessyamei();
				}
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
	
void CCellBuilderCustomize::update02_02_02_04_setRessya_Gousuu( 
	int iXColumnNumber ,
	int iYColumnNumber,
	const CentDedRessya* pCentDedRessya ,
	const CustomizeJikokuhyouContent& aCustomizeJikokuhyouContent,
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
			int idxRessyasyubetsu;
			tstring strText;
			if (pCentDedRessya == NULL)
			{
				if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
				{
					idxRessyasyubetsu = aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex;
					strText = aCustomizeJikokuhyouContent.strPrevGousuu;
				}
				else
				{
					idxRessyasyubetsu = aCustomizeJikokuhyouContent.iRessyasyubetsuIndex;
					strText = aCustomizeJikokuhyouContent.strGousuu;
				}
			}
			else
			{
				idxRessyasyubetsu = pCentDedRessya->getRessyasyubetsuIndex();
				if (!pCentDedRessya->isNull())
				{
					strText = pCentDedRessya->getGousuu();
				}
			}
			*pCDcDrawCell = createCDcdRessyabangou( idxRessyasyubetsu );
			pCDcDrawCell->setText( strText );
		}

		//セルの背景色を指定します。
		{
			pCDcDrawCell->setCdBrushProp(CdColorProp(255, 255, 255));
		}
	}
}
	
void CCellBuilderCustomize::update02_02_02_05_setRessya_Gou( 
	int iXColumnNumber ,
	int iYColumnNumber,
	const CentDedRessya* pCentDedRessya ,
	const CustomizeJikokuhyouContent& aCustomizeJikokuhyouContent,
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
			int idxRessyasyubetsu;
			CString	strText;
			if (pCentDedRessya == NULL)
			{
				if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
				{
					idxRessyasyubetsu = aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex;
					if (!aCustomizeJikokuhyouContent.strPrevGousuu.empty())
					{
						strText.LoadString(IDS_WORD_GOUSUU2);
					}
				}
				else
				{
					idxRessyasyubetsu = aCustomizeJikokuhyouContent.iRessyasyubetsuIndex;
					if (!aCustomizeJikokuhyouContent.strGousuu.empty())
					{
						strText.LoadString(IDS_WORD_GOUSUU2);
					}
				}
			}
			else
			{
				idxRessyasyubetsu = pCentDedRessya->getRessyasyubetsuIndex();
				if (!pCentDedRessya->isNull() && !pCentDedRessya->getGousuu().empty())
				{
					strText.LoadString(IDS_WORD_GOUSUU2);
				}
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

void CCellBuilderCustomize::update02_02_02_13_setRessya_ShihatsuEkimei(
	int iXColumnNumber,
	int iYColumnNumber,
	const CentDedRessya * pCentDedRessya,
	const CustomizeJikokuhyouContent& aCustomizeJikokuhyouContent,
	CWndJikokuhyou * pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	const CentDedRosen* pCentDedRosen =
		m_pCDedRosenFileData->getCentDedRosen();
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		pCentDedRosen->getCentDedEkiCont()->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou());
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
				int idxRessyasyubetsu;
				if (pCentDedRessya == NULL)
				{
					if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
					{
						idxRessyasyubetsu = aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex;
					}
					else
					{
						idxRessyasyubetsu = aCustomizeJikokuhyouContent.iRessyasyubetsuIndex;
					}
				}
				else
				{
					idxRessyasyubetsu = pCentDedRessya->getRessyasyubetsuIndex();
				}
				tstring strText;
				if (aCustomizeJikokuhyouContent.iSihatsuEkiOrder >= -2)
				{
					//路線外始発扱い

					if (aCustomizeJikokuhyouContent.iSihatsuEkiOrder < 0)
					{
						strText = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_EkiJikokuhyou_Loop);//"環状"
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
				else if(aCustomizeJikokuhyouContent.iReleaseEkiOrder >= 0)
				{
					//分割列車(当面は分割駅を表示)
					strText = muCdDedEki->get(aCustomizeJikokuhyouContent.iReleaseEkiOrder).getEkimeiJikokuhyouRyaku(true);

				}
				else if (pCentDedRessya != NULL && pCentDedRessya->getValidSihatsuEki() >= 0)
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

void CCellBuilderCustomize::update02_02_02_14_setRessya_ShuchakuEkimei(
	int iXColumnNumber,
	int iYColumnNumber,
	const CentDedRessya * pCentDedRessya,
	const CustomizeJikokuhyouContent& aCustomizeJikokuhyouContent,
	CWndJikokuhyou * pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	const CentDedRosen* pCentDedRosen =
		m_pCDedRosenFileData->getCentDedRosen();
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		pCentDedRosen->getCentDedEkiCont()->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou());
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
				int idxRessyasyubetsu;
				if (pCentDedRessya == NULL)
				{
					if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
					{
						idxRessyasyubetsu = aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex;
					}
					else
					{
						idxRessyasyubetsu = aCustomizeJikokuhyouContent.iRessyasyubetsuIndex;
					}
				}
				else
				{
					idxRessyasyubetsu = pCentDedRessya->getRessyasyubetsuIndex();
				}
				tstring strText;

				if (aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder >= -2)
				{
					//路線外終着扱い
					if (aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder < 0)
					{
						strText = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_EkiJikokuhyou_Loop);//"環状"
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
				else if (pCentDedRessya != NULL && pCentDedRessya->getValidSyuuchakuEki() >= 0)
				{
					if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
					{
						strText = muCdDedEki->get(pCentDedRessya->getValidSyuuchakuEki()).getOuterTerminalJikokuRyaku(
							pCentDedRessya->getLastOperation().getOuterShuchakuekiIndex(),true);
					}
					else
					{
						strText = muCdDedEki->get(pCentDedRessya->getValidSyuuchakuEki()).getEkimeiJikokuhyouRyaku(true);
					}
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

void CCellBuilderCustomize::update02_02_02_27_setRessya_PrevRessyabangou(
	int iXColumnNumber,
	int iYColumnNumber,
	const CentDedRessya* pCentDedRessya,
	const CustomizeJikokuhyouContent& aCustomizeJikokuhyouContent,
	int iEkiOrder,
	int iCurrentRessyaShihatsuEkiOrder,
	int iRessyaIndexContIndex,
	CWndJikokuhyou* pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	const CentDedRosen* pCentDedRosen =
		m_pCDedRosenFileData->getCentDedRosen();
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		pCentDedRosen->getCentDedEkiCont()->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou());
	//CDcdTargetGetDC	aCDcdTarget(NULL);
	// --------------------------------
	//CdYColSpec aCdYColSpec(
	//	CdYColSpec::ColumnType_EkiRessyabangou,
	//	iEkiOrder);
	//int iYColumnNumber =
	//	m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec, false);
	CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell(
		iXColumnNumber, iYColumnNumber);
	// --------------------------------
	//CdDedDispProp	aCdDedDispProp = m_pCDedRosenFileData->getCdDedDispProp() ;
	//tstring strCellExtent( aCdDedDispProp.getJikokuhyouRessyaWidth() , '0' ) ;
	//strCellExtent = セルの大きさの目安となる文字列です。
	//	時刻表列車セルの幅(文字数) CdDedDispProp::m_iJikokuhyouRessyaWidth
	//	の数だけ '0' が並んだ文字列です

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
			CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);
			int idxRessyasyubetsu;
			if (pCentDedRessya == NULL)
			{
				if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
				{
					idxRessyasyubetsu = aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex;
				}
				else
				{
					idxRessyasyubetsu = aCustomizeJikokuhyouContent.iRessyasyubetsuIndex;
				}
			}
			else
			{
				idxRessyasyubetsu = pCentDedRessya->getRessyasyubetsuIndex();
			}
			/**
				この欄に表示するもの
				・pCentDedRessya == NULLの場合
					iReleaseEkiIndex >= 0の場合
						iReleaseEkiIndex < iEkiOrderかつ路線外終着表示駅>=iEkiOrder
							「||」(経由無し)
						それ以外
							空白
					iConnectEkiIndex >= 0の場合
						増結駅の次の駅、増結駅が着時刻のみ表示で、この項が増結駅の直下の場合は↳、
						それ以外は全て空白(この項が、路線外始発表示欄より下になることは無いので、経由なしを表示することもない)

				・iEkiOrder <iValidSihatsuEkiの場合
					iRessyaIndexContIndex >= 1(2列車目以降)の場合
						「||」(経由無し)
					1列車目の場合
						路線外始発(相当)で、iEkiOrder == 路線外始発表示駅
							JikokuhyouPrevRessyabangouDisplayに基づいて、種別名もしくは空白表示(ここでは↓は無し)
						iReleaseEkiOrder >= 0かつ　iReleaseEkiOrder < iEkiOrderr(iReleaseEkiOrder = iEkiOrderの場合は、この項は↴よりも上にあるので空白)
							「||」(経由無し)
				・iValidSihatsuEki == iEkiOrder
					路線外始発相当の場合
					getPrevJikokuhyouRessyabangouDisplayが3の場合：種別名
					2列車目以降で、
						2の場合：aCustomizeJikokuhyouContent.eEBeforeTypeを見て、種別変更・列車情報変更なら種別名
						1の場合：aCustomizeJikokuhyouContent.eEBeforeTypeを見て、種別変更なら種別名
						それ以外は空白
				・iValidSihatsuEki<iEkiOrder<iValidSyuuchakuEki
					isRunbetweenがtrueの場合または、
					getJikokuhyouChakujikokuDisplayがfalseかつisRunbetween(-1)がtrueの場合、表示有りとなる。
						※発時刻のみ表示で、前駅→当駅が運行あり、当駅→次駅が運行なし(経由なし)の場合は、
						当駅の発時刻欄(この欄より下部)に、経由なしを超えた先の発時刻を表示するので、
						この欄が経由なしだと表示が合わないので。
						getJikokuhyouRessyabangouDisplayが3の場合:列車番号
						2/1の場合:「↓」
					その他の場合
						「||」
				・iValidSyuuchakuEki == iEkiOrder
					空白
				・iValidSyuuchakuEki < iEkiOrder
					路線外終着(相当)で路線外終着欄がこの駅かこれより下にある場合「||」
					iConnectEkiOrder >= iEkiOrderの場合「||」

			*/
			* pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
			tstring strText = _T("");
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
						strText = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"

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
								strText = (LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_CONNECT);
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
						strText = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
					}
					//iCurrentRessyaShihatsuEkiOrder < 0(1列車目)
					else if (aCustomizeJikokuhyouContent.iSihatsuEkiOrder >= -2 &&
						m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0 &&
						m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] == iEkiOrder)
					{
						//路線外始発相当で、この駅が路線外始発表示駅の場合
						idxRessyasyubetsu = aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex;
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
						strText = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
					}
				}
				else if (iValidSihatsuEki == iEkiOrder)
				{
					//2列車目以降かつ、1列車目の終着駅との間に、経由なしがある場合
					if (iCurrentRessyaShihatsuEkiOrder >= 0 &&
						iCurrentRessyaShihatsuEkiOrder < iEkiOrder)
					{
						strText = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
					}
					//路線外始発相当かつ、始発駅にこの項がある場合は、路線外始発表示も当然この駅にあるので、前列車接続タイプに基づいて表示を行う
					else if (aCustomizeJikokuhyouContent.iSihatsuEkiOrder >= -2)
					{
						idxRessyasyubetsu = aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex;

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
						strText = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
					}
				}
				else if (iValidSyuuchakuEki < iEkiOrder)
				{
					if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer &&
						m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0 &&
						m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= iEkiOrder)
					{
						//路線外終着
						strText = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
					}
					else if (aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder >= -2 &&
						m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0 &&
						m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= iEkiOrder)
					{
						//路線外終着相当
						//書式を次列車の種別にします
						*pCDcDrawCell = createCDcdRessyabangou(aCustomizeJikokuhyouContent.iRessyasyubetsuIndex);
						strText = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);

					}
					else if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= iEkiOrder &&
						aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
					{
						strText = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
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
							strText = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_CONNECT);
						}
					}
				}
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

void CCellBuilderCustomize::update02_02_02_28_setRessya_PrevOperationNumber(
	int iXColumnNumber,
	int iYColumnNumber,
	const CentDedRessya* pCentDedRessya,
	const CustomizeJikokuhyouContent& aCustomizeJikokuhyouContent,
	int iEkiOrder,
	int iCurrentRessyaShihatsuEkiOrder,
	int iRessyaIndexContIndex,
	CWndJikokuhyou* pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	const CentDedRosen* pCentDedRosen =
		m_pCDedRosenFileData->getCentDedRosen();
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		pCentDedRosen->getCentDedEkiCont()->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou());
	//CDcdTargetGetDC	aCDcdTarget(NULL);
	// --------------------------------
	//CdYColSpec aCdYColSpec(
	//	CdYColSpec::ColumnType_EkiOperationNumber,
	//	iEkiOrder);
	//int iYColumnNumber =
	//	m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec, false);
	int idxRessyasyubetsu;
	if (pCentDedRessya == NULL)
	{
		if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
		{
			idxRessyasyubetsu = aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex;
		}
		else
		{
			idxRessyasyubetsu = aCustomizeJikokuhyouContent.iRessyasyubetsuIndex;
		}
	}
	else
	{
		idxRessyasyubetsu = pCentDedRessya->getRessyasyubetsuIndex();
	}
	CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);
	//0:空白、1:運番、2:経由なし、3:↓、4:分割、5:併合
	int iDisplayType = 0;
	vector<tstring> strOperationNumber;
	/**
		この欄に表示するもの
	・pCentDedRessya == NULLの場合
		iReleaseEkiIndex >= 0の場合
			iReleaseEkiIndex < iEkiOrderかつ路線外終着表示駅>=iEkiOrder
				「||」(経由無し)
			それ以外
				空白
		iConnectEkiIndex >= 0の場合
			増結駅の次の駅、増結駅が着時刻のみ表示で、この項が増結駅の直下の場合は↳、
			それ以外は全て空白(この項が、路線外始発表示欄より下になることは無いので、経由なしを表示することもない)

	・iEkiOrder < iValidSihatsuEki
		2列車目以降
			「||」(経由無し)
		路線外始発相当で、iEkiOrder == 路線外始発表示駅
			JikokuhyouPrevOperationNumberDisplayに基づいて、運用番号もしくは空白表示(ここでは↓は無し)
		分割列車で分割駅と始発駅の間の場合
			「||」(経由無し)
	・iValidSihatsuEki == iEkiOrder
		getJikokuhyouPrevOperationNumberDisplayが4の場合：運用番号
		3の場合：aCustomizeJikokuhyouContent.eEBeforeTypeを見て、種別変更・列車情報変更なら運用番号。それ以外は空白。
		2の場合：aCustomizeJikokuhyouContent.eEBeforeTypeを見て、種別変更なら運用番号。それ以外は空白。
		1の場合：aCustomizeJikokuhyouContent.strPrevOperationNumberとこの駅を発車するときの運用番号を比較して、異なる場合は表示。それ以外は空白。
	・iValidSihatsuEki<iEkiOrder<iValidSyuuchakuEki
		isRunbetweenがfalseの場合は「||」(経由無し)、それ以外は空白
	・iValidSyuuchakuEki == iEkiOrder
		空白
	・iValidSyuuchakuEki < iEkiOrder
		路線外終着かつこの駅が表示駅もしくはそれより下の場合:「||」
		路線外終着相当かつこの駅が表示駅もしくはそれより下の場合:「||」(次列車の種別で表示)
		iEkiOrder <= iConnectEkiIndex
			「||」(経由無し)


	*/
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
				idxRessyasyubetsu = aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex;
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
				idxRessyasyubetsu = aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex;
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
				//書式を次列車の種別にします
				idxRessyasyubetsu = aCustomizeJikokuhyouContent.iRessyasyubetsuIndex;
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

	for (int idx = 0; idx < aCdDedEki.getJikokuhyouPrevOperationNumberDisplayRows(); idx++)
	{
		CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell(
			iXColumnNumber, iYColumnNumber + idx);
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
					else if (idx == aCdDedEki.getJikokuhyouPrevOperationNumberDisplayRows() - 1)
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
					strText = (LPCTSTR)MfcUtil::LoadCString(
						IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
				}
				else if (iDisplayType == 3)
				{
					strText = _T("↓";)
				}
				else if (iDisplayType == 4 &&
					idx == aCdDedEki.getJikokuhyouPrevOperationNumberDisplayRows() - 1)
				{
					strText = (LPCTSTR)MfcUtil::LoadCString(
						IDS_WORD_JIKOKUHYOU_RELEASE);
				}
				else if (iDisplayType == 5 &&
					idx == 0)
				{
					strText = (LPCTSTR)MfcUtil::LoadCString(
						IDS_WORD_JIKOKUHYOU_CONNECT);
				}
				*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
				pCDcDrawCell->setText(strText);

				//セルの背景色を指定します。
				{
					pCDcDrawCell->setCdBrushProp(CdColorProp(255, 255, 255));
				}
			}
		}
	}
}


void CCellBuilderCustomize::update02_02_02_29_setRessya_PrevRessyasyubetsu(
	int iXColumnNumber,
	int iYColumnNumber,
	const CentDedRessya* pCentDedRessya,
	const CustomizeJikokuhyouContent& aCustomizeJikokuhyouContent,
	int iEkiOrder,
	int iCurrentRessyaShihatsuEkiOrder,
	int iRessyaIndexContIndex,
	CWndJikokuhyou* pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	const CentDedRosen* pCentDedRosen =
		m_pCDedRosenFileData->getCentDedRosen();
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		pCentDedRosen->getCentDedEkiCont()->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou());
	// --------------------------------
	//CDcdTargetGetDC	aCDcdTarget(NULL);
	// --------------------------------
	//CdYColSpec aCdYColSpec(
	//	CdYColSpec::ColumnType_EkiRessyasyubetsu,
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
			CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);
			int idxRessyasyubetsu;
			if (pCentDedRessya == NULL)
			{
				if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
				{
					idxRessyasyubetsu = aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex;
				}
				else
				{
					idxRessyasyubetsu = aCustomizeJikokuhyouContent.iRessyasyubetsuIndex;
				}
			}
			else
			{
				idxRessyasyubetsu = pCentDedRessya->getRessyasyubetsuIndex();
			}
			const CentDedRessyasyubetsu* pCentDedRessyasyubetsu = NULL;
			{
				pCentDedRessyasyubetsu =
					pCentDedRosen->getCentDedRessyasyubetsuCont()->getMuPtr()
					->get(idxRessyasyubetsu);
				if (m_bDisplayParentSyubetsu && pCentDedRessyasyubetsu->getParentSyubetsuIndex() >= 0)
				{
					pCentDedRessyasyubetsu
						= pCentDedRosen->getCentDedRessyasyubetsuCont()->getMuPtr()
						->get(pCentDedRessyasyubetsu->getParentSyubetsuIndex());
				}
				if (pCentDedRessyasyubetsu == NULL)
				{
					pCentDedRessyasyubetsu =
						pCentDedRosen->getCentDedRessyasyubetsuCont()
						->getMuPtr()->get(0);
				}
			}
			//pCentDedRessyasyubetsu = 列車種別オブジェクト
			//	(指定がないなら、列車種別[0])

			tstring strRessyasyubetsu;
			if (pCentDedRessya == NULL || !pCentDedRessya->isNull())
			{
				strRessyasyubetsu = pCentDedRessyasyubetsu->getRyakusyou();
			}
			/**
				この欄に表示するもの
				・pCentDedRessya == NULLの場合
					iReleaseEkiIndex >= 0の場合
						iReleaseEkiIndex < iEkiOrderかつ路線外終着表示駅>=iEkiOrder
							「||」(経由無し)
						それ以外
							空白
					iConnectEkiIndex >= 0の場合
						増結駅の次の駅、増結駅が着時刻のみ表示で、この項が増結駅の直下の場合は↳、
						それ以外は全て空白(この項が、路線外始発表示欄より下になることは無いので、経由なしを表示することもない)


				・iEkiOrder <iValidSihatsuEkiの場合
					iRessyaIndexContIndex >= 1(2列車目以降)の場合
						「||」(経由無し)
					1列車目の場合
						路線外始発相当で、iEkiOrder == 路線外始発表示駅
							JikokuhyouPrevRessyaSyubetsuDisplayに基づいて、種別名もしくは空白表示(ここでは↓は無し)
						iReleaseEkiOrder >= 0かつ　iReleaseEkiOrder < iEkiOrder(iReleaseEkiOrder = iEkiOrderの場合は、この項は↴よりも上にあるので空白)
							「||」(経由無し)
				・iValidSihatsuEki == iEkiOrder
					路線外始発相当の場合
					getPrevJikokuhyouRessyasyubetsuDisplayが3の場合：種別名
					2の場合：aCustomizeJikokuhyouContent.eEBeforeTypeを見て、種別変更・列車情報変更なら種別名
					1の場合：aCustomizeJikokuhyouContent.eEBeforeTypeを見て、種別変更なら種別名
					それ以外は空白
				・iValidSihatsuEki<iEkiOrder<iValidSyuuchakuEki
					isRunbetweenがfalseの場合は「||」(経由無し)、それ以外は空白
				・iValidSyuuchakuEki == iEkiOrder
					空白
				・iValidSyuuchakuEki < iEkiOrder
					路線外終着(相当)で路線外終着欄がこの駅かこれより下にある場合「||」
					iConnectEkiOrder >= iEkiOrderの場合「||」

			*/
			tstring strText = _T("");
			*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu);
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
						*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
						strText = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"

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
								*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
								strText = (LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_CONNECT);
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
						*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
						strText = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
					}
					//iCurrentRessyaShihatsuEkiOrder < 0(1列車目)
					else if (aCustomizeJikokuhyouContent.iSihatsuEkiOrder >= -2 &&
						m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0 &&
						m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] == iEkiOrder)
					{
						//路線外始発相当で、この駅が路線外始発表示駅の場合
						idxRessyasyubetsu = aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex;
						{
							pCentDedRessyasyubetsu =
								pCentDedRosen->getCentDedRessyasyubetsuCont()->getMuPtr()
								->get(idxRessyasyubetsu);
							if (m_bDisplayParentSyubetsu && pCentDedRessyasyubetsu->getParentSyubetsuIndex() >= 0)
							{
								pCentDedRessyasyubetsu
									= pCentDedRosen->getCentDedRessyasyubetsuCont()->getMuPtr()
									->get(pCentDedRessyasyubetsu->getParentSyubetsuIndex());
							}
							if (pCentDedRessyasyubetsu == NULL)
							{
								pCentDedRessyasyubetsu =
									pCentDedRosen->getCentDedRessyasyubetsuCont()
									->getMuPtr()->get(0);
							}
						}

						strRessyasyubetsu = pCentDedRessyasyubetsu->getRyakusyou();
						*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu);

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
						*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
						strText = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
					}
				}
				else if (iValidSihatsuEki == iEkiOrder)
				{
					//2列車目以降かつ、1列車目の終着駅との間に、経由なしがある場合
					if (iCurrentRessyaShihatsuEkiOrder >= 0 &&
						iCurrentRessyaShihatsuEkiOrder < iEkiOrder)
					{
						*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
						strText = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
					}
					//路線外始発相当かつ、始発駅にこの項がある場合は、路線外始発表示も当然この駅にあるので、前列車接続タイプに基づいて表示を行う
					else if (aCustomizeJikokuhyouContent.iSihatsuEkiOrder >= -2)
					{
						idxRessyasyubetsu = aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex;
						{
							pCentDedRessyasyubetsu =
								pCentDedRosen->getCentDedRessyasyubetsuCont()->getMuPtr()
								->get(idxRessyasyubetsu);
							if (m_bDisplayParentSyubetsu && pCentDedRessyasyubetsu->getParentSyubetsuIndex() >= 0)
							{
								pCentDedRessyasyubetsu
									= pCentDedRosen->getCentDedRessyasyubetsuCont()->getMuPtr()
									->get(pCentDedRessyasyubetsu->getParentSyubetsuIndex());
							}
							if (pCentDedRessyasyubetsu == NULL)
							{
								pCentDedRessyasyubetsu =
									pCentDedRosen->getCentDedRessyasyubetsuCont()
									->getMuPtr()->get(0);
							}
						}

						strRessyasyubetsu = pCentDedRessyasyubetsu->getRyakusyou();
						*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu);

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
						*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
						strText = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
					}
				}
				else if (iValidSyuuchakuEki < iEkiOrder)
				{
					if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer &&
						m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0 &&
						m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= iEkiOrder)
					{
						//路線外終着
						*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
						strText = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
					}
					else if (aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder >= -2 &&
						m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0 &&
						m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= iEkiOrder)
					{
						//路線外終着相当
						//書式を次列車の種別にします
						*pCDcDrawCell = createCDcdRessyabangou(aCustomizeJikokuhyouContent.iRessyasyubetsuIndex);
						strText = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"

					}
					else if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= iEkiOrder &&
						aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
					{
						*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
						strText = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
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
							*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
							strText = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_CONNECT);
						}
					}
				}
			}
			pCDcDrawCell->setText(strText);
		}

		//セルの背景色を指定します。
		{
			pCDcDrawCell->setCdBrushProp(CdColorProp(255, 255, 255));
		}
	}

}

void CCellBuilderCustomize::update02_02_02_30_setRessya_PrevRessyamei(
	int iXColumnNumber,
	int iYColumnNumber,
	const CentDedRessya* pCentDedRessya,
	const CustomizeJikokuhyouContent& aCustomizeJikokuhyouContent,
	int iEkiOrder,
	int iCurrentRessyaShihatsuEkiOrder,
	int iRessyaIndexContIndex,
	CWndJikokuhyou* pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	const CentDedRosen* pCentDedRosen =
		m_pCDedRosenFileData->getCentDedRosen();
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		pCentDedRosen->getCentDedEkiCont()->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou());
	// --------------------------------
	//CDcdTargetGetDC	aCDcdTarget(NULL);
	// --------------------------------
	//CdYColSpec aCdYColSpec(
	//	CdYColSpec::ColumnType_EkiRessyamei,
	//	iEkiOrder);
	//int iYColumnNumber =
	//	m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec, false);
	CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell(
		iXColumnNumber, iYColumnNumber);
	int iYColumnNumber2 = iYColumnNumber + 1;
	int iYColumnNumber3 = iYColumnNumber + 2;
	CDcdGridCell* pCDcdGridCell2 = pCDcdGrid->getCell(
		iXColumnNumber, iYColumnNumber2);
	CDcdGridCell* pCDcdGridCell3 = pCDcdGrid->getCell(
		iXColumnNumber, iYColumnNumber3);

	// --------------------------------
	if (pCDcdGridCell != 0)
	{
		typedef CDcdTextboxV3 CDcDrawCellV;
		Ou<CDcDrawCellV> pCDcDrawCell;
		typedef CDcdTextbox CDcDrawCell;
		Ou<CDcDrawCell> pCDcDrawCell2;
		Ou<CDcDrawCell> pCDcDrawCell3;
		// --------------------------------
		//　(2.2.*.1)　セル(ColumnType_Ressya,ColumnType_Ressyabangou) の
		//	結合セルを設定
		pCDcdGridCell->setAttachCellCount(1, 1);
		pCDcdGridCell2->setAttachCellCount(1, 1);
		pCDcdGridCell3->setAttachCellCount(1, 1);

		//　(2.2.*.2)　セル の	DcDrawオブジェクトの型を設定
		//	( CDcdTextbox とする)。
		{
			pCDcDrawCell = dynamic_castOu<CDcDrawCellV>(
				pCDcdGridCell->getIfDcDraw());
			if (pCDcDrawCell == NULL)
			{
				pCDcDrawCell = OuNew<CDcDrawCellV>(new CDcDrawCellV);
				pCDcdGridCell->setIfDcDraw(pCDcDrawCell);
			}
			pCDcDrawCell2 = dynamic_castOu<CDcDrawCell>(
				pCDcdGridCell2->getIfDcDraw());
			if (pCDcDrawCell2 == NULL)
			{
				pCDcDrawCell2 = OuNew<CDcDrawCell>(new CDcDrawCell);
				pCDcdGridCell2->setIfDcDraw(pCDcDrawCell2);
			}
			pCDcDrawCell3 = dynamic_castOu<CDcDrawCell>(
				pCDcdGridCell3->getIfDcDraw());
			if (pCDcDrawCell3 == NULL)
			{
				pCDcDrawCell3 = OuNew<CDcDrawCell>(new CDcDrawCell);
				pCDcdGridCell3->setIfDcDraw(pCDcDrawCell3);
			}
		}
		//　(2.2.*.3)　セルの DcDrawオブジェクトに、属性を設定。
		{
			CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);
			int idxRessyasyubetsu;
			if (pCentDedRessya == NULL)
			{
				if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
				{
					idxRessyasyubetsu = aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex;
				}
				else
				{
					idxRessyasyubetsu = aCustomizeJikokuhyouContent.iRessyasyubetsuIndex;
				}
			}
			else
			{
				idxRessyasyubetsu = pCentDedRessya->getRessyasyubetsuIndex();
			}
			//tstring strText;
			//if (!pCentDedRessya->isNull())
			//{
			//	strText = pCentDedRessya->getRessyamei();
			//}
			/**
				この欄に表示するもの
				・pCentDedRessya == NULLの場合
					iReleaseEkiIndex >= 0の場合
						「空白」
					iConnectEkiIndex >= 0の場合
						増結駅の次の駅、増結駅が着時刻のみ表示で、この項が増結駅の直下の場合は↳、
						それ以外は全て空白(この項が、路線外始発表示欄より下になることは無いので、経由なしを表示することもない)

				・iEkiOrder <iValidSihatsuEkiの場合
					1列車目の場合
						路線外始発相当で、iEkiOrder == 路線外始発表示駅
							JikokuhyouPrevRessyameiDisplayに基づいて、種別名もしくは空白表示(ここでは↓は無し)
				・iValidSihatsuEki == iEkiOrder
					路線外始発相当の場合
					getPrevJikokuhyouRessyameiDisplayが3の場合：列車名
					2の場合：aCustomizeJikokuhyouContent.eEBeforeTypeを見て、種別変更・列車情報変更なら列車名
					1の場合：aCustomizeJikokuhyouContent.eEBeforeTypeを見て、種別変更なら列車名
					それ以外は空白
			*/
			tstring strText = _T("");
			tstring strText2 = _T("");
			tstring strText3 = _T("");
			bool bDisplayConnect = false;
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
								strText = (LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_CONNECT);
								bDisplayConnect = true;
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
						idxRessyasyubetsu = aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex;
						if (aCdDedEki.getJikokuhyouPrevRessyameiDisplay() == 3)
						{
							strText = aCustomizeJikokuhyouContent.strPrevRessyamei;
							strText2 = aCustomizeJikokuhyouContent.strPrevGousuu;
							if (!strText2.empty())
							{
								strText3 = (LPCTSTR)MfcUtil::LoadCString(IDS_WORD_GOUSUU2);
							}
						}
						else if (aCustomizeJikokuhyouContent.eEBeforeType == EBeforeAfterType::BeforeAfterType_ClassChange)
						{
							strText = aCustomizeJikokuhyouContent.strPrevRessyamei;
							strText2 = aCustomizeJikokuhyouContent.strPrevGousuu;
							if (!strText2.empty())
							{
								strText3 = (LPCTSTR)MfcUtil::LoadCString(IDS_WORD_GOUSUU2);
							}
						}
						else if (aCustomizeJikokuhyouContent.eEBeforeType == EBeforeAfterType::BeforeAfterType_PropertyChange &&
							aCdDedEki.getJikokuhyouPrevRessyameiDisplay() == 2)
						{
							strText = aCustomizeJikokuhyouContent.strPrevRessyamei;
							strText2 = aCustomizeJikokuhyouContent.strPrevGousuu;
							if (!strText2.empty())
							{
								strText3 = (LPCTSTR)MfcUtil::LoadCString(IDS_WORD_GOUSUU2);
							}
						}
					}
				}
				else if (iValidSihatsuEki == iEkiOrder)
				{
					//路線外始発相当かつ、始発駅にこの項がある場合は、路線外始発表示も当然この駅にあるので、前列車接続タイプに基づいて表示を行う
					if (aCustomizeJikokuhyouContent.iSihatsuEkiOrder >= -2)
					{
						idxRessyasyubetsu = aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex;
						if (aCdDedEki.getJikokuhyouPrevRessyameiDisplay() == 3)
						{
							strText = aCustomizeJikokuhyouContent.strPrevRessyamei;
							strText2 = aCustomizeJikokuhyouContent.strPrevGousuu;
							if (!strText2.empty())
							{
								strText3 = (LPCTSTR)MfcUtil::LoadCString(IDS_WORD_GOUSUU2);
							}
						}
						else if (aCustomizeJikokuhyouContent.eEBeforeType == EBeforeAfterType::BeforeAfterType_ClassChange)
						{
							strText = aCustomizeJikokuhyouContent.strPrevRessyamei;
							strText2 = aCustomizeJikokuhyouContent.strPrevGousuu;
							if (!strText2.empty())
							{
								strText3 = (LPCTSTR)MfcUtil::LoadCString(IDS_WORD_GOUSUU2);
							}
						}
						else if (aCustomizeJikokuhyouContent.eEBeforeType == EBeforeAfterType::BeforeAfterType_PropertyChange &&
							aCdDedEki.getJikokuhyouPrevRessyameiDisplay() == 2)
						{
							strText = aCustomizeJikokuhyouContent.strPrevRessyamei;
							strText2 = aCustomizeJikokuhyouContent.strPrevGousuu;
							if (!strText2.empty())
							{
								strText3 = (LPCTSTR)MfcUtil::LoadCString(IDS_WORD_GOUSUU2);
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
							strText = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_CONNECT);
							bDisplayConnect = true;
						}
					}
				}
			}
			if (bDisplayConnect)
			{
				Ou<CDcDrawCell> pCDcDrawCell1;
				pCDcDrawCell1 = dynamic_castOu<CDcDrawCell>(
					pCDcdGridCell->getIfDcDraw());
				if (pCDcDrawCell1 == NULL)
				{
					pCDcDrawCell1 = OuNew<CDcDrawCell>(new CDcDrawCell);
					pCDcdGridCell->setIfDcDraw(pCDcDrawCell1);
				}
				*pCDcDrawCell1 = createCDcdRessyabangou(idxRessyasyubetsu);
				CdDrawTextProp aCdDrawTextProp = pCDcDrawCell1->getCdDrawTextProp();
				aCdDrawTextProp.setCdDrawTextFormat(
					CdDrawTextFormat(CdDrawTextFormat::H_CENTER, CdDrawTextFormat::EVertical::V_SINGLELINT_TOP));
				pCDcDrawCell1->setCdDrawTextProp(aCdDrawTextProp);
				pCDcDrawCell1->setText(strText);
			}
			else
			{
				*pCDcDrawCell = createCDcdRessyamei(idxRessyasyubetsu);
				pCDcDrawCell->setText(strText);
			}
			*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);
			pCDcDrawCell2->setText(strText2);
			*pCDcDrawCell3 = createCDcdRessyabangou(idxRessyasyubetsu);
			pCDcDrawCell3->setText(strText3);
		}

		//セルの背景色を指定します。
		{
			pCDcDrawCell->setCdBrushProp(CdColorProp(255, 255, 255));
		}
	}


}

void CCellBuilderCustomize::update02_02_02_25_setRessya_EkiOuterTerminal_Shihatsu(
	int iXColumnNumber,
	int iYColumnNumber,
	const CentDedRessya * pCentDedRessya,
	const CustomizeJikokuhyouContent& aCustomizeJikokuhyouContent,
	int iEkiOrder,
	int iCurrentRessyaShihatsuEkiOrder,
	CWndJikokuhyou * pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	const CentDedRosen* pCentDedRosen =
		m_pCDedRosenFileData->getCentDedRosen();
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		pCentDedRosen->getCentDedEkiCont()->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou());
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
			iXColumnNumber, iYColumnNumber + 1);
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
				int idxRessyasyubetsu;
				if (pCentDedRessya == NULL)
				{
					if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
					{
						idxRessyasyubetsu = aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex;
					}
					else
					{
						idxRessyasyubetsu = aCustomizeJikokuhyouContent.iRessyasyubetsuIndex;
					}
				}
				else
				{
					idxRessyasyubetsu = pCentDedRessya->getRessyasyubetsuIndex();
				}
				*pCDcDrawCell1 = createCDcdRessyabangou(idxRessyasyubetsu);
				*pCDcDrawCell2 = createCDcdEkijikoku(idxRessyasyubetsu);
				tstring strText1;
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
							strText1 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_EkiJikokuhyou_Loop);//"環状"
						}
						else if (aCustomizeJikokuhyouContent.iOuterShihatsuEkiIndex >= 0)
						{
							strText1 = muCdDedEki->get(aCustomizeJikokuhyouContent.iSihatsuEkiOrder).getOuterTerminalJikokuRyaku(
								aCustomizeJikokuhyouContent.iOuterShihatsuEkiIndex, true);
						}
						else
						{
							strText1 = muCdDedEki->get(aCustomizeJikokuhyouContent.iSihatsuEkiOrder).getEkimeiJikokuhyouRyaku(true);
						}
						CdDedJikoku aCdDedJikoku
							= aCustomizeJikokuhyouContent.OuterShihatsuJikoku;
						strText2 = getCdDedJikokuConv().encode(aCdDedJikoku, false);
					}
					/**
						この列が分割表示の場合、分割表示が有効・この駅が分割駅よりも下・この駅が分割表示駅であるかここよりも上ならば、
						この項には経由なしを表示する。
					*/
					else if (aCustomizeJikokuhyouContent.iReleaseEkiOrder >= 0 &&
						iEkiOrder > aCustomizeJikokuhyouContent.iReleaseEkiOrder &&
						iEkiOrder <= m_iOuterShuchakuDisplayEkiOrder[aCustomizeJikokuhyouContent.iReleaseEkiOrder])
					{

						strText1 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
						strText2 = strText1;//"||"
						*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);
					}
				}
				else
				{
					int iValidSihatsuEki = pCentDedRessya->getValidSihatsuEki();
					int iValidSyuuchakuEki = pCentDedRessya->getValidSyuuchakuEki();
					if (iValidSihatsuEki == -1 || iValidSyuuchakuEki == -1)
					{
						strText1 = _T("");
						strText2 = _T("");
					}
					else if (iEkiOrder <= iValidSihatsuEki)
					{
						if (iCurrentRessyaShihatsuEkiOrder >= 0/* &&
							iEkiOrder < iValidSihatsuEki*/)
						{
							strText1 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
							strText2 = strText1;//"||"
							*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);
						}
						/**
							(2)のパターン　pCentDedRessyaの始発駅Orderで
							m_iOuterShihatsuDisplayEkiOrderから路線外始発表示駅を取得し、
							それが当駅ならば、ここで路線外始発表示を行う
							Ver2.06.21 表示書式を、前列車の種別に変更する
						*/
						else if (aCustomizeJikokuhyouContent.iSihatsuEkiOrder >= -2 &&
							iEkiOrder == m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki])
						{
							if (aCustomizeJikokuhyouContent.iSihatsuEkiOrder < 0)
							{
								strText1 = (LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_EkiJikokuhyou_Loop);//"環状"
							}
							else if (aCustomizeJikokuhyouContent.iOuterShihatsuEkiIndex >= 0)
							{
								strText1 = muCdDedEki->get(aCustomizeJikokuhyouContent.iSihatsuEkiOrder).getOuterTerminalJikokuRyaku(
									aCustomizeJikokuhyouContent.iOuterShihatsuEkiIndex, true);
							}
							else
							{
								strText1 = muCdDedEki->get(aCustomizeJikokuhyouContent.iSihatsuEkiOrder).getEkimeiJikokuhyouRyaku(true);
							}
							CdDedJikoku aCdDedJikoku
								= aCustomizeJikokuhyouContent.OuterShihatsuJikoku;
							strText2 = getCdDedJikokuConv().encode(aCdDedJikoku, false);

							idxRessyasyubetsu = aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex;
							*pCDcDrawCell1 = createCDcdRessyabangou(idxRessyasyubetsu);
							*pCDcDrawCell2 = createCDcdEkijikoku(idxRessyasyubetsu);
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
							strText1 = aCdDedEki.getOuterTerminalJikokuRyaku(aFirstOperation.getOuterShihatsuekiIndex(), true);
							if (!(aFirstOperation.getOuterShihatsuJikoku().isNull()))
							{
								CdDedJikoku aCdDedJikoku
									= aFirstOperation.getOuterShihatsuJikoku();
								strText2 = getCdDedJikokuConv().encode(aCdDedJikoku, false);
							}
						}
						else if (aCustomizeJikokuhyouContent.iReleaseEkiOrder < iEkiOrder &&
							aCustomizeJikokuhyouContent.iReleaseEkiOrder >= 0)
						{
							strText1 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
							strText2 = strText1;//"||"
							*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);
						}
					}
					else if (iValidSihatsuEki < iEkiOrder &&
						iEkiOrder <= iValidSyuuchakuEki)
					{
						if (!pCentDedRessya->isRunBetweenNextEki(iEkiOrder - 1))
						{
							strText1 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
							strText2 = strText1;//"||"
							*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);
						}
					}
					else if (iValidSyuuchakuEki < iEkiOrder)
					{
						if(pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer&&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= iEkiOrder)
						{
							strText1 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
							strText2 = strText1;//"||"
							*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);
						}
						else if (aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder >= -2 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= iEkiOrder)
						{
							//Ver2.06.21 表示書式を、次列車の種別に変更する
							idxRessyasyubetsu = aCustomizeJikokuhyouContent.iRessyasyubetsuIndex;
							strText1 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
							strText2 = strText1;//"||"
							*pCDcDrawCell1 = createCDcdRessyabangou(idxRessyasyubetsu);
							*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);
						}
						else if (aCustomizeJikokuhyouContent.iConnectEkiOrder > iEkiOrder &&
							aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
						{
							strText1 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
							strText2 = strText1;//"||"
							*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);
						}
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

void CCellBuilderCustomize::update02_02_02_06_setRessya_Chaku( 
	int iXColumnNumber ,
	int iYColumnNumber,
	const CentDedRessya* pCentDedRessya ,
	const CustomizeJikokuhyouContent& aCustomizeJikokuhyouContent,
	int iEkiOrder ,
	int iCurrentRessyaShihatsuEkiOrder,
	int iRessyaIndexContIndex,
	CWndJikokuhyou* pCWndJikokuhyou ) 
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid() ;
	const CentDedRosen* pCentDedRosen = 
		m_pCDedRosenFileData->getCentDedRosen() ;
	const CentDedEkiCont* pCentDedEkiCont =
		pCentDedRosen->getCentDedEkiCont();
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki = 
		pCentDedEkiCont->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou()) ;
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

				int idxRessyasyubetsu;
				if (pCentDedRessya == NULL)
				{
					if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
					{
						idxRessyasyubetsu = aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex;
					}
					else
					{
						idxRessyasyubetsu = aCustomizeJikokuhyouContent.iRessyasyubetsuIndex;
					}
				}
				else
				{
					idxRessyasyubetsu = pCentDedRessya->getRessyasyubetsuIndex();
				}
				
				//	主要駅では、空欄に主要駅表記を行います。
				//	起点・終点・着発駅のいずれかである場合、
				//	境界線に接している駅である場合は除きます。
				bool bIsSyuyouEkiHyouki = false ;
				if ( aCdDedEki.getEkikibo() == CentDedEki::EEkikibo::Ekikibo_Syuyou 
					&&	0 < iEkiOrder 
					&& iEkiOrder < muCdDedEki->size() - 1 
					&& (!aCdDedEki.getJikokuhyouChakuJikokuDisplay() ||
						!aCdDedEki.getJikokuhyouHatsuJikokuDisplay()))
				{
					//	境界線に接している駅である場合は除きます。
					CentDedEkiCont::CdDedEki aCentDedEkiPrev = muCdDedEki->get( iEkiOrder - 1 ) ;

					if (!aCentDedEkiPrev.getKyoukaisen() &&
						!aCdDedEki.getKyoukaisen())
					{
						bIsSyuyouEkiHyouki = true;
					}
				}

				//bIsSyuyouEkiHyouji = 空欄に主要駅表記を行います。
				*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
				if (bIsSyuyouEkiHyouki)
				{
					//	主要駅での表記（着発の場合は除く）
					//	"----"
					pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
						IDS_WORD_JIKOKUHYOU_UNKOUNASI_SYUYOU));
				}
				else
				{
					//	その他の駅での表記
					//	"・・"
					pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
						IDS_WORD_JIKOKUHYOU_UNKOUNASI_IPPAN));
				}

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
									pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
										IDS_WORD_JIKOKUHYOU_RELEASE));
								}
							}
						}
						else if (iEkiOrder == aCustomizeJikokuhyouContent.iReleaseEkiOrder)
						{
							pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_RELEASE));
						}
						else if (iEkiOrder > aCustomizeJikokuhyouContent.iReleaseEkiOrder &&
							iEkiOrder <= m_iOuterShuchakuDisplayEkiOrder[aCustomizeJikokuhyouContent.iReleaseEkiOrder])
						{
							pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"

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
									pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
										IDS_WORD_JIKOKUHYOU_CONNECT));
								}
							}
						}
						else if (iEkiOrder == aCustomizeJikokuhyouContent.iConnectEkiOrder)
						{
							tstring strText = getCdDedJikokuConv().encode(aCustomizeJikokuhyouContent.ChakuJikoku, true);

							*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu,
								aCustomizeJikokuhyouContent.ePrevEkiatsukai);
							pCDcDrawCell->setText(strText);
						}
						else if (iEkiOrder >= m_iOuterShihatsuDisplayEkiOrder[aCustomizeJikokuhyouContent.iConnectEkiOrder] &&
							iEkiOrder < aCustomizeJikokuhyouContent.iConnectEkiOrder)
						{
							pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI));
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
						//・・または----のまま
					}
					else if (iEkiOrder < iValidSihatsuEki)
					{
						if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] <= iEkiOrder)
						{
							//路線外始発
							pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"

						}
						else if (aCustomizeJikokuhyouContent.iSihatsuEkiOrder >= -2 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] <= iEkiOrder)
						{
							//路線外始発相当
							//Ver2.06.21 この場合は、セルの書式を前列車種別のものにする

							*pCDcDrawCell = createCDcdRessyabangou(aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex);
							pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"
						}
						else if (iCurrentRessyaShihatsuEkiOrder != -1)
						{
							//一体化の2列車目以降(前の列車との間に、経由なし区間がある場合)
							pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"
						}
						else if (iEkiOrder == aCustomizeJikokuhyouContent.iReleaseEkiOrder)
						{
							/**
								発時刻表示の有無にかかわらず、この欄に「↴」を表示する
							*/
							pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_RELEASE));
						}
						else if (aCustomizeJikokuhyouContent.iReleaseEkiOrder < iEkiOrder && 
							aCustomizeJikokuhyouContent.iReleaseEkiOrder >= 0)
						{
							pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"
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
								!m_bDisplayTsuukaEkiJikoku)
							{
								if (aCdDedEki.getJikokuhyouHatsuJikokuDisplay())
								{
									pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
										IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"
								}
								else
								{
									aCdDedJikoku = aCentDedEkiJikoku.getHatsujikoku();
									tstring strText = getCdDedJikokuConv().encode(aCdDedJikoku, false);
									*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu,
										CentDedEkiJikoku::Ekiatsukai_Tsuuka);
									pCDcDrawCell->setText(strText);

								}
							}
							else
							{
								/**
									秒単位表示OFFの場合は、切り上げ・切り捨ての処理を行いますが、
									その補助のため、着時刻が切り上げで、発時刻が30秒以上切り上げまたは切り捨ての場合は、発時刻の取得を行います。
								*/
								CdDedJikoku aHatsuJikoku;
								if (!getDisplaySecondEkiJikoku() &&
									m_iSecondRoundChaku == 2 &&
									m_iSecondRoundHatsu <= 1)
								{
									aHatsuJikoku = aCentDedEkiJikoku.getVirtualHatsujikoku();
								}

								tstring strText = getCdDedJikokuConv().encode(
									pCentDedRessya->getFirstOperation().getChakuJikoku(), true, aHatsuJikoku);
								*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu,
									aCentDedEkiJikoku.getEkiatsukai());
								pCDcDrawCell->setText(strText);
							}
						}
						else if (aCustomizeJikokuhyouContent.iSihatsuEkiOrder >= -2 &&
							iRessyaIndexContIndex == 0 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0)
						{
							//路線外始発相当
							//Ver2.06.21 この場合は、セルの書式を前列車種別のものにする

							if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka &&
								!m_bDisplayTsuukaEkiJikoku)
							{
								*pCDcDrawCell = createCDcdRessyabangou(aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex);
								pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"
							}
							else
							{
								/**
									秒単位表示OFFの場合は、切り上げ・切り捨ての処理を行いますが、
									その補助のため、着時刻が切り上げで、発時刻が30秒以上切り上げまたは切り捨ての場合は、発時刻の取得を行います。
								*/
								CdDedJikoku aHatsuJikoku;
								if (!getDisplaySecondEkiJikoku() &&
									m_iSecondRoundChaku == 2 &&
									m_iSecondRoundHatsu <= 1)
								{
									aHatsuJikoku = aCentDedEkiJikoku.getVirtualHatsujikoku();
								}

								tstring strText = getCdDedJikokuConv().encode(
									aCustomizeJikokuhyouContent.ChakuJikoku, true, aHatsuJikoku);

								idxRessyasyubetsu = aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex;
								*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu,
									aCentDedEkiJikoku.getEkiatsukai());
								pCDcDrawCell->setText(strText);
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
								!m_bDisplayTsuukaEkiJikoku)
							{
								//運転停車かつ通過駅時刻非表示の場合、発時刻表示が無い場合はレ印を、ある場合は経由なし表示とします。
								if (aCdDedEki.getJikokuhyouHatsuJikokuDisplay())
								{
									pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
										IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"
								}
								else//if(!aCdDedEki.getJikokuhyouHatsuJikokuDisplay())
								{
									pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
										IDS_WORD_JIKOKUHYOU_TSUUKA));	//" ﾚ"
								}
							}
							else if (!aCdDedJikoku.isNull())
							{
								const CentDedRessya* pPrevRessya =
									m_pCentDedRessyaCont->getMuPtr()->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex - 1]);
								CdDedJikoku aChakuJikoku = pPrevRessya->getCentDedEkiJikoku(pPrevRessya->getValidSyuuchakuEki()).getVirtualChakujikoku();
								
								/**
									秒単位表示OFFの場合は、切り上げ・切り捨ての処理を行いますが、
									その補助のため、着時刻が切り上げで、発時刻が30秒以上切り上げまたは切り捨ての場合、発時刻の取得を行います。(着時刻表示時)
								*/
								CdDedJikoku aHatsuJikoku;
								if (!getDisplaySecondEkiJikoku() &&
									m_iSecondRoundChaku == 2 &&
									m_iSecondRoundHatsu <= 1)
								{
									aHatsuJikoku = aCentDedEkiJikoku.getVirtualHatsujikoku();
								}

								tstring strText = getCdDedJikokuConv().encode(aChakuJikoku, true, aHatsuJikoku);
								*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu,
									aCentDedEkiJikoku.getEkiatsukai());
								pCDcDrawCell->setText(strText);
							}
							else if (aCdDedEki.getJikokuhyouHatsuJikokuDisplay())
							{
								pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"
							}
							else//if(!aCdDedEki.getJikokuhyouHatsuJikokuDisplay())
							{
								/**
									秒単位表示OFFの場合は、切り上げ・切り捨ての処理を行いますが、
									その補助のため、着時刻が30秒以上切り上げまたは切り上げで、発時刻が切り捨ての場合、
									前列車の終着駅着時刻の取得を行います。(発時刻表示)
								*/
								CdDedJikoku aChakuJikoku;
								if (!getDisplaySecondEkiJikoku() &&
									m_iSecondRoundChaku >= 1 &&
									m_iSecondRoundHatsu == 0)
								{
									const CentDedRessya* pPrevRessya =
										m_pCentDedRessyaCont->getMuPtr()->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex - 1]);
									aChakuJikoku = pPrevRessya->getCentDedEkiJikoku(pPrevRessya->getValidSyuuchakuEki()).getVirtualChakujikoku();
								}
								CdDedJikoku aHatsuJikoku = aCentDedEkiJikoku.getVirtualHatsujikoku();
								tstring strText = getCdDedJikokuConv().encode(aHatsuJikoku, false, aChakuJikoku);
								*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu,
									aCentDedEkiJikoku.getEkiatsukai());
								pCDcDrawCell->setText(strText);
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
							pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"
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
							//if (aCdDedEki.getJikokuhyouHatsuJikokuDisplay())
							//{
							pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_RELEASE));
							//}
							//else if (iEkiOrder != 0)
							//{
							//	int iYColumnNumberPrev = iYColumnNumber - 1;
							//	//CdYColSpec aCdYColSpec = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberPrev);

							//	CDcdGridCell* pCDcdGridCellPrev = pCDcdGrid->getCell(
							//		iXColumnNumber, iYColumnNumberPrev);
							//	if (pCDcdGridCellPrev != 0)
							//	{
							//		//typedef CDcdTextbox CDcDrawCell;
							//		Ou<CDcDrawCell> pCDcDrawCellPrev;
							//		pCDcdGridCellPrev->setAttachCellCount(1, 1);

							//		pCDcDrawCellPrev = dynamic_castOu<CDcDrawCell>(
							//			pCDcdGridCellPrev->getIfDcDraw());
							//		if (pCDcDrawCellPrev == NULL)
							//		{
							//			pCDcDrawCellPrev = OuNew<CDcDrawCell>(new CDcDrawCell);
							//			pCDcdGridCellPrev->setIfDcDraw(pCDcDrawCellPrev);
							//		}
							//		*pCDcDrawCellPrev = createCDcdRessyabangou(idxRessyasyubetsu);
							//		pCDcDrawCellPrev->setText(_T("↴"));//"||"
							//	}
							//}
						}
						//この駅が着時刻のみ表示の場合は、着時刻欄に発時刻を表示する
						else if (!aCdDedEki.getJikokuhyouHatsuJikokuDisplay())
						{
							aCdDedJikoku = aCentDedEkiJikoku.getVirtualHatsujikoku();
							tstring strText = getCdDedJikokuConv().encode(aCdDedJikoku, false);
							*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu,
								aCentDedEkiJikoku.getEkiatsukai());
							pCDcDrawCell->setText(strText);
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
								!m_bDisplayTsuukaEkiJikoku &&
								m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0)
							{
								//路線外表示スペースがない場合は、レ印ではなく時刻を表示する。
								pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_TSUUKA));	//" ﾚ"
							}
							else
							{
								CdDedJikoku aHatsuJikoku = pCentDedRessya->getLastOperation().getHatsuJikoku();
								//当駅発時刻を確認、時刻がない場合、駅扱い通過の時は通過とみなす(運転停車ではない)
								if (!aHatsuJikoku.isNull())
								{
									aCdDedJikoku = aCentDedEkiJikoku.getVirtualChakujikoku();
								}

								tstring strText = getCdDedJikokuConv().encode(aCdDedJikoku, true, aHatsuJikoku);
								*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu,
									aCentDedEkiJikoku.getEkiatsukai());
								pCDcDrawCell->setText(strText);
							}
						}
						else if (iRessyaIndexContIndex == aCustomizeJikokuhyouContent.iRessyaIndexCont.size() -1 &&
							aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder >= -2)
						{
							//路線外終着相当
							if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka &&
								!m_bDisplayTsuukaEkiJikoku &&
								m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0)
							{
								//路線外表示スペースがない場合は、レ印ではなく時刻を表示する。
								pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_TSUUKA));	//" ﾚ"
							}
							else
							{
								CdDedJikoku aHatsuJikoku = aCustomizeJikokuhyouContent.HatsuJikoku;
								aCdDedJikoku = aCentDedEkiJikoku.getVirtualChakujikoku();

								tstring strText = getCdDedJikokuConv().encode(aCdDedJikoku, true, aHatsuJikoku);
								*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu,
									aCentDedEkiJikoku.getEkiatsukai());
								pCDcDrawCell->setText(strText);
							}
						}
						else if (iRessyaIndexContIndex < (int)aCustomizeJikokuhyouContent.iRessyaIndexCont.size() - 1)
						{
							//次列車あり
							if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka &&
								!m_bDisplayTsuukaEkiJikoku)
							{
								pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_TSUUKA));	//" ﾚ"
							}
							else
							{
								/**
									秒単位表示OFFの場合は、切り上げ・切り捨ての処理を行いますが、
									その補助のため、着時刻が切り上げで、発時刻が30秒以上切り上げまたは切り捨ての場合、
									次列車の始発駅発時刻の取得を行います。(着時刻表示時)
								*/
								CdDedJikoku aHatsuJikoku;
								if (!getDisplaySecondEkiJikoku() &&
									m_iSecondRoundChaku == 2 &&
									m_iSecondRoundHatsu <= 1)
								{
									const CentDedRessya* pNextRessya =
										m_pCentDedRessyaCont->getMuPtr()->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex + 1]);
									aHatsuJikoku = pNextRessya->getCentDedEkiJikoku(pNextRessya->getValidSihatsuEki()).getVirtualHatsujikoku();
								}
								aCdDedJikoku = aCentDedEkiJikoku.getVirtualChakujikoku();

								tstring strText = getCdDedJikokuConv().encode(aCdDedJikoku, true, aHatsuJikoku);
								*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu,
									aCentDedEkiJikoku.getEkiatsukai());
								pCDcDrawCell->setText(strText);
							}

						}
						else
						{
							aCdDedJikoku = aCentDedEkiJikoku.getVirtualChakujikoku(); 

							tstring strText = getCdDedJikokuConv().encode(aCdDedJikoku, true);
							*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu,
								aCentDedEkiJikoku.getEkiatsukai());
							pCDcDrawCell->setText(strText);
						}
					}
					else if (iEkiOrder > iValidSyuuchakuEki)
					{
						if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer&& 
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= iEkiOrder)
						{
							//路線外終着
							pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"

						}
						else if (aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder >= -2 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= iEkiOrder)
						{
							//路線外終着相当
							//Ver2.06.21 この場合は、セルの書式を次列車種別のものにする
							*pCDcDrawCell = createCDcdRessyabangou(aCustomizeJikokuhyouContent.iRessyasyubetsuIndex);
							pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"

						}
						else if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= iEkiOrder && 
							aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
						{
							if (aCustomizeJikokuhyouContent.iConnectEkiOrder == iEkiOrder &&
								!aCdDedEki.getJikokuhyouHatsuJikokuDisplay())
							{
								pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_CONNECT));
							}
							else
							{
								pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"
							}
						}
						/**
							有効終着駅の次の駅で、この列車が路線外終着ではない、路線外終着相当ではない、もしくは路線外終着欄がない時、
							この欄のすぐ上が発時刻欄かつ着時刻表示がない場合、
							この欄に"===="を描写します
							Ver2.05 この欄のすぐ上が着時刻欄かつ、場合を追加(着時刻欄の場合は、自ずと発時刻表示無しとなる)
								"前駅との間に境界線がない"条件も追加
							Ver2.06.03
								路線外発着(相当)の検出が誤っていたのを修正、併合の場合は表示しないように修正
						*/
						if (iEkiOrder == iValidSyuuchakuEki + 1 &&
							((pCentDedRessya->getLastOperation().getAOperation() != CentDedAfterOperation::EAOperation::AOperation_Outer &&
								aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder < -2 &&
								aCustomizeJikokuhyouContent.iConnectEkiOrder < 0) ||
								m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] < 0))
						{
							CdYColSpec aCdYColSpecPrev = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumber - 1);
							CentDedEkiCont::CdDedEki aCdDedEkiPrev = muCdDedEki->get(iEkiOrder - 1);
							if (aCdYColSpecPrev.getEkiOrder() == iEkiOrder - 1 &&
								!aCdDedEkiPrev.getKyoukaisen() &&
								((aCdYColSpecPrev.getColumnType() == CdYColSpec::ColumnType_Ekijikoku_Hatsu &&
								!aCdDedEkiPrev.getJikokuhyouChakuJikokuDisplay()) ||
								aCdYColSpecPrev.getColumnType() == CdYColSpec::ColumnType_Ekijikoku_Chaku))
							{
								//pCDcDrawCell->setText(_T("===="));
								pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_SYUUCHAKU));
							}
						}
					}
					//中間駅の場合
					else
					{
						if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_None)
						{
							pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"
						}
						else if (pCentDedRessya->isRunBetweenNextEki(iEkiOrder - 1))
						{
							if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka &&
								!m_bDisplayTsuukaEkiJikoku)
							{
								pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_TSUUKA));	//" ﾚ"
							}
							else if (aCdDedJikoku.isNull())
							{
								//着時刻がない場合、この駅と次の駅の間が運行ありの場合は、通過の場合はレ印、停車の場合は発時刻または○印を表示します
								if (pCentDedRessya->isRunBetweenNextEki(iEkiOrder))
								{
									if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
									{
										pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
											IDS_WORD_JIKOKUHYOU_TSUUKA));	//" ﾚ"
									}
									else if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya)
									{
										CdDedJikoku aHatsuJikoku = aCentDedEkiJikoku.getVirtualHatsujikoku();
										if(!aHatsuJikoku.isNull() &&
											!aCdDedEki.getJikokuhyouHatsuJikokuDisplay())
										{
											//	時刻が設定されているかつ発時刻表示が無い場合は時刻を表示
											*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu);
											tstring strText = getCdDedJikokuConv().encode(aHatsuJikoku, false);
											pCDcDrawCell->setText(strText);
										}
										else
										{
											pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
												IDS_WORD_JIKOKUHYOU_TEISYA));
										}
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
										tstring strText = getCdDedJikokuConv().encode(aHatsuJikoku, false);
										*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu,
											aCentDedEkiJikoku.getEkiatsukai());
										pCDcDrawCell->setText(strText);
									}
									else//if (aHatsuJikoku.isNull())
									{
										if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
										{
											pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
												IDS_WORD_JIKOKUHYOU_TSUUKA));	//" ﾚ"
										}
										else if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya)
										{
											pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
												IDS_WORD_JIKOKUHYOU_TEISYA));
										}

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
								if (!getDisplaySecondEkiJikoku() &&
									m_iSecondRoundChaku == 2 &&
									m_iSecondRoundHatsu <= 1)
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

								tstring strText = getCdDedJikokuConv().encode(aCdDedJikoku, true, aHatsuJikoku);
								*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu,
									aCentDedEkiJikoku.getEkiatsukai());
								pCDcDrawCell->setText(strText);
							}
						}
						else if(pCentDedRessya->isRunBetweenNextEki(iEkiOrder))
						{
							//この駅と前の駅の間が運行なし、この駅と次の駅の間が運行ありの場合
							if (aCdDedEki.getJikokuhyouHatsuJikokuDisplay())
							{
								//この駅が発着表示の場合、基本的には経由なし表示になります。
								//ただし、この駅に発着両時刻が設定されている場合、起点側着時刻を取得して表示します
								if (aCdDedJikoku.isNull() ||aCentDedEkiJikoku.getHatsujikoku().isNull())
								{
									pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
										IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"
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
									if (!getDisplaySecondEkiJikoku() &&
										m_iSecondRoundChaku == 2 &&
										m_iSecondRoundHatsu <= 1)
									{
										aHatsuJikoku = aCentDedEkiJikoku.getVirtualHatsujikoku();
									}

									if (aChakuJikoku.isNull())
									{
										pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
											IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"
									}
									else
									{
										tstring strText = getCdDedJikokuConv().encode(aChakuJikoku, true, aHatsuJikoku);

										*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu,
											aCentDedEkiJikoku.getEkiatsukai());
										pCDcDrawCell->setText(strText);
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
										tstring strText = getCdDedJikokuConv().encode(aChakuJikoku, true);
										*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu,
											aCentDedEkiJikoku.getEkiatsukai());
										pCDcDrawCell->setText(strText);
									}
									else//if (aChakuJikoku.isNull())
									{
										if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
										{
											pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
												IDS_WORD_JIKOKUHYOU_TSUUKA));	//" ﾚ"
										}
										else if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya)
										{
											pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
												IDS_WORD_JIKOKUHYOU_TEISYA));
										}

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
									if (!getDisplaySecondEkiJikoku() &&
										m_iSecondRoundChaku >= 1 &&
										m_iSecondRoundHatsu == 0)
									{
										int iChakuEkiOrder = pCentDedRessya->getRunBetweenEkiBackward(iEkiOrder);
										if (pCentDedEkiCont->isSameBrunchLoopGroup(iEkiOrder, iChakuEkiOrder, pCentDedRessya->getRessyahoukou()))
										{
											aChakuJikoku = pCentDedRessya->getCentDedEkiJikoku(iChakuEkiOrder).getVirtualChakujikoku();
										}
									}

									tstring strText = getCdDedJikokuConv().encode(aHatsuJikoku, false, aChakuJikoku);
									*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu,
										aCentDedEkiJikoku.getEkiatsukai());
									pCDcDrawCell->setText(strText);
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
										tstring strText = getCdDedJikokuConv().encode(aChakuJikoku, true, aHatsuJikoku);
										*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu,
											aCentDedEkiJikoku.getEkiatsukai());
										pCDcDrawCell->setText(strText);
									}
									else// (aChakuJikoku.isNull())
									{
										tstring strText = getCdDedJikokuConv().encode(aHatsuJikoku, false);
										*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu,
											aCentDedEkiJikoku.getEkiatsukai());
										pCDcDrawCell->setText(strText);
									}
								}
							}
						}
						else//if (!pCentDedRessya->isRunBetweenNextEki(iEkiOrder-1)&&!pCentDedRessya->isRunBetweenNextEki(iEkiOrder))
						{
							//この駅の前後ともに運行なし(経由なし)の場合、この項は経由なし表示となります。

							pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"
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
								pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_RELEASE));
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
								pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_CONNECT));
							}
						}
					}
				}

				//セルの背景色を指定します。
				pCDcDrawCell->setCdBrushProp(getBackColor(
					iXColumnNumber,
					iEkiOrder,
					idxRessyasyubetsu));
			}
		}
	}
}

void CCellBuilderCustomize::update02_02_02_31_setRessya_Nyuusen(
	int iXColumnNumber,
	int iYColumnNumber,
	const CentDedRessya* pCentDedRessya,
	const CustomizeJikokuhyouContent& aCustomizeJikokuhyouContent,
	int iEkiOrder,
	int iCurrentRessyaShihatsuEkiOrder,
	int iRessyaIndexContIndex,
	CWndJikokuhyou* pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	const CentDedRosen* pCentDedRosen =
		m_pCDedRosenFileData->getCentDedRosen();
	const CentDedEkiCont* pCentDedEkiCont =
		pCentDedRosen->getCentDedEkiCont();
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		pCentDedEkiCont->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou());
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
				CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);

				int idxRessyasyubetsu;
				if (pCentDedRessya == NULL)
				{
					if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
					{
						idxRessyasyubetsu = aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex;
					}
					else
					{
						idxRessyasyubetsu = aCustomizeJikokuhyouContent.iRessyasyubetsuIndex;
					}
				}
				else
				{
					idxRessyasyubetsu = pCentDedRessya->getRessyasyubetsuIndex();
				}

				*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
				tstring strText = _T("");
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
									strText = (LPCTSTR)MfcUtil::LoadCString(
										IDS_WORD_JIKOKUHYOU_RELEASE);
								}
							}
						}
						else if (iEkiOrder > aCustomizeJikokuhyouContent.iReleaseEkiOrder &&
							iEkiOrder <= m_iOuterShuchakuDisplayEkiOrder[aCustomizeJikokuhyouContent.iReleaseEkiOrder])
						{
							strText = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"

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
									strText = (LPCTSTR)MfcUtil::LoadCString(
										IDS_WORD_JIKOKUHYOU_CONNECT);
								}
							}
						}
						//else if (iEkiOrder == aCustomizeJikokuhyouContent.iConnectEkiOrder)
						//{
						//	tstring strText = getCdDedJikokuConv().encode(aCustomizeJikokuhyouContent.ChakuJikoku, true);

						//	*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu,
						//		aCustomizeJikokuhyouContent.ePrevEkiatsukai);
						//	pCDcDrawCell->setText(strText);
						//}
						else if (iEkiOrder >= m_iOuterShihatsuDisplayEkiOrder[aCustomizeJikokuhyouContent.iConnectEkiOrder] &&
							iEkiOrder < aCustomizeJikokuhyouContent.iConnectEkiOrder)
						{
							strText = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);
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
							strText = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"

						}
						else if (aCustomizeJikokuhyouContent.iSihatsuEkiOrder >= -2 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] <= iEkiOrder)
						{
							//路線外始発相当
							//Ver2.06.21 この場合は、セルの書式を前列車種別のものにする

							*pCDcDrawCell = createCDcdRessyabangou(aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex);
							strText = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
						}
						else if (iCurrentRessyaShihatsuEkiOrder != -1)
						{
							//一体化の2列車目以降(前の列車との間に、経由なし区間がある場合)
							strText = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
						}
						//else if (iEkiOrder == aCustomizeJikokuhyouContent.iReleaseEkiOrder)
						//{
						//	/**
						//		発時刻表示の有無にかかわらず、この欄に「↴」を表示する
						//	*/
						//	pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
						//		IDS_WORD_JIKOKUHYOU_RELEASE));
						//}
						else if (aCustomizeJikokuhyouContent.iReleaseEkiOrder < iEkiOrder &&
							aCustomizeJikokuhyouContent.iReleaseEkiOrder >= 0)
						{
							strText = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
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
								strText = (LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
							}
						}
						else if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0)
						{
							if (m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] < iEkiOrder)
							{
								strText = (LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
							}
						}
						else if (aCustomizeJikokuhyouContent.iSihatsuEkiOrder >= -2 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0)
						{
							if (m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] < iEkiOrder)
							{
								strText = (LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
							}
						}
						else if (aCustomizeJikokuhyouContent.iReleaseEkiOrder >= 0)
						{
							if (aCustomizeJikokuhyouContent.iReleaseEkiOrder < iEkiOrder)
							{
								strText = (LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
							}
							else if (aCustomizeJikokuhyouContent.iReleaseEkiOrder == iEkiOrder &&
								!aCdDedEki.getJikokuhyouChakuJikokuDisplay())
							{
								strText = (LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_RELEASE);
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
								strText = getCdDedJikokuConv().encode(aCdDedJikoku, false);
								*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu);
							}
						}
					}
					else if (iValidSihatsuEki < iEkiOrder &&
						iEkiOrder < iValidSyuuchakuEki)
					{
						if (!pCentDedRessya->isRunBetweenNextEki(iEkiOrder - 1))
						{
							strText = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
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
							strText = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"

						}
						else if (aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder >= -2 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= iEkiOrder)
						{
							//路線外終着相当
							//Ver2.06.21 この場合は、セルの書式を次列車種別のものにする
							*pCDcDrawCell = createCDcdRessyabangou(aCustomizeJikokuhyouContent.iRessyasyubetsuIndex);
							strText = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"

						}
						else if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= iEkiOrder &&
							aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
						{
							strText = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
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
								strText = (LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_CONNECT);
							}
						}
					}
				}

				pCDcDrawCell->setText(strText);

				//セルの背景色を指定します。
				pCDcDrawCell->setCdBrushProp(CdColorProp(255, 255, 255));
			}
		}
	}
}

void CCellBuilderCustomize::update02_02_02_09_setRessya_Track(
	int iXColumnNumber,
	int iYColumnNumber,
	const CentDedRessya * pCentDedRessya,
	const CustomizeJikokuhyouContent& aCustomizeJikokuhyouContent,
	int iEkiOrder,
	int iCurrentRessyaShihatsuEkiOrder,
	CWndJikokuhyou * pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	const CentDedRosen* pCentDedRosen =
		m_pCDedRosenFileData->getCentDedRosen();
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		pCentDedRosen->getCentDedEkiCont()->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou());
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
				CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);
				int idxRessyasyubetsu;
				if (pCentDedRessya == NULL)
				{
					if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
					{
						idxRessyasyubetsu = aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex;
					}
					else
					{
						idxRessyasyubetsu = aCustomizeJikokuhyouContent.iRessyasyubetsuIndex;
					}
				}
				else
				{
					idxRessyasyubetsu = pCentDedRessya->getRessyasyubetsuIndex();
				}
				*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);

				tstring strText = _T("");
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
									strText = (LPCTSTR)MfcUtil::LoadCString(
										IDS_WORD_JIKOKUHYOU_RELEASE);
								}
							}
						}
						else if (iEkiOrder == aCustomizeJikokuhyouContent.iReleaseEkiOrder)
						{
							CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);
							CentDedEkiTrack2Cont aCentDedEkiTrack2Cont = aCdDedEki.getCentDedEkiTrack2Cont();

							strText = aCentDedEkiTrack2Cont.get(
								aCustomizeJikokuhyouContent.iRessyaTrackIndex).getTrackRyakusyou(m_pCentDedRessyaCont->getRessyahoukou());
						}
						else if (iEkiOrder > aCustomizeJikokuhyouContent.iReleaseEkiOrder &&
							iEkiOrder <= m_iOuterShuchakuDisplayEkiOrder[aCustomizeJikokuhyouContent.iReleaseEkiOrder])
						{
							strText = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"

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
									strText = (LPCTSTR)MfcUtil::LoadCString(
										IDS_WORD_JIKOKUHYOU_CONNECT);
								}
							}
						}
						else if (iEkiOrder == aCustomizeJikokuhyouContent.iConnectEkiOrder)
						{
							CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);
							CentDedEkiTrack2Cont aCentDedEkiTrack2Cont = aCdDedEki.getCentDedEkiTrack2Cont();

							strText = aCentDedEkiTrack2Cont.get(
								aCustomizeJikokuhyouContent.iPrevRessyaTrackIndex).getTrackRyakusyou(m_pCentDedRessyaCont->getRessyahoukou());
						}
						else if (iEkiOrder >= m_iOuterShihatsuDisplayEkiOrder[aCustomizeJikokuhyouContent.iConnectEkiOrder] &&
							iEkiOrder < aCustomizeJikokuhyouContent.iConnectEkiOrder)
						{
							strText = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
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
							strText = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
						}
						else if (aCustomizeJikokuhyouContent.iSihatsuEkiOrder >= -2 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] <= iEkiOrder)
						{
							//路線外始発相当
							//Ver2.06.21 この場合は、セルの書式を前列車種別のものにする

							*pCDcDrawCell = createCDcdRessyabangou(aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex);
							strText = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
						}
						else if (iCurrentRessyaShihatsuEkiOrder >= 0)
						{
							strText = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
						}
						else if (aCustomizeJikokuhyouContent.iReleaseEkiOrder == iEkiOrder &&
							aCdDedEki.getJikokuhyouChakuJikokuDisplay())
						{
							strText = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
						}
						else if (aCustomizeJikokuhyouContent.iReleaseEkiOrder < iEkiOrder && 
							aCustomizeJikokuhyouContent.iReleaseEkiOrder >= 0)
						{
							strText = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
						}
					}
					else if (iEkiOrder > iValidSyuuchakuEki)
					{
						if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= iEkiOrder)
						{
							//路線外終着
							strText = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
						}
						else if (aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder >= -2 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= iEkiOrder)
						{
							//路線外終着相当
							//Ver2.06.21 この場合は、セルの書式を次列車種別のものにする
							*pCDcDrawCell = createCDcdRessyabangou(aCustomizeJikokuhyouContent.iRessyasyubetsuIndex);
							strText = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"

						}
						else if (aCustomizeJikokuhyouContent.iConnectEkiOrder > iEkiOrder && 
							aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
						{
							strText = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
						}
						else if (aCustomizeJikokuhyouContent.iConnectEkiOrder == iEkiOrder &&
							aCdDedEki.getJikokuhyouHatsuJikokuDisplay())
						{
							strText = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
						}
					}
					else if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_None)
					{
						//始発駅から終着駅の間は、運行なし駅に経由なしマークを表示します
						strText = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
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
						strText = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
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
								strText = (LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_RELEASE);
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
								strText = (LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_CONNECT);
							}
						}
					}
				}

				pCDcDrawCell->setText(strText);
			}
		}
	}
}

void CCellBuilderCustomize::update02_02_02_19_setRessya_Ressyabangou(
	int iXColumnNumber,
	int iYColumnNumber,
	const CentDedRessya* pCentDedRessya,
	const CustomizeJikokuhyouContent& aCustomizeJikokuhyouContent,
	int iEkiOrder,
	int iCurrentRessyaShihatsuEkiOrder,
	int iRessyaIndexContIndex,
	CWndJikokuhyou* pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	const CentDedRosen* pCentDedRosen =
		m_pCDedRosenFileData->getCentDedRosen();
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		pCentDedRosen->getCentDedEkiCont()->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou());
	//CDcdTargetGetDC	aCDcdTarget(NULL);
	// --------------------------------
	//CdYColSpec aCdYColSpec(
	//	CdYColSpec::ColumnType_EkiRessyabangou,
	//	iEkiOrder);
	//int iYColumnNumber =
	//	m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec, false);
	CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell(
		iXColumnNumber, iYColumnNumber);
	// --------------------------------
	//CdDedDispProp	aCdDedDispProp = m_pCDedRosenFileData->getCdDedDispProp() ;
	//tstring strCellExtent( aCdDedDispProp.getJikokuhyouRessyaWidth() , '0' ) ;
	//strCellExtent = セルの大きさの目安となる文字列です。
	//	時刻表列車セルの幅(文字数) CdDedDispProp::m_iJikokuhyouRessyaWidth
	//	の数だけ '0' が並んだ文字列です

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
			CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);
			int idxRessyasyubetsu;
			if (pCentDedRessya == NULL)
			{
				if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
				{
					idxRessyasyubetsu = aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex;
				}
				else
				{
					idxRessyasyubetsu = aCustomizeJikokuhyouContent.iRessyasyubetsuIndex;
				}
			}
			else
			{
				idxRessyasyubetsu = pCentDedRessya->getRessyasyubetsuIndex();
			}
			/**
				この欄に表示するもの
				・pCentDedRessya == NULLの場合
					iReleaseEkiIndex >= 0の場合
						iReleaseEkiIndex == iEkiOrder
							3の場合列車番号、それ以外は↓
						iReleaseEkiIndex < iEkiOrderかつ路線外終着表示駅>=iEkiOrder
							「||」(経由無し)
						それ以外
							分割駅の前の駅、分割駅が発時刻のみ表示で、この項が分割駅の直上の場合は↴、それ以外は空白
					iConnectEkiIndex >= 0の場合
						iConnectEkiIndex == iEkiOrder
							空白
						iConnectEkiIndex > iEkiOrderかつ路線外始発表示駅<=iEkiOrder
							「||」(経由無し)
						それ以外
							解結駅の次の駅、解結駅が着時刻のみ表示で、この項が解結駅の直下の場合は↳、それ以外は空白

				・iEkiOrder <iValidSihatsuEkiの場合
					iRessyaIndexContIndex >= 1(2列車目以降)の場合
						iEkiOrder == iCurrentRessyaShihatsuEkiOrder(前列車の終着駅)で、この駅の発時刻欄に時刻が表示されている場合は空白
						それ以外は「||」(経由無し)
					1列車目の場合
						路線外始発(相当)で、iEkiOrder >= 路線外始発表示駅
							「||」(経由無し)
						iReleaseEkiOrder >= 0かつ　iReleaseEkiOrder <= iEkiOrder
							「||」(経由無し)
				・iValidSihatsuEki == iEkiOrder
					getJikokuhyouRessyabangouDisplayが3の場合：列車番号
					2列車目以降で、
						2の場合：iRessyaIndexContIndex-1の列車の次列車接続タイプを見て、種別変更・列車情報変更なら列車番号
						1の場合：iRessyaIndexContIndex-1の列車の次列車接続タイプを見て、種別変更なら列車番号
						それ以外は「↓」
				・iValidSihatsuEki<iEkiOrder<iValidSyuuchakuEki
					isRunbetweenがtrueの場合または、
					getJikokuhyouChakujikokuDisplayがfalseかつisRunbetween(-1)がtrueの場合、表示有りとなる。
						※発時刻のみ表示で、前駅→当駅が運行あり、当駅→次駅が運行なし(経由なし)の場合は、
						当駅の発時刻欄(この欄より下部)に、経由なしを超えた先の発時刻を表示するので、
						この欄が経由なしだと表示が合わないので。
						getJikokuhyouRessyabangouDisplayが3の場合:列車番号
						2/1の場合:「↓」
					その他の場合
						「||」
				・iValidSyuuchakuEki == iEkiOrder
					路線外終着で路線外終着欄がある場合「↓」
					路線外終着相当で路線外終着欄がある場合
						getJikokuhyouRessyabangouDisplayが3の場合：次列車の種別名
						2の場合：aCustomizeJikokuhyouContent.eEAfterTypeを見て、種別変更・列車情報変更なら次列車の列車番号
						1の場合：aCustomizeJikokuhyouContent.eEAfterTypeを見て、種別変更なら次列車の列車番号
						それ以外は「↓」
					iConnectEkiOrder == iValidSyuuchakuEki( == iEkiOrder)の場合空白
					iConnectEkiOrder > iValidSyuuchakuEkiの場合「||」
				・iValidSyuuchakuEki < iEkiOrder
					路線外終着(相当)で路線外終着欄がある場合「||」
					iConnectEkiOrder > iEkiOrderの場合「||」
					iEkiOrder == iConnectEkiOrder
						空白

			*/
			*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
			tstring strText = _T("");
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
								strText = (LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_RELEASE);
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
							strText = _T("↓");
						}
					}
					else if (iEkiOrder > aCustomizeJikokuhyouContent.iReleaseEkiOrder &&
						iEkiOrder <= m_iOuterShuchakuDisplayEkiOrder[aCustomizeJikokuhyouContent.iReleaseEkiOrder])
					{
						strText = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"

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
								strText = (LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_CONNECT);
							}
						}
					}
					else if (iEkiOrder >= m_iOuterShihatsuDisplayEkiOrder[aCustomizeJikokuhyouContent.iConnectEkiOrder] &&
						iEkiOrder < aCustomizeJikokuhyouContent.iConnectEkiOrder)
					{
						strText = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
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
						//iEkiOrder = iCurrentRessyaShihatsuEkiOrderで、この駅に発時刻を表示しているときは、経由なしではなく空白にします。
						if (iEkiOrder == iCurrentRessyaShihatsuEkiOrder &&
							aCdDedEki.getJikokuhyouHatsuJikokuDisplay())
						{
							//発時刻欄に時刻が表示されるのは、着時刻表示が無い場合もしくは、前列車の終着駅発時刻が入力されている場合です。
							if (aCdDedEki.getJikokuhyouChakuJikokuDisplay())
							{
								const CentDedRessya* pPrevRessya =
									m_pCentDedRessyaCont->getMuPtr()->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex - 1]);
								if (pPrevRessya->getCentDedEkiJikoku(iEkiOrder).getHatsujikoku().isNull())
								{
									strText = (LPCTSTR)MfcUtil::LoadCString(
										IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
								}
							}
						}
						else
						{
							strText = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
						}
					}
					//iCurrentRessyaShihatsuEkiOrder < 0(1列車目)
					else if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer &&
						m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0 &&
						m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] <= iEkiOrder)
					{
						//路線外始発
						strText = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
					}

					else if (aCustomizeJikokuhyouContent.iSihatsuEkiOrder >= -2 &&
						m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0 &&
						m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] <= iEkiOrder)
					{
						//路線外始発相当
						idxRessyasyubetsu = aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex;
						*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
						strText = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
					}
					else if (aCustomizeJikokuhyouContent.iReleaseEkiOrder <= iEkiOrder &&
						aCustomizeJikokuhyouContent.iReleaseEkiOrder >= 0)
					{
						//分割列車
						strText = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
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
							m_pCentDedRessyaCont->getMuPtr()->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex - 1]);
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
							strText = _T("↓");
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
							strText = _T("↓");
						}
					}
					else
					{
						strText = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
					}
				}
				else if (iValidSyuuchakuEki == iEkiOrder)
				{
					if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer &&
						m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0 )
					{
						//路線外終着「↓」
						strText = _T("↓");
					}
					else if (aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder >= -2 &&
						m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0)
					{
						//路線外終着相当
						//書式を次列車の種別にします

						idxRessyasyubetsu = aCustomizeJikokuhyouContent.iRessyasyubetsuIndex;
						*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu);

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
							*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
							strText = _T("↓");
						}

					}
					else if (aCustomizeJikokuhyouContent.iConnectEkiOrder > iEkiOrder &&
						aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
					{
						strText = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
					}
				}
				else if (iValidSyuuchakuEki < iEkiOrder)
				{
					if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer &&
						m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0 &&
						m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= iEkiOrder)
					{
						//路線外終着
						strText = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
					}
					else if (aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder >= -2 &&
						m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0 &&
						m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= iEkiOrder)
					{
						//路線外終着相当
						//書式を次列車の種別にします
						*pCDcDrawCell = createCDcdRessyabangou(aCustomizeJikokuhyouContent.iRessyasyubetsuIndex);
						strText = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);

					}
					else if (aCustomizeJikokuhyouContent.iConnectEkiOrder > iEkiOrder &&
						aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
					{
						strText = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
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
							strText = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_RELEASE);
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
							strText = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_CONNECT);
						}
					}
				}
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

void CCellBuilderCustomize::update02_02_02_20_setRessya_OperationNumber(
	int iXColumnNumber,
	int iYColumnNumber,
	const CentDedRessya * pCentDedRessya,
	const CustomizeJikokuhyouContent& aCustomizeJikokuhyouContent,
	int iEkiOrder,
	int iCurrentRessyaShihatsuEkiOrder,
	int iRessyaIndexContIndex,
	CWndJikokuhyou * pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	const CentDedRosen* pCentDedRosen =
		m_pCDedRosenFileData->getCentDedRosen();
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		pCentDedRosen->getCentDedEkiCont()->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou());
	//CDcdTargetGetDC	aCDcdTarget(NULL);
	// --------------------------------
	//CdYColSpec aCdYColSpec(
	//	CdYColSpec::ColumnType_EkiOperationNumber,
	//	iEkiOrder);
	//int iYColumnNumber =
	//	m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec, false);
	int idxRessyasyubetsu;
	if (pCentDedRessya == NULL)
	{
		if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
		{
			idxRessyasyubetsu = aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex;
		}
		else
		{
			idxRessyasyubetsu = aCustomizeJikokuhyouContent.iRessyasyubetsuIndex;
		}
	}
	else
	{
		idxRessyasyubetsu = pCentDedRessya->getRessyasyubetsuIndex();
	}
	CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);
	//0:空白、1:運番、2:経由なし、3:↓、4:分割、5:併合
	int iDisplayType = 0;
	vector<tstring> strOperationNumber;
	/**
		この欄に表示するもの
	・pCentDedRessya == NULLの場合
		iReleaseEkiIndex >= 0の場合
			iReleaseEkiIndex == iEkiOrder
				4の場合運用番号、それ以外は↓
			iReleaseEkiIndex < iEkiOrderかつ路線外終着表示駅>=iEkiOrder
				「||」(経由無し)
			それ以外
				分割駅の前の駅、分割駅が発時刻のみ表示で、この項が分割駅の直上の場合は↴、それ以外は空白
		iConnectEkiIndex >= 0の場合
			iConnectEkiIndex == iEkiOrder
				空白
			iConnectEkiIndex > iEkiOrderかつ路線外始発表示駅<=iEkiOrder
				「||」(経由無し)
			それ以外
				解結駅の次の駅、解結駅が着時刻のみ表示で、この項が解結駅の直下の場合は↳、それ以外は空白

	・iEkiOrder < iValidSihatsuEki
		2列車目以降で、発時刻が表示される場合
			空白
		表示されない場合
			「||」(経由無し)
		路線外始発の場合
			「||」(経由無し)
		路線外始発相当の場合
			「||」(経由無し)前列車の種別で表示
		分割列車で分割駅と始発駅の間の場合
			「||」(経由無し)
	・iValidSihatsuEki == iEkiOrder
		getJikokuhyouOperationNumberDisplayが4の場合：運用番号
		3の場合：2列車目以降でiRessyaIndexContIndex-1の列車の次列車接続タイプを見て、種別変更・列車情報変更なら運用番号。それ以外は空白。
		2の場合：2列車目以降でiRessyaIndexContIndex-1の列車の次列車接続タイプを見て、種別変更なら運用番号。それ以外は空白。
		1の場合：2列車目以降でこの列車のiValidSihatsuEki駅を発車するときの運用番号と、前列車の終着駅に到着するときの運用番号を比較して、異なる場合は表示。それ以外は空白。
	・iValidSihatsuEki<iEkiOrder<iValidSyuuchakuEki
		isRunbetweenがtrueの場合または、
		getJikokuhyouChakujikokuDisplayがfalseかつisRunbetween(-1)がtrueの場合、表示有りとなる。
			※発時刻のみ表示で、前駅→当駅が運行あり、当駅→次駅が運行なし(経由なし)の場合は、
			当駅の発時刻欄(この欄より下部)に、経由なしを超えた先の発時刻を表示するので、
			この欄が経由なしだと表示が合わないので。
			getJikokuhyouOperationNumberDisplayが4の場合：運用番号
			1の場合：この列車のiEkiOrder-1駅を発車するときの運用番号と、iEkiOrder駅を発車するときの運用番号を比較して、異なる場合は表示
			3/2の場合:「↓」
		その他の場合
			「||」
	・iValidSyuuchakuEki == iEkiOrder
		路線外終着の場合:「↓」
		路線外終着相当の場合(次列車の種別で表示)
			getJikokuhyouOperationNumberDisplayが4の場合：運用番号
			1の場合：この駅に到着するときと出発するときの運用番号を比較して、異なる場合は運用番号を表示、同じ場合は「↓」
			2・3の場合：aCustomizeJikokuhyouContent.eEAfterTypeを見て表示有無を決定、表示しない場合は「↓」
		iConnectEkiIndex == iValidSyuuchakuEki( == iEkiOrder)の場合
			「↓」
		iConnectEkiIndex > iValidSyuuchakuEkiの場合
			iEkiOrder >= iValidSyuuchakuEki かつ iEkiOrder < iConnectEkiIndex
				「||」(経由無し)
			iEkiOrder == iConnectEkiIndex
				空白
	・iValidSyuuchakuEki < iEkiOrder
		路線外終着かつこの駅が表示駅もしくはそれより前の場合:「||」
		路線外終着相当かつこの駅が表示駅もしくはそれより前の場合:「||」(次列車の種別で表示)
		iEkiOrder < iConnectEkiIndex
			「||」(経由無し)
		iEkiOrder == iConnectEkiIndex
			空白


	*/
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
							m_pCentDedRessyaCont->getMuPtr()->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex - 1]);
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
				idxRessyasyubetsu = aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex;
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
					m_pCentDedRessyaCont->getMuPtr()->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex - 1]);
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
					m_pCentDedRessyaCont->getMuPtr()->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex - 1]);
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
				else if(aCdDedEki.getJikokuhyouOperationNumberDisplay() == 1)
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
				m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0 )
			{
				//路線外終着「↓」
				iDisplayType = 3;//↓
			}
			else if (aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder >= -2 &&
				m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0)
			{
				//路線外終着相当
				//書式を次列車の種別にします

				idxRessyasyubetsu = aCustomizeJikokuhyouContent.iRessyasyubetsuIndex;
				//*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu);

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
				//路線外終着相当
				//書式を次列車の種別にします
				idxRessyasyubetsu = aCustomizeJikokuhyouContent.iRessyasyubetsuIndex;
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
		CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell(
			iXColumnNumber, iYColumnNumber + idx);
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
					strText = (LPCTSTR)MfcUtil::LoadCString(
						IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
				}
				else if (iDisplayType == 3)
				{
					strText = _T("↓";)
				}
				else if (iDisplayType == 4 &&
					idx == aCdDedEki.getJikokuhyouOperationNumberDisplayRows() - 1)
				{
					strText = (LPCTSTR)MfcUtil::LoadCString(
						IDS_WORD_JIKOKUHYOU_RELEASE);
				}
				else if (iDisplayType == 5 &&
					idx == 0)
				{
					strText = (LPCTSTR)MfcUtil::LoadCString(
						IDS_WORD_JIKOKUHYOU_CONNECT);
				}
				*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
				pCDcDrawCell->setText(strText);

				//セルの背景色を指定します。
				{
					pCDcDrawCell->setCdBrushProp(CdColorProp(255, 255, 255));
				}
			}
		}
	}
}


void CCellBuilderCustomize::update02_02_02_21_setRessya_Ressyasyubetsu(
	int iXColumnNumber,
	int iYColumnNumber,
	const CentDedRessya* pCentDedRessya,
	const CustomizeJikokuhyouContent& aCustomizeJikokuhyouContent,
	int iEkiOrder,
	int iCurrentRessyaShihatsuEkiOrder,
	int iRessyaIndexContIndex,
	CWndJikokuhyou* pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	const CentDedRosen* pCentDedRosen =
		m_pCDedRosenFileData->getCentDedRosen();
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		pCentDedRosen->getCentDedEkiCont()->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou());
	// --------------------------------
	//CDcdTargetGetDC	aCDcdTarget(NULL);
	// --------------------------------
	//CdYColSpec aCdYColSpec(
	//	CdYColSpec::ColumnType_EkiRessyasyubetsu,
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
			CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);
			int idxRessyasyubetsu;
			if (pCentDedRessya == NULL)
			{
				if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
				{
					idxRessyasyubetsu = aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex;
				}
				else
				{
					idxRessyasyubetsu = aCustomizeJikokuhyouContent.iRessyasyubetsuIndex;
				}
			}
			else
			{
				idxRessyasyubetsu = pCentDedRessya->getRessyasyubetsuIndex();
			}
			const CentDedRessyasyubetsu* pCentDedRessyasyubetsu = NULL;
			{
				pCentDedRessyasyubetsu =
					pCentDedRosen->getCentDedRessyasyubetsuCont()->getMuPtr()
					->get(idxRessyasyubetsu);
				if (m_bDisplayParentSyubetsu && pCentDedRessyasyubetsu->getParentSyubetsuIndex() >= 0)
				{
					pCentDedRessyasyubetsu
						= pCentDedRosen->getCentDedRessyasyubetsuCont()->getMuPtr()
						->get(pCentDedRessyasyubetsu->getParentSyubetsuIndex());
				}
				if (pCentDedRessyasyubetsu == NULL)
				{
					pCentDedRessyasyubetsu =
						pCentDedRosen->getCentDedRessyasyubetsuCont()
						->getMuPtr()->get(0);
				}
			}
			//pCentDedRessyasyubetsu = 列車種別オブジェクト
			//	(指定がないなら、列車種別[0])

			tstring strRessyasyubetsu;
			if (pCentDedRessya == NULL || !pCentDedRessya->isNull())
			{
				strRessyasyubetsu = pCentDedRessyasyubetsu->getRyakusyou();
			}
			/**
				この欄に表示するもの
				・pCentDedRessya == NULLの場合
					iReleaseEkiIndex >= 0の場合
						iReleaseEkiIndex == iEkiOrder
							3の場合列車番号、それ以外は↓
						iReleaseEkiIndex < iEkiOrderかつ路線外終着表示駅>=iEkiOrder
							「||」(経由無し)
						それ以外
							分割駅の前の駅、分割駅が発時刻のみ表示で、この項が分割駅の直上の場合は↴、それ以外は空白
					iConnectEkiIndex >= 0の場合
						iConnectEkiIndex == iEkiOrder
							空白
						iConnectEkiIndex > iEkiOrderかつ路線外始発表示駅<=iEkiOrder
							「||」(経由無し)
						それ以外
							解結駅の次の駅、解結駅が着時刻のみ表示で、この項が解結駅の直下の場合は↳、それ以外は空白


				・iEkiOrder <iValidSihatsuEkiの場合
					iRessyaIndexContIndex >= 1(2列車目以降)の場合
						iEkiOrder == iCurrentRessyaShihatsuEkiOrder(前列車の終着駅)で、この駅の発時刻欄に時刻が表示されている場合は、空白
						それ以外は「||」(経由無し)
					1列車目の場合
						路線外始発(相当)で、iEkiOrder >= 路線外始発表示駅
							「||」(経由無し)
						iReleaseEkiOrder >= 0かつ　iReleaseEkiOrder <= iEkiOrder
							「||」(経由無し)
				・iValidSihatsuEki == iEkiOrder
					getJikokuhyouRessyabangouDisplayが3の場合：種別名
					2列車目以降で、
						2の場合：iRessyaIndexContIndex-1の列車の次列車接続タイプを見て、種別変更・列車情報変更なら種別名
						1の場合：iRessyaIndexContIndex-1の列車の次列車接続タイプを見て、種別変更なら種別名
						それ以外は「↓」
				・iValidSihatsuEki<iEkiOrder<iValidSyuuchakuEki
					isRunbetweenがtrueの場合または、
					getJikokuhyouChakujikokuDisplayがfalseかつisRunbetween(-1)がtrueの場合、表示有りとなる。
						※発時刻のみ表示で、前駅→当駅が運行あり、当駅→次駅が運行なし(経由なし)の場合は、
						当駅の発時刻欄(この欄より下部)に、経由なしを超えた先の発時刻を表示するので、
						この欄が経由なしだと表示が合わないので。
						getJikokuhyouRessyabangouDisplayが3の場合:種別名
						2/1の場合:「↓」
					その他の場合
						「||」
				・iValidSyuuchakuEki == iEkiOrder
					路線外終着で路線外終着欄がある場合「↓」
					路線外終着相当で路線外終着欄がある場合
						getJikokuhyouRessyabangouDisplayが3の場合：次列車の種別名
						2の場合：aCustomizeJikokuhyouContent.eEAfterTypeを見て、種別変更・列車情報変更なら次列車の種別名
						1の場合：aCustomizeJikokuhyouContent.eEAfterTypeを見て、種別変更なら次列車の種別名
						それ以外は「↓」
					iConnectEkiOrder == iValidSyuuchakuEki( == iEkiOrder)の場合空白
					iConnectEkiOrder > iValidSyuuchakuEkiの場合「||」
				・iValidSyuuchakuEki < iEkiOrder
					路線外終着(相当)で路線外終着欄がある場合「||」
					iConnectEkiOrder > iEkiOrderの場合「||」
					iEkiOrder == iConnectEkiOrder
						空白
					
			*/
			tstring strText = _T("");
			*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu);
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
								*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
								strText = (LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_RELEASE);
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
							*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
							strText = _T("↓");
						}
					}
					else if (iEkiOrder > aCustomizeJikokuhyouContent.iReleaseEkiOrder &&
						iEkiOrder <= m_iOuterShuchakuDisplayEkiOrder[aCustomizeJikokuhyouContent.iReleaseEkiOrder])
					{
						*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
						strText = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"

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
								*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
								strText = (LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_CONNECT);
							}
						}
					}
					else if (iEkiOrder >= m_iOuterShihatsuDisplayEkiOrder[aCustomizeJikokuhyouContent.iConnectEkiOrder] &&
						iEkiOrder < aCustomizeJikokuhyouContent.iConnectEkiOrder)
					{
						*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
						strText = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
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
									m_pCentDedRessyaCont->getMuPtr()->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex - 1]);
								if (pPrevRessya->getCentDedEkiJikoku(iEkiOrder).getHatsujikoku().isNull())
								{
									*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
									strText = (LPCTSTR)MfcUtil::LoadCString(
										IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
								}
							}
						}
						else
						{
							*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
							strText = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
						}
					}
					//iCurrentRessyaShihatsuEkiOrder < 0(1列車目)
					else if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer &&
						m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0 &&
						m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] <= iEkiOrder)
					{
						//路線外始発
						*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
						strText = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
					}

					else if (aCustomizeJikokuhyouContent.iSihatsuEkiOrder >= -2 &&
						m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0 &&
						m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] <= iEkiOrder)
					{
						//路線外始発相当
						idxRessyasyubetsu = aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex;
						*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
						strText = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
					}
					else if (aCustomizeJikokuhyouContent.iReleaseEkiOrder <= iEkiOrder &&
						aCustomizeJikokuhyouContent.iReleaseEkiOrder >= 0)
					{
						//分割列車
						*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
						strText = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
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
							m_pCentDedRessyaCont->getMuPtr()->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex - 1]);
						if (pPrevRessya->getLastOperation().getNextJunctionType() == 1 )
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
							*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
							strText = _T("↓");
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
							*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
							strText = _T("↓");
						}
					}
					else
					{
						*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
						strText = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
					}
				}
				else if (iValidSyuuchakuEki == iEkiOrder)
				{
					if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer &&
						m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0)
					{
						//路線外終着
						//Ver2.06.21 この項は↓とします。(単純化)
						*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
						strText = _T("↓");
					}
					else if (aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder >= -2 &&
						m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0)
					{
						//路線外終着相当
						//書式を次列車の種別にします

						idxRessyasyubetsu = aCustomizeJikokuhyouContent.iRessyasyubetsuIndex;
						{
							pCentDedRessyasyubetsu =
								pCentDedRosen->getCentDedRessyasyubetsuCont()->getMuPtr()
								->get(idxRessyasyubetsu);
							if (m_bDisplayParentSyubetsu && pCentDedRessyasyubetsu->getParentSyubetsuIndex() >= 0)
							{
								pCentDedRessyasyubetsu
									= pCentDedRosen->getCentDedRessyasyubetsuCont()->getMuPtr()
									->get(pCentDedRessyasyubetsu->getParentSyubetsuIndex());
							}
							if (pCentDedRessyasyubetsu == NULL)
							{
								pCentDedRessyasyubetsu =
									pCentDedRosen->getCentDedRessyasyubetsuCont()
									->getMuPtr()->get(0);
							}
						}
						
						strRessyasyubetsu = pCentDedRessyasyubetsu->getRyakusyou();
						*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu);

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
							*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
							strText = _T("↓");
						}

					}
					else if (aCustomizeJikokuhyouContent.iConnectEkiOrder > iEkiOrder &&
						aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
					{
						*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
						strText = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
					}
				}
				else if (iValidSyuuchakuEki < iEkiOrder)
				{
					if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer &&
						m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0 &&
						m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= iEkiOrder)
					{
						//路線外終着
						*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
						strText = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);
					}
					else if (aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder >= -2 &&
						m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0 &&
						m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= iEkiOrder)
					{
						//路線外終着相当
						//書式を次列車の種別にします
						*pCDcDrawCell = createCDcdRessyabangou(aCustomizeJikokuhyouContent.iRessyasyubetsuIndex);
						strText = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"

					}
					else if (aCustomizeJikokuhyouContent.iConnectEkiOrder > iEkiOrder &&
						aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
					{
						*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
						strText = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
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
							*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
							strText = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_RELEASE);
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
							*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
							strText = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_CONNECT);
						}
					}
				}
			}
			pCDcDrawCell->setText(strText);
		}

		//セルの背景色を指定します。
		{
			pCDcDrawCell->setCdBrushProp(CdColorProp(255, 255, 255));
		}
	}

}

void CCellBuilderCustomize::update02_02_02_22_setRessya_Ressyamei(
	int iXColumnNumber,
	int iYColumnNumber,
	const CentDedRessya* pCentDedRessya,
	const CustomizeJikokuhyouContent& aCustomizeJikokuhyouContent,
	int iEkiOrder,
	int iCurrentRessyaShihatsuEkiOrder,
	int iRessyaIndexContIndex,
	CWndJikokuhyou* pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	const CentDedRosen* pCentDedRosen =
		m_pCDedRosenFileData->getCentDedRosen();
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		pCentDedRosen->getCentDedEkiCont()->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou());
	// --------------------------------
	//CDcdTargetGetDC	aCDcdTarget(NULL);
	// --------------------------------
	//CdYColSpec aCdYColSpec(
	//	CdYColSpec::ColumnType_EkiRessyamei,
	//	iEkiOrder);
	//int iYColumnNumber =
	//	m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec, false);
	CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell(
		iXColumnNumber, iYColumnNumber);
	int iYColumnNumber2 = iYColumnNumber + 1;
	int iYColumnNumber3 = iYColumnNumber + 2;
	CDcdGridCell* pCDcdGridCell2 = pCDcdGrid->getCell(
		iXColumnNumber, iYColumnNumber2);
	CDcdGridCell* pCDcdGridCell3 = pCDcdGrid->getCell(
		iXColumnNumber, iYColumnNumber3);

	// --------------------------------
	if (pCDcdGridCell != 0)
	{
		typedef CDcdTextboxV3 CDcDrawCellV;
		Ou<CDcDrawCellV> pCDcDrawCell;
		typedef CDcdTextbox CDcDrawCell;
		Ou<CDcDrawCell> pCDcDrawCell2;
		Ou<CDcDrawCell> pCDcDrawCell3;
		// --------------------------------
		//　(2.2.*.1)　セル(ColumnType_Ressya,ColumnType_Ressyabangou) の
		//	結合セルを設定
		pCDcdGridCell->setAttachCellCount(1, 1);
		pCDcdGridCell2->setAttachCellCount(1, 1);
		pCDcdGridCell3->setAttachCellCount(1, 1);

		//　(2.2.*.2)　セル の	DcDrawオブジェクトの型を設定
		//	( CDcdTextbox とする)。
		{
			pCDcDrawCell = dynamic_castOu<CDcDrawCellV>(
				pCDcdGridCell->getIfDcDraw());
			if (pCDcDrawCell == NULL)
			{
				pCDcDrawCell = OuNew<CDcDrawCellV>(new CDcDrawCellV);
				pCDcdGridCell->setIfDcDraw(pCDcDrawCell);
			}
			pCDcDrawCell2 = dynamic_castOu<CDcDrawCell>(
				pCDcdGridCell2->getIfDcDraw());
			if (pCDcDrawCell2 == NULL)
			{
				pCDcDrawCell2 = OuNew<CDcDrawCell>(new CDcDrawCell);
				pCDcdGridCell2->setIfDcDraw(pCDcDrawCell2);
			}
			pCDcDrawCell3 = dynamic_castOu<CDcDrawCell>(
				pCDcdGridCell3->getIfDcDraw());
			if (pCDcDrawCell3 == NULL)
			{
				pCDcDrawCell3 = OuNew<CDcDrawCell>(new CDcDrawCell);
				pCDcdGridCell3->setIfDcDraw(pCDcDrawCell3);
			}
		}
		//　(2.2.*.3)　セルの DcDrawオブジェクトに、属性を設定。
		{
			CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);
			int idxRessyasyubetsu;
			if (pCentDedRessya == NULL)
			{
				if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
				{
					idxRessyasyubetsu = aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex;
				}
				else
				{
					idxRessyasyubetsu = aCustomizeJikokuhyouContent.iRessyasyubetsuIndex;
				}
			}
			else
			{
				idxRessyasyubetsu = pCentDedRessya->getRessyasyubetsuIndex();
			}
			//tstring strText;
			//if (!pCentDedRessya->isNull())
			//{
			//	strText = pCentDedRessya->getRessyamei();
			//}
			/**
				この欄に表示するもの
				・pCentDedRessya == NULLの場合
					iReleaseEkiIndex >= 0の場合
						iReleaseEkiIndex == iEkiOrder
							getJikokuhyouRessyameiDisplayが3の場合列車名・号数・号、それ以外は「空白」
						それ以外
							「空白」
					iConnectEkiIndex >= 0の場合、常に「空白」

				・iValidSihatsuEki == iEkiOrder
					getJikokuhyouRessyabangouDisplayが3の場合：列車名
						2列車目以降かつ2の場合：iRessyaIndexContIndex-1の列車の次列車接続タイプを見て、種別変更・列車情報変更なら列車名
						2列車目以降かつ1の場合：iRessyaIndexContIndex-1の列車の次列車接続タイプを見て、種別変更なら列車名
				
				・iValidSihatsuEki<iEkiOrder<iValidSyuuchakuEki
					isRunbetweenがtrueの場合または、
					getJikokuhyouChakujikokuDisplayがfalseかつisRunbetween(-1)がtrueの場合、表示有りとなる。
						※発時刻のみ表示で、前駅→当駅が運行あり、当駅→次駅が運行なし(経由なし)の場合は、
						当駅の発時刻欄(この欄より下部)に、経由なしを超えた先の発時刻を表示するので、
						この欄が経由なしだと表示が合わないので。
						getJikokuhyouRessyameiDisplayが3の場合:列車名
						2/1の場合:「空白」
					その他の場合
						「空白」
				・iValidSyuuchakuEki==iEkiOrder
					路線外終着相当かつ、路線外終着表示欄がある場合
						getJikokuhyouRessyabangouDisplayが3の場合：次列車名
						2の場合：aCustomizeJikokuhyouContent.eEAfterTypeを見て、種別変更・列車情報変更なら列車名
						1の場合：aCustomizeJikokuhyouContent.eEAfterTypeを見て、種別変更なら列車名


				・iRessyaIndexContIndex >= 1(2列車目以降)の場合
					iCurrentRessyaShihatsuEkiOrder<= iEkiOrder <iValidSihatsuEki
						「空白」
					iEkiOrder=iValidSihatsuEki
							getJikokuhyouRessyabangouDisplayが3の場合：列車名
							2の場合：iRessyaIndexContIndex-1の列車の次列車接続タイプを見て、種別変更・列車情報変更なら列車名
							1の場合：iRessyaIndexContIndex-1の列車の次列車接続タイプを見て、種別変更なら列車名
					iValidSihatsuEki<iEkiOrder<iValidSyuuchakuEki
						isRunbetweenがtrueの場合または、
						getJikokuhyouChakujikokuDisplayがfalseかつisRunbetween(-1)がtrueの場合、表示有りとなる。
							※発時刻のみ表示で、前駅→当駅が運行あり、当駅→次駅が運行なし(経由なし)の場合は、
							当駅の発時刻欄(この欄より下部)に、経由なしを超えた先の発時刻を表示するので、
							この欄が経由なしだと表示が合わないので。
							getJikokuhyouRessyameiDisplayが3の場合：列車名
							2/1の場合:「空白」
						その他の場合
							「空白」
					iValidSyuuchakuEki<=iEkiOrder
						「空白」(列車種別等では↓を表示するようなケースでも、この項の特性上、空白とする。)

				・iRessyaIndexContIndex == 0(1列車目)の場合
					iEkiOrder<iValidSihatsuEki
						路線外始発(相当)で、iEkiOrder >= 路線外始発表示駅
							「空白」
						iReleaseEkiOrder >= 0かつ　iReleaseEkiOrder <= iEkiOrder
							「空白」
							→したがって、iEkiOrder<iValidSihatsuEki時は常時空白
					iEkiOrder=iValidSihatsuEki
						getJikokuhyouRessyameiDisplayが3の場合列車名
						2/1の場合「空白」
					iValidSihatsuEki<iEkiOrder<iValidSyuuchakuEki
						isRunbetweenがtrueの場合または、
						getJikokuhyouChakujikokuDisplayがfalseかつisRunbetween(-1)がtrueの場合、表示有りとなる。
							※発時刻のみ表示で、前駅→当駅が運行あり、当駅→次駅が運行なし(経由なし)の場合は、
							当駅の発時刻欄(この欄より下部)に、経由なしを超えた先の発時刻を表示するので、
							この欄が経由なしだと表示が合わないので。
							getJikokuhyouRessyameiDisplayが3の場合:列車名
							2/1の場合:「空白」
						その他の場合
							「空白」
					iValidSyuuchakuEki<=iEkiOrder
						「空白」(列車種別等では↓を表示するようなケースでも、この項の特性上、空白とする。)

			*/
			tstring strText = _T("");
			tstring strText2 = _T("");
			tstring strText3 = _T("");
			bool bDisplayConnect = false;
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
							int iYColumnNumberNext = iYColumnNumber3 + 1;
							CdYColSpec aCdYColSpecNext = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberNext);
							if (aCdYColSpecNext.getEkiOrder() == iEkiOrder + 1)
							{
								strText3 = (LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_RELEASE);
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
								strText3 = (LPCTSTR)MfcUtil::LoadCString(IDS_WORD_GOUSUU2);
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
								strText = (LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_CONNECT);
								bDisplayConnect = true;
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
							strText3 = (LPCTSTR)MfcUtil::LoadCString(IDS_WORD_GOUSUU2);
						}
					}
					else if (iCurrentRessyaShihatsuEkiOrder >= 0 &&
						aCdDedEki.getJikokuhyouRessyameiDisplay() >= 1)
					{
						const CentDedRessya* pPrevRessya =
							m_pCentDedRessyaCont->getMuPtr()->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex - 1]);
						if (pPrevRessya->getLastOperation().getNextJunctionType() == 1 &&
							aCdDedEki.getJikokuhyouRessyameiDisplay() >= 1)
						{
							strText = pCentDedRessya->getRessyamei();
							strText2 = pCentDedRessya->getGousuu();
							if (!strText2.empty())
							{
								strText3 = (LPCTSTR)MfcUtil::LoadCString(IDS_WORD_GOUSUU2);
							}
						}
						else if (pPrevRessya->getLastOperation().getNextJunctionType() == 2 &&
							aCdDedEki.getJikokuhyouRessyameiDisplay() == 2)
						{
							strText = pCentDedRessya->getRessyamei();
							strText2 = pCentDedRessya->getGousuu();
							if (!strText2.empty())
							{
								strText3 = (LPCTSTR)MfcUtil::LoadCString(IDS_WORD_GOUSUU2);
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
						strText3 = (LPCTSTR)MfcUtil::LoadCString(IDS_WORD_GOUSUU2);
					}
				}
				else if (iValidSyuuchakuEki == iEkiOrder &&
					aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder >= -2 &&
					m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0)
				{
					//路線外終着相当
					//書式を次列車の種別にします
					idxRessyasyubetsu = aCustomizeJikokuhyouContent.iRessyasyubetsuIndex;

					if (aCdDedEki.getJikokuhyouRessyameiDisplay() == 3)
					{
						strText = aCustomizeJikokuhyouContent.strRessyamei;
						strText2 = aCustomizeJikokuhyouContent.strGousuu;
						if (!strText2.empty())
						{
							strText3 = (LPCTSTR)MfcUtil::LoadCString(IDS_WORD_GOUSUU2);
						}
					}
					else if (aCustomizeJikokuhyouContent.eEAfterType == EBeforeAfterType::BeforeAfterType_ClassChange)
					{
						strText = aCustomizeJikokuhyouContent.strRessyamei;
						strText2 = aCustomizeJikokuhyouContent.strGousuu;
						if (!strText2.empty())
						{
							strText3 = (LPCTSTR)MfcUtil::LoadCString(IDS_WORD_GOUSUU2);
						}
					}
					else if (aCustomizeJikokuhyouContent.eEAfterType == EBeforeAfterType::BeforeAfterType_PropertyChange &&
						aCdDedEki.getJikokuhyouRessyameiDisplay() == 2)
					{
						strText = aCustomizeJikokuhyouContent.strRessyamei;
						strText2 = aCustomizeJikokuhyouContent.strGousuu;
						if (!strText2.empty())
						{
							strText3 = (LPCTSTR)MfcUtil::LoadCString(IDS_WORD_GOUSUU2);
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
						int iYColumnNumberNext = iYColumnNumber3 + 1;
						CdYColSpec aCdYColSpecNext = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberNext);
						if (aCdYColSpecNext.getEkiOrder() == iEkiOrder + 1)
						{
							strText3 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_RELEASE);
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
							strText = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_CONNECT);
							bDisplayConnect = true;
						}
					}
				}
			}
			if (bDisplayConnect)
			{
				Ou<CDcDrawCell> pCDcDrawCell1;
				pCDcDrawCell1 = dynamic_castOu<CDcDrawCell>(
					pCDcdGridCell->getIfDcDraw());
				if (pCDcDrawCell1 == NULL)
				{
					pCDcDrawCell1 = OuNew<CDcDrawCell>(new CDcDrawCell);
					pCDcdGridCell->setIfDcDraw(pCDcDrawCell1);
				}
				*pCDcDrawCell1 = createCDcdRessyabangou(idxRessyasyubetsu);
				CdDrawTextProp aCdDrawTextProp = pCDcDrawCell1->getCdDrawTextProp();
				aCdDrawTextProp.setCdDrawTextFormat(
					CdDrawTextFormat(CdDrawTextFormat::H_CENTER, CdDrawTextFormat::EVertical::V_SINGLELINT_TOP));
				pCDcDrawCell1->setCdDrawTextProp(aCdDrawTextProp);
				pCDcDrawCell1->setText(strText);
			}
			else
			{
				*pCDcDrawCell = createCDcdRessyamei(idxRessyasyubetsu);
				pCDcDrawCell->setText(strText);
			}
			*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);
			pCDcDrawCell2->setText(strText2);
			*pCDcDrawCell3 = createCDcdRessyabangou(idxRessyasyubetsu);
			pCDcDrawCell3->setText(strText3);
		}

		//セルの背景色を指定します。
		{
			pCDcDrawCell->setCdBrushProp(CdColorProp(255, 255, 255));
		}
	}


}

//void CCellBuilderCustomize::update02_02_02_23_setRessya_Gousuu(
//	int iXColumnNumber,
//	int iYColumnNumber,
//	const CentDedRessya* pCentDedRessya,
//	const CustomizeJikokuhyouContent& aCustomizeJikokuhyouContent,
//	int iEkiOrder,
//	int iCurrentRessyaShihatsuEkiOrder,
//	int iRessyaIndexContIndex,
//	CWndJikokuhyou* pCWndJikokuhyou)
//{
//	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
//	const CentDedRosen* pCentDedRosen =
//		m_pCDedRosenFileData->getCentDedRosen();
//	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
//		pCentDedRosen->getCentDedEkiCont()->getMuPtr(
//			m_pCentDedRessyaCont->getRessyahoukou());
//	// --------------------------------
//	//CDcdTargetGetDC	aCDcdTarget(NULL);
//	// --------------------------------
//	//CdYColSpec aCdYColSpec(
//	//	CdYColSpec::ColumnType_EkiGousuu,
//	//	iEkiOrder);
//	//int iYColumnNumber =
//	//	m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec, false);
//	CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell(
//		iXColumnNumber, iYColumnNumber);
//	// --------------------------------
//	if (pCDcdGridCell != 0)
//	{
//		typedef CDcdTextbox CDcDrawCell;
//		Ou<CDcDrawCell> pCDcDrawCell;
//		// --------------------------------
//		//　(2.2.*.1)　セル(ColumnType_Ressya,ColumnType_Ressyabangou) の
//		//	結合セルを設定
//		pCDcdGridCell->setAttachCellCount(1, 1);
//
//		//　(2.2.*.2)　セル の	DcDrawオブジェクトの型を設定
//		//	( CDcdTextbox とする)。
//		{
//			pCDcDrawCell = dynamic_castOu<CDcDrawCell>(
//				pCDcdGridCell->getIfDcDraw());
//			if (pCDcDrawCell == NULL)
//			{
//				pCDcDrawCell = OuNew<CDcDrawCell>(new CDcDrawCell);
//				pCDcdGridCell->setIfDcDraw(pCDcDrawCell);
//			}
//		}
//		//　(2.2.*.3)　セルの DcDrawオブジェクトに、属性を設定。
//		{
//			CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);
//			int idxRessyasyubetsu;
//			if (pCentDedRessya == NULL)
//			{
//				idxRessyasyubetsu = aCustomizeJikokuhyouContent.iRessyasyubetsuIndex;
//			}
//			else
//			{
//				idxRessyasyubetsu = pCentDedRessya->getRessyasyubetsuIndex();
//			}
//			//tstring strText = pCentDedRessya->getGousuu();
//			/**
//				この欄に表示するもの
//				・種別変更が有効な場合 (iSyubetsuChangeEkiOrder!=-1)
//					iSyubetsuChangeEkiOrder<= iEkiOrder <iValidSihatsuEki
//						「空白」
//					iEkiOrder=iValidSihatsuEki
//						号数
//					iValidSihatsuEki<iEkiOrder<iValidSyuuchakuEki
//						isRunbetweenがtrueの場合もしくはgetJikokuhyouChakuJikokuDisplay()がfalseの場合
//						->Ver2.04.05 isRunbetweenがtrueの場合または、
//						getJikokuhyouChakujikokuDisplayがfalseかつisRunbetween(-1)がtrueの場合に変更
//							※発時刻のみ表示で、前駅→当駅が運行あり、当駅→次駅が運行なし(経由なし)の場合は、
//							当駅の発時刻欄(この欄より下部)に、経由なしを超えた先の発時刻を表示するので、
//							この欄が経由なしだと表示が合わない。なお、空白にするのと悩むところだが、とりあえず表示有りで。
//							getJikokuhyouRessyabangouDisplayが2の場合種別名
//							1の場合「「空白」
//						その他の場合「空白」
//					iValidSyuuchakuEki<=iEkiOrder
//						空白
//				・種別変更ではない場合
//					iEkiOrder<iValidSihatsuEki
//						空白
//					iEkiOrder=iValidSihatsuEki
//						getJikokuhyouRessyabangouDisplayが2の場合種別名
//						1の場合空白
//					iValidSihatsuEki<iEkiOrder<iValidSyuuchakuEki
//						isRunbetweenがtrueの場合もしくはgetJikokuhyouChakuJikokuDisplay()がfalseの場合
//						->Ver2.04.05 isRunbetweenがtrueの場合または、
//						getJikokuhyouChakujikokuDisplayがfalseかつisRunbetween(-1)がtrueの場合に変更
//							※発時刻のみ表示で、前駅→当駅が運行あり、当駅→次駅が運行なし(経由なし)の場合は、
//							当駅の発時刻欄(この欄より下部)に、経由なしを超えた先の発時刻を表示するので、
//							この欄が経由なしだと表示が合わない。なお、空白にするのと悩むところだが、とりあえず表示有りで。
//							getJikokuhyouRessyabangouDisplayが2の場合種別名
//							1の場合「空白」
//						その他の場合「空白」
//					iValidSyuuchakuEki<=iEkiOrder
//						空白
//			*/
//			int iValidSihatsuEki = pCentDedRessya->getValidSihatsuEki();
//			int iValidSyuuchakuEki = pCentDedRessya->getValidSyuuchakuEki();
//			tstring strText;
//			if (iValidSihatsuEki == -1 || iValidSyuuchakuEki == -1)
//			{
//				strText = _T("");
//			}
//			else if (iValidSihatsuEki == iEkiOrder)
//			{
//				if (iSyubetsuChangeEkiOrder != -1 ||
//					aCdDedEki.getJikokuhyouRessyameiDisplay() == 2)
//				{
//					strText = pCentDedRessya->getGousuu();
//				}
//				else
//				{
//					strText = _T("");
//				}
//			}
//			else if (iValidSihatsuEki < iEkiOrder &&
//				iEkiOrder < iValidSyuuchakuEki &&
//				aCdDedEki.getJikokuhyouRessyameiDisplay() == 2 &&
//				(pCentDedRessya->isRunBetweenNextEki(iEkiOrder) ||
//					(!aCdDedEki.getJikokuhyouChakuJikokuDisplay() &&
//						pCentDedRessya->isRunBetweenNextEki(iEkiOrder - 1))))
//			{
//				strText = pCentDedRessya->getGousuu();
//			}
//			else
//			{
//				strText = _T("");
//			}
//			*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
//			pCDcDrawCell->setText(strText);
//		}
//
//		//セルの背景色を指定します。
//		{
//			pCDcDrawCell->setCdBrushProp(CdColorProp(255, 255, 255));
//		}
//	}
//}

//void CCellBuilderCustomize::update02_02_02_24_setRessya_Gou(
//	int iXColumnNumber,
//	int iYColumnNumber,
//	const CentDedRessya* pCentDedRessya,
//	const CustomizeJikokuhyouContent& aCustomizeJikokuhyouContent,
//	int iEkiOrder,
//	int iCurrentRessyaShihatsuEkiOrder,
//	int iRessyaIndexContIndex,
//	CWndJikokuhyou* pCWndJikokuhyou)
//{
//	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
//	const CentDedRosen* pCentDedRosen =
//		m_pCDedRosenFileData->getCentDedRosen();
//	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
//		pCentDedRosen->getCentDedEkiCont()->getMuPtr(
//			m_pCentDedRessyaCont->getRessyahoukou());
//	// --------------------------------
//	//CDcdTargetGetDC	aCDcdTarget(NULL);
//	// --------------------------------
//	//CdYColSpec aCdYColSpec(
//	//	CdYColSpec::ColumnType_EkiGou,
//	//	iEkiOrder);
//	//int iYColumnNumber =
//	//	m_CdYColSpecCont.ColumnNumberFromSpec(aCdYColSpec, false);
//	CDcdGridCell* pCDcdGridCell = pCDcdGrid->getCell(
//		iXColumnNumber, iYColumnNumber);
//	// --------------------------------
//	if (pCDcdGridCell != 0)
//	{
//		typedef CDcdTextbox CDcDrawCell;
//		Ou<CDcDrawCell> pCDcDrawCell;
//		// --------------------------------
//		//　(2.2.*.1)　セルの結合セルを設定
//		pCDcdGridCell->setAttachCellCount(1, 1);
//
//		//　(2.2.*.2)　セル の	DcDrawオブジェクトの型を設定
//		//	( CDcdTextbox とする)。
//		{
//			pCDcDrawCell = dynamic_castOu<CDcDrawCell>(
//				pCDcdGridCell->getIfDcDraw());
//			if (pCDcDrawCell == NULL)
//			{
//				pCDcDrawCell = OuNew<CDcDrawCell>(new CDcDrawCell);
//				pCDcdGridCell->setIfDcDraw(pCDcDrawCell);
//			}
//		}
//		//　(2.2.*.3)　セルの DcDrawオブジェクトに、属性を設定。
//		{
//			CentDedEkiCont::CdDedEki aCdDedEki = muCdDedEki->get(iEkiOrder);
//			int idxRessyasyubetsu;
//			if (pCentDedRessya == NULL)
//			{
//				idxRessyasyubetsu = aCustomizeJikokuhyouContent.iRessyasyubetsuIndex;
//			}
//			else
//			{
//				idxRessyasyubetsu = pCentDedRessya->getRessyasyubetsuIndex();
//			}
//			/**
//				この欄に表示するもの
//				・種別変更が有効な場合 (iSyubetsuChangeEkiOrder!=-1)
//					iSyubetsuChangeEkiOrder<= iEkiOrder <iValidSihatsuEki
//						「空白」
//					iEkiOrder=iValidSihatsuEki
//						「号」
//					iValidSihatsuEki<iEkiOrder<iValidSyuuchakuEki
//						isRunbetweenがtrueの場合もしくはgetJikokuhyouChakuJikokuDisplay()がfalseの場合
//						->Ver2.04.05 isRunbetweenがtrueの場合または、
//						getJikokuhyouChakujikokuDisplayがfalseかつisRunbetween(-1)がtrueの場合に変更
//							※発時刻のみ表示で、前駅→当駅が運行あり、当駅→次駅が運行なし(経由なし)の場合は、
//							当駅の発時刻欄(この欄より下部)に、経由なしを超えた先の発時刻を表示するので、
//							この欄が経由なしだと表示が合わない。なお、空白にするのと悩むところだが、とりあえず表示有りで。
//							getJikokuhyouRessyabangouDisplayが2の場合「号」
//							1の場合「空白」
//						その他の場合「空白」
//					iValidSyuuchakuEki<=iEkiOrder
//						空白
//				・種別変更ではない場合
//					iEkiOrder<iValidSihatsuEki
//						空白
//					iEkiOrder=iValidSihatsuEki
//						getJikokuhyouRessyabangouDisplayが2の場合「号」
//						1の場合空白
//					iValidSihatsuEki<iEkiOrder<iValidSyuuchakuEki
//						isRunbetweenがtrueの場合もしくはgetJikokuhyouChakuJikokuDisplay()がfalseの場合
//						->Ver2.04.05 isRunbetweenがtrueの場合または、
//						getJikokuhyouChakujikokuDisplayがfalseかつisRunbetween(-1)がtrueの場合に変更
//							※発時刻のみ表示で、前駅→当駅が運行あり、当駅→次駅が運行なし(経由なし)の場合は、
//							当駅の発時刻欄(この欄より下部)に、経由なしを超えた先の発時刻を表示するので、
//							この欄が経由なしだと表示が合わない。なお、空白にするのと悩むところだが、とりあえず表示有りで。
//							getJikokuhyouRessyabangouDisplayが2の場合「号」
//							1の場合「空白」
//						その他の場合「空白」
//					iValidSyuuchakuEki<=iEkiOrder
//						空白
//			*/
//			int iValidSihatsuEki = pCentDedRessya->getValidSihatsuEki();
//			int iValidSyuuchakuEki = pCentDedRessya->getValidSyuuchakuEki();
//			tstring strText;
//			if (iValidSihatsuEki == -1 || iValidSyuuchakuEki == -1)
//			{
//				strText = _T("");
//			}
//			else if (pCentDedRessya->getGousuu().empty())
//			{
//				strText = _T("");
//			}
//			else if (iValidSihatsuEki == iEkiOrder)
//			{
//				if (iSyubetsuChangeEkiOrder != -1 ||
//					aCdDedEki.getJikokuhyouRessyameiDisplay() == 2)
//				{
//					strText= (LPCTSTR)MfcUtil::LoadCString(IDS_WORD_GOUSUU2);
//				}
//				else
//				{
//					strText = _T("");
//				}
//			}
//			else if (iValidSihatsuEki < iEkiOrder &&
//				iEkiOrder < iValidSyuuchakuEki &&
//				aCdDedEki.getJikokuhyouRessyameiDisplay() == 2 &&
//				(pCentDedRessya->isRunBetweenNextEki(iEkiOrder) ||
//					(!aCdDedEki.getJikokuhyouChakuJikokuDisplay() &&
//						pCentDedRessya->isRunBetweenNextEki(iEkiOrder - 1))))
//			{
//				strText = (LPCTSTR)MfcUtil::LoadCString(IDS_WORD_GOUSUU2);
//			}
//			else
//			{
//				strText = _T("");
//			}
//
//			/**
//				次駅が解結駅の場合、この欄に↴印を表示することがあります
//				(1)次駅が解結駅かつ有効な始発駅
//				(2)次駅が着時刻又は発時刻のどちらかのみ表示→Ver2.05 次駅が発時刻のみ表示の場合のみに変更
//				(3)この欄の直下が、次駅の項な場合。
//			*/
//			if (iEkiOrder + 1 == iValidSihatsuEki &&
//				iEkiOrder + 1 == aCustomizeJikokuhyouContent.iReleaseEkiOrder)
//			{
//				CentDedEkiCont::CdDedEki aCdDedEkiNext = muCdDedEki->get(iEkiOrder + 1);
//				if (!aCdDedEkiNext.getJikokuhyouChakuJikokuDisplay() &&
//					aCdDedEkiNext.getJikokuhyouHatsuJikokuDisplay())
//				{
//					int iYColumnNumberNext = iYColumnNumber + 1;
//					CdYColSpec aCdYColSpecNext = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberNext);
//					if (aCdYColSpecNext.getEkiOrder() == iEkiOrder + 1)
//					{
//						strText = (LPCTSTR)MfcUtil::LoadCString(
//							IDS_WORD_JIKOKUHYOU_RELEASE);
//					}
//				}
//			}
//			/**
//				前駅が増結駅の場合、この欄に↳印を表示することがあります
//				(1)前駅が増結駅かつ有効な終着駅
//				(2)前駅が着時刻又は発時刻のどちらかのみ表示→Ver2.05 前駅が着時刻のみ表示の場合のみに変更
//				(3)この欄の直上が、前駅の項な場合。
//			*/
//			if (iEkiOrder - 1 == iValidSyuuchakuEki &&
//				iEkiOrder - 1 == aCustomizeJikokuhyouContent.iConnectEkiOrder &&
//				iValidSyuuchakuEki != -1)
//			{
//				CentDedEkiCont::CdDedEki aCdDedEkiPrev = muCdDedEki->get(iEkiOrder - 1);
//				if (aCdDedEkiPrev.getJikokuhyouChakuJikokuDisplay() &&
//					!aCdDedEkiPrev.getJikokuhyouHatsuJikokuDisplay())
//				{
//					int iYColumnNumberPrev = iYColumnNumber - 1;
//					CdYColSpec aCdYColSpecPrev = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumberPrev);
//					if (aCdYColSpecPrev.getEkiOrder() == iEkiOrder - 1)
//					{
//						strText = (LPCTSTR)MfcUtil::LoadCString(
//							IDS_WORD_JIKOKUHYOU_CONNECT);
//					}
//				}
//			}
//			//CString	strText;
//
//			*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
//			pCDcDrawCell->setText(strText);
//		}
//
//		//セルの背景色を指定します。
//		{
//			pCDcDrawCell->setCdBrushProp(CdColorProp(255, 255, 255));
//		}
//	}
//}

void CCellBuilderCustomize::update02_02_02_07_setRessya_Hatsu(
	int iXColumnNumber ,
	int iYColumnNumber,
	const CentDedRessya* pCentDedRessya ,
	const CustomizeJikokuhyouContent& aCustomizeJikokuhyouContent,
	int iEkiOrder ,
	int iCurrentRessyaShihatsuEkiOrder,
	int iRessyaIndexContIndex,
	CWndJikokuhyou* pCWndJikokuhyou ) 
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid() ;
	const CentDedRosen* pCentDedRosen = 
		m_pCDedRosenFileData->getCentDedRosen() ;
	const CentDedEkiCont* pCentDedEkiCont =
		pCentDedRosen->getCentDedEkiCont();
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki = 
		pCentDedEkiCont->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou()) ;
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
				int idxRessyasyubetsu;
				if (pCentDedRessya == NULL)
				{
					if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
					{
						idxRessyasyubetsu = aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex;
					}
					else
					{
						idxRessyasyubetsu = aCustomizeJikokuhyouContent.iRessyasyubetsuIndex;
					}
				}
				else
				{
					idxRessyasyubetsu = pCentDedRessya->getRessyasyubetsuIndex();
				}
				//	主要駅では、空欄に主要駅表記を行います。
				//	起点・終点・着発駅のいずれかである場合、
				//	境界線に接している駅である場合は除きます。
				bool bIsSyuyouEkiHyouki = false ;
				if ( aCdDedEki.getEkikibo() == CentDedEki::EEkikibo::Ekikibo_Syuyou 
					&&	0 < iEkiOrder 
					&& iEkiOrder < muCdDedEki->size() - 1 
					&& (!aCdDedEki.getJikokuhyouChakuJikokuDisplay() ||
						!aCdDedEki.getJikokuhyouHatsuJikokuDisplay()))
				{
					//	境界線に接している駅である場合は除きます。
					CentDedEkiCont::CdDedEki aCentDedEkiPrev = muCdDedEki->get( iEkiOrder - 1 ) ;

					if ( !aCentDedEkiPrev.getKyoukaisen()  &&
						!aCdDedEki.getKyoukaisen() )
					{
						bIsSyuyouEkiHyouki = true ;
					}
				}

				//bIsSyuyouEkiHyouji = 空欄に主要駅表記を行います。
				*pCDcDrawCell = createCDcdRessyabangou(idxRessyasyubetsu);
				if (bIsSyuyouEkiHyouki)
				{
					//	主要駅での表記（着発の場合は除く）
					//	"----"
					pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
						IDS_WORD_JIKOKUHYOU_UNKOUNASI_SYUYOU));
				}
				else
				{
					//	その他の駅での表記
					//	"・・"
					pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
						IDS_WORD_JIKOKUHYOU_UNKOUNASI_IPPAN));
				}

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
									pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
										IDS_WORD_JIKOKUHYOU_RELEASE));
								}
							}
						}
						else if (iEkiOrder == aCustomizeJikokuhyouContent.iReleaseEkiOrder)
						{
							tstring strText = getCdDedJikokuConv().encode(aCustomizeJikokuhyouContent.HatsuJikoku, false);

							*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu,
								aCustomizeJikokuhyouContent.eEkiatsukai);
							pCDcDrawCell->setText(strText); 
						}
						else if (iEkiOrder > aCustomizeJikokuhyouContent.iReleaseEkiOrder &&
							iEkiOrder <= m_iOuterShuchakuDisplayEkiOrder[aCustomizeJikokuhyouContent.iReleaseEkiOrder])
						{
							pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"

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
									pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
										IDS_WORD_JIKOKUHYOU_CONNECT));
								}
							}
						}
						else if (iEkiOrder == aCustomizeJikokuhyouContent.iConnectEkiOrder)
						{
							pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_CONNECT));
						}
						else if (iEkiOrder >= m_iOuterShihatsuDisplayEkiOrder[aCustomizeJikokuhyouContent.iConnectEkiOrder] &&
							iEkiOrder < aCustomizeJikokuhyouContent.iConnectEkiOrder)
						{
							pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI));
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
						//・・または----のまま
					}
					else if (iEkiOrder < iValidSihatsuEki)
					{
						if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] <= iEkiOrder)
						{
							//路線外始発
							pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"

						}
						else if (aCustomizeJikokuhyouContent.iSihatsuEkiOrder >= -2 &&
							iRessyaIndexContIndex == 0 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] <= iEkiOrder)
						{
							//路線外始発相当
							//Ver2.06.21 この場合は、セルの書式を前列車種別のものにする
							*pCDcDrawCell = createCDcdRessyabangou(aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex);
							pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"
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
									m_pCentDedRessyaCont->getMuPtr()->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex - 1]);
								const CentDedEkiJikoku aSyuuchakuEkiJikoku = pPrevRessya->getCentDedEkiJikoku(pPrevRessya->getValidSyuuchakuEki());
								if(aSyuuchakuEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka &&
									!m_bDisplayTsuukaEkiJikoku )
								{
									//運転停車かつ通過駅時刻非表示の場合、着時刻表示が無い場合はレ印を、ある場合は経由なし表示とします。
									if (aCdDedEki.getJikokuhyouChakuJikokuDisplay())
									{
										pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
											IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"
									}
									else//if(!aCdDedEki.getJikokuhyouChakuJikokuDisplay())
									{
										pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
											IDS_WORD_JIKOKUHYOU_TSUUKA));	//" ﾚ"
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
										if (!getDisplaySecondEkiJikoku() &&
											m_iSecondRoundChaku >= 1 &&
											m_iSecondRoundHatsu == 0)
										{
											aChakuJikoku = pPrevRessya->getCentDedEkiJikoku(pPrevRessya->getValidSyuuchakuEki()).getVirtualChakujikoku();
										}
										CdDedJikoku aHatsuJikoku = pCentDedRessya->getCentDedEkiJikoku(iValidSihatsuEki).getVirtualHatsujikoku();

										tstring strText = getCdDedJikokuConv().encode(aHatsuJikoku, false, aChakuJikoku);
										*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu,
											aSyuuchakuEkiJikoku.getEkiatsukai());
										pCDcDrawCell->setText(strText);
									}
									else if (aCdDedEki.getJikokuhyouChakuJikokuDisplay())
									{
										pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
											IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"
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
										if (!getDisplaySecondEkiJikoku() &&
											m_iSecondRoundChaku == 2 &&
											m_iSecondRoundHatsu <= 1)
										{
											aHatsuJikoku = pCentDedRessya->getCentDedEkiJikoku(iValidSihatsuEki).getVirtualHatsujikoku();
										}

										tstring strText = getCdDedJikokuConv().encode(aChakuJikoku, true, aHatsuJikoku);
										*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu,
											aSyuuchakuEkiJikoku.getEkiatsukai());
										pCDcDrawCell->setText(strText);
									}
								}
							}
							else
							{
								pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"
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
								pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_RELEASE));
							}
							else
							{
								pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"
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
								!m_bDisplayTsuukaEkiJikoku &&
								m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0)
							{
								//路線外表示スペースがない場合は、レ印ではなく時刻を表示する。
								pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_TSUUKA));	//" ﾚ"
							}
							else
							{
								CdDedJikoku aChakuJikoku = pCentDedRessya->getFirstOperation().getChakuJikoku();
								//当駅着時刻を確認、時刻がない場合、駅扱い通過の時は通過とみなす(運転停車ではない)
								if (!aChakuJikoku.isNull())
								{
									aCdDedJikoku = aCentDedEkiJikoku.getVirtualHatsujikoku();
								}

								tstring strText = getCdDedJikokuConv().encode(aCdDedJikoku, false, aChakuJikoku);
								*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu,
									aCentDedEkiJikoku.getEkiatsukai());
								pCDcDrawCell->setText(strText);
							}
						}
						else if (iRessyaIndexContIndex == 0 &&
							aCustomizeJikokuhyouContent.iSihatsuEkiOrder >= -2)
						{
							//路線外始発相当
							if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka &&
								!m_bDisplayTsuukaEkiJikoku &&
								m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0)
							{
								//路線外表示スペースがない場合は、レ印ではなく時刻を表示する。
								pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_TSUUKA));	//" ﾚ"
							}
							else
							{
								CdDedJikoku aChakuJikoku = aCustomizeJikokuhyouContent.ChakuJikoku;
								aCdDedJikoku = aCentDedEkiJikoku.getVirtualHatsujikoku();

								tstring strText = getCdDedJikokuConv().encode(aCdDedJikoku, false, aChakuJikoku);
								*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu,
									aCentDedEkiJikoku.getEkiatsukai());
								pCDcDrawCell->setText(strText);
							}
						}
						else if (iRessyaIndexContIndex > 0)
						{
							//前列車あり
							if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka &&
								!m_bDisplayTsuukaEkiJikoku)
							{
								pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_TSUUKA));	//" ﾚ"
							}
							else
							{

								/**
									秒単位表示OFFの場合は、切り上げ・切り捨ての処理を行いますが、
									その補助のため、着時刻が30秒以上切り上げまたは切り上げで、発時刻が切り捨ての場合、
									前列車の終着駅着時刻の取得を行います。(発時刻表示)
								*/
								CdDedJikoku aChakuJikoku;
								if (!getDisplaySecondEkiJikoku() &&
									m_iSecondRoundChaku >= 1 &&
									m_iSecondRoundHatsu == 0)
								{
									const CentDedRessya* pPrevRessya =
										m_pCentDedRessyaCont->getMuPtr()->get(aCustomizeJikokuhyouContent.iRessyaIndexCont[iRessyaIndexContIndex - 1]);
									aChakuJikoku = pPrevRessya->getCentDedEkiJikoku(pPrevRessya->getValidSyuuchakuEki()).getVirtualChakujikoku();
								}
								aCdDedJikoku = aCentDedEkiJikoku.getVirtualHatsujikoku();

								tstring strText = getCdDedJikokuConv().encode(aCdDedJikoku, false, aChakuJikoku);
								*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu,
									aCentDedEkiJikoku.getEkiatsukai());
								pCDcDrawCell->setText(strText);
							}
						}
						else
						{
							aCdDedJikoku = aCentDedEkiJikoku.getVirtualHatsujikoku();

							tstring strText = getCdDedJikokuConv().encode(aCdDedJikoku, false);
							*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu,
								aCentDedEkiJikoku.getEkiatsukai());
							pCDcDrawCell->setText(strText);
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
									通過をみなしているときは、当駅発時刻部は経由無し表記にします。
										Ver2.06.04 修正　当駅に着時刻表示が無い場合は、着時刻(通過時刻)をこの欄に表示します
									駅扱い停車の場合は、着時刻欄は経由無し表記にします。
							*/
							if (pCentDedRessya->getLastOperation().getHatsuJikoku().isNull() ||
								aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka &&
								!m_bDisplayTsuukaEkiJikoku)
							{
								if (aCdDedEki.getJikokuhyouChakuJikokuDisplay())
								{
									pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
										IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"
								}
								else
								{
									aCdDedJikoku = aCentDedEkiJikoku.getChakujikoku();
									tstring strText = getCdDedJikokuConv().encode(aCdDedJikoku, true);
									*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu,
										CentDedEkiJikoku::Ekiatsukai_Tsuuka);
									pCDcDrawCell->setText(strText);
								}
							}
							else
							{
								/**
									秒単位表示OFFの場合は、切り上げ・切り捨ての処理を行いますが、
									その補助のため、着時刻が切り上げまたは30秒以上切り上げで、発時刻が切り捨ての場合は、着時刻の取得を行います。
								*/
								CdDedJikoku aChakuJikoku;
								if (!getDisplaySecondEkiJikoku() &&
									m_iSecondRoundChaku >= 1 &&
									m_iSecondRoundHatsu == 0)
								{
									aChakuJikoku = aCentDedEkiJikoku.getVirtualChakujikoku();
								}
								tstring strText = getCdDedJikokuConv().encode(pCentDedRessya->getLastOperation().getHatsuJikoku(),
									false, aChakuJikoku);
								*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu,
									aCentDedEkiJikoku.getEkiatsukai());
								pCDcDrawCell->setText(strText);
							}
						}
						else if (aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder >= -2 &&
							iRessyaIndexContIndex == aCustomizeJikokuhyouContent.iRessyaIndexCont.size() - 1 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0)
						{
							//路線外終着相当
							//Ver2.06.21 この場合は、セルの書式を次列車種別のものにする
							if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka &&
								!m_bDisplayTsuukaEkiJikoku)
							{
								*pCDcDrawCell = createCDcdRessyabangou(aCustomizeJikokuhyouContent.iRessyasyubetsuIndex);
								pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"
							}
							else
							{

								/**
									秒単位表示OFFの場合は、切り上げ・切り捨ての処理を行いますが、
									その補助のため、着時刻が切り上げまたは30秒以上切り上げで、発時刻が切り捨ての場合は、着時刻の取得を行います。
								*/
								CdDedJikoku aChakuJikoku;
								if (!getDisplaySecondEkiJikoku() &&
									m_iSecondRoundChaku >= 1 &&
									m_iSecondRoundHatsu == 0)
								{
									aChakuJikoku = aCentDedEkiJikoku.getVirtualChakujikoku();
								}
								tstring strText = getCdDedJikokuConv().encode(aCustomizeJikokuhyouContent.HatsuJikoku,
									false, aChakuJikoku);

								idxRessyasyubetsu = aCustomizeJikokuhyouContent.iRessyasyubetsuIndex;
								*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu,
									aCentDedEkiJikoku.getEkiatsukai());
								pCDcDrawCell->setText(strText);
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

							pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"
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

							pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_CONNECT));
						}
						//この駅が発時刻のみ表示の場合は、発時刻欄に着時刻を表示する
						else if (!aCdDedEki.getJikokuhyouChakuJikokuDisplay())
						{
							aCdDedJikoku = aCentDedEkiJikoku.getVirtualChakujikoku();
							tstring strText = getCdDedJikokuConv().encode(aCdDedJikoku, true);
							*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu,
								aCentDedEkiJikoku.getEkiatsukai());
							pCDcDrawCell->setText(strText);
						}
					}
					else if (iEkiOrder > iValidSyuuchakuEki)
					{
						if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= iEkiOrder)
						{
							//路線外終着
							pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"

						}
						else if (aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder >= -2 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= 0 &&
							m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] >= iEkiOrder)
						{
							//路線外終着相当
							//Ver2.06.21 この場合は、セルの書式を次列車種別のものにする

							*pCDcDrawCell = createCDcdRessyabangou(aCustomizeJikokuhyouContent.iRessyasyubetsuIndex);
							pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"

						}
						else if (aCustomizeJikokuhyouContent.iConnectEkiOrder > iEkiOrder && 
							aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
						{
							pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"
						}
						else if (aCustomizeJikokuhyouContent.iConnectEkiOrder == iEkiOrder)
						{
							pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_CONNECT));
						}
						/**
							有効終着駅の次の駅で、この列車が路線外終着ではない、路線外終着相当ではない、もしくは路線外終着欄がない時、
							この欄のすぐ上が発時刻欄かつ着時刻表示がない場合、
							この欄に"===="を描写します
							Ver2.05 この欄のすぐ上が着時刻欄の場合を追加(着時刻欄の場合は、自ずと発時刻表示無しとなる)
							Ver2.06.03
								路線外発着(相当)の検出が誤っていたのを修正、併合の場合は表示しないように修正
						*/
						if (iEkiOrder == iValidSyuuchakuEki + 1 &&
							((pCentDedRessya->getLastOperation().getAOperation() != CentDedAfterOperation::EAOperation::AOperation_Outer &&
								aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder < -2 &&
								aCustomizeJikokuhyouContent.iConnectEkiOrder < 0) ||
								m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki] < 0))
						{
							CdYColSpec aCdYColSpecPrev = m_CdYColSpecCont.ColumnNumberToSpec(iYColumnNumber - 1);
							CentDedEkiCont::CdDedEki aCdDedEkiPrev = muCdDedEki->get(iEkiOrder - 1);
							if (aCdYColSpecPrev.getEkiOrder() == iEkiOrder - 1 &&
								!aCdDedEkiPrev.getKyoukaisen() &&
								((aCdYColSpecPrev.getColumnType() == CdYColSpec::ColumnType_Ekijikoku_Hatsu &&
									!aCdDedEkiPrev.getJikokuhyouChakuJikokuDisplay()) ||
									aCdYColSpecPrev.getColumnType() == CdYColSpec::ColumnType_Ekijikoku_Chaku))
							{
								//pCDcDrawCell->setText(_T("===="));
								pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_SYUUCHAKU));
							}
						}
					}
					//中間駅の場合
					else
					{
						if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_None)
						{
							pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"
						}
						else if (pCentDedRessya->isRunBetweenNextEki(iEkiOrder))
						{
							if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka &&
								!m_bDisplayTsuukaEkiJikoku)
							{
								pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_TSUUKA));	//" ﾚ"
							}
							else if (aCdDedJikoku.isNull())
							{
								//発時刻がない場合、この駅と前の駅の間が運行ありの場合は、通過の場合はレ印、停車の場合は発時刻または○印を表示します
								if (pCentDedRessya->isRunBetweenNextEki(iEkiOrder - 1))
								{
									if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
									{
										pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
											IDS_WORD_JIKOKUHYOU_TSUUKA));	//" ﾚ"
									}
									else if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya)
									{
										CdDedJikoku aChakuJikoku = aCentDedEkiJikoku.getVirtualChakujikoku();
										if (!aChakuJikoku.isNull() &&
											!aCdDedEki.getJikokuhyouChakuJikokuDisplay())
										{
											//	時刻が設定されているかつ着時刻表示が無い場合は時刻を表示
											*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu);
											tstring strText = getCdDedJikokuConv().encode(aChakuJikoku, true);
											pCDcDrawCell->setText(strText);
										}
										else
										{
											pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
												IDS_WORD_JIKOKUHYOU_TEISYA));
										}
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
										tstring strText = getCdDedJikokuConv().encode(aChakuJikoku, true);
										*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu,
											aCentDedEkiJikoku.getEkiatsukai());
										pCDcDrawCell->setText(strText);
									}
									else//if (aChakuJikoku.isNull())
									{
										if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
										{
											pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
												IDS_WORD_JIKOKUHYOU_TSUUKA));	//" ﾚ"
										}
										else if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya)
										{
											pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
												IDS_WORD_JIKOKUHYOU_TEISYA));
										}

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
								if (!getDisplaySecondEkiJikoku() &&
									m_iSecondRoundChaku >= 1 &&
									m_iSecondRoundHatsu == 0)
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

								tstring strText = getCdDedJikokuConv().encode(aCdDedJikoku, false, aChakuJikoku);
								*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu,
									aCentDedEkiJikoku.getEkiatsukai());
								pCDcDrawCell->setText(strText);
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
									pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
										IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"
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
									if (!getDisplaySecondEkiJikoku() &&
										m_iSecondRoundChaku >= 1 &&
										m_iSecondRoundHatsu == 0)
									{
										aChakuJikoku = aCentDedEkiJikoku.getVirtualChakujikoku();
									}

									if (aHatsuJikoku.isNull())
									{
										pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
											IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"
									}
									else
									{
										tstring strText = getCdDedJikokuConv().encode(aHatsuJikoku, false, aChakuJikoku);
										*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu,
											aCentDedEkiJikoku.getEkiatsukai());
										pCDcDrawCell->setText(strText);
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
										tstring strText = getCdDedJikokuConv().encode(aHatsuJikoku, false);
										*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu,
											aCentDedEkiJikoku.getEkiatsukai());
										pCDcDrawCell->setText(strText);
									}
									else//if (aHatsuJikoku.isNull())
									{
										if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
										{
											pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
												IDS_WORD_JIKOKUHYOU_TSUUKA));	//" ﾚ"
										}
										else if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya)
										{
											pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
												IDS_WORD_JIKOKUHYOU_TEISYA));
										}

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
									if (!getDisplaySecondEkiJikoku() &&
										m_iSecondRoundChaku == 2 &&
										m_iSecondRoundHatsu <= 1)
									{
										int iHatsuEkiOrder = pCentDedRessya->getRunBetweenEkiForward(iEkiOrder);
										if (pCentDedEkiCont->isSameBrunchLoopGroup(iEkiOrder, iHatsuEkiOrder, pCentDedRessya->getRessyahoukou()))
										{
											aHatsuJikoku = pCentDedRessya->getCentDedEkiJikoku(iHatsuEkiOrder).getVirtualHatsujikoku();
										}
									}

									tstring strText = getCdDedJikokuConv().encode(aChakuJikoku, true, aHatsuJikoku);
									*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu,
										aCentDedEkiJikoku.getEkiatsukai());
									pCDcDrawCell->setText(strText);
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
										tstring strText = getCdDedJikokuConv().encode(aHatsuJikoku, false, aChakuJikoku);
										*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu,
											aCentDedEkiJikoku.getEkiatsukai());
										pCDcDrawCell->setText(strText);
									}
									else// (aHatsuJikoku.isNull())
									{
										tstring strText = getCdDedJikokuConv().encode(aChakuJikoku, true);
										*pCDcDrawCell = createCDcdEkijikoku(idxRessyasyubetsu,
											aCentDedEkiJikoku.getEkiatsukai());
										pCDcDrawCell->setText(strText);
									}
								}
							}
						}
						else//if (!pCentDedRessya->isRunBetweenNextEki(iEkiOrder)&&!pCentDedRessya->isRunBetweenNextEki(iEkiOrder-1))
						{
							//この駅の前後ともに運行なし(経由なし)の場合、この項は経由なし表示となります。

							pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI));//"||"
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
								pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_RELEASE));
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
								pCDcDrawCell->setText((LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_JIKOKUHYOU_CONNECT));
							}
						}
					}
				}
				
				//セルの背景色を指定します。
				pCDcDrawCell->setCdBrushProp(getBackColor(
					iXColumnNumber,
					iEkiOrder,
					idxRessyasyubetsu));
			}
		}
	}
}

void CCellBuilderCustomize::update02_02_02_26_setRessya_EkiOuterTerminal_Shuchaku(
	int iXColumnNumber,
	int iYColumnNumber,
	const CentDedRessya * pCentDedRessya,
	const CustomizeJikokuhyouContent& aCustomizeJikokuhyouContent,
	int iEkiOrder,
	int iCurrentRessyaShihatsuEkiOrder,
	CWndJikokuhyou * pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	const CentDedRosen* pCentDedRosen =
		m_pCDedRosenFileData->getCentDedRosen();
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		pCentDedRosen->getCentDedEkiCont()->getMuPtr(
			m_pCentDedRessyaCont->getRessyahoukou());
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
			iXColumnNumber, iYColumnNumber + 1);
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
				int idxRessyasyubetsu;
				if (pCentDedRessya == NULL)
				{
					if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
					{
						idxRessyasyubetsu = aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex;
					}
					else
					{
						idxRessyasyubetsu = aCustomizeJikokuhyouContent.iRessyasyubetsuIndex;
					}
				}
				else
				{
					idxRessyasyubetsu = pCentDedRessya->getRessyasyubetsuIndex();
				}
				*pCDcDrawCell1 = createCDcdRessyabangou(idxRessyasyubetsu);
				*pCDcDrawCell2 = createCDcdEkijikoku(idxRessyasyubetsu);
				tstring strText1;
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
							strText1 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_EkiJikokuhyou_Loop);//"環状"
						}
						else if (aCustomizeJikokuhyouContent.iOuterShuchakuEkiIndex >= 0)
						{
							strText1 = muCdDedEki->get(aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder).getOuterTerminalJikokuRyaku(
								aCustomizeJikokuhyouContent.iOuterShuchakuEkiIndex, true);
						}
						else
						{
							strText1 = muCdDedEki->get(aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder).getEkimeiJikokuhyouRyaku(true);
						}
						CdDedJikoku aCdDedJikoku
							= aCustomizeJikokuhyouContent.OuterShuchakuJikoku;
						strText2 = getCdDedJikokuConv().encode(aCdDedJikoku, true);
					}
					/**
						この列が併合表示の場合、併合表示が有効・この駅が併合駅よりも上・この駅が併合表示駅であるかここよりも下ならば、
						この項には経由なしを表示する。
					*/
					else if(aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0 &&
						iEkiOrder < aCustomizeJikokuhyouContent.iConnectEkiOrder &&
						iEkiOrder >= m_iOuterShihatsuDisplayEkiOrder[aCustomizeJikokuhyouContent.iConnectEkiOrder])
					{

						strText1 = (LPCTSTR)MfcUtil::LoadCString(
							IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
						strText2 = strText1;//"||"
						*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);
					}
				}
				else
				{
					int iValidSihatsuEki = pCentDedRessya->getValidSihatsuEki();
					int iValidSyuuchakuEki = pCentDedRessya->getValidSyuuchakuEki();
					if (iValidSihatsuEki == -1 || iValidSyuuchakuEki == -1)
					{
						strText1 = _T("");
						strText2 = _T("");
					}
					else if (iEkiOrder < iValidSihatsuEki)
					{
						if (iCurrentRessyaShihatsuEkiOrder >= 0/* &&
							iEkiOrder < iValidSihatsuEki*/)
						{
							strText1 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
							strText2 = strText1;//"||"
							*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);
						}
						else if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] <= iEkiOrder)
						{
							strText1 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
							strText2 = strText1;//"||"
							*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);
						}
						else if (aCustomizeJikokuhyouContent.iSihatsuEkiOrder >= -2 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] >= 0 &&
							m_iOuterShihatsuDisplayEkiOrder[iValidSihatsuEki] <= iEkiOrder)
						{
							//Ver2.06.21 表示書式を、前列車の種別に変更する
							idxRessyasyubetsu = aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex;
							strText1 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
							strText2 = strText1;//"||"
							*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);
						}
						else if (aCustomizeJikokuhyouContent.iReleaseEkiOrder < iEkiOrder &&
							aCustomizeJikokuhyouContent.iReleaseEkiOrder >= 0)
						{
							strText1 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
							strText2 = strText1;//"||"
							*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);
						}
					}
					else if (iValidSihatsuEki <= iEkiOrder &&
						iEkiOrder < iValidSyuuchakuEki)
					{
						if (!pCentDedRessya->isRunBetweenNextEki(iEkiOrder))
						{
							strText1 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
							strText2 = strText1;//"||"
							*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);
						}
					}
					else if (iEkiOrder >= iValidSyuuchakuEki)
					{
						/**
							(2)のパターン　pCentDedRessyaの終着駅Orderで
							m_iOuterShihatsuDisplayEkiOrderから路線外終着表示駅を取得し、
							それが当駅ならば、ここで路線外終着表示を行う
							Ver2.06.21 表示書式を、次列車の種別に変更する
						*/
						if (aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder >= -2 &&
							iEkiOrder == m_iOuterShuchakuDisplayEkiOrder[iValidSyuuchakuEki])
						{
							if (aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder < 0)
							{
								strText1 = (LPCTSTR)MfcUtil::LoadCString(
									IDS_WORD_EkiJikokuhyou_Loop);//"環状"
							}
							else if (aCustomizeJikokuhyouContent.iOuterShuchakuEkiIndex >= 0)
							{
								strText1 = muCdDedEki->get(aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder).getOuterTerminalJikokuRyaku(
									aCustomizeJikokuhyouContent.iOuterShuchakuEkiIndex, true);
							}
							else
							{
								strText1 = muCdDedEki->get(aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder).getEkimeiJikokuhyouRyaku(true);
							}
							CdDedJikoku aCdDedJikoku
								= aCustomizeJikokuhyouContent.OuterShuchakuJikoku;
							strText2 = getCdDedJikokuConv().encode(aCdDedJikoku, true);

							idxRessyasyubetsu = aCustomizeJikokuhyouContent.iRessyasyubetsuIndex;
							*pCDcDrawCell1 = createCDcdRessyabangou(idxRessyasyubetsu);
							*pCDcDrawCell2 = createCDcdEkijikoku(idxRessyasyubetsu);

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
							strText1 = aCdDedEki.getOuterTerminalJikokuRyaku(aLastOperation.getOuterShuchakuekiIndex(), true);
							if (!(aLastOperation.getOuterShuchakuJikoku().isNull()))
							{
								CdDedJikoku aCdDedJikoku
									= aLastOperation.getOuterShuchakuJikoku();
								strText2 = getCdDedJikokuConv().encode(aCdDedJikoku, true);
							}
						}
						else if (aCustomizeJikokuhyouContent.iConnectEkiOrder > iEkiOrder &&
							aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
						{
							strText1 = (LPCTSTR)MfcUtil::LoadCString(
								IDS_WORD_JIKOKUHYOU_KEIYUNASI);//"||"
							strText2 = strText1;//"||"
							*pCDcDrawCell2 = createCDcdRessyabangou(idxRessyasyubetsu);
						}
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

void CCellBuilderCustomize::update02_02_02_08_setRessya_Bikou( 
	int iXColumnNumber ,
	int iYColumnNumber,
	const CentDedRessya* pCentDedRessya ,
	const CustomizeJikokuhyouContent& aCustomizeJikokuhyouContent,
	CWndJikokuhyou* pCWndJikokuhyou ) 
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid() ;
	const CentDedRosen* pCentDedRosen = 
		m_pCDedRosenFileData->getCentDedRosen() ;
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
			int idxRessyasyubetsu;
			if (pCentDedRessya == NULL)
			{
				if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
				{
					idxRessyasyubetsu = aCustomizeJikokuhyouContent.iPrevRessyasyubetsuIndex;
				}
				else
				{
					idxRessyasyubetsu = aCustomizeJikokuhyouContent.iRessyasyubetsuIndex;
				}
			}
			else
			{
				idxRessyasyubetsu = pCentDedRessya->getRessyasyubetsuIndex();
			}
			tstring strText;
			if (pCentDedRessya != NULL)
			{
				strText = pCentDedRessya->getBikou();
			}
			*pCDcDrawCell = createCDcdRessyamei( 
				idxRessyasyubetsu );
			pCDcDrawCell->setLinesExtentX ( getBikouTextExtent().getX() ) ;
			pCDcDrawCell->setLinesExtentY ( getBikouTextExtent().getY() ) ;
			pCDcDrawCell->setText( strText );
		}
	}
}

void CCellBuilderCustomize::update02_03_updateNullRessya(
	int iXColumnNumber,
	CWndJikokuhyou* pCWndJikokuhyou)
{
	CDcdGrid* pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
	CDcdTargetGetDC	aCDcdTarget(NULL);

	CentDedRessya aRessya(m_pCentDedRessyaCont->createNullRessya());
	const CentDedRessya* pCentDedRessya = &aRessya;
	CustomizeJikokuhyouContent aCustomizeJikokuhyouContentNull;

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
				aCustomizeJikokuhyouContentNull,
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
				aCustomizeJikokuhyouContentNull,
				pCWndJikokuhyou);
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
				aCustomizeJikokuhyouContentNull,
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
				aCustomizeJikokuhyouContentNull,
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
				aCustomizeJikokuhyouContentNull,
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
				aCustomizeJikokuhyouContentNull,
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
				aCustomizeJikokuhyouContentNull,
				pCWndJikokuhyou);
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
				aCustomizeJikokuhyouContentNull,
				pCWndJikokuhyou);
		}
		break;
		case CdYColSpec::ColumnType_EkiOuter_Shihatsu1:
		{
			// --------------------------------
			//	(2.2.2.15)セル(ColumnType_Ressya, ColumnType_Outer_Shihatsu)
			// --------------------------------
			update02_02_02_25_setRessya_EkiOuterTerminal_Shihatsu(
				iXColumnNumber,
				iYColumnNumber,
				pCentDedRessya,
				aCustomizeJikokuhyouContentNull,
				aCdYColSpec.getEkiOrder(),
				-1,
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
				aCustomizeJikokuhyouContentNull,
				aCdYColSpec.getEkiOrder(),
				-1,
				-1,
				pCWndJikokuhyou);
		}
		break;
		case CdYColSpec::ColumnType_Track:
		{
			update02_02_02_09_setRessya_Track(
				iXColumnNumber,
				iYColumnNumber,
				pCentDedRessya,
				aCustomizeJikokuhyouContentNull,
				aCdYColSpec.getEkiOrder(),
				-1,
				pCWndJikokuhyou);
		}
		break;
		case CdYColSpec::ColumnType_EkiRessyabangou:
		{
			update02_02_02_19_setRessya_Ressyabangou(
				iXColumnNumber,
				iYColumnNumber,
				pCentDedRessya,
				aCustomizeJikokuhyouContentNull,
				aCdYColSpec.getEkiOrder(),
				-1,
				-1,
				pCWndJikokuhyou);
		}
		break;
		case CdYColSpec::ColumnType_EkiOperationNumber:
		{
			update02_02_02_20_setRessya_OperationNumber(
				iXColumnNumber,
				iYColumnNumber,
				pCentDedRessya,
				aCustomizeJikokuhyouContentNull,
				aCdYColSpec.getEkiOrder(),
				-1,
				-1,
				pCWndJikokuhyou);
		}
		break;
		case CdYColSpec::ColumnType_EkiRessyasyubetsu:
		{
			update02_02_02_21_setRessya_Ressyasyubetsu(
				iXColumnNumber,
				iYColumnNumber,
				pCentDedRessya,
				aCustomizeJikokuhyouContentNull,
				aCdYColSpec.getEkiOrder(),
				-1,
				-1,
				pCWndJikokuhyou);
		}
		break;
		case CdYColSpec::ColumnType_EkiRessyamei:
		{
			update02_02_02_22_setRessya_Ressyamei(
				iXColumnNumber,
				iYColumnNumber,
				pCentDedRessya,
				aCustomizeJikokuhyouContentNull,
				aCdYColSpec.getEkiOrder(),
				-1,
				-1,
				pCWndJikokuhyou);
		}
		break;
		//case CdYColSpec::ColumnType_EkiGousuu:
		//{
		//	update02_02_02_23_setRessya_Gousuu(
		//		iXColumnNumber,
		//		iYColumnNumber,
		//		pCentDedRessya,
		//		aCustomizeJikokuhyouContentTemp,
		//		aCdYColSpec.getEkiOrder(),
		//		-1,
		//		-1,
		//		-1,
		//		pCWndJikokuhyou);
		//}
		//break;
		//case CdYColSpec::ColumnType_EkiGou:
		//{
		//	update02_02_02_24_setRessya_Gou(
		//		iXColumnNumber,
		//		iYColumnNumber,
		//		pCentDedRessya,
		//		aCdYColSpec.getEkiOrder(),
		//		-1,
		//		-1,
		//		-1,
		//		pCWndJikokuhyou);
		//}
		//break;
		case CdYColSpec::ColumnType_Ekijikoku_Hatsu:
		{
			update02_02_02_07_setRessya_Hatsu(
				iXColumnNumber,
				iYColumnNumber,
				pCentDedRessya,
				aCustomizeJikokuhyouContentNull,
				aCdYColSpec.getEkiOrder(),
				-1,
				-1,
				pCWndJikokuhyou);
		}
		break;
		case CdYColSpec::ColumnType_EkiOuter_Shuchaku1:
		{
			// --------------------------------
			//	(2.2.2.16)セル(ColumnType_Ressya, ColumnType_Outer_Shuchaku)
			// --------------------------------
			update02_02_02_26_setRessya_EkiOuterTerminal_Shuchaku(
				iXColumnNumber,
				iYColumnNumber,
				pCentDedRessya,
				aCustomizeJikokuhyouContentNull,
				aCdYColSpec.getEkiOrder(),
				-1,
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
				aCustomizeJikokuhyouContentNull,
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
		= pCDcdGrid->getXColumn(iXColumnNumber);
	{
		{
			CDcdGridCell* pCDcdGridCell
				= pCDcdGrid->getCell(iXColumnNumber, 0);
			CdDcdSizeXy	aCdDcdSizeXy;
			if (pCDcdGridCell->getIfDcDraw()->getItemSize(
				&aCDcdTarget, &aCdDcdSizeXy)) {
				pCDcdGridXColumn->setColumnSize(aCdDcdSizeXy.getX());
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
			= pCDcdGridXColumn->getCDcdGridXBorder();
		Ou<CDcdLine> pCDcdLine = pCDcdGridXBorder->getIfDcDraw();

		pCDcdLine->setCdPenProp(getCdPenPropNarrowLine());

		CdDcdSizeXy aCdDcdSizeXy;
		if (pCDcdLine->getItemSize(&aCDcdTarget, &aCdDcdSizeXy))
		{
			pCDcdGridXBorder->setColumnBorderSize(aCdDcdSizeXy.getX());
		}
	}
	// ================================
	//	X列を再描画領域とします。
	// ================================
	{
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
			CdDcdZone	zoneYColumnTop = pCDcdGrid->getYColumnZone(
				&aCDcdTarget,
				0);
			CdDcdZone	zoneYColumnBottom = pCDcdGrid->getYColumnZone(
				&aCDcdTarget,
				INT_MAX);
			aCdDcdZoneXy.setY(
				zoneYColumnTop.ZoneOr(zoneYColumnBottom));
		}
		CConverter_WinGdi	aConv;
		pCWndJikokuhyou->InvalidateRect(
			&aConv.RECTOf(aCdDcdZoneXy));
	}
}

CdColorProp CCellBuilderCustomize::getBackColor(int iXColumnNumber, int iEkiOrder, int idxRessyasyubetsu)
{
	int iBackColorPattern = m_pCentDedRessyaCont->getDia()->getBackPatternIndex();
	if (iBackColorPattern == 0)
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

	// ********************************
	//	コンストラクタ
	// ********************************
CCellBuilderCustomize::CCellBuilderCustomize(
	const CDedRosenFileData* pCDedRosenFileData,
	const CentDedRessyaCont* pCentDedRessyaCont,
	const vector<CustomizeJikokuhyouContent>& contCustomizeRessyaIndex,
	bool bDisplayTsuukaEkiJikoku ,
	bool bDisplaySecondEkiJikoku ,
	bool bDisplayColonEkiJikoku,
	bool bDisplayShihatsuShuchakuEkimei,
	bool bDisplayParentSyubetsu,
	bool bDisplayTsuukaFontPerSyubetsu,
	int iEnableOperation) :
	m_pCentDedRessyaCont( pCentDedRessyaCont ) ,
	m_pCDedRosenFileData( pCDedRosenFileData ) , 
	m_contCustomizeJikokuhyouContent(contCustomizeRessyaIndex),
	m_CdXColSpecCont( pCentDedRessyaCont ,true, contCustomizeRessyaIndex) ,
	m_bDisplayTsuukaEkiJikoku( bDisplayTsuukaEkiJikoku ) ,
	m_bDisplaySecondEkiJikoku( bDisplaySecondEkiJikoku ) ,
	m_bDisplayColonEkiJikoku(bDisplayColonEkiJikoku),
	m_bDisplayShihatsuShuchakuEkimei(bDisplayShihatsuShuchakuEkimei),
	m_bDisplayParentSyubetsu(bDisplayParentSyubetsu),
	m_bDisplayTsuukaFontPerSyubetsu(bDisplayTsuukaFontPerSyubetsu),
	m_iEnableOperation(iEnableOperation)
{
	CdDedDispProp	aCdDedDispProp = m_pCDedRosenFileData->getCdDedDispProp();
	m_bDisplayRessyamei = aCdDedDispProp.getDisplayRessyamei();
	m_iSecondRoundChaku = aCdDedDispProp.getSecondRoundChaku();
	m_iSecondRoundHatsu = aCdDedDispProp.getSecondRoundHatsu();
	m_bDisplay2400 = aCdDedDispProp.getDisplay2400();
	m_iOperationNumberRows = aCdDedDispProp.getOperationNumberRows();


	m_CdYColSpecCont = CdYColSpecCont(
		pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont(),
		pCentDedRessyaCont->getRessyahoukou(),
		false, true,
		bDisplayShihatsuShuchakuEkimei,
		m_bDisplayRessyamei, iEnableOperation,
		false, false,
		m_iOperationNumberRows,false);

	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		pCDedRosenFileData->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(
			pCentDedRessyaCont->getRessyahoukou());

	m_iOuterShihatsuDisplayEkiOrder.clear();
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

	m_iOuterShuchakuDisplayEkiOrder.clear();
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

	// ********************************
	//@name	CCellBuilderCustomize-操作
	// ********************************
void CCellBuilderCustomize::update( 
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

void CCellBuilderCustomize::updateAllRessya( 
		CWndJikokuhyou* pCWndJikokuhyou ) 
{
	//　(2.1)　X列の数を設定します。CdXColSpecCont 
	//	で指定された列数とします。
	CDcdGrid*	pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid() ;
	pCDcdGrid->setXColumnCount( m_CdXColSpecCont.size() ) ;

	//　(2.2)　X列(ColumnType_Ressya )に、列車情報を設定
	//int iRessyaSize = m_pCentDedRessyaCont->size();
	int iRessyaSize = m_contCustomizeJikokuhyouContent.size();
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
			const CustomizeJikokuhyouContent& aCustomizeJikokuhyouContent =
				m_contCustomizeJikokuhyouContent[iRessyaIndex];

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
			if (bDisplayNullRessya)
			{
				update02_03_updateNullRessya(
					iXColumnNumber,
					//&aRessya ,
					pCWndJikokuhyou);
			}
			else
			{
				update02_02_updateRessya(
					iXColumnNumber,
					aCustomizeJikokuhyouContent,
					//m_pCentDedRessyaCont->getMuPtr()->get( iRessyaIndex ) ,
					pCWndJikokuhyou);
			}
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
			//CentDedRessya aRessya( m_pCentDedRessyaCont->createNullRessya() ) ;

			update02_03_updateNullRessya( 
				iXColumnNumber , 
				//&aRessya ,
				pCWndJikokuhyou ) ;
		}
	}
}

//void CCellBuilderCustomize::updateAllOperationNumber(
//	CWndJikokuhyou* pCWndJikokuhyou)
//{
//	//　(2.1)　X列の数を設定します。CdXColSpecCont 
//	//	で指定された列数とします。
//	CDcdGrid*	pCDcdGrid = pCWndJikokuhyou->getCXDcdGrid();
//	pCDcdGrid->setXColumnCount(m_CdXColSpecCont.size());
//
//	//　(2.2)　X列(ColumnType_Ressya )に、列車情報を設定
//	//int iRessyaSize = m_pCentDedRessyaCont->size();
//	int iRessyaSize = m_contCustomizeJikokuhyouContent.size();
//#pragma omp parallel for schedule(guided)
//	for (int iRessyaIndex = 0; iRessyaIndex < iRessyaSize;
//		iRessyaIndex++)
//	{
//		int iXColumnNumber = m_CdXColSpecCont.ColumnNumberFromSpec(
//			CdXColSpec(
//				CdXColSpec::ColumnType_Ressya,
//				iRessyaIndex));
//		int iYColumnNumber = m_CdYColSpecCont.ColumnNumberFromSpec(
//			CdYColSpec(CdYColSpec::ColumnType_OperationNumber), false);
//		if (iXColumnNumber >= 0 && iYColumnNumber >= 0)
//		{
//			CDcdTargetGetDC	aCDcdTarget(NULL);
//
//			const vector<int>& contCustomizeRessyaIndex = m_contCustomizeJikokuhyouContent[iRessyaIndex].iRessyaIndexCont;
//			const CentDedRessya* pCentDedRessya;
//			if (contCustomizeRessyaIndex.empty() || contCustomizeRessyaIndex.front() < 0 ||
//				contCustomizeRessyaIndex.front() >= m_pCentDedRessyaCont->size())
//			{
//				CentDedRessya aRessya(m_pCentDedRessyaCont->createNullRessya());
//				pCentDedRessya = &aRessya;
//			}
//			else
//			{
//				pCentDedRessya = m_pCentDedRessyaCont->getMuPtr()->get(contCustomizeRessyaIndex.front());
//			}
//
//			// --------------------------------
//			//	(2.2.2.12)セル(ColumnType_Ressya, ColumnType_OperationNumber)
//			// --------------------------------
//			update02_02_02_12_setRessya_OperationNumber(
//				iXColumnNumber,
//				iYColumnNumber,
//				pCentDedRessya,
//				aCustomizeJikokuhyouContent,
//				pCWndJikokuhyou);
//
//			// ================================
//			//	X列を再描画領域とします。
//			// ================================
//			CdDcdZoneXy	aCdDcdZoneXy;
//			//X列の範囲
//			{
//				CdDcdZone	zoneXColumnZone = pCDcdGrid->getXColumnZone(
//					&aCDcdTarget,
//					iXColumnNumber);
//				CdDcdZone	zoneXColumnBorderZone = pCDcdGrid->getXColumnBorderZone(
//					&aCDcdTarget,
//					iXColumnNumber);
//
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

} //namespace ViewJikokuhyou
} //namespace WndJikokuhyou

