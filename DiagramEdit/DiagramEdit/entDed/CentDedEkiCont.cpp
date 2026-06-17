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
//	CentDedEkiCont.cpp
// ****************************************************************
*/
#include "stdafx.h"
#include <assert.h>
#include "CentDedEkiCont.h"
#include "CentDedRosen.h"

#ifndef _CONSOLE
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

namespace entDed{

// ----------------------------------------------------------------
//	CentDedEkiCont::ContKudari
// ----------------------------------------------------------------
int CentDedEkiCont::ContKudari::size()const 
{
	CentDedEkiCont* pAdaptee = (CentDedEkiCont*)( (char*)this - 
		offsetof( CentDedEkiCont , CentDedEkiCont::m_xContKudari ) ) ;
	
	return pAdaptee->size() ;
}
CentDedEkiCont::CdDedEki CentDedEkiCont::ContKudari::get(int iEkiOrder)const
{
	CentDedEkiCont* pAdaptee = (CentDedEkiCont*)((char*)this -
		offsetof(CentDedEkiCont, CentDedEkiCont::m_xContKudari));

	int iEkiIndex = pAdaptee->EkiIndexOfEkiOrder(Ressyahoukou_Kudari, iEkiOrder);
	CentDedEki aCentDedEki = pAdaptee->get(iEkiIndex);
	CentDedEki aCentDedEkiNext;
	if (iEkiIndex < size() - 1)
	{
		aCentDedEkiNext = pAdaptee->get(iEkiIndex + 1);
	}
	//下りの境界線：当駅が下り着＆BrunchCoreEkiIndex>=0 もしくは Nextが上り着＆BrunchCoreEkiIndex>=0
	bool bKyoukaisen = false;
	if (aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku &&
		aCentDedEki.getBrunchCoreEkiIndex() >= 0)
	{
		bKyoukaisen = true;
	}
	else if (aCentDedEkiNext.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku &&
		aCentDedEkiNext.getBrunchCoreEkiIndex() >= 0)
	{
		bKyoukaisen = true;
	}
	else if (aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku &&
		aCentDedEkiNext.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku)
	{
		bKyoukaisen = true;
	}
	//番線編集モード時の番線表省略：当駅が発時刻表示もしくは上り発着時にtrue
	bool bJikokuhyouTrackOmit = false;
	if ((aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsu ||
		aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku) &&
		aCentDedEki.getJikokuhyouTrackOmit())
	{
		bJikokuhyouTrackOmit = true;
	}

	//基本モード時の作業表示欄設定。駅形式が上り発着(・発時刻)の場合は、下り時刻表の作業欄は設けない
	int iJikokuhyouOperationOrigin = 0;
	int iJikokuhyouOperationTerminal = 0;
	bool bJikokuhyouBeforeOperationBefore = false;
	bool bJikokuhyouBeforeOperationAfter = false;
	bool bJikokuhyouAfterOperationBefore = false;
	bool bJikokuhyouAfterOperationAfter = false;
	if (aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
		aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
		aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ||
		aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku)
	{
		iJikokuhyouOperationOrigin = aCentDedEki.getJikokuhyouOperationOrigin();
		iJikokuhyouOperationTerminal = aCentDedEki.getJikokuhyouOperationTerminal();
		bJikokuhyouBeforeOperationBefore = aCentDedEki.getJikokuhyouOperationOriginDownBeforeUpAfter();
		bJikokuhyouBeforeOperationAfter = aCentDedEki.getJikokuhyouOperationOriginDownAfterUpBefore();
		bJikokuhyouAfterOperationBefore = aCentDedEki.getJikokuhyouOperationTerminalDownBeforeUpAfter();
		bJikokuhyouAfterOperationAfter = aCentDedEki.getJikokuhyouOperationTerminalDownAfterUpBefore();
	}
	//Ver2.06.21 カスタマイズ時刻表の着時刻・発時刻・種別変更欄表示設定を変更。従来無しだった一部駅形式でも、路線外発着欄の有無により表示が可能に。
	bool bJikokuhyouChakuJikokuDisplayKudari = aCentDedEki.getJikokuhyouChakuJikokuDisplayKudari();
	if (bJikokuhyouChakuJikokuDisplayKudari &&
		aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku &&
		!aCentDedEki.getJikokuhyouOuterSihatsuDisplayKudari())
	{
		//駅時刻形式が上り着かつ路線外始発欄がない場合は、着時刻表示を無効にする。
		bJikokuhyouChakuJikokuDisplayKudari = false;
	}
	bool bJikokuhyouHatsuJikokuDisplayKudari = aCentDedEki.getJikokuhyouHatsuJikokuDisplayKudari();
	if (bJikokuhyouHatsuJikokuDisplayKudari &&
		aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku &&
		!aCentDedEki.getJikokuhyouOuterShuchakuDisplayKudari())
	{
		//駅時刻形式が下り着かつ路線外終着欄がない場合は、発時刻表示を無効にする。
		bJikokuhyouHatsuJikokuDisplayKudari = false;

	}

	int iJikokuhyouRessyabangouDisplayKudari = aCentDedEki.getJikokuhyouRessyabangouDisplayKudari();
	if (iJikokuhyouRessyabangouDisplayKudari > 0 &&
		aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku &&
		!aCentDedEki.getJikokuhyouOuterShuchakuDisplayKudari())
	{
		//駅時刻形式が下り着かつ路線外終着欄がない場合は、列車番号表示を無効にする。
		iJikokuhyouRessyabangouDisplayKudari = 0;

	}

	int iJikokuhyouOperationNumberDisplayKudari = aCentDedEki.getJikokuhyouOperationNumberDisplayKudari();
	if (iJikokuhyouOperationNumberDisplayKudari > 0 &&
		aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku &&
		!aCentDedEki.getJikokuhyouOuterShuchakuDisplayKudari())
	{
		//駅時刻形式が下り着かつ路線外終着欄がない場合は、運用番号表示を無効にする。
		iJikokuhyouOperationNumberDisplayKudari = 0;

	}

	int iJikokuhyouRessyaSyubetsuDisplayKudari = aCentDedEki.getJikokuhyouRessyaSyubetsuDisplayKudari();
	if (iJikokuhyouRessyaSyubetsuDisplayKudari > 0 &&
		aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku &&
		!aCentDedEki.getJikokuhyouOuterShuchakuDisplayKudari())
	{
		//駅時刻形式が下り着かつ路線外終着欄がない場合は、列車種別表示を無効にする。
		iJikokuhyouRessyaSyubetsuDisplayKudari = 0;

	}

	int iJikokuhyouRessyameiDisplayKudari = aCentDedEki.getJikokuhyouRessyameiDisplayKudari();
	if (iJikokuhyouRessyameiDisplayKudari > 0 &&
		aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku &&
		!aCentDedEki.getJikokuhyouOuterShuchakuDisplayKudari())
	{
		//駅時刻形式が下り着かつ路線外終着欄がない場合は、列車名・号数表示を無効にする。
		iJikokuhyouRessyameiDisplayKudari = 0;

	}

	int iJikokuhyouPrevRessyabangouDisplayKudari = 0;
	int iJikokuhyouPrevOperationNumberDisplayKudari = 0;
	int iJikokuhyouPrevRessyaSyubetsuDisplayKudari = 0;
	int iJikokuhyouPrevRessyameiDisplayKudari = 0;
	if (aCentDedEki.getJikokuhyouOuterSihatsuDisplayKudari())
	{
		iJikokuhyouPrevRessyabangouDisplayKudari = aCentDedEki.getJikokuhyouPrevRessyabangouDisplayKudari();
		iJikokuhyouPrevOperationNumberDisplayKudari = aCentDedEki.getJikokuhyouPrevOperationNumberDisplayKudari();
		iJikokuhyouPrevRessyaSyubetsuDisplayKudari = aCentDedEki.getJikokuhyouPrevRessyaSyubetsuDisplayKudari();
		iJikokuhyouPrevRessyameiDisplayKudari = aCentDedEki.getJikokuhyouPrevRessyameiDisplayKudari();
	}

	CentDedEkiCont::CdDedEki aCdDedEki( 
		aCentDedEki.getEkimei() , 
		aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku || 
		aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku || 
		aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku , 
		aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku || 
		aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsu || 
		aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku || 
		aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku || 
		aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku ,
		aCentDedEki.getEkikibo() ,
		bKyoukaisen,
		//aCentDedEki.getKyoukaisen() ,
		aCentDedEki.getDiagramRessyajouhouHyoujiKudari() ,
		aCentDedEki.getDownMain(),
		aCentDedEki.getJikokuhyouTrackDisplayKudari() &&
		aCentDedEki.getEkijikokukeisiki() != CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku,
		aCentDedEki.getDiagramTrackDisplay(),
		aCentDedEki.getEkiTrack2Cont(),
		aCentDedEki.getOuterTerminalEkimeiCont(),
		bJikokuhyouTrackOmit,
		iJikokuhyouOperationOrigin,
		iJikokuhyouOperationTerminal,
		bJikokuhyouBeforeOperationBefore,
		bJikokuhyouBeforeOperationAfter,
		bJikokuhyouAfterOperationBefore,
		bJikokuhyouAfterOperationAfter,
		aCentDedEki.getEkimeiJikokuhyouRyaku(),
		aCentDedEki.getEkimeiDiagramRyaku(),
		bJikokuhyouChakuJikokuDisplayKudari,
		bJikokuhyouHatsuJikokuDisplayKudari,
		iJikokuhyouRessyabangouDisplayKudari,
		iJikokuhyouOperationNumberDisplayKudari,
		aCentDedEki.getJikokuhyouOperationNumberDisplayRowsKudari(),
		iJikokuhyouRessyaSyubetsuDisplayKudari,
		iJikokuhyouRessyameiDisplayKudari,
		aCentDedEki.getJikokuhyouOuterSihatsuDisplayKudari(),
		aCentDedEki.getJikokuhyouOuterShuchakuDisplayKudari(),
		aCentDedEki.getJikokuhyouNyuusenJikokuDisplayKudari(),
		iJikokuhyouPrevRessyabangouDisplayKudari,
		iJikokuhyouPrevOperationNumberDisplayKudari,
		aCentDedEki.getJikokuhyouPrevOperationNumberDisplayRowsKudari(),
		iJikokuhyouPrevRessyaSyubetsuDisplayKudari,
		iJikokuhyouPrevRessyameiDisplayKudari);
		//aCentDedEki.getEkiTrack2Cont()->getMuPtr());

	//CentDedEkiTrack2Cont* pCentDedEkiTrack2Cont = aCentDedEki.getEkiTrack2Cont();
	//for (int idx = 0; idx < pCentDedEkiTrack2Cont->size(); idx++)
	//{
	//	aCdDedEki.m_CentDedEkiTrack2
	//}
	return ( aCdDedEki ) ;
	
}
// ----------------------------------------------------------------
//	CentDedEkiCont::ContNobori
// ----------------------------------------------------------------
int CentDedEkiCont::ContNobori::size()const 
{
	CentDedEkiCont* pAdaptee = (CentDedEkiCont*)( (char*)this - offsetof( CentDedEkiCont , CentDedEkiCont::m_xContNobori ) ) ;
	
	return pAdaptee->size() ;
}
CentDedEkiCont::CdDedEki CentDedEkiCont::ContNobori::get(int iEkiOrder )const 
{
	CentDedEkiCont* pAdaptee = (CentDedEkiCont*)( (char*)this - offsetof( CentDedEkiCont , CentDedEkiCont::m_xContNobori ) ) ;
	
	int iEkiIndex = pAdaptee->EkiIndexOfEkiOrder( Ressyahoukou_Nobori , iEkiOrder ) ;
	CentDedEki aCentDedEki = pAdaptee->get( iEkiIndex ) ;

	CentDedEki aCentDedEkiPrev ;
	if ( iEkiIndex > 0 ){
		aCentDedEkiPrev = pAdaptee->get( iEkiIndex - 1 ) ;
	}
	//上りの境界線：当駅が上り着＆BrunchCoreEkiIndex>=0 もしくは Prevが下り着＆BrunchCoreEkiIndex>=0
	bool bKyoukaisen = false;
	if (aCentDedEkiPrev.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku &&
		aCentDedEkiPrev.getBrunchCoreEkiIndex() >= 0)
	{
		bKyoukaisen = true;
	}
	else if (aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku &&
		aCentDedEki.getBrunchCoreEkiIndex() >= 0)
	{
		bKyoukaisen = true;
	}
	else if (aCentDedEkiPrev.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku &&
		aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku)
	{
		bKyoukaisen = true;
	}

	//番線編集モード時の番線表省略：当駅が発時刻表示もしくは下り発着時にtrue
	bool bJikokuhyouTrackOmit = false;
	if ((aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsu ||
		aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku) &&
		aCentDedEki.getJikokuhyouTrackOmit())
	{
		bJikokuhyouTrackOmit = true;
	}

	//基本モード時の作業表示欄設定。駅形式が下り発着(・発時刻)の場合は、上り時刻表の作業欄は設けない
	int iJikokuhyouOperationOrigin = 0;
	int iJikokuhyouOperationTerminal = 0;
	bool bJikokuhyouBeforeOperationBefore = false;
	bool bJikokuhyouBeforeOperationAfter = false;
	bool bJikokuhyouAfterOperationBefore = false;
	bool bJikokuhyouAfterOperationAfter = false;
	if (aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
		aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
		aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ||
		aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
	{
		iJikokuhyouOperationOrigin = aCentDedEki.getJikokuhyouOperationOrigin();
		iJikokuhyouOperationTerminal = aCentDedEki.getJikokuhyouOperationTerminal();
		bJikokuhyouBeforeOperationBefore = aCentDedEki.getJikokuhyouOperationTerminalDownAfterUpBefore();
		bJikokuhyouBeforeOperationAfter = aCentDedEki.getJikokuhyouOperationTerminalDownBeforeUpAfter();
		bJikokuhyouAfterOperationBefore = aCentDedEki.getJikokuhyouOperationOriginDownAfterUpBefore();
		bJikokuhyouAfterOperationAfter = aCentDedEki.getJikokuhyouOperationOriginDownBeforeUpAfter();
	}

	//Ver2.06.21 カスタマイズ時刻表の着時刻・発時刻・種別変更欄表示設定を変更。従来無しだった一部駅形式でも、路線外発着欄の有無により表示が可能に。
	bool bJikokuhyouChakuJikokuDisplayNobori = aCentDedEki.getJikokuhyouChakuJikokuDisplayNobori();
	if (bJikokuhyouChakuJikokuDisplayNobori &&
		aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku &&
		!aCentDedEki.getJikokuhyouOuterSihatsuDisplayNobori())
	{
		//駅時刻形式が下り着かつ路線外始発欄がない場合は、着時刻表示を無効にする。
		bJikokuhyouChakuJikokuDisplayNobori = false;
	}
	bool bJikokuhyouHatsuJikokuDisplayNobori = aCentDedEki.getJikokuhyouHatsuJikokuDisplayNobori();
	if (bJikokuhyouHatsuJikokuDisplayNobori &&
		aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku &&
		!aCentDedEki.getJikokuhyouOuterShuchakuDisplayNobori())
	{
		//駅時刻形式が上り着かつ路線外終着欄がない場合は、発時刻表示を無効にする。
		bJikokuhyouHatsuJikokuDisplayNobori = false;

	}

	int iJikokuhyouRessyabangouDisplayNobori = aCentDedEki.getJikokuhyouRessyabangouDisplayNobori();
	if (iJikokuhyouRessyabangouDisplayNobori > 0 &&
		aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku &&
		!aCentDedEki.getJikokuhyouOuterShuchakuDisplayNobori())
	{
		//駅時刻形式が上り着かつ路線外終着欄がない場合は、列車番号表示を無効にする。
		iJikokuhyouRessyabangouDisplayNobori = 0;

	}

	int iJikokuhyouOperationNumberDisplayNobori = aCentDedEki.getJikokuhyouOperationNumberDisplayNobori();
	if (iJikokuhyouOperationNumberDisplayNobori > 0 &&
		aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku &&
		!aCentDedEki.getJikokuhyouOuterShuchakuDisplayNobori())
	{
		//駅時刻形式が上り着かつ路線外終着欄がない場合は、運用番号表示を無効にする。
		iJikokuhyouOperationNumberDisplayNobori = 0;

	}

	int iJikokuhyouRessyaSyubetsuDisplayNobori = aCentDedEki.getJikokuhyouRessyaSyubetsuDisplayNobori();
	if (iJikokuhyouRessyaSyubetsuDisplayNobori > 0 &&
		aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku &&
		!aCentDedEki.getJikokuhyouOuterShuchakuDisplayNobori())
	{
		//駅時刻形式が上り着かつ路線外終着欄がない場合は、列車種別表示を無効にする。
		iJikokuhyouRessyaSyubetsuDisplayNobori = 0;

	}

	int iJikokuhyouRessyameiDisplayNobori = aCentDedEki.getJikokuhyouRessyameiDisplayNobori();
	if (iJikokuhyouRessyameiDisplayNobori > 0 &&
		aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku &&
		!aCentDedEki.getJikokuhyouOuterShuchakuDisplayNobori())
	{
		//駅時刻形式が上り着かつ路線外終着欄がない場合は、列車名・号数表示を無効にする。
		iJikokuhyouRessyameiDisplayNobori = 0;

	}

	int iJikokuhyouPrevRessyabangouDisplayNobori = 0;
	int iJikokuhyouPrevOperationNumberDisplayNobori = 0;
	int iJikokuhyouPrevRessyaSyubetsuDisplayNobori = 0;
	int iJikokuhyouPrevRessyameiDisplayNobori = 0;
	if (aCentDedEki.getJikokuhyouOuterSihatsuDisplayNobori())
	{
		iJikokuhyouPrevRessyabangouDisplayNobori = aCentDedEki.getJikokuhyouPrevRessyabangouDisplayNobori();
		iJikokuhyouPrevOperationNumberDisplayNobori = aCentDedEki.getJikokuhyouPrevOperationNumberDisplayNobori();
		iJikokuhyouPrevRessyaSyubetsuDisplayNobori = aCentDedEki.getJikokuhyouPrevRessyaSyubetsuDisplayNobori();
		iJikokuhyouPrevRessyameiDisplayNobori = aCentDedEki.getJikokuhyouPrevRessyameiDisplayNobori();
	}

	//17.4.14 駅形式を追加_by_d_mania
	CentDedEkiCont::CdDedEki aCdDedEki( 
		aCentDedEki.getEkimei() , 
		aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku || 
		aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku || 
		aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku , 
		aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku || 
		aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsu || 
		aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku || 
		aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku || 
		aCentDedEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku ,
		aCentDedEki.getEkikibo() ,
		bKyoukaisen,
		//aCentDedEkiPrev.getKyoukaisen() , 
		aCentDedEki.getDiagramRessyajouhouHyoujiNobori(),
		aCentDedEki.getUpMain(),
		aCentDedEki.getJikokuhyouTrackDisplayNobori() &&
		aCentDedEki.getEkijikokukeisiki() != CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku,
		aCentDedEki.getDiagramTrackDisplay(),
		aCentDedEki.getEkiTrack2Cont(),
		aCentDedEki.getOuterTerminalEkimeiCont(),
		bJikokuhyouTrackOmit,
		iJikokuhyouOperationTerminal,
		iJikokuhyouOperationOrigin,
		bJikokuhyouBeforeOperationBefore,
		bJikokuhyouBeforeOperationAfter,
		bJikokuhyouAfterOperationBefore,
		bJikokuhyouAfterOperationAfter,
		aCentDedEki.getEkimeiJikokuhyouRyaku(),
		aCentDedEki.getEkimeiDiagramRyaku(),
		bJikokuhyouChakuJikokuDisplayNobori,
		bJikokuhyouHatsuJikokuDisplayNobori,
		iJikokuhyouRessyabangouDisplayNobori,
		iJikokuhyouOperationNumberDisplayNobori,
		aCentDedEki.getJikokuhyouOperationNumberDisplayRowsNobori(),
		iJikokuhyouRessyaSyubetsuDisplayNobori,
		iJikokuhyouRessyameiDisplayNobori,
		aCentDedEki.getJikokuhyouOuterSihatsuDisplayNobori(),
		aCentDedEki.getJikokuhyouOuterShuchakuDisplayNobori(),
		aCentDedEki.getJikokuhyouNyuusenJikokuDisplayNobori(),
		iJikokuhyouPrevRessyabangouDisplayNobori,
		iJikokuhyouPrevOperationNumberDisplayNobori,
		aCentDedEki.getJikokuhyouPrevOperationNumberDisplayRowsNobori(),
		iJikokuhyouPrevRessyaSyubetsuDisplayNobori,
		iJikokuhyouPrevRessyameiDisplayNobori);
		//aCentDedEki.getEkiTrack2Cont()->getMuPtr());

	return ( aCdDedEki ) ;
	
}
// ****************************************************************
//	CentDedEkiCont
// ****************************************************************

	
	// ********************************
	//@name Mui
	// ********************************
int CentDedEkiCont::insert( const CentDedEki& element ,  int iIndex )
{
	int iRv = 0; 
	if ( iIndex == INT_MAX )
	{
		iIndex = size() ;
	}
	if ( iRv >= 0 )
	{
		iRv = super::insert( element ,  iIndex ) ;
	}
	//m_iIDのセット、現在の値が0以上の場合は、ダブりがないかをチェック、
	//重複する場合は空いている値を割り当て
	//0未満の場合は、0以上で空いている値を割り当て
	if (iRv >= 0)
	{
		if (element.getID() < 0)
		{
			bool bExist;
			int iNewID;
			for (iNewID = 0; iNewID < INT_MAX; iNewID++)
			{
				bExist = false;
				for (int iEkiIndex = 0; iEkiIndex < size() && !bExist; iEkiIndex++)
				{
					if (get(iEkiIndex).getID() == iNewID && iEkiIndex != iIndex)
					{
						bExist = true;
					}
				}
				if (!bExist)
				{
					break;
				}
			}
			//bExistがfalseのままだった場合、forから抜け、iNewIDをIDとしてセットする。
			getMuPtr()->get(iIndex)->setID(iNewID);
		}
		else
		{
			bool bExist = false;
			for (int iEkiIndex = 0; iEkiIndex < size() && !bExist; iEkiIndex++)
			{
				if (get(iEkiIndex).getID() == element.getID() && iEkiIndex != iIndex)
				{
					bExist = true;
				}
			}
			//bExistがfalseのままなら、被っていないので、そのまま。
			//trueの場合被っているので、新しいIDを付与する
			if (bExist)
			{
				int iNewID;
				for (iNewID = 0; iNewID < INT_MAX; iNewID++)
				{
					bExist = false;
					for (int iEkiIndex = 0; iEkiIndex < size() && !bExist; iEkiIndex++)
					{
						if (get(iEkiIndex).getID() == iNewID && iEkiIndex != iIndex)
						{
							bExist = true;
						}
					}
					if (!bExist)
					{
						break;
					}
				}
				getMuPtr()->get(iIndex)->setID(iNewID);
			}
		}
	}
	//	  このコンテナが CentDedRosen に包含されている場合、 insert() 
	//	メソッドは、CentDedRosen::onEkInsert( iEkiIndex ) 
	//	に処理を委譲します。
	if ( iRv >= 0 )
	{
		CentDedRosen* pRosen = getRosen() ;
		if ( pRosen != NULL )
		{
			vector<int> iMainTrack;
			iMainTrack.push_back(element.getDownMain());
			iMainTrack.push_back(element.getUpMain());
			pRosen->onEkiInsert( iIndex , iMainTrack) ;
		}
	}

	return iRv ;
	
}

int CentDedEkiCont::erase( int iIndex  , int iSize ) 
{
	int iRv = 0 ;
	if ( iIndex == INT_MAX && iSize != INT_MAX )
	{
		iIndex = (int)size() - iSize ;
	}
	else if ( iIndex != INT_MAX && iSize == INT_MAX )
	{
		iSize = (int)size() - iIndex ;
	}
	if ( !( 0 <= iIndex && iIndex + iSize <= (int)size() ) )
	{
		iRv = -1 ;	//	インデクスが範囲外です。
	}
	// --------------------------------	
	if ( iRv >= 0 )
	{
		iRv = super::erase( iIndex , iSize ) ; 
	}
	// --------------------------------	
	//	  このコンテナが  CentDedRosen に包含されている場合、 erase() 
	//	メソッドは、CentDedRosen::onEkiErase( iEkiIndex )
	//	に処理を委譲します。
	if ( iRv >= 0 )
	{
		CentDedRosen* pRosen = getRosen() ;
		if ( pRosen != NULL )
		{
			for ( int idx = iIndex + iSize - 1 ; idx >= iIndex ; idx-- )
			{
				pRosen->onEkiErase( idx ) ; 
			}
		}
	}
	// --------------------------------	
	return iRv ;
}

int CentDedEkiCont::set( const CentDedEki& element , int iIndex ) 
{
	int iRv = 0 ; 
	if ( iIndex == INT_MAX )
	{
		iIndex = size() - 1 ;
	}

	if ( iRv >= 0 )
	{
		iRv = setable( element , iIndex ) ;
	}
	if ( iRv >= 0 )
	{
		iRv = super::set( element ,  iIndex ) ;
	}
	//m_iIDのセット、現在の値が0以上の場合は、ダブりがないかをチェック、
	//重複する場合は空いている値を割り当て
	//0未満の場合は、0以上で空いている値を割り当て
	if (iRv >= 0)
	{
		if (element.getID() < 0)
		{
			bool bExist;
			int iNewID;
			for (iNewID = 0; iNewID < INT_MAX; iNewID++)
			{
				bExist = false;
				for (int iEkiIndex = 0; iEkiIndex < size() && !bExist; iEkiIndex++)
				{
					if (get(iEkiIndex).getID() == iNewID && iEkiIndex != iIndex)
					{
						bExist = true;
					}
				}
				if (!bExist)
				{
					break;
				}
			}
			//bExistがfalseのままだった場合、forから抜け、iNewIDをIDとしてセットする。
			getMuPtr()->get(iIndex)->setID(iNewID);
		}
		else
		{
			bool bExist = false;
			for (int iEkiIndex = 0; iEkiIndex < size() && !bExist; iEkiIndex++)
			{
				if (get(iEkiIndex).getID() == element.getID() && iEkiIndex != iIndex)
				{
					bExist = true;
				}
			}
			//bExistがfalseのままなら、被っていないので、そのまま。
			//trueの場合被っているので、新しいIDを付与する
			if (bExist)
			{
				int iNewID;
				for (iNewID = 0; iNewID < INT_MAX; iNewID++)
				{
					bExist = false;
					for (int iEkiIndex = 0; iEkiIndex < size() && !bExist; iEkiIndex++)
					{
						if (get(iEkiIndex).getID() == iNewID && iEkiIndex != iIndex)
						{
							bExist = true;
						}
					}
					if (!bExist)
					{
						break;
					}
				}
				getMuPtr()->get(iIndex)->setID(iNewID);
			}
		}
	}
	return iRv ; 
}

	// ********************************
	//@name CentDedEkiCont-操作
	// ********************************

int CentDedEkiCont::setable( const CentDedEki& element , int iIndex )const
{
	int iRv = 0 ;
	if ( iIndex == INT_MAX )
	{
		iIndex = size() - 1 ;
	}
	return iRv;
}

int  CentDedEkiCont::getIndex(const CentDedEki* element)const
{
	const Mu<const CentDedEki*>* pMu = getMuPtr();
	for (int idx = 0; idx < pMu->size(); idx++) {
		if (pMu->get(idx) == element) { return idx; }
	}
	return -1;
}






int CentDedEkiCont::EkiIndexOfEkiOrder(
	ERessyahoukou eRessyahoukou, int iEkiOrder)const
{
	int iRv = iEkiOrder;
	if (eRessyahoukou == Ressyahoukou_Nobori) {
		iRv = size() - 1 - iEkiOrder;
	}
	return (iRv);
}
int CentDedEkiCont::EkiOrderOfEkiIndex(
	ERessyahoukou eRessyahoukou, int iEkiIndex)const
{
	int iRv = iEkiIndex;
	if (eRessyahoukou == Ressyahoukou_Nobori) {
		iRv = size() - 1 - iEkiIndex;
	}
	return (iRv);
}

int CentDedEkiCont::EkiIndexOfEkiID(int iEkiID) const
{
	int iRv = -1;
	for (int idx = 0; idx < size(); idx++)
	{
		if (get(idx).getID() == iEkiID)
		{
			iRv = idx;
		}
	}
	return iRv;
}

void CentDedEkiCont::onEkiInsert(int iEkiIndex)
{
	for (int idx = 0; idx < size(); idx++)
	{
		getMuPtr()->get(idx)->onEkiInsert(iEkiIndex, size());
	}
	if (iEkiIndex == 0 && size() >= 2)
	{
		CentDedEki* pEki = getMuPtr()->get(1);
		if (pEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku)
		{
			for (int idx = 2; idx < size(); idx++)
			{
				if (getMuPtr()->get(idx)->getBrunchCoreEkiIndex() == 1)
				{
					pEki->setEkijikokukeisiki(CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku);
				}
			}
		}
	}
	if (iEkiIndex == size()-1 && size() >= 2)
	{
		CentDedEki* pEki = getMuPtr()->get(size() - 2);
		if (pEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku)
		{
			for (int idx = 0; idx < size()-2; idx++)
			{
				if (getMuPtr()->get(idx)->getBrunchCoreEkiIndex() == size() - 2)
				{
					pEki->setEkijikokukeisiki(CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku);
				}
			}
		}
	}
}

void CentDedEkiCont::onEkiErase(int iEkiIndex)
{
	for (int idx = 0; idx < size(); idx++)
	{
		getMuPtr()->get(idx)->onEkiErase(iEkiIndex);
	}
}

bool CentDedEkiCont::adjustBrunchLoopByBrunchEdit(int iEkiIndex, 
	int iBrunchCoreEkiIndex, deque<int>& iEkiIndexBrunchOriginSide,
	deque<int>& iEkiIndexLoop, deque<int>& iEkiIndexBrunchTerminalSide,
	vector<int> &iOuterTerminalEkimeiMap)
{
	int iPosition = getEkiIndexBrunchLoop(
		iEkiIndex,
		iEkiIndexBrunchOriginSide,
		iEkiIndexLoop,
		iEkiIndexBrunchTerminalSide);

	CentDedEki* pCentDedEkiThis = getMuPtr()->get(iEkiIndex);
	CentDedEki* pCentDedEkiCore = getMuPtr()->get(iBrunchCoreEkiIndex);

	//番線設定の統一を行う。原則基幹駅側優先。
	CentDedEkiTrack2Cont* pCentDedEkiTrack2ContThis = pCentDedEkiThis->getEkiTrack2Cont();
	CentDedEkiTrack2Cont* pCentDedEkiTrack2ContCore = pCentDedEkiCore->getEkiTrack2Cont();
	int iCompareResultEkiTrack2 = pCentDedEkiTrack2ContCore->compareEkiTrack2(pCentDedEkiTrack2ContThis);
	if (iCompareResultEkiTrack2 > 0)
	{
		//基幹駅との番線＆主本線設定で、この駅に上書きします。
		//在線表非表示設定は、追加される分をfalseで埋めます。
		for (int iEkiTrack2Index = 0; iEkiTrack2Index < pCentDedEkiTrack2ContThis->size(); iEkiTrack2Index++)
		{
			pCentDedEkiTrack2ContThis->set(pCentDedEkiTrack2ContCore->get(iEkiTrack2Index), iEkiTrack2Index);
		}
		for (int iEkiTrack2Index = pCentDedEkiTrack2ContThis->size();
			iEkiTrack2Index < pCentDedEkiTrack2ContCore->size(); iEkiTrack2Index++)
		{
			pCentDedEkiTrack2ContThis->insert(pCentDedEkiTrack2ContCore->get(iEkiTrack2Index), INT_MAX);
			pCentDedEkiThis->addDiagramTrackOmit(false);
		}
	}
	else if (iCompareResultEkiTrack2 < 0)
	{
		//基幹駅の番線情報をこの駅にコピーした上で、
		//この駅の番線のうち、基幹駅の番線数を超える分を、基幹駅及び他の派生駅・連結している起点・終点駅にに追加します。
		//在線表非表示設定は、追加される分をfalseで埋めます。
		for (int iEkiTrack2Index = 0; iEkiTrack2Index < pCentDedEkiTrack2ContCore->size(); iEkiTrack2Index++)
		{
			pCentDedEkiTrack2ContThis->set(pCentDedEkiTrack2ContCore->get(iEkiTrack2Index), iEkiTrack2Index);
		}
		for (int iEkiTrack2Index = pCentDedEkiTrack2ContCore->size()
			; iEkiTrack2Index < pCentDedEkiTrack2ContThis->size(); iEkiTrack2Index++)
		{
			for (int idx = 0; idx < (int)iEkiIndexBrunchOriginSide.size(); idx++)
			{
				if (iEkiIndexBrunchOriginSide[idx] == iEkiIndex)
				{
					continue;
				}
				CentDedEkiTrack2Cont* pCentDedEkiTrack2ContTarget =
					getMuPtr()->get(iEkiIndexBrunchOriginSide[idx])->getEkiTrack2Cont();
				pCentDedEkiTrack2ContTarget->insert(pCentDedEkiTrack2ContThis->get(iEkiTrack2Index), INT_MAX);
				getMuPtr()->get(iEkiIndexBrunchOriginSide[idx])->addDiagramTrackOmit(false);
			}
			for (int idx = 0; idx < (int)iEkiIndexLoop.size(); idx++)
			{
				CentDedEkiTrack2Cont* pCentDedEkiTrack2ContTarget =
					getMuPtr()->get(iEkiIndexLoop[idx])->getEkiTrack2Cont();
				pCentDedEkiTrack2ContTarget->insert(pCentDedEkiTrack2ContThis->get(iEkiTrack2Index), INT_MAX);
				getMuPtr()->get(iEkiIndexLoop[idx])->addDiagramTrackOmit(false);
			}
			for (int idx = 0; idx < (int)iEkiIndexBrunchTerminalSide.size(); idx++)
			{
				if (iEkiIndexBrunchTerminalSide[idx] == iEkiIndex)
				{
					continue;
				}
				CentDedEkiTrack2Cont* pCentDedEkiTrack2ContTarget =
					getMuPtr()->get(iEkiIndexBrunchTerminalSide[idx])->getEkiTrack2Cont();
				pCentDedEkiTrack2ContTarget->insert(pCentDedEkiTrack2ContThis->get(iEkiTrack2Index), INT_MAX);
				getMuPtr()->get(iEkiIndexBrunchTerminalSide[idx])->addDiagramTrackOmit(false);
			}
		}
	}
	//主本線設定を基幹駅からこの駅にコピーします
	int iCompareResultEki = pCentDedEkiThis->compareMainTrack(pCentDedEkiCore);
	if (iCompareResultEki == 3)
	{
		pCentDedEkiThis->setDownMain(pCentDedEkiCore->getDownMain());
		pCentDedEkiThis->setUpMain(pCentDedEkiCore->getUpMain());
	}
	else if (iCompareResultEki == 2)
	{
		pCentDedEkiThis->setUpMain(pCentDedEkiCore->getUpMain());
	}
	else if (iCompareResultEki == 1)
	{
		pCentDedEkiThis->setDownMain(pCentDedEkiCore->getDownMain());
	}

	//路線外発着駅の調整を行います。
	//(1)iOuterTerminalEkimeiMapの初期化を行う
	for (int idx = 0; idx < pCentDedEkiThis->getOuterTerminalEkimeiCount(); idx++)
	{
		iOuterTerminalEkimeiMap.push_back(idx);
	}

	//(2)派生駅と基幹駅の比較を行い、不一致(!=0)の場合は、融合作業を行う
	//まず、派生駅の中に、基幹駅にないものがあったら、それを基幹駅側に追加する。
	//次に、派生駅を基幹駅の要素で上書きする。この上書きは、限定一致(1)の場合も行う
	int iCompareResultOuterTerminal = pCentDedEkiThis->compareOuterTerminal(pCentDedEkiCore);

	//iCompareResultOuterTerminalが-1,2,3の時に、追加作業を行う
	for (int idx = 0; idx < pCentDedEkiThis->getOuterTerminalEkimeiCount() && 
		(iCompareResultOuterTerminal >= 2 || iCompareResultOuterTerminal <= -1); idx++)
	{
		OuterTerminal sOuterTerminal = pCentDedEkiThis->getOuterTerminal(idx);
		int iOuterTerminalExsit = pCentDedEkiCore->searchOuterTerminalEkimei(sOuterTerminal.OuterTerminalEkimei);
		if (iOuterTerminalExsit < 0)
		{
			for (int idx = 0; idx < (int)iEkiIndexBrunchOriginSide.size(); idx++)
			{
				if (iEkiIndexBrunchOriginSide[idx] == iEkiIndex)
				{
					continue;
				}
				CentDedEki* pCentDedEkiTarget =
					getMuPtr()->get(iEkiIndexBrunchOriginSide[idx]);
				pCentDedEkiTarget->insertOuterTerminalEkimei(sOuterTerminal, INT_MAX);
			}
			for (int idx = 0; idx < (int)iEkiIndexLoop.size(); idx++)
			{
				CentDedEki* pCentDedEkiTarget =
					getMuPtr()->get(iEkiIndexLoop[idx]);
				pCentDedEkiTarget->insertOuterTerminalEkimei(sOuterTerminal, INT_MAX);
			}
			for (int idx = 0; idx < (int)iEkiIndexBrunchTerminalSide.size(); idx++)
			{
				if (iEkiIndexBrunchTerminalSide[idx] == iEkiIndex)
				{
					continue;
				}
				CentDedEki* pCentDedEkiTarget =
					getMuPtr()->get(iEkiIndexBrunchTerminalSide[idx]);
				pCentDedEkiTarget->insertOuterTerminalEkimei(sOuterTerminal, INT_MAX);
			}
			iOuterTerminalEkimeiMap[idx] = pCentDedEkiCore->getOuterTerminalEkimeiCount() - 1;
		}
		else
		{
			iOuterTerminalEkimeiMap[idx] = iOuterTerminalExsit;
		}
	}

	for (int idx = 0; idx < pCentDedEkiCore->getOuterTerminalEkimeiCount() && iCompareResultOuterTerminal != 0; idx++)
	{
		if (idx < pCentDedEkiThis->getOuterTerminalEkimeiCount())
		{
			pCentDedEkiThis->setOuterTerminalEkimei(pCentDedEkiCore->getOuterTerminal(idx), idx);
		}
		else
		{
			pCentDedEkiThis->insertOuterTerminalEkimei(pCentDedEkiCore->getOuterTerminal(idx), INT_MAX);
		}
	}

	/**
		交差支障チェックルールの調整を行う
		(1)This側のルールの路線外発着駅Indexを補正する
		(2)両側のルールを一つにまとめる(派生駅のルールを基幹駅の後ろにつなげ、基幹駅のルールを全駅にコピーする)
	*/

	for (int idx = 0; idx < pCentDedEkiThis->getCrossingCheckRuleSize(); idx++)
	{
		CrossingCheckRule CrossingCheckRuleTemp = pCentDedEkiThis->getCrossingCheckRule(idx);

		for (int idxbf = 0; idxbf < (int)CrossingCheckRuleTemp.BeforeFromTrackContentCont.size(); idxbf++)
		{
			if (CrossingCheckRuleTemp.BeforeFromTrackContentCont[idxbf].eTrackType == ETrackType::TrackType_Outer)
			{
				if (iOuterTerminalEkimeiMap[CrossingCheckRuleTemp.BeforeFromTrackContentCont[idxbf].iTrackIndex] != CrossingCheckRuleTemp.BeforeFromTrackContentCont[idxbf].iTrackIndex)
				{
					CrossingCheckRuleTemp.BeforeFromTrackContentCont[idxbf].iTrackIndex = iOuterTerminalEkimeiMap[CrossingCheckRuleTemp.BeforeFromTrackContentCont[idxbf].iTrackIndex];
				}
			}
		}
		for (int idxbt = 0; idxbt < (int)CrossingCheckRuleTemp.BeforeToTrackContentCont.size(); idxbt++)
		{
			if (CrossingCheckRuleTemp.BeforeToTrackContentCont[idxbt].eTrackType == ETrackType::TrackType_Outer)
			{
				if (iOuterTerminalEkimeiMap[CrossingCheckRuleTemp.BeforeToTrackContentCont[idxbt].iTrackIndex] != CrossingCheckRuleTemp.BeforeToTrackContentCont[idxbt].iTrackIndex)
				{
					CrossingCheckRuleTemp.BeforeToTrackContentCont[idxbt].iTrackIndex = iOuterTerminalEkimeiMap[CrossingCheckRuleTemp.BeforeToTrackContentCont[idxbt].iTrackIndex];
				}
			}
		}
		for (int idxaf = 0; idxaf < (int)CrossingCheckRuleTemp.AfterFromTrackContentCont.size(); idxaf++)
		{
			if (CrossingCheckRuleTemp.AfterFromTrackContentCont[idxaf].eTrackType == ETrackType::TrackType_Outer)
			{
				if (iOuterTerminalEkimeiMap[CrossingCheckRuleTemp.AfterFromTrackContentCont[idxaf].iTrackIndex] != CrossingCheckRuleTemp.AfterFromTrackContentCont[idxaf].iTrackIndex)
				{
					CrossingCheckRuleTemp.AfterFromTrackContentCont[idxaf].iTrackIndex = iOuterTerminalEkimeiMap[CrossingCheckRuleTemp.AfterFromTrackContentCont[idxaf].iTrackIndex];
				}
			}
		}
		for (int idxat = 0; idxat < (int)CrossingCheckRuleTemp.AfterToTrackContentCont.size(); idxat++)
		{
			if (CrossingCheckRuleTemp.AfterToTrackContentCont[idxat].eTrackType == ETrackType::TrackType_Outer)
			{
				if (iOuterTerminalEkimeiMap[CrossingCheckRuleTemp.AfterToTrackContentCont[idxat].iTrackIndex] != CrossingCheckRuleTemp.AfterToTrackContentCont[idxat].iTrackIndex)
				{
					CrossingCheckRuleTemp.AfterToTrackContentCont[idxat].iTrackIndex = iOuterTerminalEkimeiMap[CrossingCheckRuleTemp.AfterToTrackContentCont[idxat].iTrackIndex];
				}
			}
		}

		pCentDedEkiThis->setCrossingCheckRule(CrossingCheckRuleTemp, idx);
	}

	pCentDedEkiCore->addCrossingCheckRule(pCentDedEkiThis->getCrossingCheckRuleCont());

	for (int idx = 0; idx < (int)iEkiIndexBrunchOriginSide.size(); idx++)
	{
		CentDedEki* pCentDedEkiTarget = getMuPtr()->get(iEkiIndexBrunchOriginSide[idx]);
		pCentDedEkiTarget->setCrossingCheckRule(pCentDedEkiCore->getCrossingCheckRuleCont());
	}
	for (int idx = 0; idx < (int)iEkiIndexLoop.size(); idx++)
	{
		if (iEkiIndexLoop[idx] == iBrunchCoreEkiIndex)
		{
			continue;
		}
		CentDedEki* pCentDedEkiTarget = getMuPtr()->get(iEkiIndexLoop[idx]);
		pCentDedEkiTarget->setCrossingCheckRule(pCentDedEkiCore->getCrossingCheckRuleCont());
	}
	for (int idx = 0; idx < (int)iEkiIndexBrunchTerminalSide.size(); idx++)
	{
		CentDedEki* pCentDedEkiTarget = getMuPtr()->get(iEkiIndexBrunchTerminalSide[idx]);
		pCentDedEkiTarget->setCrossingCheckRule(pCentDedEkiCore->getCrossingCheckRuleCont());
	}

	return iPosition == INT_MIN;
}

int CentDedEkiCont::adjustBrunchLoopByLoopEdit(int iEkiIndex, 
	int iLoopOriginEkiIndex, deque<int>& iEkiIndexBrunchOriginSide,
	deque<int>& iEkiIndexLoop, deque<int>& iEkiIndexBrunchTerminalSide,
	vector<int> &iOuterTerminalEkimeiMap)
{
	int iPosition = getEkiIndexBrunchLoop(
		iEkiIndex,
		iEkiIndexBrunchOriginSide,
		iEkiIndexLoop,
		iEkiIndexBrunchTerminalSide);

	CentDedEki* pCentDedEkiThis = getMuPtr()->get(iEkiIndex);
	CentDedEki* pCentDedEkiOrigin = getMuPtr()->get(iLoopOriginEkiIndex);

	//番線設定の統一を行う。原則起点駅側優先。
	CentDedEkiTrack2Cont* pCentDedEkiTrack2ContThis = pCentDedEkiThis->getEkiTrack2Cont();
	CentDedEkiTrack2Cont* pCentDedEkiTrack2ContOrigin = pCentDedEkiOrigin->getEkiTrack2Cont();
	int iCompareResultEkiTrack2 = pCentDedEkiTrack2ContOrigin->compareEkiTrack2(pCentDedEkiTrack2ContThis);
	if (iCompareResultEkiTrack2 > 0)
	{
		//起点駅との番線＆主本線設定で、この駅に上書きします。
		//また、この駅より下流の駅にも上書きします
		//在線表非表示設定は、追加される分をfalseで埋めます。

		//for (int idxl = 1; idxl < (int)iEkiIndexLoop.size(); idxl++)
		for (int idxl = iPosition; idxl < (int)iEkiIndexLoop.size(); idxl++)
		{
			//if (iEkiIndexLoop[idxl] >= iEkiIndex)
			//{
			CentDedEkiTrack2Cont* pCentDedEkiTrack2ContTarget = getMuPtr()->get(iEkiIndexLoop[idxl])->getEkiTrack2Cont();
			for (int iEkiTrack2Index = 0; iEkiTrack2Index < pCentDedEkiTrack2ContTarget->size(); iEkiTrack2Index++)
			{
				pCentDedEkiTrack2ContTarget->set(pCentDedEkiTrack2ContOrigin->get(iEkiTrack2Index), iEkiTrack2Index);
			}
			for (int iEkiTrack2Index = pCentDedEkiTrack2ContTarget->size();
				iEkiTrack2Index < pCentDedEkiTrack2ContOrigin->size(); iEkiTrack2Index++)
			{
				pCentDedEkiTrack2ContTarget->insert(pCentDedEkiTrack2ContOrigin->get(iEkiTrack2Index), INT_MAX);
				getMuPtr()->get(iEkiIndexLoop[idxl])->addDiagramTrackOmit(false);

			}
			//}
		}
		for (int idxbd = 0; idxbd < (int)iEkiIndexBrunchTerminalSide.size(); idxbd++)
		{
			CentDedEkiTrack2Cont* pCentDedEkiTrack2ContTarget = getMuPtr()->get(iEkiIndexBrunchTerminalSide[idxbd])->getEkiTrack2Cont();
			for (int iEkiTrack2Index = 0; iEkiTrack2Index < pCentDedEkiTrack2ContTarget->size(); iEkiTrack2Index++)
			{
				pCentDedEkiTrack2ContTarget->set(pCentDedEkiTrack2ContOrigin->get(iEkiTrack2Index), iEkiTrack2Index);
			}
			for (int iEkiTrack2Index = pCentDedEkiTrack2ContTarget->size();
				iEkiTrack2Index < pCentDedEkiTrack2ContOrigin->size(); iEkiTrack2Index++)
			{
				pCentDedEkiTrack2ContTarget->insert(pCentDedEkiTrack2ContOrigin->get(iEkiTrack2Index), INT_MAX);
				getMuPtr()->get(iEkiIndexBrunchTerminalSide[idxbd])->addDiagramTrackOmit(false);
			}
		}
	}
	else if (iCompareResultEkiTrack2 < 0)
	{
		//起点駅の番線情報をこの駅及び下流の駅にコピーした上で、
		//この駅の番線のうち、起点駅の番線数を超える分を、起点駅及びその上流の駅に追加します。
		//在線表非表示設定は、追加される分をfalseで埋めます。

		for (int iEkiTrack2Index = 0; iEkiTrack2Index < pCentDedEkiTrack2ContOrigin->size(); iEkiTrack2Index++)
		{
			for (int idxl = iPosition; idxl < (int)iEkiIndexLoop.size(); idxl++)
			{
				//if (iEkiIndexLoop[idxl] >= iEkiIndex)
				//{
				CentDedEkiTrack2Cont* pCentDedEkiTrack2ContTarget =
					getMuPtr()->get(iEkiIndexLoop[idxl])->getEkiTrack2Cont();
				pCentDedEkiTrack2ContTarget->set(pCentDedEkiTrack2ContOrigin->get(iEkiTrack2Index), iEkiTrack2Index);
				//}
			}
			for (int idxbd = 0; idxbd < (int)iEkiIndexBrunchTerminalSide.size(); idxbd++)
			{
				CentDedEkiTrack2Cont* pCentDedEkiTrack2ContTarget =
					getMuPtr()->get(iEkiIndexBrunchTerminalSide[idxbd])->getEkiTrack2Cont();
				pCentDedEkiTrack2ContTarget->set(pCentDedEkiTrack2ContOrigin->get(iEkiTrack2Index), iEkiTrack2Index);
			}
		}

		for (int iEkiTrack2Index = pCentDedEkiTrack2ContOrigin->size()
			; iEkiTrack2Index < pCentDedEkiTrack2ContThis->size(); iEkiTrack2Index++)
		{
			for (int idxl = 0; idxl < iPosition; idxl++)
			{
				//if (iEkiIndexLoop[idxl] <= iLoopOriginEkiIndex)
				//{
				CentDedEkiTrack2Cont* pCentDedEkiTrack2ContTarget =
					getMuPtr()->get(iEkiIndexLoop[idxl])->getEkiTrack2Cont();
				pCentDedEkiTrack2ContTarget->insert(pCentDedEkiTrack2ContThis->get(iEkiTrack2Index), INT_MAX);
				getMuPtr()->get(iEkiIndexLoop[idxl])->addDiagramTrackOmit(false);

				//}
			}
			for (int idxbu = 0; idxbu < (int)iEkiIndexBrunchOriginSide.size(); idxbu++)
			{
				CentDedEkiTrack2Cont* pCentDedEkiTrack2ContTarget =
					getMuPtr()->get(iEkiIndexBrunchOriginSide[idxbu])->getEkiTrack2Cont();
				pCentDedEkiTrack2ContTarget->insert(pCentDedEkiTrack2ContThis->get(iEkiTrack2Index), INT_MAX);
				getMuPtr()->get(iEkiIndexBrunchOriginSide[idxbu])->addDiagramTrackOmit(false);
			}
		}
	}
	//主本線設定を起点駅からこの駅及び下流駅にコピーします
	int iCompareResultEki = pCentDedEkiThis->compareMainTrack(pCentDedEkiOrigin);
	if (iCompareResultEki == 3)
	{
		for (int idxl = iPosition; idxl < (int)iEkiIndexLoop.size(); idxl++)
		{
			//if (iEkiIndexLoop[idxl] >= iEkiIndex)
			//{
			CentDedEki* pCentDedEkiTarget = getMuPtr()->get(iEkiIndexLoop[idxl]);
			pCentDedEkiTarget->setDownMain(pCentDedEkiOrigin->getDownMain());
			pCentDedEkiTarget->setUpMain(pCentDedEkiOrigin->getUpMain());
			//}
		}
		for (int idxbd = 0; idxbd < (int)iEkiIndexBrunchTerminalSide.size(); idxbd++)
		{
			CentDedEki* pCentDedEkiTarget = getMuPtr()->get(iEkiIndexBrunchTerminalSide[idxbd]);
			pCentDedEkiTarget->setDownMain(pCentDedEkiOrigin->getDownMain());
			pCentDedEkiTarget->setUpMain(pCentDedEkiOrigin->getUpMain());
		}
	}
	else if (iCompareResultEki == 2)
	{
		for (int idxl = iPosition; idxl < (int)iEkiIndexLoop.size(); idxl++)
		{
			//if (iEkiIndexLoop[idxl] >= iEkiIndex)
			//{
			CentDedEki* pCentDedEkiTarget = getMuPtr()->get(iEkiIndexLoop[idxl]);
			pCentDedEkiTarget->setUpMain(pCentDedEkiOrigin->getUpMain());
			//}
		}
		for (int idxbd = 0; idxbd < (int)iEkiIndexBrunchTerminalSide.size(); idxbd++)
		{
			CentDedEki* pCentDedEkiTarget = getMuPtr()->get(iEkiIndexBrunchTerminalSide[idxbd]);
			pCentDedEkiTarget->setUpMain(pCentDedEkiOrigin->getUpMain());
		}
	}
	else if (iCompareResultEki == 1)
	{
		for (int idxl = iPosition; idxl < (int)iEkiIndexLoop.size(); idxl++)
		{
			//if (iEkiIndexLoop[idxl] >= iEkiIndex)
			//{
			CentDedEki* pCentDedEkiTarget = getMuPtr()->get(iEkiIndexLoop[idxl]);
			pCentDedEkiTarget->setDownMain(pCentDedEkiOrigin->getDownMain());
			//}
		}
		for (int idxbd = 0; idxbd < (int)iEkiIndexBrunchTerminalSide.size(); idxbd++)
		{
			CentDedEki* pCentDedEkiTarget = getMuPtr()->get(iEkiIndexBrunchTerminalSide[idxbd]);
			pCentDedEkiTarget->setDownMain(pCentDedEkiOrigin->getDownMain());
		}
	}

	//路線外発着駅の調整を行います。
	//(1)iOuterTerminalEkimeiMapの初期化を行う
	for (int idx = 0; idx < pCentDedEkiThis->getOuterTerminalEkimeiCount(); idx++)
	{
		iOuterTerminalEkimeiMap.push_back(idx);
	}
	//(2)起点駅と終点駅の比較を行い、不一致(!=0)の場合は、融合作業を行う
	//まず、終点駅の中に、起点駅にないものがあったら、それを起点駅側に追加する。
	//次に、終点駅側を起点駅の要素で上書きする。この上書きは、限定一致(1)の場合も行う
	int iCompareResultOuterTerminal = pCentDedEkiThis->compareOuterTerminal(pCentDedEkiOrigin);

	//iCompareResultOuterTerminalが-1,2,3の時に、追加作業を行う
	for (int idx = 0; idx < pCentDedEkiThis->getOuterTerminalEkimeiCount() && 
		(iCompareResultOuterTerminal >= 2 || iCompareResultOuterTerminal <= -1); idx++)
	{
		OuterTerminal sOuterTerminal = pCentDedEkiThis->getOuterTerminal(idx);
		int iOuterTerminalExsit = pCentDedEkiOrigin->searchOuterTerminalEkimei(sOuterTerminal.OuterTerminalEkimei);
		if (iOuterTerminalExsit < 0)
		{
			//起点駅およびそれより上流の駅に追加を行う
			for (int idxl = 0; idxl < iPosition; idxl++)
			{
				CentDedEki* pCentDedEkiTarget =
					getMuPtr()->get(iEkiIndexLoop[idxl]);
				pCentDedEkiTarget->insertOuterTerminalEkimei(sOuterTerminal, INT_MAX);
			}
			for (int idxbu = 0; idxbu < (int)iEkiIndexBrunchOriginSide.size(); idxbu++)
			{
				CentDedEki* pCentDedEkiTarget =
					getMuPtr()->get(iEkiIndexBrunchOriginSide[idxbu]);
				pCentDedEkiTarget->insertOuterTerminalEkimei(sOuterTerminal, INT_MAX);
			}
			iOuterTerminalEkimeiMap[idx] = pCentDedEkiOrigin->getOuterTerminalEkimeiCount() - 1;
		}
		else
		{
			iOuterTerminalEkimeiMap[idx] = iOuterTerminalExsit;
		}
	}

	for (int idx = 0; idx < pCentDedEkiOrigin->getOuterTerminalEkimeiCount() && iCompareResultOuterTerminal != 0; idx++)
	{
		if (idx < pCentDedEkiThis->getOuterTerminalEkimeiCount())
		{
			for (int idxl = iPosition; idxl < (int)iEkiIndexLoop.size(); idxl++)
			{
				CentDedEki* pCentDedEkiTarget = getMuPtr()->get(iEkiIndexLoop[idxl]);
				pCentDedEkiTarget->setOuterTerminalEkimei(pCentDedEkiOrigin->getOuterTerminal(idx), idx);
			}
			for (int idxbd = 0; idxbd < (int)iEkiIndexBrunchTerminalSide.size(); idxbd++)
			{
				CentDedEki* pCentDedEkiTarget = getMuPtr()->get(iEkiIndexBrunchTerminalSide[idxbd]);
				pCentDedEkiTarget->setOuterTerminalEkimei(pCentDedEkiOrigin->getOuterTerminal(idx), idx);
			}
		}
		else
		{
			for (int idxl = iPosition; idxl < (int)iEkiIndexLoop.size(); idxl++)
			{
				CentDedEki* pCentDedEkiTarget = getMuPtr()->get(iEkiIndexLoop[idxl]);
				pCentDedEkiTarget->insertOuterTerminalEkimei(pCentDedEkiOrigin->getOuterTerminal(idx), INT_MAX);
			}
			for (int idxbd = 0; idxbd < (int)iEkiIndexBrunchTerminalSide.size(); idxbd++)
			{
				CentDedEki* pCentDedEkiTarget = getMuPtr()->get(iEkiIndexBrunchTerminalSide[idxbd]);
				pCentDedEkiTarget->insertOuterTerminalEkimei(pCentDedEkiOrigin->getOuterTerminal(idx), INT_MAX);
			}
		}
	}

	/**
		交差支障チェックルールの調整を行う
		(1)This側(ただし、後でコピーするので、終点駅だけでよい)のルールの路線外発着駅Indexを補正する
		(2)両側のルールを一つにまとめる(終点駅のルールを起点駅の後ろにつなげ、起点駅のルールを全駅にコピーする)
	*/

	for (int idx = 0; idx < pCentDedEkiThis->getCrossingCheckRuleSize(); idx++)
	{
		CrossingCheckRule CrossingCheckRuleTemp = pCentDedEkiThis->getCrossingCheckRule(idx);

		for (int idxbf = 0; idxbf < (int)CrossingCheckRuleTemp.BeforeFromTrackContentCont.size(); idxbf++)
		{
			if (CrossingCheckRuleTemp.BeforeFromTrackContentCont[idxbf].eTrackType == ETrackType::TrackType_Outer)
			{
				if (iOuterTerminalEkimeiMap[CrossingCheckRuleTemp.BeforeFromTrackContentCont[idxbf].iTrackIndex] != CrossingCheckRuleTemp.BeforeFromTrackContentCont[idxbf].iTrackIndex)
				{
					CrossingCheckRuleTemp.BeforeFromTrackContentCont[idxbf].iTrackIndex = iOuterTerminalEkimeiMap[CrossingCheckRuleTemp.BeforeFromTrackContentCont[idxbf].iTrackIndex];
				}
			}
		}
		for (int idxbt = 0; idxbt < (int)CrossingCheckRuleTemp.BeforeToTrackContentCont.size(); idxbt++)
		{
			if (CrossingCheckRuleTemp.BeforeToTrackContentCont[idxbt].eTrackType == ETrackType::TrackType_Outer)
			{
				if (iOuterTerminalEkimeiMap[CrossingCheckRuleTemp.BeforeToTrackContentCont[idxbt].iTrackIndex] != CrossingCheckRuleTemp.BeforeToTrackContentCont[idxbt].iTrackIndex)
				{
					CrossingCheckRuleTemp.BeforeToTrackContentCont[idxbt].iTrackIndex = iOuterTerminalEkimeiMap[CrossingCheckRuleTemp.BeforeToTrackContentCont[idxbt].iTrackIndex];
				}
			}
		}
		for (int idxaf = 0; idxaf < (int)CrossingCheckRuleTemp.AfterFromTrackContentCont.size(); idxaf++)
		{
			if (CrossingCheckRuleTemp.AfterFromTrackContentCont[idxaf].eTrackType == ETrackType::TrackType_Outer)
			{
				if (iOuterTerminalEkimeiMap[CrossingCheckRuleTemp.AfterFromTrackContentCont[idxaf].iTrackIndex] != CrossingCheckRuleTemp.AfterFromTrackContentCont[idxaf].iTrackIndex)
				{
					CrossingCheckRuleTemp.AfterFromTrackContentCont[idxaf].iTrackIndex = iOuterTerminalEkimeiMap[CrossingCheckRuleTemp.AfterFromTrackContentCont[idxaf].iTrackIndex];
				}
			}
		}
		for (int idxat = 0; idxat < (int)CrossingCheckRuleTemp.AfterToTrackContentCont.size(); idxat++)
		{
			if (CrossingCheckRuleTemp.AfterToTrackContentCont[idxat].eTrackType == ETrackType::TrackType_Outer)
			{
				if (iOuterTerminalEkimeiMap[CrossingCheckRuleTemp.AfterToTrackContentCont[idxat].iTrackIndex] != CrossingCheckRuleTemp.AfterToTrackContentCont[idxat].iTrackIndex)
				{
					CrossingCheckRuleTemp.AfterToTrackContentCont[idxat].iTrackIndex = iOuterTerminalEkimeiMap[CrossingCheckRuleTemp.AfterToTrackContentCont[idxat].iTrackIndex];
				}
			}
		}

		pCentDedEkiThis->setCrossingCheckRule(CrossingCheckRuleTemp, idx);
	}

	pCentDedEkiOrigin->addCrossingCheckRule(pCentDedEkiThis->getCrossingCheckRuleCont());

	for (int idx = 0; idx < (int)iEkiIndexBrunchOriginSide.size(); idx++)
	{
		CentDedEki* pCentDedEkiTarget = getMuPtr()->get(iEkiIndexBrunchOriginSide[idx]);
		pCentDedEkiTarget->setCrossingCheckRule(pCentDedEkiOrigin->getCrossingCheckRuleCont());
	}
	for (int idx = 0; idx < (int)iEkiIndexLoop.size(); idx++)
	{
		if (iEkiIndexLoop[idx] == iLoopOriginEkiIndex)
		{
			continue;
		}
		CentDedEki* pCentDedEkiTarget = getMuPtr()->get(iEkiIndexLoop[idx]);
		pCentDedEkiTarget->setCrossingCheckRule(pCentDedEkiOrigin->getCrossingCheckRuleCont());
	}
	for (int idx = 0; idx < (int)iEkiIndexBrunchTerminalSide.size(); idx++)
	{
		CentDedEki* pCentDedEkiTarget = getMuPtr()->get(iEkiIndexBrunchTerminalSide[idx]);
		pCentDedEkiTarget->setCrossingCheckRule(pCentDedEkiOrigin->getCrossingCheckRuleCont());
	}

	return iPosition;
}

int CentDedEkiCont::getEkiIndexBrunchLoop(
	int iEkiIndex, deque<int>& iEkiIndexBrunchLoop)const
{	
	//編集駅のBrunchCore及びLoopOriginを基に、場合分け
	iEkiIndexBrunchLoop.push_back(iEkiIndex);
	const CentDedEki* pCentDedEkiThis = getMuPtr()->get(iEkiIndex);

	if (pCentDedEkiThis->getBrunchCoreEkiIndex() >= 0 &&
		pCentDedEkiThis->getBrunchCoreEkiIndex() > iEkiIndex)
	{
		//編集駅が、下方への派生駅の場合。基幹駅から下に繋がっている可能性あり
		int iEkiIndexCore = pCentDedEkiThis->getBrunchCoreEkiIndex();
		iEkiIndexBrunchLoop.push_back(iEkiIndexCore);
		for (int idxu = iEkiIndexCore - 1; idxu >= 0; idxu--)
		{
			if (idxu != iEkiIndex &&
				get(idxu).getBrunchCoreEkiIndex() == iEkiIndexCore)
			{
				iEkiIndexBrunchLoop.push_back(idxu);
			}
		}
		int idxl = iEkiIndexCore;
		bool bSearch;
		do
		{
			bSearch = false;
			for (int idxls = idxl + 1; idxls < size(); idxls++)
			{
				if (get(idxls).getLoopOriginEkiIndex() == idxl)
				{
					iEkiIndexBrunchLoop.push_back(idxls);
					idxl = idxls;
					bSearch = true;
					break;
				}
			}
		} while (bSearch);
		for (int idxd = idxl + 1; idxd < size(); idxd++)
		{
			if (get(idxd).getBrunchCoreEkiIndex() == idxl)
			{
				iEkiIndexBrunchLoop.push_back(idxd);
			}
		}
	}
	else if (pCentDedEkiThis->getBrunchCoreEkiIndex() >= 0 &&
		pCentDedEkiThis->getBrunchCoreEkiIndex() < iEkiIndex)
	{
		//編集駅が、上方への派生駅の場合。基幹駅から上につながっている可能性あり
		int iEkiIndexCore = pCentDedEkiThis->getBrunchCoreEkiIndex();
		iEkiIndexBrunchLoop.push_back(iEkiIndexCore);

		for (int idxd = iEkiIndexCore + 1; idxd < size(); idxd++)
		{
			if (idxd != iEkiIndex &&
				get(idxd).getBrunchCoreEkiIndex() == iEkiIndexCore)
			{
				iEkiIndexBrunchLoop.push_back(idxd);
			}
		}
		int idxl = iEkiIndexCore;
		while (get(idxl).getLoopOriginEkiIndex() >= 0)
		{
			iEkiIndexBrunchLoop.push_back(get(idxl).getLoopOriginEkiIndex());
			idxl = get(idxl).getLoopOriginEkiIndex();
		}
		for (int idxu = idxl - 1; idxu >= 0; idxu--)
		{
			if (get(idxu).getBrunchCoreEkiIndex() == idxl)
			{
				iEkiIndexBrunchLoop.push_back(idxu);
			}
		}
	}
	else if (pCentDedEkiThis->getLoopOriginEkiIndex() >= 0)
	{
		//編集駅が、終点駅の場合。下方からの始点駅OR基幹駅の可能性あり
		int iEkiIndexOrigin = pCentDedEkiThis->getLoopOriginEkiIndex();
		iEkiIndexBrunchLoop.push_back(iEkiIndexOrigin);

		//上方探索
		int idxl = iEkiIndexOrigin;
		while (get(idxl).getLoopOriginEkiIndex() >= 0)
		{
			iEkiIndexBrunchLoop.push_back(get(idxl).getLoopOriginEkiIndex());
			idxl = get(idxl).getLoopOriginEkiIndex();
		}
		for (int idxu = idxl - 1; idxu >= 0; idxu--)
		{
			if (get(idxu).getBrunchCoreEkiIndex() == idxl)
			{
				iEkiIndexBrunchLoop.push_back(idxu);
			}
		}

		//下方探索
		idxl = iEkiIndex;
		bool bSearch;
		do
		{
			bSearch = false;
			for (int idxls = idxl + 1; idxls < size(); idxls++)
			{
				if (get(idxls).getLoopOriginEkiIndex() == idxl)
				{
					iEkiIndexBrunchLoop.push_back(idxls);
					idxl = idxls;
					bSearch = true;
					break;
				}
			}
		} while (bSearch);
		for (int idxd = idxl + 1; idxd < size(); idxd++)
		{
			if (get(idxd).getBrunchCoreEkiIndex() == idxl)
			{
				iEkiIndexBrunchLoop.push_back(idxd);
			}
		}
	}
	else
	{
		//編集駅からは分岐駅設定・環状線設定がなされていない場合。基幹駅もしくは起点駅の可能性あり
		//上方探索
		for (int idxu = iEkiIndex - 1; idxu >= 0; idxu--)
		{
			if (get(idxu).getBrunchCoreEkiIndex() == iEkiIndex)
			{
				iEkiIndexBrunchLoop.push_back(idxu);
			}
		}

		//下方探索
		int idxl = iEkiIndex;
		bool bSearch;
		do
		{
			bSearch = false;
			for (int idxls = idxl + 1; idxls < size(); idxls++)
			{
				if (get(idxls).getLoopOriginEkiIndex() == idxl)
				{
					iEkiIndexBrunchLoop.push_back(idxls);
					idxl = idxls;
					bSearch = true;
					break;
				}
			}
		} while (bSearch);
		for (int idxd = idxl + 1; idxd < size(); idxd++)
		{
			if (get(idxd).getBrunchCoreEkiIndex() == idxl)
			{
				iEkiIndexBrunchLoop.push_back(idxd);
			}
		}
	}
	return (int)iEkiIndexBrunchLoop.size();
}

int CentDedEkiCont::searchEkiIndexBrunchLoop(
	int iEkiIndex, deque<int>& iEkiIndexBrunchOriginSide, 
	deque<int>& iEkiIndexLoop, deque<int>& iEkiIndexBrunchTerminalSide) const
{
	//編集駅のBrunchCore及びLoopOriginを基に、場合分け
	const CentDedEki* pCentDedEkiThis = getMuPtr()->get(iEkiIndex);

	if (pCentDedEkiThis->getBrunchCoreEkiIndex() >= 0 &&
		pCentDedEkiThis->getBrunchCoreEkiIndex() > iEkiIndex)
	{
		//編集駅が、起点方派生駅の場合。基幹駅から下に繋がっている可能性あり
		//iEkiIndexBrunchOriginSide.push_back(iEkiIndex);
		int iEkiIndexCore = pCentDedEkiThis->getBrunchCoreEkiIndex();
		iEkiIndexLoop.push_back(iEkiIndexCore);
		//for (int idxo = iEkiIndexCore - 1; idxo >= 0; idxo--)
		for (int idxo = 0; idxo < iEkiIndexCore; idxo++)
		{
			if (/*idxo != iEkiIndex &&*/
				get(idxo).getBrunchCoreEkiIndex() == iEkiIndexCore)
			{
				iEkiIndexBrunchOriginSide.push_back(idxo);
			}
		}
		int idxl = iEkiIndexCore;
		bool bSearch;
		do
		{
			bSearch = false;
			for (int idxls = idxl + 1; idxls < size(); idxls++)
			{
				if (get(idxls).getLoopOriginEkiIndex() == idxl)
				{
					iEkiIndexLoop.push_back(idxls);
					idxl = idxls;
					bSearch = true;
					break;
				}
			}
		} while (bSearch);
		for (int idxt = idxl + 1; idxt < size(); idxt++)
		//for (int idxt = size() - 1; idxt > idxl; idxt--)
		{
			if (get(idxt).getBrunchCoreEkiIndex() == idxl)
			{
				iEkiIndexBrunchTerminalSide.push_back(idxt);
			}
		}
		return INT_MIN;
	}
	else if (pCentDedEkiThis->getBrunchCoreEkiIndex() >= 0 &&
		pCentDedEkiThis->getBrunchCoreEkiIndex() < iEkiIndex)
	{
		//編集駅が、上方への派生駅の場合。基幹駅から上につながっている可能性あり
		//iEkiIndexBrunchTerminalSide.push_back(iEkiIndex);
		int iEkiIndexCore = pCentDedEkiThis->getBrunchCoreEkiIndex();
		iEkiIndexLoop.push_back(iEkiIndexCore);

		for (int idxt = iEkiIndexCore + 1; idxt < size(); idxt++)
		//for (int idxt = size() - 1; idxt > iEkiIndexCore; idxt--)
		{
			if (/*idxt != iEkiIndex &&*/
				get(idxt).getBrunchCoreEkiIndex() == iEkiIndexCore)
			{
				iEkiIndexBrunchTerminalSide.push_back(idxt);
			}
		}
		int idxl = iEkiIndexCore;
		while (get(idxl).getLoopOriginEkiIndex() >= 0)
		{
			iEkiIndexLoop.push_front(get(idxl).getLoopOriginEkiIndex());
			idxl = get(idxl).getLoopOriginEkiIndex();
		}
		//for (int idxo = idxl - 1; idxo >= 0; idxo--)
		for (int idxo = 0; idxo < idxl; idxo++)
		{
			if (get(idxo).getBrunchCoreEkiIndex() == idxl)
			{
				iEkiIndexBrunchOriginSide.push_back(idxo);
			}
		}
		return INT_MAX;
	}
	else if (pCentDedEkiThis->getLoopOriginEkiIndex() >= 0)
	{
		//編集駅が、終点駅の場合。下方からの始点駅OR基幹駅の可能性あり
		iEkiIndexLoop.push_back(iEkiIndex);
		int iEkiIndexOrigin = pCentDedEkiThis->getLoopOriginEkiIndex();
		iEkiIndexLoop.push_front(iEkiIndexOrigin);

		//上方探索
		int idxl = iEkiIndexOrigin;
		while (get(idxl).getLoopOriginEkiIndex() >= 0)
		{
			iEkiIndexLoop.push_front(get(idxl).getLoopOriginEkiIndex());
			idxl = get(idxl).getLoopOriginEkiIndex();
		}
		//for (int idxo = idxl - 1; idxo >= 0; idxo--)
		for (int idxo = 0; idxo < idxl; idxo++)
		{
			if (get(idxo).getBrunchCoreEkiIndex() == idxl)
			{
				iEkiIndexBrunchOriginSide.push_back(idxo);
			}
		}

		//下方探索
		idxl = iEkiIndex;
		bool bSearch;
		do
		{
			bSearch = false;
			for (int idxls = idxl + 1; idxls < size(); idxls++)
			{
				if (get(idxls).getLoopOriginEkiIndex() == idxl)
				{
					iEkiIndexLoop.push_back(idxls);
					idxl = idxls;
					bSearch = true;
					break;
				}
			}
		} while (bSearch);
		for (int idxt = idxl + 1; idxt < size(); idxt++)
		//for (int idxt = size() - 1; idxt > idxl; idxt--)
		{
			if (get(idxt).getBrunchCoreEkiIndex() == idxl)
			{
				iEkiIndexBrunchTerminalSide.push_back(idxt);
			}
		}
		for (int idx = 0; idx < (int)iEkiIndexLoop.size(); idx++)
		{
			if (iEkiIndexLoop[idx] == iEkiIndex)
			{
				return idx;
			}
		}
	}
	else
	{
		//編集駅からは分岐駅設定・環状線設定がなされていない場合。基幹駅もしくは起点駅の可能性あり
		//上方探索
		//for (int idxo = iEkiIndex - 1; idxo >= 0; idxo--)
		for (int idxo = 0; idxo < iEkiIndex; idxo++)
		{
			if (get(idxo).getBrunchCoreEkiIndex() == iEkiIndex)
			{
				if ((int)iEkiIndexLoop.size() == 0)
				{
					iEkiIndexLoop.push_back(iEkiIndex);
				}
				iEkiIndexBrunchOriginSide.push_back(idxo);
			}
		}

		//下方探索
		int idxl = iEkiIndex;
		bool bSearch;
		do
		{
			bSearch = false;
			for (int idxls = idxl + 1; idxls < size(); idxls++)
			{
				if (get(idxls).getLoopOriginEkiIndex() == idxl)
				{
					if ((int)iEkiIndexLoop.size() == 0)
					{
						iEkiIndexLoop.push_back(iEkiIndex);
					}
					iEkiIndexLoop.push_back(idxls);
					idxl = idxls;
					bSearch = true;
					break;
				}
			}
		} while (bSearch);
		for (int idxt = idxl + 1; idxt < size(); idxt++)
		//for (int idxt = size() - 1; idxt > idxl; idxt--)
		{
			if (get(idxt).getBrunchCoreEkiIndex() == idxl)
			{
				if ((int)iEkiIndexLoop.size() == 0)
				{
					iEkiIndexLoop.push_back(iEkiIndex);
				}
				iEkiIndexBrunchTerminalSide.push_back(idxt);
			}
		}
		if ((int)iEkiIndexLoop.size() == 0)
		{
			return -1;
		}
		for (int idx = 0; idx < (int)iEkiIndexLoop.size(); idx++)
		{
			if (iEkiIndexLoop[idx] == iEkiIndex)
			{
				return idx;
			}
		}
	}
	return -1;
}

int CentDedEkiCont::getEkiIndexBrunchLoop(
	int iEkiIndex,
	deque<int>& iEkiIndexBrunchOriginSide,
	deque<int>& iEkiIndexLoop,
	deque<int>& iEkiIndexBrunchTerminalSide) const
{
	const CentDedEki* pCentDedEkiThis = getMuPtr()->get(iEkiIndex);
	iEkiIndexBrunchOriginSide = pCentDedEkiThis->getEkiIndexBrunchOriginSide();
	iEkiIndexLoop = pCentDedEkiThis->getEkiIndexLoop();
	iEkiIndexBrunchTerminalSide = pCentDedEkiThis->getEkiIndexBrunchTerminalSide();
	return pCentDedEkiThis->getBrunchLoopPosition();
}

int CentDedEkiCont::getEkiOrderBrunchLoop(
	int iEkiOrder, ERessyahoukou eRessyahoukou, 
	deque<int>& iEkiOrderBrunchOriginSide, 
	deque<int>& iEkiOrderLoop, 
	deque<int>& iEkiOrderBrunchTerminalSide) const
{
	if (eRessyahoukou == ERessyahoukou::Ressyahoukou_Kudari)
	{
		int iResult = getEkiIndexBrunchLoop(
			iEkiOrder,
			iEkiOrderBrunchOriginSide,
			iEkiOrderLoop,
			iEkiOrderBrunchTerminalSide);
		return iResult;
	}
	else
	{
		deque<int> iEkiIndexBrunchOriginSide;
		deque<int> iEkiIndexLoop;
		deque<int> iEkiIndexBrunchTerminalSide;

		int iResult = getEkiIndexBrunchLoop(
			EkiIndexOfEkiOrder(ERessyahoukou::Ressyahoukou_Nobori,iEkiOrder),
			iEkiIndexBrunchOriginSide,
			iEkiIndexLoop,
			iEkiIndexBrunchTerminalSide);
		if (iResult == -1)
		{
			return iResult;
		}
		for (int idx = 0; idx < (int)iEkiIndexBrunchOriginSide.size(); idx++)
		{
			iEkiOrderBrunchTerminalSide.push_front(
				EkiOrderOfEkiIndex(ERessyahoukou::Ressyahoukou_Nobori, 
				iEkiIndexBrunchOriginSide[idx]));
		}
		for (int idx = 0; idx < (int)iEkiIndexLoop.size(); idx++)
		{
			iEkiOrderLoop.push_front(
				EkiOrderOfEkiIndex(ERessyahoukou::Ressyahoukou_Nobori,
					iEkiIndexLoop[idx]));
		}
		for (int idx = 0; idx < (int)iEkiIndexBrunchTerminalSide.size(); idx++)
		{
			iEkiOrderBrunchOriginSide.push_front(
				EkiOrderOfEkiIndex(ERessyahoukou::Ressyahoukou_Nobori,
					iEkiIndexBrunchTerminalSide[idx]));
		}
		if (iResult == INT_MAX)
		{
			return INT_MIN;
		}
		else if (iResult == INT_MIN)
		{
			return INT_MAX;
		}
		else if (iResult >= 0)
		{
			iResult = (int)iEkiIndexLoop.size() - iResult - 1;
		}
		return iResult;
	}
}

int CentDedEkiCont::getEkiIndexBrunchConvert(int iEkiIndex, deque<int>& iEkiIndexBrunchGroup) const
{
	//編集駅のBrunchCore及びLoopOriginを基に、場合分け
	const CentDedEki* pCentDedEkiThis = getMuPtr()->get(iEkiIndex);
	if (pCentDedEkiThis->getBrunchCoreEkiIndex() >= 0 )
	{
		//編集駅が、下方への派生駅の場合。基幹駅から下に繋がっている可能性あり
		iEkiIndexBrunchGroup.push_back(iEkiIndex);
		int iEkiIndexCore = pCentDedEkiThis->getBrunchCoreEkiIndex();
		//iEkiIndexBrunchGroup.push_back(iEkiIndexCore);
		for (int idx = 0; idx < size(); idx++)
		{
			if (idx != iEkiIndex &&
				get(idx).getBrunchCoreEkiIndex() == iEkiIndexCore)
			{
				iEkiIndexBrunchGroup.push_back(idx);
			}
		}
		return iEkiIndexCore;
	}
	else
	{
		//編集駅からは分岐駅設定・環状線設定がなされていない場合。基幹駅の可能性あり
		for (int idx = 0; idx < size(); idx++)
		{
			if (get(idx).getBrunchCoreEkiIndex() == iEkiIndex)
			{
				iEkiIndexBrunchGroup.push_back(idx);
			}
		}
		if ((int)iEkiIndexBrunchGroup.size() == 0)
		{
			return -1;
		}
		else
		{
			//iEkiIndexBrunchGroup.push_back(iEkiIndex);
			return iEkiIndex;
		}
	}
	return -1;
}

int CentDedEkiCont::getEkiOrderBrunchConvert(
	int iEkiOrder, ERessyahoukou eRessyahoukou, 
	deque<int>& iEkiOrderBrunchGroup) const
{
	if (eRessyahoukou == ERessyahoukou::Ressyahoukou_Kudari)
	{
		int iResult = getEkiIndexBrunchConvert(
			iEkiOrder,
			iEkiOrderBrunchGroup);
		return iResult;
	}
	else
	{
		deque<int> iEkiIndexBrunchGroup;

		int iResult = getEkiIndexBrunchConvert(
			EkiIndexOfEkiOrder(ERessyahoukou::Ressyahoukou_Nobori, iEkiOrder),
			iEkiIndexBrunchGroup);
		if (iResult == -1)
		{
			return iResult;
		}
		for (int idx = 0; idx < (int)iEkiIndexBrunchGroup.size(); idx++)
		{
			iEkiOrderBrunchGroup.push_back(
				EkiOrderOfEkiIndex(ERessyahoukou::Ressyahoukou_Nobori,
					iEkiIndexBrunchGroup[idx]));
		}
		iResult = EkiOrderOfEkiIndex(ERessyahoukou::Ressyahoukou_Nobori, iResult );
		
		return iResult;
	}
}

void CentDedEkiCont::adjustBrunchLoopEkiTrack2OuterTerminal(
	const int iEkiIndex, 
	const deque<int>& iEkiIndexBrunchLoop,
	const vector<int>& iEkiTrack2Map)
{
	const CentDedEki* pCentDedEkiThis = getMuPtr()->get(iEkiIndex);
	const CentDedEkiTrack2Cont* pEkiTrack2ContThis = pCentDedEkiThis->getEkiTrack2Cont();

	bool bFirstCompare = true;
	int iCompareResultEkiTrack2;
	int iCompareResultOuterEkimei;
	for (int idx = 0; idx < (int)iEkiIndexBrunchLoop.size(); idx++)
	{
		if (iEkiIndexBrunchLoop[idx] == iEkiIndex)
		{
			continue;
		}

		CentDedEki* pCentDedEkiTarget = getMuPtr()->get(iEkiIndexBrunchLoop[idx]);
		CentDedEkiTrack2Cont* pEkiTrack2ContTarget =
			pCentDedEkiTarget->getEkiTrack2Cont();

		if (bFirstCompare)
		{
			iCompareResultEkiTrack2 = pEkiTrack2ContThis->compareEkiTrack2(pEkiTrack2ContTarget);
			iCompareResultOuterEkimei = pCentDedEkiThis->compareOuterTerminal(pCentDedEkiTarget);
			bFirstCompare = false;
		}

		if (iCompareResultEkiTrack2 > 0)
		{
			//iCompareResultEkiTrack2が1・2の場合は、
			//編集された駅の番線＆主本線設定で、グループの他の駅に上書きします。
			//2の場合は、追加された分を末尾へinsertします。
			for (int iEkiTrack2Index = 0; iEkiTrack2Index < pEkiTrack2ContTarget->size(); iEkiTrack2Index++)
			{
				pEkiTrack2ContTarget->set(pEkiTrack2ContThis->get(iEkiTrack2Index), iEkiTrack2Index);
			}
			for (int iEkiTrack2Index = pEkiTrack2ContTarget->size();
				iEkiTrack2Index < pEkiTrack2ContThis->size(); iEkiTrack2Index++)
			{
				pEkiTrack2ContTarget->insert(pEkiTrack2ContThis->get(iEkiTrack2Index), INT_MAX);
			}
		}
		else if (iCompareResultEkiTrack2 < 0)
		{
			//iCompareResultEkiTrack2が-1の場合は、
			//編集された駅の番線＆主本線設定で、グループの他の駅に上書きし、減少した分をtargetからeraseします
			for (int iEkiTrack2Index = 0; iEkiTrack2Index < pEkiTrack2ContThis->size(); iEkiTrack2Index++)
			{
				pEkiTrack2ContTarget->set(pEkiTrack2ContThis->get(iEkiTrack2Index), iEkiTrack2Index);
			}
			pEkiTrack2ContTarget->erase(pEkiTrack2ContThis->size(), INT_MAX);
		}

		pCentDedEkiTarget->setDownMain(pCentDedEkiThis->getDownMain());
		pCentDedEkiTarget->setUpMain(pCentDedEkiThis->getUpMain());

		if (iCompareResultOuterEkimei > 0)
		{
			//iCompareResultOuterEkimeiが1-3の場合は、
			//編集された駅の路線外発着駅で、グループの他の駅に上書きします。
			//3の場合は、追加された分を末尾へinsertします。
			for (int iOuterEkimeiIndex = 0; iOuterEkimeiIndex < pCentDedEkiTarget->getOuterTerminalEkimeiCount(); iOuterEkimeiIndex++)
			{
				pCentDedEkiTarget->setOuterTerminalEkimei(pCentDedEkiThis->getOuterTerminal(iOuterEkimeiIndex), iOuterEkimeiIndex);
			}
			for (int iOuterEkimeiIndex = pCentDedEkiTarget->getOuterTerminalEkimeiCount();
				iOuterEkimeiIndex < pCentDedEkiThis->getOuterTerminalEkimeiCount(); iOuterEkimeiIndex++)
			{
				pCentDedEkiTarget->insertOuterTerminalEkimei(pCentDedEkiThis->getOuterTerminal(iOuterEkimeiIndex), INT_MAX);

			}
		}
		else if (iCompareResultOuterEkimei < 0)
		{
			//iCompareResultOuterEkimeiが-1の場合は、
			//編集された駅の路線外発着駅で、グループの他の駅に上書きし、減少した分をtargetからeraseします
			for (int iOuterEkimeiIndex = 0; iOuterEkimeiIndex < pCentDedEkiThis->getOuterTerminalEkimeiCount(); iOuterEkimeiIndex++)
			{
				pCentDedEkiTarget->setOuterTerminalEkimei(pCentDedEkiThis->getOuterTerminal(iOuterEkimeiIndex), iOuterEkimeiIndex);
			}
			pCentDedEkiTarget->eraseOuterTerminalEkimei(pCentDedEkiThis->getOuterTerminalEkimeiCount(), INT_MAX);
		}

		if (iCompareResultEkiTrack2 != 0)
		{
			//iEkiTrack2Mapをもとに、DiagramTrackOmitを新たに構築する
			vector<bool> bNewDiagramTrackOmit;
			for (int iEkiTrack2Index = 0; iEkiTrack2Index < pEkiTrack2ContTarget->size(); iEkiTrack2Index++)
			{
				//iEkiTrack2Mapの中から、新しいiEkiTrack2Index番線を探し出し、見つかったら元のDiagramTrackOmitから取得して、bNewDiagramTrackOmitに収める
				//見つからなかったら、新しい番線なので、falseを入れておく
				bool bFound = false;
				for (int idx = 0; idx < (int)iEkiTrack2Map.size(); idx++)
				{
					if (iEkiTrack2Map[idx] == iEkiTrack2Index)
					{
						bNewDiagramTrackOmit.push_back(pCentDedEkiTarget->getDiagramTrackOmit(idx));
						bFound = true;
						break;
					}
				}
				if (!bFound)
				{
					bNewDiagramTrackOmit.push_back(false);
				}
			}
			pCentDedEkiTarget->setDiagramTrackOmit(bNewDiagramTrackOmit);
		}
	}
}

bool CentDedEkiCont::isSameBrunchLoopGroup(
	const int iEkiIndexA, 
	const int iEkiIndexB) const
{	
	if (iEkiIndexA < 0 || size() <= iEkiIndexA)
	{
		return false;
	}
	if (iEkiIndexB < 0 || size() <= iEkiIndexB)
	{
		return false;
	}
	if (iEkiIndexA == iEkiIndexB)
	{
		return true;
	}
	deque<int> iEkiIndexBrunchOriginSideA;
	deque<int> iEkiIndexLoopA;
	deque<int> iEkiIndexBrunchTerminalSideA;
	deque<int> iEkiIndexBrunchOriginSideB;
	deque<int> iEkiIndexLoopB;
	deque<int> iEkiIndexBrunchTerminalSideB;
	int iResultA = getEkiIndexBrunchLoop(
		iEkiIndexA, iEkiIndexBrunchOriginSideA,
		iEkiIndexLoopA, iEkiIndexBrunchTerminalSideA);
	if (iResultA == -1)
	{
		return false;
	}
	int iResultB = getEkiIndexBrunchLoop(
		iEkiIndexB, iEkiIndexBrunchOriginSideB,
		iEkiIndexLoopB, iEkiIndexBrunchTerminalSideB);
	if (iResultB == -1)
	{
		return false;
	}
	return iEkiIndexLoopA[0] == iEkiIndexLoopB[0];
}

bool CentDedEkiCont::isSameBrunchLoopGroup(
	const int iEkiOrderA, 
	const int iEkiOrderB, 
	ERessyahoukou eRessyahoukou) const
{
	return isSameBrunchLoopGroup(
		EkiIndexOfEkiOrder(eRessyahoukou, iEkiOrderA),
		EkiIndexOfEkiOrder(eRessyahoukou, iEkiOrderB));
}

void CentDedEkiCont::adjustBrunchLoopCont()
{
	vector<bool> bChecked;
	bChecked.resize(size(), false);
	for (int idx = 0; idx < size(); idx++)
	{
		if (bChecked[idx])
		{
			continue;
		}
		deque<int> iEkiIndexBrunchOriginSide;
		deque<int> iEkiIndexLoop;
		deque<int> iEkiIndexBrunchTerminalSide;
		int iBrunchLoopPosition = searchEkiIndexBrunchLoop(
			idx,
			iEkiIndexBrunchOriginSide,
			iEkiIndexLoop,
			iEkiIndexBrunchTerminalSide);
		if (iBrunchLoopPosition == -1)
		{
			CentDedEki* pCentDedEki = getMuPtr()->get(idx);
			pCentDedEki->setBrunchLoopPosition(iBrunchLoopPosition);
			pCentDedEki->clearEkiIndexBrunchOriginSide();
			pCentDedEki->clearEkiIndexLoop();
			pCentDedEki->clearEkiIndexBrunchTerminalSide();
			bChecked[idx] = true;
		}
		else
		{
			for (int idxo = 0; idxo < (int)iEkiIndexBrunchOriginSide.size(); idxo++)
			{
				CentDedEki* pCentDedEki = getMuPtr()->get(iEkiIndexBrunchOriginSide[idxo]);
				pCentDedEki->setBrunchLoopPosition(INT_MIN);
				pCentDedEki->setEkiIndexBrunchOriginSide(iEkiIndexBrunchOriginSide);
				pCentDedEki->setEkiIndexLoop(iEkiIndexLoop);
				pCentDedEki->setEkiIndexBrunchTerminalSide(iEkiIndexBrunchTerminalSide);
				bChecked[iEkiIndexBrunchOriginSide[idxo]] = true;
			}
			for (int idxl = 0; idxl < (int)iEkiIndexLoop.size(); idxl++)
			{
				CentDedEki* pCentDedEki = getMuPtr()->get(iEkiIndexLoop[idxl]);
				pCentDedEki->setBrunchLoopPosition(idxl);
				pCentDedEki->setEkiIndexBrunchOriginSide(iEkiIndexBrunchOriginSide);
				pCentDedEki->setEkiIndexLoop(iEkiIndexLoop);
				pCentDedEki->setEkiIndexBrunchTerminalSide(iEkiIndexBrunchTerminalSide);
				bChecked[iEkiIndexLoop[idxl]] = true;
			}
			for (int idxt = 0; idxt < (int)iEkiIndexBrunchTerminalSide.size(); idxt++)
			{
				CentDedEki* pCentDedEki = getMuPtr()->get(iEkiIndexBrunchTerminalSide[idxt]);
				pCentDedEki->setBrunchLoopPosition(INT_MAX);
				pCentDedEki->setEkiIndexBrunchOriginSide(iEkiIndexBrunchOriginSide);
				pCentDedEki->setEkiIndexLoop(iEkiIndexLoop);
				pCentDedEki->setEkiIndexBrunchTerminalSide(iEkiIndexBrunchTerminalSide);
				bChecked[iEkiIndexBrunchTerminalSide[idxt]] = true;
			}
		}
	}
}

void CentDedEkiCont::mergeOuterTerminal(
	deque<int>& iEkiIndexBrunchOriginSide,
	deque<int>& iEkiIndexLoop,
	deque<int>& iEkiIndexBrunchTerminalSide,
	vector<vector<int>>& iOuterTerminalMapCont)
{
	CentDedEki* pCentDedEkiCore = getMuPtr()->get(iEkiIndexLoop[0]);
	for (int idxl = 1; idxl < (int)iEkiIndexLoop.size(); idxl++)
	{
		const CentDedEki* pCentDedEkiTarget =
			getMuPtr()->get(iEkiIndexLoop[idxl]);
		//iOuterTerminalMapContの初期化
		for (int idxot = 0; idxot < pCentDedEkiTarget->getOuterTerminalEkimeiCount(); idxot++)
		{
			iOuterTerminalMapCont[iEkiIndexLoop[idxl]].push_back(idxot);
		}
		int iCompareResultOuterTerminal = pCentDedEkiTarget->compareOuterTerminal(pCentDedEkiCore);
		//比較結果が-1,2,3だった場合は、CoreになくてTargetにあるものを、Coreに追加していく
		for (int idxot = 0; idxot < pCentDedEkiTarget->getOuterTerminalEkimeiCount() && 
			(iCompareResultOuterTerminal >= 2 || iCompareResultOuterTerminal <= -1); idxot++)
		{
			OuterTerminal sOuterTerminal = pCentDedEkiTarget->getOuterTerminal(idxot);
			int iOuterTerminalExsit = pCentDedEkiCore->searchOuterTerminalEkimei(sOuterTerminal.OuterTerminalEkimei);
			if (iOuterTerminalExsit < 0)
			{
				pCentDedEkiCore->insertOuterTerminalEkimei(sOuterTerminal, INT_MAX);
				iOuterTerminalMapCont[iEkiIndexLoop[idxl]][idxot] = pCentDedEkiCore->getOuterTerminalEkimeiCount() - 1;
			}
			else
			{
				iOuterTerminalMapCont[iEkiIndexLoop[idxl]][idxot] = iOuterTerminalExsit;
			}
		}
		//ここではTarget側への追加（CoreにあってTargetにないもの)は行わない。
	}
	for (int idxo = 0; idxo < (int)iEkiIndexBrunchOriginSide.size(); idxo++)
	{
		const CentDedEki* pCentDedEkiTarget =
			getMuPtr()->get(iEkiIndexBrunchOriginSide[idxo]);
		//iOuterTerminalMapContの初期化
		for (int idxot = 0; idxot < pCentDedEkiTarget->getOuterTerminalEkimeiCount(); idxot++)
		{
			iOuterTerminalMapCont[iEkiIndexBrunchOriginSide[idxo]].push_back(idxot);
		}
		int iCompareResultOuterTerminal = pCentDedEkiTarget->compareOuterTerminal(pCentDedEkiCore);
		//比較結果が-1,2,3だった場合は、CoreになくてTargetにあるものを、Coreに追加していく
		for (int idxot = 0; idxot < pCentDedEkiTarget->getOuterTerminalEkimeiCount() && 
			(iCompareResultOuterTerminal >= 2 || iCompareResultOuterTerminal <= -1); idxot++)
		{
			OuterTerminal sOuterTerminal = pCentDedEkiTarget->getOuterTerminal(idxot);
			int iOuterTerminalExsit = pCentDedEkiCore->searchOuterTerminalEkimei(sOuterTerminal.OuterTerminalEkimei);
			if (iOuterTerminalExsit < 0)
			{
				pCentDedEkiCore->insertOuterTerminalEkimei(sOuterTerminal, INT_MAX);
				iOuterTerminalMapCont[iEkiIndexBrunchOriginSide[idxo]][idxot] = pCentDedEkiCore->getOuterTerminalEkimeiCount() - 1;
			}
			else
			{
				iOuterTerminalMapCont[iEkiIndexBrunchOriginSide[idxo]][idxot] = iOuterTerminalExsit;
			}
		}
		//ここではTarget側への追加（CoreにあってTargetにないもの)は行わない。
	}
	for (int idxt = 0; idxt < (int)iEkiIndexBrunchTerminalSide.size(); idxt++)
	{
		const CentDedEki* pCentDedEkiTarget =
			getMuPtr()->get(iEkiIndexBrunchTerminalSide[idxt]);
		//iOuterTerminalMapContの初期化
		for (int idxot = 0; idxot < pCentDedEkiTarget->getOuterTerminalEkimeiCount(); idxot++)
		{
			iOuterTerminalMapCont[iEkiIndexBrunchTerminalSide[idxt]].push_back(idxot);
		}
		int iCompareResultOuterTerminal = pCentDedEkiTarget->compareOuterTerminal(pCentDedEkiCore);
		//比較結果が-1,2,3だった場合は、CoreになくてTargetにあるものを、Coreに追加していく
		for (int idxot = 0; idxot < pCentDedEkiTarget->getOuterTerminalEkimeiCount() && 
			(iCompareResultOuterTerminal >= 2 || iCompareResultOuterTerminal <= -1); idxot++)
		{
			OuterTerminal sOuterTerminal = pCentDedEkiTarget->getOuterTerminal(idxot);
			int iOuterTerminalExsit = pCentDedEkiCore->searchOuterTerminalEkimei(sOuterTerminal.OuterTerminalEkimei);
			if (iOuterTerminalExsit < 0)
			{
				pCentDedEkiCore->insertOuterTerminalEkimei(sOuterTerminal, INT_MAX);
				iOuterTerminalMapCont[iEkiIndexBrunchTerminalSide[idxt]][idxot] = pCentDedEkiCore->getOuterTerminalEkimeiCount() - 1;
			}
			else
			{
				iOuterTerminalMapCont[iEkiIndexBrunchTerminalSide[idxt]][idxot] = iOuterTerminalExsit;
			}
		}
		//ここではTarget側への追加（CoreにあってTargetにないもの)は行わない。
	}

	//Coreに集約された路線外発着駅名を、他の駅に反映させる。
	for (int idxl = 1; idxl < (int)iEkiIndexLoop.size(); idxl++)
	{
		CentDedEki* pCentDedEkiTarget =
			getMuPtr()->get(iEkiIndexLoop[idxl]);
		for (int idxot = 0; idxot < pCentDedEkiCore->getOuterTerminalEkimeiCount(); idxot++)
		{
			if (idxot < pCentDedEkiTarget->getOuterTerminalEkimeiCount())
			{
				pCentDedEkiTarget->setOuterTerminalEkimei(pCentDedEkiCore->getOuterTerminal(idxot), idxot);
			}
			else
			{
				pCentDedEkiTarget->insertOuterTerminalEkimei(pCentDedEkiCore->getOuterTerminal(idxot), INT_MAX);
			}
		}
	}
	for (int idxo = 0; idxo < (int)iEkiIndexBrunchOriginSide.size(); idxo++)
	{
		CentDedEki* pCentDedEkiTarget =
			getMuPtr()->get(iEkiIndexBrunchOriginSide[idxo]);
		for (int idxot = 0; idxot < pCentDedEkiCore->getOuterTerminalEkimeiCount(); idxot++)
		{
			if (idxot < pCentDedEkiTarget->getOuterTerminalEkimeiCount())
			{
				pCentDedEkiTarget->setOuterTerminalEkimei(pCentDedEkiCore->getOuterTerminal(idxot), idxot);
			}
			else
			{
				pCentDedEkiTarget->insertOuterTerminalEkimei(pCentDedEkiCore->getOuterTerminal(idxot), INT_MAX);
			}
		}
	}
	for (int idxt = 0; idxt < (int)iEkiIndexBrunchTerminalSide.size(); idxt++)
	{
		CentDedEki* pCentDedEkiTarget =
			getMuPtr()->get(iEkiIndexBrunchTerminalSide[idxt]);
		for (int idxot = 0; idxot < pCentDedEkiCore->getOuterTerminalEkimeiCount(); idxot++)
		{
			if (idxot < pCentDedEkiTarget->getOuterTerminalEkimeiCount())
			{
				pCentDedEkiTarget->setOuterTerminalEkimei(pCentDedEkiCore->getOuterTerminal(idxot), idxot);
			}
			else
			{
				pCentDedEkiTarget->insertOuterTerminalEkimei(pCentDedEkiCore->getOuterTerminal(idxot), INT_MAX);
			}
		}
	}
}

void CentDedEkiCont::adjustCrossingCheckRule(
	const int iEkiIndex, 
	const deque<int>& iEkiIndexBrunchLoop)
{
	const CentDedEki* pCentDedEkiThis = getMuPtr()->get(iEkiIndex);
	for (int idx = 0; idx < (int)iEkiIndexBrunchLoop.size(); idx++)
	{
		if (iEkiIndexBrunchLoop[idx] == iEkiIndex)
		{
			continue;
		}
		CentDedEki* pCentDedEkiTarget = getMuPtr()->get(iEkiIndexBrunchLoop[idx]);
		pCentDedEkiTarget->setCrossingCheckRule(pCentDedEkiThis->getCrossingCheckRuleCont());
	}
}

void CentDedEkiCont::adjustBrunchLoopCrossingCheckRule(
	const int iEkiIndex, 
	const deque<int>& iEkiIndexBrunchLoop, 
	const vector<int>& iEkiTrack2Map, 
	const vector<int>& iOuterTerminalEkimeiMap)
{
	CentDedEki* pCentDedEkiThis = getMuPtr()->get(iEkiIndex);
	//vector<CrossingCheckRule> CrossingCheckRuleCont = pCentDedEkiThis->getCrossingCheckRuleCont();
	for (int idx = pCentDedEkiThis->getCrossingCheckRuleSize() -1 ; idx >= 0  ; idx--)
	{
		CrossingCheckRule CrossingCheckRuleTemp = pCentDedEkiThis->getCrossingCheckRule(idx);
		
		//番線削除などの結果、TrackContentCont4つのうちどれか一つでも空になったなら、このルール自体を削除します。
		//bool bFoundTrackContentContEmpty = false;
		vector< TrackContent> BeforeFromTrackContentCont = CrossingCheckRuleTemp.BeforeFromTrackContentCont;
		for (int idxbf = (int)BeforeFromTrackContentCont.size() - 1; idxbf >= 0; idxbf--)
		{
			if (BeforeFromTrackContentCont[idxbf].eTrackType == ETrackType::TrackType_Track)
			{
				if (iEkiTrack2Map[BeforeFromTrackContentCont[idxbf].iTrackIndex] < 0)
				{
					BeforeFromTrackContentCont.erase(BeforeFromTrackContentCont.begin() + idxbf);
				}
				else if (iEkiTrack2Map[BeforeFromTrackContentCont[idxbf].iTrackIndex] != BeforeFromTrackContentCont[idxbf].iTrackIndex)
				{
					BeforeFromTrackContentCont[idxbf].iTrackIndex = iEkiTrack2Map[BeforeFromTrackContentCont[idxbf].iTrackIndex];
				}
			}
			else if (BeforeFromTrackContentCont[idxbf].eTrackType == ETrackType::TrackType_Outer)
			{
				if (iOuterTerminalEkimeiMap[BeforeFromTrackContentCont[idxbf].iTrackIndex] < 0)
				{
					BeforeFromTrackContentCont.erase(BeforeFromTrackContentCont.begin() + idxbf);
				}
				else if (iOuterTerminalEkimeiMap[BeforeFromTrackContentCont[idxbf].iTrackIndex] != BeforeFromTrackContentCont[idxbf].iTrackIndex)
				{
					BeforeFromTrackContentCont[idxbf].iTrackIndex = iOuterTerminalEkimeiMap[BeforeFromTrackContentCont[idxbf].iTrackIndex];
				}
			}
		}
		if ((int)BeforeFromTrackContentCont.size() == 0)
		{
			pCentDedEkiThis->eraseCrossingCheckRule(idx);
			continue;
		}
		else
		{
			CrossingCheckRuleTemp.BeforeFromTrackContentCont = BeforeFromTrackContentCont;
		}

		vector< TrackContent> BeforeToTrackContentCont = CrossingCheckRuleTemp.BeforeToTrackContentCont;
		for (int idxbf = (int)BeforeToTrackContentCont.size() - 1; idxbf >= 0; idxbf--)
		{
			if (BeforeToTrackContentCont[idxbf].eTrackType == ETrackType::TrackType_Track)
			{
				if (iEkiTrack2Map[BeforeToTrackContentCont[idxbf].iTrackIndex] < 0)
				{
					BeforeToTrackContentCont.erase(BeforeToTrackContentCont.begin() + idxbf);
				}
				else if (iEkiTrack2Map[BeforeToTrackContentCont[idxbf].iTrackIndex] != BeforeToTrackContentCont[idxbf].iTrackIndex)
				{
					BeforeToTrackContentCont[idxbf].iTrackIndex = iEkiTrack2Map[BeforeToTrackContentCont[idxbf].iTrackIndex];
				}
			}
			else if (BeforeToTrackContentCont[idxbf].eTrackType == ETrackType::TrackType_Outer)
			{
				if (iOuterTerminalEkimeiMap[BeforeToTrackContentCont[idxbf].iTrackIndex] < 0)
				{
					BeforeToTrackContentCont.erase(BeforeToTrackContentCont.begin() + idxbf);
				}
				else if (iOuterTerminalEkimeiMap[BeforeToTrackContentCont[idxbf].iTrackIndex] != BeforeToTrackContentCont[idxbf].iTrackIndex)
				{
					BeforeToTrackContentCont[idxbf].iTrackIndex = iOuterTerminalEkimeiMap[BeforeToTrackContentCont[idxbf].iTrackIndex];
				}
			}
		}
		if ((int)BeforeToTrackContentCont.size() == 0)
		{
			pCentDedEkiThis->eraseCrossingCheckRule(idx);
			continue;
		}
		else
		{
			CrossingCheckRuleTemp.BeforeToTrackContentCont = BeforeToTrackContentCont;
		}

		vector< TrackContent> AfterFromTrackContentCont = CrossingCheckRuleTemp.AfterFromTrackContentCont;
		for (int idxbf = (int)AfterFromTrackContentCont.size() - 1; idxbf >= 0; idxbf--)
		{
			if (AfterFromTrackContentCont[idxbf].eTrackType == ETrackType::TrackType_Track)
			{
				if (iEkiTrack2Map[AfterFromTrackContentCont[idxbf].iTrackIndex] < 0)
				{
					AfterFromTrackContentCont.erase(AfterFromTrackContentCont.begin() + idxbf);
				}
				else if (iEkiTrack2Map[AfterFromTrackContentCont[idxbf].iTrackIndex] != AfterFromTrackContentCont[idxbf].iTrackIndex)
				{
					AfterFromTrackContentCont[idxbf].iTrackIndex = iEkiTrack2Map[AfterFromTrackContentCont[idxbf].iTrackIndex];
				}
			}
			else if (AfterFromTrackContentCont[idxbf].eTrackType == ETrackType::TrackType_Outer)
			{
				if (iOuterTerminalEkimeiMap[AfterFromTrackContentCont[idxbf].iTrackIndex] < 0)
				{
					AfterFromTrackContentCont.erase(AfterFromTrackContentCont.begin() + idxbf);
				}
				else if (iOuterTerminalEkimeiMap[AfterFromTrackContentCont[idxbf].iTrackIndex] != AfterFromTrackContentCont[idxbf].iTrackIndex)
				{
					AfterFromTrackContentCont[idxbf].iTrackIndex = iOuterTerminalEkimeiMap[AfterFromTrackContentCont[idxbf].iTrackIndex];
				}
			}
		}
		if ((int)AfterFromTrackContentCont.size() == 0)
		{
			pCentDedEkiThis->eraseCrossingCheckRule(idx);
			continue;
		}
		else
		{
			CrossingCheckRuleTemp.AfterFromTrackContentCont = AfterFromTrackContentCont;
		}

		vector< TrackContent> AfterToTrackContentCont = CrossingCheckRuleTemp.AfterToTrackContentCont;
		for (int idxbf = (int)AfterToTrackContentCont.size() - 1; idxbf >= 0; idxbf--)
		{
			if (AfterToTrackContentCont[idxbf].eTrackType == ETrackType::TrackType_Track)
			{
				if (iEkiTrack2Map[AfterToTrackContentCont[idxbf].iTrackIndex] < 0)
				{
					AfterToTrackContentCont.erase(AfterToTrackContentCont.begin() + idxbf);
				}
				else if (iEkiTrack2Map[AfterToTrackContentCont[idxbf].iTrackIndex] != AfterToTrackContentCont[idxbf].iTrackIndex)
				{
					AfterToTrackContentCont[idxbf].iTrackIndex = iEkiTrack2Map[AfterToTrackContentCont[idxbf].iTrackIndex];
				}
			}
			else if (AfterToTrackContentCont[idxbf].eTrackType == ETrackType::TrackType_Outer)
			{
				if (iOuterTerminalEkimeiMap[AfterToTrackContentCont[idxbf].iTrackIndex] < 0)
				{
					AfterToTrackContentCont.erase(AfterToTrackContentCont.begin() + idxbf);
				}
				else if (iOuterTerminalEkimeiMap[AfterToTrackContentCont[idxbf].iTrackIndex] != AfterToTrackContentCont[idxbf].iTrackIndex)
				{
					AfterToTrackContentCont[idxbf].iTrackIndex = iOuterTerminalEkimeiMap[AfterToTrackContentCont[idxbf].iTrackIndex];
				}
			}
		}
		if ((int)AfterToTrackContentCont.size() == 0)
		{
			pCentDedEkiThis->eraseCrossingCheckRule(idx);
			continue;
		}
		else
		{
			CrossingCheckRuleTemp.AfterToTrackContentCont = AfterToTrackContentCont;
		}

		pCentDedEkiThis->setCrossingCheckRule(CrossingCheckRuleTemp,idx);
	}
}

void CentDedEkiCont::adjustCrossingCheckRuleByEkiEdit()
{
	for (int iEkiIndex = 0; iEkiIndex < size(); iEkiIndex++)
	{
		CentDedEki* pCentDedEki = getMuPtr()->get(iEkiIndex);
		if (pCentDedEki->getCrossingCheckRuleSize() == 0)
		{
			continue;
		}
		vector<bool> MapTrackContentIsValidOrigin;
		vector<bool> MapTrackContentIsValidTerminal;
		MapTrackContentIsValidOrigin.assign(size(), false);
		MapTrackContentIsValidTerminal.assign(size(), false);

		deque<int> iEkiIndexBranchLoop;
		getEkiIndexBrunchLoop(iEkiIndex, iEkiIndexBranchLoop);

		for (int idx = 0; idx < (int)iEkiIndexBranchLoop.size(); idx++)
		{
			const CentDedEki* pCentDedEkiSearch = getMuPtr()->get(iEkiIndexBranchLoop[idx]);
			if (iEkiIndexBranchLoop[idx] > 0 && pCentDedEkiSearch->getEkijikokukeisiki() != CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku)
			{
				MapTrackContentIsValidOrigin[iEkiIndexBranchLoop[idx]] = true;

			}

			if (iEkiIndexBranchLoop[idx] < size() - 1 &&
				pCentDedEkiSearch->getEkijikokukeisiki() != CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku)
			{
				MapTrackContentIsValidTerminal[iEkiIndexBranchLoop[idx]] = true;
			}
		}

		for (int idx = pCentDedEki->getCrossingCheckRuleSize() - 1; idx >= 0; idx--)
		{
			CrossingCheckRule CrossingCheckRuleTemp = pCentDedEki->getCrossingCheckRule(idx);
			vector< TrackContent> BeforeFromTrackContentCont = CrossingCheckRuleTemp.BeforeFromTrackContentCont;
			for (int idxbf = (int)BeforeFromTrackContentCont.size() - 1; idxbf >= 0; idxbf--)
			{
				if (BeforeFromTrackContentCont[idxbf].eTrackType == ETrackType::TrackType_Origin)
				{
					if (BeforeFromTrackContentCont[idxbf].iTrackIndex >= (int)MapTrackContentIsValidOrigin.size())
					{
						BeforeFromTrackContentCont.erase(BeforeFromTrackContentCont.begin() + idxbf);
					}
					else if (!MapTrackContentIsValidOrigin[BeforeFromTrackContentCont[idxbf].iTrackIndex])
					{
						BeforeFromTrackContentCont.erase(BeforeFromTrackContentCont.begin() + idxbf);
					}
				}
				else if (BeforeFromTrackContentCont[idxbf].eTrackType == ETrackType::TrackType_Terminal)
				{
					if (BeforeFromTrackContentCont[idxbf].iTrackIndex >= (int)MapTrackContentIsValidTerminal.size())
					{
						BeforeFromTrackContentCont.erase(BeforeFromTrackContentCont.begin() + idxbf);
					}
					else if (!MapTrackContentIsValidTerminal[BeforeFromTrackContentCont[idxbf].iTrackIndex])
					{
						BeforeFromTrackContentCont.erase(BeforeFromTrackContentCont.begin() + idxbf);
					}
				}
			}
			if ((int)BeforeFromTrackContentCont.size() == 0)
			{
				pCentDedEki->eraseCrossingCheckRule(idx);
				continue;
			}
			else
			{
				CrossingCheckRuleTemp.BeforeFromTrackContentCont = BeforeFromTrackContentCont;
			}

			vector< TrackContent> BeforeToTrackContentCont = CrossingCheckRuleTemp.BeforeToTrackContentCont;
			for (int idxbt = (int)BeforeToTrackContentCont.size() - 1; idxbt >= 0; idxbt--)
			{
				if (BeforeToTrackContentCont[idxbt].eTrackType == ETrackType::TrackType_Origin)
				{
					if (BeforeToTrackContentCont[idxbt].iTrackIndex >= (int)MapTrackContentIsValidOrigin.size())
					{
						BeforeToTrackContentCont.erase(BeforeToTrackContentCont.begin() + idxbt);
					}
					else if (!MapTrackContentIsValidOrigin[BeforeToTrackContentCont[idxbt].iTrackIndex])
					{
						BeforeToTrackContentCont.erase(BeforeToTrackContentCont.begin() + idxbt);
					}
				}
				else if (BeforeToTrackContentCont[idxbt].eTrackType == ETrackType::TrackType_Terminal)
				{
					if (BeforeToTrackContentCont[idxbt].iTrackIndex >= (int)MapTrackContentIsValidTerminal.size())
					{
						BeforeToTrackContentCont.erase(BeforeToTrackContentCont.begin() + idxbt);
					}
					else if (!MapTrackContentIsValidTerminal[BeforeToTrackContentCont[idxbt].iTrackIndex])
					{
						BeforeToTrackContentCont.erase(BeforeToTrackContentCont.begin() + idxbt);
					}
				}
			}
			if ((int)BeforeToTrackContentCont.size() == 0)
			{
				pCentDedEki->eraseCrossingCheckRule(idx);
				continue;
			}
			else
			{
				CrossingCheckRuleTemp.BeforeToTrackContentCont = BeforeToTrackContentCont;
			}

			vector< TrackContent> AfterFromTrackContentCont = CrossingCheckRuleTemp.AfterFromTrackContentCont;
			for (int idxaf = (int)AfterFromTrackContentCont.size() - 1; idxaf >= 0; idxaf--)
			{
				if (AfterFromTrackContentCont[idxaf].eTrackType == ETrackType::TrackType_Origin)
				{
					if (AfterFromTrackContentCont[idxaf].iTrackIndex >= (int)MapTrackContentIsValidOrigin.size())
					{
						AfterFromTrackContentCont.erase(AfterFromTrackContentCont.begin() + idxaf);
					}
					else if (!MapTrackContentIsValidOrigin[AfterFromTrackContentCont[idxaf].iTrackIndex])
					{
						AfterFromTrackContentCont.erase(AfterFromTrackContentCont.begin() + idxaf);
					}
				}
				else if (AfterFromTrackContentCont[idxaf].eTrackType == ETrackType::TrackType_Terminal)
				{
					if (AfterFromTrackContentCont[idxaf].iTrackIndex >= (int)MapTrackContentIsValidTerminal.size())
					{
						AfterFromTrackContentCont.erase(AfterFromTrackContentCont.begin() + idxaf);
					}
					else if (!MapTrackContentIsValidTerminal[AfterFromTrackContentCont[idxaf].iTrackIndex])
					{
						AfterFromTrackContentCont.erase(AfterFromTrackContentCont.begin() + idxaf);
					}
				}
			}
			if ((int)AfterFromTrackContentCont.size() == 0)
			{
				pCentDedEki->eraseCrossingCheckRule(idx);
				continue;
			}
			else
			{
				CrossingCheckRuleTemp.AfterFromTrackContentCont = AfterFromTrackContentCont;
			}

			vector< TrackContent> AfterToTrackContentCont = CrossingCheckRuleTemp.AfterToTrackContentCont;
			for (int idxat = (int)AfterToTrackContentCont.size() - 1; idxat >= 0; idxat--)
			{
				if (AfterToTrackContentCont[idxat].eTrackType == ETrackType::TrackType_Origin)
				{
					if (AfterToTrackContentCont[idxat].iTrackIndex >= (int)MapTrackContentIsValidOrigin.size())
					{
						AfterToTrackContentCont.erase(AfterToTrackContentCont.begin() + idxat);
					}
					else if (!MapTrackContentIsValidOrigin[AfterToTrackContentCont[idxat].iTrackIndex])
					{
						AfterToTrackContentCont.erase(AfterToTrackContentCont.begin() + idxat);
					}
				}
				else if (AfterToTrackContentCont[idxat].eTrackType == ETrackType::TrackType_Terminal)
				{
					if (AfterToTrackContentCont[idxat].iTrackIndex >= (int)MapTrackContentIsValidTerminal.size())
					{
						AfterToTrackContentCont.erase(AfterToTrackContentCont.begin() + idxat);
					}
					else if (!MapTrackContentIsValidTerminal[AfterToTrackContentCont[idxat].iTrackIndex])
					{
						AfterToTrackContentCont.erase(AfterToTrackContentCont.begin() + idxat);
					}
				}
			}
			if ((int)AfterToTrackContentCont.size() == 0)
			{
				pCentDedEki->eraseCrossingCheckRule(idx);
				continue;
			}
			else
			{
				CrossingCheckRuleTemp.AfterToTrackContentCont = AfterToTrackContentCont;
			}

			pCentDedEki->setCrossingCheckRule(CrossingCheckRuleTemp, idx);
		}
	}
}


} //namespace entDed
