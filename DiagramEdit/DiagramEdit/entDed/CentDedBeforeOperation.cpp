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
/*
// ****************************************************************
//	CentDedBeforeOperation.cpp
//	$Id: CentDedBeforeOperation.cpp  $
// ****************************************************************
*/
/** @file */
#include "stdafx.h"
#include "CentDedRessya.h"
#include "CentDedBeforeOperation.h"
#include "CentDedBeforeOperationCont.h"
#include "CentDedAfterOperation.h"
#include <tchar.h>
#include <algorithm>

namespace entDed{


// ****************************************************************
//	CentDedBeforeOperation
// ****************************************************************


// ********************************
//	コンストラクタ
// ********************************
CentDedBeforeOperation::CentDedBeforeOperation()
{
		set(EBOperation::BOperation_Shunt,
			false,
			INT_MIN,
			INT_MIN,
			CdDedJikoku(),
			CdDedJikoku(),
			vector<tstring>(),
			tstring());
};
CentDedBeforeOperation::CentDedBeforeOperation(
	EBOperation eBOperation,
	bool bBoolData1,
	bool bBoolData2,
	int iIntData1,
	int iIntData2,
	int iIntData3,
	CdDedJikoku JikokuData1,
	CdDedJikoku JikokuData2,
	CdDedJikoku JikokuData3,
	vector<tstring> strOperationNumber1)
{
	set(eBOperation,
		bBoolData1,
		iIntData1,
		iIntData2,
		JikokuData1,
		JikokuData2,
		strOperationNumber1,
		tstring());

	//set(eBOperation,
	//	false,
	//	INT_MIN,
	//	INT_MIN,
	//	CdDedJikoku(),
	//	CdDedJikoku(),
	//	vector<tstring>());
}
CentDedBeforeOperation::CentDedBeforeOperation(
	EBOperation eBOperation,
	int iShuntTrackIndex, 
	CdDedJikoku OperationHatsuJikoku, 
	CdDedJikoku OperationChakuJikoku, 
	bool bIsDisplayChakuJikoku)
{
	set(eBOperation,
		bIsDisplayChakuJikoku,
		iShuntTrackIndex,
		INT_MIN,
		OperationHatsuJikoku,
		OperationChakuJikoku,
		vector<tstring>(),
		tstring());
}
CentDedBeforeOperation::CentDedBeforeOperation(
	EBOperation eBOperation,
	bool bIsConnectToFront, 
	CdDedJikoku ConnectJikoku)
{
	set(eBOperation,
		bIsConnectToFront,
		INT_MIN,
		INT_MIN,
		ConnectJikoku,
		CdDedJikoku(),
		vector<tstring>(),
		tstring());
}
CentDedBeforeOperation::CentDedBeforeOperation(
	EBOperation eBOperation,
	int iReleasePos, 
	int iReleaseIndexCount, 
	CdDedJikoku ReleaseJikoku)
{
	set(eBOperation,
		false,
		iReleasePos,
		iReleaseIndexCount,
		ReleaseJikoku,
		CdDedJikoku(),
		vector<tstring>(),
		tstring());
}
CentDedBeforeOperation::CentDedBeforeOperation(
	EBOperation eBOperation,
	CdDedJikoku OutJikoku, 
	vector<tstring> strOperationNumber,
	tstring strInOutLinkCode)
{
	set(eBOperation,
		false,
		INT_MIN,
		INT_MIN,
		OutJikoku,
		CdDedJikoku(),
		strOperationNumber,
		strInOutLinkCode);
}
CentDedBeforeOperation::CentDedBeforeOperation(
	EBOperation eBOperation,
	int iOuterShihatsuekiIndex, 
	CdDedJikoku OuterShihatsuJikoku, 
	CdDedJikoku ChakuJikoku, 
	vector<tstring> strOperationNumber,
	tstring strInOutLinkCode)
{
	set(eBOperation,
		false,
		iOuterShihatsuekiIndex,
		INT_MIN,
		OuterShihatsuJikoku,
		ChakuJikoku,
		strOperationNumber,
		strInOutLinkCode);
}

CentDedBeforeOperation::CentDedBeforeOperation(
	EBOperation eBOperation,
	CdDedJikoku OriginJikoku,
	//bool bDisableReleaseDisplay,
	vector<tstring> strOperationNumberTemp)
{
	set(eBOperation,
		false,
		-1,
		0,
		OriginJikoku,
		CdDedJikoku(),
		strOperationNumberTemp,
		tstring());
}

CentDedBeforeOperation::CentDedBeforeOperation(
	EBOperation eBOperation,
	vector<tstring> strOperationNumber,
	bool bOperationNumberReverse)
{
	set(eBOperation,
		bOperationNumberReverse,
		INT_MIN,
		INT_MIN,
		CdDedJikoku(),
		CdDedJikoku(),
		strOperationNumber,
		tstring());
}

CentDedBeforeOperation& CentDedBeforeOperation::operator=( const CentDedBeforeOperation& value )
{
	//CentDedBeforeOperationCont* pBeforeOperationCont = dynamic_cast<CentDedBeforeOperationCont*>( getParent() ) ;
	//if ( pBeforeOperationCont != NULL )
	//{
	//	int iResult = pBeforeOperationCont->setable( value , pBeforeOperationCont->getIndex( this ) ) ;
	//	if ( iResult < 0 ){
	//		throw( LException() ) ;
	//	}
	//}
	super::operator=( value ) ; 

	// --------------------------------
	m_eBOperation = value.m_eBOperation;
	m_bBoolData1 = value.m_bBoolData1;
	m_iIntData1 = value.m_iIntData1;
	m_iIntData2 = value.m_iIntData2;
	m_JikokuData1 = value.m_JikokuData1;
	m_JikokuData2 = value.m_JikokuData2;
	m_strOperationNumber1 = value.m_strOperationNumber1;
	m_strInOutLinkCode = value.m_strInOutLinkCode;

	return *this ;
}

	// ********************************
	//@name CParentBase-操作
	// ********************************
void CentDedBeforeOperation::setParent( CParentBase* pParent )
{
	super::setParent( pParent ) ; 
}


	// ********************************
	//@name CentDedBeforeOperation-属性
	// ********************************

//CentDedBeforeOperation& CentDedBeforeOperation::setBOperation(const CentDedBeforeOperation::EBOperation value)
//{
//	m_eBOperation = value;
//
//	m_bBoolData1 = false;
//	m_bBoolData2 = false;
//	m_iIntData1 = INT_MIN;
//	m_iIntData2 = INT_MIN;
//	m_iIntData3 = INT_MIN;
//	m_iIntData4 = INT_MIN;
//	m_JikokuData1.setNull();
//	m_JikokuData2.setNull();
//	m_JikokuData3.setNull();
//	m_strOperationNumber1.clear();
//	m_strOperationNumber2.clear();
//	m_strOperationNumber3.clear();
//	m_CentDedBeforeOperationCont.erase(0, INT_MAX);
//	m_CentDedAfterOperationCont.erase(0, INT_MAX);
//	
//	if (m_eBOperation == BOperation_Connect)
//	{
//		//m_CentDedBeforeOperationCont
//	}
//	else if (m_eBOperation == BOperation_Release)
//	{
//		//m_CentDedAfterOperationCont
//	}
//	return *this ; 
//} ;

void CentDedBeforeOperation::mergeOperationNumber()
{
	if (m_eBOperation == EBOperation::BOperation_Connect)
	{
		if (m_bBoolData1)
		{
			if (m_strOperationNumber3.empty())
			{
				m_strOperationNumber1.clear();
				m_strOperationNumber1.push_back(_T(""));
			}
			else
			{
				m_strOperationNumber1 = m_strOperationNumber3;
			}

			if (m_strOperationNumber2.empty())
			{
				m_strOperationNumber1.push_back(_T(""));
			}
			else
			{
				m_strOperationNumber1.insert(m_strOperationNumber1.end(),
					m_strOperationNumber2.begin(), m_strOperationNumber2.end());
			}
		}
		else
		{
			if (m_strOperationNumber2.empty())
			{
				m_strOperationNumber1.clear();
				m_strOperationNumber1.push_back(_T(""));
			}
			else
			{
				m_strOperationNumber1 = m_strOperationNumber2;
			}

			if (m_strOperationNumber3.empty())
			{
				m_strOperationNumber1.push_back(_T(""));
			}
			else
			{
				m_strOperationNumber1.insert(m_strOperationNumber1.end(),
					m_strOperationNumber3.begin(), m_strOperationNumber3.end());
			}
		}
	}
}

void CentDedBeforeOperation::splitOperationNumber()
{
	if (m_eBOperation == EBOperation::BOperation_Release)
	{
		if (m_strOperationNumber1.empty())
		{
			m_strOperationNumber2.push_back(tstring());
			m_strOperationNumber3.push_back(tstring());
		}
		else if (m_strOperationNumber1.size() == 1)
		{
			m_strOperationNumber2 = m_strOperationNumber1;
			m_strOperationNumber3.push_back(tstring());
		}
		else if (m_iIntData1 == 0)
		{
			int iMainSize = max(1, ((int)m_strOperationNumber1.size() - m_iIntData2));
			m_strOperationNumber2 = vector<tstring>(m_strOperationNumber1.begin(), m_strOperationNumber1.begin() + iMainSize);
			m_strOperationNumber3 = vector<tstring>(m_strOperationNumber1.begin() + iMainSize, m_strOperationNumber1.end());
		}
		else if (m_iIntData1 == 1)
		{
			int iSubSize = min((int)m_strOperationNumber1.size() - 1, m_iIntData2);
			m_strOperationNumber3 = vector<tstring>(m_strOperationNumber1.begin(), m_strOperationNumber1.begin() + iSubSize);
			m_strOperationNumber2 = vector<tstring>(m_strOperationNumber1.begin() + iSubSize, m_strOperationNumber1.end());
		}
		else
		{
			int iMainSize = min((int)m_strOperationNumber1.size() - 1, m_iIntData2);
			m_strOperationNumber2 = vector<tstring>(m_strOperationNumber1.begin(), m_strOperationNumber1.begin() + iMainSize);
			m_strOperationNumber3 = vector<tstring>(m_strOperationNumber1.begin() + iMainSize, m_strOperationNumber1.end());
		}
	}
}

void CentDedBeforeOperation::modifyOperationJikoku(int iSecond)
{
	if (m_eBOperation == EBOperation::BOperation_Shunt)
	{
		m_JikokuData1.addSeconds(iSecond);
		m_JikokuData2.addSeconds(iSecond);
	}
	else if (m_eBOperation == EBOperation::BOperation_Connect)
	{
		m_JikokuData1.addSeconds(iSecond);
		m_CentDedBeforeOperationCont.modifyOperationJikoku(iSecond);
	}
	else if (m_eBOperation == EBOperation::BOperation_Release)
	{
		m_JikokuData1.addSeconds(iSecond);
		m_CentDedAfterOperationCont.modifyOperationJikoku(iSecond);
	}
	else if (m_eBOperation == EBOperation::BOperation_Out)
	{
		m_JikokuData1.addSeconds(iSecond);
	}
	else if (m_eBOperation == EBOperation::BOperation_Outer)
	{
		m_JikokuData1.addSeconds(iSecond);
		m_JikokuData2.addSeconds(iSecond);
	}
	else if (m_eBOperation == EBOperation::BOperation_Junction)
	{
		m_JikokuData1.addSeconds(iSecond);
		//Ver2.06.18 パターンダイヤプレビュー用に、前列車との接続時刻にも補正をかけるように変更
		m_JikokuData2.addSeconds(iSecond);
		m_JikokuData3.addSeconds(iSecond);
	}
}

bool CentDedBeforeOperation::isFirstOperation() const
{
	return (m_eBOperation == EBOperation::BOperation_Out ||
		m_eBOperation == EBOperation::BOperation_Outer ||
		m_eBOperation == EBOperation::BOperation_Junction);
}

void CentDedBeforeOperation::clearOperationNumber()
{
	if (m_eBOperation == EBOperation::BOperation_Connect)
	{
		m_strOperationNumber1.clear();
		m_strOperationNumber2.clear();
		m_strOperationNumber3.clear();
		m_bBoolData2 = false;//増結編成運番割り当て済みチェック
	}
	else if (m_eBOperation == EBOperation::BOperation_Release)
	{
		m_strOperationNumber1.clear();
		m_strOperationNumber2.clear();
		m_strOperationNumber3.clear();
	}
	else if (m_eBOperation == EBOperation::BOperation_Out ||
		m_eBOperation == EBOperation::BOperation_Outer)
	{
		//Ver2.05から
		m_bBoolData1 = false;//割当運番が有効か否か
		m_strOperationNumber2.clear();//割当運番

	}
	else if (m_eBOperation == EBOperation::BOperation_Junction)
	{
		m_strOperationNumber2.clear();//割り当て運番(2.00.05変更)
		m_bBoolData1 = false;//種別変更 (2.00.05変更)(Ver2.05再変更)
		m_bBoolData2 = false;//列車情報省略 Ver(2.05.01～)
		m_iIntData1 = -1;//解結駅Order
		m_JikokuData2.setNull();//前列車接続時刻(在線表あり)
		m_JikokuData3.setNull();//前列車接続時刻(在線表なし)
		m_iIntData1 = 0;//前列車方向(在線表あり)
		m_iIntData2 = 0;//前列車方向(在線表なし)
		m_iIntData3 = -1;//前列車終着駅Order
	}
	else if (m_eBOperation == EBOperation::BOperation_NumberChange)
	{
		m_strOperationNumber2.clear();
		m_strOperationNumber3.clear();//反転後運用番号(Ver2.06.05から)
	}
}

void CentDedBeforeOperation::trimSuffixOperationNumber()
{
	if (m_eBOperation == EBOperation::BOperation_Connect ||
		m_eBOperation == EBOperation::BOperation_Release)
	{
		for (int idx = 0; idx < (int)m_strOperationNumber1.size(); idx++)
		{
			tstring::size_type pos = 0;
			pos = m_strOperationNumber1[idx].find(';');
			if (pos != tstring::npos)
			{
				tstring strTemp = m_strOperationNumber1[idx].substr(0, pos);
				m_strOperationNumber1[idx] = strTemp;
			}
		}
		for (int idx = 0; idx < (int)m_strOperationNumber2.size(); idx++)
		{
			tstring::size_type pos = 0;
			pos = m_strOperationNumber2[idx].find(';');
			if (pos != tstring::npos)
			{
				tstring strTemp = m_strOperationNumber2[idx].substr(0, pos);
				m_strOperationNumber2[idx] = strTemp;
			}
		}
		for (int idx = 0; idx < (int)m_strOperationNumber3.size(); idx++)
		{
			tstring::size_type pos = 0;
			pos = m_strOperationNumber3[idx].find(';');
			if (pos != tstring::npos)
			{
				tstring strTemp = m_strOperationNumber3[idx].substr(0, pos);
				m_strOperationNumber3[idx] = strTemp;
			}
		}
	}
}

void CentDedBeforeOperation::adjustOperation()
{
	if (m_eBOperation == EBOperation::BOperation_Connect)
	{
		if (getCentDedBeforeOperationCont()->size() == 0)
		{
			getCentDedBeforeOperationCont()->insert(
				CentDedBeforeOperation(
					EBOperation::BOperation_Junction,
					CdDedJikoku(),
					vector<tstring>()));
		}
		else
		{
			if (!getCentDedBeforeOperationCont()->get(0).isFirstOperation())
			{
				getCentDedBeforeOperationCont()->insert(
					CentDedBeforeOperation(
						EBOperation::BOperation_Junction,
						CdDedJikoku(),
						vector<tstring>()), 0);
			}
			for (int idx = getCentDedBeforeOperationCont()->size() - 1; idx > 0; idx--)
			{
				if(getCentDedBeforeOperationCont()->get(idx).getBOperation() == EBOperation::BOperation_Connect ||
					getCentDedBeforeOperationCont()->get(idx).getBOperation() == EBOperation::BOperation_Release)
				{
					getCentDedBeforeOperationCont()->getMuPtr()->get(idx)->adjustOperation();
				}
				else if (getCentDedBeforeOperationCont()->get(idx).isFirstOperation())
				{
					getCentDedBeforeOperationCont()->erase(idx);
				}

			}
		}
	}
	else if (m_eBOperation == EBOperation::BOperation_Release)
	{
		if (getCentDedAfterOperationCont()->size() == 0)
		{
			getCentDedAfterOperationCont()->insert(
				CentDedAfterOperation(
					CentDedAfterOperation::EAOperation::AOperation_Junction,
					CdDedJikoku(),
					0));
		}
		else
		{

			if (!getCentDedAfterOperationCont()->get(INT_MAX).isLastOperation())
			{
				getCentDedAfterOperationCont()->insert(
					CentDedAfterOperation(
						CentDedAfterOperation::EAOperation::AOperation_Junction,
						CdDedJikoku(),
						0), INT_MAX);
			}
			for (int idx = getCentDedAfterOperationCont()->size() - 2; idx >= 0; idx--)
			{
				if (getCentDedAfterOperationCont()->get(idx).getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect ||
					getCentDedAfterOperationCont()->get(idx).getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
				{
					getCentDedAfterOperationCont()->getMuPtr()->get(idx)->adjustOperation();
				}
				else if (getCentDedAfterOperationCont()->get(idx).isLastOperation())
				{
					getCentDedAfterOperationCont()->erase(idx);
				}

			}
		}
	}
}

void CentDedBeforeOperation::adjustEkiTrack2(const std::vector<int>& iEkiTrack2Map)
{
	if (m_eBOperation == EBOperation::BOperation_Shunt)
	{
		if (iEkiTrack2Map[m_iIntData1] != m_iIntData1)
		{
			m_iIntData1 = iEkiTrack2Map[m_iIntData1];
		}
	}
	else if (m_eBOperation == EBOperation::BOperation_Connect)
	{
		getCentDedBeforeOperationCont()->adjustEkiTrack2(iEkiTrack2Map);
	}
	else if (m_eBOperation == EBOperation::BOperation_Release)
	{
		getCentDedAfterOperationCont()->adjustEkiTrack2(iEkiTrack2Map);
	}
}

void CentDedBeforeOperation::adjustOuterTerminal(const std::vector<int>& iOuterTerminalEkimeiMap)
{
	if (m_eBOperation == EBOperation::BOperation_Connect)
	{
		getCentDedBeforeOperationCont()->adjustOuterTerminal(iOuterTerminalEkimeiMap);
	}
	else if (m_eBOperation == EBOperation::BOperation_Release)
	{
		getCentDedAfterOperationCont()->adjustOuterTerminal(iOuterTerminalEkimeiMap);
	}
	else if (m_eBOperation == EBOperation::BOperation_Outer)
	{
		if (iOuterTerminalEkimeiMap[m_iIntData1] != m_iIntData1)
		{
			m_iIntData1 = iOuterTerminalEkimeiMap[m_iIntData1];
		}
	}
}

void CentDedBeforeOperation::fixOperation(const int iEkiTrackCount, const int iOuterTerminalCount)
{
	if (m_eBOperation == EBOperation::BOperation_Shunt)
	{
		if (m_iIntData1 >= iEkiTrackCount)
		{
			m_iIntData1 = 0;
		}
	}
	else if (m_eBOperation == EBOperation::BOperation_Connect)
	{
		getCentDedBeforeOperationCont()->fixOperation(iEkiTrackCount, iOuterTerminalCount);
	}
	else if (m_eBOperation == EBOperation::BOperation_Release)
	{
		getCentDedAfterOperationCont()->fixOperation(iEkiTrackCount, iOuterTerminalCount);
	}
	else if (m_eBOperation == EBOperation::BOperation_Outer)
	{
		if (iOuterTerminalCount == 0)
		{
			set(CentDedBeforeOperation::EBOperation::BOperation_Out,
				false,
				INT_MIN,
				INT_MIN,
				m_JikokuData2,
				CdDedJikoku(),
				m_strOperationNumber1,
				m_strInOutLinkCode);
		}
		else if (m_iIntData1 >= iOuterTerminalCount)
		{
			m_iIntData1 = 0;
		}
	}
}

int CentDedBeforeOperation::isExistRessyaOfEkiTrack2(int iEkiTrack2Index)
{
	if (m_eBOperation == EBOperation::BOperation_Shunt)
	{
		if (iEkiTrack2Index == m_iIntData1)
		{
			return 1;
		}
	}
	else if (m_eBOperation == EBOperation::BOperation_Connect)
	{
		return getCentDedBeforeOperationCont()->isExistRessyaOfEkiTrack2(iEkiTrack2Index);
	}
	else if (m_eBOperation == EBOperation::BOperation_Release)
	{
		return getCentDedAfterOperationCont()->isExistRessyaOfEkiTrack2(iEkiTrack2Index);
	}
	return 0;
}

int CentDedBeforeOperation::isExistRessyaOfOuterTerminal(int iOuterTerminalIndex)
{
	if (m_eBOperation == EBOperation::BOperation_Connect)
	{
		return getCentDedBeforeOperationCont()->isExistRessyaOfOuterTerminal(iOuterTerminalIndex);
	}
	else if (m_eBOperation == EBOperation::BOperation_Release)
	{
		return getCentDedAfterOperationCont()->isExistRessyaOfOuterTerminal(iOuterTerminalIndex);
	}
	else if (m_eBOperation == EBOperation::BOperation_Outer)
	{
		if (iOuterTerminalIndex == m_iIntData1)
		{
			return 1;
		}
	}
	return 0;
}

CentDedBeforeOperation& CentDedBeforeOperation::set(
	EBOperation eBOperation,
	bool bBoolData1,
	int iIntData1,
	int iIntData2,
	CdDedJikoku JikokuData1,
	CdDedJikoku JikokuData2,
	vector<tstring> strOperationNumber1,
	tstring strInOutLinkCode)
{
	m_eBOperation = eBOperation;
	m_bBoolData1 = bBoolData1;
	m_bBoolData2 = false;
	m_iIntData1 = iIntData1;
	m_iIntData2 = iIntData2;
	m_iIntData3 = -1;
	m_JikokuData1 = JikokuData1;
	m_JikokuData2 = JikokuData2;
	m_JikokuData3.setNull();
	m_strOperationNumber1 = strOperationNumber1;
	m_strOperationNumber2.clear();
	m_strOperationNumber3.clear();
	m_strInOutLinkCode = strInOutLinkCode;
	
	m_CentDedBeforeOperationCont.erase(0, INT_MAX);
	if (m_eBOperation == EBOperation::BOperation_Connect)
	{
		m_CentDedBeforeOperationCont.insert(
			CentDedBeforeOperation(
				EBOperation::BOperation_Junction,
				CdDedJikoku(),
				vector<tstring>()));

	}
	m_CentDedAfterOperationCont.erase(0, INT_MAX);
	if (m_eBOperation == EBOperation::BOperation_Release)
	{
		m_CentDedAfterOperationCont.insert(
			CentDedAfterOperation(
				CentDedAfterOperation::EAOperation::AOperation_Junction,
				CdDedJikoku(),
				false));

	}
	return ( *this ) ;
};

} //namespace entDed
