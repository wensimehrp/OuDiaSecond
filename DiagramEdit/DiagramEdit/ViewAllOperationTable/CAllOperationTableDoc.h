/*
OuDiaSecond Copyright (C) 2017-2025 diagram_mania

このプログラムは、take-okm氏が作成したOuDiaを改造したソフトウェアです。
このプログラム利用については、take-okm氏記載の下記文書に準拠します。
*/

#if !defined(AFX_CALLOPERATIONTABLEDOC_H__E3CD4C29_76C1_427B_96D4_CE76B599EEBA__INCLUDED_)
#define AFX_CALLOPERATIONTABLEDOC_H__E3CD4C29_76C1_427B_96D4_CE76B599EEBA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace ViewAllOperationTable {

	/////////////////////////////////////////////////////////////////////////////
	// CAllOperationTableDoc ドキュメント

	/**
	* @brief
	*	運用表一覧ビューのドキュメントクラスです。
	*
	*	このクラスには、特に処理はありません。
	*/
class CAllOperationTableDoc : public CHidemdiSubDoc
{

private:
	tstring	m_strDiaName;

public:
	tstring getDiaName()
	{
		return m_strDiaName;
	};

protected:
	virtual void SetTitle(LPCTSTR lpszTitle);

	protected:
		CAllOperationTableDoc();           // 動的生成に使用されるプロテクト コンストラクタ。
		DECLARE_DYNCREATE(CAllOperationTableDoc)

		// アトリビュート
	public:

		// オペレーション
	public:

		// オーバーライド
		// ClassWizard は仮想関数のオーバーライドを生成します。
		//{{AFX_VIRTUAL(CAllOperationTableDoc)
	public:
		virtual void Serialize(CArchive& ar);   // ドキュメント I/O に対してオーバーライドされます。
	protected:
		virtual BOOL OnNewDocument();
		//}}AFX_VIRTUAL

		// インプリメンテーション
	public:
		virtual ‾CAllOperationTableDoc();
#ifdef _DEBUG
		virtual void AssertValid() const;
		virtual void Dump(CDumpContext& dc) const;
#endif

		// メッセージ マップ関数の生成
	protected:
		//{{AFX_MSG(CAllOperationTableDoc)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//}}AFX_MSG
		DECLARE_MESSAGE_MAP()
	};


} //namespace ViewAllOperationTable

#endif // !defined(AFX_CALLOPERATIONTABLEDOC_H__E3CD4C29_76C1_427B_96D4_CE76B599EEBA__INCLUDED_)