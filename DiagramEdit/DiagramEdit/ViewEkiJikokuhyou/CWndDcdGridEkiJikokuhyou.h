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
//	CWndDcdGridEkiJikokuhyou.h
//	$Id: CWndDcdGridEkiJikokuhyou.h $
// ****************************************************************
*/
/** @file */
#ifndef  CWndDcdGridEkiJikokuhyou_h
#define  CWndDcdGridEkiJikokuhyou_h

#include "DcdGrid/WndDcdGrid3/WndDcdGrid3.h"

//#include "..\entDed\CconvCentDed.h"
#include "EkiJikokuhyouColSpec\EkiJikokuhyouColSpec.h"
//#include "..\entDed\CdDedRessyaProperty.h"
#include "CEkiJikokuhyouDoc.h"

namespace ViewEkiJikokuhyou {

	using namespace EkiJikokuhyouColSpec ;
	using namespace DcDrawLib::DcdGrid::WndDcdGrid3 ;
// ****************************************************************
//	CWndDcdGridEkiJikokuhyou
// ****************************************************************

/**
	駅時刻表一マスに表示する内容です。
	iMinute:分
	iRessyaSyubetsu:列車種別Index
	iSyuuchakuEkiOrder:終着駅Order
		ただし、この値が-1の場合は、環状運転であることを意味します。
		また、この値が-2の場合は、行き先が環状線であることを意味します。
	iOuterShuchakuekiIndex:路線外終着の場合、路線外終着駅Index
	iRessyaTrackIndex:発車番線
	aRessyaProperty:列車プロパティ
	bIsShihatsu:当該列車がこの駅始発かどうか。運用モードによって条件が変わります。

	種別変更表示の場合
	iMinute:ここには"-1"が入ります。種別変更表示であることを意味します
	iRessyaSyubetsu:種別変更後の列車種別Index
	iSyuuchakuEkiOrder:"種別変更を行う"駅Order(元の列車基準)
	aRessyaProperty:種別変更後の列車プロパティ
	iOuterShuchakuekiIndexとiRessyaTrackIndex,bIsShihatsuは未使用です
*/

struct EkiJikokuhyouContent {
	int iMinute;
	int iRessyaSyubetsu;
	int iSyuuchakuEkiOrder;
	int iOuterShuchakuekiIndex;
	int iRessyaTrackIndex;
	CdDedRessyaProperty aRessyaProperty;
	bool bIsShihatsu;

	EkiJikokuhyouContent()
		: iMinute(0)
		, iRessyaSyubetsu(0)
		, iSyuuchakuEkiOrder(INT_MIN)
		, iOuterShuchakuekiIndex(INT_MIN)
		, iRessyaTrackIndex(0)
		, aRessyaProperty(CdDedRessyaProperty())
		, bIsShihatsu(false)
	{}
};

struct RessyaPropertyBuffer {
	int iSyuuchakuEkiOrder;
	int iOuterShuchakuekiIndex;
	bool bLoop;
	CdDedRessyaProperty aRessyaProperty;

	RessyaPropertyBuffer()
		:iSyuuchakuEkiOrder(INT_MIN)
		, iOuterShuchakuekiIndex(INT_MIN)
		, bLoop(false)
		, aRessyaProperty(CdDedRessyaProperty())
	{}
};
/**
@brief
 【概要】 CEkiJikokuhyouView で用いる、グリッドウインドウです。
 */
class CWndDcdGridEkiJikokuhyou : public CWndDcdGrid
{
public:
	// ********************************
	//	インナータイプ
	// ********************************
	typedef CWndDcdGrid super ;


private:
	// ********************************
	///@name	包含
	// ********************************
	///@{
	/**
	  親ウインドウへのキー入力を契機に ModalDialog を開く場合、
	 モーダルダイアログの特定のエディットコントロールに、
	 キー入力メッセージ（ WM_KEYDOWN , WM_KEYUP ）を転送します。
	
		このオブジェクトの破棄の責務は、クラスユーザー（『転送元ウインドウ』）
		にあります。
		このオブジェクトは、 this より長く生存しなくてはなりません。
		不要であれば NULL でもかまいません。
		コンストラクタで決まります。
	 */
	//CKeyinputSenderToModalDlg	m_CKeyinputSenderToModalDlg ;
	///@}

	// --------------------------------
	///@name 内部データ
	// --------------------------------
	///@{
	/**
	 通常は false 。
	このビューがアクティブでないときに 
	全更新（ OnUpdate_All() を呼び出す）が必要になってから、
	ビューがアクティブになるまでの間だけ true になります。

	 この変数が true のときは、
	ビューの更新を、次にビューがアクティブ化されるまで
	保留していることを示します。

	 ビューがアクティブでないときに OnUpdate_All() が
	要求されたら、この変数を true にし、
	OnUpdate_All() は実行しません。

	 この値が true のときに、ビューがアクティブ化されたら、
	OnUpdate_All() を実行します。
	 */
	bool m_bUpdate_All_Requested ;

	/**
	初期値はfalse、初回の OnUpdate() が終了したら true になります。
	*/
	bool m_bInitialUpdateComplete;
	///@}
	
protected:
	// --------------------------------
	///@name	下請関数
	// --------------------------------
	///@{


	/**
		全てのX列についての 『列番号-表示内容』の対応表を生成します。
		生成された CdXColSpecCont() から
		CdXColSpec オブジェクトを
		取得することにより、各列毎に必要な表示内容を取得することができます。
	@return 
		全てのX列についての 『列番号-表示内容』の対応表である
		 CdXColSpecCont オブジェクトを返します。
		
	@attention
	 	この関数を OnCreate() ・及びそれ以前に
	 	呼び出したときは、戻り値はNULL状態になります。
	 	呼び出し時期に注意してください。

	@attention
		この対応表は、 CentDedEkiCont に変更が発生
		したら無効になります。このため、CentDedEkiCont  に
		変更の可能性がある状況では、対応表を再作成する必要があります。	
	*/
	CdEkiJikokuhyouXColSpecCont createXColSpecCont();


	/**
		全てのY列についての 『列番号-表示内容』の対応表を生成します。
		生成された CdYColSpecCont() から
		CdYColSpec オブジェクトを
		取得することにより、各列毎に必要な表示内容を取得することができます。
	@return 
		全てのY列についての 『列番号-表示内容』の対応表である
		 CdYColSpecCont オブジェクトを返します。
		
	@attention
	 	この関数を OnCreate() ・及びそれ以前に
	 	呼び出したときは、戻り値はNULL状態になります。
	 	呼び出し時期に注意してください。

	@attention
		この対応表は、 CentDedEkiCont に変更が発生
		したら無効になります。このため、CentDedEkiCont  に
		変更の可能性がある状況では、対応表を再作成する必要があります。	
	*/
	CdEkiJikokuhyouYColSpecCont createYColSpecCont();

	/**
	@return 
		フォーカスセルの列の表示内容を返します。
	*/
	CdEkiJikokuhyouXColSpec getXColSpecOfFocus();

	/**
	@return 
		フォーカスセルの列の表示内容を返します。
	*/
	CdEkiJikokuhyouYColSpec getYColSpecOfFocus() ;
	
	///@}
	// --------------------------------
	///@name OnUpdate の下請関数
	// --------------------------------
	///@{
	/**
	@return
	駅時刻を表示形式に変換するオブジェクトを返します。
	@note static メンバ関数にすることができます。
	*/
	//const CdDedJikoku::CConv	getCdDedJikokuConv()const;

	/**
	 グリッドの 指定のY列に、
	『運用』の内容を設定します。
	設定を行ったセルは、更新領域とします。
	@param iYColumnNumber [in]
		Y列番号を指定してください。
	@param aCentDedRessya [in]
		『運用』オブジェクトを指定してください。
	*/
	void OnUpdate_setEkiJikokuhyouContent_To_Column(
		int iHour,
		const list<EkiJikokuhyouContent>& ListEkiJikokuhyouContent);

	void OnUpdate_setEmptyEkiJikokuhyouContent_To_Column(
		int iHour);
	


	/**
	 OnUpdate() の下請関数です。
	関連するドキュメントの内容を、このウインドウに完全に
	反映します。

	 OnUpdate() で pHint が NULL の際の動作です。

	 このとき、ウインドウの更新再描画も発生します。
	 */
	virtual void  OnUpdate_All() ;

	void OnCreate_Header();
	///@}
protected:
	// --------------------------------
	///@name メニューコマンドの下請関数
	// --------------------------------
	///@{

	//運用表へ移動
	//int OnAllOperationtableMovetoOperationTable_Process(BOOL bQueryEnable);

	//時刻表へ移動
	int OnEkiJikokuhyouMovetojikokuhyou_Process(BOOL bQueryEnable);

	//ダイヤグラムへ移動
	int OnEkiJikokuhyouMovetodiagram_Process(BOOL bQueryEnable);

	//駅時刻表CSVエクスポート
	int OnFileExportEkiJikokuhyouCsv_Process(BOOL bQueryEnable);

	//運用一覧CSVエクスポート
	//int OnFileExportAllOperationTableCsv_Process(BOOL bQueryEnable);
	///@}

public:
	// ********************************
	//	コンストラクタ
	// ********************************
	CWndDcdGridEkiJikokuhyou();
	virtual ~CWndDcdGridEkiJikokuhyou();

	// ********************************
	///@name	CDcdGrid
	// ********************************
	///@{
	///@}
protected:
	// ********************************
	///@name	CWndDcdGrid
	// ********************************
	///@{

	// --------------------------------
	///@name	イベント処理のための仮想関数
	// --------------------------------
	///@{
	///@}
 public:
	// ********************************
	///@name  CAllOperationTableView からの委譲
	// ********************************
	///@{
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	///@}
public:
	// ********************************
	///@name CWndDcdGridEkiJikokuhyou-操作
	// ********************************
	///@{
	///@}
	
protected:
	CEkiJikokuhyouDoc* GetDocument();

	const CentDedDia* getCentDedDia();

	const CentDedRessyaCont* getCentDedRessyaCont(
		ERessyahoukou eRessyahoukou);
	
private:

	map<int, list<EkiJikokuhyouContent>> m_contListEkiJikokuhyouContent;

	/**
		最も列車本数が多い時間の列車本数。
	*/
	int m_iMaxRessyaCount;

	int m_iFirstHour;

	int m_iHourCount;

	/**
	駅時刻の秒単位を表示するか否かの指定

	-true ; 運用表ビューで秒単位まで時刻を表示します。
	-false ; (default)
	*/
	//bool m_bDisplaySecondEkiJikoku;

	/**
	列車の表示を親種別で行うか否かの指定

	-true ; 列車の表示を親種別で表示します。
	-false ; (default)
	*/
	bool m_bDisplayParentSyubetsu;

	/**
	列車の発車番線を表示するか否かの指定

	-true ; 列車の発車番線を表示します。
	-false ; (default)
	*/
	bool m_bDisplayTrack;

	/**
		最後にユーザーが入力したCSVファイル名
	*/
	CString	m_strCsvFilename;


	/**
	秒単位処理方法の指定

	0:秒単位を切り捨てて表示します(デフォルト)
	1:30秒以上は切り上げ、それ未満は切り捨てて表示します。
	2:秒単位を切り上げて表示します
	*/
	int m_iSecondRound;


	/**
	当駅始発列車に●印を表示するか否かの指定

	-true ; 当駅始発列車に●印を表示します。
	-false ; (default)
	*/
	bool m_bDisplayIsShihatsu;

	/**
	種別変更を表示するか否かの指定

	-true ; 種別変更を表示します。
	-false ; (default)
	*/
	bool m_bDisplayClassChange;

	/**
		パターンダイヤプレビュー機能における、1サイクルの秒数。
		0の場合は機能が無効
	*/
	int m_iPatternDiagramPreviewCycleSecond;

	/**
		パターンダイヤプレビュー機能における、前後各方向へのコピー範囲。
	*/
	int m_iPatternDiagramPreviewRange;


protected:

	/** [表示]-[運用一覧ビューのプロパティ]
	@param bQueryEnable [in]
		- TRUE ;	コマンドが現在実行できるか否かの判定だけを行います。@n
					エラーメッセージの表示は行いません。
		- FALSE ;	コマンドを実行します。 @n
				 エラーが発生した場合は、エラーメッセージボックスを表示します。
	@return
		0以上は成功、エラーなら負の数です。
		-	1 ;	//	ダイアログボックスでの入力が適用されました。
		-	0 ;	//	ダイアログボックスでの入力がキャンセルされました。
	*/
	//int OnAllOperationTableProp_Process(BOOL bQueryEnable);

	/**[表示] - [秒単位の時刻を表示]
		@return
		0以上は成功、エラーなら負の数です。
		- 1 	(bQueryEnable == TRUEの場合)[秒単位の時刻を表示]が有効です。
		- 0 	(bQueryEnable == TRUEの場合)[秒単位の時刻を表示]が無効です。
		*/
		//int OnViewDisplaySecondEkijikoku_Process(BOOL bQueryEnable);


		/**
		[表示] - [親種別を有効にする]
		@return
		0以上は成功、エラーなら負の数です。
		- 1 	(bQueryEnable == TRUEの場合)[親種別による表示]が有効です。
		- 0 	(bQueryEnable == TRUEの場合)[親種別によるを表示]が無効です。
		*/
		int OnViewDisplayParentSyubetsu_Process(BOOL bQueryEnable);


		/**
		[表示] - [発車番線を表示する]
		@return
		0以上は成功、エラーなら負の数です。
		- 1 	(bQueryEnable == TRUEの場合)[発車番線を表示]が有効です。
		- 0 	(bQueryEnable == TRUEの場合)[発車番線を表示]が無効です。
		*/
		int OnViewDisplayTrack_Process(BOOL bQueryEnable);

		/**
		[表示] - [始発列車に印を表示する]
		@return
		0以上は成功、エラーなら負の数です。
		- 1 	(bQueryEnable == TRUEの場合)[発車番線を表示]が有効です。
		- 0 	(bQueryEnable == TRUEの場合)[発車番線を表示]が無効です。
		*/
		int OnViewDisplayIsShihatsu_Process(BOOL bQueryEnable);

		/**
		[表示] - [種別変更を表示する]
		@return
		0以上は成功、エラーなら負の数です。
		- 1 	(bQueryEnable == TRUEの場合)[種別変更を表示]が有効です。
		- 0 	(bQueryEnable == TRUEの場合)[種別変更を表示]が無効です。
		*/
		int OnViewDisplayClassChange_Process(BOOL bQueryEnable);

public:

		//bool getDisplaySecondEkiJikoku()const;
		/**
		@return
		- 1 ;	設定を変更して、ウインドウを再描画しました。
		- 0 ;	表示内容は変化しませんでした。
		*/
		//int setDisplaySecondEkiJikoku(bool value);

		bool getDisplayParentSyubetsu()const;
		/**
		@return
		- 1 ;	設定を変更して、ウインドウを再描画しました。
		- 0 ;	表示内容は変化しませんでした。
		*/
		int setDisplayParentSyubetsu(bool value);

		bool getDisplayTrack()const;
		/**
		@return
		- 1 ;	設定を変更して、ウインドウを再描画しました。
		- 0 ;	表示内容は変化しませんでした。
		*/
		int setDisplayTrack(bool value);

		bool getDisplayIsShihatsu()const;
		/**
		@return
		- 1 ;	設定を変更して、ウインドウを再描画しました。
		- 0 ;	表示内容は変化しませんでした。
		*/
		int setDisplayIsShihatsu(bool value);

		bool getDisplayClassChange()const;
		/**
		@return
		- 1 ;	設定を変更して、ウインドウを再描画しました。
		- 0 ;	表示内容は変化しませんでした。
		*/
		int setDisplayClassChange(bool value);



		CdPenProp  getCdPenPropBoldLine()const
		{
			return CdPenProp(2, CdColorProp(0, 0, 0), CdPenProp::SOLID);
		}

		CdPenProp getCdPenPropNarrowLine()const
		{
			return CdPenProp(1, CdColorProp(0, 0, 0), CdPenProp::SOLID);
		}

		CdPenProp getCdPenPropNullLine()const
		{
			return CdPenProp(1, CdColorProp(0, 0, 0), CdPenProp::NULLPEN);
		}




// ----------------------------------------------------------------
//	MFC
// ----------------------------------------------------------------
// アトリビュート
public:

// オペレーション
public:
	//{{AFX_VIRTUAL(CWndDcdGridEkiJikokuhyou)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CWndDcdGridEkiJikokuhyou)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//[編集]
	//afx_msg void OnAllOperationtableProp();
	//afx_msg void OnUpdateAllOperationtableProp(CCmdUI* pCmdUI);
	//afx_msg void OnViewDisplaySecondEkijikoku();
	//afx_msg void OnUpdateViewDisplaySecondEkijikoku(CCmdUI *pCmdUI);
	afx_msg void OnViewDisplayParentSyubetsu();
	afx_msg void OnUpdateViewDisplayParentSyubetsu(CCmdUI *pCmdUI);
	afx_msg void OnViewDisplayTrack();
	afx_msg void OnUpdateViewDisplayTrack(CCmdUI* pCmdUI);
	afx_msg void OnViewDisplayIsShihatsu();
	afx_msg void OnUpdateViewDisplayIsShihatsu(CCmdUI* pCmdUI);
	afx_msg void OnViewDisplayClassChange();
	afx_msg void OnUpdateViewDisplayClassChange(CCmdUI* pCmdUI);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:	
	afx_msg void OnEkiJikokuhyouMovetojikokuhyou();
	afx_msg void OnUpdateEkiJikokuhyouMovetojikokuhyou(CCmdUI *pCmdUI);
	afx_msg void OnEkiJikokuhyouMovetodiagram();
	afx_msg void OnUpdateEkiJikokuhyouMovetodiagram(CCmdUI *pCmdUI);
	afx_msg void OnFileExportEkiJikokuhyoucsv();
	//afx_msg void OnFileExportAllOperationtablecsv();
};

} //namespace ViewEkiJikokuhyou

#endif /*CWndDcdGridEkiJikokuhyou_h*/
