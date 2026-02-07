/*
OuDiaSecond Copyright (C) 2017-2025 diagram_mania

このプログラムは、take-okm氏が作成したOuDiaを改造したソフトウェアです。
このプログラム利用については、take-okm氏記載の下記文書に準拠します。
*/
#include "stdafx.h"

#include "..\DiagramEdit.h"
#include "COperationTableDoc.h"
#include "str/stringSplit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace ViewOperationTable {

	/////////////////////////////////////////////////////////////////////////////
	// COperationTableDoc

	IMPLEMENT_DYNCREATE(COperationTableDoc, CHidemdiSubDoc)

	void COperationTableDoc::SetTitle(LPCTSTR lpszTitle)
	{
		tstring	strTitle = lpszTitle;
		vector<tstring>	arstrTitle = splitc< vector< tstring > >('\n', lpszTitle);
		m_strDiaName = arstrTitle[0];
		m_strOperationNumber = arstrTitle[1];

		// --------------------------------
		//	タイトル文字列の作成
		// --------------------------------
		{
			CString	strDiamei = m_strDiaName.c_str();
			strDiamei += _T(" ");

			strDiamei += m_strOperationNumber.c_str();
			strDiamei += _T(" ");

			CString	aString;
			aString.LoadString(IDS_WORD_OPERATIONTABLE);
			strDiamei += (LPCTSTR)aString;

			super::SetTitle(strDiamei);
		}
	}

	COperationTableDoc::COperationTableDoc()
	{
	}

	BOOL COperationTableDoc::OnNewDocument()
	{
		if (!CHidemdiSubDoc::OnNewDocument())
			return FALSE;
		return TRUE;
	}

	COperationTableDoc::~COperationTableDoc()
	{
	}


	BEGIN_MESSAGE_MAP(COperationTableDoc, CHidemdiSubDoc)
		//{{AFX_MSG_MAP(COperationTableDoc)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//}}AFX_MSG_MAP
	END_MESSAGE_MAP()

	/////////////////////////////////////////////////////////////////////////////
	// COperationTableDoc 診断

#ifdef _DEBUG
	void COperationTableDoc::AssertValid() const
	{
		CHidemdiSubDoc::AssertValid();
	}

	void COperationTableDoc::Dump(CDumpContext& dc) const
	{
		CHidemdiSubDoc::Dump(dc);
	}
#endif //_DEBUG

	/////////////////////////////////////////////////////////////////////////////
	// COperationTableDoc シリアライズ

	void COperationTableDoc::Serialize(CArchive& ar)
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
	// COperationTableDoc コマンド

} //namespace ViewOperationTable
