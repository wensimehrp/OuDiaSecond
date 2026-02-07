/*
OuDiaSecond Copyright (C) 2017-2025 diagram_mania

このプログラムは、take-okm氏が作成したOuDiaを改造したソフトウェアです。
このプログラム利用については、take-okm氏記載の下記文書に準拠します。
*/
#include "stdafx.h"

#include "..\DiagramEdit.h"
#include "CCrossingCheckDoc.h"
//#include "str/stringSplit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace ViewCrossingCheck {

	/////////////////////////////////////////////////////////////////////////////
	// CCrossingCheckDoc

	IMPLEMENT_DYNCREATE(CCrossingCheckDoc, CHidemdiSubDoc)

	void CCrossingCheckDoc::SetTitle(LPCTSTR lpszTitle)
	{
		vector<tstring>	arstrTitle = splitc< vector< tstring > >('\n', lpszTitle);
		m_strDiaName = arstrTitle[0];
		m_iEkiID = _ttoi(arstrTitle[1].c_str());

		//平日ダイヤ ○○駅 交差支障チェック
		// --------------------------------
		//	タイトル文字列の作成
		// --------------------------------
		tstring	strTitle = m_strDiaName;
		strTitle += _T(" ");

		const CentDedRosen* pCentDedRosen =
			getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen();
		const CentDedEkiCont* pCentDedEkiCont = pCentDedRosen->getCentDedEkiCont();
		int iEkiIndex = pCentDedEkiCont->EkiIndexOfEkiID(m_iEkiID);

		strTitle += pCentDedRosen->getCentDedEkiCont()->get(iEkiIndex).getEkimei();

		CString	strEki;
		strEki.LoadString(IDS_WORD_EKI);
		strTitle += strEki;

		strTitle += _T(" ");

		CString strCrossingCheck;
		strCrossingCheck.LoadString(IDS_WORD_CROSSINGCHECK);
		strTitle += strCrossingCheck;

		super::SetTitle(strTitle.c_str());
	}

	CCrossingCheckDoc::CCrossingCheckDoc()
	{
	}

	BOOL CCrossingCheckDoc::OnNewDocument()
	{
		if (!CHidemdiSubDoc::OnNewDocument())
			return FALSE;
		return TRUE;
	}

	CCrossingCheckDoc::~CCrossingCheckDoc()
	{
	}


	BEGIN_MESSAGE_MAP(CCrossingCheckDoc, CHidemdiSubDoc)
		//{{AFX_MSG_MAP(CCrossingCheckDoc)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//}}AFX_MSG_MAP
	END_MESSAGE_MAP()

	/////////////////////////////////////////////////////////////////////////////
	// CCrossingCheckDoc 診断

#ifdef _DEBUG
	void CCrossingCheckDoc::AssertValid() const
	{
		CHidemdiSubDoc::AssertValid();
	}

	void CCrossingCheckDoc::Dump(CDumpContext& dc) const
	{
		CHidemdiSubDoc::Dump(dc);
	}
#endif //_DEBUG

	/////////////////////////////////////////////////////////////////////////////
	// CCrossingCheckDoc シリアライズ

	void CCrossingCheckDoc::Serialize(CArchive& ar)
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
	// CCrossingCheckDoc コマンド

} //namespace ViewCrossingCheck
