/*
OuDiaSecond Copyright (C) 2017-2025 diagram_mania

このプログラムは、take-okm氏が作成したOuDiaを改造したソフトウェアです。
このプログラム利用については、take-okm氏記載の下記文書に準拠します。
*/

#if !defined(AFX_CCROSSINGCHECKDOC_H__BFA0B371_62C9_4E2F_A2CC_67719D7E1842__INCLUDED_)
#define AFX_CCROSSINGCHECKDOC_H__BFA0B371_62C9_4E2F_A2CC_67719D7E1842__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace ViewCrossingCheck {

	/////////////////////////////////////////////////////////////////////////////
	// CCrossingCheckDoc ドキュメント

	/**
	* @brief
	*	交差支障チェックビューのドキュメントクラスです。
	*
	*	このクラスには、特に処理はありません。
	*/
class CCrossingCheckDoc : public CHidemdiSubDoc
{

private:
	tstring	m_strDiaName;

	int	m_iEkiID;

public:
	tstring getDiaName()
	{
		return m_strDiaName;
	};

	int getEkiID()
	{
		return m_iEkiID;
	};

protected:
	//ダイヤ名\n駅Index
	virtual void SetTitle(LPCTSTR lpszTitle);

	protected:
		CCrossingCheckDoc();           // 動的生成に使用されるプロテクト コンストラクタ。
		DECLARE_DYNCREATE(CCrossingCheckDoc)

		// アトリビュート
	public:

		// オペレーション
	public:

		// オーバーライド
		// ClassWizard は仮想関数のオーバーライドを生成します。
		//{{AFX_VIRTUAL(CCrossingCheckDoc)
	public:
		virtual void Serialize(CArchive& ar);   // ドキュメント I/O に対してオーバーライドされます。
	protected:
		virtual BOOL OnNewDocument();
		//}}AFX_VIRTUAL

		// インプリメンテーション
	public:
		virtual ~CCrossingCheckDoc();
#ifdef _DEBUG
		virtual void AssertValid() const;
		virtual void Dump(CDumpContext& dc) const;
#endif

		// メッセージ マップ関数の生成
	protected:
		//{{AFX_MSG(CCrossingCheckDoc)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//}}AFX_MSG
		DECLARE_MESSAGE_MAP()
	};


} //namespace ViewCrossingCheck

#endif // !defined(AFX_CCROSSINGCHECKDOC_H__BFA0B371_62C9_4E2F_A2CC_67719D7E1842__INCLUDED_)