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
/*
// ****************************************************************
//	CRfEditCmd_RessyaSwap.cpp
// $Id: CRfEditCmd_RessyaSwap.cpp$
// ****************************************************************
*/
#include "stdafx.h"
#include <stdlib.h>
#include "NsOu/OuNew.h"
#include "NsMu/CaMui.h"
#include "CRfEditCmd_RessyaSwap.h"

#ifndef _CONSOLE
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

#ifndef min
#define min	__min	 
#endif /*min*/

namespace DedRosenFileData {	namespace EditCmd {

// ****************************************************************
//	CRfEditCmd_RessyaSwap
// ****************************************************************
// ********************************
//	コンストラクタ
// ********************************
CRfEditCmd_RessyaSwap::CRfEditCmd_RessyaSwap(
		int iDiaIndex ,
		ERessyahoukou eERessyahoukou ,
		int iIndexA , 
		int iSizeA , 
		int iIndexB) :
	m_iDiaIndex( iDiaIndex ) ,
	m_ERessyahoukou( eERessyahoukou ) ,
	m_iIndexA( iIndexA ) ,
	m_iSizeA( iSizeA ) ,
	m_iIndexB(iIndexB),
	m_bWaitOperationConnect(false)
{
}



CRfEditCmd_RessyaSwap::‾CRfEditCmd_RessyaSwap()
{
}

// ********************************
///	CRfEditCmd-操作
// ********************************
int CRfEditCmd_RessyaSwap::execute(
	CDedRosenFileData* pCDedRosenFileData)
{
	int iRv = 0;
	// --------------------------------
	CentDedRosen* pCentDedRosen = pCDedRosenFileData->getCentDedRosen();
	CentDedDia* pCentDedDia = NULL;
	if (iRv >= 0) {
		pCentDedDia = pCentDedRosen->getCentDedDiaCont()->getMuPtr()->get(m_iDiaIndex);
		if (pCentDedDia == NULL) {
			iRv = -2;	//	m_iDiaIndex の値が不正です。
		}
	}
	CentDedRessyaCont* pCentDedRessyaCont = NULL;
	if (iRv >= 0) {
		pCentDedRessyaCont = pCentDedDia->getCentDedRessyaCont(m_ERessyahoukou);
		//m_iIndexAがINT_MAXの場合は、末尾を指定したとみなします。その場合は、m_iSizeAも1とみなします。
		if (m_iIndexA == INT_MAX)
		{
			m_iIndexA = pCentDedRessyaCont->size() - 1;
			m_iSizeA = 1;
		}
		//m_iSizeAがINT_MAXの場合は、末尾要素までを選択したとみなします。
		//また、m_iIndexA + m_iSizeAが要素数を超える場合も、末尾要素までを選択したとみなします。
		if (m_iSizeA == INT_MAX)
		{
			m_iSizeA = pCentDedRessyaCont->size() - m_iIndexA;
		}
		else if (m_iIndexA + m_iSizeA > pCentDedRessyaCont->size())
		{
			m_iSizeA = pCentDedRessyaCont->size() - m_iIndexA;
		}
		if (!(0 <= m_iIndexA &&
			m_iIndexA <= pCentDedRessyaCont->size() - m_iSizeA)) {
			iRv = -1;	//	m_iDiaIndex の値が不正です。
		}
		//m_iIndexBがINT_MAXの場合は、末尾を指定したとみなします。
		if (m_iIndexB == INT_MAX)
		{
			m_iIndexB = pCentDedRessyaCont->size() - 1;
		}
	}

	if (iRv >= 0)
	{
		//二つの選択範囲が重複していないかを確かめます。
		if (m_iIndexB >= m_iIndexA &&
			m_iIndexB < m_iIndexA + m_iSizeA)
		{
			iRv = -3;
		}
	}



	// --------------------------------
	//	入れ替え
	// --------------------------------
	if (iRv >= 0)
	{
		if (m_iIndexA < m_iIndexB)
		{
			//後方にあるBを取得し、Tempに入れ、Bを削除する
			CentDedRessya aRessyaTempB = pCentDedRessyaCont->get(m_iIndexB);
			pCentDedRessyaCont->erase(m_iIndexB);

			//前方にあるAを、Bの位置に挿入していく、Aが全て挿入し終わったら、Aを削除する。
			for (int iOffset = 0; iOffset < m_iSizeA; iOffset++)
			{
				pCentDedRessyaCont->insert(pCentDedRessyaCont->get(m_iIndexA + iOffset), m_iIndexB + iOffset);
			}
			pCentDedRessyaCont->erase(m_iIndexA, m_iSizeA);
			//for (int iOffset = 0; iOffset < m_iSizeA; iOffset++)
			//{
			//	pCentDedRessyaCont->erase(m_iIndexA );
			//}

			//TempのBをAの位置に挿入する。
			pCentDedRessyaCont->insert(aRessyaTempB, m_iIndexA);
		}
		else
		{
			//後方にあるAを取得し、Tempに入れ、Aを削除する。
			vector<CentDedRessya> aRessyaTempA;
			for (int iOffset = 0; iOffset < m_iSizeA; iOffset++)
			{
				aRessyaTempA.emplace_back(pCentDedRessyaCont->get(m_iIndexA + iOffset));
			}
			pCentDedRessyaCont->erase(m_iIndexA, m_iSizeA);

			//前方にあるBをAの位置に挿入し、元のBを削除する
			pCentDedRessyaCont->insert(pCentDedRessyaCont->get(m_iIndexB), m_iIndexA);
			pCentDedRessyaCont->erase(m_iIndexB);

			//TempのAをBの位置に挿入する。
			for (int iOffset = 0; iOffset < m_iSizeA; iOffset++)
			{
				pCentDedRessyaCont->insert(aRessyaTempA[iOffset], m_iIndexB + iOffset);
			}
		}

	}

	if (!m_bWaitOperationConnect)
	{
		pCentDedRosen->OperationConnect(m_iDiaIndex);
	}
	else if (m_bWaitOperationConnect)
	{
		pCentDedDia->setWaitOperationUpdate(true);
	}

	return ( iRv ) ;
}

Ou<CRfEditCmd> 
CRfEditCmd_RessyaSwap::createUndoCmd()
{
	if (m_iIndexA < m_iIndexB)
	{
		OuNew<CRfEditCmd>	pCmd(
			new CRfEditCmd_RessyaSwap(
				m_iDiaIndex,
				m_ERessyahoukou,
				m_iIndexB - m_iSizeA + 1,
				m_iSizeA,
				m_iIndexA
			));
		return pCmd;
	}
	else
	{
		OuNew<CRfEditCmd>	pCmd(
			new CRfEditCmd_RessyaSwap(
				m_iDiaIndex,
				m_ERessyahoukou,
				m_iIndexB,
				m_iSizeA,
				m_iIndexA + m_iSizeA - 1
			));
		return pCmd;
	}
	return ( Ou<CRfEditCmd>() ) ;
}

} } // namespace EditCmd namespace DedRosenFileData

