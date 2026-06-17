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
//	$Id: CPropEditUI_Operation.cpp 357 2016-08-18 16:59:16Z okm $
// ****************************************************************

/** @file */

#include "stdafx.h"
#include "NsMu\CConvTable.h"
#include "CPropEditUI_Operation.h"
#include "str\CStrCharSizeMb.h"
#include "str\strLf.h"
//#include "Str\tstring.h"
#include "Str\strToWstr.h"
#include "NsOu/dynamic_castOu.h"
#include "NsOu/OuNew.h"
#include "..\entDed\entDed.h"
#include "Str\stringSplit.h"
#include <stdexcept>

namespace ViewJikokuhyou{
	using namespace OuLib::Str;

		
/** ダイアログボックスへの時刻の書式を保持します。 */
const CdDedJikoku::CConv	g_CdDedJikokuConv(
	true ,		//	NoColon 
	CdDedJikoku::CConv::EHour_ZeroToNone ,		//	HourZeroToNone 
	CdDedJikoku::CConv::ESecond_NotIfZero ) ;	//	NoSecond


/**
	時刻のUI形式を解釈して、時刻に変換します。
	エディットコントロールの内容が2桁数字の場合は、
	前の駅時刻Orderをもとに、時を補完します。
@param strUIJikoku [in]
	UI形式の時刻を指定してください。
@param jikokuRevOrder [in]
	直前の『駅時刻』。
	この値は、strControlが分のみ(数字2桁)の場合、時を補完するのに使います。
	『NULL状態』の場合、時の補完は行われません。
@param pCdDedJikoku [out]
	この関数は、文字列の解釈に成功したら、文字列の内容を変換した時刻を
	ここに書き込みます。
@param bBefore
	trueの場合、jikokuRevOrderより前の時刻をとるように変換します
@return
	成功したら 0 以上。時刻への変換ができなければ負の数です。
	-	-1 ;	//	項目数が不足しています。
	-	-2 ;	//	時・分・秒の表記が不正です。
*/
static int	getJikokuFromUI( 
	const tstring& strUIJikoku , 
	const CdDedJikoku& jikokuRevOrder , 
	CdDedJikoku* pCdDedJikoku ,
	const bool bBefore) 
{
	int	iRv = 0 ;
	CdDedJikoku	aCdDedJikoku ;
	tstring	strControl = tstringOf(CStrCharSizeMb::strToSingleByte( 
		stringOf(OuLib::Str::strTrim( strUIJikoku) ) ) ) ;

	int iResult = aCdDedJikoku.decode( strControl ) ;
	if ( iResult < 0 )
	{
		iRv = iResult ;
		//	文字列が解釈できません。
	}
	//iRv = 
	//-	-1 ;	//	項目数が不足しています。
	//-	-2 ;	//	時・分・秒の表記が不正です。

	//	着時刻が2桁で、前の駅時刻がある場合は、
	//	着時刻に時を補完
	if ( iRv == -1 && 
		 !jikokuRevOrder.isNull() && 
		strControl.size() == 2 && 
		isdigit( strControl[0] ) && 
		isdigit( strControl[1] ) )
	{
		if (bBefore)
		{
			int iMin = _ttoi(strControl.c_str());
			if (0 <= iMin && iMin < 60)
			{
				aCdDedJikoku.setTime(jikokuRevOrder.getHour(), iMin);
				CdDedJikan	jikanSub = aCdDedJikoku.subJikoku(
					jikokuRevOrder);
				if (jikanSub.getTotalSeconds() > 0)
				{
					aCdDedJikoku = aCdDedJikoku.getTotalSeconds() - 60 * 60;
				}
				//aCdDedJikoku = 現在入力された2桁の文字列に、
				//	jikokuRevOrder 以後となる時を補完

				iRv = 0;	//	時刻補完に成功しました。 
			}
		}
		else
		{
			int iMin = _ttoi(strControl.c_str());
			if (0 <= iMin && iMin < 60)
			{
				aCdDedJikoku.setTime(jikokuRevOrder.getHour(), iMin);
				CdDedJikan	jikanSub = aCdDedJikoku.subJikoku(
					jikokuRevOrder);
				if (jikanSub.getTotalSeconds() < 0)
				{
					aCdDedJikoku = aCdDedJikoku.getTotalSeconds() + 60 * 60;
				}
				//aCdDedJikoku = 現在入力された2桁の文字列に、
				//	jikokuRevOrder 以後となる時を補完

				iRv = 0;	//	時刻補完に成功しました。 
			}
		}
	}

	// --------------------------------
	if ( pCdDedJikoku != NULL )
	{
		*pCdDedJikoku = aCdDedJikoku ;
	}
	return iRv ;
}

	// ********************************
	//@name エラーメッセージ
	// ********************************

const TCHAR* const CPropEditUI_Operation::ERRMSG_INVALID_SHUNTHATSUJIKOKU = _T("Invalid ShuntHatsuJikoku.");//01
const TCHAR* const CPropEditUI_Operation::ERRMSG_INVALID_SHUNTCHAKUJIKOKU = _T("Invalid ShuntChakuJikoku.");//02
//const TCHAR* const CPropEditUI_Operation::ERRMSG_OUTOFRANGE_SHUNTHATSUJIKOKU = _T("OutOfRange ShuntHatsuJikoku.");//03
//const TCHAR* const CPropEditUI_Operation::ERRMSG_OUTOFRANGE_SHUNTCHAKUJIKOKU = _T("OutOfRange ShuntChakuJikoku.");//04
const TCHAR* const CPropEditUI_Operation::ERRMSG_INVALID_CONNECTJIKOKU = _T("Invalid ConnectJikoku.");//11
//const TCHAR* const CPropEditUI_Operation::ERRMSG_OUTOFRANGE_CONNECTJIKOKU = _T("OutOfRange ConnectJikoku.");//12
const TCHAR* const CPropEditUI_Operation::ERRMSG_INVALID_RELEASEJIKOKU = _T("Invalid ReleaseJikoku.");//21
//const TCHAR* const CPropEditUI_Operation::ERRMSG_OUTOFRANGE_RELEASEJIKOKU = _T("OutOfRange ReleaseJikoku.");//22
const TCHAR* const CPropEditUI_Operation::ERRMSG_INVALID_RELEASEINDEX = _T("Invalid ReleaseIndex.");//23
const TCHAR* const CPropEditUI_Operation::ERRMSG_OUTOFRANGE_RELEASEINDEX = _T("OutOfRange ReleaseIndex.");//24,25
const TCHAR* const CPropEditUI_Operation::ERRMSG_INVALID_OUTJIKOKU = _T("Invalid OutJikoku.");//31
//const TCHAR* const CPropEditUI_Operation::ERRMSG_OUTOFRANGE_OUTJIKOKU = _T("OutOfRange OutJikoku.");//32
const TCHAR* const CPropEditUI_Operation::ERRMSG_INVALID_INJIKOKU = _T("Invalid InJikoku.");//33
//const TCHAR* const CPropEditUI_Operation::ERRMSG_OUTOFRANGE_INJIKOKU = _T("OutOfRange InJikoku.");//34
const TCHAR* const CPropEditUI_Operation::ERRMSG_INVALID_OUTERHATSUJIKOKU = _T("Invalid OuterHatsuJikoku.");//41
const TCHAR* const CPropEditUI_Operation::ERRMSG_INVALID_CHAKUJIKOKU = _T("Invalid ChakuJikoku.");//42
//const TCHAR* const CPropEditUI_Operation::ERRMSG_OUTOFRANGE_CHAKUJIKOKU = _T("OutOfRange ChakuJikoku.");//43
const TCHAR* const CPropEditUI_Operation::ERRMSG_EMPTY_OUTERHATSUJIKOKU = _T("Empty OuterHatsuJikoku.");//44
const TCHAR* const CPropEditUI_Operation::ERRMSG_INVALID_HATSUJIKOKU = _T("Invalid HatsuJikoku.");//45
const TCHAR* const CPropEditUI_Operation::ERRMSG_INVALID_OUTERCHAKUJIKOKU = _T("Invalid OuterChakuJikoku.");//46
//const TCHAR* const CPropEditUI_Operation::ERRMSG_OUTOFRANGE_HATSUJIKOKU = _T("OutOfRange HatsuJikoku.");//47
const TCHAR* const CPropEditUI_Operation::ERRMSG_EMPTY_OUTERCHAKUJIKOKU = _T("Empty OuterChakuJikoku.");//48
const TCHAR* const CPropEditUI_Operation::ERRMSG_INVALID_ORIGINJIKOKU = _T("Invalid OriginJikoku.");//51
const TCHAR* const CPropEditUI_Operation::ERRMSG_INVALID_TERMINALJIKOKU = _T("Invalid TerminalJikoku.");//52
const TCHAR* const CPropEditUI_Operation::ERRMSG_UNUSABLE_COMMA = _T("OperationNumber Unusable comma.");//35
const TCHAR* const CPropEditUI_Operation::ERRMSG_EMPTY_OPERATIONNUMBER = _T("Empty OperationNumber.");//61
const TCHAR* const CPropEditUI_Operation::ERRMSG_UNUSABLE_COMMA_INOUTLINKCODE = _T("InOutLinkCode Unusable comma.");//36
const TCHAR* const CPropEditUI_Operation::ERRMSG_UNUSABLE_SLASH = _T("InOutLinkCode Unusable slash.");//37
const TCHAR* const CPropEditUI_Operation::ERRMSG_UNUSABLE_DOLLAR = _T("InOutLinkCode Unusable dollar.");//38




	// ================================
	//@name 下請関数
	// ================================

//const CConvTable<CentDedOperationBeforeRelease::EBReleasePos, int>& getBReleasePosConvTable()
//{
//	static CConvTable<CentDedOperationBeforeRelease::EBReleasePos, int>	aTable;
//	if (aTable.size() == 0)
//	{
//		aTable.add(CentDedOperationBeforeRelease::BReleasePos_Back, 0);//	後部
//		aTable.add(CentDedOperationBeforeRelease::BReleasePos_Front, 1);//	前部
//		aTable.add(CentDedOperationBeforeRelease::BReleasePos_FrontLeave, 2);//	前部主編成数指定
//	}
//	return aTable;
//}
//const CConvTable<CentDedOperationAfterRelease::EAReleasePos, int>& getAReleasePosConvTable()
//{
//	static CConvTable<CentDedOperationAfterRelease::EAReleasePos, int>	aTable;
//	if (aTable.size() == 0)
//	{
//		aTable.add(CentDedOperationAfterRelease::AReleasePos_Back, 0);//	後部
//		aTable.add(CentDedOperationAfterRelease::AReleasePos_Front, 1);//	前部
//		aTable.add(CentDedOperationAfterRelease::AReleasePos_FrontLeave, 2);//	前部主編成数指定
//	}
//	return aTable;
//}
	// ================================
	//@name UiData - Target間のデータ転送
	// ================================

	

vector<Operation> CPropEditUI_Operation::BeforeOperationFromTarget(
	const CentDedBeforeOperationCont * pCentDedBeforeOperationCont,
	const vector<int> iLevel)
{
	vector<Operation> sOperationB;
	CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);

	for (int idx = 0; idx < pCentDedBeforeOperationCont->size(); idx++)
	{
		const CentDedBeforeOperation*	pBeforeOperation
			= pCentDedBeforeOperationCont->getMuPtr()->get(idx);
		if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
		{
			Operation sOperationTemp;
			sOperationTemp.iOperation = 0;
			sOperationTemp.iComboData1 = pBeforeOperation->getShuntTrackIndex();
			sOperationTemp.strEditData1 = aJikokuConv.encode(
				pBeforeOperation->getOperationHatsuJikoku());
			sOperationTemp.strEditData2 = aJikokuConv.encode(
				pBeforeOperation->getOperationChakuJikoku(false));
			sOperationTemp.bCheckData1 = pBeforeOperation->getIsDisplayChakuJikoku();
			sOperationTemp.iLevel = iLevel;
			sOperationTemp.iLevel.push_back(idx);

			sOperationB.push_back(sOperationTemp);

		}
		else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
		{
			Operation sOperationTemp;
			sOperationTemp.iOperation = 1;
			sOperationTemp.iComboData1 =
				pBeforeOperation->getIsConnectToFront() ? 1 : 0;
			sOperationTemp.strEditData1 = aJikokuConv.encode(
				pBeforeOperation->getConnectJikoku());
			sOperationTemp.iLevel = iLevel;
			sOperationTemp.iLevel.push_back(idx);

			vector<Operation> sOperationBTemp =
				BeforeOperationFromTarget(
					pBeforeOperation->getCentDedBeforeOperationCont(),
					sOperationTemp.iLevel);

			//増結の場合、時系列に沿って、先に子作業をUiDataに追加したあと、この増結作業を追加する
			sOperationB.insert(sOperationB.end(), sOperationBTemp.begin(), sOperationBTemp.end());
			sOperationB.push_back(sOperationTemp);
		}
		else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
		{
			Operation sOperationTemp;
			sOperationTemp.iOperation = 2;
			sOperationTemp.iComboData1 = pBeforeOperation->getReleasePos();
			sOperationTemp.strEditData1 = to_tstring(pBeforeOperation->getReleaseIndexCount());
			sOperationTemp.strEditData2 = aJikokuConv.encode(
				pBeforeOperation->getReleaseJikoku());
			sOperationTemp.iLevel = iLevel;
			sOperationTemp.iLevel.push_back(idx);

			vector<Operation> sOperationATemp =
				AfterOperationFromTarget(
					pBeforeOperation->getCentDedAfterOperationCont(),
					sOperationTemp.iLevel);

			//解結の場合、時系列に沿って、先にこの解結作業を追加したあと、子作業を追加する
			sOperationB.push_back(sOperationTemp);
			sOperationB.insert(sOperationB.end(), sOperationATemp.begin(), sOperationATemp.end());
		}
		else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Out)
		{
			Operation sOperationTemp;
			sOperationTemp.iOperation = 3;
			sOperationTemp.strEditData1 = aJikokuConv.encode(
				pBeforeOperation->getOutJikoku());
			sOperationTemp.strOperationNumber = pBeforeOperation->getOperationNumberOriginal();
			sOperationTemp.strInOutLinkCode = pBeforeOperation->getInOutLinkCode();
			sOperationTemp.iLevel = iLevel;
			sOperationTemp.iLevel.push_back(idx);

			sOperationB.push_back(sOperationTemp);
		}
		else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
		{
			Operation sOperationTemp;
			sOperationTemp.iOperation = 4;
			sOperationTemp.iComboData1 = pBeforeOperation->getOuterShihatsuekiIndex();
			sOperationTemp.strEditData1 = aJikokuConv.encode(
				pBeforeOperation->getOuterShihatsuJikoku());
			sOperationTemp.strEditData2 = aJikokuConv.encode(
				pBeforeOperation->getChakuJikoku());
			sOperationTemp.strOperationNumber = pBeforeOperation->getOperationNumberOriginal();
			sOperationTemp.strInOutLinkCode = pBeforeOperation->getInOutLinkCode();
			sOperationTemp.iLevel = iLevel;
			sOperationTemp.iLevel.push_back(idx);

			sOperationB.push_back(sOperationTemp);
		}
		else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Junction)
		{
			Operation sOperationTemp;
			sOperationTemp.iOperation = 5;
			sOperationTemp.strEditData1 = aJikokuConv.encode(
				pBeforeOperation->getOriginJikoku());
			sOperationTemp.strOperationNumber = pBeforeOperation->getOperationNumberTemp();
			sOperationTemp.iLevel = iLevel;
			sOperationTemp.iLevel.push_back(idx);

			sOperationB.push_back(sOperationTemp);
		}
		else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_NumberChange)
		{
			Operation sOperationTemp;
			sOperationTemp.iOperation = 6;
			sOperationTemp.strOperationNumber = pBeforeOperation->getOperationNumberOriginal();
			sOperationTemp.bCheckData1 = pBeforeOperation->getOperationNumberReverse();
			sOperationTemp.iLevel = iLevel;
			sOperationTemp.iLevel.push_back(idx);

			sOperationB.push_back(sOperationTemp);
		}
	}
	return sOperationB;
}

vector<Operation> CPropEditUI_Operation::AfterOperationFromTarget(
	const CentDedAfterOperationCont * pCentDedAfterOperationCont,
	const vector<int> iLevel)
{
	//pCentDedOperationAfterContには、作業が時系列順に収められている
	vector<Operation> sOperationA;
	CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
	for (int idx = 0; idx < pCentDedAfterOperationCont->size(); idx++)
	{
		const CentDedAfterOperation*	pAfterOperation
			= pCentDedAfterOperationCont->getMuPtr()->get(idx);
		if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
		{
			Operation sOperationTemp;
			sOperationTemp.iOperation = 0;
			sOperationTemp.iComboData1 = pAfterOperation->getShuntTrackIndex();
			sOperationTemp.strEditData1 = aJikokuConv.encode(
				pAfterOperation->getOperationHatsuJikoku());
			sOperationTemp.strEditData2 = aJikokuConv.encode(
				pAfterOperation->getOperationChakuJikoku(false));
			sOperationTemp.bCheckData1 = pAfterOperation->getIsDisplayHatsuJikoku();
			sOperationTemp.iLevel = iLevel;
			sOperationTemp.iLevel.push_back(idx);

			sOperationA.push_back(sOperationTemp);

		}
		else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
		{
			Operation sOperationTemp;
			sOperationTemp.iOperation = 1;
			sOperationTemp.iComboData1 =
				pAfterOperation->getIsConnectToFront() ? 1 : 0;
			sOperationTemp.strEditData1 = aJikokuConv.encode(
				pAfterOperation->getConnectJikoku());
			sOperationTemp.iLevel = iLevel;
			sOperationTemp.iLevel.push_back(idx);

			vector<Operation> sOperationBTemp =
				BeforeOperationFromTarget(
					pAfterOperation->getCentDedBeforeOperationCont(),
					sOperationTemp.iLevel);

			sOperationA.insert(sOperationA.end(), sOperationBTemp.begin(), sOperationBTemp.end());
			sOperationA.push_back(sOperationTemp);
		}
		else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
		{
			Operation sOperationTemp;
			sOperationTemp.iOperation = 2;
			sOperationTemp.iComboData1 = pAfterOperation->getReleasePos();
			sOperationTemp.strEditData1 = to_tstring(pAfterOperation->getReleaseIndexCount());
			sOperationTemp.strEditData2 = aJikokuConv.encode(
				pAfterOperation->getReleaseJikoku());
			sOperationTemp.iLevel = iLevel;
			sOperationTemp.iLevel.push_back(idx);

			vector<Operation> sOperationATemp =
				AfterOperationFromTarget(
					pAfterOperation->getCentDedAfterOperationCont(),
					sOperationTemp.iLevel);

			sOperationA.push_back(sOperationTemp);
			sOperationA.insert(sOperationA.end(), sOperationATemp.begin(), sOperationATemp.end());
		}
		else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_In)
		{
			Operation sOperationTemp;
			sOperationTemp.iOperation = 3;
			sOperationTemp.strEditData1 = aJikokuConv.encode(
				pAfterOperation->getInJikoku());
			sOperationTemp.strInOutLinkCode = pAfterOperation->getInOutLinkCode();
			sOperationTemp.iLevel = iLevel;
			sOperationTemp.iLevel.push_back(idx);

			sOperationA.push_back(sOperationTemp);
		}
		else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
		{
			Operation sOperationTemp;
			sOperationTemp.iOperation = 4;
			sOperationTemp.iComboData1 = pAfterOperation->getOuterShuchakuekiIndex();
			sOperationTemp.strEditData1 = aJikokuConv.encode(
				pAfterOperation->getHatsuJikoku());
			sOperationTemp.strEditData2 = aJikokuConv.encode(
				pAfterOperation->getOuterShuchakuJikoku());
			sOperationTemp.strInOutLinkCode = pAfterOperation->getInOutLinkCode();
			sOperationTemp.iLevel = iLevel;
			sOperationTemp.iLevel.push_back(idx);

			sOperationA.push_back(sOperationTemp);
		}
		else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Junction)
		{
			Operation sOperationTemp;
			sOperationTemp.iOperation = 5;
			sOperationTemp.iComboData1 = pAfterOperation->getNextJunctionType();
			sOperationTemp.strEditData1 = aJikokuConv.encode(
				pAfterOperation->getTerminalJikoku());
			sOperationTemp.iLevel = iLevel;
			sOperationTemp.iLevel.push_back(idx);

			sOperationA.push_back(sOperationTemp);
		}
		else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_NumberChange)
		{
			Operation sOperationTemp;
			sOperationTemp.iOperation = 6;
			sOperationTemp.strOperationNumber = pAfterOperation->getOperationNumberOriginal();
			sOperationTemp.bCheckData1 = pAfterOperation->getOperationNumberReverse();
			sOperationTemp.iLevel = iLevel;
			sOperationTemp.iLevel.push_back(idx);

			sOperationA.push_back(sOperationTemp);
		}
	}
	return sOperationA;
}

void CPropEditUI_Operation::UiDataFromTarget(UIDATA* pUiData)
{
	CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);
	CentDedRessya* pRessya = m_pTarget->get(0);
	CentDedEkiJikoku aChakuEkiJikoku;
	CentDedEkiJikoku aHatsuEkiJikoku;
	if (m_iChakuEkiOrder == -1)
	{
		aChakuEkiJikoku = pRessya->getCentDedEkiJikoku(m_iHatsuEkiOrder);
	}
	else
	{
		aChakuEkiJikoku = pRessya->getCentDedEkiJikoku(m_iChakuEkiOrder);
	}
	if (m_iHatsuEkiOrder == -1)
	{
		aHatsuEkiJikoku = pRessya->getCentDedEkiJikoku(m_iChakuEkiOrder);
	}
	else
	{
		aHatsuEkiJikoku = pRessya->getCentDedEkiJikoku(m_iHatsuEkiOrder);
	}

	/**
		着時刻
	*/
	pUiData->strChakujikoku = aJikokuConv.encode(
		aChakuEkiJikoku.getChakujikoku());

	/**
		発時刻
	*/
	pUiData->strHatsujikoku = aJikokuConv.encode(
		aHatsuEkiJikoku.getHatsujikoku());

	/**
		前作業
	*/
	pUiData->sOperationB = BeforeOperationFromTarget(
		aChakuEkiJikoku.getCentDedBeforeOperationCont(),
		vector<int>());
	if (pUiData->sOperationB.empty())
	{
		pUiData->sOperationB.push_back(Operation());
		pUiData->sOperationB.front().iOperation = 7;
		pUiData->sOperationB.front().iLevel = { 0 };
	}


	/**
		後作業
	*/
	pUiData->sOperationA = AfterOperationFromTarget(
		aHatsuEkiJikoku.getCentDedAfterOperationCont(),
		vector<int>());
	if (pUiData->sOperationA.empty())
	{
		pUiData->sOperationA.push_back(Operation());
		pUiData->sOperationA.front().iOperation = 7;
		pUiData->sOperationA.front().iLevel = { 0 };
	}

	if (m_iFocusIndex >= 0)
	{
		pUiData->bSelectedAfter = m_bFocusAfter;
		vector<int> iFocusLevel = { m_iFocusIndex };

		if (m_bFocusAfter)
		{
			for (int idxa = 0; idxa < (int)pUiData->sOperationA.size(); idxa++)
			{
				if (pUiData->sOperationA[idxa].iLevel == iFocusLevel)
				{
					if (m_bFocusChild)
					{
						if (pUiData->sOperationA[idxa].iOperation == 1)
						{
							//増結の場合、増結編成前作業の先頭位置を返します
							//前作業コンテナを逆方向にさかのぼっていき、iLevelの一桁目が、m_bFocusAfterと一致しないもの
							//が見つかったら、その一つ後が、増結編成前作業の先頭位置となります。
							for (int idxc = idxa - 1; idxc >= 0; idxc--)
							{
								if (pUiData->sOperationA[idxc].iLevel.front() != m_iFocusIndex)
								{
									pUiData->iListSelected = idxc + 1;
								}
								else if (idxc == 0)
								{
									pUiData->iListSelected = 0;
								}
							}
						}
						else if (pUiData->sOperationA[idxa].iOperation == 2)
						{
							//解結の場合、解結編成後作業の末尾位置を返します
							//前作業コンテナを順方向に辿っていき、iLevelの一桁目が、m_bFocusAfterと一致しないもの
							//が見つかったら、その一つ前が、解結編成後作業の末尾位置となります。
							for (int idxc = idxa + 1; idxc < (int)pUiData->sOperationA.size(); idxc++)
							{
								if (pUiData->sOperationA[idxc].iLevel.front() != m_iFocusIndex)
								{
									pUiData->iListSelected = idxc - 1;
								}
								else if (idxc == (int)pUiData->sOperationA.size() - 1)
								{
									pUiData->iListSelected = (int)pUiData->sOperationA.size() - 1;
								}
							}
						}
						else
						{
							pUiData->iListSelected = idxa;
						}
					}
					else
					{
						pUiData->iListSelected = idxa;
					}
					break;
				}
			}
		}
		else
		{
			for (int idxb = 0; idxb < (int)pUiData->sOperationB.size(); idxb++)
			{
				if (pUiData->sOperationB[idxb].iLevel == iFocusLevel)
				{
					if (m_bFocusChild)
					{
						if (pUiData->sOperationB[idxb].iOperation == 1)
						{
							//増結の場合、増結編成前作業の先頭位置を返します
							//前作業コンテナを逆方向にさかのぼっていき、iLevelの一桁目が、m_bFocusAfterと一致しないもの
							//が見つかったら、その一つ後が、増結編成前作業の先頭位置となります。
							for (int idxc = idxb - 1; idxc >= 0; idxc--)
							{
								if (pUiData->sOperationB[idxc].iLevel.front() != m_iFocusIndex)
								{
									pUiData->iListSelected = idxc + 1;
								}
								else if (idxc == 0)
								{
									pUiData->iListSelected = 0;
								}
							}
						}
						else if (pUiData->sOperationB[idxb].iOperation == 2)
						{
							//解結の場合、解結編成後作業の末尾位置を返します
							//前作業コンテナを順方向に辿っていき、iLevelの一桁目が、m_bFocusAfterと一致しないもの
							//が見つかったら、その一つ前が、解結編成後作業の末尾位置となります。
							for (int idxc = idxb + 1; idxc < (int)pUiData->sOperationB.size(); idxc++)
							{
								if (pUiData->sOperationB[idxc].iLevel.front() != m_iFocusIndex)
								{
									pUiData->iListSelected = idxc - 1;
								}
								else if (idxc == (int)pUiData->sOperationB.size() - 1)
								{
									pUiData->iListSelected = (int)pUiData->sOperationB.size() - 1;
								}
							}
						}
						else
						{
							pUiData->iListSelected = idxb;
						}
					}
					else
					{
						pUiData->iListSelected = idxb;
					}
					break;
				}
			}
		}
	}
}
void CPropEditUI_Operation::AdjustUiData( 
		UIDATA* pUiData , 
		const UIDATA* pUiDataPrev , 
		bool bStartEdit )
{
	/**
		iUiOperationが0(詳細変更)のときに行われます。
		・iOperationの変更に伴う、不要パラメータの削除
		・時刻が入力された場合の正規化
	*/
	if (pUiData->iUiOperation == 0 &&
		pUiData->iListSelected >= 0)
	{
		vector<Operation> sOperationCont;
		vector<Operation> sOperationContPrev;
		if (pUiData->bSelectedAfter)
		{
			sOperationCont = pUiData->sOperationA;
			sOperationContPrev = pUiDataPrev->sOperationA;
		}
		else
		{
			sOperationCont = pUiData->sOperationB;
			sOperationContPrev = pUiDataPrev->sOperationB;
		}
		Operation sOprationSel;
		Operation sOprationSelPrev;
		sOprationSel = sOperationCont[pUiData->iListSelected];
		sOprationSelPrev = sOperationContPrev[pUiData->iListSelected];

		//if (pUiData->bSelectedAfter)
		//{
		//	pOprationSel = &pUiData->sOperationA[pUiData->iListSelected];
		//	pOprationSelPrev = &pUiDataPrev->sOperationA[pUiData->iListSelected];
		//}
		//else
		//{
		//	pOprationSel = &pUiData->sOperationB[pUiData->iListSelected];
		//	pOprationSelPrev = &pUiDataPrev->sOperationB[pUiData->iListSelected];
		//}

		//	作業種類
		if (bStartEdit || sOprationSelPrev.iOperation != sOprationSel.iOperation)
		{
			if (sOprationSelPrev.iOperation == 1)
			{
				//旧作業が増結の場合は、前作業を削除する。
				vector<int> iLevelParent = sOprationSelPrev.iLevel;
				int iDelSize = 0;
				for (int idxb = pUiData->iListSelected - 1; idxb >= 0; idxb--)
				{
					/**
						まず、idxb位置のiLevelの要素数を確認、要素数がiDeliLevel以下なら、子作業ではないので探索終了です
					*/
					if (sOperationCont[idxb].iLevel.size() <= iLevelParent.size())
					{
						break;
					}
					/**
						要素数がiDeliLevelより多い場合は、iDeliLevelの要素数までの値が、一致するか否かを調べます
					*/
					bool bMatch = true;
					//iAddiLevel.size()が1の場合は、forに入らないが問題ない。前方に値が無い、という意味で一致
					for (int idxl = 0; idxl < (int)iLevelParent.size(); idxl++)
					{
						if (sOperationCont[idxb].iLevel[idxl] != iLevelParent[idxl])
						{
							/**
								値が不一致の場合、それより先には子作業は無いので、bMatchをfalseにして探索を抜けます。
							*/
							bMatch = false;
							break;
						}
					}
					if (!bMatch)
					{
						break;
					}
					/**
						iDeliLevel.size()個の値が一致した場合、その作業は子作業です、
						iDelPositionを-1し、iDelSizeを+1します。(削除は後で行う)
					*/
					iDelSize++;
				}

				sOperationCont.erase(
					sOperationCont.begin() + pUiData->iListSelected - iDelSize, 
					sOperationCont.begin() + pUiData->iListSelected );
				//前作業を削除した分、選択位置を移動する
				pUiData->iListSelected -= iDelSize;
			}
			if (sOprationSelPrev.iOperation == 2)
			{
				//旧作業が解結の場合は、後作業を削除する。
				vector<int> iLevelParent = sOprationSelPrev.iLevel;
				int iDelSize = 0;
				for (int idxa = pUiData->iListSelected + 1; idxa < (int)sOperationCont.size(); idxa++)
				{
					/**
						まず、idxa位置のiLevelの要素数を確認、要素数がiDeliLevel以下なら、子作業ではないので探索終了です
					*/
					if (sOperationCont[idxa].iLevel.size() <= iLevelParent.size())
					{
						break;
					}
					/**
						要素数がiDeliLevelより多い場合は、iDeliLevelの要素数までの値が、一致するか否かを調べます
					*/
					bool bMatch = true;
					//iAddiLevel.size()が1の場合は、forに入らないが問題ない。前方に値が無い、という意味で一致
					for (int idxl = 0; idxl < (int)iLevelParent.size(); idxl++)
					{
						if (sOperationCont[idxa].iLevel[idxl] != iLevelParent[idxl])
						{
							/**
								値が不一致の場合、それより先には子作業は無いので、bMatchをfalseにして探索を抜けます。
							*/
							bMatch = false;
							break;
						}
					}
					if (!bMatch)
					{
						break;
					}
					/**
						iDeliLevel.size()個の値が一致した場合、その作業は子作業です、
						iDelSizeを+1します。(削除は後で行う)
					*/
					iDelSize++;
				}

				sOperationCont.erase(
					sOperationCont.begin() + pUiData->iListSelected + 1,
					sOperationCont.begin() + pUiData->iListSelected + iDelSize + 1);
			}

			if (sOprationSel.iOperation == 0)
			{
				/**
					作業種類変更の場合、前作業によって、残すパラメータ・消すパラメータが分かれます
					・増結
						増結時刻を、入換発時刻にします。他はリセットします
					・解結
						解結時刻を、入換発時刻にします。他はリセットします
					・運用番号変更
						値をリセットします
				*/
				if (sOprationSelPrev.iOperation == 1)
				{
					//strEditData1が、増結時刻・入換発時刻なので、そのまま残します
					if (pUiData->bSelectedAfter)
					{
						sOperationCont[pUiData->iListSelected].iComboData1 = m_iStandardShuntTrackIndex[1];
					}
					else
					{
						sOperationCont[pUiData->iListSelected].iComboData1 = m_iStandardShuntTrackIndex[0];
					}
					sOperationCont[pUiData->iListSelected].strEditData2.clear();
				}
				else if (sOprationSelPrev.iOperation == 2)
				{
					if (pUiData->bSelectedAfter)
					{
						sOperationCont[pUiData->iListSelected].iComboData1 = m_iStandardShuntTrackIndex[1];
					}
					else
					{
						sOperationCont[pUiData->iListSelected].iComboData1 = m_iStandardShuntTrackIndex[0];
					}
					sOperationCont[pUiData->iListSelected].strEditData1 =
						sOperationCont[pUiData->iListSelected].strEditData2;
					sOperationCont[pUiData->iListSelected].strEditData2.clear();
				}
				//else if (sOprationSelPrev.iOperation == 6)
				//{
				//	sOperationCont[pUiData->iListSelected].strOperationNumber.clear();
				//}
			}
			else if (sOprationSel.iOperation == 1)
			{
				/**
					作業種類変更の場合、前作業によって、残すパラメータ・消すパラメータが分かれます
					・入換
						入換発時刻を、増結時刻にします。他はリセットします
					・解結
						解結時刻を、増結時刻にします。他はリセットします
					・運用番号変更
						値をリセットします
				*/
				if (sOprationSelPrev.iOperation == 0)
				{
					//strEditData1が、増結時刻・入換発時刻なので、そのまま残します
					sOperationCont[pUiData->iListSelected].iComboData1 = 0;
					sOperationCont[pUiData->iListSelected].strEditData2.clear();
				}
				else if (sOprationSelPrev.iOperation == 2)
				{
					sOperationCont[pUiData->iListSelected].iComboData1 = 0;
					sOperationCont[pUiData->iListSelected].strEditData1 =
						sOperationCont[pUiData->iListSelected].strEditData2;
					sOperationCont[pUiData->iListSelected].strEditData2.clear();
				}
				//else if (sOprationSelPrev.iOperation == 6)
				//{
				//	sOperationCont[pUiData->iListSelected].strOperationNumber.clear();
				//}

				//作業が増結に変わった場合は、前作業を追加します
				Operation sOperationAdd;
				sOperationAdd.iOperation = 5;
				sOperationAdd.iLevel = sOprationSel.iLevel;
				sOperationAdd.iLevel.push_back(0);
				sOperationCont.insert(
					sOperationCont.begin() + pUiData->iListSelected,
					sOperationAdd);
				//作業追加による、選択位置ずれの補正を行います
				pUiData->iListSelected++;
			}
			else if (sOprationSel.iOperation == 2)
			{
				/**
					作業種類変更の場合、前作業によって、残すパラメータ・消すパラメータが分かれます
					・入換
						入換発時刻を、解結時刻にします。他はリセットします
					・増結
						増結時刻を、解結時刻にします。他はリセットします
					・運用番号変更
						値をリセットします
				*/
				if (sOprationSelPrev.iOperation == 0)
				{
					sOperationCont[pUiData->iListSelected].iComboData1 = 0;
					sOperationCont[pUiData->iListSelected].strEditData2 =
						sOperationCont[pUiData->iListSelected].strEditData1;
					sOperationCont[pUiData->iListSelected].strEditData1 = _T("1");
				}
				else if (sOprationSelPrev.iOperation == 1)
				{
					sOperationCont[pUiData->iListSelected].iComboData1 = 0;
					sOperationCont[pUiData->iListSelected].strEditData2 =
						sOperationCont[pUiData->iListSelected].strEditData1;
					sOperationCont[pUiData->iListSelected].strEditData1 = _T("1");
				}
				//else if (sOprationSelPrev.iOperation == 6)
				//{
				//	sOperationCont[pUiData->iListSelected].strOperationNumber.clear();
				//}
				//作業が解結に変わった場合は、後作業を追加します
				Operation sOperationAdd;
				sOperationAdd.iOperation = 5;
				sOperationAdd.iLevel = sOprationSel.iLevel;
				sOperationAdd.iLevel.push_back(0);
				sOperationCont.insert(
					sOperationCont.begin() + pUiData->iListSelected + 1,
					sOperationAdd);
			}
			else if (sOprationSel.iOperation == 6)
			{
				/**
					後で再考
					作業種類変更の場合、前作業によって、残すパラメータ・消すパラメータが分かれます
					・入換
						値をリセットします
					・増結
						値をリセットします
					・解結
						値をリセットします
				*/
				//if (sOprationSelPrev.iOperation == 0)
				//{
				//	sOperationCont[pUiData->iListSelected].iComboData1 = 0;
				//	sOperationCont[pUiData->iListSelected].strEditData1.clear();
				//	sOperationCont[pUiData->iListSelected].strEditData2.clear();
				//}
				//if (sOprationSelPrev.iOperation == 1)
				//{
				//	//strEditData1が、増結時刻・入換発時刻なので、そのまま残します
				//	sOperationCont[pUiData->iListSelected].iComboData1 = 0;
				//	sOperationCont[pUiData->iListSelected].strEditData2.clear();
				//}
				//else if (sOprationSelPrev.iOperation == 2)
				//{
				//	sOperationCont[pUiData->iListSelected].iComboData1 = 0;
				//	sOperationCont[pUiData->iListSelected].strEditData1 =
				//		sOperationCont[pUiData->iListSelected].strEditData2;
				//	sOperationCont[pUiData->iListSelected].strEditData2.clear();
				//}
			}
			else
			{
				bool bIsBeforeOperation = !pUiData->bSelectedAfter;
				if (sOprationSel.iLevel.size() > 1)
				{
					vector<int> iLevelSearch = sOprationSel.iLevel;
					iLevelSearch.pop_back();
					for (int idxp = 0; idxp < (int)sOperationCont.size(); idxp++)
					{
						if (sOperationCont[idxp].iLevel == iLevelSearch &&
							idxp > pUiData->iListSelected)
						{
							bIsBeforeOperation = true;
							break;
						}
						else if (sOperationCont[idxp].iLevel == iLevelSearch &&
							idxp < pUiData->iListSelected)
						{
							bIsBeforeOperation = false;
							break;
						}
					}

				}
				if (sOprationSel.iOperation == 3)
				{
					if (bIsBeforeOperation &&
						sOprationSelPrev.iOperation == 4)
					{
						sOperationCont[pUiData->iListSelected].strEditData1 =
							sOperationCont[pUiData->iListSelected].strEditData2;
						sOperationCont[pUiData->iListSelected].strEditData2.clear();
					}
				}
				else if (sOprationSel.iOperation == 4)
				{
					if (bIsBeforeOperation &&
						(sOprationSelPrev.iOperation == 3 ||
						sOprationSelPrev.iOperation == 5))
					{
						if ((int)m_iStandardOuterTerminalJikan.size() > sOprationSel.iComboData1 &&
							m_iStandardOuterTerminalJikan[sOprationSel.iComboData1][0] != 0)
						{
							CdDedJikoku aBaseJikoku(pUiData->strHatsujikoku);
							if (aBaseJikoku.isNull())
							{
								aBaseJikoku.decode(pUiData->strChakujikoku);
							}
							CdDedJikoku aOuterHatsuJikoku =
								aBaseJikoku.addSeconds(-(m_iStandardOuterTerminalJikan[sOprationSel.iComboData1][0]));
							CdDedJikoku aChakuJikoku =
								aBaseJikoku.addSeconds(-(m_iStandardOuterTerminalJikan[sOprationSel.iComboData1][1]));
							sOperationCont[pUiData->iListSelected].strEditData1 =
								g_CdDedJikokuConv.encode(aOuterHatsuJikoku);
							sOperationCont[pUiData->iListSelected].strEditData2 =
								g_CdDedJikokuConv.encode(aChakuJikoku);
						}
						else
						{
							sOperationCont[pUiData->iListSelected].strEditData2 =
								sOperationCont[pUiData->iListSelected].strEditData1;
							sOperationCont[pUiData->iListSelected].strEditData1.clear();
						}
					}
					if (!bIsBeforeOperation &&
						(sOprationSelPrev.iOperation == 3 ||
							sOprationSelPrev.iOperation == 5))
					{
						if (sOperationCont[pUiData->iListSelected].iComboData1 > (int)m_iStandardOuterTerminalJikan.size())
						{
							sOperationCont[pUiData->iListSelected].iComboData1 = 0;
						}
						if ((int)m_iStandardOuterTerminalJikan.size() > sOprationSel.iComboData1 &&
							m_iStandardOuterTerminalJikan[sOprationSel.iComboData1][0] != 0)
						{
							CdDedJikoku aBaseJikoku(pUiData->strChakujikoku);
							if (aBaseJikoku.isNull())
							{
								aBaseJikoku.decode(pUiData->strHatsujikoku);
							}
							CdDedJikoku aHatsuJikoku =
								aBaseJikoku.addSeconds(m_iStandardOuterTerminalJikan[sOprationSel.iComboData1][1]);
							CdDedJikoku aOuterChakuJikoku =
								aBaseJikoku.addSeconds(m_iStandardOuterTerminalJikan[sOprationSel.iComboData1][0]);
							sOperationCont[pUiData->iListSelected].strEditData1 =
								g_CdDedJikokuConv.encode(aHatsuJikoku);
							sOperationCont[pUiData->iListSelected].strEditData2 =
								g_CdDedJikokuConv.encode(aOuterChakuJikoku);
						}
					}
				}
				else if (sOprationSel.iOperation == 5)
				{
					if (bIsBeforeOperation &&
						sOprationSelPrev.iOperation == 4)
					{
						sOperationCont[pUiData->iListSelected].strEditData1 =
							sOperationCont[pUiData->iListSelected].strEditData2;
						sOperationCont[pUiData->iListSelected].strEditData2.clear();
					}
					if (!bIsBeforeOperation)
					{
						sOperationCont[pUiData->iListSelected].iComboData1 = 0;
					}
				}
			}
		}



		//	iComboData1
		if (bStartEdit || sOprationSelPrev.iComboData1 != sOprationSel.iComboData1)
		{
			if (sOprationSel.iOperation == 4)
			{
				bool bIsBeforeOperation = !pUiData->bSelectedAfter;
				if (sOprationSel.iLevel.size() > 1)
				{
					vector<int> iLevelSearch = sOprationSel.iLevel;
					iLevelSearch.pop_back();
					for (int idxp = 0; idxp < (int)sOperationCont.size(); idxp++)
					{
						if (sOperationCont[idxp].iLevel == iLevelSearch &&
							idxp > pUiData->iListSelected)
						{
							bIsBeforeOperation = true;
							break;
						}
						else if (sOperationCont[idxp].iLevel == iLevelSearch &&
							idxp < pUiData->iListSelected)
						{
							bIsBeforeOperation = false;
							break;
						}
					}
				}

				if (bIsBeforeOperation)
				{
					if ((int)m_iStandardOuterTerminalJikan.size() > sOprationSel.iComboData1 &&
						m_iStandardOuterTerminalJikan[sOprationSel.iComboData1][0] != 0)
					{
						CdDedJikoku aBaseJikoku(pUiData->strHatsujikoku);
						if (aBaseJikoku.isNull())
						{
							aBaseJikoku.decode(pUiData->strChakujikoku);
						}
						CdDedJikoku aOuterHatsuJikoku = aBaseJikoku;
						aOuterHatsuJikoku.addSeconds(-(m_iStandardOuterTerminalJikan[sOprationSel.iComboData1][0]));
						sOperationCont[pUiData->iListSelected].strEditData1 =
							g_CdDedJikokuConv.encode(aOuterHatsuJikoku);
						if (sOprationSel.strEditData2.empty())
						{
							CdDedJikoku aChakuJikoku = aBaseJikoku;
							aChakuJikoku.addSeconds(-(m_iStandardOuterTerminalJikan[sOprationSel.iComboData1][1]));
							sOperationCont[pUiData->iListSelected].strEditData2 =
								g_CdDedJikokuConv.encode(aChakuJikoku);
						}
					}
				}
				else
				{
					if ((int)m_iStandardOuterTerminalJikan.size() > sOprationSel.iComboData1 &&
						m_iStandardOuterTerminalJikan[sOprationSel.iComboData1][0] != 0)
					{
						CdDedJikoku aBaseJikoku(pUiData->strChakujikoku);
						if (aBaseJikoku.isNull())
						{
							aBaseJikoku.decode(pUiData->strHatsujikoku);
						}
						CdDedJikoku aOuterChakuJikoku = aBaseJikoku;
						aOuterChakuJikoku.addSeconds(m_iStandardOuterTerminalJikan[sOprationSel.iComboData1][0]);
						sOperationCont[pUiData->iListSelected].strEditData2 =
							g_CdDedJikokuConv.encode(aOuterChakuJikoku);
						if (sOprationSel.strEditData1.empty())
						{
							CdDedJikoku aHatsuJikoku = aBaseJikoku;
							aHatsuJikoku.addSeconds(m_iStandardOuterTerminalJikan[sOprationSel.iComboData1][1]);
							sOperationCont[pUiData->iListSelected].strEditData1 =
								g_CdDedJikokuConv.encode(aHatsuJikoku);
						}
					}
				}
			}
		}

		//--------------------------------------------------------------------------------
		//	strEditData1
		//--------------------------------------------------------------------------------
		if (bStartEdit || sOprationSelPrev.strEditData1 != sOprationSel.strEditData1)
		{
			if (sOprationSel.iOperation == 0 || sOprationSel.iOperation == 1 ||
				sOprationSel.iOperation == 3 || sOprationSel.iOperation == 4 ||
				sOprationSel.iOperation == 5)
			{
				/**
					時刻の正規化
					(1)半角変換
					(2)時の補完
						時を補完するときは
						(a)始発駅前作業・終着駅を除く後作業・増結の前作業は後方から補完
						(b)終着駅後作業・始発駅を除く前作業・解結の後作業は前方から補完する
					なお、入換の場合は、最初に入換着時刻からの補完も行います
					路線外始発の場合は、最初に当駅着時刻からの補完も行います
					路線外終着の場合は、終着駅着時刻からの補完は行いません
				*/
				CdDedJikoku aJikokuOpeChaku;
				if (sOprationSel.iOperation == 0)
				{
					aJikokuOpeChaku = CdDedJikoku(
						sOprationSel.strEditData2);
					if (!aJikokuOpeChaku.isNull())
					{
						CdDedJikoku aJikokuTemp;
						int iResult = getJikokuFromUI(
							sOprationSel.strEditData1,
							aJikokuOpeChaku,
							&aJikokuTemp,
							true);
						if (iResult >= 0)
						{
							sOperationCont[pUiData->iListSelected].strEditData1 =
								g_CdDedJikokuConv.encode(aJikokuTemp);
						}
					}
				}
				if (aJikokuOpeChaku.isNull() && sOprationSel.iLevel.size() > 1)
				{
					/**
						iLevelが2要素以上ある場合は、子作業なので、前作業か後作業が調べる必要があります
					*/
					vector<int> iLevelSearch = sOprationSel.iLevel;
					iLevelSearch.pop_back();
					for (int idxp = 0; idxp < (int)sOperationCont.size(); idxp++)
					{
						if (sOperationCont[idxp].iLevel == iLevelSearch &&
							idxp > pUiData->iListSelected)
						{
							//idxp(増結)が後にある→後方から補完、増結作業が下限
							CdDedJikoku JikokuNext;

							if (sOprationSel.iOperation == 4)//路線外始発
							{
								JikokuNext = CdDedJikoku(
									sOprationSel.strEditData2);
							}

							for (int idxb = pUiData->iListSelected + 1;
								idxb <= idxp && JikokuNext.isNull(); idxb++)
							{
								if (sOperationCont[idxb].iLevel.size() > sOprationSel.iLevel.size())
								{
									/**
										探索箇所のiLevel要素数が、sOprationSelよりも多い場合は、
										別作業の子作業なので、スキップする
									*/
									continue;
								}
								if (sOperationCont[idxb].iOperation == 0 ||
									sOperationCont[idxb].iOperation == 1)
								{
									/**
										入換・増結の場合は、strEditData1(入換発時刻・増結時刻)を見る
									*/
									CdDedJikoku aJikoku(
										sOperationCont[idxb].strEditData1);
									if (!aJikoku.isNull())
									{
										JikokuNext = aJikoku;
										break;
									}
								}
								if (sOperationCont[idxb].iOperation == 0 ||
									sOperationCont[idxb].iOperation == 2)
								{
									/**
										入換・解結の場合は、strEditData2(入換着時刻・解結時刻)を見る
										入換発時刻が存在する場合は、breakでここには入らない。
										※原則として、入換発時刻無しの入換着時刻有状態はないが、一応
									*/
									CdDedJikoku aJikoku(
										sOperationCont[idxb].strEditData2);
									if (!aJikoku.isNull())
									{
										JikokuNext = aJikoku;
										break;
									}
								}
							}
							if (!JikokuNext.isNull())
							{
								CdDedJikoku aJikokuTemp;
								int iResult = getJikokuFromUI(
									sOprationSel.strEditData1,
									JikokuNext,
									&aJikokuTemp,
									true);
								if (iResult >= 0)
								{
									sOperationCont[pUiData->iListSelected].strEditData1 =
										g_CdDedJikokuConv.encode(aJikokuTemp);
								}
							}
							break;
						}
						else if (sOperationCont[idxp].iLevel == iLevelSearch &&
							idxp < pUiData->iListSelected)
						{
							//idxp(解結)が前にある→前方から補完、解結作業が上限
							CdDedJikoku JikokuPrev;
							for (int idxa = pUiData->iListSelected - 1;
								idxa >= idxp; idxa--)
							{
								if (sOperationCont[idxa].iLevel.size() > sOprationSel.iLevel.size())
								{
									/**
										探索箇所のiLevel要素数が、sOprationSelよりも多い場合は、
										別作業の子作業なので、スキップする
									*/
									continue;
								}
								if (sOperationCont[idxa].iOperation == 0 ||
									sOperationCont[idxa].iOperation == 2)
								{
									/**
										入換・解結の場合は、strEditData2(入換着時刻・解結時刻)を見る
									*/
									CdDedJikoku aJikoku(
										sOperationCont[idxa].strEditData2);
									if (!aJikoku.isNull())
									{
										JikokuPrev = aJikoku;
										break;
									}
								}
								if (sOperationCont[idxa].iOperation == 0 ||
									sOperationCont[idxa].iOperation == 1)
								{
									/**
										入換・増結の場合は、strEditData1(入換発時刻・増結時刻)を見る
										入換着時刻が存在する場合は、breakでここには入らない。
									*/
									CdDedJikoku aJikoku(
										sOperationCont[idxa].strEditData1);
									if (!aJikoku.isNull())
									{
										JikokuPrev = aJikoku;
										break;
									}
								}
							}
							if (!JikokuPrev.isNull())
							{
								CdDedJikoku aJikokuTemp;
								int iResult = getJikokuFromUI(
									sOprationSel.strEditData1,
									JikokuPrev,
									&aJikokuTemp,
									false);
								if (iResult >= 0)
								{
									sOperationCont[pUiData->iListSelected].strEditData1 =
										g_CdDedJikokuConv.encode(aJikokuTemp);
								}
							}
							break;
						}
					}
				}
				else if (aJikokuOpeChaku.isNull() && ((m_iHatsuEkiOrder >= 0 && pUiData->bSelectedAfter) ||
					(m_iChakuEkiOrder < 0 && !pUiData->bSelectedAfter)))
				{
					CdDedJikoku JikokuNext;
					if (m_iChakuEkiOrder < 0 && !pUiData->bSelectedAfter)
					{
						/**
							始発駅前作業の場合は、まず前作業を後方に見る。
							ただし路線外始発の場合は、当駅着時刻を最初に見る
						*/

						if (sOprationSel.iOperation == 4)//路線外始発
						{
							JikokuNext = CdDedJikoku(
								sOprationSel.strEditData2);
						}

						for (int idxb = pUiData->iListSelected + 1;
							idxb < (int)pUiData->sOperationB.size() && JikokuNext.isNull(); idxb++)
						{
							if (pUiData->sOperationB[idxb].iLevel.size() > 1)
							{
								continue;
							}
							if (pUiData->sOperationB[idxb].iOperation == 0 ||
								pUiData->sOperationB[idxb].iOperation == 1)
							{
								/**
									入換・増結の場合は、strEditData1(入換発時刻・増結時刻)を見る
								*/
								CdDedJikoku aJikoku(
									pUiData->sOperationB[idxb].strEditData1);
								if (!aJikoku.isNull())
								{
									JikokuNext = aJikoku;
									break;
								}
							}
							if (pUiData->sOperationB[idxb].iOperation == 0 ||
								pUiData->sOperationB[idxb].iOperation == 2)
							{
								/**
									入換・解結の場合は、strEditData2(入換着時刻・解結時刻)を見る
									入換発時刻が存在する場合は、breakでここには入らない。
									※原則として、入換発時刻無しの入換着時刻有状態はないが、一応
								*/
								CdDedJikoku aJikoku(
									pUiData->sOperationB[idxb].strEditData2);
								if (!aJikoku.isNull())
								{
									JikokuNext = aJikoku;
									break;
								}
							}
						}
					}
					int idxa = 0;
					if (m_iHatsuEkiOrder >= 0 && pUiData->bSelectedAfter)
					{
						/**
							後作業探索の初期位置。
							始発駅前作業なら0から、
							後作業なら、リスト選択位置の一つ下から
						*/
						idxa = pUiData->iListSelected + 1;
					}
					for (; idxa < (int)pUiData->sOperationA.size() && JikokuNext.isNull()
						; idxa++)
					{
						if (pUiData->sOperationA[idxa].iLevel.size() > 1)
						{
							continue;
						}
						if (pUiData->sOperationA[idxa].iOperation == 0 ||
							pUiData->sOperationA[idxa].iOperation == 1)
						{
							/**
								入換・増結の場合は、strEditData1(入換発時刻・増結時刻)を見る
							*/
							CdDedJikoku aJikoku(
								pUiData->sOperationA[idxa].strEditData1);
							if (!aJikoku.isNull())
							{
								JikokuNext = aJikoku;
								break;
							}

						}
						if (pUiData->sOperationA[idxa].iOperation == 0 ||
							pUiData->sOperationA[idxa].iOperation == 2)
						{
							/**
								入換・解結の場合は、strEditData2(入換着時刻・解結時刻)を見る
								入換発時刻が存在する場合は、breakでここには入らない。
								※原則として、入換発時刻無しの入換着時刻有状態はないが、一応
							*/
							CdDedJikoku aJikoku(
								pUiData->sOperationA[idxa].strEditData2);
							if (!aJikoku.isNull())
							{
								JikokuNext = aJikoku;
								break;
							}

						}
					}
					if (JikokuNext.isNull())
					{
						/**
							後作業をすべて見て、後の時刻が見つからなかったら、発時刻を見る
						*/
						JikokuNext = CdDedJikoku(pUiData->strHatsujikoku);
					}
					if (!JikokuNext.isNull())
					{
						CdDedJikoku aJikokuTemp;
						int iResult = getJikokuFromUI(
							sOprationSel.strEditData1,
							JikokuNext,
							&aJikokuTemp,
							true);
						if (iResult >= 0)
						{
							sOperationCont[pUiData->iListSelected].strEditData1 =
								g_CdDedJikokuConv.encode(aJikokuTemp);
						}
					}

				}
				else if (aJikokuOpeChaku.isNull())
				{
					CdDedJikoku JikokuPrev;
					if (m_iHatsuEkiOrder < 0 && pUiData->bSelectedAfter)
					{
						/**
							終着駅後作業の場合は、まず後作業を前方に見る。
						*/
						for (int idxa = pUiData->iListSelected - 1;
							idxa >= 0 && JikokuPrev.isNull(); idxa--)
						{
							if (pUiData->sOperationA[idxa].iLevel.size() > 1)
							{
								continue;
							}
							if (pUiData->sOperationA[idxa].iOperation == 0 ||
								pUiData->sOperationA[idxa].iOperation == 2)
							{
								/**
									入換・解結の場合は、strEditData2(入換着時刻・解結時刻)を見る
								*/
								CdDedJikoku aJikoku(
									pUiData->sOperationA[idxa].strEditData2);
								if (!aJikoku.isNull())
								{
									JikokuPrev = aJikoku;
									break;
								}
							}
							if (pUiData->sOperationA[idxa].iOperation == 0 ||
								pUiData->sOperationA[idxa].iOperation == 1)
							{
								/**
									入換・増結の場合は、strEditData1(入換発時刻・増結時刻)を見る
									入換着時刻が存在する場合は、breakでここには入らない。
								*/
								CdDedJikoku aJikoku(
									pUiData->sOperationA[idxa].strEditData1);
								if (!aJikoku.isNull())
								{
									JikokuPrev = aJikoku;
									break;
								}
							}
						}
					}
					int idxb = pUiData->sOperationB.size() - 1;
					if (m_iChakuEkiOrder >= 0 && !pUiData->bSelectedAfter)
					{
						/**
							前作業探索の初期位置。
							終着駅後作業ならリスト末尾から、
							前作業なら、リスト選択位置の一つ上から
						*/
						idxb = pUiData->iListSelected - 1;
					}
					for (; idxb >= 0 && JikokuPrev.isNull()
						; idxb--)
					{
						if (pUiData->sOperationB[idxb].iLevel.size() > 1)
						{
							continue;
						}
						if (pUiData->sOperationB[idxb].iOperation == 0 ||
							pUiData->sOperationB[idxb].iOperation == 2)
						{
							/**
								入換・解結の場合は、strEditData2(入換着時刻・解結時刻)を見る
							*/
							CdDedJikoku aJikoku(
								pUiData->sOperationB[idxb].strEditData2);
							if (!aJikoku.isNull())
							{
								JikokuPrev = aJikoku;
								break;
							}

						}
						if (pUiData->sOperationB[idxb].iOperation == 0 ||
							pUiData->sOperationB[idxb].iOperation == 1)
						{
							/**
								入換・増結の場合は、strEditData1(入換発時刻・増結時刻)を見る
								入換着時刻が存在する場合は、breakでここには入らない。
							*/
							CdDedJikoku aJikoku(
								pUiData->sOperationB[idxb].strEditData1);
							if (!aJikoku.isNull())
							{
								JikokuPrev = aJikoku;
								break;
							}

						}
					}
					if (JikokuPrev.isNull())
					{
						/**
							前作業をすべて見て、前の時刻が見つからなかったら、着時刻を見る
						*/
						JikokuPrev = CdDedJikoku(pUiData->strChakujikoku);
					}
					if (!JikokuPrev.isNull())
					{
						CdDedJikoku aJikokuTemp;
						int iResult = getJikokuFromUI(
							sOprationSel.strEditData1,
							JikokuPrev,
							&aJikokuTemp,
							false);
						if (iResult >= 0)
						{
							sOperationCont[pUiData->iListSelected].strEditData1 =
								g_CdDedJikokuConv.encode(aJikokuTemp);
						}
					}
				}
			}

			if (sOprationSel.iOperation == 0)
			{
				//	入換発時刻の前回値・現在値・入換発時刻の入力を取得
				CdDedJikoku	jikokuOperationHatsuPrev(sOprationSelPrev.strEditData1);
				CdDedJikoku	jikokuOperationHatsu(sOprationSel.strEditData1);
				CdDedJikoku jikokuOperationChaku(sOprationSel.strEditData2);
				if (!jikokuOperationHatsuPrev.isNull()
					&& !jikokuOperationHatsu.isNull()
					&& !jikokuOperationChaku.isNull())
				{
					jikokuOperationChaku.addSeconds(jikokuOperationHatsu.subJikoku(jikokuOperationHatsuPrev));
					sOperationCont[pUiData->iListSelected].strEditData2 = g_CdDedJikokuConv.encode(jikokuOperationChaku);
				}
			}
		}


		//--------------------------------------------------------------------------------
		//	strEditData2
		//--------------------------------------------------------------------------------
		if (bStartEdit || sOprationSelPrev.strEditData2 != sOprationSel.strEditData2)
		{
			if (sOprationSel.iOperation == 0 || sOprationSel.iOperation == 2 ||
				sOprationSel.iOperation == 4)
			{
				/**
					時刻の正規化
					(1)半角変換
					(2)時の補完
						時を補完するときは
						(a)始発駅前作業・終着駅を除く後作業・増結の前作業は後方から補完
						(b)終着駅後作業・始発駅を除く前作業・解結の後作業は前方から補完する
					なお、入換の場合は、最初に入換発時刻からの補完も行う
					路線外始発の場合は、始発駅発時刻からの補完は行わない
					路線外終着の場合は、当駅発時刻からの補完も行う
				*/
				CdDedJikoku aJikokuOpeHatsu;
				if (sOprationSel.iOperation == 0)
				{
					aJikokuOpeHatsu = CdDedJikoku(
						sOprationSel.strEditData1);
					if (!aJikokuOpeHatsu.isNull())
					{
						CdDedJikoku aJikokuTemp;
						int iResult = getJikokuFromUI(
							sOprationSel.strEditData2,
							aJikokuOpeHatsu,
							&aJikokuTemp,
							false);
						if (iResult >= 0)
						{
							sOperationCont[pUiData->iListSelected].strEditData2 =
								g_CdDedJikokuConv.encode(aJikokuTemp);
						}
					}
				}
				if (aJikokuOpeHatsu.isNull() && sOprationSel.iLevel.size() > 1)
				{

					/**
						iLevelが2要素以上ある場合は、子作業なので、前作業か後作業が調べる必要があります
					*/
					vector<int> iLevelSearch = sOprationSel.iLevel;
					iLevelSearch.pop_back();
					for (int idxp = 0; idxp < (int)sOperationCont.size(); idxp++)
					{
						if (sOperationCont[idxp].iLevel == iLevelSearch &&
							idxp > pUiData->iListSelected)
						{
							//idxp(増結)が後にある→後方から補完、増結作業が下限
							CdDedJikoku JikokuNext;
							for (int idxb = pUiData->iListSelected + 1;
								idxb <= idxp && JikokuNext.isNull(); idxb++)
							{
								if (sOperationCont[idxb].iLevel.size() > sOprationSel.iLevel.size())
								{
									/**
										探索箇所のiLevel要素数が、sOprationSelよりも多い場合は、
										別作業の子作業なので、スキップする
									*/
									continue;
								}
								if (sOperationCont[idxb].iOperation == 0 ||
									sOperationCont[idxb].iOperation == 1)
								{
									/**
										入換・増結の場合は、strEditData1(入換発時刻・増結時刻)を見る
									*/
									CdDedJikoku aJikoku(
										sOperationCont[idxb].strEditData1);
									if (!aJikoku.isNull())
									{
										JikokuNext = aJikoku;
										break;
									}
								}
								if (sOperationCont[idxb].iOperation == 0 ||
									sOperationCont[idxb].iOperation == 2)
								{
									/**
										入換・解結の場合は、strEditData2(入換着時刻・解結時刻)を見る
										入換発時刻が存在する場合は、breakでここには入らない。
										※原則として、入換発時刻無しの入換着時刻有状態はないが、一応
									*/
									CdDedJikoku aJikoku(
										sOperationCont[idxb].strEditData2);
									if (!aJikoku.isNull())
									{
										JikokuNext = aJikoku;
										break;
									}
								}
							}
							if (!JikokuNext.isNull())
							{
								CdDedJikoku aJikokuTemp;
								int iResult = getJikokuFromUI(
									sOprationSel.strEditData2,
									JikokuNext,
									&aJikokuTemp,
									true);
								if (iResult >= 0)
								{
									sOperationCont[pUiData->iListSelected].strEditData2 =
										g_CdDedJikokuConv.encode(aJikokuTemp);
								}
							}
							break;
						}
						else if (sOperationCont[idxp].iLevel == iLevelSearch &&
							idxp < pUiData->iListSelected)
						{
							//idxp(解結)が前にある→前方から補完、解結作業が上限
							CdDedJikoku JikokuPrev;

							if (sOprationSel.iOperation == 4)//路線外終着
							{
								JikokuPrev = CdDedJikoku(
									sOprationSel.strEditData1);
							}

							for (int idxa = pUiData->iListSelected - 1;
								idxa >= idxp && JikokuPrev.isNull(); idxa--)
							{
								if (sOperationCont[idxa].iLevel.size() > sOprationSel.iLevel.size())
								{
									/**
										探索箇所のiLevel要素数が、sOprationSelよりも多い場合は、
										別作業の子作業なので、スキップする
									*/
									continue;
								}
								if (sOperationCont[idxa].iOperation == 0 ||
									sOperationCont[idxa].iOperation == 2)
								{
									/**
										入換・解結の場合は、strEditData2(入換着時刻・解結時刻)を見る
									*/
									CdDedJikoku aJikoku(
										sOperationCont[idxa].strEditData2);
									if (!aJikoku.isNull())
									{
										JikokuPrev = aJikoku;
										break;
									}
								}
								if (sOperationCont[idxa].iOperation == 0 ||
									sOperationCont[idxa].iOperation == 1)
								{
									/**
										入換・増結の場合は、strEditData1(入換発時刻・増結時刻)を見る
										入換着時刻が存在する場合は、breakでここには入らない。
									*/
									CdDedJikoku aJikoku(
										sOperationCont[idxa].strEditData1);
									if (!aJikoku.isNull())
									{
										JikokuPrev = aJikoku;
										break;
									}
								}
							}
							if (!JikokuPrev.isNull())
							{
								CdDedJikoku aJikokuTemp;
								int iResult = getJikokuFromUI(
									sOprationSel.strEditData2,
									JikokuPrev,
									&aJikokuTemp,
									false);
								if (iResult >= 0)
								{
									sOperationCont[pUiData->iListSelected].strEditData2 =
										g_CdDedJikokuConv.encode(aJikokuTemp);
								}
							}
							break;
						}
					}
				}
				else if (aJikokuOpeHatsu.isNull() && ((m_iHatsuEkiOrder >= 0 && pUiData->bSelectedAfter) ||
					(m_iChakuEkiOrder < 0 && !pUiData->bSelectedAfter)))
				{
					CdDedJikoku JikokuNext;
					if (m_iChakuEkiOrder < 0 && !pUiData->bSelectedAfter)
					{
						/**
							始発駅前作業の場合は、まず前作業を後方に見る。
						*/
						for (int idxb = pUiData->iListSelected + 1;
							idxb < (int)pUiData->sOperationB.size(); idxb++)
						{
							if (pUiData->sOperationB[idxb].iLevel.size() > 1)
							{
								continue;
							}
							if (pUiData->sOperationB[idxb].iOperation == 0 ||
								pUiData->sOperationB[idxb].iOperation == 1)
							{
								/**
									入換・増結の場合は、strEditData1(入換発時刻・増結時刻)を見る
								*/
								CdDedJikoku aJikoku(
									pUiData->sOperationB[idxb].strEditData1);
								if (!aJikoku.isNull())
								{
									JikokuNext = aJikoku;
									break;
								}
							}
							if (pUiData->sOperationB[idxb].iOperation == 0 ||
								pUiData->sOperationB[idxb].iOperation == 2)
							{
								/**
									入換・解結の場合は、strEditData2(入換着時刻・解結時刻)を見る
									入換発時刻が存在する場合は、breakでここには入らない。
									※原則として、入換発時刻無しの入換着時刻有状態はないが、一応
								*/
								CdDedJikoku aJikoku(
									pUiData->sOperationB[idxb].strEditData2);
								if (!aJikoku.isNull())
								{
									JikokuNext = aJikoku;
									break;
								}
							}
						}
					}
					int idxa = 0;
					if (m_iHatsuEkiOrder >= 0 && pUiData->bSelectedAfter)
					{
						/**
							後作業探索の初期位置。
							始発駅前作業なら0から、
							後作業なら、リスト選択位置の一つ下から
						*/
						idxa = pUiData->iListSelected + 1;
					}
					for (; idxa < (int)pUiData->sOperationA.size() && JikokuNext.isNull()
						; idxa++)
					{
						if (pUiData->sOperationA[idxa].iLevel.size() > 1)
						{
							continue;
						}
						if (pUiData->sOperationA[idxa].iOperation == 0 ||
							pUiData->sOperationA[idxa].iOperation == 1)
						{
							/**
								入換・増結の場合は、strEditData1(入換発時刻・増結時刻)を見る
							*/
							CdDedJikoku aJikoku(
								pUiData->sOperationA[idxa].strEditData1);
							if (!aJikoku.isNull())
							{
								JikokuNext = aJikoku;
								break;
							}

						}
						if (pUiData->sOperationA[idxa].iOperation == 0 ||
							pUiData->sOperationA[idxa].iOperation == 2)
						{
							/**
								入換・解結の場合は、strEditData2(入換着時刻・解結時刻)を見る
								入換発時刻が存在する場合は、breakでここには入らない。
								※原則として、入換発時刻無しの入換着時刻有状態はないが、一応
							*/
							CdDedJikoku aJikoku(
								pUiData->sOperationA[idxa].strEditData2);
							if (!aJikoku.isNull())
							{
								JikokuNext = aJikoku;
								break;
							}

						}
					}
					if (JikokuNext.isNull())
					{
						/**
							後作業をすべて見て、後の時刻が見つからなかったら、発時刻を見る
						*/
						JikokuNext = CdDedJikoku(pUiData->strHatsujikoku);
					}
					if (!JikokuNext.isNull())
					{
						CdDedJikoku aJikokuTemp;
						int iResult = getJikokuFromUI(
							sOprationSel.strEditData2,
							JikokuNext,
							&aJikokuTemp,
							true);
						if (iResult >= 0)
						{
							sOperationCont[pUiData->iListSelected].strEditData2 =
								g_CdDedJikokuConv.encode(aJikokuTemp);
						}
					}

				}
				else if (aJikokuOpeHatsu.isNull())
				{
					CdDedJikoku JikokuPrev;
					if (m_iHatsuEkiOrder < 0 && pUiData->bSelectedAfter)
					{
						/**
							終着駅後作業の場合は、まず後作業を前方に見る。
							ただし、路線外終着の場合は、当駅発時刻を最初に見る
						*/
						if (sOprationSel.iOperation == 4)//路線外終着
						{
							JikokuPrev = CdDedJikoku(
								sOprationSel.strEditData1);
						}
						for (int idxa = pUiData->iListSelected - 1;
							idxa >= 0 && JikokuPrev.isNull(); idxa--)
						{
							if (pUiData->sOperationA[idxa].iLevel.size() > 1)
							{
								continue;
							}
							if (pUiData->sOperationA[idxa].iOperation == 0 ||
								pUiData->sOperationA[idxa].iOperation == 2)
							{
								/**
									入換・解結の場合は、strEditData2(入換着時刻・解結時刻)を見る
								*/
								CdDedJikoku aJikoku(
									pUiData->sOperationA[idxa].strEditData2);
								if (!aJikoku.isNull())
								{
									JikokuPrev = aJikoku;
									break;
								}
							}
							if (pUiData->sOperationA[idxa].iOperation == 0 ||
								pUiData->sOperationA[idxa].iOperation == 1)
							{
								/**
									入換・増結の場合は、strEditData1(入換発時刻・増結時刻)を見る
									入換着時刻が存在する場合は、breakでここには入らない。
								*/
								CdDedJikoku aJikoku(
									pUiData->sOperationA[idxa].strEditData1);
								if (!aJikoku.isNull())
								{
									JikokuPrev = aJikoku;
									break;
								}
							}
						}
					}
					int idxb = pUiData->sOperationB.size() - 1;
					if (m_iChakuEkiOrder >= 0 && !pUiData->bSelectedAfter)
					{
						/**
							前作業探索の初期位置。
							終着駅後作業ならリスト末尾から、
							前作業なら、リスト選択位置の一つ上から
						*/
						idxb = pUiData->iListSelected - 1;
					}
					for (;idxb >= 0 && JikokuPrev.isNull()
						; idxb--)
					{
						if (pUiData->sOperationB[idxb].iLevel.size() > 1)
						{
							continue;
						}
						if (pUiData->sOperationB[idxb].iOperation == 0 ||
							pUiData->sOperationB[idxb].iOperation == 2)
						{
							/**
								入換・解結の場合は、strEditData2(入換着時刻・解結時刻)を見る
							*/
							CdDedJikoku aJikoku(
								pUiData->sOperationB[idxb].strEditData2);
							if (!aJikoku.isNull())
							{
								JikokuPrev = aJikoku;
								break;
							}

						}
						if (pUiData->sOperationB[idxb].iOperation == 0 ||
							pUiData->sOperationB[idxb].iOperation == 1)
						{
							/**
								入換・増結の場合は、strEditData1(入換発時刻・増結時刻)を見る
								入換着時刻が存在する場合は、breakでここには入らない。
							*/
							CdDedJikoku aJikoku(
								pUiData->sOperationB[idxb].strEditData1);
							if (!aJikoku.isNull())
							{
								JikokuPrev = aJikoku;
								break;
							}

						}
					}
					if (JikokuPrev.isNull())
					{
						/**
							前作業をすべて見て、前の時刻が見つからなかったら、着時刻を見る
						*/
						JikokuPrev = CdDedJikoku(pUiData->strChakujikoku);
					}
					if (!JikokuPrev.isNull())
					{
						CdDedJikoku aJikokuTemp;
						int iResult = getJikokuFromUI(
							sOprationSel.strEditData2,
							JikokuPrev,
							&aJikokuTemp,
							false);
						if (iResult >= 0)
						{
							sOperationCont[pUiData->iListSelected].strEditData2 =
								g_CdDedJikokuConv.encode(aJikokuTemp);
						}
					}
				}
			}
		}

		if (pUiData->bSelectedAfter)
		{
			pUiData->sOperationA = sOperationCont;
		}
		else
		{
			pUiData->sOperationB = sOperationCont;
		}
	}
	if (pUiData->iUiOperation == 2 &&
		pUiData->iListSelected >= 0)
	{
		vector<Operation> sOperationCont;
		if (pUiData->bSelectedAfter)
		{
			sOperationCont = pUiData->sOperationA;
		}
		else
		{
			sOperationCont = pUiData->sOperationB;
		}

		if (sOperationCont[pUiData->iListSelected].iOperation == 0)
		{
			if (pUiData->bSelectedAfter)
			{
				sOperationCont[pUiData->iListSelected].iComboData1 = m_iStandardShuntTrackIndex[1];
			}
			else
			{
				sOperationCont[pUiData->iListSelected].iComboData1 = m_iStandardShuntTrackIndex[0];
			}
		}

		if (pUiData->bSelectedAfter)
		{
			pUiData->sOperationA = sOperationCont;
		}
		else
		{
			pUiData->sOperationB = sOperationCont;
		}
	}
}

int CPropEditUI_Operation::CheckBeforeOperation(
	const vector<Operation>& sOperationB,
	const vector<int> iLevelSearch,
	int& iListErrorPos,
	vector<int>& iLevelErrorPos)
{
	int iRv = 0;
	/**
		まずは、時刻範囲の合致および時刻と識別できない文字列をチェック、
		その後、空白時刻の補完を行う。**空白時刻の補完は、UiDataToTargetで行う。
	*/

		for (int idx = 0; idx < (int)sOperationB.size() && iRv >= 0; idx++)
		{

			const Operation& pOperation = sOperationB[idx];
			/**
				チェック対象となるのは
				(1)iLevelの上位「iLevelSearch.size()」桁が、iLevelSearch.size()と一致する
				(2)iLevel.size()がiLevelSearch.size()+1と等しい
				(例1)iLevelSearchが空の場合は、iLevel.size()が1の物全てが対象になる。
				(例2)iLevelSearchが(1,2)の場合は、iLevelが(1.2.0)や(1.2.2)が対象となり、
					(1.1.0)や(1.2.1.0)は対象にならない
			*/

			if (pOperation.iLevel.size() != iLevelSearch.size() + 1)
			{
				continue;
			}
			bool bMatchiLevel = true;
			for (int idxl = 0; idxl < (int)iLevelSearch.size() && bMatchiLevel; idxl++)
			{
				if (pOperation.iLevel[idxl] != iLevelSearch[idxl])
				{
					bMatchiLevel = false;
				}
			}
			if (!bMatchiLevel)
			{
				continue;
			}

			if (pOperation.iOperation == 0)
			{
				/**
					入換の場合
						入換発時刻・入換着時刻が不正でないかを調べる
				*/
				if (iRv >= 0)
				{
					CdDedJikoku aJikoku;
					int iResult = aJikoku.decode(pOperation.strEditData1);
					if (iResult < 0)
					{
						iListErrorPos = idx;
						iLevelErrorPos = pOperation.iLevel;
						iRv = -201;
					}
				}

				if (iRv >= 0)
				{
					CdDedJikoku aJikoku;
					int iResult = aJikoku.decode(pOperation.strEditData2);
					if (iResult < 0)
					{
						iListErrorPos = idx;
						iLevelErrorPos = pOperation.iLevel;
						iRv = -202;
					}
				}
			}
			else if (pOperation.iOperation == 1)
			{
				/**
					増結の場合
						増結時刻が不正でないかを調べる

					増結編成の前作業のチェックを行う。
				*/
				if (iRv >= 0)
				{
					CdDedJikoku aJikoku;
					int iResult = aJikoku.decode(pOperation.strEditData1);
					if (iResult < 0)
					{
						iListErrorPos = idx;
						iLevelErrorPos = pOperation.iLevel;
						iRv = -211;
					}
				}
				if (iRv >= 0)
				{
					iRv = CheckBeforeOperation(
						sOperationB,
						pOperation.iLevel,
						iListErrorPos,
						iLevelErrorPos);
				}
			}
			else if (pOperation.iOperation == 2)
			{
				/**
					解結の場合
						解結時刻が不正でないかを調べる
						解結位置Indexが数字であるかどうか、1-10の範囲に収まっているかを調べる

					解結時刻が空の場合、pJikokuBackを仮解結時刻とみなし、
					解結編成の後作業のチェックを行う。
				*/
				if (iRv >= 0)
				{
					CdDedJikoku aJikoku;
					int iResult = aJikoku.decode(pOperation.strEditData2);
					if (iResult < 0)
					{
						iListErrorPos = idx;
						iLevelErrorPos = pOperation.iLevel;
						iRv = -221;
					}
				}

				if (iRv >= 0 && !pOperation.strEditData1.empty())
				{
					try
					{
						int iResult = stoi(pOperation.strEditData1);

						if (iResult < 1 || iResult>10)
						{
							iListErrorPos = idx;
							iLevelErrorPos = pOperation.iLevel;
							iRv = -225;
						}
					}
					catch (std::invalid_argument e)
					{
						iListErrorPos = idx;
						iLevelErrorPos = pOperation.iLevel;
						iRv = -223;
					}
					catch (std::out_of_range e)
					{
						iListErrorPos = idx;
						iLevelErrorPos = pOperation.iLevel;
						iRv = -224;
					}

				}

				if (iRv >= 0)
				{
					iRv = CheckAfterOperation(
						sOperationB,
						pOperation.iLevel,
						iListErrorPos,
						iLevelErrorPos);
				}
			}
			else if (pOperation.iOperation == 3)
			{
				/**
					出区の場合
						出区時刻が不正でないかを調べる
						運用番号内に','が含まれていないかどうかを調べる
						入出区連携コード内に','、'/'、'$'が含まれていないかどうかを調べる
				*/
				if (iRv >= 0)
				{
					CdDedJikoku aJikoku;
					int iResult = aJikoku.decode(pOperation.strEditData1);
					if (iResult < 0)
					{
						iListErrorPos = idx;
						iLevelErrorPos = pOperation.iLevel;
						iRv = -231;
					}
				}

				if (iRv >= 0 && !pOperation.strOperationNumber.empty())
				{
					for (int idxon = 0; idxon < (int)pOperation.strOperationNumber.size(); idxon++)
					{
						if (pOperation.strOperationNumber[idxon].find(',') != tstring::npos)
						{
							iListErrorPos = idx;
							iLevelErrorPos = pOperation.iLevel;
							iRv = -235;
							break;
						}
					}

				}

				if (iRv >= 0 && pOperation.strInOutLinkCode.find(',') != tstring::npos)
				{
					iListErrorPos = idx;
					iLevelErrorPos = pOperation.iLevel;
					iRv = -236;
					break;
				}

				if (iRv >= 0 && pOperation.strInOutLinkCode.find('/') != tstring::npos)
				{
					iListErrorPos = idx;
					iLevelErrorPos = pOperation.iLevel;
					iRv = -237;
					break;
				}

				if (iRv >= 0 && pOperation.strInOutLinkCode.find('$') != tstring::npos)
				{
					iListErrorPos = idx;
					iLevelErrorPos = pOperation.iLevel;
					iRv = -238;
					break;
				}
			}
			else if (pOperation.iOperation == 4)
			{
				/**
					路線外始発の場合
						路線外始発駅発時刻・当駅着時刻が不正でないかを調べる
						路線外始発駅発時刻は、空の場合でもエラーにする
						運用番号内に','が含まれていないかどうかを調べる
						入出区連携コード内に','、'/'、'$'が含まれていないかどうかを調べる
				*/
				if (iRv >= 0)
				{
					CdDedJikoku aJikoku;
					int iResult = aJikoku.decode(pOperation.strEditData1);
					if (iResult < 0)
					{
						iListErrorPos = idx;
						iLevelErrorPos = pOperation.iLevel;
						iRv = -241;
					}
				}

				if (iRv >= 0)
				{
					CdDedJikoku aJikoku;
					int iResult = aJikoku.decode(pOperation.strEditData2);
					if (iResult < 0)
					{
						iListErrorPos = idx;
						iLevelErrorPos = pOperation.iLevel;
						iRv = -242;
					}
				}

				if (iRv >= 0 && pOperation.strEditData1.empty())
				{
					iListErrorPos = idx;
					iLevelErrorPos = pOperation.iLevel;
					iRv = -244;
				}

				if (iRv >= 0 && !pOperation.strOperationNumber.empty())
				{
					for (int idxon = 0; idxon < (int)pOperation.strOperationNumber.size(); idxon++)
					{
						if (pOperation.strOperationNumber[idxon].find(',') != tstring::npos)
						{
							iListErrorPos = idx;
							iLevelErrorPos = pOperation.iLevel;
							iRv = -235;
							break;
						}
					}
				}

				if (iRv >= 0 && pOperation.strInOutLinkCode.find(',') != tstring::npos)
				{
					iListErrorPos = idx;
					iLevelErrorPos = pOperation.iLevel;
					iRv = -236;
					break;
				}

				if (iRv >= 0 && pOperation.strInOutLinkCode.find('/') != tstring::npos)
				{
					iListErrorPos = idx;
					iLevelErrorPos = pOperation.iLevel;
					iRv = -237;
					break;
				}

				if (iRv >= 0 && pOperation.strInOutLinkCode.find('$') != tstring::npos)
				{
					iListErrorPos = idx;
					iLevelErrorPos = pOperation.iLevel;
					iRv = -238;
					break;
				}
			}
			else if (pOperation.iOperation == 5)
			{
				/**
					前列車接続の場合
						起点時刻が不正でないかを調べる
						運用番号内に','が含まれていないかどうかを調べる
				*/
				if (iRv >= 0)
				{
					CdDedJikoku aJikoku;
					int iResult = aJikoku.decode(pOperation.strEditData1);
					if (iResult < 0)
					{
						iListErrorPos = idx;
						iLevelErrorPos = pOperation.iLevel;
						iRv = -251;
					}
				}
				if (iRv >= 0 && !pOperation.strOperationNumber.empty())
				{
					for (int idxon = 0; idxon < (int)pOperation.strOperationNumber.size(); idxon++)
					{
						if (pOperation.strOperationNumber[idxon].find(',') != tstring::npos)
						{
							iListErrorPos = idx;
							iLevelErrorPos = pOperation.iLevel;
							iRv = -235;
							break;
						}
					}

				}
			}
			else if (pOperation.iOperation == 6)
			{
				/**
					運用番号変更の場合
						運用番号順反転が無効の場合、運用番号が空白かどうかを調べる
						運用番号内に','が含まれていないかどうかを調べる
				*/
				if (iRv >= 0)
				{
					if (!pOperation.bCheckData1 &&
						pOperation.strOperationNumber.empty())
					{
						iListErrorPos = idx;
						iLevelErrorPos = pOperation.iLevel;
						iRv = -261;
					}
				}
				if (iRv >= 0 && !pOperation.strOperationNumber.empty())
				{
					for (int idxon = 0; idxon < (int)pOperation.strOperationNumber.size(); idxon++)
					{
						if (pOperation.strOperationNumber[idxon].find(',') != tstring::npos)
						{
							iListErrorPos = idx;
							iLevelErrorPos = pOperation.iLevel;
							iRv = -235;
							break;
						}
					}

				}
			}
		}
	return iRv;
}

int CPropEditUI_Operation::CheckAfterOperation(
	const vector<Operation>& sOperationA,
	const vector<int> iLevelSearch,
	int& iListErrorPos,
	vector<int>& iLevelErrorPos)
{
	int iRv = 0;
	/**
		まずは、時刻範囲の合致および時刻と識別できない文字列をチェック、
		その後、空白時刻の補完を行う。**空白時刻の補完は、UiDataToTargetで行う。
	*/
	for (int idx = 0; idx < (int)sOperationA.size() && iRv >= 0; idx++)
	{

		const Operation& pOperation = sOperationA[idx];
		/**
			チェック対象となるのは
			(1)iLevelの上位「iLevelSearch.size()」桁が、iLevelSearch.size()と一致する
			(2)iLevel.size()がiLevelSearch.size()+1と等しい
			(例1)iLevelSearchが空の場合は、iLevel.size()が1の物全てが対象になる。
			(例2)iLevelSearchが(1,2)の場合は、iLevelが(1.2.0)や(1.2.2)が対象となり、
				(1.1.0)や(1.2.1.0)は対象にならない
		*/
		if (pOperation.iLevel.size() != iLevelSearch.size() + 1)
		{
			continue;
		}
		bool bMatchiLevel = true;
		for (int idxl = 0; idxl < (int)iLevelSearch.size() && bMatchiLevel; idxl++)
		{
			if (pOperation.iLevel[idxl] != iLevelSearch[idxl])
			{
				bMatchiLevel = false;
			}
		}
		if (!bMatchiLevel)
		{
			continue;
		}

		if (pOperation.iOperation == 0)
		{
			/**
				入換の場合
					入換発時刻・入換着時刻が不正でないかを調べる
			*/
			if (iRv >= 0)
			{
				CdDedJikoku aJikoku;
				int iResult = aJikoku.decode(pOperation.strEditData1);
				if (iResult < 0)
				{
					iListErrorPos = idx;
					iLevelErrorPos = pOperation.iLevel;
					iRv = -301;
				}
			}

			if (iRv >= 0)
			{
				CdDedJikoku aJikoku;
				int iResult = aJikoku.decode(pOperation.strEditData2);
				if (iResult < 0)
				{
					iListErrorPos = idx;
					iLevelErrorPos = pOperation.iLevel;
					iRv = -302;
				}
			}
		}
		else if (pOperation.iOperation == 1)
		{
			/**
				増結の場合
					増結時刻が不正でないかを調べる

				増結時刻が空の場合、pJikokuFrontを仮増結時刻とみなし、
				増結編成の前作業のチェックを行う。
			*/
			if (iRv >= 0)
			{
				CdDedJikoku aJikoku;
				int iResult = aJikoku.decode(pOperation.strEditData1);
				if (iResult < 0)
				{
					iListErrorPos = idx;
					iLevelErrorPos = pOperation.iLevel;
					iRv = -311;
				}
			}


			if (iRv >= 0)
			{
				iRv = CheckBeforeOperation(
					sOperationA,
					pOperation.iLevel,
					iListErrorPos,
					iLevelErrorPos);
			}

		}
		else if (pOperation.iOperation == 2)
		{
			/**
				解結の場合
					解結時刻が不正でないかを調べる
					解結位置Indexが数字であるかどうか、1-10の範囲に収まっているかを調べる

				解結時刻が空の場合、pJikokuFrontを仮解結時刻とみなし、
				解結編成の後作業のチェックを行う。
			*/
			if (iRv >= 0)
			{
				CdDedJikoku aJikoku;
				int iResult = aJikoku.decode(pOperation.strEditData2);
				if (iResult < 0)
				{
					iListErrorPos = idx;
					iLevelErrorPos = pOperation.iLevel;
					iRv = -321;
				}
			}

			if (iRv >= 0 && !pOperation.strEditData1.empty())
			{
				try
				{
					int iResult = stoi(pOperation.strEditData1);

					if (iResult < 1 || iResult>10)
					{
						iListErrorPos = idx;
						iLevelErrorPos = pOperation.iLevel;
						iRv = -325;
					}
				}
				catch (std::invalid_argument e)
				{
					iListErrorPos = idx;
					iLevelErrorPos = pOperation.iLevel;
					iRv = -323;
				}
				catch (std::out_of_range e)
				{
					iListErrorPos = idx;
					iLevelErrorPos = pOperation.iLevel;
					iRv = -324;
				}

			}

			if (iRv >= 0)
			{
				iRv = CheckAfterOperation(
					sOperationA,
					pOperation.iLevel,
					iListErrorPos,
					iLevelErrorPos);
			}
		}
		else if (pOperation.iOperation == 3)
		{
			/**
				入区の場合
					入区時刻が不正でないかを調べる
					入出区連携コード内に','、'/'、'$'が含まれていないかどうかを調べる
			*/
			if (iRv >= 0)
			{
				CdDedJikoku aJikoku;
				int iResult = aJikoku.decode(pOperation.strEditData1);
				if (iResult < 0)
				{
					iListErrorPos = idx;
					iLevelErrorPos = pOperation.iLevel;
					iRv = -333;
				}
			}

			if (iRv >= 0 && pOperation.strInOutLinkCode.find(',') != tstring::npos)
			{
				iListErrorPos = idx;
				iLevelErrorPos = pOperation.iLevel;
				iRv = -336;
				break;
			}

			if (iRv >= 0 && pOperation.strInOutLinkCode.find('/') != tstring::npos)
			{
				iListErrorPos = idx;
				iLevelErrorPos = pOperation.iLevel;
				iRv = -337;
				break;
			}

			if (iRv >= 0 && pOperation.strInOutLinkCode.find('$') != tstring::npos)
			{
				iListErrorPos = idx;
				iLevelErrorPos = pOperation.iLevel;
				iRv = -338;
				break;
			}
		}
		else if (pOperation.iOperation == 4)
		{
			/**
				路線外終着の場合
					当駅発時刻・路線外終着駅着時刻が不正でないかを調べる
					路線外終着駅着時刻は、範囲チェックの対象にはしない。
					路線外終着駅着時刻は、空の場合でもエラーにする
					入出区連携コード内に','、'/'、'$'が含まれていないかどうかを調べる
			*/
			if (iRv >= 0)
			{
				CdDedJikoku aJikoku;
				int iResult = aJikoku.decode(pOperation.strEditData1);
				if (iResult < 0)
				{
					iListErrorPos = idx;
					iLevelErrorPos = pOperation.iLevel;
					iRv = -345;
				}
			}

			if (iRv >= 0)
			{
				CdDedJikoku aJikoku;
				int iResult = aJikoku.decode(pOperation.strEditData2);
				if (iResult < 0)
				{
					iListErrorPos = idx;
					iLevelErrorPos = pOperation.iLevel;
					iRv = -346;
				}
			}

			if (iRv >= 0 && pOperation.strEditData2.empty())
			{
				iListErrorPos = idx;
				iLevelErrorPos = pOperation.iLevel;
				iRv = -348;
			}

			if (iRv >= 0 && pOperation.strInOutLinkCode.find(',') != tstring::npos)
			{
				iListErrorPos = idx;
				iLevelErrorPos = pOperation.iLevel;
				iRv = -336;
				break;
			}

			if (iRv >= 0 && pOperation.strInOutLinkCode.find('/') != tstring::npos)
			{
				iListErrorPos = idx;
				iLevelErrorPos = pOperation.iLevel;
				iRv = -337;
				break;
			}

			if (iRv >= 0 && pOperation.strInOutLinkCode.find('$') != tstring::npos)
			{
				iListErrorPos = idx;
				iLevelErrorPos = pOperation.iLevel;
				iRv = -338;
				break;
			}
		}
		else if (pOperation.iOperation == 5)
		{
			/**
				次列車接続の場合
					終点時刻が不正でないかを調べる
			*/
			if (iRv >= 0)
			{
				CdDedJikoku aJikoku;
				int iResult = aJikoku.decode(pOperation.strEditData1);
				if (iResult < 0)
				{
					iListErrorPos = idx;
					iLevelErrorPos = pOperation.iLevel;
					iRv = -352;
				}
			}
		}
		else if (pOperation.iOperation == 6)
		{
			/**
				運用番号変更の場合
					運用番号順反転が無効の場合、運用番号が空白かどうかを調べる
					運用番号内に','が含まれていないかどうかを調べる
			*/
			if (iRv >= 0)
			{
				if (!pOperation.bCheckData1 &&
					pOperation.strOperationNumber.empty())
				{
					iListErrorPos = idx;
					iLevelErrorPos = pOperation.iLevel;
					iRv = -361;
				}
			}
			if (iRv >= 0 && !pOperation.strOperationNumber.empty())
			{
				for (int idxon = 0; idxon < (int)pOperation.strOperationNumber.size(); idxon++)
				{
					if (pOperation.strOperationNumber[idxon].find(',') != tstring::npos)
					{
						iListErrorPos = idx;
						iLevelErrorPos = pOperation.iLevel;
						iRv = -335;
						break;
					}
				}
			}
		}
	}
	return iRv;
}

int CPropEditUI_Operation::CheckUiData( 
		bool bNewItem , 
		const UIDATA* pUiData , 
		const UIDATA* pUiDataStartEdit ) 
{
	int iRv = 0 ; 

	/**
		時刻のチェック
			編集対象が中間駅の場合は、着時刻→発時刻内に全ての時刻が収まっていなければならない
				なお、探索順序は、前作業→後作業の順になるので、
				後作業の範囲は、前作業の最終時刻→発時刻になる。
			始発駅の場合は、発時刻から前24時間以内に全ての時刻が収まっていなければならない
				なお、探索順序は、後作業→前作業の順になるので、
				前作業の範囲は、後作業の発時刻の24時間前→最初の時刻になる。
			終着駅の場合は、着時刻から後24時間以内に全ての時刻が収まっていなければならない
				なお、探索順序は、前作業→後作業の順になるので、
				後作業の範囲は、前作業の最終時刻→着時刻の24時間後になる。

		※時刻の順序チェックは不要にし、不正形式の検出のみ行う。
	*/
	vector<int> iLevelErrorPos;
	int iListErrorPos = -1;
	bool bErrorIsAfter;

	if (iRv >= 0)
	{
		bErrorIsAfter = false;
		iRv = CheckBeforeOperation(
			pUiData->sOperationB,
			vector<int>(),
			iListErrorPos,
			iLevelErrorPos);
	}

	if (iRv >= 0)
	{
		bErrorIsAfter = true;
		iRv = CheckAfterOperation(
			pUiData->sOperationA,
			vector<int>(),
			iListErrorPos,
			iLevelErrorPos);
	}
	//// --------------------------------
	////	エラーメッセージを表示します
	//// --------------------------------
	if ( iRv < 0 )
	{
		tstring strInfo;
		if (bErrorIsAfter)
		{
			strInfo = _T("(後作業");
		}
		else
		{
			strInfo = _T("(前作業");
		}

		vector<tstring> strLevel;
		for (int idx = 0; idx < (int)iLevelErrorPos.size(); idx++)
		{
			strLevel.push_back(to_tstring(iLevelErrorPos[idx]));
		}
		strInfo += joinc('.', strLevel);
		strInfo += _T(")");

		switch( iRv )
		{
		case -101:
		case -201:
		case -301:
		case -401:
			ShowError(ERRMSG_INVALID_SHUNTHATSUJIKOKU,
				strInfo);
			SetFocus(offsetof(Operation, strEditData1));
			//SetFocus2(offsetof(Operation, strEditData1),
			//	iListErrorPos,
			//	bErrorIsAfter);
			break;
		case -102:
		case -202:
		case -302:
		case -402:
			ShowError(ERRMSG_INVALID_SHUNTCHAKUJIKOKU,
				strInfo);
			SetFocus(offsetof(Operation, strEditData2));
			//SetFocus2(offsetof(Operation, strEditData2),
			//	iListErrorPos,
			//	bErrorIsAfter);
			break;
		//case -103:
		//case -203:
		//case -303:
		//case -403:
		//	ShowError(ERRMSG_OUTOFRANGE_SHUNTHATSUJIKOKU);
		//	SetFocus2(offsetof(Operation, strEditData1),
		//		iListErrorPos,
		//		bErrorIsAfter);
		//	break;
		//case -104:
		//case -204:
		//case -304:
		//case -404:
		//	ShowError(ERRMSG_OUTOFRANGE_SHUNTCHAKUJIKOKU);
		//	SetFocus2(offsetof(Operation, strEditData2),
		//		iListErrorPos,
		//		bErrorIsAfter);
		//	break;

		case -111:
		case -211:
		case -311:
		case -411:
			ShowError(ERRMSG_INVALID_CONNECTJIKOKU,
				strInfo);
			SetFocus(offsetof(Operation, strEditData1));
			//SetFocus2(offsetof(Operation, strEditData1),
			//	iListErrorPos,
			//	bErrorIsAfter);
			break;
		//case -112:
		//case -212:
		//case -312:
		//case -412:
		//	ShowError(ERRMSG_OUTOFRANGE_CONNECTJIKOKU);
		//	SetFocus2(offsetof(Operation, strEditData1),
		//		iListErrorPos,
		//		bErrorIsAfter);
		//	break;

		case -121:
		case -221:
		case -321:
		case -421:
			ShowError(ERRMSG_INVALID_RELEASEJIKOKU,
				strInfo);
			SetFocus(offsetof(Operation, strEditData2));
			//SetFocus2(offsetof(Operation, strEditData2),
			//	iListErrorPos,
			//	bErrorIsAfter);
			break;
		//case -122:
		//case -222:
		//case -322:
		//case -422:
		//	ShowError(ERRMSG_OUTOFRANGE_RELEASEJIKOKU);
		//	SetFocus2(offsetof(Operation, strEditData2),
		//		iListErrorPos,
		//		bErrorIsAfter);
		//	break;

		case -123:
		case -223:
		case -323:
		case -423:
			ShowError(ERRMSG_INVALID_RELEASEINDEX,
				strInfo);
			SetFocus(offsetof(Operation, strEditData1));
			//SetFocus2(offsetof(Operation, strEditData1),
			//	iListErrorPos,
			//	bErrorIsAfter);
			break;
		case -124:
		case -224:
		case -324:
		case -424:
		case -125:
		case -225:
		case -325:
		case -425:
			ShowError(ERRMSG_OUTOFRANGE_RELEASEINDEX,
				strInfo);
			SetFocus(offsetof(Operation, strEditData1));
			//SetFocus2(offsetof(Operation, strEditData1),
			//	iListErrorPos,
			//	bErrorIsAfter);
			break;

		case -131:
		case -231:
		case -331:
		case -431:
			ShowError(ERRMSG_INVALID_OUTJIKOKU,
				strInfo);
			SetFocus(offsetof(Operation, strEditData1));
			//SetFocus2(offsetof(Operation, strEditData1),
			//	iListErrorPos,
			//	bErrorIsAfter);
			break;
		//case -132:
		//case -232:
		//case -332:
		//case -432:
		//	ShowError(ERRMSG_OUTOFRANGE_OUTJIKOKU);
		//	SetFocus2(offsetof(Operation, strEditData1),
		//		iListErrorPos,
		//		bErrorIsAfter);
		//	break;
		case -133:
		case -233:
		case -333:
		case -433:
			ShowError(ERRMSG_INVALID_INJIKOKU,
				strInfo);
			SetFocus(offsetof(Operation, strEditData1));
			//SetFocus2(offsetof(Operation, strEditData1),
			//	iListErrorPos,
			//	bErrorIsAfter);
			break;
		//case -134:
		//case -234:
		//case -334:
		//case -434:
		//	ShowError(ERRMSG_OUTOFRANGE_INJIKOKU);
		//	SetFocus2(offsetof(Operation, strEditData1),
		//		iListErrorPos,
		//		bErrorIsAfter);
		//	break;
		case -235:
		case -335:
			ShowError(ERRMSG_UNUSABLE_COMMA);
			SetFocus(offsetof(Operation, strOperationNumber));
			break;
		case -236:
		case -336:
			ShowError(ERRMSG_UNUSABLE_COMMA_INOUTLINKCODE);
			SetFocus(offsetof(Operation, strInOutLinkCode));
			break;
		case -237:
		case -337:
			ShowError(ERRMSG_UNUSABLE_SLASH);
			SetFocus(offsetof(Operation, strInOutLinkCode));
			break;
		case -238:
		case -338:
			ShowError(ERRMSG_UNUSABLE_DOLLAR);
			SetFocus(offsetof(Operation, strInOutLinkCode));
			break;

		case -141:
		case -241:
		case -341:
		case -441:
			ShowError(ERRMSG_INVALID_OUTERHATSUJIKOKU,
				strInfo);
			SetFocus(offsetof(Operation, strEditData1));
			//SetFocus2(offsetof(Operation, strEditData1),
			//	iListErrorPos,
			//	bErrorIsAfter);
			break;
		case -142:
		case -242:
		case -342:
		case -442:
			ShowError(ERRMSG_INVALID_CHAKUJIKOKU,
				strInfo);
			SetFocus(offsetof(Operation, strEditData2));
			//SetFocus2(offsetof(Operation, strEditData2),
			//	iListErrorPos,
			//	bErrorIsAfter);
			break;
		//case -143:
		//case -243:
		//case -343:
		//case -443:
		//	ShowError(ERRMSG_OUTOFRANGE_CHAKUJIKOKU);
		//	SetFocus2(offsetof(Operation, strEditData2),
		//		iListErrorPos,
		//		bErrorIsAfter);
		//	break;
		case -144:
		case -244:
		case -344:
		case -444:
			ShowError(ERRMSG_EMPTY_OUTERHATSUJIKOKU,
				strInfo);
			SetFocus(offsetof(Operation, strEditData1));
			//SetFocus2(offsetof(Operation, strEditData1),
			//	iListErrorPos,
			//	bErrorIsAfter);
			break;
		case -145:
		case -245:
		case -345:
		case -445:
			ShowError(ERRMSG_INVALID_HATSUJIKOKU,
				strInfo);
			SetFocus(offsetof(Operation, strEditData1));
			//SetFocus2(offsetof(Operation, strEditData1),
			//	iListErrorPos,
			//	bErrorIsAfter);
			break;
		case -146:
		case -246:
		case -346:
		case -446:
			ShowError(ERRMSG_INVALID_OUTERCHAKUJIKOKU,
				strInfo);
			SetFocus(offsetof(Operation, strEditData2));
			//SetFocus2(offsetof(Operation, strEditData2),
			//	iListErrorPos,
			//	bErrorIsAfter);
			break;
		//case -147:
		//case -247:
		//case -347:
		//case -447:
		//	ShowError(ERRMSG_OUTOFRANGE_HATSUJIKOKU);
		//	SetFocus2(offsetof(Operation, strEditData1),
		//		iListErrorPos,
		//		bErrorIsAfter);
		//	break;
		case -148:
		case -248:
		case -348:
		case -448:
			ShowError(ERRMSG_EMPTY_OUTERCHAKUJIKOKU,
				strInfo);
			SetFocus(offsetof(Operation, strEditData2));
			//SetFocus2(offsetof(Operation, strEditData2),
			//	iListErrorPos,
			//	bErrorIsAfter);
			break;
		case -251:
			ShowError(ERRMSG_INVALID_ORIGINJIKOKU,
				strInfo);
			SetFocus(offsetof(Operation, strEditData1));
			break;
		case -352:
			ShowError(ERRMSG_INVALID_TERMINALJIKOKU,
				strInfo);
			SetFocus(offsetof(Operation, strEditData1));
			break;
		//case -161:
		case -261:
		case -361:
		//case -461:
			ShowError(ERRMSG_EMPTY_OPERATIONNUMBER,
				strInfo);
			SetFocus(offsetof(Operation, strOperationNumber));
		}
	}
	return iRv ;
}

void CPropEditUI_Operation::BeforeOperationComplement(
	vector<Operation>& sOperationB,
	const vector<int> iLevelTarget,
	CdDedJikoku& pSourceJikoku,
	const bool bSupplyFromFront,
	const bool bIsTeisya)
{
	CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);

	if (bSupplyFromFront)
	{
		for (int idx = 0; idx < (int)sOperationB.size(); idx++)
		{
			Operation& pOperation = sOperationB[idx];
			/**
				チェック対象となるのは
				(1)iLevelの上位「iLevelSearch.size()」桁が、iLevelSearch.size()と一致する
				(2)iLevel.size()がiLevelSearch.size()+1と等しい
				(例1)iLevelSearchが空の場合は、iLevel.size()が1の物全てが対象になる。
				(例2)iLevelSearchが(1,2)の場合は、iLevelが(1.2.0)や(1.2.2)が対象となり、
					(1.1.0)や(1.2.1.0)は対象にならない
			*/

			if (pOperation.iLevel.size() != iLevelTarget.size() + 1)
			{
				continue;
			}
			bool bMatchiLevel = true;
			for (int idxl = 0; idxl < (int)iLevelTarget.size() && bMatchiLevel; idxl++)
			{
				if (pOperation.iLevel[idxl] != iLevelTarget[idxl])
				{
					bMatchiLevel = false;
				}
			}
			if (!bMatchiLevel)
			{
				continue;
			}

			if (pOperation.iOperation == 0)
			{
				/**
					入換の場合
						入換発時刻が空の場合は、pSourceJikokuに1分を加えたもので補完する
						ただし、入換着時刻が空でない場合は、入換着時刻で補完する
						空でない場合は、基準時刻を更新する。
						入換着時刻は空でもよいので、基準時刻の更新のみ行う
				*/
				if (pOperation.strEditData1.empty())
				{
					if (pOperation.strEditData2.empty())
					{
						pSourceJikoku.addSeconds(+60);
						pOperation.strEditData1 = aJikokuConv.encode(pSourceJikoku);
					}
					else
					{
						pOperation.strEditData1 = pOperation.strEditData2;
					}
				}
				else
				{
					pSourceJikoku.decode(pOperation.strEditData1);
				}

				if (!pOperation.strEditData2.empty())
				{
					pSourceJikoku.decode(pOperation.strEditData2);
				}


			}
			else if (pOperation.iOperation == 1)
			{
				/**
					増結の場合
						増結時刻が空の場合は、pSourceJikokuで補完する

					増結編成の前作業のチェックを行う。
				*/
				if (pOperation.strEditData1.empty())
				{
					pOperation.strEditData1 = aJikokuConv.encode(pSourceJikoku);
				}
				else
				{
					pSourceJikoku.decode(pOperation.strEditData1);
				}
				CdDedJikoku aConnectJikoku(pOperation.strEditData1);
				BeforeOperationComplement(
					sOperationB,
					pOperation.iLevel,
					aConnectJikoku,
					false,
					bIsTeisya);
			}
			else if (pOperation.iOperation == 2)
			{
				/**
					解結の場合
						解結時刻が空の場合は、pSourceJikokuで補完する
						解結位置Indexが空の場合は、1を入れる

					解結編成の後作業のチェックを行う。
				*/
				if (pOperation.strEditData2.empty())
				{
					pOperation.strEditData2 = aJikokuConv.encode(pSourceJikoku);
				}
				else
				{
					pSourceJikoku.decode(pOperation.strEditData2);
				}
				if (pOperation.strEditData1.empty())
				{
					pOperation.strEditData1 = _T("1");
				}
				CdDedJikoku aReleaseJikoku(pOperation.strEditData2);
				AfterOperationComplement(
					sOperationB,
					pOperation.iLevel,
					aReleaseJikoku,
					true,
					bIsTeisya);
			}
		}
	}
	else
	{
		for (int idx = sOperationB.size() - 1; idx >= 0; idx--)
		{
			Operation& pOperation = sOperationB[idx];
			/**
				チェック対象となるのは
				(1)iLevelの上位「iLevelSearch.size()」桁が、iLevelSearch.size()と一致する
				(2)iLevel.size()がiLevelSearch.size()+1と等しい
				(例1)iLevelSearchが空の場合は、iLevel.size()が1の物全てが対象になる。
				(例2)iLevelSearchが(1,2)の場合は、iLevelが(1.2.0)や(1.2.2)が対象となり、
					(1.1.0)や(1.2.1.0)は対象にならない
			*/

			if (pOperation.iLevel.size() != iLevelTarget.size() + 1)
			{
				continue;
			}
			bool bMatchiLevel = true;
			for (int idxl = 0; idxl < (int)iLevelTarget.size() && bMatchiLevel; idxl++)
			{
				if (pOperation.iLevel[idxl] != iLevelTarget[idxl])
				{
					bMatchiLevel = false;
				}
			}
			if (!bMatchiLevel)
			{
				continue;
			}

			if (pOperation.iOperation == 0)
			{
				/**
					入換の場合
						入換発時刻が空の場合は、pSourceJikokuから1分を減算したもので補完する。
						ただし、入換着時刻が空でない場合は、入換着時刻で補完する
						空でない場合は、基準時刻を更新する。
						入換着時刻は空でもよいので、基準時刻の更新のみ行う
				*/
				if (pOperation.strEditData1.empty())
				{
					if (pOperation.strEditData2.empty())
					{
						pSourceJikoku.addSeconds(-60);
						pOperation.strEditData1 = aJikokuConv.encode(pSourceJikoku);
					}
					else
					{
						pOperation.strEditData1 = pOperation.strEditData2;
					}
				}
				else
				{
					pSourceJikoku.decode(pOperation.strEditData1);
				}

			}
			else if (pOperation.iOperation == 1)
			{
				/**
					増結の場合
						増結時刻が空の場合は、pSourceJikokuで補完する

					増結編成の前作業のチェックを行う。
				*/
				if (pOperation.strEditData1.empty())
				{
					pOperation.strEditData1 = aJikokuConv.encode(pSourceJikoku);
				}
				else
				{
					pSourceJikoku.decode(pOperation.strEditData1);
				}
				CdDedJikoku aConnectJikoku(pOperation.strEditData1);
				BeforeOperationComplement(
					sOperationB,
					pOperation.iLevel,
					aConnectJikoku,
					false,
					bIsTeisya);
			}
			else if (pOperation.iOperation == 2)
			{
				/**
					解結の場合
						解結時刻が空の場合は、pSourceJikokuで補完する
						解結位置Indexが空の場合は、1を入れる

					解結編成の後作業のチェックを行う。
				*/
				if (pOperation.strEditData2.empty())
				{
					pOperation.strEditData2 = aJikokuConv.encode(pSourceJikoku);
				}
				else
				{
					pSourceJikoku.decode(pOperation.strEditData2);
				}
				if (pOperation.strEditData1.empty())
				{
					pOperation.strEditData1 = _T("1");
				}
				CdDedJikoku aReleaseJikoku(pOperation.strEditData2);
				AfterOperationComplement(
					sOperationB,
					pOperation.iLevel,
					aReleaseJikoku,
					true,
					bIsTeisya);
			}
			else if (pOperation.iOperation == 3)
			{
				/**
					出区の場合
						出区時刻が空の場合は、pSourceJikokuから1分を減算したもので補完する
				*/
				if (pOperation.strEditData1.empty())
				{
					pSourceJikoku.addSeconds(-60);
					pOperation.strEditData1 = aJikokuConv.encode(pSourceJikoku);
				}
			}
			//19.11.26 路線外始発において、当駅着時刻は空でもよいことにする
			//19.12.22 通過の場合のみ、当駅着時刻を空のままにするように変更
			else if (pOperation.iOperation == 4 &&
				bIsTeisya)
			{
				/**
					路線外始発の場合
						路線外始発駅発時刻が空の場合はエラーなので、ここではチェックしない。
						当駅着時刻が空の場合は、pSourceJikokuから1分を減算したもので補完する
				*/
				if (pOperation.strEditData2.empty())
				{
					pSourceJikoku.addSeconds(-60);
					pOperation.strEditData2 = aJikokuConv.encode(pSourceJikoku);
				}
			}
		}
	}
}

void CPropEditUI_Operation::BeforeOperationToTarget(
	CentDedBeforeOperationCont * pCentDedBeforeOperationCont,
	const vector<Operation> sOperationB/*,
	const vector<int> iLevelTarget,
	CdDedJikoku& pSourceJikoku,
	const bool bSupplyFromFront*/)
{
	int iSetInsertCount = 0;
	for (int idx = 0; idx < (int)sOperationB.size(); idx++)
	{
		Operation sOperationTemp = sOperationB[idx];
		CentDedBeforeOperation aBeforeOperation;
		if (sOperationTemp.iLevel.size() > 1)
		{
			/**
				iLevel.size() > 1に該当する作業は、
				pCentDedBeforOperationeContに格納する作業の子作業にあたるため、
				スキップする。
			*/
			continue;
		}
		else if (sOperationTemp.iOperation == 0)//入換
		{
			aBeforeOperation =
				CentDedBeforeOperation(
					CentDedBeforeOperation::EBOperation::BOperation_Shunt,
					sOperationTemp.iComboData1,
					CdDedJikoku(sOperationTemp.strEditData1),
					CdDedJikoku(sOperationTemp.strEditData2),
					sOperationTemp.bCheckData1);
		}
		else if (sOperationTemp.iOperation == 1)//増結
		{
			aBeforeOperation =
				CentDedBeforeOperation(
					CentDedBeforeOperation::EBOperation::BOperation_Connect,
					sOperationTemp.iComboData1,
					CdDedJikoku(sOperationTemp.strEditData1));
			/**
				この作業の子作業を求める
				sOperationBTempはこの作業の子作業となるOperation配列となる。
				もとのsOperationBから、
				(1)iLevel[0]がこの作業と一致するもの　かつ
				(2)この作業自身以外(indexが一致しない)
				を抜き出したもの。その時、iLevel[0]は削除しておく
			*/
			vector<Operation> sOperationBTemp;
			for (int idxb = 0; idxb < (int)sOperationB.size(); idxb++)
			{
				Operation sOperationTemp2 = sOperationB[idxb];
				if (sOperationTemp2.iLevel.front() == sOperationTemp.iLevel.front()
					&& idx != idxb)
				{
					sOperationTemp2.iLevel.erase(sOperationTemp2.iLevel.begin());
					sOperationBTemp.push_back(sOperationTemp2);
				}
			}
			BeforeOperationToTarget(
				aBeforeOperation.getCentDedBeforeOperationCont(),
				sOperationBTemp);
		}
		else if (sOperationTemp.iOperation == 2)//解結
		{
			aBeforeOperation =
				CentDedBeforeOperation(
					CentDedBeforeOperation::EBOperation::BOperation_Release,
					sOperationTemp.iComboData1,
					stoi(sOperationTemp.strEditData1),
					CdDedJikoku(sOperationTemp.strEditData2));
			/**
				この作業の子作業を求める
				sOperationATempはこの作業の子作業となるOperation配列となる。
				もとのsOperationBから、
				(1)pCentDedBeforeOperationContに入る作業＝iLevel.size()=1のもの
				(2)pCentDedBeforeOperationContに入る他の作業の子作業となるもの
					＝iLevel[0]の値が、この作業と異なるもの
				を取り除いたもの。その時、iLevel[0]は削除しておく
			*/
			vector<Operation> sOperationATemp;
			for (int idxa = 0; idxa < (int)sOperationB.size(); idxa++)
			{
				Operation sOperationTemp2 = sOperationB[idxa];
				if (sOperationTemp2.iLevel.front() == sOperationTemp.iLevel.front()
					&& idx != idxa)
				{
					sOperationTemp2.iLevel.erase(sOperationTemp2.iLevel.begin());
					sOperationATemp.push_back(sOperationTemp2);
				}
			}
			AfterOperationToTarget(
				aBeforeOperation.getCentDedAfterOperationCont(),
				sOperationATemp);
		}
		else if (sOperationTemp.iOperation == 3)//出区
		{
			aBeforeOperation =
				CentDedBeforeOperation(
					CentDedBeforeOperation::EBOperation::BOperation_Out,
					CdDedJikoku(sOperationTemp.strEditData1),
					sOperationTemp.strOperationNumber,
					sOperationTemp.strInOutLinkCode);
		}
		else if (sOperationTemp.iOperation == 4)//路線外始発
		{
			aBeforeOperation =
				CentDedBeforeOperation(
					CentDedBeforeOperation::EBOperation::BOperation_Outer,
					sOperationTemp.iComboData1,
					CdDedJikoku(sOperationTemp.strEditData1),
					CdDedJikoku(sOperationTemp.strEditData2),
					sOperationTemp.strOperationNumber,
					sOperationTemp.strInOutLinkCode);
		}
		else if (sOperationTemp.iOperation == 5)//前列車接続
		{
			aBeforeOperation =
				CentDedBeforeOperation(
					CentDedBeforeOperation::EBOperation::BOperation_Junction,
					CdDedJikoku(sOperationTemp.strEditData1),
					sOperationTemp.strOperationNumber);
		}
		else if (sOperationTemp.iOperation == 6)//運用番号変更
		{
			//Ver2.06.05 運用番号順反転設定を追加、運用番号順反転設定が有効な場合は、運用番号は空にする。
			if (sOperationTemp.bCheckData1)
			{
				aBeforeOperation =
					CentDedBeforeOperation(
						CentDedBeforeOperation::EBOperation::BOperation_NumberChange,
						vector<tstring>(),
						true);
			}
			else
			{
				aBeforeOperation =
					CentDedBeforeOperation(
						CentDedBeforeOperation::EBOperation::BOperation_NumberChange,
						sOperationTemp.strOperationNumber,
						false);
			}
		}
		else//(作業を追加)
		{
			continue;
		}

		if (sOperationTemp.iLevel.front() < pCentDedBeforeOperationCont->size())
		{
			pCentDedBeforeOperationCont->set(aBeforeOperation, sOperationTemp.iLevel.front());
		}
		else
		{
			pCentDedBeforeOperationCont->insert(aBeforeOperation);
		}
		iSetInsertCount++;
	}

	if (iSetInsertCount < pCentDedBeforeOperationCont->size())
	{
		pCentDedBeforeOperationCont->erase(iSetInsertCount, INT_MAX);
	}

}
void CPropEditUI_Operation::AfterOperationComplement(
	vector<Operation>& sOperationA,
	const vector<int> iLevelTarget,
	CdDedJikoku & pSourceJikoku,
	const bool bSupplyFromFront,
	const bool bIsTeisya)
{
	CdDedJikoku::CConv	aJikokuConv(g_CdDedJikokuConv);

	if (bSupplyFromFront)
	{
		for (int idx = 0; idx < (int)sOperationA.size(); idx++)
		{
			Operation& pOperation = sOperationA[idx];
			/**
				チェック対象となるのは
				(1)iLevelの上位「iLevelSearch.size()」桁が、iLevelSearch.size()と一致する
				(2)iLevel.size()がiLevelSearch.size()+1と等しい
				(例1)iLevelSearchが空の場合は、iLevel.size()が1の物全てが対象になる。
				(例2)iLevelSearchが(1,2)の場合は、iLevelが(1.2.0)や(1.2.2)が対象となり、
					(1.1.0)や(1.2.1.0)は対象にならない
			*/

			if (pOperation.iLevel.size() != iLevelTarget.size() + 1)
			{
				continue;
			}
			bool bMatchiLevel = true;
			for (int idxl = 0; idxl < (int)iLevelTarget.size() && bMatchiLevel; idxl++)
			{
				if (pOperation.iLevel[idxl] != iLevelTarget[idxl])
				{
					bMatchiLevel = false;
				}
			}
			if (!bMatchiLevel)
			{
				continue;
			}

			if (pOperation.iOperation == 0)
			{
				/**
					入換の場合
						入換発時刻が空の場合は、pSourceJikokuに1分を加えたもので補完する
						ただし、入換着時刻が空でない場合は、入換着時刻で補完する
						空でない場合は、基準時刻を更新する。
						入換着時刻は空でもよいので、基準時刻の更新のみ行う
				*/
				if (pOperation.strEditData1.empty())
				{
					if (pOperation.strEditData2.empty())
					{
						pSourceJikoku.addSeconds(+60);
						pOperation.strEditData1 = aJikokuConv.encode(pSourceJikoku);
					}
					else
					{
						pOperation.strEditData1 = pOperation.strEditData2;
					}
				}
				else
				{
					pSourceJikoku.decode(pOperation.strEditData1);
				}

				if (!pOperation.strEditData2.empty())
				{
					pSourceJikoku.decode(pOperation.strEditData2);
				}


			}
			else if (pOperation.iOperation == 1)
			{
				/**
					増結の場合
						増結時刻が空の場合は、pSourceJikokuで補完する

					増結編成の前作業のチェックを行う。
				*/
				if (pOperation.strEditData1.empty())
				{
					pOperation.strEditData1 = aJikokuConv.encode(pSourceJikoku);
				}
				else
				{
					pSourceJikoku.decode(pOperation.strEditData1);
				}
				CdDedJikoku aConnectJikoku(pOperation.strEditData1);
				BeforeOperationComplement(
					sOperationA,
					pOperation.iLevel,
					aConnectJikoku,
					false,
					bIsTeisya);
			}
			else if (pOperation.iOperation == 2)
			{
				/**
					解結の場合
						解結時刻が空の場合は、pSourceJikokuで補完する
						解結位置Indexが空の場合は、1を入れる

					解結編成の後作業のチェックを行う。
				*/
				if (pOperation.strEditData2.empty())
				{
					pOperation.strEditData2 = aJikokuConv.encode(pSourceJikoku);
				}
				else
				{
					pSourceJikoku.decode(pOperation.strEditData2);
				}
				if (pOperation.strEditData1.empty())
				{
					pOperation.strEditData1 = _T("1");
				}
				CdDedJikoku aReleaseJikoku(pOperation.strEditData2);
				AfterOperationComplement(
					sOperationA,
					pOperation.iLevel,
					aReleaseJikoku,
					true,
					bIsTeisya);
			}
			else if (pOperation.iOperation == 3)
			{
				/**
					入区の場合
						入区時刻が空の場合は、pSourceJikokuに1分を加えたもので補完する
				*/
				if (pOperation.strEditData1.empty())
				{
					pSourceJikoku.addSeconds(+60);
					pOperation.strEditData1 = aJikokuConv.encode(pSourceJikoku);
				}
			}
			//19.11.26 路線外終着において、当駅発時刻は空でもよいことにする
			//19.12.22 通過の場合のみ、当駅着時刻を空のままにするように変更
			else if (pOperation.iOperation == 4 &&
				bIsTeisya)
			{
				/**
					路線外終着の場合
						路線外終着駅着時刻が空の場合はエラーなので、ここではチェックしない。
						当駅発時刻が空の場合は、pSourceJikokuに1分を加えたもので補完する
				*/
				if (pOperation.strEditData1.empty())
				{
					pSourceJikoku.addSeconds(+60);
					pOperation.strEditData1 = aJikokuConv.encode(pSourceJikoku);
				}
			}
		}
	}
	else
	{
		for (int idx = sOperationA.size() - 1; idx >= 0; idx--)
		{
			Operation& pOperation = sOperationA[idx];
			/**
				チェック対象となるのは
				(1)iLevelの上位「iLevelSearch.size()」桁が、iLevelSearch.size()と一致する
				(2)iLevel.size()がiLevelSearch.size()+1と等しい
				(例1)iLevelSearchが空の場合は、iLevel.size()が1の物全てが対象になる。
				(例2)iLevelSearchが(1,2)の場合は、iLevelが(1.2.0)や(1.2.2)が対象となり、
					(1.1.0)や(1.2.1.0)は対象にならない
			*/

			if (pOperation.iLevel.size() != iLevelTarget.size() + 1)
			{
				continue;
			}
			bool bMatchiLevel = true;
			for (int idxl = 0; idxl < (int)iLevelTarget.size() && bMatchiLevel; idxl++)
			{
				if (pOperation.iLevel[idxl] != iLevelTarget[idxl])
				{
					bMatchiLevel = false;
				}
			}
			if (!bMatchiLevel)
			{
				continue;
			}

			if (pOperation.iOperation == 0)
			{
				/**
					入換の場合
						入換発時刻が空の場合は、pSourceJikokuから1分を減算したもので補完する。
						ただし、入換着時刻が空でない場合は、入換着時刻で補完する
						空でない場合は、基準時刻を更新する。
						入換着時刻は空でもよいので、基準時刻の更新のみ行う
				*/
				if (pOperation.strEditData1.empty())
				{
					if (pOperation.strEditData2.empty())
					{
						pSourceJikoku.addSeconds(-60);
						pOperation.strEditData1 = aJikokuConv.encode(pSourceJikoku);
					}
					else
					{
						pOperation.strEditData1 = pOperation.strEditData2;
					}
				}
				else
				{
					pSourceJikoku.decode(pOperation.strEditData1);
				}

			}
			else if (pOperation.iOperation == 1)
			{
				/**
					増結の場合
						増結時刻が空の場合は、pSourceJikokuで補完する

					増結編成の前作業のチェックを行う。
				*/
				if (pOperation.strEditData1.empty())
				{
					pOperation.strEditData1 = aJikokuConv.encode(pSourceJikoku);
				}
				else
				{
					pSourceJikoku.decode(pOperation.strEditData1);
				}
				CdDedJikoku aConnectJikoku(pOperation.strEditData1);
				BeforeOperationComplement(
					sOperationA,
					pOperation.iLevel,
					aConnectJikoku,
					false,
					bIsTeisya);
			}
			else if (pOperation.iOperation == 2)
			{
				/**
					解結の場合
						解結時刻が空の場合は、pSourceJikokuで補完する
						解結位置Indexが空の場合は、1を入れる

					解結編成の後作業のチェックを行う。
				*/
				if (pOperation.strEditData2.empty())
				{
					pOperation.strEditData2 = aJikokuConv.encode(pSourceJikoku);
				}
				else
				{
					pSourceJikoku.decode(pOperation.strEditData2);
				}
				if (pOperation.strEditData1.empty())
				{
					pOperation.strEditData1 = _T("1");
				}
				CdDedJikoku aReleaseJikoku(pOperation.strEditData2);
				AfterOperationComplement(
					sOperationA,
					pOperation.iLevel,
					aReleaseJikoku,
					true,
					bIsTeisya);
			}
		}
	}
}
void CPropEditUI_Operation::AfterOperationToTarget(
	CentDedAfterOperationCont * pCentDedAfterOperationCont,
	const vector<Operation> sOperationA/*,
	CdDedJikoku& pSourceJikoku,
	const bool bSupplyFromFront*/)
{
	int iSetInsertCount = 0;
	for (int idx = 0; idx < (int)sOperationA.size(); idx++)
	{
		Operation sOperationTemp = sOperationA[idx];
		CentDedAfterOperation aAfterOperation;
		if (sOperationTemp.iLevel.size() > 1)
		{
			/**
				iLevel.size() > 1に該当する作業は、
				pCentDedOperationAfterContに格納する作業の子作業にあたるため、
				スキップする。
			*/
			continue;
		}
		else if (sOperationTemp.iOperation == 0)//入換
		{
			aAfterOperation =
				CentDedAfterOperation(
					CentDedAfterOperation::EAOperation::AOperation_Shunt,
					sOperationTemp.iComboData1,
					CdDedJikoku(sOperationTemp.strEditData1),
					CdDedJikoku(sOperationTemp.strEditData2),
					sOperationTemp.bCheckData1);
		}
		else if (sOperationTemp.iOperation == 1)//増結
		{
			aAfterOperation =
				CentDedAfterOperation(
					CentDedAfterOperation::EAOperation::AOperation_Connect,
					sOperationTemp.iComboData1,
					CdDedJikoku(sOperationTemp.strEditData1));
			/**
				この作業の子作業を求める
				sOperationBTempはこの作業の子作業となるOperation配列となる。
				もとのsOperationAから、
				(1)iLevel[0]がこの作業と一致するもの　かつ
				(2)この作業自身以外(indexが一致しない)
				を抜き出したもの。その時、iLevel[0]は削除しておく
			*/
			vector<Operation> sOperationBTemp;
			for (int idxb = 0; idxb < (int)sOperationA.size(); idxb++)
			{
				Operation sOperationTemp2 = sOperationA[idxb];
				if (sOperationTemp2.iLevel.front() == sOperationTemp.iLevel.front()
					&& idx != idxb)
				{
					sOperationTemp2.iLevel.erase(sOperationTemp2.iLevel.begin());
					sOperationBTemp.push_back(sOperationTemp2);
				}
			}
			BeforeOperationToTarget(
				aAfterOperation.getCentDedBeforeOperationCont(),
				sOperationBTemp);
		}
		else if (sOperationTemp.iOperation == 2)//解結
		{
			aAfterOperation =
				CentDedAfterOperation(
					CentDedAfterOperation::EAOperation::AOperation_Release,
					sOperationTemp.iComboData1,
					stoi(sOperationTemp.strEditData1),
					CdDedJikoku(sOperationTemp.strEditData2));
			/**
				この作業の子作業を求める
				sOperationATempはこの作業の子作業となるOperation配列となる。
				もとのsOperationBから、
				(1)pCentDedBeforeOperationContに入る作業＝iLevel.size()=1のもの
				(2)pCentDedBeforeOperationContに入る他の作業の子作業となるもの
					＝iLevel[0]の値が、この作業と異なるもの
				を取り除いたもの。その時、iLevel[0]は削除しておく
			*/
			vector<Operation> sOperationATemp;
			for (int idxa = 0; idxa < (int)sOperationA.size(); idxa++)
			{
				Operation sOperationTemp2 = sOperationA[idxa];
				if (sOperationTemp2.iLevel.front() == sOperationTemp.iLevel.front()
					&& idx != idxa)
				{
					sOperationTemp2.iLevel.erase(sOperationTemp2.iLevel.begin());
					sOperationATemp.push_back(sOperationTemp2);
				}
			}
			AfterOperationToTarget(
				aAfterOperation.getCentDedAfterOperationCont(),
				sOperationATemp);
		}
		else if (sOperationTemp.iOperation == 3)//入区
		{
			aAfterOperation =
				CentDedAfterOperation(
					CentDedAfterOperation::EAOperation::AOperation_In,
					CdDedJikoku(sOperationTemp.strEditData1),
					sOperationTemp.strInOutLinkCode);
		}
		else if (sOperationTemp.iOperation == 4)//路線外終着
		{
			aAfterOperation =
				CentDedAfterOperation(
					CentDedAfterOperation::EAOperation::AOperation_Outer,
					sOperationTemp.iComboData1,
					CdDedJikoku(sOperationTemp.strEditData1),
					CdDedJikoku(sOperationTemp.strEditData2),
					sOperationTemp.strInOutLinkCode);
		}
		else if (sOperationTemp.iOperation == 5)//次列車接続
		{
			aAfterOperation =
				CentDedAfterOperation(
					CentDedAfterOperation::EAOperation::AOperation_Junction,
					CdDedJikoku(sOperationTemp.strEditData1),
					sOperationTemp.iComboData1);
		}
		else if (sOperationTemp.iOperation == 6)//運用番号変更
		{
			//Ver2.06.05 運用番号順反転設定を追加、運用番号順反転設定が有効な場合は、運用番号は空にする。
			if (sOperationTemp.bCheckData1)
			{
				aAfterOperation =
					CentDedAfterOperation(
						CentDedAfterOperation::EAOperation::AOperation_NumberChange,
						vector<tstring>(),
						true);
			}
			else
			{
				aAfterOperation =
					CentDedAfterOperation(
						CentDedAfterOperation::EAOperation::AOperation_NumberChange,
						sOperationTemp.strOperationNumber,
						false);
			}
		}
		else//(作業を追加)
		{
			continue;
		}

		if (sOperationTemp.iLevel.front() < pCentDedAfterOperationCont->size())
		{
			pCentDedAfterOperationCont->set(aAfterOperation, sOperationTemp.iLevel.front());
		}
		else
		{
			pCentDedAfterOperationCont->insert(aAfterOperation);
		}
		iSetInsertCount++;
	}

	if (iSetInsertCount < pCentDedAfterOperationCont->size())
	{
		pCentDedAfterOperationCont->erase(iSetInsertCount, INT_MAX);
	}
}

int CPropEditUI_Operation::UiDataToTarget( 
		bool bNewItem , 
		const UIDATA* pUiData , 
		const UIDATA* pUiDataStartEdit ) 
{

	int iRv = 0 ; 
	CentDedRessya* pRessya = m_pTarget->get( 0 ) ; 

	int iChakuEkiOrder = m_iChakuEkiOrder;
	if (iChakuEkiOrder == -1)
	{
		iChakuEkiOrder = m_iHatsuEkiOrder;
	}
	int iHatsuEkiOrder = m_iHatsuEkiOrder;
	if (iHatsuEkiOrder == -1)
	{
		iHatsuEkiOrder = m_iChakuEkiOrder;
	}

	bool bIsTeisya = pRessya->getCentDedEkiJikokuCont()
		->getMuPtr()->get(iChakuEkiOrder)->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya;

	vector<Operation> sOperationB = pUiData->sOperationB;
	vector<Operation> sOperationA = pUiData->sOperationA;
	if (m_iChakuEkiOrder == -1)//当駅始発
	{

		/**
			後作業 時刻補完
		*/
		CdDedJikoku aHatsuJikoku(pUiData->strHatsujikoku);

		AfterOperationComplement(
			sOperationA,
			vector<int>(),
			aHatsuJikoku,
			false,
			bIsTeisya);

		/**
			前作業 時刻補完 後方から行い、時刻は後作業を引き継ぐ
		*/
		BeforeOperationComplement(
			sOperationB,
			vector<int>(),
			aHatsuJikoku,
			false,
			bIsTeisya);
	}
	else if (m_iHatsuEkiOrder == -1)//当駅止まり
	{
		/**
			前作業 時刻補完
		*/
		CdDedJikoku aChakuJikoku(pUiData->strChakujikoku);

		BeforeOperationComplement(
			sOperationB,
			vector<int>(),
			aChakuJikoku,
			true,
			bIsTeisya);

		/**
			後作業 時刻補完 前方から行い、時刻は前作業を引き継ぐ
		*/
		AfterOperationComplement(
			sOperationA,
			vector<int>(),
			aChakuJikoku,
			true,
			bIsTeisya);

	}
	else
	{
		/**
			前作業 時刻補完
		*/
		CdDedJikoku aChakuJikoku(pUiData->strChakujikoku);

		BeforeOperationComplement(
			sOperationB,
			vector<int>(),
			aChakuJikoku,
			true,
			bIsTeisya);

		/**
			後作業 時刻補完
		*/
		CdDedJikoku aHatsuJikoku(pUiData->strHatsujikoku);

		AfterOperationComplement(
			sOperationA,
			vector<int>(),
			aHatsuJikoku,
			false,
			bIsTeisya);

	}
	/**
		前作業
	*/
	CentDedEkiJikoku* pChakuEkiJikoku = pRessya->getCentDedEkiJikokuCont()
		->getMuPtr()->get(iChakuEkiOrder);
	
	BeforeOperationToTarget(
		pChakuEkiJikoku->getCentDedBeforeOperationCont(),
		sOperationB);

	/**
		後作業
	*/
	CentDedEkiJikoku* pHatsuEkiJikoku = pRessya->getCentDedEkiJikokuCont()
		->getMuPtr()->get(iHatsuEkiOrder);

	AfterOperationToTarget(
		pHatsuEkiJikoku->getCentDedAfterOperationCont(),
		sOperationA);
	
	return iRv ;
}	



	// ********************************
	//	コンストラクタ
	// ********************************
CPropEditUI_Operation::CPropEditUI_Operation( 
		bool bNewItem , 
		Mu<CentDedRessya*>* pTarget , 
		int iChakuEkiOrder,
		int iHatsuEkiOrder,
		bool bFocusAfter,
		int iFocusIndex,
		bool bFocusChild,
		int iStandardShuntTrackIndex[],
		vector<vector<int>> iStandardOuterTerminalJikan)
		: CPropEditUi2( bNewItem ) 
		, m_pTarget( pTarget ) 
		, m_iChakuEkiOrder(iChakuEkiOrder)
		, m_iHatsuEkiOrder(iHatsuEkiOrder)
		,m_iStandardOuterTerminalJikan(iStandardOuterTerminalJikan)
	, m_bFocusAfter(bFocusAfter)
	, m_iFocusIndex(iFocusIndex)
	, m_bFocusChild(bFocusChild)
{
	m_iStandardShuntTrackIndex[0] = iStandardShuntTrackIndex[0];
	m_iStandardShuntTrackIndex[1] = iStandardShuntTrackIndex[1];
}



} //namespace ViewJikokuhyou

