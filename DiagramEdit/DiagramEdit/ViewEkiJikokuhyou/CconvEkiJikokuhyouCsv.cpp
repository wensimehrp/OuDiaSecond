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
// ****************************************************************
// $Id: CconvEkiJikokuhyouCsv.cpp
// ****************************************************************
#include "stdafx.h"
#include "CconvEkiJikokuhyouCsv.h"
#include "str\strprintf.h"
//#include "OperationTableColSpec\CdOperationTableYColSpecCont.h"
//#include "..\entDed\CdDedJikoku.h"
//#include "..\entDed\CdDedRessyaProperty.h"
#include "../DiagramEdit.h"

namespace ViewEkiJikokuhyou {

using namespace std ;
using namespace OuLib ;
using namespace OuLib::Str ;

/**
	FileTypeの 名前
*/
//const TCHAR* const nameFileType = _T("FileType") ;

/**
	FileType の値
*/
//const TCHAR* const nameFileTypeValue = _T("OuDiaSecond.AllOperationTableCsv.1") ;

///** 時刻の書式を保持します。 */
//const CdDedJikoku::CConv	g_CdDedJikokuConv(
//	true ,		//	NoColon 
//	// 時が 00 から 09 の場合、10の位の "0" を削除します。
//	CdDedJikoku::CConv::EHour_ZeroToNone ,	
//	CdDedJikoku::CConv::ESecond_NoSecond 	// 秒を常に出力しません。 
//	) ;
//
//const CdDedJikoku::CConv	g_CdDedJikokuConvSecond(
//	true,		//	NoColon 
//				// 時が 00 から 09 の場合、10の位の "0" を削除します。
//	CdDedJikoku::CConv::EHour_ZeroToNone,
//	CdDedJikoku::CConv::ESecond_Output 	
//);
//const CdDedJikoku::CConv	g_CdDedJikokuConvColon(
//	false,		//	コロンあり
//				// 時が 00 から 09 の場合、10の位の "0" を削除します。
//	CdDedJikoku::CConv::EHour_ZeroToNone,
//	CdDedJikoku::CConv::ESecond_NoSecond 	// 秒を常に出力しません。 
//);
//
//const CdDedJikoku::CConv	g_CdDedJikokuConvSecondColon(
//	false,		//	コロンあり
//				// 時が 00 から 09 の場合、10の位の "0" を削除します。
//	CdDedJikoku::CConv::EHour_ZeroToNone,
//	CdDedJikoku::CConv::ESecond_Output
//);

	// --------------------------------
	//@name	駅時刻セルの文字列の解釈
	// --------------------------------
//tstring CconvEkiJikokuhyouCsv::encode_Ekijikoku(
//		const CdDedJikoku& aCdDedJikoku ,
//		const bool bDisplaySecondEkiJikoku,
//		const bool bDisplayColonEkiJikoku)
//{
//	tstring strValue ;
//	if (bDisplayColonEkiJikoku)
//	{
//		if (bDisplaySecondEkiJikoku) {
//			strValue = g_CdDedJikokuConvSecondColon.encode(aCdDedJikoku);
//		}
//		else {
//			strValue = g_CdDedJikokuConvColon.encode(aCdDedJikoku);
//		}
//	}
//	else
//	{
//		if (bDisplaySecondEkiJikoku) {
//			strValue = g_CdDedJikokuConvSecond.encode(aCdDedJikoku);
//		}
//		else {
//			strValue = g_CdDedJikokuConv.encode(aCdDedJikoku);
//		}
//	}
//
//	return strValue ;
//}

	// --------------------------------
	//@name encode() の下請関数	
	// --------------------------------


// ********************************
	//	コンストラクタ
	// ********************************
CconvEkiJikokuhyouCsv::CconvEkiJikokuhyouCsv()
{
}


	// ********************************
	//@name	CconvEkiJikokuhyouCsv
	// ********************************
int CconvEkiJikokuhyouCsv::encode(
	const ERessyahoukou eRessyahoukou,
	const int iEkiOrder,
	const map<int, list<EkiJikokuhyouContent>>& contListEkiJikokuhyouContent,
	const tstring& strTitle,
	const int& iFirstHour,
	const int& iHourCount,
	const bool bDisplayParentSyubetsu,
	const bool bResume,
	const bool bDisplayTrack,
	const bool bDisplayIsShihatsu,
	CdCsvDocument* pCdCsvDocument ) 
{
	int iRv = 0 ;
	
	//const Mu<CentDedEkiCont::CdDedEki>* pCdDedEkiCont[2];
	const Mu<CentDedEkiCont::CdDedEki>* pCdDedEkiCont = 
		getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont()->getMuPtr(eRessyahoukou);
	//const Mu<CentDedEkiCont::CdDedEki>* pCdDedEkiCont = aCentDedRosen.getCentDedEkiCont()->getMuPtr(eRessyahoukou);
	const CentDedEkiCont::CdDedEki aEki = pCdDedEkiCont->get(iEkiOrder);
	const Mu<const CentDedRessyasyubetsu*>* pCentDedRessyasyubetsuCont = NULL ;
	//const Mu<const CentDedRessya*>* pCentDedRessyaConts[2] ;

	//if (!aCentDedRosen.getKudariDiaAlias().empty())
	//{
	//	m_nameKudari = aCentDedRosen.getKudariDiaAlias();
	//}
	//if (!aCentDedRosen.getNoboriDiaAlias().empty())
	//{
	//	m_nameNobori = aCentDedRosen.getNoboriDiaAlias();
	//}



	// --------------------------------
	//	オブジェクトCdCsvDocument をクリア
	// --------------------------------
	if ( iRv >= 0 )
	{
		//for (int iRessyahoukou = Ressyahoukou_Kudari;
		//	iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
		//{
		//	pCdDedEkiCont[iRessyahoukou] = aCentDedRosen.getCentDedEkiCont()
		//		->getMuPtr((ERessyahoukou)iRessyahoukou);
		//	pCentDedRessyaConts[iRessyahoukou] = aCentDedDia.getCentDedRessyaCont((ERessyahoukou)iRessyahoukou)->getMuPtr();
		//}
		pCentDedRessyasyubetsuCont = 
			getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedRessyasyubetsuCont()->getMuPtr();
		//pCentDedRessyasyubetsuCont = aCentDedRosen.getCentDedRessyasyubetsuCont()->getMuPtr() ;
	}

	// --------------------------------
	//	CdCsvDocument をクリア
	// --------------------------------
	if ( iRv >= 0 )
	{
		//bResumeがTrueの場合は、空行を一行挟んで内容を追記します。
		//Falseの場合は、クリアしてから内容を書き込みます。
		if (bResume)
		{
			pCdCsvDocument->getRowCont()->insert(CdCsvRow());
		}
		else
		{
			pCdCsvDocument->getRowCont()->erase(0, INT_MAX);
		}
	}

	// --------------------------------
	//	ヘッダ列
	// --------------------------------
	//	1行目 タイトル行
	if ( iRv >= 0 )
	{
		CdCsvRow	aRow ;
		aRow.getCellCont()->insert( CdCsvCell(strTitle) ) ;
		pCdCsvDocument->getRowCont()->insert( aRow ) ;
	}

	int iOffset = 0;
	for (int idx = 0; idx < iHourCount; idx++)
	{
		if (iFirstHour + idx == 24)
		{
			iOffset = -24;
		}
		int iHour = iFirstHour + iOffset + idx;
		// --------------------------------
		//	属性を設定
		// --------------------------------
		CdCsvRow	aRow1;
		CdCsvRow	aRow2;
		CdCsvRow	aRow3;
		CdCsvRow	aRow4;

		//	時
		aRow1.getCellCont()->insert(CdCsvCell(to_tstring(iHour)));
		aRow2.getCellCont()->insert(CdCsvCell());
		aRow3.getCellCont()->insert(CdCsvCell());
		aRow4.getCellCont()->insert(CdCsvCell());

		if (contListEkiJikokuhyouContent.find(iHour) != contListEkiJikokuhyouContent.end())
		{
			const list<EkiJikokuhyouContent>& ListEkiJikokuhyouContent = contListEkiJikokuhyouContent.at(iHour);

			int iRessyaIndex = 0;
			for (auto itr = ListEkiJikokuhyouContent.begin();
				itr != ListEkiJikokuhyouContent.end(); itr++, iRessyaIndex++)
			{
				const CentDedRessyasyubetsu* pCentDedRessyasyubetsu = pCentDedRessyasyubetsuCont
					->get(itr->iRessyaSyubetsu);
				if (bDisplayParentSyubetsu && pCentDedRessyasyubetsu->getParentSyubetsuIndex() >= 0)
				{
					pCentDedRessyasyubetsu = pCentDedRessyasyubetsuCont
						->get(pCentDedRessyasyubetsu->getParentSyubetsuIndex());
				}
				if (itr->iMinute >= 0)
				{
					{
						//	列車種別
						//種別のテキスト
						aRow1.getCellCont()->insert(CdCsvCell(pCentDedRessyasyubetsu->getRyakusyou()));
					}
					{
						//	発時刻
						tstring strTemp = _T("");
						if (bDisplayIsShihatsu && itr->bIsShihatsu)
						{
							strTemp += m_nameIsShihatsu;
						}
						strTemp += strprintf(_T("%02d"), itr->iMinute);
						aRow2.getCellCont()->insert(CdCsvCell(strTemp));
					}
					{
						//	行き先駅名
						tstring strEkimei;
						if (itr->iSyuuchakuEkiOrder == -1)
						{
							strEkimei = m_nameLoop;

						}
						else if (itr->iSyuuchakuEkiOrder == -2)
						{
							strEkimei = m_nameForLoop;

						}
						else if (itr->iOuterShuchakuekiIndex != INT_MIN)
						{
							int iOuterTerminalIndex = itr->iOuterShuchakuekiIndex;
							//strEkimei = pCdDedEkiConts[GetDocument()->getRessyahoukou()]
							//	->get(itr->iSyuuchakuEkiOrder).getOuterTerminalEkimei(iOuterTerminalIndex);
							strEkimei = pCdDedEkiCont->get(itr->iSyuuchakuEkiOrder).getOuterTerminalJikokuRyaku(iOuterTerminalIndex, true);
						}
						else
						{
							//strEkimei = pCdDedEkiConts[GetDocument()->getRessyahoukou()]
							//	->get(itr->iSyuuchakuEkiOrder).getEkimei();
							strEkimei = pCdDedEkiCont->get(itr->iSyuuchakuEkiOrder).getEkimeiJikokuhyouRyaku(true);
						}
						aRow3.getCellCont()->insert(CdCsvCell(strEkimei));
					}
					if (bDisplayTrack)
					{
						//	列車番線
						tstring strTrackName = aEki.getCentDedEkiTrack2Cont().get(itr->iRessyaTrackIndex).
							getTrackRyakusyou(eRessyahoukou);
						aRow4.getCellCont()->insert(CdCsvCell(strTrackName));
					}
				}
				else
				{
					{
						//	種別変更駅名
						tstring strEkimei = pCdDedEkiCont->get(itr->iSyuuchakuEkiOrder).getEkimeiJikokuhyouRyaku(true);
						
						aRow1.getCellCont()->insert(CdCsvCell(strEkimei));
					}
					{
						//	"から"
						aRow2.getCellCont()->insert(CdCsvCell(m_nameFrom));
					}
					{
						//	列車種別
						//種別のテキスト
						aRow3.getCellCont()->insert(CdCsvCell(pCentDedRessyasyubetsu->getRyakusyou()));
					}
					if (bDisplayTrack)
					{
						aRow4.getCellCont()->insert(CdCsvCell());
					}

				}
			}
		}

		pCdCsvDocument->getRowCont()->insert(aRow1);
		pCdCsvDocument->getRowCont()->insert(aRow2);
		pCdCsvDocument->getRowCont()->insert(aRow3);
		if (bDisplayTrack)
		{
			pCdCsvDocument->getRowCont()->insert(aRow4);
		}
	}
	return iRv ;
}

} //namespace ViewEkiJikokuhyou

