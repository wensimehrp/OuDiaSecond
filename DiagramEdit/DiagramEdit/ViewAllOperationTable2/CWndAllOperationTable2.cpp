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
// CWndAllOperationTable2.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"

#include "DcdCd\Pos\CconvDcdPosOnZone_PosOrgAndRate.h"
#include "DcDraw\CConverter_WinGdi.h"
#include "DcDraw\CDcdTargetOnPaint.h"
#include "DcDraw\CDcdTargetGetDC.h"
#include "WinUtil\CconvWinUser.h"
#include "LogMsg\LogMsg.h"

#include "..\DiagramEdit.h"
#include "CWndAllOperationTable2.h"
#include "..\ViewJikokuhyou\CJikokuhyouView.h"
#include "..\ViewOperationTable\COperationTableView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace ViewAllOperationTable2 {

using namespace DcDrawLib::WinUtil;

/////////////////////////////////////////////////////////////////////////////
// CWndAllOperationTable2
// ********************************
//	CWndAllOperationTable2
// ********************************
// --------------------------------
//@name 下請関数
// --------------------------------
bool CWndAllOperationTable2::update_adjustProp() 
{
	bool	bRv = false ;

	CDcdTargetGetDC	aTarget( GetSafeHwnd() ) ;

	LogMsg(_T("CWndAllOperationTable2::update_adjustProp() Target.GetZone()=X(%d,%d)Y(%d,%d)")  ,
		aTarget.getZone().getX().getPos() , 
		aTarget.getZone().getX().getSize() , 
		aTarget.getZone().getY().getPos() , 
		aTarget.getZone().getY().getSize() ) ;

	// --------------------------------		
	//	m_pCDcdAllOperationTable2->m_CconvContentPosToDcdTarget の値を正規化
	// --------------------------------		
	{
		CdDcdZoneXy zoneDgrInDcd ;
		CdDcdZoneXy zoneDgr ;
		//if ( m_pCDcdAllOperationTable2->getCentDedDgrDia() != NULL ){
		//	zoneDgr = m_pCDcdAllOperationTable2->getCentDedDgrDia()->getZone();
		//}
		if (m_pCDcdAllOperationTable2->getCdDcdZone() != NULL) 
		{
			zoneDgr = *m_pCDcdAllOperationTable2->getCdDcdZone();
		}
		zoneDgrInDcd = m_pCDcdAllOperationTable2->getZone_Dgr( &aTarget ) ;
		//zoneDgr = ダイヤグラムの座標の範囲
		//	(X方向=(0,24時間),Y方向=(0,終点のダイヤグラム座標)
		//zoneDgrInDcd = ウインドウに表示されている範囲の
		//	ダイヤグラム座標

		LogMsg(_T("\t zoneDgr=X(%d,%d)Y(%d,%d)")  ,
			zoneDgr.getX().getPos() , 
			zoneDgr.getX().getSize() , 
			zoneDgr.getY().getPos() , 
			zoneDgr.getY().getSize() ) ;

		LogMsg(_T("\t zoneDgrInDcd=X(%d,%d)Y(%d,%d)")  ,
			zoneDgrInDcd.getX().getPos() , 
			zoneDgrInDcd.getX().getSize() , 
			zoneDgrInDcd.getY().getPos() , 
			zoneDgrInDcd.getY().getSize() ) ;


		// --------------------------------		
		//	X座標
		// --------------------------------		
		{

			LogMsg(_T("CWndAllOperationTable2::update_adjustProp() ")
				_T("zoneDgrInDcd.getX()=(%d,%d)")  ,
				zoneDgrInDcd.getX().getPos() ,
				zoneDgrInDcd.getX().getSize() ) ;

			//	コンテンツの右(下)端が、
			//	ターゲットのDcDrawの右(下)端よりも左(上)に
			//	寄っていて、右(下)に空きがある場合は、
			//	一旦コンテンツを右(下)に寄せます。
			if ( zoneDgrInDcd.getX().getEndPos() 
					> zoneDgr.getX().getEndPos() ){
				CdDcdZone	aCdDcdZone = zoneDgrInDcd.getX() ;
				aCdDcdZone.setPos( 
					zoneDgr.getX().getEndPos() - zoneDgrInDcd.getX().getSize() ) ;
				zoneDgrInDcd.setX( aCdDcdZone ) ;
			}

			//	コンテンツのPos(左(上)の端)が
			//	ターゲットのDcDrawのPos(左(上))よりも右(下)に
			//	寄っていて、左(上)に空きがある場合は、
			//	コンテンツを左(上)に寄せます。
			if ( zoneDgrInDcd.getX().getPos() < zoneDgr.getX().getPos() ){
				CdDcdZone	aCdDcdZone = zoneDgrInDcd.getX() ;
				aCdDcdZone.setPos( zoneDgr.getX().getPos() ) ;
				zoneDgrInDcd.setX( aCdDcdZone ) ;
			}
		}
		// --------------------------------		
		//	Y座標
		// --------------------------------		
		{
			//	コンテンツの右(下)端が、
			//	ターゲットのDcDrawの右(下)端よりも左(上)に
			//	寄っていて、右(下)に空きがある場合は、
			//	一旦コンテンツを右(下)に寄せます。
			if ( zoneDgrInDcd.getY().getEndPos() 
					> zoneDgr.getY().getEndPos() ){
				CdDcdZone	aCdDcdZone = zoneDgrInDcd.getY() ;
				aCdDcdZone.setPos( 
					zoneDgr.getY().getEndPos() - zoneDgrInDcd.getY().getSize() ) ;
				zoneDgrInDcd.setY( aCdDcdZone ) ;
			}

			//	コンテンツのPos(左(上)の端)が
			//	ターゲットのDcDrawのPos(左(上))よりも右(下)に
			//	寄っていて、左(上)に空きがある場合は、
			//	コンテンツを左(上)に寄せます。
			if ( zoneDgrInDcd.getY().getPos() < zoneDgr.getY().getPos() ){
				CdDcdZone	aCdDcdZone = zoneDgrInDcd.getY() ;
				aCdDcdZone.setPos( zoneDgr.getY().getPos() ) ;
				zoneDgrInDcd.setY( aCdDcdZone ) ;
			}
		}
		LogMsg(_T("\t zoneDgrInDcd=X(%d,%d)Y(%d,%d)")  ,
			zoneDgrInDcd.getX().getPos() , 
			zoneDgrInDcd.getX().getSize() , 
			zoneDgrInDcd.getY().getPos() , 
			zoneDgrInDcd.getY().getSize() ) ;
	
		// --------------------------------
		if ( zoneDgrInDcd != m_pCDcdAllOperationTable2->getZone_Dgr(  &aTarget  ) ){
			m_pCDcdAllOperationTable2->setZone_Dgr(  &aTarget , zoneDgrInDcd ) ;
			bRv = true ;
		}
	}

	return ( bRv ) ;
}

void CWndAllOperationTable2::update_updateScreen() 
{
	CDcdTargetGetDC	aTarget( GetSafeHwnd() ) ;

	CdDcdZoneXy zoneDgrInDcd ;
	//CdDcdZoneXy zoneDgr = *m_pCDcdAllOperationTable2->getCdDcdZone();
	CdDcdZoneXy zoneDgr ;
	{
		//if ( m_pCDcdAllOperationTable2->getCentDedDgrDia() != NULL )
		//{
		//	zoneDgr = m_pCDcdAllOperationTable2->getCentDedDgrDia()->getZone();
		//}
		if (m_pCDcdAllOperationTable2->getCdDcdZone() != NULL)
		{
			zoneDgr = *m_pCDcdAllOperationTable2->getCdDcdZone();
		}

		zoneDgrInDcd = m_pCDcdAllOperationTable2->getZone_Dgr( &aTarget ) ;
	}
	//zoneDgr=ダイヤグラム座標の全体範囲
	//zoneDgrInDcd = IfDcdTargetに描画するダイヤグラム座標範囲

	CdDcdZoneXy	zoneDiagramZoneDcd = calcDiagramZoneDcd() ;
	//zoneDiagramZoneDcd = ウインドウ上でダイヤグラムが描画される領域

	// --------------------------------		
	//	ウインドウスクロール
	// --------------------------------	
	//※　現在のzoneDgrInDcd(IfDcdTargetに描画するダイヤグラム座標範囲)の
	//	Pos(始点位置)と、
	//	前回(現在表示中)のzoneDgrInDcdのPos(始点位置)を比較し、
	//	その差をもとにウインドウのスクロールを行います。
	//※『前回(現在表示中)のzoneDgrInDcdのPos(始点位置)』は
	//	スクロールバーの位置から取得します。
	{

		// --------------------------------		
		//	X方向ウインドウスクロールピクセル数の計算
		// --------------------------------
		int iXAmount = 0 ;
		if ( m_CdScrollbarPropX.getPos() != 
			zoneDgrInDcd.getX().getPos() )
		{
			int iXPos_DcdPrev = m_pCDcdAllOperationTable2->XDgrToDcd( 
				&aTarget , m_CdScrollbarPropX.getPos() ) ;  
			int iXPos_DcdNew  = m_pCDcdAllOperationTable2->XDgrToDcd( 
				&aTarget , zoneDgrInDcd.getX().getPos() ) ;  
			iXAmount = iXPos_DcdPrev - iXPos_DcdNew ;
		}
		// --------------------------------		
		//	Y方向ウインドウスクロールピクセル数の計算
		// --------------------------------
		int iYAmount = 0 ;
		if ( m_CdScrollbarPropY.getPos() != 
			zoneDgrInDcd.getY().getPos() )
		{
			int iYPos_DcdPrev = m_pCDcdAllOperationTable2->YDgrToDcd( 
				&aTarget , m_CdScrollbarPropY.getPos() ) ;
			//int iYPos_DcdPrev = m_CdScrollbarPropY.getPos() * m_pCDcdAllOperationTable2->getDcdPerDgrY() +
			//	aTarget.getZone().getY().getPos();
			int iYPos_DcdNew  = m_pCDcdAllOperationTable2->YDgrToDcd( 
				&aTarget , zoneDgrInDcd.getY().getPos() ) ;
			//int iYPos_DcdNew = zoneDgrInDcd.getY().getPos() * m_pCDcdAllOperationTable2->getDcdPerDgrY() +
			//	aTarget.getZone().getY().getPos();
			iYAmount = iYPos_DcdPrev - iYPos_DcdNew ;
		}

		// --------------------------------		
		//	スクロール
		// --------------------------------
		if ( iXAmount != 0 || iYAmount != 0 )
		{
			CConverter_WinGdi	aConverter_WinGdi ;
			//	ダイヤグラム領域のスクロール
			{
				CdDcdZoneXy	zoneDcdDiagram = 
					m_pCDcdAllOperationTable2->calcDiagramZoneDcd( &aTarget ) ; 
				RECT	aRect = aConverter_WinGdi.RECTOf( zoneDcdDiagram );
				ScrollWindow( iXAmount , iYAmount , NULL , &aRect ) ;
			}
			//	駅名領域の縦スクロール
			{
				CdDcdZoneXy	zoneDcdOperationLeft =
					m_pCDcdAllOperationTable2->calcOperationLeftZoneDcd( &aTarget ) ; 
				RECT	aRect = aConverter_WinGdi.RECTOf(zoneDcdOperationLeft);
				ScrollWindow( 0 , iYAmount , NULL , &aRect ) ;
			}
			//	時刻領域の横スクロール
			{
				CdDcdZoneXy	zoneDcdJikoku = 
					m_pCDcdAllOperationTable2->calcJikokuZoneDcd( &aTarget ) ; 
				RECT	aRect = aConverter_WinGdi.RECTOf( zoneDcdJikoku );
				ScrollWindow( iXAmount , 0 , NULL , &aRect ) ;
			}
			//	駅名領域の縦スクロール
			{
				CdDcdZoneXy	zoneDcdOperationRight =
					m_pCDcdAllOperationTable2->calcOperationRightZoneDcd(&aTarget);
				RECT	aRect = aConverter_WinGdi.RECTOf(zoneDcdOperationRight);
				ScrollWindow(0, iYAmount, NULL, &aRect);
			}
		}
	}


	// --------------------------------		
	//	スクロールバー属性の変更
	// --------------------------------	
	{
		// --------------------------------		
		//	X方向のスクロールバー属性の変更
		// --------------------------------	
		CdScrollbarProp	aCdScrollbarPropX_New 
			= m_CdScrollbarPropX  ;
		if ( zoneDiagramZoneDcd.getX().getSize() > 0 )	
		{
			//	ダイヤグラム表示領域がウインドウ内
			aCdScrollbarPropX_New.setDisableNoScroll( false ) ;
			aCdScrollbarPropX_New.set(
					zoneDgr.getX().getPos() , 
					zoneDgr.getX().getEndPos() ,
					zoneDgrInDcd.getX().getSize() + 1 ,
					zoneDgrInDcd.getX().getPos() ) ;
		}
		else
		{
			//	ダイヤグラム表示領域がウインドウ上にない場合は
			//	スクロールバーは非表示にはせずに無効にします。
			//
			//【理由】スクロールバーが点滅する状態を避けるためです。
			//【memo】ダイヤグラムビューで、スクロールバーが点滅する現象
			//	以下の動作が原因です。
			//(1)　クライアント領域のサイズが小さい
			//　→ダイヤグラム表示領域が、クライアント領域内にない
			//　→スクロールバーは非表示
			//(2)　ユーザーがクライアント領域のサイズを、ダイヤグラム
			//	表示領域が少し表示されるくらいに大きくする
			//　→ダイヤグラム表示領域がクライアント領域になる
			//　→スクロールバーが表示される
			//(3)スクロールバーが表示されたことにより、CWndAllOperationTable2の
			//	クライアント領域が小さくなる。
			//　→ダイヤグラム表示領域が、クライアント領域外になる
			//	(スクロールバーに隠れる)
			//　→スクロールバーが非表示になる
			//(4)スクロールバーが非表示になったことにより、CWndAllOperationTable2の
			//	クライアント領域が大きくなる
			//　→ダイヤグラム表示領域がクライアント領域になる
			//　→スクロールバーが表示される
			//(5)　(3)～(4)の繰り返しで、スクロールバーが点滅したようになる。
			//
			//  これを避けるために、以下のようにします。
			//
			//  CWndAllOperationTable2 は、ダイヤグラム表示領域が
			//	クライアント領域内にないときは、スクロールバーは
			//	表示したままで無効にする。
			aCdScrollbarPropX_New.setDisableNoScroll( true ) ;
			aCdScrollbarPropX_New.setNull() ;

		}
		if ( !m_CdScrollbarPropX.isEqualTo( aCdScrollbarPropX_New ) )
		{
			m_CdScrollbarPropX = aCdScrollbarPropX_New ;
			SCROLLINFO	aScrollinfo = 
				CconvWinUser::SCROLLINFOof( m_CdScrollbarPropX ) ;

			//	SIF_DISABLENOSCROLL を使ってスクロールバーを無効にする場合は、
			//
			//	EnableScrollBar( (SB_HORZ or SB_VERT), ESB_ENABLE_BOTH ) ;
			//
			//	を呼び出してから、
			//
			//	SetScrollInfo()を呼び出してください。
			//	
			//	EnableScrollBar() を呼び出さないと、
			//	無効になったスクロールバーは
			//	スクロールバーが必要になったときにも有効になりません。
			EnableScrollBar( SB_HORZ ,  ESB_ENABLE_BOTH ) ;
			SetScrollInfo( SB_HORZ , &aScrollinfo ) ;
		}

		// --------------------------------		
		//	Y方向のスクロールバー属性の変更
		// --------------------------------	
		CdScrollbarProp	aCdScrollbarPropY_New 
			= m_CdScrollbarPropY  ;
		if ( zoneDiagramZoneDcd.getY().getSize() > 0 )	
		{
			//	ダイヤグラム表示領域がウインドウ内
			aCdScrollbarPropY_New.setDisableNoScroll( false ) ;
			aCdScrollbarPropY_New.set(
					zoneDgr.getY().getPos() , 
					zoneDgr.getY().getEndPos() ,
					zoneDgrInDcd.getY().getSize() + 1 , 
					zoneDgrInDcd.getY().getPos() ) ;
		}
		else
		{
			//	ダイヤグラム表示領域がウインドウ上にない場合は
			//	スクロールバーは非表示にはせずに無効にします。
			//
			//【理由】スクロールバーが点滅する状態を避けるためです。
			aCdScrollbarPropY_New.setDisableNoScroll( true ) ;
			aCdScrollbarPropY_New.setNull() ;
		}
		if ( !m_CdScrollbarPropY.isEqualTo( aCdScrollbarPropY_New ) )
		{
			m_CdScrollbarPropY = aCdScrollbarPropY_New ;
			SCROLLINFO	aScrollinfo = 
				CconvWinUser::SCROLLINFOof( m_CdScrollbarPropY ) ;
			EnableScrollBar( SB_VERT ,  ESB_ENABLE_BOTH ) ;
			SetScrollInfo( SB_VERT , &aScrollinfo ) ;
		}
	}
}
	// --------------------------------
	//@name MFCメッセージハンドラの下請関数
	// --------------------------------
int CWndAllOperationTable2::OnLButtonDblClk_openJikokuhyouView( CPoint point) 
{
	int iRv = 0 ;


	CDcdTargetGetDC	aTarget( GetSafeHwnd() ) ;
	ERessyahoukou eRessyahoukou = Ressyahoukou_Kudari ;
	int iRessyaIdx = -1 ;
	//int iRessyasenIdx = -1 ;
	{
		int iResult =  m_pCDcdAllOperationTable2->calcCentDedRessyaOfPoint( 
			&aTarget , 
			CdDcdPosXy( point.x , point.y ) ,/* 2 , */
			&eRessyahoukou , 
			&iRessyaIdx /*, 
			&iRessyasenIdx*/ ) ;
		if ( iResult != 1 )
		{
			iRv = -1 ;	//	point が列車線上にありません。
		}
	}
	//eRessyahoukou = point を通る列車線の方向 
	//iRessyaIdx = point を通る列車の列車Index
	//iRessyasenIdx = point の位置の列車線Index

	const CentDedDia* pCentDedDia = NULL ;
	//int iEkiOrder = -1 ;
	if ( iRv >= 0 )
	{
		int iDiaIndex = -1 ;
		// --------------------------------
		//iEkiOrder = m_pCDcdAllOperationTable2->calcEkiOrderOfPoint( 
		//	&aTarget , eRessyahoukou , point.y ) ;

		//iEkiOrder = point の位置の直前の駅Order
		iDiaIndex = getCDiagramEditDoc()->
			getCDedRosenFileData()->getCentDedRosen()->getCentDedDiaCont()
				->findCentDedDiaByName( 
					m_pCDcdAllOperationTable2->getName()) ;
		if ( iDiaIndex < 0 )
		{
			iRv = -2 ;	//	ダイヤグラムビューに対応する 
						//	CentDedDia が見つかりません。
		}
		else
		{
			pCentDedDia = getCDiagramEditDoc()->
					getCDedRosenFileData()->getCentDedRosen()->getCentDedDiaCont()
					->getMuPtr()->get( iDiaIndex ) ; 
		}
	}
	//pCentDedDia = 路線ダイヤオブジェクト
	//iEkiOrder = 移動先の駅Order

	CJikokuhyouView* pCJikokuhyouView = NULL ;
	if ( iRv >= 0 )
	{
		CJikokuhyouDoc* pCJikokuhyouDoc = NULL ;
		pCJikokuhyouDoc = 
			getCDiagramEditApp()->openCJikokuhyouDoc( 
				pCentDedDia , eRessyahoukou ,false,
				&pCJikokuhyouView) ; 
		if ( pCJikokuhyouView == NULL )
		{
			iRv = -3 ;	//	時刻表ビューを開くのに失敗しました。
		}
		//pCJikokuhyouDoc = 時刻表ドキュメント
		//pCJikokuhyouView = 時刻表ビュー
	}

	if ( iRv >= 0 )
	{
		//attention
		//	この行は不要です（openCJikokuhyouDoc() でアクティブになる）し、
		//	あるとAssert()に失敗します。
		//
		//	CMainFrame* pCMainFrame = (CMainFrame*)AfxGetMainWnd() ;
		//	pCMainFrame->SetActiveView( pCJikokuhyouView ) ;
	
		pCJikokuhyouView->setFocusToRessyaIndex( iRessyaIdx , 0 ) ;
		iRv = 1 ;	//	時刻表ビューへ移動しました
	}

	return iRv ;
}

int CWndAllOperationTable2::OnLButtonDblClk_openOperationTableView(CPoint point)
{
	int iRv = 0;


	CDcdTargetGetDC	aTarget(GetSafeHwnd());
	int iOperationIndex = -1;
	tstring strOperationNumber;
	{
		iOperationIndex = m_pCDcdAllOperationTable2->calcOperationIndexOfPoint(
			&aTarget,
			point.y);
		if (iOperationIndex < 0 || iOperationIndex >= (int)getOperationNumber()->size())
		{
			iRv = -1;	//	point が列車線上にありません。
		}
		else
		{
			strOperationNumber = getOperationNumber()->at(iOperationIndex);
		}
	}

	const CentDedDia* pCentDedDia = NULL;
	if (iRv >= 0)
	{
		int iDiaIndex = -1;
		// --------------------------------
		iDiaIndex = getCDiagramEditDoc()->
			getCDedRosenFileData()->getCentDedRosen()->getCentDedDiaCont()
			->findCentDedDiaByName(
				m_pCDcdAllOperationTable2->getName());
		if (iDiaIndex < 0)
		{
			iRv = -2;	//	ダイヤグラムビューに対応する 
						//	CentDedDia が見つかりません。
		}
		else
		{
			pCentDedDia = getCDiagramEditDoc()->
				getCDedRosenFileData()->getCentDedRosen()->getCentDedDiaCont()
				->getMuPtr()->get(iDiaIndex);
		}
	}
	//pCentDedDia = 路線ダイヤオブジェクト

	COperationTableView* pCOperationTableView = NULL;
	if (iRv >= 0)
	{
		COperationTableDoc* pCOperationTableDoc = NULL;
		if (iRv >= 0)
		{
			pCOperationTableDoc =
				getCDiagramEditApp()->openCOperationTableDoc(
					pCentDedDia,
					strOperationNumber);
			//if (pCOperationTableView == NULL)
			//{
			//	iRv = -4;	//	運用表ビューのオープンに失敗しました
			//}
		}
		//pCOperationTableDoc = 運用表ドキュメント
		//pCOperationTableView = 運用表ビュー
	}

	return iRv;
}


	// ********************************
	//@name	CDcdDiagrem-関連
	// ********************************
vector<tstring>* CWndAllOperationTable2::getOperationNumber()
{
	return m_pCDcdAllOperationTable2->getOperationNumber() ;
}
CWndAllOperationTable2& CWndAllOperationTable2::setOperationNumber(vector<tstring>* value )
{
	if ( m_pCDcdAllOperationTable2->getOperationNumber() != value )
	{
		m_pCDcdAllOperationTable2->setOperationNumber( value ) ;

		update_adjustProp() ;
		update_updateScreen() ;
		//Invalidate();
	}	
	return *this ;
}
CdDcdZoneXy* CWndAllOperationTable2::getCdDcdZone()
{
	return m_pCDcdAllOperationTable2->getCdDcdZone();
}
CWndAllOperationTable2& CWndAllOperationTable2::setCdDcdZone(CdDcdZoneXy* value)
{
	if (m_pCDcdAllOperationTable2->getCdDcdZone() != value)
	{
		m_pCDcdAllOperationTable2->setCdDcdZone(value);

		update_adjustProp();
		update_updateScreen();
	}
	return *this;
}
tstring CWndAllOperationTable2::getName()
{
	return m_pCDcdAllOperationTable2->getName();
}
CWndAllOperationTable2& CWndAllOperationTable2::setName(tstring value)
{
	if (m_pCDcdAllOperationTable2->getName() != value)
	{
		m_pCDcdAllOperationTable2->setName(value);

		update_adjustProp();
		update_updateScreen();
	}
	return *this;
}
	// ********************************
	//@name CDcdDiagram-属性-CdDedDispProp にはないもの
	// ********************************
bool CWndAllOperationTable2::getDisplayEkimeiJikoku()const
{
	return m_pCDcdAllOperationTable2->getDisplayEkimeiJikoku();
}

int CWndAllOperationTable2::setDisplayEkimeiJikoku(bool value)
{
	int iRv = 0;
	if (value != m_pCDcdAllOperationTable2->getDisplayEkimeiJikoku()) {
		m_pCDcdAllOperationTable2->setDisplayEkimeiJikoku(value);
		update_adjustProp();
		update_updateScreen();
		Invalidate();

		//	.ini ファイルに保存
		getCDiagramEditApp()->writeCWndAllOperationTable2ViewProp(this);


		iRv = 1;
	}
	return (iRv);

}
bool CWndAllOperationTable2::getDisplayRessyabangou()const 
{
	return m_pCDcdAllOperationTable2->getDisplayRessyabangou() ;
}

int CWndAllOperationTable2::setDisplayRessyabangou( bool value ) 
{
	int iRv = 0 ;
	if ( value != m_pCDcdAllOperationTable2->getDisplayRessyabangou() ){
		m_pCDcdAllOperationTable2->setDisplayRessyabangou( value ) ;
		update_adjustProp() ;
		update_updateScreen() ;
		Invalidate() ;	

		//	.ini ファイルに保存
		getCDiagramEditApp()->writeCWndAllOperationTable2ViewProp( this ) ;


		iRv = 1 ;
	}
	return ( iRv ) ;
	
}
bool CWndAllOperationTable2::getDisplaySyubetsuRyakusyou()const
{
	return m_pCDcdAllOperationTable2->getDisplaySyubetsuRyakusyou();
}
int CWndAllOperationTable2::setDisplaySyubetsuRyakusyou(bool value)
{
	int iRv = 0;
	if (value != m_pCDcdAllOperationTable2->getDisplaySyubetsuRyakusyou()) {
		m_pCDcdAllOperationTable2->setDisplaySyubetsuRyakusyou(value);
		update_adjustProp();
		update_updateScreen();
		Invalidate();

		//	.ini ファイルに保存
		getCDiagramEditApp()->writeCWndAllOperationTable2ViewProp(this);

		iRv = 1;
	}
	return (iRv);
}
bool CWndAllOperationTable2::getDisplayRessyamei()const 
{
	return m_pCDcdAllOperationTable2->getDisplayRessyamei() ;
}
int CWndAllOperationTable2::setDisplayRessyamei( bool value ) 
{
	int iRv = 0 ;
	if ( value != m_pCDcdAllOperationTable2->getDisplayRessyamei() ){
		m_pCDcdAllOperationTable2->setDisplayRessyamei( value ) ;
		update_adjustProp() ;
		update_updateScreen() ;
		Invalidate() ;	

		//	.ini ファイルに保存
		getCDiagramEditApp()->writeCWndAllOperationTable2ViewProp( this ) ;

		iRv = 1 ;
	}
	return ( iRv ) ;
}
bool CWndAllOperationTable2::getDisplayJikokuMinute()const
{
	return m_pCDcdAllOperationTable2->getDisplayJikokuMinute();
}
int CWndAllOperationTable2::setDisplayJikokuMinute(bool value)
{
	int iRv = 0;
	if (value != m_pCDcdAllOperationTable2->getDisplayJikokuMinute()) {
		m_pCDcdAllOperationTable2->setDisplayJikokuMinute(value);
		update_adjustProp();
		update_updateScreen();
		Invalidate();

		//	.ini ファイルに保存
		getCDiagramEditApp()->writeCWndAllOperationTable2ViewProp(this);

		iRv = 1;
	}
	return (iRv);
}

CdDcdPosXy	CWndAllOperationTable2::getPosDgr()const 
{
	return m_pCDcdAllOperationTable2->getPosDgr() ;
}
int CWndAllOperationTable2::setPosDgr( CdDcdPosXy value )
{
	int iRv = 0 ;
	if ( value != m_pCDcdAllOperationTable2->getPosDgr() )
	{
		m_pCDcdAllOperationTable2->setPosDgr( value ) ;
		update_adjustProp() ;
		update_updateScreen() ;
		Invalidate() ;	

		//	.ini ファイルに保存
		getCDiagramEditApp()->writeCWndAllOperationTable2ViewProp( this ) ;
		

		iRv = 1 ;
	}
	return iRv ;
}
double CWndAllOperationTable2::getDcdPerDgrX()const 
{
	CDcdTargetGetDC	aTarget( GetSafeHwnd() ) ;
	return m_pCDcdAllOperationTable2->getDcdPerDgrX(&aTarget) ;
}
int CWndAllOperationTable2::setDcdPerDgrX( double value ) 
{
	int iRv = 0 ;
	CDcdTargetGetDC	aTarget( GetSafeHwnd() ) ;
	if ( value != m_pCDcdAllOperationTable2->getDcdPerDgrX(&aTarget) )
	{
		m_pCDcdAllOperationTable2->setDcdPerDgrX( &aTarget , value ) ;
		update_adjustProp() ;
		update_updateScreen() ;
		Invalidate() ;	

		//	.ini ファイルに保存
		getCDiagramEditApp()->writeCWndAllOperationTable2ViewProp( this ) ;
		

		iRv = 1 ;
	}
	return iRv ;
}

double CWndAllOperationTable2::getDcdPerDgrY()const 
{
	CDcdTargetGetDC	aTarget( GetSafeHwnd() ) ;
	return m_pCDcdAllOperationTable2->getDcdPerDgrY(&aTarget) ;
}

int CWndAllOperationTable2::setDcdPerDgrY( double value ) 
{
	int iRv = 0 ;
	CDcdTargetGetDC	aTarget( GetSafeHwnd() ) ;
	if ( value != m_pCDcdAllOperationTable2->getDcdPerDgrY(&aTarget) )
	{
		m_pCDcdAllOperationTable2->setDcdPerDgrY( &aTarget , value ) ;
		update_adjustProp() ;
		update_updateScreen() ;
		Invalidate() ;			

		iRv = 1 ;
	}
	return iRv ;
}



int	CWndAllOperationTable2::getVlineMode()const 
{
	return m_pCDcdAllOperationTable2->getVlineMode() ;
	
}
int CWndAllOperationTable2::setVlineMode( int value ) 
{
	int iRv = 0 ;
	if ( value != m_pCDcdAllOperationTable2->getVlineMode() ){
		m_pCDcdAllOperationTable2->setVlineMode( value ) ;
		update_adjustProp() ;
		update_updateScreen() ;
		Invalidate() ;	

		//	.ini ファイルに保存
		getCDiagramEditApp()->writeCWndAllOperationTable2ViewProp( this ) ;


		iRv = 1 ;
	}
	return ( iRv ) ;
	
}



int CWndAllOperationTable2::getVlineChoices( Mui<CDcdAllOperationTable::VLINE>* pContVLINE )
{
	return m_pCDcdAllOperationTable2->getVlineChoices( pContVLINE )  ;
}

bool CWndAllOperationTable2::getDisplayParentSyubetsu() const
{
	return m_pCDcdAllOperationTable2->getDisplayParentSyubetsu();
}

int CWndAllOperationTable2::setDisplayParentSyubetsu(bool value)
{
	int iRv = 0;
	if (value != m_pCDcdAllOperationTable2->getDisplayParentSyubetsu()) {
		m_pCDcdAllOperationTable2->setDisplayParentSyubetsu(value);
		update_adjustProp();
		update_updateScreen();
		Invalidate();

		//	.ini ファイルに保存
		getCDiagramEditApp()->writeCWndAllOperationTable2ViewProp(this);


		iRv = 1;
	}
	return (iRv);
}



	// ********************************
	//@name	CDcdDiagrem-操作
	// ********************************
int CWndAllOperationTable2::readCdDedDispProp( const CdDedDispProp& value ) 
{
	int iRv = 0 ;
	m_pCDcdAllOperationTable2->readCdDedDispProp( value ) ;
	update_adjustProp() ;
	update_updateScreen() ;
	Invalidate() ;
	return ( iRv ) ;
}

CdDcdZoneXy	CWndAllOperationTable2::getZone_Dgr()const 
{
	CDcdTargetGetDC	aTarget( GetSafeHwnd() ) ;
	return m_pCDcdAllOperationTable2->getZone_Dgr( &aTarget ) ;
}
CdDcdZoneXy	CWndAllOperationTable2::getZone_Dgr(const int iType)const
{
	CDcdTargetGetDC	aTarget(GetSafeHwnd());
	return m_pCDcdAllOperationTable2->getZone_Dgr(&aTarget, iType);
}
int CWndAllOperationTable2::setZone_Dgr( const CdDcdZoneXy& value ) 
{
	int iRv = 0 ;
	CDcdTargetGetDC	aTarget( GetSafeHwnd() ) ;
	if ( value != m_pCDcdAllOperationTable2->getZone_Dgr( &aTarget ) )
	{
		m_pCDcdAllOperationTable2->setZone_Dgr(  &aTarget , value ) ;
		update_adjustProp() ;
		update_updateScreen() ;
		Invalidate() ;	

		//	.ini ファイルに保存
		getCDiagramEditApp()->writeCWndAllOperationTable2ViewProp( this ) ;

		iRv = 1 ;
	}
	return ( iRv ) ;
}

bool CWndAllOperationTable2::getKeepZoneDgrOnSize()const
{
	return m_pCDcdAllOperationTable2->getKeepZoneDgrOnSize() ;
};
int CWndAllOperationTable2::setKeepZoneDgrOnSize( bool value )
{
	int iRv = 0 ;
	if ( value != m_pCDcdAllOperationTable2->getKeepZoneDgrOnSize() )
	{
		m_pCDcdAllOperationTable2->setKeepZoneDgrOnSize( value ) ;

		update_adjustProp() ;
		update_updateScreen() ;
		Invalidate() ;	

		//	.ini ファイルに保存
		getCDiagramEditApp()->writeCWndAllOperationTable2ViewProp( this ) ;

		iRv = 1 ;
	}
	return ( iRv ) ;
};

	// ********************************
	//@name	CDcdDiagrem2-属性
	// ********************************


	// ********************************
	//@name	CDcdDiagrem2-操作
	// ********************************
CdDcdZoneXy CWndAllOperationTable2::calcDiagramZoneDcd()const 
{
	CDcdTargetGetDC	aTarget( GetSafeHwnd() ) ;

	CdDcdZoneXy	zoneDiagramZoneDcd = 
		m_pCDcdAllOperationTable2->calcDiagramZoneDcd( &aTarget ) ;
	return zoneDiagramZoneDcd ;
}


	// ********************************
	//@name	CWndAllOperationTable2-属性
	// ********************************

	// ********************************
	//@name	CWndAllOperationTable2-包含
	// ********************************
CDcdAllOperationTable2* CWndAllOperationTable2::getCDcdAllOperationTable2()
{
	return m_pCDcdAllOperationTable2 ;
}

	// ********************************
	//@name	CWndAllOperationTable2-構築
	// ********************************
BOOL CWndAllOperationTable2::Create( const RECT& rect, CWnd* pParentWnd, UINT nID )
{
	return CreateEx( 0 
		, AfxRegisterWndClass( CS_DBLCLKS //| CS_HREDRAW | CS_VREDRAW 
			, LoadCursor( NULL , IDC_ARROW ) 
			, (HBRUSH)GetStockObject( WHITE_BRUSH ) 
			, NULL ) 
		, _T("CWndAllOperationTable2")	//	この文字列が表示されることはありません
		, WS_CHILD | WS_VSCROLL | WS_HSCROLL | WS_TABSTOP
		, rect
		, pParentWnd
		, nID
		, NULL ) ;
}

BOOL CWndAllOperationTable2::Create( CWnd* pParentWnd, UINT nID )
{
	return CreateEx( 0 
		, AfxRegisterWndClass( CS_DBLCLKS //| CS_HREDRAW | CS_VREDRAW 
			, LoadCursor( NULL , IDC_ARROW ) 
			, (HBRUSH)GetStockObject( WHITE_BRUSH ) 
			, NULL ) 
		, _T("CWndAllOperationTable2")	//	この文字列が表示されることはありません
		, WS_CHILD | WS_VSCROLL | WS_HSCROLL | WS_TABSTOP
		, CRect( 0 , 0 , 0 , 0 ) 
		, pParentWnd
		, nID
		, NULL ) ;
}
	// ********************************
	//@name	CWndAllOperationTable2-操作
	// ********************************

void CWndAllOperationTable2::onUpdateOperationNumberCont() 
{
	if ( !m_bReadCWndAllOperationTable2Default )
	{
		//	最初にダイヤグラムを表示するときには、
		//	.ini ファイルから、スクロール位置と
		//	罫線の設定を読み込み
		getCDiagramEditApp()->readCWndAllOperationTable2ViewProp( this ) ;

		m_bReadCWndAllOperationTable2Default = true ;
	}

	// --------------------------------		
	update_adjustProp() ;
	update_updateScreen() ;
	Invalidate() ;
}
	
// ----------------------------------------------------------------

int CWndAllOperationTable2::YPosNormalization(const int iYPos)
{
	int iRv = iYPos + m_pCDcdAllOperationTable2->DEFAULT_YSIZE_PER_ONEOPERATION() / 2;
	iRv = iRv - iRv % m_pCDcdAllOperationTable2->DEFAULT_YSIZE_PER_ONEOPERATION();
	return iRv;
}

CWndAllOperationTable2::CWndAllOperationTable2():
	m_pCDcdAllOperationTable2( NULL ) , 
	m_bReadCWndAllOperationTable2Default( false ) 
{
	m_CdScrollbarPropX.setAdjustPosByPage( true ) ;
	m_CdScrollbarPropY.setAdjustPosByPage( true ) ;
}

CWndAllOperationTable2::~CWndAllOperationTable2()
{
}


BEGIN_MESSAGE_MAP(CWndAllOperationTable2, CWnd)
	//{{AFX_MSG_MAP(CWndAllOperationTable2)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CWndAllOperationTable2 メッセージ ハンドラ

int CWndAllOperationTable2::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (super::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_pCDcdAllOperationTable2 = new CDcdAllOperationTable2() ;
	
	return 0;
}

void CWndAllOperationTable2::OnDestroy() 
{
	if ( m_pCDcdAllOperationTable2 != NULL ){
		delete m_pCDcdAllOperationTable2 ;
		m_pCDcdAllOperationTable2 = NULL ;
	}
	
	super::OnDestroy();
	
}

void CWndAllOperationTable2::OnPaint() 
{
	CPaintDC dc(this); // 描画用のデバイス コンテキスト
	CDcdTargetOnPaint	aTarget( GetSafeHwnd() , &dc.m_ps ) ;
	if ( m_pCDcdAllOperationTable2 != NULL ){
		m_pCDcdAllOperationTable2->DcDraw( &aTarget ) ;
	}
}

void CWndAllOperationTable2::OnSize(UINT nType, int cx, int cy) 
{
	LogMsg(_T("CWndAllOperationTable2::OnSize(%d,%d,%d)") , nType , cx , cy ) ;

	CDcdTargetGetDC	aTarget( GetSafeHwnd() ) ;

	//memo: CWndAllOperationTable2::OnSize()では、SIZE_RESTORED以外は発生しない
	//このウインドウでは、 
	//SIZE_RESTORED以外(SIZE_MAXIMIZED,SIZE_MINIMIZEDなど)
	//は発生しません。
	//【理由】
	//このウインドウは子ウインドウです。位置やサイズは、
	//親ウインドウであるCDcdDiagramViewによって
	//制御されています。
	//親ウインドウは、この子ウインドウに対して
	//最小化・最大化を行いません。

	if ( ( nType == SIZE_MAXIMIZED      //	ウィンドウは最大表示されています
	    || nType == SIZE_RESTORED )     //	ウィンドウはサイズ変更されて
	    								//	いますが、
		                                //	サイズ変更の種類は SIZE_MINIMIZED 
		                                //	でも SIZE_MAXIMIZED 
										//	でもありません。
		&& cx > 0 && cy > 0 )
	{
		//	ウインドウがサイズ1以上で表示されている場合。
		//	(ウインドウが最小化の場合・
		//	またはサイズが0になった場合は、処理を行いません。)

		CdDcdSizeXy	sizeClientSize ; 

		////memo: CWndAllOperationTable2::OnSize()での IsWindowVisible() の効果。
		////	「表示されている」の判定に、このコードは
		////	効果がありません(例：初回表示・ウインドウの最大化など)
		//if ( !IsWindowVisible() )
		//{
		//	LogMsg( "\tNOT_VISIBLE" ) ;
		//}
		//else 

		{

			CdDcdZoneXy	zoneZone_Dgr = getZone_Dgr() ;

			LogMsg(_T("CWndAllOperationTable2::OnSize(%d,%d)") , cx , cy ) ;
			CdDcdZoneXy	zoneDiagramZoneDcd 
				= getCDcdAllOperationTable2()->calcDiagramZoneDcd( &aTarget ) ;
			if ( zoneDiagramZoneDcd.getX().getSize() > 0 &&
				zoneDiagramZoneDcd.getY().getSize() > 0 )
			{
				sizeClientSize.setX( cx ).setY( cy ) ;
			}
			else
			{
				LogMsg(_T("\tsizeClientSize NOT AVAILABLE") ) ;
			}
		}
		//sizeClientSize = クライアント領域サイズ。
		//	ただし、ダイヤグラムビュー領域のサイズの 
		//	x,y のいずれかがが	0なら、無効を示す0です。
		//【理由】ダイヤグラムビュー領域のサイズが0の場合は、
		//	getZone_Dgr() が正しく動作しないためです。

		{
			update_adjustProp() ;

			//スクロールバーの動作範囲を、新しいウインドウサイズに合わせます。
			update_updateScreen() ;

			//memo: CWndAllOperationTable2::OnSize() での、Invalidate()の必要性
			//	ウインドウサイズ変更時に、
			//	表示の大きさ(ダイヤグラム座標1あたりのDcDraw座標)を
			//	変更しないのなら、
			//	Invalidate() ( ウインドウの全面再描画 )は必要ありません。
		}

	}
	// --------------------------------
	super::OnSize(nType, cx, cy);

	LogMsg(_T("CWndAllOperationTable2::OnSize()=") ) ;
}

void CWndAllOperationTable2::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CDcdTargetGetDC	aTarget( GetSafeHwnd() ) ;

	CdDcdZoneXy	zoneDiagramZoneDcd = m_pCDcdAllOperationTable2->calcDiagramZoneDcd( &aTarget ) ;
	//zoneDiagramZoneDcd = ウインドウ上で、ダイヤグラムが表示される領域

	//	X方向では、ダイヤグラム部分はダイヤグラムビューに表示されません。
	if ( zoneDiagramZoneDcd.getX().getSize() <= 0 )
	{
		return ;
	}

	if ( pScrollBar == NULL )
	{
		//CdDcdZone	zoneCentDedDgrDia = m_pCDcdAllOperationTable2->getCentDedDgrDia()->getZone().getX()  ;
		CdDcdZone	zoneCentDedDgrDia = m_pCDcdAllOperationTable2->getCdDcdZone()->getX();
		CdDcdZone	zoneCDcdDiagram = m_pCDcdAllOperationTable2->getZone_Dgr( &aTarget ).getX() ;
		CdDcdZone	zoneCDcdDiagramPrev = zoneCDcdDiagram ;


		switch( nSBCode ){
		 case SB_LEFT :	//   左端へスクロール。
			{
				zoneCDcdDiagram.setPos( zoneCentDedDgrDia.getPos() ) ;
			}
			break ;
		 case SB_RIGHT :	//   右端へスクロール。
			{
				zoneCDcdDiagram.setPos( zoneCentDedDgrDia.getEndPos() - 
					zoneCDcdDiagram.getSize() ) ;
			}
			break ;
		 case SB_LINELEFT :		//   左へスクロール。
			{
				zoneCDcdDiagram.setPos( zoneCDcdDiagram.getPos() - 
					m_pCDcdAllOperationTable2->getVlinePitch() ) ;
			}
			break ;
		 case SB_LINERIGHT :	//   右へスクロール。
			{
				zoneCDcdDiagram.setPos( zoneCDcdDiagram.getPos() + 
					m_pCDcdAllOperationTable2->getVlinePitch() ) ;
			}
			break ;
		 case SB_PAGELEFT :	// 1 ページ左へスクロール。
			{
				zoneCDcdDiagram.setPos( zoneCDcdDiagram.getPos() - 
					zoneCDcdDiagram.getSize() ) ;
			}
			break ;
		 case SB_PAGERIGHT :	//   1 ページ右へスクロール。
			{
				zoneCDcdDiagram.setPos( zoneCDcdDiagram.getPos() + 
					zoneCDcdDiagram.getSize() ) ;
			}
			break ;
		 case SB_THUMBPOSITION :	//  絶対位置へスクロール。現在位置は引数 nPos で指定されます。
			{
				SCROLLINFO	aSCROLLINFO ;
				memset( &aSCROLLINFO , 0 , sizeof(aSCROLLINFO) ) ;
				aSCROLLINFO.cbSize = sizeof(aSCROLLINFO) ;			
				GetScrollInfo( SB_HORZ , &aSCROLLINFO , SIF_ALL ) ;
				int iPos = aSCROLLINFO.nPos ;
				zoneCDcdDiagram.setPos( iPos ) ;
			}
			break ;
		 case SB_THUMBTRACK :	//   スクロール ボックスを指定位置へドラッグします。現在位置は引数 nPos で指定されます
			{
				SCROLLINFO	aSCROLLINFO ;
				memset( &aSCROLLINFO , 0 , sizeof(aSCROLLINFO) ) ;
				aSCROLLINFO.cbSize = sizeof(aSCROLLINFO) ;			
				GetScrollInfo( SB_HORZ , &aSCROLLINFO , SIF_ALL ) ;
				int iPos = aSCROLLINFO.nTrackPos ;
				zoneCDcdDiagram.setPos( iPos ) ;
			}
			break ;

		 case SB_ENDSCROLL :	//   スクロール終了。
			break ;
		}
		if ( zoneCDcdDiagramPrev != zoneCDcdDiagram )
		{
			//memo: CWndAllOperationTable2 スクロール時の setZone_Dgr()呼び出し
			//	update_updateScreen() によりウインドウがスクロールされ、
			//	スクロールで無効になる領域に対してだけ再描画ができるように
			//	なりました。
			//	これにより、Invalidate() を呼び出す必要はなくなりました。
			//	CWndAllOperationTable2::setZone_Dgr() は内部で Invalidate() 
			//	を呼び出すため、この呼び出しは避けることにしました。

			//setZone_Dgr( 
			//	CdDcdZoneXy( zoneCDcdDiagram , getZone_Dgr().getY() ) ) ;
			m_pCDcdAllOperationTable2->setZone_Dgr( &aTarget , 
				CdDcdZoneXy( zoneCDcdDiagram , getZone_Dgr().getY() ) ) ;

			update_adjustProp() ;
			update_updateScreen() ;
		}
		return ;
	}
	
	super::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CWndAllOperationTable2::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CDcdTargetGetDC	aTarget( GetSafeHwnd() ) ;

	CdDcdZoneXy	zoneDiagramZoneDcd = m_pCDcdAllOperationTable2->calcDiagramZoneDcd( &aTarget ) ;
	//zoneDiagramZoneDcd = ウインドウ上で、ダイヤグラムが表示される領域

	//	Y方向では、ダイヤグラム部分はダイヤグラムビューに表示されません。
	if ( zoneDiagramZoneDcd.getY().getSize() <= 0 )
	{
		return ;
	}

	if ( pScrollBar == NULL )
	{
		//CdDcdZone	zoneCentDedDgrDia = m_pCDcdAllOperationTable2->getCentDedDgrDia()->getZone().getY()  ;
		CdDcdZone	zoneCentDedDgrDia = m_pCDcdAllOperationTable2->getCdDcdZone()->getY();
		CdDcdZone	zoneCDcdDiagram = m_pCDcdAllOperationTable2->getZone_Dgr( &aTarget ).getY() ;
		CdDcdZone	zoneCDcdDiagramPrev = zoneCDcdDiagram ;


		switch( nSBCode ){
		 case SB_TOP :	// 一番上までスクロール。 
			{
				zoneCDcdDiagram.setPos( zoneCentDedDgrDia.getPos() ) ;
			}
			break ;
		 case SB_BOTTOM :	//  一番下までスクロール。
			{
				zoneCDcdDiagram.setPos( zoneCentDedDgrDia.getEndPos() - 
					zoneCDcdDiagram.getSize() ) ;
			}
			break ;
		 case SB_LINEUP :	//  1 行上へスクロール。
			{
				//zoneCDcdDiagram.setPos( zoneCDcdDiagram.getPos() - 
				//	m_pCDcdAllOperationTable2->DEFAULT_YSIZE_PER_ONEOPERATION() ) ;
				 int iPos = YPosNormalization(zoneCDcdDiagram.getPos() -
					 m_pCDcdAllOperationTable2->DEFAULT_YSIZE_PER_ONEOPERATION());
				 zoneCDcdDiagram.setPos(iPos);
			}
			break ;
		 case SB_LINEDOWN : // 1 行下へスクロール。
			{
				//zoneCDcdDiagram.setPos( zoneCDcdDiagram.getPos() + 
				//	m_pCDcdAllOperationTable2->DEFAULT_YSIZE_PER_ONEOPERATION() ) ;
				 int iPos = YPosNormalization(zoneCDcdDiagram.getPos() +
					 m_pCDcdAllOperationTable2->DEFAULT_YSIZE_PER_ONEOPERATION());
				 zoneCDcdDiagram.setPos(iPos);
			}
			break ;
		 case SB_PAGEUP :	//  1 ページ上へスクロール。
			{
				//zoneCDcdDiagram.setPos( zoneCDcdDiagram.getPos() - 
				//	zoneCDcdDiagram.getSize() ) ;
				int iPos = YPosNormalization(zoneCDcdDiagram.getPos() -
					zoneCDcdDiagram.getSize());
				zoneCDcdDiagram.setPos(iPos);
			}
			break ;
		 case SB_PAGEDOWN :	//  1 ページ下へスクロール。
			{
				//zoneCDcdDiagram.setPos( zoneCDcdDiagram.getPos() + 
				//	zoneCDcdDiagram.getSize() ) ;
				int iPos = YPosNormalization(zoneCDcdDiagram.getPos() +
					zoneCDcdDiagram.getSize());
				zoneCDcdDiagram.setPos(iPos);
			}
			break ;
		 case SB_THUMBPOSITION :	//  絶対位置へスクロール。現在位置は引数 nPos で指定されます。
			{
				SCROLLINFO	aSCROLLINFO ;
				memset( &aSCROLLINFO , 0 , sizeof(aSCROLLINFO) ) ;
				aSCROLLINFO.cbSize = sizeof(aSCROLLINFO) ;			
				GetScrollInfo( SB_VERT , &aSCROLLINFO , SIF_ALL ) ;
				//int iPos = aSCROLLINFO.nPos ;
				int iPos = YPosNormalization(aSCROLLINFO.nPos);
				zoneCDcdDiagram.setPos( iPos ) ;
			}
			break ;
		 case SB_THUMBTRACK :	//   スクロール ボックスを指定位置へドラッグします。現在位置は引数 nPos で指定されます
			{
				SCROLLINFO	aSCROLLINFO ;
				memset( &aSCROLLINFO , 0 , sizeof(aSCROLLINFO) ) ;
				aSCROLLINFO.cbSize = sizeof(aSCROLLINFO) ;			
				GetScrollInfo( SB_VERT , &aSCROLLINFO , SIF_ALL ) ;
				//int iPos = aSCROLLINFO.nTrackPos ;
				int iPos = YPosNormalization(aSCROLLINFO.nTrackPos);
				zoneCDcdDiagram.setPos( iPos ) ;
			}
			break ;

		 case SB_ENDSCROLL :	//   スクロール終了。
			break ;
		}
		if ( zoneCDcdDiagramPrev != zoneCDcdDiagram )
		{
			//memo: CWndAllOperationTable2 スクロール時の setZone_Dgr()呼び出し
			//	update_updateScreen() によりウインドウがスクロールされ、
			//	スクロールで無効になる領域に対してだけ再描画ができるように
			//	なりました。
			//	これにより、Invalidate() を呼び出す必要はなくなりました。
			//	CWndAllOperationTable2::setZone_Dgr() は内部で Invalidate() を
			//	呼び出すため、この呼び出しは避けることにしました。

			//setZone_Dgr( 
			//	 CdDcdZoneXy( getZone_Dgr().getX() , zoneCDcdDiagram ) ) ;
			m_pCDcdAllOperationTable2->setZone_Dgr( &aTarget , 
				CdDcdZoneXy( getZone_Dgr().getX() , zoneCDcdDiagram )  ) ;

			update_adjustProp() ;
			update_updateScreen() ;
		}
		return ;
	}
	
	
	super::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CWndAllOperationTable2::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	bool bRv = false ;
	CDcdTargetGetDC	aTarget( GetSafeHwnd() ) ;



	// --------------------------------
	//	水平方向のキーボードによるスクロール結果の
	//	表示範囲を計算
	// --------------------------------
	{
		//CdDcdZone	zoneCentDedDgrDia = m_pCDcdAllOperationTable2->getCentDedDgrDia()->getZone().getX()  ;
		//CdDcdZone	zoneCentDedDgrDia = m_pCDcdAllOperationTable2->getCdDcdZone()->getX();
		CdDcdZone	zoneCDcdDiagram = m_pCDcdAllOperationTable2->getZone_Dgr( &aTarget ).getX() ;
		CdDcdZone	zoneCDcdDiagramPrev = zoneCDcdDiagram ;
		//zoneCDcdDiagram=現在の表示範囲

		switch( nChar ){
		 case VK_LEFT :		//WM_HSCROLL SB_LINELEFT と等価です
			{
				zoneCDcdDiagram.setPos( zoneCDcdDiagram.getPos() - 
						m_pCDcdAllOperationTable2->getVlinePitch() ) ;
			}
			break ;
		 case VK_RIGHT :	//WM_HSCROLL SB_LINERIGHT と等価です
			{
				zoneCDcdDiagram.setPos( zoneCDcdDiagram.getPos() + 
						m_pCDcdAllOperationTable2->getVlinePitch() ) ;
			}
			break ;
		 case VK_HOME :	//WM_HSCROLL SB_PAGELEFT と等価です。
			{
				zoneCDcdDiagram.setPos( zoneCDcdDiagram.getPos() - 
						zoneCDcdDiagram.getSize() ) ;
			}
			break ;
		 case VK_END ://WM_HSCROLL SB_PAGERIGHT と等価です。
			{
				zoneCDcdDiagram.setPos( zoneCDcdDiagram.getPos() + 
						zoneCDcdDiagram.getSize() ) ;
			}
			break ;
		}
		//	表示範囲変更要求があれば、
		//	CDcdDiagram2に内容を反映し、
		//	ウインドウをスクロール
		if ( zoneCDcdDiagramPrev != zoneCDcdDiagram )
		{
			//memo: CWndAllOperationTable2 スクロール時の setZone_Dgr()呼び出し
			//	update_updateScreen() によりウインドウがスクロールされ、
			//	スクロールで無効になる領域に対してだけ再描画ができるように
			//	なりました。
			//	これにより、Invalidate() を呼び出す必要はなくなりました。
			//	CWndAllOperationTable2::setZone_Dgr() は内部で Invalidate() を
			//	呼び出すため、この呼び出しは避けることにしました。

			//setZone_Dgr(  
			//	CdDcdZoneXy( zoneCDcdDiagram , getZone_Dgr().getY() ) ) ;
			m_pCDcdAllOperationTable2->setZone_Dgr( &aTarget , 
				CdDcdZoneXy( zoneCDcdDiagram , getZone_Dgr().getY() ) ) ;

			update_adjustProp() ;
			update_updateScreen() ;

			bRv = true ;
		}
	}
	// --------------------------------
	//	垂直方向のキーボードによるスクロール量を計算
	// --------------------------------
	{
		//CdDcdZone	zoneCentDedDgrDia = m_pCDcdAllOperationTable2->getCentDedDgrDia()->getZone().getY()  ;
		//CdDcdZone	zoneCentDedDgrDia = m_pCDcdAllOperationTable2->getCdDcdZone()->getY();
		CdDcdZone	zoneCDcdDiagram = m_pCDcdAllOperationTable2->getZone_Dgr( &aTarget ).getY() ;
		CdDcdZone	zoneCDcdDiagramPrev = zoneCDcdDiagram ;
		//zoneCDcdDiagram=現在の表示範囲

		switch( nChar ){
		 case VK_UP :	//	WM_VSCROLL SB_LINEUP 
			{
				//zoneCDcdDiagram.setPos( zoneCDcdDiagram.getPos() - 
				//	m_pCDcdAllOperationTable2->DEFAULT_YSIZE_PER_ONEOPERATION() ) ;
				int iPos = YPosNormalization(zoneCDcdDiagram.getPos() -
					m_pCDcdAllOperationTable2->DEFAULT_YSIZE_PER_ONEOPERATION());
				zoneCDcdDiagram.setPos(iPos);
			}
			break ;
		 case VK_DOWN :	//	WM_VSCROLL SB_LINEDOWN
			{
				//zoneCDcdDiagram.setPos( zoneCDcdDiagram.getPos() + 
				//	m_pCDcdAllOperationTable2->DEFAULT_YSIZE_PER_ONEOPERATION() ) ;
				int iPos = YPosNormalization(zoneCDcdDiagram.getPos() +
					m_pCDcdAllOperationTable2->DEFAULT_YSIZE_PER_ONEOPERATION());
				zoneCDcdDiagram.setPos(iPos);
			}
			break ;
		 case VK_PRIOR ://	WM_VSCROLL SB_PAGEUP 
			{
				//zoneCDcdDiagram.setPos( zoneCDcdDiagram.getPos() - 
				//	zoneCDcdDiagram.getSize() ) ;
				int iPos = YPosNormalization(zoneCDcdDiagram.getPos() -
					zoneCDcdDiagram.getSize());
				zoneCDcdDiagram.setPos(iPos);
			}
			break ;
		 case VK_NEXT :	//	WM_VSCROLL SB_PAGEDOWN
			{
				//zoneCDcdDiagram.setPos( zoneCDcdDiagram.getPos() + 
				//	zoneCDcdDiagram.getSize() ) ;
				int iPos = YPosNormalization(zoneCDcdDiagram.getPos() +
					zoneCDcdDiagram.getSize());
				zoneCDcdDiagram.setPos(iPos);
			}
			break ;
		}
		//	表示範囲変更要求があれば、
		//	CDcdDiagram2に内容を反映し、
		//	ウインドウをスクロール
		if ( zoneCDcdDiagramPrev != zoneCDcdDiagram )
		{
			//memo: CWndAllOperationTable2 スクロール時の setZone_Dgr()呼び出し
			//	update_updateScreen() によりウインドウがスクロールされ、
			//	スクロールで無効になる領域に対してだけ再描画ができるように
			//	なりました。
			//	これにより、Invalidate() を呼び出す必要はなくなりました。
			//	CWndAllOperationTable2::setZone_Dgr() は内部で Invalidate() を
			//	呼び出すため、この呼び出しは避けることにしました。

			//setZone_Dgr(  
			//	CdDcdZoneXy( getZone_Dgr().getX() , zoneCDcdDiagram) ) ;
			m_pCDcdAllOperationTable2->setZone_Dgr( &aTarget , 
				CdDcdZoneXy( getZone_Dgr().getX() , zoneCDcdDiagram ) ) ;

			update_adjustProp() ;
			update_updateScreen() ;

			bRv = true ;
		}
	}
	//zoneCDcdDiagram=新しい表示範囲

	// --------------------------------
	if ( !bRv )
	{
		super::OnKeyDown(nChar, nRepCnt, nFlags);
	}
}

BOOL CWndAllOperationTable2::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	CDcdTargetGetDC	aTarget( GetSafeHwnd() ) ;
	if ( nFlags == 0 )
	{
		int iYMove = zDelta / (-WHEEL_DELTA) ;
		//iYMove = Y方向に移動する数。


		//CdDcdZone	zoneCentDedDgrDia =
		//	m_pCDcdAllOperationTable2->getCdDcdZone()->getY();
			//m_pCDcdAllOperationTable2->getCentDedDgrDia()->getZone().getY()  ;
		CdDcdZone	zoneCDcdDiagram = 
			m_pCDcdAllOperationTable2->getZone_Dgr( &aTarget ).getY() ;
		CdDcdZone	zoneCDcdDiagramPrev = zoneCDcdDiagram ;
		//zoneCDcdDiagram.setPos( zoneCDcdDiagram.getPos() + 
		//			m_pCDcdAllOperationTable2->DEFAULT_YSIZE_PER_ONEOPERATION() * iYMove ) ;
		int iPos = YPosNormalization(zoneCDcdDiagram.getPos() +
			m_pCDcdAllOperationTable2->DEFAULT_YSIZE_PER_ONEOPERATION() * iYMove);
		zoneCDcdDiagram.setPos(iPos);
		if ( zoneCDcdDiagramPrev != zoneCDcdDiagram )
		{
			//memo: CWndAllOperationTable2 スクロール時の setZone_Dgr()呼び出し
			//	update_updateScreen() によりウインドウがスクロールされ、
			//	スクロールで無効になる領域に対してだけ再描画ができるように
			//	なりました。
			//	これにより、Invalidate() を呼び出す必要はなくなりました。
			//	CWndAllOperationTable2::setZone_Dgr() は内部で Invalidate() を
			//	呼び出すため、
			//	この呼び出しは避けることにしました。
			
			//setZone_Dgr( 
			//	CdDcdZoneXy( getZone_Dgr().getX() , zoneCDcdDiagram ) ) ;
			m_pCDcdAllOperationTable2->setZone_Dgr( &aTarget , 
				CdDcdZoneXy( getZone_Dgr().getX() , zoneCDcdDiagram )  ) ;

			update_adjustProp() ;
			update_updateScreen() ;

			
		}


		return ( TRUE ) ;
	}	
	return super::OnMouseWheel(nFlags, zDelta, pt);
}

void CWndAllOperationTable2::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	int iRv = 0 ;
	CWaitCursor	aCursor ;

	//	時刻表ビューへの移動を試行
	{
		int iResult = OnLButtonDblClk_openJikokuhyouView( point ); 
		if ( iResult >= 1 )
		{
			iRv = 1 ;
		}
	}
	//	時刻表ビューが開けない場合は、
	//	運用表ビューのオープンを試行
	if ( iRv <= 0 )	
	{
		int iResult = OnLButtonDblClk_openOperationTableView( point ) ;
		if ( iResult >= 1 )
		{
			iRv = 1 ;
		}
		
	}
	//	どのビューも開けない場合は、
	//	デフォルト処理
	if ( iRv <= 0 )
	{
		CWnd::OnLButtonDblClk(nFlags, point);
	}
}

void CWndAllOperationTable2::OnContextMenu(CWnd* pWnd, CPoint point)
{
	//	ダイヤグラムビューのコンテキストメニューは、
	//	現在のところ表示しません。
	{
		super::OnContextMenu(pWnd, point);
	}
}
} //namespace ViewAllOperationTable2
