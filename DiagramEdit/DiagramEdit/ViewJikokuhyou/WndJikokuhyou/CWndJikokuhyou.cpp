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
//	CWndJikokuhyou.cpp
//	$Id: CWndJikokuhyou.cpp 295 2016-06-11 05:14:13Z okm $
// ****************************************************************
*/
/** @file */
//#include "..\..\StdAfx.h"
#include "stdafx.h"

#include "NsOu\OuNew.h"
#include "NsOu\dynamic_castOu.h"
#include "str\CsvDocument\CConvCsvDocument.h"
#include "str\vectorToFile.h"
#include "logmsg\LogMsg.h"

#include "DcDraw\CDcdTargetGetDC.h"
#include "DcDraw\CDcdLine.h"
#include "DcDraw\CDcdFillrectRop.h"
#include "DcDraw\CDcdTextbox.h"
#include "DcDraw\CConverter_WinGdi.h"

#include "MfcUtil\MfcUtil.h"

#include "..\JikokuhyouColSpec\JikokuhyouColSpec.h"
#include "..\..\DedRosenFileData\EditCmd\CRfEditCmd_Rosen.h"
#include "..\..\resource.h"
#include "..\..\entDed\CentDedRosen.h"
#include "..\..\DiagramEdit.h"
#include "..\..\ViewJikokuhyou\CDlgJikokuhyouViewProp.h"
#include "..\..\ViewDiagram\CDedDiagramView.h"
#include "..\CDlgOuJikokuhyouCsvExport.h"
#include "CCellBuilder.h"
#include "CCellBuilderCustomize.h"
#include "CWndJikokuhyou.h"
#include "CWjkState_Ressyahensyu.h"
#include "CWjkState_Renzoku.h"
#include "CWndJikokuhyou.h"

#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace ViewJikokuhyou{ namespace WndJikokuhyou{
using namespace std ;
using namespace OuMfc::MfcUtil ;
using namespace OuLib::Str;
// ****************************************************************
//	CWndJikokuhyou
// ****************************************************************
// --------------------------------
//@name 下請関数
// --------------------------------
CJikokuhyouDoc*	CWndJikokuhyou::GetDocument() 
{
	CView* pCView = (CView*)GetParent() ;
	return (CJikokuhyouDoc*)pCView->GetDocument() ;
};

ERessyahoukou CWndJikokuhyou::getRessyahoukou() 
{
	return GetDocument()->getRessyahoukou() ;
};


const CentDedDia*	CWndJikokuhyou::getCentDedDia()
{
	const CentDedRosen*	pCentDedRosen = 
		getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen() ;
	int iDiaIndex = pCentDedRosen->getCentDedDiaCont()->findCentDedDiaByName( 
			GetDocument()->getDiaName() ) ;
	if ( iDiaIndex < 0 ){
		return ( NULL ) ;
	}
	const CentDedDia* pCentDedDia = pCentDedRosen->getCentDedDiaCont()->getMuPtr()->get( iDiaIndex ) ;
	return ( pCentDedDia ) ;
};

const CentDedRessyaCont*	CWndJikokuhyou::getCentDedRessyaCont()
{
	const CentDedDia* pCentDedDia = getCentDedDia() ;
	if ( pCentDedDia == NULL ){
		return ( NULL ) ;
	}
	return ( pCentDedDia->getCentDedRessyaCont( getRessyahoukou() ) ) ;
}
const bool CWndJikokuhyou::getCustomizeDisplayMode()
{
	return GetDocument()->getCustomizeDisplayMode();
}
;


	// --------------------------------
	//@name updateUI...() ・セルの更新
	// --------------------------------

void  CWndJikokuhyou::updateUIAll() 
{
	//	この変数が true のときは、
	//	「ビューがアクティブな状態での updateUIAll() 」
	//	まで、あらゆる更新操作は行われません。
	if ( m_bUpdate_All_Requested )
	{
		return ;
	}
	// --------------------------------

	//	全更新
	CView *pView = getCDiagramEditApp()->getCMainFrame()->
		getMDIChildActiveView() ;
	if ( pView != GetParent() )
	{
		//	全更新を必要とする場合で、
		//	このビューがアクティブでない場合は
		//	全更新を保留します。
		LogMsg(_T("CWndJikokuhyou::OnUpdate_All() ")
			_T("m_bUpdate_All_Requested=true") ) ;
		m_bUpdate_All_Requested = true ;
	}
	else
	{
		//	全更新を必要とする場合で、
		//	このビューがアクティブの場合は、
		//	全更新を行います。
		CWaitCursor	aCWaitCursor ;


		// --------------------------------
		//	セルを更新
		// --------------------------------
		//	コマンドオブジェクト実行によるセル移動でセル選択にならないように、
		//	セル選択機能を一時的に中止します。
		{
			clearSelect() ;
			CPropStack aPropStack( this ) ;
			aPropStack
				.CBoxSelect_setIsEnable( false )
				.CRandomSelect_setIsEnable( false )  ;
		}
		{

			const CdDedDispProp aCdDedDispProp =
				getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();

			int iEnableOperation = getCDiagramEditDoc()
				->getCDedRosenFileData()->getCentDedRosen()->getEnableOperation();
			bool bDisplayRessyamei = aCdDedDispProp.getDisplayRessyamei();
			bool bDisplayInOutLinkCode = aCdDedDispProp.getDisplayInOutLinkCode();
			//bool bDisplayOuterTerminalShihatsu = getCDiagramEditDoc()
			//	->getCDedRosenFileData()->getCdDedDispProp().getDisplayOuterTerminalShihatsu(getRessyahoukou());
			//bool bDisplayOuterTerminalShuchaku = getCDiagramEditDoc()
			//	->getCDedRosenFileData()->getCdDedDispProp().getDisplayOuterTerminalShuchaku(getRessyahoukou());
			//	列車番号
			//　運用番号
			//	種別
			//	列車名
			//	号数
			//	号
			//	駅時刻(0...*)
			//	備考
			int iYColumnCount = 3;
			if (iEnableOperation>1)
			{
				iYColumnCount += aCdDedDispProp.getOperationNumberRows();
				//運用番号欄
			}
			if (bDisplayRessyamei)
			{
				iYColumnCount += 3;
				//列車名・号数・号
			}
			if (m_bDisplayShihatsuShuchakuEkimei || !getCustomizeDisplayMode())
			{
				iYColumnCount += 2;
				//始発駅・終着駅
			}
			if ( !getCustomizeDisplayMode())
			{
				iYColumnCount += 4;
				//始発駅作業・終着駅作業
				if (iEnableOperation > 1)
				{
					iYColumnCount += 1;
					//始発駅作業(運用番号)
					if (bDisplayInOutLinkCode)
					{
						iYColumnCount += 2;
						//始発駅作業・終着駅作業(入出区連携コード)
					}
				}
			}
			if (getCXDcdGrid()->getYColumnCount() < iYColumnCount)
			{
				getCXDcdGrid()->setYColumnCount(iYColumnCount);
			}
			getCXDcdGrid()->setYFixColumnCount(iYColumnCount -1);
		}
		//	セルを更新
		if (getCustomizeDisplayMode())
		{
			ViewJikokuhyou::WndJikokuhyou::CCellBuilderCustomize	aCellBuilder(
				getCDiagramEditDoc()->getCDedRosenFileData(),
				getCentDedRessyaCont(),
				getCentDedDia()->getcontCustomizeRessyaIndex(getRessyahoukou()),
				m_bDisplayTsuukaEkiJikoku,
				m_bDisplaySecondEkiJikoku,
				m_bDisplayColonEkiJikoku,
				m_bDisplayShihatsuShuchakuEkimei,
				m_bDisplayParentSyubetsu,
				m_bDisplayTsuukaFontPerSyubetsu,
				getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getEnableOperation());
			aCellBuilder.update(
				this);
		}
		else
		{
			ViewJikokuhyou::WndJikokuhyou::CCellBuilder	aCellBuilder(
				getCDiagramEditDoc()->getCDedRosenFileData(),
				getCentDedRessyaCont(),
				m_bDisplayTsuukaEkiJikoku,
				m_bDisplayAllEkiJikoku,
				m_bDisplaySecondEkiJikoku,
				m_bDisplayColonEkiJikoku,
				m_bStandardOperationTimeFunction,
				m_bDisplayShihatsuShuchakuEkimei,
				m_bDisplayParentSyubetsu,
				m_bDisplayTsuukaFontPerSyubetsu,
				//getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp().getDisplayRessyamei(),
				getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getEnableOperation()/*,
				getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp().getDisplayOuterTerminalShihatsu(getRessyahoukou()),
				getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp().getDisplayOuterTerminalShuchaku(getRessyahoukou())*/);
			aCellBuilder.update(
				this);
		}

		InvalidateGrid() ;

		m_bUpdate_All_Requested = false ;
	}
}
void CWndJikokuhyou::updateUISetAllRessya() 
{
	//	この変数が true のときは、
	//	「ビューがアクティブな状態での OnUpdate_All() 」
	//	まで、あらゆる更新操作は行われません。
	if ( m_bUpdate_All_Requested )
	{
		return ;
	}
	// --------------------------------
	//	セルを更新
	// --------------------------------
	{
		//	コマンドオブジェクト実行によるセル移動でセル選択にならないように、
		//	セル選択を解除し、セル選択機能も一時的に中止します。
		{
			clearSelect() ;
			CPropStack aPropStack( this ) ;
			aPropStack
				.CBoxSelect_setIsEnable( false )
				.CRandomSelect_setIsEnable( false )  ;
		}

		//	セルを更新
		if (getCustomizeDisplayMode())
		{
			ViewJikokuhyou::WndJikokuhyou::CCellBuilderCustomize	aCellBuilder(
				getCDiagramEditDoc()->getCDedRosenFileData(),
				getCentDedRessyaCont(),
				getCentDedDia()->getcontCustomizeRessyaIndex(getRessyahoukou()),
				m_bDisplayTsuukaEkiJikoku,
				m_bDisplaySecondEkiJikoku,
				m_bDisplayColonEkiJikoku,
				m_bDisplayShihatsuShuchakuEkimei,
				m_bDisplayParentSyubetsu,
				m_bDisplayTsuukaFontPerSyubetsu,
				getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getEnableOperation());
			aCellBuilder.updateAllRessya(
				this);

		}
		else
		{
			ViewJikokuhyou::WndJikokuhyou::CCellBuilder	aCellBuilder(
				getCDiagramEditDoc()->getCDedRosenFileData(),
				getCentDedRessyaCont(),
				m_bDisplayTsuukaEkiJikoku,
				m_bDisplayAllEkiJikoku,
				m_bDisplaySecondEkiJikoku,
				m_bDisplayColonEkiJikoku,
				m_bStandardOperationTimeFunction,
				m_bDisplayShihatsuShuchakuEkimei,
				m_bDisplayParentSyubetsu,
				m_bDisplayTsuukaFontPerSyubetsu,
				//getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp().getDisplayRessyamei(),
				getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getEnableOperation()/*,
				getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp().getDisplayOuterTerminalShihatsu(getRessyahoukou()),
				getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp().getDisplayOuterTerminalShuchaku(getRessyahoukou())*/);
			aCellBuilder.updateAllRessya(
				this);

		}
	}
}

void CWndJikokuhyou::updateUI_ReplaceRessya( 
		int iDstRessyaIndex , 
		int iDstDelCount , 
		int iInsertCount ) 

{
	//	この変数が true のときは、
	//	「ビューがアクティブな状態での OnUpdate_All() 」
	//	まで、あらゆる更新操作は行われません。
	if ( m_bUpdate_All_Requested )
	{
		return ;
	}
	// --------------------------------
	//	セルを更新
	// --------------------------------
	{
		//	列の増減を伴うコマンドを実行する場合は、
		//	コマンドオブジェクト実行によるセル移動でセル選択にならないように、
		//	セル選択を解除し、セル選択機能も一時的に中止します。
		if ( iDstDelCount != iInsertCount )
		{
			clearSelect() ;
			CPropStack aPropStack( this ) ;
			aPropStack
				.CBoxSelect_setIsEnable( false )
				.CRandomSelect_setIsEnable( false )  ;
		}

		//	セルを更新
		if (getCustomizeDisplayMode())
		{
			ViewJikokuhyou::WndJikokuhyou::CCellBuilderCustomize	aCellBuilder(
				getCDiagramEditDoc()->getCDedRosenFileData(),
				getCentDedRessyaCont(),
				getCentDedDia()->getcontCustomizeRessyaIndex(getRessyahoukou()),
				m_bDisplayTsuukaEkiJikoku,
				m_bDisplaySecondEkiJikoku,
				m_bDisplayColonEkiJikoku,
				m_bDisplayShihatsuShuchakuEkimei,
				m_bDisplayParentSyubetsu,
				m_bDisplayTsuukaFontPerSyubetsu,
				getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getEnableOperation());
			aCellBuilder.updateAllRessya(this);
			//aCellBuilder.replaceRessya(
			//	iDstRessyaIndex,
			//	iDstDelCount,
			//	iInsertCount,
			//	this);
		}
		else
		{
			ViewJikokuhyou::WndJikokuhyou::CCellBuilder	aCellBuilder(
				getCDiagramEditDoc()->getCDedRosenFileData(),
				getCentDedRessyaCont(),
				m_bDisplayTsuukaEkiJikoku,
				m_bDisplayAllEkiJikoku,
				m_bDisplaySecondEkiJikoku,
				m_bDisplayColonEkiJikoku,
				m_bStandardOperationTimeFunction,
				m_bDisplayShihatsuShuchakuEkimei,
				m_bDisplayParentSyubetsu,
				m_bDisplayTsuukaFontPerSyubetsu,
				//getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp().getDisplayRessyamei(),
				getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getEnableOperation()/*,
				getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp().getDisplayOuterTerminalShihatsu(getRessyahoukou()),
				getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp().getDisplayOuterTerminalShuchaku(getRessyahoukou())*/);
			aCellBuilder.replaceRessya(
				iDstRessyaIndex,
				iDstDelCount,
				iInsertCount,
				this);
		}
	}
}

void CWndJikokuhyou::updateUI_ReplaceRessyaAndAllOperationNumber(
	int iDstRessyaIndex,
	int iDstDelCount,
	int iInsertCount)

{
	//	この変数が true のときは、
	//	「ビューがアクティブな状態での OnUpdate_All() 」
	//	まで、あらゆる更新操作は行われません。
	if (m_bUpdate_All_Requested)
	{
		return;
	}
	// --------------------------------
	//	セルを更新
	// --------------------------------
	{
		//	列の増減を伴うコマンドを実行する場合は、
		//	コマンドオブジェクト実行によるセル移動でセル選択にならないように、
		//	セル選択を解除し、セル選択機能も一時的に中止します。
		if (iDstDelCount != iInsertCount)
		{
			clearSelect();
			CPropStack aPropStack(this);
			aPropStack
				.CBoxSelect_setIsEnable(false)
				.CRandomSelect_setIsEnable(false);
		}

		//	セルを更新
		if (getCustomizeDisplayMode())
		{
			ViewJikokuhyou::WndJikokuhyou::CCellBuilderCustomize	aCellBuilder(
				getCDiagramEditDoc()->getCDedRosenFileData(),
				getCentDedRessyaCont(),
				getCentDedDia()->getcontCustomizeRessyaIndex(getRessyahoukou()),
				m_bDisplayTsuukaEkiJikoku,
				m_bDisplaySecondEkiJikoku,
				m_bDisplayColonEkiJikoku,
				m_bDisplayShihatsuShuchakuEkimei,
				m_bDisplayParentSyubetsu,
				m_bDisplayTsuukaFontPerSyubetsu,
				getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getEnableOperation());
			aCellBuilder.updateAllRessya(this);
			//aCellBuilder.replaceRessyaAndAllOperationNumber(
			//	iDstRessyaIndex,
			//	iDstDelCount,
			//	iInsertCount,
			//	this);
		}
		else
		{
			ViewJikokuhyou::WndJikokuhyou::CCellBuilder	aCellBuilder(
				getCDiagramEditDoc()->getCDedRosenFileData(),
				getCentDedRessyaCont(),
				m_bDisplayTsuukaEkiJikoku,
				m_bDisplayAllEkiJikoku,
				m_bDisplaySecondEkiJikoku,
				m_bDisplayColonEkiJikoku,
				m_bStandardOperationTimeFunction,
				m_bDisplayShihatsuShuchakuEkimei,
				m_bDisplayParentSyubetsu,
				m_bDisplayTsuukaFontPerSyubetsu,
				//getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp().getDisplayRessyamei(),
				getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getEnableOperation()/*,
				getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp().getDisplayOuterTerminalShihatsu(getRessyahoukou()),
				getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp().getDisplayOuterTerminalShuchaku(getRessyahoukou())*/);
			aCellBuilder.replaceRessyaAndAllOperationNumber(
				iDstRessyaIndex,
				iDstDelCount,
				iInsertCount,
				this);
		}
	}
}

void CWndJikokuhyou::updateUI_AllOperationNumber()

{
	//	この変数が true のときは、
	//	「ビューがアクティブな状態での OnUpdate_All() 」
	//	まで、あらゆる更新操作は行われません。
	if (m_bUpdate_All_Requested)
	{
		return;
	}
	// --------------------------------
	//	セルを更新
	// --------------------------------
	{
		//	コマンドオブジェクト実行によるセル移動でセル選択にならないように、
		//	セル選択を解除し、セル選択機能も一時的に中止します。
		{
			clearSelect();
			CPropStack aPropStack(this);
			aPropStack
				.CBoxSelect_setIsEnable(false)
				.CRandomSelect_setIsEnable(false);
		}

		//	セルを更新
		if (getCustomizeDisplayMode())
		{
			//カスタマイズ時刻表の場合、運用接続により、並び順が変わることがあるので、全列車更新とします。
			ViewJikokuhyou::WndJikokuhyou::CCellBuilderCustomize	aCellBuilder(
				getCDiagramEditDoc()->getCDedRosenFileData(),
				getCentDedRessyaCont(),
				getCentDedDia()->getcontCustomizeRessyaIndex(getRessyahoukou()),
				m_bDisplayTsuukaEkiJikoku,
				m_bDisplaySecondEkiJikoku,
				m_bDisplayColonEkiJikoku,
				m_bDisplayShihatsuShuchakuEkimei,
				m_bDisplayParentSyubetsu,
				m_bDisplayTsuukaFontPerSyubetsu,
				getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getEnableOperation());
			aCellBuilder.updateAllRessya(
				this);
		}
		else
		{
			ViewJikokuhyou::WndJikokuhyou::CCellBuilder	aCellBuilder(
				getCDiagramEditDoc()->getCDedRosenFileData(),
				getCentDedRessyaCont(),
				m_bDisplayTsuukaEkiJikoku,
				m_bDisplayAllEkiJikoku,
				m_bDisplaySecondEkiJikoku,
				m_bDisplayColonEkiJikoku,
				m_bStandardOperationTimeFunction,
				m_bDisplayShihatsuShuchakuEkimei,
				m_bDisplayParentSyubetsu,
				m_bDisplayTsuukaFontPerSyubetsu,
				//getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp().getDisplayRessyamei(),
				getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getEnableOperation()/*,
				getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp().getDisplayOuterTerminalShihatsu(getRessyahoukou()),
				getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp().getDisplayOuterTerminalShuchaku(getRessyahoukou())*/);
			aCellBuilder.updateAllOperationNumber(
				this);
		}
	}
}



	// --------------------------------
	//@name CWndJikokuhyou-MFCコマンドハンドラ下請関数
	// --------------------------------
int CWndJikokuhyou::OnFileExportJikokuhyoucsv_Process( 
	BOOL bQueryEnable )  
{
	int iRv = 0 ;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************

	// ****************************************************************
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		CJikokuhyouDoc* pCJikokuhyouDoc = (CJikokuhyouDoc*)GetDocument() ;

		const CDedRosenFileData* pCDedRosenFileData = 
			getCDiagramEditDoc()->getCDedRosenFileData() ;
		const CdDedDispProp aCdDedDispProp =
			pCDedRosenFileData->getCdDedDispProp();

		CDlgOuJikokuhyouCsvExport	aDlg( 
			pCDedRosenFileData->getCentDedRosen() , 
			pCJikokuhyouDoc->getDiaIndex() , 
			pCJikokuhyouDoc->getRessyahoukou() ,
			m_bDisplayTsuukaEkiJikoku,
			m_bDisplaySecondEkiJikoku,
			m_bDisplayColonEkiJikoku,
			m_bDisplayShihatsuShuchakuEkimei,
			m_bDisplayParentSyubetsu,
			aCdDedDispProp.getDisplayRessyamei(),
			getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getEnableOperation(),
			aCdDedDispProp.getDisplayOuterTerminalShihatsu(getRessyahoukou()),
			aCdDedDispProp.getDisplayOuterTerminalShuchaku(getRessyahoukou()),
			aCdDedDispProp.getSecondRoundChaku(),
			aCdDedDispProp.getSecondRoundHatsu(),
			aCdDedDispProp.getDisplay2400(),
			aCdDedDispProp.getOperationNumberRows(),
			aCdDedDispProp.getDisplayInOutLinkCode(),
			getCustomizeDisplayMode(),
			this ) ;
		aDlg.DoModal() ;
	
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv ;
}

int CWndJikokuhyou::OnJikokuhyouViewProp_Process( BOOL bQueryEnable ) 
{
	int iRv = 0 ;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (getCustomizeDisplayMode())
		{
			iRv = -1;
		}
	}
	// ****************************************************************
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		CDlgJikokuhyouViewProp aDlg( 
			m_jikanPasteIdouryou , 
			m_iRessyaBangouPasteIdouryou,
			m_iGouPasteIdouryou,
			m_eEkijikokuSort ,
			m_bCompareBottom,
			this ) ;
		if ( aDlg.DoModal() == IDOK )
		{
			m_jikanPasteIdouryou = aDlg.getPasteIdouryou() ;
			m_jikanPasteIdouryouPrevValue = 0 ;
			m_eEkijikokuSort = aDlg.getEkijikokuSort() ;
			m_iRessyaBangouPasteIdouryou = aDlg.getPasteIdouryouRessyaBangou();
			m_iRessyaBangouPasteIdouryouPrevValue = 0;
			m_iGouPasteIdouryou = aDlg.getPasteIdouryouRessyaGou();
			m_iGouPasteIdouryouPrevValue = 0;
			m_bCompareBottom = aDlg.getCompareBottom();

			//	EkijikokuSort の設定を、
			//	.ini ファイルに保存
			getCDiagramEditApp()->writeCWndJikokuhyouViewProp( this ) ;

			iRv = 1 ;	//	ダイアログボックスでの入力が適用されました。
		}
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv ;
}

int CWndJikokuhyou::OnJikokuhyouDiagramHeIdou_Process( BOOL bQueryEnable ) 
{
	int iRv = 0 ;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	const Mu<const CentDedRessya*>* pCentDedRessyaCont = getCentDedRessyaCont()->getMuPtr() ;

	CDcdGridCell*	pCDcdGridCell = NULL ;
	if ( iRv >= 0 ){
		 pCDcdGridCell = getCFocus()->getFocusCell() ;
		if ( pCDcdGridCell == NULL ){
			iRv = -11  ;	//	セルの場所が不正
		}
	}
	//pCDcdGridCell = 編集中のセル
	
	int iRessyaIdx = -1 ;
	const CentDedRessya* pCentDedRessya = NULL ;
	if ( iRv >= 0 ){
		iRessyaIdx = getXColSpecOfFocus().getRessyaIndex() ;
		if (getCustomizeDisplayMode())
		{
			CustomizeJikokuhyouContent contRessyaIndex =
				getCentDedDia()->getcontCustomizeRessyaIndex(getRessyahoukou(), getXColSpecOfFocus().getRessyaIndex());
			if (contRessyaIndex.iRessyaIndexCont.empty())
			{
				iRv = -7;	//選択列に列車がありません
			}
			else
			{
				iRessyaIdx = contRessyaIndex.iRessyaIndexCont.front();
			}
		}

		if ( !( 0 <= iRessyaIdx && iRessyaIdx < pCentDedRessyaCont->size() ) ){
			//	セルの位置が、特定の列車の特定の時刻の場所ではない
			//	エラーにはしません。
		}	else	{
			pCentDedRessya = pCentDedRessyaCont->get( iRessyaIdx ) ;
		}
	}
	//iRessyaIdx = 列車Index
	//pCentDedRessya = 指定のセルに対応する『列車』
	//	対応する列車がない場合はNULL
	
	CdDedJikokuOrder aJikokuOrder;
	if ( iRv >= 0 )
	{
		aJikokuOrder = CdDedJikokuOrderOf( getYColSpecOfFocus() ) ;
	}
	//aJikokuOrder = 指定のセルに対応する『時刻Order』
	//	ないならNULL

	CdDedJikoku	jikokuFocus ;
	if ( iRv >= 0 ){
		if ( pCentDedRessya != NULL ){
			jikokuFocus = pCentDedRessya->getEkiJikoku( aJikokuOrder ) ;
		}
	}
	//jikokuFocus = フォーカスのあるセルの時刻。ないならNULL

	// ****************************************************************
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		// --------------------------------
		//	ダイヤグラムビューを開く
		// --------------------------------
		CDedDiagramView* pCDedDiagramView = NULL ;
		if ( iRv >= 0 ){
			
			const CDedDiagramDoc* pCDedDiagramDoc = NULL ;
			if ( iRv >= 0 ){
				pCDedDiagramDoc = 
					getCDiagramEditApp()->openCDedDiagramDoc( 
						getCentDedDia()  ) ; 
				if ( pCDedDiagramDoc == NULL ){
					iRv = -2 ;	//	ダイヤグラムビューのオープンに失敗しました
				}
			}
			//pCJikokuhyouDoc = ダイヤグラムドキュメント
			//	ビューがアクティブになっています。
			
			if ( iRv >= 0 ){
				POSITION aPOSITION = pCDedDiagramDoc->GetFirstViewPosition() ;
				if ( aPOSITION != NULL ){
					pCDedDiagramView = (CDedDiagramView*)pCDedDiagramDoc->GetNextView( aPOSITION ) ;
				}
				if ( pCDedDiagramView == NULL ){
					iRv = -3 ;	//	ダイヤグラムビューのオープンに失敗しました
				}
			}
		}
		//pCDedDiagramView = ダイヤグラムビュー
		if ( iRv >= 0 ){
			pCDedDiagramView->setZone_Dgr( jikokuFocus , 
				getCentDedRessyaCont()->EkiIndexOfEkiOrder( aJikokuOrder.getEkiOrder() ) , 
				getRessyahoukou() == Ressyahoukou_Nobori ) ;
		}
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv ;
}

//17.4.20edit_by_d_mania
int CWndJikokuhyou::OnVIEWDisplayTsuukaEkiJikoku_Process( 
	BOOL bQueryEnable )  
{
	int iRv = 0 ;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if ( getDisplayTsuukaEkiJikoku() )
	{
		iRv = 1 ;	//(bQueryEnable==TRUEの場合)[全時刻を表示]が有効です。
	}
	// ****************************************************************
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドを実行
		// ****************************************************************
		//通過時刻表示と基準機能の両方がONの時に、通過時刻をOFFにする場合は、基準もOFFにする。
		if( getDisplayTsuukaEkiJikoku() &&
			getStandardOperationTimeFunction() )
		{
			setStandardOperationTimeFunction( false ) ;
		}
		setDisplayTsuukaEkiJikoku( !getDisplayTsuukaEkiJikoku() ) ;
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv ;
}

int CWndJikokuhyou::OnViewDisplayallekijikoku_Process( 
	BOOL bQueryEnable ) 
{
	int iRv = 0 ;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (getCustomizeDisplayMode())
	{
		iRv = -1;
	}
	if (iRv >= 0 && getDisplayAllEkiJikoku())
	{
		iRv = 1;	//	(bQueryEnable==TRUEの場合)[全時刻を表示]が有効です。
	}

	// ****************************************************************
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドを実行
		// ****************************************************************
		const CentDedRosen*	pCentDedRosen = 
			getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen() ;
		// --------------------------------
		//	Gridの配置を変更する前の、
		//	フォーカスセルの表示内容を取得
		// --------------------------------
		CDcdGridCell*	pCDcdGridCell = getCFocus()->getFocusCell() ;
		int iYColumnNumber = getCXDcdGrid()->getYColumnNumberOfCell(
			pCDcdGridCell) ;
		int iXColumnNumber = getCXDcdGrid()->getXColumnNumberOfCell(
			pCDcdGridCell) ;

		CdYColSpecCont aYColumnSpecCont 
			= createYColSpecCont() ;

		CdYColSpec aYColumnSpec = 
			aYColumnSpecCont.ColumnNumberToSpec( iYColumnNumber ) ;
		//aYColumnSpec = フォーカスセルの表示内容。

		// --------------------------------
		//	全時刻表示モードの変更
		// --------------------------------
		setDisplayAllEkiJikoku( !getDisplayAllEkiJikoku() ) ;
		// --------------------------------
		//	フォーカスセルを、Grid配置変更前と同じ表示内容の位置に移動
		// --------------------------------
		//	Grid配置が変わったため、『列番号-表示内容』の対応表を再作成します。
		aYColumnSpecCont = createYColSpecCont() ;

		//	Grid配置前のフォーカスセルの表示内容に対応した
		//	Y列番号を取得
		iYColumnNumber = aYColumnSpecCont.ColumnNumberFromSpec(
			aYColumnSpec , true ) ;

		pCDcdGridCell = getCXDcdGrid()->getCell( 
			iXColumnNumber , iYColumnNumber ) ;
		getCFocus()->setFocusCell( pCDcdGridCell ) ;
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv ;
}

//add_by_d_mania
int CWndJikokuhyou::OnViewDisplaySecondEkijikoku_Process( 
	BOOL bQueryEnable )  
{
	int iRv = 0 ;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if ( getDisplaySecondEkiJikoku() )
	{
		iRv = 1 ;	//(bQueryEnable==TRUEの場合)[秒単位の時刻を表示]が有効です。
	}
	// ****************************************************************
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドを実行
		// ****************************************************************
		setDisplaySecondEkiJikoku( !getDisplaySecondEkiJikoku() ) ;
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv ;
}

//17.4.20edit_by_d_mania
//add_by_d_mania
int CWndJikokuhyou::OnViewStandardOperationTimeFunction_Process( 
	BOOL bQueryEnable )  
{
	int iRv = 0 ;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (getCustomizeDisplayMode())
	{
		iRv = -1;
	}
	if (iRv >= 0 && getStandardOperationTimeFunction())
	{
		iRv = 1;	//(bQueryEnable==TRUEの場合)[基準運転時分機能を有効にする]が有効です。
	}
	// ****************************************************************
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドを実行
		// ****************************************************************
		//通過時刻表示と基準機能の両方がOFFの時に、基準機能をONにする場合は、通過時刻表示もONにする。
		if( !getDisplayTsuukaEkiJikoku() &&
			!getStandardOperationTimeFunction() )
		{
			setDisplayTsuukaEkiJikoku( true ) ;
		}
		setStandardOperationTimeFunction( !getStandardOperationTimeFunction() ) ;
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv ;
}

int CWndJikokuhyou::OnViewDisplayShihatsuShuchakuEkimei_Process(BOOL bQueryEnable)
{
	int iRv = 0;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (getDisplayShihatsuShuchakuEkimei())
	{
		iRv = 1;	//	(bQueryEnable==TRUEの場合)[全時刻を表示]が有効です。
	}

	// ****************************************************************
	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドを実行
		// ****************************************************************
		const CentDedRosen*	pCentDedRosen =
			getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen();
		// --------------------------------
		//	Gridの配置を変更する前の、
		//	フォーカスセルの表示内容を取得
		// --------------------------------
		CDcdGridCell*	pCDcdGridCell = getCFocus()->getFocusCell();
		int iYColumnNumber = getCXDcdGrid()->getYColumnNumberOfCell(
			pCDcdGridCell);
		int iXColumnNumber = getCXDcdGrid()->getXColumnNumberOfCell(
			pCDcdGridCell);

		CdYColSpecCont aYColumnSpecCont
			= createYColSpecCont();

		CdYColSpec aYColumnSpec =
			aYColumnSpecCont.ColumnNumberToSpec(iYColumnNumber);
		//aYColumnSpec = フォーカスセルの表示内容。

		// --------------------------------
		//	全時刻表示モードの変更
		// --------------------------------
		setDisplayShihatsuShuchakuEkimei(!getDisplayShihatsuShuchakuEkimei());
		// --------------------------------
		//	フォーカスセルを、Grid配置変更前と同じ表示内容の位置に移動
		// --------------------------------
		//	Grid配置が変わったため、『列番号-表示内容』の対応表を再作成します。
		aYColumnSpecCont = createYColSpecCont();

		//	Grid配置前のフォーカスセルの表示内容に対応した
		//	Y列番号を取得
		iYColumnNumber = aYColumnSpecCont.ColumnNumberFromSpec(
			aYColumnSpec, true);

		pCDcdGridCell = getCXDcdGrid()->getCell(
			iXColumnNumber, iYColumnNumber);
		getCFocus()->setFocusCell(pCDcdGridCell);
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv;
}

int CWndJikokuhyou::OnViewDisplayColonEkijikoku_Process(
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

int CWndJikokuhyou::OnViewOperationupdatestop_Process(BOOL bQueryEnable)
{
	int iRv = 0;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (getCustomizeDisplayMode())
	{
		iRv = -1;
	}
	if (iRv>=0&&getOperationUpdateStop())
	{
		iRv = 1;	//(bQueryEnable==TRUEの場合)[秒単位の時刻を表示]が有効です。
	}
	// ****************************************************************
	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドを実行
		// ****************************************************************
		setOperationUpdateStop(!getOperationUpdateStop());
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv;
}

int CWndJikokuhyou::OnViewDisplayParentSyubetsu_Process(
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

int CWndJikokuhyou::OnViewDisplayTsuukaFontPerSyubetsu_Process(
	BOOL bQueryEnable)
{
	int iRv = 0;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (getDisplayTsuukaFontPerSyubetsu())
	{
		iRv = 1;	//(bQueryEnable==TRUEの場合)[秒単位の時刻を表示]が有効です。
	}
	// ****************************************************************
	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドを実行
		// ****************************************************************
		setDisplayTsuukaFontPerSyubetsu(!getDisplayTsuukaFontPerSyubetsu());
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv;
}


CString CWndJikokuhyou::OnUpdateINDICATOR_PasteZoubun_Process() 
{
	CString	strLs ;
	if ( m_StateMachine.getCurrentStateIdx() == StateIdx_Renzoku  )
	{
		//	連続入力モード
		strLs.LoadString( IDS_INDICATOR_Renzoku ) ;
	}
	else
	{
		//	その他
		//秒出力を追加、分がゼロの場合のみ、秒は符号出力 edit_by_d_mania
		if( m_jikanPasteIdouryou.getTotalSeconds() / 60 == 0 )
		{
		strLs.Format( ID_INDICATOR_PasteZoubun , 
			m_jikanPasteIdouryou.getTotalSeconds() / 60 , 
			m_jikanPasteIdouryou.getTotalSeconds() % 60 , 
			( m_jikanPasteIdouryouPrevValue.getTotalSeconds() + 
				m_jikanPasteIdouryou.getTotalSeconds() ) / 60  ,
			( m_jikanPasteIdouryouPrevValue.getTotalSeconds() + 
				m_jikanPasteIdouryou.getTotalSeconds() ) % 60 )	;
		}
		else
		{
		strLs.Format( ID_INDICATOR_PasteZoubun , 
			m_jikanPasteIdouryou.getTotalSeconds() / 60 , 
			abs( m_jikanPasteIdouryou.getTotalSeconds() % 60 ) , 
			( m_jikanPasteIdouryouPrevValue.getTotalSeconds() + 
				m_jikanPasteIdouryou.getTotalSeconds() ) / 60  ,
			abs( ( m_jikanPasteIdouryouPrevValue.getTotalSeconds() + 
				m_jikanPasteIdouryou.getTotalSeconds() ) % 60 ) )	;
		}
	}
	return strLs ;
}



// --------------------------------
//@name 下請関数
// --------------------------------


// ********************************
//@name	CDcdGrid
// ********************************

	// --------------------------------
	//@name 行・列・セルの初期化
	// --------------------------------
void CWndJikokuhyou::OnCreateXColumn( int iXColumnNumber , 
		CDcdGridXColumn* pCDcdGridXColumn ) 
{
	pCDcdGridXColumn->getCDcdGridXBorder()->setAutoColumnBorderSize( false ) ;
	pCDcdGridXColumn->setAutoColumnSize( false ) ;

	super::OnCreateXColumn( iXColumnNumber , 
		pCDcdGridXColumn ) ;
}

	
void CWndJikokuhyou::OnCreateYColumn( int iYColumnNumber , 
		CDcdGridYColumn* pCDcdGridYColumn ) 
{
	pCDcdGridYColumn->getCDcdGridYBorder()->setAutoColumnBorderSize( false ) ;
	pCDcdGridYColumn->setAutoColumnSize( false ) ;

	super::OnCreateYColumn( iYColumnNumber , 
			pCDcdGridYColumn ) ;
}

	
// ********************************
//@name	CWndDcdGrid
// ********************************
	// --------------------------------
	//@name	イベント処理のための仮想関数
	// --------------------------------
void CWndJikokuhyou::OnSetFocusCell( CDcdGridCell* pCDcdGridCell ) 
{
	m_StateMachine.getCurrentState()->
		OnSetFocusCell( pCDcdGridCell ) ;

	//	super::OnSetFocusCell( pCDcdGridCell ) ;
}

void CWndJikokuhyou::OnSetXFixafterColumnNumber( int iFixafterColumnNumber ) 
{
	m_StateMachine.getCurrentState()->
		OnSetXFixafterColumnNumber( iFixafterColumnNumber ) ;
	//	super::OnSetXFixafterColumnNumber( iFixafterColumnNumber ) ;
}

void CWndJikokuhyou::OnSetYFixafterColumnNumber( int iFixafterColumnNumber ) 
{
	m_StateMachine.getCurrentState()->
		OnSetYFixafterColumnNumber( iFixafterColumnNumber ) ;
	//	super::OnSetYFixafterColumnNumber( iFixafterColumnNumber ) ;
}

void CWndJikokuhyou::OnChangeSelectCell( 
		int iXColumnNumber , int iYColumnNumber , bool bIsSelected ) 
{
	m_StateMachine.getCurrentState()->
		OnChangeSelectCell( iXColumnNumber , iYColumnNumber , bIsSelected ) ;
}


// ********************************
//	コンストラクタ
// ********************************
CWndJikokuhyou::CWndJikokuhyou()
	: m_jikanPasteIdouryou( 0 )
	, m_bDisplayTsuukaEkiJikoku( true )
	, m_bDisplayAllEkiJikoku( false ) 
	, m_eEkijikokuSort( EEkijikokuSort_Ekiatsukai )	// 駅扱でのソート
	, m_bModifyEkijikoku( true )
	, m_jikanPasteIdouryouPrevValue( 0 )
	, m_bUpdate_All_Requested( true )
	, m_bReadCWndJikokuhyouDefault( false ) 
	, m_bDisplaySecondEkiJikoku( false ) 
	, m_bStandardOperationTimeFunction( false )
	, m_bDisplayShihatsuShuchakuEkimei(false)
	, m_bDisplayColonEkiJikoku(false)
	, m_bOperationUpdateStop(false)
	, m_bDisplayParentSyubetsu(false)
	, m_bDisplayTsuukaFontPerSyubetsu(false)
	, m_iRessyaBangouPasteIdouryou(0)
	, m_iRessyaBangouPasteIdouryouPrevValue(0)
	, m_iGouPasteIdouryou(0)
	, m_iGouPasteIdouryouPrevValue(0)
	, m_bCompareBottom(false)
{
	//	選択テキストカラーを設定
	{
		Ou<CDcdFillrectRop>	pIfDcDraw = dynamic_castOu<CDcdFillrectRop>(
			getCSelect()->getIfDcDrawSelect() ) ;

		//	選択テキストカラー=黒
		pIfDcDraw->setCdBrushProp( CdColorProp( 0 , 0 , 0 ) ) ;
	}
}
CWndJikokuhyou::~CWndJikokuhyou()
{
}


// ********************************
//@name	CWndJikokuhyou
// ********************************
	// ********************************
	//@name CWndJikokuhyou-属性
	// ********************************
bool CWndJikokuhyou::getDisplayTsuukaEkiJikoku()const 
{
	return m_bDisplayTsuukaEkiJikoku ;
}
int CWndJikokuhyou::setDisplayTsuukaEkiJikoku( bool value ) 
{
	int iRv = 0 ;
	if ( m_bDisplayTsuukaEkiJikoku != value )
	{
		m_bDisplayTsuukaEkiJikoku = value ;

		//	通過列車の表示の有無が変化した場合は、
		//	ビューの駅時刻を更新します。
		updateUISetAllRessya() ;
		InvalidateGrid() ;

		//	通過列車の表示の有無を、
		//	.ini ファイルに保存
		getCDiagramEditApp()->writeCWndJikokuhyouViewProp( this ) ;
	}
	return ( iRv ) ;
}

bool CWndJikokuhyou::getDisplayAllEkiJikoku()const
{	return m_bDisplayAllEkiJikoku ;};

int CWndJikokuhyou::setDisplayAllEkiJikoku( bool value )
{
	int iRv = 0 ;
	if ( m_bDisplayAllEkiJikoku != value )
	{
		m_bDisplayAllEkiJikoku = value ;

		//	グリッドの列数が変わりますので、
		//	ビューの全更新が必要です。
		//	ただし、他のビューを更新する 必要はありません。
		updateUIAll() ;

		//	表示設定を .ini ファイルに保存
		getCDiagramEditApp()->writeCWndJikokuhyouViewProp( this ) ;
	}
	return ( iRv ) ;
}


void CWndJikokuhyou::setModifyEkijikoku( bool value )
{
	if ( m_bModifyEkijikoku != value )
	{
		m_bModifyEkijikoku = value ;
	
		//	表示設定を .ini ファイルに保存
		getCDiagramEditApp()->writeCWndJikokuhyouViewProp( this ) ;
	}
};

//add_by_d_mania
bool CWndJikokuhyou::getDisplaySecondEkiJikoku()const 
{
	return m_bDisplaySecondEkiJikoku ;
}
int CWndJikokuhyou::setDisplaySecondEkiJikoku( bool value ) 
{
	int iRv = 0 ;
	if ( m_bDisplaySecondEkiJikoku != value )
	{
		m_bDisplaySecondEkiJikoku = value ;

		//	秒単位の表示の有無が変化した場合は、
		//	ビューの駅時刻を更新します。
		updateUISetAllRessya() ;
		InvalidateGrid() ;

		//	秒単位の表示の有無を、
		//	.ini ファイルに保存
		getCDiagramEditApp()->writeCWndJikokuhyouViewProp( this ) ;
	}
	return ( iRv ) ;
}

//add_by_d_mania
bool CWndJikokuhyou::getStandardOperationTimeFunction()const 
{
	return m_bStandardOperationTimeFunction ;
}
int CWndJikokuhyou::setStandardOperationTimeFunction( bool value ) 
{
	int iRv = 0 ;
	if ( m_bStandardOperationTimeFunction != value )
	{
		m_bStandardOperationTimeFunction = value ;

		//	基準運転時分機能の有無が変化した場合は、
		//	ビューの駅時刻を更新します。
		updateUISetAllRessya() ;
		InvalidateGrid() ;

		//	基準運転時分機能の有無を
		//	.ini ファイルに保存
		getCDiagramEditApp()->writeCWndJikokuhyouViewProp( this ) ;
	}
	return ( iRv ) ;
}

bool CWndJikokuhyou::getDisplayShihatsuShuchakuEkimei()const
{
	return m_bDisplayShihatsuShuchakuEkimei;
};

int CWndJikokuhyou::setDisplayShihatsuShuchakuEkimei(bool value)
{
	int iRv = 0;
	if (m_bDisplayShihatsuShuchakuEkimei != value)
	{
		m_bDisplayShihatsuShuchakuEkimei = value;

		//	グリッドの列数が変わりますので、
		//	ビューの全更新が必要です。
		//	ただし、他のビューを更新する 必要はありません。
		updateUIAll();

		//	表示設定を .ini ファイルに保存
		getCDiagramEditApp()->writeCWndJikokuhyouViewProp(this);
	}
	return (iRv);
}

bool CWndJikokuhyou::getDisplayColonEkiJikoku()const
{
	return m_bDisplayColonEkiJikoku;
}
int CWndJikokuhyou::setDisplayColonEkiJikoku(bool value)
{
	int iRv = 0;
	if (m_bDisplayColonEkiJikoku != value)
	{
		m_bDisplayColonEkiJikoku = value;

		//	秒単位の表示の有無が変化した場合は、
		//	ビューの駅時刻を更新します。
		updateUISetAllRessya();
		InvalidateGrid();

		//	秒単位の表示の有無を、
		//	.ini ファイルに保存
		getCDiagramEditApp()->writeCWndJikokuhyouViewProp(this);
	}
	return (iRv);
}

bool CWndJikokuhyou::getOperationUpdateStop() const
{
	return m_bOperationUpdateStop;
}

int CWndJikokuhyou::setOperationUpdateStop(bool value)
{
	int iRv = 0;
	if (m_bOperationUpdateStop != value)
	{
		m_bOperationUpdateStop = value;

		if (!m_bOperationUpdateStop)
		{
			// ****************************************************************
			//	コマンドの実行
			// ****************************************************************
			OuNew<CRfEditCmd> pCmd(
				new CRfEditCmd_Operation(
					GetDocument()->getDiaIndex()));
			// --------------------------------
			//	コマンドオブジェクトを実行
			// --------------------------------
			getCDiagramEditDoc()->executeEditCmd(pCmd);

			//getCDiagramEditDoc()->OperationConnect(GetDocument()->getDiaIndex());
			//	ビューの駅時刻を更新します。
			updateUI_AllOperationNumber();
			InvalidateGrid();

		}
	}
	return (iRv);
}

bool CWndJikokuhyou::getDisplayParentSyubetsu()const
{
	return m_bDisplayParentSyubetsu;
}
int CWndJikokuhyou::setDisplayParentSyubetsu(bool value)
{
	int iRv = 0;
	if (m_bDisplayParentSyubetsu != value)
	{
		m_bDisplayParentSyubetsu = value;

		//	秒単位の表示の有無が変化した場合は、
		//	ビューの駅時刻を更新します。
		updateUISetAllRessya();
		InvalidateGrid();

		//	秒単位の表示の有無を、
		//	.ini ファイルに保存
		getCDiagramEditApp()->writeCWndJikokuhyouViewProp(this);
	}
	return (iRv);
}

bool CWndJikokuhyou::getDisplayTsuukaFontPerSyubetsu()const
{
	return m_bDisplayTsuukaFontPerSyubetsu;
}
int CWndJikokuhyou::setDisplayTsuukaFontPerSyubetsu(bool value)
{
	int iRv = 0;
	if (m_bDisplayTsuukaFontPerSyubetsu != value)
	{
		m_bDisplayTsuukaFontPerSyubetsu = value;

		//	通過駅時刻の表示フォントが変化した場合は、
		//	ビューの駅時刻を更新します。
		updateUISetAllRessya();
		InvalidateGrid();

		//	秒単位の表示の有無を、
		//	.ini ファイルに保存
		getCDiagramEditApp()->writeCWndJikokuhyouViewProp(this);
	}
	return (iRv);
}


	// ********************************
	//@name CDiagramView からの委譲
	// ********************************
void CWndJikokuhyou::OnUpdate(
	CView* pSender, LPARAM lHint, CObject* pHint)
{
	if ( !m_bReadCWndJikokuhyouDefault )
	{
		// --------------------------------
		//	.ini ファイルから、状態を読み込み
		// --------------------------------
		getCDiagramEditApp()->readCWndJikokuhyouViewProp( this ) ;
		
		m_bReadCWndJikokuhyouDefault = true ;
	}
	if (getCustomizeDisplayMode())
	{
		m_bStandardOperationTimeFunction = false;
		m_bDisplayAllEkiJikoku = false;
	}

	//	更新は、CWjkState オブジェクトで行います。
	{
		m_StateMachine.getCurrentState()->
			OnUpdate( pSender, lHint, pHint) ;
		//memo:
		//	「全更新要求 AND このビューが非アクティブビュー」の場合でも、
		//	更新を行う必要があります。
		//	全更新要求の場合は、列車選択モード・連続入力モードを
		//	退場する必要があるためです。
	}


}

void CWndJikokuhyou::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	LogMsg(_T("CWndJikokuhyou::OnActivateView(%d,,)") , bActivate ) ;
	
	if ( bActivate && m_bUpdate_All_Requested ){
		//	updateUI... 関数を呼び出す前に、この変数を false に
		//	しなくてはなりません。
		//	この変数が true だと、OnUpdate の下請関数は何もせずに
		//	return します。
		m_bUpdate_All_Requested = false ;

		updateUIAll() ;
	}
}

	// ********************************
	//@name static CWndJikokuhyou-操作
	// ********************************
CdDedJikokuOrder 
CWndJikokuhyou::CdDedJikokuOrderOf( 
		const CdYColSpec& aYColSpec ) 
{
	CdDedJikokuOrder	aJikokuOrder ;
	if ( aYColSpec.getColumnType() 
		== CdYColSpec::ColumnType_Ekijikoku_Chaku )
	{
		aJikokuOrder.setEkiOrder( aYColSpec.getEkiOrder() , 
			CdDedJikokuOrder::EkiJikokuItem_Chaku ) ;
	}
	else if ( aYColSpec.getColumnType() 
		== CdYColSpec::ColumnType_Ekijikoku_Hatsu )
	{
		aJikokuOrder.setEkiOrder( aYColSpec.getEkiOrder() , 
			CdDedJikokuOrder::EkiJikokuItem_Hatsu ) ;
	}
	return aJikokuOrder ;
}
CdYColSpec 
CWndJikokuhyou::CdYColSpecOf( 
		const CdDedJikokuOrder& aJikokuOrder ) 
{
	CdYColSpec aYColSpec ;
	if ( aJikokuOrder.getEkiJikokuItem() 
		== CdDedJikokuOrder::EkiJikokuItem_Chaku )
	{
		aYColSpec.set( CdYColSpec::ColumnType_Ekijikoku_Chaku ,
			aJikokuOrder.getEkiOrder() ) ;
	}
	else if ( aJikokuOrder.getEkiJikokuItem() 
		== CdDedJikokuOrder::EkiJikokuItem_Hatsu )
	{
		aYColSpec.set( CdYColSpec::ColumnType_Ekijikoku_Hatsu ,
			aJikokuOrder.getEkiOrder() ) ;
	}
	return aYColSpec ;
}


	// ********************************
	//@name CWndJikokuhyou-操作
	// ********************************

CdXColSpecCont 
CWndJikokuhyou::createXColSpecCont() 
{
	CdXColSpecCont aXColumnSpecCont ;
	const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont() ;
	if ( pCentDedRessyaCont != NULL )
	{
		aXColumnSpecCont.scan(pCentDedRessyaCont,
			getCustomizeDisplayMode(),
			getCentDedDia()->getcontCustomizeRessyaIndex(getRessyahoukou()));
	}
	return aXColumnSpecCont ;
}

CdYColSpecCont 
CWndJikokuhyou::createYColSpecCont() 
{
	const CentDedRosen*	pCentDedRosen = 
		getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen() ;
	const CdDedDispProp aCdDedDispProp =
		getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();

	CdYColSpecCont aYColumnSpecCont ;

	aYColumnSpecCont.scan(
		pCentDedRosen->getCentDedEkiCont() ,
		getRessyahoukou() ,
		m_bDisplayAllEkiJikoku ,
		getCustomizeDisplayMode(),
		m_bDisplayShihatsuShuchakuEkimei,
		aCdDedDispProp.getDisplayRessyamei(),
		pCentDedRosen->getEnableOperation(),
		aCdDedDispProp.getDisplayOuterTerminalShihatsu(getRessyahoukou()),
		aCdDedDispProp.getDisplayOuterTerminalShuchaku(getRessyahoukou()),
		aCdDedDispProp.getOperationNumberRows(),
		aCdDedDispProp.getDisplayInOutLinkCode());
	return aYColumnSpecCont ;
}

CdXColSpec 
CWndJikokuhyou::getXColSpecOfFocus() 
{
	CdXColSpec aXColSpec ;

	CdXColSpecCont aXColSpecCont 
				= createXColSpecCont() ;
	CdDcdPosXy	posFocusCell = getCFocus()->getFocusCellColumnNumber() ;
	aXColSpec = aXColSpecCont.ColumnNumberToSpec( posFocusCell.getX() ) ;

	return aXColSpec ;
}
CdYColSpec 
CWndJikokuhyou::getYColSpecOfFocus() 
{
	CdYColSpec aYColSpec ;

	CdYColSpecCont aYColSpecCont 
				= createYColSpecCont() ;
	CdDcdPosXy	posFocusCell = getCFocus()->getFocusCellColumnNumber() ;
	aYColSpec = aYColSpecCont.ColumnNumberToSpec( posFocusCell.getY() ) ;

	return aYColSpec ;
}


int CWndJikokuhyou::
	moveFocusCellToNext( bool bJikokuhyouFocusToRight , bool bNextEkiOrder ) 
{
	int iRv = 0 ;
	CDcdGridCell*	pCDcdGridCell = getCFocus()->getFocusCell() ;

	CdXColSpecCont	aXColSpecCont
		= createXColSpecCont() ;

	//	フォーカスを上下に移動
	if ( !bJikokuhyouFocusToRight )
	{
		//	セル移動時に、列車選択が変動しないようにします。
		CPropStack aPropStack( this ) ;
		aPropStack.CBoxSelect_setIsEnable( false ).CRandomSelect_setIsEnable( false ) ;

		//	移動先のセル位置を求める
		CdYColSpecCont aYColSpecCont = createYColSpecCont() ;

		int iYColumnNumber = getCXDcdGrid()->getYColumnNumberOfCell(pCDcdGridCell) ;
		int iXColumnNumber = getCXDcdGrid()->getXColumnNumberOfCell(pCDcdGridCell) ;
		if ( 0 <= iYColumnNumber && 
				iYColumnNumber < 
				aYColSpecCont.getColumnNumber_Ekijikoku_begin() )
		{
			//iYColumnNumber = 列車番号～号数までの間（駅時刻の上）
			//	にあります。
			//	この場合は、一番上の駅時刻に移動します。
			iYColumnNumber = 
				aYColSpecCont.getColumnNumber_Ekijikoku_begin() ;
		}
		else if ( 
			aYColSpecCont.getColumnNumber_Ekijikoku_begin() <= 
				iYColumnNumber && 
			iYColumnNumber < 
				aYColSpecCont.getColumnNumber_Ekijikoku_end() )
		{
			//iYColumnNumber = 駅時刻の位置にあります。
			if ( bNextEkiOrder && 
				aXColSpecCont.getColumnNumber_Ressya_begin() <= iXColumnNumber	)
			{
				//	bNextEkiOrder が真で、フォーカスが特定列車上にある場合	
				CdDedJikokuOrder	aJikokuOrder = CdDedJikokuOrderOf( 
					aYColSpecCont.ColumnNumberToSpec( iYColumnNumber ) ) ;
				if ( !aJikokuOrder.getIsNull() )
				{
					//iYColumnNumber = 駅時刻の位置にあります。
					//	次の駅の着時刻の列番号
					iYColumnNumber = aYColSpecCont.ColumnNumberFromSpec( 
						CdYColSpec(
							CdYColSpec::ColumnType_Ekijikoku_Chaku ,
							aJikokuOrder.getEkiOrder() + 1  ) , false ) ;
					//iYColumnNumber=次の駅の着時刻の列番号
					if ( iYColumnNumber < 0 )
					{
						iYColumnNumber = aYColSpecCont.ColumnNumberFromSpec( 
						CdYColSpec(
							CdYColSpec::ColumnType_Ekijikoku_Hatsu ,
							aJikokuOrder.getEkiOrder() + 1  ) , false ) ;
					}
					if ( iYColumnNumber < 0 )
					{
						//	一番下の駅時刻からの移動です。
						//	駅時刻の次に移動しました。
						iYColumnNumber = aYColSpecCont.getColumnNumber_Ekijikoku_end() ;
					}

				}
			}
			else
			{
				//	bNextEkiOrder が偽の場合、
				//	フォーカスが特定列車上にある場合	

				//フォーカスセルを次へ移動
				CDcdGridCell*	pCell;
				//CdYColSpecCont aCdYColSpecCont = createYColSpecCont();
				int i = 0;
				do
				{
					i++;
					pCell =getCXDcdGrid()->calcMovedCell(
						pCDcdGridCell,
						0,
						i);
					if (pCell != NULL)
					{
						iYColumnNumber = getCXDcdGrid()->getYColumnNumberOfCell(pCell);
					}

				} while (aYColSpecCont.ColumnNumberToSpec(iYColumnNumber).getColumnType() ==
					CdYColSpec::ColumnType_Track);
			}
		}
		else if ( aYColSpecCont.getColumnNumber_Ekijikoku_end() <= 
					iYColumnNumber )
		{
			//iYColumnNumber = 駅時刻の後(備考欄)にあります。
			//	この場合は、次の列(次の列車)の最上行に移動します。	
			iYColumnNumber = 0 ;
			if ( 0 <= iXColumnNumber && 
				iXColumnNumber < aXColSpecCont.getColumnNumber_Ressya_begin() )
			{
				iXColumnNumber = aXColSpecCont.getColumnNumber_Ressya_begin() ;
			}
			else
			{
				iXColumnNumber ++ ;
			}

		}

		//iYColumnNumber = 次の駅時刻の列番号
		//	(-1の場合もあります。(路線の終着駅の駅時刻入力を終えた後))
		if ( iYColumnNumber >= 0 )
		{
			CDcdGridCell*	pCell = 
				getCXDcdGrid()->getCell( 
					iXColumnNumber , 
					iYColumnNumber ) ;
			if ( pCell )
			{
				getCFocus()->setFocusCell( pCell ) ;
			}
		}
	}
	//	フォーカス横移動モード
	else
	{
		CDcdGridCell*	pCell = 
			getCXDcdGrid()->calcMovedCell( 
				getCFocus()->getFocusCell() , 
				+1 , 
				0 ) ;
		if ( pCell ){
			getCFocus()->setFocusCell( pCell ) ;
		}

		//	フォーカス横移動モードでは、選択を解除します。
		clearSelect() ;

	}


	return ( iRv ) ;
}

int CWndJikokuhyou::
	moveFocusCellToPrev( bool bJikokuhyouFocusToRight , bool bNextEkiOrder ) 
{
	int iRv = 0 ;
	CDcdGridCell*	pCDcdGridCell = getCFocus()->getFocusCell() ;

	CdXColSpecCont	aXColSpecCont
		= createXColSpecCont() ;
	CdYColSpecCont	aYColSpecCont
		= createYColSpecCont() ;

	//	フォーカスを上下に移動
	if ( !bJikokuhyouFocusToRight )
	{
		//	セル移動時に、列車選択が変動しないようにします。
		CPropStack aPropStack( this ) ;
		aPropStack.CBoxSelect_setIsEnable( false ).CRandomSelect_setIsEnable( false ) ;


		//	移動先のセル位置を求める
		int iYColumnNumber = getCXDcdGrid()->getYColumnNumberOfCell(pCDcdGridCell) ;
		int iXColumnNumber = getCXDcdGrid()->getXColumnNumberOfCell(pCDcdGridCell) ;
		if ( 0 <= iYColumnNumber && 
			iYColumnNumber < 
			aYColSpecCont.getColumnNumber_Ekijikoku_begin() )
		{
			//iYColumnNumber = 列車番号～号数までの間（駅時刻の上）
			//	にあります。
			//	この場合は、前の列(列車)の、備考欄 に移動します。
			iYColumnNumber = aYColSpecCont.getColumnNumber_Ekijikoku_end()  ;

			iXColumnNumber -- ;

		}
		else if ( 
			aYColSpecCont.getColumnNumber_Ekijikoku_begin() <= 
				iYColumnNumber && 
			iYColumnNumber < 
				aYColSpecCont.getColumnNumber_Ekijikoku_end() )
		{
			//iYColumnNumber = 駅時刻の位置にあります。
			if ( bNextEkiOrder &&
				aXColSpecCont.getColumnNumber_Ressya_begin() <= iXColumnNumber	)
			{
				//	bNextEkiOrder が真で、フォーカスが特定列車上にある場合	

				CdDedJikokuOrder aJikokuOrder = CdDedJikokuOrderOf(
					aYColSpecCont.ColumnNumberToSpec( iYColumnNumber ) )  ;

				if ( !aJikokuOrder.getIsNull() )
				{
					//iYColumnNumber = 駅時刻の位置にあります。
					iYColumnNumber = aYColSpecCont.ColumnNumberFromSpec( 
						CdYColSpec( 
							CdYColSpec::ColumnType_Ekijikoku_Chaku ,
							aJikokuOrder.getEkiOrder() - 1  ) , false ) ;
					//iYColumnNumber = 前の駅の着駅
					if ( iYColumnNumber < 0 )
					{
						iYColumnNumber = aYColSpecCont.ColumnNumberFromSpec( 
							CdYColSpec( 
								CdYColSpec::ColumnType_Ekijikoku_Hatsu ,
								aJikokuOrder.getEkiOrder() - 1  ) , false ) ;
					}
					if ( iYColumnNumber < 0 )
					{
						//	フォーカスが始発駅の駅時刻より前になります。
						//	この場合は、列車番号の位置に移動します。
						iYColumnNumber = aYColSpecCont.ColumnNumberFromSpec( 
							CdYColSpec(
							CdYColSpec::ColumnType_Ressyabangou )
							, false ) ;
					}
				}
			}
			else
			{
				CDcdGridCell*	pCell;
				//CdYColSpecCont aCdYColSpecCont = createYColSpecCont();
				int i = 0;
				do
				{
					i--;
					pCell =
						getCXDcdGrid()->calcMovedCell(
							pCDcdGridCell,
							0,
							i);
					if (pCell != NULL)
					{
						iYColumnNumber = getCXDcdGrid()->getYColumnNumberOfCell(pCell);
					}
				} while (aYColSpecCont.ColumnNumberToSpec(iYColumnNumber).getColumnType() ==
					CdYColSpec::ColumnType_Track);
			}
		}
		else if ( aYColSpecCont.getColumnNumber_Ekijikoku_end() <= iYColumnNumber )
		{
			//iYColumnNumber = 駅時刻の位置よりあとにあります。
			//	終着駅の最後の駅時刻に移動します。
			iYColumnNumber = aYColSpecCont.getColumnNumber_Ekijikoku_end() - 1 ;
		}

		//iYColumnNumber = 次の駅時刻の列番号
		//	(-1の場合もあります。(路線の終着駅の駅時刻入力を終えた後))
		if ( iYColumnNumber >= 0 )
		{
			CDcdGridCell*	pCell = 
				getCXDcdGrid()->getCell( 
					iXColumnNumber , 
					iYColumnNumber ) ;
			if ( pCell )
			{
				getCFocus()->setFocusCell( pCell ) ;
			}
		}
	}
	//	フォーカス横移動モード
	else
	{
		CDcdGridCell*	pCell = 
			getCXDcdGrid()->calcMovedCell( 
				getCFocus()->getFocusCell() , 
				-1 , 
				0 ) ;
		if ( pCell )
		{
			getCFocus()->setFocusCell( pCell ) ;
		}

		//	フォーカス横移動モードでは、選択を解除します。
		clearSelect() ;

	}


	return ( iRv ) ;
}


int CWndJikokuhyou::execCdModifyEkijikokuCmd(
		Ou<EditCmd::CRfEditCmd_Ressya> pCmd , 
		CdDedJikokuOrder aCdJikokuOrder ) 
{
	int iRv = 0 ;
	CString	strError ;
	// --------------------------------
	int idxError = -1 ;

	// --------------------------------
	//	コマンドオブジェクトの列車を編集
	// --------------------------------
	vector<int> iEkiAtsukaiPrev;
	if ( iRv >= 0 )
	{
		for ( int idxRessya = 0 ; 
			iRv >= 0 && idxRessya < pCmd->getCaMuiSelect()->size() ; 
			idxRessya ++ )
		{
			CentDedRessya*	pCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr()->get( idxRessya ) ; 
			//pCentDedRessya = pCmd 内の列車オブジェクトを指します。

			CentDedEkiJikoku aCentDedEkiJikoku =
				pCentDedRessya->getCentDedEkiJikoku(aCdJikokuOrder.getEkiOrder());
			if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya ||
				aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka)
			{
				iEkiAtsukaiPrev.push_back(1);
			}
			else if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_None)
			{
				iEkiAtsukaiPrev.push_back(0);
			}

			int iResult = m_EkijikokuModifyOperation2.execute( 
				pCentDedRessya , 
				aCdJikokuOrder ) ;
			//	-	-1 ;	//	iJikokuOrder が範囲外です。
			if ( iResult < 0 )
			{
				switch ( iResult ){
				case -1 :	
					iRv = -1 ;	//	X列番号が不正です。
					break ;
				default :	
					iRv = iResult ;
					break ;
				}
				idxError = idxRessya ;
			}
		}
	}
	//idxError = エラーが発生した場合は、
	//	エラーの発生した列車の aCentDedRessyaCont 内でのIndexです。

	// --------------------------------
	//  分岐駅・環状線の駅扱い・番線の補正
	// --------------------------------
	if (iRv >= 0)
	{
		const CentDedEkiCont* pCentDedEkiCont = getCDiagramEditDoc()->getCDedRosenFileData()
			->getCentDedRosen()->getCentDedEkiCont();
		for (int idx = 0; idx < pCmd->getCaMuiSelect()->size(); idx++)
		{
			CentDedRessya*	pCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr()->get(idx);
			int iEkiCount = pCentDedRessya->getCentDedEkiJikokuCount();
			int iEkiOrder = aCdJikokuOrder.getEkiOrder();
			vector<bool> bEkiChecked(iEkiCount, false);

			//まずは、編集対象駅を軸として、調整を行う。
			deque<int> iEkiOrderBrunchOriginSideThis;
			deque<int> iEkiOrderLoopThis;
			deque<int> iEkiOrderBrunchTerminalSideThis;
			deque<int> iEkiOrderCheckedThis;
			if (iEkiOrder >= 0)
			{
				CentDedEkiJikoku aCentDedEkiJikoku =
					pCentDedRessya->getCentDedEkiJikoku(iEkiOrder);
				if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya ||
					aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka)
				{
					int iResult = pCentDedEkiCont->getEkiOrderBrunchLoop(
						iEkiOrder,
						getRessyahoukou(),
						iEkiOrderBrunchOriginSideThis,
						iEkiOrderLoopThis,
						iEkiOrderBrunchTerminalSideThis);
					if (iResult != -1 && iEkiAtsukaiPrev[idx] == 0)
					{
						pCentDedRessya->adjustBrunchLoopByEkijikokuEdit(
							iEkiOrder,
							iEkiOrderBrunchOriginSideThis,
							iEkiOrderLoopThis,
							iEkiOrderBrunchTerminalSideThis,
							iEkiOrderCheckedThis,
							iResult,
							false);
					}
					else if (iResult != -1)
					{
						pCentDedRessya->adjustBrunchLoopByEkijikokuEdit(
							iEkiOrder,
							iEkiOrderBrunchOriginSideThis,
							iEkiOrderLoopThis,
							iEkiOrderBrunchTerminalSideThis,
							iEkiOrderCheckedThis,
							iResult,
							true);
					}
					for (int idxc = 0; idxc < (int)iEkiOrderCheckedThis.size(); idxc++)
					{
						bEkiChecked[iEkiOrderCheckedThis[idxc]] = true;
					}
				}
				bEkiChecked[iEkiOrder] = true;
			}
			//次に、それ以外の駅(列車の運行範囲)について、調整を行う。
			for (int ord = pCentDedRessya->getSihatsuEki();
				ord <= pCentDedRessya->getSyuuchakuEki() 
				&& pCentDedRessya->getSihatsuEki() != -1; ord++)
			{
				deque<int> iEkiOrderBrunchOriginSide;
				deque<int> iEkiOrderLoop;
				deque<int> iEkiOrderBrunchTerminalSide;
				deque<int> iEkiOrderChecked;
				if (bEkiChecked[ord])
				{
					continue;
				}
				CentDedEkiJikoku aCentDedEkiJikoku =
					pCentDedRessya->getCentDedEkiJikoku(ord);
				if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_None)
				{
					bEkiChecked[ord] = true;
					continue;
				}
				int iResult = pCentDedEkiCont->getEkiOrderBrunchLoop(
					ord,
					getRessyahoukou(),
					iEkiOrderBrunchOriginSide,
					iEkiOrderLoop,
					iEkiOrderBrunchTerminalSide);
				if (iResult != -1)
				{
					pCentDedRessya->adjustBrunchLoopByEkijikokuEdit(
						ord,
						iEkiOrderBrunchOriginSide,
						iEkiOrderLoop,
						iEkiOrderBrunchTerminalSide,
						iEkiOrderChecked,
						iResult,
						false);
				}
				bEkiChecked[ord] = true;
				for (int idxc = 0; idxc < (int)iEkiOrderChecked.size(); idxc++)
				{
					bEkiChecked[iEkiOrderChecked[idxc]] = true;
				}
			}
		}
	}

	// --------------------------------
	//	コマンドオブジェクトを実行
	// --------------------------------
	if ( iRv >= 0 )
	{
		getCDiagramEditDoc()->executeEditCmd( pCmd ) ;
	}
	// --------------------------------
	//	エラー表示
	// --------------------------------
	if ( iRv < 0 )
	{
		//	フォーカスセルをエラーの発生した列車へ移します。
		{
			CdDcdPosXy	posFocusCell = getCFocus()->getFocusCellColumnNumber() ;

			CdXColSpecCont aXColSpecCont 
				= createXColSpecCont() ;
			posFocusCell.setX( aXColSpecCont.ColumnNumberFromSpec( 
				CdXColSpec( 
					CdXColSpec::ColumnType_Ressya ,
					pCmd->getIndexDst() + pCmd->getCaMuiSelect()->indexFromAdapteeIndex( idxError ) )
			) );
			
			getCFocus()->setFocusCellColumnNumber( posFocusCell ) ;
		}

		// --------------------------------
		if ( strError.IsEmpty() )
		{
			strError.Format( IDS_ERR_ERRORCODE , iRv ) ;
		}
		MessageBox( strError , NULL , MB_ICONEXCLAMATION | MB_OK ) ; 
	}
	return ( iRv ) ;

}



bool CWndJikokuhyou::createCmd( ECreateCmd eCreateCmd , Ou<DedRosenFileData::EditCmd::CRfEditCmd_Ressya>* ppCmd )
{
	bool bRv = false ;
	Ou<DedRosenFileData::EditCmd::CRfEditCmd_Ressya> pCmd ;

	CdXColSpecCont aCdXColSpecCont = createXColSpecCont() ;
	CdXColSpec  aCdXColSpecOfFocus = getXColSpecOfFocus() ;

	// ********************************
	//	ECreateCmd_NewTrain
	//　新規列車を対象としたコマンドを生成します。
	// ********************************
	if ( eCreateCmd == ECreateCmd_NewItem )
	{
		//	時刻表ビュー上で複数選択がOFF
		if ( getCSelect()->getSelectedCellCount() == 0 )
		{
			//	新規に追加される列車の、初期オブジェクト
			CentDedRessya aNewRessya = getCentDedRessyaCont()->createNullRessya() ;
			aNewRessya.setRessyasyubetsuIndex( 0 ) ;

			//　時刻表ビュー上で複数選択がOFF・フォーカスセルが既存列車上にある場合: 
			// - m_iDiaIndex = フォーカスセルの列車Index、m_iIndexSize = 0
			// - m_CentDedRessyaCont = 空列車(NULLではない)
			// - CaMuSelect,CaMuiSelect = 当該列車を選択。
			if ( aCdXColSpecOfFocus.getColumnType() == CdXColSpec::ColumnType_Ressya )
			{
				bRv = true ;
				if ( ppCmd != NULL )
				{
					pCmd = OuNew<DedRosenFileData::EditCmd::CRfEditCmd_Ressya>( 
						new CRfEditCmd_Ressya( 
							*getCDiagramEditDoc()->getCDedRosenFileData() , 
							GetDocument()->getDiaIndex() , 
							GetDocument()->getRessyahoukou() ,
							aCdXColSpecOfFocus.getRessyaIndex() , 
							0 ) ) ;
					pCmd->getCaMuiSelect()->insert( aNewRessya , INT_MAX ) ;
					pCmd->getCaMuiSelect()->setSelectAll( true ) ;
					pCmd->setWaitOperationConnect(getOperationUpdateStop());
				}
			}
			// 　時刻表ビュー上で複数選択がOFF・フォーカスセルが新規列車位置にある場合:
			// - m_iDiaIndex = 末尾列車Index+1、m_iIndexSize = 0
			// - m_CentDedRessyaCont = 空列車(NULLではない)
			// - CaMuSelect,CaMuiSelect = 当該列車を選択。
			else if ( aCdXColSpecOfFocus.getColumnType() == CdXColSpec::ColumnType_NewRessya )
			{
				bRv = true ;
				if ( ppCmd != NULL )
				{
					pCmd = OuNew<DedRosenFileData::EditCmd::CRfEditCmd_Ressya>( 
						new CRfEditCmd_Ressya( 
							*getCDiagramEditDoc()->getCDedRosenFileData() , 
							GetDocument()->getDiaIndex() , 
							GetDocument()->getRessyahoukou() ,
							aCdXColSpecOfFocus.getRessyaIndex() , 
							0 ) ) ;
					pCmd->getCaMuiSelect()->insert( aNewRessya , INT_MAX ) ;
					pCmd->getCaMuiSelect()->setSelectAll( true ) ;
					pCmd->setWaitOperationConnect(getOperationUpdateStop());
				}
			}
		}
		// 　時刻表ビュー上で複数選択ON:
		// NULLを返します([14/05/18]旧:複数選択OFFの場合と同じ動作)
	}
	// ********************************
	//	ECreateCmd_Focus
	//　フォーカスセル上の1列車を対象としたコマンドを生成します。
	// ********************************
	if ( eCreateCmd == ECreateCmd_Focus )
	{
		//	時刻表ビュー上で複数選択がOFF
		if ( getCSelect()->getSelectedCellCount() == 0 )
		{
			//　時刻表ビュー上で複数選択がOFF・フォーカスセルが既存列車上にある場合: 
			// - m_iDiaIndex = フォーカスセルの列車Index、m_iIndexSize = 1
			// - m_CentDedRessyaCont = フォーカスセル上の列車1個のコピー
			// - m_CaMuiSelect = フォーカスセル上の列車を選択。
			if ( aCdXColSpecOfFocus.getColumnType() == CdXColSpec::ColumnType_Ressya )
			{
				bRv = true ;
				if ( ppCmd != NULL )
				{
					pCmd = OuNew<DedRosenFileData::EditCmd::CRfEditCmd_Ressya>( 
						new CRfEditCmd_Ressya( 
							*getCDiagramEditDoc()->getCDedRosenFileData() , 
							GetDocument()->getDiaIndex() , 
							GetDocument()->getRessyahoukou() ,
							aCdXColSpecOfFocus.getRessyaIndex() , 
							1 ) ) ;
					pCmd->getCaMuiSelect()->setSelectAll( true ) ;
					pCmd->setWaitOperationConnect(getOperationUpdateStop());
				}
			}

			//　時刻表ビュー上で複数選択がOFF・フォーカスセルが新規列車位置にある場合: 
			// - NULLを返します。
		}
		//　時刻表ビュー上で複数選択ON
		// NULLを返します([14/05/18]旧:複数選択OFFの場合と同じ動作)
	}
	// ********************************
	//	ECreateCmd_Select
	//　既存の単数または複数選択されている列車を対象とした
	//	コマンドを生成します。
	// ********************************
	if ( eCreateCmd == ECreateCmd_Select )
	{
		//　時刻表ビュー上で複数選択がOFF・フォーカスセルが既存列車上にある場合: 
		//
		// - m_iDiaIndex = フォーカスセルの列車Index、m_iIndexSize = 1
		// - m_CentDedRessyaCont = フォーカスセルのある列車1個のコピー
		// - CaMuiSelect = 当該列車を選択。
		if ( getCSelect()->getSelectedCellCount() == 0 
			&& aCdXColSpecOfFocus.getColumnType() == CdXColSpec::ColumnType_Ressya )
		{
			bRv = true ;
			if ( ppCmd != NULL )
			{
				pCmd = OuNew<DedRosenFileData::EditCmd::CRfEditCmd_Ressya>( 
					new CRfEditCmd_Ressya( 
						*getCDiagramEditDoc()->getCDedRosenFileData() , 
						GetDocument()->getDiaIndex() , 
						GetDocument()->getRessyahoukou() ,
						aCdXColSpecOfFocus.getRessyaIndex() , 
						1 ) ) ;
				pCmd->getCaMuiSelect()->setSelectAll( true ) ;
				pCmd->setWaitOperationConnect(getOperationUpdateStop());
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
		
		//(A)の位置で処理します。
	}


	// ********************************
	//		ECreateCmd_All ,
	//　全列車を対象としたコマンドを生成します。
	// ********************************
	if ( eCreateCmd == ECreateCmd_All )
	{

		//  時刻表ビュー上で複数選択がOFF・フォーカスセルが列車上にある場合: 
		//
		// - m_iDiaIndex = 0、m_iIndexSize = 列車の数
		// - m_CentDedRessyaCont = 全列車のコピー
		// - m_CaMuiSelect2 は、全列車を選択。
		//  時刻表ビュー上で複数選択がOFF・フォーカスセルが新規列車位置にある場合: 
		// 
		// - m_iDiaIndex = 0、m_iIndexSize = 列車の数
		// - m_CentDedRessyaCont = 全列車のコピー
		// - CaMuiSelect2 は、全列車を選択。
		if ( getCSelect()->getSelectedCellCount() == 0 
			&& ( aCdXColSpecOfFocus.getColumnType() == CdXColSpec::ColumnType_Ressya 
			|| aCdXColSpecOfFocus.getColumnType() == CdXColSpec::ColumnType_NewRessya ) )
		{
			bRv = true ;
			if ( ppCmd != NULL )
			{
				pCmd = OuNew<DedRosenFileData::EditCmd::CRfEditCmd_Ressya>( 
					new CRfEditCmd_Ressya( 
						*getCDiagramEditDoc()->getCDedRosenFileData() , 
						GetDocument()->getDiaIndex() , 
						GetDocument()->getRessyahoukou() ,
						0 , 
						getCentDedRessyaCont()->size() ) ) ;
				pCmd->getCaMuiSelect()->setSelectAll( true ) ;
				pCmd->setWaitOperationConnect(getOperationUpdateStop());
			}
		}

		//時刻表ビュー上で複数選択ON
		//
		// - m_iDiaIndex = 選択されている列車の先頭index
		// - m_iIndexSize = 選択されている列車の末尾index-先頭index+1
		// - m_CentDedRessyaCont = 選択されている列車の先頭indexから
		//	末尾indexまでの列車のコピー
		// - m_CaMuiSelect2 は、セルの選択に合わせて列車を選択。

		//(A)の位置で処理します。
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
			//	選択されている列車の列車Indexを取得
			deque<int> contiRessyaIndex ;
			for ( int iColumnNumber = 0 ; iColumnNumber < getCXDcdGrid()->getXColumnCount() ;iColumnNumber ++ )
			{
				if ( getCSelect()->getXColumnNumberSelected( iColumnNumber ) )
				{
					CdXColSpec aCdXColSpec = aCdXColSpecCont.ColumnNumberToSpec( iColumnNumber ) ;
					if ( aCdXColSpec.getColumnType() == CdXColSpec::ColumnType_Ressya )
					{
						contiRessyaIndex.push_back( aCdXColSpec.getRessyaIndex() ) ;
					}
				}
			}
			//contiRessyaIndex = 列の複数選択が実施されている場合は、
			//	選択されている列車Indexが格納されます。
			//	そうでない場合は、空です。

			if ( contiRessyaIndex.size() > 1 )
			{
				bRv = true ;
				if ( ppCmd != NULL )
				{
					//	コマンドオブジェクト内に、選択されている列車の先頭から末尾までの
					//	列車を格納します(先頭・末尾以外には、選択されていない列車が
					//	含まれている場合もあります)
					pCmd = OuNew<DedRosenFileData::EditCmd::CRfEditCmd_Ressya>( 
						new CRfEditCmd_Ressya( 
							*getCDiagramEditDoc()->getCDedRosenFileData() ,
							GetDocument()->getDiaIndex() , 
							GetDocument()->getRessyahoukou() ,
							contiRessyaIndex.front() , 
							contiRessyaIndex.back() - contiRessyaIndex.front() + 1 ) ) ;

					//	コマンドオブジェクトの
					//	m_CentDedRessyaContSrc  内の列車を選択します。
					pCmd->getCaMuiSelect()->setSelectAll( false ) ;
					pCmd->setWaitOperationConnect(getOperationUpdateStop());
					for ( int i = 0 ; i < (int)contiRessyaIndex.size() ; i ++ )
					{
						pCmd->getCaMuiSelect()->setSelect( contiRessyaIndex[i] - contiRessyaIndex.front()  , true ) ;
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

bool CWndJikokuhyou::createCmd( int iRessyaIndex , int iRessyaCount , 
		Ou<DedRosenFileData::EditCmd::CRfEditCmd_Ressya>* ppCmd) 
{
	bool bRv = false ;
	Ou<DedRosenFileData::EditCmd::CRfEditCmd_Ressya> pCmd ;
	int iRv = 0 ;

	//  --------------------------------
	//	コマンドオブジェクトを生成
	//  --------------------------------
	if ( iRv >= 0 )
	{
		//	コマンドオブジェクト内に、指定された範囲の
		//	列車を格納します
		//	列車は全選択となります。
		bRv = true ;
		if ( ppCmd != NULL )
		{
			pCmd = OuNew<DedRosenFileData::EditCmd::CRfEditCmd_Ressya>( 
				new CRfEditCmd_Ressya( 
					*getCDiagramEditDoc()->getCDedRosenFileData() , 
					GetDocument()->getDiaIndex() , 
					GetDocument()->getRessyahoukou() ,
					iRessyaIndex , 
					iRessyaCount ) ) ;
		}
	}
	// ================================
	if ( ppCmd != NULL && pCmd != NULL )
	{
		*ppCmd = pCmd ;
	}
	return bRv ;
}

// ----------------------------------------------------------------
//	MFC
// ----------------------------------------------------------------

BEGIN_MESSAGE_MAP(CWndJikokuhyou,CWndJikokuhyou::super)
	//{{AFX_MSG_MAP(CWndJikokuhyou)
	ON_WM_CREATE()
	ON_WM_KEYUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_Jikokuhyou_RessyaProp, OnJikokuhyouRessyaProp)
	ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_RessyaProp, OnUpdateJikokuhyouRessyaProp)
	ON_COMMAND(ID_Jikokuhyou_RessyaInsert, OnJikokuhyouRessyaInsert)
	ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_RessyaInsert, OnUpdateJikokuhyouRessyaInsert)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR, OnUpdateEditClear)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_OPERATIONCOPY, OnEditOperationCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_OPERATIONCOPY, OnUpdateEditOperationCopy)
	ON_COMMAND(ID_EDIT_RESSYAJOUHOUCOPY, OnEditRessyaJouhouCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_RESSYAJOUHOUCOPY, OnUpdateEditRessyaJouhouCopy)
	ON_COMMAND(ID_Edit_PasteEkiJikoku, OnEditPasteEkiJikoku)
	ON_UPDATE_COMMAND_UI(ID_Edit_PasteEkiJikoku, OnUpdateEditPasteEkiJikoku)
	ON_COMMAND(ID_Jikokuhyou_Tsuuka, OnJikokuhyouTsuuka)
	ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_Tsuuka, OnUpdateJikokuhyouTsuuka)
	ON_COMMAND(ID_Jikokuhyou_Keiyunasi, OnJikokuhyouKeiyunasi)
	ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_Keiyunasi, OnUpdateJikokuhyouKeiyunasi)
	ON_COMMAND(ID_Jikokuhyou_Sihatsu, OnJikokuhyouSihatsu)
	ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_Sihatsu, OnUpdateJikokuhyouSihatsu)
	ON_COMMAND(ID_Jikokuhyou_Syuuchaku, OnJikokuhyouSyuuchaku)
	ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_Syuuchaku, OnUpdateJikokuhyouSyuuchaku)
	ON_COMMAND(ID_Jikokuhyou_Renzoku, OnJikokuhyouRenzoku)
	ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_Renzoku, OnUpdateJikokuhyouRenzoku)
	ON_COMMAND(ID_Jikokuhyou_ViewProp, OnJikokuhyouViewProp)
	ON_COMMAND(ID_Jikokuhyou_FocusMoveDown, OnJikokuhyouFocusMoveDown)
	ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_FocusMoveDown, OnUpdateJikokuhyouFocusMoveDown)
	ON_COMMAND(ID_Jikokuhyou_FocusMoveRight, OnJikokuhyouFocusMoveRight)
	ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_FocusMoveRight, OnUpdateJikokuhyouFocusMoveRight)
	ON_COMMAND(ID_Jikokuhyou_EkijikokuProp, OnJikokuhyouEkijikokuProp)
	ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_EkijikokuProp, OnUpdateJikokuhyouEkijikokuProp)
	ON_COMMAND(ID_Jikokuhyou_EkijikokuInsert, OnJikokuhyouEkijikokuInsert)
	ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_EkijikokuInsert, OnUpdateJikokuhyouEkijikokuInsert)
	ON_COMMAND(ID_Jikokuhyou_EkijikokuErase, OnJikokuhyouEkijikokuErase)
	ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_EkijikokuErase, OnUpdateJikokuhyouEkijikokuErase)
	ON_WM_CHAR()
	ON_COMMAND(ID_Jikokuhyou_ModifyEkijikokuCmd, OnJikokuhyouModifyEkijikokuCmd)
	ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_ModifyEkijikokuCmd, OnUpdateJikokuhyouModifyEkijikokuCmd)
	ON_COMMAND(ID_Jikokuhyou_ModifyEkijikokuCmdRepeat, OnJikokuhyouModifyEkijikokuCmdRepeat)
	ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_ModifyEkijikokuCmdRepeat, OnUpdateJikokuhyouModifyEkijikokuCmdRepeat)
	ON_COMMAND(ID_Jikokuhyou_JikokuSakujo, OnJikokuhyouJikokuSakujo)
	ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_JikokuSakujo, OnUpdateJikokuhyouJikokuSakujo)
	ON_COMMAND(ID_Jikokuhyou_EkijikokuDec, OnJikokuhyouEkijikokuDec)
	ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_EkijikokuDec, OnUpdateJikokuhyouEkijikokuDec)
	ON_COMMAND(ID_Jikokuhyou_EkijikokuNext, OnJikokuhyouEkijikokuNext)
	ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_EkijikokuNext, OnUpdateJikokuhyouEkijikokuNext)
	ON_COMMAND(ID_Jikokuhyou_EkijikokuInc, OnJikokuhyouEkijikokuInc)
	ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_EkijikokuInc, OnUpdateJikokuhyouEkijikokuInc)
	ON_COMMAND(ID_Jikokuhyou_EKikanSaisyouSec, OnJikokuhyouEKikanSaisyouSec)
	ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_EKikanSaisyouSec, OnUpdateJikokuhyouEKikanSaisyouSec)
	ON_COMMAND(ID_Jikokuhyou_DiagramHeIdou, OnJikokuhyouDiagramHeIdou)
	ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_DiagramHeIdou, OnUpdateJikokuhyouDiagramHeIdou)
	ON_COMMAND(ID_VIEW_DisplayTsuukaEkiJikoku, OnVIEWDisplayTsuukaEkiJikoku)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DisplayTsuukaEkiJikoku, OnUpdateVIEWDisplayTsuukaEkiJikoku)
	ON_COMMAND(ID_FILE_EXPORT_JIKOKUHYOUCSV, OnFileExportJikokuhyoucsv)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_PasteZoubun, OnUpdateINDICATOR_PasteZoubun)

	ON_COMMAND(ID_Jikokuhyou_EkijikokuDecNoMove, &CWndJikokuhyou::OnJikokuhyouEkijikokudecnomove)
	ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_EkijikokuDecNoMove, &CWndJikokuhyou::OnUpdateJikokuhyouEkijikokudecnomove)
	ON_COMMAND(ID_Jikokuhyou_EkijikokuIncNoMove, &CWndJikokuhyou::OnJikokuhyouEkijikokuincnomove)
	ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_EkijikokuIncNoMove, &CWndJikokuhyou::OnUpdateJikokuhyouEkijikokuincnomove)
	ON_COMMAND(ID_Jikokuhyou_EkijikokuPrev, &CWndJikokuhyou::OnJikokuhyouEkijikokuPrev)
	ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_EkijikokuPrev, &CWndJikokuhyou::OnUpdateJikokuhyouEkijikokuPrev)
	ON_COMMAND(ID_EDIT_SELECT_ALL, &CWndJikokuhyou::OnEditSelectAll)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SELECT_ALL, &CWndJikokuhyou::OnUpdateEditSelectAll)
	ON_COMMAND(ID_Jikokuhyou_SORT, &CWndJikokuhyou::OnJikokuhyouSort)
	ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_SORT, &CWndJikokuhyou::OnUpdateJikokuhyouSort)
	ON_COMMAND(ID_Jikokuhyou_TsuukaTeisya, &CWndJikokuhyou::OnJikokuhyouTsuukateisya)
	ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_TsuukaTeisya, &CWndJikokuhyou::OnUpdateJikokuhyouTsuukateisya)
	ON_COMMAND(ID_Jikokuhyou_Direct, &CWndJikokuhyou::OnJikokuhyouDirect)
	ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_Direct, &CWndJikokuhyou::OnUpdateJikokuhyouDirect)
	ON_COMMAND(ID_Jikokuhyou_Undirect, &CWndJikokuhyou::OnJikokuhyouUndirect)
	ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_Undirect, &CWndJikokuhyou::OnUpdateJikokuhyouUndirect)
	ON_COMMAND(ID_VIEW_DisplayAllEkiJikoku, &CWndJikokuhyou::OnViewDisplayallekijikoku)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DisplayAllEkiJikoku, &CWndJikokuhyou::OnUpdateViewDisplayallekijikoku)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_Jikokuhyou_Unify, &CWndJikokuhyou::OnJikokuhyouUnify)
	ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_Unify, &CWndJikokuhyou::OnUpdateJikokuhyouUnify)
//ここからchange_by_d_mania
	ON_COMMAND(ID_Jikokuhyou_EkijikokuDecAnySecNoMove, &CWndJikokuhyou::OnJikokuhyouEkijikokudecAnysecnomove)
	ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_EkijikokuDecAnySecNoMove, &CWndJikokuhyou::OnUpdateJikokuhyouEkijikokudecAnysecnomove)
	ON_COMMAND(ID_Jikokuhyou_EkijikokuIncAnySecNoMove, &CWndJikokuhyou::OnJikokuhyouEkijikokuincAnysecnomove)
	ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_EkijikokuIncAnySecNoMove, &CWndJikokuhyou::OnUpdateJikokuhyouEkijikokuincAnysecnomove)
	ON_COMMAND(ID_Jikokuhyou_EkijikokuDecAny2SecNoMove, &CWndJikokuhyou::OnJikokuhyouEkijikokudecAny2secnomove)
	ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_EkijikokuDecAny2SecNoMove, &CWndJikokuhyou::OnUpdateJikokuhyouEkijikokudecAny2secnomove)
	ON_COMMAND(ID_Jikokuhyou_EkijikokuIncAny2SecNoMove, &CWndJikokuhyou::OnJikokuhyouEkijikokuincAny2secnomove)
	ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_EkijikokuIncAny2SecNoMove, &CWndJikokuhyou::OnUpdateJikokuhyouEkijikokuincAny2secnomove)
	ON_COMMAND(ID_VIEW_DisplaySecondEkiJikoku, &CWndJikokuhyou::OnViewDisplaySecondEkijikoku)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DisplaySecondEkiJikoku, &CWndJikokuhyou::OnUpdateViewDisplaySecondEkijikoku)
	ON_COMMAND(ID_VIEW_StandardOperationTimeFunction, &CWndJikokuhyou::OnViewStandardOperationTimeFunction)
	ON_UPDATE_COMMAND_UI(ID_VIEW_StandardOperationTimeFunction, &CWndJikokuhyou::OnUpdateViewStandardOperationTimeFunction)
	ON_COMMAND(ID_Jikokuhyou_EkijikokuAdjustStdOpeTime, &CWndJikokuhyou::OnJikokuhyouEkijikokuAdjustStdOpeTime) // 17.4.19
	ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_EkijikokuAdjustStdOpeTime, &CWndJikokuhyou::OnUpdateJikokuhyouEkijikokuAdjustStdOpeTime) // 17.4.19
	//ON_COMMAND(ID_VIEW_DisplayCustomizeDisplayMode, &CWndJikokuhyou::OnViewCustomizeDisplayMode)
	//ON_UPDATE_COMMAND_UI(ID_VIEW_DisplayCustomizeDisplayMode, &CWndJikokuhyou::OnUpdateViewCustomizeDisplayMode)
	ON_COMMAND(ID_VIEW_DisplayShihatsuShuchakuEkimei, &CWndJikokuhyou::OnViewDisplayShihatsuShuchakuEkimei)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DisplayShihatsuShuchakuEkimei, &CWndJikokuhyou::OnUpdateViewDisplayShihatsuShuchakuEkimei)
	ON_COMMAND(ID_Jikokuhyou_MoveToOutRessya, &CWndJikokuhyou::OnJikokuhyouMoveToOutRessya)
	ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_MoveToOutRessya, &CWndJikokuhyou::OnUpdateJikokuhyouMoveToOutRessya)
		ON_COMMAND(ID_Jikokuhyou_MoveToPrevRessya, &CWndJikokuhyou::OnJikokuhyouMoveToPrevRessya)
		ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_MoveToPrevRessya, &CWndJikokuhyou::OnUpdateJikokuhyouMoveToPrevRessya)
		ON_COMMAND(ID_Jikokuhyou_MoveToNextRessya, &CWndJikokuhyou::OnJikokuhyouMoveToNextRessya)
		ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_MoveToNextRessya, &CWndJikokuhyou::OnUpdateJikokuhyouMoveToNextRessya)
		ON_COMMAND(ID_Jikokuhyou_MoveToInRessya, &CWndJikokuhyou::OnJikokuhyouMoveToInRessya)
		ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_MoveToInRessya, &CWndJikokuhyou::OnUpdateJikokuhyouMoveToInRessya)
		ON_COMMAND(IDC_BUTTON_RessyaBangouJump, &CWndJikokuhyou::OnJikokuhyouRessyabangouMove)
		ON_UPDATE_COMMAND_UI(IDC_BUTTON_RessyaBangouJump, &CWndJikokuhyou::OnUpdateJikokuhyouRessyabangouMove)
		ON_COMMAND(ID_Jikokuhyou_OpenOperationTable, &CWndJikokuhyou::OnJikokuhyouOpenOperationTable)
		ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_OpenOperationTable, &CWndJikokuhyou::OnUpdateJikokuhyouOpenOperationTable)
		ON_COMMAND(ID_Jikokuhyou_OpenEki, &CWndJikokuhyou::OnJikokuhyouOpenEki)
		ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_OpenEki, &CWndJikokuhyou::OnUpdateJikokuhyouOpenEki)
		ON_COMMAND(ID_Jikokuhyou_OpenEkiJikokuhyou, &CWndJikokuhyou::OnJikokuhyouOpenEkiJikokuhyou)
		ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_OpenEkiJikokuhyou, &CWndJikokuhyou::OnUpdateJikokuhyouOpenEkiJikokuhyou)
		ON_COMMAND(ID_Jikokuhyou_OpenCrossingCheck, &CWndJikokuhyou::OnJikokuhyouOpenCrossingCheck)
		ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_OpenCrossingCheck, &CWndJikokuhyou::OnUpdateJikokuhyouOpenCrossingCheck)
		ON_COMMAND(ID_VIEW_DisplayColonEkiJikoku, &CWndJikokuhyou::OnViewDisplayColonEkijikoku)
		ON_UPDATE_COMMAND_UI(ID_VIEW_DisplayColonEkiJikoku, &CWndJikokuhyou::OnUpdateViewDisplayColonEkijikoku)
		ON_COMMAND(ID_VIEW_OperationUpdateStop, &CWndJikokuhyou::OnViewOperationupdatestop)
		ON_UPDATE_COMMAND_UI(ID_VIEW_OperationUpdateStop, &CWndJikokuhyou::OnUpdateViewOperationupdatestop)
		ON_COMMAND(ID_VIEW_UPDATEOPERATION, &CWndJikokuhyou::OnViewUpdateOperation)
		ON_UPDATE_COMMAND_UI(ID_VIEW_UPDATEOPERATION, &CWndJikokuhyou::OnUpdateViewUpdateOperation)
		ON_COMMAND(ID_VIEW_DisplayParentSyubetsu, &CWndJikokuhyou::OnViewDisplayParentSyubetsu)
		ON_UPDATE_COMMAND_UI(ID_VIEW_DisplayParentSyubetsu, &CWndJikokuhyou::OnUpdateViewDisplayParentSyubetsu)
		ON_COMMAND(ID_Jikokuhyou_RessyaComplementStdOpeTime, &CWndJikokuhyou::OnJikokuhyouRessyaComplementStdOpeTime)
		ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_RessyaComplementStdOpeTime, &CWndJikokuhyou::OnUpdateJikokuhyouRessyaComplementStdOpeTime)
		ON_COMMAND(ID_Jikokuhyou_EkijikokuDecRev, OnJikokuhyouEkijikokuDecRev)
		ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_EkijikokuDecRev, OnUpdateJikokuhyouEkijikokuDecRev)
		ON_COMMAND(ID_Jikokuhyou_EkijikokuIncRev, OnJikokuhyouEkijikokuIncRev)
		ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_EkijikokuIncRev, OnUpdateJikokuhyouEkijikokuIncRev)
		ON_COMMAND(ID_Jikokuhyou_EkijikokuDecRevNoMove, &CWndJikokuhyou::OnJikokuhyouEkijikokudecRevnomove)
		ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_EkijikokuDecRevNoMove, &CWndJikokuhyou::OnUpdateJikokuhyouEkijikokudecRevnomove)
		ON_COMMAND(ID_Jikokuhyou_EkijikokuIncRevNoMove, &CWndJikokuhyou::OnJikokuhyouEkijikokuincRevnomove)
		ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_EkijikokuIncRevNoMove, &CWndJikokuhyou::OnUpdateJikokuhyouEkijikokuincRevnomove)
		ON_COMMAND(ID_Jikokuhyou_EkijikokuDecRevAnySecNoMove, &CWndJikokuhyou::OnJikokuhyouEkijikokudecRevAnysecnomove)
		ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_EkijikokuDecRevAnySecNoMove, &CWndJikokuhyou::OnUpdateJikokuhyouEkijikokudecRevAnysecnomove)
		ON_COMMAND(ID_Jikokuhyou_EkijikokuIncRevAnySecNoMove, &CWndJikokuhyou::OnJikokuhyouEkijikokuincRevAnysecnomove)
		ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_EkijikokuIncRevAnySecNoMove, &CWndJikokuhyou::OnUpdateJikokuhyouEkijikokuincRevAnysecnomove)
		ON_COMMAND(ID_Jikokuhyou_EkijikokuDecRevAny2SecNoMove, &CWndJikokuhyou::OnJikokuhyouEkijikokudecRevAny2secnomove)
		ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_EkijikokuDecRevAny2SecNoMove, &CWndJikokuhyou::OnUpdateJikokuhyouEkijikokudecRevAny2secnomove)
		ON_COMMAND(ID_Jikokuhyou_EkijikokuIncRevAny2SecNoMove, &CWndJikokuhyou::OnJikokuhyouEkijikokuincRevAny2secnomove)
		ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_EkijikokuIncRevAny2SecNoMove, &CWndJikokuhyou::OnUpdateJikokuhyouEkijikokuincRevAny2secnomove)
		ON_COMMAND(ID_Jikokuhyou_EkijikokuAdjustStdOpeTimeRev, &CWndJikokuhyou::OnJikokuhyouEkijikokuAdjustStdOpeTimeRev)
		ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_EkijikokuAdjustStdOpeTimeRev, &CWndJikokuhyou::OnUpdateJikokuhyouEkijikokuAdjustStdOpeTimeRev)
		ON_COMMAND(ID_Jikokuhyou_OperationProp, OnJikokuhyouOperationProp)
		ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_OperationProp, OnUpdateJikokuhyouOperationProp)
		ON_COMMAND(ID_VIEW_DisplayTsuukaFontPerSyubetsu, &CWndJikokuhyou::OnViewDisplayTsuukaFontPerSyubetsu)
		ON_UPDATE_COMMAND_UI(ID_VIEW_DisplayTsuukaFontPerSyubetsu, &CWndJikokuhyou::OnUpdateViewDisplayTsuukaFontPerSyubetsu)
		ON_COMMAND(ID_Jikokuhyou_Left, OnJikokuhyouLeft)
		ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_Left, OnUpdateJikokuhyouLeft)
		ON_COMMAND(ID_Jikokuhyou_Right, OnJikokuhyouRight)
		ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_Right, OnUpdateJikokuhyouRight)
		ON_COMMAND(ID_Jikokuhyou_Canceled, OnJikokuhyouCanceled)
		ON_UPDATE_COMMAND_UI(ID_Jikokuhyou_Canceled, OnUpdateJikokuhyouCanceled)
		END_MESSAGE_MAP()


	//ここまでchange_by_d_mania
	//}}AFX_MSG_MAP


int CWndJikokuhyou::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (super::OnCreate(lpCreateStruct) == -1)
		return -1;


	// --------------------------------
	//	状態の初期値を設定
	// --------------------------------
	m_StateMachine.add( OuNew< CWjkState >( new CWjkState_Ressyahensyu( this ) ) ) ;
	m_StateMachine.add( OuNew< CWjkState >( new CWjkState_Renzoku( this ) ) ) ;
	m_StateMachine.setCurrentStateIdx( StateIdx_Ressyahensyu ) ;


	// --------------------------------
	//	列の数を指定
	// --------------------------------
	//	駅名
	//	発着
	//	列車(1...*)
	getCXDcdGrid()->setXColumnCount( 3 ) ;
	getCXDcdGrid()->setXFixColumnCount( 2 ) ;

	const CdDedDispProp aCdDedDispProp =
		getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();

	int iEnableOperation = getCDiagramEditDoc()
		->getCDedRosenFileData()->getCentDedRosen()->getEnableOperation();
	bool bDisplayRessyamei = aCdDedDispProp.getDisplayRessyamei();
	bool bDisplayInOutLinkCode = aCdDedDispProp.getDisplayInOutLinkCode();
	//	列車番号
	//　運用番号
	//	種別
	//	列車名
	//	号数
	//	号
	//	駅時刻(0...*)
	//	備考
	int iYColumnCount = 3;
	if (iEnableOperation>1)
	{
		iYColumnCount += aCdDedDispProp.getOperationNumberRows();
	}
	if (bDisplayRessyamei)
	{
		iYColumnCount += 3;
	}
	if (m_bDisplayShihatsuShuchakuEkimei || !getCustomizeDisplayMode())
	{
		iYColumnCount += 2;
	}
	if (!getCustomizeDisplayMode())
	{
		iYColumnCount += 4;
		if (iEnableOperation > 1)
		{
			iYColumnCount += 1;
			if (bDisplayInOutLinkCode)
			{
				iYColumnCount += 2;
				//始発駅作業・終着駅作業(入出区連携コード)
			}
		}
	}
	getCXDcdGrid()->setYColumnCount(iYColumnCount) ;
	getCXDcdGrid()->setYFixColumnCount(iYColumnCount - 1);

	// --------------------------------
	//	フォーカスセルの初期位置を設定
	// --------------------------------
	getCFocus()->setFocusCell( getCXDcdGrid()->getCell( 1 , 1 ) ) ;	
	
	return 0;
}

void CWndJikokuhyou::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	m_StateMachine.getCurrentState()->
		OnKeyDown(nChar, nRepCnt, nFlags);
	//	super::OnKeyDown(nChar, nRepCnt, nFlags);
}
void CWndJikokuhyou::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	m_StateMachine.getCurrentState()->
		OnKeyUp(nChar, nRepCnt, nFlags);
	//super::OnKeyUp(nChar, nRepCnt, nFlags);
}



void CWndJikokuhyou::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	m_StateMachine.getCurrentState()->
		OnChar( nChar, nRepCnt, nFlags)  ;
	
	
}

void CWndJikokuhyou::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	m_StateMachine.getCurrentState()->
		OnLButtonDblClk(nFlags, point);
	//super::OnLButtonDblClk(nFlags, point);

}

//TODO:リファクタリング
//	GridからのOnContextMenu() は、実装が重複しています。
//	これは、CWndDcdGrid2(将来は、CWndDcdGrid3)に置くべきです。
void CWndJikokuhyou::OnContextMenu(CWnd* pWnd, CPoint point)
{
	int iMenuIndex = -1 ;
	//	フォーカスセルが列車にあるか、駅時刻にあるかを判定します
	//	これにより、表示するコンテキストメニューが変わります。
	{
		const Mu<const CentDedRessya*>* pCentDedRessyaCont = getCentDedRessyaCont()->getMuPtr() ;
		CdXColSpec aXColSpec = getXColSpecOfFocus() ;
		CdYColSpec aYColSpec = getYColSpecOfFocus() ;
		
		//	フォーカスセルが駅名部分・列車(新しい列車 を含む)にある場合は、
		//	コンテキストメニューを表示します。
		if (aXColSpec.getColumnType()
			== CdXColSpec::ColumnType_Ekimei ||
			aXColSpec.getColumnType()
			== CdXColSpec::ColumnType_Chakuhatsu)
		{
			if (aYColSpec.isEkiJikoku() ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_Track ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperation1 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperation2 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperation1 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperation2 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_EkiRessyabangou ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_EkiOperationNumber ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_EkiRessyasyubetsu ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_EkiRessyamei ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_EkiGousuu ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_EkiGou ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore1 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore2 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore3 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore4 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter1 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter2 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter3 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore1 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore2 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore3 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore4 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter1 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter2 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter3)

			{
				iMenuIndex = 3;
			}
			else
			{
				//	列車の、駅時刻以外の列車情報にセルがある場合は、
				//	列車用のメニュー
				iMenuIndex = 0;
			}
		}
		else if (aXColSpec.getColumnType() 
				== CdXColSpec::ColumnType_Ressya || 
			aXColSpec.getColumnType() 
				== CdXColSpec::ColumnType_NewRessya )
		{
			if ( aYColSpec.isEkiJikoku() ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_Track ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu1 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu2 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu3 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu4 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku1 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku2 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku3 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_Outer_Shihatsu1 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_Outer_Shihatsu2 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_Outer_Shuchaku1 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_Outer_Shuchaku2 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperation1 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperation2 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperation1 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperation2 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore1 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore2 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore3 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore4 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter1 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter2 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter3 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore1 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore2 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore3 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore4 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter1 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter2 ||
				aYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter3)
			{
				//	列車の駅時刻にセルがある場合は、駅時刻用のメニュー
				iMenuIndex = 1 ;
			}
			else if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_OperationNumber)
			{
				//運用番号にセルがある場合は、運用用のメニュー
				iMenuIndex = 2;
			}
			else
			{
				//	列車の、駅時刻以外の列車情報にセルがある場合は、
				//	列車用のメニュー
				iMenuIndex = 0 ;
			}
		}
	}
	//iMenuIndex = 
	//	0: 列車のコンテキストメニュー
	//	1: 列車・駅時刻のコンテキストメニュー
	//	2: 運用のコンテキストメニュー
	//	-1: 該当するコンテキストメニューがありません。

	{
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
	}
	//point = コンテキストメニューの表示位置。
	//	-1の場合は、コンテキストメニューは表示できません。

	if ( iMenuIndex >= 0 && point.x >= 0 &&  point.y >= 0 )
	{
		CMenu	aMenu ;
		aMenu.LoadMenu( IDR_MENU_JIKOKUHYOUVIEW_CONTEXT ) ;
		CMenu* pContextMenu = aMenu.GetSubMenu( iMenuIndex ) ;
	
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

void CWndJikokuhyou::OnEditCut() 
{
	m_StateMachine.getCurrentState()->
		OnEditCut_Process( FALSE )  ;

}

void CWndJikokuhyou::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_StateMachine.getCurrentState()->
		OnEditCut_Process( TRUE ) >= 0 );
}

void CWndJikokuhyou::OnEditCopy() 
{
	m_StateMachine.getCurrentState()->
		OnEditCopy_Process( FALSE ) ;
}

void CWndJikokuhyou::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_StateMachine.getCurrentState()->
		OnEditCopy_Process( TRUE ) >= 0 ) ;
}

void CWndJikokuhyou::OnEditPaste() 
{
	m_StateMachine.getCurrentState()->
		OnEditPaste_Process( FALSE ) ;
}

void CWndJikokuhyou::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_StateMachine.getCurrentState()->
		OnEditPaste_Process( TRUE ) >= 0 ) ;
}
void CWndJikokuhyou::OnEditClear() 
{
	m_StateMachine.getCurrentState()->
		OnEditClear_Process( FALSE ) ;

}

void CWndJikokuhyou::OnUpdateEditClear(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_StateMachine.getCurrentState()->
		OnEditClear_Process( TRUE ) >= 0 ) ;
}

void CWndJikokuhyou::OnEditPasteEkiJikoku() 
{
	m_StateMachine.getCurrentState()->
		OnEditPasteEkiJikoku_Process( FALSE ) ;

	
}

void CWndJikokuhyou::OnUpdateEditPasteEkiJikoku(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_StateMachine.getCurrentState()->
		OnEditPasteEkiJikoku_Process( TRUE ) >= 0 ) ;
	
}

void CWndJikokuhyou::OnEditOperationCopy()
{
	m_StateMachine.getCurrentState()->
		OnEditOperationCopy_Process(FALSE);
}

void CWndJikokuhyou::OnUpdateEditOperationCopy(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_StateMachine.getCurrentState()->
		OnEditOperationCopy_Process(TRUE) >= 0);
}

void CWndJikokuhyou::OnEditRessyaJouhouCopy()
{
	m_StateMachine.getCurrentState()->
		OnEditRessyaJouhouCopy_Process(FALSE);
}

void CWndJikokuhyou::OnUpdateEditRessyaJouhouCopy(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_StateMachine.getCurrentState()->
		OnEditRessyaJouhouCopy_Process(TRUE) >= 0);
}

void CWndJikokuhyou::OnEditSelectAll()
{
	m_StateMachine.getCurrentState()->
		OnEditSelectAll_Process( FALSE ) ;
}

void CWndJikokuhyou::OnUpdateEditSelectAll(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( m_StateMachine.getCurrentState()->
		OnEditSelectAll_Process( TRUE ) >= 0 ) ;
}

void CWndJikokuhyou::OnJikokuhyouRessyaProp() 
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouRessyaProp_Process( FALSE ) ;
	
}

void CWndJikokuhyou::OnUpdateJikokuhyouRessyaProp(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_StateMachine.getCurrentState()->
		OnJikokuhyouRessyaProp_Process( TRUE )  >= 0 ) ;
	
}

void CWndJikokuhyou::OnJikokuhyouRessyaInsert() 
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouRessyaInsert_Process( FALSE ) ;
}

void CWndJikokuhyou::OnUpdateJikokuhyouRessyaInsert(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_StateMachine.getCurrentState()->
		OnJikokuhyouRessyaInsert_Process( TRUE )  >= 0 ) ;
}

void CWndJikokuhyou::OnJikokuhyouTsuuka() 
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouTsuuka_Process(FALSE) ;
	
}

void CWndJikokuhyou::OnUpdateJikokuhyouTsuuka(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_StateMachine.getCurrentState()->
		OnJikokuhyouTsuuka_Process( TRUE )  >= 0 ) ;
}

void CWndJikokuhyou::OnJikokuhyouKeiyunasi() 
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouKeiyunasi_Process(FALSE) ;
	
}

void CWndJikokuhyou::OnUpdateJikokuhyouKeiyunasi(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_StateMachine.getCurrentState()->
		OnJikokuhyouKeiyunasi_Process( TRUE )  >= 0 ) ;
}

void CWndJikokuhyou::OnJikokuhyouSihatsu() 
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouSihatsu_Process(FALSE) ;
}

void CWndJikokuhyou::OnUpdateJikokuhyouSihatsu(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_StateMachine.getCurrentState()->
		OnJikokuhyouSihatsu_Process( TRUE )  >= 0 ) ;
}

void CWndJikokuhyou::OnJikokuhyouSyuuchaku() 
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouSyuuchaku_Process(FALSE) ;
	
}

void CWndJikokuhyou::OnUpdateJikokuhyouSyuuchaku(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_StateMachine.getCurrentState()->
		OnJikokuhyouSyuuchaku_Process( TRUE )  >= 0 ) ;
}

void CWndJikokuhyou::OnJikokuhyouRenzoku() 
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouRenzoku_Process( FALSE ) ;
	
}

void CWndJikokuhyou::OnUpdateJikokuhyouRenzoku(CCmdUI* pCmdUI) 
{
	int iResult = m_StateMachine.getCurrentState()->
		OnJikokuhyouRenzoku_Process( TRUE ) ;
	pCmdUI->Enable( iResult >= 0 ) ; 
	pCmdUI->SetCheck( iResult > 0 ) ; 
}

void CWndJikokuhyou::OnJikokuhyouViewProp() 
{
	OnJikokuhyouViewProp_Process( FALSE ) ;
}



void CWndJikokuhyou::OnUpdateINDICATOR_PasteZoubun(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(); 
	pCmdUI->SetText( OnUpdateINDICATOR_PasteZoubun_Process() ) ;
}



void CWndJikokuhyou::OnJikokuhyouFocusMoveDown() 
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouFocusMoveDown_Process( FALSE ) ;
}

void CWndJikokuhyou::OnUpdateJikokuhyouFocusMoveDown(CCmdUI* pCmdUI) 
{
	int iResult = m_StateMachine.getCurrentState()
		->OnJikokuhyouFocusMoveDown_Process( TRUE ) ;
	//iResult = 
	//	-	1 ;	//	(bQueryEnable=TRUEの場合)この項目はすでに選択されています
	//	-	0 ;	//	(bQueryEnable=TRUEの場合)この項目は選択されていません
	//	-  -1 ;	//	このコマンドは選択できません(メニューが無効)
	pCmdUI->Enable( iResult >= 0 );
	pCmdUI->SetCheck( iResult > 0 );
}

void CWndJikokuhyou::OnJikokuhyouFocusMoveRight() 
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouFocusMoveRight_Process( FALSE ) ;

}

void CWndJikokuhyou::OnUpdateJikokuhyouFocusMoveRight(CCmdUI* pCmdUI) 
{
	int iResult = m_StateMachine.getCurrentState()
		->OnJikokuhyouFocusMoveRight_Process( TRUE ) ;
	//iResult = 
	//	-	1 ;	//	(bQueryEnable=TRUEの場合)この項目はすでに選択されています
	//	-	0 ;	//	(bQueryEnable=TRUEの場合)この項目は選択されていません
	//	-  -1 ;	//	このコマンドは選択できません(メニューが無効)
	pCmdUI->Enable( iResult >= 0 );
	pCmdUI->SetCheck( iResult > 0 );
}

void CWndJikokuhyou::OnJikokuhyouEkijikokuProp() 
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuProp_Process( FALSE ) ;

}

void CWndJikokuhyou::OnUpdateJikokuhyouEkijikokuProp(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuProp_Process( TRUE ) >= 0 ) ;
}

void CWndJikokuhyou::OnJikokuhyouJikokuSakujo() 
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouJikokuSakujo_Process( FALSE ) ;
	
}

void CWndJikokuhyou::OnUpdateJikokuhyouJikokuSakujo(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_StateMachine.getCurrentState()->
		OnJikokuhyouJikokuSakujo_Process( TRUE ) >= 0 ) ;
}

void CWndJikokuhyou::OnJikokuhyouEkijikokuInsert() 
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuInsert_Process( FALSE ) ;
	
}

void CWndJikokuhyou::OnUpdateJikokuhyouEkijikokuInsert(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuInsert_Process( TRUE ) >= 0 ) ;
}

void CWndJikokuhyou::OnJikokuhyouEkijikokuErase() 
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuErase_Process( FALSE ) ;
}

void CWndJikokuhyou::OnUpdateJikokuhyouEkijikokuErase(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuErase_Process( TRUE ) >= 0 ) ;
}


void CWndJikokuhyou::OnJikokuhyouModifyEkijikokuCmd() 
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouModifyEkijikokuCmd_Process( FALSE ) ;
	
}

void CWndJikokuhyou::OnUpdateJikokuhyouModifyEkijikokuCmd(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_StateMachine.getCurrentState()->
		OnJikokuhyouModifyEkijikokuCmd_Process( TRUE ) >= 0 ) ;
	
}

void CWndJikokuhyou::OnJikokuhyouModifyEkijikokuCmdRepeat() 
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouModifyEkijikokuCmdRepeat_Process( FALSE ) ;
}

void CWndJikokuhyou::OnUpdateJikokuhyouModifyEkijikokuCmdRepeat(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_StateMachine.getCurrentState()->
		OnJikokuhyouModifyEkijikokuCmdRepeat_Process( TRUE ) >= 0 ) ;
}


void CWndJikokuhyou::OnJikokuhyouEkijikokuDec() 
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuDec_Process( FALSE ) ;
}

void CWndJikokuhyou::OnUpdateJikokuhyouEkijikokuDec(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuDec_Process( TRUE ) >= 0 ) ;
}

void CWndJikokuhyou::OnJikokuhyouEkijikokuNext() 
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuNext_Process( FALSE ) ;
}

void CWndJikokuhyou::OnUpdateJikokuhyouEkijikokuNext(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuNext_Process( TRUE ) >= 0 ) ;
}

void CWndJikokuhyou::OnJikokuhyouEkijikokuInc() 
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuInc_Process( FALSE ) ;
}

void CWndJikokuhyou::OnUpdateJikokuhyouEkijikokuInc(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuInc_Process( TRUE ) >= 0 ) ;
}

void CWndJikokuhyou::OnJikokuhyouEkijikokudecnomove()
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuDecNoMove_Process( FALSE ) ;
}

void CWndJikokuhyou::OnUpdateJikokuhyouEkijikokudecnomove(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuDecNoMove_Process( TRUE ) >= 0 ) ;
}

void CWndJikokuhyou::OnJikokuhyouEkijikokuincnomove()
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuIncNoMove_Process( FALSE ) ;
}

void CWndJikokuhyou::OnUpdateJikokuhyouEkijikokuincnomove(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuIncNoMove_Process( TRUE ) >= 0 ) ;
}

void CWndJikokuhyou::OnJikokuhyouEkijikokuPrev()
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuPrev_Process( FALSE ) ;
}

void CWndJikokuhyou::OnUpdateJikokuhyouEkijikokuPrev(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuPrev_Process( TRUE ) >= 0 ) ;
}


//add_by_d_mania
void CWndJikokuhyou::OnJikokuhyouEkijikokuincAnysecnomove()
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuIncAnySecNoMove_Process( FALSE ) ;
}

//add_by_d_mania
void CWndJikokuhyou::OnUpdateJikokuhyouEkijikokuincAnysecnomove(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuIncAnySecNoMove_Process( TRUE ) >= 0 ) ;
}

//add_by_d_mania
void CWndJikokuhyou::OnJikokuhyouEkijikokudecAnysecnomove()
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuDecAnySecNoMove_Process( FALSE ) ;
}

//add_by_d_mania
void CWndJikokuhyou::OnUpdateJikokuhyouEkijikokudecAnysecnomove(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuDecAnySecNoMove_Process( TRUE ) >= 0 ) ;
}

//add_by_d_mania
void CWndJikokuhyou::OnJikokuhyouEkijikokuincAny2secnomove()
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuIncAny2SecNoMove_Process( FALSE ) ;
}

//add_by_d_mania
void CWndJikokuhyou::OnUpdateJikokuhyouEkijikokuincAny2secnomove(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuIncAny2SecNoMove_Process( TRUE ) >= 0 ) ;
}

//add_by_d_mania
void CWndJikokuhyou::OnJikokuhyouEkijikokudecAny2secnomove()
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuDecAny2SecNoMove_Process( FALSE ) ;
}

//add_by_d_mania
void CWndJikokuhyou::OnUpdateJikokuhyouEkijikokudecAny2secnomove(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuDecAny2SecNoMove_Process( TRUE ) >= 0 ) ;
}

//add_by_d_mania 17.4.19
void CWndJikokuhyou::OnJikokuhyouEkijikokuAdjustStdOpeTime()
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuAdjustStdOpeTime_Process( FALSE ) ;
}

//add_by_d_mania 17.4.19
void CWndJikokuhyou::OnUpdateJikokuhyouEkijikokuAdjustStdOpeTime(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuAdjustStdOpeTime_Process( TRUE ) >= 0 ) ;
}

void CWndJikokuhyou::OnJikokuhyouEKikanSaisyouSec() 
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouEKikanSaisyouSec_Process( FALSE ) ;
}

void CWndJikokuhyou::OnUpdateJikokuhyouEKikanSaisyouSec(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_StateMachine.getCurrentState()->
		OnJikokuhyouEKikanSaisyouSec_Process( TRUE ) >= 0 );
}

void CWndJikokuhyou::OnJikokuhyouSort()
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouSort_Process( FALSE ) ;
}

void CWndJikokuhyou::OnUpdateJikokuhyouSort(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( m_StateMachine.getCurrentState()->
		OnJikokuhyouSort_Process( TRUE ) >= 0 );
}

void CWndJikokuhyou::OnJikokuhyouDiagramHeIdou() 
{
	OnJikokuhyouDiagramHeIdou_Process( FALSE ) ;
}
void CWndJikokuhyou::OnUpdateJikokuhyouDiagramHeIdou(CCmdUI* pCmdUI) 
{
	int iResult = OnJikokuhyouDiagramHeIdou_Process( TRUE ) ;
	pCmdUI->Enable( iResult >= 0 ? TRUE : FALSE ) ;
}

void CWndJikokuhyou::OnVIEWDisplayTsuukaEkiJikoku() 
{
	OnVIEWDisplayTsuukaEkiJikoku_Process( FALSE ) ;
}

void CWndJikokuhyou::OnUpdateVIEWDisplayTsuukaEkiJikoku(CCmdUI* pCmdUI) 
{
	int iResult = OnVIEWDisplayTsuukaEkiJikoku_Process( TRUE ) ;
	pCmdUI->Enable( iResult >= 0 ? TRUE : FALSE ) ;
	pCmdUI->SetCheck( iResult >= 1 ? TRUE : FALSE ) ;
	
}

void CWndJikokuhyou::OnFileExportJikokuhyoucsv() 
{
	OnFileExportJikokuhyoucsv_Process( FALSE ) ;
}

void CWndJikokuhyou::OnJikokuhyouTsuukateisya()
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouTsuukateisya_Process( FALSE ) ;
}

void CWndJikokuhyou::OnUpdateJikokuhyouTsuukateisya(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( m_StateMachine.getCurrentState()->
		OnJikokuhyouTsuukateisya_Process( TRUE ) >= 0 ) ;
}

void CWndJikokuhyou::OnJikokuhyouDirect()
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouDirect_Process( FALSE ) ;
}

void CWndJikokuhyou::OnUpdateJikokuhyouDirect(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( m_StateMachine.getCurrentState()->
		OnJikokuhyouDirect_Process( TRUE ) >= 0 ) ;
}

void CWndJikokuhyou::OnJikokuhyouUndirect()
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouUndirect_Process( FALSE ) ;
}

void CWndJikokuhyou::OnUpdateJikokuhyouUndirect(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( m_StateMachine.getCurrentState()->
		OnJikokuhyouUndirect_Process( TRUE ) >= 0 ) ;
}



void CWndJikokuhyou::OnViewDisplayallekijikoku()
{
	OnViewDisplayallekijikoku_Process( FALSE ) ;
}

void CWndJikokuhyou::OnUpdateViewDisplayallekijikoku(CCmdUI *pCmdUI)
{
	int iResult = OnViewDisplayallekijikoku_Process( TRUE ) ;
	pCmdUI->Enable( iResult >= 0 ) ;
	pCmdUI->SetCheck( iResult >= 1 ) ;
}

void CWndJikokuhyou::OnJikokuhyouUnify()
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouUnify_Process( FALSE ) ;
}

void CWndJikokuhyou::OnUpdateJikokuhyouUnify(CCmdUI *pCmdUI)
{
	int iResult = m_StateMachine.getCurrentState()->
		OnJikokuhyouUnify_Process( TRUE ) ;
	pCmdUI->Enable( iResult >= 0 ) ;
}

//add_by_d_mania
void CWndJikokuhyou::OnViewDisplaySecondEkijikoku()
{
	OnViewDisplaySecondEkijikoku_Process( FALSE ) ;
}

//add_by_d_mania
void CWndJikokuhyou::OnUpdateViewDisplaySecondEkijikoku(CCmdUI *pCmdUI)
{
	int iResult = OnViewDisplaySecondEkijikoku_Process( TRUE ) ;
	pCmdUI->Enable( iResult >= 0 ) ;
	pCmdUI->SetCheck( iResult >= 1 ) ;
}

//add_by_d_mania
void CWndJikokuhyou::OnViewStandardOperationTimeFunction()
{
	OnViewStandardOperationTimeFunction_Process( FALSE ) ;
}

//add_by_d_mania
void CWndJikokuhyou::OnUpdateViewStandardOperationTimeFunction(CCmdUI *pCmdUI)
{
	int iResult = OnViewStandardOperationTimeFunction_Process( TRUE ) ;
	pCmdUI->Enable( iResult >= 0 ) ;
	pCmdUI->SetCheck( iResult >= 1 ) ;
}

//void CWndJikokuhyou::OnViewCustomizeDisplayMode()
//{
//	OnViewCustomizeDisplayMode_Process(FALSE);
//}
//
//void CWndJikokuhyou::OnUpdateViewCustomizeDisplayMode(CCmdUI *pCmdUI)
//{
//	int iResult = OnViewCustomizeDisplayMode_Process(TRUE);
//	pCmdUI->Enable(iResult >= 0);
//	pCmdUI->SetCheck(iResult >= 1);
//}

void CWndJikokuhyou::OnViewDisplayShihatsuShuchakuEkimei()
{
	OnViewDisplayShihatsuShuchakuEkimei_Process(FALSE);
}

void CWndJikokuhyou::OnUpdateViewDisplayShihatsuShuchakuEkimei(CCmdUI *pCmdUI)
{
	int iResult = OnViewDisplayShihatsuShuchakuEkimei_Process(TRUE);
	pCmdUI->Enable(iResult >= 0);
	pCmdUI->SetCheck(iResult >= 1);
}

void CWndJikokuhyou::OnJikokuhyouMoveToOutRessya()
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouMoveToOutRessya_Process(FALSE);
}

void CWndJikokuhyou::OnUpdateJikokuhyouMoveToOutRessya(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_StateMachine.getCurrentState()->
		OnJikokuhyouMoveToOutRessya_Process(TRUE) >= 0);
}

void CWndJikokuhyou::OnJikokuhyouMoveToPrevRessya()
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouMoveToPrevRessya_Process(FALSE);
}

void CWndJikokuhyou::OnUpdateJikokuhyouMoveToPrevRessya(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_StateMachine.getCurrentState()->
		OnJikokuhyouMoveToPrevRessya_Process(TRUE) >= 0);
}

void CWndJikokuhyou::OnJikokuhyouMoveToNextRessya()
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouMoveToNextRessya_Process(FALSE);
}

void CWndJikokuhyou::OnUpdateJikokuhyouMoveToNextRessya(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_StateMachine.getCurrentState()->
		OnJikokuhyouMoveToNextRessya_Process(TRUE) >= 0);
}

void CWndJikokuhyou::OnJikokuhyouMoveToInRessya()
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouMoveToInRessya_Process(FALSE);
}

void CWndJikokuhyou::OnUpdateJikokuhyouMoveToInRessya(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_StateMachine.getCurrentState()->
		OnJikokuhyouMoveToInRessya_Process(TRUE) >= 0);
}

void CWndJikokuhyou::OnJikokuhyouRessyabangouMove()
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouRessyabangouMove_Process(FALSE);
}

void CWndJikokuhyou::OnUpdateJikokuhyouRessyabangouMove(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_StateMachine.getCurrentState()->
		OnJikokuhyouRessyabangouMove_Process(TRUE) >= 0);
}

void CWndJikokuhyou::OnJikokuhyouOpenOperationTable()
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouOpenOperationTable_Process(FALSE);
}

void CWndJikokuhyou::OnUpdateJikokuhyouOpenOperationTable(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_StateMachine.getCurrentState()->
		OnJikokuhyouOpenOperationTable_Process(TRUE) >= 0);
}

void CWndJikokuhyou::OnJikokuhyouOpenEki()
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouOpenEki_Process(FALSE);
}

void CWndJikokuhyou::OnUpdateJikokuhyouOpenEki(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_StateMachine.getCurrentState()->
		OnJikokuhyouOpenEki_Process(TRUE) >= 0);
}

void CWndJikokuhyou::OnJikokuhyouOpenEkiJikokuhyou()
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouOpenEkiJikokuhyou_Process(FALSE);
}

void CWndJikokuhyou::OnUpdateJikokuhyouOpenEkiJikokuhyou(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_StateMachine.getCurrentState()->
		OnJikokuhyouOpenEkiJikokuhyou_Process(TRUE) >= 0);
}

void CWndJikokuhyou::OnJikokuhyouOpenCrossingCheck()
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouOpenCrossingCheck_Process(FALSE);
}

void CWndJikokuhyou::OnUpdateJikokuhyouOpenCrossingCheck(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_StateMachine.getCurrentState()->
		OnJikokuhyouOpenCrossingCheck_Process(TRUE) >= 0);
}

void CWndJikokuhyou::OnViewDisplayColonEkijikoku()
{
	OnViewDisplayColonEkijikoku_Process(FALSE);
}

void CWndJikokuhyou::OnUpdateViewDisplayColonEkijikoku(CCmdUI *pCmdUI)
{
	int iResult = OnViewDisplayColonEkijikoku_Process(TRUE);
	pCmdUI->Enable(iResult >= 0);
	pCmdUI->SetCheck(iResult >= 1);
}



void ViewJikokuhyou::WndJikokuhyou::CWndJikokuhyou::OnViewOperationupdatestop()
{
	OnViewOperationupdatestop_Process(FALSE);
}


void ViewJikokuhyou::WndJikokuhyou::CWndJikokuhyou::OnUpdateViewOperationupdatestop(CCmdUI *pCmdUI)
{
	int iResult = OnViewOperationupdatestop_Process(TRUE);
	pCmdUI->Enable(iResult >= 0);
	pCmdUI->SetCheck(iResult >= 1);
}


void ViewJikokuhyou::WndJikokuhyou::CWndJikokuhyou::OnViewUpdateOperation()
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouUpdateOperation_Process(FALSE);
}


void ViewJikokuhyou::WndJikokuhyou::CWndJikokuhyou::OnUpdateViewUpdateOperation(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_StateMachine.getCurrentState()->
		OnJikokuhyouUpdateOperation_Process(TRUE) >= 0);
}

void CWndJikokuhyou::OnViewDisplayParentSyubetsu()
{
	OnViewDisplayParentSyubetsu_Process(FALSE);
}

void CWndJikokuhyou::OnUpdateViewDisplayParentSyubetsu(CCmdUI *pCmdUI)
{
	int iResult = OnViewDisplayParentSyubetsu_Process(TRUE);
	pCmdUI->Enable(iResult >= 0);
	pCmdUI->SetCheck(iResult >= 1);
}

void CWndJikokuhyou::OnJikokuhyouRessyaComplementStdOpeTime()
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouRessyaComplementStdOpeTime_Process(FALSE);
}

void CWndJikokuhyou::OnUpdateJikokuhyouRessyaComplementStdOpeTime(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_StateMachine.getCurrentState()->
		OnJikokuhyouRessyaComplementStdOpeTime_Process(TRUE) >= 0);
}


void CWndJikokuhyou::OnJikokuhyouEkijikokuDecRev()
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuDec_Process(FALSE,true);
}

void CWndJikokuhyou::OnUpdateJikokuhyouEkijikokuDecRev(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuDec_Process(TRUE, true) >= 0);
}

void CWndJikokuhyou::OnJikokuhyouEkijikokuIncRev()
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuInc_Process(FALSE, true);
}

void CWndJikokuhyou::OnUpdateJikokuhyouEkijikokuIncRev(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuInc_Process(TRUE, true) >= 0);
}

void CWndJikokuhyou::OnJikokuhyouEkijikokudecRevnomove()
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuDecNoMove_Process(FALSE, true);
}

void CWndJikokuhyou::OnUpdateJikokuhyouEkijikokudecRevnomove(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuDecNoMove_Process(TRUE, true) >= 0);
}

void CWndJikokuhyou::OnJikokuhyouEkijikokuincRevnomove()
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuIncNoMove_Process(FALSE, true);
}

void CWndJikokuhyou::OnUpdateJikokuhyouEkijikokuincRevnomove(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuIncNoMove_Process(TRUE, true) >= 0);
}

void CWndJikokuhyou::OnJikokuhyouEkijikokuincRevAnysecnomove()
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuIncAnySecNoMove_Process(FALSE, true);
}

void CWndJikokuhyou::OnUpdateJikokuhyouEkijikokuincRevAnysecnomove(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuIncAnySecNoMove_Process(TRUE, true) >= 0);
}

void CWndJikokuhyou::OnJikokuhyouEkijikokudecRevAnysecnomove()
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuDecAnySecNoMove_Process(FALSE, true);
}

void CWndJikokuhyou::OnUpdateJikokuhyouEkijikokudecRevAnysecnomove(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuDecAnySecNoMove_Process(TRUE, true) >= 0);
}

void CWndJikokuhyou::OnJikokuhyouEkijikokuincRevAny2secnomove()
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuIncAny2SecNoMove_Process(FALSE, true);
}

void CWndJikokuhyou::OnUpdateJikokuhyouEkijikokuincRevAny2secnomove(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuIncAny2SecNoMove_Process(TRUE, true) >= 0);
}

void CWndJikokuhyou::OnJikokuhyouEkijikokudecRevAny2secnomove()
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuDecAny2SecNoMove_Process(FALSE, true);
}

void CWndJikokuhyou::OnUpdateJikokuhyouEkijikokudecRevAny2secnomove(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuDecAny2SecNoMove_Process(TRUE, true) >= 0);
}

void CWndJikokuhyou::OnJikokuhyouEkijikokuAdjustStdOpeTimeRev()
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuAdjustStdOpeTime_Process(FALSE, true);
}

void CWndJikokuhyou::OnUpdateJikokuhyouEkijikokuAdjustStdOpeTimeRev(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_StateMachine.getCurrentState()->
		OnJikokuhyouEkijikokuAdjustStdOpeTime_Process(TRUE, true) >= 0);
}

void CWndJikokuhyou::OnJikokuhyouOperationProp()
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouOperationProp_Process(FALSE);

}

void CWndJikokuhyou::OnUpdateJikokuhyouOperationProp(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_StateMachine.getCurrentState()->
		OnJikokuhyouOperationProp_Process(TRUE) >= 0);
}

void CWndJikokuhyou::OnViewDisplayTsuukaFontPerSyubetsu()
{
	OnViewDisplayTsuukaFontPerSyubetsu_Process(FALSE);
}

void CWndJikokuhyou::OnUpdateViewDisplayTsuukaFontPerSyubetsu(CCmdUI* pCmdUI)
{
	int iResult = OnViewDisplayTsuukaFontPerSyubetsu_Process(TRUE);
	pCmdUI->Enable(iResult >= 0);
	pCmdUI->SetCheck(iResult >= 1);
}

void CWndJikokuhyou::OnJikokuhyouLeft()
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouLeft_Process(FALSE);

}

void CWndJikokuhyou::OnUpdateJikokuhyouLeft(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_StateMachine.getCurrentState()->
		OnJikokuhyouLeft_Process(TRUE) >= 0);
}

void CWndJikokuhyou::OnJikokuhyouRight()
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouRight_Process(FALSE);

}

void CWndJikokuhyou::OnUpdateJikokuhyouRight(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_StateMachine.getCurrentState()->
		OnJikokuhyouRight_Process(TRUE) >= 0);
}

void CWndJikokuhyou::OnJikokuhyouCanceled()
{
	m_StateMachine.getCurrentState()->
		OnJikokuhyouCanceled_Process(FALSE);

}

void CWndJikokuhyou::OnUpdateJikokuhyouCanceled(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_StateMachine.getCurrentState()->
		OnJikokuhyouCanceled_Process(TRUE) >= 0);
}

} } // namespace WndJikokuhyou namespace ViewJikokuhyou
