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
//	CconvCentDedOud.cpp
// ****************************************************************
*/
#include "stdafx.h"
#include <vector>
#include <map>
using namespace std ;

#include "str¥strToInt.h"
#include "str¥stringSplit.h"
#include "str¥tstring.h"
#include "NsOu¥OuNew.h"
#include "NsOu¥dynamic_castOu.h"
#include "NsMu¥CaMui.h"
#include "DcdCd¥DcDrawProp¥CconvDcDrawProp.h"
#include "CconvCentDedOud.h"

using namespace OuLib::Str ;
using namespace OuLib::Str::OuPropertiesText;
using namespace OuLib::Str::OuPropertiesText::ErrorInfo;

/*delete 遅いので抑止
#ifndef _CONSOLE
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static TCHAR THIS_FILE[] = __FILE__;
#endif
#endif
*/

namespace entDed{

/** 時刻の書式を保持します。 */
const CdDedJikoku::CConv	g_CdDedJikokuConv(
	true ,		//	NoColon 
	CdDedJikoku::CConv::EHour_ZeroToNone ,
	CdDedJikoku::CConv::ESecond_NotIfZero ) ;
// ********************************
//	CdColorProp
// ********************************

/**
	aCdColorProp を文字列に変換します。
@param aCdColorProp [in]
	変換元の値を指定してください。
@return
	変換結果を返します。
*/
static tstring CdColorProp_to_string( const CdColorProp& aCdColorProp )
{
	CconvDcDrawProp	aConv ;
	return aConv.CdColorProp_to_string( aCdColorProp ) ;
	
}


/**
	文字列を aCdColorProp に変換します。
@param aString [in]
	変換元の値を指定してください。
@return
	変換結果を返します。
 */
static CdColorProp CdColorProp_from_string( const tstring& aString  )
{
	CconvDcDrawProp	aConv ;
	return aConv.CdColorProp_from_string( aString ) ;
}


// ********************************
//	CentDedEki
// ********************************
const TCHAR nameEkimei[] = _T("Ekimei") ;
const TCHAR nameEkijikokukeisiki[] = _T("Ekijikokukeisiki") ;
const TCHAR nameEkikibo[] = _T("Ekikibo") ;
const TCHAR nameKyoukaisen[] = _T("Kyoukaisen") ;
const TCHAR nameDiagramRessyajouhouHyoujiKudari[] = _T("DiagramRessyajouhouHyoujiKudari") ;
const TCHAR nameDiagramRessyajouhouHyoujiNobori[] = _T("DiagramRessyajouhouHyoujiNobori") ;

const CEnumToString< CentDedEki::EEkijikokukeisiki >& 
CconvCentDedOud::getEEkijikokukeisikiToString()
{
	static CEnumToString< CentDedEki::EEkijikokukeisiki >	aCEnumToString ;
	if ( aCEnumToString.size() == 0 )
	{
		aCEnumToString.add( CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsu , _T("Jikokukeisiki_Hatsu") ) ;
		aCEnumToString.add( CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku , _T("Jikokukeisiki_Hatsuchaku") ) ;
		aCEnumToString.add( CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku , _T("Jikokukeisiki_KudariChaku") ) ;
		aCEnumToString.add( CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku , _T("Jikokukeisiki_NoboriChaku")  ) ;
		//17.4.14 add_by_d_mania 4.15 oud形式向けに変換、追加2形式は発着扱いに。
		aCEnumToString.add( CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku , _T("Jikokukeisiki_Hatsuchaku") ) ;
		aCEnumToString.add( CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku , _T("Jikokukeisiki_Hatsuchaku")  ) ;
	}
	return aCEnumToString ;
}


const CEnumToString< CentDedEki::EEkikibo >& 
CconvCentDedOud::getEEkikiboToString()
{
	static CEnumToString< CentDedEki::EEkikibo >	aCEnumToString ;
	if ( aCEnumToString.size() == 0 )
	{
		aCEnumToString.add( CentDedEki::EEkikibo::Ekikibo_Ippan , _T("Ekikibo_Ippan") ) ;
		aCEnumToString.add( CentDedEki::EEkikibo::Ekikibo_Syuyou , _T("Ekikibo_Syuyou") ) ;
	}
	return aCEnumToString ;
}


const CEnumToString< CentDedEki::EDiagramRessyajouhouHyouji >& 
CconvCentDedOud::getEDiagramRessyajouhouHyoujiToString()
{
	static CEnumToString< CentDedEki::EDiagramRessyajouhouHyouji >	aCEnumToString ;
	if ( aCEnumToString.size() == 0 )
	{
		aCEnumToString.add( CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Origin , 
			_T("") ) ;
		aCEnumToString.add( CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Anytime , 
			_T("DiagramRessyajouhouHyouji_Anytime") ) ;
		aCEnumToString.add( CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Not , 
			_T("DiagramRessyajouhouHyouji_Not") ) ;
	}
	return aCEnumToString ;
}

int CconvCentDedOud::CentDedEki_To_OuPropertiesText( 
			const CentDedEki& aCentDedEki , 
			OuPropertiesText::CNodeContainer* pCNodeContainer ) 
{
	int iRv = 0 ;
	// --------------------------------	
	//1.Ekimei
	if ( iRv >= 0 ){
		//memo:
		//	以前は、空文字列の駅名はエラーでしたが、
		//	現在はこれを認めるようになりました。
		pCNodeContainer->setValue( nameEkimei , 
			aCentDedEki.getEkimei() ) ;
	}
	//2.Ekijikokukeisiki
	if ( iRv >= 0 )
	{
		tstring strValue = getEEkijikokukeisikiToString().stringOf( 
			aCentDedEki.getEkijikokukeisiki() ) ;
		pCNodeContainer->setValue( nameEkijikokukeisiki , strValue ) ;
	}

	//3.Ekikibo
	if ( iRv >= 0 )
	{
		tstring strValue = getEEkikiboToString().stringOf( 
			aCentDedEki.getEkikibo() ) ;
		pCNodeContainer->setValue( nameEkikibo , 
				strValue ) ;
	}
	//4.Kyoukaisen
	if ( iRv >= 0 )
	{
		if ( aCentDedEki.getKyoukaisen() )
		{
			pCNodeContainer->setValue( nameKyoukaisen , _T("1") ) ;
		}
	}
	//5. m_bDiagramRessyajouhouHyoujiKudari ;
	if ( iRv >= 0 )
	{
		tstring strValue = getEDiagramRessyajouhouHyoujiToString().stringOf( 
					aCentDedEki.getDiagramRessyajouhouHyoujiKudari() ) ;
		if ( !strValue.empty() )
		{
			pCNodeContainer->setValue( 
				nameDiagramRessyajouhouHyoujiKudari , strValue ) ;
		}
	}
	//6.m_bDiagramRessyajouhouHyoujiNobori
	if ( iRv >= 0 )
	{
		tstring strValue = getEDiagramRessyajouhouHyoujiToString().stringOf( 
					aCentDedEki.getDiagramRessyajouhouHyoujiNobori() ) ;
		if ( !strValue.empty() )
		{
			pCNodeContainer->setValue( nameDiagramRessyajouhouHyoujiNobori ,strValue) ;
		}
	}
	// --------------------------------	
	return ( iRv ) ;
}

	// ********************************
	//	CentDedEkiCont
	// ********************************
const TCHAR nameEki[] = _T("Eki") ;
	
int CconvCentDedOud::CentDedEkiCont_To_OuPropertiesText( 
			const CentDedEkiCont& aCentDedEkiCont , 
			OuPropertiesText::CNodeContainer* pCNodeContainer ) 
{
	int iRv = 0 ;
	if ( iRv >= 0 )
	{
		//for (int idxEki = 0; iRv >= 0 && idxEki < aCentDedEkiCont.size()-1; idxEki++)
		//{
		//	aCentDedEkiCont.get
		//}
		for ( int idxEki = 0 ; iRv >= 0 && idxEki < aCentDedEkiCont.size() ; idxEki ++ )
		{
			CentDedEki aCentDedEki = aCentDedEkiCont.get(idxEki);
			aCentDedEki.setKyoukaisen(false);
			if (idxEki < aCentDedEkiCont.size() - 1 && aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku)
			{
				const CentDedEki aCentDedEkiNext = aCentDedEkiCont.get(idxEki + 1);
				if (aCentDedEkiNext.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku)
				{
					aCentDedEki.setKyoukaisen(true);
				}
			}
			Ou<CDirectory> pCDirectory = OuNew<CDirectory>( new CDirectory( nameEki ) ) ;
			int iResult = CentDedEki_To_OuPropertiesText(
				aCentDedEki,
				//aCentDedEkiCont.get( idxEki ) ,
				pCDirectory->getCNodeContainer() ) ;
			if ( iResult < 0 )
			{
				iRv = iResult ;
			}
			else
			{
				pCNodeContainer->insert( pCDirectory ) ;
			}
		}
	}
	return iRv ;
}
	
// ********************************
//	CentDedRessyasyubetsu
// ********************************

const TCHAR nameSyubetsumei[]= _T("Syubetsumei") ;
const TCHAR nameRyakusyou[]= _T("Ryakusyou") ;
const TCHAR nameJikokuhyouMojiColor[]= _T("JikokuhyouMojiColor") ;
const TCHAR nameJikokuhyouFontIndex[] = _T("JikokuhyouFontIndex") ;
const TCHAR nameDiagramSenColor[]= _T("DiagramSenColor") ;
const TCHAR nameDiagramSenStyle[]= _T("DiagramSenStyle") ;
const TCHAR nameDiagramSenIsBold[]= _T("DiagramSenIsBold") ;
const TCHAR nameDiagramRessyaFont[] = _T("DiagramRessyaFont") ;
const TCHAR nameStopMarkDrawType[] = _T("StopMarkDrawType") ;

const CEnumToString< CentDedRessyasyubetsu::ESenStyle >& 
CconvCentDedOud::getESenStyleToString()
{
	static CEnumToString< CentDedRessyasyubetsu::ESenStyle >	aCEnumToString ;
	if ( aCEnumToString.size() == 0 )
	{
		aCEnumToString.add( CentDedRessyasyubetsu::SenStyle_Jissen , _T("SenStyle_Jissen") ) ;
		aCEnumToString.add( CentDedRessyasyubetsu::SenStyle_Hasen , _T("SenStyle_Hasen") ) ;
		aCEnumToString.add( CentDedRessyasyubetsu::SenStyle_Tensen , _T("SenStyle_Tensen")) ;
		aCEnumToString.add( CentDedRessyasyubetsu::SenStyle_Ittensasen , _T("SenStyle_Ittensasen") ) ;
	}
	return aCEnumToString ;
}

const CEnumToString< CentDedRessyasyubetsu::EStopMarkDrawType >& 
CconvCentDedOud::getEStopMarkDrawTypeToString()
{
	static CEnumToString< CentDedRessyasyubetsu::EStopMarkDrawType >	aCEnumToString ;
	if ( aCEnumToString.size() == 0 )
	{
		aCEnumToString.add( CentDedRessyasyubetsu::EStopMarkDrawType_DrawOnStop , _T("EStopMarkDrawType_DrawOnStop") ) ;
		aCEnumToString.add( CentDedRessyasyubetsu::EStopMarkDrawType_Nothing , _T("EStopMarkDrawType_Nothing") ) ;
		aCEnumToString.add( CentDedRessyasyubetsu::EStopMarkDrawType_DrawOnPass , _T("EStopMarkDrawType_DrawOnPass")) ;
	}
	return aCEnumToString ;
}

int CconvCentDedOud::CdDiagramLineStyle_To_OuPropertiesText( 
	const CentDedRessyasyubetsu::CdDiagramLineStyle& aCdDiagramLineStyle , 
	OuPropertiesText::CNodeContainer* pCNodeContainer ) 
{
	int iRv = 0 ;

	// --------------------------------	
	//5.DiagramSenColor
	if ( iRv >= 0 )
	{
		pCNodeContainer->setValue( nameDiagramSenColor , 
			CdColorProp_to_string( aCdDiagramLineStyle.getDiagramSenColor() ) ) ;
	}

	//6.DiagramSenStyle
	if ( iRv >= 0 )
	{
		tstring strValue = getESenStyleToString().stringOf( aCdDiagramLineStyle.getDiagramSenStyle() ) ;
		pCNodeContainer->setValue( nameDiagramSenStyle , strValue ) ;

	}

	//7.DiagramSenIsBold
	if ( iRv >= 0 )
	{
		bool bValue = aCdDiagramLineStyle.getDiagramSenIsBold();
		if ( bValue )
		{
			pCNodeContainer->setValue( nameDiagramSenIsBold , _T("1") ) ;
		}
	}
	return iRv ;
}

int CconvCentDedOud::CentDedRessyasyubetsu_To_OuPropertiesText( 
			const CentDedRessyasyubetsu& aCentDedRessyasyubetsu , 
			OuPropertiesText::CNodeContainer* pCNodeContainer ) 
{
	int iRv = 0 ;

	// --------------------------------	
	//1.Syubetsumei
	if ( iRv >= 0 )
	{
		if ( aCentDedRessyasyubetsu.getSyubetsumei().empty() )
		{
			iRv = -11 ;	//	Syubetsumei が指定されていません。
		}
		else
		{
			pCNodeContainer->setValue( nameSyubetsumei , 
				aCentDedRessyasyubetsu.getSyubetsumei() ) ;
		}
	}

	//2.Ryakusyou
	if ( iRv >= 0 )
	{
		if ( aCentDedRessyasyubetsu.getRyakusyou().empty() )
		{

		}
		else
		{
			pCNodeContainer->setValue( nameRyakusyou , 
				aCentDedRessyasyubetsu.getRyakusyou() ) ;
		}
	}

	//3.JikokuhyouMojiColor
	if ( iRv >= 0 )
	{
		pCNodeContainer->setValue( nameJikokuhyouMojiColor , 
			CdColorProp_to_string( aCentDedRessyasyubetsu.getJikokuhyouMojiColor() ) ) ;
	}
	//4.JikokuhyouFontIndex
	if ( iRv >= 0 )
	{
		int iValue = aCentDedRessyasyubetsu.getJikokuhyouFontIndex() ;
		{
			pCNodeContainer->setValue( 
				nameJikokuhyouFontIndex , 
				stringOf( iValue ) ) ;
		}
	}
	//5.DiagramSenColor
	//6.DiagramSenStyle
	//7.DiagramSenIsBold
	if ( iRv >= 0 )
	{
		CdDiagramLineStyle_To_OuPropertiesText( 
			aCentDedRessyasyubetsu.getCdDiagramLineStyle() ,
			pCNodeContainer ) ;
	}

	//9 StopMarkDrawType
	if ( iRv >= 0 )
	{
		tstring strValue = getEStopMarkDrawTypeToString().stringOf( aCentDedRessyasyubetsu.getStopMarkDrawType() ) ;
		pCNodeContainer->setValue( nameStopMarkDrawType , strValue ) ;
	}
	return ( iRv ) ;
}

void CconvCentDedOud::CentDedRessyasyubetsu_to_CDcdFreeLineProp(
		const CentDedRessyasyubetsu::CdDiagramLineStyle& aLineStyle , 
		CdDcdFreeLineProp* pCdLineProp )
{
	pCdLineProp->setColor( aLineStyle.getDiagramSenColor() ) ;
	switch( aLineStyle.getDiagramSenStyle() ){
		 // 実線 
		 case CentDedRessyasyubetsu::SenStyle_Jissen :
			pCdLineProp->setLinestyle( LINESTYLE_SOLID ) ;
			break ;
		 // 破線
		 case CentDedRessyasyubetsu::SenStyle_Hasen :
			pCdLineProp->setLinestyle( LINESTYLE_DASH ) ;
			break ;
		 // 点線
		 case CentDedRessyasyubetsu::SenStyle_Tensen :
			pCdLineProp->setLinestyle( LINESTYLE_DOT ) ;
			break ;
		 // 一点鎖線
		 case CentDedRessyasyubetsu::SenStyle_Ittensasen :
			pCdLineProp->setLinestyle( LINESTYLE_DASH_DOT ) ;
			break ;
	}
	pCdLineProp->setLogicalunitWidth( aLineStyle.getDiagramSenIsBold() ? 2 : 1 ) ;

}

	// ********************************
	//	CentDedRessyasyubetsuCont
	// ********************************
const TCHAR nameRessyasyubetsu[] = _T("Ressyasyubetsu") ;
	

int CconvCentDedOud::CentDedRessyasyubetsuCont_To_OuPropertiesText( 
			const CentDedRessyasyubetsuCont& aCentDedRessyasyubetsuCont , 
			OuPropertiesText::CNodeContainer* pCNodeContainer ) 
{
	int iRv = 0 ;
	if ( iRv >= 0 )
	{
		for ( int idx = 0 ; iRv >= 0 && idx < aCentDedRessyasyubetsuCont.size() ; idx ++ )
		{
			Ou<CDirectory> pCDirectory = OuNew<CDirectory>( new CDirectory( nameRessyasyubetsu ) ) ;
			int iResult = CentDedRessyasyubetsu_To_OuPropertiesText(
				aCentDedRessyasyubetsuCont.get( idx ) ,
				pCDirectory->getCNodeContainer() ) ;
			//	-	-11 ;	//	Syubetsumei が指定されていません。
			//	-	-52 ;	//	DiagramSenStyle の値が不正です。
			if ( iResult < 0 )
			{
				//	-	-11 ;	//	Syubetsumei が指定されていません。
				//	-	-52 ;	//	DiagramSenStyle の値が不正です。
				iRv = iResult ;
			}
			else
			{
				pCNodeContainer->insert( pCDirectory ) ;
			}
		}
	}
	return iRv ;
}
	
	// ********************************
	//	CentDedEkiJikoku
	// ********************************
tstring CconvCentDedOud::CentDedEkiJikoku_To_string( 
			const CentDedEkiJikoku* pCentDedEkiJikoku ) 
{
	tstring	strEkiatsukai ;
	tstring strChaku ;
	tstring strHatsu ;
	//	駅扱
	if ( pCentDedEkiJikoku->getEkiatsukai() != CentDedEkiJikoku::Ekiatsukai_None )
	{
		strEkiatsukai = stringOf( 
			(int)pCentDedEkiJikoku->getEkiatsukai() ) ;
	}
	//	着時刻
	if ( !pCentDedEkiJikoku->getChakujikoku().isNull() )
	{
		strChaku = g_CdDedJikokuConv.encode( pCentDedEkiJikoku->getChakujikoku() ) ;
	}
	//	発時刻
	if ( !pCentDedEkiJikoku->getHatsujikoku().isNull() )
	{
		strHatsu = g_CdDedJikokuConv.encode( pCentDedEkiJikoku->getHatsujikoku() ) ;
	}

	tstring	strEkijikoku ;
	strEkijikoku.reserve( 32 ) ;
	if ( !strEkiatsukai.empty() )
	{
		strEkijikoku += strEkiatsukai ;
		if ( !strChaku.empty() || !strHatsu.empty() )
		{
			strEkijikoku += ';' ;
			if ( !strChaku.empty() )
			{
				strEkijikoku += strChaku ;
				strEkijikoku += '/' ;
			}
			strEkijikoku += strHatsu ;
		}
	}
	return strEkijikoku ;
}

// ********************************
//	CentDedRessya
// ********************************

const CEnumToString<ERessyahoukou>& CconvCentDedOud::getERessyahoukouToString()
{
	static CEnumToString<ERessyahoukou> aEnumToString ;
	if ( aEnumToString.size() == 0 )
	{
		aEnumToString.add( Ressyahoukou_Kudari , _T("Kudari") ) ;
		aEnumToString.add( Ressyahoukou_Nobori , _T("Nobori") ) ;
	}
	return aEnumToString ;
};
const TCHAR nameRessyahoukou[]= _T("Houkou") ;
const TCHAR nameRessyasyubetsuIndex[]= _T("Syubetsu") ;
const TCHAR nameEkiJikoku3[]= _T("EkiJikoku") ;
const TCHAR nameRessyabangou[]= _T("Ressyabangou") ;
const TCHAR nameRessyamei[]= _T("Ressyamei") ;
const TCHAR nameGousuu[]= _T("Gousuu") ;
const TCHAR nameBikou[]= _T("Bikou") ;





int CconvCentDedOud::CentDedRessya_To_OuPropertiesText( 
			const CentDedRessya* pCentDedRessya , 
			OuPropertiesText::CNodeContainer* pCNodeContainer ) 
{
	int iRv = 0 ;
	// --------------------------------
	//0.IsNull
	bool bIsNull = false ;
	if ( iRv >= 0 )
	{
		bIsNull = pCentDedRessya->isNull() ;
	}

	if ( !bIsNull )
	{
		//1.Ressyahoukou
		if ( iRv >= 0 )
		{
			tstring strValue = getERessyahoukouToString().stringOf( 
				pCentDedRessya->getRessyahoukou() ) ;
			if ( strValue.empty() )
			{
				iRv = -12 ;	//	Ressyahoukou の値が不正です。
			}
			else
			{
				pCNodeContainer->setValue( nameRessyahoukou , 
					strValue ) ;
			}
		}
		//2.RessyasyubetsuIndex ;
		if ( iRv >= 0 )
		{
			pCNodeContainer->setValue( 
				nameRessyasyubetsuIndex , 
				stringOf( 
					pCentDedRessya->getRessyasyubetsuIndex() 
				) 
			) ;
		}


		//4."Ressyabangou" ;
		if ( iRv >= 0 )
		{
			tstring strValue = pCentDedRessya->getRessyabangou() ;
			if ( !strValue.empty() )
			{
				pCNodeContainer->setValue( nameRessyabangou , 
					strValue ) ;
			}
		}
		//5."Ressyamei" ;
		if ( iRv >= 0 )
		{
			tstring strValue = pCentDedRessya->getRessyamei() ;
			if ( !strValue.empty() )
			{
				pCNodeContainer->setValue( nameRessyamei , 
					 strValue) ;
			}
		}
		//6."Gousuu" ;
		if ( iRv >= 0 )
		{
			tstring strValue = pCentDedRessya->getGousuu() ;
			if ( !strValue.empty() )
			{
				pCNodeContainer->setValue( nameGousuu , 
					strValue ) ;
			}
		}
		//3.EkiJikoku3
		if ( iRv >= 0 )
		{
			vector<tstring>	contstrEkijikoku ;
			int iEkiOrder ;
			for ( iEkiOrder = 0 ; 
					iEkiOrder <= pCentDedRessya->getSyuuchakuEki() ; 
					iEkiOrder ++ )
			{
				CentDedEkiJikoku	aCentDedEkiJikoku = 
					pCentDedRessya->getCentDedEkiJikoku( iEkiOrder ) ;
				tstring	strEkijikoku = CentDedEkiJikoku_To_string(
					&aCentDedEkiJikoku ) ;
				
				contstrEkijikoku.push_back( strEkijikoku ) ;
			}
			tstring strEkijikoku2 = joinc( ',' , contstrEkijikoku ) ;
			pCNodeContainer->setValue( nameEkiJikoku3 ,
						strEkijikoku2 ) ; 
		}
		//7."Bikou" ;
		if ( iRv >= 0 )
		{
			tstring strValue = pCentDedRessya->getBikou() ;
			if ( !strValue.empty() )
			{
				pCNodeContainer->setValue( nameBikou , 
					strValue ) ;
			}
		}
	}
	// --------------------------------
	return ( iRv ) ;
}

// ********************************
//	CentDedRessyaCont
// ********************************
const TCHAR nameRessya[]= _T("Ressya") ;

int CconvCentDedOud::CentDedRessyaCont_To_OuPropertiesText( 
			const CentDedRessyaCont* pCentDedRessyaCont , 
			OuPropertiesText::CNodeContainer* pCNodeContainer ) 
{
	int iRv = 0 ;
	
		
	int idxRessya ;
	for ( idxRessya = 0 ; idxRessya < pCentDedRessyaCont->size() ; 
			idxRessya ++ )
	{
		Ou<CDirectory> pCDirectory = OuNew<CDirectory>( new CDirectory( nameRessya ) ) ;

		const CentDedRessya*	pCentDedRessya = 
			pCentDedRessyaCont->getMuPtr()->get( idxRessya );
		int iResult = CentDedRessya_To_OuPropertiesText( 
			pCentDedRessya , pCDirectory->getCNodeContainer() ) ;
		//	-	-12 ;	//	Ressyahoukou の値が不正です。
		if ( iResult < 0 )
		{
			iRv = iResult ;
		}
		else
		{
			pCNodeContainer->insert( pCDirectory ) ;
		}
	}
	
	return ( iRv ) ;
}

// ********************************
//	CentDedDia
// ********************************
const TCHAR nameDiaName[]=_T("DiaName") ;

int CconvCentDedOud::CentDedDia_To_OuPropertiesText( 
			const CentDedDia* pCentDedDia , 
			OuPropertiesText::CNodeContainer* pCNodeContainer ) 
{
	int iRv = 0 ;

	//1.DiaName
	if ( iRv >= 0 )
	{
		pCNodeContainer->setValue( nameDiaName , 
			pCentDedDia->getName() ) ;
	}
	//3.Kudari
	//  Nobori
	if ( iRv >= 0 )
	{
		int iRessyahoukou = 0 ; 
		for ( iRessyahoukou = Ressyahoukou_Kudari ; 
				iRessyahoukou <= Ressyahoukou_Nobori ; 
				iRessyahoukou ++ )
		{
			ERessyahoukou eRessyahoukou = (ERessyahoukou)iRessyahoukou ;
			tstring	strRessyahoukou = 
				getERessyahoukouToString().stringOf( eRessyahoukou ) ;
			
			Ou<CDirectory> pCDirectory = OuNew<CDirectory>( 
				new CDirectory( strRessyahoukou ) ) ;
			int iResult = CentDedRessyaCont_To_OuPropertiesText( 
				pCentDedDia->getCentDedRessyaCont( (ERessyahoukou)iRessyahoukou ) , 
				pCDirectory->getCNodeContainer() );
			//iResult = 
			//	-12 ;	//	Ressyahoukou の値が不正です。
			if ( iResult < 0 )
			{
				iRv = iResult ;
			}
			else
			{
				pCNodeContainer->insert( pCDirectory ) ;
			}
		}
	}
	
	return ( iRv ) ;
}

	// ********************************
	//	CentDedDiaCont
	// ********************************
const TCHAR nameDia[] = _T("Dia") ;
	
int CconvCentDedOud::CentDedDiaCont_To_OuPropertiesText( 
			const CentDedDiaCont* pCentDedDiaCont , 
			OuPropertiesText::CNodeContainer* pCNodeContainer ) 
{
	int iRv = 0 ;
	for ( int idxDia = 0 ; iRv >= 0 && idxDia < pCentDedDiaCont->size() ; idxDia ++ )
	{
		Ou<CDirectory> pCDirectory = OuNew<CDirectory>( new CDirectory( nameDia ) ) ;
		CentDedDia aCentDedDia = pCentDedDiaCont->get( idxDia ) ; 
		if ( iRv >= 0 )
		{
			int iResult = CentDedDia_To_OuPropertiesText( 
				&aCentDedDia , 
				pCDirectory->getCNodeContainer() ) ;
			if ( iResult < 0 )
			{
				//	-	-12 ;	//	DiagramEkiatsukai の値が不正です。
				iRv = iResult ;
			}
			else
			{
				pCNodeContainer->insert( pCDirectory ) ;
			}
		}
	}
	return iRv ;
}
	
// ********************************
//	CentDedRosen
// ********************************
const TCHAR nameRosenmei[] = _T("Rosenmei") ;
const TCHAR nameKitenJikoku[] = _T("KitenJikoku") ;
const TCHAR nameDiagramDgrYZahyouKyoriDefault[] = _T("DiagramDgrYZahyouKyoriDefault") ;
const TCHAR nameComment[] = _T("Comment") ;


int CconvCentDedOud::CentDedRosen_To_OuPropertiesText( 
			const CentDedRosen* pCentDedRosen , 
			OuPropertiesText::CNodeContainer* pCNodeContainer ) 
{
	int iRv = 0 ;

	//1.Rosenmei
	if ( iRv >= 0 )
	{
		pCNodeContainer->setValue( nameRosenmei , 
			pCentDedRosen->getName() ) ;
	}
	//2.Eki[]
	if ( iRv >= 0 )
	{
		int iResult = CentDedEkiCont_To_OuPropertiesText( 
			*pCentDedRosen->getCentDedEkiCont() , 
			pCNodeContainer ) ;
		//	-	-22 ;	//	Ekijikokukeisiki の値が不正です。
		//	-	-32 ;	//	Ekikibo の値が不正です。
		if ( iResult < 0 )
		{
			//	-	-22 ;	//	Ekijikokukeisiki の値が不正です。
			//	-	-32 ;	//	Ekikibo の値が不正です。
			iRv = iResult ;
		}
	}
	

	//3.Ressyasyubetsu[]
	if ( iRv >= 0 )
	{
		int iResult = CentDedRessyasyubetsuCont_To_OuPropertiesText( 
			*pCentDedRosen->getCentDedRessyasyubetsuCont() , 
			pCNodeContainer ) ;
		//	-	-11 ;	//	Syubetsumei が指定されていません。
		//	-	-52 ;	//	DiagramSenStyle の値が不正です。
		if ( iResult < 0 )
		{
			//	-	-111 ;	//	Syubetsumei が指定されていません。
			//	-	-152 ;	//	DiagramSenStyle の値が不正です。
			iRv = iResult - 100 ;
		}
	}
	
	//4.Dia[]
	if ( iRv >= 0 )
	{
		int iResult = CentDedDiaCont_To_OuPropertiesText( 
			pCentDedRosen->getCentDedDiaCont() , 
			pCNodeContainer ) ;
		//	-	-12 ;	//	DiagramEkiatsukai の値が不正です。
		if ( iResult < 0 )
		{
			//	-	-212 ;	//	DiagramEkiatsukai の値が不正です。
			iRv = iResult - 200 ;
		}
	}
	//5.KitenJikoku
	if ( iRv >= 0 )
	{
		pCNodeContainer->setValue( nameKitenJikoku , 
			g_CdDedJikokuConv.encode( pCentDedRosen->getKitenJikoku() ) ) ;
		
	}
	//6.DiagramDgrYZahyouKyoriDefault
	if ( iRv >= 0 )
	{
		pCNodeContainer->setValue( nameDiagramDgrYZahyouKyoriDefault , 
			stringOf( pCentDedRosen->getDiagramDgrYZahyouKyoriDefault() ) ) ;
	}
	//7.Comment
	if ( iRv >= 0 )
	{
		pCNodeContainer->setValue( nameComment ,pCentDedRosen->getComment() ) ;
	}
	return ( iRv ) ;
}
} //namespace entDed


