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
// CDedAllOperationTable2View.cpp : インプリメンテーション ファイル
//	$Id: CDedAllOperationTable2View.cpp 

#include "stdafx.h"

#include "NsMu/CaMuPtref.h"
#include "NsOu/dynamic_castOu.h"
#include "NsOu/OuNew.h"
#include "LogMsg¥LogMsg.h"
#include "DcDraw¥CConverter_WinGdi.h"
#include "DcDraw¥CaDcdTargetItemPosition.h"
#include "DcDrawMfc/CDcdTargetMfcPrintInfo.h"
#include "DcDraw/print/CaDcdTargetZoomDisplay.h"
#include "str/strToInt.h"

#include "..¥diagramedit.h"
#include "..¥entDed¥CentDedRosen.h"
#include "..¥CRfEditCmdHolder.h"
#include "..¥DedRosenFileData¥EditCmd¥EditCmd.h"
#include "..¥Print¥CconvCdPrintPageProp.h"
#include "CaDcdAllOperationTable2_PageSelector.h"
#include "CDedAllOperationTable2View.h"
#include "CDlgAllOperationTable2ViewProp.h"

namespace ViewAllOperationTable2 {

using namespace std ;
using namespace DcDrawLib::DcDraw::Print;
using namespace DcDrawLib::DcDrawMfc;

/////////////////////////////////////////////////////////////////////////////
// CDedAllOperationTable2View
/**
	ダイヤグラム座標の許容誤差値
*/
const int ALLOWED_DIFFERENCE = 1 ;

// --------------------------------
//@name OnUpdate下請関数
// --------------------------------

void CDedAllOperationTable2View::splitOperationNumber(
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

bool CDedAllOperationTable2View::SortOperationNumber(
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

bool CDedAllOperationTable2View::SortOperation(
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
	if (m_eOperationSort == EOperationSort_OperationNumber)
	{
		/**
			運用番号順
			運用番号をCompareBottomに基づく順で判定します
			同一の運用番号は無いので、結果は一意に決まります
		*/
		return SortOperationNumber(strOperationNumber1, strOperationNumber2);
	}
	else if (m_eOperationSort == EOperationSort_OutEki ||
		m_eOperationSort == EOperationSort_InEki)
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
	else if (m_eOperationSort == EOperationSort_OutJikoku ||
		m_eOperationSort == EOperationSort_InJikoku)
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

void CDedAllOperationTable2View::SortOperation()
{
	unordered_map<tstring, list<OperationTableContent>> contOperationTableContent =
		getCentDedDia()->getcontOperationTableContent();

	const CentDedEkiCont* pCentDedEkiCont = getCDiagramEditDoc()->
		getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont();

	const CentDedRosen* pCentDedRosen = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen();

	int iDiaIndex = pCentDedRosen->getCentDedDiaCont()->findCentDedDiaByName(
		GetDocument()->getDiaName());
	const CentDedDia* pCentDedDia = pCentDedRosen->getCentDedDiaCont()->getMuPtr()->get(iDiaIndex);
	const Mu<const CentDedRessya*>* pCentDedRessyaConts[2];
	for (int iRessyahoukou = Ressyahoukou_Kudari;
		iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
	{
		pCentDedRessyaConts[iRessyahoukou] = pCentDedDia->getCentDedRessyaCont((ERessyahoukou)iRessyahoukou)->getMuPtr();
	}
	const CdDedJikoku KitenJikoku = getCDiagramEditDoc()->getCDedRosenFileData()
		->getCentDedRosen()->getKitenJikoku();

	m_strOperationNumber.clear();
	vector<int> iEkiIndexCont;
	vector<int> iOuterIndexCont;
	vector<CdDedJikoku> JikokuCont;

	for (auto itr = contOperationTableContent.begin();
		itr != contOperationTableContent.end(); itr++)
	{
		int iEkiIndexTemp;
		int iOuterIndexTemp;
		CdDedJikoku JikokuTemp;
		if (m_eOperationSort == EOperationSort_OutEki)
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
		else if (m_eOperationSort == EOperationSort_OutJikoku)
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
		else if (m_eOperationSort == EOperationSort_InEki)
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
		else if (m_eOperationSort == EOperationSort_InJikoku)
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
		for (int idx = 0; idx < (int)m_strOperationNumber.size(); idx++)
		{
			if (SortOperation(itr->first, iEkiIndexTemp,
				iOuterIndexTemp, JikokuTemp,
				m_strOperationNumber[idx], iEkiIndexCont[idx],
				iOuterIndexCont[idx], JikokuCont[idx],
				KitenJikoku))
			{
				m_strOperationNumber.insert(m_strOperationNumber.begin() + idx, itr->first);
				iEkiIndexCont.insert(iEkiIndexCont.begin() + idx, iEkiIndexTemp);
				iOuterIndexCont.insert(iOuterIndexCont.begin() + idx, iOuterIndexTemp);
				JikokuCont.insert(JikokuCont.begin() + idx, JikokuTemp);
				bInsert = true;
				break;
			}
		}
		if (!bInsert)
		{
			m_strOperationNumber.push_back(itr->first);
			iEkiIndexCont.push_back(iEkiIndexTemp);
			iOuterIndexCont.push_back(iOuterIndexTemp);
			JikokuCont.push_back(JikokuTemp);
		}
	}
	m_pCWndAllOperationTable2->setOperationNumber(&m_strOperationNumber);
}
void CDedAllOperationTable2View::OnUpdate_All() 
{
	CWaitCursor	aCWaitCursor ;

	LogMsg(_T("CDedAllOperationTable2View::OnUpdate_All()") ) ;
	// --------------------------------
	//	『ダイヤグラム駅』オブジェクトを生成
	// --------------------------------

	// --------------------------------		
	//	全要素を更新
	// --------------------------------

	SortOperation();

	// --------------------------------
	CdDedDispProp	aCdDedDispProp = getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp() ;
	m_pCWndAllOperationTable2->readCdDedDispProp( aCdDedDispProp ) ;
	
	int iKitenJikoku = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
		->getKitenJikoku().getTotalSeconds();
	
	CdDcdZone aCdDcdZone(0,
		m_pCWndAllOperationTable2->getCDcdAllOperationTable2()->DEFAULT_YSIZE_PER_ONEOPERATION() * m_strOperationNumber.size());

	m_CdDcdZoneXy = CdDcdZoneXy(CdDcdZone(iKitenJikoku, CdDedJikoku::TOTALSECONDS_A_DAY),
		aCdDcdZone);
	m_pCWndAllOperationTable2->setCdDcdZone(&m_CdDcdZoneXy);


	m_pCWndAllOperationTable2->setName(GetDocument()->getDiaName());

	LogMsg(_T("CDedAllOperationTable2View::OnUpdate_All()5") ) ;
	
	// --------------------------------
	m_pCWndAllOperationTable2->onUpdateOperationNumberCont() ;

	LogMsg(_T("CDedAllOperationTable2View::OnUpdate_All()=") ) ;

	m_bUpdate_All_Requested = false ;
}




/**
  整数(補正対象値)が、増減単位の倍数±α(誤差許容値) なら、
  最寄の増減単位の倍数丁度の値に補正します。

(例)iUnit=5,iAllowedDifference=1 の場合、valueに対する結果は以下のとおりです。

　- value=3 なら return=3
　- value=4 なら return=5
　- value=5 なら return=5
　- value=6 なら return=5
　- value=7 なら return=7


　この関数は、以下のために使います。

	「CDcdDiagram::getZone_Dgr()で取得した(描画範囲の幅(ダイヤグラム座標系))が
	増減単位の倍数±α(誤差許容値)なら、(描画範囲の幅(ダイヤグラム座標系))を
	最寄の増減単位の倍数丁度の値に補正する」

@param value [in]
	補正対象値を指定してください。範囲は0以上です。
@param iUnit [in]
	増減単位を指定してください。範囲は1以上です。
@param iAllowedDifference [in]
	誤差許容値
@return
	補正された値を返します。
*/
static int adjustForNearestUnit( int value , int iUnit , int iAllowedDifference ) 
{

	//補正１：(現在値%増減単位)≦(誤差許容値) なら、
	//　現在値=現在値-(現在値%増減単位)
	//
	//(例)
	//　増減単位=1800
	//　現在値=1801
	//　(誤差許容値)=1
	//の場合
	//　(1801%1800)=1 (現在値%増減単位)
	//　1801-(1801%1800)=1800
	//
	if ( value % iUnit <= iAllowedDifference )
	{
		value = value - ( value % iUnit ) ; 
	}

	//補正２：(現在値%増減単位)≧(増減単位-誤差許容値) なら、
	//　現在値=現在値+(増減単位-(現在値%増減単位))
	//
	//(例)
	//　増減単位=1800
	//　現在値=3599
	//　(誤差許容値)=1
	//の場合
	//　(3599%1800)=1799 (現在値%増減単位)
	//　3599+(1800-(3599%1800))=3600
	else if ( ( value % iUnit ) >= ( iUnit - iAllowedDifference ) )
	{
		value = value + ( iUnit - ( value % iUnit ) ) ; 
	}
	return value ;
}



	// --------------------------------
	//@param メッセージ マップ関数の下請関数
	// --------------------------------
int CDedAllOperationTable2View::OnAllOperationTable2XDgrSizeInc_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;
	CString	strErrorMsg ;	

	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	//	横軸方向縮小
	CdDcdZoneXy	zonexyCWndDiagram_Dgr = m_pCWndAllOperationTable2->getZone_Dgr() ;
	CdDcdZone	zoneCWndDiagram_Dgr = zonexyCWndDiagram_Dgr.getX() ;

	//	ウインドウへの表示範囲の増減単位を算出
	//	
	//	運用一覧図全体が画面内に収まっていない場合:30分
	//	運用一覧図全体が画面内に収まっている場合  :12時間
	int iUnit = 30*60 ;
	if ( iRv >= 0 )
	{
		if (zoneCWndDiagram_Dgr.getSize() >=
			m_CdDcdZoneXy.getX().getSize())
		{
			//iUnit = CdDedJikoku::TOTALSECONDS_A_DAY / 2;
			iUnit = m_CdDcdZoneXy.getX().getSize() / 2;
		}
		if ( iUnit == 0 )
		{
			iUnit = 1 ;	//	あとの割り算に備えて、0 は 1 にしておきます。
		}
	}
		//iUnit = ウインドウへの表示範囲の増減単位(ダイヤグラムエンティティX座標)

	//	描画範囲の幅(ダイヤグラム座標系)が増減単位の倍数に近い場合は、
	//	増減単位の倍数丁度の値に補正する
	//	これは、CDcdDiagram に対して setZone_Dgr() で設定した
	//	『描画を行う領域の範囲(ダイヤグラムエンティティ座標系)』と 
	//	getZone_Dgr() で取得した値が一致しない場合があるためです。
	zoneCWndDiagram_Dgr.setSize( 
		adjustForNearestUnit( 
			zoneCWndDiagram_Dgr.getSize() , iUnit , ALLOWED_DIFFERENCE ) ) ;

	if ( iRv >= 0 )
	{
		//	ウインドウ上にダイヤグラムが表示されていない場合は、
		//	X方向の表示範囲は変更できません。
		if ( m_pCWndAllOperationTable2->calcDiagramZoneDcd().getX().getSize() <= 0 )
		{
			iRv = -2 ;	//	ダイヤグラムは表示されていません。
		}
	}
	if ( iRv >= 0 )
	{
		if (zoneCWndDiagram_Dgr.getEndPos() >=
			m_CdDcdZoneXy.getX().getEndPos())
		{
			//	これ以上表示範囲を広げることはできません。
			iRv = -1;	//現在は実行できません(エラーメッセージは表示しません)
		}
	}

	// ****************************************************************
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドを実行
		// ****************************************************************
		DcdSize	iDcdSize = zoneCWndDiagram_Dgr.getSize() ;
		int iMod = iDcdSize % (iUnit) ;
		if ( iMod == 0 ){
			iDcdSize += (iUnit) ;
		}	else	{
			iDcdSize += ( (iUnit) - iMod ) ;
		}
		zoneCWndDiagram_Dgr.setSize( iDcdSize ) ;

		LogMsg(_T("¥t") _T("zoneCWndDiagram_Dgr=%d,%d") ,
			zoneCWndDiagram_Dgr.getPos() , zoneCWndDiagram_Dgr.getSize() ) ;

		zonexyCWndDiagram_Dgr.setX( zoneCWndDiagram_Dgr ) ;
		m_pCWndAllOperationTable2->setZone_Dgr( zonexyCWndDiagram_Dgr ) ;
		// --------------------------------
		if ( iRv < 0 )
		{
			switch( iRv )
			{
			case -1 :	//	現在は実行できません。(エラーメッセージは表示しません)
				break ;
			default:
				strErrorMsg.Format( _T( "Error %d") , iRv ) ;
				break ;
			}
			if ( strErrorMsg.GetLength() > 0 )
			{
				MessageBox( strErrorMsg , 0 , MB_ICONERROR ) ;
			}
		}
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	LogMsg(_T("CDedAllOperationTable2View::OnDiagramXDgrSizeInc_Process()=%d") , iRv ) ;
	return iRv ;
}
int CDedAllOperationTable2View::OnAllOperationTable2XDgrSizeDec_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;
	CString	strErrorMsg ;	
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	// 
	CdDcdZoneXy	zonexyCWndDiagram_Dgr = m_pCWndAllOperationTable2->getZone_Dgr() ;
	CdDcdZone	zoneCWndDiagram_Dgr = zonexyCWndDiagram_Dgr.getX() ;

	//	ウインドウへの表示範囲の増減単位を算出
	//	
	//	運用一覧図全体が画面内に収まっていない場合:30分
	//	運用一覧図全体が画面内に収まっている場合  :12時間
	int iUnit = 30*60 ;
	if ( iRv >= 0 )
	{
		//if ( zoneCWndDiagram_Dgr.getSize() 
		//		> m_pCentDedDgrDia->getZone().getX().getSize() )
		//{
		//	iUnit = m_pCentDedDgrDia->getZone().getX().getSize() / 2 ;
		//}
		if (zoneCWndDiagram_Dgr.getSize() >
			CdDedJikoku::TOTALSECONDS_A_DAY)
		{
			iUnit = m_CdDcdZoneXy.getX().getSize() / 2;
		}
		if ( iUnit == 0 )
		{
			iRv = -2 ;	//	運用一覧図は表示されていません。
		}
	}
		//iUnit=ウインドウへの表示範囲の増減単位(ダイヤグラムエンティティX座標)


	//	描画範囲の幅(ダイヤグラム座標系)が増減単位の倍数に近い場合は、
	//	増減単位の倍数丁度の値に補正する
	//	これは、CDcdDiagram に対して setZone_Dgr() で設定した
	//	『描画を行う領域の範囲(ダイヤグラムエンティティ座標系)』と 
	//	getZone_Dgr() で取得した値が一致しない場合があるためです。
	zoneCWndDiagram_Dgr.setSize( 
		adjustForNearestUnit( 
			zoneCWndDiagram_Dgr.getSize() , iUnit , ALLOWED_DIFFERENCE ) ) ;

	if ( iRv >= 0 )
	{
		//	ウインドウ上に運用一覧図が表示されていない場合は、
		//	X方向の表示範囲は変更できません。
		if ( m_pCWndAllOperationTable2->calcDiagramZoneDcd().getX().getSize() <= 0 )
		{
			iRv = -2 ;	//	ダイヤグラムは表示されていません。
		}
	}
	if ( iRv >= 0 )
	{
		if ( zoneCWndDiagram_Dgr.getSize() <= (iUnit) )
		{
			//	これ以上表示範囲を広げることはできません。
			iRv = -1 ;	//現在は実行できません(エラーメッセージは表示しません)
		}
	}
	// ****************************************************************
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドを実行
		// ****************************************************************
		DcdSize	iDcdSize = zoneCWndDiagram_Dgr.getSize() ;
		int iMod = iDcdSize % (iUnit) ;
		if ( iMod == 0 ){
			iDcdSize -= (iUnit) ;
		}	else	{
			iDcdSize -= iMod  ;
		}
		zoneCWndDiagram_Dgr.setSize( iDcdSize ) ;

		LogMsg(_T("¥t") _T("zoneCWndDiagram_Dgr=%d,%d") ,
			zoneCWndDiagram_Dgr.getPos() , zoneCWndDiagram_Dgr.getSize() ) ;

		zonexyCWndDiagram_Dgr.setX( zoneCWndDiagram_Dgr ) ;
		m_pCWndAllOperationTable2->setZone_Dgr( zonexyCWndDiagram_Dgr ) ;
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************
		if ( iRv < 0 )
		{
			switch( iRv )
			{
			case -1 :	//	現在は実行できません。(エラーメッセージは表示しません)
				break ;
			default:
				strErrorMsg.Format( _T( "Error %d") , iRv ) ;
				break ;
			}
			if ( strErrorMsg.GetLength() > 0 )
			{
				MessageBox( strErrorMsg , 0 , MB_ICONERROR ) ;
			}
		}
		// ****************************************************************
	}
	LogMsg(_T("CDedAllOperationTable2View::OnDiagramXDgrSizeDec_Process()=%d") , iRv ) ;
	return iRv ;
}
int CDedAllOperationTable2View::OnAllOperationTable2XDgrSizeReset_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;
	CString	strErrorMsg ;	
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if ( iRv >= 0 )
	{
		//	ウインドウ上にダイヤグラムが表示されていない場合は、
		//	Y方向の表示範囲は変更できません。
		if ( m_pCWndAllOperationTable2->calcDiagramZoneDcd().getX().getSize() <= 0 )
		{
			iRv = -2 ;	//	ダイヤグラムは表示されていません。
		}
	}
	// ****************************************************************
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドを実行
		// ****************************************************************
		CdDcdZoneXy	zonexyCWndAllOperationTable2_Dgr = m_pCWndAllOperationTable2->getZone_Dgr() ;
		CdDcdZone	zoneCWndDiagram_Dgr = zonexyCWndAllOperationTable2_Dgr.getX() ;

		zoneCWndDiagram_Dgr = m_CdDcdZoneXy.getX() ;

		zonexyCWndAllOperationTable2_Dgr.setX( zoneCWndDiagram_Dgr ) ;
		m_pCWndAllOperationTable2->setZone_Dgr( zonexyCWndAllOperationTable2_Dgr ) ;

		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************
		if ( iRv < 0 )
		{
			switch( iRv )
			{
			case -1 :	//	現在は実行できません。(エラーメッセージは表示しません)
				break ;
			default:
				strErrorMsg.Format( _T( "Error %d") , iRv ) ;
				break ;
			}
			if ( strErrorMsg.GetLength() > 0 )
			{
				MessageBox( strErrorMsg , 0 , MB_ICONERROR ) ;
			}
		}
		// ****************************************************************
	}
	return iRv ;
}

int CDedAllOperationTable2View::OnAllOperationTable2MemoriDown_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	int idxVlineMode = m_pCWndAllOperationTable2->getVlineMode() ;
	bool	bRv = true ;	
	if ( idxVlineMode <= 0 ){
		iRv = -1 ;	//	コマンドを無効
	}
	// ****************************************************************
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドを実行
		// ****************************************************************
		m_pCWndAllOperationTable2->setVlineMode( idxVlineMode - 1 ) ;

		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv ;
}
int CDedAllOperationTable2View::OnAllOperationTable2MemoriUp_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	int idxVlineMode = m_pCWndAllOperationTable2->getVlineMode() ;
	if ( idxVlineMode + 1 >= m_pCWndAllOperationTable2->getVlineChoices( NULL ) ){
		iRv = -1 ;	//	コマンドを無効
	}
	// ****************************************************************
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドを実行
		// ****************************************************************
		m_pCWndAllOperationTable2->setVlineMode( idxVlineMode + 1 ) ;
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv ;
}

int CDedAllOperationTable2View::OnAllOperationTable2EkimeiJikoku_Process(BOOL bQueryEnable)
{
	int iRv = 0;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (m_pCWndAllOperationTable2->getDisplayEkimeiJikoku())
	{
		iRv = 1;
	}

	// ****************************************************************
	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドを実行
		// ****************************************************************
		m_pCWndAllOperationTable2->setDisplayEkimeiJikoku(
			!m_pCWndAllOperationTable2->getDisplayEkimeiJikoku());
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv;
}

int CDedAllOperationTable2View::OnAllOperationTable2Ressyabangou_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if ( m_pCWndAllOperationTable2->getDisplayRessyabangou() )
	{
		iRv = 1 ;
	}

	// ****************************************************************
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドを実行
		// ****************************************************************
		m_pCWndAllOperationTable2->setDisplayRessyabangou( 
			!m_pCWndAllOperationTable2->getDisplayRessyabangou() ) ;
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv ;
}

int CDedAllOperationTable2View::OnUpdateAllOperationTable2SyubetsuRyakusyou_Process(BOOL bQueryEnable)
{
	int iRv = 0;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (m_pCWndAllOperationTable2->getDisplaySyubetsuRyakusyou())
	{
		iRv = 1;
	}
	// ****************************************************************
	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドを実行
		// ****************************************************************
		m_pCWndAllOperationTable2->setDisplaySyubetsuRyakusyou(
			!m_pCWndAllOperationTable2->getDisplaySyubetsuRyakusyou());
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv;
}

int CDedAllOperationTable2View::OnUpdateAllOperationTable2Ressyamei_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if ( m_pCWndAllOperationTable2->getDisplayRessyamei() )
	{
		iRv = 1 ;
	}
	// ****************************************************************
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドを実行
		// ****************************************************************
		m_pCWndAllOperationTable2->setDisplayRessyamei( 
			!m_pCWndAllOperationTable2->getDisplayRessyamei() ) ;
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv ;
}

int CDedAllOperationTable2View::OnUpdateAllOperationTable2JikokuMinute_Process(BOOL bQueryEnable)
{
	int iRv = 0;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (m_pCWndAllOperationTable2->getDisplayJikokuMinute())
	{
		iRv = 1;
	}
	// ****************************************************************
	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドを実行
		// ****************************************************************
		m_pCWndAllOperationTable2->setDisplayJikokuMinute(
			!m_pCWndAllOperationTable2->getDisplayJikokuMinute());
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv;
}


int CDedAllOperationTable2View::OneDisplayParentSyubetsu_Process(BOOL bQueryEnable)
{
	int iRv = 0;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	if (m_pCWndAllOperationTable2->getDisplayParentSyubetsu())
	{
		iRv = 1;
	}
	// ****************************************************************
	if (!bQueryEnable && iRv >= 0)
	{
		// ****************************************************************
		//	コマンドを実行
		// ****************************************************************
		m_pCWndAllOperationTable2->setDisplayParentSyubetsu(
			!m_pCWndAllOperationTable2->getDisplayParentSyubetsu());
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv;
}

int CDedAllOperationTable2View::OnViewUpdate_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************
	//if (m_bWaitOperationConnect)
	//{
	//	iRv = -1;
	//}

	// ****************************************************************
	if ( !bQueryEnable && iRv >= 0 )
	{
		// ****************************************************************
		//	コマンドを実行
		// ****************************************************************
		//	ビューを全更新します。
		OnUpdate( NULL , 0 , NULL ) ;
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv ;
}

int CDedAllOperationTable2View::OnAllOperationTable2ViewProp_Process( BOOL bQueryEnable )
{
	int iRv = 0 ;
	// ****************************************************************
	//	コマンドの有効・無効判定
	// ****************************************************************

	// ****************************************************************
	if ( !bQueryEnable && iRv >= 0 )
	{
		//	ウインドウ内で、ダイヤグラムを描画する領域の大きさを求めます。
		//	単位は、 IfDcdTarget 上の座標です。
		CdDcdZoneXy	zoneDiagramZoneDcd = m_pCWndAllOperationTable2->calcDiagramZoneDcd() ;

		CDlgAllOperationTable2ViewProp aDlg(
			m_CdDcdZoneXy.getX(),
			//	ウインドウのX方向幅が、ダイヤグラムが表示可能な大きさであるか
			//	否かを指定
			zoneDiagramZoneDcd.getX().getSize() > 0 ,
			//	ウインドウのY方向幅が、ダイヤグラムが表示可能な大きさであるか
			//	否かを指定
			//zoneDiagramZoneDcd.getY().getSize() > 0 ,
			m_pCWndAllOperationTable2->getZone_Dgr() ,
			m_pCWndAllOperationTable2->getVlineMode() ,
			m_eOperationSort,
			m_bCompareBottom,
			this ) ;
		if ( aDlg.DoModal() == IDOK ){
			m_eOperationSort = aDlg.getOperationSort();
			m_bCompareBottom = aDlg.getCompareBottom();
			SortOperation();
			m_pCWndAllOperationTable2->setZone_Dgr( aDlg.getCWndDiagramZone_Dgr() );
			m_pCWndAllOperationTable2->setVlineMode( aDlg.getVlineMode() ) ;
		}	
		// ****************************************************************
		//	エラーメッセージ
		// ****************************************************************

		// ****************************************************************
	}
	return iRv ;
}


// ********************************
//	CDedAllOperationTable2View
// ********************************
	// ********************************
	//@name CDedAllOperationTable2View-操作
	// ********************************
int CDedAllOperationTable2View::setZone_Dgr( 
		const CdDedJikoku& aCdDedJikoku ,
		int iOperationNumberIndex)
{
	CdDcdZoneXy	zonexyZone_Dgr = m_pCWndAllOperationTable2->getZone_Dgr() ;
	
	//X座標を変更
	if ( !aCdDedJikoku.isNull() ){
		CdDcdZone	aCdDcdZone = zonexyZone_Dgr.getX() ;
		aCdDcdZone.setPos( aCdDedJikoku.getTotalSeconds() ) ;
		zonexyZone_Dgr.setX( aCdDcdZone ) ;
	}
	//Y座標を変更
	if ( 0 <= iOperationNumberIndex && iOperationNumberIndex < (int)m_strOperationNumber.size() ){
		CdDcdZone	aCdDcdZone = zonexyZone_Dgr.getY() ;
		int iYZahyou =
			iOperationNumberIndex *
			m_pCWndAllOperationTable2->getCDcdAllOperationTable2()->DEFAULT_YSIZE_PER_ONEOPERATION();
		aCdDcdZone.setPos( iYZahyou ) ;
		zonexyZone_Dgr.setY( aCdDcdZone ) ;
	}
		
	return m_pCWndAllOperationTable2->setZone_Dgr( zonexyZone_Dgr ) ;
}

// ----------------------------------------------------------------
IMPLEMENT_DYNCREATE(CDedAllOperationTable2View, CView)

CDedAllOperationTable2View::CDedAllOperationTable2View()
	: m_pCWndAllOperationTable2( NULL ) 
	, m_bUpdate_All_Requested( false ) 
	, m_eOperationSort(EOperationSort_OperationNumber)
	, m_bCompareBottom(false)
{
}

CDedAllOperationTable2View::‾CDedAllOperationTable2View()
{
}


BEGIN_MESSAGE_MAP(CDedAllOperationTable2View, CView)
	//{{AFX_MSG_MAP(CDedAllOperationTable2View)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_COMMAND(ID_AllOperationTable2_ViewProp, OnAllOperationTable2ViewProp)
	ON_COMMAND(ID_Diagram_XDgrSize_Inc, OnAllOperationTable2XDgrSizeInc)
	ON_UPDATE_COMMAND_UI(ID_Diagram_XDgrSize_Inc, OnUpdateAllOperationTable2XDgrSizeInc)
	ON_COMMAND(ID_AllOperationTable2_XDgrSize_Inc, OnAllOperationTable2XDgrSizeInc)
	ON_UPDATE_COMMAND_UI(ID_AllOperationTable2_XDgrSize_Inc, OnUpdateAllOperationTable2XDgrSizeInc)
	ON_COMMAND(ID_Diagram_XDgrSize_Dec, OnAllOperationTable2XDgrSizeDec)
	ON_UPDATE_COMMAND_UI(ID_Diagram_XDgrSize_Dec, OnUpdateAllOperationTable2XDgrSizeDec)
	ON_COMMAND(ID_AllOperationTable2_XDgrSize_Dec, OnAllOperationTable2XDgrSizeDec)
	ON_UPDATE_COMMAND_UI(ID_AllOperationTable2_XDgrSize_Dec, OnUpdateAllOperationTable2XDgrSizeDec)
	ON_COMMAND(ID_Diagram_Memori_Down, OnAllOperationTable2MemoriDown)
	ON_UPDATE_COMMAND_UI(ID_Diagram_Memori_Down, OnUpdateAllOperationTable2MemoriDown)
	ON_COMMAND(ID_AllOperationTable2_Memori_Down, OnAllOperationTable2MemoriDown)
	ON_UPDATE_COMMAND_UI(ID_AllOperationTable2_Memori_Down, OnUpdateAllOperationTable2MemoriDown)
	ON_COMMAND(ID_Diagram_Memori_Up, OnAllOperationTable2MemoriUp)
	ON_UPDATE_COMMAND_UI(ID_Diagram_Memori_Up, OnUpdateAllOperationTable2MemoriUp)
	ON_COMMAND(ID_AllOperationTable2_Memori_Up, OnAllOperationTable2MemoriUp)
	ON_UPDATE_COMMAND_UI(ID_AllOperationTable2_Memori_Up, OnUpdateAllOperationTable2MemoriUp)
	ON_COMMAND(ID_AllOperationTable2_EkimeiJikoku, OnAllOperationTable2EkimeiJikoku)
	ON_UPDATE_COMMAND_UI(ID_AllOperationTable2_EkimeiJikoku, OnUpdateAllOperationTable2EkimeiJikoku)
	ON_COMMAND(ID_Diagram_Ressyabangou, OnAllOperationTable2Ressyabangou)
	ON_UPDATE_COMMAND_UI(ID_Diagram_Ressyabangou, OnUpdateAllOperationTable2Ressyabangou)
	ON_COMMAND(ID_AllOperationTable2_SyubetsuRyakusyou, OnAllOperationTable2SyubetsuRyakusyou)
	ON_UPDATE_COMMAND_UI(ID_AllOperationTable2_SyubetsuRyakusyou, OnUpdateAllOperationTable2SyubetsuRyakusyou)
	ON_COMMAND(ID_Diagram_Ressyamei, OnAllOperationTable2Ressyamei)
	ON_UPDATE_COMMAND_UI(ID_Diagram_Ressyamei, OnUpdateAllOperationTable2Ressyamei)
	ON_COMMAND(ID_AllOperationTable2_JikokuMinute, OnAllOperationTable2JikokuMinute)
	ON_UPDATE_COMMAND_UI(ID_AllOperationTable2_JikokuMinute, OnUpdateAllOperationTable2JikokuMinute)
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_AllOperationTable2_XDgrSize_Reset, OnAllOperationTable2XDgrSizeReset)
	ON_UPDATE_COMMAND_UI(ID_AllOperationTable2_XDgrSize_Reset, OnUpdateAllOperationTable2XDgrSizeReset)

	ON_COMMAND(ID_VIEW_UPDATE, OnViewUpdate)
	ON_UPDATE_COMMAND_UI(ID_VIEW_UPDATE, OnUpdateViewUpdate)
	//}}AFX_MSG_MAP
	// 標準印刷コマンド
	ON_COMMAND(ID_VIEW_DisplayParentSyubetsu, &CDedAllOperationTable2View::OnDisplayParentSyubetsu)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DisplayParentSyubetsu, &CDedAllOperationTable2View::OnUpdateDisplayParentSyubetsu)
	ON_COMMAND(ID_FILE_PRINT, &CDedAllOperationTable2View::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CDedAllOperationTable2View::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDedAllOperationTable2View 描画

void CDedAllOperationTable2View::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: この位置に描画用のコードを追加してください
}

/////////////////////////////////////////////////////////////////////////////
// CDedAllOperationTable2View 診断

#ifdef _DEBUG
void CDedAllOperationTable2View::AssertValid() const
{
	CView::AssertValid();
}

void CDedAllOperationTable2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDedAllOperationTable2View メッセージ ハンドラ



void CDedAllOperationTable2View::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if ( lHint == LHINT_SUBVIEW_TO_ROOTDOC ){
		return ;
	}
	// --------------------------------

	//pHint= 
	//	pHintが CRfEditCmdHolder オブジェクトなら、
	//	対応する編集コマンド CRfEditCmd を保持しています。
	//	この場合、this は CRfEditCmd の内容に最適化した
	//	更新を行います。
	//	NULLなら、全更新が要求されています。

	if ( m_bUpdate_All_Requested )
	{
		//	全更新が保留されている場合は、
		//	その後はコマンドによる最適化された単体のいかなる
		//	更新要求に対しても、全更新を行います。
		//memo:CDedAllOperationTable2Viewの全更新
		//	これを行わないと、
		//	(1)ダイヤグラムビューを開いた状態にする
		//	(2)駅を追加
		//		( m_bUpdate_All_Requested =true となりますが、
		//		ビューがアクティブでないため、
		//		CentDedDgrDia::m_CentDedDgrEkiCont の
		//		更新が行われません。
		//	(3)その駅に運行する列車を入力する
		//		編集コマンドは CRfEditCmd_Ressya 
		//		なので、列車の更新が行われます。
		//		しかし、CentDedDgrDia::m_CentDedDgrEkiCont が
		//		更新されていないため、アプリケーションエラーになります。
		//		
		pHint = NULL ;
	}

	// --------------------------------
	//	CRfEditCmd に最適化された更新
	// --------------------------------
	Ou<CRfEditCmd> pCmd ;
	if ( pHint != NULL && pHint->IsKindOf( 
		RUNTIME_CLASS( CRfEditCmdHolder ) ) )
	{
		CRfEditCmdHolder* pHolder = 
			(CRfEditCmdHolder*)pHint ;
		pCmd = pHolder->getCmd() ; 
	}
	//pCmd = (pCmdがNULLでない場合は)対応する編集コマンド

	if ( pCmd != NULL )
	{
		if ( dynamic_castOu<CRfEditCmd_Comment>( pCmd ) || 
			dynamic_castOu<CRfEditCmd_Dia>( pCmd ) || 
			dynamic_castOu<CRfEditCmd_DiaProp>( pCmd ) || 
			dynamic_castOu<CRfEditCmd_RessyasyubetsuSwap>( pCmd ) ) 
		{
			//	このビューは、
			//		コメントの変更
			//		ダイヤの変更
			//		ダイヤのプロパティの変更
			//		列車種別の入替
			//	の場合は、更新を行いません。
		}
		else
		{
			//	CRfEditCmd_Ressya
			//	列車の変更
			//CRfEditCmd_Eki
			//	駅の変更は、全更新が必要です。
			//CRfEditCmd_Ressyasyubetsu
			//	列車種別の変更は、全更新が必要です。
			//CRfEditCmd_DedRosenFileDataProp
			//	  路線ファイルのプロパティの変更は、
			//	フォントの変化を伴うため、全更新が必要です。
			//CRfEditCmd_Rosen
			//CRfEditCmd_RosenFileData
			//	駅を包含するオブジェクトです。これが更新された場合は、
			//	全更新が必要です。

			pHint = NULL ;	//	全更新の要求
		}
	}

	if ( pHint == NULL )	//	全更新
	{
		// --------------------------------		
		//	全要素を更新
		// --------------------------------
		CView *pView = getCDiagramEditApp()->getCMainFrame()->
			getMDIChildActiveView() ;
		if ( this == pView ){
			OnUpdate_All() ;
		}	else	{
			LogMsg(_T("CDedAllOperationTable2View::OnUpdate()")
				_T("m_bUpdate_All_Requested=true") ) ;
			m_bUpdate_All_Requested = true ;
		}
	}

}

int CDedAllOperationTable2View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// --------------------------------
	m_pCWndAllOperationTable2 = new CWndAllOperationTable2() ;
	m_pCWndAllOperationTable2->Create( this ) ;
	m_pCWndAllOperationTable2->ShowWindow( SW_SHOW ) ;

	return 0;
}

void CDedAllOperationTable2View::OnDestroy() 
{
	//	ダイヤグラムビューの属性を .ini ファイルに書き込み。
	//getCDiagramEditApp()->writeCWndAllOperationTable2ViewProp( m_pCWndAllOperationTable2 ) ;

	if ( m_pCWndAllOperationTable2 != NULL ){
		m_pCWndAllOperationTable2->DestroyWindow() ;
		delete m_pCWndAllOperationTable2 ;
		m_pCWndAllOperationTable2 = NULL ;
	}

	CView::OnDestroy();
	

	
}

void CDedAllOperationTable2View::OnSize(UINT nType, int cx, int cy) 
{
	if ( nType == SIZE_MAXIMIZED	//ウィンドウは最大表示されます。
		|| nType == SIZE_RESTORED 	// ウィンドウはサイズ変更されますが、
									//	SIZE_MINIMIZED と SIZE_MAXIMIZED は
									//	適用されません。
	){
		//memo:CDedAllOperationTable2View::OnSize()
		//	この関数を使うと、リサイズ時にウインドウの全領域が無効になります。
		m_pCWndAllOperationTable2->MoveWindow( 0 , 0 , cx , cy , TRUE ) ; 

		////memo:CDedAllOperationTable2View::OnSize()
		////	この関数を使っても、リサイズ時にウインドウの
		////	全領域が無効になります
		//m_pCWndAllOperationTable2->SetWindowPos( 
		//	NULL , 
		//	0 , 0 , 
		//	cx , cy , 
		//	SWP_NOACTIVATE	//	ウィンドウをアクティブにしません。
		//	                //	このフラグが設定されていないと、
		//	                //	ウィンドウはアクティブになり、
		//	                //	最上位または非最上位のウィンドウ 
		//	                //	グループのいずれかの先頭に移動されます 
		//	                //(パラメータ pWndInsertAfter の設定に依存します)。
		//	| SWP_NOZORDER	//  現在の順序を保持します 
		//	                //	(pWndInsertAfter を無視します)。
		//	| SWP_NOMOVE ) ;// 現在位置を保持します 
		//	                //(x パラメータと y パラメータを無視します)。

		////memo:CDedAllOperationTable2View::OnSize()
		////	この関数を使っても、リサイズ時にウインドウの
		////	全領域が無効になります。
		//m_pCWndAllOperationTable2->MoveWindow( 0 , 0 , cx , cy , FALSE ) ; 

		return ;
	}
	
	
	CView::OnSize(nType, cx, cy);
}


void CDedAllOperationTable2View::OnAllOperationTable2ViewProp()
{
	OnAllOperationTable2ViewProp_Process( FALSE );
}

void CDedAllOperationTable2View::OnAllOperationTable2XDgrSizeInc()
{
	OnAllOperationTable2XDgrSizeInc_Process( FALSE ) ;
}

void CDedAllOperationTable2View::OnUpdateAllOperationTable2XDgrSizeInc(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(OnAllOperationTable2XDgrSizeInc_Process( TRUE ) >= 0 );
}

void CDedAllOperationTable2View::OnAllOperationTable2XDgrSizeDec()
{
	OnAllOperationTable2XDgrSizeDec_Process( FALSE ) ;
}

void CDedAllOperationTable2View::OnUpdateAllOperationTable2XDgrSizeDec(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(OnAllOperationTable2XDgrSizeDec_Process( TRUE ) >= 0 );
}

void CDedAllOperationTable2View::OnAllOperationTable2XDgrSizeReset()
{
	OnAllOperationTable2XDgrSizeReset_Process( FALSE ) ;
}

void CDedAllOperationTable2View::OnUpdateAllOperationTable2XDgrSizeReset(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(	OnAllOperationTable2XDgrSizeReset_Process( TRUE ) >= 0 );
}


void CDedAllOperationTable2View::OnAllOperationTable2MemoriDown()
{
	OnAllOperationTable2MemoriDown_Process( FALSE ) ;
}
void CDedAllOperationTable2View::OnUpdateAllOperationTable2MemoriDown(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(OnAllOperationTable2MemoriDown_Process( TRUE ) >= 0 );
}

void CDedAllOperationTable2View::OnAllOperationTable2MemoriUp()
{
	OnAllOperationTable2MemoriUp_Process( FALSE ) ;
}

void CDedAllOperationTable2View::OnUpdateAllOperationTable2MemoriUp(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(OnAllOperationTable2MemoriUp_Process( TRUE ) >= 0 );
}


void CDedAllOperationTable2View::OnAllOperationTable2EkimeiJikoku()
{
	OnAllOperationTable2EkimeiJikoku_Process(FALSE);
}
void CDedAllOperationTable2View::OnUpdateAllOperationTable2EkimeiJikoku(CCmdUI* pCmdUI)
{
	int iResult = OnAllOperationTable2EkimeiJikoku_Process(TRUE);
	pCmdUI->Enable(iResult >= 0);
	pCmdUI->SetCheck(iResult >= 1);

}

void CDedAllOperationTable2View::OnAllOperationTable2Ressyabangou()
{
	OnAllOperationTable2Ressyabangou_Process( FALSE ) ;
}
void CDedAllOperationTable2View::OnUpdateAllOperationTable2Ressyabangou(CCmdUI* pCmdUI)
{
	int iResult = OnAllOperationTable2Ressyabangou_Process( TRUE ) ;
	pCmdUI->Enable( iResult >= 0 ) ;
	pCmdUI->SetCheck( iResult >= 1 ) ;
	
}

void CDedAllOperationTable2View::OnAllOperationTable2SyubetsuRyakusyou()
{
	OnUpdateAllOperationTable2SyubetsuRyakusyou_Process(FALSE);
}

void CDedAllOperationTable2View::OnUpdateAllOperationTable2SyubetsuRyakusyou(CCmdUI* pCmdUI)
{
	int iResult = OnUpdateAllOperationTable2SyubetsuRyakusyou_Process(TRUE);
	pCmdUI->Enable(iResult >= 0);
	pCmdUI->SetCheck(iResult >= 1);
}

void CDedAllOperationTable2View::OnAllOperationTable2Ressyamei()
{
	OnUpdateAllOperationTable2Ressyamei_Process( FALSE ) ;
}

void CDedAllOperationTable2View::OnUpdateAllOperationTable2Ressyamei(CCmdUI* pCmdUI)
{
	int iResult = OnUpdateAllOperationTable2Ressyamei_Process( TRUE ) ;
	pCmdUI->Enable( iResult >= 0 ) ;
	pCmdUI->SetCheck( iResult >= 1 ) ;
}

void CDedAllOperationTable2View::OnAllOperationTable2JikokuMinute()
{
	OnUpdateAllOperationTable2JikokuMinute_Process(FALSE);
}

void CDedAllOperationTable2View::OnUpdateAllOperationTable2JikokuMinute(CCmdUI* pCmdUI)
{
	int iResult = OnUpdateAllOperationTable2JikokuMinute_Process(TRUE);
	pCmdUI->Enable(iResult >= 0);
	pCmdUI->SetCheck(iResult >= 1);
}



void CDedAllOperationTable2View::OnDisplayParentSyubetsu()
{
	OneDisplayParentSyubetsu_Process(FALSE);
}

void CDedAllOperationTable2View::OnUpdateDisplayParentSyubetsu(CCmdUI *pCmdUI)
{
	int iResult = OneDisplayParentSyubetsu_Process(TRUE);
	pCmdUI->Enable(iResult >= 0);
	pCmdUI->SetCheck(iResult >= 1);
}

void CDedAllOperationTable2View::OnViewUpdate() 
{
	OnViewUpdate_Process( FALSE );
}

void CDedAllOperationTable2View::OnUpdateViewUpdate(CCmdUI *pCmdUI)
{
	int iResult = OnViewUpdate_Process(TRUE);
	pCmdUI->Enable(iResult >= 0);
	pCmdUI->SetCheck(iResult >= 1);
}



BOOL CDedAllOperationTable2View::OnPreparePrinting(CPrintInfo* pInfo) 
{
	BOOL bRv = TRUE ;

	// デフォルトの印刷準備
	//CaDcdAllOperationTable2_PageSelector	aPageSelector(
	//	m_pCWndAllOperationTable2->getCDcdAllOperationTable2() , 
	//	m_sizePrintSize_Dgr ) ;
	CaDcdAllOperationTable2_PageSelector	aPageSelector(
		m_pCWndAllOperationTable2->getCDcdAllOperationTable2(),
		m_sizePrintSize_DgrLeft,
		m_sizePrintSize_DgrCenter,
		m_sizePrintSize_DgrRight);
	if ( bRv )
	{
		if ( aPageSelector.getPageCount() == 0 )
		{
			//	印刷するページがありません。
			bRv = FALSE ;
		}
	}
	if ( bRv )
	{
		//	ウインドウ上にダイヤグラムが表示されていない場合は、
		//	印刷は行いません。
		if ( m_pCWndAllOperationTable2->calcDiagramZoneDcd().getX().getSize() <= 0 ||
			m_pCWndAllOperationTable2->calcDiagramZoneDcd().getY().getSize() <= 0 )
		{
			//	印刷するページがありません。
			bRv = FALSE ;
		}
	}
	// --------------------------------

	if ( bRv )
	{
		pInfo->SetMinPage( 1 ) ;
		pInfo->SetMaxPage( aPageSelector.getPageCount()  ) ;

		bRv = DoPreparePrinting(pInfo);
	}
	
	return bRv ;
}

void CDedAllOperationTable2View::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
	//	この時点では、 
	//	pInfo->m_rectDraw
	//	の値は決定していません。

	if ( m_bUpdate_All_Requested ){
		OnUpdate_All() ;
	}


	CView::OnBeginPrinting(pDC, pInfo);
}

void CDedAllOperationTable2View::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	//	この時点では、 
	//	pInfo->m_rectDraw
	//	の値は決定していません。

	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	
	CView::OnPrepareDC(pDC, pInfo);
}


static CdDrawTextProp	getCdDrawTextPropStandard()
{ 
	const CDedRosenFileData* pCDedRosenFileData = 
		getCDiagramEditDoc()->getCDedRosenFileData() ;
	CdDedDispProp aCdDedDispProp = pCDedRosenFileData->getCdDedDispProp() ;

	return CdDrawTextProp(
		aCdDedDispProp.getOperationTableFont(),
		aCdDedDispProp.getOperationStringColor());
		//aCdDedDispProp.getDiaJikokuFont() ,
		//CdColorProp( 0 , 0 , 0 ) ) ;
}


void CDedAllOperationTable2View::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	LogMsg(_T("CDedAllOperationTable2View::OnPrint() ") ) ;
	LogMsg( CDcdTargetMfcPrintInfo::stringOf( pInfo ).c_str() ) ;

	// --------------------------------
	//	描画面を作成
	// --------------------------------
	CDcdTargetMfcPrintInfo	aCDcdTargetMfcPrintInfo( pDC, pInfo ) ;

	LogMsg(_T("CDedAllOperationTable2View::OnPrint()1") ) ;
	
	// --------------------------------
	//	余白を除いた領域を作成
	// --------------------------------
	CaDcdTargetItemPosition	aTargetInnerMargin( &aCDcdTargetMfcPrintInfo , 
		CdDcdZoneXy() ) ;
	{
		LogMsg( DeviceCapsToString( 
			aCDcdTargetMfcPrintInfo.getPrinterHdc() ).c_str() ) ;
	
		CconvCdPrintPageProp aCconvCdPrintPageProp ;
		CdDcdZoneXy	zonexyInneraMargin = 
			aCconvCdPrintPageProp.calcZoneInnerMargin( 
				getCDiagramEditApp()->getCdPrintPageProp() , 
				aCDcdTargetMfcPrintInfo.getPrinterHdc() ) ;
		if ( zonexyInneraMargin.getX().getSize() <= 0 ){
			zonexyInneraMargin.setX( 
				aCDcdTargetMfcPrintInfo.getZone().getX() ) ;
		}
		if ( zonexyInneraMargin.getY().getSize() <= 0 ){
			zonexyInneraMargin.setY( 
				aCDcdTargetMfcPrintInfo.getZone().getY() ) ;
		}

		aTargetInnerMargin.setZone( zonexyInneraMargin ) ;

	}

	//aTargetInnerMargin = 余白部分を除いた描画領域。
	//	単位はプリンタのピクセルです。

	LogMsg(_T("CDedAllOperationTable2View::OnPrint()2") ) ;
	// --------------------------------
	//	論理座標を設定
	// --------------------------------
	CaDcdTargetZoomDisplay	aCaDcdTargetZoomDisplay( 
		&aTargetInnerMargin , 
		aCDcdTargetMfcPrintInfo.getPrinterHdc() ) ;
	//aCaDcdTargetZoomDisplay = 余白部分を除いた描画領域。
	//	単位は、画面上の１ピクセル相当になりました。

	LogMsg(_T("CDedAllOperationTable2View::OnPrint()3") ) ;
	
	// --------------------------------
	//	キャプションとページ番号の部品を作成
	// --------------------------------
	Ou<CDcdText>	pdcdCaption ;
	Ou<CDcdText>	pdcdPage ;
	{
		const CentDedRosen* pCentDedRosen = 
			getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen() ;
		//CJikokuhyouDoc* pCJikokuhyouDoc = (CJikokuhyouDoc*)GetDocument() ;
		CDedAllOperationTable2Doc* pCDedAllOperationTable2Doc = (CDedAllOperationTable2Doc*)GetDocument();

		tstring	strText ;
		//	路線名
		if ( !pCentDedRosen->getName().empty() ){
			strText += pCentDedRosen->getName() ;
			strText += _T(" ") ;
		}
		//	ダイヤ名
		if ( !pCDedAllOperationTable2Doc->getDiaName().empty() ){
			strText += pCDedAllOperationTable2Doc->getDiaName() ;
			strText += _T(" ") ;
		}

		CString	aString;
		aString.LoadString(IDS_WORD_ALLOPERATIONTABLE2);
		strText += (LPCTSTR)aString;
		strText += _T(" ");

		pdcdCaption = OuNew<CDcdText>( new CDcdText( 
			strText , getCdDrawTextPropStandard() ) ) ;
	}
	// --------------------------------
	{
		CdDrawTextProp	aProp = getCdDrawTextPropStandard() ;
		CdDrawTextFormat	aFormat = aProp.getCdDrawTextFormat() ;
		aFormat.setHorizontal( aFormat.H_CENTER ) ;
		aProp.setCdDrawTextFormat( aFormat ) ;
		pdcdPage = OuNew<CDcdText>( new CDcdText(_T("") ,aProp , _T("99") ) ) ;
	}

	LogMsg(_T("CDedAllOperationTable2View::OnPrint()4") ) ;
	// --------------------------------
	//	キャプションとページ番号の部品・
	//	グリッドのレイアウトを決める	
	// --------------------------------
	Ou<IfDcdTarget>	pTargetCaption ;
	Ou<IfDcdTarget>	pTargetGrid ;
	Ou<IfDcdTarget>	pTargetPage ;
	{
		CdDcdZoneXy	zoneGrid = aCaDcdTargetZoomDisplay.getZone() ;
		CdDcdSizeXy	aSize ;
		
		pdcdCaption->getItemSize(&aCaDcdTargetZoomDisplay, &aSize);
		CdDcdZoneXy zoneCaption(zoneGrid.getX(),
			CdDcdZone(zoneGrid.getY().getPos(), aSize.getY()));
		if (getCDiagramEditApp()->getCdPrintPageProp().getPrintHeader() > 0)
		{
			zoneGrid.setY(CdDcdZone().setBeginEndPos(
				zoneCaption.getY().getEndPos(), zoneGrid.getY().getEndPos()));
			//zoneCaption = 全領域の上部を、キャプション用に割り当てています。
			//zoneGrid = 全領域から、上部のキャプション領域を除いた領域です。

		}

			pdcdPage->getItemSize(&aCaDcdTargetZoomDisplay, &aSize);
			CdDcdZoneXy zonePage(zoneGrid.getX(),
				CdDcdZone(zoneGrid.getY().getEndPos() - aSize.getY(),
					aSize.getY()));
		if (getCDiagramEditApp()->getCdPrintPageProp().getPrintFooter() > 0)
		{
			zoneGrid.setY(CdDcdZone().setBeginEndPos(
				zoneGrid.getY().getPos(), zonePage.getY().getPos()));
			//zoneCaption.getY().getEndPos(), zonePage.getY().getPos()));
			//zonePage = 全領域の下部を、ページ用に割り当てています。
			//zoneGrid = 上部のキャプションに続いて、下部のページ領域も除いた
			//			領域です。
		}


		pTargetCaption = OuNew<CaDcdTargetItemPosition>( 
			new CaDcdTargetItemPosition( 
				&aCaDcdTargetZoomDisplay , zoneCaption ) ) ;
		pTargetGrid = OuNew<CaDcdTargetItemPosition>( 
			new CaDcdTargetItemPosition( 
				&aCaDcdTargetZoomDisplay , zoneGrid ) ) ;
		pTargetPage = OuNew<CaDcdTargetItemPosition>(
			new CaDcdTargetItemPosition( 
				&aCaDcdTargetZoomDisplay , zonePage ) ) ;
	}
	// --------------------------------
	//	ダイヤグラムを描画
	// --------------------------------
	
	int iPage = 0 ;
	int iXPage = 0 ;
	{
		CDcdAllOperationTable2*	pCDcdAllOperationTable2 = m_pCWndAllOperationTable2->getCDcdAllOperationTable2() ;
		//CaDcdAllOperationTable2_PageSelector	aPageSelector(
		//	pCDcdAllOperationTable2 ,
		//	m_sizePrintSize_Dgr ) ;
		CaDcdAllOperationTable2_PageSelector	aPageSelector(
			pCDcdAllOperationTable2,
			m_sizePrintSize_DgrLeft,
			m_sizePrintSize_DgrCenter,
			m_sizePrintSize_DgrRight);
		aPageSelector.setPage( pInfo->m_nCurPage - 1 ) ;
		aPageSelector.DcDraw( pTargetGrid ) ;


		pInfo->SetMinPage(1);
		pInfo->SetMaxPage(aPageSelector.getPageCount(pTargetGrid));

		pCDcdAllOperationTable2->setNoDisplayLeftSpace(false);
		pCDcdAllOperationTable2->setNoDisplayAllOperationTableSpace(false);
		pCDcdAllOperationTable2->setNoDisplayRightSpace(false);
		pCDcdAllOperationTable2->setClippingCount(0);

		if ( (int)pInfo->m_nCurPage >= aPageSelector.getPageCount() ){
			//最終ページを印刷したら、印刷ループを終わります。
			pInfo->m_bContinuePrinting = false ;
		}	else	{
			pInfo->m_bContinuePrinting = true ;
		}


		iPage = aPageSelector.getPage() ;
		iXPage = aPageSelector.getXPage() ;
	}
	

	LogMsg(_T("CDedAllOperationTable2View::OnPrint()5") ) ;
	LogMsg(_T("CDedAllOperationTable2View::OnPrint()6") ) ;
	// --------------------------------
	//	キャプションとページ番号のテキストを作成
	// --------------------------------
	{
		//キャプションにページを追加
		{
			tstring	strCaption = pdcdCaption->getText() ;
			CString	strSono ;
			strSono.Format( IDS_WORD_Sono , iXPage + 1 ) ;
			strCaption += (LPCTSTR)strSono ;
			strCaption += _T(" ") ;
			pdcdCaption->setText( strCaption ) ;
		}
		//ページ番号も決定
		{
			tstring	strPage = stringOf( iPage + 1) ;
			pdcdPage->setText( strPage ) ;
		}
	}

	LogMsg(_T("CDedAllOperationTable2View::OnPrint()7") ) ;
	// --------------------------------
	//	キャプションとページ番号を描画
	// --------------------------------
	{
		if (getCDiagramEditApp()->getCdPrintPageProp().getPrintHeader() > 0)
		{
			pdcdCaption->DcDraw(pTargetCaption);
		}
		if (getCDiagramEditApp()->getCdPrintPageProp().getPrintFooter() > 0)
		{
			pdcdPage->DcDraw(pTargetPage);
		}
	}
	// --------------------------------
	
	//CView::OnPrint(pDC, pInfo);
}

void CDedAllOperationTable2View::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) 
{

	//	印刷終了後に画面表示が崩れる問題を回避。
	//
	//	このクラスは、印刷中はスクロール位置を
	//	一時的に変更します。
	//	このときに m_pCWndAllOperationTable2 に再描画が発生すると、
	//	画面には一時的に位置の変更されたコンテンツが
	//	描画されるため、画面が崩れます。
	m_pCWndAllOperationTable2->Invalidate() ;
	
	CView::OnEndPrinting(pDC, pInfo);
}

void CDedAllOperationTable2View::OnSetFocus(CWnd* pOldWnd) 
{
	//CView::OnSetFocus(pOldWnd);
	CWnd*	pControl = GetNextDlgTabItem( (CWnd*)NULL , FALSE ) ;
	pControl->SetFocus() ;
	
}


void CDedAllOperationTable2View::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	LogMsg(_T("CDedAllOperationTable2View::OnActivateView(%d,,)") , bActivate ) ;
	
	if ( bActivate && m_bUpdate_All_Requested ){
		OnUpdate_All() ;
	}
	
	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}



void CDedAllOperationTable2View::OnFilePrint()
{
	//	印刷時に、１ページに印刷するダイヤグラムの範囲を保存
	m_sizePrintSize_Dgr = m_pCWndAllOperationTable2->getZone_Dgr().getSize() ;
	m_sizePrintSize_DgrLeft = m_pCWndAllOperationTable2->getZone_Dgr(-1).getSize();
	m_sizePrintSize_DgrCenter = m_pCWndAllOperationTable2->getZone_Dgr(0).getSize();
	m_sizePrintSize_DgrRight = m_pCWndAllOperationTable2->getZone_Dgr(+1).getSize();

	CView::OnFilePrint() ;
}

void CDedAllOperationTable2View::OnFilePrintPreview()
{
	//	印刷時に、１ページに印刷するダイヤグラムの範囲を保存
	m_sizePrintSize_Dgr = m_pCWndAllOperationTable2->getZone_Dgr().getSize() ;
	m_sizePrintSize_DgrLeft = m_pCWndAllOperationTable2->getZone_Dgr(-1).getSize();
	m_sizePrintSize_DgrCenter = m_pCWndAllOperationTable2->getZone_Dgr(0).getSize();
	m_sizePrintSize_DgrRight = m_pCWndAllOperationTable2->getZone_Dgr(+1).getSize();

	CView::OnFilePrintPreview() ;
}
} // namespace ViewAllOperationTable2
