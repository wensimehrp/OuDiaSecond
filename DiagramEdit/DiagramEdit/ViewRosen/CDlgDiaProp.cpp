/*
OuDiaSecond Copyright (C) 2017-2025 diagram_mania

このプログラムは、take-okm氏が作成したOuDiaを改造したソフトウェアです。
このプログラム利用については、take-okm氏記載の下記文書に準拠します。
*/
/*
	OuDia - Win32 Application Software to draw a "Train Service Planning
 Diagram" based on a "Train Timetable".

Copyright (C) 2006-2017 take-okm

This program is free software; you can redistribute it and/or modify it 
under the terms of the GNU General Public License as published by the Free 
Software Foundation; either version 3 of the License, or (at your option) 
any later version. 

This program is distributed in the hope that it will be useful, but WITHOUT 
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for 
more details. 

You should have received a copy of the GNU General Public License along with
 this program. If not, see <http://www.gnu.org/licenses/>.

  In addition, as a special exception, take-okm
  gives permission to link the code of this program with
  the "MFC(Microsoft Foundation Class library) Version 9.0" 
  (or with modified versions of "MFC Version 9.0" that use the same license as 
  "MFC Version 9.0" ), and distribute linked combinations including
  the two.  You must obey the GNU General Public License in all
  respects for all of the code used other than  "MFC".  If you modify
  this file, you may extend this exception to your version of the
  file, but you are not obligated to do so.  If you do not wish to
  do so, delete this exception statement from your version.


(訳: 

	OuDia - 列車時刻表をもとに、ダイヤグラムを描画するWin32アプリケーシ
ョン。

Copyright (C) 2006-2017 take-okm 

このプログラムはフリーソフトウェアです。あなたはこれを、フリーソフトウェア財
団によって発行されたGNU 一般公衆利用許諾書(バージョン3か、それ以降のバージョ
ンのうちどれか)が定める条件の下で再頒布または改変 することができます。

このプログラムは有用であることを願って頒布されますが、*全くの無保証 *です。
商業可能性の保証や特定目的への適合性は、言外に示されたものも 含め、全く存在
しません。詳しくはGNU 一般公衆利用許諾書をご覧ください。

あなたはこのプログラムと共に、GNU 一般公衆利用許諾書のコピーを一部 受け取っ
ているはずです。もし受け取っていなければ、<http://www.gnu.org/licenses/> を
ご覧ください。

)

  加えて、特別な例外として、take-okm はこのプログラムのコードを 
  "MFC(Microsoft Foundation Class library) Version 9.0" 
  (  あるいは "MFC Version 9.0" と同じライセンスが適用された
  "MFC Version 9.0" の改変されたバージョン)とリンクし、
  リンクされた両者を含む結合著作物を頒布する許可を与えます。
  あなたは "MFC" 以外で使われているすべて
  のコードに関しては全面的にGNU一般公衆利用許諾契約書に従わなければ
  なりません。あなたがこのファイルを改変したならば、あなたはこの例外
  をあなたのバージョンのファイルに引き続き設けることもできますが、そ
  うする義務はありません。もし例外を設けたくなければ、この例外条項を
  あなたのバージョンからは削除してください。)
*/
// CDlgDiaProp.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"

#include "DcDraw/CDcdTargetOnPaint.h"
#include "DcDraw/CaDcdTargetItemPosition.h"
#include "DcDraw/CConverter_WinGdi.h"
#include "..\DiagramEdit.h"
#include "CDlgDiaProp.h"
#include "MfcUtil\MfcUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace ViewRosen{

using namespace OuMfc::MfcUtil;
using namespace std ;

/////////////////////////////////////////////////////////////////////////////
// CDlgDiaProp ダイアログ


void CDlgDiaProp::updateUIState()
{
	// --------------------------------
	//	カラー
	// --------------------------------
	{
		CComboBox* pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_JikokuhyouMainBackColorIndex);

		int idx = pComboBox->GetCurSel();
		//COLORREF*	pColor = NULL;
		if (0 <= idx && idx < sizeof(m_ColorpropJikokuhyouColor) / sizeof(m_ColorpropJikokuhyouColor[0]))
		{
			m_pdcdrawMainBackColor->setCdBrushProp(m_ColorpropJikokuhyouColor[idx]);
			//pColor = &m_ColorpropJikokuhyouColor[idx];
		}
		// --------------------------------
		//if (pColor != NULL)
		//{
		//	CConverter_WinGdi	aConv;
		//	m_pdcdrawColor->setCdBrushProp(CdBrushProp(aConv.CdColorPropOf(*pColor)));
		//}

		CRect	aRect = GetDlgControlRect(this, IDC_STATIC_JikokuhyouMainBackColor);
		InvalidateRect(&aRect);
	}
	{
		CComboBox* pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_JikokuhyouSubBackColorIndex);

		int idx = pComboBox->GetCurSel();
		if (0 <= idx && idx < sizeof(m_ColorpropJikokuhyouColor) / sizeof(m_ColorpropJikokuhyouColor[0]))
		{
			m_pdcdrawSubBackColor->setCdBrushProp(m_ColorpropJikokuhyouColor[idx]);
		}
		CRect	aRect = GetDlgControlRect(this, IDC_STATIC_JikokuhyouSubBackColor);
		InvalidateRect(&aRect);
	}
}

CDlgDiaProp::CDlgDiaProp(
		const tstring& strName ,
		const int &iJikokuhyouMainBackColorIndex,
		const int &iJikokuhyouSubBackColorIndex,
		const int &iJikokuhyouBackPatternIndex,
		const bool& bPatternDiagramPreviewEnable,
		const int& iPatternDiagramPreviewCycleSecond,
		const CdDedDispProp&	aCdDedDispProp,
		CWnd* pParent )
	: CDialog(CDlgDiaProp::IDD, pParent)
	, m_strName( strName )
	, m_iJikokuhyouMainBackColorIndex(iJikokuhyouMainBackColorIndex)
	, m_iJikokuhyouSubBackColorIndex(iJikokuhyouSubBackColorIndex)
	, m_iJikokuhyouBackPatternIndex(iJikokuhyouBackPatternIndex)
	, m_iEDIT_PatternDiagramPreviewEnable(bPatternDiagramPreviewEnable)
	, m_iPatternDiagramPreviewCycleSecond(iPatternDiagramPreviewCycleSecond)
	, m_pdcdrawMainBackColor(NULL)
	, m_pdcdrawSubBackColor(NULL)
{
	//{{AFX_DATA_INIT(CDlgDiaProp)
	m_strEDIT_Name = _T("");
	//}}AFX_DATA_INIT
	m_strEDIT_Name = m_strName.c_str() ;

	for (int idx = 0; idx < CentDedDia::JIKOKUHYOUCOLOR_COUNT; idx++)
	{
		m_ColorpropJikokuhyouColor[idx] = aCdDedDispProp.getJikokuhyouBackColor(idx);
	}

	m_iEDIT_PatternDiagramPreviewCycleMinute = m_iPatternDiagramPreviewCycleSecond / 60;
	m_iEDIT_PatternDiagramPreviewCycleSecond = m_iPatternDiagramPreviewCycleSecond % 60;

}


void CDlgDiaProp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDiaProp)
	DDX_Text(pDX, IDC_EDIT_Name, m_strEDIT_Name);
	DDX_CBIndex(pDX, IDC_COMBO_JikokuhyouMainBackColorIndex, m_iJikokuhyouMainBackColorIndex);
	DDX_CBIndex(pDX, IDC_COMBO_JikokuhyouSubBackColorIndex, m_iJikokuhyouSubBackColorIndex);
	DDX_CBIndex(pDX, IDC_COMBO_JikokuhyouBackPatternIndex, m_iJikokuhyouBackPatternIndex);
	DDX_Check(pDX, IDC_CHECK_PatternDiagramPreviewEnable, m_iEDIT_PatternDiagramPreviewEnable);
	DDX_Text(pDX, IDC_EDIT_CycleMinute, m_iEDIT_PatternDiagramPreviewCycleMinute);
	DDX_Text(pDX, IDC_EDIT_CycleSecond, m_iEDIT_PatternDiagramPreviewCycleSecond);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDiaProp, CDialog)
	//{{AFX_MSG_MAP(CDlgDiaProp)
	ON_WM_PAINT()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_CBN_SELCHANGE(IDC_COMBO_JikokuhyouMainBackColorIndex, &CDlgDiaProp::OnCbnSelchangeComboJikokuhyoumainbackcolorindex)
	ON_CBN_SELCHANGE(IDC_COMBO_JikokuhyouSubBackColorIndex, &CDlgDiaProp::OnCbnSelchangeComboJikokuhyousubbackcolorindex)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDiaProp メッセージ ハンドラ

void CDlgDiaProp::OnOK() 
{
	// --------------------------------
	//	UpdateData()の前処理
	// --------------------------------
	////IDC_EDIT_PasteZoubun 
	//{
	//	//	空文字列なら、0を補います。
	//	CWnd* pCWnd = GetDlgItem(IDC_EDIT_CycleMinute);
	//	CString	strLs;
	//	pCWnd->GetWindowText(strLs);
	//	strLs = tstringOf(
	//		CStrCharSizeMb::strToSingleByte(stringOf((LPCTSTR)strLs))).c_str();
	//	if (strLs.IsEmpty())
	//	{
	//		strLs = _T("0");
	//	}
	//	pCWnd->SetWindowText(strLs);
	//}
	////IDC_EDIT_PasteZoubunSecond
	//{
	//	//	空文字列なら、0を補います。
	//	CWnd* pCWnd = GetDlgItem(IDC_EDIT_CycleSecond);
	//	CString	strLs;
	//	pCWnd->GetWindowText(strLs);
	//	strLs = tstringOf(
	//		CStrCharSizeMb::strToSingleByte(stringOf((LPCTSTR)strLs))).c_str();
	//	if (strLs.IsEmpty())
	//	{
	//		strLs = _T("0");
	//	}
	//	pCWnd->SetWindowText(strLs);
	//}

	UpdateData() ;
	/**
		パターンダイヤプレビューの秒数の入力値の修正を行います
		分：0～180
		秒：0～10800(3時間)
		まず、上記の通りに修正した上で、分と秒を合わせて、60～10800秒になるように修正します。
	*/
	if (m_iEDIT_PatternDiagramPreviewCycleMinute < 0)
	{
		m_iEDIT_PatternDiagramPreviewCycleMinute = 0;
	}
	else if(m_iEDIT_PatternDiagramPreviewCycleMinute > 180)
	{
		m_iEDIT_PatternDiagramPreviewCycleMinute = 180;
	}

	if (m_iEDIT_PatternDiagramPreviewCycleSecond < 0)
	{
		m_iEDIT_PatternDiagramPreviewCycleSecond = 0;
	}
	else if (m_iEDIT_PatternDiagramPreviewCycleSecond > 10800)
	{
		m_iEDIT_PatternDiagramPreviewCycleSecond = 10800;
	}

	m_iPatternDiagramPreviewCycleSecond = m_iEDIT_PatternDiagramPreviewCycleMinute * 60 + m_iEDIT_PatternDiagramPreviewCycleSecond;

	if (m_iPatternDiagramPreviewCycleSecond < 60)
	{
		m_iPatternDiagramPreviewCycleSecond = 60;
	}
	else if(m_iPatternDiagramPreviewCycleSecond > 10800)
	{
		m_iPatternDiagramPreviewCycleSecond = 10800;
	}

	int iRv = 0;
	CString	strError ;
	if ( iRv >= 0 ){
		if ( m_strEDIT_Name.GetLength() == 0 ){
			GetDlgItemText( IDC_STATIC_ERROR_NameNotSet , strError ) ; 
			iRv = -1 ;	//	ダイヤ名が設定されていません。
		}	else	{
			m_strName = (LPCTSTR)m_strEDIT_Name ;
		}
	}
	if ( iRv >= 0 ){
		CDialog::OnOK();
	}	else	{
		MessageBox( strError , NULL , MB_OK | MB_ICONEXCLAMATION ) ;
	}
}

BOOL CDlgDiaProp::OnInitDialog() 
{
	
	// TODO: この位置に初期化の補足処理を追加してください

	m_pdcdrawMainBackColor = new CDcdRectangle(
		CdPenProp(1));
	m_pdcdrawSubBackColor = new CDcdRectangle(
		CdPenProp(1));

	// コンボボックス
	{
		CComboBox*	pCComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_JikokuhyouMainBackColorIndex);
		CComboBox*	pCComboBox2 = (CComboBox*)GetDlgItem(IDC_COMBO_JikokuhyouSubBackColorIndex);

		tstring strTemp = _T("1");
		pCComboBox->AddString(strTemp.c_str());
		pCComboBox2->AddString(strTemp.c_str());
		strTemp = _T("2");
		pCComboBox->AddString(strTemp.c_str());
		pCComboBox2->AddString(strTemp.c_str());
		strTemp = _T("3");
		pCComboBox->AddString(strTemp.c_str());
		pCComboBox2->AddString(strTemp.c_str());
		strTemp = _T("4");
		pCComboBox->AddString(strTemp.c_str());
		pCComboBox2->AddString(strTemp.c_str());
		//1;2;3;4;
	}
	// コンボボックス
	{
		CComboBox*	pCComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_JikokuhyouBackPatternIndex);

		tstring strTemp = _T("単色");
		pCComboBox->AddString(strTemp.c_str());
		strTemp = _T("種別色");
		pCComboBox->AddString(strTemp.c_str());
		strTemp = _T("縦縞");
		pCComboBox->AddString(strTemp.c_str());
		strTemp = _T("横縞");
		pCComboBox->AddString(strTemp.c_str());
		strTemp = _T("市松模様");
		pCComboBox->AddString(strTemp.c_str());
		//単色;種別色;縦縞;横縞;市松模様;
	}

	CDialog::OnInitDialog();

	// --------------------------------
	updateUIState();

	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CDlgDiaProp::OnPaint()
{
	CPaintDC dc(this); // 描画用のデバイス コンテキスト

	CDcdTargetOnPaint	aDcdTarget(GetSafeHwnd(), &dc.m_ps);
	// --------------------------------
	//	色の見本表示
	// --------------------------------
	{
		CRect	aRect = GetDlgControlRect(this, IDC_STATIC_JikokuhyouMainBackColor);

		CaDcdTargetItemPosition	aDcdTargetItemPosition(&aDcdTarget,
			CdDcdZoneXy(CdDcdZone(aRect.left, aRect.right - aRect.left),
				CdDcdZone(aRect.top, aRect.bottom - aRect.top)));

		m_pdcdrawMainBackColor->DcDraw(&aDcdTargetItemPosition);
	}
	{
		CRect	aRect = GetDlgControlRect(this, IDC_STATIC_JikokuhyouSubBackColor);

		CaDcdTargetItemPosition	aDcdTargetItemPosition(&aDcdTarget,
			CdDcdZoneXy(CdDcdZone(aRect.left, aRect.right - aRect.left),
				CdDcdZone(aRect.top, aRect.bottom - aRect.top)));

		m_pdcdrawSubBackColor->DcDraw(&aDcdTargetItemPosition);
	}
}

void CDlgDiaProp::OnDestroy()
{
	if (m_pdcdrawMainBackColor != NULL) {
		delete m_pdcdrawMainBackColor;
		m_pdcdrawMainBackColor = NULL;
	}
	if (m_pdcdrawSubBackColor != NULL) {
		delete m_pdcdrawSubBackColor;
		m_pdcdrawSubBackColor = NULL;
	}
	CDialog::OnDestroy();



}
} //namespace ViewRosen


void ViewRosen::CDlgDiaProp::OnCbnSelchangeComboJikokuhyoumainbackcolorindex()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	updateUIState();
}


void ViewRosen::CDlgDiaProp::OnCbnSelchangeComboJikokuhyousubbackcolorindex()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	updateUIState();
}
