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
// CDlgOperationProp.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"

#include "str\CStrCharSizeMb.h"
#include "str\strLf.h"
#include "LogMsg\LogMsg.h"

#include "..\DiagramEdit.h"
#include "CDlgOperationProp.h"
#include "str\tstring.h"
#include "Str\strtoint.h"
#include "str\stringSplit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace ViewJikokuhyou{

using namespace std ;


// ================================================================
//	CDlgOperationProp::CPropEditUiInternal
// ================================================================

tstring CDlgOperationProp::CPropEditUiInternal::CreateOperationString(
	Operation aOperation, 
	bool bIsAfterOperation)
{
	CDlgOperationProp* pOuter = (CDlgOperationProp*)((BYTE*)this - offsetof(CDlgOperationProp, m_PropEditUiInternal));

	/** ダイアログボックスへの時刻の書式を保持します。 */
	const CdDedJikoku::CConv	g_CdDedJikokuConv(
		false,		//	Colon 
		CdDedJikoku::CConv::EHour_ZeroToNone,		//	HourZeroToNone 
		CdDedJikoku::CConv::ESecond_Output);	//	Output

	tstring strRev = _T("");
	strRev += to_tstring(aOperation.iLevel[0]);
	for (int idxl = 1; idxl < (int)aOperation.iLevel.size(); idxl++)
	{
		strRev += _T(".");
		strRev += to_tstring(aOperation.iLevel[idxl]);
	}
	if (aOperation.iOperation == 0)//入換
	{
		strRev += _T(" 入換 ");
		const CentDedEki* pEki = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->
			getCentDedEkiCont()->getMuPtr()->get(pOuter->m_iEkiIndex);
		strRev += pEki->getEkiTrack2Cont()->get(aOperation.iComboData1).getTrackName().c_str();
		if (bIsAfterOperation)
		{
			strRev += _T("へ ");
		}
		else
		{
			strRev += _T("から ");
		}
		CdDedJikoku aJikoku;
		int iRev = aJikoku.decode(aOperation.strEditData1);
		if (iRev >= 0)
		{
			if (aJikoku.isNull())
			{
				strRev += _T("--:--");
			}
			else
			{
				strRev += g_CdDedJikokuConv.encode(aJikoku).c_str();
			}
			strRev += _T(" 発 ");
		}
		iRev = aJikoku.decode(aOperation.strEditData2);
		if (iRev >= 0)
		{
			if (aJikoku.isNull())
			{
				strRev += _T("--:--");
			}
			else
			{
				strRev += g_CdDedJikokuConv.encode(aJikoku).c_str();
			}
			strRev += _T(" 着 ");
		}
	}
	else if (aOperation.iOperation == 1)//増結
	{
		strRev += _T("┘ 増結 ");
		CdDedJikoku aJikoku;
		int iRev = aJikoku.decode(aOperation.strEditData1);
		if (iRev >= 0)
		{
			if (aJikoku.isNull())
			{
				strRev += _T("--:--");
			}
			else
			{
				strRev += g_CdDedJikokuConv.encode(aJikoku).c_str();
			}
		}
		if (aOperation.iComboData1 == 0)
		{
			strRev += _T(" 編成後方に増結");
		}
		else
		{
			strRev += _T(" 編成前方に増結");
		}

	}
	else if (aOperation.iOperation == 2)//解結
	{
		strRev += _T("┐ 解結 ");
		CdDedJikoku aJikoku;
		int iRev = aJikoku.decode(aOperation.strEditData2);
		if (iRev >= 0)
		{
			if (aJikoku.isNull())
			{
				strRev += _T("--:--");
			}
			else
			{
				strRev += g_CdDedJikokuConv.encode(aJikoku).c_str();
			}
		}
		if (aOperation.iComboData1 == 0)
		{
			strRev += _T(" 後方の ");
			strRev += aOperation.strEditData1.c_str();
			strRev += _T(" 編成を解結");
		}
		else if (aOperation.iComboData1 == 1)
		{
			strRev += _T(" 前方の ");
			strRev += aOperation.strEditData1.c_str();
			strRev += _T(" 編成を解結");
		}
		else
		{
			strRev += _T(" 前方の ");
			strRev += aOperation.strEditData1.c_str();
			strRev += _T(" 編成以外を解結");
		}
	}
	else if (aOperation.iOperation == 3)
	{
		if (bIsAfterOperation)//入区
		{
			strRev += _T(" 入区 ");
			CdDedJikoku aJikoku;
			int iRev = aJikoku.decode(aOperation.strEditData1);
			if (iRev >= 0)
			{
				if (aJikoku.isNull())
				{
					strRev += _T("--:--");
				}
				else
				{
					strRev += g_CdDedJikokuConv.encode(aJikoku).c_str();
				}
			}
			if (!aOperation.strInOutLinkCode.empty())
			{
				strRev += _T(" ");
				strRev += aOperation.strInOutLinkCode;
			}
		}
		else//出区
		{
			strRev += _T(" 出区 ");
			CdDedJikoku aJikoku;
			int iRev = aJikoku.decode(aOperation.strEditData1);
			if (iRev >= 0)
			{
				if (aJikoku.isNull())
				{
					strRev += _T("--:--");
				}
				else
				{
					strRev += g_CdDedJikokuConv.encode(aJikoku).c_str();
				}
			}
			if (aOperation.strOperationNumber.size() > 0)
			{
				strRev += _T(" ");
				strRev += joinc(';', aOperation.strOperationNumber);
			}
			if (!aOperation.strInOutLinkCode.empty())
			{
				strRev += _T(" ");
				strRev += aOperation.strInOutLinkCode;
			}
		}
	}
	else if (aOperation.iOperation == 4)
	{
		if (bIsAfterOperation)//路線外終着
		{
			strRev += _T(" 路線外終着 ");
			CdDedJikoku aJikoku;
			int iRev = aJikoku.decode(aOperation.strEditData1);
			if (iRev >= 0)
			{
				strRev += _T("当駅 ");
				if (aJikoku.isNull())
				{
					strRev += _T("--:--");
				}
				else
				{
					strRev += g_CdDedJikokuConv.encode(aJikoku).c_str();
				}
				strRev += _T(" 発 ");
			}
			iRev = aJikoku.decode(aOperation.strEditData2);
			if (iRev >= 0)
			{
				const CentDedEki* pEki = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->
					getCentDedEkiCont()->getMuPtr()->get(pOuter->m_iEkiIndex);
				strRev += pEki->getOuterTerminalEkimei(aOperation.iComboData1);
				strRev += _T("駅 ");
				if (aJikoku.isNull())
				{
					strRev += _T("--:--");
				}
				else
				{
					strRev += g_CdDedJikokuConv.encode(aJikoku).c_str();
				}
				strRev += _T(" 着");
			}
			if (!aOperation.strInOutLinkCode.empty())
			{
				strRev += _T(" ");
				strRev += aOperation.strInOutLinkCode;
			}
		}
		else//路線外始発
		{
			strRev += _T(" 路線外始発 ");
			CdDedJikoku aJikoku;
			int iRev = aJikoku.decode(aOperation.strEditData1);
			if (iRev >= 0)
			{
				const CentDedEki* pEki = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->
					getCentDedEkiCont()->getMuPtr()->get(pOuter->m_iEkiIndex);
				strRev += pEki->getOuterTerminalEkimei(aOperation.iComboData1);
				strRev += _T("駅 ");
				if (aJikoku.isNull())
				{
					strRev += _T("--:--");
				}
				else
				{
					strRev += g_CdDedJikokuConv.encode(aJikoku).c_str();
				}
				strRev += _T(" 発 ");
			}
			iRev = aJikoku.decode(aOperation.strEditData2);
			if (iRev >= 0)
			{
				strRev += _T("当駅 ");
				if (aJikoku.isNull())
				{
					strRev += _T("--:--");
				}
				else
				{
					strRev += g_CdDedJikokuConv.encode(aJikoku).c_str();
				}
				strRev += _T(" 着");
			}

			if (aOperation.strOperationNumber.size() > 0)
			{
				strRev += _T(" ");
				strRev += joinc(';', aOperation.strOperationNumber);
			}
			if (!aOperation.strInOutLinkCode.empty())
			{
				strRev += _T(" ");
				strRev += aOperation.strInOutLinkCode;
			}
		}
	}
	else if (aOperation.iOperation == 5)
	{
		if (bIsAfterOperation)//次列車接続
		{
			strRev += _T(" 次列車接続 ");
			CdDedJikoku aJikoku;
			int iRev = aJikoku.decode(aOperation.strEditData1);
			if (iRev >= 0)
			{
				if (aJikoku.isNull())
				{
					strRev += _T("--:--");
				}
				else
				{
					strRev += g_CdDedJikokuConv.encode(aJikoku).c_str();
				}
			}
			if (aOperation.iComboData1 == 0)
			{
				strRev += _T(" 別列車");
			}
			else if (aOperation.iComboData1 == 1)
			{
				strRev += _T(" 種別変更");
			}
			else if (aOperation.iComboData1 == 2)
			{
				strRev += _T(" 列車情報変更");
			}
			else if (aOperation.iComboData1 == 3)
			{
				strRev += _T(" 同一列車扱い");
			}
		}
		else//前列車接続
		{
			strRev += _T(" 前列車接続 ");
			CdDedJikoku aJikoku;
			int iRev = aJikoku.decode(aOperation.strEditData1);
			if (iRev >= 0)
			{
				if (aJikoku.isNull())
				{
					strRev += _T("--:--");
				}
				else
				{
					strRev += g_CdDedJikokuConv.encode(aJikoku).c_str();
				}
			}
			strRev += _T(" ");
			if (aOperation.strOperationNumber.size() > 0)
			{
				strRev += joinc(';', aOperation.strOperationNumber);
			}
		}
	}
	else if (aOperation.iOperation == 6)
	{
		if (aOperation.bCheckData1)
		{
			strRev += _T(" 運用番号順反転");
		}
		else
		{
			strRev += _T(" 運用番号変更 ");
			if (aOperation.strOperationNumber.size() > 0)
			{
				strRev += joinc(';', aOperation.strOperationNumber);
			}
		}
	}
	else if (aOperation.iOperation == 7)
	{
		strRev = _T("(作業を追加)");
	}
	return strRev;
}

void CDlgOperationProp::CPropEditUiInternal::UiDataToUi( const UIDATA* pUiData )
{
	CDlgOperationProp* pOuter = (CDlgOperationProp*)( (BYTE*)this - offsetof( CDlgOperationProp , m_PropEditUiInternal ) ) ;

	if (pUiData->iListSelected >= 0)
	{
		/**
			作業種類ボタンの有効無効
			(厳密な仕様)始発駅前作業の一番上と、終着駅後作業の一番下、
				及び増結の前作業の一番上と解結後作業の一番下は、入出区・路線外発着・無し(前後列車接続)のいずれかのみ
				それ以外の作業は、入換・増結・解結のいずれかに限定
			(簡易な実装)選択されている作業が入出区・路線外発着・無しのいずれかなら、その三種を有効、他を無効に、
				入換・増結・解結のいずれかなら、その三種を有効、他を無効にする。
		*/
		bool bIsAfterOperation = pUiData->bSelectedAfter;
		const Operation* pOprationSel;
		if (pUiData->bSelectedAfter)
		{
			pOprationSel = &pUiData->sOperationA[pUiData->iListSelected];

			if (pOprationSel->iLevel.size() > 1)
			{
				/**
					iLevelが2要素以上ある場合は、子作業なので、前作業か後作業が調べる必要があります
				*/
				vector<int> iLevelSearch = pOprationSel->iLevel;
				iLevelSearch.pop_back();
				for (int idxp = 0; idxp < (int)pUiData->sOperationA.size(); idxp++)
				{
					if (pUiData->sOperationA[idxp].iLevel == iLevelSearch)
					{
						if (idxp > pUiData->iListSelected)
						{
							//idxp(増結)が後にある→前作業
							bIsAfterOperation = false;
						}
						break;
					}
				}
			}
		}
		else
		{
			pOprationSel = &pUiData->sOperationB[pUiData->iListSelected];

			if (pOprationSel->iLevel.size() > 1)
			{
				/**
					iLevelが2要素以上ある場合は、子作業なので、前作業か後作業が調べる必要があります
				*/
				vector<int> iLevelSearch = pOprationSel->iLevel;
				iLevelSearch.pop_back();
				for (int idxp = 0; idxp < (int)pUiData->sOperationB.size(); idxp++)
				{
					if (pUiData->sOperationB[idxp].iLevel == iLevelSearch)
					{
						if (idxp < pUiData->iListSelected)
						{
							//idxp(解結)が前にある→後作業
							bIsAfterOperation = true;
						}
						break;
					}
				}
			}
		}

		CButton* pButton1 = (CButton*)pOuter->GetDlgItem(IDC_RADIO_OperationType);
		CButton* pButton2 = (CButton*)pOuter->GetDlgItem(IDC_RADIO_OperationType2);
		CButton* pButton3 = (CButton*)pOuter->GetDlgItem(IDC_RADIO_OperationType3);
		CButton* pButton4 = (CButton*)pOuter->GetDlgItem(IDC_RADIO_OperationType4);
		CButton* pButton5 = (CButton*)pOuter->GetDlgItem(IDC_RADIO_OperationType5);
		CButton* pButton6 = (CButton*)pOuter->GetDlgItem(IDC_RADIO_OperationType6);
		CButton* pButton7 = (CButton*)pOuter->GetDlgItem(IDC_RADIO_OperationType7);
		if (bIsAfterOperation)
		{
			pButton4->SetWindowText(_T("入区(&K)"));
			pButton5->SetWindowText(_T("路線外終着(&O)"));
			pButton6->SetWindowText(_T("次列車接続(&E)"));
		}
		else
		{
			pButton4->SetWindowText(_T("出区(&K)"));
			pButton5->SetWindowText(_T("路線外始発(&O)"));
			pButton6->SetWindowText(_T("前列車接続(&E)"));
		}
		if (pOprationSel->iOperation <= 2 ||
			pOprationSel->iOperation == 6)//入換・増結・解結・運用番号変更
		{
			pButton1->EnableWindow(true);
			pButton2->EnableWindow(true);
			pButton3->EnableWindow(true);
			pButton4->EnableWindow(false);
			pButton5->EnableWindow(false);
			pButton6->EnableWindow(false);
			pButton7->EnableWindow(true);
		}
		else if (pOprationSel->iOperation >= 3 && pOprationSel->iOperation <= 5)
		{
			pButton1->EnableWindow(false);
			pButton2->EnableWindow(false);
			pButton3->EnableWindow(false);
			pButton4->EnableWindow(true);
			pButton5->EnableWindow(pOuter->m_bOuterHatsuChakuIsEnable);
			pButton6->EnableWindow(true);
			pButton7->EnableWindow(false);
		}
		else
		{
			pButton1->EnableWindow(false);
			pButton2->EnableWindow(false);
			pButton3->EnableWindow(false);
			pButton4->EnableWindow(false);
			pButton5->EnableWindow(false);
			pButton6->EnableWindow(false);
			pButton7->EnableWindow(false);
		}

		/**
			作業の追加・削除ボタンの有効無効設定
			選択場所の作業、位置によって、有効なボタンが変わります
			・下に追加
				後作業の入区・路線外終着・次列車接続では無効
			・挿入
				前作業の出区・路線外始発・前列車接続では無効
			・子作業追加
				増結及び解結でのみ有効
			・削除
				入出区・路線外始発終着・次列車前列車接続では無効
			・上へ
				入出区・路線外始発終着・次列車前列車接続では無効
				一つ上の作業が、入出区・路線外始発終着・次列車前列車接続なら無効
				最も上の作業の場合無効。
			・下へ
				入出区・路線外始発終着・次列車前列車接続では無効
				一つ下の作業が、入出区・路線外始発終着・次列車前列車接続なら無効
				最も下の作業の場合無効。
		*/
		CButton* pButtonAdd = (CButton*)pOuter->GetDlgItem(IDC_BUTTON_OperationAdd);
		CButton* pButtonIns = (CButton*)pOuter->GetDlgItem(IDC_BUTTON_OperationInsert);
		CButton* pButtonCAdd = (CButton*)pOuter->GetDlgItem(IDC_BUTTON_ChildOperationAdd);
		CButton* pButtonCLR = (CButton*)pOuter->GetDlgItem(IDC_BUTTON_OperationClear);
		CButton* pButtonUp = (CButton*)pOuter->GetDlgItem(IDC_BUTTON_OperationUp);
		CButton* pButtonDown = (CButton*)pOuter->GetDlgItem(IDC_BUTTON_OperationDown);
		if (pOprationSel->iOperation == 1 ||
			pOprationSel->iOperation == 2) 
		{
			pButtonAdd->EnableWindow(true);
			pButtonIns->EnableWindow(true);
			pButtonCAdd->EnableWindow(true);
			pButtonCLR->EnableWindow(true);
			if (pOprationSel->iOperation == 1)
			{
				pButtonCAdd->SetWindowTextW(_T("増結編成の作業を挿入(&3)"));
			}
			else if (pOprationSel->iOperation == 2)
			{
				pButtonCAdd->SetWindowTextW(_T("解結編成の作業を追加(&3)"));
			}
		}
		else if(pOprationSel->iOperation == 0 ||
			pOprationSel->iOperation == 6)
		{
			pButtonAdd->EnableWindow(true);
			pButtonIns->EnableWindow(true);
			pButtonCAdd->EnableWindow(false);
			pButtonCLR->EnableWindow(true);
		}
		else if (pOprationSel->iOperation == 7)
		{
			pButtonAdd->EnableWindow(true);
			pButtonIns->EnableWindow(false);
			pButtonCAdd->EnableWindow(false);
			pButtonCLR->EnableWindow(false);
		}
		else
		{
			if (bIsAfterOperation)
			{
				pButtonAdd->EnableWindow(false);
				pButtonIns->EnableWindow(true);
				pButtonCAdd->EnableWindow(false);
				pButtonCLR->EnableWindow(false);
			}
			else
			{
				pButtonAdd->EnableWindow(true);
				pButtonIns->EnableWindow(false);
				pButtonCAdd->EnableWindow(false);
				pButtonCLR->EnableWindow(false);
			}

		}
		if (pOprationSel->iOperation == 0 ||
			pOprationSel->iOperation == 1 ||
			pOprationSel->iOperation == 2 ||
			pOprationSel->iOperation == 6)
		{
			vector<Operation> contOperation;
			if (pUiData->bSelectedAfter)
			{
				contOperation = pUiData->sOperationA;
			}
			else
			{
				contOperation = pUiData->sOperationB;
			}
			vector<int> iLevelUpper = pOprationSel->iLevel;
			vector<int> iLevelLower = pOprationSel->iLevel;
			if (iLevelUpper.back() == 0)
			{
				pButtonUp->EnableWindow(false);
			}
			else
			{
				iLevelUpper.back()--;
				bool bFound = false;
				for (int idx = 0; idx < pUiData->iListSelected && !bFound; idx++)
				{
					if (contOperation[idx].iLevel == iLevelUpper &&
						(contOperation[idx].iOperation == 0 ||
						contOperation[idx].iOperation == 1 || 
						contOperation[idx].iOperation == 2 ||
						contOperation[idx].iOperation == 6))
					{
						bFound = true;
					}
				}
				if (bFound)
				{
					pButtonUp->EnableWindow(true);
				}
				else
				{
					pButtonUp->EnableWindow(false);
				}
			}
			iLevelLower.back()++;
			bool bFound = false;
			for (int idx = pUiData->iListSelected+1; idx < (int)contOperation.size() && !bFound; idx++)
			{
				if (contOperation[idx].iLevel == iLevelLower &&
					(contOperation[idx].iOperation == 0 ||
						contOperation[idx].iOperation == 1 ||
						contOperation[idx].iOperation == 2 ||
						contOperation[idx].iOperation == 6))
				{
					bFound = true;
				}
			}
			if (bFound)
			{
				pButtonDown->EnableWindow(true);
			}
			else
			{
				pButtonDown->EnableWindow(false);
			}
		}
		else
		{
			pButtonUp->EnableWindow(false);
			pButtonDown->EnableWindow(false);
		}

		/**
			時刻変更ボタンの有効無効設定
			Edit1:入換、増結、入出区、路線外発着、前後列車接続時に有効、解結時はAnySec1のみ有効
			Edit2:入換、解結、路線外発着時に有効
		*/
		CButton* pButton1_0 = (CButton*)pOuter->GetDlgItem(IDC_BUTTON_DecEdit1_1Min);
		CButton* pButton1_1 = (CButton*)pOuter->GetDlgItem(IDC_BUTTON_IncEdit1_1Min);
		CButton* pButton1_2 = (CButton*)pOuter->GetDlgItem(IDC_BUTTON_DecEdit1_5Min);
		CButton* pButton1_3 = (CButton*)pOuter->GetDlgItem(IDC_BUTTON_IncEdit1_5Min);
		CButton* pButton1_4 = (CButton*)pOuter->GetDlgItem(IDC_BUTTON_DecEdit1AnySec1);
		CButton* pButton1_5 = (CButton*)pOuter->GetDlgItem(IDC_BUTTON_IncEdit1AnySec1);
		CButton* pButton1_6 = (CButton*)pOuter->GetDlgItem(IDC_BUTTON_DecEdit1AnySec2);
		CButton* pButton1_7 = (CButton*)pOuter->GetDlgItem(IDC_BUTTON_IncEdit1AnySec2);
		CButton* pButton2_0 = (CButton*)pOuter->GetDlgItem(IDC_BUTTON_DecEdit2_1Min);
		CButton* pButton2_1 = (CButton*)pOuter->GetDlgItem(IDC_BUTTON_IncEdit2_1Min);
		CButton* pButton2_2 = (CButton*)pOuter->GetDlgItem(IDC_BUTTON_DecEdit2_5Min);
		CButton* pButton2_3 = (CButton*)pOuter->GetDlgItem(IDC_BUTTON_IncEdit2_5Min);
		CButton* pButton2_4 = (CButton*)pOuter->GetDlgItem(IDC_BUTTON_DecEdit2AnySec1);
		CButton* pButton2_5 = (CButton*)pOuter->GetDlgItem(IDC_BUTTON_IncEdit2AnySec1);
		CButton* pButton2_6 = (CButton*)pOuter->GetDlgItem(IDC_BUTTON_DecEdit2AnySec2);
		CButton* pButton2_7 = (CButton*)pOuter->GetDlgItem(IDC_BUTTON_IncEdit2AnySec2);

		if (pOprationSel->iOperation == 0 ||
			pOprationSel->iOperation == 4)
		{
			pButton1_0->EnableWindow(true);
			pButton1_1->EnableWindow(true);
			pButton1_2->EnableWindow(true);
			pButton1_3->EnableWindow(true);
			pButton1_4->EnableWindow(true);
			pButton1_5->EnableWindow(true);
			pButton1_6->EnableWindow(true);
			pButton1_7->EnableWindow(true);
			pButton2_0->EnableWindow(true);
			pButton2_1->EnableWindow(true);
			pButton2_2->EnableWindow(true);
			pButton2_3->EnableWindow(true);
			pButton2_4->EnableWindow(true);
			pButton2_5->EnableWindow(true);
			pButton2_6->EnableWindow(true);
			pButton2_7->EnableWindow(true);
		}
		else if (pOprationSel->iOperation == 1 ||
			pOprationSel->iOperation == 3 ||
			pOprationSel->iOperation == 5)
		{
			pButton1_0->EnableWindow(true);
			pButton1_1->EnableWindow(true);
			pButton1_2->EnableWindow(true);
			pButton1_3->EnableWindow(true);
			pButton1_4->EnableWindow(true);
			pButton1_5->EnableWindow(true);
			pButton1_6->EnableWindow(true);
			pButton1_7->EnableWindow(true);
			pButton2_0->EnableWindow(false);
			pButton2_1->EnableWindow(false);
			pButton2_2->EnableWindow(false);
			pButton2_3->EnableWindow(false);
			pButton2_4->EnableWindow(false);
			pButton2_5->EnableWindow(false);
			pButton2_6->EnableWindow(false);
			pButton2_7->EnableWindow(false);
		}
		else if (pOprationSel->iOperation == 2)
		{
			pButton1_0->EnableWindow(false);
			pButton1_1->EnableWindow(false);
			pButton1_2->EnableWindow(false);
			pButton1_3->EnableWindow(false);
			pButton1_4->EnableWindow(true);
			pButton1_5->EnableWindow(true);
			pButton1_6->EnableWindow(false);
			pButton1_7->EnableWindow(false);
			pButton2_0->EnableWindow(true);
			pButton2_1->EnableWindow(true);
			pButton2_2->EnableWindow(true);
			pButton2_3->EnableWindow(true);
			pButton2_4->EnableWindow(true);
			pButton2_5->EnableWindow(true);
			pButton2_6->EnableWindow(true);
			pButton2_7->EnableWindow(true);
		}
		else
		{
			pButton1_0->EnableWindow(false);
			pButton1_1->EnableWindow(false);
			pButton1_2->EnableWindow(false);
			pButton1_3->EnableWindow(false);
			pButton1_4->EnableWindow(false);
			pButton1_5->EnableWindow(false);
			pButton1_6->EnableWindow(false);
			pButton1_7->EnableWindow(false);
			pButton2_0->EnableWindow(false);
			pButton2_1->EnableWindow(false);
			pButton2_2->EnableWindow(false);
			pButton2_3->EnableWindow(false);
			pButton2_4->EnableWindow(false);
			pButton2_5->EnableWindow(false);
			pButton2_6->EnableWindow(false);
			pButton2_7->EnableWindow(false);
		}
		// --------------------------------
		//	DDXを用いた、UiControlへの設定
		// --------------------------------
		{
			//IDC_RADIO_Operation
			{
				pOuter->m_iRADIO_OperationType = pOprationSel->iOperation;
			}

			// --------------------------------
			pOuter->UpdateData(FALSE);
		}
		// --------------------------------
		//	DDXを用いない、UiControlへの設定
		//	これらは、DDXによる値設定の後で
		//	行わなくてはなりません。
		// --------------------------------
		//IDC_COMBO_Data1
		{
			CComboBox* pComboBox0 = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_Data1_0);
			CComboBox* pComboBox1 = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_Data1_1);
			CComboBox* pComboBox2 = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_Data1_2);
			CComboBox* pComboBox4 = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_Data1_4);
			CComboBox* pComboBox5 = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_Data1_5);
			CStatic* pStatic = (CStatic*)pOuter->GetDlgItem(IDC_STATIC_Combo1);
			if (pOprationSel->iOperation == 0 )
			{
				pComboBox0->EnableWindow(true);
				pComboBox0->ShowWindow(SW_SHOW);
				pComboBox0->SetCurSel(pOprationSel->iComboData1);
				pStatic->SetWindowText(_T("入換番線(&U):"));

				pComboBox1->EnableWindow(false);
				pComboBox1->ShowWindow(SW_HIDE);
				pComboBox2->EnableWindow(false);
				pComboBox2->ShowWindow(SW_HIDE);
				pComboBox4->EnableWindow(false);
				pComboBox4->ShowWindow(SW_HIDE);
				pComboBox5->EnableWindow(false);
				pComboBox5->ShowWindow(SW_HIDE);
			}
			else if (pOprationSel->iOperation == 1)
			{
				pComboBox1->EnableWindow(true);
				pComboBox1->ShowWindow(SW_SHOW);
				pComboBox1->SetCurSel(pOprationSel->iComboData1);
				pStatic->SetWindowText(_T("増結位置(&U):"));

				pComboBox0->EnableWindow(false);
				pComboBox0->ShowWindow(SW_HIDE);
				pComboBox2->EnableWindow(false);
				pComboBox2->ShowWindow(SW_HIDE);
				pComboBox4->EnableWindow(false);
				pComboBox4->ShowWindow(SW_HIDE);
				pComboBox5->EnableWindow(false);
				pComboBox5->ShowWindow(SW_HIDE);
			}
			else if (pOprationSel->iOperation == 2)
			{
				pComboBox2->EnableWindow(true);
				pComboBox2->ShowWindow(SW_SHOW);
				pComboBox2->SetCurSel(pOprationSel->iComboData1);
				pStatic->SetWindowText(_T("解結位置(&U):"));

				pComboBox0->EnableWindow(false);
				pComboBox0->ShowWindow(SW_HIDE);
				pComboBox1->EnableWindow(false);
				pComboBox1->ShowWindow(SW_HIDE);
				pComboBox4->EnableWindow(false);
				pComboBox4->ShowWindow(SW_HIDE);
				pComboBox5->EnableWindow(false);
				pComboBox5->ShowWindow(SW_HIDE);
			}
			else if (pOprationSel->iOperation == 4)
			{
				pComboBox4->EnableWindow(true);
				pComboBox4->ShowWindow(SW_SHOW);
				pComboBox4->SetCurSel(pOprationSel->iComboData1);

				if (bIsAfterOperation)
				{
					pStatic->SetWindowText(_T("路線外終着駅名(&U):"));
				}
				else
				{
					pStatic->SetWindowText(_T("路線外始発駅名(&U):"));
				}

				pComboBox0->EnableWindow(false);
				pComboBox0->ShowWindow(SW_HIDE);
				pComboBox1->EnableWindow(false);
				pComboBox1->ShowWindow(SW_HIDE);
				pComboBox2->EnableWindow(false);
				pComboBox2->ShowWindow(SW_HIDE);
				pComboBox5->EnableWindow(false);
				pComboBox5->ShowWindow(SW_HIDE);
			}
			else if (pOprationSel->iOperation == 5 &&
				bIsAfterOperation)
			{
				pComboBox5->EnableWindow(true);
				pComboBox5->ShowWindow(SW_SHOW);
				pComboBox5->SetCurSel(pOprationSel->iComboData1);
				pStatic->SetWindowText(_T("次列車接続タイプ(&U):"));

				pComboBox0->EnableWindow(false);
				pComboBox0->ShowWindow(SW_HIDE);
				pComboBox1->EnableWindow(false);
				pComboBox1->ShowWindow(SW_HIDE);
				pComboBox2->EnableWindow(false);
				pComboBox2->ShowWindow(SW_HIDE);
				pComboBox4->EnableWindow(false);
				pComboBox4->ShowWindow(SW_HIDE);
			}
			else
			{
				pComboBox0->EnableWindow(false);
				pComboBox1->EnableWindow(false);
				pComboBox2->EnableWindow(false);
				pComboBox4->EnableWindow(false);
				pComboBox5->EnableWindow(false);
			}
		}
		//IDC_EDIT_Data1
		{
			CEdit* pControl = (CEdit*)(pOuter->GetDlgItem(IDC_EDIT_Data1));
			CStatic* pStatic = (CStatic*)pOuter->GetDlgItem(IDC_STATIC_Edit1);


			if (pOprationSel->iOperation == 0)
			{
				pControl->EnableWindow(true);
				pControl->SetWindowText(pOprationSel->strEditData1.c_str());
				pControl->SetSel(0, -1);
				pStatic->SetWindowText(_T("入換発時刻(&J):"));
			}
			else if (pOprationSel->iOperation == 1)
			{
				pControl->EnableWindow(true);
				pControl->SetWindowText(pOprationSel->strEditData1.c_str());
				pControl->SetSel(0, -1);
				pStatic->SetWindowText(_T("増結時刻(&J):"));
			}
			else if (pOprationSel->iOperation == 2)
			{
				pControl->EnableWindow(true);
				pControl->SetWindowText(pOprationSel->strEditData1.c_str());
				pControl->SetSel(0, -1);
				pStatic->SetWindowText(_T("編成数(&J):"));
			}
			else if (pOprationSel->iOperation == 3)
			{
				pControl->EnableWindow(true);
				pControl->SetWindowText(pOprationSel->strEditData1.c_str());
				pControl->SetSel(0, -1);
				if (bIsAfterOperation)
				{
					pStatic->SetWindowText(_T("入区時刻(&J):"));
				}
				else
				{
					pStatic->SetWindowText(_T("出区時刻(&J):"));
				}
			}
			else if (pOprationSel->iOperation == 4)
			{
				pControl->EnableWindow(true);
				pControl->SetWindowText(pOprationSel->strEditData1.c_str());
				pControl->SetSel(0, -1);
				if (bIsAfterOperation)
				{
					pStatic->SetWindowText(_T("当駅発時刻(&J):"));
				}
				else
				{
					pStatic->SetWindowText(_T("始発駅発時刻(&J):"));
				}
			}
			else if (pOprationSel->iOperation == 5)
			{
				pControl->EnableWindow(true);
				pControl->SetWindowText(pOprationSel->strEditData1.c_str());
				pControl->SetSel(0, -1);
				if (bIsAfterOperation)
				{
					pStatic->SetWindowText(_T("終点時刻(&J):"));
				}
				else
				{
					pStatic->SetWindowText(_T("起点時刻(&J):"));
				}
			}
			else
			{
				pControl->EnableWindow(false);
				pControl->SetWindowText(CString());
				//pControl->SetSel(0, -1);
			}
		}
		//IDC_EDIT_Data2
		{
			CEdit* pControl = (CEdit*)(pOuter->GetDlgItem(IDC_EDIT_Data2));
			CStatic* pStatic = (CStatic*)pOuter->GetDlgItem(IDC_STATIC_Edit2);
			if (pOprationSel->iOperation == 0 )
			{
				pControl->EnableWindow(true);
				pControl->SetWindowText(pOprationSel->strEditData2.c_str());
				pControl->SetSel(0, -1);
				pStatic->SetWindowText(_T("入換着時刻(&I):"));
			}
			else if (pOprationSel->iOperation == 2 )
			{
				pControl->EnableWindow(true);
				pControl->SetWindowText(pOprationSel->strEditData2.c_str());
				pControl->SetSel(0, -1);
				pStatic->SetWindowText(_T("解結時刻(&I):"));
			}
			else if (pOprationSel->iOperation == 4)
			{
				pControl->EnableWindow(true);
				pControl->SetWindowText(pOprationSel->strEditData2.c_str());
				pControl->SetSel(0, -1);
				if (bIsAfterOperation)
				{
					pStatic->SetWindowText(_T("終着駅着時刻(&J):"));
				}
				else
				{
					pStatic->SetWindowText(_T("当駅着時刻(&J):"));
				}
			}
			else
			{
				pControl->EnableWindow(false);
				pControl->SetWindowText(CString());
			}
		}

		//IDC_EDIT_OperationNumbers
		{
			CEdit* pControl = (CEdit*)(pOuter->GetDlgItem(IDC_EDIT_OperationNumbers));
			CStatic* pStatic = (CStatic*)pOuter->GetDlgItem(IDC_STATIC_OperationNumber);
			if (((pOprationSel->iOperation == 3 || pOprationSel->iOperation == 4 ||
				pOprationSel->iOperation == 5) &&
				!bIsAfterOperation) ||
				pOprationSel->iOperation == 6)
			{
				tstring strTemp = _T("");
				strTemp = joinc(';', pOprationSel->strOperationNumber);
				pControl->EnableWindow(true);
				pControl->SetWindowText(strTemp.c_str());
				pControl->SetSel(0, -1);

				if (pOprationSel->iOperation == 5)
				{
					pStatic->SetWindowText(_T("仮運用番号(&N):"));
				}
				else
				{
					pStatic->SetWindowText(_T("運用番号(&N):"));
				}

			}
			else
			{
				pControl->EnableWindow(false);
				pControl->SetWindowText(CString());
			}
		}
		//IDC_CHECK_JikokuDisplay(増解結表示省略設定追加)
		{
			CButton* pControl = (CButton*)(pOuter->GetDlgItem(IDC_CHECK_JikokuDisplay));
			if (pOprationSel->iOperation == 0 && pOprationSel->iLevel.size() == 1)
			{
				pControl->EnableWindow(true);
				pControl->SetCheck(pOprationSel->bCheckData1 ? BST_CHECKED : BST_UNCHECKED);
				if (bIsAfterOperation)
				{
					pControl->SetWindowText(_T("入換発時刻を当駅発時刻にする(&M)"));
				}
				else
				{
					pControl->SetWindowText(_T("入換着時刻を当駅着時刻にする(&M)"));
				}
			}
			else if (pOprationSel->iOperation == 6)
			{
				pControl->EnableWindow(true);
				pControl->SetCheck(pOprationSel->bCheckData1 ? BST_CHECKED : BST_UNCHECKED);
				pControl->SetWindowText(_T("運用番号順を反転させる(&M)"));
			}
			else
			{
				pControl->EnableWindow(false);
			}
		}
		//IDC_EDIT_InOutLinkCode
		{
			CEdit* pControl = (CEdit*)(pOuter->GetDlgItem(IDC_EDIT_InOutLinkCode));
			CStatic* pStatic = (CStatic*)pOuter->GetDlgItem(IDC_STATIC_InOutLinkCode);
			if (pOprationSel->iOperation == 3 || pOprationSel->iOperation == 4)
			{
				pControl->EnableWindow(true);
				pControl->SetWindowText(pOprationSel->strInOutLinkCode.c_str());
				pControl->SetSel(0, -1);
				pStatic->SetWindowText(_T("入出区連携コード(&L):"));

			}
			else
			{
				pControl->EnableWindow(false);
				pControl->SetWindowText(CString());
			}
		}
	}
	else
	{
		CButton* pButton1 = (CButton*)pOuter->GetDlgItem(IDC_RADIO_OperationType);
		CButton* pButton2 = (CButton*)pOuter->GetDlgItem(IDC_RADIO_OperationType2);
		CButton* pButton3 = (CButton*)pOuter->GetDlgItem(IDC_RADIO_OperationType3);
		CButton* pButton4 = (CButton*)pOuter->GetDlgItem(IDC_RADIO_OperationType4);
		CButton* pButton5 = (CButton*)pOuter->GetDlgItem(IDC_RADIO_OperationType5);
		CButton* pButton6 = (CButton*)pOuter->GetDlgItem(IDC_RADIO_OperationType6);
		CButton* pButton7 = (CButton*)pOuter->GetDlgItem(IDC_RADIO_OperationType7);
		pButton1->EnableWindow(false);
		pButton2->EnableWindow(false);
		pButton3->EnableWindow(false);
		pButton4->EnableWindow(false);
		pButton5->EnableWindow(false);
		pButton6->EnableWindow(false);
		pButton7->EnableWindow(false);

		CComboBox* pComboBox0 = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_Data1_0);
		CComboBox* pComboBox1 = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_Data1_1);
		CComboBox* pComboBox2 = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_Data1_2);
		CComboBox* pComboBox4 = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_Data1_4);
		CComboBox* pComboBox5 = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_Data1_5);
		pComboBox0->EnableWindow(false);
		pComboBox1->EnableWindow(false);
		pComboBox2->EnableWindow(false);
		pComboBox4->EnableWindow(false);
		pComboBox5->EnableWindow(false);

		CEdit* pControl1 = (CEdit*)(pOuter->GetDlgItem(IDC_EDIT_Data1));
		pControl1->EnableWindow(false);
		pControl1->SetWindowText(CString());

		CEdit* pControl2 = (CEdit*)(pOuter->GetDlgItem(IDC_EDIT_Data2));
		pControl2->EnableWindow(false);
		pControl2->SetWindowText(CString());

		CEdit* pControl3 = (CEdit*)(pOuter->GetDlgItem(IDC_EDIT_OperationNumbers));
		pControl3->EnableWindow(false);
		pControl3->SetWindowText(CString());

		CButton* pControl4 = (CButton*)(pOuter->GetDlgItem(IDC_CHECK_JikokuDisplay));
		pControl4->EnableWindow(false);

		CEdit* pControl5 = (CEdit*)(pOuter->GetDlgItem(IDC_EDIT_InOutLinkCode));
		pControl5->EnableWindow(false);
		pControl5->SetWindowText(CString());

		CButton* pButtonAdd = (CButton*)pOuter->GetDlgItem(IDC_BUTTON_OperationAdd);
		CButton* pButtonIns = (CButton*)pOuter->GetDlgItem(IDC_BUTTON_OperationInsert);
		CButton* pButtonCAdd = (CButton*)pOuter->GetDlgItem(IDC_BUTTON_ChildOperationAdd);
		CButton* pButtonCLR = (CButton*)pOuter->GetDlgItem(IDC_BUTTON_OperationClear);

		pButtonAdd->EnableWindow(false);
		pButtonIns->EnableWindow(false);
		pButtonCAdd->EnableWindow(false);
		pButtonCLR->EnableWindow(false);
	}
	{

		CListBox* pListBoxB = (CListBox*)pOuter->GetDlgItem(IDC_LIST_OperationBefore);
		pListBoxB->ResetContent();
		for (int idxb = 0; idxb < (int)pUiData->sOperationB.size(); idxb++)
		{
			bool bIsAfterOperation = false;
			if (pUiData->sOperationB[idxb].iLevel.size() > 1)
			{
				/**
					iLevelが2要素以上ある場合は、子作業なので、前作業か後作業が調べる必要があります
				*/
				vector<int> iLevelSearch = pUiData->sOperationB[idxb].iLevel;
				iLevelSearch.pop_back();
				for (int idxp = 0; idxp < (int)pUiData->sOperationB.size(); idxp++)
				{
					if (pUiData->sOperationB[idxp].iLevel == iLevelSearch)
					{
						if (idxp < idxb)
						{
							//idxp(解結)が前にある→後作業
							bIsAfterOperation = true;
						}
						break;
					}
				}
			}
			tstring strOperation = CreateOperationString(pUiData->sOperationB[idxb], bIsAfterOperation);
			pListBoxB->AddString(strOperation.c_str());
		}
		if (!pUiData->bSelectedAfter)
		{
			pListBoxB->SetCurSel(pUiData->iListSelected);
		}


		CListBox* pListBoxA = (CListBox*)pOuter->GetDlgItem(IDC_LIST_OperationAfter);
		pListBoxA->ResetContent();
		for (int idxa = 0; idxa < (int)pUiData->sOperationA.size(); idxa++)
		{
			bool bIsAfterOperation = true;
			if (pUiData->sOperationA[idxa].iLevel.size() > 1)
			{
				/**
					iLevelが2要素以上ある場合は、子作業なので、前作業か後作業が調べる必要があります
				*/
				vector<int> iLevelSearch = pUiData->sOperationA[idxa].iLevel;
				iLevelSearch.pop_back();
				for (int idxp = 0; idxp < (int)pUiData->sOperationA.size(); idxp++)
				{
					if (pUiData->sOperationA[idxp].iLevel == iLevelSearch)
					{
						if (idxp > idxa)
						{
							//idxp(増結)が後にある→前作業
							bIsAfterOperation = false;
						}
						break;
					}
				}
			}
			tstring strOperation = CreateOperationString(pUiData->sOperationA[idxa], bIsAfterOperation);
			pListBoxA->AddString(strOperation.c_str());
		}
		if (pUiData->bSelectedAfter)
		{
			pListBoxA->SetCurSel(pUiData->iListSelected);
		}
	}
}


void  CDlgOperationProp::CPropEditUiInternal::UiDataFromUi( UIDATA* pUiData )
{
	int iRv = 0 ; 
	CDlgOperationProp* pOuter = (CDlgOperationProp*)( (BYTE*)this - offsetof( CDlgOperationProp , m_PropEditUiInternal ) ) ;

	if ( iRv >= 0 )
	{
		if ( !pOuter->UpdateData( TRUE ) )
		{
			iRv = -1 ;	//	入力エラーあり
		}
	}

	/**
		iUiOperationが0の時以外は、この動作はスキップされるので、
		iUiOperationが0であると仮定して進める
	*/
	if ( iRv >= 0 )
	{
		if (pUiData->iListSelected >= 0)
		{
			Operation* pOprationSel;
			if (pUiData->bSelectedAfter)
			{
				pOprationSel = &pUiData->sOperationA[pUiData->iListSelected];
			}
			else
			{
				pOprationSel = &pUiData->sOperationB[pUiData->iListSelected];
			}

			//IDC_RADIO_Operation
			{
				pOprationSel->iOperation = pOuter->m_iRADIO_OperationType;
				if (pOprationSel->iOperation == -1)
				{
					pOprationSel->iOperation = 7;//(作業を追加)
				}
			}

			//IDC_COMBO_Data1
			if (pOprationSel->iOperation == 0 ) {
				CComboBox* pComboBox = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_Data1_0);
				int iSel = pComboBox->GetCurSel();
				if (iSel != CB_ERR)
				{
					pOprationSel->iComboData1 = iSel;
				}
			}
			else if ( pOprationSel->iOperation == 1) {
				CComboBox* pComboBox = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_Data1_1);
				int iSel = pComboBox->GetCurSel();
				if (iSel != CB_ERR)
				{
					pOprationSel->iComboData1 = iSel;
				}
			}
			else if (pOprationSel->iOperation == 2) {
				CComboBox* pComboBox = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_Data1_2);
				int iSel = pComboBox->GetCurSel();
				if (iSel != CB_ERR)
				{
					pOprationSel->iComboData1 = iSel;
				}
			}
			else if (pOprationSel->iOperation == 4) {
				CComboBox* pComboBox = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_Data1_4);
				int iSel = pComboBox->GetCurSel();
				if (iSel != CB_ERR)
				{
					pOprationSel->iComboData1 = iSel;
				}
			}
			else if (pOprationSel->iOperation == 5) {
				CComboBox* pComboBox = (CComboBox*)pOuter->GetDlgItem(IDC_COMBO_Data1_5);
				int iSel = pComboBox->GetCurSel();
				if (iSel != CB_ERR)
				{
					pOprationSel->iComboData1 = iSel;
				}
			}

			//IDC_EDIT_Data1
			{
				CString strText;
				CEdit* pControl = (CEdit*)(pOuter->GetDlgItem(IDC_EDIT_Data1));
				pControl->GetWindowText(strText);
				pOprationSel->strEditData1 = (LPCTSTR)strText;
			}
			//IDC_EDIT_Data2
			if (pOprationSel->iOperation == 0 || pOprationSel->iOperation == 2 ||
				pOprationSel->iOperation == 4)
			{
				CString strText;
				CEdit* pControl = (CEdit*)(pOuter->GetDlgItem(IDC_EDIT_Data2));
				pControl->GetWindowText(strText);
				pOprationSel->strEditData2 = (LPCTSTR)strText;
			}

			//IDC_EDIT_OperationNumbers
			if ((pOprationSel->iOperation == 3 || pOprationSel->iOperation == 4 ||
				pOprationSel->iOperation == 5 || pOprationSel->iOperation == 6)/*&&
				!pUiData->bSelectedAfter*/)
			{
				CString strText;
				CEdit* pControl = (CEdit*)(pOuter->GetDlgItem(IDC_EDIT_OperationNumbers));
				pControl->GetWindowText(strText);
				vector<tstring>strTemp = splitc<vector<tstring>>(';', (LPCTSTR)strText,true);
				pOprationSel->strOperationNumber = strTemp;
			}

			//IDC_CHECK_JikokuDisplay
			if (pOprationSel->iOperation == 0 || pOprationSel->iOperation == 6)
			{
				CButton* pControl = (CButton*)(pOuter->GetDlgItem(IDC_CHECK_JikokuDisplay));
				pOprationSel->bCheckData1 = (pControl->GetCheck() == BST_CHECKED);
			}

			//IDC_EDIT_InOutLinkCode
			if (pOprationSel->iOperation == 3 || pOprationSel->iOperation == 4)
			{
				CString strText;
				CEdit* pControl = (CEdit*)(pOuter->GetDlgItem(IDC_EDIT_InOutLinkCode));
				pControl->GetWindowText(strText);
				pOprationSel->strInOutLinkCode = (LPCTSTR)strText;
			}
		}
	}	
}

void CDlgOperationProp::CPropEditUiInternal::SetFocus(int iOffsetofUiDataMember)
{
	CDlgOperationProp* pOuter = (CDlgOperationProp*)((BYTE*)this - offsetof(CDlgOperationProp, m_PropEditUiInternal));
	CWnd* pControl = NULL;

	//IDC_RADIO_Operation
	{
		if (iOffsetofUiDataMember == offsetof(Operation, iOperation))
		{
			pControl = pOuter->GetDlgItem(IDC_RADIO_OperationType);
		}
	}
	//IDC_EDIT_Data1
	{
		if (iOffsetofUiDataMember == offsetof(Operation, strEditData1))
		{
			pControl = pOuter->GetDlgItem(IDC_EDIT_Data1);
		}
	}
	//IDC_EDIT_Data2
	{
		if (iOffsetofUiDataMember == offsetof(Operation, strEditData2))
		{
			pControl = pOuter->GetDlgItem(IDC_EDIT_Data2);
		}

	}
	//IDC_EDIT_OperationNumber
	{
		if (iOffsetofUiDataMember == offsetof(Operation, strOperationNumber))
		{
			pControl = pOuter->GetDlgItem(IDC_EDIT_OperationNumbers);
		}

	}

	if ( pControl != NULL )
	{
		pOuter->GotoDlgCtrl( pControl ) ; 
	}
}
//void CDlgOperationProp::CPropEditUiInternal::SetFocus2(
//	int iOffsetofUiDataMember,
//	int iListSelect,
//	bool bSelectedAfter,
//	int iOperation)
//{
//	CDlgOperationProp* pOuter = (CDlgOperationProp*)( (BYTE*)this - offsetof( CDlgOperationProp , m_PropEditUiInternal ) ) ;
//	CWnd* pControl = NULL ;
//
//	//IDC_RADIO_Operation
//	{
//		if (iOffsetofUiDataMember == offsetof(Operation, iOperation))
//		{
//			if (bSelectedAfter)
//			{
//				CListBox* pListBox = (CListBox*)pOuter->GetDlgItem(IDC_LIST_OperationAfter);
//				pListBox->SetCurSel(iListSelect);
//			}
//			else
//			{
//				CListBox* pListBox = (CListBox*)pOuter->GetDlgItem(IDC_LIST_OperationBefore);
//				pListBox->SetCurSel(iListSelect);
//			}
//			pControl = pOuter->GetDlgItem(IDC_RADIO_Operation);
//		}
//	}
//	//IDC_COMBO_Data1_0
//	{
//		if ( iOffsetofUiDataMember == offsetof(Operation, iComboData1) )
//		{
//			if (bSelectedAfter)
//			{
//				CListBox* pListBox = (CListBox*)pOuter->GetDlgItem(IDC_LIST_OperationAfter);
//				pListBox->SetCurSel(iListSelect);
//			}
//			else
//			{
//				CListBox* pListBox = (CListBox*)pOuter->GetDlgItem(IDC_LIST_OperationBefore);
//				pListBox->SetCurSel(iListSelect);
//			}
//			if (iOperation == 0)
//			{
//				pControl = pOuter->GetDlgItem(IDC_COMBO_Data1_0);
//			}
//			else if (iOperation == 1)
//			{
//				pControl = pOuter->GetDlgItem(IDC_COMBO_Data1_1);
//			}
//			else if (iOperation == 2)
//			{
//				pControl = pOuter->GetDlgItem(IDC_COMBO_Data1_2);
//			}
//			else if (iOperation == 4)
//			{
//				pControl = pOuter->GetDlgItem(IDC_COMBO_Data1_4);
//			}
//		}
//	}
//	//IDC_EDIT_Data1
//	{
//		if ( iOffsetofUiDataMember == offsetof(Operation, strEditData1) )
//		{
//			if (bSelectedAfter)
//			{
//				CListBox* pListBox = (CListBox*)pOuter->GetDlgItem(IDC_LIST_OperationAfter);
//				pOuter->GotoDlgCtrl(pListBox);
//				pListBox->SetCurSel(iListSelect);
//				pOuter->OnLbnSelchangeListOperationafter();
//
//			}
//			else
//			{
//				CListBox* pListBox = (CListBox*)pOuter->GetDlgItem(IDC_LIST_OperationBefore);
//				pOuter->GotoDlgCtrl(pListBox);
//				pListBox->SetCurSel(iListSelect);
//				pOuter->OnLbnSelchangeListOperationbefore();
//			}
//			pControl = pOuter->GetDlgItem(IDC_EDIT_Data1)  ;
//		}
//	}
//	//IDC_EDIT_Data2
//	{
//		if ( iOffsetofUiDataMember == offsetof(Operation, strEditData2) )
//		{
//			if (bSelectedAfter)
//			{
//				CListBox* pListBox = (CListBox*)pOuter->GetDlgItem(IDC_LIST_OperationAfter);;
//				pOuter->GotoDlgCtrl(pListBox);
//				pListBox->SetCurSel(iListSelect);
//				pOuter->OnLbnSelchangeListOperationafter();
//			}
//			else
//			{
//				CListBox* pListBox = (CListBox*)pOuter->GetDlgItem(IDC_LIST_OperationBefore);
//				pOuter->GotoDlgCtrl(pListBox);
//				pListBox->SetCurSel(iListSelect);
//				pOuter->OnLbnSelchangeListOperationbefore();
//			}
//			pControl = pOuter->GetDlgItem(IDC_EDIT_Data2) ;
//		}
//
//	}
//	//IDC_CHECK_JikokuDisplay
//	{
//		if (iOffsetofUiDataMember == offsetof(Operation, bCheckData1))
//		{
//			if (bSelectedAfter)
//			{
//				CListBox* pListBox = (CListBox*)pOuter->GetDlgItem(IDC_LIST_OperationAfter);
//				pListBox->SetCurSel(iListSelect);
//			}
//			else
//			{
//				CListBox* pListBox = (CListBox*)pOuter->GetDlgItem(IDC_LIST_OperationBefore);
//				pListBox->SetCurSel(iListSelect);
//			}
//			pControl = pOuter->GetDlgItem(IDC_CHECK_JikokuDisplay);
//		}
//
//	}
//	//IDC_EDIT_OperationNumber
//	{
//		if (iOffsetofUiDataMember == offsetof(Operation, strOperationNumber))
//		{
//			if (bSelectedAfter)
//			{
//				CListBox* pListBox = (CListBox*)pOuter->GetDlgItem(IDC_LIST_OperationAfter);
//				pOuter->GotoDlgCtrl(pListBox);
//				pListBox->SetCurSel(iListSelect);
//			}
//			else
//			{
//				CListBox* pListBox = (CListBox*)pOuter->GetDlgItem(IDC_LIST_OperationBefore);
//				pListBox->SetCurSel(iListSelect);
//			}
//			pControl = pOuter->GetDlgItem(IDC_EDIT_OperationNumber);
//		}
//
//	}
//	////IDC_CHECK_SyubetsuChange
//	//{
//	//	if (iOffsetofUiDataMember == offsetof(UIDATA, iOuterTerminalIndex))
//	//	{
//	//		pControl = pOuter->GetDlgItem(IDC_CHECK_SyubetsuChange);
//	//	}
//
//	//}
//	////IDC_LIST_OperationBefore
//	//{
//	//	if (iOffsetofUiDataMember == offsetof(UIDATA, strOuterHatsuChakuJikoku))
//	//	{
//	//		pControl = pOuter->GetDlgItem(IDC_LIST_OperationBefore);
//	//	}
//
//	//}
//	////IDC_LIST_OperationAfter
//	//{
//	//	if (iOffsetofUiDataMember == offsetof(UIDATA, strOuterHatsuChakuJikoku))
//	//	{
//	//		pControl = pOuter->GetDlgItem(IDC_LIST_OperationAfter);
//	//	}
//
//	//}
//	if ( pControl != NULL )
//	{
//		//pOuter->GotoDlgCtrl( pControl ) ; 
//	}
//}
		
void CDlgOperationProp::CPropEditUiInternal::ShowError(
			const tstring& strErrorReason ,
			const tstring& strInfo )  
{
	CDlgOperationProp* pOuter = (CDlgOperationProp*)( (BYTE*)this - offsetof( CDlgOperationProp , m_PropEditUiInternal ) ) ;
	CString strErrorMsg = strErrorReason.c_str() ;

	if ( strErrorReason == ERRMSG_INVALID_SHUNTHATSUJIKOKU)
	{
		pOuter->GetDlgItem( IDC_ERR_INVALID_SHUNTHATSUJIKOKU)->GetWindowText( strErrorMsg )  ;
	}
	else if ( strErrorReason == ERRMSG_INVALID_SHUNTCHAKUJIKOKU)
	{
		pOuter->GetDlgItem( IDC_ERR_INVALID_SHUNTCHAKUJIKOKU)->GetWindowText( strErrorMsg )  ;
	}
	//else if (strErrorReason == ERRMSG_OUTOFRANGE_SHUNTHATSUJIKOKU)
	//{
	//	//pOuter->GetDlgItem(IDC_ERROR_ShuntTrack)->GetWindowText(strErrorMsg);
	//}
	//else if (strErrorReason == ERRMSG_OUTOFRANGE_SHUNTCHAKUJIKOKU)
	//{
	//	//pOuter->GetDlgItem(IDC_ERROR_OperationHatsuJikokuFormat)->GetWindowText(strErrorMsg);
	//}
	else if (strErrorReason == ERRMSG_INVALID_CONNECTJIKOKU)
	{
		pOuter->GetDlgItem(IDC_ERR_INVALID_CONNECTJIKOKU)->GetWindowText(strErrorMsg);
	}
	//else if (strErrorReason == ERRMSG_OUTOFRANGE_CONNECTJIKOKU)
	//{
	//	//pOuter->GetDlgItem(IDC_ERROR_OuterHatsuChakuJikokuFormat)->GetWindowText(strErrorMsg);
	//}
	else if (strErrorReason == ERRMSG_INVALID_RELEASEJIKOKU)
	{
		pOuter->GetDlgItem(IDC_ERR_INVALID_RELEASEJIKOKU)->GetWindowText(strErrorMsg);
	}
	//else if (strErrorReason == ERRMSG_OUTOFRANGE_RELEASEJIKOKU)
	//{
	//	//pOuter->GetDlgItem(IDC_ERROR_ShuntTrack)->GetWindowText(strErrorMsg);
	//}
	else if (strErrorReason == ERRMSG_INVALID_RELEASEINDEX)
	{
		pOuter->GetDlgItem(IDC_ERR_INVALID_RELEASEINDEX)->GetWindowText(strErrorMsg);
	}
	else if (strErrorReason == ERRMSG_OUTOFRANGE_RELEASEINDEX)
	{
		pOuter->GetDlgItem(IDC_ERR_OUTOFRANGE_RELEASEINDEX)->GetWindowText(strErrorMsg);
	}
	else if (strErrorReason == ERRMSG_INVALID_OUTJIKOKU)
	{
		pOuter->GetDlgItem(IDC_ERR_INVALID_OUTJIKOKU)->GetWindowText(strErrorMsg);
	}
	//else if (strErrorReason == ERRMSG_OUTOFRANGE_OUTJIKOKU)
	//{
	//	//pOuter->GetDlgItem(IDC_ERROR_HatsujikokuFormat)->GetWindowText(strErrorMsg);
	//}
	else if (strErrorReason == ERRMSG_INVALID_INJIKOKU)
	{
		pOuter->GetDlgItem(IDC_ERR_INVALID_INJIKOKU)->GetWindowText(strErrorMsg);
	}
	//else if (strErrorReason == ERRMSG_OUTOFRANGE_INJIKOKU)
	//{
	//	//pOuter->GetDlgItem(IDC_ERROR_OperationHatsuJikokuFormat)->GetWindowText(strErrorMsg);
	//}
	else if (strErrorReason == ERRMSG_INVALID_OUTERHATSUJIKOKU)
	{
		pOuter->GetDlgItem(IDC_ERR_INVALID_OUTERHATSUJIKOKU)->GetWindowText(strErrorMsg);
	}
	else if (strErrorReason == ERRMSG_INVALID_CHAKUJIKOKU)
	{
		pOuter->GetDlgItem(IDC_ERR_INVALID_CHAKUJIKOKU)->GetWindowText(strErrorMsg);
	}
	//else if (strErrorReason == ERRMSG_OUTOFRANGE_CHAKUJIKOKU)
	//{
	//	//pOuter->GetDlgItem(IDC_ERROR_OuterHatsuChakuJikokuFormat)->GetWindowText(strErrorMsg);
	//}
	else if (strErrorReason == ERRMSG_EMPTY_OUTERHATSUJIKOKU)
	{
		pOuter->GetDlgItem(IDC_ERR_EMPTY_OUTERHATSUJIKOKU)->GetWindowText(strErrorMsg);
	}
	else if (strErrorReason == ERRMSG_INVALID_HATSUJIKOKU)
	{
		pOuter->GetDlgItem(IDC_ERR_INVALID_HATSUJIKOKU)->GetWindowText(strErrorMsg);
	}
	else if (strErrorReason == ERRMSG_INVALID_OUTERCHAKUJIKOKU)
	{
		pOuter->GetDlgItem(IDC_ERR_INVALID_OUTERCHAKUJIKOKU)->GetWindowText(strErrorMsg);
	}
	//else if (strErrorReason == ERRMSG_OUTOFRANGE_HATSUJIKOKU)
	//{
	//	//pOuter->GetDlgItem(IDC_ERROR_OperationChakuJikokuFormat)->GetWindowText(strErrorMsg);
	//}
	else if (strErrorReason == ERRMSG_EMPTY_OUTERCHAKUJIKOKU)
	{
		pOuter->GetDlgItem(IDC_ERR_EMPTY_OUTERCHAKUJIKOKU)->GetWindowText(strErrorMsg);
	}
	else if (strErrorReason == ERRMSG_INVALID_ORIGINJIKOKU)
	{
		pOuter->GetDlgItem(IDC_ERR_INVALID_ORIGINJIKOKU)->GetWindowText(strErrorMsg);
	}
	else if (strErrorReason == ERRMSG_INVALID_TERMINALJIKOKU)
	{
		pOuter->GetDlgItem(IDC_ERR_INVALID_TERMINALJIKOKU)->GetWindowText(strErrorMsg);
	}
	else if (strErrorReason == ERRMSG_UNUSABLE_COMMA)
	{
		pOuter->GetDlgItem(IDC_ERR_UNUSABLE_COMMA)->GetWindowText(strErrorMsg);
	}
	else if (strErrorReason == ERRMSG_EMPTY_OPERATIONNUMBER)
	{
		pOuter->GetDlgItem(IDC_ERR_EMPTY_OPERATIONNUMBER)->GetWindowText(strErrorMsg);
	}
	//strErrorMsg += _T("(作業");
	strErrorMsg += strInfo.c_str();
	//strErrorMsg += _T(")");
	pOuter->MessageBox( strErrorMsg , NULL , MB_OK | MB_ICONEXCLAMATION ) ;
}
		// ********************************
		//	コンストラクタ
		// ********************************
CDlgOperationProp::CPropEditUiInternal::CPropEditUiInternal(
			bool bNewItem , 
			Mu<CentDedRessya*>* pTarget , 
			int iChakuEkiOrder ,
			int iHatsuEkiOrder,
			bool bFocusAfter,
			int iFocusIndex,
			bool bFocusChild,
			int iStandardShuntTrackIndex[],
			vector<vector<int>> iStandardOuterTerminalJikan )
	: CPropEditUI_Operation(
			bNewItem , pTarget , 
			iChakuEkiOrder,
			iHatsuEkiOrder,
			bFocusAfter,
			iFocusIndex,
			bFocusChild,
			iStandardShuntTrackIndex,
			iStandardOuterTerminalJikan)
{
}


/////////////////////////////////////////////////////////////////////////////
// CDlgOperationProp ダイアログ


// ----------------------------------------------------------------
CDlgOperationProp::CDlgOperationProp(
		Mu<CentDedRessya*>* pMuRessya ,
		int iChakuEkiOrder ,
		int iHatsuEkiOrder,
		int iFocusItem ,
		bool bFocusAfter,
		int iFocusIndex,
		bool bFocusChild,
		bool bOuterHatsuChakuIsEnable,
		int iStandardShuntTrackIndex[],
		vector<vector<int>> iStandardOuterTerminalJikan,
		CKeyinputSenderToModalDlg*	pCKeyinputSenderToModalDlg ,
		CWnd* pParent  ) 
	: CDialog(CDlgOperationProp::IDD, pParent)
	, m_PropEditUiInternal( false , pMuRessya ,
		iChakuEkiOrder, iHatsuEkiOrder , bFocusAfter, iFocusIndex, bFocusChild,
		iStandardShuntTrackIndex, iStandardOuterTerminalJikan)
	, m_iFocusItem( iFocusItem )
	, m_bFocusAfter(bFocusAfter)
	, m_iFocusIndex(iFocusIndex)
	, m_bFocusChild(bFocusChild)
	, m_pCKeyinputSenderToModalDlg( pCKeyinputSenderToModalDlg )
	, m_iChakuEkiOrder(iChakuEkiOrder)
	, m_iHatsuEkiOrder(iHatsuEkiOrder)
	, m_bOuterHatsuChakuIsEnable(bOuterHatsuChakuIsEnable)
{
	//{{AFX_DATA_INIT(CDlgOperationProp)
	m_iRADIO_OperationType = -1;
	if (m_iChakuEkiOrder < 0)
	{
		m_iEkiIndex = pMuRessya->get(0)->EkiIndexOfEkiOrder(iHatsuEkiOrder);
	}
	else
	{
		m_iEkiIndex = pMuRessya->get(0)->EkiIndexOfEkiOrder(iChakuEkiOrder);
	}

	//発着時刻＆発車番線
	{
		if (m_iChakuEkiOrder >= 0)
		{
			m_ChakuJikoku = pMuRessya->get(0)->getCentDedEkiJikoku(m_iChakuEkiOrder).getChakujikoku(true);
		}

		if (m_iHatsuEkiOrder >= 0)
		{
			m_HatsuJikoku = pMuRessya->get(0)->getCentDedEkiJikoku(m_iHatsuEkiOrder).getHatsujikoku(true);
		}

		if (m_iChakuEkiOrder < 0)
		{
			m_iRessyaTrackIndex = pMuRessya->get(0)->getCentDedEkiJikoku(m_iHatsuEkiOrder).getRessyaTrackIndex();
		}
		else
		{
			m_iRessyaTrackIndex = pMuRessya->get(0)->getCentDedEkiJikoku(m_iChakuEkiOrder).getRessyaTrackIndex();
		}
	}
	//}}AFX_DATA_INIT
}


void CDlgOperationProp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOperationProp)
	DDX_Radio(pDX, IDC_RADIO_OperationType, m_iRADIO_OperationType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOperationProp, CDialog)
	//{{AFX_MSG_MAP(CDlgOperationProp)
	ON_WM_SHOWWINDOW()

	ON_BN_CLICKED(IDC_RADIO_OperationType, OnRADIOOperationType)
	ON_BN_CLICKED(IDC_RADIO_OperationType2, OnRADIOOperationType2)
	ON_BN_CLICKED(IDC_RADIO_OperationType3, OnRADIOOperationType3)
	ON_BN_CLICKED(IDC_RADIO_OperationType4, OnRADIOOperationType4)
	ON_BN_CLICKED(IDC_RADIO_OperationType5, OnRADIOOperationType5)
	ON_BN_CLICKED(IDC_RADIO_OperationType6, OnRADIOOperationType6)
	ON_BN_CLICKED(IDC_RADIO_OperationType7, OnRADIOOperationType7)
	ON_CBN_SELCHANGE(IDC_COMBO_Data1_0, &CDlgOperationProp::OnCbnSelchangeComboData1_0)
	ON_CBN_SELCHANGE(IDC_COMBO_Data1_1, &CDlgOperationProp::OnCbnSelchangeComboData1_1)
	ON_CBN_SELCHANGE(IDC_COMBO_Data1_2, &CDlgOperationProp::OnCbnSelchangeComboData1_2)
	ON_CBN_SELCHANGE(IDC_COMBO_Data1_4, &CDlgOperationProp::OnCbnSelchangeComboData1_4)
	ON_CBN_SELCHANGE(IDC_COMBO_Data1_5, &CDlgOperationProp::OnCbnSelchangeComboData1_5)
	ON_EN_KILLFOCUS(IDC_EDIT_Data1, &CDlgOperationProp::OnEnKillfocusEditData1)
	ON_EN_KILLFOCUS(IDC_EDIT_Data2, &CDlgOperationProp::OnEnKillfocusEditData2)
	ON_BN_CLICKED(IDC_CHECK_JikokuDisplay, &CDlgOperationProp::OnBnClickedCheckJikokudisplay)
	ON_EN_KILLFOCUS(IDC_EDIT_OperationNumbers, OnKillfocusEDITOperationNumber)
	ON_EN_KILLFOCUS(IDC_EDIT_InOutLinkCode, OnKillfocusEDITInOutLinkCode)

	ON_LBN_SELCHANGE(IDC_LIST_OperationBefore, &CDlgOperationProp::OnLbnSelchangeListOperationbefore)
	ON_LBN_SELCHANGE(IDC_LIST_OperationAfter, &CDlgOperationProp::OnLbnSelchangeListOperationafter)
	ON_BN_CLICKED(IDC_BUTTON_OperationAdd, &CDlgOperationProp::OnBnClickedButtonOperationadd)
	ON_BN_CLICKED(IDC_BUTTON_OperationInsert, &CDlgOperationProp::OnBnClickedButtonOperationinsert)
	ON_BN_CLICKED(IDC_BUTTON_ChildOperationAdd, &CDlgOperationProp::OnBnClickedButtonChildoperationadd)
	ON_BN_CLICKED(IDC_BUTTON_OperationClear, &CDlgOperationProp::OnBnClickedButtonOperationclear)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_OperationUp, &CDlgOperationProp::OnBnClickedButtonOperationup)
	ON_BN_CLICKED(IDC_BUTTON_OperationDown, &CDlgOperationProp::OnBnClickedButtonOperationdown)
	ON_BN_CLICKED(IDC_BUTTON_DecEdit1_1Min, &CDlgOperationProp::OnBnClickedButtonDecEdit1_1min)
	ON_BN_CLICKED(IDC_BUTTON_IncEdit1_1Min, &CDlgOperationProp::OnBnClickedButtonIncEdit1_1min)
	ON_BN_CLICKED(IDC_BUTTON_DecEdit1_5Min, &CDlgOperationProp::OnBnClickedButtonDecEdit1_5min)
	ON_BN_CLICKED(IDC_BUTTON_IncEdit1_5Min, &CDlgOperationProp::OnBnClickedButtonIncEdit1_5min)
	ON_BN_CLICKED(IDC_BUTTON_DecEdit1AnySec1, &CDlgOperationProp::OnBnClickedButtonDecEdit1anysec1)
	ON_BN_CLICKED(IDC_BUTTON_IncEdit1AnySec1, &CDlgOperationProp::OnBnClickedButtonIncEdit1anysec1)
	ON_BN_CLICKED(IDC_BUTTON_DecEdit1AnySec2, &CDlgOperationProp::OnBnClickedButtonDecEdit1anysec2)
	ON_BN_CLICKED(IDC_BUTTON_IncEdit1AnySec2, &CDlgOperationProp::OnBnClickedButtonIncEdit1anysec2)
	ON_BN_CLICKED(IDC_BUTTON_DecEdit2_1Min, &CDlgOperationProp::OnBnClickedButtonDecEdit2_1min)
	ON_BN_CLICKED(IDC_BUTTON_IncEdit2_1Min, &CDlgOperationProp::OnBnClickedButtonIncEdit2_1min)
	ON_BN_CLICKED(IDC_BUTTON_DecEdit2_5Min, &CDlgOperationProp::OnBnClickedButtonDecEdit2_5min)
	ON_BN_CLICKED(IDC_BUTTON_IncEdit2_5Min, &CDlgOperationProp::OnBnClickedButtonIncEdit2_5min)
	ON_BN_CLICKED(IDC_BUTTON_DecEdit2AnySec1, &CDlgOperationProp::OnBnClickedButtonDecEdit2anysec1)
	ON_BN_CLICKED(IDC_BUTTON_IncEdit2AnySec1, &CDlgOperationProp::OnBnClickedButtonIncEdit2anysec1)
	ON_BN_CLICKED(IDC_BUTTON_DecEdit2AnySec2, &CDlgOperationProp::OnBnClickedButtonDecEdit2anysec2)
	ON_BN_CLICKED(IDC_BUTTON_IncEdit2AnySec2, &CDlgOperationProp::OnBnClickedButtonIncEdit2anysec2)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOperationProp メッセージ ハンドラ

BOOL CDlgOperationProp::OnInitDialog() 
{
	LogMsg(_T("CDlgOperationProp::OnInitDialog()") ) ;

	CDialog::OnInitDialog();
	LogMsg(_T("CDlgOperationProp::OnInitDialog()1 ") ) ;


	//発着時刻＆発車番線
	{
		CStatic* pStaticTrack = (CStatic*)GetDlgItem(IDC_STATIC_RessyaTrack);
		CStatic* pStaticChaku = (CStatic*)GetDlgItem(IDC_STATIC_ChakuJikoku);
		CStatic* pStaticHatsu = (CStatic*)GetDlgItem(IDC_STATIC_HatsuJikoku);

		/** ダイアログボックスへの時刻の書式を保持します。 */
		const CdDedJikoku::CConv	g_CdDedJikokuConv(
			false,		//	Colon 
			CdDedJikoku::CConv::EHour_ZeroToNone,		//	HourZeroToNone 
			CdDedJikoku::CConv::ESecond_Output);	//	Output

		if (m_ChakuJikoku.isNull())
		{
			pStaticChaku->SetWindowText(_T("当駅始発"));
		}
		else
		{
			pStaticChaku->SetWindowText(
				g_CdDedJikokuConv.encode(m_ChakuJikoku).c_str());
		}

		if (m_HatsuJikoku.isNull())
		{
			pStaticHatsu->SetWindowText(_T("当駅止まり"));
		}
		else
		{
			pStaticHatsu->SetWindowText(
				g_CdDedJikokuConv.encode(m_HatsuJikoku).c_str());
		}
		const CentDedRosen* pCentDedRosen = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen();
		const CentDedEki* pCentDedEki = pCentDedRosen->getCentDedEkiCont()->getMuPtr()->get(m_iEkiIndex);
		pStaticTrack->SetWindowText(pCentDedEki->getEkiTrack2Cont()->get(m_iRessyaTrackIndex).getTrackName().c_str());
	}

	//IDC_COMBO_Data1_0 (入換番線)
	{
		const CentDedRosen* pCentDedRosen = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen();
		const Mu<const CentDedEkiTrack2*>* pMuCentDedEkiTrack2 =
			pCentDedRosen->getCentDedEkiCont()->getMuPtr()->get(m_iEkiIndex)->getEkiTrack2Cont()->getMuPtr();

		CComboBox*	pCComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_Data1_0);

		for (int idxEkiTrack2 = 0;
			idxEkiTrack2 < pMuCentDedEkiTrack2->size();
			idxEkiTrack2++)
		{
			const CentDedEkiTrack2* pCentDedEkiTrack2 =
				pMuCentDedEkiTrack2->get(idxEkiTrack2);

			tstring	strTrackName = pCentDedEkiTrack2->getTrackName();
			strTrackName = stringOf(idxEkiTrack2)
				+ _T(". ")
				+ strTrackName;

			pCComboBox->AddString(strTrackName.c_str());
		}
	}

	//IDC_COMBO_Data1_1(増結位置)
	{
		CComboBox*	pCComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_Data1_1);

		tstring strTemp1 = _T("編成後方に増結");
		pCComboBox->AddString(strTemp1.c_str());
		tstring strTemp2 = _T("編成前方に増結");
		pCComboBox->AddString(strTemp2.c_str());
	}

	//IDC_COMBO_Data1_2(解結位置)
	{
		CComboBox*	pCComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_Data1_2);

		tstring strTemp1 = _T("後方編成を解結(後方数指定)");
		pCComboBox->AddString(strTemp1.c_str());
		tstring strTemp2 = _T("前方編成を解結");
		pCComboBox->AddString(strTemp2.c_str());
		tstring strTemp3 = _T("後方編成を解結(前方数指定)");
		pCComboBox->AddString(strTemp3.c_str());
	}

	//IDC_COMBO_Data1_4(路線外始発駅)
	{
		const CentDedRosen* pCentDedRosen = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen();
		CentDedEki aCentDedEki = pCentDedRosen->getCentDedEkiCont()->get(m_iEkiIndex);

		CComboBox*	pCComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_Data1_4);

		for (int idx = 0;
			idx < aCentDedEki.getOuterTerminalEkimeiCount();
			idx++)
		{
			pCComboBox->AddString(aCentDedEki.getOuterTerminalEkimei(idx).c_str());
		}
	}
	//IDC_COMBO_Data1_5(次列車接続タイプ)
	{
		CComboBox* pCComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_Data1_5);

		tstring strTemp1 = _T("別列車");
		pCComboBox->AddString(strTemp1.c_str());
		tstring strTemp2 = _T("種別変更");
		pCComboBox->AddString(strTemp2.c_str());
		tstring strTemp3 = _T("列車情報変更");
		pCComboBox->AddString(strTemp3.c_str());
		tstring strTemp4 = _T("同一列車扱い");
		pCComboBox->AddString(strTemp4.c_str());
	}
	{
		LOGFONT lf;
		this->GetFont()->GetLogFont(&lf);
		//int a = lf.lfHeight;
		lf.lfHeight = 100;
		CFont font;
		font.CreatePointFontIndirect(&lf);
		CStatic* pStatic = (CStatic*)GetDlgItem(IDC_STATIC_ChakuJikoku);
		CStatic* pStatic2 = (CStatic*)GetDlgItem(IDC_STATIC_ChakuJikokuCaption);
		CStatic* pStatic3 = (CStatic*)GetDlgItem(IDC_STATIC_HatsuJikoku);
		CStatic* pStatic4 = (CStatic*)GetDlgItem(IDC_STATIC_HatsuJikokuCaption);
		CStatic* pStatic5 = (CStatic*)GetDlgItem(IDC_STATIC_RessyaTrackCaption);
		CStatic* pStatic6 = (CStatic*)GetDlgItem(IDC_STATIC_RessyaTrack);
		CStatic* pStatic7 = (CStatic*)GetDlgItem(IDC_STATIC_OperationBefore);
		CStatic* pStatic8 = (CStatic*)GetDlgItem(IDC_STATIC_OperationAfter);
		pStatic->SetFont(&font);
		pStatic2->SetFont(&font);
		pStatic3->SetFont(&font);
		pStatic4->SetFont(&font);
		pStatic5->SetFont(&font);
		pStatic6->SetFont(&font);
		pStatic7->SetFont(&font);
		pStatic8->SetFont(&font);
		font.Detach();
	}
	{
		int iAnySec1 = abs(getCDiagramEditDoc()->getCDedRosenFileData()
			->getCdDedDispProp().getAnySecondIncDec1());
		int iAnySec2 = abs(getCDiagramEditDoc()->getCDedRosenFileData()
			->getCdDedDispProp().getAnySecondIncDec2());

		m_AnySec1 = min(iAnySec1, iAnySec2);
		m_AnySec2 = max(iAnySec1, iAnySec2);

		CStatic* pStaticAnySec1 = (CStatic*)GetDlgItem(IDC_STATIC_AnySec1);
		CStatic* pStaticAnySec2 = (CStatic*)GetDlgItem(IDC_STATIC_AnySec2);

		tstring strAnySec1 = to_tstring(m_AnySec1) + _T("秒");
		pStaticAnySec1->SetWindowText(strAnySec1.c_str());
		tstring strAnySec2 = to_tstring(m_AnySec2) + _T("秒");
		pStaticAnySec2->SetWindowText(strAnySec2.c_str());

	}
	m_PropEditUiInternal.StartEdit() ;

	LogMsg(_T("CDlgOperationProp::OnInitDialog()= ") ) ;
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CDlgOperationProp::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	LogMsg(_T("CDlgOperationProp::OnShowWindow() ") ) ;
	CDialog::OnShowWindow(bShow, nStatus);
	LogMsg(_T("_T(CDlgOperationProp::OnShowWindow()1 ") ) ;
	
	if ( bShow ){
		CWnd* pControl = NULL ;
		switch( m_iFocusItem ){
		 case 0	:	//	駅扱
			pControl = GetDlgItem(IDC_RADIO_OperationType) ;
			break ;
		 case 1	:	//	コンボ1 入換番線
			pControl = GetDlgItem(IDC_COMBO_Data1_0) ;
			break ;
		 case 2	:	//	エディット1
			pControl = GetDlgItem( IDC_EDIT_Data1 ) ;
			break ;
		 case 3:	//	エディット2
			 pControl = GetDlgItem(IDC_EDIT_Data2);
			 break;
		 case 4:	//	運用番号
			 pControl = GetDlgItem(IDC_EDIT_OperationNumbers);
			 break;
		 case 5:	//	チェック1
			 pControl = GetDlgItem(IDC_CHECK_JikokuDisplay);
			 break;
		 case 6:	//	コンボ1 次列車接続タイプ(Ver2.05から)
			 pControl = GetDlgItem(IDC_COMBO_Data1_5);
			 break;
		 case 7:	//	コンボ1 増結位置
			 pControl = GetDlgItem(IDC_COMBO_Data1_1);
			 break;
		 case 8:	//	コンボ1 解結位置
			 pControl = GetDlgItem(IDC_COMBO_Data1_2);
			 break;
		 case 9:	//	コンボ1 路線外発着駅名
			 pControl = GetDlgItem(IDC_COMBO_Data1_4);
			 break;
		 case 10:	//	入出区連携コード(Ver2.05から)
			 pControl = GetDlgItem(IDC_EDIT_InOutLinkCode);
			 break;
		}
		if ( pControl != NULL ){
			GotoDlgCtrl( pControl ) ;
			if ( m_pCKeyinputSenderToModalDlg != NULL ){
				m_pCKeyinputSenderToModalDlg->registerCtrl( 
					pControl->GetSafeHwnd() ) ;
			}
		}
	}
	LogMsg(_T("CDlgOperationProp::OnShowWindow()= ") ) ;
	
	
}

void CDlgOperationProp::OnOK() 
{
	int iRv = 0 ;

	int iResult = m_PropEditUiInternal.EndEdit() ;
	if ( iResult >= 0 )
	{
		CDialog::OnOK();
	}
}


void CDlgOperationProp::OnRADIOOperationType()
{
	m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
	m_PropEditUiInternal.OnUiChanged();
}

void CDlgOperationProp::OnRADIOOperationType2()
{
	m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
	m_PropEditUiInternal.OnUiChanged();
}

void CDlgOperationProp::OnRADIOOperationType3()
{
	m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
	m_PropEditUiInternal.OnUiChanged();
}

void CDlgOperationProp::OnRADIOOperationType4()
{
	m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
	m_PropEditUiInternal.OnUiChanged();
}

void CDlgOperationProp::OnRADIOOperationType5()
{
	m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
	m_PropEditUiInternal.OnUiChanged();
}

void CDlgOperationProp::OnRADIOOperationType6()
{
	m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
	m_PropEditUiInternal.OnUiChanged();
}

void CDlgOperationProp::OnRADIOOperationType7()
{
	m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
	m_PropEditUiInternal.OnUiChanged();
}

void CDlgOperationProp::OnKillfocusEDITOperationNumber()
{
	m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
	m_PropEditUiInternal.OnUiChanged();
}

//void CDlgOperationProp::OnCbnSelchangeComboOuterTerminalIndex()
//{
//	m_PropEditUiInternal.OnUiChanged();
//}
//
//void CDlgOperationProp::OnKillfocusEDITOuterHatsuChakuJikoku()
//{
//	m_PropEditUiInternal.OnUiChanged();
//}


void ViewJikokuhyou::CDlgOperationProp::OnCbnSelchangeComboData1_0()
{
	m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
	m_PropEditUiInternal.OnUiChanged();
}
void ViewJikokuhyou::CDlgOperationProp::OnCbnSelchangeComboData1_1()
{
	m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
	m_PropEditUiInternal.OnUiChanged();
}
void ViewJikokuhyou::CDlgOperationProp::OnCbnSelchangeComboData1_2()
{
	m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
	m_PropEditUiInternal.OnUiChanged();
}
void ViewJikokuhyou::CDlgOperationProp::OnCbnSelchangeComboData1_4()
{
	m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
	m_PropEditUiInternal.OnUiChanged();
}

void ViewJikokuhyou::CDlgOperationProp::OnCbnSelchangeComboData1_5()
{
	m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
	m_PropEditUiInternal.OnUiChanged();
}

void ViewJikokuhyou::CDlgOperationProp::OnEnKillfocusEditData1()
{
	m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
	m_PropEditUiInternal.OnUiChanged();
}


void ViewJikokuhyou::CDlgOperationProp::OnEnKillfocusEditData2()
{
	m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
	m_PropEditUiInternal.OnUiChanged();
}


void ViewJikokuhyou::CDlgOperationProp::OnBnClickedCheckJikokudisplay()
{
	m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
	m_PropEditUiInternal.OnUiChanged();
}


void ViewJikokuhyou::CDlgOperationProp::OnKillfocusEDITInOutLinkCode()
{
	m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
	m_PropEditUiInternal.OnUiChanged();
}


void ViewJikokuhyou::CDlgOperationProp::OnLbnSelchangeListOperationbefore()
{

	m_PropEditUiInternal.GetUiData()->bSelectedAfter = false;
	CListBox* pListBox = (CListBox*)GetDlgItem(IDC_LIST_OperationBefore);
	m_PropEditUiInternal.GetUiData()->iListSelected = pListBox->GetCurSel();
	m_PropEditUiInternal.GetUiData()->iUiOperation = 1;
	m_PropEditUiInternal.OnUiDataChanged();
}


void ViewJikokuhyou::CDlgOperationProp::OnLbnSelchangeListOperationafter()
{
	m_PropEditUiInternal.GetUiData()->bSelectedAfter = true;
	CListBox* pListBox = (CListBox*)GetDlgItem(IDC_LIST_OperationAfter);
	m_PropEditUiInternal.GetUiData()->iListSelected = pListBox->GetCurSel();
	m_PropEditUiInternal.GetUiData()->iUiOperation = 1;
	m_PropEditUiInternal.OnUiDataChanged();
}


void ViewJikokuhyou::CDlgOperationProp::OnBnClickedButtonOperationadd()
{
	//UiDataに外からアクセスし、直接作業を追加します。
	//その後iLevelの補正も行います。
	bool bSelectedAfter = m_PropEditUiInternal.GetUiData()->bSelectedAfter;
	int iListSelected = m_PropEditUiInternal.GetUiData()->iListSelected;
	if (iListSelected >= 0)
	{
		/**
			追加された作業が持つiLevelです。これより大きなiLevelを持つものは、一つづつ値が繰り下がります
			繰り下がる条件
			(0)iAddPositionよりも下にある
			(1)iLevelの要素数が、iAddiLevel以上の物
				この値が1,1,1の場合→0・1・1,0などiLevelの要素数が少ないものは対象外
			(2)iLevelの値のうち、iAddiLevelの末尾要素以外の値が一致するもの
				この値が1,1,1の場合→1,2,0・2,1,1など、前方二つの値が異なるものは除外
			(3)iAddiLevelの末尾要素と同じ位置の値が、iAddiLevelの末尾要素の値以上のもの
				この値が1,1,1の場合→1,1,0・1,1,0,1などは除外
		*/
		vector<int> iAddiLevel;

		//作業を追加する、sOperation上の位置です、iLevel補正を誤って行わないためにも用います。
		int iAddPosition = 0;

		vector<Operation> sOperation;
		if (bSelectedAfter)
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationA;
		}
		else
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationB;
		}


		//実際に追加する位置とそのiLevelを求めます
		//「作業を追加」位置が選択されている場合は、新しい作業(入換)に置き換えます。
		if (sOperation[iListSelected].iOperation == 7)
		{
			sOperation.clear();
			sOperation.push_back(Operation());
			sOperation.front().iLevel = { 0 };
		}
		else 
		{
			if (sOperation[iListSelected].iOperation == 2)
			{
				iAddiLevel = sOperation[iListSelected].iLevel;
				/**
					解結作業の下に追加する場合は、解結作業の後作業群を飛び越した後方に追加を行う。
					追加場所条件は
					(1)iLevelの、iAddiLevelの末尾桁目の値が、iAddiLevelの当該桁の値と異なる(大きい)
						→この場合は、解結作業の一つ後の作業(その作業が増結なら、その前作業の最上位)の場所
					(2)iLevelの要素数が、iAddiLevelよりも少ない
						→この場合は、解結作業が、親となる増結作業の1番目の子作業に当たる場合、
					(3)idx=sOperation.size()-1まで探索しても見つからない場合は最後(idx=sOperation,size())
						→この場合は、最後の作業が解結作業
				*/
				iAddPosition = sOperation.size();//(3)の場合用、(1)(2)が該当する場合はそれで上書きされるので問題ない
				for (int idx = iListSelected + 1; idx < (int)sOperation.size(); idx++)
				{
					int iAddiLevelLastPos = iAddiLevel.size() - 1;
					if (sOperation[idx].iLevel.size() < iAddiLevel.size())
					{
						iAddPosition = idx;
						break;
					}
					else if (sOperation[idx].iLevel[iAddiLevelLastPos] != iAddiLevel[iAddiLevelLastPos])
					{
						iAddPosition = idx;
						break;
					}
				}
				iAddiLevel.back()++;//iAddLevelを上記探索で用いるので、ここで加算を行う
					//(先に加算した上で、判定条件を変えてもよいが、insertと判定式を合わせるため)
			}
			else
			{
				iAddiLevel = sOperation[iListSelected].iLevel;
				iAddiLevel.back()++;
				iAddPosition = iListSelected + 1;
			}

			sOperation.insert(sOperation.begin() + iAddPosition, Operation());
			sOperation[iAddPosition].iLevel = iAddiLevel;

			//既存項目のiLevelの補正作業
			for (int idx = iAddPosition + 1; idx < (int)sOperation.size(); idx++)
			{
				//まず、追加された要素自身と、追加された要素より親側の要素を除外
				if (/*idx != iAddPosition &&*/
					sOperation[idx].iLevel.size() >= iAddiLevel.size())
				{
					//追加された要素と、親作業が同一か否かをチェック
					bool bMatch = true;
					//iAddiLevel.size()が1の場合は、forに入らないが問題ない。前方に値が無い、という意味で一致
					for (int idxl = 0; idxl < (int)iAddiLevel.size() - 1; idxl++)
					{
						if (sOperation[idx].iLevel[idxl] != iAddiLevel[idxl])
						{
							bMatch = false;
							break;
						}
					}
					if (bMatch &&
						sOperation[idx].iLevel[iAddiLevel.size() - 1] >= iAddiLevel.back())
					{
						sOperation[idx].iLevel[iAddiLevel.size() - 1]++;
					}
				}
			}
		}
		if (bSelectedAfter)
		{
			m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
		}
		else
		{
			m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
		}
		m_PropEditUiInternal.GetUiData()->iUiOperation = 2;
		m_PropEditUiInternal.GetUiData()->iListSelected = iAddPosition;
	}
	m_PropEditUiInternal.OnUiDataChanged();
}

//void AdjustiLevel

void ViewJikokuhyou::CDlgOperationProp::OnBnClickedButtonOperationinsert()
{
	//UiDataに外からアクセスし、直接作業を挿入します。
	//その後iLevelの補正も行います。
	bool bSelectedAfter = m_PropEditUiInternal.GetUiData()->bSelectedAfter;
	int iListSelected = m_PropEditUiInternal.GetUiData()->iListSelected;
	if ( iListSelected >= 0)
	{
		/**
			追加された作業が持つiLevelです。これより大きなiLevelを持つものは、一つづつ値が繰り下がります
			繰り下がる条件
			(0)iAddPositionよりも下にある
			(1)iLevelの要素数が、iAddiLevel以上の物
				この値が1,1,1の場合→0・1・1,0などiLevelの要素数が少ないものは対象外
			(2)iLevelの値のうち、iAddiLevelの末尾要素以外の値が一致するもの
				この値が1,1,1の場合→1,2,0・2,1,1など、前方二つの値が異なるものは除外
			(3)iAddiLevelの末尾要素と同じ位置の値が、iAddiLevelの末尾要素の値以上のもの
				この値が1,1,1の場合→1,1,0・1,1,0,1などは除外
		*/
		vector<int> iAddiLevel;

		//作業を追加する、sOperation上の位置です、iLevel補正を誤って行わないためにも用います。
		int iAddPosition = 0;

		vector<Operation> sOperation;
		if(bSelectedAfter)
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationA;
		}
		else
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationB;
		}

		//実際に追加する位置とそのiLevelを求めます
		//「作業を追加」位置が選択されている場合は、新しい作業(入換)に置き換えます。
		if (sOperation[iListSelected].iOperation == 7)
		{
			sOperation.clear();
			sOperation.push_back(Operation());
			sOperation.front().iLevel = { 0 };
		}
		else
		{
			if (sOperation[iListSelected].iOperation == 1)
			{
				iAddiLevel = sOperation[iListSelected].iLevel;
				/**
					増結作業の場所に挿入する場合は、増結作業の前作業群を飛び越した前方に追加を行う。
					挿入場所条件は
					(1)iLevelの、iAddiLevelの末尾桁目の値が、iAddiLevelの当該桁の値と異なる(小さい)
						→この場合は、増結作業の一つ前の作業(その作業が解結なら、その後作業の最下位)の場所
					(2)iLevelの要素数が、iAddiLevelよりも少ない
						→この場合は、増結作業が、親となる解結作業の1番目の子作業に当たる場合、
					(3)idx=0まで探索しても見つからない場合は最初(idx=0)
						→この場合は、最初の作業が増結作業
				*/
				iAddPosition = 0;//(3)の場合用、(1)(2)が該当する場合はそれで上書きされるので問題ない
				for (int idx = iListSelected - 1; idx >= 0; idx--)
				{
					int iAddiLevelLastPos = iAddiLevel.size() - 1;
					if (sOperation[idx].iLevel.size() < iAddiLevel.size())
					{
						iAddPosition = idx+1;
						break;
					}
					else if (sOperation[idx].iLevel[iAddiLevelLastPos] != iAddiLevel[iAddiLevelLastPos])
					{
						iAddPosition = idx+1;
						break;
					}
				}
			}
			else
			{
				iAddiLevel = sOperation[iListSelected].iLevel;
				iAddPosition = iListSelected;
			}

			sOperation.insert(sOperation.begin() + iAddPosition, Operation());
			sOperation[iAddPosition].iLevel = iAddiLevel;

			//既存項目のiLevelの補正作業
			for (int idx = iAddPosition + 1; idx < (int)sOperation.size(); idx++)
			{
				//まず、追加された要素自身と、追加された要素より親側の要素を除外
				if (/*idx != iAddPosition &&*/
					sOperation[idx].iLevel.size() >= iAddiLevel.size())
				{
					//追加された要素と、親作業が同一か否かをチェック
					bool bMatch = true;
					//iAddiLevel.size()が1の場合は、forに入らないが問題ない。前方に値が無い、という意味で一致
					for (int idxl = 0; idxl < (int)iAddiLevel.size() - 1; idxl++)
					{
						if (sOperation[idx].iLevel[idxl] != iAddiLevel[idxl])
						{
							bMatch = false;
							break;
						}
					}
					if (bMatch &&
						sOperation[idx].iLevel[iAddiLevel.size() - 1] >= iAddiLevel.back())
					{
						sOperation[idx].iLevel[iAddiLevel.size() - 1]++;
					}
				}
			}
		}

		if (bSelectedAfter)
		{
			m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
		}
		else
		{
			m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
		}
		m_PropEditUiInternal.GetUiData()->iUiOperation = 2;
		m_PropEditUiInternal.GetUiData()->iListSelected = iAddPosition;
	}

	m_PropEditUiInternal.OnUiDataChanged();
}


void ViewJikokuhyou::CDlgOperationProp::OnBnClickedButtonChildoperationadd()
{
	//UiDataに外からアクセスし、直接作業を挿入します。
	//その後iLevelの補正も行います。
	bool bSelectedAfter = m_PropEditUiInternal.GetUiData()->bSelectedAfter;
	int iListSelected = m_PropEditUiInternal.GetUiData()->iListSelected;
	if (iListSelected >= 0)
	{
		/**
			追加された作業が持つiLevelです。これより大きなiLevelを持つものは、一つづつ値が繰り下がります
			繰り下がる条件
			(1)iLevelの要素数が、iAddiLevel以上の物
				この値が1,1,1の場合→0・1・1,0などiLevelの要素数が少ないものは対象外
			(2)iLevelの値のうち、iAddiLevelの末尾要素以外の値が一致するもの
				この値が1,1,1の場合→1,2,0・2,1,1など、前方二つの値が異なるものは除外
			(3)iAddiLevelの末尾要素と同じ位置の値が、iAddiLevelの末尾要素の値以上のもの
				この値が1,1,1の場合→1,1,0・1,1,0,1などは除外
			(4)追加された作業自身は除く。iAddPositionで判定
		*/
		vector<int> iAddiLevel;

		//作業を追加する、sOperation上の位置です、iLevel補正を誤って行わないためにも用います。
		int iAddPosition = 0;

		vector<Operation> sOperation;
		if (bSelectedAfter)
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationA;
		}
		else
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationB;
		}

		//実際に追加する位置とそのiLevelを求めます
		if (sOperation[iListSelected].iOperation == 1)
		{
			/**
				選択位置が増結の場合は、選択位置に前作業を挿入します
			*/
			//iAddiLevelは、前作業最下位のものを基に、末尾要素に1加算したものです。
			//増結作業の前作業には、必ず一つ以上の作業が入っているので、決め打ちで取得できます。
			iAddiLevel = sOperation[iListSelected - 1].iLevel;
			iAddiLevel.back()++;
			iAddPosition = iListSelected;
		}
		else if (sOperation[iListSelected].iOperation == 2)
		{
			/**
				選択位置が解結の場合は、選択位置の一つ下に後作業を挿入します
			*/
			//iAddiLevelは、後作業最上位のものを引き継ぎます。
			//解結作業の後作業には、必ず一つ以上の作業が入っているので、決め打ちで取得できます。
			iAddiLevel = sOperation[iListSelected + 1].iLevel;
			iAddPosition = iListSelected + 1;

			m_PropEditUiInternal.GetUiData()->iListSelected++;
		}

		sOperation.insert(sOperation.begin() + iAddPosition, Operation());
		sOperation[iAddPosition].iLevel = iAddiLevel;

		//既存項目のiLevelの補正作業
		for (int idx = 0; idx < (int)sOperation.size(); idx++)
		{
			//まず、追加された要素自身と、追加された要素より親側の要素を除外
			if (idx != iAddPosition &&
				sOperation[idx].iLevel.size() >= iAddiLevel.size())
			{
				//追加された要素と、親作業が同一か否かをチェック
				bool bMatch = true;
				//iAddiLevel.size()が1の場合は、forに入らないが問題ない.前方に値が無い、という意味で一致
				for (int idxl = 0; idxl < (int)iAddiLevel.size() - 1; idxl++)
				{
					if (sOperation[idx].iLevel[idxl] != iAddiLevel[idxl])
					{
						bMatch = false;
						break;
					}
				}
				if (bMatch &&
					sOperation[idx].iLevel[iAddiLevel.size() - 1] >= iAddiLevel.back())
				{
					sOperation[idx].iLevel[iAddiLevel.size() - 1]++;
				}
			}
		}

		if (bSelectedAfter)
		{
			m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
		}
		else
		{
			m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
		}
		m_PropEditUiInternal.GetUiData()->iUiOperation = 2;
	}

	m_PropEditUiInternal.OnUiDataChanged();
}


void ViewJikokuhyou::CDlgOperationProp::OnBnClickedButtonOperationclear()
{
	//UiDataに外からアクセスし、直接作業を削除します。
	//削除対象が増解結の場合は、その子作業も削除します。
	//その後iLevelの補正も行います。
	bool bSelectedAfter = m_PropEditUiInternal.GetUiData()->bSelectedAfter;
	int iListSelected = m_PropEditUiInternal.GetUiData()->iListSelected;
	if (iListSelected >= 0)
	{
		/**
			削除された作業が持つiLevelです。これより大きなiLevelを持つものは、一つづつ値が繰り上がります
			繰り上がり条件
			(0)iDelPositionよりも下にある
			(1)iLevelの要素数が、iDeliLevel以上の物
				この値が1,1,1の場合→0・1・1,0などiLevelの要素数が少ないものは対象外
			(2)iLevelの値のうち、iDeliLevelの末尾要素以外の値が一致するもの
				この値が1,1,1の場合→1,2,0・2,1,1など、前方二つの値が異なるものは除外
			(3)iAddiLevelの末尾要素と同じ位置の値が、iDeliLevelの末尾要素の値以上のもの
				この値が1,1,1の場合→1,1,0・1,1,0,1などは除外
		*/
		vector<int> iDeliLevel;

		//作業を削除する、sOperation上の位置です、iLevel補正を誤って行わないためにも用います。
		int iDelPosition = iListSelected;
		//作業を削除する個数です。削除対象が増解結の場合は、その子作業も削除するので、
		//それを含めた数になります。
		int iDelSize = 1;

		vector<Operation> sOperation;
		if (bSelectedAfter)
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationA;
		}
		else
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationB;
		}

		iDeliLevel = sOperation[iListSelected].iLevel;

		if (sOperation[iListSelected].iOperation == 1)
		{
			/**
				増結の場合は、前作業も併せて削除します
			*/
			for (int idxb = iListSelected - 1; idxb >= 0; idxb--)
			{
				/**
					まず、idxb位置のiLevelの要素数を確認、要素数がiDeliLevel以下なら、子作業ではないので探索終了です
				*/
				if (sOperation[idxb].iLevel.size() <= iDeliLevel.size())
				{
					break;
				}
				/**
					要素数がiDeliLevelより多い場合は、iDeliLevelの要素数までの値が、一致するか否かを調べます
				*/
				bool bMatch = true;
				//iAddiLevel.size()が1の場合は、forに入らないが問題ない。前方に値が無い、という意味で一致
				for (int idxl = 0; idxl < (int)iDeliLevel.size() ; idxl++)
				{
					if (sOperation[idxb].iLevel[idxl] != iDeliLevel[idxl])
					{
						/**
							値が不一致の場合、それより先には子作業は無いので、bMatchをfalseにして探索を抜けます。
						*/
						bMatch = false;
						break;
					}
				}
				if (!bMatch)
				{
					break;
				}
				/**
					iDeliLevel.size()個の値が一致した場合、その作業は子作業です、
					iDelPositionを-1し、iDelSizeを+1します。(削除は後で行う)
				*/
				iDelPosition--;
				iDelSize++;
			}

		}
		else if (sOperation[iListSelected].iOperation == 2)
		{
			/**
				解結の場合は、後作業も併せて削除します
			*/
			for (int idxa = iListSelected + 1; idxa < (int)sOperation.size(); idxa++)
			{
				/**
					まず、idxa位置のiLevelの要素数を確認、要素数がiDeliLevel以下なら、子作業ではないので探索終了です
				*/
				if (sOperation[idxa].iLevel.size() <= iDeliLevel.size())
				{
					break;
				}
				/**
					要素数がiDeliLevelより多い場合は、iDeliLevelの要素数までの値が、一致するか否かを調べます
				*/
				bool bMatch = true;
				//iAddiLevel.size()が1の場合は、forに入らないが問題ない。前方に値が無い、という意味で一致
				for (int idxl = 0; idxl < (int)iDeliLevel.size(); idxl++)
				{
					if (sOperation[idxa].iLevel[idxl] != iDeliLevel[idxl])
					{
						/**
							値が不一致の場合、それより先には子作業は無いので、bMatchをfalseにして探索を抜けます。
						*/
						bMatch = false;
						break;
					}
				}
				if (!bMatch)
				{
					break;
				}
				/**
					iDeliLevel.size()個の値が一致した場合、その作業は子作業です、
					iDelSizeを+1します。(削除は後で行う)
				*/
				iDelSize++;
			}
		}

		sOperation.erase(sOperation.begin() + iDelPosition, sOperation.begin() + iDelPosition + iDelSize);

		//既存項目のiLevelの補正作業
		for (int idx = iDelPosition ; idx < (int)sOperation.size(); idx++)
		{
			//追加された要素より親側の要素を除外
			if (sOperation[idx].iLevel.size() >= iDeliLevel.size())
			{
				//追加された要素と、親作業が同一か否かをチェック
				bool bMatch = true;
				//iDeliLevel.size()が1の場合は、forに入らないが問題ない。前方に値が無い、という意味で一致
				for (int idxl = 0; idxl < (int)iDeliLevel.size() - 1; idxl++)
				{
					if (sOperation[idx].iLevel[idxl] != iDeliLevel[idxl])
					{
						bMatch = false;
						break;
					}
				}
				if (bMatch &&
					sOperation[idx].iLevel[iDeliLevel.size() - 1] >= iDeliLevel.back())
				{
					sOperation[idx].iLevel[iDeliLevel.size() - 1]--;
				}
			}
		}
		//削除後に、作業数が0になった場合は、(作業を追加)の作業を追加します
		if (sOperation.size() == 0)
		{
			Operation sOperationAdd;
			sOperationAdd.iOperation = 7;
			sOperationAdd.iLevel.push_back(0);
			sOperation.push_back(sOperationAdd);
		}
		if (bSelectedAfter)
		{
			m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
		}
		else
		{
			m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
		}
		m_PropEditUiInternal.GetUiData()->iUiOperation = 3;
		if ((int)sOperation.size() <= iListSelected)
		{
			m_PropEditUiInternal.GetUiData()->iListSelected = sOperation.size() - 1;
		}
	}

	m_PropEditUiInternal.OnUiDataChanged();
}

void ViewJikokuhyou::CDlgOperationProp::OnBnClickedButtonOperationup()
{
	//UiDataに外からアクセスし、直接作業を入れ替えます。
	//その後iLevelの補正も行います。
	bool bSelectedAfter = m_PropEditUiInternal.GetUiData()->bSelectedAfter;
	int iListSelected = m_PropEditUiInternal.GetUiData()->iListSelected;
	if (iListSelected >= 0)
	{
		/**
			入れ替え対象となるiLevelです。これより大きなiLevelを持つものは、一つづつ値が繰り下がります
			繰り下がる条件
			(0)iAddPositionよりも下にある
			(1)iLevelの要素数が、iAddiLevel以上の物
				この値が1,1,1の場合→0・1・1,0などiLevelの要素数が少ないものは対象外
			(2)iLevelの値のうち、iAddiLevelの末尾要素以外の値が一致するもの
				この値が1,1,1の場合→1,2,0・2,1,1など、前方二つの値が異なるものは除外
			(3)iAddiLevelの末尾要素と同じ位置の値が、iAddiLevelの末尾要素の値以上のもの
				この値が1,1,1の場合→1,1,0・1,1,0,1などは除外
		*/
		vector<int> iUpperiLevel;
		vector<int> iLoweriLevel;

		//作業を追加する、sOperation上の位置です、iLevel補正を誤って行わないためにも用います。
		int iUpperPosition = 0;
		int iLowerPosition = iListSelected;
		int iLowerCount = 1;
		int iUpperCount = 1;
		int iFocusShift = 0;

		vector<Operation> sOperation;
		if (bSelectedAfter)
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationA;
		}
		else
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationB;
		}

		//入換先の位置とそのiLevelを求めます
		{
			iLoweriLevel = sOperation[iListSelected].iLevel;
			if (sOperation[iListSelected].iOperation == 1)
			{
				/**
					増結作業を移動する場合は、子作業もまとめて移動します。

				*/
				for (int idx = iListSelected - 1; idx >= 0; idx--)
				{
					if (sOperation[idx].iLevel.size() <= iLoweriLevel.size())
					{
						continue;
					}
					bool bMatchiLevel = true;
					for (int idxiLevel = 0; idxiLevel < (int)iLoweriLevel.size() && bMatchiLevel; idxiLevel++)
					{
						if (sOperation[idx].iLevel[idxiLevel] != iLoweriLevel[idxiLevel])
						{
							bMatchiLevel = false;
						}
						if (idxiLevel == (int)iLoweriLevel.size() - 1 &&
							bMatchiLevel)
						{
							iLowerPosition--;
							iLowerCount++;
							iFocusShift++;
						}
					}
				}
			}
			else if (sOperation[iListSelected].iOperation == 2)
			{
				/**
					解結作業を移動する場合は、子作業もまとめて移動します。

				*/
				for (int idx = iListSelected + 1; idx < (int)sOperation.size(); idx++)
				{
					if (sOperation[idx].iLevel.size() <= iLoweriLevel.size())
					{
						continue;
					}
					bool bMatchiLevel = true;
					for (int idxiLevel = 0; idxiLevel < (int)iLoweriLevel.size() && bMatchiLevel; idxiLevel++)
					{
						if (sOperation[idx].iLevel[idxiLevel] != iLoweriLevel[idxiLevel])
						{
							bMatchiLevel = false;
						}
						if (idxiLevel == (int)iLoweriLevel.size() - 1 &&
							bMatchiLevel)
						{
							iLowerCount++;
						}
					}
				}
			}

			//入れ替え先は、入換元のiLevelの末尾桁が、1少ないもの
			iUpperiLevel = iLoweriLevel;
			iUpperiLevel.back()--;

			for (int idx = iListSelected - 1; idx >= 0; idx--)
			{
				if (sOperation[idx].iLevel.size() != iUpperiLevel.size())
				{
					continue;
				}
				bool bMatchiLevel = true;
				for (int idxiLevel = 0; idxiLevel < (int)iUpperiLevel.size() && bMatchiLevel; idxiLevel++)
				{
					if (sOperation[idx].iLevel[idxiLevel] != iUpperiLevel[idxiLevel])
					{
						bMatchiLevel = false;
					}
					if (idxiLevel == (int)iUpperiLevel.size() - 1 &&
						bMatchiLevel)
					{
						iUpperPosition = idx;
					}
				}
				if (bMatchiLevel)
				{
					break;
				}
			}
			if (sOperation[iUpperPosition].iOperation == 1)
			{
				/**
					入れ替え先が増結作業の場合は、その子作業の前が入れ替え先となります。

				*/
				for (int idx = iUpperPosition - 1; idx >= 0; idx--)
				{
					if (sOperation[idx].iLevel.size() <= iUpperiLevel.size())
					{
						continue;
					}
					bool bMatchiLevel = true;
					for (int idxiLevel = 0; idxiLevel < (int)iUpperiLevel.size() && bMatchiLevel; idxiLevel++)
					{
						if (sOperation[idx].iLevel[idxiLevel] != iUpperiLevel[idxiLevel])
						{
							bMatchiLevel = false;
						}
						if (idxiLevel == (int)iUpperiLevel.size() - 1 &&
							bMatchiLevel)
						{
							iUpperPosition--;
							iUpperCount++;
						}
					}
				}
			}
			else if (sOperation[iUpperPosition].iOperation == 2)
			{
				/**
					解結作業

				*/
				for (int idx = iUpperPosition + 1; idx < (int)sOperation.size(); idx++)
				{
					if (sOperation[idx].iLevel.size() <= iUpperiLevel.size())
					{
						continue;
					}
					bool bMatchiLevel = true;
					for (int idxiLevel = 0; idxiLevel < (int)iUpperiLevel.size() && bMatchiLevel; idxiLevel++)
					{
						if (sOperation[idx].iLevel[idxiLevel] != iUpperiLevel[idxiLevel])
						{
							bMatchiLevel = false;
						}
						if (idxiLevel == (int)iUpperiLevel.size() - 1 &&
							bMatchiLevel)
						{
							iUpperCount++;
						}
					}
				}
			}
			vector<Operation> contLower(sOperation.begin() + iLowerPosition, sOperation.begin() + iLowerPosition + iLowerCount);
			sOperation.erase(sOperation.begin() + iLowerPosition, sOperation.begin() + iLowerPosition + iLowerCount);

			//既存項目のiLevelの補正作業
			int iLevelAdjustidx = iLoweriLevel.size() - 1;
			for (int idx = 0; idx < (int)contLower.size(); idx++)
			{
				contLower[idx].iLevel[iLevelAdjustidx]--;
			}
			for (int idx = iUpperPosition ; idx < iUpperPosition+ iUpperCount; idx++)
			{
				sOperation[idx].iLevel[iLevelAdjustidx]++;
			}

			sOperation.insert(sOperation.begin() + iUpperPosition, contLower.begin(), contLower.end());

		}

		if (bSelectedAfter)
		{
			m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
		}
		else
		{
			m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
		}
		m_PropEditUiInternal.GetUiData()->iUiOperation = 1;
		m_PropEditUiInternal.GetUiData()->iListSelected = iUpperPosition+ iFocusShift;
	}

	m_PropEditUiInternal.OnUiDataChanged();
}


void ViewJikokuhyou::CDlgOperationProp::OnBnClickedButtonOperationdown()
{
	//UiDataに外からアクセスし、直接作業を入れ替えます。
	//その後iLevelの補正も行います。
	bool bSelectedAfter = m_PropEditUiInternal.GetUiData()->bSelectedAfter;
	int iListSelected = m_PropEditUiInternal.GetUiData()->iListSelected;
	if (iListSelected >= 0)
	{
		/**
			入れ替え対象となるiLevelです。これより大きなiLevelを持つものは、一つづつ値が繰り下がります
			繰り下がる条件
			(0)iAddPositionよりも下にある
			(1)iLevelの要素数が、iAddiLevel以上の物
				この値が1,1,1の場合→0・1・1,0などiLevelの要素数が少ないものは対象外
			(2)iLevelの値のうち、iAddiLevelの末尾要素以外の値が一致するもの
				この値が1,1,1の場合→1,2,0・2,1,1など、前方二つの値が異なるものは除外
			(3)iAddiLevelの末尾要素と同じ位置の値が、iAddiLevelの末尾要素の値以上のもの
				この値が1,1,1の場合→1,1,0・1,1,0,1などは除外
		*/
		vector<int> iUpperiLevel;
		vector<int> iLoweriLevel;

		//作業を追加する、sOperation上の位置です、iLevel補正を誤って行わないためにも用います。
		int iUpperPosition = iListSelected;
		int iLowerPosition = 0;
		int iLowerCount = 1;
		int iUpperCount = 1;
		int iFocusShift = 0;

		vector<Operation> sOperation;
		if (bSelectedAfter)
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationA;
		}
		else
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationB;
		}

		//入換先の位置とそのiLevelを求めます
		{
			iUpperiLevel = sOperation[iListSelected].iLevel;
			if (sOperation[iListSelected].iOperation == 1)
			{
				/**
					増結作業を移動する場合は、子作業もまとめて移動します。

				*/
				for (int idx = iListSelected - 1; idx >= 0; idx--)
				{
					if (sOperation[idx].iLevel.size() <= iUpperiLevel.size())
					{
						continue;
					}
					bool bMatchiLevel = true;
					for (int idxiLevel = 0; idxiLevel < (int)iUpperiLevel.size() && bMatchiLevel; idxiLevel++)
					{
						if (sOperation[idx].iLevel[idxiLevel] != iUpperiLevel[idxiLevel])
						{
							bMatchiLevel = false;
						}
						if (idxiLevel == (int)iUpperiLevel.size() - 1 &&
							bMatchiLevel)
						{
							iUpperPosition--;
							iUpperCount++;
							iFocusShift++;
						}
					}
				}
			}
			else if (sOperation[iListSelected].iOperation == 2)
			{
				/**
					解結作業を移動する場合は、子作業もまとめて移動します。

				*/
				for (int idx = iListSelected + 1; idx < (int)sOperation.size(); idx++)
				{
					if (sOperation[idx].iLevel.size() <= iUpperiLevel.size())
					{
						continue;
					}
					bool bMatchiLevel = true;
					for (int idxiLevel = 0; idxiLevel < (int)iUpperiLevel.size() && bMatchiLevel; idxiLevel++)
					{
						if (sOperation[idx].iLevel[idxiLevel] != iUpperiLevel[idxiLevel])
						{
							bMatchiLevel = false;
						}
						if (idxiLevel == (int)iUpperiLevel.size() - 1 &&
							bMatchiLevel)
						{
							iUpperCount++;
						}
					}
				}
			}

			//入れ替え先は、入換元のiLevelの末尾桁が、1大きいもの
			iLoweriLevel = iUpperiLevel;
			iLoweriLevel.back()++;

			for (int idx = iListSelected + 1; idx < (int)sOperation.size(); idx++)
			{
				if (sOperation[idx].iLevel.size() != iLoweriLevel.size())
				{
					continue;
				}
				bool bMatchiLevel = true;
				for (int idxiLevel = 0; idxiLevel < (int)iLoweriLevel.size() && bMatchiLevel; idxiLevel++)
				{
					if (sOperation[idx].iLevel[idxiLevel] != iLoweriLevel[idxiLevel])
					{
						bMatchiLevel = false;
					}
					if (idxiLevel == (int)iLoweriLevel.size() - 1 &&
						bMatchiLevel)
					{
						iLowerPosition = idx;
					}
				}
				if (bMatchiLevel)
				{
					break;
				}
			}
			if (sOperation[iLowerPosition].iOperation == 1)
			{
				/**
					入れ替え先が増結作業の場合は、その子作業の前が入れ替え先となります。

				*/
				for (int idx = iLowerPosition - 1; idx >= 0; idx--)
				{
					if (sOperation[idx].iLevel.size() <= iLoweriLevel.size())
					{
						continue;
					}
					bool bMatchiLevel = true;
					for (int idxiLevel = 0; idxiLevel < (int)iLoweriLevel.size() && bMatchiLevel; idxiLevel++)
					{
						if (sOperation[idx].iLevel[idxiLevel] != iLoweriLevel[idxiLevel])
						{
							bMatchiLevel = false;
						}
						if (idxiLevel == (int)iLoweriLevel.size() - 1 &&
							bMatchiLevel)
						{
							iLowerPosition--;
							iLowerCount++;
						}
					}
				}
			}
			else if (sOperation[iLowerPosition].iOperation == 2)
			{
				/**
					解結作業

				*/
				for (int idx = iLowerPosition + 1; idx < (int)sOperation.size(); idx++)
				{
					if (sOperation[idx].iLevel.size() <= iLoweriLevel.size())
					{
						continue;
					}
					bool bMatchiLevel = true;
					for (int idxiLevel = 0; idxiLevel < (int)iLoweriLevel.size() && bMatchiLevel; idxiLevel++)
					{
						if (sOperation[idx].iLevel[idxiLevel] != iLoweriLevel[idxiLevel])
						{
							bMatchiLevel = false;
						}
						if (idxiLevel == (int)iLoweriLevel.size() - 1 &&
							bMatchiLevel)
						{
							iLowerCount++;
						}
					}
				}
			}
			vector<Operation> contLower(sOperation.begin() + iLowerPosition, sOperation.begin() + iLowerPosition + iLowerCount);
			sOperation.erase(sOperation.begin() + iLowerPosition, sOperation.begin() + iLowerPosition + iLowerCount);

			//既存項目のiLevelの補正作業
			int iLevelAdjustidx = iLoweriLevel.size() - 1;
			for (int idx = 0; idx < (int)contLower.size(); idx++)
			{
				contLower[idx].iLevel[iLevelAdjustidx]--;
			}
			for (int idx = iUpperPosition; idx < iUpperPosition + iUpperCount; idx++)
			{
				sOperation[idx].iLevel[iLevelAdjustidx]++;
			}

			sOperation.insert(sOperation.begin() + iUpperPosition, contLower.begin(), contLower.end());

		}

		if (bSelectedAfter)
		{
			m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
		}
		else
		{
			m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
		}
		m_PropEditUiInternal.GetUiData()->iUiOperation = 1;
		m_PropEditUiInternal.GetUiData()->iListSelected = iUpperPosition + iLowerCount + iFocusShift;
	}

	m_PropEditUiInternal.OnUiDataChanged();
}

/** ダイアログボックスへの時刻の書式を保持します。 */
const CdDedJikoku::CConv	g_CdDedJikokuConv(
	true,		//	NoColon 
	CdDedJikoku::CConv::EHour_ZeroToNone,		//	HourZeroToNone 
	CdDedJikoku::CConv::ESecond_NotIfZero);	//	NoSecond


void CDlgOperationProp::OnBnClickedButtonDecEdit1_1min()
{
	bool bSelectedAfter = m_PropEditUiInternal.GetUiData()->bSelectedAfter;
	int iListSelected = m_PropEditUiInternal.GetUiData()->iListSelected;
	if (iListSelected >= 0)
	{
		vector<Operation> sOperation;
		if (bSelectedAfter)
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationA;
		}
		else
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationB;
		}

		if (sOperation[iListSelected].iOperation == 0 ||
			sOperation[iListSelected].iOperation == 1 ||
			sOperation[iListSelected].iOperation == 3 ||
			sOperation[iListSelected].iOperation == 4 ||
			sOperation[iListSelected].iOperation == 5)
		{
			tstring strJikokuOld = sOperation[iListSelected].strEditData1;
			if (!strJikokuOld.empty())
			{
				CdDedJikoku aJikoku(strJikokuOld);
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(-60);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData1 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
			else if(sOperation[iListSelected].iOperation == 0)
			{
				CdDedJikoku aJikoku;
				tstring strOperationChakuJikoku = sOperation[iListSelected].strEditData2;
				if (!strOperationChakuJikoku.empty())
				{
					aJikoku.decode(strOperationChakuJikoku);
				}
				if (aJikoku.isNull())
				{
					if (m_iHatsuEkiOrder == -1 ||
						!bSelectedAfter && m_iChakuEkiOrder >= 0)
					{
						aJikoku = m_ChakuJikoku;
					}
					else
					{
						aJikoku = m_HatsuJikoku;
					}
				}
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(-60);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData1 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
			else
			{
				CdDedJikoku aJikoku;
				if (m_iHatsuEkiOrder == -1 ||
					!bSelectedAfter && m_iChakuEkiOrder >= 0)
				{
					aJikoku = m_ChakuJikoku;
				}
				else
				{
					aJikoku = m_HatsuJikoku;
				}
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(-60);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData1 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
		}
		else if (sOperation[iListSelected].iOperation == 2)
		{
			int iOld = _ttoi(sOperation[iListSelected].strEditData1.c_str());
			if (iOld > 1)
			{
				sOperation[iListSelected].strEditData1 = to_tstring(iOld - 1);

				if (bSelectedAfter)
				{
					m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
				}
				else
				{
					m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
				}
				m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
			}
		}
	}
	m_PropEditUiInternal.OnUiDataChanged();
}

void CDlgOperationProp::OnBnClickedButtonIncEdit1_1min()
{
	bool bSelectedAfter = m_PropEditUiInternal.GetUiData()->bSelectedAfter;
	int iListSelected = m_PropEditUiInternal.GetUiData()->iListSelected;
	if (iListSelected >= 0)
	{
		vector<Operation> sOperation;
		if (bSelectedAfter)
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationA;
		}
		else
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationB;
		}

		if (sOperation[iListSelected].iOperation == 0 ||
			sOperation[iListSelected].iOperation == 1 ||
			sOperation[iListSelected].iOperation == 3 ||
			sOperation[iListSelected].iOperation == 4 ||
			sOperation[iListSelected].iOperation == 5)
		{
			tstring strJikokuOld = sOperation[iListSelected].strEditData1;
			if (!strJikokuOld.empty())
			{
				CdDedJikoku aJikoku(strJikokuOld);
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(+60);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData1 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
			else if (sOperation[iListSelected].iOperation == 0)
			{
				CdDedJikoku aJikoku;
				tstring strOperationChakuJikoku = sOperation[iListSelected].strEditData2;
				if (!strOperationChakuJikoku.empty())
				{
					aJikoku.decode(strOperationChakuJikoku);
				}
				if (aJikoku.isNull())
				{
					if (m_iHatsuEkiOrder == -1 ||
						!bSelectedAfter && m_iChakuEkiOrder >= 0)
					{
						aJikoku = m_ChakuJikoku;
					}
					else
					{
						aJikoku = m_HatsuJikoku;
					}
				}
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(+60);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData1 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
			else
			{
				CdDedJikoku aJikoku;
				if (m_iHatsuEkiOrder == -1 ||
					!bSelectedAfter && m_iChakuEkiOrder >= 0)
				{
					aJikoku = m_ChakuJikoku;
				}
				else
				{
					aJikoku = m_HatsuJikoku;
				}
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(+60);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData1 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
		}
		else if (sOperation[iListSelected].iOperation == 2)
		{
			int iOld = _ttoi(sOperation[iListSelected].strEditData1.c_str());
			if (iOld < 10)
			{
				sOperation[iListSelected].strEditData1 = to_tstring(iOld + 1);

				if (bSelectedAfter)
				{
					m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
				}
				else
				{
					m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
				}
				m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
			}
		}
	}
	m_PropEditUiInternal.OnUiDataChanged();
}

void CDlgOperationProp::OnBnClickedButtonDecEdit1_5min()
{
	bool bSelectedAfter = m_PropEditUiInternal.GetUiData()->bSelectedAfter;
	int iListSelected = m_PropEditUiInternal.GetUiData()->iListSelected;
	if (iListSelected >= 0)
	{
		vector<Operation> sOperation;
		if (bSelectedAfter)
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationA;
		}
		else
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationB;
		}

		if (sOperation[iListSelected].iOperation == 0 ||
			sOperation[iListSelected].iOperation == 1 ||
			sOperation[iListSelected].iOperation == 3 ||
			sOperation[iListSelected].iOperation == 4 ||
			sOperation[iListSelected].iOperation == 5)
		{
			tstring strJikokuOld = sOperation[iListSelected].strEditData1;
			if (!strJikokuOld.empty())
			{
				CdDedJikoku aJikoku(strJikokuOld);
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(-300);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData1 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
			else if (sOperation[iListSelected].iOperation == 0)
			{
				CdDedJikoku aJikoku;
				tstring strOperationChakuJikoku = sOperation[iListSelected].strEditData2;
				if (!strOperationChakuJikoku.empty())
				{
					aJikoku.decode(strOperationChakuJikoku);
				}
				if (aJikoku.isNull())
				{
					if (m_iHatsuEkiOrder == -1 ||
						!bSelectedAfter && m_iChakuEkiOrder >= 0)
					{
						aJikoku = m_ChakuJikoku;
					}
					else
					{
						aJikoku = m_HatsuJikoku;
					}
				}
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(-300);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData1 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
			else
			{
				CdDedJikoku aJikoku;
				if (m_iHatsuEkiOrder == -1 ||
					!bSelectedAfter && m_iChakuEkiOrder >= 0)
				{
					aJikoku = m_ChakuJikoku;
				}
				else
				{
					aJikoku = m_HatsuJikoku;
				}
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(-300);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData1 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
		}
		else if (sOperation[iListSelected].iOperation == 2)
		{
			int iOld = _ttoi(sOperation[iListSelected].strEditData1.c_str());
			if (iOld > 1)
			{
				sOperation[iListSelected].strEditData1 = to_tstring(iOld - 1);

				if (bSelectedAfter)
				{
					m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
				}
				else
				{
					m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
				}
				m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
			}
		}
	}
	m_PropEditUiInternal.OnUiDataChanged();
}

void CDlgOperationProp::OnBnClickedButtonIncEdit1_5min()
{
	bool bSelectedAfter = m_PropEditUiInternal.GetUiData()->bSelectedAfter;
	int iListSelected = m_PropEditUiInternal.GetUiData()->iListSelected;
	if (iListSelected >= 0)
	{
		vector<Operation> sOperation;
		if (bSelectedAfter)
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationA;
		}
		else
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationB;
		}

		if (sOperation[iListSelected].iOperation == 0 ||
			sOperation[iListSelected].iOperation == 1 ||
			sOperation[iListSelected].iOperation == 3 ||
			sOperation[iListSelected].iOperation == 4 ||
			sOperation[iListSelected].iOperation == 5)
		{
			tstring strJikokuOld = sOperation[iListSelected].strEditData1;
			if (!strJikokuOld.empty())
			{
				CdDedJikoku aJikoku(strJikokuOld);
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(+300);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData1 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
			else if (sOperation[iListSelected].iOperation == 0)
			{
				CdDedJikoku aJikoku;
				tstring strOperationChakuJikoku = sOperation[iListSelected].strEditData2;
				if (!strOperationChakuJikoku.empty())
				{
					aJikoku.decode(strOperationChakuJikoku);
				}
				if (aJikoku.isNull())
				{
					if (m_iHatsuEkiOrder == -1 ||
						!bSelectedAfter && m_iChakuEkiOrder >= 0)
					{
						aJikoku = m_ChakuJikoku;
					}
					else
					{
						aJikoku = m_HatsuJikoku;
					}
				}
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(+300);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData1 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
			else
			{
				CdDedJikoku aJikoku;
				if (m_iHatsuEkiOrder == -1 ||
					!bSelectedAfter && m_iChakuEkiOrder >= 0)
				{
					aJikoku = m_ChakuJikoku;
				}
				else
				{
					aJikoku = m_HatsuJikoku;
				}
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(+300);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData1 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
		}
		else if (sOperation[iListSelected].iOperation == 2)
		{
			int iOld = _ttoi(sOperation[iListSelected].strEditData1.c_str());
			if (iOld < 10)
			{
				sOperation[iListSelected].strEditData1 = to_tstring(iOld + 1);

				if (bSelectedAfter)
				{
					m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
				}
				else
				{
					m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
				}
				m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
			}
		}
	}
	m_PropEditUiInternal.OnUiDataChanged();
}

void CDlgOperationProp::OnBnClickedButtonDecEdit1anysec1()
{
	bool bSelectedAfter = m_PropEditUiInternal.GetUiData()->bSelectedAfter;
	int iListSelected = m_PropEditUiInternal.GetUiData()->iListSelected;
	if (iListSelected >= 0)
	{
		vector<Operation> sOperation;
		if (bSelectedAfter)
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationA;
		}
		else
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationB;
		}

		if (sOperation[iListSelected].iOperation == 0 ||
			sOperation[iListSelected].iOperation == 1 ||
			sOperation[iListSelected].iOperation == 3 ||
			sOperation[iListSelected].iOperation == 4 ||
			sOperation[iListSelected].iOperation == 5)
		{
			tstring strJikokuOld = sOperation[iListSelected].strEditData1;
			if (!strJikokuOld.empty())
			{
				CdDedJikoku aJikoku(strJikokuOld);
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(-m_AnySec1);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData1 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
			else if (sOperation[iListSelected].iOperation == 0)
			{
				CdDedJikoku aJikoku;
				tstring strOperationChakuJikoku = sOperation[iListSelected].strEditData2;
				if (!strOperationChakuJikoku.empty())
				{
					aJikoku.decode(strOperationChakuJikoku);
				}
				if (aJikoku.isNull())
				{
					if (m_iHatsuEkiOrder == -1 ||
						!bSelectedAfter && m_iChakuEkiOrder >= 0)
					{
						aJikoku = m_ChakuJikoku;
					}
					else
					{
						aJikoku = m_HatsuJikoku;
					}
				}
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(-m_AnySec1);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData1 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
			else
			{
				CdDedJikoku aJikoku;
				if (m_iHatsuEkiOrder == -1 ||
					!bSelectedAfter && m_iChakuEkiOrder >= 0)
				{
					aJikoku = m_ChakuJikoku;
				}
				else
				{
					aJikoku = m_HatsuJikoku;
				}
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(-m_AnySec1);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData1 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
		}
		else if (sOperation[iListSelected].iOperation == 2)
		{
			int iOld = _ttoi(sOperation[iListSelected].strEditData1.c_str());
			if (iOld > 1)
			{
				sOperation[iListSelected].strEditData1 = to_tstring(iOld - 1);

				if (bSelectedAfter)
				{
					m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
				}
				else
				{
					m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
				}
				m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
			}
		}
	}
	m_PropEditUiInternal.OnUiDataChanged();
}

void CDlgOperationProp::OnBnClickedButtonIncEdit1anysec1()
{
	bool bSelectedAfter = m_PropEditUiInternal.GetUiData()->bSelectedAfter;
	int iListSelected = m_PropEditUiInternal.GetUiData()->iListSelected;
	if (iListSelected >= 0)
	{
		vector<Operation> sOperation;
		if (bSelectedAfter)
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationA;
		}
		else
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationB;
		}

		if (sOperation[iListSelected].iOperation == 0 ||
			sOperation[iListSelected].iOperation == 1 ||
			sOperation[iListSelected].iOperation == 3 ||
			sOperation[iListSelected].iOperation == 4 ||
			sOperation[iListSelected].iOperation == 5)
		{
			tstring strJikokuOld = sOperation[iListSelected].strEditData1;
			if (!strJikokuOld.empty())
			{
				CdDedJikoku aJikoku(strJikokuOld);
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(+m_AnySec1);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData1 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
			else if (sOperation[iListSelected].iOperation == 0)
			{
				CdDedJikoku aJikoku;
				tstring strOperationChakuJikoku = sOperation[iListSelected].strEditData2;
				if (!strOperationChakuJikoku.empty())
				{
					aJikoku.decode(strOperationChakuJikoku);
				}
				if (aJikoku.isNull())
				{
					if (m_iHatsuEkiOrder == -1 ||
						!bSelectedAfter && m_iChakuEkiOrder >= 0)
					{
						aJikoku = m_ChakuJikoku;
					}
					else
					{
						aJikoku = m_HatsuJikoku;
					}
				}
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(+m_AnySec1);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData1 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
			else
			{
				CdDedJikoku aJikoku;
				if (m_iHatsuEkiOrder == -1 ||
					!bSelectedAfter && m_iChakuEkiOrder >= 0)
				{
					aJikoku = m_ChakuJikoku;
				}
				else
				{
					aJikoku = m_HatsuJikoku;
				}
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(+m_AnySec1);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData1 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
		}
		else if (sOperation[iListSelected].iOperation == 2)
		{
			int iOld = _ttoi(sOperation[iListSelected].strEditData1.c_str());
			if (iOld < 10)
			{
				sOperation[iListSelected].strEditData1 = to_tstring(iOld + 1);

				if (bSelectedAfter)
				{
					m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
				}
				else
				{
					m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
				}
				m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
			}
		}
	}
	m_PropEditUiInternal.OnUiDataChanged();
}

void CDlgOperationProp::OnBnClickedButtonDecEdit1anysec2()
{
	bool bSelectedAfter = m_PropEditUiInternal.GetUiData()->bSelectedAfter;
	int iListSelected = m_PropEditUiInternal.GetUiData()->iListSelected;
	if (iListSelected >= 0)
	{
		vector<Operation> sOperation;
		if (bSelectedAfter)
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationA;
		}
		else
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationB;
		}

		if (sOperation[iListSelected].iOperation == 0 ||
			sOperation[iListSelected].iOperation == 1 ||
			sOperation[iListSelected].iOperation == 3 ||
			sOperation[iListSelected].iOperation == 4 ||
			sOperation[iListSelected].iOperation == 5)
		{
			tstring strJikokuOld = sOperation[iListSelected].strEditData1;
			if (!strJikokuOld.empty())
			{
				CdDedJikoku aJikoku(strJikokuOld);
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(-m_AnySec2);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData1 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
			else if (sOperation[iListSelected].iOperation == 0)
			{
				CdDedJikoku aJikoku;
				tstring strOperationChakuJikoku = sOperation[iListSelected].strEditData2;
				if (!strOperationChakuJikoku.empty())
				{
					aJikoku.decode(strOperationChakuJikoku);
				}
				if (aJikoku.isNull())
				{
					if (m_iHatsuEkiOrder == -1 ||
						!bSelectedAfter && m_iChakuEkiOrder >= 0)
					{
						aJikoku = m_ChakuJikoku;
					}
					else
					{
						aJikoku = m_HatsuJikoku;
					}
				}
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(-m_AnySec2);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData1 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
			else
			{
				CdDedJikoku aJikoku;
				if (m_iHatsuEkiOrder == -1 ||
					!bSelectedAfter && m_iChakuEkiOrder >= 0)
				{
					aJikoku = m_ChakuJikoku;
				}
				else
				{
					aJikoku = m_HatsuJikoku;
				}
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(-m_AnySec2);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData1 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
		}
		else if (sOperation[iListSelected].iOperation == 2)
		{
			int iOld = _ttoi(sOperation[iListSelected].strEditData1.c_str());
			if (iOld > 1)
			{
				sOperation[iListSelected].strEditData1 = to_tstring(iOld - 1);

				if (bSelectedAfter)
				{
					m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
				}
				else
				{
					m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
				}
				m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
			}
		}
	}
	m_PropEditUiInternal.OnUiDataChanged();
}

void CDlgOperationProp::OnBnClickedButtonIncEdit1anysec2()
{
	bool bSelectedAfter = m_PropEditUiInternal.GetUiData()->bSelectedAfter;
	int iListSelected = m_PropEditUiInternal.GetUiData()->iListSelected;
	if (iListSelected >= 0)
	{
		vector<Operation> sOperation;
		if (bSelectedAfter)
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationA;
		}
		else
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationB;
		}

		if (sOperation[iListSelected].iOperation == 0 ||
			sOperation[iListSelected].iOperation == 1 ||
			sOperation[iListSelected].iOperation == 3 ||
			sOperation[iListSelected].iOperation == 4 ||
			sOperation[iListSelected].iOperation == 5)
		{
			tstring strJikokuOld = sOperation[iListSelected].strEditData1;
			if (!strJikokuOld.empty())
			{
				CdDedJikoku aJikoku(strJikokuOld);
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(+m_AnySec2);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData1 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
			else if (sOperation[iListSelected].iOperation == 0)
			{
				CdDedJikoku aJikoku;
				tstring strOperationChakuJikoku = sOperation[iListSelected].strEditData2;
				if (!strOperationChakuJikoku.empty())
				{
					aJikoku.decode(strOperationChakuJikoku);
				}
				if (aJikoku.isNull())
				{
					if (m_iHatsuEkiOrder == -1 ||
						!bSelectedAfter && m_iChakuEkiOrder >= 0)
					{
						aJikoku = m_ChakuJikoku;
					}
					else
					{
						aJikoku = m_HatsuJikoku;
					}
				}
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(+m_AnySec2);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData1 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
			else
			{
				CdDedJikoku aJikoku;
				if (m_iHatsuEkiOrder == -1 ||
					!bSelectedAfter && m_iChakuEkiOrder >= 0)
				{
					aJikoku = m_ChakuJikoku;
				}
				else
				{
					aJikoku = m_HatsuJikoku;
				}
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(+m_AnySec2);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData1 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
		}
		else if (sOperation[iListSelected].iOperation == 2)
		{
			int iOld = _ttoi(sOperation[iListSelected].strEditData1.c_str());
			if (iOld < 10)
			{
				sOperation[iListSelected].strEditData1 = to_tstring(iOld + 1);

				if (bSelectedAfter)
				{
					m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
				}
				else
				{
					m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
				}
				m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
			}
		}
	}
	m_PropEditUiInternal.OnUiDataChanged();
}

void CDlgOperationProp::OnBnClickedButtonDecEdit2_1min()
{
	bool bSelectedAfter = m_PropEditUiInternal.GetUiData()->bSelectedAfter;
	int iListSelected = m_PropEditUiInternal.GetUiData()->iListSelected;
	if (iListSelected >= 0)
	{
		vector<Operation> sOperation;
		if (bSelectedAfter)
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationA;
		}
		else
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationB;
		}

		if (sOperation[iListSelected].iOperation == 0 ||
			sOperation[iListSelected].iOperation == 2 ||
			sOperation[iListSelected].iOperation == 4)
		{
			tstring strJikokuOld = sOperation[iListSelected].strEditData2;
			if (!strJikokuOld.empty())
			{
				CdDedJikoku aJikoku(strJikokuOld);
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(-60);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData2 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
			else if (sOperation[iListSelected].iOperation == 0)
			{
				CdDedJikoku aJikoku;
				tstring strOperationHatsuJikoku = sOperation[iListSelected].strEditData1;
				if (!strOperationHatsuJikoku.empty())
				{
					aJikoku.decode(strOperationHatsuJikoku);
				}
				if (aJikoku.isNull())
				{
					if (m_iHatsuEkiOrder == -1 ||
						!bSelectedAfter && m_iChakuEkiOrder >= 0)
					{
						aJikoku = m_ChakuJikoku;
					}
					else
					{
						aJikoku = m_HatsuJikoku;
					}
				}
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(-60);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData2 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
			else
			{
				CdDedJikoku aJikoku;
				if (m_iHatsuEkiOrder == -1 ||
					!bSelectedAfter && m_iChakuEkiOrder >= 0)
				{
					aJikoku = m_ChakuJikoku;
				}
				else
				{
					aJikoku = m_HatsuJikoku;
				}
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(-60);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData2 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
		}
	}
	m_PropEditUiInternal.OnUiDataChanged();
}

void CDlgOperationProp::OnBnClickedButtonIncEdit2_1min()
{
	bool bSelectedAfter = m_PropEditUiInternal.GetUiData()->bSelectedAfter;
	int iListSelected = m_PropEditUiInternal.GetUiData()->iListSelected;
	if (iListSelected >= 0)
	{
		vector<Operation> sOperation;
		if (bSelectedAfter)
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationA;
		}
		else
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationB;
		}

		if (sOperation[iListSelected].iOperation == 0 ||
			sOperation[iListSelected].iOperation == 2 ||
			sOperation[iListSelected].iOperation == 4)
		{
			tstring strJikokuOld = sOperation[iListSelected].strEditData2;
			if (!strJikokuOld.empty())
			{
				CdDedJikoku aJikoku(strJikokuOld);
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(+60);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData2 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
			else if (sOperation[iListSelected].iOperation == 0)
			{
				CdDedJikoku aJikoku;
				tstring strOperationHatsuJikoku = sOperation[iListSelected].strEditData1;
				if (!strOperationHatsuJikoku.empty())
				{
					aJikoku.decode(strOperationHatsuJikoku);
				}
				if (aJikoku.isNull())
				{
					if (m_iHatsuEkiOrder == -1 ||
						!bSelectedAfter && m_iChakuEkiOrder >= 0)
					{
						aJikoku = m_ChakuJikoku;
					}
					else
					{
						aJikoku = m_HatsuJikoku;
					}
				}
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(+60);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData2 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
			else
			{
				CdDedJikoku aJikoku;
				if (m_iHatsuEkiOrder == -1 ||
					!bSelectedAfter && m_iChakuEkiOrder >= 0)
				{
					aJikoku = m_ChakuJikoku;
				}
				else
				{
					aJikoku = m_HatsuJikoku;
				}
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(+60);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData2 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
		}
	}
	m_PropEditUiInternal.OnUiDataChanged();
}

void CDlgOperationProp::OnBnClickedButtonDecEdit2_5min()
{
	bool bSelectedAfter = m_PropEditUiInternal.GetUiData()->bSelectedAfter;
	int iListSelected = m_PropEditUiInternal.GetUiData()->iListSelected;
	if (iListSelected >= 0)
	{
		vector<Operation> sOperation;
		if (bSelectedAfter)
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationA;
		}
		else
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationB;
		}

		if (sOperation[iListSelected].iOperation == 0 ||
			sOperation[iListSelected].iOperation == 2 ||
			sOperation[iListSelected].iOperation == 4)
		{
			tstring strJikokuOld = sOperation[iListSelected].strEditData2;
			if (!strJikokuOld.empty())
			{
				CdDedJikoku aJikoku(strJikokuOld);
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(-300);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData2 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
			else if (sOperation[iListSelected].iOperation == 0)
			{
				CdDedJikoku aJikoku;
				tstring strOperationHatsuJikoku = sOperation[iListSelected].strEditData1;
				if (!strOperationHatsuJikoku.empty())
				{
					aJikoku.decode(strOperationHatsuJikoku);
				}
				if (aJikoku.isNull())
				{
					if (m_iHatsuEkiOrder == -1 ||
						!bSelectedAfter && m_iChakuEkiOrder >= 0)
					{
						aJikoku = m_ChakuJikoku;
					}
					else
					{
						aJikoku = m_HatsuJikoku;
					}
				}
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(-300);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData2 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
			else
			{
				CdDedJikoku aJikoku;
				if (m_iHatsuEkiOrder == -1 ||
					!bSelectedAfter && m_iChakuEkiOrder >= 0)
				{
					aJikoku = m_ChakuJikoku;
				}
				else
				{
					aJikoku = m_HatsuJikoku;
				}
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(-300);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData2 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
		}
	}
	m_PropEditUiInternal.OnUiDataChanged();
}

void CDlgOperationProp::OnBnClickedButtonIncEdit2_5min()
{
	bool bSelectedAfter = m_PropEditUiInternal.GetUiData()->bSelectedAfter;
	int iListSelected = m_PropEditUiInternal.GetUiData()->iListSelected;
	if (iListSelected >= 0)
	{
		vector<Operation> sOperation;
		if (bSelectedAfter)
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationA;
		}
		else
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationB;
		}

		if (sOperation[iListSelected].iOperation == 0 ||
			sOperation[iListSelected].iOperation == 2 ||
			sOperation[iListSelected].iOperation == 4)
		{
			tstring strJikokuOld = sOperation[iListSelected].strEditData2;
			if (!strJikokuOld.empty())
			{
				CdDedJikoku aJikoku(strJikokuOld);
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(+300);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData2 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
			else if (sOperation[iListSelected].iOperation == 0)
			{
				CdDedJikoku aJikoku;
				tstring strOperationHatsuJikoku = sOperation[iListSelected].strEditData1;
				if (!strOperationHatsuJikoku.empty())
				{
					aJikoku.decode(strOperationHatsuJikoku);
				}
				if (aJikoku.isNull())
				{
					if (m_iHatsuEkiOrder == -1 ||
						!bSelectedAfter && m_iChakuEkiOrder >= 0)
					{
						aJikoku = m_ChakuJikoku;
					}
					else
					{
						aJikoku = m_HatsuJikoku;
					}
				}
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(+300);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData2 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
			else
			{
				CdDedJikoku aJikoku;
				if (m_iHatsuEkiOrder == -1 ||
					!bSelectedAfter && m_iChakuEkiOrder >= 0)
				{
					aJikoku = m_ChakuJikoku;
				}
				else
				{
					aJikoku = m_HatsuJikoku;
				}
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(+300);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData2 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
		}
	}
	m_PropEditUiInternal.OnUiDataChanged();
}

void CDlgOperationProp::OnBnClickedButtonDecEdit2anysec1()
{
	bool bSelectedAfter = m_PropEditUiInternal.GetUiData()->bSelectedAfter;
	int iListSelected = m_PropEditUiInternal.GetUiData()->iListSelected;
	if (iListSelected >= 0)
	{
		vector<Operation> sOperation;
		if (bSelectedAfter)
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationA;
		}
		else
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationB;
		}

		if (sOperation[iListSelected].iOperation == 0 ||
			sOperation[iListSelected].iOperation == 2 ||
			sOperation[iListSelected].iOperation == 4)
		{
			tstring strJikokuOld = sOperation[iListSelected].strEditData2;
			if (!strJikokuOld.empty())
			{
				CdDedJikoku aJikoku(strJikokuOld);
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(-m_AnySec1);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData2 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
			else if (sOperation[iListSelected].iOperation == 0)
			{
				CdDedJikoku aJikoku;
				tstring strOperationHatsuJikoku = sOperation[iListSelected].strEditData1;
				if (!strOperationHatsuJikoku.empty())
				{
					aJikoku.decode(strOperationHatsuJikoku);
				}
				if (aJikoku.isNull())
				{
					if (m_iHatsuEkiOrder == -1 ||
						!bSelectedAfter && m_iChakuEkiOrder >= 0)
					{
						aJikoku = m_ChakuJikoku;
					}
					else
					{
						aJikoku = m_HatsuJikoku;
					}
				}
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(-m_AnySec1);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData2 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
			else
			{
				CdDedJikoku aJikoku;
				if (m_iHatsuEkiOrder == -1 ||
					!bSelectedAfter && m_iChakuEkiOrder >= 0)
				{
					aJikoku = m_ChakuJikoku;
				}
				else
				{
					aJikoku = m_HatsuJikoku;
				}
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(-m_AnySec1);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData2 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
		}
	}
	m_PropEditUiInternal.OnUiDataChanged();
}

void CDlgOperationProp::OnBnClickedButtonIncEdit2anysec1()
{
	bool bSelectedAfter = m_PropEditUiInternal.GetUiData()->bSelectedAfter;
	int iListSelected = m_PropEditUiInternal.GetUiData()->iListSelected;
	if (iListSelected >= 0)
	{
		vector<Operation> sOperation;
		if (bSelectedAfter)
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationA;
		}
		else
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationB;
		}

		if (sOperation[iListSelected].iOperation == 0 ||
			sOperation[iListSelected].iOperation == 2 ||
			sOperation[iListSelected].iOperation == 4)
		{
			tstring strJikokuOld = sOperation[iListSelected].strEditData2;
			if (!strJikokuOld.empty())
			{
				CdDedJikoku aJikoku(strJikokuOld);
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(+m_AnySec1);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData2 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
			else if (sOperation[iListSelected].iOperation == 0)
			{
				CdDedJikoku aJikoku;
				tstring strOperationHatsuJikoku = sOperation[iListSelected].strEditData1;
				if (!strOperationHatsuJikoku.empty())
				{
					aJikoku.decode(strOperationHatsuJikoku);
				}
				if (aJikoku.isNull())
				{
					if (m_iHatsuEkiOrder == -1 ||
						!bSelectedAfter && m_iChakuEkiOrder >= 0)
					{
						aJikoku = m_ChakuJikoku;
					}
					else
					{
						aJikoku = m_HatsuJikoku;
					}
				}
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(+m_AnySec1);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData2 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
			else
			{
				CdDedJikoku aJikoku;
				if (m_iHatsuEkiOrder == -1 ||
					!bSelectedAfter && m_iChakuEkiOrder >= 0)
				{
					aJikoku = m_ChakuJikoku;
				}
				else
				{
					aJikoku = m_HatsuJikoku;
				}
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(+m_AnySec1);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData2 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
		}
	}
	m_PropEditUiInternal.OnUiDataChanged();
}

void CDlgOperationProp::OnBnClickedButtonDecEdit2anysec2()
{
	bool bSelectedAfter = m_PropEditUiInternal.GetUiData()->bSelectedAfter;
	int iListSelected = m_PropEditUiInternal.GetUiData()->iListSelected;
	if (iListSelected >= 0)
	{
		vector<Operation> sOperation;
		if (bSelectedAfter)
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationA;
		}
		else
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationB;
		}

		if (sOperation[iListSelected].iOperation == 0 ||
			sOperation[iListSelected].iOperation == 2 ||
			sOperation[iListSelected].iOperation == 4)
		{
			tstring strJikokuOld = sOperation[iListSelected].strEditData2;
			if (!strJikokuOld.empty())
			{
				CdDedJikoku aJikoku(strJikokuOld);
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(-m_AnySec2);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData2 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
			else if (sOperation[iListSelected].iOperation == 0)
			{
				CdDedJikoku aJikoku;
				tstring strOperationHatsuJikoku = sOperation[iListSelected].strEditData1;
				if (!strOperationHatsuJikoku.empty())
				{
					aJikoku.decode(strOperationHatsuJikoku);
				}
				if (aJikoku.isNull())
				{
					if (m_iHatsuEkiOrder == -1 ||
						!bSelectedAfter && m_iChakuEkiOrder >= 0)
					{
						aJikoku = m_ChakuJikoku;
					}
					else
					{
						aJikoku = m_HatsuJikoku;
					}
				}
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(-m_AnySec2);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData2 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
			else
			{
				CdDedJikoku aJikoku;
				if (m_iHatsuEkiOrder == -1 ||
					!bSelectedAfter && m_iChakuEkiOrder >= 0)
				{
					aJikoku = m_ChakuJikoku;
				}
				else
				{
					aJikoku = m_HatsuJikoku;
				}
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(-m_AnySec2);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData2 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
		}
	}
	m_PropEditUiInternal.OnUiDataChanged();
}

void CDlgOperationProp::OnBnClickedButtonIncEdit2anysec2()
{
	bool bSelectedAfter = m_PropEditUiInternal.GetUiData()->bSelectedAfter;
	int iListSelected = m_PropEditUiInternal.GetUiData()->iListSelected;
	if (iListSelected >= 0)
	{
		vector<Operation> sOperation;
		if (bSelectedAfter)
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationA;
		}
		else
		{
			sOperation = m_PropEditUiInternal.GetUiData()->sOperationB;
		}

		if (sOperation[iListSelected].iOperation == 0 ||
			sOperation[iListSelected].iOperation == 2 ||
			sOperation[iListSelected].iOperation == 4)
		{
			tstring strJikokuOld = sOperation[iListSelected].strEditData2;
			if (!strJikokuOld.empty())
			{
				CdDedJikoku aJikoku(strJikokuOld);
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(+m_AnySec2);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData2 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
			else if (sOperation[iListSelected].iOperation == 0)
			{
				CdDedJikoku aJikoku;
				tstring strOperationHatsuJikoku = sOperation[iListSelected].strEditData1;
				if (!strOperationHatsuJikoku.empty())
				{
					aJikoku.decode(strOperationHatsuJikoku);
				}
				if (aJikoku.isNull())
				{
					if (m_iHatsuEkiOrder == -1 ||
						!bSelectedAfter && m_iChakuEkiOrder >= 0)
					{
						aJikoku = m_ChakuJikoku;
					}
					else
					{
						aJikoku = m_HatsuJikoku;
					}
				}
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(+m_AnySec2);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData2 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
			else
			{
				CdDedJikoku aJikoku;
				if (m_iHatsuEkiOrder == -1 ||
					!bSelectedAfter && m_iChakuEkiOrder >= 0)
				{
					aJikoku = m_ChakuJikoku;
				}
				else
				{
					aJikoku = m_HatsuJikoku;
				}
				if (!aJikoku.isNull())
				{
					aJikoku.addSeconds(+m_AnySec2);
					CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
					sOperation[iListSelected].strEditData2 = aJikokuConv.encode(aJikoku);

					if (bSelectedAfter)
					{
						m_PropEditUiInternal.GetUiData()->sOperationA = sOperation;
					}
					else
					{
						m_PropEditUiInternal.GetUiData()->sOperationB = sOperation;
					}
					m_PropEditUiInternal.GetUiData()->iUiOperation = 0;
				}
			}
		}
	}
	m_PropEditUiInternal.OnUiDataChanged();
}


} //namespace ViewJikokuhyou
