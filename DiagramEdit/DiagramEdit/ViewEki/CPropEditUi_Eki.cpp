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
// ****************************************************************
//	$Id: CPropEditUi_Eki.cpp
// ****************************************************************

/** @file */
#include "stdafx.h"
#include "CPropEditUi_Eki.h"
#include <tchar.h>

namespace ViewEki {


	// ********************************
	//@name エラーメッセージ
	// ********************************
	/// 駅名が長すぎます
const TCHAR* const CPropEditUi_Eki::ERRMSG_EKIMEI_TOO_LONG = _T("Ekimei is too long(Limit is 58 characters).") ;

/// 分岐駅設定ONの時は、対象駅を選択してください
const TCHAR* const CPropEditUi_Eki::ERRMSG_BRUNCH_EKIINDEX = _T("To enable Brunch-Func need ekiindex.");

/// 分岐駅設定ONの時は、駅規模を主要駅にしてください
const TCHAR* const CPropEditUi_Eki::ERRMSG_BRUNCH_EKIKIBO = _T("To enable Brunch-Func need Syuyoueki.");

/// 分岐駅設定ONかつ対象駅が終点方の場合は、駅時刻形式を下り着時刻にしてください
const TCHAR* const CPropEditUi_Eki::ERRMSG_BRUNCH_EKIJIKOKUKEISIKI_DOWNCHAKU = _T("To enable Brunch-Func need down-chakujikoku.");

/// 分岐駅設定ONかつ対象駅が起点方の場合は、駅時刻形式を上り着時刻にしてください
const TCHAR* const CPropEditUi_Eki::ERRMSG_BRUNCH_EKIJIKOKUKEISIKI_UPCHAKU = _T("To enable Brunch-Func need up-chakujikoku.");

/// 環状線設定ONの時は、起点駅を選択してください
const TCHAR* const CPropEditUi_Eki::ERRMSG_LOOP_EKIINDEX = _T("To enable Loop-Func need ekiindex.");

/// 環状線設定ONの時は、駅規模を主要駅にしてください
const TCHAR* const CPropEditUi_Eki::ERRMSG_LOOP_EKIKIBO = _T("To enable Loop-Func need Syuyoueki.");

/// 環状線設定ONの時は、駅時刻形式を発着または下り着時刻にしてください
const TCHAR* const CPropEditUi_Eki::ERRMSG_LOOP_EKIJIKOKUKEISIKI_HATSUCHAKU_DOWNCHAKU = _T("To enable Loop-Func need hatsu-chaku or down-chakujikoku.");
// 駅名が指定されていません
const TCHAR* const CPropEditUi_Eki::ERRMSG_EKIMEI_EMPTY = _T("EKIMEI is empty.");

/// 駅名略称が長すぎます
const TCHAR* const CPropEditUi_Eki::ERRMSG_EKIMEIJIKOKUHYOURYAKU_TOO_LONG = _T("EkimeiJikokuhyouRyaku is too long(Limit is 58 characters).");

/// 駅名略称(運用一覧)が長すぎます
const TCHAR* const CPropEditUi_Eki::ERRMSG_EKIMEIDIAGRAMRYAKU_TOO_LONG = _T("EkimeiDiagramRyaku is too long(Limit is 58 characters).");


//	// ================================
//	//@name 下請関数
//	// ================================
//
void CPropEditUi_Eki::InitUiData(UIDATA * pUiData)
{
	const CentDedEki* pTarget = m_pTarget->get(0);
	pUiData->iEkijikokukeisiki = (int)pTarget->getEkijikokukeisiki();
	EkiTrack2 aEkiTrack2;

	aEkiTrack2.strTrackName = _T("1番線");
	aEkiTrack2.strTrackRyakusyou = _T("1");
	aEkiTrack2.strTrackNoboriRyakusyou = _T("");
	aEkiTrack2.iMainTrack = 1;
	pUiData->sEkiTrack2.push_back(aEkiTrack2);

	aEkiTrack2.strTrackName = _T("2番線");
	aEkiTrack2.strTrackRyakusyou = _T("2");
	aEkiTrack2.strTrackNoboriRyakusyou = _T("");
	aEkiTrack2.iMainTrack = 2;
	pUiData->sEkiTrack2.push_back(aEkiTrack2);

	pUiData->bDiagramTrackOmit.push_back(false);
	pUiData->bDiagramTrackOmit.push_back(false);

}
	// ================================
	//	オーバーライトの必要なメソッド1-Targetに依存する処理
	// ================================
void CPropEditUi_Eki::UiDataFromTarget( UIDATA* pUiData ) 
{
	for ( int i = 0 ; i < m_pTarget->size() ; i ++ )
	{
		const CentDedEki* pTarget = m_pTarget->get( i ) ; 
		// 駅名 
		if ( i == 0 )
		{
			pUiData->strEkimei = pTarget->getEkimei() ;
		}
		else if ( pUiData->strEkimei != pTarget->getEkimei() )
		{
			pUiData->strEkimei = _T("") ;
		}

		// 駅時刻形式 
		if ( i == 0 )
		{
			pUiData->iEkijikokukeisiki = (int)pTarget->getEkijikokukeisiki() ;
		}
		else if ( pUiData->iEkijikokukeisiki != (int)pTarget->getEkijikokukeisiki() )
		{
			pUiData->iEkijikokukeisiki = -1 ;	//-1 : 不定
		}
		// 駅規模 
		if ( i == 0 )
		{
			pUiData->iEkikibo = (int)pTarget->getEkikibo() ;
		}
		else if ( pUiData->iEkikibo != (int)pTarget->getEkikibo() )
		{
			pUiData->iEkikibo = -1 ;	//	不定
		}
		// ダイヤグラム列車情報表示（下り）
		if ( i == 0 )
		{
			pUiData->iDiagramRessyajouhouHyoujiKudari = (int)pTarget->getDiagramRessyajouhouHyoujiKudari() ;
		}
		else if ( pUiData->iDiagramRessyajouhouHyoujiKudari != (int)pTarget->getDiagramRessyajouhouHyoujiKudari() )
		{
			pUiData->iDiagramRessyajouhouHyoujiKudari = -1 ;	//-1: 不定
		}
		// ダイヤグラム列車情報表示（上り） 
		if ( i == 0 )
		{
			pUiData->iDiagramRessyajouhouHyoujiNobori = (int)pTarget->getDiagramRessyajouhouHyoujiNobori() ;
		}
		else if ( pUiData->iDiagramRessyajouhouHyoujiNobori != (int)pTarget->getDiagramRessyajouhouHyoujiNobori() )
		{
			pUiData->iDiagramRessyajouhouHyoujiNobori = -1 ;	// 不定
		}
		//分岐駅設定,分岐駅設定の有効無効
		if (m_bBrunchFunctionEnable)
		{
			if (pTarget->getLoopOriginEkiIndex() >= 0)
			{
				pUiData->bBrunchFunctionEnable = false;
				pUiData->bBrunch = false;
				//pUiData->iBrunchCoreEkiIndex = 0;
				pUiData->iBrunchCoreEkiIndex = -1;
				pUiData->bBrunchOpposite = false;
			}
			else
			{
				pUiData->bBrunchFunctionEnable = true;
				pUiData->bBrunch = (pTarget->getBrunchCoreEkiIndex() >= 0);
				if (pUiData->bBrunch)
				{
					pUiData->iBrunchCoreEkiIndex = pTarget->getBrunchCoreEkiIndex();
					pUiData->bBrunchOpposite = pTarget->getBrunchOpposite();
				}
				else
				{
					//pUiData->iBrunchCoreEkiIndex = 0;
					pUiData->iBrunchCoreEkiIndex = -1;
					pUiData->bBrunchOpposite = false;
				}
			}
		}
		else
		{
			pUiData->bBrunchFunctionEnable = false;
			pUiData->bBrunch = false;	//-1: 不定
			pUiData->iBrunchCoreEkiIndex = -1;	//-1: 不定
			pUiData->bBrunchOpposite = false;
		}
		//環状線設定,環状線設定の有効無効
		if (m_bLoopFunctionEnable)
		{
			if (pTarget->getBrunchCoreEkiIndex() >= 0)
			{
				pUiData->bLoopFunctionEnable = false;
				pUiData->bLoop = false;	
				//pUiData->iLoopOriginEkiIndex = 0;
				pUiData->iLoopOriginEkiIndex = -1;
				pUiData->bLoopOpposite = false;
			}
			else
			{
				pUiData->bLoopFunctionEnable = true;
				pUiData->bLoop = (pTarget->getLoopOriginEkiIndex() >= 0);
				if (pUiData->bLoop)
				{
					pUiData->iLoopOriginEkiIndex = pTarget->getLoopOriginEkiIndex();
					pUiData->bLoopOpposite = pTarget->getLoopOpposite();
				}
				else
				{
					//pUiData->iLoopOriginEkiIndex = 0;
					pUiData->iLoopOriginEkiIndex = -1;
					pUiData->bLoopOpposite = false;
				}
			}
		}
		else
		{
			pUiData->bLoopFunctionEnable = false;
			pUiData->bLoop = false;	//-1: 不定
			pUiData->iLoopOriginEkiIndex = -1;	//0: 不定
			pUiData->bLoopOpposite = false;
		}


		//下り時刻表ビュー番線表示
		if (i == 0)
		{
			if ((int)pTarget->getEkijikokukeisiki() == 1 ||
				(int)pTarget->getEkijikokukeisiki() == 2 ||
				(int)pTarget->getEkijikokukeisiki() == 3 ||
				(int)pTarget->getEkijikokukeisiki() == 4)
			{
				pUiData->iJikokuhyouTrackDisplayKudari = (int)pTarget->getJikokuhyouTrackDisplayKudari();
				pUiData->bJikokuhyouTrackDisplayKudariEnable = true;
			}
			else
			{
				pUiData->iJikokuhyouTrackDisplayKudari = 0;
				pUiData->bJikokuhyouTrackDisplayKudariEnable = false;
			}
		}
		else
		{
			pUiData->iJikokuhyouTrackDisplayKudari = 0;
			pUiData->bJikokuhyouTrackDisplayKudariEnable = false;
		}
		//上り時刻表ビュー番線表示
		if (i == 0)
		{
			if ((int)pTarget->getEkijikokukeisiki() == 1 ||
				(int)pTarget->getEkijikokukeisiki() == 2 ||
				(int)pTarget->getEkijikokukeisiki() == 3 ||
				(int)pTarget->getEkijikokukeisiki() == 5)
			{
				pUiData->iJikokuhyouTrackDisplayNobori = (int)pTarget->getJikokuhyouTrackDisplayNobori();
				pUiData->bJikokuhyouTrackDisplayNoboriEnable = true;
			}
			else
			{
				pUiData->iJikokuhyouTrackDisplayNobori = 0;
				pUiData->bJikokuhyouTrackDisplayNoboriEnable = false;
			}
		}
		else
		{
			pUiData->iJikokuhyouTrackDisplayNobori = 0;
			pUiData->bJikokuhyouTrackDisplayNoboriEnable = false;
		}


		//ダイヤグラムビュー番線表示
		if (i == 0)
		{
			if (((int)pTarget->getEkijikokukeisiki() == 1 ||
				(int)pTarget->getEkijikokukeisiki() == 2 || 
				(int)pTarget->getEkijikokukeisiki() == 3 )&&
				(int)pTarget->getEkikibo() == 1)
			{
				pUiData->iDiagramTrackDisplay = (int)pTarget->getDiagramTrackDisplay();
				pUiData->bDiagramTrackDisplayEnable = true;
			}
			else
			{
				pUiData->iDiagramTrackDisplay = 0;
				pUiData->bDiagramTrackDisplayEnable = false;
			}
		}
		else
		{
			pUiData->iDiagramTrackDisplay = 0;
			pUiData->bDiagramTrackDisplayEnable = false;
		}

		//在線表省略設定
		if (i == 0 && m_pTarget->size() == 1)
		{
			pUiData->bDiagramTrackOmit = pTarget->getDiagramTrackOmit();
		}

		// 駅名略称
		if (i == 0)
		{
			pUiData->strEkimeiJikokuhyouRyaku = pTarget->getEkimeiJikokuhyouRyaku(false);
		}
		else if (pUiData->strEkimeiJikokuhyouRyaku != pTarget->getEkimeiJikokuhyouRyaku(false))
		{
			pUiData->strEkimeiJikokuhyouRyaku = _T("");
		}

		// 駅名略称(運用一覧)
		if (i == 0)
		{
			pUiData->strEkimeiDiagramRyaku = pTarget->getEkimeiDiagramRyaku(false);
		}
		else if (pUiData->strEkimeiDiagramRyaku != pTarget->getEkimeiDiagramRyaku(false))
		{
			pUiData->strEkimeiDiagramRyaku = _T("");
		}

		//EkiTrack2
		if (i == 0 && m_pTarget->size() == 1)
		{
			const CentDedEkiTrack2Cont* pCentDedEkiTrack2Cont = pTarget->getEkiTrack2Cont();
			for (int idx = 0; idx < pCentDedEkiTrack2Cont->size(); idx++)
			{
				const CentDedEkiTrack2 aCentDedEkiTrack2 = pCentDedEkiTrack2Cont->get(idx);
				EkiTrack2 aEkiTrack2;
				aEkiTrack2.strTrackName = aCentDedEkiTrack2.getTrackName();
				aEkiTrack2.strTrackRyakusyou = aCentDedEkiTrack2.getTrackRyakusyou();
				aEkiTrack2.strTrackNoboriRyakusyou = aCentDedEkiTrack2.getTrackNoboriRyakusyou();
				//Ver2.0　列車側主本線設定撤廃により、+1処理を削除
				if (pTarget->getDownMain() == idx)
				{
					if (pTarget->getUpMain() == idx)
					{
						//上下主本線
						aEkiTrack2.iMainTrack = 3;
					}
					else
					{
						//下り主本線
						aEkiTrack2.iMainTrack = 1;
					}
				}
				else
				{
					if (pTarget->getUpMain() == idx)
					{
						//上り主本線");
						aEkiTrack2.iMainTrack = 2;
					}
					else
					{
						//副本線/側線");
						aEkiTrack2.iMainTrack = 0;
					}
				}
				pUiData->sEkiTrack2.push_back(aEkiTrack2);
			}
		}
		//OuterTerminalEkimei
		if (i == 0 && m_pTarget->size() == 1)
		{
			int iSize = pTarget->getOuterTerminalEkimeiCount();
			for (int idx = 0; idx < iSize; idx++)
			{
				OuterTerminalEkimei sTemp(
					pTarget->getOuterTerminalEkimei(idx),
					pTarget->getOuterTerminalJikokuRyaku(idx, false),
					pTarget->getOuterTerminalDiaRyaku(idx, false));
				pUiData->sOuterTerminalEkimei.push_back(sTemp);
			}
		}

		// 次駅までの距離 
		if (i == 0)
		{
			pUiData->iNextEkiDistance = pTarget->getNextEkiDistance();
		}
		else if (pUiData->iNextEkiDistance != pTarget->getNextEkiDistance())
		{
			pUiData->iNextEkiDistance = 0;
		}

		//番線表示省略設定
		if (i == 0)
		{
			if ((int)pTarget->getEkijikokukeisiki() == 0 ||
				(int)pTarget->getEkijikokukeisiki() == 4 ||
				(int)pTarget->getEkijikokukeisiki() == 5)
			{
				pUiData->iJikokuhyouTrackOmit = (int)pTarget->getJikokuhyouTrackOmit();
				pUiData->bJikokuhyouTrackOmitEnable = true;
			}
			else
			{
				pUiData->iJikokuhyouTrackOmit = 0;
				pUiData->bJikokuhyouTrackOmitEnable = false;
			}
		}
		else
		{
			pUiData->iJikokuhyouTrackOmit = 0;
			pUiData->bJikokuhyouTrackOmitEnable = false;
		}

		// 作業表示欄設定
		if (i == 0)
		{
			if (pTarget->getEkijikokukeisiki() != CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsu)
			{
				pUiData->bJikokuhyouOperationEnable = true;
				pUiData->iJikokuhyouOperationOrigin = pTarget->getJikokuhyouOperationOrigin();
				pUiData->iJikokuhyouOperationTerminal = pTarget->getJikokuhyouOperationTerminal();
				pUiData->bJikokuhyouOperationOriginDownBeforeUpAfter = pTarget->getJikokuhyouOperationOriginDownBeforeUpAfter();
				pUiData->bJikokuhyouOperationOriginDownAfterUpBefore = pTarget->getJikokuhyouOperationOriginDownAfterUpBefore();
				pUiData->bJikokuhyouOperationTerminalDownBeforeUpAfter = pTarget->getJikokuhyouOperationTerminalDownBeforeUpAfter();
				pUiData->bJikokuhyouOperationTerminalDownAfterUpBefore = pTarget->getJikokuhyouOperationTerminalDownAfterUpBefore();
			}
			else
			{
				pUiData->bJikokuhyouOperationEnable = false;
				pUiData->iJikokuhyouOperationTerminal = 0;
				pUiData->iJikokuhyouOperationOrigin = 0;
				pUiData->bJikokuhyouOperationOriginDownBeforeUpAfter = false;
				pUiData->bJikokuhyouOperationOriginDownAfterUpBefore = false;
				pUiData->bJikokuhyouOperationTerminalDownBeforeUpAfter = false;
				pUiData->bJikokuhyouOperationTerminalDownAfterUpBefore = false;
			}
		}
		else
		{
			pUiData->bJikokuhyouOperationEnable = false;
			pUiData->iJikokuhyouOperationTerminal = 0;
			pUiData->iJikokuhyouOperationOrigin = 0;
			pUiData->bJikokuhyouOperationOriginDownBeforeUpAfter = false;
			pUiData->bJikokuhyouOperationOriginDownAfterUpBefore = false;
			pUiData->bJikokuhyouOperationTerminalDownBeforeUpAfter = false;
			pUiData->bJikokuhyouOperationTerminalDownAfterUpBefore = false;
		}

		//下り時刻表ビュー着時刻表示
		if (i == 0)
		{
			if (pTarget->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
				pTarget->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
				pTarget->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku)
			{
				pUiData->bJikokuhyouChakuJikokuDisplayKudariEnable = true;
				pUiData->bJikokuhyouChakuJikokuDisplayKudari =
					pTarget->getJikokuhyouChakuJikokuDisplayKudari();
			}
			else
			{
				pUiData->bJikokuhyouChakuJikokuDisplayKudariEnable = false;
				pUiData->bJikokuhyouChakuJikokuDisplayKudari = false;
			}
		}
		else
		{
			pUiData->bJikokuhyouChakuJikokuDisplayKudariEnable = false;
			pUiData->bJikokuhyouChakuJikokuDisplayKudari = false;
		}
		//上り時刻表ビュー着時刻表示
		if (i == 0)
		{
			if (pTarget->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
				pTarget->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ||
				pTarget->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
			{
				pUiData->bJikokuhyouChakuJikokuDisplayNoboriEnable = true;
				pUiData->bJikokuhyouChakuJikokuDisplayNobori =
					pTarget->getJikokuhyouChakuJikokuDisplayNobori();
			}
			else
			{
				pUiData->bJikokuhyouChakuJikokuDisplayNoboriEnable = false;
				pUiData->bJikokuhyouChakuJikokuDisplayNobori = false;
			}
		}
		else
		{
			pUiData->bJikokuhyouChakuJikokuDisplayNoboriEnable = false;
			pUiData->bJikokuhyouChakuJikokuDisplayNobori = false;
		}

		//下り時刻表ビュー発時刻表示
		if (i == 0)
		{
			if (pTarget->getEkijikokukeisiki() != CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku)
			{
				pUiData->bJikokuhyouHatsuJikokuDisplayKudariEnable = true;
				pUiData->bJikokuhyouHatsuJikokuDisplayKudari =
					pTarget->getJikokuhyouHatsuJikokuDisplayKudari();
			}
			else
			{
				pUiData->bJikokuhyouHatsuJikokuDisplayKudariEnable = false;
				pUiData->bJikokuhyouHatsuJikokuDisplayKudari = false;
			}
		}
		else
		{
			pUiData->bJikokuhyouHatsuJikokuDisplayKudariEnable = false;
			pUiData->bJikokuhyouHatsuJikokuDisplayKudari = false;
		}

		//上り時刻表ビュー発時刻表示
		if (i == 0)
		{
			if (pTarget->getEkijikokukeisiki() != CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku)
			{
				pUiData->bJikokuhyouHatsuJikokuDisplayNoboriEnable = true;
				pUiData->bJikokuhyouHatsuJikokuDisplayNobori =
					pTarget->getJikokuhyouHatsuJikokuDisplayNobori();
			}
			else
			{
				pUiData->bJikokuhyouHatsuJikokuDisplayNoboriEnable = false;
				pUiData->bJikokuhyouHatsuJikokuDisplayNobori = false;
			}
		}
		else
		{
			pUiData->bJikokuhyouHatsuJikokuDisplayNoboriEnable = false;
			pUiData->bJikokuhyouHatsuJikokuDisplayNobori = false;
		}

		//下り時刻表ビュー種別変更表示
		if (i == 0)
		{
			if (pTarget->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
				pTarget->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ||
				pTarget->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku)
			{
				pUiData->bJikokuhyouSyubetsuChangeDisplayKudariEnable = true;
				pUiData->iJikokuhyouRessyabangouDisplayKudari =
					pTarget->getJikokuhyouRessyabangouDisplayKudari();
				pUiData->iJikokuhyouOperationNumberDisplayKudari =
					pTarget->getJikokuhyouOperationNumberDisplayKudari();
				pUiData->iJikokuhyouOperationNumberDisplayRowsKudari =
					pTarget->getJikokuhyouOperationNumberDisplayRowsKudari() - 1;
				pUiData->iJikokuhyouRessyaSyubetsuDisplayKudari =
					pTarget->getJikokuhyouRessyaSyubetsuDisplayKudari();
				pUiData->iJikokuhyouRessyameiDisplayKudari =
					pTarget->getJikokuhyouRessyameiDisplayKudari();
			}
			else
			{
				pUiData->bJikokuhyouSyubetsuChangeDisplayKudariEnable = false;
				pUiData->iJikokuhyouRessyabangouDisplayKudari = 0;
				pUiData->iJikokuhyouOperationNumberDisplayKudari = 0;
				pUiData->iJikokuhyouOperationNumberDisplayRowsKudari =0;
				pUiData->iJikokuhyouRessyaSyubetsuDisplayKudari = 0;
				pUiData->iJikokuhyouRessyameiDisplayKudari = 0;
			}
		}
		else
		{
			pUiData->bJikokuhyouSyubetsuChangeDisplayKudariEnable = false;
			pUiData->iJikokuhyouRessyabangouDisplayKudari = 0;
			pUiData->iJikokuhyouOperationNumberDisplayKudari = 0;
			pUiData->iJikokuhyouOperationNumberDisplayRowsKudari = 0;
			pUiData->iJikokuhyouRessyaSyubetsuDisplayKudari = 0;
			pUiData->iJikokuhyouRessyameiDisplayKudari = 0;
		}
		//上り時刻表ビュー種別変更表示
		if (i == 0)
		{
			if (pTarget->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
				pTarget->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
				pTarget->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
			{
				pUiData->bJikokuhyouSyubetsuChangeDisplayNoboriEnable = true;
				pUiData->iJikokuhyouRessyabangouDisplayNobori =
					pTarget->getJikokuhyouRessyabangouDisplayNobori();
				pUiData->iJikokuhyouOperationNumberDisplayNobori =
					pTarget->getJikokuhyouOperationNumberDisplayNobori();
				pUiData->iJikokuhyouOperationNumberDisplayRowsNobori =
					pTarget->getJikokuhyouOperationNumberDisplayRowsNobori() - 1;
				pUiData->iJikokuhyouRessyaSyubetsuDisplayNobori =
					pTarget->getJikokuhyouRessyaSyubetsuDisplayNobori();
				pUiData->iJikokuhyouRessyameiDisplayNobori =
					pTarget->getJikokuhyouRessyameiDisplayNobori();
			}
			else
			{
				pUiData->bJikokuhyouSyubetsuChangeDisplayNoboriEnable = false;
				pUiData->iJikokuhyouRessyabangouDisplayNobori = 0;
				pUiData->iJikokuhyouOperationNumberDisplayNobori = 0;
				pUiData->iJikokuhyouOperationNumberDisplayRowsNobori = 0;
				pUiData->iJikokuhyouRessyaSyubetsuDisplayNobori = 0;
				pUiData->iJikokuhyouRessyameiDisplayNobori = 0;
			}
		}
		else
		{
			pUiData->bJikokuhyouSyubetsuChangeDisplayNoboriEnable = false;
			pUiData->iJikokuhyouRessyabangouDisplayNobori = 0;
			pUiData->iJikokuhyouOperationNumberDisplayNobori = 0;
			pUiData->iJikokuhyouOperationNumberDisplayRowsNobori = 0;
			pUiData->iJikokuhyouRessyaSyubetsuDisplayNobori = 0;
			pUiData->iJikokuhyouRessyameiDisplayNobori = 0;
		}
		// ダイヤグラム背景色
		if (i == 0)
		{
			pUiData->iDiagramColorNextEki = pTarget->getDiagramColorNextEki();
		}
		else if (pUiData->iDiagramColorNextEki != pTarget->getDiagramColorNextEki())
		{
			pUiData->iDiagramColorNextEki = -1;	// 不定
		}

		// 箱ダイヤで表示するか否か 
		if (i == 0)
		{
			if (pTarget->getBrunchCoreEkiIndex() == -1)
			{
				//pUiData->bOperationTableDisplayJikokuEnable = true;
				pUiData->bOperationTableDisplayJikoku = pTarget->getOperationTableDisplayJikoku();
			}
			else
			{
				//pUiData->bOperationTableDisplayJikokuEnable = false;
				pUiData->bOperationTableDisplayJikoku = false;
			}
		}
		else
		{
			pUiData->bOperationTableDisplayJikokuEnable = false;
			pUiData->bOperationTableDisplayJikoku = false;
		}

		//下りカスタマイズ時刻表ビューの路線外・前列車始発駅表示
		if (i == 0)
		{
			if (pTarget->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
				pTarget->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ||
				pTarget->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku)
			{
				pUiData->bJikokuhyouOuterSihatsuDisplayKudariEnable = true;
				pUiData->bJikokuhyouOuterSihatsuDisplayKudari =
					pTarget->getJikokuhyouOuterSihatsuDisplayKudari();
			}
			else
			{
				pUiData->bJikokuhyouOuterSihatsuDisplayKudariEnable = false;
				pUiData->bJikokuhyouOuterSihatsuDisplayKudari = false;
			}
		}
		else
		{
			pUiData->bJikokuhyouOuterSihatsuDisplayKudariEnable = false;
			pUiData->bJikokuhyouOuterSihatsuDisplayKudari = false;
		}
		//下りカスタマイズ時刻表ビューの路線外・次列車終着駅表示
		if (i == 0)
		{
			if (pTarget->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
				pTarget->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
				pTarget->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku)
			{
				pUiData->bJikokuhyouOuterShuchakuDisplayKudariEnable = true;
				pUiData->bJikokuhyouOuterShuchakuDisplayKudari =
					pTarget->getJikokuhyouOuterShuchakuDisplayKudari();
			}
			else
			{
				pUiData->bJikokuhyouOuterShuchakuDisplayKudariEnable = false;
				pUiData->bJikokuhyouOuterShuchakuDisplayKudari = false;
			}
		}
		else
		{
			pUiData->bJikokuhyouOuterShuchakuDisplayKudariEnable = false;
			pUiData->bJikokuhyouOuterShuchakuDisplayKudari = false;
		}
		//上りカスタマイズ時刻表ビュー路線外・前列車始発駅表示
		if (i == 0)
		{
			if (pTarget->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
				pTarget->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ||
				pTarget->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
			{
				pUiData->bJikokuhyouOuterSihatsuDisplayNoboriEnable = true;
				pUiData->bJikokuhyouOuterSihatsuDisplayNobori =
					pTarget->getJikokuhyouOuterSihatsuDisplayNobori();
			}
			else
			{
				pUiData->bJikokuhyouOuterSihatsuDisplayNoboriEnable = false;
				pUiData->bJikokuhyouOuterSihatsuDisplayNobori = false;
			}
		}
		else
		{
			pUiData->bJikokuhyouOuterSihatsuDisplayNoboriEnable = false;
			pUiData->bJikokuhyouOuterSihatsuDisplayNobori = false;
		}
		//上りカスタマイズ時刻表ビュー路線外・次列車終着駅表示
		if (i == 0)
		{
			if (pTarget->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ||
				pTarget->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ||
				pTarget->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku)
			{
				pUiData->bJikokuhyouOuterShuchakuDisplayNoboriEnable = true;
				pUiData->bJikokuhyouOuterShuchakuDisplayNobori =
					pTarget->getJikokuhyouOuterShuchakuDisplayNobori();
			}
			else
			{
				pUiData->bJikokuhyouOuterShuchakuDisplayNoboriEnable = false;
				pUiData->bJikokuhyouOuterShuchakuDisplayNobori = false;
			}
		}
		else
		{
			pUiData->bJikokuhyouOuterShuchakuDisplayNoboriEnable = false;
			pUiData->bJikokuhyouOuterShuchakuDisplayNobori = false;
		}
	}

	// [駅時刻を駅時刻形式で正規化]の設定
	pUiData->bAdjustByEkijikokukeisiki = *m_pbAdjustByEkijikokukeisiki ;
}
	
void CPropEditUi_Eki::AdjustUiData( 
		UIDATA* pUiData , 
		const UIDATA* pUiDataPrev , 
		bool bStartEdit )
{
	/* 駅名 */
	if ( bStartEdit || pUiDataPrev->strEkimei != pUiData->strEkimei)
	{
		// pUiData->メンバー名 の正規化を行うコード。
	}
	/* 駅時刻形式 */
	if ( bStartEdit || pUiDataPrev->iEkijikokukeisiki != pUiData->iEkijikokukeisiki)
	{
		if (pUiData->iEkikibo == 1 && /*!pUiData->bBrunch &&*/
			m_pTarget->size() == 1 &&
			(pUiData->iEkijikokukeisiki == 1 ||
				pUiData->iEkijikokukeisiki == 2 ||
				pUiData->iEkijikokukeisiki == 3))
		{
			pUiData->bDiagramTrackDisplayEnable = true;
		}
		else
		{
			pUiData->bDiagramTrackDisplayEnable = false;
		}

		if (m_pTarget->size() == 1 &&
			(pUiData->iEkijikokukeisiki == 1 ||
			pUiData->iEkijikokukeisiki == 2 ||
			pUiData->iEkijikokukeisiki == 3 ||
			pUiData->iEkijikokukeisiki == 4 )
			)
		{
			pUiData->bJikokuhyouTrackDisplayKudariEnable = true;
		}
		else if (pUiData->iEkijikokukeisiki == 0 ||
			pUiData->iEkijikokukeisiki == 5)
		{
			pUiData->bJikokuhyouTrackDisplayKudariEnable = false;
		}

		if (m_pTarget->size() == 1 &&
			(pUiData->iEkijikokukeisiki == 1 ||
				pUiData->iEkijikokukeisiki == 2 ||
				pUiData->iEkijikokukeisiki == 3 ||
				pUiData->iEkijikokukeisiki == 5)
			)
		{
			pUiData->bJikokuhyouTrackDisplayNoboriEnable = true;
		}
		else if (pUiData->iEkijikokukeisiki == 0 ||
			pUiData->iEkijikokukeisiki == 4)
		{
			pUiData->bJikokuhyouTrackDisplayNoboriEnable = false;
		}

		if (m_pTarget->size() == 1 &&
			(pUiData->iEkijikokukeisiki == 0 ||
				pUiData->iEkijikokukeisiki == 4 ||
				pUiData->iEkijikokukeisiki == 5)
			)
		{
			pUiData->bJikokuhyouTrackOmitEnable = true;
		}
		else if (pUiData->iEkijikokukeisiki == 1 ||
			pUiData->iEkijikokukeisiki == 2 ||
			pUiData->iEkijikokukeisiki == 3)
		{
			pUiData->bJikokuhyouTrackOmitEnable = false;
		}

		if (m_pTarget->size() == 1 &&
			pUiData->iEkijikokukeisiki != 0 )
		{
			pUiData->bJikokuhyouOperationEnable = true;
		}
		else
		{
			pUiData->bJikokuhyouOperationEnable = false;
		}
		
		if (m_pTarget->size() == 1 &&
			(pUiData->iEkijikokukeisiki == 1 ||
			pUiData->iEkijikokukeisiki == 2 ||
			pUiData->iEkijikokukeisiki == 4 ))
		{
			pUiData->bJikokuhyouChakuJikokuDisplayKudariEnable = true;
			if (pUiData->iEkijikokukeisiki == 2)
			{
				pUiData->bJikokuhyouChakuJikokuDisplayKudari = true;
			}
		}
		else
		{
			pUiData->bJikokuhyouChakuJikokuDisplayKudariEnable = false;
		}

		if (m_pTarget->size() == 1 &&
			(pUiData->iEkijikokukeisiki == 1 ||
				pUiData->iEkijikokukeisiki == 3 ||
				pUiData->iEkijikokukeisiki == 5))
		{
			pUiData->bJikokuhyouChakuJikokuDisplayNoboriEnable = true;
			if (pUiData->iEkijikokukeisiki == 3)
			{
				pUiData->bJikokuhyouChakuJikokuDisplayNobori = true;
			}
		}
		else
		{
			pUiData->bJikokuhyouChakuJikokuDisplayNoboriEnable = false;
		}

		if (m_pTarget->size() == 1 &&
			pUiData->iEkijikokukeisiki != 2)
		{
			pUiData->bJikokuhyouHatsuJikokuDisplayKudariEnable = true;
			if (pUiData->iEkijikokukeisiki == 0 || 
				pUiData->iEkijikokukeisiki == 3 ||
				pUiData->iEkijikokukeisiki == 5)
			{
				pUiData->bJikokuhyouHatsuJikokuDisplayKudari = true;
			}
		}
		else
		{
			pUiData->bJikokuhyouHatsuJikokuDisplayKudariEnable = false;
		}

		if (m_pTarget->size() == 1 &&
			pUiData->iEkijikokukeisiki != 3)
		{
			pUiData->bJikokuhyouHatsuJikokuDisplayNoboriEnable = true;
			if (pUiData->iEkijikokukeisiki == 0 ||
				pUiData->iEkijikokukeisiki == 2 ||
				pUiData->iEkijikokukeisiki == 4)
			{
				pUiData->bJikokuhyouHatsuJikokuDisplayNobori = true;
			}
		}
		else
		{
			pUiData->bJikokuhyouHatsuJikokuDisplayNoboriEnable = false;
		}

		if (m_pTarget->size() == 1 &&
			(pUiData->iEkijikokukeisiki == 1 ||
				pUiData->iEkijikokukeisiki == 3 ||
				pUiData->iEkijikokukeisiki == 4))
		{
			pUiData->bJikokuhyouSyubetsuChangeDisplayKudariEnable = true;
		}
		else
		{
			pUiData->bJikokuhyouSyubetsuChangeDisplayKudariEnable = false;
		}

		if (m_pTarget->size() == 1 &&
			(pUiData->iEkijikokukeisiki == 1 ||
				pUiData->iEkijikokukeisiki == 2 ||
				pUiData->iEkijikokukeisiki == 5))
		{
			pUiData->bJikokuhyouSyubetsuChangeDisplayNoboriEnable = true;
		}
		else
		{
			pUiData->bJikokuhyouSyubetsuChangeDisplayNoboriEnable = false;
		}

		if (m_pTarget->size() == 1 &&
			(pUiData->iEkijikokukeisiki == 1 ||
				pUiData->iEkijikokukeisiki == 3 ||
				pUiData->iEkijikokukeisiki == 4))
		{
			pUiData->bJikokuhyouOuterSihatsuDisplayKudariEnable = true;
		}
		else
		{
			pUiData->bJikokuhyouOuterSihatsuDisplayKudariEnable = false;
		}

		if (m_pTarget->size() == 1 &&
			(pUiData->iEkijikokukeisiki == 1 ||
				pUiData->iEkijikokukeisiki ==2 ||
				pUiData->iEkijikokukeisiki == 4))
		{
			pUiData->bJikokuhyouOuterShuchakuDisplayKudariEnable = true;
		}
		else
		{
			pUiData->bJikokuhyouOuterShuchakuDisplayKudariEnable = false;
		}

		if (m_pTarget->size() == 1 &&
			(pUiData->iEkijikokukeisiki == 1 ||
				pUiData->iEkijikokukeisiki == 2 ||
				pUiData->iEkijikokukeisiki == 5))
		{
			pUiData->bJikokuhyouOuterSihatsuDisplayNoboriEnable = true;
		}
		else
		{
			pUiData->bJikokuhyouOuterSihatsuDisplayNoboriEnable = false;
		}

		if (m_pTarget->size() == 1 &&
			(pUiData->iEkijikokukeisiki == 1 ||
				pUiData->iEkijikokukeisiki == 3 ||
				pUiData->iEkijikokukeisiki == 5))
		{
			pUiData->bJikokuhyouOuterShuchakuDisplayNoboriEnable = true;
		}
		else
		{
			pUiData->bJikokuhyouOuterShuchakuDisplayNoboriEnable = false;
		}
	}
	/* 駅規模 */
	if ( bStartEdit || pUiDataPrev->iEkikibo != pUiData->iEkikibo)
	{
		// pUiData->メンバー名 の正規化を行うコード。
		if (pUiData->iEkikibo == 1 &&/* !pUiData->bBrunch &&*/
			m_pTarget->size() == 1 &&
			(pUiData->iEkijikokukeisiki == 1 ||
			pUiData->iEkijikokukeisiki == 2 ||
			pUiData->iEkijikokukeisiki == 3))
		{
			pUiData->bDiagramTrackDisplayEnable = true;
		}
		else
		{
			pUiData->bDiagramTrackDisplayEnable = false;
		}
	}

	/* ダイヤグラム列車情報表示（下り） */
	if ( bStartEdit || pUiDataPrev->iDiagramRessyajouhouHyoujiKudari != pUiData->iDiagramRessyajouhouHyoujiKudari)
	{
		// pUiData->メンバー名 の正規化を行うコード。
	}

	/* ダイヤグラム列車情報表示（上り） */
	if ( bStartEdit || pUiDataPrev->iDiagramRessyajouhouHyoujiNobori != pUiData->iDiagramRessyajouhouHyoujiNobori)
	{
		// pUiData->メンバー名 の正規化を行うコード。
	}

	/*	[駅時刻を駅時刻形式で正規化]の設定です。*/
	if ( bStartEdit || pUiDataPrev->bAdjustByEkijikokukeisiki != pUiData->bAdjustByEkijikokukeisiki)
	{
		// pUiData->メンバー名 の正規化を行うコード。
	}

	//分岐駅設定
	if (bStartEdit || pUiDataPrev->bBrunch != pUiData->bBrunch)
	{
		//if (pUiData->iEkikibo == 1 && !pUiData->bBrunch &&
		//	m_pTarget->size() == 1 &&
		//	(pUiData->iEkijikokukeisiki == 1 ||
		//		pUiData->iEkijikokukeisiki == 2 ||
		//		pUiData->iEkijikokukeisiki == 3))
		//{
		//	pUiData->bDiagramTrackDisplayEnable = true;
		//}
		//else
		//{
		//	pUiData->bDiagramTrackDisplayEnable = false;
		//}

		if (pUiData->bBrunch)
		{
			pUiData->iEkikibo = 1;//主要駅にする。
			//駅時刻形式が上り着以外の場合、値を下り着に。
			if (pUiData->iEkijikokukeisiki != 3 )
			{
				pUiData->iEkijikokukeisiki = 2;
			}
			if (m_bLoopFunctionEnable)
			{
				pUiData->bLoopFunctionEnable = false;
			}
		}
		else
		{
			if (m_bLoopFunctionEnable)
			{
				pUiData->bLoopFunctionEnable = true;
			}
		}
	}
	//分岐駅設定基幹駅Index
	if (bStartEdit || pUiDataPrev->iBrunchCoreEkiIndex != pUiData->iBrunchCoreEkiIndex)
	{

	}
	//環状線設定
	if (bStartEdit || pUiDataPrev->bLoop != pUiData->bLoop)
	{
		if (pUiData->bLoop)
		{
			pUiData->iEkikibo = 1;//主要駅にする。
								  //駅時刻形式が下り着以外の場合、値を発着に。
			if (pUiData->iEkijikokukeisiki != 2)
			{
				pUiData->iEkijikokukeisiki = 1;
			}
			if (m_bBrunchFunctionEnable)
			{
				pUiData->bBrunchFunctionEnable = false;
			}
		}
		else
		{
			if (m_bBrunchFunctionEnable)
			{
				pUiData->bBrunchFunctionEnable = true;
			}

		}
	}
	//環状線Index
	if (bStartEdit || pUiDataPrev->iLoopOriginEkiIndex != pUiData->iLoopOriginEkiIndex)
	{

	}
	//下り時刻表ビュー番線表示
	if (bStartEdit || pUiDataPrev->iJikokuhyouTrackDisplayKudari != pUiData->iJikokuhyouTrackDisplayKudari)
	{
	}
	//上り時刻表ビュー番線表示
	if (bStartEdit || pUiDataPrev->iJikokuhyouTrackDisplayNobori != pUiData->iJikokuhyouTrackDisplayNobori)
	{
	}
	//ダイヤグラムビュー番線表示
	if (bStartEdit || pUiDataPrev->bDiagramTrackDisplayEnable != pUiData->bDiagramTrackDisplayEnable)
	{
	}
	//下り時刻表ビュー着時刻表示
	/**
		着時刻表示がfalseになったとき、発時刻設定自体がfalseもしくは、発時刻表示がfalseの場合は、着時刻表示をtrueに戻します。
		(着時刻か発時刻のいずれかがtrueである必要があります)
	*/
	if (bStartEdit ||(pUiDataPrev->bJikokuhyouChakuJikokuDisplayKudari != pUiData->bJikokuhyouChakuJikokuDisplayKudari &&
		!pUiData->bJikokuhyouChakuJikokuDisplayKudari))
	{
		if (!pUiData->bJikokuhyouHatsuJikokuDisplayKudariEnable ||
			!pUiData->bJikokuhyouHatsuJikokuDisplayKudari)
		{
			pUiData->bJikokuhyouChakuJikokuDisplayKudari = true;
		}
	}
	//下り時刻表ビュー発時刻表示
	if (bStartEdit || (pUiDataPrev->bJikokuhyouHatsuJikokuDisplayKudari != pUiData->bJikokuhyouHatsuJikokuDisplayKudari &&
		!pUiData->bJikokuhyouHatsuJikokuDisplayKudari))
	{
		if (!pUiData->bJikokuhyouChakuJikokuDisplayKudariEnable ||
			!pUiData->bJikokuhyouChakuJikokuDisplayKudari)
		{
			pUiData->bJikokuhyouHatsuJikokuDisplayKudari = true;
		}
	}
	//上り時刻表ビュー着時刻表示
	if (bStartEdit || (pUiDataPrev->bJikokuhyouChakuJikokuDisplayNobori != pUiData->bJikokuhyouChakuJikokuDisplayNobori &&
		!pUiData->bJikokuhyouChakuJikokuDisplayNobori))
	{
		if (!pUiData->bJikokuhyouHatsuJikokuDisplayNoboriEnable ||
			!pUiData->bJikokuhyouHatsuJikokuDisplayNobori)
		{
			pUiData->bJikokuhyouChakuJikokuDisplayNobori = true;
		}
	}
	//上り時刻表ビュー発時刻表示
	if (bStartEdit || (pUiDataPrev->bJikokuhyouHatsuJikokuDisplayNobori != pUiData->bJikokuhyouHatsuJikokuDisplayNobori &&
		!pUiData->bJikokuhyouHatsuJikokuDisplayNobori))
	{
		if (!pUiData->bJikokuhyouChakuJikokuDisplayNoboriEnable ||
			!pUiData->bJikokuhyouChakuJikokuDisplayNobori)
		{
			pUiData->bJikokuhyouHatsuJikokuDisplayNobori = true;
		}
	}

	//箱ダイヤ表示設定
	if (pUiData->bBrunch)
	{
		pUiData->bOperationTableDisplayJikoku = false;
	}
}

int CPropEditUi_Eki::CheckUiData( 
		bool bNewItem , 
		const UIDATA* pUiData , 
		const UIDATA* pUiDataStartEdit ) 
{
	int iRv = 0 ; 
	/* 駅名 */
	if ( iRv >= 0 )
	{
		if ( bNewItem || pUiDataStartEdit->strEkimei != pUiData->strEkimei)
		{
			if ( pUiData->strEkimei.length() > 58 )
			{
				ShowError( ERRMSG_EKIMEI_TOO_LONG ) ;
				SetFocus( offsetof( UIDATA , strEkimei )) ;
				iRv = -1 ;	//	駅名が長すぎます。
			}
			else if (pUiData->strEkimei.length() == 0)
			{
				iRv = -1;      //  駅名が指定されていません
				ShowError(ERRMSG_EKIMEI_EMPTY);
				SetFocus(offsetof(UIDATA, strEkimei));
			}
		}
	}
	/* 駅時刻形式 */
	if ( iRv >= 0 )
	{
		if ( bNewItem || pUiDataStartEdit->iEkijikokukeisiki != pUiData->iEkijikokukeisiki)
		{
			// pUiData->メンバー名 のエラーチェックを行うコード。
		}
	}
	/* 駅規模 */
	if ( iRv >= 0 )
	{
		if ( bNewItem || pUiDataStartEdit->iEkikibo != pUiData->iEkikibo)
		{
			// pUiData->メンバー名 のエラーチェックを行うコード。
		}
	}
	/* ダイヤグラム列車情報表示（下り） */
	if ( iRv >= 0 )
	{
		if ( bNewItem || pUiDataStartEdit->iDiagramRessyajouhouHyoujiKudari != pUiData->iDiagramRessyajouhouHyoujiKudari)
		{
			// pUiData->メンバー名 のエラーチェックを行うコード。
		}
	}
	/* ダイヤグラム列車情報表示（上り） */
	if ( iRv >= 0 )
	{
		if ( bNewItem || pUiDataStartEdit->iDiagramRessyajouhouHyoujiNobori != pUiData->iDiagramRessyajouhouHyoujiNobori)
		{
			// pUiData->メンバー名 のエラーチェックを行うコード。
		}
	}
	/*	[駅時刻を駅時刻形式で正規化]の設定です。*/
	if ( iRv >= 0 )
	{
		if ( bNewItem || pUiDataStartEdit->bAdjustByEkijikokukeisiki != pUiData->bAdjustByEkijikokukeisiki)
		{
			// pUiData->メンバー名 のエラーチェックを行うコード。
		}
	}
	//分岐駅設定
	if (iRv >= 0 && m_pTarget->size() == 1)
	{
		if (pUiData->bBrunch)
		{
			if (pUiData->iBrunchCoreEkiIndex < 0)
			{
				ShowError(ERRMSG_BRUNCH_EKIINDEX);
				SetFocus(offsetof(UIDATA, iBrunchCoreEkiIndex));
				iRv = -2;//分岐駅設定ONの時は、基幹駅を指定してください。
			}
			//当駅と対象駅のインデクスを比較、大小関係によって、駅時刻扱いの判定を行う
			else if (m_iEkiIndex > pUiData->iBrunchCoreEkiIndex)
			{
				if (pUiData->iEkijikokukeisiki != 3)//3=上り着時刻
				{
					ShowError(ERRMSG_BRUNCH_EKIJIKOKUKEISIKI_UPCHAKU);
					SetFocus(offsetof(UIDATA, iEkijikokukeisiki));
					iRv = -3;//分岐駅設定ONの時は、駅時刻形式を上り着にしてください。
				}
			}
			else if (m_iEkiIndex < pUiData->iBrunchCoreEkiIndex)
			{
				if (pUiData->iEkijikokukeisiki != 2)//2=下り着時刻
				{
					ShowError(ERRMSG_BRUNCH_EKIJIKOKUKEISIKI_DOWNCHAKU);
					SetFocus(offsetof(UIDATA, iEkijikokukeisiki));
					iRv = -4;//分岐駅設定ONの時は、駅時刻形式を下り着にしてください。
				}
			}

			if (pUiData->iEkikibo != 1)
			{
				ShowError(ERRMSG_BRUNCH_EKIKIBO);
				SetFocus(offsetof(UIDATA, iEkikibo));
				iRv = -5;//分岐駅設定ONの時は、駅規模は主要駅にしてください
			}
		}
	}
	//環状線設定
	if (iRv >= 0 && m_pTarget->size() == 1)
	{
		if (pUiData->bLoop)
		{
			if (pUiData->iLoopOriginEkiIndex < 0)
			{
				ShowError(ERRMSG_LOOP_EKIINDEX);
				SetFocus(offsetof(UIDATA, iLoopOriginEkiIndex));
				iRv = -2;//環状線設定ONの時は、起点駅を指定してください。
			}

			//駅時刻扱いの判定を行う
			if (pUiData->iEkijikokukeisiki != 1 && //1=発着
				pUiData->iEkijikokukeisiki != 2)//3=下り着時刻
			{
				ShowError(ERRMSG_LOOP_EKIJIKOKUKEISIKI_HATSUCHAKU_DOWNCHAKU);
				SetFocus(offsetof(UIDATA, iEkijikokukeisiki));
				iRv = -3;//環状線設定ONの時は、駅時刻形式を発着または上り着にしてください。
			}

			if (pUiData->iEkikibo != 1)
			{
				ShowError(ERRMSG_LOOP_EKIKIBO);
				SetFocus(offsetof(UIDATA, iEkikibo));
				iRv = -5;//環状線設定ONの時は、駅規模は主要駅にしてください
			}
		}
	}
	/* 駅名略称 */
	if (iRv >= 0)
	{
		if (bNewItem || pUiDataStartEdit->strEkimeiJikokuhyouRyaku != pUiData->strEkimeiJikokuhyouRyaku)
		{
			if (pUiData->strEkimeiJikokuhyouRyaku.length() > 58)
			{
				ShowError(ERRMSG_EKIMEIJIKOKUHYOURYAKU_TOO_LONG);
				SetFocus(offsetof(UIDATA, strEkimeiJikokuhyouRyaku));
				iRv = -1;	//	駅名が長すぎます。
			}
		}
	}
	/* 駅名略称(運用一覧) */
	if (iRv >= 0)
	{
		if (bNewItem || pUiDataStartEdit->strEkimeiDiagramRyaku != pUiData->strEkimeiDiagramRyaku)
		{
			if (pUiData->strEkimeiDiagramRyaku.length() > 58)
			{
				ShowError(ERRMSG_EKIMEIDIAGRAMRYAKU_TOO_LONG);
				SetFocus(offsetof(UIDATA, strEkimeiDiagramRyaku));
				iRv = -1;	//	駅名が長すぎます。
			}
		}
	}
	return iRv ;
}




int CPropEditUi_Eki::UiDataToTarget( 
		bool bNewItem , 
		const UIDATA* pUiData , 
		const UIDATA* pUiDataStartEdit ) 
{
	int iRv = 0 ;
	for ( int i = 0 ; iRv >= 0 && i < m_pTarget->size() ; i ++ )
	{
		CentDedEki* pTarget= m_pTarget->get( i ) ; 
		/* 駅名 */
		if ( bNewItem || pUiDataStartEdit->strEkimei != pUiData->strEkimei)
		{
			pTarget->setEkimei( pUiData->strEkimei ) ;
		}
		/* 駅時刻形式 */
		if ( bNewItem || pUiDataStartEdit->iEkijikokukeisiki != pUiData->iEkijikokukeisiki)
		{
			pTarget->setEkijikokukeisiki( 
				(CentDedEki::EEkijikokukeisiki)pUiData->iEkijikokukeisiki ) ;
		}
		/* 駅規模 */
		if ( bNewItem || pUiDataStartEdit->iEkikibo != pUiData->iEkikibo)
		{
			pTarget->setEkikibo( (CentDedEki::EEkikibo)pUiData->iEkikibo ) ;
		}
		/* ダイヤグラム列車情報表示（下り） */
		if ( bNewItem || pUiDataStartEdit->iDiagramRessyajouhouHyoujiKudari != pUiData->iDiagramRessyajouhouHyoujiKudari)
		{
			pTarget->setDiagramRessyajouhouHyoujiKudari(
				(CentDedEki::EDiagramRessyajouhouHyouji)pUiData->iDiagramRessyajouhouHyoujiKudari ) ;
		}
		/* ダイヤグラム列車情報表示（上り） */
		if ( bNewItem || pUiDataStartEdit->iDiagramRessyajouhouHyoujiNobori != pUiData->iDiagramRessyajouhouHyoujiNobori)
		{
			pTarget->setDiagramRessyajouhouHyoujiNobori(
				(CentDedEki::EDiagramRessyajouhouHyouji)pUiData->iDiagramRessyajouhouHyoujiNobori ) ;
		}

		//分岐駅設定
		if (m_pTarget->size() == 1)
		{
			if (pUiData->bBrunchFunctionEnable)
			{
				if (pUiData->bBrunch)
				{
					pTarget->setBrunchCoreEkiIndex(pUiData->iBrunchCoreEkiIndex);
					pTarget->setBrunchOpposite(pUiData->bBrunchOpposite);
				}
				else
				{
					pTarget->setBrunchCoreEkiIndex(-1);
					pTarget->setBrunchOpposite(false);
				}
			}
			else
			{
				pTarget->setBrunchCoreEkiIndex(-1);
				pTarget->setBrunchOpposite(false);
			}
		}
		//環状線設定
		if (m_pTarget->size() == 1)
		{
			if (pUiData->bLoopFunctionEnable)
			{
				if (pUiData->bLoop)
				{
					pTarget->setLoopOriginEkiIndex(pUiData->iLoopOriginEkiIndex);
					pTarget->setLoopOpposite(pUiData->bLoopOpposite);
				}
				else
				{
					pTarget->setLoopOriginEkiIndex(-1);
					pTarget->setLoopOpposite(false);
				}
			}
			else
			{
				pTarget->setLoopOriginEkiIndex(-1);
				pTarget->setLoopOpposite(false);
			}
		}
		//下り時刻表ビュー番線表示
		if (m_pTarget->size() == 1)
		{
			if (pUiData->bJikokuhyouTrackDisplayKudariEnable)
			{
				pTarget->setJikokuhyouTrackDisplayKudari(pUiData->iJikokuhyouTrackDisplayKudari != 0);
			}
			else
			{
				pTarget->setJikokuhyouTrackDisplayKudari(false);
			}
		}
		//else if ( pUiDataStartEdit->iJikokuhyouTrackDisplayKudari != pUiData->iJikokuhyouTrackDisplayKudari &&
		//	pUiData->bJikokuhyouTrackDisplayKudariEnable)
		//{
		//	pTarget->setJikokuhyouTrackDisplayKudari(pUiData->iJikokuhyouTrackDisplayKudari != 0);
		//}
		//else if(!pUiData->bJikokuhyouTrackDisplayKudariEnable)
		//{
		//	pTarget->setJikokuhyouTrackDisplayKudari( false );
		//}
		//上り時刻表ビュー番線表示
		if (m_pTarget->size() == 1)
		{
			if (pUiData->bJikokuhyouTrackDisplayNoboriEnable)
			{
				pTarget->setJikokuhyouTrackDisplayNobori(pUiData->iJikokuhyouTrackDisplayNobori != 0);
			}
			else
			{
				pTarget->setJikokuhyouTrackDisplayNobori(false);
			}
		}
		//else if (pUiDataStartEdit->iJikokuhyouTrackDisplayNobori != pUiData->iJikokuhyouTrackDisplayNobori &&
		//	pUiData->bJikokuhyouTrackDisplayNoboriEnable)
		//{
		//	pTarget->setJikokuhyouTrackDisplayNobori(pUiData->iJikokuhyouTrackDisplayNobori != 0);
		//}
		//else if (!pUiData->bJikokuhyouTrackDisplayNoboriEnable)
		//{
		//	pTarget->setJikokuhyouTrackDisplayNobori(false);
		//}
		//ダイヤグラムビュー番線表示
		if (m_pTarget->size() == 1)
		{
			if (pUiData->bDiagramTrackDisplayEnable)
			{
				pTarget->setDiagramTrackDisplay(pUiData->iDiagramTrackDisplay != 0);
			}
			else
			{
				pTarget->setDiagramTrackDisplay(false);
			}
		}
		//else if (pUiDataStartEdit->iDiagramTrackDisplay != pUiData->iDiagramTrackDisplay &&
		//	pUiData->bDiagramTrackDisplayEnable)
		//{
		//	pTarget->setDiagramTrackDisplay(pUiData->iDiagramTrackDisplay != 0);
		//}
		//else if (!pUiData->bDiagramTrackDisplayEnable)
		//{
		//	pTarget->setDiagramTrackDisplay(false);
		//}

		//在線表省略設定
		if (m_pTarget->size() == 1)
		{
			pTarget->setDiagramTrackOmit(pUiData->bDiagramTrackOmit);
		}

		/* 駅名略称 */
		if (bNewItem || pUiDataStartEdit->strEkimeiJikokuhyouRyaku != pUiData->strEkimeiJikokuhyouRyaku)
		{
			pTarget->setEkimeiJikokuhyouRyaku(pUiData->strEkimeiJikokuhyouRyaku);
		}
		/* 駅名略称(運用一覧) */
		if (bNewItem || pUiDataStartEdit->strEkimeiDiagramRyaku != pUiData->strEkimeiDiagramRyaku)
		{
			pTarget->setEkimeiDiagramRyaku(pUiData->strEkimeiDiagramRyaku);
		}

		//EkiTrack2
		if (m_pTarget->size() == 1)
		{
			CentDedEkiTrack2Cont* pCentDedEkiTrack2Cont = pTarget->getEkiTrack2Cont();
			int iMainDown = -1;
			int iMainUp = -1;
			for (int idx = 0; idx < (int)pUiData->sEkiTrack2.size(); idx++)
			{
				CentDedEkiTrack2 aCentDedEkiTrack2(
					pUiData->sEkiTrack2[idx].strTrackName,
					pUiData->sEkiTrack2[idx].strTrackRyakusyou,
					pUiData->sEkiTrack2[idx].strTrackNoboriRyakusyou);
				//Ver2.0　列車側主本線設定撤廃により、+1処理を削除
				if (iMainDown == -1 &&
					(pUiData->sEkiTrack2[idx].iMainTrack == 1 ||
					pUiData->sEkiTrack2[idx].iMainTrack == 3))
				{
					iMainDown = idx;
				}
				if (iMainUp == -1 &&
					(pUiData->sEkiTrack2[idx].iMainTrack == 2 ||
						pUiData->sEkiTrack2[idx].iMainTrack == 3))
				{
					iMainUp = idx;
				}
				if (idx < pCentDedEkiTrack2Cont->size())
				{
					pCentDedEkiTrack2Cont->set(aCentDedEkiTrack2, idx);
				}
				else
				{
					pCentDedEkiTrack2Cont->insert(aCentDedEkiTrack2);
				}

			}
			if ((int)pUiData->sEkiTrack2.size() < pCentDedEkiTrack2Cont->size())
			{
				pCentDedEkiTrack2Cont->erase(pUiData->sEkiTrack2.size(), INT_MAX);
			}
			if (iMainDown >= 0)
			{
				pTarget->setDownMain(iMainDown);
			}
			if (iMainUp >= 0)
			{
				pTarget->setUpMain(iMainUp);
			}
		}
		//OuterTerminalEkimei
		if (m_pTarget->size() == 1)
		{
			for (int idx = 0; idx < (int)pUiData->sOuterTerminalEkimei.size(); idx++)
			{
				OuterTerminal sOuterTerminal(
					pUiData->sOuterTerminalEkimei[idx].strOuterTerminalEkimei,
					pUiData->sOuterTerminalEkimei[idx].strOuterTerminalJikokuRyaku,
					pUiData->sOuterTerminalEkimei[idx].strOuterTerminalDiaRyaku);
				if (idx < pTarget->getOuterTerminalEkimeiCount())
				{
					pTarget->setOuterTerminalEkimei(sOuterTerminal, idx);
				}
				else
				{
					pTarget->insertOuterTerminalEkimei(sOuterTerminal);
				}
			}
			if ((int)pUiData->sOuterTerminalEkimei.size() < pTarget->getOuterTerminalEkimeiCount())
			{
				pTarget->eraseOuterTerminalEkimei(pUiData->sOuterTerminalEkimei.size(), INT_MAX);
			}
		}
		/* 次駅までの距離  */
		if (bNewItem || pUiDataStartEdit->iNextEkiDistance != pUiData->iNextEkiDistance)
		{
			pTarget->setNextEkiDistance(pUiData->iNextEkiDistance);
		}
		//番線表示省略設定
		if (m_pTarget->size() == 1)
		{
			if (pUiData->bJikokuhyouTrackOmitEnable)
			{
				pTarget->setJikokuhyouTrackOmit(pUiData->iJikokuhyouTrackOmit != 0);
			}
			else
			{
				pTarget->setJikokuhyouTrackOmit(false);
			}
		}
		//else if (pUiDataStartEdit->iJikokuhyouTrackOmit != pUiData->iJikokuhyouTrackOmit &&
		//	pUiData->bJikokuhyouTrackOmitEnable)
		//{
		//	pTarget->setJikokuhyouTrackOmit(pUiData->iJikokuhyouTrackOmit != 0);
		//}
		//else if (!pUiData->bJikokuhyouTrackOmitEnable)
		//{
		//	pTarget->setJikokuhyouTrackOmit(false);
		//}

		/* 作業表示欄設定（起点側） */
		if (m_pTarget->size() == 1)
		{
			if (pUiData->bJikokuhyouOperationEnable)
			{
				pTarget->setJikokuhyouOperationOrigin(pUiData->iJikokuhyouOperationOrigin);
				if (pUiData->iJikokuhyouOperationOrigin > 0)
				{
					pTarget->setJikokuhyouOperationOriginDownBeforeUpAfter(
						pUiData->bJikokuhyouOperationOriginDownBeforeUpAfter);
					pTarget->setJikokuhyouOperationOriginDownAfterUpBefore(
						pUiData->bJikokuhyouOperationOriginDownAfterUpBefore);
				}
				else
				{
					pTarget->setJikokuhyouOperationOriginDownBeforeUpAfter(false);
					pTarget->setJikokuhyouOperationOriginDownAfterUpBefore(false);
				}
			}
			else
			{
				pTarget->setJikokuhyouOperationOrigin(0);
				pTarget->setJikokuhyouOperationOriginDownBeforeUpAfter(false);
				pTarget->setJikokuhyouOperationOriginDownAfterUpBefore(false);
			}
		}
		//else if (pUiDataStartEdit->iJikokuhyouOperationOrigin != pUiData->iJikokuhyouOperationOrigin &&
		//	pUiData->bJikokuhyouOperationEnable)
		//{
		//	pTarget->setJikokuhyouOperationOrigin(pUiData->iJikokuhyouOperationOrigin);
		//}
		//else if (!pUiData->bJikokuhyouOperationEnable)
		//{
		//	pTarget->setJikokuhyouOperationOrigin(0);
		//}
		/* 作業表示欄設定（終点側） */
		if (m_pTarget->size() == 1)
		{
			if (pUiData->bJikokuhyouOperationEnable)
			{
				pTarget->setJikokuhyouOperationTerminal(pUiData->iJikokuhyouOperationTerminal);
				if (pUiData->iJikokuhyouOperationTerminal > 0)
				{
					pTarget->setJikokuhyouOperationTerminalDownBeforeUpAfter(
						pUiData->bJikokuhyouOperationTerminalDownBeforeUpAfter);
					pTarget->setJikokuhyouOperationTerminalDownAfterUpBefore(
						pUiData->bJikokuhyouOperationTerminalDownAfterUpBefore);
				}
				else
				{
					pTarget->setJikokuhyouOperationTerminalDownBeforeUpAfter(false);
					pTarget->setJikokuhyouOperationTerminalDownAfterUpBefore(false);
				}
			}
			else
			{
				pTarget->setJikokuhyouOperationTerminal(0);
				pTarget->setJikokuhyouOperationTerminalDownBeforeUpAfter(false);
				pTarget->setJikokuhyouOperationTerminalDownAfterUpBefore(false);
			}
		}
		//else if (pUiDataStartEdit->iJikokuhyouOperationTerminal != pUiData->iJikokuhyouOperationTerminal &&
		//	pUiData->bJikokuhyouOperationEnable)
		//{
		//	pTarget->setJikokuhyouOperationTerminal(pUiData->iJikokuhyouOperationTerminal);
		//}
		//else if (!pUiData->bJikokuhyouOperationEnable)
		//{
		//	pTarget->setJikokuhyouOperationTerminal(0);
		//}

		//下り時刻表ビュー着時刻表示
		if (m_pTarget->size() == 1)
		{
			if (pUiData->bJikokuhyouChakuJikokuDisplayKudariEnable)
			{
				pTarget->setJikokuhyouChakuJikokuDisplayKudari(pUiData->bJikokuhyouChakuJikokuDisplayKudari);
			}
			else
			{
				pTarget->setJikokuhyouChakuJikokuDisplayKudari(false);
			}
		}

		//if (bNewItem)
		//{
		//	if (pUiData->bJikokuhyouChakuJikokuDisplayKudariEnable)
		//	{
		//		pTarget->setJikokuhyouChakuJikokuDisplayKudari(pUiData->bJikokuhyouChakuJikokuDisplayKudari);
		//	}
		//	else
		//	{
		//		pTarget->setJikokuhyouChakuJikokuDisplayKudari(false);
		//	}
		//}
		//else if (pUiDataStartEdit->bJikokuhyouChakuJikokuDisplayKudari != pUiData->bJikokuhyouChakuJikokuDisplayKudari &&
		//	pUiData->bJikokuhyouChakuJikokuDisplayKudariEnable)
		//{
		//	pTarget->setJikokuhyouChakuJikokuDisplayKudari(pUiData->bJikokuhyouChakuJikokuDisplayKudari);
		//}
		//else if (!pUiData->bJikokuhyouChakuJikokuDisplayKudariEnable)
		//{
		//	pTarget->setJikokuhyouChakuJikokuDisplayKudari(false);
		//}
		//上り時刻表ビュー着時刻表示
		if (m_pTarget->size() == 1)
		{
			if (pUiData->bJikokuhyouChakuJikokuDisplayNoboriEnable)
			{
				pTarget->setJikokuhyouChakuJikokuDisplayNobori(pUiData->bJikokuhyouChakuJikokuDisplayNobori);
			}
			else
			{
				pTarget->setJikokuhyouChakuJikokuDisplayNobori(false);
			}
		}
		//if (bNewItem)
		//{
		//	if (pUiData->bJikokuhyouChakuJikokuDisplayNoboriEnable)
		//	{
		//		pTarget->setJikokuhyouChakuJikokuDisplayNobori(pUiData->bJikokuhyouChakuJikokuDisplayNobori);
		//	}
		//	else
		//	{
		//		pTarget->setJikokuhyouChakuJikokuDisplayNobori(false);
		//	}
		//}
		//else if (pUiDataStartEdit->bJikokuhyouChakuJikokuDisplayNobori != pUiData->bJikokuhyouChakuJikokuDisplayNobori &&
		//	pUiData->bJikokuhyouChakuJikokuDisplayNoboriEnable)
		//{
		//	pTarget->setJikokuhyouChakuJikokuDisplayNobori(pUiData->bJikokuhyouChakuJikokuDisplayNobori);
		//}
		//else if (!pUiData->bJikokuhyouChakuJikokuDisplayNoboriEnable)
		//{
		//	pTarget->setJikokuhyouChakuJikokuDisplayNobori(false);
		//}

		//下り時刻表ビュー発時刻表示
		if (m_pTarget->size() == 1)
		{
			if (pUiData->bJikokuhyouHatsuJikokuDisplayKudariEnable)
			{
				pTarget->setJikokuhyouHatsuJikokuDisplayKudari(pUiData->bJikokuhyouHatsuJikokuDisplayKudari);
			}
			else
			{
				pTarget->setJikokuhyouHatsuJikokuDisplayKudari(false);
			}
		}
		//if (bNewItem)
		//{
		//	if (pUiData->bJikokuhyouHatsuJikokuDisplayKudariEnable)
		//	{
		//		pTarget->setJikokuhyouHatsuJikokuDisplayKudari(pUiData->bJikokuhyouHatsuJikokuDisplayKudari);
		//	}
		//	else
		//	{
		//		pTarget->setJikokuhyouHatsuJikokuDisplayKudari(false);
		//	}
		//}
		//else if (pUiDataStartEdit->bJikokuhyouHatsuJikokuDisplayKudari != pUiData->bJikokuhyouHatsuJikokuDisplayKudari &&
		//	pUiData->bJikokuhyouHatsuJikokuDisplayKudariEnable)
		//{
		//	pTarget->setJikokuhyouHatsuJikokuDisplayKudari(pUiData->bJikokuhyouHatsuJikokuDisplayKudari);
		//}
		//else if (!pUiData->bJikokuhyouHatsuJikokuDisplayKudariEnable)
		//{
		//	pTarget->setJikokuhyouHatsuJikokuDisplayKudari(false);
		//}

		//上り時刻表ビュー発時刻表示
		if (m_pTarget->size() == 1)
		{
			if (pUiData->bJikokuhyouHatsuJikokuDisplayNoboriEnable)
			{
				pTarget->setJikokuhyouHatsuJikokuDisplayNobori(pUiData->bJikokuhyouHatsuJikokuDisplayNobori);
			}
			else
			{
				pTarget->setJikokuhyouHatsuJikokuDisplayNobori(false);
			}
		}
		//if (bNewItem)
		//{
		//	if (pUiData->bJikokuhyouHatsuJikokuDisplayNoboriEnable)
		//	{
		//		pTarget->setJikokuhyouHatsuJikokuDisplayNobori(pUiData->bJikokuhyouHatsuJikokuDisplayNobori);
		//	}
		//	else
		//	{
		//		pTarget->setJikokuhyouHatsuJikokuDisplayNobori(false);
		//	}
		//}
		//else if (pUiDataStartEdit->bJikokuhyouHatsuJikokuDisplayNobori != pUiData->bJikokuhyouHatsuJikokuDisplayNobori &&
		//	pUiData->bJikokuhyouHatsuJikokuDisplayNoboriEnable)
		//{
		//	pTarget->setJikokuhyouHatsuJikokuDisplayNobori(pUiData->bJikokuhyouHatsuJikokuDisplayNobori);
		//}
		//else if (!pUiData->bJikokuhyouHatsuJikokuDisplayNoboriEnable)
		//{
		//	pTarget->setJikokuhyouHatsuJikokuDisplayNobori(false);
		//}

		//下り時刻表ビュー列車番号表示
		if (m_pTarget->size() == 1)
		{
			if (pUiData->bJikokuhyouSyubetsuChangeDisplayKudariEnable)
			{
				pTarget->setJikokuhyouRessyabangouDisplayKudari(pUiData->iJikokuhyouRessyabangouDisplayKudari);
			}
			else
			{
				pTarget->setJikokuhyouRessyabangouDisplayKudari(0);
			}
		}
		//else if (pUiDataStartEdit->iJikokuhyouRessyabangouDisplayKudari != pUiData->iJikokuhyouRessyabangouDisplayKudari &&
		//	pUiData->bJikokuhyouSyubetsuChangeDisplayKudariEnable)
		//{
		//	pTarget->setJikokuhyouRessyabangouDisplayKudari(pUiData->iJikokuhyouRessyabangouDisplayKudari);
		//}
		//else if (!pUiData->bJikokuhyouSyubetsuChangeDisplayKudariEnable)
		//{
		//	pTarget->setJikokuhyouRessyabangouDisplayKudari(0);
		//}

		//上り時刻表ビュー列車番号表示
		if (m_pTarget->size() == 1)
		{
			if (pUiData->bJikokuhyouSyubetsuChangeDisplayNoboriEnable)
			{
				pTarget->setJikokuhyouRessyabangouDisplayNobori(pUiData->iJikokuhyouRessyabangouDisplayNobori);
			}
			else
			{
				pTarget->setJikokuhyouRessyabangouDisplayNobori(0);
			}
		}
		//else if (pUiDataStartEdit->iJikokuhyouRessyabangouDisplayNobori != pUiData->iJikokuhyouRessyabangouDisplayNobori &&
		//	pUiData->bJikokuhyouSyubetsuChangeDisplayNoboriEnable)
		//{
		//	pTarget->setJikokuhyouRessyabangouDisplayNobori(pUiData->iJikokuhyouRessyabangouDisplayNobori);
		//}
		//else if (!pUiData->bJikokuhyouSyubetsuChangeDisplayNoboriEnable)
		//{
		//	pTarget->setJikokuhyouRessyabangouDisplayNobori(0);
		//}

		//下り時刻表ビュー運用番号表示
		if (m_pTarget->size() == 1)
		{
			if (pUiData->bJikokuhyouSyubetsuChangeDisplayKudariEnable)
			{
				pTarget->setJikokuhyouOperationNumberDisplayKudari(pUiData->iJikokuhyouOperationNumberDisplayKudari);
				pTarget->setJikokuhyouOperationNumberDisplayRowsKudari(pUiData->iJikokuhyouOperationNumberDisplayRowsKudari + 1);
			}
			else
			{
				pTarget->setJikokuhyouOperationNumberDisplayKudari(0);
				pTarget->setJikokuhyouOperationNumberDisplayRowsKudari(1);
			}
		}
		//else if (pUiDataStartEdit->iJikokuhyouOperationNumberDisplayKudari != pUiData->iJikokuhyouOperationNumberDisplayKudari &&
		//	pUiData->bJikokuhyouSyubetsuChangeDisplayKudariEnable)
		//{
		//	pTarget->setJikokuhyouOperationNumberDisplayKudari(pUiData->iJikokuhyouOperationNumberDisplayKudari);
		//}
		//else if (!pUiData->bJikokuhyouSyubetsuChangeDisplayKudariEnable)
		//{
		//	pTarget->setJikokuhyouOperationNumberDisplayKudari(0);
		//}

		//上り時刻表ビュー運用番号表示
		if (m_pTarget->size() == 1)
		{
			if (pUiData->bJikokuhyouSyubetsuChangeDisplayNoboriEnable)
			{
				pTarget->setJikokuhyouOperationNumberDisplayNobori(pUiData->iJikokuhyouOperationNumberDisplayNobori);
				pTarget->setJikokuhyouOperationNumberDisplayRowsNobori(pUiData->iJikokuhyouOperationNumberDisplayRowsNobori + 1);
			}
			else
			{
				pTarget->setJikokuhyouOperationNumberDisplayNobori(0);
				pTarget->setJikokuhyouOperationNumberDisplayRowsNobori(1);
			}
		}
		//else if (pUiDataStartEdit->iJikokuhyouOperationNumberDisplayNobori != pUiData->iJikokuhyouOperationNumberDisplayNobori &&
		//	pUiData->bJikokuhyouSyubetsuChangeDisplayNoboriEnable)
		//{
		//	pTarget->setJikokuhyouOperationNumberDisplayNobori(pUiData->iJikokuhyouOperationNumberDisplayNobori);
		//}
		//else if (!pUiData->bJikokuhyouSyubetsuChangeDisplayNoboriEnable)
		//{
		//	pTarget->setJikokuhyouOperationNumberDisplayNobori(0);
		//}

		//下り時刻表ビュー列車種別表示
		if (m_pTarget->size() == 1)
		{
			if (pUiData->bJikokuhyouSyubetsuChangeDisplayKudariEnable)
			{
				pTarget->setJikokuhyouRessyaSyubetsuDisplayKudari(pUiData->iJikokuhyouRessyaSyubetsuDisplayKudari);
			}
			else
			{
				pTarget->setJikokuhyouRessyaSyubetsuDisplayKudari(0);
			}
		}
		//else if (pUiDataStartEdit->iJikokuhyouRessyaSyubetsuDisplayKudari != pUiData->iJikokuhyouRessyaSyubetsuDisplayKudari &&
		//	pUiData->bJikokuhyouSyubetsuChangeDisplayKudariEnable)
		//{
		//	pTarget->setJikokuhyouRessyaSyubetsuDisplayKudari(pUiData->iJikokuhyouRessyaSyubetsuDisplayKudari);
		//}
		//else if (!pUiData->bJikokuhyouSyubetsuChangeDisplayKudariEnable)
		//{
		//	pTarget->setJikokuhyouRessyaSyubetsuDisplayKudari(0);
		//}

		//上り時刻表ビュー列車種別表示
		if (m_pTarget->size() == 1)
		{
			if (pUiData->bJikokuhyouSyubetsuChangeDisplayNoboriEnable)
			{
				pTarget->setJikokuhyouRessyaSyubetsuDisplayNobori(pUiData->iJikokuhyouRessyaSyubetsuDisplayNobori);
			}
			else
			{
				pTarget->setJikokuhyouRessyaSyubetsuDisplayNobori(0);
			}
		}
		//else if (pUiDataStartEdit->iJikokuhyouRessyaSyubetsuDisplayNobori != pUiData->iJikokuhyouRessyaSyubetsuDisplayNobori &&
		//	pUiData->bJikokuhyouSyubetsuChangeDisplayNoboriEnable)
		//{
		//	pTarget->setJikokuhyouRessyaSyubetsuDisplayNobori(pUiData->iJikokuhyouRessyaSyubetsuDisplayNobori);
		//}
		//else if (!pUiData->bJikokuhyouSyubetsuChangeDisplayNoboriEnable)
		//{
		//	pTarget->setJikokuhyouRessyaSyubetsuDisplayNobori(0);
		//}

		//下り時刻表ビュー列車名表示
		if (m_pTarget->size() == 1)
		{
			if (pUiData->bJikokuhyouSyubetsuChangeDisplayKudariEnable)
			{
				pTarget->setJikokuhyouRessyameiDisplayKudari(pUiData->iJikokuhyouRessyameiDisplayKudari);
			}
			else
			{
				pTarget->setJikokuhyouRessyameiDisplayKudari(0);
			}
		}
		//else if (pUiDataStartEdit->iJikokuhyouRessyameiDisplayKudari != pUiData->iJikokuhyouRessyameiDisplayKudari &&
		//	pUiData->bJikokuhyouSyubetsuChangeDisplayKudariEnable)
		//{
		//	pTarget->setJikokuhyouRessyameiDisplayKudari(pUiData->iJikokuhyouRessyameiDisplayKudari);
		//}
		//else if (!pUiData->bJikokuhyouSyubetsuChangeDisplayKudariEnable)
		//{
		//	pTarget->setJikokuhyouRessyameiDisplayKudari(0);
		//}

		//上り時刻表ビュー列車名表示
		if (m_pTarget->size() == 1)
		{
			if (pUiData->bJikokuhyouSyubetsuChangeDisplayNoboriEnable)
			{
				pTarget->setJikokuhyouRessyameiDisplayNobori(pUiData->iJikokuhyouRessyameiDisplayNobori);
			}
			else
			{
				pTarget->setJikokuhyouRessyameiDisplayNobori(0);
			}
		}
		//else if (pUiDataStartEdit->iJikokuhyouRessyameiDisplayNobori != pUiData->iJikokuhyouRessyameiDisplayNobori &&
		//	pUiData->bJikokuhyouSyubetsuChangeDisplayNoboriEnable)
		//{
		//	pTarget->setJikokuhyouRessyameiDisplayNobori(pUiData->iJikokuhyouRessyameiDisplayNobori);
		//}
		//else if (!pUiData->bJikokuhyouSyubetsuChangeDisplayNoboriEnable)
		//{
		//	pTarget->setJikokuhyouRessyameiDisplayNobori(0);
		//}

		//下りカスタマイズ時刻表ビューでの路線外・前列車始発駅表示
		if (m_pTarget->size() == 1)
		{
			if (pUiData->bJikokuhyouOuterSihatsuDisplayKudariEnable)
			{
				pTarget->setJikokuhyouOuterSihatsuDisplayKudari(pUiData->bJikokuhyouOuterSihatsuDisplayKudari);
			}
			else
			{
				pTarget->setJikokuhyouOuterSihatsuDisplayKudari(false);
			}
		}

		//下りカスタマイズ時刻表ビューでの路線外・次列車終着駅表示
		if (m_pTarget->size() == 1)
		{
			if (pUiData->bJikokuhyouOuterShuchakuDisplayKudariEnable)
			{
				pTarget->setJikokuhyouOuterShuchakuDisplayKudari(pUiData->bJikokuhyouOuterShuchakuDisplayKudari);
			}
			else
			{
				pTarget->setJikokuhyouOuterShuchakuDisplayKudari(false);
			}
		}

		//上りカスタマイズ時刻表ビューでの路線外・前列車始発駅表示
		if (m_pTarget->size() == 1)
		{
			if (pUiData->bJikokuhyouOuterSihatsuDisplayNoboriEnable)
			{
				pTarget->setJikokuhyouOuterSihatsuDisplayNobori(pUiData->bJikokuhyouOuterSihatsuDisplayNobori);
			}
			else
			{
				pTarget->setJikokuhyouOuterSihatsuDisplayNobori(false);
			}
		}

		//上りカスタマイズ時刻表ビューでの路線外・次列車終着駅表示
		if (m_pTarget->size() == 1)
		{
			if (pUiData->bJikokuhyouOuterShuchakuDisplayNoboriEnable)
			{
				pTarget->setJikokuhyouOuterShuchakuDisplayNobori(pUiData->bJikokuhyouOuterShuchakuDisplayNobori);
			}
			else
			{
				pTarget->setJikokuhyouOuterShuchakuDisplayNobori(false);
			}
		}

		/* ダイヤグラム背景色 */
		if (bNewItem || pUiDataStartEdit->iDiagramColorNextEki != pUiData->iDiagramColorNextEki)
		{
			pTarget->setDiagramColorNextEki(pUiData->iDiagramColorNextEki);
		}

		/* 箱ダイヤで表示するか否か */
		if (m_pTarget->size() == 1)
		{
			//if (pUiData->bOperationTableDisplayJikokuEnable)
			//{
				pTarget->setOperationTableDisplayJikoku(pUiData->bOperationTableDisplayJikoku);
			//}
			//else
			//{
				//pTarget->setOperationTableDisplayJikoku(0);
			//}
		}

	}
	/*	[駅時刻を駅時刻形式で正規化]の設定です。*/
	if ( iRv >= 0 )
	{
		if ( bNewItem || pUiDataStartEdit->bAdjustByEkijikokukeisiki != pUiData->bAdjustByEkijikokukeisiki)
		{
			// [駅時刻を駅時刻形式で正規化]の設定
			*m_pbAdjustByEkijikokukeisiki = pUiData->bAdjustByEkijikokukeisiki ;
		}
	}
	return iRv ;
}


	// ********************************
	//	コンストラクタ
	// ********************************
CPropEditUi_Eki::CPropEditUi_Eki( 
	bool bNewItem , 
	Mu<CentDedEki*>* pTarget ,
	bool* pbAdjustByEkijikokukeisiki,
	int iEkiIndex,
	bool bEkijikokukeisikiAndEkikiboEnable,
	bool bBrunchFunctionEnable,
	bool bLoopFunctionEnable)
	: CPropEditUi2( bNewItem ) 
	, m_pTarget( pTarget ) 
	, m_pbAdjustByEkijikokukeisiki( pbAdjustByEkijikokukeisiki )
	, m_iEkiIndex(iEkiIndex)
	, m_bEkijikokukeisikiAndEkikiboEnable(bEkijikokukeisikiAndEkikiboEnable)
	, m_bBrunchFunctionEnable(bBrunchFunctionEnable)
	, m_bLoopFunctionEnable(bLoopFunctionEnable)
{	
};

} //namespace ViewEki 



