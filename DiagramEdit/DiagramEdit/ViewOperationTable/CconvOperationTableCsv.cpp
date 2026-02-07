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
// $Id: CconvOperationTableCsv.cpp
// ****************************************************************
#include "stdafx.h"
#include "CconvOperationTableCsv.h"
#include "str\strprintf.h"
//#include "OperationTableColSpec\CdOperationTableYColSpecCont.h"
//#include "..\entDed\CdDedJikoku.h"
#include "..\entDed\CdDedRessyaProperty.h"
#include "../DiagramEdit.h"

namespace ViewOperationTable {

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
//const TCHAR* const nameFileTypeValue = _T("OuDiaSecond.OperationTableCsv.1") ;

/** 時刻の書式を保持します。 */
const CdDedJikoku::CConv	g_CdDedJikokuConv(
	true ,		//	NoColon 
	// 時が 00 から 09 の場合、10の位の "0" を削除します。
	CdDedJikoku::CConv::EHour_ZeroToNone ,	
	CdDedJikoku::CConv::ESecond_NoSecond 	// 秒を常に出力しません。 
	) ;

const CdDedJikoku::CConv	g_CdDedJikokuConvSecond(
	true,		//	NoColon 
				// 時が 00 から 09 の場合、10の位の "0" を削除します。
	CdDedJikoku::CConv::EHour_ZeroToNone,
	CdDedJikoku::CConv::ESecond_Output 	
);
const CdDedJikoku::CConv	g_CdDedJikokuConvColon(
	false,		//	コロンあり
				// 時が 00 から 09 の場合、10の位の "0" を削除します。
	CdDedJikoku::CConv::EHour_ZeroToNone,
	CdDedJikoku::CConv::ESecond_NoSecond 	// 秒を常に出力しません。 
);

const CdDedJikoku::CConv	g_CdDedJikokuConvSecondColon(
	false,		//	コロンあり
				// 時が 00 から 09 の場合、10の位の "0" を削除します。
	CdDedJikoku::CConv::EHour_ZeroToNone,
	CdDedJikoku::CConv::ESecond_Output
);

const CdDedJikoku::CConv
CconvOperationTableCsv::getCdDedJikokuConv()const
{
	CdDedJikoku::CConv::ESecond eSecond = CdDedJikoku::CConv::ESecond_NoSecond;
	if (m_bDisplaySecondEkiJikoku)
	{
		eSecond = CdDedJikoku::CConv::ESecond_Output;
	}

	CdDedJikoku::CConv aConv(
		!m_bDisplayColonEkiJikoku,
		CdDedJikoku::CConv::EHour_ZeroToSpace,
		eSecond,
		(CdDedJikoku::CConv::ESecondRound)m_iSecondRoundChaku,
		(CdDedJikoku::CConv::ESecondRound)m_iSecondRoundHatsu,
		m_bDisplay2400
	);
	return aConv;
}
	// --------------------------------
	//@name	駅時刻セルの文字列の解釈
	// --------------------------------
tstring CconvOperationTableCsv::encode_Ekijikoku(
		const CdDedJikoku& aCdDedJikoku ,
		const bool bDisplaySecondEkiJikoku,
		const bool bDisplayColonEkiJikoku)
{
	tstring strValue ;
	if (bDisplayColonEkiJikoku)
	{
		if (bDisplaySecondEkiJikoku) {
			strValue = g_CdDedJikokuConvSecondColon.encode(aCdDedJikoku);
		}
		else {
			strValue = g_CdDedJikokuConvColon.encode(aCdDedJikoku);
		}
	}
	else
	{
		if (bDisplaySecondEkiJikoku) {
			strValue = g_CdDedJikokuConvSecond.encode(aCdDedJikoku);
		}
		else {
			strValue = g_CdDedJikokuConv.encode(aCdDedJikoku);
		}
	}

	return strValue ;
}

	// --------------------------------
	//@name encode() の下請関数	
	// --------------------------------


// ********************************
	//	コンストラクタ
	// ********************************
CconvOperationTableCsv::CconvOperationTableCsv(
		const tstring& nameRessyabangou ,
		const tstring& nameRessyasyubetsu ,
		const tstring& nameRessyamei ,
		const tstring& nameGousuu,
		const tstring& nameGou,
		const tstring& nameEkimei,
		const tstring& nameEkiJikoku,
		const tstring& nameKudariArrow,
		const tstring& nameNoboriArrow) :
	m_nameRessyabangou( nameRessyabangou ),
	m_nameRessyasyubetsu( nameRessyasyubetsu ),
	m_nameRessyamei( nameRessyamei ),
	m_nameGousuu(nameGousuu),
	m_nameGou(nameGou),
	m_nameEkimei(nameEkimei),
	m_nameEkiJikoku(nameEkiJikoku),
	m_nameKudariArrow(nameKudariArrow),
	m_nameNoboriArrow(nameNoboriArrow)
{
}


	// ********************************
	//@name	CconvJikokuhyouCsv
	// ********************************
int CconvOperationTableCsv::encode(
		const CentDedRosen& aCentDedRosen ,
		const CentDedDia& aCentDedDia,
		const CdDedDispProp& aCdDedDispProp,
		const vector<tstring>& strOperationNumberCont,
		const bool bDisplayExtensionOperationTable,
		//const deque<int>& iDisplayJikokuEkiIndex,
		const bool bDisplaySecondEkiJikoku,
		const bool bDisplayColonEkiJikoku,
		const bool bDisplayParentSyubetsu,
		const bool bDisplayNoboriLeftToRight,
	const bool bDisplayTrackName,
	const bool bDisplayTsuukaEkiJikoku,
		CdCsvDocument* pCdCsvDocument ) 
{
	int iRv = 0 ;
	
	m_bDisplaySecondEkiJikoku = bDisplaySecondEkiJikoku;
	m_bDisplayColonEkiJikoku = bDisplayColonEkiJikoku;
	m_iSecondRoundChaku = aCdDedDispProp.getSecondRoundChaku();
	m_iSecondRoundHatsu = aCdDedDispProp.getSecondRoundHatsu();
	m_bDisplay2400 = aCdDedDispProp.getDisplay2400();


	const CentDedEkiCont* pCentDedEkiCont = NULL ;
	const Mu<CentDedEkiCont::CdDedEki>* pCdDedEkiContKudari = NULL ;
	const Mu<CentDedEkiCont::CdDedEki>* pCdDedEkiContNobori = NULL;
	const Mu<const CentDedRessyasyubetsu*>* pCentDedRessyasyubetsuContGet = NULL ;
	//const CentDedDia* pCentDedDia = NULL ;
	const Mu<const CentDedRessya*>* pCentDedRessyaConts[2] ;

	// --------------------------------
	//	オブジェクトCdCsvDocument をクリア
	// --------------------------------
	if ( iRv >= 0 )
	{
		for (int iRessyahoukou = Ressyahoukou_Kudari;
			iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
		{
			pCentDedRessyaConts[iRessyahoukou] = aCentDedDia.getCentDedRessyaCont((ERessyahoukou)iRessyahoukou)->getMuPtr();
		}
		pCentDedEkiCont = aCentDedRosen.getCentDedEkiCont() ;
		pCdDedEkiContKudari = aCentDedRosen.getCentDedEkiCont()
			->getMuPtr(ERessyahoukou::Ressyahoukou_Kudari);
		pCdDedEkiContNobori = aCentDedRosen.getCentDedEkiCont()
			->getMuPtr(ERessyahoukou::Ressyahoukou_Nobori) ;
		pCentDedRessyasyubetsuContGet = aCentDedRosen.getCentDedRessyasyubetsuCont()->getMuPtr() ; 
	}

	// --------------------------------
	//	CdCsvDocument をクリア
	// --------------------------------
	if ( iRv >= 0 )
	{
		pCdCsvDocument->getRowCont()->erase( 0 , INT_MAX ) ;
	}

	// --------------------------------
	//	ヘッダ列
	// --------------------------------
	//	1行目 FileType行
	//if ( iRv >= 0 )
	//{
	//	CdCsvRow	aRow ;
	//	aRow.getCellCont()->insert( CdCsvCell( nameFileType ) ) ;
	//	aRow.getCellCont()->insert( CdCsvCell( nameFileTypeValue ) ) ;
	//	pCdCsvDocument->getRowCont()->insert( aRow ) ;
	//}	
	//	2行目 DiaName行
	if ( iRv >= 0 )
	{
		CdCsvRow	aRow ;
		aRow.getCellCont()->insert( CdCsvCell(aCentDedDia.getName() ) ) ;
		pCdCsvDocument->getRowCont()->insert( aRow ) ;
	}
	bool bDisplayRessyamei = getCDiagramEditDoc()->getCDedRosenFileData()
		->getCdDedDispProp().getDisplayRessyamei();
	//int idxOperationNumber = -1;
	for (int idxOperationNumber = 0; idxOperationNumber < (int)strOperationNumberCont.size(); idxOperationNumber++)
	{
		//空行
		pCdCsvDocument->getRowCont()->insert(CdCsvRow());
		//運用番号・行
		CdCsvRow	aRowOpeNum;
		aRowOpeNum.getCellCont()->insert(CdCsvCell(strOperationNumberCont[idxOperationNumber]));
		pCdCsvDocument->getRowCont()->insert(aRowOpeNum);

		const list<OperationTableContent>& ListOperationTableContent =
			aCentDedDia.getcontOperationTableContent().at(strOperationNumberCont[idxOperationNumber]);

		vector<OperationTable> contOperationTable;


		bool bIsContinue = false;
		for (auto itr = ListOperationTableContent.begin();
			itr != ListOperationTableContent.end(); itr++)
		{
			//前列車から受け取ったbIsContinueも書き込みます。書き込み後はbIsContinueをfalseに戻します。
			OperationTable aOperationTable(itr->aRessyaProperty.getRessyahoukou(), bIsContinue);
			bIsContinue = false;
			if (itr->eAfterType == EBeforeAfterType::BeforeAfterType_PropertySame)
			{
				int iSihatsuEkiIndex = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
					->getCentDedEkiCont()->EkiIndexOfEkiOrder(itr->aRessyaProperty.getRessyahoukou(),
						itr->iSihatsuEkiOrder);
				int iSyuuchakuEkiIndex = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
					->getCentDedEkiCont()->EkiIndexOfEkiOrder(itr->aRessyaProperty.getRessyahoukou(),
						itr->iSyuuchakuEkiOrder);
				auto itrNext = itr;
				do {
					itrNext++;
					if (itrNext == ListOperationTableContent.end() ||
						itrNext->eBeforeType != EBeforeAfterType::BeforeAfterType_PropertySame)
					{
						//次の列車が末尾を超えた場合、もしくは
						//次の列車の前タイプが同一列車扱い以外なら、一体化は無効その前の列車で終了します。
						if (iSihatsuEkiIndex > iSyuuchakuEkiIndex)
						{
							aOperationTable.eRessyahoukou = ERessyahoukou::Ressyahoukou_Nobori;
						}
						else if (iSihatsuEkiIndex < iSyuuchakuEkiIndex)
						{
							aOperationTable.eRessyahoukou = ERessyahoukou::Ressyahoukou_Kudari;
						}
						contOperationTable.push_back(aOperationTable);
						break;
					}
					else/* if (itrNext->eBeforeType == EBeforeAfterType::BeforeAfterType_PropertySame)*/
					{
						//箱ダイヤの時、前列車と次列車の列車方向が違う、または前列車の終着駅が次列車の始発駅よりも後ろな場合は、
						//行はまとめず、次列車側のbIsContinueをtrueにします。
						if (bDisplayExtensionOperationTable &&
							(itr->aRessyaProperty.getRessyahoukou() != itrNext->aRessyaProperty.getRessyahoukou() ||
								itr->iSyuuchakuEkiOrder > itrNext->iSihatsuEkiOrder))
						{
							bIsContinue = true;
							//前列車までの分をm_contOperationTableに入れて終了です。
							if (iSihatsuEkiIndex > iSyuuchakuEkiIndex)
							{
								aOperationTable.eRessyahoukou = ERessyahoukou::Ressyahoukou_Nobori;
							}
							else if (iSihatsuEkiIndex < iSyuuchakuEkiIndex)
							{
								aOperationTable.eRessyahoukou = ERessyahoukou::Ressyahoukou_Kudari;
							}
							contOperationTable.push_back(aOperationTable);
							break;
						}

						//次の列車の前タイプが同一列車扱いの場合、通常時および箱ダイヤで列車方向一致、終着→始発が駅順の場合は、次の列車は一体化が確定する。

						aOperationTable.iCombineCount++;
						itr++;

						iSyuuchakuEkiIndex = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
							->getCentDedEkiCont()->EkiIndexOfEkiOrder(itrNext->aRessyaProperty.getRessyahoukou(),
								itrNext->iSyuuchakuEkiOrder);

						if (itrNext->eAfterType == EBeforeAfterType::BeforeAfterType_PropertySame)
						{
							//次の列車の後タイプが同一列車扱いなら、さらに次の列車の検索を行う。
							continue;
						}
						else
						{
							//次の列車の後タイプが同一列車扱い以外なら、この列車が一体化の末尾となるので、aOperationTableを確定させる。
							if (iSihatsuEkiIndex > iSyuuchakuEkiIndex)
							{
								aOperationTable.eRessyahoukou = ERessyahoukou::Ressyahoukou_Nobori;
							}
							else if (iSihatsuEkiIndex < iSyuuchakuEkiIndex)
							{
								aOperationTable.eRessyahoukou = ERessyahoukou::Ressyahoukou_Kudari;
							}
							//一体化の結果、始発駅と終着駅が同じの場合は、1列車目の列車方向をそのまま用いる。
							contOperationTable.push_back(aOperationTable);
							break;
						}
					}
				} while (itrNext != ListOperationTableContent.end());
			}
			else
			{
				contOperationTable.push_back(aOperationTable);
			}
		}


		//箱ダイヤ時のiDisplayJikokuEkiIndexを求める
		deque<int> iDisplayJikokuEkiIndex;
		if (bDisplayExtensionOperationTable &&
			!contOperationTable.empty())
		{

			for (int iEkiIndex = 0; iEkiIndex < pCentDedEkiCont->size(); iEkiIndex++)
			{
				const CentDedEki* pCentDedEki = pCentDedEkiCont->getMuPtr()->get(iEkiIndex);
				if (pCentDedEki->getOperationTableDisplayJikoku())
				{
					iDisplayJikokuEkiIndex.push_back(iEkiIndex);
				}
			}

			vector<int> contOriginOuter;
			vector<int> contTerminalOuter;
			auto itr = ListOperationTableContent.begin();
			for (int iOTIndex = 0; iOTIndex < (int)contOperationTable.size(); iOTIndex++)
			{
				int iCombineCount = contOperationTable[iOTIndex].iCombineCount;
				for (int iCbIndex = 0; iCbIndex < iCombineCount; iCbIndex++, itr++)
				{
					const CentDedRessya* pCentDedRessya =
						pCentDedRessyaConts[itr->aRessyaProperty.getRessyahoukou()]
						->get(itr->aRessyaProperty.getRessyaIndex());

					int iSihatsuEkiOrder = itr->iSihatsuEkiOrder;
					if (!pCentDedRessya->isRunBetweenNextEki(iSihatsuEkiOrder))
					{
						iSihatsuEkiOrder = pCentDedRessya->getRunBetweenEkiForward(iSihatsuEkiOrder);
					}

					int iSyuuchakuEkiOrder = itr->iSyuuchakuEkiOrder;
					if (!pCentDedRessya->isRunBetweenNextEki(iSyuuchakuEkiOrder - 1))
					{
						iSyuuchakuEkiOrder = pCentDedRessya->getRunBetweenEkiBackward(iSyuuchakuEkiOrder);
					}

					/**
						1行に複数列車を表示する場合は、最初の列車の始発駅と、最後の列車の終着駅のみが追加対象となります。
						起点側発着駅では、下り方向の場合は先頭列車、上り方向の場合は末尾列車が対象です。
					*/
					if ((contOperationTable[iOTIndex].eRessyahoukou == ERessyahoukou::Ressyahoukou_Kudari &&
						iCbIndex == 0) ||
						(contOperationTable[iOTIndex].eRessyahoukou == ERessyahoukou::Ressyahoukou_Nobori &&
							iCbIndex == iCombineCount - 1))
					{
						/**
							まずは、下り列車の始発駅or上り列車の終着駅(起点側発着駅)について調べる。
							上り列車の場合は、駅Orderを駅Indexに直す。
						*/
						int iOriginEkiIndex;
						bool bOriginOuter;
						if (itr->aRessyaProperty.getRessyahoukou() == ERessyahoukou::Ressyahoukou_Kudari)
						{
							iOriginEkiIndex = iSihatsuEkiOrder;
							bOriginOuter = itr->iOuterShihatsuekiIndex != INT_MIN;
						}
						else
						{
							iOriginEkiIndex = pCentDedEkiCont->EkiIndexOfEkiOrder(itr->aRessyaProperty.getRessyahoukou(), iSyuuchakuEkiOrder);
							bOriginOuter = itr->iOuterShuchakuekiIndex != INT_MIN;
						}

						/**
							iOriginEkiIndexが分岐駅の場合、分岐元の駅に統合します。
						*/
						const CentDedEki* pCentDedEkiOrigin = pCentDedEkiCont->getMuPtr()->get(iOriginEkiIndex);
						if (pCentDedEkiOrigin->getBrunchCoreEkiIndex() != -1)
						{
							iOriginEkiIndex = pCentDedEkiOrigin->getBrunchCoreEkiIndex();
						}


						if (bOriginOuter)
						{
							/**
								路線外発着の場合は、一度駅Indexを、contOriginOuterに入れ、最後にチェックを行う。
							*/
							contOriginOuter.push_back(iOriginEkiIndex);
						}
						else
						{
							/**
								路線外発着ではない場合、起点側発着駅Indexがm_iDisplayJikokuEkiIndexの中にあるかを調べ、なかった場合は、挿入する。
							*/
							if (iDisplayJikokuEkiIndex.empty())
							{
								iDisplayJikokuEkiIndex.push_back(iOriginEkiIndex);
							}
							else
							{
								for (int idx = 0; idx < (int)iDisplayJikokuEkiIndex.size(); idx++)
								{
									if (iDisplayJikokuEkiIndex[idx] == iOriginEkiIndex)
									{
										//一致するものがあったら、何も行わず終了
										break;
									}
									else if (iDisplayJikokuEkiIndex[idx] > iOriginEkiIndex)
									{
										//一致するものがなく、idx番目の駅IndexがiOriginEkiIndexより大きくなってしまったら、idx番目にiOriginEkiIndexを挿入する
										iDisplayJikokuEkiIndex.insert(iDisplayJikokuEkiIndex.begin() + idx, iOriginEkiIndex);
										break;
									}
									else if (idx == (int)iDisplayJikokuEkiIndex.size() - 1)
									{
										//最終要素までにiOriginEkiIndex以上のものがなかった場合、末尾に挿入する
										iDisplayJikokuEkiIndex.push_back(iOriginEkiIndex);
									}

								}
							}
						}
					}

					/**
						1行に複数列車を表示する場合は、最初の列車の始発駅と、最後の列車の終着駅のみが追加対象となります。
						終点側発着駅では、下り方向の場合は末尾列車、上り方向の場合は先頭列車が対象です。
					*/
					if ((contOperationTable[iOTIndex].eRessyahoukou == ERessyahoukou::Ressyahoukou_Kudari &&
						iCbIndex == iCombineCount - 1) ||
						(contOperationTable[iOTIndex].eRessyahoukou == ERessyahoukou::Ressyahoukou_Nobori &&
							iCbIndex == 0))
					{
						/**
							次に、下り列車の終着駅or上り列車の始発駅(終点側発着駅)について調べる。
							上り列車の場合は、駅Orderを駅Indexに直す。
						*/
						int iTerminalEkiIndex;
						bool bTerminalOuter;
						if (itr->aRessyaProperty.getRessyahoukou() == ERessyahoukou::Ressyahoukou_Kudari)
						{
							iTerminalEkiIndex = iSyuuchakuEkiOrder;
							bTerminalOuter = itr->iOuterShuchakuekiIndex != INT_MIN;
						}
						else
						{
							iTerminalEkiIndex = pCentDedEkiCont->EkiIndexOfEkiOrder(itr->aRessyaProperty.getRessyahoukou(), iSihatsuEkiOrder);
							bTerminalOuter = itr->iOuterShihatsuekiIndex != INT_MIN;
						}

						/**
							iTerminalEkiIndexが分岐駅の場合、分岐元の駅に統合します。
						*/
						const CentDedEki* pCentDedEkiTerminal = pCentDedEkiCont->getMuPtr()->get(iTerminalEkiIndex);
						if (pCentDedEkiTerminal->getBrunchCoreEkiIndex() != -1)
						{
							iTerminalEkiIndex = pCentDedEkiTerminal->getBrunchCoreEkiIndex();
						}

						if (bTerminalOuter)
						{
							/**
								路線外発着の場合は、一度駅Indexを、iTerminalOuterに入れ、最後にチェックを行う。
							*/
							contTerminalOuter.push_back(iTerminalEkiIndex);
						}
						else
						{
							/**
								路線外発着ではない場合、終点側発着駅Indexがm_iDisplayJikokuEkiIndexの中にあるかを調べ、なかった場合は、挿入する。
							*/
							if (iDisplayJikokuEkiIndex.empty())
							{
								iDisplayJikokuEkiIndex.push_back(iTerminalEkiIndex);
							}
							else
							{
								for (int idx = 0; idx < (int)iDisplayJikokuEkiIndex.size(); idx++)
								{
									if (iDisplayJikokuEkiIndex[idx] == iTerminalEkiIndex)
									{
										//一致するものがあったら、何も行わず終了
										break;
									}
									else if (iDisplayJikokuEkiIndex[idx] > iTerminalEkiIndex)
									{
										//一致するものがなく、idx番目の駅IndexがiOriginEkiIndexより大きくなってしまったら、idx番目にiOriginEkiIndexを挿入する
										iDisplayJikokuEkiIndex.insert(iDisplayJikokuEkiIndex.begin() + idx, iTerminalEkiIndex);
										break;
									}
									else if (idx == (int)iDisplayJikokuEkiIndex.size() - 1)
									{
										//最終要素までにiOriginEkiIndex以上のものがなかった場合、末尾に挿入する
										iDisplayJikokuEkiIndex.push_back(iTerminalEkiIndex);
									}

								}
							}
						}
					}
				}
			}

			/**
				起点側路線外発着がある場合は、起点側スペースが必要か否かをチェックする
				必要なのは(1)m_iDisplayJikokuEkiIndexが空で、起点側路線外発着が存在する(運用が、路線外始発→路線外終着の一本しかない場合はありうる)
				(2)起点側発着駅が、m_iDisplayJikokuEkiIndexの先頭(最も起点側の表示駅)と同じもしくは起点側
			*/
			for (int iOuterOriginIndex = 0; iOuterOriginIndex < (int)contOriginOuter.size(); iOuterOriginIndex++)
			{
				if (iDisplayJikokuEkiIndex.empty())
				{
					iDisplayJikokuEkiIndex.push_front(INT_MIN);
					break;
				}
				else if (contOriginOuter[iOuterOriginIndex] <= iDisplayJikokuEkiIndex.front())
				{
					iDisplayJikokuEkiIndex.push_front(INT_MIN);
					break;
				}
			}
			/**
				終点側路線外発着についても同様に調べる。
				ただし、ここではm_iDisplayJikokuEkiIndexが空であることはない
				(一列車で、両側路線外の場合は、上でINT_MINを挿入ずみなので)
				m_iDisplayJikokuEkiIndexが一つのみの場合、入っているのは起点側駅か起点側路線外なので、いずれにしろINT_MAXを挿入する
			*/
			for (int iOuterTerminalIndex = 0; iOuterTerminalIndex < (int)contTerminalOuter.size(); iOuterTerminalIndex++)
			{
				if (iDisplayJikokuEkiIndex.size() == 1)
				{
					iDisplayJikokuEkiIndex.push_back(INT_MAX);
					break;
				}
				else if (contTerminalOuter[iOuterTerminalIndex] >= iDisplayJikokuEkiIndex.back())
				{
					iDisplayJikokuEkiIndex.push_back(INT_MAX);
					break;
				}
			}
		}



		//項目名行
		CdCsvRow	aRowHeader;
		aRowHeader.getCellCont()->insert(CdCsvCell(m_nameRessyabangou));
		aRowHeader.getCellCont()->insert(CdCsvCell(m_nameRessyasyubetsu));
		if (bDisplayRessyamei)
		{
			aRowHeader.getCellCont()->insert(CdCsvCell(m_nameRessyamei));
			aRowHeader.getCellCont()->insert(CdCsvCell(m_nameGousuu));
			aRowHeader.getCellCont()->insert(CdCsvCell());
		}
		if (bDisplayExtensionOperationTable)
		{
			for (int idx = 0; idx < (int)iDisplayJikokuEkiIndex.size(); idx++)
			{
				tstring strEkimei = _T("");
				if (iDisplayJikokuEkiIndex[idx] >= 0 &&
					iDisplayJikokuEkiIndex[idx] < pCentDedEkiCont->size())
				{
					strEkimei = pCentDedEkiCont->get(iDisplayJikokuEkiIndex[idx]).getEkimei();
				}
				aRowHeader.getCellCont()->insert(CdCsvCell(strEkimei));
			}
		}
		else
		{
			aRowHeader.getCellCont()->insert(CdCsvCell(m_nameEkimei));
			aRowHeader.getCellCont()->insert(CdCsvCell(m_nameEkiJikoku));
			aRowHeader.getCellCont()->insert(CdCsvCell());
			aRowHeader.getCellCont()->insert(CdCsvCell(m_nameEkimei));
			aRowHeader.getCellCont()->insert(CdCsvCell(m_nameEkiJikoku));
		}
		pCdCsvDocument->getRowCont()->insert(aRowHeader);

		auto itr = ListOperationTableContent.begin();
		for (int iOTIndex = 0; iOTIndex < (int)contOperationTable.size(); iOTIndex++)
		//for(auto itr = ListOperationTableContent.begin(); itr !=ListOperationTableContent.end(); itr++)
		//for (int Ressyaidx = 0; Ressyaidx < (int)ListOperationTableContent.size(); Ressyaidx++)
		{

			CdCsvRow	aRow;
			CdCsvRow	aRow2;
			CdCsvRow	aRow3;

			if (bDisplayExtensionOperationTable)
			{
				vector<tstring> strRow;
				vector<tstring> strRow2;
				vector<tstring> strRow3;
				for (int iCbIndex = 0; iCbIndex < contOperationTable[iOTIndex].iCombineCount; iCbIndex++, itr++)
				{
					vector<tstring> strRowTemp;
					vector<tstring> strRowTemp2;
					vector<tstring> strRowTemp3;


				/**
					箱ダイヤの列車間縦線のために、前列車の終着駅と次列車の始発駅を求めます
					次の場合は求める必要がありません
					前列車:この列車が先頭のとき、この列車が路線外始発の時、この列車が出区の時、前列車が路線外終着の時、前列車が入区の時
					次列車:この列車が末尾の時、この列車が路線外終着の時、この列車が入区の時、次列車が出区の時、次列車が路線外始発の時
				*/
					const CentDedRessya* pCentDedRessya =
						pCentDedRessyaConts[itr->aRessyaProperty.getRessyahoukou()]
						->get(itr->aRessyaProperty.getRessyaIndex());

					int iPrevShuchakuEkiIndex = -1;
					int iNextShihatsuEkiIndex = -1;
					int iPrevContinueEkiIndex = -1;
					int iNextContinueEkiIndex = -1;
					if (iCbIndex == 0 &&//m_contOperationTableの先頭である
						itr != ListOperationTableContent.begin() &&//先頭ではない
						itr->iOuterShihatsuekiIndex == INT_MIN &&//路線外始発ではない
						itr->eBeforeType != EBeforeAfterType::BeforeAfterType_OutIn)//出区ではない
					{
						auto itrPrev = itr;
						itrPrev--;
						if (itrPrev->iOuterShuchakuekiIndex == INT_MIN &&//前列車が路線外終着ではない
							itrPrev->eAfterType != EBeforeAfterType::BeforeAfterType_OutIn)//前列車が入区ではない
						{
							iPrevShuchakuEkiIndex =
								pCentDedEkiCont->EkiIndexOfEkiOrder(
									itrPrev->aRessyaProperty.getRessyahoukou(),
									itrPrev->iSyuuchakuEkiOrder);
							if (pCentDedEkiCont->get(iPrevShuchakuEkiIndex).getBrunchCoreEkiIndex() != -1)
							{
								iPrevShuchakuEkiIndex = pCentDedEkiCont->get(iPrevShuchakuEkiIndex).getBrunchCoreEkiIndex();
							}
						}
					}

					if (iCbIndex == contOperationTable[iOTIndex].iCombineCount - 1 &&//m_contOperationTableの末尾である
						itr->iOuterShuchakuekiIndex == INT_MIN &&//路線外終着ではない
						itr->eAfterType != EBeforeAfterType::BeforeAfterType_OutIn)//入区ではない
					{
						auto itrNext = itr;
						itrNext++;
						if (itrNext != ListOperationTableContent.end() &&//末尾ではない
							itrNext->iOuterShihatsuekiIndex == INT_MIN &&//次列車が路線外始発ではない
							itrNext->eBeforeType != EBeforeAfterType::BeforeAfterType_OutIn)//次列車が出区ではない
						{
							iNextShihatsuEkiIndex =
								pCentDedEkiCont->EkiIndexOfEkiOrder(
									itrNext->aRessyaProperty.getRessyahoukou(),
									itrNext->iSihatsuEkiOrder);
							if (pCentDedEkiCont->get(iNextShihatsuEkiIndex).getBrunchCoreEkiIndex() != -1)
							{
								iNextShihatsuEkiIndex = pCentDedEkiCont->get(iNextShihatsuEkiIndex).getBrunchCoreEkiIndex();
							}
						}
					}

					if (iCbIndex > 0)
					{
						auto itrPrev = itr;
						itrPrev--;
						int iPrevContinueEkiOrder = itrPrev->iSyuuchakuEkiOrder;
						iPrevContinueEkiIndex = pCentDedEkiCont->EkiIndexOfEkiOrder(
							itrPrev->aRessyaProperty.getRessyahoukou(), iPrevContinueEkiOrder);
					}

					if (iCbIndex < contOperationTable[iOTIndex].iCombineCount - 1)
					{
						auto itrNext = itr;
						itrNext++;
						int iNextContinueEkiOrder = itrNext->iSihatsuEkiOrder;
						iNextContinueEkiIndex = pCentDedEkiCont->EkiIndexOfEkiOrder(
							itrNext->aRessyaProperty.getRessyahoukou(), iNextContinueEkiOrder);
					}

					int iSihatsuEkiOrder = itr->iSihatsuEkiOrder;
					if (!pCentDedRessya->isRunBetweenNextEki(iSihatsuEkiOrder))
					{
						iSihatsuEkiOrder = pCentDedRessya->getRunBetweenEkiForward(iSihatsuEkiOrder);
					}
					int iSihatsuCoreEkiIndex =
						pCentDedEkiCont->get(pCentDedEkiCont->EkiIndexOfEkiOrder(itr->aRessyaProperty.getRessyahoukou(), iSihatsuEkiOrder)).getBrunchCoreEkiIndex();
					int iSihatsuEkiIndex = pCentDedRessya->EkiIndexOfEkiOrder(iSihatsuEkiOrder);
					int iSihatsuCoreEkiOrder = -1;
					if (iSihatsuCoreEkiIndex != -1)
					{
						iSihatsuCoreEkiOrder = pCentDedRessya->EkiOrderOfEkiIndex(iSihatsuCoreEkiOrder);
					}

					int iSyuuchakuEkiOrder = itr->iSyuuchakuEkiOrder;
					if (!pCentDedRessya->isRunBetweenNextEki(iSyuuchakuEkiOrder - 1))
					{
						iSyuuchakuEkiOrder = pCentDedRessya->getRunBetweenEkiBackward(iSyuuchakuEkiOrder);
					}
					int iSyuuchakuCoreEkiIndex =
						pCentDedEkiCont->get(pCentDedEkiCont->EkiIndexOfEkiOrder(itr->aRessyaProperty.getRessyahoukou(), iSyuuchakuEkiOrder)).getBrunchCoreEkiIndex();
					int iSyuuchakuEkiIndex = pCentDedRessya->EkiIndexOfEkiOrder(iSyuuchakuEkiOrder);
					int iSyuuchakuCoreEkiOrder = -1;
					if (iSyuuchakuCoreEkiIndex != -1)
					{
						iSyuuchakuCoreEkiOrder = pCentDedRessya->EkiOrderOfEkiIndex(iSyuuchakuCoreEkiIndex);
					}

					int iPrevContinueCoreEkiIndex = -1;
					if (iPrevContinueEkiIndex != -1)
					{
						iPrevContinueCoreEkiIndex = pCentDedEkiCont->get(iPrevContinueEkiIndex).getBrunchCoreEkiIndex();
					}

					int iNextContinueCoreEkiIndex = -1;
					if (iNextContinueEkiIndex != -1)
					{
						iNextContinueCoreEkiIndex = pCentDedEkiCont->get(iNextContinueEkiIndex).getBrunchCoreEkiIndex();
					}

					//列車番号等の表示処理は、iContinueEkiIndex == -1(他列車からの継続ではない場合)のみ実行します。
					if (iPrevContinueEkiIndex == -1)
					{
						aRow.getCellCont()->insert(CdCsvCell(pCentDedRessya->getRessyabangou()));
						aRow2.getCellCont()->insert(CdCsvCell());
						aRow3.getCellCont()->insert(CdCsvCell());

						int iRessyaSyubetsuIndex = pCentDedRessya->getRessyasyubetsuIndex();
						if (pCentDedRessyasyubetsuContGet->get(iRessyaSyubetsuIndex)->getParentSyubetsuIndex() >= 0 &&
							bDisplayParentSyubetsu)
						{
							iRessyaSyubetsuIndex = pCentDedRessyasyubetsuContGet->get(iRessyaSyubetsuIndex)->getParentSyubetsuIndex();
						}
						aRow.getCellCont()->insert(CdCsvCell(
							pCentDedRessyasyubetsuContGet->get(iRessyaSyubetsuIndex)->getSyubetsumei()));
						aRow2.getCellCont()->insert(CdCsvCell());
						aRow3.getCellCont()->insert(CdCsvCell());

						if (bDisplayRessyamei)
						{
							aRow.getCellCont()->insert(CdCsvCell(pCentDedRessya->getRessyamei()));
							aRow2.getCellCont()->insert(CdCsvCell());
							aRow3.getCellCont()->insert(CdCsvCell());

							aRow.getCellCont()->insert(CdCsvCell(pCentDedRessya->getGousuu()));
							aRow2.getCellCont()->insert(CdCsvCell());
							aRow3.getCellCont()->insert(CdCsvCell());

							if (pCentDedRessya->getGousuu().empty())
							{
								aRow.getCellCont()->insert(CdCsvCell());
								aRow2.getCellCont()->insert(CdCsvCell());
								aRow3.getCellCont()->insert(CdCsvCell());
							}
							else
							{
								aRow.getCellCont()->insert(CdCsvCell(m_nameGou));
								aRow2.getCellCont()->insert(CdCsvCell());
								aRow3.getCellCont()->insert(CdCsvCell());
							}
						}
					}

					for (int idx = 0; idx < (int)iDisplayJikokuEkiIndex.size(); idx++)
					{
						/**
							以下の条件を満たすときは、この列への描写処理をスキップします
							・iContinueEkiIndexが-1以外
							・下り列車の場合、m_iDisplayJikokuEkiIndex[idx]がiContinueEkiIndexよりも小さい場合
							・上り列車の場合、m_iDisplayJikokuEkiIndex[idx]がiContinueEkiIndexよりも大きい場合

							・iPrevContinueEkiIndexが-1以外かつiPrevContinueCoreEkiIndexが-1かつm_iDisplayJikokuEkiIndex[idx]がiPrevContinueEkiIndexよりも小さい
							・iPrevContinueEkiIndexが-1以外かつiPrevContinueCoreEkiIndexが-1以外かつm_iDisplayJikokuEkiIndex[idx]がiPrevContinueCoreEkiIndexよりも小さい
							・iNextContinueEkiIndexが-1以外かつiNextContinueCoreEkiIndexが-1かつm_iDisplayJikokuEkiIndex[idx]がiNextContinueEkiIndexよりも大きい
							・iNextContinueEkiIndexが-1以外かつiNextContinueCoreEkiIndexが-1以外かつm_iDisplayJikokuEkiIndex[idx]がiNextContinueCoreEkiIndexよりも大きい
						*/
						if (itr->aRessyaProperty.getRessyahoukou() == ERessyahoukou::Ressyahoukou_Kudari)
						{
							if (iPrevContinueEkiIndex != -1)
							{
								if (iPrevContinueCoreEkiIndex == -1 &&
									iDisplayJikokuEkiIndex[idx] < iPrevContinueEkiIndex)
								{
									continue;
								}
								else if (iPrevContinueCoreEkiIndex != -1 &&
									iDisplayJikokuEkiIndex[idx] < iPrevContinueCoreEkiIndex)
								{
									continue;
								}
							}

							if (iNextContinueEkiIndex != -1)
							{
								if (iNextContinueCoreEkiIndex == -1 &&
									iDisplayJikokuEkiIndex[idx] > iNextContinueEkiIndex)
								{
									continue;
								}
								else if (iNextContinueCoreEkiIndex != -1 &&
									iDisplayJikokuEkiIndex[idx] > iNextContinueCoreEkiIndex)
								{
									continue;
								}
							}
						}
						else if (itr->aRessyaProperty.getRessyahoukou() == ERessyahoukou::Ressyahoukou_Nobori)
						{
							if (iPrevContinueEkiIndex != -1)
							{
								if (iPrevContinueCoreEkiIndex == -1 &&
									iDisplayJikokuEkiIndex[idx] > iPrevContinueEkiIndex)
								{
									continue;
								}
								else if (iPrevContinueCoreEkiIndex != -1 &&
									iDisplayJikokuEkiIndex[idx] > iPrevContinueCoreEkiIndex)
								{
									continue;
								}
							}

							if (iNextContinueEkiIndex != -1)
							{
								if (iNextContinueCoreEkiIndex == -1 &&
									iDisplayJikokuEkiIndex[idx] < iNextContinueEkiIndex)
								{
									continue;
								}
								else if (iNextContinueCoreEkiIndex != -1 &&
									iDisplayJikokuEkiIndex[idx] < iNextContinueCoreEkiIndex)
								{
									continue;
								}
							}
						}
						/**
							ColumnType_JikokuDisplayEkiに表示するもの
							・運行範囲内の時刻表示駅→着発時刻
							・運行範囲内の非時刻表示駅(路線外発着以外の始発・終着駅を除く)→空白
							・
						*/
						tstring strChaku = _T("");
						tstring strHatsu = _T("");
						/**
							当該セルにおける横線の形式
							-1:線無し
							0:横線全域
							1:右半分
							2:左半分
							3:全域(破線)(経由なし)
						*/
						int iHorizontalLineType = -1;
						/**
							当該セルにおける縦線の形式
							-1:上方向
							0:無し
							1:下方向
						*/
						int iVerticalLineType = 0;

						bool bSkipChaku = false;
						bool bSkipLine = false;
						bool bSkipHatsu = false;

						if (iDisplayJikokuEkiIndex[idx] == INT_MIN)
						{
							if (itr->aRessyaProperty.getRessyahoukou() == ERessyahoukou::Ressyahoukou_Kudari)
							{
								//路線外始発
								if (itr->iOuterShihatsuekiIndex != INT_MIN &&
									(iSihatsuEkiIndex <= iDisplayJikokuEkiIndex[idx + 1] ||
									(iSihatsuCoreEkiIndex != -1 &&
										iSihatsuCoreEkiIndex <= iDisplayJikokuEkiIndex[idx + 1])))
								{
									strChaku = pCdDedEkiContKudari->get(iSihatsuEkiOrder).getOuterTerminalEkimei(itr->iOuterShihatsuekiIndex);

									strHatsu = getCdDedJikokuConv().encode(itr->OuterShihatsuJikoku, false);
									iHorizontalLineType = 1;
								}
							}
							else
							{
								//int iSyuuchakuEkiIndex = pCentDedRessya->EkiIndexOfEkiOrder(itr->iSyuuchakuEkiOrder);
								if (itr->iOuterShuchakuekiIndex != INT_MIN &&
									(iSyuuchakuEkiIndex <= iDisplayJikokuEkiIndex[idx + 1] ||
									(iSyuuchakuCoreEkiIndex != -1 &&
										iSyuuchakuCoreEkiIndex <= iDisplayJikokuEkiIndex[idx + 1])))
								{
									//路線外終着
									strHatsu = pCdDedEkiContNobori->get(iSyuuchakuEkiOrder).getOuterTerminalEkimei(itr->iOuterShuchakuekiIndex);

									strChaku = getCdDedJikokuConv().encode(itr->OuterShuchakuJikoku, true);
									iHorizontalLineType = 1;
								}

							}
						}
						else if (iDisplayJikokuEkiIndex[idx] == INT_MAX)
						{
							if (itr->aRessyaProperty.getRessyahoukou() == ERessyahoukou::Ressyahoukou_Kudari)
							{
								//路線外終着
								if (itr->iOuterShuchakuekiIndex != INT_MIN &&
									(iSyuuchakuEkiIndex >= iDisplayJikokuEkiIndex[idx - 1] ||
									(iSyuuchakuCoreEkiIndex != -1 &&
										iSyuuchakuCoreEkiIndex >= iDisplayJikokuEkiIndex[idx - 1])))
								{
									strHatsu = pCdDedEkiContKudari->get(iSyuuchakuEkiOrder).getOuterTerminalEkimei(itr->iOuterShuchakuekiIndex);

									strChaku = getCdDedJikokuConv().encode(itr->OuterShuchakuJikoku, true);
									iHorizontalLineType = 2;
								}
							}
							else
							{
								//路線外始発
								//int iSihatsuEkiIndex = pCentDedRessya->EkiIndexOfEkiOrder(iSihatsuEkiOrder);
								if (itr->iOuterShihatsuekiIndex != INT_MIN &&
									(iSihatsuEkiIndex >= iDisplayJikokuEkiIndex[idx - 1] ||
									(iSihatsuCoreEkiIndex != -1 &&
										iSihatsuCoreEkiIndex >= iDisplayJikokuEkiIndex[idx - 1])))
								{
									strChaku = pCdDedEkiContNobori->get(iSihatsuEkiOrder).getOuterTerminalEkimei(itr->iOuterShihatsuekiIndex);

									strHatsu = getCdDedJikokuConv().encode(itr->OuterShihatsuJikoku, false);
									iHorizontalLineType = 2;
								}

							}
						}
						else
						{
							if (itr->aRessyaProperty.getRessyahoukou() == ERessyahoukou::Ressyahoukou_Kudari)
							{
								/**
									表示駅が始発駅よりも前の場合、路線外始発かつ一つ右側の表示駅の駅Indexが始発駅の駅Indexと同じか大きい場合は、
									この項に路線外始発を表示します。
								*/
								if (iSihatsuEkiIndex > iDisplayJikokuEkiIndex[idx])
								{
									if (iSihatsuCoreEkiIndex != -1)
									{
										if (iSihatsuCoreEkiIndex > iDisplayJikokuEkiIndex[idx])
										{
											if (itr->iOuterShihatsuekiIndex != INT_MIN &&
												iSihatsuCoreEkiIndex <= iDisplayJikokuEkiIndex[idx + 1])
											{
												//路線外始発
												strChaku = pCdDedEkiContKudari->get(iSihatsuCoreEkiOrder).getOuterTerminalEkimei(itr->iOuterShihatsuekiIndex);

												strHatsu = getCdDedJikokuConv().encode(itr->OuterShihatsuJikoku, false);
												iHorizontalLineType = 1;
											}
											else if (iPrevContinueEkiIndex != -1)
											{
												/**
													同一行表示の前列車がある場合、
													表示駅が前列車終着駅の場合は、始発駅発時刻を表示する(着時刻およびラインは前列車の管轄)
													前列車終着駅とこの列車の始発駅の間の場合は破線だが、ここでは前列車の管轄となる。
													ただし、この駅が時刻非表示駅なら、時刻・番線は非表示にする
												*/
												if ((iPrevContinueCoreEkiIndex == -1 &&
													iPrevContinueEkiIndex == iDisplayJikokuEkiIndex[idx]) ||
													(iPrevContinueCoreEkiIndex != -1 &&
														iPrevContinueCoreEkiIndex == iDisplayJikokuEkiIndex[idx]))
												{
													if (pCentDedEkiCont->getMuPtr()->get(iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
														(bDisplayTsuukaEkiJikoku ||
															pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya))
													{
														strHatsu = getCdDedJikokuConv().encode(
															pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getVirtualHatsujikoku(), false);
													}
													bSkipLine = true;
													bSkipChaku = true;
													if (pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka &&
														!strHatsu.empty())
													{
														strHatsu += _T("?");
													}
												}
												else if ((iPrevContinueCoreEkiIndex == -1 &&
													iPrevContinueEkiIndex < iDisplayJikokuEkiIndex[idx]) ||
													(iPrevContinueCoreEkiIndex != -1 &&
														iPrevContinueCoreEkiIndex < iDisplayJikokuEkiIndex[idx]))
												{
													//ここでは本来不要だが、CSV出力時はセル数合わせのため、スキップが必須となるので加えておく
													bSkipLine = true;
													bSkipChaku = true;
												}
											}
										}
										else if (iSihatsuCoreEkiIndex == iDisplayJikokuEkiIndex[idx])
										{
											if (itr->iOuterShihatsuekiIndex != INT_MIN)
											{
												if (pCentDedEkiCont->getMuPtr()->get(iSihatsuCoreEkiIndex)->getOperationTableDisplayJikoku())
												{
													//路線外始発のデータ上始発駅
													CdDedJikoku ChakuJikoku = itr->ChakuJikoku;
													CdDedJikoku HatsuJikoku = pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getHatsujikoku();
													if (!ChakuJikoku.isNull())
													{
														HatsuJikoku = pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getVirtualHatsujikoku();
													}

													strChaku = getCdDedJikokuConv().encode(ChakuJikoku, true, HatsuJikoku);
													strHatsu = getCdDedJikokuConv().encode(HatsuJikoku, false, ChakuJikoku);

													if (bDisplayTrackName)
													{
														//if (!strChaku.empty())
														//{
														//	strChaku += _T(" ");
														//}
														strChaku += _T("(");
														strChaku += pCdDedEkiContKudari->get(iSihatsuEkiOrder).getCentDedEkiTrack2Cont().get(
															pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(pCentDedRessya->getRessyahoukou());
														strChaku += _T(")");
													}
												}
												iHorizontalLineType = 0;
											}
											else
											{
												//始発駅
												//前列車と同一行に表示する場合、この駅が時刻非表示駅または駅扱い通過かつ通過駅時刻非表示の場合は、時刻を表示しません
												if (iPrevContinueEkiIndex == -1 ||
													(pCentDedEkiCont->getMuPtr()->get(iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
														(bDisplayTsuukaEkiJikoku ||
															pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya)))
												{
													strHatsu = getCdDedJikokuConv().encode(
														pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getVirtualHatsujikoku(), false);
												}
												iHorizontalLineType = 1;
												//前列車と同一行に表示する場合、この駅の着時刻および横線は、前列車の管轄で描写します
												if (iPrevContinueEkiIndex != -1)
												{
													bSkipChaku = true;
													bSkipLine = true;
													if (pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka &&
														!strHatsu.empty())
													{
														strHatsu += _T("?");
													}
												}

												if (itr->eBeforeType == EBeforeAfterType::BeforeAfterType_OutIn)
												{
													iVerticalLineType = -2;
												}
												else if (iPrevShuchakuEkiIndex != -1 &&
													iPrevShuchakuEkiIndex == iSihatsuCoreEkiIndex)
												{
													iVerticalLineType = -1;
												}

												if (bDisplayTrackName &&
													iPrevContinueEkiIndex == -1)
												{
													if (iVerticalLineType == 0)
													{
														strChaku += _T("(");
														strChaku += pCdDedEkiContKudari->get(iSihatsuEkiOrder).getCentDedEkiTrack2Cont().get(
															pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(pCentDedRessya->getRessyahoukou());
														strChaku += _T(")");
													}
													else
													{
														//strHatsu += _T(" ");

														strHatsu += _T("(");
														strHatsu += pCdDedEkiContKudari->get(iSihatsuEkiOrder).getCentDedEkiTrack2Cont().get(
															pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(pCentDedRessya->getRessyahoukou());
														strHatsu += _T(")");
													}
												}
											}
										}
										else//sihatsuCore<iDisplayJikokuEkiIndex[idx]<Sihatsu
										{
											//経由無し
											iHorizontalLineType = 3;
										}

									}
									else if (itr->iOuterShihatsuekiIndex != INT_MIN &&
										iSihatsuEkiIndex <= iDisplayJikokuEkiIndex[idx + 1])
									{
										//路線外始発
										strChaku = pCdDedEkiContKudari->get(iSihatsuEkiOrder).getOuterTerminalEkimei(itr->iOuterShihatsuekiIndex);

										strHatsu = getCdDedJikokuConv().encode(itr->OuterShihatsuJikoku, false);
										iHorizontalLineType = 1;
									}
									else if (iPrevContinueEkiIndex != -1)
									{
										/**
											同一行表示の前列車がある場合、
											表示駅が前列車終着駅の場合は、始発駅発時刻を表示する(着時刻およびラインは前列車の管轄)
											前列車終着駅とこの列車の始発駅の間の場合は破線だが、ここでは前列車の管轄となる。
											ただし、この駅が時刻非表示駅なら、時刻・番線は非表示にする
										*/
										if ((iPrevContinueCoreEkiIndex == -1 &&
											iPrevContinueEkiIndex == iDisplayJikokuEkiIndex[idx]) ||
											(iPrevContinueCoreEkiIndex != -1 &&
												iPrevContinueCoreEkiIndex == iDisplayJikokuEkiIndex[idx]))
										{
											if (pCentDedEkiCont->getMuPtr()->get(iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
												(bDisplayTsuukaEkiJikoku ||
													pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya))
											{
												strHatsu = getCdDedJikokuConv().encode(
													pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getVirtualHatsujikoku(), false);
											}
											bSkipLine = true;
											bSkipChaku = true;
											if (pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka &&
												!strHatsu.empty())
											{
												strHatsu += _T("?");
											}
										}
										else if ((iPrevContinueCoreEkiIndex == -1 &&
											iPrevContinueEkiIndex < iDisplayJikokuEkiIndex[idx]) ||
											(iPrevContinueCoreEkiIndex != -1 &&
												iPrevContinueCoreEkiIndex < iDisplayJikokuEkiIndex[idx]))
										{
											//ここでは本来不要だが、CSV出力時はセル数合わせのため、スキップが必須となるので加えておく
											bSkipLine = true;
											bSkipChaku = true;
										}
									}
								}
								/**
									表示駅が終着駅よりも後の場合、路線外終着かつ一つ左側の表示駅の駅Indexが終着駅の駅Indexと同じか小さい場合は、
									この項に路線外終着を表示します。
								*/
								else if (iSyuuchakuEkiIndex < iDisplayJikokuEkiIndex[idx])
								{
									if (iSyuuchakuCoreEkiIndex != -1)
									{
										if (iSyuuchakuCoreEkiIndex < iDisplayJikokuEkiIndex[idx])
										{
											if (itr->iOuterShuchakuekiIndex != INT_MIN &&
												iSyuuchakuCoreEkiIndex >= iDisplayJikokuEkiIndex[idx - 1])
											{
												//路線外終着
												strHatsu = pCdDedEkiContKudari->get(iSyuuchakuCoreEkiOrder).getOuterTerminalEkimei(itr->iOuterShuchakuekiIndex);

												strChaku = getCdDedJikokuConv().encode(itr->OuterShuchakuJikoku, true);
												iHorizontalLineType = 2;
											}
											else if (iNextContinueEkiIndex != -1)
											{
												/**
													同一行表示の次列車がある場合、
													表示駅が次列車始発駅の場合は、終着駅着時刻とラインを表示する(発時刻は次列車の管轄)
													この列車の終着駅と次列車始発駅との間の場合は破線となり、この列車が描写責任を持つ
													ただし、この駅が時刻非表示駅なら、時刻・番線は非表示にする
												*/
												if ((iNextContinueCoreEkiIndex == -1 &&
													iNextContinueEkiIndex == iDisplayJikokuEkiIndex[idx]) ||
													(iNextContinueCoreEkiIndex != -1 &&
														iNextContinueCoreEkiIndex == iDisplayJikokuEkiIndex[idx]))
												{
													if (pCentDedEkiCont->getMuPtr()->get(iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
														(bDisplayTsuukaEkiJikoku ||
															pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya))
													{
														strChaku = getCdDedJikokuConv().encode(
															pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getVirtualChakujikoku(), true);
													}
													iHorizontalLineType = 0;

													if (bDisplayTrackName &&
														pCentDedEkiCont->getMuPtr()->get(iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku())
													{
														strChaku += _T("(");
														strChaku += pCdDedEkiContKudari->get(iSyuuchakuEkiOrder).getCentDedEkiTrack2Cont().get(
															pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(pCentDedRessya->getRessyahoukou());
														strChaku += _T(")");
													}
													bSkipHatsu = true;
													if (pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
													{
														strChaku += _T("?");
													}
												}
												else if ((iNextContinueCoreEkiIndex == -1 &&
													iNextContinueEkiIndex > iDisplayJikokuEkiIndex[idx]) ||
													(iNextContinueCoreEkiIndex != -1 &&
														iNextContinueCoreEkiIndex > iDisplayJikokuEkiIndex[idx]))
												{
													iHorizontalLineType = 3;
													//ここでは本来不要だが、CSV出力時はセル数合わせのため、スキップが必須となるので加えておく
													bSkipHatsu = true;
												}
											}

										}
										else if (iSyuuchakuCoreEkiIndex == iDisplayJikokuEkiIndex[idx])
										{
											if (itr->iOuterShuchakuekiIndex != INT_MIN)
											{
												if (pCentDedEkiCont->getMuPtr()->get(iSyuuchakuCoreEkiIndex)->getOperationTableDisplayJikoku())
												{
													//路線外終着のデータ上終着駅
													CdDedJikoku ChakuJikoku = pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getChakujikoku();
													CdDedJikoku HatsuJikoku = itr->HatsuJikoku;
													if (!HatsuJikoku.isNull())
													{
														ChakuJikoku = pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getVirtualChakujikoku();
													}

													strChaku = getCdDedJikokuConv().encode(ChakuJikoku, true, HatsuJikoku);
													strHatsu = getCdDedJikokuConv().encode(HatsuJikoku, false, ChakuJikoku);

													if (bDisplayTrackName)
													{
														if (strHatsu.empty())
														{
															strHatsu += _T("(");
															strHatsu += pCdDedEkiContKudari->get(iSyuuchakuEkiOrder).getCentDedEkiTrack2Cont().get(
																pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(pCentDedRessya->getRessyahoukou());
															strHatsu += _T(")");
														}
														else
														{
															//strChaku += _T(" ");

															strChaku += _T("(");
															strChaku += pCdDedEkiContKudari->get(iSyuuchakuEkiOrder).getCentDedEkiTrack2Cont().get(
																pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(pCentDedRessya->getRessyahoukou());
															strChaku += _T(")");
														}
													}
												}
												iHorizontalLineType = 0;
											}
											else
											{
												//終着駅
												//次列車と同一行に表示する場合、この駅が時刻非表示駅または駅扱い通過かつ通過駅時刻非表示の場合は、時刻を表示しません
												if (iNextContinueEkiIndex == -1 ||
													(pCentDedEkiCont->getMuPtr()->get(iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
														(bDisplayTsuukaEkiJikoku ||
															pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya)))
												{
													strChaku = getCdDedJikokuConv().encode(
														pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getVirtualChakujikoku(), true);
												}
												iHorizontalLineType = 2;
												//次列車と同一行に表示する場合、この駅の発時刻は、次列車の管轄で描写します。横線は全域になります。
												if (iNextContinueEkiIndex != -1)
												{
													iHorizontalLineType = 0;
													bSkipHatsu = true;
													if (pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka&&
														!strChaku.empty())
													{
														strChaku += _T("?");
													}
												}
												if (itr->eAfterType == EBeforeAfterType::BeforeAfterType_OutIn)
												{
													iVerticalLineType = 2;
												}
												else if (iNextShihatsuEkiIndex != -1 &&
													iNextShihatsuEkiIndex == iSyuuchakuCoreEkiIndex)
												{
													iVerticalLineType = 1;
												}

												if (bDisplayTrackName)
												{
													if (iVerticalLineType == 0 &&
														iNextContinueEkiIndex == -1)
													{
														strHatsu += _T("(");
														strHatsu += pCdDedEkiContKudari->get(iSyuuchakuEkiOrder).getCentDedEkiTrack2Cont().get(
															pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(pCentDedRessya->getRessyahoukou());
														strHatsu += _T(")");
													}
													else
													{
														//strChaku += _T(" ");

														strChaku += _T("(");
														strChaku += pCdDedEkiContKudari->get(iSyuuchakuEkiOrder).getCentDedEkiTrack2Cont().get(
															pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(pCentDedRessya->getRessyahoukou());
														strChaku += _T(")");
													}
												}
											}
										}
										else//sihatsuCore<iDisplayJikokuEkiIndex[idx]<Sihatsu
										{
											//経由無し
											iHorizontalLineType = 3;
										}
									}
									else if (itr->iOuterShuchakuekiIndex != INT_MIN &&
										iSyuuchakuEkiIndex >= iDisplayJikokuEkiIndex[idx - 1])
									{
										//路線外終着
										strHatsu = pCdDedEkiContKudari->get(iSyuuchakuEkiOrder).getOuterTerminalEkimei(itr->iOuterShuchakuekiIndex);

										strChaku = getCdDedJikokuConv().encode(itr->OuterShuchakuJikoku, true);
										iHorizontalLineType = 2;
									}
									else if (iNextContinueEkiIndex != -1)
									{
										/**
											同一行表示の次列車がある場合、
											表示駅が次列車始発駅の場合は、終着駅着時刻とラインを表示する(発時刻は次列車の管轄)
											この列車の終着駅と次列車始発駅との間の場合は破線となり、この列車が描写責任を持つ
											ただし、この駅が時刻非表示駅なら、時刻・番線は非表示にする
										*/
										if ((iNextContinueCoreEkiIndex == -1 &&
											iNextContinueEkiIndex == iDisplayJikokuEkiIndex[idx]) ||
											(iNextContinueCoreEkiIndex != -1 &&
												iNextContinueCoreEkiIndex == iDisplayJikokuEkiIndex[idx]))
										{
											if (pCentDedEkiCont->getMuPtr()->get(iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
												(bDisplayTsuukaEkiJikoku ||
													pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya))
											{
												strChaku = getCdDedJikokuConv().encode(
													pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getVirtualChakujikoku(), true);
											}
											iHorizontalLineType = 0;

											if (bDisplayTrackName &&
												pCentDedEkiCont->getMuPtr()->get(iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku())
											{
												strChaku += _T("(");
												strChaku += pCdDedEkiContKudari->get(iSyuuchakuEkiOrder).getCentDedEkiTrack2Cont().get(
													pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(pCentDedRessya->getRessyahoukou());
												strChaku += _T(")");
											}
											bSkipHatsu = true;
											if (pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka &&
												!strChaku.empty())
											{
												strChaku += _T("?");
											}
										}
										else if ((iNextContinueCoreEkiIndex == -1 &&
											iNextContinueEkiIndex > iDisplayJikokuEkiIndex[idx]) ||
											(iNextContinueCoreEkiIndex != -1 &&
												iNextContinueCoreEkiIndex > iDisplayJikokuEkiIndex[idx]))
										{
											iHorizontalLineType = 3;
											//ここでは本来不要だが、CSV出力時はセル数合わせのため、スキップが必須となるので加えておく
											bSkipHatsu = true;
										}
									}

								}
								/**
									表示駅が始発駅の場合、路線外始発なら、この駅の時刻表示は駅設定に依存します
									出区・前列車接続の場合は、発時刻を表示します。
								*/
								else if (iSihatsuEkiIndex == iDisplayJikokuEkiIndex[idx])
								{
									if (itr->iOuterShihatsuekiIndex != INT_MIN)
									{
										if (pCentDedEkiCont->getMuPtr()->get(iSihatsuEkiIndex)->getOperationTableDisplayJikoku())
										{
											//路線外始発のデータ上始発駅
											CdDedJikoku ChakuJikoku = itr->ChakuJikoku;
											CdDedJikoku HatsuJikoku = pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getHatsujikoku();
											if (!ChakuJikoku.isNull())
											{
												HatsuJikoku = pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getVirtualHatsujikoku();
											}

											strChaku = getCdDedJikokuConv().encode(ChakuJikoku, true, HatsuJikoku);
											strHatsu = getCdDedJikokuConv().encode(HatsuJikoku, false, ChakuJikoku);

											if (bDisplayTrackName)
											{
												//if (!strChaku.empty())
												//{
												//	strChaku += _T(" ");
												//}
												strChaku += _T("(");
												strChaku += pCdDedEkiContKudari->get(iSihatsuEkiOrder).getCentDedEkiTrack2Cont().get(
													pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(pCentDedRessya->getRessyahoukou());
												strChaku += _T(")");
											}
										}
										iHorizontalLineType = 0;
									}
									else
									{
										//始発駅
										//前列車と同一行に表示する場合、この駅が時刻非表示駅または駅扱い通過かつ通過駅時刻非表示の場合は、時刻を表示しません
										if (iPrevContinueEkiIndex == -1 ||
											(pCentDedEkiCont->getMuPtr()->get(iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
												(bDisplayTsuukaEkiJikoku ||
													pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya)))
										{
											strHatsu = getCdDedJikokuConv().encode(
												pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getVirtualHatsujikoku(), false);
										}
										iHorizontalLineType = 1;
										//前列車と同一行に表示する場合、この駅の着時刻および横線は、前列車の管轄で描写します
										if (iPrevContinueEkiIndex != -1)
										{
											bSkipChaku = true;
											bSkipLine = true;
											if (pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka &&
												!strHatsu.empty())
											{
												strHatsu += _T("?");
											}
										}

										if (itr->eBeforeType == EBeforeAfterType::BeforeAfterType_OutIn)
										{
											iVerticalLineType = -2;
										}
										else if (iPrevShuchakuEkiIndex != -1 &&
											iPrevShuchakuEkiIndex == iSihatsuEkiIndex)
										{
											iVerticalLineType = -1;
										}

										if (bDisplayTrackName &&
											iPrevContinueEkiIndex == -1)
										{
											if (iVerticalLineType == 0)
											{
												strChaku += _T("(");
												strChaku += pCdDedEkiContKudari->get(iSihatsuEkiOrder).getCentDedEkiTrack2Cont().get(
													pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(pCentDedRessya->getRessyahoukou());
												strChaku += _T(")");
											}
											else
											{
												//strHatsu += _T(" ");

												strHatsu += _T("(");
												strHatsu += pCdDedEkiContKudari->get(iSihatsuEkiOrder).getCentDedEkiTrack2Cont().get(
													pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(pCentDedRessya->getRessyahoukou());
												strHatsu += _T(")");
											}
										}
									}
								}
								/**
									表示駅が終着駅の場合、路線外終着なら、この駅の時刻表示は駅設定に依存します
									入区・次列車接続の場合は、着時刻を表示します。
								*/
								else if (iSyuuchakuEkiIndex == iDisplayJikokuEkiIndex[idx])
								{
									if (itr->iOuterShuchakuekiIndex != INT_MIN)
									{
										if (pCentDedEkiCont->getMuPtr()->get(iSyuuchakuEkiIndex)->getOperationTableDisplayJikoku())
										{
											//路線外終着のデータ上終着駅
											CdDedJikoku ChakuJikoku = pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getChakujikoku();
											CdDedJikoku HatsuJikoku = itr->HatsuJikoku;
											if (!HatsuJikoku.isNull())
											{
												ChakuJikoku = pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getVirtualChakujikoku();
											}

											strChaku = getCdDedJikokuConv().encode(ChakuJikoku, true, HatsuJikoku);
											strHatsu = getCdDedJikokuConv().encode(HatsuJikoku, false, ChakuJikoku);

											if (bDisplayTrackName)
											{
												if (strHatsu.empty())
												{
													strHatsu += _T("(");
													strHatsu += pCdDedEkiContKudari->get(iSyuuchakuEkiOrder).getCentDedEkiTrack2Cont().get(
														pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(pCentDedRessya->getRessyahoukou());
													strHatsu += _T(")");
												}
												else
												{
													//strChaku += _T(" ");

													strChaku += _T("(");
													strChaku += pCdDedEkiContKudari->get(iSyuuchakuEkiOrder).getCentDedEkiTrack2Cont().get(
														pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(pCentDedRessya->getRessyahoukou());
													strChaku += _T(")");
												}
											}
										}
										iHorizontalLineType = 0;
									}
									else
									{
										//終着駅
										//次列車と同一行に表示する場合、この駅が時刻非表示駅または駅扱い通過かつ通過駅時刻非表示の場合は、時刻を表示しません
										if (iNextContinueEkiIndex == -1 ||
											(pCentDedEkiCont->getMuPtr()->get(iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
												(bDisplayTsuukaEkiJikoku ||
													pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya)))
										{
											strChaku = getCdDedJikokuConv().encode(
												pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getVirtualChakujikoku(), true);
										}
										iHorizontalLineType = 2;
										//次列車と同一行に表示する場合、この駅の発時刻は、次列車の管轄で描写します。横線は全域になります。
										if (iNextContinueEkiIndex != -1)
										{
											iHorizontalLineType = 0;
											bSkipHatsu = true;
											if (pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka &&
												!strChaku.empty())
											{
												strChaku += _T("?");
											}
										}
										if (itr->eAfterType == EBeforeAfterType::BeforeAfterType_OutIn)
										{
											iVerticalLineType = 2;
										}
										else if (iNextShihatsuEkiIndex != -1 &&
											iNextShihatsuEkiIndex == iSyuuchakuEkiIndex)
										{
											iVerticalLineType = 1;
										}

										if (bDisplayTrackName)
										{
											if (iVerticalLineType == 0 &&
												iNextContinueEkiIndex == -1)
											{
												strHatsu += _T("(");
												strHatsu += pCdDedEkiContKudari->get(iSyuuchakuEkiOrder).getCentDedEkiTrack2Cont().get(
													pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(pCentDedRessya->getRessyahoukou());
												strHatsu += _T(")");
											}
											else
											{
												//strChaku += _T(" ");

												strChaku += _T("(");
												strChaku += pCdDedEkiContKudari->get(iSyuuchakuEkiOrder).getCentDedEkiTrack2Cont().get(
													pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(pCentDedRessya->getRessyahoukou());
												strChaku += _T(")");
											}
										}
									}
								}
								/**
									表示駅が始発駅から終着駅の間の場合、その駅が時刻表示駅なのかで、時刻を表示するかどうかが変わります

								*/
								else//sihatsu<iDisplayJikokuEkiIndex[idx]<syuchaku
								{
									int iEkiOrder = pCentDedRessya->EkiOrderOfEkiIndex(iDisplayJikokuEkiIndex[idx]);
									int iRessyaTrackIndex = -1;
									CentDedEkiJikoku aEkiJikoku = pCentDedRessya->getCentDedEkiJikoku(iEkiOrder);

									//着時刻側
									bool bChakuIsNone = true;
									CdDedJikoku ChakuJikoku;
									if (pCentDedRessya->isRunBetweenNextEki(iEkiOrder - 1))
									{
										bChakuIsNone = false;
										if (pCentDedEkiCont->getMuPtr()->get(iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
											(bDisplayTsuukaEkiJikoku ||
												aEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya))
										{
											ChakuJikoku = aEkiJikoku.getVirtualChakujikoku();
											if (!ChakuJikoku.isNull() &&
												aEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
											{
												strChaku = _T("?");
												//aCdDrawTextPropChaku.setTextColor(CdColorProp(128, 128, 128));
											}
										}
										iRessyaTrackIndex = aEkiJikoku.getRessyaTrackIndex();
									}
									else
									{
										int iPrevEkiOrder = pCentDedRessya->getRunBetweenEkiBackward(iEkiOrder);
										if (iPrevEkiOrder != -1)
										{
											if (pCentDedEkiCont->isSameBrunchLoopGroup(iPrevEkiOrder, iEkiOrder, pCentDedRessya->getRessyahoukou()))
											{
												bChakuIsNone = false;
												CentDedEkiJikoku aPrevEkiJikoku = pCentDedRessya->getCentDedEkiJikoku(iPrevEkiOrder);
												if (pCentDedEkiCont->getMuPtr()->get(iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
													(bDisplayTsuukaEkiJikoku ||
														aPrevEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya))
												{
													ChakuJikoku = aPrevEkiJikoku.getVirtualChakujikoku();
													if (!ChakuJikoku.isNull() &&
														aPrevEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
													{
														strChaku = _T("?");
														//aCdDrawTextPropChaku.setTextColor(CdColorProp(128, 128, 128));
													}
												}
												iRessyaTrackIndex = aPrevEkiJikoku.getRessyaTrackIndex();
											}
										}
									}

									bool bHatsuIsNone = true;
									CdDedJikoku HatsuJikoku;
									if (pCentDedRessya->isRunBetweenNextEki(iEkiOrder))
									{
										bHatsuIsNone = false;
										if (pCentDedEkiCont->getMuPtr()->get(iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
											(bDisplayTsuukaEkiJikoku ||
												aEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya))
										{
											HatsuJikoku = aEkiJikoku.getVirtualHatsujikoku();
											if (!HatsuJikoku.isNull() &&
												aEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
											{
												strHatsu = _T("?");
												//aCdDrawTextPropHatsu.setTextColor(CdColorProp(128, 128, 128));
											}
										}
										iRessyaTrackIndex = aEkiJikoku.getRessyaTrackIndex();
									}
									else
									{
										int iNextEkiOrder = pCentDedRessya->getRunBetweenEkiForward(iEkiOrder);
										if (iNextEkiOrder != -1)
										{
											if (pCentDedEkiCont->isSameBrunchLoopGroup(iNextEkiOrder, iEkiOrder, pCentDedRessya->getRessyahoukou()))
											{
												bHatsuIsNone = false;
												CentDedEkiJikoku aNextEkiJikoku = pCentDedRessya->getCentDedEkiJikoku(iNextEkiOrder);
												if (pCentDedEkiCont->getMuPtr()->get(iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
													(bDisplayTsuukaEkiJikoku ||
														aNextEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya))
												{
													HatsuJikoku = aNextEkiJikoku.getVirtualHatsujikoku();
													if (!HatsuJikoku.isNull() &&
														aNextEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
													{
														strHatsu = _T("?");
														//aCdDrawTextPropHatsu.setTextColor(CdColorProp(128, 128, 128));
													}
												}
												iRessyaTrackIndex = aNextEkiJikoku.getRessyaTrackIndex();
											}
										}
									}
									if (bChakuIsNone && bHatsuIsNone)
									{
										iHorizontalLineType = 3;
									}
									else
									{
										iHorizontalLineType = 0;
									}

									strChaku = getCdDedJikokuConv().encode(ChakuJikoku, true, HatsuJikoku) + strChaku;
									strHatsu = getCdDedJikokuConv().encode(HatsuJikoku, false, ChakuJikoku) + strHatsu;

									if (bDisplayTrackName &&
										iRessyaTrackIndex != -1 &&
										pCentDedEkiCont->getMuPtr()->get(iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku())
									{
										if (!strChaku.empty() && strHatsu.empty())
										{
											strHatsu += _T("(");
											strHatsu += pCdDedEkiContKudari->get(iEkiOrder).getCentDedEkiTrack2Cont().
												get(iRessyaTrackIndex).getTrackRyakusyou(pCentDedRessya->getRessyahoukou());
											strHatsu += _T(")");
										}
										else
										{
											//if (!strChaku.empty())
											//{
											//	strChaku += _T(" ");
											//}
											strChaku += _T("(");
											strChaku += pCdDedEkiContKudari->get(iEkiOrder).getCentDedEkiTrack2Cont().
												get(iRessyaTrackIndex).getTrackRyakusyou(pCentDedRessya->getRessyahoukou());
											strChaku += _T(")");
										}
									}
								}
							}
							else// if(itr->aRessyaProperty.getRessyahoukou() == ERessyahoukou::Ressyahoukou_Nobori)
							{
								if (iSyuuchakuEkiIndex > iDisplayJikokuEkiIndex[idx])
								{
									if (iSyuuchakuCoreEkiIndex != -1)
									{
										if (iSyuuchakuCoreEkiIndex > iDisplayJikokuEkiIndex[idx])
										{
											if (itr->iOuterShuchakuekiIndex != INT_MIN &&
												iSyuuchakuCoreEkiIndex <= iDisplayJikokuEkiIndex[idx + 1])
											{
												//路線外終着
												strHatsu = pCdDedEkiContNobori->get(iSyuuchakuEkiOrder).getOuterTerminalEkimei(itr->iOuterShuchakuekiIndex);

												strChaku = getCdDedJikokuConv().encode(itr->OuterShuchakuJikoku, true);
												iHorizontalLineType = 1;
											}
											else if (iNextContinueEkiIndex != -1)
											{
												/**
													同一行表示の次列車がある場合、
													表示駅が次列車始発駅の場合は、終着駅着時刻とラインを表示する(発時刻は次列車の管轄)
													この列車の終着駅と次列車始発駅との間の場合は破線となり、この列車が描写責任を持つ
													ただし、この駅が時刻非表示駅なら、時刻・番線は非表示にする
												*/
												if ((iNextContinueCoreEkiIndex == -1 &&
													iNextContinueEkiIndex == iDisplayJikokuEkiIndex[idx]) ||
													(iNextContinueCoreEkiIndex != -1 &&
														iNextContinueCoreEkiIndex == iDisplayJikokuEkiIndex[idx]))
												{
													if (pCentDedEkiCont->getMuPtr()->get(iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
														(bDisplayTsuukaEkiJikoku ||
															pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya))
													{
														strChaku = getCdDedJikokuConv().encode(
															pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getVirtualChakujikoku(), true);
													}
													iHorizontalLineType = 0;

													if (bDisplayTrackName &&
														pCentDedEkiCont->getMuPtr()->get(iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku())
													{
														strChaku += _T("(");
														strChaku += pCdDedEkiContNobori->get(iSyuuchakuEkiOrder).getCentDedEkiTrack2Cont().get(
															pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(pCentDedRessya->getRessyahoukou());
														strChaku += _T(")");
													}
													bSkipHatsu = true;
													if (pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
													{
														strChaku += _T("?");
													}
												}
												else if ((iNextContinueCoreEkiIndex == -1 &&
													iNextContinueEkiIndex > iDisplayJikokuEkiIndex[idx]) ||
													(iNextContinueCoreEkiIndex != -1 &&
														iNextContinueCoreEkiIndex > iDisplayJikokuEkiIndex[idx]))
												{
													iHorizontalLineType = 3;
													//ここでは本来不要だが、CSV出力時はセル数合わせのため、スキップが必須となるので加えておく
													bSkipHatsu = true;
												}
											}
										}
										else if (iSyuuchakuCoreEkiIndex == iDisplayJikokuEkiIndex[idx])
										{
											if (itr->iOuterShuchakuekiIndex != INT_MIN)
											{
												if (pCentDedEkiCont->getMuPtr()->get(iSyuuchakuCoreEkiIndex)->getOperationTableDisplayJikoku())
												{
													//路線外終着のデータ上終着駅
													CdDedJikoku ChakuJikoku = pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getChakujikoku();
													CdDedJikoku HatsuJikoku = itr->HatsuJikoku;
													if (!HatsuJikoku.isNull())
													{
														ChakuJikoku = pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getVirtualChakujikoku();
													}

													strChaku = getCdDedJikokuConv().encode(ChakuJikoku, true, HatsuJikoku);
													strHatsu = getCdDedJikokuConv().encode(HatsuJikoku, false, ChakuJikoku);

													if (bDisplayTrackName)
													{
														if (strHatsu.empty())
														{
															strHatsu += _T("(");
															strHatsu += pCdDedEkiContNobori->get(iSyuuchakuEkiOrder).getCentDedEkiTrack2Cont().get(
																pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(pCentDedRessya->getRessyahoukou());
															strHatsu += _T(")");
														}
														else
														{
															//strChaku += _T(" ");

															strChaku += _T("(");
															strChaku += pCdDedEkiContNobori->get(iSyuuchakuEkiOrder).getCentDedEkiTrack2Cont().get(
																pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(pCentDedRessya->getRessyahoukou());
															strChaku += _T(")");
														}
													}
												}
												iHorizontalLineType = 0;
											}
											else
											{
												//終着駅
												//次列車と同一行に表示する場合、この駅が時刻非表示駅または駅扱い通過かつ通過駅時刻非表示の場合は、時刻を表示しません
												if (iNextContinueEkiIndex == -1 ||
													(pCentDedEkiCont->getMuPtr()->get(iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
														(bDisplayTsuukaEkiJikoku ||
															pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya)))
												{
													strChaku = getCdDedJikokuConv().encode(
														pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getVirtualChakujikoku(), true);
												}
												iHorizontalLineType = 1;
												//次列車と同一行に表示する場合、この駅の発時刻は、次列車の管轄で描写します。横線は全域になります。
												if (iNextContinueEkiIndex != -1)
												{
													iHorizontalLineType = 0;
													bSkipHatsu = true;
													if (pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka &&
														!strChaku.empty())
													{
														strChaku += _T("?");
													}
												}
												if (itr->eAfterType == EBeforeAfterType::BeforeAfterType_OutIn)
												{
													iVerticalLineType = 2;
												}
												else if (iNextShihatsuEkiIndex != -1 &&
													iNextShihatsuEkiIndex == iSyuuchakuCoreEkiIndex)
												{
													iVerticalLineType = 1;
												}

												if (bDisplayTrackName)
												{
													if (iVerticalLineType == 0 &&
														iNextContinueEkiIndex == -1)
													{
														strHatsu += _T("(");
														strHatsu += pCdDedEkiContNobori->get(iSyuuchakuEkiOrder).getCentDedEkiTrack2Cont().get(
															pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(pCentDedRessya->getRessyahoukou());
														strHatsu += _T(")");
													}
													else
													{
														//strChaku += _T(" ");

														strChaku += _T("(");
														strChaku += pCdDedEkiContNobori->get(iSyuuchakuEkiOrder).getCentDedEkiTrack2Cont().get(
															pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(pCentDedRessya->getRessyahoukou());
														strChaku += _T(")");
													}
												}
											}
										}
										else//sihatsu<iDisplayJikokuEkiIndex[idx]<syuchaku
										{
											//経由無し
											iHorizontalLineType = 3;
										}

									}
									else if (itr->iOuterShuchakuekiIndex != INT_MIN &&
										iSyuuchakuEkiIndex <= iDisplayJikokuEkiIndex[idx + 1])
									{
										//路線外終着
										strHatsu = pCdDedEkiContNobori->get(iSyuuchakuEkiOrder).getOuterTerminalEkimei(itr->iOuterShuchakuekiIndex);

										strChaku = getCdDedJikokuConv().encode(itr->OuterShuchakuJikoku, true);
										iHorizontalLineType = 1;
									}
									else if (iNextContinueEkiIndex != -1)
									{
										/**
											同一行表示の次列車がある場合、
											表示駅が次列車始発駅の場合は、終着駅着時刻とラインを表示する(発時刻は次列車の管轄)
											この列車の終着駅と次列車始発駅との間の場合は破線となり、この列車が描写責任を持つ
											ただし、この駅が時刻非表示駅なら、時刻・番線は非表示にする
										*/
										if ((iNextContinueCoreEkiIndex == -1 &&
											iNextContinueEkiIndex == iDisplayJikokuEkiIndex[idx]) ||
											(iNextContinueCoreEkiIndex != -1 &&
												iNextContinueCoreEkiIndex == iDisplayJikokuEkiIndex[idx]))
										{
											if (pCentDedEkiCont->getMuPtr()->get(iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
												(bDisplayTsuukaEkiJikoku ||
													pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya))
											{
												strChaku = getCdDedJikokuConv().encode(
													pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getVirtualChakujikoku(), true);
											}
											iHorizontalLineType = 0;

											if (bDisplayTrackName &&
												pCentDedEkiCont->getMuPtr()->get(iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku())
											{
												strChaku += _T("(");
												strChaku += pCdDedEkiContNobori->get(iSyuuchakuEkiOrder).getCentDedEkiTrack2Cont().get(
													pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(pCentDedRessya->getRessyahoukou());
												strChaku += _T(")");
											}
											bSkipHatsu = true;
											if (pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka &&
												!strChaku.empty())
											{
												strChaku += _T("?");
											}
										}
										else if ((iNextContinueCoreEkiIndex == -1 &&
											iNextContinueEkiIndex > iDisplayJikokuEkiIndex[idx]) ||
											(iNextContinueCoreEkiIndex != -1 &&
												iNextContinueCoreEkiIndex > iDisplayJikokuEkiIndex[idx]))
										{
											iHorizontalLineType = 3;
											//ここでは本来不要だが、CSV出力時はセル数合わせのため、スキップが必須となるので加えておく
											bSkipHatsu = true;
										}
									}
								}
								else if (iSihatsuEkiIndex < iDisplayJikokuEkiIndex[idx])
								{
									if (iSihatsuCoreEkiIndex != -1)
									{
										if (iSihatsuCoreEkiIndex < iDisplayJikokuEkiIndex[idx])
										{
											if (itr->iOuterShihatsuekiIndex != INT_MIN &&
												iSihatsuCoreEkiIndex >= iDisplayJikokuEkiIndex[idx - 1])
											{
												//路線外始発
												strChaku = pCdDedEkiContNobori->get(iSihatsuEkiOrder).getOuterTerminalEkimei(itr->iOuterShihatsuekiIndex);

												strHatsu = getCdDedJikokuConv().encode(itr->OuterShihatsuJikoku, false);
												iHorizontalLineType = 2;
											}
											else if (iPrevContinueEkiIndex != -1)
											{
												/**
													同一行表示の前列車がある場合、
													表示駅が前列車終着駅の場合は、始発駅発時刻を表示する(着時刻およびラインは前列車の管轄)
													前列車終着駅とこの列車の始発駅の間の場合は破線だが、ここでは前列車の管轄となる。
													ただし、この駅が時刻非表示駅なら、時刻・番線は非表示にする
												*/
												if ((iPrevContinueCoreEkiIndex == -1 &&
													iPrevContinueEkiIndex == iDisplayJikokuEkiIndex[idx]) ||
													(iPrevContinueCoreEkiIndex != -1 &&
														iPrevContinueCoreEkiIndex == iDisplayJikokuEkiIndex[idx]))
												{
													if (pCentDedEkiCont->getMuPtr()->get(iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
														(bDisplayTsuukaEkiJikoku ||
															pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya))
													{
														strHatsu = getCdDedJikokuConv().encode(
															pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getVirtualHatsujikoku(), false);
													}
													bSkipLine = true;
													bSkipChaku = true;
													if (pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka &&
														!strHatsu.empty())
													{
														strHatsu += _T("?");
													}
												}
												else if ((iPrevContinueCoreEkiIndex == -1 &&
													iPrevContinueEkiIndex < iDisplayJikokuEkiIndex[idx]) ||
													(iPrevContinueCoreEkiIndex != -1 &&
														iPrevContinueCoreEkiIndex < iDisplayJikokuEkiIndex[idx]))
												{
													//ここでは本来不要だが、CSV出力時はセル数合わせのため、スキップが必須となるので加えておく
													bSkipLine = true;
													bSkipChaku = true;
												}
											}
										}
										else if (iSihatsuCoreEkiIndex == iDisplayJikokuEkiIndex[idx])
										{
											if (itr->iOuterShihatsuekiIndex != INT_MIN)
											{
												if (pCentDedEkiCont->getMuPtr()->get(iSihatsuCoreEkiIndex)->getOperationTableDisplayJikoku())
												{
													//路線外始発のデータ上始発駅
													CdDedJikoku ChakuJikoku = itr->ChakuJikoku;
													CdDedJikoku HatsuJikoku = pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getHatsujikoku();
													if (!ChakuJikoku.isNull())
													{
														HatsuJikoku = pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getVirtualHatsujikoku();
													}

													strChaku = getCdDedJikokuConv().encode(ChakuJikoku, true, HatsuJikoku);
													strHatsu = getCdDedJikokuConv().encode(HatsuJikoku, false, ChakuJikoku);

													if (bDisplayTrackName)
													{
														//if (!strChaku.empty())
														//{
														//	strChaku += _T(" ");
														//}
														strChaku += _T("(");
														strChaku += pCdDedEkiContNobori->get(iSihatsuEkiOrder).getCentDedEkiTrack2Cont().get(
															pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(pCentDedRessya->getRessyahoukou());
														strChaku += _T(")");
													}
												}
												iHorizontalLineType = 0;
											}
											else
											{
												//始発駅
												//前列車と同一行に表示する場合、この駅が時刻非表示駅または駅扱い通過かつ通過駅時刻非表示の場合は、時刻を表示しません
												if (iPrevContinueEkiIndex == -1 ||
													(pCentDedEkiCont->getMuPtr()->get(iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
														(bDisplayTsuukaEkiJikoku ||
															pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya)))
												{
													strHatsu = getCdDedJikokuConv().encode(
														pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getVirtualHatsujikoku(), false);
												}
												iHorizontalLineType = 2;
												//前列車と同一行に表示する場合、この駅の着時刻および横線は、前列車の管轄で描写します
												if (iPrevContinueEkiIndex != -1)
												{
													bSkipChaku = true;
													bSkipLine = true;
													if (pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka &&
														!strHatsu.empty())
													{
														strHatsu += _T("?");
													}
												}

												if (itr->eBeforeType == EBeforeAfterType::BeforeAfterType_OutIn)
												{
													iVerticalLineType = -2;
												}
												else if (iPrevShuchakuEkiIndex != -1 &&
													iPrevShuchakuEkiIndex == iSihatsuCoreEkiIndex)
												{
													iVerticalLineType = -1;
												}

												if (bDisplayTrackName &&
													iPrevContinueEkiIndex == -1)
												{
													if (iVerticalLineType == 0)
													{
														strChaku += _T("(");
														strChaku += pCdDedEkiContNobori->get(iSihatsuEkiOrder).getCentDedEkiTrack2Cont().get(
															pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(pCentDedRessya->getRessyahoukou());
														strChaku += _T(")");
													}
													else
													{
														//strHatsu += _T(" ");

														strHatsu += _T("(");
														strHatsu += pCdDedEkiContNobori->get(iSihatsuEkiOrder).getCentDedEkiTrack2Cont().get(
															pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(pCentDedRessya->getRessyahoukou());
														strHatsu += _T(")");
													}
												}
											}
										}
										else//sihatsu<iDisplayJikokuEkiIndex[idx]<syuchaku
										{
											//経由無し
											iHorizontalLineType = 3;
										}
									}
									if (itr->iOuterShihatsuekiIndex != INT_MIN &&
										iSihatsuEkiIndex >= iDisplayJikokuEkiIndex[idx - 1])
									{
										//路線外始発
										strChaku = pCdDedEkiContNobori->get(iSihatsuEkiOrder).getOuterTerminalEkimei(itr->iOuterShihatsuekiIndex);

										strHatsu = getCdDedJikokuConv().encode(itr->OuterShihatsuJikoku, false);
										iHorizontalLineType = 2;
									}
									else if (iPrevContinueEkiIndex != -1)
									{
										/**
											同一行表示の前列車がある場合、
											表示駅が前列車終着駅の場合は、始発駅発時刻を表示する(着時刻およびラインは前列車の管轄)
											前列車終着駅とこの列車の始発駅の間の場合は破線だが、ここでは前列車の管轄となる。
											ただし、この駅が時刻非表示駅なら、時刻・番線は非表示にする
										*/
										if ((iPrevContinueCoreEkiIndex == -1 &&
											iPrevContinueEkiIndex == iDisplayJikokuEkiIndex[idx]) ||
											(iPrevContinueCoreEkiIndex != -1 &&
												iPrevContinueCoreEkiIndex == iDisplayJikokuEkiIndex[idx]))
										{
											if (pCentDedEkiCont->getMuPtr()->get(iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
												(bDisplayTsuukaEkiJikoku ||
													pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya))
											{
												strHatsu = getCdDedJikokuConv().encode(
													pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getVirtualHatsujikoku(), false);
											}
											bSkipLine = true;
											bSkipChaku = true;
											if (pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka &&
												!strHatsu.empty())
											{
												strHatsu += _T("?");
											}
										}
										else if ((iPrevContinueCoreEkiIndex == -1 &&
											iPrevContinueEkiIndex < iDisplayJikokuEkiIndex[idx]) ||
											(iPrevContinueCoreEkiIndex != -1 &&
												iPrevContinueCoreEkiIndex < iDisplayJikokuEkiIndex[idx]))
										{
											//ここでは本来不要だが、CSV出力時はセル数合わせのため、スキップが必須となるので加えておく
											bSkipLine = true;
											bSkipChaku = true;
										}
									}

								}
								/**
									表示駅が始発駅の場合、路線外始発なら、この駅の時刻表示は駅設定に依存します
									出区・前列車接続の場合は、発時刻を表示します。
								*/
								else if (iSihatsuEkiIndex == iDisplayJikokuEkiIndex[idx])
								{
									if (itr->iOuterShihatsuekiIndex != INT_MIN)
									{
										if (pCentDedEkiCont->getMuPtr()->get(iSihatsuEkiIndex)->getOperationTableDisplayJikoku())
										{
											//路線外始発のデータ上始発駅
											CdDedJikoku ChakuJikoku = itr->ChakuJikoku;
											CdDedJikoku HatsuJikoku = pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getHatsujikoku();
											if (!ChakuJikoku.isNull())
											{
												HatsuJikoku = pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getVirtualHatsujikoku();
											}

											strChaku = getCdDedJikokuConv().encode(ChakuJikoku, true, HatsuJikoku);
											strHatsu = getCdDedJikokuConv().encode(HatsuJikoku, false, ChakuJikoku);

											if (bDisplayTrackName)
											{
												//if (!strChaku.empty())
												//{
												//	strChaku += _T(" ");
												//}
												strChaku += _T("(");
												strChaku += pCdDedEkiContNobori->get(iSihatsuEkiOrder).getCentDedEkiTrack2Cont().get(
													pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(pCentDedRessya->getRessyahoukou());
												strChaku += _T(")");
											}
										}
										iHorizontalLineType = 0;
									}
									else
									{
										//始発駅
										//前列車と同一行に表示する場合、この駅が時刻非表示駅または駅扱い通過かつ通過駅時刻非表示の場合は、時刻を表示しません
										if (iPrevContinueEkiIndex == -1 ||
											(pCentDedEkiCont->getMuPtr()->get(iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
												(bDisplayTsuukaEkiJikoku ||
													pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya)))
										{
											strHatsu = getCdDedJikokuConv().encode(
												pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getVirtualHatsujikoku(), false);
										}
										iHorizontalLineType = 2;
										//前列車と同一行に表示する場合、この駅の着時刻および横線は、前列車の管轄で描写します
										if (iPrevContinueEkiIndex != -1)
										{
											bSkipChaku = true;
											bSkipLine = true;
											if (pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka &&
												!strHatsu.empty())
											{
												strHatsu += _T("?");
											}
										}

										if (itr->eBeforeType == EBeforeAfterType::BeforeAfterType_OutIn)
										{
											iVerticalLineType = -2;
										}
										else if (iPrevShuchakuEkiIndex != -1 &&
											iPrevShuchakuEkiIndex == iSihatsuEkiIndex)
										{
											iVerticalLineType = -1;
										}

										if (bDisplayTrackName &&
											iPrevContinueEkiIndex == -1)
										{
											if (iVerticalLineType == 0)
											{
												strChaku += _T("(");
												strChaku += pCdDedEkiContNobori->get(iSihatsuEkiOrder).getCentDedEkiTrack2Cont().get(
													pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(pCentDedRessya->getRessyahoukou());
												strChaku += _T(")");
											}
											else
											{
												//strHatsu += _T(" ");

												strHatsu += _T("(");
												strHatsu += pCdDedEkiContNobori->get(iSihatsuEkiOrder).getCentDedEkiTrack2Cont().get(
													pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(pCentDedRessya->getRessyahoukou());
												strHatsu += _T(")");
											}
										}
									}
								}
								/**
									表示駅が終着駅の場合、路線外終着なら、この駅の時刻表示は駅設定に依存します
									入区・次列車接続の場合は、着時刻を表示します。
								*/
								else if (iSyuuchakuEkiIndex == iDisplayJikokuEkiIndex[idx])
								{
									if (itr->iOuterShuchakuekiIndex != INT_MIN)
									{
										if (pCentDedEkiCont->getMuPtr()->get(iSyuuchakuEkiIndex)->getOperationTableDisplayJikoku())
										{
											//路線外終着のデータ上終着駅
											CdDedJikoku ChakuJikoku = pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getChakujikoku();
											CdDedJikoku HatsuJikoku = itr->HatsuJikoku;
											if (!HatsuJikoku.isNull())
											{
												ChakuJikoku = pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getVirtualChakujikoku();
											}

											strChaku = getCdDedJikokuConv().encode(ChakuJikoku, true, HatsuJikoku);
											strHatsu = getCdDedJikokuConv().encode(HatsuJikoku, false, ChakuJikoku);

											if (bDisplayTrackName)
											{
												if (strHatsu.empty())
												{
													strHatsu += _T("(");
													strHatsu += pCdDedEkiContNobori->get(iSyuuchakuEkiOrder).getCentDedEkiTrack2Cont().get(
														pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(pCentDedRessya->getRessyahoukou());
													strHatsu += _T(")");
												}
												else
												{
													//strChaku += _T(" ");

													strChaku += _T("(");
													strChaku += pCdDedEkiContNobori->get(iSyuuchakuEkiOrder).getCentDedEkiTrack2Cont().get(
														pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(pCentDedRessya->getRessyahoukou());
													strChaku += _T(")");
												}
											}
										}
										iHorizontalLineType = 0;
									}
									else
									{
										//終着駅
										//次列車と同一行に表示する場合、この駅が時刻非表示駅または駅扱い通過かつ通過駅時刻非表示の場合は、時刻を表示しません
										if (iNextContinueEkiIndex == -1 ||
											(pCentDedEkiCont->getMuPtr()->get(iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
												(bDisplayTsuukaEkiJikoku ||
													pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya)))
										{
											strChaku = getCdDedJikokuConv().encode(
												pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getVirtualChakujikoku(), true);
										}
										iHorizontalLineType = 1;
										//次列車と同一行に表示する場合、この駅の発時刻は、次列車の管轄で描写します。横線は全域になります。
										if (iNextContinueEkiIndex != -1)
										{
											iHorizontalLineType = 0;
											bSkipHatsu = true;
											if (pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka &&
												!strChaku.empty())
											{
												strChaku += _T("?");
											}
										}
										if (itr->eAfterType == EBeforeAfterType::BeforeAfterType_OutIn)
										{
											iVerticalLineType = 2;
										}
										else if (iNextShihatsuEkiIndex != -1 &&
											iNextShihatsuEkiIndex == iSyuuchakuEkiIndex)
										{
											iVerticalLineType = 1;
										}

										if (bDisplayTrackName)
										{
											if (iVerticalLineType == 0 &&
												iNextContinueEkiIndex == -1)
											{
												strHatsu += _T("(");
												strHatsu += pCdDedEkiContNobori->get(iSyuuchakuEkiOrder).getCentDedEkiTrack2Cont().get(
													pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(pCentDedRessya->getRessyahoukou());
												strHatsu += _T(")");
											}
											else
											{
												//strChaku += _T(" ");

												strChaku += _T("(");
												strChaku += pCdDedEkiContNobori->get(iSyuuchakuEkiOrder).getCentDedEkiTrack2Cont().get(
													pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getRessyaTrackIndex()).getTrackRyakusyou(pCentDedRessya->getRessyahoukou());
												strChaku += _T(")");
											}
										}
									}
								}
								/**
									表示駅が始発駅から終着駅の間の場合、その駅が時刻表示駅なのかで、時刻を表示するかどうかが変わります

								*/
								else//sihatsu<iDisplayJikokuEkiIndex[idx]<syuchaku
								{
									int iEkiOrder = pCentDedRessya->EkiOrderOfEkiIndex(iDisplayJikokuEkiIndex[idx]);
									int iRessyaTrackIndex = -1;
									CentDedEkiJikoku aEkiJikoku = pCentDedRessya->getCentDedEkiJikoku(iEkiOrder);

									//着時刻側
									bool bChakuIsNone = true;
									CdDedJikoku ChakuJikoku;
									if (pCentDedRessya->isRunBetweenNextEki(iEkiOrder - 1))
									{
										bChakuIsNone = false;
										if (pCentDedEkiCont->getMuPtr()->get(iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
											(bDisplayTsuukaEkiJikoku ||
												aEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya))
										{
											ChakuJikoku = aEkiJikoku.getVirtualChakujikoku();
											if (!ChakuJikoku.isNull() &&
												aEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
											{
												strChaku = _T("?");
											}
										}
										iRessyaTrackIndex = aEkiJikoku.getRessyaTrackIndex();
									}
									else
									{
										int iPrevEkiOrder = pCentDedRessya->getRunBetweenEkiBackward(iEkiOrder);

										if (iPrevEkiOrder != -1)
										{
											if (pCentDedEkiCont->isSameBrunchLoopGroup(iPrevEkiOrder, iEkiOrder, pCentDedRessya->getRessyahoukou()))
											{
												bChakuIsNone = false;
												CentDedEkiJikoku aPrevEkiJikoku = pCentDedRessya->getCentDedEkiJikoku(iPrevEkiOrder);
												if (pCentDedEkiCont->getMuPtr()->get(iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
													(bDisplayTsuukaEkiJikoku ||
														aPrevEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya))
												{
													ChakuJikoku = aPrevEkiJikoku.getVirtualChakujikoku();//後で、入換時刻設定を確認＆通過駅時刻表示を追加
													if (!ChakuJikoku.isNull() &&
														aPrevEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
													{
														strChaku = _T("?");
													}
												}
												iRessyaTrackIndex = aPrevEkiJikoku.getRessyaTrackIndex();
											}
										}
									}

									bool bHatsuIsNone = true;
									CdDedJikoku HatsuJikoku;
									if (pCentDedRessya->isRunBetweenNextEki(iEkiOrder))
									{
										bHatsuIsNone = false;
										if (pCentDedEkiCont->getMuPtr()->get(iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
											(bDisplayTsuukaEkiJikoku ||
												aEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya))
										{
											HatsuJikoku = aEkiJikoku.getVirtualHatsujikoku();
											if (!HatsuJikoku.isNull() &&
												aEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
											{
												strHatsu = _T("?");
											}
										}
										iRessyaTrackIndex = aEkiJikoku.getRessyaTrackIndex();
									}
									else
									{
										int iNextEkiOrder = pCentDedRessya->getRunBetweenEkiForward(iEkiOrder);
										if (iNextEkiOrder != -1)
										{
											if (pCentDedEkiCont->isSameBrunchLoopGroup(iNextEkiOrder, iEkiOrder, pCentDedRessya->getRessyahoukou()))
											{
												bHatsuIsNone = false;
												CentDedEkiJikoku aNextEkiJikoku = pCentDedRessya->getCentDedEkiJikoku(iNextEkiOrder);
												if (pCentDedEkiCont->getMuPtr()->get(iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku() &&
													(bDisplayTsuukaEkiJikoku ||
														aNextEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya))
												{
													HatsuJikoku = aNextEkiJikoku.getVirtualHatsujikoku();
													if (!HatsuJikoku.isNull() &&
														aNextEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Tsuuka)
													{
														strHatsu = _T("?");
													}
												}
												iRessyaTrackIndex = aNextEkiJikoku.getRessyaTrackIndex();
											}
										}
									}
									if (bChakuIsNone && bHatsuIsNone)
									{
										iHorizontalLineType = 3;
									}
									else
									{
										iHorizontalLineType = 0;
									}

									strChaku = getCdDedJikokuConv().encode(ChakuJikoku, true, HatsuJikoku) + strChaku;
									strHatsu = getCdDedJikokuConv().encode(HatsuJikoku, false, ChakuJikoku) + strHatsu;

									if (bDisplayTrackName &&
										iRessyaTrackIndex != -1 &&
										pCentDedEkiCont->getMuPtr()->get(iDisplayJikokuEkiIndex[idx])->getOperationTableDisplayJikoku())
									{
										if (!strChaku.empty() && strHatsu.empty())
										{
											strHatsu += _T("(");
											strHatsu += pCdDedEkiContNobori->get(iEkiOrder).getCentDedEkiTrack2Cont().
												get(iRessyaTrackIndex).getTrackRyakusyou(pCentDedRessya->getRessyahoukou());
											strHatsu += _T(")");
										}
										else
										{
											//if (!strChaku.empty())
											//{
											//	strChaku += _T(" ");
											//}
											strChaku += _T("(");
											strChaku += pCdDedEkiContNobori->get(iEkiOrder).getCentDedEkiTrack2Cont().
												get(iRessyaTrackIndex).getTrackRyakusyou(pCentDedRessya->getRessyahoukou());
											strChaku += _T(")");
										}
									}
								}
							}
						}

						tstring strLine;

						if (iHorizontalLineType == 0)
						{
							strLine = _T("━━━━━");

						}
						if (iHorizontalLineType == 1)
						{
							strLine = _T("　　　━━");
						}
						if (iHorizontalLineType == 2)
						{
							strLine = _T("━━　　　");
						}
						if (iHorizontalLineType == 3)
						{
							strLine = _T("・・・・・");
						}

						if (iVerticalLineType == -1)
						{
							strChaku= _T("　　┃　　");
						}
						else if (iVerticalLineType == 1)
						{
							strHatsu = _T("　　┃　　");
						}
						else if (iVerticalLineType == -2)
						{
							strChaku = _T("　　○　　");
						}
						else if (iVerticalLineType == 2)
						{
							strHatsu = _T("　　△　　");
						}

						//bSkipChakuが有効になるのは、前列車と同一行に表示する場合の、始発駅です(前列車の着時刻を上書きしないように)
						if (!bSkipChaku)
						{
							strRowTemp.push_back(strChaku);
							//aRow.getCellCont()->insert(CdCsvCell(strChaku));
						}
						if (!bSkipLine)
						{
							strRowTemp2.push_back(strLine);
							//aRow2.getCellCont()->insert(CdCsvCell(strLine));
						}
						if (!bSkipHatsu)
						{
							strRowTemp3.push_back(strHatsu);
							//aRow3.getCellCont()->insert(CdCsvCell(strHatsu));
						}


					}
					if (itr->aRessyaProperty.getRessyahoukou() == ERessyahoukou::Ressyahoukou_Kudari)
					{
						strRow.insert(strRow.end(), strRowTemp.begin(), strRowTemp.end());
						strRow2.insert(strRow2.end(), strRowTemp2.begin(), strRowTemp2.end());
						strRow3.insert(strRow3.end(), strRowTemp3.begin(), strRowTemp3.end());
					}
					else
					{
						strRow.insert(strRow.begin(), strRowTemp.begin(), strRowTemp.end());
						strRow2.insert(strRow2.begin(), strRowTemp2.begin(), strRowTemp2.end());
						strRow3.insert(strRow3.begin(), strRowTemp3.begin(), strRowTemp3.end());

					}
				}
				for (int idx = 0; idx < (int)strRow.size(); idx++)
				{
					aRow.getCellCont()->insert(CdCsvCell(strRow[idx]));
				}
				for (int idx = 0; idx < (int)strRow2.size(); idx++)
				{
					aRow2.getCellCont()->insert(CdCsvCell(strRow2[idx]));
				}
				for (int idx = 0; idx < (int)strRow3.size(); idx++)
				{
					aRow3.getCellCont()->insert(CdCsvCell(strRow3[idx]));
				}
			}
			else
			{
				const CentDedRessya* pShihatsuRessya =
					pCentDedRessyaConts[itr->aRessyaProperty.getRessyahoukou()]
					->get(itr->aRessyaProperty.getRessyaIndex());

				auto itrShihatsu = itr;
				auto itrShuchaku = itr;

				/**
					itrをiCombineCount回インクリメントします。その際、itrShuchakuをitrで書き換えることで、
					forが終わったとき、itrShuchakuは末尾(終着)の列車になり、itrはm_contOperationTable[iOTIndex+1]の先頭列車(もしくはend())になります。
				*/
				for (int iCbIndex = 0; iCbIndex < contOperationTable[iOTIndex].iCombineCount; iCbIndex++, itr++)
				{
					itrShuchaku = itr;
				}
				const CentDedRessya* pShuchakuRessya =
					pCentDedRessyaConts[itrShuchaku->aRessyaProperty.getRessyahoukou()]
					->get(itrShuchaku->aRessyaProperty.getRessyaIndex());

				//int iSihatsuEkiOrder = itrShihatsu->iSihatsuEkiOrder;
				//if (!pShihatsuRessya->isRunBetweenNextEki(iSihatsuEkiOrder))
				//{
				//	iSihatsuEkiOrder = pShihatsuRessya->getRunBetweenEkiForward(iSihatsuEkiOrder);
				//}
				//int iSihatsuEkiIndex = pShihatsuRessya->EkiIndexOfEkiOrder(iSihatsuEkiOrder);




				//int iSyuuchakuEkiOrder = itrShuchaku->iSyuuchakuEkiOrder;
				//if (!pShuchakuRessya->isRunBetweenNextEki(iSyuuchakuEkiOrder - 1))
				//{
				//	iSyuuchakuEkiOrder = pShuchakuRessya->getRunBetweenEkiBackward(iSyuuchakuEkiOrder);
				//}
				//int iSyuuchakuEkiIndex = pShuchakuRessya->EkiIndexOfEkiOrder(iSyuuchakuEkiOrder);

				aRow.getCellCont()->insert(CdCsvCell(pShihatsuRessya->getRessyabangou()));
				aRow2.getCellCont()->insert(CdCsvCell());
				aRow3.getCellCont()->insert(CdCsvCell());

				int iRessyaSyubetsuIndex = pShihatsuRessya->getRessyasyubetsuIndex();
				if (pCentDedRessyasyubetsuContGet->get(iRessyaSyubetsuIndex)->getParentSyubetsuIndex() >= 0 &&
					bDisplayParentSyubetsu)
				{
					iRessyaSyubetsuIndex = pCentDedRessyasyubetsuContGet->get(iRessyaSyubetsuIndex)->getParentSyubetsuIndex();
				}
				aRow.getCellCont()->insert(CdCsvCell(
					pCentDedRessyasyubetsuContGet->get(iRessyaSyubetsuIndex)->getSyubetsumei()));
				aRow2.getCellCont()->insert(CdCsvCell());
				aRow3.getCellCont()->insert(CdCsvCell());

				if (bDisplayRessyamei)
				{
					aRow.getCellCont()->insert(CdCsvCell(pShihatsuRessya->getRessyamei()));
					aRow2.getCellCont()->insert(CdCsvCell());
					aRow3.getCellCont()->insert(CdCsvCell());

					aRow.getCellCont()->insert(CdCsvCell(pShihatsuRessya->getGousuu()));
					aRow2.getCellCont()->insert(CdCsvCell());
					aRow3.getCellCont()->insert(CdCsvCell());

					if (pShihatsuRessya->getGousuu().empty())
					{
						aRow.getCellCont()->insert(CdCsvCell());
						aRow2.getCellCont()->insert(CdCsvCell());
						aRow3.getCellCont()->insert(CdCsvCell());
					}
					else
					{
						aRow.getCellCont()->insert(CdCsvCell(m_nameGou));
						aRow2.getCellCont()->insert(CdCsvCell());
						aRow3.getCellCont()->insert(CdCsvCell());
					}
				}

				if (contOperationTable[iOTIndex].eRessyahoukou == ERessyahoukou::Ressyahoukou_Kudari)
				{
					tstring strOrgEkimei;
					tstring strOrgEkijikoku;

					if (itrShihatsu->iOuterShihatsuekiIndex != INT_MIN)
					{
						strOrgEkimei = pCdDedEkiContKudari->get(itrShihatsu->iSihatsuEkiOrder).getOuterTerminalEkimei(
							itrShihatsu->iOuterShihatsuekiIndex);
						strOrgEkijikoku = getCdDedJikokuConv().encode(itrShihatsu->OuterShihatsuJikoku, false);
					}
					else
					{
						int iSihatsuEkiOrder = itrShihatsu->iSihatsuEkiOrder;
						if (!pShihatsuRessya->isRunBetweenNextEki(iSihatsuEkiOrder))
						{
							iSihatsuEkiOrder = pShihatsuRessya->getRunBetweenEkiForward(iSihatsuEkiOrder);
						}
						strOrgEkimei = pCdDedEkiContKudari->get(iSihatsuEkiOrder).getEkimei();
						strOrgEkijikoku = getCdDedJikokuConv().encode(
							pShihatsuRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getHatsujikoku(), false);
						
					}
					aRow.getCellCont()->insert(CdCsvCell(strOrgEkimei));
					aRow.getCellCont()->insert(CdCsvCell(strOrgEkijikoku));

					aRow.getCellCont()->insert(CdCsvCell(m_nameKudariArrow));

					tstring strDstEkimei;
					tstring strDstEkijikoku;
					if (itrShuchaku->iOuterShuchakuekiIndex != INT_MIN)
					{
						strDstEkimei = pCdDedEkiContKudari->get(itrShuchaku->iSyuuchakuEkiOrder).getOuterTerminalEkimei(
							itrShuchaku->iOuterShuchakuekiIndex);
						strDstEkijikoku = getCdDedJikokuConv().encode(itrShuchaku->OuterShuchakuJikoku, true);
						
					}
					else
					{
						int iSyuuchakuEkiOrder = itrShuchaku->iSyuuchakuEkiOrder;
						if (!pShuchakuRessya->isRunBetweenNextEki(iSyuuchakuEkiOrder - 1))
						{
							iSyuuchakuEkiOrder = pShuchakuRessya->getRunBetweenEkiBackward(iSyuuchakuEkiOrder);
						}
						strDstEkimei = pCdDedEkiContKudari->get(iSyuuchakuEkiOrder).getEkimei();
						strDstEkijikoku = getCdDedJikokuConv().encode(
							pShuchakuRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getChakujikoku(), true);
						
					}
					aRow.getCellCont()->insert(CdCsvCell(strDstEkimei));
					aRow.getCellCont()->insert(CdCsvCell(strDstEkijikoku));
				}
				else if (bDisplayNoboriLeftToRight)
				{
					tstring strOrgEkimei;
					tstring strOrgEkijikoku;
					if (itrShihatsu->iOuterShihatsuekiIndex != INT_MIN)
					{
						strOrgEkimei = pCdDedEkiContNobori->get(itrShihatsu->iSihatsuEkiOrder).getOuterTerminalEkimei(
							itrShihatsu->iOuterShihatsuekiIndex);
						strOrgEkijikoku = getCdDedJikokuConv().encode(itrShihatsu->OuterShihatsuJikoku, false);
						
					}
					else
					{
						int iSihatsuEkiOrder = itrShihatsu->iSihatsuEkiOrder;
						if (!pShihatsuRessya->isRunBetweenNextEki(iSihatsuEkiOrder))
						{
							iSihatsuEkiOrder = pShihatsuRessya->getRunBetweenEkiForward(iSihatsuEkiOrder);
						}
						strOrgEkimei = pCdDedEkiContNobori->get(iSihatsuEkiOrder).getEkimei();
						strOrgEkijikoku = getCdDedJikokuConv().encode(
							pShihatsuRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getHatsujikoku(), false);
						
					}
					aRow.getCellCont()->insert(CdCsvCell(strOrgEkimei));
					aRow.getCellCont()->insert(CdCsvCell(strOrgEkijikoku));

					aRow.getCellCont()->insert(CdCsvCell(m_nameKudariArrow));

					tstring strDstEkimei;
					tstring strDstEkijikoku;
					if (itrShuchaku->iOuterShuchakuekiIndex != INT_MIN)
					{
						strDstEkimei = pCdDedEkiContNobori->get(itrShuchaku->iSyuuchakuEkiOrder).getOuterTerminalEkimei(
							itrShuchaku->iOuterShuchakuekiIndex);
						strDstEkijikoku = getCdDedJikokuConv().encode(itrShuchaku->OuterShuchakuJikoku, true);
						
					}
					else
					{
						int iSyuuchakuEkiOrder = itrShuchaku->iSyuuchakuEkiOrder;
						if (!pShuchakuRessya->isRunBetweenNextEki(iSyuuchakuEkiOrder - 1))
						{
							iSyuuchakuEkiOrder = pShuchakuRessya->getRunBetweenEkiBackward(iSyuuchakuEkiOrder);
						}
						strDstEkimei = pCdDedEkiContNobori->get(iSyuuchakuEkiOrder).getEkimei();
						strDstEkijikoku = getCdDedJikokuConv().encode(
							pShuchakuRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getChakujikoku(), true);
						
					}
					aRow.getCellCont()->insert(CdCsvCell(strDstEkimei));
					aRow.getCellCont()->insert(CdCsvCell(strDstEkijikoku));
				}
				else
				{
					tstring strOrgEkimei;
					tstring strOrgEkijikoku;
					if (itrShuchaku->iOuterShuchakuekiIndex != INT_MIN)
					{
						strOrgEkimei = pCdDedEkiContNobori->get(itrShuchaku->iSyuuchakuEkiOrder).getOuterTerminalEkimei(
							itrShuchaku->iOuterShuchakuekiIndex);
						strOrgEkijikoku = getCdDedJikokuConv().encode(itrShuchaku->OuterShuchakuJikoku, true);
						
					}
					else
					{
						int iSyuuchakuEkiOrder = itrShuchaku->iSyuuchakuEkiOrder;
						if (!pShuchakuRessya->isRunBetweenNextEki(iSyuuchakuEkiOrder - 1))
						{
							iSyuuchakuEkiOrder = pShuchakuRessya->getRunBetweenEkiBackward(iSyuuchakuEkiOrder);
						}
						strOrgEkimei = pCdDedEkiContNobori->get(iSyuuchakuEkiOrder).getEkimei();
						strOrgEkijikoku = getCdDedJikokuConv().encode(
							pShuchakuRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getChakujikoku(), true);
						
					}
					aRow.getCellCont()->insert(CdCsvCell(strOrgEkimei));
					aRow.getCellCont()->insert(CdCsvCell(strOrgEkijikoku));

					aRow.getCellCont()->insert(CdCsvCell(m_nameNoboriArrow));

					tstring strDstEkimei;
					tstring strDstEkijikoku;
					if (itrShihatsu->iOuterShihatsuekiIndex != INT_MIN)
					{
						strDstEkimei = pCdDedEkiContNobori->get(itrShihatsu->iSihatsuEkiOrder).getOuterTerminalEkimei(
							itrShihatsu->iOuterShihatsuekiIndex);
						strDstEkijikoku = getCdDedJikokuConv().encode(itrShihatsu->OuterShihatsuJikoku, false);
						
					}
					else
					{
						int iSihatsuEkiOrder = itrShihatsu->iSihatsuEkiOrder;
						if (!pShihatsuRessya->isRunBetweenNextEki(iSihatsuEkiOrder))
						{
							iSihatsuEkiOrder = pShihatsuRessya->getRunBetweenEkiForward(iSihatsuEkiOrder);
						}
						strDstEkimei = pCdDedEkiContNobori->get(iSihatsuEkiOrder).getEkimei();
						strDstEkijikoku = getCdDedJikokuConv().encode(
							pShihatsuRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getHatsujikoku(), false);
						
					}
					aRow.getCellCont()->insert(CdCsvCell(strDstEkimei));
					aRow.getCellCont()->insert(CdCsvCell(strDstEkijikoku));
				}
			}
			pCdCsvDocument->getRowCont()->insert(aRow);
			if (bDisplayExtensionOperationTable)
			{
				pCdCsvDocument->getRowCont()->insert(aRow2);
				pCdCsvDocument->getRowCont()->insert(aRow3);
			}
		}
	}
	return iRv ;
}

} //namespace ViewOperationTable

