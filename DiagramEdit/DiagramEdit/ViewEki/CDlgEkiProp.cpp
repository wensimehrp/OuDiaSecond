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
// CDlgEkiProp.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"

#include "..¥DiagramEdit.h"
#include "CDlgEkiProp.h"
#include "str/stringSplit.h"
#include "..¥ViewEki¥CDlgEkiTrack2Prop2.h"
#include "..¥ViewEki¥CDlgOuterEkimeiProp.h"
//#include "..¥DedRosenFileData¥EditCmd¥EditCmd.h"
#include "Str¥strToWstr.h"
#include "MfcUtil¥MfcUtil.h"
#include "..¥resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


namespace ViewEki {

	const TCHAR nameDiagramTrackOmit[] = _T("省略");

	// ================================================================
	//	CDlgEkiProp::CPropEditUiInternal
	// ================================================================
		// ================================
		//@name CPropEditUi - UiData - UiControl 間のデータ転送
		// ================================
	void CDlgEkiProp::CPropEditUiInternal::UiDataToUi(const UIDATA* pUiData)
	{
		CDlgEkiProp* pOuter = (CDlgEkiProp*)((char*)this - offsetof(CDlgEkiProp, m_PropEditUiInternal));

		// --------------------------------
		//	DDXを用いた、UiControlへの設定
		// --------------------------------
		{
			// 駅時刻形式
			{
				pOuter->m_iRADIO_Jikokukeisiki = pUiData->iEkijikokukeisiki;
			}
			// 駅規模 
			{
				pOuter->m_iRADIO_Ekikibo = pUiData->iEkikibo;
			}
			// 次駅までの距離 
			{
				pOuter->m_iEDITNextEkiDistance = pUiData->iNextEkiDistance;
			}
			// --------------------------------
			pOuter->UpdateData(FALSE);
		}
		// --------------------------------
		//	DDXを用いない、UiControlへの設定
		//	これらは、DDXによる値設定の後で
		//	行わなくてはなりません。
		// --------------------------------
		// 駅名 
		{
			CEdit* pEdit = (CEdit*)pOuter->GetDlgItem(IDC_EDIT_Ekimei);
			pEdit->SetWindowText(pUiData->strEkimei.c_str());
			pEdit->SetSel(0, -1);
		}

		//ダイヤグラム列車情報表示（下り）
		{
			CComboBox* pComboBox = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_DiagramRessyajouhouHyoujiKudari);
			pComboBox->SetCurSel(pUiData->iDiagramRessyajouhouHyoujiKudari);
		}
		// ダイヤグラム列車情報表示（上り） 
		{
			CComboBox* pComboBox = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_DiagramRessyajouhouHyoujiNobori);
			pComboBox->SetCurSel(pUiData->iDiagramRessyajouhouHyoujiNobori);
		}

		//[駅時刻を駅時刻形式で正規化]の設定です。
		{
			CButton* pButton = (CButton*)pOuter->GetDlgItem(IDC_CHECK_AdjustByEkijikokukeisiki);
			int nCheck = (pUiData->bAdjustByEkijikokukeisiki ? BST_CHECKED : BST_UNCHECKED);
			pButton->SetCheck(nCheck);
		}

		//分岐駅設定
		{
			CButton* pButton = (CButton*)pOuter->GetDlgItem(IDC_CHECK_Brunch);
			CComboBox* pComboBox = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_BrunchCoreEkiIndex);
			CStatic* pStatic = (CStatic*)pOuter->GetDlgItem(IDC_STATIC_BRUNCH);
			CButton* pButtonO = (CButton*)pOuter->GetDlgItem(IDC_CHECK_BrunchLoopOpposite);


			if (pUiData->bBrunchFunctionEnable)
			{
				pButton->EnableWindow(true);
				pStatic->EnableWindow(true);
				if (pUiData->bBrunch)
				{
					tstring strIdx = stringOf(pUiData->iBrunchCoreEkiIndex) + _T(".");
					int isel = pComboBox->FindString(0, strIdx.c_str());
					pButton->SetCheck(BST_CHECKED);
					pComboBox->EnableWindow(true);
					if (isel == -1)
					{
						pComboBox->SetCurSel(0);

					}
					else
					{
						pComboBox->SetCurSel(isel);
					}

					pButtonO->EnableWindow(true);
					int nCheck = (pUiData->bBrunchOpposite ? BST_CHECKED : BST_UNCHECKED);
					pButtonO->SetCheck(nCheck);
				}
				else
				{
					pButton->SetCheck(BST_UNCHECKED);
					pComboBox->EnableWindow(false);
					//pComboBox->SetCurSel(0);
					pStatic->EnableWindow(false);
					pButtonO->EnableWindow(false);
				}
			}
			else
			{
				pButton->EnableWindow(false);
				pComboBox->EnableWindow(false);
				//pComboBox->SetCurSel(-1);
				pStatic->EnableWindow(false);
			}
		}
		//環状線設定
		{
			CButton* pButton = (CButton*)pOuter->GetDlgItem(IDC_CHECK_Loop);
			CComboBox* pComboBox = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_LoopOriginEkiIndex);
			CStatic* pStatic = (CStatic*)pOuter->GetDlgItem(IDC_STATIC_LOOP);
			CButton* pButtonO = (CButton*)pOuter->GetDlgItem(IDC_CHECK_BrunchLoopOpposite);


			if (pUiData->bLoopFunctionEnable)
			{
				pButton->EnableWindow(true);
				pStatic->EnableWindow(true);

				if (pUiData->bLoop)
				{
					tstring strIdx = stringOf(pUiData->iLoopOriginEkiIndex) + _T(".");
					int isel = pComboBox->FindString(0, strIdx.c_str());
					pButton->SetCheck(BST_CHECKED);
					pComboBox->EnableWindow(true);
					if (isel == -1)
					{
						pComboBox->SetCurSel(0);

					}
					else
					{
						pComboBox->SetCurSel(isel);
					}

					pButtonO->EnableWindow(true);
					int nCheck = (pUiData->bLoopOpposite ? BST_CHECKED : BST_UNCHECKED);
					pButtonO->SetCheck(nCheck);
				}
				else
				{
					pButton->SetCheck(BST_UNCHECKED);
					pComboBox->EnableWindow(false);
					//pComboBox->SetCurSel(0);
					pStatic->EnableWindow(false);
					pButtonO->EnableWindow(false);
				}
			}
			else
			{
				pButton->EnableWindow(false);
				pComboBox->EnableWindow(false);
				//pComboBox->SetCurSel(-1);
				pStatic->EnableWindow(false);
			}
		}
		if (!pUiData->bBrunchFunctionEnable &&
			!pUiData->bLoopFunctionEnable)
		{
			CButton* pButtonO = (CButton*)pOuter->GetDlgItem(IDC_CHECK_BrunchLoopOpposite);
			pButtonO->EnableWindow(false);
		}
		//下り時刻表ビュー番線表示
		{
			CButton* pButton = (CButton*)pOuter->GetDlgItem(IDC_CHECK_JikokuhyouTrackDisplayKudari);
			int nCheck = BST_INDETERMINATE;
			switch (pUiData->iJikokuhyouTrackDisplayKudari)
			{
			case 1: // 番線表示あり
				nCheck = BST_CHECKED;
				break;
			case 0: //なし
				nCheck = BST_UNCHECKED;
				break;
			}
			pButton->SetCheck(nCheck);
			pButton->EnableWindow(pUiData->bJikokuhyouTrackDisplayKudariEnable);
		}
		//上り時刻表ビュー番線表示
		{
			CButton* pButton = (CButton*)pOuter->GetDlgItem(IDC_CHECK_JikokuhyouTrackDisplayNobori);
			int nCheck = BST_INDETERMINATE;
			switch (pUiData->iJikokuhyouTrackDisplayNobori)
			{
			case 1: // 番線表示あり
				nCheck = BST_CHECKED;
				break;
			case 0: //なし
				nCheck = BST_UNCHECKED;
				break;
			}
			pButton->SetCheck(nCheck);
			pButton->EnableWindow(pUiData->bJikokuhyouTrackDisplayNoboriEnable);
		}
		//ダイヤグラムビュー番線表示
		{
			CButton* pButton = (CButton*)pOuter->GetDlgItem(IDC_CHECK_DiagramTrackDisplay);
			int nCheck = BST_INDETERMINATE;
			switch (pUiData->iDiagramTrackDisplay)
			{
			case 1: // 番線表示あり
				nCheck = BST_CHECKED;
				break;
			case 0: //なし
				nCheck = BST_UNCHECKED;
				break;
			}
			pButton->SetCheck(nCheck);
			pButton->EnableWindow(pUiData->bDiagramTrackDisplayEnable);
		}
		// 駅名略称
		{
			CEdit* pEdit = (CEdit*)pOuter->GetDlgItem(IDC_EDIT_EkimeiJikokuhyouRyaku);
			pEdit->SetWindowText(pUiData->strEkimeiJikokuhyouRyaku.c_str());
			pEdit->SetSel(0, -1);
		}
		// 駅名略称(運用一覧)
		{
			CEdit* pEdit = (CEdit*)pOuter->GetDlgItem(IDC_EDIT_EkimeiDiagramRyaku);
			pEdit->SetWindowText(pUiData->strEkimeiDiagramRyaku.c_str());
			pEdit->SetSel(0, -1);
		}
		//EkiTrack2
		{
			CListCtrl* pListCtrl = (CListCtrl*)pOuter->GetDlgItem(IDC_LIST_EkiTrack2);
			int iSelectColumn = pListCtrl->GetNextItem(-1, LVNI_SELECTED | LVNI_ALL);
			//pListCtrl->DeleteAllItems();

			for (int idx = 0; idx < (int)pUiData->sEkiTrack2.size(); idx++)
			{
				if (idx < pListCtrl->GetItemCount())
				{
					pListCtrl->SetItemText(idx, 0, pUiData->sEkiTrack2[idx].strTrackName.c_str());
					pListCtrl->SetItemText(idx, 1, pUiData->sEkiTrack2[idx].strTrackRyakusyou.c_str());
					pListCtrl->SetItemText(idx, 2, pUiData->sEkiTrack2[idx].strTrackNoboriRyakusyou.c_str());

					if (pUiData->sEkiTrack2[idx].iMainTrack == 0)
					{
						pListCtrl->SetItemText(idx, 3, (LPCTSTR)MfcUtil::LoadCString(IDS_WORD_SubMain));
						//pListCtrl->SetItemText(idx, 3, _T("副本線/側線"));
					}
					else if (pUiData->sEkiTrack2[idx].iMainTrack == 1)
					{
						pListCtrl->SetItemText(idx, 3, (LPCTSTR)MfcUtil::LoadCString(IDS_WORD_DownMain));
						//pListCtrl->SetItemText(idx, 3, _T("下り主本線"));
					}
					else if (pUiData->sEkiTrack2[idx].iMainTrack == 2)
					{
						pListCtrl->SetItemText(idx, 3, (LPCTSTR)MfcUtil::LoadCString(IDS_WORD_UpMain));
						//pListCtrl->SetItemText(idx, 3, _T("上り主本線"));
					}
					else if (pUiData->sEkiTrack2[idx].iMainTrack == 3)
					{
						pListCtrl->SetItemText(idx, 3, (LPCTSTR)MfcUtil::LoadCString(IDS_WORD_DownUpMain));
						//pListCtrl->SetItemText(idx, 3, _T("上下主本線"));
					}

					if ((int)pUiData->bDiagramTrackOmit.size() > idx && pUiData->bDiagramTrackOmit[idx])
					{
						pListCtrl->SetItemText(idx, 4, nameDiagramTrackOmit);
					}
					else
					{
						pListCtrl->SetItemText(idx, 4, _T(""));
					}
				}
				else
				{
					int idxList = pListCtrl->InsertItem(INT_MAX, pUiData->sEkiTrack2[idx].strTrackName.c_str());
					pListCtrl->SetItemText(idxList, 1, pUiData->sEkiTrack2[idx].strTrackRyakusyou.c_str());
					pListCtrl->SetItemText(idxList, 2, pUiData->sEkiTrack2[idx].strTrackNoboriRyakusyou.c_str());

					if (pUiData->sEkiTrack2[idx].iMainTrack == 0)
					{
						pListCtrl->SetItemText(idxList, 3, (LPCTSTR)MfcUtil::LoadCString(IDS_WORD_SubMain));
						//pListCtrl->SetItemText(idxList, 3, _T("副本線/側線"));
					}
					else if (pUiData->sEkiTrack2[idx].iMainTrack == 1)
					{
						pListCtrl->SetItemText(idxList, 3, (LPCTSTR)MfcUtil::LoadCString(IDS_WORD_DownMain));
						//pListCtrl->SetItemText(idxList, 3, _T("下り主本線"));
					}
					else if (pUiData->sEkiTrack2[idx].iMainTrack == 2)
					{
						pListCtrl->SetItemText(idxList, 3, (LPCTSTR)MfcUtil::LoadCString(IDS_WORD_UpMain));
						//pListCtrl->SetItemText(idxList, 3, _T("上り主本線"));
					}
					else if (pUiData->sEkiTrack2[idx].iMainTrack == 3)
					{
						pListCtrl->SetItemText(idxList, 3, (LPCTSTR)MfcUtil::LoadCString(IDS_WORD_DownUpMain));
						//pListCtrl->SetItemText(idxList, 3, _T("上下主本線"));
					}

					if ((int)pUiData->bDiagramTrackOmit.size() > idx && pUiData->bDiagramTrackOmit[idx])
					{
						pListCtrl->SetItemText(idxList, 4, nameDiagramTrackOmit);
					}
					else
					{
						pListCtrl->SetItemText(idxList, 4, _T(""));
					}

				}
			}
			for (int idx = pListCtrl->GetItemCount() - 1; idx >= (int)pUiData->sEkiTrack2.size(); idx--)
			{
				pListCtrl->DeleteItem(idx);
			}
		}
		//OuterTerminalEkimei
		{
			CListCtrl* pListCtrl = (CListCtrl*)pOuter->GetDlgItem(IDC_LIST_OuterTerminalEkimei2);
			int iSelectColumn = pListCtrl->GetNextItem(-1, LVNI_SELECTED | LVNI_ALL);
			//pListCtrl->DeleteAllItems();

			for (int idx = 0; idx < (int)pUiData->sOuterTerminalEkimei.size(); idx++)
			{
				if (idx < pListCtrl->GetItemCount())
				{
					pListCtrl->SetItemText(idx, 0, pUiData->sOuterTerminalEkimei[idx].strOuterTerminalEkimei.c_str());
					pListCtrl->SetItemText(idx, 1, pUiData->sOuterTerminalEkimei[idx].strOuterTerminalJikokuRyaku.c_str());
					pListCtrl->SetItemText(idx, 2, pUiData->sOuterTerminalEkimei[idx].strOuterTerminalDiaRyaku.c_str());
				}
				else
				{
					int idxList = pListCtrl->InsertItem(INT_MAX, pUiData->sOuterTerminalEkimei[idx].strOuterTerminalEkimei.c_str());
					pListCtrl->SetItemText(idxList, 1, pUiData->sOuterTerminalEkimei[idx].strOuterTerminalJikokuRyaku.c_str());
					pListCtrl->SetItemText(idxList, 2, pUiData->sOuterTerminalEkimei[idx].strOuterTerminalDiaRyaku.c_str());
				}

			}
			for (int idx = pListCtrl->GetItemCount() - 1; idx >= (int)pUiData->sOuterTerminalEkimei.size(); idx--)
			{
				pListCtrl->DeleteItem(idx);
			}
		}
		//番線表示省略設定
		{
			CButton* pButton = (CButton*)pOuter->GetDlgItem(IDC_CHECK_JikokuhyouTrackOmit);
			int nCheck = BST_INDETERMINATE;
			switch (pUiData->iJikokuhyouTrackOmit)
			{
			case 1: // 番線表示省略
				nCheck = BST_CHECKED;
				break;
			case 0: //なし
				nCheck = BST_UNCHECKED;
				break;
			}
			pButton->SetCheck(nCheck);
			pButton->EnableWindow(pUiData->bJikokuhyouTrackOmitEnable);
		}
		//作業表示欄設定（起点側）
		{
			CComboBox* pComboBox = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_JikokuhyouOperationOrigin);
			pComboBox->SetCurSel(pUiData->iJikokuhyouOperationOrigin);
			pComboBox->EnableWindow(pUiData->bJikokuhyouOperationEnable);

			CButton* pButton = (CButton*)pOuter->GetDlgItem(IDC_CHECK_JikokuhyouOperationOriginDownBeforeUpAfter);
			int nCheck =
				pUiData->bJikokuhyouOperationOriginDownBeforeUpAfter ? BST_CHECKED : BST_UNCHECKED;
			pButton->SetCheck(nCheck);
			pButton->EnableWindow(pUiData->bJikokuhyouOperationEnable);

			CButton* pButton2 = (CButton*)pOuter->GetDlgItem(IDC_CHECK_JikokuhyouOperationOriginDownAfterUpBefore);
			int nCheck2 =
				pUiData->bJikokuhyouOperationOriginDownAfterUpBefore ? BST_CHECKED : BST_UNCHECKED;
			pButton2->SetCheck(nCheck2);
			pButton2->EnableWindow(pUiData->bJikokuhyouOperationEnable);
		}
		//作業表示欄設定（終点側）
		{
			CComboBox* pComboBox = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_JikokuhyouOperationTerminal);
			pComboBox->SetCurSel(pUiData->iJikokuhyouOperationTerminal);
			pComboBox->EnableWindow(pUiData->bJikokuhyouOperationEnable);

			CButton* pButton = (CButton*)pOuter->GetDlgItem(IDC_CHECK_JikokuhyouOperationTerminalDownBeforeUpAfter);
			int nCheck =
				pUiData->bJikokuhyouOperationTerminalDownBeforeUpAfter ? BST_CHECKED : BST_UNCHECKED;
			pButton->SetCheck(nCheck);
			pButton->EnableWindow(pUiData->bJikokuhyouOperationEnable);

			CButton* pButton2 = (CButton*)pOuter->GetDlgItem(IDC_CHECK_JikokuhyouOperationTerminalDownAfterUpBefore);
			int nCheck2 =
				pUiData->bJikokuhyouOperationTerminalDownAfterUpBefore ? BST_CHECKED : BST_UNCHECKED;
			pButton2->SetCheck(nCheck2);
			pButton2->EnableWindow(pUiData->bJikokuhyouOperationEnable);
		}

		//下り時刻表ビュー着時刻表示
		{
			CButton* pButton = (CButton*)pOuter->GetDlgItem(IDC_CHECK_JikokuhyouChakuJikokuDisplayKudari);
			int nCheck =
				pUiData->bJikokuhyouChakuJikokuDisplayKudari ? BST_CHECKED : BST_UNCHECKED;
			pButton->SetCheck(nCheck);
			pButton->EnableWindow(pUiData->bJikokuhyouChakuJikokuDisplayKudariEnable);
		}

		//上り時刻表ビュー着時刻表示
		{
			CButton* pButton = (CButton*)pOuter->GetDlgItem(IDC_CHECK_JikokuhyouChakuJikokuDisplayNobori);
			int nCheck =
				pUiData->bJikokuhyouChakuJikokuDisplayNobori ? BST_CHECKED : BST_UNCHECKED;
			pButton->SetCheck(nCheck);
			pButton->EnableWindow(pUiData->bJikokuhyouChakuJikokuDisplayNoboriEnable);
		}

		//下り時刻表ビュー発時刻表示
		{
			CButton* pButton = (CButton*)pOuter->GetDlgItem(IDC_CHECK_JikokuhyouHatsuJikokuDisplayKudari);
			int nCheck =
				pUiData->bJikokuhyouHatsuJikokuDisplayKudari ? BST_CHECKED : BST_UNCHECKED;
			pButton->SetCheck(nCheck);
			pButton->EnableWindow(pUiData->bJikokuhyouHatsuJikokuDisplayKudariEnable);
		}

		//上り時刻表ビュー発時刻表示
		{
			CButton* pButton = (CButton*)pOuter->GetDlgItem(IDC_CHECK_JikokuhyouHatsuJikokuDisplayNobori);
			int nCheck =
				pUiData->bJikokuhyouHatsuJikokuDisplayNobori ? BST_CHECKED : BST_UNCHECKED;
			pButton->SetCheck(nCheck);
			pButton->EnableWindow(pUiData->bJikokuhyouHatsuJikokuDisplayNoboriEnable);
		}

		//下り時刻表ビュー列車番号表示
		{
			CComboBox* pComboBox = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_JikokuhyouRessyabangouDisplayKudari);
			pComboBox->SetCurSel(pUiData->iJikokuhyouRessyabangouDisplayKudari);
			pComboBox->EnableWindow(pUiData->bJikokuhyouSyubetsuChangeDisplayKudariEnable);
		}

		//上り時刻表ビュー列車番号表示
		{
			CComboBox* pComboBox = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_JikokuhyouRessyabangouDisplayNobori);
			pComboBox->SetCurSel(pUiData->iJikokuhyouRessyabangouDisplayNobori);
			pComboBox->EnableWindow(pUiData->bJikokuhyouSyubetsuChangeDisplayNoboriEnable);
		}

		//下り時刻表ビュー運用番号表示
		{
			CComboBox* pComboBox = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_JikokuhyouOperationNumberDisplayKudari);
			pComboBox->SetCurSel(pUiData->iJikokuhyouOperationNumberDisplayKudari);
			pComboBox->EnableWindow(pUiData->bJikokuhyouSyubetsuChangeDisplayKudariEnable);

			CComboBox* pComboBox2 = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_JikokuhyouOperationNumberDisplayRowsKudari);
			pComboBox2->SetCurSel(pUiData->iJikokuhyouOperationNumberDisplayRowsKudari);
			pComboBox2->EnableWindow(pUiData->bJikokuhyouSyubetsuChangeDisplayKudariEnable);
		}

		//上り時刻表ビュー運用番号表示
		{
			CComboBox* pComboBox = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_JikokuhyouOperationNumberDisplayNobori);
			pComboBox->SetCurSel(pUiData->iJikokuhyouOperationNumberDisplayNobori);
			pComboBox->EnableWindow(pUiData->bJikokuhyouSyubetsuChangeDisplayNoboriEnable);

			CComboBox* pComboBox2 = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_JikokuhyouOperationNumberDisplayRowsNobori);
			pComboBox2->SetCurSel(pUiData->iJikokuhyouOperationNumberDisplayRowsNobori);
			pComboBox2->EnableWindow(pUiData->bJikokuhyouSyubetsuChangeDisplayNoboriEnable);
		}

		//下り時刻表ビュー列車種別表示
		{
			CComboBox* pComboBox = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_JikokuhyouRessyaSyubetsuDisplayKudari);
			pComboBox->SetCurSel(pUiData->iJikokuhyouRessyaSyubetsuDisplayKudari);
			pComboBox->EnableWindow(pUiData->bJikokuhyouSyubetsuChangeDisplayKudariEnable);
		}

		//上り時刻表ビュー列車種別表示
		{
			CComboBox* pComboBox = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_JikokuhyouRessyaSyubetsuDisplayNobori);
			pComboBox->SetCurSel(pUiData->iJikokuhyouRessyaSyubetsuDisplayNobori);
			pComboBox->EnableWindow(pUiData->bJikokuhyouSyubetsuChangeDisplayNoboriEnable);
		}

		//下り時刻表ビュー列車名表示
		{
			CComboBox* pComboBox = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_JikokuhyouRessyameiDisplayKudari);
			pComboBox->SetCurSel(pUiData->iJikokuhyouRessyameiDisplayKudari);
			pComboBox->EnableWindow(pUiData->bJikokuhyouSyubetsuChangeDisplayKudariEnable);
		}

		//上り時刻表ビュー列車名表示
		{
			CComboBox* pComboBox = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_JikokuhyouRessyameiDisplayNobori);
			pComboBox->SetCurSel(pUiData->iJikokuhyouRessyameiDisplayNobori);
			pComboBox->EnableWindow(pUiData->bJikokuhyouSyubetsuChangeDisplayNoboriEnable);
		}

		//下りカスタマイズ時刻表ビューでの路線外・前列車始発駅表示
		{
			CButton* pButton = (CButton*)pOuter->GetDlgItem(IDC_CHECK_JikokuhyouOuterSihatsuDisplayKudari);
			int nCheck =
				pUiData->bJikokuhyouOuterSihatsuDisplayKudari ? BST_CHECKED : BST_UNCHECKED;
			pButton->SetCheck(nCheck);
			pButton->EnableWindow(pUiData->bJikokuhyouOuterSihatsuDisplayKudariEnable);
		}

		//下りカスタマイズ時刻表ビューでの路線外・次列車終着駅表示
		{
			CButton* pButton = (CButton*)pOuter->GetDlgItem(IDC_CHECK_JikokuhyouOuterShuchakuDisplayKudari);
			int nCheck =
				pUiData->bJikokuhyouOuterShuchakuDisplayKudari ? BST_CHECKED : BST_UNCHECKED;
			pButton->SetCheck(nCheck);
			pButton->EnableWindow(pUiData->bJikokuhyouOuterShuchakuDisplayKudariEnable);
		}

		//上りカスタマイズ時刻表ビューでの路線外・前列車始発駅表示
		{
			CButton* pButton = (CButton*)pOuter->GetDlgItem(IDC_CHECK_JikokuhyouOuterSihatsuDisplayNobori);
			int nCheck =
				pUiData->bJikokuhyouOuterSihatsuDisplayNobori ? BST_CHECKED : BST_UNCHECKED;
			pButton->SetCheck(nCheck);
			pButton->EnableWindow(pUiData->bJikokuhyouOuterSihatsuDisplayNoboriEnable);
		}

		//上りカスタマイズ時刻表ビューでの路線外・次列車終着駅表示
		{
			CButton* pButton = (CButton*)pOuter->GetDlgItem(IDC_CHECK_JikokuhyouOuterShuchakuDisplayNobori);
			int nCheck =
				pUiData->bJikokuhyouOuterShuchakuDisplayNobori ? BST_CHECKED : BST_UNCHECKED;
			pButton->SetCheck(nCheck);
			pButton->EnableWindow(pUiData->bJikokuhyouOuterShuchakuDisplayNoboriEnable);
		}

		//ダイヤグラム背景色
		{
			CComboBox* pComboBox = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_DiagramColorNextEki);
			pComboBox->SetCurSel(pUiData->iDiagramColorNextEki);
		}

		//箱ダイヤで表示するか否か 
		{
			CButton* pButton = (CButton*)pOuter->GetDlgItem(IDC_CHECK_OperationTableDisplayJikoku);
			pButton->EnableWindow(pUiData->bOperationTableDisplayJikokuEnable);
			int nCheck = BST_INDETERMINATE;
			switch (pUiData->bOperationTableDisplayJikoku)
			{
			case true: // 表示あり
				nCheck = BST_CHECKED;
				break;
			case false: //なし
				nCheck = BST_UNCHECKED;
				break;
			}
			pButton->SetCheck(nCheck);
		}
	}

	void CDlgEkiProp::CPropEditUiInternal::UiDataFromUi(UIDATA* pUiData)
	{
		CDlgEkiProp* pOuter = (CDlgEkiProp*)((char*)this - offsetof(CDlgEkiProp, m_PropEditUiInternal));
		int iRv = 0;

		// --------------------------------
		//	DDXを用いた、UiControlへの設定
		// --------------------------------
		if (!pOuter->UpdateData(TRUE))
		{
			iRv = -1;	//	UpdateData でエラーが発生しました。
		}

		if (iRv >= 0)
		{
			// 駅時刻形式
			{
				pUiData->iEkijikokukeisiki = pOuter->m_iRADIO_Jikokukeisiki;
			}
			// 駅規模 
			{
				pUiData->iEkikibo = pOuter->m_iRADIO_Ekikibo;
			}
			// 次駅までの距離 
			{
				pUiData->iNextEkiDistance = pOuter->m_iEDITNextEkiDistance;
			}
		}
		// --------------------------------
		//	DDXを用いない、UiControlへの設定
		//	これらは、DDXによる値設定の後で
		//	行わなくてはなりません。
		// --------------------------------
		// 駅名 
		{
			CEdit* pEdit = (CEdit*)pOuter->GetDlgItem(IDC_EDIT_Ekimei);
			CString aString;
			pEdit->GetWindowText(aString);
			pUiData->strEkimei = (LPCTSTR)aString;
		}

		//ダイヤグラム列車情報表示（下り）
		{
			CComboBox* pComboBox = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_DiagramRessyajouhouHyoujiKudari);
			int iSel = pComboBox->GetCurSel();
			if (iSel != CB_ERR)
			{
				pUiData->iDiagramRessyajouhouHyoujiKudari = iSel;
			}
		}
		// ダイヤグラム列車情報表示（上り） 
		{
			CComboBox* pComboBox = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_DiagramRessyajouhouHyoujiNobori);
			int iSel = pComboBox->GetCurSel();
			if (iSel != CB_ERR)
			{
				pUiData->iDiagramRessyajouhouHyoujiNobori = iSel;
			}
		}

		//[駅時刻を駅時刻形式で正規化]の設定です。
		{
			CButton* pButton = (CButton*)pOuter->GetDlgItem(IDC_CHECK_AdjustByEkijikokukeisiki);
			int nCheck = pButton->GetCheck();
			switch (nCheck)
			{
			case BST_CHECKED:
				pUiData->bAdjustByEkijikokukeisiki = true;
				break;
			case BST_UNCHECKED:
				pUiData->bAdjustByEkijikokukeisiki = false;
				break;
			}
		}
		//分岐駅設定
		{
			CButton* pButton = (CButton*)pOuter->GetDlgItem(IDC_CHECK_Brunch);
			CComboBox* pComboBox = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_BrunchCoreEkiIndex);
			CButton* pButtonO = (CButton*)pOuter->GetDlgItem(IDC_CHECK_BrunchLoopOpposite);
			if (pUiData->bBrunchFunctionEnable)
			{
				int nCheck = pButton->GetCheck();
				int iSel = pComboBox->GetCurSel();
				if (nCheck == BST_CHECKED)
				{
					pUiData->bBrunch = true;
					if (iSel != -1)
					{
						CString strIdx;
						pComboBox->GetLBText(pComboBox->GetCurSel(), strIdx);
						vector<tstring>	strSpl = splitc< vector< tstring > >('.', (LPCTSTR)(strIdx));
						pUiData->iBrunchCoreEkiIndex = stoi(strSpl[0]);
					}
					else {
						pUiData->iBrunchCoreEkiIndex = iSel;
					}
					int nCheckO = pButtonO->GetCheck();
					if (nCheckO == BST_CHECKED)
					{
						pUiData->bBrunchOpposite = true;
					}
					else
					{
						pUiData->bBrunchOpposite = false;
					}
				}
				else if (nCheck == BST_UNCHECKED)
				{
					pUiData->bBrunch = false;
					pUiData->iBrunchCoreEkiIndex = -1;
					pUiData->bBrunchOpposite = false;
					//break;
				}
			}
		}
		//環状線設定
		{
			CButton* pButton = (CButton*)pOuter->GetDlgItem(IDC_CHECK_Loop);
			CComboBox* pComboBox = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_LoopOriginEkiIndex);
			CButton* pButtonO = (CButton*)pOuter->GetDlgItem(IDC_CHECK_BrunchLoopOpposite);
			if (pUiData->bLoopFunctionEnable)
			{
				int nCheck = pButton->GetCheck();
				int iSel = pComboBox->GetCurSel();
				if (nCheck == BST_CHECKED)
				{
					pUiData->bLoop = true;
					if (iSel != -1)
					{
						CString strIdx;
						pComboBox->GetLBText(pComboBox->GetCurSel(), strIdx);
						vector<tstring>	strSpl = splitc< vector< tstring > >('.', (LPCTSTR)(strIdx));
						pUiData->iLoopOriginEkiIndex = stoi(strSpl[0]);
					}
					else {
						pUiData->iLoopOriginEkiIndex = iSel;
					}
					int nCheckO = pButtonO->GetCheck();
					if (nCheckO == BST_CHECKED)
					{
						pUiData->bLoopOpposite = true;
					}
					else
					{
						pUiData->bLoopOpposite = false;
					}
				}
				else if (nCheck == BST_UNCHECKED)
				{
					pUiData->bLoop = false;
					pUiData->iLoopOriginEkiIndex = -1;
					pUiData->bLoopOpposite = false;
					//break;
				}
			}
		}
		//下り時刻表ビュー番線表示
		{
			CButton* pButton = (CButton*)pOuter->GetDlgItem(IDC_CHECK_JikokuhyouTrackDisplayKudari);
			int nCheck = pButton->GetCheck();
			switch (nCheck)
			{
			case BST_CHECKED:
				pUiData->iJikokuhyouTrackDisplayKudari = 1;
				break;
			case BST_UNCHECKED:
				pUiData->iJikokuhyouTrackDisplayKudari = 0;
				break;
			}

			//	チェックボックスは、中間状態への変更を認めません。
			//	ユーザーによって中間状態へ変更された場合は、
			//	チェックなし状態に変更します。
			if (pUiData->iJikokuhyouTrackDisplayKudari != -1 && nCheck == BST_INDETERMINATE)
			{
				pUiData->iJikokuhyouTrackDisplayKudari = 0;
			}
		}
		//上り時刻表ビュー番線表示
		{
			CButton* pButton = (CButton*)pOuter->GetDlgItem(IDC_CHECK_JikokuhyouTrackDisplayNobori);
			int nCheck = pButton->GetCheck();
			switch (nCheck)
			{
			case BST_CHECKED:
				pUiData->iJikokuhyouTrackDisplayNobori = 1;
				break;
			case BST_UNCHECKED:
				pUiData->iJikokuhyouTrackDisplayNobori = 0;
				break;
			}

			//	チェックボックスは、中間状態への変更を認めません。
			//	ユーザーによって中間状態へ変更された場合は、
			//	チェックなし状態に変更します。
			if (pUiData->iJikokuhyouTrackDisplayNobori != -1 && nCheck == BST_INDETERMINATE)
			{
				pUiData->iJikokuhyouTrackDisplayNobori = 0;
			}
		}
		//ダイヤグラムビュー番線表示
		{
			CButton* pButton = (CButton*)pOuter->GetDlgItem(IDC_CHECK_DiagramTrackDisplay);
			int nCheck = pButton->GetCheck();
			switch (nCheck)
			{
			case BST_CHECKED:
				pUiData->iDiagramTrackDisplay = 1;
				break;
			case BST_UNCHECKED:
				pUiData->iDiagramTrackDisplay = 0;
				break;
			}

			//	チェックボックスは、中間状態への変更を認めません。
			//	ユーザーによって中間状態へ変更された場合は、
			//	チェックなし状態に変更します。
			if (pUiData->iDiagramTrackDisplay != -1 && nCheck == BST_INDETERMINATE)
			{
				pUiData->iDiagramTrackDisplay = 0;
			}
		}
		// 駅名 
		{
			CEdit* pEdit = (CEdit*)pOuter->GetDlgItem(IDC_EDIT_EkimeiJikokuhyouRyaku);
			CString aString;
			pEdit->GetWindowText(aString);
			pUiData->strEkimeiJikokuhyouRyaku = (LPCTSTR)aString;
		}
		// 駅名 
		{
			CEdit* pEdit = (CEdit*)pOuter->GetDlgItem(IDC_EDIT_EkimeiDiagramRyaku);
			CString aString;
			pEdit->GetWindowText(aString);
			pUiData->strEkimeiDiagramRyaku = (LPCTSTR)aString;
		}
		//EkiTrack2
		{
			CListCtrl* pListCtrl = (CListCtrl*)pOuter->GetDlgItem(IDC_LIST_EkiTrack2);

			vector<bool> bDiagramTrackOmit;
			for (int idx = 0; idx < pListCtrl->GetItemCount(); idx++)
			{
				EkiTrack2 aEkiTrack2;
				aEkiTrack2.strTrackName = pListCtrl->GetItemText(idx, 0);
				aEkiTrack2.strTrackRyakusyou = pListCtrl->GetItemText(idx, 1);
				aEkiTrack2.strTrackNoboriRyakusyou = pListCtrl->GetItemText(idx, 2);
				CString strMainTrack = pListCtrl->GetItemText(idx, 3);
				//if (strMainTrack == _T("副本線/側線"))
				if (strMainTrack == (LPCTSTR)MfcUtil::LoadCString(IDS_WORD_SubMain))
				{
					aEkiTrack2.iMainTrack = 0;
				}
				//else if (strMainTrack == _T("下り主本線"))
				else if (strMainTrack == (LPCTSTR)MfcUtil::LoadCString(IDS_WORD_DownMain))
				{
					aEkiTrack2.iMainTrack = 1;
				}
				//else if (strMainTrack == _T("上り主本線"))
				else if (strMainTrack == (LPCTSTR)MfcUtil::LoadCString(IDS_WORD_UpMain))
				{
					aEkiTrack2.iMainTrack = 2;
				}
				//else if (strMainTrack == _T("上下主本線"))
				else if (strMainTrack == (LPCTSTR)MfcUtil::LoadCString(IDS_WORD_DownUpMain))
				{
					aEkiTrack2.iMainTrack = 3;
				}
				if (idx < (int)pUiData->sEkiTrack2.size())
				{
					pUiData->sEkiTrack2[idx] = aEkiTrack2;
				}
				else
				{
					pUiData->sEkiTrack2.push_back(aEkiTrack2);
				}
				bDiagramTrackOmit.push_back(pListCtrl->GetItemText(idx, 4) != _T(""));

			}
			if ((int)pUiData->sEkiTrack2.size() > pListCtrl->GetItemCount())
			{
				pUiData->sEkiTrack2.erase(
					pUiData->sEkiTrack2.begin() + pListCtrl->GetItemCount(),
					pUiData->sEkiTrack2.end());
			}
			pUiData->bDiagramTrackOmit = bDiagramTrackOmit;
		}
		//OuterTerminalEkimei
		{
			CListCtrl* pListCtrl = (CListCtrl*)pOuter->GetDlgItem(IDC_LIST_OuterTerminalEkimei2);

			for (int idx = 0; idx < pListCtrl->GetItemCount(); idx++)
			{
				OuterTerminalEkimei sOuterTerminalEkimei;

				sOuterTerminalEkimei.strOuterTerminalEkimei = pListCtrl->GetItemText(idx, 0);
				sOuterTerminalEkimei.strOuterTerminalJikokuRyaku = pListCtrl->GetItemText(idx, 1);
				sOuterTerminalEkimei.strOuterTerminalDiaRyaku = pListCtrl->GetItemText(idx, 2);
				//pListCtrl->GetItemText(idx, 0),
				//pListCtrl->GetItemText(idx, 1),
				//pListCtrl->GetItemText(idx, 2));
				if (idx < (int)pUiData->sOuterTerminalEkimei.size())
				{
					pUiData->sOuterTerminalEkimei[idx] = sOuterTerminalEkimei;
				}
				else
				{
					//tstring temp = pListCtrl->GetItemText(idx, 0);
					pUiData->sOuterTerminalEkimei.push_back(sOuterTerminalEkimei);
				}
			}
			if ((int)pUiData->sOuterTerminalEkimei.size() > pListCtrl->GetItemCount())
			{
				pUiData->sOuterTerminalEkimei.erase(
					pUiData->sOuterTerminalEkimei.begin() + pListCtrl->GetItemCount(),
					pUiData->sOuterTerminalEkimei.end());
			}
		}
		//番線表示省略設定
		{
			CButton* pButton = (CButton*)pOuter->GetDlgItem(IDC_CHECK_JikokuhyouTrackOmit);
			int nCheck = pButton->GetCheck();
			switch (nCheck)
			{
			case BST_CHECKED:
				pUiData->iJikokuhyouTrackOmit = 1;
				break;
			case BST_UNCHECKED:
				pUiData->iJikokuhyouTrackOmit = 0;
				break;
			}

			//	チェックボックスは、中間状態への変更を認めません。
			//	ユーザーによって中間状態へ変更された場合は、
			//	チェックなし状態に変更します。
			if (pUiData->iJikokuhyouTrackOmit != -1 && nCheck == BST_INDETERMINATE)
			{
				pUiData->iJikokuhyouTrackOmit = 0;
			}
		}

		//作業表示欄設定（起点側）
		{
			CComboBox* pComboBox = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_JikokuhyouOperationOrigin);
			int iSel = pComboBox->GetCurSel();
			if (iSel != CB_ERR)
			{
				pUiData->iJikokuhyouOperationOrigin = iSel;
			}

			CButton* pButton = (CButton*)pOuter->GetDlgItem(IDC_CHECK_JikokuhyouOperationOriginDownBeforeUpAfter);
			pUiData->bJikokuhyouOperationOriginDownBeforeUpAfter = pButton->GetCheck() == BST_CHECKED;

			CButton* pButton2 = (CButton*)pOuter->GetDlgItem(IDC_CHECK_JikokuhyouOperationOriginDownAfterUpBefore);
			pUiData->bJikokuhyouOperationOriginDownAfterUpBefore = pButton2->GetCheck() == BST_CHECKED;
		}
		//作業表示欄設定（終点側）
		{
			CComboBox* pComboBox = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_JikokuhyouOperationTerminal);
			int iSel = pComboBox->GetCurSel();
			if (iSel != CB_ERR)
			{
				pUiData->iJikokuhyouOperationTerminal = iSel;
			}

			CButton* pButton = (CButton*)pOuter->GetDlgItem(IDC_CHECK_JikokuhyouOperationTerminalDownBeforeUpAfter);
			pUiData->bJikokuhyouOperationTerminalDownBeforeUpAfter = pButton->GetCheck() == BST_CHECKED;

			CButton* pButton2 = (CButton*)pOuter->GetDlgItem(IDC_CHECK_JikokuhyouOperationTerminalDownAfterUpBefore);
			pUiData->bJikokuhyouOperationTerminalDownAfterUpBefore = pButton2->GetCheck() == BST_CHECKED;
		}

		//下り時刻表ビュー着時刻表示
		{
			CButton* pButton = (CButton*)pOuter->GetDlgItem(IDC_CHECK_JikokuhyouChakuJikokuDisplayKudari);
			pUiData->bJikokuhyouChakuJikokuDisplayKudari = pButton->GetCheck() == BST_CHECKED;
		}

		//上り時刻表ビュー着時刻表示
		{
			CButton* pButton = (CButton*)pOuter->GetDlgItem(IDC_CHECK_JikokuhyouChakuJikokuDisplayNobori);
			pUiData->bJikokuhyouChakuJikokuDisplayNobori = pButton->GetCheck() == BST_CHECKED;
		}

		//下り時刻表ビュー発時刻表示
		{
			CButton* pButton = (CButton*)pOuter->GetDlgItem(IDC_CHECK_JikokuhyouHatsuJikokuDisplayKudari);
			pUiData->bJikokuhyouHatsuJikokuDisplayKudari = pButton->GetCheck() == BST_CHECKED;
		}

		//上り時刻表ビュー発時刻表示
		{
			CButton* pButton = (CButton*)pOuter->GetDlgItem(IDC_CHECK_JikokuhyouHatsuJikokuDisplayNobori);
			pUiData->bJikokuhyouHatsuJikokuDisplayNobori = pButton->GetCheck() == BST_CHECKED;
		}

		//下り時刻表ビュー列車番号表示
		{
			CComboBox* pComboBox = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_JikokuhyouRessyabangouDisplayKudari);
			int iSel = pComboBox->GetCurSel();
			if (iSel != CB_ERR)
			{
				pUiData->iJikokuhyouRessyabangouDisplayKudari = iSel;
			}
		}
		//上り時刻表ビュー列車番号表示
		{
			CComboBox* pComboBox = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_JikokuhyouRessyabangouDisplayNobori);
			int iSel = pComboBox->GetCurSel();
			if (iSel != CB_ERR)
			{
				pUiData->iJikokuhyouRessyabangouDisplayNobori = iSel;
			}
		}

		//下り時刻表ビュー運用番号表示
		{
			CComboBox* pComboBox = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_JikokuhyouOperationNumberDisplayKudari);
			int iSel = pComboBox->GetCurSel();
			if (iSel != CB_ERR)
			{
				pUiData->iJikokuhyouOperationNumberDisplayKudari = iSel;
			}

			CComboBox* pComboBox2 = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_JikokuhyouOperationNumberDisplayRowsKudari);
			int iSel2 = pComboBox2->GetCurSel();
			if (iSel2 != CB_ERR)
			{
				pUiData->iJikokuhyouOperationNumberDisplayRowsKudari = iSel2;
			}
		}
		//上り時刻表ビュー運用番号表示
		{
			CComboBox* pComboBox = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_JikokuhyouOperationNumberDisplayNobori);
			int iSel = pComboBox->GetCurSel();
			if (iSel != CB_ERR)
			{
				pUiData->iJikokuhyouOperationNumberDisplayNobori = iSel;
			}

			CComboBox* pComboBox2 = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_JikokuhyouOperationNumberDisplayRowsNobori);
			int iSel2 = pComboBox2->GetCurSel();
			if (iSel2 != CB_ERR)
			{
				pUiData->iJikokuhyouOperationNumberDisplayRowsNobori = iSel2;
			}
		}

		//下り時刻表ビュー列車種別表示
		{
			CComboBox* pComboBox = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_JikokuhyouRessyaSyubetsuDisplayKudari);
			int iSel = pComboBox->GetCurSel();
			if (iSel != CB_ERR)
			{
				pUiData->iJikokuhyouRessyaSyubetsuDisplayKudari = iSel;
			}
		}
		//上り時刻表ビュー列車種別表示
		{
			CComboBox* pComboBox = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_JikokuhyouRessyaSyubetsuDisplayNobori);
			int iSel = pComboBox->GetCurSel();
			if (iSel != CB_ERR)
			{
				pUiData->iJikokuhyouRessyaSyubetsuDisplayNobori = iSel;
			}
		}

		//下り時刻表ビュー列車名・号数表示
		{
			CComboBox* pComboBox = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_JikokuhyouRessyameiDisplayKudari);
			int iSel = pComboBox->GetCurSel();
			if (iSel != CB_ERR)
			{
				pUiData->iJikokuhyouRessyameiDisplayKudari = iSel;
			}
		}
		//上り時刻表ビュー列車名・号数表示
		{
			CComboBox* pComboBox = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_JikokuhyouRessyameiDisplayNobori);
			int iSel = pComboBox->GetCurSel();
			if (iSel != CB_ERR)
			{
				pUiData->iJikokuhyouRessyameiDisplayNobori = iSel;
			}
		}

		//下りカスタマイズ時刻表ビューでの路線外・前列車始発駅表示
		{
			CButton* pButton = (CButton*)pOuter->GetDlgItem(IDC_CHECK_JikokuhyouOuterSihatsuDisplayKudari);
			pUiData->bJikokuhyouOuterSihatsuDisplayKudari = pButton->GetCheck() == BST_CHECKED;
		}

		//下りカスタマイズ時刻表ビューでの路線外・次列車終着駅表示
		{
			CButton* pButton = (CButton*)pOuter->GetDlgItem(IDC_CHECK_JikokuhyouOuterShuchakuDisplayKudari);
			pUiData->bJikokuhyouOuterShuchakuDisplayKudari = pButton->GetCheck() == BST_CHECKED;
		}

		//上りカスタマイズ時刻表ビューでの路線外・前列車始発駅表示
		{
			CButton* pButton = (CButton*)pOuter->GetDlgItem(IDC_CHECK_JikokuhyouOuterSihatsuDisplayNobori);
			pUiData->bJikokuhyouOuterSihatsuDisplayNobori = pButton->GetCheck() == BST_CHECKED;
		}

		//上りカスタマイズ時刻表ビューでの路線外・次列車終着駅表示
		{
			CButton* pButton = (CButton*)pOuter->GetDlgItem(IDC_CHECK_JikokuhyouOuterShuchakuDisplayNobori);
			pUiData->bJikokuhyouOuterShuchakuDisplayNobori = pButton->GetCheck() == BST_CHECKED;
		}

		//ダイヤグラム背景色
		{
			CComboBox* pComboBox = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_DiagramColorNextEki);
			int iSel = pComboBox->GetCurSel();
			if (iSel != CB_ERR)
			{
				pUiData->iDiagramColorNextEki = iSel;
			}
		}
		//箱ダイヤで表示するか否か
		{
			CButton* pButton = (CButton*)pOuter->GetDlgItem(IDC_CHECK_OperationTableDisplayJikoku);
			int nCheck = pButton->GetCheck();
			switch (nCheck)
			{
			case BST_CHECKED:
				pUiData->bOperationTableDisplayJikoku = true;
				break;
			case BST_UNCHECKED:
				pUiData->bOperationTableDisplayJikoku = false;
				break;
			case BST_INDETERMINATE:
				pUiData->bOperationTableDisplayJikoku = false;
				break;
			}

			//	チェックボックスは、中間状態への変更を認めません。
			//	ユーザーによって中間状態へ変更された場合は、
			//	チェックなし状態に変更します。
			//if (pUiData->iOperationTableDisplayJikoku != -1 && nCheck == BST_INDETERMINATE)
			//{
			//	pUiData->iOperationTableDisplayJikoku = false;
			//}
		}
	}

	void CDlgEkiProp::CPropEditUiInternal::ShowError(
		const tstring& strErrorReason,
		const tstring& strInfo)
	{
		CDlgEkiProp* pOuter = (CDlgEkiProp*)((char*)this - offsetof(CDlgEkiProp, m_PropEditUiInternal));

		CString strErrorMsg = strErrorReason.c_str();

		if (strErrorReason == ERRMSG_EKIMEI_TOO_LONG)
		{
			//pOuter->GetDlgItem( IDC_ERR_EkimeiNo )->GetWindowText( strErrorMsg )  ;
			pOuter->GetDlgItem(IDC_ERR_EkimeiTooLong)->GetWindowText(strErrorMsg);
		}
		else if (strErrorReason == ERRMSG_BRUNCH_EKIINDEX)
		{
			pOuter->GetDlgItem(IDC_ERR_BRUNCH_EKIINDEX)->GetWindowText(strErrorMsg);
		}
		else if (strErrorReason == ERRMSG_BRUNCH_EKIJIKOKUKEISIKI_UPCHAKU)
		{
			pOuter->GetDlgItem(IDC_ERR_BRUNCH_EKIJIKOKUKEISIKI_UPCHAKU)->GetWindowText(strErrorMsg);
		}
		else if (strErrorReason == ERRMSG_BRUNCH_EKIJIKOKUKEISIKI_DOWNCHAKU)
		{
			pOuter->GetDlgItem(IDC_ERR_BRUNCH_EKIJIKOKUKEISIKI_DOWNCHAKU)->GetWindowText(strErrorMsg);
		}
		else if (strErrorReason == ERRMSG_BRUNCH_EKIKIBO)
		{
			pOuter->GetDlgItem(IDC_ERR_BRUNCH_EKIKIBO)->GetWindowText(strErrorMsg);
		}
		else if (strErrorReason == ERRMSG_LOOP_EKIINDEX)
		{
			pOuter->GetDlgItem(IDC_ERR_LOOP_EKIINDEX)->GetWindowText(strErrorMsg);
		}
		else if (strErrorReason == ERRMSG_LOOP_EKIJIKOKUKEISIKI_HATSUCHAKU_DOWNCHAKU)
		{
			pOuter->GetDlgItem(IDC_ERR_LOOP_EKIJIKOKUKEISIKI_HATSUCHAKU_DOWNCHAKU)->GetWindowText(strErrorMsg);
		}
		else if (strErrorReason == ERRMSG_LOOP_EKIKIBO)
		{
			pOuter->GetDlgItem(IDC_ERR_LOOP_EKIKIBO)->GetWindowText(strErrorMsg);
		}
		else if (strErrorReason == ERRMSG_EKIMEI_EMPTY)
		{
			pOuter->GetDlgItem(IDC_ERR_EkimeiEmpty)->GetWindowText(strErrorMsg);
		}
		else if (strErrorReason == ERRMSG_EKIMEIJIKOKUHYOURYAKU_TOO_LONG)
		{
			//pOuter->GetDlgItem( IDC_ERR_EkimeiNo )->GetWindowText( strErrorMsg )  ;
			pOuter->GetDlgItem(IDC_ERR_EkimeiJikokuhyouRyakuTooLong)->GetWindowText(strErrorMsg);
		}
		else if (strErrorReason == ERRMSG_EKIMEIDIAGRAMRYAKU_TOO_LONG)
		{
			//pOuter->GetDlgItem( IDC_ERR_EkimeiNo )->GetWindowText( strErrorMsg )  ;
			pOuter->GetDlgItem(IDC_ERR_EkimeiDiagramRyakuTooLong)->GetWindowText(strErrorMsg);
		}
		pOuter->MessageBox(strErrorMsg, NULL, MB_OK | MB_ICONEXCLAMATION);

	}

	void CDlgEkiProp::CPropEditUiInternal::SetFocus(int iOffsetofUiDataMember)
	{
		CDlgEkiProp* pOuter = (CDlgEkiProp*)((char*)this - offsetof(CDlgEkiProp, m_PropEditUiInternal));
		CWnd* pControl = NULL;

		// 駅時刻形式
		{
			if (iOffsetofUiDataMember == offsetof(UIDATA, iEkijikokukeisiki))
			{
				pControl = pOuter->GetDlgItem(IDC_RADIO_Jikokukeisiki);
			}
		}
		// 駅規模 
		{
			if (iOffsetofUiDataMember == offsetof(UIDATA, iEkikibo))
			{
				pControl = pOuter->GetDlgItem(IDC_RADIO_Ekikibo);
			}
		}
		// --------------------------------
		// 駅名 
		{
			if (iOffsetofUiDataMember == offsetof(UIDATA, strEkimei))
			{
				pControl = (CEdit*)pOuter->GetDlgItem(IDC_EDIT_Ekimei);
			}
		}

		//ダイヤグラム列車情報表示（下り）
		{
			if (iOffsetofUiDataMember == offsetof(UIDATA, iDiagramRessyajouhouHyoujiKudari))
			{
				pControl = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_DiagramRessyajouhouHyoujiKudari);
			}
		}
		// ダイヤグラム列車情報表示（上り） 
		{
			if (iOffsetofUiDataMember == offsetof(UIDATA, iDiagramRessyajouhouHyoujiNobori))
			{
				pControl = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_DiagramRessyajouhouHyoujiNobori);
			}
		}

		//[駅時刻を駅時刻形式で正規化]の設定です。
		{
			if (iOffsetofUiDataMember == offsetof(UIDATA, bAdjustByEkijikokukeisiki))
			{
				pControl = (CButton*)pOuter->GetDlgItem(IDC_CHECK_AdjustByEkijikokukeisiki);
			}
		}

		//分岐駅設定
		{
			if (iOffsetofUiDataMember == offsetof(UIDATA, bBrunch))
			{
				pControl = (CButton*)pOuter->GetDlgItem(IDC_CHECK_Brunch);
			}
		}
		// 分岐駅設定基幹駅Index
		{
			if (iOffsetofUiDataMember == offsetof(UIDATA, iBrunchCoreEkiIndex))
			{
				pControl = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_BrunchCoreEkiIndex);
			}
		}

		//環状線設定
		{
			if (iOffsetofUiDataMember == offsetof(UIDATA, bLoop))
			{
				pControl = (CButton*)pOuter->GetDlgItem(IDC_CHECK_Loop);
			}
		}
		// 環状線設定終点駅Index
		{
			if (iOffsetofUiDataMember == offsetof(UIDATA, iLoopOriginEkiIndex))
			{
				pControl = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_LoopOriginEkiIndex);
			}
		}

		//下り時刻表ビュー番線表示
		{
			if (iOffsetofUiDataMember == offsetof(UIDATA, iJikokuhyouTrackDisplayKudari))
			{
				pControl = (CButton*)pOuter->GetDlgItem(IDC_CHECK_JikokuhyouTrackDisplayKudari);
			}
		}
		//上り時刻表ビュー番線表示
		{
			if (iOffsetofUiDataMember == offsetof(UIDATA, iJikokuhyouTrackDisplayNobori))
			{
				pControl = (CButton*)pOuter->GetDlgItem(IDC_CHECK_JikokuhyouTrackDisplayNobori);
			}
		}

		//ダイヤグラムビュー番線表示
		{
			if (iOffsetofUiDataMember == offsetof(UIDATA, iDiagramTrackDisplay))
			{
				pControl = (CButton*)pOuter->GetDlgItem(IDC_CHECK_DiagramTrackDisplay);
			}
		}
		//次駅までの距離
		{
			if (iOffsetofUiDataMember == offsetof(UIDATA, iNextEkiDistance))
			{
				pControl = (CButton*)pOuter->GetDlgItem(IDC_EDIT_NextEkiDistance);
			}
		}
		//番線表示省略設定
		{
			if (iOffsetofUiDataMember == offsetof(UIDATA, iJikokuhyouTrackOmit))
			{
				pControl = (CButton*)pOuter->GetDlgItem(IDC_CHECK_JikokuhyouTrackOmit);
			}
		}
		//作業表示欄設定（起点側）
		{
			if (iOffsetofUiDataMember == offsetof(UIDATA, iJikokuhyouOperationOrigin))
			{
				pControl = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_JikokuhyouOperationOrigin);
			}
		}
		//作業表示欄設定（終点側）
		{
			if (iOffsetofUiDataMember == offsetof(UIDATA, iJikokuhyouOperationTerminal))
			{
				pControl = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_JikokuhyouOperationTerminal);
			}
		}
		// 駅名略称
		{
			if (iOffsetofUiDataMember == offsetof(UIDATA, strEkimeiJikokuhyouRyaku))
			{
				pControl = (CEdit*)pOuter->GetDlgItem(IDC_EDIT_EkimeiJikokuhyouRyaku);
			}
		}
		// 駅名略称(運用一覧)
		{
			if (iOffsetofUiDataMember == offsetof(UIDATA, strEkimeiDiagramRyaku))
			{
				pControl = (CEdit*)pOuter->GetDlgItem(IDC_EDIT_EkimeiDiagramRyaku);
			}
		}

		//下り時刻表ビュー着時刻表示
		{
			if (iOffsetofUiDataMember == offsetof(UIDATA, bJikokuhyouChakuJikokuDisplayKudari))
			{
				pControl = (CButton*)pOuter->GetDlgItem(IDC_CHECK_JikokuhyouChakuJikokuDisplayKudari);
			}
		}
		//上り時刻表ビュー着時刻表示
		{
			if (iOffsetofUiDataMember == offsetof(UIDATA, bJikokuhyouChakuJikokuDisplayNobori))
			{
				pControl = (CButton*)pOuter->GetDlgItem(IDC_CHECK_JikokuhyouChakuJikokuDisplayNobori);
			}
		}

		//下り時刻表ビュー発時刻表示
		{
			if (iOffsetofUiDataMember == offsetof(UIDATA, bJikokuhyouHatsuJikokuDisplayKudari))
			{
				pControl = (CButton*)pOuter->GetDlgItem(IDC_CHECK_JikokuhyouHatsuJikokuDisplayKudari);
			}
		}
		//上り時刻表ビュー発時刻表示
		{
			if (iOffsetofUiDataMember == offsetof(UIDATA, bJikokuhyouHatsuJikokuDisplayNobori))
			{
				pControl = (CButton*)pOuter->GetDlgItem(IDC_CHECK_JikokuhyouHatsuJikokuDisplayNobori);
			}
		}
		//下り時刻表ビュー列車番号表示
		{
			if (iOffsetofUiDataMember == offsetof(UIDATA, iJikokuhyouRessyabangouDisplayKudari))
			{
				pControl = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_JikokuhyouRessyabangouDisplayKudari);
			}
		}
		//上り時刻表ビュー列車番号表示
		{
			if (iOffsetofUiDataMember == offsetof(UIDATA, iJikokuhyouRessyabangouDisplayNobori))
			{
				pControl = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_JikokuhyouRessyabangouDisplayNobori);
			}
		}
		//下り時刻表ビュー列車番号表示
		{
			if (iOffsetofUiDataMember == offsetof(UIDATA, iJikokuhyouOperationNumberDisplayKudari))
			{
				pControl = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_JikokuhyouOperationNumberDisplayKudari);
			}
		}
		//上り時刻表ビュー列車番号表示
		{
			if (iOffsetofUiDataMember == offsetof(UIDATA, iJikokuhyouOperationNumberDisplayNobori))
			{
				pControl = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_JikokuhyouOperationNumberDisplayNobori);
			}
		}
		//下り時刻表ビュー列車番号表示
		{
			if (iOffsetofUiDataMember == offsetof(UIDATA, iJikokuhyouRessyaSyubetsuDisplayKudari))
			{
				pControl = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_JikokuhyouRessyaSyubetsuDisplayKudari);
			}
		}
		//上り時刻表ビュー列車番号表示
		{
			if (iOffsetofUiDataMember == offsetof(UIDATA, iJikokuhyouRessyaSyubetsuDisplayNobori))
			{
				pControl = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_JikokuhyouRessyaSyubetsuDisplayNobori);
			}
		}
		//下り時刻表ビュー列車番号表示
		{
			if (iOffsetofUiDataMember == offsetof(UIDATA, iJikokuhyouRessyameiDisplayKudari))
			{
				pControl = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_JikokuhyouRessyameiDisplayKudari);
			}
		}
		//上り時刻表ビュー列車番号表示
		{
			if (iOffsetofUiDataMember == offsetof(UIDATA, iJikokuhyouRessyameiDisplayNobori))
			{
				pControl = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_JikokuhyouRessyameiDisplayNobori);
			}
		}
		//下りカスタマイズ時刻表ビューでの路線外・前列車始発駅表示
		{
			if (iOffsetofUiDataMember == offsetof(UIDATA, bJikokuhyouOuterSihatsuDisplayKudari))
			{
				pControl = (CComboBox*)pOuter->GetDlgItem(IDC_CHECK_JikokuhyouOuterSihatsuDisplayKudari);
			}
		}
		//下りカスタマイズ時刻表ビューでの路線外・次列車終着駅表示
		{
			if (iOffsetofUiDataMember == offsetof(UIDATA, bJikokuhyouOuterShuchakuDisplayKudari))
			{
				pControl = (CComboBox*)pOuter->GetDlgItem(IDC_CHECK_JikokuhyouOuterShuchakuDisplayKudari);
			}
		}
		//上りカスタマイズ時刻表ビューでの路線外・前列車始発駅表示
		{
			if (iOffsetofUiDataMember == offsetof(UIDATA, bJikokuhyouOuterSihatsuDisplayNobori))
			{
				pControl = (CComboBox*)pOuter->GetDlgItem(IDC_CHECK_JikokuhyouOuterSihatsuDisplayNobori);
			}
		}
		//上りカスタマイズ時刻表ビューでの路線外・次列車終着駅表示
		{
			if (iOffsetofUiDataMember == offsetof(UIDATA, bJikokuhyouOuterShuchakuDisplayNobori))
			{
				pControl = (CComboBox*)pOuter->GetDlgItem(IDC_CHECK_JikokuhyouOuterShuchakuDisplayNobori);
			}
		}
		//ダイヤグラム背景色
		{
			if (iOffsetofUiDataMember == offsetof(UIDATA, iDiagramColorNextEki))
			{
				pControl = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_DiagramColorNextEki);
			}
		}
		// --------------------------------
		if (pControl != NULL)
		{
			pOuter->GotoDlgCtrl(pControl);
		}
	}

	// ********************************
	//	コンストラクタ
	// ********************************
	CDlgEkiProp::CPropEditUiInternal::CPropEditUiInternal(
		bool bNewItem,
		Mu<CentDedEki*>* pTarget,
		bool* pbAdjustBuEkijikokukeisiki,
		int iEkiIndex,
		bool bEkijikokukeisikiAndEkikiboEnable,
		bool bBrunchFunctionEnable,
		bool bLoopFunctionEnable)
		: CPropEditUi_Eki(bNewItem, pTarget,
			pbAdjustBuEkijikokukeisiki, iEkiIndex,
			bEkijikokukeisikiAndEkikiboEnable,
			bBrunchFunctionEnable,
			bLoopFunctionEnable)
	{
	}

	/////////////////////////////////////////////////////////////////////////////
	//// CDlgEkiProp ダイアログ

		// --------------------------------
		//@name 下請関数
		// --------------------------------


	// ********************************
		//@name 属性
		// ********************************
	// ----------------------------------------------------------------
	//	MFC
	// ----------------------------------------------------------------
	CDlgEkiProp::CDlgEkiProp(
		bool bNewItem,
		Mu<CentDedEki*>* pTarget,
		bool* pbAdjustBuEkijikokukeisiki,
		int iEkiIndex,
		bool bEkijikokukeisikiAndEkikiboEnable,
		bool bBrunchFunctionEnable,
		bool bLoopFunctionEnable,
		vector<int>& iEkiTrack2Map,
		vector<int>& iOuterTerminalEkimeiMap,
		int iFocusItem,
		CKeyinputSenderToModalDlg* pCKeyinputSenderToModalDlg,
		CWnd* pParent)
		: CDialog(CDlgEkiProp::IDD, pParent)
		, m_PropEditUiInternal(bNewItem, pTarget,
			pbAdjustBuEkijikokukeisiki, iEkiIndex,
			bEkijikokukeisikiAndEkikiboEnable,
			bBrunchFunctionEnable,
			bLoopFunctionEnable)
		, m_iFocusItem(iFocusItem)
		, m_pCKeyinputSenderToModalDlg(pCKeyinputSenderToModalDlg)
		, m_bNewItem(bNewItem)
		, m_iEkiIndex(iEkiIndex)
		, m_bEkijikokukeisikiAndEkikiboEnable(bEkijikokukeisikiAndEkikiboEnable)
		, m_bBrunchFunctionEnable(bBrunchFunctionEnable)
		, m_bLoopFunctionEnable(bLoopFunctionEnable)
		, m_iEkiTrack2Map(iEkiTrack2Map)
		, m_iOuterTerminalEkimeiMap(iOuterTerminalEkimeiMap)
	{
		//{{AFX_DATA_INIT(CDlgEkiProp)
		m_iRADIO_Jikokukeisiki = -1;
		m_iRADIO_Ekikibo = -1;
		m_iEDITNextEkiDistance = 0;

		//}}AFX_DATA_INIT
	}


	void CDlgEkiProp::DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
		//{{AFX_DATA_MAP(CDlgEkiProp)
		DDX_Radio(pDX, IDC_RADIO_Jikokukeisiki, m_iRADIO_Jikokukeisiki);
		DDX_Radio(pDX, IDC_RADIO_Ekikibo, m_iRADIO_Ekikibo);
		DDX_Control(pDX, IDC_LIST_EkiTrack2, m_ListEkiTrack2);
		DDX_Control(pDX, IDC_LIST_OuterTerminalEkimei2, m_ListOuterTerminalEkimei2);
		DDX_Text(pDX, IDC_EDIT_NextEkiDistance, m_iEDITNextEkiDistance);
		DDV_MinMaxInt(pDX, m_iEDITNextEkiDistance, 0, 7200);//add_by_d_mania
		//}}AFX_DATA_MAP
	}


	BEGIN_MESSAGE_MAP(CDlgEkiProp, CDialog)
		//{{AFX_MSG_MAP(CDlgEkiProp)
		ON_WM_SHOWWINDOW()
		//}}AFX_MSG_MAP
		ON_EN_KILLFOCUS(IDC_EDIT_Ekimei, &CDlgEkiProp::OnEnKillfocusEditEkimei)
		ON_BN_CLICKED(IDC_RADIO_Jikokukeisiki, &CDlgEkiProp::OnBnClickedRadioJikokukeisiki)
		ON_BN_CLICKED(IDC_RADIO_Jikokukeisiki2, &CDlgEkiProp::OnBnClickedRadioJikokukeisiki2)
		ON_BN_CLICKED(IDC_RADIO_Jikokukeisiki3, &CDlgEkiProp::OnBnClickedRadioJikokukeisiki3)
		ON_BN_CLICKED(IDC_RADIO_Jikokukeisiki4, &CDlgEkiProp::OnBnClickedRadioJikokukeisiki4)
		ON_BN_CLICKED(IDC_RADIO_Jikokukeisiki5, &CDlgEkiProp::OnBnClickedRadioJikokukeisiki5)
		ON_BN_CLICKED(IDC_RADIO_Jikokukeisiki6, &CDlgEkiProp::OnBnClickedRadioJikokukeisiki6)
		ON_BN_CLICKED(IDC_RADIO_Ekikibo, &CDlgEkiProp::OnBnClickedRadioEkikibo)
		ON_BN_CLICKED(IDC_RADIO_Ekikibo2, &CDlgEkiProp::OnBnClickedRadioEkikibo2)
		ON_CBN_SELCHANGE(IDC_COMBO_DiagramRessyajouhouHyoujiKudari, &CDlgEkiProp::OnCbnSelchangeComboDiagramressyajouhouhyoujikudari)
		ON_CBN_SELCHANGE(IDC_COMBO_DiagramRessyajouhouHyoujiNobori, &CDlgEkiProp::OnCbnSelchangeComboDiagramressyajouhouhyoujinobori)
		ON_BN_CLICKED(IDC_CHECK_AdjustByEkijikokukeisiki, &CDlgEkiProp::OnBnClickedCheckAdjustbyekijikokukeisiki)
		ON_BN_CLICKED(IDC_CHECK_Brunch, &CDlgEkiProp::OnBnClickedCheckBrunch)
		ON_CBN_SELCHANGE(IDC_COMBO_BrunchCoreEkiIndex, &CDlgEkiProp::OnCbnSelchangeComboBrunchCoreEkiIndex)
		ON_BN_CLICKED(IDC_CHECK_Loop, &CDlgEkiProp::OnBnClickedCheckLoop)
		ON_CBN_SELCHANGE(IDC_COMBO_LoopOriginEkiIndex, &CDlgEkiProp::OnCbnSelchangeComboLoopOriginEkiIndex)
		ON_BN_CLICKED(IDC_CHECK_JikokuhyouTrackDisplayKudari, &CDlgEkiProp::OnBnClickedCheckJikokuhyouTrackDisplayKudari)
		ON_BN_CLICKED(IDC_CHECK_JikokuhyouTrackDisplayNobori, &CDlgEkiProp::OnBnClickedCheckJikokuhyouTrackDisplayNobori)
		ON_BN_CLICKED(IDC_CHECK_DiagramTrackDisplay, &CDlgEkiProp::OnBnClickedCheckDiagramTrackDisplay)
		ON_EN_KILLFOCUS(IDC_EDIT_EkimeiJikokuhyouRyaku, &CDlgEkiProp::OnEnKillfocusEditEkimeiJikokuhyouRyaku)
		ON_EN_KILLFOCUS(IDC_EDIT_EkimeiDiagramRyaku, &CDlgEkiProp::OnEnKillfocusEditEkimeiDiagramRyaku)
		ON_BN_CLICKED(IDC_BUTTON_EkiTrack2Add, &CDlgEkiProp::OnBnClickedButtonEkitrack2add)
		ON_BN_CLICKED(IDC_BUTTON_EkiTrack2Prop, &CDlgEkiProp::OnBnClickedButtonEkitrack2prop)
		ON_BN_CLICKED(IDC_BUTTON_EkiTrack2Clear, &CDlgEkiProp::OnBnClickedButtonEkitrack2clear)
		ON_BN_CLICKED(IDC_BUTTON_EkiTrack2Up, &CDlgEkiProp::OnBnClickedButtonEkitrack2up)
		ON_BN_CLICKED(IDC_BUTTON_EkiTrack2Down, &CDlgEkiProp::OnBnClickedButtonEkitrack2down)
		ON_BN_CLICKED(IDC_BUTTON_EkiTrack2DownMain, &CDlgEkiProp::OnBnClickedButtonEkitrack2downmain)
		ON_BN_CLICKED(IDC_BUTTON_EkiTrack2UpMain, &CDlgEkiProp::OnBnClickedButtonEkitrack2upmain)
		ON_BN_CLICKED(IDC_BUTTON_DiagramTrackOmitSwitch, &CDlgEkiProp::OnBnClickedButtonDiagramTrackOmitSwitch)
		ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_EkiTrack2, &CDlgEkiProp::OnLvnItemchangedListEkitrack2)
		ON_BN_CLICKED(IDC_BUTTON_OuterEkimeiAdd, &CDlgEkiProp::OnBnClickedButtonOuterTerminalEkimeiadd)
		ON_BN_CLICKED(IDC_BUTTON_OuterEkimeiProp, &CDlgEkiProp::OnBnClickedButtonOuterTerminalEkimeiprop)
		ON_BN_CLICKED(IDC_BUTTON_OuterEkimeiClear, &CDlgEkiProp::OnBnClickedButtonOuterTerminalEkimeiclear)
		ON_BN_CLICKED(IDC_BUTTON_OuterEkimeiUp, &CDlgEkiProp::OnBnClickedButtonOuterTerminalEkimeiup)
		ON_BN_CLICKED(IDC_BUTTON_OuterEkimeiDown, &CDlgEkiProp::OnBnClickedButtonOuterTerminalEkimeidown)
		ON_NOTIFY(NM_DBLCLK, IDC_LIST_EkiTrack2, &CDlgEkiProp::OnNMDblclkListEkitrack2)
		ON_EN_KILLFOCUS(IDC_EDIT_NextEkiDistance, &CDlgEkiProp::OnEnKillfocusEditNextekidistance)
		ON_BN_CLICKED(IDC_CHECK_JikokuhyouTrackOmit, &CDlgEkiProp::OnBnClickedCheckJikokuhyouTrackOmit)
		ON_CBN_SELCHANGE(IDC_COMBO_JikokuhyouOperationOrigin, &CDlgEkiProp::OnCbnSelchangeComboJikokuhyouoperationorigin)
		ON_CBN_SELCHANGE(IDC_COMBO_JikokuhyouOperationTerminal, &CDlgEkiProp::OnCbnSelchangeComboJikokuhyouoperationterminal)
		ON_BN_CLICKED(IDC_CHECK_JikokuhyouOperationOriginDownBeforeUpAfter, &CDlgEkiProp::OnBnClickedCheckJikokuhyouoperationorigindownbeforeupafter)
		ON_BN_CLICKED(IDC_CHECK_JikokuhyouOperationOriginDownAfterUpBefore, &CDlgEkiProp::OnBnClickedCheckJikokuhyouoperationorigindownafterupbefore)
		ON_BN_CLICKED(IDC_CHECK_JikokuhyouOperationTerminalDownBeforeUpAfter, &CDlgEkiProp::OnBnClickedCheckJikokuhyouoperationterminaldownbeforeupafter)
		ON_BN_CLICKED(IDC_CHECK_JikokuhyouOperationTerminalDownAfterUpBefore, &CDlgEkiProp::OnBnClickedCheckJikokuhyouoperationterminaldownafterupbefore)
		ON_NOTIFY(NM_DBLCLK, IDC_LIST_OuterTerminalEkimei2, &CDlgEkiProp::OnNMDblclkListOuterterminalekimei2)
		ON_BN_CLICKED(IDC_CHECK_JikokuhyouChakuJikokuDisplayKudari, &CDlgEkiProp::OnBnClickedCheckJikokuhyouchakujikokudisplaykudari)
		ON_BN_CLICKED(IDC_CHECK_JikokuhyouChakuJikokuDisplayNobori, &CDlgEkiProp::OnBnClickedCheckJikokuhyouchakujikokudisplaynobori)
		ON_BN_CLICKED(IDC_CHECK_JikokuhyouHatsuJikokuDisplayKudari, &CDlgEkiProp::OnBnClickedCheckJikokuhyouhatsujikokudisplaykudari)
		ON_BN_CLICKED(IDC_CHECK_JikokuhyouHatsuJikokuDisplayNobori, &CDlgEkiProp::OnBnClickedCheckJikokuhyouhatsujikokudisplaynobori)
		ON_CBN_SELCHANGE(IDC_COMBO_JikokuhyouRessyabangouDisplayKudari, &CDlgEkiProp::OnCbnSelchangeComboJikokuhyouressyabangoudisplaykudari)
		ON_CBN_SELCHANGE(IDC_COMBO_JikokuhyouRessyabangouDisplayNobori, &CDlgEkiProp::OnCbnSelchangeComboJikokuhyouressyabangoudisplaynobori)
		ON_CBN_SELCHANGE(IDC_COMBO_JikokuhyouOperationNumberDisplayKudari, &CDlgEkiProp::OnCbnSelchangeComboJikokuhyouoperationnumberdisplaykudari)
		ON_CBN_SELCHANGE(IDC_COMBO_JikokuhyouOperationNumberDisplayNobori, &CDlgEkiProp::OnCbnSelchangeComboJikokuhyouoperationnumberdisplaynobori)
		ON_CBN_SELCHANGE(IDC_COMBO_JikokuhyouOperationNumberDisplayRowsKudari, &CDlgEkiProp::OnCbnSelchangeComboJikokuhyouoperationnumberdisplayrowskudari)
		ON_CBN_SELCHANGE(IDC_COMBO_JikokuhyouOperationNumberDisplayRowsNobori, &CDlgEkiProp::OnCbnSelchangeComboJikokuhyouoperationnumberdisplayrowsnobori)
		ON_CBN_SELCHANGE(IDC_COMBO_JikokuhyouRessyaSyubetsuDisplayKudari, &CDlgEkiProp::OnCbnSelchangeComboJikokuhyouressyasyubetsudisplaykudari)
		ON_CBN_SELCHANGE(IDC_COMBO_JikokuhyouRessyaSyubetsuDisplayNobori, &CDlgEkiProp::OnCbnSelchangeComboJikokuhyouressyasyubetsudisplaynobori)
		ON_CBN_SELCHANGE(IDC_COMBO_JikokuhyouRessyameiDisplayKudari, &CDlgEkiProp::OnCbnSelchangeComboJikokuhyouressyameidisplaykudari)
		ON_CBN_SELCHANGE(IDC_COMBO_JikokuhyouRessyameiDisplayNobori, &CDlgEkiProp::OnCbnSelchangeComboJikokuhyouressyameidisplaynobori)
		ON_BN_CLICKED(IDC_CHECK_JikokuhyouOuterSihatsuDisplayKudari, &CDlgEkiProp::OnBnClickedCheckJikokuhyououtersihatsudisplaykudari)
		ON_BN_CLICKED(IDC_CHECK_JikokuhyouOuterShuchakuDisplayKudari, &CDlgEkiProp::OnBnClickedCheckJikokuhyououtershuchakudisplaykudari)
		ON_BN_CLICKED(IDC_CHECK_JikokuhyouOuterSihatsuDisplayNobori, &CDlgEkiProp::OnBnClickedCheckJikokuhyououtersihatsudisplaynobori)
		ON_BN_CLICKED(IDC_CHECK_JikokuhyouOuterShuchakuDisplayNobori, &CDlgEkiProp::OnBnClickedCheckJikokuhyououtershuchakudisplaynobori)
		ON_CBN_SELCHANGE(IDC_COMBO_DiagramColorNextEki, &CDlgEkiProp::OnCbnSelchangeComboDiagramColorNextEki)
		ON_BN_CLICKED(IDC_CHECK_OperationTableDisplayJikoku, &CDlgEkiProp::OnBnClickedCheckOperationTableDisplayJikoku)
	END_MESSAGE_MAP()

	/////////////////////////////////////////////////////////////////////////////
	// CDlgEkiProp メッセージ ハンドラ

	BOOL CDlgEkiProp::OnInitDialog()
	{
		CDialog::OnInitDialog();

		// 駅時刻形式/駅規模 
		if (!m_bEkijikokukeisikiAndEkikiboEnable)
		{
			CButton* pButton1 = (CButton*)GetDlgItem(IDC_RADIO_Jikokukeisiki);
			CButton* pButton2 = (CButton*)GetDlgItem(IDC_RADIO_Jikokukeisiki2);
			CButton* pButton3 = (CButton*)GetDlgItem(IDC_RADIO_Jikokukeisiki3);
			CButton* pButton4 = (CButton*)GetDlgItem(IDC_RADIO_Jikokukeisiki4);
			CButton* pButton5 = (CButton*)GetDlgItem(IDC_RADIO_Jikokukeisiki5);
			CButton* pButton6 = (CButton*)GetDlgItem(IDC_RADIO_Jikokukeisiki6);
			CButton* pButton7 = (CButton*)GetDlgItem(IDC_RADIO_Ekikibo);
			CButton* pButton8 = (CButton*)GetDlgItem(IDC_RADIO_Ekikibo2);
			pButton1->EnableWindow(false);
			pButton2->EnableWindow(false);
			pButton3->EnableWindow(false);
			pButton4->EnableWindow(false);
			pButton5->EnableWindow(false);
			pButton6->EnableWindow(false);
			pButton7->EnableWindow(false);
			pButton8->EnableWindow(false);

			//CButton* pButton9 = (CButton*)GetDlgItem(IDC_CHECK_Brunch);
			//CComboBox* pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_BrunchCoreEkiIndex);
			//pButton9->EnableWindow(false);
			//pComboBox->EnableWindow(false);

		}

		{
			const CentDedRosen* pCentDedRosen = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen();
			const Mu<const CentDedEki*>* pMuCentDedEki =
				pCentDedRosen->getCentDedEkiCont()->getMuPtr();
			CComboBox* pCComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_BrunchCoreEkiIndex);
			CComboBox* pCComboBox2 = (CComboBox*)GetDlgItem(IDC_COMBO_LoopOriginEkiIndex);
			for (int idx = 0; idx < pMuCentDedEki->size(); idx++)
			{
				/**
					Ver2.0
					路線の起点駅・上り着の場合、基幹駅にできるようにします。
					また、路線の終端駅・下り着の場合も、基幹駅にできるようにします。
				*/
				const CentDedEki* pCentDedEki = pMuCentDedEki->get(idx);
				tstring strEkimei = to_tstring(idx) + _T(". ");
				strEkimei = strEkimei + pCentDedEki->getEkimei();
				if (pCentDedEki->getEkikibo() == CentDedEki::EEkikibo::Ekikibo_Syuyou &&
					idx < m_iEkiIndex)
				{
					if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku)
					{
						/**
							発着駅の場合は、自身が派生駅(INT_MIN,INT_MAX)の可能性は無い
						*/
						if (pCentDedEki->getBrunchLoopPosition() == -1)
						{
							//単独駅の場合
							pCComboBox->AddString(strEkimei.c_str());
						}
						else if (pCentDedEki->getEkiIndexLoop().size() >= 2 &&
							pCentDedEki->getBrunchLoopPosition() != pCentDedEki->getEkiIndexLoop().size() - 1)
						{
							//起点駅でも、編集対象駅が終点駅の場合(この場合、環状線設定を解除すれば、分岐設定が可に)
							if (pCentDedEki->getEkiIndexLoop()[pCentDedEki->getBrunchLoopPosition() + 1] == m_iEkiIndex)
							{
								pCComboBox->AddString(strEkimei.c_str());
							}
						}
						else
						{
							//単独の基幹駅もしくは終点駅の場合
							pCComboBox->AddString(strEkimei.c_str());
						}

						if (pCentDedEki->getBrunchLoopPosition() == -1)
						{
							//単独駅の場合
							pCComboBox2->AddString(strEkimei.c_str());
						}
						else if (pCentDedEki->getEkiIndexLoop().size() >= 2 &&
							pCentDedEki->getBrunchLoopPosition() != pCentDedEki->getEkiIndexLoop().size() - 1)
						{
							//起点駅でも、編集対象駅が終点駅の場合
							if (pCentDedEki->getEkiIndexLoop()[pCentDedEki->getBrunchLoopPosition() + 1] == m_iEkiIndex)
							{
								pCComboBox2->AddString(strEkimei.c_str());
							}
						}
						else if (pCentDedEki->getEkiIndexBrunchTerminalSide().size() == 0)
						{
							//単独の基幹駅もしくは終点駅で、終点側分岐駅が無い場合
							pCComboBox2->AddString(strEkimei.c_str());
						}
						else if (pCentDedEki->getEkiIndexBrunchTerminalSide().size() == 1 &&
							pCentDedEki->getEkiIndexBrunchTerminalSide().front() == m_iEkiIndex)
						{
							//単独の基幹駅もしくは終点駅で、終点側分岐駅が編集対象駅一つのみの場合(この場合、分岐駅設定を解除すれば、環状設定が可に)
							pCComboBox2->AddString(strEkimei.c_str());
						}
					}
					else if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku)
					{
						if (idx == 0)
						{
							//idx==0の上り着の場合、派生駅の可能性は無い
							if (pCentDedEki->getBrunchLoopPosition() == -1)
							{
								//単独駅の場合
								pCComboBox->AddString(strEkimei.c_str());
							}
							else if (pCentDedEki->getEkiIndexLoop().size() == 1)
							{
								//単独の基幹駅の場合
								pCComboBox->AddString(strEkimei.c_str());
							}
							else if (pCentDedEki->getEkiIndexLoop().size() >= 2 &&
								pCentDedEki->getBrunchLoopPosition() != pCentDedEki->getEkiIndexLoop().size() - 1)
							{
								//起点駅でも、編集対象駅が終点駅の場合(この場合、環状線設定を解除すれば、分岐設定が可に)
								if (pCentDedEki->getEkiIndexLoop()[pCentDedEki->getBrunchLoopPosition() + 1] == m_iEkiIndex)
								{
									pCComboBox->AddString(strEkimei.c_str());
								}
							}

							if (pCentDedEki->getBrunchLoopPosition() == -1)
							{
								//単独駅の場合
								pCComboBox2->AddString(strEkimei.c_str());
							}
							//else if (pCentDedEki->getEkiIndexLoop().size() >= 2 &&
							//	pCentDedEki->getBrunchLoopPosition() != pCentDedEki->getEkiIndexLoop().size() - 1)
							//{
							//	//起点駅でも、編集対象駅が終点駅の場合
							//	if (pCentDedEki->getEkiIndexLoop()[pCentDedEki->getBrunchLoopPosition() + 1] == m_iEkiIndex)
							//	{
							//		pCComboBox2->AddString(strEkimei.c_str());
							//	}
							//}
							else if (pCentDedEki->getEkiIndexLoop().size() >= 2)
							{
								//起点駅でも、編集対象駅が終点駅の場合(上り着の起点駅は必ずiPositionが先頭(0)になる)
								if (pCentDedEki->getEkiIndexLoop()[1] == m_iEkiIndex)
								{
									pCComboBox2->AddString(strEkimei.c_str());
								}
							}
							//else if (pCentDedEki->getEkiIndexBrunchTerminalSide().size() == 0)
							//{
							//	//単独の基幹駅もしくは終点駅で、終点側分岐駅が無い場合
							//	pCComboBox2->AddString(strEkimei.c_str());
							//}
							else if (pCentDedEki->getEkiIndexBrunchTerminalSide().size() == 1 &&
								pCentDedEki->getEkiIndexBrunchTerminalSide().front() == m_iEkiIndex)
							{
								//単独の基幹駅で、終点側分岐駅が編集対象駅一つのみの場合(この場合、分岐駅設定を解除すれば、環状設定が可に)
								//idx0上り着の基幹駅は、必ず終点方派生駅が一つ以上存在する
								pCComboBox2->AddString(strEkimei.c_str());
							}

						}
						else
						{
							//idx=0以外の場合は、終点方派生駅になっている可能性に注意
							if (pCentDedEki->getBrunchLoopPosition() == -1)
							{
								//単独駅の場合
								pCComboBox2->AddString(strEkimei.c_str());
							}
							else if (pCentDedEki->getBrunchLoopPosition() == 0 &&
								pCentDedEki->getEkiIndexLoop().size() >= 2)
							{
								//起点駅でも、編集対象駅が終点駅の場合
								if (pCentDedEki->getEkiIndexLoop()[1] == m_iEkiIndex)
								{
									pCComboBox2->AddString(strEkimei.c_str());
								}

							}
						}
					}
				}
				else if (pCentDedEki->getEkikibo() == CentDedEki::EEkikibo::Ekikibo_Syuyou &&
					idx > m_iEkiIndex)
				{
					if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku)
					{
						/**
							発着駅の場合は、自身が派生駅(INT_MIN,INT_MAX)の可能性は無い
						*/
						if (pCentDedEki->getBrunchLoopPosition() == -1 ||
							pCentDedEki->getBrunchLoopPosition() == 0)
						{
							//単独駅の場合または基幹駅or起点駅(先頭)の場合
							pCComboBox->AddString(strEkimei.c_str());
						}

					}
					else if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku &&
						idx == pMuCentDedEki->size() - 1)
					{
						//末尾の下り着駅は派生駅の可能性は無いので、無条件で追加する
						if (pCentDedEki->getBrunchLoopPosition() == -1 ||
							pCentDedEki->getBrunchLoopPosition() == 0)
						{
							//単独駅の場合または基幹駅の場合
							pCComboBox->AddString(strEkimei.c_str());
						}
					}
				}
			}
		}

		if (m_iEkiIndex >= 0)
		{
			LVCOLUMN    lvc;
			TCHAR       strCaption[][32] = { _T("駅番線名"), _T("下略称"), _T("上略称"), _T("主本線設定"), _T("在線略") };
			//const int   clmNum = sizeof strCaption / sizeof strCaption[0];
			int         err = 0;
			m_ListEkiTrack2.SetExtendedStyle(LVS_EX_FULLROWSELECT);
			lvc.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;    // 有効フラグ
			{
				lvc.iSubItem = 0;            // サブアイテム番号
				lvc.pszText = strCaption[0];   // 見出しテキスト
				//lvc.cx = 128;          // 横幅
				lvc.cx = 100;          // 横幅
				m_ListEkiTrack2.InsertColumn(0, &lvc);
			}
			{
				lvc.iSubItem = 1;            // サブアイテム番号
				lvc.pszText = strCaption[1];   // 見出しテキスト
				lvc.cx = 48;          // 横幅
				m_ListEkiTrack2.InsertColumn(1, &lvc);
			}
			{
				lvc.iSubItem = 2;            // サブアイテム番号
				lvc.pszText = strCaption[2];   // 見出しテキスト
				lvc.cx = 48;          // 横幅
				m_ListEkiTrack2.InsertColumn(2, &lvc);
			}
			{
				lvc.iSubItem = 3;            // サブアイテム番号
				lvc.pszText = strCaption[3];   // 見出しテキスト
				//lvc.cx = 96;          // 
				lvc.cx = 78;          // 横幅
				m_ListEkiTrack2.InsertColumn(3, &lvc);
			}
			{
				lvc.iSubItem = 4;            // サブアイテム番号
				lvc.pszText = strCaption[4];   // 見出しテキスト
				//lvc.cx = 96;          // 
				lvc.cx = 48;          // 横幅
				m_ListEkiTrack2.InsertColumn(4, &lvc);
			}

			//updateListEkiTrack2();
		}
		else
		{
			GetDlgItem(IDC_BUTTON_EkiTrack2Add)->EnableWindow(false);
			GetDlgItem(IDC_BUTTON_EkiTrack2Prop)->EnableWindow(false);
			GetDlgItem(IDC_BUTTON_EkiTrack2Clear)->EnableWindow(false);
			GetDlgItem(IDC_BUTTON_EkiTrack2Up)->EnableWindow(false);
			GetDlgItem(IDC_BUTTON_EkiTrack2Down)->EnableWindow(false);
			GetDlgItem(IDC_BUTTON_EkiTrack2DownMain)->EnableWindow(false);
			GetDlgItem(IDC_BUTTON_EkiTrack2UpMain)->EnableWindow(false);
		}

		if (m_iEkiIndex >= 0)
		{
			LVCOLUMN    lvc;
			TCHAR       strCaption[][32] = { _T("駅名"), _T("時刻表略称"), _T("ダイヤ略") };
			//const int   clmNum = sizeof strCaption / sizeof strCaption[0];
			int         err = 0;
			m_ListOuterTerminalEkimei2.SetExtendedStyle(LVS_EX_FULLROWSELECT);
			lvc.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;    // 有効フラグ
			{
				lvc.iSubItem = 0;            // サブアイテム番号
				lvc.pszText = strCaption[0];   // 見出しテキスト
				//lvc.cx = 128;          // 横幅
				lvc.cx = 100;          // 横幅
				m_ListOuterTerminalEkimei2.InsertColumn(0, &lvc);
			}
			{
				lvc.iSubItem = 1;            // サブアイテム番号
				lvc.pszText = strCaption[1];   // 見出しテキスト
				lvc.cx = 80;          // 横幅
				m_ListOuterTerminalEkimei2.InsertColumn(1, &lvc);
			}
			{
				lvc.iSubItem = 2;            // サブアイテム番号
				lvc.pszText = strCaption[2];   // 見出しテキスト
				lvc.cx = 60;          // 横幅
				m_ListOuterTerminalEkimei2.InsertColumn(2, &lvc);
			}
		}
		else
		{
			GetDlgItem(IDC_BUTTON_OuterEkimeiAdd)->EnableWindow(false);
			GetDlgItem(IDC_BUTTON_OuterEkimeiProp)->EnableWindow(false);
			GetDlgItem(IDC_BUTTON_OuterEkimeiClear)->EnableWindow(false);
			GetDlgItem(IDC_BUTTON_OuterEkimeiUp)->EnableWindow(false);
			GetDlgItem(IDC_BUTTON_OuterEkimeiDown)->EnableWindow(false);
		}

		// コンボボックス
		{
			CComboBox* pCComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_DiagramRessyajouhouHyoujiKudari);
			CComboBox* pCComboBox2 = (CComboBox*)GetDlgItem(IDC_COMBO_DiagramRessyajouhouHyoujiNobori);

			tstring strTemp = _T("始発なら表示");
			pCComboBox->AddString(strTemp.c_str());
			pCComboBox2->AddString(strTemp.c_str());
			strTemp = _T("常に表示");
			pCComboBox->AddString(strTemp.c_str());
			pCComboBox2->AddString(strTemp.c_str());
			strTemp = _T("表示しない");
			pCComboBox->AddString(strTemp.c_str());
			pCComboBox2->AddString(strTemp.c_str());
			//始発なら表示;常に表示;表示しない;

		}

		// コンボボックス
		{
			CComboBox* pCComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_JikokuhyouOperationOrigin);
			CComboBox* pCComboBox2 = (CComboBox*)GetDlgItem(IDC_COMBO_JikokuhyouOperationTerminal);

			tstring strTemp = _T("無し");
			pCComboBox->AddString(strTemp.c_str());
			pCComboBox2->AddString(strTemp.c_str());
			strTemp = _T("1作業");
			pCComboBox->AddString(strTemp.c_str());
			pCComboBox2->AddString(strTemp.c_str());
			strTemp = _T("2作業");
			pCComboBox->AddString(strTemp.c_str());
			pCComboBox2->AddString(strTemp.c_str());
			strTemp = _T("3作業");
			pCComboBox->AddString(strTemp.c_str());
			pCComboBox2->AddString(strTemp.c_str());

		}

		// コンボボックス
		{
			CComboBox* pCComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_JikokuhyouRessyabangouDisplayKudari);
			CComboBox* pCComboBox2 = (CComboBox*)GetDlgItem(IDC_COMBO_JikokuhyouRessyabangouDisplayNobori);
			CComboBox* pCComboBox3 = (CComboBox*)GetDlgItem(IDC_COMBO_JikokuhyouOperationNumberDisplayKudari);
			CComboBox* pCComboBox4 = (CComboBox*)GetDlgItem(IDC_COMBO_JikokuhyouOperationNumberDisplayNobori);
			CComboBox* pCComboBox5 = (CComboBox*)GetDlgItem(IDC_COMBO_JikokuhyouRessyaSyubetsuDisplayKudari);
			CComboBox* pCComboBox6 = (CComboBox*)GetDlgItem(IDC_COMBO_JikokuhyouRessyaSyubetsuDisplayNobori);
			CComboBox* pCComboBox7 = (CComboBox*)GetDlgItem(IDC_COMBO_JikokuhyouRessyameiDisplayKudari);
			CComboBox* pCComboBox8 = (CComboBox*)GetDlgItem(IDC_COMBO_JikokuhyouRessyameiDisplayNobori);

			tstring strTemp = _T("表示しない");//全種
			pCComboBox->AddString(strTemp.c_str());
			pCComboBox2->AddString(strTemp.c_str());
			pCComboBox3->AddString(strTemp.c_str());
			pCComboBox4->AddString(strTemp.c_str());
			pCComboBox5->AddString(strTemp.c_str());
			pCComboBox6->AddString(strTemp.c_str());
			pCComboBox7->AddString(strTemp.c_str());
			pCComboBox8->AddString(strTemp.c_str());
			strTemp = _T("運用番号が変わる列車のみ");//運用番号
			pCComboBox3->AddString(strTemp.c_str());
			pCComboBox4->AddString(strTemp.c_str());
			strTemp = _T("種別変更列車のみ");//全種
			pCComboBox->AddString(strTemp.c_str());
			pCComboBox2->AddString(strTemp.c_str());
			pCComboBox3->AddString(strTemp.c_str());
			pCComboBox4->AddString(strTemp.c_str());
			pCComboBox5->AddString(strTemp.c_str());
			pCComboBox6->AddString(strTemp.c_str());
			pCComboBox7->AddString(strTemp.c_str());
			pCComboBox8->AddString(strTemp.c_str());
			strTemp = _T("種別・列車情報変更列車のみ");//全種
			pCComboBox->AddString(strTemp.c_str());
			pCComboBox2->AddString(strTemp.c_str());
			pCComboBox3->AddString(strTemp.c_str());
			pCComboBox4->AddString(strTemp.c_str());
			pCComboBox5->AddString(strTemp.c_str());
			pCComboBox6->AddString(strTemp.c_str());
			pCComboBox7->AddString(strTemp.c_str());
			pCComboBox8->AddString(strTemp.c_str());
			strTemp = _T("全列車表示");//全種
			pCComboBox->AddString(strTemp.c_str());
			pCComboBox2->AddString(strTemp.c_str());
			pCComboBox3->AddString(strTemp.c_str());
			pCComboBox4->AddString(strTemp.c_str());
			pCComboBox5->AddString(strTemp.c_str());
			pCComboBox6->AddString(strTemp.c_str());
			pCComboBox7->AddString(strTemp.c_str());
			pCComboBox8->AddString(strTemp.c_str());

		}

		// コンボボックス
		{
			CComboBox* pCComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_JikokuhyouOperationNumberDisplayRowsKudari);
			CComboBox* pCComboBox2 = (CComboBox*)GetDlgItem(IDC_COMBO_JikokuhyouOperationNumberDisplayRowsNobori);

			tstring strTemp = _T("1段");
			pCComboBox->AddString(strTemp.c_str());
			pCComboBox2->AddString(strTemp.c_str());
			strTemp = _T("2段");
			pCComboBox->AddString(strTemp.c_str());
			pCComboBox2->AddString(strTemp.c_str());
			strTemp = _T("3段");
			pCComboBox->AddString(strTemp.c_str());
			pCComboBox2->AddString(strTemp.c_str());
			strTemp = _T("4段");
			pCComboBox->AddString(strTemp.c_str());
			pCComboBox2->AddString(strTemp.c_str());
			strTemp = _T("5段");
			pCComboBox->AddString(strTemp.c_str());
			pCComboBox2->AddString(strTemp.c_str());

		}
		// コンボボックス
		{
			CComboBox* pCComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_DiagramColorNextEki);

			tstring strTemp = _T("基本色");
			pCComboBox->AddString(strTemp.c_str());
			strTemp = _T("個別色1");
			pCComboBox->AddString(strTemp.c_str());
			strTemp = _T("個別色2");
			pCComboBox->AddString(strTemp.c_str());
			strTemp = _T("個別色3");
			pCComboBox->AddString(strTemp.c_str());
			strTemp = _T("個別色4");
			pCComboBox->AddString(strTemp.c_str());

		}
		//	編集を開始
		m_PropEditUiInternal.StartEdit();

		// --------------------------------
		return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
					  // 例外: OCX プロパティ ページの戻り値は FALSE となります
	}

	void CDlgEkiProp::OnOK()
	{
		int iResult = m_PropEditUiInternal.EndEdit();
		if (iResult >= 0)
		{
			CDialog::OnOK();
		}

	}

	void CDlgEkiProp::OnShowWindow(BOOL bShow, UINT nStatus)
	{
		CDialog::OnShowWindow(bShow, nStatus);



		if (bShow)
		{
			// --------------------------------
			//	フォーカスを移動
			// --------------------------------
			//駅名
			if (m_iFocusItem == 0) {
				CEdit* pControl = (CEdit*)GetDlgItem(IDC_EDIT_Ekimei);
				GotoDlgCtrl(pControl);
				if (m_pCKeyinputSenderToModalDlg != NULL) {
					m_pCKeyinputSenderToModalDlg->registerCtrl(pControl->GetSafeHwnd());
				}
			}
			//駅時刻形式
			if (m_iFocusItem == 1) {
				CWnd* pControl = GetDlgItem(IDC_RADIO_Jikokukeisiki);
				GotoDlgCtrl(pControl);
				if (m_pCKeyinputSenderToModalDlg != NULL) {
					m_pCKeyinputSenderToModalDlg->registerCtrl(pControl->GetSafeHwnd());
				}
			}
			//駅規模
			if (m_iFocusItem == 2) {
				CWnd* pControl = GetDlgItem(IDC_RADIO_Ekikibo);
				GotoDlgCtrl(pControl);
				if (m_pCKeyinputSenderToModalDlg != NULL) {
					m_pCKeyinputSenderToModalDlg->registerCtrl(pControl->GetSafeHwnd());
				}
			}
			//駅規模
			if (m_iFocusItem == 3) {
				CWnd* pControl = GetDlgItem(IDC_CHECK_Brunch);
				GotoDlgCtrl(pControl);
				if (m_pCKeyinputSenderToModalDlg != NULL) {
					m_pCKeyinputSenderToModalDlg->registerCtrl(pControl->GetSafeHwnd());
				}
			}
			//駅規模
			if (m_iFocusItem == 4) {
				CWnd* pControl = GetDlgItem(IDC_CHECK_Loop);
				GotoDlgCtrl(pControl);
				if (m_pCKeyinputSenderToModalDlg != NULL) {
					m_pCKeyinputSenderToModalDlg->registerCtrl(pControl->GetSafeHwnd());
				}
			}

			m_iFocusItem = -1;
		}

	}

	void CDlgEkiProp::OnEnKillfocusEditEkimei()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	//void CDlgEkiProp::OnBnClickedCheckKyoukaisen()
	//{
	//	m_PropEditUiInternal.OnUiChanged();
	//}

	void CDlgEkiProp::OnBnClickedRadioJikokukeisiki()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	void CDlgEkiProp::OnBnClickedRadioJikokukeisiki2()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	void CDlgEkiProp::OnBnClickedRadioJikokukeisiki3()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	void CDlgEkiProp::OnBnClickedRadioJikokukeisiki4()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	//add_by_d_mania
	void CDlgEkiProp::OnBnClickedRadioJikokukeisiki5()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	void CDlgEkiProp::OnBnClickedRadioJikokukeisiki6()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	void CDlgEkiProp::OnBnClickedRadioEkikibo()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	void CDlgEkiProp::OnBnClickedRadioEkikibo2()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	void CDlgEkiProp::OnCbnSelchangeComboDiagramressyajouhouhyoujikudari()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	void CDlgEkiProp::OnCbnSelchangeComboDiagramressyajouhouhyoujinobori()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	void CDlgEkiProp::OnBnClickedCheckAdjustbyekijikokukeisiki()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	void CDlgEkiProp::OnBnClickedCheckBrunch()
	{
		m_PropEditUiInternal.OnUiChanged();
	}
	void CDlgEkiProp::OnCbnSelchangeComboBrunchCoreEkiIndex()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	void CDlgEkiProp::OnBnClickedCheckLoop()
	{
		m_PropEditUiInternal.OnUiChanged();
	}
	void CDlgEkiProp::OnCbnSelchangeComboLoopOriginEkiIndex()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	void CDlgEkiProp::OnBnClickedCheckJikokuhyouTrackDisplayKudari()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	void CDlgEkiProp::OnBnClickedCheckJikokuhyouTrackDisplayNobori()
	{
		m_PropEditUiInternal.OnUiChanged();
	}
	void CDlgEkiProp::OnBnClickedCheckDiagramTrackDisplay()
	{
		m_PropEditUiInternal.OnUiChanged();
	}
	void CDlgEkiProp::OnEnKillfocusEditEkimeiJikokuhyouRyaku()
	{
		m_PropEditUiInternal.OnUiChanged();
	}
	void CDlgEkiProp::OnEnKillfocusEditEkimeiDiagramRyaku()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	void ViewEki::CDlgEkiProp::OnBnClickedButtonEkitrack2add()
	{
		int iRv = 0;

		tstring strTrackName = _T("");
		tstring strTrackRyakusyou = _T("");
		tstring strTrackNoboriRyakusyou = _T("");
		bool bDiagramTrackOmit = false;

		int idx = m_ListEkiTrack2.GetNextItem(-1, LVNI_SELECTED | LVNI_ALL);
		if (idx >= 0 && idx < m_ListEkiTrack2.GetItemCount())
		{
			//idxが既存番線の範囲内の場合、その番線の番線名・略称を初期値とします
			strTrackName = m_ListEkiTrack2.GetItemText(idx, 0);
			strTrackRyakusyou = m_ListEkiTrack2.GetItemText(idx, 1);
			strTrackNoboriRyakusyou = m_ListEkiTrack2.GetItemText(idx, 2);
			bDiagramTrackOmit = m_ListEkiTrack2.GetItemText(idx, 4) == nameDiagramTrackOmit;
		}

		CDlgEkiTrack2Prop2 aDlg(
			strTrackName.c_str(),
			strTrackRyakusyou.c_str(),
			strTrackNoboriRyakusyou.c_str(),
			bDiagramTrackOmit,
			this);
		if (aDlg.DoModal() == IDOK)
		{
			int idxa = m_ListEkiTrack2.GetItemCount();
			m_ListEkiTrack2.InsertItem(idxa, aDlg.getTrackName());

			if (iRv >= 0)
			{
				m_ListEkiTrack2.SetItemText(idxa, 1, aDlg.getTrackRyakusyou());
				m_ListEkiTrack2.SetItemText(idxa, 2, aDlg.getTrackNoboriRyakusyou());
				m_ListEkiTrack2.SetItemText(idxa, 3, _T("副本線/側線"));
				if (aDlg.getDiagramTrackOmit())
				{
					m_ListEkiTrack2.SetItemText(idxa, 4, nameDiagramTrackOmit);
				}
				else
				{
					m_ListEkiTrack2.SetItemText(idxa, 4, _T(""));
				}
			}

			m_PropEditUiInternal.OnUiChanged();
		}
	}

	void ViewEki::CDlgEkiProp::OnBnClickedButtonEkitrack2prop()
	{
		int iRv = 0;
		int idx = m_ListEkiTrack2.GetNextItem(-1, LVNI_SELECTED | LVNI_ALL);

		if (idx < 0 || idx >= m_ListEkiTrack2.GetItemCount())
		{
			iRv = -1;//idxが範囲外です
		}

		if (iRv >= 0)
		{
			CString strTrackName = m_ListEkiTrack2.GetItemText(idx, 0);
			CString strTrackRyakusyou = m_ListEkiTrack2.GetItemText(idx, 1);
			CString strTrackNoboriRyakusyou = m_ListEkiTrack2.GetItemText(idx, 2);
			bool bDiagramTrackOmit = m_ListEkiTrack2.GetItemText(idx, 4) == nameDiagramTrackOmit;

			CDlgEkiTrack2Prop2 aDlg(
				strTrackName,
				strTrackRyakusyou,
				strTrackNoboriRyakusyou,
				bDiagramTrackOmit,
				this);
			if (aDlg.DoModal() == IDOK)
			{
				m_ListEkiTrack2.SetItemText(idx, 0, aDlg.getTrackName());
				m_ListEkiTrack2.SetItemText(idx, 1, aDlg.getTrackRyakusyou());
				m_ListEkiTrack2.SetItemText(idx, 2, aDlg.getTrackNoboriRyakusyou());
				if (aDlg.getDiagramTrackOmit())
				{
					m_ListEkiTrack2.SetItemText(idx, 4, nameDiagramTrackOmit);
				}
				else
				{
					m_ListEkiTrack2.SetItemText(idx, 4, _T(""));
				}

				if (iRv >= 0)
				{
					m_PropEditUiInternal.OnUiChanged();
				}
			}
		}
	}

	void ViewEki::CDlgEkiProp::OnBnClickedButtonEkitrack2clear()
	{
		int iRv = 0;
		int idx = m_ListEkiTrack2.GetNextItem(-1, LVNI_SELECTED | LVNI_ALL);

		if (idx < 0 || idx >= m_ListEkiTrack2.GetItemCount())
		{
			iRv = -1;//idxが範囲外です
		}
		if (iRv >= 0)
		{
			if (m_ListEkiTrack2.GetItemCount() == 1)
			{
				iRv = -2;//番線数が1の場合は削除できません
			}
		}

		if (iRv >= 0)
		{
			if (m_ListEkiTrack2.GetItemText(idx, 3) != MfcUtil::LoadCString(IDS_WORD_SubMain))
			{
				iRv = -3;//対象番線が主本線の場合は削除できません
			}
		}

		if (iRv >= 0)
		{
			int iEkiTrack2Index = -1;
			//選択された番線が、駅編集開始時に存在していたかどうかを調べます。
			//m_iEkiTrack2Mapの中に、"idx"の値を持つものがある場合は最初から存在しています。
			for (int idxm = 0; idxm < (int)m_iEkiTrack2Map.size(); idxm++)
			{
				if (m_iEkiTrack2Map[idxm] == idx)
				{
					iEkiTrack2Index = idxm;
					break;
				}
			}
			//選択された番線が、駅編集開始時から存在する場合のみ、
			//その番線を使用している列車が存在するかを調べます。
			if (iEkiTrack2Index >= 0)
			{
				int iDiaIndex = -1;
				ERessyahoukou	eRessyahoukou = Ressyahoukou_Kudari;

				const CentDedRosen* pCentDedRosen =
					getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen();
				std::deque<int> iEkiIndexBrunchLoop;
				int iSize = pCentDedRosen->getCentDedEkiCont()
					->getEkiIndexBrunchLoop(m_iEkiIndex, iEkiIndexBrunchLoop);
				for (int idxbl = 0; idxbl < iSize; idxbl++)
				{
					if (pCentDedRosen->getCentDedDiaCont()
						->isExistRessyaOfEkiTrack2(
							iEkiIndexBrunchLoop[idxbl], iEkiTrack2Index,
							&iDiaIndex, &eRessyahoukou, NULL)
						!= 0)
					{
						iRv = -4;	//削除しようとしている番線の列車が存在します
						break;
					}

				}

				//	エラーメッセージを構成
				if (iRv == -4)
				{
					CString	strEkiName = pCentDedRosen->getCentDedEkiCont()
						->get(m_iEkiIndex).getEkimei().c_str();
					CString	strEkiTrack2Name =
						m_ListEkiTrack2.GetItemText(idx, 0);
					CString	strDiaName =
						pCentDedRosen->getCentDedDiaCont()->getMuPtr()->
						get(iDiaIndex)->getName().c_str();
					CString	strRessyahoukou;
					//if (eRessyahoukou == Ressyahoukou_Kudari)
					//{
					//	strRessyahoukou.LoadString(IDS_WORD_Kudari);
					//}
					//else
					//{
					//	strRessyahoukou.LoadString(IDS_WORD_Nobori);
					//}
					if (eRessyahoukou == Ressyahoukou_Kudari)
					{
						if (pCentDedRosen->getKudariDiaAlias().empty())
						{
							strRessyahoukou.LoadString(IDS_WORD_Kudari);
						}
						else
						{
							strRessyahoukou = pCentDedRosen->getKudariDiaAlias().c_str();
						}
					}
					else
					{
						if (pCentDedRosen->getNoboriDiaAlias().empty())
						{
							strRessyahoukou.LoadString(IDS_WORD_Nobori);
						}
						else
						{
							strRessyahoukou = pCentDedRosen->getNoboriDiaAlias().c_str();
						}
					}
					CString	strMsg;
					strMsg.Format(IDS_ERR_ExistRessyaOfEkiTrack,
						strEkiName, strEkiTrack2Name, strDiaName, strRessyahoukou);
					MessageBox(strMsg, NULL, MB_ICONSTOP | MB_OK);
				}
			}
		}

		if (iRv >= 0)
		{
			m_ListEkiTrack2.DeleteItem(idx);

			//削除された番線が、編集開始時から存在していた番線の場合は、
			//m_iEkiTrack2Mapの当該箇所を-1にします。
			//また、削除箇所より後ろにある、編集開始時から存在していた番線は
			//m_iEkiTrack2Mapの当該値を-1します。
			for (int idxm = 0; idxm < (int)m_iEkiTrack2Map.size(); idxm++)
			{
				if (m_iEkiTrack2Map[idxm] == idx)
				{
					m_iEkiTrack2Map[idxm] = -1;
				}
				else if (m_iEkiTrack2Map[idxm] > idx)
				{
					m_iEkiTrack2Map[idxm] -= 1;
				}
			}

		}

		if (iRv >= 0)
		{
			m_PropEditUiInternal.OnUiChanged();
		}

	}

	void ViewEki::CDlgEkiProp::OnBnClickedButtonEkitrack2up()
	{
		// TODO: ここにコントロール通知ハンドラー コードを追加します。
		int iRv = 0;
		int idx = m_ListEkiTrack2.GetNextItem(-1, LVNI_SELECTED | LVNI_ALL);
		if (idx < 1 || idx >= m_ListEkiTrack2.GetItemCount())
		{
			iRv = -1;//idxが範囲外です
		}

		if (iRv >= 0)
		{
			tstring strTrackNameUp = m_ListEkiTrack2.GetItemText(idx - 1, 0);
			tstring strTrackRyakusyouUp = m_ListEkiTrack2.GetItemText(idx - 1, 1);
			tstring strTrackNoboriRyakusyouUp = m_ListEkiTrack2.GetItemText(idx - 1, 2);
			tstring strMainTrackUp = m_ListEkiTrack2.GetItemText(idx - 1, 3);
			bool bDiagramTrackOmitUp = m_ListEkiTrack2.GetItemText(idx - 1, 4) == nameDiagramTrackOmit;

			tstring strTrackNameDown = m_ListEkiTrack2.GetItemText(idx, 0);
			tstring strTrackRyakusyouDown = m_ListEkiTrack2.GetItemText(idx, 1);
			tstring strTrackNoboriRyakusyouDown = m_ListEkiTrack2.GetItemText(idx, 2);
			tstring strMainTrackDown = m_ListEkiTrack2.GetItemText(idx, 3);
			bool bDiagramTrackOmitDown = m_ListEkiTrack2.GetItemText(idx, 4) == nameDiagramTrackOmit;

			m_ListEkiTrack2.SetItemText(idx - 1, 0, strTrackNameDown.c_str());
			m_ListEkiTrack2.SetItemText(idx - 1, 1, strTrackRyakusyouDown.c_str());
			m_ListEkiTrack2.SetItemText(idx - 1, 2, strTrackNoboriRyakusyouDown.c_str());
			m_ListEkiTrack2.SetItemText(idx - 1, 3, strMainTrackDown.c_str());
			if (bDiagramTrackOmitDown)
			{
				m_ListEkiTrack2.SetItemText(idx - 1, 4, nameDiagramTrackOmit);
			}
			else
			{
				m_ListEkiTrack2.SetItemText(idx - 1, 4, _T(""));
			}

			m_ListEkiTrack2.SetItemText(idx, 0, strTrackNameUp.c_str());
			m_ListEkiTrack2.SetItemText(idx, 1, strTrackRyakusyouUp.c_str());
			m_ListEkiTrack2.SetItemText(idx, 2, strTrackNoboriRyakusyouUp.c_str());
			m_ListEkiTrack2.SetItemText(idx, 3, strMainTrackUp.c_str());
			if (bDiagramTrackOmitUp)
			{
				m_ListEkiTrack2.SetItemText(idx, 4, nameDiagramTrackOmit);
			}
			else
			{
				m_ListEkiTrack2.SetItemText(idx, 4, _T(""));
			}

			m_ListEkiTrack2.SetItemState(idx - 1, LVIS_SELECTED, LVIS_SELECTED);

			//上へ移動した番線及び入れ替わりで下に移動した番線が、編集開始時からある番線の場合は、
			//m_iEkiTrack2Mapを更新します。
			for (int idxm = 0; idxm < (int)m_iEkiTrack2Map.size(); idxm++)
			{
				if (m_iEkiTrack2Map[idxm] == idx)
				{
					m_iEkiTrack2Map[idxm] -= 1;
				}
				else if (m_iEkiTrack2Map[idxm] == idx - 1)
				{
					m_iEkiTrack2Map[idxm] += 1;
				}
			}
		}

		if (iRv >= 0)
		{
			m_PropEditUiInternal.OnUiChanged();
		}
	}


	void ViewEki::CDlgEkiProp::OnBnClickedButtonEkitrack2down()
	{
		// TODO: ここにコントロール通知ハンドラー コードを追加します。
		int iRv = 0;
		int idx = m_ListEkiTrack2.GetNextItem(-1, LVNI_SELECTED | LVNI_ALL);
		if (idx < 0 || idx >= m_ListEkiTrack2.GetItemCount() - 1)
		{
			iRv = -1;//idxが範囲外です
		}

		if (iRv >= 0)
		{
			tstring strTrackNameUp = m_ListEkiTrack2.GetItemText(idx, 0);
			tstring strTrackRyakusyouUp = m_ListEkiTrack2.GetItemText(idx, 1);
			tstring strTrackNoboriRyakusyouUp = m_ListEkiTrack2.GetItemText(idx, 2);
			tstring strMainTrackUp = m_ListEkiTrack2.GetItemText(idx, 3);
			bool bDiagramTrackOmitUp = m_ListEkiTrack2.GetItemText(idx, 4) == nameDiagramTrackOmit;

			tstring strTrackNameDown = m_ListEkiTrack2.GetItemText(idx + 1, 0);
			tstring strTrackRyakusyouDown = m_ListEkiTrack2.GetItemText(idx + 1, 1);
			tstring strTrackNoboriRyakusyouDown = m_ListEkiTrack2.GetItemText(idx + 1, 2);
			tstring strMainTrackDown = m_ListEkiTrack2.GetItemText(idx + 1, 3);
			bool bDiagramTrackOmitDown = m_ListEkiTrack2.GetItemText(idx + 1, 4) == nameDiagramTrackOmit;

			m_ListEkiTrack2.SetItemText(idx, 0, strTrackNameDown.c_str());
			m_ListEkiTrack2.SetItemText(idx, 1, strTrackRyakusyouDown.c_str());
			m_ListEkiTrack2.SetItemText(idx, 2, strTrackNoboriRyakusyouDown.c_str());
			m_ListEkiTrack2.SetItemText(idx, 3, strMainTrackDown.c_str());
			if (bDiagramTrackOmitDown)
			{
				m_ListEkiTrack2.SetItemText(idx, 4, nameDiagramTrackOmit);
			}
			else
			{
				m_ListEkiTrack2.SetItemText(idx, 4, _T(""));
			}

			m_ListEkiTrack2.SetItemText(idx + 1, 0, strTrackNameUp.c_str());
			m_ListEkiTrack2.SetItemText(idx + 1, 1, strTrackRyakusyouUp.c_str());
			m_ListEkiTrack2.SetItemText(idx + 1, 2, strTrackNoboriRyakusyouUp.c_str());
			m_ListEkiTrack2.SetItemText(idx + 1, 3, strMainTrackUp.c_str());
			if (bDiagramTrackOmitUp)
			{
				m_ListEkiTrack2.SetItemText(idx + 1, 4, nameDiagramTrackOmit);
			}
			else
			{
				m_ListEkiTrack2.SetItemText(idx + 1, 4, _T(""));
			}

			m_ListEkiTrack2.SetItemState(idx + 1, LVIS_SELECTED, LVIS_SELECTED);

			//下へ移動した番線及び入れ替わりで上に移動した番線が、編集開始時からある番線の場合は、
			//m_iEkiTrack2Mapを更新します。
			for (int idxm = 0; idxm < (int)m_iEkiTrack2Map.size(); idxm++)
			{
				if (m_iEkiTrack2Map[idxm] == idx)
				{
					m_iEkiTrack2Map[idxm] += 1;
				}
				else if (m_iEkiTrack2Map[idxm] == idx + 1)
				{
					m_iEkiTrack2Map[idxm] -= 1;
				}
			}
		}

		if (iRv >= 0)
		{
			m_PropEditUiInternal.OnUiChanged();
		}
	}

	void ViewEki::CDlgEkiProp::OnBnClickedButtonEkitrack2downmain()
	{
		int iRv = 0;
		int idx = m_ListEkiTrack2.GetNextItem(-1, LVNI_SELECTED | LVNI_ALL);
		int iSizeEkiTrack2 = m_ListEkiTrack2.GetItemCount();
		if (idx < 0 || idx >= iSizeEkiTrack2)
		{
			iRv = -1;//idxが範囲外です
		}

		if (iRv >= 0)
		{
			for (int idxEkiTrack2 = 0; idxEkiTrack2 < iSizeEkiTrack2; idxEkiTrack2++)
			{
				if (idxEkiTrack2 == idx)
				{
					continue;
				}
				if (m_ListEkiTrack2.GetItemText(idxEkiTrack2, 3)
					== MfcUtil::LoadCString(IDS_WORD_DownMain))
				{
					m_ListEkiTrack2.SetItemText(idxEkiTrack2, 3, (LPCTSTR)MfcUtil::LoadCString(IDS_WORD_SubMain));
				}
				else if (m_ListEkiTrack2.GetItemText(idxEkiTrack2, 3)
					== MfcUtil::LoadCString(IDS_WORD_DownUpMain))
				{
					m_ListEkiTrack2.SetItemText(idxEkiTrack2, 3, (LPCTSTR)MfcUtil::LoadCString(IDS_WORD_UpMain));
				}
			}

			if (m_ListEkiTrack2.GetItemText(idx, 3)
				== MfcUtil::LoadCString(IDS_WORD_SubMain))
			{
				m_ListEkiTrack2.SetItemText(idx, 3, (LPCTSTR)MfcUtil::LoadCString(IDS_WORD_DownMain));
			}
			else if (m_ListEkiTrack2.GetItemText(idx, 3)
				== MfcUtil::LoadCString(IDS_WORD_UpMain))
			{
				m_ListEkiTrack2.SetItemText(idx, 3, (LPCTSTR)MfcUtil::LoadCString(IDS_WORD_DownUpMain));
			}
		}

		if (iRv >= 0)
		{
			m_PropEditUiInternal.OnUiChanged();
		}
	}

	void ViewEki::CDlgEkiProp::OnBnClickedButtonEkitrack2upmain()
	{
		int iRv = 0;
		int idx = m_ListEkiTrack2.GetNextItem(-1, LVNI_SELECTED | LVNI_ALL);
		int iSizeEkiTrack2 = m_ListEkiTrack2.GetItemCount();
		if (idx < 0 || idx >= iSizeEkiTrack2)
		{
			iRv = -1;//idxが範囲外です
		}

		if (iRv >= 0)
		{
			for (int idxEkiTrack2 = 0; idxEkiTrack2 < iSizeEkiTrack2; idxEkiTrack2++)
			{
				if (idxEkiTrack2 == idx)
				{
					continue;
				}
				if (m_ListEkiTrack2.GetItemText(idxEkiTrack2, 3)
					== MfcUtil::LoadCString(IDS_WORD_UpMain))
				{
					m_ListEkiTrack2.SetItemText(idxEkiTrack2, 3, (LPCTSTR)MfcUtil::LoadCString(IDS_WORD_SubMain));
				}
				else if (m_ListEkiTrack2.GetItemText(idxEkiTrack2, 3)
					== MfcUtil::LoadCString(IDS_WORD_DownUpMain))
				{
					m_ListEkiTrack2.SetItemText(idxEkiTrack2, 3, (LPCTSTR)MfcUtil::LoadCString(IDS_WORD_DownMain));
				}
			}

			if (m_ListEkiTrack2.GetItemText(idx, 3)
				== MfcUtil::LoadCString(IDS_WORD_SubMain))
			{
				m_ListEkiTrack2.SetItemText(idx, 3, MfcUtil::LoadCString(IDS_WORD_UpMain));
			}
			else if (m_ListEkiTrack2.GetItemText(idx, 3)
				== MfcUtil::LoadCString(IDS_WORD_DownMain))
			{
				m_ListEkiTrack2.SetItemText(idx, 3, (LPCTSTR)MfcUtil::LoadCString(IDS_WORD_DownUpMain));
			}
		}

		if (iRv >= 0)
		{
			m_PropEditUiInternal.OnUiChanged();
		}
	}

	void CDlgEkiProp::OnBnClickedButtonDiagramTrackOmitSwitch()
	{
		int iRv = 0;
		int idx = m_ListEkiTrack2.GetNextItem(-1, LVNI_SELECTED | LVNI_ALL);
		int iSizeEkiTrack2 = m_ListEkiTrack2.GetItemCount();
		if (idx < 0 || idx >= iSizeEkiTrack2)
		{
			iRv = -1;//idxが範囲外です
		}

		if (iRv >= 0)
		{
			if (m_ListEkiTrack2.GetItemText(idx, 4).IsEmpty())
			{
				m_ListEkiTrack2.SetItemText(idx, 4, nameDiagramTrackOmit);
			}
			else
			{
				m_ListEkiTrack2.SetItemText(idx, 4, _T(""));
			}
		}

		if (iRv >= 0)
		{
			m_PropEditUiInternal.OnUiChanged();
		}
	}


	void ViewEki::CDlgEkiProp::OnLvnItemchangedListEkitrack2(NMHDR* pNMHDR, LRESULT* pResult)
	{
		LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
		// TODO: ここにコントロール通知ハンドラー コードを追加します。

		int iRv = 0;
		int idx = m_ListEkiTrack2.GetNextItem(-1, LVNI_SELECTED | LVNI_ALL);
		int iSizeEkiTrack2 = m_ListEkiTrack2.GetItemCount();

		if (idx < 0 || idx >= iSizeEkiTrack2)
		{
			iRv = -1;//idxが範囲外です
		}

		if (iRv >= 0)
		{
			if (iSizeEkiTrack2 == 1)
			{
				//番線数が1の場合は、削除・上へ・下へが無効
				GetDlgItem(IDC_BUTTON_EkiTrack2Clear)->EnableWindow(false);
				GetDlgItem(IDC_BUTTON_EkiTrack2Up)->EnableWindow(false);
				GetDlgItem(IDC_BUTTON_EkiTrack2Down)->EnableWindow(false);
				GetDlgItem(IDC_BUTTON_EkiTrack2DownMain)->EnableWindow(false);
				GetDlgItem(IDC_BUTTON_EkiTrack2UpMain)->EnableWindow(false);
			}
			else if (idx == 0)
			{
				//最上位番線の場合は、上へが無効+削除が主本線設定依存。
				GetDlgItem(IDC_BUTTON_EkiTrack2Up)->EnableWindow(false);
				GetDlgItem(IDC_BUTTON_EkiTrack2Down)->EnableWindow(true);

				if (m_ListEkiTrack2.GetItemText(idx, 3) == MfcUtil::LoadCString(IDS_WORD_SubMain))
				{
					GetDlgItem(IDC_BUTTON_EkiTrack2Clear)->EnableWindow(true);
					GetDlgItem(IDC_BUTTON_EkiTrack2DownMain)->EnableWindow(true);
					GetDlgItem(IDC_BUTTON_EkiTrack2UpMain)->EnableWindow(true);
				}
				else if (m_ListEkiTrack2.GetItemText(idx, 3) == MfcUtil::LoadCString(IDS_WORD_DownMain))
				{
					GetDlgItem(IDC_BUTTON_EkiTrack2Clear)->EnableWindow(false);
					GetDlgItem(IDC_BUTTON_EkiTrack2DownMain)->EnableWindow(false);
					GetDlgItem(IDC_BUTTON_EkiTrack2UpMain)->EnableWindow(true);
				}
				else if (m_ListEkiTrack2.GetItemText(idx, 3) == MfcUtil::LoadCString(IDS_WORD_UpMain))
				{
					GetDlgItem(IDC_BUTTON_EkiTrack2Clear)->EnableWindow(false);
					GetDlgItem(IDC_BUTTON_EkiTrack2DownMain)->EnableWindow(true);
					GetDlgItem(IDC_BUTTON_EkiTrack2UpMain)->EnableWindow(false);
				}
				else if (m_ListEkiTrack2.GetItemText(idx, 3) == MfcUtil::LoadCString(IDS_WORD_DownUpMain))
				{
					GetDlgItem(IDC_BUTTON_EkiTrack2Clear)->EnableWindow(false);
					GetDlgItem(IDC_BUTTON_EkiTrack2DownMain)->EnableWindow(false);
					GetDlgItem(IDC_BUTTON_EkiTrack2UpMain)->EnableWindow(false);
				}
			}
			else if (idx == iSizeEkiTrack2 - 1)
			{
				//最下位番線の場合は、下へが無効+削除が主本線設定依存。
				GetDlgItem(IDC_BUTTON_EkiTrack2Up)->EnableWindow(true);
				GetDlgItem(IDC_BUTTON_EkiTrack2Down)->EnableWindow(false);

				if (m_ListEkiTrack2.GetItemText(idx, 3) == MfcUtil::LoadCString(IDS_WORD_SubMain))
				{
					GetDlgItem(IDC_BUTTON_EkiTrack2Clear)->EnableWindow(true);
					GetDlgItem(IDC_BUTTON_EkiTrack2DownMain)->EnableWindow(true);
					GetDlgItem(IDC_BUTTON_EkiTrack2UpMain)->EnableWindow(true);
				}
				else if (m_ListEkiTrack2.GetItemText(idx, 3) == MfcUtil::LoadCString(IDS_WORD_DownMain))
				{
					GetDlgItem(IDC_BUTTON_EkiTrack2Clear)->EnableWindow(false);
					GetDlgItem(IDC_BUTTON_EkiTrack2DownMain)->EnableWindow(false);
					GetDlgItem(IDC_BUTTON_EkiTrack2UpMain)->EnableWindow(true);
				}
				else if (m_ListEkiTrack2.GetItemText(idx, 3) == MfcUtil::LoadCString(IDS_WORD_UpMain))
				{
					GetDlgItem(IDC_BUTTON_EkiTrack2Clear)->EnableWindow(false);
					GetDlgItem(IDC_BUTTON_EkiTrack2DownMain)->EnableWindow(true);
					GetDlgItem(IDC_BUTTON_EkiTrack2UpMain)->EnableWindow(false);
				}
				else if (m_ListEkiTrack2.GetItemText(idx, 3) == MfcUtil::LoadCString(IDS_WORD_DownUpMain))
				{
					GetDlgItem(IDC_BUTTON_EkiTrack2Clear)->EnableWindow(false);
					GetDlgItem(IDC_BUTTON_EkiTrack2DownMain)->EnableWindow(false);
					GetDlgItem(IDC_BUTTON_EkiTrack2UpMain)->EnableWindow(false);
				}

			}
			else if (idx > 0 && idx < iSizeEkiTrack2 - 1)
			{
				//中間の場合は、削除が主本線設定依存。
				GetDlgItem(IDC_BUTTON_EkiTrack2Up)->EnableWindow(true);
				GetDlgItem(IDC_BUTTON_EkiTrack2Down)->EnableWindow(true);

				if (m_ListEkiTrack2.GetItemText(idx, 3) == MfcUtil::LoadCString(IDS_WORD_SubMain))
				{
					GetDlgItem(IDC_BUTTON_EkiTrack2Clear)->EnableWindow(true);
					GetDlgItem(IDC_BUTTON_EkiTrack2DownMain)->EnableWindow(true);
					GetDlgItem(IDC_BUTTON_EkiTrack2UpMain)->EnableWindow(true);
				}
				else if (m_ListEkiTrack2.GetItemText(idx, 3) == MfcUtil::LoadCString(IDS_WORD_DownMain))
				{
					GetDlgItem(IDC_BUTTON_EkiTrack2Clear)->EnableWindow(false);
					GetDlgItem(IDC_BUTTON_EkiTrack2DownMain)->EnableWindow(false);
					GetDlgItem(IDC_BUTTON_EkiTrack2UpMain)->EnableWindow(true);
				}
				else if (m_ListEkiTrack2.GetItemText(idx, 3) == MfcUtil::LoadCString(IDS_WORD_UpMain))
				{
					GetDlgItem(IDC_BUTTON_EkiTrack2Clear)->EnableWindow(false);
					GetDlgItem(IDC_BUTTON_EkiTrack2DownMain)->EnableWindow(true);
					GetDlgItem(IDC_BUTTON_EkiTrack2UpMain)->EnableWindow(false);
				}
				else if (m_ListEkiTrack2.GetItemText(idx, 3) == MfcUtil::LoadCString(IDS_WORD_DownUpMain))
				{
					GetDlgItem(IDC_BUTTON_EkiTrack2Clear)->EnableWindow(false);
					GetDlgItem(IDC_BUTTON_EkiTrack2DownMain)->EnableWindow(false);
					GetDlgItem(IDC_BUTTON_EkiTrack2UpMain)->EnableWindow(false);
				}

			}
			else
			{
				//それ以外の場合は、削除・上へ・下へが無効
				GetDlgItem(IDC_BUTTON_EkiTrack2Clear)->EnableWindow(false);
				GetDlgItem(IDC_BUTTON_EkiTrack2Up)->EnableWindow(false);
				GetDlgItem(IDC_BUTTON_EkiTrack2Down)->EnableWindow(false);
				GetDlgItem(IDC_BUTTON_EkiTrack2DownMain)->EnableWindow(false);
				GetDlgItem(IDC_BUTTON_EkiTrack2UpMain)->EnableWindow(false);
			}
		}
		*pResult = 0;
	}

	void ViewEki::CDlgEkiProp::OnBnClickedButtonOuterTerminalEkimeiadd()
	{
		int iRv = 0;

		CDlgOuterEkimeiProp aDlg(
			_T(""),
			_T(""),
			_T(""),
			this);
		if (aDlg.DoModal() == IDOK)
		{
			int idxa = m_ListOuterTerminalEkimei2.GetItemCount();

			//CListBox* pListBox = (CListBox*)GetDlgItem(IDC_LIST_OuterTerminalEkimei);

			bool bAbort = false;
			for (int idx = 0; idx < idxa; idx++)
			{
				CString strTemp;
				strTemp = m_ListOuterTerminalEkimei2.GetItemText(idx, 0);
				//pListBox->GetText(idx, strTemp);
				if (aDlg.getOuterEkimei() == strTemp)
				{
					bAbort = true;
				}
			}
			if (!bAbort)
			{
				//pListBox->InsertString(-1, aDlg.getOuterEkimei());
				m_ListOuterTerminalEkimei2.InsertItem(idxa, aDlg.getOuterEkimei());

				if (iRv >= 0)
				{
					m_ListOuterTerminalEkimei2.SetItemText(idxa, 1, aDlg.getOuterJikokuRyakusyou());
					m_ListOuterTerminalEkimei2.SetItemText(idxa, 2, aDlg.getOuterDiaRyakusyou());
				}
			}
			else
			{

				CString	strMsg;
				GetDlgItem(IDC_ERROR_OuterEkimeiExist)->GetWindowText(strMsg);
				MessageBox(strMsg, NULL, MB_ICONSTOP | MB_OK);
			}



			m_PropEditUiInternal.OnUiChanged();
		}

	}
	void ViewEki::CDlgEkiProp::OnBnClickedButtonOuterTerminalEkimeiprop()
	{
		int iRv = 0;

		int idx = m_ListOuterTerminalEkimei2.GetNextItem(-1, LVNI_SELECTED | LVNI_ALL);
		//CListBox* pListBox = (CListBox*)GetDlgItem(IDC_LIST_OuterTerminalEkimei);
		//int idx = pListBox->GetCurSel();

		if (idx >= 0 && idx < m_ListOuterTerminalEkimei2.GetItemCount())
			//if (idx >= 0 && idx < pListBox->GetCount())
		{
			CString strOuterEkimei = m_ListOuterTerminalEkimei2.GetItemText(idx, 0);
			CString strOuterJikokuRyakusyou = m_ListOuterTerminalEkimei2.GetItemText(idx, 1);
			CString strOuterDiaRyakusyou = m_ListOuterTerminalEkimei2.GetItemText(idx, 2);
			//CString EkimeiOld;
			//pListBox->GetText(idx, EkimeiOld);
			CDlgOuterEkimeiProp aDlg(
				strOuterEkimei,
				strOuterJikokuRyakusyou,
				strOuterDiaRyakusyou,
				this);
			if (aDlg.DoModal() == IDOK)
			{
				//m_ListOuterTerminalEkimei.SetItemText(idx, 0, aDlg.getOuterEkimei());


				m_ListOuterTerminalEkimei2.SetItemText(idx, 0, aDlg.getOuterEkimei());
				m_ListOuterTerminalEkimei2.SetItemText(idx, 1, aDlg.getOuterJikokuRyakusyou());
				m_ListOuterTerminalEkimei2.SetItemText(idx, 2, aDlg.getOuterDiaRyakusyou());

				//CListBox* pListBox = (CListBox*)GetDlgItem(IDC_LIST_OuterTerminalEkimei);
				//pListBox->DeleteString(idx);
				//pListBox->InsertString(idx, aDlg.getOuterEkimei());

				m_PropEditUiInternal.OnUiChanged();
			}
		}

	}

	void ViewEki::CDlgEkiProp::OnBnClickedButtonOuterTerminalEkimeiclear()
	{
		int iRv = 0;
		int idx = m_ListOuterTerminalEkimei2.GetNextItem(-1, LVNI_SELECTED | LVNI_ALL);

		//CListBox* pListBox = (CListBox*)GetDlgItem(IDC_LIST_OuterTerminalEkimei);
		//int idx = pListBox->GetCurSel();
		if (!(idx >= 0 && idx < m_ListOuterTerminalEkimei2.GetItemCount()))
		{
			iRv = -1;//idxが範囲外です
		}
		if (iRv >= 0)
		{
			int iOuterTerminalIndex = -1;
			//選択された駅名が、駅編集開始時に存在していたかどうかを調べます。
			//m_iOuterTerminalEkimeiMapの中に、"idx"の値を持つものがある場合は最初から存在しています。
			//その値があるMapのIndexが、元々のIndexになります。
			for (int idxm = 0; idxm < (int)m_iOuterTerminalEkimeiMap.size(); idxm++)
			{
				if (m_iOuterTerminalEkimeiMap[idxm] == idx)
				{
					iOuterTerminalIndex = idxm;
					break;
				}
			}
			//選択された駅名が、駅編集開始時から存在する場合のみ、
			//その駅名を使用している列車が存在するかを調べます。
			if (iOuterTerminalIndex >= 0)
			{
				int iDiaIndex = -1;
				ERessyahoukou	eRessyahoukou = Ressyahoukou_Kudari;

				const CentDedRosen* pCentDedRosen =
					getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen();
				std::deque<int> iEkiIndexBrunchLoop;
				int iSize = pCentDedRosen->getCentDedEkiCont()
					->getEkiIndexBrunchLoop(m_iEkiIndex, iEkiIndexBrunchLoop);

				for (int idxbl = 0; idxbl < iSize; idxbl++)
				{
					if (pCentDedRosen->getCentDedDiaCont()
						->isExistRessyaOfOuterTerminal(
							iEkiIndexBrunchLoop[idxbl], iOuterTerminalIndex,
							&iDiaIndex, &eRessyahoukou, NULL)
						!= 0)
					{
						iRv = -4;	//削除しようとしている駅を路線外発着する列車が存在します
						break;
					}
				}

				//	エラーメッセージを構成
				if (iRv == -4)
				{
					CString	strEkiName = pCentDedRosen->getCentDedEkiCont()
						->get(m_iEkiIndex).getEkimei().c_str();
					CString	strOuterTerminalEkiName = pCentDedRosen->getCentDedEkiCont()
						->get(m_iEkiIndex).getOuterTerminalEkimei(iOuterTerminalIndex).c_str();
					CString	strDiaName =
						pCentDedRosen->getCentDedDiaCont()->getMuPtr()->
						get(iDiaIndex)->getName().c_str();
					CString	strRessyahoukou;
					//if (eRessyahoukou == Ressyahoukou_Kudari)
					//{
					//	strRessyahoukou.LoadString(IDS_WORD_Kudari);
					//}
					//else
					//{
					//	strRessyahoukou.LoadString(IDS_WORD_Nobori);
					//}
					if (eRessyahoukou == Ressyahoukou_Kudari)
					{
						if (pCentDedRosen->getKudariDiaAlias().empty())
						{
							strRessyahoukou.LoadString(IDS_WORD_Kudari);
						}
						else
						{
							strRessyahoukou = pCentDedRosen->getKudariDiaAlias().c_str();
						}
					}
					else
					{
						if (pCentDedRosen->getNoboriDiaAlias().empty())
						{
							strRessyahoukou.LoadString(IDS_WORD_Nobori);
						}
						else
						{
							strRessyahoukou = pCentDedRosen->getNoboriDiaAlias().c_str();
						}
					}
					CString	strMsg;
					//%s駅で路線外発着駅「%s駅」を使用する列車が存在します(%s %s)。¥n路線外発着駅の削除はできません。
					strMsg.Format(IDS_ERR_ExistRessyaOfOuterTerminal,
						strEkiName, strOuterTerminalEkiName, strDiaName, strRessyahoukou);
					MessageBox(strMsg, NULL, MB_ICONSTOP | MB_OK);
				}
			}
			//当該路線外発着駅が、使われているかどうかを確認する。
			//使用されている場合はiRv=-1
		}
		if (iRv >= 0)
		{
			m_ListOuterTerminalEkimei2.DeleteItem(idx);

			//CListBox* pListBox = (CListBox*)GetDlgItem(IDC_LIST_OuterTerminalEkimei);
			//pListBox->DeleteString(idx);

			//削除された駅名が、編集開始時から存在していた場合は、
			//m_iOuterTerminalEkimeiMapの当該箇所を-1にします。
			//また、削除箇所より後ろにある、編集開始時から存在していた駅名は
			//m_iOuterTerminalEkimeiMapの当該値を-1します。

			for (int idxm = 0; idxm < (int)m_iOuterTerminalEkimeiMap.size(); idxm++)
			{
				if (m_iOuterTerminalEkimeiMap[idxm] == idx)
				{
					m_iOuterTerminalEkimeiMap[idxm] = -1;
				}
				else if (m_iOuterTerminalEkimeiMap[idxm] > idx)
				{
					m_iOuterTerminalEkimeiMap[idxm] -= 1;
				}
			}
		}

		if (iRv >= 0)
		{
			m_PropEditUiInternal.OnUiChanged();
		}

	}
	void ViewEki::CDlgEkiProp::OnBnClickedButtonOuterTerminalEkimeiup()
	{
		// TODO: ここにコントロール通知ハンドラー コードを追加します。
		int iRv = 0;
		int idx = m_ListOuterTerminalEkimei2.GetNextItem(-1, LVNI_SELECTED | LVNI_ALL);
		if (idx < 1 || idx >= m_ListOuterTerminalEkimei2.GetItemCount())
		{
			iRv = -1;//idxが範囲外です
		}

		if (iRv >= 0)
		{
			tstring strOuterEkimeiUp = m_ListOuterTerminalEkimei2.GetItemText(idx - 1, 0);
			tstring strOuterJikokuRyakuUp = m_ListOuterTerminalEkimei2.GetItemText(idx - 1, 1);
			tstring strOuterDiaRyakuUp = m_ListOuterTerminalEkimei2.GetItemText(idx - 1, 2);
			tstring strOuterEkimeiDown = m_ListOuterTerminalEkimei2.GetItemText(idx, 0);
			tstring strOuterJikokuRyakuDown = m_ListOuterTerminalEkimei2.GetItemText(idx, 1);
			tstring strOuterDiaRyakuDown = m_ListOuterTerminalEkimei2.GetItemText(idx, 2);

			m_ListOuterTerminalEkimei2.SetItemText(idx - 1, 0, strOuterEkimeiDown.c_str());
			m_ListOuterTerminalEkimei2.SetItemText(idx - 1, 1, strOuterJikokuRyakuDown.c_str());
			m_ListOuterTerminalEkimei2.SetItemText(idx - 1, 2, strOuterDiaRyakuDown.c_str());
			m_ListOuterTerminalEkimei2.SetItemText(idx, 0, strOuterEkimeiUp.c_str());
			m_ListOuterTerminalEkimei2.SetItemText(idx, 1, strOuterJikokuRyakuUp.c_str());
			m_ListOuterTerminalEkimei2.SetItemText(idx, 2, strOuterDiaRyakuUp.c_str());

			m_ListOuterTerminalEkimei2.SetItemState(idx - 1, LVIS_SELECTED, LVIS_SELECTED);

			//上へ移動した番線及び入れ替わりで下に移動した番線が、編集開始時からある番線の場合は、
			//m_iEkiTrack2Mapを更新します。
			for (int idxm = 0; idxm < (int)m_iOuterTerminalEkimeiMap.size(); idxm++)
			{
				if (m_iOuterTerminalEkimeiMap[idxm] == idx)
				{
					m_iOuterTerminalEkimeiMap[idxm] -= 1;
				}
				else if (m_iOuterTerminalEkimeiMap[idxm] == idx - 1)
				{
					m_iOuterTerminalEkimeiMap[idxm] += 1;
				}
			}
		}

		if (iRv >= 0)
		{
			m_PropEditUiInternal.OnUiChanged();
		}
	}


	void ViewEki::CDlgEkiProp::OnBnClickedButtonOuterTerminalEkimeidown()
	{
		// TODO: ここにコントロール通知ハンドラー コードを追加します。
		int iRv = 0;
		int idx = m_ListOuterTerminalEkimei2.GetNextItem(-1, LVNI_SELECTED | LVNI_ALL);
		if (idx < 0 || idx >= m_ListOuterTerminalEkimei2.GetItemCount() - 1)
		{
			iRv = -1;//idxが範囲外です
		}

		if (iRv >= 0)
		{
			tstring strOuterEkimeiUp = m_ListOuterTerminalEkimei2.GetItemText(idx, 0);
			tstring strOuterJikokuRyakuUp = m_ListOuterTerminalEkimei2.GetItemText(idx, 1);
			tstring strOuterDiaRyakuUp = m_ListOuterTerminalEkimei2.GetItemText(idx, 2);
			tstring strOuterEkimeiDown = m_ListOuterTerminalEkimei2.GetItemText(idx + 1, 0);
			tstring strOuterJikokuRyakuDown = m_ListOuterTerminalEkimei2.GetItemText(idx + 1, 1);
			tstring strOuterDiaRyakuDown = m_ListOuterTerminalEkimei2.GetItemText(idx + 1, 2);

			m_ListOuterTerminalEkimei2.SetItemText(idx, 0, strOuterEkimeiDown.c_str());
			m_ListOuterTerminalEkimei2.SetItemText(idx, 1, strOuterJikokuRyakuDown.c_str());
			m_ListOuterTerminalEkimei2.SetItemText(idx, 2, strOuterDiaRyakuDown.c_str());
			m_ListOuterTerminalEkimei2.SetItemText(idx + 1, 0, strOuterEkimeiUp.c_str());
			m_ListOuterTerminalEkimei2.SetItemText(idx + 1, 1, strOuterJikokuRyakuUp.c_str());
			m_ListOuterTerminalEkimei2.SetItemText(idx + 1, 2, strOuterDiaRyakuUp.c_str());

			m_ListOuterTerminalEkimei2.SetItemState(idx + 1, LVIS_SELECTED, LVIS_SELECTED);

			//下へ移動した番線及び入れ替わりで上に移動した番線が、編集開始時からある番線の場合は、
			//m_iEkiTrack2Mapを更新します。
			for (int idxm = 0; idxm < (int)m_iOuterTerminalEkimeiMap.size(); idxm++)
			{
				if (m_iOuterTerminalEkimeiMap[idxm] == idx)
				{
					m_iOuterTerminalEkimeiMap[idxm] += 1;
				}
				else if (m_iOuterTerminalEkimeiMap[idxm] == idx + 1)
				{
					m_iOuterTerminalEkimeiMap[idxm] -= 1;
				}
			}
		}

		if (iRv >= 0)
		{
			m_PropEditUiInternal.OnUiChanged();
		}
	}

	void ViewEki::CDlgEkiProp::OnNMDblclkListEkitrack2(NMHDR* pNMHDR, LRESULT* pResult)
	{
		LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
		// TODO: ここにコントロール通知ハンドラー コードを追加します。
		if (pNMItemActivate->iItem != -1)
		{
			CString strTrackName = m_ListEkiTrack2.GetItemText(pNMItemActivate->iItem, 0);
			CString strTrackRyakusyou = m_ListEkiTrack2.GetItemText(pNMItemActivate->iItem, 1);
			CString strTrackNoboriRyakusyou = m_ListEkiTrack2.GetItemText(pNMItemActivate->iItem, 2);
			bool bDiagramTrackOmit = m_ListEkiTrack2.GetItemText(pNMItemActivate->iItem, 4) == nameDiagramTrackOmit;

			CDlgEkiTrack2Prop2 aDlg(
				strTrackName,
				strTrackRyakusyou,
				strTrackNoboriRyakusyou,
				bDiagramTrackOmit,
				this);
			if (aDlg.DoModal() == IDOK)
			{
				m_ListEkiTrack2.SetItemText(pNMItemActivate->iItem, 0, aDlg.getTrackName());
				m_ListEkiTrack2.SetItemText(pNMItemActivate->iItem, 1, aDlg.getTrackRyakusyou());
				m_ListEkiTrack2.SetItemText(pNMItemActivate->iItem, 2, aDlg.getTrackNoboriRyakusyou());
				if (aDlg.getDiagramTrackOmit())
				{
					m_ListEkiTrack2.SetItemText(pNMItemActivate->iItem, 4, nameDiagramTrackOmit);
				}
				else
				{
					m_ListEkiTrack2.SetItemText(pNMItemActivate->iItem, 4, _T(""));
				}

				m_PropEditUiInternal.OnUiChanged();
			}
		}
		*pResult = 0;
	}

	void ViewEki::CDlgEkiProp::OnEnKillfocusEditNextekidistance()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	void ViewEki::CDlgEkiProp::OnBnClickedCheckJikokuhyouTrackOmit()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	void ViewEki::CDlgEkiProp::OnCbnSelchangeComboJikokuhyouoperationorigin()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	void ViewEki::CDlgEkiProp::OnCbnSelchangeComboJikokuhyouoperationterminal()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	void ViewEki::CDlgEkiProp::OnBnClickedCheckJikokuhyouoperationorigindownbeforeupafter()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	void ViewEki::CDlgEkiProp::OnBnClickedCheckJikokuhyouoperationorigindownafterupbefore()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	void ViewEki::CDlgEkiProp::OnBnClickedCheckJikokuhyouoperationterminaldownbeforeupafter()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	void ViewEki::CDlgEkiProp::OnBnClickedCheckJikokuhyouoperationterminaldownafterupbefore()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	void ViewEki::CDlgEkiProp::OnNMDblclkListOuterterminalekimei2(NMHDR* pNMHDR, LRESULT* pResult)
	{
		LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
		// TODO: ここにコントロール通知ハンドラー コードを追加します。
		if (pNMItemActivate->iItem != -1)
		{
			CString strOuterEkimei = m_ListOuterTerminalEkimei2.GetItemText(pNMItemActivate->iItem, 0);
			CString strOuterJikokuRyakusyou = m_ListOuterTerminalEkimei2.GetItemText(pNMItemActivate->iItem, 1);
			CString strOuterDiaRyakusyou = m_ListOuterTerminalEkimei2.GetItemText(pNMItemActivate->iItem, 2);

			CDlgOuterEkimeiProp aDlg(
				strOuterEkimei,
				strOuterJikokuRyakusyou,
				strOuterDiaRyakusyou,
				this);
			if (aDlg.DoModal() == IDOK)
			{
				m_ListOuterTerminalEkimei2.SetItemText(pNMItemActivate->iItem, 0, aDlg.getOuterEkimei());
				m_ListOuterTerminalEkimei2.SetItemText(pNMItemActivate->iItem, 1, aDlg.getOuterJikokuRyakusyou());
				m_ListOuterTerminalEkimei2.SetItemText(pNMItemActivate->iItem, 2, aDlg.getOuterDiaRyakusyou());

				m_PropEditUiInternal.OnUiChanged();
			}
		}
		*pResult = 0;
	}

	void ViewEki::CDlgEkiProp::OnBnClickedCheckJikokuhyouchakujikokudisplaykudari()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	void ViewEki::CDlgEkiProp::OnBnClickedCheckJikokuhyouchakujikokudisplaynobori()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	void ViewEki::CDlgEkiProp::OnBnClickedCheckJikokuhyouhatsujikokudisplaykudari()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	void ViewEki::CDlgEkiProp::OnBnClickedCheckJikokuhyouhatsujikokudisplaynobori()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	void ViewEki::CDlgEkiProp::OnCbnSelchangeComboJikokuhyouressyabangoudisplaykudari()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	void ViewEki::CDlgEkiProp::OnCbnSelchangeComboJikokuhyouressyabangoudisplaynobori()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	void ViewEki::CDlgEkiProp::OnCbnSelchangeComboJikokuhyouoperationnumberdisplaykudari()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	void ViewEki::CDlgEkiProp::OnCbnSelchangeComboJikokuhyouoperationnumberdisplaynobori()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	void ViewEki::CDlgEkiProp::OnCbnSelchangeComboJikokuhyouoperationnumberdisplayrowskudari()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	void ViewEki::CDlgEkiProp::OnCbnSelchangeComboJikokuhyouoperationnumberdisplayrowsnobori()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	void ViewEki::CDlgEkiProp::OnCbnSelchangeComboJikokuhyouressyasyubetsudisplaykudari()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	void ViewEki::CDlgEkiProp::OnCbnSelchangeComboJikokuhyouressyasyubetsudisplaynobori()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	void ViewEki::CDlgEkiProp::OnCbnSelchangeComboJikokuhyouressyameidisplaykudari()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	void ViewEki::CDlgEkiProp::OnCbnSelchangeComboJikokuhyouressyameidisplaynobori()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	void ViewEki::CDlgEkiProp::OnBnClickedCheckJikokuhyououtersihatsudisplaykudari()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	void ViewEki::CDlgEkiProp::OnBnClickedCheckJikokuhyououtershuchakudisplaykudari()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	void ViewEki::CDlgEkiProp::OnBnClickedCheckJikokuhyououtersihatsudisplaynobori()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	void ViewEki::CDlgEkiProp::OnBnClickedCheckJikokuhyououtershuchakudisplaynobori()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	void ViewEki::CDlgEkiProp::OnCbnSelchangeComboDiagramColorNextEki()
	{
		m_PropEditUiInternal.OnUiChanged();
	}

	void ViewEki::CDlgEkiProp::OnBnClickedCheckOperationTableDisplayJikoku()
	{
		m_PropEditUiInternal.OnUiChanged();
	}
} //namespace ViewEki

