/*
OuDiaSecond Copyright (C) 2017-2025 diagram_mania

このプログラムは、take-okm氏が作成したOuDiaを改造したソフトウェアです。
このプログラム利用については、take-okm氏記載の下記文書に準拠します。
*/
#if !defined(AFX_CEKIJIKOKUHYOUVIEW_H__69F2D214_3000_4E10_97F0_8F68B467F234__INCLUDED_)
#define AFX_CEKIJIKOKUHYOUVIEW_H__69F2D214_3000_4E10_97F0_8F68B467F234__INCLUDED_

/** @file */
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CEkiJikokuhyouView.h : ヘッダー ファイル
//


#include "CWndDcdGridEkiJikokuhyou.h"

namespace ViewEkiJikokuhyou {

	/////////////////////////////////////////////////////////////////////////////
	// CEkiJikokuhyouView ビュー
	
	/**
	* @brief
	*	駅時刻表ビューの、View クラスです。
	*/
	class CEkiJikokuhyouView : public CView
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
		CWndDcdGridEkiJikokuhyou* m_pCWndDcdGrid;

		///@}


		// ----------------------------------------------------------------
	protected:
		CEkiJikokuhyouView();           // 動的生成に使用されるプロテクト コンストラクタ
		DECLARE_DYNCREATE(CEkiJikokuhyouView)

		// アトリビュート
	public:

		// オペレーション
	public:

		// オーバーライド
		// ClassWizard は仮想関数のオーバーライドを生成します。

		//{{AFX_VIRTUAL(CEkiJikokuhyouView)
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
		virtual ‾CEkiJikokuhyouView();
#ifdef _DEBUG
		virtual void AssertValid() const;
		virtual void Dump(CDumpContext& dc) const;
#endif

		// 生成されたメッセージ マップ関数
	protected:
		//{{AFX_MSG(CEkiJikokuhyouView)
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

} //namespace ViewEkiJikokuhyou

#endif // !defined(AFX_CEKIJIKOKUHYOUVIEW_H__69F2D214_3000_4E10_97F0_8F68B467F234__INCLUDED_)
