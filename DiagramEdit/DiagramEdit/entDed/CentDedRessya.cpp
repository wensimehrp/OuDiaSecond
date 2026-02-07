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
//	CentDedRessya.cpp
// ****************************************************************
*/
#include "stdafx.h"

#include "CentDedRosen.h"
#include "CentDedRessya.h"
#include "CentDedRessyaCont.h"
#include "CentDedRessyasyubetsuCont.h"
#include "CdDedJikan.h"
//#include <ctype.h>
#include <tchar.h>
#include "..\diagramedit.h"
#include "NsOu/dynamic_castOu.h"

#ifdef _MFC_VER 
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

namespace entDed{



// ****************************************************************
//	CentDedRessya::CXEkiJikokuCont
// ****************************************************************
CentDedRessya* CentDedRessya::CXEkiJikokuCont::getRessya() 
{
	CentDedRessya* pOuter = (CentDedRessya*)( ((char*)this) - offsetof( CentDedRessya , m_CentDedEkiJikokuCont ) ) ;
	return pOuter ;
}

const CentDedRessya* CentDedRessya::CXEkiJikokuCont::getRessya()const
{
	const CentDedRessya* pOuter = (const CentDedRessya*)( ((char*)this) - offsetof( CentDedRessya , m_CentDedEkiJikokuCont ) ) ;
	return pOuter ;
}
// ****************************************************************

// ****************************************************************
//	CentDedRessya
// ****************************************************************


// ********************************
//	コンストラクタ
// ********************************
CentDedRessya::CentDedRessya( 
		int iEkiJikokuCount ,
		ERessyahoukou	eRessyahoukou ) :
	m_bIsNull( true ) ,
	m_eRessyahoukou( eRessyahoukou ) ,
	m_iRessyasyubetsuIndex( 0 ),
	m_bIsCanceled(false)
{
	while ( (int)m_CentDedEkiJikokuCont.size() < iEkiJikokuCount ){
		m_CentDedEkiJikokuCont.insert( CentDedEkiJikoku() ) ;
	}
}

CentDedRessya& CentDedRessya::operator=( const CentDedRessya& value )
{
	super::operator=( value ) ; 
	// --------------------------------
	CentDedRessyaCont* pRessyaCont = dynamic_cast<CentDedRessyaCont*>( getParent() ) ;

	m_bIsNull = value.m_bIsNull ;

	//this が列車コンテナの一部である場合、『列車方向』 ( m_eRessyahoukou ) は変更しません。
	if ( pRessyaCont == NULL )
	{
		m_eRessyahoukou = value.m_eRessyahoukou ;
	}

	m_iRessyasyubetsuIndex = value.m_iRessyasyubetsuIndex ;
	m_strRessyabangou = value.m_strRessyabangou ;
	m_strRessyamei = value.m_strRessyamei;
	m_strGousuu = value.m_strGousuu;
	m_strBikou = value.m_strBikou;
	m_CentDedEkiJikokuCont =  value.m_CentDedEkiJikokuCont ;
	m_bIsCanceled = value.m_bIsCanceled;
	return *this ;
}

	// ********************************
	//@name CParentBase-操作
	// ********************************
void CentDedRessya::setParent( CParentBase* pParent )
{
	super::setParent( pParent ) ; 
	adjust() ;
}



	// ********************************
	//@name CentDedRessya-属性
	// ********************************
bool CentDedRessya::isNull()const 
{
	return ( m_bIsNull ) ;
}
CentDedRessya& CentDedRessya::setIsNull( bool value )
{
	m_bIsNull = value ;
	if ( value )
	{
		clear() ;
	}
	return *this ;
}

ERessyahoukou	CentDedRessya::getRessyahoukou()const
{
		return m_eRessyahoukou ;
};

int	CentDedRessya::getRessyasyubetsuIndex()const
{
		return m_iRessyasyubetsuIndex ; 
};
CentDedRessya& CentDedRessya::setRessyasyubetsuIndex( int value )
{
	//	列車が路線(CentDedRosen)の一部である場合は
	//	Rosenへのポインタを取得します。
	CentDedRosen* pRosen = NULL ;
	{
		CentDedRessyaCont* pRessyaCont = dynamic_cast<CentDedRessyaCont*>( getParent() ) ;
		if ( pRessyaCont != NULL ){	pRosen = pRessyaCont->getRosen() ;}
	}

	//△setRessyasyubetsuIndex: 列車が路線(CentDedRosen)の一部である場合で、
	//	列車種別Indexが列車種別コンテナ CentDedRessyasyubetsuCont に
	//	対応していない場合はエラー。
	if ( pRosen != NULL )
	{
		CentDedRessyasyubetsuCont* pRessyasyubetsuCont = pRosen->getCentDedRessyasyubetsuCont() ;
		if ( !( 0 <= value && value < pRessyasyubetsuCont->size() ) )
		{
			throw LException() ;
		}
	}
	// --------------------------------
	//	属性の更新
	m_bIsNull = false ;
	m_iRessyasyubetsuIndex = value ; 
	return *this ;
};
	
	// ********************************
	//@name 包含-CentDedEkiJikoku
	// ********************************

int CentDedRessya::getCentDedEkiJikokuCount()const 
{
	return ( (int)m_CentDedEkiJikokuCont.size() ) ;
}

CentDedEkiJikoku CentDedRessya::
getCentDedEkiJikoku( int iEkiOrder )const 
{
	CentDedEkiJikoku	aCentDedEkiJikoku ;
	if ( iEkiOrder == INT_MAX ){
		iEkiOrder = (int)m_CentDedEkiJikokuCont.size() - 1 ;
	}
	if ( ( 0 <= iEkiOrder && iEkiOrder < (int)m_CentDedEkiJikokuCont.size() ) ){

		aCentDedEkiJikoku = m_CentDedEkiJikokuCont.get( iEkiOrder ) ;
	}
	return ( aCentDedEkiJikoku ) ;
}


CentDedRessya& CentDedRessya::
setCentDedEkiJikoku( int iEkiOrder , const CentDedEkiJikoku& value ) 
{
	if ( iEkiOrder == INT_MAX ){
		iEkiOrder = (int)m_CentDedEkiJikokuCont.size() - 1 ;
	}
	if ( 0 <= iEkiOrder && iEkiOrder < (int)m_CentDedEkiJikokuCont.size() ){
		m_bIsNull = false ;
		m_CentDedEkiJikokuCont.set( value , iEkiOrder ) ;
	}
	return *this ;
}
	// ********************************
	//@name 『駅Order』単位の操作
	// ********************************
int CentDedRessya::EkiIndexOfEkiOrder( int iEkiOrder )const  
{
	int iRv = iEkiOrder ;
	if ( m_eRessyahoukou == Ressyahoukou_Nobori ){
		iRv = (int)m_CentDedEkiJikokuCont.size() - 1 - iEkiOrder ;
	}
	return ( iRv ) ;
}

int CentDedRessya::EkiOrderOfEkiIndex( int iEkiIndex ) const
{
	int iRv = iEkiIndex ;
	if ( m_eRessyahoukou == Ressyahoukou_Nobori ){
		iRv = (int)m_CentDedEkiJikokuCont.size() - 1 - iEkiIndex ;
	}
	return ( iRv ) ;
}


CentDedRessya& CentDedRessya::modifyCentDedEkiJikoku( 
	int iEkiOrder , 
	const CentDedEkiJikoku& value ) 
{
	if ( iEkiOrder == INT_MAX ){
		iEkiOrder = (int)m_CentDedEkiJikokuCont.size() - 1 ;
	}
	if ( 0 <= iEkiOrder && iEkiOrder < (int)m_CentDedEkiJikokuCont.size() ){
		m_bIsNull = false ;
	
		//	変更前の時刻を保存
		CdDedJikoku jikokuChakujikokuPrev = 
			m_CentDedEkiJikokuCont.getMuPtr()->get( iEkiOrder )->getChakujikoku() ;
		CdDedJikoku jikokuHatsujikokuPrev = 
			m_CentDedEkiJikokuCont.getMuPtr()->get( iEkiOrder )->getHatsujikoku() ;

		CdDedJikoku jikokuChakujikoku = value.getChakujikoku() ;
		CdDedJikoku jikokuHatsujikoku =  value.getHatsujikoku() ;
		
		//	駅時刻の変更
		m_CentDedEkiJikokuCont.getMuPtr()->get( iEkiOrder )->set( 
			value.getEkiatsukai() , value.getChakujikoku() , value.getHatsujikoku() , value.getRessyaTrackIndex()) ;


		//	その後の時刻の繰上げ・繰下げ
		if ( !jikokuHatsujikoku.isNull() && !jikokuHatsujikokuPrev.isNull() )
		{
			//	発時刻が変更前・変更後も入力されている場合は、
			//	発時刻の入力前・入力後の差分を求めて、
			//　その駅の前後作業と、
			//	次の駅以降から繰下げを行います。
			CdDedJikan	aCdDedJikan = jikokuHatsujikoku.subJikoku( 
					jikokuHatsujikokuPrev ) ;

			getCentDedEkiJikokuCont()->getMuPtr()->get(iEkiOrder)
				->getCentDedAfterOperationCont()->modifyOperationJikoku(aCdDedJikan.getTotalSeconds());
			if (getValidSihatsuEki() == iEkiOrder)
			{
				getCentDedEkiJikokuCont()->getMuPtr()->get(iEkiOrder)
					->getCentDedBeforeOperationCont()->modifyOperationJikoku(aCdDedJikan.getTotalSeconds());
			}
			else if(!jikokuChakujikoku.isNull() && !jikokuChakujikokuPrev.isNull())
			{
				CdDedJikan	aCdDedJikanChaku = jikokuChakujikoku.subJikoku(
					jikokuChakujikokuPrev);

				getCentDedEkiJikokuCont()->getMuPtr()->get(iEkiOrder)
					->getCentDedBeforeOperationCont()->modifyOperationJikoku(aCdDedJikanChaku.getTotalSeconds());
			}
			modifyRessyaJikoku( 
				aCdDedJikan , 
				CdDedJikokuOrder( iEkiOrder + 1 , CdDedJikokuOrder::EkiJikokuItem_Chaku ) ) ;
		}
		else if ( !jikokuChakujikoku.isNull() && !jikokuChakujikokuPrev.isNull() )
		{
			//	発時刻による繰上げ・繰下げはできないが、
			//	着時刻が変更前・変更後も入力されている場合は、
			//	着時刻の差分を求めて、
			//  その駅の前作業と
			//	その駅の発時刻以降から繰下げを行います。
			CdDedJikan	aCdDedJikan = jikokuChakujikoku.subJikoku( 
					jikokuChakujikokuPrev ) ;

			getCentDedEkiJikokuCont()->getMuPtr()->get(iEkiOrder)
				->getCentDedBeforeOperationCont()->modifyOperationJikoku(aCdDedJikan.getTotalSeconds());

			modifyRessyaJikoku(
				aCdDedJikan , 
				CdDedJikokuOrder( iEkiOrder , CdDedJikokuOrder::EkiJikokuItem_Hatsu ) ) ;
		}
	}
	return *this ;
}

int CentDedRessya::getSihatsuEki() const
{
	int	iRv = -1 ;
	// --------------------------------
	int iEkiOrder = 0 ;
	for ( iEkiOrder = 0 ; 
			iRv == -1 && 
			iEkiOrder < (int)m_CentDedEkiJikokuCont.size() ; 
			iEkiOrder ++ ){
		const CentDedEkiJikoku*	pCentDedEkiJikoku = 
			m_CentDedEkiJikokuCont.getMuPtr()->get( iEkiOrder ) ;
		if ( pCentDedEkiJikoku->getEkiatsukai() != 
				CentDedEkiJikoku::Ekiatsukai_None ){
			iRv = iEkiOrder ;
		}
	}
	// --------------------------------
	return ( iRv ) ;
}

int CentDedRessya::setSihatsuEki( int iEkiOrder ) 
{
	int	iRv = 0 ;

	if ( iRv >= 0 ){
		if ( !( 0 <= iEkiOrder && iEkiOrder < (int)m_CentDedEkiJikokuCont.size() ) ){
			iRv = -1 ;	//	『駅Index』が不正です。
		}
	}

	// --------------------------------
	if (iRv >= 0) 
	{
		int iEkiOrderCurr = 0;
		for (iEkiOrderCurr = 0;
			iEkiOrderCurr < iEkiOrder;
			iEkiOrderCurr++) {
			CentDedEkiJikoku*	pCentDedEkiJikoku =
				m_CentDedEkiJikokuCont.getMuPtr()->get(iEkiOrderCurr);
			pCentDedEkiJikoku->setEkiatsukai(CentDedEkiJikoku::Ekiatsukai_None);
		}

		CentDedEkiJikoku*	pCentDedEkiJikoku = 
			m_CentDedEkiJikokuCont.getMuPtr()->get( iEkiOrderCurr ) ;
		if ( !pCentDedEkiJikoku->getHatsujikoku().isNull() ){
			//	発時刻が設定されている場合だけ
			//	着時刻を消去します。
			//	（発時刻が設定されていない場合に着時刻を
			//	消去してしまうと、その駅の駅時刻は
			//	運行なし Ekiatsukai_None になってしまうためです）
			pCentDedEkiJikoku->setChakujikoku( CdDedJikoku() ) ;
	
		}
	}
	if (iRv >= 0)
	{
		adjustOperation();
	}
	// --------------------------------
	return ( iRv ) ;
}

int CentDedRessya::getSyuuchakuEki() const
{
	int	iRv = -1 ;
	// --------------------------------
	int iEkiOrder = 0 ;
	for ( iEkiOrder = (int)m_CentDedEkiJikokuCont.size() - 1 ; 
			iRv == -1 && 
			iEkiOrder >= 0 ; 
			iEkiOrder -- )
	{
		const CentDedEkiJikoku*	pCentDedEkiJikoku = 
			m_CentDedEkiJikokuCont.getMuPtr()->get( iEkiOrder ) ;
		if ( pCentDedEkiJikoku->getEkiatsukai() != 
				CentDedEkiJikoku::Ekiatsukai_None )
		{
			iRv = iEkiOrder ;
		}
	}
	// --------------------------------
	return ( iRv ) ;
}

int CentDedRessya::setSyuuchakuEki( int iEkiOrder ) 
{
	int	iRv = 0 ;

	if ( iRv >= 0 ){
		if ( !( 0 <= iEkiOrder && iEkiOrder < (int)m_CentDedEkiJikokuCont.size() ) ){
			iRv = -1 ;	//	『駅Index』が不正です。
		}
	}

	// --------------------------------
	if (iRv >= 0)
	{
		CentDedEkiJikoku*	pCentDedEkiJikoku = 
			m_CentDedEkiJikokuCont.getMuPtr()->get( iEkiOrder ) ;
		if ( !pCentDedEkiJikoku->getChakujikoku().isNull() ){
			//	着時刻が設定されている場合だけ
			//	発時刻を消去します。
			//	（着時刻が設定されていない場合に発時刻を
			//	消去してしまうと、その駅の駅時刻は
			//	運行なし Ekiatsukai_None になってしまうためです）
			pCentDedEkiJikoku->setHatsujikoku( CdDedJikoku() ) ;

		}
	}
	if (iRv >= 0)
	{
		int iEkiOrderCurr = 0;
		for (iEkiOrderCurr = iEkiOrder + 1;
			iEkiOrderCurr < (int)m_CentDedEkiJikokuCont.size();
			iEkiOrderCurr++) {
			CentDedEkiJikoku*	pCentDedEkiJikoku =
				m_CentDedEkiJikokuCont.getMuPtr()->get(iEkiOrderCurr);
			pCentDedEkiJikoku->setEkiatsukai(CentDedEkiJikoku::Ekiatsukai_None);
		}
	}
	if (iRv >= 0)
	{
		adjustOperation();
	}
	// --------------------------------
	return ( iRv ) ;
}

bool CentDedRessya::isRunBetweenNextEki( int iEkiOrder )const 
{
	bool bRv = false ;
	if ( !( 0 <= iEkiOrder && iEkiOrder < (int)m_CentDedEkiJikokuCont.size() - 1 ) )
	{
		bRv = false ;	//	『駅Index』が不正です。
	}
	else
	{
		const CentDedEkiJikoku* pEkijikoku = m_CentDedEkiJikokuCont.getMuPtr()->get( iEkiOrder ) ;
		const CentDedEkiJikoku* pEkijikokuNext = m_CentDedEkiJikokuCont.getMuPtr()->get( iEkiOrder + 1 ) ;
		if ( 
			( pEkijikoku->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya 
				|| pEkijikoku->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka ) 
			&& ( pEkijikokuNext->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya 
				|| pEkijikokuNext->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka ) 
		)
		{
			bRv = true ;
		}

	}
	return bRv ;
}

int CentDedRessya::getRunFirstEkiOrder()const 
{
	int iRv = -1 ;
	for ( int iEkiOrder = 0 ; 
		iRv == -1 && iEkiOrder < (int)m_CentDedEkiJikokuCont.size() - 1 ; 
		iEkiOrder ++ )
	{
		if ( isRunBetweenNextEki( iEkiOrder ) )
		{
			iRv = iEkiOrder ;
		}
	}
	return iRv ;
}
	
int CentDedRessya::getRunLastEkiOrder()const 
{
	int iRv = -1 ;
	for ( int iEkiOrder = (int)( m_CentDedEkiJikokuCont.size() ) - 2 ; 
		iRv == -1 && iEkiOrder >= 0 ; 
		iEkiOrder -- )
	{
		if ( isRunBetweenNextEki( iEkiOrder ) )
		{
			iRv = iEkiOrder + 1 ;
		}
	}
	return iRv ;
}

void CentDedRessya::adjustByEkijikokukeisiki(
		int iEkiOrder ,
		bool bChakujikokuHyouji , bool bHatsujikokuHyouji ) 
{
	if ( !m_bIsNull )
	{
		bool bSihatsuEki = ( getSihatsuEki() == iEkiOrder ) ;
		bool bSyuuchakuEki = ( getSyuuchakuEki() == iEkiOrder ) ;

		CentDedEkiJikoku aEkiJikoku = getCentDedEkiJikoku(iEkiOrder) ;
		aEkiJikoku.adjustByEkijikokukeisiki( 
			bChakujikokuHyouji , bHatsujikokuHyouji,
			bSihatsuEki , bSyuuchakuEki ) ;
		setCentDedEkiJikoku( iEkiOrder , aEkiJikoku ) ;
	}
}

int CentDedRessya::getValidSihatsuEki() const
{
	int iRv = -1;
	for (int iEkiOrder = 0; iEkiOrder < (int)m_CentDedEkiJikokuCont.size() - 1 && iRv == -1; iEkiOrder++)
	{
		const CentDedEkiJikoku* pEkijikoku = m_CentDedEkiJikokuCont.getMuPtr()->get(iEkiOrder);
		if (pEkijikoku->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_None)
		{
			continue;
		}
		else if (pEkijikoku->getHatsujikoku(false).isNull())
		{
			continue;
		}
		const CentDedEkiJikoku* pEkijikokuNext = m_CentDedEkiJikokuCont.getMuPtr()->get(iEkiOrder + 1);
		if (pEkijikokuNext->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya
			|| pEkijikokuNext->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka)
		{
			iRv = iEkiOrder;
		}
	}
	return iRv;
}

int CentDedRessya::getValidSyuuchakuEki() const
{
	int iRv = -1;
	for (int iEkiOrder = m_CentDedEkiJikokuCont.size() - 1; iEkiOrder > 0 && iRv == -1; iEkiOrder--)
	{
		const CentDedEkiJikoku* pEkijikoku = m_CentDedEkiJikokuCont.getMuPtr()->get(iEkiOrder);
		if (pEkijikoku->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_None)
		{
			continue;
		}
		else if (pEkijikoku->getChakujikoku(false).isNull())
		{
			continue;
		}
		const CentDedEkiJikoku* pEkijikokuPrev = m_CentDedEkiJikokuCont.getMuPtr()->get(iEkiOrder - 1);
		if (pEkijikokuPrev->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya
			|| pEkijikokuPrev->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka)
		{
			iRv = iEkiOrder;
		}
	}
	return iRv;
}


	// ********************************
	//@name 『時刻Order』単位の操作
	// ********************************
CdDedJikokuOrder CentDedRessya::incJikokuOrder( 
		const CdDedJikokuOrder& aJikokuOrder )const 
{
	CdDedJikokuOrder jikokuOrderRv = aJikokuOrder ;


	//	- aJikokuOrder の EkiOrder>=this.size() (最後の駅Orderの次) なら、@n
	//		aJikokuOrder をそのまま返します。
	//	- aJikokuOrder がNULL状態 なら、aJikokuOrder をそのまま返します。
	if ( !aJikokuOrder.getIsNull() && 
		aJikokuOrder.getEkiOrder() < (int)m_CentDedEkiJikokuCont.size() )
	{
		//	- aJikokuOrder が着時刻の場合は、同じ駅Orderの発時刻
		if ( jikokuOrderRv.getEkiJikokuItem() == CdDedJikokuOrder::EkiJikokuItem_Chaku )
		{
			jikokuOrderRv.setEkiOrder( jikokuOrderRv.getEkiOrder() , 
				CdDedJikokuOrder::EkiJikokuItem_Hatsu );
		}
		else if ( jikokuOrderRv.getEkiJikokuItem() == CdDedJikokuOrder::EkiJikokuItem_Hatsu )
		{
			//- aJikokuOrder が発時刻の場合は、次の駅Orderの着時刻
			jikokuOrderRv.setEkiOrder( jikokuOrderRv.getEkiOrder() + 1 , 
				CdDedJikokuOrder::EkiJikokuItem_Chaku );
		}
	}
	return jikokuOrderRv ;
}

CdDedJikokuOrder CentDedRessya::decJikokuOrder( 
		const CdDedJikokuOrder& aJikokuOrder )const 
{
	CdDedJikokuOrder jikokuOrderRv = aJikokuOrder ;

	//	- aJikokuOrder がNULL状態 なら、aJikokuOrder をそのまま返します。
	if ( !aJikokuOrder.getIsNull() )
	{ 
		//- aJikokuOrder の EkiOrder>=this.size() (最後の駅Orderの次) なら、@n
		//	最後の駅Orderの発時刻
		if ( aJikokuOrder.getEkiOrder() >= (int)m_CentDedEkiJikokuCont.size() )
		{
			jikokuOrderRv.setEkiOrder( (int)m_CentDedEkiJikokuCont.size() - 1, 
				CdDedJikokuOrder::EkiJikokuItem_Hatsu ) ;
		}
		//- aJikokuOrder が発時刻の場合は、同じ駅Orderの着時刻
		else if ( aJikokuOrder.getEkiJikokuItem() == CdDedJikokuOrder::EkiJikokuItem_Hatsu )
		{
			jikokuOrderRv.setEkiOrder( aJikokuOrder.getEkiOrder() , 
				CdDedJikokuOrder::EkiJikokuItem_Chaku ) ; 
		}
		//- aJikokuOrder が着時刻の場合は、次の駅Orderの発時刻
		//- aJikokuOrder が EkiOrder=0 の着なら、NULL状態
		else if (  aJikokuOrder.getEkiJikokuItem() == CdDedJikokuOrder::EkiJikokuItem_Chaku )
		{
			jikokuOrderRv.setEkiOrder( aJikokuOrder.getEkiOrder() - 1 , 
				CdDedJikokuOrder::EkiJikokuItem_Hatsu ) ; 
		}
	}
	return jikokuOrderRv ;
}



CdDedJikoku CentDedRessya::getEkiJikoku( CdDedJikokuOrder aJikokuOrder )const 
{
	CdDedJikoku	aCdDedJikoku ;
	int iRv = 0 ;
	if ( iRv >= 0 ){
		if ( !( 0 <= aJikokuOrder.getEkiOrder() && 
				aJikokuOrder.getEkiOrder() < (int)m_CentDedEkiJikokuCont.size() ) ){
			iRv = -1 ;	//	パラメータが不正
		}
	}
	if ( iRv >= 0 ){
		if ( aJikokuOrder.getEkiJikokuItem() == CdDedJikokuOrder::EkiJikokuItem_Hatsu ){
			aCdDedJikoku = 
				m_CentDedEkiJikokuCont.getMuPtr()->get( aJikokuOrder.getEkiOrder() )->getHatsujikoku() ;
		}	else	{
			aCdDedJikoku = 
				m_CentDedEkiJikokuCont.getMuPtr()->get( aJikokuOrder.getEkiOrder() )->getChakujikoku() ;
		}
	}
	return ( aCdDedJikoku ) ;
}

int CentDedRessya::setEkiJikoku( 
		const CdDedJikoku& aCdDedJikoku ,
		CdDedJikokuOrder aJikokuOrder ) 
{
	int iRv = 0 ;
	if ( iRv >= 0 ){
		if ( !( 0 <= aJikokuOrder.getEkiOrder() && 
				aJikokuOrder.getEkiOrder() < (int)m_CentDedEkiJikokuCont.size() ) ){
			iRv = -1 ;	//	パラメータが不正
		}
	}
	if ( iRv >= 0 ){
		if ( aJikokuOrder.getEkiJikokuItem() == CdDedJikokuOrder::EkiJikokuItem_Hatsu ){
			m_CentDedEkiJikokuCont.getMuPtr()->get( aJikokuOrder.getEkiOrder() )->setHatsujikoku(
				aCdDedJikoku ) ;
		}	else	{
			m_CentDedEkiJikokuCont.getMuPtr()->get( aJikokuOrder.getEkiOrder() )->setChakujikoku(
				aCdDedJikoku ) ;
		}
	}
	return ( iRv ) ;
}

int CentDedRessya::modifyRessyaJikoku( 
	const CdDedJikan& aCdDedJikan , 
	const CdDedJikokuOrder& aJikokuOrder ) 
{
	int iRv = 0 ;
	if ( iRv >= 0 ){
		if ( !( 0 <= aJikokuOrder.getEkiOrder() && 
				aJikokuOrder.getEkiOrder() < (int)m_CentDedEkiJikokuCont.size() ) ){
			iRv = -1 ;	//	パラメータが不正
		}
	}
	/**
		変更の基準時刻Orderが、有効始発駅の発時刻の場合は、その駅の前作業も時刻を変更します。
		(時刻Orderが始発駅以前or始発駅の着時刻の場合は、下のfor中に時刻変更が行われるのでここでは不要)
	*/
	if (iRv >= 0) {
		if (aJikokuOrder.getEkiOrder() == getValidSihatsuEki() &&
			aJikokuOrder.getEkiJikokuItem() == CdDedJikokuOrder::EkiJikokuItem_Hatsu)
		{
			getCentDedEkiJikokuCont()->getMuPtr()->get(aJikokuOrder.getEkiOrder())
				->getCentDedBeforeOperationCont()->modifyOperationJikoku(aCdDedJikan.getTotalSeconds());
		}
	}
	if ( iRv >= 0 ){
		CdDedJikokuOrder iJikokuOrderCurr ;
		for ( iJikokuOrderCurr = aJikokuOrder ;
			iJikokuOrderCurr.getEkiOrder() < (int)m_CentDedEkiJikokuCont.size() ;
			iJikokuOrderCurr = incJikokuOrder( iJikokuOrderCurr ) )
		{
			CdDedJikoku aCdDedJikoku = getEkiJikoku( iJikokuOrderCurr ) ;
			if ( !aCdDedJikoku.isNull() )
			{
				aCdDedJikoku = aCdDedJikoku.addSeconds( 
					aCdDedJikan.getTotalSeconds() ) ;
				setEkiJikoku( aCdDedJikoku , iJikokuOrderCurr ) ;
			}
			if (iJikokuOrderCurr.getEkiJikokuItem() == CdDedJikokuOrder::EkiJikokuItem_Chaku)
			{
				getCentDedEkiJikokuCont()->getMuPtr()->get(iJikokuOrderCurr.getEkiOrder())
					->getCentDedBeforeOperationCont()->modifyOperationJikoku(aCdDedJikan.getTotalSeconds());
			}
			else
			{
				getCentDedEkiJikokuCont()->getMuPtr()->get(iJikokuOrderCurr.getEkiOrder())
					->getCentDedAfterOperationCont()->modifyOperationJikoku(aCdDedJikan.getTotalSeconds());
			}
		}
	}
	return ( iRv ) ;
	
}

int CentDedRessya::modifyRessyaJikokuRev(
	const CdDedJikan& aCdDedJikan,
	const CdDedJikokuOrder& aJikokuOrder)
{
	int iRv = 0;
	if (iRv >= 0) {
		if (!(0 <= aJikokuOrder.getEkiOrder() &&
			aJikokuOrder.getEkiOrder() < (int)m_CentDedEkiJikokuCont.size())) {
			iRv = -1;	//	パラメータが不正
		}
	}
	/**
		変更の基準時刻Orderが、有効終着駅の着時刻の場合は、その駅の後作業も時刻を変更します。
		(時刻Orderが終着駅以降or終着駅の発時刻の場合は、下のfor中に時刻変更が行われるのでここでは不要)
	*/
	if (iRv >= 0) {
		if (aJikokuOrder.getEkiOrder() == getValidSyuuchakuEki() &&
			aJikokuOrder.getEkiJikokuItem() == CdDedJikokuOrder::EkiJikokuItem_Chaku)
		{
			getCentDedEkiJikokuCont()->getMuPtr()->get(aJikokuOrder.getEkiOrder())
				->getCentDedAfterOperationCont()->modifyOperationJikoku(aCdDedJikan.getTotalSeconds());
		}
	}
	if (iRv >= 0) {
		CdDedJikokuOrder iJikokuOrderCurr;
		for (iJikokuOrderCurr = aJikokuOrder;
			iJikokuOrderCurr.getEkiOrder() >= 0;
			//iJikokuOrderCurr.getEkiOrder() < (int)m_CentDedEkiJikokuCont.size();
			iJikokuOrderCurr = decJikokuOrder(iJikokuOrderCurr))
		{
			CdDedJikoku aCdDedJikoku = getEkiJikoku(iJikokuOrderCurr);
			if (!aCdDedJikoku.isNull())
			{
				aCdDedJikoku = aCdDedJikoku.addSeconds(
					aCdDedJikan.getTotalSeconds());
				setEkiJikoku(aCdDedJikoku, iJikokuOrderCurr);
			}
			if (iJikokuOrderCurr.getEkiJikokuItem() == CdDedJikokuOrder::EkiJikokuItem_Chaku)
			{
				getCentDedEkiJikokuCont()->getMuPtr()->get(iJikokuOrderCurr.getEkiOrder())
					->getCentDedBeforeOperationCont()->modifyOperationJikoku(aCdDedJikan.getTotalSeconds());
			}
			else
			{
				getCentDedEkiJikokuCont()->getMuPtr()->get(iJikokuOrderCurr.getEkiOrder())
					->getCentDedAfterOperationCont()->modifyOperationJikoku(aCdDedJikan.getTotalSeconds());
			}
		}
	}
	return (iRv);

}

int CentDedRessya::modifyRessyaBangou(const int & iShiftRessyaBangou)
{
	int iRv = 0;
	tstring strRessyaBangouOld = getRessyabangou();
	CString strCRessyaBangouOld = strRessyaBangouOld.c_str();
	int idxNumTop = INT_MIN;
	int idxNumBottom = INT_MIN;
	bool bFullWidth = false;
	for (int idx = strRessyaBangouOld.size() - 1; 
		idx >= 0; idx--)
	{
		if (idxNumBottom != INT_MIN && idxNumTop != INT_MIN)
		{
			break;
		}
		if (_istdigit(strRessyaBangouOld[idx]) != 0)
		{
			//数字の場合、底が見つかっていない場合は、idxを底にする。
			if (idxNumBottom == INT_MIN)
			{
				idxNumBottom = idx;

				//idx番目の文字が全角の場合、bFullWidthをTrueにする。
				int iLength = strCRessyaBangouOld.GetLength();
				WORD *type = new WORD[iLength];
				if (GetStringTypeEx(
					LOCALE_SYSTEM_DEFAULT,
					CT_CTYPE3,
					strCRessyaBangouOld,
					iLength,
					type))
				{
					if ((type[idx] & C3_FULLWIDTH) == C3_FULLWIDTH)
					{
						bFullWidth = true;
					}
				}
			}
			//idx=0で、底が見つかっていて頭が見つかっていない場合は、idx(0)を頭にする
			if (idx == 0 &&
				idxNumBottom != INT_MIN &&
				idxNumTop == INT_MIN)
			{
				idxNumTop = idx;
			}
		}
		else
		{
			//数字以外の場合、底が見つかっていて頭が見つかっていない場合は、idx+1を頭にする
			if (idxNumBottom != INT_MIN && idxNumTop == INT_MIN)
			{
				idxNumTop = idx + 1;
			}
		}
	}
	if (idxNumBottom != INT_MIN && idxNumTop != INT_MIN)
	{
		int iRessyaBangou = _ttoi(strRessyaBangouOld.substr(idxNumTop).c_str());
		iRessyaBangou += iShiftRessyaBangou;
		if (iRessyaBangou < 0)
		{
			//加算した結果が負の値になったら、値を0にします。
			iRessyaBangou = 0;
		}
		tstring strRessyaBangouNew = strRessyaBangouOld.substr(0, idxNumTop);
		TCHAR strBuf[17] /*= _T("")*/;
		_stprintf_s(strBuf, 16, _T("%0*d"), idxNumBottom - idxNumTop + 1, iRessyaBangou);
		if (bFullWidth)
		{
			for (int idx = 0; idx < 17; idx++)
			{
				switch (strBuf[idx]) {
				case _T('0'): strBuf[idx] = _T('０'); break;
				case _T('1'): strBuf[idx] = _T('１'); break;
				case _T('2'): strBuf[idx] = _T('２'); break;
				case _T('3'): strBuf[idx] = _T('３'); break;
				case _T('4'): strBuf[idx] = _T('４'); break;
				case _T('5'): strBuf[idx] = _T('５'); break;
				case _T('6'): strBuf[idx] = _T('６'); break;
				case _T('7'): strBuf[idx] = _T('７'); break;
				case _T('8'): strBuf[idx] = _T('８'); break;
				case _T('9'): strBuf[idx] = _T('９'); break;
				}
			}
		}
		strRessyaBangouNew += strBuf;
		strRessyaBangouNew+= strRessyaBangouOld.substr(idxNumBottom+1);
		setRessyabangou(strRessyaBangouNew);
	}
	return iRv;
}

int CentDedRessya::modifyGou(const int & iShiftGou)
{
	int iRv = 0;
	tstring strGouOld = getGousuu();
	CString strCGouOld = strGouOld.c_str();
	int idxNumTop = INT_MIN;
	int idxNumBottom = INT_MIN;
	bool bFullWidth = false;
	for (int idx = strGouOld.size() - 1;
		idx >= 0; idx--)
	{
		if (idxNumBottom != INT_MIN && idxNumTop != INT_MIN)
		{
			break;
		}
		if (_istdigit(strGouOld[idx]) != 0)
		{
			//数字の場合、底が見つかっていない場合は、idxを底にする。
			if (idxNumBottom == INT_MIN)
			{
				idxNumBottom = idx;

				//idx番目の文字が全角の場合、bFullWidthをTrueにする。
				int iLength = strCGouOld.GetLength();
				WORD *type = new WORD[iLength];
				if (GetStringTypeEx(
					LOCALE_SYSTEM_DEFAULT,
					CT_CTYPE3,
					strCGouOld,
					iLength,
					type))
				{
					if ((type[idx] & C3_FULLWIDTH) == C3_FULLWIDTH)
					{
						bFullWidth = true;
					}
				}
			}
			//idx=0で、底が見つかっていて頭が見つかっていない場合は、idx(0)を頭にする
			if (idx == 0 &&
				idxNumBottom != INT_MIN &&
				idxNumTop == INT_MIN)
			{
				idxNumTop = idx;
			}
		}
		else
		{
			//数字以外の場合、底が見つかっていて頭が見つかっていない場合は、idx+1を頭にする
			if (idxNumBottom != INT_MIN && idxNumTop == INT_MIN)
			{
				idxNumTop = idx + 1;
			}
		}
	}
	if (idxNumBottom != INT_MIN && idxNumTop != INT_MIN)
	{
		int iGou = _ttoi(strGouOld.substr(idxNumTop).c_str());
		iGou += iShiftGou;
		if (iGou < 0)
		{
			//加算した結果が負の値になったら、値を0にします。
			iGou = 0;
		}
		tstring strGouNew = strGouOld.substr(0, idxNumTop);
		TCHAR strBuf[17] /*= _T("")*/;
		//_stprintf_s(strBuf, 16, _T("%0*d"), idxNumBottom - idxNumTop + 1, iGou);
		_stprintf_s(strBuf, 16, _T("%d"), iGou);
		if (bFullWidth)
		{
			for (int idx = 0; idx < 17; idx++)
			{
				switch (strBuf[idx]) {
				case _T('0'): strBuf[idx] = _T('０'); break;
				case _T('1'): strBuf[idx] = _T('１'); break;
				case _T('2'): strBuf[idx] = _T('２'); break;
				case _T('3'): strBuf[idx] = _T('３'); break;
				case _T('4'): strBuf[idx] = _T('４'); break;
				case _T('5'): strBuf[idx] = _T('５'); break;
				case _T('6'): strBuf[idx] = _T('６'); break;
				case _T('7'): strBuf[idx] = _T('７'); break;
				case _T('8'): strBuf[idx] = _T('８'); break;
				case _T('9'): strBuf[idx] = _T('９'); break;
				}
			}
		}
		strGouNew += strBuf;
		strGouNew += strGouOld.substr(idxNumBottom + 1);
		setGousuu(strGouNew);
	}
	return iRv;
}


CdDedJikokuOrder CentDedRessya::findrevJikoku( 
	const CdDedJikokuOrder& jikokuOrder )const 
{
	CdDedJikokuOrder aJikokuOrder = jikokuOrder ;
	CdDedJikokuOrder iRv  ;
	
	for ( ; 
		iRv.getIsNull() && aJikokuOrder.getEkiOrder() >= 0 ; 
		aJikokuOrder = decJikokuOrder(  aJikokuOrder ) )
	{
		CdDedJikoku	aCdDedJikoku = getEkiJikoku( aJikokuOrder ) ;
		if ( !aCdDedJikoku.isNull() )
		{
			iRv = aJikokuOrder ;
		}
	}
	return ( iRv ) ;
}
	
	
	// ********************************
	//@name 操作
	// ********************************



void CentDedRessya::clear() 
{
	m_bIsNull = true ;
	m_iRessyasyubetsuIndex = 0 ;
	m_strRessyabangou.erase() ;
	m_strRessyamei.erase() ;
	m_strGousuu.erase() ;
	m_strBikou.erase() ;
	m_bIsCanceled = false;

	for ( int iEkiOrder = 0 ; 
			iEkiOrder < (int)m_CentDedEkiJikokuCont.size() ; 
			iEkiOrder ++ ){
		CentDedEkiJikoku*	pCentDedEkiJikoku = 
			m_CentDedEkiJikokuCont.getMuPtr()->get( iEkiOrder ) ;
		pCentDedEkiJikoku->setEkiatsukai( CentDedEkiJikoku::Ekiatsukai_None ) ;
	}

}

void CentDedRessya::pasteEkiJikoku( const CentDedRessya& aCentDedRessyaSrc ) 
{
	int iEkiOrder = 0 ;
	for ( iEkiOrder = 0 ; 
		iEkiOrder < (int)m_CentDedEkiJikokuCont.size()  ; 
			iEkiOrder ++ )
	{
		CentDedEkiJikoku aCentDedEkiJikokuSrc = 
			aCentDedRessyaSrc.getCentDedEkiJikoku( iEkiOrder ) ;
		if ( aCentDedEkiJikokuSrc.getEkiatsukai() != 
				CentDedEkiJikoku::Ekiatsukai_None  )
		{
			CentDedEkiJikoku* pCentDedEkiJikokuDst = m_CentDedEkiJikokuCont.getMuPtr()->get(iEkiOrder) ;
			pCentDedEkiJikokuDst->setEkiatsukai( aCentDedEkiJikokuSrc.getEkiatsukai() ) ;
			
			if ( !aCentDedEkiJikokuSrc.getChakujikoku().isNull() )
			{
				pCentDedEkiJikokuDst->setChakujikoku( aCentDedEkiJikokuSrc.getChakujikoku() ) ;
			}
			if ( !aCentDedEkiJikokuSrc.getHatsujikoku().isNull() )
			{
				pCentDedEkiJikokuDst->setHatsujikoku( aCentDedEkiJikokuSrc.getHatsujikoku() ) ;
			}

			pCentDedEkiJikokuDst->setRessyaTrackIndex(aCentDedEkiJikokuSrc.getRessyaTrackIndex());
			//前後作業の貼り付け
			pCentDedEkiJikokuDst->setCentDedBeforeOperationCont(*aCentDedEkiJikokuSrc.getCentDedBeforeOperationCont());
			pCentDedEkiJikokuDst->setCentDedAfterOperationCont(*aCentDedEkiJikokuSrc.getCentDedAfterOperationCont());
		}
	}
	adjustOperation();
}

int CentDedRessya::direct( 
		const CentDedRessya& aRessyaSihatsu ) 
{
	int iRv = 0 ;

	int iEkiOrderSyuuchaku = -1 ;
	int iEkiOrderSihatsu = -1 ;

	//	this列車の終着駅・始発列車の始発駅の取得
	if ( iRv >= 0 )
	{
		iEkiOrderSyuuchaku = getRunLastEkiOrder() ;
		iEkiOrderSihatsu = aRessyaSihatsu.getRunFirstEkiOrder() ;
		if ( iEkiOrderSyuuchaku == -1 )
		{
			iRv = -1 ;	//	この列車には駅時刻が指定されていません。
		}
		else if ( iEkiOrderSihatsu == -1 )
		{
			iRv = -2 ;	//	始発列車には駅時刻が指定されていません。
		}
		else if ( !( iEkiOrderSyuuchaku <= iEkiOrderSihatsu ) )
		{
			iRv = -3 ;	//	aRessyaSihatsu との直通化はできません。
			//aRessyaSihatsu の始発駅は、	this の終着駅と同じか、それ以降でなくてはなりません。
		}
	}
	//iEkiOrderSyuuchaku = this列車の終着駅の駅Order
	//iEkiOrderSihatsu = aRessyaSihatsu の始発駅の駅Order


	//	終着駅～始発駅までの間は、運行なしとします。
	if ( iRv <= 0 )
	{
		for ( int iEkiOrder = iEkiOrderSyuuchaku + 1 ;
			iEkiOrder < iEkiOrderSihatsu ;
			iEkiOrder ++ )
		{
			setCentDedEkiJikoku( 
				iEkiOrder , 
				CentDedEkiJikoku( CentDedEkiJikoku::Ekiatsukai_None , CdDedJikoku() , CdDedJikoku() ) 
				);
		}
	}

	//	始発列車の始発駅
	//
	//始発駅の時刻(直通化した時刻)は、以下のようになります。
	//- 駅扱：変わりません。
	//- 着時刻：
	//  - this列車に着時刻が指定されていた場合：その着時刻
	//  - this列車に着時刻がなく、発時刻が指定されていた場合：途中駅止まり列車の発時刻
	//  - this列車に着時刻も発時刻も指定されていない場合：着時刻はなし
	//- 発時刻
	//  - 始発列車に発時刻が指定されていた場合：その発時刻を直通化した列車の発時刻とします。
	//  - 始発列車に発時刻がなく、着時刻が指定されていた場合：途中駅始発列車の着時刻を、新しい列車の発時刻とします。
	//  - 始発列車に着時刻も発時刻も指定されていない場合：発時刻はなし

	//-番線
	//this終着駅と始発列車始発駅の駅Orderが同じ場合は、番線はthisのまま、それ以外の場合始発列車からコピー
	//異なる場合は、それぞれ使用
	if ( iRv <= 0 )
	{
		CentDedEkiJikoku	aCentDedEkiJikokuSyuuchaku = getCentDedEkiJikoku( iEkiOrderSihatsu ) ;
		CentDedEkiJikoku	aCentDedEkiJikokuSihatsu = aRessyaSihatsu.getCentDedEkiJikoku( iEkiOrderSihatsu ) ;

		CentDedEkiJikoku	aCentDedEkiJikokuNew = aCentDedEkiJikokuSyuuchaku ;
		//- 着時刻：
		if ( !aCentDedEkiJikokuSyuuchaku.getChakujikoku().isNull() )
		{
			//　途中駅止まりの列車に着時刻が指定されていた場合：その着時刻
			aCentDedEkiJikokuNew.setChakujikoku( aCentDedEkiJikokuSyuuchaku.getChakujikoku() ) ;
		}
		else if ( !aCentDedEkiJikokuSyuuchaku.getHatsujikoku().isNull() )
		{
			//　途中駅止まりの列車に着時刻がなく、発時刻が指定されていた場合：途中駅止まり列車の発時刻
			aCentDedEkiJikokuNew.setChakujikoku( aCentDedEkiJikokuSyuuchaku.getHatsujikoku() ) ;
		}
		else
		{
			//　途中駅止まりの列車に着時刻も発時刻も指定されていない場合：着時刻はなし
			aCentDedEkiJikokuNew.setChakujikoku( CdDedJikoku() ) ;
		}


		//- 発時刻
		if ( !( aCentDedEkiJikokuSihatsu.getHatsujikoku().isNull() ) )
		{
			//  - 始発列車に発時刻が指定されていた場合：その発時刻を直通化した列車の発時刻とします。
			aCentDedEkiJikokuNew.setHatsujikoku( aCentDedEkiJikokuSihatsu.getHatsujikoku() ) ;
		}
		else if ( !( aCentDedEkiJikokuSihatsu.getChakujikoku().isNull() ) )
		{
			//  - 始発列車に発時刻がなく、着時刻が指定されていた場合：途中駅始発列車の着時刻を、新しい列車の発時刻とします。
			aCentDedEkiJikokuNew.setHatsujikoku( aCentDedEkiJikokuSihatsu.getChakujikoku() ) ;
		}
		else
		{
			//  - 始発列車に着時刻も発時刻も指定されていない場合：発時刻はなし
			aCentDedEkiJikokuNew.setHatsujikoku( CdDedJikoku() ) ;
		}

		//発着番線
		if (iEkiOrderSyuuchaku < iEkiOrderSihatsu)
		{
			aCentDedEkiJikokuNew.setRessyaTrackIndex(aCentDedEkiJikokuSihatsu.getRessyaTrackIndex());
		}
		setCentDedEkiJikoku( iEkiOrderSihatsu , aCentDedEkiJikokuNew ) ;
	}

	//	始発駅より後の駅の駅時刻
	if ( iRv <= 0 )
	{
		for ( int iEkiOrder = iEkiOrderSihatsu + 1 ; 
			iEkiOrder < (int)m_CentDedEkiJikokuCont.size()  ; 
				iEkiOrder ++ )
		{
			CentDedEkiJikoku	aCentDedEkiJikokuSihatsu = aRessyaSihatsu.getCentDedEkiJikoku( iEkiOrder ) ;
			setCentDedEkiJikoku( iEkiOrder , aCentDedEkiJikokuSihatsu ) ;
		}
	}

	if (iRv <= 0)
	{
		adjustOperation();
	}

	//始発駅の列車情報(列車番号・列車名・号数・備考)は以下のようになります。
	//
	//- this列車が空文字列、始発列車が情報ありの場合、始発列車の情報を受け継ぎます。
	//- this列車が情報あり、始発列車が空文字列の場合、this列車の情報を受け継ぎます。
	//- this列車も始発列車も情報ありの場合、this列車の情報を受け継ぎます。
	if ( iRv <= 0 )
	{
		if ( m_strRessyabangou.length() == 0 && aRessyaSihatsu.getRessyabangou().length() > 0 )
		{
			m_strRessyabangou = aRessyaSihatsu.getRessyabangou() ;
		}
		if ( m_strRessyamei.length() == 0 && aRessyaSihatsu.getRessyamei().length() > 0 )
		{
			m_strRessyamei = aRessyaSihatsu.getRessyamei() ;
		}
		if ( m_strGousuu.length() == 0 && aRessyaSihatsu.getGousuu().length() > 0 )
		{
			m_strGousuu = aRessyaSihatsu.getGousuu() ;
		}
		if ( m_strBikou.length() == 0 && aRessyaSihatsu.getBikou().length() > 0 )
		{
			m_strBikou = aRessyaSihatsu.getBikou() ;
		}

	}	

	return iRv ;
}

int CentDedRessya::undirect(
		int iEkiOrder , 
		CentDedRessya* pCentDedRessyaSyuuchaku ,
		CentDedRessya* pCentDedRessyaSihatsu )const 
{
	int iRv = 0 ;


	//○途中駅止まり列車の終着駅Orderを決定
	//│([終着駅Orderの駅と終着駅Order-1の駅の間に列車運行がない]
	//│の条件が偽の間は、終着駅Order--する。
	//↓終着駅Orderが0ならエラー)
	//◇[終着駅Order==0]→エラー
	int iEkiOrderSyuuchaku = -1 ;
	if ( iRv >= 0 )
	{
		for ( iEkiOrderSyuuchaku = iEkiOrder ;
			iEkiOrderSyuuchaku > 0 && !isRunBetweenNextEki( iEkiOrderSyuuchaku - 1 ) ;
			iEkiOrderSyuuchaku -- )
		{
		}
		if ( iEkiOrderSyuuchaku == 0 )
		{
			iRv = -1 ;	//	指定の駅Orderでは、分断はできません
		}
	}

	//○途中駅始発列車の始発駅Indexを決定
	//│([始発駅Orderの駅と始発駅Order+1の駅の間に列車運行がない]
	//↓の条件が偽の間は、始発駅rOder++する。)
	//◇[始発駅Order==駅数-1]→エラー
	int iEkiOrderSihatsu = -1 ;
	if ( iRv >= 0 )
	{
		for ( iEkiOrderSihatsu = iEkiOrder ;
			iEkiOrderSihatsu < (int)m_CentDedEkiJikokuCont.size() - 1 && 
				!isRunBetweenNextEki( iEkiOrderSihatsu ) ;
			iEkiOrderSihatsu ++ )
		{
		}
		if ( iEkiOrderSihatsu == m_CentDedEkiJikokuCont.size() - 1 )
		{
			iRv = -1 ;	//	指定の駅Orderでは、分断はできません
		}
	}
	//○分断する列車のコピーを2つ作成。
	//↓これを途中駅止まり列車・途中駅始発列車とする。
	//○途中駅止まり列車の方を、終着駅Orderで当駅どまりにする
	//○途中駅始発列車の方を、始発駅Orderで当駅始発にする
	if ( iRv >= 0 )
	{
		*pCentDedRessyaSyuuchaku = *this ;
		pCentDedRessyaSyuuchaku->setSyuuchakuEki( iEkiOrderSyuuchaku ) ;
		pCentDedRessyaSyuuchaku->getCentDedEkiJikokuCont()->getMuPtr()->
			get(iEkiOrderSyuuchaku)->getCentDedAfterOperationCont()->adjustOperation(INT_MIN);
		pCentDedRessyaSyuuchaku->adjustOperation();

		*pCentDedRessyaSihatsu = *this ;
		pCentDedRessyaSihatsu->setSihatsuEki( iEkiOrderSihatsu ) ;
		pCentDedRessyaSihatsu->getCentDedEkiJikokuCont()->getMuPtr()->
			get(iEkiOrderSihatsu)->getCentDedBeforeOperationCont()->adjustOperation(INT_MIN);
		pCentDedRessyaSihatsu->adjustOperation();
	}	

	return iRv ;
}

void CentDedRessya::adjust() 
{
	CentDedRessyaCont* pCentDedRessyaCont 
		= pCentDedRessyaCont = dynamic_cast<CentDedRessyaCont*>( getParent() ) ;
	CentDedRosen* pCentDedRosen = NULL ;
	if ( pCentDedRessyaCont != NULL )
	{
		pCentDedRosen = pCentDedRessyaCont->getRosen() ;
	}

	//△列車が親オブジェクト CentDedRessyaCont の一部である場合、
	//列車方向は、親オブジェクトである列車コンテナの列車方向と同一とします。
	if ( pCentDedRessyaCont != NULL )
	{
		m_eRessyahoukou = pCentDedRessyaCont->getRessyahoukou() ;	
	}

	//△列車種別IndexがCentDedRessyasyubetsuCont(列車種別コンテナ)の
	//範囲外である場合は、列車種別Indexは0とします。
	
	
	if ( pCentDedRosen != NULL )
	{
		CentDedRessyasyubetsuCont* pCentDedRessyasyubetsuCont = pCentDedRosen->getCentDedRessyasyubetsuCont() ;

		if ( !( 0 <= m_iRessyasyubetsuIndex 
			&& m_iRessyasyubetsuIndex < pCentDedRessyasyubetsuCont->size() 
		) )
		{
			m_iRessyasyubetsuIndex = 0 ;
		}
	}
	//○CentDedEkiJikokuCont(駅時刻コンテナ)に、adjust()を委譲します。
	m_CentDedEkiJikokuCont.adjust() ;
}

void CentDedRessya::adjustOperation()
{
	const CentDedEkiCont* pCentDedEkiCont =
		getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont();
	const Mu< CentDedEkiCont::CdDedEki>* pMuCdDedEki =
		pCentDedEkiCont->getMuPtr(getRessyahoukou());

	adjustOperation(pCentDedEkiCont, pMuCdDedEki);
}

void CentDedRessya::adjustOperation(
	const CentDedEkiCont* pCentDedEkiCont,
	const Mu<CentDedEkiCont::CdDedEki>* pMuCdDedEki)
{
	int iValidSihatsuEki = getValidSihatsuEki();
	int iValidSyuuchakuEki = getValidSyuuchakuEki();
	if (iValidSihatsuEki == -1 || iValidSyuuchakuEki == -1 || iValidSihatsuEki >= iValidSyuuchakuEki)
	{
		return;
	}
	for (int iEkiOrder = 0; iEkiOrder < (int)m_CentDedEkiJikokuCont.size(); iEkiOrder++)
	{
		CentDedEkiJikoku* pEkijikoku = m_CentDedEkiJikokuCont.getMuPtr()->get(iEkiOrder);
		if (iEkiOrder < iValidSihatsuEki || iEkiOrder > iValidSyuuchakuEki)
		{
			pEkijikoku->adjustOperation(INT_MIN);
		}
		else if (iEkiOrder == iValidSihatsuEki)
		{
			pEkijikoku->adjustOperation(-2);
		}
		else if (iEkiOrder > iValidSihatsuEki && iEkiOrder < iValidSyuuchakuEki)
		{
			//pEkijikoku->adjustOperation(0);
			//if (isRunBetweenNextEki(iEkiOrder - 1))
			//{
			if (isRunBetweenNextEki(iEkiOrder))
			{
				//前後ともありの場合は、この駅の時刻次第となる。
				/**
					前後とも時刻有の場合は、この駅の時刻形式を見て判断する
					発着・下り発着(下り)・上り発着(上り)の場合
						駅時刻が発着ともある場合のみ、作業が有効。
					発時刻・下り発着(上り)・上り発着(下り)・下り着・上り着の場合
						作業を削除
				*/
				const CentDedEkiCont::CdDedEki aCdDedEki = pMuCdDedEki->get(iEkiOrder);
				if (aCdDedEki.isHatsuChakuHyouji())
				{
					pEkijikoku->adjustOperation(0);
				}
				else
				{
					pEkijikoku->adjustOperation(INT_MIN);
				}

			}
			else
			{
				//前方のみ有の場合は、後作業は必ず削除とする
				/**
					前方のみ有の場合は、運行無しの連続をたどり、運行無し後の駅と合わせて評価する
					・間の無関係な駅に、飛び地の停車・通過がある(b)
					・間が運行無しだけだが、その前後の駅が別駅の場合(c)
					・間が運行無しだけで、前後の駅が同一駅扱いだが、駅時刻形式が合わない(d)
						　　(前側は着時刻が、後側は発時刻表示が必須)場合
						前駅の後作業は削除、前作業は時刻形式と時刻次第
						運行無しの駅の作業削除
						孤立した停車・通過駅は作業削除
						次のisRunBetweenNextEki(iEkiOrder2)=True駅は、前作業削除、後作業は時刻形式と時刻次第
						iEkiOrderをiEkiOrder2に書き換えて探索継続
						
					間が経由無しだけ(同一駅扱いの駅に限り、飛び地の停車・通過を認める)で、前後の駅が同一駅扱いで、駅時刻形式も適切な場合
						駅時刻が前駅の着と後駅の発がある場合のみ、作業が有効
						前駅の後作業と後駅の前作業は削除
						途中の経由無し・単独停車・通過駅の作業は削除
					
				*/
				//まずは、次のisRunBetweenNextEkiを見つける
				int iHatsuEkiOrder = getRunBetweenEkiForward(iEkiOrder);

				bool bSame = true;
				if (iHatsuEkiOrder == -1)
				{
					continue;
				}
				else if(!pCentDedEkiCont->isSameBrunchLoopGroup(
					iEkiOrder, iHatsuEkiOrder, getRessyahoukou()))
				{
					bSame = false;
					//(c)は確定((a),(b)の可能性も)
				}
				const CentDedEkiCont::CdDedEki aCdDedEki = pMuCdDedEki->get(iEkiOrder);
				const CentDedEkiCont::CdDedEki aCdDedEkiHatsu = pMuCdDedEki->get(iHatsuEkiOrder);
				if (bSame)
				{
					//駅時刻形式(d)のチェックを行う
					if (!aCdDedEki.getChakujikokuHyouji() ||
						!aCdDedEkiHatsu.getHatsujikokuHyouji())
					{
						bSame = false;
						//同一駅でも、前駅に着時刻が、後駅に発時刻表示が無いのなら、falseにする。
					}
				}
				if (bSame)
				{
					CentDedEkiJikoku* pEkijikokuHatsu = 
						m_CentDedEkiJikokuCont.getMuPtr()->get(iHatsuEkiOrder);
					if (!pEkijikoku->getChakujikoku(false).isNull() &&
						!pEkijikokuHatsu->getHatsujikoku(false).isNull())
					{
						/**
							着発両時刻が有る場合は、前駅の前作業と後駅の後作業はチェックを行い、
							前駅の後作業と後駅の前作業は削除します
						*/
						pEkijikoku->adjustOperation(1);
						pEkijikokuHatsu->adjustOperation(-1);
					}
					else
					{
						/**
							着発時刻が揃っていない時は、全作業を削除します
						*/
						pEkijikoku->adjustOperation(INT_MIN);
						pEkijikokuHatsu->adjustOperation(INT_MIN);
					}

				}
				else
				{
					/**
						同一駅扱いでない場合、前駅作業と後駅作業は削除します

					*/
					CentDedEkiJikoku* pEkijikokuHatsu =
						m_CentDedEkiJikokuCont.getMuPtr()->get(iHatsuEkiOrder);
					pEkijikoku->adjustOperation(INT_MIN);
					pEkijikokuHatsu->adjustOperation(INT_MIN);
				}
				for (int ord = iEkiOrder + 1; ord < iHatsuEkiOrder; ord++)
				{
					CentDedEkiJikoku* pEkijikokuMid =
						m_CentDedEkiJikokuCont.getMuPtr()->get(ord);
					pEkijikokuMid->adjustOperation(INT_MIN);
				}

				iEkiOrder = iHatsuEkiOrder;
			}
		}
		else if (iEkiOrder == iValidSyuuchakuEki)
		{
			pEkijikoku->adjustOperation(2);
		}
	}
}


int CentDedRessya::isExistRessyaOfEkiTrack2(
	int iEkiOrder, 
	int iEkiTrack2Index)
{
	int iRv = 0;
	if (getCentDedEkiJikoku(iEkiOrder).getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_None)
	{
		return iRv;
	}
	int iRessyaTrackIndex = getCentDedEkiJikoku(iEkiOrder).getRessyaTrackIndex();

	if (iRv ==0 && iRessyaTrackIndex == iEkiTrack2Index)
	{
		iRv = 1;
	}
	if (iRv == 0)
	{
		iRv = getCentDedEkiJikokuCont()->getMuPtr()->get(iEkiOrder)
			->getCentDedBeforeOperationCont()->isExistRessyaOfEkiTrack2(iEkiTrack2Index);
	}
	if (iRv == 0)
	{
		iRv = getCentDedEkiJikokuCont()->getMuPtr()->get(iEkiOrder)
			->getCentDedAfterOperationCont()->isExistRessyaOfEkiTrack2(iEkiTrack2Index);
	}
	return iRv;
}

int CentDedRessya::isExistRessyaOfOuterTerminal(
	int iEkiOrder,
	int iOuterTerminalIndex)
{
	int iRv = 0;
	if (getCentDedEkiJikoku(iEkiOrder).getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_None)
	{
		return iRv;
	}

	if (iRv == 0)
	{
		iRv = getCentDedEkiJikokuCont()->getMuPtr()->get(iEkiOrder)
			->getCentDedBeforeOperationCont()->isExistRessyaOfOuterTerminal(iOuterTerminalIndex);
	}
	if (iRv == 0)
	{
		iRv = getCentDedEkiJikokuCont()->getMuPtr()->get(iEkiOrder)
			->getCentDedAfterOperationCont()->isExistRessyaOfOuterTerminal(iOuterTerminalIndex);
	}

	return iRv;
}

const CentDedBeforeOperation CentDedRessya::getFirstOperation()const
{
	if (this->getValidSihatsuEki() < 0)
	{
		return CentDedBeforeOperation();
	}
	const CentDedBeforeOperationCont* pBeforeOperationCont = getCentDedEkiJikokuCont()->getMuPtr()
		->get(getValidSihatsuEki())->getCentDedBeforeOperationCont();
	if (pBeforeOperationCont->size() == 0)
	{
		return CentDedBeforeOperation();
	}
	const CentDedBeforeOperation aBeforeFirstOperation = pBeforeOperationCont->get(0);
	if (aBeforeFirstOperation.isFirstOperation())
	{
		return aBeforeFirstOperation;
	}
	return CentDedBeforeOperation();
}

const CentDedAfterOperation CentDedRessya::getLastOperation()const
{
	if (this->getValidSyuuchakuEki() < 0)
	{
		return CentDedAfterOperation();
	}
	const CentDedAfterOperationCont* pAfterOperationCont = getCentDedEkiJikokuCont()->getMuPtr()
		->get(getValidSyuuchakuEki())->getCentDedAfterOperationCont();
	if (pAfterOperationCont->size() == 0)
	{
		return CentDedAfterOperation();
	}
	const CentDedAfterOperation aAfterLastOperation = pAfterOperationCont->get(INT_MAX);
	if (aAfterLastOperation.isLastOperation())
	{
		return aAfterLastOperation;
	}
	return CentDedAfterOperation();
}

int CentDedRessya::getRunBetweenEkiForward(int iEkiOrder)const
{
	int iRv = -1;
	if (0 <= iEkiOrder && iEkiOrder < (int)m_CentDedEkiJikokuCont.size())
	{
		for (int iEkiOrderSearch = iEkiOrder + 1; iEkiOrderSearch < (int)m_CentDedEkiJikokuCont.size() - 1; iEkiOrderSearch++)
		{
			if (isRunBetweenNextEki(iEkiOrderSearch))
			{
				iRv = iEkiOrderSearch;
				break;
			}
		}

	}
	return iRv;
}

int CentDedRessya::getRunBetweenEkiBackward(int iEkiOrder)const
{
	int iRv = -1;
	if (0 <= iEkiOrder && iEkiOrder < (int)m_CentDedEkiJikokuCont.size())
	{
		for (int iEkiOrderSearch = iEkiOrder - 2; iEkiOrderSearch >= 0; iEkiOrderSearch--)
		{
			if (isRunBetweenNextEki(iEkiOrderSearch))
			{
				iRv = iEkiOrderSearch + 1;
				break;
			}
		}

	}
	return iRv;
}
vector<tstring> CentDedRessya::getOperationNumber(const int iEkiOrder) const
{
	int iValidSihatsuEki = getValidSihatsuEki();
	int iValidSyuuchakuEki = getValidSyuuchakuEki();
	if (iValidSihatsuEki == -1 || iValidSyuuchakuEki == -1)
	{
		return vector<tstring>();
	}
	else if (iEkiOrder < iValidSihatsuEki)
	{
		return vector<tstring>();
	}
	else if (iEkiOrder >= iValidSyuuchakuEki)
	{
		return getLastOperation().getOperationNumber();
	}
	for (int idx = iEkiOrder; idx >= iValidSihatsuEki; idx--)
	{
		const CentDedAfterOperationCont* pAfterCont = getCentDedEkiJikokuCont()->getMuPtr()
			->get(idx)->getCentDedAfterOperationCont();
		for (int idxa = pAfterCont->size() - 1; idxa >= 0; idxa--)
		{
			const CentDedAfterOperation* pAfterOperation = pAfterCont->getMuPtr()->get(idxa);
			if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
			{
				return pAfterOperation->getOperationNumberAfter();
			}
			else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
			{
				return pAfterOperation->getOperationNumberMain();
			}
			//Ver2.00.05 運用番号変更に対応
			else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_NumberChange)
			{
				return pAfterOperation->getOperationNumber();
			}
		}

		const CentDedBeforeOperationCont* pBeforeCont = getCentDedEkiJikokuCont()->getMuPtr()
			->get(idx)->getCentDedBeforeOperationCont();
		for (int idxb = pBeforeCont->size() - 1; idxb >= 0; idxb--)
		{
			const CentDedBeforeOperation* pBeforeOperation = pBeforeCont->getMuPtr()->get(idxb);
			if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
			{
				return pBeforeOperation->getOperationNumberAfter();
			}
			else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
			{
				return pBeforeOperation->getOperationNumberMain();
			}
			//Ver2.00.05 運用番号変更に対応
			else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_NumberChange)
			{
				return pBeforeOperation->getOperationNumber();
			}
			else if (pBeforeOperation->isFirstOperation())
			{
				return pBeforeOperation->getOperationNumber();
			}
		}
	}
	return vector<tstring>();
}
void CentDedRessya::splitRessyabangou(
	vector<int>& iRessyaBangou,
	vector<tstring>& strRessyaBangou) const
{
	iRessyaBangou.clear();
	strRessyaBangou.clear();

	if (m_strRessyabangou.empty())
	{
		iRessyaBangou.push_back(INT_MIN);
		strRessyaBangou.push_back(tstring());
		return;
	}

	bool bIsDigit = false;
	bool bIsNotDigit = false;
	tstring strRessyabangouTemp = m_strRessyabangou;
	while (!strRessyabangouTemp.empty())
	{
		int idx = 0;
		if (_istdigit(strRessyabangouTemp[idx]) != 0)
		{
			if ((int)strRessyabangouTemp.size() == 1)
			{
				iRessyaBangou.push_back(
					_ttoi(strRessyabangouTemp.c_str()));
				strRessyaBangou.push_back(tstring());
				break;
			}
			//数字の場合
			bIsDigit = true;
		}
		else
		{
			if ((int)strRessyabangouTemp.size() == 1)
			{
				iRessyaBangou.push_back(INT_MIN);
				strRessyaBangou.push_back(strRessyabangouTemp);
				break;
			}
			//それ以外の場合
			bIsDigit = false;
		}
		idx++;
		for (; idx < (int)strRessyabangouTemp.size(); idx++)
		{
			if (idx == (int)strRessyabangouTemp.size() - 1)
			{
				if (bIsDigit && _istdigit(strRessyabangouTemp[idx]) != 0)
				{
					iRessyaBangou.push_back(
						_ttoi(strRessyabangouTemp.c_str()));
					strRessyaBangou.push_back(tstring());

					strRessyabangouTemp.clear();
					break;
				}
				else if (!bIsDigit && _istdigit(strRessyabangouTemp[idx]) == 0)
				{
					iRessyaBangou.push_back(INT_MIN);
					strRessyaBangou.push_back(strRessyabangouTemp);

					strRessyabangouTemp.clear();
					break;
				}

			}
			if (_istdigit(strRessyabangouTemp[idx]) != 0)
			{
				//idx位置が数字で、先頭が文字の場合、先頭からidx個を文字列に返します。
				if (!bIsDigit)
				{
					iRessyaBangou.push_back(INT_MIN);
					strRessyaBangou.push_back(strRessyabangouTemp.substr(0, idx));

					strRessyabangouTemp = strRessyabangouTemp.substr(idx);
					break;
				}
			}
			else
			{
				//idx位置が文字で、先頭が数字の場合
				if (bIsDigit)
				{
					iRessyaBangou.push_back(
						_ttoi(strRessyabangouTemp.substr(0, idx).c_str()));
					strRessyaBangou.push_back(tstring());

					strRessyabangouTemp = strRessyabangouTemp.substr(idx);
					break;
				}
			}
		}
	}
}
void CentDedRessya::splitOperationNumber(
	vector<int>& iOperationNumber,
	vector<tstring>& strOperationNumber) const
{
	iOperationNumber.clear();
	strOperationNumber.clear();
	int iValidSihatsuEki = getValidSihatsuEki();
	if (iValidSihatsuEki == -1)
	{
		iOperationNumber.push_back(INT_MIN);
		strOperationNumber.push_back(tstring());
		return;
	}
	if (getOperationNumber(iValidSihatsuEki).empty())
	{
		iOperationNumber.push_back(INT_MIN);
		strOperationNumber.push_back(tstring());
		return;
	}

	bool bIsDigit = false;
	bool bIsNotDigit = false;
	tstring strOperationNumberFront = getOperationNumber(iValidSihatsuEki).front();
	while (!strOperationNumberFront.empty())
	{
		int idx = 0;
		if (_istdigit(strOperationNumberFront[idx]) != 0)
		{
			if ((int)strOperationNumberFront.size() == 1)
			{
				iOperationNumber.push_back(
					_ttoi(strOperationNumberFront.c_str()));
				strOperationNumber.push_back(tstring());
				break;
			}
			//数字の場合
			bIsDigit = true;
		}
		else
		{
			if ((int)strOperationNumberFront.size() == 1)
			{
				iOperationNumber.push_back(INT_MIN);
				strOperationNumber.push_back(strOperationNumberFront);
				break;
			}
			//それ以外の場合
			bIsDigit = false;
		}
		idx++;
		for (; idx < (int)strOperationNumberFront.size(); idx++)
		{
			if (idx == (int)strOperationNumberFront.size() - 1)
			{
				if (bIsDigit && _istdigit(strOperationNumberFront[idx]) != 0)
				{
					iOperationNumber.push_back(
						_ttoi(strOperationNumberFront.c_str()));
					strOperationNumber.push_back(tstring());

					strOperationNumberFront.clear();
					break;
				}
				else if (!bIsDigit && _istdigit(strOperationNumberFront[idx]) == 0)
				{
					iOperationNumber.push_back(INT_MIN);
					strOperationNumber.push_back(strOperationNumberFront);

					strOperationNumberFront.clear();
					break;
				}

			}
			if (_istdigit(strOperationNumberFront[idx]) != 0)
			{
				//idx位置が数字で、先頭が文字の場合
				if (!bIsDigit)
				{
					iOperationNumber.push_back(INT_MIN);
					strOperationNumber.push_back(strOperationNumberFront.substr(0, idx));

					strOperationNumberFront = strOperationNumberFront.substr(idx);
					break;
				}
			}
			else
			{
				//idx位置が文字で、先頭が数字の場合
				if (bIsDigit)
				{
					iOperationNumber.push_back(
						_ttoi(strOperationNumberFront.substr(0, idx).c_str()));
					strOperationNumber.push_back(tstring());

					strOperationNumberFront = strOperationNumberFront.substr(idx);
					break;
				}
			}
		}
	}
}
	// ********************************
	//@name CentDedRosen-子オブジェクトの増減の通知
	// ********************************

void CentDedRessya::onRessyasyubetsuInsert( int iRessyasyubetsuIndex )
{
	//△列車種別の追加(OnInsertRessyasyubetsu):　列車の列車種別インデクスは、コンテナへの追加に合わせてシフトさせる。
		
	if ( iRessyasyubetsuIndex <= m_iRessyasyubetsuIndex )
	{
		m_iRessyasyubetsuIndex ++ ;
	}
}

void CentDedRessya::onRessyasyubetsuErase( int iRessyasyubetsuIndex )
{
	//△列車種別の削除(OnEraseRessyasyubetsu):　列車の列車種別インデクスは、コンテナへの追加に合わせてシフトさせる。
	if ( iRessyasyubetsuIndex < m_iRessyasyubetsuIndex )
	{
		m_iRessyasyubetsuIndex -- ;
	}
	//  列車の列車種別インデクスが削除対象の場合、インデクスは0にする
	else if ( iRessyasyubetsuIndex == m_iRessyasyubetsuIndex )
	{
		m_iRessyasyubetsuIndex = 0 ;
	}
}

void CentDedRessya::adjustBrunchLoopByBrunchEdit(
	int iEkiOrder, bool bOriginSide,
	deque<int>& iEkiOrderBrunchOriginSide,
	deque<int>& iEkiOrderLoop,
	deque<int>& iEkiOrderBrunchTerminalSide,
	vector<int> &iOuterTerminalEkimeiMap)
{
	CentDedEkiJikoku* pEkiJikoku = getCentDedEkiJikokuCont()->getMuPtr()->get(iEkiOrder);
	//先に路線外発着の修正を行う

	pEkiJikoku->getCentDedBeforeOperationCont()->adjustOuterTerminal(iOuterTerminalEkimeiMap);
	pEkiJikoku->getCentDedAfterOperationCont()->adjustOuterTerminal(iOuterTerminalEkimeiMap);


	if (bOriginSide)
	{
		/**
			Ver2.0 同一扱いの条件の再変更
				二駅の間が、全てisRunBetweenNextEkiがfalseであること。
				起点側の一つ前と、終点側の一つ後が、停車or通過である
		*/
		if (!isRunBetweenNextEki(iEkiOrder - 1))
		{
			return;
		}

		int iHatsuEkiOrder = getRunBetweenEkiForward(iEkiOrder);
		if (iHatsuEkiOrder == -1)
		{
			return;
		}

		bool bMatch = false;
		for (int idxl = 0; idxl < (int)iEkiOrderLoop.size() && !bMatch; idxl++)
		{
			if (iEkiOrderLoop[idxl] == iHatsuEkiOrder)
			{
				bMatch = true;
			}
		}

		for (int idxt = 0; idxt < (int)iEkiOrderBrunchTerminalSide.size() && !bMatch; idxt++)
		{
			if (iEkiOrderBrunchTerminalSide[idxt] == iHatsuEkiOrder)
			{
				bMatch = true;
			}
		}
		if (bMatch)
		{
			/**
				停車・通過の場合は一つ後の駅をチェックし、停車・通過なら、
				この駅と派生駅との間で駅扱い等を確認して、必要に応じて調整を行う
				両停車:		派生着時刻と基幹発時刻がある場合は、番線の調整を行い、派生後作業と基幹前作業を削除
							いずれかが無い場合は、両駅の作業を削除
				両通過:		時刻有無に関係なく番線の調整を行う。派生着時刻と基幹発時刻がある場合は、派生後作業と基幹前作業を削除、
							いずれかが無い場合は、両駅の作業を削除
				基幹停車:	派生着時刻と基幹発時刻がある場合は、派生駅を停車にした上で番線の調整を行い、派生後作業と基幹前作業を削除。
							いずれかが無い場合は、基幹側を通過にした上で、両駅の作業を削除。
				基幹通過:	時刻有無に関係なく、派生駅を通過にした上で番線の調整を行う
							派生着時刻と基幹発時刻がある場合は、派生前作業と基幹後作業を削除、
							いずれかが無い場合は、両駅の作業を削除
			*/
			CentDedEkiJikoku* pEkiJikokuCore = getCentDedEkiJikokuCont()->getMuPtr()->get(iHatsuEkiOrder);
			if (pEkiJikoku->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya &&
				pEkiJikokuCore->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya)
			{
				//両停車
				if (!pEkiJikoku->getChakujikoku(false).isNull() &&
					!pEkiJikokuCore->getHatsujikoku(false).isNull())
				{
					if (pEkiJikoku->getRessyaTrackIndex() != pEkiJikokuCore->getRessyaTrackIndex())
					{
						pEkiJikoku->setRessyaTrackIndex(pEkiJikokuCore->getRessyaTrackIndex());
					}
					pEkiJikoku->adjustOperation(1);
					pEkiJikokuCore->adjustOperation(-1);
				}
				else
				{
					pEkiJikoku->adjustOperation(INT_MIN);
					pEkiJikokuCore->adjustOperation(INT_MIN);
				}
			}
			else if (pEkiJikoku->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka &&
				pEkiJikokuCore->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka)
			{
				//両通過
				if (pEkiJikoku->getRessyaTrackIndex() != pEkiJikokuCore->getRessyaTrackIndex())
				{
					pEkiJikoku->setRessyaTrackIndex(pEkiJikokuCore->getRessyaTrackIndex());
				}
				if (!pEkiJikoku->getChakujikoku(false).isNull() &&
					!pEkiJikokuCore->getHatsujikoku(false).isNull())
				{
					pEkiJikoku->adjustOperation(1);
					pEkiJikokuCore->adjustOperation(-1);
				}
				else
				{
					pEkiJikoku->adjustOperation(INT_MIN);
					pEkiJikokuCore->adjustOperation(INT_MIN);
				}
			}
			else if (pEkiJikoku->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka &&
				pEkiJikokuCore->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya)
			{
				//基幹停車
				if (pEkiJikoku->getRessyaTrackIndex() != pEkiJikokuCore->getRessyaTrackIndex())
				{
					pEkiJikoku->setRessyaTrackIndex(pEkiJikokuCore->getRessyaTrackIndex());
				}
				if (!pEkiJikoku->getChakujikoku(false).isNull() &&
					!pEkiJikokuCore->getHatsujikoku(false).isNull())
				{
					pEkiJikoku->setEkiatsukai(CentDedEkiJikoku::Ekiatsukai_Teisya);
					pEkiJikoku->adjustOperation(1);
					pEkiJikokuCore->adjustOperation(-1);
				}
				else
				{
					pEkiJikokuCore->setEkiatsukai(CentDedEkiJikoku::Ekiatsukai_Tsuuka);
					pEkiJikoku->adjustOperation(INT_MIN);
					pEkiJikokuCore->adjustOperation(INT_MIN);
				}
			}
			else if (pEkiJikoku->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya &&
				pEkiJikokuCore->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka)
			{
				//基幹通過
				pEkiJikoku->setEkiatsukai(CentDedEkiJikoku::Ekiatsukai_Tsuuka);
				if (pEkiJikoku->getRessyaTrackIndex() != pEkiJikokuCore->getRessyaTrackIndex())
				{
					pEkiJikoku->setRessyaTrackIndex(pEkiJikokuCore->getRessyaTrackIndex());
				}
				if (!pEkiJikoku->getChakujikoku(false).isNull() &&
					!pEkiJikokuCore->getHatsujikoku(false).isNull())
				{
					pEkiJikoku->adjustOperation(1);
					pEkiJikokuCore->adjustOperation(-1);
				}
				else
				{
					pEkiJikoku->adjustOperation(INT_MIN);
					pEkiJikokuCore->adjustOperation(INT_MIN);
				}
			}
		}

	}
	else
	{
		/**
			Ver2.0 同一扱いの条件の再変更
				二駅の間が、全てisRunBetweenNextEkiがfalseであること。
				起点側の一つ前と、終点側の一つ後が、停車or通過である
		*/
		if (!isRunBetweenNextEki(iEkiOrder))
		{
			return;
		}

		int iChakuEkiOrder = getRunBetweenEkiBackward(iEkiOrder);
		if (iChakuEkiOrder == -1)
		{
			return;
		}

		bool bMatch = false;
		for (int idxl = 0; idxl < (int)iEkiOrderLoop.size()&& !bMatch; idxl++)
		{
			if (iEkiOrderLoop[idxl] == iChakuEkiOrder)
			{
				bMatch = true;
			}
		}

		for (int idxo = 0; idxo < (int)iEkiOrderBrunchOriginSide.size() && !bMatch; idxo++)
		{
			if (iEkiOrderBrunchOriginSide[idxo] == iChakuEkiOrder)
			{
				bMatch = true;
			}
		}
		if (bMatch)
		{
			/**
				停車・通過の場合は一つ前の駅をチェックし、停車・通過なら、
				この駅と派生駅との間で駅扱い等を確認して、必要に応じて調整を行う
				両停車:		派生発時刻と基幹着時刻がある場合は、番線の調整を行い、派生前作業と基幹後作業を削除
							いずれかが無い場合は、両駅の作業を削除
				両通過:		時刻有無に関係なく番線の調整を行う。派生発時刻と基幹着時刻がある場合は、派生前作業と基幹後作業を削除、
							いずれかが無い場合は、両駅の作業を削除
				基幹停車:	派生発時刻と基幹着時刻が有る場合は、派生駅を停車にした上で番線の調整を行う、派生前作業と基幹後作業を削除。
							いずれかが無い場合は、基幹側を通過にした上で、両駅の作業を削除。
				基幹通過:	時刻有無に関係なく、派生駅を通過にした上で番線の調整を行う。
							派生発時刻と基幹着時刻がある場合は、派生前作業と基幹後作業を削除、
							いずれかが無い場合は、両駅の作業を削除
			*/
			CentDedEkiJikoku* pEkiJikokuCore = getCentDedEkiJikokuCont()->getMuPtr()->get(iChakuEkiOrder);
			if (pEkiJikoku->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya &&
				pEkiJikokuCore->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya)
			{
				//両停車
				if (!pEkiJikoku->getHatsujikoku(false).isNull() &&
					!pEkiJikokuCore->getChakujikoku(false).isNull())
				{
					if (pEkiJikoku->getRessyaTrackIndex() != pEkiJikokuCore->getRessyaTrackIndex())
					{
						pEkiJikoku->setRessyaTrackIndex(pEkiJikokuCore->getRessyaTrackIndex());
					}
					pEkiJikokuCore->adjustOperation(1);
					pEkiJikoku->adjustOperation(-1);
				}
				else
				{
					pEkiJikokuCore->adjustOperation(INT_MIN);
					pEkiJikoku->adjustOperation(INT_MIN);
				}
			}
			else if (pEkiJikoku->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka &&
				pEkiJikokuCore->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka)
			{
				//両通過
				if (pEkiJikoku->getRessyaTrackIndex() != pEkiJikokuCore->getRessyaTrackIndex())
				{
					pEkiJikoku->setRessyaTrackIndex(pEkiJikokuCore->getRessyaTrackIndex());
				}
				if (!pEkiJikoku->getHatsujikoku(false).isNull() &&
					!pEkiJikokuCore->getChakujikoku(false).isNull())
				{
					pEkiJikokuCore->adjustOperation(1);
					pEkiJikoku->adjustOperation(-1);
				}
				else
				{
					pEkiJikokuCore->adjustOperation(INT_MIN);
					pEkiJikoku->adjustOperation(INT_MIN);
				}
			}
			else if (pEkiJikoku->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka &&
				pEkiJikokuCore->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya)
			{
				//基幹停車
				if (pEkiJikoku->getRessyaTrackIndex() != pEkiJikokuCore->getRessyaTrackIndex())
				{
					pEkiJikoku->setRessyaTrackIndex(pEkiJikokuCore->getRessyaTrackIndex());
				}
				if (!pEkiJikoku->getHatsujikoku(false).isNull() &&
					!pEkiJikokuCore->getChakujikoku(false).isNull())
				{
					pEkiJikoku->setEkiatsukai(CentDedEkiJikoku::Ekiatsukai_Teisya);
					pEkiJikokuCore->adjustOperation(1);
					pEkiJikoku->adjustOperation(-1);
				}
				else
				{
					pEkiJikokuCore->setEkiatsukai(CentDedEkiJikoku::Ekiatsukai_Tsuuka);
					pEkiJikokuCore->adjustOperation(INT_MIN);
					pEkiJikoku->adjustOperation(INT_MIN);
				}
			}
			else if (pEkiJikoku->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya &&
				pEkiJikokuCore->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka)
			{
				//基幹通過
				pEkiJikoku->setEkiatsukai(CentDedEkiJikoku::Ekiatsukai_Tsuuka);
				if (pEkiJikoku->getRessyaTrackIndex() != pEkiJikokuCore->getRessyaTrackIndex())
				{
					pEkiJikoku->setRessyaTrackIndex(pEkiJikokuCore->getRessyaTrackIndex());
				}
				if (!pEkiJikoku->getHatsujikoku(false).isNull() &&
					!pEkiJikokuCore->getChakujikoku(false).isNull())
				{
					pEkiJikokuCore->adjustOperation(1);
					pEkiJikoku->adjustOperation(-1);
				}
				else
				{
					pEkiJikokuCore->adjustOperation(INT_MIN);
					pEkiJikoku->adjustOperation(INT_MIN);
				}
			}
		}
	}
}


void CentDedRessya::adjustBrunchLoopByLoopEdit(
	int iEkiOrder, int iPosition,
	deque<int>& iEkiOrderBrunchOriginSide,
	deque<int>& iEkiOrderLoop,
	deque<int>& iEkiOrderBrunchTerminalSide,
	vector<int> &iOuterTerminalEkimeiMap)
{

	if (getRessyahoukou() == Ressyahoukou_Kudari)
	{
		CentDedEkiJikoku* pEkiJikoku = getCentDedEkiJikokuCont()->getMuPtr()->get(iEkiOrder);
		//先に路線外発着の修正を行う、下り列車の場合は列車の終点側を修正する
		for (int idxl = iPosition; idxl < (int)iEkiOrderLoop.size(); idxl++)
		{
			CentDedEkiJikoku* pEkiJikokuTarget = getCentDedEkiJikokuCont()->getMuPtr()->get(iEkiOrderLoop[idxl]);
			pEkiJikokuTarget->getCentDedBeforeOperationCont()->adjustOuterTerminal(iOuterTerminalEkimeiMap);
			pEkiJikokuTarget->getCentDedAfterOperationCont()->adjustOuterTerminal(iOuterTerminalEkimeiMap);
		}
		for (int idxt = 0; idxt < (int)iEkiOrderBrunchTerminalSide.size(); idxt++)
		{
			CentDedEkiJikoku* pEkiJikokuTarget = getCentDedEkiJikokuCont()->getMuPtr()->get(iEkiOrderBrunchTerminalSide[idxt]);
			pEkiJikokuTarget->getCentDedBeforeOperationCont()->adjustOuterTerminal(iOuterTerminalEkimeiMap);
			pEkiJikokuTarget->getCentDedAfterOperationCont()->adjustOuterTerminal(iOuterTerminalEkimeiMap);
		}

		//下り列車の場合は、列車の起点側を基準に、終点側を修正する
		/**
			Ver2.0 同一扱いの条件の再変更
				二駅の間が、全てisRunBetweenNextEkiがfalseであること。
				起点側の一つ前と、終点側の一つ後が、停車or通過である

			Ver2.0同一扱いの条件を、二駅間が基本経由無しの場合に厳格化。
			ただし、途中のグループ駅のみ停車・通過を許容する。
			加えて、停車・通過でも前後が共に経由無し・運行無しの場合は、無視する
			(1)派生側有効条件　	(a)当駅の一つ後の駅が停車または通過・停車の場合は当駅に発時刻が有る
			(2)基幹側有効条件	(a)派生駅の前から基幹駅及び逆側派生駅までの間が経由無し
								(b)基幹側が停車・通過で着時刻あり
								(c)基幹側の前の駅が、停車または通過
		*/

		CentDedEkiJikoku* pEkiJikokuHatsu = NULL;

		bool bMatchHatsu = false;
		if (isRunBetweenNextEki(iEkiOrder))
		{
			pEkiJikokuHatsu = getCentDedEkiJikokuCont()->getMuPtr()->get(iEkiOrder);
			bMatchHatsu = true;
		}
		int iHatsuEkiOrder;
		if (!bMatchHatsu)
		{
			iHatsuEkiOrder = getRunBetweenEkiBackward(iEkiOrder);
			if (iHatsuEkiOrder == -1)
			{
				return;
			}
		}
		if (!bMatchHatsu)
		{
			for (int idxl = 0; idxl < (int)iEkiOrderLoop.size() && !bMatchHatsu; idxl++)
			{
				if (iEkiOrderLoop[idxl] == iHatsuEkiOrder)
				{
					bMatchHatsu = true;
				}
			}

			for (int idxt = 0; idxt < (int)iEkiOrderBrunchTerminalSide.size() && !bMatchHatsu; idxt++)
			{
				if (iEkiOrderBrunchTerminalSide[idxt] == iHatsuEkiOrder)
				{
					bMatchHatsu = true;
				}
			}
			if (bMatchHatsu)
			{
				pEkiJikokuHatsu = getCentDedEkiJikokuCont()->getMuPtr()->get(iHatsuEkiOrder);
			}
			else
			{
				return;
			}
		}

		if (isRunBetweenNextEki(iEkiOrder - 1))
		{
			return;
		}
		int iChakuEkiOrder = getRunBetweenEkiBackward(iEkiOrder);
		if (iChakuEkiOrder == -1)
		{
			return;
		}
		bool bMatchChaku = false;
		for (int idxl = 0; idxl < (int)iEkiOrderLoop.size() && !bMatchChaku; idxl++)
		{
			if (iEkiOrderLoop[idxl] == iChakuEkiOrder)
			{
				bMatchChaku = true;
			}
		}

		for (int idxo = 0; idxo < (int)iEkiOrderBrunchOriginSide.size() && !bMatchChaku; idxo++)
		{
			if (iEkiOrderBrunchOriginSide[idxo] == iChakuEkiOrder)
			{
				bMatchChaku = true;
			}
		}
		CentDedEkiJikoku* pEkiJikokuChaku = NULL;
		if (bMatchChaku)
		{
			pEkiJikokuChaku= getCentDedEkiJikokuCont()->getMuPtr()->get(iChakuEkiOrder);
		}
		else
		{
			return;
		}

		if (pEkiJikokuChaku != NULL &&
			pEkiJikokuHatsu != NULL)
		{
			/**
				起点側駅と終点側駅との間で駅扱い等を確認して、必要に応じて調整を行う
				両停車:		起点側着時刻と終点側発時刻がある場合は、番線の調整を行い、起点側後作業と終点側前作業を削除、
							いずれかが無い場合は、両駅の作業を削除
				両通過:		時刻有無に関係なく番線の調整を行う。起点側着時刻と終点側発時刻がある場合は、起点側後作業と終点側前作業を削除、
							いずれかが無い場合は、両駅の作業を削除
				起点側停車:	起点側着時刻と終点側発時刻が有る場合は、終点側駅を停車にした上で番線の調整を行い、起点側後作業と終点側前作業を削除、
						いずれかが無い場合は、起点側駅を停車にした上で、両駅の作業を削除。
							いずれかが無い場合はそのまま。
				起点側通過:	時刻有無に関係なく、終点側駅を通過にした上で番線の調整を行う。
							起点側着時刻と終点側発時刻がある場合は、起点側後作業と終点側前作業を削除、
							いずれかが無い場合は、両駅の作業を削除
			*/
			if (pEkiJikokuHatsu->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya &&
				pEkiJikokuChaku->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya)
			{
				//両停車
				if (!pEkiJikokuHatsu->getHatsujikoku(false).isNull() &&
					!pEkiJikokuChaku->getChakujikoku(false).isNull())
				{
					if (pEkiJikokuHatsu->getRessyaTrackIndex() != pEkiJikokuChaku->getRessyaTrackIndex())
					{
						pEkiJikokuHatsu->setRessyaTrackIndex(pEkiJikokuChaku->getRessyaTrackIndex());
					}
					pEkiJikokuChaku->adjustOperation(1);
					pEkiJikokuHatsu->adjustOperation(-1);
				}
				else
				{
					pEkiJikokuChaku->adjustOperation(INT_MIN);
					pEkiJikokuHatsu->adjustOperation(INT_MIN);
				}
			}
			else if (pEkiJikokuHatsu->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka &&
				pEkiJikokuChaku->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka)
			{
				//両通過
				if (pEkiJikokuHatsu->getRessyaTrackIndex() != pEkiJikokuChaku->getRessyaTrackIndex())
				{
					pEkiJikokuHatsu->setRessyaTrackIndex(pEkiJikokuChaku->getRessyaTrackIndex());
				}
				if (!pEkiJikokuHatsu->getHatsujikoku(false).isNull() &&
					!pEkiJikokuChaku->getChakujikoku(false).isNull())
				{
					pEkiJikokuChaku->adjustOperation(1);
					pEkiJikokuHatsu->adjustOperation(-1);
				}
				else
				{
					pEkiJikokuChaku->adjustOperation(INT_MIN);
					pEkiJikokuHatsu->adjustOperation(INT_MIN);
				}
			}
			else if (pEkiJikokuHatsu->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka &&
				pEkiJikokuChaku->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya)
			{
				//起点側停車
				if (pEkiJikokuHatsu->getRessyaTrackIndex() != pEkiJikokuChaku->getRessyaTrackIndex())
				{
					pEkiJikokuHatsu->setRessyaTrackIndex(pEkiJikokuChaku->getRessyaTrackIndex());
				}
				if (!pEkiJikokuHatsu->getHatsujikoku(false).isNull() &&
					!pEkiJikokuChaku->getChakujikoku(false).isNull())
				{
					pEkiJikokuHatsu->setEkiatsukai(CentDedEkiJikoku::Ekiatsukai_Teisya);
					pEkiJikokuChaku->adjustOperation(1);
					pEkiJikokuHatsu->adjustOperation(-1);
				}
				else
				{
					pEkiJikokuChaku->setEkiatsukai(CentDedEkiJikoku::Ekiatsukai_Tsuuka);
					pEkiJikokuChaku->adjustOperation(INT_MIN);
					pEkiJikokuHatsu->adjustOperation(INT_MIN);
				}
			}
			else if (pEkiJikokuHatsu->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya &&
				pEkiJikokuChaku->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka)
			{
				//起点側通過
				pEkiJikokuHatsu->setEkiatsukai(CentDedEkiJikoku::Ekiatsukai_Tsuuka);
				if (pEkiJikokuHatsu->getRessyaTrackIndex() != pEkiJikokuChaku->getRessyaTrackIndex())
				{
					pEkiJikokuHatsu->setRessyaTrackIndex(pEkiJikokuChaku->getRessyaTrackIndex());
				}
				if (!pEkiJikokuHatsu->getHatsujikoku(false).isNull() &&
					!pEkiJikokuChaku->getChakujikoku(false).isNull())
				{
					pEkiJikokuChaku->adjustOperation(1);
					pEkiJikokuHatsu->adjustOperation(-1);
				}
				else
				{
					pEkiJikokuChaku->adjustOperation(INT_MIN);
					pEkiJikokuHatsu->adjustOperation(INT_MIN);
				}
			}
		}
	}
	else
	{
		CentDedEkiJikoku* pEkiJikoku = getCentDedEkiJikokuCont()->getMuPtr()->get(iEkiOrder);
		//先に路線外発着の修正を行う、上り列車の場合は列車の起点側を修正する
		for (int idxl = iPosition - 1; idxl >= 0; idxl--)
		{
			CentDedEkiJikoku* pEkiJikokuTarget = getCentDedEkiJikokuCont()->getMuPtr()->get(iEkiOrderLoop[idxl]);
			pEkiJikokuTarget->getCentDedBeforeOperationCont()->adjustOuterTerminal(iOuterTerminalEkimeiMap);
			pEkiJikokuTarget->getCentDedAfterOperationCont()->adjustOuterTerminal(iOuterTerminalEkimeiMap);
		}
		for (int idxo = 0; idxo < (int)iEkiOrderBrunchOriginSide.size(); idxo++)
		{
			CentDedEkiJikoku* pEkiJikokuTarget = getCentDedEkiJikokuCont()->getMuPtr()->get(iEkiOrderBrunchOriginSide[idxo]);
			pEkiJikokuTarget->getCentDedBeforeOperationCont()->adjustOuterTerminal(iOuterTerminalEkimeiMap);
			pEkiJikokuTarget->getCentDedAfterOperationCont()->adjustOuterTerminal(iOuterTerminalEkimeiMap);
		}

		//上り列車の場合は、列車の終点側を基準に、起点側を修正する
		bool bContinue = true;
		/**
			Ver2.0同一扱いの条件を、二駅間が基本経由無しの場合に厳格化。
			ただし、途中のグループ駅のみ停車・通過を許容する。
			加えて、停車・通過でも前後が共に経由無し・運行無しの場合は、無視する
			(1)派生側有効条件　	(a)当駅の一つ後の駅が停車または通過・停車の場合は当駅に発時刻が有る
			(2)基幹側有効条件	(a)派生駅の前から基幹駅及び逆側派生駅までの間が経由無し
								(b)基幹側が停車・通過で着時刻あり
								(c)基幹側の前の駅が、停車または通過
		*/

		CentDedEkiJikoku* pEkiJikokuChaku = NULL;

		bool bMatchChaku = false;
		if (isRunBetweenNextEki(iEkiOrder-1))
		{
			pEkiJikokuChaku = getCentDedEkiJikokuCont()->getMuPtr()->get(iEkiOrder);
			bMatchChaku = true;
		}
		int iChakuEkiOrder;
		if (!bMatchChaku)
		{
			iChakuEkiOrder = getRunBetweenEkiBackward(iEkiOrder);
			if (iChakuEkiOrder == -1)
			{
				return;
			}
		}
		if (!bMatchChaku)
		{
			for (int idxl = 0; idxl < (int)iEkiOrderLoop.size() && !bMatchChaku; idxl++)
			{
				if (iEkiOrderLoop[idxl] == iChakuEkiOrder)
				{
					bMatchChaku = true;
				}
			}

			for (int idxo = 0; idxo < (int)iEkiOrderBrunchOriginSide.size() && !bMatchChaku; idxo++)
			{
				if (iEkiOrderBrunchOriginSide[idxo] == iChakuEkiOrder)
				{
					bMatchChaku = true;
				}
			}
			if (bMatchChaku)
			{
				pEkiJikokuChaku = getCentDedEkiJikokuCont()->getMuPtr()->get(iChakuEkiOrder);
			}
			else
			{
				return;
			}
		}

		if (isRunBetweenNextEki(iEkiOrder))
		{
			return;
		}
		int iHatsuEkiOrder = getRunBetweenEkiForward(iEkiOrder);
		if (iHatsuEkiOrder == -1)
		{
			return;
		}
		bool bMatchHatsu = false;
		for (int idxl = 0; idxl < (int)iEkiOrderLoop.size() && !bMatchHatsu; idxl++)
		{
			if (iEkiOrderLoop[idxl] == iHatsuEkiOrder)
			{
				bMatchHatsu = true;
			}
		}

		for (int idxt = 0; idxt < (int)iEkiOrderBrunchTerminalSide.size() && !bMatchHatsu; idxt++)
		{
			if (iEkiOrderBrunchTerminalSide[idxt] == iHatsuEkiOrder)
			{
				bMatchHatsu = true;
			}
		}
		CentDedEkiJikoku* pEkiJikokuHatsu = NULL;
		if (bMatchHatsu)
		{
			pEkiJikokuHatsu = getCentDedEkiJikokuCont()->getMuPtr()->get(iHatsuEkiOrder);
		}
		else
		{
			return;
		}

		if (pEkiJikokuChaku != NULL &&
			pEkiJikokuHatsu != NULL)
		{
			/**
				起点側駅と終点側駅との間で駅扱い等を確認して、必要に応じて調整を行う
				両停車:		起点側着時刻と終点側発時刻がある場合は、番線の調整を行い、起点側後作業と終点側前作業を削除、
							いずれかが無い場合は、両駅の作業を削除
				両通過:		時刻有無に関係なく番線の調整を行う。起点側着時刻と終点側発時刻がある場合は、起点側後作業と終点側前作業を削除、
							いずれかが無い場合は、両駅の作業を削除
				終点側停車:	起点側着時刻と終点側発時刻が有る場合は、起点側駅を停車にした上で番線の調整を行い、起点側後作業と終点側前作業を削除、
						いずれかが無い場合は、終点側駅を停車にした上で、両駅の作業を削除。
							いずれかが無い場合はそのまま。
				終点側通過:	時刻有無に関係なく、起点側駅を通過にした上で番線の調整を行う。
							起点側着時刻と終点側発時刻がある場合は、起点側後作業と終点側前作業を削除、
							いずれかが無い場合は、両駅の作業を削除
			*/
			if (pEkiJikokuHatsu->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya &&
				pEkiJikokuChaku->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya)
			{
				//両停車
				if (!pEkiJikokuHatsu->getHatsujikoku(false).isNull() &&
					!pEkiJikokuChaku->getChakujikoku(false).isNull())
				{
					if (pEkiJikokuHatsu->getRessyaTrackIndex() != pEkiJikokuChaku->getRessyaTrackIndex())
					{
						pEkiJikokuChaku->setRessyaTrackIndex(pEkiJikokuHatsu->getRessyaTrackIndex());
					}
					pEkiJikokuChaku->adjustOperation(1);
					pEkiJikokuHatsu->adjustOperation(-1);
				}
				else
				{
					pEkiJikokuChaku->adjustOperation(INT_MIN);
					pEkiJikokuHatsu->adjustOperation(INT_MIN);
				}
			}
			else if (pEkiJikokuHatsu->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka &&
				pEkiJikokuChaku->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka)
			{
				//両通過
				if (pEkiJikokuHatsu->getRessyaTrackIndex() != pEkiJikokuChaku->getRessyaTrackIndex())
				{
					pEkiJikokuChaku->setRessyaTrackIndex(pEkiJikokuHatsu->getRessyaTrackIndex());
				}
				if (!pEkiJikokuHatsu->getHatsujikoku(false).isNull() &&
					!pEkiJikokuChaku->getChakujikoku(false).isNull())
				{
					pEkiJikokuChaku->adjustOperation(1);
					pEkiJikokuHatsu->adjustOperation(-1);
				}
				else
				{
					pEkiJikokuChaku->adjustOperation(INT_MIN);
					pEkiJikokuHatsu->adjustOperation(INT_MIN);
				}
			}
			else if (pEkiJikokuHatsu->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya &&
				pEkiJikokuChaku->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka)
			{
				//終点側停車
				if (pEkiJikokuHatsu->getRessyaTrackIndex() != pEkiJikokuChaku->getRessyaTrackIndex())
				{
					pEkiJikokuChaku->setRessyaTrackIndex(pEkiJikokuHatsu->getRessyaTrackIndex());
				}
				if (!pEkiJikokuHatsu->getHatsujikoku(false).isNull() &&
					!pEkiJikokuChaku->getChakujikoku(false).isNull())
				{
					pEkiJikokuChaku->setEkiatsukai(CentDedEkiJikoku::Ekiatsukai_Teisya);
					pEkiJikokuChaku->adjustOperation(1);
					pEkiJikokuHatsu->adjustOperation(-1);
				}
				else
				{
					pEkiJikokuHatsu->setEkiatsukai(CentDedEkiJikoku::Ekiatsukai_Tsuuka);
					pEkiJikokuChaku->adjustOperation(INT_MIN);
					pEkiJikokuHatsu->adjustOperation(INT_MIN);
				}
			}
			else if (pEkiJikokuHatsu->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka &&
				pEkiJikokuChaku->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya)
			{
				//終点側通過
				pEkiJikokuChaku->setEkiatsukai(CentDedEkiJikoku::Ekiatsukai_Tsuuka);
				if (pEkiJikokuHatsu->getRessyaTrackIndex() != pEkiJikokuChaku->getRessyaTrackIndex())
				{
					pEkiJikokuChaku->setRessyaTrackIndex(pEkiJikokuHatsu->getRessyaTrackIndex());
				}
				if (!pEkiJikokuHatsu->getHatsujikoku(false).isNull() &&
					!pEkiJikokuChaku->getChakujikoku(false).isNull())
				{
					pEkiJikokuChaku->adjustOperation(1);
					pEkiJikokuHatsu->adjustOperation(-1);
				}
				else
				{
					pEkiJikokuChaku->adjustOperation(INT_MIN);
					pEkiJikokuHatsu->adjustOperation(INT_MIN);
				}
			}
		}
	}
}

void CentDedRessya::adjustBrunchLoopByEkijikokuEdit(
	int iEkiOrder,
	deque<int>& iEkiOrderBrunchOriginSide,
	deque<int>& iEkiOrderLoop,
	deque<int>& iEkiOrderBrunchTerminalSide,
	deque<int>& iEkiOrderTeisyaTsuuka,
	int iEkiOrderPosition, bool bPriority)
{
	CentDedEkiJikoku* pEkiJikoku = getCentDedEkiJikokuCont()->getMuPtr()->get(iEkiOrder);
	if (iEkiOrderPosition == INT_MIN)
	{
		//起点方派生駅の場合
		if (!isRunBetweenNextEki(iEkiOrder - 1))
		{
			//前駅とこの駅間が運転無しなら、作業の必要なし
			return;
		}

		int iHatsuEkiOrder = getRunBetweenEkiForward(iEkiOrder);
		if (iHatsuEkiOrder == -1)
		{
			return;
		}

		bool bMatch = false;
		for (int idxl = 0; idxl < (int)iEkiOrderLoop.size() && !bMatch; idxl++)
		{
			if (iEkiOrderLoop[idxl] == iHatsuEkiOrder)
			{
				bMatch = true;
			}
		}

		for (int idxt = 0; idxt < (int)iEkiOrderBrunchTerminalSide.size() && !bMatch; idxt++)
		{
			if (iEkiOrderBrunchTerminalSide[idxt] == iHatsuEkiOrder)
			{
				bMatch = true;
			}
		}
		if (bMatch)
		{
			//駅扱い等と番線の調整を行う
			CentDedEkiJikoku* pEkiJikokuHatsu = getCentDedEkiJikokuCont()->getMuPtr()->get(iHatsuEkiOrder);
			if (pEkiJikokuHatsu->getEkiatsukai() != pEkiJikoku->getEkiatsukai())
			{
				pEkiJikokuHatsu->setEkiatsukai(pEkiJikoku->getEkiatsukai());
			}
			if (pEkiJikokuHatsu->getRessyaTrackIndex() != pEkiJikoku->getRessyaTrackIndex())
			{
				//Priorityについては要検討
				if (bPriority)
				{
					pEkiJikokuHatsu->setRessyaTrackIndex(pEkiJikoku->getRessyaTrackIndex());
				}
				else
				{
					pEkiJikoku->setRessyaTrackIndex(pEkiJikokuHatsu->getRessyaTrackIndex());
				}
			}
			iEkiOrderTeisyaTsuuka.push_back(iHatsuEkiOrder);
			return;
		}
	}
	else if (iEkiOrderPosition == INT_MAX)
	{

		if (!isRunBetweenNextEki(iEkiOrder))
		{
			//次駅とこの駅間が運転無しなら、作業の必要なし
			return;
		}

		int iChakuEkiOrder = getRunBetweenEkiBackward(iEkiOrder);
		if (iChakuEkiOrder == -1)
		{
			return;
		}

		bool bMatch = false;
		for (int idxl = 0; idxl < (int)iEkiOrderLoop.size() && !bMatch; idxl++)
		{
			if (iEkiOrderLoop[idxl] == iChakuEkiOrder)
			{
				bMatch = true;
			}
		}

		for (int idxo = 0; idxo < (int)iEkiOrderBrunchOriginSide.size() && !bMatch; idxo++)
		{
			if (iEkiOrderBrunchOriginSide[idxo] == iChakuEkiOrder)
			{
				bMatch = true;
			}
		}
		if (bMatch)
		{
			//駅扱い等と番線の調整を行う
			CentDedEkiJikoku* pEkiJikokuChaku =
				getCentDedEkiJikokuCont()->getMuPtr()->get(iChakuEkiOrder);
			if (pEkiJikokuChaku->getEkiatsukai() != pEkiJikoku->getEkiatsukai())
			{
				pEkiJikokuChaku->setEkiatsukai(pEkiJikoku->getEkiatsukai());
			}
			if (pEkiJikokuChaku->getRessyaTrackIndex() != pEkiJikoku->getRessyaTrackIndex())
			{
				//Priorityについては要検討
				if (bPriority)
				{
					pEkiJikokuChaku->setRessyaTrackIndex(pEkiJikoku->getRessyaTrackIndex());
				}
				else
				{
					pEkiJikoku->setRessyaTrackIndex(pEkiJikokuChaku->getRessyaTrackIndex());
				}
			}
			iEkiOrderTeisyaTsuuka.push_back(iChakuEkiOrder);
			return;
		}
	}
	else
	{
		//基幹駅 前後とも停車・通過の場合は、調整の必要なし。
		//前後とも経由無し・運行無しの場合も、調整の必要なし。
		if (isRunBetweenNextEki(iEkiOrder) ==
			isRunBetweenNextEki(iEkiOrder - 1))
		{
			return;
		}
		else if (isRunBetweenNextEki(iEkiOrder))
		{

			int iChakuEkiOrder = getRunBetweenEkiBackward(iEkiOrder);
			if (iChakuEkiOrder == -1)
			{
				return;
			}

			bool bMatch = false;
			for (int idxl = 0; idxl < (int)iEkiOrderLoop.size() && !bMatch; idxl++)
			{
				if (iEkiOrderLoop[idxl] == iChakuEkiOrder)
				{
					bMatch = true;
				}
			}

			for (int idxo = 0; idxo < (int)iEkiOrderBrunchOriginSide.size() && !bMatch; idxo++)
			{
				if (iEkiOrderBrunchOriginSide[idxo] == iChakuEkiOrder)
				{
					bMatch = true;
				}
			}
			if (bMatch)
			{
				//駅扱い等と番線の調整を行う
				CentDedEkiJikoku* pEkiJikokuChaku =
					getCentDedEkiJikokuCont()->getMuPtr()->get(iChakuEkiOrder);
				if (pEkiJikokuChaku->getEkiatsukai() != pEkiJikoku->getEkiatsukai())
				{
					pEkiJikokuChaku->setEkiatsukai(pEkiJikoku->getEkiatsukai());
				}
				if (pEkiJikokuChaku->getRessyaTrackIndex() != pEkiJikoku->getRessyaTrackIndex())
				{
					//Priorityについては要検討
					if (bPriority)
					{
						pEkiJikokuChaku->setRessyaTrackIndex(pEkiJikoku->getRessyaTrackIndex());
					}
					else
					{
						pEkiJikoku->setRessyaTrackIndex(pEkiJikokuChaku->getRessyaTrackIndex());
					}
				}
				iEkiOrderTeisyaTsuuka.push_back(iChakuEkiOrder);
				return;
			}
		}
		else
		{
			int iHatsuEkiOrder = getRunBetweenEkiForward(iEkiOrder);
			if (iHatsuEkiOrder == -1)
			{
				return;
			}

			bool bMatch = false;
			for (int idxl = 0; idxl < (int)iEkiOrderLoop.size() && !bMatch; idxl++)
			{
				if (iEkiOrderLoop[idxl] == iHatsuEkiOrder)
				{
					bMatch = true;
				}
			}

			for (int idxt = 0; idxt < (int)iEkiOrderBrunchTerminalSide.size() && !bMatch; idxt++)
			{
				if (iEkiOrderBrunchTerminalSide[idxt] == iHatsuEkiOrder)
				{
					bMatch = true;
				}
			}
			if (bMatch)
			{
				//駅扱い等と番線の調整を行う
				CentDedEkiJikoku* pEkiJikokuHatsu = getCentDedEkiJikokuCont()->getMuPtr()->get(iHatsuEkiOrder);
				if (pEkiJikokuHatsu->getEkiatsukai() != pEkiJikoku->getEkiatsukai())
				{
					pEkiJikokuHatsu->setEkiatsukai(pEkiJikoku->getEkiatsukai());
				}
				if (pEkiJikokuHatsu->getRessyaTrackIndex() != pEkiJikoku->getRessyaTrackIndex())
				{
					//Priorityについては要検討
					if (bPriority)
					{
						pEkiJikokuHatsu->setRessyaTrackIndex(pEkiJikoku->getRessyaTrackIndex());
					}
					else
					{
						pEkiJikoku->setRessyaTrackIndex(pEkiJikokuHatsu->getRessyaTrackIndex());
					}
				}
				iEkiOrderTeisyaTsuuka.push_back(iHatsuEkiOrder);
				return;
			}
		}
	}
}

void CentDedRessya::adjustBrunchConvert(const CentDedEkiCont* pCentDedEkiCont)
{
	if (getSihatsuEki() == -1 || isNull())
	{
		return;
	}
	/**
		始発駅から終着駅の間で、停車通過→停車通過(A)→一つ以上の運行なし→停車通過(B)→停車通過
		の並びがある場合、(A)駅と(B)駅が分岐駅関係にあるかどうかを調べ、
		分岐駅関係なら駅扱いを統一します。
		駅扱いが異なっている場合、(A)駅の着時刻と(B)駅の発時刻のうち一つでもNULL時刻なら駅扱いを通過に、
		両時刻ともある場合は、駅扱いを停車に統一します。
	
	*/
	for (int iEkiOrder = getRunFirstEkiOrder()+1; iEkiOrder < getSyuuchakuEki(); iEkiOrder++)
	{
		if (!isRunBetweenNextEki(iEkiOrder) && iEkiOrder != getSihatsuEki())
		{
			int iHatsuEkiOrder = getRunBetweenEkiForward(iEkiOrder);
			if (iHatsuEkiOrder == -1)
			{
				return;
			}
			if (pCentDedEkiCont->isSameBrunchLoopGroup(iEkiOrder, iHatsuEkiOrder, getRessyahoukou()))
			{
				CentDedEkiJikoku* pChakuEkiJikoku = getCentDedEkiJikokuCont()->getMuPtr()->get(iEkiOrder);
				CentDedEkiJikoku* pHatsuEkiJikoku = getCentDedEkiJikokuCont()->getMuPtr()->get(iHatsuEkiOrder);
				if (pChakuEkiJikoku->getEkiatsukai() != pHatsuEkiJikoku->getEkiatsukai())
				{
					if (pChakuEkiJikoku->getChakujikoku().isNull() ||
						pHatsuEkiJikoku->getHatsujikoku().isNull())
					{
						pChakuEkiJikoku->setEkiatsukai(CentDedEkiJikoku::Ekiatsukai_Tsuuka);
						pHatsuEkiJikoku->setEkiatsukai(CentDedEkiJikoku::Ekiatsukai_Tsuuka);
					}
					else
					{
						pChakuEkiJikoku->setEkiatsukai(CentDedEkiJikoku::Ekiatsukai_Teisya);
						pHatsuEkiJikoku->setEkiatsukai(CentDedEkiJikoku::Ekiatsukai_Teisya);
					}
				}
			}
			iEkiOrder = iHatsuEkiOrder;
		}
	}
}

void CentDedRessya::adjustBrunchLoopForTransferSort(
	deque<int>& iEkiOrderBrunchOriginSide,
	deque<int>& iEkiOrderLoop,
	deque<int>& iEkiOrderBrunchTerminalSide)
{
	
	m_CentDedEkiJikokuCont.adjustBrunchLoopForTransferSort(
		 iEkiOrderBrunchOriginSide,
		iEkiOrderLoop, iEkiOrderBrunchTerminalSide);
}

void CentDedRessya::adjustBrunchLoopEkiTrack2(
	const deque<int>& iEkiOrderBrunchLoop, 
	const std::vector<int>& iEkiTrack2Map)
{
	m_CentDedEkiJikokuCont.adjustBrunchLoopEkiTrack2(
		iEkiOrderBrunchLoop, iEkiTrack2Map);
}

void CentDedRessya::adjustBrunchLoopOuterTerminal(
	const deque<int>& iEkiOrderBrunchLoop,
	const std::vector<int>& iOuterTerminalEkimeiMap)
{
	m_CentDedEkiJikokuCont.adjustBrunchLoopOuterTerminal(
		iEkiOrderBrunchLoop, iOuterTerminalEkimeiMap);
}

void CentDedRessya::mergeOuterTerminal(
	const deque<int>& iEkiOrderBrunchOriginSide, 
	const deque<int>& iEkiOrderLoop, 
	const deque<int>& iEkiOrderBrunchTerminalSide, 
	const vector<vector<int>>& iOuterTerminalMapCont)
{
	for (int idxo = 0; idxo < (int)iEkiOrderBrunchOriginSide.size(); idxo++)
	{
		if (iOuterTerminalMapCont[iEkiOrderBrunchOriginSide[idxo]].empty())
		{
			continue;
		}
		CentDedEkiJikoku* pEkiJikokuTarget = getCentDedEkiJikokuCont()->getMuPtr()->get(iEkiOrderBrunchOriginSide[idxo]);
		pEkiJikokuTarget->getCentDedBeforeOperationCont()->adjustOuterTerminal(iOuterTerminalMapCont[iEkiOrderBrunchOriginSide[idxo]]);
		pEkiJikokuTarget->getCentDedAfterOperationCont()->adjustOuterTerminal(iOuterTerminalMapCont[iEkiOrderBrunchOriginSide[idxo]]);
	}
	for (int idxl = 0; idxl < (int)iEkiOrderLoop.size(); idxl++)
	{
		if (iOuterTerminalMapCont[iEkiOrderLoop[idxl]].empty())
		{
			continue;
		}
		CentDedEkiJikoku* pEkiJikokuTarget = getCentDedEkiJikokuCont()->getMuPtr()->get(iEkiOrderLoop[idxl]);
		pEkiJikokuTarget->getCentDedBeforeOperationCont()->adjustOuterTerminal(iOuterTerminalMapCont[iEkiOrderLoop[idxl]]);
		pEkiJikokuTarget->getCentDedAfterOperationCont()->adjustOuterTerminal(iOuterTerminalMapCont[iEkiOrderLoop[idxl]]);
	}
	for (int idxt = 0; idxt < (int)iEkiOrderBrunchTerminalSide.size(); idxt++)
	{
		if (iOuterTerminalMapCont[iEkiOrderBrunchTerminalSide[idxt]].empty())
		{
			continue;
		}
		CentDedEkiJikoku* pEkiJikokuTarget = getCentDedEkiJikokuCont()->getMuPtr()->get(iEkiOrderBrunchTerminalSide[idxt]);
		pEkiJikokuTarget->getCentDedBeforeOperationCont()->adjustOuterTerminal(iOuterTerminalMapCont[iEkiOrderBrunchTerminalSide[idxt]]);
		pEkiJikokuTarget->getCentDedAfterOperationCont()->adjustOuterTerminal(iOuterTerminalMapCont[iEkiOrderBrunchTerminalSide[idxt]]);
	}
}

} //namespace entDed
