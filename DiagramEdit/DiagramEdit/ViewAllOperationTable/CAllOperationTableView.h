/*
OuDiaSecond Copyright (C) 2017-2026 diagram_mania

このプログラムは、take-okm氏が作成したOuDiaを改造したソフトウェアです。
このプログラム利用については、take-okm氏記載の下記文書に準拠します。
*/
#if !defined(AFX_CALLOPERATIONTABLEVIEW_H__F72A32C0_C536_4E1D_B544_0564CC6B9C21__INCLUDED_)
#define AFX_CALLOPERATIONTABLEVIEW_H__F72A32C0_C536_4E1D_B544_0564CC6B9C21__INCLUDED_
/** @file */
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CAllOperationTableView.h : ヘッダー ファイル
//


#include "CWndDcdGridAllOperationTable.h"

namespace ViewAllOperationTable {

	/////////////////////////////////////////////////////////////////////////////
	// CAllOperationTableView ビュー
	
	/**
	* @brief
	*	運用表ビューの、View クラスです。
	*/
	class CAllOperationTableView : public CView
	{
		// ********************************
		///@name 包含
		// ********************************
		///@{
	private:
		/**
		*	グリッドウインドウオブジェクト。
		*	OnCreate() で生成・OnDestroy() で破棄します。
		*/
		CWndDcdGridAllOperationTable* m_pCWndDcdGrid;

		///@}


		// ----------------------------------------------------------------
	protected:
		CAllOperationTableView();           // 動的生成に使用されるプロテクト コンストラクタ
		DECLARE_DYNCREATE(CAllOperationTableView)

		// アトリビュート
	public:

		// オペレーション
	public:

		// オーバーライド
		// ClassWizard は仮想関数のオーバーライドを生成します。

		//{{AFX_VIRTUAL(CAllOperationTableView)
	public:
		virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
		virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
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
		virtual ~CAllOperationTableView();
#ifdef _DEBUG
		virtual void AssertValid() const;
		virtual void Dump(CDumpContext& dc) const;
#endif

		// 生成されたメッセージ マップ関数
	protected:
		//{{AFX_MSG(CAllOperationTableView)
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnDestroy();
		afx_msg void OnSize(UINT nType, int cx, int cy);
		afx_msg void OnSetFocus(CWnd* pOldWnd);
		//}}AFX_MSG
		DECLARE_MESSAGE_MAP()
	};

	/////////////////////////////////////////////////////////////////////////////

	//{{AFX_INSERT_LOCATION}}
	// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

} //namespace ViewAllOperationTable

#endif // !defined(AFX_CALLOPERATIONTABLEVIEW_H__F72A32C0_C536_4E1D_B544_0564CC6B9C21__INCLUDED_)
