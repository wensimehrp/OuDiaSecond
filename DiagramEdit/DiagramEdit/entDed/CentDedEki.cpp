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
/** @file */
//$Id: CentDedEki.cpp 378 2016-11-16 21:10:54Z okm $
#include "stdafx.h"
#include "CentDedEki.h"
#include "CentDedEkiCont.h"
#include "Str/tstring.h"

namespace entDed{


// ****************************************************************
//	CentDedEki::CXentDedEkiTrackCont
// ****************************************************************
	// ********************************
	//	コンストラクタ
	// ********************************


	// ********************************
	//@name CentDedEkiTrack2Cont-関連
	// ********************************

CentDedEki* CentDedEki::CXEkiTrack2Cont::getEki()
{
	CentDedEki* pOuter = (CentDedEki*)(((char*)this) - offsetof(CentDedEki, m_CentDedEkiTrack2Cont));
	return pOuter;
}

const CentDedEki* CentDedEki::CXEkiTrack2Cont::getEki()const
{
	const CentDedEki* pOuter = (const CentDedEki*)(((const char*)this) - offsetof(CentDedEki, m_CentDedEkiTrack2Cont));
	return pOuter;
}


// ****************************************************************
//	CentDedEki
// ****************************************************************
	// ********************************
	//	コンストラクタ
	// ********************************
CentDedEki::CentDedEki()
	:
	m_eEkijikokukeisiki(EEkijikokukeisiki::Jikokukeisiki_Hatsu),
	m_eEkikibo(EEkikibo::Ekikibo_Ippan),
	m_bKyoukaisen(false),
	m_eDiagramRessyajouhouHyoujiKudari(EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Origin),
	m_eDiagramRessyajouhouHyoujiNobori(EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Origin),
	m_iDownMain(0),
	m_iUpMain(1),
	m_iID(-1),
	m_iBrunchCoreEkiIndex(-1),
	m_bBrunchOpposite(false),
	m_iLoopOriginEkiIndex(-1),
	m_bLoopOpposite(false),
	m_bJikokuhyouTrackDisplayKudari(false),
	m_bJikokuhyouTrackDisplayNobori(false),
	m_bDiagramTrackDisplay(false),
	m_iNextEkiDistance(0),
	m_bJikokuhyouTrackOmit(false),
	m_iBrunchLoopPosition(-1),
	m_iJikokuhyouOperationOrigin(0),
	m_iJikokuhyouOperationTerminal(0),
	m_bJikokuhyouOperationOriginDownBeforeUpAfter(false),
	m_bJikokuhyouOperationOriginDownAfterUpBefore(false),
	m_bJikokuhyouOperationTerminalDownBeforeUpAfter(false),
	m_bJikokuhyouOperationTerminalDownAfterUpBefore(false),
	m_strEkimeiJikokuhyouRyaku(_T("")),
	m_strEkimeiDiagramRyaku(_T("")),
	m_bJikokuhyouChakuJikokuDisplayKudari(false),
	m_bJikokuhyouChakuJikokuDisplayNobori(false),
	m_bJikokuhyouHatsuJikokuDisplayKudari(true),
	m_bJikokuhyouHatsuJikokuDisplayNobori(true),
	m_iJikokuhyouRessyabangouDisplayKudari(0),
	m_iJikokuhyouRessyabangouDisplayNobori(0),
	m_iJikokuhyouOperationNumberDisplayKudari(0),
	m_iJikokuhyouOperationNumberDisplayNobori(0),
	m_iJikokuhyouOperationNumberDisplayRowsKudari(1),
	m_iJikokuhyouOperationNumberDisplayRowsNobori(1),
	m_iJikokuhyouRessyaSyubetsuDisplayKudari(0),
	m_iJikokuhyouRessyaSyubetsuDisplayNobori(0),
	m_iJikokuhyouRessyameiDisplayKudari(0),
	m_iJikokuhyouRessyameiDisplayNobori(0),
	m_bJikokuhyouOuterSihatsuDisplayKudari(false),
	m_bJikokuhyouOuterShuchakuDisplayKudari(false),
	m_bJikokuhyouOuterSihatsuDisplayNobori(false),
	m_bJikokuhyouOuterShuchakuDisplayNobori(false),
	m_iDiagramColorNextEki(0),
	m_bOperationTableDisplayJikoku(false),
	m_bJikokuhyouNyuusenJikokuDisplayKudari(false),
	m_bJikokuhyouNyuusenJikokuDisplayNobori(false),
	m_iJikokuhyouPrevRessyabangouDisplayKudari(0),
	m_iJikokuhyouPrevRessyabangouDisplayNobori(0),
	m_iJikokuhyouPrevOperationNumberDisplayKudari(0),
	m_iJikokuhyouPrevOperationNumberDisplayNobori(0),
	m_iJikokuhyouPrevOperationNumberDisplayRowsKudari(1),
	m_iJikokuhyouPrevOperationNumberDisplayRowsNobori(1),
	m_iJikokuhyouPrevRessyaSyubetsuDisplayKudari(0),
	m_iJikokuhyouPrevRessyaSyubetsuDisplayNobori(0),
	m_iJikokuhyouPrevRessyameiDisplayKudari(0),
	m_iJikokuhyouPrevRessyameiDisplayNobori(0)

{
	m_CentDedEkiTrack2Cont.insert(
		CentDedEkiTrack2(_T("1番線"), _T("1"), _T("")),
		INT_MAX);
	m_CentDedEkiTrack2Cont.insert(
		CentDedEkiTrack2(_T("2番線"), _T("2"), _T("")),
		INT_MAX);
	m_bDiagramTrackOmit.push_back(false);
	m_bDiagramTrackOmit.push_back(false);
	m_OuterTerminalCont.clear();
	//m_strOuterTerminalEkimei.clear();
	m_iEkiIndexBrunchOriginSide.clear();
	m_iEkiIndexLoop.clear();
	m_iEkiIndexBrunchTerminalSide.clear();
	m_CrossingCheckRuleCont.clear();
};

CentDedEki::CentDedEki( const tstring& strEkimei , 
			EEkijikokukeisiki	eEkijikokukeisiki ,
			EEkikibo	eEkikibo , 
			bool bKyoukaisen , 
			EDiagramRessyajouhouHyouji eDiagramRessyajouhouHyoujiKudari  ,
			EDiagramRessyajouhouHyouji eDiagramRessyajouhouHyoujiNobori  ) 
	:
	m_strEkimei( strEkimei ) ,
	m_eEkijikokukeisiki( eEkijikokukeisiki ) ,
	m_eEkikibo( eEkikibo ) ,
	m_bKyoukaisen( bKyoukaisen ) ,
	m_eDiagramRessyajouhouHyoujiKudari( eDiagramRessyajouhouHyoujiKudari ) ,
	m_eDiagramRessyajouhouHyoujiNobori( eDiagramRessyajouhouHyoujiNobori ),
	m_iDownMain(0),
	m_iUpMain(1),
	m_iID(-1),
	m_iBrunchCoreEkiIndex(-1),
	m_bBrunchOpposite(false),
	m_iLoopOriginEkiIndex(-1),
	m_bLoopOpposite(false),
	m_bJikokuhyouTrackDisplayKudari(false),
	m_bJikokuhyouTrackDisplayNobori(false),
	m_bDiagramTrackDisplay(false),
	m_iNextEkiDistance(0),
	m_bJikokuhyouTrackOmit(false),
	m_iBrunchLoopPosition(-1),
	m_iJikokuhyouOperationOrigin(0),
	m_iJikokuhyouOperationTerminal(0),
	m_bJikokuhyouOperationOriginDownBeforeUpAfter(false),
	m_bJikokuhyouOperationOriginDownAfterUpBefore(false),
	m_bJikokuhyouOperationTerminalDownBeforeUpAfter(false),
	m_bJikokuhyouOperationTerminalDownAfterUpBefore(false),
	m_strEkimeiJikokuhyouRyaku(_T("")),
	m_strEkimeiDiagramRyaku(_T("")),
	m_bJikokuhyouChakuJikokuDisplayKudari(true),
	m_bJikokuhyouChakuJikokuDisplayNobori(true),
	m_bJikokuhyouHatsuJikokuDisplayKudari(true),
	m_bJikokuhyouHatsuJikokuDisplayNobori(true),
	m_iJikokuhyouRessyabangouDisplayKudari(0),
	m_iJikokuhyouRessyabangouDisplayNobori(0),
	m_iJikokuhyouOperationNumberDisplayKudari(0),
	m_iJikokuhyouOperationNumberDisplayNobori(0),
	m_iJikokuhyouOperationNumberDisplayRowsKudari(1),
	m_iJikokuhyouOperationNumberDisplayRowsNobori(1),
	m_iJikokuhyouRessyaSyubetsuDisplayKudari(0),
	m_iJikokuhyouRessyaSyubetsuDisplayNobori(0),
	m_iJikokuhyouRessyameiDisplayKudari(0),
	m_iJikokuhyouRessyameiDisplayNobori(0),
	m_bJikokuhyouOuterSihatsuDisplayKudari(false),
	m_bJikokuhyouOuterShuchakuDisplayKudari(false),
	m_bJikokuhyouOuterSihatsuDisplayNobori(false),
	m_bJikokuhyouOuterShuchakuDisplayNobori(false),
	m_iDiagramColorNextEki(0),
	m_bOperationTableDisplayJikoku(false),
	m_bJikokuhyouNyuusenJikokuDisplayKudari(false),
	m_bJikokuhyouNyuusenJikokuDisplayNobori(false),
	m_iJikokuhyouPrevRessyabangouDisplayKudari(0),
	m_iJikokuhyouPrevRessyabangouDisplayNobori(0),
	m_iJikokuhyouPrevOperationNumberDisplayKudari(0),
	m_iJikokuhyouPrevOperationNumberDisplayNobori(0),
	m_iJikokuhyouPrevOperationNumberDisplayRowsKudari(1),
	m_iJikokuhyouPrevOperationNumberDisplayRowsNobori(1),
	m_iJikokuhyouPrevRessyaSyubetsuDisplayKudari(0),
	m_iJikokuhyouPrevRessyaSyubetsuDisplayNobori(0),
	m_iJikokuhyouPrevRessyameiDisplayKudari(0),
	m_iJikokuhyouPrevRessyameiDisplayNobori(0)
{
	m_CentDedEkiTrack2Cont.insert(
		CentDedEkiTrack2(_T("1番線"), _T("1"), _T("")),
		INT_MAX);
	m_CentDedEkiTrack2Cont.insert(
		CentDedEkiTrack2(_T("2番線"), _T("2"), _T("")),
		INT_MAX);
	m_bDiagramTrackOmit.push_back(false);
	m_bDiagramTrackOmit.push_back(false);
	m_OuterTerminalCont.clear();
	//m_strOuterTerminalEkimei.clear();
	m_iEkiIndexBrunchOriginSide.clear();
	m_iEkiIndexLoop.clear();
	m_iEkiIndexBrunchTerminalSide.clear();
	m_CrossingCheckRuleCont.clear();
};

CentDedEki& CentDedEki::operator=( const CentDedEki& value ) 
{
	//	このオブジェクトが、親オブジェクトCentDedEkiTrackCont の
	//	子である場合で、代入元が CentDedEkiTrackCont::set() でエラーに
	//	なる場合、例外スローになります。
	CentDedEkiCont* pParent 
		= dynamic_cast<CentDedEkiCont*>( getParent() ) ;
	if ( pParent != NULL )
	{
		if ( pParent->setable( value , pParent->getIndex( this ) < 0 ) )
		{
			throw( LException() ) ;
		}
	}

	//	メンバーのコピー
	m_strEkimei = value.m_strEkimei ;
	m_eEkijikokukeisiki = value.m_eEkijikokukeisiki ;
	m_eEkikibo = value.m_eEkikibo ;
	m_bKyoukaisen = value.m_bKyoukaisen ;
	m_eDiagramRessyajouhouHyoujiKudari = value.m_eDiagramRessyajouhouHyoujiKudari ;
	m_eDiagramRessyajouhouHyoujiNobori = value.m_eDiagramRessyajouhouHyoujiNobori ;
	m_iDownMain = value.m_iDownMain;
	m_iUpMain = value.m_iUpMain;
	m_iID = value.m_iID;
	m_iBrunchCoreEkiIndex = value.m_iBrunchCoreEkiIndex;
	m_bBrunchOpposite = value.m_bBrunchOpposite;
	m_iLoopOriginEkiIndex = value.m_iLoopOriginEkiIndex;
	m_bLoopOpposite = value.m_bLoopOpposite;
	m_bJikokuhyouTrackDisplayKudari = value.m_bJikokuhyouTrackDisplayKudari;
	m_bJikokuhyouTrackDisplayNobori = value.m_bJikokuhyouTrackDisplayNobori;
	m_bDiagramTrackDisplay = value.m_bDiagramTrackDisplay;
	m_OuterTerminalCont = value.m_OuterTerminalCont;
	//m_strOuterTerminalEkimei = value.m_strOuterTerminalEkimei;
	m_iNextEkiDistance = value.m_iNextEkiDistance;
	m_bJikokuhyouTrackOmit = value.m_bJikokuhyouTrackOmit;
	m_iJikokuhyouOperationOrigin = value.m_iJikokuhyouOperationOrigin;
	m_iJikokuhyouOperationTerminal = value.m_iJikokuhyouOperationTerminal;
	m_bJikokuhyouOperationOriginDownBeforeUpAfter = value.m_bJikokuhyouOperationOriginDownBeforeUpAfter;
	m_bJikokuhyouOperationOriginDownAfterUpBefore = value.m_bJikokuhyouOperationOriginDownAfterUpBefore;
	m_bJikokuhyouOperationTerminalDownBeforeUpAfter = value.m_bJikokuhyouOperationTerminalDownBeforeUpAfter;
	m_bJikokuhyouOperationTerminalDownAfterUpBefore = value.m_bJikokuhyouOperationTerminalDownAfterUpBefore;
	m_strEkimeiJikokuhyouRyaku = value.m_strEkimeiJikokuhyouRyaku;
	m_strEkimeiDiagramRyaku = value.m_strEkimeiDiagramRyaku;
	m_bJikokuhyouChakuJikokuDisplayKudari = value.m_bJikokuhyouChakuJikokuDisplayKudari;
	m_bJikokuhyouChakuJikokuDisplayNobori = value.m_bJikokuhyouChakuJikokuDisplayNobori;
	m_bJikokuhyouHatsuJikokuDisplayKudari = value.m_bJikokuhyouHatsuJikokuDisplayKudari;
	m_bJikokuhyouHatsuJikokuDisplayNobori = value.m_bJikokuhyouHatsuJikokuDisplayNobori;
	m_iJikokuhyouRessyabangouDisplayKudari = value.m_iJikokuhyouRessyabangouDisplayKudari;
	m_iJikokuhyouRessyabangouDisplayNobori = value.m_iJikokuhyouRessyabangouDisplayNobori;
	m_iJikokuhyouOperationNumberDisplayKudari = value.m_iJikokuhyouOperationNumberDisplayKudari;
	m_iJikokuhyouOperationNumberDisplayNobori = value.m_iJikokuhyouOperationNumberDisplayNobori;
	m_iJikokuhyouOperationNumberDisplayRowsKudari = value.m_iJikokuhyouOperationNumberDisplayRowsKudari;
	m_iJikokuhyouOperationNumberDisplayRowsNobori = value.m_iJikokuhyouOperationNumberDisplayRowsNobori;
	m_iJikokuhyouRessyaSyubetsuDisplayKudari = value.m_iJikokuhyouRessyaSyubetsuDisplayKudari;
	m_iJikokuhyouRessyaSyubetsuDisplayNobori = value.m_iJikokuhyouRessyaSyubetsuDisplayNobori;
	m_iJikokuhyouRessyameiDisplayKudari = value.m_iJikokuhyouRessyameiDisplayKudari;
	m_iJikokuhyouRessyameiDisplayNobori = value.m_iJikokuhyouRessyameiDisplayNobori;
	m_bJikokuhyouOuterSihatsuDisplayKudari = value.m_bJikokuhyouOuterSihatsuDisplayKudari;
	m_bJikokuhyouOuterShuchakuDisplayKudari = value.m_bJikokuhyouOuterShuchakuDisplayKudari;
	m_bJikokuhyouOuterSihatsuDisplayNobori = value.m_bJikokuhyouOuterSihatsuDisplayNobori;
	m_bJikokuhyouOuterShuchakuDisplayNobori = value.m_bJikokuhyouOuterShuchakuDisplayNobori;
	m_iDiagramColorNextEki = value.m_iDiagramColorNextEki;
	m_bOperationTableDisplayJikoku = value.m_bOperationTableDisplayJikoku;
	m_bJikokuhyouNyuusenJikokuDisplayKudari = value.m_bJikokuhyouNyuusenJikokuDisplayKudari;
	m_bJikokuhyouNyuusenJikokuDisplayNobori = value.m_bJikokuhyouNyuusenJikokuDisplayNobori;
	m_iJikokuhyouPrevRessyabangouDisplayKudari = value.m_iJikokuhyouPrevRessyabangouDisplayKudari;
	m_iJikokuhyouPrevRessyabangouDisplayNobori = value.m_iJikokuhyouPrevRessyabangouDisplayNobori;
	m_iJikokuhyouPrevOperationNumberDisplayKudari = value.m_iJikokuhyouPrevOperationNumberDisplayKudari;
	m_iJikokuhyouPrevOperationNumberDisplayNobori = value.m_iJikokuhyouPrevOperationNumberDisplayNobori;
	m_iJikokuhyouPrevOperationNumberDisplayRowsKudari = value.m_iJikokuhyouPrevOperationNumberDisplayRowsKudari;
	m_iJikokuhyouPrevOperationNumberDisplayRowsNobori = value.m_iJikokuhyouPrevOperationNumberDisplayRowsNobori;
	m_iJikokuhyouPrevRessyaSyubetsuDisplayKudari = value.m_iJikokuhyouPrevRessyaSyubetsuDisplayKudari;
	m_iJikokuhyouPrevRessyaSyubetsuDisplayNobori = value.m_iJikokuhyouPrevRessyaSyubetsuDisplayNobori;
	m_iJikokuhyouPrevRessyameiDisplayKudari = value.m_iJikokuhyouPrevRessyameiDisplayKudari;
	m_iJikokuhyouPrevRessyameiDisplayNobori = value.m_iJikokuhyouPrevRessyameiDisplayNobori;
	m_CrossingCheckRuleCont = value.m_CrossingCheckRuleCont;
	m_bDiagramTrackOmit = value.m_bDiagramTrackOmit;

	// --------------------------------
	super::operator=( value ) ;
	return *this ;
}

	// ********************************
	//@name CParentBase-操作
	// ********************************
void CentDedEki::setParent( CParentBase* pParent ) 
{
	super::setParent( pParent ) ;
}


	// ********************************
	//@name CentDedEki-操作
	// ********************************

bool CentDedEki::getDiagramTrackOmit(int iIndex) const
{
	if (iIndex >= 0 && iIndex < (int)m_bDiagramTrackOmit.size())
	{
		return m_bDiagramTrackOmit[iIndex];
		//return m_strOuterTerminalEkimei[iIndex];
	}
	return false;
}

OuterTerminal CentDedEki::getOuterTerminal(int iIndex) const
{
	if (iIndex >= 0 && iIndex < getOuterTerminalEkimeiCount())
	{
		return m_OuterTerminalCont[iIndex];
		//return m_strOuterTerminalEkimei[iIndex];
	}
	return OuterTerminal();
}

tstring CentDedEki::getOuterTerminalEkimei(int iIndex) const
{
	if (iIndex >= 0 && iIndex < getOuterTerminalEkimeiCount())
	{
		return m_OuterTerminalCont[iIndex].OuterTerminalEkimei;
		//return m_strOuterTerminalEkimei[iIndex];
	}
	return _T("");
}
tstring CentDedEki::getOuterTerminalJikokuRyaku(int iIndex, bool bEkimeiIfEmpty) const
{
	if (iIndex >= 0 && iIndex < getOuterTerminalEkimeiCount())
	{
		if (bEkimeiIfEmpty && m_OuterTerminalCont[iIndex].OuterTerminalJikokuRyaku.empty())
		{
			return m_OuterTerminalCont[iIndex].OuterTerminalEkimei;
		}
		else 
		{
			return m_OuterTerminalCont[iIndex].OuterTerminalJikokuRyaku;
			//return m_strOuterTerminalEkimei[iIndex];
		}
	}
	return _T("");
}
tstring CentDedEki::getOuterTerminalDiaRyaku(int iIndex, bool bEkimeiIfEmpty) const
{
	if (iIndex >= 0 && iIndex < getOuterTerminalEkimeiCount())
	{
		if (bEkimeiIfEmpty && m_OuterTerminalCont[iIndex].OuterTerminalDiaRyaku.empty())
		{
			tstring strEkimei = m_OuterTerminalCont[iIndex].OuterTerminalEkimei;
			return strEkimei.substr(0, 1);
		}
		else
		{
			return m_OuterTerminalCont[iIndex].OuterTerminalDiaRyaku;
			//return m_strOuterTerminalEkimei[iIndex];
		}
	}
	return _T("");
}

void CentDedEki::setOuterTerminalEkimei(const OuterTerminal & value, int iIndex)
{
	if (iIndex >= 0 && iIndex < getOuterTerminalEkimeiCount())
	{
		m_OuterTerminalCont[iIndex] = value;
		//m_strOuterTerminalEkimei[iIndex] = value;
	}
}

void CentDedEki::insertOuterTerminalEkimei(const OuterTerminal & value, int iIndex)
{
	if (iIndex == INT_MAX)
	{
		iIndex = getOuterTerminalEkimeiCount();
	}

	if (iIndex >= 0 && iIndex <= getOuterTerminalEkimeiCount())
	{
		m_OuterTerminalCont.insert(m_OuterTerminalCont.begin() + iIndex, value);
		//m_strOuterTerminalEkimei.insert(m_strOuterTerminalEkimei.begin() + iIndex, value);
	}
}

void CentDedEki::eraseOuterTerminalEkimei(int iIndex, int iSize)
{
	if (iIndex == INT_MAX && iSize != INT_MAX)
	{
		iIndex = getOuterTerminalEkimeiCount() - iSize;
	}
	else if (iIndex != INT_MAX && iSize == INT_MAX)
	{
		iSize = getOuterTerminalEkimeiCount() - iIndex;
	}
	if (iIndex >= 0 && iIndex + iSize <= getOuterTerminalEkimeiCount())
	{
		m_OuterTerminalCont.erase(
			m_OuterTerminalCont.begin() + iIndex,
			m_OuterTerminalCont.begin() + iIndex + iSize);
		//m_strOuterTerminalEkimei.erase(
		//	m_strOuterTerminalEkimei.begin() + iIndex,
		//	m_strOuterTerminalEkimei.begin() + iIndex + iSize);
	}
}

int CentDedEki::getOuterTerminalEkimeiCount() const
{
	return m_OuterTerminalCont.size();
	//return m_strOuterTerminalEkimei.size();
}

vector<OuterTerminal> CentDedEki::getOuterTerminalEkimeiCont() const
{
	return m_OuterTerminalCont;
	//return m_strOuterTerminalEkimei;
}

int CentDedEki::searchOuterTerminalEkimei(const tstring& strEkimei)
{
	for (int idx = 0; idx < (int)m_OuterTerminalCont.size(); idx++)
	{
		if (strEkimei == m_OuterTerminalCont[idx].OuterTerminalEkimei)
		{
			return idx;
		}
	}
	
	return -1;
}

int CentDedEki::addOuterTerminalEkimei(const OuterTerminal& strEkimei)
{
	m_OuterTerminalCont.push_back(strEkimei);
	return m_OuterTerminalCont.size() - 1;
}



tstring CentDedEki::getEkimeiJikokuhyouRyaku(bool bEkimeiIfEmpty) const
{
	if (bEkimeiIfEmpty && m_strEkimeiJikokuhyouRyaku.empty())
	{
		return m_strEkimei;
	}
	return m_strEkimeiJikokuhyouRyaku;
}

tstring CentDedEki::getEkimeiDiagramRyaku(bool bEkimeiIfEmpty) const
{
	if (bEkimeiIfEmpty && m_strEkimeiDiagramRyaku.empty())
	{
		return m_strEkimei.substr(0, 1);
	}
	return m_strEkimeiDiagramRyaku;
}

void CentDedEki::onEkiInsert(int iEkiIndex,int size)
{
	//m_iBrunchCoreEkiIndex,m_iLoopOriginEkiIndexがコンテナサイズ以下の場合は、初期読み込みと見て加算を行わない
	if (m_iBrunchCoreEkiIndex >= iEkiIndex &&
		m_iBrunchCoreEkiIndex + 1 < size)
	{
		m_iBrunchCoreEkiIndex++;
	}
	if (m_iLoopOriginEkiIndex >= iEkiIndex &&
		m_iLoopOriginEkiIndex + 1 < size)
	{
		m_iLoopOriginEkiIndex++;
	}

	for (int idx = getCrossingCheckRuleSize() - 1; idx >= 0; idx--)
	{
		CrossingCheckRule CrossingCheckRuleTemp = getCrossingCheckRule(idx);

		vector< TrackContent> BeforeFromTrackContentCont = CrossingCheckRuleTemp.BeforeFromTrackContentCont;
		for (int idxbf = (int)BeforeFromTrackContentCont.size() - 1; idxbf >= 0; idxbf--)
		{
			if (BeforeFromTrackContentCont[idxbf].eTrackType == ETrackType::TrackType_Origin || 
				BeforeFromTrackContentCont[idxbf].eTrackType == ETrackType::TrackType_Terminal)
			{
				if (BeforeFromTrackContentCont[idxbf].iTrackIndex >= iEkiIndex &&
					BeforeFromTrackContentCont[idxbf].iTrackIndex + 1 < size)
				{
					BeforeFromTrackContentCont[idxbf].iTrackIndex++;
				}
			}
		}
		CrossingCheckRuleTemp.BeforeFromTrackContentCont = BeforeFromTrackContentCont;

		vector< TrackContent> BeforeToTrackContentCont = CrossingCheckRuleTemp.BeforeToTrackContentCont;
		for (int idxbt = (int)BeforeToTrackContentCont.size() - 1; idxbt >= 0; idxbt--)
		{
			if (BeforeToTrackContentCont[idxbt].eTrackType == ETrackType::TrackType_Origin||
				BeforeToTrackContentCont[idxbt].eTrackType == ETrackType::TrackType_Terminal)
			{
				if (BeforeToTrackContentCont[idxbt].iTrackIndex >= iEkiIndex &&
					BeforeToTrackContentCont[idxbt].iTrackIndex + 1 < size)
				{
					BeforeToTrackContentCont[idxbt].iTrackIndex++;
				}
			}
		}
		CrossingCheckRuleTemp.BeforeToTrackContentCont = BeforeToTrackContentCont;

		vector< TrackContent> AfterFromTrackContentCont = CrossingCheckRuleTemp.AfterFromTrackContentCont;
		for (int idxaf = (int)AfterFromTrackContentCont.size() - 1; idxaf >= 0; idxaf--)
		{
			if (AfterFromTrackContentCont[idxaf].eTrackType == ETrackType::TrackType_Origin||
				AfterFromTrackContentCont[idxaf].eTrackType == ETrackType::TrackType_Terminal)
			{
				if (AfterFromTrackContentCont[idxaf].iTrackIndex >= iEkiIndex &&
					AfterFromTrackContentCont[idxaf].iTrackIndex + 1 < size)
				{
					AfterFromTrackContentCont[idxaf].iTrackIndex++;
				}
			}
		}
		CrossingCheckRuleTemp.AfterFromTrackContentCont = AfterFromTrackContentCont;

		vector< TrackContent> AfterToTrackContentCont = CrossingCheckRuleTemp.AfterToTrackContentCont;
		for (int idxat = (int)AfterToTrackContentCont.size() - 1; idxat >= 0; idxat--)
		{
			if (AfterToTrackContentCont[idxat].eTrackType == ETrackType::TrackType_Origin||
				AfterToTrackContentCont[idxat].eTrackType == ETrackType::TrackType_Terminal)
			{
				if (AfterToTrackContentCont[idxat].eTrackType == ETrackType::TrackType_Origin ||
					AfterToTrackContentCont[idxat].eTrackType == ETrackType::TrackType_Terminal)
				{
					if (AfterToTrackContentCont[idxat].iTrackIndex >= iEkiIndex &&
						AfterToTrackContentCont[idxat].iTrackIndex + 1 < size)
					{
						AfterToTrackContentCont[idxat].iTrackIndex++;
					}
				}
			}
		}
		CrossingCheckRuleTemp.AfterToTrackContentCont = AfterToTrackContentCont;

		setCrossingCheckRule(CrossingCheckRuleTemp, idx);
	}
}

void CentDedEki::onEkiErase(int iEkiIndex)
{
	if (m_iBrunchCoreEkiIndex > iEkiIndex)
	{
		m_iBrunchCoreEkiIndex--;
	}
	if (m_iLoopOriginEkiIndex > iEkiIndex)
	{
		m_iLoopOriginEkiIndex--;
	}

	for (int idx = getCrossingCheckRuleSize() - 1; idx >= 0; idx--)
	{
		CrossingCheckRule CrossingCheckRuleTemp = getCrossingCheckRule(idx);

		vector< TrackContent> BeforeFromTrackContentCont = CrossingCheckRuleTemp.BeforeFromTrackContentCont;
		for (int idxbf = (int)BeforeFromTrackContentCont.size() - 1; idxbf >= 0; idxbf--)
		{
			if (BeforeFromTrackContentCont[idxbf].eTrackType == ETrackType::TrackType_Origin ||
				BeforeFromTrackContentCont[idxbf].eTrackType == ETrackType::TrackType_Terminal)
			{
				if (BeforeFromTrackContentCont[idxbf].iTrackIndex > iEkiIndex)
				{
					BeforeFromTrackContentCont[idxbf].iTrackIndex--;
				}
			}
		}
		CrossingCheckRuleTemp.BeforeFromTrackContentCont = BeforeFromTrackContentCont;

		vector< TrackContent> BeforeToTrackContentCont = CrossingCheckRuleTemp.BeforeToTrackContentCont;
		for (int idxbt = (int)BeforeToTrackContentCont.size() - 1; idxbt >= 0; idxbt--)
		{
			if (BeforeToTrackContentCont[idxbt].eTrackType == ETrackType::TrackType_Origin ||
				BeforeToTrackContentCont[idxbt].eTrackType == ETrackType::TrackType_Terminal)
			{
				if (BeforeToTrackContentCont[idxbt].iTrackIndex > iEkiIndex)
				{
					BeforeToTrackContentCont[idxbt].iTrackIndex--;
				}
			}
		}
		CrossingCheckRuleTemp.BeforeToTrackContentCont = BeforeToTrackContentCont;

		vector< TrackContent> AfterFromTrackContentCont = CrossingCheckRuleTemp.AfterFromTrackContentCont;
		for (int idxaf = (int)AfterFromTrackContentCont.size() - 1; idxaf >= 0; idxaf--)
		{
			if (AfterFromTrackContentCont[idxaf].eTrackType == ETrackType::TrackType_Origin ||
				AfterFromTrackContentCont[idxaf].eTrackType == ETrackType::TrackType_Terminal)
			{
				if (AfterFromTrackContentCont[idxaf].iTrackIndex > iEkiIndex)
				{
					AfterFromTrackContentCont[idxaf].iTrackIndex--;
				}
			}
		}
		CrossingCheckRuleTemp.AfterFromTrackContentCont = AfterFromTrackContentCont;

		vector< TrackContent> AfterToTrackContentCont = CrossingCheckRuleTemp.AfterToTrackContentCont;
		for (int idxat = (int)AfterToTrackContentCont.size() - 1; idxat >= 0; idxat--)
		{
			if (AfterToTrackContentCont[idxat].eTrackType == ETrackType::TrackType_Origin ||
				AfterToTrackContentCont[idxat].eTrackType == ETrackType::TrackType_Terminal)
			{
				if (AfterToTrackContentCont[idxat].eTrackType == ETrackType::TrackType_Origin ||
					AfterToTrackContentCont[idxat].eTrackType == ETrackType::TrackType_Terminal)
				{
					if (AfterToTrackContentCont[idxat].iTrackIndex > iEkiIndex )
					{
						AfterToTrackContentCont[idxat].iTrackIndex--;
					}
				}
			}
		}
		CrossingCheckRuleTemp.AfterToTrackContentCont = AfterToTrackContentCont;

		setCrossingCheckRule(CrossingCheckRuleTemp, idx);
	}
}

int CentDedEki::compareMainTrack(const CentDedEki * pCentDedEki)
{
	int iRv=0;
	if (getDownMain() != pCentDedEki->getDownMain())
	{
		iRv = 1;
	}
	if (getUpMain() != pCentDedEki->getUpMain())
	{
		iRv = iRv+2;
	}
	return iRv;
}

int CentDedEki::compareOuterTerminal(const CentDedEki* pCentDedEki)const
{
	int iRv;
	if (getOuterTerminalEkimeiCount() > pCentDedEki->getOuterTerminalEkimeiCount())
	{
		iRv = 3;
	}
	else if (getOuterTerminalEkimeiCount() < pCentDedEki->getOuterTerminalEkimeiCount())
	{
		iRv = -1;
	}
	else
	{
		iRv = 0;
		for (int idx = 0; idx < getOuterTerminalEkimeiCount() && iRv < 2; idx++)
		{
			const OuterTerminal sOuterTerminalThis = getOuterTerminal(idx);
			const OuterTerminal sOuterTerminalComp = pCentDedEki->getOuterTerminal(idx);
			if (sOuterTerminalThis.OuterTerminalEkimei != sOuterTerminalComp.OuterTerminalEkimei)
			{
				iRv = 2;
			}
			if (iRv == 0 &&
				sOuterTerminalThis.OuterTerminalJikokuRyaku != sOuterTerminalComp.OuterTerminalJikokuRyaku)
			{
				iRv = 1;
			}
			if (iRv == 0 &&
				sOuterTerminalThis.OuterTerminalDiaRyaku != sOuterTerminalComp.OuterTerminalDiaRyaku)
			{
				iRv = 1;
			}
		}
	}
	return iRv;
}


}//namespace entDed 
