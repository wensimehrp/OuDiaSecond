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
// CDlgOperationTableExport.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "MfcUtil¥MfcUtil.h"
#include "str¥CsvDocument¥CdCsvDocument.h"
#include "str¥CsvDocument¥CconvCsvDocument.h"
#include "str¥strtoint.h"
#include "str¥vectorToFile.h"

#include "..¥diagramedit.h"
#include "..¥resource.h"
#include "CDlgOperationTableCsvExport.h"
#include "..¥entDed¥CdDedRessyaProperty.h"
#include <algorithm>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace ViewAllOperationTable {
using namespace std ;

/////////////////////////////////////////////////////////////////////////////
// CDlgOperationTableCsvExport ダイアログ


CDlgOperationTableCsvExport::CDlgOperationTableCsvExport(
	const CentDedRosen* pCentDedRosen,
	const CentDedDia* pCentDedDia,
	const CdDedDispProp aCdDedDispProp,
	tstring  strOperationNumber,
	int iStationIndex,
	bool bDisplaySecondEkiJikoku,
	bool bDisplayColonEkiJikoku,
	bool bDisplayParentSyubetsu,
	bool bDisplayNoboriLeftToRight,
	bool bCompareBottom,
	CWndDcdGridAllOperationTable::EOperationSort eOperationSort,
	bool bDisplayExtensionOperationTable,
	bool bDisplayTrackName,
	bool bDisplayTsuukaEkiJikoku,
	CWnd* pParent )
	: CDialog(CDlgOperationTableCsvExport::IDD, pParent)
 	, m_pCentDedRosen( pCentDedRosen )
	, m_pCentDedDia(pCentDedDia)
	, m_aCdDedDispProp(aCdDedDispProp)
	, m_strOperationNumber(strOperationNumber)
	, m_bDisplaySecondEkiJikoku(bDisplaySecondEkiJikoku)
	, m_bDisplayColonEkiJikoku(bDisplayColonEkiJikoku)
	, m_bDisplayParentSyubetsu(bDisplayParentSyubetsu)
	//, m_bDisplayNoboriLeftToRight(bDisplayNoboriLeftToRight)
	, m_bCompareBottom(bCompareBottom)
	, m_iRadioOperationTarget(0)
	, m_strOperationNumberInput(strOperationNumber.c_str())
	, m_iTypeOfSearch(0)
	, m_iStationIndex(iStationIndex)
	, m_iInOrOut(0)
	, m_iOperationOrder((int)eOperationSort)
	, m_iIncludeOuterTerminal(1)
{
	//{{AFX_DATA_INIT(CDlgOuJikokuhyouCsvExport)
	//}}AFX_DATA_INIT
	m_iNoboriLeftToRight = bDisplayNoboriLeftToRight ? 1 : 0;
	m_iExtensionOperationTable = bDisplayExtensionOperationTable ? 1 : 0;
	m_iTrackName = bDisplayTrackName ? 1 : 0;
	m_iTsuukaEkiJikoku = bDisplayTsuukaEkiJikoku ? 1 : 0;
	if (eOperationSort == CWndDcdGridAllOperationTable::EOperationSort_InEki ||
		eOperationSort == CWndDcdGridAllOperationTable::EOperationSort_InJikoku)
	{
		m_iInOrOut = 1;
	}
}

void CDlgOperationTableCsvExport::splitOperationNumber(
	const tstring strOperationNumberIn,
	vector<int>& iOperationNumber,
	vector<tstring>& strOperationNumberOut) const
{
	iOperationNumber.clear();
	strOperationNumberOut.clear();
	bool bIsDigit = false;
	bool bIsNotDigit = false;
	tstring strOperationNumberTemp = strOperationNumberIn;
	while (!strOperationNumberTemp.empty())
	{
		int idx = 0;
		if (_istdigit(strOperationNumberTemp[idx]) != 0)
		{
			if ((int)strOperationNumberTemp.size() == 1)
			{
				iOperationNumber.push_back(
					_ttoi(strOperationNumberTemp.c_str()));
				strOperationNumberOut.push_back(tstring());
				break;
			}
			//数字の場合
			bIsDigit = true;
		}
		else
		{
			if ((int)strOperationNumberTemp.size() == 1)
			{
				iOperationNumber.push_back(INT_MIN);
				strOperationNumberOut.push_back(strOperationNumberTemp);
				break;
			}
			//それ以外の場合
			bIsDigit = false;
		}
		idx++;
		for (; idx < (int)strOperationNumberTemp.size(); idx++)
		{
			if (idx == (int)strOperationNumberTemp.size() - 1)
			{
				if (bIsDigit && _istdigit(strOperationNumberTemp[idx]) != 0)
				{
					iOperationNumber.push_back(
						_ttoi(strOperationNumberTemp.c_str()));
					strOperationNumberOut.push_back(tstring());

					strOperationNumberTemp.clear();
					break;
				}
				else if (!bIsDigit && _istdigit(strOperationNumberTemp[idx]) == 0)
				{
					iOperationNumber.push_back(INT_MIN);
					strOperationNumberOut.push_back(strOperationNumberTemp);

					strOperationNumberTemp.clear();
					break;
				}

			}
			if (_istdigit(strOperationNumberTemp[idx]) != 0)
			{
				//idx位置が数字で、先頭が文字の場合
				if (!bIsDigit)
				{
					iOperationNumber.push_back(INT_MIN);
					strOperationNumberOut.push_back(strOperationNumberTemp.substr(0, idx));

					strOperationNumberTemp = strOperationNumberTemp.substr(idx);
					break;
				}
			}
			else
			{
				//idx位置が文字で、先頭が数字の場合
				if (bIsDigit)
				{
					iOperationNumber.push_back(
						_ttoi(strOperationNumberTemp.substr(0, idx).c_str()));
					strOperationNumberOut.push_back(tstring());

					strOperationNumberTemp = strOperationNumberTemp.substr(idx);
					break;
				}
			}
		}
	}
}

bool CDlgOperationTableCsvExport::SortOperationNumber(
	const tstring strOperationNumber1,
	const tstring strOperationNumber2)
{
	if (strOperationNumber2.empty())
	{
		return true;
	}
	if (strOperationNumber1.empty())
	{
		return false;
	}


	vector<int> iOperationNumber1;
	vector<int> iOperationNumber2;
	vector<tstring> strOperationNumber1Part;
	vector<tstring> strOperationNumber2Part;
	splitOperationNumber(strOperationNumber1, iOperationNumber1, strOperationNumber1Part);
	splitOperationNumber(strOperationNumber2, iOperationNumber2, strOperationNumber2Part);

	if (m_bCompareBottom)
	{
		int iSize1 = iOperationNumber1.size();
		int iSize2 = iOperationNumber2.size();
		int iMin = min(iSize1, iSize2);
		for (int idx = 1; idx <= iMin; idx++)
		{
			// --------------------------------
			//	- 数字とそれ以外では数字の方が先
			// --------------------------------
			{
				if (iOperationNumber1[iSize1 - idx] != INT_MIN && iOperationNumber2[iSize2 - idx] == INT_MIN)
				{
					return true;
				}
				else if (iOperationNumber1[iSize1 - idx] == INT_MIN && iOperationNumber2[iSize2 - idx] != INT_MIN)
				{
					return false;
				}
			}

			if (iOperationNumber1[iSize1 - idx] == INT_MIN)
			{
				//共に数字以外の場合、文字数→辞書順
				// --------------------------------
				//	- 文字部の長さが短い方が先
				// --------------------------------
				{
					if (strOperationNumber1Part[iSize1 - idx].length() < strOperationNumber2Part[iSize2 - idx].length())
					{
						return true;
					}
					else if (strOperationNumber1Part[iSize1 - idx].length() > strOperationNumber2Part[iSize2 - idx].length())
					{
						return false;
					}
				}
				// --------------------------------
				//	- 文字部が辞書順で早い方が先。
				// --------------------------------
				{
					if (strOperationNumber1Part[iSize1 - idx] < strOperationNumber2Part[iSize2 - idx])
					{
						return true;
					}
					else if (strOperationNumber1Part[iSize1 - idx] > strOperationNumber2Part[iSize2 - idx])
					{
						return false;
					}
				}
			}
			else
			{
				//共に数字の場合、数字の大小
				// --------------------------------
				//	- 数字が小さいものが先
				// --------------------------------
				{
					if (iOperationNumber1[iSize1 - idx] < iOperationNumber2[iSize2 - idx])
					{
						return true;
					}
					else if (iOperationNumber1[iSize1 - idx] > iOperationNumber2[iSize2 - idx])
					{
						return false;
					}
				}
			}

		}
	}
	else
	{
		int iMin = min(iOperationNumber1.size(), iOperationNumber2.size());
		for (int idx = 0; idx < iMin; idx++)
		{
			// --------------------------------
			//	- 数字とそれ以外では数字の方が先
			// --------------------------------
			{
				if (iOperationNumber1[idx] != INT_MIN && iOperationNumber2[idx] == INT_MIN)
				{
					return true;
				}
				else if (iOperationNumber1[idx] == INT_MIN && iOperationNumber2[idx] != INT_MIN)
				{
					return false;
				}
			}

			if (iOperationNumber1[idx] == INT_MIN)
			{
				//共に数字以外の場合、文字数→辞書順
				// --------------------------------
				//	- 文字部の長さが短い方が先
				// --------------------------------
				{
					if (strOperationNumber1Part[idx].length() < strOperationNumber2Part[idx].length())
					{
						return true;
					}
					else if (strOperationNumber1Part[idx].length() > strOperationNumber2Part[idx].length())
					{
						return false;
					}
				}
				// --------------------------------
				//	- 文字部が辞書順で早い方が先。
				// --------------------------------
				{
					if (strOperationNumber1Part[idx] < strOperationNumber2Part[idx])
					{
						return true;
					}
					else if (strOperationNumber1Part[idx] > strOperationNumber2Part[idx])
					{
						return false;
					}
				}
			}
			else
			{
				//共に数字の場合、数字の大小
				// --------------------------------
				//	- 数字が小さいものが先
				// --------------------------------
				{
					if (iOperationNumber1[idx] < iOperationNumber2[idx])
					{
						return true;
					}
					else if (iOperationNumber1[idx] > iOperationNumber2[idx])
					{
						return false;
					}
				}
			}

		}
	}
	// --------------------------------
	//	- 要素数が少ないものが先
	// --------------------------------
	{
		if (iOperationNumber1.size() < iOperationNumber2.size())
		{
			return true;
		}
		else if (iOperationNumber1.size() > iOperationNumber2.size())
		{
			return false;
		}
	}

	return false;
}

bool CDlgOperationTableCsvExport::SortOperation(
	const tstring strOperationNumber1,
	const int& iEkiIndex1,
	const int& iOuterIndex1,
	const CdDedJikoku& Jikoku1,
	const tstring strOperationNumber2,
	const int& iEkiIndex2,
	const int& iOuterIndex2,
	const CdDedJikoku& Jikoku2,
	const CdDedJikoku& KitenJikoku)
{
	if (strOperationNumber1.empty())
	{
		return false;
	}
	if (m_iOperationOrder == (int)CWndDcdGridAllOperationTable::EOperationSort_OperationNumber)
	{
		/**
			運用番号順
			運用番号をCompareBottomに基づく順で判定します
			同一の運用番号は無いので、結果は一意に決まります
		*/
		return SortOperationNumber(strOperationNumber1, strOperationNumber2);
	}
	else if (m_iOperationOrder == (int)CWndDcdGridAllOperationTable::EOperationSort_OutEki ||
		m_iOperationOrder == (int)CWndDcdGridAllOperationTable::EOperationSort_InEki)
	{
		/**
			出区駅順
			(1)出区駅順
			(2)発時刻順
			(3)運用番号順で並べます
			(1)出区駅順は、分岐駅の場合iPosition=0の駅に集約します。
				また、路線外始発の場合、純粋な出区よりも後になり、
				路線外始発同士の場合、路線外始発駅Indexが小さいものが先になります
			(2)出区駅が一致している場合、発時刻順で並べます。
				なお、路線外始発駅が一致している場合は、路線外始発駅発時刻で比較します
			(3)出区駅（路線外始発駅）、発時刻が一致している場合は、運用番号順で並べます。
		*/

		if (iEkiIndex1 < iEkiIndex2)
		{
			return true;
		}
		else if (iEkiIndex1 > iEkiIndex2)
		{
			return false;
		}

		if (iOuterIndex1 < iOuterIndex2)
		{
			return true;
		}
		else if (iOuterIndex1 > iOuterIndex2)
		{
			return false;
		}

		if (Jikoku1.compare(Jikoku2, KitenJikoku) < 0)
		{
			return true;
		}
		else if (Jikoku1.compare(Jikoku2, KitenJikoku) > 0)
		{
			return false;
		}

		return SortOperationNumber(strOperationNumber1, strOperationNumber2);
	}
	else if (m_iOperationOrder == (int)CWndDcdGridAllOperationTable::EOperationSort_OutJikoku ||
		m_iOperationOrder == (int)CWndDcdGridAllOperationTable::EOperationSort_InJikoku)
	{
		/**
			発時刻順
			(1)発時刻順
			(2)運用番号順で並べます。
			(1)発時刻順は、路線外始発の場合、路線外始発駅発時刻を用いて比較します
		*/

		if (Jikoku1.compare(Jikoku2, KitenJikoku) < 0)
		{
			return true;
		}
		else if (Jikoku1.compare(Jikoku2, KitenJikoku) > 0)
		{
			return false;
		}

		return SortOperationNumber(strOperationNumber1, strOperationNumber2);
	}
	return false;
}

bool CDlgOperationTableCsvExport::CheckSatisfyConditions(
	const tstring& strOperationNumber,
	list< OperationTableContent> ListOperationTableContent,
	//const CentDedRessya* pCentDedRessya,
	const deque<int>& iEkiIndexGroup)
{
	if (m_iRadioOperationTarget == 0)
	{
		/**
			全運用出力
		*/
		return true;
	}
	else if (m_iRadioOperationTarget == 1)
	{
		/**
			運用番号一致出力
		*/
		if (m_strOperationNumberInput.IsEmpty())
		{
			return false;
		}

		tstring strOperationNumberInput((LPCTSTR)m_strOperationNumberInput);
		if (strOperationNumber.size() < strOperationNumberInput.size())
		{
			return false;
		}
		if (m_iTypeOfSearch == 0) //部分一致
		{
			return strOperationNumber.find(strOperationNumberInput) != tstring::npos;
		}
		else if (m_iTypeOfSearch == 1)//完全一致
		{
			return strOperationNumber == strOperationNumberInput;
		}
		else if (m_iTypeOfSearch == 2)//前方一致
		{
			return strOperationNumber.compare(
				0,
				strOperationNumberInput.size(),
				strOperationNumberInput) == 0;

		}
		else if (m_iTypeOfSearch == 3)//後方一致
		{
			return strOperationNumber.compare(
				strOperationNumber.size()-strOperationNumberInput.size(),
				strOperationNumberInput.size(),
				strOperationNumberInput) == 0;

		}
	}
	else if (m_iRadioOperationTarget == 2)
	{
		/**
			出区・入区駅指定出力
		*/
		if (m_iInOrOut == 0)
		{
			if (ListOperationTableContent.front().iOuterShihatsuekiIndex != INT_MIN)
			{
				if (m_iIncludeOuterTerminal == 0)
				{
					return false;
				}
			}
			/**
				Ver2.02
				運用の先頭列車の作業が「出区」「路線外始発」以外(前列車接続)でも可にします。
			*/
			//else if (ListOperationTableContent.front().aRessyaProperty.getJikoku().isNull())
			//{
			//	return false;
			//}

			int iSihatsuEkiIndex = m_pCentDedRosen->getCentDedEkiCont()->EkiIndexOfEkiOrder(
				ListOperationTableContent.front().aRessyaProperty.getRessyahoukou(), ListOperationTableContent.front().iSihatsuEkiOrder);
			for (int idx = 0; idx < (int)iEkiIndexGroup.size(); idx++)
			{
				if (iSihatsuEkiIndex == iEkiIndexGroup[idx])
				{
					return true;
				}
			}
		}
		else if (m_iInOrOut == 1)
		{
			if (ListOperationTableContent.back().iOuterShuchakuekiIndex != INT_MIN)
			{
				if (m_iIncludeOuterTerminal == 0)
				{
					return false;
				}
			}
			/**
				Ver2.02
				運用の先頭列車の作業が「入区」「路線外終着」以外(次列車接続)でも可にします。
			*/
			//else if (ListOperationTableContent.back().AfterOperation != NULL)
			//{
			//	return false;
			//}

			int iSyuuchakuEkiIndex = m_pCentDedRosen->getCentDedEkiCont()->EkiIndexOfEkiOrder(
				ListOperationTableContent.back().aRessyaProperty.getRessyahoukou(), ListOperationTableContent.back().iSyuuchakuEkiOrder);
			for (int idx = 0; idx < (int)iEkiIndexGroup.size(); idx++)
			{
				if (iSyuuchakuEkiIndex == iEkiIndexGroup[idx])
				{
					return true;
				}
			}
		}
	}
	return false;
}

void CDlgOperationTableCsvExport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOuJikokuhyouCsvExport)
	//}}AFX_DATA_MAP
	DDX_Radio(pDX, IDC_OperationExport_RADIO1, m_iRadioOperationTarget);
	DDX_Text(pDX, IDC_OperationExport_EDIT_KeyWord, m_strOperationNumberInput);
	DDX_CBIndex(pDX, IDC_OperationExport_COMBO_TypeOfSearch, m_iTypeOfSearch);
	DDX_CBIndex(pDX, IDC_OperationExport_COMBO_Station, m_iStationIndex);
	DDX_CBIndex(pDX, IDC_OperationExport_COMBO_OutOrIn, m_iInOrOut);
	DDX_CBIndex(pDX, IDC_OperationExport_COMBO_Order, m_iOperationOrder);
	DDX_Check(pDX, IDC_OperationExport_CHECK_IncludeOuterTerminal, m_iIncludeOuterTerminal);
	DDX_Check(pDX, IDC_OperationExport_CHECK_NoboriLeftToRight, m_iNoboriLeftToRight);
	DDX_Check(pDX, IDC_OperationExport_CHECK_ExtensionOperationTable, m_iExtensionOperationTable);
	DDX_Check(pDX, IDC_OperationExport_CHECK_TrackName, m_iTrackName);
	DDX_Check(pDX, IDC_OperationExport_CHECK_TsuukaEkiJikoku, m_iTsuukaEkiJikoku);
}


BEGIN_MESSAGE_MAP(CDlgOperationTableCsvExport, CDialog)
	//{{AFX_MSG_MAP(CDlgOuJikokuhyouCsvExport)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOuJikokuhyouCsvExport メッセージ ハンドラ

BOOL CDlgOperationTableCsvExport::OnInitDialog()
{
	
	// --------------------------------
	int iRv = 0 ;
	const CentDedDia* pCentDedDia = NULL ;
	if ( iRv >= 0 )
	{
		//pCentDedDia = m_pCentDedRosen->getCentDedDiaCont()->getMuPtr()->get( m_iDiaIndex ) ;
		if ( m_pCentDedDia == NULL )
		{
			iRv = -11 ;	//	m_pCentDedDia が不正です。
		}
	}
	if 	( iRv >= 0 )
	{
		const Mu<const CentDedEki*>* pCentDedEkiCont = m_pCentDedRosen->getCentDedEkiCont()->getMuPtr();

		CComboBox*	pCComboBox = (CComboBox*)GetDlgItem(IDC_OperationExport_COMBO_Station);
		for (int idx = 0; idx < pCentDedEkiCont->size(); idx++ )
		{
			const CentDedEki* pCentDedEki = pCentDedEkiCont->get(idx);
			//tstring strEkimei = stringOf(idx) + ". ";
			//strEkimei = strEkimei + pCentDedEki->getEkimei();
			tstring strEkimei =  pCentDedEki->getEkimei();
			pCComboBox->AddString(strEkimei.c_str());
		}

		//pCComboBox->SetCurSel(m_iStationIndex);
	}

	// コンボボックス
	{
		CComboBox*	pCComboBox = (CComboBox*)GetDlgItem(IDC_OperationExport_COMBO_TypeOfSearch);

		tstring strTemp = _T("と一致する");
		pCComboBox->AddString(strTemp.c_str());
		strTemp = _T("を含む");
		pCComboBox->AddString(strTemp.c_str());
		strTemp = _T("が前方一致する");
		pCComboBox->AddString(strTemp.c_str());
		strTemp = _T("が後方一致する");
		pCComboBox->AddString(strTemp.c_str());
		//と一致する;を含む;が前方一致する;が後方一致する;
	}
	// コンボボックス
	{
		CComboBox*	pCComboBox = (CComboBox*)GetDlgItem(IDC_OperationExport_COMBO_OutOrIn);

		tstring strTemp = _T("出区");
		pCComboBox->AddString(strTemp.c_str());
		strTemp = _T("入区");
		pCComboBox->AddString(strTemp.c_str());
		//出区;入区;
	}
	// コンボボックス
	{
		CComboBox*	pCComboBox = (CComboBox*)GetDlgItem(IDC_OperationExport_COMBO_Order);

		tstring strTemp = _T("運用番号順に並べる");
		pCComboBox->AddString(strTemp.c_str());
		strTemp = _T("出区駅順に並べる");
		pCComboBox->AddString(strTemp.c_str());
		strTemp = _T("発時刻順に並べる");
		pCComboBox->AddString(strTemp.c_str());
		strTemp = _T("入区駅順に並べる");
		pCComboBox->AddString(strTemp.c_str());
		strTemp = _T("着時刻順に並べる");
		pCComboBox->AddString(strTemp.c_str());
		//運用番号順に並べる;出区駅時刻順に並べる;
	}


	CDialog::OnInitDialog();

	// --------------------------------
	
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CDlgOperationTableCsvExport::OnOK()
{
	int iRv = 0 ;
	UpdateData();
	CString	strError ;
	// --------------------------------
	const CentDedDia* pCentDedDia = NULL ;
	//const Mu<const CentDedRessya*>* pCentDedRessyaContGet = NULL ;
	if ( iRv >= 0 )
	{
		//pCentDedDia = m_pCentDedRosen->getCentDedDiaCont()->getMuPtr()->get( m_iDiaIndex ) ;
		if ( m_pCentDedDia == NULL )
		{
			iRv = -11 ;	//	m_iDiaIndex が不正です。
		}
	}
	//if 	( iRv >= 0 )
	//{
	//	pCentDedRessyaContGet = pCentDedDia->getCentDedRessyaCont( m_eRessyahoukou )->getMuPtr() ;
	//}
	//pCentDedRessyaContGet = 対象となる列車コンテナ
	
	
	// --------------------------------
	//	入力値の取得
	// --------------------------------
	const CdDedJikoku KitenJikoku = m_pCentDedRosen->getKitenJikoku();
	
	deque<int> iEkiIndexGroup;
	if (m_iRadioOperationTarget == 2)
	{
		m_pCentDedRosen->getCentDedEkiCont()->getEkiIndexBrunchLoop(
			m_iStationIndex,
			iEkiIndexGroup);
	}

	unordered_map<tstring, list<OperationTableContent>> contOperationTableContent =
		m_pCentDedDia->getcontOperationTableContent();

	const CentDedEkiCont* pCentDedEkiCont = m_pCentDedRosen->getCentDedEkiCont();
	const Mu<const CentDedRessya*>* pCentDedRessyaConts[2];
	for (int iRessyahoukou = Ressyahoukou_Kudari;
		iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
	{
		pCentDedRessyaConts[iRessyahoukou] = m_pCentDedDia->getCentDedRessyaCont((ERessyahoukou)iRessyahoukou)->getMuPtr();
	}

	vector<tstring> strOperationNumberCont;
	vector<int> iEkiIndexCont;
	vector<int> iOuterIndexCont;
	vector<CdDedJikoku> JikokuCont;


	int iMaxRessyaCount = 0;
	for (auto itr = contOperationTableContent.begin();
		itr != contOperationTableContent.end(); itr++)
	{
		if ((int)itr->second.size() > iMaxRessyaCount)
		{
			iMaxRessyaCount = itr->second.size();
		}

		if (!CheckSatisfyConditions(itr->first, itr->second,/*pCentDedRessya,*/ iEkiIndexGroup))
		{
			continue;
		}

		int iEkiIndexTemp;
		int iOuterIndexTemp;
		CdDedJikoku JikokuTemp;
		if (m_iOperationOrder == 1)
		{
			OperationTableContent aShihatsuOperationTableContent = itr->second.front();
			iEkiIndexTemp = pCentDedEkiCont->EkiIndexOfEkiOrder(
				aShihatsuOperationTableContent.aRessyaProperty.getRessyahoukou(),
				aShihatsuOperationTableContent.iSihatsuEkiOrder);
			const CentDedEki* pSihatsuEki = pCentDedEkiCont->getMuPtr()->get(iEkiIndexTemp);

			if (pSihatsuEki->getBrunchLoopPosition() != -1)
			{
				iEkiIndexTemp = pSihatsuEki->getEkiIndexLoop().front();
			}
			iOuterIndexTemp = aShihatsuOperationTableContent.iOuterShihatsuekiIndex;
			if (iOuterIndexTemp != INT_MIN)
			{
				JikokuTemp = aShihatsuOperationTableContent.OuterShihatsuJikoku;
			}
			else
			{
				int iSihatsuEkiOrder = aShihatsuOperationTableContent.iSihatsuEkiOrder;
				const CentDedRessya* pCentDedRessya =
					pCentDedRessyaConts[aShihatsuOperationTableContent.aRessyaProperty.getRessyahoukou()]
					->get(aShihatsuOperationTableContent.aRessyaProperty.getRessyaIndex());

				if (!pCentDedRessya->isRunBetweenNextEki(iSihatsuEkiOrder))
				{
					iSihatsuEkiOrder = pCentDedRessya->getRunBetweenEkiForward(iSihatsuEkiOrder);
				}

				JikokuTemp = pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getHatsujikoku();
			}
		}
		else if (m_iOperationOrder == 2)
		{
			OperationTableContent aShihatsuOperationTableContent = itr->second.front();
			if (aShihatsuOperationTableContent.iOuterShihatsuekiIndex != INT_MIN)
			{
				JikokuTemp = aShihatsuOperationTableContent.OuterShihatsuJikoku;
			}
			else
			{
				int iSihatsuEkiOrder = aShihatsuOperationTableContent.iSihatsuEkiOrder;
				const CentDedRessya* pCentDedRessya =
					pCentDedRessyaConts[aShihatsuOperationTableContent.aRessyaProperty.getRessyahoukou()]
					->get(aShihatsuOperationTableContent.aRessyaProperty.getRessyaIndex());

				if (!pCentDedRessya->isRunBetweenNextEki(iSihatsuEkiOrder))
				{
					iSihatsuEkiOrder = pCentDedRessya->getRunBetweenEkiForward(iSihatsuEkiOrder);
				}

				JikokuTemp = pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getHatsujikoku();
			}
		}
		else if (m_iOperationOrder == 3)
		{
			OperationTableContent aSyuchakuOperationTableContent = itr->second.back();
			iEkiIndexTemp = pCentDedEkiCont->EkiIndexOfEkiOrder(
				aSyuchakuOperationTableContent.aRessyaProperty.getRessyahoukou(),
				aSyuchakuOperationTableContent.iSyuuchakuEkiOrder);
			const CentDedEki* pSyuchakuEki = pCentDedEkiCont->getMuPtr()->get(iEkiIndexTemp);

			if (pSyuchakuEki->getBrunchLoopPosition() != -1)
			{
				iEkiIndexTemp = pSyuchakuEki->getEkiIndexLoop().front();
			}
			iOuterIndexTemp = aSyuchakuOperationTableContent.iOuterShuchakuekiIndex;
			if (iOuterIndexTemp != INT_MIN)
			{
				JikokuTemp = aSyuchakuOperationTableContent.OuterShuchakuJikoku;
			}
			else
			{
				int iSyuuchakuEkiOrder = aSyuchakuOperationTableContent.iSyuuchakuEkiOrder;
				const CentDedRessya* pCentDedRessya =
					pCentDedRessyaConts[aSyuchakuOperationTableContent.aRessyaProperty.getRessyahoukou()]
					->get(aSyuchakuOperationTableContent.aRessyaProperty.getRessyaIndex());

				if (!pCentDedRessya->isRunBetweenNextEki(iSyuuchakuEkiOrder - 1))
				{
					iSyuuchakuEkiOrder = pCentDedRessya->getRunBetweenEkiBackward(iSyuuchakuEkiOrder);
				}

				JikokuTemp = pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getChakujikoku();
			}
		}
		else if (m_iOperationOrder == 4)
		{
			OperationTableContent aSyuchakuOperationTableContent = itr->second.back();
			if (aSyuchakuOperationTableContent.iOuterShuchakuekiIndex != INT_MIN)
			{
				JikokuTemp = aSyuchakuOperationTableContent.OuterShuchakuJikoku;
			}
			else
			{
				int iSyuuchakuEkiOrder = aSyuchakuOperationTableContent.iSyuuchakuEkiOrder;
				const CentDedRessya* pCentDedRessya =
					pCentDedRessyaConts[aSyuchakuOperationTableContent.aRessyaProperty.getRessyahoukou()]
					->get(aSyuchakuOperationTableContent.aRessyaProperty.getRessyaIndex());

				if (!pCentDedRessya->isRunBetweenNextEki(iSyuuchakuEkiOrder - 1))
				{
					iSyuuchakuEkiOrder = pCentDedRessya->getRunBetweenEkiBackward(iSyuuchakuEkiOrder);
				}

				JikokuTemp = pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getChakujikoku();
			}
		}

		bool bInsert = false;
		for (int idx = 0; idx < (int)strOperationNumberCont.size(); idx++)
		{
			if (SortOperation(
				itr->first, iEkiIndexTemp, 
				iOuterIndexTemp, JikokuTemp ,
				strOperationNumberCont[idx],iEkiIndexCont[idx], 
				iOuterIndexCont[idx], JikokuCont[idx],
				KitenJikoku))
		{
				strOperationNumberCont.insert(strOperationNumberCont.begin() + idx, itr->first);
				iEkiIndexCont.insert(iEkiIndexCont.begin() + idx, iEkiIndexTemp);
				iOuterIndexCont.insert(iOuterIndexCont.begin() + idx, iOuterIndexTemp);
				JikokuCont.insert(JikokuCont.begin() + idx, JikokuTemp);
				bInsert = true;
				break;
			}
		}
		if (!bInsert)
		{
			strOperationNumberCont.push_back(itr->first);
			iEkiIndexCont.push_back(iEkiIndexTemp);
			iOuterIndexCont.push_back(iOuterIndexTemp);
			JikokuCont.push_back(JikokuTemp);
		}
	}

	
	// --------------------------------
	//	出力ファイル名入力値の取得
	// --------------------------------
	if ( iRv >= 0 )
	{
		CFileDialog aDlg( 
			FALSE , 
			_T( "csv" ) , 
			m_strCsvFilename , 
			OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
			getCDiagramEditApp()->getCFileDialogFilterCsv(), 
			this );
		if ( aDlg.DoModal() != IDOK )
		{
			iRv = -2 ;	//	Cancelされました。
		}
		else
		{
			m_strCsvFilename = aDlg.GetPathName() ;
		}
	}
	//m_strCsvFilename = 指定されたCSVファイル名

	// --------------------------------
	//	CSVファイルの出力
	// --------------------------------
	CWaitCursor aCursor ;
	if ( iRv >= 0 )
	{
		bool bDisplayNoboriLeftToRight = false;
		if (m_iNoboriLeftToRight == 1)
		{
			bDisplayNoboriLeftToRight = true;
		}
		bool bDisplayExtensionOperationTable = false;
		if (m_iExtensionOperationTable == 1)
		{
			bDisplayExtensionOperationTable = true;
		}
		bool bDisplayTrackName = false;
		if (m_iTrackName == 1)
		{
			bDisplayTrackName = true;
		}
		bool bDisplayTsuukaEkiJikoku = false;
		if (m_iTsuukaEkiJikoku == 1)
		{
			bDisplayTsuukaEkiJikoku = true;
		}
		CconvOperationTableCsv	aConv( getCDiagramEditApp()->createCconvOperationTableCsv()) ;
		CdCsvDocument	aCdCsvDocument ;
		int iResult = aConv.encode(
			*m_pCentDedRosen , 
			*m_pCentDedDia ,
			m_aCdDedDispProp,
			strOperationNumberCont,
			bDisplayExtensionOperationTable,
			m_bDisplaySecondEkiJikoku,
			m_bDisplayColonEkiJikoku,
			m_bDisplayParentSyubetsu,
			bDisplayNoboriLeftToRight,
			bDisplayTrackName,
			bDisplayTsuukaEkiJikoku,
			&aCdCsvDocument ) ;
		if ( iResult < 0 )
		{
			GetDlgItemText( IDC_TEXT_ENCODE_ERROR , strError ) ;
			//strError="CSVへの変換に失敗しました。"

			strError.Format( _T( "%s(%d)" ) , CString( strError ), iResult ) ; 
			iRv = iResult - 10 ;
		}
		else
		{
			tstring strCsvDocument ;
			CConvCsvDocument	aCConvCsvDocument ;
			strCsvDocument = aCConvCsvDocument.encode( &aCdCsvDocument ) ;
			int iResult = stringToFile( strCsvDocument , (LPCTSTR)m_strCsvFilename ) ;
			if ( iResult < 0 )
			{
				GetDlgItemText( IDC_TEXT_FILE_SAVE_FAILED , strError ) ;
				//strError="ファイルへの保存に失敗しました。"

				iRv = -21 ; // ファイルへの保存に失敗しました。

			}
		}
	}
	//CDialog::OnOK();
}

} //namespace ViewAllOperationTable
