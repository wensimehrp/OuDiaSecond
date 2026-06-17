/*
OuDiaSecond Copyright (C) 2017-2026 diagram_mania

このプログラムは、take-okm氏が作成したOuDiaを改造したソフトウェアです。
このプログラム利用については、take-okm氏記載の下記文書に準拠します。
*/
#include "stdafx.h"

#include "..\DiagramEdit.h"
#include "CAllOperationTableDoc.h"
//#include "str/stringSplit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace ViewAllOperationTable {

	/////////////////////////////////////////////////////////////////////////////
	// CAllOperationTableDoc

	IMPLEMENT_DYNCREATE(CAllOperationTableDoc, CHidemdiSubDoc)

	void CAllOperationTableDoc::SetTitle(LPCTSTR lpszTitle)
	{
		m_strDiaName = lpszTitle;

		// --------------------------------
		//	タイトル文字列の作成
		// --------------------------------
		{
			CString	strDiamei = m_strDiaName.c_str();
			strDiamei += _T(" ");
			CString strAllOperationTable;
			strAllOperationTable.LoadString(IDS_WORD_ALLOPERATIONTABLE);
			strDiamei += strAllOperationTable;
			super::SetTitle(strDiamei);
		}
	}

	CAllOperationTableDoc::CAllOperationTableDoc()
	{
	}

	BOOL CAllOperationTableDoc::OnNewDocument()
	{
		if (!CHidemdiSubDoc::OnNewDocument())
			return FALSE;
		return TRUE;
	}

	CAllOperationTableDoc::~CAllOperationTableDoc()
	{
	}


	BEGIN_MESSAGE_MAP(CAllOperationTableDoc, CHidemdiSubDoc)
		//{{AFX_MSG_MAP(CAllOperationTableDoc)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//}}AFX_MSG_MAP
	END_MESSAGE_MAP()

	/////////////////////////////////////////////////////////////////////////////
	// CAllOperationTableDoc 診断

#ifdef _DEBUG
	void CAllOperationTableDoc::AssertValid() const
	{
		CHidemdiSubDoc::AssertValid();
	}

	void CAllOperationTableDoc::Dump(CDumpContext& dc) const
	{
		CHidemdiSubDoc::Dump(dc);
	}
#endif //_DEBUG

	/////////////////////////////////////////////////////////////////////////////
	// CAllOperationTableDoc シリアライズ

	void CAllOperationTableDoc::Serialize(CArchive& ar)
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
	// CAllOperationTableDoc コマンド

} //namespace ViewAllOperationTable
