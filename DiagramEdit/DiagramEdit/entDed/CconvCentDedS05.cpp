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
//	CconvCentDedS05.cpp
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
#include "CconvCentDedS05.h"

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

int CconvCentDedS05::CentDedEkiTrack2_From_OuPropertiesText(
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

int CconvCentDedS05::CentDedEkiTrack2Cont_From_OuPropertiesText(
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
const TCHAR nameEkijikokukeisiki[] = _T("Ekijikokukeisiki") ;
const TCHAR nameEkikibo[] = _T("Ekikibo") ;
const TCHAR nameKyoukaisen[] = _T("Kyoukaisen") ;
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
const TCHAR nameNextEkiDistance[] = _T("NextEkiDistance");
const TCHAR nameJikokuhyouTrackOmit[] = _T("JikokuhyouTrackOmit");


const CEnumToString< CentDedEki::EEkijikokukeisiki >& 
CconvCentDedS05::getEEkijikokukeisikiToString()
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
CconvCentDedS05::getEEkikiboToString()
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
CconvCentDedS05::getEDiagramRessyajouhouHyoujiToString()
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

int CconvCentDedS05::CentDedEki_From_OuPropertiesText( 
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
				駅時刻形式をもとに、カスタム表示モード時の時刻表示を設定します
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

	/**
		Ver2.0で、番線Indexの仕様を変更したので、
		旧形式から読み込む場合は、-1する必要があります。
	*/
	//7.DownMain 
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(
			nameDownMain);
		int iValue = _ttoi(strValue.c_str());
		iValue--;
		aCentDedEki.setDownMain(iValue);
	}
	//8.UpMain 
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(
			nameUpMain);
		int iValue = _ttoi(strValue.c_str());
		iValue--;
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
			 iValue = _ttoi(strValue.c_str());
		}
		aCentDedEki.setBrunchCoreEkiIndex(iValue);
		if (iValue >= 0)
		{
			tstring	strValueO = pCNodeContainer->getValue(
				nameBrunchOpposite);
			aCentDedEki.setBrunchOpposite(_ttoi(strValueO.c_str()) == 1);
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
			iValue = _ttoi(strValue.c_str());
		}
		aCentDedEki.setLoopOriginEkiIndex(iValue);
		if (iValue >= 0)
		{
			tstring	strValueO = pCNodeContainer->getValue(
				nameLoopOpposite);
			aCentDedEki.setLoopOpposite(_ttoi(strValueO.c_str()) == 1);
		}
	}
	//11.JikokuhyouTrackDisplayKudari
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(nameJikokuhyouTrackDisplayKudari);
		aCentDedEki.setJikokuhyouTrackDisplayKudari(_ttoi(strValue.c_str()) == 1);
	}
	//12.JikokuhyouTrackDisplayNobori
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(nameJikokuhyouTrackDisplayNobori);
		aCentDedEki.setJikokuhyouTrackDisplayNobori(_ttoi(strValue.c_str()) == 1);
	}
	//13.DiagramTrackDisplay
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(nameDiagramTrackDisplay);
		aCentDedEki.setDiagramTrackDisplay(_ttoi(strValue.c_str()) == 1);
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
				tstring strValue = pCDirectory->getIfNodeContainerConst()->getValue(
					nameOuterTerminalEkimei);
				if (!strValue.empty())
				{
					OuterTerminal sOuterTerminal(strValue, _T(""), _T(""));
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
			iValue = _ttoi(strValue.c_str());
		}
		aCentDedEki.setNextEkiDistance(iValue);
	}

	//Ver2.00.05 旧ファイルを読み込んだ時、発時刻のみ駅の番線表示省略をONにする仕様に伴い、この処理を一時保留に
	//17.JikokuhyouTrackOmit
	//if (iRv >= 0)
	//{
	//	tstring	strValue = pCNodeContainer->getValue(nameJikokuhyouTrackOmit);
	//	aCentDedEki.setJikokuhyouTrackOmit(_ttoi(strValue.c_str()) == 1);
	//}


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
		*pCentDedEki->getEkiTrack2Cont() = aCentDedEkiTrack2Cont;
	}
	return ( iRv ) ;
}

	// ********************************
	//	CentDedEkiCont
	// ********************************
const TCHAR nameEki[] = _T("Eki") ;

int CconvCentDedS05::CentDedEkiCont_From_OuPropertiesText( 
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
	if (iRv >= 0)
	{
		pCentDedEkiCont->adjustBrunchLoopCont();
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
CconvCentDedS05::getESenStyleToString()
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
CconvCentDedS05::getEStopMarkDrawTypeToString()
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
int CconvCentDedS05::CdDiagramLineStyle_From_OuPropertiesText( 
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

int CconvCentDedS05::CentDedRessyasyubetsu_From_OuPropertiesText( 
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
			iValue = _ttoi(strValue.c_str());
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
	
int CconvCentDedS05::CentDedRessyasyubetsuCont_From_OuPropertiesText( 
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
int CconvCentDedS05::CentDedEkiJikoku_From_string( 
			CentDedEkiJikoku* pCentDedEkiJikoku , 
			const tstring strValue,
			const tstring strValue2,
			const int iEkiTrack2Size,
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

	tstring strRessyaTrack = strValue2;
	tstring strRessyaTrackIndex;
	pos = 0;
	pos = strRessyaTrack.find(';');
	if (pos != tstring::npos)
	{
		strRessyaTrackIndex = strRessyaTrack.substr(0, pos);
	}
	else
	{
		strRessyaTrackIndex = strRessyaTrack;
	}
	int iRessyaTrackIndex = iMainTrack;
	if (!strRessyaTrackIndex.empty())
	{
		iRessyaTrackIndex = _ttoi(strRessyaTrackIndex.c_str());
		if (!(1 <= iRessyaTrackIndex && iRessyaTrackIndex <= iEkiTrack2Size))
		{
			//iRessyaTrackIndex==0(主本線)の場合も含む。
			iRessyaTrackIndex = iMainTrack;
		}
		else
		{
			//Ver2.0以前は、0が主本線,1～sizeが個別指定なので、-1する。
			iRessyaTrackIndex--;
		}
	}

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
		jikokuChaku , jikokuHatsu , iRessyaTrackIndex) ;

	// --------------------------------
	if ( pCentDedEkiJikoku != NULL )
	{
		*pCentDedEkiJikoku = aCentDedEkiJikoku ;
	}
	return iRv ;
}

// ********************************
//	CentDedRessyaTrack
// ********************************

int CconvCentDedS05::BeforeOperation_From_string(
	CentDedEkiJikoku* pEkiJikoku,
	const int iEkiTrack2Size,
	const tstring strValue)
{
	int iRv = 0;
	pEkiJikoku->getCentDedBeforeOperationCont()->erase(0, INT_MAX);

	if (!pEkiJikoku->getChakujikoku().isNull() &&
		pEkiJikoku->getHatsujikoku().isNull())
	{
		pEkiJikoku->setHatsujikoku(pEkiJikoku->getChakujikoku());
	}
	else if (pEkiJikoku->getChakujikoku().isNull() &&
		pEkiJikoku->getHatsujikoku().isNull())
	{
		return iRv;
	}
	// --------------------------------
	tstring strRessyaTrack = strValue;
	tstring strOperation;
	tstring strOperationPara1;
	tstring strOperationPara2;
	tstring strOperationPara3;

	tstring::size_type pos = 0;
	pos = strRessyaTrack.find(';');
	if (pos != tstring::npos)
	{
		strRessyaTrack.erase(0, pos + 1);

		pos = strRessyaTrack.find('/');
		if (pos != tstring::npos)
		{
			strOperation = strRessyaTrack.substr(0, pos);
			strRessyaTrack.erase(0, pos + 1);
			pos = strRessyaTrack.find('$');
			if (pos != tstring::npos)
			{
				strOperationPara1 = strRessyaTrack.substr(0, pos);
				strRessyaTrack.erase(0, pos + 1);
				pos = strRessyaTrack.find('/');
				if (pos != tstring::npos)
				{
					strOperationPara2 = strRessyaTrack.substr(0, pos);
					strRessyaTrack.erase(0, pos + 1);
					strOperationPara3 = strRessyaTrack;
				}
				else
				{
					strOperationPara2 = strRessyaTrack;
				}

			}
			else
			{
				strOperationPara1 = strRessyaTrack;
			}

		}
		else
		{
			strOperation = strRessyaTrack;
		}
	}

	//strRessyaTrackIndex = 列車番線Index、駅扱いが運行無しの場合空白
	//strOperation = 作業、0-2
	//strOperationPara1 = 作業による附則事項、0:無しの場合は無し、1:入換の場合は番線、
	//2:入出区の場合は、無しまたは出区の場合のみ運番
	//strOperationPara2 = 作業による附則事項、0:無しの場合は無し、1:入換の場合は発時刻もしくはなし、
	//2:入出区の場合は無し
	//strOperationPara3 = 作業による附則事項、0:無しの場合は無し、1:入換の場合は着時刻もしくはなし、
	//2:入出区の場合は無し

	int iOperation = 0;
	if (!strOperation.empty())
	{
		iOperation = _ttoi(strOperation.c_str());
	}
	if (!(0 <= iOperation && iOperation < 4))
	{
		iOperation = 0;
	}
	if ( iOperation == 1)
	{
		CentDedBeforeOperation aBeforeOperation =
			CentDedBeforeOperation(
				CentDedBeforeOperation::EBOperation::BOperation_Junction,
				CdDedJikoku(),
				vector<tstring>());

		pEkiJikoku->getCentDedBeforeOperationCont()->insert(aBeforeOperation);

		int iShuntTrackIndex = 0;
		CdDedJikoku OperationHatsuJikoku;
		CdDedJikoku OperationChakuJikoku;

		if (!strOperationPara1.empty())
		{
			iShuntTrackIndex = _ttoi(strOperationPara1.c_str());
		}
		if (!(1 <= iShuntTrackIndex && iShuntTrackIndex <= iEkiTrack2Size))
		{
			iShuntTrackIndex = 0;
		}
		else
		{
			//Ver2.0以前は、0が主本線,1～sizeが個別指定なので、-1する。
			iShuntTrackIndex--;
		}
		OperationHatsuJikoku.decode(strOperationPara2);
		OperationChakuJikoku.decode(strOperationPara3);

		if (OperationHatsuJikoku.isNull())
		{
			if (!OperationChakuJikoku.isNull())
			{
				OperationHatsuJikoku = OperationChakuJikoku;
			}
			else if (!pEkiJikoku->getHatsujikoku(false).isNull())
			{
				OperationHatsuJikoku = pEkiJikoku->getHatsujikoku(false);
				OperationHatsuJikoku.addSeconds(-60);
			}
		}
		if (!OperationHatsuJikoku.isNull() &&
			!pEkiJikoku->getHatsujikoku(false).isNull())
		{
			CentDedBeforeOperation aBeforeOperationShunt =
				CentDedBeforeOperation(
					CentDedBeforeOperation::EBOperation::BOperation_Shunt,
					iShuntTrackIndex,
					OperationHatsuJikoku,
					OperationChakuJikoku,
					false);

			pEkiJikoku->getCentDedBeforeOperationCont()->insert(aBeforeOperationShunt);
		}

	}
	else if (iOperation == 2)
	{
		vector<tstring> strOperationNumber;
		if (!strOperationPara1.empty())
		{
			strOperationNumber.push_back(strOperationPara1);
		}

		CdDedJikoku OutJikoku = pEkiJikoku->getHatsujikoku(false);
		if (!OutJikoku.isNull())
		{
			OutJikoku.addSeconds(-60);

			CentDedBeforeOperation aBeforeOperation =
				CentDedBeforeOperation(
					CentDedBeforeOperation::EBOperation::BOperation_Out,
					OutJikoku,
					strOperationNumber,
					tstring());

			pEkiJikoku->getCentDedBeforeOperationCont()->insert(aBeforeOperation);
		}

	}
	else if (iOperation == 3)
	{
		int iOuterHatsuIndex = _ttoi(strOperationPara1.c_str());

		vector<tstring> strOperationNumber;
		if (!strOperationPara3.empty())
		{
			strOperationNumber.push_back(strOperationPara3);
		}
		CdDedJikoku ChakuJikoku = pEkiJikoku->getChakujikoku(true);
		CdDedJikoku OuterShihatsuJikoku(strOperationPara2);
		if (!ChakuJikoku.isNull() && !OuterShihatsuJikoku.isNull())
		{

			CentDedBeforeOperation aBeforeOperation =
				CentDedBeforeOperation(
					CentDedBeforeOperation::EBOperation::BOperation_Outer,
					iOuterHatsuIndex,
					OuterShihatsuJikoku,
					ChakuJikoku,
					strOperationNumber,
					tstring());

			pEkiJikoku->getCentDedBeforeOperationCont()->insert(aBeforeOperation);
		}
	}
	else
	{
		CentDedBeforeOperation aBeforeOperation =
			CentDedBeforeOperation(
				CentDedBeforeOperation::EBOperation::BOperation_Junction,
				CdDedJikoku(),
				vector<tstring>());

		pEkiJikoku->getCentDedBeforeOperationCont()->insert(aBeforeOperation);
	}

	return iRv;
}

int CconvCentDedS05::AfterOperation_From_string(
	CentDedEkiJikoku* pEkiJikoku,
	const int iEkiTrack2Size,
	const tstring strValue)
{
	int iRv = 0;
	pEkiJikoku->getCentDedAfterOperationCont()->erase(0, INT_MAX);

	if (pEkiJikoku->getChakujikoku().isNull() &&
		!pEkiJikoku->getHatsujikoku().isNull())
	{
		pEkiJikoku->setChakujikoku(pEkiJikoku->getHatsujikoku());
	}
	else if (pEkiJikoku->getChakujikoku().isNull() &&
		pEkiJikoku->getHatsujikoku().isNull())
	{
		return iRv;
	}


	// --------------------------------
	tstring strRessyaTrack = strValue;
	tstring strOperation;
	tstring strOperationPara1;
	tstring strOperationPara2;
	tstring strOperationPara3;

	tstring::size_type pos = 0;
	pos = strRessyaTrack.find(';');
	if (pos != tstring::npos)
	{
		strRessyaTrack.erase(0, pos + 1);

		pos = strRessyaTrack.find('/');
		if (pos != tstring::npos)
		{
			strOperation = strRessyaTrack.substr(0, pos);
			strRessyaTrack.erase(0, pos + 1);
			pos = strRessyaTrack.find('$');
			if (pos != tstring::npos)
			{
				strOperationPara1 = strRessyaTrack.substr(0, pos);
				strRessyaTrack.erase(0, pos + 1);
				pos = strRessyaTrack.find('/');
				if (pos != tstring::npos)
				{
					strOperationPara2 = strRessyaTrack.substr(0, pos);
					strRessyaTrack.erase(0, pos + 1);
					strOperationPara3 = strRessyaTrack;
				}
				else
				{
					strOperationPara2 = strRessyaTrack;
				}

			}
			else
			{
				strOperationPara1 = strRessyaTrack;
			}

		}
		else
		{
			strOperation = strRessyaTrack;
		}
	}

	//strRessyaTrackIndex = 列車番線Index、駅扱いが運行無しの場合空白
	//strOperation = 作業、0-2
	//strOperationPara1 = 作業による附則事項、0:無しの場合は無し、1:入換の場合は番線、
	//2:入出区の場合は、無しまたは出区の場合のみ運番
	//strOperationPara2 = 作業による附則事項、0:無しの場合は無し、1:入換の場合は発時刻もしくはなし、
	//2:入出区の場合は無し
	//strOperationPara3 = 作業による附則事項、0:無しの場合は無し、1:入換の場合は着時刻もしくはなし、
	//2:入出区の場合は無し

	int iOperation = 0;
	if (!strOperation.empty())
	{
		iOperation = _ttoi(strOperation.c_str());
	}
	if (!(0 <= iOperation && iOperation < 4))
	{
		iOperation = 0;
	}
	if (iOperation == 1)
	{

		int iShuntTrackIndex = 0;
		CdDedJikoku OperationHatsuJikoku;
		CdDedJikoku OperationChakuJikoku;

		if (!strOperationPara1.empty())
		{
			iShuntTrackIndex = _ttoi(strOperationPara1.c_str());
		}
		if (!(1 <= iShuntTrackIndex && iShuntTrackIndex <= iEkiTrack2Size))
		{
			iShuntTrackIndex = 0;
		}
		else
		{
			//Ver2.0以前は、0が主本線,1～sizeが個別指定なので、-1する。
			iShuntTrackIndex--;
		}
		OperationHatsuJikoku.decode(strOperationPara2);
		OperationChakuJikoku.decode(strOperationPara3);

		if (OperationHatsuJikoku.isNull())
		{
			if (!OperationChakuJikoku.isNull())
			{
				OperationHatsuJikoku = OperationChakuJikoku;
			}
			else if (!pEkiJikoku->getChakujikoku(false).isNull())
			{
				OperationHatsuJikoku = pEkiJikoku->getChakujikoku(false);
				OperationHatsuJikoku.addSeconds(60);
			}
		}
		if (!OperationHatsuJikoku.isNull() &&
			!pEkiJikoku->getChakujikoku(false).isNull())
		{
			CentDedAfterOperation aAfterOperation =
				CentDedAfterOperation(
					CentDedAfterOperation::EAOperation::AOperation_Shunt,
					iShuntTrackIndex,
					OperationHatsuJikoku,
					OperationChakuJikoku,
					false);

			pEkiJikoku->getCentDedAfterOperationCont()->insert(aAfterOperation);
		}

		CentDedAfterOperation aAfterOperationJunction =
			CentDedAfterOperation(
				CentDedAfterOperation::EAOperation::AOperation_Junction,
				CdDedJikoku(strOperationPara1),
				0);

		pEkiJikoku->getCentDedAfterOperationCont()->insert(aAfterOperationJunction);
	}
	else if (iOperation == 2)
	{
		CdDedJikoku InJikoku = pEkiJikoku->getChakujikoku(false);
		if (!InJikoku.isNull())
		{
			InJikoku.addSeconds(60);

			CentDedAfterOperation aAfterOperation =
				CentDedAfterOperation(
					CentDedAfterOperation::EAOperation::AOperation_In,
					InJikoku,
					tstring());

			pEkiJikoku->getCentDedAfterOperationCont()->insert(aAfterOperation);
		}

	}
	else if (iOperation == 3)
	{
		int iOuterChakuIndex = _ttoi(strOperationPara1.c_str());

		CdDedJikoku HatsuJikoku = pEkiJikoku->getHatsujikoku(true);
		CdDedJikoku OuterShuchakuJikoku(strOperationPara2);
		if (!HatsuJikoku.isNull() && !OuterShuchakuJikoku.isNull())
		{

			CentDedAfterOperation aAfterOperation =
				CentDedAfterOperation(
					CentDedAfterOperation::EAOperation::AOperation_Outer,
					iOuterChakuIndex, 
					HatsuJikoku,
					OuterShuchakuJikoku,
					tstring());

			pEkiJikoku->getCentDedAfterOperationCont()->insert(aAfterOperation);
		}
	}
	else
	{
		CentDedAfterOperation aAfterOperation =
			CentDedAfterOperation(
				CentDedAfterOperation::EAOperation::AOperation_Junction,
				CdDedJikoku(strOperationPara1),
				0);

		pEkiJikoku->getCentDedAfterOperationCont()->insert(aAfterOperation);
	}

	return iRv;
}

// ********************************
//	CentDedRessya
// ********************************

const CEnumToString<ERessyahoukou>& CconvCentDedS05::getERessyahoukouToString()
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

int CconvCentDedS05::CentDedRessya_From_OuPropertiesText( 
			CentDedRessya* pCentDedRessya ,
			deque<int>& iEkiTrack2SizeCont,
			deque<int>& iMainTrackCont,
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
		//3.EkiJikoku3
		if ( iRv >= 0 )
		{
			tstring strEkijikokus = pCNodeContainer->getValue( 
				nameEkiJikoku3 ) ;
			tstring strRessyaTracks = pCNodeContainer->getValue(
				nameRessyaTrack);
			if ( !strEkijikokus.empty() )
			{
				deque<tstring>	contstrEkijikoku = 
					splitc< deque< tstring > >( ',' , strEkijikokus ) ;
				deque<tstring>	contstrRessyaTrack =
					splitc< deque< tstring > >(',', strRessyaTracks);
					
				int iEkiOrder ;
				for ( iEkiOrder = 0 ; iRv >= 0 && 
					iEkiOrder < (int)contstrEkijikoku.size()  ;
					iEkiOrder ++ )
				{
					tstring strEkijikoku = contstrEkijikoku[iEkiOrder] ;
					tstring strRessyaTrack = contstrRessyaTrack[iEkiOrder];
					CentDedEkiJikoku	aCentDedEkiJikoku ;
					int iResult = CentDedEkiJikoku_From_string( 
						&aCentDedEkiJikoku , 
						strEkijikoku ,
						strRessyaTrack,
						iEkiTrack2SizeCont[iEkiOrder],
						iMainTrackCont[iEkiOrder]) ;
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
		//8.始発終着駅作業の適用
		if (iRv >= 0) 
		{
			tstring strRessyaTrack = pCNodeContainer->getValue(
				nameRessyaTrack);
			if (!strRessyaTrack.empty())
			{
				deque<tstring>	contstrRessyaTrack =
					splitc< deque< tstring > >(',', strRessyaTrack);

				tstring strRessyaTrack = contstrRessyaTrack[pCentDedRessya->getSihatsuEki()];
				CentDedEkiJikoku*	pCentDedEkiJikoku =
					pCentDedRessya->getCentDedEkiJikokuCont()->getMuPtr()
					->get(pCentDedRessya->getSihatsuEki());
				int iResult = BeforeOperation_From_string(
					pCentDedEkiJikoku,
					iEkiTrack2SizeCont[pCentDedRessya->getSihatsuEki()],
					strRessyaTrack);
				//assert(iResult >= 0);
			}
		}
		if (iRv >= 0)
		{
			tstring strRessyaTrack = pCNodeContainer->getValue(
				nameRessyaTrack);
			if (!strRessyaTrack.empty())
			{
				deque<tstring>	contstrRessyaTrack =
					splitc< deque< tstring > >(',', strRessyaTrack);

				tstring strRessyaTrack = contstrRessyaTrack[pCentDedRessya->getSyuuchakuEki()];
				CentDedEkiJikoku*	pCentDedEkiJikoku =
					pCentDedRessya->getCentDedEkiJikokuCont()->getMuPtr()
					->get(pCentDedRessya->getSyuuchakuEki());
				int iResult = AfterOperation_From_string(
					pCentDedEkiJikoku,
					iEkiTrack2SizeCont[pCentDedRessya->getSyuuchakuEki()],
					strRessyaTrack);
				//assert(iResult >= 0);
			}
		}
		//if (iRv >= 0)
		//{
		//	pCentDedRessya->adjustOperation();
		//}
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

int CconvCentDedS05::CentDedRessyaCont_From_OuPropertiesText( 
			CentDedRessyaCont* pCentDedRessyaCont ,
			deque<int>& iEkiTrack2SizeCont,
			deque<int>& iMainTrackCont,
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
					iEkiTrack2SizeCont,
					iMainTrackCont,
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

int CconvCentDedS05::CentDedDia_From_OuPropertiesText( 
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
			deque<int> iEkiTrack2SizeCont;
			deque<int> iMainTrackCont;
			for (int idxEki = 0; idxEki < pCdDedEkiCont->size(); idxEki++)
			{
				const CentDedEkiCont::CdDedEki aCdDedEki = pCdDedEkiCont->get(idxEki);
				iEkiTrack2SizeCont.push_back(aCdDedEki.getCentDedEkiTrack2Cont().size());
				iMainTrackCont.push_back(aCdDedEki.getMainTrack());
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
					iEkiTrack2SizeCont,
					iMainTrackCont,
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
		
int CconvCentDedS05::CentDedDiaCont_From_OuPropertiesText( 
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
const TCHAR nameComment[] = _T("Comment") ;

int CconvCentDedS05::CentDedRosen_From_OuPropertiesText( 
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

	if (iRv >= 0)
	{
		pCentDedRosen->adjustOperation();
	}

	//6.1.EnableOperation
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(nameEnableOperation);
		if (strValue.empty())
		{
			pCentDedRosen->setEnableOperation(0);
		}
		else
		{
			//pCentDedRosen->setEnableOperation(intOf(strValue));
			pCentDedRosen->setEnableOperation(2);
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
		pCentDedRosen->mergeOuterTerminal();
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


