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
//	CWjkState_Ressyahensyu.cpp
// $Id: CWjkState_Ressyahensyu.cpp 357 2016-08-18 16:59:16Z okm $
// ****************************************************************
*/
/** @file */
#include "stdafx.h"



#include "logmsg/LogMsg.h"
#include "DcDraw/CDcdLine.h"
#include "NsOu/OuNew.h"
#include "NsOu/dynamic_castOu.h"
#include "NsMu\CaMui.h"

#include "CWjkState_Ressyahensyu.h"
#include "CWjkState_Renzoku.h"
#include "..\..\DiagramEdit.h"
#include "..\CDlgRessyaProp.h"
#include "..\CDlgEkiJikokuProp.h"
#include "..\CDlgOperationProp.h"
#include "..\CDlgModifyEkijikokuOperation2.h"
#include "..\..\CRfEditCmdHolder.h"
#include "..\..\DedRosenFileData\EditCmd\EditCmd.h"

#include "..\..\entDed\CDedRessyaSoater_Ressyasyubetsu.h"
#include "..\..\entDed\CDedRessyaSoater_Bikou.h"
#include "..\..\entDed\CDedRessyaSoater_Ekiatsukai.h"
#include "..\..\entDed\CDedRessyaSoater_OperationNumber.h"
#include "..\..\entDed\CDedRessyaSoater_RessyaTrack.h"
#include "..\..\entDed\CDedRessyaSoater_Ressyamei.h"
#include "..\..\entDed\CDedRessyaSoater_Ressyabangou.h"
#include "..\..\entDed\CRessyaContUnifier.h"
#include "..\..\entDgr\CDedRessyaSoater_Transfer.h"

#include "..\..\CDlgProgress.h"
#include "..\JikokuhyouColSpec\JikokuhyouColSpec.h"
#include "..\..\ViewOperationTable\COperationTableView.h"
#include "..\..\ViewEkiJikokuhyou\CEkiJikokuhyouView.h"
#include "..\..\ViewCrossingCheck\CCrossingCheckView.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



namespace ViewJikokuhyou{ namespace WndJikokuhyou{

// ****************************************************************
//	CWjkState_Ressyahensyu
// ****************************************************************
// --------------------------------
//@name OnUpdate下請関数
// --------------------------------
void CWjkState_Ressyahensyu::OnUpdate_All() 
{
	LogMsg(_T("CWjkState_Ressyahensyu::OnUpdate_All()") ) ;
 
	getCWndDcdGrid()->updateUIAll() ;

	LogMsg(_T("CWjkState_Ressyahensyu::OnUpdate_All()=") ) ;
}


void CWjkState_Ressyahensyu::OnUpdate_CentDedRessya( 
		Ou<CRfEditCmd_Ressya> pCommand ) 
{
	int iDiaIndex = GetDocument()->getDiaIndex() ;
	if (  pCommand->getDiaIndex() != iDiaIndex  )
		//if (!(pCommand->getDiaIndex() == iDiaIndex &&
		//	pCommand->getRessyahoukou() == GetDocument()->getRessyahoukou()))
	{
		return ;
	}

	//const CentDedDia* pCentDedDia = getCDiagramEditDoc()->getCDedRosenFileData()
	//	->getCentDedRosen()->getCentDedDiaCont()->getMuPtr()->get(iDiaIndex);
	//int iBackColorPattern = pCentDedDia->getBackPatternIndex();
	//if (iBackColorPattern == 2 ||
	//	iBackColorPattern == 4)
	//{
	//	//縦縞・市松模様の場合、編集箇所より後方の模様がずれるので全列車更新。
		//セル位置の問題や、表示速度の観点から、やはり今まで通りにしておく。
	//	getCWndDcdGrid()->updateUISetAllRessya();
	//	//OnUpdate_All();
	//}
	//else
	//{
	if (getCDiagramEditDoc()->getCDedRosenFileData()
		->getCentDedRosen()->getEnableOperation() > 1 &&
		!pCommand->getWaitOperationConnect())
	{
		if (pCommand->getRessyahoukou() == GetDocument()->getRessyahoukou())
		{
			//	列車のセルを置き換え
			getCWndDcdGrid()->updateUI_ReplaceRessyaAndAllOperationNumber(
				pCommand->getIndexDst(),
				pCommand->getSizeDst(),
				pCommand->getCentDedRessyaContSrc()->size());
		}
		else
		{
			getCWndDcdGrid()->updateUI_AllOperationNumber();
		}
	}
	else
	{
		if (pCommand->getRessyahoukou() == GetDocument()->getRessyahoukou())
		{
			//	列車のセルを置き換え
			getCWndDcdGrid()->updateUI_ReplaceRessya(
				pCommand->getIndexDst(),
				pCommand->getSizeDst(),
				pCommand->getCentDedRessyaContSrc()->size());
		}
	}

	//}

}

void CWjkState_Ressyahensyu::OnUpdate_Operation(Ou<CRfEditCmd_Operation> pCommand)
{
	int iDiaIndex = GetDocument()->getDiaIndex();
	if (pCommand->getDiaIndex() != iDiaIndex)
	{
		return;
	}
	//	列車のセルを置き換え
	getCWndDcdGrid()->updateUI_AllOperationNumber();
}



int CWjkState_Ressyahensyu::
		execJikokuhyouPropDlg( bool bInsert , BOOL bQueryEnable  ) 
{
	int iRv = 0 ;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	
	//iType = { 0: 駅時刻の編集,1: 列車の編集,2:駅の編集 ,3:運用表へ移動} 
	int iType = -1 ;
	if ( iRv >= 0 && iType == -1 )
	{
		//	駅プロパティダイアログの使用を判定
		int iResult = execCDlgEkiProp( TRUE ) ;
		if ( iResult >= 0 )
		{
			iType = 2;	//	駅の編集
		}
	}
	if ( iRv >= 0 && iType == -1 )
	{
		int iResult = execCDlgEkijikokuProp( bInsert , TRUE ) ;
		if ( iResult >= 0 )
		{	
			iType = 0 ;	// 駅時刻の編集
		}
	}
	if (iRv >= 0 && iType == -1)
	{
		int iResult = execCDlgOperationProp(bInsert, TRUE);
		if (iResult >= 0)
		{
			iType = 4;	// 作業の編集
		}
	}
	if ( iRv >= 0 && iType == -1 )
	{
		int iResult = execCDlgRessyaProp( bInsert , TRUE ) ;
		//iResult = 
 		//	-	1 ;	//	列車の追加・またはプロパティの変更を行いました。
 		//	-	0 ;	//	ダイアログがキャンセルで終了したため、
 		//		//	変更は発生しませんでした。
 		//	-	-1 ;	//	X列番号が不正です。
 		//	-	-2 ;	//	Y列番号が不正です。
		if ( iResult >= 0 )
		{	
			iType = 1 ;	// 列車の編集
		}
		//else
		//{
		//	iRv = iResult ;
		//}
	}
	if (iRv >= 0 && iType == -1)
	{
		//	運用表移動の使用を判定
		int iResult = OnJikokuhyouOpenOperationTable_Process(TRUE);
		if (iResult >= 0)
		{
			iType = 3;	//	駅の編集
		}
	}
	//iType = { 0: 駅時刻の編集,1: 列車の編集,2;駅の編集 } 
	// ****************************************************************
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		if (iType == 4)
		{
			iRv = execCDlgOperationProp(bInsert, FALSE);
		}
		if ( iType == 2 ) //	2;駅の編集
		{
			iRv = execCDlgEkiProp( FALSE ) ;
		}
		if ( iType == 1 ) //	1: 列車の編集
		{
			// --------------------------------
			//	『列車プロパティ』ダイアログを開く
			// --------------------------------
			iRv = execCDlgRessyaProp( bInsert , FALSE ) ;
			//iRv = 
	 		//	-	1 ;	//	列車の追加・またはプロパティの変更を行いました。
	 		//	-	0 ;	//	ダイアログがキャンセルで終了したため、@n
	 		//			変更は発生しませんでした。
	 		//	-	-1 ;	//	X列番号が不正です。
		}
		if ( iType == 0 )	//0: 駅時刻の編集,, } 
		{
			// --------------------------------
			//	『駅時刻のプロパティ』ダイアログを開く
			// --------------------------------
			iRv = execCDlgEkijikokuProp( bInsert , FALSE ) ;
			//iRv = 
	 		//	-	1 ;	//	列車の追加・またはプロパティの変更を行いました。
	 		//	-	0 ;	//	ダイアログがキャンセルで終了したため、
	 		//		//	変更は発生しませんでした。
	 		//	-	-1 ;	//	X列番号が不正です。
	 		//	-	-2 ;	//	Y列番号が不正です。
		}
		if (iType == 3)
		{
			iRv= OnJikokuhyouOpenOperationTable_Process(FALSE);
			//iRv =
			//-1 フォーカスが列車以外にあります
			//-2 NULL状態の列車です。
			//-3 運用番号がありません。
			//-4 運用表ビューのオープンに失敗しました
			//-5 運用更新抑止状態です
			//-6 フォーカスが運用番号欄以外にあります
		}
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return ( iRv ) ;
}

int CWjkState_Ressyahensyu::
execAltJikokuhyouPropDlg(bool bInsert, BOOL bQueryEnable)
{
	int iRv = 0;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************

	//iType = { 0: 駅時刻の編集,1: 列車の編集,2:駅の編集 ,3:運用表へ移動} 
	int iType = -1;

	if (iRv >= 0 && iType == -1)
	{
		//	駅プロパティダイアログの使用を判定
		int iResult = execCDlgEkiProp(TRUE);
		if (iResult >= 0)
		{
			iType = 2;	//	駅の編集
		}
	}
	if (iRv >= 0 && iType == -1)
	{
		int iResult = execCDlgOperationProp(bInsert, TRUE);
		if (iResult >= 0)
		{
			iType = 4;	// 駅作業の編集
		}
	}
	if (iRv >= 0 && iType == -1)
	{
		int iResult = execCDlgEkijikokuProp(bInsert, TRUE);
		if (iResult >= 0)
		{
			iType = 0;	// 駅時刻の編集
		}
	}
	if (iRv >= 0 && iType == -1)
	{
		//	運用表移動の使用を判定
		int iResult = OnJikokuhyouOpenOperationTable_Process(TRUE);
		if (iResult >= 0)
		{
			iType = 3;	//	駅の編集
		}
	}
	if (iRv >= 0 && iType == -1)
	{
		int iResult = execCDlgRessyaProp(bInsert, TRUE);
		//iResult = 
		//	-	1 ;	//	列車の追加・またはプロパティの変更を行いました。
		//	-	0 ;	//	ダイアログがキャンセルで終了したため、
		//		//	変更は発生しませんでした。
		//	-	-1 ;	//	X列番号が不正です。
		//	-	-2 ;	//	Y列番号が不正です。
		if (iResult >= 0)
		{
			iType = 1;	// 列車の編集
		}
		else
		{
			iRv = iResult;
		}
	}
	//iType = { 0: 駅時刻の編集,1: 列車の編集,2;駅の編集 } 
	// ****************************************************************
	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		if (iType == 4)
		{
			iRv = execCDlgOperationProp(bInsert, FALSE);
		}
		if (iType == 2) //	2;駅の編集
		{
			iRv = execCDlgEkiProp(FALSE);
		}
		if (iType == 1) //	1: 列車の編集
		{
			// --------------------------------
			//	『列車プロパティ』ダイアログを開く
			// --------------------------------
			iRv = execCDlgRessyaProp(bInsert, FALSE);
			//iRv = 
			//	-	1 ;	//	列車の追加・またはプロパティの変更を行いました。
			//	-	0 ;	//	ダイアログがキャンセルで終了したため、@n
			//			変更は発生しませんでした。
			//	-	-1 ;	//	X列番号が不正です。
		}
		if (iType == 0)	//0: 駅時刻の編集,, } 
		{
			// --------------------------------
			//	『駅時刻のプロパティ』ダイアログを開く
			// --------------------------------
			iRv = execCDlgEkijikokuProp(bInsert, FALSE);
			//iRv = 
			//	-	1 ;	//	列車の追加・またはプロパティの変更を行いました。
			//	-	0 ;	//	ダイアログがキャンセルで終了したため、
			//		//	変更は発生しませんでした。
			//	-	-1 ;	//	X列番号が不正です。
			//	-	-2 ;	//	Y列番号が不正です。
		}
		if (iType == 3)
		{
			iRv = OnJikokuhyouOpenOperationTable_Process(FALSE);
			//iRv =
			//-1 フォーカスが列車以外にあります
			//-2 NULL状態の列車です。
			//-3 運用番号がありません。
			//-4 運用表ビューのオープンに失敗しました
			//-5 運用更新抑止状態です
			//-6 フォーカスが運用番号欄以外にあります
		}
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return (iRv);
}



int CWjkState_Ressyahensyu::
	execCDlgRessyaProp( bool bInsert , BOOL bQueryEnable) 
{
	int iRv = 0 ;
	
	Ou<EditCmd::CRfEditCmd_Ressya> pCmd ;
	Ou<EditCmd::CRfEditCmd_Ressya>* ppCmd = NULL ;
	if ( !bQueryEnable )
	{
		ppCmd = &pCmd ;
	}

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -2;
		}
	}
	if ( iRv >= 0 )
	{
		if ( bInsert )
		{
			if ( !getCWndDcdGrid()->createCmd( CWndJikokuhyou::ECreateCmd_NewItem , ppCmd ) )
			{
				iRv = -1 ;	//	列車選択位置が正しくありません。
			}
		}
		else
		{
			if ( !getCWndDcdGrid()->createCmd( CWndJikokuhyou::ECreateCmd_Select , ppCmd ) )
			{
				iRv = -1 ;	//	列車選択位置が正しくありません。
			}
		}
	}
	if (iRv >= 0)
	{
		CdYColSpec	aYColSpec =
			getCWndDcdGrid()->getYColSpecOfFocus();
		if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_OperationNumber)
		{
			iRv = -3;
		}
	}
	// ****************************************************************
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		// --------------------------------
		//	『列車プロパティ』ダイアログを開く
		// --------------------------------
		CdYColSpecCont	aYColSpecCont
			= getCWndDcdGrid()->createYColSpecCont() ;

		int iFocus = 1;// = getCWndDcdGrid()->getCFocus()
		//	->getFocusCellColumnNumber().getY() + 1 ;
		CdYColSpec	aYColSpec = 
			getCWndDcdGrid()->getYColSpecOfFocus() ;
		if (aYColSpec.getColumnType()
			== CdYColSpec::ColumnType_Ressyabangou)
		{
			iFocus = 1;	//	列車番号
		}
		else if (aYColSpec.getColumnType()
			== CdYColSpec::ColumnType_Ressyasyubetsu)
		{
			iFocus = 2;	//	列車種別
		}
		else if (aYColSpec.getColumnType()
			== CdYColSpec::ColumnType_Ressyamei)
		{
			iFocus = 3;	//	列車名
		}
		else if (aYColSpec.getColumnType()
			== CdYColSpec::ColumnType_Gousuu ||
			aYColSpec.getColumnType()
			== CdYColSpec::ColumnType_Gou )
		{
			iFocus = 4	;	//	号数
		}
		else if ( aYColSpec.getColumnType() 
			== CdYColSpec::ColumnType_Bikou )
		{
			iFocus = 5	;	//	備考
		}

		CDlgRessyaProp	aDlg( 
			bInsert , 
			pCmd->getCaMuiSelect()->getMuPtr() , 
			iFocus , 
			&m_CKeyinputSenderToModalDlg , 
			getCWndDcdGrid() );
		if ( aDlg.DoModal() == IDOK )
		{
			iRv = 1 ;
		}
		//iRv = 
		//	1 ;	//	列車の追加・またはプロパティの変更を行いました。
		//	0 ;	//	ダイアログがキャンセルで終了したため、
		//		//	変更は発生しませんでした。
		//pCentDedRessyaSelectedCont = 
		//	ダイアログがOKで終了した場合は、
		//	pCentDedRessyaSelectedCont->m_pRessyaContAdaptee の
		//	内容が変更されています。


		// --------------------------------
		//	ダイアログOK時の処理
		// --------------------------------
		if ( iRv == 1 )
		{
			// --------------------------------
			//	編集コマンドを実行
			// --------------------------------
			getCDiagramEditDoc()->executeEditCmd( pCmd ) ;

			// --------------------------------
			//	フォーカスセルを、新設列車の始発駅に
			//	移します。
			// --------------------------------
			if ( bInsert )
			{
				//	フォーカスセルを、新設列車のX列に移動
				CDcdGridCell*	pCell = getCWndDcdGrid()->
					getCXDcdGrid()->calcMovedCell( 
						getCWndDcdGrid()->getCFocus()->getFocusCell() , 
						-1 , 
						0 ) ;
				if ( pCell )
				{
					getCWndDcdGrid()->getCFocus()->setFocusCell( pCell ) ;
				}
			}

			// --------------------------------
			//	フォーカスセルのY列番号が
			//	列車番号・列車種別・列車名・号数・備考の
			//	いずれかにある場合だけ、次の位置にフォーカスを
			//	移動します。
			// --------------------------------
			{
				CdYColSpecCont	aYColSpecCont
					= getCWndDcdGrid()->createYColSpecCont() ;

				int iYColumnNumber = getCWndDcdGrid()->getCFocus()
					->getFocusCellColumnNumber().getY() ;
				if ( !( aYColSpecCont.getColumnNumber_Ekijikoku_begin() 
						<= iYColumnNumber && 
						iYColumnNumber 
						 < aYColSpecCont.getColumnNumber_Ekijikoku_end()
				) )
				{
					moveFocusCellToNext( true ) ;
				}
			}
		}
		
	}
	return iRv ;
}

int  CWjkState_Ressyahensyu::
	execCDlgEkiProp( BOOL bQueryEnable ) 
{
	int iRv = 0 ;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	//if (iRv >= 0)
	//{
	//	if (getCWndDcdGrid()->getCustomizeDisplayMode())
	//	{
	//		iRv = -2;
	//	}
	//}
	int iEkiIndex = -1 ;
	if (iRv >= 0) {
		CdXColSpec	aXColSpecFocus = 
			getCWndDcdGrid()->getXColSpecOfFocus() ;
		CdYColSpec	aYColSpecFocus = 
			getCWndDcdGrid()->getYColSpecOfFocus() ;
		if (  
			( aXColSpecFocus.getColumnType() == 
				CdXColSpec::ColumnType_Ekimei ||
			  aXColSpecFocus.getColumnType() == 
				CdXColSpec::ColumnType_Chakuhatsu ) && 
			aYColSpecFocus.getEkiOrder() >= 0 
		)
		{
			const CentDedEkiCont* pCentDedEkiCont = 
				getCDiagramEditDoc()->getCDedRosenFileData()
				->getCentDedRosen()->getCentDedEkiCont() ;
			iEkiIndex = pCentDedEkiCont->EkiOrderOfEkiIndex( 
				getCWndDcdGrid()->getRessyahoukou() ,
				aYColSpecFocus.getEkiOrder() ) ;
		}
		else
		{
			iRv = -1 ;	//	セルの位置が駅名ではありません。
		}
	}
	//iEkiIndex = 駅Index
	// ****************************************************************
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		CEkiView* pCEkiView = NULL ;
		getCDiagramEditApp()->openCEkiDoc( &pCEkiView ) ;
		if ( pCEkiView != NULL )
		{
			pCEkiView->openCDlgEkiProp( iEkiIndex ) ;
		}
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return ( iRv ) ;
}



int CWjkState_Ressyahensyu::
execCDlgEkijikokuProp(bool bInsert, BOOL bQueryEnable)
{
	int iRv = 0;

	Ou<EditCmd::CRfEditCmd_Ressya> pCmd;
	Ou<EditCmd::CRfEditCmd_Ressya>* ppCmd = NULL;
	if (!bQueryEnable)
	{
		ppCmd = &pCmd;
	}
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -9;
		}
	}
	CdDedJikokuOrder	aCdJikokuOrder;
	if (iRv >= 0)
	{
		if (bInsert)
		{
			if (!getCWndDcdGrid()->createCmd(CWndJikokuhyou::ECreateCmd_NewItem, ppCmd))
			{
				iRv = -1;	//	列車選択位置が正しくありません。
			}
		}
		else
		{
			if (!getCWndDcdGrid()->createCmd(CWndJikokuhyou::ECreateCmd_Select, ppCmd))
			{
				iRv = -1;	//	列車選択位置が正しくありません。
			}
		}
	}
	int iEkiOrder;
	int iFocusItem;
	//-0;	//	駅扱
	//-1;	//	着時刻
	//-2;	//	発時刻
	CdYColSpec	aYColSpec =
		getCWndDcdGrid()->getYColSpecOfFocus();
	if (iRv >= 0)
	{
		if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_Track)
		{
			iEkiOrder = getCWndDcdGrid()->getYColSpecOfFocus().getEkiOrder();
			iFocusItem = 3;
		}
		else if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_ShihatsuEkimei)
		{
			if (getCWndDcdGrid()->getXColSpecOfFocus().getColumnType() == CdXColSpec::ColumnType_NewRessya)
			{
				iRv = -5;
			}
			else if (getCWndDcdGrid()->getCSelect()->getSelectedCellCount() == 0)
			{
				const CentDedRessyaCont* pCentDedRessyaCont = NULL;
				const CentDedRessya* pCentDedRessya = NULL;
				pCentDedRessyaCont = getCentDedRessyaCont();
				CdXColSpec aCdXColSpec = getCWndDcdGrid()->getXColSpecOfFocus();
				pCentDedRessya = pCentDedRessyaCont->getMuPtr()->get(aCdXColSpec.getRessyaIndex());
				if (pCentDedRessya->isNull())
				{
					iRv = -7;
				}
				else
				{
					iEkiOrder = pCentDedRessya->getValidSihatsuEki();
					if (iEkiOrder >= 0)
					{
						iFocusItem = 0;
					}
					else
					{
						iRv = -10;
					}
				}
			}
			else
			{
				iRv = -3;
			}
		}
		else if (aYColSpec == CdYColSpec::ColumnType_ShuchakuEkimei)
		{
			if (getCWndDcdGrid()->getXColSpecOfFocus().getColumnType() == CdXColSpec::ColumnType_NewRessya)
			{
				iRv = -6;
			}
			else if (getCWndDcdGrid()->getCSelect()->getSelectedCellCount() == 0)
			{
				const CentDedRessyaCont* pCentDedRessyaCont = NULL;
				const CentDedRessya* pCentDedRessya = NULL;
				pCentDedRessyaCont = getCentDedRessyaCont();
				CdXColSpec aCdXColSpec = getCWndDcdGrid()->getXColSpecOfFocus();
				pCentDedRessya = pCentDedRessyaCont->getMuPtr()->get(aCdXColSpec.getRessyaIndex());
				if (pCentDedRessya->isNull())
				{
					iRv = -8;
				}
				else
				{
					iEkiOrder = pCentDedRessya->getValidSyuuchakuEki();
					if (iEkiOrder >= 0)
					{
						iFocusItem = 0;
					}
					else
					{
						iRv = -11;
					}
				}
			}
			else
			{
				iRv = -3;
			}
		}
		else
		{
			aCdJikokuOrder = getCWndDcdGrid()->CdDedJikokuOrderOf(
				getCWndDcdGrid()->getYColSpecOfFocus());
			if (aCdJikokuOrder.getIsNull())
			{
				iRv = -2;	//	Y列番号が不正です。
			}
			else
			{
				iEkiOrder = aCdJikokuOrder.getEkiOrder();
				iFocusItem = aCdJikokuOrder.getEkiJikokuItem()
					== CdDedJikokuOrder::EkiJikokuItem_Hatsu ? 2 : 1;
			}
		}
	}
	//aCdJikokuOrder = 編集対象の時刻Orderです

	// ****************************************************************
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		// --------------------------------
		//	『駅時刻のプロパティ』ダイアログを開く
		// --------------------------------
		bool bJikokuModify = getCWndDcdGrid()->getModifyEkijikoku() ;
		const CentDedEkiCont* pCentDedEkiCont = getCDiagramEditDoc()->getCDedRosenFileData()
			->getCentDedRosen()->getCentDedEkiCont();
		int iEkiIndex = pCentDedEkiCont->EkiIndexOfEkiOrder
			(getCWndDcdGrid()->getRessyahoukou(), iEkiOrder);
		int iMainTrack = pCentDedEkiCont->getMuPtr()->get(iEkiIndex)->getMainTrack(getCWndDcdGrid()->getRessyahoukou());

		//編集前駅扱いを取得
		deque<int> iEkiAtsukaiPrev;
		if (bInsert)
		{
			iEkiAtsukaiPrev.push_back(0);
		}
		else 
		{
			for (int idx = 0; idx < pCmd->getCaMuiSelect()->size(); idx++)
			{
				CentDedEkiJikoku aCentDedEkiJikoku = 
					pCmd->getCaMuiSelect()->getMuPtr()->get(idx)->getCentDedEkiJikoku(iEkiOrder);
				if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya ||
					aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka)
				{
					iEkiAtsukaiPrev.push_back(1);
				}
				else if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_None)
				{
					iEkiAtsukaiPrev.push_back(0);
				}
			}
		}
		int iStandardRessyaTrackIndex[2] = { 0,0 }; 
		if (getCWndDcdGrid()->getCSelect()->getSelectedCellCount() == 0)
		{
			int iRessyasyubetsuIndex = pCmd->getCaMuiSelect()->getMuPtr()->get(0)->getRessyasyubetsuIndex();
			getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
				->StandardRessyaTrackIndexSearch(
					iRessyasyubetsuIndex,
					getRessyahoukou(),
					iEkiOrder,
					iStandardRessyaTrackIndex);
		}
		//int iOuterTerminalCount = pCentDedEkiCont->get(iEkiIndex).getOuterTerminalEkimeiCount();

		CDlgEkijikokuProp	aDlg( 
			pCmd->getCaMuiSelect()->getMuPtr() , 
			&bJikokuModify ,
			iEkiOrder,
			iMainTrack,
			iStandardRessyaTrackIndex,
			//iOuterTerminalCount,
			iFocusItem,
			&m_CKeyinputSenderToModalDlg ,  
			getCWndDcdGrid()  ) ;
		if ( aDlg.DoModal() == IDOK )
		{
			iRv = 1 ;
		}
		// --------------------------------
		//	ダイアログOK時の処理
		// --------------------------------
		if ( iRv == 1 )
		{
			//	CWndJikokuhyou オブジェクトに
			//	繰上げ・繰下げの設定を反映
			getCWndDcdGrid()->setModifyEkijikoku( bJikokuModify ) ;

			// --------------------------------
			//	分岐駅・環状線・作業の調整
			// --------------------------------
			const Mu<CentDedEkiCont::CdDedEki>* pMuCentDedEki =
				pCentDedEkiCont->getMuPtr(getRessyahoukou());

			for (int idx = 0; idx < pCmd->getCaMuiSelect()->size(); idx++)
			{
				AdjustBrunchLoop(
					iEkiOrder,
					pCmd->getCaMuiSelect()->getMuPtr()->get(idx),
					iEkiAtsukaiPrev[idx]);

				pCmd->getCaMuiSelect()->getMuPtr()->get(idx)->adjustOperation(
					pCentDedEkiCont, pMuCentDedEki);
			}

			// --------------------------------
			//	編集コマンドを実行
			// --------------------------------
			getCDiagramEditDoc()->executeEditCmd( pCmd ) ;

			// --------------------------------
			//	フォーカスセルを移します。
			// --------------------------------
			if ( bInsert )
			{
				// --------------------------------
				//	フォーカスセルを、新設列車の次の駅に
				//	移します。
				// --------------------------------

				//	フォーカスセルを、新設列車のX列に移動
				{
					CDcdGridCell*	pCell = getCWndDcdGrid()->
						getCXDcdGrid()->calcMovedCell( 
							getCWndDcdGrid()->getCFocus()->getFocusCell() , 
							-1 , 
							0 ) ;
					if ( pCell ){
						getCWndDcdGrid()->getCFocus()->setFocusCell( pCell ) ;
					}
				}
				//	フォーカスセルを次へ移します。
				moveFocusCellToNext( true ) ;	
			}
			else 
			{
				//	フォーカスセルを次へ移します。
				moveFocusCellToNext( true ) ;
			}
		}
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return ( iRv ) ;

}
int CWjkState_Ressyahensyu::
execCDlgOperationProp(bool bInsert, BOOL bQueryEnable)
{
	int iRv = 0;

	Ou<EditCmd::CRfEditCmd_Ressya> pCmd;
	Ou<EditCmd::CRfEditCmd_Ressya>* ppCmd = NULL;
	if (!bQueryEnable)
	{
		ppCmd = &pCmd;
	}
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -2;
		}
	}
	CdDedJikokuOrder	aCdJikokuOrder;
	if (iRv >= 0)
	{
		if (bInsert)
		{
			if (!getCWndDcdGrid()->createCmd(CWndJikokuhyou::ECreateCmd_NewItem, ppCmd))
			{
				iRv = -1;	//	列車選択位置が正しくありません。
			}
		}
		else
		{
			if (!getCWndDcdGrid()->createCmd(CWndJikokuhyou::ECreateCmd_Focus, ppCmd))
			{
				iRv = -1;	//	列車選択位置が正しくありません。
			}
		}
	}
	int iChakuEkiOrder;
	int iHatsuEkiOrder;
	int iFocusItem;
	bool bFocusAfter = false;
	int iFocusIndex = -1;
	bool bFocusChild = false;
	//-0;	//	作業種類
	//-1;	//	コンボ1 入換番線
	//-2;	//	エディット1
	//-3;	//	エディット2
	//-4;	//	運用番号
	//-5;	//	チェック1
	//-6;	//	種別変更
	//-7;	//	コンボ1 増結位置
	//-8;	//	コンボ1 解結位置
	//-9;	//	コンボ1 路線外発着駅名
	//-10;	//	入出区連携コード
	CdYColSpec	aYColSpec =
		getCWndDcdGrid()->getYColSpecOfFocus();
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getXColSpecOfFocus().getColumnType() == CdXColSpec::ColumnType_NewRessya)
		{
			iRv = -5;
		}
		else if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_Ekijikoku_Chaku ||
			aYColSpec.getColumnType() == CdYColSpec::ColumnType_Track || 
			aYColSpec.getColumnType() == CdYColSpec::ColumnType_Ekijikoku_Hatsu )
		{
			iChakuEkiOrder = getCWndDcdGrid()->getYColSpecOfFocus().getEkiOrder();
			iFocusItem = 0;
		}
		else if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_ShihatsuEkimei ||
			aYColSpec.getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu1 ||
			aYColSpec.getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu2 ||
			aYColSpec.getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu3 ||
			aYColSpec.getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu4 ||
			aYColSpec.getColumnType() == CdYColSpec::ColumnType_Outer_Shihatsu1 ||
			aYColSpec.getColumnType() == CdYColSpec::ColumnType_Outer_Shihatsu2)
		{
			/*if (getCWndDcdGrid()->getXColSpecOfFocus().getColumnType() == CdXColSpec::ColumnType_NewRessya)
			{
				iRv = -5;
			}
			else */if (getCWndDcdGrid()->getCSelect()->getSelectedCellCount() == 0)
			{
				const CentDedRessyaCont* pCentDedRessyaCont = NULL;
				const CentDedRessya* pCentDedRessya = NULL;
				pCentDedRessyaCont = getCentDedRessyaCont();
				CdXColSpec aCdXColSpec = getCWndDcdGrid()->getXColSpecOfFocus();
				pCentDedRessya = pCentDedRessyaCont->getMuPtr()->get(aCdXColSpec.getRessyaIndex());
				if (pCentDedRessya->isNull() || pCentDedRessya->getValidSihatsuEki() == -1)
				{
					iRv = -7;
				}
				else
				{
					iChakuEkiOrder = pCentDedRessya->getValidSihatsuEki();
					if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_ShihatsuEkimei)
					{
						iFocusItem = 0;
						iFocusIndex = -1;
					}
					else if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu1)
					{
						bFocusAfter = false;
						iFocusIndex = 0;
						/**
							前列車接続：作業種類(空白)
							出区：作業種類("出区")
							路線外始発：コンボ(路線外始発駅名)
						*/
						if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
						{
							iFocusItem = 9;
						}
						else
						{
							iFocusItem = 0;
						}
					}
					else if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu2)
					{
						bFocusAfter = false;
						iFocusIndex = 0;
						/**
							前列車接続：エディット1(起点時刻)
							出区：エディット1(出区時刻)
							路線外始発：エディット2(当駅着時刻)
						*/
						if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Junction ||
							pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Out)
						{
							iFocusItem = 2;
						}
						else
						{
							iFocusItem = 3;
						}
					}
					else if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu3)
					{
						bFocusAfter = false;
						iFocusIndex = 0;
						/**
							前列車接続：運用番号(仮運用番号)
							出区：運用番号(運用番号)
							路線外始発：運用番号(運用番号)
						*/
						iFocusItem = 4;
					}
					else if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu4)
					{
						bFocusAfter = false;
						iFocusIndex = 0;
						/**
							前列車接続：作業種類(なし)
							出区：入出区連携コード(入出区連携コード)
							路線外始発：入出区連携コード(入出区連携コード)
						*/
						if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer ||
							pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Out)
						{
							iFocusItem = 10;
						}
						else
						{
							iFocusItem = 0;
						}
					}
					else if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_Outer_Shihatsu1)
					{
						//Ver2.0 この項目が、編集モードに搭載されるかどうかは未定
						bFocusAfter = false;
						iFocusIndex = 0;
						/**
							前列車接続：作業種類(空白)
							出区：作業種類(空白)
							路線外始発：コンボ(路線外始発駅名)
						*/
						if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
						{
							iFocusItem = 9;
						}
						else
						{
							iFocusItem = 0;
						}
					}
					else if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_Outer_Shihatsu2)
					{
						//Ver2.0 この項目が、編集モードに搭載されるかどうかは未定
						bFocusAfter = false;
						iFocusIndex = 0;
						/**
							前列車接続：作業種類(空白)
							出区：作業種類(空白)
							路線外始発：エディット1(路線外始発駅発時刻)
						*/
						if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
						{
							iFocusItem = 2;
						}
						else
						{
							iFocusItem = 0;
						}
					}
				}
			}
			else
			{
				iRv = -3;
			}
		}
		else if (aYColSpec == CdYColSpec::ColumnType_ShuchakuEkimei ||
			aYColSpec == CdYColSpec::ColumnType_Operation_Shuchaku1 ||
			aYColSpec == CdYColSpec::ColumnType_Operation_Shuchaku2 ||
			aYColSpec == CdYColSpec::ColumnType_Operation_Shuchaku3 ||
			aYColSpec.getColumnType() == CdYColSpec::ColumnType_Outer_Shuchaku1 ||
			aYColSpec.getColumnType() == CdYColSpec::ColumnType_Outer_Shuchaku2)
		{
			/*if (getCWndDcdGrid()->getXColSpecOfFocus().getColumnType() == CdXColSpec::ColumnType_NewRessya)
			{
				iRv = -6;
			}
			else */if (getCWndDcdGrid()->getCSelect()->getSelectedCellCount() == 0)
			{
				const CentDedRessyaCont* pCentDedRessyaCont = NULL;
				const CentDedRessya* pCentDedRessya = NULL;
				pCentDedRessyaCont = getCentDedRessyaCont();
				CdXColSpec aCdXColSpec = getCWndDcdGrid()->getXColSpecOfFocus();
				pCentDedRessya = pCentDedRessyaCont->getMuPtr()->get(aCdXColSpec.getRessyaIndex());
				if (pCentDedRessya->isNull() || pCentDedRessya->getValidSyuuchakuEki() == -1)
				{
					iRv = -8;
				}
				else
				{
					iChakuEkiOrder = pCentDedRessya->getValidSyuuchakuEki();
					if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_ShuchakuEkimei)
					{
						iFocusItem = 0;
						iFocusIndex = -1;
					}
					else if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku1)
					{
						bFocusAfter = true;
						iFocusIndex = pCentDedRessya->getCentDedEkiJikoku(iChakuEkiOrder).getCentDedAfterOperationCont()->size() - 1;
						//iFocusIndex = INT_MAX;
						/**
							次列車接続：作業種類(空白)
							入区：作業種類("入区")
							路線外終着：コンボ(路線外終着駅名)
						*/
						if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
						{
							iFocusItem = 9;
						}
						else
						{
							iFocusItem = 0;
						}
					}
					else if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku2)
					{
						bFocusAfter = true;
						iFocusIndex = pCentDedRessya->getCentDedEkiJikoku(iChakuEkiOrder).getCentDedAfterOperationCont()->size() - 1;
						//iFocusIndex = INT_MAX;
						/**
							次列車接続：エディット1(終点時刻)
							入区：エディット1(入区時刻)
							路線外終着：エディット1(当駅発時刻)
						*/
						iFocusItem = 2;
					}
					else if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku3)
					{
						bFocusAfter = true;
						iFocusIndex = pCentDedRessya->getCentDedEkiJikoku(iChakuEkiOrder).getCentDedAfterOperationCont()->size() - 1;
						/**
							次列車接続：作業種類(なし)
							入区：入出区連携コード(入出区連携コード)
							路線外終着：入出区連携コード(入出区連携コード)
						*/
						if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer ||
							pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_In)
						{
							iFocusItem = 10;
						}
						else
						{
							iFocusItem = 0;
						}
					}
					else if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_Outer_Shuchaku1)
					{
						//Ver2.0 この項目が、編集モードに搭載されるかどうかは未定
						bFocusAfter = true;
						iFocusIndex = pCentDedRessya->getCentDedEkiJikoku(iChakuEkiOrder).getCentDedAfterOperationCont()->size() - 1;
						//iFocusIndex = INT_MAX;
						/**
							次列車接続：作業種類(空白)
							入区：作業種類(空白)
							路線外終着：コンボ(路線外終着駅名)
						*/
						if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
						{
							iFocusItem = 9;
						}
						else
						{
							iFocusItem = 0;
						}
					}
					else if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_Outer_Shuchaku2)
					{
						//Ver2.0 この項目が、編集モードに搭載されるかどうかは未定
						bFocusAfter = true;
						iFocusIndex = pCentDedRessya->getCentDedEkiJikoku(iChakuEkiOrder).getCentDedAfterOperationCont()->size() - 1;
						//iFocusIndex = INT_MAX;
						/**
							次列車接続：作業種類(空白)
							入区：作業種類(空白)
							路線外終着：エディット2(路線外終着駅着時刻)
						*/
						if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
						{
							iFocusItem = 3;
						}
						else
						{
							iFocusItem = 0;
						}
					}
				}
			}
			else
			{
				iRv = -3;
			}
		}
		else if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperation1 ||
			aYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperation2)
		{
			if (getCWndDcdGrid()->getXColSpecOfFocus().getColumnType() == CdXColSpec::ColumnType_NewRessya)
			{
				iRv = -5;
			}
			else if (getCWndDcdGrid()->getCSelect()->getSelectedCellCount() == 0)
			{
				const CentDedRessyaCont* pCentDedRessyaCont = NULL;
				const CentDedRessya* pCentDedRessya = NULL;
				pCentDedRessyaCont = getCentDedRessyaCont();
				CdXColSpec aCdXColSpec = getCWndDcdGrid()->getXColSpecOfFocus();
				pCentDedRessya = pCentDedRessyaCont->getMuPtr()->get(aCdXColSpec.getRessyaIndex());
				if (pCentDedRessya->isNull() || pCentDedRessya->getSihatsuEki() == -1)
				{
					iRv = -7;
				}
				else
				{
					iChakuEkiOrder = aYColSpec.getEkiOrder();
					bFocusAfter = false;
					const CentDedBeforeOperationCont* pBeforeCont = pCentDedRessya->getCentDedEkiJikokuCont()
						->getMuPtr()->get(iChakuEkiOrder)->getCentDedBeforeOperationCont();

					const CentDedRosen* pCentDedRosen =
						getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen();
					const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
						pCentDedRosen->getCentDedEkiCont()->getMuPtr(
							pCentDedRessya->getRessyahoukou());
					CentDedEkiCont::CdDedEki aEki = muCdDedEki->get(iChakuEkiOrder);

					if (pBeforeCont->size() == 0 ||
						(pBeforeCont->size() == 1 &&
							pBeforeCont->getMuPtr()->get(0)->isFirstOperation()))
					{
						iFocusItem = 0;
						iFocusIndex = -1;
					}
					else if(pBeforeCont->getMuPtr()->get(0)->isFirstOperation())
					{
						/**
							iTargetPosは、選択された位置に、表示されている作業のCont内Index。
							ただし、作業数が表示数よりも少ない場合は、空白の場合もあるので、比較を行う
						*/
						int iTargetPos =
							max((pBeforeCont->size() - aEki.getJikokuhyouBeforeOperation() + aYColSpec.getOperationIndex()),
								aYColSpec.getOperationIndex() + 1);
						if (iTargetPos < pBeforeCont->size())
						{
							iFocusIndex = iTargetPos;
							if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperation1)
							{
								/**
									入換：コンボ1(入換番線)
									増結：コンボ1(増結位置)
									解結：コンボ1(解結位置・数)
									運用番号変更：作業種類("運番変更")
								*/
								if (pBeforeCont->getMuPtr()->get(iTargetPos)->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
								{
									iFocusItem = 1;
								}
								else if (pBeforeCont->getMuPtr()->get(iTargetPos)->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
								{
									iFocusItem = 7;
								}
								else if (pBeforeCont->getMuPtr()->get(iTargetPos)->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
								{
									iFocusItem = 8;
								}
								else
								{
									iFocusItem = 0;
								}
							}
							else if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperation2)
							{
								/**
									入換：エディット1(入換発時刻)
									増結：エディット1(増結時刻)
									解結：エディット2(解結時刻)
									運用番号変更：運用番号(運用番号)
								*/
								if (pBeforeCont->getMuPtr()->get(iTargetPos)->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
								{
									iFocusItem = 3;
								}
								else if (pBeforeCont->getMuPtr()->get(iTargetPos)->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_NumberChange)
								{
									iFocusItem = 4;
								}
								else
								{
									iFocusItem = 2;
								}
							}

						}
						else
						{
							iFocusItem = 0;
							iFocusIndex = -1;
						}
					}
					else
					{
						/**
							iTargetPosは、選択された位置に、表示されている作業のCont内Index。
							ただし、作業数が表示数よりも少ない場合は、空白の場合もあるので、比較を行う
						*/
						int iTargetPos = 
							max((pBeforeCont->size() - aEki.getJikokuhyouBeforeOperation() + aYColSpec.getOperationIndex()),
								aYColSpec.getOperationIndex());
						if (iTargetPos < pBeforeCont->size())
						{
							iFocusIndex = iTargetPos;
							if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperation1)
							{
								/**
									入換：コンボ1(入換番線)
									増結：コンボ1(増結位置)
									解結：コンボ1(解結位置・数)
									運用番号変更：作業種類("運番変更")
								*/
								if (pBeforeCont->getMuPtr()->get(iTargetPos)->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
								{
									iFocusItem = 1;
								}
								else if (pBeforeCont->getMuPtr()->get(iTargetPos)->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
								{
									iFocusItem = 7;
								}
								else if (pBeforeCont->getMuPtr()->get(iTargetPos)->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
								{
									iFocusItem = 8;
								}
								else
								{
									iFocusItem = 0;
								}
							}
							else if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperation2)
							{
								/**
									入換：エディット1(入換発時刻)
									増結：エディット1(増結時刻)
									解結：エディット2(解結時刻)
									運用番号変更：運用番号(運用番号)
								*/
								if (pBeforeCont->getMuPtr()->get(iTargetPos)->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
								{
									iFocusItem = 3;
								}
								else if (pBeforeCont->getMuPtr()->get(iTargetPos)->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_NumberChange)
								{
									iFocusItem = 4;
								}
								else
								{
									iFocusItem = 2;
								}
							}
						}
						else
						{
							iFocusItem = 0;
							iFocusIndex = -1;
						}
					}
				}
			}
			else
			{
				iRv = -3;
			}
		}
		else if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperation1 ||
			aYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperation2)
		{
			if (getCWndDcdGrid()->getXColSpecOfFocus().getColumnType() == CdXColSpec::ColumnType_NewRessya)
			{
				iRv = -5;
			}
			else if (getCWndDcdGrid()->getCSelect()->getSelectedCellCount() == 0)
			{
				const CentDedRessyaCont* pCentDedRessyaCont = NULL;
				const CentDedRessya* pCentDedRessya = NULL;
				pCentDedRessyaCont = getCentDedRessyaCont();
				CdXColSpec aCdXColSpec = getCWndDcdGrid()->getXColSpecOfFocus();
				pCentDedRessya = pCentDedRessyaCont->getMuPtr()->get(aCdXColSpec.getRessyaIndex());
				if (pCentDedRessya->isNull() || pCentDedRessya->getSihatsuEki() == -1)
				{
					iRv = -7;
				}
				else
				{
					iChakuEkiOrder = aYColSpec.getEkiOrder();
					bFocusAfter = true;
					const CentDedAfterOperationCont* pAfterCont = pCentDedRessya->getCentDedEkiJikokuCont()
						->getMuPtr()->get(iChakuEkiOrder)->getCentDedAfterOperationCont();

					const CentDedRosen* pCentDedRosen =
						getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen();
					const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
						pCentDedRosen->getCentDedEkiCont()->getMuPtr(
							pCentDedRessya->getRessyahoukou());
					CentDedEkiCont::CdDedEki aEki = muCdDedEki->get(iChakuEkiOrder);

					if (aYColSpec.getOperationIndex() < pAfterCont->size())
					{
						if (pAfterCont->getMuPtr()->get(aYColSpec.getOperationIndex())->isLastOperation())
						{
							iFocusItem = 0;
							iFocusIndex = -1;
						}
						else if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperation1)
						{
							/**
								入換：コンボ1(入換番線)
								増結：コンボ1(増結位置)
								解結：コンボ1(解結位置・数)
								運用番号変更：作業種類("運番変更")
							*/
							iFocusIndex = aYColSpec.getOperationIndex();
							if (pAfterCont->getMuPtr()->get(iFocusIndex)->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
							{
								iFocusItem = 1;
							}
							else if (pAfterCont->getMuPtr()->get(iFocusIndex)->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
							{
								iFocusItem = 7;
							}
							else if (pAfterCont->getMuPtr()->get(iFocusIndex)->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
							{
								iFocusItem = 8;
							}
							else
							{
								iFocusItem = 0;
							}
						}
						else if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperation2)
						{
							/**
								入換：エディット1(入換発時刻)
								増結：エディット1(増結時刻)
								解結：エディット2(解結時刻)
								運用番号変更：運用番号(運用番号)
							*/
							iFocusIndex = aYColSpec.getOperationIndex();
							if (pAfterCont->getMuPtr()->get(iFocusIndex)->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
							{
								iFocusItem = 3;
							}
							else if (pAfterCont->getMuPtr()->get(iFocusIndex)->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
							{
								iFocusItem = 4;
							}
							else
							{
								iFocusItem = 2;
							}
						}
					}
					else
					{
						iFocusItem = 0;
						iFocusIndex = -1;
					}
				}
			}
			else
			{
				iRv = -3;
			}
		}
		else if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore1 ||
			aYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore2 ||
			aYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore3 ||
			aYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore4)
		{
			if (getCWndDcdGrid()->getXColSpecOfFocus().getColumnType() == CdXColSpec::ColumnType_NewRessya)
			{
				iRv = -5;
			}
			else if (getCWndDcdGrid()->getCSelect()->getSelectedCellCount() == 0)
			{
				const CentDedRessyaCont* pCentDedRessyaCont = NULL;
				const CentDedRessya* pCentDedRessya = NULL;
				pCentDedRessyaCont = getCentDedRessyaCont();
				CdXColSpec aCdXColSpec = getCWndDcdGrid()->getXColSpecOfFocus();
				pCentDedRessya = pCentDedRessyaCont->getMuPtr()->get(aCdXColSpec.getRessyaIndex());
				if (pCentDedRessya->isNull() || pCentDedRessya->getSihatsuEki() == -1)
				{
					iRv = -7;
				}
				else
				{
					iChakuEkiOrder = aYColSpec.getEkiOrder();
					bFocusAfter = false; 
					bFocusChild = true;
					const CentDedBeforeOperationCont* pBeforeCont = pCentDedRessya->getCentDedEkiJikokuCont()
						->getMuPtr()->get(iChakuEkiOrder)->getCentDedBeforeOperationCont();

					const CentDedRosen* pCentDedRosen =
						getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen();
					const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
						pCentDedRosen->getCentDedEkiCont()->getMuPtr(
							pCentDedRessya->getRessyahoukou());
					CentDedEkiCont::CdDedEki aEki = muCdDedEki->get(iChakuEkiOrder);

					const CentDedBeforeOperation* pFirstOperation = NULL;
					for (int idx = pBeforeCont->size() - 1; idx >= 0; idx--)
					{
						if (pBeforeCont->get(idx).getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
						{
							const CentDedBeforeOperationCont* pBeforeOperationOfConnectCont = pBeforeCont->getMuPtr()->get(idx)->getCentDedBeforeOperationCont();
							pFirstOperation = pBeforeOperationOfConnectCont->getMuPtr()->get(0);
							iFocusIndex = idx;
							break;
						}
					}

					if (pFirstOperation != NULL)
					{
						if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore1)
						{
							/**
								前列車接続：作業種類("前接続")
								出区：作業種類("出区")
								路線外始発：コンボ(路線外始発駅名)
							*/
							if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
							{
								iFocusItem = 9;
							}
							else
							{
								iFocusItem = 0;
							}
						}
						else if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore2)
						{
							/**
								前列車接続：エディット1(起点時刻)
								出区：エディット1(出区時刻)
								路線外始発：エディット2(当駅着時刻)
							*/
							if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Junction ||
								pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Out)
							{
								iFocusItem = 2;
							}
							else
							{
								iFocusItem = 3;
							}
						}
						else if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore3)
						{
							/**
								前列車接続：運用番号(仮運用番号)
								出区：運用番号(運用番号)
								路線外始発：運用番号(運用番号)
							*/
							iFocusItem = 4;
						}
						else if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore4)
						{
							/**
								前列車接続：作業種類(なし)
								出区：入出区連携コード(入出区連携コード)
								路線外始発：入出区連携コード(入出区連携コード)
							*/
							if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer ||
								pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Out)
							{
								iFocusItem = 10;
							}
							else
							{
								iFocusItem = 0;
							}
						}

					}
					else
					{
						iFocusItem = 0;
						iFocusIndex = -1;
					}
				}
			}
			else
			{
				iRv = -3;
			}
		}
		else if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter1 ||
			aYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter2 ||
			aYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter3)
		{
			if (getCWndDcdGrid()->getXColSpecOfFocus().getColumnType() == CdXColSpec::ColumnType_NewRessya)
			{
				iRv = -5;
			}
			else if (getCWndDcdGrid()->getCSelect()->getSelectedCellCount() == 0)
			{
				const CentDedRessyaCont* pCentDedRessyaCont = NULL;
				const CentDedRessya* pCentDedRessya = NULL;
				pCentDedRessyaCont = getCentDedRessyaCont();
				CdXColSpec aCdXColSpec = getCWndDcdGrid()->getXColSpecOfFocus();
				pCentDedRessya = pCentDedRessyaCont->getMuPtr()->get(aCdXColSpec.getRessyaIndex());
				if (pCentDedRessya->isNull() || pCentDedRessya->getSihatsuEki() == -1)
				{
					iRv = -7;
				}
				else
				{
					iChakuEkiOrder = aYColSpec.getEkiOrder();
					bFocusAfter = false;
					bFocusChild = true;
					const CentDedBeforeOperationCont* pBeforeCont = pCentDedRessya->getCentDedEkiJikokuCont()
						->getMuPtr()->get(iChakuEkiOrder)->getCentDedBeforeOperationCont();

					const CentDedRosen* pCentDedRosen =
						getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen();
					const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
						pCentDedRosen->getCentDedEkiCont()->getMuPtr(
							pCentDedRessya->getRessyahoukou());
					CentDedEkiCont::CdDedEki aEki = muCdDedEki->get(iChakuEkiOrder);

					const CentDedAfterOperation* pLastOperation = NULL;
					for (int idx = pBeforeCont->size() - 1; idx >= 0; idx--)
					{
						if (pBeforeCont->get(idx).getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
						{
							const CentDedAfterOperationCont* pAfterOperationOfReleaseCont = pBeforeCont->getMuPtr()->get(idx)->getCentDedAfterOperationCont();
							pLastOperation = pAfterOperationOfReleaseCont->getMuPtr()->get(INT_MAX);
							iFocusIndex = idx;
							break;
						}
					}

					if (pLastOperation != NULL)
					{
						if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter1)
						{
							/**
								次列車接続：作業種類("次接続")
								入区：作業種類("入区")
								路線外終着：コンボ(路線外終着駅名)
							*/
							if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
							{
								iFocusItem = 9;
							}
							else
							{
								iFocusItem = 0;
							}
						}
						else if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter2)
						{
							/**
								次列車接続：エディット1(終点時刻)
								入区：エディット1(入区時刻)
								路線外終着：エディット1(当駅発時刻)
							*/
							iFocusItem = 2;
						}
						else if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter3)
						{
							/**
								次列車接続：作業種類(なし)
								入区：入出区連携コード(入出区連携コード)
								路線外終着：入出区連携コード(入出区連携コード)
							*/
							if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer ||
								pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_In)
							{
								iFocusItem = 10;
							}
							else
							{
								iFocusItem = 0;
							}
						}
					}
					else
					{
						iFocusItem = 0;
						iFocusIndex = -1;
					}
				}
			}
			else
			{
				iRv = -3;
			}
		}
		else if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore1 ||
			aYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore2 ||
			aYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore3 ||
			aYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore4)
		{
			if (getCWndDcdGrid()->getXColSpecOfFocus().getColumnType() == CdXColSpec::ColumnType_NewRessya)
			{
				iRv = -5;
			}
			else if (getCWndDcdGrid()->getCSelect()->getSelectedCellCount() == 0)
			{
				const CentDedRessyaCont* pCentDedRessyaCont = NULL;
				const CentDedRessya* pCentDedRessya = NULL;
				pCentDedRessyaCont = getCentDedRessyaCont();
				CdXColSpec aCdXColSpec = getCWndDcdGrid()->getXColSpecOfFocus();
				pCentDedRessya = pCentDedRessyaCont->getMuPtr()->get(aCdXColSpec.getRessyaIndex());
				if (pCentDedRessya->isNull() || pCentDedRessya->getSihatsuEki() == -1)
				{
					iRv = -7;
				}
				else
				{
					iChakuEkiOrder = aYColSpec.getEkiOrder();
					bFocusAfter = true;
					bFocusChild = true;
					const CentDedAfterOperationCont* pAfterCont = pCentDedRessya->getCentDedEkiJikokuCont()
						->getMuPtr()->get(iChakuEkiOrder)->getCentDedAfterOperationCont();

					const CentDedRosen* pCentDedRosen =
						getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen();
					const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
						pCentDedRosen->getCentDedEkiCont()->getMuPtr(
							pCentDedRessya->getRessyahoukou());
					CentDedEkiCont::CdDedEki aEki = muCdDedEki->get(iChakuEkiOrder);

					const CentDedBeforeOperation* pFirstOperation = NULL;
					for (int idx = 0; idx < pAfterCont->size(); idx++)
					{
						if (pAfterCont->get(idx).getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
						{
							const CentDedBeforeOperationCont* pBeforeOperationOfConnectCont = pAfterCont->getMuPtr()->get(idx)->getCentDedBeforeOperationCont();
							pFirstOperation = pBeforeOperationOfConnectCont->getMuPtr()->get(0);
							iFocusIndex = idx;
							break;
						}
					}

					if (pFirstOperation != NULL)
					{
						if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore1)
						{
							/**
								前列車接続：作業種類("前接続")
								出区：作業種類("出区")
								路線外始発：コンボ(路線外始発駅名)
							*/
							if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
							{
								iFocusItem = 9;
							}
							else
							{
								iFocusItem = 0;
							}
						}
						else if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore2)
						{
							/**
								前列車接続：エディット1(起点時刻)
								出区：エディット1(出区時刻)
								路線外始発：エディット2(当駅着時刻)
							*/
							if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Junction ||
								pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Out)
							{
								iFocusItem = 2;
							}
							else
							{
								iFocusItem = 3;
							}
						}
						else if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore3)
						{
							/**
								前列車接続：運用番号(仮運用番号)
								出区：運用番号(運用番号)
								路線外始発：運用番号(運用番号)
							*/
							iFocusItem = 4;
						}
						else if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore4)
						{
							/**
								前列車接続：作業種類(なし)
								出区：入出区連携コード(入出区連携コード)
								路線外始発：入出区連携コード(入出区連携コード)
							*/
							if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer ||
								pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Out)
							{
								iFocusItem = 10;
							}
							else
							{
								iFocusItem = 0;
							}
						}

					}
					else
					{
						iFocusItem = 0;
						iFocusIndex = -1;
					}
				}
			}
			else
			{
				iRv = -3;
			}
		}
		else if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter1 ||
			aYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter2 ||
			aYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter3)
		{
			if (getCWndDcdGrid()->getXColSpecOfFocus().getColumnType() == CdXColSpec::ColumnType_NewRessya)
			{
				iRv = -5;
			}
			else if (getCWndDcdGrid()->getCSelect()->getSelectedCellCount() == 0)
			{
				const CentDedRessyaCont* pCentDedRessyaCont = NULL;
				const CentDedRessya* pCentDedRessya = NULL;
				pCentDedRessyaCont = getCentDedRessyaCont();
				CdXColSpec aCdXColSpec = getCWndDcdGrid()->getXColSpecOfFocus();
				pCentDedRessya = pCentDedRessyaCont->getMuPtr()->get(aCdXColSpec.getRessyaIndex());
				if (pCentDedRessya->isNull() || pCentDedRessya->getSihatsuEki() == -1)
				{
					iRv = -7;
				}
				else
				{
					iChakuEkiOrder = aYColSpec.getEkiOrder();
					bFocusAfter = true;
					bFocusChild = true;
					const CentDedAfterOperationCont* pAfterCont = pCentDedRessya->getCentDedEkiJikokuCont()
						->getMuPtr()->get(iChakuEkiOrder)->getCentDedAfterOperationCont();

					const CentDedRosen* pCentDedRosen =
						getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen();
					const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
						pCentDedRosen->getCentDedEkiCont()->getMuPtr(
							pCentDedRessya->getRessyahoukou());
					CentDedEkiCont::CdDedEki aEki = muCdDedEki->get(iChakuEkiOrder);

					const CentDedAfterOperation* pLastOperation = NULL;
					for (int idx = 0; idx < pAfterCont->size(); idx++)
					{
						if (pAfterCont->get(idx).getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
						{
							const CentDedAfterOperationCont* pAfterOperationOfReleaseCont = pAfterCont->getMuPtr()->get(idx)->getCentDedAfterOperationCont();
							pLastOperation = pAfterOperationOfReleaseCont->getMuPtr()->get(INT_MAX);
							iFocusIndex = idx;
							break;
						}
					}

					if (pLastOperation != NULL)
					{
						if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter1)
						{
							/**
								次列車接続：作業種類("次接続")
								入区：作業種類("入区")
								路線外終着：コンボ(路線外終着駅名)
							*/
							if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
							{
								iFocusItem = 9;
							}
							else
							{
								iFocusItem = 0;
							}
						}
						else if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter2)
						{
							/**
								次列車接続：エディット1(終点時刻)
								入区：エディット1(入区時刻)
								路線外終着：エディット1(当駅発時刻)
							*/
							iFocusItem = 2;
						}
						else if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter3)
						{
							/**
								次列車接続：作業種類(なし)
								入区：入出区連携コード(入出区連携コード)
								路線外終着：入出区連携コード(入出区連携コード)
							*/
							if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer ||
								pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_In)
							{
								iFocusItem = 10;
							}
							else
							{
								iFocusItem = 0;
							}
						}
					}
					else
					{
						iFocusItem = 0;
						iFocusIndex = -1;
					}
				}
			}
			else
			{
				iRv = -3;
			}
		}
		else
		{
			aCdJikokuOrder = getCWndDcdGrid()->CdDedJikokuOrderOf(
				getCWndDcdGrid()->getYColSpecOfFocus());
			if (aCdJikokuOrder.getIsNull())
			{
				iRv = -2;	//	Y列番号が不正です。
			}
			else
			{
				iChakuEkiOrder = aCdJikokuOrder.getEkiOrder();
				iFocusItem = aCdJikokuOrder.getEkiJikokuItem()
					== CdDedJikokuOrder::EkiJikokuItem_Hatsu ? 2 : 1;
			}
		}
	}
	if (iRv >= 0 && iChakuEkiOrder >= 0)
	{
		//const CentDedRosen* pCentDedRosen =
		//	getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen();
		//const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
		//	pCentDedRosen->getCentDedEkiCont()->getMuPtr(
		//		getRessyahoukou());
		//CentDedEkiCont::CdDedEki aEki = muCdDedEki->get(iEkiOrder);
		//if(aEki.get)

		const CentDedRessyaCont* pCentDedRessyaCont = NULL;
		const CentDedRessya* pCentDedRessya = NULL;
		pCentDedRessyaCont = getCentDedRessyaCont();
		CdXColSpec aCdXColSpec = getCWndDcdGrid()->getXColSpecOfFocus();
		pCentDedRessya = pCentDedRessyaCont->getMuPtr()->get(aCdXColSpec.getRessyaIndex());
		if (iChakuEkiOrder == pCentDedRessya->getValidSihatsuEki())
		{
			//有効な始発駅の要件に、その駅の発時刻が存在することが含まれているので、時刻のチェックは不要。
			iHatsuEkiOrder = iChakuEkiOrder;
			iChakuEkiOrder = -1;
		}
		else if (iChakuEkiOrder == pCentDedRessya->getValidSyuuchakuEki())
		{
			iHatsuEkiOrder = -1;
		}
		else if (iChakuEkiOrder > pCentDedRessya->getValidSihatsuEki() ||
			iChakuEkiOrder < pCentDedRessya->getValidSyuuchakuEki())
		{
			CentDedEkiJikoku aEkiJikoku = pCentDedRessya->getCentDedEkiJikoku(iChakuEkiOrder);
			if (aEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_None)
			{
				iRv = -11;
			}
			else/* if (aEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya)*/
			{
				/**
					停車の場合、前後の駅扱いを確認。両側とも経由無し・運行無しなら無効
					片側のみ運行無しなら無効
					片側のみ経由無しなら、経由無しを挟んで、経由無し以外の駅を取得、
						駅扱いの一致及び駅時刻の有無等を確認。
					両側とも停車・通過の場合は、当駅に着発両時刻が有るかをチェック
				*/
				const CentDedEkiCont* pEkiCont = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont();

				const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
					getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
					->getCentDedEkiCont()->getMuPtr(getRessyahoukou());
				CentDedEkiCont::CdDedEki aEki = muCdDedEki->get(iChakuEkiOrder);
				/**
					前後ともisRunBetweenNextEkiがtrueの場合は、
					駅時刻が着発とも存在することを確認する。
				*/
				if (aEki.isHatsuChakuHyouji() && 
					pCentDedRessya->isRunBetweenNextEki(iChakuEkiOrder - 1) &&
					pCentDedRessya->isRunBetweenNextEki(iChakuEkiOrder)&& 
					!aEkiJikoku.getChakujikoku().isNull() &&
					!aEkiJikoku.getHatsujikoku().isNull())
				{
						iHatsuEkiOrder = iChakuEkiOrder;
						//中間駅なのに、前後に経由無し・運行無しがある。もしくは、発着時刻のいずれか・両方がない
				}
				/**
					後ろのみisRunBetweenNextEkiがtrueの場合は、
					前方にさかのぼって、isRunBetweenNextEkiがtrueの駅を探し、両駅が分岐駅関係の場合は、
					駅扱い、時刻有無を確認する。
				*/
				else if (aEki.getHatsujikokuHyouji() &&
					!pCentDedRessya->isRunBetweenNextEki(iChakuEkiOrder - 1) &&
					pCentDedRessya->isRunBetweenNextEki(iChakuEkiOrder) &&
					!aEkiJikoku.getHatsujikoku().isNull())
				{
					iHatsuEkiOrder = iChakuEkiOrder;
					iChakuEkiOrder = pCentDedRessya->getRunBetweenEkiBackward(iHatsuEkiOrder);
					if (iChakuEkiOrder != -1 &&
						!pEkiCont->isSameBrunchLoopGroup(iChakuEkiOrder, iHatsuEkiOrder, getRessyahoukou()))
					{
						iRv = -201;
					}
					if (iRv >= 0)
					{
						//駅扱いおよび時刻条件のチェックに入る
						CentDedEkiJikoku aEkiJikokuChaku = pCentDedRessya->getCentDedEkiJikoku(iChakuEkiOrder);
						CentDedEkiCont::CdDedEki aEkiChaku = muCdDedEki->get(iChakuEkiOrder);
						if (aEkiChaku.getChakujikokuHyouji()&&
							aEkiJikokuChaku.getEkiatsukai() == aEkiJikoku.getEkiatsukai() &&
							!aEkiJikokuChaku.getChakujikoku(false).isNull())
						{
							iRv = 1;
						}
						else
						{
							//基幹駅の駅扱いが発側と一致しない、もしくは着時刻が無い。
							iRv = -202;
						}

					}
				}
				/**
					前のみisRunBetweenNextEkiがtrueの場合は、
					後方に進んで、isRunBetweenNextEkiがtrueの駅を探し、両駅が分岐駅関係の場合は、
					駅扱い、時刻有無を確認する。
				*/
				else if (aEki.getChakujikokuHyouji() &&
					pCentDedRessya->isRunBetweenNextEki(iChakuEkiOrder - 1) &&
					!pCentDedRessya->isRunBetweenNextEki(iChakuEkiOrder) &&
					!aEkiJikoku.getChakujikoku().isNull())
				{
					iHatsuEkiOrder = pCentDedRessya->getRunBetweenEkiForward(iChakuEkiOrder);
					if (iHatsuEkiOrder != -1 &&
						!pEkiCont->isSameBrunchLoopGroup(iChakuEkiOrder, iHatsuEkiOrder, getRessyahoukou()))
					{
						iRv = -301;
					}
					if (iRv >= 0)
					{
						//駅扱いおよび時刻条件のチェックに入る
						CentDedEkiJikoku aEkiJikokuHatsu = pCentDedRessya->getCentDedEkiJikoku(iHatsuEkiOrder);
						CentDedEkiCont::CdDedEki aEkiHatsu = muCdDedEki->get(iHatsuEkiOrder);
						if (aEkiHatsu.getHatsujikokuHyouji()&&
							aEkiJikokuHatsu.getEkiatsukai() == aEkiJikoku.getEkiatsukai() &&
							!aEkiJikokuHatsu.getHatsujikoku(false).isNull())
						{
							iRv = 1;
						}
						else
						{
							//基幹駅の駅扱いが着側と一致しない、もしくは発時刻が無い。
							iRv = -302;
						}
					}

				}
				/**
					中間駅だが時刻が欠けている。
					片方のみisRunBetweenNextEkiがtrueだが、対応する時刻が無い
					両方ともisRunBetweenNextEkiがfalse
					の場合は、コマンド無効とする
				*/
				else
				{
					iRv = -401;
				}
			}
		}
		else
		{
			iRv = -30;
		}
	}
	//aCdJikokuOrder = 編集対象の時刻Orderです

	// ****************************************************************
	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		// --------------------------------
		//	『作業のプロパティ』ダイアログを開く
		// --------------------------------

		const CentDedRosen* pCentDedRosen =
			getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen();
		const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
			pCentDedRosen->getCentDedEkiCont()->getMuPtr(getRessyahoukou());
		CentDedEkiCont::CdDedEki aEki = muCdDedEki->get(max(iChakuEkiOrder, iHatsuEkiOrder));

		int iStandardShuntTrackIndex[2]= { 0,0 };
		vector<vector<int>> iOuterTerminalJikan;
		int iRessyasyubetsuIndex = pCmd->getCaMuiSelect()->getMuPtr()->get(0)->getRessyasyubetsuIndex();
		getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
			->StandardShuntTrackIndexSearch(
				iRessyasyubetsuIndex,
				getRessyahoukou(),
				iChakuEkiOrder,
				iHatsuEkiOrder,
				iStandardShuntTrackIndex);
		getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
			->StandardOuterTerminalJikanSearch(
				iRessyasyubetsuIndex,
				getRessyahoukou(),
				iChakuEkiOrder,
				iHatsuEkiOrder,
				iOuterTerminalJikan);

		CDlgOperationProp	aDlg(
			pCmd->getCaMuiSelect()->getMuPtr(),
			iChakuEkiOrder,
			iHatsuEkiOrder,
			iFocusItem,
			bFocusAfter,
			iFocusIndex,
			bFocusChild,
			aEki.getOuterTerminalEkimeiCount() > 0,
			iStandardShuntTrackIndex,
			iOuterTerminalJikan,
			&m_CKeyinputSenderToModalDlg,
			getCWndDcdGrid());

		if (aDlg.DoModal() == IDOK)
		{
			iRv = 1;
		}
		// --------------------------------
		//	ダイアログOK時の処理
		// --------------------------------
		if (iRv == 1)
		{

			// --------------------------------
			//	分岐駅・環状線の調整
			// --------------------------------
			//for (int idx = 0; idx < pCmd->getCaMuiSelect()->size(); idx++)
			//{
			//	AdjustBrunchLoop(
			//		iEkiOrder,
			//		pCmd->getCaMuiSelect()->getMuPtr()->get(idx),
			//		iEkiAtsukaiPrev[idx]);
			//}

			// --------------------------------
			//	編集コマンドを実行
			// --------------------------------
			getCDiagramEditDoc()->executeEditCmd(pCmd);

			// --------------------------------
			//	フォーカスセルを移します。
			// --------------------------------
			if (bInsert)
			{
				// --------------------------------
				//	フォーカスセルを、新設列車の次の駅に
				//	移します。
				// --------------------------------

				//	フォーカスセルを、新設列車のX列に移動
				{
					CDcdGridCell*	pCell = getCWndDcdGrid()->
						getCXDcdGrid()->calcMovedCell(
							getCWndDcdGrid()->getCFocus()->getFocusCell(),
							-1,
							0);
					if (pCell) {
						getCWndDcdGrid()->getCFocus()->setFocusCell(pCell);
					}
				}
				if (m_bJikokuhyouFocusMoveRight)
				{
					//	フォーカスセルを次へ移します。
					moveFocusCellToNext(true);
				}
			}
			else
			{
				if (m_bJikokuhyouFocusMoveRight)
				{
					//	フォーカスセルを次へ移します。
					moveFocusCellToNext(true);
				}
			}
		}
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return (iRv);

}

int CWjkState_Ressyahensyu::
	moveFocusCellToNext( bool bNextEkiOrder ) 
{
	int iRv = 0 ;
	iRv = getCWndDcdGrid()->moveFocusCellToNext( m_bJikokuhyouFocusMoveRight , bNextEkiOrder ) ;
	return iRv ;
}

int CWjkState_Ressyahensyu::
	moveFocusCellToPrev( bool bNextEkiOrder ) 
{
	int iRv = 0 ;
	iRv = getCWndDcdGrid()->moveFocusCellToPrev( m_bJikokuhyouFocusMoveRight , bNextEkiOrder ) ;
	return iRv ;
}

// ********************************
//	コンストラクタ
// ********************************
CWjkState_Ressyahensyu::
	CWjkState_Ressyahensyu( 
		CWndJikokuhyou*	pCWndDcdGrid )
	: super( pCWndDcdGrid )
	, m_bJikokuhyouFocusMoveRight( false ) 
{
}
CWjkState_Ressyahensyu::
	~CWjkState_Ressyahensyu() 
{
}

	// ********************************
	//	CWjkState
	// ********************************
		// ********************************
		//@name 操作
		// ********************************
void CWjkState_Ressyahensyu::onEnter() 
{
	//	選択範囲の設定
	getCWndDcdGrid()->getCSelect()->setSelectMode( CSelect::SelectMode_XColumn ) ;

	const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont() ;
	if ( pCentDedRessyaCont != NULL )
	{
		const Mu<const CentDedRessya*>* pMuCentDedRessyaCont = pCentDedRessyaCont->getMuPtr() ;
		getCWndDcdGrid()->getCSelect()->setColumnNumberSelectLimit(
			CdDcdZoneXy( 
				CdDcdZone( 2 , pMuCentDedRessyaCont->size() ) , 
				CdDcdZone( 0 , INT_MAX ) 
			) );
	}

	//	この状態に入場時は、全列車選択を解除
	getCWndDcdGrid()->clearSelect() ;
	

}
void CWjkState_Ressyahensyu::onExit() 
{
}

	// ********************************
	//@name CView からの委譲
	// ********************************
void CWjkState_Ressyahensyu::
	OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	if ( lHint == LHINT_SUBVIEW_TO_ROOTDOC )
	{
		return ;
	}
	// --------------------------------
	//pHint= 
	//	pHintが CRfEditCmdHolder オブジェクトなら、
	//	対応する編集コマンド CRfEditCmd を保持しています。
	//	この場合、this は CRfEditCmd の内容に最適化した
	//	更新を行います。
	//	NULLなら、全更新が要求されています。


	//	このビューが非アクティブで、全更新が要求されている場合は
	//	更新は行いません。
	CView *pActiveView = getCDiagramEditApp()->getCMainFrame()->
		getMDIChildActiveView() ;
	if ( pActiveView != getCWndDcdGrid()->GetParent() && getCWndDcdGrid()->getUpdate_All_Requested() )
	{
		//	このビューが非アクティブで、全更新が要求されている場合は
		//	すべての更新を行いません。
	}
	else
	{
		bool bUpdateComplete = false ;
		// --------------------------------
		//	CRfEditCmd に最適化された更新
		// --------------------------------

		Ou<CRfEditCmd> pCmd ;
		if ( pHint != NULL && pHint->IsKindOf( RUNTIME_CLASS( CRfEditCmdHolder ) ) )
		{
			CRfEditCmdHolder* pHolder = 
				(CRfEditCmdHolder*)pHint ;
			pCmd = pHolder->getCmd() ; 
		}


		if ( pCmd != NULL )
		{
			if ( dynamic_castOu<CRfEditCmd_Comment>( pCmd ) || 
				dynamic_castOu<CRfEditCmd_Dia>( pCmd ) || 
				dynamic_castOu<CRfEditCmd_RessyasyubetsuSwap>( pCmd )) 
			{
				//	このビューは、
				//		コメントの変更
				//		ダイヤの変更
				//		列車種別の入替
				//	の場合は、更新を行いません。
				bUpdateComplete = true ;
			}
			else if ( dynamic_castOu<CRfEditCmd_Ressya>( pCmd )	) 
			{
				//	列車の変更
				Ou<CRfEditCmd_Ressya>	pCommand = 
					dynamic_castOu<CRfEditCmd_Ressya>( pCmd );
				OnUpdate_CentDedRessya( pCommand ) ;
				bUpdateComplete = true ;
			}
			else if (dynamic_castOu<CRfEditCmd_Operation>(pCmd))
			{
				//運用更新
				Ou<CRfEditCmd_Operation>	pCommand =
					dynamic_castOu<CRfEditCmd_Operation>(pCmd);
				OnUpdate_Operation(pCommand);
				bUpdateComplete = true;
			}
			else if (dynamic_castOu<CRfEditCmd_DedRosenFileDataProp>(pCmd))
			{
				//CRfEditCmd_DedRosenFileDataProp
				//ダイヤのプロパティの変更は、
				//ダイヤ別名及び運用機能の変更を含むので、ウィンドウタイトルを更新します
				GetDocument()->UpdateTitle();
			}
			else
			{
				//CRfEditCmd_Eki
				//	駅の変更は、全更新が必要です。
				//CRfEditCmd_Ressyasyubetsu
				//	列車種別の変更は、全更新が必要です。
				//CRfEditCmd_DedRosenFileDataProp
				//	  路線ファイルのプロパティの変更は、
				//	フォントの変化を伴うため、全更新が必要です。
				//CRfEditCmd_Rosen
				//CRfEditCmd_RosenFileData
				//	駅を包含するオブジェクトです。これが更新された場合は、
				//	全更新が必要です。
				//CRfEditCmd_DiaProp
				//	ダイヤのプロパティの変更
				//	背景色変更の場合があるので、全更新が必要です
				//CRfEditCmd_EkiTrack2
				//　番線略称の変更の場合があるので、更新が必要です
			}
		}
		// --------------------------------
		if ( !bUpdateComplete )
		{
			//	全要素を更新
			OnUpdate_All() ;
		}
	}

	// --------------------------------
	//	列選択範囲を設定
	// --------------------------------
	{
		getCWndDcdGrid()->getCSelect()->setSelectMode( CSelect::SelectMode_XColumn ) ;
		const Mu<const CentDedRessya*>* pMuCentDedRessyaCont = getCentDedRessyaCont()->getMuPtr() ;
		getCWndDcdGrid()->getCSelect()->setColumnNumberSelectLimit(
			CdDcdZoneXy( 
				CdDcdZone( 2 , pMuCentDedRessyaCont->size() ) , 
				CdDcdZone( 0 , INT_MAX ) 
			) );
	}

	super::OnUpdate(pSender,  lHint,  pHint) ;
}

	// ********************************
	//@name メッセージハンドラ・コマンドハンドラ-CWnd
	// ********************************
void CWjkState_Ressyahensyu::
	OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	LogMsg(_T("CWjkState_Ressyahensyu::OnKeyDown %02x %d %02x") , nChar , nRepCnt , nFlags ) ;

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************

	//	フォーカスセルが新規列車位置にあるときは、
	//	「新規列車のプロパティ入力を行い、それを末尾に挿入する」という
	//	動作になります。
	bool bInsert = false ;
	CdXColSpec aXColSpec = getCWndDcdGrid()->getXColSpecOfFocus() ;
	if ( aXColSpec.getColumnType() == CdXColSpec::ColumnType_NewRessya )
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
		execJikokuhyouPropDlg( bInsert , FALSE ) ;
		m_CKeyinputSenderToModalDlg.endSend() ;
	}
	//	すでにダイアログが起動中→ダイアログボックスにメッセージを転送
	else
	{
		if ( !m_CKeyinputSenderToModalDlg.OnKeyDown( nChar , nRepCnt , nFlags ) )
		{
			super::OnKeyDown(  nChar , nRepCnt , nFlags  ) ;
		}
	}
}

void CWjkState_Ressyahensyu::
	OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	LogMsg(_T("CWjkState_Ressyahensyu::OnKeyUp %02x %d %02x") , nChar , nRepCnt , nFlags ) ;

	{
		if ( !m_CKeyinputSenderToModalDlg.OnKeyUp( nChar , nRepCnt , nFlags ) )
		{
			super::OnKeyUp(  nChar , nRepCnt , nFlags  ) ;
		}
	}
}
void CWjkState_Ressyahensyu::
	OnLButtonDblClk(UINT nFlags, CPoint point)
{
	//	フォーカスセルが新規列車位置にあるときは、
	//	「新規列車のプロパティ入力を行い、それを末尾に挿入する」という
	//	動作になります。
	bool bInsert = false ;
	CdXColSpec aXColSpec = getCWndDcdGrid()->getXColSpecOfFocus() ;
	if ( aXColSpec.getColumnType() == CdXColSpec::ColumnType_NewRessya )
	{
		bInsert = true ;
	}	

	execJikokuhyouPropDlg( bInsert , FALSE ) ;
	super::OnLButtonDblClk(  nFlags , point ) ;
}

void CWjkState_Ressyahensyu::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	LogMsg(_T("CWjkState_Ressyahensyu::OnChar %02x %d %02x") , nChar , nRepCnt , nFlags ) ;

	{
		super::OnChar( nChar, nRepCnt, nFlags ) ;
	}
}

void CWjkState_Ressyahensyu::OnWM_IME_STARTCOMPOSITION() 
{
	{
		super::OnWM_IME_STARTCOMPOSITION() ;
	}
}

// --------------------------------
int CWjkState_Ressyahensyu::
OnEditCut_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;

	Ou<EditCmd::CRfEditCmd_Ressya> pCmd ;
	Ou<EditCmd::CRfEditCmd_Ressya>* ppCmd = NULL ;
	if ( !bQueryEnable )
	{
		ppCmd = &pCmd ;
	}

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -2;
		}
	}
	if ( iRv >= 0 )
	{
		if ( !getCWndDcdGrid()->createCmd( CWndJikokuhyou::ECreateCmd_Select , ppCmd ) )
		{
			iRv = -1 ;	//	列車選択位置が正しくありません。
		}
	}
	// ****************************************************************
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		// --------------------------------
		//	削除される列車を取得
		// --------------------------------
		CentDedRessyaCont	aCentDedRessyaCont( getCentDedRessyaCont()->createEmptyCont() ) ;
		CaMui<CentDedRessya> aCaMui( &aCentDedRessyaCont ) ;
		aCaMui.insert( pCmd->getCaMuiSelect() ) ;

		// -------------------------------- 
		//	列車をクリップボードに格納
		//	『貼り付け移動量(秒)』の値は、０にします。
		// --------------------------------
		getCDiagramEditDoc()->CentDedRessyaCont_To_Cliboard( 
			aCentDedRessyaCont ) ;
		getCWndDcdGrid()->m_jikanPasteIdouryou = 0 ;
		getCWndDcdGrid()->m_jikanPasteIdouryouPrevValue = 0 ;
		getCWndDcdGrid()->m_iRessyaBangouPasteIdouryou = 0;
		getCWndDcdGrid()->m_iRessyaBangouPasteIdouryouPrevValue = 0;
		getCWndDcdGrid()->m_iGouPasteIdouryou = 0;
		getCWndDcdGrid()->m_iGouPasteIdouryouPrevValue = 0;
		
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


int CWjkState_Ressyahensyu::
OnEditCopy_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;
	Ou<EditCmd::CRfEditCmd_Ressya> pCmd ;
	Ou<EditCmd::CRfEditCmd_Ressya>* ppCmd = NULL ;
	if ( !bQueryEnable )
	{
		ppCmd = &pCmd ;
	}

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -2;
		}
	}
	if ( iRv >= 0 )
	{
		if ( !getCWndDcdGrid()->createCmd( CWndJikokuhyou::ECreateCmd_Select , ppCmd ) )
		{
			iRv = -1 ;	//	列車選択位置が正しくありません。
		}
	}
	// ****************************************************************
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		// --------------------------------
		//	削除される列車を取得
		// --------------------------------
		CentDedRessyaCont	aCentDedRessyaCont( getCentDedRessyaCont()->createEmptyCont() ) ;
		CaMui<CentDedRessya> aCaMui( &aCentDedRessyaCont ) ;
		aCaMui.insert( pCmd->getCaMuiSelect() ) ;

		// -------------------------------- 
		//	列車をクリップボードに格納
		//	『貼り付け移動量(秒)』の値は、０にします。
		// --------------------------------
		getCDiagramEditDoc()->CentDedRessyaCont_To_Cliboard( 
			aCentDedRessyaCont ) ;
		getCWndDcdGrid()->m_jikanPasteIdouryou = 0 ;
		getCWndDcdGrid()->m_jikanPasteIdouryouPrevValue = 0 ;
		getCWndDcdGrid()->m_iRessyaBangouPasteIdouryou = 0;
		getCWndDcdGrid()->m_iRessyaBangouPasteIdouryouPrevValue = 0;
		getCWndDcdGrid()->m_iGouPasteIdouryou = 0;
		getCWndDcdGrid()->m_iGouPasteIdouryouPrevValue = 0;
		
		// -------------------------------- 
		//	フォーカスセルを、選択列車中で最大の列車Indexの次位に移動
		// --------------------------------
		{
			//	フォーカスセルの移動によるセル選択を無効化します。
			CPropStack	aPropStack( getCWndDcdGrid() ) ;
			aPropStack.CSelect_setSelectMode( CSelect::SelectMode_NONE ) ;
		
			int iRessyaIndexMax = -1 ;
			{
				CaMuiSelect<CentDedRessya>* pCaMuiSelect = pCmd->getCaMuiSelect() ;
				for ( int iRessyaIndex = pCaMuiSelect->getAdapteeMu()->size() - 1  ; 
					iRessyaIndexMax == -1 && iRessyaIndex >= 0 ; iRessyaIndex -- )
				{
					if ( pCaMuiSelect->getSelect( iRessyaIndex ) )
					{
						iRessyaIndexMax = iRessyaIndex + pCmd->getIndexDst() ;
					}
				}
			}
			//iRessyaIndexMax = 選択されている列車のうち、最大のIndex
			
			int iXColumnNumber = -1 ;
			{
				CdXColSpecCont aCdXColSpecCont = getCWndDcdGrid()->createXColSpecCont() ;
				iXColumnNumber = aCdXColSpecCont.ColumnNumberFromSpec( CdXColSpec( 
								CdXColSpec::ColumnType_Ressya , 
								iRessyaIndexMax ) ) + 1 ;
			}
			//iXColumnNumber = 選択されている列車のうち、最大のIndexの列車の右の列番号
			//	これが、次のフォーカスセルの列番号になります。

			int iYColumnNmber = -1 ;
			{
				CDcdGridCell* pCDcdGridCell = getCWndDcdGrid()->getCFocus()->getFocusCell() ;
				if ( pCDcdGridCell != NULL )
				{
					iYColumnNmber = getCWndDcdGrid()->getCXDcdGrid()->getYColumnNumberOfCell( pCDcdGridCell ) ;
				}
			}
			//iYColumnNmber = 現在のフォーカスセル。次のフォーカスセルも同じ位置になります。

			{
				CDcdGridCell* pCDcdGridCellNew = getCWndDcdGrid()->getCXDcdGrid()->getCell( 
					iXColumnNumber , iYColumnNmber ) ; 
				if ( pCDcdGridCellNew != NULL ){
					getCWndDcdGrid()->getCFocus()->setFocusCell( pCDcdGridCellNew ) ;
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

int CWjkState_Ressyahensyu::
OnEditPaste_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;
	int iType = -1;
	Ou<EditCmd::CRfEditCmd_Ressya> pCmd ;
	Ou<EditCmd::CRfEditCmd_Ressya>* ppCmd = NULL ;
	if ( !bQueryEnable )
	{
		ppCmd = &pCmd ;
	}

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -1;
		}
	}

	if (iRv >= 0 && iType == -1)
	{
		if (getCDiagramEditDoc()->
			CentDedRessyaCont_IsClipboardFormatAvailable() ||
			getCDiagramEditDoc()->
			UnicodeText_IsClipboardFormatAvailable())
		{
			iType = 0;
		}
		else if (getCDiagramEditDoc()->
			CentDedOperation_IsClipboardFormatAvailable())
		{
			iType = 1;
			iRv = OnEditOperationPaste_Process(TRUE);
		}
		else if (getCDiagramEditDoc()->
			RessyaJouhou_IsClipboardFormatAvailable())
		{
			iType = 2;
			iRv = OnEditRessyaJouhouPaste_Process(TRUE);
		}
		else
		{
			iRv = -2;	//	クリップボードにデータがありません。
		}
	}

	if ( iRv >= 0 && iType == 0)
	{
		if ( !getCWndDcdGrid()->createCmd( CWndJikokuhyou::ECreateCmd_NewItem , ppCmd ) )
		{
			iRv = -3 ;	//	列車選択位置が正しくありません。
		}
	}
	// ****************************************************************
	if ( !bQueryEnable && iRv >= 0 && iType == 0)
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		// --------------------------------
		//	クリップボードから列車を取得
		// --------------------------------
		CentDedRessyaCont	aCentDedRessyaCont(
			getCentDedRessyaCont()->createEmptyCont());
		iRv = getCDiagramEditDoc()->CentDedRessyaCont_From_Cliboard(
			&aCentDedRessyaCont);
		//aCentDedRessyaCont = クリップボード内の列車

		if (iRv >= 0 && aCentDedRessyaCont.size() > 0)
		{
			// --------------------------------
			//	貼り付ける列車に移動量を加算・番線Index、路線外発着駅Indexの補正を行う
			// --------------------------------
			{
				CdDedJikan	aCdDedJikan = getCWndDcdGrid()->m_jikanPasteIdouryouPrevValue +
					getCWndDcdGrid()->m_jikanPasteIdouryou;
				int	iShiftRessyaBangou = getCWndDcdGrid()->m_iRessyaBangouPasteIdouryouPrevValue +
					getCWndDcdGrid()->m_iRessyaBangouPasteIdouryou;
				int	iShiftGou = getCWndDcdGrid()->m_iGouPasteIdouryouPrevValue +
					getCWndDcdGrid()->m_iGouPasteIdouryou;


				int iInsertIndex;
				for (iInsertIndex = 0; iInsertIndex < aCentDedRessyaCont.size();
					iInsertIndex++)
				{
					CentDedRessya* pCentDedRessya =
						aCentDedRessyaCont.getMuPtr()->get(iInsertIndex);
					pCentDedRessya->modifyRessyaJikoku(
						aCdDedJikan,
						CdDedJikokuOrder(0, CdDedJikokuOrder::EkiJikokuItem_Chaku));
					pCentDedRessya->modifyRessyaBangou(
						iShiftRessyaBangou);
					pCentDedRessya->modifyGou(
						iShiftGou);

					const Mu< CentDedEkiCont::CdDedEki>* pCdDedEkiCont = getCDiagramEditDoc()->getCDedRosenFileData()
						->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(getRessyahoukou());
					for (int iEkiOrder = 0; iEkiOrder < pCentDedRessya->getCentDedEkiJikokuCount() && iEkiOrder < pCdDedEkiCont->size(); iEkiOrder++)
					{
						//作業の内容が、駅設定に合致しているかをチェックします。
						//入換番線が、駅番線数内に収まっているか。路線外発着駅Indexが、路線外発着駅数内に収まっているか。
						//路線外発着駅がない場合は、作業を出区に変更します。

						const CentDedEkiCont::CdDedEki aCdDedEki = pCdDedEkiCont->get(iEkiOrder);
						int iEkiTrackCount = aCdDedEki.getCentDedEkiTrack2Cont().size();
						int iOuterTerminalCount = aCdDedEki.getOuterTerminalEkimeiCount();

						CentDedEkiJikoku* pCentDedEkiJikoku = pCentDedRessya->getCentDedEkiJikokuCont()->getMuPtr()->get(iEkiOrder);

						if (pCentDedEkiJikoku->getRessyaTrackIndex() >= iEkiTrackCount)
						{
							pCentDedEkiJikoku->setRessyaTrackIndex(aCdDedEki.getMainTrack());
						}
						pCentDedEkiJikoku->getCentDedBeforeOperationCont()->fixOperation(iEkiTrackCount, iOuterTerminalCount);
						pCentDedEkiJikoku->getCentDedAfterOperationCont()->fixOperation(iEkiTrackCount, iOuterTerminalCount);
					}

					pCentDedRessya->adjustOperation();
				}
			}
			//{
			//	int iInsertIndex;
			//	for (iInsertIndex = 0; iInsertIndex < aCentDedRessyaCont.size();
			//		iInsertIndex++)
			//	{
			//		CentDedRessya* pCentDedRessya =
			//			aCentDedRessyaCont.getMuPtr()->get(iInsertIndex);
			//	}
			//}
			// --------------------------------
			//	貼り付け移動量(秒)を追加
			// --------------------------------
			getCWndDcdGrid()->m_jikanPasteIdouryouPrevValue +=
				getCWndDcdGrid()->m_jikanPasteIdouryou;
			getCWndDcdGrid()->m_iRessyaBangouPasteIdouryouPrevValue +=
				getCWndDcdGrid()->m_iRessyaBangouPasteIdouryou;
			getCWndDcdGrid()->m_iGouPasteIdouryouPrevValue +=
				getCWndDcdGrid()->m_iGouPasteIdouryou;
			// --------------------------------
			//	コマンドオブジェクトの列車を編集
			// --------------------------------
			{
				//	CWndJikokuhyou::ECreateCmd_NewTrain によって生成された
				//	新規アイテムは削除します。
				pCmd->getCaMuiSelect()->erase(0, INT_MAX);

				//	コマンドにクリップボードからのアイテムを追加します。
				CaMui<CentDedRessya> aCaMui(pCmd->getCaMuiSelect());
				aCaMui.insert(&aCentDedRessyaCont, 0, INT_MAX, 0);
			}
			// --------------------------------
			//	コマンドオブジェクトを実行
			// --------------------------------
			{
				getCDiagramEditDoc()->executeEditCmd(pCmd);
			}
		}

	}
	else if (!bQueryEnable && iRv >= 0 && iType == 1)
	{
		iRv = OnEditOperationPaste_Process(FALSE);
	}
	else if (!bQueryEnable && iRv >= 0 && iType == 2)
	{
	iRv = OnEditRessyaJouhouPaste_Process(FALSE);
	}
	return iRv ;

}

int CWjkState_Ressyahensyu::
OnEditOperationPaste_Process(BOOL bQueryEnable)
{
	int iRv = 0;
	Ou<EditCmd::CRfEditCmd_Ressya> pCmd;
	Ou<EditCmd::CRfEditCmd_Ressya>* ppCmd = NULL;
	if (!bQueryEnable)
	{
		ppCmd = &pCmd;
	}

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -2;
		}
	}
	if (iRv >= 0)
	{
		if (!getCWndDcdGrid()->createCmd(CWndJikokuhyou::ECreateCmd_Select, ppCmd))
		{
			iRv = -1;	//	列車選択位置が正しくありません。
		}
	}
	if (iRv >= 0)
	{
		if (!getCDiagramEditDoc()->
			CentDedOperation_IsClipboardFormatAvailable())
		{
			iRv = -2;	//	クリップボードにデータがありません。
		}
	}
	// ****************************************************************
	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		// --------------------------------
		//	クリップボードから駅作業を取得
		// --------------------------------
		CentDedEkiJikoku aCentDedEkiJikokuBase;
		bool bSyubetsuChange = false;
		int iEkiOrder;
		getCDiagramEditDoc()->CentDedOperation_From_Cliboard(
			aCentDedEkiJikokuBase,
			bSyubetsuChange,
			iEkiOrder);

		if (iEkiOrder >= 0 &&
			iEkiOrder < getCDiagramEditDoc()->getCDedRosenFileData()
			->getCentDedRosen()->getCentDedEkiCont()->size())
		{
			// --------------------------------
			//	番線Index、路線外発着駅Indexの補正を行う
			// --------------------------------

			//作業の内容が、駅設定に合致しているかをチェックします。
			//入換番線が、駅番線数内に収まっているか。路線外発着駅Indexが、路線外発着駅数内に収まっているか。
			//路線外発着駅がない場合は、作業を出区に変更します。
			const CentDedEkiCont::CdDedEki aCdDedEki = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
				->getCentDedEkiCont()->getMuPtr(getRessyahoukou())->get(iEkiOrder);
			int iEkiTrackCount = aCdDedEki.getCentDedEkiTrack2Cont().size();
			int iOuterTerminalCount = aCdDedEki.getOuterTerminalEkimeiCount();

			aCentDedEkiJikokuBase.getCentDedBeforeOperationCont()->fixOperation(iEkiTrackCount, iOuterTerminalCount);

			aCentDedEkiJikokuBase.getCentDedAfterOperationCont()->fixOperation(iEkiTrackCount, iOuterTerminalCount);

			Mu<CentDedRessya*>* muCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr();
			for (int i = 0; iRv >= 0 && i < muCentDedRessya->size(); i++)
			{
				CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);

				CentDedEkiJikoku* pCentDedEkiJikoku =
					pCentDedRessya->getCentDedEkiJikokuCont()->getMuPtr()->get(iEkiOrder);

				CentDedEkiJikoku aCentDedEkiJikoku(aCentDedEkiJikokuBase);

				if (aCentDedEkiJikoku.getCentDedBeforeOperationCont()->size() > 0)
				{
					int iDifSecond = INT_MIN;
					if (!pCentDedEkiJikoku->getChakujikoku().isNull() &&
						!aCentDedEkiJikoku.getChakujikoku().isNull())
					{
						iDifSecond = pCentDedEkiJikoku->getChakujikoku().subJikoku(aCentDedEkiJikoku.getChakujikoku());
					}
					else if (!pCentDedEkiJikoku->getHatsujikoku().isNull() &&
						!aCentDedEkiJikoku.getHatsujikoku().isNull())
					{
						iDifSecond = pCentDedEkiJikoku->getHatsujikoku().subJikoku(aCentDedEkiJikoku.getHatsujikoku());
					}
					if (iDifSecond != INT_MIN)
					{
						aCentDedEkiJikoku.getCentDedBeforeOperationCont()->modifyOperationJikoku(iDifSecond);
						/**
							元の前作業に開始作業がある場合
								貼り付ける作業に開始作業がある場合は、丸ごと上書き
								ない場合は、元の作業の開始作業のみを残し、他は上書き
							元の前作業に開始作業がない場合
								貼り付ける作業における開始作業の有無にかかわらず、
								丸ごと上書きする。
								もし、開始作業があっても、adjustOperationで自動削除される。
						*/
						if (pCentDedEkiJikoku->getCentDedBeforeOperationCont()->size() > 0 &&
							pCentDedEkiJikoku->getCentDedBeforeOperationCont()->get(0).isFirstOperation() &&
							!aCentDedEkiJikoku.getCentDedBeforeOperationCont()->get(0).isFirstOperation())
						{
							/**
								元の前作業に開始作業があり、
								貼り付ける作業に開始作業がない場合。
								元の作業の開始作業のみを残し、他は上書きするが、
								元の作業の開始作業を、aCentDedEkiJikokuの先頭に挿入してから、丸ごと上書きするという方法で処理する。

							*/
							aCentDedEkiJikoku.getCentDedBeforeOperationCont()->insert(
								pCentDedEkiJikoku->getCentDedBeforeOperationCont()->get(0), 0);
						}

						pCentDedEkiJikoku->setCentDedBeforeOperationCont(*aCentDedEkiJikoku.getCentDedBeforeOperationCont());
					}
				}

				aCentDedEkiJikoku = aCentDedEkiJikokuBase;
				if (aCentDedEkiJikoku.getCentDedAfterOperationCont()->size() > 0)
				{
					int iDifSecond = INT_MIN;
					if (!pCentDedEkiJikoku->getHatsujikoku().isNull() &&
						!aCentDedEkiJikoku.getHatsujikoku().isNull())
					{
						iDifSecond = pCentDedEkiJikoku->getHatsujikoku().subJikoku(aCentDedEkiJikoku.getHatsujikoku());
					}
					else if (!pCentDedEkiJikoku->getChakujikoku().isNull() &&
						!aCentDedEkiJikoku.getChakujikoku().isNull())
					{
						iDifSecond = pCentDedEkiJikoku->getChakujikoku().subJikoku(aCentDedEkiJikoku.getChakujikoku());
					}
					if (iDifSecond != INT_MIN)
					{
						aCentDedEkiJikoku.getCentDedAfterOperationCont()->modifyOperationJikoku(iDifSecond);
						/**
							元の後作業に終了作業がある場合
								貼り付ける作業に終了作業がある場合は、丸ごと上書き
								ない場合は、元の作業の終了作業のみを残し、他は上書き
							元の後作業に終了作業がない場合
								貼り付ける作業における終了作業の有無にかかわらず、
								丸ごと上書きする。
								もし、終了作業があっても、adjustOperationで自動削除される。
						*/
						if (pCentDedEkiJikoku->getCentDedAfterOperationCont()->size() > 0 &&
							pCentDedEkiJikoku->getCentDedAfterOperationCont()->get(INT_MAX).isLastOperation() &&
							!aCentDedEkiJikoku.getCentDedAfterOperationCont()->get(INT_MAX).isLastOperation())
						{
							/**
								元の後作業に終了作業があり、
								貼り付ける作業に終了作業がない場合。
								元の作業の終了作業のみを残し、他は上書きするが、
								元の作業の終了作業を、aCentDedEkiJikokuの末尾に挿入してから、丸ごと上書きするという方法で処理する。

							*/
							aCentDedEkiJikoku.getCentDedAfterOperationCont()->insert(
								pCentDedEkiJikoku->getCentDedAfterOperationCont()->get(INT_MAX), INT_MAX);
						}

						pCentDedEkiJikoku->setCentDedAfterOperationCont(*aCentDedEkiJikoku.getCentDedAfterOperationCont());
					}
				}
				pCentDedRessya->adjustOperation();

				/**
					・貼り付け駅が有効終着駅
					・貼り付ける後作業の末尾が次列車接続(貼り付ける作業が有効終着駅のものだった)
					以上の条件を満たす場合は、クリップボードから取得した種別変更を書き込む。
				*/
				//Ver2.05 仮処理
				//if (iEkiOrder == pCentDedRessya->getValidSyuuchakuEki() &&
				//	aCentDedEkiJikoku.getCentDedAfterOperationCont()->size() > 0 &&
				//	aCentDedEkiJikoku.getCentDedAfterOperationCont()->get(INT_MAX).getAOperation() ==
				//		CentDedAfterOperation::EAOperation::AOperation_Junction)
				//{
				//	pCentDedRessya->setSyubetsuChange(bSyubetsuChange);
				//}
			}
		}

		// --------------------------------
		//	コマンドオブジェクトを実行
		// --------------------------------
		{
			getCDiagramEditDoc()->executeEditCmd(pCmd);
		}

	}
	return iRv;

}

int CWjkState_Ressyahensyu::
OnEditOperationInsert_Process(BOOL bQueryEnable)
{
	int iRv = 0;
	Ou<EditCmd::CRfEditCmd_Ressya> pCmd;
	Ou<EditCmd::CRfEditCmd_Ressya>* ppCmd = NULL;
	if (!bQueryEnable)
	{
		ppCmd = &pCmd;
	}

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -2;
		}
	}
	if (iRv >= 0)
	{
		if (!getCWndDcdGrid()->createCmd(CWndJikokuhyou::ECreateCmd_Select, ppCmd))
		{
			iRv = -1;	//	列車選択位置が正しくありません。
		}
	}
	if (iRv >= 0)
	{
		if (!getCDiagramEditDoc()->
			CentDedOperation_IsClipboardFormatAvailable())
		{
			iRv = -2;	//	クリップボードにデータがありません。
		}
	}
	// ****************************************************************
	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		// --------------------------------
		//	クリップボードから駅作業を取得
		// --------------------------------
		CentDedEkiJikoku aCentDedEkiJikokuBase;
		int iEkiOrder;
		bool bSyubetsuChange = false;
		getCDiagramEditDoc()->CentDedOperation_From_Cliboard(
			aCentDedEkiJikokuBase,
			bSyubetsuChange,
			iEkiOrder);

		if (iEkiOrder >= 0 &&
			iEkiOrder < getCDiagramEditDoc()->getCDedRosenFileData()
			->getCentDedRosen()->getCentDedEkiCont()->size())
		{
			// --------------------------------
			//	番線Index、路線外発着駅Indexの補正を行う
			// --------------------------------

			//作業の内容が、駅設定に合致しているかをチェックします。
			//入換番線が、駅番線数内に収まっているか。路線外発着駅Indexが、路線外発着駅数内に収まっているか。
			//路線外発着駅がない場合は、作業を出区に変更します。
			const CentDedEkiCont::CdDedEki aCdDedEki = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
				->getCentDedEkiCont()->getMuPtr(getRessyahoukou())->get(iEkiOrder);
			int iEkiTrackCount = aCdDedEki.getCentDedEkiTrack2Cont().size();
			int iOuterTerminalCount = aCdDedEki.getOuterTerminalEkimeiCount();

			aCentDedEkiJikokuBase.getCentDedBeforeOperationCont()->fixOperation(iEkiTrackCount, iOuterTerminalCount);

			aCentDedEkiJikokuBase.getCentDedAfterOperationCont()->fixOperation(iEkiTrackCount, iOuterTerminalCount);

			Mu<CentDedRessya*>* muCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr();
			for (int i = 0; iRv >= 0 && i < muCentDedRessya->size(); i++)
			{
				CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);

				CentDedEkiJikoku* pCentDedEkiJikoku =
					pCentDedRessya->getCentDedEkiJikokuCont()->getMuPtr()->get(iEkiOrder);

				CentDedEkiJikoku aCentDedEkiJikoku(aCentDedEkiJikokuBase);

				if (aCentDedEkiJikoku.getCentDedBeforeOperationCont()->size() > 0)
				{
					int iDifSecond = INT_MIN;
					if (!pCentDedEkiJikoku->getChakujikoku().isNull() &&
						!aCentDedEkiJikoku.getChakujikoku().isNull())
					{
						iDifSecond = pCentDedEkiJikoku->getChakujikoku().subJikoku(aCentDedEkiJikoku.getChakujikoku());
					}
					else if (!pCentDedEkiJikoku->getHatsujikoku().isNull() &&
						!aCentDedEkiJikoku.getHatsujikoku().isNull())
					{
						iDifSecond = pCentDedEkiJikoku->getHatsujikoku().subJikoku(aCentDedEkiJikoku.getHatsujikoku());
					}
					if (iDifSecond != INT_MIN)
					{
						aCentDedEkiJikoku.getCentDedBeforeOperationCont()->modifyOperationJikoku(iDifSecond);
						/**
							元の前作業に開始作業がある場合
								貼り付ける作業に開始作業がある場合は、開始作業は上書き、他は開始作業の直後に挿入
								ない場合は、元の作業の開始作業の直後に挿入
							元の前作業に開始作業がない場合
								貼り付ける作業における開始作業の有無にかかわらず、
								先頭に挿入する
								もし、開始作業があっても、adjustOperationで自動削除される。
						*/
						if (pCentDedEkiJikoku->getCentDedBeforeOperationCont()->size() > 0 &&
							pCentDedEkiJikoku->getCentDedBeforeOperationCont()->get(0).isFirstOperation() &&
							!aCentDedEkiJikoku.getCentDedBeforeOperationCont()->get(0).isFirstOperation())
						{
							/**
								元の前作業に開始作業があり、
								貼り付ける作業に開始作業がない場合。
								元の作業の開始作業の後に挿入する。
								元の作業の開始作業を、aCentDedEkiJikokuの先頭に挿入し、
								それ以外の作業を、aCentDedEkiJikokuの最後に追加し、丸ごと上書きするという方法で処理する。

							*/
							aCentDedEkiJikoku.getCentDedBeforeOperationCont()->insert(
								pCentDedEkiJikoku->getCentDedBeforeOperationCont()->get(0), 0);
							for (int idxb = 1; idxb < pCentDedEkiJikoku->getCentDedBeforeOperationCont()->size(); idxb++)
							{
								aCentDedEkiJikoku.getCentDedBeforeOperationCont()->insert(
									pCentDedEkiJikoku->getCentDedBeforeOperationCont()->get(idxb), INT_MAX);
							}
						}
						else
						{
							/**
								元の作業を、aCentDedEkiJikokuの最後に追加し、丸ごと上書きするという方法で処理する。
							*/
							for (int idxb = 0; idxb < pCentDedEkiJikoku->getCentDedBeforeOperationCont()->size(); idxb++)
							{
								aCentDedEkiJikoku.getCentDedBeforeOperationCont()->insert(
									pCentDedEkiJikoku->getCentDedBeforeOperationCont()->get(idxb), INT_MAX);
							}
						}

						pCentDedEkiJikoku->setCentDedBeforeOperationCont(*aCentDedEkiJikoku.getCentDedBeforeOperationCont());
					}
				}

				if (aCentDedEkiJikoku.getCentDedAfterOperationCont()->size() > 0)
				{
					int iDifSecond = INT_MIN;
					if (!pCentDedEkiJikoku->getHatsujikoku().isNull() &&
						!aCentDedEkiJikoku.getHatsujikoku().isNull())
					{
						iDifSecond = pCentDedEkiJikoku->getHatsujikoku().subJikoku(aCentDedEkiJikoku.getHatsujikoku());
					}
					else if (!pCentDedEkiJikoku->getChakujikoku().isNull() &&
						!aCentDedEkiJikoku.getChakujikoku().isNull())
					{
						iDifSecond = pCentDedEkiJikoku->getChakujikoku().subJikoku(aCentDedEkiJikoku.getChakujikoku());
					}
					if (iDifSecond != INT_MIN)
					{
						aCentDedEkiJikoku.getCentDedAfterOperationCont()->modifyOperationJikoku(iDifSecond);
						/**
							元の後作業に終了作業がある場合
								貼り付ける作業に終了作業がある場合は、終了作業は上書き、他は終了作業の直前に挿入
								ない場合は、元の作業の終了作業の直前に挿入
							元の後作業に終了作業がない場合
								貼り付ける作業における終了作業の有無にかかわらず、
								末尾に挿入する
								もし、終了作業があっても、adjustOperationで自動削除される。
						*/
						if (pCentDedEkiJikoku->getCentDedAfterOperationCont()->size() > 0 &&
							pCentDedEkiJikoku->getCentDedAfterOperationCont()->get(INT_MAX).isLastOperation() &&
							!aCentDedEkiJikoku.getCentDedAfterOperationCont()->get(INT_MAX).isLastOperation())
						{
							/**
								元の後作業に終了作業があり、
								貼り付ける作業に終了作業がない場合。
								元の作業の終了作業の直前に挿入する。
								元の作業の終了作業を、aCentDedEkiJikokuの末尾に追加し、
								それ以外の作業を、aCentDedEkiJikokuの先頭に挿入し、丸ごと上書きするという方法で処理する。

							*/
							aCentDedEkiJikoku.getCentDedAfterOperationCont()->insert(
								pCentDedEkiJikoku->getCentDedAfterOperationCont()->get(INT_MAX), INT_MAX);
							for (int idxa = pCentDedEkiJikoku->getCentDedAfterOperationCont()->size() - 2; idxa >= 0; idxa--)
							{
								aCentDedEkiJikoku.getCentDedAfterOperationCont()->insert(
									pCentDedEkiJikoku->getCentDedAfterOperationCont()->get(idxa), 0);
							}
						}
						else
						{
							/**
								元の作業をaCentDedEkiJikokuの先頭に挿入し、丸ごと上書きするという方法で処理する。
							*/
							for (int idxa = pCentDedEkiJikoku->getCentDedAfterOperationCont()->size() - 1; idxa >= 0; idxa--)
							{
								aCentDedEkiJikoku.getCentDedAfterOperationCont()->insert(
									pCentDedEkiJikoku->getCentDedAfterOperationCont()->get(idxa), 0);
							}
						}

						pCentDedEkiJikoku->setCentDedAfterOperationCont(*aCentDedEkiJikoku.getCentDedAfterOperationCont());
					}
				}
				pCentDedRessya->adjustOperation();

				/**
					・貼り付け駅が有効終着駅
					・貼り付ける後作業の末尾が次列車接続(貼り付ける作業が有効終着駅のものだった)
					以上の条件を満たす場合は、クリップボードから取得した種別変更を書き込む。
				*/
				//Ver2.05 仮処理
				/*if (iEkiOrder == pCentDedRessya->getValidSyuuchakuEki() &&
					aCentDedEkiJikoku.getCentDedAfterOperationCont()->size() > 0 &&
					aCentDedEkiJikoku.getCentDedAfterOperationCont()->get(INT_MAX).getAOperation() ==
					CentDedAfterOperation::EAOperation::AOperation_Junction)
				{
					pCentDedRessya->setSyubetsuChange(bSyubetsuChange);
				}*/
			}
		}

		// --------------------------------
		//	コマンドオブジェクトを実行
		// --------------------------------
		{
			getCDiagramEditDoc()->executeEditCmd(pCmd);
		}

	}
	return iRv;

}

int CWjkState_Ressyahensyu::
OnEditRessyaJouhouPaste_Process(BOOL bQueryEnable)
{
	int iRv = 0;
	Ou<EditCmd::CRfEditCmd_Ressya> pCmd;
	Ou<EditCmd::CRfEditCmd_Ressya>* ppCmd = NULL;
	if (!bQueryEnable)
	{
		ppCmd = &pCmd;
	}

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -1;
		}
	}

	if (iRv >= 0)
	{
		if (!getCWndDcdGrid()->createCmd(CWndJikokuhyou::ECreateCmd_Focus, ppCmd))
		{
			iRv = -1;	//	列車選択位置が正しくありません。
		}
	}

	if (iRv >= 0)
	{
		if (!getCDiagramEditDoc()->
			RessyaJouhou_IsClipboardFormatAvailable())
		{
			iRv = -2;	//	クリップボードにデータがありません。
		}
	}
	// ****************************************************************
	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		// --------------------------------
		//	クリップボードから列車を取得
		// --------------------------------
		CentDedRessya	aCentDedRessya =
			getCentDedRessyaCont()->createNullRessya();
		iRv = getCDiagramEditDoc()->RessyaJouhou_From_Cliboard(
			&aCentDedRessya);
		//aCentDedRessya = クリップボード内の列車

		if (iRv >= 0 && !aCentDedRessya.isNull())
		{
			// --------------------------------
			//	貼り付ける列車に移動量を加算・番線Index、路線外発着駅Indexの補正を行う
			// --------------------------------
			CentDedRessya* pCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr()->get(0);
			if(!aCentDedRessya.getRessyabangou().empty())
			{
				aCentDedRessya.modifyRessyaBangou(getCWndDcdGrid()->m_iRessyaBangouPasteIdouryouPrevValue +
					getCWndDcdGrid()->m_iRessyaBangouPasteIdouryou);
				pCentDedRessya->setRessyabangou(aCentDedRessya.getRessyabangou());
			}
			if (!aCentDedRessya.getRessyamei().empty())
			{
				pCentDedRessya->setRessyamei(aCentDedRessya.getRessyamei());
			}
			if (!aCentDedRessya.getGousuu().empty())
			{
				aCentDedRessya.modifyGou(getCWndDcdGrid()->m_iGouPasteIdouryouPrevValue +
					getCWndDcdGrid()->m_iGouPasteIdouryou);

				pCentDedRessya->setGousuu(aCentDedRessya.getGousuu());
			}
			// --------------------------------
			//	貼り付け移動量を追加
			// --------------------------------
			getCWndDcdGrid()->m_iRessyaBangouPasteIdouryouPrevValue +=
				getCWndDcdGrid()->m_iRessyaBangouPasteIdouryou;
			getCWndDcdGrid()->m_iGouPasteIdouryouPrevValue +=
				getCWndDcdGrid()->m_iGouPasteIdouryou;
			// --------------------------------
			//	コマンドオブジェクトを実行
			// --------------------------------
			{
				getCDiagramEditDoc()->executeEditCmd(pCmd);
			}
		}

		// --------------------------------
		//	フォーカスを移動
		// --------------------------------
		if (iRv >= 0)
		{
			//moveFocusCellToNext(true);
			getCWndDcdGrid()->moveFocusCellToNext(true, true);
		}
	}
	return iRv;

}

int CWjkState_Ressyahensyu::
OnEditClear_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;

	Ou<EditCmd::CRfEditCmd_Ressya> pCmd ;
	Ou<EditCmd::CRfEditCmd_Ressya>* ppCmd = NULL ;
	if ( !bQueryEnable ){	ppCmd = &pCmd ;	}

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
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -2;
		}
	}
	if ( iRv >= 0 )
	{
		if ( !getCWndDcdGrid()->createCmd( CWndJikokuhyou::ECreateCmd_Select , ppCmd ) )
		{
			iRv = -1 ;	//	列車選択位置が正しくありません。
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

int CWjkState_Ressyahensyu::OnEditOperationCopy_Process(BOOL bQueryEnable)
{
	int iRv = 0;
	Ou<EditCmd::CRfEditCmd_Ressya> pCmd;
	Ou<EditCmd::CRfEditCmd_Ressya>* ppCmd = NULL;
	if (!bQueryEnable)
	{
		ppCmd = &pCmd;
	}

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -2;
		}
	}
	if (iRv >= 0)
	{
		if (!getCWndDcdGrid()->createCmd(CWndJikokuhyou::ECreateCmd_Focus, ppCmd))
		{
			iRv = -1;	//	列車選択位置が正しくありません。
		}
	}
	CdYColSpec	aYColSpec =
		getCWndDcdGrid()->getYColSpecOfFocus();
	int iEkiOrder;
	const CentDedRessyaCont* pCentDedRessyaCont = NULL;
	pCentDedRessyaCont = getCentDedRessyaCont();
	const CentDedRessya* pCentDedRessya = NULL;
	if (iRv >= 0)
	{
		CdXColSpec aCdXColSpec = getCWndDcdGrid()->getXColSpecOfFocus();
		pCentDedRessya = pCentDedRessyaCont->getMuPtr()->get(aCdXColSpec.getRessyaIndex());
		if (pCentDedRessya->isNull())
		{
			iRv = -3;
		}
	}

	if (iRv >= 0)
	{
		if (pCentDedRessya->getValidSihatsuEki() == -1 ||
			pCentDedRessya->getValidSyuuchakuEki() == -1)
		{
			iRv = -4;
		}
	}
	if (iRv >= 0)
	{
		if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_Ekijikoku_Chaku ||
			aYColSpec.getColumnType() == CdYColSpec::ColumnType_Track ||
			aYColSpec.getColumnType() == CdYColSpec::ColumnType_Ekijikoku_Hatsu||
			aYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperation1 ||
			aYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperation2||
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
			iEkiOrder = getCWndDcdGrid()->getYColSpecOfFocus().getEkiOrder();
		}
		else if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_ShihatsuEkimei ||
			aYColSpec.getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu1 ||
			aYColSpec.getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu2 ||
			aYColSpec.getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu3 ||
			aYColSpec.getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu4 ||
			aYColSpec.getColumnType() == CdYColSpec::ColumnType_Outer_Shihatsu1 ||
			aYColSpec.getColumnType() == CdYColSpec::ColumnType_Outer_Shihatsu2)
		{
			iEkiOrder = pCentDedRessya->getValidSihatsuEki();
		}
		else if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_ShuchakuEkimei ||
			aYColSpec.getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku1 ||
			aYColSpec.getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku2 ||
			aYColSpec.getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku3 ||
			aYColSpec.getColumnType() == CdYColSpec::ColumnType_Outer_Shuchaku1 ||
			aYColSpec.getColumnType() == CdYColSpec::ColumnType_Outer_Shuchaku2)
		{
			iEkiOrder = pCentDedRessya->getValidSyuuchakuEki();
		}
		//else if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperation1 ||
		//	aYColSpec.getColumnType() == CdYColSpec::ColumnType_BeforeOperation2)
		//{
		//}
		//else if (aYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperation1 ||
		//	aYColSpec.getColumnType() == CdYColSpec::ColumnType_AfterOperation2)
		//{
		//}
		else
		{
			iRv = -5;
		}
	}
	if (iRv >= 0)
	{
		if (pCentDedRessya->getValidSihatsuEki() > iEkiOrder ||
			pCentDedRessya->getValidSyuuchakuEki() < iEkiOrder)
		{
			iRv = -6;
		}
	}

	if (iRv >= 0)
	{
		if (pCentDedRessya->getCentDedEkiJikoku(iEkiOrder).getCentDedBeforeOperationCont()->size() == 0 &&
			pCentDedRessya->getCentDedEkiJikoku(iEkiOrder).getCentDedAfterOperationCont()->size() == 0)
		{
			iRv = -7;
		}
	}
	// ****************************************************************
	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		// --------------------------------
		//	コピーする駅時刻を取得
		// --------------------------------
		CentDedEkiJikoku aCentDedEkiJikoku = pCentDedRessya->getCentDedEkiJikoku(iEkiOrder);

		// -------------------------------- 
		//	駅時刻をクリップボードに格納
		// --------------------------------
				//Ver2.05 仮処理
		getCDiagramEditDoc()->CentDedOperation_To_Cliboard(
			aCentDedEkiJikoku,
			//pCentDedRessya->getSyubetsuChange(),
			false,
			iEkiOrder);

		// -------------------------------- 
		//	フォーカスセルを、選択列車中で最大の列車Indexの次位に移動
		// --------------------------------
		//{
		//	//	フォーカスセルの移動によるセル選択を無効化します。
		//	CPropStack	aPropStack(getCWndDcdGrid());
		//	aPropStack.CSelect_setSelectMode(CSelect::SelectMode_NONE);

		//	int iRessyaIndexMax = -1;
		//	{
		//		CaMuiSelect<CentDedRessya>* pCaMuiSelect = pCmd->getCaMuiSelect();
		//		for (int iRessyaIndex = pCaMuiSelect->getAdapteeMu()->size() - 1;
		//			iRessyaIndexMax == -1 && iRessyaIndex >= 0; iRessyaIndex--)
		//		{
		//			if (pCaMuiSelect->getSelect(iRessyaIndex))
		//			{
		//				iRessyaIndexMax = iRessyaIndex + pCmd->getIndexDst();
		//			}
		//		}
		//	}
		//	//iRessyaIndexMax = 選択されている列車のうち、最大のIndex

		//	int iXColumnNumber = -1;
		//	{
		//		CdXColSpecCont aCdXColSpecCont = getCWndDcdGrid()->createXColSpecCont();
		//		iXColumnNumber = aCdXColSpecCont.ColumnNumberFromSpec(CdXColSpec(
		//			CdXColSpec::ColumnType_Ressya,
		//			iRessyaIndexMax)) + 1;
		//	}
		//	//iXColumnNumber = 選択されている列車のうち、最大のIndexの列車の右の列番号
		//	//	これが、次のフォーカスセルの列番号になります。

		//	int iYColumnNmber = -1;
		//	{
		//		CDcdGridCell* pCDcdGridCell = getCWndDcdGrid()->getCFocus()->getFocusCell();
		//		if (pCDcdGridCell != NULL)
		//		{
		//			iYColumnNmber = getCWndDcdGrid()->getCXDcdGrid()->getYColumnNumberOfCell(pCDcdGridCell);
		//		}
		//	}
		//	//iYColumnNmber = 現在のフォーカスセル。次のフォーカスセルも同じ位置になります。

		//	{
		//		CDcdGridCell* pCDcdGridCellNew = getCWndDcdGrid()->getCXDcdGrid()->getCell(
		//			iXColumnNumber, iYColumnNmber);
		//		if (pCDcdGridCellNew != NULL) {
		//			getCWndDcdGrid()->getCFocus()->setFocusCell(pCDcdGridCellNew);
		//		}
		//	}

		//}

		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv;
}



int CWjkState_Ressyahensyu::OnEditRessyaJouhouCopy_Process(BOOL bQueryEnable)
{
	int iRv = 0;
	Ou<EditCmd::CRfEditCmd_Ressya> pCmd;
	Ou<EditCmd::CRfEditCmd_Ressya>* ppCmd = NULL;
	if (!bQueryEnable)
	{
		ppCmd = &pCmd;
	}

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -2;
		}
	}
	if (iRv >= 0)
	{
		if (!getCWndDcdGrid()->createCmd(CWndJikokuhyou::ECreateCmd_Focus, ppCmd))
		{
			iRv = -1;	//	列車選択位置が正しくありません。
		}
	}
	CdYColSpec	aYColSpec =
		getCWndDcdGrid()->getYColSpecOfFocus();
	const CentDedRessyaCont* pCentDedRessyaCont = NULL;
	pCentDedRessyaCont = getCentDedRessyaCont();
	const CentDedRessya* pCentDedRessya = NULL;
	if (iRv >= 0)
	{
		CdXColSpec aCdXColSpec = getCWndDcdGrid()->getXColSpecOfFocus();
		pCentDedRessya = pCentDedRessyaCont->getMuPtr()->get(aCdXColSpec.getRessyaIndex());
		if (pCentDedRessya->isNull())
		{
			iRv = -3;
		}
	}

	//if (iRv >= 0)
	//{
	//	if (!(aYColSpec.getColumnType() == CdYColSpec::ColumnType_Ressyabangou ||
	//		aYColSpec.getColumnType() == CdYColSpec::ColumnType_Ressyamei ||
	//		aYColSpec.getColumnType() == CdYColSpec::ColumnType_Gousuu||
	//		aYColSpec.getColumnType() == CdYColSpec::ColumnType_Gou))
	//	{
	//		iRv = -5;
	//	}
	//}
	// ****************************************************************
	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************

		// -------------------------------- 
		//	列車をクリップボードに格納
		//	『貼り付け移動量(秒)』の値は、０にします。
		// --------------------------------
		getCDiagramEditDoc()->RessyaJouhou_To_Cliboard(
			pCentDedRessya);
		getCWndDcdGrid()->m_iRessyaBangouPasteIdouryou = 0;
		getCWndDcdGrid()->m_iRessyaBangouPasteIdouryouPrevValue = 0;
		getCWndDcdGrid()->m_iGouPasteIdouryou = 0;
		getCWndDcdGrid()->m_iGouPasteIdouryouPrevValue = 0;

		// -------------------------------- 
		//	駅時刻をクリップボードに格納
		// --------------------------------
				//Ver2.05 仮処理
		getCDiagramEditDoc()->RessyaJouhou_To_Cliboard(
			pCentDedRessya);

		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv;
}



int CWjkState_Ressyahensyu::
OnEditPasteEkiJikoku_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;
	int iType = -1;

	Ou<EditCmd::CRfEditCmd_Ressya> pCmd ;
	Ou<EditCmd::CRfEditCmd_Ressya>* ppCmd = NULL ;
	if ( !bQueryEnable ){	ppCmd = &pCmd ;	}

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -1;
		}
	}
	if (iRv >= 0 && iType == -1)
	{
		if (getCDiagramEditDoc()->
			CentDedRessyaCont_IsClipboardFormatAvailable())
		{
			iType = 0;
		}
		else if (getCDiagramEditDoc()->
			CentDedOperation_IsClipboardFormatAvailable())
		{
			iType = 1;
			iRv = OnEditOperationInsert_Process(TRUE);
		}
		else
		{
			iRv = -2;	//	クリップボードにデータがありません。
		}
	}
	if ( iRv >= 0 && iType == 0)
	{
		if ( !getCWndDcdGrid()->createCmd( CWndJikokuhyou::ECreateCmd_Focus , ppCmd ) )
		{
			iRv = -3 ;	//	列車選択位置が正しくありません。
		}
	}
	// ****************************************************************
	if ( !bQueryEnable && iRv >= 0 && iType == 0)
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		if (iType == 0)
		{
			// --------------------------------
			//	クリップボードから列車を取得
			// --------------------------------
			CentDedRessyaCont	aCentDedRessyaCont(
				getCentDedRessyaCont()->createEmptyCont());
			getCDiagramEditDoc()->CentDedRessyaCont_From_Cliboard(
				&aCentDedRessyaCont);
			//aCentDedRessyaCont = クリップボード内の列車

			// --------------------------------
			//	コマンドオブジェクトの列車を編集
			// --------------------------------
			{
				CentDedRessya* pCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr()->get(0);
				pCentDedRessya->pasteEkiJikoku(aCentDedRessyaCont.get(0));
			}
			// --------------------------------
			//	分岐駅の駅扱い・番線の補正
			// --------------------------------
			AdjustBrunchLoop(
				-1,
				pCmd->getCaMuiSelect()->getMuPtr()->get(0),
				0);
		}
		// --------------------------------
		//	コマンドオブジェクトを実行
		// --------------------------------
		{
			getCDiagramEditDoc()->executeEditCmd( pCmd ) ;
		}
	}
	else if (!bQueryEnable && iRv >= 0 && iType == 1)
	{
		iRv = OnEditOperationInsert_Process(FALSE);
	}
	return iRv ;	

}


int CWjkState_Ressyahensyu::OnEditSelectAll_Process( 
	BOOL bQueryEnable )
{
	int iRv = 0 ;
	Ou<EditCmd::CRfEditCmd_Ressya> pCmd ;
	Ou<EditCmd::CRfEditCmd_Ressya>* ppCmd = NULL ;
	if ( !bQueryEnable ){	ppCmd = &pCmd ;	}

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************

	// ****************************************************************
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		getCWndDcdGrid()->selectAll() ;
	}
	return iRv ;
}

// --------------------------------

int CWjkState_Ressyahensyu::
	OnJikokuhyouRessyaProp_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************

	//	フォーカスセルが新規列車位置にあるときは、
	//	「新規列車のプロパティ入力を行い、それを末尾に挿入する」という
	//	動作になります。
	bool bInsert = false ;
	CdXColSpec aXColSpec = getCWndDcdGrid()->getXColSpecOfFocus() ;
	if ( aXColSpec.getColumnType() == CdXColSpec::ColumnType_NewRessya )
	{
		bInsert = true ;
	}

	iRv = execCDlgRessyaProp( bInsert , TRUE ) ;

	//iRv = 
	// 	-	1 ;	//	列車の追加・またはプロパティの変更を行いました。
	//	-	0 ;	//	ダイアログがキャンセルで終了したため、@n
	//				変更は発生しませんでした。
	//	-	-1 ;	//	X列番号が不正です。

	// ****************************************************************
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		iRv = execCDlgRessyaProp( bInsert , FALSE ) ;
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv ;
}


int CWjkState_Ressyahensyu::
OnJikokuhyouRessyaInsert_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;
	Ou<EditCmd::CRfEditCmd_Ressya> pCmd ;
	Ou<EditCmd::CRfEditCmd_Ressya>* ppCmd = NULL ;
	if ( !bQueryEnable ){	ppCmd = &pCmd ;	}

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -2;
		}
	}
	if ( iRv >= 0 )
	{
		if ( !getCWndDcdGrid()->createCmd( CWndJikokuhyou::ECreateCmd_NewItem , ppCmd ) )
		{
			iRv = -1 ;	//	列車選択位置が正しくありません。
		}
	}
	// ****************************************************************
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		//	列車の挿入の場合は、空列車(列車種別Index=0)ではなく、
		//	NULL列車を挿入します。
		//	Command 内の列車を置き換えます。
		{
			Mu<CentDedRessya*>* pmuRessya = pCmd->getCaMuiSelect()->getMuPtr() ;
			pmuRessya->get( 0 )->setIsNull( true ) ; 
		}
		// --------------------------------
		//	コマンドオブジェクトを実行
		// --------------------------------
		{
			getCDiagramEditDoc()->executeEditCmd( pCmd ) ;
		}
	}
	return iRv ;
}


int CWjkState_Ressyahensyu::
	OnJikokuhyouFocusMoveDown_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if ( !m_bJikokuhyouFocusMoveRight )
	{
		iRv = 1 ;	//(bQueryEnable=TRUEの場合)この項目はすでに選択されています
	}
	// ****************************************************************
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		m_bJikokuhyouFocusMoveRight = false ;
		
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv ;
}

int CWjkState_Ressyahensyu::
	OnJikokuhyouFocusMoveRight_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if ( m_bJikokuhyouFocusMoveRight )
	{
		iRv = 1 ;	//(bQueryEnable=TRUEの場合)この項目はすでに選択されています
	}
	// ****************************************************************
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		m_bJikokuhyouFocusMoveRight = true ;
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv ;
}


int CWjkState_Ressyahensyu::
	OnJikokuhyouEKikanSaisyouSec_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;
	CString strErrorMessage ;
	const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont() ;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -3;
		}
	}
	CdYColSpec aCdYColSpec = getCWndDcdGrid()->getYColSpecOfFocus() ;
	if ( iRv >= 0 )
	{
		if ( !( aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_Ekijikoku_Chaku || 
				aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_Ekijikoku_Hatsu ||
				aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_Track) )
		{
			iRv = -1 ;	//	フォーカスセルの位置が不正です。
		}
	}
	if ( iRv >= 0 )
	{
		if ( !( 0 <= aCdYColSpec.getEkiOrder() 
			&& aCdYColSpec.getEkiOrder() <  pCentDedRessyaCont->getEkiCount() - 1 ) )
		{
			iRv = -2 ;	//	フォーカスセルが終着駅にある場合は実行できません。
		}
	}
	// ****************************************************************
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		int iEkikanSaisyouSecRessyaIndex = -1 ;

		pCentDedRessyaCont->findEkikanSaisyouSec( 
			aCdYColSpec.getEkiOrder() , &iEkikanSaisyouSecRessyaIndex ) ;
		
		if ( iEkikanSaisyouSecRessyaIndex >= 0 )
		{
			CdXColSpecCont aXColSpecCont 
				= getCWndDcdGrid()->createXColSpecCont() ;
			CDcdGridCell* pcellCurrent 
				= getCWndDcdGrid()->getCFocus()->getFocusCell() ;
			int iXColumnNumberNew = aXColSpecCont.ColumnNumberFromSpec( 
				CdXColSpec( 
					CdXColSpec::ColumnType_Ressya ,
					iEkikanSaisyouSecRessyaIndex ) ) ;
			int iYColumnNumberNew = getCWndDcdGrid()->getCXDcdGrid()
				->getYColumnNumberOfCell( pcellCurrent );
			
			CDcdGridCell* pcellNew 
				= getCWndDcdGrid()->getCXDcdGrid()->getCell( 
					iXColumnNumberNew , 
					iYColumnNumberNew ) ; 
			getCWndDcdGrid()->getCFocus()->setFocusCell( pcellNew ) ;
		}
		else	
		{
			const CentDedRosen* pCentDedRosen = getCDiagramEditDoc()
				->getCDedRosenFileData()->getCentDedRosen() ;
			const Mu<CentDedEkiCont::CdDedEki>* pCentDedEkiCont 
				= pCentDedRosen->getCentDedEkiCont()
					->getMuPtr( getRessyahoukou() ) ;
			CString	strFmt ;
			strFmt.LoadString( IDS_ERR_EkikanSaisyouSecIsNone ) ;
			CString strEkimei0 = pCentDedEkiCont->get( 
				aCdYColSpec.getEkiOrder() ).getEkimei().c_str() ;
			CString strEkimei1 = pCentDedEkiCont->get( 
				aCdYColSpec.getEkiOrder() + 1 ).getEkimei().c_str() ;
			CString aStr ;
			aStr.Format( strFmt , strEkimei0 , strEkimei1 ) ;
			
			strErrorMessage = aStr ;
			iRv = -21 ;	//	駅間最小所要秒数列車が決定できません。
						//	時刻が%s駅と%s駅の両方に設定された列車が１本も
						//	ありません。"
		}
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************
		if ( iRv < 0 )
		{
			switch( iRv )
			{
			case -1 :	//	フォーカスセルの位置が不正です。
			case -2 :	//	フォーカスセルが終着駅にある場合は、
						//	この機能は実行できません
			case -21 :	//	駅間最小所要秒数列車が決定できません。
				break ;
			default:
				strErrorMessage.Format( _T( "Error=%d" ) , iRv ) ;
				break ;
			}
			if ( strErrorMessage.GetLength() > 0 )
			{
				getCWndDcdGrid()->MessageBox( strErrorMessage , NULL , 
					MB_OK | MB_ICONEXCLAMATION ) ;
			}
		}
		// ****************************************************************
	}
	return iRv ;
}


int CWjkState_Ressyahensyu::
	OnJikokuhyouSort_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;
	Ou<EditCmd::CRfEditCmd_Ressya> pCmd ;
	Ou<EditCmd::CRfEditCmd_Ressya>* ppCmd = NULL ;
	if ( !bQueryEnable ){	ppCmd = &pCmd ;	}

	CdYColSpec aCdYColSpec = getCWndDcdGrid()->getYColSpecOfFocus() ;

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -2;
		}
	}
	bool bRessyasyubetsuSort = false ;
	CdDedJikokuOrder aJikokuOrder  ;
	bool bBikouSort = false ;
	bool bOperationNumberSort = false;
	bool bRessyaTrackSort = false;
	bool bRessyameiSort = false;
	bool bRessyabangouSort = false;
	if ( iRv >= 0 )
	{
		if ( !getCWndDcdGrid()->createCmd( CWndJikokuhyou::ECreateCmd_All , ppCmd ) )
		{
			iRv = -1 ;	//	列車選択位置が正しくありません。
		}
	}
	if ( iRv >= 0 )
	{
		if ( aCdYColSpec.getColumnType() == 
			CdYColSpec::ColumnType_Ressyasyubetsu)
		{
			bRessyasyubetsuSort = true ;
		}
		else if (aCdYColSpec.getColumnType() ==
			CdYColSpec::ColumnType_Ressyamei ||
			aCdYColSpec.getColumnType() ==
			CdYColSpec::ColumnType_Gousuu ||
			aCdYColSpec.getColumnType() ==
			CdYColSpec::ColumnType_Gou)
		{
			bRessyameiSort = true;
		}
		else if (aCdYColSpec.getColumnType() ==
			CdYColSpec::ColumnType_Ressyabangou)
		{
			bRessyabangouSort = true;
		}
		else if ( aCdYColSpec.getColumnType() == 
			CdYColSpec::ColumnType_Bikou )
 		{
			//	フォーカスセルが備考列にある場合は、備考でソート
			bBikouSort = true ;
		}
		else if ( aCdYColSpec.getColumnType() == 
			CdYColSpec::ColumnType_Ekijikoku_Chaku )
		{
			aJikokuOrder.setEkiOrder( aCdYColSpec.getEkiOrder() , CdDedJikokuOrder::EkiJikokuItem_Chaku ) ;
		}
		else if ( aCdYColSpec.getColumnType() == 
			CdYColSpec::ColumnType_Ekijikoku_Hatsu )
		{
			aJikokuOrder.setEkiOrder( aCdYColSpec.getEkiOrder() , CdDedJikokuOrder::EkiJikokuItem_Hatsu ) ;
		}
		else if (aCdYColSpec.getColumnType() ==
			CdYColSpec::ColumnType_OperationNumber &&
			getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getEnableOperation() > 1)
		{
			//運用番号でソート
			bOperationNumberSort = true;
		}
		else if (aCdYColSpec.getColumnType() ==
			CdYColSpec::ColumnType_Track)
		{
			//番線でソート
			bRessyaTrackSort = true;
		}
		else
		{
			iRv = -1 ;	//	フォーカスセルの位置が不正です。
		}
	}
	//bRessyasyubetsuSort = 列車種別でソートする場合はtrue ;
	//iJikokuOrder = 指定のセルに対応する『時刻Order』
	//bBikouSort = 備考でソートする場合はtrue ;

	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		CWaitCursor	aCursor ;	

		// --------------------------------
		//	対象列車を取得し、ソート用のコンテナに移動
		// --------------------------------
		CentDedRessyaCont aCentDedRessyaCont( getCentDedRessyaCont()->createEmptyCont() ) ;
		CaMui<CentDedRessya> aCaMui( &aCentDedRessyaCont ) ;
		aCaMui.insert( pCmd->getCaMuiSelect() ) ;


		// --------------------------------
		//	対象列車をソート
		// --------------------------------
		if ( bRessyasyubetsuSort )
		{
			//	列車種別でソート
			CDedRessyaSoater_Ressyasyubetsu	aSoater(getCWndDcdGrid()->getCompareBottom()) ;
			aSoater.sort( &aCentDedRessyaCont , NULL ) ;
		}
		else if (bRessyameiSort)
		{
			//	列車名でソート
			CDedRessyaSoater_Ressyamei	aSoater(getCWndDcdGrid()->getCompareBottom());
			aSoater.sort(&aCentDedRessyaCont, NULL);
		}
		else if (bRessyabangouSort)
		{
			//	列車番号でソート
			CDedRessyaSoater_Ressyabangou	aSoater(getCWndDcdGrid()->getCompareBottom());
			aSoater.sort(&aCentDedRessyaCont, NULL);
		}
		else if ( bBikouSort )
		{
			//	備考でソート
			CDedRessyaSoater_Bikou	aSoater ;
			aSoater.sort( &aCentDedRessyaCont , NULL ) ;

		}
		else if (bOperationNumberSort)
		{
			//	運用番号でソート
				//	起点時刻
			CdDedJikoku jikokuKitenJikoku = getCDiagramEditDoc()
				->getCDedRosenFileData()->getCentDedRosen()
				->getKitenJikoku();
			CDedRessyaSoater_OperationNumber	aSoater(
				jikokuKitenJikoku,
				getCWndDcdGrid()->getCompareBottom());
			aSoater.sort(&aCentDedRessyaCont, NULL);

		}
		else if (bRessyaTrackSort)
		{
			//	列車番線でソート
				//	起点時刻
			CdDedJikoku jikokuKitenJikoku = getCDiagramEditDoc()
				->getCDedRosenFileData()->getCentDedRosen()
				->getKitenJikoku();
			CDedRessyaSoater_RessyaTrack	aSoater(
				aCdYColSpec.getEkiOrder(),jikokuKitenJikoku);
			aSoater.sort(&aCentDedRessyaCont, NULL);

		}
		else
		{
			if ( getCWndDcdGrid()->getEkijikokuSort() 
				== CWndJikokuhyou::EEkijikokuSort_Ekiatsukai )
			{
				//	駅扱ソート

				//	起点時刻
				CdDedJikoku jikokuKitenJikoku = getCDiagramEditDoc()
					->getCDedRosenFileData()->getCentDedRosen()
					->getKitenJikoku() ;

				//	駅時刻でソート
				CDedRessyaSoater_Ekiatsukai	aSoater( 
					aJikokuOrder ,
					jikokuKitenJikoku ) ;

				aSoater.sort( &aCentDedRessyaCont , NULL ) ;

			}
			else if ( getCWndDcdGrid()->getEkijikokuSort() 
				== CWndJikokuhyou::EEkijikokuSort_Transfer )
			{
				//	乗継ソート

				//	進捗ダイアログの作成
				CWnd* pWndToDisable = AfxGetMainWnd() ;
				pWndToDisable->EnableWindow( FALSE ) ;

				CDlgProgress	aDlg ;
				aDlg.Create( pWndToDisable ) ;
				aDlg.ShowWindow( SW_SHOW ) ;
				aDlg.CenterWindow() ;

				//	ソートオブジェクトを生成
				CDedRessyaSoater_Transfer	aRessyaContTransferSort( 
					getCDiagramEditDoc()->getCDedRosenFileData()
						->getCentDedRosen() , 
					getCentDedDia() , 
					aJikokuOrder ,
					pCmd->getIndexDst(),
					pCmd->getSizeDst()) ;
				aRessyaContTransferSort.validate() ;

				//	乗継ソート
				aRessyaContTransferSort.sort(
					&aCentDedRessyaCont ,
					&aDlg ) ;

				pWndToDisable->EnableWindow( TRUE ) ;
				aDlg.DestroyWindow() ;
			}
		}
		// --------------------------------
		//	ソート用のコンテナの内容をコマンドオブジェクトに
		//	書き戻す
		// --------------------------------
		{
			for ( int i = 0 ; i < pCmd->getCaMuiSelect()->size() ; i ++ )
			{
				pCmd->getCaMuiSelect()->set( aCentDedRessyaCont.get( i ) , i ) ;
			}
		}
		// --------------------------------
		//	コマンドオブジェクトを実行
		// --------------------------------
		{
			getCDiagramEditDoc()->executeEditCmd( pCmd ) ;
		}
	}
	return iRv ;
}

int CWjkState_Ressyahensyu::
OnJikokuhyouUnify_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;
	Ou<EditCmd::CRfEditCmd_Ressya> pCmd ;
	Ou<EditCmd::CRfEditCmd_Ressya>* ppCmd = NULL ;
	if ( !bQueryEnable ){	ppCmd = &pCmd ;	}

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -2;
		}
	}
	if ( iRv >= 0 )
	{
		if ( !getCWndDcdGrid()->createCmd( CWndJikokuhyou::ECreateCmd_All , ppCmd ) )
		{
			iRv = -1 ;	//	列車選択位置が正しくありません。
		}
	}
	CdYColSpec	aCdYColSpec ;
	if ( iRv >= 0 )
	{
		aCdYColSpec = getCWndDcdGrid()->getYColSpecOfFocus() ;
		if ( !aCdYColSpec.isEkiJikoku() &&
			aCdYColSpec.getColumnType() != CdYColSpec::ColumnType_Track)
		{
			iRv = -1 ;	//	セルの位置が、特定の列車の特定の時刻の場所ではない。
		}
	}
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		CWaitCursor	aCursor ;	
		// --------------------------------
		//	コマンドオブジェクトの列車を編集
		// --------------------------------
		{
			//	進捗ダイアログの作成
			CWnd* pWndToDisable = AfxGetMainWnd() ;
			pWndToDisable->EnableWindow( FALSE ) ;
			CDlgProgress	aDlg ;
			aDlg.Create( pWndToDisable ) ;
			aDlg.ShowWindow( SW_SHOW ) ;
			aDlg.CenterWindow() ;

			//	編集操作を実行
			{
				Mui<CentDedRessya>* muCentDedRessya = 
					pCmd->getCaMuiSelect() ;
				entDed::CRessyaContUnifier	aUnifier ;
				aUnifier.unify( 
					muCentDedRessya ,
					getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont(),
					&aDlg ) ;
			}

			//	進捗ダイアログを閉じる
			pWndToDisable->EnableWindow( TRUE ) ;
			aDlg.DestroyWindow() ;
		}
		// --------------------------------
		//	分岐駅・環状線の駅扱い・番線の補正
		// --------------------------------
		for (int idx = 0; idx < pCmd->getCaMuiSelect()->size(); idx++)
		{
			CentDedRessya* pCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr()->get(idx);
			if (pCentDedRessya->getRessyabangou().length() == 0)
			{
				continue;
			}
			AdjustBrunchLoop(
				-1,
				pCentDedRessya,
				0);
		}
		// --------------------------------
		//	コマンドオブジェクトを実行
		// --------------------------------
		{
			getCDiagramEditDoc()->executeEditCmd( pCmd ) ;
		}
	}
	return iRv ;
}



// --------------------------------

int CWjkState_Ressyahensyu::
	OnJikokuhyouEkijikokuProp_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	//	フォーカスセルが新規列車位置にあるときは、
	//	「新規列車のプロパティ入力を行い、それを末尾に挿入する」という
	//	動作になります。
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -1;
		}
	}
	bool bInsert = false ;
	if (iRv >= 0)
	{
		CdXColSpec aXColSpec = getCWndDcdGrid()->getXColSpecOfFocus();
		if (aXColSpec.getColumnType() == CdXColSpec::ColumnType_NewRessya)
		{
			bInsert = true;
		}
		iRv = execJikokuhyouPropDlg(bInsert, TRUE);
	}

	//iRv = 
	//	-	1 ;	//	列車の追加・またはプロパティの変更を行いました。
	//	-	0 ;	//	ダイアログがキャンセルで終了したため、
	//			//	変更は発生しませんでした。
	//	-	-1 ;	//	X列番号が不正です。
	//	-	-2 ;	//	Y列番号が不正です。

	// ****************************************************************
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		iRv = execJikokuhyouPropDlg( bInsert , FALSE ) ;
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}

	return iRv ;
}

int CWjkState_Ressyahensyu::
OnJikokuhyouOperationProp_Process(BOOL bQueryEnable)
{
	int iRv = 0;

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	//	フォーカスセルが新規列車位置にあるときは、
	//	「新規列車のプロパティ入力を行い、それを末尾に挿入する」という
	//	動作になります。
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -1;
		}
	}
	bool bInsert = false;
	if (iRv >= 0)
	{
		CdXColSpec aXColSpec = getCWndDcdGrid()->getXColSpecOfFocus();
		if (aXColSpec.getColumnType() == CdXColSpec::ColumnType_NewRessya)
		{
			bInsert = true;
		}
		iRv = execAltJikokuhyouPropDlg(bInsert, TRUE);
	}

	//iRv = 
	//	-	1 ;	//	列車の追加・またはプロパティの変更を行いました。
	//	-	0 ;	//	ダイアログがキャンセルで終了したため、
	//			//	変更は発生しませんでした。
	//	-	-1 ;	//	X列番号が不正です。
	//	-	-2 ;	//	Y列番号が不正です。

	// ****************************************************************
	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		iRv = execAltJikokuhyouPropDlg(bInsert, FALSE);
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}

	return iRv;
}

int CWjkState_Ressyahensyu::
	OnJikokuhyouJikokuSakujo_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;
	Ou<EditCmd::CRfEditCmd_Ressya> pCmd ;
	Ou<EditCmd::CRfEditCmd_Ressya>* ppCmd = NULL ;
	if ( !bQueryEnable ){	ppCmd = &pCmd ;	}

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -2;
		}
	}
	if ( iRv >= 0 )
	{
		if ( !getCWndDcdGrid()->createCmd( CWndJikokuhyou::ECreateCmd_Select , ppCmd ) )
		{
			iRv = -1 ;	//	列車選択位置が正しくありません。
		}
	}
	CdYColSpec	aCdYColSpec ;
	if ( iRv >= 0 )
	{
		aCdYColSpec = getCWndDcdGrid()->getYColSpecOfFocus() ;
		if ( !aCdYColSpec.isEkiJikoku() )
		{
			iRv = -1 ;	//	セルの位置が、特定の列車の特定の時刻の場所ではない。
		}
	}
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		// --------------------------------
		//	コマンドオブジェクトの列車を編集
		// --------------------------------
		Mu<CentDedRessya*>* muCentDedRessya =  pCmd->getCaMuiSelect()->getMuPtr() ;
		for ( int i = 0 ; iRv >= 0 && i < muCentDedRessya->size() ; i++ )
		{
			CentDedRessya* pCentDedRessya = muCentDedRessya->get( i ) ;

			//	フォーカスのある時刻をNULL時刻にします。
			//
			//	これに伴って、着・発ともNULL時刻になると、駅扱は Ekiatsukai_None 
			//	になります。
			CentDedEkiJikoku aCentDedEkiJikoku =
				pCentDedRessya->getCentDedEkiJikoku( aCdYColSpec.getEkiOrder() ) ;

			if ( aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_Ekijikoku_Chaku )
			{	//	着時刻の消去
				aCentDedEkiJikoku.setChakujikoku( CdDedJikoku() ) ;
			}
			else
			{	//	発時刻の消去
				aCentDedEkiJikoku.setHatsujikoku( CdDedJikoku() ) ;
			}
			//	これに伴って、着・発ともNULL時刻になると、駅扱は Ekiatsukai_None 
			//	になります。
			if ( aCentDedEkiJikoku.getChakujikoku().isNull() && 
				aCentDedEkiJikoku.getHatsujikoku().isNull() )
			{
				aCentDedEkiJikoku.setEkiatsukai( 
					CentDedEkiJikoku::Ekiatsukai_None )	 ;

			}
			pCentDedRessya->setCentDedEkiJikoku( aCdYColSpec.getEkiOrder() , aCentDedEkiJikoku ) ;

			pCentDedRessya->adjustOperation();

			AdjustBrunchLoop(
				-1,
				pCentDedRessya,
				0);
			//ある駅を運行なしにすることによって、分岐・環状線設定に影響を及ぼす可能性があるので、
			//iEkiOrder=-1で調整を行う

		}
		// --------------------------------
		//	コマンドオブジェクトを実行
		// --------------------------------
		{
			getCDiagramEditDoc()->executeEditCmd( pCmd ) ;
		}
		// --------------------------------
		//	フォーカスを移動
		// --------------------------------
		//	着発表示で、着にフォーカスがある場合、
		//	発に移動します。
		{
			moveFocusCellToNext( false ) ;
		}
	}
	return iRv ;

}



int CWjkState_Ressyahensyu
	::OnJikokuhyouTsuuka_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;
	Ou<EditCmd::CRfEditCmd_Ressya> pCmd ;
	Ou<EditCmd::CRfEditCmd_Ressya>* ppCmd = NULL ;
	if ( !bQueryEnable ){	ppCmd = &pCmd ;	}

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -2;
		}
	}
	if ( iRv >= 0 )
	{
		if ( !getCWndDcdGrid()->createCmd( CWndJikokuhyou::ECreateCmd_Select , ppCmd ) )
		{
			iRv = -1 ;	//	列車選択位置が正しくありません。
		}
	}
	CdYColSpec	aCdYColSpec ;
	if ( iRv >= 0 )
	{
		aCdYColSpec = getCWndDcdGrid()->getYColSpecOfFocus() ;
		if ( !aCdYColSpec.isEkiJikoku() &&
			aCdYColSpec.getColumnType() != CdYColSpec::ColumnType_Track)
		{
			iRv = -1 ;	//	セルの位置が、特定の列車の特定の時刻の場所ではない。
		}
	}
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		// --------------------------------
		//	コマンドオブジェクトの列車を編集＆分岐駅・環状線の駅扱い・番線の補正
		// --------------------------------
		Mu<CentDedRessya*>* muCentDedRessya =  pCmd->getCaMuiSelect()->getMuPtr() ;

		int iEkiOrder = aCdYColSpec.getEkiOrder();
		
		for ( int i = 0 ; iRv >= 0 && i < muCentDedRessya->size() ; i++ )
		{
			CentDedRessya* pCentDedRessya = muCentDedRessya->get( i ) ;

			CentDedEkiJikoku aCentDedEkiJikoku =
				pCentDedRessya->getCentDedEkiJikoku(iEkiOrder) ;
			int iEkiAtsukaiPrev = 0;
			if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya ||
				aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka)
			{
				iEkiAtsukaiPrev = 1;
			}
			aCentDedEkiJikoku.setEkiatsukai( CentDedEkiJikoku::Ekiatsukai_Tsuuka ) ;

			//	駅時刻もNULLにする
			//	このほうが便利
			aCentDedEkiJikoku.setChakujikoku( CdDedJikoku() ) ;
			aCentDedEkiJikoku.setHatsujikoku( CdDedJikoku() ) ;

			if (iEkiAtsukaiPrev == 0)
			{
				int iStandardRessyaTrackIndex[2] = { 0,0 };
				int iRessyasyubetsuIndex = pCmd->getCaMuiSelect()->getMuPtr()->get(0)->getRessyasyubetsuIndex();
				getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
					->StandardRessyaTrackIndexSearch(
						iRessyasyubetsuIndex,
						getRessyahoukou(),
						aCdYColSpec.getEkiOrder(),
						iStandardRessyaTrackIndex);

				aCentDedEkiJikoku.setRessyaTrackIndex(iStandardRessyaTrackIndex[1]);
				//CentDedRessyaTrack aCentDedRessyaTrack =
				//	pCentDedRessya->getCentDedRessyaTrack(aCdYColSpec.getEkiOrder());
				//aCentDedRessyaTrack.setRessyaTrackIndex(iStandardRessyaTrackIndex[1]);

				//pCentDedRessya->setCentDedRessyaTrack(aCdYColSpec.getEkiOrder(), aCentDedRessyaTrack);
			}

			pCentDedRessya->setCentDedEkiJikoku(iEkiOrder, aCentDedEkiJikoku);

			pCentDedRessya->adjustOperation();

			AdjustBrunchLoop(
				iEkiOrder,
				pCentDedRessya,
				0);
			//元々停車・通過の場合は、番線の同期がとれているので、trueでもfalseでも変わらない。
			//運行無し・経由無しの場合、こちらは主本線なので、falseにし、既に番線がある場合はそちらを優先する。
			//なので、iEkiAtsukaiPrevは0で固定してしまう。
		}
		// --------------------------------
		//	コマンドオブジェクトを実行
		// --------------------------------
		{
			getCDiagramEditDoc()->executeEditCmd( pCmd ) ;
		}
		// --------------------------------
		//	フォーカスを移動
		// --------------------------------
		if ( iRv >= 0 )
		{
			moveFocusCellToNext( true ) ;
		}
	}
	return iRv ;

}



int CWjkState_Ressyahensyu::
	OnJikokuhyouTsuukateisya_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;
	Ou<EditCmd::CRfEditCmd_Ressya> pCmd ;
	Ou<EditCmd::CRfEditCmd_Ressya>* ppCmd = NULL ;
	if ( !bQueryEnable ){	ppCmd = &pCmd ;	}

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -2;
		}
	}
	if ( iRv >= 0 )
	{
		if ( !getCWndDcdGrid()->createCmd( CWndJikokuhyou::ECreateCmd_Select , ppCmd ) )
		{
			iRv = -1 ;	//	列車選択位置が正しくありません。
		}
	}
	CdYColSpec	aCdYColSpec ;
	if ( iRv >= 0 )
	{
		aCdYColSpec = getCWndDcdGrid()->getYColSpecOfFocus() ;
		if ( !aCdYColSpec.isEkiJikoku() &&
			aCdYColSpec.getColumnType() != CdYColSpec::ColumnType_Track)
		{
			iRv = -1 ;	//	セルの位置が、特定の列車の特定の時刻の場所ではない。
		}
	}
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		// --------------------------------
		//	コマンドオブジェクトの列車を編集＆分岐駅・環状線の駅扱い・番線の補正
		// --------------------------------
		Mu<CentDedRessya*>* muCentDedRessya =  pCmd->getCaMuiSelect()->getMuPtr() ;

		int iEkiOrder = aCdYColSpec.getEkiOrder();

		for ( int i = 0 ; iRv >= 0 && i < muCentDedRessya->size() ; i++ )
		{
			CentDedRessya* pCentDedRessya = muCentDedRessya->get( i ) ;
			CentDedEkiJikoku aCentDedEkiJikoku =
					pCentDedRessya->getCentDedEkiJikoku(iEkiOrder ) ;
			
			if ( aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka )
			{
				//フォーカスセルの位置が『通過』ならば『停車』に変更します。駅時刻は変更しません。
				//また、駅番線も変更しません
				aCentDedEkiJikoku.setEkiatsukai( CentDedEkiJikoku::Ekiatsukai_Teisya ) ;
			}
			else if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya)
			{
				//フォーカスセルの位置の『駅時刻』が『停車』なら、
				//『通過』に変更します。駅時刻は変更しません。
				//また、駅番線も変更しません
				aCentDedEkiJikoku.setEkiatsukai( CentDedEkiJikoku::Ekiatsukai_Tsuuka ) ;
			}
			else
			{
				//フォーカスセルの位置の『駅時刻』が『運行なし』『経由なし』なら、
				//『通過』に変更します。駅時刻は変更しません。
				//また、列車番線を、基準番線に設定します
				aCentDedEkiJikoku.setEkiatsukai(CentDedEkiJikoku::Ekiatsukai_Tsuuka);

				int iStandardRessyaTrackIndex[2] = { 0,0 };
				int iRessyasyubetsuIndex = pCmd->getCaMuiSelect()->getMuPtr()->get(0)->getRessyasyubetsuIndex();
				getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
					->StandardRessyaTrackIndexSearch(
						iRessyasyubetsuIndex,
						getRessyahoukou(),
						aCdYColSpec.getEkiOrder(),
						iStandardRessyaTrackIndex);

				aCentDedEkiJikoku.setRessyaTrackIndex(iStandardRessyaTrackIndex[1]);
				//CentDedRessyaTrack aCentDedRessyaTrack =
				//	pCentDedRessya->getCentDedRessyaTrack(aCdYColSpec.getEkiOrder());

				//aCentDedRessyaTrack.setRessyaTrackIndex(iStandardRessyaTrackIndex[1]);
				//pCentDedRessya->setCentDedRessyaTrack(aCdYColSpec.getEkiOrder(), aCentDedRessyaTrack);
			}

			pCentDedRessya->setCentDedEkiJikoku(iEkiOrder, aCentDedEkiJikoku ) ;

			pCentDedRessya->adjustOperation();

			AdjustBrunchLoop(
				iEkiOrder,
				pCentDedRessya,
				0);
			//元々停車・通過の場合は、番線の同期がとれているので、trueでもfalseでも変わらない。
			//運行無し・経由無しの場合、こちらは主本線なので、falseにし、既に番線がある場合はそちらを優先する。
			//なので、iEkiAtsukaiPrevは0で固定してしまう。
		}
		// --------------------------------
		//	コマンドオブジェクトを実行
		// --------------------------------
		{
			getCDiagramEditDoc()->executeEditCmd( pCmd ) ;
		}
		// --------------------------------
		//	フォーカスを移動
		// --------------------------------
		if ( iRv >= 0 )
		{
			moveFocusCellToNext( true ) ;
		}
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv ;
}


int CWjkState_Ressyahensyu::
	OnJikokuhyouKeiyunasi_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;
	Ou<EditCmd::CRfEditCmd_Ressya> pCmd ;
	Ou<EditCmd::CRfEditCmd_Ressya>* ppCmd = NULL ;
	if ( !bQueryEnable ){	ppCmd = &pCmd ;	}

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -2;
		}
	}
	if ( iRv >= 0 )
	{
		if ( !getCWndDcdGrid()->createCmd( CWndJikokuhyou::ECreateCmd_Select , ppCmd ) )
		{
			iRv = -1 ;	//	列車選択位置が正しくありません。
		}
	}
	CdYColSpec	aCdYColSpec ;
	if ( iRv >= 0 )
	{
		aCdYColSpec = getCWndDcdGrid()->getYColSpecOfFocus() ;
		if ( !aCdYColSpec.isEkiJikoku() &&
			aCdYColSpec.getColumnType() != CdYColSpec::ColumnType_Track)
		{
			iRv = -1 ;	//	セルの位置が、特定の列車の特定の時刻の場所ではない。
		}
	}
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		// --------------------------------
		//	コマンドオブジェクトの列車を編集＆分岐駅・環状線の駅扱い・番線の補正
		// --------------------------------
		Mu<CentDedRessya*>* muCentDedRessya =  pCmd->getCaMuiSelect()->getMuPtr() ;
		for ( int i = 0 ; iRv >= 0 && i < muCentDedRessya->size() ; i++ )
		{
			CentDedRessya* pCentDedRessya = muCentDedRessya->get( i ) ;
			CentDedEkiJikoku aCentDedEkiJikoku =
					pCentDedRessya->getCentDedEkiJikoku( aCdYColSpec.getEkiOrder() ) ;

			//Ver2.0暫定措置 駅扱いを運行なしに変更
			aCentDedEkiJikoku.setEkiatsukai( 
				CentDedEkiJikoku::Ekiatsukai_None ) ;

			pCentDedRessya->setCentDedEkiJikoku( aCdYColSpec.getEkiOrder() , aCentDedEkiJikoku ) ;

			pCentDedRessya->adjustOperation();

			AdjustBrunchLoop(
				-1,
				pCentDedRessya,
				0);
			//ある駅を経由なしにすることによって、分岐・環状線設定に影響を及ぼす可能性があるので、
			//iEkiOrder=-1で調整を行う
		}
		// --------------------------------
		//	コマンドオブジェクトを実行
		// --------------------------------
		{
			getCDiagramEditDoc()->executeEditCmd( pCmd ) ;
		}
		// --------------------------------
		//	フォーカスを移動
		// --------------------------------
		if ( iRv >= 0 )
		{
			moveFocusCellToNext( true ) ;
		}
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv ;

}


int CWjkState_Ressyahensyu::
	OnJikokuhyouSihatsu_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;
	Ou<EditCmd::CRfEditCmd_Ressya> pCmd ;
	Ou<EditCmd::CRfEditCmd_Ressya>* ppCmd = NULL ;
	if ( !bQueryEnable ){	ppCmd = &pCmd ;	}

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -2;
		}
	}
	if ( iRv >= 0 )
	{
		if ( !getCWndDcdGrid()->createCmd( CWndJikokuhyou::ECreateCmd_Select , ppCmd ) )
		{
			iRv = -1 ;	//	列車選択位置が正しくありません。
		}
	}
	CdYColSpec	aCdYColSpec ;
	if ( iRv >= 0 )
	{
		aCdYColSpec = getCWndDcdGrid()->getYColSpecOfFocus() ;
		if ( !aCdYColSpec.isEkiJikoku() &&
			aCdYColSpec.getColumnType() != CdYColSpec::ColumnType_Track)
		{
			iRv = -1 ;	//	セルの位置が、特定の列車の特定の時刻の場所ではない。
		}
	}
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		// --------------------------------
		//	コマンドオブジェクトの列車を編集
		// --------------------------------
		Mu<CentDedRessya*>* muCentDedRessya =  pCmd->getCaMuiSelect()->getMuPtr() ;
		for ( int i = 0 ; iRv >= 0 && i < muCentDedRessya->size() ; i++ )
		{
			CentDedRessya* pCentDedRessya = muCentDedRessya->get( i ) ;

			//	コンテナの列車を編集
			pCentDedRessya->setSihatsuEki(  aCdYColSpec.getEkiOrder() ) ;

		}
		// --------------------------------
		//	コマンドオブジェクトを実行
		// --------------------------------
		{
			getCDiagramEditDoc()->executeEditCmd( pCmd ) ;
		}
		// --------------------------------
		//	フォーカスを移動
		// --------------------------------
		if ( iRv >= 0 )
		{
			moveFocusCellToNext( true ) ;
		}
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv ;

}


int CWjkState_Ressyahensyu::
	OnJikokuhyouSyuuchaku_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;
	Ou<EditCmd::CRfEditCmd_Ressya> pCmd ;
	Ou<EditCmd::CRfEditCmd_Ressya>* ppCmd = NULL ;
	if ( !bQueryEnable ){	ppCmd = &pCmd ;	}

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -2;
		}
	}
	if ( iRv >= 0 )
	{
		if ( !getCWndDcdGrid()->createCmd( CWndJikokuhyou::ECreateCmd_Select , ppCmd ) )
		{
			iRv = -1 ;	//	列車選択位置が正しくありません。
		}
	}
	CdYColSpec	aCdYColSpec ;
	if ( iRv >= 0 )
	{
		aCdYColSpec = getCWndDcdGrid()->getYColSpecOfFocus() ;
		if ( !aCdYColSpec.isEkiJikoku() &&
			aCdYColSpec.getColumnType() != CdYColSpec::ColumnType_Track)
		{
			iRv = -1 ;	//	セルの位置が、特定の列車の特定の時刻の場所ではない。
		}
	}
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		// --------------------------------
		//	コマンドオブジェクトの列車を編集
		// --------------------------------
		Mu<CentDedRessya*>* muCentDedRessya =  pCmd->getCaMuiSelect()->getMuPtr() ;
		for ( int i = 0 ; iRv >= 0 && i < muCentDedRessya->size() ; i++ )
		{
			CentDedRessya* pCentDedRessya = muCentDedRessya->get( i ) ;

			//	コンテナの列車を編集
			pCentDedRessya->setSyuuchakuEki(  aCdYColSpec.getEkiOrder() ) ;

		}
		// --------------------------------
		//	コマンドオブジェクトを実行
		// --------------------------------
		{
			getCDiagramEditDoc()->executeEditCmd( pCmd ) ;
		}
		// --------------------------------
		//	フォーカスを移動
		// --------------------------------
		if ( iRv >= 0 )
		{
			moveFocusCellToNext( true ) ;
		}
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv ;
}



int CWjkState_Ressyahensyu::
	OnJikokuhyouDirect_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;
	Ou<EditCmd::CRfEditCmd_Ressya> pCmd ;
	Ou<EditCmd::CRfEditCmd_Ressya>* ppCmd = NULL ;
	if ( !bQueryEnable ){	ppCmd = &pCmd ;	}

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -2;
		}
	}
	if ( iRv >= 0 )
	{
		if ( !getCWndDcdGrid()->createCmd( CWndJikokuhyou::ECreateCmd_Focus , ppCmd ) )
		{
			iRv = -1 ;	//	列車選択位置が正しくありません。
		}
	}
	CdYColSpec	aCdYColSpec ;
	if ( iRv >= 0 )
	{
		aCdYColSpec = getCWndDcdGrid()->getYColSpecOfFocus() ;
		if ( !aCdYColSpec.isEkiJikoku() &&
			aCdYColSpec.getColumnType() != CdYColSpec::ColumnType_Track)
		{
			iRv = -1 ;	//	セルの位置が、特定の列車の特定の時刻の場所ではない。
		}
	}
	const CentDedRessyaCont* pCentDedRessyaCont = NULL ;
	const CentDedRessya* pCentDedRessya = NULL ;
	int idxRessyaSyuuchaku = -1 ;
	if ( iRv >= 0 )
	{
		pCentDedRessyaCont = getCentDedRessyaCont() ;
		CdXColSpec aCdXColSpec = getCWndDcdGrid()->getXColSpecOfFocus() ;
		idxRessyaSyuuchaku = aCdXColSpec.getRessyaIndex() ;
		pCentDedRessya = pCentDedRessyaCont->getMuPtr()->get( aCdXColSpec.getRessyaIndex() ) ;
	}

	//○途中駅止まり列車を取得　　　　　　CentDedRessyaCont
	//◇[フォーカスセルの位置が、その列車の終着駅Orderより上]→エラー
	if ( iRv >= 0 )
	{
		if ( aCdYColSpec.getEkiOrder() < pCentDedRessya->getSyuuchakuEki() )
		{
			iRv = -13;	//	セルの位置が、終着駅より上
		}
	}
	//idxRessyaSyuuchaku = フォーカスのある位置の列車
	//pCentDedRessya = フォーカスセルのある位置の列車


	//○対応する途中駅始発列車を検索      CentDedRessyaCont
	//◇[対応する列車がない]→処理終了
	int idxRessyaSihatsu = -1 ;
	if ( iRv >= 0 )
	{
		idxRessyaSihatsu = pCentDedRessyaCont->findTrainToDirect(
			idxRessyaSyuuchaku  , 
			aCdYColSpec.getEkiOrder() ) ;
		if ( idxRessyaSihatsu < 0 )
		{
			iRv = -14 ;	//	対応する始発列車が見つかりません。
		}
	}
	//idxRessyaSihatsu = 対応する始発列車のインデクス

	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		// --------------------------------
		//	コマンドオブジェクトを生成
		// --------------------------------
		if ( !getCWndDcdGrid()->createCmd( idxRessyaSyuuchaku , idxRessyaSihatsu - idxRessyaSyuuchaku + 1  , ppCmd ) )
		{
			iRv = -1 ;	//	列車選択位置が正しくありません。
		}
		// --------------------------------
		//	コマンドオブジェクト内の列車を編集＆分岐駅・環状線の駅扱い・番線の補正
		// --------------------------------
		if ( iRv >= 0 )
		{
			CentDedRessya aRessyaSyuuchaku = pCmd->getCaMuiSelect()->get( 0 ) ; 
			CentDedRessya aCentDedRessyaToDirect = pCmd->getCaMuiSelect()->get( INT_MAX ) ;
			int iResult = aRessyaSyuuchaku.direct( aCentDedRessyaToDirect ) ;
			//iResult = 
			//-	-1 ;	//	この列車には駅時刻が指定されていません。
			//-	-2 ;	//	始発列車には駅時刻が指定されていません。
			//-	-3 ;	//	aRessyaSihatsu との直通化はできません。\n
			//	//aRessyaSihatsu の始発駅は、	this の終着駅と同じか、
			//	//	それ以降でなくてはなりません。

			if ( iResult < 0 )
			{
				iRv = iResult  ;
			}
			else
			{
				pCmd->getCaMuiSelect()->set( aRessyaSyuuchaku , 0 );
				AdjustBrunchLoop(
					-1,
					pCmd->getCaMuiSelect()->getMuPtr()->get(0),
					0);
				pCmd->getCaMuiSelect()->erase( INT_MAX , 1 ); 
			}
		}
		// --------------------------------
		//	コマンドオブジェクトを実行
		// --------------------------------
		{
			getCDiagramEditDoc()->executeEditCmd( pCmd ) ;
		}
		// --------------------------------
		//	フォーカスを移動
		// --------------------------------
		if ( iRv >= 0 )
		{
			moveFocusCellToNext( true ) ;
		}

		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************
		CString strErrorMsg ;
		if ( iRv < 0 )
		{
			//switch( iRv )
			//{
			//default:
				strErrorMsg.Format( _T( "Error(%d)" ) , iRv ) ;	
			//	break ;
			//}
			if ( strErrorMsg.IsEmpty() )
			{
				getCWndDcdGrid()->MessageBox( 
					strErrorMsg , NULL , MB_ICONSTOP ) ;
			}
		}

		// ****************************************************************
	}
	return iRv ;

}

int CWjkState_Ressyahensyu::
	OnJikokuhyouUndirect_Process( BOOL bQueryEnable )

{
	int iRv = 0 ;
	Ou<EditCmd::CRfEditCmd_Ressya> pCmd ;
	Ou<EditCmd::CRfEditCmd_Ressya>* ppCmd = NULL ;
	if ( !bQueryEnable ){	ppCmd = &pCmd ;	}

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -2;
		}
	}
	if ( iRv >= 0 )
	{
		if ( !getCWndDcdGrid()->createCmd( CWndJikokuhyou::ECreateCmd_Focus , ppCmd ) )
		{
			iRv = -1 ;	//	列車選択位置が正しくありません。
		}
	}
	CdYColSpec	aCdYColSpec ;
	if ( iRv >= 0 )
	{
		aCdYColSpec = getCWndDcdGrid()->getYColSpecOfFocus() ;
		if ( !aCdYColSpec.isEkiJikoku() &&
			aCdYColSpec.getColumnType() != CdYColSpec::ColumnType_Track)
		{
			iRv = -1 ;	//	セルの位置が、特定の列車の特定の時刻の場所ではない。
		}
	}
	const CentDedRessyaCont* pCentDedRessyaCont = NULL ;
	const CentDedRessya* pCentDedRessya = NULL ;
	if ( iRv >= 0 )
	{
		pCentDedRessyaCont = getCentDedRessyaCont() ;
		CdXColSpec aCdXColSpec = getCWndDcdGrid()->getXColSpecOfFocus() ;
		pCentDedRessya = pCentDedRessyaCont->getMuPtr()->get( aCdXColSpec.getRessyaIndex() ) ;
	}

	//●メニュー[駅時刻]-[分断]
	//↓
	//○分断する列車を取得	CentDedRessyaCont
	//◇[!(その列車の始発駅Order<フォーカスセルの位置<終着駅Order)]→エラー
	if ( iRv >= 0 )
	{
		if ( !( pCentDedRessya->getSihatsuEki() < aCdYColSpec.getEkiOrder() 
			&& aCdYColSpec.getEkiOrder() < pCentDedRessya->getSyuuchakuEki()
		) )
		{
			iRv = -21 ;	//	その列車の始発駅・終着駅では分断はできません。
		}
	}
	//◇[駅時刻に着時刻も発時刻も指定されていない駅では、この機能は使用できません]→エラー
	if ( iRv >= 0 )
	{
		CentDedEkiJikoku	aCentDedEkiJikoku 
			= pCentDedRessya->getCentDedEkiJikoku( 
				aCdYColSpec.getEkiOrder() ) ;
		if ( aCentDedEkiJikoku.getChakujikoku().isNull() && 
			aCentDedEkiJikoku.getHatsujikoku().isNull() )
		{
			iRv = -22 ;	//	駅時刻に着時刻も発時刻も指定されていない駅では、この機能は使用できません
		}
	}
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		// --------------------------------
		//	コマンドオブジェクト内の列車を編集
		// --------------------------------
		CentDedRessya aRessyaSyuuchaku( getCentDedRessyaCont()->createNullRessya() ) ;
		CentDedRessya aRessyaSihatsu( getCentDedRessyaCont()->createNullRessya() ) ;
		if ( iRv >= 0 )
		{
			CentDedRessya aRessya = pCmd->getCaMuiSelect()->get( 0 ) ; 

			int iResult = pCentDedRessya->undirect( 
				aCdYColSpec.getEkiOrder() , 
				&aRessyaSyuuchaku, 
				&aRessyaSihatsu ) ;
			//iResult = 
			//	-	-1 ;	//	指定の駅Orderでは、分断はできません
			if ( iResult < 0 )
			{
				iRv = iResult - 30 ;
			}
			else
			{
				pCmd->getCaMuiSelect()->set( aRessyaSyuuchaku , 0 ) ;
				pCmd->getCaMuiSelect()->insert( aRessyaSihatsu , 1 ) ; 
			}
			//iRv = 
			//	-	-31 ;	//	指定の駅Orderでは、分断はできません
		}
		// --------------------------------
		//	コマンドオブジェクトを実行
		// --------------------------------
		if ( iRv >= 0 )
		{
			getCDiagramEditDoc()->executeEditCmd( pCmd ) ;
		}
		// --------------------------------
		//	フォーカスを移動
		// --------------------------------
		if ( iRv >= 0 ){
			moveFocusCellToNext( true ) ;
		}

		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************
		CString strErrorMsg ;
		if ( iRv < 0 )
		{
			//switch( iRv )
			//{
			//default:
				strErrorMsg.Format( _T( "Error(%d)" ) , iRv ) ;	
			//	break ;
			//}
			if ( strErrorMsg.IsEmpty() )
			{
				getCWndDcdGrid()->MessageBox( 
					strErrorMsg , NULL , MB_ICONSTOP ) ;
			}
		}
	}
	return iRv ;

}

int CWjkState_Ressyahensyu::
	OnJikokuhyouRenzoku_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -2;
		}
	}
	CWjkState* pCState = 
		getCWndDcdGrid()->getStateMachine()->getCStateContGet()->get( 
			CWndJikokuhyou::StateIdx_Renzoku ) ;
	int iResult = pCState->canEnter() ;
	if ( iResult < 0 )
	{
		iRv = -1 ;	//	現在、このコマンドは選択できません
	}
	// ****************************************************************
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		getCWndDcdGrid()->getStateMachine()->setCurrentStateIdx( 
			CWndJikokuhyou::StateIdx_Renzoku ) ;
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************
	}
	return iRv ;
}



int CWjkState_Ressyahensyu::
	OnJikokuhyouEkijikokuInsert_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;
	Ou<EditCmd::CRfEditCmd_Ressya> pCmd ;
	Ou<EditCmd::CRfEditCmd_Ressya>* ppCmd = NULL ;
	if ( !bQueryEnable ){	ppCmd = &pCmd ;	}

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************

	//Ver2.0 作業アップデートに伴い、当面無効化。
	//Ver2.2.5 仕様を調整して再実装

	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -2;
		}
	}
	if ( iRv >= 0 )
	{
		if ( !getCWndDcdGrid()->createCmd( CWndJikokuhyou::ECreateCmd_Select , ppCmd ) )
		{
			iRv = -1 ;	//	列車選択位置が正しくありません。
		}
	}
	CdYColSpec	aCdYColSpec ;
	if ( iRv >= 0 )
	{
		aCdYColSpec = getCWndDcdGrid()->getYColSpecOfFocus() ;
		if ( !aCdYColSpec.isEkiJikoku() &&
			aCdYColSpec.getColumnType() != CdYColSpec::ColumnType_Track)
		{
			iRv = -1 ;	//	セルの位置が、特定の列車の特定の時刻の場所ではない。
		}
	}
	if ( iRv >= 0 ){
		if ( !( 0 <= aCdYColSpec.getEkiOrder() && 
			aCdYColSpec.getEkiOrder() 
			< getCentDedRessyaCont()->getEkiCount() - 1 ) )
		{
			iRv = -2 ;	//	一番下の駅では、この操作はできません。
		}
	}
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		// --------------------------------
		//	コマンドオブジェクトの列車を編集&分岐駅・環状線の駅扱い・番線の補正
		// --------------------------------
		//番線は繰り下げを行わない、途中駅の作業は削除となる、繰り下げ終了後にAdjustOperationを行い、終了作業等の調整を行う。
		const CentDedRessyaCont* pCentDedRessyaCont  =  getCentDedRessyaCont() ;

		Mu<CentDedRessya*>* muCentDedRessya =  pCmd->getCaMuiSelect()->getMuPtr() ;
		for ( int i = 0 ; iRv >= 0 && i < muCentDedRessya->size() ; i++ )
		{
			CentDedRessya* pCentDedRessya = muCentDedRessya->get( i ) ;
			
			int iEkiOrderCurr = 0 ;
			for ( iEkiOrderCurr = pCentDedRessyaCont->getEkiCount() - 1 ;
					iEkiOrderCurr > aCdYColSpec.getEkiOrder() ;
					iEkiOrderCurr -- ){
				int iRessyaTrackBuffer = pCentDedRessya->getCentDedEkiJikoku(iEkiOrderCurr).getRessyaTrackIndex();
				CentDedEkiJikoku aCentDedEkiJikoku = 
					pCentDedRessya->getCentDedEkiJikoku( iEkiOrderCurr - 1 ) ;
				/**
					貼り付け元と先の駅扱いによっては、主本線(デフォルト番線)の取得が必要になります。
					元(iEkiOrderCurr - 1):先(iEkiOrderCurr)
					運行なし:運行なし　番線処理は必要ない
					運行なし:停車通過　運行なしに変わるので番線処理は必要ない
					停車通過:運行なし　停車通過に変わるので、主本線(デフォルト番線)を取得する必要がある
					停車通過:停車通過　先から取得したBufferをそのまま適用。
				*/
				if (pCentDedRessya->getCentDedEkiJikoku(iEkiOrderCurr).getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_None &&
					aCentDedEkiJikoku.getEkiatsukai() != CentDedEkiJikoku::Ekiatsukai_None)
				{
					int iStandardRessyaTrackIndex[2] = { 0,0 };

					getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
						->StandardRessyaTrackIndexSearch(
							pCentDedRessya->getRessyasyubetsuIndex(),
							getRessyahoukou(),
							iEkiOrderCurr,
							iStandardRessyaTrackIndex);
					if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya)
					{
						iRessyaTrackBuffer = iStandardRessyaTrackIndex[0];
					}
					else
					{
						iRessyaTrackBuffer = iStandardRessyaTrackIndex[1];
					}
				}
				aCentDedEkiJikoku.setRessyaTrackIndex(iRessyaTrackBuffer);
				aCentDedEkiJikoku.getCentDedBeforeOperationCont()->erase(0, INT_MAX);
				aCentDedEkiJikoku.getCentDedAfterOperationCont()->erase(0, INT_MAX);

				pCentDedRessya->setCentDedEkiJikoku( iEkiOrderCurr , 
					aCentDedEkiJikoku ) ;
			}
			CentDedEkiJikoku aCentDedEkiJikoku ;

			//挿入を行った前後の駅がともに運行なし以外の場合は、挿入した駅の駅扱いを通過にします。
			//挿入箇所が先頭駅の場合は、後の駅が運行なし以外でも、運行なしのままにします。
			if (pCentDedRessya->getCentDedEkiJikoku(iEkiOrderCurr + 1).getEkiatsukai() != CentDedEkiJikoku::Ekiatsukai_None &&
				iEkiOrderCurr != 0 &&
				pCentDedRessya->getCentDedEkiJikoku(iEkiOrderCurr - 1).getEkiatsukai() != CentDedEkiJikoku::Ekiatsukai_None)
			{
				int iStandardRessyaTrackIndex[2] = { 0,0 };

				getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
					->StandardRessyaTrackIndexSearch(
						pCentDedRessya->getRessyasyubetsuIndex(),
						getRessyahoukou(),
						iEkiOrderCurr,
						iStandardRessyaTrackIndex);
				aCentDedEkiJikoku.setRessyaTrackIndex(iStandardRessyaTrackIndex[1]);
				aCentDedEkiJikoku.setEkiatsukai(CentDedEkiJikoku::Ekiatsukai_Tsuuka);
			}
			pCentDedRessya->setCentDedEkiJikoku( iEkiOrderCurr , 
				aCentDedEkiJikoku ) ;

			pCentDedRessya->adjustOperation();

			AdjustBrunchLoop(
				-1,
				pCentDedRessya,
				0);
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
	}
	return iRv ;


}



int CWjkState_Ressyahensyu::
	OnJikokuhyouEkijikokuErase_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;
	Ou<EditCmd::CRfEditCmd_Ressya> pCmd ;
	Ou<EditCmd::CRfEditCmd_Ressya>* ppCmd = NULL ;
	if ( !bQueryEnable ){	ppCmd = &pCmd ;	}

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************

	//Ver2.0 作業アップデートに伴い、当面無効化。

	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -2;
		}
	}
	if ( iRv >= 0 )
	{
		if ( !getCWndDcdGrid()->createCmd( CWndJikokuhyou::ECreateCmd_Select , ppCmd ) )
		{
			iRv = -1 ;	//	列車選択位置が正しくありません。
		}
	}
	CdYColSpec	aCdYColSpec ;
	if ( iRv >= 0 )
	{
		aCdYColSpec = getCWndDcdGrid()->getYColSpecOfFocus() ;
		if ( !aCdYColSpec.isEkiJikoku() &&
			aCdYColSpec.getColumnType() != CdYColSpec::ColumnType_Track)
		{
			iRv = -1 ;	//	セルの位置が、特定の列車の特定の時刻の場所ではない。
		}
	}
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		// --------------------------------
		//	コマンドオブジェクトの列車を編集&分岐駅・環状線の駅扱い・番線の補正
		// --------------------------------
		//番線は繰り上げを行わない、途中駅の作業は削除となる、繰り下げ終了後にAdjustOperationを行い、終了作業等の調整を行う。
		const CentDedRessyaCont* pCentDedRessyaCont  =  getCentDedRessyaCont() ;
		const CentDedEkiCont* pCentDedEkiCont = getCDiagramEditDoc()->getCDedRosenFileData()
			->getCentDedRosen()->getCentDedEkiCont();
		Mu<CentDedRessya*>* muCentDedRessya =  pCmd->getCaMuiSelect()->getMuPtr() ;
		for ( int i = 0 ; iRv >= 0 && i < muCentDedRessya->size() ; i++ )
		{
			CentDedRessya* pCentDedRessya = muCentDedRessya->get( i ) ;

			int iEkiOrderCurr ;
			for ( iEkiOrderCurr = aCdYColSpec.getEkiOrder() ;
					iEkiOrderCurr < pCentDedRessyaCont->getEkiCount() - 1 ;
					iEkiOrderCurr ++ ){
				int iRessyaTrackBuffer = pCentDedRessya->getCentDedEkiJikoku(iEkiOrderCurr).getRessyaTrackIndex();
				CentDedEkiJikoku aCentDedEkiJikoku = 
					pCentDedRessya->getCentDedEkiJikoku( iEkiOrderCurr + 1 ) ;
				/**
					貼り付け元と先の駅扱いによっては、主本線(デフォルト番線)の取得が必要になります。
					元(iEkiOrderCurr + 1):先(iEkiOrderCurr)
					運行なし:運行なし　番線処理は必要ない
					運行なし:停車通過　運行なしに変わるので番線処理は必要ない
					停車通過:運行なし　停車通過に変わるので、主本線(デフォルト番線)を取得する必要がある
					停車通過:停車通過　先から取得したBufferをそのまま適用。
				*/
				if (pCentDedRessya->getCentDedEkiJikoku(iEkiOrderCurr).getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_None &&
					aCentDedEkiJikoku.getEkiatsukai() != CentDedEkiJikoku::Ekiatsukai_None)
				{
					int iStandardRessyaTrackIndex[2] = { 0,0 };

					getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
						->StandardRessyaTrackIndexSearch(
							pCentDedRessya->getRessyasyubetsuIndex(),
							getRessyahoukou(),
							iEkiOrderCurr,
							iStandardRessyaTrackIndex);
					if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya)
					{
						iRessyaTrackBuffer = iStandardRessyaTrackIndex[0];
					}
					else
					{
						iRessyaTrackBuffer = iStandardRessyaTrackIndex[1];
					}
				}

				aCentDedEkiJikoku.setRessyaTrackIndex(iRessyaTrackBuffer);
				aCentDedEkiJikoku.getCentDedBeforeOperationCont()->erase(0, INT_MAX);
				aCentDedEkiJikoku.getCentDedAfterOperationCont()->erase(0, INT_MAX);
				pCentDedRessya->setCentDedEkiJikoku( iEkiOrderCurr , 
					aCentDedEkiJikoku ) ;
			}
			CentDedEkiJikoku aCentDedEkiJikoku ;
			pCentDedRessya->setCentDedEkiJikoku( iEkiOrderCurr , 
				aCentDedEkiJikoku ) ;

			pCentDedRessya->adjustOperation();

			AdjustBrunchLoop(
				-1,
				pCentDedRessya,
				0);
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
	}
	return iRv ;

}
// --------------------------------
int CWjkState_Ressyahensyu::
OnJikokuhyouModifyEkijikokuCmd_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;
	Ou<EditCmd::CRfEditCmd_Ressya> pCmd ;
	Ou<EditCmd::CRfEditCmd_Ressya>* ppCmd = NULL ;
	if ( !bQueryEnable ){	ppCmd = &pCmd ;	}

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -2;
		}
	}
	if ( iRv >= 0 )
	{
		if ( !getCWndDcdGrid()->createCmd( CWndJikokuhyou::ECreateCmd_Select , ppCmd ) )
		{
			iRv = -1 ;	//	列車選択位置が正しくありません。
		}
	}
	CdDedJikokuOrder aCdJikokuOrder ;
	if ( iRv >= 0 )
	{
		aCdJikokuOrder = getCWndDcdGrid()->CdDedJikokuOrderOf( 
			getCWndDcdGrid()->getYColSpecOfFocus() ) ;
		if ( aCdJikokuOrder.getIsNull() )
		{
			iRv = -1 ;	//	セルの位置が、特定の列車の特定の時刻の場所ではない
		}
	}
	//aCdJikokuOrder = 指定のセルに対応する『時刻Order』
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		bool bRepeat = false ;
		do{
			bRepeat = false ;
			// --------------------------------
			//	ダイアログを起動
			// --------------------------------
			CDlgModifyEkijikokuOperation2 aCDlgModifyEkijikokuOperation2( 
				getCWndDcdGrid()->getEkijikokuModifyOperation2() , 
				getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->
					getCentDedEkiCont()->getMuPtr( getCWndDcdGrid()->getRessyahoukou() ) , 
				getCWndDcdGrid() ) ;
			if ( aCDlgModifyEkijikokuOperation2.DoModal() == IDOK )
			{
				getCWndDcdGrid()->setEkijikokuModifyOperation2(
					aCDlgModifyEkijikokuOperation2.getCentDedRessya_EkijikokuModifyOperation2() ) ;

				// --------------------------------
				//	駅時刻変更の動作を実行
				// --------------------------------
				int iResult = getCWndDcdGrid()->execCdModifyEkijikokuCmd(
					pCmd , 
					aCdJikokuOrder ) ;
				if  ( iResult < 0 )
				{
					//	エラーが発生した場合は、ダイアログを再度開きます。
					bRepeat = true ;
				}
				else
				{
					// --------------------------------
					//	フォーカスセルを次へ移します。
					// --------------------------------
					moveFocusCellToNext( true ) ;
				}
			}
		}	while ( bRepeat ) ;
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************
	}
	return iRv ;




}


int CWjkState_Ressyahensyu::OnJikokuhyouModifyEkijikokuCmdRepeat_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;
	Ou<EditCmd::CRfEditCmd_Ressya> pCmd ;
	Ou<EditCmd::CRfEditCmd_Ressya>* ppCmd = NULL ;
	if ( !bQueryEnable ){	ppCmd = &pCmd ;	}

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -2;
		}
	}
	if ( iRv >= 0 )
	{
		if ( !getCWndDcdGrid()->createCmd( CWndJikokuhyou::ECreateCmd_Select , ppCmd ) )
		{
			iRv = -1 ;	//	列車選択位置が正しくありません。
		}
	}
	CdDedJikokuOrder aCdJikokuOrder ;
	if ( iRv >= 0 )
	{
		aCdJikokuOrder = getCWndDcdGrid()->CdDedJikokuOrderOf( 
			getCWndDcdGrid()->getYColSpecOfFocus() ) ;
		if ( aCdJikokuOrder.getIsNull() )
		{
			iRv = -1 ;	//	セルの位置が、特定の列車の特定の時刻の場所ではない
		}
	}
	//aCdJikokuOrder = 指定のセルに対応する『時刻Order』
	if ( iRv >= 0 )
	{
		if ( getCWndDcdGrid()->getEkijikokuModifyOperation2().isNull() )
		{
			iRv = -1 ;	//	前回の「駅時刻変更」が無効です。
		}
	}

	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		{
				// --------------------------------
				//	駅時刻変更の動作を実行
				// --------------------------------
				int iResult = getCWndDcdGrid()->execCdModifyEkijikokuCmd(
					pCmd , 
					aCdJikokuOrder ) ;
				if  ( iResult >= 0 )
				{
					//	フォーカスセルを次へ移します。
					moveFocusCellToNext( true ) ;
				}
		}
	}
	return iRv ; 

}

// --------------------------------
int CWjkState_Ressyahensyu::
	OnJikokuhyouEkijikokuDec_Process( BOOL bQueryEnable, bool bAlt)
{
	int iRv = 0 ;
	Ou<EditCmd::CRfEditCmd_Ressya> pCmd ;
	Ou<EditCmd::CRfEditCmd_Ressya>* ppCmd = NULL ;
	if ( !bQueryEnable ){	ppCmd = &pCmd ;	}

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -2;
		}
	}
	if ( iRv >= 0 )
	{
		if ( !getCWndDcdGrid()->createCmd( CWndJikokuhyou::ECreateCmd_Select , ppCmd ) )
		{
			iRv = -1 ;	//	列車選択位置が正しくありません。
		}
	}
	CdDedJikokuOrder aCdJikokuOrder ;
	int iType = -1;
	int iOperationIndex = -1; 
	if ( iRv >= 0)
	{
		aCdJikokuOrder = getCWndDcdGrid()->CdDedJikokuOrderOf( 
			getCWndDcdGrid()->getYColSpecOfFocus() ) ;
		if (bAlt && !aCdJikokuOrder.getIsNull())
		{
			iType = 10;
		}
		else if (!aCdJikokuOrder.getIsNull())
		{
			iType = 0;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() ==
			CdYColSpec::ColumnType_Track)
		{
			iType = 1;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter1)
		{
			iType = 2;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter2)
		{
			iType = 3;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Outer_Shihatsu1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Outer_Shuchaku1)
		{
			iType = 4;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Outer_Shihatsu2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Outer_Shuchaku2)
		{
			iType = 5;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperation1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperation1)
		{
			iType = 6;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperation2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperation2)
		{
			iType = 7;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() ==
			CdYColSpec::ColumnType_Ressyasyubetsu)
		{
			iType = 8;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() ==
			CdYColSpec::ColumnType_Ressyabangou)
		{
			iType = 11;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() ==
			CdYColSpec::ColumnType_Gousuu)
		{
			iType = 12;
		}
		else
		{
			iRv = -1;
		}
	}
	//aCdJikokuOrder = 指定のセルに対応する『時刻Order』
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		// --------------------------------
		//	コマンドオブジェクトの列車を編集
		// --------------------------------
		if (iType == 0)
		{
			//const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont();
			Mu<CentDedRessya*>* muCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr();
			for (int i = 0; iRv >= 0 && i < muCentDedRessya->size(); i++)
			{
				CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);

				pCentDedRessya->modifyRessyaJikoku(CdDedJikan(-1 * 60),
					aCdJikokuOrder);
			}
		}
		else if (iType == 1)
		{
			ChangeRessyaTrackPrev(pCmd->getCaMuiSelect()->getMuPtr());

		}
		else if (iType == 2)
		{
			ChangeShihatsuShuchakuOperationDataPrev(
				pCmd->getCaMuiSelect()->getMuPtr());

		}
		else if (iType == 3)
		{
			ChangeShihatsuShuchakuOperationJikoku(
				pCmd->getCaMuiSelect()->getMuPtr(),
				-60);

		}
		else if (iType == 4)
		{
			ChangeShihatsuShuchakuOuterTerminalPrev(
				pCmd->getCaMuiSelect()->getMuPtr());

		}
		else if (iType == 5)
		{
			ChangeShihatsuShuchakuOuterJikoku(
				pCmd->getCaMuiSelect()->getMuPtr(),
				-60);

		}
		else if (iType == 6)
		{
			if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperation1)
			{
				ChangeOperationBeforeDataPrev(
					pCmd->getCaMuiSelect()->getMuPtr(),
					false);
			}
			else
			{
				ChangeOperationAfterDataPrev(
					pCmd->getCaMuiSelect()->getMuPtr(),
					false);
			}
		}
		else if (iType == 7)
		{
			if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperation2)
			{
				ChangeOperationBeforeJikoku(
					pCmd->getCaMuiSelect()->getMuPtr(),
					-60);
			}
			else
			{
				ChangeOperationAfterJikoku(
					pCmd->getCaMuiSelect()->getMuPtr(),
					-60);
			}
		}
		else if (iType == 8)
		{
			ChangeRessyasyubetsuPrev(pCmd->getCaMuiSelect()->getMuPtr());
		}
		else if (iType == 10)
		{
			//const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont();
			Mu<CentDedRessya*>* muCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr();
			for (int i = 0; iRv >= 0 && i < muCentDedRessya->size(); i++)
			{
				CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);

				pCentDedRessya->modifyRessyaJikokuRev(CdDedJikan(-1 * 60),
					aCdJikokuOrder);
			}
		}
		else if (iType == 11)
		{
			//const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont();
			Mu<CentDedRessya*>* muCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr();
			for (int i = 0; iRv >= 0 && i < muCentDedRessya->size(); i++)
			{
				CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);

				pCentDedRessya->modifyRessyaBangou(-1);
			}
		}
		else if (iType == 12)
		{
			//const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont();
			Mu<CentDedRessya*>* muCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr();
			for (int i = 0; iRv >= 0 && i < muCentDedRessya->size(); i++)
			{
				CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);

				pCentDedRessya->modifyGou(-1);
			}
		}
		// --------------------------------
		//	コマンドオブジェクトを実行
		// --------------------------------
		{
			getCDiagramEditDoc()->executeEditCmd( pCmd ) ;
		}
		// --------------------------------
		//	フォーカスを移動
		// --------------------------------
		if(iType == 0 || iType == 10)
		{
			moveFocusCellToNext( false ) ;
		}
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************
	}
	return iRv ;
			

}

int CWjkState_Ressyahensyu::
OnJikokuhyouEkijikokuDecNoMove_Process( BOOL bQueryEnable, bool bAlt)
{
	int iRv = 0 ;
	Ou<EditCmd::CRfEditCmd_Ressya> pCmd ;
	Ou<EditCmd::CRfEditCmd_Ressya>* ppCmd = NULL ;
	if ( !bQueryEnable ){	ppCmd = &pCmd ;	}

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -2;
		}
	}
	if ( iRv >= 0 )
	{
		if ( !getCWndDcdGrid()->createCmd( CWndJikokuhyou::ECreateCmd_Select , ppCmd ) )
		{
			iRv = -1 ;	//	列車選択位置が正しくありません。
		}
	}
	CdDedJikokuOrder aCdJikokuOrder ;
	int iType = -1;
	if ( iRv >= 0 )
	{
		aCdJikokuOrder = getCWndDcdGrid()->CdDedJikokuOrderOf( 
			getCWndDcdGrid()->getYColSpecOfFocus() ) ;
		if (bAlt && !aCdJikokuOrder.getIsNull())
		{
			iType = 10;
		}
		else if ( !aCdJikokuOrder.getIsNull() )
		{
			iType = 0;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() ==
			CdYColSpec::ColumnType_Track)
		{
			iType = 1;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter1)
		{
			iType = 2;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter2)
		{
			iType = 3;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Outer_Shihatsu1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Outer_Shuchaku1)
		{
			iType = 4;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Outer_Shihatsu2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Outer_Shuchaku2)
		{
			iType = 5;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperation1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperation1)
		{
			iType = 6;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperation2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperation2)
		{
			iType = 7;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() ==
			CdYColSpec::ColumnType_Ressyasyubetsu)
		{
			iType = 8;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() ==
			CdYColSpec::ColumnType_Ressyabangou)
		{
			iType = 11;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() ==
			CdYColSpec::ColumnType_Gousuu)
		{
			iType = 12;
		}
		else
		{
			iRv = -1;
		}
	}
	//aCdJikokuOrder = 指定のセルに対応する『時刻Order』
	if ( !bQueryEnable && iRv >= 0   )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		// --------------------------------
		//	コマンドオブジェクトの列車を編集
		// --------------------------------
		if (iType == 0)
		{
			const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont();
			Mu<CentDedRessya*>* muCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr();
			for (int i = 0; iRv >= 0 && i < muCentDedRessya->size(); i++)
			{
				CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);

				pCentDedRessya->modifyRessyaJikoku(CdDedJikan(-1 * 60),
					aCdJikokuOrder);
			}
		}
		else if (iType == 1)
		{
			ChangeRessyaTrackPrev(pCmd->getCaMuiSelect()->getMuPtr());

		}
		else if (iType == 2)
		{
			ChangeShihatsuShuchakuOperationDataPrev(
				pCmd->getCaMuiSelect()->getMuPtr());

		}
		else if (iType == 3)
		{
			ChangeShihatsuShuchakuOperationJikoku(
				pCmd->getCaMuiSelect()->getMuPtr(),
				-60);

		}
		else if (iType == 4)
		{
			ChangeShihatsuShuchakuOuterTerminalPrev(
				pCmd->getCaMuiSelect()->getMuPtr());

		}
		else if (iType == 5)
		{
			ChangeShihatsuShuchakuOuterJikoku(
				pCmd->getCaMuiSelect()->getMuPtr(),
				-60);
		}
		else if (iType == 6)
		{
			if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperation1)
			{
				ChangeOperationBeforeDataPrev(
					pCmd->getCaMuiSelect()->getMuPtr(),
					true);
			}
			else
			{
				ChangeOperationAfterDataPrev(
					pCmd->getCaMuiSelect()->getMuPtr(),
					true);
			}
		}
		else if (iType == 7)
		{
			if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperation2)
			{
				ChangeOperationBeforeJikoku(
					pCmd->getCaMuiSelect()->getMuPtr(),
					-60);
			}
			else
			{
				ChangeOperationAfterJikoku(
					pCmd->getCaMuiSelect()->getMuPtr(),
					-60);
			}
		}
		else if (iType == 8)
		{
			ChangeRessyasyubetsuPrev(pCmd->getCaMuiSelect()->getMuPtr());
		}
		else if (iType == 10)
		{
			const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont();
			Mu<CentDedRessya*>* muCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr();
			for (int i = 0; iRv >= 0 && i < muCentDedRessya->size(); i++)
			{
				CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);

				pCentDedRessya->modifyRessyaJikokuRev(CdDedJikan(-1 * 60),
					aCdJikokuOrder);
			}
		}
		else if (iType == 11)
		{
			//const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont();
			Mu<CentDedRessya*>* muCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr();
			for (int i = 0; iRv >= 0 && i < muCentDedRessya->size(); i++)
			{
				CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);

				pCentDedRessya->modifyRessyaBangou(-10);
			}
		}
		else if (iType == 12)
		{
			//const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont();
			Mu<CentDedRessya*>* muCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr();
			for (int i = 0; iRv >= 0 && i < muCentDedRessya->size(); i++)
			{
				CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);

				pCentDedRessya->modifyGou(-10);
			}
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
	}
	return iRv ;

}


int CWjkState_Ressyahensyu::
	OnJikokuhyouEkijikokuNext_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	CDcdGridCell*	pCDcdGridCell = NULL ;
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -2;
		}
	}
	if ( iRv >= 0 )
	{
		pCDcdGridCell = getCWndDcdGrid()->getCFocus()->getFocusCell() ;
		if ( pCDcdGridCell == NULL )
		{
			iRv = -11  ;	//	セルの場所が不正
		}
	}
	//pCDcdGridCell = 編集中のセル
	
	// ****************************************************************
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		// --------------------------------
		//	フォーカスを移動
		// --------------------------------
		{
			moveFocusCellToNext( false ) ;
		}
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************
	}
	return iRv ;
}



int CWjkState_Ressyahensyu::
	OnJikokuhyouEkijikokuPrev_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	CDcdGridCell*	pCDcdGridCell = NULL ;
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -2;
		}
	}
	if ( iRv >= 0 )
	{
		pCDcdGridCell = getCWndDcdGrid()->getCFocus()->getFocusCell() ;
		if ( pCDcdGridCell == NULL )
		{
			iRv = -11  ;	//	セルの場所が不正
		}
	}
	//pCDcdGridCell = 編集中のセル
	
	// ****************************************************************
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		// --------------------------------
		//	フォーカスを移動
		// --------------------------------
		{
			moveFocusCellToPrev( false ) ;
		}
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************
	}
	return iRv ;
}

int CWjkState_Ressyahensyu::
	OnJikokuhyouEkijikokuInc_Process( BOOL bQueryEnable, bool bAlt)
{
	int iRv = 0 ;
	Ou<EditCmd::CRfEditCmd_Ressya> pCmd ;
	Ou<EditCmd::CRfEditCmd_Ressya>* ppCmd = NULL ;
	if ( !bQueryEnable ){	ppCmd = &pCmd ;	}

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -2;
		}
	}
	if ( iRv >= 0 )
	{
		if ( !getCWndDcdGrid()->createCmd( CWndJikokuhyou::ECreateCmd_Select , ppCmd ) )
		{
			iRv = -1 ;	//	列車選択位置が正しくありません。
		}
	}
	CdDedJikokuOrder aCdJikokuOrder ;
	int iType = -1;
	if ( iRv >= 0 )
	{
		aCdJikokuOrder = getCWndDcdGrid()->CdDedJikokuOrderOf( 
			getCWndDcdGrid()->getYColSpecOfFocus() ) ;
		if (bAlt && !aCdJikokuOrder.getIsNull())
		{
			iType = 10;
		}
		else if (!aCdJikokuOrder.getIsNull())
		{
			iType = 0;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() ==
			CdYColSpec::ColumnType_Track)
		{
			iType = 1;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter1)
		{
			iType = 2;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter2)
		{
			iType = 3;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Outer_Shihatsu1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Outer_Shuchaku1)
		{
			iType = 4;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Outer_Shihatsu2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Outer_Shuchaku2)
		{
			iType = 5;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperation1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperation1)
		{
			iType = 6;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperation2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperation2)
		{
			iType = 7;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() ==
			CdYColSpec::ColumnType_Ressyasyubetsu)
		{
			iType = 8;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() ==
			CdYColSpec::ColumnType_Ressyabangou)
		{
			iType = 11;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() ==
			CdYColSpec::ColumnType_Gousuu)
		{
			iType = 12;
		}
		else
		{
			iRv = -1;
		}
	}
	//aCdJikokuOrder = 指定のセルに対応する『時刻Order』
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		// --------------------------------
		//	コマンドオブジェクトの列車を編集
		// --------------------------------
		if (iType == 0)
		{
			const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont();
			Mu<CentDedRessya*>* muCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr();
			for (int i = 0; iRv >= 0 && i < muCentDedRessya->size(); i++)
			{
				CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);

				pCentDedRessya->modifyRessyaJikoku(CdDedJikan(+1 * 60),
					aCdJikokuOrder);
			}
		}
		else if (iType == 1)
		{
			ChangeRessyaTrackNext(pCmd->getCaMuiSelect()->getMuPtr());

		}
		else if (iType == 2)
		{
			ChangeShihatsuShuchakuOperationDataNext(
				pCmd->getCaMuiSelect()->getMuPtr());

		}
		else if (iType == 3)
		{
			ChangeShihatsuShuchakuOperationJikoku(
				pCmd->getCaMuiSelect()->getMuPtr(),
				60);
		}
		else if (iType == 4)
		{
			ChangeShihatsuShuchakuOuterTerminalNext(
				pCmd->getCaMuiSelect()->getMuPtr());

		}
		else if (iType == 5)
		{
			ChangeShihatsuShuchakuOuterJikoku(
				pCmd->getCaMuiSelect()->getMuPtr(),
				60);
		}
		else if (iType == 6)
		{
			if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperation1)
			{
				ChangeOperationBeforeDataNext(
					pCmd->getCaMuiSelect()->getMuPtr(),
					false);
			}
			else
			{
				ChangeOperationAfterDataNext(
					pCmd->getCaMuiSelect()->getMuPtr(),
					false);
			}
		}
		else if (iType == 7)
		{
			if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperation2)
			{
				ChangeOperationBeforeJikoku(
					pCmd->getCaMuiSelect()->getMuPtr(),
					60);
			}
			else
			{
				ChangeOperationAfterJikoku(
					pCmd->getCaMuiSelect()->getMuPtr(),
					60);
			}
		}
		else if (iType == 8)
		{
			ChangeRessyasyubetsuNext(pCmd->getCaMuiSelect()->getMuPtr());
		}
		else if (iType == 10)
		{
			const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont();
			Mu<CentDedRessya*>* muCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr();
			for (int i = 0; iRv >= 0 && i < muCentDedRessya->size(); i++)
			{
				CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);

				pCentDedRessya->modifyRessyaJikokuRev(CdDedJikan(+1 * 60),
					aCdJikokuOrder);
			}
		}
		else if (iType == 11)
		{
			//const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont();
			Mu<CentDedRessya*>* muCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr();
			for (int i = 0; iRv >= 0 && i < muCentDedRessya->size(); i++)
			{
				CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);

				pCentDedRessya->modifyRessyaBangou(1);
			}
		}
		else if (iType == 12)
		{
			//const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont();
			Mu<CentDedRessya*>* muCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr();
			for (int i = 0; iRv >= 0 && i < muCentDedRessya->size(); i++)
			{
				CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);

				pCentDedRessya->modifyGou(1);
			}
		}
		// --------------------------------
		//	コマンドオブジェクトを実行
		// --------------------------------
		{
			getCDiagramEditDoc()->executeEditCmd( pCmd ) ;
		}
		// --------------------------------
		//	フォーカスを移動
		// --------------------------------
		if (iType == 0 || iType == 10)
		{
			moveFocusCellToNext( false ) ;
		}
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************
	}
	return iRv ;
}



int CWjkState_Ressyahensyu::
	OnJikokuhyouEkijikokuIncNoMove_Process( BOOL bQueryEnable, bool bAlt)
{
	int iRv = 0 ;
	Ou<EditCmd::CRfEditCmd_Ressya> pCmd ;
	Ou<EditCmd::CRfEditCmd_Ressya>* ppCmd = NULL ;
	if ( !bQueryEnable ){	ppCmd = &pCmd ;	}

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -2;
		}
	}
	if ( iRv >= 0 )
	{
		if ( !getCWndDcdGrid()->createCmd( CWndJikokuhyou::ECreateCmd_Select , ppCmd ) )
		{
			iRv = -1 ;	//	列車選択位置が正しくありません。
		}
	}
	CdDedJikokuOrder aCdJikokuOrder ;
	int iType = -1;
	if ( iRv >= 0 )
	{
		aCdJikokuOrder = getCWndDcdGrid()->CdDedJikokuOrderOf( 
			getCWndDcdGrid()->getYColSpecOfFocus() ) ;
		if (bAlt && !aCdJikokuOrder.getIsNull())
		{
			iType = 10;
		}
		else if (!aCdJikokuOrder.getIsNull())
		{
			iType = 0;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() ==
			CdYColSpec::ColumnType_Track)
		{
			iType = 1;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter1)
		{
			iType = 2;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter2)
		{
			iType = 3;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Outer_Shihatsu1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Outer_Shuchaku1)
		{
			iType = 4;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Outer_Shihatsu2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Outer_Shuchaku2)
		{
			iType = 5;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperation1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperation1)
		{
			iType = 6;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperation2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperation2)
		{
			iType = 7;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() ==
			CdYColSpec::ColumnType_Ressyasyubetsu)
		{
			iType = 8;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() ==
			CdYColSpec::ColumnType_Ressyabangou)
		{
			iType = 11;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() ==
			CdYColSpec::ColumnType_Gousuu)
		{
			iType = 12;
		}
		else
		{
			iRv = -1;
		}
	}
	//aCdJikokuOrder = 指定のセルに対応する『時刻Order』
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		// --------------------------------
		//	コマンドオブジェクトの列車を編集
		// --------------------------------
		if (iType == 0)
		{
			const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont();
			Mu<CentDedRessya*>* muCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr();
			for (int i = 0; iRv >= 0 && i < muCentDedRessya->size(); i++)
			{
				CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);

				pCentDedRessya->modifyRessyaJikoku(CdDedJikan(+1 * 60),
					aCdJikokuOrder);
			}
		}
		else if (iType == 1)
		{
			ChangeRessyaTrackNext(pCmd->getCaMuiSelect()->getMuPtr());

		}
		else if (iType == 2)
		{
			ChangeShihatsuShuchakuOperationDataNext(
				pCmd->getCaMuiSelect()->getMuPtr());

		}
		else if (iType == 3)
		{
			ChangeShihatsuShuchakuOperationJikoku(
				pCmd->getCaMuiSelect()->getMuPtr(),
				60);
		}
		else if (iType == 4)
		{
			ChangeShihatsuShuchakuOuterTerminalNext(
				pCmd->getCaMuiSelect()->getMuPtr());

		}
		else if (iType == 5)
		{
			ChangeShihatsuShuchakuOuterJikoku(
				pCmd->getCaMuiSelect()->getMuPtr(),
				60);
		}
		else if (iType == 6)
		{
			if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperation1)
			{
				ChangeOperationBeforeDataNext(
					pCmd->getCaMuiSelect()->getMuPtr(),
					true);
			}
			else
			{
				ChangeOperationAfterDataNext(
					pCmd->getCaMuiSelect()->getMuPtr(),
					true);
			}
		}
		else if (iType == 7)
		{
			if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperation2)
			{
				ChangeOperationBeforeJikoku(
					pCmd->getCaMuiSelect()->getMuPtr(),
					60);
			}
			else
			{
				ChangeOperationAfterJikoku(
					pCmd->getCaMuiSelect()->getMuPtr(),
					60);
			}
		}
		else if (iType == 8)
		{
			ChangeRessyasyubetsuNext(pCmd->getCaMuiSelect()->getMuPtr());
		}
		else if (iType == 10)
		{
			const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont();
			Mu<CentDedRessya*>* muCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr();
			for (int i = 0; iRv >= 0 && i < muCentDedRessya->size(); i++)
			{
				CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);

				pCentDedRessya->modifyRessyaJikokuRev(CdDedJikan(+1 * 60),
					aCdJikokuOrder);
			}
		}
		else if (iType == 11)
		{
			//const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont();
			Mu<CentDedRessya*>* muCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr();
			for (int i = 0; iRv >= 0 && i < muCentDedRessya->size(); i++)
			{
				CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);

				pCentDedRessya->modifyRessyaBangou(10);
			}
		}
		else if (iType == 12)
		{
			//const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont();
			Mu<CentDedRessya*>* muCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr();
			for (int i = 0; iRv >= 0 && i < muCentDedRessya->size(); i++)
			{
				CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);

				pCentDedRessya->modifyGou(10);
			}
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
	}
	return iRv ;
			
			

}

//ここからchange_by_d_mania

int CWjkState_Ressyahensyu::
OnJikokuhyouEkijikokuDecAnySecNoMove_Process( BOOL bQueryEnable, bool bAlt)
{
	int iRv = 0 ;
	Ou<EditCmd::CRfEditCmd_Ressya> pCmd ;
	Ou<EditCmd::CRfEditCmd_Ressya>* ppCmd = NULL ;
	if ( !bQueryEnable ){	ppCmd = &pCmd ;	}

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -2;
		}
	}
	if ( iRv >= 0 )
	{
		if ( !getCWndDcdGrid()->createCmd( CWndJikokuhyou::ECreateCmd_Select , ppCmd ) )
		{
			iRv = -1 ;	//	列車選択位置が正しくありません。
		}
	}
	CdDedJikokuOrder aCdJikokuOrder ;
	int iType = -1;
	if ( iRv >= 0 )
	{
		aCdJikokuOrder = getCWndDcdGrid()->CdDedJikokuOrderOf( 
			getCWndDcdGrid()->getYColSpecOfFocus() ) ;
		if (bAlt && !aCdJikokuOrder.getIsNull())
		{
			iType = 10;
		}
		else if (!aCdJikokuOrder.getIsNull())
		{
			iType = 0;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() ==
			CdYColSpec::ColumnType_Track)
		{
			iType = 1;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter1)
		{
			iType = 2;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter2)
		{
			iType = 3;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Outer_Shihatsu1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Outer_Shuchaku1)
		{
			iType = 4;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Outer_Shihatsu2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Outer_Shuchaku2)
		{
			iType = 5;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperation1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperation1)
		{
			iType = 6;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperation2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperation2)
		{
			iType = 7;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() ==
			CdYColSpec::ColumnType_Ressyasyubetsu)
		{
			iType = 8;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() ==
			CdYColSpec::ColumnType_Ressyabangou)
		{
			iType = 11;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() ==
			CdYColSpec::ColumnType_Gousuu)
		{
			iType = 12;
		}
		else
		{
			iRv = -1;
		}
	}
	//aCdJikokuOrder = 指定のセルに対応する『時刻Order』
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		// --------------------------------
		//	コマンドオブジェクトの列車を編集
		// --------------------------------
		if (iType == 0)
		{
			const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont();
			Mu<CentDedRessya*>* muCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr();
			for (int i = 0; iRv >= 0 && i < muCentDedRessya->size(); i++)
			{
				CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);

				//17.4.15 任意秒対応化_by_d_mania
				CdDedDispProp aCdDedDispProp = getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
				pCentDedRessya->modifyRessyaJikoku(CdDedJikan(-1 * aCdDedDispProp.getAnySecondIncDec1()),
					aCdJikokuOrder);
			}
		}
		else if (iType == 1)
		{
			ChangeRessyaTrackPrev(pCmd->getCaMuiSelect()->getMuPtr());
		}
		else if (iType == 2)
		{
			ChangeShihatsuShuchakuOperationTypePrev(
				pCmd->getCaMuiSelect()->getMuPtr());

		}
		else if (iType == 3)
		{
			CdDedDispProp aCdDedDispProp = getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
			ChangeShihatsuShuchakuOperationJikoku(
				pCmd->getCaMuiSelect()->getMuPtr(),
				-(aCdDedDispProp.getAnySecondIncDec1()));
		}
		else if (iType == 4)
		{
			ChangeShihatsuShuchakuOuterTerminalPrev(
				pCmd->getCaMuiSelect()->getMuPtr());

		}
		else if (iType == 5)
		{
			CdDedDispProp aCdDedDispProp = getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
			ChangeShihatsuShuchakuOuterJikoku(
				pCmd->getCaMuiSelect()->getMuPtr(),
				-(aCdDedDispProp.getAnySecondIncDec1()));
		}
		else if (iType == 6)
		{
			if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperation1)
			{
				ChangeOperationBeforeTypePrev(
					pCmd->getCaMuiSelect()->getMuPtr());
			}
			else
			{
				ChangeOperationAfterTypePrev(
					pCmd->getCaMuiSelect()->getMuPtr());
			}
		}
		else if (iType == 7)
		{
			CdDedDispProp aCdDedDispProp = getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
			if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperation2)
			{
				ChangeOperationBeforeJikoku(
					pCmd->getCaMuiSelect()->getMuPtr(),
					-(aCdDedDispProp.getAnySecondIncDec1()));
			}
			else
			{
				ChangeOperationAfterJikoku(
					pCmd->getCaMuiSelect()->getMuPtr(),
					-(aCdDedDispProp.getAnySecondIncDec1()));
			}
		}
		else if (iType == 8)
		{
			ChangeRessyasyubetsuPrev(pCmd->getCaMuiSelect()->getMuPtr());
		}
		else if (iType == 10)
		{
			const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont();
			Mu<CentDedRessya*>* muCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr();
			for (int i = 0; iRv >= 0 && i < muCentDedRessya->size(); i++)
			{
				CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);

				//17.4.15 任意秒対応化_by_d_mania
				CdDedDispProp aCdDedDispProp = getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
				pCentDedRessya->modifyRessyaJikokuRev(CdDedJikan(-1 * aCdDedDispProp.getAnySecondIncDec1()),
					aCdJikokuOrder);
			}
		}
		else if (iType == 11)
		{
			//const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont();
			Mu<CentDedRessya*>* muCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr();
			for (int i = 0; iRv >= 0 && i < muCentDedRessya->size(); i++)
			{
				CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);

				pCentDedRessya->modifyRessyaBangou(-2);
			}
		}
		else if (iType == 12)
		{
			//const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont();
			Mu<CentDedRessya*>* muCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr();
			for (int i = 0; iRv >= 0 && i < muCentDedRessya->size(); i++)
			{
				CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);

				pCentDedRessya->modifyGou(-2);
			}
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
	}
	return iRv ;
}

int CWjkState_Ressyahensyu::
	OnJikokuhyouEkijikokuIncAnySecNoMove_Process( BOOL bQueryEnable, bool bAlt)
{
	int iRv = 0 ;
	Ou<EditCmd::CRfEditCmd_Ressya> pCmd ;
	Ou<EditCmd::CRfEditCmd_Ressya>* ppCmd = NULL ;
	if ( !bQueryEnable ){	ppCmd = &pCmd ;	}

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -2;
		}
	}
	if ( iRv >= 0 )
	{
		if ( !getCWndDcdGrid()->createCmd( CWndJikokuhyou::ECreateCmd_Select , ppCmd ) )
		{
			iRv = -1 ;	//	列車選択位置が正しくありません。
		}
	}
	CdDedJikokuOrder aCdJikokuOrder ;
	int iType = -1;
	if ( iRv >= 0 )
	{
		aCdJikokuOrder = getCWndDcdGrid()->CdDedJikokuOrderOf( 
			getCWndDcdGrid()->getYColSpecOfFocus() ) ;
		if (bAlt && !aCdJikokuOrder.getIsNull())
		{
			iType = 10;
		}
		else if (!aCdJikokuOrder.getIsNull())
		{
			iType = 0;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() ==
			CdYColSpec::ColumnType_Track)
		{
			iType = 1;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter1)
		{
			iType = 2;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter2)
		{
			iType = 3;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Outer_Shihatsu1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Outer_Shuchaku1)
		{
			iType = 4;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Outer_Shihatsu2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Outer_Shuchaku2)
		{
			iType = 5;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperation1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperation1)
		{
			iType = 6;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperation2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperation2)
		{
			iType = 7;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() ==
			CdYColSpec::ColumnType_Ressyasyubetsu)
		{
			iType = 8;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() ==
			CdYColSpec::ColumnType_Ressyabangou)
		{
			iType = 11;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() ==
			CdYColSpec::ColumnType_Gousuu)
		{
			iType = 12;
		}
		else
		{
			iRv = -1;
		}
	}
	//aCdJikokuOrder = 指定のセルに対応する『時刻Order』
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		// --------------------------------
		//	コマンドオブジェクトの列車を編集
		// --------------------------------
		if (iType == 0)
		{
			const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont();
			Mu<CentDedRessya*>* muCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr();
			for (int i = 0; iRv >= 0 && i < muCentDedRessya->size(); i++)
			{
				CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);

				//17.4.15 任意秒対応化_by_d_mania
				CdDedDispProp aCdDedDispProp = getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
				pCentDedRessya->modifyRessyaJikoku(CdDedJikan(+1 * aCdDedDispProp.getAnySecondIncDec1()),
					aCdJikokuOrder);
				//pCentDedRessya->modifyRessyaJikoku( CdDedJikan(  +1 * 5 ) , 
				//	aCdJikokuOrder ) ;
			}
		}
		else if (iType == 1)
		{
			ChangeRessyaTrackNext(pCmd->getCaMuiSelect()->getMuPtr());

		}
		else if (iType == 2)
		{
			ChangeShihatsuShuchakuOperationTypeNext(
				pCmd->getCaMuiSelect()->getMuPtr());

		}
		else if (iType == 3)
		{
			CdDedDispProp aCdDedDispProp = getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
			ChangeShihatsuShuchakuOperationJikoku(
				pCmd->getCaMuiSelect()->getMuPtr(),
				aCdDedDispProp.getAnySecondIncDec1());
		}
		else if (iType == 4)
		{
			ChangeShihatsuShuchakuOuterTerminalNext(
				pCmd->getCaMuiSelect()->getMuPtr());

		}
		else if (iType == 5)
		{
			CdDedDispProp aCdDedDispProp = getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
			ChangeShihatsuShuchakuOuterJikoku(
				pCmd->getCaMuiSelect()->getMuPtr(),
				aCdDedDispProp.getAnySecondIncDec1());
		}
		else if (iType == 6)
		{
			if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperation1)
			{
				ChangeOperationBeforeTypeNext(
					pCmd->getCaMuiSelect()->getMuPtr());
			}
			else
			{
				ChangeOperationAfterTypeNext(
					pCmd->getCaMuiSelect()->getMuPtr());
			}
		}
		else if (iType == 7)
		{
			CdDedDispProp aCdDedDispProp = getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
			if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperation2)
			{
				ChangeOperationBeforeJikoku(
					pCmd->getCaMuiSelect()->getMuPtr(),
					aCdDedDispProp.getAnySecondIncDec1());
			}
			else
			{
				ChangeOperationAfterJikoku(
					pCmd->getCaMuiSelect()->getMuPtr(),
					aCdDedDispProp.getAnySecondIncDec1());
			}
		}
		else if (iType == 8)
		{
			ChangeRessyasyubetsuNext(pCmd->getCaMuiSelect()->getMuPtr());
		}
		else if (iType == 10)
		{
			const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont();
			Mu<CentDedRessya*>* muCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr();
			for (int i = 0; iRv >= 0 && i < muCentDedRessya->size(); i++)
			{
				CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);

				//17.4.15 任意秒対応化_by_d_mania
				CdDedDispProp aCdDedDispProp = getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
				pCentDedRessya->modifyRessyaJikokuRev(CdDedJikan(+1 * aCdDedDispProp.getAnySecondIncDec1()),
					aCdJikokuOrder);
				//pCentDedRessya->modifyRessyaJikoku( CdDedJikan(  +1 * 5 ) , 
				//	aCdJikokuOrder ) ;
			}
		}
		else if (iType == 11)
		{
			//const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont();
			Mu<CentDedRessya*>* muCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr();
			for (int i = 0; iRv >= 0 && i < muCentDedRessya->size(); i++)
			{
				CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);

				pCentDedRessya->modifyRessyaBangou(2);
			}
		}
		else if (iType == 12)
		{
			//const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont();
			Mu<CentDedRessya*>* muCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr();
			for (int i = 0; iRv >= 0 && i < muCentDedRessya->size(); i++)
			{
				CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);

				pCentDedRessya->modifyGou(2);
			}
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
	}
	return iRv ;
}

int CWjkState_Ressyahensyu::
OnJikokuhyouEkijikokuDecAny2SecNoMove_Process( BOOL bQueryEnable, bool bAlt )
{
	int iRv = 0 ;
	Ou<EditCmd::CRfEditCmd_Ressya> pCmd ;
	Ou<EditCmd::CRfEditCmd_Ressya>* ppCmd = NULL ;
	if ( !bQueryEnable ){	ppCmd = &pCmd ;	}

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -2;
		}
	}
	if ( iRv >= 0 )
	{
		if ( !getCWndDcdGrid()->createCmd( CWndJikokuhyou::ECreateCmd_Select , ppCmd ) )
		{
			iRv = -1 ;	//	列車選択位置が正しくありません。
		}
	}
	CdDedJikokuOrder aCdJikokuOrder ;
	int iType = -1;
	if ( iRv >= 0 )
	{
		aCdJikokuOrder = getCWndDcdGrid()->CdDedJikokuOrderOf( 
			getCWndDcdGrid()->getYColSpecOfFocus() ) ;
		if (bAlt && !aCdJikokuOrder.getIsNull())
		{
			iType = 10;
		}
		else if (!aCdJikokuOrder.getIsNull())
		{
			iType = 0;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() ==
			CdYColSpec::ColumnType_Track)
		{
			iType = 1;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter1)
		{
			iType = 2;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter2)
		{
			iType = 3;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Outer_Shihatsu1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Outer_Shuchaku1)
		{
			iType = 4;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Outer_Shihatsu2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Outer_Shuchaku2)
		{
			iType = 5;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperation1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperation1)
		{
			iType = 6;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperation2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperation2)
		{
			iType = 7;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() ==
			CdYColSpec::ColumnType_Ressyasyubetsu)
		{
			iType = 8;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() ==
			CdYColSpec::ColumnType_Ressyabangou)
		{
			iType = 11;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() ==
			CdYColSpec::ColumnType_Gousuu)
		{
			iType = 12;
		}
		else
		{
			iRv = -1;
		}
	}
	//aCdJikokuOrder = 指定のセルに対応する『時刻Order』
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		// --------------------------------
		//	コマンドオブジェクトの列車を編集
		// --------------------------------
		if (iType == 0)
		{
			const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont();
			Mu<CentDedRessya*>* muCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr();
			for (int i = 0; iRv >= 0 && i < muCentDedRessya->size(); i++)
			{
				CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);

				//17.4.15 任意秒対応化_by_d_mania
				CdDedDispProp aCdDedDispProp = getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
				pCentDedRessya->modifyRessyaJikoku(CdDedJikan(-1 * aCdDedDispProp.getAnySecondIncDec2()),
					aCdJikokuOrder);
				//pCentDedRessya->modifyRessyaJikoku( CdDedJikan(  -1 * 15 ) , 
				//	aCdJikokuOrder ) ;
			}
		}
		else if (iType == 1)
		{
			ChangeRessyaTrackPrev(pCmd->getCaMuiSelect()->getMuPtr());

		}
		else if (iType == 2)
		{
			ChangeShihatsuShuchakuOperationTypePrev(
				pCmd->getCaMuiSelect()->getMuPtr());

		}
		else if (iType == 3)
		{
			CdDedDispProp aCdDedDispProp = getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
			ChangeShihatsuShuchakuOperationJikoku(
				pCmd->getCaMuiSelect()->getMuPtr(),
				-(aCdDedDispProp.getAnySecondIncDec2()));
		}
		else if (iType == 4)
		{
			ChangeShihatsuShuchakuOuterTerminalPrev(
				pCmd->getCaMuiSelect()->getMuPtr());

		}
		else if (iType == 5)
		{
			CdDedDispProp aCdDedDispProp = getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
			ChangeShihatsuShuchakuOuterJikoku(
				pCmd->getCaMuiSelect()->getMuPtr(),
				-(aCdDedDispProp.getAnySecondIncDec2()));
		}
		else if (iType == 6)
		{
			if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperation1)
			{
				ChangeOperationBeforeTypePrev(
					pCmd->getCaMuiSelect()->getMuPtr());
			}
			else
			{
				ChangeOperationAfterTypePrev(
					pCmd->getCaMuiSelect()->getMuPtr());
			}
		}
		else if (iType == 7)
		{
			CdDedDispProp aCdDedDispProp = getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
			if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperation2)
			{
				ChangeOperationBeforeJikoku(
					pCmd->getCaMuiSelect()->getMuPtr(),
					-(aCdDedDispProp.getAnySecondIncDec2()));
			}
			else
			{
				ChangeOperationAfterJikoku(
					pCmd->getCaMuiSelect()->getMuPtr(),
					-(aCdDedDispProp.getAnySecondIncDec2()));
			}
		}
		else if (iType == 8)
		{
			ChangeRessyasyubetsuPrev(pCmd->getCaMuiSelect()->getMuPtr());
		}
		else if (iType == 10)
		{
			const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont();
			Mu<CentDedRessya*>* muCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr();
			for (int i = 0; iRv >= 0 && i < muCentDedRessya->size(); i++)
			{
				CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);

				CdDedDispProp aCdDedDispProp = getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
				pCentDedRessya->modifyRessyaJikokuRev(CdDedJikan(-1 * aCdDedDispProp.getAnySecondIncDec2()),
					aCdJikokuOrder);
			}
		}
		else if (iType == 11)
		{
			//const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont();
			Mu<CentDedRessya*>* muCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr();
			for (int i = 0; iRv >= 0 && i < muCentDedRessya->size(); i++)
			{
				CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);

				pCentDedRessya->modifyRessyaBangou(-100);
			}
		}
		else if (iType == 12)
		{
			//const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont();
			Mu<CentDedRessya*>* muCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr();
			for (int i = 0; iRv >= 0 && i < muCentDedRessya->size(); i++)
			{
				CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);

				pCentDedRessya->modifyGou(-100);
			}
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
	}
	return iRv ;
}

int CWjkState_Ressyahensyu::
	OnJikokuhyouEkijikokuIncAny2SecNoMove_Process( BOOL bQueryEnable, bool bAlt )
{
	int iRv = 0 ;
	Ou<EditCmd::CRfEditCmd_Ressya> pCmd ;
	Ou<EditCmd::CRfEditCmd_Ressya>* ppCmd = NULL ;
	if ( !bQueryEnable ){	ppCmd = &pCmd ;	}

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -2;
		}
	}
	if ( iRv >= 0 )
	{
		if ( !getCWndDcdGrid()->createCmd( CWndJikokuhyou::ECreateCmd_Select , ppCmd ) )
		{
			iRv = -1 ;	//	列車選択位置が正しくありません。
		}
	}
	CdDedJikokuOrder aCdJikokuOrder ;
	int iType = -1;
	if ( iRv >= 0 )
	{
		aCdJikokuOrder = getCWndDcdGrid()->CdDedJikokuOrderOf( 
			getCWndDcdGrid()->getYColSpecOfFocus() ) ;
		if (bAlt && !aCdJikokuOrder.getIsNull())
		{
			iType = 10;
		}
		else if (!aCdJikokuOrder.getIsNull())
		{
			iType = 0;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() ==
			CdYColSpec::ColumnType_Track)
		{
			iType = 1;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter1)
		{
			iType = 2;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter2)
		{
			iType = 3;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Outer_Shihatsu1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Outer_Shuchaku1)
		{
			iType = 4;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Outer_Shihatsu2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Outer_Shuchaku2)
		{
			iType = 5;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperation1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperation1)
		{
			iType = 6;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperation2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperation2)
		{
			iType = 7;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() ==
			CdYColSpec::ColumnType_Ressyasyubetsu)
		{
			iType = 8;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() ==
			CdYColSpec::ColumnType_Ressyabangou)
		{
			iType = 11;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() ==
			CdYColSpec::ColumnType_Gousuu)
		{
			iType = 12;
		}
		else
		{
			iRv = -1;
		}
	}
	//aCdJikokuOrder = 指定のセルに対応する『時刻Order』
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		// --------------------------------
		//	コマンドオブジェクトの列車を編集
		// --------------------------------
		if (iType == 0)
		{
			const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont();
			Mu<CentDedRessya*>* muCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr();
			for (int i = 0; iRv >= 0 && i < muCentDedRessya->size(); i++)
			{
				CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);

				//17.4.15 任意秒対応化_by_d_mania
				CdDedDispProp aCdDedDispProp = getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
				pCentDedRessya->modifyRessyaJikoku(CdDedJikan(+1 * aCdDedDispProp.getAnySecondIncDec2()),
					aCdJikokuOrder);
				//pCentDedRessya->modifyRessyaJikoku( CdDedJikan(  +1 * 15 ) , 
				//	aCdJikokuOrder ) ;
			}
		}
		else if (iType == 1)
		{
			ChangeRessyaTrackNext(pCmd->getCaMuiSelect()->getMuPtr());

		}
		else if (iType == 2)
		{
			ChangeShihatsuShuchakuOperationTypeNext(
				pCmd->getCaMuiSelect()->getMuPtr());

		}
		else if (iType == 3)
		{
			CdDedDispProp aCdDedDispProp = getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
			ChangeShihatsuShuchakuOperationJikoku(
				pCmd->getCaMuiSelect()->getMuPtr(),
				aCdDedDispProp.getAnySecondIncDec2());
		}
		else if (iType == 4)
		{
			ChangeShihatsuShuchakuOuterTerminalNext(
				pCmd->getCaMuiSelect()->getMuPtr());

		}
		else if (iType == 5)
		{
			CdDedDispProp aCdDedDispProp = getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
			ChangeShihatsuShuchakuOuterJikoku(
				pCmd->getCaMuiSelect()->getMuPtr(),
				aCdDedDispProp.getAnySecondIncDec2());
		}
		else if (iType == 6)
		{
			if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperation1)
			{
				ChangeOperationBeforeTypeNext(
					pCmd->getCaMuiSelect()->getMuPtr());
			}
			else
			{
				ChangeOperationAfterTypeNext(
					pCmd->getCaMuiSelect()->getMuPtr());
			}
		}
		else if (iType == 7)
		{
			CdDedDispProp aCdDedDispProp = getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
			if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperation2)
			{
				ChangeOperationBeforeJikoku(
					pCmd->getCaMuiSelect()->getMuPtr(),
					aCdDedDispProp.getAnySecondIncDec2());
			}
			else
			{
				ChangeOperationAfterJikoku(
					pCmd->getCaMuiSelect()->getMuPtr(),
					aCdDedDispProp.getAnySecondIncDec2());
			}
		}
		else if (iType == 8)
		{
			ChangeRessyasyubetsuNext(pCmd->getCaMuiSelect()->getMuPtr());
		}
		else if (iType == 10)
		{
			const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont();
			Mu<CentDedRessya*>* muCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr();
			for (int i = 0; iRv >= 0 && i < muCentDedRessya->size(); i++)
			{
				CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);

				CdDedDispProp aCdDedDispProp = getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp();
				pCentDedRessya->modifyRessyaJikokuRev(CdDedJikan(+1 * aCdDedDispProp.getAnySecondIncDec2()),
					aCdJikokuOrder);
			}
		}
		else if (iType == 11)
		{
			//const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont();
			Mu<CentDedRessya*>* muCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr();
			for (int i = 0; iRv >= 0 && i < muCentDedRessya->size(); i++)
			{
				CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);

				pCentDedRessya->modifyRessyaBangou(100);
			}
		}
		else if (iType == 12)
		{
			//const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont();
			Mu<CentDedRessya*>* muCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr();
			for (int i = 0; iRv >= 0 && i < muCentDedRessya->size(); i++)
			{
				CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);

				pCentDedRessya->modifyGou(100);
			}
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
	}
	return iRv ;
}

//17.4.19
int CWjkState_Ressyahensyu::
	OnJikokuhyouEkijikokuAdjustStdOpeTime_Process( BOOL bQueryEnable, bool bAlt )
{
	int iRv = 0 ;
	Ou<EditCmd::CRfEditCmd_Ressya> pCmd ;
	Ou<EditCmd::CRfEditCmd_Ressya>* ppCmd = NULL ;
	if ( !bQueryEnable ){	ppCmd = &pCmd ;	}

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -2;
		}
	}
	if ( iRv >= 0 )
	{
		if ( !getCWndDcdGrid()->createCmd( CWndJikokuhyou::ECreateCmd_Select , ppCmd ) )
		{
			iRv = -1 ;	//	列車選択位置が正しくありません。
		}
	}
	CdDedJikokuOrder aCdJikokuOrder ;
	int iType = -1;
	if ( iRv >= 0 )
	{
		aCdJikokuOrder = getCWndDcdGrid()->CdDedJikokuOrderOf( 
			getCWndDcdGrid()->getYColSpecOfFocus() ) ;
		if ( !aCdJikokuOrder.getIsNull() )
		{
			//基準運転時分機能&通過駅時刻表示がOFFの場合は、無効
			if (!(getCWndDcdGrid()->getDisplayTsuukaEkiJikoku()) ||
				!(getCWndDcdGrid()->getStandardOperationTimeFunction()))
			{
				iRv = -1;	//	
			}
			else if(bAlt)
			{
				iType = 10;
			}
			else
			{
				iType = 0;
			}
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() ==
			CdYColSpec::ColumnType_Track)
		{
			iType = 1;
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter2)
		{
			iType = 3;
		}
		else
		{
			iRv = -1;
		}
	}
	
	//aCdJikokuOrder = 指定のセルに対応する『時刻Order』
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		// --------------------------------
		//	コマンドオブジェクトの列車を編集
		// --------------------------------
		if (iType == 0)
		{
			const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont();
			Mu<CentDedRessya*>* muCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr();
			for (int i = 0; iRv >= 0 && i < muCentDedRessya->size(); i++)
			{
				CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);

				//Ver2.06.07 基準運転時分取得元ダイヤインデクス機能追加に伴う変更
				int iDiaIndexStandard = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getKijunDiaIndex();
				//基準運転時分取得元ダイヤ以外かつ、列車の始発駅ではない
				if (aCdJikokuOrder.getEkiOrder() > pCentDedRessya->getSihatsuEki() &&
					getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedDiaCont()->findCentDedDiaByName(
						pCentDedRessyaCont->getDia()->getName()) != iDiaIndexStandard)
				{
					const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
						getCDiagramEditDoc()->getCDedRosenFileData()->
						getCentDedRosen()->getCentDedEkiCont()->getMuPtr(
							pCentDedRessya->getRessyahoukou());
					int iDifferenceTime = StdOpeTimeFunc(
						iDiaIndexStandard,
						aCdJikokuOrder,
						pCentDedRessya,
						muCdDedEki
					);
					if (iDifferenceTime != 0)
					{
						pCentDedRessya->modifyRessyaJikoku(CdDedJikan(+1 * iDifferenceTime),
							aCdJikokuOrder);
					}
				}
			}
		}
		else if (iType == 1)
		{
			ChangeRessyaTrackMain(pCmd->getCaMuiSelect()->getMuPtr());

		}
		else if (iType == 3)
		{
			ChangeShihatsuShuchakuOperationJikokuNull(
				pCmd->getCaMuiSelect()->getMuPtr());

		}
		else if (iType == 10)
		{
			const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont();
			Mu<CentDedRessya*>* muCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr();
			for (int i = 0; iRv >= 0 && i < muCentDedRessya->size(); i++)
			{
				CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);

				//Ver2.06.07 基準運転時分取得元ダイヤインデクス機能追加に伴う変更
				int iDiaIndexStandard = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getKijunDiaIndex();
				//基準運転時分取得元ダイヤ以外かつ、列車の始発駅ではない
				if (aCdJikokuOrder.getEkiOrder() > pCentDedRessya->getSihatsuEki() &&
					getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedDiaCont()->findCentDedDiaByName(
						pCentDedRessyaCont->getDia()->getName()) != iDiaIndexStandard)
				{
					const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
						getCDiagramEditDoc()->getCDedRosenFileData()->
						getCentDedRosen()->getCentDedEkiCont()->getMuPtr(
							pCentDedRessya->getRessyahoukou());
					int iDifferenceTime = StdOpeTimeFunc(
						iDiaIndexStandard,
						aCdJikokuOrder,
						pCentDedRessya,
						muCdDedEki
					);
					if (iDifferenceTime != 0)
					{
						CdDedJikokuOrder aCdJikokuOrderPrev = pCentDedRessya->decJikokuOrder(aCdJikokuOrder);
						pCentDedRessya->modifyRessyaJikokuRev(CdDedJikan(-1 * iDifferenceTime),
							aCdJikokuOrderPrev);
					}
				}
			}
		}
		// --------------------------------
		//	コマンドオブジェクトを実行
		// --------------------------------
		{
			getCDiagramEditDoc()->executeEditCmd( pCmd ) ;
		}
		// --------------------------------
		//	フォーカスを移動
		// --------------------------------
		{
			moveFocusCellToNext( false ) ;
		}
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************
	}
	return iRv ;
}

int CWjkState_Ressyahensyu::
OnJikokuhyouMoveToOutRessya_Process(BOOL bQueryEnable)
{
	int iRv = 0;
	//Ou<EditCmd::CRfEditCmd_Ressya> pCmd;
	//Ou<EditCmd::CRfEditCmd_Ressya>* ppCmd = NULL;
	//if (!bQueryEnable) { ppCmd = &pCmd; }

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	CdXColSpec aCdXColSpec = getCWndDcdGrid()->getXColSpecOfFocus();

	if (iRv >= 0)
	{
		if (aCdXColSpec.getColumnType() != CdXColSpec::ColumnType_Ressya)
		{
			iRv = -1;	//	フォーカスが列車以外にあります
		}
	}
	if (iRv >= 0)
	{
		if (getCDiagramEditDoc()->getCDedRosenFileData()
			->getCentDedRosen()->getEnableOperation() < 2)
		{
			iRv = -7;	//運用機能がOFFまたは簡易モードです。
		}
	}
	if (iRv >= 0)
	{
		if (getCentDedDia()->getWaitOperationUpdate())
		{
			iRv = -5;	//運用更新抑止状態です
		}
	}
	int iRessyaIndex = aCdXColSpec.getRessyaIndex();
	if (iRv >= 0 && getCWndDcdGrid()->getCustomizeDisplayMode())
	{
		CustomizeJikokuhyouContent contRessyaIndex = getCentDedDia()->getcontCustomizeRessyaIndex(getRessyahoukou(),aCdXColSpec.getRessyaIndex());
		if (contRessyaIndex.iRessyaIndexCont.empty())
		{
			iRv = -6;	//選択列に列車がありません
		}
		else
		{
			iRessyaIndex = contRessyaIndex.iRessyaIndexCont.front();
		}
	}
	if (iRv >= 0)
	{
		const CentDedRessya* pCentDedRessya = getCentDedRessyaCont()->getMuPtr()->get(iRessyaIndex);
		if (pCentDedRessya->isNull())
		{
			iRv = -2;	//NULL状態の列車です。
		}
		if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Out ||
			pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
		{
			iRv = -3;	//この列車が出区列車です。
		}
		if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Junction &&
			pCentDedRessya->getFirstOperation().getOperationNumber().empty())
		{
			iRv = -4;	//運用番号がありません。
		}
	}
	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************

		//const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont();

		const CentDedRessya* pCentDedRessya = getCentDedRessyaCont()->getMuPtr()->get(iRessyaIndex);

		CdDedRessyaProperty aRessyaPropertyThis(getRessyahoukou(), iRessyaIndex);
		tstring strOperationNumberFirst = pCentDedRessya->getFirstOperation().getOperationNumber()[0];
		if (strOperationNumberFirst.empty())
		{
			iRv = -11;//空白運番なので、探索は行いません
		}
		if (getCentDedDia()->getcontOperationTableContent().count(strOperationNumberFirst) == 0)
		{
			iRv = -13;//運用番号に対する運用表が見つかりませんでした
		}
		CdDedRessyaProperty aRessyaPropertyOut;
		int iOutSihatsuEkiOrder;
		if (iRv >= 0)
		{
			const list<OperationTableContent>& pOperationTableContent =
				getCentDedDia()->getcontOperationTableContent().at(strOperationNumberFirst);
			bool bFound = false;
			for (auto itr = pOperationTableContent.rbegin(); itr != pOperationTableContent.rend(); itr++)
			{
				if (bFound && !itr->aRessyaProperty.getJikoku().isNull())
				{
					aRessyaPropertyOut = itr->aRessyaProperty;
					iOutSihatsuEkiOrder = itr->iSihatsuEkiOrder;
					break;
				}
				if (!bFound && itr->aRessyaProperty.isEqualTo(aRessyaPropertyThis,false) &&
					itr->iSihatsuEkiOrder == pCentDedRessya->getValidSihatsuEki())
				{
					bFound = true;
				}
			}
			if (aRessyaPropertyOut.getIsNull())
			{
				iRv = -12;//出区列車が見つかりませんでした。
			}
		}
		if (iRv >= 0)
		{
			if (pCentDedRessya->getRessyahoukou() == aRessyaPropertyOut.getRessyahoukou())
			{
				//出区列車が、選択列車と同じ列車方向の場合。
				int iRessyaIndexOut = aRessyaPropertyOut.getRessyaIndex();
				if (getCWndDcdGrid()->getCustomizeDisplayMode())
				{
					const vector<CustomizeJikokuhyouContent>& contCustomizeRessyaIndex =
						getCentDedDia()->getcontCustomizeRessyaIndex(getRessyahoukou());
					bool bFound = false;
					for (int idx = 0; idx < (int)contCustomizeRessyaIndex.size() && !bFound; idx++)
					{
						const CustomizeJikokuhyouContent& CustomizeRessyaIndex =
							contCustomizeRessyaIndex[idx];
						for (int idx2 = 0; idx2 < (int)CustomizeRessyaIndex.iRessyaIndexCont.size() && !bFound; idx2++)
						{
							if (CustomizeRessyaIndex.iRessyaIndexCont[idx2] == iRessyaIndexOut)
							{
								iRessyaIndexOut = idx;
								bFound = true;
							}
						}
					}
				}
				CdXColSpecCont aXColSpecCont
					= getCWndDcdGrid()->createXColSpecCont();
				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(
					CdXColSpec(
						CdXColSpec::ColumnType_Ressya,
						iRessyaIndexOut));

				CdYColSpecCont aYColSpecCont
					= getCWndDcdGrid()->createYColSpecCont();
				int iYColumnNumber = aYColSpecCont.ColumnNumberFromSpec(
					CdYColSpec(
						CdYColSpec::ColumnType_Ekijikoku_Hatsu,
						iOutSihatsuEkiOrder),
					true);

				getCWndDcdGrid()->getCFocus()->setFocusCellColumnNumber(CdDcdPosXy(iXColumnNumber, iYColumnNumber));
			}
			else
			{
				//出区列車が、選択列車と反対方向の場合
				// --------------------------------
				//	反対方向の時刻表ビューを開く
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
								aRessyaPropertyOut.getRessyahoukou(),
								getCWndDcdGrid()->getCustomizeDisplayMode(),
								&pCJikokuhyouView);
						if (pCJikokuhyouView == NULL)
						{
							iRv = -5;	//	反対方向の時刻表ビューのオープンに失敗しました
						}
					}
					//pCJikokuhyouDoc = 時刻表ドキュメント
					//pCJikokuhyouView = 時刻表ビュー
				}

				if (iRv >= 0)
				{
					int iRessyaIndexOut = aRessyaPropertyOut.getRessyaIndex();
					if (getCWndDcdGrid()->getCustomizeDisplayMode())
					{
						const vector<CustomizeJikokuhyouContent>& contCustomizeRessyaIndex =
							getCentDedDia()->getcontCustomizeRessyaIndex(aRessyaPropertyOut.getRessyahoukou());
						bool bFound = false;
						for (int idx = 0; idx < (int)contCustomizeRessyaIndex.size() && !bFound; idx++)
						{
							const CustomizeJikokuhyouContent& CustomizeRessyaIndex =
								contCustomizeRessyaIndex[idx];
							for (int idx2 = 0; idx2 < (int)CustomizeRessyaIndex.iRessyaIndexCont.size() && !bFound; idx2++)
							{
								if (CustomizeRessyaIndex.iRessyaIndexCont[idx2] == iRessyaIndexOut)
								{
									iRessyaIndexOut = idx;
									bFound = true;
								}
							}
						}
					}

					pCJikokuhyouView->setFocusToRessyaIndex(iRessyaIndexOut, iOutSihatsuEkiOrder);
					iRv = 1;	//	時刻表ビューへ移動しました
				}

			}
		}

		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************
	}
	return iRv;
}
int CWjkState_Ressyahensyu::
OnJikokuhyouMoveToPrevRessya_Process(BOOL bQueryEnable)
{
	int iRv = 0;
	CdXColSpec aCdXColSpec = getCWndDcdGrid()->getXColSpecOfFocus();

	if (iRv >= 0)
	{
		if (aCdXColSpec.getColumnType() != CdXColSpec::ColumnType_Ressya)
		{
			iRv = -1;	//	フォーカスが列車以外にあります
		}
	}
	if (iRv >= 0)
	{
		if (getCDiagramEditDoc()->getCDedRosenFileData()
			->getCentDedRosen()->getEnableOperation() < 2)
		{
			iRv = -8;	//運用機能がOFFまたは簡易モードです。
		}
	}
	if (iRv >= 0)
	{
		if (getCentDedDia()->getWaitOperationUpdate())
		{
			iRv = -6;	//運用更新抑止状態です
		}
	}
	int iRessyaIndex = aCdXColSpec.getRessyaIndex();
	if (iRv >= 0 && getCWndDcdGrid()->getCustomizeDisplayMode())
	{
		CustomizeJikokuhyouContent contRessyaIndex = getCentDedDia()->getcontCustomizeRessyaIndex(getRessyahoukou(), aCdXColSpec.getRessyaIndex());
		if (contRessyaIndex.iRessyaIndexCont.empty())
		{
			iRv = -7;	//選択列に列車がありません
		}
		else
		{
			iRessyaIndex = contRessyaIndex.iRessyaIndexCont.front();
		}
	}
	if (iRv >= 0)
	{
		const CentDedRessya* pCentDedRessya = getCentDedRessyaCont()->getMuPtr()->get(iRessyaIndex);
		if (pCentDedRessya->isNull())
		{
			iRv = -2;	//NULL状態の列車です。
		}
		if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Out ||
			pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
		{
			iRv = -3;	//この列車が出区列車です。
		}
		if (pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Junction &&
			pCentDedRessya->getFirstOperation().getOperationNumber().empty())
		{
			iRv = -4;	//運用番号がありません。
		}
	}

	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************

		const CentDedRessya* pCentDedRessya = getCentDedRessyaCont()->getMuPtr()->get(iRessyaIndex);

		CdDedRessyaProperty aRessyaPropertyThis(getRessyahoukou(), iRessyaIndex);
		tstring strOperationNumberFirst = pCentDedRessya->getFirstOperation().getOperationNumber()[0];
		if (strOperationNumberFirst.empty())
		{
			iRv = -11;//空白運番なので、探索は行いません
		}
		if (getCentDedDia()->getcontOperationTableContent().count(strOperationNumberFirst) == 0)
		{
			iRv = -13;//運用番号に対する運用表が見つかりませんでした
		}
		CdDedRessyaProperty aRessyaPropertyPrev;
		int iPrevSihatsuEkiOrder;
		if (iRv >= 0)
		{
			const list<OperationTableContent>& pOperationTableContent =
				getCentDedDia()->getcontOperationTableContent().at(strOperationNumberFirst);
			for (auto itr = pOperationTableContent.rbegin(); itr != pOperationTableContent.rend(); itr++)
			{
				if (itr->aRessyaProperty.isEqualTo(aRessyaPropertyThis, false) &&
					itr->iSihatsuEkiOrder == pCentDedRessya->getValidSihatsuEki())
				{
					itr++;
					if (itr != pOperationTableContent.rend())
					{
						aRessyaPropertyPrev = itr->aRessyaProperty;
						iPrevSihatsuEkiOrder = itr->iSihatsuEkiOrder;
					}
					else
					{
						break;
					}
				}
			}
			if (aRessyaPropertyPrev.getIsNull())
			{
				iRv = -12;//一つ前の列車が見つかりませんでした。
			}
		}

		if (iRv >= 0)
		{
			if (pCentDedRessya->getRessyahoukou() == aRessyaPropertyPrev.getRessyahoukou())
			{
				//前の列車が、選択列車と同じ列車方向の場合。
				int iRessyaIndexPrev = aRessyaPropertyPrev.getRessyaIndex();
				if (getCWndDcdGrid()->getCustomizeDisplayMode())
				{
					const vector<CustomizeJikokuhyouContent>& contCustomizeRessyaIndex =
						getCentDedDia()->getcontCustomizeRessyaIndex(getRessyahoukou());
					bool bFound = false;
					for (int idx = 0; idx < (int)contCustomizeRessyaIndex.size() && !bFound; idx++)
					{
						const CustomizeJikokuhyouContent& CustomizeRessyaIndex =
							contCustomizeRessyaIndex[idx];
						for (int idx2 = 0; idx2 < (int)CustomizeRessyaIndex.iRessyaIndexCont.size() && !bFound; idx2++)
						{
							if (CustomizeRessyaIndex.iRessyaIndexCont[idx2] == iRessyaIndexPrev)
							{
								iRessyaIndexPrev = idx;
								bFound = true;
							}
						}
					}
				}
				CdXColSpecCont aXColSpecCont
					= getCWndDcdGrid()->createXColSpecCont();
				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(
					CdXColSpec(
						CdXColSpec::ColumnType_Ressya,
						iRessyaIndexPrev));

				CdYColSpecCont aYColSpecCont
					= getCWndDcdGrid()->createYColSpecCont();
				int iYColumnNumber = aYColSpecCont.ColumnNumberFromSpec(
					CdYColSpec(
						CdYColSpec::ColumnType_Ekijikoku_Hatsu,
						iPrevSihatsuEkiOrder),
					true);

				getCWndDcdGrid()->getCFocus()->setFocusCellColumnNumber(CdDcdPosXy(iXColumnNumber, iYColumnNumber));
			}
			else
			{
				//前の列車が、選択列車と反対方向の場合
				// --------------------------------
				//	反対方向の時刻表ビューを開く
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
								aRessyaPropertyPrev.getRessyahoukou(),
								getCWndDcdGrid()->getCustomizeDisplayMode(),
								&pCJikokuhyouView);
						if (pCJikokuhyouView == NULL)
						{
							iRv = -5;	//	反対方向の時刻表ビューのオープンに失敗しました
						}
					}
					//pCJikokuhyouDoc = 時刻表ドキュメント
					//pCJikokuhyouView = 時刻表ビュー
				}

				if (iRv >= 0)
				{
					int iRessyaIndexPrev = aRessyaPropertyPrev.getRessyaIndex();
					if (getCWndDcdGrid()->getCustomizeDisplayMode())
					{
						const vector<CustomizeJikokuhyouContent>& contCustomizeRessyaIndex =
							getCentDedDia()->getcontCustomizeRessyaIndex(aRessyaPropertyPrev.getRessyahoukou());
						bool bFound = false;
						for (int idx = 0; idx < (int)contCustomizeRessyaIndex.size() && !bFound; idx++)
						{
							const CustomizeJikokuhyouContent& CustomizeRessyaIndex =
								contCustomizeRessyaIndex[idx];
							for (int idx2 = 0; idx2 < (int)CustomizeRessyaIndex.iRessyaIndexCont.size() && !bFound; idx2++)
							{
								if (CustomizeRessyaIndex.iRessyaIndexCont[idx2] == iRessyaIndexPrev)
								{
									iRessyaIndexPrev = idx;
									bFound = true;
								}
							}
						}
					}
					pCJikokuhyouView->setFocusToRessyaIndex(iRessyaIndexPrev, iPrevSihatsuEkiOrder);
					iRv = 1;	//	時刻表ビューへ移動しました
				}
			}
		}

		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************
	}
	return iRv;
}
int CWjkState_Ressyahensyu::
OnJikokuhyouMoveToNextRessya_Process(BOOL bQueryEnable)
{
	int iRv = 0;
	CdXColSpec aCdXColSpec = getCWndDcdGrid()->getXColSpecOfFocus();

	if (iRv >= 0)
	{
		if (aCdXColSpec.getColumnType() != CdXColSpec::ColumnType_Ressya)
		{
			iRv = -1;	//	フォーカスが列車以外にあります
		}
	}
	if (iRv >= 0)
	{
		if (getCDiagramEditDoc()->getCDedRosenFileData()
			->getCentDedRosen()->getEnableOperation() < 2)
		{
			iRv = -8;	//運用機能がOFFまたは簡易モードです。
		}
	}
	if (iRv >= 0)
	{
		if (getCentDedDia()->getWaitOperationUpdate())
		{
			iRv = -6;	//運用更新抑止状態です
		}
	}
	int iRessyaIndex = aCdXColSpec.getRessyaIndex();
	if (iRv >= 0 && getCWndDcdGrid()->getCustomizeDisplayMode())
	{
		CustomizeJikokuhyouContent contRessyaIndex = getCentDedDia()->getcontCustomizeRessyaIndex(getRessyahoukou(), aCdXColSpec.getRessyaIndex());
		if (contRessyaIndex.iRessyaIndexCont.empty())
		{
			iRv = -7;	//選択列に列車がありません
		}
		else
		{
			iRessyaIndex = contRessyaIndex.iRessyaIndexCont.back();
		}
	}
	if (iRv >= 0)
	{
		const CentDedRessya* pCentDedRessya = getCentDedRessyaCont()->getMuPtr()->get(iRessyaIndex);
		if (pCentDedRessya->isNull())
		{
			iRv = -2;	//NULL状態の列車です。
		}
		if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_In ||
			pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
		{
			iRv = -3;	//この列車が入区列車です。
		}
		if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Junction &&
			pCentDedRessya->getLastOperation().getOperationNumber().empty())
		{
			iRv = -4;	//運用番号がありません。
		}
		if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Junction &&
			!pCentDedRessya->getLastOperation().getJunctionSucceed())
		{
			iRv = -5;	//次列車がありません。
		}
	}

	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************

		const CentDedRessya* pCentDedRessya = getCentDedRessyaCont()->getMuPtr()->get(iRessyaIndex);

		CdDedRessyaProperty aRessyaPropertyThis(getRessyahoukou(), iRessyaIndex);
		tstring strOperationNumberFirst = pCentDedRessya->getLastOperation().getOperationNumber()[0];
		if (strOperationNumberFirst.empty())
		{
			iRv = -11;//空白運番なので、探索は行いません
		}
		if (getCentDedDia()->getcontOperationTableContent().count(strOperationNumberFirst) == 0)
		{
			iRv = -13;//運用番号に対する運用表が見つかりませんでした
		}
		CdDedRessyaProperty aRessyaPropertyNext;
		int iNextSihatsuEkiOrder;
		if (iRv >= 0)
		{
			const list<OperationTableContent>& pOperationTableContent =
				getCentDedDia()->getcontOperationTableContent().at(strOperationNumberFirst);
			for (auto itr = pOperationTableContent.begin(); itr != pOperationTableContent.end(); itr++)
			{
				if (itr->aRessyaProperty.isEqualTo(aRessyaPropertyThis, false) &&
					itr->iSyuuchakuEkiOrder == pCentDedRessya->getValidSyuuchakuEki())
				{
					itr++;
					if (itr != pOperationTableContent.end())
					{
						aRessyaPropertyNext = itr->aRessyaProperty;
						iNextSihatsuEkiOrder = itr->iSihatsuEkiOrder;
					}
					else
					{
						break;
					}
				}
			}
			if (aRessyaPropertyNext.getIsNull())
			{
				iRv = -12;//一つ前の列車が見つかりませんでした。
			}
		}

		if (iRv >= 0)
		{
			if (pCentDedRessya->getRessyahoukou() == aRessyaPropertyNext.getRessyahoukou())
			{
				//次の列車が、選択列車と同じ列車方向の場合。
				int iRessyaIndexNext = aRessyaPropertyNext.getRessyaIndex();
				if (getCWndDcdGrid()->getCustomizeDisplayMode())
				{
					const vector<CustomizeJikokuhyouContent>& contCustomizeRessyaIndex =
						getCentDedDia()->getcontCustomizeRessyaIndex(getRessyahoukou());
					bool bFound = false;
					for (int idx = 0; idx < (int)contCustomizeRessyaIndex.size() && !bFound; idx++)
					{
						const CustomizeJikokuhyouContent& CustomizeRessyaIndex =
							contCustomizeRessyaIndex[idx];
						for (int idx2 = 0; idx2 < (int)CustomizeRessyaIndex.iRessyaIndexCont.size() && !bFound; idx2++)
						{
							if (CustomizeRessyaIndex.iRessyaIndexCont[idx2] == iRessyaIndexNext)
							{
								iRessyaIndexNext = idx;
								bFound = true;
							}
						}
					}
				}
				CdXColSpecCont aXColSpecCont
					= getCWndDcdGrid()->createXColSpecCont();
				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(
					CdXColSpec(
						CdXColSpec::ColumnType_Ressya,
						iRessyaIndexNext));

				CdYColSpecCont aYColSpecCont
					= getCWndDcdGrid()->createYColSpecCont();
				int iYColumnNumber = aYColSpecCont.ColumnNumberFromSpec(
					CdYColSpec(
						CdYColSpec::ColumnType_Ekijikoku_Hatsu,
						iNextSihatsuEkiOrder),
					true);

				getCWndDcdGrid()->getCFocus()->setFocusCellColumnNumber(CdDcdPosXy(iXColumnNumber, iYColumnNumber));
			}
			else
			{
				//次の列車が、選択列車と反対方向の場合
				// --------------------------------
				//	反対方向の時刻表ビューを開く
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
								aRessyaPropertyNext.getRessyahoukou(),
								getCWndDcdGrid()->getCustomizeDisplayMode(),
								&pCJikokuhyouView);
						if (pCJikokuhyouView == NULL)
						{
							iRv = -5;	//	反対方向の時刻表ビューのオープンに失敗しました
						}
					}
					//pCJikokuhyouDoc = 時刻表ドキュメント
					//pCJikokuhyouView = 時刻表ビュー
				}

				if (iRv >= 0)
				{
					int iRessyaIndexNext = aRessyaPropertyNext.getRessyaIndex();
					if (getCWndDcdGrid()->getCustomizeDisplayMode())
					{
						const vector<CustomizeJikokuhyouContent>& contCustomizeRessyaIndex =
							getCentDedDia()->getcontCustomizeRessyaIndex(aRessyaPropertyNext.getRessyahoukou());
						bool bFound = false;
						for (int idx = 0; idx < (int)contCustomizeRessyaIndex.size() && !bFound; idx++)
						{
							const CustomizeJikokuhyouContent& CustomizeRessyaIndex =
								contCustomizeRessyaIndex[idx];
							for (int idx2 = 0; idx2 < (int)CustomizeRessyaIndex.iRessyaIndexCont.size() && !bFound; idx2++)
							{
								if (CustomizeRessyaIndex.iRessyaIndexCont[idx2] == iRessyaIndexNext)
								{
									iRessyaIndexNext = idx;
									bFound = true;
								}
							}
						}
					}
					pCJikokuhyouView->setFocusToRessyaIndex(iRessyaIndexNext, iNextSihatsuEkiOrder);
					iRv = 1;	//	時刻表ビューへ移動しました
				}
			}
		}
		
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************
	}
	return iRv;
}
int CWjkState_Ressyahensyu::
OnJikokuhyouMoveToInRessya_Process(BOOL bQueryEnable)
{
	int iRv = 0;
	CdXColSpec aCdXColSpec = getCWndDcdGrid()->getXColSpecOfFocus();

	if (iRv >= 0)
	{
		if (aCdXColSpec.getColumnType() != CdXColSpec::ColumnType_Ressya)
		{
			iRv = -1;	//	フォーカスが列車以外にあります
		}
	}
	if (iRv >= 0)
	{
		if (getCDiagramEditDoc()->getCDedRosenFileData()
			->getCentDedRosen()->getEnableOperation() < 2)
		{
			iRv = -8;	//運用機能がOFFまたは簡易モードです。
		}
	}
	if (iRv >= 0)
	{
		if (getCentDedDia()->getWaitOperationUpdate())
		{
			iRv = -6;	//運用更新抑止状態です
		}
	}
	int iRessyaIndex = aCdXColSpec.getRessyaIndex();
	if (iRv >= 0 && getCWndDcdGrid()->getCustomizeDisplayMode())
	{
		CustomizeJikokuhyouContent contRessyaIndex = getCentDedDia()->getcontCustomizeRessyaIndex(getRessyahoukou(), aCdXColSpec.getRessyaIndex());
		if (contRessyaIndex.iRessyaIndexCont.empty())
		{
			iRv = -7;	//選択列に列車がありません
		}
		else
		{
			iRessyaIndex = contRessyaIndex.iRessyaIndexCont.back();
		}
	}
	if (iRv >= 0)
	{
		const CentDedRessya* pCentDedRessya = getCentDedRessyaCont()->getMuPtr()->get(iRessyaIndex);
		if (pCentDedRessya->isNull())
		{
			iRv = -2;	//NULL状態の列車です。
		}
		if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_In ||
			pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
		{
			iRv = -3;	//この列車が入区列車です。
		}
		if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Junction &&
			pCentDedRessya->getLastOperation().getOperationNumber().empty())
		{
			iRv = -4;	//運用番号がありません。
		}
		if (pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Junction &&
			!pCentDedRessya->getLastOperation().getJunctionSucceed())
		{
			iRv = -5;	//次列車がありません。
		}
	}
	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************

		const CentDedRessya* pCentDedRessya = getCentDedRessyaCont()->getMuPtr()->get(iRessyaIndex);

		CdDedRessyaProperty aRessyaPropertyThis(getRessyahoukou(), iRessyaIndex);
		tstring strOperationNumberFirst = pCentDedRessya->getLastOperation().getOperationNumber()[0];
		if (strOperationNumberFirst.empty())
		{
			iRv = -11;//空白運番なので、探索は行いません
		}
		if (getCentDedDia()->getcontOperationTableContent().count(strOperationNumberFirst) == 0)
		{
			iRv = -13;//運用番号に対する運用表が見つかりませんでした
		}
		CdDedRessyaProperty aRessyaPropertyIn;
		int iInSyuuchakuEkiOrder;
		if (iRv >= 0)
		{
			const list<OperationTableContent>& pOperationTableContent =
				getCentDedDia()->getcontOperationTableContent().at(strOperationNumberFirst);
			bool bFound = false;
			for (auto itr = pOperationTableContent.begin(); itr != pOperationTableContent.end(); itr++)
			{
				if (bFound)
				{
					if (itr->aRessyaProperty.getJikoku().isNull())
					{
						aRessyaPropertyIn = itr->aRessyaProperty;
						iInSyuuchakuEkiOrder = itr->iSyuuchakuEkiOrder;
					}
					else
					{
						break;
					}
				}
				if (!bFound && itr->aRessyaProperty.isEqualTo(aRessyaPropertyThis, false) &&
					itr->iSyuuchakuEkiOrder == pCentDedRessya->getValidSyuuchakuEki())
				{
					bFound = true;
				}
			}
			if (aRessyaPropertyIn.getIsNull())
			{
				iRv = -12;//一つ前の列車が見つかりませんでした。
			}
		}

		if (iRv >= 0)
		{
			if (pCentDedRessya->getRessyahoukou() == aRessyaPropertyIn.getRessyahoukou())
			{
				//入区列車が、選択列車と同じ列車方向の場合。
				int iRessyaIndexIn = aRessyaPropertyIn.getRessyaIndex();
				if (getCWndDcdGrid()->getCustomizeDisplayMode())
				{
					const vector<CustomizeJikokuhyouContent>& contCustomizeRessyaIndex =
						getCentDedDia()->getcontCustomizeRessyaIndex(getRessyahoukou());
					bool bFound = false;
					for (int idx = 0; idx < (int)contCustomizeRessyaIndex.size() && !bFound; idx++)
					{
						const CustomizeJikokuhyouContent& CustomizeRessyaIndex =
							contCustomizeRessyaIndex[idx];
						for (int idx2 = 0; idx2 < (int)CustomizeRessyaIndex.iRessyaIndexCont.size() && !bFound; idx2++)
						{
							if (CustomizeRessyaIndex.iRessyaIndexCont[idx2] == iRessyaIndexIn)
							{
								iRessyaIndexIn = idx;
								bFound = true;
							}
						}
					}
				}
				CdXColSpecCont aXColSpecCont
					= getCWndDcdGrid()->createXColSpecCont();
				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(
					CdXColSpec(
						CdXColSpec::ColumnType_Ressya,
						iRessyaIndexIn));

				CdYColSpecCont aYColSpecCont
					= getCWndDcdGrid()->createYColSpecCont();
				int iYColumnNumber = aYColSpecCont.ColumnNumberFromSpec(
					CdYColSpec(
						CdYColSpec::ColumnType_Ekijikoku_Hatsu,
						iInSyuuchakuEkiOrder),
					true);

				getCWndDcdGrid()->getCFocus()->setFocusCellColumnNumber(CdDcdPosXy(iXColumnNumber, iYColumnNumber));
			}
			else
			{
				//出区列車が、選択列車と反対方向の場合
				// --------------------------------
				//	反対方向の時刻表ビューを開く
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
								aRessyaPropertyIn.getRessyahoukou(),
								getCWndDcdGrid()->getCustomizeDisplayMode(),
								&pCJikokuhyouView);
						if (pCJikokuhyouView == NULL)
						{
							iRv = -5;	//	反対方向の時刻表ビューのオープンに失敗しました
						}
					}
					//pCJikokuhyouDoc = 時刻表ドキュメント
					//pCJikokuhyouView = 時刻表ビュー
				}

				if (iRv >= 0)
				{
					int iRessyaIndexIn = aRessyaPropertyIn.getRessyaIndex();
					if (getCWndDcdGrid()->getCustomizeDisplayMode())
					{
						const vector<CustomizeJikokuhyouContent>& contCustomizeRessyaIndex =
							getCentDedDia()->getcontCustomizeRessyaIndex(aRessyaPropertyIn.getRessyahoukou());
						bool bFound = false;
						for (int idx = 0; idx < (int)contCustomizeRessyaIndex.size() && !bFound; idx++)
						{
							const CustomizeJikokuhyouContent& CustomizeRessyaIndex =
								contCustomizeRessyaIndex[idx];
							for (int idx2 = 0; idx2 < (int)CustomizeRessyaIndex.iRessyaIndexCont.size() && !bFound; idx2++)
							{
								if (CustomizeRessyaIndex.iRessyaIndexCont[idx2] == iRessyaIndexIn)
								{
									iRessyaIndexIn = idx;
									bFound = true;
								}
							}
						}
					}
					pCJikokuhyouView->setFocusToRessyaIndex(iRessyaIndexIn, iInSyuuchakuEkiOrder);
					iRv = 1;	//	時刻表ビューへ移動しました
				}
			}
		}
		
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************
	}
	return iRv;
}

int CWjkState_Ressyahensyu::
OnJikokuhyouRessyabangouMove_Process(BOOL bQueryEnable)
{
	int iRv = 0;
	//Ou<EditCmd::CRfEditCmd_Ressya> pCmd;
	//Ou<EditCmd::CRfEditCmd_Ressya>* ppCmd = NULL;
	//if (!bQueryEnable) { ppCmd = &pCmd; }

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	CdXColSpec aCdXColSpec = getCWndDcdGrid()->getXColSpecOfFocus();
	tstring strSearchRessyabangou;
	if (iRv >= 0)
	{
		strSearchRessyabangou = getCDiagramEditApp()->getCMainFrame()->getSearchRessyabangou();
		if (strSearchRessyabangou.empty())
		{
			iRv = -1;
		}
	}
	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************

		int iFoundRessyaIndex = -1;
		for (int iRessyaIndex = 0; iRessyaIndex < getCentDedRessyaCont()->size(); iRessyaIndex++)
		{
			const CentDedRessya* pCentDedRessya = getCentDedRessyaCont()->getMuPtr()->get(iRessyaIndex);
			if (pCentDedRessya->getRessyabangou() == strSearchRessyabangou)
			{
				iFoundRessyaIndex = iRessyaIndex;
				break;
			}
		}

		if (iFoundRessyaIndex >= 0)
		{
			//出区列車が、選択列車と同じ列車方向の場合。
			if (getCWndDcdGrid()->getCustomizeDisplayMode())
			{
				const vector<CustomizeJikokuhyouContent>& contCustomizeRessyaIndex =
					getCentDedDia()->getcontCustomizeRessyaIndex(getRessyahoukou());
				bool bFound = false;
				for (int idx = 0; idx < (int)contCustomizeRessyaIndex.size() && !bFound; idx++)
				{
					const CustomizeJikokuhyouContent& CustomizeRessyaIndex =
						contCustomizeRessyaIndex[idx];
					for (int idx2 = 0; idx2 < (int)CustomizeRessyaIndex.iRessyaIndexCont.size() && !bFound; idx2++)
					{
						if (CustomizeRessyaIndex.iRessyaIndexCont[idx2] == iFoundRessyaIndex)
						{
							iFoundRessyaIndex = idx;
							bFound = true;
						}
					}
				}
			}
			CdXColSpecCont aXColSpecCont
				= getCWndDcdGrid()->createXColSpecCont();
			int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(
				CdXColSpec(
					CdXColSpec::ColumnType_Ressya,
					iFoundRessyaIndex));

			CdYColSpecCont aYColSpecCont
				= getCWndDcdGrid()->createYColSpecCont();
			int iYColumnNumber = aYColSpecCont.ColumnNumberFromSpec(
				CdYColSpec(
					CdYColSpec::ColumnType_Ressyabangou),
				true);

			getCWndDcdGrid()->getCFocus()->setFocusCellColumnNumber(CdDcdPosXy(iXColumnNumber, iYColumnNumber));
			//getCWndDcdGrid()->SetActiveWindow();
			getCWndDcdGrid()->SetFocus();
		}
		else
		{
			CString strError;
			strError += _T("列車番号[");
			strError += strSearchRessyabangou.c_str();
			strError+= _T("]は見つかりませんでした。");
			AfxMessageBox(strError, MB_ICONASTERISK);
		}

		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************
	}
	return iRv;
}

int CWjkState_Ressyahensyu::OnJikokuhyouOpenOperationTable_Process(BOOL bQueryEnable)
{
	int iRv = 0;
	CdXColSpec aCdXColSpec = getCWndDcdGrid()->getXColSpecOfFocus();
	CdYColSpec aCdYColSpec = getCWndDcdGrid()->getYColSpecOfFocus();
	//const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont();

	if (iRv >= 0)
	{
		if (aCdXColSpec.getColumnType() != CdXColSpec::ColumnType_Ressya)
		{
			iRv = -1;	//	フォーカスが列車以外にあります
		}
	}
	//if (iRv >= 0)
	//{
	//	if (aCdYColSpec.getColumnType() != CdYColSpec::ColumnType_OperationNumber)
	//	{
	//		iRv = -6;	//	フォーカスが運用番号欄以外にあります
	//	}
	//}
	if (iRv >= 0)
	{
		if (getCDiagramEditDoc()->getCDedRosenFileData()
			->getCentDedRosen()->getEnableOperation() < 2)
		{
			iRv = -6;	//運用機能がOFFまたは簡易モードです。
		}
	}
	if (iRv >= 0)
	{
		if (getCentDedDia()->getWaitOperationUpdate())
		{
			iRv = -5;	//運用更新抑止状態です
		}
	}
	if (iRv >= 0 && getCWndDcdGrid()->getCustomizeDisplayMode())
	{
		const CustomizeJikokuhyouContent contRessyaIndex = getCentDedDia()->getcontCustomizeRessyaIndex(getRessyahoukou(), aCdXColSpec.getRessyaIndex());
		if (contRessyaIndex.iRessyaIndexCont.empty())
		{
			iRv = -7;	//選択列に列車がありません
		}

	}
	if (iRv >= 0 && !getCWndDcdGrid()->getCustomizeDisplayMode())
	{
		const CentDedRessya* pCentDedRessya = getCentDedRessyaCont()->getMuPtr()->get(aCdXColSpec.getRessyaIndex());
		if (pCentDedRessya->isNull())
		{
			iRv = -2;	//NULL状態の列車です。
		}
		//if (pCentDedRessya->getOperationNumber().empty())
		//{
		//	iRv = -3;	//運用番号がありません。
		//}
	}
	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************

		vector<tstring> strOperationNumber;
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			const CustomizeJikokuhyouContent contRessyaIndex = getCentDedDia()->getcontCustomizeRessyaIndex(getRessyahoukou(), aCdXColSpec.getRessyaIndex());

			//int iOperationNumberReferEki;
			if (aCdYColSpec.isEkiComponent())
			{
				//iOperationNumberReferEki = aCdYColSpec.getEkiOrder();
				for (int idx = 0; idx < (int)contRessyaIndex.iRessyaIndexCont.size(); idx++)
				{
					const CentDedRessya* pCentDedRessya = getCentDedRessyaCont()->getMuPtr()->get(contRessyaIndex.iRessyaIndexCont[idx]);
					if (pCentDedRessya->getValidSihatsuEki() > aCdYColSpec.getEkiOrder())
					{
						strOperationNumber = pCentDedRessya->getOperationNumber(
							pCentDedRessya->getValidSihatsuEki());
						break;
					}
					else if (pCentDedRessya->getValidSyuuchakuEki() >= aCdYColSpec.getEkiOrder())
					{
						strOperationNumber = pCentDedRessya->getOperationNumber(
							aCdYColSpec.getEkiOrder());
						break;
					}
					if (idx == contRessyaIndex.iRessyaIndexCont.size() - 1)
					{
						strOperationNumber = pCentDedRessya->getOperationNumber(
							aCdYColSpec.getEkiOrder());
					}
				}
			}
			else if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku1 ||
				aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku2 ||
				aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_ShuchakuEkimei ||
				aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_Outer_Shuchaku1 ||
				aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_Outer_Shuchaku2)
			{
				const CentDedRessya* pCentDedRessya = getCentDedRessyaCont()->getMuPtr()->get(contRessyaIndex.iRessyaIndexCont.back());
				strOperationNumber = pCentDedRessya->getOperationNumber(
					pCentDedRessya->getValidSyuuchakuEki());
			}
			else
			{
				const CentDedRessya* pCentDedRessya = getCentDedRessyaCont()->getMuPtr()->get(contRessyaIndex.iRessyaIndexCont.front());
				strOperationNumber = pCentDedRessya->getOperationNumber(
					pCentDedRessya->getValidSihatsuEki());
			}

		}
		else
		{
			const CentDedRessya* pCentDedRessya = getCentDedRessyaCont()->getMuPtr()->get(aCdXColSpec.getRessyaIndex());
			int iOperationNumberReferEki = pCentDedRessya->getValidSihatsuEki();
			if (aCdYColSpec.isEkiComponent() &&
				aCdYColSpec.getEkiOrder() > iOperationNumberReferEki)
			{
				iOperationNumberReferEki = aCdYColSpec.getEkiOrder();
			}
			else if (aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku1 ||
				aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku2 ||
				aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_ShuchakuEkimei ||
				aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_Outer_Shuchaku1 ||
				aCdYColSpec.getColumnType() == CdYColSpec::ColumnType_Outer_Shuchaku2)
			{
				iOperationNumberReferEki = pCentDedRessya->getValidSyuuchakuEki();
			}
			strOperationNumber = pCentDedRessya->getOperationNumber(
				iOperationNumberReferEki);
		}
		{
			// --------------------------------
			//	運用表ビューを開く
			// --------------------------------
			//Ver2.0暫定仕様　列車の有効始発駅を発車する段階の運用番号を取得し、
			//その運番に対して、運用表を開く。
			for (int idx = 0; idx < (int)strOperationNumber.size(); idx++)
			{
				if (strOperationNumber[idx].empty())
				{
					continue;
				}
				COperationTableView* pCOperationTableView = NULL;
				if (iRv >= 0)
				{
					COperationTableDoc* pCOperationTableDoc = NULL;
					if (iRv >= 0)
					{
						pCOperationTableDoc =
							getCDiagramEditApp()->openCOperationTableDoc(
								getCentDedDia(),
								strOperationNumber[idx]);
						//if (pCOperationTableView == NULL)
						//{
						//	iRv = -4;	//	運用表ビューのオープンに失敗しました
						//}
					}
					//pCJikokuhyouDoc = 時刻表ドキュメント
					//pCJikokuhyouView = 時刻表ビュー
				}
			}

			//if (iRv >= 0)
			//{
			//	int iEkiOrder = pCentDedRessyaOut->getSihatsuEki();
			//	pCJikokuhyouView->setFocusToRessyaIndex(iRessyaidxOut, iEkiOrder);
			//	iRv = 1;	//	時刻表ビューへ移動しました
			//}

		}

		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************
	}
	return iRv;
}

int CWjkState_Ressyahensyu::OnJikokuhyouOpenEki_Process(BOOL bQueryEnable)
{
	int iRv = 0;
	if (iRv >= 0)
	{
		//	駅プロパティダイアログの使用を判定
		int iRv = execCDlgEkiProp(TRUE);
	}

	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		iRv = execCDlgEkiProp(FALSE);
	}

	return iRv;
}

int CWjkState_Ressyahensyu::OnJikokuhyouOpenEkiJikokuhyou_Process(BOOL bQueryEnable)
{
	int iRv = 0;
	int iEkiIndex = -1;
	CdXColSpec aXColSpecFocus = getCWndDcdGrid()->getXColSpecOfFocus();
	CdYColSpec aYColSpecFocus = getCWndDcdGrid()->getYColSpecOfFocus();
	if (iRv >= 0)
	{
		if ((aXColSpecFocus.getColumnType() ==
				CdXColSpec::ColumnType_Ekimei ||
				aXColSpecFocus.getColumnType() ==
				CdXColSpec::ColumnType_Chakuhatsu) &&
			aYColSpecFocus.getEkiOrder() >= 0)
		{
			const CentDedEkiCont* pCentDedEkiCont =
				getCDiagramEditDoc()->getCDedRosenFileData()
				->getCentDedRosen()->getCentDedEkiCont();
			iEkiIndex = pCentDedEkiCont->EkiOrderOfEkiIndex(
				getCWndDcdGrid()->getRessyahoukou(),
				aYColSpecFocus.getEkiOrder());
		}
		else
		{
			iRv = -1;	//	セルの位置が駅名ではありません。
		}
	}

	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		CEkiJikokuhyouView* pCEkiJikokuhyouView = NULL;
		getCDiagramEditApp()->openCEkiJikokuhyouDoc(
			getCentDedDia(),
			getRessyahoukou(),
			iEkiIndex,
			&pCEkiJikokuhyouView);
	}

	return iRv;
}

int CWjkState_Ressyahensyu::OnJikokuhyouOpenCrossingCheck_Process(BOOL bQueryEnable)
{
	int iRv = 0;
	int iEkiIndex = -1;
	CdXColSpec aXColSpecFocus = getCWndDcdGrid()->getXColSpecOfFocus();
	CdYColSpec aYColSpecFocus = getCWndDcdGrid()->getYColSpecOfFocus();
	if (iRv >= 0)
	{
		if ((aXColSpecFocus.getColumnType() ==
			CdXColSpec::ColumnType_Ekimei ||
			aXColSpecFocus.getColumnType() ==
			CdXColSpec::ColumnType_Chakuhatsu) &&
			aYColSpecFocus.getEkiOrder() >= 0)
		{
			const CentDedEkiCont* pCentDedEkiCont =
				getCDiagramEditDoc()->getCDedRosenFileData()
				->getCentDedRosen()->getCentDedEkiCont();
			iEkiIndex = pCentDedEkiCont->EkiOrderOfEkiIndex(
				getCWndDcdGrid()->getRessyahoukou(),
				aYColSpecFocus.getEkiOrder());
		}
		else
		{
			iRv = -1;	//	セルの位置が駅名ではありません。
		}
	}
	if (iRv >= 0)
	{
		const CentDedEki* pCentDedEki = getCDiagramEditDoc()->getCDedRosenFileData()
			->getCentDedRosen()->getCentDedEkiCont()->getMuPtr()->get(iEkiIndex);
		if (pCentDedEki->getCrossingCheckRuleSize() <= 0)
		{
			iRv = -2;
		}
	}

	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		//CCrossingCheckView* pCrossingCheckView = NULL;
		getCDiagramEditApp()->openCCrossingCheckDoc(
			getCentDedDia(),
			iEkiIndex/*,
			&pCrossingCheckView*/);
	}

	return iRv;
}

int CWjkState_Ressyahensyu::OnJikokuhyouUpdateOperation_Process(BOOL bQueryEnable)
{
	int iRv = 0;
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -2;
		}
	}
	if (iRv >= 0)
	{
		//運用更新抑止中のみコマンドが有効です。
		if (!getCWndDcdGrid()->getOperationUpdateStop())
		{
			iRv = -1;
		}
	}
	if (!bQueryEnable && iRv >= 0)
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
	}
	return iRv;
}

int CWjkState_Ressyahensyu::
OnJikokuhyouRessyaComplementStdOpeTime_Process(BOOL bQueryEnable)
{
	int iRv = 0;
	Ou<EditCmd::CRfEditCmd_Ressya> pCmd;
	Ou<EditCmd::CRfEditCmd_Ressya>* ppCmd = NULL;
	if (!bQueryEnable) { ppCmd = &pCmd; }

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -2;
		}
	}
	if (iRv >= 0)
	{
		if (!getCWndDcdGrid()->createCmd(CWndJikokuhyou::ECreateCmd_Select, ppCmd))
		{
			iRv = -1;	//	列車選択位置が正しくありません。
		}
	}
	CdDedJikokuOrder aCdJikokuOrder;
	int iType = -1;
	if (iRv >= 0)
	{
		aCdJikokuOrder = getCWndDcdGrid()->CdDedJikokuOrderOf(
			getCWndDcdGrid()->getYColSpecOfFocus());
		if (!aCdJikokuOrder.getIsNull())
		{
			//基準運転時分機能&通過駅時刻表示がOFFの場合は、無効
			if (!(getCWndDcdGrid()->getDisplayTsuukaEkiJikoku()) ||
				!(getCWndDcdGrid()->getStandardOperationTimeFunction()))
			{
				iRv = -1;	//	
			}
			else
			{
				iType = 0;
			}
		}
		else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() ==
			CdYColSpec::ColumnType_Track)
		{
			iRv = -1;
			//iType = 1;
		}
		else
		{
			iRv = -1;
		}
	}

	//aCdJikokuOrder = 指定のセルに対応する『時刻Order』
	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		// --------------------------------
		//	コマンドオブジェクトの列車を編集
		// --------------------------------
		if (iType == 0)
		{
			const CentDedRessyaCont* pCentDedRessyaCont = getCentDedRessyaCont();
			Mu<CentDedRessya*>* muCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr();
			for (int i = 0; iRv >= 0 && i < muCentDedRessya->size(); i++)
			{
				CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);

				//Ver2.06.07 基準運転時分取得元ダイヤインデクス機能追加に伴う変更
				int iDiaIndexStandard = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getKijunDiaIndex();
				//基準運転時分取得元ダイヤ以外
				if (getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedDiaCont()->findCentDedDiaByName(
					pCentDedRessyaCont->getDia()->getName()) != iDiaIndexStandard)
				{
					const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki =
						getCDiagramEditDoc()->getCDedRosenFileData()->
						getCentDedRosen()->getCentDedEkiCont()->getMuPtr(
							pCentDedRessya->getRessyahoukou());
					if (aCdJikokuOrder.getEkiOrder() < pCentDedRessya->getSihatsuEki())
					{
						ComplementSihatsuStdOpeTime(
							iDiaIndexStandard,
							aCdJikokuOrder,
							pCentDedRessya,
							muCdDedEki);
					}
					else if (aCdJikokuOrder.getEkiOrder() == pCentDedRessya->getSihatsuEki() &&
							aCdJikokuOrder.getEkiJikokuItem() == CdDedJikokuOrder::EkiJikokuItem_Chaku &&
							muCdDedEki->get(aCdJikokuOrder.getEkiOrder()).isHatsuChakuHyouji() &&
							pCentDedRessya->getCentDedEkiJikoku(aCdJikokuOrder.getEkiOrder()).getChakujikoku().isNull() &&
							!pCentDedRessya->getCentDedEkiJikoku(aCdJikokuOrder.getEkiOrder()).getHatsujikoku().isNull())
					{
						ComplementChakuFromHatsuStdOpeTime(
							iDiaIndexStandard,
							aCdJikokuOrder.getEkiOrder(),
							pCentDedRessya/*,
							muCdDedEki*/);
					}
					else if (aCdJikokuOrder.getEkiOrder() > pCentDedRessya->getSyuuchakuEki() &&
						pCentDedRessya->getSyuuchakuEki() != -1)
					{
						ComplementSyuuchakuStdOpeTime(
							iDiaIndexStandard,
							aCdJikokuOrder,
							pCentDedRessya,
							muCdDedEki);
					}
					else if (aCdJikokuOrder.getEkiOrder() == pCentDedRessya->getSyuuchakuEki() &&
							aCdJikokuOrder.getEkiJikokuItem() == CdDedJikokuOrder::EkiJikokuItem_Hatsu &&
							muCdDedEki->get(aCdJikokuOrder.getEkiOrder()).isHatsuChakuHyouji() &&
							!pCentDedRessya->getCentDedEkiJikoku(aCdJikokuOrder.getEkiOrder()).getChakujikoku().isNull() &&
							pCentDedRessya->getCentDedEkiJikoku(aCdJikokuOrder.getEkiOrder()).getHatsujikoku().isNull() &&
							pCentDedRessya->getSyuuchakuEki() != -1)
					{
						ComplementHatsuFromChakuStdOpeTime(
							iDiaIndexStandard,
							aCdJikokuOrder.getEkiOrder(),
							pCentDedRessya/*,
							muCdDedEki*/);
					}
				}
			}
		}
		//else if (iType == 1)
		//{
		//	ChangeRessyaTrackMain(pCmd->getCaMuiSelect()->getMuPtr());

		//}
		//else if (iType == 3)
		//{
		//	ChangeShihatsuShuchakuOperationJikokuNull(
		//		pCmd->getCaMuiSelect()->getMuPtr());

		//}
		// --------------------------------
		//	コマンドオブジェクトを実行
		// --------------------------------
		{
			getCDiagramEditDoc()->executeEditCmd(pCmd);
		}
		// --------------------------------
		//	フォーカスを移動
		// --------------------------------
		{
			moveFocusCellToNext(false);
		}
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************
	}
	return iRv;
}

int CWjkState_Ressyahensyu::OnJikokuhyouLeft_Process(BOOL bQueryEnable)
{
	int iRv = 0;

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -1;
		}
	}
	int iSelectIndex = -1;
	int iSelectSize = 1;
	if (iRv >= 0)
	{
		CdXColSpec	aXColSpec =
			getCWndDcdGrid()->getXColSpecOfFocus();
		if (aXColSpec.getColumnType() != CdXColSpec::EColumnType::ColumnType_Ressya)
		{
			iRv = -2;
		}
		else if (getCWndDcdGrid()->getCSelect()->getSelectedCellCount() == 0)
		{
			if (aXColSpec.getRessyaIndex() == 0)
			{
				iRv = -3;
			}
			else
			{
				iSelectIndex = aXColSpec.getRessyaIndex();
			}
		}
		else
		{
			/**
				getSelectedCellCountが1以上の場合(ランダム選択)は、連続した選択であるかどうかを調べます。
				(1)Index=0から調べる、getXColumnNumberSelectedがfalseの場合は次へ、
					trueの場合は、iSelectIndexにその列車のRessyaIndexを入れ、bSequentialをtrueにして次へ
					ただし、「左へ」の場合は、RessyaIndexが0の時は無効にする(0だと左には移動できないので)
				(2)bSequentialがtrueの場合、getXColumnNumberSelectedがtrueの場合は次へ、
					falseの場合、iSelectSizeを確定させ、bSequentialをfalseにする。
				(3)iSelectIndexが0以上かつ、bSequentialがfalseの状態で、getXColumnNumberSelectedがtrueの場合は、ランダム選択なのでiRv-で終了。
			
			*/
			CdXColSpecCont aCdXColSpecCont = getCWndDcdGrid()->createXColSpecCont();
			bool bSequential = false;
			for (int iColumnNumber = 0; iColumnNumber < getCWndDcdGrid()->getCXDcdGrid()->getXColumnCount(); iColumnNumber++)
			{
				CdXColSpec aCdXColSpec = aCdXColSpecCont.ColumnNumberToSpec(iColumnNumber);
				if (getCWndDcdGrid()->getCSelect()->getXColumnNumberSelected(iColumnNumber))
				{
					if (aCdXColSpec.getColumnType() == CdXColSpec::ColumnType_Ressya)
					{
						if (iSelectIndex < 0)
						{
							if (aCdXColSpec.getRessyaIndex() == 0)
							{
								iRv = -5;
								break;
							}
							iSelectIndex = aCdXColSpec.getRessyaIndex();
							bSequential = true;
						}
						else if(!bSequential)
						{
							iRv = -4;
							break;
						}
					}
				}
				else if (bSequential)
				{
					if (aCdXColSpec.getColumnType() == CdXColSpec::ColumnType_Ressya)
					{
						iSelectSize = aCdXColSpec.getRessyaIndex() - iSelectIndex;
					}
					else
					{
						iSelectSize = getCentDedRessyaCont()->size() - iSelectIndex;
					}
					bSequential = false;
				}
			}
		}
	}
	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************

		// --------------------------------
		//	コマンドを生成・実行
		// --------------------------------
		{
			OuNew<CRfEditCmd> pCmd(
				new CRfEditCmd_RessyaSwap(
					GetDocument()->getDiaIndex(),
					getRessyahoukou(),
					iSelectIndex,
					iSelectSize,
					iSelectIndex - 1));
			getCDiagramEditDoc()->executeEditCmd(pCmd);
		}

		// --------------------------------
		//	フォーカス位置を移動
		// --------------------------------
		{
			CDcdGridCell* pCell =
			getCWndDcdGrid()->getCXDcdGrid()->calcMovedCell(
				getCWndDcdGrid()->getCFocus()->getFocusCell(),
				-1,
				0);
			if (pCell) 
			{
				getCWndDcdGrid()->getCFocus()->setFocusCell(pCell);
			}
			if (iSelectSize > 1)
			{
				CdXColSpecCont aCdXColSpecCont = getCWndDcdGrid()->createXColSpecCont();
				int iSelectColumnNumber = aCdXColSpecCont.getColumnNumber_Ressya_begin() + iSelectIndex - 1;
				for (int iOffset = 0; iOffset < iSelectSize; iOffset++)
				{
					getCWndDcdGrid()->getCSelect()->setXColumnNumberSelected(iSelectColumnNumber + iOffset, true);
				}
			}
		}

	}
	return iRv;
}

int CWjkState_Ressyahensyu::OnJikokuhyouRight_Process(BOOL bQueryEnable)
{
	int iRv = 0;

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -1;
		}
	}
	int iSelectIndex = -1;
	int iSelectSize = 1;
	if (iRv >= 0)
	{
		CdXColSpec	aXColSpec =
			getCWndDcdGrid()->getXColSpecOfFocus();
		if (aXColSpec.getColumnType() != CdXColSpec::EColumnType::ColumnType_Ressya)
		{
			iRv = -2;
		}
		else if (getCWndDcdGrid()->getCSelect()->getSelectedCellCount() == 0)
		{
			if (aXColSpec.getRessyaIndex() >= getCentDedRessyaCont()->size() - 1)
			{
				iRv = -3;
			}
			else
			{
				iSelectIndex = aXColSpec.getRessyaIndex();
			}
		}
		else
		{
			/**
				getSelectedCellCountが1以上の場合(ランダム選択)は、連続した選択であるかどうかを調べます。
				(1)Index=0から調べる、getXColumnNumberSelectedがfalseの場合は次へ、
					trueの場合は、iSelectIndexにその列車のRessyaIndexを入れ、bSequentialをtrueにして次へ
				(2)bSequentialがtrueの場合、getXColumnNumberSelectedがtrueの場合は次へ、
					falseの場合、iSelectSizeを確定させ、bSequentialをfalseにする。
					ただし、「右へ」の場合は、最終要素が列車末尾の場合（＝falseになった列が新規列車列)は、右へ移動できないので無効になる(iRv-)
				(3)iSelectIndexが0以上かつ、bSequentialがfalseの状態で、getXColumnNumberSelectedがtrueの場合は、ランダム選択なのでiRv-で終了。

			*/
			CdXColSpecCont aCdXColSpecCont = getCWndDcdGrid()->createXColSpecCont();
			bool bSequential = false;
			for (int iColumnNumber = 0; iColumnNumber < getCWndDcdGrid()->getCXDcdGrid()->getXColumnCount(); iColumnNumber++)
			{
				CdXColSpec aCdXColSpec = aCdXColSpecCont.ColumnNumberToSpec(iColumnNumber);
				if (getCWndDcdGrid()->getCSelect()->getXColumnNumberSelected(iColumnNumber))
				{
					if (aCdXColSpec.getColumnType() == CdXColSpec::ColumnType_Ressya)
					{
						if (iSelectIndex < 0)
						{
							iSelectIndex = aCdXColSpec.getRessyaIndex();
							bSequential = true;
						}
						else if (!bSequential)
						{
							iRv = -4;
							break;
						}
					}
				}
				else if (bSequential)
				{
					if (aCdXColSpec.getColumnType() == CdXColSpec::ColumnType_Ressya)
					{
						iSelectSize = aCdXColSpec.getRessyaIndex() - iSelectIndex;
					}
					else
					{
						iRv = -5;
						break;
						//iSelectSize = getCentDedRessyaCont()->size() - iSelectIndex;
					}
					bSequential = false;
				}
			}
		}
	}
	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************

		// --------------------------------
		//	コマンドを生成・実行
		// --------------------------------
		{
			OuNew<CRfEditCmd> pCmd(
				new CRfEditCmd_RessyaSwap(
					GetDocument()->getDiaIndex(),
					getRessyahoukou(),
					iSelectIndex,
					iSelectSize,
					iSelectIndex + iSelectSize));
			getCDiagramEditDoc()->executeEditCmd(pCmd);
		}

		// --------------------------------
		//	フォーカス位置を移動
		// --------------------------------
		{
			CDcdGridCell* pCell =
				getCWndDcdGrid()->getCXDcdGrid()->calcMovedCell(
					getCWndDcdGrid()->getCFocus()->getFocusCell(),
					+1,
					0);
			if (pCell)
			{
				getCWndDcdGrid()->getCFocus()->setFocusCell(pCell);
			}
			if (iSelectSize > 1)
			{
				CdXColSpecCont aCdXColSpecCont = getCWndDcdGrid()->createXColSpecCont();
				int iSelectColumnNumber = aCdXColSpecCont.getColumnNumber_Ressya_begin() + iSelectIndex + 1;
				for (int iOffset = 0; iOffset < iSelectSize; iOffset++)
				{
					getCWndDcdGrid()->getCSelect()->setXColumnNumberSelected(iSelectColumnNumber + iOffset, true);
				}
			}
		}
	}
	return iRv;
}

int CWjkState_Ressyahensyu
::OnJikokuhyouCanceled_Process(BOOL bQueryEnable)
{
	int iRv = 0;
	Ou<EditCmd::CRfEditCmd_Ressya> pCmd;
	Ou<EditCmd::CRfEditCmd_Ressya>* ppCmd = NULL;
	if (!bQueryEnable) { ppCmd = &pCmd; }

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (iRv >= 0)
	{
		if (getCWndDcdGrid()->getCustomizeDisplayMode())
		{
			iRv = -2;
		}
	}
	if (iRv >= 0)
	{
		if (!getCWndDcdGrid()->createCmd(CWndJikokuhyou::ECreateCmd_Select, ppCmd))
		{
			iRv = -1;	//	列車選択位置が正しくありません。
		}
	}
	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドの実行
		// ****************************************************************
		// --------------------------------
		//	コマンドオブジェクトの列車を編集
		// --------------------------------
		Mu<CentDedRessya*>* muCentDedRessya = pCmd->getCaMuiSelect()->getMuPtr();

		for (int i = 0; iRv >= 0 && i < muCentDedRessya->size(); i++)
		{
			CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);

			pCentDedRessya->setIsCanceled(!pCentDedRessya->isCanceled());
		}
		// --------------------------------
		//	コマンドオブジェクトを実行
		// --------------------------------
		{
			getCDiagramEditDoc()->executeEditCmd(pCmd);
		}
		// --------------------------------
		//	フォーカスを移動
		// --------------------------------
		if (iRv >= 0)
		{
			moveFocusCellToNext(true);
		}
	}
	return iRv;

}



void CWjkState_Ressyahensyu::ChangeRessyaTrackNext(Mu<CentDedRessya*>* muCentDedRessya)
{
	int iEkiOrder = getCWndDcdGrid()->getYColSpecOfFocus().getEkiOrder();
	for (int i = 0;  i < muCentDedRessya->size(); i++)
	{
		CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);
		CentDedEkiJikoku* pCentDedEkiJikoku =
			pCentDedRessya->getCentDedEkiJikokuCont()->getMuPtr()->get(iEkiOrder);
		if (pCentDedEkiJikoku->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_None)
		{
			continue;
		}

		const CentDedEkiCont::CdDedEki aCdDedEki =
			getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont()
			->getMuPtr(pCentDedRessya->getRessyahoukou())->get(iEkiOrder);
		CentDedEkiTrack2Cont aCentDedEkiTrack2Cont = aCdDedEki.getCentDedEkiTrack2Cont();

		//番線を一つずらす
		if (pCentDedEkiJikoku->getRessyaTrackIndex() < aCentDedEkiTrack2Cont.size() - 1)
		{
			pCentDedEkiJikoku->setRessyaTrackIndex(pCentDedEkiJikoku->getRessyaTrackIndex() + 1);
		}
		else
		{
			pCentDedEkiJikoku->setRessyaTrackIndex(0);
		}
		AdjustBrunchLoop(
			iEkiOrder,
			pCentDedRessya,
			1);
	}
}

void CWjkState_Ressyahensyu::ChangeRessyaTrackPrev(Mu<CentDedRessya*>* muCentDedRessya)
{
	int iEkiOrder = getCWndDcdGrid()->getYColSpecOfFocus().getEkiOrder();
	for (int i = 0; i < muCentDedRessya->size(); i++)
	{
		CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);
		CentDedEkiJikoku* pCentDedEkiJikoku =
			pCentDedRessya->getCentDedEkiJikokuCont()->getMuPtr()->get(iEkiOrder);
		if (pCentDedEkiJikoku->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_None)
		{
			continue;
		}

		const CentDedEkiCont::CdDedEki aCdDedEki =
			getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont()
			->getMuPtr(pCentDedRessya->getRessyahoukou())->get(iEkiOrder);
		CentDedEkiTrack2Cont aCentDedEkiTrack2Cont = aCdDedEki.getCentDedEkiTrack2Cont();

		//番線を一つずらす
		if (pCentDedEkiJikoku->getRessyaTrackIndex() == 0)
		{
			pCentDedEkiJikoku->setRessyaTrackIndex(aCentDedEkiTrack2Cont.size() - 1);
		}
		else
		{
			pCentDedEkiJikoku->setRessyaTrackIndex(pCentDedEkiJikoku->getRessyaTrackIndex() - 1);
		}
		AdjustBrunchLoop(
			iEkiOrder,
			pCentDedRessya,
			1);

	}
}


void CWjkState_Ressyahensyu::ChangeRessyaTrackMain(Mu<CentDedRessya*>* muCentDedRessya)
{
	int iEkiOrder = getCWndDcdGrid()->getYColSpecOfFocus().getEkiOrder();
	for (int i = 0; i < muCentDedRessya->size(); i++)
	{
		CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);
		CentDedEkiJikoku* pCentDedEkiJikoku =
			pCentDedRessya->getCentDedEkiJikokuCont()->getMuPtr()->get(iEkiOrder);
		if (pCentDedEkiJikoku->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_None)
		{
			continue;
		}

		int iStandardRessyaTrackIndex[2] = { 0,0 };

		int iRessyasyubetsuIndex = pCentDedRessya->getRessyasyubetsuIndex();
		getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
			->StandardRessyaTrackIndexSearch(
				iRessyasyubetsuIndex,
				getRessyahoukou(),
				iEkiOrder,
				iStandardRessyaTrackIndex);

		int iEkiAtsukai = 0;
		if (pCentDedEkiJikoku->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka)
		{
			iEkiAtsukai = 1;
		}
		pCentDedEkiJikoku->setRessyaTrackIndex(iStandardRessyaTrackIndex[iEkiAtsukai]);

		AdjustBrunchLoop(
			iEkiOrder,
			pCentDedRessya,
			1);
	}
}

void CWjkState_Ressyahensyu::ChangeShihatsuShuchakuOperationTypeNext(
	Mu<CentDedRessya*>* muCentDedRessya)
{
	for (int i = 0; i < muCentDedRessya->size(); i++)
	{
		CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);
		if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore1)
		{
			int iEkiOrder = -1;
			if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu1)
			{
				iEkiOrder = pCentDedRessya->getValidSihatsuEki();
			}
			else
			{
				iEkiOrder = getCWndDcdGrid()->getYColSpecOfFocus().getEkiOrder();
			}
			if (iEkiOrder == -1)
			{
				continue;
			}

			CentDedBeforeOperation* pFirstOperation = NULL;
			CentDedBeforeOperationCont* pBeforeOperationCont = NULL;
			if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu1)
			{
				pBeforeOperationCont = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iEkiOrder)->getCentDedBeforeOperationCont();
			}
			else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore1)
			{
				CentDedBeforeOperationCont* pBeforeContTemp = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iEkiOrder)->getCentDedBeforeOperationCont();
				for (int idx = pBeforeContTemp->size() - 1; idx >= 0; idx--)
				{
					if (pBeforeContTemp->get(idx).getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
					{
						pBeforeOperationCont = pBeforeContTemp->getMuPtr()->get(idx)->getCentDedBeforeOperationCont();
						break;
					}
				}
			}
			else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore1)
			{
				CentDedAfterOperationCont* pAfterContTemp = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iEkiOrder)->getCentDedAfterOperationCont();
				for (int idx = 0; idx < pAfterContTemp->size(); idx++)
				{
					if (pAfterContTemp->get(idx).getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
					{
						pBeforeOperationCont = pAfterContTemp->getMuPtr()->get(idx)->getCentDedBeforeOperationCont();
						break;
					}
				}
			}
			if(pBeforeOperationCont == NULL)
			{
				continue;
			}

			pFirstOperation= pBeforeOperationCont->getMuPtr()->get(0);
			if (pFirstOperation == NULL)
			{
				continue;
			}

			if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Junction)
			{
				CdDedJikoku aJikoku = pFirstOperation->getOriginJikoku();
				for (int idxb = 0; idxb < pBeforeOperationCont->size() && aJikoku.isNull(); idxb++)
				{
					const CentDedBeforeOperation* pBeforeOperation = pBeforeOperationCont->getMuPtr()->get(idxb);
					if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
					{
						aJikoku = pBeforeOperation->getOperationHatsuJikoku();
					}
					else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
					{
						aJikoku = pBeforeOperation->getConnectJikoku();
					}
					else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
					{
						aJikoku = pBeforeOperation->getReleaseJikoku();
					}
				}

				if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu1 &&
					aJikoku.isNull())
				{
					CentDedAfterOperationCont* pAfterOperationCont = pCentDedRessya->getCentDedEkiJikokuCont()
						->getMuPtr()->get(iEkiOrder)->getCentDedAfterOperationCont();
					for (int idxa = 0; idxa < pAfterOperationCont->size() && aJikoku.isNull(); idxa++)
					{
						const CentDedAfterOperation* pAfterOperation = pAfterOperationCont->getMuPtr()->get(idxa);
						if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
						{
							aJikoku = pAfterOperation->getOperationHatsuJikoku();
						}
						else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
						{
							aJikoku = pAfterOperation->getConnectJikoku();
						}
						else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
						{
							aJikoku = pAfterOperation->getReleaseJikoku();
						}
					}
					if (aJikoku.isNull())
					{
						aJikoku = pCentDedRessya->getCentDedEkiJikokuCont()
							->getMuPtr()->get(iEkiOrder)->getHatsujikoku();
					}
				}
				else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore1 &&
					aJikoku.isNull())
				{
					const CentDedBeforeOperation* pConnectOperation = pBeforeOperationCont->getBeforeOperation();
					aJikoku = pConnectOperation->getConnectJikoku();
				}
				else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore1 &&
					aJikoku.isNull())
				{
					const CentDedAfterOperation* pConnectOperation = pBeforeOperationCont->getAfterOperation();
					aJikoku = pConnectOperation->getConnectJikoku();
				}

				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(-60);
					CentDedBeforeOperation aBeforeOperation(
						CentDedBeforeOperation::EBOperation::BOperation_Out,
						aJikoku,
						pFirstOperation->getOperationNumberTemp(),
						tstring());
					pBeforeOperationCont->set(aBeforeOperation, 0);
				}

			}
			else if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Out)
			{
				vector<vector<int>> iOuterTerminalJikan;

				getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
					->StandardOuterTerminalJikanSearch(
						pCentDedRessya->getRessyasyubetsuIndex(),
						getRessyahoukou(),
						-1,
						iEkiOrder,
						iOuterTerminalJikan);
				bool bSet = false;
				for (int idx = 0; idx < (int)iOuterTerminalJikan.size() && !bSet; idx++)
				{
					if (iOuterTerminalJikan[idx][0] != 0)
					{
						CdDedJikoku aOuterShihatsuJikoku;
						CdDedJikoku aChakuJikoku;
						if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu1)
						{
							aOuterShihatsuJikoku = pCentDedRessya->getCentDedEkiJikokuCont()
								->getMuPtr()->get(iEkiOrder)->getHatsujikoku();
						}
						else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore1)
						{
							const CentDedBeforeOperation* pConnectOperation = pBeforeOperationCont->getBeforeOperation();
							aOuterShihatsuJikoku = pConnectOperation->getConnectJikoku();
						}
						else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore1)
						{
							const CentDedAfterOperation* pConnectOperation = pBeforeOperationCont->getAfterOperation();
							aOuterShihatsuJikoku = pConnectOperation->getConnectJikoku();
						}
						if (!aOuterShihatsuJikoku.isNull())
						{
							aChakuJikoku = aOuterShihatsuJikoku;
							aOuterShihatsuJikoku.addSeconds(-(iOuterTerminalJikan[idx][0]));
							aChakuJikoku.addSeconds(-(iOuterTerminalJikan[idx][1]));

							CentDedBeforeOperation aBeforeOperation(
								CentDedBeforeOperation::EBOperation::BOperation_Outer,
								idx,
								aOuterShihatsuJikoku,
								aChakuJikoku,
								pFirstOperation->getOperationNumberOriginal(),
								pFirstOperation->getInOutLinkCode());
							pBeforeOperationCont->set(aBeforeOperation, 0);

							bSet = true;
						}
						break;
					}
				}
				if (!bSet)
				{
					CentDedBeforeOperation aBeforeOperation(
						CentDedBeforeOperation::EBOperation::BOperation_Junction,
						CdDedJikoku(),
						vector<tstring>());
					pBeforeOperationCont->set(aBeforeOperation, 0);
				}

			}
			else if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
			{
				CentDedBeforeOperation aBeforeOperation(
					CentDedBeforeOperation::EBOperation::BOperation_Junction,
					CdDedJikoku(),
					vector<tstring>());
				pBeforeOperationCont->set(aBeforeOperation, 0);
			}
		}
		else//終着作業
		{
			int iEkiOrder = -1;
			if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku1)
			{
				iEkiOrder = pCentDedRessya->getValidSyuuchakuEki();
			}
			else
			{
				iEkiOrder = getCWndDcdGrid()->getYColSpecOfFocus().getEkiOrder();
			}
			if (iEkiOrder == -1)
			{
				continue;
			}

			CentDedAfterOperation* pLastOperation = NULL;
			CentDedAfterOperationCont* pAfterOperationCont = NULL;
			if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku1)
			{
				pAfterOperationCont = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iEkiOrder)->getCentDedAfterOperationCont();
			}
			else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter1)
			{
				CentDedBeforeOperationCont* pBeforeCont = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iEkiOrder)->getCentDedBeforeOperationCont();
				for (int idx = pBeforeCont->size() - 1; idx >= 0; idx--)
				{
					if (pBeforeCont->get(idx).getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
					{
						pAfterOperationCont = pBeforeCont->getMuPtr()->get(idx)->getCentDedAfterOperationCont();
						break;
					}
				}
			}
			else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter1)
			{
				CentDedAfterOperationCont* pAfterCont = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iEkiOrder)->getCentDedAfterOperationCont();
				for (int idx = 0; idx < pAfterCont->size(); idx++)
				{
					if (pAfterCont->get(idx).getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
					{
						pAfterOperationCont = pAfterCont->getMuPtr()->get(idx)->getCentDedAfterOperationCont();
						break;
					}
				}
			}
			if (pAfterOperationCont == NULL)
			{
				continue;
			}

			pLastOperation = pAfterOperationCont->getMuPtr()->get(INT_MAX);

			if (pLastOperation == NULL)
			{
				continue;
			}

			if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Junction)
			{
				CdDedJikoku aJikoku = pLastOperation->getTerminalJikoku();
				for (int idxa = pAfterOperationCont->size() - 1; idxa >= 0 && aJikoku.isNull(); idxa--)
				{
					const CentDedAfterOperation* pAfterOperation = pAfterOperationCont->getMuPtr()->get(idxa);
					if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
					{
						aJikoku = pAfterOperation->getOperationChakuJikoku(true);
					}
					else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
					{
						aJikoku = pAfterOperation->getConnectJikoku();
					}
					else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
					{
						aJikoku = pAfterOperation->getReleaseJikoku();
					}
				}
				if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku1 &&
					aJikoku.isNull())
				{
					CentDedBeforeOperationCont* pBeforeOperationCont = pCentDedRessya->getCentDedEkiJikokuCont()
						->getMuPtr()->get(iEkiOrder)->getCentDedBeforeOperationCont();
					for (int idxb = pBeforeOperationCont->size() - 1; idxb >= 0 && aJikoku.isNull(); idxb--)
					{
						const CentDedBeforeOperation* pBeforeOperation = pBeforeOperationCont->getMuPtr()->get(idxb);
						if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
						{
							aJikoku = pBeforeOperation->getOperationChakuJikoku(true);
						}
						else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
						{
							aJikoku = pBeforeOperation->getConnectJikoku();
						}
						else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
						{
							aJikoku = pBeforeOperation->getReleaseJikoku();
						}
					}
					if (aJikoku.isNull())
					{
						aJikoku = pCentDedRessya->getCentDedEkiJikokuCont()
							->getMuPtr()->get(iEkiOrder)->getChakujikoku();
					}
				}
				else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter1 &&
					aJikoku.isNull())
				{
					const CentDedBeforeOperation* pReleaseOperation = pAfterOperationCont->getBeforeOperation();
					aJikoku = pReleaseOperation->getReleaseJikoku();
				}
				else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter1 &&
					aJikoku.isNull())
				{
					const CentDedAfterOperation* pReleaseOperation = pAfterOperationCont->getAfterOperation();
					aJikoku = pReleaseOperation->getReleaseJikoku();
				}

				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(60);
					CentDedAfterOperation aAfterOperation(
						CentDedAfterOperation::EAOperation::AOperation_In,
						aJikoku,
						tstring());
					pAfterOperationCont->set(aAfterOperation, INT_MAX);
				}
			}
			else if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_In)
			{
				vector<vector<int>> iOuterTerminalJikan;

				getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
					->StandardOuterTerminalJikanSearch(
						pCentDedRessya->getRessyasyubetsuIndex(),
						getRessyahoukou(),
						iEkiOrder,
						-1,
						iOuterTerminalJikan);
				bool bSet = false;
				for (int idx = 0; idx < (int)iOuterTerminalJikan.size() && !bSet; idx++)
				{
					if (iOuterTerminalJikan[idx][0] != 0)
					{
						CdDedJikoku aHatsuJikoku;
						CdDedJikoku aOuterSyuchakuJikoku;
						if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku1)
						{
							aHatsuJikoku = pCentDedRessya->getCentDedEkiJikokuCont()
								->getMuPtr()->get(iEkiOrder)->getChakujikoku();
						}
						else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter1)
						{
							const CentDedBeforeOperation* pReleaseOperation = pAfterOperationCont->getBeforeOperation();
							aHatsuJikoku = pReleaseOperation->getReleaseJikoku();
						}
						else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter1)
						{
							const CentDedAfterOperation* pReleaseOperation = pAfterOperationCont->getAfterOperation();
							aHatsuJikoku = pReleaseOperation->getReleaseJikoku();
						}
						if (!aHatsuJikoku.isNull())
						{
							aOuterSyuchakuJikoku = aHatsuJikoku;
							aHatsuJikoku.addSeconds(iOuterTerminalJikan[idx][1]);
							aOuterSyuchakuJikoku.addSeconds(iOuterTerminalJikan[idx][0]);

							CentDedAfterOperation aAfterOperation(
								CentDedAfterOperation::EAOperation::AOperation_Outer,
								idx,
								aHatsuJikoku,
								aOuterSyuchakuJikoku,
								pLastOperation->getInOutLinkCode());
							pAfterOperationCont->set(aAfterOperation, INT_MAX);

							bSet = true;

						}
						break;
					}
				}
				if (!bSet)
				{
					CentDedAfterOperation aAfterOperation(
						CentDedAfterOperation::EAOperation::AOperation_Junction,
						CdDedJikoku(),
						0);
					pAfterOperationCont->set(aAfterOperation, INT_MAX);
				}
			}
			else if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
			{
				CentDedAfterOperation aAfterOperation(
					CentDedAfterOperation::EAOperation::AOperation_Junction,
					CdDedJikoku(),
					0);
				pAfterOperationCont->set(aAfterOperation, INT_MAX);
			}
		}
	}
}

void CWjkState_Ressyahensyu::ChangeShihatsuShuchakuOperationTypePrev(
	Mu<CentDedRessya*>* muCentDedRessya)
{
	for (int i = 0; i < muCentDedRessya->size(); i++)
	{
		CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);
		if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore1)
		{
			int iEkiOrder = -1;
			if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu1)
			{
				iEkiOrder = pCentDedRessya->getValidSihatsuEki();
			}
			else
			{
				iEkiOrder = getCWndDcdGrid()->getYColSpecOfFocus().getEkiOrder();
			}
			if (iEkiOrder == -1)
			{
				continue;
			}

			CentDedBeforeOperation* pFirstOperation = NULL;
			CentDedBeforeOperationCont* pBeforeOperationCont = NULL;
			if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu1)
			{
				pBeforeOperationCont = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iEkiOrder)->getCentDedBeforeOperationCont();
			}
			else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore1)
			{
				CentDedBeforeOperationCont* pBeforeContTemp = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iEkiOrder)->getCentDedBeforeOperationCont();
				for (int idx = pBeforeContTemp->size() - 1; idx >= 0; idx--)
				{
					if (pBeforeContTemp->get(idx).getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
					{
						pBeforeOperationCont = pBeforeContTemp->getMuPtr()->get(idx)->getCentDedBeforeOperationCont();
						break;
					}
				}
			}
			else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore1)
			{
				CentDedAfterOperationCont* pAfterContTemp = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iEkiOrder)->getCentDedAfterOperationCont();
				for (int idx = 0; idx < pAfterContTemp->size(); idx++)
				{
					if (pAfterContTemp->get(idx).getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
					{
						pBeforeOperationCont = pAfterContTemp->getMuPtr()->get(idx)->getCentDedBeforeOperationCont();
						break;
					}
				}
			}
			if (pBeforeOperationCont == NULL)
			{
				continue;
			}

			pFirstOperation = pBeforeOperationCont->getMuPtr()->get(0);
			if (pFirstOperation == NULL)
			{
				continue;
			}

			if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Junction)
			{
				vector<vector<int>> iOuterTerminalJikan;

				getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
					->StandardOuterTerminalJikanSearch(
						pCentDedRessya->getRessyasyubetsuIndex(),
						getRessyahoukou(),
						-1,
						iEkiOrder,
						iOuterTerminalJikan);
				bool bSet = false;
				for (int idx = 0; idx < (int)iOuterTerminalJikan.size() && !bSet; idx++)
				{
					if (iOuterTerminalJikan[idx][0] != 0)
					{
						CdDedJikoku aOuterShihatsuJikoku;
						CdDedJikoku aChakuJikoku;
						if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu1)
						{
							aOuterShihatsuJikoku = pCentDedRessya->getCentDedEkiJikokuCont()
								->getMuPtr()->get(iEkiOrder)->getHatsujikoku();
						}
						else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore1)
						{
							const CentDedBeforeOperation* pConnectOperation = pBeforeOperationCont->getBeforeOperation();
							aOuterShihatsuJikoku = pConnectOperation->getConnectJikoku();
						}
						else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore1)
						{
							const CentDedAfterOperation* pConnectOperation = pBeforeOperationCont->getAfterOperation();
							aOuterShihatsuJikoku = pConnectOperation->getConnectJikoku();
						}
						if (!aOuterShihatsuJikoku.isNull())
						{
							aChakuJikoku = aOuterShihatsuJikoku;
							aOuterShihatsuJikoku.addSeconds(-(iOuterTerminalJikan[idx][0]));
							aChakuJikoku.addSeconds(-(iOuterTerminalJikan[idx][1]));

							CentDedBeforeOperation aBeforeOperation(
								CentDedBeforeOperation::EBOperation::BOperation_Outer,
								idx,
								aOuterShihatsuJikoku,
								aChakuJikoku,
								pFirstOperation->getOperationNumberTemp(),
								tstring());
							pBeforeOperationCont->set(aBeforeOperation, 0);

							bSet = true;
						}
						break;
					}
				}
				if (!bSet)
				{
					CdDedJikoku aJikoku = pFirstOperation->getOriginJikoku();
					for (int idxb = 0; idxb < pBeforeOperationCont->size() && aJikoku.isNull(); idxb++)
					{
						const CentDedBeforeOperation* pBeforeOperation = pBeforeOperationCont->getMuPtr()->get(idxb);
						if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
						{
							aJikoku = pBeforeOperation->getOperationHatsuJikoku();
						}
						else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
						{
							aJikoku = pBeforeOperation->getConnectJikoku();
						}
						else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
						{
							aJikoku = pBeforeOperation->getReleaseJikoku();
						}
					}

					if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu1 &&
						aJikoku.isNull())
					{
						CentDedAfterOperationCont* pAfterOperationCont = pCentDedRessya->getCentDedEkiJikokuCont()
							->getMuPtr()->get(iEkiOrder)->getCentDedAfterOperationCont();
						for (int idxa = 0; idxa < pAfterOperationCont->size() && aJikoku.isNull(); idxa++)
						{
							const CentDedAfterOperation* pAfterOperation = pAfterOperationCont->getMuPtr()->get(idxa);
							if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
							{
								aJikoku = pAfterOperation->getOperationHatsuJikoku();
							}
							else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
							{
								aJikoku = pAfterOperation->getConnectJikoku();
							}
							else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
							{
								aJikoku = pAfterOperation->getReleaseJikoku();
							}
						}
						if (aJikoku.isNull())
						{
							aJikoku = pCentDedRessya->getCentDedEkiJikokuCont()
								->getMuPtr()->get(iEkiOrder)->getHatsujikoku();
						}
					}
					else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore1 &&
						aJikoku.isNull())
					{
						const CentDedBeforeOperation* pConnectOperation = pBeforeOperationCont->getBeforeOperation();
						aJikoku = pConnectOperation->getConnectJikoku();
					}
					else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore1 &&
						aJikoku.isNull())
					{
						const CentDedAfterOperation* pConnectOperation = pBeforeOperationCont->getAfterOperation();
						aJikoku = pConnectOperation->getConnectJikoku();
					}

					if (!aJikoku.isNull())
					{
						aJikoku.addSeconds(-60);
						CentDedBeforeOperation aBeforeOperation(
							CentDedBeforeOperation::EBOperation::BOperation_Out,
							aJikoku,
							pFirstOperation->getOperationNumberTemp(),
							tstring());
						pBeforeOperationCont->set(aBeforeOperation, 0);
					}
				}
			}
			else if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Out)
			{
				CentDedBeforeOperation aBeforeOperation(
					CentDedBeforeOperation::EBOperation::BOperation_Junction,
					CdDedJikoku(),
					vector<tstring>());
				pBeforeOperationCont->set(aBeforeOperation, 0);
			}
			else if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
			{
				CdDedJikoku aJikoku = pFirstOperation->getChakuJikoku();
				for (int idxb = 0; idxb < pBeforeOperationCont->size() && aJikoku.isNull(); idxb++)
				{
					const CentDedBeforeOperation* pBeforeOperation = pBeforeOperationCont->getMuPtr()->get(idxb);
					if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
					{
						aJikoku = pBeforeOperation->getOperationHatsuJikoku();
					}
					else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
					{
						aJikoku = pBeforeOperation->getConnectJikoku();
					}
					else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
					{
						aJikoku = pBeforeOperation->getReleaseJikoku();
					}
				}

				if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu1 &&
					aJikoku.isNull())
				{
					CentDedAfterOperationCont* pAfterOperationCont = pCentDedRessya->getCentDedEkiJikokuCont()
						->getMuPtr()->get(iEkiOrder)->getCentDedAfterOperationCont();
					for (int idxa = 0; idxa < pAfterOperationCont->size() && aJikoku.isNull(); idxa++)
					{
						const CentDedAfterOperation* pAfterOperation = pAfterOperationCont->getMuPtr()->get(idxa);
						if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
						{
							aJikoku = pAfterOperation->getOperationHatsuJikoku();
						}
						else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
						{
							aJikoku = pAfterOperation->getConnectJikoku();
						}
						else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
						{
							aJikoku = pAfterOperation->getReleaseJikoku();
						}
					}
					if (aJikoku.isNull())
					{
						aJikoku = pCentDedRessya->getCentDedEkiJikokuCont()
							->getMuPtr()->get(iEkiOrder)->getHatsujikoku();
					}
				}
				else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore1 &&
					aJikoku.isNull())
				{
					const CentDedBeforeOperation* pConnectOperation = pBeforeOperationCont->getBeforeOperation();
					aJikoku = pConnectOperation->getConnectJikoku();
				}
				else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore1 &&
					aJikoku.isNull())
				{
					const CentDedAfterOperation* pConnectOperation = pBeforeOperationCont->getAfterOperation();
					aJikoku = pConnectOperation->getConnectJikoku();
				}

				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(-60);
					CentDedBeforeOperation aBeforeOperation(
						CentDedBeforeOperation::EBOperation::BOperation_Out,
						aJikoku,
						pFirstOperation->getOperationNumberOriginal(),
						pFirstOperation->getInOutLinkCode());
					pBeforeOperationCont->set(aBeforeOperation, 0);
				}

			}
		}
		else//終着作業
		{
			int iEkiOrder = -1;
			if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku1)
			{
				iEkiOrder = pCentDedRessya->getValidSyuuchakuEki();
			}
			else
			{
				iEkiOrder = getCWndDcdGrid()->getYColSpecOfFocus().getEkiOrder();
			}
			if (iEkiOrder == -1)
			{
				continue;
			}

			CentDedAfterOperation* pLastOperation = NULL;
			CentDedAfterOperationCont* pAfterOperationCont = NULL;
			if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku1)
			{
				pAfterOperationCont = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iEkiOrder)->getCentDedAfterOperationCont();
			}
			else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter1)
			{
				CentDedBeforeOperationCont* pBeforeCont = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iEkiOrder)->getCentDedBeforeOperationCont();
				for (int idx = pBeforeCont->size() - 1; idx >= 0; idx--)
				{
					if (pBeforeCont->get(idx).getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
					{
						pAfterOperationCont = pBeforeCont->getMuPtr()->get(idx)->getCentDedAfterOperationCont();
						break;
					}
				}
			}
			else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter1)
			{
				CentDedAfterOperationCont* pAfterCont = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iEkiOrder)->getCentDedAfterOperationCont();
				for (int idx = 0; idx < pAfterCont->size(); idx++)
				{
					if (pAfterCont->get(idx).getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
					{
						pAfterOperationCont = pAfterCont->getMuPtr()->get(idx)->getCentDedAfterOperationCont();
						break;
					}
				}
			}
			if (pAfterOperationCont == NULL)
			{
				continue;
			}

			pLastOperation = pAfterOperationCont->getMuPtr()->get(INT_MAX);

			if (pLastOperation == NULL)
			{
				continue;
			}
			if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Junction)
			{
				vector<vector<int>> iOuterTerminalJikan;

				getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
					->StandardOuterTerminalJikanSearch(
						pCentDedRessya->getRessyasyubetsuIndex(),
						getRessyahoukou(),
						iEkiOrder,
						-1,
						iOuterTerminalJikan);
				bool bSet = false;
				for (int idx = 0; idx < (int)iOuterTerminalJikan.size() && !bSet; idx++)
				{
					if (iOuterTerminalJikan[idx][0] != 0)
					{
						CdDedJikoku aHatsuJikoku;
						CdDedJikoku aOuterSyuchakuJikoku;
						if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku1)
						{
							aHatsuJikoku = pCentDedRessya->getCentDedEkiJikokuCont()
								->getMuPtr()->get(iEkiOrder)->getChakujikoku();
						}
						else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter1)
						{
							const CentDedBeforeOperation* pReleaseOperation = pAfterOperationCont->getBeforeOperation();
							aHatsuJikoku = pReleaseOperation->getReleaseJikoku();
						}
						else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter1)
						{
							const CentDedAfterOperation* pReleaseOperation = pAfterOperationCont->getAfterOperation();
							aHatsuJikoku = pReleaseOperation->getReleaseJikoku();
						}
						if (!aHatsuJikoku.isNull())
						{
							aOuterSyuchakuJikoku = aHatsuJikoku;
							aHatsuJikoku.addSeconds(iOuterTerminalJikan[idx][1]);
							aOuterSyuchakuJikoku.addSeconds(iOuterTerminalJikan[idx][0]);

							CentDedAfterOperation aAfterOperation(
								CentDedAfterOperation::EAOperation::AOperation_Outer,
								idx,
								aHatsuJikoku,
								aOuterSyuchakuJikoku,
								tstring());
							pAfterOperationCont->set(aAfterOperation, INT_MAX);

							bSet = true;

						}
						break;
					}
				}
				if (!bSet)
				{
					CdDedJikoku aJikoku = pLastOperation->getTerminalJikoku();
					for (int idxa = pAfterOperationCont->size() - 1; idxa >= 0 && aJikoku.isNull(); idxa--)
					{
						const CentDedAfterOperation* pAfterOperation = pAfterOperationCont->getMuPtr()->get(idxa);
						if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
						{
							aJikoku = pAfterOperation->getOperationChakuJikoku(true);
						}
						else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
						{
							aJikoku = pAfterOperation->getConnectJikoku();
						}
						else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
						{
							aJikoku = pAfterOperation->getReleaseJikoku();
						}
					}
					if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku1 &&
						aJikoku.isNull())
					{
						CentDedBeforeOperationCont* pBeforeOperationCont = pCentDedRessya->getCentDedEkiJikokuCont()
							->getMuPtr()->get(iEkiOrder)->getCentDedBeforeOperationCont();
						for (int idxb = pBeforeOperationCont->size() - 1; idxb >= 0 && aJikoku.isNull(); idxb--)
						{
							const CentDedBeforeOperation* pBeforeOperation = pBeforeOperationCont->getMuPtr()->get(idxb);
							if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
							{
								aJikoku = pBeforeOperation->getOperationChakuJikoku(true);
							}
							else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
							{
								aJikoku = pBeforeOperation->getConnectJikoku();
							}
							else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
							{
								aJikoku = pBeforeOperation->getReleaseJikoku();
							}
						}
						if (aJikoku.isNull())
						{
							aJikoku = pCentDedRessya->getCentDedEkiJikokuCont()
								->getMuPtr()->get(iEkiOrder)->getChakujikoku();
						}
					}
					else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter1 &&
						aJikoku.isNull())
					{
						const CentDedBeforeOperation* pReleaseOperation = pAfterOperationCont->getBeforeOperation();
						aJikoku = pReleaseOperation->getReleaseJikoku();
					}
					else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter1 &&
						aJikoku.isNull())
					{
						const CentDedAfterOperation* pReleaseOperation = pAfterOperationCont->getAfterOperation();
						aJikoku = pReleaseOperation->getReleaseJikoku();
					}

					if (!aJikoku.isNull())
					{
						aJikoku.addSeconds(60);
						CentDedAfterOperation aAfterOperation(
							CentDedAfterOperation::EAOperation::AOperation_In,
							aJikoku,
							tstring());
						pAfterOperationCont->set(aAfterOperation, INT_MAX);
					}
				}
			}
			else if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_In)
			{
				CentDedAfterOperation aAfterOperation(
					CentDedAfterOperation::EAOperation::AOperation_Junction,
					CdDedJikoku(),
					0);
				pAfterOperationCont->set(aAfterOperation, INT_MAX);
			}
			else if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
			{
				CdDedJikoku aJikoku = pLastOperation->getHatsuJikoku();
				for (int idxa = pAfterOperationCont->size() - 1; idxa >= 0 && aJikoku.isNull(); idxa--)
				{
					const CentDedAfterOperation* pAfterOperation = pAfterOperationCont->getMuPtr()->get(idxa);
					if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
					{
						aJikoku = pAfterOperation->getOperationChakuJikoku(true);
					}
					else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
					{
						aJikoku = pAfterOperation->getConnectJikoku();
					}
					else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
					{
						aJikoku = pAfterOperation->getReleaseJikoku();
					}
				}
				if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku1 &&
					aJikoku.isNull())
				{
					CentDedBeforeOperationCont* pBeforeOperationCont = pCentDedRessya->getCentDedEkiJikokuCont()
						->getMuPtr()->get(iEkiOrder)->getCentDedBeforeOperationCont();
					for (int idxb = pBeforeOperationCont->size() - 1; idxb >= 0 && aJikoku.isNull(); idxb--)
					{
						const CentDedBeforeOperation* pBeforeOperation = pBeforeOperationCont->getMuPtr()->get(idxb);
						if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
						{
							aJikoku = pBeforeOperation->getOperationChakuJikoku(true);
						}
						else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
						{
							aJikoku = pBeforeOperation->getConnectJikoku();
						}
						else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
						{
							aJikoku = pBeforeOperation->getReleaseJikoku();
						}
					}
					if (aJikoku.isNull())
					{
						aJikoku = pCentDedRessya->getCentDedEkiJikokuCont()
							->getMuPtr()->get(iEkiOrder)->getChakujikoku();
					}
				}
				else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter1 &&
					aJikoku.isNull())
				{
					const CentDedBeforeOperation* pReleaseOperation = pAfterOperationCont->getBeforeOperation();
					aJikoku = pReleaseOperation->getReleaseJikoku();
				}
				else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter1 &&
					aJikoku.isNull())
				{
					const CentDedAfterOperation* pReleaseOperation = pAfterOperationCont->getAfterOperation();
					aJikoku = pReleaseOperation->getReleaseJikoku();
				}

				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(60);
					CentDedAfterOperation aAfterOperation(
						CentDedAfterOperation::EAOperation::AOperation_In,
						aJikoku,
						pLastOperation->getInOutLinkCode());
					pAfterOperationCont->set(aAfterOperation, INT_MAX);
				}
			}
		}
	}
}

void CWjkState_Ressyahensyu::ChangeShihatsuShuchakuOperationDataNext(
	Mu<CentDedRessya*>* muCentDedRessya)
{
	for (int i = 0; i < muCentDedRessya->size(); i++)
	{
		CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);
		//int iEkiOrder;
		if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore1)
		{
			int iEkiOrder = -1;
			if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu1)
			{
				iEkiOrder = pCentDedRessya->getValidSihatsuEki();
			}
			else
			{
				iEkiOrder = getCWndDcdGrid()->getYColSpecOfFocus().getEkiOrder();
			}
			if (iEkiOrder == -1)
			{
				continue;
			}

			CentDedBeforeOperation* pFirstOperation = NULL;
			if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu1)
			{
				pFirstOperation = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iEkiOrder)->getCentDedBeforeOperationCont()->getMuPtr()->get(0);
			}
			else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore1)
			{
				CentDedBeforeOperationCont* pBeforeCont = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iEkiOrder)->getCentDedBeforeOperationCont();
				for (int idx = pBeforeCont->size() - 1; idx >= 0; idx--)
				{
					if (pBeforeCont->get(idx).getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
					{
						CentDedBeforeOperationCont* pBeforeOperationOfConnectCont = pBeforeCont->getMuPtr()->get(idx)->getCentDedBeforeOperationCont();
						pFirstOperation = pBeforeOperationOfConnectCont->getMuPtr()->get(0);
						break;
					}
				}
			}
			else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore1)
			{
				CentDedAfterOperationCont* pAfterCont = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iEkiOrder)->getCentDedAfterOperationCont();
				for (int idx = 0; idx < pAfterCont->size(); idx++)
				{
					if (pAfterCont->get(idx).getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
					{
						CentDedBeforeOperationCont* pBeforeOperationOfConnectCont = pAfterCont->getMuPtr()->get(idx)->getCentDedBeforeOperationCont();
						pFirstOperation = pBeforeOperationOfConnectCont->getMuPtr()->get(0);
						break;
					}
				}
			}

			if (pFirstOperation == NULL)
			{
				continue;
			}

			if(pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
			{
				const CentDedEkiCont::CdDedEki aCdDedEki =
					getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont()
					->getMuPtr(pCentDedRessya->getRessyahoukou())->get(iEkiOrder);
				int iOuterTerminalEkimeiCount = aCdDedEki.getOuterTerminalEkimeiCount();

				vector<vector<int>> iOuterTerminalJikan;

				getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
					->StandardOuterTerminalJikanSearch(
						pCentDedRessya->getRessyasyubetsuIndex(),
						getRessyahoukou(),
						-1,
						iEkiOrder,
						iOuterTerminalJikan);

				if (pFirstOperation->getOuterShihatsuekiIndex() < iOuterTerminalEkimeiCount - 1)
				{
					int iNewIndex = pFirstOperation->getOuterShihatsuekiIndex() + 1;
					pFirstOperation->setOuterShihatsuekiIndex(iNewIndex);
					if (iOuterTerminalJikan[iNewIndex][0] != 0)
					{
						//路線外始発駅の変更の場合、当駅着時刻はとりあえず変更しないことにする。
						CdDedJikoku aOuterShihatsuJikoku = pCentDedRessya->getCentDedEkiJikokuCont()
							->getMuPtr()->get(iEkiOrder)->getHatsujikoku();
						//CdDedJikoku aChakuJikoku = aOuterShihatsuJikoku;
						aOuterShihatsuJikoku.addSeconds(-(iOuterTerminalJikan[iNewIndex][0]));
						//aChakuJikoku.addSeconds(-(iOuterTerminalJikan[iNewIndex][1]));

						pFirstOperation->setOuterShihatsuJikoku(aOuterShihatsuJikoku);
					}
				}
				else
				{
					pFirstOperation->setOuterShihatsuekiIndex(0);
					if (iOuterTerminalJikan[0][0] != 0)
					{
						//路線外始発駅の変更の場合、当駅着時刻はとりあえず変更しないことにする。
						CdDedJikoku aOuterShihatsuJikoku = pCentDedRessya->getCentDedEkiJikokuCont()
							->getMuPtr()->get(iEkiOrder)->getHatsujikoku();
						//CdDedJikoku aChakuJikoku = aOuterShihatsuJikoku;
						aOuterShihatsuJikoku.addSeconds(-(iOuterTerminalJikan[0][0]));
						//aChakuJikoku.addSeconds(-(iOuterTerminalJikan[0][1]));

						pFirstOperation->setOuterShihatsuJikoku(aOuterShihatsuJikoku);
					}
				}
			}
		}
		else//終着作業
		{
			int iEkiOrder = -1;
			if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku1)
			{
				iEkiOrder = pCentDedRessya->getValidSyuuchakuEki();
			}
			else
			{
				iEkiOrder = getCWndDcdGrid()->getYColSpecOfFocus().getEkiOrder();
			}
			if (iEkiOrder == -1)
			{
				continue;
			}

			CentDedAfterOperation* pLastOperation = NULL;
			if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku1)
			{
				pLastOperation = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iEkiOrder)->getCentDedAfterOperationCont()->getMuPtr()->get(INT_MAX);
			}
			else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter1)
			{
				CentDedBeforeOperationCont* pBeforeCont = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iEkiOrder)->getCentDedBeforeOperationCont();
				for (int idx = pBeforeCont->size() - 1; idx >= 0; idx--)
				{
					if (pBeforeCont->get(idx).getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
					{
						CentDedAfterOperationCont* pAfterOperationOfReleaseCont = pBeforeCont->getMuPtr()->get(idx)->getCentDedAfterOperationCont();
						pLastOperation = pAfterOperationOfReleaseCont->getMuPtr()->get(INT_MAX);
						break;
					}
				}
			}
			else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter1)
			{
				CentDedAfterOperationCont* pAfterCont = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iEkiOrder)->getCentDedAfterOperationCont();
				for (int idx = 0; idx < pAfterCont->size(); idx++)
				{
					if (pAfterCont->get(idx).getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
					{
						CentDedAfterOperationCont* pAfterOperationOfReleaseCont = pAfterCont->getMuPtr()->get(idx)->getCentDedAfterOperationCont();
						pLastOperation = pAfterOperationOfReleaseCont->getMuPtr()->get(INT_MAX);
						break;
					}
				}
			}

			if (pLastOperation == NULL)
			{
				continue;
			}

			if(pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
			{
				const CentDedEkiCont::CdDedEki aCdDedEki =
					getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont()
					->getMuPtr(pCentDedRessya->getRessyahoukou())->get(iEkiOrder);
				int iOuterTerminalEkimeiCount = aCdDedEki.getOuterTerminalEkimeiCount();
				vector<vector<int>> iOuterTerminalJikan;

				getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
					->StandardOuterTerminalJikanSearch(
						pCentDedRessya->getRessyasyubetsuIndex(),
						getRessyahoukou(),
						iEkiOrder,
						-1,
						iOuterTerminalJikan);
				if (pLastOperation->getOuterShuchakuekiIndex() < iOuterTerminalEkimeiCount - 1)
				{
					int iNewIndex = pLastOperation->getOuterShuchakuekiIndex() + 1;
					pLastOperation->setOuterShuchakuekiIndex(iNewIndex);
					if (iOuterTerminalJikan[iNewIndex][0] != 0)
					{
						//路線外終着駅の変更の場合、当駅発時刻はとりあえず変更しないことにする。
						CdDedJikoku aOuterSyuchakuJikoku = pCentDedRessya->getCentDedEkiJikokuCont()
							->getMuPtr()->get(iEkiOrder)->getChakujikoku();
						//CdDedJikoku aHatsuJikoku = aOuterSyuchakuJikoku;
						//aHatsuJikoku.addSeconds(iOuterTerminalJikan[iNewIndex][1]);
						aOuterSyuchakuJikoku.addSeconds(iOuterTerminalJikan[iNewIndex][0]);

						pLastOperation->setOuterShuchakuJikoku(aOuterSyuchakuJikoku);
					}
				}
				else
				{
					pLastOperation->setOuterShuchakuekiIndex(0);
					if (iOuterTerminalJikan[0][0] != 0)
					{
						CdDedJikoku aOuterSyuchakuJikoku = pCentDedRessya->getCentDedEkiJikokuCont()
							->getMuPtr()->get(iEkiOrder)->getChakujikoku();
						//CdDedJikoku aHatsuJikoku = aOuterSyuchakuJikoku;
						//aHatsuJikoku.addSeconds(iOuterTerminalJikan[0][1]);
						aOuterSyuchakuJikoku.addSeconds(iOuterTerminalJikan[0][0]);

						pLastOperation->setOuterShuchakuJikoku(aOuterSyuchakuJikoku);
					}
				}
			}
			else if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Junction)
			{
				if (pLastOperation->getNextJunctionType() == 3)
				{
					pLastOperation->setNextJunctionType(0);
				}
				else
				{
					pLastOperation->setNextJunctionType(
						pLastOperation->getNextJunctionType() + 1);
				}
			}
		}
	}
}

void CWjkState_Ressyahensyu::ChangeShihatsuShuchakuOperationDataPrev(
	Mu<CentDedRessya*>* muCentDedRessya)
{
	for (int i = 0; i < muCentDedRessya->size(); i++)
	{
		CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);
		//int iEkiOrder;
		if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore1 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore1)
		{
			int iEkiOrder = -1;
			if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu1)
			{
				iEkiOrder = pCentDedRessya->getValidSihatsuEki();
			}
			else
			{
				iEkiOrder = getCWndDcdGrid()->getYColSpecOfFocus().getEkiOrder();
			}
			if (iEkiOrder == -1)
			{
				continue;
			}

			CentDedBeforeOperation* pFirstOperation = NULL;
			if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu1)
			{
				pFirstOperation = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iEkiOrder)->getCentDedBeforeOperationCont()->getMuPtr()->get(0);
			}
			else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore1)
			{
				CentDedBeforeOperationCont* pBeforeCont = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iEkiOrder)->getCentDedBeforeOperationCont();
				for (int idx = pBeforeCont->size() - 1; idx >= 0; idx--)
				{
					if (pBeforeCont->get(idx).getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
					{
						CentDedBeforeOperationCont* pBeforeOperationOfConnectCont = pBeforeCont->getMuPtr()->get(idx)->getCentDedBeforeOperationCont();
						pFirstOperation = pBeforeOperationOfConnectCont->getMuPtr()->get(0);
						break;
					}
				}
			}
			else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore1)
			{
				CentDedAfterOperationCont* pAfterCont = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iEkiOrder)->getCentDedAfterOperationCont();
				for (int idx = 0; idx < pAfterCont->size(); idx++)
				{
					if (pAfterCont->get(idx).getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
					{
						CentDedBeforeOperationCont* pBeforeOperationOfConnectCont = pAfterCont->getMuPtr()->get(idx)->getCentDedBeforeOperationCont();
						pFirstOperation = pBeforeOperationOfConnectCont->getMuPtr()->get(0);
						break;
					}
				}
			}

			if (pFirstOperation == NULL)
			{
				continue;
			}

			if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
			{
				const CentDedEkiCont::CdDedEki aCdDedEki =
					getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont()
					->getMuPtr(pCentDedRessya->getRessyahoukou())->get(iEkiOrder);
				int iOuterTerminalEkimeiCount = aCdDedEki.getOuterTerminalEkimeiCount();

				vector<vector<int>> iOuterTerminalJikan;

				getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
					->StandardOuterTerminalJikanSearch(
						pCentDedRessya->getRessyasyubetsuIndex(),
						getRessyahoukou(),
						-1,
						iEkiOrder,
						iOuterTerminalJikan);

				if (pFirstOperation->getOuterShihatsuekiIndex() == 0)
				{
					pFirstOperation->setOuterShihatsuekiIndex(iOuterTerminalEkimeiCount - 1);
					if (iOuterTerminalJikan[iOuterTerminalEkimeiCount - 1][0] != 0)
					{
						//路線外始発駅の変更の場合、当駅着時刻はとりあえず変更しないことにする。
						CdDedJikoku aOuterShihatsuJikoku = pCentDedRessya->getCentDedEkiJikokuCont()
							->getMuPtr()->get(iEkiOrder)->getHatsujikoku();
						//CdDedJikoku aChakuJikoku = aOuterShihatsuJikoku;
						aOuterShihatsuJikoku.addSeconds(-(iOuterTerminalJikan[iOuterTerminalEkimeiCount - 1][0]));
						//aChakuJikoku.addSeconds(-(iOuterTerminalJikan[iOuterTerminalEkimeiCount - 1][1]));

						pFirstOperation->setOuterShihatsuJikoku(aOuterShihatsuJikoku);
					}
				}
				else
				{
					int iNewIndex = pFirstOperation->getOuterShihatsuekiIndex() - 1;
					pFirstOperation->setOuterShihatsuekiIndex(iNewIndex);
					if (iOuterTerminalJikan[iNewIndex][0] != 0)
					{
						//路線外始発駅の変更の場合、当駅着時刻はとりあえず変更しないことにする。
						CdDedJikoku aOuterShihatsuJikoku = pCentDedRessya->getCentDedEkiJikokuCont()
							->getMuPtr()->get(iEkiOrder)->getHatsujikoku();
						//CdDedJikoku aChakuJikoku = aOuterShihatsuJikoku;
						aOuterShihatsuJikoku.addSeconds(-(iOuterTerminalJikan[iNewIndex][0]));
						//aChakuJikoku.addSeconds(-(iOuterTerminalJikan[iNewIndex][1]));

						pFirstOperation->setOuterShihatsuJikoku(aOuterShihatsuJikoku);
					}
				}
			}
		}
		else//終着作業
		{
			int iEkiOrder = -1;
			if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku1)
			{
				iEkiOrder = pCentDedRessya->getValidSyuuchakuEki();
			}
			else
			{
				iEkiOrder = getCWndDcdGrid()->getYColSpecOfFocus().getEkiOrder();
			}
			if (iEkiOrder == -1)
			{
				continue;
			}

			CentDedAfterOperation* pLastOperation = NULL;
			if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku1)
			{
				pLastOperation = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iEkiOrder)->getCentDedAfterOperationCont()->getMuPtr()->get(INT_MAX);
			}
			else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter1)
			{
				CentDedBeforeOperationCont* pBeforeCont = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iEkiOrder)->getCentDedBeforeOperationCont();
				for (int idx = pBeforeCont->size() - 1; idx >= 0; idx--)
				{
					if (pBeforeCont->get(idx).getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
					{
						CentDedAfterOperationCont* pAfterOperationOfReleaseCont = pBeforeCont->getMuPtr()->get(idx)->getCentDedAfterOperationCont();
						pLastOperation = pAfterOperationOfReleaseCont->getMuPtr()->get(INT_MAX);
						break;
					}
				}
			}
			else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter1)
			{
				CentDedAfterOperationCont* pAfterCont = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iEkiOrder)->getCentDedAfterOperationCont();
				for (int idx = 0; idx < pAfterCont->size(); idx++)
				{
					if (pAfterCont->get(idx).getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
					{
						CentDedAfterOperationCont* pAfterOperationOfReleaseCont = pAfterCont->getMuPtr()->get(idx)->getCentDedAfterOperationCont();
						pLastOperation = pAfterOperationOfReleaseCont->getMuPtr()->get(INT_MAX);
						break;
					}
				}
			}

			if (pLastOperation == NULL)
			{
				continue;
			}

			if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
			{
				const CentDedEkiCont::CdDedEki aCdDedEki =
					getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont()
					->getMuPtr(pCentDedRessya->getRessyahoukou())->get(iEkiOrder);
				int iOuterTerminalEkimeiCount = aCdDedEki.getOuterTerminalEkimeiCount();
				vector<vector<int>> iOuterTerminalJikan;

				getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
					->StandardOuterTerminalJikanSearch(
						pCentDedRessya->getRessyasyubetsuIndex(),
						getRessyahoukou(),
						iEkiOrder,
						-1,
						iOuterTerminalJikan);
				if (pLastOperation->getOuterShuchakuekiIndex() == 0)
				{
					pLastOperation->setOuterShuchakuekiIndex(iOuterTerminalEkimeiCount - 1);
					if (iOuterTerminalJikan[iOuterTerminalEkimeiCount - 1][0] != 0)
					{
						CdDedJikoku aOuterSyuchakuJikoku = pCentDedRessya->getCentDedEkiJikokuCont()
							->getMuPtr()->get(iEkiOrder)->getChakujikoku();
						//CdDedJikoku aHatsuJikoku = aOuterSyuchakuJikoku;
						//aHatsuJikoku.addSeconds(iOuterTerminalJikan[iOuterTerminalEkimeiCount - 1][1]);
						aOuterSyuchakuJikoku.addSeconds(iOuterTerminalJikan[iOuterTerminalEkimeiCount - 1][0]);

						pLastOperation->setOuterShuchakuJikoku(aOuterSyuchakuJikoku);
					}
				}
				else
				{
					int iNewIndex = pLastOperation->getOuterShuchakuekiIndex() - 1;
					pLastOperation->setOuterShuchakuekiIndex(iNewIndex);
					if (iOuterTerminalJikan[iNewIndex][0] != 0)
					{
						//路線外終着駅の変更の場合、当駅発時刻はとりあえず変更しないことにする。
						CdDedJikoku aOuterSyuchakuJikoku = pCentDedRessya->getCentDedEkiJikokuCont()
							->getMuPtr()->get(iEkiOrder)->getChakujikoku();
						//CdDedJikoku aHatsuJikoku = aOuterSyuchakuJikoku;
						//aHatsuJikoku.addSeconds(iOuterTerminalJikan[iNewIndex][1]);
						aOuterSyuchakuJikoku.addSeconds(iOuterTerminalJikan[iNewIndex][0]);

						pLastOperation->setOuterShuchakuJikoku(aOuterSyuchakuJikoku);
					}
				}
			}
			else if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Junction)
			{
				if (pLastOperation->getNextJunctionType() == 0)
				{
					pLastOperation->setNextJunctionType(3);
				}
				else
				{
					pLastOperation->setNextJunctionType(
						pLastOperation->getNextJunctionType() - 1);
				}
			}
		}
	}
}

void CWjkState_Ressyahensyu::ChangeShihatsuShuchakuOuterTerminalNext(
	Mu<CentDedRessya*>* muCentDedRessya)
{
	for (int i = 0; i < muCentDedRessya->size(); i++)
	{
		CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);
		//int iEkiOrder;
		if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Outer_Shihatsu1)
		{
			int iValidSihatsuEkiOrder = pCentDedRessya->getValidSihatsuEki();
			if (iValidSihatsuEkiOrder != -1 &&
				pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
			{
				CentDedBeforeOperation* pFirstOperation = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iValidSihatsuEkiOrder)->getCentDedBeforeOperationCont()->getMuPtr()->get(0);
				const CentDedEkiCont::CdDedEki aCdDedEki =
					getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont()
					->getMuPtr(pCentDedRessya->getRessyahoukou())->get(iValidSihatsuEkiOrder);
				int iOuterTerminalEkimeiCount = aCdDedEki.getOuterTerminalEkimeiCount();

				vector<vector<int>> iOuterTerminalJikan;

				getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
					->StandardOuterTerminalJikanSearch(
						pCentDedRessya->getRessyasyubetsuIndex(),
						getRessyahoukou(),
						-1,
						iValidSihatsuEkiOrder,
						iOuterTerminalJikan);

				if (pFirstOperation->getOuterShihatsuekiIndex() < iOuterTerminalEkimeiCount - 1)
				{
					int iNewIndex = pFirstOperation->getOuterShihatsuekiIndex() + 1;
					pFirstOperation->setOuterShihatsuekiIndex(iNewIndex);
					if (iOuterTerminalJikan[iNewIndex][0] != 0)
					{
						//路線外始発駅の変更の場合、当駅着時刻はとりあえず変更しないことにする。
						CdDedJikoku aOuterShihatsuJikoku = pCentDedRessya->getCentDedEkiJikokuCont()
							->getMuPtr()->get(iValidSihatsuEkiOrder)->getHatsujikoku();
						//CdDedJikoku aChakuJikoku = aOuterShihatsuJikoku;
						aOuterShihatsuJikoku.addSeconds(-(iOuterTerminalJikan[iNewIndex][0]));
						//aChakuJikoku.addSeconds(-(iOuterTerminalJikan[iNewIndex][1]));

						pFirstOperation->setOuterShihatsuJikoku(aOuterShihatsuJikoku);
					}
				}
				else
				{
					pFirstOperation->setOuterShihatsuekiIndex(0);
					if (iOuterTerminalJikan[0][0] != 0)
					{
						//路線外始発駅の変更の場合、当駅着時刻はとりあえず変更しないことにする。
						CdDedJikoku aOuterShihatsuJikoku = pCentDedRessya->getCentDedEkiJikokuCont()
							->getMuPtr()->get(iValidSihatsuEkiOrder)->getHatsujikoku();
						//CdDedJikoku aChakuJikoku = aOuterShihatsuJikoku;
						aOuterShihatsuJikoku.addSeconds(-(iOuterTerminalJikan[0][0]));
						//aChakuJikoku.addSeconds(-(iOuterTerminalJikan[0][1]));

						pFirstOperation->setOuterShihatsuJikoku(aOuterShihatsuJikoku);
					}
				}
			}
		}
		else//終着作業
		{
			int iValidSyuuchakuEkiOrder = pCentDedRessya->getValidSyuuchakuEki();
			if (iValidSyuuchakuEkiOrder != -1 &&
				pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
			{
				CentDedAfterOperation* pLastOperation = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iValidSyuuchakuEkiOrder)->getCentDedAfterOperationCont()->getMuPtr()->get(INT_MAX);
				const CentDedEkiCont::CdDedEki aCdDedEki =
					getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont()
					->getMuPtr(pCentDedRessya->getRessyahoukou())->get(iValidSyuuchakuEkiOrder);
				int iOuterTerminalEkimeiCount = aCdDedEki.getOuterTerminalEkimeiCount();
				vector<vector<int>> iOuterTerminalJikan;

				getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
					->StandardOuterTerminalJikanSearch(
						pCentDedRessya->getRessyasyubetsuIndex(),
						getRessyahoukou(),
						iValidSyuuchakuEkiOrder,
						-1,
						iOuterTerminalJikan);
				if (pLastOperation->getOuterShuchakuekiIndex() < iOuterTerminalEkimeiCount - 1)
				{
					int iNewIndex = pLastOperation->getOuterShuchakuekiIndex() + 1;
					pLastOperation->setOuterShuchakuekiIndex(iNewIndex);
					if (iOuterTerminalJikan[iNewIndex][0] != 0)
					{
						//路線外終着駅の変更の場合、当駅発時刻はとりあえず変更しないことにする。
						CdDedJikoku aOuterSyuchakuJikoku = pCentDedRessya->getCentDedEkiJikokuCont()
							->getMuPtr()->get(iValidSyuuchakuEkiOrder)->getChakujikoku();
						//CdDedJikoku aHatsuJikoku = aOuterSyuchakuJikoku;
						//aHatsuJikoku.addSeconds(iOuterTerminalJikan[iNewIndex][1]);
						aOuterSyuchakuJikoku.addSeconds(iOuterTerminalJikan[iNewIndex][0]);

						pLastOperation->setOuterShuchakuJikoku(aOuterSyuchakuJikoku);
					}
				}
				else
				{
					pLastOperation->setOuterShuchakuekiIndex(0);
					if (iOuterTerminalJikan[0][0] != 0)
					{
						CdDedJikoku aOuterSyuchakuJikoku = pCentDedRessya->getCentDedEkiJikokuCont()
							->getMuPtr()->get(iValidSyuuchakuEkiOrder)->getChakujikoku();
						//CdDedJikoku aHatsuJikoku = aOuterSyuchakuJikoku;
						//aHatsuJikoku.addSeconds(iOuterTerminalJikan[0][1]);
						aOuterSyuchakuJikoku.addSeconds(iOuterTerminalJikan[0][0]);

						pLastOperation->setOuterShuchakuJikoku(aOuterSyuchakuJikoku);
					}
				}
			}
		}
	}
}

void CWjkState_Ressyahensyu::ChangeShihatsuShuchakuOuterTerminalPrev(
	Mu<CentDedRessya*>* muCentDedRessya)
{
	for (int i = 0; i < muCentDedRessya->size(); i++)
	{
		CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);
		if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Outer_Shihatsu1)
		{
			int iValidSihatsuEkiOrder = pCentDedRessya->getValidSihatsuEki();
			if (iValidSihatsuEkiOrder != -1 &&
				pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
			{
				CentDedBeforeOperation* pFirstOperation = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iValidSihatsuEkiOrder)->getCentDedBeforeOperationCont()->getMuPtr()->get(0);
				const CentDedEkiCont::CdDedEki aCdDedEki =
					getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont()
					->getMuPtr(pCentDedRessya->getRessyahoukou())->get(iValidSihatsuEkiOrder);
				int iOuterTerminalEkimeiCount = aCdDedEki.getOuterTerminalEkimeiCount();

				vector<vector<int>> iOuterTerminalJikan;

				getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
					->StandardOuterTerminalJikanSearch(
						pCentDedRessya->getRessyasyubetsuIndex(),
						getRessyahoukou(),
						-1,
						iValidSihatsuEkiOrder,
						iOuterTerminalJikan);

				if (pFirstOperation->getOuterShihatsuekiIndex() == 0)
				{
					pFirstOperation->setOuterShihatsuekiIndex(iOuterTerminalEkimeiCount - 1);
					if (iOuterTerminalJikan[iOuterTerminalEkimeiCount - 1][0] != 0)
					{
						//路線外始発駅の変更の場合、当駅着時刻はとりあえず変更しないことにする。
						CdDedJikoku aOuterShihatsuJikoku = pCentDedRessya->getCentDedEkiJikokuCont()
							->getMuPtr()->get(iValidSihatsuEkiOrder)->getHatsujikoku();
						//CdDedJikoku aChakuJikoku = aOuterShihatsuJikoku;
						aOuterShihatsuJikoku.addSeconds(-(iOuterTerminalJikan[iOuterTerminalEkimeiCount - 1][0]));
						//aChakuJikoku.addSeconds(-(iOuterTerminalJikan[iOuterTerminalEkimeiCount - 1][1]));

						pFirstOperation->setOuterShihatsuJikoku(aOuterShihatsuJikoku);
					}
				}
				else
				{
					int iNewIndex = pFirstOperation->getOuterShihatsuekiIndex() - 1;
					pFirstOperation->setOuterShihatsuekiIndex(iNewIndex);
					if (iOuterTerminalJikan[iNewIndex][0] != 0)
					{
						//路線外始発駅の変更の場合、当駅着時刻はとりあえず変更しないことにする。
						CdDedJikoku aOuterShihatsuJikoku = pCentDedRessya->getCentDedEkiJikokuCont()
							->getMuPtr()->get(iValidSihatsuEkiOrder)->getHatsujikoku();
						//CdDedJikoku aChakuJikoku = aOuterShihatsuJikoku;
						aOuterShihatsuJikoku.addSeconds(-(iOuterTerminalJikan[iNewIndex][0]));
						//aChakuJikoku.addSeconds(-(iOuterTerminalJikan[iNewIndex][1]));

						pFirstOperation->setOuterShihatsuJikoku(aOuterShihatsuJikoku);
					}
				}
			}
		}
		else//終着作業
		{
			int iValidSyuuchakuEkiOrder = pCentDedRessya->getValidSyuuchakuEki();
			if (iValidSyuuchakuEkiOrder != -1 &&
				pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
			{
				CentDedAfterOperation* pLastOperation = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iValidSyuuchakuEkiOrder)->getCentDedAfterOperationCont()->getMuPtr()->get(INT_MAX);
				const CentDedEkiCont::CdDedEki aCdDedEki =
					getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont()
					->getMuPtr(pCentDedRessya->getRessyahoukou())->get(iValidSyuuchakuEkiOrder);
				int iOuterTerminalEkimeiCount = aCdDedEki.getOuterTerminalEkimeiCount();
				vector<vector<int>> iOuterTerminalJikan;

				getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
					->StandardOuterTerminalJikanSearch(
						pCentDedRessya->getRessyasyubetsuIndex(),
						getRessyahoukou(),
						iValidSyuuchakuEkiOrder,
						-1,
						iOuterTerminalJikan);
				if (pLastOperation->getOuterShuchakuekiIndex() == 0)
				{
					pLastOperation->setOuterShuchakuekiIndex(iOuterTerminalEkimeiCount - 1);
					if (iOuterTerminalJikan[iOuterTerminalEkimeiCount - 1][0] != 0)
					{
						CdDedJikoku aOuterSyuchakuJikoku = pCentDedRessya->getCentDedEkiJikokuCont()
							->getMuPtr()->get(iValidSyuuchakuEkiOrder)->getChakujikoku();
						//CdDedJikoku aHatsuJikoku = aOuterSyuchakuJikoku;
						//aHatsuJikoku.addSeconds(iOuterTerminalJikan[iOuterTerminalEkimeiCount - 1][1]);
						aOuterSyuchakuJikoku.addSeconds(iOuterTerminalJikan[iOuterTerminalEkimeiCount - 1][0]);

						pLastOperation->setOuterShuchakuJikoku(aOuterSyuchakuJikoku);
					}
				}
				else
				{
					int iNewIndex = pLastOperation->getOuterShuchakuekiIndex() - 1;
					pLastOperation->setOuterShuchakuekiIndex(iNewIndex);
					if (iOuterTerminalJikan[iNewIndex][0] != 0)
					{
						//路線外終着駅の変更の場合、当駅発時刻はとりあえず変更しないことにする。
						CdDedJikoku aOuterSyuchakuJikoku = pCentDedRessya->getCentDedEkiJikokuCont()
							->getMuPtr()->get(iValidSyuuchakuEkiOrder)->getChakujikoku();
						//CdDedJikoku aHatsuJikoku = aOuterSyuchakuJikoku;
						//aHatsuJikoku.addSeconds(iOuterTerminalJikan[iNewIndex][1]);
						aOuterSyuchakuJikoku.addSeconds(iOuterTerminalJikan[iNewIndex][0]);

						pLastOperation->setOuterShuchakuJikoku(aOuterSyuchakuJikoku);
					}
				}
			}
		}
	}
}

void CWjkState_Ressyahensyu::ChangeShihatsuShuchakuOperationJikoku(
	Mu<CentDedRessya*>* muCentDedRessya, int iShiftSecond)
{
	//Ver2.0　路線外発着の場合は、当駅発/着時刻の変更を行う（路線外駅時刻は、路線外発着駅欄に表示されるので)
	for (int i = 0; i < muCentDedRessya->size(); i++)
	{
		CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);
		//int iEkiOrder;
		if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore2)
		{
			int iEkiOrder = -1;
			if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu2)
			{
				iEkiOrder = pCentDedRessya->getValidSihatsuEki();
			}
			else
			{
				iEkiOrder = getCWndDcdGrid()->getYColSpecOfFocus().getEkiOrder();
			}
			if (iEkiOrder == -1)
			{
				continue;
			}

			CentDedBeforeOperation* pFirstOperation = NULL;
			if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu2)
			{
				pFirstOperation = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iEkiOrder)->getCentDedBeforeOperationCont()->getMuPtr()->get(0);
			}
			else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore2)
			{
				CentDedBeforeOperationCont* pBeforeCont = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iEkiOrder)->getCentDedBeforeOperationCont();
				for (int idx = pBeforeCont->size() - 1; idx >= 0; idx--)
				{
					if (pBeforeCont->get(idx).getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
					{
						CentDedBeforeOperationCont* pBeforeOperationOfConnectCont = pBeforeCont->getMuPtr()->get(idx)->getCentDedBeforeOperationCont();
						pFirstOperation = pBeforeOperationOfConnectCont->getMuPtr()->get(0);
						break;
					}
				}
			}
			else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore2)
			{
				CentDedAfterOperationCont* pAfterCont = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iEkiOrder)->getCentDedAfterOperationCont();
				for (int idx = 0; idx < pAfterCont->size(); idx++)
				{
					if (pAfterCont->get(idx).getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
					{
						CentDedBeforeOperationCont* pBeforeOperationOfConnectCont = pAfterCont->getMuPtr()->get(idx)->getCentDedBeforeOperationCont();
						pFirstOperation = pBeforeOperationOfConnectCont->getMuPtr()->get(0);
						break;
					}
				}
			}

			if (pFirstOperation == NULL)
			{
				continue;
			}

			if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Out)
			{
				if (!pFirstOperation->getOutJikoku().isNull())
				{
					pFirstOperation->setOutJikoku(
						pFirstOperation->getOutJikoku().addSeconds(iShiftSecond));
				}
			}
			else if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
			{
				if (!pFirstOperation->getChakuJikoku().isNull())
				{
					pFirstOperation->setChakuJikoku(
						pFirstOperation->getChakuJikoku().addSeconds(iShiftSecond));
				}
				else if(getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu2)
				{
					CentDedBeforeOperationCont* pBeforeOperationCont = pCentDedRessya->getCentDedEkiJikokuCont()
						->getMuPtr()->get(iEkiOrder)->getCentDedBeforeOperationCont();
					CdDedJikoku aJikoku;
					for (int idxb = 0; idxb < pBeforeOperationCont->size() && aJikoku.isNull(); idxb++)
					{
						const CentDedBeforeOperation* pBeforeOperation = pBeforeOperationCont->getMuPtr()->get(idxb);
						if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
						{
							aJikoku = pBeforeOperation->getOperationHatsuJikoku();

						}
						else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
						{
							aJikoku = pBeforeOperation->getConnectJikoku();
						}
						else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
						{
							aJikoku = pBeforeOperation->getReleaseJikoku();
						}
					}
					CentDedAfterOperationCont* pAfterOperationCont = pCentDedRessya->getCentDedEkiJikokuCont()
						->getMuPtr()->get(iEkiOrder)->getCentDedAfterOperationCont();
					for (int idxa = 0; idxa < pAfterOperationCont->size() && aJikoku.isNull(); idxa++)
					{
						const CentDedAfterOperation* pAfterOperation = pAfterOperationCont->getMuPtr()->get(idxa);
						if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
						{
							aJikoku = pAfterOperation->getOperationHatsuJikoku();

						}
						else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
						{
							aJikoku = pAfterOperation->getConnectJikoku();
						}
						else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
						{
							aJikoku = pAfterOperation->getReleaseJikoku();
						}
					}
					if (aJikoku.isNull())
					{
						aJikoku = pCentDedRessya->getCentDedEkiJikokuCont()
							->getMuPtr()->get(iEkiOrder)->getChakujikoku(true);
					}
					if (!aJikoku.isNull())
					{
						pFirstOperation->setChakuJikoku(aJikoku);
					}
				}
				else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore2)
				{
					/**
						増結編成の起点作業の場合、その他の前作業及び増結時刻からセットする時刻を求めます
					*/
					CentDedBeforeOperationCont* pBeforeCont = pCentDedRessya->getCentDedEkiJikokuCont()
						->getMuPtr()->get(iEkiOrder)->getCentDedBeforeOperationCont();
					CdDedJikoku aJikoku;
					for (int idx = pBeforeCont->size() - 1; idx >= 0; idx--)
					{
						if (pBeforeCont->get(idx).getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
						{
							CentDedBeforeOperationCont* pBeforeOperationOfConnectCont = pBeforeCont->getMuPtr()->get(idx)->getCentDedBeforeOperationCont();
							for (int idxb = 0; idxb < pBeforeOperationOfConnectCont->size() && aJikoku.isNull(); idxb++)
							{
								const CentDedBeforeOperation* pBeforeOperation = pBeforeOperationOfConnectCont->getMuPtr()->get(idxb);
								if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
								{
									aJikoku = pBeforeOperation->getOperationHatsuJikoku();

								}
								else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
								{
									aJikoku = pBeforeOperation->getConnectJikoku();
								}
								else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
								{
									aJikoku = pBeforeOperation->getReleaseJikoku();
								}
							}
							if (aJikoku.isNull())
							{
								aJikoku = pBeforeCont->get(idx).getConnectJikoku();
							}

							if (!aJikoku.isNull())
							{
								pFirstOperation->setChakuJikoku(aJikoku);
							}

							break;
						}
					}
				}
				else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore2)
				{
					CentDedAfterOperationCont* pAfterCont = pCentDedRessya->getCentDedEkiJikokuCont()
						->getMuPtr()->get(iEkiOrder)->getCentDedAfterOperationCont();
					CdDedJikoku aJikoku;
					for (int idx = 0; idx < pAfterCont->size(); idx++)
					{
						if (pAfterCont->get(idx).getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
						{
							CentDedBeforeOperationCont* pBeforeOperationOfConnectCont = pAfterCont->getMuPtr()->get(idx)->getCentDedBeforeOperationCont();
							for (int idxb = 0; idxb < pBeforeOperationOfConnectCont->size() && aJikoku.isNull(); idxb++)
							{
								const CentDedBeforeOperation* pBeforeOperation = pBeforeOperationOfConnectCont->getMuPtr()->get(idxb);
								if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
								{
									aJikoku = pBeforeOperation->getOperationHatsuJikoku();

								}
								else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
								{
									aJikoku = pBeforeOperation->getConnectJikoku();
								}
								else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
								{
									aJikoku = pBeforeOperation->getReleaseJikoku();
								}
							}
							if (aJikoku.isNull())
							{
								aJikoku = pAfterCont->get(idx).getConnectJikoku();
							}

							if (!aJikoku.isNull())
							{
								pFirstOperation->setChakuJikoku(aJikoku);
							}

							break;
						}
					}
				}
			}
			else if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Junction)
			{
				if (!pFirstOperation->getOriginJikoku().isNull())
				{
					pFirstOperation->setOriginJikoku(
						pFirstOperation->getOriginJikoku().addSeconds(iShiftSecond));
				}
				else if(getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu2)
				{
					CentDedBeforeOperationCont* pBeforeOperationCont = pCentDedRessya->getCentDedEkiJikokuCont()
						->getMuPtr()->get(iEkiOrder)->getCentDedBeforeOperationCont();
					CdDedJikoku aJikoku;
					for (int idxb = 0; idxb < pBeforeOperationCont->size() && aJikoku.isNull(); idxb++)
					{
						const CentDedBeforeOperation* pBeforeOperation = pBeforeOperationCont->getMuPtr()->get(idxb);
						if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
						{
							aJikoku = pBeforeOperation->getOperationHatsuJikoku();

						}
						else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
						{
							aJikoku = pBeforeOperation->getConnectJikoku();
						}
						else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
						{
							aJikoku = pBeforeOperation->getReleaseJikoku();
						}
					}
					CentDedAfterOperationCont* pAfterOperationCont = pCentDedRessya->getCentDedEkiJikokuCont()
						->getMuPtr()->get(iEkiOrder)->getCentDedAfterOperationCont();
					for (int idxa = 0; idxa < pAfterOperationCont->size() && aJikoku.isNull(); idxa++)
					{
						const CentDedAfterOperation* pAfterOperation = pAfterOperationCont->getMuPtr()->get(idxa);
						if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
						{
							aJikoku = pAfterOperation->getOperationHatsuJikoku();

						}
						else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
						{
							aJikoku = pAfterOperation->getConnectJikoku();
						}
						else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
						{
							aJikoku = pAfterOperation->getReleaseJikoku();
						}
					}
					if (aJikoku.isNull())
					{
						aJikoku = pCentDedRessya->getCentDedEkiJikokuCont()
							->getMuPtr()->get(iEkiOrder)->getChakujikoku(true);
					}
					if (!aJikoku.isNull())
					{
						pFirstOperation->setOriginJikoku(aJikoku);
					}
				}
				else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore2)
				{
					/**
						増結編成の起点作業の場合、その他の前作業及び増結時刻からセットする時刻を求めます
					*/
					CentDedBeforeOperationCont* pBeforeCont = pCentDedRessya->getCentDedEkiJikokuCont()
						->getMuPtr()->get(iEkiOrder)->getCentDedBeforeOperationCont();
					CdDedJikoku aJikoku;
					for (int idx = pBeforeCont->size() - 1; idx >= 0; idx--)
					{
						if (pBeforeCont->get(idx).getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
						{
							CentDedBeforeOperationCont* pBeforeOperationOfConnectCont = pBeforeCont->getMuPtr()->get(idx)->getCentDedBeforeOperationCont();
							for (int idxb = 0; idxb < pBeforeOperationOfConnectCont->size() && aJikoku.isNull(); idxb++)
							{
								const CentDedBeforeOperation* pBeforeOperation = pBeforeOperationOfConnectCont->getMuPtr()->get(idxb);
								if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
								{
									aJikoku = pBeforeOperation->getOperationHatsuJikoku();

								}
								else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
								{
									aJikoku = pBeforeOperation->getConnectJikoku();
								}
								else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
								{
									aJikoku = pBeforeOperation->getReleaseJikoku();
								}
							}
							if (aJikoku.isNull())
							{
								aJikoku = pBeforeCont->get(idx).getConnectJikoku();
							}

							if (!aJikoku.isNull())
							{
								pFirstOperation->setOriginJikoku(aJikoku);
							}

							break;
						}
					}
				}
				else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore2)
				{
					CentDedAfterOperationCont* pAfterCont = pCentDedRessya->getCentDedEkiJikokuCont()
						->getMuPtr()->get(iEkiOrder)->getCentDedAfterOperationCont();
					CdDedJikoku aJikoku;
					for (int idx = 0; idx < pAfterCont->size(); idx++)
					{
						if (pAfterCont->get(idx).getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
						{
							CentDedBeforeOperationCont* pBeforeOperationOfConnectCont = pAfterCont->getMuPtr()->get(idx)->getCentDedBeforeOperationCont();
							for (int idxb = 0; idxb < pBeforeOperationOfConnectCont->size() && aJikoku.isNull(); idxb++)
							{
								const CentDedBeforeOperation* pBeforeOperation = pBeforeOperationOfConnectCont->getMuPtr()->get(idxb);
								if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
								{
									aJikoku = pBeforeOperation->getOperationHatsuJikoku();

								}
								else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
								{
									aJikoku = pBeforeOperation->getConnectJikoku();
								}
								else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
								{
									aJikoku = pBeforeOperation->getReleaseJikoku();
								}
							}
							if (aJikoku.isNull())
							{
								aJikoku = pAfterCont->get(idx).getConnectJikoku();
							}

							if (!aJikoku.isNull())
							{
								pFirstOperation->setOriginJikoku(aJikoku);
							}

							break;
						}
					}
				}
			}
		}
		else
		{
			int iEkiOrder = -1;
			if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku2)
			{
				iEkiOrder = pCentDedRessya->getValidSyuuchakuEki();
			}
			else
			{
				iEkiOrder = getCWndDcdGrid()->getYColSpecOfFocus().getEkiOrder();
			}
			if (iEkiOrder == -1)
			{
				continue;
			}

			CentDedAfterOperation* pLastOperation = NULL;

			if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku2)
			{
				pLastOperation = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iEkiOrder)->getCentDedAfterOperationCont()->getMuPtr()->get(INT_MAX);
			}
			else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter2)
			{
				CentDedBeforeOperationCont* pBeforeCont = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iEkiOrder)->getCentDedBeforeOperationCont();
				for (int idx = pBeforeCont->size() - 1; idx >= 0; idx--)
				{
					if (pBeforeCont->get(idx).getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
					{
						CentDedAfterOperationCont* pAfterOperationOfReleaseCont = pBeforeCont->getMuPtr()->get(idx)->getCentDedAfterOperationCont();
						pLastOperation = pAfterOperationOfReleaseCont->getMuPtr()->get(INT_MAX);
						break;
					}
				}
			}
			else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter2)
			{
				CentDedAfterOperationCont* pAfterCont = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iEkiOrder)->getCentDedAfterOperationCont();
				for (int idx = 0; idx < pAfterCont->size(); idx++)
				{
					if (pAfterCont->get(idx).getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
					{
						CentDedAfterOperationCont* pAfterOperationOfReleaseCont = pAfterCont->getMuPtr()->get(idx)->getCentDedAfterOperationCont();
						pLastOperation = pAfterOperationOfReleaseCont->getMuPtr()->get(INT_MAX);
						break;
					}
				}
			}

			if (pLastOperation == NULL)
			{
				continue;
			}

			if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_In)
			{
				if (!pLastOperation->getInJikoku().isNull())
				{
					pLastOperation->setInJikoku(
						pLastOperation->getInJikoku().addSeconds(iShiftSecond));
				}
			}
			else if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
			{
				if (!pLastOperation->getHatsuJikoku().isNull())
				{
					pLastOperation->setHatsuJikoku(
						pLastOperation->getHatsuJikoku().addSeconds(iShiftSecond));
				}
				else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku2)
				{
					CentDedAfterOperationCont* pAfterOperationCont = pCentDedRessya->getCentDedEkiJikokuCont()
						->getMuPtr()->get(iEkiOrder)->getCentDedAfterOperationCont();
					CdDedJikoku aJikoku;
					for (int idxa = pAfterOperationCont->size() - 1; idxa >= 0 && aJikoku.isNull(); idxa--)
					{
						const CentDedAfterOperation* pAfterOperation = pAfterOperationCont->getMuPtr()->get(idxa);
						if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
						{
							aJikoku = pAfterOperation->getOperationChakuJikoku(true);

						}
						else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
						{
							aJikoku = pAfterOperation->getConnectJikoku();
						}
						else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
						{
							aJikoku = pAfterOperation->getReleaseJikoku();
						}
					}
					CentDedBeforeOperationCont* pBeforeOperationCont = pCentDedRessya->getCentDedEkiJikokuCont()
						->getMuPtr()->get(iEkiOrder)->getCentDedBeforeOperationCont();
					for (int idxb = pBeforeOperationCont->size() - 1; idxb >= 0 && aJikoku.isNull(); idxb--)
					{
						const CentDedBeforeOperation* pBeforeOperation = pBeforeOperationCont->getMuPtr()->get(idxb);
						if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
						{
							aJikoku = pBeforeOperation->getOperationChakuJikoku(true);

						}
						else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
						{
							aJikoku = pBeforeOperation->getConnectJikoku();
						}
						else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
						{
							aJikoku = pBeforeOperation->getReleaseJikoku();
						}
					}
					if (aJikoku.isNull())
					{
						aJikoku = pCentDedRessya->getCentDedEkiJikokuCont()
							->getMuPtr()->get(iEkiOrder)->getHatsujikoku(true);
					}
					if (!aJikoku.isNull())
					{
						pLastOperation->setHatsuJikoku(aJikoku);
					}
				}
				else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter2)
				{
					CentDedBeforeOperationCont* pBeforeCont = pCentDedRessya->getCentDedEkiJikokuCont()
						->getMuPtr()->get(iEkiOrder)->getCentDedBeforeOperationCont();
					for (int idx = pBeforeCont->size() - 1; idx >= 0; idx--)
					{
						if (pBeforeCont->get(idx).getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
						{
							CentDedAfterOperationCont* pAfterOperationOfReleaseCont = pBeforeCont->getMuPtr()->get(idx)->getCentDedAfterOperationCont();

							CdDedJikoku aJikoku;
							for (int idxa = pAfterOperationOfReleaseCont->size() - 1; idxa >= 0 && aJikoku.isNull(); idxa--)
							{
								const CentDedAfterOperation* pAfterOperation = pAfterOperationOfReleaseCont->getMuPtr()->get(idxa);
								if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
								{
									aJikoku = pAfterOperation->getOperationChakuJikoku(true);

								}
								else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
								{
									aJikoku = pAfterOperation->getConnectJikoku();
								}
								else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
								{
									aJikoku = pAfterOperation->getReleaseJikoku();
								}
							}
							if (aJikoku.isNull())
							{
								aJikoku = pBeforeCont->get(idx).getReleaseJikoku();
							}
							if (!aJikoku.isNull())
							{
								pLastOperation->setHatsuJikoku(aJikoku);
							}
							break;
						}
					}
				}
				else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter2)
				{
					CentDedAfterOperationCont* pAfterCont = pCentDedRessya->getCentDedEkiJikokuCont()
						->getMuPtr()->get(iEkiOrder)->getCentDedAfterOperationCont();
					for (int idx = 0; idx < pAfterCont->size(); idx++)
					{
						if (pAfterCont->get(idx).getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
						{
							CentDedAfterOperationCont* pAfterOperationOfReleaseCont = pAfterCont->getMuPtr()->get(idx)->getCentDedAfterOperationCont();

							CdDedJikoku aJikoku;
							for (int idxa = pAfterOperationOfReleaseCont->size() - 1; idxa >= 0 && aJikoku.isNull(); idxa--)
							{
								const CentDedAfterOperation* pAfterOperation = pAfterOperationOfReleaseCont->getMuPtr()->get(idxa);
								if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
								{
									aJikoku = pAfterOperation->getOperationChakuJikoku(true);

								}
								else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
								{
									aJikoku = pAfterOperation->getConnectJikoku();
								}
								else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
								{
									aJikoku = pAfterOperation->getReleaseJikoku();
								}
							}
							if (aJikoku.isNull())
							{
								aJikoku = pAfterCont->get(idx).getReleaseJikoku();
							}
							if (!aJikoku.isNull())
							{
								pLastOperation->setHatsuJikoku(aJikoku);
							}
							break;
						}
					}
				}
			}
			else if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Junction)
			{
				if (!pLastOperation->getTerminalJikoku().isNull())
				{
					pLastOperation->setTerminalJikoku(
						pLastOperation->getTerminalJikoku().addSeconds(iShiftSecond));
				}
				else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku2)
				{
					CentDedAfterOperationCont* pAfterOperationCont = pCentDedRessya->getCentDedEkiJikokuCont()
						->getMuPtr()->get(iEkiOrder)->getCentDedAfterOperationCont();
					CdDedJikoku aJikoku;
					for (int idxa = pAfterOperationCont->size() - 1; idxa >= 0 && aJikoku.isNull(); idxa--)
					{
						const CentDedAfterOperation* pAfterOperation = pAfterOperationCont->getMuPtr()->get(idxa);
						if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
						{
							aJikoku = pAfterOperation->getOperationChakuJikoku(true);

						}
						else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
						{
							aJikoku = pAfterOperation->getConnectJikoku();
						}
						else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
						{
							aJikoku = pAfterOperation->getReleaseJikoku();
						}
					}
					CentDedBeforeOperationCont* pBeforeOperationCont = pCentDedRessya->getCentDedEkiJikokuCont()
						->getMuPtr()->get(iEkiOrder)->getCentDedBeforeOperationCont();
					for (int idxb = pBeforeOperationCont->size() - 1; idxb >= 0 && aJikoku.isNull(); idxb--)
					{
						const CentDedBeforeOperation* pBeforeOperation = pBeforeOperationCont->getMuPtr()->get(idxb);
						if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
						{
							aJikoku = pBeforeOperation->getOperationChakuJikoku(true);

						}
						else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
						{
							aJikoku = pBeforeOperation->getConnectJikoku();
						}
						else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
						{
							aJikoku = pBeforeOperation->getReleaseJikoku();
						}
					}
					if (aJikoku.isNull())
					{
						aJikoku = pCentDedRessya->getCentDedEkiJikokuCont()
							->getMuPtr()->get(iEkiOrder)->getHatsujikoku(true);
					}
					if (!aJikoku.isNull())
					{
						pLastOperation->setTerminalJikoku(aJikoku);
					}
				}
				else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter2)
				{
					CentDedBeforeOperationCont* pBeforeCont = pCentDedRessya->getCentDedEkiJikokuCont()
						->getMuPtr()->get(iEkiOrder)->getCentDedBeforeOperationCont();
					for (int idx = pBeforeCont->size() - 1; idx >= 0; idx--)
					{
						if (pBeforeCont->get(idx).getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
						{
							CentDedAfterOperationCont* pAfterOperationOfReleaseCont = pBeforeCont->getMuPtr()->get(idx)->getCentDedAfterOperationCont();

							CdDedJikoku aJikoku;
							for (int idxa = pAfterOperationOfReleaseCont->size() - 1; idxa >= 0 && aJikoku.isNull(); idxa--)
							{
								const CentDedAfterOperation* pAfterOperation = pAfterOperationOfReleaseCont->getMuPtr()->get(idxa);
								if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
								{
									aJikoku = pAfterOperation->getOperationChakuJikoku(true);

								}
								else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
								{
									aJikoku = pAfterOperation->getConnectJikoku();
								}
								else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
								{
									aJikoku = pAfterOperation->getReleaseJikoku();
								}
							}
							if (aJikoku.isNull())
							{
								aJikoku = pBeforeCont->get(idx).getReleaseJikoku();
							}
							if (!aJikoku.isNull())
							{
								pLastOperation->setTerminalJikoku(aJikoku);
							}
							break;
						}
					}
				}
				else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter2)
				{
					CentDedAfterOperationCont* pAfterCont = pCentDedRessya->getCentDedEkiJikokuCont()
						->getMuPtr()->get(iEkiOrder)->getCentDedAfterOperationCont();
					for (int idx = 0; idx < pAfterCont->size(); idx++)
					{
						if (pAfterCont->get(idx).getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
						{
							CentDedAfterOperationCont* pAfterOperationOfReleaseCont = pAfterCont->getMuPtr()->get(idx)->getCentDedAfterOperationCont();

							CdDedJikoku aJikoku;
							for (int idxa = pAfterOperationOfReleaseCont->size() - 1; idxa >= 0 && aJikoku.isNull(); idxa--)
							{
								const CentDedAfterOperation* pAfterOperation = pAfterOperationOfReleaseCont->getMuPtr()->get(idxa);
								if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
								{
									aJikoku = pAfterOperation->getOperationChakuJikoku(true);

								}
								else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
								{
									aJikoku = pAfterOperation->getConnectJikoku();
								}
								else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
								{
									aJikoku = pAfterOperation->getReleaseJikoku();
								}
							}
							if (aJikoku.isNull())
							{
								aJikoku = pAfterCont->get(idx).getReleaseJikoku();
							}
							if (!aJikoku.isNull())
							{
								pLastOperation->setTerminalJikoku(aJikoku);
							}
							break;
						}
					}
				}
			}
		}
	}
}

void CWjkState_Ressyahensyu::ChangeShihatsuShuchakuOperationJikokuNull(
	Mu<CentDedRessya*>* muCentDedRessya)
{
	//Ver2.0　前列車接続の起点時刻および次列車接続の終点時刻のみNULL化を行う
	//19.12.7 路線外始発・終着かつ駅扱いが通過の場合は、当駅発・着時刻のNULL化を行う
	//Ver2.05 増結編成及び解結編成の作業については、前列車接続の起点時刻および次列車接続の終点時刻のみNULL化を行う
	for (int i = 0; i < muCentDedRessya->size(); i++)
	{
		CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);
		//int iEkiOrder;
		if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore2 ||
			getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore2)
		{
			int iEkiOrder = -1;
			if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu2)
			{
				iEkiOrder = pCentDedRessya->getValidSihatsuEki();
			}
			else
			{
				iEkiOrder = getCWndDcdGrid()->getYColSpecOfFocus().getEkiOrder();
			}
			if (iEkiOrder == -1)
			{
				continue;
			}

			CentDedBeforeOperation* pFirstOperation = NULL;
			if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu2)
			{
				pFirstOperation = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iEkiOrder)->getCentDedBeforeOperationCont()->getMuPtr()->get(0);
			}
			else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationBefore2)
			{
				CentDedBeforeOperationCont* pBeforeCont = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iEkiOrder)->getCentDedBeforeOperationCont();
				for (int idx = pBeforeCont->size() - 1; idx >= 0; idx--)
				{
					if (pBeforeCont->get(idx).getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
					{
						CentDedBeforeOperationCont* pBeforeOperationOfConnectCont = pBeforeCont->getMuPtr()->get(idx)->getCentDedBeforeOperationCont();
						pFirstOperation = pBeforeOperationOfConnectCont->getMuPtr()->get(0);
						break;
					}
				}
			}
			else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationBefore2)
			{
				CentDedAfterOperationCont* pAfterCont = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iEkiOrder)->getCentDedAfterOperationCont();
				for (int idx = 0; idx < pAfterCont->size(); idx++)
				{
					if (pAfterCont->get(idx).getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
					{
						CentDedBeforeOperationCont* pBeforeOperationOfConnectCont = pAfterCont->getMuPtr()->get(idx)->getCentDedBeforeOperationCont();
						pFirstOperation = pBeforeOperationOfConnectCont->getMuPtr()->get(0);
						break;
					}
				}
			}

			if (pFirstOperation == NULL)
			{
				continue;
			}

			if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Junction &&
				!pFirstOperation->getOriginJikoku().isNull())
			{
				pFirstOperation->setOriginJikoku(CdDedJikoku());
			}
			else if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer &&
				getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shihatsu2 &&
				!pFirstOperation->getChakuJikoku().isNull() &&
				pCentDedRessya->getCentDedEkiJikokuCont()->getMuPtr()->get(iEkiOrder)->
					getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka)
			{
				pFirstOperation->setChakuJikoku(CdDedJikoku());
			}
		}
		else
		{
			int iEkiOrder = -1;
			if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku2)
			{
				iEkiOrder = pCentDedRessya->getValidSyuuchakuEki();
			}
			else
			{
				iEkiOrder = getCWndDcdGrid()->getYColSpecOfFocus().getEkiOrder();
			}
			if (iEkiOrder == -1)
			{
				continue;
			}

			CentDedAfterOperation* pLastOperation = NULL;

			if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku2)
			{
				pLastOperation = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iEkiOrder)->getCentDedAfterOperationCont()->getMuPtr()->get(INT_MAX);
			}
			else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_BeforeOperationAfter2)
			{
				CentDedBeforeOperationCont* pBeforeCont = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iEkiOrder)->getCentDedBeforeOperationCont();
				for (int idx = pBeforeCont->size() - 1; idx >= 0; idx--)
				{
					if (pBeforeCont->get(idx).getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
					{
						CentDedAfterOperationCont* pAfterOperationOfReleaseCont = pBeforeCont->getMuPtr()->get(idx)->getCentDedAfterOperationCont();
						pLastOperation = pAfterOperationOfReleaseCont->getMuPtr()->get(INT_MAX);
						break;
					}
				}
			}
			else if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_AfterOperationAfter2)
			{
				CentDedAfterOperationCont* pAfterCont = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iEkiOrder)->getCentDedAfterOperationCont();
				for (int idx = 0; idx < pAfterCont->size(); idx++)
				{
					if (pAfterCont->get(idx).getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
					{
						CentDedAfterOperationCont* pAfterOperationOfReleaseCont = pAfterCont->getMuPtr()->get(idx)->getCentDedAfterOperationCont();
						pLastOperation = pAfterOperationOfReleaseCont->getMuPtr()->get(INT_MAX);
						break;
					}
				}
			}

			if (pLastOperation == NULL)
			{
				continue;
			}

			if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Junction &&
				!pLastOperation->getTerminalJikoku().isNull())
			{
				pLastOperation->setTerminalJikoku(CdDedJikoku());
			}
			else if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer &&
				getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Operation_Shuchaku2 &&
				!pLastOperation->getHatsuJikoku().isNull() &&
				pCentDedRessya->getCentDedEkiJikokuCont()->getMuPtr()->get(iEkiOrder)->
					getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka)
			{
				pLastOperation->setHatsuJikoku(CdDedJikoku());
			}
		}
	}
}

void CWjkState_Ressyahensyu::ChangeShihatsuShuchakuOuterJikoku(
	Mu<CentDedRessya*>* muCentDedRessya, int iShiftSecond)
{
	for (int i = 0; i < muCentDedRessya->size(); i++)
	{
		CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);
		//int iEkiOrder;
		if (getCWndDcdGrid()->getYColSpecOfFocus().getColumnType() == CdYColSpec::ColumnType_Outer_Shihatsu2)
		{
			int iValidSihatsuEkiOrder = pCentDedRessya->getValidSihatsuEki();
			if (iValidSihatsuEkiOrder != -1 &&
				pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
			{
				CentDedBeforeOperation* pFirstOperation = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iValidSihatsuEkiOrder)->getCentDedBeforeOperationCont()->getMuPtr()->get(0);
				if (!pFirstOperation->getOuterShihatsuJikoku().isNull())
				{
					pFirstOperation->setOuterShihatsuJikoku(
						pFirstOperation->getOuterShihatsuJikoku().addSeconds(iShiftSecond));
				}
			}
		}
		else
		{
			int iValidSyuuchakuEkiOrder = pCentDedRessya->getValidSyuuchakuEki();
			if (iValidSyuuchakuEkiOrder != -1 &&
				pCentDedRessya->getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
			{
				CentDedAfterOperation* pLastOperation = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iValidSyuuchakuEkiOrder)->getCentDedAfterOperationCont()->getMuPtr()->get(INT_MAX);
				if (!pLastOperation->getOuterShuchakuJikoku().isNull())
				{
					pLastOperation->setOuterShuchakuJikoku(
						pLastOperation->getOuterShuchakuJikoku().addSeconds(iShiftSecond));
				}
			}
		}
	}
}


//17.4.19
//AdjustStdOpeTimeの下請け関数
int CWjkState_Ressyahensyu::StdOpeTimeFunc( 
	int iDiaIndexStandard,
	const CdDedJikokuOrder aCdJikokuOrder,
	const CentDedRessya* pCentDedRessya,
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki 
	) 
{
	//不適切形式をここではじき出す
//ALL
	int iSearchEkiOrder = aCdJikokuOrder.getEkiOrder() ;
	CdDedJikokuOrder::EEkiJikokuItem aEEkiJikokuItem = aCdJikokuOrder.getEkiJikokuItem() ;
	
	bool SkipFor = false ;
	//着時刻の場合、一つ前が運行なしなら、この時刻は意味を持たない。
	if (aEEkiJikokuItem == CdDedJikokuOrder::EkiJikokuItem_Chaku &&
		!pCentDedRessya->isRunBetweenNextEki(iSearchEkiOrder - 1))
	{
		return 0;
	}
	//発時刻の場合、一つ後が運行なしなら、この時刻は意味を持たない。
	else if (aEEkiJikokuItem == CdDedJikokuOrder::EkiJikokuItem_Hatsu &&
		!pCentDedRessya->isRunBetweenNextEki(iSearchEkiOrder))
	{
		return 0;
	}


	if( aEEkiJikokuItem == CdDedJikokuOrder::EkiJikokuItem_Hatsu)
	{
		if (!pCentDedRessya->isRunBetweenNextEki(iSearchEkiOrder - 1))
		{
			//一つ前の駅が運行なしの場合は、この駅の着時刻は意味を持たないので、
			//運行なしを挟んで時刻がある駅を見つける。
			//見つかった駅とこの駅が、分岐・環状線設定で同グループではない場合は、illegalとする
			//同グループの場合は、iSearchEkiOrderを見つかった駅で上書きし、着時刻検査を行う。
			int iPrevEkiOrder = pCentDedRessya->getRunBetweenEkiBackward(iSearchEkiOrder);
			if (getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont()
				->isSameBrunchLoopGroup(iPrevEkiOrder, iSearchEkiOrder, pCentDedRessya->getRessyahoukou()))
			{
				iSearchEkiOrder = iPrevEkiOrder;
			}
			else
			{
				return 0;
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
					return 0;
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
					return 0;
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
		if (!pCentDedRessya->isRunBetweenNextEki(iSearchEkiOrder - 1))
		{
			int iPrevEkiOrder = pCentDedRessya->getRunBetweenEkiBackward(iSearchEkiOrder);
			if (getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont()
				->isSameBrunchLoopGroup(iPrevEkiOrder, iSearchEkiOrder, pCentDedRessya->getRessyahoukou()))
			{
				iSearchEkiOrder = iPrevEkiOrder;
			}
			else
			{
				return 0;
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
					return 0;
				}
			}
			else
			{
				break; //評価可能なので、forを抜けて本体へ
			}
		}
	}
	//ここまで事前確認


	//
	//まずは基準側列車コンテナまで定義
	const CentDedRessyaCont* pCentDedRessyaContStandard =
		getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedDiaCont()
		->getMuPtr()->get( iDiaIndexStandard )->getCentDedRessyaCont( pCentDedRessya->getRessyahoukou() ) ; 
	//対象列車種別を取得(引数から外した)
	int idxRessyasyubetsu = pCentDedRessya->getRessyasyubetsuIndex() ;
	//対象列車と同じ種別を基準側で探索
	for(int iRessyaIndexStandard = 0 ; 
		iRessyaIndexStandard < pCentDedRessyaContStandard->size()/*コンテナ内列車数*/ ; 
		iRessyaIndexStandard++ )
	{
		//対象列車と同じ種別かどうか確認
		if( pCentDedRessyaContStandard->getMuPtr()->get( iRessyaIndexStandard )->getRessyasyubetsuIndex() != idxRessyasyubetsu )
		{
			continue ; //次列車に移行
		}
	//同じ種別
		iSearchEkiOrder = aCdJikokuOrder.getEkiOrder();
		const CentDedEkiJikoku aEkiJikoku = pCentDedRessya->getCentDedEkiJikoku(iSearchEkiOrder);
		//基準側列車コンテナ取得
		const CentDedRessya* pCentDedRessyaStandard = pCentDedRessyaContStandard->getMuPtr()->get( iRessyaIndexStandard ) ;
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
		if( aEEkiJikokuItem == CdDedJikokuOrder::EkiJikokuItem_Chaku && 
			aStandardEkiJikoku.getChakujikoku().isNull() )
		{ 
			//評価対象が着時刻なのに、基準側にはないので、次列車
			continue ;
		}
	//評価対象が発時刻の場合と、着時刻なら基準側にも存在している
		if( aEEkiJikokuItem == CdDedJikokuOrder::EkiJikokuItem_Hatsu && 
			aStandardEkiJikoku.getHatsujikoku().isNull() )
		{
			//評価対象が発時刻なのに、基準側にはないので、次列車
			continue ;
		}
	//着時刻の場合、評価対象の一つ前が運行なしなら、この時刻は意味を持たないので、次列車へ
		if (aEEkiJikokuItem == CdDedJikokuOrder::EkiJikokuItem_Chaku &&
			!pCentDedRessyaStandard->isRunBetweenNextEki(iSearchEkiOrder - 1))
		{
			continue;
		}
	//発時刻の場合、評価対象の一つ後が運行なしなら、この時刻は意味を持たないので、次列車へ
		if (aEEkiJikokuItem == CdDedJikokuOrder::EkiJikokuItem_Hatsu &&
			!pCentDedRessyaStandard->isRunBetweenNextEki(iSearchEkiOrder))
		{
			continue;
		}
	//評価対象と同じポジションの時刻が存在する

		if (aEEkiJikokuItem == CdDedJikokuOrder::EkiJikokuItem_Hatsu)
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

						return iElapsedTimeStandard - iElapsedTime;
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
					int iElapsedTime = 0;
					int iElapsedTimeStandard = 0;
					if (aEEkiJikokuItem == CdDedJikokuOrder::EkiJikokuItem_Chaku)
					{
						iElapsedTime = aEkiJikoku.getChakujikoku().subJikoku(aSearchHatsuEkiJikoku.getHatsujikoku());
						iElapsedTimeStandard = aStandardEkiJikoku.getChakujikoku().subJikoku(aStandardSearchHatsuEkiJikoku.getHatsujikoku());
					}
					else
					{
						iElapsedTime = aEkiJikoku.getHatsujikoku().subJikoku(aSearchHatsuEkiJikoku.getHatsujikoku());
						iElapsedTimeStandard = aStandardEkiJikoku.getHatsujikoku().subJikoku(aStandardSearchHatsuEkiJikoku.getHatsujikoku());
					}
					return iElapsedTimeStandard - iElapsedTime;
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
					int iElapsedTime = 0;
					int iElapsedTimeStandard = 0;
					if (aEEkiJikokuItem == CdDedJikokuOrder::EkiJikokuItem_Chaku)
					{
						iElapsedTime = aEkiJikoku.getChakujikoku().subJikoku(aSearchChakuEkiJikoku.getChakujikoku());
						iElapsedTimeStandard = aStandardEkiJikoku.getChakujikoku().subJikoku(aStandardSearchChakuEkiJikoku.getChakujikoku());
					}
					else
					{
						iElapsedTime = aEkiJikoku.getHatsujikoku().subJikoku(aSearchChakuEkiJikoku.getChakujikoku());
						iElapsedTimeStandard = aStandardEkiJikoku.getHatsujikoku().subJikoku(aStandardSearchChakuEkiJikoku.getChakujikoku());
					}
					return iElapsedTimeStandard - iElapsedTime;
				}
				//通過・着時刻なしの場合は、前駅へ
			}
		}
	}
	//不適切に当てはまらず、なおかつ見つからなかった場合
	return 0 ;
}

/**
	経由なし相当に対する方針
	・経由なし相当になるので、意味を持たない位置に時刻がある場合でも、その時刻を有効扱いして基準点を決める
	・停車の場合、経由なし相当になるので意味を持たない位置に時刻がない場合は、それを許容するようにする。
	→経由無しを見るのは、停車で、時刻がなくても問題ない場合を確認するときのみ。
*/
int CWjkState_Ressyahensyu::ComplementSihatsuStdOpeTime(
	int iDiaIndexStandard, 
	CdDedJikokuOrder aCdJikokuOrder, 
	CentDedRessya * pCentDedRessya, 
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki)
{
	int iTsuukaBegin = -1;
	CdDedJikokuOrder aCdDedJikokuOrderKiten;
	for (int iEkiOrder = aCdJikokuOrder.getEkiOrder() + 1; iEkiOrder < muCdDedEki->size() && aCdDedJikokuOrderKiten.getIsNull(); iEkiOrder++)
	{

		CentDedEkiJikoku aCentDedEkiJikoku = pCentDedRessya->getCentDedEkiJikoku(iEkiOrder);
		if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka)
		{
			//通過の場合は、駅時刻表示を基にチェック、着時刻表示有の場合、着時刻が存在したら
			if (muCdDedEki->get(iEkiOrder).getChakujikokuHyouji())
			{
				if (!aCentDedEkiJikoku.getChakujikoku().isNull())
				{
					//着時刻が存在し、一つ前が経由なし相当ではない場合、この時刻Orderがコピー起点になる。
					//simplever,経由無しを見ないようにに。
					//if (iTsuukaBegin == -1 ||
					//	pCentDedRessya->isRunBetweenNextEki(iEkiOrder - 1))
					//{
						aCdDedJikokuOrderKiten = CdDedJikokuOrder(iEkiOrder, CdDedJikokuOrder::EkiJikokuItem_Chaku);
						break;
					//}
				}
			}
			//着時刻非表示or着時刻NULL
			if (muCdDedEki->get(iEkiOrder).getHatsujikokuHyouji())
			{
				if (aCentDedEkiJikoku.getHatsujikoku().isNull())
				{
					//発着時刻ともNULLの場合、iTsuukaBeginが初期値の場合は、この駅を通過経由無しの起点にする。
					//ただし、経由なし相当ではない場合に限る
					if (iTsuukaBegin == -1/* &&
						pCentDedRessya->isRunBetweenNextEki(iEkiOrder)*/)//simplever、経由無しを見ない
					{
						iTsuukaBegin = iEkiOrder;
					}
				}
				else/* if (pCentDedRessya->isRunBetweenNextEki(iEkiOrder))*///simplever、経由無しを見ない
				{
					//発時刻が存在するし、経由なし相当ではない場合、この時刻Orderがコピー起点になる。
					aCdDedJikokuOrderKiten = CdDedJikokuOrder(iEkiOrder, CdDedJikokuOrder::EkiJikokuItem_Hatsu);
					break;
				}
				//経由なし相当の場合は、iTsuukaBegin == -1であっても、この駅を通過連続の起点としない
			}
			else
			{
				//発時刻表示がない場合、iTsuukaBeginが初期値の場合は、この駅を通過経由無しの起点にする
					//ただし、経由なし相当ではない場合に限る
				if (iTsuukaBegin == -1/* &&
					pCentDedRessya->isRunBetweenNextEki(iEkiOrder)*/)//simplever、経由無しを見ない
				{
					iTsuukaBegin = iEkiOrder;
				}
			}
		}
		else if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya)
		{
			//停車の場合は、駅時刻表示を基にチェック、着時刻表示有の場合、着時刻が存在したら
			if (muCdDedEki->get(iEkiOrder).getChakujikokuHyouji())
			{
				if (aCentDedEkiJikoku.getChakujikoku().isNull())
				{
					//着時刻表示有にもかかわらず、着時刻が無い場合、前の駅が経由無し相当なら問題なし。
					//通過の場合は、return、当駅始発の場合は問題なし
					if (iTsuukaBegin != -1 &&
						pCentDedRessya->isRunBetweenNextEki(iEkiOrder - 1))
					{
						return -1;
					}
				}
				else
				{
					//着時刻が存在する場合、この時刻Orderがコピー起点になる。
					aCdDedJikokuOrderKiten = CdDedJikokuOrder(iEkiOrder, CdDedJikokuOrder::EkiJikokuItem_Chaku);
					break;
				}
			}
			//着時刻非表示or着時刻表示有でNULLだが、前の駅が経由無しもしくは運行無しもしくは探索頭駅
			if (muCdDedEki->get(iEkiOrder).getHatsujikokuHyouji())
			{
				if (aCentDedEkiJikoku.getHatsujikoku().isNull())
				{
					//次駅が運行なし(経由なし相当)の場合は、時刻なしも可
					if (pCentDedRessya->isRunBetweenNextEki(iEkiOrder))
					{
						return -1;
					}
				}
				else
				{
					//発時刻が存在する場合、この時刻Orderがコピー起点になる。
					aCdDedJikokuOrderKiten = CdDedJikokuOrder(iEkiOrder, CdDedJikokuOrder::EkiJikokuItem_Hatsu);
					break;
				}
			}
		}
		//運行無しの場合、iTsuukaBeginが-1の場合は、始発駅より前なので何も行わない、
	}
	if (aCdDedJikokuOrderKiten.getIsNull())
	{
		//コピーの起点となる駅が見つからなかったらreturn(経由無しや時刻なし通過しかないetc)
		return -1;
	}
	//基準運転時分ダイヤの中から、コピーの対象にできる列車を探す。
	const CentDedRessyaCont* pCentDedRessyaContStandard =
		getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedDiaCont()
		->getMuPtr()->get(iDiaIndexStandard)->getCentDedRessyaCont(pCentDedRessya->getRessyahoukou());
	int idxRessyasyubetsu = pCentDedRessya->getRessyasyubetsuIndex();

	for (int iRessyaIndexStandard = 0;
		iRessyaIndexStandard < pCentDedRessyaContStandard->size()/*コンテナ内列車数*/;
		iRessyaIndexStandard++)
	{
		//対象列車と同じ種別かどうか確認
		if (pCentDedRessyaContStandard->getMuPtr()->get(iRessyaIndexStandard)->getRessyasyubetsuIndex() != idxRessyasyubetsu)
		{
			continue; //次列車に移行
		}
		const CentDedRessya* pCentDedRessyaStd = pCentDedRessyaContStandard->getMuPtr()->get(iRessyaIndexStandard);
		//iTsuukaKeiyunasiBeginからコピーの起点となる駅の一つ上までの駅扱いが一致するか、
		//および、通過の場合は、駅時刻がないことも一致するかをチェックする。
		//ただし、経由なし相当に伴う、時刻無効に注意する
		bool bContinue = true;
		for (int ord = iTsuukaBegin;
			bContinue && iTsuukaBegin != -1 && ord < aCdDedJikokuOrderKiten.getEkiOrder();
			ord++)
		{
			CentDedEkiJikoku aCentDedEkiJikoku = pCentDedRessya->getCentDedEkiJikoku(ord);
			CentDedEkiJikoku aCentDedEkiJikokuStd = pCentDedRessyaStd->getCentDedEkiJikoku(ord);
			if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_None &&
				aCentDedEkiJikokuStd.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_None)
			{
				continue;
			}
			else if (aCentDedEkiJikoku.getEkiatsukai() ==aCentDedEkiJikokuStd.getEkiatsukai())
			{
				//駅扱いが停車・通過で一致の場合、発時刻・着時刻各々に対し、表示有の場合に、std側の時刻がNULLではなかった場合、一致していないのでbreak
				//なお、停車の場合でも必ず時刻はNULLになる(この区間に停車がくる場合は、着発共に経由なしによる意味を持たない場合かつ時刻がNULLの場合)
				if (muCdDedEki->get(ord).getChakujikokuHyouji() &&
					!aCentDedEkiJikokuStd.getChakujikoku().isNull())
				{
					bContinue = false;
					break;
				}
				if (muCdDedEki->get(ord).getHatsujikokuHyouji() &&
					!aCentDedEkiJikokuStd.getHatsujikoku().isNull())
				{
					bContinue = false;
					break;
				}
				continue;
			}
			//else if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya &&
			//	aCentDedEkiJikokuStd.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya)
			//{
			//	//元列車が停車の場合は、経由無し相当により、有効な時刻欄が無いかつ時刻が未入力の場合。
			//	//std側も、時刻が未入力である必要がある
			//	if (muCdDedEki->get(ord).getChakujikokuHyouji() &&
			//		!aCentDedEkiJikokuStd.getChakujikoku().isNull())
			//	{
			//		bContinue = false;
			//		break;
			//	}
			//	if (muCdDedEki->get(ord).getHatsujikokuHyouji() &&
			//		!aCentDedEkiJikokuStd.getHatsujikoku().isNull())
			//	{
			//		bContinue = false;
			//		break;
			//	}
			//	continue;
			//}
			//一致しなかった場合、break
			bContinue = false;
			break;
		}
		//一致しなかったものがあった場合、bContinueがfalseになるのでその場合は次列車に移行
		if (!bContinue)
		{
			continue;
		}
		//aCdDedJikokuOrderKitenについてチェックを行う、
		//まずは駅扱いをチェック、異なっている場合は次列車へ
		CentDedEkiJikoku aCentDedEkiJikoku = pCentDedRessya->getCentDedEkiJikoku(aCdDedJikokuOrderKiten.getEkiOrder());
		CentDedEkiJikoku aCentDedEkiJikokuStd = pCentDedRessyaStd->getCentDedEkiJikoku(aCdDedJikokuOrderKiten.getEkiOrder());
		if (aCentDedEkiJikoku.getEkiatsukai() != aCentDedEkiJikokuStd.getEkiatsukai())
		{
			continue;
		}
		int iDifferenceTime;
		if (aCdDedJikokuOrderKiten.getEkiJikokuItem() == CdDedJikokuOrder::EkiJikokuItem_Chaku)
		{
			//着時刻の場合は、aCentDedEkiJikokuStdの着時刻がNULLなら、次列車へ
			if (aCentDedEkiJikokuStd.getChakujikoku().isNull())
			{
				continue;
			}
			//ここまで来たら、コピーの前作業として、iDifferenceTimeを求める。
			iDifferenceTime = aCentDedEkiJikoku.getChakujikoku().subJikoku(aCentDedEkiJikokuStd.getChakujikoku());
		}
		else
		{
			//前提　発時刻が指定されている場合、元列車の着時刻は必ずNULLである
			//(逆に言うと、着時刻がある場合は、その着時刻が指定されているはず)
			//aCdDedJikokuOrderKitenは停車か通過のいずれかなので、ifは不要
			//if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka)
			//{
				//通過の場合、着時刻表示有かつstd側に着時刻が存在するなら、次列車へ
				//iTsuukaBeginが-1の場合は、編集対象列車の現始発駅であるので、着時刻があっても大丈夫
				if (muCdDedEki->get(aCdDedJikokuOrderKiten.getEkiOrder()).getChakujikokuHyouji() &&
					!aCentDedEkiJikokuStd.getChakujikoku().isNull() &&
					iTsuukaBegin != -1)
				{
					continue;
				}
			//}
			//else if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya)
			//{
			//	//停車の場合、着時刻表示有かつstd側に着時刻が存在するなら、次列車へ
			//	if (muCdDedEki->get(aCdDedJikokuOrderKiten.getEkiOrder()).getChakujikokuHyouji()&&
			//		!aCentDedEkiJikokuStd.getChakujikoku().isNull())
			//	{
			//		continue;
			//	}
			//}
			//発時刻がNULLなら次列車へ
			if (aCentDedEkiJikokuStd.getHatsujikoku().isNull())
			{
				continue;
			}
			//ここまで来たら、コピーの前作業として、iDifferenceTimeを求める。
			iDifferenceTime = aCentDedEkiJikoku.getHatsujikoku().subJikoku(aCentDedEkiJikokuStd.getHatsujikoku());
			//着時刻表示有の場合は、着時刻＆前作業のコピーも行ってしまう。
			if (muCdDedEki->get(aCdDedJikokuOrderKiten.getEkiOrder()).getChakujikokuHyouji() &&
				!aCentDedEkiJikokuStd.getChakujikoku().isNull())
			{
				aCentDedEkiJikoku.setChakujikoku(aCentDedEkiJikokuStd.getChakujikoku().addSeconds(iDifferenceTime));
				aCentDedEkiJikoku.setCentDedBeforeOperationCont(*aCentDedEkiJikokuStd.getCentDedBeforeOperationCont());
				aCentDedEkiJikoku.getCentDedBeforeOperationCont()->modifyOperationJikoku(iDifferenceTime);

				pCentDedRessya->setCentDedEkiJikoku(aCdDedJikokuOrderKiten.getEkiOrder(), aCentDedEkiJikoku);
			}
		}

		//コピーの起点駅の一つ前から、フォーカス位置までのコピーを行う。
		int ord = aCdDedJikokuOrderKiten.getEkiOrder() - 1;
		if (iTsuukaBegin != -1)
		{
			ord = iTsuukaBegin - 1;
		}
		for (; ord >= aCdJikokuOrder.getEkiOrder(); ord--)
		{
			//(1)コピー元の始発駅の場合、作業時刻・路線外発着時刻を補正する。
			//(2)aCdJikokuOrder.getEkiOrder()でフォーカスが発時刻の場合、着時刻をNULLにする。
			//なお、aCdJikokuOrder.getEkiOrder()かつコピー元の始発駅の場合は(1)優先になるようにif文を構築する
			//(3)どちらでもない場合は、時刻の補正のみ行う

			CentDedEkiJikoku aCentDedEkiJikokuNew(pCentDedRessyaStd->getCentDedEkiJikoku(ord));
			aCentDedEkiJikokuNew.setChakujikoku(aCentDedEkiJikokuNew.getChakujikoku().addSeconds(iDifferenceTime));
			aCentDedEkiJikokuNew.setHatsujikoku(aCentDedEkiJikokuNew.getHatsujikoku().addSeconds(iDifferenceTime));
			aCentDedEkiJikokuNew.getCentDedBeforeOperationCont()->modifyOperationJikoku(iDifferenceTime);
			aCentDedEkiJikokuNew.getCentDedAfterOperationCont()->modifyOperationJikoku(iDifferenceTime);

			//CentDedRessyaTrack aCentDedRessyaTrackNew(pCentDedRessyaStd->getCentDedRessyaTrack(ord));

/*			if (ord == pCentDedRessyaStd->getSihatsuEki())
			{
				aCentDedRessyaTrackNew.setOperationChakuJikoku(aCentDedRessyaTrackNew.getOperationChakuJikoku().addSeconds(iDifferenceTime));
				aCentDedRessyaTrackNew.setOperationHatsuJikoku(aCentDedRessyaTrackNew.getOperationHatsuJikoku().addSeconds(iDifferenceTime));
				aCentDedRessyaTrackNew.setOuterHatsuChakuJikoku(aCentDedRessyaTrackNew.getOuterHatsuChakuJikoku().addSeconds(iDifferenceTime));
			}
			else */if (ord == aCdJikokuOrder.getEkiOrder() &&
				aCdJikokuOrder.getEkiJikokuItem() == CdDedJikokuOrder::EkiJikokuItem_Hatsu)
			{
				aCentDedEkiJikokuNew.setChakujikoku(CdDedJikoku());
			}

			pCentDedRessya->setCentDedEkiJikoku(ord, aCentDedEkiJikokuNew);
			//pCentDedRessya->setCentDedRessyaTrack(ord, aCentDedRessyaTrackNew);
		}
		pCentDedRessya->adjustOperation();
		return 0;
	}
	return -1;
}
int CWjkState_Ressyahensyu::ComplementSyuuchakuStdOpeTime(
	int iDiaIndexStandard, 
	CdDedJikokuOrder aCdJikokuOrder, 
	CentDedRessya * pCentDedRessya, 
	const Mu<CentDedEkiCont::CdDedEki>* muCdDedEki)
{
	int iTsuukaBegin = -1;
	CdDedJikokuOrder aCdDedJikokuOrderKiten;
	int iEkiOrder;
	for (iEkiOrder = aCdJikokuOrder.getEkiOrder() - 1; iEkiOrder >= 0; iEkiOrder--)
	{

		CentDedEkiJikoku aCentDedEkiJikoku = pCentDedRessya->getCentDedEkiJikoku(iEkiOrder);
		if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka)
		{
			//通過の場合は、駅時刻表示を基にチェック、発時刻表示有の場合、発時刻が存在したら
			if (muCdDedEki->get(iEkiOrder).getHatsujikokuHyouji())
			{
				if (!aCentDedEkiJikoku.getHatsujikoku().isNull())
				{
					//発時刻が存在する場合、この時刻Orderがコピー起点になる。
					aCdDedJikokuOrderKiten = CdDedJikokuOrder(iEkiOrder, CdDedJikokuOrder::EkiJikokuItem_Hatsu);
					break;
				}
			}
			//発時刻非表示or発時刻NULL
			if (muCdDedEki->get(iEkiOrder).getChakujikokuHyouji())
			{
				if (aCentDedEkiJikoku.getChakujikoku().isNull())
				{
					//発着時刻ともNULLの場合、iTsuukaKeiyunasiBeginが初期値の場合は、この駅を通過経由無しの起点にする
					if (iTsuukaBegin == -1)
					{
						iTsuukaBegin = iEkiOrder;
					}
				}
				else
				{
					//着時刻が存在する場合、この時刻Orderがコピー起点になる。
					aCdDedJikokuOrderKiten = CdDedJikokuOrder(iEkiOrder, CdDedJikokuOrder::EkiJikokuItem_Chaku);
					break;
				}
			}
			else
			{
				//着時刻表示がない場合、iTsuukaKeiyunasiBeginが初期値の場合は、この駅を通過経由無しの起点にする
				if (iTsuukaBegin == -1)
				{
					iTsuukaBegin = iEkiOrder;
				}
			}
		}
		else if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya)
		{
			//停車の場合は、駅時刻表示を基にチェック、発時刻表示有の場合、発時刻が存在したら
			if (muCdDedEki->get(iEkiOrder).getHatsujikokuHyouji())
			{
				if (aCentDedEkiJikoku.getHatsujikoku().isNull())
				{
					//発時刻表示有にもかかわらず、発時刻が無い場合、次の駅が経由無し相当なら問題なし。
					//通過の場合は、return、当駅どまりの場合は問題なし
					if (iTsuukaBegin != -1 &&
						pCentDedRessya->isRunBetweenNextEki(iEkiOrder))
					{
						return -1;
					}
				}
				else
				{
					//発時刻が存在する場合、この時刻Orderがコピー起点になる。
					aCdDedJikokuOrderKiten = CdDedJikokuOrder(iEkiOrder, CdDedJikokuOrder::EkiJikokuItem_Hatsu);
					break;
				}
			}
			//発時刻非表示or発時刻表示有でNULLだが、前の駅が経由無しもしくは運行無しもしくは探索頭駅
			if (muCdDedEki->get(iEkiOrder).getChakujikokuHyouji())
			{
				if (aCentDedEkiJikoku.getChakujikoku().isNull())
				{
					//前駅が運行なし(経由なし相当)の場合は、時刻なしも可
					if (pCentDedRessya->isRunBetweenNextEki(iEkiOrder - 1))
					{
						return -1;
					}
				}
				else
				{
					//着時刻が存在する場合、この時刻Orderがコピー起点になる。
					aCdDedJikokuOrderKiten = CdDedJikokuOrder(iEkiOrder, CdDedJikokuOrder::EkiJikokuItem_Chaku);
					break;
				}
			}
		}
	}
	if (aCdDedJikokuOrderKiten.getIsNull())
	{
		//コピーの起点となる駅が見つからなかったらreturn(経由無しや時刻なし通過しかないetc)
		return -1;
	}
	//基準運転時分ダイヤの中から、コピーの対象にできる列車を探す。
	const CentDedRessyaCont* pCentDedRessyaContStandard =
		getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedDiaCont()
		->getMuPtr()->get(iDiaIndexStandard)->getCentDedRessyaCont(pCentDedRessya->getRessyahoukou());
	int idxRessyasyubetsu = pCentDedRessya->getRessyasyubetsuIndex();

	for (int iRessyaIndexStandard = 0;
		iRessyaIndexStandard < pCentDedRessyaContStandard->size()/*コンテナ内列車数*/;
		iRessyaIndexStandard++)
	{
		//対象列車と同じ種別かどうか確認
		if (pCentDedRessyaContStandard->getMuPtr()->get(iRessyaIndexStandard)->getRessyasyubetsuIndex() != idxRessyasyubetsu)
		{
			continue; //次列車に移行
		}
		const CentDedRessya* pCentDedRessyaStd = pCentDedRessyaContStandard->getMuPtr()->get(iRessyaIndexStandard);
		//iTsuukaKeiyunasiBeginからコピーの起点となる駅の一つ上までの駅扱いが一致するか、
		//および、通過の場合は、駅時刻がないことも一致するかをチェックする。
		bool bContinue = true;
		for (int ord = iTsuukaBegin;
			bContinue && iTsuukaBegin != -1 && ord > aCdDedJikokuOrderKiten.getEkiOrder();
			ord--)
		{
			CentDedEkiJikoku aCentDedEkiJikoku = pCentDedRessya->getCentDedEkiJikoku(ord);
			CentDedEkiJikoku aCentDedEkiJikokuStd = pCentDedRessyaStd->getCentDedEkiJikoku(ord);
			if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_None &&
				aCentDedEkiJikokuStd.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_None)
			{
				continue;
			}
			else if (aCentDedEkiJikoku.getEkiatsukai() == aCentDedEkiJikokuStd.getEkiatsukai())
			{
				//駅扱いが停車・通過で一致の場合、発時刻・着時刻各々に対し、表示有の場合に、std側の時刻がNULLではなかった場合、一致していないのでbreak
				//なお、停車の場合でも必ず時刻はNULLになる(この区間に停車がくる場合は、着発共に経由なしによる意味を持たない場合かつ時刻がNULLの場合)
				if (muCdDedEki->get(ord).getHatsujikokuHyouji() &&
					!aCentDedEkiJikokuStd.getHatsujikoku().isNull())
				{
					bContinue = false;
					break;
				}
				if (muCdDedEki->get(ord).getChakujikokuHyouji() &&
					!aCentDedEkiJikokuStd.getChakujikoku().isNull())
				{
					bContinue = false;
					break;
				}
				continue;
			}
			//一致しなかった場合、break
			bContinue = false;
			break;
		}
		//一致しなかったものがあった場合、bContinueがfalseになるのでその場合は次列車に移行
		if (!bContinue)
		{
			continue;
		}
		//aCdDedJikokuOrderKitenについてチェックを行う、
		//まずは駅扱いをチェック、異なっている場合は次列車へ
		CentDedEkiJikoku aCentDedEkiJikoku = pCentDedRessya->getCentDedEkiJikoku(aCdDedJikokuOrderKiten.getEkiOrder());
		CentDedEkiJikoku aCentDedEkiJikokuStd = pCentDedRessyaStd->getCentDedEkiJikoku(aCdDedJikokuOrderKiten.getEkiOrder());
		if (aCentDedEkiJikoku.getEkiatsukai() != aCentDedEkiJikokuStd.getEkiatsukai())
		{
			continue;
		}
		int iDifferenceTime;
		if (aCdDedJikokuOrderKiten.getEkiJikokuItem() == CdDedJikokuOrder::EkiJikokuItem_Hatsu)
		{
			//発時刻の場合は、aCentDedEkiJikokuStdの発時刻がNULLなら、次列車へ
			if (aCentDedEkiJikokuStd.getHatsujikoku().isNull())
			{
				continue;
			}
			//ここまで来たら、コピーの前作業として、iDifferenceTimeを求める。
			iDifferenceTime = aCentDedEkiJikoku.getHatsujikoku().subJikoku(aCentDedEkiJikokuStd.getHatsujikoku());
		}
		else
		{
			//前提　発時刻が指定されている場合、元列車の着時刻は必ずNULLである
			//(逆に言うと、着時刻がある場合は、その着時刻が指定されているはず)
			//aCdDedJikokuOrderKitenは停車か通過のいずれかなので、ifは不要
			//if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka)
			//{
			//	//通過の場合、発時刻表示有かつ発時刻が存在するなら、次列車へ
			//	if (muCdDedEki->get(aCdDedJikokuOrderKiten.getEkiOrder()).getHatsujikokuHyouji() &&
			//		!aCentDedEkiJikokuStd.getHatsujikoku().isNull())
			//	{
			//		continue;
			//	}
			//}
			//else if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya)
			//{
				//停車の場合、発時刻が存在しても、次列車へ行くとは限らない
				//iTsuukaKeiyunasiBeginが-1以外の場合は、一つ下の駅が経由無しとなる。
				//その場合は、発時刻表示有かつ発時刻が存在するなら、次列車へ
				//iTsuukaKeiyunasiBeginが-1の場合は、編集対象列車の現終着駅であるので、発時刻があっても大丈夫
				if (muCdDedEki->get(aCdDedJikokuOrderKiten.getEkiOrder()).getHatsujikokuHyouji() &&
					!aCentDedEkiJikokuStd.getHatsujikoku().isNull() &&
					iTsuukaBegin != -1)
				{
					continue;
				}
			//}
			//着時刻がNULLなら次列車へ
			if (aCentDedEkiJikokuStd.getChakujikoku().isNull())
			{
				continue;
			}
			//ここまで来たら、コピーの前作業として、iDifferenceTimeを求める。
			iDifferenceTime = aCentDedEkiJikoku.getChakujikoku().subJikoku(aCentDedEkiJikokuStd.getChakujikoku());
			//発時刻表示有の場合は、発時刻のコピーも行ってしまう。
			if (muCdDedEki->get(aCdDedJikokuOrderKiten.getEkiOrder()).getHatsujikokuHyouji() &&
				!aCentDedEkiJikokuStd.getHatsujikoku().isNull())
			{
				aCentDedEkiJikoku.setHatsujikoku(aCentDedEkiJikokuStd.getHatsujikoku().addSeconds(iDifferenceTime));
				aCentDedEkiJikoku.setCentDedAfterOperationCont(*aCentDedEkiJikokuStd.getCentDedAfterOperationCont());
				aCentDedEkiJikoku.getCentDedAfterOperationCont()->modifyOperationJikoku(iDifferenceTime);

				pCentDedRessya->setCentDedEkiJikoku(aCdDedJikokuOrderKiten.getEkiOrder(), aCentDedEkiJikoku);
			}
		}

		//コピーの起点駅の一つ後から、フォーカス位置までのコピーを行う。
		int ord = aCdDedJikokuOrderKiten.getEkiOrder() + 1;
		if (iTsuukaBegin != -1)
		{
			ord = iTsuukaBegin + 1;
		}
		for (; ord <= aCdJikokuOrder.getEkiOrder(); ord++)
		{
			//(1)コピー元の終着駅の場合、作業時刻・路線外発着時刻を補正する。
			//(2)aCdJikokuOrder.getEkiOrder()でフォーカスが着時刻の場合、発時刻をNULLにする。
			//ただし、着時刻表示がない場合は除く
			//なお、aCdJikokuOrder.getEkiOrder()かつコピー元の終着駅の場合は(1)優先になるようにif文を構築する
			//(3)どちらでもない場合は、時刻の補正のみ行う

			CentDedEkiJikoku aCentDedEkiJikokuNew(pCentDedRessyaStd->getCentDedEkiJikoku(ord));
			aCentDedEkiJikokuNew.setChakujikoku(aCentDedEkiJikokuNew.getChakujikoku().addSeconds(iDifferenceTime));
			aCentDedEkiJikokuNew.setHatsujikoku(aCentDedEkiJikokuNew.getHatsujikoku().addSeconds(iDifferenceTime));
			aCentDedEkiJikokuNew.getCentDedBeforeOperationCont()->modifyOperationJikoku(iDifferenceTime);
			aCentDedEkiJikokuNew.getCentDedAfterOperationCont()->modifyOperationJikoku(iDifferenceTime);

			//CentDedRessyaTrack aCentDedRessyaTrackNew(pCentDedRessyaStd->getCentDedRessyaTrack(ord));

/*			if (ord == pCentDedRessyaStd->getSyuuchakuEki())
			{
				aCentDedRessyaTrackNew.setOperationChakuJikoku(aCentDedRessyaTrackNew.getOperationChakuJikoku().addSeconds(iDifferenceTime));
				aCentDedRessyaTrackNew.setOperationHatsuJikoku(aCentDedRessyaTrackNew.getOperationHatsuJikoku().addSeconds(iDifferenceTime));
				aCentDedRessyaTrackNew.setOuterHatsuChakuJikoku(aCentDedRessyaTrackNew.getOuterHatsuChakuJikoku().addSeconds(iDifferenceTime));
			}
			else */if (ord == aCdJikokuOrder.getEkiOrder() &&
				aCdJikokuOrder.getEkiJikokuItem() == CdDedJikokuOrder::EkiJikokuItem_Chaku)
			{
				aCentDedEkiJikokuNew.setHatsujikoku(CdDedJikoku());
			}

			pCentDedRessya->setCentDedEkiJikoku(ord, aCentDedEkiJikokuNew);
			//pCentDedRessya->setCentDedRessyaTrack(ord, aCentDedRessyaTrackNew);
		}
		pCentDedRessya->adjustOperation();
		return 0;
	}
	return -1;
}
int CWjkState_Ressyahensyu::ComplementChakuFromHatsuStdOpeTime(
	int iDiaIndexStandard, 
	int iEkiOrder,
	CentDedRessya * pCentDedRessya)
{
	/*ここへ来る列車は、
		(1)列車の始発駅で
		(2)フォーカスが発着時刻表示駅の着時刻で
		(3)着時刻は空で発時刻が有り＝停車or通過

		従って、基準運転時分から、種別一致、停車or通過一致・発着共に時刻存在の列車を見つけて、コピーすればよい。
	*/
	//基準運転時分ダイヤの中から、コピーの対象にできる列車を探す。
	const CentDedRessyaCont* pCentDedRessyaContStandard =
		getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedDiaCont()
		->getMuPtr()->get(iDiaIndexStandard)->getCentDedRessyaCont(pCentDedRessya->getRessyahoukou());
	int idxRessyasyubetsu = pCentDedRessya->getRessyasyubetsuIndex();

	for (int iRessyaIndexStandard = 0;
		iRessyaIndexStandard < pCentDedRessyaContStandard->size()/*コンテナ内列車数*/;
		iRessyaIndexStandard++)
	{
		//対象列車と同じ種別かどうか確認
		if (pCentDedRessyaContStandard->getMuPtr()->get(iRessyaIndexStandard)->getRessyasyubetsuIndex() != idxRessyasyubetsu)
		{
			continue; //次列車に移行
		}
		//const CentDedRessya* pCentDedRessyaStd = pCentDedRessyaContStandard->getMuPtr()->get(iRessyaIndexStandard);
		CentDedEkiJikoku aCentDedEkiJikoku = pCentDedRessya->getCentDedEkiJikoku(iEkiOrder);
		const CentDedEkiJikoku aCentDedEkiJikokuStd = pCentDedRessyaContStandard->getMuPtr()->get(iRessyaIndexStandard)->getCentDedEkiJikoku(iEkiOrder);
		if (aCentDedEkiJikoku.getEkiatsukai() != aCentDedEkiJikokuStd.getEkiatsukai())
		{
			continue;
		}
		if(aCentDedEkiJikokuStd.getChakujikoku().isNull() ||
			aCentDedEkiJikokuStd.getHatsujikoku().isNull())
		{
			continue;
		}
		int iDifferenceTime = aCentDedEkiJikoku.getHatsujikoku().subJikoku(aCentDedEkiJikokuStd.getHatsujikoku());
		aCentDedEkiJikoku.setChakujikoku(aCentDedEkiJikokuStd.getChakujikoku().addSeconds(iDifferenceTime));

		pCentDedRessya->setCentDedEkiJikoku(iEkiOrder, aCentDedEkiJikoku);

	}
	return 0;
}
int CWjkState_Ressyahensyu::ComplementHatsuFromChakuStdOpeTime(
	int iDiaIndexStandard, 
	int iEkiOrder,
	CentDedRessya * pCentDedRessya)
{
	/*ここへ来る列車は、
		(1)列車の終着駅で
		(2)フォーカスが発着時刻表示駅の発時刻で
		(3)着時刻は有りで発時刻が空＝停車or通過

		従って、基準運転時分から、種別一致、停車or通過一致・発着共に時刻存在の列車を見つけて、コピーすればよい。
	*/
	//基準運転時分ダイヤの中から、コピーの対象にできる列車を探す。
	const CentDedRessyaCont* pCentDedRessyaContStandard =
		getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedDiaCont()
		->getMuPtr()->get(iDiaIndexStandard)->getCentDedRessyaCont(pCentDedRessya->getRessyahoukou());
	int idxRessyasyubetsu = pCentDedRessya->getRessyasyubetsuIndex();

	for (int iRessyaIndexStandard = 0;
		iRessyaIndexStandard < pCentDedRessyaContStandard->size()/*コンテナ内列車数*/;
		iRessyaIndexStandard++)
	{
		//対象列車と同じ種別かどうか確認
		if (pCentDedRessyaContStandard->getMuPtr()->get(iRessyaIndexStandard)->getRessyasyubetsuIndex() != idxRessyasyubetsu)
		{
			continue; //次列車に移行
		}
		//const CentDedRessya* pCentDedRessyaStd = pCentDedRessyaContStandard->getMuPtr()->get(iRessyaIndexStandard);
		CentDedEkiJikoku aCentDedEkiJikoku = pCentDedRessya->getCentDedEkiJikoku(iEkiOrder);
		const CentDedEkiJikoku aCentDedEkiJikokuStd = pCentDedRessyaContStandard->getMuPtr()->get(iRessyaIndexStandard)->getCentDedEkiJikoku(iEkiOrder);
		if (aCentDedEkiJikoku.getEkiatsukai() != aCentDedEkiJikokuStd.getEkiatsukai())
		{
			continue;
		}
		if (aCentDedEkiJikokuStd.getChakujikoku().isNull() ||
			aCentDedEkiJikokuStd.getHatsujikoku().isNull())
		{
			continue;
		}
		int iDifferenceTime = aCentDedEkiJikoku.getChakujikoku().subJikoku(aCentDedEkiJikokuStd.getChakujikoku());
		aCentDedEkiJikoku.setHatsujikoku(aCentDedEkiJikokuStd.getHatsujikoku().addSeconds(iDifferenceTime));

		pCentDedRessya->setCentDedEkiJikoku(iEkiOrder, aCentDedEkiJikoku);

	}
	return 0;
}
void CWjkState_Ressyahensyu::ChangeOperationBeforeDataNext(
	Mu<CentDedRessya*>* muCentDedRessya,
	bool isShift)
{

	for (int i = 0; i < muCentDedRessya->size(); i++)
	{
		CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);
		int iEkiOrder = getCWndDcdGrid()->getYColSpecOfFocus().getEkiOrder();
		CentDedBeforeOperationCont* pBeforeCont = pCentDedRessya->getCentDedEkiJikokuCont()
			->getMuPtr()->get(iEkiOrder)->getCentDedBeforeOperationCont();
		int iOperationIndex = getCWndDcdGrid()->getYColSpecOfFocus().getOperationIndex();
		CentDedEkiCont::CdDedEki aEki = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
			->getCentDedEkiCont()->getMuPtr(pCentDedRessya->getRessyahoukou())->get(iEkiOrder);

		if (pBeforeCont->size() == 0)
		{
			continue;
		}
		int iTargetPos;
		if (pBeforeCont->getMuPtr()->get(0)->isFirstOperation())
		{
			iTargetPos = max(pBeforeCont->size() - aEki.getJikokuhyouBeforeOperation(), 1)
				+ iOperationIndex;
		}
		else
		{
			iTargetPos = max(pBeforeCont->size() - aEki.getJikokuhyouBeforeOperation(), 0)
				+ iOperationIndex;
		}

		if (iTargetPos < pBeforeCont->size())
		{
			CentDedBeforeOperation* pBeforeOperation = pBeforeCont->getMuPtr()->get(iTargetPos);
			if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
			{
				if (pBeforeOperation->getShuntTrackIndex() == aEki.getCentDedEkiTrack2Cont().size() - 1)
				{
					pBeforeOperation->setShuntTrackIndex(0);
				}
				else
				{
					pBeforeOperation->setShuntTrackIndex(pBeforeOperation->getShuntTrackIndex() + 1);
				}

			}
			else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
			{
				pBeforeOperation->setIsConnectToFront(!pBeforeOperation->getIsConnectToFront());
			}
			else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
			{
				if (isShift)
				{
					if (pBeforeOperation->getReleaseIndexCount() < 10)
					{
						pBeforeOperation->setReleaseIndexCount(pBeforeOperation->getReleaseIndexCount() + 1);
					}
				}
				else
				{
					if (pBeforeOperation->getReleasePos() == 0)
					{
						pBeforeOperation->setReleasePos(1);
					}
					else if (pBeforeOperation->getReleasePos() == 1)
					{
						pBeforeOperation->setReleasePos(2);
					}
					else if (pBeforeOperation->getReleasePos() == 2)
					{
						pBeforeOperation->setReleasePos(0);
					}
				}
			}
			//運用番号変更の場合は、動作無し
		}
	}
}
void CWjkState_Ressyahensyu::ChangeOperationBeforeDataPrev(
	Mu<CentDedRessya*>* muCentDedRessya,
	bool isShift)
{

	for (int i = 0; i < muCentDedRessya->size(); i++)
	{
		CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);
		int iEkiOrder = getCWndDcdGrid()->getYColSpecOfFocus().getEkiOrder();
		CentDedBeforeOperationCont* pBeforeCont = pCentDedRessya->getCentDedEkiJikokuCont()
			->getMuPtr()->get(iEkiOrder)->getCentDedBeforeOperationCont();
		int iOperationIndex = getCWndDcdGrid()->getYColSpecOfFocus().getOperationIndex();
		CentDedEkiCont::CdDedEki aEki = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
			->getCentDedEkiCont()->getMuPtr(pCentDedRessya->getRessyahoukou())->get(iEkiOrder);

		if (pBeforeCont->size() == 0)
		{
			continue;
		}
		int iTargetPos;
		if (pBeforeCont->getMuPtr()->get(0)->isFirstOperation())
		{
			iTargetPos = max(pBeforeCont->size() - aEki.getJikokuhyouBeforeOperation(), 1)
				+ iOperationIndex;
			//iTargetPos += idxb;
		}
		else
		{
			iTargetPos = max(pBeforeCont->size() - aEki.getJikokuhyouBeforeOperation(), 0)
				+ iOperationIndex;
		}

		if (iTargetPos < pBeforeCont->size())
		{
			CentDedBeforeOperation* pBeforeOperation = pBeforeCont->getMuPtr()->get(iTargetPos);
			if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
			{
				if (pBeforeOperation->getShuntTrackIndex() == 0)
				{
					pBeforeOperation->setShuntTrackIndex(aEki.getCentDedEkiTrack2Cont().size() - 1);
				}
				else
				{
					pBeforeOperation->setShuntTrackIndex(pBeforeOperation->getShuntTrackIndex() - 1);
				}

			}
			else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
			{
				pBeforeOperation->setIsConnectToFront(!pBeforeOperation->getIsConnectToFront());
			}
			else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
			{
				if (isShift)
				{
					if (pBeforeOperation->getReleaseIndexCount() > 1)
					{
						pBeforeOperation->setReleaseIndexCount(pBeforeOperation->getReleaseIndexCount() - 1);
					}
				}
				else
				{
					if (pBeforeOperation->getReleasePos() == 0)
					{
						pBeforeOperation->setReleasePos(2);
					}
					else if (pBeforeOperation->getReleasePos() == 1)
					{
						pBeforeOperation->setReleasePos(0);
					}
					else if (pBeforeOperation->getReleasePos() == 2)
					{
						pBeforeOperation->setReleasePos(1);
					}
				}
			}
			//運用番号変更の場合は、動作無し
		}
	}
}

void CWjkState_Ressyahensyu::ChangeOperationAfterDataNext(
	Mu<CentDedRessya*>* muCentDedRessya,
	bool isShift)
{
	for (int i = 0; i < muCentDedRessya->size(); i++)
	{
		CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);
		int iEkiOrder = getCWndDcdGrid()->getYColSpecOfFocus().getEkiOrder();
		CentDedAfterOperationCont* pAfterCont = pCentDedRessya->getCentDedEkiJikokuCont()
			->getMuPtr()->get(iEkiOrder)->getCentDedAfterOperationCont();
		int iOperationIndex = getCWndDcdGrid()->getYColSpecOfFocus().getOperationIndex();
		CentDedEkiCont::CdDedEki aEki = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
			->getCentDedEkiCont()->getMuPtr(pCentDedRessya->getRessyahoukou())->get(iEkiOrder);

		if (pAfterCont->size() <= iOperationIndex)
		{
			continue;
		}

		if (!pAfterCont->getMuPtr()->get(iOperationIndex)->isLastOperation())
		{
			CentDedAfterOperation* pAfterOperation = pAfterCont->getMuPtr()->get(iOperationIndex);
			if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
			{
				if (pAfterOperation->getShuntTrackIndex() == aEki.getCentDedEkiTrack2Cont().size() - 1)
				{
					pAfterOperation->setShuntTrackIndex(0);
				}
				else
				{
					pAfterOperation->setShuntTrackIndex(pAfterOperation->getShuntTrackIndex() + 1);
				}

			}
			else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
			{
				pAfterOperation->setIsConnectToFront(!pAfterOperation->getIsConnectToFront());
			}
			else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
			{
				if (isShift)
				{
					if (pAfterOperation->getReleaseIndexCount() < 10)
					{
						pAfterOperation->setReleaseIndexCount(pAfterOperation->getReleaseIndexCount() + 1);
					}
				}
				else
				{
					if (pAfterOperation->getReleasePos() == 0)
					{
						pAfterOperation->setReleasePos(1);
					}
					else if (pAfterOperation->getReleasePos() == 1)
					{
						pAfterOperation->setReleasePos(2);
					}
					else if (pAfterOperation->getReleasePos() == 2)
					{
						pAfterOperation->setReleasePos(0);
					}
				}
			}
			//運用番号変更の場合は、動作無し
		}
	}
}

void CWjkState_Ressyahensyu::ChangeOperationAfterDataPrev(
	Mu<CentDedRessya*>* muCentDedRessya,
	bool isShift)
{

	for (int i = 0; i < muCentDedRessya->size(); i++)
	{
		CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);
		int iEkiOrder = getCWndDcdGrid()->getYColSpecOfFocus().getEkiOrder();
		CentDedAfterOperationCont* pAfterCont = pCentDedRessya->getCentDedEkiJikokuCont()
			->getMuPtr()->get(iEkiOrder)->getCentDedAfterOperationCont();
		int iOperationIndex = getCWndDcdGrid()->getYColSpecOfFocus().getOperationIndex();
		CentDedEkiCont::CdDedEki aEki = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
			->getCentDedEkiCont()->getMuPtr(pCentDedRessya->getRessyahoukou())->get(iEkiOrder);

		if (pAfterCont->size() <= iOperationIndex)
		{
			continue;
		}

		if (!pAfterCont->getMuPtr()->get(iOperationIndex)->isLastOperation())
		{
			CentDedAfterOperation* pAfterOperation = pAfterCont->getMuPtr()->get(iOperationIndex);
			if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
			{
				if (pAfterOperation->getShuntTrackIndex() == 0)
				{
					pAfterOperation->setShuntTrackIndex(aEki.getCentDedEkiTrack2Cont().size() - 1);
				}
				else
				{
					pAfterOperation->setShuntTrackIndex(pAfterOperation->getShuntTrackIndex() - 1);
				}

			}
			else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
			{
				pAfterOperation->setIsConnectToFront(!pAfterOperation->getIsConnectToFront());
			}
			else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
			{
				if (isShift )
				{
					if ( pAfterOperation->getReleaseIndexCount() > 1)
					{
						pAfterOperation->setReleaseIndexCount(pAfterOperation->getReleaseIndexCount() - 1);
					}
				}
				else
				{
					if (pAfterOperation->getReleasePos() == 0)
					{
						pAfterOperation->setReleasePos(2);
					}
					else if (pAfterOperation->getReleasePos() == 1)
					{
						pAfterOperation->setReleasePos(0);
					}
					else if (pAfterOperation->getReleasePos() == 2)
					{
						pAfterOperation->setReleasePos(1);
					}
				}
			}
			//運用番号変更の場合は、動作無し
		}
	}
}
void CWjkState_Ressyahensyu::ChangeOperationBeforeTypeNext(
	Mu<CentDedRessya*>* muCentDedRessya)
{
	for (int i = 0; i < muCentDedRessya->size(); i++)
	{
		CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);
		int iEkiOrder = getCWndDcdGrid()->getYColSpecOfFocus().getEkiOrder();
		CentDedBeforeOperationCont* pBeforeCont = pCentDedRessya->getCentDedEkiJikokuCont()
			->getMuPtr()->get(iEkiOrder)->getCentDedBeforeOperationCont();
		int iOperationIndex = getCWndDcdGrid()->getYColSpecOfFocus().getOperationIndex();
		CentDedEkiCont::CdDedEki aEki = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
			->getCentDedEkiCont()->getMuPtr(pCentDedRessya->getRessyahoukou())->get(iEkiOrder);

		int iTargetPos;
		if (pBeforeCont->size() == 0)
		{
			iTargetPos = 0;
		}
		else if (pBeforeCont->getMuPtr()->get(0)->isFirstOperation())
		{
			iTargetPos = max(pBeforeCont->size() - aEki.getJikokuhyouBeforeOperation(), 1)
				+ iOperationIndex;
		}
		else
		{
			iTargetPos = max(pBeforeCont->size() - aEki.getJikokuhyouBeforeOperation(), 0)
				+ iOperationIndex;
		}

		if (iTargetPos < pBeforeCont->size())
		{
			//作業が存在する場合、入換なら削除、解結なら解結Indexの変更を行う
			//仕様変更
			//2.00.05再仕様変更
			//入換→増結、増結→解結、解結・運用番号変更→削除
			CentDedBeforeOperation* pBeforeOperation = pBeforeCont->getMuPtr()->get(iTargetPos);
			if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
			{
				CentDedBeforeOperation aBeforeOperation(
					CentDedBeforeOperation::EBOperation::BOperation_Connect,
					false,
					pBeforeOperation->getOperationHatsuJikoku());

				pBeforeCont->set(aBeforeOperation, iTargetPos);
				pCentDedRessya->adjustOperation();
			}
			else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
			{
				CentDedBeforeOperation aBeforeOperation(
					CentDedBeforeOperation::EBOperation::BOperation_Release,
					0,1,
					pBeforeOperation->getConnectJikoku());

				pBeforeCont->set(aBeforeOperation, iTargetPos);
				pCentDedRessya->adjustOperation();
			}
			else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release ||
				pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_NumberChange)
			{
				pBeforeCont->erase(iTargetPos);
			}
		}
		else
		{
			//空白箇所を選択している場合は、そこに入換作業を追加する
			//厳密には、この駅の駅扱いや分岐関係を見て、作業付加の可否を判定する必要があるが、
			//とりあえず付加だけして、チェック作業はadjustOperationに丸投げする。
			//iTargetPos = pBeforeCont->size();
			//入換作業を追加するときは、デフォルト入換番線を取得する

			CdDedJikoku aShuntJikoku;
			if (!pCentDedRessya->getCentDedEkiJikoku(iEkiOrder).getChakujikoku(false).isNull())
			{
				aShuntJikoku = pCentDedRessya->getCentDedEkiJikoku(iEkiOrder).getChakujikoku(false);
				aShuntJikoku.addSeconds(60);
			}
			else if(!pCentDedRessya->getCentDedEkiJikoku(iEkiOrder).getHatsujikoku(false).isNull())
			{
				aShuntJikoku = pCentDedRessya->getCentDedEkiJikoku(iEkiOrder).getHatsujikoku(false);
				aShuntJikoku.addSeconds(-60);
			}
			if (!aShuntJikoku.isNull())
			{
				int iStandardShuntTrackIndex[2] = { 0,0 };
				int iChakuEkiOrder = iEkiOrder;
				int iHatsuEkiOrder = iEkiOrder;
				if (iEkiOrder == pCentDedRessya->getValidSihatsuEki())
				{
					iChakuEkiOrder = -1;
				}
				if (iEkiOrder == pCentDedRessya->getValidSyuuchakuEki())
				{
					iHatsuEkiOrder = -1;
				}
				getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
					->StandardShuntTrackIndexSearch(
						pCentDedRessya->getRessyasyubetsuIndex(),
						getRessyahoukou(),
						iChakuEkiOrder,
						iHatsuEkiOrder,
						iStandardShuntTrackIndex);

				CentDedBeforeOperation aBeforeOperation(
					CentDedBeforeOperation::EBOperation::BOperation_Shunt,
					iStandardShuntTrackIndex[0],
					aShuntJikoku,
					CdDedJikoku(),
					false);

				pBeforeCont->insert(aBeforeOperation, INT_MAX);
				pCentDedRessya->adjustOperation();
			}
		}

	}
}
void CWjkState_Ressyahensyu::ChangeOperationBeforeTypePrev(
	Mu<CentDedRessya*>* muCentDedRessya)
{
	for (int i = 0; i < muCentDedRessya->size(); i++)
	{
		CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);
		int iEkiOrder = getCWndDcdGrid()->getYColSpecOfFocus().getEkiOrder();
		CentDedBeforeOperationCont* pBeforeCont = pCentDedRessya->getCentDedEkiJikokuCont()
			->getMuPtr()->get(iEkiOrder)->getCentDedBeforeOperationCont();
		int iOperationIndex = getCWndDcdGrid()->getYColSpecOfFocus().getOperationIndex();
		CentDedEkiCont::CdDedEki aEki = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
			->getCentDedEkiCont()->getMuPtr(pCentDedRessya->getRessyahoukou())->get(iEkiOrder);

		int iTargetPos;
		if (pBeforeCont->size() == 0)
		{
			iTargetPos = 0;
		}
		else if (pBeforeCont->getMuPtr()->get(0)->isFirstOperation())
		{
			iTargetPos = max(pBeforeCont->size() - aEki.getJikokuhyouBeforeOperation(), 1)
				+ iOperationIndex;
		}
		else
		{
			iTargetPos = max(pBeforeCont->size() - aEki.getJikokuhyouBeforeOperation(), 0)
				+ iOperationIndex;
		}

		if (iTargetPos < pBeforeCont->size())
		{
			//作業が存在する場合、入換なら削除、解結なら解結Indexの変更を行う
			//仕様変更
			//2.00.05再仕様変更
			//入換→削除、増結→入換、解結→増結、運用番号変更→解結
			CentDedBeforeOperation* pBeforeOperation = pBeforeCont->getMuPtr()->get(iTargetPos);
			if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
			{
				pBeforeCont->erase(iTargetPos);
			}
			else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
			{
				int iStandardShuntTrackIndex[2] = { 0,0 };
				int iChakuEkiOrder = iEkiOrder;
				int iHatsuEkiOrder = iEkiOrder;
				if (iEkiOrder == pCentDedRessya->getValidSihatsuEki())
				{
					iChakuEkiOrder = -1;
				}
				if (iEkiOrder == pCentDedRessya->getValidSyuuchakuEki())
				{
					iHatsuEkiOrder = -1;
				}
				getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
					->StandardShuntTrackIndexSearch(
						pCentDedRessya->getRessyasyubetsuIndex(),
						getRessyahoukou(),
						iChakuEkiOrder,
						iHatsuEkiOrder,
						iStandardShuntTrackIndex);

				CentDedBeforeOperation aBeforeOperation(
					CentDedBeforeOperation::EBOperation::BOperation_Shunt,
					iStandardShuntTrackIndex[0],
					pBeforeOperation->getConnectJikoku(),
					CdDedJikoku(),
					false);

				pBeforeCont->set(aBeforeOperation, iTargetPos);
				pCentDedRessya->adjustOperation();
			}
			else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
			{
				CentDedBeforeOperation aBeforeOperation(
					CentDedBeforeOperation::EBOperation::BOperation_Connect,
					false,
					pBeforeOperation->getReleaseJikoku());

				pBeforeCont->set(aBeforeOperation, iTargetPos);
				pCentDedRessya->adjustOperation();
			}
			else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_NumberChange)
			{
				CdDedJikoku aReleaseJikoku;
				if (!pCentDedRessya->getCentDedEkiJikoku(iEkiOrder).getChakujikoku(false).isNull())
				{
					aReleaseJikoku = pCentDedRessya->getCentDedEkiJikoku(iEkiOrder).getChakujikoku(false);
				}
				else if (!pCentDedRessya->getCentDedEkiJikoku(iEkiOrder).getHatsujikoku(false).isNull())
				{
					aReleaseJikoku = pCentDedRessya->getCentDedEkiJikoku(iEkiOrder).getHatsujikoku(false);
				}
				if (!aReleaseJikoku.isNull())
				{
					CentDedBeforeOperation aBeforeOperation(
						CentDedBeforeOperation::EBOperation::BOperation_Release,
						0, 1,
						aReleaseJikoku);

					pBeforeCont->set(aBeforeOperation, iTargetPos);
					pCentDedRessya->adjustOperation();
				}
			}
		}
		else
		{
			//空白箇所を選択している場合は、そこに入換作業を追加する
			//厳密には、この駅の駅扱いや分岐関係を見て、作業付加の可否を判定する必要があるが、
			//とりあえず付加だけして、チェック作業はadjustOperationに丸投げする。
			//iTargetPos = pBeforeCont->size();
			//仕様変更
			//解結作業を追加する
			//2.00.05再仕様変更　運用番号変更作業を追加する

			CdDedJikoku aReleaseJikoku;
			if (!pCentDedRessya->getCentDedEkiJikoku(iEkiOrder).getChakujikoku(false).isNull())
			{
				aReleaseJikoku = pCentDedRessya->getCentDedEkiJikoku(iEkiOrder).getChakujikoku(false);
			}
			else if (!pCentDedRessya->getCentDedEkiJikoku(iEkiOrder).getHatsujikoku(false).isNull())
			{
				aReleaseJikoku = pCentDedRessya->getCentDedEkiJikoku(iEkiOrder).getHatsujikoku(false);
			}
			if (!aReleaseJikoku.isNull())
			{
				CentDedBeforeOperation aBeforeOperation(
					CentDedBeforeOperation::EBOperation::BOperation_Release,
					0, 1,
					aReleaseJikoku);

				pBeforeCont->insert(aBeforeOperation, INT_MAX);
				pCentDedRessya->adjustOperation();
			}
		}

	}
}
void CWjkState_Ressyahensyu::ChangeOperationAfterTypeNext(
	Mu<CentDedRessya*>* muCentDedRessya)
{
	for (int i = 0; i < muCentDedRessya->size(); i++)
	{
		CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);
		int iEkiOrder = getCWndDcdGrid()->getYColSpecOfFocus().getEkiOrder();
		CentDedAfterOperationCont* pAfterCont = pCentDedRessya->getCentDedEkiJikokuCont()
			->getMuPtr()->get(iEkiOrder)->getCentDedAfterOperationCont();
		int iOperationIndex = getCWndDcdGrid()->getYColSpecOfFocus().getOperationIndex();
		CentDedEkiCont::CdDedEki aEki = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
			->getCentDedEkiCont()->getMuPtr(pCentDedRessya->getRessyahoukou())->get(iEkiOrder);

		/**
			iOperationIndexがpAfterCont->size()-1未満の場合は、既存作業の変更
			iOperationIndexがpAfterCont->size()-1の場合は、作業種類を見て、
				終端作業なら入換を挿入、それ以外なら既存作業の変更
			iOperationIndexがpAfterCont->size()以上の場合は、入換の挿入
		*/
		int iType = -1;
		if (pAfterCont->size() -1 > iOperationIndex)
		{
			iType = 0;
		}
		else if (pAfterCont->size() - 1 == iOperationIndex)
		{
			if (pAfterCont->getMuPtr()->get(INT_MAX)->isLastOperation())
			{
				iType = 1;
			}
			else
			{
				iType = 0;
			}
		}
		else
		{
			iType = 1;
		}

		if (iType == 1)
		{
			//空白箇所を選択している場合は、そこに入換作業を追加する
			//厳密には、この駅の駅扱いや分岐関係を見て、作業付加の可否を判定する必要があるが、
			//とりあえず付加だけして、チェック作業はadjustOperationに丸投げする。

			CdDedJikoku aShuntJikoku;
			if (!pCentDedRessya->getCentDedEkiJikoku(iEkiOrder).getHatsujikoku(false).isNull())
			{
				aShuntJikoku = pCentDedRessya->getCentDedEkiJikoku(iEkiOrder).getHatsujikoku(false);
				aShuntJikoku.addSeconds(-60);
			}
			else if (!pCentDedRessya->getCentDedEkiJikoku(iEkiOrder).getChakujikoku(false).isNull())
			{
				aShuntJikoku = pCentDedRessya->getCentDedEkiJikoku(iEkiOrder).getChakujikoku(false);
				aShuntJikoku.addSeconds(60);
			}
			if (!aShuntJikoku.isNull())
			{
				int iStandardShuntTrackIndex[2] = { 0,0 };
				int iChakuEkiOrder = iEkiOrder;
				int iHatsuEkiOrder = iEkiOrder;
				if (iEkiOrder == pCentDedRessya->getValidSihatsuEki())
				{
					iChakuEkiOrder = -1;
				}
				if (iEkiOrder == pCentDedRessya->getValidSyuuchakuEki())
				{
					iHatsuEkiOrder = -1;
				}
				getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
					->StandardShuntTrackIndexSearch(
						pCentDedRessya->getRessyasyubetsuIndex(),
						getRessyahoukou(),
						iChakuEkiOrder,
						iHatsuEkiOrder,
						iStandardShuntTrackIndex);

				CentDedAfterOperation aAfterOperation(
					CentDedAfterOperation::EAOperation::AOperation_Shunt,
					iStandardShuntTrackIndex[1],
					aShuntJikoku,
					CdDedJikoku(),
					false);
				if (pAfterCont->size() == 0)
				{
					pAfterCont->insert(aAfterOperation, INT_MAX);
				}
				else if (pAfterCont->getMuPtr()->get(INT_MAX)->isLastOperation())
				{
					pAfterCont->insert(aAfterOperation, pAfterCont->size() - 1);
				}
				else
				{
					pAfterCont->insert(aAfterOperation, INT_MAX);
				}

				pCentDedRessya->adjustOperation();
			}
		}
		else if (iType == 0)
		{
			//入換→増結、増結→解結、解結・運用番号変更→削除
			CentDedAfterOperation* pAfterOperation = pAfterCont->getMuPtr()->get(iOperationIndex);
			if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
			{
				CentDedAfterOperation aAfterOperation(
					CentDedAfterOperation::EAOperation::AOperation_Connect,
					false,
					pAfterOperation->getOperationHatsuJikoku());

				pAfterCont->set(aAfterOperation, iOperationIndex);
				pCentDedRessya->adjustOperation();

			}
			else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
			{
				CentDedAfterOperation aAfterOperation(
					CentDedAfterOperation::EAOperation::AOperation_Release,
					0, 1,
					pAfterOperation->getConnectJikoku());

				pAfterCont->set(aAfterOperation, iOperationIndex);
				pCentDedRessya->adjustOperation();
			}
			else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release ||
				pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_NumberChange)
			{
				pAfterCont->erase(iOperationIndex);
			}
		}
	}
}
void CWjkState_Ressyahensyu::ChangeOperationAfterTypePrev(
	Mu<CentDedRessya*>* muCentDedRessya)
{
	for (int i = 0; i < muCentDedRessya->size(); i++)
	{
		CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);
		int iEkiOrder = getCWndDcdGrid()->getYColSpecOfFocus().getEkiOrder();
		CentDedAfterOperationCont* pAfterCont = pCentDedRessya->getCentDedEkiJikokuCont()
			->getMuPtr()->get(iEkiOrder)->getCentDedAfterOperationCont();
		int iOperationIndex = getCWndDcdGrid()->getYColSpecOfFocus().getOperationIndex();
		CentDedEkiCont::CdDedEki aEki = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
			->getCentDedEkiCont()->getMuPtr(pCentDedRessya->getRessyahoukou())->get(iEkiOrder);

		/**
			iOperationIndexがpAfterCont->size()-1未満の場合は、既存作業の変更
			iOperationIndexがpAfterCont->size()-1の場合は、作業種類を見て、
				終端作業なら入換を挿入、それ以外なら既存作業の変更
			iOperationIndexがpAfterCont->size()以上の場合は、入換の挿入
		*/
		int iType = -1;
		if (pAfterCont->size() - 1 > iOperationIndex)
		{
			iType = 0;
		}
		else if (pAfterCont->size() - 1 == iOperationIndex)
		{
			if (pAfterCont->getMuPtr()->get(INT_MAX)->isLastOperation())
			{
				iType = 1;
			}
			else
			{
				iType = 0;
			}
		}
		else
		{
			iType = 1;
		}

		if (iType == 1)
		{
			//空白箇所を選択している場合は、そこに入換作業を追加する
			//厳密には、この駅の駅扱いや分岐関係を見て、作業付加の可否を判定する必要があるが、
			//とりあえず付加だけして、チェック作業はadjustOperationに丸投げする。
			//仕様変更
			//解結作業を追加する
			//2.00.05再仕様変更　運用番号変更作業を追加する

			CdDedJikoku aReleaseJikoku;
			if (!pCentDedRessya->getCentDedEkiJikoku(iEkiOrder).getHatsujikoku(false).isNull())
			{
				aReleaseJikoku = pCentDedRessya->getCentDedEkiJikoku(iEkiOrder).getHatsujikoku(false);
			}
			else if (!pCentDedRessya->getCentDedEkiJikoku(iEkiOrder).getChakujikoku(false).isNull())
			{
				aReleaseJikoku = pCentDedRessya->getCentDedEkiJikoku(iEkiOrder).getChakujikoku(false);
			}
			if (!aReleaseJikoku.isNull())
			{
				CentDedAfterOperation aAfterOperation(
					CentDedAfterOperation::EAOperation::AOperation_Release,
					0, 1,
					aReleaseJikoku);

				if (pAfterCont->size() == 0)
				{
					pAfterCont->insert(aAfterOperation, INT_MAX);
				}
				else if (pAfterCont->getMuPtr()->get(INT_MAX)->isLastOperation())
				{
					pAfterCont->insert(aAfterOperation, pAfterCont->size() - 1);
				}
				else
				{
					pAfterCont->insert(aAfterOperation, INT_MAX);
				}

				pCentDedRessya->adjustOperation();
			}

		}
		else if (iType == 0)
		{
			//入換→削除、増結→入換、解結→増結、運用番号変更→解結
			CentDedAfterOperation* pAfterOperation = pAfterCont->getMuPtr()->get(iOperationIndex);
			if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
			{
				pAfterCont->erase(iOperationIndex);

			}
			else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
			{
				int iStandardShuntTrackIndex[2] = { 0,0 };
				int iChakuEkiOrder = iEkiOrder;
				int iHatsuEkiOrder = iEkiOrder;
				if (iEkiOrder == pCentDedRessya->getValidSihatsuEki())
				{
					iChakuEkiOrder = -1;
				}
				if (iEkiOrder == pCentDedRessya->getValidSyuuchakuEki())
				{
					iHatsuEkiOrder = -1;
				}
				getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
					->StandardShuntTrackIndexSearch(
						pCentDedRessya->getRessyasyubetsuIndex(),
						getRessyahoukou(),
						iChakuEkiOrder,
						iHatsuEkiOrder,
						iStandardShuntTrackIndex);

				CentDedAfterOperation aAfterOperation(
					CentDedAfterOperation::EAOperation::AOperation_Shunt,
					iStandardShuntTrackIndex[1],
					pAfterOperation->getConnectJikoku(),
					CdDedJikoku(),
					false);

				pAfterCont->set(aAfterOperation, iOperationIndex);
				pCentDedRessya->adjustOperation();
			}
			else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
			{
				CentDedAfterOperation aAfterOperation(
					CentDedAfterOperation::EAOperation::AOperation_Connect,
					false,
					pAfterOperation->getReleaseJikoku());

				pAfterCont->set(aAfterOperation, iOperationIndex);
				pCentDedRessya->adjustOperation();
			}
			else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_NumberChange)
			{
				CdDedJikoku aReleaseJikoku;
				if (!pCentDedRessya->getCentDedEkiJikoku(iEkiOrder).getHatsujikoku(false).isNull())
				{
					aReleaseJikoku = pCentDedRessya->getCentDedEkiJikoku(iEkiOrder).getHatsujikoku(false);
				}
				else if (!pCentDedRessya->getCentDedEkiJikoku(iEkiOrder).getChakujikoku(false).isNull())
				{
					aReleaseJikoku = pCentDedRessya->getCentDedEkiJikoku(iEkiOrder).getChakujikoku(false);
				}
				if (!aReleaseJikoku.isNull())
				{
					CentDedAfterOperation aAfterOperation(
						CentDedAfterOperation::EAOperation::AOperation_Release,
						0, 1,
						aReleaseJikoku);

					pAfterCont->set(aAfterOperation, iOperationIndex);
					pCentDedRessya->adjustOperation();
				}
			}
		}
	}
}

void CWjkState_Ressyahensyu::ChangeOperationBeforeJikoku(
	Mu<CentDedRessya*>* muCentDedRessya, 
	int iShiftSecond)
{
	for (int i = 0; i < muCentDedRessya->size(); i++)
	{
		CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);
		int iEkiOrder = getCWndDcdGrid()->getYColSpecOfFocus().getEkiOrder();
		CentDedBeforeOperationCont* pBeforeCont = pCentDedRessya->getCentDedEkiJikokuCont()
			->getMuPtr()->get(iEkiOrder)->getCentDedBeforeOperationCont();
		int iOperationIndex = getCWndDcdGrid()->getYColSpecOfFocus().getOperationIndex();
		CentDedEkiCont::CdDedEki aEki = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
			->getCentDedEkiCont()->getMuPtr(pCentDedRessya->getRessyahoukou())->get(iEkiOrder);

		int iTargetPos;
		if (pBeforeCont->size() == 0)
		{
			iTargetPos = 0;
		}
		else if (pBeforeCont->getMuPtr()->get(0)->isFirstOperation())
		{
			iTargetPos = max(pBeforeCont->size() - aEki.getJikokuhyouBeforeOperation(), 1)
				+ iOperationIndex;
		}
		else
		{
			iTargetPos = max(pBeforeCont->size() - aEki.getJikokuhyouBeforeOperation(), 0)
				+ iOperationIndex;
		}

		if (iTargetPos < pBeforeCont->size())
		{
			pBeforeCont->getMuPtr()->get(iTargetPos)->modifyOperationJikoku(iShiftSecond);
		}
	}
}

void CWjkState_Ressyahensyu::ChangeOperationAfterJikoku(
	Mu<CentDedRessya*>* muCentDedRessya,
	int iShiftSecond)
{
	for (int i = 0; i < muCentDedRessya->size(); i++)
	{
		CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);
		int iEkiOrder = getCWndDcdGrid()->getYColSpecOfFocus().getEkiOrder();
		CentDedAfterOperationCont* pAfterCont = pCentDedRessya->getCentDedEkiJikokuCont()
			->getMuPtr()->get(iEkiOrder)->getCentDedAfterOperationCont();
		int iOperationIndex = getCWndDcdGrid()->getYColSpecOfFocus().getOperationIndex();
		CentDedEkiCont::CdDedEki aEki = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
			->getCentDedEkiCont()->getMuPtr(pCentDedRessya->getRessyahoukou())->get(iEkiOrder);

		if (pAfterCont->size() <= iOperationIndex)
		{
			continue;
		}

		if (!pAfterCont->getMuPtr()->get(iOperationIndex)->isLastOperation())
		{
			pAfterCont->getMuPtr()->get(iOperationIndex)->modifyOperationJikoku(iShiftSecond);
		}
	}
}

void CWjkState_Ressyahensyu::ChangeRessyasyubetsuNext(
	Mu<CentDedRessya*>* muCentDedRessya)
{
	for (int i = 0; i < muCentDedRessya->size(); i++)
	{
		CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);
		int iSyubetsuCount = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
			->getCentDedRessyasyubetsuCont()->size();
		if (pCentDedRessya->getRessyasyubetsuIndex() >= iSyubetsuCount - 1)
		{
			pCentDedRessya->setRessyasyubetsuIndex(0);
		}
		else
		{
			pCentDedRessya->setRessyasyubetsuIndex(pCentDedRessya->getRessyasyubetsuIndex() + 1);
		}
	}
}

void CWjkState_Ressyahensyu::ChangeRessyasyubetsuPrev(
	Mu<CentDedRessya*>* muCentDedRessya)
{
	for (int i = 0; i < muCentDedRessya->size(); i++)
	{
		CentDedRessya* pCentDedRessya = muCentDedRessya->get(i);
		int iSyubetsuCount = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
			->getCentDedRessyasyubetsuCont()->size();
		if (pCentDedRessya->getRessyasyubetsuIndex() == 0)
		{
			pCentDedRessya->setRessyasyubetsuIndex(iSyubetsuCount - 1);
		}
		else
		{
			pCentDedRessya->setRessyasyubetsuIndex(pCentDedRessya->getRessyasyubetsuIndex() - 1);
		}
	}
}

void CWjkState_Ressyahensyu::AdjustBrunchLoop(
	int iEkiOrder, CentDedRessya* pCentDedRessya,
	int iEkiAtsukaiPrev)
{
	if (pCentDedRessya->getValidSihatsuEki()<0)
	{
		return;
	}
	const CentDedEkiCont* pCentDedEkiCont = getCDiagramEditDoc()->getCDedRosenFileData()
		->getCentDedRosen()->getCentDedEkiCont();
	int iEkiCount = pCentDedRessya->getCentDedEkiJikokuCount();
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
				getCWndDcdGrid()->getRessyahoukou(),
				iEkiOrderBrunchOriginSideThis,
				iEkiOrderLoopThis,
				iEkiOrderBrunchTerminalSideThis);
			if (iResult != -1 && iEkiAtsukaiPrev == 0)
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
	for (int ord = pCentDedRessya->getValidSihatsuEki();
		ord <= pCentDedRessya->getValidSyuuchakuEki(); ord++)
	{
		deque<int> iEkiOrderBrunchOriginSide;
		deque<int> iEkiOrderLoop;
		deque<int> iEkiOrderBrunchTerminalSide;
		deque<int> iEkiOrderChecked;
		//if (iEkiOrder == ord)
		//{
		//	continue;
		//}
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
			getCWndDcdGrid()->getRessyahoukou(),
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
//ここまでchange_by_d_mania

		// ********************************
		//@name	CWndDcdGrid
		// ********************************
void CWjkState_Ressyahensyu::OnSetFocusCell( 
		CDcdGridCell* pCDcdGridCell ) 
{
}

void CWjkState_Ressyahensyu::OnChangeSelectCell( 
		int iXColumnNumber , int iYColumnNumber , bool bIsSelected ) 
{
	super::OnChangeSelectCell( iXColumnNumber , iYColumnNumber , bIsSelected );
}



} } // namespace WndJikokuhyou namespace ViewJikokuhyou
