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
// $Id: CconvAllOperationTableCsv.cpp
// ****************************************************************
#include "stdafx.h"
#include "CconvAllOperationTableCsv.h"
#include "str\strprintf.h"
//#include "OperationTableColSpec\CdOperationTableYColSpecCont.h"
//#include "..\entDed\CdDedJikoku.h"
//#include "..\entDed\CdDedRessyaProperty.h"
#include "../DiagramEdit.h"

namespace ViewAllOperationTable {

using namespace std ;
using namespace OuLib ;
using namespace OuLib::Str ;

/**
	FileTypeの 名前
*/
const TCHAR* const nameFileType = _T("FileType") ;

/**
	FileType の値
*/
const TCHAR* const nameFileTypeValue = _T("OuDiaSecond.AllOperationTableCsv.1") ;

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

	// --------------------------------
	//@name	駅時刻セルの文字列の解釈
	// --------------------------------
tstring CconvAllOperationTableCsv::encode_Ekijikoku(
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
CconvAllOperationTableCsv::CconvAllOperationTableCsv()
{
}


	// ********************************
	//@name	CconvJikokuhyouCsv
	// ********************************
int CconvAllOperationTableCsv::encode(
		const CentDedRosen& aCentDedRosen ,
		const CentDedDia& aCentDedDia,
		const vector<tstring>& strOperationNumberCont,
		const bool bDisplaySecondEkiJikoku,
		const bool bDisplayColonEkiJikoku,
		const bool bDisplayParentSyubetsu,
		const bool bDisplayAllRessya,
		const int iMaxRessyaCount,
		CdCsvDocument* pCdCsvDocument ) 
{
	int iRv = 0 ;
	
	const Mu<CentDedEkiCont::CdDedEki>* pCdDedEkiCont[2];
	const Mu<const CentDedRessyasyubetsu*>* pCentDedRessyasyubetsuContGet = NULL ;
	const Mu<const CentDedRessya*>* pCentDedRessyaConts[2] ;

	if (!aCentDedRosen.getKudariDiaAlias().empty())
	{
		m_nameKudari = aCentDedRosen.getKudariDiaAlias();
	}
	if (!aCentDedRosen.getNoboriDiaAlias().empty())
	{
		m_nameNobori = aCentDedRosen.getNoboriDiaAlias();
	}



	// --------------------------------
	//	オブジェクトCdCsvDocument をクリア
	// --------------------------------
	if ( iRv >= 0 )
	{
		for (int iRessyahoukou = Ressyahoukou_Kudari;
			iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
		{
			pCdDedEkiCont[iRessyahoukou] = aCentDedRosen.getCentDedEkiCont()
				->getMuPtr((ERessyahoukou)iRessyahoukou);
			pCentDedRessyaConts[iRessyahoukou] = aCentDedDia.getCentDedRessyaCont((ERessyahoukou)iRessyahoukou)->getMuPtr();
		}
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
	if ( iRv >= 0 )
	{
		CdCsvRow	aRow ;
		aRow.getCellCont()->insert( CdCsvCell( nameFileType ) ) ;
		aRow.getCellCont()->insert( CdCsvCell( nameFileTypeValue ) ) ;
		pCdCsvDocument->getRowCont()->insert( aRow ) ;
	}	
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

	//空行
	pCdCsvDocument->getRowCont()->insert(CdCsvRow());

	//項目名行
	CdCsvRow	aRowHeader;
	aRowHeader.getCellCont()->insert(CdCsvCell());//列番号
	aRowHeader.getCellCont()->insert(CdCsvCell(m_nameOperationNumber));
	aRowHeader.getCellCont()->insert(CdCsvCell(m_nameOutEkimei));
	aRowHeader.getCellCont()->insert(CdCsvCell(m_nameHatsuJikoku));
	aRowHeader.getCellCont()->insert(CdCsvCell());//矢印
	aRowHeader.getCellCont()->insert(CdCsvCell(m_nameInEkimei));
	aRowHeader.getCellCont()->insert(CdCsvCell(m_nameChakuJikoku));
	if (bDisplayAllRessya)
	{
		for (int idx = 0; idx < iMaxRessyaCount; idx++)
		{
			aRowHeader.getCellCont()->insert(CdCsvCell(to_tstring(idx + 1)));
			aRowHeader.getCellCont()->insert(CdCsvCell(m_nameRessyabangou));
			aRowHeader.getCellCont()->insert(CdCsvCell(m_nameRessyasyubetsu));
			if (bDisplayRessyamei)
			{
				aRowHeader.getCellCont()->insert(CdCsvCell(m_nameRessyamei));
				aRowHeader.getCellCont()->insert(CdCsvCell(m_nameGousuu));
				aRowHeader.getCellCont()->insert(CdCsvCell());
			}
			if (idx < iMaxRessyaCount - 1)
			{
				aRowHeader.getCellCont()->insert(CdCsvCell());//矢印
			}
		}
	}
	else
	{
		aRowHeader.getCellCont()->insert(CdCsvCell(m_nameOutRessya));
		aRowHeader.getCellCont()->insert(CdCsvCell(m_nameRessyabangou));
		aRowHeader.getCellCont()->insert(CdCsvCell(m_nameRessyasyubetsu));
		if (bDisplayRessyamei)
		{
			aRowHeader.getCellCont()->insert(CdCsvCell(m_nameRessyamei));
			aRowHeader.getCellCont()->insert(CdCsvCell(m_nameGousuu));
			aRowHeader.getCellCont()->insert(CdCsvCell());
		}

		aRowHeader.getCellCont()->insert(CdCsvCell());//矢印

		aRowHeader.getCellCont()->insert(CdCsvCell(m_nameInRessya));
		aRowHeader.getCellCont()->insert(CdCsvCell(m_nameRessyabangou));
		aRowHeader.getCellCont()->insert(CdCsvCell(m_nameRessyasyubetsu));
		if (bDisplayRessyamei)
		{
			aRowHeader.getCellCont()->insert(CdCsvCell(m_nameRessyamei));
			aRowHeader.getCellCont()->insert(CdCsvCell(m_nameGousuu));
			aRowHeader.getCellCont()->insert(CdCsvCell());
		}
	}
	pCdCsvDocument->getRowCont()->insert(aRowHeader);
	for (int idxOperationNumber = 0; idxOperationNumber < (int)strOperationNumberCont.size(); idxOperationNumber++)
	{
		const list<OperationTableContent>& ListOperationTableContent =
			aCentDedDia.getcontOperationTableContent().at(strOperationNumberCont[idxOperationNumber]);

		const OperationTableContent aOperationTableContentOut = ListOperationTableContent.front();
		const OperationTableContent aOperationTableContentIn = ListOperationTableContent.back();

		const CentDedRessya* pCentDedRessyaOut =
			pCentDedRessyaConts[aOperationTableContentOut.aRessyaProperty.getRessyahoukou()]
			->get(aOperationTableContentOut.aRessyaProperty.getRessyaIndex());
		const CentDedRessya* pCentDedRessyaIn =
			pCentDedRessyaConts[aOperationTableContentIn.aRessyaProperty.getRessyahoukou()]
			->get(aOperationTableContentIn.aRessyaProperty.getRessyaIndex());


		CdCsvRow	aRow;
		aRow.getCellCont()->insert(CdCsvCell(to_tstring(idxOperationNumber + 1)));
		aRow.getCellCont()->insert(CdCsvCell(strOperationNumberCont[idxOperationNumber]));

		tstring strOutEkimei;
		tstring strOutEkijikoku;

		if (aOperationTableContentOut.iOuterShihatsuekiIndex != INT_MIN)
		{
			strOutEkimei = pCdDedEkiCont[aOperationTableContentOut.aRessyaProperty.getRessyahoukou()]->get(aOperationTableContentOut.iSihatsuEkiOrder).getOuterTerminalEkimei(
				aOperationTableContentOut.iOuterShihatsuekiIndex);
			strOutEkijikoku = encode_Ekijikoku(
				aOperationTableContentOut.OuterShihatsuJikoku,
				bDisplaySecondEkiJikoku,
				bDisplayColonEkiJikoku);
		}
		else
		{
			int iSihatsuEkiOrder = aOperationTableContentOut.iSihatsuEkiOrder;
			if (!pCentDedRessyaOut->isRunBetweenNextEki(iSihatsuEkiOrder))
			{
				iSihatsuEkiOrder = pCentDedRessyaOut->getRunBetweenEkiForward(iSihatsuEkiOrder);
			}
			strOutEkimei = pCdDedEkiCont[aOperationTableContentOut.aRessyaProperty.getRessyahoukou()]->get(iSihatsuEkiOrder).getEkimei();
			strOutEkijikoku = encode_Ekijikoku(
				pCentDedRessyaOut->getCentDedEkiJikoku(iSihatsuEkiOrder).getHatsujikoku(),
				bDisplaySecondEkiJikoku,
				bDisplayColonEkiJikoku);
		}
		aRow.getCellCont()->insert(CdCsvCell(strOutEkimei));
		aRow.getCellCont()->insert(CdCsvCell(strOutEkijikoku));

		aRow.getCellCont()->insert(CdCsvCell(m_nameArrow));

		tstring strInEkimei;
		tstring strInEkijikoku;
		if (aOperationTableContentIn.iOuterShuchakuekiIndex != INT_MIN)
		{
			strInEkimei = pCdDedEkiCont[aOperationTableContentIn.aRessyaProperty.getRessyahoukou()]->get(aOperationTableContentIn.iSyuuchakuEkiOrder).getOuterTerminalEkimei(
				aOperationTableContentIn.iOuterShuchakuekiIndex);
			strInEkijikoku = encode_Ekijikoku(
				aOperationTableContentIn.OuterShuchakuJikoku,
				bDisplaySecondEkiJikoku,
				bDisplayColonEkiJikoku);
		}
		else
		{
			int iSyuuchakuEkiOrder = aOperationTableContentIn.iSyuuchakuEkiOrder;
			if (!pCentDedRessyaIn->isRunBetweenNextEki(iSyuuchakuEkiOrder - 1))
			{
				iSyuuchakuEkiOrder = pCentDedRessyaIn->getRunBetweenEkiBackward(iSyuuchakuEkiOrder);
			}
			strInEkimei = pCdDedEkiCont[aOperationTableContentIn.aRessyaProperty.getRessyahoukou()]->get(iSyuuchakuEkiOrder).getEkimei();
			strInEkijikoku = encode_Ekijikoku(
				pCentDedRessyaIn->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getChakujikoku(),
				bDisplaySecondEkiJikoku,
				bDisplayColonEkiJikoku);
		}
		aRow.getCellCont()->insert(CdCsvCell(strInEkimei));
		aRow.getCellCont()->insert(CdCsvCell(strInEkijikoku));



		if(bDisplayAllRessya)
		{
			int iRessyaIndex = 0;
			int iPropertySameCount = 0;
			for (auto itr = ListOperationTableContent.begin(); itr != ListOperationTableContent.end(); itr++, iRessyaIndex++)
			{
				const CentDedRessya* pCentDedRessya =
					pCentDedRessyaConts[itr->aRessyaProperty.getRessyahoukou()]
					->get(itr->aRessyaProperty.getRessyaIndex());

				/**
					列車方向
					全列車表示時の列車方向は、同一列車扱い設定を加味します
					itr列車のAfterTypeがPropertySameの場合、itrnextとして次の列車を読み込み、そのBeforeTypeがPropertySameなら同一列車扱いとなります。
					同一列車扱いの場合は先頭列車の始発駅Indexと末尾列車の終着駅Indexの大小関係で列車方向を決めます。
				*/
				ERessyahoukou eRessyahoukou = pCentDedRessya->getRessyahoukou();
				if (itr->eAfterType == EBeforeAfterType::BeforeAfterType_PropertySame)
				{
					int iSihatsuEkiIndex = pCentDedRessya->EkiIndexOfEkiOrder(itr->iSihatsuEkiOrder);

					int iSyuuchakuEkiIndex = pCentDedRessya->EkiIndexOfEkiOrder(itr->iSyuuchakuEkiOrder);
					auto itrNext = itr;
					do {
						itrNext++;
						if (itrNext == ListOperationTableContent.end() ||
							itrNext->eBeforeType != EBeforeAfterType::BeforeAfterType_PropertySame)
						{
							//次の列車が末尾を超えた場合、もしくは
							//次の列車の前タイプが同一列車扱い以外なら、一体化は無効その前の列車で終了します。
							break;
						}
						else/* if (itrNext->eBeforeType == EBeforeAfterType::BeforeAfterType_PropertySame)*/
						{
							//次の列車の前タイプが同一列車扱いの場合、通常時および箱ダイヤで列車方向一致、終着→始発が駅順の場合は、次の列車は一体化が確定する。

							itr++;
							iPropertySameCount++;
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
								//次の列車の後タイプが同一列車扱い以外なら、この列車が一体化の末尾となる
								break;
							}
						}
					} while (itrNext != ListOperationTableContent.end());

					if (iSihatsuEkiIndex < iSyuuchakuEkiIndex)
					{
						eRessyahoukou = ERessyahoukou::Ressyahoukou_Kudari;
					}
					else if (iSihatsuEkiIndex > iSyuuchakuEkiIndex)
					{
						eRessyahoukou = ERessyahoukou::Ressyahoukou_Nobori;
					}
					//iSihatsuEkiIndex と iSyuuchakuEkiIndex　が同値の場合は、最初の列車の列車方向をそのまま用います
				}
				if (eRessyahoukou == Ressyahoukou_Kudari)
				{
					aRow.getCellCont()->insert(CdCsvCell(m_nameKudari));
				}
				else
				{
					aRow.getCellCont()->insert(CdCsvCell(m_nameNobori));
				}
				aRow.getCellCont()->insert(CdCsvCell(pCentDedRessya->getRessyabangou()));
				int iRessyaSyubetsuIndex = pCentDedRessya->getRessyasyubetsuIndex();
				if (pCentDedRessyasyubetsuContGet->get(iRessyaSyubetsuIndex)->getParentSyubetsuIndex() >= 0 &&
					bDisplayParentSyubetsu)
				{
					iRessyaSyubetsuIndex = pCentDedRessyasyubetsuContGet->get(iRessyaSyubetsuIndex)->getParentSyubetsuIndex();
				}
				aRow.getCellCont()->insert(CdCsvCell(
					pCentDedRessyasyubetsuContGet->get(iRessyaSyubetsuIndex)->getSyubetsumei()));
				if (bDisplayRessyamei)
				{
					aRow.getCellCont()->insert(CdCsvCell(pCentDedRessya->getRessyamei()));
					aRow.getCellCont()->insert(CdCsvCell(pCentDedRessya->getGousuu()));
					if (pCentDedRessya->getGousuu().empty())
					{
						aRow.getCellCont()->insert(CdCsvCell());
					}
					else
					{
						aRow.getCellCont()->insert(CdCsvCell(m_nameGou));
					}
				}
				if (iRessyaIndex + iPropertySameCount < (int)ListOperationTableContent.size() - 1)
				{
					aRow.getCellCont()->insert(CdCsvCell(m_nameArrow));
				}
			}
		}
		else
		{
			if (pCentDedRessyaOut->getRessyahoukou() == Ressyahoukou_Kudari)
			{
				aRow.getCellCont()->insert(CdCsvCell(m_nameKudari));
			}
			else
			{
				aRow.getCellCont()->insert(CdCsvCell(m_nameNobori));
			}
			aRow.getCellCont()->insert(CdCsvCell(pCentDedRessyaOut->getRessyabangou()));
			int iRessyaSyubetsuIndex = pCentDedRessyaOut->getRessyasyubetsuIndex();
			if (pCentDedRessyasyubetsuContGet->get(iRessyaSyubetsuIndex)->getParentSyubetsuIndex() >= 0 &&
				bDisplayParentSyubetsu)
			{
				iRessyaSyubetsuIndex = pCentDedRessyasyubetsuContGet->get(iRessyaSyubetsuIndex)->getParentSyubetsuIndex();
			}
			aRow.getCellCont()->insert(CdCsvCell(
				pCentDedRessyasyubetsuContGet->get(iRessyaSyubetsuIndex)->getSyubetsumei()));
			if (bDisplayRessyamei)
			{
				aRow.getCellCont()->insert(CdCsvCell(pCentDedRessyaOut->getRessyamei()));
				aRow.getCellCont()->insert(CdCsvCell(pCentDedRessyaOut->getGousuu()));
				if (pCentDedRessyaOut->getGousuu().empty())
				{
					aRow.getCellCont()->insert(CdCsvCell());
				}
				else
				{
					aRow.getCellCont()->insert(CdCsvCell(m_nameGou));
				}
			}

			aRow.getCellCont()->insert(CdCsvCell(m_nameArrow));

			if (pCentDedRessyaIn->getRessyahoukou() == Ressyahoukou_Kudari)
			{
				aRow.getCellCont()->insert(CdCsvCell(m_nameKudari));
			}
			else
			{
				aRow.getCellCont()->insert(CdCsvCell(m_nameNobori));
			}
			aRow.getCellCont()->insert(CdCsvCell(pCentDedRessyaIn->getRessyabangou()));
			iRessyaSyubetsuIndex = pCentDedRessyaIn->getRessyasyubetsuIndex();
			if (pCentDedRessyasyubetsuContGet->get(iRessyaSyubetsuIndex)->getParentSyubetsuIndex() >= 0 &&
				bDisplayParentSyubetsu)
			{
				iRessyaSyubetsuIndex = pCentDedRessyasyubetsuContGet->get(iRessyaSyubetsuIndex)->getParentSyubetsuIndex();
			}
			aRow.getCellCont()->insert(CdCsvCell(
				pCentDedRessyasyubetsuContGet->get(iRessyaSyubetsuIndex)->getSyubetsumei()));
			if (bDisplayRessyamei)
			{
				aRow.getCellCont()->insert(CdCsvCell(pCentDedRessyaIn->getRessyamei()));
				aRow.getCellCont()->insert(CdCsvCell(pCentDedRessyaIn->getGousuu()));
				if (pCentDedRessyaIn->getGousuu().empty())
				{
					aRow.getCellCont()->insert(CdCsvCell());
				}
				else
				{
					aRow.getCellCont()->insert(CdCsvCell(m_nameGou));
				}
			}
		}
		pCdCsvDocument->getRowCont()->insert(aRow);

	}
	return iRv ;
}

} //namespace ViewAllOperationTable

