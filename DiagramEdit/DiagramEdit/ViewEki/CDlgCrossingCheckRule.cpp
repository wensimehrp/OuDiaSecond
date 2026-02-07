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
// CDlgCrossingCheckRule.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"

#include "..¥DiagramEdit.h"
#include "CDlgCrossingCheckRule.h"
#include "str/stringSplit.h"
//#include "..¥DedRosenFileData¥EditCmd¥EditCmd.h"
#include "Str¥strToWstr.h"
#include "MfcUtil¥MfcUtil.h"
#include "..¥resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


namespace ViewEki{


// ================================================================
//	CDlgCrossingCheckRule::CPropEditUiInternal
// ================================================================
	// ================================
	//@name CPropEditUi - UiData - UiControl 間のデータ転送
	// ================================
void CDlgCrossingCheckRule::CPropEditUiInternal::UiDataToUi( const UIDATA* pUiData ) 
{
	CDlgCrossingCheckRule* pOuter = (CDlgCrossingCheckRule*)( (char*)this - offsetof( CDlgCrossingCheckRule , m_PropEditUiInternal ) ) ;

	if (pUiData->iListSelected >= 0)
	{
		const CrossingCheckRule* pCrossingCheckRuleSel = &pUiData->ContCrossingCheckRule[pUiData->iListSelected];
		/**
			ルールの追加・削除ボタンの有効無効設定
			選択場所の作業、位置によって、有効なボタンが変わります
			・追加
				常に有効
			・コピー
				ルール0個時無効
			・削除
				ルール0個時無効
			・上へ
				ルール0個時無効
				最も上のルールの場合無効。
			・下へ
				ルール0個時無効
				最も下のルールの場合無効。
		*/
		CButton* pButtonAdd = (CButton*)pOuter->GetDlgItem(IDC_BUTTON_CrossingCheckRuleAdd);
		CButton* pButtonCopy = (CButton*)pOuter->GetDlgItem(IDC_BUTTON_CrossingCheckRuleCopy);
		CButton* pButtonCLR = (CButton*)pOuter->GetDlgItem(IDC_BUTTON_CrossingCheckRuleClear);
		CButton* pButtonUp = (CButton*)pOuter->GetDlgItem(IDC_BUTTON_CrossingCheckRuleUp);
		CButton* pButtonDown = (CButton*)pOuter->GetDlgItem(IDC_BUTTON_CrossingCheckRuleDown);

		pButtonAdd->EnableWindow(true);
		if (pUiData->ContCrossingCheckRule.size() == 0)
		{
			pButtonCopy->EnableWindow(false);
			pButtonCLR->EnableWindow(false);
			pButtonUp->EnableWindow(false);
			pButtonDown->EnableWindow(false);

		}
		else if (pUiData->ContCrossingCheckRule.size() == 1)
		{
			pButtonCopy->EnableWindow(true);
			pButtonCLR->EnableWindow(true);
			pButtonUp->EnableWindow(false);
			pButtonDown->EnableWindow(false);
		}
		else if (pUiData->iListSelected == 0)
		{
			pButtonCopy->EnableWindow(true);
			pButtonCLR->EnableWindow(true);
			pButtonUp->EnableWindow(false);
			pButtonDown->EnableWindow(true);
		}
		else if (pUiData->iListSelected == pUiData->ContCrossingCheckRule.size() - 1)
		{
			pButtonCopy->EnableWindow(true);
			pButtonCLR->EnableWindow(true);
			pButtonUp->EnableWindow(true);
			pButtonDown->EnableWindow(false);
		}
		else
		{
			pButtonCopy->EnableWindow(true);
			pButtonCLR->EnableWindow(true);
			pButtonUp->EnableWindow(true);
			pButtonDown->EnableWindow(true);
		}
		{

			CButton* pButton1 = (CButton*)pOuter->GetDlgItem(IDC_RADIO_BeforeArrDep);
			CButton* pButton2 = (CButton*)pOuter->GetDlgItem(IDC_RADIO_BeforeArrDep2);
			CButton* pButton3 = (CButton*)pOuter->GetDlgItem(IDC_RADIO_BeforeIsTsuuka);
			CButton* pButton4 = (CButton*)pOuter->GetDlgItem(IDC_RADIO_BeforeIsTsuuka2);
			CButton* pButton5 = (CButton*)pOuter->GetDlgItem(IDC_RADIO_AfterArrDep);
			CButton* pButton6 = (CButton*)pOuter->GetDlgItem(IDC_RADIO_AfterArrDep2);
			CButton* pButton7 = (CButton*)pOuter->GetDlgItem(IDC_RADIO_AfterIsTsuuka);
			CButton* pButton8 = (CButton*)pOuter->GetDlgItem(IDC_RADIO_AfterIsTsuuka2);
			pButton1->EnableWindow(true);
			pButton2->EnableWindow(true);
			pButton3->EnableWindow(true);
			pButton4->EnableWindow(true);
			pButton5->EnableWindow(true);
			pButton6->EnableWindow(true);
			pButton7->EnableWindow(true);
			pButton8->EnableWindow(true);
		}
		// --------------------------------
		//	DDXを用いた、UiControlへの設定
		// --------------------------------
		{
			// IDC_RADIO_BeforeArrDep
			{
				pOuter->m_iRADIO_BeforeIsArrival = pCrossingCheckRuleSel->bBeforeIsArrival ? 1 : 0;
			}
			// IDC_RADIO_BeforeIsTsuuka 
			{
				pOuter->m_iRADIO_BeforeIsTsuuka = pCrossingCheckRuleSel->bBeforeIsTsuuka ? 1 : 0;
			}
			// IDC_RADIO_AfterArrDep
			{
				pOuter->m_iRADIO_AfterIsArrival = pCrossingCheckRuleSel->bAfterIsArrival ? 1 : 0;
			}
			// IDC_RADIO_AfterIsTsuuka
			{
				pOuter->m_iRADIO_AfterIsTsuuka = pCrossingCheckRuleSel->bAfterIsTsuuka ? 1 : 0;
			}
			// --------------------------------
			pOuter->UpdateData(FALSE);
		}

		// --------------------------------
		//	DDXを用いない、UiControlへの設定
		//	これらは、DDXによる値設定の後で
		//	行わなくてはなりません。
		// --------------------------------
		//IDC_EDIT_CrossingCheckRuleCaption
		{
			CEdit* pCaption = (CEdit*)(pOuter->GetDlgItem(IDC_EDIT_CrossingCheckRuleCaption));
			pCaption->EnableWindow(true);
			pCaption->SetWindowText(pCrossingCheckRuleSel->strCaption.c_str());
			pCaption->SetSel(0, -1);
		}
		//IDC_EDIT_CrossingCheckRuleHeadway
		{
			CEdit* pHeadway = (CEdit*)(pOuter->GetDlgItem(IDC_EDIT_CrossingCheckRuleHeadway));
			pHeadway->EnableWindow(true);
			pHeadway->SetWindowText(to_tstring(pCrossingCheckRuleSel->iHeadwaySecond).c_str());
			pHeadway->SetSel(0, -1);
		}
		//IDC_EDIT_CrossingCheckRuleHeadwayMinimum
		{
			CEdit* pHeadway = (CEdit*)(pOuter->GetDlgItem(IDC_EDIT_CrossingCheckRuleHeadwayMinimum));
			pHeadway->EnableWindow(true);
			pHeadway->SetWindowText(to_tstring(pCrossingCheckRuleSel->iHeadwaySecondMinimum).c_str());
			pHeadway->SetSel(0, -1);
		}
		//IDC_CHECK_Enable
		{
			CButton* pControl = (CButton*)(pOuter->GetDlgItem(IDC_CHECK_Enable));
			pControl->EnableWindow(true);
			pControl->SetCheck(pCrossingCheckRuleSel->bEnable ? BST_CHECKED : BST_UNCHECKED);
		}
		//IDC_LIST_BeforeFrom
		{
			CListBox* pListBoxBF = (CListBox*)pOuter->GetDlgItem(IDC_LIST_BeforeFrom);
			pListBoxBF->EnableWindow(true);
			for (int idx = 0; idx < pListBoxBF->GetCount(); idx++)
			{
				pListBoxBF->SetSel(idx, false);
			}
			for (int idx = 0; idx < (int)pCrossingCheckRuleSel->BeforeFromTrackContentCont.size(); idx++)
			{
				int iListIndex = pOuter->m_MapTrackContentToList[(int)pCrossingCheckRuleSel->BeforeFromTrackContentCont[idx].eTrackType]
					[pCrossingCheckRuleSel->BeforeFromTrackContentCont[idx].iTrackIndex];
				pListBoxBF->SetSel(iListIndex, true);
			}
		}
		//IDC_LIST_BeforeTo
		{
			CListBox* pListBoxBT = (CListBox*)pOuter->GetDlgItem(IDC_LIST_BeforeTo);
			pListBoxBT->EnableWindow(true);
			for (int idx = 0; idx < pListBoxBT->GetCount(); idx++)
			{
				pListBoxBT->SetSel(idx, false);
			}
			for (int idx = 0; idx < (int)pCrossingCheckRuleSel->BeforeToTrackContentCont.size(); idx++)
			{
				int iListIndex = pOuter->m_MapTrackContentToList[(int)pCrossingCheckRuleSel->BeforeToTrackContentCont[idx].eTrackType]
					[pCrossingCheckRuleSel->BeforeToTrackContentCont[idx].iTrackIndex];
				pListBoxBT->SetSel(iListIndex, true);
			}
		}
		//IDC_LIST_AfterFrom
		{
			CListBox* pListBoxAF = (CListBox*)pOuter->GetDlgItem(IDC_LIST_AfterFrom);
			pListBoxAF->EnableWindow(true);
			for (int idx = 0; idx < pListBoxAF->GetCount(); idx++)
			{
				pListBoxAF->SetSel(idx, false);
			}
			for (int idx = 0; idx < (int)pCrossingCheckRuleSel->AfterFromTrackContentCont.size(); idx++)
			{
				int iListIndex = pOuter->m_MapTrackContentToList[(int)pCrossingCheckRuleSel->AfterFromTrackContentCont[idx].eTrackType]
					[pCrossingCheckRuleSel->AfterFromTrackContentCont[idx].iTrackIndex];
				pListBoxAF->SetSel(iListIndex, true);
			}
		}
		//IDC_LIST_AfterTo
		{
			CListBox* pListBoxAT = (CListBox*)pOuter->GetDlgItem(IDC_LIST_AfterTo);
			pListBoxAT->EnableWindow(true);
			for (int idx = 0; idx < pListBoxAT->GetCount(); idx++)
			{
				pListBoxAT->SetSel(idx, false);
			}
			for (int idx = 0; idx < (int)pCrossingCheckRuleSel->AfterToTrackContentCont.size(); idx++)
			{
				int iListIndex = pOuter->m_MapTrackContentToList[(int)pCrossingCheckRuleSel->AfterToTrackContentCont[idx].eTrackType]
					[pCrossingCheckRuleSel->AfterToTrackContentCont[idx].iTrackIndex];
				pListBoxAT->SetSel(iListIndex, true);
			}
		}
	}
	else
	{
		CButton* pButtonAdd = (CButton*)pOuter->GetDlgItem(IDC_BUTTON_CrossingCheckRuleAdd);
		CButton* pButtonCopy = (CButton*)pOuter->GetDlgItem(IDC_BUTTON_CrossingCheckRuleCopy);
		CButton* pButtonCLR = (CButton*)pOuter->GetDlgItem(IDC_BUTTON_CrossingCheckRuleClear);
		CButton* pButtonUp = (CButton*)pOuter->GetDlgItem(IDC_BUTTON_CrossingCheckRuleUp);
		CButton* pButtonDown = (CButton*)pOuter->GetDlgItem(IDC_BUTTON_CrossingCheckRuleDown);
		pButtonAdd->EnableWindow(true);
		pButtonCopy->EnableWindow(false);
		pButtonCLR->EnableWindow(false);
		pButtonUp->EnableWindow(false);
		pButtonDown->EnableWindow(false);

		CEdit* pCaption = (CEdit*)(pOuter->GetDlgItem(IDC_EDIT_CrossingCheckRuleCaption));
		pCaption->EnableWindow(false);
		CEdit* pHeadway = (CEdit*)(pOuter->GetDlgItem(IDC_EDIT_CrossingCheckRuleHeadway));
		pHeadway->EnableWindow(false);
		CEdit* pHeadwayMinimum = (CEdit*)(pOuter->GetDlgItem(IDC_EDIT_CrossingCheckRuleHeadwayMinimum));
		pHeadwayMinimum->EnableWindow(false);
		CButton* pControl = (CButton*)(pOuter->GetDlgItem(IDC_CHECK_Enable));
		pControl->EnableWindow(false);

		CButton* pButton1 = (CButton*)pOuter->GetDlgItem(IDC_RADIO_BeforeArrDep);
		CButton* pButton2 = (CButton*)pOuter->GetDlgItem(IDC_RADIO_BeforeArrDep2);
		CButton* pButton3 = (CButton*)pOuter->GetDlgItem(IDC_RADIO_BeforeIsTsuuka);
		CButton* pButton4 = (CButton*)pOuter->GetDlgItem(IDC_RADIO_BeforeIsTsuuka2);
		CButton* pButton5 = (CButton*)pOuter->GetDlgItem(IDC_RADIO_AfterArrDep);
		CButton* pButton6 = (CButton*)pOuter->GetDlgItem(IDC_RADIO_AfterArrDep2);
		CButton* pButton7 = (CButton*)pOuter->GetDlgItem(IDC_RADIO_AfterIsTsuuka);
		CButton* pButton8 = (CButton*)pOuter->GetDlgItem(IDC_RADIO_AfterIsTsuuka2);
		pButton1->EnableWindow(false);
		pButton2->EnableWindow(false);
		pButton3->EnableWindow(false);
		pButton4->EnableWindow(false);
		pButton5->EnableWindow(false);
		pButton6->EnableWindow(false);
		pButton7->EnableWindow(false);
		pButton8->EnableWindow(false);

		CListBox* pListBoxBF = (CListBox*)pOuter->GetDlgItem(IDC_LIST_BeforeFrom);
		CListBox* pListBoxBT = (CListBox*)pOuter->GetDlgItem(IDC_LIST_BeforeTo);
		CListBox* pListBoxAF = (CListBox*)pOuter->GetDlgItem(IDC_LIST_AfterFrom);
		CListBox* pListBoxAT = (CListBox*)pOuter->GetDlgItem(IDC_LIST_AfterTo);
		pListBoxBF->EnableWindow(false);
		pListBoxBT->EnableWindow(false);
		pListBoxAF->EnableWindow(false);
		pListBoxAT->EnableWindow(false);
	}
	{
		CListBox* pListBox = (CListBox*)pOuter->GetDlgItem(IDC_LIST_CrossingCheckRule);
		pListBox->ResetContent();
		for (int idx = 0; idx < (int)pUiData->ContCrossingCheckRule.size(); idx++)
		{
			tstring strTemp;
			strTemp += _T("[");
			strTemp += to_tstring(idx + 1);
			strTemp += _T("] ");
			if (!pUiData->ContCrossingCheckRule[idx].bEnable)
			{
				strTemp += _T("[無効] ");
			}
			strTemp += pUiData->ContCrossingCheckRule[idx].strCaption;
			pListBox->AddString(strTemp.c_str());
		}
		pListBox->SetCurSel(pUiData->iListSelected);
	}
	if (pUiData->iUiOperation == 2)
	{
		SetFocus(offsetof(CrossingCheckRule, strCaption));
	}
}

void CDlgCrossingCheckRule::CPropEditUiInternal::UiDataFromUi( UIDATA* pUiData ) 
{
	CDlgCrossingCheckRule* pOuter = (CDlgCrossingCheckRule*)( (char*)this - offsetof( CDlgCrossingCheckRule , m_PropEditUiInternal ) ) ;
	int iRv = 0 ;
	
	// --------------------------------
	//	DDXを用いた、UiControlへの設定
	// --------------------------------
	if ( !pOuter->UpdateData( TRUE ) )
	{
		iRv = -1 ;	//	UpdateData でエラーが発生しました。
	}

	/**
		iUiOperationが0の時以外は、この動作はスキップされるので、
		iUiOperationが0であると仮定して進める
	*/
	if (iRv >= 0)
	{
		if (pUiData->iListSelected >= 0)
		{
			CrossingCheckRule* pCrossingCheckRuleSel = &pUiData->ContCrossingCheckRule[pUiData->iListSelected];

			//IDC_RADIO_BeforeArrDep
			{
				pCrossingCheckRuleSel->bBeforeIsArrival = pOuter->m_iRADIO_BeforeIsArrival == 1;
			}
			//IDC_RADIO_BeforeIsTsuuka
			{
				pCrossingCheckRuleSel->bBeforeIsTsuuka = pOuter->m_iRADIO_BeforeIsTsuuka == 1;
			}
			//IDC_RADIO_AfterArrDep
			{
				pCrossingCheckRuleSel->bAfterIsArrival = pOuter->m_iRADIO_AfterIsArrival == 1;
			}
			//IDC_RADIO_AfterIsTsuuka
			{
				pCrossingCheckRuleSel->bAfterIsTsuuka = pOuter->m_iRADIO_AfterIsTsuuka == 1;
			}

			//IDC_EDIT_CrossingCheckRuleCaption
			{
				CString strText;
				CEdit* pControl = (CEdit*)(pOuter->GetDlgItem(IDC_EDIT_CrossingCheckRuleCaption));
				pControl->GetWindowText(strText);
				pCrossingCheckRuleSel->strCaption = (LPCTSTR)strText;
			}

			//IDC_EDIT_CrossingCheckRuleHeadway
			{
				CString strText;
				CEdit* pControl = (CEdit*)(pOuter->GetDlgItem(IDC_EDIT_CrossingCheckRuleHeadway));
				pControl->GetWindowText(strText);
				pCrossingCheckRuleSel->iHeadwaySecond = _ttoi(strText);
			}

			//IDC_EDIT_CrossingCheckRuleHeadwayMinimum
			{
				CString strText;
				CEdit* pControl = (CEdit*)(pOuter->GetDlgItem(IDC_EDIT_CrossingCheckRuleHeadwayMinimum));
				pControl->GetWindowText(strText);
				pCrossingCheckRuleSel->iHeadwaySecondMinimum = _ttoi(strText);
			}

			//IDC_CHECK_Enable
			{
				CButton* pControl = (CButton*)(pOuter->GetDlgItem(IDC_CHECK_Enable));
				pCrossingCheckRuleSel->bEnable = (pControl->GetCheck() == BST_CHECKED);
			}

			//IDC_LIST_BeforeFrom
			{
				CListBox* pListBoxBF = (CListBox*)pOuter->GetDlgItem(IDC_LIST_BeforeFrom);
				vector<TrackContent> TrackContentTemp;
				for (int idx = 0; idx < pListBoxBF->GetCount(); idx++)
				{
					if (pListBoxBF->GetSel(idx))
					{
						TrackContentTemp.push_back(pOuter->m_MapListToTrackContent[idx]);
					}
				}
				pCrossingCheckRuleSel->BeforeFromTrackContentCont = TrackContentTemp;
			}

			//IDC_LIST_BeforeTo
			{
				CListBox* pListBoxBT = (CListBox*)pOuter->GetDlgItem(IDC_LIST_BeforeTo);
				vector<TrackContent> TrackContentTemp;
				for (int idx = 0; idx < pListBoxBT->GetCount(); idx++)
				{
					if (pListBoxBT->GetSel(idx))
					{
						TrackContentTemp.push_back(pOuter->m_MapListToTrackContent[idx]);
					}
				}
				pCrossingCheckRuleSel->BeforeToTrackContentCont = TrackContentTemp;
			}

			//IDC_LIST_AfterFrom
			{
				CListBox* pListBoxAF = (CListBox*)pOuter->GetDlgItem(IDC_LIST_AfterFrom);
				vector<TrackContent> TrackContentTemp;
				for (int idx = 0; idx < pListBoxAF->GetCount(); idx++)
				{
					if (pListBoxAF->GetSel(idx))
					{
						TrackContentTemp.push_back(pOuter->m_MapListToTrackContent[idx]);
					}
				}
				pCrossingCheckRuleSel->AfterFromTrackContentCont = TrackContentTemp;
			}

			//IDC_LIST_AfterTo
			{
				CListBox* pListBoxAT = (CListBox*)pOuter->GetDlgItem(IDC_LIST_AfterTo);
				vector<TrackContent> TrackContentTemp;
				for (int idx = 0; idx < pListBoxAT->GetCount(); idx++)
				{
					if (pListBoxAT->GetSel(idx))
					{
						TrackContentTemp.push_back(pOuter->m_MapListToTrackContent[idx]);
					}
				}
				pCrossingCheckRuleSel->AfterToTrackContentCont = TrackContentTemp;
			}
		}
	}
}

void CDlgCrossingCheckRule::CPropEditUiInternal::ShowError( 
			const tstring& strErrorReason ,
			const tstring& strInfo ) 
{
	CDlgCrossingCheckRule* pOuter = (CDlgCrossingCheckRule*)( (char*)this - offsetof( CDlgCrossingCheckRule , m_PropEditUiInternal ) ) ;

	CString strErrorMsg = strErrorReason.c_str() ;

	if ( strErrorReason == ERRMSG_EMPTY_BEFOREFROM)
	{
		//pOuter->GetDlgItem( IDC_ERR_EkimeiNo )->GetWindowText( strErrorMsg )  ;
		pOuter->GetDlgItem(IDC_ERR_EMPTY_BEFOREFROM)->GetWindowText(strErrorMsg);
	}
	else if (strErrorReason == ERRMSG_EMPTY_BEFORETO)
	{
		pOuter->GetDlgItem(IDC_ERR_EMPTY_BEFORETO)->GetWindowText(strErrorMsg);
	}
	else if (strErrorReason == ERRMSG_EMPTY_AFTERFROM)
	{
		pOuter->GetDlgItem(IDC_ERR_EMPTY_AFTERFROM)->GetWindowText(strErrorMsg);
	}
	else if (strErrorReason == ERRMSG_EMPTY_AFTERTO)
	{
		pOuter->GetDlgItem(IDC_ERR_EMPTY_AFTERTO)->GetWindowText(strErrorMsg);
	}
	else if (strErrorReason == ERRMSG_INVALID_HEADWAY)
	{
		pOuter->GetDlgItem(IDC_ERR_INVALID_HEADWAY)->GetWindowText(strErrorMsg);
	}
	else if (strErrorReason == ERRMSG_INVALID_HEADWAYMINIMUM)
	{
		pOuter->GetDlgItem(IDC_ERR_INVALID_HEADWAYMINIMUM)->GetWindowText(strErrorMsg);
	}
	else if (strErrorReason == ERRMSG_INVALID_HEADWAYRELATION)
	{
		pOuter->GetDlgItem(IDC_ERR_INVALID_HEADWAYRELATION)->GetWindowText(strErrorMsg);
	}
	else if (strErrorReason == ERRMSG_EMPTY_CAPTION)
	{
		pOuter->GetDlgItem(IDC_ERR_EMPTY_CAPTION)->GetWindowText(strErrorMsg);
	}
	//else if (strErrorReason == ERRMSG_LOOP_EKIJIKOKUKEISIKI_HATSUCHAKU_DOWNCHAKU)
	//{
	//	pOuter->GetDlgItem(IDC_ERR_LOOP_EKIJIKOKUKEISIKI_HATSUCHAKU_DOWNCHAKU)->GetWindowText(strErrorMsg);
	//}
	//else if (strErrorReason == ERRMSG_LOOP_EKIKIBO)
	//{
	//	pOuter->GetDlgItem(IDC_ERR_LOOP_EKIKIBO)->GetWindowText(strErrorMsg);
	//}
	//else if (strErrorReason == ERRMSG_EKIMEI_EMPTY)
	//{
	//	pOuter->GetDlgItem(IDC_ERR_EkimeiEmpty)->GetWindowText(strErrorMsg);
	//}
	//else if (strErrorReason == ERRMSG_EKIMEIJIKOKUHYOURYAKU_TOO_LONG)
	//{
	//	//pOuter->GetDlgItem( IDC_ERR_EkimeiNo )->GetWindowText( strErrorMsg )  ;
	//	pOuter->GetDlgItem(IDC_ERR_EkimeiJikokuhyouRyakuTooLong)->GetWindowText(strErrorMsg);
	//}
	//else if (strErrorReason == ERRMSG_EKIMEIDIAGRAMRYAKU_TOO_LONG)
	//{
	//	//pOuter->GetDlgItem( IDC_ERR_EkimeiNo )->GetWindowText( strErrorMsg )  ;
	//	pOuter->GetDlgItem(IDC_ERR_EkimeiDiagramRyakuTooLong)->GetWindowText(strErrorMsg);
	//}
	strErrorMsg += strInfo.c_str();
	pOuter->MessageBox(strErrorMsg, NULL, MB_OK | MB_ICONEXCLAMATION);

}

void CDlgCrossingCheckRule::CPropEditUiInternal::SetFocus( int iOffsetofUiDataMember ) 
{
	CDlgCrossingCheckRule* pOuter = (CDlgCrossingCheckRule*)( (char*)this - offsetof( CDlgCrossingCheckRule , m_PropEditUiInternal ) ) ;
	CWnd* pControl = NULL ;
	
	// IDC_EDIT_CrossingCheckRuleCaption
	{
		if ( iOffsetofUiDataMember == offsetof( CrossingCheckRule , strCaption) )
		{
			pControl = pOuter->GetDlgItem(IDC_EDIT_CrossingCheckRuleCaption) ;
		}
	}
	// IDC_EDIT_CrossingCheckRuleHeadway 
	{
		if ( iOffsetofUiDataMember == offsetof(CrossingCheckRule, iHeadwaySecond) )
		{
			pControl = pOuter->GetDlgItem(IDC_EDIT_CrossingCheckRuleHeadway) ;
		}
	}
	// IDC_EDIT_CrossingCheckRuleHeadwayMinimum
	{
		if (iOffsetofUiDataMember == offsetof(CrossingCheckRule, iHeadwaySecondMinimum))
		{
			pControl = pOuter->GetDlgItem(IDC_EDIT_CrossingCheckRuleHeadwayMinimum);
		}
	}
	// IDC_LIST_BeforeFrom 
	{
		if ( iOffsetofUiDataMember == offsetof(CrossingCheckRule, BeforeFromTrackContentCont) )
		{
			pControl = (CEdit*)pOuter->GetDlgItem(IDC_LIST_BeforeFrom) ;
		}
	}	

	//IDC_LIST_BeforeTo
	{
		if ( iOffsetofUiDataMember == offsetof(CrossingCheckRule, BeforeToTrackContentCont) )
		{
			pControl = (CComboBox*)pOuter->GetDlgItem(IDC_LIST_BeforeTo) ;
		}
	}
	// IDC_LIST_AfterFrom
	{
		if ( iOffsetofUiDataMember == offsetof(CrossingCheckRule, AfterFromTrackContentCont) )
		{
			pControl = (CComboBox*)pOuter->GetDlgItem(IDC_LIST_AfterFrom) ;
		}
	}

	//IDC_LIST_AfterTo
	{
		if ( iOffsetofUiDataMember == offsetof(CrossingCheckRule, AfterToTrackContentCont) )
		{
			pControl = (CButton*)pOuter->GetDlgItem(IDC_LIST_AfterTo) ;
		}
	}

	// --------------------------------
	if ( pControl != NULL )
	{
		pOuter->GotoDlgCtrl( pControl ) ; 
	}
}	

	// ********************************
	//	コンストラクタ
	// ********************************
CDlgCrossingCheckRule::CPropEditUiInternal::CPropEditUiInternal(
	CentDedEki* pTarget ,
	int iEkiIndex)
	: CPropEditUi_CrossingCheckRule(  pTarget ,
		iEkiIndex)
{
}

/////////////////////////////////////////////////////////////////////////////
//// CDlgCrossingCheckRule ダイアログ

	// --------------------------------
	//@name 下請関数
	// --------------------------------


// ********************************
	//@name 属性
	// ********************************
// ----------------------------------------------------------------
//	MFC
// ----------------------------------------------------------------
CDlgCrossingCheckRule::CDlgCrossingCheckRule(
		CentDedEki* pTarget ,
		int iEkiIndex,
		//int iFocusItem ,
		CKeyinputSenderToModalDlg*	pCKeyinputSenderToModalDlg ,
		CWnd* pParent )
	: CDialog(CDlgCrossingCheckRule::IDD, pParent)
	, m_PropEditUiInternal( pTarget ,
		 iEkiIndex)
	//, m_iFocusItem( iFocusItem ) 
	, m_pCKeyinputSenderToModalDlg(	pCKeyinputSenderToModalDlg )
	, m_iEkiIndex(iEkiIndex)
{
	//{{AFX_DATA_INIT(CDlgCrossingCheckRule)
	//m_iRADIO_Jikokukeisiki = -1;
	//m_iRADIO_Ekikibo = -1;
	//m_iEDITNextEkiDistance = 0;

	//}}AFX_DATA_INIT
}


void CDlgCrossingCheckRule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCrossingCheckRule)
	DDX_Radio(pDX, IDC_RADIO_BeforeArrDep, m_iRADIO_BeforeIsArrival);
	DDX_Radio(pDX, IDC_RADIO_BeforeIsTsuuka, m_iRADIO_BeforeIsTsuuka);
	DDX_Radio(pDX, IDC_RADIO_AfterArrDep, m_iRADIO_AfterIsArrival);
	DDX_Radio(pDX, IDC_RADIO_AfterIsTsuuka, m_iRADIO_AfterIsTsuuka);
	//DDX_Text(pDX, IDC_EDIT_CrossingCheckRuleHeadway, m_iEDIT_CrossingCheckRuleHeadway);
	//DDV_MinMaxInt(pDX, m_iEDIT_CrossingCheckRuleHeadway, 1, 7200);//add_by_d_mania
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCrossingCheckRule, CDialog)
	//{{AFX_MSG_MAP(CDlgCrossingCheckRule)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
	ON_LBN_SELCHANGE(IDC_LIST_CrossingCheckRule, &CDlgCrossingCheckRule::OnLbnSelchangeListCrossingCheckRule)
	ON_BN_CLICKED(IDC_BUTTON_CrossingCheckRuleAdd, &CDlgCrossingCheckRule::OnBnClickedButtonListCrossingCheckadd)
	ON_BN_CLICKED(IDC_BUTTON_CrossingCheckRuleCopy, &CDlgCrossingCheckRule::OnBnClickedButtonListCrossingCheckcopy)
	ON_BN_CLICKED(IDC_BUTTON_CrossingCheckRuleClear, &CDlgCrossingCheckRule::OnBnClickedButtonListCrossingCheckclear)
	ON_BN_CLICKED(IDC_BUTTON_CrossingCheckRuleUp, &CDlgCrossingCheckRule::OnBnClickedButtonListCrossingCheckup)
	ON_BN_CLICKED(IDC_BUTTON_CrossingCheckRuleDown, &CDlgCrossingCheckRule::OnBnClickedButtonListCrossingCheckdown)

	ON_EN_KILLFOCUS(IDC_EDIT_CrossingCheckRuleCaption, &CDlgCrossingCheckRule::OnEnKillfocusEditCrossingCheckRuleCaption)
	ON_EN_KILLFOCUS(IDC_EDIT_CrossingCheckRuleHeadway, &CDlgCrossingCheckRule::OnEnKillfocusEditCrossingCheckRuleHeadway)
	ON_EN_KILLFOCUS(IDC_EDIT_CrossingCheckRuleHeadwayMinimum, &CDlgCrossingCheckRule::OnEnKillfocusEditCrossingCheckRuleHeadwayMinimum)
	ON_BN_CLICKED(IDC_CHECK_Enable, &CDlgCrossingCheckRule::OnBnClickedCheckEnable)

	ON_BN_CLICKED(IDC_RADIO_BeforeArrDep, &CDlgCrossingCheckRule::OnBnClickedRadioBeforeArrDep)
	ON_BN_CLICKED(IDC_RADIO_BeforeArrDep2, &CDlgCrossingCheckRule::OnBnClickedRadioBeforeArrDep2)
	ON_BN_CLICKED(IDC_RADIO_BeforeIsTsuuka, &CDlgCrossingCheckRule::OnBnClickedRadioBeforeIsTsuuka)
	ON_BN_CLICKED(IDC_RADIO_BeforeIsTsuuka2, &CDlgCrossingCheckRule::OnBnClickedRadioBeforeIsTsuuka2)

	ON_LBN_SELCHANGE(IDC_LIST_BeforeFrom, &CDlgCrossingCheckRule::OnLbnSelchangeListBeforeFrom)
	ON_LBN_SELCHANGE(IDC_LIST_BeforeTo, &CDlgCrossingCheckRule::OnLbnSelchangeListBeforeTo)

	ON_BN_CLICKED(IDC_RADIO_AfterArrDep, &CDlgCrossingCheckRule::OnBnClickedRadioAfterArrDep)
	ON_BN_CLICKED(IDC_RADIO_AfterArrDep2, &CDlgCrossingCheckRule::OnBnClickedRadioAfterArrDep2)
	ON_BN_CLICKED(IDC_RADIO_AfterIsTsuuka, &CDlgCrossingCheckRule::OnBnClickedRadioAfterIsTsuuka)
	ON_BN_CLICKED(IDC_RADIO_AfterIsTsuuka2, &CDlgCrossingCheckRule::OnBnClickedRadioAfterIsTsuuka2)

	ON_LBN_SELCHANGE(IDC_LIST_AfterFrom, &CDlgCrossingCheckRule::OnLbnSelchangeListAfterFrom)
	ON_LBN_SELCHANGE(IDC_LIST_AfterTo, &CDlgCrossingCheckRule::OnLbnSelchangeListAfterTo)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCrossingCheckRule メッセージ ハンドラ

BOOL CDlgCrossingCheckRule::OnInitDialog() 
{
	CDialog::OnInitDialog();

	{
		const CentDedRosen* pCentDedRosen = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen();
		const CentDedEkiCont* pCentDedEkiCont =
			pCentDedRosen->getCentDedEkiCont();

		m_MapTrackContentToList.clear();
		m_MapListToTrackContent.clear();
		int iListIndex = 0;

		CListBox* pListBoxBF = (CListBox*)GetDlgItem(IDC_LIST_BeforeFrom);
		pListBoxBF->ResetContent();
		CListBox* pListBoxBT = (CListBox*)GetDlgItem(IDC_LIST_BeforeTo);
		pListBoxBT->ResetContent();
		CListBox* pListBoxAF = (CListBox*)GetDlgItem(IDC_LIST_AfterFrom);
		pListBoxAF->ResetContent();
		CListBox* pListBoxAT = (CListBox*)GetDlgItem(IDC_LIST_AfterTo);
		pListBoxAT->ResetContent();

		//Track
		const CentDedEkiTrack2Cont* pCentDedEkiTrack2Cont = pCentDedEkiCont->getMuPtr()->get(m_iEkiIndex)->getEkiTrack2Cont();
		vector<int> MapTrackContentToList0;
		for (int iEkiTrack2Index = 0; iEkiTrack2Index < pCentDedEkiTrack2Cont->size(); iEkiTrack2Index++)
		{
			MapTrackContentToList0.push_back(iListIndex);
			m_MapListToTrackContent[iListIndex] = TrackContent(ETrackType::TrackType_Track, iEkiTrack2Index);
			tstring strTemp = pCentDedEkiTrack2Cont->get(iEkiTrack2Index).getTrackName();
			pListBoxBF->AddString(strTemp.c_str());
			pListBoxBT->AddString(strTemp.c_str());
			pListBoxAF->AddString(strTemp.c_str());
			pListBoxAT->AddString(strTemp.c_str());
			iListIndex++;
		}
		m_MapTrackContentToList.push_back(MapTrackContentToList0);

		deque<int> iEkiIndexBranchLoop;
		pCentDedEkiCont->getEkiIndexBrunchLoop(m_iEkiIndex, iEkiIndexBranchLoop);
		sort(iEkiIndexBranchLoop.begin(), iEkiIndexBranchLoop.end());

		//MapTrackContentToListの内、当駅と関係ない駅の部分を埋めるために用います。
		//int iPrevPushBack = 0;
		vector<int> MapTrackContentToList1;
		vector<int> MapTrackContentToList2;
		MapTrackContentToList1.assign(pCentDedEkiCont->size(), -1);
		MapTrackContentToList2.assign(pCentDedEkiCont->size(), -1);
		for (int idx = 0; idx < (int)iEkiIndexBranchLoop.size(); idx++)
		{
			const CentDedEki* pCentDedEki = pCentDedEkiCont->getMuPtr()->get(iEkiIndexBranchLoop[idx]);
			if (iEkiIndexBranchLoop[idx] > 0 && pCentDedEki->getEkijikokukeisiki() != CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku)
			{
				MapTrackContentToList1[iEkiIndexBranchLoop[idx]] = iListIndex;
				m_MapListToTrackContent[iListIndex] = TrackContent(ETrackType::TrackType_Origin, iEkiIndexBranchLoop[idx]);

				/**
					Listboxに表示するための文字列を求める。
					〜〜方面(起点側)の、〜〜に入る駅は、この駅から遡って一番近い主要駅を用います。ただし、iEkiIndexBranchLoop[idx - 1]よりも後ろ(含む)は除きます
					主要駅が見つからない場合は、直前の駅を用います
				*/
				int iEkiIndexLoopPrev = -1;
				if (idx > 0)
				{
					iEkiIndexLoopPrev = iEkiIndexBranchLoop[idx - 1];
				}
				tstring strTemp;
				for (int iPrevEkiIndex = iEkiIndexBranchLoop[idx] - 1; iPrevEkiIndex > iEkiIndexLoopPrev; iPrevEkiIndex--)
				{
					const CentDedEki* pCentDedEkiPrev = pCentDedEkiCont->getMuPtr()->get(iPrevEkiIndex);
					if (pCentDedEkiPrev->getEkikibo() == CentDedEki::EEkikibo::Ekikibo_Syuyou)
					{
						strTemp = pCentDedEkiPrev->getEkimei();
						break;
					}
				}
				if (strTemp.empty())
				{
					const CentDedEki* pCentDedEkiPrev = pCentDedEkiCont->getMuPtr()->get(iEkiIndexBranchLoop[idx] - 1);
					strTemp = pCentDedEkiPrev->getEkimei();
				}
				strTemp += _T("方面(起点側)");
				pListBoxBF->AddString(strTemp.c_str());
				pListBoxBT->AddString(strTemp.c_str());
				pListBoxAF->AddString(strTemp.c_str());
				pListBoxAT->AddString(strTemp.c_str());
				iListIndex++;
			}

			if (iEkiIndexBranchLoop[idx] < pCentDedEkiCont->size() - 1 &&
				pCentDedEki->getEkijikokukeisiki() != CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku)
			{
				MapTrackContentToList2[iEkiIndexBranchLoop[idx]] = iListIndex;
				m_MapListToTrackContent[iListIndex] = TrackContent(ETrackType::TrackType_Terminal, iEkiIndexBranchLoop[idx]);

				/**
					Listboxに表示するための文字列を求める。
					〜〜方面(起点側)の、〜〜に入る駅は、この駅から遡って一番近い主要駅を用います。ただし、iEkiIndexBranchLoop[idx - 1]よりも後ろ(含む)は除きます
					主要駅が見つからない場合は、直前の駅を用います
				*/
				int iEkiIndexLoopNext = pCentDedEkiCont->size();
				if (idx < (int)iEkiIndexBranchLoop.size()-1)
				{
					iEkiIndexLoopNext = iEkiIndexBranchLoop[idx + 1];
				}
				tstring strTemp;
				for (int iNextEkiIndex = iEkiIndexBranchLoop[idx] + 1; iNextEkiIndex < iEkiIndexLoopNext; iNextEkiIndex++)
				{
					const CentDedEki* pCentDedEkiNext = pCentDedEkiCont->getMuPtr()->get(iNextEkiIndex);
					if (pCentDedEkiNext->getEkikibo() == CentDedEki::EEkikibo::Ekikibo_Syuyou)
					{
						strTemp = pCentDedEkiNext->getEkimei();
						break;
					}
				}
				if (strTemp.empty())
				{
					const CentDedEki* pCentDedEkiNext = pCentDedEkiCont->getMuPtr()->get(iEkiIndexBranchLoop[idx] + 1);
					strTemp = pCentDedEkiNext->getEkimei();
				}
				strTemp += _T("方面(終点側)");
				pListBoxBF->AddString(strTemp.c_str());
				pListBoxBT->AddString(strTemp.c_str());
				pListBoxAF->AddString(strTemp.c_str());
				pListBoxAT->AddString(strTemp.c_str());
				iListIndex++;

			}
		}
		m_MapTrackContentToList.push_back(MapTrackContentToList1);
		m_MapTrackContentToList.push_back(MapTrackContentToList2);

		//路線外終着駅
		const vector<OuterTerminal> OuterTerminalCont = pCentDedEkiCont->get(m_iEkiIndex).getOuterTerminalEkimeiCont();
		vector<int> MapTrackContentToList3;
		for (int iOuterTerminalIndex = 0; iOuterTerminalIndex < (int)OuterTerminalCont.size(); iOuterTerminalIndex++)
		{
			MapTrackContentToList3.push_back(iListIndex);
			m_MapListToTrackContent[iListIndex] = TrackContent(ETrackType::TrackType_Outer, iOuterTerminalIndex);
			tstring strTemp = OuterTerminalCont[iOuterTerminalIndex].OuterTerminalEkimei;
			strTemp += _T("方面(路線外)");
			pListBoxBF->AddString(strTemp.c_str());
			pListBoxBT->AddString(strTemp.c_str());
			pListBoxAF->AddString(strTemp.c_str());
			pListBoxAT->AddString(strTemp.c_str());
			iListIndex++;
		}
		m_MapTrackContentToList.push_back(MapTrackContentToList3);

		//番線リストの数に合わせて、ダイアログのサイズを変えます
		//変更するのは、リストボックス(4つ)、OK・キャンセルボタン(位置のみ)、枠、ダイアログ全体
		{
			const int yExpand = 15 * (min(40, pListBoxBF->GetCount() - 1));
			RECT RECTDialog{};
			this->GetWindowRect((LPRECT)&RECTDialog);
			this->MoveWindow(RECTDialog.left, RECTDialog.top, RECTDialog.right - RECTDialog.left, RECTDialog.bottom - RECTDialog.top + yExpand);
			const int xOffset = RECTDialog.left + 8;
			const int yOffset = RECTDialog.top + 31;

			RECT RECTListBF{};
			pListBoxBF->GetWindowRect((LPRECT)&RECTListBF);
			pListBoxBF->MoveWindow(RECTListBF.left - xOffset, RECTListBF.top - yOffset,
				RECTListBF.right - RECTListBF.left, RECTListBF.bottom - RECTListBF.top + yExpand);
			RECT RECTListBT{};
			pListBoxBT->GetWindowRect((LPRECT)&RECTListBT);
			pListBoxBT->MoveWindow(RECTListBT.left - xOffset, RECTListBT.top - yOffset,
				RECTListBT.right - RECTListBT.left, RECTListBT.bottom - RECTListBT.top + yExpand);
			RECT RECTListAF{};
			pListBoxAF->GetWindowRect((LPRECT)&RECTListAF);
			pListBoxAF->MoveWindow(RECTListAF.left - xOffset, RECTListAF.top - yOffset,
				RECTListAF.right - RECTListAF.left, RECTListAF.bottom - RECTListAF.top + yExpand);
			RECT RECTListAT{};
			pListBoxAT->GetWindowRect((LPRECT)&RECTListAT);
			pListBoxAT->MoveWindow(RECTListAT.left - xOffset, RECTListAT.top - yOffset,
				RECTListAT.right - RECTListAT.left, RECTListAT.bottom - RECTListAT.top + yExpand);

			CWnd* pFrameB = (CWnd*)GetDlgItem(IDC_STATIC_BeforeFrame);
			RECT RECTFrameB{};
			pFrameB->GetWindowRect((LPRECT)&RECTFrameB);
			pFrameB->MoveWindow(RECTFrameB.left - xOffset, RECTFrameB.top - yOffset,
				RECTFrameB.right - RECTFrameB.left, RECTFrameB.bottom - RECTFrameB.top + yExpand);
			CWnd* pFrameA = (CWnd*)GetDlgItem(IDC_STATIC_AfterFrame);
			RECT RECTFrameA{};
			pFrameA->GetWindowRect((LPRECT)&RECTFrameA);
			pFrameA->MoveWindow(RECTFrameA.left - xOffset, RECTFrameA.top - yOffset,
				RECTFrameA.right - RECTFrameA.left, RECTFrameA.bottom - RECTFrameA.top + yExpand);

			CWnd* pOKButton = (CWnd*)GetDlgItem(IDOK);
			RECT RECTOKButton{};
			pOKButton->GetWindowRect((LPRECT)&RECTOKButton);
			pOKButton->MoveWindow(RECTOKButton.left - xOffset, RECTOKButton.top - yOffset + yExpand,
				RECTOKButton.right - RECTOKButton.left, RECTOKButton.bottom - RECTOKButton.top);
			CWnd* pCancelButton = (CWnd*)GetDlgItem(IDCANCEL);
			RECT RECTCancelButton{};
			pCancelButton->GetWindowRect((LPRECT)&RECTCancelButton);
			pCancelButton->MoveWindow(RECTCancelButton.left - xOffset, RECTCancelButton.top - yOffset + yExpand,
				RECTCancelButton.right - RECTCancelButton.left, RECTCancelButton.bottom - RECTCancelButton.top);
		}
	}

	//	編集を開始
	m_PropEditUiInternal.StartEdit() ;
	
	// --------------------------------
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CDlgCrossingCheckRule::OnOK() 
{
	int iResult = m_PropEditUiInternal.EndEdit() ;
	if ( iResult >= 0 )
	{
		CDialog::OnOK();
	}

}

void CDlgCrossingCheckRule::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	//
	//
	//if ( bShow )
	//{
	//	// --------------------------------
	//	//	フォーカスを移動
	//	// --------------------------------
	//	//駅名
	//	if ( m_iFocusItem == 0 ){
	//		CEdit*	pControl = (CEdit*)GetDlgItem( IDC_EDIT_Ekimei );
	//		GotoDlgCtrl( pControl ) ;
	//		if ( m_pCKeyinputSenderToModalDlg != NULL ){
	//			m_pCKeyinputSenderToModalDlg->registerCtrl( pControl->GetSafeHwnd() ) ;
	//		}
	//	}
	//	//駅時刻形式
	//	if ( m_iFocusItem == 1 ){
	//		CWnd*	pControl = GetDlgItem( IDC_RADIO_Jikokukeisiki );
	//		GotoDlgCtrl( pControl ) ;
	//		if ( m_pCKeyinputSenderToModalDlg != NULL ){
	//			m_pCKeyinputSenderToModalDlg->registerCtrl( pControl->GetSafeHwnd() ) ;
	//		}
	//	}
	//	//駅規模
	//	if ( m_iFocusItem == 2 ){
	//		CWnd*	pControl = GetDlgItem( IDC_RADIO_Ekikibo );
	//		GotoDlgCtrl( pControl ) ;
	//		if ( m_pCKeyinputSenderToModalDlg != NULL ){
	//			m_pCKeyinputSenderToModalDlg->registerCtrl( pControl->GetSafeHwnd() ) ;
	//		}
	//	}
	//	//駅規模
	//	if (m_iFocusItem == 3) {
	//		CWnd*	pControl = GetDlgItem(IDC_CHECK_Brunch);
	//		GotoDlgCtrl(pControl);
	//		if (m_pCKeyinputSenderToModalDlg != NULL) {
	//			m_pCKeyinputSenderToModalDlg->registerCtrl(pControl->GetSafeHwnd());
	//		}
	//	}
	//	//駅規模
	//	if (m_iFocusItem == 4) {
	//		CWnd*	pControl = GetDlgItem(IDC_CHECK_Loop);
	//		GotoDlgCtrl(pControl);
	//		if (m_pCKeyinputSenderToModalDlg != NULL) {
	//			m_pCKeyinputSenderToModalDlg->registerCtrl(pControl->GetSafeHwnd());
	//		}
	//	}
	//	
	//	m_iFocusItem = -1 ;
	//}	
	
}

void CDlgCrossingCheckRule::OnEnKillfocusEditCrossingCheckRuleCaption()
{
	m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
	m_PropEditUiInternal.OnUiChanged();
}

void CDlgCrossingCheckRule::OnEnKillfocusEditCrossingCheckRuleHeadway()
{
	m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
	m_PropEditUiInternal.OnUiChanged();
}

void CDlgCrossingCheckRule::OnEnKillfocusEditCrossingCheckRuleHeadwayMinimum()
{
	m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
	m_PropEditUiInternal.OnUiChanged();
}
void CDlgCrossingCheckRule::OnBnClickedCheckEnable()
{
	m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
	m_PropEditUiInternal.OnUiChanged();
}

void CDlgCrossingCheckRule::OnBnClickedRadioBeforeArrDep()
{
	m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
	m_PropEditUiInternal.OnUiChanged();
}

void CDlgCrossingCheckRule::OnBnClickedRadioBeforeArrDep2()
{
	m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
	m_PropEditUiInternal.OnUiChanged();
}

void CDlgCrossingCheckRule::OnBnClickedRadioBeforeIsTsuuka()
{
	m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
	m_PropEditUiInternal.OnUiChanged();
}

void CDlgCrossingCheckRule::OnBnClickedRadioBeforeIsTsuuka2()
{
	m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
	m_PropEditUiInternal.OnUiChanged();
}

void CDlgCrossingCheckRule::OnLbnSelchangeListBeforeFrom()
{
	m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
	m_PropEditUiInternal.OnUiChanged();
}

void CDlgCrossingCheckRule::OnLbnSelchangeListBeforeTo()
{
	m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
	m_PropEditUiInternal.OnUiChanged();
}

void CDlgCrossingCheckRule::OnBnClickedRadioAfterArrDep()
{
	m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
	m_PropEditUiInternal.OnUiChanged();
}

void CDlgCrossingCheckRule::OnBnClickedRadioAfterArrDep2()
{
	m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
	m_PropEditUiInternal.OnUiChanged();
}

void CDlgCrossingCheckRule::OnBnClickedRadioAfterIsTsuuka()
{
	m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
	m_PropEditUiInternal.OnUiChanged();
}

void CDlgCrossingCheckRule::OnBnClickedRadioAfterIsTsuuka2()
{
	m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
	m_PropEditUiInternal.OnUiChanged();
}

void CDlgCrossingCheckRule::OnLbnSelchangeListAfterFrom()
{
	m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
	m_PropEditUiInternal.OnUiChanged();
}

void CDlgCrossingCheckRule::OnLbnSelchangeListAfterTo()
{
	m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
	m_PropEditUiInternal.OnUiChanged();
}

void ViewEki::CDlgCrossingCheckRule::OnLbnSelchangeListCrossingCheckRule()
{
	CListBox* pListBox = (CListBox*)GetDlgItem(IDC_LIST_CrossingCheckRule);
	m_PropEditUiInternal.GetUiData()->iListSelected = pListBox->GetCurSel();
	m_PropEditUiInternal.GetUiData()->iUiOperation = 1;
	m_PropEditUiInternal.OnUiDataChanged();
}

void ViewEki::CDlgCrossingCheckRule::OnBnClickedButtonListCrossingCheckadd()
{
	//UiDataに外からアクセスし、直接作業を追加します。
	CrossingCheckRule CrossingCheckRuleTemp;
	CrossingCheckRuleTemp.strCaption = _T("ルール") + to_tstring(m_PropEditUiInternal.GetUiData()->ContCrossingCheckRule.size() + 1);
	m_PropEditUiInternal.GetUiData()->ContCrossingCheckRule.push_back(CrossingCheckRuleTemp);
	m_PropEditUiInternal.GetUiData()->iListSelected = m_PropEditUiInternal.GetUiData()->ContCrossingCheckRule.size() - 1;
	//CListBox* pListBox = (CListBox*)GetDlgItem(IDC_LIST_CrossingCheckRule);
	//pListBox->SetCurSel(m_PropEditUiInternal.GetUiData()->ContCrossingCheckRule.size() - 1);
	m_PropEditUiInternal.GetUiData()->iUiOperation = 2;
	m_PropEditUiInternal.OnUiDataChanged();
}

void ViewEki::CDlgCrossingCheckRule::OnBnClickedButtonListCrossingCheckcopy()
{
	//UiDataに外からアクセスし、直接作業を追加します。
	int iListSelected = m_PropEditUiInternal.GetUiData()->iListSelected;
	if (iListSelected >= 0)
	{
		CrossingCheckRule CrossingCheckRuleTemp =
			m_PropEditUiInternal.GetUiData()->ContCrossingCheckRule[iListSelected];
		//m_PropEditUiInternal.GetUiData()->ContCrossingCheckRule.push_back(CrossingCheckRuleTemp);
		m_PropEditUiInternal.GetUiData()->ContCrossingCheckRule.insert(m_PropEditUiInternal.GetUiData()->ContCrossingCheckRule.begin()+ iListSelected,CrossingCheckRuleTemp);
		//m_PropEditUiInternal.GetUiData()->iListSelected = m_PropEditUiInternal.GetUiData()->ContCrossingCheckRule.size() - 1;
		m_PropEditUiInternal.GetUiData()->iListSelected++;
		//CListBox* pListBox = (CListBox*)GetDlgItem(IDC_LIST_CrossingCheckRule);
		//pListBox->SetCurSel(m_PropEditUiInternal.GetUiData()->ContCrossingCheckRule.size() - 1);
		m_PropEditUiInternal.GetUiData()->iUiOperation = 2;
	}
	m_PropEditUiInternal.OnUiDataChanged();
}

void ViewEki::CDlgCrossingCheckRule::OnBnClickedButtonListCrossingCheckclear()
{
	//UiDataに外からアクセスし、直接作業を削除します。
	int iListSelected = m_PropEditUiInternal.GetUiData()->iListSelected;
	if (iListSelected >= 0)
	{
		m_PropEditUiInternal.GetUiData()->ContCrossingCheckRule.erase(
			m_PropEditUiInternal.GetUiData()->ContCrossingCheckRule.begin()+ iListSelected);
		if ((int)m_PropEditUiInternal.GetUiData()->ContCrossingCheckRule.size() <= iListSelected)
		{
			m_PropEditUiInternal.GetUiData()->iListSelected = m_PropEditUiInternal.GetUiData()->ContCrossingCheckRule.size() - 1;
		}
		//CListBox* pListBox = (CListBox*)GetDlgItem(IDC_LIST_CrossingCheckRule);
		//pListBox->SetCurSel(m_PropEditUiInternal.GetUiData()->ContCrossingCheckRule.size() - 1);
		m_PropEditUiInternal.GetUiData()->iUiOperation = 3;
	}
	m_PropEditUiInternal.OnUiDataChanged();


}

void ViewEki::CDlgCrossingCheckRule::OnBnClickedButtonListCrossingCheckup()
{
	//UiDataに外からアクセスし、直接ルールを入れ替えます。
	int iListSelected = m_PropEditUiInternal.GetUiData()->iListSelected;
	if (iListSelected > 0)
	{
		CrossingCheckRule Temp = m_PropEditUiInternal.GetUiData()->ContCrossingCheckRule[iListSelected];
		m_PropEditUiInternal.GetUiData()->ContCrossingCheckRule.insert(
			m_PropEditUiInternal.GetUiData()->ContCrossingCheckRule.begin() + iListSelected - 1, Temp);
		m_PropEditUiInternal.GetUiData()->ContCrossingCheckRule.erase(
			m_PropEditUiInternal.GetUiData()->ContCrossingCheckRule.begin() + iListSelected + 1);
		m_PropEditUiInternal.GetUiData()->iListSelected = iListSelected - 1;
		m_PropEditUiInternal.GetUiData()->iUiOperation = 1;
	}
	m_PropEditUiInternal.OnUiDataChanged();
}


void ViewEki::CDlgCrossingCheckRule::OnBnClickedButtonListCrossingCheckdown()
{
	//UiDataに外からアクセスし、直接ルールを入れ替えます。
	int iListSelected = m_PropEditUiInternal.GetUiData()->iListSelected;
	if (iListSelected >= 0 && iListSelected < (int)m_PropEditUiInternal.GetUiData()->ContCrossingCheckRule.size() - 1)
	{
		CrossingCheckRule Temp = m_PropEditUiInternal.GetUiData()->ContCrossingCheckRule[iListSelected];
		m_PropEditUiInternal.GetUiData()->ContCrossingCheckRule.insert(
			m_PropEditUiInternal.GetUiData()->ContCrossingCheckRule.begin() + iListSelected + 2, Temp);
		m_PropEditUiInternal.GetUiData()->ContCrossingCheckRule.erase(
			m_PropEditUiInternal.GetUiData()->ContCrossingCheckRule.begin() + iListSelected);
		m_PropEditUiInternal.GetUiData()->iListSelected = iListSelected + 1;
		m_PropEditUiInternal.GetUiData()->iUiOperation = 1;
	}
	m_PropEditUiInternal.OnUiDataChanged();
}



} //namespace ViewEki

