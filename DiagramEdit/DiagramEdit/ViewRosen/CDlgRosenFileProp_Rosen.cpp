/*
OuDiaSecond Copyright (C) 2017-2026 diagram_mania

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
// DlgRosenFileProp_Rosen.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "str/CStrCharSizeMb.h"
#include "str\strToWstr.h"

#include "..\DiagramEdit.h"
#include "CDlgRosenFileProp.h"
#include "CDlgRosenFileProp_Rosen.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace ViewRosen {

	/////////////////////////////////////////////////////////////////////////////
	// CDlgRosenFileProp_Rosen ダイアログ
	// ********************************
	//	CDlgRosenFileProp_Rosen
	// ********************************

	CDlgRosenFileProp* CDlgRosenFileProp_Rosen::GetParent()
	{
		return static_cast<CDlgRosenFileProp*>(CWnd::GetParent());
	}

	//void CDlgRosenFileProp_Rosen::updateUIState()
	//{
	//}

	void CDlgRosenFileProp_Rosen::updateUI()
	{
		CDlgRosenFileProp::CPropEditorData*	pPropEditorData = GetParent()->getPropEditorData();
		// --------------------------------
		m_strEDIT_RosenName
			= pPropEditorData->getUIRosenName().c_str();
		m_iEDIT_EkimeiLength
			= pPropEditorData->getUIDispProp().getEkimeiLength();
		//m_iEDIT_JikokuhyouRessyaWidth
		//	= pPropEditorData->getUIDispProp().getJikokuhyouRessyaWidth();
		//add_by_d_mania
		//m_iEDIT_AnySecondIncDec1
		//	= pPropEditorData->getUIDispProp().getAnySecondIncDec1();
		//m_iEDIT_AnySecondIncDec2
		//	= pPropEditorData->getUIDispProp().getAnySecondIncDec2();
		m_iEDIT_EnableOperation
			= pPropEditorData->getUIEnableOperation();
		//m_bEDIT_DisplayRessyamei
		//	= pPropEditorData->getUIDispProp().getDisplayRessyamei();
		//m_bEDIT_DisplayOuterTerminalO
		//	= pPropEditorData->getUIDispProp().getDisplayOuterTerminalO();
		//m_bEDIT_DisplayOuterTerminalT
		//	= pPropEditorData->getUIDispProp().getDisplayOuterTerminalT();
		m_strEDIT_KudariDiaAlias
			= pPropEditorData->getUIKudariDiaAlias().c_str();
		m_strEDIT_NoboriDiaAlias
			= pPropEditorData->getUINoboriDiaAlias().c_str();
		m_bEDIT_OperationNumberReverse
			= pPropEditorData->getUIOperationNumberReverse();
		m_iEDIT_OperationNumberRows
			= pPropEditorData->getUIDispProp().getOperationNumberRows();
		m_bEDIT_OperationCrossKitenJikoku
			= pPropEditorData->getUIOperationCrossKitenJikoku();
		m_iEDIT_KijunDiaIndex
			= pPropEditorData->getUIKijunDiaIndex();
		m_bEDIT_DisableHiddenSyubetsu
			= pPropEditorData->getUIDisableHiddenSyubetsu();
		// --------------------------------

		UpdateData(FALSE);
	}

	int CDlgRosenFileProp_Rosen::updatePropEditorData()
	{
		CDlgRosenFileProp::CPropEditorData*	pPropEditorData = GetParent()->getPropEditorData();
		// --------------------------------
		int	iRv = 0;
		if (iRv >= 0)
		{
			CString	aString;
			GetDlgItemText(IDC_EDIT_EkimeiLength, aString);
			aString = CStrCharSizeMb::strToSingleByte(stringOf((LPCTSTR)aString)).c_str();
			//aString = CStrCharSizeMb::strToSingleByte( (LPCTSTR)aString ).c_str() ;
			SetDlgItemText(IDC_EDIT_EkimeiLength, aString);
			//GetDlgItemText(IDC_EDIT_JikokuhyouRessyaWidth, aString);
			//aString = CStrCharSizeMb::strToSingleByte(stringOf((LPCTSTR)aString)).c_str();
			//aString = CStrCharSizeMb::strToSingleByte( (LPCTSTR)aString ).c_str() ;
			//SetDlgItemText(IDC_EDIT_JikokuhyouRessyaWidth, aString);
			//add_by_d_mania
			//GetDlgItemText(IDC_EDIT_AnySecondIncDec1, aString);
			//aString = CStrCharSizeMb::strToSingleByte(stringOf((LPCTSTR)aString)).c_str();
			//aString = CStrCharSizeMb::strToSingleByte( (LPCTSTR)aString ).c_str() ;
			//SetDlgItemText(IDC_EDIT_AnySecondIncDec1, aString);
			//GetDlgItemText(IDC_EDIT_AnySecondIncDec2, aString);
			//aString = CStrCharSizeMb::strToSingleByte(stringOf((LPCTSTR)aString)).c_str();
			//aString = CStrCharSizeMb::strToSingleByte( (LPCTSTR)aString ).c_str() ;
			//SetDlgItemText(IDC_EDIT_AnySecondIncDec2, aString);
			//GetDlgItemText(IDC_COMBO_OperationNumberRows, aString);
			//aString = CStrCharSizeMb::strToSingleByte(stringOf((LPCTSTR)aString)).c_str();
			//aString = CStrCharSizeMb::strToSingleByte( (LPCTSTR)aString ).c_str() ;
			//SetDlgItemText(IDC_COMBO_OperationNumberRows, aString);

			if (!UpdateData())
			{
				iRv = -1;
			}
		}
		if (iRv >= 0)
		{
			pPropEditorData->setUIRosenName((LPCTSTR)m_strEDIT_RosenName);
			pPropEditorData->setUIEnableOperation(m_iEDIT_EnableOperation);
			pPropEditorData->setUIKudariDiaAlias((LPCTSTR)m_strEDIT_KudariDiaAlias);
			pPropEditorData->setUINoboriDiaAlias((LPCTSTR)m_strEDIT_NoboriDiaAlias);
			pPropEditorData->setUIOperationNumberReverse(m_bEDIT_OperationNumberReverse);
			pPropEditorData->setUIOperationCrossKitenJikoku(m_bEDIT_OperationCrossKitenJikoku);
			pPropEditorData->setUIKijunDiaIndex(m_iEDIT_KijunDiaIndex);
			pPropEditorData->setUIDisableHiddenSyubetsu(m_bEDIT_DisableHiddenSyubetsu);
			{
				CdDedDispProp	aDispProp = pPropEditorData->getUIDispProp();
				aDispProp.setEkimeiLength(m_iEDIT_EkimeiLength);
				aDispProp.setOperationNumberRows(m_iEDIT_OperationNumberRows);
				//aDispProp.setJikokuhyouRessyaWidth(m_iEDIT_JikokuhyouRessyaWidth);
				//aDispProp.setAnySecondIncDec1(m_iEDIT_AnySecondIncDec1);
				//aDispProp.setAnySecondIncDec2(m_iEDIT_AnySecondIncDec2);
				//aDispProp.setDisplayRessyamei(m_bEDIT_DisplayRessyamei);
				//aDispProp.setDisplayOuterTerminalO(m_bEDIT_DisplayOuterTerminalO);
				//aDispProp.setDisplayOuterTerminalT(m_bEDIT_DisplayOuterTerminalT);
				pPropEditorData->setUIDispProp(aDispProp);
			}
		}
		// --------------------------------
		return iRv;
	}

	// ----------------------------------------------------------------
	//	MFC
	// ----------------------------------------------------------------

	CDlgRosenFileProp_Rosen::CDlgRosenFileProp_Rosen(CWnd* pParent /*=NULL*/)
		: CDialog(CDlgRosenFileProp_Rosen::IDD, pParent)
		//, m_iEDIT_JikokuhyouRessyaWidth(0)
		, m_iEDIT_EnableOperation(0)
		//, m_bEDIT_DisplayRessyamei(FALSE)
		//, m_bEDIT_DisplayOuterTerminalO(FALSE)
		//, m_bEDIT_DisplayOuterTerminalT(FALSE)
		, m_bEDIT_OperationNumberReverse(FALSE)
		, m_iEDIT_OperationNumberRows(1)
		, m_bEDIT_OperationCrossKitenJikoku(TRUE)
		, m_iEDIT_KijunDiaIndex(0)
		, m_bEDIT_DisableHiddenSyubetsu(FALSE)
	{
		//{{AFX_DATA_INIT(CDlgRosenFileProp_Rosen)
		m_strEDIT_RosenName = _T("");
		m_iEDIT_EkimeiLength = 5;
		m_strEDIT_KudariDiaAlias = _T("");
		m_strEDIT_NoboriDiaAlias = _T("");
		//}}AFX_DATA_INIT
	}


	void CDlgRosenFileProp_Rosen::DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
		//{{AFX_DATA_MAP(CDlgRosenFileProp_Rosen)
		DDX_Text(pDX, IDC_EDIT_RosenName, m_strEDIT_RosenName);
		DDX_Text(pDX, IDC_EDIT_EkimeiLength, m_iEDIT_EkimeiLength);
		DDV_MinMaxUInt(pDX, m_iEDIT_EkimeiLength, 1, 29);
		//DDX_Text(pDX, IDC_EDIT_JikokuhyouRessyaWidth, m_iEDIT_JikokuhyouRessyaWidth);
		//DDV_MinMaxInt(pDX, m_iEDIT_JikokuhyouRessyaWidth, 4, 255);//edit_by_d_mania
		//DDX_Text(pDX, IDC_EDIT_AnySecondIncDec1, m_iEDIT_AnySecondIncDec1);
		//DDV_MinMaxInt(pDX, m_iEDIT_AnySecondIncDec1, -60, 60);//add_by_d_mania
		//DDX_Text(pDX, IDC_EDIT_AnySecondIncDec2, m_iEDIT_AnySecondIncDec2);
		//DDV_MinMaxInt(pDX, m_iEDIT_AnySecondIncDec2, -60, 60);//add_by_d_mania
		DDX_CBIndex(pDX, IDC_COMBO_EnableOperation, m_iEDIT_EnableOperation);
		//DDX_Check(pDX, IDC_EDIT_DisplayRessyamei, m_bEDIT_DisplayRessyamei);
		//DDX_Check(pDX, IDC_EDIT_DisplayOuterTerminalO, m_bEDIT_DisplayOuterTerminalO);
		//DDX_Check(pDX, IDC_EDIT_DisplayOuterTerminalT, m_bEDIT_DisplayOuterTerminalT);
		DDX_Text(pDX, IDC_EDIT_KudariDiaAlias, m_strEDIT_KudariDiaAlias);
		DDX_Text(pDX, IDC_EDIT_NoboriDiaAlias, m_strEDIT_NoboriDiaAlias);
		DDX_Check(pDX, IDC_EDIT_OperationNumberReverse, m_bEDIT_OperationNumberReverse);
		DDX_Text(pDX, IDC_EDIT_OperationNumberRows, m_iEDIT_OperationNumberRows);
		DDV_MinMaxUInt(pDX, m_iEDIT_OperationNumberRows, 1, 5);
		DDX_Check(pDX, IDC_EDIT_OperationCrossKitenJikoku, m_bEDIT_OperationCrossKitenJikoku);
		DDX_CBIndex(pDX, IDC_COMBO_KijunDiaIndex, m_iEDIT_KijunDiaIndex);
		DDX_Check(pDX, IDC_EDIT_DisableHiddenSyubetsu, m_bEDIT_DisableHiddenSyubetsu);
		//}}AFX_DATA_MAP
	}


	BEGIN_MESSAGE_MAP(CDlgRosenFileProp_Rosen, CDialog)
		//{{AFX_MSG_MAP(CDlgRosenFileProp_Rosen)
		//ON_COMMAND(IDC_EDIT_DisplayRessyamei, &CDlgRosenFileProp_Rosen::OnViewDisplayRessyamei)
		//ON_UPDATE_COMMAND_UI(IDC_EDIT_DisplayRessyamei, &CDlgRosenFileProp_Rosen::OnUpdateViewDisplayRessyamei)
		//ON_COMMAND(IDC_EDIT_EnableOperation, &CDlgRosenFileProp_Rosen::OnViewEnableOperation)
		//ON_UPDATE_COMMAND_UI(IDC_EDIT_EnableOperation, &CDlgRosenFileProp_Rosen::OnUpdateViewEnableOperation)
		//}}AFX_MSG_MAP
		//ON_BN_CLICKED(IDC_EDIT_EnableOperation, &CDlgRosenFileProp_Rosen::OnBnClickedEditEnableoperation)
	END_MESSAGE_MAP()

	/////////////////////////////////////////////////////////////////////////////
	// CDlgRosenFileProp_Rosen メッセージ ハンドラ

	BOOL CDlgRosenFileProp_Rosen::OnInitDialog()
	{
		CDialog::OnInitDialog();

		// コンボボックス
		{
			CComboBox*	pCComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_EnableOperation);

			tstring strTemp = _T("無効");
			pCComboBox->AddString(strTemp.c_str());
			strTemp = _T("簡易モード");
			pCComboBox->AddString(strTemp.c_str());
			strTemp = _T("通常モード");
			pCComboBox->AddString(strTemp.c_str());
			//無効;完全モード;軽量モード;
		}
		{
			CComboBox* pCComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_KijunDiaIndex);

			const CentDedDiaCont* pCentDedDiaCont = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedDiaCont();
			for (int idx = 0; idx < pCentDedDiaCont->size(); idx++)
			{
				pCComboBox->AddString(pCentDedDiaCont->get(idx).getName().c_str());

			}
			if (pCentDedDiaCont->size() == 0)
			{
				tstring strTemp = _T("ダイヤ無し");
				pCComboBox->AddString(strTemp.c_str());
			}
		}
		// --------------------------------
		//updateUIState();

		return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
					  // 例外: OCX プロパティ ページの戻り値は FALSE となります
	}

} //namespace ViewRosen


//void ViewRosen::CDlgRosenFileProp_Rosen::OnBnClickedEditEnableoperation()
//{
//	// TODO: ここにコントロール通知ハンドラー コードを追加します。
//
//	m_bEDIT_EnableOperation
//}
