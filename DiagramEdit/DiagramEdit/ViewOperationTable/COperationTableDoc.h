/*
OuDiaSecond Copyright (C) 2017-2026 diagram_mania

このプログラムは、take-okm氏が作成したOuDiaを改造したソフトウェアです。
このプログラム利用については、take-okm氏記載の下記文書に準拠します。
*/

#if !defined(AFX_COPERATIONTABLEDOC_H__4A1D02DA_40C6_42FC_80BE_9E08A08EF8D8__INCLUDED_)
#define AFX_COPERATIONTABLEDOC_H__4A1D02DA_40C6_42FC_80BE_9E08A08EF8D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace ViewOperationTable {

	/////////////////////////////////////////////////////////////////////////////
	// COperationTableDoc ドキュメント

	/**
	* @brief
	*	運用表ビューのドキュメントクラスです。
	*
	*	このクラスには、特に処理はありません。
	*/
class COperationTableDoc : public CHidemdiSubDoc
{

private:
	tstring	m_strDiaName;

	tstring	m_strOperationNumber;


public:
	tstring getDiaName()
	{
		return m_strDiaName;
	};

	tstring getOperationNumber()
	{
		return m_strOperationNumber;
	};

protected:
	virtual void SetTitle(LPCTSTR lpszTitle);

	protected:
		COperationTableDoc();           // 動的生成に使用されるプロテクト コンストラクタ。
		DECLARE_DYNCREATE(COperationTableDoc)

		// アトリビュート
	public:

		// オペレーション
	public:

		// オーバーライド
		// ClassWizard は仮想関数のオーバーライドを生成します。
		//{{AFX_VIRTUAL(CRessyasyubetsuDoc)
	public:
		virtual void Serialize(CArchive& ar);   // ドキュメント I/O に対してオーバーライドされます。
	protected:
		virtual BOOL OnNewDocument();
		//}}AFX_VIRTUAL

		// インプリメンテーション
	public:
		virtual ~COperationTableDoc();
#ifdef _DEBUG
		virtual void AssertValid() const;
		virtual void Dump(CDumpContext& dc) const;
#endif

		// メッセージ マップ関数の生成
	protected:
		//{{AFX_MSG(COperationTableDoc)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//}}AFX_MSG
		DECLARE_MESSAGE_MAP()
	};


} //namespace ViewOperationTable

#endif // !defined(AFX_COPERATIONTABLEDOC_H__4A1D02DA_40C6_42FC_80BE_9E08A08EF8D8__INCLUDED_)