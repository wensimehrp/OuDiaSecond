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
//	CRfEditCmd_Dia.cpp
// $Id: CRfEditCmd_Dia.cpp 378 2016-11-16 21:10:54Z okm $
// ****************************************************************
*/
#include "stdafx.h"
#include "NsOu/OuNew.h"
#include "NsMu/CaMui.h"
#include "CRfEditCmd_Dia.h"

#ifndef _CONSOLE
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

namespace DedRosenFileData{ namespace EditCmd{

// ****************************************************************
//	CRfEditCmd_Dia
// ****************************************************************

// ********************************
//	コンストラクタ
// ********************************
CRfEditCmd_Dia::CRfEditCmd_Dia( 
		int iIndexDst ,
		int iSizeDst ,
		const CentDedDiaCont& aCentDedDiaContSrc ,
		bool bIsSwap) : 
		m_iIndexDst( iIndexDst ) ,
		m_iSizeDst( iSizeDst ) ,
		m_CentDedDiaContSrc( aCentDedDiaContSrc ) ,
		m_pCentDedDiaContOld( NULL ) ,
		m_bIsSwap(bIsSwap)
{
};
CRfEditCmd_Dia::~CRfEditCmd_Dia()
{
	if ( m_pCentDedDiaContOld != NULL ){
		delete m_pCentDedDiaContOld ;
		m_pCentDedDiaContOld = NULL ;
	}
}

// ********************************
//@name	CRfEditCmd-操作
// ********************************
int CRfEditCmd_Dia::execute( 
		CDedRosenFileData* pCDedRosenFileData ) 
{
	int iRv = 0 ;
	// --------------------------------
	CentDedRosen*	pCentDedRosen = pCDedRosenFileData->getCentDedRosen() ;
	CentDedDiaCont*	pCentDedDiaCont = pCentDedRosen->getCentDedDiaCont() ;
	if ( iRv >= 0 ){
		if ( m_iIndexDst == INT_MAX && m_iSizeDst == INT_MAX ){
			iRv = -1 ;	//	m_iDiaIndex の値が不正です。
		}	else	{
			if ( m_iIndexDst == INT_MAX ){
				m_iIndexDst = pCentDedDiaCont->size()  - m_iSizeDst ;
			}	else if ( m_iSizeDst == INT_MAX ){
				m_iSizeDst = pCentDedDiaCont->size() - m_iIndexDst ;
			}
			if ( !( 0 <= m_iIndexDst && 
				m_iIndexDst + m_iSizeDst<= pCentDedDiaCont->size() ) ){
				iRv = -1 ;	//	m_iDiaIndex の値が不正です。
			}
		}
	}
	// --------------------------------
	//	削除データを保存
	// --------------------------------
	if ( iRv >= 0 ){
		if ( m_pCentDedDiaContOld != NULL ){
			delete m_pCentDedDiaContOld ;
			m_pCentDedDiaContOld = NULL ;
		}
		//m_pCentDedDiaContOld = new CentDedDiaCont( 
		//	pCentDedRosen->getCentDedEkiCont()->size() , 
		//	pCentDedRosen->getCentDedRessyasyubetsuCont()->size() ) ;
		m_pCentDedDiaContOld = new CentDedDiaCont() ;

		CaMui< CentDedDia >	aCaCont( m_pCentDedDiaContOld ) ;
		aCaCont.insert( 
			pCentDedDiaCont , 
			m_iIndexDst , 
			m_iSizeDst , 0 ) ;
	}
	// --------------------------------
	//	既存データの削除
	// --------------------------------
	if ( iRv >= 0 ){
		int iResult = pCentDedDiaCont->erase( m_iIndexDst , m_iSizeDst ) ;
		if ( iResult < 0 ){
			iRv = -11 ;	//	要素の削除に失敗しました。
		}
	}
	// --------------------------------
	//	新規データを追加
	// --------------------------------
	if ( iRv >= 0 ){
		CaMui<CentDedDia>	aCaCont( pCentDedDiaCont ) ;
		int iResult = aCaCont.insert( 
			&m_CentDedDiaContSrc , 
			0 , 
			m_CentDedDiaContSrc.size() , 
			m_iIndexDst ) ;
		if ( iResult < 0 ){
			iRv = -12 ;	//	要素の追加に失敗しました。
		}

	}

	// --------------------------------
	//	基準運転時分取得ダイヤインデクスの変更
	// --------------------------------
	if (iRv >= 0) {
		if (m_bIsSwap && m_iSizeDst == m_CentDedDiaContSrc.size())
		{
			/**
				入れ替えの場合、取得ダイヤインデクスが入れ替え範囲(iIndexDst～iIndexDst+iSizeDst-1)の先頭か末尾
				(実際には、入れ替え範囲(iSizeDst)は2なので、範囲のどちらか)の場合、先頭なら末尾位置に、末尾なら先頭位置のインデクスに変更します。
				なお、m_bIsSwapがTrueでも、削除数と追加数が食い違う場合は、他の場合と同様に処理します。
			*/
			int iKijunDiaIndex = pCentDedRosen->getKijunDiaIndex();
			if (iKijunDiaIndex == m_iIndexDst)
			{
				pCentDedRosen->setKijunDiaIndex(m_iIndexDst + m_iSizeDst - 1);
			}
			else if (iKijunDiaIndex == (m_iIndexDst + m_iSizeDst - 1))
			{
				pCentDedRosen->setKijunDiaIndex(m_iIndexDst);
			}
		}
		else
		{
			/**
				入れ替え以外の場合、取得ダイヤインデクスがm_iIndexDst以上の場合は、補正を行います。
			*/
			int iKijunDiaIndex = pCentDedRosen->getKijunDiaIndex();
			if (m_iSizeDst > m_CentDedDiaContSrc.size())
			{
				//削除側が大きい場合、削除された範囲の内、追加された数よりも多い部分に取得ダイヤインデクスがある場合は、取得ダイヤインデクスを0(先頭のダイヤ)にします。
				//削除された範囲よりも後ろに取得ダイヤインデクスがある場合は、取得ダイヤインデクスを削除数-追加数だけ減算します。
				if (iKijunDiaIndex >= m_iIndexDst + m_CentDedDiaContSrc.size() && iKijunDiaIndex < m_iIndexDst + m_iSizeDst)
				{
					pCentDedRosen->setKijunDiaIndex(0);
				}
				else if (iKijunDiaIndex >= m_iIndexDst + m_iSizeDst)
				{
					pCentDedRosen->setKijunDiaIndex(iKijunDiaIndex - m_iSizeDst + m_CentDedDiaContSrc.size());
				}
			}
			else if (m_iSizeDst < m_CentDedDiaContSrc.size())
			{
				//追加側が大きい場合、削除された範囲よりも後に取得ダイヤインデクスがある場合は、取得ダイヤインデクスを追加数-削除数だけ加算します。
				//ただし、元のダイヤが空の場合は除きます。
				if (iKijunDiaIndex >= m_iIndexDst + m_iSizeDst && pCentDedDiaCont->size() == 0)
				{
					pCentDedRosen->setKijunDiaIndex(iKijunDiaIndex + m_CentDedDiaContSrc.size() - m_iSizeDst);
				}
			}
		}
	}
	//新規作成・削除・上下入換だけなので、運用探索する必要は無し
//	for (int idx = 0; idx < m_CentDedDiaContSrc->size(); idx++)
//	{
//		pCentDedRosen->OperationConnect(idx + m_iDiaIndex);
//	}

	return ( iRv ) ;
}
Ou<CRfEditCmd> CRfEditCmd_Dia::createUndoCmd()
{
	if ( m_pCentDedDiaContOld != NULL ){
		OuNew<CRfEditCmd>	pCmd( 
			new CRfEditCmd_Dia( 
				m_iIndexDst , 
				m_CentDedDiaContSrc.size() , 
				*m_pCentDedDiaContOld ,
				m_bIsSwap) ) ;
		delete m_pCentDedDiaContOld ;
		m_pCentDedDiaContOld = NULL ;
		return pCmd ;
	}
	return ( Ou<CRfEditCmd>() ) ;
}
} } // namespace EditCmd namespace DedRosenFileData
