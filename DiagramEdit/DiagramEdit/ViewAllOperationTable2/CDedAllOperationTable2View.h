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
#if !defined(AFX_CDEDALLOPERATIONTABLE2VIEW_H__6A6702AD_CDFE_44B8_A0A7_5B837BCEFB81__INCLUDED_)
#define AFX_CDEDALLOPERATIONTABLE2VIEW_H__6A6702AD_CDFE_44B8_A0A7_5B837BCEFB81__INCLUDED_

// CDedAllOperationTable2View.h : ヘッダー ファイル
//	$Id: CDedAllOperationTable2View.h 
/** @file */

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NsOu/Ou.h"

#include "DiagramEdit.h"
//#include "..\entDgr\CentDedDgrDia.h"
#include "CWndAllOperationTable2.h"
#include "DedRosenFileData\EditCmd\CRfEditCmd_Ressya.h"

namespace ViewAllOperationTable2 {
	using namespace DedRosenFileData::EditCmd;
	using namespace entDed;

/////////////////////////////////////////////////////////////////////////////
// CDedAllOperationTable2View ビュー
/**
	@brief
	運用一覧図ビューです。
 */
class CDedAllOperationTable2View : public CView
{
public:
	/** 運用一覧での「並べ替え」のモードを表す列挙です。 */
	enum EOperationSort
	{
		EOperationSort_OperationNumber = 0,	///< 運用番号でのソート
		EOperationSort_OutEki,	///< 出区駅ソート
		EOperationSort_OutJikoku,	///< 出区時刻ソート
		EOperationSort_InEki,	///< 入区駅ソート
		EOperationSort_InJikoku,	///< 入区時刻ソート
	};

	// ********************************
	///@name 包含
	// ********************************
	///@{

private:

	/**
		運用番号を、m_eOperationSortとm_bCompareBottomに基づいて並び替えたものです
		この順番で運用一覧に表示します
	*/
	vector<tstring> m_strOperationNumber;


	/**
		運用の並び順です、運用一覧のプロパティで設定します。
	*/
	EOperationSort m_eOperationSort;

	/**
		運用番号を並び替えるときのルールです。運用一覧のプロパティで設定します。
	*/
	bool m_bCompareBottom;

	/**
		運用一覧図の範囲です。
		横方向は、起点時刻から始まる24時間
		縦方向は、DEFAULT_YSIZE_PER_ONEOPERATION()×運用数です。
	*/
	CdDcdZoneXy m_CdDcdZoneXy;

	/**
		運用一覧図を描画する子ウインドウ。
		OnCreate() で生成し、 OnDestroy() で破棄します。
		このオブジェクトの破棄の責務は this にあります。
		
	*/
	CWndAllOperationTable2* m_pCWndAllOperationTable2;
	///@}

private:
	// --------------------------------
	///@name 内部データ
	// --------------------------------
	///@{
	/**
		全更新が保留されていたら true 。

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
		印刷時に、１ページに印刷するダイヤグラムの範囲を、
		ダイヤグラムエンティティ座標で保持します。

		この値は、ユーザーがメニューコマンド
		[印刷][印刷プレビュー]を選択した時点で
		ビューに表示されているダイヤグラムの範囲になります。
	*/
	CdDcdSizeXy	m_sizePrintSize_Dgr ;
	CdDcdSizeXy	m_sizePrintSize_DgrLeft;
	CdDcdSizeXy	m_sizePrintSize_DgrCenter;
	CdDcdSizeXy	m_sizePrintSize_DgrRight;

	///@}
protected:
	// --------------------------------
	///@name 下請関数
	// --------------------------------
	///@{
	/**
	 @return
		対応するドキュメントオブジェクトを返します。
	 */
	CDedAllOperationTable2Doc*	GetDocument() {
		CView* pCView = this ;
		return (CDedAllOperationTable2Doc*)pCView->GetDocument() ;};
	
	/**
	 @return
		CentDedDia オブジェクトを返します。
	 */
	const CentDedDia*	getCentDedDia()
	{
		const CentDedRosen*	pCentDedRosen = 
			getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen() ;
		return pCentDedRosen->getCentDedDiaCont()->getMuPtr()->get(  
			pCentDedRosen->getCentDedDiaCont()->findCentDedDiaByName( 
				GetDocument()->getDiaName() 
			) 
		) ;
	};
	///@}
private:
	// --------------------------------
	///@name OnUpdate下請関数
	// --------------------------------
	///@{

	/**
		列車番号を数字の塊と数字以外の塊に分割します。
		CentDedRessya内にあるものと同様の動作です。
	*/
	void splitOperationNumber(
		const tstring strOperationNumberIn,
		vector<int>& iOperationNumber,
		vector<tstring>& strOperationNumberOut)const;

	/**
		二つの運用番号について、その並び順を調べます
		trueを返した場合は、strOperationNumber1が先、falseの場合は2が先を意味します。
	*/
	bool SortOperationNumber(
		const tstring strOperationNumber1,
		const tstring strOperationNumber2);

	/**
		二つの運用について、m_eOperationSortをもとに、その並び順を調べます
		trueを返した場合は、strOperationNumber1が先、falseの場合はstrOperationNumber2が先を意味します。
		strOperationNumber:比較対象となる運用番号です
		iEkiIndex:比較対象となるの出区駅・入区駅Indexです。予め求めておきます。
		iOuterIndex:比較対象となるの路線外始発・終着駅のIndexです。予め求めておきます。
			路線外発着でない場合はINT_MINが入ります。
		Jikoku:比較対象となるの出区駅発時刻・入区駅着時刻です。

		KitenJikoku:ダイヤグラムの起点時刻です。時刻順での比較に用います。
	*/
	bool SortOperation(
		const tstring strOperationNumber1,
		const int& iEkiIndex1,
		const int& iOuterIndex1,
		const CdDedJikoku& Jikoku1,
		const tstring strOperationNumber2,
		const int& iEkiIndex2,
		const int& iOuterIndex2,
		const CdDedJikoku& Jikoku2,
		const CdDedJikoku& KitenJikoku);

	void SortOperation();
	/**
		OnUpdate() の pHint が CHint_CentDedRessya オブジェクトで
		ない場合です。
	
		m_pCentDedDgrDia オブジェクトを完全に更新し、
		ウインドウ m_pCWndDiagram に反映させます。
	 */
	void OnUpdate_All() ;
	///@}
private:
	// --------------------------------
	///@name MFCコマンドハンドラ下請関数
	// --------------------------------
	///@{
	/** [表示]-[横軸方向縮小]
	@param bQueryEnable [in]
		- TRUE ;	コマンドが現在実行できるか否かの判定だけを行います。@n
					エラーメッセージの表示は行いません。
		- FALSE ;	コマンドを実行します。 @n
				エラーが発生した場合は、エラーメッセージボックスを表示します。
	@return
		-	0 :	成功
		-	-1 :	現在は実行できません。(エラーメッセージは表示しません)
		-	-2 ;	//	ダイヤグラムは表示されていません。
	*/
	int OnAllOperationTable2XDgrSizeInc_Process( BOOL bQueryEnable );
	/** [表示]-[横軸方向拡大]
	@return
		-	0 :	成功
		-	-1 :	現在は実行できません。(エラーメッセージは表示しません)
		-	-2 ;	//	ダイヤグラムは表示されていません。
	*/
	int OnAllOperationTable2XDgrSizeDec_Process( BOOL bQueryEnable );
	/** [表示]-[横軸方向リセット]
	@return
		-	0 :	成功
		-	-2 ;	//	ダイヤグラムは表示されていません。
	*/
	int OnAllOperationTable2XDgrSizeReset_Process( BOOL bQueryEnable );
	// --------------------------------
	/** [表示]-[目盛を細かくする]
	@return
		-	0 :	成功
		-	-1 ;	//	コマンドを無効
	*/
	int OnAllOperationTable2MemoriDown_Process( BOOL bQueryEnable );
	/** [表示]-[目盛を粗くする]
	@return
		-	0 :	成功
		-	-1 ;	//	コマンドを無効
	*/
	int OnAllOperationTable2MemoriUp_Process( BOOL bQueryEnable );
	// --------------------------------
	/** [表示]-[始発・終着駅名時刻の表示]
	@return
		0以上は成功、エラーなら負の数です。
		-	1 	(bQueryEnable==TRUEの場合)このメニューコマンドが有効です。
		-	0 	(bQueryEnable==TRUEの場合)このメニューコマンドが無効です。
	*/
	int OnAllOperationTable2EkimeiJikoku_Process(BOOL bQueryEnable);
	// --------------------------------
	/** [表示]-[列車番号の表示]
	@return
		0以上は成功、エラーなら負の数です。
		-	1 	(bQueryEnable==TRUEの場合)このメニューコマンドが有効です。
		-	0 	(bQueryEnable==TRUEの場合)このメニューコマンドが無効です。
	*/
	int OnAllOperationTable2Ressyabangou_Process( BOOL bQueryEnable );

	/** [表示]-[種別名の表示]
	@return
		0以上は成功、エラーなら負の数です。
		-	1 	(bQueryEnable==TRUEの場合)このメニューコマンドが有効です。
		-	0 	(bQueryEnable==TRUEの場合)このメニューコマンドが無効です。
	*/
	int OnUpdateAllOperationTable2SyubetsuRyakusyou_Process(BOOL bQueryEnable);

	/** [表示]-[列車名の表示]
	@return
		0以上は成功、エラーなら負の数です。
		-	1 	(bQueryEnable==TRUEの場合)このメニューコマンドが有効です。
		-	0 	(bQueryEnable==TRUEの場合)このメニューコマンドが無効です。
	*/
	int OnUpdateAllOperationTable2Ressyamei_Process( BOOL bQueryEnable );

	/** [表示]-[各列車の時刻表示]
	@return
		0以上は成功、エラーなら負の数です。
		-	1 	(bQueryEnable==TRUEの場合)このメニューコマンドが有効です。
		-	0 	(bQueryEnable==TRUEの場合)このメニューコマンドが無効です。
	*/
	int OnUpdateAllOperationTable2JikokuMinute_Process(BOOL bQueryEnable);

	/** [表示]-[親種別による表示を有効]
	@return
	0以上は成功、エラーなら負の数です。
	-	1 	(bQueryEnable==TRUEの場合)このメニューコマンドが有効です。
	-	0 	(bQueryEnable==TRUEの場合)このメニューコマンドが無効です。
	*/
	int OneDisplayParentSyubetsu_Process(BOOL bQueryEnable);
	// --------------------------------
	/** [表示]-[更新]
	@see OnAllOperationTable2XDgrSizeInc_Process  
	*/
	int OnViewUpdate_Process( BOOL bQueryEnable );
	// --------------------------------
	/** [表示]-[ダイヤグラムビューのプロパティ]
	@see OnAllOperationTable2XDgrSizeInc_Process  
	*/
	int OnAllOperationTable2ViewProp_Process( BOOL bQueryEnable );
	
	///@}
// ********************************
//	CDedAllOperationTable2View
// ********************************
public:
	// ********************************
	///@name CDedAllOperationTable2View-操作
	// ********************************
	///@{
	/**
		ダイヤグラムビューの表示位置を、
		指定の時刻、指定の駅Orderに移動させます。
	 @param aCdDedJikoku [in]
		時刻を指定してください。
		この関数は、ダイヤグラムビューの左端を、この時刻にします。
		NULL 時刻を指定した場合、ダイヤグラムビューのX方向の位置を
		変更しません。
	 @param iEkiIndex [in]
		『駅Index』を指定してください。
		この関数は、ダイヤグラムの上端・下端を、この『駅Index』にします。
		負の数を指定した場合、ダイヤグラムビューのY方向の位置を
		変更しません。
		ダイヤグラムの上端・下端のどちらをこの『駅Index』にするかは、
		bEkiOrderIsBottom で指定します。
	 @param bEkiIndexIsBottom [in]
		- false ;	//	この関数は iEkiIndex を、ダイヤグラムの上端にします。
		- true ;	//	この関数は iEkiIndex を、ダイヤグラムの下端にします。
	 */
	virtual int setZone_Dgr( 
		const CdDedJikoku& aCdDedJikoku ,
		int iOperationNumberIndex  ) ; 
	///@}


// ----------------------------------------------------------------
protected:
	CDedAllOperationTable2View();           // 動的生成に使用されるプロテクト コンストラクタ
	DECLARE_DYNCREATE(CDedAllOperationTable2View)

// アトリビュート
public:

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CDedAllOperationTable2View)
	public:
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual void OnDraw(CDC* pDC);      // このビューを描画するためにオーバーライドしました。
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	virtual ~CDedAllOperationTable2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:

private:
	// 生成されたメッセージ マップ関数

	//{{AFX_MSG(CDedAllOperationTable2View)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnAllOperationTable2ViewProp();
	afx_msg void OnAllOperationTable2XDgrSizeInc();
	afx_msg void OnUpdateAllOperationTable2XDgrSizeInc(CCmdUI* pCmdUI);
	afx_msg void OnAllOperationTable2XDgrSizeDec();
	afx_msg void OnUpdateAllOperationTable2XDgrSizeDec(CCmdUI* pCmdUI);
	afx_msg void OnAllOperationTable2XDgrSizeReset();
	afx_msg void OnUpdateAllOperationTable2XDgrSizeReset(CCmdUI* pCmdUI);
	afx_msg void OnAllOperationTable2MemoriDown();
	afx_msg void OnUpdateAllOperationTable2MemoriDown(CCmdUI* pCmdUI);
	afx_msg void OnAllOperationTable2MemoriUp();
	afx_msg void OnUpdateAllOperationTable2MemoriUp(CCmdUI* pCmdUI);
	afx_msg void OnAllOperationTable2EkimeiJikoku();
	afx_msg void OnUpdateAllOperationTable2EkimeiJikoku(CCmdUI* pCmdUI);
	afx_msg void OnAllOperationTable2Ressyabangou();
	afx_msg void OnUpdateAllOperationTable2Ressyabangou(CCmdUI* pCmdUI);
	afx_msg void OnAllOperationTable2SyubetsuRyakusyou();
	afx_msg void OnUpdateAllOperationTable2SyubetsuRyakusyou(CCmdUI* pCmdUI);
	afx_msg void OnAllOperationTable2Ressyamei();
	afx_msg void OnUpdateAllOperationTable2Ressyamei(CCmdUI* pCmdUI);
	afx_msg void OnAllOperationTable2JikokuMinute();
	afx_msg void OnUpdateAllOperationTable2JikokuMinute(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnViewUpdate();
	afx_msg void OnUpdateViewUpdate(CCmdUI* pCmdUI);
	afx_msg void OnDisplayParentSyubetsu();
	afx_msg void OnUpdateDisplayParentSyubetsu(CCmdUI* pCmdUI);
	afx_msg void OnFilePrint();
	afx_msg void OnFilePrintPreview();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

} //namespace ViewAllOperationTable2

#endif // !defined(AFX_CDEDALLOPERATIONTABLE2VIEW_H__6A6702AD_CDFE_44B8_A0A7_5B837BCEFB81__INCLUDED_)
