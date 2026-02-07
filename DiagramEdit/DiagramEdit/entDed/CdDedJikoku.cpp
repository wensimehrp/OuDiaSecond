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
//	CdDedJikoku.cpp
// ****************************************************************
*/
#include "stdafx.h"

#include "CdDedJikoku.h"
#include "str¥strprintf.h"
#include <tchar.h>

using namespace std ;

#ifndef _CONSOLE
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

namespace entDed{
	using namespace OuLib::Str;

// ****************************************************************
//	CdDedJikoku::CConv
// ****************************************************************
CdDedJikoku::CConv::CConv() 
	: m_bNoColon( false )
	, m_eHour( EHour_Zero )
	, m_eSecond( ESecond_Output )
	, m_eSecondRoundChaku(ESecondRound_RoundDown)
	, m_eSecondRoundHatsu(ESecondRound_RoundDown)
	, m_bDisplay2400(false)
{
} ;

CdDedJikoku::CConv::CConv( 
	bool bNoColon ,
	CdDedJikoku::CConv::EHour	eHour  ,
	CdDedJikoku::CConv::ESecond eSecond,
	ESecondRound eSecondRoundChaku,
	ESecondRound eSecondRoundHatsu,
	bool bDisplay2400)
	: m_bNoColon( bNoColon )
	, m_eHour( eHour )
	, m_eSecond( eSecond )
	, m_eSecondRoundChaku(eSecondRoundChaku)
	, m_eSecondRoundHatsu(eSecondRoundHatsu)
	, m_bDisplay2400(bDisplay2400)
{
	int a = 0;
}

		
tstring CdDedJikoku::CConv::encode( const CdDedJikoku& aJikoku,
	const bool& bIsChakuJikoku,
	const CdDedJikoku& aCompareJikoku)const
{
	tstring	strRv ;
	if ( !aJikoku.isNull() ){
		if (m_eSecond == ESecond_NoSecond)
		{
			/**
				ESecond_NoSecondの場合は、秒単位丸め処理を行います。
				秒単位を丸めた場合、分及び時にも影響を及ぼすので注意が必要です。
			*/

			CdDedJikoku aTempJikoku(aJikoku);
			if (aCompareJikoku.isNull())
			{
				//切り上げの場合は、元の時刻に59秒を加算したものを、秒単位を無視することで、時と分が得られます
				//30秒以上切り上げの場合は、30秒を加算して同様に処理します
				if (bIsChakuJikoku &&
					m_eSecondRoundChaku == ESecondRound_RoundUp ||
					!bIsChakuJikoku &&
					m_eSecondRoundHatsu == ESecondRound_RoundUp)
				{
					aTempJikoku.addSeconds(59);
				}
				else if (bIsChakuJikoku &&
					m_eSecondRoundChaku == ESecondRound_Round ||
					!bIsChakuJikoku &&
					m_eSecondRoundHatsu == ESecondRound_Round)
				{
					aTempJikoku.addSeconds(30);
				}
			}
			else
			{
				//aCompareJikokuがNullでない場合は、着発それぞれの秒単位処理方法によっては、時刻の順序が逆転することがあります
				//逆転が起こる場合は、切り捨てまたは切り上げを止めます
				if (aJikoku.getHour() == aCompareJikoku.getHour() &&
					aJikoku.getMinute() == aCompareJikoku.getMinute())
				{
					if (bIsChakuJikoku &&
						m_eSecondRoundChaku == ESecondRound_RoundUp &&
						(m_eSecondRoundHatsu == ESecondRound_RoundDown ||
							m_eSecondRoundHatsu == ESecondRound_Round) &&
						aJikoku.getSecond() > 0 && aJikoku.getSecond() < 30 &&
						aCompareJikoku.getSecond() > 0 && aCompareJikoku.getSecond() < 30)
					{
						//着時刻が切り上げで、発時刻が30秒以上切り上げまたは切り捨てかつ、
						//着時刻発時刻ともに1-29秒の場合、順序が逆転するので、
						//着時刻の秒を切り捨てることで順序を維持します。

						//切り捨てなので特に処理なし
					}
					else if(!bIsChakuJikoku &&
						(m_eSecondRoundChaku == ESecondRound_RoundUp ||
							m_eSecondRoundChaku == ESecondRound_Round) &&
						m_eSecondRoundHatsu == ESecondRound_RoundDown &&
						aJikoku.getSecond() >= 30 &&
						aCompareJikoku.getSecond() >= 30)
					{
						//着時刻が丸めまたは切り上げで、発時刻が切り捨てかつ、
						//着時刻発時刻ともに30-59秒の場合、順序が逆転するので、
						//発時刻の秒を切り上げることで順序を維持します。
						aTempJikoku.addSeconds(59);
					}
					else if (bIsChakuJikoku &&
						m_eSecondRoundChaku == ESecondRound_RoundUp &&
						m_eSecondRoundHatsu == ESecondRound_RoundDown &&
						aJikoku.getSecond() > 0 && aJikoku.getSecond() < 30 &&
						aCompareJikoku.getSecond() >= 30)
					{
						//着時刻が切り上げで、発時刻が切り捨てかつ、
						//着時刻が1-29秒で発時刻が30-59秒の場合、順序が逆転するので、
						//秒単位の平均をとり、それが30秒以上なら切り上げ、未満なら切り捨てに統一します
						if (aJikoku.getSecond() + aCompareJikoku.getSecond() >= 60)
						{
							aTempJikoku.addSeconds(59);
						}
					}
					else if (!bIsChakuJikoku &&
						m_eSecondRoundChaku == ESecondRound_RoundUp &&
						m_eSecondRoundHatsu == ESecondRound_RoundDown &&
						aJikoku.getSecond() >= 30 &&
						aCompareJikoku.getSecond() > 0 && aCompareJikoku.getSecond() < 30)
					{
						//着時刻が切り上げで、発時刻が切り捨てかつ、
						//着時刻が1-29秒で発時刻が30-59秒の場合、順序が逆転するので、
						//秒単位の平均をとり、それが30秒以上なら切り上げ、未満なら切り捨てに統一します
						if (aJikoku.getSecond() + aCompareJikoku.getSecond() >= 60)
						{
							aTempJikoku.addSeconds(59);
						}
					}
					else
					{
						//前記の条件に合致しない場合は、bIsHatsuJikokuと、対応するm_eSecondRoundに基づき、
						//30秒以上切り上げ、または切り上げの処理を行います

						if (bIsChakuJikoku &&
							m_eSecondRoundChaku == ESecondRound_RoundUp ||
							!bIsChakuJikoku &&
							m_eSecondRoundHatsu == ESecondRound_RoundUp)
						{
							aTempJikoku.addSeconds(59);
						}
						else if (bIsChakuJikoku &&
							m_eSecondRoundChaku == ESecondRound_Round ||
							!bIsChakuJikoku &&
							m_eSecondRoundHatsu == ESecondRound_Round)
						{
							aTempJikoku.addSeconds(30);
						}
					}
				}
				else
				{
					//時分が一致しない場合は、bIsChakuJikokuと、対応するm_eSecondRoundに基づき、
					//30秒以上切り上げ、または切り上げの処理を行います

					if (bIsChakuJikoku &&
						m_eSecondRoundChaku == ESecondRound_RoundUp ||
						!bIsChakuJikoku &&
						m_eSecondRoundHatsu == ESecondRound_RoundUp)
					{
						aTempJikoku.addSeconds(59);
					}
					else if (bIsChakuJikoku &&
						m_eSecondRoundChaku == ESecondRound_Round ||
						!bIsChakuJikoku &&
						m_eSecondRoundHatsu == ESecondRound_Round)
					{
						aTempJikoku.addSeconds(30);
					}
				}
			}

			//	時 
			int iHour = aTempJikoku.getHour(); 
			if (m_bDisplay2400 && bIsChakuJikoku &&
				iHour == 0 && aTempJikoku.getMinute() == 0)
			{
				iHour = 24;
			}
			//int iHour = aJikoku.getHour();
			//if (aJikoku.getMinute() == 59 &&
			//	((!bIsChakuJikoku &&
			//	(m_eSecondRoundChaku == ESecondRound_RoundUp && aJikoku.getSecond() > 0 ||
			//		m_eSecondRoundChaku == ESecondRound_Round && aJikoku.getSecond() >= 30)) ||
			//		(bIsChakuJikoku &&
			//		(m_eSecondRoundHatsu == ESecondRound_RoundUp && aJikoku.getSecond() > 0 ||
			//			m_eSecondRoundHatsu == ESecondRound_Round && aJikoku.getSecond() >= 30))))
			//{
			//	/**
			//		分が59分かつ、秒切り上げで0秒以外・秒丸めで30秒以上の場合は、時も繰り上がります。
			//		ただし、時が23時の場合は、繰り上がって0になります(2400表示の場合は別)
			//	*/
			//	iHour++;
			//	if (iHour == 24 && 
			//		(!m_bDisplay2400 || bIsChakuJikoku))
			//	{
			//		iHour = 0;
			//	}
			//}
			//else if (m_bDisplay2400 && !bIsChakuJikoku &&
			//	iHour == 0 && aJikoku.getMinute() == 0)
			//{
			//	/**
			//		時が繰り上がり対象ではない場合、m_bDisplay2400がtrueで着時刻の場合に0時0分なら、
			//		時を24に変更します。
			//		ただし、繰り上がりで001になる場合は除きます
			//	*/
			//	if (m_eSecondRoundChaku == ESecondRound_RoundDown ||
			//		m_eSecondRoundChaku == ESecondRound_RoundUp && aJikoku.getSecond() == 0 ||
			//		m_eSecondRoundChaku == ESecondRound_Round && aJikoku.getSecond() < 30)
			//	{
			//		iHour = 24;
			//	}
			//}
			if (m_eHour == EHour_ZeroToNone)
			{
				//char	szLs[16] ;
				//sprintf( szLs , "%d" , aJikoku.getHour() ) ;
				//strRv += szLs ;
				strRv += strprintf(_T("%d"), iHour);
			}
			else if (m_eHour == EHour_ZeroToSpace)
			{
				//char	szLs[16] ;
				//sprintf( szLs , "%2d" , aJikoku.getHour() ) ;
				//strRv += szLs ;
				strRv += strprintf(_T("%2d"), iHour);
			}
			else
			{
				//char	szLs[16] ;
				//sprintf( szLs , "%02d" , aJikoku.getHour() ) ;
				//strRv += szLs ;
				strRv += strprintf(_T("%02d"), iHour);
			}
			//	時のつぎのコロン
			if (!m_bNoColon)
			{
				strRv += _T(":");
			}
			//	分
			//int iMinute = aJikoku.getMinute();
			//if (!bIsChakuJikoku &&
			//	(m_eSecondRoundChaku == ESecondRound_RoundUp && aJikoku.getSecond() > 0 ||
			//		m_eSecondRoundChaku == ESecondRound_Round && aJikoku.getSecond() >= 30) ||
			//	bIsChakuJikoku &&
			//	(m_eSecondRoundHatsu == ESecondRound_RoundUp && aJikoku.getSecond() > 0 ||
			//		m_eSecondRoundHatsu == ESecondRound_Round && aJikoku.getSecond() >= 30))
			//{
			//	/**
			//		秒切り上げで0秒以外・秒丸めで30秒以上の場合は、分が繰り上がります。
			//		分が60になった場合は、0に変更します。
			//	*/
			//	iMinute++;
			//	if (iMinute == 60)
			//	{
			//		iMinute = 0;
			//	}
			//}
			{
				strRv += strprintf(_T("%02d"), aTempJikoku.getMinute());
			}
		}
		else
		{
			//	時
			int iHour = aJikoku.getHour(); 
			if (m_bDisplay2400 && bIsChakuJikoku &&
				iHour == 0 && aJikoku.getMinute() == 0)
			{
				/**
					m_bDisplay2400がtrueで着時刻の場合に0時0分なら、
					時を24に変更します。秒は考慮しません。
				*/
				iHour = 24;
			}
			if (m_eHour == EHour_ZeroToNone)
			{
				//char	szLs[16] ;
				//sprintf( szLs , "%d" , aJikoku.getHour() ) ;
				//strRv += szLs ;
				strRv += strprintf(_T("%d"), iHour);
			}
			else if (m_eHour == EHour_ZeroToSpace)
			{
				//char	szLs[16] ;
				//sprintf( szLs , "%2d" , aJikoku.getHour() ) ;
				//strRv += szLs ;
				strRv += strprintf(_T("%2d"), iHour);
			}
			else
			{
				//char	szLs[16] ;
				//sprintf( szLs , "%02d" , aJikoku.getHour() ) ;
				//strRv += szLs ;
				strRv += strprintf(_T("%02d"), iHour);
			}
			//	時のつぎのコロン
			if (!m_bNoColon)
			{
				strRv += _T(":");
			}
			//	分
			{
				strRv += strprintf(_T("%02d"), aJikoku.getMinute());
			}
			//	秒
			if (m_eSecond == ESecond_Output ||
				(m_eSecond == ESecond_NotIfZero && aJikoku.getSecond() != 0))
			{
				//	分のつぎのコロン
				if (!m_bNoColon)
				{
					strRv += _T(":");
				}
				{
					strRv += strprintf(_T("%02d"), aJikoku.getSecond());
				}
			}
		}
	}
	return ( strRv ) ;

};




// ****************************************************************
//	CdDedJikoku
// ****************************************************************
const int iSecondsOfADay = 24 * 60 * 60 ;

// --------------------------------
//@name 下請関数
// --------------------------------
int CdDedJikoku::adjustTotalSeconds( int iTotalSeconds ) 
{
	iTotalSeconds %= iSecondsOfADay ;
	if ( iTotalSeconds < 0 ){
		iTotalSeconds = iSecondsOfADay + iTotalSeconds ;
	}
	return ( iTotalSeconds ) ;
}

// ********************************
//	コンストラクタ
// ********************************
CdDedJikoku::CdDedJikoku() : 
		m_iTotalSeconds( INT_MIN )
{
}

CdDedJikoku::CdDedJikoku( int iTotalSeconds ) 
{
	m_iTotalSeconds = adjustTotalSeconds( iTotalSeconds ) ;
}
	
CdDedJikoku::CdDedJikoku( int iHour , int iMinute , int iSecond ) 
{
	m_iTotalSeconds = adjustTotalSeconds( iHour * 60 * 60 + iMinute * 60 + iSecond ) ; 
}
CdDedJikoku::CdDedJikoku( const tstring& strTime ) 
	: m_iTotalSeconds( INT_MIN ) 
{
	decode( strTime ) ;
}

// ********************************
//	CdDedJikoku
// ********************************
	// ********************************
	//@name 属性
	// ********************************
CdDedJikoku& CdDedJikoku::setTotalSeconds( int value ) 
{
	m_iTotalSeconds = adjustTotalSeconds( value ) ;
	return ( *this ) ;
}
	
CdDedJikoku& CdDedJikoku::setTime( int iHour , int iMinute , int iSecond ) 
{
	m_iTotalSeconds = adjustTotalSeconds( iHour * 60 * 60 + iMinute * 60 + iSecond ) ; 
	return ( *this ) ;
}
	
CdDedJikoku& CdDedJikoku::setNull() 
{
	m_iTotalSeconds = INT_MIN ;
	return ( *this ) ;
}
	
	// ********************************
	//@name 操作
	// ********************************
int CdDedJikoku::compare( const CdDedJikoku& value )const 
{
	if ( m_iTotalSeconds > value.m_iTotalSeconds ){
		return ( 1 ) ;
	}	else if ( m_iTotalSeconds < value.m_iTotalSeconds ){
		return ( -1 ) ;
	}
	return ( 0 ) ;
}

int CdDedJikoku::compare( 
		const CdDedJikoku& value , 
		const CdDedJikoku& jikokuKitenJikoku )const 
{
	int iThisTotalSeconds = this->m_iTotalSeconds ;
	if ( iThisTotalSeconds < jikokuKitenJikoku.m_iTotalSeconds )
	{
		iThisTotalSeconds += TOTALSECONDS_A_DAY ;
	}

	int iValueTotalSeconds = value.m_iTotalSeconds ;
	if ( iValueTotalSeconds < jikokuKitenJikoku.m_iTotalSeconds )
	{
		iValueTotalSeconds += TOTALSECONDS_A_DAY ;
	}

	if ( iThisTotalSeconds > iValueTotalSeconds ){
		return ( 1 ) ;
	}	else if ( iThisTotalSeconds < iValueTotalSeconds ){
		return ( -1 ) ;
	}
	return ( 0 ) ;
}


CdDedJikoku& CdDedJikoku::addSeconds( int value ) 
{
	if ( !isNull() ){
		m_iTotalSeconds += value ;
		m_iTotalSeconds = adjustTotalSeconds( m_iTotalSeconds ) ;
	}
	return *this ;
}

int CdDedJikoku::subJikoku( const CdDedJikoku& value  )const 
{
	int iRv = 0 ; 
	if ( !isNull() && !value.isNull() ){
		iRv = m_iTotalSeconds - value.m_iTotalSeconds ;

		if ( iRv > 12*60*60 ){
			iRv -= 24*60*60 ;
		}	else if ( iRv < -12*60*60 ){
			iRv += 24*60*60 ;
		} 
	} 
	return ( iRv ) ;
}
	

int CdDedJikoku::decode( const tstring& value ) 
{
	int iRv = 0 ;

	tstring	strValue = value ;

	//	文字列が空文字列なら、『Null状態』とします。
	if ( value.empty() ){
		setNull() ;
		return ( 0 ) ;
	}

	//	コロンがない場合は追加
	{
		tstring::size_type pos = strValue.find(_T(":") ) ;
		if ( pos == tstring::npos ){
			//	コロンがありません。末尾から2桁区切りでコロンを挿入します。
			if ( strValue.size() > 2 ){
				strValue.insert( strValue.size() - 2 , _T(":") ) ;
			}
			if ( strValue.size() > 5 ){
				strValue.insert( strValue.size() - 5 , _T(":") ) ;
			}
		} 
	}
	//strValue = "13:15:45","9:15"
	
	//	秒がない場合は追加
	if ( strValue.size() <= 5 ){
		strValue += _T(":00") ;
	}
	//strValue = "13:15:45","9:15:00"

	//	時の10の位がない場合は追加
	if ( strValue.size() <= 7 ){
		strValue = tstring(_T("0") ) + strValue ;
	}
	//	時の10の位がスペースの場合は、スペースを "0" に変更
	if ( strValue.size() > 0 && strValue[0] == ' ' ){
		strValue[0] = '0' ;
	}

	//strValue = "13:15:45","09:15:00"

	int iHour = -1 ;
	int iMinute = -1 ;
	int iSecond = -1 ;
	if ( strValue.size() == 8 ){
		//	時
		{
			tstring	strLs = strValue.substr( 0 , 2 ) ;
			if ( strLs.find_first_not_of(_T("0123456789") ) == tstring::npos ){
				iHour = _ttoi( strLs.c_str() ) ;
			}
		}
		//	分
		{
			tstring	strLs = strValue.substr( 3 , 2 ) ;
			if ( strLs.find_first_not_of(_T("0123456789") ) == tstring::npos ){
				iMinute = _ttoi( strLs.c_str() ) ;
			}
		}
		//	秒
		{
			tstring	strLs = strValue.substr( 6 , 2 ) ;
			if ( strLs.find_first_not_of(_T("0123456789") ) == tstring::npos ){
				iSecond = _ttoi( strLs.c_str() ) ;
			}
		}
	}	else	{
		iRv = -1 ;	//	項目数が不足しています。
		return ( iRv ) ;
	}
	
	if ( 0 <= iHour && iHour < 24 && 
			0 <= iMinute && iMinute < 60 && 
			0 <= iSecond && iSecond < 60 ){
		setTime( iHour , iMinute , iSecond ) ;
	}	else	{
		iRv = -2 ;	//	時・分・秒の表記が不正です。
	}
	
	return ( iRv ) ;
}

void CdDedJikoku::round(CdDedJikoku::CConv::ESecondRound eSecondRound)
{
	if (eSecondRound == CdDedJikoku::CConv::ESecondRound_RoundDown)
	{
		m_iTotalSeconds -= getSecond();
	}
	else if (eSecondRound == CdDedJikoku::CConv::ESecondRound_Round)
	{
		int iSecond = getSecond();
		if (iSecond < 30)
		{
			m_iTotalSeconds -= iSecond;
		}
		else
		{
			m_iTotalSeconds += 59;
			m_iTotalSeconds -= iSecond;
		}
	}
	else
	{
		m_iTotalSeconds += 59;
		m_iTotalSeconds -= getSecond();
	}

}

} //namespace entDed
