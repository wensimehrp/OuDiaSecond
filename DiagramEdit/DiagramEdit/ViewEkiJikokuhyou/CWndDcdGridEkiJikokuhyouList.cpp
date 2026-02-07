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
//	CWndDcdGridEkiJikokuhyouList.cpp
//	$Id: CWndDcdGridEkiJikokuhyouList.cpp
// ****************************************************************
*/
#include "stdafx.h"

#include "..\resource.h"

#include "DcDraw/CDcdTargetGetDC.h"
#include "logmsg/LogMsg.h"
#include "NsOu/OuNew.h"
#include "NsOu/dynamic_castOu.h"

#include "DcdCd\DcDrawProp\CdFontProp.h"
#include "DcDraw\CDcdTarget.h"
#include "DcDraw\CDcDeviceUnitSizeX.h"
#include "DcDraw\CDcDeviceUnitSizeY.h"
#include "DcDraw\CDcdText.h"
#include "DcDraw\CaDcdTargetItemPosition.h"
#include "DcDraw\CDcdLine.h"
#include "DcDraw\CDcdTargetGetDC.h"
#include "DcDraw\CConverter_Wingdi.h"

#include "..\entDed\CentDedRosen.h"
#include "..\DiagramEdit.h"
#include "..\CRfEditCmdHolder.h"
#include "..\DedRosenFileData\EditCmd\EditCmd.h"
#include "CWndDcdGridEkiJikokuhyouList.h"
#include <NsMu\CaMui.h>
#include "CconvEkiJikokuhyouCsv.h"
#include "str\CsvDocument\CconvCsvDocument.h"
#include "str\vectorToFile.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/** 配列 a の要素数を返します。 */
#define arrayof(a) (sizeof(a)/sizeof(a[0]))


namespace ViewEkiJikokuhyou {
	

using namespace std ;

// ****************************************************************
//	CWndDcdGridEkiJikokuhyouList
// ****************************************************************
// --------------------------------
//@name 下請関数
// --------------------------------
	
//CDcdTextbox	CWndDcdGridEkiJikokuhyouList::getCDcdEkiIndex()const
//{
//	//CdFontProp aCdFontProp( getCDiagramEditDoc()->getCDedRosenFileData()->
//	//	getCdDedDispProp().getJikokuhyouFont() ) ;
//	//CdFontProp aCdFontProp(CConverter_WinGdi().CdFontPropOf(DEFAULT_GUI_FONT));
//	CdFontProp aCdFontProp(9, _T("Meiryo UI"));
//	return CDcdTextbox(_T(""),
//		aCdFontProp,
//		_T("京都"), 1, 2, 2, CdPenProp(),
//		CConverter_WinGdi().CdBrushPropOf(WHITE_BRUSH));
//};

CDcdTextbox	CWndDcdGridEkiJikokuhyouList::getCDcdEkimei()const
{
	tstring strExtent = getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp().createEkimeiExtentString() ;
	//strExtent = 路線ファイルデータに保存されている値をもとにして、
	//	作成した、文字列幅の基準文字列です。

	//CdFontProp aCdFontProp( getCDiagramEditDoc()->getCDedRosenFileData()->
	//	getCdDedDispProp().getJikokuhyouFont() ) ;
	//CdFontProp aCdFontProp(CConverter_WinGdi().CdFontPropOf(DEFAULT_GUI_FONT));
	CdFontProp aCdFontProp(9, _T("Meiryo UI"));
	return CDcdTextbox(_T("") ,
		aCdFontProp ,
		strExtent , 1 , 2 , 2 , CdPenProp() ,
		CConverter_WinGdi().CdBrushPropOf( WHITE_BRUSH ) ) ;
};
	
CDcdTextbox	CWndDcdGridEkiJikokuhyouList::getCDcdEkiJikokuhyou()const
{
	//CdFontProp aCdFontProp( getCDiagramEditDoc()->getCDedRosenFileData()->
	//	getCdDedDispProp().getJikokuhyouFont() ) ;
	//CdFontProp aCdFontProp(CConverter_WinGdi().CdFontPropOf(DEFAULT_GUI_FONT));
	CdFontProp aCdFontProp(9, _T("Meiryo UI"));
	return CDcdTextbox(_T("") ,
		aCdFontProp ,
		_T("京都京都京都") , 1 , 2 , 2 , CdPenProp() ,
		CConverter_WinGdi().CdBrushPropOf( WHITE_BRUSH ) ) ;
};
//	
//CDcdTextbox	CWndDcdGridEkiJikokuhyouList::getCDcdEkikibo()const
//{
//	//CdFontProp aCdFontProp( getCDiagramEditDoc()->getCDedRosenFileData()->
//	//	getCdDedDispProp().getJikokuhyouFont() ) ;
//	//CdFontProp aCdFontProp(CConverter_WinGdi().CdFontPropOf(DEFAULT_GUI_FONT));
//	CdFontProp aCdFontProp(9, _T("Meiryo UI"));
//	return CDcdTextbox(_T("") ,
//		aCdFontProp ,
//		_T("京都京都京都") , 1 , 2 , 2 , CdPenProp() ,
//		CConverter_WinGdi().CdBrushPropOf( WHITE_BRUSH ) ) ;
//};
//
//CDcdTextbox	CWndDcdGridEkiJikokuhyouList::getCDcdEkiTrack2Count()const
//{
//	//CdFontProp aCdFontProp( getCDiagramEditDoc()->getCDedRosenFileData()->
//	//	getCdDedDispProp().getJikokuhyouFont() ) ;
//	//CdFontProp aCdFontProp(CConverter_WinGdi().CdFontPropOf(DEFAULT_GUI_FONT));
//	CdFontProp aCdFontProp(9, _T("Meiryo UI"));
//	return CDcdTextbox(_T(""),
//		aCdFontProp,
//		_T("京都京"), 1, 2, 2, CdPenProp(),
//		CConverter_WinGdi().CdBrushPropOf(WHITE_BRUSH));
//};
//
//CDcdTextbox	CWndDcdGridEkiJikokuhyouList::getCDcdBrunchLoop()const
//{
//	//CdFontProp aCdFontProp( getCDiagramEditDoc()->getCDedRosenFileData()->
//	//	getCdDedDispProp().getJikokuhyouFont() ) ;
//	//CdFontProp aCdFontProp(CConverter_WinGdi().CdFontPropOf(DEFAULT_GUI_FONT));
//	CdFontProp aCdFontProp(9, _T("Meiryo UI"));
//	return CDcdTextbox(_T(""),
//		aCdFontProp,
//		_T("京都京都京都京都"), 1, 2, 2, CdPenProp(),
//		CConverter_WinGdi().CdBrushPropOf(WHITE_BRUSH));
//};
//	
//
//
//CdEkiXColSpecCont CWndDcdGridEkiJikokuhyouList::createXColSpecCont() 
//{
//	CdEkiXColSpecCont aSpecCont( 
//		getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont() ,
//		getDisplaySettingMode()) ;
//	return aSpecCont ;
//}
//CdEkiYColSpecCont CWndDcdGridEkiJikokuhyouList::createYColSpecCont() 
//{
//	CdEkiYColSpecCont aSpecCont( 
//		getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont() ) ;
//	return aSpecCont ;
//}	
//CdEkiXColSpec CWndDcdGridEkiJikokuhyouList::getXColSpecOfFocus() 
//{
//	CdEkiXColSpec aSpec ;
//	CdDcdPosXy aPos = getCFocus()->getFocusCellColumnNumber() ;
//	if ( aPos != getCFocus()->ColumnNumberPosXy_NULL() )
//	{
//		CdEkiXColSpecCont aSpecCont( 
//			getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont(),
//			getDisplaySettingMode()) ;
//		aSpec = aSpecCont.ColumnNumberToSpec( aPos.getX() ) ;
//	}
//	return aSpec ;
//}	
//CdEkiYColSpec CWndDcdGridEkiJikokuhyouList::getYColSpecOfFocus() 
//{
//	CdEkiYColSpec aSpec ;
//	CdDcdPosXy aPos = getCFocus()->getFocusCellColumnNumber() ;
//	if ( aPos != getCFocus()->ColumnNumberPosXy_NULL() )
//	{
//		CdEkiYColSpecCont aSpecCont( 
//			getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont() ) ;
//		aSpec = aSpecCont.ColumnNumberToSpec( aPos.getY() ) ;
//	}
//	return aSpec ;
//}	
	
	
	
//bool CWndDcdGridEkiJikokuhyouList::
//createCmd( ECreateCmd eCreateCmd , Ou<DedRosenFileData::EditCmd::CRfEditCmd_Eki>* ppCmd )
//{
//	bool bRv = false ;
//	Ou<DedRosenFileData::EditCmd::CRfEditCmd_Eki> pCmd ;
//
//	CdEkiYColSpecCont aCdYColSpecCont = createYColSpecCont() ;
//	CdEkiYColSpec  aCdYColSpecOfFocus = getYColSpecOfFocus() ;
//
//	// ********************************
//	//	ECreateCmd_NewItem
//	//　新規アイテムを対象としたコマンドを生成します。
//	// ********************************
//	if ( eCreateCmd == ECreateCmd_NewItem )
//	{
//		//ビュー上で複数選択がOFF
//		if ( getCSelect()->getSelectedCellCount() == 0 )
//		{
//			//	新規アイテムの、初期オブジェクト
//			//	駅Indexが0の場合は、駅時刻形式を「上り着時刻」とします。
//			CentDedEki aNewEki ;
//			if ( aCdYColSpecOfFocus.getEkiIndex() == 0 )
//			{
//				aNewEki.setEkijikokukeisiki( CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ) ;
//			}
//
//
//			//	ビュー上で複数選択がOFF・フォーカスセルが既存アイテム上にある場合: 
//			//
//			//- m_iDiaIndex = フォーカスセルのアイテムIndex、m_iIndexSize = 0
//			//- m_CentDedEkiCont = 新規作成時のアイテムの既定値
//			//- CaMuiSelect = 当該アイテムを選択。
//			if ( aCdYColSpecOfFocus.getColumnType() == CdEkiYColSpec::ColumnType_Eki )
//			{
//				bRv = true ;
//				if ( ppCmd != NULL )
//				{
//					pCmd = OuNew<DedRosenFileData::EditCmd::CRfEditCmd_Eki>( 
//						new CRfEditCmd_Eki( 
//							*getCDiagramEditDoc()->getCDedRosenFileData() , 
//							aCdYColSpecOfFocus.getEkiIndex() , 
//							0 , m_bAdjustByEkijikokukeisiki ) ) ;
//					pCmd->getCaMuiSelect()->insert( aNewEki , INT_MAX ) ;
//					pCmd->getCaMuiSelect()->setSelectAll( true ) ;
//				}
//			}
//
//			//　ビュー上で複数選択がOFF・フォーカスセルが新規アイテム位置にある場合:
//			//- m_iDiaIndex = 末尾アイテムIndex+1、m_iIndexSize = 0
//			//- m_CentDedEkiCont = 新規作成時のアイテムの既定値
//			//- CaMuiSelect = 当該アイテムを選択。
//			else if ( aCdYColSpecOfFocus.getColumnType() == CdEkiYColSpec::ColumnType_NewEki )
//			{
//				bRv = true ;
//				if ( ppCmd != NULL )
//				{
//					pCmd = OuNew<DedRosenFileData::EditCmd::CRfEditCmd_Eki>( 
//						new CRfEditCmd_Eki( 
//							*getCDiagramEditDoc()->getCDedRosenFileData() , 
//							aCdYColSpecOfFocus.getEkiIndex() , 
//							0 , m_bAdjustByEkijikokukeisiki ) ) ;
//					pCmd->getCaMuiSelect()->insert( aNewEki , INT_MAX ) ;
//					pCmd->getCaMuiSelect()->setSelectAll( true ) ;
//				}
//			}
//		}
//		// 　ビュー上で複数選択ON:
//		//	 - NULLを返します([14/05/18]旧:複数選択OFFの場合と同じ動作)
//
//	}
//	// ********************************
//	//	ECreateCmd_Focus
//	//　フォーカスセル上の1列車を対象としたコマンドを生成します。
//	// ********************************
//	if ( eCreateCmd == ECreateCmd_Focus )
//	{
//		//ビュー上で複数選択がOFF
//		if ( getCSelect()->getSelectedCellCount() == 0 )
//		{
//			//ビュー上で複数選択がOFF・フォーカスセルが既存アイテム上にある場合: 
//			//- m_iDiaIndex = フォーカスセルのアイテムIndex、m_iIndexSize = 1
//			//- m_CentDedRessyaCont = フォーカスセル上のアイテム1個のコピー
//			//- m_CaMuiSelect = フォーカスセル上のアイテムを選択。
//			if ( aCdYColSpecOfFocus.getColumnType() == CdEkiYColSpec::ColumnType_Eki )
//			{
//				bRv = true ;
//				if ( ppCmd != NULL )
//				{
//					pCmd = OuNew<DedRosenFileData::EditCmd::CRfEditCmd_Eki>( 
//						new CRfEditCmd_Eki( 
//							*getCDiagramEditDoc()->getCDedRosenFileData() , 
//							aCdYColSpecOfFocus.getEkiIndex() , 
//							1 , m_bAdjustByEkijikokukeisiki ) ) ;
//					pCmd->getCaMuiSelect()->setSelectAll( true ) ;
//				}
//			}
//
//			//ビュー上で複数選択がOFF・フォーカスセルが新規アイテム位置にある場合: 
//			//- NULLを返します。
//		}
//		//ビュー上で複数選択ON
//		// - NULLを返します([14/05/18]旧:複数選択OFFの場合と同じ動作)
//
//	}
//	// ********************************
//	//	ECreateCmd_Select
//	//　既存の単数または複数選択されている列車を対象とした
//	//	コマンドを生成します。
//	// ********************************
//	if ( eCreateCmd == ECreateCmd_Select )
//	{
//		//ビュー上で複数選択がOFF・フォーカスセルが既存アイテム上にある場合: 
//		//- m_iDiaIndex = フォーカスセルのアイテムIndex、m_iIndexSize = 1
//		//- m_CentDedRessyaCont = フォーカスセルのあるアイテム1個のコピー
//		//- CaMuiSelect = 当該列車を選択。
//		if ( getCSelect()->getSelectedCellCount() == 0 
//			&& aCdYColSpecOfFocus.getColumnType() == CdEkiYColSpec::ColumnType_Eki )
//		{
//			bRv = true ;
//			if ( ppCmd != NULL )
//			{
//				pCmd = OuNew<DedRosenFileData::EditCmd::CRfEditCmd_Eki>( 
//					new CRfEditCmd_Eki( 
//						*getCDiagramEditDoc()->getCDedRosenFileData() , 
//						aCdYColSpecOfFocus.getEkiIndex() , 
//						1 , m_bAdjustByEkijikokukeisiki ) ) ;
//				pCmd->getCaMuiSelect()->setSelectAll( true ) ;
//			}
//		}
//
//		//　時刻表ビュー上で複数選択がOFF・フォーカスセルが新規列車位置にある場合: 
//		// - NULLを返します。
//
//		//　時刻表ビュー上で複数選択ON
//		// - m_iDiaIndex = 選択されている列車の先頭index
//		// - m_iIndexSize = 選択されている列車の末尾index-先頭index+1
//		// - m_CentDedRessyaCont = 選択されている列車の先頭indexから
//		//  末尾indexまでの列車のコピー
//		// - CaMuiSelect は、フォーカスセルに合わせて列車を選択。
//		//
//		//(A)の位置で処理します。
//	}
//
//
//	// ********************************
//	//		ECreateCmd_All ,
//	//　全列車を対象としたコマンドを生成します。
//	// ********************************
//	if ( eCreateCmd == ECreateCmd_All )
//	{
//		// ビュー上で複数選択がOFF・フォーカスセルが既存アイテム上にある場合: 
//		//
//		//- m_iDiaIndex = 0、m_iIndexSize = アイテムの数
//		//- m_CentDedRessyaCont = 全アイテムのコピー
//		//- m_CaMuiSelect は、全アイテムを選択。
//		//
//		// ビュー上で複数選択がOFF・フォーカスセルが新規アイテム位置にある場合: 
//		//
//		//- m_iDiaIndex = 0、m_iIndexSize = アイテムの数
//		//- m_CentDedRessyaCont = 全アイテムのコピー
//		//- CaMuiSelect は、全アイテムを選択。
//		if ( getCSelect()->getSelectedCellCount() == 0 
//			&& ( aCdYColSpecOfFocus.getColumnType() == CdEkiYColSpec::ColumnType_Eki 
//			|| aCdYColSpecOfFocus.getColumnType() == CdEkiYColSpec::ColumnType_NewEki ) )
//		{
//			bRv = true ;
//			if ( ppCmd != NULL )
//			{
//				pCmd = OuNew<DedRosenFileData::EditCmd::CRfEditCmd_Eki>( 
//					new CRfEditCmd_Eki( 
//						*getCDiagramEditDoc()->getCDedRosenFileData() , 
//						0 , 
//						aCdYColSpecCont.getEkiCount() ,
//						m_bAdjustByEkijikokukeisiki ) ) ;
//				pCmd->getCaMuiSelect()->setSelectAll( true ) ;
//			}
//		}
//
//		// ビュー上で複数選択ON
//		//
//		//- m_iDiaIndex = 選択されているアイテムの先頭index
//		//- m_iIndexSize = 選択されているアイテムの末尾index-先頭index+1
//		//- m_CentDedRessyaCont = 選択されているアイテムの先頭indexから
//		//末尾indexまでのアイテムのコピー
//		//- m_CaMuiSelect は、セルの選択に合わせてアイテムを選択。
//		//
//		//(A)の位置で処理します。
//	}
//
//	// ********************************
//	//	(A)ECreateCmd_Select・ECreateCmd_All で
//	//　複数選択されている列車を対象とした
//	//	コマンドを生成します。
//	// ********************************
//	if ( eCreateCmd == ECreateCmd_Select 
//		|| eCreateCmd == ECreateCmd_All )
//	{
//		if ( getCSelect()->getSelectedCellCount() > 0 )
//		{
//			//	選択されているアイテムのIndexを取得
//			deque<int> contiEkiIndex ;
//			for ( int iColumnNumber = 0 ; iColumnNumber < getCXDcdGrid()->getYColumnCount() ;iColumnNumber ++ )
//			{
//				if ( getCSelect()->getYColumnNumberSelected( iColumnNumber ) )
//				{
//					CdEkiYColSpec aCdYColSpec = aCdYColSpecCont.ColumnNumberToSpec( iColumnNumber ) ;
//					if ( aCdYColSpec.getColumnType() == CdEkiYColSpec::ColumnType_Eki )
//					{
//						contiEkiIndex.push_back( aCdYColSpec.getEkiIndex() ) ;
//					}
//				}
//			}
//			//contiEkiIndex = 列の複数選択が実施されている場合は、
//			//	選択されている駅Indexが格納されます。
//			//	そうでない場合は、空です。
//
//			if ( contiEkiIndex.size() > 1 )
//			{
//				bRv = true ;
//				if ( ppCmd != NULL )
//				{
//					//	コマンドオブジェクト内に、選択されている駅の先頭から末尾までの
//					//	駅を格納します(先頭・末尾以外には、選択されていない駅が
//					//	含まれている場合もあります)
//					pCmd = OuNew<DedRosenFileData::EditCmd::CRfEditCmd_Eki>( 
//						new CRfEditCmd_Eki( 
//							*getCDiagramEditDoc()->getCDedRosenFileData() ,
//							contiEkiIndex.front() , 
//							contiEkiIndex.back() - contiEkiIndex.front() + 1 ,
//							m_bAdjustByEkijikokukeisiki ) ) ;
//
//					//	コマンドオブジェクトの
//					//	m_CentDedRessyaContSrc  内の列車を選択します。
//					pCmd->getCaMuiSelect()->setSelectAll( false ) ;
//					for ( int i = 0 ; i < (int)contiEkiIndex.size() ; i ++ )
//					{
//						pCmd->getCaMuiSelect()->setSelect( contiEkiIndex[i] - contiEkiIndex.front()  , true ) ;
//					}
//				}
//			}
//		}
//	}
//	// ================================
//	if ( ppCmd != NULL && pCmd != NULL )
//	{
//		*ppCmd = pCmd ;
//	}
//	return bRv ;
//}
	// --------------------------------
	//@name OnUpdate の下請関数
	// --------------------------------

/**
	CentDedEki::EEkijikokukeisiki と、文字列リソースIDの対応表
	17.4.14 下り発着・上り発着を追加_by_d_mania
*/
//struct {
//	CentDedEki::EEkijikokukeisiki	m_eValue ;
//	int m_iId ;
//}	nameEEkijikokukeisiki[] = {
//	{ CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsu ,IDS_WORD_Jikokukeisiki_Hatsu } ,
//	{ CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ,IDS_WORD_Jikokukeisiki_Hatsuchaku } ,
//	{ CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ,IDS_WORD_Jikokukeisiki_KudariChaku } ,
//	{ CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ,IDS_WORD_Jikokukeisiki_NoboriChaku } ,
//	{ CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku ,IDS_WORD_Jikokukeisiki_KudariHatsuchaku } ,
//	{ CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku ,IDS_WORD_Jikokukeisiki_NoboriHatsuchaku } ,
//};

/**
	CentDedEki::EEkikibo と、文字列リソースIDの対応表
*/
//struct {
//	CentDedEki::EEkikibo	m_eValue ;
//	int m_iId ;
//}	nameEkikibo[] = {
//	{ CentDedEki::EEkikibo::Ekikibo_Ippan , IDS_WORD_Ekikibo_Ippan } ,
//	{ CentDedEki::EEkikibo::Ekikibo_Syuyou , IDS_WORD_Ekikibo_Syuyou } ,
//};


void CWndDcdGridEkiJikokuhyouList::OnUpdate_setCentDedEki_To_Column( 
	int iYColumnNumber , const CentDedEki& aCentDedEki)
{
	if ( m_bWaitForActivate )
	{
		//	ビューの更新が更新されているなら、後続の処理は行いません
		return;
	}
	// ****************************************************************
	//	ビューの更新が保留されていない
	// ****************************************************************

	bool bIsNull = aCentDedEki.getEkimei().empty() ;
	// --------------------------------
	//	列のサイズを設定
	// --------------------------------
	{
		CDcdTargetGetDC	aCDcdTarget( NULL ) ;
		// --------------------------------
		//	Y列
		// --------------------------------
		{
			CdDcdSizeXy	sizeEkimei ;
			CDcdTextbox	aCDcdTextbox( 
				getCDcdEkimei() ) ;
			aCDcdTextbox.getItemSize( 
				&aCDcdTarget , &sizeEkimei ) ;

			getCXDcdGrid()->getYColumn( iYColumnNumber )
				->setColumnSize( sizeEkimei.getY() ) ;
		}
	}
	// --------------------------------
	//	セルの属性を設定
	// --------------------------------
	{
		//	駅名列の DcDraw の属性を設定
		Ou<CDcdTextbox>	pCDcdTextbox = 
			(getCXDcdGrid()->getCell(0, iYColumnNumber )->getIfDcDraw());
		*pCDcdTextbox = this->getCDcdEkimei() ;
	}
	{
		//	下り駅時刻表の DcDraw の属性を設定
		Ou<CDcdTextbox>	pCDcdTextbox = 
			(getCXDcdGrid()->getCell( 1, iYColumnNumber )->getIfDcDraw());
		*pCDcdTextbox = this->getCDcdEkiJikokuhyou() ;
	}
	{
		//	上り駅時刻表の DcDraw の属性を設定
		Ou<CDcdTextbox>	pCDcdTextbox =
			(getCXDcdGrid()->getCell(2, iYColumnNumber)->getIfDcDraw());
		*pCDcdTextbox = this->getCDcdEkiJikokuhyou();
	}
	
	// --------------------------------
	//	セルのテキストを設定
	// --------------------------------
	//	駅名
	{
		Ou<CDcdTextbox>(getCXDcdGrid()
			->getCell(0,iYColumnNumber )->getIfDcDraw())
				->setText( aCentDedEki.getEkimei() )  ;	
	}
	//	下り駅時刻表
	{
		CString strText;
		if (aCentDedEki.getEkijikokukeisiki() != CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku)
		{
			if (getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getKudariDiaAlias().empty())
			{
				strText.LoadString(IDS_WORD_Kudari);
			}
			else
			{
				strText = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getKudariDiaAlias().c_str();
			}
		}
		Ou<CDcdTextbox>(getCXDcdGrid()
			->getCell(1,iYColumnNumber)->getIfDcDraw())
			->setText((LPCTSTR)strText);
	}
	//	上り駅時刻表
	{
		CString strText;
		if (aCentDedEki.getEkijikokukeisiki() != CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku)
		{
			if (getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getNoboriDiaAlias().empty())
			{
				strText.LoadString(IDS_WORD_Nobori);
			}
			else
			{
				strText = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getNoboriDiaAlias().c_str();
			}
		}
		Ou<CDcdTextbox>(getCXDcdGrid()
			->getCell(2, iYColumnNumber)->getIfDcDraw())
			->setText((LPCTSTR)strText);
	}
	// --------------------------------
	//	境界線
	// --------------------------------
	//{
	//	bool bKyoukaisen = false;
	//	if (aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku &&
	//		aCentDedEki.getBrunchCoreEkiIndex() >= 0)
	//	{
	//		bKyoukaisen = true;
	//	}
	//	else if (aCentDedEkiNext.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku &&
	//		aCentDedEkiNext.getBrunchCoreEkiIndex() >= 0)
	//	{
	//		bKyoukaisen = true;
	//	}
	//	else if (aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku && 
	//		aCentDedEkiNext.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku)
	//	{
	//		bKyoukaisen = true;
	//	}
	//	CdPenProp aCdPenProp = getCdPenPropNormal() ;
	//	if ( !bIsNull ){
	//		if (bKyoukaisen){
	//			aCdPenProp = getCdPenPropBold() ;
	//		}
	//	}
	//	Ou<CDcdLine>
	//		( getCXDcdGrid()->getYBorder( iYColumnNumber )->getIfDcDraw())
	//			->setCdPenProp( aCdPenProp ) ;
	//}

	// --------------------------------
	//	グリッド全体を更新領域とします
	// --------------------------------
	//	境界線の太さが変動した場合は、
	//	境界線・およびそれより下のすべてのセルの更新が必要です。
	//	これに対応するため、 CWndDcdGridEkiJikokuhyouList では、
	//	駅の属性の更新のたびに
	//	グリッド全域を更新します。
	//InvalidateGrid() ;
}

void CWndDcdGridEkiJikokuhyouList::OnUpdate_All() 
{
	CView *pView = getCDiagramEditApp()->getCMainFrame()->
		getMDIChildActiveView() ;
	if ( GetParent() != pView )
	{
		// ****************************************************************
		//	ビューがアクティブではない
		// ****************************************************************
		m_bWaitForActivate = true ;
	}
	else
	{
		// ****************************************************************
		//	ビューがアクティブ
		// ****************************************************************
		CWaitCursor	aCWaitCursor ;	

		// --------------------------------
		//	ビューの更新を行うために OnUpdate_XXX() を呼び出すなら
		//	あらかじめ以下のフラグを false にしなくてはなりません
		m_bWaitForActivate = false ;

		//	コマンドオブジェクト実行によるセル移動でセル選択にならないように、
		//	セル選択を解除し、セル選択機能も一時的に中止します。
		clearSelect() ;
		CPropStack aPropStack( this ) ;
		aPropStack
			.CBoxSelect_setIsEnable( false )
			.CRandomSelect_setIsEnable( false )  ;


		// --------------------------------
		//	ビューを更新
		// --------------------------------
		CDiagramEditDoc* pCDiagramEditDoc = getCDiagramEditDoc() ;
		const CentDedRosen*	pCentDedRosen = 
			pCDiagramEditDoc->getCDedRosenFileData()->getCentDedRosen() ;
		const Mu<const CentDedEki*>* pCentDedEkiContGet = 
			pCentDedRosen->getCentDedEkiCont()->getMuPtr() ;

		//OnCreate_Header();

	// --------------------------------
	//	列の数を指定
	// --------------------------------
		getCXDcdGrid()->setXColumnCount(3);
		getCXDcdGrid()->setYColumnCount(
			pCentDedEkiContGet->size());
		getCXDcdGrid()->setYFixColumnCount(0);

		// --------------------------------
		//	列のサイズを設定
		// --------------------------------
		{
			CDcdTargetGetDC	aCDcdTarget(NULL);
			// --------------------------------
			//	X列
			// --------------------------------
			{
				//	駅名
				CDcdGridXColumn* pCDcdGridXColumn = getCXDcdGrid()->getXColumn(0);
				CdDcdSizeXy	sizeEkimei;
				CDcdTextbox	aCDcdTextbox(getCDcdEkimei());
				aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeEkimei);
				pCDcdGridXColumn->setColumnSize(sizeEkimei.getX());
			}
			{
				//	下り駅時刻表
				CDcdGridXColumn* pCDcdGridXColumn = getCXDcdGrid()->getXColumn(1);
				CdDcdSizeXy	sizeEkiJikokuhyou;
				CDcdTextbox	aCDcdTextbox(
					getCDcdEkiJikokuhyou());
				aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeEkiJikokuhyou);
				pCDcdGridXColumn->setColumnSize(sizeEkiJikokuhyou.getX());
			}
			{
				//	上り駅時刻表
				CDcdGridXColumn* pCDcdGridXColumn = getCXDcdGrid()->getXColumn(2);
				CdDcdSizeXy	sizeEkiJikokuhyou;
				CDcdTextbox	aCDcdTextbox(
					getCDcdEkiJikokuhyou());
				aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeEkiJikokuhyou);
				pCDcdGridXColumn->setColumnSize(sizeEkiJikokuhyou.getX());
			}
		}

		////	駅名列の幅を設定する
		//{
		//	CDcdTargetGetDC	aTarget ;
		//	CDcdTextbox aCDcd = this->getCDcdEkimei() ;
		//	CdDcdSizeXy	aCdDcdSizeXy ;
		//	aCDcd.getItemSize( &aTarget , &aCdDcdSizeXy ) ;
		//	getCXDcdGrid()->getXColumn( 1 )->setColumnSize( 
		//		aCdDcdSizeXy.getX() ) ;
		//}
		int iEkiSize = pCentDedEkiContGet->size();
		//	各セルに、データを設定
//#pragma omp parallel for schedule(static)
		for (int idxEki = 0 ; idxEki < iEkiSize;
				idxEki ++ ){
			const CentDedEki* pCentDedEki = pCentDedEkiContGet->get( idxEki ) ;

			OnUpdate_setCentDedEki_To_Column(
				idxEki, *pCentDedEki);

			//const CentDedEki* pCentDedEkiNext = pCentDedEkiContGet->get(idxEki + 1);
			//OnUpdate_setCentDedEki_To_Column( idxEki + 1 , *pCentDedEki, *pCentDedEkiNext) ;
		}

		InvalidateGrid() ;

//#pragma omp barrier	
		//OnUpdate_setCentDedEki_To_Column(idxEki + 1, CentDedEki(), CentDedEki());
		// ****************************************************************
	}
}

//void CWndDcdGridEkiJikokuhyouList::OnCreate_Header()
//{
//	// --------------------------------
//	//	列の数を指定
//	// --------------------------------
//	getCXDcdGrid()->setXColumnCount(3);
//	getCXDcdGrid()->setYColumnCount(2);
//	getCXDcdGrid()->setYFixColumnCount(1);
//
//	//getCXDcdGrid()->setXFixColumnCount(2);
//
//	// --------------------------------
//	//	列のサイズを設定
//	// --------------------------------
//	{
//		CDcdTargetGetDC	aCDcdTarget(NULL);
//		// --------------------------------
//		//	X列
//		// --------------------------------
//		{
//			//	駅名
//			CDcdGridXColumn* pCDcdGridXColumn = getCXDcdGrid()->getXColumn(0);
//			CdDcdSizeXy	sizeEkimei;
//			CDcdTextbox	aCDcdTextbox(getCDcdEkimei());
//			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeEkimei);
//			pCDcdGridXColumn->setColumnSize(sizeEkimei.getX());
//		}
//		{
//			//	下り駅時刻表
//			CDcdGridXColumn* pCDcdGridXColumn = getCXDcdGrid()->getXColumn(1);
//			CdDcdSizeXy	sizeEkiJikokuhyou;
//			CDcdTextbox	aCDcdTextbox(
//				getCDcdEkiJikokuhyou());
//			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeEkiJikokuhyou);
//			pCDcdGridXColumn->setColumnSize(sizeEkiJikokuhyou.getX());
//		}
//		{
//			//	上り駅時刻表
//			CDcdGridXColumn* pCDcdGridXColumn = getCXDcdGrid()->getXColumn(2);
//			CdDcdSizeXy	sizeEkiJikokuhyou;
//			CDcdTextbox	aCDcdTextbox(
//				getCDcdEkiJikokuhyou());
//			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeEkiJikokuhyou);
//			pCDcdGridXColumn->setColumnSize(sizeEkiJikokuhyou.getX());
//		}
//		// --------------------------------
//		//	Y列
//		// --------------------------------
//		{
//			CdDcdSizeXy	sizeEkimei;
//			CDcdTextbox	aCDcdTextbox(
//				getCDcdEkimei());
//			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeEkimei);
//
//			getCXDcdGrid()->getYColumn(0)->setColumnSize(sizeEkimei.getY());
//			getCXDcdGrid()->getYColumn(1)->setColumnSize(sizeEkimei.getY());
//		}
//	}
//	// --------------------------------
//	//	最上行にテキストを設定
//	// --------------------------------
//	{
//		CConverter_WinGdi	aConv;
//
//		CdDrawTextProp	aCdDrawTextProp(
//			CdFontProp(9, _T("Meiryo UI")),
//			//aConv.CdFontPropOf( DEFAULT_GUI_FONT ) ,
//			aConv.CdColorPropOfSysColor(COLOR_MENUTEXT));
//		CdBrushProp	aCdBrushProp(aConv.CdColorPropOfSysColor(COLOR_MENU));
//
//
//
//		{
//			//	駅名
//			CDcdGridCell* pCDcdGridCell = getCXDcdGrid()->getCell(0, 0);
//
//			Ou<CDcdTextbox>	pCDcdTextbox =
//				pCDcdGridCell->getIfDcDraw();
//			pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
//			pCDcdTextbox->setCdBrushProp(aCdBrushProp);
//
//			CString	aString;
//			aString.LoadString(IDS_WORD_Ekimei);
//			Ou<CDcdTextbox>(pCDcdGridCell->getIfDcDraw())->setText((LPCTSTR)aString);
//		}
//		{
//			//	下り駅時刻表
//			CDcdGridCell* pCDcdGridCell = getCXDcdGrid()->getCell(1, 0);
//
//			Ou<CDcdTextbox>	pCDcdTextbox =
//				pCDcdGridCell->getIfDcDraw();
//			pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
//			pCDcdTextbox->setCdBrushProp(aCdBrushProp);
//
//			CString	aString;
//			aString.LoadString(IDS_WORD_KUDARIEKIJIKOKUHYOU);
//			Ou<CDcdTextbox>(pCDcdGridCell->getIfDcDraw())->setText((LPCTSTR)aString);
//		}
//		{
//			//	上り駅時刻表
//			CDcdGridCell* pCDcdGridCell = getCXDcdGrid()->getCell(1, 0);
//
//			Ou<CDcdTextbox>	pCDcdTextbox =
//				pCDcdGridCell->getIfDcDraw();
//			pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
//			pCDcdTextbox->setCdBrushProp(aCdBrushProp);
//
//			CString	aString;
//			aString.LoadString(IDS_WORD_KUDARIEKIJIKOKUHYOU);
//			Ou<CDcdTextbox>(pCDcdGridCell->getIfDcDraw())->setText((LPCTSTR)aString);
//		}
//	}
//}

	// --------------------------------
	//@name メニューコマンドの下請関数
	// --------------------------------
//int CWndDcdGridEkiJikokuhyouList::OnEditCut_Process( BOOL bQueryEnable )
//{
//	int iRv = 0 ;
//	Ou<CRfEditCmd_Eki> pCmd ;
//	Ou<CRfEditCmd_Eki>* ppCmd = NULL ;
//	if ( !bQueryEnable ){	ppCmd = &pCmd ;}
//	
//	// ****************************************************************
//	//	コマンドの有効・無効判定
//	// ****************************************************************
//	if ( iRv >= 0 )
//	{
//		if (!createCmd(CWndDcdGridEkiJikokuhyouList::ECreateCmd_Focus, ppCmd))
//		//if ( !createCmd( CWndDcdGridEkiJikokuhyouList::ECreateCmd_Select , ppCmd ) )
//		{
//			iRv = -1 ;	//	セルの位置が正しくありません。
//		}
//	}
//	//基幹駅および終点駅になっている場合は、コマンド無効です。
//	if (iRv >= 0)
//	{
//		if (getCSelect()->getSelectedCellCount() == 0)
//		{
//			const Mu< const CentDedEki* >* pCentDedEkiCont = getCDiagramEditDoc()->getCDedRosenFileData()
//				->getCentDedRosen()->getCentDedEkiCont()->getMuPtr();
//			CdEkiYColSpec aCdEkiYColSpec = getYColSpecOfFocus();
//			int iEkiIndexSelect = aCdEkiYColSpec.getEkiIndex();
//			for (int idx = 0; idx < pCentDedEkiCont->size() && iRv >= 0 ; idx++)
//			{
//				if (iEkiIndexSelect != idx)
//				{
//					if (pCentDedEkiCont->get(idx)->getBrunchCoreEkiIndex() == iEkiIndexSelect)
//					{
//						iRv = -2; //選択された駅は、他の駅から基幹駅に指定されています
//					}
//					else if (pCentDedEkiCont->get(idx)->getLoopOriginEkiIndex() == iEkiIndexSelect)
//					{
//						iRv = -3; //選択された駅は、他の駅から起点駅に指定されています
//					}
//				}
//			}
//		}
//		else if (getCSelect()->getSelectedCellCount() > 0)
//		{
//			const Mu< const CentDedEki* >* pCentDedEkiCont = getCDiagramEditDoc()->getCDedRosenFileData()
//				->getCentDedRosen()->getCentDedEkiCont()->getMuPtr();
//			CdEkiYColSpecCont aCdYColSpecCont = createYColSpecCont();
//
//			for (int iColumnNumber = 0; iColumnNumber < getCXDcdGrid()->getYColumnCount() && iRv >= 0; iColumnNumber++)
//			{
//				if (getCSelect()->getYColumnNumberSelected(iColumnNumber))
//				{
//					CdEkiYColSpec aCdEkiYColSpec = aCdYColSpecCont.ColumnNumberToSpec(iColumnNumber);
//					int iEkiIndexSelect = aCdEkiYColSpec.getEkiIndex();
//					for (int idx = 0; idx < pCentDedEkiCont->size() && iRv >= 0; idx++)
//					{
//						if (iEkiIndexSelect != idx)
//						{
//							if (pCentDedEkiCont->get(idx)->getBrunchCoreEkiIndex() == iEkiIndexSelect)
//							{
//								iRv = -2; //選択された駅は、他の駅から基幹駅に指定されています
//							}
//							else if (pCentDedEkiCont->get(idx)->getLoopOriginEkiIndex() == iEkiIndexSelect)
//							{
//								iRv = -3; //選択された駅は、他の駅から起点駅に指定されています
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//	// ****************************************************************
//	if ( !bQueryEnable && iRv >= 0 )
//	{
//		// ****************************************************************
//		//	コマンドの実行
//		// ****************************************************************
//		// -------------------------------- 
//		//	クリップボードに転送
//		// --------------------------------
//		getCDiagramEditDoc()->CentDedEki_To_Cliboard( 
//			pCmd->getCaMuiSelect() ) ;
//
//		// --------------------------------
//		//	コマンドオブジェクトの列車を編集
//		// --------------------------------
//		{
//			pCmd->getCaMuiSelect()->erase( 0 , INT_MAX ) ;
//		}
//		// --------------------------------
//		//	コマンドオブジェクトを実行
//		// --------------------------------
//		{
//			getCDiagramEditDoc()->executeEditCmd( pCmd ) ;
//		}
//		// ****************************************************************
//		//	エラーメッセージ
//		// ****************************************************************
//
//		// ****************************************************************
//	}
//	return iRv ;	
//
//}
//int CWndDcdGridEkiJikokuhyouList::OnEditCopy_Process( BOOL bQueryEnable )
//{
//	int iRv = 0 ;
//	Ou<CRfEditCmd_Eki> pCmd ;
//	Ou<CRfEditCmd_Eki>* ppCmd = NULL ;
//	if ( !bQueryEnable ){	ppCmd = &pCmd ;}
//	
//	// ****************************************************************
//	//	コマンドの有効・無効判定
//	// ****************************************************************
//	if ( iRv >= 0 )
//	{
//		if ( !createCmd( CWndDcdGridEkiJikokuhyouList::ECreateCmd_Select , ppCmd ) )
//		{
//			iRv = -1 ;	//	セルの位置が正しくありません。
//		}
//	}
//	// ****************************************************************
//	if ( !bQueryEnable && iRv >= 0 )
//	{
//		// ****************************************************************
//		//	コマンドの実行
//		// ****************************************************************
//		// -------------------------------- 
//		//	クリップボードに転送
//		// --------------------------------
//		getCDiagramEditDoc()->CentDedEki_To_Cliboard( 
//			pCmd->getCaMuiSelect() ) ;
//
//		// -------------------------------- 
//		//	フォーカスセルを、選択要素中で最大の駅Indexの次位に移動
//		// --------------------------------
//		{
//			//	セル選択をクリアし、
//			//	フォーカスセルの移動によるセル選択を無効化します。
//			clearSelect() ;
//			CPropStack	aPropStack( this ) ;
//			aPropStack
//				.CBoxSelect_setIsEnable( false )
//				.CRandomSelect_setIsEnable( false )  ;
//		
//			//	選択要素中で最大の駅Index を求める
//			int iEkiIndexMax = -1 ;
//			{
//				CaMuiSelect<CentDedEki>* pCaMuiSelect = pCmd->getCaMuiSelect() ;
//				for ( int iIndex = pCaMuiSelect->getAdapteeMu()->size() - 1  ; 
//					iEkiIndexMax == -1 && iIndex >= 0 ; iIndex -- )
//				{
//					if ( pCaMuiSelect->getSelect( iIndex ) )
//					{
//						iEkiIndexMax = iIndex + pCmd->getIndexDst() ;
//					}
//				}
//			}
//			//iEkiIndexMax = 選択されている列車のうち、最大のIndex
//
//			//	移動先のフォーカスセル位置を決定
//			int iYColumnNmber = -1 ;
//			{
//				CdEkiYColSpecCont aCdEkiYColSpecCont = createYColSpecCont() ;
//				iYColumnNmber = aCdEkiYColSpecCont.ColumnNumberFromSpec( 
//					CdEkiYColSpec( CdEkiYColSpec::ColumnType_Eki , iEkiIndexMax ) ) + 1 ;
//			}
//			//	フォーカスを移動
//			{
//				CdDcdPosXy posxyFocusCellColumnNumber 
//					= getCFocus()->getFocusCellColumnNumber() ;
//				if ( iYColumnNmber >= 0 
//					&& posxyFocusCellColumnNumber != getCFocus()->ColumnNumberPosXy_NULL() )
//				{
//					posxyFocusCellColumnNumber.setY( iYColumnNmber ) ;
//					getCFocus()->setFocusCellColumnNumber( posxyFocusCellColumnNumber ) ;
//				}
//			}
//		}
//
//
//		// ****************************************************************
//		//	エラーメッセージ
//		// ****************************************************************
//
//		// ****************************************************************
//	}
//	return iRv ;
//
//
//}
//int CWndDcdGridEkiJikokuhyouList::OnEditPaste_Process( BOOL bQueryEnable )
//{
//	int iRv = 0 ;
//	Ou<CRfEditCmd_Eki> pCmd ;
//	Ou<CRfEditCmd_Eki>* ppCmd = NULL ;
//	if ( !bQueryEnable ){	ppCmd = &pCmd ;}
//	
//	// ****************************************************************
//	//	コマンドの有効・無効判定
//	// ****************************************************************
//	if ( iRv >= 0 )
//	{
//		if ( !createCmd( CWndDcdGridEkiJikokuhyouList::ECreateCmd_NewItem , ppCmd ) )
//		{
//			iRv = -1 ;	//	セルの位置が正しくありません。
//		}
//	}
//	if ( iRv >= 0 )
//	{
//		if ( !getCDiagramEditDoc()->CentDedEki_IsClipboardFormatAvailable() &&
//			!getCDiagramEditDoc()->UnicodeText_IsClipboardFormatAvailable())
//		{
//			iRv = -2 ;	//	クリップボードに駅のデータがありません
//		}
//	}
//	// ****************************************************************
//	if ( !bQueryEnable && iRv >= 0 )
//	{
//		// ****************************************************************
//		//	コマンドの実行
//		// ****************************************************************
//		// -------------------------------- 
//		//	クリップボードからデータを取得
//		// --------------------------------
//		CentDedEkiCont	aEkiCont ;
//		iRv = getCDiagramEditDoc()->CentDedEki_From_Cliboard( &aEkiCont ) ;
//		if (iRv >= 0 && aEkiCont.size() > 0)
//		{
//			// --------------------------------
//			//	コマンドオブジェクトの駅を編集
//			// --------------------------------
//			//	CWndDcdGridEkiJikokuhyouList::ECreateCmd_NewItem によって生成された
//			//	新規アイテムは削除します。
//			pCmd->getCaMuiSelect()->erase( 0 , INT_MAX ) ;
//
//			//	コマンドにクリップボードからのアイテムを追加します。
//			CaMui<CentDedEki> aCaMui( pCmd->getCaMuiSelect() ) ;
//			aCaMui.insert( &aEkiCont , 0 , INT_MAX , 0 ) ;
//
//			//CaMuiSelect<CentDedEki>* pCaMuiSelect = pCmd->getCaMuiSelect();
//			//for (int iIndex = pCaMuiSelect->getAdapteeMu()->size() - 1;
//			//	iEkiIndexMax == -1 && iIndex >= 0; iIndex--)
//			//{
//			//	if (pCaMuiSelect->getSelect(iIndex))
//			//	{
//			//		iEkiIndexMax = iIndex + pCmd->getIndexDst();
//			//	}
//			//}
//
//			//アイテム内に、分岐駅設定・環状線設定が有効な駅がある場合は、それを解除します。
//			//CaMuiSelect<CentDedEki>* pCaMuiSelect = pCmd->getCaMuiSelect();
//			for (int idx = 0; idx < pCmd->getCaMuiSelect()->/*getMuPtr()->*/size(); idx++)
//			{
//				pCmd->getCaMuiSelect()->getMuPtr()->get(idx)->setBrunchCoreEkiIndex(-1);
//				pCmd->getCaMuiSelect()->getMuPtr()->get(idx)->setLoopOriginEkiIndex(-1);
//			}
//			// --------------------------------
//			//	コマンドオブジェクトを実行
//			// --------------------------------
//			{
//				getCDiagramEditDoc()->executeEditCmd(pCmd);
//			}
//		}
//
//	}
//	return iRv ;
//
//}
//int CWndDcdGridEkiJikokuhyouList::OnEditClear_Process( BOOL bQueryEnable )
//{
//	int iRv = 0 ;
//	Ou<CRfEditCmd_Eki> pCmd ;
//	Ou<CRfEditCmd_Eki>* ppCmd = NULL ;
//	if ( !bQueryEnable ){	ppCmd = &pCmd ;}
//	
//	// ****************************************************************
//	//	コマンドの有効・無効判定
//	// ****************************************************************
//	if ( iRv >= 0 )
//	{
//		if (!createCmd(CWndDcdGridEkiJikokuhyouList::ECreateCmd_Focus, ppCmd))
//		//if ( !createCmd( CWndDcdGridEkiJikokuhyouList::ECreateCmd_Select , ppCmd ) )
//		{
//			iRv = -1 ;	//	セルの位置が正しくありません。
//		}
//	}
//	//被共有対象になっている場合は、コマンド無効です。
//	if (iRv >= 0)
//	{
//		if (getCSelect()->getSelectedCellCount() == 0)
//		{
//			const Mu< const CentDedEki* >* pCentDedEkiCont = getCDiagramEditDoc()->getCDedRosenFileData()
//				->getCentDedRosen()->getCentDedEkiCont()->getMuPtr();
//			CdEkiYColSpec aCdEkiYColSpec = getYColSpecOfFocus();
//			int iEkiIndexSelect = aCdEkiYColSpec.getEkiIndex();
//			for (int idx = 0; idx < pCentDedEkiCont->size() && iRv >= 0; idx++)
//			{
//				if (iEkiIndexSelect != idx)
//				{
//					if (pCentDedEkiCont->get(idx)->getBrunchCoreEkiIndex() == iEkiIndexSelect)
//					{
//						iRv = -2; //選択された駅は、他の駅から基幹駅に指定されています
//					}
//					else if (pCentDedEkiCont->get(idx)->getLoopOriginEkiIndex() == iEkiIndexSelect)
//					{
//						iRv = -3; //選択された駅は、他の駅から起点駅に指定されています
//					}
//				}
//			}
//		}
//		else if (getCSelect()->getSelectedCellCount() > 0)
//		{
//			const Mu< const CentDedEki* >* pCentDedEkiCont = getCDiagramEditDoc()->getCDedRosenFileData()
//				->getCentDedRosen()->getCentDedEkiCont()->getMuPtr();
//			CdEkiYColSpecCont aCdYColSpecCont = createYColSpecCont();
//
//			for (int iColumnNumber = 0; iColumnNumber < getCXDcdGrid()->getYColumnCount() && iRv >= 0; iColumnNumber++)
//			{
//				if (getCSelect()->getYColumnNumberSelected(iColumnNumber))
//				{
//					CdEkiYColSpec aCdEkiYColSpec = aCdYColSpecCont.ColumnNumberToSpec(iColumnNumber);
//					int iEkiIndexSelect = aCdEkiYColSpec.getEkiIndex();
//					for (int idx = 0; idx < pCentDedEkiCont->size() && iRv >= 0; idx++)
//					{
//						if (iEkiIndexSelect != idx)
//						{
//							if (pCentDedEkiCont->get(idx)->getBrunchCoreEkiIndex() == iEkiIndexSelect)
//							{
//								iRv = -2; //選択された駅は、他の駅から基幹駅に指定されています
//							}
//							else if (pCentDedEkiCont->get(idx)->getLoopOriginEkiIndex() == iEkiIndexSelect)
//							{
//								iRv = -3; //選択された駅は、他の駅から起点駅に指定されています
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//	// ****************************************************************
//	if ( !bQueryEnable && iRv >= 0 )
//	{
//		// ****************************************************************
//		//	コマンドの実行
//		// ****************************************************************
//		// --------------------------------
//		//	コマンドオブジェクトの列車を編集
//		// --------------------------------
//		{
//			pCmd->getCaMuiSelect()->erase( 0 , INT_MAX ) ;
//		}
//		// --------------------------------
//		//	コマンドオブジェクトを実行
//		// --------------------------------
//		{
//			getCDiagramEditDoc()->executeEditCmd( pCmd ) ;
//		}
//		// ****************************************************************
//		//	エラーメッセージ
//		// ****************************************************************
//
//		// ****************************************************************
//	}
//	return iRv ;	
//
//}

	/*	
		[編集]-[駅を挿入]
	@return
		成功したら0以上、エラーなら負の数です。
	*/
//int CWndDcdGridEkiJikokuhyouList:: OnEDITEkiInsert_Process( BOOL bQueryEnable )
//{
//	int iRv = 0 ;
//
//	// ****************************************************************
//	//	コマンドの有効・無効判定
//	// ****************************************************************
//	if ( execEkiPropDlg( true , TRUE ) < 0 )
//	{
//		iRv = -1 ;	//	フォーカスの位置が不正です。
//	}
//
//	// ****************************************************************
//	if ( !bQueryEnable && iRv >= 0 )
//	{
//		// ****************************************************************
//		//	コマンドの実行
//		// ****************************************************************
//		execEkiPropDlg( true , FALSE ) ;
//
//		// ****************************************************************
//		//	エラーメッセージ
//		// ****************************************************************
//		if ( iRv < 0 )
//		{
//			CString strErrorMessage ;
//			switch( iRv )
//			{
//			case -1 :	//	現在は実行できません。
//				break ;
//			default:
//				strErrorMessage.Format( _T( "Error=%d" ) , iRv ) ;
//				break ;
//			}
//			if ( strErrorMessage.GetLength() > 0 )
//			{
//				MessageBox( strErrorMessage , NULL , MB_ICONSTOP | MB_OK ) ; 
//			}
//		}
//		// ****************************************************************
//	}
//	return iRv ;
//}
//
//int CWndDcdGridEkiJikokuhyouList::OnEditEkiInvert_Process( BOOL bQueryEnable )
//{
//	int iRv = 0 ;
//
//	// ****************************************************************
//	//	コマンドの実行可否の判定
//	// ****************************************************************
//	//	コマンドの実行の可否を判定します。
//	//	コマンドが実行不可能なら、 iRv に負の数を設定してください。
//
//	const CentDedRosen*	pCentDedRosen = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen() ;
//	const Mu<const CentDedEki*>* pCentDedEkiContGet = pCentDedRosen->getCentDedEkiCont()->getMuPtr() ;
//	
//	
//	// ****************************************************************
//	if ( !bQueryEnable && iRv >= 0 )
//	{
//		// ****************************************************************
//		//	コマンドの実行
//		// ****************************************************************
//		//	コマンドを実行します。
//		//	結果がエラーなら、iRv に負の数を設定します。
//
//		//CentDedRosen	aRosenNew ;
//		CDedRosenFileData aCDedRosenFileData = *getCDiagramEditDoc()->getCDedRosenFileData();
//		if (iRv >= 0)
//		{
//			//	路線を取得後、上下を反転します。
//			//aRosenNew = *pCentDedRosen ;
//			//aRosenNew.invert() ;
//
//			aCDedRosenFileData.getCentDedRosen()->invert();;
//
//			CdDedDispProp aCdDedDispProp = aCDedRosenFileData.getCdDedDispProp();
//
//			bool bOrigin = aCdDedDispProp.getDisplayOuterTerminalO();
//			bool bTerminal = aCdDedDispProp.getDisplayOuterTerminalT();
//			aCdDedDispProp.setDisplayOuterTerminalO(bTerminal);
//			aCdDedDispProp.setDisplayOuterTerminalT(bOrigin);
//
//			aCDedRosenFileData.setCdDedDispProp(aCdDedDispProp);
//			//	更新コマンドを生成
//		}
//		// --------------------------------
//		//	コマンドを生成・実行
//		// --------------------------------
//		if (iRv >= 0)
//		{
//
//			OuNew<CRfEditCmd> pCmd(
//				new CRfEditCmd_RosenFileData(aCDedRosenFileData)
//			);
//			getCDiagramEditDoc()->executeEditCmd(pCmd);
//		}
//		//if ( iRv >= 0 )
//		//{
//		//	OuNew<CRfEditCmd> pCmd(
//		//		new CRfEditCmd_Rosen( aRosenNew )  
//		//	);
//		//	getCDiagramEditDoc()->executeEditCmd( pCmd ) ;
//		//}
//		// ****************************************************************
//		//	エラーメッセージ
//		// ****************************************************************
//		if ( iRv < 0 )
//		{
//			CString strErrorMessage ;
//			switch( iRv )
//			{
//			case -1 :	//	現在は実行できません。
//				break ;
//			default:
//				strErrorMessage.Format( _T( "Error=%d" ) , iRv ) ;
//				break ;
//			}
//			if ( strErrorMessage.GetLength() > 0 )
//			{
//				MessageBox( strErrorMessage , NULL , MB_ICONSTOP | MB_OK ) ; 
//			}
//		}
//		// ****************************************************************
//	}
//	return iRv ;
//}
//
//	/*	
//		[編集]-[駅のプロパティ]
//	*/
//int CWndDcdGridEkiJikokuhyouList:: OnEDITEkiProp_Process( BOOL bQueryEnable )
//{
//	int iRv = 0 ;
//	// ****************************************************************
//	//	コマンドの有効・無効判定
//	// ****************************************************************
//
//	//	フォーカスセルが新規アイテム位置にあるときは、
//	//	「新規アイテムのプロパティ入力を行い、それを末尾に挿入する」という
//	//	動作になります。
//	bool bInsert = false ;
//	CdEkiYColSpec aYColSpec = getYColSpecOfFocus() ;
//	if ( aYColSpec.getColumnType() == CdEkiYColSpec::ColumnType_NewEki )
//	{
//		bInsert = true ;
//	}
//
//	if ( execEkiPropDlg( bInsert , TRUE ) < 0 )
//	{
//		iRv = -1 ;	//	-1 ;	//	フォーカスセルの位置が不正です。
//	}
//	// ****************************************************************
//	if ( !bQueryEnable && iRv >= 0 )
//	{
//		// ****************************************************************
//		//	コマンドの実行
//		// ****************************************************************
//		//	コマンドを実行します。
//		//	結果がエラーなら、iRv に負の数を設定します。
//
//		execEkiPropDlg( bInsert , FALSE ) ;
//
//		// ****************************************************************
//		//	エラーメッセージ
//		// ****************************************************************
//		// ****************************************************************
//	}
//	return iRv ;
//}
//
//
//int CWndDcdGridEkiJikokuhyouList::OnEkiSettingNext_Process(BOOL bQueryEnable, int iType)
//{
//	int iRv = 0;
//	Ou<CRfEditCmd_Eki> pCmd;
//	Ou<CRfEditCmd_Eki>* ppCmd = NULL;
//	if (!bQueryEnable) { ppCmd = &pCmd; }
//
//	// ****************************************************************
//	//	コマンドの有効・無効判定
//	// ****************************************************************
//	if (iRv >= 0)
//	{
//		if (!createCmd(CWndDcdGridEkiJikokuhyouList::ECreateCmd_Select, ppCmd))
//		{
//			iRv = -1;	//	セルの位置が正しくありません。
//		}
//	}
//	if (iRv >= 0)
//	{
//		if (!getDisplaySettingMode())
//		{
//			iRv = -2;	//	表示設定モードではありません。
//		}
//
//	}
//	if (iRv >= 0)
//	{
//		CdEkiXColSpec	aXColSpec = getXColSpecOfFocus();
//		if (aXColSpec.getColumnType() < CdEkiXColSpec::ColumnType_OperationOrigin ||
//			aXColSpec.getColumnType() > CdEkiXColSpec::ColumnType_DiagramColorNextEki)
//		{
//			iRv = -3;	//編集可能なのは、前後作業欄設定～次駅までの背景色の間です。
//		}
//
//	}
//	// ****************************************************************
//	if (!bQueryEnable && iRv >= 0)
//	{
//		// ****************************************************************
//		//	コマンドの実行
//		// ****************************************************************
//
//		CdEkiXColSpec	aXColSpec = getXColSpecOfFocus();
//
//		Mu<CentDedEki*>* muCentDedEki = pCmd->getCaMuiSelect()->getMuPtr();
//		for (int idx = 0; idx < muCentDedEki->size(); idx++)
//		{
//			CentDedEki* pCentDedEki = muCentDedEki->get(idx);
//			if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_OperationOrigin)
//			{
//				//前後作業欄が有効なのは、駅時刻形式が発時刻以外の場合
//				if (pCentDedEki->getEkijikokukeisiki() != CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsu)
//				{
//					if (pCentDedEki->getJikokuhyouOperationOrigin() >= 3)
//					{
//						pCentDedEki->setJikokuhyouOperationOrigin(0);
//					}
//					else
//					{
//						pCentDedEki->setJikokuhyouOperationOrigin(
//							pCentDedEki->getJikokuhyouOperationOrigin() + 1);
//					}
//				}
//			}
//			else if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_OperationTerminal)
//			{
//				//前後作業欄が有効なのは、駅時刻形式が発時刻以外の場合
//				if (pCentDedEki->getEkijikokukeisiki() != CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsu)
//				{
//					if (pCentDedEki->getJikokuhyouOperationTerminal() >= 3)
//					{
//						pCentDedEki->setJikokuhyouOperationTerminal(0);
//					}
//					else
//					{
//						pCentDedEki->setJikokuhyouOperationTerminal(
//							pCentDedEki->getJikokuhyouOperationTerminal() + 1);
//					}
//				}
//			}
//			else if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_TrackOmit)
//			{
//				//番線省略が有効なのは、駅時刻形式が発時刻・下り発着・上り発着の場合
//				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsu ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
//				{
//					pCentDedEki->setJikokuhyouTrackOmit(!pCentDedEki->getJikokuhyouTrackOmit());
//				}
//			}
//			else if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_ChakuJikokuDisplayKudari)
//			{
//				//カスタマイズ時刻表下り着時刻が有効なのは、駅時刻形式が発着・下り着時刻・下り発着の場合
//				//ただし、発時刻表示が無効の場合は、着時刻表示を有効→無効に変更しない
//				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku)
//				{
//					if (!pCentDedEki->getJikokuhyouChakuJikokuDisplayKudari())
//					{
//						pCentDedEki->setJikokuhyouChakuJikokuDisplayKudari(true);
//					}
//					else if (pCentDedEki->getJikokuhyouHatsuJikokuDisplayKudari())
//					{
//						pCentDedEki->setJikokuhyouChakuJikokuDisplayKudari(false);
//					}
//				}
//			}
//			else if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_TrackDisplayKudari)
//			{
//				//カスタマイズ時刻表下り番線が有効なのは、駅時刻形式が発着・下り着時刻・上り着時刻・下り発着の場合
//				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku)
//				{
//					pCentDedEki->setJikokuhyouTrackDisplayKudari(
//						!pCentDedEki->getJikokuhyouTrackDisplayKudari());
//				}
//			}
//			else if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_HatsuJikokuDisplayKudari)
//			{
//				//カスタマイズ時刻表下り発時刻が有効なのは、駅時刻形式が下り着時刻以外の場合
//				//ただし、着時刻表示が無効の場合は、発時刻表示を有効→無効に変更しない
//				if (pCentDedEki->getEkijikokukeisiki() != CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku)
//				{
//					if (!pCentDedEki->getJikokuhyouHatsuJikokuDisplayKudari())
//					{
//						pCentDedEki->setJikokuhyouHatsuJikokuDisplayKudari(true);
//					}
//					else if (pCentDedEki->getJikokuhyouChakuJikokuDisplayKudari())
//					{
//						pCentDedEki->setJikokuhyouHatsuJikokuDisplayKudari(false);
//					}
//				}
//			}
//			else if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_RessyabangouDisplayKudari)
//			{
//				//カスタマイズ時刻表下り列車番号が有効なのは、駅時刻形式が発着・上り着時刻・下り発着の場合
//				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku)
//				{
//					if (pCentDedEki->getJikokuhyouRessyabangouDisplayKudari() >= 2)
//					{
//						pCentDedEki->setJikokuhyouRessyabangouDisplayKudari(0);
//					}
//					else
//					{
//						pCentDedEki->setJikokuhyouRessyabangouDisplayKudari(
//							pCentDedEki->getJikokuhyouRessyabangouDisplayKudari() + 1);
//					}
//				}
//			}
//			else if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_OperationNumberDisplayKudari)
//			{
//				//カスタマイズ時刻表下り運用番号が有効なのは、駅時刻形式が発着・上り着時刻・下り発着の場合
//				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku)
//				{
//					if (pCentDedEki->getJikokuhyouOperationNumberDisplayKudari() >= 2)
//					{
//						pCentDedEki->setJikokuhyouOperationNumberDisplayKudari(0);
//					}
//					else
//					{
//						pCentDedEki->setJikokuhyouOperationNumberDisplayKudari(
//							pCentDedEki->getJikokuhyouOperationNumberDisplayKudari() + 1);
//					}
//				}
//			}
//			else if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_RessyaSyubetsuDisplayKudari)
//			{
//				//カスタマイズ時刻表下り列車種別が有効なのは、駅時刻形式が発着・上り着時刻・下り発着の場合
//				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku)
//				{
//					if (pCentDedEki->getJikokuhyouRessyaSyubetsuDisplayKudari() >= 2)
//					{
//						pCentDedEki->setJikokuhyouRessyaSyubetsuDisplayKudari(0);
//					}
//					else
//					{
//						pCentDedEki->setJikokuhyouRessyaSyubetsuDisplayKudari(
//							pCentDedEki->getJikokuhyouRessyaSyubetsuDisplayKudari() + 1);
//					}
//				}
//			}
//			else if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_RessyameiDisplayKudari)
//			{
//				//カスタマイズ時刻表下り列車名が有効なのは、駅時刻形式が発着・上り着時刻・下り発着の場合
//				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku)
//				{
//					if (pCentDedEki->getJikokuhyouRessyameiDisplayKudari() >= 2)
//					{
//						pCentDedEki->setJikokuhyouRessyameiDisplayKudari(0);
//					}
//					else
//					{
//						pCentDedEki->setJikokuhyouRessyameiDisplayKudari(
//							pCentDedEki->getJikokuhyouRessyameiDisplayKudari() + 1);
//					}
//				}
//			}
//			else if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_ChakuJikokuDisplayNobori)
//			{
//				//カスタマイズ時刻表上り着時刻が有効なのは、駅時刻形式が発着・上り着時刻・上り発着の場合
//				//ただし、発時刻表示が無効の場合は、着時刻表示を有効→無効に変更しない
//				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
//				{
//					if (!pCentDedEki->getJikokuhyouChakuJikokuDisplayNobori())
//					{
//						pCentDedEki->setJikokuhyouChakuJikokuDisplayNobori(true);
//					}
//					else if (pCentDedEki->getJikokuhyouHatsuJikokuDisplayNobori())
//					{
//						pCentDedEki->setJikokuhyouChakuJikokuDisplayNobori(false);
//					}
//				}
//			}
//			else if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_TrackDisplayNobori)
//			{
//				//カスタマイズ時刻表上り番線が有効なのは、駅時刻形式が発着・下り着時刻・上り着時刻・上り発着の場合
//				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
//				{
//					pCentDedEki->setJikokuhyouTrackDisplayNobori(
//						!pCentDedEki->getJikokuhyouTrackDisplayNobori());
//				}
//			}
//			else if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_HatsuJikokuDisplayNobori)
//			{
//				//カスタマイズ時刻表上り発時刻が有効なのは、駅時刻形式が上り着時刻以外の場合
//				//ただし、着時刻表示が無効の場合は、発時刻表示を有効→無効に変更しない
//				if (pCentDedEki->getEkijikokukeisiki() != CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku)
//				{
//					if (!pCentDedEki->getJikokuhyouHatsuJikokuDisplayNobori())
//					{
//						pCentDedEki->setJikokuhyouHatsuJikokuDisplayNobori(true);
//					}
//					else if (pCentDedEki->getJikokuhyouChakuJikokuDisplayNobori())
//					{
//						pCentDedEki->setJikokuhyouHatsuJikokuDisplayNobori(false);
//					}
//				}
//			}
//			else if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_RessyabangouDisplayNobori)
//			{
//				//カスタマイズ時刻表上り列車番号が有効なのは、駅時刻形式が発着・下り着時刻・上り発着の場合
//				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
//				{
//					if (pCentDedEki->getJikokuhyouRessyabangouDisplayNobori() >= 2)
//					{
//						pCentDedEki->setJikokuhyouRessyabangouDisplayNobori(0);
//					}
//					else
//					{
//						pCentDedEki->setJikokuhyouRessyabangouDisplayNobori(
//							pCentDedEki->getJikokuhyouRessyabangouDisplayNobori() + 1);
//					}
//				}
//			}
//			else if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_OperationNumberDisplayNobori)
//			{
//				//カスタマイズ時刻表上り運用番号が有効なのは、駅時刻形式が発着・下り着時刻・上り発着の場合
//				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
//				{
//					if (pCentDedEki->getJikokuhyouOperationNumberDisplayNobori() >= 2)
//					{
//						pCentDedEki->setJikokuhyouOperationNumberDisplayNobori(0);
//					}
//					else
//					{
//						pCentDedEki->setJikokuhyouOperationNumberDisplayNobori(
//							pCentDedEki->getJikokuhyouOperationNumberDisplayNobori() + 1);
//					}
//				}
//			}
//			else if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_RessyaSyubetsuDisplayNobori)
//			{
//				//カスタマイズ時刻表上り列車種別が有効なのは、駅時刻形式が発着・下り着時刻・上り発着の場合
//				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
//				{
//					if (pCentDedEki->getJikokuhyouRessyaSyubetsuDisplayNobori() >= 2)
//					{
//						pCentDedEki->setJikokuhyouRessyaSyubetsuDisplayNobori(0);
//					}
//					else
//					{
//						pCentDedEki->setJikokuhyouRessyaSyubetsuDisplayNobori(
//							pCentDedEki->getJikokuhyouRessyaSyubetsuDisplayNobori() + 1);
//					}
//				}
//			}
//			else if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_RessyameiDisplayNobori)
//			{
//				//カスタマイズ時刻表上り列車名が有効なのは、駅時刻形式が発着・下り着時刻・上り発着の場合
//				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
//				{
//					if (pCentDedEki->getJikokuhyouRessyameiDisplayNobori() >= 2)
//					{
//						pCentDedEki->setJikokuhyouRessyameiDisplayNobori(0);
//					}
//					else
//					{
//						pCentDedEki->setJikokuhyouRessyameiDisplayNobori(
//							pCentDedEki->getJikokuhyouRessyameiDisplayNobori() + 1);
//					}
//				}
//			}
//			else if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_DiagramTrackDisplay)
//			{
//				//在線表表示が有効なのは、駅時刻形式が発着・下り着時刻・上り着時刻かつ主要駅の場合
//				if ((pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku) &&
//					pCentDedEki->getEkikibo() == CentDedEki::EEkikibo::Ekikibo_Syuyou)
//				{
//					pCentDedEki->setDiagramTrackDisplay(!pCentDedEki->getDiagramTrackDisplay());
//				}
//			}
//			else if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_DiagramRessyajouhouHyoujiKudari)
//			{
//				//ダイヤグラム列車情報表示(下り)
//				if (pCentDedEki->getDiagramRessyajouhouHyoujiKudari() == CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Origin)
//				{
//					pCentDedEki->setDiagramRessyajouhouHyoujiKudari(CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Anytime);
//				}
//				else if (pCentDedEki->getDiagramRessyajouhouHyoujiKudari() == CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Anytime)
//				{
//					pCentDedEki->setDiagramRessyajouhouHyoujiKudari(CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Not);
//				}
//				else if (pCentDedEki->getDiagramRessyajouhouHyoujiKudari() == CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Not)
//				{
//					pCentDedEki->setDiagramRessyajouhouHyoujiKudari(CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Origin);
//				}
//			}
//			else if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_DiagramRessyajouhouHyoujiNobori)
//			{
//				//ダイヤグラム列車情報表示(上り)
//				if (pCentDedEki->getDiagramRessyajouhouHyoujiNobori() == CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Origin)
//				{
//					pCentDedEki->setDiagramRessyajouhouHyoujiNobori(CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Anytime);
//				}
//				else if (pCentDedEki->getDiagramRessyajouhouHyoujiNobori() == CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Anytime)
//				{
//					pCentDedEki->setDiagramRessyajouhouHyoujiNobori(CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Not);
//				}
//				else if (pCentDedEki->getDiagramRessyajouhouHyoujiNobori() == CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Not)
//				{
//					pCentDedEki->setDiagramRessyajouhouHyoujiNobori(CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Origin);
//				}
//			}
//			else if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_NextEkiDistance)
//			{
//				//この駅から次の駅までの距離
//				//iTypeによって加算時間を変えて、ChangeNextEkiDistanceを実行する。
//				int iShiftSecond = 0;
//				if (iType == 0)
//				{
//					iShiftSecond = 60;
//				}
//				else if (iType == 1)
//				{
//					CdDedDispProp aCdDedDispProp = getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
//					iShiftSecond = aCdDedDispProp.getAnySecondIncDec1();
//				}
//				else if (iType == 2)
//				{
//					CdDedDispProp aCdDedDispProp = getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
//					iShiftSecond = aCdDedDispProp.getAnySecondIncDec2();
//				}
//				ChangeNextEkiDistance(pCentDedEki,iShiftSecond);
//			}
//			else if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_DiagramColorNextEki)
//			{
//				//この駅から次の駅までの背景色設定
//				if (pCentDedEki->getDiagramColorNextEki() >= 4)
//				{
//					pCentDedEki->setDiagramColorNextEki(0);
//				}
//				else
//				{
//					pCentDedEki->setDiagramColorNextEki(
//						pCentDedEki->getDiagramColorNextEki() + 1);
//				}
//			}
//		}
//
//		if (iRv >= 0)
//		{
//			// --------------------------------
//			//	編集コマンドを実行
//			// --------------------------------
//			getCDiagramEditDoc()->executeEditCmd(pCmd);
//		}
//
//		// ****************************************************************
//		//	エラーメッセージ
//		// ****************************************************************
//
//		// ****************************************************************
//	}
//	return iRv;
//}
//int CWndDcdGridEkiJikokuhyouList::OnEkiSettingPrev_Process(BOOL bQueryEnable, int iType)
//{
//	int iRv = 0;
//	Ou<CRfEditCmd_Eki> pCmd;
//	Ou<CRfEditCmd_Eki>* ppCmd = NULL;
//	if (!bQueryEnable) { ppCmd = &pCmd; }
//
//	// ****************************************************************
//	//	コマンドの有効・無効判定
//	// ****************************************************************
//	if (iRv >= 0)
//	{
//		if (!createCmd(CWndDcdGridEkiJikokuhyouList::ECreateCmd_Select, ppCmd))
//		{
//			iRv = -1;	//	セルの位置が正しくありません。
//		}
//	}
//	if (iRv >= 0)
//	{
//		if (!getDisplaySettingMode())
//		{
//			iRv = -2;	//	表示設定モードではありません。
//		}
//
//	}
//	if (iRv >= 0)
//	{
//		CdEkiXColSpec	aXColSpec = getXColSpecOfFocus();
//		if (aXColSpec.getColumnType() < CdEkiXColSpec::ColumnType_OperationOrigin ||
//			aXColSpec.getColumnType() > CdEkiXColSpec::ColumnType_DiagramColorNextEki)
//		{
//			iRv = -3;	//編集可能なのは、前後作業欄設定～次駅までの背景色の間です。
//		}
//
//	}
//	// ****************************************************************
//	if (!bQueryEnable && iRv >= 0)
//	{
//		// ****************************************************************
//		//	コマンドの実行
//		// ****************************************************************
//
//		CdEkiXColSpec	aXColSpec = getXColSpecOfFocus();
//
//		Mu<CentDedEki*>* muCentDedEki = pCmd->getCaMuiSelect()->getMuPtr();
//		for (int idx = 0; idx < muCentDedEki->size(); idx++)
//		{
//			CentDedEki* pCentDedEki = muCentDedEki->get(idx);
//			if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_OperationOrigin)
//			{
//				//前後作業欄が有効なのは、駅時刻形式が発時刻以外の場合
//				if (pCentDedEki->getEkijikokukeisiki() != CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsu)
//				{
//					if (pCentDedEki->getJikokuhyouOperationOrigin() <= 0)
//					{
//						pCentDedEki->setJikokuhyouOperationOrigin(3);
//					}
//					else
//					{
//						pCentDedEki->setJikokuhyouOperationOrigin(
//							pCentDedEki->getJikokuhyouOperationOrigin() - 1);
//					}
//				}
//			}
//			else if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_OperationTerminal)
//			{
//				//前後作業欄が有効なのは、駅時刻形式が発時刻以外の場合
//				if (pCentDedEki->getEkijikokukeisiki() != CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsu)
//				{
//					if (pCentDedEki->getJikokuhyouOperationTerminal() <= 0)
//					{
//						pCentDedEki->setJikokuhyouOperationTerminal(3);
//					}
//					else
//					{
//						pCentDedEki->setJikokuhyouOperationTerminal(
//							pCentDedEki->getJikokuhyouOperationTerminal() - 1);
//					}
//				}
//			}
//			else if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_TrackOmit)
//			{
//				//番線省略が有効なのは、駅時刻形式が発時刻・下り発着・上り発着の場合
//				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsu ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
//				{
//					pCentDedEki->setJikokuhyouTrackOmit(!pCentDedEki->getJikokuhyouTrackOmit());
//				}
//			}
//			else if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_ChakuJikokuDisplayKudari)
//			{
//				//カスタマイズ時刻表下り着時刻が有効なのは、駅時刻形式が発着・下り着時刻・下り発着の場合
//				//ただし、発時刻表示が無効の場合は、着時刻表示を有効→無効に変更しない
//				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku)
//				{
//					if (!pCentDedEki->getJikokuhyouChakuJikokuDisplayKudari())
//					{
//						pCentDedEki->setJikokuhyouChakuJikokuDisplayKudari(true);
//					}
//					else if (pCentDedEki->getJikokuhyouHatsuJikokuDisplayKudari())
//					{
//						pCentDedEki->setJikokuhyouChakuJikokuDisplayKudari(false);
//					}
//				}
//			}
//			else if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_TrackDisplayKudari)
//			{
//				//カスタマイズ時刻表下り番線が有効なのは、駅時刻形式が発着・下り着時刻・上り着時刻・下り発着の場合
//				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku)
//				{
//					pCentDedEki->setJikokuhyouTrackDisplayKudari(
//						!pCentDedEki->getJikokuhyouTrackDisplayKudari());
//				}
//			}
//			else if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_HatsuJikokuDisplayKudari)
//			{
//				//カスタマイズ時刻表下り発時刻が有効なのは、駅時刻形式が下り着時刻以外の場合
//				//ただし、着時刻表示が無効の場合は、発時刻表示を有効→無効に変更しない
//				if (pCentDedEki->getEkijikokukeisiki() != CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku)
//				{
//					if (!pCentDedEki->getJikokuhyouHatsuJikokuDisplayKudari())
//					{
//						pCentDedEki->setJikokuhyouHatsuJikokuDisplayKudari(true);
//					}
//					else if (pCentDedEki->getJikokuhyouChakuJikokuDisplayKudari())
//					{
//						pCentDedEki->setJikokuhyouHatsuJikokuDisplayKudari(false);
//					}
//				}
//			}
//			else if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_RessyabangouDisplayKudari)
//			{
//				//カスタマイズ時刻表下り列車番号が有効なのは、駅時刻形式が発着・上り着時刻・下り発着の場合
//				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku)
//				{
//					if (pCentDedEki->getJikokuhyouRessyabangouDisplayKudari() <= 0)
//					{
//						pCentDedEki->setJikokuhyouRessyabangouDisplayKudari(2);
//					}
//					else
//					{
//						pCentDedEki->setJikokuhyouRessyabangouDisplayKudari(
//							pCentDedEki->getJikokuhyouRessyabangouDisplayKudari() - 1);
//					}
//				}
//			}
//			else if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_OperationNumberDisplayKudari)
//			{
//				//カスタマイズ時刻表下り運用番号が有効なのは、駅時刻形式が発着・上り着時刻・下り発着の場合
//				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku)
//				{
//					if (pCentDedEki->getJikokuhyouOperationNumberDisplayKudari() <= 0)
//					{
//						pCentDedEki->setJikokuhyouOperationNumberDisplayKudari(2);
//					}
//					else
//					{
//						pCentDedEki->setJikokuhyouOperationNumberDisplayKudari(
//							pCentDedEki->getJikokuhyouOperationNumberDisplayKudari() -1);
//					}
//				}
//			}
//			else if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_RessyaSyubetsuDisplayKudari)
//			{
//				//カスタマイズ時刻表下り列車種別が有効なのは、駅時刻形式が発着・上り着時刻・下り発着の場合
//				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku)
//				{
//					if (pCentDedEki->getJikokuhyouRessyaSyubetsuDisplayKudari() <= 0)
//					{
//						pCentDedEki->setJikokuhyouRessyaSyubetsuDisplayKudari(2);
//					}
//					else
//					{
//						pCentDedEki->setJikokuhyouRessyaSyubetsuDisplayKudari(
//							pCentDedEki->getJikokuhyouRessyaSyubetsuDisplayKudari() - 1);
//					}
//				}
//			}
//			else if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_RessyameiDisplayKudari)
//			{
//				//カスタマイズ時刻表下り列車名が有効なのは、駅時刻形式が発着・上り着時刻・下り発着の場合
//				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku)
//				{
//					if (pCentDedEki->getJikokuhyouRessyameiDisplayKudari() <= 0)
//					{
//						pCentDedEki->setJikokuhyouRessyameiDisplayKudari(2);
//					}
//					else
//					{
//						pCentDedEki->setJikokuhyouRessyameiDisplayKudari(
//							pCentDedEki->getJikokuhyouRessyameiDisplayKudari() - 1);
//					}
//				}
//			}
//			else if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_ChakuJikokuDisplayNobori)
//			{
//				//カスタマイズ時刻表上り着時刻が有効なのは、駅時刻形式が発着・上り着時刻・上り発着の場合
//				//ただし、発時刻表示が無効の場合は、着時刻表示を有効→無効に変更しない
//				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
//				{
//					if (!pCentDedEki->getJikokuhyouChakuJikokuDisplayNobori())
//					{
//						pCentDedEki->setJikokuhyouChakuJikokuDisplayNobori(true);
//					}
//					else if (pCentDedEki->getJikokuhyouHatsuJikokuDisplayNobori())
//					{
//						pCentDedEki->setJikokuhyouChakuJikokuDisplayNobori(false);
//					}
//				}
//			}
//			else if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_TrackDisplayNobori)
//			{
//				//カスタマイズ時刻表上り番線が有効なのは、駅時刻形式が発着・下り着時刻・上り着時刻・上り発着の場合
//				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
//				{
//					pCentDedEki->setJikokuhyouTrackDisplayNobori(
//						!pCentDedEki->getJikokuhyouTrackDisplayNobori());
//				}
//			}
//			else if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_HatsuJikokuDisplayNobori)
//			{
//				//カスタマイズ時刻表上り発時刻が有効なのは、駅時刻形式が上り着時刻以外の場合
//				//ただし、着時刻表示が無効の場合は、発時刻表示を有効→無効に変更しない
//				if (pCentDedEki->getEkijikokukeisiki() != CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku)
//				{
//					if (!pCentDedEki->getJikokuhyouHatsuJikokuDisplayNobori())
//					{
//						pCentDedEki->setJikokuhyouHatsuJikokuDisplayNobori(true);
//					}
//					else if (pCentDedEki->getJikokuhyouChakuJikokuDisplayNobori())
//					{
//						pCentDedEki->setJikokuhyouHatsuJikokuDisplayNobori(false);
//					}
//				}
//			}
//			else if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_RessyabangouDisplayNobori)
//			{
//				//カスタマイズ時刻表上り列車番号が有効なのは、駅時刻形式が発着・下り着時刻・上り発着の場合
//				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
//				{
//					if (pCentDedEki->getJikokuhyouRessyabangouDisplayNobori() <= 0)
//					{
//						pCentDedEki->setJikokuhyouRessyabangouDisplayNobori(2);
//					}
//					else
//					{
//						pCentDedEki->setJikokuhyouRessyabangouDisplayNobori(
//							pCentDedEki->getJikokuhyouRessyabangouDisplayNobori() - 1);
//					}
//				}
//			}
//			else if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_OperationNumberDisplayNobori)
//			{
//				//カスタマイズ時刻表上り運用番号が有効なのは、駅時刻形式が発着・下り着時刻・上り発着の場合
//				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
//				{
//					if (pCentDedEki->getJikokuhyouOperationNumberDisplayNobori() <= 0)
//					{
//						pCentDedEki->setJikokuhyouOperationNumberDisplayNobori(2);
//					}
//					else
//					{
//						pCentDedEki->setJikokuhyouOperationNumberDisplayNobori(
//							pCentDedEki->getJikokuhyouOperationNumberDisplayNobori() - 1);
//					}
//				}
//			}
//			else if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_RessyaSyubetsuDisplayNobori)
//			{
//				//カスタマイズ時刻表上り列車種別が有効なのは、駅時刻形式が発着・下り着時刻・上り発着の場合
//				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
//				{
//					if (pCentDedEki->getJikokuhyouRessyaSyubetsuDisplayNobori() <= 0)
//					{
//						pCentDedEki->setJikokuhyouRessyaSyubetsuDisplayNobori(2);
//					}
//					else
//					{
//						pCentDedEki->setJikokuhyouRessyaSyubetsuDisplayNobori(
//							pCentDedEki->getJikokuhyouRessyaSyubetsuDisplayNobori() - 1);
//					}
//				}
//			}
//			else if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_RessyameiDisplayNobori)
//			{
//				//カスタマイズ時刻表上り列車名が有効なのは、駅時刻形式が発着・下り着時刻・上り発着の場合
//				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
//				{
//					if (pCentDedEki->getJikokuhyouRessyameiDisplayNobori() <= 0)
//					{
//						pCentDedEki->setJikokuhyouRessyameiDisplayNobori(2);
//					}
//					else
//					{
//						pCentDedEki->setJikokuhyouRessyameiDisplayNobori(
//							pCentDedEki->getJikokuhyouRessyameiDisplayNobori() - 1);
//					}
//				}
//			}
//			else if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_DiagramTrackDisplay)
//			{
//				//在線表表示が有効なのは、駅時刻形式が発着・下り着時刻・上り着時刻かつ主要駅の場合
//				if ((pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
//					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku) &&
//					pCentDedEki->getEkikibo() == CentDedEki::EEkikibo::Ekikibo_Syuyou)
//				{
//					pCentDedEki->setDiagramTrackDisplay(!pCentDedEki->getDiagramTrackDisplay());
//				}
//			}
//			else if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_DiagramRessyajouhouHyoujiKudari)
//			{
//				//ダイヤグラム列車情報表示(下り)
//				if (pCentDedEki->getDiagramRessyajouhouHyoujiKudari() == CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Origin)
//				{
//					pCentDedEki->setDiagramRessyajouhouHyoujiKudari(CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Not);
//				}
//				else if (pCentDedEki->getDiagramRessyajouhouHyoujiKudari() == CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Anytime)
//				{
//					pCentDedEki->setDiagramRessyajouhouHyoujiKudari(CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Origin);
//				}
//				else if (pCentDedEki->getDiagramRessyajouhouHyoujiKudari() == CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Not)
//				{
//					pCentDedEki->setDiagramRessyajouhouHyoujiKudari(CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Anytime);
//				}
//			}
//			else if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_DiagramRessyajouhouHyoujiNobori)
//			{
//				//ダイヤグラム列車情報表示(上り)
//				if (pCentDedEki->getDiagramRessyajouhouHyoujiNobori() == CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Origin)
//				{
//					pCentDedEki->setDiagramRessyajouhouHyoujiNobori(CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Not);
//				}
//				else if (pCentDedEki->getDiagramRessyajouhouHyoujiNobori() == CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Anytime)
//				{
//					pCentDedEki->setDiagramRessyajouhouHyoujiNobori(CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Origin);
//				}
//				else if (pCentDedEki->getDiagramRessyajouhouHyoujiNobori() == CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Not)
//				{
//					pCentDedEki->setDiagramRessyajouhouHyoujiNobori(CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Anytime);
//				}
//			}
//			else if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_NextEkiDistance)
//			{
//				//この駅から次の駅までの距離
//				//iTypeによって加算時間を変えて、ChangeNextEkiDistanceを実行する。
//				int iShiftSecond = 0;
//				if (iType == 0)
//				{
//					iShiftSecond = -60;
//				}
//				else if (iType == 1)
//				{
//					CdDedDispProp aCdDedDispProp = getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
//					iShiftSecond = -aCdDedDispProp.getAnySecondIncDec1();
//				}
//				else if (iType == 2)
//				{
//					CdDedDispProp aCdDedDispProp = getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
//					iShiftSecond = -aCdDedDispProp.getAnySecondIncDec2();
//				}
//				ChangeNextEkiDistance(pCentDedEki, iShiftSecond);
//			}
//			else if (aXColSpec.getColumnType() == CdEkiXColSpec::ColumnType_DiagramColorNextEki)
//			{
//				//この駅から次の駅までの背景色設定
//				if (pCentDedEki->getDiagramColorNextEki() <= 0)
//				{
//					pCentDedEki->setDiagramColorNextEki(4);
//				}
//				else
//				{
//					pCentDedEki->setDiagramColorNextEki(
//						pCentDedEki->getDiagramColorNextEki() - 1);
//				}
//			}
//		}
//
//		if (iRv >= 0)
//		{
//			// --------------------------------
//			//	編集コマンドを実行
//			// --------------------------------
//			getCDiagramEditDoc()->executeEditCmd(pCmd);
//		}
//
//		// ****************************************************************
//		//	エラーメッセージ
//		// ****************************************************************
//
//		// ****************************************************************
//	}
//	return iRv;
//}
//void CWndDcdGridEkiJikokuhyouList::ChangeNextEkiDistance(CentDedEki* pCentDedEki, int iShiftSecond)
//{
//	int iNextEkiDistance = pCentDedEki->getNextEkiDistance();
//	iNextEkiDistance += iShiftSecond;
//	if (iNextEkiDistance < 0)
//	{
//		iNextEkiDistance = 0;
//	}
//	if (iNextEkiDistance > 7200)
//	{
//		iNextEkiDistance = 7200;
//	}
//	pCentDedEki->setNextEkiDistance(iNextEkiDistance);
//}

int CWndDcdGridEkiJikokuhyouList::OnEkiJikokuhyouListMovetoEkiJikokuhyou_Process(BOOL bQueryEnable)
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
		CdDcdPosXy aPos = getCFocus()->getFocusCellColumnNumber();
		if (aPos == getCFocus()->ColumnNumberPosXy_NULL())
		{
			iRv = -2;
		}
		if (iRv >= 0 && aPos.getX() == 0)
		{
			iRv = -3;
		}
	}
	//CdEkiJikokuhyouYColSpec aCdEkiJikokuhyouYColSpec = getYColSpecOfFocus();
	//CdEkiJikokuhyouXColSpec aCdEkiJikokuhyouXColSpec = getXColSpecOfFocus();
	//if (iRv >= 0)
	//{
	//	if (getCSelect()->getSelectedCellCount() == 0)
	//	{
	//		if (aCdEkiJikokuhyouYColSpec.getColumnType() ==
	//			CdEkiJikokuhyouYColSpec::ColumnType_Head)
	//		{
	//			iRv = -3;	//フォーカスが列車位置以外なら不可
	//		}
	//		else if (aCdEkiJikokuhyouXColSpec.getColumnType() ==
	//			CdEkiJikokuhyouXColSpec::ColumnType_Hour)
	//		{
	//			iRv = -4;
	//		}
	//	}
	//	else
	//	{
	//		iRv = -5; //複数選択は不可
	//	}

	//}
	if (!bQueryEnable && iRv >= 0)
	{
		CdDcdPosXy aPos = getCFocus()->getFocusCellColumnNumber();
		if (aPos == getCFocus()->ColumnNumberPosXy_NULL())
		{
			iRv = -11;
		}
		
		if (iRv >= 0)
		{
			ERessyahoukou eRessyahoukou = (ERessyahoukou)(aPos.getX() - 1);
			int iEkiIndex = aPos.getY();

			// ****************************************************************
			//	コマンドの実行
			// ****************************************************************
			CEkiJikokuhyouView* pCEkiJikokuhyouView = NULL;
			getCDiagramEditApp()->openCEkiJikokuhyouDoc(
				getCentDedDia(),
				eRessyahoukou,
				iEkiIndex,
				&pCEkiJikokuhyouView);
		}
	}
	return iRv;
}

int CWndDcdGridEkiJikokuhyouList::OnFileExportAllEkiJikokuhyouCsv_Process(BOOL bQueryEnable)
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
			getCDiagramEditApp()->readCWndDcdGridEkiJikokuhyouListProp(this);

			CconvEkiJikokuhyouCsv	aConv;
			CdCsvDocument	aCdCsvDocument;

			CDiagramEditDoc* pCDiagramEditDoc = getCDiagramEditDoc();
			const CentDedRosen* pCentDedRosen =
				pCDiagramEditDoc->getCDedRosenFileData()->getCentDedRosen();
			const CentDedEkiCont* pCentDedEkiCont = getCDiagramEditDoc()->
				getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont();
			int iEnableOperation = getCDiagramEditDoc()->
				getCDedRosenFileData()->getCentDedRosen()->getEnableOperation();
			unordered_map<tstring, list<OperationTableContent>> contOperationTableContent =
				getCentDedDia()->getcontOperationTableContent();
			const CdDedJikoku KitenJikoku = getCDiagramEditDoc()->getCDedRosenFileData()
				->getCentDedRosen()->getKitenJikoku();
			CdDedJikoku::CConv::ESecondRound eSecondRound = (CdDedJikoku::CConv::ESecondRound)getCDiagramEditDoc()
				->getCDedRosenFileData()->getCdDedDispProp().getSecondRoundHatsu();
			bool bResume = false;

			const Mu<const CentDedRessya*>* pCentDedRessyaConts[2];
			for (int iRessyahoukou = Ressyahoukou_Kudari;
				iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
			{
				pCentDedRessyaConts[iRessyahoukou] = getCentDedDia()->getCentDedRessyaCont((ERessyahoukou)iRessyahoukou)->getMuPtr();
			}

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

			for (int iEkiIndex = 0; iEkiIndex < pCentDedEkiCont->size(); iEkiIndex++)
			{
				const CentDedEki* pCentDedEki =
					pCentDedEkiCont->getMuPtr()->get(iEkiIndex);
				for (int iRessyahoukou = Ressyahoukou_Kudari;
					iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
				{
					if (iRessyahoukou == Ressyahoukou_Kudari &&
						pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku)
					{
						continue;
					}
					else if(iRessyahoukou == Ressyahoukou_Nobori &&
						pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku)
					{
						continue;
					}

					map<int, list<EkiJikokuhyouContent>> contListEkiJikokuhyouContent;

					const CentDedRessyaCont* pCentDedRessyaCont = getCentDedDia()->getCentDedRessyaCont((ERessyahoukou)iRessyahoukou);

					int iEkiOrder = pCentDedRessyaCont->EkiOrderOfEkiIndex(iEkiIndex);
					//この駅と、分岐駅・環状線設定で関連付けられた駅のIndexです。環状列車判定に用います
					deque<int> iEkiIndexBrunchLoop;
					pCentDedEkiCont->getEkiIndexBrunchLoop(iEkiIndex, iEkiIndexBrunchLoop);

					for (int iRessyaIndex = 0; iRessyaIndex < pCentDedRessyaCont->size(); iRessyaIndex++)
					{
						const CentDedRessya* pCentDedRessya = pCentDedRessyaCont->getMuPtr()->get(iRessyaIndex);
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
								CdDedRessyaProperty((ERessyahoukou)iRessyahoukou, iRessyaIndex);

							bool bIsShihatsu = pCentDedRessya->getValidSihatsuEki() == iEkiOrder;
							if (bIsShihatsu)
							{
								if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
								{
									bIsShihatsu = false;
								}
							}
							aEkiJikokuhyouContent.bIsShihatsu = bIsShihatsu;

							if (contListEkiJikokuhyouContent.find(aHatsuJikoku.getHour()) == contListEkiJikokuhyouContent.end())
							{
								contListEkiJikokuhyouContent[aHatsuJikoku.getHour()] = list<EkiJikokuhyouContent>(1, aEkiJikokuhyouContent);
							}
							else
							{
								list<EkiJikokuhyouContent>& ListEkiJikokuhyouContent =
									contListEkiJikokuhyouContent[aHatsuJikoku.getHour()];
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
						else if (iEnableOperation == 1)
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
								getCentDedDia()->getcontCustomizeRessyaIndex((ERessyahoukou)iRessyahoukou);
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
														CdDedRessyaProperty((ERessyahoukou)iRessyahoukou, aCustomizeJikokuhyouContent.iRessyaIndexCont[idx2]);

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
							//aEkiJikokuhyouContent.aRessyaProperty =
							//	CdDedRessyaProperty(GetDocument()->getRessyahoukou(), iRessyaIndex);

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

							if (contListEkiJikokuhyouContent.find(aHatsuJikoku.getHour()) == contListEkiJikokuhyouContent.end())
							{
								contListEkiJikokuhyouContent[aHatsuJikoku.getHour()] = ListEkiJikokuhyouContentTemp;
							}
							else
							{
								list<EkiJikokuhyouContent>& ListEkiJikokuhyouContent =
									contListEkiJikokuhyouContent[aHatsuJikoku.getHour()];
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
						else
						{
							vector<tstring> strContOperationNumber = pCentDedRessya->getOperationNumber(iEkiOrder);

							CdDedJikoku aHatsuJikoku = pCentDedRessya->getCentDedEkiJikoku(iEkiOrder).getVirtualHatsujikoku();
							//CdDedJikoku aHatsuJikoku = pCentDedRessya->getCentDedEkiJikoku(iEkiOrder).getHatsujikoku();
							aHatsuJikoku.round(eSecondRound);
							CdDedRessyaProperty aRessyaProperty(
								(ERessyahoukou)iRessyahoukou,
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
											//aRessyaPropertyBufferNextの終着駅Orderはその列車基準でokとする(同じ列車同士で比較し、終着駅の遠さを見る必要があるので)
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
							if (contListEkiJikokuhyouContent.find(aHatsuJikoku.getHour()) == contListEkiJikokuhyouContent.end())
							{
								contListEkiJikokuhyouContent[aHatsuJikoku.getHour()] = ListEkiJikokuhyouContentTemp;
							}
							else
							{
								list<EkiJikokuhyouContent>& ListEkiJikokuhyouContent =
									contListEkiJikokuhyouContent[aHatsuJikoku.getHour()];
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

					if (contListEkiJikokuhyouContent.empty())
					{
						continue;
					}

					/**
						駅時刻表コンテンツの読み取りが終わったら、
						各時帯の列車本数を調べ、実際の駅時刻表の表示範囲を決める。
						起点時刻のある時間帯→起点時刻のある時間帯-1の順で調べる。
						最初に列車がある時間帯がm_iFirstHourとなり、最後に列車がある時間帯までの時数がm_iHourCountとなる
						ここでは、途中に列車がない時間帯があっても、表示のスキップはしない。
						また、m_iMaxRessyaCount(最も列車本数が多い時間の列車本数)も求める
					*/
					int iFirstHour = INT_MIN;
					int iHourCount = INT_MIN;
					int iOffset = 0;
					int iBlankHourCount = 0;
					for (int iHour = KitenJikoku.getHour(); iHour < KitenJikoku.getHour() + 24; iHour++)
					{
						if (iHour == 24)
						{
							iOffset = -24;
						}
						if (contListEkiJikokuhyouContent.find(iHour + iOffset) == contListEkiJikokuhyouContent.end())
						{
							iBlankHourCount++;
							continue;
						}

						if (iFirstHour == INT_MIN)
						{
							iFirstHour = iHour + iOffset;
							iHourCount = 1;
							iBlankHourCount = 0;
						}
						else
						{
							if (iBlankHourCount != 0)
							{
								iHourCount += iBlankHourCount;
								iBlankHourCount = 0;
							}
							iHourCount++;
						}
					}

					tstring strTitle = GetDocument()->getDiaName();
					strTitle += _T(" ");

					strTitle += pCentDedEki->getEkimei();

					CString	strEki;
					strEki.LoadString(IDS_WORD_EKI);
					strTitle += strEki;

					strTitle += _T(" ");

					CString	strRessyahoukou;
					if (iRessyahoukou == Ressyahoukou_Kudari)
					{
						if (pCentDedRosen->getKudariDiaAlias().empty())
						{
							strRessyahoukou.LoadString(IDS_WORD_KUDARIJIKOKUHYOU);
						}
						else
						{
							strRessyahoukou = pCentDedRosen->getKudariDiaAlias().c_str();
							CString strJikokuhyou;
							strJikokuhyou.LoadString(IDS_WORD_JIKOKUHYOU);
							strRessyahoukou += strJikokuhyou;
						}
					}
					else
					{
						if (pCentDedRosen->getNoboriDiaAlias().empty())
						{
							strRessyahoukou.LoadString(IDS_WORD_NOBORIJIKOKUHYOU);
						}
						else
						{
							strRessyahoukou = pCentDedRosen->getNoboriDiaAlias().c_str();
							CString strJikokuhyou;
							strJikokuhyou.LoadString(IDS_WORD_JIKOKUHYOU);
							strRessyahoukou += strJikokuhyou;
						}
					}

					strTitle += strRessyahoukou;

					iRv = aConv.encode(
						(ERessyahoukou)iRessyahoukou,
						iEkiOrder,
						contListEkiJikokuhyouContent,
						strTitle,
						iFirstHour,
						iHourCount,
						getDisplayParentSyubetsu(),
						bResume,
						getDisplayTrack(),
						getDisplayIsShihatsu(),
						&aCdCsvDocument);
					if (iRv < 0)
					{
						break;
					}
					bResume = true;
				}
				if (iRv < 0)
				{
					break;
				}
			}
			if (iRv < 0)
			{
				GetDlgItemText(IDC_TEXT_ENCODE_ERROR, strError);
				//strError="CSVへの変換に失敗しました。"

				strError.Format(_T("%s(%d)"), CString(strError), iRv);
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

// ********************************
//	コンストラクタ
// ********************************
CWndDcdGridEkiJikokuhyouList::CWndDcdGridEkiJikokuhyouList()
	: m_bWaitForActivate( true )
	, m_bInitialUpdateComplete( false )
{
	getCSelect()->setSelectMode( CSelect::SelectMode_NONE ) ;

}
CWndDcdGridEkiJikokuhyouList::~CWndDcdGridEkiJikokuhyouList()
{
}

	// ********************************
	//@name CWndDcdGridEkiJikokuhyouList-属性
	// ********************************




	// ********************************
	//@name CEkiView からの委譲
	// ********************************
void CWndDcdGridEkiJikokuhyouList::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if ( lHint == LHINT_SUBVIEW_TO_ROOTDOC )
	{
		//	ビューの内容をドキュメントに反映させる指令です。
		//	後続の処理は行いません。
		return ;
	}
	// --------------------------------
	//	初回のOnUpdate()
	//	.iniファイルからプロパティを読み込み
	// --------------------------------
	if ( !m_bInitialUpdateComplete )
	{
		//getCDiagramEditApp()->readCWndDcdGridEkiJikokuhyouListProp( this ) ;
		// --------------------------------
		m_bInitialUpdateComplete = true ;
	}

	// --------------------------------
	//	更新コマンドを取得
	// --------------------------------
	Ou<CRfEditCmd> pCmd ;
	if ( pHint != NULL 
		&& pHint->IsKindOf(RUNTIME_CLASS(CRfEditCmdHolder)) )
	{
		CRfEditCmdHolder* pHolder = 
			(CRfEditCmdHolder*)pHint ;
		pCmd = pHolder->getCmd() ; 
	}
	//pCmd=編集コマンド CRfEditCmd 。
	//	NULLなら、全更新が要求されています。

	//pHint= 
	//	pHintが CRfEditCmdHolder オブジェクトなら、
	//	対応する編集コマンド CRfEditCmd を保持しています。
	//	この場合、this は CRfEditCmd の内容に最適化した
	//	更新を行います。
	//	NULLなら、全更新が要求されています。

	if ( m_bWaitForActivate )
	{
		//	全更新が保留されている場合は、
		//	コマンドを無視して、全更新を行います。
		pCmd = Ou<CRfEditCmd>() ;
	}

	// --------------------------------
	{
		CDiagramEditDoc* pCDiagramEditDoc = getCDiagramEditDoc() ;
		const CentDedRosen*	pCentDedRosen = 
			pCDiagramEditDoc->getCDedRosenFileData()->getCentDedRosen() ;
		const Mu<const CentDedEki*>* pCentDedEkiContGet 
			= pCentDedRosen->getCentDedEkiCont()->getMuPtr() ;

		if ( dynamic_castOu<CRfEditCmd_Comment>( pCmd ) || 
			dynamic_castOu<CRfEditCmd_Dia>( pCmd ) ||
			dynamic_castOu<CRfEditCmd_DiaProp>(pCmd) ||
			dynamic_castOu<CRfEditCmd_Ressya>( pCmd ) || 
			dynamic_castOu<CRfEditCmd_Ressyasyubetsu>( pCmd )||
			dynamic_castOu<CRfEditCmd_RessyasyubetsuSwap>( pCmd ) ||
			dynamic_castOu<CRfEditCmd_Operation>(pCmd)
		)
		{
			//	このビューは、
			//		コメントの変更
			//		ダイヤの変更
			//		ダイヤのプロパティの変更
			//		列車の変更
			//		列車の直通化
			//		列車種別の変更
			//		列車種別の入替
			//	の場合は、更新を行いません。
			//
		}
		//駅を変更した場合、全更新にするため、onupdate_allに統合します
//		else if (dynamic_castOu<CRfEditCmd_Eki>(pCmd))
//		{
//
//			//		駅の変更
//			Ou<CRfEditCmd_Eki>	pCommand
//				= dynamic_castOu<CRfEditCmd_Eki>(pCmd);
//
//			//	コマンドオブジェクト実行によるセル移動でセル選択にならないように、
//			//	セル選択を解除し、セル選択機能も一時的に中止します。
//			if (pCommand->getCaMuiSelect()->size() == 1)
//			{
//				clearSelect();
//				CPropStack aPropStack(this);
//				aPropStack
//					.CBoxSelect_setIsEnable(false)
//					.CRandomSelect_setIsEnable(false);
//			}
//
//			// --------------------------------
//			//	減少分の要素の削除
//			// --------------------------------
//			CentDedEkiCont	aCentDedEkiContSrc 
//				= *pCommand->getCentDedEkiContSrc() ;
//			int iGensyouSize = 
//				pCommand->getSizeDst() - aCentDedEkiContSrc.size() ;
//			if ( iGensyouSize > 0 ){
//				for ( int cnt = 0 ; cnt < iGensyouSize ; cnt ++ ){
//					getCXDcdGrid()->eraseYColumn( 
//						pCommand->getIndexDst() + 
//						pCommand->getSizeDst() - iGensyouSize 
//						+ 1 ) ;
//				}
//			}
//			// --------------------------------
//			//	増加分の要素の追加
//			// --------------------------------
//			int iOkikaeSize = 0 ;
//			iOkikaeSize = 
//				min( pCommand->getSizeDst() , aCentDedEkiContSrc.size() ) ;
//			int iZoukaSize = 
//				aCentDedEkiContSrc.size() - pCommand->getSizeDst() ;
//			if ( iZoukaSize > 0 )
//			{
//				for ( int cnt = 0 ; cnt < iZoukaSize ; cnt ++ )
//				{
//					getCXDcdGrid()->insertYColumn( 
//						pCommand->getIndexDst() + iOkikaeSize + cnt + 1 , 
//						true ) ; 
//				}
//			}
//			// --------------------------------
//			//	要素の更新
//			// --------------------------------
//			//境界線の設定のため、一つ前も更新する。
//			{
//				/*for ( int cnt = 0 ; cnt < aCentDedEkiContSrc.size() ; cnt ++ )
//				{
//					int iEkiIndex = pCommand->getIndexDst() + cnt ;
//					const CentDedEki*	pCentDedEki 
//						= pCentDedEkiContGet->get( iEkiIndex ) ;
//					if (iEkiIndex == 0 &&
//						pCentDedEkiContGet->size()>1)
//					{
//						const CentDedEki*	pCentDedEkiNext
//							= pCentDedEkiContGet->get(iEkiIndex + 1);
//						OnUpdate_setCentDedEki_To_Column(
//							iEkiIndex + 1, *pCentDedEki, *pCentDedEkiNext);
//					}
//					else if (iEkiIndex == 0 )
//					{
//						OnUpdate_setCentDedEki_To_Column(
//							iEkiIndex + 1, *pCentDedEki, CentDedEki());
//					}
//					else if (iEkiIndex < pCentDedEkiContGet->size()-1)
//					{
//						const CentDedEki*	pCentDedEkiPrev
//							= pCentDedEkiContGet->get(iEkiIndex - 1);
//						const CentDedEki*	pCentDedEkiNext 
//							= pCentDedEkiContGet->get(iEkiIndex + 1);
//						OnUpdate_setCentDedEki_To_Column(
//							iEkiIndex , *pCentDedEkiPrev, *pCentDedEki);
//						OnUpdate_setCentDedEki_To_Column(
//							iEkiIndex + 1, *pCentDedEki, *pCentDedEkiNext);
//					}
//					else
//					{
//						const CentDedEki*	pCentDedEkiPrev
//							= pCentDedEkiContGet->get(iEkiIndex - 1);
//						OnUpdate_setCentDedEki_To_Column(
//							iEkiIndex, *pCentDedEkiPrev, *pCentDedEki);
//						OnUpdate_setCentDedEki_To_Column(
//							iEkiIndex + 1, *pCentDedEki, CentDedEki());
//					}
//				}*/
//				//駅の挿入・削除を行うと、駅Index番号表示および分岐駅・環状線設定の
//				//相手先番号が変わる場合があるので、全駅を更新します
//				//(挿入・削除が行われた箇所よりも下側だけでなく、
//				//その範囲内の駅に対し、分岐駅設定を行っている、上側の駅もありうるため
//				//区域を指定するよりも、全更新の方が手っ取り早いという判断です)
//				int iEkiSize = pCentDedEkiContGet->size();
////#pragma omp parallel for schedule(static)
//				for (int cnt = 0; cnt < iEkiSize; cnt++)
//				{
//					int iEkiIndex =  cnt;
//					const CentDedEki*	pCentDedEki
//						= pCentDedEkiContGet->get(iEkiIndex);
//					if (iEkiIndex == 0 &&
//						pCentDedEkiContGet->size()>1)
//					{
//						OnUpdate_setCentDedEki_To_Column(
//							iEkiIndex + 1, *pCentDedEki);
//					}
//					else if (iEkiIndex == 0)
//					{
//						OnUpdate_setCentDedEki_To_Column(
//							iEkiIndex + 1, *pCentDedEki);
//					}
//					else if (iEkiIndex < pCentDedEkiContGet->size() - 1)
//					{
//						const CentDedEki*	pCentDedEkiPrev
//							= pCentDedEkiContGet->get(iEkiIndex - 1);
//						OnUpdate_setCentDedEki_To_Column(
//							iEkiIndex, *pCentDedEkiPrev);
//						OnUpdate_setCentDedEki_To_Column(
//							iEkiIndex + 1, *pCentDedEki);
//					}
//					else
//					{
//						const CentDedEki*	pCentDedEkiPrev
//							= pCentDedEkiContGet->get(iEkiIndex - 1);
//						OnUpdate_setCentDedEki_To_Column(
//							iEkiIndex, *pCentDedEkiPrev);
//						OnUpdate_setCentDedEki_To_Column(
//							iEkiIndex + 1, *pCentDedEki);
//					}
//				}
//				InvalidateGrid();
//			}
//			// --------------------------------
//			
//		}
		else
		{
			//CRfEditCmd_DedRosenFileDataProp
			//	  路線ファイルのプロパティの変更は、
			//	フォントの変化を伴うため、全更新が必要です。
			//CRfEditCmd_Rosen
			//CRfEditCmd_RosenFileData
			//	駅を包含するオブジェクトです。これが更新された場合は、
			//	全更新が必要です。
			//CRfEditCmd_Eki
			//	全更新とします

			//	全要素を更新
			OnUpdate_All() ;
		}
	}
	// --------------------------------
	//	列選択範囲を設定
	// --------------------------------
	{
		CDiagramEditDoc* pCDiagramEditDoc = getCDiagramEditDoc() ;
		const CentDedRosen*	pCentDedRosen = 
			pCDiagramEditDoc->getCDedRosenFileData()->getCentDedRosen() ;
		const Mu<const CentDedEki*>* pCentDedEkiContGet 
			= pCentDedRosen->getCentDedEkiCont()->getMuPtr() ;

		//int iYColumnBegin = createYColSpecCont().ColumnNumberFromSpec( 
		//	CdEkiYColSpec( CdEkiYColSpec::ColumnType_Eki , 0 ) ) ;

		getCSelect()->setColumnNumberSelectLimit(
			CdDcdZoneXy( 
				CdDcdZone( 0 , INT_MAX ) , 
				CdDcdZone( 0 , pCentDedEkiContGet->size()   ) 
			) );
	}
}

void CWndDcdGridEkiJikokuhyouList::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	if ( bActivate && m_bWaitForActivate ){
		OnUpdate_All() ;
	}
}





	// ********************************
	//@name CWndDcdGridEkiJikokuhyouList-操作
	// ********************************

CEkiJikokuhyouListDoc* CWndDcdGridEkiJikokuhyouList::GetDocument()
{
	CView* pCView = (CView*)GetParent();
	return (CEkiJikokuhyouListDoc*)pCView->GetDocument();
}

const CentDedDia* CWndDcdGridEkiJikokuhyouList::getCentDedDia()
{
	const CentDedRosen* pCentDedRosen =
		getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen();
	int iDiaIndex = pCentDedRosen->getCentDedDiaCont()->findCentDedDiaByName(
		GetDocument()->getDiaName());
	if (iDiaIndex < 0) {
		return (NULL);
	}
	const CentDedDia* pCentDedDia = pCentDedRosen->getCentDedDiaCont()->getMuPtr()->get(iDiaIndex);
	return (pCentDedDia);
};

//int CWndDcdGridEkiJikokuhyouList::execEkiPropDlg( bool bInsert , BOOL bQueryEnable ) 
//{
//	int iRv = 0 ;
//	Ou<CRfEditCmd_Eki>	pCmd ;
//	Ou<CRfEditCmd_Eki>*	ppCmd = NULL ;
//	if ( !bQueryEnable ){	ppCmd = &pCmd ;};
//
//	// ****************************************************************
//	//	コマンドの実行可否の判定
//	// ****************************************************************
//	if ( iRv >= 0 )
//	{
//		if ( bInsert )
//		{
//			if ( !createCmd( ECreateCmd_NewItem , ppCmd ) )
//			{
//				iRv = -1 ;	//	セルの位置が不正です。
//			}
//		}
//		else
//		{
//			if ( !createCmd( ECreateCmd_Select , ppCmd ) ) 
//			{
//				iRv = -1 ;
//			}
//		}
//	}
//	// ****************************************************************
//	if ( !bQueryEnable && iRv >= 0 )
//	{
//		// ****************************************************************
//		//	コマンドの実行
//		// ****************************************************************
//		CdEkiXColSpec	aXColSpec = getXColSpecOfFocus() ;
//		int iFocus = -1 ;
//		switch( aXColSpec.getColumnType() )
//		{
//		case aXColSpec.ColumnType_EkiIndex:
//			iFocus = 0;
//			break;
//		case aXColSpec.ColumnType_Ekimei:
//			iFocus = 0 ; 
//			break ;
//		case aXColSpec.ColumnType_Ekijikokukeisiki:
//			iFocus = 1 ;
//			break ;
//		case aXColSpec.ColumnType_Ekikibo:
//			iFocus = 2 ;
//			break ;
//		case aXColSpec.ColumnType_EkiBrunch:
//			iFocus = 3;
//			break;
//		case aXColSpec.ColumnType_EkiLoop:
//			iFocus = 4;
//			break;
//		}
//		int iEkiIndex = -2;
//		bool bEkijikokukeisikiAndEkikiboEnable = true;
//		bool bBrunchFunctionEnable = true;
//		bool bLoopFunctionEnable = true;
//		vector<int> iEkiTrack2Map;
//		vector<int> iOuterTerminalEkimeiMap;
//		if (bInsert)
//		{
//			//新規アイテムの場合、iEkiIndexを-1とする。
//			//iEkiIndex = -1;
//			CdEkiYColSpec  aCdYColSpecOfFocus = getYColSpecOfFocus();
//			iEkiIndex = aCdYColSpecOfFocus.getEkiIndex();
//			bEkijikokukeisikiAndEkikiboEnable = true;
//			bBrunchFunctionEnable = true;
//			bLoopFunctionEnable = true;
//			//pCmd->setBrunchCoreEkiIndex(-1);
//		}
//		else if ( getCSelect()->getSelectedCellCount() == 0)
//		{
//			//単数選択の場合、iEkiIndexは駅Indexになる。
//			//bEkijikokukeisikiAndEkikiboEnable 
//			//	基幹駅もしくは起点駅の場合、false
//			//bBrunchFunctionEnable
//			//	基幹駅もしくは起点駅の場合、false
//			//bLoopFunctionEnable
//			//	起点方に派生駅を持つ基幹駅の場合、false
//			//※ダイアログオープン後、分岐駅設定及び環状線設定を変えた場合に、trueになるような場合は、
//			//最初からtrueにし、FromTargetでfalseにする。
//			CdEkiYColSpec  aCdYColSpecOfFocus = getYColSpecOfFocus();
//			iEkiIndex = aCdYColSpecOfFocus.getEkiIndex();
//			const Mu< const CentDedEki* >* pCentDedEkiCont = getCDiagramEditDoc()->getCDedRosenFileData()
//				->getCentDedRosen()->getCentDedEkiCont()->getMuPtr();
//			const CentDedEki* pCentDedEki = pCentDedEkiCont->get(iEkiIndex);
//			if (pCentDedEki->getBrunchLoopPosition() != -1 &&
//				pCentDedEki->getBrunchLoopPosition() != INT_MAX &&
//				pCentDedEki->getBrunchLoopPosition() != INT_MIN)
//			{
//				if (pCentDedEki->getBrunchLoopPosition() < (int)pCentDedEki->getEkiIndexLoop().size() - 1)
//				{
//					/**
//						EkiIndexLoopのiEkiIndexよりも後方に値が存在する場合は、iEkiIndexは"起点駅"になる。
//					*/
//					bEkijikokukeisikiAndEkikiboEnable = false;
//					bBrunchFunctionEnable = false;
//				}
//				if (pCentDedEki->getBrunchLoopPosition() == 0 &&
//					pCentDedEki->getEkiIndexBrunchOriginSide().size() > 0)
//				{
//					/**
//						iEkiIndexがEkiIndexLoopの先頭にあり、EkiIndexBrunchOriginSideに一つ以上の値がある場合は、
//						この駅は"起点方に派生駅を持つ基幹駅"となる。
//					*/
//					bEkijikokukeisikiAndEkikiboEnable = false;
//					bBrunchFunctionEnable = false;
//					bLoopFunctionEnable = false;
//
//				}
//				if (pCentDedEki->getBrunchLoopPosition() == pCentDedEki->getEkiIndexLoop().size() - 1 &&
//					pCentDedEki->getEkiIndexBrunchTerminalSide().size() > 0)
//				{
//					/**
//						iEkiIndexがEkiIndexLoopの末尾にあり、EkiIndexBrunchTerminalSideに一つ以上の値がある場合は、
//						この駅は"終点方に派生駅を持つ基幹駅"となる。
//					*/
//					bEkijikokukeisikiAndEkikiboEnable = false;
//					bBrunchFunctionEnable = false;
//
//				}
//
//			}
//
//
//
//
//			//for (int idx = 0; idx < pCentDedEkiCont->size(); idx++)
//			//{
//			//	if (iEkiIndex != idx)
//			//	{
//			//		if (pCentDedEkiCont->get(idx)->getBrunchCoreEkiIndex() == iEkiIndex)
//			//		{
//			//			bEkijikokukeisikiAndEkikiboEnable = false;
//			//			bBrunchFunctionEnable = false;
//			//			if (iEkiIndex > idx)
//			//			{
//			//				bLoopFunctionEnable = false;
//			//			}
//			//		}
//			//		if (pCentDedEkiCont->get(idx)->getLoopOriginEkiIndex() == iEkiIndex)
//			//		{
//			//			bEkijikokukeisikiAndEkikiboEnable = false;
//			//			bBrunchFunctionEnable = false;
//			//		}
//			//	}
//			//}
//			pCmd->setBrunchCoreEkiIndex(
//				pCentDedEki->getBrunchCoreEkiIndex()
//				//pCentDedEkiCont->get(iEkiIndex)->getBrunchCoreEkiIndex()
//			);
//			pCmd->setLoopOriginEkiIndex(
//				pCentDedEki->getLoopOriginEkiIndex()
//				//pCentDedEkiCont->get(iEkiIndex)->getLoopOriginEkiIndex()
//			);
//			//駅番線の変更処理のためのMapを初期化する
//			for (int idx = 0; idx < pCentDedEkiCont->get(iEkiIndex)->getEkiTrack2Cont()->size(); idx++)
//			{
//				iEkiTrack2Map.push_back(idx);
//			}
//			//路線外発着駅の変更処理のためのMapを初期化する
//			for (int idx = 0; idx < pCentDedEkiCont->get(iEkiIndex)->getOuterTerminalEkimeiCount(); idx++)
//			{
//				iOuterTerminalEkimeiMap.push_back(idx);
//			}
//		}
//		else
//		{
//			//複数選択の場合、iEkiIndexを-2とする。
//			//選択された駅の中に、基幹駅がある場合、駅時刻形式と駅規模の変更を不可にする。
//			//選択された駅の中に、派生駅がある場合、駅時刻形式と駅規模の変更を不可にする。
//			//選択された駅の中に、起点駅がある場合、駅時刻形式と駅規模の変更を不可にする。
//			//選択された駅の中に、終点駅がある場合、駅時刻形式と駅規模の変更を不可にする。
//			const Mu< const CentDedEki* >* pCentDedEkiCont = getCDiagramEditDoc()->getCDedRosenFileData()
//				->getCentDedRosen()->getCentDedEkiCont()->getMuPtr();
//			//int iEkiIndexSelect;
//			CdEkiYColSpecCont aCdYColSpecCont = createYColSpecCont();
//
//			for (int iColumnNumber = 0;
//				iColumnNumber < getCXDcdGrid()->getYColumnCount() && bEkijikokukeisikiAndEkikiboEnable ;
//				iColumnNumber++)
//			{
//				if (getCSelect()->getYColumnNumberSelected(iColumnNumber))
//				{
//					CdEkiYColSpec aCdEkiYColSpec = aCdYColSpecCont.ColumnNumberToSpec(iColumnNumber);
//					int iEkiIndexSelect = aCdEkiYColSpec.getEkiIndex();
//					if (pCentDedEkiCont->get(iEkiIndexSelect)->getBrunchLoopPosition() != -1)
//					{
//						bEkijikokukeisikiAndEkikiboEnable = false;
//					}
//					//if (pCentDedEkiCont->get(iEkiIndexSelect)->getBrunchCoreEkiIndex() >= 0 ||
//					//	pCentDedEkiCont->get(iEkiIndexSelect)->getLoopOriginEkiIndex() >= 0)
//					//{
//					//	bEkijikokukeisikiAndEkikiboEnable = false;
//					//}
//					//for (int idx = 0; idx < pCentDedEkiCont->size(); idx++)
//					//{
//					//	if (iEkiIndexSelect != idx)
//					//	{
//					//		if (pCentDedEkiCont->get(idx)->getBrunchCoreEkiIndex() == iEkiIndexSelect ||
//					//			pCentDedEkiCont->get(idx)->getLoopOriginEkiIndex() == iEkiIndexSelect)
//					//		{
//					//			bEkijikokukeisikiAndEkikiboEnable = false;
//					//			//選択された駅は、他の駅から共有対象に指定されています
//					//		}
//					//	}
//					//}
//				}
//			}
//			iEkiIndex = -2;
//			bBrunchFunctionEnable = false;
//			bLoopFunctionEnable = false;
//			//pCmd->setBrunchCoreEkiIndex(-2);
//		}
//		CDlgEkiProp	aDlg( 
//			bInsert,
//			pCmd->getCaMuiSelect()->getMuPtr() ,
//			&m_bAdjustByEkijikokukeisiki , 
//			iEkiIndex,
//			bEkijikokukeisikiAndEkikiboEnable,
//			bBrunchFunctionEnable,
//			bLoopFunctionEnable,
//			iEkiTrack2Map,
//			iOuterTerminalEkimeiMap,
//			iFocus , 
//			&m_CKeyinputSenderToModalDlg , 
//			this ) ;
//		if ( aDlg.DoModal() == IDOK )
//		{
//			iRv = 1 ;
//
//			//	[駅時刻を駅時刻形式で正規化]の設定を、
//			//	次に実行するコマンドに反映します。
//			pCmd->setAdjustByEkijikokukeisiki( m_bAdjustByEkijikokukeisiki ) ;
//
//			if (getCSelect()->getSelectedCellCount() == 0)
//			{
//				if (pCmd->getBrunchCoreEkiIndex() ==
//					pCmd->getCaMuiSelect()->getMuPtr()->get(0)->getBrunchCoreEkiIndex())
//				{
//					pCmd->setChangeBrunchCoreEkiIndex(false);
//				}
//				else
//				{
//					pCmd->setBrunchCoreEkiIndex(
//						pCmd->getCaMuiSelect()->getMuPtr()->get(0)->getBrunchCoreEkiIndex());
//					pCmd->setChangeBrunchCoreEkiIndex(true);
//				}
//				if (pCmd->getLoopOriginEkiIndex() ==
//					pCmd->getCaMuiSelect()->getMuPtr()->get(0)->getLoopOriginEkiIndex())
//				{
//					pCmd->setChangeLoopOriginEkiIndex(false);
//				}
//				else
//				{
//					pCmd->setLoopOriginEkiIndex(
//						pCmd->getCaMuiSelect()->getMuPtr()->get(0)->getLoopOriginEkiIndex());
//					pCmd->setChangeLoopOriginEkiIndex(true);
//				}
//			}
//
//			pCmd->setEkiTrack2Map(iEkiTrack2Map);
//			pCmd->setOuterTerminalEkimeiMap(iOuterTerminalEkimeiMap);
//		}
//		// --------------------------------
//		//	ダイアログOK時の処理
//		// --------------------------------
//		if ( iRv == 1 )
//		{
//			// --------------------------------
//			//	編集コマンドを実行
//			// --------------------------------
//			getCDiagramEditDoc()->executeEditCmd( pCmd ) ;
//		}
//		// ****************************************************************
//		//	エラーメッセージ
//		// ****************************************************************
//		if ( iRv < 0 )
//		{
//			CString strErrorMessage ;
//			switch( iRv )
//			{
//			case -1 :	//	現在は実行できません。
//				break ;
//			default:
//				strErrorMessage.Format( _T( "Error=%d" ) , iRv ) ;
//				break ;
//			}
//			if ( strErrorMessage.GetLength() > 0 )
//			{
//				MessageBox( strErrorMessage , NULL , MB_ICONSTOP | MB_OK ) ; 
//			}
//		}
//
//		// ****************************************************************
//	}
//	return iRv ;
//}
//
//int CWndDcdGridEkiJikokuhyouList::OnViewDisplaySettingMode_Process(BOOL bQueryEnable)
//{
//	int iRv = 0;
//	// ****************************************************************
//	//	コマンドの有効・無効判定
//	// ****************************************************************
//	if (getDisplaySettingMode())
//	{
//		iRv = 1;	//(bQueryEnable==TRUEの場合)[表示設定モードにする]が有効です。
//	}
//	// ****************************************************************
//	if (!bQueryEnable && iRv >= 0)
//	{
//		// ****************************************************************
//		//	コマンドを実行
//		// ****************************************************************
//		setDisplaySettingMode(!getDisplaySettingMode());
//
//		// ****************************************************************
//		//	エラーメッセージ
//		// ****************************************************************
//
//		// ****************************************************************
//	}
//	return iRv;
//}

//bool CWndDcdGridEkiJikokuhyouList::getDisplaySettingMode() const
//{
//	return m_bDisplaySettingMode;
//}
//
//int CWndDcdGridEkiJikokuhyouList::setDisplaySettingMode(bool value)
//{
//	int iRv = 0;
//	if (m_bDisplaySettingMode != value)
//	{
//		m_bDisplaySettingMode = value;
//
//		//	表示設定モードの有効無効が変化した場合は、
//		//	ビューを更新します。
//		OnUpdate_All();
//		InvalidateGrid();
//
//		//	表示設定モードの有効無効を、
//		//	.ini ファイルに保存
//		getCDiagramEditApp()->writeCWndDcdGridEkiJikokuhyouListProp(this);
//	}
//	return (iRv);
//}

// ----------------------------------------------------------------
//	MFC
// ----------------------------------------------------------------
BEGIN_MESSAGE_MAP(CWndDcdGridEkiJikokuhyouList,CWndDcdGridEkiJikokuhyouList::super)
	//{{AFX_MSG_MAP(CWndDcdGridEkiJikokuhyouList)
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KEYUP()
	//ON_COMMAND(ID_EDIT_EkiProp, OnEDITEkiProp)
	//ON_COMMAND(ID_EDIT_EkiInsert, OnEDITEkiInsert)
	//ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	//ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	//ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	//ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	//ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	//ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR, OnUpdateEditClear)
	//ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	//ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	//}}AFX_MSG_MAP
	//ON_COMMAND(ID_EDIT_EKI_INVERT, &CWndDcdGridEkiJikokuhyouList::OnEditEkiInvert)
	//ON_UPDATE_COMMAND_UI(ID_EDIT_EKI_INVERT, &CWndDcdGridEkiJikokuhyouList::OnUpdateEditEkiInvert)
	//ON_UPDATE_COMMAND_UI(ID_EDIT_EkiInsert, &CWndDcdGridEkiJikokuhyouList::OnUpdateEditEkiinsert)
	//ON_UPDATE_COMMAND_UI(ID_EDIT_EkiProp, &CWndDcdGridEkiJikokuhyouList::OnUpdateEditEkiprop)
	//ON_COMMAND(ID_VIEW_DisplaySettingMode, &CWndDcdGridEkiJikokuhyouList::OnViewDisplaySettingMode)
	//ON_UPDATE_COMMAND_UI(ID_VIEW_DisplaySettingMode, &CWndDcdGridEkiJikokuhyouList::OnUpdateViewDisplaySettingMode)
	//ON_COMMAND(ID_Eki_SettingNext, &CWndDcdGridEkiJikokuhyouList::OnEkiSettingNext)
	//ON_UPDATE_COMMAND_UI(ID_Eki_SettingNext, &CWndDcdGridEkiJikokuhyouList::OnUpdateEkiSettingNext)
	//ON_COMMAND(ID_Eki_SettingPrev, &CWndDcdGridEkiJikokuhyouList::OnEkiSettingPrev)
	//ON_UPDATE_COMMAND_UI(ID_Eki_SettingPrev, &CWndDcdGridEkiJikokuhyouList::OnUpdateEkiSettingPrev)
	//ON_COMMAND(ID_Eki_SettingNext2, &CWndDcdGridEkiJikokuhyouList::OnEkiSettingNext2)
	//ON_UPDATE_COMMAND_UI(ID_Eki_SettingNext2, &CWndDcdGridEkiJikokuhyouList::OnUpdateEkiSettingNext2)
	//ON_COMMAND(ID_Eki_SettingPrev2, &CWndDcdGridEkiJikokuhyouList::OnEkiSettingPrev2)
	//ON_UPDATE_COMMAND_UI(ID_Eki_SettingPrev2, &CWndDcdGridEkiJikokuhyouList::OnUpdateEkiSettingPrev2)
	//ON_COMMAND(ID_Eki_SettingNext3, &CWndDcdGridEkiJikokuhyouList::OnEkiSettingNext3)
	//ON_UPDATE_COMMAND_UI(ID_Eki_SettingNext3, &CWndDcdGridEkiJikokuhyouList::OnUpdateEkiSettingNext3)
	ON_COMMAND(ID_EkiJikokuhyouList_OpenEkiJikokuhyou, &CWndDcdGridEkiJikokuhyouList::OnOpenEkiJikokuhyou)
	ON_UPDATE_COMMAND_UI(ID_EkiJikokuhyouList_OpenEkiJikokuhyou, &CWndDcdGridEkiJikokuhyouList::OnUpdateOpenEkiJikokuhyou)
	ON_COMMAND(ID_FILE_EXPORT_ALLEKIJIKOKUHYOUCSV, &CWndDcdGridEkiJikokuhyouList::OnFileExportAllEkiJikokuhyoucsv)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

int CWndDcdGridEkiJikokuhyouList::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (super::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	//OnCreate_Header();
	// --------------------------------
	//	フォーカスセルの初期位置を設定
	// --------------------------------
	getCFocus()->setFocusCell( getCXDcdGrid()->getCell( 0 , 1 ) ) ;	
	
	return 0;
}

void CWndDcdGridEkiJikokuhyouList::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	LogMsg(_T("CWndDcdGridEkiJikokuhyouList::OnKeyDown(%08X,%04X,%08X)") , nChar, nRepCnt, nFlags) ;

	int iRv = 0 ;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************

	//	フォーカスセルが新規アイテム位置にあるときは、
	//	「新規アイテムのプロパティ入力を行い、それを末尾に挿入する」という
	//	動作になります。
	//bool bInsert = false ;
	//CdEkiYColSpec aYColSpec = getYColSpecOfFocus() ;
	//if ( aYColSpec.getColumnType() == CdEkiYColSpec::ColumnType_NewEki )
	//{
	//	bInsert = true ;
	//}

	// ****************************************************************


	//	文字キーが押されていて、ダイアログボックスが開いていない場合は
	//	ダイアログボックスを開きます。
	//if ( CKeyinputSenderToModalDlg::AnyLetterOrDigitKeyIsDown() && 
	//		m_CKeyinputSenderToModalDlg.startSend() >= 0 )
	//{
	//	m_CKeyinputSenderToModalDlg.OnKeyDown( nChar , nRepCnt , nFlags ) ;
	//	//execEkiPropDlg( bInsert , FALSE ) ;
	//	m_CKeyinputSenderToModalDlg.endSend() ;
	//}
	////	すでにダイアログが起動中→ダイアログボックスにメッセージを転送
	//else	
	//{
	//	if ( !m_CKeyinputSenderToModalDlg.OnKeyDown( nChar , nRepCnt , nFlags ) )
	//	{
			CWndDcdGridEkiJikokuhyouList::super::OnKeyDown(nChar, nRepCnt, nFlags);
	//	}
	//}
			
}

void CWndDcdGridEkiJikokuhyouList::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	int iRv = 0 ;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************

	//	フォーカスセルが新規アイテム位置にあるときは、
	//	「新規アイテムのプロパティ入力を行い、それを末尾に挿入する」という
	//	動作になります。
	//bool bInsert = false ;
	//CdEkiYColSpec aYColSpec = getYColSpecOfFocus() ;
	//if ( aYColSpec.getColumnType() == CdEkiYColSpec::ColumnType_NewEki )
	//{
	//	bInsert = true ;
	//}

	// ****************************************************************
	//	コマンドの実行
	// ****************************************************************
	OnEkiJikokuhyouListMovetoEkiJikokuhyou_Process(FALSE);
	//if ( execEkiPropDlg( bInsert , FALSE ) < 0 )
	//{
	//	iRv = -1 ;	//	-1 ;	//	フォーカスセルの位置が不正です。
	//}
	// ****************************************************************

	//CWndDcdGridEkiJikokuhyouList::super::OnLButtonDblClk(nFlags, point);
}

void CWndDcdGridEkiJikokuhyouList::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if ( !m_CKeyinputSenderToModalDlg.OnKeyUp( nChar , nRepCnt , nFlags ) )
	{
		CWndDcdGridEkiJikokuhyouList::super::OnKeyUp(nChar, nRepCnt, nFlags);
	}
}

//void CWndDcdGridEkiJikokuhyouList::OnEDITEkiProp() 
//{
//	OnEDITEkiProp_Process( FALSE );
//}
//void CWndDcdGridEkiJikokuhyouList::OnUpdateEditEkiprop(CCmdUI *pCmdUI)
//{
//	pCmdUI->Enable( OnEDITEkiProp_Process( TRUE ) >= 0 ) ;
//}
//
//
//void CWndDcdGridEkiJikokuhyouList::OnEDITEkiInsert() 
//{
//	OnEDITEkiInsert_Process( FALSE ) ;
//}
//void CWndDcdGridEkiJikokuhyouList::OnUpdateEditEkiinsert(CCmdUI *pCmdUI)
//{
//	pCmdUI->Enable( OnEDITEkiInsert_Process( TRUE ) >= 0 ) ;
//}
//
//
//void CWndDcdGridEkiJikokuhyouList::OnEditClear() 
//{
//	OnEditClear_Process( FALSE ) ;
//}
//
//void CWndDcdGridEkiJikokuhyouList::OnEditCut() 
//{
//	OnEditCut_Process( FALSE ) ;
//}
//
//void CWndDcdGridEkiJikokuhyouList::OnEditCopy() 
//{
//	OnEditCopy_Process( FALSE ) ;
//
//}
//
//void CWndDcdGridEkiJikokuhyouList::OnEditPaste() 
//{
//	OnEditPaste_Process( FALSE ) ;
//	
//}
//
//void CWndDcdGridEkiJikokuhyouList::OnUpdateEditClear(CCmdUI* pCmdUI) 
//{
//	pCmdUI->Enable( OnEditClear_Process( TRUE ) >= 0 ) ;
//}
//
//void CWndDcdGridEkiJikokuhyouList::OnUpdateEditCut(CCmdUI* pCmdUI) 
//{
//	pCmdUI->Enable( OnEditCut_Process( TRUE ) >= 0 ) ;
//}
//
//void CWndDcdGridEkiJikokuhyouList::OnUpdateEditCopy(CCmdUI* pCmdUI) 
//{
//	pCmdUI->Enable( OnEditCopy_Process( TRUE ) >= 0 ) ;
//}
//
//void CWndDcdGridEkiJikokuhyouList::OnUpdateEditPaste(CCmdUI* pCmdUI) 
//{
//	pCmdUI->Enable( OnEditPaste_Process( TRUE ) >= 0 ) ;
//}
//
//
//void CWndDcdGridEkiJikokuhyouList::OnEditEkiInvert()
//{
//	OnEditEkiInvert_Process( FALSE ) ;
//}
//
//void CWndDcdGridEkiJikokuhyouList::OnUpdateEditEkiInvert(CCmdUI *pCmdUI)
//{
//	pCmdUI->Enable( OnEditEkiInvert_Process( TRUE ) >= 0 ) ;
//}



void CWndDcdGridEkiJikokuhyouList::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CMenu	aMenu ;
	aMenu.LoadMenu( IDR_MENU_EKIJIKOKUHYOULIST_CONTEXT ) ;
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

//void CWndDcdGridEkiJikokuhyouList::OnViewDisplaySettingMode()
//{
//	OnViewDisplaySettingMode_Process(FALSE);
//}
//
//void CWndDcdGridEkiJikokuhyouList::OnUpdateViewDisplaySettingMode(CCmdUI* pCmdUI)
//{
//	int iResult = OnViewDisplaySettingMode_Process(TRUE);
//	pCmdUI->Enable(iResult >= 0);
//	pCmdUI->SetCheck(iResult >= 1);
//}
//
//void CWndDcdGridEkiJikokuhyouList::OnEkiSettingNext()
//{
//	OnEkiSettingNext_Process(FALSE,0);
//}
//
//void CWndDcdGridEkiJikokuhyouList::OnUpdateEkiSettingNext(CCmdUI* pCmdUI)
//{
//	int iResult = OnEkiSettingNext_Process(TRUE,0);
//	pCmdUI->Enable(iResult >= 0);
//	pCmdUI->SetCheck(iResult >= 1);
//}
//
//void CWndDcdGridEkiJikokuhyouList::OnEkiSettingPrev()
//{
//	OnEkiSettingPrev_Process(FALSE, 0);
//}
//
//void CWndDcdGridEkiJikokuhyouList::OnUpdateEkiSettingPrev(CCmdUI* pCmdUI)
//{
//	int iResult = OnEkiSettingPrev_Process(TRUE, 0);
//	pCmdUI->Enable(iResult >= 0);
//	pCmdUI->SetCheck(iResult >= 1);
//}
//
//void CWndDcdGridEkiJikokuhyouList::OnEkiSettingNext2()
//{
//	OnEkiSettingNext_Process(FALSE, 1);
//}
//
//void CWndDcdGridEkiJikokuhyouList::OnUpdateEkiSettingNext2(CCmdUI* pCmdUI)
//{
//	int iResult = OnEkiSettingNext_Process(TRUE,1);
//	pCmdUI->Enable(iResult >= 0);
//	pCmdUI->SetCheck(iResult >= 1);
//}
//
//void CWndDcdGridEkiJikokuhyouList::OnEkiSettingPrev2()
//{
//	OnEkiSettingPrev_Process(FALSE, 1);
//}
//
//void CWndDcdGridEkiJikokuhyouList::OnUpdateEkiSettingPrev2(CCmdUI* pCmdUI)
//{
//	int iResult = OnEkiSettingPrev_Process(TRUE, 1);
//	pCmdUI->Enable(iResult >= 0);
//	pCmdUI->SetCheck(iResult >= 1);
//}
//
//void CWndDcdGridEkiJikokuhyouList::OnEkiSettingNext3()
//{
//	OnEkiSettingNext_Process(FALSE, 2);
//}
//
//void CWndDcdGridEkiJikokuhyouList::OnUpdateEkiSettingNext3(CCmdUI* pCmdUI)
//{
//	int iResult = OnEkiSettingNext_Process(TRUE, 2);
//	pCmdUI->Enable(iResult >= 0);
//	pCmdUI->SetCheck(iResult >= 1);
//}
//
void CWndDcdGridEkiJikokuhyouList::OnOpenEkiJikokuhyou()
{
	OnEkiJikokuhyouListMovetoEkiJikokuhyou_Process(FALSE);
}

void CWndDcdGridEkiJikokuhyouList::OnUpdateOpenEkiJikokuhyou(CCmdUI* pCmdUI)
{
	int iResult = OnEkiJikokuhyouListMovetoEkiJikokuhyou_Process(TRUE);
	pCmdUI->Enable(iResult >= 0);
	pCmdUI->SetCheck(iResult >= 1);
}

void CWndDcdGridEkiJikokuhyouList::OnFileExportAllEkiJikokuhyoucsv()
{
	OnFileExportAllEkiJikokuhyouCsv_Process(FALSE);
}

} //namespace ViewEkiJikokuhyou
