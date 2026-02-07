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
//	CconvCentDed.cpp
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
#include "CconvCentDed.h"
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

int CconvCentDed::CentDedEkiTrack2_To_OuPropertiesText(
	const CentDedEkiTrack2& aCentDedEkiTrack2,
	OuPropertiesText::CNodeContainer* pCNodeContainer)
{
	int iRv = 0;
	// --------------------------------	
	//1.nameTrackName
	if (iRv >= 0) {
		if (aCentDedEkiTrack2.getTrackName().empty())
		{
			iRv = -11;	//	TrackName が指定されていません。
		}
		else
		{
			pCNodeContainer->setValue(nameTrackName,
				aCentDedEkiTrack2.getTrackName());
		}
	}
	//2.TrackRyakusyou
	if (iRv >= 0) {
		if (aCentDedEkiTrack2.getTrackRyakusyou().empty())
		{
			iRv = -21;	//	TrackRyakusyou が指定されていません。
		}
		else
		{
			pCNodeContainer->setValue(nameTrackRyakusyou,
				aCentDedEkiTrack2.getTrackRyakusyou());
		}
	}
	//3.TrackNoboriRyakusyou
	//上り略称は、空白の場合出力しません。
	if (iRv >= 0) {
		if (!aCentDedEkiTrack2.getTrackNoboriRyakusyou().empty())
		{
			pCNodeContainer->setValue(nameTrackNoboriRyakusyou,
				aCentDedEkiTrack2.getTrackNoboriRyakusyou());
		}
	}
	// --------------------------------	
	return (iRv);
}

int CconvCentDed::CentDedEkiTrack2_From_OuPropertiesText(
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

int CconvCentDed::CentDedEkiTrack2Cont_To_OuPropertiesText(
	const CentDedEkiTrack2Cont& aCentDedEkiTrack2Cont,
	OuPropertiesText::CNodeContainer* pCNodeContainer)
{
	int iRv = 0;
	if (iRv >= 0)
	{
		for (int idx = 0; iRv >= 0 && idx < aCentDedEkiTrack2Cont.size(); idx++)
		{
			Ou<CDirectory> pCDirectory = OuNew<CDirectory>(new CDirectory(nameEkiTrack2));
			int iResult = CentDedEkiTrack2_To_OuPropertiesText(
				aCentDedEkiTrack2Cont.get(idx),
				pCDirectory->getCNodeContainer());
			if (iResult < 0)
			{
				iRv = iResult;
				//	-	-11 ;	//	TrackName が指定されていません。
				//	-	-21 ;	//	TrackRyakusyou が指定されていません。
				//	-	-31 ;	//	TrackNoboriRyakusyou が指定されていません。
			}
			else
			{
				pCNodeContainer->insert(pCDirectory);
			}
		}
	}
	return iRv;
}


int CconvCentDed::CentDedEkiTrack2Cont_From_OuPropertiesText(
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
const TCHAR nameCaption[] = _T("Caption");
const TCHAR nameEnable[] = _T("Enable");
const TCHAR nameHeadwaySecond[] = _T("HeadwaySecond");
const TCHAR nameHeadwaySecondMinimum[] = _T("HeadwaySecondMinimum");
const TCHAR nameBeforeFromTrackContentCont[] = _T("BeforeFromTrackContentCont");
const TCHAR nameBeforeToTrackContentCont[] = _T("BeforeToTrackContentCont");
const TCHAR nameBeforeIsArrival[] = _T("BeforeIsArrival");
const TCHAR nameBeforeIsTsuuka[] = _T("BeforeIsTsuuka");
const TCHAR nameAfterFromTrackContentCont[] = _T("AfterFromTrackContentCont");
const TCHAR nameAfterToTrackContentCont[] = _T("AfterToTrackContentCont");
const TCHAR nameAfterIsArrival[] = _T("AfterIsArrival");
const TCHAR nameAfterIsTsuuka[] = _T("AfterIsTsuuka");

int CconvCentDed::CrossingCheckRule_To_OuPropertiesText(
	const CrossingCheckRule& aCrossingCheckRule, 
	OuPropertiesText::CNodeContainer* pCNodeContainer)
{
	int iRv = 0;
	//1.Caption
	if (iRv >= 0) {
		if (aCrossingCheckRule.strCaption.empty())
		{
			iRv = -1;	//	strCaption が指定されていません。
		}
		else
		{
			pCNodeContainer->setValue(nameCaption,
				aCrossingCheckRule.strCaption);
		}
	}
	//2.Enable
	if (iRv >= 0)
	{
		pCNodeContainer->setValue(nameEnable, 
			aCrossingCheckRule.bEnable ? _T("1") : _T("0"));
	}
	//3.HeadwaySecond
	if (iRv >= 0)
	{
		pCNodeContainer->setValue(nameHeadwaySecond,
			stringOf(aCrossingCheckRule.iHeadwaySecond));
	}
	//12.HeadwaySecondMinimum
	if (iRv >= 0)
	{
		pCNodeContainer->setValue(nameHeadwaySecondMinimum,
			stringOf(aCrossingCheckRule.iHeadwaySecondMinimum));
	}
	//4.BeforeFromTrackContentCont
	if (iRv >= 0)
	{
		vector<tstring> strTemp;
		for (int idx = 0; idx < (int)aCrossingCheckRule.BeforeFromTrackContentCont.size(); idx++)
		{
			strTemp.push_back(stringOf((int)aCrossingCheckRule.BeforeFromTrackContentCont[idx].eTrackType) + 
				_T("$") + stringOf(aCrossingCheckRule.BeforeFromTrackContentCont[idx].iTrackIndex));
		}
		pCNodeContainer->setValue(nameBeforeFromTrackContentCont,
			joinc(';', strTemp));
	}
	//5.BeforeToTrackContentCont
	if (iRv >= 0)
	{
		vector<tstring> strTemp;
		for (int idx = 0; idx < (int)aCrossingCheckRule.BeforeToTrackContentCont.size(); idx++)
		{
			strTemp.push_back(stringOf((int)aCrossingCheckRule.BeforeToTrackContentCont[idx].eTrackType) +
				_T("$") + stringOf(aCrossingCheckRule.BeforeToTrackContentCont[idx].iTrackIndex));
		}
		pCNodeContainer->setValue(nameBeforeToTrackContentCont,
			joinc(';', strTemp));
	}
	//6.BeforeIsArrival
	if (iRv >= 0)
	{
		pCNodeContainer->setValue(nameBeforeIsArrival,
			aCrossingCheckRule.bBeforeIsArrival ? _T("1") : _T("0"));
	}
	//7.BeforeIsTsuuka
	if (iRv >= 0)
	{
		pCNodeContainer->setValue(nameBeforeIsTsuuka,
			aCrossingCheckRule.bBeforeIsTsuuka ? _T("1") : _T("0"));
	}
	//8.AfterFromTrackContentCont
	if (iRv >= 0)
	{
		vector<tstring> strTemp;
		for (int idx = 0; idx < (int)aCrossingCheckRule.AfterFromTrackContentCont.size(); idx++)
		{
			strTemp.push_back(stringOf((int)aCrossingCheckRule.AfterFromTrackContentCont[idx].eTrackType) +
				_T("$") + stringOf(aCrossingCheckRule.AfterFromTrackContentCont[idx].iTrackIndex));
		}
		pCNodeContainer->setValue(nameAfterFromTrackContentCont,
			joinc(';', strTemp));
	}
	//9.AfterToTrackContentCont
	if (iRv >= 0)
	{
		vector<tstring> strTemp;
		for (int idx = 0; idx < (int)aCrossingCheckRule.AfterToTrackContentCont.size(); idx++)
		{
			strTemp.push_back(stringOf((int)aCrossingCheckRule.AfterToTrackContentCont[idx].eTrackType) +
				_T("$") + stringOf(aCrossingCheckRule.AfterToTrackContentCont[idx].iTrackIndex));
		}
		pCNodeContainer->setValue(nameAfterToTrackContentCont,
			joinc(';', strTemp));
	}
	//10.AfterIsArrival
	if (iRv >= 0)
	{
		pCNodeContainer->setValue(nameAfterIsArrival,
			aCrossingCheckRule.bAfterIsArrival ? _T("1") : _T("0"));
	}
	//11.AfterIsTsuuka
	if (iRv >= 0)
	{
		pCNodeContainer->setValue(nameAfterIsTsuuka,
			aCrossingCheckRule.bAfterIsTsuuka ? _T("1") : _T("0"));
	}
	return iRv;
}


int CconvCentDed::CrossingCheckRule_From_OuPropertiesText(
	CrossingCheckRule* pCrossingCheckRule, 
	const OuPropertiesText::IfNodeContainerConst* pCNodeContainer, 
	OuPropertiesText::ErrorInfo::COuErrorInfoContainer* pCOuErrorInfoContainer)
{
	int iRv = 0;

	CrossingCheckRule aCrossingCheckRule;

	//1.Caption
	if (iRv >= 0)
	{
		tstring strValue = pCNodeContainer->getValue(nameCaption);
		if (strValue.empty())
		{
			COuErrorInfo	aCOuErrorInfo(ERRREASON_TrackNameIsInvalid());
			aCOuErrorInfo.getProp()->setValue(nameCaption, strValue);
			pCOuErrorInfoContainer->insert(aCOuErrorInfo);
			iRv = -1;	//	strCaption が指定されていません。
		}
		else
		{
			aCrossingCheckRule.strCaption = strValue;
		}
	}
	//2.Enable
	if (iRv >= 0)
	{
		tstring strValue = pCNodeContainer->getValue(nameEnable);
		aCrossingCheckRule.bEnable = strValue != _T("0");
	}
	//3.HeadwaySecond
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(nameHeadwaySecond);
		int iValue;
		if (strValue == _T(""))
		{
			iValue = 60;
		}
		else
		{
			iValue = intOf(strValue);
		}
		aCrossingCheckRule.iHeadwaySecond = iValue;
	}
	//12.HeadwaySecondMinimum
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(nameHeadwaySecondMinimum);
		int iValue;
		if (strValue == _T(""))
		{
			iValue = 0;
		}
		else
		{
			iValue = intOf(strValue);
		}
		//HeadwaySecond>HeadwaySecondMinimum条件のチェックを行う。
		//満たさない場合は、HeadwaySecondが1以上の場合は、HeadwaySecondMinimumを0にする。
		if (aCrossingCheckRule.iHeadwaySecond <= iValue)
		{	
			iValue = 0;
		}

		aCrossingCheckRule.iHeadwaySecondMinimum = iValue;
	}
	//4.BeforeFromTrackContentCont
	if (iRv >= 0)
	{
		tstring strValue = pCNodeContainer->getValue(nameBeforeFromTrackContentCont);
		vector<tstring> contValue = splitc<vector<tstring>>(';', strValue);
		vector<TrackContent> TrackContentCont;
		for (int idx = 0; idx < (int)contValue.size(); idx++)
		{
			vector<tstring> contTemp = splitc<vector<tstring>>('$', contValue[idx]);
			TrackContent TrackContentTemp((ETrackType)intOf(contTemp[0]), intOf(contTemp[1]));
			TrackContentCont.push_back(TrackContentTemp);
		}
		if (TrackContentCont.empty())
		{
			iRv = -2;
		}
		else
		{
			aCrossingCheckRule.BeforeFromTrackContentCont = TrackContentCont;
		}
	}
	//5.BeforeToTrackContentCont
	if (iRv >= 0)
	{
		tstring strValue = pCNodeContainer->getValue(nameBeforeToTrackContentCont);
		vector<tstring> contValue = splitc<vector<tstring>>(';', strValue);
		vector<TrackContent> TrackContentCont;
		for (int idx = 0; idx < (int)contValue.size(); idx++)
		{
			vector<tstring> contTemp = splitc<vector<tstring>>('$', contValue[idx]);
			TrackContent TrackContentTemp((ETrackType)intOf(contTemp[0]), intOf(contTemp[1]));
			TrackContentCont.push_back(TrackContentTemp);
		}
		if (TrackContentCont.empty())
		{
			iRv = -3;
		}
		else
		{
			aCrossingCheckRule.BeforeToTrackContentCont = TrackContentCont;
		}
	}
	//6.nameBeforeIsArrival
	if (iRv >= 0)
	{
		tstring strValue = pCNodeContainer->getValue(nameBeforeIsArrival);
		aCrossingCheckRule.bBeforeIsArrival = strValue == _T("1");
	}
	//7.nameBeforeIsTsuuka
	if (iRv >= 0)
	{
		tstring strValue = pCNodeContainer->getValue(nameBeforeIsTsuuka);
		aCrossingCheckRule.bBeforeIsTsuuka = strValue == _T("1");
	}
	//8.AfterFromTrackContentCont
	if (iRv >= 0)
	{
		tstring strValue = pCNodeContainer->getValue(nameAfterFromTrackContentCont);
		vector<tstring> contValue = splitc<vector<tstring>>(';', strValue);
		vector<TrackContent> TrackContentCont;
		for (int idx = 0; idx < (int)contValue.size(); idx++)
		{
			vector<tstring> contTemp = splitc<vector<tstring>>('$', contValue[idx]);
			TrackContent TrackContentTemp((ETrackType)intOf(contTemp[0]), intOf(contTemp[1]));
			TrackContentCont.push_back(TrackContentTemp);
		}
		if (TrackContentCont.empty())
		{
			iRv = -4;
		}
		else
		{
			aCrossingCheckRule.AfterFromTrackContentCont = TrackContentCont;
		}
	}
	//9.AfterToTrackContentCont
	if (iRv >= 0)
	{
		tstring strValue = pCNodeContainer->getValue(nameAfterToTrackContentCont);
		vector<tstring> contValue = splitc<vector<tstring>>(';', strValue);
		vector<TrackContent> TrackContentCont;
		for (int idx = 0; idx < (int)contValue.size(); idx++)
		{
			vector<tstring> contTemp = splitc<vector<tstring>>('$', contValue[idx]);
			TrackContent TrackContentTemp((ETrackType)intOf(contTemp[0]), intOf(contTemp[1]));
			TrackContentCont.push_back(TrackContentTemp);
		}
		if (TrackContentCont.empty())
		{
			iRv = -5;
		}
		else
		{
			aCrossingCheckRule.AfterToTrackContentCont = TrackContentCont;
		}
	}
	//10.AfterIsArrival
	if (iRv >= 0)
	{
		tstring strValue = pCNodeContainer->getValue(nameAfterIsArrival);
		aCrossingCheckRule.bAfterIsArrival = strValue == _T("1");
	}
	//11.nameAfterIsTsuuka
	if (iRv >= 0)
	{
		tstring strValue = pCNodeContainer->getValue(nameAfterIsTsuuka);
		aCrossingCheckRule.bAfterIsTsuuka = strValue == _T("1");
	}
	if (iRv >= 0) 
	{
		*pCrossingCheckRule = aCrossingCheckRule;
	}
	return 0;
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
const TCHAR nameDiagramTrackOmit[] = _T("DiagramTrackOmit");
const TCHAR nameEkiTrack2Cont[] = _T("EkiTrack2Cont");
const TCHAR nameOuterTerminal[] = _T("OuterTerminal");
const TCHAR nameOuterTerminalEkimei[] = _T("OuterTerminalEkimei");
const TCHAR nameOuterTerminalJikokuRyaku[] = _T("OuterTerminalJikokuRyaku");
const TCHAR nameOuterTerminalDiaRyaku[] = _T("OuterTerminalDiaRyaku");
const TCHAR nameNextEkiDistance[] = _T("NextEkiDistance");
const TCHAR nameJikokuhyouTrackOmit[] = _T("JikokuhyouTrackOmit");
const TCHAR nameJikokuhyouOperationOrigin[] = _T("JikokuhyouOperationOrigin");
const TCHAR nameJikokuhyouOperationTerminal[] = _T("JikokuhyouOperationTerminal");
const TCHAR nameJikokuhyouOperationOriginDownBeforeUpAfter[] = _T("JikokuhyouOperationOriginDownBeforeUpAfter");
const TCHAR nameJikokuhyouOperationOriginDownAfterUpBefore[] = _T("JikokuhyouOperationOriginDownAfterUpBefore");
const TCHAR nameJikokuhyouOperationTerminalDownBeforeUpAfter[] = _T("JikokuhyouOperationTerminalDownBeforeUpAfter");
const TCHAR nameJikokuhyouOperationTerminalDownAfterUpBefore[] = _T("JikokuhyouOperationTerminalDownAfterUpBefore");
const TCHAR nameJikokuhyouJikokuDisplayKudari[] = _T("JikokuhyouJikokuDisplayKudari");
const TCHAR nameJikokuhyouJikokuDisplayNobori[] = _T("JikokuhyouJikokuDisplayNobori");
const TCHAR nameJikokuhyouSyubetsuChangeDisplayKudari[] = _T("JikokuhyouSyubetsuChangeDisplayKudari");
const TCHAR nameJikokuhyouSyubetsuChangeDisplayNobori[] = _T("JikokuhyouSyubetsuChangeDisplayNobori");
const TCHAR nameDiagramColorNextEki[] = _T("DiagramColorNextEki");
const TCHAR nameOperationTableDisplayJikoku[] = _T("OperationTableDisplayJikoku");
const TCHAR nameJikokuhyouOuterDisplayKudari[] = _T("JikokuhyouOuterDisplayKudari");
const TCHAR nameJikokuhyouOuterDisplayNobori[] = _T("JikokuhyouOuterDisplayNobori");
const TCHAR nameCrossingCheckRule[] = _T("CrossingCheckRule");



const CEnumToString< CentDedEki::EEkijikokukeisiki >&
CconvCentDed::getEEkijikokukeisikiToString()
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
CconvCentDed::getEEkikiboToString()
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
CconvCentDed::getEDiagramRessyajouhouHyoujiToString()
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



int CconvCentDed::CentDedEki_To_OuPropertiesText( 
			const CentDedEki& aCentDedEki , 
			OuPropertiesText::CNodeContainer* pCNodeContainer ) 
{
	int iRv = 0 ;
	// --------------------------------	
	//1.Ekimei
	if ( iRv >= 0 )
	{
		pCNodeContainer->setValue( nameEkimei , 
			aCentDedEki.getEkimei() ) ;
	}
	//1.1.EkimeiJikokuRyaku
	if (iRv >= 0)
	{
		if (!aCentDedEki.getEkimeiJikokuhyouRyaku(false).empty())
		{
			pCNodeContainer->setValue(nameEkimeiJikokuRyaku,
				aCentDedEki.getEkimeiJikokuhyouRyaku(false));
		}
	}
	//1.2.EkimeiDiaRyaku
	if (iRv >= 0)
	{
		if (!aCentDedEki.getEkimeiDiagramRyaku(false).empty())
		{
			pCNodeContainer->setValue(nameEkimeiDiaRyaku,
				aCentDedEki.getEkimeiDiagramRyaku(false));
		}
	}
	//2.Ekijikokukeisiki
	if ( iRv >= 0 )
	{
		tstring strValue = getEEkijikokukeisikiToString().stringOf( 
			aCentDedEki.getEkijikokukeisiki() ) ;
		pCNodeContainer->setValue( nameEkijikokukeisiki , strValue ) ;
	}

	//3.Ekikibo
	if ( iRv >= 0 )
	{
		tstring strValue = getEEkikiboToString().stringOf( 
			aCentDedEki.getEkikibo() ) ;
		pCNodeContainer->setValue( nameEkikibo , 
				strValue ) ;
	}
	//5. m_bDiagramRessyajouhouHyoujiKudari ;
	if ( iRv >= 0 )
	{
		tstring strValue = getEDiagramRessyajouhouHyoujiToString().stringOf( 
					aCentDedEki.getDiagramRessyajouhouHyoujiKudari() ) ;
		if ( !strValue.empty() )
		{
			pCNodeContainer->setValue( 
				nameDiagramRessyajouhouHyoujiKudari , strValue ) ;
		}
	}
	//6.m_bDiagramRessyajouhouHyoujiNobori
	if ( iRv >= 0 )
	{
		tstring strValue = getEDiagramRessyajouhouHyoujiToString().stringOf( 
					aCentDedEki.getDiagramRessyajouhouHyoujiNobori() ) ;
		if ( !strValue.empty() )
		{
			pCNodeContainer->setValue( nameDiagramRessyajouhouHyoujiNobori ,strValue) ;
		}
	}

	//7.DownMain ;
	if (iRv >= 0)
	{
		pCNodeContainer->setValue(
			nameDownMain,
			stringOf(
				aCentDedEki.getDownMain()
			)
		);
	}
	//8.UpMain ;
	if (iRv >= 0)
	{
		pCNodeContainer->setValue(
			nameUpMain,
			stringOf(
				aCentDedEki.getUpMain()
			)
		);
	}
	//9.BrunchCoreEkiIndex,BrunchOpposite
	if (iRv >= 0)
	{
		if (aCentDedEki.getBrunchCoreEkiIndex()>=0)
		{
			pCNodeContainer->setValue(
				nameBrunchCoreEkiIndex,
				stringOf(aCentDedEki.getBrunchCoreEkiIndex()));
			if (aCentDedEki.getBrunchOpposite())
			{
				pCNodeContainer->setValue(
					nameBrunchOpposite,
					_T("1"));
			}
		}
	}
	//10.LoopOriginEkiIndex
	if (iRv >= 0)
	{
		if (aCentDedEki.getLoopOriginEkiIndex() >= 0)
		{
			pCNodeContainer->setValue(
				nameLoopOriginEkiIndex,
				stringOf(aCentDedEki.getLoopOriginEkiIndex()));
			if (aCentDedEki.getLoopOpposite())
			{
				pCNodeContainer->setValue(
					nameLoopOpposite,
					_T("1"));
			}
		}
	}
	//11.JikokuhyouTrackDisplayKudari
	if (iRv >= 0)
	{
		if (aCentDedEki.getJikokuhyouTrackDisplayKudari())
		{
			pCNodeContainer->setValue(nameJikokuhyouTrackDisplayKudari, _T("1"));
		}
	}
	//12.JikokuhyouTrackDisplayNobori
	if (iRv >= 0)
	{
		if (aCentDedEki.getJikokuhyouTrackDisplayNobori())
		{
			pCNodeContainer->setValue(nameJikokuhyouTrackDisplayNobori, _T("1"));
		}
	}
	//13.DiagramTrackDisplay
	if (iRv >= 0)
	{
		if (aCentDedEki.getDiagramTrackDisplay())
		{
			pCNodeContainer->setValue(nameDiagramTrackDisplay, _T("1"));
		}
	}

	//29.DiagramTrackOmit
	if (iRv >= 0)
	{
		tstring strValue;
		for (int iEkiTrackIndex = 0; iEkiTrackIndex < aCentDedEki.getEkiTrack2Cont()->size(); iEkiTrackIndex++)
		{
			if (iEkiTrackIndex != 0)
			{
				strValue += _T(",");
			}
			if (aCentDedEki.getDiagramTrackOmit(iEkiTrackIndex))
			{
				strValue += _T("1");
			}
			else
			{
				strValue += _T("0");
			}
		}
		pCNodeContainer->setValue(nameDiagramTrackOmit, strValue);
	}

	//14.EkiTrack2Cont
	if (iRv >= 0)
	{
		Ou<CDirectory> pCDirectory = OuNew<CDirectory>(
			new CDirectory(nameEkiTrack2Cont));
		int iResult = CentDedEkiTrack2Cont_To_OuPropertiesText(
			*aCentDedEki.getEkiTrack2Cont(),
			pCDirectory->getCNodeContainer());
			//pCNodeContainer);
		//	-	-22 ;	//	Ekijikokukeisiki の値が不正です。
		//	-	-32 ;	//	Ekikibo の値が不正です。
		if (iResult < 0)
		{
			//	-	-22 ;	//	Ekijikokukeisiki の値が不正です。
			//	-	-32 ;	//	Ekikibo の値が不正です。
			iRv = iResult;
		}
		else
		{
			pCNodeContainer->insert(pCDirectory);
		}
	}
	//15.OuterTerminal
	if (iRv >= 0)
	{
		for (int idx = 0; idx < aCentDedEki.getOuterTerminalEkimeiCount(); idx++)
		{
			Ou<CDirectory> pCDirectory = OuNew<CDirectory>(new CDirectory(nameOuterTerminal));
			//15.1.OuterTerminalEkimei
			if (iRv >= 0)
			{
				pCDirectory->getCNodeContainer()->setValue(nameOuterTerminalEkimei,
					aCentDedEki.getOuterTerminalEkimei(idx));
				if (!aCentDedEki.getOuterTerminalJikokuRyaku(idx, false).empty())
				{
					pCDirectory->getCNodeContainer()->setValue(nameOuterTerminalJikokuRyaku,
						aCentDedEki.getOuterTerminalJikokuRyaku(idx, false));
				}
				if (!aCentDedEki.getOuterTerminalDiaRyaku(idx, false).empty())
				{
					pCDirectory->getCNodeContainer()->setValue(nameOuterTerminalDiaRyaku,
						aCentDedEki.getOuterTerminalDiaRyaku(idx, false));
				}
			}

			if (iRv >= 0)
			{
				pCNodeContainer->insert(pCDirectory);
			}

		}
	}
	//16.NextEkiDistance
	if (iRv >= 0)
	{
		if (!aCentDedEki.getNextEkiDistanceIsDefault())
		{
			pCNodeContainer->setValue(
				nameNextEkiDistance,
				stringOf(aCentDedEki.getNextEkiDistance()));
		}
	}
	//17.JikokuhyouTrackOmit
	if (iRv >= 0)
	{
		if (aCentDedEki.getJikokuhyouTrackOmit())
		{
			pCNodeContainer->setValue(nameJikokuhyouTrackOmit, _T("1"));
		}
	}
	//18.JikokuhyouOperationOrigin
	if (iRv >= 0)
	{
		if (aCentDedEki.getJikokuhyouOperationOrigin() > 0)
		{
			pCNodeContainer->setValue(
				nameJikokuhyouOperationOrigin,
				stringOf(aCentDedEki.getJikokuhyouOperationOrigin()));
		}
	}
	//19.JikokuhyouOperationTerminal
	if (iRv >= 0)
	{
		if (aCentDedEki.getJikokuhyouOperationTerminal() > 0)
		{
			pCNodeContainer->setValue(
				nameJikokuhyouOperationTerminal,
				stringOf(aCentDedEki.getJikokuhyouOperationTerminal()));
		}
	}
	//19.1.JikokuhyouOperationOriginDownBeforeUpAfter
	if (iRv >= 0)
	{
		if (aCentDedEki.getJikokuhyouOperationOriginDownBeforeUpAfter())
		{
			pCNodeContainer->setValue(nameJikokuhyouOperationOriginDownBeforeUpAfter, _T("1"));
		}
	}
	//19.2.JikokuhyouOperationOriginDownAfterUpBefore
	if (iRv >= 0)
	{
		if (aCentDedEki.getJikokuhyouOperationOriginDownAfterUpBefore())
		{
			pCNodeContainer->setValue(nameJikokuhyouOperationOriginDownAfterUpBefore, _T("1"));
		}
	}
	//19.3.JikokuhyouOperationTerminalDownBeforeUpAfter
	if (iRv >= 0)
	{
		if (aCentDedEki.getJikokuhyouOperationTerminalDownBeforeUpAfter())
		{
			pCNodeContainer->setValue(nameJikokuhyouOperationTerminalDownBeforeUpAfter, _T("1"));
		}
	}
	//19.4.JikokuhyouOperationTerminalDownAfterUpBefore
	if (iRv >= 0)
	{
		if (aCentDedEki.getJikokuhyouOperationTerminalDownAfterUpBefore())
		{
			pCNodeContainer->setValue(nameJikokuhyouOperationTerminalDownAfterUpBefore, _T("1"));
		}
	}
	//20.JikokuhyouJikokuDisplayKudari
	if (iRv >= 0)
	{
		tstring strValue;
		if (aCentDedEki.getJikokuhyouChakuJikokuDisplayKudari())
		{
			strValue += _T("1,");
		}
		else
		{
			strValue += _T("0,");
		}
		if (aCentDedEki.getJikokuhyouHatsuJikokuDisplayKudari())
		{
			strValue += _T("1");
		}
		else
		{
			strValue += _T("0");
		}
		pCNodeContainer->setValue(
			nameJikokuhyouJikokuDisplayKudari,
			strValue);
	}
	//21.JikokuhyouJikokuDisplayNobori
	if (iRv >= 0)
	{
		tstring strValue;
		if (aCentDedEki.getJikokuhyouChakuJikokuDisplayNobori())
		{
			strValue += _T("1,");
		}
		else
		{
			strValue += _T("0,");
		}
		if (aCentDedEki.getJikokuhyouHatsuJikokuDisplayNobori())
		{
			strValue += _T("1");
		}
		else
		{
			strValue += _T("0");
		}
		pCNodeContainer->setValue(
			nameJikokuhyouJikokuDisplayNobori,
			strValue);
	}
	
	//22.JikokuhyouSyubetsuChangeDisplayKudari
	if (iRv >= 0)
	{
		tstring strValue;
		strValue += to_tstring(aCentDedEki.getJikokuhyouRessyabangouDisplayKudari());
		strValue += _T(",");
		strValue += to_tstring(aCentDedEki.getJikokuhyouOperationNumberDisplayKudari());
		strValue += _T(",");
		strValue += to_tstring(aCentDedEki.getJikokuhyouRessyaSyubetsuDisplayKudari());
		strValue += _T(",");
		strValue += to_tstring(aCentDedEki.getJikokuhyouRessyameiDisplayKudari());
		strValue += _T(",");
		strValue += to_tstring(aCentDedEki.getJikokuhyouOperationNumberDisplayRowsKudari());

		pCNodeContainer->setValue(
			nameJikokuhyouSyubetsuChangeDisplayKudari,
			strValue);
	}
	//23.JikokuhyouSyubetsuChangeDisplayNobori
	if (iRv >= 0)
	{
		tstring strValue;
		strValue += to_tstring(aCentDedEki.getJikokuhyouRessyabangouDisplayNobori());
		strValue += _T(",");
		strValue += to_tstring(aCentDedEki.getJikokuhyouOperationNumberDisplayNobori());
		strValue += _T(",");
		strValue += to_tstring(aCentDedEki.getJikokuhyouRessyaSyubetsuDisplayNobori());
		strValue += _T(",");
		strValue += to_tstring(aCentDedEki.getJikokuhyouRessyameiDisplayNobori());
		strValue += _T(",");
		strValue += to_tstring(aCentDedEki.getJikokuhyouOperationNumberDisplayRowsNobori());

		pCNodeContainer->setValue(
			nameJikokuhyouSyubetsuChangeDisplayNobori,
			strValue);
	}
	//24.DiagramColorNextEki ;
	if (iRv >= 0)
	{
		pCNodeContainer->setValue(
			nameDiagramColorNextEki,
			stringOf(aCentDedEki.getDiagramColorNextEki()));
	}
	//25.OperationTableDisplayJikoku
	if (iRv >= 0)
	{
		if (aCentDedEki.getOperationTableDisplayJikoku())
		{
			pCNodeContainer->setValue(nameOperationTableDisplayJikoku, _T("1"));
		}
	}
	//26.JikokuhyouOuterDisplayKudari
	if (iRv >= 0)
	{
		tstring strValue;
		if (aCentDedEki.getJikokuhyouOuterSihatsuDisplayKudari())
		{
			strValue += _T("1,");
		}
		else
		{
			strValue += _T("0,");
		}
		if (aCentDedEki.getJikokuhyouOuterShuchakuDisplayKudari())
		{
			strValue += _T("1");
		}
		else
		{
			strValue += _T("0");
		}
		pCNodeContainer->setValue(
			nameJikokuhyouOuterDisplayKudari,
			strValue);
	}
	//27.JikokuhyouOuterDisplayNobori
	if (iRv >= 0)
	{
		tstring strValue;
		if (aCentDedEki.getJikokuhyouOuterSihatsuDisplayNobori())
		{
			strValue += _T("1,");
		}
		else
		{
			strValue += _T("0,");
		}
		if (aCentDedEki.getJikokuhyouOuterShuchakuDisplayNobori())
		{
			strValue += _T("1");
		}
		else
		{
			strValue += _T("0");
		}
		pCNodeContainer->setValue(
			nameJikokuhyouOuterDisplayNobori,
			strValue);
	}
	//28.CrossingCheckRule
	if (iRv >= 0)
	{
		for (int idx = 0; idx < aCentDedEki.getCrossingCheckRuleSize(); idx++)
		{
			Ou<CDirectory> pCDirectory = OuNew<CDirectory>(new CDirectory(nameCrossingCheckRule));
			int iResult = CrossingCheckRule_To_OuPropertiesText(
				aCentDedEki.getCrossingCheckRule(idx),
				pCDirectory->getCNodeContainer());
			if (iResult < 0)
			{
				iRv = iResult;
			}
			else
			{
				pCNodeContainer->insert(pCDirectory);
			}
		}
	}


	// --------------------------------	
	return ( iRv ) ;
}

int CconvCentDed::CentDedEki_From_OuPropertiesText( 
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
	//19.1.JikokuhyouOperationOriginDownBeforeUpAfter,JikokuhyouOperationOriginDownAfterUpBefore
	if (iRv >= 0 && aCentDedEki.getJikokuhyouOperationOrigin()>0)
	{
		tstring	strValue = pCNodeContainer->getValue(nameJikokuhyouOperationOriginDownBeforeUpAfter);
		aCentDedEki.setJikokuhyouOperationOriginDownBeforeUpAfter(strValue == _T("1"));

		tstring	strValue2 = pCNodeContainer->getValue(nameJikokuhyouOperationOriginDownAfterUpBefore);
		aCentDedEki.setJikokuhyouOperationOriginDownAfterUpBefore(strValue2 == _T("1"));
	}
	//19.2.JikokuhyouOperationTerminalDownBeforeUpAfter,JikokuhyouOperationTerminalDownAfterUpBefore
	if (iRv >= 0 && aCentDedEki.getJikokuhyouOperationTerminal() > 0)
	{
		tstring	strValue = pCNodeContainer->getValue(nameJikokuhyouOperationTerminalDownBeforeUpAfter);
		aCentDedEki.setJikokuhyouOperationTerminalDownBeforeUpAfter(strValue == _T("1"));

		tstring	strValue2 = pCNodeContainer->getValue(nameJikokuhyouOperationTerminalDownAfterUpBefore);
		aCentDedEki.setJikokuhyouOperationTerminalDownAfterUpBefore(strValue2 == _T("1"));
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

				if (iResult < 0 || iResult>3)
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
			aCentDedEki.setJikokuhyouRessyabangouDisplayKudari(iResult);
		}
		else
		{
			aCentDedEki.setJikokuhyouRessyabangouDisplayKudari(1);
		}

		if (contValue.size() >= 2 && !contValue[1].empty())
		{
			int iResult;
			try
			{
				iResult = stoi(contValue[1]);

				if (iResult < 0 || iResult>4)
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
			aCentDedEki.setJikokuhyouOperationNumberDisplayKudari(iResult);
		}
		else
		{
			aCentDedEki.setJikokuhyouOperationNumberDisplayKudari(1);
		}

		if (contValue.size() >= 3 && !contValue[2].empty())
		{
			int iResult;
			try
			{
				iResult = stoi(contValue[2]);

				if (iResult < 0 || iResult>3)
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

				if (iResult < 0 || iResult>3)
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
			aCentDedEki.setJikokuhyouRessyameiDisplayKudari(iResult);
		}
		else
		{
			aCentDedEki.setJikokuhyouRessyameiDisplayKudari(0);
		}

		if (contValue.size() >= 5 && !contValue[4].empty())
		{
			int iResult;
			try
			{
				iResult = stoi(contValue[4]);

				if (iResult < 1 || iResult>5)
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
			aCentDedEki.setJikokuhyouOperationNumberDisplayRowsKudari(iResult);
		}
		else
		{
			aCentDedEki.setJikokuhyouOperationNumberDisplayRowsKudari(1);
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

				if (iResult < 0 || iResult>3)
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
			aCentDedEki.setJikokuhyouRessyabangouDisplayNobori(iResult);
		}
		else
		{
			aCentDedEki.setJikokuhyouRessyabangouDisplayNobori(1);
		}

		if (contValue.size() >= 2 && !contValue[1].empty())
		{
			int iResult;
			try
			{
				iResult = stoi(contValue[1]);

				if (iResult < 0 || iResult>4)
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
			aCentDedEki.setJikokuhyouOperationNumberDisplayNobori(iResult);
		}
		else
		{
			aCentDedEki.setJikokuhyouOperationNumberDisplayNobori(1);
		}

		if (contValue.size() >= 3 && !contValue[2].empty())
		{
			int iResult;
			try
			{
				iResult = stoi(contValue[2]);

				if (iResult < 0 || iResult>3)
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

				if (iResult < 0 || iResult>3)
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
			aCentDedEki.setJikokuhyouRessyameiDisplayNobori(iResult);
		}
		else
		{
			aCentDedEki.setJikokuhyouRessyameiDisplayNobori(0);
		}

		if (contValue.size() >= 5 && !contValue[4].empty())
		{
			int iResult;
			try
			{
				iResult = stoi(contValue[4]);

				if (iResult < 1 || iResult>5)
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
			aCentDedEki.setJikokuhyouOperationNumberDisplayRowsNobori(iResult);
		}
		else
		{
			aCentDedEki.setJikokuhyouOperationNumberDisplayRowsNobori(1);
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
	//26.JikokuhyouOuterDisplayKudari
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(
			nameJikokuhyouOuterDisplayKudari);
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
			aCentDedEki.setJikokuhyouOuterSihatsuDisplayKudari(iResult == 1);
		}
		else
		{
			aCentDedEki.setJikokuhyouOuterSihatsuDisplayKudari(false);
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
			aCentDedEki.setJikokuhyouOuterShuchakuDisplayKudari(iResult);
		}
		else
		{
			aCentDedEki.setJikokuhyouOuterShuchakuDisplayKudari(false);
		}
	}
	//27.JikokuhyouOuterDisplayNobori
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(
			nameJikokuhyouOuterDisplayNobori);
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
			aCentDedEki.setJikokuhyouOuterSihatsuDisplayNobori(iResult == 1);
		}
		else
		{
			aCentDedEki.setJikokuhyouOuterSihatsuDisplayNobori(false);
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
			aCentDedEki.setJikokuhyouOuterShuchakuDisplayNobori(iResult == 1);
		}
		else
		{
			aCentDedEki.setJikokuhyouOuterShuchakuDisplayNobori(false);
		}
	}
	//28.CrossingCheckRule
	if (iRv >= 0)
	{
		int iSize = pCNodeContainer->sizeInName(nameCrossingCheckRule);
		for (int idx = 0; idx < iSize; idx++)
		{
			Ou<const CDirectory> pCDirectory;
			if (iRv >= 0)
			{
				pCDirectory = dynamic_castOu<const CDirectory>(
					pCNodeContainer->getInName(nameCrossingCheckRule, idx));
				CrossingCheckRule aCrossingCheckRule;
				int iResult = CrossingCheckRule_From_OuPropertiesText(
					&aCrossingCheckRule,
					pCDirectory->getIfNodeContainerConst(),
					pCOuErrorInfoContainer);
				if (iResult < 0)
				{
					iRv = iResult;
				}
				else
				{
					aCentDedEki.addCrossingCheckRule(aCrossingCheckRule);
				}
			}
		}
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

	//29.DiagramTrackOmit
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(nameDiagramTrackOmit);
		vector<tstring> contValue = splitc<vector<tstring>>(',', strValue);
		vector<bool> bDiagramTrackOmit(aCentDedEkiTrack2Cont.size(), false);
		for (int iIndex = 0; iIndex < aCentDedEkiTrack2Cont.size(); iIndex++)
		{
			if (iIndex < contValue.size())
			{
				bDiagramTrackOmit[iIndex] = contValue[iIndex] == _T("1");
			}
			else
			{
				bDiagramTrackOmit[iIndex] = false;
			}
		}
		aCentDedEki.setDiagramTrackOmit(bDiagramTrackOmit);
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
	
int CconvCentDed::CentDedEkiCont_To_OuPropertiesText( 
			const CentDedEkiCont& aCentDedEkiCont , 
			OuPropertiesText::CNodeContainer* pCNodeContainer ) 
{
	int iRv = 0 ;
	if ( iRv >= 0 )
	{
		for ( int idxEki = 0 ; iRv >= 0 && idxEki < aCentDedEkiCont.size() ; idxEki ++ )
		{
			Ou<CDirectory> pCDirectory = OuNew<CDirectory>( new CDirectory( nameEki ) ) ;
			int iResult = CentDedEki_To_OuPropertiesText(
				aCentDedEkiCont.get( idxEki ) ,
				pCDirectory->getCNodeContainer() ) ;
			if ( iResult < 0 )
			{
				iRv = iResult ;
			}
			else
			{
				pCNodeContainer->insert( pCDirectory ) ;
			}
		}
	}
	return iRv ;
}
	

int CconvCentDed::CentDedEkiCont_From_OuPropertiesText( 
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
const TCHAR nameHidden[] = _T("Hidden");

const CEnumToString< CentDedRessyasyubetsu::ESenStyle >& 
CconvCentDed::getESenStyleToString()
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
CconvCentDed::getEStopMarkDrawTypeToString()
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

int CconvCentDed::CdDiagramLineStyle_To_OuPropertiesText( 
	const CentDedRessyasyubetsu::CdDiagramLineStyle& aCdDiagramLineStyle , 
	OuPropertiesText::CNodeContainer* pCNodeContainer ) 
{
	int iRv = 0 ;

	// --------------------------------	
	//5.DiagramSenColor
	if ( iRv >= 0 )
	{
		pCNodeContainer->setValue( nameDiagramSenColor , 
			CdColorProp_to_string( aCdDiagramLineStyle.getDiagramSenColor() ) ) ;
	}

	//6.DiagramSenStyle
	if ( iRv >= 0 )
	{
		tstring strValue = getESenStyleToString().stringOf( aCdDiagramLineStyle.getDiagramSenStyle() ) ;
		pCNodeContainer->setValue( nameDiagramSenStyle , strValue ) ;

	}

	//7.DiagramSenIsBold
	if ( iRv >= 0 )
	{
		bool bValue = aCdDiagramLineStyle.getDiagramSenIsBold();
		if ( bValue )
		{
			pCNodeContainer->setValue( nameDiagramSenIsBold , _T("1") ) ;
		}
	}
	return iRv ;
}

int CconvCentDed::CdDiagramLineStyle_From_OuPropertiesText( 
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


int CconvCentDed::CentDedRessyasyubetsu_To_OuPropertiesText( 
			const CentDedRessyasyubetsu& aCentDedRessyasyubetsu , 
			OuPropertiesText::CNodeContainer* pCNodeContainer ) 
{
	int iRv = 0 ;

	// --------------------------------	
	//1.Syubetsumei
	if ( iRv >= 0 )
	{
		if ( aCentDedRessyasyubetsu.getSyubetsumei().empty() )
		{
			iRv = -11 ;	//	Syubetsumei が指定されていません。
		}
		else
		{
			pCNodeContainer->setValue( nameSyubetsumei , 
				aCentDedRessyasyubetsu.getSyubetsumei() ) ;
		}
	}


	//2.Ryakusyou
	if ( iRv >= 0 )
	{
		if ( aCentDedRessyasyubetsu.getRyakusyou().empty() )
		{

		}
		else
		{
			pCNodeContainer->setValue( nameRyakusyou , 
				aCentDedRessyasyubetsu.getRyakusyou() ) ;
		}
	}

	//3.JikokuhyouMojiColor
	if ( iRv >= 0 )
	{
		pCNodeContainer->setValue( nameJikokuhyouMojiColor , 
			CdColorProp_to_string( aCentDedRessyasyubetsu.getJikokuhyouMojiColor() ) ) ;
	}
	//4.JikokuhyouFontIndex
	if ( iRv >= 0 )
	{
		int iValue = aCentDedRessyasyubetsu.getJikokuhyouFontIndex() ;
		{
			pCNodeContainer->setValue( 
				nameJikokuhyouFontIndex , 
				stringOf( iValue ) ) ;
		}
	}
	//4.1.JikokuhyouMojiColor
	if (iRv >= 0)
	{
		pCNodeContainer->setValue(nameJikokuhyouBackColor,
			CdColorProp_to_string(aCentDedRessyasyubetsu.getJikokuhyouBackColor()));
	}
	//5.DiagramSenColor
	//6.DiagramSenStyle
	//7.DiagramSenIsBold
	if ( iRv >= 0 )
	{
		CdDiagramLineStyle_To_OuPropertiesText( 
			aCentDedRessyasyubetsu.getCdDiagramLineStyle() ,
			pCNodeContainer ) ;
	}

	//9 StopMarkDrawType
	if ( iRv >= 0 )
	{
		tstring strValue = getEStopMarkDrawTypeToString().stringOf( aCentDedRessyasyubetsu.getStopMarkDrawType() ) ;
		pCNodeContainer->setValue( nameStopMarkDrawType , strValue ) ;
	}

	//10.ParentSyubetsuIndex
	if (iRv >= 0)
	{
		if (aCentDedRessyasyubetsu.getParentSyubetsuIndex() >= 0)
		{
			pCNodeContainer->setValue(
				nameParentSyubetsuIndex,
				stringOf(aCentDedRessyasyubetsu.getParentSyubetsuIndex()));
		}
	}

	//11.Hidden
	if (iRv >= 0)
	{
		if (aCentDedRessyasyubetsu.getHidden())
		{
			pCNodeContainer->setValue(nameHidden, _T("1"));
		}
	}

	return ( iRv ) ;
}


int CconvCentDed::CentDedRessyasyubetsu_From_OuPropertiesText( 
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

	//11."Hidden"
	if (iRv >= 0) {
		tstring	strValue = pCNodeContainer->getValue(nameHidden);
		aCentDedRessyasyubetsu.setHidden(strValue == _T("1"));
	}

	// --------------------------------
	if ( iRv >= 0 )
	{
		*pCentDedRessyasyubetsu = aCentDedRessyasyubetsu ;
	}

	return ( iRv ) ;
}

void CconvCentDed::CentDedRessyasyubetsu_to_CDcdFreeLineProp(
		const CentDedRessyasyubetsu::CdDiagramLineStyle& aLineStyle , 
		CdDcdFreeLineProp* pCdLineProp )
{
	pCdLineProp->setColor( aLineStyle.getDiagramSenColor() ) ;
	switch( aLineStyle.getDiagramSenStyle() ){
		 // 実線 
		 case CentDedRessyasyubetsu::SenStyle_Jissen :
			pCdLineProp->setLinestyle( LINESTYLE_SOLID ) ;
			break ;
		 // 破線
		 case CentDedRessyasyubetsu::SenStyle_Hasen :
			pCdLineProp->setLinestyle( LINESTYLE_DASH ) ;
			break ;
		 // 点線
		 case CentDedRessyasyubetsu::SenStyle_Tensen :
			pCdLineProp->setLinestyle( LINESTYLE_DOT ) ;
			break ;
		 // 一点鎖線
		 case CentDedRessyasyubetsu::SenStyle_Ittensasen :
			pCdLineProp->setLinestyle( LINESTYLE_DASH_DOT ) ;
			break ;
	}
	pCdLineProp->setLogicalunitWidth( aLineStyle.getDiagramSenIsBold() ? 2 : 1 ) ;

}

	// ********************************
	//	CentDedRessyasyubetsuCont
	// ********************************
const TCHAR nameRessyasyubetsu[] = _T("Ressyasyubetsu") ;
	

int CconvCentDed::CentDedRessyasyubetsuCont_To_OuPropertiesText( 
			const CentDedRessyasyubetsuCont& aCentDedRessyasyubetsuCont , 
			OuPropertiesText::CNodeContainer* pCNodeContainer ) 
{
	int iRv = 0 ;
	if ( iRv >= 0 )
	{
		for ( int idx = 0 ; iRv >= 0 && idx < aCentDedRessyasyubetsuCont.size() ; idx ++ )
		{
			Ou<CDirectory> pCDirectory = OuNew<CDirectory>( new CDirectory( nameRessyasyubetsu ) ) ;
			int iResult = CentDedRessyasyubetsu_To_OuPropertiesText(
				aCentDedRessyasyubetsuCont.get( idx ) ,
				pCDirectory->getCNodeContainer() ) ;
			//	-	-11 ;	//	Syubetsumei が指定されていません。
			//	-	-52 ;	//	DiagramSenStyle の値が不正です。
			if ( iResult < 0 )
			{
				//	-	-11 ;	//	Syubetsumei が指定されていません。
				//	-	-52 ;	//	DiagramSenStyle の値が不正です。
				iRv = iResult ;
			}
			else
			{
				pCNodeContainer->insert( pCDirectory ) ;
			}
		}
	}
	return iRv ;
}
	
int CconvCentDed::CentDedRessyasyubetsuCont_From_OuPropertiesText( 
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
tstring CconvCentDed::CentDedEkiJikoku_To_string( 
			const CentDedEkiJikoku* pCentDedEkiJikoku ) 
{
	tstring	strEkiatsukai ;
	tstring strChaku ;
	tstring strHatsu ;
	tstring strRessyaTrackIndex;
	//	駅扱
	if ( pCentDedEkiJikoku->getEkiatsukai() != CentDedEkiJikoku::Ekiatsukai_None )
	{
		strEkiatsukai = stringOf( 
			(int)pCentDedEkiJikoku->getEkiatsukai() ) ;
	}
	//	着時刻
	if ( !pCentDedEkiJikoku->getChakujikoku().isNull() )
	{
		strChaku = g_CdDedJikokuConv.encode( pCentDedEkiJikoku->getChakujikoku() ) ;
	}
	//	発時刻
	if ( !pCentDedEkiJikoku->getHatsujikoku().isNull() )
	{
		strHatsu = g_CdDedJikokuConv.encode( pCentDedEkiJikoku->getHatsujikoku() ) ;
	}
	//　番線
	if (pCentDedEkiJikoku->getEkiatsukai() != CentDedEkiJikoku::Ekiatsukai_None)
	{
		strRessyaTrackIndex = stringOf(pCentDedEkiJikoku->getRessyaTrackIndex());
	}

	tstring	strEkijikoku ;
	strEkijikoku.reserve( 32 ) ;
	if ( !strEkiatsukai.empty() )
	{
		strEkijikoku += strEkiatsukai ;
		if ( !strChaku.empty() || !strHatsu.empty() )
		{
			strEkijikoku += ';' ;
			if ( !strChaku.empty() )
			{
				strEkijikoku += strChaku ;
				strEkijikoku += '/' ;
			}
			strEkijikoku += strHatsu ;
		}
		if (!strRessyaTrackIndex.empty())
		{
			strEkijikoku += '$';
			strEkijikoku += strRessyaTrackIndex;
		}
	}
	return strEkijikoku ;
}

int CconvCentDed::CentDedEkiJikoku_From_string( 
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
	//strEkiatsukai = 駅扱・空文字列は『運行なし』。"1"～"3" ;
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

vector<vector<tstring>> CconvCentDed::CentDedBeforeOperationCont_To_string(
	const CentDedBeforeOperationCont * pBeforeOperationCont,
	const tstring strParentIndex)
{
	vector<vector<tstring>> strOperation = { { nameOperation + strParentIndex ,_T("")} };

	//strOperation[0][0] += nameOperation;
	//strOperation[0][0] += strParentIndex;
	vector<tstring> strThisCont;
	for (int idx = 0; idx < pBeforeOperationCont->size(); idx++)
	{
		const CentDedBeforeOperation*	pOperation
			= pBeforeOperationCont->getMuPtr()->get(idx);
		if (pOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
		{
			tstring strOperationShunt = _T("0/");
			strOperationShunt += to_tstring(pOperation->getShuntTrackIndex());
			strOperationShunt += _T('$');
			strOperationShunt +=
				g_CdDedJikokuConv.encode(pOperation->getOperationHatsuJikoku());
			strOperationShunt += _T('/');
			if (!pOperation->getOperationChakuJikoku().isNull())
			{
				strOperationShunt +=
					g_CdDedJikokuConv.encode(pOperation->getOperationChakuJikoku());
			}
			strOperationShunt += _T('$');
			strOperationShunt += pOperation->getIsDisplayChakuJikoku() ? '1' : '0';

			strThisCont.push_back(strOperationShunt);


		}
		else if (pOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
		{
			tstring strOperationConnect = _T("1/");
			strOperationConnect += pOperation->getIsConnectToFront() ? '1' : '0';
			strOperationConnect += _T('$');
			strOperationConnect +=
				g_CdDedJikokuConv.encode(pOperation->getConnectJikoku());

			strThisCont.push_back(strOperationConnect);

			tstring strChildIndex = strParentIndex;
			strChildIndex += _T('.');
			strChildIndex += to_tstring(idx);
			strChildIndex += _T('B');
			vector<vector<tstring>> strChildOperation = 
				CentDedBeforeOperationCont_To_string(
					pOperation->getCentDedBeforeOperationCont(),
					strChildIndex);
			for (int idxs = 0; idxs < (int)strChildOperation.size(); idxs++)
			{
				strOperation.push_back(strChildOperation[idxs]);
			}
		}
		else if (pOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
		{
			tstring strOperationRelease = _T("2/");
			strOperationRelease += to_tstring(pOperation->getReleasePos());
			strOperationRelease += _T('$');
			strOperationRelease += to_tstring(pOperation->getReleaseIndexCount());
			strOperationRelease += _T('/');
			strOperationRelease +=
				g_CdDedJikokuConv.encode(pOperation->getReleaseJikoku());

			strThisCont.push_back(strOperationRelease);

			tstring strChildIndex = strParentIndex;
			strChildIndex += _T('.');
			strChildIndex += to_tstring(idx);
			strChildIndex += _T('A');
			vector<vector<tstring>> strChildOperation =
				CentDedAfterOperationCont_To_string(
					pOperation->getCentDedAfterOperationCont(),
					strChildIndex);
			for (int idxs = 0; idxs < (int)strChildOperation.size(); idxs++)
			{
				strOperation.push_back(strChildOperation[idxs]);
			}

		}
		else if (pOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Out)
		{
			//Ver2.05 入出区連携コード追加
			tstring strOperationOut = _T("3/");
			strOperationOut +=
				g_CdDedJikokuConv.encode(pOperation->getOutJikoku());
			strOperationOut += _T('$');
			strOperationOut += pOperation->getInOutLinkCode();
			strOperationOut += _T('/');
			strOperationOut += joinc(';', pOperation->getOperationNumberOriginal());

			strThisCont.push_back(strOperationOut);

		}
		else if (pOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
		{
			//Ver2.05 入出区連携コード追加
			tstring strOperationOuter = _T("4/");
			strOperationOuter += to_tstring(pOperation->getOuterShihatsuekiIndex());
			strOperationOuter += _T('$');
			strOperationOuter +=
				g_CdDedJikokuConv.encode(pOperation->getOuterShihatsuJikoku());
			strOperationOuter += _T('/');
			strOperationOuter +=
				g_CdDedJikokuConv.encode(pOperation->getChakuJikoku());
			strOperationOuter += _T('$');
			strOperationOuter += pOperation->getInOutLinkCode();
			strOperationOuter += _T('/');
			strOperationOuter += joinc(';', pOperation->getOperationNumberOriginal());

			strThisCont.push_back(strOperationOuter);

		}
		else if (pOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Junction)
		{
			//Ver2.00.05 解結表示省略および仮運用番号要素を追加
			//Ver2.05 解結表示省略を削除
			tstring strOperationJunction = _T("5/");
			strOperationJunction +=
				g_CdDedJikokuConv.encode(pOperation->getOriginJikoku());
			strOperationJunction += _T('$');
			strOperationJunction += joinc(';', pOperation->getOperationNumberTemp());

			strThisCont.push_back(strOperationJunction);

		}
		else if (pOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_NumberChange)
		{
			//Ver2.00.05 運用番号変更作業を追加
			//Ver2.06.05 運用番号順反転設定を追加
			tstring strOperationNumChange = _T("6/");
			//運用番号が空であることを、運用番号順反転が有効な状態であるとみなすようにする。、
			if (!pOperation->getOperationNumberReverse())
			{
				strOperationNumChange += joinc(';', pOperation->getOperationNumber());
			}

			strThisCont.push_back(strOperationNumChange);
		}
	}
	strOperation[0][1] = joinc(',', strThisCont);
	return strOperation;
}

int CconvCentDed::CentDedBeforeOperationCont_From_string(
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
			tstring strOperationPara5;

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

			pos = strOperation.find('/');
			if (pos != tstring::npos)
			{
				strOperationPara4 = strOperation.substr(0, pos);
				strOperation.erase(0, pos + 1);
			}
			else
			{
				strOperationPara4 = strOperation;
				strOperation.clear();
			}

			strOperationPara5 = strOperation;

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
					pCNodeContainer);
			}
			else if (strOperationType == _T("3"))
			{
				//Ver2.05 入出区連携コードを追加、運番の位置変更に対応
				vector<tstring> strOperationNumber =
					splitc<vector<tstring>>(';', strOperationPara3,true);
				aBeforeOperation =
					CentDedBeforeOperation(
						CentDedBeforeOperation::EBOperation::BOperation_Out,
						CdDedJikoku(strOperationPara1),
						strOperationNumber,
						strOperationPara2);
			}
			else if (strOperationType == _T("4"))
			{
				//Ver2.05 入出区連携コードを追加、運番の位置変更に対応
				int iOuterTerminalIndex = stoi(strOperationPara1);
				if (iOuterTerminalIndex < 0 || iOuterTerminalIndex >= iOuterTerminalCount)
				{
					iOuterTerminalIndex = 0;
				}
				vector<tstring> strOperationNumber =
					splitc<vector<tstring>>(';', strOperationPara5,true);
				aBeforeOperation =
					CentDedBeforeOperation(
						CentDedBeforeOperation::EBOperation::BOperation_Outer,
						iOuterTerminalIndex,
						CdDedJikoku(strOperationPara2),
						CdDedJikoku(strOperationPara3),
						strOperationNumber,
						strOperationPara4);
			}
			else if (strOperationType == _T("5"))
			{
				//Ver2.00.05 解結表示省略および仮運用番号要素を追加
				//Ver2.05 解結表示省略削除
				vector<tstring> strOperationNumber =
					splitc<vector<tstring>>(';', strOperationPara2, true);
				aBeforeOperation =
					CentDedBeforeOperation(
						CentDedBeforeOperation::EBOperation::BOperation_Junction,
						CdDedJikoku(strOperationPara1),
						strOperationNumber);
			}
			else if (strOperationType == _T("6"))
			{
				//Ver2.00.05 運用番号変更作業を追加
				//Ver2.06.05 運用番号順反転設定を追加

				//strOperationPara1(運用番号)が空の場合は、運用番号順反転設定が有効であるとみなす。
				if (strOperationPara1.empty())
				{
					aBeforeOperation =
						CentDedBeforeOperation(
							CentDedBeforeOperation::EBOperation::BOperation_NumberChange,
							vector<tstring>(),
							true);
				}
				else
				{
					vector<tstring> strOperationNumber =
						splitc<vector<tstring>>(';', strOperationPara1, true);
					aBeforeOperation =
						CentDedBeforeOperation(
							CentDedBeforeOperation::EBOperation::BOperation_NumberChange,
							strOperationNumber,
							false);
				}
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

vector<vector<tstring>> CconvCentDed::CentDedAfterOperationCont_To_string(
	const CentDedAfterOperationCont * pAfterOperationCont, 
	const tstring strParentIndex)
{
	vector<vector<tstring>> strOperation = { { nameOperation + strParentIndex ,_T("")} };

	//strOperation[0][0] += nameOperation;
	//strOperation[0][0] += strParentIndex;
	vector<tstring> strThisCont;
	for (int idx = 0; idx < pAfterOperationCont->size(); idx++)
	{
		const CentDedAfterOperation*	pOperation
			= pAfterOperationCont->getMuPtr()->get(idx);
		if (pOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
		{
			tstring strOperationShunt = _T("0/");
			strOperationShunt += to_tstring(pOperation->getShuntTrackIndex());
			strOperationShunt += _T('$');
			strOperationShunt +=
				g_CdDedJikokuConv.encode(pOperation->getOperationHatsuJikoku());
			strOperationShunt += _T('/');
			if (!pOperation->getOperationChakuJikoku().isNull())
			{
				strOperationShunt +=
					g_CdDedJikokuConv.encode(pOperation->getOperationChakuJikoku());
			}
			strOperationShunt += _T('$');
			strOperationShunt += pOperation->getIsDisplayHatsuJikoku() ? '1' : '0';

			strThisCont.push_back(strOperationShunt);
			/*
		strOperationShunt += joinc(';', pOperationShunt->get)
			tstring strEkijikoku2 = joinc(',', contstrEkijikoku);*/


		}
		else if (pOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
		{
			tstring strOperationConnect = _T("1/");
			strOperationConnect += pOperation->getIsConnectToFront() ? '1' : '0';
			strOperationConnect += _T('$');
			strOperationConnect +=
				g_CdDedJikokuConv.encode(pOperation->getConnectJikoku());

			strThisCont.push_back(strOperationConnect);

			tstring strChildIndex = strParentIndex;
			strChildIndex += _T('.');
			strChildIndex += to_tstring(idx);
			strChildIndex += _T('B');
			vector<vector<tstring>> strChildOperation =
				CentDedBeforeOperationCont_To_string(
					pOperation->getCentDedBeforeOperationCont(),
					strChildIndex);
			for (int idxs = 0; idxs < (int)strChildOperation.size(); idxs++)
			{
				strOperation.push_back(strChildOperation[idxs]);
			}
		}
		else if (pOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
		{
			tstring strOperationRelease = _T("2/");
			strOperationRelease += to_tstring(pOperation->getReleasePos());
			strOperationRelease += _T('$');
			strOperationRelease += to_tstring(pOperation->getReleaseIndexCount());
			strOperationRelease += _T('/');
			strOperationRelease +=
				g_CdDedJikokuConv.encode(pOperation->getReleaseJikoku());

			strThisCont.push_back(strOperationRelease);

			tstring strChildIndex = strParentIndex;
			strChildIndex += _T('.');
			strChildIndex += to_tstring(idx);
			strChildIndex += _T('A');
			vector<vector<tstring>> strChildOperation =
				CentDedAfterOperationCont_To_string(
					pOperation->getCentDedAfterOperationCont(),
					strChildIndex);
			for (int idxs = 0; idxs < (int)strChildOperation.size(); idxs++)
			{
				strOperation.push_back(strChildOperation[idxs]);
			}

		}
		else if (pOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_In)
		{
			//Ver2.05 入出区連携コード追加
			tstring strOperationIn = _T("3/");
			strOperationIn +=
				g_CdDedJikokuConv.encode(pOperation->getInJikoku());
			strOperationIn += _T('$');
			strOperationIn += pOperation->getInOutLinkCode();

			strThisCont.push_back(strOperationIn);

		}
		else if (pOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
		{
			//Ver2.05 入出区連携コード追加
			tstring strOperationOuter = _T("4/");
			strOperationOuter += to_tstring(pOperation->getOuterShuchakuekiIndex());
			strOperationOuter += _T('$');
			strOperationOuter +=
				g_CdDedJikokuConv.encode(pOperation->getHatsuJikoku());
			strOperationOuter += _T('/');
			strOperationOuter +=
				g_CdDedJikokuConv.encode(pOperation->getOuterShuchakuJikoku());
			strOperationOuter += _T('$');
			strOperationOuter += pOperation->getInOutLinkCode();

			strThisCont.push_back(strOperationOuter);

		}
		else if (pOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Junction)
		{

			//Ver2.05 増結表示省略から次列車接続タイプに変更
			tstring strOperationNone = _T("5/");
			strOperationNone +=
				g_CdDedJikokuConv.encode(pOperation->getTerminalJikoku());
			strOperationNone += _T('$');
			strOperationNone += to_tstring(pOperation->getNextJunctionType());

			strThisCont.push_back(strOperationNone);

		}
		else if (pOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_NumberChange)
		{
			//Ver2.00.05 運用番号変更作業を追加
			//Ver2.06.05 運用番号順反転設定を追加
			tstring strOperationNumChange = _T("6/");
			//運用番号が空であることを、運用番号順反転が有効な状態であるとみなすようにする。、
			if (!pOperation->getOperationNumberReverse())
			{
				strOperationNumChange += joinc(';', pOperation->getOperationNumber());
			}

			strThisCont.push_back(strOperationNumChange);
		}
	}
	strOperation[0][1] = joinc(',', strThisCont);
	return strOperation;
}

int CconvCentDed::CentDedAfterOperationCont_From_string(
	CentDedAfterOperationCont * pCentDedAfterOperationCont,
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
					pCNodeContainer);
			}
			else if (strOperationType == _T("3"))
			{
				//Ver2.05 入出区連携コード追加
				aAfterOperation =
					CentDedAfterOperation(
						CentDedAfterOperation::EAOperation::AOperation_In,
						CdDedJikoku(strOperationPara1),
						strOperationPara2);
			}
			else if (strOperationType == _T("4"))
			{
				//Ver2.05 入出区連携コード追加
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
						strOperationPara4);
			}
			else if (strOperationType == _T("5"))
			{
				//Ver2.00.05 増結表示省略設定を追加
				//Ver2.05 増結表示省略から次列車接続タイプに変更
				int iNextJunctionType = stoi(strOperationPara2);
				if (iNextJunctionType < 0 || iNextJunctionType > 3)
				{
					iNextJunctionType = 0;
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
				//Ver2.06.05 運用番号順反転設定を追加

				//strOperationPara1(運用番号)が空の場合は、運用番号順反転設定が有効であるとみなす。
				if (strOperationPara1.empty())
				{
					aAfterOperation =
						CentDedAfterOperation(
							CentDedAfterOperation::EAOperation::AOperation_NumberChange,
							vector<tstring>(),
							true);
				}
				else
				{
					vector<tstring> strOperationNumber =
						splitc<vector<tstring>>(';', strOperationPara1, true);
					aAfterOperation =
						CentDedAfterOperation(
							CentDedAfterOperation::EAOperation::AOperation_NumberChange,
							strOperationNumber,
							false);
				}
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

const CEnumToString<ERessyahoukou>& CconvCentDed::getERessyahoukouToString()
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
const TCHAR nameCanceled[] = _T("Canceled");
//const TCHAR nameRessyaTrack[] = _T("RessyaTrack");
//const TCHAR nameOperationNumber[] = _T("OperationNumber");
//const TCHAR nameSyubetsuChange[] = _T("SyubetsuChange");





int CconvCentDed::CentDedRessya_To_OuPropertiesText( 
	const CentDedRessya* pCentDedRessya , 
	const int iEnableOperation,
	OuPropertiesText::CNodeContainer* pCNodeContainer ) 
{
	int iRv = 0 ;
	// --------------------------------
	//0.IsNull
	bool bIsNull = false ;
	if ( iRv >= 0 )
	{
		bIsNull = pCentDedRessya->isNull() ;
	}

	if ( !bIsNull )
	{
		//1.Ressyahoukou
		if ( iRv >= 0 )
		{
			tstring strValue = getERessyahoukouToString().stringOf( 
				pCentDedRessya->getRessyahoukou() ) ;
			if ( strValue.empty() )
			{
				iRv = -12 ;	//	Ressyahoukou の値が不正です。
			}
			else
			{
				pCNodeContainer->setValue( nameRessyahoukou , 
					strValue ) ;
			}
		}
		//2.RessyasyubetsuIndex ;
		if ( iRv >= 0 )
		{
			pCNodeContainer->setValue( 
				nameRessyasyubetsuIndex , 
				stringOf( 
					pCentDedRessya->getRessyasyubetsuIndex() 
				) 
			) ;
		}


		//4."Ressyabangou" ;
		if ( iRv >= 0 )
		{
			tstring strValue = pCentDedRessya->getRessyabangou() ;
			if ( !strValue.empty() )
			{
				pCNodeContainer->setValue( nameRessyabangou , 
					strValue ) ;
			}
		}
		//5."Ressyamei" ;
		if ( iRv >= 0 )
		{
			tstring strValue = pCentDedRessya->getRessyamei() ;
			if ( !strValue.empty() )
			{
				pCNodeContainer->setValue( nameRessyamei , 
					 strValue) ;
			}
		}
		//6."Gousuu" ;
		if ( iRv >= 0 )
		{
			tstring strValue = pCentDedRessya->getGousuu() ;
			if ( !strValue.empty() )
			{
				pCNodeContainer->setValue( nameGousuu , 
					strValue ) ;
			}
		}
		//3.EkiJikoku3
		if ( iRv >= 0 )
		{
			vector<tstring>	contstrEkijikoku ;
			int iEkiOrder ;
			for ( iEkiOrder = 0 ; 
					iEkiOrder <= pCentDedRessya->getSyuuchakuEki() ; 
					iEkiOrder ++ )
			{
				CentDedEkiJikoku	aCentDedEkiJikoku = 
					pCentDedRessya->getCentDedEkiJikoku( iEkiOrder ) ;
				tstring	strEkijikoku = CentDedEkiJikoku_To_string(
					&aCentDedEkiJikoku ) ;
				
				contstrEkijikoku.push_back( strEkijikoku ) ;
			}
			tstring strEkijikoku2 = joinc( ',' , contstrEkijikoku ) ;
			pCNodeContainer->setValue( nameEkiJikoku3 ,
						strEkijikoku2 ) ; 
		}
		//8.BeforeOperation,AfterOperation
		if (iRv >= 0)
		{
			//vector<tstring>	contstrEkijikoku;
			int iEkiOrder;
			for (iEkiOrder = 0;
				iEkiOrder <= pCentDedRessya->getSyuuchakuEki();
				iEkiOrder++)
			{
				CentDedEkiJikoku	aCentDedEkiJikoku =
					pCentDedRessya->getCentDedEkiJikoku(iEkiOrder);
				if (aCentDedEkiJikoku.getCentDedBeforeOperationCont()->size() > 0)
				{
					tstring strBefore = to_tstring(iEkiOrder) + _T('B');
					vector<vector<tstring>> strBeforeOperation =
						CentDedBeforeOperationCont_To_string(
							aCentDedEkiJikoku.getCentDedBeforeOperationCont(),
							strBefore);
					for (int idxb = 0; idxb < (int)strBeforeOperation.size(); idxb++)
					{
						pCNodeContainer->setValue(strBeforeOperation[idxb][0],
							strBeforeOperation[idxb][1]);
					}
				}

				if (aCentDedEkiJikoku.getCentDedAfterOperationCont()->size() > 0)
				{
					tstring strAfter = to_tstring(iEkiOrder) + _T('A');
					vector<vector<tstring>> strAfterOperation =
						CentDedAfterOperationCont_To_string(
							aCentDedEkiJikoku.getCentDedAfterOperationCont(),
							strAfter);
					for (int idxa = 0; idxa < (int)strAfterOperation.size(); idxa++)
					{
						pCNodeContainer->setValue(strAfterOperation[idxa][0],
							strAfterOperation[idxa][1]);
					}
				}
			}
		}

		//7."Bikou" ;
		if ( iRv >= 0 )
		{
			tstring strValue = pCentDedRessya->getBikou() ;
			if ( !strValue.empty() )
			{
				pCNodeContainer->setValue( nameBikou , 
					strValue ) ;
			}
		}

		//8."Canceled"
		if (iRv >= 0)
		{
			if (pCentDedRessya->isCanceled())
			{
				pCNodeContainer->setValue(nameCanceled, _T("1"));
			}
		}
		//当面保留
		////9."OperationNumber" ;
		//if (iRv >= 0 && iEnableOperation>0)
		//{
		//	tstring strValue = pCentDedRessya->getOperationNumber();
		//	if (!strValue.empty())
		//	{
		//		pCNodeContainer->setValue(nameOperationNumber,
		//			strValue);
		//	}
		//}
	}
	// --------------------------------
	return ( iRv ) ;
}

int CconvCentDed::CentDedRessya_From_OuPropertiesText( 
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
		//8."Canceled"
		if (iRv >= 0) {
			tstring	strValue = pCNodeContainer->getValue(nameCanceled);
			pCentDedRessya->setIsCanceled(strValue == _T("1"));
		}
	}
	return ( iRv ) ;
}


// ********************************
//	CentDedRessyaCont
// ********************************
const TCHAR nameRessya[]=_T("Ressya") ;

int CconvCentDed::CentDedRessyaCont_To_OuPropertiesText( 
	const CentDedRessyaCont* pCentDedRessyaCont ,
	const int iEnableOperation,
	OuPropertiesText::CNodeContainer* pCNodeContainer ) 
{
	int iRv = 0 ;
	
		
	int idxRessya ;
	for ( idxRessya = 0 ; idxRessya < pCentDedRessyaCont->size() ; 
			idxRessya ++ )
	{
		Ou<CDirectory> pCDirectory = OuNew<CDirectory>( new CDirectory( nameRessya ) ) ;

		const CentDedRessya*	pCentDedRessya = 
			pCentDedRessyaCont->getMuPtr()->get( idxRessya );
		int iResult = CentDedRessya_To_OuPropertiesText( 
			pCentDedRessya , iEnableOperation , pCDirectory->getCNodeContainer() ) ;
		//	-	-12 ;	//	Ressyahoukou の値が不正です。
		if ( iResult < 0 )
		{
			iRv = iResult ;
		}
		else
		{
			pCNodeContainer->insert( pCDirectory ) ;
		}
	}
	
	return ( iRv ) ;
}
int CconvCentDed::CentDedRessyaCont_From_OuPropertiesText( 
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
const TCHAR namePatternDiagramPreviewEnable[] = _T("PatternDiagramPreviewEnable");
const TCHAR namePatternDiagramPreviewCycleSecond[] = _T("PatternDiagramPreviewCycleSecond");

int CconvCentDed::CentDedDia_To_OuPropertiesText( 
			const CentDedDia* pCentDedDia ,
			const int iEnableOperation,
			OuPropertiesText::CNodeContainer* pCNodeContainer ) 
{
	int iRv = 0 ;

	//1.DiaName
	if ( iRv >= 0 )
	{
		pCNodeContainer->setValue( nameDiaName , 
			pCentDedDia->getName() ) ;
	}
	//2.MainBackColorIndex
	if (iRv >= 0)
	{
		pCNodeContainer->setValue(nameMainBackColorIndex,
			stringOf(pCentDedDia->getMainBackColorIndex()));
	}
	//2.1.SubBackColorIndex
	if (iRv >= 0)
	{
		pCNodeContainer->setValue(nameSubBackColorIndex,
			stringOf(pCentDedDia->getSubBackColorIndex()));
	}
	//2.2.BackPatternIndex
	if (iRv >= 0)
	{
		pCNodeContainer->setValue(nameBackPatternIndex,
			stringOf(pCentDedDia->getBackPatternIndex()));
	}
	//2.3.PatternDiagramPreviewEnable
	if (iRv >= 0)
	{
		if (pCentDedDia->getPatternDiagramPreviewEnable())
		{
			pCNodeContainer->setValue(namePatternDiagramPreviewEnable, _T("1"));
		}
	}
	//2.4.PatternDiagramPreviewCycleSecond
	if (iRv >= 0)
	{
		pCNodeContainer->setValue(namePatternDiagramPreviewCycleSecond,
			stringOf(pCentDedDia->getPatternDiagramPreviewCycleSecond()));
	}
	//3.Kudari
	//  Nobori
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
			
			Ou<CDirectory> pCDirectory = OuNew<CDirectory>( 
				new CDirectory( strRessyahoukou ) ) ;
			int iResult = CentDedRessyaCont_To_OuPropertiesText( 
				pCentDedDia->getCentDedRessyaCont( (ERessyahoukou)iRessyahoukou ) , 
				iEnableOperation,
				pCDirectory->getCNodeContainer() );
			//iResult = 
			//	-12 ;	//	Ressyahoukou の値が不正です。
			if ( iResult < 0 )
			{
				iRv = iResult ;
			}
			else
			{
				pCNodeContainer->insert( pCDirectory ) ;
			}
		}
	}
	
	return ( iRv ) ;
}



int CconvCentDed::CentDedDia_From_OuPropertiesText( 
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
	//2.3.PatternDiagramPreviewEnable
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(namePatternDiagramPreviewEnable);
		pCentDedDia->setPatternDiagramPreviewEnable(strValue == _T("1"));
	}
	//2.4.PatternDiagramPreviewCycleSecond
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(namePatternDiagramPreviewCycleSecond);
		if (strValue.length() != 0)
		{
			pCentDedDia->setPatternDiagramPreviewCycleSecond(intOf(strValue));
		}
		else
		{
			pCentDedDia->setPatternDiagramPreviewCycleSecond(600);
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
	
int CconvCentDed::CentDedDiaCont_To_OuPropertiesText( 
			const CentDedDiaCont* pCentDedDiaCont ,
			const int iEnableOperation,
			OuPropertiesText::CNodeContainer* pCNodeContainer ) 
{
	int iRv = 0 ;
	for ( int idxDia = 0 ; iRv >= 0 && idxDia < pCentDedDiaCont->size() ; idxDia ++ )
	{
		Ou<CDirectory> pCDirectory = OuNew<CDirectory>( new CDirectory( nameDia ) ) ;
		CentDedDia aCentDedDia = pCentDedDiaCont->get( idxDia ) ; 
		if ( iRv >= 0 )
		{
			int iResult = CentDedDia_To_OuPropertiesText( 
				&aCentDedDia , 
				iEnableOperation,
				pCDirectory->getCNodeContainer() ) ;
			if ( iResult < 0 )
			{
				//	-	-12 ;	//	DiagramEkiatsukai の値が不正です。
				iRv = iResult ;
			}
			else
			{
				pCNodeContainer->insert( pCDirectory ) ;
			}
		}
	}
	return iRv ;
}
	
int CconvCentDed::CentDedDiaCont_From_OuPropertiesText( 
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
const TCHAR nameOperationCrossKitenJikoku[] = _T("OperationCrossKitenJikoku");
const TCHAR nameKijunDiaIndex[] = _T("KijunDiaIndex");
const TCHAR nameDisableHiddenSyubetsu[] = _T("DisableHiddenSyubetsu");
const TCHAR nameComment[] = _T("Comment") ;


int CconvCentDed::CentDedRosen_To_OuPropertiesText( 
			const CentDedRosen* pCentDedRosen , 
			OuPropertiesText::CNodeContainer* pCNodeContainer ) 
{
	int iRv = 0 ;

	//1.Rosenmei
	if ( iRv >= 0 )
	{
		pCNodeContainer->setValue( nameRosenmei , 
			pCentDedRosen->getName() ) ;
	}
	//1.1.KudariDiaAlias
	if (iRv >= 0)
	{
		pCNodeContainer->setValue(nameKudariDiaAlias,
			pCentDedRosen->getKudariDiaAlias());
	}
	//1.2.NoboriDiaAlias
	if (iRv >= 0)
	{
		pCNodeContainer->setValue(nameNoboriDiaAlias,
			pCentDedRosen->getNoboriDiaAlias());
	}
	//2.Eki[]
	if ( iRv >= 0 )
	{
		int iResult = CentDedEkiCont_To_OuPropertiesText( 
			*pCentDedRosen->getCentDedEkiCont() , 
			pCNodeContainer ) ;
		//	-	-22 ;	//	Ekijikokukeisiki の値が不正です。
		//	-	-32 ;	//	Ekikibo の値が不正です。
		if ( iResult < 0 )
		{
			//	-	-22 ;	//	Ekijikokukeisiki の値が不正です。
			//	-	-32 ;	//	Ekikibo の値が不正です。
			iRv = iResult ;
		}
	}
	

	//3.Ressyasyubetsu[]
	if ( iRv >= 0 )
	{
		int iResult = CentDedRessyasyubetsuCont_To_OuPropertiesText( 
			*pCentDedRosen->getCentDedRessyasyubetsuCont() , 
			pCNodeContainer ) ;
		//	-	-11 ;	//	Syubetsumei が指定されていません。
		//	-	-52 ;	//	DiagramSenStyle の値が不正です。
		if ( iResult < 0 )
		{
			//	-	-111 ;	//	Syubetsumei が指定されていません。
			//	-	-152 ;	//	DiagramSenStyle の値が不正です。
			iRv = iResult - 100 ;
		}
	}
	
	//4.Dia[]
	if ( iRv >= 0 )
	{
		int iResult = CentDedDiaCont_To_OuPropertiesText(
			pCentDedRosen->getCentDedDiaCont(),
			pCentDedRosen->getEnableOperation() > 1,
			pCNodeContainer);
		//	-	-12 ;	//	DiagramEkiatsukai の値が不正です。
		if ( iResult < 0 )
		{
			//	-	-212 ;	//	DiagramEkiatsukai の値が不正です。
			iRv = iResult - 200 ;
		}
	}
	//5.KitenJikoku
	if ( iRv >= 0 )
	{
		pCNodeContainer->setValue( nameKitenJikoku , 
			g_CdDedJikokuConv.encode( pCentDedRosen->getKitenJikoku() ) ) ;
		
	}
	//6.DiagramDgrYZahyouKyoriDefault
	if ( iRv >= 0 )
	{
		pCNodeContainer->setValue( nameDiagramDgrYZahyouKyoriDefault , 
			stringOf( pCentDedRosen->getDiagramDgrYZahyouKyoriDefault() ) ) ;
	}
	//6.1.EnableOperation
	if (iRv >= 0)
	{
		if (pCentDedRosen->getEnableOperation()>0)
		{
			////pCNodeContainer->setValue(nameEnableOperation, _T("1"));
			pCNodeContainer->setValue(nameEnableOperation,
				stringOf(pCentDedRosen->getEnableOperation()));
		}
	}
	//6.2.OperationNumberReverse
	if (iRv >= 0)
	{
		if (pCentDedRosen->getOperationNumberReverse())
		{
			pCNodeContainer->setValue(nameOperationNumberReverse, _T("1"));
		}
	}
	//6.3.OperationCrossKitenJikoku
	if (iRv >= 0)
	{
		if (pCentDedRosen->getOperationCrossKitenJikoku())
		{
			pCNodeContainer->setValue(nameOperationCrossKitenJikoku, _T("1"));
		}
	}
	//6.4.KijunDiaIndex
	if (iRv >= 0)
	{
		pCNodeContainer->setValue(nameKijunDiaIndex,
			stringOf(pCentDedRosen->getKijunDiaIndex()));
	}
	//6.5.DisableHiddenSyubetsu
	if (iRv >= 0)
	{
		if (pCentDedRosen->getDisableHiddenSyubetsu())
		{
			pCNodeContainer->setValue(nameDisableHiddenSyubetsu, _T("1"));
		}
	}
	//7.Comment
	if ( iRv >= 0 )
	{
		pCNodeContainer->setValue( nameComment ,pCentDedRosen->getComment() ) ;
	}




	return ( iRv ) ;
}

int CconvCentDed::CentDedRosen_From_OuPropertiesText( 
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
	//6.3.OperationCrossKitenJikoku
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(nameOperationCrossKitenJikoku);
		pCentDedRosen->setOperationCrossKitenJikoku(strValue == _T("1"));
	}
	//6.4.KijunDiaIndex
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(nameKijunDiaIndex);
		if (strValue.length() == 0)
		{
			int iKijunDiaIndex = 0;
			const CentDedDiaCont* pCentDedDiaCont = pCentDedRosen->getCentDedDiaCont();
			for (int idx = 0; idx < pCentDedDiaCont->size(); idx++)
			{
				if (pCentDedDiaCont->get(idx).getName() == _T("基準運転時分"))
				{
					iKijunDiaIndex = idx;
					break;
				}
			}
			pCentDedRosen->setKijunDiaIndex(iKijunDiaIndex);
		}
		else
		{
			pCentDedRosen->setKijunDiaIndex(intOf(strValue));
		}
	}
	//6.5.DisableHiddenSyubetsu
	if (iRv >= 0)
	{
		tstring	strValue = pCNodeContainer->getValue(nameDisableHiddenSyubetsu);
		pCentDedRosen->setDisableHiddenSyubetsu(strValue == _T("1"));
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
		pCentDedRosen->getCentDedEkiCont()->adjustCrossingCheckRuleByEkiEdit();
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


