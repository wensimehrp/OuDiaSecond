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
//	CentDedEkiJikoku.cpp
//	$Id: CentDedEkiJikoku.cpp 378 2016-11-16 21:10:54Z okm $
// ****************************************************************
*/
/** @file */
#include "stdafx.h"
#include "CentDedEkiJikoku.h"
#include "CentDedEkiJikokuCont.h"

namespace entDed{



// ****************************************************************
//	CentDedEkiJikoku::CXBeforeOperationCont
// ****************************************************************
CentDedEkiJikoku * CentDedEkiJikoku::CXBeforeOperationCont::getEkiJikoku()
{
	CentDedEkiJikoku* pOuter = (CentDedEkiJikoku*)(((char*)this) - offsetof(CentDedEkiJikoku, m_CentDedBeforeOperationCont));
	return pOuter;
}

const CentDedEkiJikoku * CentDedEkiJikoku::CXBeforeOperationCont::getEkiJikoku() const
{
	const CentDedEkiJikoku* pOuter = (const CentDedEkiJikoku*)(((char*)this) - offsetof(CentDedEkiJikoku, m_CentDedBeforeOperationCont));
	return pOuter;
}

// ****************************************************************
//	CentDedEkiJikoku::CXAfterOperationCont
// ****************************************************************
CentDedEkiJikoku * CentDedEkiJikoku::CXAfterOperationCont::getEkiJikoku()
{
	CentDedEkiJikoku* pOuter = (CentDedEkiJikoku*)(((char*)this) - offsetof(CentDedEkiJikoku, m_CentDedAfterOperationCont));
	return pOuter;
}

const CentDedEkiJikoku * CentDedEkiJikoku::CXAfterOperationCont::getEkiJikoku() const
{
	const CentDedEkiJikoku* pOuter = (const CentDedEkiJikoku*)(((char*)this) - offsetof(CentDedEkiJikoku, m_CentDedAfterOperationCont));
	return pOuter;
}

// ****************************************************************
//	CentDedEkiJikoku
// ****************************************************************


// ********************************
//	コンストラクタ
// ********************************
CentDedEkiJikoku::CentDedEkiJikoku() :
		m_eEkiatsukai( Ekiatsukai_None ) 
{
};
CentDedEkiJikoku::CentDedEkiJikoku( 
		EEkiatsukai	eEkiatsukai , 
		CdDedJikoku	jikokuChakujikoku , 
		CdDedJikoku	jikokuHatsujikoku ) 
{
	set( eEkiatsukai , jikokuChakujikoku , jikokuHatsujikoku ) ;			
};
CentDedEkiJikoku::CentDedEkiJikoku(
	EEkiatsukai	eEkiatsukai,
	CdDedJikoku	jikokuChakujikoku,
	CdDedJikoku	jikokuHatsujikoku,
	int iRessyaTrackIndex)
{
	set(eEkiatsukai, jikokuChakujikoku, jikokuHatsujikoku, iRessyaTrackIndex);
};

CentDedEkiJikoku& CentDedEkiJikoku::operator=( const CentDedEkiJikoku& value ) 
{
	CentDedEkiJikokuCont* pEkiJikokuCont = dynamic_cast<CentDedEkiJikokuCont*>( getParent() ) ;
	if ( pEkiJikokuCont != NULL )
	{
		int iResult = pEkiJikokuCont->setable( value , pEkiJikokuCont->getIndex( this ) ) ;
		if ( iResult < 0 ){
			throw( LException() ) ;
		}
	}
	super::operator=( value ) ; 

	// --------------------------------
	m_eEkiatsukai = value.m_eEkiatsukai ;
	m_jikokuChakujikoku = value.m_jikokuChakujikoku ;
	m_jikokuHatsujikoku = value.m_jikokuHatsujikoku ;
	m_iRessyaTrackIndex = value.m_iRessyaTrackIndex;
	m_CentDedBeforeOperationCont = value.m_CentDedBeforeOperationCont;
	m_CentDedAfterOperationCont = value.m_CentDedAfterOperationCont;


	return *this ;
}

	// ********************************
	//@name CParentBase-操作
	// ********************************
void CentDedEkiJikoku::setParent( CParentBase* pParent )
{
	super::setParent( pParent ) ; 
}


	// ********************************
	//@name CentDedEkiJikoku-属性
	// ********************************
CentDedEkiJikoku::EEkiatsukai	CentDedEkiJikoku::getEkiatsukai()const{	return m_eEkiatsukai ;};

CentDedEkiJikoku& CentDedEkiJikoku::setEkiatsukai( CentDedEkiJikoku::EEkiatsukai value )
{
	m_eEkiatsukai = value ;
	if ( m_eEkiatsukai == Ekiatsukai_None){
		m_jikokuChakujikoku.setNull() ;
		m_jikokuHatsujikoku.setNull() ;
		m_iRessyaTrackIndex = 0;
		m_CentDedBeforeOperationCont.erase(0, INT_MAX);
		m_CentDedAfterOperationCont.erase(0, INT_MAX);
	}

	return *this ; 
} ;

CdDedJikoku	CentDedEkiJikoku::getChakujikoku( bool bHatsuIfNull )const
{
	if ( bHatsuIfNull && m_jikokuChakujikoku.isNull() ){
		return m_jikokuHatsujikoku ;
	}
	return m_jikokuChakujikoku ;
}
CdDedJikoku CentDedEkiJikoku::getVirtualChakujikoku() const
{
	if (m_jikokuChakujikoku.isNull())
	{
		return m_jikokuChakujikoku;
	}
	int iRessyaTrack = m_iRessyaTrackIndex;
	CdDedJikoku aCdDedJikoku = m_jikokuChakujikoku;
	const CentDedBeforeOperationCont* pBeforeCont = getCentDedBeforeOperationCont();
	for (int idx = pBeforeCont->size() - 1; idx >= 0; idx--)
	{
		const CentDedBeforeOperation* pBeforeOperation = pBeforeCont->getMuPtr()->get(idx);
		if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt &&
			iRessyaTrack != pBeforeOperation->getShuntTrackIndex())
		{
			/**
				同じ番線からの入換は、入換自体を無効と見なし、次を検索します
			*/
			if (pBeforeOperation->getIsDisplayChakuJikoku())
			{
				aCdDedJikoku = pBeforeOperation->getOperationChakuJikoku(true);
				break;
			}
			/**
				getIsDisplayChakuJikokuがfalseの場合、iRessyaTrackを更新して、次を検索します
			*/
			iRessyaTrack = pBeforeOperation->getShuntTrackIndex();
		}
	}
	return aCdDedJikoku;
}

CentDedEkiJikoku& CentDedEkiJikoku::setChakujikoku( const CdDedJikoku& value )
{
	m_jikokuChakujikoku = value ; 

	//	- 	m_eEkiatsukai == Ekiatsukai_Noneの駅に対して
	//		着・発のいずれかに 非Null 時刻を設定すると、this の
	//		m_eEkiatsukai = Ekiatsukai_Teisya となります。
	if ( 
		( m_eEkiatsukai == Ekiatsukai_None) &&
		( !m_jikokuChakujikoku.isNull() ||
		  ! m_jikokuHatsujikoku.isNull() )   ){
		m_eEkiatsukai = Ekiatsukai_Teisya ;

	}
		
	return *this ;
};

CdDedJikoku	CentDedEkiJikoku::getHatsujikoku( bool bChakuIfNull )const{
	if ( bChakuIfNull && m_jikokuHatsujikoku.isNull() ){
		return m_jikokuChakujikoku ;
	}
	return m_jikokuHatsujikoku ;
}
CdDedJikoku CentDedEkiJikoku::getVirtualHatsujikoku() const
{
	if (m_jikokuHatsujikoku.isNull())
	{
		return m_jikokuHatsujikoku;
	}
	int iRessyaTrack = m_iRessyaTrackIndex;
	CdDedJikoku aCdDedJikoku = m_jikokuHatsujikoku;
	const CentDedAfterOperationCont* pAfterCont = getCentDedAfterOperationCont();
	for (int idx = 0; idx < (int)pAfterCont->size(); idx++)
	{
		const CentDedAfterOperation* pAfterOperation = pAfterCont->getMuPtr()->get(idx);
		if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt &&
			iRessyaTrack != pAfterOperation->getShuntTrackIndex())
		{
			/**
				同じ番線からの入換は、入換自体を無効と見なし、次を検索します
			*/
			if (pAfterOperation->getIsDisplayHatsuJikoku())
			{
				aCdDedJikoku = pAfterOperation->getOperationHatsuJikoku();
				break;
			}
			/**
				getIsDisplayHatsuJikokuがfalseの場合、iRessyaTrackを更新して、次を検索します
			*/
			iRessyaTrack = pAfterOperation->getShuntTrackIndex();
		}
	}
	return aCdDedJikoku;
}

CentDedEkiJikoku& CentDedEkiJikoku::setHatsujikoku( const CdDedJikoku& value )
{
	m_jikokuHatsujikoku = value ; 

	//- 	m_eEkiatsukai == Ekiatsukai_None の駅に対して
	//	着・発のいずれかに 非Null 時刻を設定すると、this の
	//	m_eEkiatsukai = Ekiatsukai_Teisya となります。
	if ( 
		( m_eEkiatsukai == Ekiatsukai_None) &&
		( !m_jikokuChakujikoku.isNull() ||
		  ! m_jikokuHatsujikoku.isNull() )   ){
		m_eEkiatsukai = Ekiatsukai_Teisya ;

	}
	return *this ;
};

int CentDedEkiJikoku::getRessyaTrackIndex()const
{
	return m_iRessyaTrackIndex;
};

CentDedEkiJikoku& CentDedEkiJikoku::setRessyaTrackIndex(const int value)
{
	m_iRessyaTrackIndex = value;
	return *this;
};


CentDedEkiJikoku& CentDedEkiJikoku::set( 
		EEkiatsukai	eEkiatsukai , 
		CdDedJikoku	jikokuChakujikoku , 
		CdDedJikoku	jikokuHatsujikoku )
{
	m_eEkiatsukai = eEkiatsukai ; 
	m_jikokuChakujikoku =  jikokuChakujikoku ;
	m_jikokuHatsujikoku =  jikokuHatsujikoku ;
	m_iRessyaTrackIndex = 0;


	if ( m_eEkiatsukai == Ekiatsukai_None )
	{
		m_jikokuChakujikoku.setNull() ;
		m_jikokuHatsujikoku.setNull() ;
	}

	return ( *this ) ;
};

CentDedEkiJikoku& CentDedEkiJikoku::set(
	EEkiatsukai	eEkiatsukai,
	CdDedJikoku	jikokuChakujikoku,
	CdDedJikoku	jikokuHatsujikoku,
	int iRessyaTrackIndex)
{
	m_eEkiatsukai = eEkiatsukai;
	m_jikokuChakujikoku = jikokuChakujikoku;
	m_jikokuHatsujikoku = jikokuHatsujikoku;
	m_iRessyaTrackIndex = iRessyaTrackIndex;

	if (m_eEkiatsukai == Ekiatsukai_None)
	{
		m_jikokuChakujikoku.setNull();
		m_jikokuHatsujikoku.setNull();
		m_iRessyaTrackIndex = 0;
	}

	return (*this);
}
void CentDedEkiJikoku::setCentDedBeforeOperationCont(
	CentDedBeforeOperationCont value)
{
	for (int idx = 0; idx < value.size(); idx++)
	{
		if (idx < m_CentDedBeforeOperationCont.size())
		{
			m_CentDedBeforeOperationCont.set(value.get(idx), idx);
		}
		else
		{
			m_CentDedBeforeOperationCont.insert(value.get(idx));
		}
	}
	if (value.size() < m_CentDedBeforeOperationCont.size())
	{
		m_CentDedBeforeOperationCont.erase(value.size(), INT_MAX);
	}
	//m_CentDedBeforeOperationCont = value;
}
;
void CentDedEkiJikoku::setCentDedAfterOperationCont(
	CentDedAfterOperationCont value)
{
	for (int idx = 0; idx < value.size(); idx++)
	{
		if (idx < m_CentDedAfterOperationCont.size())
		{
			m_CentDedAfterOperationCont.set(value.get(idx), idx);
		}
		else
		{
			m_CentDedAfterOperationCont.insert(value.get(idx));
		}
	}
	if (value.size() < m_CentDedAfterOperationCont.size())
	{
		m_CentDedAfterOperationCont.erase(value.size(), INT_MAX);
	}
	//m_CentDedAfterOperationCont = value;
}
;

	// ********************************
	//@name CentDedEkiJikoku-操作
	// ********************************
void CentDedEkiJikoku::adjustByEkijikokukeisiki(
		bool bChakujikokuHyouji , bool bHatsujikokuHyouji ,
		bool bIsSihatsueki , bool bSyuuchakueki ) 
{
	//○[駅時刻形式に着時刻あり・発時刻なし、
	//  駅時刻に着時刻なし、発時刻あり]
	//  着時刻には発時刻をコピー、発時刻はNULL。
	if ( bChakujikokuHyouji && !bHatsujikokuHyouji && 
		m_jikokuChakujikoku.isNull() && !m_jikokuHatsujikoku.isNull() )
	{
		m_jikokuChakujikoku = m_jikokuHatsujikoku ;
		m_jikokuHatsujikoku.setNull() ;
	}
	//○[駅時刻形式に着時刻なし・発時刻あり
	//  駅時刻に着時刻あり、発時刻なし]
	//  発時刻には着時刻をコピー、着時刻はNULL。
	else if ( !bChakujikokuHyouji && bHatsujikokuHyouji && 
		!m_jikokuChakujikoku.isNull() && m_jikokuHatsujikoku.isNull() )
	{
		m_jikokuHatsujikoku = m_jikokuChakujikoku ;
		m_jikokuChakujikoku.setNull() ;
	}
	//○[駅が始発駅・
	//  駅時刻形式に着時刻あり・発時刻あり、
	//  駅時刻に着時刻あり、発時刻なし]
	//  発時刻には着時刻をコピー、着時刻はNULL。
	else if ( bIsSihatsueki && 
		bChakujikokuHyouji && bHatsujikokuHyouji && 
		!m_jikokuChakujikoku.isNull() && m_jikokuHatsujikoku.isNull() )
	{
		m_jikokuHatsujikoku = m_jikokuChakujikoku ;
		m_jikokuChakujikoku.setNull() ;
	}
	//○[駅が終着駅・
	//  駅時刻形式に着時刻あり・発時刻あり
	//  駅時刻に着時刻なし、発時刻あり]
	//  着時刻には発時刻をコピー、発時刻はNULL。
	else if ( bSyuuchakueki && 
		bChakujikokuHyouji && bHatsujikokuHyouji && 
		m_jikokuChakujikoku.isNull() && !m_jikokuHatsujikoku.isNull() )
	{
		m_jikokuChakujikoku = m_jikokuHatsujikoku ;
		m_jikokuHatsujikoku.setNull() ;
	}


}

void CentDedEkiJikoku::adjustOperation(int iType)
{
	if (iType == INT_MIN)
	{
		getCentDedBeforeOperationCont()->adjustOperation(INT_MIN);
		getCentDedAfterOperationCont()->adjustOperation(INT_MIN);

	}
	else if (iType == -2)
	{
		getCentDedBeforeOperationCont()->adjustOperation(-1);
		getCentDedAfterOperationCont()->adjustOperation(0);
	}
	else if (iType == -1)
	{
		getCentDedBeforeOperationCont()->adjustOperation(INT_MIN);
		if (m_jikokuHatsujikoku.isNull())
		{
			getCentDedAfterOperationCont()->adjustOperation(INT_MIN);
		}
		else
		{
			getCentDedAfterOperationCont()->adjustOperation(0);
		}
	}
	else if (iType == 0)
	{
		if (m_jikokuChakujikoku.isNull() ||
			m_jikokuHatsujikoku.isNull())
		{
			getCentDedBeforeOperationCont()->adjustOperation(INT_MIN);
			getCentDedAfterOperationCont()->adjustOperation(INT_MIN);
		}
		else
		{
			getCentDedBeforeOperationCont()->adjustOperation(0);
			getCentDedAfterOperationCont()->adjustOperation(0);
		}
	}
	else if (iType == 1)
	{
		if (m_jikokuChakujikoku.isNull())
		{
			getCentDedBeforeOperationCont()->adjustOperation(INT_MIN);
		}
		else
		{
			getCentDedBeforeOperationCont()->adjustOperation(0);
		}
		getCentDedAfterOperationCont()->adjustOperation(INT_MIN);
	}
	else if (iType == 2)
	{
		getCentDedBeforeOperationCont()->adjustOperation(0);
		getCentDedAfterOperationCont()->adjustOperation(1);
	}
	else if (iType == INT_MAX)
	{
		if (m_jikokuChakujikoku.isNull())
		{
			getCentDedBeforeOperationCont()->adjustOperation(INT_MIN);
		}
		else
		{
			getCentDedBeforeOperationCont()->adjustOperation(0);
		}
		if (m_jikokuHatsujikoku.isNull())
		{
			getCentDedAfterOperationCont()->adjustOperation(INT_MIN);
		}
		else
		{
			getCentDedAfterOperationCont()->adjustOperation(0);
		}

	}
}

} //namespace entDed
