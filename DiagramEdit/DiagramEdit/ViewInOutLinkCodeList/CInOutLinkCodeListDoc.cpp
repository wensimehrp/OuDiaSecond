/*
OuDiaSecond Copyright (C) 2017-2025 diagram_mania

このプログラムは、take-okm氏が作成したOuDiaを改造したソフトウェアです。
このプログラム利用については、take-okm氏記載の下記文書に準拠します。
*/
#include "stdafx.h"

#include "..¥DiagramEdit.h"
#include "CInOutLinkCodeListDoc.h"
//#include "str/stringSplit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace ViewInOutLinkCodeList {

	/////////////////////////////////////////////////////////////////////////////
	// CInOutLinkCodeListDoc

	IMPLEMENT_DYNCREATE(CInOutLinkCodeListDoc, CHidemdiSubDoc)

	void CInOutLinkCodeListDoc::SetTitle(LPCTSTR lpszTitle)
	{
		m_strDiaName = lpszTitle;

		// --------------------------------
		//	タイトル文字列の作成
		// --------------------------------
		{
			CString	strDiamei = m_strDiaName.c_str();
			strDiamei += _T(" ");
			CString strInOutLinkCodeList;
			strInOutLinkCodeList.LoadString(IDS_WORD_INOUTLINKCODELIST);
			strDiamei += strInOutLinkCodeList;
			super::SetTitle(strDiamei);
		}
	}

	CInOutLinkCodeListDoc::CInOutLinkCodeListDoc()
	{
	}

	BOOL CInOutLinkCodeListDoc::OnNewDocument()
	{
		if (!CHidemdiSubDoc::OnNewDocument())
			return FALSE;
		return TRUE;
	}

	CInOutLinkCodeListDoc::‾CInOutLinkCodeListDoc()
	{
	}


	BEGIN_MESSAGE_MAP(CInOutLinkCodeListDoc, CHidemdiSubDoc)
		//{{AFX_MSG_MAP(CInOutLinkCodeListDoc)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//}}AFX_MSG_MAP
	END_MESSAGE_MAP()

	/////////////////////////////////////////////////////////////////////////////
	// CInOutLinkCodeListDoc 診断

#ifdef _DEBUG
	void CInOutLinkCodeListDoc::AssertValid() const
	{
		CHidemdiSubDoc::AssertValid();
	}

	void CInOutLinkCodeListDoc::Dump(CDumpContext& dc) const
	{
		CHidemdiSubDoc::Dump(dc);
	}
#endif //_DEBUG

	/////////////////////////////////////////////////////////////////////////////
	// CInOutLinkCodeListDoc シリアライズ

	void CInOutLinkCodeListDoc::Serialize(CArchive& ar)
	{
		if (ar.IsStoring())
		{
			// TODO: この位置に保存用のコードを追加してください
		}
		else
		{
			// TODO: この位置に読み込み用のコードを追加してください
		}
	}

	/////////////////////////////////////////////////////////////////////////////
	// CInOutLinkCodeListDoc コマンド

} //namespace ViewInOutLinkCodeList
