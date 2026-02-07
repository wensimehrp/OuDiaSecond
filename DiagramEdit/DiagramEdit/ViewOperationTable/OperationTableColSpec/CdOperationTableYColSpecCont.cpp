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
// ****************************************************************
// $Id: CdOperationTableYColSpecCont.cpp 
// ****************************************************************
//#pragma once
#include "stdafx.h"
#include "CdOperationTableYColSpecCont.h"

namespace ViewOperationTable { namespace OperationTableColSpec{

/// ヘッダ列の数
const int HEADER_COUNT = 1;

	// ********************************
	//	コンストラクタ
	// ********************************
CdOperationTableYColSpecCont::CdOperationTableYColSpecCont(

	int iRowCount,
	bool bDisplayExtensionOperationTable)
	//: m_iColumnNumber_Ekijikoku_begin( 0 ) 
{
	scan(iRowCount,
		bDisplayExtensionOperationTable) ;
}

CdOperationTableYColSpecCont::CdOperationTableYColSpecCont( )
	:m_iRowCount(0),
	m_bDisplayExtensionOperationTable(false)
{
}

	// ********************************
	//@name CdYColSpec-関連
	// ********************************

	// ********************************
	//@name 属性
	// ********************************
bool CdOperationTableYColSpecCont::getDisplayExtensionOperationTable()const
{
	return m_bDisplayExtensionOperationTable;
}
int CdOperationTableYColSpecCont::getRessyaCount()const
{
	return m_iRowCount;
}

	// ********************************
	//@name CdYColSpec-操作
	// ********************************
void CdOperationTableYColSpecCont::scan(
	int iRowCount,
	bool bDisplayExtensionOperationTable)
{
	// --------------------------------
	//	既存データの削除
	 --------------------------------
	//clear() ;
	m_iRowCount = iRowCount;
	m_bDisplayExtensionOperationTable = bDisplayExtensionOperationTable;

	// --------------------------------
	//	『列番号-表示内容』の対応表を構築
	// --------------------------------
	m_contColumnSpec.insert(
		CdOperationTableYColSpec::EColumnType::ColumnType_Head);
	for (int idx = 0; idx < m_iRowCount; idx++)
	{
		m_contColumnSpec.insert(CdOperationTableYColSpec(
			CdOperationTableYColSpec::EColumnType::ColumnType_Ressya, idx));
		if (bDisplayExtensionOperationTable)
		{
			m_contColumnSpec.insert(CdOperationTableYColSpec(
				CdOperationTableYColSpec::EColumnType::ColumnType_Line, idx));
			m_contColumnSpec.insert(CdOperationTableYColSpec(
				CdOperationTableYColSpec::EColumnType::ColumnType_RessyaHatsu, idx));
		}

	}
}



int CdOperationTableYColSpecCont::size()
{
	//if (getDisplayExtensionOperationTable())
	//{
	//	return (m_iRowCount*2) + HEADER_COUNT;
	//}
	//return m_iRowCount + HEADER_COUNT;
	return m_contColumnSpec.size();
}

CdOperationTableYColSpec CdOperationTableYColSpecCont::ColumnNumberToSpec( int iYColumnNumber )
{
	CdOperationTableYColSpec	aSpec;

	//	ヘッダ列
	//if (iYColumnNumber == 0)
	//{
	//	aSpec.set(CdOperationTableYColSpec::EColumnType::ColumnType_Head, -1);
	//}
	////	列車列
	//else if (getDisplayExtensionOperationTable())
	//{
	//	if (HEADER_COUNT <= iYColumnNumber &&
	//		iYColumnNumber < HEADER_COUNT + (m_iRowCount * 2))
	//	{
	//		if (iYColumnNumber % 2 == 1)
	//		{
	//			aSpec.set(CdOperationTableYColSpec::EColumnType::ColumnType_Ressya,
	//				floor(iYColumnNumber / 2));
	//		}
	//		else
	//		{
	//			aSpec.set(CdOperationTableYColSpec::EColumnType::ColumnType_RessyaHatsu,
	//				(iYColumnNumber / 2) - HEADER_COUNT);
	//		}
	//	}
	//}
	//else if (HEADER_COUNT <= iYColumnNumber &&
	//	iYColumnNumber < HEADER_COUNT + m_iRowCount)
	//{
	//	aSpec.set(CdOperationTableYColSpec::EColumnType::ColumnType_Ressya,
	//		iYColumnNumber - HEADER_COUNT);
	//}

	if (0 <= iYColumnNumber
		&& iYColumnNumber < m_contColumnSpec.size())
	{
		aSpec = m_contColumnSpec.get(iYColumnNumber);
		//aSpec.set((CdOperationTableXColSpec::EColumnType) iColumnNumber);
	}
	return aSpec;

}




int CdOperationTableYColSpecCont::ColumnNumberFromSpec(
		const CdOperationTableYColSpec& aCdYColumnSpec  ) 
{
	//int iColumnNumber = -1;
	////	ヘッダ列 
	//if (aCdYColumnSpec.getColumnType() == CdOperationTableYColSpec::EColumnType::ColumnType_Head)
	//{
	//	iColumnNumber = 0;
	//}
	////	列車種別列 
	//else if (aCdYColumnSpec.getColumnType() ==
	//	CdOperationTableYColSpec::EColumnType::ColumnType_Ressya)
	//{
	//	if (getDisplayExtensionOperationTable())
	//	{
	//		iColumnNumber = HEADER_COUNT + (aCdYColumnSpec.getOperationTableContentIndex()*2);
	//	}
	//	else
	//	{
	//		iColumnNumber = HEADER_COUNT + aCdYColumnSpec.getOperationTableContentIndex();
	//	}
	//}
	//else if (aCdYColumnSpec.getColumnType() ==
	//	CdOperationTableYColSpec::EColumnType::ColumnType_RessyaHatsu &&
	//	getDisplayExtensionOperationTable())
	//{
	//	iColumnNumber = (HEADER_COUNT + aCdYColumnSpec.getOperationTableContentIndex()) * 2;
	//}

	//return iColumnNumber;
	int iRv = -1;

	for (int iColumnNumber = 0;
		iRv == -1 && iColumnNumber < m_contColumnSpec.size();
		iColumnNumber++)
	{
		if (m_contColumnSpec.get(iColumnNumber) == aCdYColumnSpec)
		{
			iRv = iColumnNumber;
		}
	}


	return iRv;
}

void CdOperationTableYColSpecCont::clear()
{
	m_bDisplayExtensionOperationTable = false;
	m_iRowCount = 0;
	m_contColumnSpec.erase(0, INT_MAX);
}
} } //namespace OperationTableColSpec namespace ViewOperationTable

