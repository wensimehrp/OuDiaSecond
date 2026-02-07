/*
OuDiaSecond Copyright (C) 2017-2025 diagram_mania

このプログラムは、take-okm氏が作成したOuDiaを改造したソフトウェアです。
このプログラム利用については、take-okm氏記載の下記文書に準拠します。
*/

#if !defined(AFX_CINOUTLINKCODELISTDOC_H__ACB99EE5_73D3_441A_9DF7_0B68EAD629CE__INCLUDED_)
#define AFX_CINOUTLINKCODELISTDOC_H__ACB99EE5_73D3_441A_9DF7_0B68EAD629CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace ViewInOutLinkCodeList {

	/////////////////////////////////////////////////////////////////////////////
	// CInOutLinkCodeListDoc ドキュメント

	/**
	* @brief
	*	入出区連携コード一覧ビューのドキュメントクラスです。
	*
	*	このクラスには、特に処理はありません。
	*/
class CInOutLinkCodeListDoc : public CHidemdiSubDoc
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
		CInOutLinkCodeListDoc();           // 動的生成に使用されるプロテクト コンストラクタ。
		DECLARE_DYNCREATE(CInOutLinkCodeListDoc)

		// アトリビュート
	public:

		// オペレーション
	public:

		// オーバーライド
		// ClassWizard は仮想関数のオーバーライドを生成します。
		//{{AFX_VIRTUAL(CInOutLinkCodeListDoc)
	public:
		virtual void Serialize(CArchive& ar);   // ドキュメント I/O に対してオーバーライドされます。
	protected:
		virtual BOOL OnNewDocument();
		//}}AFX_VIRTUAL

		// インプリメンテーション
	public:
		virtual ~CInOutLinkCodeListDoc();
#ifdef _DEBUG
		virtual void AssertValid() const;
		virtual void Dump(CDumpContext& dc) const;
#endif

		// メッセージ マップ関数の生成
	protected:
		//{{AFX_MSG(CInOutLinkCodeListDoc)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//}}AFX_MSG
		DECLARE_MESSAGE_MAP()
	};


} //namespace ViewInOutLinkCodeList

#endif // !defined(AFX_CINOUTLINKCODELISTDOC_H__ACB99EE5_73D3_441A_9DF7_0B68EAD629CE__INCLUDED_)