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
//	CconvCentDedS00.cpp
// ****************************************************************
*/
#include "stdafx.h"
#include <vector>
#include <map>
using namespace std ;

#include "str\strToInt.h"
#include "str\stringSplit.h"
#include "str\tstring.h"
#include "NsOu\OuNew.h"
#include "NsOu\dynamic_castOu.h"
#include "NsMu\CaMui.h"
#include "DcdCd\DcDrawProp\CconvDcDrawProp.h"
#include "CconvCentDedS00.h"
#include <tchar.h>

using namespace OuLib::Str ;
using namespace OuLib::Str::OuPropertiesText;
using namespace OuLib::Str::OuPropertiesText::ErrorInfo;

/*delete 遅いので抑止
#ifndef _CONSOLE
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
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
const TCHAR nameDownMain[] = _T("DownMain");
const TCHAR nameUpMain[] = _T("UpMain");
const TCHAR nameBrunchCoreEkiIndex[] = _T("BrunchCoreEkiIndex");
const TCHAR nameLoopOriginEkiIndex[] = _T("LoopOriginEkiIndex");
const TCHAR nameJikokuhyouTrackDisplayKudari[] = _T("JikokuhyouTrackDisplayKudari");
const TCHAR nameJikokuhyouTrackDisplayNobori[] = _T("JikokuhyouTrackDisplayNobori");
const TCHAR nameDiagramTrackDisplay[] = _T("DiagramTrackDisplay");
const TCHAR nameEkiTrack2Cont[] = _T("EkiTrack2Cont");

const CEnumToString< CentDedEki::EEkijikokukeisiki >& 
CconvCentDedS00::getEEkijikokukeisikiToString()
{
	static CEnumToString< CentDedEki::EEkijikokukeisiki >	aCEnumToString ;
	if ( aCEnumToString.size() == 0 )
	{
		aCEnumToString.add( CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsu , _T("Jikokukeisiki_Hatsu") ) ;
		aCEnumToString.add( CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku , _T("Jikokukeisiki_Hatsuchaku") ) ;
		aCEnumToString.add( CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku , _T("Jikokukeisiki_KudariChaku") ) ;
		aCEnumToString.add( CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku , _T("Jikokukeisiki_NoboriChaku")  ) ;
		//17.4.14 add_by_d_mania
		aCEnumToString.add( CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku , _T("Jikokukeisiki_KudariHatsuchaku") ) ;
		aCEnumToString.add( CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku , _T("Jikokukeisiki_NoboriHatsuchaku")  ) ;
	}
	return aCEnumToString ;
}


const CEnumToString< CentDedEki::EEkikibo >& 
CconvCentDedS00::getEEkikiboToString()
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
CconvCentDedS00::getEDiagramRessyajouhouHyoujiToString()
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

int CconvCentDedS00::CentDedEki_From_OuPropertiesText(
			CentDedEki* pCentDedEki ,
			const OuPropertiesText::IfNodeContainerConst* pCNodeContainer ,
			OuPropertiesText::ErrorInfo::COuErrorInfoContainer* pCOuErrorInfoContainer ) 
{
	int iRv = 0 ;
	
	CentDedEki	aCentDedEki ; 
	// --------------------------------	
	//1.Ekimei
	if ( iRv >= 0 )
	{
		tstring strValue = pCNodeContainer->getValue( nameEkimei ) ;
		//memo:
		//	以前は、空文字列の駅名はエラーでしたが、
		//	現在はこれを認めるようになりました。
		// oudiasecond1.01で、空文字は認めないようにし、空文字の場合は、適当な文字を入れておきます
		if (strValue.empty())
		{
			strValue = _T("00");
		}
		aCentDedEki.setEkimei( strValue ) ;
	}

	//2.Ekijikokukeisiki
	if ( iRv >= 0 )
	{
		tstring	strValue = pCNodeContainer->getValue( nameEkijikokukeisiki );
		CentDedEki::EEkijikokukeisiki eValue = CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsu ;
		if ( getEEkijikokukeisikiToString().fromString( strValue , &eValue ) < 0 )
		{
			COuErrorInfo aCOuErrorInfo( ERRREASON_EkijikokukeisikiIsInvalid() ) ;
			aCOuErrorInfo.getProp()->setValue( nameEkijikokukeisiki , strValue ) ;
			pCOuErrorInfoContainer->insert( aCOuErrorInfo ) ;
			iRv = -22 ;	//	Ekijikokukeisiki の値が不正です。
		}
		else
		{
			aCentDedEki.setEkijikokukeisiki( eValue ) ;
			/**
				駅時刻形式をもとに、カスタマイズ時刻表の時刻表示を設定します
			*/
			if (eValue == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
				eValue == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
				eValue == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku)
			{
				aCentDedEki.setJikokuhyouChakuJikokuDisplayKudari(true);
			}
			else
			{
				aCentDedEki.setJikokuhyouChakuJikokuDisplayKudari(false);
			}
			if (eValue == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
				eValue == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ||
				eValue == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
			{
				aCentDedEki.setJikokuhyouChakuJikokuDisplayNobori(true);
			}
			else
			{
				aCentDedEki.setJikokuhyouChakuJikokuDisplayNobori(false);
			}
			if (eValue == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsu ||
				eValue == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
				eValue == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku ||
				eValue == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ||
				eValue == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
			{
				aCentDedEki.setJikokuhyouHatsuJikokuDisplayKudari(true);
			}
			else
			{
				aCentDedEki.setJikokuhyouHatsuJikokuDisplayKudari(false);
			}
			if (eValue == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsu ||
				eValue == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
				eValue == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
				eValue == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku ||
				eValue == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
			{
				aCentDedEki.setJikokuhyouHatsuJikokuDisplayNobori(true);
			}
			else
			{
				aCentDedEki.setJikokuhyouHatsuJikokuDisplayNobori(false);
			}

			//Ver2.00.05 旧ファイルを読み込んだ時、発時刻のみ駅の番線表示省略をONにする
			if (eValue == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsu ||
				eValue == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku ||
				eValue == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
			{
				aCentDedEki.setJikokuhyouTrackOmit(true);
			}
		}

	}

	//3.Ekikibo
	if ( iRv >= 0 )
	{
		tstring	strValue = pCNodeContainer->getValue( nameEkikibo );
		CentDedEki::EEkikibo eValue = CentDedEki::EEkikibo::Ekikibo_Ippan ;
		if ( getEEkikiboToString().fromString( strValue , &eValue ) < 0 )
		{
			COuErrorInfo aCOuErrorInfo( ERRREASON_EkikiboIsInvalid() ) ;
			aCOuErrorInfo.getProp()->setValue( nameEkikibo , strValue ) ;
			pCOuErrorInfoContainer->insert( aCOuErrorInfo ) ;
			iRv = -32 ;	//	Ekikibo の値が不正です。
		}
		else
		{
			aCentDedEki.setEkikibo( eValue ) ; 
		}
	}
	//4.Kyoukaisen //境界線の読み込みは、分岐駅設定を求めるために残しておく。
	if ( iRv >= 0 )
	{
		tstring	strValue = pCNodeContainer->getValue( nameKyoukaisen ) ; 
		aCentDedEki.setKyoukaisen( _ttoi( strValue.c_str() ) == 1 ) ;
	}

	//5. m_eDiagramRessyajouhouHyoujiKudari ;
	if ( iRv >= 0 )
	{
		tstring	strValue = pCNodeContainer->getValue( nameDiagramRessyajouhouHyoujiKudari ) ; 
		CentDedEki::EDiagramRessyajouhouHyouji eValue = 
			CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Origin ;
		if ( strValue.length() > 0 && 
			getEDiagramRessyajouhouHyoujiToString().fromString( strValue , &eValue ) < 0 )
		{
			COuErrorInfo aCOuErrorInfo( ERRREASON_DiagramRessyajouhouHyoujiIsInvalid() ) ;
			aCOuErrorInfo.getProp()->setValue( nameDiagramRessyajouhouHyoujiKudari , strValue ) ;
			pCOuErrorInfoContainer->insert( aCOuErrorInfo ) ;
			iRv = -41 ;	//	DiagramRessyajouhouHyoujiKudari の値が不正です。
		}
		else
		{
			aCentDedEki.setDiagramRessyajouhouHyoujiKudari( eValue ) ;
		}
	}
	//6.m_eDiagramRessyajouhouHyoujiNobori
	if ( iRv >= 0 )
	{
		tstring	strValue = pCNodeContainer->getValue( nameDiagramRessyajouhouHyoujiNobori ) ; 
		CentDedEki::EDiagramRessyajouhouHyouji eValue = 
			CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Origin ;
		if ( strValue.length() > 0 && 
			getEDiagramRessyajouhouHyoujiToString().fromString( strValue , &eValue ) < 0 )
		{
			COuErrorInfo aCOuErrorInfo( ERRREASON_DiagramRessyajouhouHyoujiIsInvalid() ) ;
			aCOuErrorInfo.getProp()->setValue( nameDiagramRessyajouhouHyoujiNobori , strValue ) ;
			pCOuErrorInfoContainer->insert( aCOuErrorInfo ) ;
			iRv = -42 ;	//	DiagramRessyajouhouHyoujiNobori の値が不正です。
		}
		else
		{
			aCentDedEki.setDiagramRessyajouhouHyoujiNobori( eValue ) ;
		}
	}

	if ( iRv >= 0 ){
		*pCentDedEki = aCentDedEki ;
	}
	return ( iRv ) ;
}

	// ********************************
	//	CentDedEkiCont
	// ********************************
const TCHAR nameEki[] = _T("Eki") ;
	
int CconvCentDedS00::CentDedEkiCont_From_OuPropertiesText(
			CentDedEkiCont* pCentDedEkiCont ,
			const OuPropertiesText::IfNodeContainerConst* pCNodeContainer ,
			OuPropertiesText::ErrorInfo::COuErrorInfoContainer* pCOuErrorInfoContainer ) 
{
	int iRv = 0 ;
	if ( iRv >= 0 )
	{
		for ( int idxEki = 0 ; iRv >= 0 && idxEki < pCNodeContainer->sizeInName( nameEki )  ; idxEki ++ )
		{
			Ou<const CDirectory> pCDirectory ; 
			if ( iRv >= 0 )
			{
				pCDirectory = dynamic_castOu<const CDirectory>( 
					pCNodeContainer->getInName( nameEki , idxEki ) ) ;
				if ( pCDirectory == NULL )
				{
					COuErrorInfo aCOuErrorInfo( ERRREASON_EkiIsNotDirectory() ) ;
					aCOuErrorInfo.getProp()->setValue( 
						ERRPROP_Index() , stringOf( idxEki ) ) ;
					pCOuErrorInfoContainer->insert( aCOuErrorInfo ) ;
					iRv = -101 ;	//	Eki がディレクトリではありません。

				}
			}
			//pCDirectory = 対応するディレクトリ

			CentDedEki aCentDedEki ;
			if ( iRv >= 0 )
			{
				int iResult = CentDedEki_From_OuPropertiesText( 
					&aCentDedEki , 
					pCDirectory->getIfNodeContainerConst() , 
					pCOuErrorInfoContainer ) ;
				if ( iResult < 0 )
				{
					iRv = iResult ;
					//	-	-22 ;	//	Ekijikokukeisiki の値が不正です。
					//	-	-32 ;	//	Ekikibo の値が不正です。
					//	-	-41 ;	//	DiagramRessyajouhouHyoujiKudari の値が不正です。
					//	-	-42 ;	//	DiagramRessyajouhouHyoujiNobori の値が不正です。
				}
			}
			//aCentDedEki = Directory の内容を反映しました。
			if ( iRv >= 0 )
			{
				pCentDedEkiCont->insert( aCentDedEki ) ;
			}
				
		}
	}
	//可能な範囲で分岐駅設定を行う
	//(1)境界線がtrueかつ、下り着時刻の場合は、下方向に同名かつ発着の駅がある場合、その駅を基幹駅に設定する
	//(2)一つ上の駅の境界線がtrueかつ、上り着時刻の場合は、上方向に同名かつ発着の駅がある場合、その駅を基幹駅に設定する
	//いずれの場合も、基幹駅・派生駅が一般駅の場合、主要駅に変更する。
	if (iRv >= 0)
	{
		for (int idx = 1; idx < pCentDedEkiCont->size() - 1; idx++)
		{
			CentDedEki* pCentDedEki = pCentDedEkiCont->getMuPtr()->get(idx);
			CentDedEki* pCentDedEkiPrev = pCentDedEkiCont->getMuPtr()->get(idx-1);
			if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku &&
				pCentDedEki->getKyoukaisen())
			{
				for (int idxs = idx + 1; idxs < pCentDedEkiCont->size() - 1; idxs++)
				{
					CentDedEki* pCentDedEkiSearch = pCentDedEkiCont->getMuPtr()->get(idxs);
					if (pCentDedEki->getEkimei() == pCentDedEkiSearch->getEkimei() &&
						pCentDedEkiSearch->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku)
					{
						pCentDedEki->setBrunchCoreEkiIndex(idxs);
						pCentDedEki->setEkikibo(CentDedEki::EEkikibo::Ekikibo_Syuyou);
						pCentDedEkiSearch->setEkikibo(CentDedEki::EEkikibo::Ekikibo_Syuyou);
						break;
					}
					
				}
			}
			else if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku &&
				pCentDedEkiPrev->getKyoukaisen())
			{
				for (int idxs = idx - 1; idxs >0; idxs--)
				{
					CentDedEki* pCentDedEkiSearch = pCentDedEkiCont->getMuPtr()->get(idxs);
					if (pCentDedEki->getEkimei() == pCentDedEkiSearch->getEkimei() &&
						pCentDedEkiSearch->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku)
					{
						pCentDedEki->setBrunchCoreEkiIndex(idxs);
						pCentDedEki->setEkikibo(CentDedEki::EEkikibo::Ekikibo_Syuyou);
						pCentDedEkiSearch->setEkikibo(CentDedEki::EEkikibo::Ekikibo_Syuyou);
						break;
					}

				}
			}
		}
	}
	if (iRv >= 0)
	{
		pCentDedEkiCont->adjustBrunchLoopCont();
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
//const TCHAR nameJikokuhyouBackColor[] = _T("JikokuhyouBackColor");
const TCHAR nameDiagramSenColor[]= _T("DiagramSenColor") ;
const TCHAR nameDiagramSenStyle[]= _T("DiagramSenStyle") ;
const TCHAR nameDiagramSenIsBold[]= _T("DiagramSenIsBold") ;
const TCHAR nameDiagramRessyaFont[] = _T("DiagramRessyaFont") ;
const TCHAR nameStopMarkDrawType[] = _T("StopMarkDrawType") ;

const CEnumToString< CentDedRessyasyubetsu::ESenStyle >& 
CconvCentDedS00::getESenStyleToString()
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
CconvCentDedS00::getEStopMarkDrawTypeToString()
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

int CconvCentDedS00::CdDiagramLineStyle_From_OuPropertiesText(
	CentDedRessyasyubetsu::CdDiagramLineStyle* pCdDiagramLineStyle ,
	const OuPropertiesText::IfNodeContainerConst* pCNodeContainer ,
	OuPropertiesText::ErrorInfo::COuErrorInfoContainer* pCOuErrorInfoContainer ) 
{
	int iRv = 0 ;

	CentDedRessyasyubetsu::CdDiagramLineStyle aCdDiagramLineStyle;

	// --------------------------------	
	//5.DiagramSenColor
	if ( iRv >= 0 ){
		tstring	strValue = pCNodeContainer->getValue( 
			nameDiagramSenColor ) ;
		aCdDiagramLineStyle.setDiagramSenColor( 
			CdColorProp_from_string( strValue ) ) ;
	}
	
	//6.DiagramSenStyle
	if ( iRv >= 0 )
	{
		tstring	strValue = pCNodeContainer->getValue( 
			nameDiagramSenStyle ) ;
		CentDedRessyasyubetsu::ESenStyle eValue = CentDedRessyasyubetsu::SenStyle_Jissen ;
		if ( getESenStyleToString().fromString( strValue , &eValue ) < 0 )
		{
			COuErrorInfo	aCOuErrorInfo( ERRREASON_DiagramSenStyleIsInvalid() ) ;
			aCOuErrorInfo.getProp()->setValue( nameDiagramSenStyle , strValue ) ;
			pCOuErrorInfoContainer->insert( aCOuErrorInfo ) ;
			iRv = -52 ;	//	DiagramSenStyle の値が不正です。
		}
		else
		{
			aCdDiagramLineStyle.setDiagramSenStyle( eValue ) ;
		}
	}

	//7.DiagramSenIsBold
	if ( iRv >= 0 )
	{
		tstring	strValue = pCNodeContainer->getValue( 
			nameDiagramSenIsBold ) ;
		unsigned long iValue = _tcstoul( strValue.c_str() , NULL , 10 ) ;
		aCdDiagramLineStyle.setDiagramSenIsBold( iValue != 0 ) ;
	}
	// --------------------------------
	if ( iRv >= 0 )
	{
		*pCdDiagramLineStyle = aCdDiagramLineStyle ;
	}
	return iRv ;
}

int CconvCentDedS00::CentDedRessyasyubetsu_From_OuPropertiesText(
			CentDedRessyasyubetsu* pCentDedRessyasyubetsu ,
			const OuPropertiesText::IfNodeContainerConst* pCNodeContainer ,
			OuPropertiesText::ErrorInfo::COuErrorInfoContainer* pCOuErrorInfoContainer ) 
{
	int iRv = 0 ;

	CentDedRessyasyubetsu aCentDedRessyasyubetsu ;

	// --------------------------------	
	//1.Syubetsumei
	if ( iRv >= 0 )
	{
		tstring	strValue = pCNodeContainer->getValue( nameSyubetsumei ) ;
		if ( strValue.empty() )
		{
			COuErrorInfo	aCOuErrorInfo( ERRREASON_SyubetsumeiIsInvalid() ) ;
			aCOuErrorInfo.getProp()->setValue( nameSyubetsumei , strValue ) ;
			pCOuErrorInfoContainer->insert( aCOuErrorInfo ) ;
			iRv = -11 ;	//	Syubetsumei が指定されていません。
		}
		else
		{
			aCentDedRessyasyubetsu.setSyubetsumei( strValue ) ;
		}
	}
	
	//2.Ryakusyou
	if ( iRv >= 0 ){
		tstring	strValue = pCNodeContainer->getValue( nameRyakusyou ) ;
		if ( strValue.empty() ){
		}	else	{
			aCentDedRessyasyubetsu.setRyakusyou( strValue ) ;
		}
	}
	
	//3.JikokuhyouMojiColor
	if ( iRv >= 0 )
	{
		tstring	strValue = pCNodeContainer->getValue( 
			nameJikokuhyouMojiColor ) ;
		aCentDedRessyasyubetsu.setJikokuhyouMojiColor( 
			CdColorProp_from_string( strValue ) ) ;
	}
	//4.JikokuhyouFontIndex
	if ( iRv >= 0 )
	{
		tstring strValue = pCNodeContainer->getValue( 
			nameJikokuhyouFontIndex ) ;
		if ( !strValue.empty() )
		{
			int iValue = intOf( strValue ) ;
			if ( !( 0 <= iValue && iValue < CentDedRessyasyubetsu::JIKOKUHYOUFONT_COUNT ) )
			{
				COuErrorInfo	aCOuErrorInfo( ERRREASON_InvalidValueFormat() ) ;
				aCOuErrorInfo.getProp()->setValue( ERRPROP_Name() , nameJikokuhyouFontIndex ) ;
				aCOuErrorInfo.getProp()->setValue( ERRPROP_Value() , strValue ) ;
				pCOuErrorInfoContainer->insert( aCOuErrorInfo ) ;
				iRv = -101 ;	//	値の形式が正しくありません。
			}
			else
			{
				aCentDedRessyasyubetsu.setJikokuhyouFontIndex( iValue ) ;
			}
		}
	}
	//5.DiagramSenColor
	//6.DiagramSenStyle
	//7.DiagramSenIsBold
	{
		CentDedRessyasyubetsu::CdDiagramLineStyle	aCdDiagramLineStyle ;
		int iResult = CdDiagramLineStyle_From_OuPropertiesText( 
			&aCdDiagramLineStyle ,
			pCNodeContainer ,
			pCOuErrorInfoContainer ) ;
		//iResult = 
		//	-52 ;	//	DiagramSenStyle の値が不正です。
		if ( iResult < 0 )
		{
			iRv = iResult ;
			//iRv = 
			//	-52 ;	//	DiagramSenStyle の値が不正です。
		}
		else
		{
			aCentDedRessyasyubetsu.setCdDiagramLineStyle( aCdDiagramLineStyle ) ;
		}
	}
	

	//9 StopMarkDrawType
	if ( iRv >= 0 )
	{
		CentDedRessyasyubetsu::EStopMarkDrawType eStopMarkDrawType = 
			CentDedRessyasyubetsu::EStopMarkDrawType_DrawOnStop ;
		tstring strValue = pCNodeContainer->getValue( nameStopMarkDrawType ) ;
		if ( !strValue.empty() )
		{
			getEStopMarkDrawTypeToString().fromString( strValue , &eStopMarkDrawType ) ;
		}
		aCentDedRessyasyubetsu.setStopMarkDrawType( eStopMarkDrawType ) ;
	}

	// --------------------------------
	if ( iRv >= 0 )
	{
		*pCentDedRessyasyubetsu = aCentDedRessyasyubetsu ;
	}

	return ( iRv ) ;
}

	// ********************************
	//	CentDedRessyasyubetsuCont
	// ********************************
const TCHAR nameRessyasyubetsu[] = _T("Ressyasyubetsu") ;
		
int CconvCentDedS00::CentDedRessyasyubetsuCont_From_OuPropertiesText(
			CentDedRessyasyubetsuCont* pCentDedRessyasyubetsuCont ,
			const OuPropertiesText::IfNodeContainerConst* pCNodeContainer ,
			OuPropertiesText::ErrorInfo::COuErrorInfoContainer* pCOuErrorInfoContainer ) 
{
	int iRv = 0 ;
	if ( iRv >= 0 )
	{
		for ( int idx = 0 ; iRv >= 0 && idx < pCNodeContainer->sizeInName( nameRessyasyubetsu )  ; idx ++ )
		{
			Ou<const CDirectory> pCDirectory ; 
			if ( iRv >= 0 )
			{
				pCDirectory = dynamic_castOu<const CDirectory>( 
					pCNodeContainer->getInName( nameRessyasyubetsu , idx ) ) ;
				if ( pCDirectory == NULL )
				{
					COuErrorInfo aCOuErrorInfo( ERRREASON_RessyasyubetsuIsNotDirectory() ) ;
					aCOuErrorInfo.getProp()->setValue( 
						ERRPROP_Index() , stringOf( idx ) ) ;
					pCOuErrorInfoContainer->insert( aCOuErrorInfo ) ;
					iRv = -101 ;	//	Ressyasyubetsu がディレクトリではありません。

				}
			}
			//pCDirectory = 対応するディレクトリ

			CentDedRessyasyubetsu aCentDedRessyasyubetsu ;
			if ( iRv >= 0 )
			{
				int iResult = CentDedRessyasyubetsu_From_OuPropertiesText( 
					&aCentDedRessyasyubetsu , 
					pCDirectory->getIfNodeContainerConst() , 
					pCOuErrorInfoContainer ) ;
				//	-	-11 ;	//	Syubetsumei が指定されていません。
				//	-	-52 ;	//	DiagramSenStyle の値が不正です。
				if ( iResult < 0 )
				{
					iRv = iResult ;
					//	-	-11 ;	//	Syubetsumei が指定されていません。
					//	-	-52 ;	//	DiagramSenStyle の値が不正です。
				}
			}
			//aCentDedRessyasyubetsu = Directory の内容を反映しました。
			if ( iRv >= 0 )
			{
				//	列車種別コンテナに既にデータがある場合は、それを上書きします
				//	列車種別コンテナは、少なくとも1つの要素を持っています。
				if ( idx < pCentDedRessyasyubetsuCont->size() )
				{
					pCentDedRessyasyubetsuCont->set( aCentDedRessyasyubetsu , idx ) ;
				}
				else
				{
					pCentDedRessyasyubetsuCont->insert( aCentDedRessyasyubetsu ) ;
				}
			}
				
		}
	}
	return iRv ;
}

	// ********************************
	//	CentDedEkiJikoku
	// ********************************

int CconvCentDedS00::CentDedEkiJikoku_From_string(
			CentDedEkiJikoku* pCentDedEkiJikoku , 
			const tstring strValue,
			const int iMainTrack)
{
	int iRv = 0 ;
	// --------------------------------
	tstring strEkijikoku = strValue ;
	tstring	strEkiatsukai ;
	tstring strChaku ;
	tstring strHatsu ;

	tstring::size_type pos = 0 ;
	pos = strEkijikoku.find( ';' ) ;
	if ( pos != tstring::npos )
	{
		strEkiatsukai = strEkijikoku.substr( 0 , pos ) ;
		strEkijikoku.erase( 0 , pos + 1 ) ;
		
		pos = strEkijikoku.find( '/' ) ;
		if ( pos != tstring::npos )
		{
			strChaku = strEkijikoku.substr( 0 , pos ) ;
			strEkijikoku.erase( 0 , pos + 1 ) ;
		}
		strHatsu = strEkijikoku ;
	}
	else
	{
		strEkiatsukai = strEkijikoku ;
	}
	//strEkiatsukai = 駅扱・空文字列は『運行なし』。"1"～"3" ;
	//strChaku = 着時刻
	//strHatsu = 発時刻
	
	int iEkiatsukai = 0 ;
	if ( !strEkiatsukai.empty() )
	{
		iEkiatsukai = _ttoi( strEkiatsukai.c_str() ) ;
	}
	/**
		Ver2.0 経由なし削除に伴い、経由なし(3)は運行なしに変更。
	*/
	if ( !( 0 <= iEkiatsukai && iEkiatsukai <= 2 ) )
	{
		iEkiatsukai = 0 ;
	}
	CdDedJikoku jikokuChaku( strChaku ) ;
	CdDedJikoku jikokuHatsu( strHatsu ) ;
	CentDedEkiJikoku	aCentDedEkiJikoku( 
		(CentDedEkiJikoku::EEkiatsukai)iEkiatsukai , 
		jikokuChaku , jikokuHatsu , iMainTrack) ;

	// --------------------------------
	if ( pCentDedEkiJikoku != NULL )
	{
		*pCentDedEkiJikoku = aCentDedEkiJikoku ;
	}
	return iRv ;
}

// ********************************
//	CentDedRessya
// ********************************

const CEnumToString<ERessyahoukou>& CconvCentDedS00::getERessyahoukouToString()
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


int CconvCentDedS00::CentDedRessya_From_OuPropertiesText(
			CentDedRessya* pCentDedRessya,
			const OuPropertiesText::IfNodeContainerConst* pCNodeContainer ,
			OuPropertiesText::ErrorInfo::COuErrorInfoContainer* pCOuErrorInfoContainer ) 
{
	int iRv = 0 ;
	// --------------------------------
	bool	bIsNull = false ;
	ERessyahoukou	eRessyahoukou = Ressyahoukou_Kudari ;
	//1.Ressyahoukou
	if ( iRv >= 0 )
	{
		tstring	strValue = pCNodeContainer->getValue( nameRessyahoukou );
		int iResult = getERessyahoukouToString().fromString( 
			strValue , &eRessyahoukou ) ;
		if ( iResult < 0 )
		{
			bIsNull = true ;
		}
	}
	//bIsNull = この列車に関する記述がない場合は、真です。
	//eRessyahoukou = 1.Ressyahoukouの値。
	//	但し、bIsNull が真の場合は、この値は無効です。
	
	if ( !bIsNull )
	{
		int iRessyasyubetsuIndex = -1 ; 
		//2.RessyasyubetsuIndex ;
		if ( iRv >= 0 )
		{
			tstring	strValue = pCNodeContainer->getValue( 
				nameRessyasyubetsuIndex ) ;
			int iValue = _ttoi( strValue.c_str() ) ;
			pCentDedRessya->setRessyasyubetsuIndex( iValue ) ;
		}
		
		//iRessyasyubetsuIndex = 2.RessyasyubetsuIndexの値。
		//	但し、bIsNull が真の場合は、この値は無効です。

		//4."Ressyabangou" ;
		if ( iRv >= 0 )
		{
			tstring	strValue = pCNodeContainer->getValue( nameRessyabangou ) ;
			pCentDedRessya->setRessyabangou( strValue ) ;
		}
		//5."Ressyamei" ;
		if ( iRv >= 0 ){
			tstring	strValue = pCNodeContainer->getValue( nameRessyamei ) ;
			pCentDedRessya->setRessyamei( strValue ) ;
		}
		//6."Gousuu" ;
		if ( iRv >= 0 ){
			tstring	strValue = pCNodeContainer->getValue( nameGousuu ) ;
			pCentDedRessya->setGousuu( strValue ) ;
		}
		int iMainTrack = 0;
		if (pCentDedRessya->getRessyahoukou() == ERessyahoukou::Ressyahoukou_Nobori)
		{
			iMainTrack = 1;
		}
		//3.EkiJikoku3
		if ( iRv >= 0 )
		{
			tstring strEkijikoku2 = pCNodeContainer->getValue( 
				nameEkiJikoku3 ) ;
			if ( !strEkijikoku2.empty() )
			{
				deque<tstring>	contstrEkijikoku = 
					splitc< deque< tstring > >( ',' , strEkijikoku2 ) ;
					
				int iEkiOrder ;
				for ( iEkiOrder = 0 ; iRv >= 0 && 
					iEkiOrder < (int)contstrEkijikoku.size()  ;
					iEkiOrder ++ )
				{
					tstring strEkijikoku = contstrEkijikoku[iEkiOrder] ;
					CentDedEkiJikoku	aCentDedEkiJikoku ;
					int iResult = CentDedEkiJikoku_From_string( 
						&aCentDedEkiJikoku , 
						strEkijikoku ,
						iMainTrack) ;
					assert( iResult >= 0 ) ;
					if ( iEkiOrder < pCentDedRessya->getCentDedEkiJikokuCont()->size() )
					{
						pCentDedRessya->setCentDedEkiJikoku( iEkiOrder , 
							aCentDedEkiJikoku ) ;
					}
					else
					{
						pCentDedRessya->getCentDedEkiJikokuCont()->insert( aCentDedEkiJikoku ) ;
					}
				}
			}
		}
		//7."Bikou" ;
		if ( iRv >= 0 ){
			tstring	strValue = pCNodeContainer->getValue( nameBikou ) ;
			pCentDedRessya->setBikou( strValue ) ;
		}
	}
	return ( iRv ) ;
}


// ********************************
//	CentDedRessyaCont
// ********************************
const TCHAR nameRessya[]= _T("Ressya") ;

int CconvCentDedS00::CentDedRessyaCont_From_OuPropertiesText(
			CentDedRessyaCont* pCentDedRessyaCont ,
			const OuPropertiesText::IfNodeContainerConst* pCNodeContainer ,
			OuPropertiesText::ErrorInfo::COuErrorInfoContainer* pCOuErrorInfoContainer ) 
{
	int iRv = 0 ;

	int iRessyaCount = 0 ;

	if ( iRv >= 0 )
	{
		int idxRessya ;
		for ( idxRessya = 0 ; iRv >= 0 && 
			idxRessya < pCNodeContainer->sizeInName( nameRessya )  ; 
				idxRessya ++ )
		{
			Ou<const CDirectory> pCDirectory = dynamic_castOu<const CDirectory>( 
				pCNodeContainer->getInName( nameRessya , idxRessya ) ) ;
			if ( pCDirectory != NULL )
			{
				CentDedRessya	aCentDedRessya( pCentDedRessyaCont->createNullRessya() );
				int iResult = CentDedRessya_From_OuPropertiesText( 
					&aCentDedRessya , 
					pCDirectory->getIfNodeContainerConst() , 
					pCOuErrorInfoContainer ) ;
				//iResult = 現在、この値が負の数になることはありません
				if ( iResult < 0 )
				{
					iRv = iResult ;
				}
				else
				{
					pCentDedRessyaCont->insert( aCentDedRessya );
				}
			}
		}
	}
	return ( iRv ) ;
}



// ********************************
//	CentDedDia
// ********************************
const TCHAR nameDiaName[]= _T("DiaName") ;
int CconvCentDedS00::CentDedDia_From_OuPropertiesText(
			CentDedDia* pCentDedDia ,
			const OuPropertiesText::IfNodeContainerConst* pCNodeContainer ,
			OuPropertiesText::ErrorInfo::COuErrorInfoContainer* pCOuErrorInfoContainer ) 
{
	int iRv = 0 ;
	
	int iEkiCount = pCentDedDia->getEkiCount() ;

	//1.DiaName
	tstring	strDiaName ;
	if ( iRv >= 0 )
	{
		tstring	strValue = pCNodeContainer->getValue( nameDiaName ) ;
		if ( strValue.length() == 0 )
		{
			ErrorInfo::COuErrorInfo aCOuErrorInfo( ERRREASON_DiaNameInvalid() ) ;
			pCOuErrorInfoContainer->insert( aCOuErrorInfo ) ;
			iRv = -11 ;	//	DiaName が指定されていません。
		}
		else
		{
			strDiaName = strValue ;
			pCentDedDia->setName( strDiaName ) ;
		}
	}

	//3.Ressya[Ressyahoukou_Kudari][]
	//  Ressya[Ressyahoukou_Nobori][]
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

			Ou<const CDirectory> pCDirectory ;
			if ( iRv >= 0 )
			{
				pCDirectory = dynamic_castOu< const CDirectory >( 
					pCNodeContainer->getInName( strRessyahoukou , 0 ) ) ;
				if ( pCDirectory == NULL )
				{
					ErrorInfo::COuErrorInfo aCOuErrorInfo( ERRREASON_ResyaContIsNotExist() ) ;
					aCOuErrorInfo.getProp()->setValue( ERRPROP_Ressyahoukou() , strRessyahoukou ) ;
					pCOuErrorInfoContainer->insert( aCOuErrorInfo ) ;
					iRv = -12 ;	//	RessyaContが見つかりません。
				}
			}
			//pCDirectory = Kudari,NoboriのRessyaCont
			if ( iRv >= 0 )
			{
				CentDedRessyaCont	aCentDedRessyaCont( 
					pCentDedDia->getCentDedRessyaCont( (ERessyahoukou)iRessyahoukou )->createEmptyCont() ) ; 

				int iResult = CentDedRessyaCont_From_OuPropertiesText( 
					&aCentDedRessyaCont , 
					pCDirectory->getIfNodeContainerConst() , 
					pCOuErrorInfoContainer );
				if ( iResult < 0 )
				{
				}
				else
				{
					*pCentDedDia->getCentDedRessyaCont( (ERessyahoukou)iRessyahoukou ) 
						= aCentDedRessyaCont ; 
				}
			}
		}
	}
	return ( iRv ) ;
}
	// ********************************
	//	CentDedDiaCont
	// ********************************
const TCHAR nameDia[] = _T("Dia") ;
	
int CconvCentDedS00::CentDedDiaCont_From_OuPropertiesText( 
			CentDedDiaCont* pCentDedDiaCont ,
			const OuPropertiesText::IfNodeContainerConst* pCNodeContainer ,
			OuPropertiesText::ErrorInfo::COuErrorInfoContainer* pCOuErrorInfoContainer ) 
{
	int iRv = 0 ;
	if ( iRv >= 0 )
	{
		for ( int idxDia = 0 ; 
			iRv >= 0 && idxDia < pCNodeContainer->sizeInName( nameDia ) ;
			idxDia ++ )
		{
			Ou<const CDirectory> pCDirectory = dynamic_castOu<const CDirectory>( 
				pCNodeContainer->getInName( nameDia , idxDia ) ) ;
			if ( pCDirectory != NULL )
			{
				CentDedDia aCentDedDia ;

				int iResult = CentDedDia_From_OuPropertiesText( 
					&aCentDedDia , 
					pCDirectory->getIfNodeContainerConst() , 
					pCOuErrorInfoContainer ) ;
				//	-	-11 ;	//	DiaName が指定されていません。
				//	-	-12 ;	//	RessyaContが見つかりません。
				if ( iResult < 0 )
				{
					//	-	-11 ;	//	DiaName が指定されていません。
					//	-	-12 ;	//	RessyaContが見つかりません。
					iRv = iResult ;
				}
				else
				{
					pCentDedDiaCont->insert( aCentDedDia ) ;
				}
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

int CconvCentDedS00::CentDedRosen_From_OuPropertiesText( 
			CentDedRosen* pCentDedRosen ,
			const OuPropertiesText::IfNodeContainerConst* pCNodeContainer ,
			OuPropertiesText::ErrorInfo::COuErrorInfoContainer* pCOuErrorInfoContainer ) 
{
	int iRv = 0 ;

	pCentDedRosen->clear() ;

	//1.Rosenmei
	if ( iRv >= 0 )
	{
		tstring	strValue = pCNodeContainer->getValue( nameRosenmei ) ;
		pCentDedRosen->setName( strValue ) ;
	}
	//2.Eki[]
	if ( iRv >= 0 )
	{
		CentDedEkiCont aCentDedEkiCont ;
		int iResult = CentDedEkiCont_From_OuPropertiesText( 
			&aCentDedEkiCont , 
			pCNodeContainer , 
			pCOuErrorInfoContainer ) ;
		//	-	-22 ;	//	Ekijikokukeisiki の値が不正です。
		//	-	-32 ;	//	Ekikibo の値が不正です。
		//	-	-41 ;	//	DiagramRessyajouhouHyoujiKudari の値が不正です。
		//	-	-42 ;	//	DiagramRessyajouhouHyoujiNobori の値が不正です。
		//	-	-101 ;	//	Eki がディレクトリではありません。
		if ( iResult < 0 )
		{
			//	-	-22 ;	//	Ekijikokukeisiki の値が不正です。
			//	-	-32 ;	//	Ekikibo の値が不正です。
			//	-	-41 ;	//	DiagramRessyajouhouHyoujiKudari の値が不正です。
			//	-	-42 ;	//	DiagramRessyajouhouHyoujiNobori の値が不正です。
			//	-	-101 ;	//	Eki がディレクトリではありません。
			iRv = iResult ;
		}
		else
		{
			//*pCentDedRosen->getCentDedEkiCont() = aCentDedEkiCont ;
			CaMui<CentDedEki>	aCaCont( pCentDedRosen->getCentDedEkiCont() ) ; 
			aCaCont.insert( &aCentDedEkiCont ) ;
		}
	}

	//3.Ressyasyubetsu[]
	if ( iRv >= 0 )
	{
		CentDedRessyasyubetsuCont aCentDedRessyasyubetsuCont ;
		int iResult = CentDedRessyasyubetsuCont_From_OuPropertiesText( 
			&aCentDedRessyasyubetsuCont , 
			pCNodeContainer , 
			pCOuErrorInfoContainer ) ;
		//	-	-11 ;	//	Syubetsumei が指定されていません。
		//	-	-52 ;	//	DiagramSenStyle の値が不正です。
		//	-	-101 ;	//	Ressyasyubetsu がディレクトリではありません。
		if ( iResult < 0 )
		{
			//	-	-111 ;	//	Syubetsumei が指定されていません。
			//	-	-152 ;	//	DiagramSenStyle の値が不正です。
			//	-	-201 ;	//	Ressyasyubetsu がディレクトリではありません。
			iRv = iResult - 100 ;
		}
		else
		{
			*pCentDedRosen->getCentDedRessyasyubetsuCont() = aCentDedRessyasyubetsuCont ;
		}
	}
	
	//4.Dia[]
	if ( iRv >= 0 )
	{
		CentDedDiaCont aCentDedDiaCont ;

		int iResult = CentDedDiaCont_From_OuPropertiesText( 
			&aCentDedDiaCont , 
			pCNodeContainer , 
			pCOuErrorInfoContainer ) ;
		//	-	-11 ;	//	DiaName が指定されていません。
		//	-	-12 ;	//	RessyaContが見つかりません。
		if ( iResult < 0 )
		{
			//	-	-211 ;	//	DiaName が指定されていません。
			//	-	-212 ;	//	RessyaContが見つかりません。
			iRv = iResult - 200 ;
		}
		else
		{
			//*pCentDedRosen->getCentDedDiaCont() = aCentDedDiaCont ;

			CaMui<CentDedDia>	aCaCont( pCentDedRosen->getCentDedDiaCont() ) ; 
			aCaCont.insert( &aCentDedDiaCont ) ;
		}
	}
	//4.1 AdjustBrunch
	if (iRv >= 0)
	{
		AdjustBrunch(
			pCentDedRosen->getCentDedEkiCont(),
			pCentDedRosen->getCentDedDiaCont());
	}



	//5.KitenJikoku
	if ( iRv >= 0 )
	{
		tstring	strValue = pCNodeContainer->getValue( nameKitenJikoku ) ;
		CdDedJikoku	aCdDedJikoku ;
		if ( !strValue.empty() )
		{
			if ( aCdDedJikoku.decode( strValue ) < 0 )
			{
				ErrorInfo::COuErrorInfo aCOuErrorInfo( ERRREASON_KitenjikokuIsInvalid() ) ;
				aCOuErrorInfo.getProp()->setValue( ERRPROP_Jikoku() , strValue ) ;
				pCOuErrorInfoContainer->insert( aCOuErrorInfo ) ;
				iRv = -352 ;	//	起点時刻の設定が不適切です。
			}
		}
		if ( iRv >= 0 )
		{
			pCentDedRosen->setKitenJikoku( aCdDedJikoku ) ;
		}
	}
	//6.DiagramDgrYZahyouKyoriDefault
	if ( iRv >= 0 )
	{
		tstring	strValue = pCNodeContainer->getValue( nameDiagramDgrYZahyouKyoriDefault ) ;
		int iDiagramDgrYZahyouKyoriDefault = 60 ;
		if ( !strValue.empty() )
		{
			iDiagramDgrYZahyouKyoriDefault = _ttoi( strValue.c_str() ) ;
			if ( !( 0 <= iDiagramDgrYZahyouKyoriDefault ) )
			{
				ErrorInfo::COuErrorInfo aCOuErrorInfo( ERRREASON_DiagramDgrYZahyouKyoriDefaultIsInvalid() ) ;
				aCOuErrorInfo.getProp()->setValue( ERRPROP_Value() , strValue ) ;
				pCOuErrorInfoContainer->insert( aCOuErrorInfo ) ;
				iRv = -353 ;	//	ダイヤグラムの既定の駅間幅が不正です。
			}
		}
		if ( iRv >= 0 )
		{
			pCentDedRosen->setDiagramDgrYZahyouKyoriDefault( iDiagramDgrYZahyouKyoriDefault ) ;
		}
	}

	if (iRv >= 0)
	{
		pCentDedRosen->adjustOperation();
	}

	if (iRv >= 0)
	{
		for (int idxDia = 0; idxDia < pCentDedRosen->getCentDedDiaCont()->size(); idxDia++)
		{
			pCentDedRosen->OperationConnect(idxDia);
		}
	}

	//7.Comment
	if ( iRv >= 0 ){
		tstring	strValue = pCNodeContainer->getValue( nameComment )  ;
		if ( iRv >= 0 )
		{
			pCentDedRosen->setComment( strValue ) ;
		}
	}


	return ( iRv ) ;
}

void CconvCentDedS00::AdjustBrunch(const CentDedEkiCont * pCentDedEkiCont, CentDedDiaCont * pCentDedDiaCont)
{
	for (int idxdia = 0; idxdia < pCentDedDiaCont->size(); idxdia++)
	{
		CentDedDia* pCentDedDia = pCentDedDiaCont->getMuPtr()->get(idxdia);
		for (int iRessyahoukou = Ressyahoukou_Kudari;
			iRessyahoukou <= Ressyahoukou_Nobori;
			iRessyahoukou++)
		{
			CentDedRessyaCont* pCentDedRessyaCont =
				pCentDedDia->getCentDedRessyaCont((ERessyahoukou)iRessyahoukou);
			for (int idxRessya = 0; idxRessya < pCentDedRessyaCont->size(); idxRessya++)
			{
				CentDedRessya* pCentDedRessya = pCentDedRessyaCont->getMuPtr()->get(idxRessya);
				pCentDedRessya->adjustBrunchConvert(
					pCentDedEkiCont);
			}
		}
	}
}

} //namespace entDed


