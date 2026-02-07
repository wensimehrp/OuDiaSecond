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
//	CconvCentDedS09.cpp
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
#include "CconvCentDedS09.h"
#include <stdexcept>
#include "CentDedBeforeOperation.h"
#include "CentDedAfterOperation.h"

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
//	CentDedEkiTrack2
// ********************************
const TCHAR nameTrackName[] = _T("TrackName");
const TCHAR nameTrackRyakusyou[] = _T("TrackRyakusyou");
const TCHAR nameTrackNoboriRyakusyou[] = _T("TrackNoboriRyakusyou");

int CconvCentDedS09::CentDedEkiTrack2_From_OuPropertiesText(
	CentDedEkiTrack2* pCentDedEkiTrack2,
	const OuPropertiesText::IfNodeContainerConst* pCNodeContainer,
	OuPropertiesText::ErrorInfo::COuErrorInfoContainer* pCOuErrorInfoContainer)
{
	int iRv = 0;

	CentDedEkiTrack2	aCentDedEkiTrack2;
	// --------------------------------	
	//1.TrackName
	if (iRv >= 0)
	{
		tstring strValue = pCNodeContainer->getValue(nameTrackName);
		if (strValue.empty())
		{
			COuErrorInfo	aCOuErrorInfo(ERRREASON_TrackNameIsInvalid());
			aCOuErrorInfo.getProp()->setValue(nameTrackName, strValue);
			pCOuErrorInfoContainer->insert(aCOuErrorInfo);
			iRv = -11;	//	TrackName が指定されていません。
		}
		else
		{
			aCentDedEkiTrack2.setTrackName(strValue);
		}
	}
	//2.TrackRyakusyou
	if (iRv >= 0)
	{
		tstring strValue = pCNodeContainer->getValue(nameTrackRyakusyou);
		if (strValue.empty())
		{
			COuErrorInfo	aCOuErrorInfo(ERRREASON_TrackRyakusyouIsInvalid());
			aCOuErrorInfo.getProp()->setValue(nameTrackRyakusyou, strValue);
			pCOuErrorInfoContainer->insert(aCOuErrorInfo);
			iRv = -21;	//	TrackRyakusyou が指定されていません。
		}
		else
		{
			aCentDedEkiTrack2.setTrackRyakusyou(strValue);
		}
	}
	//3.TrackNoboriRyakusyou
	if (iRv >= 0)
	{
		tstring strValue = pCNodeContainer->getValue(nameTrackNoboriRyakusyou);
		//if (strValue.empty())
		//{
		//	COuErrorInfo	aCOuErrorInfo(ERRREASON_TrackNoboriRyakusyouIsInvalid());
		//	aCOuErrorInfo.getProp()->setValue(nameTrackNoboriRyakusyou, strValue);
		//	pCOuErrorInfoContainer->insert(aCOuErrorInfo);
		//	iRv = -31;	//	TrackNoboriRyakusyou が指定されていません。
		//}
		//else
		if (!strValue.empty())
		{
			aCentDedEkiTrack2.setTrackNoboriRyakusyou(strValue);
		}
	}
	// --------------------------------
	if (iRv >= 0) {
		*pCentDedEkiTrack2 = aCentDedEkiTrack2;
	}
	return (iRv);
}

// ********************************
//	CentDedEkiTrack2Cont
// ********************************
const TCHAR nameEkiTrack2[] = _T("EkiTrack2");

int CconvCentDedS09::CentDedEkiTrack2Cont_From_OuPropertiesText(
	CentDedEkiTrack2Cont* pCentDedEkiTrack2Cont,
	const OuPropertiesText::IfNodeContainerConst* pCNodeContainer,
	OuPropertiesText::ErrorInfo::COuErrorInfoContainer* pCOuErrorInfoContainer)
{
	int iRv = 0;
	if (iRv >= 0)
	{
		int a = pCNodeContainer->sizeInName(nameEkiTrack2);
		for (int idx = 0; iRv >= 0 && idx < pCNodeContainer->sizeInName(nameEkiTrack2); idx++)
		{
			Ou<const CDirectory> pCDirectory;
			if (iRv >= 0)
			{
				pCDirectory = dynamic_castOu<const CDirectory>(
					pCNodeContainer->getInName(nameEkiTrack2, idx));
				if (pCDirectory == NULL)
				{
					COuErrorInfo aCOuErrorInfo(ERRREASON_EkiIsNotDirectory());
					aCOuErrorInfo.getProp()->setValue(
						ERRPROP_Index(), stringOf(idx));
					pCOuErrorInfoContainer->insert(aCOuErrorInfo);
					iRv = -101;	//	EkiTrack2 がディレクトリではありません。

				}
			}
			//pCDirectory = 対応するディレクトリ

			CentDedEkiTrack2 aCentDedEkiTrack2;
			if (iRv >= 0)
			{
				int iResult = CentDedEkiTrack2_From_OuPropertiesText(
					&aCentDedEkiTrack2,
					pCDirectory->getIfNodeContainerConst(),
					pCOuErrorInfoContainer);
				if (iResult < 0)
				{
					iRv = iResult;
					//	-	-11 ;	//	TrackName が指定されていません。
					//	-	-21 ;	//	TrackRyakusyou が指定されていません。
					//	-	-31 ;	//	TrackNoboriRyakusyou が指定されていません。
				}
			}
			//aCentDedEki = Directory の内容を反映しました。
			if (iRv >= 0)
			{
				pCentDedEkiTrack2Cont->insert(aCentDedEkiTrack2);
			}

		}
	}
	return iRv;
}

// ********************************
//	CentDedEki
// ********************************
const TCHAR nameEkimei[] = _T("Ekimei") ;
const TCHAR nameEkimeiJikokuRyaku[] = _T("EkimeiJikokuRyaku");
const TCHAR nameEkimeiDiaRyaku[] = _T("EkimeiDiaRyaku");
const TCHAR nameEkijikokukeisiki[] = _T("Ekijikokukeisiki") ;
const TCHAR nameEkikibo[] = _T("Ekikibo") ;
const TCHAR nameDiagramRessyajouhouHyoujiKudari[] = _T("DiagramRessyajouhouHyoujiKudari") ;
const TCHAR nameDiagramRessyajouhouHyoujiNobori[] = _T("DiagramRessyajouhouHyoujiNobori") ;
const TCHAR nameDownMain[] = _T("DownMain");
const TCHAR nameUpMain[] = _T("UpMain");
const TCHAR nameBrunchCoreEkiIndex[] = _T("BrunchCoreEkiIndex");
const TCHAR nameBrunchOpposite[] = _T("BrunchOpposite");
const TCHAR nameLoopOriginEkiIndex[] = _T("LoopOriginEkiIndex");
const TCHAR nameLoopOpposite[] = _T("LoopOpposite");
const TCHAR nameJikokuhyouTrackDisplayKudari[] = _T("JikokuhyouTrackDisplayKudari");
const TCHAR nameJikokuhyouTrackDisplayNobori[] = _T("JikokuhyouTrackDisplayNobori");
const TCHAR nameDiagramTrackDisplay[] = _T("DiagramTrackDisplay");
const TCHAR nameEkiTrack2Cont[] = _T("EkiTrack2Cont");
const TCHAR nameOuterTerminal[] = _T("OuterTerminal");
const TCHAR nameOuterTerminalEkimei[] = _T("OuterTerminalEkimei");
const TCHAR nameOuterTerminalJikokuRyaku[] = _T("OuterTerminalJikokuRyaku");
const TCHAR nameOuterTerminalDiaRyaku[] = _T("OuterTerminalDiaRyaku");
const TCHAR nameNextEkiDistance[] = _T("NextEkiDistance");
const TCHAR nameJikokuhyouTrackOmit[] = _T("JikokuhyouTrackOmit");
const TCHAR nameJikokuhyouOperationOrigin[] = _T("JikokuhyouOperationOrigin");
const TCHAR nameJikokuhyouOperationTerminal[] = _T("JikokuhyouOperationTerminal");
const TCHAR nameJikokuhyouJikokuDisplayKudari[] = _T("JikokuhyouJikokuDisplayKudari");
const TCHAR nameJikokuhyouJikokuDisplayNobori[] = _T("JikokuhyouJikokuDisplayNobori");
const TCHAR nameJikokuhyouSyubetsuChangeDisplayKudari[] = _T("JikokuhyouSyubetsuChangeDisplayKudari");
const TCHAR nameJikokuhyouSyubetsuChangeDisplayNobori[] = _T("JikokuhyouSyubetsuChangeDisplayNobori");
const TCHAR nameDiagramColorNextEki[] = _T("DiagramColorNextEki");
const TCHAR nameOperationTableDisplayJikoku[] = _T("OperationTableDisplayJikoku");




const CEnumToString< CentDedEki::EEkijikokukeisiki >& 
CconvCentDedS09::getEEkijikokukeisikiToString()
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
CconvCentDedS09::getEEkikiboToString()
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
CconvCentDedS09::getEDiagramRessyajouhouHyoujiToString()
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

int CconvCentDedS09::CentDedEki_From_OuPropertiesText( 
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

		aCentDedEki.setEkimei( strValue ) ;
	}
	//1.1.nameEkimeiJikokuRyaku
	if (iRv >= 0)
	{
		tstring strValue = pCNodeContainer->getValue(nameEkimeiJikokuRyaku);
		if (!strValue.empty())
		{
			aCentDedEki.setEkimeiJikokuhyouRyaku(strValue);
		}
	}
	//1.2.nameEkimeiDiaRyaku
	if (iRv >= 0)
	{
		tstring strValue = pCNodeContainer->getValue(nameEkimeiDiaRyaku);
		if (!strValue.empty())
		{
			aCentDedEki.setEkimeiDiagramRyaku(strValue);
		}
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

	//7.DownMain 
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(
			nameDownMain);
		int iValue = intOf(strValue);
		aCentDedEki.setDownMain(iValue);
	}
	//8.UpMain 
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(
			nameUpMain);
		int iValue = intOf(strValue);
		aCentDedEki.setUpMain(iValue);
	}
	//9.BrunchCoreEkiIndex,BrunchOpposite
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(
			nameBrunchCoreEkiIndex);
		int iValue;
		if (strValue == _T(""))
		{
			 iValue = -1;
		}
		else
		{
			iValue = intOf(strValue);
		}
		aCentDedEki.setBrunchCoreEkiIndex(iValue);
		if (iValue >= 0)
		{
			tstring	strValueO = pCNodeContainer->getValue(
				nameBrunchOpposite);
			aCentDedEki.setBrunchOpposite(intOf(strValueO) == 1);
		}
	}
	//10.LoopOriginEkiIndex
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(
			nameLoopOriginEkiIndex);
		int iValue;
		if (strValue == _T(""))
		{
			iValue = -1;
		}
		else
		{
			iValue = intOf(strValue);
		}
		aCentDedEki.setLoopOriginEkiIndex(iValue);
		if (iValue >= 0)
		{
			tstring	strValueO = pCNodeContainer->getValue(
				nameLoopOpposite);
			aCentDedEki.setLoopOpposite(intOf(strValueO) == 1);
		}
	}
	//11.JikokuhyouTrackDisplayKudari
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(nameJikokuhyouTrackDisplayKudari);
		aCentDedEki.setJikokuhyouTrackDisplayKudari(strValue == _T("1"));
	}
	//12.JikokuhyouTrackDisplayNobori
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(nameJikokuhyouTrackDisplayNobori);
		aCentDedEki.setJikokuhyouTrackDisplayNobori(strValue == _T("1"));
	}
	//13.DiagramTrackDisplay
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(nameDiagramTrackDisplay);
		aCentDedEki.setDiagramTrackDisplay(strValue == _T("1"));
	}
	//15.OuterTerminalEkimei
	if (iRv >= 0)
	{
		int iSize = pCNodeContainer->sizeInName(nameOuterTerminal);
		for (int idx = 0; idx < iSize; idx++)
		{
			Ou<const CDirectory> pCDirectory;
			if (iRv >= 0)
			{
				pCDirectory = dynamic_castOu<const CDirectory>(
					pCNodeContainer->getInName(nameOuterTerminal, idx));
				tstring strEkimei = pCDirectory->getIfNodeContainerConst()->getValue(
					nameOuterTerminalEkimei);
				tstring strJikokuRyaku = pCDirectory->getIfNodeContainerConst()->getValue(
					nameOuterTerminalJikokuRyaku);
				tstring strDiaRyaku = pCDirectory->getIfNodeContainerConst()->getValue(
					nameOuterTerminalDiaRyaku);

				if (!strEkimei.empty())
				{
					OuterTerminal sOuterTerminal(
						strEkimei,
						strJikokuRyaku,
						strDiaRyaku);
					aCentDedEki.insertOuterTerminalEkimei(sOuterTerminal, INT_MAX);
				}
			}
		}
	}
	//16.NextEkiDistance
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(
			nameNextEkiDistance);
		int iValue;
		if (strValue == _T(""))
		{
			iValue = 0;
		}
		else
		{
			iValue = intOf(strValue);
		}
		aCentDedEki.setNextEkiDistance(iValue);
	}
	//17.JikokuhyouTrackOmit
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(nameJikokuhyouTrackOmit);
		aCentDedEki.setJikokuhyouTrackOmit(strValue == _T("1"));
	}
	//18.JikokuhyouOperationOrigin 
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(
			nameJikokuhyouOperationOrigin);
		int iValue = 0;
		if (!strValue.empty())
		{
			iValue = stoi(strValue);
			if (iValue < 1 || iValue > 3)
			{
				iValue = 0;
			}
		}
		aCentDedEki.setJikokuhyouOperationOrigin(iValue);
	}
	//19.JikokuhyouOperationTerminal 
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(
			nameJikokuhyouOperationTerminal);
		int iValue = 0;
		if (!strValue.empty())
		{
			iValue = stoi(strValue);
			if (iValue < 1 || iValue > 3)
			{
				iValue = 0;
			}
		}
		aCentDedEki.setJikokuhyouOperationTerminal(iValue);
	}
	//20.JikokuhyouJikokuDisplayKudari
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(
			nameJikokuhyouJikokuDisplayKudari);
		vector<tstring> contValue = splitc<vector<tstring>>(',', strValue);
		if (contValue.size() >= 1 && !contValue[0].empty())
		{
			int iResult;
			try
			{
				iResult = stoi(contValue[0]);

				if (iResult < 0 || iResult>1)
				{
					iResult = 1;
				}
			}
			catch (std::invalid_argument e)
			{
				iResult = 1;
			}
			catch (std::out_of_range e)
			{
				iResult = 1;
			}
			aCentDedEki.setJikokuhyouChakuJikokuDisplayKudari(iResult);
		}
		else
		{
			aCentDedEki.setJikokuhyouChakuJikokuDisplayKudari(1);
		}

		if (contValue.size() >= 2 && !contValue[1].empty())
		{
			int iResult;
			try
			{
				iResult = stoi(contValue[1]);

				if (iResult < 0 || iResult>1)
				{
					iResult = 1;
				}
			}
			catch (std::invalid_argument e)
			{
				iResult = 1;
			}
			catch (std::out_of_range e)
			{
				iResult = 1;
			}
			aCentDedEki.setJikokuhyouHatsuJikokuDisplayKudari(iResult);
		}
		else
		{
			aCentDedEki.setJikokuhyouHatsuJikokuDisplayKudari(1);
		}
	}
	//21.JikokuhyouJikokuDisplayNobori
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(
			nameJikokuhyouJikokuDisplayNobori);
		vector<tstring> contValue = splitc<vector<tstring>>(',', strValue);
		if (contValue.size() >= 1 && !contValue[0].empty())
		{
			int iResult;
			try
			{
				iResult = stoi(contValue[0]);

				if (iResult < 0 || iResult>1)
				{
					iResult = 1;
				}
			}
			catch (std::invalid_argument e)
			{
				iResult = 1;
			}
			catch (std::out_of_range e)
			{
				iResult = 1;
			}
			aCentDedEki.setJikokuhyouChakuJikokuDisplayNobori(iResult);
		}
		else
		{
			aCentDedEki.setJikokuhyouChakuJikokuDisplayNobori(1);
		}

		if (contValue.size() >= 2 && !contValue[1].empty())
		{
			int iResult;
			try
			{
				iResult = stoi(contValue[1]);

				if (iResult < 0 || iResult>1)
				{
					iResult = 1;
				}
			}
			catch (std::invalid_argument e)
			{
				iResult = 1;
			}
			catch (std::out_of_range e)
			{
				iResult = 1;
			}
			aCentDedEki.setJikokuhyouHatsuJikokuDisplayNobori(iResult);
		}
		else
		{
			aCentDedEki.setJikokuhyouHatsuJikokuDisplayNobori(1);
		}
	}

	//22.JikokuhyouSyubetsuChangeDisplayKudari
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(
			nameJikokuhyouSyubetsuChangeDisplayKudari);
		vector<tstring> contValue = splitc<vector<tstring>>(',', strValue);
		if (contValue.size() >= 1 && !contValue[0].empty())
		{
			int iResult;
			try
			{
				iResult = stoi(contValue[0]);

				if (iResult < 0 || iResult>2)
				{
					iResult = 0;
				}
			}
			catch (std::invalid_argument e)
			{
				iResult = 0;
			}
			catch (std::out_of_range e)
			{
				iResult = 0;
			}
			if (iResult == 2)
			{
				//全列車表示に対応する値が変わったので、調整する
				iResult = 3;
			}
			aCentDedEki.setJikokuhyouRessyabangouDisplayKudari(iResult);
		}
		else
		{
			aCentDedEki.setJikokuhyouRessyabangouDisplayKudari(0);
		}

		if (contValue.size() >= 2 && !contValue[1].empty())
		{
			int iResult;
			try
			{
				iResult = stoi(contValue[1]);

				if (iResult < 0 || iResult>2)
				{
					iResult = 0;
				}
			}
			catch (std::invalid_argument e)
			{
				iResult = 0;
			}
			catch (std::out_of_range e)
			{
				iResult = 0;
			}
			if (iResult == 2)
			{
				//全列車表示に対応する値が変わったので、調整する
				iResult = 4;
			}
			else if (iResult == 1)
			{
				//種別変更のみ表示に対応する値が変わったので、調整する
				iResult = 2;
			}
			aCentDedEki.setJikokuhyouOperationNumberDisplayKudari(iResult);
		}
		else
		{
			aCentDedEki.setJikokuhyouOperationNumberDisplayKudari(0);
		}

		if (contValue.size() >= 3 && !contValue[2].empty())
		{
			int iResult;
			try
			{
				iResult = stoi(contValue[2]);

				if (iResult < 0 || iResult>2)
				{
					iResult = 0;
				}
			}
			catch (std::invalid_argument e)
			{
				iResult = 0;
			}
			catch (std::out_of_range e)
			{
				iResult = 0;
			}
			if (iResult == 2)
			{
				//全列車表示に対応する値が変わったので、調整する
				iResult = 3;
			}
			aCentDedEki.setJikokuhyouRessyaSyubetsuDisplayKudari(iResult);
		}
		else
		{
			aCentDedEki.setJikokuhyouRessyaSyubetsuDisplayKudari(0);
		}

		if (contValue.size() >= 4 && !contValue[3].empty())
		{
			int iResult;
			try
			{
				iResult = stoi(contValue[3]);

				if (iResult < 0 || iResult>2)
				{
					iResult = 0;
				}
			}
			catch (std::invalid_argument e)
			{
				iResult = 0;
			}
			catch (std::out_of_range e)
			{
				iResult = 0;
			}
			if (iResult == 2)
			{
				//全列車表示に対応する値が変わったので、調整する
				iResult = 3;
			}
			aCentDedEki.setJikokuhyouRessyameiDisplayKudari(iResult);
		}
		else
		{
			aCentDedEki.setJikokuhyouRessyameiDisplayKudari(0);
		}
	}

	//22.JikokuhyouSyubetsuChangeDisplayNobori
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(
			nameJikokuhyouSyubetsuChangeDisplayNobori);
		vector<tstring> contValue = splitc<vector<tstring>>(',', strValue);
		if (contValue.size() >= 1 && !contValue[0].empty())
		{
			int iResult;
			try
			{
				iResult = stoi(contValue[0]);

				if (iResult < 0 || iResult>2)
				{
					iResult = 0;
				}
			}
			catch (std::invalid_argument e)
			{
				iResult = 0;
			}
			catch (std::out_of_range e)
			{
				iResult = 0;
			}
			if (iResult == 2)
			{
				//全列車表示に対応する値が変わったので、調整する
				iResult = 3;
			}
			aCentDedEki.setJikokuhyouRessyabangouDisplayNobori(iResult);
		}
		else
		{
			aCentDedEki.setJikokuhyouRessyabangouDisplayNobori(0);
		}

		if (contValue.size() >= 2 && !contValue[1].empty())
		{
			int iResult;
			try
			{
				iResult = stoi(contValue[1]);

				if (iResult < 0 || iResult>2)
				{
					iResult = 0;
				}
			}
			catch (std::invalid_argument e)
			{
				iResult = 0;
			}
			catch (std::out_of_range e)
			{
				iResult = 0;
			}
			if (iResult == 2)
			{
				//全列車表示に対応する値が変わったので、調整する
				iResult = 4;
			}
			else if (iResult == 1)
			{
				//種別変更のみ表示に対応する値が変わったので、調整する
				iResult = 2;
			}
			aCentDedEki.setJikokuhyouOperationNumberDisplayNobori(iResult);
		}
		else
		{
			aCentDedEki.setJikokuhyouOperationNumberDisplayNobori(0);
		}

		if (contValue.size() >= 3 && !contValue[2].empty())
		{
			int iResult;
			try
			{
				iResult = stoi(contValue[2]);

				if (iResult < 0 || iResult>2)
				{
					iResult = 0;
				}
			}
			catch (std::invalid_argument e)
			{
				iResult = 0;
			}
			catch (std::out_of_range e)
			{
				iResult = 0;
			}
			if (iResult == 2)
			{
				//全列車表示に対応する値が変わったので、調整する
				iResult = 3;
			}
			aCentDedEki.setJikokuhyouRessyaSyubetsuDisplayNobori(iResult);
		}
		else
		{
			aCentDedEki.setJikokuhyouRessyaSyubetsuDisplayNobori(0);
		}

		if (contValue.size() >= 4 && !contValue[3].empty())
		{
			int iResult;
			try
			{
				iResult = stoi(contValue[3]);

				if (iResult < 0 || iResult>2)
				{
					iResult = 0;
				}
			}
			catch (std::invalid_argument e)
			{
				iResult = 0;
			}
			catch (std::out_of_range e)
			{
				iResult = 0;
			}
			if (iResult == 2)
			{
				//全列車表示に対応する値が変わったので、調整する
				iResult = 3;
			}
			aCentDedEki.setJikokuhyouRessyameiDisplayNobori(iResult);
		}
		else
		{
			aCentDedEki.setJikokuhyouRessyameiDisplayNobori(0);
		}
	}
	//24.DiagramColorNextEki 
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(
			nameDiagramColorNextEki);
		int iValue;
		if (strValue.empty())
		{
			iValue = 0;
		}
		else
		{
			iValue = intOf(strValue);
		}
		aCentDedEki.setDiagramColorNextEki(iValue);
	}
	//13.OperationTableDisplayJikoku
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(nameOperationTableDisplayJikoku);
		aCentDedEki.setOperationTableDisplayJikoku(strValue == _T("1"));
	}
	// --------------------------------

	CentDedEkiTrack2Cont	aCentDedEkiTrack2Cont;
	if (iRv >= 0)
	{
		Ou<const CDirectory> pCDirectory = dynamic_castOu<const CDirectory>(
			pCNodeContainer->getInName(nameEkiTrack2Cont, 0));
			//pCNodeContainer->getInName(nameEkiTrack2, 0));
		if (pCDirectory != NULL)
		{
			int iResult = CentDedEkiTrack2Cont_From_OuPropertiesText(
				&aCentDedEkiTrack2Cont,
				pCDirectory->getIfNodeContainerConst(),
				pCOuErrorInfoContainer);
			//iResult = 現在、この値が負の数になることはありません
			if (iResult < 0)
			{
				iRv = iResult;
			}
			//else
			//{
			//	//CaMui<CentDedEkiTrack2>	aCaCont(aCentDedEki.getEkiTrack2Cont());
			//	//CaMui<CentDedEkiTrack2>	aCaCont(pCentDedEki->getEkiTrack2Cont());
			//	//aCaCont.insert(&aCentDedEkiTrack2Cont);
			//	//*pCentDedEki->getEkiTrack2Cont() = aCentDedEkiTrack2Cont;
			//	//pCentDedRessyaCont->insert(aCentDedRessya);
			//}
		}
	}

	if ( iRv >= 0 ){
		*pCentDedEki = aCentDedEki ;
		/**
			テキストのペースト対応への処置
			コピー元内に番線要素がない場合、デフォルトの1番線・2番線をそのまま適用する
			その際、下り主本線は1番(index0)に、上り主本線は2番にする。
		*/
		if (aCentDedEkiTrack2Cont.size() > 0)
		{
			*pCentDedEki->getEkiTrack2Cont() = aCentDedEkiTrack2Cont;
		}
		else
		{
			pCentDedEki->setDownMain(0);
			pCentDedEki->setUpMain(1);
		}
	}
	return ( iRv ) ;
}

	// ********************************
	//	CentDedEkiCont
	// ********************************
const TCHAR nameEki[] = _T("Eki") ;
	
int CconvCentDedS09::CentDedEkiCont_From_OuPropertiesText( 
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
	return iRv ;
}


// ********************************
//	CentDedRessyasyubetsu
// ********************************

const TCHAR nameSyubetsumei[]=_T("Syubetsumei") ;
const TCHAR nameRyakusyou[]=_T("Ryakusyou") ;
const TCHAR nameJikokuhyouMojiColor[]=_T("JikokuhyouMojiColor") ;
const TCHAR nameJikokuhyouFontIndex[] = _T("JikokuhyouFontIndex") ;
const TCHAR nameJikokuhyouBackColor[] = _T("JikokuhyouBackColor");
const TCHAR nameDiagramSenColor[]=_T("DiagramSenColor") ;
const TCHAR nameDiagramSenStyle[]=_T("DiagramSenStyle") ;
const TCHAR nameDiagramSenIsBold[]=_T("DiagramSenIsBold") ;
const TCHAR nameDiagramRessyaFont[] = _T("DiagramRessyaFont") ;
const TCHAR nameStopMarkDrawType[] = _T("StopMarkDrawType") ;
const TCHAR nameParentSyubetsuIndex[] = _T("ParentSyubetsuIndex");

const CEnumToString< CentDedRessyasyubetsu::ESenStyle >& 
CconvCentDedS09::getESenStyleToString()
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
CconvCentDedS09::getEStopMarkDrawTypeToString()
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

int CconvCentDedS09::CdDiagramLineStyle_From_OuPropertiesText( 
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

int CconvCentDedS09::CentDedRessyasyubetsu_From_OuPropertiesText( 
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
	//4.1.JikokuhyouBackColor
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(
			nameJikokuhyouBackColor);
		if (strValue != _T(""))
		{
			aCentDedRessyasyubetsu.setJikokuhyouBackColor(
				CdColorProp_from_string(strValue));
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

	//10.ParentSyubetsuIndex
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(
			nameParentSyubetsuIndex);
		int iValue;
		if (strValue == _T(""))
		{
			iValue = -1;
		}
		else
		{
			iValue = intOf(strValue);
		}
		aCentDedRessyasyubetsu.setParentSyubetsuIndex(iValue);
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
		
int CconvCentDedS09::CentDedRessyasyubetsuCont_From_OuPropertiesText( 
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

int CconvCentDedS09::CentDedEkiJikoku_From_string( 
	CentDedEkiJikoku* pCentDedEkiJikoku ,
	const int iEkiTrack2Count,
	const int iMainTrack,
	const tstring strValue ) 
{
	int iRv = 0 ;
	// --------------------------------
	tstring strEkijikoku = strValue ;
	tstring	strEkiatsukai ;
	tstring strChaku ;
	tstring strHatsu ;
	tstring strRessyaTrack;
	
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
			pos = strEkijikoku.find('$');
			if (pos != tstring::npos)
			{
				strHatsu = strEkijikoku.substr(0, pos);
				strEkijikoku.erase(0, pos + 1);
				strRessyaTrack = strEkijikoku;
			}
			else
			{
				strHatsu = strEkijikoku;
			}
		}
		else
		{
			pos = strEkijikoku.find('$');
			if (pos != tstring::npos)
			{
				strHatsu = strEkijikoku.substr(0, pos);
				strEkijikoku.erase(0, pos + 1);
				strRessyaTrack = strEkijikoku;
			}
			else
			{
				strHatsu = strEkijikoku;
			}
		}
	}
	else
	{
		pos = strEkijikoku.find('$');
		if (pos != tstring::npos)
		{
			strEkiatsukai = strEkijikoku.substr(0, pos);
			strEkijikoku.erase(0, pos + 1);
			strRessyaTrack = strEkijikoku;
		}
		else
		{
			strEkiatsukai = strEkijikoku;
		}
	}
	//strEkiatsukai = 駅扱・空文字列は『運行なし』。"1"〜"3" ;
	//strChaku = 着時刻
	//strHatsu = 発時刻
	
	int iEkiatsukai = 0 ;
	if ( !strEkiatsukai.empty() )
	{
		iEkiatsukai = _ttoi( strEkiatsukai.c_str() ) ;
	}
	if ( !( 0 <= iEkiatsukai && iEkiatsukai < 3 ) )
	{
		iEkiatsukai = 0 ;
	}
	CdDedJikoku jikokuChaku( strChaku ) ;
	CdDedJikoku jikokuHatsu( strHatsu ) ;
	int iRessyaTrack = _ttoi(strRessyaTrack.c_str());
	if (iRessyaTrack < 0 || iRessyaTrack >= iEkiTrack2Count)
	{
		iRessyaTrack = iMainTrack;
	}
	CentDedEkiJikoku	aCentDedEkiJikoku( 
		(CentDedEkiJikoku::EEkiatsukai)iEkiatsukai , 
		jikokuChaku , jikokuHatsu , iRessyaTrack) ;

	// --------------------------------
	if ( pCentDedEkiJikoku != NULL )
	{
		*pCentDedEkiJikoku = aCentDedEkiJikoku ;
	}
	return iRv ;
}

const TCHAR nameOperation[] = _T("Operation");

int CconvCentDedS09::CentDedBeforeOperationCont_From_string(
	CentDedBeforeOperationCont * pCentDedBeforeOperationCont,
	const tstring strParentIndex,
	const int iEkiTrack2Count,
	const int iOuterTerminalCount,
	const OuPropertiesText::IfNodeContainerConst * pCNodeContainer)
{
	tstring strOperationJoin = pCNodeContainer->getValue(
		nameOperation + strParentIndex);
	if (!strOperationJoin.empty())
	{
		vector<tstring> strOperationCont =
			splitc< vector< tstring > >(',', strOperationJoin);
		for (int idx = 0; idx < (int)strOperationCont.size(); idx++)
		{
			tstring strOperation = strOperationCont[idx];
			tstring::size_type pos = 0;
			tstring strOperationType;
			tstring strOperationPara1;
			tstring strOperationPara2;
			tstring strOperationPara3;
			tstring strOperationPara4;

			pos = strOperation.find('/');
			if (pos != tstring::npos)
			{
				strOperationType = strOperation.substr(0, pos);
				strOperation.erase(0, pos + 1);
			}
			else
			{
				strOperationType = strOperation;
				strOperation.clear();
			}

			pos = strOperation.find('$');
			if (pos != tstring::npos)
			{
				strOperationPara1 = strOperation.substr(0, pos);
				strOperation.erase(0, pos + 1);
			}
			else
			{
				strOperationPara1 = strOperation;
				strOperation.clear();
			}

			pos = strOperation.find('/');
			if (pos != tstring::npos)
			{
				strOperationPara2 = strOperation.substr(0, pos);
				strOperation.erase(0, pos + 1);
			}
			else
			{
				strOperationPara2 = strOperation;
				strOperation.clear();
			}

			pos = strOperation.find('$');
			if (pos != tstring::npos)
			{
				strOperationPara3 = strOperation.substr(0, pos);
				strOperation.erase(0, pos + 1);
			}
			else
			{
				strOperationPara3 = strOperation;
				strOperation.clear();
			}

			strOperationPara4 = strOperation;

			CentDedBeforeOperation aBeforeOperation;
			if (strOperationType == _T("0"))
			{
				int iShuntTrackIndex = stoi(strOperationPara1);
				if (iShuntTrackIndex < 0 || iShuntTrackIndex >= iEkiTrack2Count)
				{
					iShuntTrackIndex = 0;
				}
				aBeforeOperation = 
					CentDedBeforeOperation(
						CentDedBeforeOperation::EBOperation::BOperation_Shunt,
						iShuntTrackIndex,
						CdDedJikoku(strOperationPara2),
						CdDedJikoku(strOperationPara3),
						strOperationPara4 == _T("1"));
			}
			else if (strOperationType == _T("1"))
			{
				aBeforeOperation =
					CentDedBeforeOperation(
						CentDedBeforeOperation::EBOperation::BOperation_Connect,
						strOperationPara1 == _T("1"),
						CdDedJikoku(strOperationPara2));

				tstring strChildIndex = strParentIndex + _T('.') + to_tstring(idx) + _T('B');
				CentDedBeforeOperationCont_From_string(
					aBeforeOperation.getCentDedBeforeOperationCont(),
					strChildIndex,
					iEkiTrack2Count,
					iOuterTerminalCount,
					pCNodeContainer);
			}
			else if (strOperationType == _T("2"))
			{
				aBeforeOperation =
					CentDedBeforeOperation(
						CentDedBeforeOperation::EBOperation::BOperation_Release,
						stoi(strOperationPara1),
						stoi(strOperationPara2),
						CdDedJikoku(strOperationPara3));

				tstring strChildIndex = strParentIndex + _T('.') + to_tstring(idx) + _T('A');
				CentDedAfterOperationCont_From_string(
					aBeforeOperation.getCentDedAfterOperationCont(),
					strChildIndex,
					iEkiTrack2Count,
					iOuterTerminalCount,
					false,
					pCNodeContainer);
			}
			else if (strOperationType == _T("3"))
			{
				vector<tstring> strOperationNumber =
					splitc<vector<tstring>>(';', strOperationPara2,true);
				aBeforeOperation =
					CentDedBeforeOperation(
						CentDedBeforeOperation::EBOperation::BOperation_Out,
						CdDedJikoku(strOperationPara1),
						strOperationNumber,
						tstring());
			}
			else if (strOperationType == _T("4"))
			{
				int iOuterTerminalIndex = stoi(strOperationPara1);
				if (iOuterTerminalIndex < 0 || iOuterTerminalIndex >= iOuterTerminalCount)
				{
					iOuterTerminalIndex = 0;
				}
				vector<tstring> strOperationNumber =
					splitc<vector<tstring>>(';', strOperationPara4,true);
				aBeforeOperation =
					CentDedBeforeOperation(
						CentDedBeforeOperation::EBOperation::BOperation_Outer,
						iOuterTerminalIndex,
						CdDedJikoku(strOperationPara2),
						CdDedJikoku(strOperationPara3),
						strOperationNumber,
						tstring());
			}
			else if (strOperationType == _T("5"))
			{
				//Ver2.00.05 解結表示省略および仮運用番号要素を追加
				//Ver2.05 解結表示省略の削除に対応
				vector<tstring> strOperationNumber =
					splitc<vector<tstring>>(';', strOperationPara3, true);
				aBeforeOperation =
					CentDedBeforeOperation(
						CentDedBeforeOperation::EBOperation::BOperation_Junction,
						CdDedJikoku(strOperationPara1),
						strOperationNumber);
			}
			else if (strOperationType == _T("6"))
			{
				//Ver2.00.05 運用番号変更作業を追加
				vector<tstring> strOperationNumber =
					splitc<vector<tstring>>(';', strOperationPara1, true);
				aBeforeOperation =
					CentDedBeforeOperation(
						CentDedBeforeOperation::EBOperation::BOperation_NumberChange,
						strOperationNumber,
						false);
			}

			if (idx < pCentDedBeforeOperationCont->size())
			{
				pCentDedBeforeOperationCont->set(aBeforeOperation, idx);
			}
			else
			{
				pCentDedBeforeOperationCont->insert(aBeforeOperation);
			}

		}
	}

	return 0;
}

int CconvCentDedS09::CentDedAfterOperationCont_From_string(
	CentDedAfterOperationCont * pCentDedAfterOperationCont,
	const tstring strParentIndex,
	const int iEkiTrack2Count,
	const int iOuterTerminalCount,
	const bool bSyubetsuChange,
	const OuPropertiesText::IfNodeContainerConst * pCNodeContainer)
{
	tstring strOperationJoin = pCNodeContainer->getValue(
		nameOperation + strParentIndex);
	if (!strOperationJoin.empty())
	{
		vector<tstring> strOperationCont =
			splitc< vector< tstring > >(',', strOperationJoin);
		for (int idx = 0; idx < (int)strOperationCont.size(); idx++)
		{
			tstring strOperation = strOperationCont[idx];
			tstring::size_type pos = 0;
			tstring strOperationType;
			tstring strOperationPara1;
			tstring strOperationPara2;
			tstring strOperationPara3;
			tstring strOperationPara4;

			pos = strOperation.find('/');
			if (pos != tstring::npos)
			{
				strOperationType = strOperation.substr(0, pos);
				strOperation.erase(0, pos + 1);
			}
			else
			{
				strOperationType = strOperation;
				strOperation.clear();
			}

			pos = strOperation.find('$');
			if (pos != tstring::npos)
			{
				strOperationPara1 = strOperation.substr(0, pos);
				strOperation.erase(0, pos + 1);
			}
			else
			{
				strOperationPara1 = strOperation;
				strOperation.clear();
			}

			pos = strOperation.find('/');
			if (pos != tstring::npos)
			{
				strOperationPara2 = strOperation.substr(0, pos);
				strOperation.erase(0, pos + 1);
			}
			else
			{
				strOperationPara2 = strOperation;
				strOperation.clear();
			}

			pos = strOperation.find('$');
			if (pos != tstring::npos)
			{
				strOperationPara3 = strOperation.substr(0, pos);
				strOperation.erase(0, pos + 1);
			}
			else
			{
				strOperationPara3 = strOperation;
				strOperation.clear();
			}

			strOperationPara4 = strOperation;

			CentDedAfterOperation aAfterOperation;
			if (strOperationType == _T("0"))
			{
				int iShuntTrackIndex = stoi(strOperationPara1);
				if (iShuntTrackIndex < 0 || iShuntTrackIndex >= iEkiTrack2Count)
				{
					iShuntTrackIndex = 0;
				}
				aAfterOperation =
					CentDedAfterOperation(
						CentDedAfterOperation::EAOperation::AOperation_Shunt,
						iShuntTrackIndex,
						CdDedJikoku(strOperationPara2),
						CdDedJikoku(strOperationPara3),
						strOperationPara4 == _T("1"));
			}
			else if (strOperationType == _T("1"))
			{
				aAfterOperation =
					CentDedAfterOperation(
						CentDedAfterOperation::EAOperation::AOperation_Connect,
						strOperationPara1 == _T("1"),
						CdDedJikoku(strOperationPara2));

				tstring strChildIndex = strParentIndex + _T('.') + to_tstring(idx) + _T('B');
				CentDedBeforeOperationCont_From_string(
					aAfterOperation.getCentDedBeforeOperationCont(),
					strChildIndex,
					iEkiTrack2Count,
					iOuterTerminalCount,
					pCNodeContainer);
			}
			else if (strOperationType == _T("2"))
			{
				aAfterOperation =
					CentDedAfterOperation(
						CentDedAfterOperation::EAOperation::AOperation_Release,
						stoi(strOperationPara1),
						stoi(strOperationPara2),
						CdDedJikoku(strOperationPara3));

				tstring strChildIndex = strParentIndex + _T('.') + to_tstring(idx) + _T('A');
				CentDedAfterOperationCont_From_string(
					aAfterOperation.getCentDedAfterOperationCont(),
					strChildIndex,
					iEkiTrack2Count,
					iOuterTerminalCount,
					false,
					pCNodeContainer);
			}
			else if (strOperationType == _T("3"))
			{
				aAfterOperation =
					CentDedAfterOperation(
						CentDedAfterOperation::EAOperation::AOperation_In,
						CdDedJikoku(strOperationPara1),
						tstring());
			}
			else if (strOperationType == _T("4"))
			{
				int iOuterTerminalIndex = stoi(strOperationPara1);
				if (iOuterTerminalIndex < 0 || iOuterTerminalIndex >= iOuterTerminalCount)
				{
					iOuterTerminalIndex = 0;
				}
				aAfterOperation =
					CentDedAfterOperation(
						CentDedAfterOperation::EAOperation::AOperation_Outer,
						iOuterTerminalIndex,
						CdDedJikoku(strOperationPara2),
						CdDedJikoku(strOperationPara3),
						tstring());
			}
			else if (strOperationType == _T("5"))
			{
				//Ver2.00.05 増結表示省略設定を追加
				//Ver2.05 増結表示省略＆種別変更設定→次列車接続タイプ変更に伴う移行処理追加
				int iNextJunctionType = 0;
				if (bSyubetsuChange)
				{
					iNextJunctionType = 1;
				}
				aAfterOperation =
					CentDedAfterOperation(
						CentDedAfterOperation::EAOperation::AOperation_Junction,
						CdDedJikoku(strOperationPara1),
						iNextJunctionType);
			}
			else if (strOperationType == _T("6"))
			{
				//Ver2.00.05 運用番号変更作業を追加
				vector<tstring> strOperationNumber =
					splitc<vector<tstring>>(';', strOperationPara1, true);
				aAfterOperation =
					CentDedAfterOperation(
						CentDedAfterOperation::EAOperation::AOperation_NumberChange,
						strOperationNumber,
						false);
			}

			if (idx < pCentDedAfterOperationCont->size())
			{
				pCentDedAfterOperationCont->set(aAfterOperation, idx);
			}
			else
			{
				pCentDedAfterOperationCont->insert(aAfterOperation);
			}

		}
	}

	return 0;
}

// ********************************
//	CentDedRessya
// ********************************

const CEnumToString<ERessyahoukou>& CconvCentDedS09::getERessyahoukouToString()
{
	static CEnumToString<ERessyahoukou> aEnumToString ;
	if ( aEnumToString.size() == 0 )
	{
		aEnumToString.add( Ressyahoukou_Kudari , _T("Kudari") ) ;
		aEnumToString.add( Ressyahoukou_Nobori , _T("Nobori") ) ;
	}
	return aEnumToString ;
};
const TCHAR nameRessyahoukou[]=_T("Houkou") ;
const TCHAR nameRessyasyubetsuIndex[]=_T("Syubetsu") ;
const TCHAR nameEkiJikoku3[]=_T("EkiJikoku") ;
const TCHAR nameRessyabangou[]=_T("Ressyabangou") ;
const TCHAR nameRessyamei[]=_T("Ressyamei") ;
const TCHAR nameGousuu[]=_T("Gousuu") ;
const TCHAR nameBikou[]=_T("Bikou") ;
const TCHAR nameRessyaTrack[] = _T("RessyaTrack");
const TCHAR nameOperationNumber[] = _T("OperationNumber");
const TCHAR nameSyubetsuChange[] = _T("SyubetsuChange");

int CconvCentDedS09::CentDedRessya_From_OuPropertiesText( 
	CentDedRessya* pCentDedRessya ,
	vector<int>& iEkiTrack2CountCont,
	vector<int>& iMainTrackCont,
	vector<int>& iOuterTerminalCountCont,
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
		//10.SyubetsuChange
		bool bSyubetsuChange = false;
		if (iRv >= 0)
		{
			tstring	strValue = pCNodeContainer->getValue(nameSyubetsuChange);
			bSyubetsuChange = strValue == _T("1");
		}
		//3.EkiJikoku3,BeforeOperationCont,AfterOperationCont
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
					iEkiOrder < (int)contstrEkijikoku.size() &&
					iEkiOrder < (int)iEkiTrack2CountCont.size();
					iEkiOrder ++ )
				{
					tstring strEkijikoku = contstrEkijikoku[iEkiOrder] ;
					CentDedEkiJikoku	aCentDedEkiJikoku ;
					int iResult = CentDedEkiJikoku_From_string( 
						&aCentDedEkiJikoku ,
						iEkiTrack2CountCont[iEkiOrder],
						iMainTrackCont[iEkiOrder],
						strEkijikoku ) ;
					assert( iResult >= 0 ) ;

					tstring strParentIndex = to_tstring(iEkiOrder) + _T('B');
					iResult = CentDedBeforeOperationCont_From_string(
						aCentDedEkiJikoku.getCentDedBeforeOperationCont(),
						strParentIndex,
						iEkiTrack2CountCont[iEkiOrder],
						iOuterTerminalCountCont[iEkiOrder],
						pCNodeContainer);
					if ( iEkiOrder < pCentDedRessya->getCentDedEkiJikokuCont()->size() )
					{
						pCentDedRessya->setCentDedEkiJikoku( iEkiOrder , 
							aCentDedEkiJikoku ) ;
					}
					else
					{
						pCentDedRessya->getCentDedEkiJikokuCont()->insert( aCentDedEkiJikoku ) ;
					}
					
					strParentIndex = to_tstring(iEkiOrder) + _T('A');
					iResult = CentDedAfterOperationCont_From_string(
						aCentDedEkiJikoku.getCentDedAfterOperationCont(),
						strParentIndex,
						iEkiTrack2CountCont[iEkiOrder],
						iOuterTerminalCountCont[iEkiOrder],
						bSyubetsuChange,
						pCNodeContainer);
					if (iEkiOrder < pCentDedRessya->getCentDedEkiJikokuCont()->size())
					{
						pCentDedRessya->setCentDedEkiJikoku(iEkiOrder,
							aCentDedEkiJikoku);
					}
					else
					{
						pCentDedRessya->getCentDedEkiJikokuCont()->insert(aCentDedEkiJikoku);
					}
				}
				//pCentDedRessya->adjustOperation();
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
const TCHAR nameRessya[]=_T("Ressya") ;

int CconvCentDedS09::CentDedRessyaCont_From_OuPropertiesText( 
	CentDedRessyaCont* pCentDedRessyaCont ,
	vector<int>& iEkiTrack2CountCont,
	vector<int>& iMainTrackCont,
	vector<int>& iOuterTerminalCountCont,
	const OuPropertiesText::IfNodeContainerConst* pCNodeContainer ,
	OuPropertiesText::ErrorInfo::COuErrorInfoContainer* pCOuErrorInfoContainer ) 
{
	int iRv = 0 ;

	int iRessyaCount = 0 ;

	if ( iRv >= 0 )
	{
		int idxRessya ;
		int iRessyaSize = pCNodeContainer->sizeInName(nameRessya);
#pragma omp parallel for ordered schedule(dynamic) 
		for ( idxRessya = 0 ; /*iRv >= 0 && */
			idxRessya < iRessyaSize;
				idxRessya ++ )
		{
			Ou<const CDirectory> pCDirectory = dynamic_castOu<const CDirectory>( 
				pCNodeContainer->getInName( nameRessya , idxRessya ) ) ;
			if ( pCDirectory != NULL )
			{
				CentDedRessya	aCentDedRessya( pCentDedRessyaCont->createNullRessya() );
				int iResult = CentDedRessya_From_OuPropertiesText( 
					&aCentDedRessya , 
					iEkiTrack2CountCont,
					iMainTrackCont,
					iOuterTerminalCountCont,
					pCDirectory->getIfNodeContainerConst() , 
					pCOuErrorInfoContainer ) ;
				//iResult = 現在、この値が負の数になることはありません
				if (iResult < 0)
				{
					iRv = iResult;
					break;
				}
				else
				{
#pragma omp ordered 
					pCentDedRessyaCont->insert(aCentDedRessya);
				}
			}
		}
	}
	return ( iRv ) ;
}



// ********************************
//	CentDedDia
// ********************************
const TCHAR nameDiaName[]=_T("DiaName") ;
const TCHAR nameMainBackColorIndex[] = _T("MainBackColorIndex");
const TCHAR nameSubBackColorIndex[] = _T("SubBackColorIndex");
const TCHAR nameBackPatternIndex[] = _T("BackPatternIndex");

int CconvCentDedS09::CentDedDia_From_OuPropertiesText( 
			CentDedDia* pCentDedDia ,
			const CentDedEkiCont* pCentDedEkiCont,
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
	//2.MainBackColorIndex
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(nameMainBackColorIndex);
		if (strValue.length() != 0)
		{
			pCentDedDia->setMainBackColorIndex(intOf(strValue));
		}
	}
	//2.1.SubBackColorIndex
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(nameSubBackColorIndex);
		if (strValue.length() != 0)
		{
			pCentDedDia->setSubBackColorIndex(intOf(strValue));
		}
	}
	//2.2.BackPatternIndex
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(nameBackPatternIndex);
		if (strValue.length() != 0)
		{
			pCentDedDia->setBackPatternIndex(intOf(strValue));
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
			const Mu<CentDedEkiCont::CdDedEki>* pCdDedEkiCont = pCentDedEkiCont->getMuPtr(eRessyahoukou);
			vector<int> iEkiTrack2CountCont;
			vector<int> iMainTrackCont;
			vector<int> iOuterTerminalCountCont;
			for (int idxEki = 0; idxEki < pCdDedEkiCont->size(); idxEki++)
			{
				const CentDedEkiCont::CdDedEki aCdDedEki = pCdDedEkiCont->get(idxEki);
				iEkiTrack2CountCont.push_back(aCdDedEki.getCentDedEkiTrack2Cont().size());
				iMainTrackCont.push_back(aCdDedEki.getMainTrack());
				iOuterTerminalCountCont.push_back(aCdDedEki.getOuterTerminalEkimeiCount());
			}

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
					iEkiTrack2CountCont,
					iMainTrackCont,
					iOuterTerminalCountCont,
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
	
int CconvCentDedS09::CentDedDiaCont_From_OuPropertiesText( 
			CentDedDiaCont* pCentDedDiaCont ,
			const CentDedEkiCont* pCentDedEkiCont,
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
					pCentDedEkiCont,
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
const TCHAR nameKudariDiaAlias[] = _T("KudariDiaAlias");
const TCHAR nameNoboriDiaAlias[] = _T("NoboriDiaAlias");
const TCHAR nameKitenJikoku[] = _T("KitenJikoku") ;
const TCHAR nameDiagramDgrYZahyouKyoriDefault[] = _T("DiagramDgrYZahyouKyoriDefault") ;
const TCHAR nameEnableOperation[] = _T("EnableOperation");
const TCHAR nameOperationNumberReverse[] = _T("OperationNumberReverse");
const TCHAR nameComment[] = _T("Comment") ;

int CconvCentDedS09::CentDedRosen_From_OuPropertiesText( 
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
	//1.1.KudariDiaAlias
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(nameKudariDiaAlias);
		pCentDedRosen->setKudariDiaAlias(strValue);
	}
	//1.2.NoboriDiaAlias
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(nameNoboriDiaAlias);
		pCentDedRosen->setNoboriDiaAlias(strValue);
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
			aCentDedEkiCont.adjustBrunchLoopCont();
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
			pCentDedRosen->getCentDedEkiCont(),
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
	//6.1.EnableOperation
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(nameEnableOperation);
		if (strValue.length() == 0)
		{
			pCentDedRosen->setEnableOperation(0);
		}
		else
		{
			pCentDedRosen->setEnableOperation(intOf(strValue));
		}
		//if (strValue == _T("1"))
		//{
		//	pCentDedRosen->setEnableOperation(true);
		//}
		//else
		//{
		//	pCentDedRosen->setEnableOperation(false);
		//}
	}
	//6.2.OperationNumberReverse
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(nameOperationNumberReverse);
		pCentDedRosen->setOperationNumberReverse(strValue == _T("1"));
	}
	//7.Comment
	if ( iRv >= 0 ){
		tstring	strValue = pCNodeContainer->getValue( nameComment )  ;
		if ( iRv >= 0 )
		{
			pCentDedRosen->setComment( strValue ) ;
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

	return ( iRv ) ;
}

} //namespace entDed


