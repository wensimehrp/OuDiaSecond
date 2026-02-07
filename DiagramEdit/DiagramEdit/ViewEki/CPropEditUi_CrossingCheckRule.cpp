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
//	$Id: CPropEditUi_CrossingCheckRule.cpp
// ****************************************************************

/** @file */
#include "stdafx.h"
#include "CPropEditUi_CrossingCheckRule.h"
#include <tchar.h>

namespace ViewEki {


	// ********************************
	//@name エラーメッセージ
	// ********************************
	/// 前動作の移動元番線を一つ以上選択してください。
const TCHAR* const CPropEditUi_CrossingCheckRule::ERRMSG_EMPTY_BEFOREFROM = _T("Before-From-List no select.") ;

/// 前動作の移動先番線を一つ以上選択してください。
const TCHAR* const CPropEditUi_CrossingCheckRule::ERRMSG_EMPTY_BEFORETO = _T("Before-To-List no select.");

/// 後動作の移動元番線を一つ以上選択してください。
const TCHAR* const CPropEditUi_CrossingCheckRule::ERRMSG_EMPTY_AFTERFROM = _T("After-From-List no select.");

/// 後動作の移動先番線を一つ以上選択してください。
const TCHAR* const CPropEditUi_CrossingCheckRule::ERRMSG_EMPTY_AFTERTO = _T("After-To-List no select.");

/// 時隔上限の入力が正しくありません。
const TCHAR* const CPropEditUi_CrossingCheckRule::ERRMSG_INVALID_HEADWAY = _T("Headway is invalid.");

/// 時隔下限の入力が正しくありません。
const TCHAR* const CPropEditUi_CrossingCheckRule::ERRMSG_INVALID_HEADWAYMINIMUM = _T("Headway is invalid.");

/// 時隔の大小関係が正しくありません。
const TCHAR* const CPropEditUi_CrossingCheckRule::ERRMSG_INVALID_HEADWAYRELATION = _T("Headway relation is invalid.");

 //ルール名が空白です。
const TCHAR* const CPropEditUi_CrossingCheckRule::ERRMSG_EMPTY_CAPTION = _T("Rule-Name is empty.");


//	// ================================
//	//@name 下請関数
//	// ================================
//
void CPropEditUi_CrossingCheckRule::InitUiData(UIDATA * pUiData)
{
	//const CentDedEki* pTarget = m_pTarget->get(0);
	//pUiData->iEkijikokukeisiki = (int)pTarget->getEkijikokukeisiki();
	//EkiTrack2 aEkiTrack2;

	//aEkiTrack2.strTrackName = _T("1番線");
	//aEkiTrack2.strTrackRyakusyou = _T("1");
	//aEkiTrack2.strTrackNoboriRyakusyou = _T("");
	//aEkiTrack2.iMainTrack = 1;
	//pUiData->sEkiTrack2.push_back(aEkiTrack2);

	//aEkiTrack2.strTrackName = _T("2番線");
	//aEkiTrack2.strTrackRyakusyou = _T("2");
	//aEkiTrack2.strTrackNoboriRyakusyou = _T("");
	//aEkiTrack2.iMainTrack = 2;
	//pUiData->sEkiTrack2.push_back(aEkiTrack2);

}
	// ================================
	//	オーバーライトの必要なメソッド1-Targetに依存する処理
	// ================================
void CPropEditUi_CrossingCheckRule::UiDataFromTarget( UIDATA* pUiData ) 
{
	pUiData->ContCrossingCheckRule = m_pTarget->getCrossingCheckRuleCont();
	if (!pUiData->ContCrossingCheckRule.empty())
	{
		pUiData->iListSelected = 0;
	}
}
	
void CPropEditUi_CrossingCheckRule::AdjustUiData( 
		UIDATA* pUiData , 
		const UIDATA* pUiDataPrev , 
		bool bStartEdit )
{
	/**
		iUiOperationが0(詳細変更)のときに行われます。
		・到着時刻・出発時刻の違いによる、移動前後番線の制限
		・停車・通過の違いによる、移動前後番線の制限
	*/
	if (pUiData->iUiOperation == 0 &&
		pUiData->iListSelected >= 0)
	{
		CrossingCheckRule* pCrossingCheckRule = &pUiData->ContCrossingCheckRule[pUiData->iListSelected];
		const CrossingCheckRule* pCrossingCheckRulePrev = &pUiDataPrev->ContCrossingCheckRule[pUiData->iListSelected];
		if (bStartEdit || pCrossingCheckRule->BeforeFromTrackContentCont.size() != pCrossingCheckRulePrev->BeforeFromTrackContentCont.size())
		{
			/**
				Listの選択状態が変わったときは、到着・出発、停車・通過の状態に合致しないものについて、選択状態を解除します
				移動元番線の場合、出発時刻の場合は番線以外を、到着時刻・通過の場合は番線を解除します。
			*/
			if (!pCrossingCheckRule->bBeforeIsArrival)
			{
				for (int idx = pCrossingCheckRule->BeforeFromTrackContentCont.size() - 1; idx >= 0; idx--)
				{
					if (pCrossingCheckRule->BeforeFromTrackContentCont[idx].eTrackType != ETrackType::TrackType_Track)
					{
						pCrossingCheckRule->BeforeFromTrackContentCont.erase(
							pCrossingCheckRule->BeforeFromTrackContentCont.begin() + idx);
					}
				}
			}
			if (pCrossingCheckRule->bBeforeIsArrival && pCrossingCheckRule->bBeforeIsTsuuka)
			{
				for (int idx = pCrossingCheckRule->BeforeFromTrackContentCont.size() - 1; idx >= 0; idx--)
				{
					if (pCrossingCheckRule->BeforeFromTrackContentCont[idx].eTrackType == ETrackType::TrackType_Track)
					{
						pCrossingCheckRule->BeforeFromTrackContentCont.erase(
							pCrossingCheckRule->BeforeFromTrackContentCont.begin() + idx);
					}
				}
			}
		}
		if (bStartEdit || pCrossingCheckRule->BeforeToTrackContentCont.size() != pCrossingCheckRulePrev->BeforeToTrackContentCont.size())
		{
			/**
				Listの選択状態が変わったときは、到着・出発、停車・通過の状態に合致しないものについて、選択状態を解除します
				移動先番線の場合、到着時刻の場合は番線以外を、出発時刻・通過の場合は番線を解除します。
			*/
			if (pCrossingCheckRule->bBeforeIsArrival)
			{
				for (int idx = pCrossingCheckRule->BeforeToTrackContentCont.size() - 1; idx >= 0; idx--)
				{
					if (pCrossingCheckRule->BeforeToTrackContentCont[idx].eTrackType != ETrackType::TrackType_Track)
					{
						pCrossingCheckRule->BeforeToTrackContentCont.erase(
							pCrossingCheckRule->BeforeToTrackContentCont.begin() + idx);
					}
				}
			}
			if (!pCrossingCheckRule->bBeforeIsArrival && pCrossingCheckRule->bBeforeIsTsuuka)
			{
				for (int idx = pCrossingCheckRule->BeforeToTrackContentCont.size() - 1; idx >= 0; idx--)
				{
					if (pCrossingCheckRule->BeforeToTrackContentCont[idx].eTrackType == ETrackType::TrackType_Track)
					{
						pCrossingCheckRule->BeforeToTrackContentCont.erase(
							pCrossingCheckRule->BeforeToTrackContentCont.begin() + idx);
					}
				}
			}
		}
		if (bStartEdit || pCrossingCheckRule->AfterFromTrackContentCont.size() != pCrossingCheckRulePrev->AfterFromTrackContentCont.size())
		{
			/**
				Listの選択状態が変わったときは、到着・出発、停車・通過の状態に合致しないものについて、選択状態を解除します
				移動元番線の場合、出発時刻の場合は番線以外を、到着時刻・通過の場合は番線を解除します。
			*/
			if (!pCrossingCheckRule->bAfterIsArrival)
			{
				for (int idx = pCrossingCheckRule->AfterFromTrackContentCont.size() - 1; idx >= 0; idx--)
				{
					if (pCrossingCheckRule->AfterFromTrackContentCont[idx].eTrackType != ETrackType::TrackType_Track)
					{
						pCrossingCheckRule->AfterFromTrackContentCont.erase(
							pCrossingCheckRule->AfterFromTrackContentCont.begin() + idx);
					}
				}
			}
			if (pCrossingCheckRule->bAfterIsArrival && pCrossingCheckRule->bAfterIsTsuuka)
			{
				for (int idx = pCrossingCheckRule->AfterFromTrackContentCont.size() - 1; idx >= 0; idx--)
				{
					if (pCrossingCheckRule->AfterFromTrackContentCont[idx].eTrackType == ETrackType::TrackType_Track)
					{
						pCrossingCheckRule->AfterFromTrackContentCont.erase(
							pCrossingCheckRule->AfterFromTrackContentCont.begin() + idx);
					}
				}
			}
		}
		if (bStartEdit || pCrossingCheckRule->AfterToTrackContentCont.size() != pCrossingCheckRulePrev->AfterToTrackContentCont.size())
		{
			/**
				Listの選択状態が変わったときは、到着・出発、停車・通過の状態に合致しないものについて、選択状態を解除します
				移動先番線の場合、到着時刻の場合は番線以外を、出発時刻・通過の場合は番線を解除します。
			*/
			if (pCrossingCheckRule->bAfterIsArrival)
			{
				for (int idx = pCrossingCheckRule->AfterToTrackContentCont.size() - 1; idx >= 0; idx--)
				{
					if (pCrossingCheckRule->AfterToTrackContentCont[idx].eTrackType != ETrackType::TrackType_Track)
					{
						pCrossingCheckRule->AfterToTrackContentCont.erase(
							pCrossingCheckRule->AfterToTrackContentCont.begin() + idx);
					}
				}
			}
			if (!pCrossingCheckRule->bAfterIsArrival && pCrossingCheckRule->bAfterIsTsuuka)
			{
				for (int idx = pCrossingCheckRule->AfterToTrackContentCont.size() - 1; idx >= 0; idx--)
				{
					if (pCrossingCheckRule->AfterToTrackContentCont[idx].eTrackType == ETrackType::TrackType_Track)
					{
						pCrossingCheckRule->AfterToTrackContentCont.erase(
							pCrossingCheckRule->AfterToTrackContentCont.begin() + idx);
					}
				}
			}
		}
		if (bStartEdit || pCrossingCheckRule->bBeforeIsArrival != pCrossingCheckRulePrev->bBeforeIsArrival)
		{
			if (pCrossingCheckRule->bBeforeIsTsuuka)
			{
				//通過の場合は、全てを選択解除します
				pCrossingCheckRule->BeforeFromTrackContentCont.clear();
				pCrossingCheckRule->BeforeToTrackContentCont.clear();

			}
			else if (pCrossingCheckRule->bBeforeIsArrival)
			{
				//前動作が出発時刻→到着時刻に変わった場合、移動先番線のうち、番線以外を選択解除します。
				for (int idx = pCrossingCheckRule->BeforeToTrackContentCont.size() - 1; idx >= 0; idx--)
				{
					if (pCrossingCheckRule->BeforeToTrackContentCont[idx].eTrackType != ETrackType::TrackType_Track)
					{
						pCrossingCheckRule->BeforeToTrackContentCont.erase(
							pCrossingCheckRule->BeforeToTrackContentCont.begin() + idx);
					}
				}
			}
			else
			{
				//前動作が到着時刻→出発時刻に変わった場合、移動元番線のうち、番線以外を選択解除します。
				for (int idx = pCrossingCheckRule->BeforeFromTrackContentCont.size() - 1; idx >= 0; idx--)
				{
					if (pCrossingCheckRule->BeforeFromTrackContentCont[idx].eTrackType != ETrackType::TrackType_Track)
					{
						pCrossingCheckRule->BeforeFromTrackContentCont.erase(
							pCrossingCheckRule->BeforeFromTrackContentCont.begin() + idx);
					}
				}
			}
		}
		
		if (bStartEdit || pCrossingCheckRule->bAfterIsArrival != pCrossingCheckRulePrev->bAfterIsArrival)
		{
			if (pCrossingCheckRule->bAfterIsTsuuka)
			{
				//通過の場合は、全てを選択解除します
				pCrossingCheckRule->AfterFromTrackContentCont.clear();
				pCrossingCheckRule->AfterToTrackContentCont.clear();

			}
			else if (pCrossingCheckRule->bAfterIsArrival)
			{
				//前動作が出発時刻→到着時刻に変わった場合、移動先番線のうち、番線以外を選択解除します。
				for (int idx = pCrossingCheckRule->AfterToTrackContentCont.size() - 1; idx >= 0; idx--)
				{
					if (pCrossingCheckRule->AfterToTrackContentCont[idx].eTrackType != ETrackType::TrackType_Track)
					{
						pCrossingCheckRule->AfterToTrackContentCont.erase(
							pCrossingCheckRule->AfterToTrackContentCont.begin() + idx);
					}
				}
			}
			else
			{
				//前動作が到着時刻→出発時刻に変わった場合、移動元番線のうち、番線以外を選択解除します。
				for (int idx = pCrossingCheckRule->AfterFromTrackContentCont.size() - 1; idx >= 0; idx--)
				{
					if (pCrossingCheckRule->AfterFromTrackContentCont[idx].eTrackType != ETrackType::TrackType_Track)
					{
						pCrossingCheckRule->AfterFromTrackContentCont.erase(
							pCrossingCheckRule->AfterFromTrackContentCont.begin() + idx);
					}
				}
			}
		}
		if (bStartEdit || pCrossingCheckRule->bBeforeIsTsuuka != pCrossingCheckRulePrev->bBeforeIsTsuuka)
		{
			//通過・停車が切り替わったときは、停車→通過になったときのみ、出発時刻の移動先の番線、到着時刻時の移動前の番線を削除します。
			if (pCrossingCheckRule->bBeforeIsTsuuka)
			{
				if (pCrossingCheckRule->bBeforeIsArrival)
				{
					for (int idx = pCrossingCheckRule->BeforeFromTrackContentCont.size() - 1; idx >= 0; idx--)
					{
						if (pCrossingCheckRule->BeforeFromTrackContentCont[idx].eTrackType == ETrackType::TrackType_Track)
						{
							pCrossingCheckRule->BeforeFromTrackContentCont.erase(
								pCrossingCheckRule->BeforeFromTrackContentCont.begin() + idx);
						}
					}
				}
				else
				{
					for (int idx = pCrossingCheckRule->BeforeToTrackContentCont.size() - 1; idx >= 0; idx--)
					{
						if (pCrossingCheckRule->BeforeToTrackContentCont[idx].eTrackType == ETrackType::TrackType_Track)
						{
							pCrossingCheckRule->BeforeToTrackContentCont.erase(
								pCrossingCheckRule->BeforeToTrackContentCont.begin() + idx);
						}
					}
				}
			}
		}
		if (bStartEdit || pCrossingCheckRule->bAfterIsTsuuka != pCrossingCheckRulePrev->bAfterIsTsuuka)
		{
			//通過・停車が切り替わったときは、停車→通過になったときのみ、出発時刻の移動先の番線、到着時刻時の移動前の番線を削除します。
			if (pCrossingCheckRule->bAfterIsTsuuka)
			{
				if (pCrossingCheckRule->bAfterIsArrival)
				{
					for (int idx = pCrossingCheckRule->AfterFromTrackContentCont.size() - 1; idx >= 0; idx--)
					{
						if (pCrossingCheckRule->AfterFromTrackContentCont[idx].eTrackType == ETrackType::TrackType_Track)
						{
							pCrossingCheckRule->AfterFromTrackContentCont.erase(
								pCrossingCheckRule->AfterFromTrackContentCont.begin() + idx);
						}
					}
				}
				else
				{
					for (int idx = pCrossingCheckRule->AfterToTrackContentCont.size() - 1; idx >= 0; idx--)
					{
						if (pCrossingCheckRule->AfterToTrackContentCont[idx].eTrackType == ETrackType::TrackType_Track)
						{
							pCrossingCheckRule->AfterToTrackContentCont.erase(
								pCrossingCheckRule->AfterToTrackContentCont.begin() + idx);
						}
					}
				}
			}
		}
	}
	
}

int CPropEditUi_CrossingCheckRule::CheckUiData( 
		bool bNewItem , 
		const UIDATA* pUiData , 
		const UIDATA* pUiDataStartEdit ) 
{
	int iRv = 0 ; 
	for (int idx = 0; idx < (int)pUiData->ContCrossingCheckRule.size(); idx++)
	{
		const CrossingCheckRule* pCrossingCheckRule = &pUiData->ContCrossingCheckRule[idx];
		tstring strInfo = _T("[") + to_tstring(idx + 1)+ _T("]");

		if (iRv >= 0)
		{
			if (pCrossingCheckRule->strCaption.empty())
			{
				ShowError(ERRMSG_EMPTY_CAPTION, strInfo);
				SetFocus(offsetof(CrossingCheckRule, strCaption));
				iRv = -1;	//	ルール名が空白です。
			}
		}
		if (iRv >= 0)
		{

			if (pCrossingCheckRule->iHeadwaySecond <= 0 || pCrossingCheckRule->iHeadwaySecond > 7200)
			{
				ShowError(ERRMSG_INVALID_HEADWAY, strInfo);
				SetFocus(offsetof(CrossingCheckRule, iHeadwaySecond));
				iRv = -2;	//	時隔上限の入力が正しくありません。
			}
		}
		if (iRv >= 0)
		{

			if (pCrossingCheckRule->iHeadwaySecondMinimum < -7200 || pCrossingCheckRule->iHeadwaySecondMinimum > 7199)
			{
				ShowError(ERRMSG_INVALID_HEADWAYMINIMUM, strInfo);
				SetFocus(offsetof(CrossingCheckRule, iHeadwaySecondMinimum));
				iRv = -3;	//	時隔下限の入力が正しくありません。
			}
		}
		if (iRv >= 0)
		{

			if (pCrossingCheckRule->iHeadwaySecond <= pCrossingCheckRule->iHeadwaySecondMinimum)
			{
				ShowError(ERRMSG_INVALID_HEADWAYRELATION, strInfo);
				SetFocus(offsetof(CrossingCheckRule, iHeadwaySecond));
				iRv = -4;	//	時隔の大小関係が正しくありません。
			}
		}
		if (iRv >= 0)
		{

			if (pCrossingCheckRule->BeforeFromTrackContentCont.empty())
			{
				ShowError(ERRMSG_EMPTY_BEFOREFROM, strInfo);
				SetFocus(offsetof(CrossingCheckRule, BeforeFromTrackContentCont));
				iRv = -11;	//	前動作の移動元番線を一つ以上選択してください。
			}
		}
		if (iRv >= 0)
		{

			if (pCrossingCheckRule->BeforeToTrackContentCont.empty())
			{
				ShowError(ERRMSG_EMPTY_BEFORETO, strInfo);
				SetFocus(offsetof(CrossingCheckRule, BeforeToTrackContentCont));
				iRv = -12;	//	前動作の移動先番線を一つ以上選択してください。
			}
		}
		if (iRv >= 0)
		{

			if (pCrossingCheckRule->AfterFromTrackContentCont.empty())
			{
				ShowError(ERRMSG_EMPTY_AFTERFROM, strInfo);
				SetFocus(offsetof(CrossingCheckRule, AfterFromTrackContentCont));
				iRv = -13;	//	後動作の移動元番線を一つ以上選択してください。
			}
		}
		if (iRv >= 0)
		{

			if (pCrossingCheckRule->AfterToTrackContentCont.empty())
			{
				ShowError(ERRMSG_EMPTY_AFTERTO, strInfo);
				SetFocus(offsetof(CrossingCheckRule, AfterToTrackContentCont));
				iRv = -14;	//	後動作の移動先番線を一つ以上選択してください。
			}
		}
	}
	return iRv ;
}




int CPropEditUi_CrossingCheckRule::UiDataToTarget( 
		bool bNewItem , 
		const UIDATA* pUiData , 
		const UIDATA* pUiDataStartEdit ) 
{
	int iRv = 0 ;
	m_pTarget->setCrossingCheckRule(pUiData->ContCrossingCheckRule);
	return iRv ;
}


	// ********************************
	//	コンストラクタ
	// ********************************
CPropEditUi_CrossingCheckRule::CPropEditUi_CrossingCheckRule( 
	CentDedEki* pTarget ,
	int iEkiIndex)
	: CPropEditUi2( false ) 
	, m_pTarget( pTarget ) 
	, m_iEkiIndex(iEkiIndex)
{	
};

} //namespace ViewEki 



