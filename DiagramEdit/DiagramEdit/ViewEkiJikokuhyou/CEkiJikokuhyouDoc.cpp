/*
OuDiaSecond Copyright (C) 2017-2025 diagram_mania

このプログラムは、take-okm氏が作成したOuDiaを改造したソフトウェアです。
このプログラム利用については、take-okm氏記載の下記文書に準拠します。
*/
#include "stdafx.h"

#include "..\DiagramEdit.h"
#include "CEkiJikokuhyouDoc.h"
//#include "str/stringSplit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace ViewEkiJikokuhyou {

	/////////////////////////////////////////////////////////////////////////////
	// CEkiJikokuhyouDoc

	IMPLEMENT_DYNCREATE(CEkiJikokuhyouDoc, CHidemdiSubDoc)

	void CEkiJikokuhyouDoc::SetTitle(LPCTSTR lpszTitle)
	{
		vector<tstring>	arstrTitle = splitc< vector< tstring > >('\n', lpszTitle);
		m_strDiaName = arstrTitle[0];
		m_eRessyahoukou = (ERessyahoukou)_ttoi(arstrTitle[1].c_str());
		//m_iEkiIndex = _ttoi(arstrTitle[2].c_str());
		m_iEkiID = _ttoi(arstrTitle[2].c_str());

		//平日ダイヤ ○○駅 下り時刻表
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


		CString	strRessyahoukou;
		if (m_eRessyahoukou == Ressyahoukou_Kudari)
		{
			if (pCentDedRosen->getKudariDiaAlias().empty())
			{
				strRessyahoukou.LoadString(IDS_WORD_KUDARIJIKOKUHYOU);
			}
			else
			{
				strRessyahoukou = pCentDedRosen->getKudariDiaAlias().c_str();
				CString strJikokuhyou;
				strJikokuhyou.LoadString(IDS_WORD_JIKOKUHYOU);
				strRessyahoukou += strJikokuhyou;
			}
		}
		else
		{
			if (pCentDedRosen->getNoboriDiaAlias().empty())
			{
					strRessyahoukou.LoadString(IDS_WORD_NOBORIJIKOKUHYOU);
			}
			else
			{
				strRessyahoukou = pCentDedRosen->getNoboriDiaAlias().c_str();
				CString strJikokuhyou;
				strJikokuhyou.LoadString(IDS_WORD_JIKOKUHYOU);
				strRessyahoukou += strJikokuhyou;
			}
		}

		strTitle += strRessyahoukou;

		super::SetTitle(strTitle.c_str());
	}

	CEkiJikokuhyouDoc::CEkiJikokuhyouDoc()
	{
	}

	BOOL CEkiJikokuhyouDoc::OnNewDocument()
	{
		if (!CHidemdiSubDoc::OnNewDocument())
			return FALSE;
		return TRUE;
	}

	CEkiJikokuhyouDoc::~CEkiJikokuhyouDoc()
	{
	}


	BEGIN_MESSAGE_MAP(CEkiJikokuhyouDoc, CHidemdiSubDoc)
		//{{AFX_MSG_MAP(CEkiJikokuhyouDoc)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//}}AFX_MSG_MAP
	END_MESSAGE_MAP()

	/////////////////////////////////////////////////////////////////////////////
	// CEkiJikokuhyouDoc 診断

#ifdef _DEBUG
	void CEkiJikokuhyouDoc::AssertValid() const
	{
		CHidemdiSubDoc::AssertValid();
	}

	void CEkiJikokuhyouDoc::Dump(CDumpContext& dc) const
	{
		CHidemdiSubDoc::Dump(dc);
	}
#endif //_DEBUG

	/////////////////////////////////////////////////////////////////////////////
	// CEkiJikokuhyouDoc シリアライズ

	void CEkiJikokuhyouDoc::Serialize(CArchive& ar)
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
	// CEkiJikokuhyouDoc コマンド

} //namespace ViewEkiJikokuhyou
