/*
OuDiaSecond Copyright (C) 2017-2025 diagram_mania

このプログラムは、take-okm氏が作成したOuDiaを改造したソフトウェアです。
このプログラム利用については、take-okm氏記載の下記文書に準拠します。
*/

#if !defined(AFX_CEKIJIKOKUHYOUDOC_H__C1C2F04A_1254_4350_883A_7A236C003257__INCLUDED_)
#define AFX_CEKIJIKOKUHYOUDOC_H__C1C2F04A_1254_4350_883A_7A236C003257__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace ViewEkiJikokuhyou {

	/////////////////////////////////////////////////////////////////////////////
	// CEkiJikokuhyouDoc ドキュメント

	/**
	* @brief
	*	駅時刻表ビューのドキュメントクラスです。
	*
	*	このクラスには、特に処理はありません。
	*/
class CEkiJikokuhyouDoc : public CHidemdiSubDoc
{

private:
	tstring	m_strDiaName;

	ERessyahoukou m_eRessyahoukou;

	//int m_iEkiIndex;

	int	m_iEkiID;

public:
	tstring getDiaName()
	{
		return m_strDiaName;
	};

	ERessyahoukou getRessyahoukou()
	{
		return m_eRessyahoukou;
	};

	//int getEkiIndex()
	//{
	//	return m_iEkiIndex;
	//};

	int getEkiID()
	{
		return m_iEkiID;
	};

protected:
	//ダイヤ名¥n列車方向¥n駅Index
	virtual void SetTitle(LPCTSTR lpszTitle);

	protected:
		CEkiJikokuhyouDoc();           // 動的生成に使用されるプロテクト コンストラクタ。
		DECLARE_DYNCREATE(CEkiJikokuhyouDoc)

		// アトリビュート
	public:

		// オペレーション
	public:

		// オーバーライド
		// ClassWizard は仮想関数のオーバーライドを生成します。
		//{{AFX_VIRTUAL(CEkiJikokuhyouDoc)
	public:
		virtual void Serialize(CArchive& ar);   // ドキュメント I/O に対してオーバーライドされます。
	protected:
		virtual BOOL OnNewDocument();
		//}}AFX_VIRTUAL

		// インプリメンテーション
	public:
		virtual ‾CEkiJikokuhyouDoc();
#ifdef _DEBUG
		virtual void AssertValid() const;
		virtual void Dump(CDumpContext& dc) const;
#endif

		// メッセージ マップ関数の生成
	protected:
		//{{AFX_MSG(CEkiJikokuhyouDoc)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//}}AFX_MSG
		DECLARE_MESSAGE_MAP()
	};


} //namespace ViewEkiJikokuhyou

#endif // !defined(AFX_CEKIJIKOKUHYOUDOC_H__C1C2F04A_1254_4350_883A_7A236C003257__INCLUDED_)