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
//	CWndDcdGridEki.cpp
//	$Id: CWndDcdGridEki.cpp 295 2016-06-11 05:14:13Z okm $
// ****************************************************************
*/
#include "stdafx.h"

#include "..¥resource.h"

#include "DcDraw/CDcdTargetGetDC.h"
#include "logmsg/LogMsg.h"
#include "NsOu/OuNew.h"
#include "NsOu/dynamic_castOu.h"

#include "DcdCd¥DcDrawProp¥CdFontProp.h"
#include "DcDraw¥CDcdTarget.h"
#include "DcDraw¥CDcDeviceUnitSizeX.h"
#include "DcDraw¥CDcDeviceUnitSizeY.h"
#include "DcDraw¥CDcdText.h"
#include "DcDraw¥CaDcdTargetItemPosition.h"
#include "DcDraw¥CDcdLine.h"
#include "DcDraw¥CDcdTargetGetDC.h"
#include "DcDraw¥CConverter_Wingdi.h"

#include "..¥entDed¥CentDedRosen.h"
#include "..¥DiagramEdit.h"
#include "..¥CRfEditCmdHolder.h"
#include "..¥DedRosenFileData¥EditCmd¥EditCmd.h"
#include "CDlgEkiProp.h"
#include "CDlgCrossingCheckRule.h"
#include "CWndDcdGridEki.h"
#include <NsMu¥CaMui.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/** 配列 a の要素数を返します。 */
#define arrayof(a) (sizeof(a)/sizeof(a[0]))


namespace ViewEki{
	

using namespace std ;

// ****************************************************************
//	CWndDcdGridEki
// ****************************************************************
// --------------------------------
//@name 下請関数
// --------------------------------
	
CDcdTextbox	CWndDcdGridEki::getCDcdEkiIndex()const
{
	//CdFontProp aCdFontProp( getCDiagramEditDoc()->getCDedRosenFileData()->
	//	getCdDedDispProp().getJikokuhyouFont() ) ;
	//CdFontProp aCdFontProp(CConverter_WinGdi().CdFontPropOf(DEFAULT_GUI_FONT));
	CdFontProp aCdFontProp(9, _T("Meiryo UI"));
	return CDcdTextbox(_T(""),
		aCdFontProp,
		_T("京都"), 1, 2, 2, CdPenProp(),
		CConverter_WinGdi().CdBrushPropOf(WHITE_BRUSH));
};

CDcdTextbox	CWndDcdGridEki::getCDcdEkimei()const
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
	
CDcdTextbox	CWndDcdGridEki::getCDcdEkijikokukeisiki()const
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
	
CDcdTextbox	CWndDcdGridEki::getCDcdEkikibo()const
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

CDcdTextbox	CWndDcdGridEki::getCDcdEkiTrack2Count()const
{
	//CdFontProp aCdFontProp( getCDiagramEditDoc()->getCDedRosenFileData()->
	//	getCdDedDispProp().getJikokuhyouFont() ) ;
	//CdFontProp aCdFontProp(CConverter_WinGdi().CdFontPropOf(DEFAULT_GUI_FONT));
	CdFontProp aCdFontProp(9, _T("Meiryo UI"));
	return CDcdTextbox(_T(""),
		aCdFontProp,
		_T("京都京"), 1, 2, 2, CdPenProp(),
		CConverter_WinGdi().CdBrushPropOf(WHITE_BRUSH));
};

CDcdTextbox	CWndDcdGridEki::getCDcdBrunchLoop()const
{
	//CdFontProp aCdFontProp( getCDiagramEditDoc()->getCDedRosenFileData()->
	//	getCdDedDispProp().getJikokuhyouFont() ) ;
	//CdFontProp aCdFontProp(CConverter_WinGdi().CdFontPropOf(DEFAULT_GUI_FONT));
	CdFontProp aCdFontProp(9, _T("Meiryo UI"));
	return CDcdTextbox(_T(""),
		aCdFontProp,
		_T("京都京都京都京都"), 1, 2, 2, CdPenProp(),
		CConverter_WinGdi().CdBrushPropOf(WHITE_BRUSH));
};
	


CdEkiXColSpecCont CWndDcdGridEki::createXColSpecCont() 
{
	CdEkiXColSpecCont aSpecCont( 
		getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont() ,
		getDisplaySettingMode()) ;
	return aSpecCont ;
}
CdEkiYColSpecCont CWndDcdGridEki::createYColSpecCont() 
{
	CdEkiYColSpecCont aSpecCont( 
		getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont() ) ;
	return aSpecCont ;
}	
CdEkiXColSpec CWndDcdGridEki::getXColSpecOfFocus() 
{
	CdEkiXColSpec aSpec ;
	CdDcdPosXy aPos = getCFocus()->getFocusCellColumnNumber() ;
	if ( aPos != getCFocus()->ColumnNumberPosXy_NULL() )
	{
		CdEkiXColSpecCont aSpecCont( 
			getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont(),
			getDisplaySettingMode()) ;
		aSpec = aSpecCont.ColumnNumberToSpec( aPos.getX() ) ;
	}
	return aSpec ;
}	
CdEkiYColSpec CWndDcdGridEki::getYColSpecOfFocus() 
{
	CdEkiYColSpec aSpec ;
	CdDcdPosXy aPos = getCFocus()->getFocusCellColumnNumber() ;
	if ( aPos != getCFocus()->ColumnNumberPosXy_NULL() )
	{
		CdEkiYColSpecCont aSpecCont( 
			getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont() ) ;
		aSpec = aSpecCont.ColumnNumberToSpec( aPos.getY() ) ;
	}
	return aSpec ;
}	
	
	
	
bool CWndDcdGridEki::
createCmd( ECreateCmd eCreateCmd , Ou<DedRosenFileData::EditCmd::CRfEditCmd_Eki>* ppCmd )
{
	bool bRv = false ;
	Ou<DedRosenFileData::EditCmd::CRfEditCmd_Eki> pCmd ;

	CdEkiYColSpecCont aCdYColSpecCont = createYColSpecCont() ;
	CdEkiYColSpec  aCdYColSpecOfFocus = getYColSpecOfFocus() ;

	// ********************************
	//	ECreateCmd_NewItem
	//　新規アイテムを対象としたコマンドを生成します。
	// ********************************
	if ( eCreateCmd == ECreateCmd_NewItem )
	{
		//ビュー上で複数選択がOFF
		if ( getCSelect()->getSelectedCellCount() == 0 )
		{
			//	新規アイテムの、初期オブジェクト
			//	駅Indexが0の場合は、駅時刻形式を「上り着時刻」とします。
			CentDedEki aNewEki ;
			if ( aCdYColSpecOfFocus.getEkiIndex() == 0 )
			{
				aNewEki.setEkijikokukeisiki(CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku);
			}


			//	ビュー上で複数選択がOFF・フォーカスセルが既存アイテム上にある場合: 
			//
			//- m_iDiaIndex = フォーカスセルのアイテムIndex、m_iIndexSize = 0
			//- m_CentDedEkiCont = 新規作成時のアイテムの既定値
			//- CaMuiSelect = 当該アイテムを選択。
			if ( aCdYColSpecOfFocus.getColumnType() == CdEkiYColSpec::ColumnType_Eki )
			{
				bRv = true ;
				if ( ppCmd != NULL )
				{
					pCmd = OuNew<DedRosenFileData::EditCmd::CRfEditCmd_Eki>( 
						new CRfEditCmd_Eki( 
							*getCDiagramEditDoc()->getCDedRosenFileData() , 
							aCdYColSpecOfFocus.getEkiIndex() , 
							0 , m_bAdjustByEkijikokukeisiki ) ) ;
					pCmd->getCaMuiSelect()->insert( aNewEki , INT_MAX ) ;
					pCmd->getCaMuiSelect()->setSelectAll( true ) ;
				}
			}

			//　ビュー上で複数選択がOFF・フォーカスセルが新規アイテム位置にある場合:
			//- m_iDiaIndex = 末尾アイテムIndex+1、m_iIndexSize = 0
			//- m_CentDedEkiCont = 新規作成時のアイテムの既定値
			//- CaMuiSelect = 当該アイテムを選択。
			else if ( aCdYColSpecOfFocus.getColumnType() == CdEkiYColSpec::ColumnType_NewEki )
			{
				bRv = true ;
				if ( ppCmd != NULL )
				{
					pCmd = OuNew<DedRosenFileData::EditCmd::CRfEditCmd_Eki>( 
						new CRfEditCmd_Eki( 
							*getCDiagramEditDoc()->getCDedRosenFileData() , 
							aCdYColSpecOfFocus.getEkiIndex() , 
							0 , m_bAdjustByEkijikokukeisiki ) ) ;
					pCmd->getCaMuiSelect()->insert( aNewEki , INT_MAX ) ;
					pCmd->getCaMuiSelect()->setSelectAll( true ) ;
				}
			}
		}
		// 　ビュー上で複数選択ON:
		//	 - NULLを返します([14/05/18]旧:複数選択OFFの場合と同じ動作)

	}
	// ********************************
	//	ECreateCmd_Focus
	//　フォーカスセル上の1列車を対象としたコマンドを生成します。
	// ********************************
	if ( eCreateCmd == ECreateCmd_Focus )
	{
		//ビュー上で複数選択がOFF
		if ( getCSelect()->getSelectedCellCount() == 0 )
		{
			//ビュー上で複数選択がOFF・フォーカスセルが既存アイテム上にある場合: 
			//- m_iDiaIndex = フォーカスセルのアイテムIndex、m_iIndexSize = 1
			//- m_CentDedRessyaCont = フォーカスセル上のアイテム1個のコピー
			//- m_CaMuiSelect = フォーカスセル上のアイテムを選択。
			if ( aCdYColSpecOfFocus.getColumnType() == CdEkiYColSpec::ColumnType_Eki )
			{
				bRv = true ;
				if ( ppCmd != NULL )
				{
					pCmd = OuNew<DedRosenFileData::EditCmd::CRfEditCmd_Eki>( 
						new CRfEditCmd_Eki( 
							*getCDiagramEditDoc()->getCDedRosenFileData() , 
							aCdYColSpecOfFocus.getEkiIndex() , 
							1 , m_bAdjustByEkijikokukeisiki ) ) ;
					pCmd->getCaMuiSelect()->setSelectAll( true ) ;
				}
			}

			//ビュー上で複数選択がOFF・フォーカスセルが新規アイテム位置にある場合: 
			//- NULLを返します。
		}
		//ビュー上で複数選択ON
		// - NULLを返します([14/05/18]旧:複数選択OFFの場合と同じ動作)

	}
	// ********************************
	//	ECreateCmd_Sequence
	//　既存の単数または連続して複数選択されているアイテムを対象とした
	//	コマンドを生成します。
	// ********************************
	if (eCreateCmd == ECreateCmd_Sequence)
	{
		//	ビュー上で複数選択がOFF・フォーカスセルが既存アイテム上にある場合: 
		//- m_iDiaIndex = フォーカスセルのアイテムIndex、m_iIndexSize = 1
		//- m_CentDedRessyaCont = フォーカスセルのあるアイテム1個のコピー
		//- CaMuiSelect = 当該列車を選択。
		if (getCSelect()->getSelectedCellCount() == 0
			&& aCdYColSpecOfFocus.getColumnType() == CdEkiYColSpec::ColumnType_Eki)
		{
			bRv = true;
			if (ppCmd != NULL)
			{
				pCmd = OuNew<DedRosenFileData::EditCmd::CRfEditCmd_Eki>(
					new CRfEditCmd_Eki(
						*getCDiagramEditDoc()->getCDedRosenFileData(),
						aCdYColSpecOfFocus.getEkiIndex(),
						1, m_bAdjustByEkijikokukeisiki));
				pCmd->getCaMuiSelect()->setSelectAll(true);
			}
		}

		//	ビュー上で複数選択がOFF・フォーカスセルが新規アイテム位置にある場合: 
		//- NULLを返します。

		//	ビュー上で複数選択ON
		//
		//- m_iDiaIndex = 選択されているアイテムの先頭index
		//- m_iIndexSize = 選択されているアイテムの末尾index-先頭index+1
		//- m_CentDedRessyaCont = 選択されているアイテムの先頭indexから
		//	末尾indexまでのアイテムのコピー
		//- CaMuiSelec = m_CentDedRessyaCont。
		//
		//(A)の位置で処理します。
	}

	// ********************************
	//	ECreateCmd_Select
	//　既存の単数または複数選択されている列車を対象とした
	//	コマンドを生成します。
	// ********************************
	if ( eCreateCmd == ECreateCmd_Select )
	{
		//ビュー上で複数選択がOFF・フォーカスセルが既存アイテム上にある場合: 
		//- m_iDiaIndex = フォーカスセルのアイテムIndex、m_iIndexSize = 1
		//- m_CentDedRessyaCont = フォーカスセルのあるアイテム1個のコピー
		//- CaMuiSelect = 当該列車を選択。
		if ( getCSelect()->getSelectedCellCount() == 0 
			&& aCdYColSpecOfFocus.getColumnType() == CdEkiYColSpec::ColumnType_Eki )
		{
			bRv = true ;
			if ( ppCmd != NULL )
			{
				pCmd = OuNew<DedRosenFileData::EditCmd::CRfEditCmd_Eki>( 
					new CRfEditCmd_Eki( 
						*getCDiagramEditDoc()->getCDedRosenFileData() , 
						aCdYColSpecOfFocus.getEkiIndex() , 
						1 , m_bAdjustByEkijikokukeisiki ) ) ;
				pCmd->getCaMuiSelect()->setSelectAll( true ) ;
			}
		}

		//　時刻表ビュー上で複数選択がOFF・フォーカスセルが新規列車位置にある場合: 
		// - NULLを返します。

		//　時刻表ビュー上で複数選択ON
		// - m_iDiaIndex = 選択されている列車の先頭index
		// - m_iIndexSize = 選択されている列車の末尾index-先頭index+1
		// - m_CentDedRessyaCont = 選択されている列車の先頭indexから
		//  末尾indexまでの列車のコピー
		// - CaMuiSelect は、フォーカスセルに合わせて列車を選択。
		//
		//(A)の位置で処理します。
	}


	// ********************************
	//		ECreateCmd_All ,
	//　全列車を対象としたコマンドを生成します。
	// ********************************
	if ( eCreateCmd == ECreateCmd_All )
	{
		// ビュー上で複数選択がOFF・フォーカスセルが既存アイテム上にある場合: 
		//
		//- m_iDiaIndex = 0、m_iIndexSize = アイテムの数
		//- m_CentDedRessyaCont = 全アイテムのコピー
		//- m_CaMuiSelect は、全アイテムを選択。
		//
		// ビュー上で複数選択がOFF・フォーカスセルが新規アイテム位置にある場合: 
		//
		//- m_iDiaIndex = 0、m_iIndexSize = アイテムの数
		//- m_CentDedRessyaCont = 全アイテムのコピー
		//- CaMuiSelect は、全アイテムを選択。
		if ( getCSelect()->getSelectedCellCount() == 0 
			&& ( aCdYColSpecOfFocus.getColumnType() == CdEkiYColSpec::ColumnType_Eki 
			|| aCdYColSpecOfFocus.getColumnType() == CdEkiYColSpec::ColumnType_NewEki ) )
		{
			bRv = true ;
			if ( ppCmd != NULL )
			{
				pCmd = OuNew<DedRosenFileData::EditCmd::CRfEditCmd_Eki>( 
					new CRfEditCmd_Eki( 
						*getCDiagramEditDoc()->getCDedRosenFileData() , 
						0 , 
						aCdYColSpecCont.getEkiCount() ,
						m_bAdjustByEkijikokukeisiki ) ) ;
				pCmd->getCaMuiSelect()->setSelectAll( true ) ;
			}
		}

		// ビュー上で複数選択ON
		//
		//- m_iDiaIndex = 選択されているアイテムの先頭index
		//- m_iIndexSize = 選択されているアイテムの末尾index-先頭index+1
		//- m_CentDedRessyaCont = 選択されているアイテムの先頭indexから
		//末尾indexまでのアイテムのコピー
		//- m_CaMuiSelect は、セルの選択に合わせてアイテムを選択。
		//
		//(A)の位置で処理します。
	}

	// ********************************
	//	(A)ECreateCmd_Sequence で
	//　複数選択されている列車を対象とした
	//	コマンドを生成します。
	// ********************************
	if (eCreateCmd == ECreateCmd_Sequence)
	{
		if (getCSelect()->getSelectedCellCount() > 0)
		{
			int iSelectIndex = -1;
			int iSelectSize = 1;
			bool bSequential = false;
			for (int iColumnNumber = 0; iColumnNumber < getCXDcdGrid()->getYColumnCount(); iColumnNumber++)
			{
				CdEkiYColSpec aCdYColSpec = aCdYColSpecCont.ColumnNumberToSpec(iColumnNumber);
				if (getCSelect()->getYColumnNumberSelected(iColumnNumber))
				{
					if (aCdYColSpec.getColumnType() == CdEkiYColSpec::ColumnType_Eki)
					{
						if (iSelectIndex < 0)
						{
							iSelectIndex = aCdYColSpec.getEkiIndex();
							bSequential = true;
						}
						else if (!bSequential)
						{
							iSelectIndex = -1;
							break;
						}
					}
				}
				else if (bSequential)
				{
					if (aCdYColSpec.getColumnType() == CdEkiYColSpec::ColumnType_Eki)
					{
						iSelectSize = aCdYColSpec.getEkiIndex() - iSelectIndex;
					}
					else
					{
						iSelectSize = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont()->size()
							- iSelectIndex;
					}
					bSequential = false;
				}
			}

			if (iSelectIndex >= 0)
			{
				bRv = true;
				if (ppCmd != NULL)
				{
					//	コマンドオブジェクト内に、選択されている駅の先頭から末尾までの
					//	駅を格納します
					pCmd = OuNew<DedRosenFileData::EditCmd::CRfEditCmd_Eki>(
						new CRfEditCmd_Eki(
							*getCDiagramEditDoc()->getCDedRosenFileData(),
							iSelectIndex,
							iSelectSize,
							m_bAdjustByEkijikokukeisiki));

					//	コマンドオブジェクトの
					//	m_CentDedRessyaContSrc  内の列車を全選択します。
					pCmd->getCaMuiSelect()->setSelectAll(true);
				}
			}
		}
	}

	// ********************************
	//	(A)ECreateCmd_Select・ECreateCmd_All で
	//　複数選択されている列車を対象とした
	//	コマンドを生成します。
	// ********************************
	if ( eCreateCmd == ECreateCmd_Select 
		|| eCreateCmd == ECreateCmd_All )
	{
		if ( getCSelect()->getSelectedCellCount() > 0 )
		{
			//	選択されているアイテムのIndexを取得
			deque<int> contiEkiIndex ;
			for ( int iColumnNumber = 0 ; iColumnNumber < getCXDcdGrid()->getYColumnCount() ;iColumnNumber ++ )
			{
				if ( getCSelect()->getYColumnNumberSelected( iColumnNumber ) )
				{
					CdEkiYColSpec aCdYColSpec = aCdYColSpecCont.ColumnNumberToSpec( iColumnNumber ) ;
					if ( aCdYColSpec.getColumnType() == CdEkiYColSpec::ColumnType_Eki )
					{
						contiEkiIndex.push_back( aCdYColSpec.getEkiIndex() ) ;
					}
				}
			}
			//contiEkiIndex = 列の複数選択が実施されている場合は、
			//	選択されている駅Indexが格納されます。
			//	そうでない場合は、空です。

			if ( contiEkiIndex.size() > 1 )
			{
				bRv = true ;
				if ( ppCmd != NULL )
				{
					//	コマンドオブジェクト内に、選択されている駅の先頭から末尾までの
					//	駅を格納します(先頭・末尾以外には、選択されていない駅が
					//	含まれている場合もあります)
					pCmd = OuNew<DedRosenFileData::EditCmd::CRfEditCmd_Eki>( 
						new CRfEditCmd_Eki( 
							*getCDiagramEditDoc()->getCDedRosenFileData() ,
							contiEkiIndex.front() , 
							contiEkiIndex.back() - contiEkiIndex.front() + 1 ,
							m_bAdjustByEkijikokukeisiki ) ) ;

					//	コマンドオブジェクトの
					//	m_CentDedRessyaContSrc  内の列車を選択します。
					pCmd->getCaMuiSelect()->setSelectAll( false ) ;
					for ( int i = 0 ; i < (int)contiEkiIndex.size() ; i ++ )
					{
						pCmd->getCaMuiSelect()->setSelect( contiEkiIndex[i] - contiEkiIndex.front()  , true ) ;
					}
				}
			}
		}
	}
	// ================================
	if ( ppCmd != NULL && pCmd != NULL )
	{
		*ppCmd = pCmd ;
	}
	return bRv ;
}
	// --------------------------------
	//@name OnUpdate の下請関数
	// --------------------------------

/**
	CentDedEki::EEkijikokukeisiki と、文字列リソースIDの対応表
	17.4.14 下り発着・上り発着を追加_by_d_mania
*/
struct {
	CentDedEki::EEkijikokukeisiki	m_eValue ;
	int m_iId ;
}	nameEEkijikokukeisiki[] = {
	{ CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsu ,IDS_WORD_Jikokukeisiki_Hatsu } ,
	{ CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ,IDS_WORD_Jikokukeisiki_Hatsuchaku } ,
	{ CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ,IDS_WORD_Jikokukeisiki_KudariChaku } ,
	{ CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ,IDS_WORD_Jikokukeisiki_NoboriChaku } ,
	{ CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku ,IDS_WORD_Jikokukeisiki_KudariHatsuchaku } ,
	{ CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku ,IDS_WORD_Jikokukeisiki_NoboriHatsuchaku } ,
};

/**
	CentDedEki::EEkikibo と、文字列リソースIDの対応表
*/
struct {
	CentDedEki::EEkikibo	m_eValue ;
	int m_iId ;
}	nameEkikibo[] = {
	{ CentDedEki::EEkikibo::Ekikibo_Ippan , IDS_WORD_Ekikibo_Ippan } ,
	{ CentDedEki::EEkikibo::Ekikibo_Syuyou , IDS_WORD_Ekikibo_Syuyou } ,
};


void CWndDcdGridEki::OnUpdate_setCentDedEki_To_Column( 
	int iYColumnNumber , const CentDedEki& aCentDedEki, const CentDedEki& aCentDedEkiNext)
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
	CdEkiXColSpecCont aCdEkiXColSpecCont = createXColSpecCont();
	{
		//	駅Index列の DcDraw の属性を設定
		Ou<CDcdTextbox>	pCDcdTextbox =
			(getCXDcdGrid()->getCell(
				aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_EkiIndex), iYColumnNumber)->getIfDcDraw());
		*pCDcdTextbox = this->getCDcdEkiIndex();
	}
	{
		//	駅名列の DcDraw の属性を設定
		Ou<CDcdTextbox>	pCDcdTextbox = 
			(getCXDcdGrid()->getCell(
				aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_Ekimei), iYColumnNumber )->getIfDcDraw());
		*pCDcdTextbox = this->getCDcdEkimei() ;
	}
	{
		//	駅時刻形式の DcDraw の属性を設定
		Ou<CDcdTextbox>	pCDcdTextbox = 
			(getCXDcdGrid()->getCell( 
				aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_Ekijikokukeisiki), iYColumnNumber )->getIfDcDraw());
		*pCDcdTextbox = this->getCDcdEkijikokukeisiki() ;
	}
	{
		//	駅規模
		Ou<CDcdTextbox>	pCDcdTextbox = 
			(getCXDcdGrid()->getCell( 
				aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_Ekikibo), iYColumnNumber )->getIfDcDraw());
		*pCDcdTextbox = this->getCDcdEkikibo() ;
	}
	{
		//	駅番線数
		Ou<CDcdTextbox>	pCDcdTextbox =
			(getCXDcdGrid()->getCell(
				aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_EkiTrack2Count), iYColumnNumber)->getIfDcDraw());
		*pCDcdTextbox = this->getCDcdEkiTrack2Count();
	}
	if (getDisplaySettingMode())
	{
		{
			//	前後作業欄
			Ou<CDcdTextbox>	pCDcdTextbox =
				(getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_OperationOriginDownBeforeUpAfter), iYColumnNumber)->getIfDcDraw());
			Ou<CDcdTextbox>	pCDcdTextbox2 =
				(getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_OperationOrigin), iYColumnNumber)->getIfDcDraw());
			Ou<CDcdTextbox>	pCDcdTextbox3 =
				(getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_OperationOriginDownAfterUpBefore), iYColumnNumber)->getIfDcDraw());
			
			Ou<CDcdTextbox>	pCDcdTextbox4 =
				(getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_OperationTerminalDownBeforeUpAfter), iYColumnNumber)->getIfDcDraw());
			Ou<CDcdTextbox>	pCDcdTextbox5 =
				(getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_OperationTerminal), iYColumnNumber)->getIfDcDraw());
			Ou<CDcdTextbox>	pCDcdTextbox6 =
				(getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_OperationTerminalDownAfterUpBefore), iYColumnNumber)->getIfDcDraw());
			
			*pCDcdTextbox = this->getCDcdEkikibo();
			*pCDcdTextbox2 = this->getCDcdEkikibo();
			*pCDcdTextbox3 = this->getCDcdEkikibo();
			*pCDcdTextbox4 = this->getCDcdEkikibo();
			*pCDcdTextbox5 = this->getCDcdEkikibo();
			*pCDcdTextbox6 = this->getCDcdEkikibo();
		}
		{
			//	番線表示省略設定
			Ou<CDcdTextbox>	pCDcdTextbox =
				(getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_TrackOmit), iYColumnNumber)->getIfDcDraw());
			*pCDcdTextbox = this->getCDcdEkikibo();
		}
		{
			//	下りカスタマイズ時刻表
			Ou<CDcdTextbox>	pCDcdTextbox =
				(getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_ChakuJikokuDisplayKudari), iYColumnNumber)->getIfDcDraw());
			Ou<CDcdTextbox>	pCDcdTextbox2 =
				(getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_TrackDisplayKudari), iYColumnNumber)->getIfDcDraw());
			Ou<CDcdTextbox>	pCDcdTextbox3 =
				(getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_HatsuJikokuDisplayKudari), iYColumnNumber)->getIfDcDraw());
			Ou<CDcdTextbox>	pCDcdTextbox4 =
				(getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_RessyabangouDisplayKudari), iYColumnNumber)->getIfDcDraw());
			Ou<CDcdTextbox>	pCDcdTextbox5 =
				(getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_OperationNumberDisplayKudari), iYColumnNumber)->getIfDcDraw());
			Ou<CDcdTextbox>	pCDcdTextbox10 =
				(getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_OperationNumberDisplayRowsKudari), iYColumnNumber)->getIfDcDraw());
			Ou<CDcdTextbox>	pCDcdTextbox6 =
				(getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_RessyaSyubetsuDisplayKudari), iYColumnNumber)->getIfDcDraw());
			Ou<CDcdTextbox>	pCDcdTextbox7 =
				(getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_RessyameiDisplayKudari), iYColumnNumber)->getIfDcDraw());
			Ou<CDcdTextbox>	pCDcdTextbox8 =
				(getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_OuterSihatsuDisplayKudari), iYColumnNumber)->getIfDcDraw());
			Ou<CDcdTextbox>	pCDcdTextbox9 =
				(getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_OuterShuchakuDisplayKudari), iYColumnNumber)->getIfDcDraw());
			*pCDcdTextbox = this->getCDcdEkikibo();
			*pCDcdTextbox2 = this->getCDcdEkikibo();
			*pCDcdTextbox3 = this->getCDcdEkikibo();
			*pCDcdTextbox4 = this->getCDcdEkikibo();
			*pCDcdTextbox5 = this->getCDcdEkikibo();
			*pCDcdTextbox6 = this->getCDcdEkikibo();
			*pCDcdTextbox7 = this->getCDcdEkikibo();
			*pCDcdTextbox8 = this->getCDcdEkikibo();
			*pCDcdTextbox9 = this->getCDcdEkikibo();
			*pCDcdTextbox10 = this->getCDcdEkikibo();
		}
		{
			//	上りカスタマイズ時刻表
			Ou<CDcdTextbox>	pCDcdTextbox =
				(getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_ChakuJikokuDisplayNobori), iYColumnNumber)->getIfDcDraw());
			Ou<CDcdTextbox>	pCDcdTextbox2 =
				(getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_TrackDisplayNobori), iYColumnNumber)->getIfDcDraw());
			Ou<CDcdTextbox>	pCDcdTextbox3 =
				(getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_HatsuJikokuDisplayNobori), iYColumnNumber)->getIfDcDraw());
			Ou<CDcdTextbox>	pCDcdTextbox4 =
				(getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_RessyabangouDisplayNobori), iYColumnNumber)->getIfDcDraw());
			Ou<CDcdTextbox>	pCDcdTextbox5 =
				(getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_OperationNumberDisplayNobori), iYColumnNumber)->getIfDcDraw());
			Ou<CDcdTextbox>	pCDcdTextbox10 =
				(getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_OperationNumberDisplayRowsNobori), iYColumnNumber)->getIfDcDraw());
			Ou<CDcdTextbox>	pCDcdTextbox6 =
				(getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_RessyaSyubetsuDisplayNobori), iYColumnNumber)->getIfDcDraw());
			Ou<CDcdTextbox>	pCDcdTextbox7 =
				(getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_RessyameiDisplayNobori), iYColumnNumber)->getIfDcDraw());
			Ou<CDcdTextbox>	pCDcdTextbox8 =
				(getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_OuterSihatsuDisplayNobori), iYColumnNumber)->getIfDcDraw());
			Ou<CDcdTextbox>	pCDcdTextbox9 =
				(getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_OuterShuchakuDisplayNobori), iYColumnNumber)->getIfDcDraw());
			*pCDcdTextbox = this->getCDcdEkikibo();
			*pCDcdTextbox2 = this->getCDcdEkikibo();
			*pCDcdTextbox3 = this->getCDcdEkikibo();
			*pCDcdTextbox4 = this->getCDcdEkikibo();
			*pCDcdTextbox5 = this->getCDcdEkikibo();
			*pCDcdTextbox6 = this->getCDcdEkikibo();
			*pCDcdTextbox7 = this->getCDcdEkikibo();
			*pCDcdTextbox8 = this->getCDcdEkikibo();
			*pCDcdTextbox9 = this->getCDcdEkikibo();
			*pCDcdTextbox10 = this->getCDcdEkikibo();
		}
		{
			//	在線表表示設定
			Ou<CDcdTextbox>	pCDcdTextbox =
				(getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_DiagramTrackDisplay), iYColumnNumber)->getIfDcDraw());
			*pCDcdTextbox = this->getCDcdEkikibo();
		}
		{
			//	ダイヤグラム列車情報表示
			Ou<CDcdTextbox>	pCDcdTextbox =
				(getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_DiagramRessyajouhouHyoujiKudari), iYColumnNumber)->getIfDcDraw());
			Ou<CDcdTextbox>	pCDcdTextbox2 =
				(getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_DiagramRessyajouhouHyoujiNobori), iYColumnNumber)->getIfDcDraw());
			*pCDcdTextbox = this->getCDcdEkikibo();
			*pCDcdTextbox2 = this->getCDcdEkikibo();
		}
		{
			//	この駅から次の駅までの距離
			Ou<CDcdTextbox>	pCDcdTextbox =
				(getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_NextEkiDistance), iYColumnNumber)->getIfDcDraw());
			*pCDcdTextbox = this->getCDcdEkikibo();
		}
		{
			//	この駅から次の駅までの背景色設定
			Ou<CDcdTextbox>	pCDcdTextbox =
				(getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_DiagramColorNextEki), iYColumnNumber)->getIfDcDraw());
			*pCDcdTextbox = this->getCDcdEkikibo();
		}
		{
			//	箱ダイヤで表示するか否か
			Ou<CDcdTextbox>	pCDcdTextbox =
				(getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_OperationTableDisplayJikoku), iYColumnNumber)->getIfDcDraw());
			*pCDcdTextbox = this->getCDcdEkikibo();
		}
	}
	else
	{
		{
			//	分岐駅設定
			Ou<CDcdTextbox>	pCDcdTextbox =
				(getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_EkiBrunch), iYColumnNumber)->getIfDcDraw());
			*pCDcdTextbox = this->getCDcdBrunchLoop();
		}
		{
			//	環状線設定
			Ou<CDcdTextbox>	pCDcdTextbox =
				(getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_EkiLoop), iYColumnNumber)->getIfDcDraw());
			*pCDcdTextbox = this->getCDcdBrunchLoop();
		}
	}
	
	
	// --------------------------------
	//	セルのテキストを設定
	// --------------------------------
	//	駅Index
	{
		if (!bIsNull)
		{
			Ou<CDcdTextbox>(getCXDcdGrid()
				->getCell(aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_EkiIndex), 
					iYColumnNumber)->getIfDcDraw())
				->setText(to_tstring(iYColumnNumber - 1));
		}
	}
	//	駅名
	{
		Ou<CDcdTextbox>(getCXDcdGrid()
			->getCell(aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_Ekimei),
				iYColumnNumber )->getIfDcDraw())
				->setText( aCentDedEki.getEkimei() )  ;	
	}
	//	駅時刻形式
	{
		tstring	strEkijikokukeisiki ;
		if ( !bIsNull )
		{
			int idx ;	
			for ( idx = 0 ; 
				idx < arrayof( nameEEkijikokukeisiki ) ; idx ++ )
			{
				if ( nameEEkijikokukeisiki[idx].m_eValue 
					== aCentDedEki.getEkijikokukeisiki() )
				{
					CString	strLs ;
					strLs.LoadString( nameEEkijikokukeisiki[idx].m_iId ) ;
					strEkijikokukeisiki = (LPCTSTR)strLs ;
					break ;
				}
			}
		}
		Ou<CDcdTextbox>(getCXDcdGrid()
			->getCell(aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_Ekijikokukeisiki),
				iYColumnNumber )->getIfDcDraw())->
				setText( strEkijikokukeisiki )  ;	
	}
	//	駅規模
	{
		tstring	strEkikibo ;
		if ( !bIsNull ){
			int idx ;	
			for ( idx = 0 ; idx < arrayof( nameEkikibo ) ;	idx ++ ){
				if ( nameEkikibo[idx].m_eValue == 
						aCentDedEki.getEkikibo() )
				{
					CString	strLs ;
					strLs.LoadString( nameEkikibo[idx].m_iId ) ;
					strEkikibo = (LPCTSTR)strLs ;
					break ;
				}
			}
		}
		Ou<CDcdTextbox>(getCXDcdGrid()->
			getCell(aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_Ekikibo),
				iYColumnNumber )->getIfDcDraw())
				->setText( strEkikibo )  ;	
	}
	//	駅番線数
	{
		if (!bIsNull)
		{
			Ou<CDcdTextbox>(getCXDcdGrid()
				->getCell(aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_EkiTrack2Count),
					iYColumnNumber)->getIfDcDraw())
				->setText(to_tstring(aCentDedEki.getEkiTrack2Cont()->size()));
		}
	}
	if (getDisplaySettingMode())
	{
		//起点側下り増結上り解結作業欄
		{
			tstring strText = _T("");
			if (!bIsNull &&
				aCentDedEki.getJikokuhyouOperationOrigin() > 0)
			{
				switch (aCentDedEki.getJikokuhyouOperationOriginDownBeforeUpAfter()) {
				case false:
					strText = _T(""); break;
				case true:
					strText = _T("増解"); break;
				}
			}
			Ou<CDcdTextbox>(getCXDcdGrid()->
				getCell(aCdEkiXColSpecCont.ColumnNumberFromSpec(
					CdEkiXColSpec::EColumnType::ColumnType_OperationOriginDownBeforeUpAfter), iYColumnNumber)->getIfDcDraw())
				->setText(strText);
		}
		//前後作業欄
		{
			tstring strText = _T("");
			if (!bIsNull) 
			{
				switch (aCentDedEki.getJikokuhyouOperationOrigin()) {
				case 0:
					strText = _T("無し"); break;
				case 1:
					strText = _T("1作業"); break;
				case 2:
					strText = _T("2作業"); break;
				case 3:
					strText = _T("3作業"); break;
				}
			}
			Ou<CDcdTextbox>(getCXDcdGrid()->
				getCell(aCdEkiXColSpecCont.ColumnNumberFromSpec(
					CdEkiXColSpec::EColumnType::ColumnType_OperationOrigin), iYColumnNumber)->getIfDcDraw())
				->setText(strText);
		}
		//起点側下り解結上り増結作業欄
		{
			tstring strText = _T("");
			if (!bIsNull &&
				aCentDedEki.getJikokuhyouOperationOrigin() > 0)
			{
				switch (aCentDedEki.getJikokuhyouOperationOriginDownAfterUpBefore()) {
				case false:
					strText = _T(""); break;
				case true:
					strText = _T("解増"); break;
				}
			}
			Ou<CDcdTextbox>(getCXDcdGrid()->
				getCell(aCdEkiXColSpecCont.ColumnNumberFromSpec(
					CdEkiXColSpec::EColumnType::ColumnType_OperationOriginDownAfterUpBefore), iYColumnNumber)->getIfDcDraw())
				->setText(strText);
		}

		//終点側下り増結上り解結作業欄
		{
			tstring strText = _T("");
			if (!bIsNull &&
				aCentDedEki.getJikokuhyouOperationTerminal() > 0)
			{
				switch (aCentDedEki.getJikokuhyouOperationTerminalDownBeforeUpAfter()) {
				case false:
					strText = _T(""); break;
				case true:
					strText = _T("増解"); break;
				}
			}
			Ou<CDcdTextbox>(getCXDcdGrid()->
				getCell(aCdEkiXColSpecCont.ColumnNumberFromSpec(
					CdEkiXColSpec::EColumnType::ColumnType_OperationTerminalDownBeforeUpAfter), iYColumnNumber)->getIfDcDraw())
				->setText(strText);
		}
		//前後作業欄
		{
			tstring strText = _T("");
			if (!bIsNull) 
			{
				switch (aCentDedEki.getJikokuhyouOperationTerminal()) {
				case 0:
					strText = _T("無し"); break;
				case 1:
					strText = _T("1作業"); break;
				case 2:
					strText = _T("2作業"); break;
				case 3:
					strText = _T("3作業"); break;
				}
			}
			Ou<CDcdTextbox>(getCXDcdGrid()->
				getCell(aCdEkiXColSpecCont.ColumnNumberFromSpec(
					CdEkiXColSpec::EColumnType::ColumnType_OperationTerminal), iYColumnNumber)->getIfDcDraw())
				->setText(strText);
		}
		//終点側下り解結上り増結作業欄
		{
			tstring strText = _T("");
			if (!bIsNull &&
				aCentDedEki.getJikokuhyouOperationTerminal() > 0)
			{
				switch (aCentDedEki.getJikokuhyouOperationTerminalDownAfterUpBefore()) {
				case false:
					strText = _T(""); break;
				case true:
					strText = _T("解増"); break;
				}
			}
			Ou<CDcdTextbox>(getCXDcdGrid()->
				getCell(aCdEkiXColSpecCont.ColumnNumberFromSpec(
					CdEkiXColSpec::EColumnType::ColumnType_OperationTerminalDownAfterUpBefore), iYColumnNumber)->getIfDcDraw())
				->setText(strText);
		}

		//番線表示省略設定
		{
			tstring strText = _T("");
			if (!bIsNull) {
				if (aCentDedEki.getJikokuhyouTrackOmit())
				{
					strText = _T("省略");
				}
				else
				{
					strText = _T("表示");
				}
			}
			Ou<CDcdTextbox>(getCXDcdGrid()->
				getCell(aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_TrackOmit), iYColumnNumber)->getIfDcDraw())
				->setText(strText);
		}

		//下りカスタマイズ時刻表(着時刻)
		{
			tstring strText = _T("");
			if (!bIsNull) {
				//if (aCentDedEki.getJikokuhyouChakuJikokuDisplayKudari())
				//{
				//	strText = _T("表示有り");
				//}
				//else
				//{
				//	strText = _T("表示無し");
				//}
				if (aCentDedEki.getJikokuhyouChakuJikokuDisplayKudari())
				{
					strText = _T("着時刻");
				}
				else
				{
					strText = _T("");
				}
			}
			Ou<CDcdTextbox>(getCXDcdGrid()->
				getCell(aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_ChakuJikokuDisplayKudari), iYColumnNumber)->getIfDcDraw())
				->setText(strText);
		}
		//下りカスタマイズ時刻表(番線)
		{
			tstring strText = _T("");
			if (!bIsNull) {
				//if (aCentDedEki.getJikokuhyouTrackDisplayKudari())
				//{
				//	strText = _T("表示有り");
				//}
				//else
				//{
				//	strText = _T("表示無し");
				//}
				if (aCentDedEki.getJikokuhyouTrackDisplayKudari())
				{
					strText = _T("番線");
				}
				else
				{
					strText = _T("");
				}
			}
			Ou<CDcdTextbox>(getCXDcdGrid()->
				getCell(aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_TrackDisplayKudari), iYColumnNumber)->getIfDcDraw())
				->setText(strText);
		}
		//下りカスタマイズ時刻表(発時刻)
		{
			tstring strText = _T("");
			if (!bIsNull) {
				//if (aCentDedEki.getJikokuhyouHatsuJikokuDisplayKudari())
				//{
				//	strText = _T("表示有り");
				//}
				//else
				//{
				//	strText = _T("表示無し");
				//}
				if (aCentDedEki.getJikokuhyouHatsuJikokuDisplayKudari())
				{
					strText = _T("発時刻");
				}
				else
				{
					strText = _T("");
				}
			}
			Ou<CDcdTextbox>(getCXDcdGrid()->
				getCell(aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_HatsuJikokuDisplayKudari), iYColumnNumber)->getIfDcDraw())
				->setText(strText);
		}
		//下りカスタマイズ時刻表(列車番号)
		{
			tstring strText = _T("");
			if (!bIsNull) {
				switch (aCentDedEki.getJikokuhyouRessyabangouDisplayKudari()) {
				case 0:
					strText = _T(""); break;
				case 1:
					strText = _T("列番種変のみ"); break;
				case 2:
					strText = _T("列番種変情変"); break;
				case 3:
					strText = _T("列番全列車"); break;
				}
			}
			Ou<CDcdTextbox>(getCXDcdGrid()->
				getCell(aCdEkiXColSpecCont.ColumnNumberFromSpec(
					CdEkiXColSpec::EColumnType::ColumnType_RessyabangouDisplayKudari), iYColumnNumber)->getIfDcDraw())
				->setText(strText);
		}
		//下りカスタマイズ時刻表(運用番号)
		{
			tstring strText = _T("");
			if (!bIsNull) {
				switch (aCentDedEki.getJikokuhyouOperationNumberDisplayKudari()) {
				case 0:
					strText = _T(""); break;
				case 1:
					strText = _T("運番当駅変更"); break;
				case 2:
					strText = _T("運番種変のみ"); break;
				case 3:
					strText = _T("運番種変情変"); break;
				case 4:
					strText = _T("運番全列車"); break;
				}
			}
			Ou<CDcdTextbox>(getCXDcdGrid()->
				getCell(aCdEkiXColSpecCont.ColumnNumberFromSpec(
					CdEkiXColSpec::EColumnType::ColumnType_OperationNumberDisplayKudari), iYColumnNumber)->getIfDcDraw())
				->setText(strText);
		}
		//下りカスタマイズ時刻表(運用番号段数)
		{
			tstring strText = _T("");
			if (!bIsNull &&
				aCentDedEki.getJikokuhyouOperationNumberDisplayKudari() > 0) 
			{
				strText = to_tstring(aCentDedEki.getJikokuhyouOperationNumberDisplayRowsKudari());
			}
			Ou<CDcdTextbox>(getCXDcdGrid()->
				getCell(aCdEkiXColSpecCont.ColumnNumberFromSpec(
					CdEkiXColSpec::EColumnType::ColumnType_OperationNumberDisplayRowsKudari), iYColumnNumber)->getIfDcDraw())
				->setText(strText);
		}
		//下りカスタマイズ時刻表(種別)
		{
			tstring strText = _T("");
			if (!bIsNull) {
				switch (aCentDedEki.getJikokuhyouRessyaSyubetsuDisplayKudari()) {
				case 0:
					strText = _T(""); break;
				case 1:
					strText = _T("種別種変のみ"); break;
				case 2:
					strText = _T("種別種変情変"); break;
				case 3:
					strText = _T("種別全列車"); break;
				}
			}
			Ou<CDcdTextbox>(getCXDcdGrid()->
				getCell(aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_RessyaSyubetsuDisplayKudari), iYColumnNumber)->getIfDcDraw())
				->setText(strText);
		}
		//下りカスタマイズ時刻表(列車名)
		{
			tstring strText = _T("");
			if (!bIsNull) {
				switch (aCentDedEki.getJikokuhyouRessyameiDisplayKudari()) {
				case 0:
					strText = _T(""); break;
				case 1:
					strText = _T("列名種変のみ"); break;
				case 2:
					strText = _T("列名種変情変"); break;
				case 3:
					strText = _T("列名全列車"); break;
				}
			}
			Ou<CDcdTextbox>(getCXDcdGrid()->
				getCell(aCdEkiXColSpecCont.ColumnNumberFromSpec(
					CdEkiXColSpec::EColumnType::ColumnType_RessyameiDisplayKudari), iYColumnNumber)->getIfDcDraw())
				->setText(strText);
		}
		//下りカスタマイズ時刻表(路線外・前列車始発駅)
		{
			tstring strText = _T("");
			if (!bIsNull) {
				if (aCentDedEki.getJikokuhyouOuterSihatsuDisplayKudari())
				{
					strText = _T("始発駅");
				}
				else
				{
					strText = _T("");
				}
			}
			Ou<CDcdTextbox>(getCXDcdGrid()->
				getCell(aCdEkiXColSpecCont.ColumnNumberFromSpec(
					CdEkiXColSpec::EColumnType::ColumnType_OuterSihatsuDisplayKudari), iYColumnNumber)->getIfDcDraw())
				->setText(strText);
		}
		//下りカスタマイズ時刻表(路線外・次列車終着駅)
		{
			tstring strText = _T("");
			if (!bIsNull) {
				if (aCentDedEki.getJikokuhyouOuterShuchakuDisplayKudari())
				{
					strText = _T("終着駅");
				}
				else
				{
					strText = _T("");
				}
			}
			Ou<CDcdTextbox>(getCXDcdGrid()->
				getCell(aCdEkiXColSpecCont.ColumnNumberFromSpec(
					CdEkiXColSpec::EColumnType::ColumnType_OuterShuchakuDisplayKudari), iYColumnNumber)->getIfDcDraw())
				->setText(strText);
		}

		//上りカスタマイズ時刻表(着時刻)
		{
			tstring strText = _T("");
			if (!bIsNull) {
				if (aCentDedEki.getJikokuhyouChakuJikokuDisplayNobori())
				{
					strText = _T("着時刻");
				}
				else
				{
					strText = _T("");
				}
			}
			Ou<CDcdTextbox>(getCXDcdGrid()->
				getCell(aCdEkiXColSpecCont.ColumnNumberFromSpec(
					CdEkiXColSpec::EColumnType::ColumnType_ChakuJikokuDisplayNobori), iYColumnNumber)->getIfDcDraw())
				->setText(strText);
		}
		//上りカスタマイズ時刻表(番線)
		{
			tstring strText = _T("");
			if (!bIsNull) {
				if (aCentDedEki.getJikokuhyouTrackDisplayNobori())
				{
					strText = _T("番線");
				}
				else
				{
					strText = _T("");
				}
			}
			Ou<CDcdTextbox>(getCXDcdGrid()->
				getCell(aCdEkiXColSpecCont.ColumnNumberFromSpec(
					CdEkiXColSpec::EColumnType::ColumnType_TrackDisplayNobori), iYColumnNumber)->getIfDcDraw())
				->setText(strText);
		}
		//上りカスタマイズ時刻表(発時刻)
		{
			tstring strText = _T("");
			if (!bIsNull) {
				if (aCentDedEki.getJikokuhyouHatsuJikokuDisplayNobori())
				{
					strText = _T("発時刻");
				}
				else
				{
					strText = _T("");
				}
			}
			Ou<CDcdTextbox>(getCXDcdGrid()->
				getCell(aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_HatsuJikokuDisplayNobori), iYColumnNumber)->getIfDcDraw())
				->setText(strText);
		}
		//上りカスタマイズ時刻表(列車番号)
		{
			tstring strText = _T("");
			if (!bIsNull) {
				switch (aCentDedEki.getJikokuhyouRessyabangouDisplayNobori()) {
				case 0:
					strText = _T(""); break;
				case 1:
					strText = _T("列番種変のみ"); break;
				case 2:
					strText = _T("列番種変情変"); break;
				case 3:
					strText = _T("列番全列車"); break;
				}
			}
			Ou<CDcdTextbox>(getCXDcdGrid()->
				getCell(aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_RessyabangouDisplayNobori), iYColumnNumber)->getIfDcDraw())
				->setText(strText);
		}
		//上りカスタマイズ時刻表(運用番号)
		{
			tstring strText = _T("");
			if (!bIsNull) {
				switch (aCentDedEki.getJikokuhyouOperationNumberDisplayNobori()) {
				case 0:
					strText = _T(""); break;
				case 1:
					strText = _T("運番当駅変更"); break;
				case 2:
					strText = _T("運番種変のみ"); break;
				case 3:
					strText = _T("運番種変情変"); break;
				case 4:
					strText = _T("運番全列車"); break;
				}
			}
			Ou<CDcdTextbox>(getCXDcdGrid()->
				getCell(aCdEkiXColSpecCont.ColumnNumberFromSpec(
					CdEkiXColSpec::EColumnType::ColumnType_OperationNumberDisplayNobori), iYColumnNumber)->getIfDcDraw())
				->setText(strText);
		}
		//上りカスタマイズ時刻表(運用番号段数)
		{
			tstring strText = _T("");
			if (!bIsNull &&
				aCentDedEki.getJikokuhyouOperationNumberDisplayNobori() > 0)
			{
				strText = to_tstring(aCentDedEki.getJikokuhyouOperationNumberDisplayRowsNobori());
			}
			Ou<CDcdTextbox>(getCXDcdGrid()->
				getCell(aCdEkiXColSpecCont.ColumnNumberFromSpec(
					CdEkiXColSpec::EColumnType::ColumnType_OperationNumberDisplayRowsNobori), iYColumnNumber)->getIfDcDraw())
				->setText(strText);
		}
		//上りカスタマイズ時刻表(種別)
		{
			tstring strText = _T("");
			if (!bIsNull) {
				switch (aCentDedEki.getJikokuhyouRessyaSyubetsuDisplayNobori()) {
				case 0:
					strText = _T(""); break;
				case 1:
					strText = _T("種別種変のみ"); break;
				case 2:
					strText = _T("種別種変情変"); break;
				case 3:
					strText = _T("種別全列車"); break;
				}
			}
			Ou<CDcdTextbox>(getCXDcdGrid()->
				getCell(aCdEkiXColSpecCont.ColumnNumberFromSpec(
					CdEkiXColSpec::EColumnType::ColumnType_RessyaSyubetsuDisplayNobori), iYColumnNumber)->getIfDcDraw())
				->setText(strText);
		}
		//上りカスタマイズ時刻表(列車名)
		{
			tstring strText = _T("");
			if (!bIsNull) {
				switch (aCentDedEki.getJikokuhyouRessyameiDisplayNobori()) {
				case 0:
					strText = _T(""); break;
				case 1:
					strText = _T("列名種変のみ"); break;
				case 2:
					strText = _T("列名種変情変"); break;
				case 3:
					strText = _T("列名全列車"); break;
				}
			}
			Ou<CDcdTextbox>(getCXDcdGrid()->
				getCell(aCdEkiXColSpecCont.ColumnNumberFromSpec(
					CdEkiXColSpec::EColumnType::ColumnType_RessyameiDisplayNobori), iYColumnNumber)->getIfDcDraw())
				->setText(strText);
		}
		//上りカスタマイズ時刻表(路線外・前列車始発駅)
		{
			tstring strText = _T("");
			if (!bIsNull) {
				if (aCentDedEki.getJikokuhyouOuterSihatsuDisplayNobori())
				{
					strText = _T("始発駅");
				}
				else
				{
					strText = _T("");
				}
			}
			Ou<CDcdTextbox>(getCXDcdGrid()->
				getCell(aCdEkiXColSpecCont.ColumnNumberFromSpec(
					CdEkiXColSpec::EColumnType::ColumnType_OuterSihatsuDisplayNobori), iYColumnNumber)->getIfDcDraw())
				->setText(strText);
		}
		//上りカスタマイズ時刻表(路線外・次列車終着駅)
		{
			tstring strText = _T("");
			if (!bIsNull) {
				if (aCentDedEki.getJikokuhyouOuterShuchakuDisplayNobori())
				{
					strText = _T("終着駅");
				}
				else
				{
					strText = _T("");
				}
			}
			Ou<CDcdTextbox>(getCXDcdGrid()->
				getCell(aCdEkiXColSpecCont.ColumnNumberFromSpec(
					CdEkiXColSpec::EColumnType::ColumnType_OuterShuchakuDisplayNobori), iYColumnNumber)->getIfDcDraw())
				->setText(strText);
		}

		//在線表
		{
			tstring strText = _T("");
			if (!bIsNull) {
				if (aCentDedEki.getDiagramTrackDisplay())
				{
					strText = _T("表示");
				}
				else
				{
					strText = _T("");
				}
			}
			Ou<CDcdTextbox>(getCXDcdGrid()->
				getCell(aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_DiagramTrackDisplay), iYColumnNumber)->getIfDcDraw())
				->setText(strText);
		}
		//ダイヤグラム列車情報表示
		{
			tstring strText = _T("");
			if (!bIsNull) {
				switch (aCentDedEki.getDiagramRessyajouhouHyoujiKudari()) {
				case CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Origin:
					strText = _T("始発表示"); break;
				case CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Anytime:
					strText = _T("常に表示"); break;
				case CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Not:
					//strText = _T("表示無し"); break;
					strText = _T(""); break;
				}
			}
			Ou<CDcdTextbox>(getCXDcdGrid()->
				getCell(aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_DiagramRessyajouhouHyoujiKudari), iYColumnNumber)->getIfDcDraw())
				->setText(strText);
		}
		//ダイヤグラム列車情報表示
		{
			tstring strText = _T("");
			if (!bIsNull) {
				switch (aCentDedEki.getDiagramRessyajouhouHyoujiNobori()) {
				case CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Origin:
					strText = _T("始発表示"); break;
				case CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Anytime:
					strText = _T("常に表示"); break;
				case CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Not:
					//strText = _T("表示無し"); break;
					strText = _T(""); break;
				}
			}
			Ou<CDcdTextbox>(getCXDcdGrid()->
				getCell(aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_DiagramRessyajouhouHyoujiNobori), iYColumnNumber)->getIfDcDraw())
				->setText(strText);
		}

		//この駅から次の駅までの距離
		{
			tstring strText = _T("");
			if (!bIsNull) {
				strText = to_tstring(aCentDedEki.getNextEkiDistance());
			}
			Ou<CDcdTextbox>(getCXDcdGrid()->
				getCell(aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_NextEkiDistance), iYColumnNumber)->getIfDcDraw())
				->setText(strText);
		}
		//この駅から次の駅までの背景色設定
		{
			tstring strText = _T("");
			int iDiagramColorNextEki = 0;
			if (!bIsNull)
			{
				iDiagramColorNextEki = aCentDedEki.getDiagramColorNextEki();
				switch (iDiagramColorNextEki) {
				case 0:
					strText = _T("基本色"); break;
				case 1:
					strText = _T("個別色1"); break;
				case 2:
					strText = _T("個別色2"); break;
				case 3:
					strText = _T("個別色3"); break;
				case 4:
					strText = _T("個別色4"); break;
				}
			}
			Ou<CDcdTextbox>(getCXDcdGrid()->
				getCell(aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_DiagramColorNextEki), iYColumnNumber)->getIfDcDraw())
				->setText(strText);
			CdBrushProp aCdBrushProp(getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp().getDiaBackColor(iDiagramColorNextEki));
			Ou<CDcdTextbox>(getCXDcdGrid()->
				getCell(aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_DiagramColorNextEki), iYColumnNumber)->getIfDcDraw())
				->setCdBrushProp(aCdBrushProp);
		}

		//箱ダイヤで表示するか否か
		{
			tstring strText = _T("");
			if (!bIsNull) {
				if (aCentDedEki.getOperationTableDisplayJikoku())
				{
					strText = _T("表示");
				}
				else
				{
					strText = _T("");
				}
			}
			Ou<CDcdTextbox>(getCXDcdGrid()->
				getCell(aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_OperationTableDisplayJikoku), iYColumnNumber)->getIfDcDraw())
				->setText(strText);
		}
	}
	else
	{
		CDiagramEditDoc* pCDiagramEditDoc = getCDiagramEditDoc();
		const CentDedRosen* pCentDedRosen =
			pCDiagramEditDoc->getCDedRosenFileData()->getCentDedRosen();
		const Mu<const CentDedEki*>* pCentDedEkiContGet =
			pCentDedRosen->getCentDedEkiCont()->getMuPtr();
		//分岐駅設定
		{
			tstring strBrunch = _T("");
			if (!bIsNull) {
				if (aCentDedEki.getBrunchCoreEkiIndex() >= 0)
				{
					const CentDedEki* pCentDedEkiBrunchCore =
						pCentDedEkiContGet->get(aCentDedEki.getBrunchCoreEkiIndex());
					strBrunch = to_tstring(aCentDedEki.getBrunchCoreEkiIndex()) +
						_T(". ") + pCentDedEkiBrunchCore->getEkimei();
				}
			}
			Ou<CDcdTextbox>(getCXDcdGrid()->
				getCell(5, iYColumnNumber)->getIfDcDraw())
				->setText(strBrunch);
		}
		//環状線設定
		{
			tstring strLoop = _T("");
			if (!bIsNull) {
				if (aCentDedEki.getLoopOriginEkiIndex() >= 0)
				{
					const CentDedEki* pCentDedEkiLoopOrigin =
						pCentDedEkiContGet->get(aCentDedEki.getLoopOriginEkiIndex());
					strLoop = to_tstring(aCentDedEki.getLoopOriginEkiIndex()) +
						_T(". ") + pCentDedEkiLoopOrigin->getEkimei();
				}
			}
			Ou<CDcdTextbox>(getCXDcdGrid()->
				getCell(6, iYColumnNumber)->getIfDcDraw())
				->setText(strLoop);
		}
	}
	// --------------------------------
	//	境界線
	// --------------------------------
	{
		bool bKyoukaisen = false;
		if (aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku &&
			aCentDedEki.getBrunchCoreEkiIndex() >= 0)
		{
			bKyoukaisen = true;
		}
		else if (aCentDedEkiNext.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku &&
			aCentDedEkiNext.getBrunchCoreEkiIndex() >= 0)
		{
			bKyoukaisen = true;
		}
		else if (aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku &&
			aCentDedEkiNext.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku)
		{
			bKyoukaisen = true;
		}
		CdPenProp aCdPenProp = getCdPenPropNormal() ;
		if ( !bIsNull ){
			if (bKyoukaisen){
				aCdPenProp = getCdPenPropBold() ;
			}
		}
		Ou<CDcdLine>
			( getCXDcdGrid()->getYBorder( iYColumnNumber )->getIfDcDraw())
				->setCdPenProp( aCdPenProp ) ;
	}

	// --------------------------------
	//	グリッド全体を更新領域とします
	// --------------------------------
	//	境界線の太さが変動した場合は、
	//	境界線・およびそれより下のすべてのセルの更新が必要です。
	//	これに対応するため、 CWndDcdGridEki では、
	//	駅の属性の更新のたびに
	//	グリッド全域を更新します。
	//InvalidateGrid() ;
}

void CWndDcdGridEki::OnUpdate_All() 
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

		OnCreate_Header();

		//	Y列数を増減させる
		getCXDcdGrid()->setYColumnCount( 
			pCentDedEkiContGet->size() + 2 ) ;

		//	駅名列の幅を設定する
		{
			CDcdTargetGetDC	aTarget ;
			CDcdTextbox aCDcd = this->getCDcdEkimei() ;
			CdDcdSizeXy	aCdDcdSizeXy ;
			aCDcd.getItemSize( &aTarget , &aCdDcdSizeXy ) ;
			getCXDcdGrid()->getXColumn( 1 )->setColumnSize( 
				aCdDcdSizeXy.getX() ) ;
		}
		int iEkiSize = pCentDedEkiContGet->size();
		//	各セルに、データを設定
//#pragma omp parallel for schedule(static)
		for (int idxEki = 0 ; idxEki < iEkiSize;
				idxEki ++ ){
			const CentDedEki* pCentDedEki = pCentDedEkiContGet->get( idxEki ) ;
			{
				if (idxEki < iEkiSize - 1)
				{
					const CentDedEki*	pCentDedEkiNext
						= pCentDedEkiContGet->get(idxEki + 1);
					OnUpdate_setCentDedEki_To_Column(
						idxEki + 1, *pCentDedEki, *pCentDedEkiNext);
				}
				else
				{
					OnUpdate_setCentDedEki_To_Column(
						idxEki + 1, *pCentDedEki, CentDedEki());
				}
			}

			//const CentDedEki* pCentDedEkiNext = pCentDedEkiContGet->get(idxEki + 1);
			//OnUpdate_setCentDedEki_To_Column( idxEki + 1 , *pCentDedEki, *pCentDedEkiNext) ;
		}
		OnUpdate_setCentDedEki_To_Column(iEkiSize + 1, CentDedEki(), CentDedEki());

		InvalidateGrid() ;

//#pragma omp barrier	
		//OnUpdate_setCentDedEki_To_Column(idxEki + 1, CentDedEki(), CentDedEki());
		// ****************************************************************
	}
}

void CWndDcdGridEki::OnCreate_Header()
{
	// --------------------------------
	//	列の数を指定
	// --------------------------------
	getCXDcdGrid()->setXColumnCount(createXColSpecCont().size());
	getCXDcdGrid()->setYColumnCount(2);
	getCXDcdGrid()->setYFixColumnCount(1);

	//if (getDisplaySettingMode())
	//{
	getCXDcdGrid()->setXFixColumnCount(2);
	//}

	CdEkiXColSpecCont aCdEkiXColSpecCont = createXColSpecCont();
	// --------------------------------
	//	列のサイズを設定
	// --------------------------------
	{
		CDcdTargetGetDC	aCDcdTarget(NULL);
		// --------------------------------
		//	X列
		// --------------------------------
		{
			//駅Index
			CDcdGridXColumn* pCDcdGridXColumn = getCXDcdGrid()->getXColumn(
				aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_EkiIndex));
			CdDcdSizeXy	sizeEkiIndex;
			CDcdTextbox	aCDcdTextbox(getCDcdEkiIndex());
			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeEkiIndex);
			pCDcdGridXColumn->setColumnSize(sizeEkiIndex.getX());

		}
		{
			//	駅名
			CDcdGridXColumn* pCDcdGridXColumn = getCXDcdGrid()->getXColumn(
				aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_Ekimei));
			CdDcdSizeXy	sizeEkimei;
			CDcdTextbox	aCDcdTextbox(getCDcdEkimei());
			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeEkimei);
			pCDcdGridXColumn->setColumnSize(sizeEkimei.getX());
		}
		{
			//	駅時刻形式
			CDcdGridXColumn* pCDcdGridXColumn = getCXDcdGrid()->getXColumn(
				aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_Ekijikokukeisiki));
			CdDcdSizeXy	sizeEkijikokukeisiki;
			CDcdTextbox	aCDcdTextbox(
				getCDcdEkijikokukeisiki());
			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeEkijikokukeisiki);

			pCDcdGridXColumn->setColumnSize(sizeEkijikokukeisiki.getX());
		}
		{
			//	駅規模
			CDcdGridXColumn* pCDcdGridXColumn = getCXDcdGrid()->getXColumn(
				aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_Ekikibo));
			CdDcdSizeXy	sizeEkikibo;
			CDcdTextbox	aCDcdTextbox(
				getCDcdEkikibo());
			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeEkikibo);

			pCDcdGridXColumn->setColumnSize(sizeEkikibo.getX());
		}
		{
			//	駅番線数
			CDcdGridXColumn* pCDcdGridXColumn = getCXDcdGrid()->getXColumn(
				aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_EkiTrack2Count));
			CdDcdSizeXy	sizeEkiTrack2Count;
			CDcdTextbox	aCDcdTextbox(
				getCDcdEkiTrack2Count());
			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeEkiTrack2Count);

			pCDcdGridXColumn->setColumnSize(sizeEkiTrack2Count.getX());
		}
		if (getDisplaySettingMode())
		{
			{
				//前後作業欄
				CDcdGridXColumn* pCDcdGridXColumn = getCXDcdGrid()->getXColumn(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_OperationOriginDownBeforeUpAfter));
				CDcdGridXColumn* pCDcdGridXColumn2 = getCXDcdGrid()->getXColumn(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_OperationOrigin));
				CDcdGridXColumn* pCDcdGridXColumn3 = getCXDcdGrid()->getXColumn(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_OperationOriginDownAfterUpBefore));
				CDcdGridXColumn* pCDcdGridXColumn4 = getCXDcdGrid()->getXColumn(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_OperationTerminalDownBeforeUpAfter));
				CDcdGridXColumn* pCDcdGridXColumn5 = getCXDcdGrid()->getXColumn(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_OperationTerminal));
				CDcdGridXColumn* pCDcdGridXColumn6 = getCXDcdGrid()->getXColumn(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_OperationTerminalDownAfterUpBefore));
				
				CdDcdSizeXy	sizeHeader4;
				CDcdTextbox	aCDcdTextbox4(CDcdTextbox(_T(""),
					CdFontProp(9, _T("Meiryo UI")),
					_T("京都京都"), 1, 2, 2, CdPenProp(),
					CConverter_WinGdi().CdBrushPropOf(WHITE_BRUSH)));
				aCDcdTextbox4.getItemSize(&aCDcdTarget, &sizeHeader4);
				CdDcdSizeXy	sizeHeader2;
				CDcdTextbox	aCDcdTextbox2(CDcdTextbox(_T(""),
					CdFontProp(9, _T("Meiryo UI")),
					_T("京都"), 1, 2, 2, CdPenProp(),
					CConverter_WinGdi().CdBrushPropOf(WHITE_BRUSH)));

				aCDcdTextbox2.getItemSize(&aCDcdTarget, &sizeHeader2);
				pCDcdGridXColumn->setColumnSize(sizeHeader2.getX());
				pCDcdGridXColumn2->setColumnSize(sizeHeader4.getX());
				pCDcdGridXColumn3->setColumnSize(sizeHeader2.getX());
				pCDcdGridXColumn4->setColumnSize(sizeHeader2.getX());
				pCDcdGridXColumn5->setColumnSize(sizeHeader4.getX());
				pCDcdGridXColumn6->setColumnSize(sizeHeader2.getX());
			}
			{
				//番線表示省略設定
				CDcdGridXColumn* pCDcdGridXColumn = getCXDcdGrid()->getXColumn(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_TrackOmit));
				CdDcdSizeXy	sizeHeader;
				CDcdTextbox	aCDcdTextbox(CDcdTextbox(_T(""),
					CdFontProp(9, _T("Meiryo UI")),
					_T("京都京都"), 1, 2, 2, CdPenProp(),
					CConverter_WinGdi().CdBrushPropOf(WHITE_BRUSH)));
				aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeHeader);
				pCDcdGridXColumn->setColumnSize(sizeHeader.getX());

			}
			{
				//下りカスタマイズ時刻表
				CDcdGridXColumn* pCDcdGridXColumn = getCXDcdGrid()->getXColumn(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_ChakuJikokuDisplayKudari));
				CDcdGridXColumn* pCDcdGridXColumn2 = getCXDcdGrid()->getXColumn(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_TrackDisplayKudari));
				CDcdGridXColumn* pCDcdGridXColumn3 = getCXDcdGrid()->getXColumn(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_HatsuJikokuDisplayKudari));
				CDcdGridXColumn* pCDcdGridXColumn4 = getCXDcdGrid()->getXColumn(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_RessyabangouDisplayKudari));
				CDcdGridXColumn* pCDcdGridXColumn5 = getCXDcdGrid()->getXColumn(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_OperationNumberDisplayKudari));
				CDcdGridXColumn* pCDcdGridXColumn10 = getCXDcdGrid()->getXColumn(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_OperationNumberDisplayRowsKudari));
				CDcdGridXColumn* pCDcdGridXColumn6 = getCXDcdGrid()->getXColumn(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_RessyaSyubetsuDisplayKudari));
				CDcdGridXColumn* pCDcdGridXColumn7 = getCXDcdGrid()->getXColumn(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_RessyameiDisplayKudari));
				CDcdGridXColumn* pCDcdGridXColumn8 = getCXDcdGrid()->getXColumn(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_OuterSihatsuDisplayKudari));
				CDcdGridXColumn* pCDcdGridXColumn9 = getCXDcdGrid()->getXColumn(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_OuterShuchakuDisplayKudari));
				CdDcdSizeXy	sizeHeader1;
				CDcdTextbox	aCDcdTextbox1(CDcdTextbox(_T(""),
					CdFontProp(9, _T("Meiryo UI")),
					_T("京"), 1, 2, 2, CdPenProp(),
					CConverter_WinGdi().CdBrushPropOf(WHITE_BRUSH)));
				aCDcdTextbox1.getItemSize(&aCDcdTarget, &sizeHeader1);
				CdDcdSizeXy	sizeHeader2;
				CDcdTextbox	aCDcdTextbox2(CDcdTextbox(_T(""),
					CdFontProp(9, _T("Meiryo UI")),
					_T("京都"), 1, 2, 2, CdPenProp(),
					CConverter_WinGdi().CdBrushPropOf(WHITE_BRUSH)));
				aCDcdTextbox2.getItemSize(&aCDcdTarget, &sizeHeader2);
				CdDcdSizeXy	sizeHeader3;
				CDcdTextbox	aCDcdTextbox3(CDcdTextbox(_T(""),
					CdFontProp(9, _T("Meiryo UI")),
					_T("京都京"), 1, 2, 2, CdPenProp(),
					CConverter_WinGdi().CdBrushPropOf(WHITE_BRUSH)));
				aCDcdTextbox3.getItemSize(&aCDcdTarget, &sizeHeader3);
				CdDcdSizeXy	sizeHeader6;
				CDcdTextbox	aCDcdTextbox6(CDcdTextbox(_T(""),
					CdFontProp(9, _T("Meiryo UI")),
					_T("京都京都京都"), 1, 2, 2, CdPenProp(),
					CConverter_WinGdi().CdBrushPropOf(WHITE_BRUSH)));
				aCDcdTextbox6.getItemSize(&aCDcdTarget, &sizeHeader6);

				pCDcdGridXColumn->setColumnSize(sizeHeader3.getX());
				pCDcdGridXColumn2->setColumnSize(sizeHeader2.getX());
				pCDcdGridXColumn3->setColumnSize(sizeHeader3.getX());
				pCDcdGridXColumn4->setColumnSize(sizeHeader6.getX());
				pCDcdGridXColumn5->setColumnSize(sizeHeader6.getX());
				pCDcdGridXColumn10->setColumnSize(sizeHeader1.getX());
				pCDcdGridXColumn6->setColumnSize(sizeHeader6.getX());
				pCDcdGridXColumn7->setColumnSize(sizeHeader6.getX());
				pCDcdGridXColumn8->setColumnSize(sizeHeader3.getX());
				pCDcdGridXColumn9->setColumnSize(sizeHeader3.getX());
			}
			{
				//上りカスタマイズ時刻表
				CDcdGridXColumn* pCDcdGridXColumn = getCXDcdGrid()->getXColumn(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_ChakuJikokuDisplayNobori));
				CDcdGridXColumn* pCDcdGridXColumn2 = getCXDcdGrid()->getXColumn(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_TrackDisplayNobori));
				CDcdGridXColumn* pCDcdGridXColumn3 = getCXDcdGrid()->getXColumn(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_HatsuJikokuDisplayNobori));
				CDcdGridXColumn* pCDcdGridXColumn4 = getCXDcdGrid()->getXColumn(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_RessyabangouDisplayNobori));
				CDcdGridXColumn* pCDcdGridXColumn5 = getCXDcdGrid()->getXColumn(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_OperationNumberDisplayNobori));
				CDcdGridXColumn* pCDcdGridXColumn10 = getCXDcdGrid()->getXColumn(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_OperationNumberDisplayRowsNobori));
				CDcdGridXColumn* pCDcdGridXColumn6 = getCXDcdGrid()->getXColumn(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_RessyaSyubetsuDisplayNobori));
				CDcdGridXColumn* pCDcdGridXColumn7 = getCXDcdGrid()->getXColumn(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_RessyameiDisplayNobori));
				CDcdGridXColumn* pCDcdGridXColumn8 = getCXDcdGrid()->getXColumn(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_OuterSihatsuDisplayNobori));
				CDcdGridXColumn* pCDcdGridXColumn9 = getCXDcdGrid()->getXColumn(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_OuterShuchakuDisplayNobori));
				CdDcdSizeXy	sizeHeader1;
				CDcdTextbox	aCDcdTextbox1(CDcdTextbox(_T(""),
					CdFontProp(9, _T("Meiryo UI")),
					_T("京"), 1, 2, 2, CdPenProp(),
					CConverter_WinGdi().CdBrushPropOf(WHITE_BRUSH)));
				aCDcdTextbox1.getItemSize(&aCDcdTarget, &sizeHeader1);
				CdDcdSizeXy	sizeHeader2;
				CDcdTextbox	aCDcdTextbox2(CDcdTextbox(_T(""),
					CdFontProp(9, _T("Meiryo UI")),
					_T("京都"), 1, 2, 2, CdPenProp(),
					CConverter_WinGdi().CdBrushPropOf(WHITE_BRUSH)));
				aCDcdTextbox2.getItemSize(&aCDcdTarget, &sizeHeader2);
				CdDcdSizeXy	sizeHeader3;
				CDcdTextbox	aCDcdTextbox3(CDcdTextbox(_T(""),
					CdFontProp(9, _T("Meiryo UI")),
					_T("京都京"), 1, 2, 2, CdPenProp(),
					CConverter_WinGdi().CdBrushPropOf(WHITE_BRUSH)));
				aCDcdTextbox3.getItemSize(&aCDcdTarget, &sizeHeader3);
				CdDcdSizeXy	sizeHeader6;
				CDcdTextbox	aCDcdTextbox6(CDcdTextbox(_T(""),
					CdFontProp(9, _T("Meiryo UI")),
					_T("京都京都京都"), 1, 2, 2, CdPenProp(),
					CConverter_WinGdi().CdBrushPropOf(WHITE_BRUSH)));
				aCDcdTextbox6.getItemSize(&aCDcdTarget, &sizeHeader6);

				pCDcdGridXColumn->setColumnSize(sizeHeader3.getX());
				pCDcdGridXColumn2->setColumnSize(sizeHeader2.getX());
				pCDcdGridXColumn3->setColumnSize(sizeHeader3.getX());
				pCDcdGridXColumn4->setColumnSize(sizeHeader6.getX());
				pCDcdGridXColumn5->setColumnSize(sizeHeader6.getX());
				pCDcdGridXColumn10->setColumnSize(sizeHeader1.getX());
				pCDcdGridXColumn6->setColumnSize(sizeHeader6.getX());
				pCDcdGridXColumn7->setColumnSize(sizeHeader6.getX());
				pCDcdGridXColumn8->setColumnSize(sizeHeader3.getX());
				pCDcdGridXColumn9->setColumnSize(sizeHeader3.getX());
			}
			{
				//在線表表示設定
				CDcdGridXColumn* pCDcdGridXColumn = getCXDcdGrid()->getXColumn(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_DiagramTrackDisplay));
				CdDcdSizeXy	sizeHeader;
				CDcdTextbox	aCDcdTextbox(CDcdTextbox(_T(""),
					CdFontProp(9, _T("Meiryo UI")),
					_T("京都京"), 1, 2, 2, CdPenProp(),
					CConverter_WinGdi().CdBrushPropOf(WHITE_BRUSH)));
				aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeHeader);
				pCDcdGridXColumn->setColumnSize(sizeHeader.getX());

			}
			{
				//ダイヤグラム列車情報表示
				CDcdGridXColumn* pCDcdGridXColumn = getCXDcdGrid()->getXColumn(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_DiagramRessyajouhouHyoujiKudari));
				CDcdGridXColumn* pCDcdGridXColumn2 = getCXDcdGrid()->getXColumn(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_DiagramRessyajouhouHyoujiNobori));
				CdDcdSizeXy	sizeHeader;
				CDcdTextbox	aCDcdTextbox(CDcdTextbox(_T(""),
					CdFontProp(9, _T("Meiryo UI")),
					_T("京都京都京"), 1, 2, 2, CdPenProp(),
					CConverter_WinGdi().CdBrushPropOf(WHITE_BRUSH)));
				aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeHeader);
				pCDcdGridXColumn->setColumnSize(sizeHeader.getX());
				pCDcdGridXColumn2->setColumnSize(sizeHeader.getX());

			}
			{
				//この駅から次の駅までの距離
				CDcdGridXColumn* pCDcdGridXColumn = getCXDcdGrid()->getXColumn(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_NextEkiDistance));
				CdDcdSizeXy	sizeHeader;
				CDcdTextbox	aCDcdTextbox(CDcdTextbox(_T(""),
					CdFontProp(9, _T("Meiryo UI")),
					_T("京都京都"), 1, 2, 2, CdPenProp(),
					CConverter_WinGdi().CdBrushPropOf(WHITE_BRUSH)));
				aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeHeader);
				pCDcdGridXColumn->setColumnSize(sizeHeader.getX());
			}
			{
				//この駅から次の駅までの背景色設定
				CDcdGridXColumn* pCDcdGridXColumn = getCXDcdGrid()->getXColumn(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_DiagramColorNextEki));
				CdDcdSizeXy	sizeHeader;
				CDcdTextbox	aCDcdTextbox(CDcdTextbox(_T(""),
					CdFontProp(9, _T("Meiryo UI")),
					_T("京都京都京"), 1, 2, 2, CdPenProp(),
					CConverter_WinGdi().CdBrushPropOf(WHITE_BRUSH)));
				aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeHeader);
				pCDcdGridXColumn->setColumnSize(sizeHeader.getX());
			}
			{
				//箱ダイヤで表示するか否か
				CDcdGridXColumn* pCDcdGridXColumn = getCXDcdGrid()->getXColumn(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_OperationTableDisplayJikoku));
				CdDcdSizeXy	sizeHeader;
				CDcdTextbox	aCDcdTextbox(CDcdTextbox(_T(""),
					CdFontProp(9, _T("Meiryo UI")),
					_T("京都京都"), 1, 2, 2, CdPenProp(),
					CConverter_WinGdi().CdBrushPropOf(WHITE_BRUSH)));
				aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeHeader);
				pCDcdGridXColumn->setColumnSize(sizeHeader.getX());
			}

		}
		else
		{
			{
				//分岐駅設定
				CDcdGridXColumn* pCDcdGridXColumn = getCXDcdGrid()->getXColumn(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_EkiBrunch));
				CdDcdSizeXy	sizeBrunch;
				CDcdTextbox	aCDcdTextbox(getCDcdBrunchLoop());
				aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeBrunch);
				pCDcdGridXColumn->setColumnSize(sizeBrunch.getX());

			}
			{
				//環状線設定
				CDcdGridXColumn* pCDcdGridXColumn = getCXDcdGrid()->getXColumn(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_EkiLoop));
				CdDcdSizeXy	sizeLoop;
				CDcdTextbox	aCDcdTextbox(getCDcdBrunchLoop());
				aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeLoop);
				pCDcdGridXColumn->setColumnSize(sizeLoop.getX());

			}
		}
		// --------------------------------
		//	Y列
		// --------------------------------
		{
			CdDcdSizeXy	sizeEkimei;
			CDcdTextbox	aCDcdTextbox(
				getCDcdEkimei());
			aCDcdTextbox.getItemSize(&aCDcdTarget, &sizeEkimei);

			getCXDcdGrid()->getYColumn(0)->setColumnSize(sizeEkimei.getY());
			getCXDcdGrid()->getYColumn(1)->setColumnSize(sizeEkimei.getY());
		}
	}
	// --------------------------------
	//	最上行にテキストを設定
	// --------------------------------
	{
		CConverter_WinGdi	aConv;

		CdDrawTextProp	aCdDrawTextProp(
			CdFontProp(9, _T("Meiryo UI")),
			//aConv.CdFontPropOf( DEFAULT_GUI_FONT ) ,
			aConv.CdColorPropOfSysColor(COLOR_MENUTEXT));
		CdBrushProp	aCdBrushProp(aConv.CdColorPropOfSysColor(COLOR_MENU));



		{
			//	駅Index
			CDcdGridCell* pCDcdGridCell = getCXDcdGrid()->getCell(
				aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_EkiIndex), 0);

			Ou<CDcdTextbox>	pCDcdTextbox =
				pCDcdGridCell->getIfDcDraw();
			pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
			pCDcdTextbox->setCdBrushProp(aCdBrushProp);

			CString	aString;
			aString.LoadString(IDS_WORD_EkiIndex);
			Ou<CDcdTextbox>(pCDcdGridCell->getIfDcDraw())->setText((LPCTSTR)aString);
		}
		{
			//	駅名
			CDcdGridCell* pCDcdGridCell = getCXDcdGrid()->getCell(
				aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_Ekimei), 0);

			Ou<CDcdTextbox>	pCDcdTextbox =
				pCDcdGridCell->getIfDcDraw();
			pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
			pCDcdTextbox->setCdBrushProp(aCdBrushProp);

			CString	aString;
			aString.LoadString(IDS_WORD_Ekimei);
			Ou<CDcdTextbox>(pCDcdGridCell->getIfDcDraw())->setText((LPCTSTR)aString);
		}
		{
			//	駅時刻形式
			CDcdGridCell* pCDcdGridCell = getCXDcdGrid()->getCell(
				aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_Ekijikokukeisiki), 0);

			Ou<CDcdTextbox>	pCDcdTextbox =
				pCDcdGridCell->getIfDcDraw();
			pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
			pCDcdTextbox->setCdBrushProp(aCdBrushProp);

			CString	aString;
			aString.LoadString(IDS_WORD_Jikokukeisiki);
			Ou<CDcdTextbox>(pCDcdGridCell->getIfDcDraw())->setText((LPCTSTR)aString);
		}
		{
			//	駅規模
			CDcdGridCell* pCDcdGridCell = getCXDcdGrid()->getCell(
				aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_Ekikibo), 0);

			Ou<CDcdTextbox>	pCDcdTextbox =
				pCDcdGridCell->getIfDcDraw();
			pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
			pCDcdTextbox->setCdBrushProp(aCdBrushProp);

			CString	aString;
			aString.LoadString(IDS_WORD_Ekikibo);
			Ou<CDcdTextbox>(pCDcdGridCell->getIfDcDraw())->setText((LPCTSTR)aString);
		}
		{
			//	駅番線数
			CDcdGridCell* pCDcdGridCell = getCXDcdGrid()->getCell(
				aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_EkiTrack2Count), 0);

			Ou<CDcdTextbox>	pCDcdTextbox =
				pCDcdGridCell->getIfDcDraw();
			pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
			pCDcdTextbox->setCdBrushProp(aCdBrushProp);

			CString	aString;
			aString.LoadString(IDS_WORD_EkiTrack2Count);
			Ou<CDcdTextbox>(pCDcdGridCell->getIfDcDraw())->setText((LPCTSTR)aString);
		}
		if (getDisplaySettingMode())
		{
			{
				//	前後作業欄(起点側)
				CDcdGridCell* pCDcdGridCell = getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(
						CdEkiXColSpec::EColumnType::ColumnType_OperationOriginDownBeforeUpAfter), 0);

				pCDcdGridCell->setAttachCellCount(3, 1);
				Ou<CDcdTextbox>	pCDcdTextbox =
					pCDcdGridCell->getIfDcDraw();
				pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
				pCDcdTextbox->setCdBrushProp(aCdBrushProp);

				//CString	aString;
				//aString.LoadString(IDS_WORD_EkiTrack2Count);
				//Ou<CDcdTextbox>(pCDcdGridCell->getIfDcDraw())->setText((LPCTSTR)aString);
				Ou<CDcdTextbox>(pCDcdGridCell->getIfDcDraw())->setText(_T("作業欄(起点側)"));
			}
			{
				//	前後作業欄(終点側)
				CDcdGridCell* pCDcdGridCell = getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(
						CdEkiXColSpec::EColumnType::ColumnType_OperationTerminalDownBeforeUpAfter), 0);

				pCDcdGridCell->setAttachCellCount(3, 1);
				Ou<CDcdTextbox>	pCDcdTextbox =
					pCDcdGridCell->getIfDcDraw();
				pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
				pCDcdTextbox->setCdBrushProp(aCdBrushProp);

				//CString	aString;
				//aString.LoadString(IDS_WORD_EkiTrack2Count);
				//Ou<CDcdTextbox>(pCDcdGridCell->getIfDcDraw())->setText((LPCTSTR)aString);
				Ou<CDcdTextbox>(pCDcdGridCell->getIfDcDraw())->setText(_T("作業欄(終点側)"));
			}
			{
				//	番線表示省略設定
				CDcdGridCell* pCDcdGridCell = getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_TrackOmit), 0);

				Ou<CDcdTextbox>	pCDcdTextbox =
					pCDcdGridCell->getIfDcDraw();
				pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
				pCDcdTextbox->setCdBrushProp(aCdBrushProp);

				//CString	aString;
				//aString.LoadString(IDS_WORD_EkiTrack2Count);
				//Ou<CDcdTextbox>(pCDcdGridCell->getIfDcDraw())->setText((LPCTSTR)aString);
				Ou<CDcdTextbox>(pCDcdGridCell->getIfDcDraw())->setText(_T("番線省略"));
			}
			{
				//	下りカスタマイズ時刻表
				CDcdGridCell* pCDcdGridCell = getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_ChakuJikokuDisplayKudari), 0);

				pCDcdGridCell->setAttachCellCount(10, 1);
				Ou<CDcdTextbox>	pCDcdTextbox =
					pCDcdGridCell->getIfDcDraw();
				pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
				pCDcdTextbox->setCdBrushProp(aCdBrushProp);

				//CString	aString;
				//aString.LoadString(IDS_WORD_EkiTrack2Count);
				//Ou<CDcdTextbox>(pCDcdGridCell->getIfDcDraw())->setText((LPCTSTR)aString);
				Ou<CDcdTextbox>(pCDcdGridCell->getIfDcDraw())->setText(_T("下りカスタマイズ時刻表(着時刻/番線/発時刻/列車番号/運用番号・段数/種別/列車名/始発駅/終着駅)"));
			}
			{
				//	上りカスタマイズ時刻表
				CDcdGridCell* pCDcdGridCell = getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_ChakuJikokuDisplayNobori), 0);

				pCDcdGridCell->setAttachCellCount(10, 1);
				Ou<CDcdTextbox>	pCDcdTextbox =
					pCDcdGridCell->getIfDcDraw();
				pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
				pCDcdTextbox->setCdBrushProp(aCdBrushProp);

				//CString	aString;
				//aString.LoadString(IDS_WORD_EkiTrack2Count);
				//Ou<CDcdTextbox>(pCDcdGridCell->getIfDcDraw())->setText((LPCTSTR)aString);
				Ou<CDcdTextbox>(pCDcdGridCell->getIfDcDraw())->setText(_T("上りカスタマイズ時刻表(着時刻/番線/発時刻/列車番号/運用番号・段数/種別/列車名/始発駅/終着駅)"));
			}
			{
				//	在線表表示設定
				CDcdGridCell* pCDcdGridCell = getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_DiagramTrackDisplay), 0);

				Ou<CDcdTextbox>	pCDcdTextbox =
					pCDcdGridCell->getIfDcDraw();
				pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
				pCDcdTextbox->setCdBrushProp(aCdBrushProp);

				//CString	aString;
				//aString.LoadString(IDS_WORD_EkiTrack2Count);
				//Ou<CDcdTextbox>(pCDcdGridCell->getIfDcDraw())->setText((LPCTSTR)aString);
				Ou<CDcdTextbox>(pCDcdGridCell->getIfDcDraw())->setText(_T("在線表"));
			}
			{
				//	ダイヤグラム列車情報表示
				CDcdGridCell* pCDcdGridCell = getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_DiagramRessyajouhouHyoujiKudari), 0);

				pCDcdGridCell->setAttachCellCount(2, 1);
				Ou<CDcdTextbox>	pCDcdTextbox =
					pCDcdGridCell->getIfDcDraw();
				pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
				pCDcdTextbox->setCdBrushProp(aCdBrushProp);

				//CString	aString;
				//aString.LoadString(IDS_WORD_EkiTrack2Count);
				//Ou<CDcdTextbox>(pCDcdGridCell->getIfDcDraw())->setText((LPCTSTR)aString);
				Ou<CDcdTextbox>(pCDcdGridCell->getIfDcDraw())->setText(_T("列車情報(下り/上り)"));
			}
			{
				//	この駅から次の駅までの距離
				CDcdGridCell* pCDcdGridCell = getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_NextEkiDistance), 0);

				Ou<CDcdTextbox>	pCDcdTextbox =
					pCDcdGridCell->getIfDcDraw();
				pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
				pCDcdTextbox->setCdBrushProp(aCdBrushProp);

				//CString	aString;
				//aString.LoadString(IDS_WORD_EkiTrack2Count);
				//Ou<CDcdTextbox>(pCDcdGridCell->getIfDcDraw())->setText((LPCTSTR)aString);
				Ou<CDcdTextbox>(pCDcdGridCell->getIfDcDraw())->setText(_T("駅間距離"));
			}
			{
				//	この駅から次の駅までの背景色設定
				CDcdGridCell* pCDcdGridCell = getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_DiagramColorNextEki), 0);

				Ou<CDcdTextbox>	pCDcdTextbox =
					pCDcdGridCell->getIfDcDraw();
				pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
				pCDcdTextbox->setCdBrushProp(aCdBrushProp);

				//CString	aString;
				//aString.LoadString(IDS_WORD_EkiTrack2Count);
				//Ou<CDcdTextbox>(pCDcdGridCell->getIfDcDraw())->setText((LPCTSTR)aString);
				Ou<CDcdTextbox>(pCDcdGridCell->getIfDcDraw())->setText(_T("駅間背景色"));
			}
			{
				//	箱ダイヤで表示するか否か
				CDcdGridCell* pCDcdGridCell = getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_OperationTableDisplayJikoku), 0);

				Ou<CDcdTextbox>	pCDcdTextbox =
					pCDcdGridCell->getIfDcDraw();
				pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
				pCDcdTextbox->setCdBrushProp(aCdBrushProp);

				//CString	aString;
				//aString.LoadString(IDS_WORD_EkiTrack2Count);
				//Ou<CDcdTextbox>(pCDcdGridCell->getIfDcDraw())->setText((LPCTSTR)aString);
				Ou<CDcdTextbox>(pCDcdGridCell->getIfDcDraw())->setText(_T("箱ダイヤ"));
			}
		}
		else
		{
			{
				//	分岐駅設定
				CDcdGridCell* pCDcdGridCell = getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_EkiBrunch), 0);

				pCDcdGridCell->setAttachCellCount(1, 1);
				Ou<CDcdTextbox>	pCDcdTextbox =
					pCDcdGridCell->getIfDcDraw();
				pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
				pCDcdTextbox->setCdBrushProp(aCdBrushProp);

				CString	aString;
				aString.LoadString(IDS_WORD_Brunch);
				Ou<CDcdTextbox>(pCDcdGridCell->getIfDcDraw())->setText((LPCTSTR)aString);
			}
			{
				//	環状線設定
				CDcdGridCell* pCDcdGridCell = getCXDcdGrid()->getCell(
					aCdEkiXColSpecCont.ColumnNumberFromSpec(CdEkiXColSpec::EColumnType::ColumnType_EkiLoop), 0);

				Ou<CDcdTextbox>	pCDcdTextbox =
					pCDcdGridCell->getIfDcDraw();
				pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
				pCDcdTextbox->setCdBrushProp(aCdBrushProp);

				CString	aString;
				aString.LoadString(IDS_WORD_Loop);
				Ou<CDcdTextbox>(pCDcdGridCell->getIfDcDraw())->setText((LPCTSTR)aString);
			}
		}
	}
}

	// --------------------------------
	//@name メニューコマンドの下請関数
	// --------------------------------
int CWndDcdGridEki::OnEditCut_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;
	Ou<CRfEditCmd_Eki> pCmd ;
	Ou<CRfEditCmd_Eki>* ppCmd = NULL ;
	if ( !bQueryEnable ){	ppCmd = &pCmd ;}
	
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if ( iRv >= 0 )
	{
		//if (!createCmd(CWndDcdGridEki::ECreateCmd_Focus, ppCmd))
		if ( !createCmd( CWndDcdGridEki::ECreateCmd_Sequence , ppCmd ) )
		{
			iRv = -1 ;	//	セルの位置が正しくありません。
		}
	}
	//基幹駅および終点駅になっている場合は、コマンド無効です。
	if (iRv >= 0)
	{
		if (getCSelect()->getSelectedCellCount() == 0)
		{
			const Mu< const CentDedEki* >* pCentDedEkiCont = getCDiagramEditDoc()->getCDedRosenFileData()
				->getCentDedRosen()->getCentDedEkiCont()->getMuPtr();
			CdEkiYColSpec aCdEkiYColSpec = getYColSpecOfFocus();
			int iEkiIndexSelect = aCdEkiYColSpec.getEkiIndex();
			for (int idx = 0; idx < pCentDedEkiCont->size() && iRv >= 0 ; idx++)
			{
				if (iEkiIndexSelect != idx)
				{
					if (pCentDedEkiCont->get(idx)->getBrunchCoreEkiIndex() == iEkiIndexSelect)
					{
						iRv = -2; //選択された駅は、他の駅から基幹駅に指定されています
					}
					else if (pCentDedEkiCont->get(idx)->getLoopOriginEkiIndex() == iEkiIndexSelect)
					{
						iRv = -3; //選択された駅は、他の駅から起点駅に指定されています
					}
				}
			}
		}
		else if (getCSelect()->getSelectedCellCount() > 0)
		{
			const Mu< const CentDedEki* >* pCentDedEkiCont = getCDiagramEditDoc()->getCDedRosenFileData()
				->getCentDedRosen()->getCentDedEkiCont()->getMuPtr();
			CdEkiYColSpecCont aCdYColSpecCont = createYColSpecCont();

			for (int iColumnNumber = 0; iColumnNumber < getCXDcdGrid()->getYColumnCount() && iRv >= 0; iColumnNumber++)
			{
				if (getCSelect()->getYColumnNumberSelected(iColumnNumber))
				{
					CdEkiYColSpec aCdEkiYColSpec = aCdYColSpecCont.ColumnNumberToSpec(iColumnNumber);
					int iEkiIndexSelect = aCdEkiYColSpec.getEkiIndex();
					for (int idx = 0; idx < pCentDedEkiCont->size() && iRv >= 0; idx++)
					{
						if (iEkiIndexSelect != idx)
						{
							if (pCentDedEkiCont->get(idx)->getBrunchCoreEkiIndex() == iEkiIndexSelect)
							{
								iRv = -2; //選択された駅は、他の駅から基幹駅に指定されています
							}
							else if (pCentDedEkiCont->get(idx)->getLoopOriginEkiIndex() == iEkiIndexSelect)
							{
								iRv = -3; //選択された駅は、他の駅から起点駅に指定されています
							}
						}
					}
				}
			}
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
		getCDiagramEditDoc()->CentDedEki_To_Cliboard( 
			pCmd->getCaMuiSelect() ) ;

		// --------------------------------
		//	コマンドオブジェクトの列車を編集
		// --------------------------------
		{
			pCmd->getCaMuiSelect()->erase( 0 , INT_MAX ) ;
		}
		// --------------------------------
		//	コマンドオブジェクトを実行
		// --------------------------------
		{
			getCDiagramEditDoc()->executeEditCmd( pCmd ) ;
		}
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv ;	

}
int CWndDcdGridEki::OnEditCopy_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;
	Ou<CRfEditCmd_Eki> pCmd ;
	Ou<CRfEditCmd_Eki>* ppCmd = NULL ;
	if ( !bQueryEnable ){	ppCmd = &pCmd ;}
	
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if ( iRv >= 0 )
	{
		if ( !createCmd( CWndDcdGridEki::ECreateCmd_Select , ppCmd ) )
		{
			iRv = -1 ;	//	セルの位置が正しくありません。
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
		getCDiagramEditDoc()->CentDedEki_To_Cliboard( 
			pCmd->getCaMuiSelect() ) ;

		// -------------------------------- 
		//	フォーカスセルを、選択要素中で最大の駅Indexの次位に移動
		// --------------------------------
		{
			//	セル選択をクリアし、
			//	フォーカスセルの移動によるセル選択を無効化します。
			clearSelect() ;
			CPropStack	aPropStack( this ) ;
			aPropStack
				.CBoxSelect_setIsEnable( false )
				.CRandomSelect_setIsEnable( false )  ;
		
			//	選択要素中で最大の駅Index を求める
			int iEkiIndexMax = -1 ;
			{
				CaMuiSelect<CentDedEki>* pCaMuiSelect = pCmd->getCaMuiSelect() ;
				for ( int iIndex = pCaMuiSelect->getAdapteeMu()->size() - 1  ; 
					iEkiIndexMax == -1 && iIndex >= 0 ; iIndex -- )
				{
					if ( pCaMuiSelect->getSelect( iIndex ) )
					{
						iEkiIndexMax = iIndex + pCmd->getIndexDst() ;
					}
				}
			}
			//iEkiIndexMax = 選択されている列車のうち、最大のIndex

			//	移動先のフォーカスセル位置を決定
			int iYColumnNmber = -1 ;
			{
				CdEkiYColSpecCont aCdEkiYColSpecCont = createYColSpecCont() ;
				iYColumnNmber = aCdEkiYColSpecCont.ColumnNumberFromSpec( 
					CdEkiYColSpec( CdEkiYColSpec::ColumnType_Eki , iEkiIndexMax ) ) + 1 ;
			}
			//	フォーカスを移動
			{
				CdDcdPosXy posxyFocusCellColumnNumber 
					= getCFocus()->getFocusCellColumnNumber() ;
				if ( iYColumnNmber >= 0 
					&& posxyFocusCellColumnNumber != getCFocus()->ColumnNumberPosXy_NULL() )
				{
					posxyFocusCellColumnNumber.setY( iYColumnNmber ) ;
					getCFocus()->setFocusCellColumnNumber( posxyFocusCellColumnNumber ) ;
				}
			}
		}


		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv ;


}
int CWndDcdGridEki::OnEditPaste_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;
	Ou<CRfEditCmd_Eki> pCmd ;
	Ou<CRfEditCmd_Eki>* ppCmd = NULL ;
	if ( !bQueryEnable ){	ppCmd = &pCmd ;}
	
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if ( iRv >= 0 )
	{
		if ( !createCmd( CWndDcdGridEki::ECreateCmd_NewItem , ppCmd ) )
		{
			iRv = -1 ;	//	セルの位置が正しくありません。
		}
	}
	if ( iRv >= 0 )
	{
		if ( !getCDiagramEditDoc()->CentDedEki_IsClipboardFormatAvailable() &&
			!getCDiagramEditDoc()->UnicodeText_IsClipboardFormatAvailable())
		{
			iRv = -2 ;	//	クリップボードに駅のデータがありません
		}
	}
	// ****************************************************************
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		// -------------------------------- 
		//	クリップボードからデータを取得
		// --------------------------------
		CentDedEkiCont	aEkiCont ;
		iRv = getCDiagramEditDoc()->CentDedEki_From_Cliboard( &aEkiCont ) ;
		if (iRv >= 0 && aEkiCont.size() > 0)
		{
			// --------------------------------
			//	コマンドオブジェクトの駅を編集
			// --------------------------------
			//	CWndDcdGridEki::ECreateCmd_NewItem によって生成された
			//	新規アイテムは削除します。
			pCmd->getCaMuiSelect()->erase( 0 , INT_MAX ) ;

			//	コマンドにクリップボードからのアイテムを追加します。
			CaMui<CentDedEki> aCaMui( pCmd->getCaMuiSelect() ) ;
			aCaMui.insert( &aEkiCont , 0 , INT_MAX , 0 ) ;

			//CaMuiSelect<CentDedEki>* pCaMuiSelect = pCmd->getCaMuiSelect();
			//for (int iIndex = pCaMuiSelect->getAdapteeMu()->size() - 1;
			//	iEkiIndexMax == -1 && iIndex >= 0; iIndex--)
			//{
			//	if (pCaMuiSelect->getSelect(iIndex))
			//	{
			//		iEkiIndexMax = iIndex + pCmd->getIndexDst();
			//	}
			//}

			//アイテム内に、分岐駅設定・環状線設定が有効な駅がある場合は、それを解除します。
			//CaMuiSelect<CentDedEki>* pCaMuiSelect = pCmd->getCaMuiSelect();
			for (int idx = 0; idx < pCmd->getCaMuiSelect()->/*getMuPtr()->*/size(); idx++)
			{
				pCmd->getCaMuiSelect()->getMuPtr()->get(idx)->setBrunchCoreEkiIndex(-1);
				pCmd->getCaMuiSelect()->getMuPtr()->get(idx)->setLoopOriginEkiIndex(-1);
			}
			// --------------------------------
			//	コマンドオブジェクトを実行
			// --------------------------------
			{
				getCDiagramEditDoc()->executeEditCmd(pCmd);
			}
		}

	}
	return iRv ;

}
int CWndDcdGridEki::OnEditClear_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;
	Ou<CRfEditCmd_Eki> pCmd ;
	Ou<CRfEditCmd_Eki>* ppCmd = NULL ;
	if ( !bQueryEnable ){	ppCmd = &pCmd ;}
	
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		bool bRv = getCDiagramEditApp()->getCMainFrame()->RessyabangouDelete(bQueryEnable);
		if (bRv)
		{
			return iRv;
		}
	}
	if ( iRv >= 0 )
	{
		//if (!createCmd(CWndDcdGridEki::ECreateCmd_Focus, ppCmd))
		if ( !createCmd( CWndDcdGridEki::ECreateCmd_Sequence , ppCmd ) )
		{
			iRv = -1 ;	//	セルの位置が正しくありません。
		}
	}
	//被共有対象になっている場合は、コマンド無効です。
	if (iRv >= 0)
	{
		if (getCSelect()->getSelectedCellCount() == 0)
		{
			const Mu< const CentDedEki* >* pCentDedEkiCont = getCDiagramEditDoc()->getCDedRosenFileData()
				->getCentDedRosen()->getCentDedEkiCont()->getMuPtr();
			CdEkiYColSpec aCdEkiYColSpec = getYColSpecOfFocus();
			int iEkiIndexSelect = aCdEkiYColSpec.getEkiIndex();
			for (int idx = 0; idx < pCentDedEkiCont->size() && iRv >= 0; idx++)
			{
				if (iEkiIndexSelect != idx)
				{
					if (pCentDedEkiCont->get(idx)->getBrunchCoreEkiIndex() == iEkiIndexSelect)
					{
						iRv = -2; //選択された駅は、他の駅から基幹駅に指定されています
					}
					else if (pCentDedEkiCont->get(idx)->getLoopOriginEkiIndex() == iEkiIndexSelect)
					{
						iRv = -3; //選択された駅は、他の駅から起点駅に指定されています
					}
				}
			}
		}
		else if (getCSelect()->getSelectedCellCount() > 0)
		{
			const Mu< const CentDedEki* >* pCentDedEkiCont = getCDiagramEditDoc()->getCDedRosenFileData()
				->getCentDedRosen()->getCentDedEkiCont()->getMuPtr();
			CdEkiYColSpecCont aCdYColSpecCont = createYColSpecCont();

			for (int iColumnNumber = 0; iColumnNumber < getCXDcdGrid()->getYColumnCount() && iRv >= 0; iColumnNumber++)
			{
				if (getCSelect()->getYColumnNumberSelected(iColumnNumber))
				{
					CdEkiYColSpec aCdEkiYColSpec = aCdYColSpecCont.ColumnNumberToSpec(iColumnNumber);
					int iEkiIndexSelect = aCdEkiYColSpec.getEkiIndex();
					for (int idx = 0; idx < pCentDedEkiCont->size() && iRv >= 0; idx++)
					{
						if (iEkiIndexSelect != idx)
						{
							if (pCentDedEkiCont->get(idx)->getBrunchCoreEkiIndex() == iEkiIndexSelect)
							{
								iRv = -2; //選択された駅は、他の駅から基幹駅に指定されています
							}
							else if (pCentDedEkiCont->get(idx)->getLoopOriginEkiIndex() == iEkiIndexSelect)
							{
								iRv = -3; //選択された駅は、他の駅から起点駅に指定されています
							}
						}
					}
				}
			}
		}
	}
	// ****************************************************************
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		// --------------------------------
		//	コマンドオブジェクトの列車を編集
		// --------------------------------
		{
			pCmd->getCaMuiSelect()->erase( 0 , INT_MAX ) ;
		}
		// --------------------------------
		//	コマンドオブジェクトを実行
		// --------------------------------
		{
			getCDiagramEditDoc()->executeEditCmd( pCmd ) ;
		}
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv ;	

}

	/*	
		[編集]-[駅を挿入]
	@return
		成功したら0以上、エラーなら負の数です。
	*/
int CWndDcdGridEki:: OnEDITEkiInsert_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if ( execEkiPropDlg( true , TRUE ) < 0 )
	{
		iRv = -1 ;	//	フォーカスの位置が不正です。
	}

	// ****************************************************************
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		execEkiPropDlg( true , FALSE ) ;

		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************
		if ( iRv < 0 )
		{
			CString strErrorMessage ;
			switch( iRv )
			{
			case -1 :	//	現在は実行できません。
				break ;
			default:
				strErrorMessage.Format( _T( "Error=%d" ) , iRv ) ;
				break ;
			}
			if ( strErrorMessage.GetLength() > 0 )
			{
				MessageBox( strErrorMessage , NULL , MB_ICONSTOP | MB_OK ) ; 
			}
		}
		// ****************************************************************
	}
	return iRv ;
}

int CWndDcdGridEki::OnEditEkiInvert_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;

	// ****************************************************************
	//	コマンドの実行可否の判定
	// ****************************************************************
	//	コマンドの実行の可否を判定します。
	//	コマンドが実行不可能なら、 iRv に負の数を設定してください。

	const CentDedRosen*	pCentDedRosen = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen() ;
	const Mu<const CentDedEki*>* pCentDedEkiContGet = pCentDedRosen->getCentDedEkiCont()->getMuPtr() ;
	
	
	// ****************************************************************
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		//	コマンドを実行します。
		//	結果がエラーなら、iRv に負の数を設定します。

		//CentDedRosen	aRosenNew ;
		CDedRosenFileData aCDedRosenFileData = *getCDiagramEditDoc()->getCDedRosenFileData();
		if (iRv >= 0)
		{
			//	路線を取得後、上下を反転します。
			//aRosenNew = *pCentDedRosen ;
			//aRosenNew.invert() ;

			aCDedRosenFileData.getCentDedRosen()->invert();;

			CdDedDispProp aCdDedDispProp = aCDedRosenFileData.getCdDedDispProp();

			bool bOrigin = aCdDedDispProp.getDisplayOuterTerminalO();
			bool bTerminal = aCdDedDispProp.getDisplayOuterTerminalT();
			aCdDedDispProp.setDisplayOuterTerminalO(bTerminal);
			aCdDedDispProp.setDisplayOuterTerminalT(bOrigin);

			aCDedRosenFileData.setCdDedDispProp(aCdDedDispProp);
			//	更新コマンドを生成
		}
		// --------------------------------
		//	コマンドを生成・実行
		// --------------------------------
		if (iRv >= 0)
		{

			OuNew<CRfEditCmd> pCmd(
				new CRfEditCmd_RosenFileData(aCDedRosenFileData)
			);
			getCDiagramEditDoc()->executeEditCmd(pCmd);
		}
		//if ( iRv >= 0 )
		//{
		//	OuNew<CRfEditCmd> pCmd(
		//		new CRfEditCmd_Rosen( aRosenNew )  
		//	);
		//	getCDiagramEditDoc()->executeEditCmd( pCmd ) ;
		//}
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************
		if ( iRv < 0 )
		{
			CString strErrorMessage ;
			switch( iRv )
			{
			case -1 :	//	現在は実行できません。
				break ;
			default:
				strErrorMessage.Format( _T( "Error=%d" ) , iRv ) ;
				break ;
			}
			if ( strErrorMessage.GetLength() > 0 )
			{
				MessageBox( strErrorMessage , NULL , MB_ICONSTOP | MB_OK ) ; 
			}
		}
		// ****************************************************************
	}
	return iRv ;
}

	/*	
		[編集]-[駅のプロパティ]
	*/
int CWndDcdGridEki:: OnEDITEkiProp_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************

	//	フォーカスセルが新規アイテム位置にあるときは、
	//	「新規アイテムのプロパティ入力を行い、それを末尾に挿入する」という
	//	動作になります。
	bool bInsert = false ;
	CdEkiYColSpec aYColSpec = getYColSpecOfFocus() ;
	if ( aYColSpec.getColumnType() == CdEkiYColSpec::ColumnType_NewEki )
	{
		bInsert = true ;
	}

	if ( execEkiPropDlg( bInsert , TRUE ) < 0 )
	{
		iRv = -1 ;	//	-1 ;	//	フォーカスセルの位置が不正です。
	}
	// ****************************************************************
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		//	コマンドを実行します。
		//	結果がエラーなら、iRv に負の数を設定します。

		execEkiPropDlg( bInsert , FALSE ) ;

		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************
		// ****************************************************************
	}
	return iRv ;
}

/*
	[編集]-[交差支障チェックルール編集]
*/
int CWndDcdGridEki::OnEDITCrossingCheckRuleDlg_Process(BOOL bQueryEnable)
{
	int iRv = 0;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************

	//	フォーカスセルが新規アイテム位置にあるときは、
	//	「新規アイテムのプロパティ入力を行い、それを末尾に挿入する」という
	//	動作になります。
	bool bInsert = false;
	CdEkiYColSpec aYColSpec = getYColSpecOfFocus();
	if (aYColSpec.getColumnType() == CdEkiYColSpec::ColumnType_NewEki)
	{
		bInsert = true;
	}

	if (execCrossingCheckRuleDlg(bInsert, TRUE) < 0)
	{
		iRv = -1;	//	-1 ;	//	フォーカスセルの位置が不正です。
	}
	// ****************************************************************
	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		//	コマンドを実行します。
		//	結果がエラーなら、iRv に負の数を設定します。

		execCrossingCheckRuleDlg(bInsert, FALSE);

		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************
		// ****************************************************************
	}
	return iRv;
}


int CWndDcdGridEki::OnEkiSettingNext_Process(BOOL bQueryEnable, int iType)
{
	int iRv = 0;
	Ou<CRfEditCmd_Eki> pCmd;
	Ou<CRfEditCmd_Eki>* ppCmd = NULL;
	if (!bQueryEnable) { ppCmd = &pCmd; }

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (!createCmd(CWndDcdGridEki::ECreateCmd_Select, ppCmd))
		{
			iRv = -1;	//	セルの位置が正しくありません。
		}
	}
	if (iRv >= 0)
	{
		if (!getDisplaySettingMode())
		{
			iRv = -2;	//	表示設定モードではありません。
		}

	}
	if (iRv >= 0)
	{
		CdEkiXColSpec	aXColSpec = getXColSpecOfFocus();
		if (aXColSpec.getColumnType() < CdEkiXColSpec::EColumnType::ColumnType_OperationOriginDownBeforeUpAfter ||
			aXColSpec.getColumnType() > CdEkiXColSpec::EColumnType::ColumnType_OperationTableDisplayJikoku)
		{
			iRv = -3;	//編集可能なのは、前後作業欄設定〜次駅までの背景色の間です。
		}

	}
	// ****************************************************************
	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************

		CdEkiXColSpec	aXColSpec = getXColSpecOfFocus();

		Mu<CentDedEki*>* muCentDedEki = pCmd->getCaMuiSelect()->getMuPtr();
		for (int idx = 0; idx < muCentDedEki->size(); idx++)
		{
			CentDedEki* pCentDedEki = muCentDedEki->get(idx);
			if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_OperationOriginDownBeforeUpAfter)
			{
				//前後作業欄が有効なのは、駅時刻形式が発時刻以外の場合
				//また、前作業欄がない場合は、増解結欄も無しになる。
				if (pCentDedEki->getEkijikokukeisiki() != CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsu&&
					pCentDedEki->getJikokuhyouOperationOrigin() > 0)
				{
					pCentDedEki->setJikokuhyouOperationOriginDownBeforeUpAfter(
						!pCentDedEki->getJikokuhyouOperationOriginDownBeforeUpAfter());
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_OperationOrigin)
			{
				//前後作業欄が有効なのは、駅時刻形式が発時刻以外の場合
				if (pCentDedEki->getEkijikokukeisiki() != CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsu)
				{
					if (pCentDedEki->getJikokuhyouOperationOrigin() >= 3)
					{
						pCentDedEki->setJikokuhyouOperationOrigin(0);
					}
					else
					{
						pCentDedEki->setJikokuhyouOperationOrigin(
							pCentDedEki->getJikokuhyouOperationOrigin() + 1);
					}
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_OperationOriginDownAfterUpBefore)
			{
				//前後作業欄が有効なのは、駅時刻形式が発時刻以外の場合
				//また、前作業欄がない場合は、増解結欄も無しになる。
				if (pCentDedEki->getEkijikokukeisiki() != CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsu &&
					pCentDedEki->getJikokuhyouOperationOrigin() > 0)
				{
					pCentDedEki->setJikokuhyouOperationOriginDownAfterUpBefore(
						!pCentDedEki->getJikokuhyouOperationOriginDownAfterUpBefore());
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_OperationTerminalDownBeforeUpAfter)
			{
				//前後作業欄が有効なのは、駅時刻形式が発時刻以外の場合
				//また、後作業欄がない場合は、増解結欄も無しになる。
				if (pCentDedEki->getEkijikokukeisiki() != CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsu &&
					pCentDedEki->getJikokuhyouOperationTerminal() > 0)
				{
					pCentDedEki->setJikokuhyouOperationTerminalDownBeforeUpAfter(
						!pCentDedEki->getJikokuhyouOperationTerminalDownBeforeUpAfter());
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_OperationTerminal)
			{
				//前後作業欄が有効なのは、駅時刻形式が発時刻以外の場合
				if (pCentDedEki->getEkijikokukeisiki() != CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsu)
				{
					if (pCentDedEki->getJikokuhyouOperationTerminal() >= 3)
					{
						pCentDedEki->setJikokuhyouOperationTerminal(0);
					}
					else
					{
						pCentDedEki->setJikokuhyouOperationTerminal(
							pCentDedEki->getJikokuhyouOperationTerminal() + 1);
					}
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_OperationTerminalDownAfterUpBefore)
			{
				//前後作業欄が有効なのは、駅時刻形式が発時刻以外の場合
				//また、後作業欄がない場合は、増解結欄も無しになる。
				if (pCentDedEki->getEkijikokukeisiki() != CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsu &&
					pCentDedEki->getJikokuhyouOperationTerminal() > 0)
				{
					pCentDedEki->setJikokuhyouOperationTerminalDownAfterUpBefore(
						!pCentDedEki->getJikokuhyouOperationTerminalDownAfterUpBefore());
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_TrackOmit)
			{
				//番線省略が有効なのは、駅時刻形式が発時刻・下り発着・上り発着の場合
				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsu ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
				{
					pCentDedEki->setJikokuhyouTrackOmit(!pCentDedEki->getJikokuhyouTrackOmit());
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_ChakuJikokuDisplayKudari)
			{
				//カスタマイズ時刻表下り着時刻が有効なのは、駅時刻形式が発着・下り着時刻・下り発着の場合
				//ただし、発時刻表示が無効の場合は、着時刻表示を有効→無効に変更しない
				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku)
				{
					if (!pCentDedEki->getJikokuhyouChakuJikokuDisplayKudari())
					{
						pCentDedEki->setJikokuhyouChakuJikokuDisplayKudari(true);
					}
					else if (pCentDedEki->getJikokuhyouHatsuJikokuDisplayKudari())
					{
						pCentDedEki->setJikokuhyouChakuJikokuDisplayKudari(false);
					}
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_TrackDisplayKudari)
			{
				//カスタマイズ時刻表下り番線が有効なのは、駅時刻形式が発着・下り着時刻・上り着時刻・下り発着の場合
				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku)
				{
					pCentDedEki->setJikokuhyouTrackDisplayKudari(
						!pCentDedEki->getJikokuhyouTrackDisplayKudari());
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_HatsuJikokuDisplayKudari)
			{
				//カスタマイズ時刻表下り発時刻が有効なのは、駅時刻形式が下り着時刻以外の場合
				//ただし、着時刻表示が無効の場合は、発時刻表示を有効→無効に変更しない
				if (pCentDedEki->getEkijikokukeisiki() != CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku)
				{
					if (!pCentDedEki->getJikokuhyouHatsuJikokuDisplayKudari())
					{
						pCentDedEki->setJikokuhyouHatsuJikokuDisplayKudari(true);
					}
					else if (pCentDedEki->getJikokuhyouChakuJikokuDisplayKudari())
					{
						pCentDedEki->setJikokuhyouHatsuJikokuDisplayKudari(false);
					}
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_RessyabangouDisplayKudari)
			{
				//カスタマイズ時刻表下り列車番号が有効なのは、駅時刻形式が発着・上り着時刻・下り発着の場合
				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku)
				{
					if (pCentDedEki->getJikokuhyouRessyabangouDisplayKudari() >= 3)
					{
						pCentDedEki->setJikokuhyouRessyabangouDisplayKudari(0);
					}
					else
					{
						pCentDedEki->setJikokuhyouRessyabangouDisplayKudari(
							pCentDedEki->getJikokuhyouRessyabangouDisplayKudari() + 1);
					}
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_OperationNumberDisplayKudari)
			{
				//カスタマイズ時刻表下り運用番号が有効なのは、駅時刻形式が発着・上り着時刻・下り発着の場合
				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku)
				{
					if (pCentDedEki->getJikokuhyouOperationNumberDisplayKudari() >= 4)
					{
						pCentDedEki->setJikokuhyouOperationNumberDisplayKudari(0);
					}
					else
					{
						pCentDedEki->setJikokuhyouOperationNumberDisplayKudari(
							pCentDedEki->getJikokuhyouOperationNumberDisplayKudari() + 1);
					}
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_OperationNumberDisplayRowsKudari)
			{
				//カスタマイズ時刻表下り運用番号が有効なのは、駅時刻形式が発着・上り着時刻・下り発着の場合
				//段数を変更可能なのは、運用番号欄がある場合
				if ((pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku) &&
					pCentDedEki->getJikokuhyouOperationNumberDisplayKudari() > 0)
				{
					if (pCentDedEki->getJikokuhyouOperationNumberDisplayRowsKudari() >= 5)
					{
						pCentDedEki->setJikokuhyouOperationNumberDisplayRowsKudari(1);
					}
					else
					{
						pCentDedEki->setJikokuhyouOperationNumberDisplayRowsKudari(
							pCentDedEki->getJikokuhyouOperationNumberDisplayRowsKudari() + 1);
					}
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_RessyaSyubetsuDisplayKudari)
			{
				//カスタマイズ時刻表下り列車種別が有効なのは、駅時刻形式が発着・上り着時刻・下り発着の場合
				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku)
				{
					if (pCentDedEki->getJikokuhyouRessyaSyubetsuDisplayKudari() >= 3)
					{
						pCentDedEki->setJikokuhyouRessyaSyubetsuDisplayKudari(0);
					}
					else
					{
						pCentDedEki->setJikokuhyouRessyaSyubetsuDisplayKudari(
							pCentDedEki->getJikokuhyouRessyaSyubetsuDisplayKudari() + 1);
					}
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_RessyameiDisplayKudari)
			{
				//カスタマイズ時刻表下り列車名が有効なのは、駅時刻形式が発着・上り着時刻・下り発着の場合
				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku)
				{
					if (pCentDedEki->getJikokuhyouRessyameiDisplayKudari() >= 3)
					{
						pCentDedEki->setJikokuhyouRessyameiDisplayKudari(0);
					}
					else
					{
						pCentDedEki->setJikokuhyouRessyameiDisplayKudari(
							pCentDedEki->getJikokuhyouRessyameiDisplayKudari() + 1);
					}
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_OuterSihatsuDisplayKudari)
			{
				//カスタマイズ時刻表下り路線外・前列車始発駅が有効なのは、駅時刻形式が発着・上り着時刻・下り発着の場合
				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku)
				{
					pCentDedEki->setJikokuhyouOuterSihatsuDisplayKudari(
						!pCentDedEki->getJikokuhyouOuterSihatsuDisplayKudari());
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_OuterShuchakuDisplayKudari)
			{
				//カスタマイズ時刻表下り路線外・次列車終着駅が有効なのは、駅時刻形式が発着・下り着時刻・下り発着の場合
				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku)
				{
					pCentDedEki->setJikokuhyouOuterShuchakuDisplayKudari(
						!pCentDedEki->getJikokuhyouOuterShuchakuDisplayKudari());
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_ChakuJikokuDisplayNobori)
			{
				//カスタマイズ時刻表上り着時刻が有効なのは、駅時刻形式が発着・上り着時刻・上り発着の場合
				//ただし、発時刻表示が無効の場合は、着時刻表示を有効→無効に変更しない
				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
				{
					if (!pCentDedEki->getJikokuhyouChakuJikokuDisplayNobori())
					{
						pCentDedEki->setJikokuhyouChakuJikokuDisplayNobori(true);
					}
					else if (pCentDedEki->getJikokuhyouHatsuJikokuDisplayNobori())
					{
						pCentDedEki->setJikokuhyouChakuJikokuDisplayNobori(false);
					}
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_TrackDisplayNobori)
			{
				//カスタマイズ時刻表上り番線が有効なのは、駅時刻形式が発着・下り着時刻・上り着時刻・上り発着の場合
				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
				{
					pCentDedEki->setJikokuhyouTrackDisplayNobori(
						!pCentDedEki->getJikokuhyouTrackDisplayNobori());
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_HatsuJikokuDisplayNobori)
			{
				//カスタマイズ時刻表上り発時刻が有効なのは、駅時刻形式が上り着時刻以外の場合
				//ただし、着時刻表示が無効の場合は、発時刻表示を有効→無効に変更しない
				if (pCentDedEki->getEkijikokukeisiki() != CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku)
				{
					if (!pCentDedEki->getJikokuhyouHatsuJikokuDisplayNobori())
					{
						pCentDedEki->setJikokuhyouHatsuJikokuDisplayNobori(true);
					}
					else if (pCentDedEki->getJikokuhyouChakuJikokuDisplayNobori())
					{
						pCentDedEki->setJikokuhyouHatsuJikokuDisplayNobori(false);
					}
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_RessyabangouDisplayNobori)
			{
				//カスタマイズ時刻表上り列車番号が有効なのは、駅時刻形式が発着・下り着時刻・上り発着の場合
				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
				{
					if (pCentDedEki->getJikokuhyouRessyabangouDisplayNobori() >= 3)
					{
						pCentDedEki->setJikokuhyouRessyabangouDisplayNobori(0);
					}
					else
					{
						pCentDedEki->setJikokuhyouRessyabangouDisplayNobori(
							pCentDedEki->getJikokuhyouRessyabangouDisplayNobori() + 1);
					}
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_OperationNumberDisplayNobori)
			{
				//カスタマイズ時刻表上り運用番号が有効なのは、駅時刻形式が発着・下り着時刻・上り発着の場合
				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
				{
					if (pCentDedEki->getJikokuhyouOperationNumberDisplayNobori() >= 4)
					{
						pCentDedEki->setJikokuhyouOperationNumberDisplayNobori(0);
					}
					else
					{
						pCentDedEki->setJikokuhyouOperationNumberDisplayNobori(
							pCentDedEki->getJikokuhyouOperationNumberDisplayNobori() + 1);
					}
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_OperationNumberDisplayRowsNobori)
			{
				//カスタマイズ時刻表上り運用番号が有効なのは、駅時刻形式が発着・下り着時刻・上り発着の場合
				if ((pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)&&
					pCentDedEki->getJikokuhyouOperationNumberDisplayNobori() > 0)
				{
					if (pCentDedEki->getJikokuhyouOperationNumberDisplayRowsNobori() >= 5)
					{
						pCentDedEki->setJikokuhyouOperationNumberDisplayRowsNobori(1);
					}
					else
					{
						pCentDedEki->setJikokuhyouOperationNumberDisplayRowsNobori(
							pCentDedEki->getJikokuhyouOperationNumberDisplayRowsNobori() + 1);
					}
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_RessyaSyubetsuDisplayNobori)
			{
				//カスタマイズ時刻表上り列車種別が有効なのは、駅時刻形式が発着・下り着時刻・上り発着の場合
				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
				{
					if (pCentDedEki->getJikokuhyouRessyaSyubetsuDisplayNobori() >= 3)
					{
						pCentDedEki->setJikokuhyouRessyaSyubetsuDisplayNobori(0);
					}
					else
					{
						pCentDedEki->setJikokuhyouRessyaSyubetsuDisplayNobori(
							pCentDedEki->getJikokuhyouRessyaSyubetsuDisplayNobori() + 1);
					}
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_RessyameiDisplayNobori)
			{
				//カスタマイズ時刻表上り列車名が有効なのは、駅時刻形式が発着・下り着時刻・上り発着の場合
				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
				{
					if (pCentDedEki->getJikokuhyouRessyameiDisplayNobori() >= 3)
					{
						pCentDedEki->setJikokuhyouRessyameiDisplayNobori(0);
					}
					else
					{
						pCentDedEki->setJikokuhyouRessyameiDisplayNobori(
							pCentDedEki->getJikokuhyouRessyameiDisplayNobori() + 1);
					}
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_OuterSihatsuDisplayNobori)
			{
				//カスタマイズ時刻表上り路線外・前列車始発駅が有効なのは、駅時刻形式が発着・下り着時刻・上り発着の場合
				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
				{
					pCentDedEki->setJikokuhyouOuterSihatsuDisplayNobori(
						!pCentDedEki->getJikokuhyouOuterSihatsuDisplayNobori());
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_OuterShuchakuDisplayNobori)
			{
				//カスタマイズ時刻表上り路線外・次列車終着駅が有効なのは、駅時刻形式が発着・上り着時刻・上り発着の場合
				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
				{
					pCentDedEki->setJikokuhyouOuterShuchakuDisplayNobori(
						!pCentDedEki->getJikokuhyouOuterShuchakuDisplayNobori());
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_DiagramTrackDisplay)
			{
				//在線表表示が有効なのは、駅時刻形式が発着・下り着時刻・上り着時刻かつ主要駅の場合
				if ((pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku) &&
					pCentDedEki->getEkikibo() == CentDedEki::EEkikibo::Ekikibo_Syuyou)
				{
					pCentDedEki->setDiagramTrackDisplay(!pCentDedEki->getDiagramTrackDisplay());
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_DiagramRessyajouhouHyoujiKudari)
			{
				//ダイヤグラム列車情報表示(下り)
				if (pCentDedEki->getDiagramRessyajouhouHyoujiKudari() == CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Origin)
				{
					pCentDedEki->setDiagramRessyajouhouHyoujiKudari(CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Anytime);
				}
				else if (pCentDedEki->getDiagramRessyajouhouHyoujiKudari() == CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Anytime)
				{
					pCentDedEki->setDiagramRessyajouhouHyoujiKudari(CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Not);
				}
				else if (pCentDedEki->getDiagramRessyajouhouHyoujiKudari() == CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Not)
				{
					pCentDedEki->setDiagramRessyajouhouHyoujiKudari(CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Origin);
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_DiagramRessyajouhouHyoujiNobori)
			{
				//ダイヤグラム列車情報表示(上り)
				if (pCentDedEki->getDiagramRessyajouhouHyoujiNobori() == CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Origin)
				{
					pCentDedEki->setDiagramRessyajouhouHyoujiNobori(CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Anytime);
				}
				else if (pCentDedEki->getDiagramRessyajouhouHyoujiNobori() == CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Anytime)
				{
					pCentDedEki->setDiagramRessyajouhouHyoujiNobori(CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Not);
				}
				else if (pCentDedEki->getDiagramRessyajouhouHyoujiNobori() == CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Not)
				{
					pCentDedEki->setDiagramRessyajouhouHyoujiNobori(CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Origin);
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_NextEkiDistance)
			{
				//この駅から次の駅までの距離
				//iTypeによって加算時間を変えて、ChangeNextEkiDistanceを実行する。
				int iShiftSecond = 0;
				if (iType == 0)
				{
					iShiftSecond = 60;
				}
				else if (iType == 1)
				{
					CdDedDispProp aCdDedDispProp = getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
					iShiftSecond = aCdDedDispProp.getAnySecondIncDec1();
				}
				else if (iType == 2)
				{
					CdDedDispProp aCdDedDispProp = getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
					iShiftSecond = aCdDedDispProp.getAnySecondIncDec2();
				}
				ChangeNextEkiDistance(pCentDedEki,iShiftSecond);
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_DiagramColorNextEki)
			{
				//この駅から次の駅までの背景色設定
				if (pCentDedEki->getDiagramColorNextEki() >= 4)
				{
					pCentDedEki->setDiagramColorNextEki(0);
				}
				else
				{
					pCentDedEki->setDiagramColorNextEki(
						pCentDedEki->getDiagramColorNextEki() + 1);
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_OperationTableDisplayJikoku)
			{
				//箱ダイヤで表示するか否か
				if (pCentDedEki->getBrunchCoreEkiIndex() == -1)
				{
					pCentDedEki->setOperationTableDisplayJikoku(!pCentDedEki->getOperationTableDisplayJikoku());
				}
			}

			vector<int> iEkiTrack2Map;
			vector<int> iOuterTerminalEkimeiMap;
			//駅番線の変更処理のためのMapを初期化する
			for (int idx = 0; idx < pCentDedEki->getEkiTrack2Cont()->size(); idx++)
			{
				iEkiTrack2Map.push_back(idx);
			}
			//路線外発着駅の変更処理のためのMapを初期化する
			for (int idx = 0; idx < pCentDedEki->getOuterTerminalEkimeiCount(); idx++)
			{
				iOuterTerminalEkimeiMap.push_back(idx);
			}
			pCmd->setEkiTrack2Map(iEkiTrack2Map);
			pCmd->setOuterTerminalEkimeiMap(iOuterTerminalEkimeiMap);
		}

		if (iRv >= 0)
		{
			// --------------------------------
			//	編集コマンドを実行
			// --------------------------------
			getCDiagramEditDoc()->executeEditCmd(pCmd);
		}

		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv;
}
int CWndDcdGridEki::OnEkiSettingPrev_Process(BOOL bQueryEnable, int iType)
{
	int iRv = 0;
	Ou<CRfEditCmd_Eki> pCmd;
	Ou<CRfEditCmd_Eki>* ppCmd = NULL;
	if (!bQueryEnable) { ppCmd = &pCmd; }

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (!createCmd(CWndDcdGridEki::ECreateCmd_Select, ppCmd))
		{
			iRv = -1;	//	セルの位置が正しくありません。
		}
	}
	if (iRv >= 0)
	{
		if (!getDisplaySettingMode())
		{
			iRv = -2;	//	表示設定モードではありません。
		}

	}
	if (iRv >= 0)
	{
		CdEkiXColSpec	aXColSpec = getXColSpecOfFocus();
		if (aXColSpec.getColumnType() < CdEkiXColSpec::EColumnType::ColumnType_OperationOriginDownBeforeUpAfter ||
			aXColSpec.getColumnType() > CdEkiXColSpec::EColumnType::ColumnType_OperationTableDisplayJikoku)
		{
			iRv = -3;	//編集可能なのは、前後作業欄設定〜次駅までの背景色の間です。
		}

	}
	// ****************************************************************
	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************

		CdEkiXColSpec	aXColSpec = getXColSpecOfFocus();

		Mu<CentDedEki*>* muCentDedEki = pCmd->getCaMuiSelect()->getMuPtr();
		for (int idx = 0; idx < muCentDedEki->size(); idx++)
		{
			CentDedEki* pCentDedEki = muCentDedEki->get(idx);
			if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_OperationOriginDownBeforeUpAfter)
			{
				//前後作業欄が有効なのは、駅時刻形式が発時刻以外の場合
				//また、前作業欄がない場合は、増解結欄も無しになる。
				if (pCentDedEki->getEkijikokukeisiki() != CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsu &&
					pCentDedEki->getJikokuhyouOperationOrigin() > 0)
				{
					pCentDedEki->setJikokuhyouOperationOriginDownBeforeUpAfter(
						!pCentDedEki->getJikokuhyouOperationOriginDownBeforeUpAfter());
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_OperationOrigin)
			{
				//前後作業欄が有効なのは、駅時刻形式が発時刻以外の場合
				if (pCentDedEki->getEkijikokukeisiki() != CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsu)
				{
					if (pCentDedEki->getJikokuhyouOperationOrigin() <= 0)
					{
						pCentDedEki->setJikokuhyouOperationOrigin(3);
					}
					else
					{
						pCentDedEki->setJikokuhyouOperationOrigin(
							pCentDedEki->getJikokuhyouOperationOrigin() - 1);
					}
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_OperationOriginDownAfterUpBefore)
			{
				//前後作業欄が有効なのは、駅時刻形式が発時刻以外の場合
				//また、前作業欄がない場合は、増解結欄も無しになる。
				if (pCentDedEki->getEkijikokukeisiki() != CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsu &&
					pCentDedEki->getJikokuhyouOperationOrigin() > 0)
				{
					pCentDedEki->setJikokuhyouOperationOriginDownAfterUpBefore(
						!pCentDedEki->getJikokuhyouOperationOriginDownAfterUpBefore());
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_OperationTerminalDownBeforeUpAfter)
			{
				//前後作業欄が有効なのは、駅時刻形式が発時刻以外の場合
				//また、後作業欄がない場合は、増解結欄も無しになる。
				if (pCentDedEki->getEkijikokukeisiki() != CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsu &&
					pCentDedEki->getJikokuhyouOperationTerminal() > 0)
				{
					pCentDedEki->setJikokuhyouOperationTerminalDownBeforeUpAfter(
						!pCentDedEki->getJikokuhyouOperationTerminalDownBeforeUpAfter());
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_OperationTerminal)
			{
				//前後作業欄が有効なのは、駅時刻形式が発時刻以外の場合
				if (pCentDedEki->getEkijikokukeisiki() != CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsu)
				{
					if (pCentDedEki->getJikokuhyouOperationTerminal() <= 0)
					{
						pCentDedEki->setJikokuhyouOperationTerminal(3);
					}
					else
					{
						pCentDedEki->setJikokuhyouOperationTerminal(
							pCentDedEki->getJikokuhyouOperationTerminal() - 1);
					}
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_OperationTerminalDownAfterUpBefore)
			{
				//前後作業欄が有効なのは、駅時刻形式が発時刻以外の場合
				//また、後作業欄がない場合は、増解結欄も無しになる。
				if (pCentDedEki->getEkijikokukeisiki() != CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsu &&
					pCentDedEki->getJikokuhyouOperationTerminal() > 0)
				{
					pCentDedEki->setJikokuhyouOperationTerminalDownAfterUpBefore(
						!pCentDedEki->getJikokuhyouOperationTerminalDownAfterUpBefore());
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_TrackOmit)
			{
				//番線省略が有効なのは、駅時刻形式が発時刻・下り発着・上り発着の場合
				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsu ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
				{
					pCentDedEki->setJikokuhyouTrackOmit(!pCentDedEki->getJikokuhyouTrackOmit());
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_ChakuJikokuDisplayKudari)
			{
				//カスタマイズ時刻表下り着時刻が有効なのは、駅時刻形式が発着・下り着時刻・下り発着の場合
				//ただし、発時刻表示が無効の場合は、着時刻表示を有効→無効に変更しない
				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku)
				{
					if (!pCentDedEki->getJikokuhyouChakuJikokuDisplayKudari())
					{
						pCentDedEki->setJikokuhyouChakuJikokuDisplayKudari(true);
					}
					else if (pCentDedEki->getJikokuhyouHatsuJikokuDisplayKudari())
					{
						pCentDedEki->setJikokuhyouChakuJikokuDisplayKudari(false);
					}
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_TrackDisplayKudari)
			{
				//カスタマイズ時刻表下り番線が有効なのは、駅時刻形式が発着・下り着時刻・上り着時刻・下り発着の場合
				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku)
				{
					pCentDedEki->setJikokuhyouTrackDisplayKudari(
						!pCentDedEki->getJikokuhyouTrackDisplayKudari());
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_HatsuJikokuDisplayKudari)
			{
				//カスタマイズ時刻表下り発時刻が有効なのは、駅時刻形式が下り着時刻以外の場合
				//ただし、着時刻表示が無効の場合は、発時刻表示を有効→無効に変更しない
				if (pCentDedEki->getEkijikokukeisiki() != CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku)
				{
					if (!pCentDedEki->getJikokuhyouHatsuJikokuDisplayKudari())
					{
						pCentDedEki->setJikokuhyouHatsuJikokuDisplayKudari(true);
					}
					else if (pCentDedEki->getJikokuhyouChakuJikokuDisplayKudari())
					{
						pCentDedEki->setJikokuhyouHatsuJikokuDisplayKudari(false);
					}
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_RessyabangouDisplayKudari)
			{
				//カスタマイズ時刻表下り列車番号が有効なのは、駅時刻形式が発着・上り着時刻・下り発着の場合
				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku)
				{
					if (pCentDedEki->getJikokuhyouRessyabangouDisplayKudari() <= 0)
					{
						pCentDedEki->setJikokuhyouRessyabangouDisplayKudari(3);
					}
					else
					{
						pCentDedEki->setJikokuhyouRessyabangouDisplayKudari(
							pCentDedEki->getJikokuhyouRessyabangouDisplayKudari() - 1);
					}
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_OperationNumberDisplayKudari)
			{
				//カスタマイズ時刻表下り運用番号が有効なのは、駅時刻形式が発着・上り着時刻・下り発着の場合
				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku)
				{
					if (pCentDedEki->getJikokuhyouOperationNumberDisplayKudari() <= 0)
					{
						pCentDedEki->setJikokuhyouOperationNumberDisplayKudari(4);
					}
					else
					{
						pCentDedEki->setJikokuhyouOperationNumberDisplayKudari(
							pCentDedEki->getJikokuhyouOperationNumberDisplayKudari() -1);
					}
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_OperationNumberDisplayRowsKudari)
			{
				//カスタマイズ時刻表下り運用番号が有効なのは、駅時刻形式が発着・上り着時刻・下り発着の場合
				//段数を変更可能なのは、運用番号欄がある場合
				if ((pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku) &&
					pCentDedEki->getJikokuhyouOperationNumberDisplayKudari() > 0)
				{
					if (pCentDedEki->getJikokuhyouOperationNumberDisplayRowsKudari() <= 1)
					{
						pCentDedEki->setJikokuhyouOperationNumberDisplayRowsKudari(5);
					}
					else
					{
						pCentDedEki->setJikokuhyouOperationNumberDisplayRowsKudari(
							pCentDedEki->getJikokuhyouOperationNumberDisplayRowsKudari() - 1);
					}
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_RessyaSyubetsuDisplayKudari)
			{
				//カスタマイズ時刻表下り列車種別が有効なのは、駅時刻形式が発着・上り着時刻・下り発着の場合
				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku)
				{
					if (pCentDedEki->getJikokuhyouRessyaSyubetsuDisplayKudari() <= 0)
					{
						pCentDedEki->setJikokuhyouRessyaSyubetsuDisplayKudari(3);
					}
					else
					{
						pCentDedEki->setJikokuhyouRessyaSyubetsuDisplayKudari(
							pCentDedEki->getJikokuhyouRessyaSyubetsuDisplayKudari() - 1);
					}
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_RessyameiDisplayKudari)
			{
				//カスタマイズ時刻表下り列車名が有効なのは、駅時刻形式が発着・上り着時刻・下り発着の場合
				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku)
				{
					if (pCentDedEki->getJikokuhyouRessyameiDisplayKudari() <= 0)
					{
						pCentDedEki->setJikokuhyouRessyameiDisplayKudari(3);
					}
					else
					{
						pCentDedEki->setJikokuhyouRessyameiDisplayKudari(
							pCentDedEki->getJikokuhyouRessyameiDisplayKudari() - 1);
					}
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_OuterSihatsuDisplayKudari)
			{
				//カスタマイズ時刻表下り路線外・前列車始発駅が有効なのは、駅時刻形式が発着・上り着時刻・下り発着の場合
				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku)
				{
					pCentDedEki->setJikokuhyouOuterSihatsuDisplayKudari(
						!pCentDedEki->getJikokuhyouOuterSihatsuDisplayKudari());
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_OuterShuchakuDisplayKudari)
			{
				//カスタマイズ時刻表下り路線外・次列車終着駅が有効なのは、駅時刻形式が発着・下り着時刻・下り発着の場合
				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku)
				{
					pCentDedEki->setJikokuhyouOuterShuchakuDisplayKudari(
						!pCentDedEki->getJikokuhyouOuterShuchakuDisplayKudari());
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_ChakuJikokuDisplayNobori)
			{
				//カスタマイズ時刻表上り着時刻が有効なのは、駅時刻形式が発着・上り着時刻・上り発着の場合
				//ただし、発時刻表示が無効の場合は、着時刻表示を有効→無効に変更しない
				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
				{
					if (!pCentDedEki->getJikokuhyouChakuJikokuDisplayNobori())
					{
						pCentDedEki->setJikokuhyouChakuJikokuDisplayNobori(true);
					}
					else if (pCentDedEki->getJikokuhyouHatsuJikokuDisplayNobori())
					{
						pCentDedEki->setJikokuhyouChakuJikokuDisplayNobori(false);
					}
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_TrackDisplayNobori)
			{
				//カスタマイズ時刻表上り番線が有効なのは、駅時刻形式が発着・下り着時刻・上り着時刻・上り発着の場合
				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
				{
					pCentDedEki->setJikokuhyouTrackDisplayNobori(
						!pCentDedEki->getJikokuhyouTrackDisplayNobori());
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_HatsuJikokuDisplayNobori)
			{
				//カスタマイズ時刻表上り発時刻が有効なのは、駅時刻形式が上り着時刻以外の場合
				//ただし、着時刻表示が無効の場合は、発時刻表示を有効→無効に変更しない
				if (pCentDedEki->getEkijikokukeisiki() != CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku)
				{
					if (!pCentDedEki->getJikokuhyouHatsuJikokuDisplayNobori())
					{
						pCentDedEki->setJikokuhyouHatsuJikokuDisplayNobori(true);
					}
					else if (pCentDedEki->getJikokuhyouChakuJikokuDisplayNobori())
					{
						pCentDedEki->setJikokuhyouHatsuJikokuDisplayNobori(false);
					}
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_RessyabangouDisplayNobori)
			{
				//カスタマイズ時刻表上り列車番号が有効なのは、駅時刻形式が発着・下り着時刻・上り発着の場合
				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
				{
					if (pCentDedEki->getJikokuhyouRessyabangouDisplayNobori() <= 0)
					{
						pCentDedEki->setJikokuhyouRessyabangouDisplayNobori(3);
					}
					else
					{
						pCentDedEki->setJikokuhyouRessyabangouDisplayNobori(
							pCentDedEki->getJikokuhyouRessyabangouDisplayNobori() - 1);
					}
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_OperationNumberDisplayNobori)
			{
				//カスタマイズ時刻表上り運用番号が有効なのは、駅時刻形式が発着・下り着時刻・上り発着の場合
				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
				{
					if (pCentDedEki->getJikokuhyouOperationNumberDisplayNobori() <= 0)
					{
						pCentDedEki->setJikokuhyouOperationNumberDisplayNobori(4);
					}
					else
					{
						pCentDedEki->setJikokuhyouOperationNumberDisplayNobori(
							pCentDedEki->getJikokuhyouOperationNumberDisplayNobori() - 1);
					}
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_OperationNumberDisplayRowsNobori)
			{
				//カスタマイズ時刻表上り運用番号が有効なのは、駅時刻形式が発着・下り着時刻・上り発着の場合
				if ((pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku) &&
					pCentDedEki->getJikokuhyouOperationNumberDisplayNobori() > 0)
				{
					if (pCentDedEki->getJikokuhyouOperationNumberDisplayRowsNobori() <= 1)
					{
						pCentDedEki->setJikokuhyouOperationNumberDisplayRowsNobori(5);
					}
					else
					{
						pCentDedEki->setJikokuhyouOperationNumberDisplayRowsNobori(
							pCentDedEki->getJikokuhyouOperationNumberDisplayRowsNobori() - 1);
					}
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_RessyaSyubetsuDisplayNobori)
			{
				//カスタマイズ時刻表上り列車種別が有効なのは、駅時刻形式が発着・下り着時刻・上り発着の場合
				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
				{
					if (pCentDedEki->getJikokuhyouRessyaSyubetsuDisplayNobori() <= 0)
					{
						pCentDedEki->setJikokuhyouRessyaSyubetsuDisplayNobori(3);
					}
					else
					{
						pCentDedEki->setJikokuhyouRessyaSyubetsuDisplayNobori(
							pCentDedEki->getJikokuhyouRessyaSyubetsuDisplayNobori() - 1);
					}
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_RessyameiDisplayNobori)
			{
				//カスタマイズ時刻表上り列車名が有効なのは、駅時刻形式が発着・下り着時刻・上り発着の場合
				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
				{
					if (pCentDedEki->getJikokuhyouRessyameiDisplayNobori() <= 0)
					{
						pCentDedEki->setJikokuhyouRessyameiDisplayNobori(3);
					}
					else
					{
						pCentDedEki->setJikokuhyouRessyameiDisplayNobori(
							pCentDedEki->getJikokuhyouRessyameiDisplayNobori() - 1);
					}
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_OuterSihatsuDisplayNobori)
			{
				//カスタマイズ時刻表上り路線外・前列車始発駅が有効なのは、駅時刻形式が発着・下り着時刻・上り発着の場合
				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
				{
					pCentDedEki->setJikokuhyouOuterSihatsuDisplayNobori(
						!pCentDedEki->getJikokuhyouOuterSihatsuDisplayNobori());
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_OuterShuchakuDisplayNobori)
			{
				//カスタマイズ時刻表上り路線外・次列車終着駅が有効なのは、駅時刻形式が発着・上り着時刻・上り発着の場合
				if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
				{
					pCentDedEki->setJikokuhyouOuterShuchakuDisplayNobori(
						!pCentDedEki->getJikokuhyouOuterShuchakuDisplayNobori());
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_DiagramTrackDisplay)
			{
				//在線表表示が有効なのは、駅時刻形式が発着・下り着時刻・上り着時刻かつ主要駅の場合
				if ((pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
					pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku) &&
					pCentDedEki->getEkikibo() == CentDedEki::EEkikibo::Ekikibo_Syuyou)
				{
					pCentDedEki->setDiagramTrackDisplay(!pCentDedEki->getDiagramTrackDisplay());
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_DiagramRessyajouhouHyoujiKudari)
			{
				//ダイヤグラム列車情報表示(下り)
				if (pCentDedEki->getDiagramRessyajouhouHyoujiKudari() == CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Origin)
				{
					pCentDedEki->setDiagramRessyajouhouHyoujiKudari(CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Not);
				}
				else if (pCentDedEki->getDiagramRessyajouhouHyoujiKudari() == CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Anytime)
				{
					pCentDedEki->setDiagramRessyajouhouHyoujiKudari(CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Origin);
				}
				else if (pCentDedEki->getDiagramRessyajouhouHyoujiKudari() == CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Not)
				{
					pCentDedEki->setDiagramRessyajouhouHyoujiKudari(CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Anytime);
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_DiagramRessyajouhouHyoujiNobori)
			{
				//ダイヤグラム列車情報表示(上り)
				if (pCentDedEki->getDiagramRessyajouhouHyoujiNobori() == CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Origin)
				{
					pCentDedEki->setDiagramRessyajouhouHyoujiNobori(CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Not);
				}
				else if (pCentDedEki->getDiagramRessyajouhouHyoujiNobori() == CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Anytime)
				{
					pCentDedEki->setDiagramRessyajouhouHyoujiNobori(CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Origin);
				}
				else if (pCentDedEki->getDiagramRessyajouhouHyoujiNobori() == CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Not)
				{
					pCentDedEki->setDiagramRessyajouhouHyoujiNobori(CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Anytime);
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_NextEkiDistance)
			{
				//この駅から次の駅までの距離
				//iTypeによって加算時間を変えて、ChangeNextEkiDistanceを実行する。
				int iShiftSecond = 0;
				if (iType == 0)
				{
					iShiftSecond = -60;
				}
				else if (iType == 1)
				{
					CdDedDispProp aCdDedDispProp = getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
					iShiftSecond = -aCdDedDispProp.getAnySecondIncDec1();
				}
				else if (iType == 2)
				{
					CdDedDispProp aCdDedDispProp = getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
					iShiftSecond = -aCdDedDispProp.getAnySecondIncDec2();
				}
				ChangeNextEkiDistance(pCentDedEki, iShiftSecond);
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_DiagramColorNextEki)
			{
				//この駅から次の駅までの背景色設定
				if (pCentDedEki->getDiagramColorNextEki() <= 0)
				{
					pCentDedEki->setDiagramColorNextEki(4);
				}
				else
				{
					pCentDedEki->setDiagramColorNextEki(
						pCentDedEki->getDiagramColorNextEki() - 1);
				}
			}
			else if (aXColSpec.getColumnType() == CdEkiXColSpec::EColumnType::ColumnType_OperationTableDisplayJikoku)
			{
				//箱ダイヤで表示するか否か
				if (pCentDedEki->getBrunchCoreEkiIndex() == -1)
				{
					pCentDedEki->setOperationTableDisplayJikoku(!pCentDedEki->getOperationTableDisplayJikoku());
				}
			}

			vector<int> iEkiTrack2Map;
			vector<int> iOuterTerminalEkimeiMap;
			//駅番線の変更処理のためのMapを初期化する
			for (int idx = 0; idx < pCentDedEki->getEkiTrack2Cont()->size(); idx++)
			{
				iEkiTrack2Map.push_back(idx);
			}
			//路線外発着駅の変更処理のためのMapを初期化する
			for (int idx = 0; idx < pCentDedEki->getOuterTerminalEkimeiCount(); idx++)
			{
				iOuterTerminalEkimeiMap.push_back(idx);
			}
			pCmd->setEkiTrack2Map(iEkiTrack2Map);
			pCmd->setOuterTerminalEkimeiMap(iOuterTerminalEkimeiMap);
		}

		if (iRv >= 0)
		{
			// --------------------------------
			//	編集コマンドを実行
			// --------------------------------
			getCDiagramEditDoc()->executeEditCmd(pCmd);
		}

		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv;
}
void CWndDcdGridEki::ChangeNextEkiDistance(CentDedEki* pCentDedEki, int iShiftSecond)
{
	int iNextEkiDistance = pCentDedEki->getNextEkiDistance();
	iNextEkiDistance += iShiftSecond;
	if (iNextEkiDistance < 0)
	{
		iNextEkiDistance = 0;
	}
	if (iNextEkiDistance > 7200)
	{
		iNextEkiDistance = 7200;
	}
	pCentDedEki->setNextEkiDistance(iNextEkiDistance);
}
// ********************************
//	コンストラクタ
// ********************************
CWndDcdGridEki::CWndDcdGridEki()
	: m_bAdjustByEkijikokukeisiki( true ) 
 	, m_bWaitForActivate( true )
	, m_bInitialUpdateComplete( false )
	, m_bDisplaySettingMode(false)
{
	getCSelect()->setSelectMode( CSelect::SelectMode_YColumn ) ;

}
CWndDcdGridEki::‾CWndDcdGridEki()
{
}

	// ********************************
	//@name CWndDcdGridEki-属性
	// ********************************
bool CWndDcdGridEki::getAdjustByEkijikokukeisiki()const 
{
	return m_bAdjustByEkijikokukeisiki ;
}
int CWndDcdGridEki::setAdjustByEkijikokukeisiki( bool value ) 
{
	int iRv = 0 ;
	if ( m_bAdjustByEkijikokukeisiki != value )
	{
		m_bAdjustByEkijikokukeisiki = value ;

		//	.ini ファイルに保存
		getCDiagramEditApp()->writeCWndDcdGridEkiProp( this ) ;
		
		iRv = 1 ;
	}
	return iRv ;
}



	// ********************************
	//@name CEkiView からの委譲
	// ********************************
void CWndDcdGridEki::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
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
		getCDiagramEditApp()->readCWndDcdGridEkiProp( this ) ;
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
			dynamic_castOu<CRfEditCmd_DiaProp>( pCmd ) || 
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
		//17.12.6カーソル位置の問題があるため、戻します
		else if (dynamic_castOu<CRfEditCmd_Eki>(pCmd))
		{

			//		駅の変更
			Ou<CRfEditCmd_Eki>	pCommand
				= dynamic_castOu<CRfEditCmd_Eki>(pCmd);

			//	コマンドオブジェクト実行によるセル移動でセル選択にならないように、
			//	セル選択を解除し、セル選択機能も一時的に中止します。
			if (pCommand->getCaMuiSelect()->size() == 1)
			{
				clearSelect();
				CPropStack aPropStack(this);
				aPropStack
					.CBoxSelect_setIsEnable(false)
					.CRandomSelect_setIsEnable(false);
			}

			// --------------------------------
			//	減少分の要素の削除
			// --------------------------------
			CentDedEkiCont	aCentDedEkiContSrc 
				= *pCommand->getCentDedEkiContSrc() ;
			int iGensyouSize = 
				pCommand->getSizeDst() - aCentDedEkiContSrc.size() ;
			if ( iGensyouSize > 0 ){
				for ( int cnt = 0 ; cnt < iGensyouSize ; cnt ++ ){
					getCXDcdGrid()->eraseYColumn( 
						pCommand->getIndexDst() + 
						pCommand->getSizeDst() - iGensyouSize 
						+ 1 ) ;
				}
			}
			// --------------------------------
			//	増加分の要素の追加
			// --------------------------------
			int iOkikaeSize = 0 ;
			iOkikaeSize = 
				min( pCommand->getSizeDst() , aCentDedEkiContSrc.size() ) ;
			int iZoukaSize = 
				aCentDedEkiContSrc.size() - pCommand->getSizeDst() ;
			if ( iZoukaSize > 0 )
			{
				for ( int cnt = 0 ; cnt < iZoukaSize ; cnt ++ )
				{
					getCXDcdGrid()->insertYColumn( 
						pCommand->getIndexDst() + iOkikaeSize + cnt + 1 , 
						true ) ; 
				}
			}
			// --------------------------------
			//	要素の更新
			// --------------------------------
			//境界線の設定のため、一つ前も更新する。
			{
				/*for ( int cnt = 0 ; cnt < aCentDedEkiContSrc.size() ; cnt ++ )
				{
					int iEkiIndex = pCommand->getIndexDst() + cnt ;
					const CentDedEki*	pCentDedEki 
						= pCentDedEkiContGet->get( iEkiIndex ) ;
					if (iEkiIndex == 0 &&
						pCentDedEkiContGet->size()>1)
					{
						const CentDedEki*	pCentDedEkiNext
							= pCentDedEkiContGet->get(iEkiIndex + 1);
						OnUpdate_setCentDedEki_To_Column(
							iEkiIndex + 1, *pCentDedEki, *pCentDedEkiNext);
					}
					else if (iEkiIndex == 0 )
					{
						OnUpdate_setCentDedEki_To_Column(
							iEkiIndex + 1, *pCentDedEki, CentDedEki());
					}
					else if (iEkiIndex < pCentDedEkiContGet->size()-1)
					{
						const CentDedEki*	pCentDedEkiPrev
							= pCentDedEkiContGet->get(iEkiIndex - 1);
						const CentDedEki*	pCentDedEkiNext 
							= pCentDedEkiContGet->get(iEkiIndex + 1);
						OnUpdate_setCentDedEki_To_Column(
							iEkiIndex , *pCentDedEkiPrev, *pCentDedEki);
						OnUpdate_setCentDedEki_To_Column(
							iEkiIndex + 1, *pCentDedEki, *pCentDedEkiNext);
					}
					else
					{
						const CentDedEki*	pCentDedEkiPrev
							= pCentDedEkiContGet->get(iEkiIndex - 1);
						OnUpdate_setCentDedEki_To_Column(
							iEkiIndex, *pCentDedEkiPrev, *pCentDedEki);
						OnUpdate_setCentDedEki_To_Column(
							iEkiIndex + 1, *pCentDedEki, CentDedEki());
					}
				}*/
				//駅の挿入・削除を行うと、駅Index番号表示および分岐駅・環状線設定の
				//相手先番号が変わる場合があるので、全駅を更新します
				//(挿入・削除が行われた箇所よりも下側だけでなく、
				//その範囲内の駅に対し、分岐駅設定を行っている、上側の駅もありうるため
				//区域を指定するよりも、全更新の方が手っ取り早いという判断です)
				int iEkiSize = pCentDedEkiContGet->size();
//#pragma omp parallel for schedule(static)
				for (int cnt = 0; cnt < iEkiSize; cnt++)
				{
					int iEkiIndex =  cnt;
					const CentDedEki*	pCentDedEki
						= pCentDedEkiContGet->get(iEkiIndex);
					if (iEkiIndex == 0 &&
						pCentDedEkiContGet->size()>1)
					{
						const CentDedEki*	pCentDedEkiNext
							= pCentDedEkiContGet->get(iEkiIndex + 1);
						OnUpdate_setCentDedEki_To_Column(
							iEkiIndex + 1, *pCentDedEki, *pCentDedEkiNext);
					}
					else if (iEkiIndex == 0)
					{
						OnUpdate_setCentDedEki_To_Column(
							iEkiIndex + 1, *pCentDedEki, CentDedEki());
					}
					else if (iEkiIndex < pCentDedEkiContGet->size() - 1)
					{
						const CentDedEki*	pCentDedEkiPrev
							= pCentDedEkiContGet->get(iEkiIndex - 1);
						const CentDedEki*	pCentDedEkiNext
							= pCentDedEkiContGet->get(iEkiIndex + 1);
						OnUpdate_setCentDedEki_To_Column(
							iEkiIndex, *pCentDedEkiPrev, *pCentDedEki);
						OnUpdate_setCentDedEki_To_Column(
							iEkiIndex + 1, *pCentDedEki, *pCentDedEkiNext);
					}
					else
					{
						const CentDedEki*	pCentDedEkiPrev
							= pCentDedEkiContGet->get(iEkiIndex - 1);
						OnUpdate_setCentDedEki_To_Column(
							iEkiIndex, *pCentDedEkiPrev, *pCentDedEki);
						OnUpdate_setCentDedEki_To_Column(
							iEkiIndex + 1, *pCentDedEki, CentDedEki());
					}
				}
				InvalidateGrid();
			}
			// --------------------------------
			
		}
		else
		{
			//CRfEditCmd_DedRosenFileDataProp
			//	  路線ファイルのプロパティの変更は、
			//	フォントの変化を伴うため、全更新が必要です。
			//CRfEditCmd_Rosen
			//CRfEditCmd_RosenFileData
			//	駅を包含するオブジェクトです。これが更新された場合は、
			//	全更新が必要です。

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

		int iYColumnBegin = createYColSpecCont().ColumnNumberFromSpec( 
			CdEkiYColSpec( CdEkiYColSpec::ColumnType_Eki , 0 ) ) ;

		getCSelect()->setColumnNumberSelectLimit(
			CdDcdZoneXy( 
				CdDcdZone( 0 , INT_MAX ) , 
				CdDcdZone( iYColumnBegin , pCentDedEkiContGet->size()   ) 
			) );
	}
}

void CWndDcdGridEki::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	if ( bActivate && m_bWaitForActivate ){
		OnUpdate_All() ;
	}
}





	// ********************************
	//@name CWndDcdGridEki-操作
	// ********************************
	
int CWndDcdGridEki::execEkiPropDlg( bool bInsert , BOOL bQueryEnable ) 
{
	int iRv = 0 ;
	Ou<CRfEditCmd_Eki>	pCmd ;
	Ou<CRfEditCmd_Eki>*	ppCmd = NULL ;
	if ( !bQueryEnable ){	ppCmd = &pCmd ;};

	// ****************************************************************
	//	コマンドの実行可否の判定
	// ****************************************************************
	if ( iRv >= 0 )
	{
		if ( bInsert )
		{
			if ( !createCmd( ECreateCmd_NewItem , ppCmd ) )
			{
				iRv = -1 ;	//	セルの位置が不正です。
			}
		}
		else
		{
			if ( !createCmd( ECreateCmd_Select , ppCmd ) ) 
			{
				iRv = -1 ;
			}
		}
	}
	// ****************************************************************
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		CdEkiXColSpec	aXColSpec = getXColSpecOfFocus() ;
		int iFocus = -1 ;
		switch( aXColSpec.getColumnType() )
		{
		case CdEkiXColSpec::EColumnType::ColumnType_EkiIndex:
			iFocus = 0;
			break;
		case CdEkiXColSpec::EColumnType::ColumnType_Ekimei:
			iFocus = 0 ; 
			break ;
		case CdEkiXColSpec::EColumnType::ColumnType_Ekijikokukeisiki:
			iFocus = 1 ;
			break ;
		case CdEkiXColSpec::EColumnType::ColumnType_Ekikibo:
			iFocus = 2 ;
			break ;
		case CdEkiXColSpec::EColumnType::ColumnType_EkiBrunch:
			iFocus = 3;
			break;
		case CdEkiXColSpec::EColumnType::ColumnType_EkiLoop:
			iFocus = 4;
			break;
		}
		int iEkiIndex = -2;
		bool bEkijikokukeisikiAndEkikiboEnable = true;
		bool bBrunchFunctionEnable = true;
		bool bLoopFunctionEnable = true;
		vector<int> iEkiTrack2Map;
		vector<int> iOuterTerminalEkimeiMap;
		if (bInsert)
		{
			//新規アイテムの場合、iEkiIndexを-1とする。
			//iEkiIndex = -1;
			CdEkiYColSpec  aCdYColSpecOfFocus = getYColSpecOfFocus();
			iEkiIndex = aCdYColSpecOfFocus.getEkiIndex();
			bEkijikokukeisikiAndEkikiboEnable = true;
			bBrunchFunctionEnable = true;
			bLoopFunctionEnable = true;
			//pCmd->setBrunchCoreEkiIndex(-1);
		}
		else if ( getCSelect()->getSelectedCellCount() == 0)
		{
			//単数選択の場合、iEkiIndexは駅Indexになる。
			//bEkijikokukeisikiAndEkikiboEnable 
			//	基幹駅もしくは起点駅の場合、false
			//bBrunchFunctionEnable
			//	基幹駅もしくは起点駅の場合、false
			//bLoopFunctionEnable
			//	起点方に派生駅を持つ基幹駅の場合、false
			//※ダイアログオープン後、分岐駅設定及び環状線設定を変えた場合に、trueになるような場合は、
			//最初からtrueにし、FromTargetでfalseにする。
			CdEkiYColSpec  aCdYColSpecOfFocus = getYColSpecOfFocus();
			iEkiIndex = aCdYColSpecOfFocus.getEkiIndex();
			const Mu< const CentDedEki* >* pCentDedEkiCont = getCDiagramEditDoc()->getCDedRosenFileData()
				->getCentDedRosen()->getCentDedEkiCont()->getMuPtr();
			const CentDedEki* pCentDedEki = pCentDedEkiCont->get(iEkiIndex);
			if (pCentDedEki->getBrunchLoopPosition() != -1 &&
				pCentDedEki->getBrunchLoopPosition() != INT_MAX &&
				pCentDedEki->getBrunchLoopPosition() != INT_MIN)
			{
				if (pCentDedEki->getBrunchLoopPosition() < (int)pCentDedEki->getEkiIndexLoop().size() - 1)
				{
					/**
						EkiIndexLoopのiEkiIndexよりも後方に値が存在する場合は、iEkiIndexは"起点駅"になる。
					*/
					bEkijikokukeisikiAndEkikiboEnable = false;
					bBrunchFunctionEnable = false;
				}
				if (pCentDedEki->getBrunchLoopPosition() == 0 &&
					pCentDedEki->getEkiIndexBrunchOriginSide().size() > 0)
				{
					/**
						iEkiIndexがEkiIndexLoopの先頭にあり、EkiIndexBrunchOriginSideに一つ以上の値がある場合は、
						この駅は"起点方に派生駅を持つ基幹駅"となる。
					*/
					bEkijikokukeisikiAndEkikiboEnable = false;
					bBrunchFunctionEnable = false;
					bLoopFunctionEnable = false;

				}
				if (pCentDedEki->getBrunchLoopPosition() == pCentDedEki->getEkiIndexLoop().size() - 1 &&
					pCentDedEki->getEkiIndexBrunchTerminalSide().size() > 0)
				{
					/**
						iEkiIndexがEkiIndexLoopの末尾にあり、EkiIndexBrunchTerminalSideに一つ以上の値がある場合は、
						この駅は"終点方に派生駅を持つ基幹駅"となる。
					*/
					bEkijikokukeisikiAndEkikiboEnable = false;
					bBrunchFunctionEnable = false;

				}

			}




			//for (int idx = 0; idx < pCentDedEkiCont->size(); idx++)
			//{
			//	if (iEkiIndex != idx)
			//	{
			//		if (pCentDedEkiCont->get(idx)->getBrunchCoreEkiIndex() == iEkiIndex)
			//		{
			//			bEkijikokukeisikiAndEkikiboEnable = false;
			//			bBrunchFunctionEnable = false;
			//			if (iEkiIndex > idx)
			//			{
			//				bLoopFunctionEnable = false;
			//			}
			//		}
			//		if (pCentDedEkiCont->get(idx)->getLoopOriginEkiIndex() == iEkiIndex)
			//		{
			//			bEkijikokukeisikiAndEkikiboEnable = false;
			//			bBrunchFunctionEnable = false;
			//		}
			//	}
			//}
			pCmd->setBrunchCoreEkiIndex(
				pCentDedEki->getBrunchCoreEkiIndex()
				//pCentDedEkiCont->get(iEkiIndex)->getBrunchCoreEkiIndex()
			);
			pCmd->setLoopOriginEkiIndex(
				pCentDedEki->getLoopOriginEkiIndex()
				//pCentDedEkiCont->get(iEkiIndex)->getLoopOriginEkiIndex()
			);
			//駅番線の変更処理のためのMapを初期化する
			for (int idx = 0; idx < pCentDedEkiCont->get(iEkiIndex)->getEkiTrack2Cont()->size(); idx++)
			{
				iEkiTrack2Map.push_back(idx);
			}
			//路線外発着駅の変更処理のためのMapを初期化する
			for (int idx = 0; idx < pCentDedEkiCont->get(iEkiIndex)->getOuterTerminalEkimeiCount(); idx++)
			{
				iOuterTerminalEkimeiMap.push_back(idx);
			}
		}
		else
		{
			//複数選択の場合、iEkiIndexを-2とする。
			//選択された駅の中に、基幹駅がある場合、駅時刻形式と駅規模の変更を不可にする。
			//選択された駅の中に、派生駅がある場合、駅時刻形式と駅規模の変更を不可にする。
			//選択された駅の中に、起点駅がある場合、駅時刻形式と駅規模の変更を不可にする。
			//選択された駅の中に、終点駅がある場合、駅時刻形式と駅規模の変更を不可にする。
			const Mu< const CentDedEki* >* pCentDedEkiCont = getCDiagramEditDoc()->getCDedRosenFileData()
				->getCentDedRosen()->getCentDedEkiCont()->getMuPtr();
			//int iEkiIndexSelect;
			CdEkiYColSpecCont aCdYColSpecCont = createYColSpecCont();

			for (int iColumnNumber = 0;
				iColumnNumber < getCXDcdGrid()->getYColumnCount() && bEkijikokukeisikiAndEkikiboEnable ;
				iColumnNumber++)
			{
				if (getCSelect()->getYColumnNumberSelected(iColumnNumber))
				{
					CdEkiYColSpec aCdEkiYColSpec = aCdYColSpecCont.ColumnNumberToSpec(iColumnNumber);
					int iEkiIndexSelect = aCdEkiYColSpec.getEkiIndex();
					if (pCentDedEkiCont->get(iEkiIndexSelect)->getBrunchLoopPosition() != -1)
					{
						bEkijikokukeisikiAndEkikiboEnable = false;
					}
					//if (pCentDedEkiCont->get(iEkiIndexSelect)->getBrunchCoreEkiIndex() >= 0 ||
					//	pCentDedEkiCont->get(iEkiIndexSelect)->getLoopOriginEkiIndex() >= 0)
					//{
					//	bEkijikokukeisikiAndEkikiboEnable = false;
					//}
					//for (int idx = 0; idx < pCentDedEkiCont->size(); idx++)
					//{
					//	if (iEkiIndexSelect != idx)
					//	{
					//		if (pCentDedEkiCont->get(idx)->getBrunchCoreEkiIndex() == iEkiIndexSelect ||
					//			pCentDedEkiCont->get(idx)->getLoopOriginEkiIndex() == iEkiIndexSelect)
					//		{
					//			bEkijikokukeisikiAndEkikiboEnable = false;
					//			//選択された駅は、他の駅から共有対象に指定されています
					//		}
					//	}
					//}
				}
			}
			iEkiIndex = -2;
			bBrunchFunctionEnable = false;
			bLoopFunctionEnable = false;
			//pCmd->setBrunchCoreEkiIndex(-2);
		}
		CDlgEkiProp	aDlg( 
			bInsert,
			pCmd->getCaMuiSelect()->getMuPtr() ,
			&m_bAdjustByEkijikokukeisiki , 
			iEkiIndex,
			bEkijikokukeisikiAndEkikiboEnable,
			bBrunchFunctionEnable,
			bLoopFunctionEnable,
			iEkiTrack2Map,
			iOuterTerminalEkimeiMap,
			iFocus , 
			&m_CKeyinputSenderToModalDlg , 
			this ) ;
		if ( aDlg.DoModal() == IDOK )
		{
			iRv = 1 ;

			//	[駅時刻を駅時刻形式で正規化]の設定を、
			//	次に実行するコマンドに反映します。
			pCmd->setAdjustByEkijikokukeisiki( m_bAdjustByEkijikokukeisiki ) ;

			if (getCSelect()->getSelectedCellCount() == 0)
			{
				if (pCmd->getBrunchCoreEkiIndex() ==
					pCmd->getCaMuiSelect()->getMuPtr()->get(0)->getBrunchCoreEkiIndex())
				{
					pCmd->setChangeBrunchCoreEkiIndex(false);
				}
				else
				{
					pCmd->setBrunchCoreEkiIndex(
						pCmd->getCaMuiSelect()->getMuPtr()->get(0)->getBrunchCoreEkiIndex());
					pCmd->setChangeBrunchCoreEkiIndex(true);
				}
				if (pCmd->getLoopOriginEkiIndex() ==
					pCmd->getCaMuiSelect()->getMuPtr()->get(0)->getLoopOriginEkiIndex())
				{
					pCmd->setChangeLoopOriginEkiIndex(false);
				}
				else
				{
					pCmd->setLoopOriginEkiIndex(
						pCmd->getCaMuiSelect()->getMuPtr()->get(0)->getLoopOriginEkiIndex());
					pCmd->setChangeLoopOriginEkiIndex(true);
				}
			}

			pCmd->setEkiTrack2Map(iEkiTrack2Map);
			pCmd->setOuterTerminalEkimeiMap(iOuterTerminalEkimeiMap);
		}
		// --------------------------------
		//	ダイアログOK時の処理
		// --------------------------------
		if ( iRv == 1 )
		{
			// --------------------------------
			//	編集コマンドを実行
			// --------------------------------
			getCDiagramEditDoc()->executeEditCmd( pCmd ) ;
		}
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************
		if ( iRv < 0 )
		{
			CString strErrorMessage ;
			switch( iRv )
			{
			case -1 :	//	現在は実行できません。
				break ;
			default:
				strErrorMessage.Format( _T( "Error=%d" ) , iRv ) ;
				break ;
			}
			if ( strErrorMessage.GetLength() > 0 )
			{
				MessageBox( strErrorMessage , NULL , MB_ICONSTOP | MB_OK ) ; 
			}
		}

		// ****************************************************************
	}
	return iRv ;
}
int CWndDcdGridEki::execCrossingCheckRuleDlg(bool bInsert, BOOL bQueryEnable)
{
	int iRv = 0;
	Ou<CRfEditCmd_Eki>	pCmd;
	Ou<CRfEditCmd_Eki>* ppCmd = NULL;
	if (!bQueryEnable) { ppCmd = &pCmd; };

	// ****************************************************************
	//	コマンドの実行可否の判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (bInsert)
		{
			iRv = -1;	//	セルの位置が不正です。
		}
		else
		{
			if (!createCmd(ECreateCmd_Focus, ppCmd))
			{
				iRv = -1;
			}
		}
	}
	// ****************************************************************
	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		CdEkiXColSpec	aXColSpec = getXColSpecOfFocus();
		int iEkiIndex = getYColSpecOfFocus().getEkiIndex();
		CDlgCrossingCheckRule	aDlg(
			pCmd->getCaMuiSelect()->getMuPtr()->get(0),
			iEkiIndex,
			&m_CKeyinputSenderToModalDlg,
			this);
		if (aDlg.DoModal() == IDOK)
		{
			iRv = 1;
			pCmd->setCrossingCheckRuleEdit(true);
		}
		// --------------------------------
		//	ダイアログOK時の処理
		// --------------------------------
		if (iRv == 1)
		{
			// --------------------------------
			//	編集コマンドを実行
			// --------------------------------
			getCDiagramEditDoc()->executeEditCmd(pCmd);
		}
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************
		if (iRv < 0)
		{
			CString strErrorMessage;
			switch (iRv)
			{
			case -1:	//	現在は実行できません。
				break;
			default:
				strErrorMessage.Format(_T("Error=%d"), iRv);
				break;
			}
			if (strErrorMessage.GetLength() > 0)
			{
				MessageBox(strErrorMessage, NULL, MB_ICONSTOP | MB_OK);
			}
		}

		// ****************************************************************
	}
	return iRv;
}

int CWndDcdGridEki::OnViewDisplaySettingMode_Process(BOOL bQueryEnable)
{
	int iRv = 0;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (getDisplaySettingMode())
	{
		iRv = 1;	//(bQueryEnable==TRUEの場合)[表示設定モードにする]が有効です。
	}
	// ****************************************************************
	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドを実行
		// ****************************************************************
		setDisplaySettingMode(!getDisplaySettingMode());

		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv;
}

bool CWndDcdGridEki::getDisplaySettingMode() const
{
	return m_bDisplaySettingMode;
}

int CWndDcdGridEki::setDisplaySettingMode(bool value)
{
	int iRv = 0;
	if (m_bDisplaySettingMode != value)
	{
		m_bDisplaySettingMode = value;

		//	表示設定モードの有効無効が変化した場合は、
		//	ビューを更新します。
		OnUpdate_All();
		InvalidateGrid();

		//	表示設定モードの有効無効を、
		//	.ini ファイルに保存
		getCDiagramEditApp()->writeCWndDcdGridEkiProp(this);
	}
	return (iRv);
}

// ----------------------------------------------------------------
//	MFC
// ----------------------------------------------------------------
BEGIN_MESSAGE_MAP(CWndDcdGridEki,CWndDcdGridEki::super)
	//{{AFX_MSG_MAP(CWndDcdGridEki)
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KEYUP()
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR, OnUpdateEditClear)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_EDIT_EKI_INVERT, &CWndDcdGridEki::OnEditEkiInvert)
	ON_UPDATE_COMMAND_UI(ID_EDIT_EKI_INVERT, &CWndDcdGridEki::OnUpdateEditEkiInvert)
	ON_COMMAND(ID_EDIT_EkiInsert, OnEDITEkiInsert)
	ON_UPDATE_COMMAND_UI(ID_EDIT_EkiInsert, &CWndDcdGridEki::OnUpdateEditEkiinsert)
	ON_COMMAND(ID_EDIT_EkiProp, OnEDITEkiProp)
	ON_UPDATE_COMMAND_UI(ID_EDIT_EkiProp, &CWndDcdGridEki::OnUpdateEditEkiprop)
	ON_COMMAND(ID_VIEW_DisplaySettingMode, &CWndDcdGridEki::OnViewDisplaySettingMode)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DisplaySettingMode, &CWndDcdGridEki::OnUpdateViewDisplaySettingMode)
	ON_COMMAND(ID_Eki_SettingNext, &CWndDcdGridEki::OnEkiSettingNext)
	ON_UPDATE_COMMAND_UI(ID_Eki_SettingNext, &CWndDcdGridEki::OnUpdateEkiSettingNext)
	ON_COMMAND(ID_Eki_SettingPrev, &CWndDcdGridEki::OnEkiSettingPrev)
	ON_UPDATE_COMMAND_UI(ID_Eki_SettingPrev, &CWndDcdGridEki::OnUpdateEkiSettingPrev)
	ON_COMMAND(ID_Eki_SettingNext2, &CWndDcdGridEki::OnEkiSettingNext2)
	ON_UPDATE_COMMAND_UI(ID_Eki_SettingNext2, &CWndDcdGridEki::OnUpdateEkiSettingNext2)
	ON_COMMAND(ID_Eki_SettingPrev2, &CWndDcdGridEki::OnEkiSettingPrev2)
	ON_UPDATE_COMMAND_UI(ID_Eki_SettingPrev2, &CWndDcdGridEki::OnUpdateEkiSettingPrev2)
	ON_COMMAND(ID_Eki_SettingNext3, &CWndDcdGridEki::OnEkiSettingNext3)
	ON_UPDATE_COMMAND_UI(ID_Eki_SettingNext3, &CWndDcdGridEki::OnUpdateEkiSettingNext3)
	ON_COMMAND(ID_Eki_SettingPrev3, &CWndDcdGridEki::OnEkiSettingPrev3)
	ON_UPDATE_COMMAND_UI(ID_Eki_SettingPrev3, &CWndDcdGridEki::OnUpdateEkiSettingPrev3)
	ON_COMMAND(ID_EDIT_CrossingCheckRuleDlg, OnEDITCrossingCheckRuleDlg)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CrossingCheckRuleDlg, &CWndDcdGridEki::OnUpdateEditCrossingCheckRuleDlg)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

int CWndDcdGridEki::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (super::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	OnCreate_Header();
	// --------------------------------
	//	フォーカスセルの初期位置を設定
	// --------------------------------
	getCFocus()->setFocusCell( getCXDcdGrid()->getCell( 0 , 1 ) ) ;	
	
	return 0;
}

void CWndDcdGridEki::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	LogMsg(_T("CWndDcdGridEki::OnKeyDown(%08X,%04X,%08X)") , nChar, nRepCnt, nFlags) ;

	int iRv = 0 ;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************

	//	フォーカスセルが新規アイテム位置にあるときは、
	//	「新規アイテムのプロパティ入力を行い、それを末尾に挿入する」という
	//	動作になります。
	bool bInsert = false ;
	CdEkiYColSpec aYColSpec = getYColSpecOfFocus() ;
	if ( aYColSpec.getColumnType() == CdEkiYColSpec::ColumnType_NewEki )
	{
		bInsert = true ;
	}

	// ****************************************************************


	//	文字キーが押されていて、ダイアログボックスが開いていない場合は
	//	ダイアログボックスを開きます。
	if ( CKeyinputSenderToModalDlg::AnyLetterOrDigitKeyIsDown() && 
			m_CKeyinputSenderToModalDlg.startSend() >= 0 )
	{
		m_CKeyinputSenderToModalDlg.OnKeyDown( nChar , nRepCnt , nFlags ) ;
		execEkiPropDlg( bInsert , FALSE ) ;
		m_CKeyinputSenderToModalDlg.endSend() ;
	}
	//	すでにダイアログが起動中→ダイアログボックスにメッセージを転送
	else	
	{
		if ( !m_CKeyinputSenderToModalDlg.OnKeyDown( nChar , nRepCnt , nFlags ) )
		{
			CWndDcdGridEki::super::OnKeyDown(nChar, nRepCnt, nFlags);
		}
	}
			
}

void CWndDcdGridEki::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	int iRv = 0 ;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************

	//	フォーカスセルが新規アイテム位置にあるときは、
	//	「新規アイテムのプロパティ入力を行い、それを末尾に挿入する」という
	//	動作になります。
	bool bInsert = false ;
	CdEkiYColSpec aYColSpec = getYColSpecOfFocus() ;
	if ( aYColSpec.getColumnType() == CdEkiYColSpec::ColumnType_NewEki )
	{
		bInsert = true ;
	}

	// ****************************************************************
	//	コマンドの実行
	// ****************************************************************
	if ( execEkiPropDlg( bInsert , FALSE ) < 0 )
	{
		iRv = -1 ;	//	-1 ;	//	フォーカスセルの位置が不正です。
	}
	// ****************************************************************

	CWndDcdGridEki::super::OnLButtonDblClk(nFlags, point);
}

void CWndDcdGridEki::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if ( !m_CKeyinputSenderToModalDlg.OnKeyUp( nChar , nRepCnt , nFlags ) )
	{
		CWndDcdGridEki::super::OnKeyUp(nChar, nRepCnt, nFlags);
	}
}

void CWndDcdGridEki::OnEDITEkiProp() 
{
	OnEDITEkiProp_Process( FALSE );
}
void CWndDcdGridEki::OnUpdateEditEkiprop(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( OnEDITEkiProp_Process( TRUE ) >= 0 ) ;
}


void CWndDcdGridEki::OnEDITEkiInsert() 
{
	OnEDITEkiInsert_Process( FALSE ) ;
}
void CWndDcdGridEki::OnUpdateEditEkiinsert(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( OnEDITEkiInsert_Process( TRUE ) >= 0 ) ;
}


void CWndDcdGridEki::OnEditClear() 
{
	OnEditClear_Process( FALSE ) ;
}

void CWndDcdGridEki::OnEditCut() 
{
	OnEditCut_Process( FALSE ) ;
}

void CWndDcdGridEki::OnEditCopy() 
{
	OnEditCopy_Process( FALSE ) ;

}

void CWndDcdGridEki::OnEditPaste() 
{
	OnEditPaste_Process( FALSE ) ;
	
}

void CWndDcdGridEki::OnUpdateEditClear(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( OnEditClear_Process( TRUE ) >= 0 ) ;
}

void CWndDcdGridEki::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( OnEditCut_Process( TRUE ) >= 0 ) ;
}

void CWndDcdGridEki::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( OnEditCopy_Process( TRUE ) >= 0 ) ;
}

void CWndDcdGridEki::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( OnEditPaste_Process( TRUE ) >= 0 ) ;
}


void CWndDcdGridEki::OnEditEkiInvert()
{
	OnEditEkiInvert_Process( FALSE ) ;
}

void CWndDcdGridEki::OnUpdateEditEkiInvert(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( OnEditEkiInvert_Process( TRUE ) >= 0 ) ;
}



void CWndDcdGridEki::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CMenu	aMenu ;
	aMenu.LoadMenu( IDR_MENU_EKIVIEW_CONTEXT ) ;
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

void CWndDcdGridEki::OnViewDisplaySettingMode()
{
	OnViewDisplaySettingMode_Process(FALSE);
}

void CWndDcdGridEki::OnUpdateViewDisplaySettingMode(CCmdUI* pCmdUI)
{
	int iResult = OnViewDisplaySettingMode_Process(TRUE);
	pCmdUI->Enable(iResult >= 0);
	pCmdUI->SetCheck(iResult >= 1);
}

void CWndDcdGridEki::OnEkiSettingNext()
{
	OnEkiSettingNext_Process(FALSE,0);
}

void CWndDcdGridEki::OnUpdateEkiSettingNext(CCmdUI* pCmdUI)
{
	int iResult = OnEkiSettingNext_Process(TRUE,0);
	pCmdUI->Enable(iResult >= 0);
	pCmdUI->SetCheck(iResult >= 1);
}

void CWndDcdGridEki::OnEkiSettingPrev()
{
	OnEkiSettingPrev_Process(FALSE, 0);
}

void CWndDcdGridEki::OnUpdateEkiSettingPrev(CCmdUI* pCmdUI)
{
	int iResult = OnEkiSettingPrev_Process(TRUE, 0);
	pCmdUI->Enable(iResult >= 0);
	pCmdUI->SetCheck(iResult >= 1);
}

void CWndDcdGridEki::OnEkiSettingNext2()
{
	OnEkiSettingNext_Process(FALSE, 1);
}

void CWndDcdGridEki::OnUpdateEkiSettingNext2(CCmdUI* pCmdUI)
{
	int iResult = OnEkiSettingNext_Process(TRUE,1);
	pCmdUI->Enable(iResult >= 0);
	pCmdUI->SetCheck(iResult >= 1);
}

void CWndDcdGridEki::OnEkiSettingPrev2()
{
	OnEkiSettingPrev_Process(FALSE, 1);
}

void CWndDcdGridEki::OnUpdateEkiSettingPrev2(CCmdUI* pCmdUI)
{
	int iResult = OnEkiSettingPrev_Process(TRUE, 1);
	pCmdUI->Enable(iResult >= 0);
	pCmdUI->SetCheck(iResult >= 1);
}

void CWndDcdGridEki::OnEkiSettingNext3()
{
	OnEkiSettingNext_Process(FALSE, 2);
}

void CWndDcdGridEki::OnUpdateEkiSettingNext3(CCmdUI* pCmdUI)
{
	int iResult = OnEkiSettingNext_Process(TRUE, 2);
	pCmdUI->Enable(iResult >= 0);
	pCmdUI->SetCheck(iResult >= 1);
}

void CWndDcdGridEki::OnEkiSettingPrev3()
{
	OnEkiSettingPrev_Process(FALSE, 2);
}

void CWndDcdGridEki::OnUpdateEkiSettingPrev3(CCmdUI* pCmdUI)
{
	int iResult = OnEkiSettingPrev_Process(TRUE, 2);
	pCmdUI->Enable(iResult >= 0);
	pCmdUI->SetCheck(iResult >= 1);
}

void CWndDcdGridEki::OnEDITCrossingCheckRuleDlg()
{
	OnEDITCrossingCheckRuleDlg_Process(FALSE);
}
void CWndDcdGridEki::OnUpdateEditCrossingCheckRuleDlg(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(OnEDITCrossingCheckRuleDlg_Process(TRUE) >= 0);
}

} //namespace ViewEki
