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
//	CDedOperationConnecter.cpp
// ****************************************************************
*/
/** @file */
#include "stdafx.h"
//#include <algorithm>
#include "CDedOperationConnecter.h"
//#include "NsMu\CaMui.h"
//#include "NsMu\CMup_vector.h"
//#include "NsMu\CaMup_vector.h"
//#include "..\entDgr\CentDedDgrRessya.h"
#include "CdDedRessyaProperty.h"
#include "NsOu/dynamic_castOu.h"
#include <list>
#include <chrono>



namespace entDed {
	using namespace std;

	// ****************************************************************
	//	CDedOperationConnecter
	// ****************************************************************
		// --------------------------------
		//@name 下請関数
		// --------------------------------





		// ********************************
		//	コンストラクタ
		// ********************************
CDedOperationConnecter::CDedOperationConnecter(
	const CentDedRosen* pDedRosen,
	CentDedDia* pDedDia) :
	m_pDedRosen(pDedRosen),
	m_pDedDia(pDedDia)
{
	//auto p1 = std::chrono::high_resolution_clock::now();

	m_KitenJikoku = m_pDedRosen->getKitenJikoku();
	m_bOperationCrossKitenJikoku = m_pDedRosen->getOperationCrossKitenJikoku();

	if (m_pDedDia->getPatternDiagramPreviewEnable())
	{
		m_iPatternDiagramPreviewCycleSecond = m_pDedDia->getPatternDiagramPreviewCycleSecond();
		m_iPatternDiagramPreviewRange = m_pDedDia->getPatternDiagramPreviewRange();
		operationConnectPatternDiagram();
	}
	else if (m_pDedRosen->getEnableOperation() == 2)
	{
		m_bOperationNumberReverse = m_pDedRosen->getOperationNumberReverse();
		operationConnect();
	}
	else
	{
		operationConnectLight();
	}

	//auto p2 = std::chrono::high_resolution_clock::now();

	//auto count1 = std::chrono::duration_cast<std::chrono::milliseconds>(p2 - p1).count();
}

CDedOperationConnecter::CDedOperationConnecter(
	const CentDedRosen * pDedRosen,
	CentDedDia * pDedDia,
	const CdDedJikoku aCdDedJikokuMin,
	const CdDedJikoku aCdDedJikokuMax,
	const ERessyahoukou eRessyahoukouEdit,
	const int iIndexDst, const int iSizeDst, const int iAddSize) :
	m_pDedRosen(pDedRosen),
	m_pDedDia(pDedDia)
{
	m_KitenJikoku = m_pDedRosen->getKitenJikoku();
	m_bOperationCrossKitenJikoku = m_pDedRosen->getOperationCrossKitenJikoku();
	//auto p1 = std::chrono::high_resolution_clock::now();
	//if (m_pDedRosen->getiEnableOperation() == 2)
	//{
		operationConnect();
	//}
	//else
	//{
	//	m_CentDedDgrDia.readCentDedRosen(
	//		m_pDedRosen,
	//		m_pDedDia,
	//		true);

	//	operationUpdate(
	//		aCdDedJikokuMin, aCdDedJikokuMax,
	//		eRessyahoukouEdit, iIndexDst,
	//		iSizeDst, iAddSize);
	//}

	//auto p2 = std::chrono::high_resolution_clock::now();

	//auto count1 = std::chrono::duration_cast<std::chrono::milliseconds>(p2 - p1).count();
}

CDedOperationConnecter::~CDedOperationConnecter()
{
}

	// ********************************
	//@name 操作
	// ********************************
	

void CDedOperationConnecter::InsertRessyaElement(
	const int iEkiIndexofContExist,
	const int iRessyaTrackIndex,
	const RessyaElement aRessyaElement)
{
	list<RessyaElement>* pRessyaExist = &m_contRessyaExist[iEkiIndexofContExist][iRessyaTrackIndex];
	if (pRessyaExist->empty())
	{
		pRessyaExist->push_back(aRessyaElement);
		return;
	}
	for (list<RessyaElement>::iterator itr = pRessyaExist->begin();
		itr != pRessyaExist->end(); itr++)
	{
		if (aRessyaElement.sRessyaProperty.getJikoku().compare(itr->sRessyaProperty.getJikoku(), m_KitenJikoku) < 0)
		{
			//aRessyaElementが比較対象よりも前方にある場合、その位置に挿入します
			pRessyaExist->insert(itr, aRessyaElement);
			return;
		}

		if (aRessyaElement.sRessyaProperty.getJikoku().compare(itr->sRessyaProperty.getJikoku(), m_KitenJikoku) > 0)
		{
			//aRessyaElementが比較対象よりも後方にある場合、continueで次の比較に移ります
			continue;
		}
		//ここまでの2条件を満たしていない場合、二つのaRessyaElementは、同時刻になる。
		//二つのRessyaElementがそれぞれBeforeとAfterが有効な時は、その2列車が接続対象となるため、After(列車終端)の方が前になるように挿入する
		//ただし、既にBeforeとAfterの組み合わせが存在する可能性があるのでaRessyaElementがBefore有効でitrがAfter有効の場合は、itrのさらに一つ先を見て、
		//それが、同時刻のBefore有効でないことを確認する必要がある。
		//それ以外の場合は、BeforeAfter共にNULL(列車競合)になる、ただし、aRessyaElementとitrが共にAfter有効の場合は、itrのさらに一つ先を見て、
		//それが、同時刻のBefore有効でないことを確認する必要がある。
		if (aRessyaElement.AfterOperation != NULL && itr->AfterOperation != NULL)
		{
			//どちらも列車終点の場合は、競合に変更する。ただし、一つ後が同時刻の先端の場合は、それを削除する
			itr->AfterOperation = NULL;

			list<RessyaElement>::iterator itrNext = itr;
			itrNext++;
			if (itrNext != pRessyaExist->end())
			{
				if (aRessyaElement.sRessyaProperty.getJikoku().compare(itrNext->sRessyaProperty.getJikoku()) == 0)
				{
					//時刻が一致した場合、itrNextは削除。
					pRessyaExist->erase(itrNext);
				}
			}
		}
		//else if (aRessyaElement.iType == -1 && itr->iType == 1)
		else if (aRessyaElement.AfterOperation != NULL && itr->BeforeOperation != NULL)
		{
			//挿入対象が列車終端で、比較対象が列車先端の場合、比較対象の次は関係ないので、itrの位置に挿入する
			pRessyaExist->insert(itr, aRessyaElement);
		}
		else if (aRessyaElement.BeforeOperation != NULL && itr->AfterOperation != NULL)
		{
			//挿入対象が列車先端で、比較対象が列車終端の場合、比較対象の次が同時刻の列車先端かどうかを確認する
			//(実際は、同時刻であれば間違いなく列車先端なので、時刻比較だけでよい。
			list<RessyaElement>::iterator itrNext = itr;
			itrNext++;
			if (itrNext != pRessyaExist->end())
			{
				if (aRessyaElement.sRessyaProperty.getJikoku().compare(itrNext->sRessyaProperty.getJikoku()) == 0)
				{
					//時刻が一致した場合、aRessyaElement,itr,itrNextの三つがかち合っているので、
					//itrのiTypeを0にして、itrNextは削除。
					itr->AfterOperation = NULL;
					pRessyaExist->erase(itrNext);
					return;
				}
			}
			//itrが最後尾だった場合、itrNextが無関係だった場合は、itrNextの位置にaRessyaElementを挿入して戻る。
			pRessyaExist->insert(itrNext, aRessyaElement);
		}
		else if (aRessyaElement.BeforeOperation != NULL && itr->BeforeOperation != NULL)
		{
			//どちらも列車先端の場合は、競合に変更
			itr->BeforeOperation = NULL;
		}

		return;
	}
	//forを抜けた場合は、List中のどれよりも後の時刻であるということなので、Listの最後尾に追加して戻る
	pRessyaExist->push_back(aRessyaElement);
	return;
}
//
//void CDedOperationConnecter::InsertRessyaElementPatternDiagram(
//	const int iEkiIndexofContExist,
//	const int iRessyaTrackIndex,
//	const RessyaElement aRessyaElement)
//{
//	list<RessyaElement>* pRessyaExist = &m_contRessyaExist[iEkiIndexofContExist][iRessyaTrackIndex];
//	if (pRessyaExist->empty())
//	{
//		pRessyaExist->push_back(aRessyaElement);
//		return;
//	}
//	for (list<RessyaElement>::iterator itr = pRessyaExist->begin();
//		itr != pRessyaExist->end(); itr++)
//	{
//		if (aRessyaElement.sRessyaProperty.getJikoku().compare(itr->sRessyaProperty.getJikoku(), m_KitenJikoku) < 0)
//		{
//			//aRessyaElementが比較対象よりも前方にある場合、その位置に挿入します
//			pRessyaExist->insert(itr, aRessyaElement);
//			return;
//		}
//
//		if (aRessyaElement.sRessyaProperty.getJikoku().compare(itr->sRessyaProperty.getJikoku(), m_KitenJikoku) > 0)
//		{
//			//aRessyaElementが比較対象よりも後方にある場合、continueで次の比較に移ります
//			continue;
//		}
//		//ここまでの2条件を満たしていない場合、二つのaRessyaElementは、同時刻になる。
//		//二つのRessyaElementがそれぞれBeforeとAfterが有効な時は、その2列車が接続対象となるため、After(列車終端)の方が前になるように挿入する
//		//ただし、既にBeforeとAfterの組み合わせが存在する可能性があるのでaRessyaElementがBefore有効でitrがAfter有効の場合は、itrのさらに一つ先を見て、
//		//それが、同時刻のBefore有効でないことを確認する必要がある。
//		//それ以外の場合は、BeforeAfter共にNULL(列車競合)になる、ただし、aRessyaElementとitrが共にAfter有効の場合は、itrのさらに一つ先を見て、
//		//それが、同時刻のBefore有効でないことを確認する必要がある。
//		if (aRessyaElement.AfterOperation != NULL && itr->AfterOperation != NULL)
//		{
//			//どちらも列車終点の場合は、競合に変更する。ただし、一つ後が同時刻の先端の場合は、それを削除する
//			itr->AfterOperation = NULL;
//
//			list<RessyaElement>::iterator itrNext = itr;
//			itrNext++;
//			if (itrNext != pRessyaExist->end())
//			{
//				if (aRessyaElement.sRessyaProperty.getJikoku().compare(itrNext->sRessyaProperty.getJikoku()) == 0)
//				{
//					//時刻が一致した場合、itrNextは削除。
//					pRessyaExist->erase(itrNext);
//				}
//			}
//		}
//		//else if (aRessyaElement.iType == -1 && itr->iType == 1)
//		else if (aRessyaElement.AfterOperation != NULL && itr->BeforeOperation != NULL)
//		{
//			//挿入対象が列車終端で、比較対象が列車先端の場合、比較対象の次は関係ないので、itrの位置に挿入する
//			pRessyaExist->insert(itr, aRessyaElement);
//		}
//		else if (aRessyaElement.BeforeOperation != NULL && itr->AfterOperation != NULL)
//		{
//			//挿入対象が列車先端で、比較対象が列車終端の場合、比較対象の次が同時刻の列車先端かどうかを確認する
//			//(実際は、同時刻であれば間違いなく列車先端なので、時刻比較だけでよい。
//			list<RessyaElement>::iterator itrNext = itr;
//			itrNext++;
//			if (itrNext != pRessyaExist->end())
//			{
//				if (aRessyaElement.sRessyaProperty.getJikoku().compare(itrNext->sRessyaProperty.getJikoku()) == 0)
//				{
//					//時刻が一致した場合、aRessyaElement,itr,itrNextの三つがかち合っているので、
//					//itrのiTypeを0にして、itrNextは削除。
//					itr->AfterOperation = NULL;
//					pRessyaExist->erase(itrNext);
//					return;
//				}
//			}
//			//itrが最後尾だった場合、itrNextが無関係だった場合は、itrNextの位置にaRessyaElementを挿入して戻る。
//			pRessyaExist->insert(itrNext, aRessyaElement);
//		}
//		else if (aRessyaElement.BeforeOperation != NULL && itr->BeforeOperation != NULL)
//		{
//			//どちらも列車先端の場合は、競合に変更
//			itr->BeforeOperation = NULL;
//		}
//
//		return;
//	}
//	//forを抜けた場合は、List中のどれよりも後の時刻であるということなので、Listの最後尾に追加して戻る
//	pRessyaExist->push_back(aRessyaElement);
//	return;
//
//	for (int iShiftSecond = m_iPatternDiagramPreviewCycleSecond; iShiftSecond <= m_iPatternDiagramPreviewRange; iShiftSecond += m_iPatternDiagramPreviewCycleSecond)
//	{
//		RessyaElement aRessyaElementShift(aRessyaElement);
//		aRessyaElementShift.sRessyaProperty.setJikoku(aRessyaElementShift.sRessyaProperty.getJikoku().addSeconds(iShiftSecond));
//		aRessyaElementShift.iShiftSecond = iShiftSecond;
//
//		for (list<RessyaElement>::iterator itr = pRessyaExist->begin();
//			itr != pRessyaExist->end(); itr++)
//		{
//			if (aRessyaElementShift.sRessyaProperty.getJikoku().compare(itr->sRessyaProperty.getJikoku(), m_KitenJikoku) < 0)
//			{
//				//aRessyaElementが比較対象よりも前方にある場合、その位置に挿入します
//				pRessyaExist->insert(itr, aRessyaElementShift);
//				return;
//			}
//
//			if (aRessyaElementShift.sRessyaProperty.getJikoku().compare(itr->sRessyaProperty.getJikoku(), m_KitenJikoku) > 0)
//			{
//				//aRessyaElementが比較対象よりも後方にある場合、continueで次の比較に移ります
//				continue;
//			}
//			//ここまでの2条件を満たしていない場合、二つのaRessyaElementは、同時刻になる。
//			//二つのRessyaElementがそれぞれBeforeとAfterが有効な時は、その2列車が接続対象となるため、After(列車終端)の方が前になるように挿入する
//			//ただし、既にBeforeとAfterの組み合わせが存在する可能性があるのでaRessyaElementがBefore有効でitrがAfter有効の場合は、itrのさらに一つ先を見て、
//			//それが、同時刻のBefore有効でないことを確認する必要がある。
//			//それ以外の場合は、BeforeAfter共にNULL(列車競合)になる、ただし、aRessyaElementとitrが共にAfter有効の場合は、itrのさらに一つ先を見て、
//			//それが、同時刻のBefore有効でないことを確認する必要がある。
//			if (aRessyaElementShift.AfterOperation != NULL && itr->AfterOperation != NULL)
//			{
//				//どちらも列車終点の場合は、競合に変更する。ただし、一つ後が同時刻の先端の場合は、それを削除する
//				itr->AfterOperation = NULL;
//
//				list<RessyaElement>::iterator itrNext = itr;
//				itrNext++;
//				if (itrNext != pRessyaExist->end())
//				{
//					if (aRessyaElementShift.sRessyaProperty.getJikoku().compare(itrNext->sRessyaProperty.getJikoku()) == 0)
//					{
//						//時刻が一致した場合、itrNextは削除。
//						pRessyaExist->erase(itrNext);
//					}
//				}
//			}
//			//else if (aRessyaElement.iType == -1 && itr->iType == 1)
//			else if (aRessyaElementShift.AfterOperation != NULL && itr->BeforeOperation != NULL)
//			{
//				//挿入対象が列車終端で、比較対象が列車先端の場合、比較対象の次は関係ないので、itrの位置に挿入する
//				pRessyaExist->insert(itr, aRessyaElementShift);
//			}
//			else if (aRessyaElementShift.BeforeOperation != NULL && itr->AfterOperation != NULL)
//			{
//				//挿入対象が列車先端で、比較対象が列車終端の場合、比較対象の次が同時刻の列車先端かどうかを確認する
//				//(実際は、同時刻であれば間違いなく列車先端なので、時刻比較だけでよい。
//				list<RessyaElement>::iterator itrNext = itr;
//				itrNext++;
//				if (itrNext != pRessyaExist->end())
//				{
//					if (aRessyaElementShift.sRessyaProperty.getJikoku().compare(itrNext->sRessyaProperty.getJikoku()) == 0)
//					{
//						//時刻が一致した場合、aRessyaElement,itr,itrNextの三つがかち合っているので、
//						//itrのiTypeを0にして、itrNextは削除。
//						itr->AfterOperation = NULL;
//						pRessyaExist->erase(itrNext);
//						return;
//					}
//				}
//				//itrが最後尾だった場合、itrNextが無関係だった場合は、itrNextの位置にaRessyaElementを挿入して戻る。
//				pRessyaExist->insert(itrNext, aRessyaElementShift);
//			}
//			else if (aRessyaElementShift.BeforeOperation != NULL && itr->BeforeOperation != NULL)
//			{
//				//どちらも列車先端の場合は、競合に変更
//				itr->BeforeOperation = NULL;
//			}
//
//			return;
//		}
//		//forを抜けた場合は、List中のどれよりも後の時刻であるということなので、Listの最後尾に追加して戻る
//		pRessyaExist->push_back(aRessyaElementShift);
//		return;
//
//
//	}
//}


RessyaElement CDedOperationConnecter::SearchRessyaElement(
	list<RessyaElement>* pRessyaExist,
	CentDedAfterOperation* aAfterOperation,
	CdDedJikoku& pTerminalJikoku,
	const int iShiftSecond)
{
	if (aAfterOperation == NULL)
	{
		return RessyaElement();
	}
	for (list<RessyaElement>::iterator itr = pRessyaExist->begin();
		itr != pRessyaExist->end(); itr++)
	{
		/**
			aOperationAfterが一致するものを探します。
			一致しない場合は、次の探索へ、
			一致した場合は、iTypeのチェックを行い、列車終端のままであるかを確認します。
			もし、列車終端でなくなっていた場合(注・insertRessyaElementで、列車終端ではなくなった場合は、
				RessyaPropertyをNULLにするようにしているが、念のため)は、
				次列車は見つからなかったとして、NULLを返します。
		*/
		if (aAfterOperation == itr->AfterOperation &&
			iShiftSecond == itr->iShiftSecond)
		{
			//Afterが一致かつ、NULLではない場合、確実に列車終端なので、下のifは省略
			//if (itr->iType == -1)
			//{
				/**
					列車が一致した場合は、前列車の終端が有効を意味します
					(他の列車と競合していないので、次列車接続が可能)
					その場合は、次のRessyaElement(itrNext)を取得して、それが列車先端であるかを確認します
					ただし、itrがリストの最後部だった場合は、次列車は無いのでNULLを返します
					itrNextが列車先端(iType==1)の場合、そのRessyaElementを返します。
					それ以外の場合は、NULLを返します
				*/
			list<RessyaElement>::iterator itrNext = itr;
			itrNext++;
			if (itrNext == pRessyaExist->end())
			{
				//Ver2.01 irtが末尾の場合には、先頭要素を評価対象とします(ダイヤグラム起点時刻を跨ぐことを容認する)
				//実際には、itrNextを先頭要素に置き換えたのち、今まで通りの評価を行います。
				//Ver2.05 m_bOperationCrossKitenJikokuがfalseの場合、itrが末尾の場合は終了します。
				if (m_bOperationCrossKitenJikoku)
				{
					itrNext = pRessyaExist->begin();
				}
				else
				{
					return RessyaElement();
				}
			}

			if (itrNext->BeforeOperation != NULL)
			{
				pTerminalJikoku = itr->sRessyaProperty.getJikoku();
				return *itrNext;
			}
			else
			{
				return RessyaElement();
			}
			//}
		}
		//aOperationAfterが一致しない場合は、次のRessyaElementの検索に移ります。
	}
	return RessyaElement();
}

bool CDedOperationConnecter::SearchRessyaElementRev(
	list<RessyaElement>* pRessyaExist,
	CentDedBeforeOperation* aBeforeOperation)
{
	if (aBeforeOperation == NULL)
	{
		return false;
	}
	for (list<RessyaElement>::iterator itr = pRessyaExist->begin();
		itr != pRessyaExist->end(); itr++)
	{
		/**
			aBeforeOperationが一致するものを探します。
			一致しない場合は、次の探索へ、
			一致した場合は、iTypeのチェックを行い、列車終端のままであるかを確認します。
			もし、列車終端でなくなっていた場合(注・insertRessyaElementで、列車終端ではなくなった場合は、
				RessyaPropertyをNULLにするようにしているが、念のため)は、
				次列車は見つからなかったとして、NULLを返します。
		*/
		if (aBeforeOperation == itr->BeforeOperation)
			//if (aRessyaPropertyBefore.isEqualTo(itr->sRessyaProperty, false))
		{
			//Beforeが一致かつ、NULLではない場合、確実に列車先端なので、下のifは省略
			//if (itr->iType == 1)
			//{
				/**
					列車が一致した場合は、先端作業が有効を意味します
					(他の列車と競合していないので、前列車接続が可能)
					その場合は、前のRessyaElement(itrPrev)を取得して、それが列車終端であるかを確認します
					ただし、itrがリストの最前部だった場合は、前列車は無いのでfalseを返します
					itrNextが列車終端(iType==-1)の場合、trueを返します。
					それ以外の場合は、NULLを返します

					Ver2.01	itrがリストの最前部だった場合はリストの最後部を比較対象にします
					(ダイヤグラム起点時刻を跨ぐのを許容します)
					Ver2.05 m_bOperationCrossKitenJikokuがfalseの場合、itrが最前部の場合はfalseを返します

				*/
			if (itr == pRessyaExist->begin())
			{
				if (m_bOperationCrossKitenJikoku)
				{
					list<RessyaElement>::iterator itrBack = pRessyaExist->end();
					itrBack--;
					if (itrBack->AfterOperation != NULL)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
			list<RessyaElement>::iterator itrPrev = itr;
			itrPrev--;
			if (itrPrev->AfterOperation != NULL)
			{
				return true;
			}
			else
			{
				return false;
			}
			//}
		}
		//aOperationAfterが一致しない場合は、次のRessyaElementの検索に移ります。
	}
	return false;
}
	
void CDedOperationConnecter::operationConnectLight()
{
	const CentDedEkiCont* pEkiCont = m_pDedRosen->getCentDedEkiCont();
	CentDedRessyaCont* pRessyaCont[2];
	for (int iRessyahoukou = Ressyahoukou_Kudari;
		iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
	{
		pRessyaCont[iRessyahoukou] = m_pDedDia->getCentDedRessyaCont((ERessyahoukou)iRessyahoukou);
	}

	//駅・番線別ホーム使用状態リスト
	m_contRessyaExist.resize(pEkiCont->size());
	/**
		iEkiOrder->iEkiIndex対応表(分岐・環状対応)
		下り・上りの2方面×駅数のコンテナ
		[iEkiOrder][iRessyahoukou]でアクセスすると、contRessyaExistに対応するiEkiIndexを返します
		また、分岐環状駅については、iEkiIndexLoop[0]駅に集約します。従って、上り列車の場合はiEkiOrderLoop.back()に当たります
	*/
	vector<vector<int>> iEkiOrderTable;
	iEkiOrderTable.resize(pEkiCont->size());

	for (int iEki = 0; iEki < (int)m_contRessyaExist.size(); iEki++)
	{
		const CentDedEki aEki = pEkiCont->get(iEki);
		m_contRessyaExist[iEki].assign(aEki.getEkiTrack2Cont()->size(), list<RessyaElement>());

		if (aEki.getBrunchLoopPosition() == -1)
		{
			iEkiOrderTable[iEki].insert(iEkiOrderTable[iEki].begin(), iEki);
			iEkiOrderTable[m_contRessyaExist.size() - 1 - iEki].push_back(iEki);
		}
		else
		{
			deque<int> iEkiIndexLoop = aEki.getEkiIndexLoop();
			iEkiOrderTable[iEki].insert(iEkiOrderTable[iEki].begin(), iEkiIndexLoop[0]);
			iEkiOrderTable[m_contRessyaExist.size() - 1 - iEki].push_back(iEkiIndexLoop[0]);
		}
	}

	//簡易作業リスト、運用表情報リストを作成
	m_contRessyaOperationElement.resize(2);
	for (int iRessyahoukou = Ressyahoukou_Kudari;
		iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
	{
		m_contRessyaOperationElement[iRessyahoukou].assign(pRessyaCont[iRessyahoukou]->size(), vector<OperationElement>());
	}
	m_contJunctionList.clear();

	//カスタム表示モード用RessyaIndex初期化
	m_pDedDia->getcontCustomizeRessyaIndexKudari().clear();
	for (int idx = 0; idx < pRessyaCont[0]->size(); idx++)
	{
		m_pDedDia->getcontCustomizeRessyaIndexKudari().push_back(
			CustomizeJikokuhyouContent({ idx }));
	}

	m_pDedDia->getcontCustomizeRessyaIndexNobori().clear();
	for (int idx = 0; idx < pRessyaCont[1]->size(); idx++)
	{
		m_pDedDia->getcontCustomizeRessyaIndexNobori().push_back(
			CustomizeJikokuhyouContent({ idx }));
	}

	//m_contOuterConnectInsertList.resize(2);
	//m_contOuterReleaseInsertList.resize(2);
	m_contConnectMoveList.resize(2);
	m_contReleaseMoveList.resize(2);
	for (int iRessyahoukou = Ressyahoukou_Kudari;
		iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
	{
		//m_contOuterConnectInsertList[iRessyahoukou].resize(pEkiCont->size());
		//m_contOuterReleaseInsertList[iRessyahoukou].resize(pEkiCont->size());
		m_contConnectMoveList[iRessyahoukou].resize(pEkiCont->size());
		m_contReleaseMoveList[iRessyahoukou].resize(pEkiCont->size());
	}

	//m_contHidden初期化、bDisableHiddenSyubetsuがTrueの場合は、全値をfalseとする。

	m_contHidden.assign(m_pDedRosen->getCentDedRessyasyubetsuCont()->size(), false);
	m_bHiddenExist = false;
	if (!m_pDedRosen->getDisableHiddenSyubetsu())
	{
		const CentDedRessyasyubetsuCont* pCentDedRessyasyubetsuCont = m_pDedRosen->getCentDedRessyasyubetsuCont();

		for (int iRessyaSyubetsuIndex = 0; iRessyaSyubetsuIndex < pCentDedRessyasyubetsuCont->size(); iRessyaSyubetsuIndex++)
		{
			bool bHidden = pCentDedRessyasyubetsuCont->get(iRessyaSyubetsuIndex).getHidden();
			if (bHidden)
			{
				m_contHidden[iRessyaSyubetsuIndex] = true;
				m_bHiddenExist = true;
			}
		}
	}


	/*
	Step1 全列車について
			始発駅前作業から終着駅後作業まで順番に見ながら、作業抽出リストを作成する
			作業抽出リストには、開始作業・終了作業と増結・解結を抜き出す。
			次列車接続の場合は、m_contJunctionListにスタックし、接続を行うのに用いる。

	*/
	for (int iRessyahoukou = Ressyahoukou_Kudari;
		iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
	{
		int iSize = pRessyaCont[iRessyahoukou]->size();
#pragma omp parallel for schedule(dynamic)
		for (int idxRessya = 0; idxRessya < iSize; idxRessya++)
		{
			/*const */CentDedRessya* pCentDedRessya = pRessyaCont[iRessyahoukou]->getMuPtr()->get(idxRessya);

			//列車が運休状態のときは、運用探索の対象に入れず、contRessyaIndexからも削除する
			if (pCentDedRessya->isCanceled())
			{
#pragma omp critical(CustomizeRessyaIndex)
				{
					vector<CustomizeJikokuhyouContent>& contCustomizeRessyaIndex =
						m_pDedDia->getcontCustomizeRessyaIndex((ERessyahoukou)iRessyahoukou);
					int iCustomizeIndex = -1;
					for (int idx = 0; idx < (int)contCustomizeRessyaIndex.size(); idx++)
					{
						for (int idxc = 0; idxc < (int)contCustomizeRessyaIndex[idx].iRessyaIndexCont.size(); idxc++)
						{
							if (contCustomizeRessyaIndex[idx].iRessyaIndexCont[idxc] == idxRessya)
							{
								iCustomizeIndex = idx;
							}
						}
						if (iCustomizeIndex != -1)
						{
							contCustomizeRessyaIndex.erase(contCustomizeRessyaIndex.begin() + iCustomizeIndex);
							break;
						}
					}
				}
				continue;

			}

			if (pCentDedRessya->isNull())
			{
				continue;
			}

			int iValidSihatsuEkiOrder = pCentDedRessya->getValidSihatsuEki();
			int iValidSyuuchakuEkiOrder = pCentDedRessya->getValidSyuuchakuEki();
			//有効な始発駅もしくは有効な終着駅が無い場合は、運用探索の対象に入れず、contRessyaIndexからも削除する
			//また、始発駅が終着駅と同一かそれ以降にある場合も除外
			if (iValidSihatsuEkiOrder < 0 || iValidSyuuchakuEkiOrder < 0 || iValidSihatsuEkiOrder >= iValidSyuuchakuEkiOrder)
			{
#pragma omp critical(CustomizeRessyaIndex)
				{
					vector<CustomizeJikokuhyouContent>& contCustomizeRessyaIndex =
						m_pDedDia->getcontCustomizeRessyaIndex((ERessyahoukou)iRessyahoukou);
					int iCustomizeIndex = -1;
					for (int idx = 0; idx < (int)contCustomizeRessyaIndex.size(); idx++)
					{
						for (int idxc = 0; idxc < (int)contCustomizeRessyaIndex[idx].iRessyaIndexCont.size(); idxc++)
						{
							if (contCustomizeRessyaIndex[idx].iRessyaIndexCont[idxc] == idxRessya)
							{
								iCustomizeIndex = idx;
							}
						}
						if (iCustomizeIndex != -1)
						{
							contCustomizeRessyaIndex.erase(contCustomizeRessyaIndex.begin() + iCustomizeIndex);
							break;
						}
					}
				}
				continue;
			}
			/**
				分岐・環状線を考慮した駅時刻・番線取得
				・始発駅の場合、次駅の駅扱いが経由無し以外なら、iEkiOrderから着発両側・前後作業を取得。
				・次駅の駅扱いが経由無しなら、経由無しが連続した後の駅Order(iEkiOrderSearch)を取得し、
					二つが同一駅扱いなら、iEkiOrderから着時刻・前作業を、iEkiOrderSearchから発時刻・後作業を取得する。
					なお、iEkiOrderSearchの次が経由無しなら、その先をチェックする必要がある。
				・終着駅については、始発駅についての探索を逆方向に行う。
			*/
			vector<OperationElement> contOperationElement;
			CdDedRessyaProperty aRessyaProperty(
				(ERessyahoukou)iRessyahoukou,
				idxRessya);
			int iLevelAdd = 0;
			/**
				始発駅
				・出区・路線外始発の場合は、contOutOuterに入れる。
				・前列車接続の場合は、前作業を後方に見て、番線と時刻を取得して、contRessyaExistに入れる

				・それ以外の作業に、増解結がある場合も
			*/
			{
				CentDedEkiJikoku* pEkiJikokuSihatsu =
					pCentDedRessya->getCentDedEkiJikokuCont()->getMuPtr()->get(iValidSihatsuEkiOrder);
				CentDedBeforeOperationCont* pBeforeCont =
					pEkiJikokuSihatsu->getCentDedBeforeOperationCont();
				CentDedAfterOperationCont* pAfterCont =
					pEkiJikokuSihatsu->getCentDedAfterOperationCont();

				CentDedBeforeOperation* pFirstOperation = pBeforeCont->getMuPtr()->get(0);
				if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Out ||
					pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
				{
					vector<int> iLevel;
					iLevel.push_back(iLevelAdd);
					contOperationElement.push_back(OperationElement(
						pFirstOperation, iLevel, iValidSihatsuEkiOrder));

					iLevelAdd++;
				}
				else if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Junction)
				{
					/**
						前列車接続の場合、最初にどの番線にいるのか、起点となる時刻を調べる。
						番線は、発着番線を初期値とし、BeforeContを逆順に見て、入換番線を取得します。
						ただし、同じホームへの入換がある場合は、最も後の物のみが有効となる

						起点時刻は、pOperationNoneに起点時刻が設定されている場合はそれを用います。
						NULLの場合は、BeforeContを昇順に全て見て、時刻が見つかればそれを用います。
						このとき、入換作業が有効かどうかのチェックが必要です。
						BeforeContを見てもNULLの場合は、AfterContを降順にみて、時刻が見つかればそこで終了です。
						このとき、入換作業が有効かどうかのチェックが必要です。
						それでもNULLの場合は、当駅発時刻を用います。

						m_contBeforeNoneListに作業を収めておく
					*/

					pFirstOperation->clearOperationNumber();

					int iRessyaTrackIndex = pEkiJikokuSihatsu->getRessyaTrackIndex();
					for (int idxb = pBeforeCont->size() - 1; idxb > 0; idxb--)
					{
						CentDedBeforeOperation* pBeforeOperation = pBeforeCont->getMuPtr()->get(idxb);
						if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
						{
							/**
								同じ番線への入換は、最も後の物のみが有効
							*/
							if (iRessyaTrackIndex != pBeforeOperation->getShuntTrackIndex())
							{
								iRessyaTrackIndex = pBeforeOperation->getShuntTrackIndex();
							}
						}
					}

					CdDedJikoku aOriginJikoku = pFirstOperation->getOriginJikoku();
					if (aOriginJikoku.isNull())
					{
						int iRessyaTrackIndexTemp = pEkiJikokuSihatsu->getRessyaTrackIndex();
						for (int idxb = pBeforeCont->size() - 1; idxb > 0; idxb--)
						{
							CentDedBeforeOperation* pBeforeOperation = pBeforeCont->getMuPtr()->get(idxb);
							if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
							{
								/**
									同じ番線への入換は、最も後の物のみが有効
								*/
								if (iRessyaTrackIndexTemp != pBeforeOperation->getShuntTrackIndex())
								{
									aOriginJikoku = pBeforeOperation->getOperationHatsuJikoku();
									iRessyaTrackIndexTemp = pBeforeOperation->getShuntTrackIndex();
								}
							}
							else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
							{
								aOriginJikoku = pBeforeOperation->getConnectJikoku();
							}
							else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
							{
								aOriginJikoku = pBeforeOperation->getReleaseJikoku();
							}
						}
					}
					if (aOriginJikoku.isNull())
					{
						int iRessyaTrackIndexTemp = pEkiJikokuSihatsu->getRessyaTrackIndex();
						for (int idxa = 0; idxa < pAfterCont->size(); idxa++)
						{
							CentDedAfterOperation* pAfterOperation = pAfterCont->getMuPtr()->get(idxa);
							if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
							{
								/**
									同じ番線への入換は、最も前の物のみが有効
								*/
								if (iRessyaTrackIndexTemp != pAfterOperation->getShuntTrackIndex())
								{
									aOriginJikoku = pAfterOperation->getOperationHatsuJikoku();
									break;
								}
							}
							else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
							{
								aOriginJikoku = pAfterOperation->getConnectJikoku();
								break;
							}
							else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
							{
								aOriginJikoku = pAfterOperation->getReleaseJikoku();
								break;
							}
						}
					}
					if (aOriginJikoku.isNull())
					{
						aOriginJikoku = pEkiJikokuSihatsu->getHatsujikoku();
					}
					vector<int> iLevel;
					iLevel.push_back(iLevelAdd);

					int iEkiIndexofContExist = iEkiOrderTable[iValidSihatsuEkiOrder][iRessyahoukou];

					aRessyaProperty.setJikoku(aOriginJikoku);
					RessyaElement aRessyaElement(pFirstOperation, aRessyaProperty);

					contOperationElement.push_back(
						OperationElement(pFirstOperation,
							iLevel,
							iValidSihatsuEkiOrder,
							iEkiIndexofContExist,
							iRessyaTrackIndex));

#pragma omp critical(RessyaExist)
					InsertRessyaElement(
						iEkiIndexofContExist,
						iRessyaTrackIndex,
						aRessyaElement);

					iLevelAdd++;
				}
				/**
					bTsuukaOuterJikokuNull
					始発駅の駅扱いが通過で、路線外始発かつ当駅着時刻がNULLの場合は、
					路線外始発作業以外は無効になります。
					したがって、下記の前作業・後作業検索はスキップします。
				*/
				bool bTsuukaOuterJikokuNull =
					pEkiJikokuSihatsu->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka &&
					pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer &&
					pFirstOperation->getChakuJikoku().isNull();

				for (int idxb = 1; idxb < (int)pBeforeCont->size() && !bTsuukaOuterJikokuNull; idxb++)
				{
					CentDedBeforeOperation* pBeforeOperation = pBeforeCont->getMuPtr()->get(idxb);
					if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
					{
						pBeforeOperation->clearOperationNumber();

						int iConnectTrackIndex = pEkiJikokuSihatsu->getRessyaTrackIndex();
						for (int idxb2 = pBeforeCont->size() - 1; idxb2 > idxb; idxb2--)
						{
							CentDedBeforeOperation* pBeforeOperation2 = pBeforeCont->getMuPtr()->get(idxb2);
							if (pBeforeOperation2->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
							{
								iConnectTrackIndex = pBeforeOperation2->getShuntTrackIndex();
							}
						}
						vector<int> iLevel;
						iLevel.push_back(iLevelAdd);
						OperationElement aOperationElement(
							pBeforeOperation, iLevel, iValidSihatsuEkiOrder);
						vector<OperationElement> contTemp = searchBeforeOperationElementLight(
							pBeforeOperation->getCentDedBeforeOperationCont(),
							pBeforeOperation->getConnectJikoku(),
							aRessyaProperty,
							iLevel,
							iValidSihatsuEkiOrder,
							iEkiOrderTable[iValidSihatsuEkiOrder][iRessyahoukou],
							iConnectTrackIndex);

						contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());
						contOperationElement.push_back(aOperationElement);

						iLevelAdd++;
					}
					else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
					{
						pBeforeOperation->clearOperationNumber();

						int iReleaseTrackIndex = pEkiJikokuSihatsu->getRessyaTrackIndex();
						for (int idxb2 = pBeforeCont->size() - 1; idxb2 > idxb; idxb2--)
						{
							CentDedBeforeOperation* pBeforeOperation2 = pBeforeCont->getMuPtr()->get(idxb2);
							if (pBeforeOperation2->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
							{
								iReleaseTrackIndex = pBeforeOperation2->getShuntTrackIndex();
							}
						}
						vector<int> iLevel;
						iLevel.push_back(iLevelAdd);
						OperationElement aOperationElement(
							pBeforeOperation, iLevel, iValidSihatsuEkiOrder);
						vector<OperationElement> contTemp = searchAfterOperationElementLight(
							pBeforeOperation->getCentDedAfterOperationCont(),
							pBeforeOperation->getReleaseJikoku(),
							aRessyaProperty,
							iLevel,
							iValidSihatsuEkiOrder,
							iEkiOrderTable[iValidSihatsuEkiOrder][iRessyahoukou],
							iReleaseTrackIndex);

						contOperationElement.push_back(aOperationElement);
						contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());

						iLevelAdd++;
					}

				}

				for (int idxa = 0; idxa < (int)pAfterCont->size() && !bTsuukaOuterJikokuNull; idxa++)
				{
					CentDedAfterOperation* pAfterOperation = pAfterCont->getMuPtr()->get(idxa);
					if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
					{
						pAfterOperation->clearOperationNumber();

						int iConnectTrackIndex = pEkiJikokuSihatsu->getRessyaTrackIndex();
						for (int idxa2 = 0; idxa2 < idxa; idxa2++)
						{
							CentDedAfterOperation* pAfterOperation2 = pAfterCont->getMuPtr()->get(idxa2);
							if (pAfterOperation2->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
							{
								iConnectTrackIndex = pAfterOperation2->getShuntTrackIndex();
							}
						}
						vector<int> iLevel;
						iLevel.push_back(iLevelAdd);
						OperationElement aOperationElement(
							pAfterOperation, iLevel, iValidSihatsuEkiOrder);
						vector<OperationElement> contTemp = searchBeforeOperationElementLight(
							pAfterOperation->getCentDedBeforeOperationCont(),
							pAfterOperation->getConnectJikoku(),
							aRessyaProperty,
							iLevel,
							iValidSihatsuEkiOrder,
							iEkiOrderTable[iValidSihatsuEkiOrder][iRessyahoukou],
							iConnectTrackIndex);

						contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());
						contOperationElement.push_back(aOperationElement);

						iLevelAdd++;
					}
					else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
					{
						pAfterOperation->clearOperationNumber();

						int iReleaseTrackIndex = pEkiJikokuSihatsu->getRessyaTrackIndex();
						for (int idxa2 = 0; idxa2 < idxa; idxa2++)
						{
							CentDedAfterOperation* pAfterOperation2 = pAfterCont->getMuPtr()->get(idxa2);
							if (pAfterOperation2->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
							{
								iReleaseTrackIndex = pAfterOperation2->getShuntTrackIndex();
							}
						}
						vector<int> iLevel;
						iLevel.push_back(iLevelAdd);
						OperationElement aOperationElement(
							pAfterOperation, iLevel, iValidSihatsuEkiOrder);
						vector<OperationElement> contTemp = searchAfterOperationElementLight(
							pAfterOperation->getCentDedAfterOperationCont(),
							pAfterOperation->getReleaseJikoku(),
							aRessyaProperty,
							iLevel,
							iValidSihatsuEkiOrder,
							iEkiOrderTable[iValidSihatsuEkiOrder][iRessyahoukou],
							iReleaseTrackIndex);

						contOperationElement.push_back(aOperationElement);
						contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());

						iLevelAdd++;
					}

				}
			}

			for (int iEkiOrder = iValidSihatsuEkiOrder + 1; iEkiOrder < iValidSyuuchakuEkiOrder; iEkiOrder++)
			{
				CentDedEkiJikoku* pEkiJikoku =
					pCentDedRessya->getCentDedEkiJikokuCont()->getMuPtr()->get(iEkiOrder);
				CentDedBeforeOperationCont* pBeforeCont =
					pEkiJikoku->getCentDedBeforeOperationCont();
				CentDedAfterOperationCont* pAfterCont =
					pEkiJikoku->getCentDedAfterOperationCont();

				for (int idxb = 0; idxb < (int)pBeforeCont->size(); idxb++)
				{
					CentDedBeforeOperation* pBeforeOperation = pBeforeCont->getMuPtr()->get(idxb);
					if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
					{
						pBeforeOperation->clearOperationNumber();

						int iConnectTrackIndex = pEkiJikoku->getRessyaTrackIndex();
						for (int idxb2 = pBeforeCont->size() - 1; idxb2 > idxb; idxb2--)
						{
							CentDedBeforeOperation* pBeforeOperation2 = pBeforeCont->getMuPtr()->get(idxb2);
							if (pBeforeOperation2->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
							{
								iConnectTrackIndex = pBeforeOperation2->getShuntTrackIndex();
							}
						}
						vector<int> iLevel;
						iLevel.push_back(iLevelAdd);
						OperationElement aOperationElement(
							pBeforeOperation, iLevel, iEkiOrder);
						vector<OperationElement> contTemp = searchBeforeOperationElementLight(
							pBeforeOperation->getCentDedBeforeOperationCont(),
							pBeforeOperation->getConnectJikoku(),
							aRessyaProperty,
							iLevel,
							iEkiOrder,
							iEkiOrderTable[iEkiOrder][iRessyahoukou],
							iConnectTrackIndex);

						contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());
						contOperationElement.push_back(aOperationElement);

						iLevelAdd++;
					}
					else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
					{
						pBeforeOperation->clearOperationNumber();

						int iReleaseTrackIndex = pEkiJikoku->getRessyaTrackIndex();
						for (int idxb2 = pBeforeCont->size() - 1; idxb2 > idxb; idxb2--)
						{
							CentDedBeforeOperation* pBeforeOperation2 = pBeforeCont->getMuPtr()->get(idxb2);
							if (pBeforeOperation2->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
							{
								iReleaseTrackIndex = pBeforeOperation2->getShuntTrackIndex();
							}
						}
						vector<int> iLevel;
						iLevel.push_back(iLevelAdd);
						OperationElement aOperationElement(
							pBeforeOperation, iLevel, iEkiOrder);
						vector<OperationElement> contTemp = searchAfterOperationElementLight(
							pBeforeOperation->getCentDedAfterOperationCont(),
							pBeforeOperation->getReleaseJikoku(),
							aRessyaProperty,
							iLevel,
							iEkiOrder,
							iEkiOrderTable[iEkiOrder][iRessyahoukou],
							iReleaseTrackIndex);

						contOperationElement.push_back(aOperationElement);
						contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());

						iLevelAdd++;
					}

				}

				for (int idxa = 0; idxa < (int)pAfterCont->size(); idxa++)
				{
					CentDedAfterOperation* pAfterOperation = pAfterCont->getMuPtr()->get(idxa);
					if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
					{
						pAfterOperation->clearOperationNumber();

						int iConnectTrackIndex = pEkiJikoku->getRessyaTrackIndex();
						for (int idxa2 = 0; idxa2 < idxa; idxa2++)
						{
							CentDedAfterOperation* pAfterOperation2 = pAfterCont->getMuPtr()->get(idxa2);
							if (pAfterOperation2->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
							{
								iConnectTrackIndex = pAfterOperation2->getShuntTrackIndex();
							}
						}
						vector<int> iLevel;
						iLevel.push_back(iLevelAdd);
						OperationElement aOperationElement(
							pAfterOperation, iLevel, iEkiOrder);
						vector<OperationElement> contTemp = searchBeforeOperationElementLight(
							pAfterOperation->getCentDedBeforeOperationCont(),
							pAfterOperation->getConnectJikoku(),
							aRessyaProperty,
							iLevel,
							iEkiOrder,
							iEkiOrderTable[iEkiOrder][iRessyahoukou],
							iConnectTrackIndex);

						contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());
						contOperationElement.push_back(aOperationElement);

						iLevelAdd++;
					}
					else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
					{
						pAfterOperation->clearOperationNumber();

						int iReleaseTrackIndex = pEkiJikoku->getRessyaTrackIndex();
						for (int idxa2 = 0; idxa2 < idxa; idxa2++)
						{
							CentDedAfterOperation* pAfterOperation2 = pAfterCont->getMuPtr()->get(idxa2);
							if (pAfterOperation2->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
							{
								iReleaseTrackIndex = pAfterOperation2->getShuntTrackIndex();
							}
						}
						vector<int> iLevel;
						iLevel.push_back(iLevelAdd);
						OperationElement aOperationElement(
							pAfterOperation, iLevel, iEkiOrder);
						vector<OperationElement> contTemp = searchAfterOperationElementLight(
							pAfterOperation->getCentDedAfterOperationCont(),
							pAfterOperation->getReleaseJikoku(),
							aRessyaProperty,
							iLevel,
							iEkiOrder,
							iEkiOrderTable[iEkiOrder][iRessyahoukou],
							iReleaseTrackIndex);

						contOperationElement.push_back(aOperationElement);
						contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());

						iLevelAdd++;
					}

				}
			}

			/**
				終着駅
				・次列車始発の場合は、後作業を見て、番線と時刻を取得して、contRessyaExistに入れる

			*/
			{
				CentDedEkiJikoku* pEkiJikokuSyuuchaku =
					pCentDedRessya->getCentDedEkiJikokuCont()->getMuPtr()->get(iValidSyuuchakuEkiOrder);
				CentDedBeforeOperationCont* pBeforeCont =
					pEkiJikokuSyuuchaku->getCentDedBeforeOperationCont();
				CentDedAfterOperationCont* pAfterCont =
					pEkiJikokuSyuuchaku->getCentDedAfterOperationCont();

				CentDedAfterOperation* pLastOperation = pAfterCont->getMuPtr()->get(INT_MAX);
				/**
					bTsuukaOuterJikokuNull
					終着駅の駅扱いが通過で、路線外終着かつ当駅発時刻がNULLの場合は、
					路線外終着作業以外は無効になります。
					したがって、下記の前作業・後作業検索はスキップします。
				*/
				bool bTsuukaOuterJikokuNull =
					pEkiJikokuSyuuchaku->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka &&
					pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer &&
					pLastOperation->getHatsuJikoku().isNull();

				for (int idxb = 0; idxb < (int)pBeforeCont->size() && !bTsuukaOuterJikokuNull; idxb++)
				{
					CentDedBeforeOperation* pBeforeOperation = pBeforeCont->getMuPtr()->get(idxb);
					if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
					{
						pBeforeOperation->clearOperationNumber();

						int iConnectTrackIndex = pEkiJikokuSyuuchaku->getRessyaTrackIndex();
						for (int idxb2 = pBeforeCont->size() - 1; idxb2 > idxb; idxb2--)
						{
							CentDedBeforeOperation* pBeforeOperation2 = pBeforeCont->getMuPtr()->get(idxb2);
							if (pBeforeOperation2->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
							{
								iConnectTrackIndex = pBeforeOperation2->getShuntTrackIndex();
							}
						}
						vector<int> iLevel;
						iLevel.push_back(iLevelAdd);
						OperationElement aOperationElement(
							pBeforeOperation, iLevel, iValidSyuuchakuEkiOrder);
						vector<OperationElement> contTemp = searchBeforeOperationElementLight(
							pBeforeOperation->getCentDedBeforeOperationCont(),
							pBeforeOperation->getConnectJikoku(),
							aRessyaProperty,
							iLevel,
							iValidSyuuchakuEkiOrder,
							iEkiOrderTable[iValidSyuuchakuEkiOrder][iRessyahoukou],
							iConnectTrackIndex);

						contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());
						contOperationElement.push_back(aOperationElement);

						iLevelAdd++;
					}
					else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
					{
						pBeforeOperation->clearOperationNumber();

						int iReleaseTrackIndex = pEkiJikokuSyuuchaku->getRessyaTrackIndex();
						for (int idxb2 = pBeforeCont->size() - 1; idxb2 > idxb; idxb2--)
						{
							CentDedBeforeOperation* pBeforeOperation2 = pBeforeCont->getMuPtr()->get(idxb2);
							if (pBeforeOperation2->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
							{
								iReleaseTrackIndex = pBeforeOperation2->getShuntTrackIndex();
							}
						}
						vector<int> iLevel;
						iLevel.push_back(iLevelAdd);
						OperationElement aOperationElement(
							pBeforeOperation, iLevel, iValidSyuuchakuEkiOrder);
						vector<OperationElement> contTemp = searchAfterOperationElementLight(
							pBeforeOperation->getCentDedAfterOperationCont(),
							pBeforeOperation->getReleaseJikoku(),
							aRessyaProperty,
							iLevel,
							iValidSyuuchakuEkiOrder,
							iEkiOrderTable[iValidSyuuchakuEkiOrder][iRessyahoukou],
							iReleaseTrackIndex);

						contOperationElement.push_back(aOperationElement);
						contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());

						iLevelAdd++;
					}

				}

				for (int idxa = 0; idxa < (int)pAfterCont->size() - 1 && !bTsuukaOuterJikokuNull; idxa++)
				{
					CentDedAfterOperation* pAfterOperation = pAfterCont->getMuPtr()->get(idxa);
					if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
					{
						pAfterOperation->clearOperationNumber();

						int iConnectTrackIndex = pEkiJikokuSyuuchaku->getRessyaTrackIndex();
						for (int idxa2 = 0; idxa2 < idxa; idxa2++)
						{
							CentDedAfterOperation* pAfterOperation2 = pAfterCont->getMuPtr()->get(idxa2);
							if (pAfterOperation2->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
							{
								iConnectTrackIndex = pAfterOperation2->getShuntTrackIndex();
							}
						}
						vector<int> iLevel;
						iLevel.push_back(iLevelAdd);
						OperationElement aOperationElement(
							pAfterOperation, iLevel, iValidSyuuchakuEkiOrder);
						vector<OperationElement> contTemp = searchBeforeOperationElementLight(
							pAfterOperation->getCentDedBeforeOperationCont(),
							pAfterOperation->getConnectJikoku(),
							aRessyaProperty,
							iLevel,
							iValidSyuuchakuEkiOrder,
							iEkiOrderTable[iValidSyuuchakuEkiOrder][iRessyahoukou],
							iConnectTrackIndex);

						contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());
						contOperationElement.push_back(aOperationElement);

						iLevelAdd++;
					}
					else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
					{
						pAfterOperation->clearOperationNumber();

						int iReleaseTrackIndex = pEkiJikokuSyuuchaku->getRessyaTrackIndex();
						for (int idxa2 = 0; idxa2 < idxa; idxa2++)
						{
							CentDedAfterOperation* pAfterOperation2 = pAfterCont->getMuPtr()->get(idxa2);
							if (pAfterOperation2->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
							{
								iReleaseTrackIndex = pAfterOperation2->getShuntTrackIndex();
							}
						}
						vector<int> iLevel;
						iLevel.push_back(iLevelAdd);
						OperationElement aOperationElement(
							pAfterOperation, iLevel, iValidSyuuchakuEkiOrder);
						vector<OperationElement> contTemp = searchAfterOperationElementLight(
							pAfterOperation->getCentDedAfterOperationCont(),
							pAfterOperation->getReleaseJikoku(),
							aRessyaProperty,
							iLevel,
							iValidSyuuchakuEkiOrder,
							iEkiOrderTable[iValidSyuuchakuEkiOrder][iRessyahoukou],
							iReleaseTrackIndex);

						contOperationElement.push_back(aOperationElement);
						contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());

						iLevelAdd++;
					}

				}

				if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_In ||
					pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
				{
					pLastOperation->clearOperationNumber();
					vector<int> iLevel;
					iLevel.push_back(iLevelAdd);
					contOperationElement.push_back(OperationElement(
						pLastOperation, iLevel, iValidSyuuchakuEkiOrder));
				}
				else if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Junction)
				{
					/**
						後列車接続の場合、最後にどの番線にいるのかと、終点となる時刻を調べる
						番線は、発着番線を初期値とし、AfterContを降順に見て、入換番線を取得します。
						ただし、同じホームへの入換がある場合は、最も前の物のみが有効となる

						終点時刻は、pOperationNoneに終点時刻が設定されている場合はそれを用います。
						NULLの場合は、AfterContを降順に全て見て、時刻が見つかればそれを用います。
						このとき、入換作業が有効かどうかのチェックが必要です。
						AfterContを見てもNULLの場合は、BeforeContを昇順にみて、時刻が見つかればそこで終了です。
						このとき、入換作業が有効かどうかのチェックが必要です。
						それでもNULLの場合は、当駅着時刻を用います。
					*/
					pLastOperation->clearOperationNumber();

					int iRessyaTrackIndex = pEkiJikokuSyuuchaku->getRessyaTrackIndex();

					CdDedJikoku aTerminalJikoku;
					CdDedJikoku aJunctionJikoku;
					int iPrevRessyahoukou = 0;

					for (int idxa = 0; idxa < pAfterCont->size() - 1; idxa++)
					{
						CentDedAfterOperation* pAfterOperation = pAfterCont->getMuPtr()->get(idxa);
						if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
						{
							/**
								同じ番線への入換は、最も前の物のみが有効
							*/
							if (iRessyaTrackIndex == pAfterOperation->getShuntTrackIndex())
							{
								continue;
							}
							aTerminalJikoku = pAfterOperation->getOperationChakuJikoku(true);
							aJunctionJikoku = pAfterOperation->getOperationChakuJikoku(true);
							if ((iRessyaTrackIndex > pAfterOperation->getShuntTrackIndex() &&
								pCentDedRessya->getRessyahoukou() == Ressyahoukou_Kudari) ||
								(iRessyaTrackIndex < pAfterOperation->getShuntTrackIndex() &&
									pCentDedRessya->getRessyahoukou() == Ressyahoukou_Nobori))
							{
								iPrevRessyahoukou = 2;
							}
							else
							{
								iPrevRessyahoukou = -2;
							}
							iRessyaTrackIndex = pAfterOperation->getShuntTrackIndex();
						}
						else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
						{
							aTerminalJikoku = pAfterOperation->getConnectJikoku();
						}
						else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
						{
							aTerminalJikoku = pAfterOperation->getReleaseJikoku();
						}
					}
					if (!pLastOperation->getTerminalJikoku().isNull())
					{
						aTerminalJikoku = pLastOperation->getTerminalJikoku();
					}

					int iRessyaTrackIndexTemp = pEkiJikokuSyuuchaku->getRessyaTrackIndex();
					for (int idxb = pBeforeCont->size() - 1; idxb >= 0; idxb--)
					{
						CentDedBeforeOperation* pBeforeOperation = pBeforeCont->getMuPtr()->get(idxb);
						if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
						{
							/**
								同じ番線への入換は、最も後の物のみが有効
							*/
							if (iRessyaTrackIndexTemp == pBeforeOperation->getShuntTrackIndex())
							{
								continue;
							}
							if (aTerminalJikoku.isNull())
							{
								aTerminalJikoku = pBeforeOperation->getOperationChakuJikoku(true);
							}
							if (aJunctionJikoku.isNull())
							{
								aJunctionJikoku = pBeforeOperation->getOperationChakuJikoku(true);
								if ((pEkiJikokuSyuuchaku->getRessyaTrackIndex() > pBeforeOperation->getShuntTrackIndex() &&
									pCentDedRessya->getRessyahoukou() == Ressyahoukou_Kudari) ||
									(pEkiJikokuSyuuchaku->getRessyaTrackIndex() < pBeforeOperation->getShuntTrackIndex() &&
										pCentDedRessya->getRessyahoukou() == Ressyahoukou_Nobori))
								{
									iPrevRessyahoukou = -2;
								}
								else
								{
									iPrevRessyahoukou = 2;
								}
							}
						}
						else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
						{
							if (aTerminalJikoku.isNull())
							{
								aTerminalJikoku = pBeforeOperation->getConnectJikoku();
							}
						}
						else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
						{
							if (aTerminalJikoku.isNull())
							{
								aTerminalJikoku = pBeforeOperation->getReleaseJikoku();
							}
						}
					}
					if (aTerminalJikoku.isNull())
					{
						aTerminalJikoku = pEkiJikokuSyuuchaku->getChakujikoku();
					}
					if (aJunctionJikoku.isNull())
					{
						aJunctionJikoku = pEkiJikokuSyuuchaku->getChakujikoku();
						iPrevRessyahoukou = -1;
					}

					pLastOperation->setPrevRessyahoukou(iPrevRessyahoukou);
					pLastOperation->setJunctionJikoku(aJunctionJikoku);


					vector<int> iLevel;
					iLevel.push_back(iLevelAdd);

					int iEkiIndexofContExist = iEkiOrderTable[iValidSyuuchakuEkiOrder][iRessyahoukou];

					aRessyaProperty.setJikoku(aTerminalJikoku);
					RessyaElement aRessyaElement(pLastOperation, aRessyaProperty);

					contOperationElement.push_back(
						OperationElement(pLastOperation,
							iLevel,
							iValidSyuuchakuEkiOrder,
							iEkiIndexofContExist,
							iRessyaTrackIndex));

#pragma omp critical(RessyaExist)
					InsertRessyaElement(
						iEkiIndexofContExist,
						iRessyaTrackIndex,
						aRessyaElement);

#pragma omp critical(JunctionList)
					m_contJunctionList.push_back(aRessyaElement);
				}
			}

#pragma omp critical(RessyaOperationElement)
			m_contRessyaOperationElement[iRessyahoukou][idxRessya] = contOperationElement;
		}
	}

	/**
		Step2
		m_contJunctionListに収められた次列車接続を取り出し、
		SearchRessyaElementを用いて、接続可能な前列車接続(aRessyaElementNext)があるかどうかを調べる
		前列車接続が見つかったら、在線表表示に必要な情報(前列車方向や時刻)の書き込み、
		種別変更・分割・併合等の処理を行う

	*/
	int iSizeJ = m_contJunctionList.size();
#pragma omp parallel for schedule(dynamic)
	for (int idxAJunc = 0; idxAJunc < iSizeJ; idxAJunc++)
	{

		//CdDedRessyaProperty aRessyaPropertyOut = contOutOuter[idxOut];
		RessyaElement aAfterJunctionOperation = m_contJunctionList[idxAJunc];

		CdDedRessyaProperty aRessyaPropertyCurr = aAfterJunctionOperation.sRessyaProperty;
		vector<OperationElement>& contOperationElementCurr = m_contRessyaOperationElement
			[(int)aRessyaPropertyCurr.getRessyahoukou()][aRessyaPropertyCurr.getRessyaIndex()];
		int iOperationIndex = 0;
		for (; iOperationIndex < (int)contOperationElementCurr.size(); iOperationIndex++)
		{
			if (contOperationElementCurr[iOperationIndex].AfterOperation == aAfterJunctionOperation.AfterOperation)
			{
				break;
			}
		}

		CentDedAfterOperation* pAfterOperation = contOperationElementCurr[iOperationIndex].AfterOperation;
		CdDedJikoku aTerminalJikoku;
		RessyaElement aRessyaElementNext =
			SearchRessyaElement(
				&m_contRessyaExist[contOperationElementCurr[iOperationIndex].iEkiIndexofContExist][contOperationElementCurr[iOperationIndex].iRessyaTrackIndex],
				pAfterOperation,
				aTerminalJikoku);
		CentDedBeforeOperation* pBeforeOperationNext = aRessyaElementNext.BeforeOperation;
		if (pBeforeOperationNext == NULL)
		{
			continue;
		}

		EBeforeAfterType eBeforeAfterType = EBeforeAfterType::BeforeAfterType_Unrelated;
		if (pAfterOperation->getNextJunctionType() == 1)
		{
			eBeforeAfterType = EBeforeAfterType::BeforeAfterType_ClassChange;
		}
		else if (pAfterOperation->getNextJunctionType() == 2)
		{
			eBeforeAfterType = EBeforeAfterType::BeforeAfterType_PropertyChange;
		}
		else if (pAfterOperation->getNextJunctionType() == 3)
		{
			eBeforeAfterType = EBeforeAfterType::BeforeAfterType_PropertySame;
		}

		if (m_bHiddenExist && eBeforeAfterType != EBeforeAfterType::BeforeAfterType_Unrelated)
		{
			const CentDedRessya* pRessya =
				m_pDedDia->getCentDedRessyaCont(aRessyaPropertyCurr.getRessyahoukou())->getMuPtr()
				->get(aRessyaPropertyCurr.getRessyaIndex());
			const CentDedRessya* pRessyaNext =
				m_pDedDia->getCentDedRessyaCont(aRessyaElementNext.sRessyaProperty.getRessyahoukou())->getMuPtr()
				->get(aRessyaElementNext.sRessyaProperty.getRessyaIndex());
			if (m_contHidden[pRessya->getRessyasyubetsuIndex()] != m_contHidden[pRessyaNext->getRessyasyubetsuIndex()])
			{
				eBeforeAfterType = EBeforeAfterType::BeforeAfterType_Unrelated;
			}
		}


		vector<OperationElement>& contOperationElementNext = m_contRessyaOperationElement
			[(int)aRessyaElementNext.sRessyaProperty.getRessyahoukou()][aRessyaElementNext.sRessyaProperty.getRessyaIndex()];

		int iOperationIndexNext = -1;
		for (int idxoi = 0;
			idxoi < (int)contOperationElementNext.size(); idxoi++)
		{
			if (contOperationElementNext[idxoi].BeforeOperation == pBeforeOperationNext &&
				pBeforeOperationNext->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Junction)
			{
				iOperationIndexNext = idxoi;
				break;
			}
		}
		if (iOperationIndexNext == -1)
		{
			continue;
		}
		const CentDedRessya* pRessya =
			m_pDedDia->getCentDedRessyaCont(aRessyaPropertyCurr.getRessyahoukou())->getMuPtr()
			->get(aRessyaPropertyCurr.getRessyaIndex());
		//const CentDedRessya* pRessyaNext =
		//	m_pDedDia->getCentDedRessyaCont(aRessyaListNext.sRessyaProperty.getRessyahoukou())->getMuPtr()
		//	->get(aRessyaListNext.sRessyaProperty.getRessyaIndex());

#pragma omp critical(Operation)
		pAfterOperation->setJunctionSucceed(true);

		/**
			EkiOrderOfPrevSyuuchakuEki
			前列車の有効終着駅Orderを、次列車の方向に合わせたものです。
			ダイヤグラム描写において、反転駅設定の確認に用います。
		*/
		int iValidSyuuchakuEki = pRessya->getValidSyuuchakuEki();
		int iEkiIndexOfPrevSyuuchakuEki =
			pRessya->EkiIndexOfEkiOrder(iValidSyuuchakuEki);
#pragma omp critical(Operation)
		pBeforeOperationNext->setEkiOrderOfPrevSyuuchakuEki(
			m_pDedDia->getCentDedRessyaCont(aRessyaElementNext.sRessyaProperty.getRessyahoukou())
			->EkiOrderOfEkiIndex(iEkiIndexOfPrevSyuuchakuEki));

		/**
			iPrevRessyahoukou,JunctionJikoku
			在線表表示駅でダイヤグラムを描写する際に用います。
			前列車と次列車が繋がる番線の横線は、
			次列車の責任で描写を行いますが、
			描写の開始X座標(JunctionJikoku)および、左端の形状(iPrevRessyahoukou)をここで求めておきます。
			iPrevRessyahoukouは、前列車の列車方向に基づいて求められているので、
			前列車と次列車の列車方向が異なる場合は、符号を反転する必要があります。
			iPrevRessyahoukouが+1または-1の場合は、反転駅設定により向きが変わる場合があります。
			前列車が、解結編成の場合は、iPrevRessyahoukouは0になります。
		*/
#pragma omp critical(Operation)
		pBeforeOperationNext->setJunctionJikoku(pAfterOperation->getJunctionJikoku());
		int iPrevRessyahoukou = pAfterOperation->getPrevRessyahoukou();
		if (aRessyaPropertyCurr.getRessyahoukou() != aRessyaElementNext.sRessyaProperty.getRessyahoukou())
		{
			iPrevRessyahoukou *= -1;
		}
#pragma omp critical(Operation)
		pBeforeOperationNext->setPrevRessyahoukou(iPrevRessyahoukou);

		/**
			PrevRessyahoukouNoDisplay
			在線表非表示駅における、列車を接続する円弧は、
			接続する両列車が、主編成の場合(増結編成・解結編成でない場合)のみ行います。
			主編成は、iLevelのsizeが1であるかどうかで判定できます。
			また、前列車と後列車が種別変更・列車情報変更・同一列車扱いの場合、円弧の描写は行いません。
			実際の円弧の向き・形状は、反転駅設定により変化します。
		*/
		if (contOperationElementCurr[iOperationIndex].iLevel.size() == 1 &&
			contOperationElementNext[iOperationIndexNext].iLevel.size() == 1 &&
			eBeforeAfterType == EBeforeAfterType::BeforeAfterType_Unrelated)
		{
			if (aRessyaPropertyCurr.getRessyahoukou() == aRessyaElementNext.sRessyaProperty.getRessyahoukou())
			{
#pragma omp critical(Operation)
				pBeforeOperationNext->setPrevRessyahoukouNoDisplay(-1);
			}
			else
			{
#pragma omp critical(Operation)
				pBeforeOperationNext->setPrevRessyahoukouNoDisplay(+1);
			}
			const CentDedEkiJikoku* pEkiJikoku = pRessya->getCentDedEkiJikokuCont()
				->getMuPtr()->get(iValidSyuuchakuEki);
#pragma omp critical(Operation)
			pBeforeOperationNext->setJunctionJikokuNoDisplay(pEkiJikoku->getChakujikoku());
		}

		/**
			種別変更・列車情報変更・同一列車扱いの処理
			iRessyaType
			0:主編成
			1:解結・増結編成
			2:その他
		*/
		int iPrevRessyaType = 2;
		if (contOperationElementCurr[iOperationIndex].iLevel.size() == 1)
		{
			iPrevRessyaType = 0;
		}
		else
		{
			/**
				この作業が主編成から解結されている(解結の繰り返しは可)かどうかを確認します。
			*/
			vector<int> iLevelParent = contOperationElementCurr[iOperationIndex].iLevel;
			bool bReleaseValid = true;
			while (iLevelParent.size() > 1)
			{
				iLevelParent.pop_back();
				for (int iOperationIndexParent = 0;
					iOperationIndexParent < (int)contOperationElementCurr.size(); iOperationIndexParent++)
				{
					if (contOperationElementCurr[iOperationIndexParent].iLevel != iLevelParent)
					{
						continue;
					}
					/**
						親作業が、増結(BeforeConnectかAfterConnect)だった場合は、
						bReleaseValidをfalseにして終了。
					*/
					if ((contOperationElementCurr[iOperationIndexParent].BeforeOperation != NULL &&
						contOperationElementCurr[iOperationIndexParent].BeforeOperation->getBOperation()
						== CentDedBeforeOperation::EBOperation::BOperation_Connect) ||
						(contOperationElementCurr[iOperationIndexParent].AfterOperation != NULL &&
							contOperationElementCurr[iOperationIndexParent].AfterOperation->getAOperation()
							== CentDedAfterOperation::EAOperation::AOperation_Connect))
					{
						bReleaseValid = false;
						break;
					}
				}
			}
			if (bReleaseValid)
			{
				iPrevRessyaType = 1;
			}
		}
		int iNextRessyaType = 2;
		if (contOperationElementNext[iOperationIndexNext].iLevel.size() == 1)
		{
			iNextRessyaType = 0;
		}
		else
		{
			/**
				次作業が主編成に増結している(増結の繰り返しは可)かどうかの確認を行います。
			*/
			vector<int> iLevelParent = contOperationElementNext[iOperationIndexNext].iLevel;
			bool bConnectValid = true;
			while (iLevelParent.size() > 1)
			{
				iLevelParent.pop_back();
				for (int iOperationIndexParent = 0;
					iOperationIndexParent < (int)contOperationElementNext.size(); iOperationIndexParent++)
				{
					if (contOperationElementNext[iOperationIndexParent].iLevel != iLevelParent)
					{
						continue;
					}
					/**
						親作業が、解結(BeforeReleaseかAfterRelease)だった場合は、
						bConnectValidをfalseにして終了。
					*/
					if ((contOperationElementNext[iOperationIndexParent].BeforeOperation != NULL &&
						contOperationElementNext[iOperationIndexParent].BeforeOperation->getBOperation()
						== CentDedBeforeOperation::EBOperation::BOperation_Release) ||
						(contOperationElementNext[iOperationIndexParent].AfterOperation != NULL &&
							contOperationElementNext[iOperationIndexParent].AfterOperation->getAOperation()
							== CentDedAfterOperation::EAOperation::AOperation_Release))
					{
						bConnectValid = false;
						break;
					}
				}
			}
			if (bConnectValid)
			{
				iNextRessyaType = 1;
			}
		}

		/**
			列車一体化、増結、解結の処理
			ここでは、列車位置の移動および、ReleaseEkiOrder・ConnectEkiOrderの設定と、
			m_contBeforeContinueList、m_contAfterContinueListへの格納を行います。
			同方向順並び
				両方主編成：一本化(前の列車に統合)
				前列車主編成・次列車増結編成：前列車はConnectEkiOrderの設定と、次列車の左への移動
				前列車解結編成・次列車主編成：次列車はReleaseEkiOrderの設定と、前列車の右への移動
			同方向逆並び・逆方向
				カスタマイズ時刻表では、前列車始発駅・次列車終着駅の表示は行わない


			Unrelated、前列車・次列車のいずれかが、主編成・解結編成・増結編成ではない場合：
				一体化等の作業は無し、前列車側のCustomizeJikokuhyouContentをreplaceに入れ、新たなCustomizeJikokuhyouContentを作り、次に送る
			前列車が解結・次列車が増結の場合：暫定で上と同じ扱い
			前列車と次列車が逆方向の場合：前列車が主編成の場合は路線外扱い、解結編成の場合は↴+路線外表示を追加する。
				次列車が主編成の場合は路線外扱い、増結編成の場合は路線外表示+↳を追加する。
				ただし、ここでは両列車のCdDedRessyaPropertyを配列状にしてから、m_contContinueListに収める作業のみを行い、
				実際に各列車のCustomizeJikokuhyouContentに始発駅・終着駅を書き込むのは、後で実施します。

		*/
		/**
			除外対象
			次列車接続タイプが別列車
			列車方向が異なる
			前列車もしくは次列車が"その他"である
			前列車が解結編成かつ次列車が増結編成
		*/
		if (eBeforeAfterType != EBeforeAfterType::BeforeAfterType_Unrelated &&
			aRessyaPropertyCurr.getRessyahoukou() == aRessyaElementNext.sRessyaProperty.getRessyahoukou() &&
			iPrevRessyaType != 2 && iNextRessyaType != 2 &&
			!(iPrevRessyaType == 1 && iNextRessyaType == 1))
		{
			if (contOperationElementCurr[iOperationIndex].iEkiOrder <= contOperationElementNext[iOperationIndexNext].iEkiOrder)
			{
				//同方向順並び
				if (iPrevRessyaType == 1)
				{
					//解結
					//☆5 分割列車の位置変更
#pragma omp critical(contReleaseMoveList)
					{
						m_contReleaseMoveList[aRessyaPropertyCurr.getRessyahoukou()][contOperationElementCurr[iOperationIndex].iEkiOrder].
							insert(make_pair(aRessyaPropertyCurr.getRessyaIndex(), aRessyaElementNext.sRessyaProperty.getRessyaIndex()));

					}
					//実処理は後で行うのでコメントアウト
					//解結
//#pragma omp critical(CustomizeRessyaIndex)
//					{
//						//まずは、前列車と次列車それぞれのCustomizeJikokuhyouContentを探す。
//						vector<CustomizeJikokuhyouContent>& contCustomizeJikokuhyouContent =
//							m_pDedDia->getcontCustomizeRessyaIndex(aRessyaPropertyCurr.getRessyahoukou());
//						int iCustomizeIndexPrev = -1;
//						int iCustomizeIndexNext = -1;
//						for (int idx = 0; idx < (int)contCustomizeJikokuhyouContent.size(); idx++)
//						{
//							for (int idxc = 0; idxc < (int)contCustomizeJikokuhyouContent[idx].iRessyaIndexCont.size(); idxc++)
//							{
//								if (contCustomizeJikokuhyouContent[idx].iRessyaIndexCont[idxc] ==
//									aRessyaPropertyCurr.getRessyaIndex())
//								{
//									iCustomizeIndexPrev = idx;
//								}
//								if (contCustomizeJikokuhyouContent[idx].iRessyaIndexCont[idxc] ==
//									aRessyaElementNext.sRessyaProperty.getRessyaIndex())
//								{
//									iCustomizeIndexNext = idx;
//								}
//
//							}
//						}
//						if (iCustomizeIndexPrev != -1 &&
//							iCustomizeIndexNext != -1)
//						{
//							//次列車にReleaseEkiOrderの設定をします
//							contCustomizeJikokuhyouContent[iCustomizeIndexNext].iReleaseEkiOrder =
//								contOperationElementCurr[iOperationIndex].iEkiOrder;
//
//							//次列車を前列車の右に移動します
//							if (iCustomizeIndexPrev > iCustomizeIndexNext)
//							{
//								contCustomizeJikokuhyouContent.insert(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexPrev + 1,
//									contCustomizeJikokuhyouContent[iCustomizeIndexNext]);
//								contCustomizeJikokuhyouContent.erase(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexNext);
//							}
//							else if (iCustomizeIndexPrev < iCustomizeIndexNext)
//							{
//								CustomizeJikokuhyouContent temp = contCustomizeJikokuhyouContent[iCustomizeIndexNext];
//								contCustomizeJikokuhyouContent.erase(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexNext);
//								contCustomizeJikokuhyouContent.insert(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexPrev + 1,
//									temp);
//							}
//						}
//					}

				}
				else if (iNextRessyaType == 1)
				{
					//増結
					//☆6 併合列車の位置変更

#pragma omp critical(contConnectMoveList)
					{
						m_contConnectMoveList[aRessyaPropertyCurr.getRessyahoukou()][contOperationElementNext[iOperationIndexNext].iEkiOrder].
							insert(make_pair(aRessyaElementNext.sRessyaProperty.getRessyaIndex(), aRessyaPropertyCurr.getRessyaIndex()));

					}
					//実処理は後で行うのでコメントアウト

//#pragma omp critical(CustomizeRessyaIndex)
//					{
//						//まずは、前列車と次列車それぞれのCustomizeJikokuhyouContentを探す。
//						vector<CustomizeJikokuhyouContent>& contCustomizeJikokuhyouContent =
//							m_pDedDia->getcontCustomizeRessyaIndex(aRessyaPropertyCurr.getRessyahoukou());
//						int iCustomizeIndexPrev = -1;
//						int iCustomizeIndexNext = -1;
//						for (int idx = 0; idx < (int)contCustomizeJikokuhyouContent.size(); idx++)
//						{
//							for (int idxc = 0; idxc < (int)contCustomizeJikokuhyouContent[idx].iRessyaIndexCont.size(); idxc++)
//							{
//								if (contCustomizeJikokuhyouContent[idx].iRessyaIndexCont[idxc] ==
//									aRessyaPropertyCurr.getRessyaIndex())
//								{
//									iCustomizeIndexPrev = idx;
//								}
//								if (contCustomizeJikokuhyouContent[idx].iRessyaIndexCont[idxc] ==
//									aRessyaElementNext.sRessyaProperty.getRessyaIndex())
//								{
//									iCustomizeIndexNext = idx;
//								}
//
//							}
//						}
//						if (iCustomizeIndexPrev != -1 &&
//							iCustomizeIndexNext != -1)
//						{
//							//前列車にConnectEkiOrderの設定をします
//							contCustomizeJikokuhyouContent[iCustomizeIndexPrev].iConnectEkiOrder =
//								contOperationElementNext[iOperationIndexNext].iEkiOrder;
//
//							//前列車を次列車の左に移動します
//							if (iCustomizeIndexPrev > iCustomizeIndexNext)
//							{
//								CustomizeJikokuhyouContent temp = contCustomizeJikokuhyouContent[iCustomizeIndexPrev];
//								contCustomizeJikokuhyouContent.erase(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexPrev);
//								contCustomizeJikokuhyouContent.insert(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexNext,
//									temp);
//							}
//							else if (iCustomizeIndexPrev < iCustomizeIndexNext)
//							{
//								contCustomizeJikokuhyouContent.insert(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexNext,
//									contCustomizeJikokuhyouContent[iCustomizeIndexPrev]);
//								contCustomizeJikokuhyouContent.erase(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexPrev);
//							}
//						}
//					}
				}
				else
				{
					//一本化
#pragma omp critical(CustomizeRessyaIndex)
					{
						//まずは、前列車と次列車それぞれのCustomizeJikokuhyouContentを探す。
						vector<CustomizeJikokuhyouContent>& contCustomizeJikokuhyouContent =
							m_pDedDia->getcontCustomizeRessyaIndex(aRessyaPropertyCurr.getRessyahoukou());
						int iCustomizeIndexPrev = -1;
						int iCustomizeIndexNext = -1;
						for (int idx = 0; idx < (int)contCustomizeJikokuhyouContent.size(); idx++)
						{
							for (int idxc = 0; idxc < (int)contCustomizeJikokuhyouContent[idx].iRessyaIndexCont.size(); idxc++)
							{
								if (contCustomizeJikokuhyouContent[idx].iRessyaIndexCont[idxc] ==
									aRessyaPropertyCurr.getRessyaIndex())
								{
									iCustomizeIndexPrev = idx;
								}
								if (contCustomizeJikokuhyouContent[idx].iRessyaIndexCont[idxc] ==
									aRessyaElementNext.sRessyaProperty.getRessyaIndex())
								{
									iCustomizeIndexNext = idx;
								}

							}
						}
						if (iCustomizeIndexPrev != -1 &&
							iCustomizeIndexNext != -1)
						{
							//次列車のiRessyaIndexContを前列車のiRessyaIndexContの後ろに挿入します。
							//また、次列車のConnectEkiOrderで、前列車のConnectEkiOrderを上書きします。
							//次列車のcontCustomizeJikokuhyouContentは削除します。
							contCustomizeJikokuhyouContent[iCustomizeIndexPrev].iRessyaIndexCont.insert(
								contCustomizeJikokuhyouContent[iCustomizeIndexPrev].iRessyaIndexCont.end(),
								contCustomizeJikokuhyouContent[iCustomizeIndexNext].iRessyaIndexCont.begin(),
								contCustomizeJikokuhyouContent[iCustomizeIndexNext].iRessyaIndexCont.end());
							contCustomizeJikokuhyouContent[iCustomizeIndexPrev].iConnectEkiOrder =
								contCustomizeJikokuhyouContent[iCustomizeIndexNext].iConnectEkiOrder;
							contCustomizeJikokuhyouContent.erase(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexNext);
						}
					}
					//一本化の列車の組について、後列車はダイヤグラムビューで、既に列車情報を一回以上表示したものとして扱います。
					if (eBeforeAfterType == EBeforeAfterType::BeforeAfterType_PropertySame)
					{
#pragma omp critical(Operation)
						pBeforeOperationNext->setRessyajouhouOmit(true);
					}
				}
			}
		}
	}

	const CentDedEkiCont* pCentDedEkiCont = m_pDedRosen->getCentDedEkiCont();
	for (int iRessyahoukou = Ressyahoukou_Kudari; iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
	{
		//Before+Connectは下位の駅から遡っていく
		for (int iEkiOrder = pCentDedEkiCont->size() - 1; iEkiOrder >= 0; iEkiOrder--)
		{
			//(1)併合で同方向順並びのパターン(☆6)
			unordered_multimap<int, int> contConnectMoveList = m_contConnectMoveList[iRessyahoukou][iEkiOrder];
			auto itrConnectMoveList = contConnectMoveList.begin();
			for (; itrConnectMoveList != contConnectMoveList.end(); itrConnectMoveList++)
			{
				//itrConnectMoveList->first : 併合先の列車Index
				//itrConnectMoveList->second : 併合列車の列車Index

				//まずは、前列車と次列車それぞれのCustomizeJikokuhyouContentを探す。
				vector<CustomizeJikokuhyouContent>& contCustomizeJikokuhyouContent =
					m_pDedDia->getcontCustomizeRessyaIndex((ERessyahoukou)iRessyahoukou);
				int iCustomizeIndexPrev = -1;
				int iCustomizeIndexNext = -1;
				for (int idx = 0; idx < (int)contCustomizeJikokuhyouContent.size(); idx++)
				{
					for (int idxc = 0; idxc < (int)contCustomizeJikokuhyouContent[idx].iRessyaIndexCont.size(); idxc++)
					{
						if (contCustomizeJikokuhyouContent[idx].iRessyaIndexCont[idxc] ==
							itrConnectMoveList->second)
						{
							iCustomizeIndexPrev = idx;
						}
						if (contCustomizeJikokuhyouContent[idx].iRessyaIndexCont[idxc] ==
							itrConnectMoveList->first)
						{
							iCustomizeIndexNext = idx;
						}

					}
				}
				if (iCustomizeIndexPrev != -1 &&
					iCustomizeIndexNext != -1)
				{
					//前列車にConnectEkiOrderの設定をします
					contCustomizeJikokuhyouContent[iCustomizeIndexPrev].iConnectEkiOrder = iEkiOrder;

					//前列車を次列車の左に移動します
					if (iCustomizeIndexPrev > iCustomizeIndexNext)
					{
						CustomizeJikokuhyouContent temp = contCustomizeJikokuhyouContent[iCustomizeIndexPrev];
						contCustomizeJikokuhyouContent.erase(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexPrev);
						contCustomizeJikokuhyouContent.insert(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexNext,
							temp);
					}
					else if (iCustomizeIndexPrev < iCustomizeIndexNext)
					{
						contCustomizeJikokuhyouContent.insert(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexNext,
							contCustomizeJikokuhyouContent[iCustomizeIndexPrev]);
						contCustomizeJikokuhyouContent.erase(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexPrev);
					}
				}
			}
		}

		//After+Releaseは上位の駅から順に行う
		for (int iEkiOrder = 0; iEkiOrder < pCentDedEkiCont->size(); iEkiOrder++)
		{
			//(4)分割で同方向順並びのパターン(☆5)
			unordered_multimap<int, int> contReleaseMoveList = m_contReleaseMoveList[iRessyahoukou][iEkiOrder];
			auto itrReleaseMoveList = contReleaseMoveList.begin();
			for (; itrReleaseMoveList != contReleaseMoveList.end(); itrReleaseMoveList++)
			{
				//itrReleaseMoveList->first : 分割元の列車Index
				//itrReleaseMoveList->second : 分割列車の列車Index

				//まずは、前列車と次列車それぞれのCustomizeJikokuhyouContentを探す。
				vector<CustomizeJikokuhyouContent>& contCustomizeJikokuhyouContent =
					m_pDedDia->getcontCustomizeRessyaIndex((ERessyahoukou)iRessyahoukou);
				int iCustomizeIndexPrev = -1;
				int iCustomizeIndexNext = -1;
				for (int idx = 0; idx < (int)contCustomizeJikokuhyouContent.size(); idx++)
				{
					for (int idxc = 0; idxc < (int)contCustomizeJikokuhyouContent[idx].iRessyaIndexCont.size(); idxc++)
					{
						if (contCustomizeJikokuhyouContent[idx].iRessyaIndexCont[idxc] ==
							itrReleaseMoveList->first)
						{
							iCustomizeIndexPrev = idx;
						}
						if (contCustomizeJikokuhyouContent[idx].iRessyaIndexCont[idxc] ==
							itrReleaseMoveList->second)
						{
							iCustomizeIndexNext = idx;
						}

					}
				}
				if (iCustomizeIndexPrev != -1 &&
					iCustomizeIndexNext != -1)
				{
					//次列車にReleaseEkiOrderの設定をします
					contCustomizeJikokuhyouContent[iCustomizeIndexNext].iReleaseEkiOrder = iEkiOrder;

					//次列車を前列車の右に移動します
					if (iCustomizeIndexPrev > iCustomizeIndexNext)
					{
						contCustomizeJikokuhyouContent.insert(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexPrev + 1,
							contCustomizeJikokuhyouContent[iCustomizeIndexNext]);
						contCustomizeJikokuhyouContent.erase(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexNext);
					}
					else if (iCustomizeIndexPrev < iCustomizeIndexNext)
					{
						CustomizeJikokuhyouContent temp = contCustomizeJikokuhyouContent[iCustomizeIndexNext];
						contCustomizeJikokuhyouContent.erase(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexNext);
						contCustomizeJikokuhyouContent.insert(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexPrev + 1,
							temp);
					}
				}
			}
		}
	}


	//隠し種別が存在する場合、隠し種別の列車を削除します
	if (m_bHiddenExist)
	{
		for (int iRessyahoukou = Ressyahoukou_Kudari;
			iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
		{
			int iSize = pRessyaCont[iRessyahoukou]->size();
			const Mu<CentDedRessya*>* pCentDedRessyaCont = m_pDedDia->getCentDedRessyaCont((ERessyahoukou)iRessyahoukou)->getMuPtr();
#pragma omp parallel for schedule(dynamic)
			for (int idxRessya = 0; idxRessya < iSize; idxRessya++)
			{
				const CentDedRessya* pRessya =
					pCentDedRessyaCont->get(idxRessya);
				if (!m_contHidden[pRessya->getRessyasyubetsuIndex()])
				{
					continue;
				}
#pragma omp critical(CustomizeRessyaIndex)
				{
					vector<CustomizeJikokuhyouContent>& contCustomizeRessyaIndex =
						m_pDedDia->getcontCustomizeRessyaIndex((ERessyahoukou)iRessyahoukou);
					int iCustomizeIndex = -1;
					for (int idx = 0; idx < (int)contCustomizeRessyaIndex.size(); idx++)
					{
						for (int idxc = 0; idxc < (int)contCustomizeRessyaIndex[idx].iRessyaIndexCont.size(); idxc++)
						{
							if (contCustomizeRessyaIndex[idx].iRessyaIndexCont[idxc] == idxRessya)
							{
								iCustomizeIndex = idx;
							}
						}
						if (iCustomizeIndex != -1)
						{
							contCustomizeRessyaIndex.erase(contCustomizeRessyaIndex.begin() + iCustomizeIndex);
							break;
						}
					}
				}
			}
		}
	}
}

void CDedOperationConnecter::operationConnectPatternDiagram()
{
	const CentDedEkiCont* pEkiCont = m_pDedRosen->getCentDedEkiCont();
	CentDedRessyaCont* pRessyaCont[2];
	for (int iRessyahoukou = Ressyahoukou_Kudari;
		iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
	{
		pRessyaCont[iRessyahoukou] = m_pDedDia->getCentDedRessyaCont((ERessyahoukou)iRessyahoukou);
	}

	//駅・番線別ホーム使用状態リスト
	m_contRessyaExist.resize(pEkiCont->size());
	/**
		iEkiOrder->iEkiIndex対応表(分岐・環状対応)
		下り・上りの2方面×駅数のコンテナ
		[iEkiOrder][iRessyahoukou]でアクセスすると、contRessyaExistに対応するiEkiIndexを返します
		また、分岐環状駅については、iEkiIndexLoop[0]駅に集約します。従って、上り列車の場合はiEkiOrderLoop.back()に当たります
	*/
	vector<vector<int>> iEkiOrderTable;
	iEkiOrderTable.resize(pEkiCont->size());

	for (int iEki = 0; iEki < (int)m_contRessyaExist.size(); iEki++)
	{
		const CentDedEki aEki = pEkiCont->get(iEki);
		m_contRessyaExist[iEki].assign(aEki.getEkiTrack2Cont()->size(), list<RessyaElement>());

		if (aEki.getBrunchLoopPosition() == -1)
		{
			iEkiOrderTable[iEki].insert(iEkiOrderTable[iEki].begin(), iEki);
			iEkiOrderTable[m_contRessyaExist.size() - 1 - iEki].push_back(iEki);
		}
		else
		{
			deque<int> iEkiIndexLoop = aEki.getEkiIndexLoop();
			iEkiOrderTable[iEki].insert(iEkiOrderTable[iEki].begin(), iEkiIndexLoop[0]);
			iEkiOrderTable[m_contRessyaExist.size() - 1 - iEki].push_back(iEkiIndexLoop[0]);
		}
	}

	//簡易作業リスト、運用表情報リストを作成
	m_contRessyaOperationElement.resize(2);
	for (int iRessyahoukou = Ressyahoukou_Kudari;
		iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
	{
		m_contRessyaOperationElement[iRessyahoukou].assign(pRessyaCont[iRessyahoukou]->size(), vector<OperationElement>());
	}
	m_contJunctionList.clear();

	//カスタム表示モード用RessyaIndex初期化
	m_pDedDia->getcontCustomizeRessyaIndexKudari().clear();
	for (int idx = 0; idx < pRessyaCont[0]->size(); idx++)
	{
		m_pDedDia->getcontCustomizeRessyaIndexKudari().push_back(
			CustomizeJikokuhyouContent({ idx }));
	}

	m_pDedDia->getcontCustomizeRessyaIndexNobori().clear();
	for (int idx = 0; idx < pRessyaCont[1]->size(); idx++)
	{
		m_pDedDia->getcontCustomizeRessyaIndexNobori().push_back(
			CustomizeJikokuhyouContent({ idx }));
	}

	//m_contOuterConnectInsertList.resize(2);
	//m_contOuterReleaseInsertList.resize(2);
	m_contConnectMoveList.resize(2);
	m_contReleaseMoveList.resize(2);
	for (int iRessyahoukou = Ressyahoukou_Kudari;
		iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
	{
		//m_contOuterConnectInsertList[iRessyahoukou].resize(pEkiCont->size());
		//m_contOuterReleaseInsertList[iRessyahoukou].resize(pEkiCont->size());
		m_contConnectMoveList[iRessyahoukou].resize(pEkiCont->size());
		m_contReleaseMoveList[iRessyahoukou].resize(pEkiCont->size());
	}

	//m_contHidden初期化、bDisableHiddenSyubetsuがTrueの場合は、全値をfalseとする。

	m_contHidden.assign(m_pDedRosen->getCentDedRessyasyubetsuCont()->size(), false);
	m_bHiddenExist = false;
	if (!m_pDedRosen->getDisableHiddenSyubetsu())
	{
		const CentDedRessyasyubetsuCont* pCentDedRessyasyubetsuCont = m_pDedRosen->getCentDedRessyasyubetsuCont();

		for (int iRessyaSyubetsuIndex = 0; iRessyaSyubetsuIndex < pCentDedRessyasyubetsuCont->size(); iRessyaSyubetsuIndex++)
		{
			bool bHidden = pCentDedRessyasyubetsuCont->get(iRessyaSyubetsuIndex).getHidden();
			if (bHidden)
			{
				m_contHidden[iRessyaSyubetsuIndex] = true;
				m_bHiddenExist = true;
			}
		}
	}


	/*
	Step1 全列車について
			始発駅前作業から終着駅後作業まで順番に見ながら、作業抽出リストを作成する
			作業抽出リストには、開始作業・終了作業と増結・解結を抜き出す。
			次列車接続の場合は、m_contJunctionListにスタックし、接続を行うのに用いる。

	*/
	for (int iRessyahoukou = Ressyahoukou_Kudari;
		iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
	{
		int iSize = pRessyaCont[iRessyahoukou]->size();
#pragma omp parallel for schedule(dynamic)
		for (int idxRessya = 0; idxRessya < iSize; idxRessya++)
		{
			/*const */CentDedRessya* pCentDedRessya = pRessyaCont[iRessyahoukou]->getMuPtr()->get(idxRessya);

			//列車が運休状態のときは、運用探索の対象に入れず、contRessyaIndexからも削除する
			if (pCentDedRessya->isCanceled())
			{
#pragma omp critical(CustomizeRessyaIndex)
				{
					vector<CustomizeJikokuhyouContent>& contCustomizeRessyaIndex =
						m_pDedDia->getcontCustomizeRessyaIndex((ERessyahoukou)iRessyahoukou);
					int iCustomizeIndex = -1;
					for (int idx = 0; idx < (int)contCustomizeRessyaIndex.size(); idx++)
					{
						for (int idxc = 0; idxc < (int)contCustomizeRessyaIndex[idx].iRessyaIndexCont.size(); idxc++)
						{
							if (contCustomizeRessyaIndex[idx].iRessyaIndexCont[idxc] == idxRessya)
							{
								iCustomizeIndex = idx;
							}
						}
						if (iCustomizeIndex != -1)
						{
							contCustomizeRessyaIndex.erase(contCustomizeRessyaIndex.begin() + iCustomizeIndex);
							break;
						}
					}
				}
				continue;

			}

			if (pCentDedRessya->isNull())
			{
				continue;
			}

			int iValidSihatsuEkiOrder = pCentDedRessya->getValidSihatsuEki();
			int iValidSyuuchakuEkiOrder = pCentDedRessya->getValidSyuuchakuEki();
			//有効な始発駅もしくは有効な終着駅が無い場合は、運用探索の対象に入れず、contRessyaIndexからも削除する
			//また、始発駅が終着駅と同一かそれ以降にある場合も除外
			if (iValidSihatsuEkiOrder < 0 || iValidSyuuchakuEkiOrder < 0 || iValidSihatsuEkiOrder >= iValidSyuuchakuEkiOrder)
			{
#pragma omp critical(CustomizeRessyaIndex)
				{
					vector<CustomizeJikokuhyouContent>& contCustomizeRessyaIndex =
						m_pDedDia->getcontCustomizeRessyaIndex((ERessyahoukou)iRessyahoukou);
					int iCustomizeIndex = -1;
					for (int idx = 0; idx < (int)contCustomizeRessyaIndex.size(); idx++)
					{
						for (int idxc = 0; idxc < (int)contCustomizeRessyaIndex[idx].iRessyaIndexCont.size(); idxc++)
						{
							if (contCustomizeRessyaIndex[idx].iRessyaIndexCont[idxc] == idxRessya)
							{
								iCustomizeIndex = idx;
							}
						}
						if (iCustomizeIndex != -1)
						{
							contCustomizeRessyaIndex.erase(contCustomizeRessyaIndex.begin() + iCustomizeIndex);
							break;
						}
					}
				}
				continue;
			}
			/**
				分岐・環状線を考慮した駅時刻・番線取得
				・始発駅の場合、次駅の駅扱いが経由無し以外なら、iEkiOrderから着発両側・前後作業を取得。
				・次駅の駅扱いが経由無しなら、経由無しが連続した後の駅Order(iEkiOrderSearch)を取得し、
					二つが同一駅扱いなら、iEkiOrderから着時刻・前作業を、iEkiOrderSearchから発時刻・後作業を取得する。
					なお、iEkiOrderSearchの次が経由無しなら、その先をチェックする必要がある。
				・終着駅については、始発駅についての探索を逆方向に行う。
			*/
			vector<OperationElement> contOperationElement;
			CdDedRessyaProperty aRessyaProperty(
				(ERessyahoukou)iRessyahoukou,
				idxRessya);
			int iLevelAdd = 0;
			/**
				始発駅
				・出区・路線外始発の場合は、contOutOuterに入れる。
				・前列車接続の場合は、前作業を後方に見て、番線と時刻を取得して、contRessyaExistに入れる

				・それ以外の作業に、増解結がある場合も
			*/
			{
				CentDedEkiJikoku* pEkiJikokuSihatsu =
					pCentDedRessya->getCentDedEkiJikokuCont()->getMuPtr()->get(iValidSihatsuEkiOrder);
				CentDedBeforeOperationCont* pBeforeCont =
					pEkiJikokuSihatsu->getCentDedBeforeOperationCont();
				CentDedAfterOperationCont* pAfterCont =
					pEkiJikokuSihatsu->getCentDedAfterOperationCont();

				CentDedBeforeOperation* pFirstOperation = pBeforeCont->getMuPtr()->get(0);
				if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Out ||
					pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
				{
					vector<int> iLevel;
					iLevel.push_back(iLevelAdd);
					contOperationElement.push_back(OperationElement(
						pFirstOperation, iLevel, iValidSihatsuEkiOrder));

					iLevelAdd++;
				}
				else if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Junction)
				{
					/**
						前列車接続の場合、最初にどの番線にいるのか、起点となる時刻を調べる。
						番線は、発着番線を初期値とし、BeforeContを逆順に見て、入換番線を取得します。
						ただし、同じホームへの入換がある場合は、最も後の物のみが有効となる

						起点時刻は、pOperationNoneに起点時刻が設定されている場合はそれを用います。
						NULLの場合は、BeforeContを昇順に全て見て、時刻が見つかればそれを用います。
						このとき、入換作業が有効かどうかのチェックが必要です。
						BeforeContを見てもNULLの場合は、AfterContを降順にみて、時刻が見つかればそこで終了です。
						このとき、入換作業が有効かどうかのチェックが必要です。
						それでもNULLの場合は、当駅発時刻を用います。

						m_contBeforeNoneListに作業を収めておく
					*/

					pFirstOperation->clearOperationNumber();

					int iRessyaTrackIndex = pEkiJikokuSihatsu->getRessyaTrackIndex();
					for (int idxb = pBeforeCont->size() - 1; idxb > 0; idxb--)
					{
						CentDedBeforeOperation* pBeforeOperation = pBeforeCont->getMuPtr()->get(idxb);
						if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
						{
							/**
								同じ番線への入換は、最も後の物のみが有効
							*/
							if (iRessyaTrackIndex != pBeforeOperation->getShuntTrackIndex())
							{
								iRessyaTrackIndex = pBeforeOperation->getShuntTrackIndex();
							}
						}
					}

					CdDedJikoku aOriginJikoku = pFirstOperation->getOriginJikoku();
					if (aOriginJikoku.isNull())
					{
						int iRessyaTrackIndexTemp = pEkiJikokuSihatsu->getRessyaTrackIndex();
						for (int idxb = pBeforeCont->size() - 1; idxb > 0; idxb--)
						{
							CentDedBeforeOperation* pBeforeOperation = pBeforeCont->getMuPtr()->get(idxb);
							if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
							{
								/**
									同じ番線への入換は、最も後の物のみが有効
								*/
								if (iRessyaTrackIndexTemp != pBeforeOperation->getShuntTrackIndex())
								{
									aOriginJikoku = pBeforeOperation->getOperationHatsuJikoku();
									iRessyaTrackIndexTemp = pBeforeOperation->getShuntTrackIndex();
								}
							}
							else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
							{
								aOriginJikoku = pBeforeOperation->getConnectJikoku();
							}
							else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
							{
								aOriginJikoku = pBeforeOperation->getReleaseJikoku();
							}
						}
					}
					if (aOriginJikoku.isNull())
					{
						int iRessyaTrackIndexTemp = pEkiJikokuSihatsu->getRessyaTrackIndex();
						for (int idxa = 0; idxa < pAfterCont->size(); idxa++)
						{
							CentDedAfterOperation* pAfterOperation = pAfterCont->getMuPtr()->get(idxa);
							if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
							{
								/**
									同じ番線への入換は、最も前の物のみが有効
								*/
								if (iRessyaTrackIndexTemp != pAfterOperation->getShuntTrackIndex())
								{
									aOriginJikoku = pAfterOperation->getOperationHatsuJikoku();
									break;
								}
							}
							else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
							{
								aOriginJikoku = pAfterOperation->getConnectJikoku();
								break;
							}
							else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
							{
								aOriginJikoku = pAfterOperation->getReleaseJikoku();
								break;
							}
						}
					}
					if (aOriginJikoku.isNull())
					{
						aOriginJikoku = pEkiJikokuSihatsu->getHatsujikoku();
					}
					vector<int> iLevel;
					iLevel.push_back(iLevelAdd);

					int iEkiIndexofContExist = iEkiOrderTable[iValidSihatsuEkiOrder][iRessyahoukou];

					aRessyaProperty.setJikoku(aOriginJikoku);
					RessyaElement aRessyaElement(pFirstOperation, aRessyaProperty);

					contOperationElement.push_back(
						OperationElement(pFirstOperation,
							iLevel,
							iValidSihatsuEkiOrder,
							iEkiIndexofContExist,
							iRessyaTrackIndex));

#pragma omp critical(RessyaExist)
					InsertRessyaElement(
						iEkiIndexofContExist,
						iRessyaTrackIndex,
						aRessyaElement);

					for (int iShiftSecond = m_iPatternDiagramPreviewCycleSecond; iShiftSecond <= m_iPatternDiagramPreviewRange; iShiftSecond += m_iPatternDiagramPreviewCycleSecond)
					{
						CdDedJikoku aOriginJikokuPlus = aOriginJikoku;
						aOriginJikokuPlus.addSeconds(iShiftSecond);
						aRessyaElement.sRessyaProperty.setJikoku(aOriginJikokuPlus);
						aRessyaElement.iShiftSecond = iShiftSecond;
#pragma omp critical(RessyaExist)
						InsertRessyaElement(
							iEkiIndexofContExist,
							iRessyaTrackIndex,
							aRessyaElement);

						CdDedJikoku aOriginJikokuMinus = aOriginJikoku;
						aOriginJikokuMinus.addSeconds(-iShiftSecond);
						aRessyaElement.sRessyaProperty.setJikoku(aOriginJikokuMinus);
						aRessyaElement.iShiftSecond = -iShiftSecond;
#pragma omp critical(RessyaExist)
						InsertRessyaElement(
							iEkiIndexofContExist,
							iRessyaTrackIndex,
							aRessyaElement);
					}

					iLevelAdd++;
				}
				/**
					bTsuukaOuterJikokuNull
					始発駅の駅扱いが通過で、路線外始発かつ当駅着時刻がNULLの場合は、
					路線外始発作業以外は無効になります。
					したがって、下記の前作業・後作業検索はスキップします。
				*/
				bool bTsuukaOuterJikokuNull =
					pEkiJikokuSihatsu->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka &&
					pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer &&
					pFirstOperation->getChakuJikoku().isNull();

				for (int idxb = 1; idxb < (int)pBeforeCont->size() && !bTsuukaOuterJikokuNull; idxb++)
				{
					CentDedBeforeOperation* pBeforeOperation = pBeforeCont->getMuPtr()->get(idxb);
					if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
					{
						pBeforeOperation->clearOperationNumber();

						int iConnectTrackIndex = pEkiJikokuSihatsu->getRessyaTrackIndex();
						for (int idxb2 = pBeforeCont->size() - 1; idxb2 > idxb; idxb2--)
						{
							CentDedBeforeOperation* pBeforeOperation2 = pBeforeCont->getMuPtr()->get(idxb2);
							if (pBeforeOperation2->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
							{
								iConnectTrackIndex = pBeforeOperation2->getShuntTrackIndex();
							}
						}
						vector<int> iLevel;
						iLevel.push_back(iLevelAdd);
						OperationElement aOperationElement(
							pBeforeOperation, iLevel, iValidSihatsuEkiOrder);
						vector<OperationElement> contTemp = searchBeforeOperationElementLight(
							pBeforeOperation->getCentDedBeforeOperationCont(),
							pBeforeOperation->getConnectJikoku(),
							aRessyaProperty,
							iLevel,
							iValidSihatsuEkiOrder,
							iEkiOrderTable[iValidSihatsuEkiOrder][iRessyahoukou],
							iConnectTrackIndex);

						contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());
						contOperationElement.push_back(aOperationElement);

						iLevelAdd++;
					}
					else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
					{
						pBeforeOperation->clearOperationNumber();

						int iReleaseTrackIndex = pEkiJikokuSihatsu->getRessyaTrackIndex();
						for (int idxb2 = pBeforeCont->size() - 1; idxb2 > idxb; idxb2--)
						{
							CentDedBeforeOperation* pBeforeOperation2 = pBeforeCont->getMuPtr()->get(idxb2);
							if (pBeforeOperation2->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
							{
								iReleaseTrackIndex = pBeforeOperation2->getShuntTrackIndex();
							}
						}
						vector<int> iLevel;
						iLevel.push_back(iLevelAdd);
						OperationElement aOperationElement(
							pBeforeOperation, iLevel, iValidSihatsuEkiOrder);
						vector<OperationElement> contTemp = searchAfterOperationElementLight(
							pBeforeOperation->getCentDedAfterOperationCont(),
							pBeforeOperation->getReleaseJikoku(),
							aRessyaProperty,
							iLevel,
							iValidSihatsuEkiOrder,
							iEkiOrderTable[iValidSihatsuEkiOrder][iRessyahoukou],
							iReleaseTrackIndex);

						contOperationElement.push_back(aOperationElement);
						contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());

						iLevelAdd++;
					}

				}

				for (int idxa = 0; idxa < (int)pAfterCont->size() && !bTsuukaOuterJikokuNull; idxa++)
				{
					CentDedAfterOperation* pAfterOperation = pAfterCont->getMuPtr()->get(idxa);
					if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
					{
						pAfterOperation->clearOperationNumber();

						int iConnectTrackIndex = pEkiJikokuSihatsu->getRessyaTrackIndex();
						for (int idxa2 = 0; idxa2 < idxa; idxa2++)
						{
							CentDedAfterOperation* pAfterOperation2 = pAfterCont->getMuPtr()->get(idxa2);
							if (pAfterOperation2->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
							{
								iConnectTrackIndex = pAfterOperation2->getShuntTrackIndex();
							}
						}
						vector<int> iLevel;
						iLevel.push_back(iLevelAdd);
						OperationElement aOperationElement(
							pAfterOperation, iLevel, iValidSihatsuEkiOrder);
						vector<OperationElement> contTemp = searchBeforeOperationElementLight(
							pAfterOperation->getCentDedBeforeOperationCont(),
							pAfterOperation->getConnectJikoku(),
							aRessyaProperty,
							iLevel,
							iValidSihatsuEkiOrder,
							iEkiOrderTable[iValidSihatsuEkiOrder][iRessyahoukou],
							iConnectTrackIndex);

						contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());
						contOperationElement.push_back(aOperationElement);

						iLevelAdd++;
					}
					else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
					{
						pAfterOperation->clearOperationNumber();

						int iReleaseTrackIndex = pEkiJikokuSihatsu->getRessyaTrackIndex();
						for (int idxa2 = 0; idxa2 < idxa; idxa2++)
						{
							CentDedAfterOperation* pAfterOperation2 = pAfterCont->getMuPtr()->get(idxa2);
							if (pAfterOperation2->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
							{
								iReleaseTrackIndex = pAfterOperation2->getShuntTrackIndex();
							}
						}
						vector<int> iLevel;
						iLevel.push_back(iLevelAdd);
						OperationElement aOperationElement(
							pAfterOperation, iLevel, iValidSihatsuEkiOrder);
						vector<OperationElement> contTemp = searchAfterOperationElementLight(
							pAfterOperation->getCentDedAfterOperationCont(),
							pAfterOperation->getReleaseJikoku(),
							aRessyaProperty,
							iLevel,
							iValidSihatsuEkiOrder,
							iEkiOrderTable[iValidSihatsuEkiOrder][iRessyahoukou],
							iReleaseTrackIndex);

						contOperationElement.push_back(aOperationElement);
						contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());

						iLevelAdd++;
					}

				}
			}

			for (int iEkiOrder = iValidSihatsuEkiOrder + 1; iEkiOrder < iValidSyuuchakuEkiOrder; iEkiOrder++)
			{
				CentDedEkiJikoku* pEkiJikoku =
					pCentDedRessya->getCentDedEkiJikokuCont()->getMuPtr()->get(iEkiOrder);
				CentDedBeforeOperationCont* pBeforeCont =
					pEkiJikoku->getCentDedBeforeOperationCont();
				CentDedAfterOperationCont* pAfterCont =
					pEkiJikoku->getCentDedAfterOperationCont();

				for (int idxb = 0; idxb < (int)pBeforeCont->size(); idxb++)
				{
					CentDedBeforeOperation* pBeforeOperation = pBeforeCont->getMuPtr()->get(idxb);
					if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
					{
						pBeforeOperation->clearOperationNumber();

						int iConnectTrackIndex = pEkiJikoku->getRessyaTrackIndex();
						for (int idxb2 = pBeforeCont->size() - 1; idxb2 > idxb; idxb2--)
						{
							CentDedBeforeOperation* pBeforeOperation2 = pBeforeCont->getMuPtr()->get(idxb2);
							if (pBeforeOperation2->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
							{
								iConnectTrackIndex = pBeforeOperation2->getShuntTrackIndex();
							}
						}
						vector<int> iLevel;
						iLevel.push_back(iLevelAdd);
						OperationElement aOperationElement(
							pBeforeOperation, iLevel, iEkiOrder);
						vector<OperationElement> contTemp = searchBeforeOperationElementLight(
							pBeforeOperation->getCentDedBeforeOperationCont(),
							pBeforeOperation->getConnectJikoku(),
							aRessyaProperty,
							iLevel,
							iEkiOrder,
							iEkiOrderTable[iEkiOrder][iRessyahoukou],
							iConnectTrackIndex);

						contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());
						contOperationElement.push_back(aOperationElement);

						iLevelAdd++;
					}
					else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
					{
						pBeforeOperation->clearOperationNumber();

						int iReleaseTrackIndex = pEkiJikoku->getRessyaTrackIndex();
						for (int idxb2 = pBeforeCont->size() - 1; idxb2 > idxb; idxb2--)
						{
							CentDedBeforeOperation* pBeforeOperation2 = pBeforeCont->getMuPtr()->get(idxb2);
							if (pBeforeOperation2->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
							{
								iReleaseTrackIndex = pBeforeOperation2->getShuntTrackIndex();
							}
						}
						vector<int> iLevel;
						iLevel.push_back(iLevelAdd);
						OperationElement aOperationElement(
							pBeforeOperation, iLevel, iEkiOrder);
						vector<OperationElement> contTemp = searchAfterOperationElementLight(
							pBeforeOperation->getCentDedAfterOperationCont(),
							pBeforeOperation->getReleaseJikoku(),
							aRessyaProperty,
							iLevel,
							iEkiOrder,
							iEkiOrderTable[iEkiOrder][iRessyahoukou],
							iReleaseTrackIndex);

						contOperationElement.push_back(aOperationElement);
						contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());

						iLevelAdd++;
					}

				}

				for (int idxa = 0; idxa < (int)pAfterCont->size(); idxa++)
				{
					CentDedAfterOperation* pAfterOperation = pAfterCont->getMuPtr()->get(idxa);
					if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
					{
						pAfterOperation->clearOperationNumber();

						int iConnectTrackIndex = pEkiJikoku->getRessyaTrackIndex();
						for (int idxa2 = 0; idxa2 < idxa; idxa2++)
						{
							CentDedAfterOperation* pAfterOperation2 = pAfterCont->getMuPtr()->get(idxa2);
							if (pAfterOperation2->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
							{
								iConnectTrackIndex = pAfterOperation2->getShuntTrackIndex();
							}
						}
						vector<int> iLevel;
						iLevel.push_back(iLevelAdd);
						OperationElement aOperationElement(
							pAfterOperation, iLevel, iEkiOrder);
						vector<OperationElement> contTemp = searchBeforeOperationElementLight(
							pAfterOperation->getCentDedBeforeOperationCont(),
							pAfterOperation->getConnectJikoku(),
							aRessyaProperty,
							iLevel,
							iEkiOrder,
							iEkiOrderTable[iEkiOrder][iRessyahoukou],
							iConnectTrackIndex);

						contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());
						contOperationElement.push_back(aOperationElement);

						iLevelAdd++;
					}
					else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
					{
						pAfterOperation->clearOperationNumber();

						int iReleaseTrackIndex = pEkiJikoku->getRessyaTrackIndex();
						for (int idxa2 = 0; idxa2 < idxa; idxa2++)
						{
							CentDedAfterOperation* pAfterOperation2 = pAfterCont->getMuPtr()->get(idxa2);
							if (pAfterOperation2->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
							{
								iReleaseTrackIndex = pAfterOperation2->getShuntTrackIndex();
							}
						}
						vector<int> iLevel;
						iLevel.push_back(iLevelAdd);
						OperationElement aOperationElement(
							pAfterOperation, iLevel, iEkiOrder);
						vector<OperationElement> contTemp = searchAfterOperationElementLight(
							pAfterOperation->getCentDedAfterOperationCont(),
							pAfterOperation->getReleaseJikoku(),
							aRessyaProperty,
							iLevel,
							iEkiOrder,
							iEkiOrderTable[iEkiOrder][iRessyahoukou],
							iReleaseTrackIndex);

						contOperationElement.push_back(aOperationElement);
						contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());

						iLevelAdd++;
					}

				}
			}

			/**
				終着駅
				・次列車始発の場合は、後作業を見て、番線と時刻を取得して、contRessyaExistに入れる

			*/
			{
				CentDedEkiJikoku* pEkiJikokuSyuuchaku =
					pCentDedRessya->getCentDedEkiJikokuCont()->getMuPtr()->get(iValidSyuuchakuEkiOrder);
				CentDedBeforeOperationCont* pBeforeCont =
					pEkiJikokuSyuuchaku->getCentDedBeforeOperationCont();
				CentDedAfterOperationCont* pAfterCont =
					pEkiJikokuSyuuchaku->getCentDedAfterOperationCont();

				CentDedAfterOperation* pLastOperation = pAfterCont->getMuPtr()->get(INT_MAX);
				/**
					bTsuukaOuterJikokuNull
					終着駅の駅扱いが通過で、路線外終着かつ当駅発時刻がNULLの場合は、
					路線外終着作業以外は無効になります。
					したがって、下記の前作業・後作業検索はスキップします。
				*/
				bool bTsuukaOuterJikokuNull =
					pEkiJikokuSyuuchaku->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka &&
					pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer &&
					pLastOperation->getHatsuJikoku().isNull();

				for (int idxb = 0; idxb < (int)pBeforeCont->size() && !bTsuukaOuterJikokuNull; idxb++)
				{
					CentDedBeforeOperation* pBeforeOperation = pBeforeCont->getMuPtr()->get(idxb);
					if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
					{
						pBeforeOperation->clearOperationNumber();

						int iConnectTrackIndex = pEkiJikokuSyuuchaku->getRessyaTrackIndex();
						for (int idxb2 = pBeforeCont->size() - 1; idxb2 > idxb; idxb2--)
						{
							CentDedBeforeOperation* pBeforeOperation2 = pBeforeCont->getMuPtr()->get(idxb2);
							if (pBeforeOperation2->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
							{
								iConnectTrackIndex = pBeforeOperation2->getShuntTrackIndex();
							}
						}
						vector<int> iLevel;
						iLevel.push_back(iLevelAdd);
						OperationElement aOperationElement(
							pBeforeOperation, iLevel, iValidSyuuchakuEkiOrder);
						vector<OperationElement> contTemp = searchBeforeOperationElementLight(
							pBeforeOperation->getCentDedBeforeOperationCont(),
							pBeforeOperation->getConnectJikoku(),
							aRessyaProperty,
							iLevel,
							iValidSyuuchakuEkiOrder,
							iEkiOrderTable[iValidSyuuchakuEkiOrder][iRessyahoukou],
							iConnectTrackIndex);

						contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());
						contOperationElement.push_back(aOperationElement);

						iLevelAdd++;
					}
					else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
					{
						pBeforeOperation->clearOperationNumber();

						int iReleaseTrackIndex = pEkiJikokuSyuuchaku->getRessyaTrackIndex();
						for (int idxb2 = pBeforeCont->size() - 1; idxb2 > idxb; idxb2--)
						{
							CentDedBeforeOperation* pBeforeOperation2 = pBeforeCont->getMuPtr()->get(idxb2);
							if (pBeforeOperation2->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
							{
								iReleaseTrackIndex = pBeforeOperation2->getShuntTrackIndex();
							}
						}
						vector<int> iLevel;
						iLevel.push_back(iLevelAdd);
						OperationElement aOperationElement(
							pBeforeOperation, iLevel, iValidSyuuchakuEkiOrder);
						vector<OperationElement> contTemp = searchAfterOperationElementLight(
							pBeforeOperation->getCentDedAfterOperationCont(),
							pBeforeOperation->getReleaseJikoku(),
							aRessyaProperty,
							iLevel,
							iValidSyuuchakuEkiOrder,
							iEkiOrderTable[iValidSyuuchakuEkiOrder][iRessyahoukou],
							iReleaseTrackIndex);

						contOperationElement.push_back(aOperationElement);
						contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());

						iLevelAdd++;
					}

				}

				for (int idxa = 0; idxa < (int)pAfterCont->size() - 1 && !bTsuukaOuterJikokuNull; idxa++)
				{
					CentDedAfterOperation* pAfterOperation = pAfterCont->getMuPtr()->get(idxa);
					if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
					{
						pAfterOperation->clearOperationNumber();

						int iConnectTrackIndex = pEkiJikokuSyuuchaku->getRessyaTrackIndex();
						for (int idxa2 = 0; idxa2 < idxa; idxa2++)
						{
							CentDedAfterOperation* pAfterOperation2 = pAfterCont->getMuPtr()->get(idxa2);
							if (pAfterOperation2->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
							{
								iConnectTrackIndex = pAfterOperation2->getShuntTrackIndex();
							}
						}
						vector<int> iLevel;
						iLevel.push_back(iLevelAdd);
						OperationElement aOperationElement(
							pAfterOperation, iLevel, iValidSyuuchakuEkiOrder);
						vector<OperationElement> contTemp = searchBeforeOperationElementLight(
							pAfterOperation->getCentDedBeforeOperationCont(),
							pAfterOperation->getConnectJikoku(),
							aRessyaProperty,
							iLevel,
							iValidSyuuchakuEkiOrder,
							iEkiOrderTable[iValidSyuuchakuEkiOrder][iRessyahoukou],
							iConnectTrackIndex);

						contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());
						contOperationElement.push_back(aOperationElement);

						iLevelAdd++;
					}
					else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
					{
						pAfterOperation->clearOperationNumber();

						int iReleaseTrackIndex = pEkiJikokuSyuuchaku->getRessyaTrackIndex();
						for (int idxa2 = 0; idxa2 < idxa; idxa2++)
						{
							CentDedAfterOperation* pAfterOperation2 = pAfterCont->getMuPtr()->get(idxa2);
							if (pAfterOperation2->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
							{
								iReleaseTrackIndex = pAfterOperation2->getShuntTrackIndex();
							}
						}
						vector<int> iLevel;
						iLevel.push_back(iLevelAdd);
						OperationElement aOperationElement(
							pAfterOperation, iLevel, iValidSyuuchakuEkiOrder);
						vector<OperationElement> contTemp = searchAfterOperationElementLight(
							pAfterOperation->getCentDedAfterOperationCont(),
							pAfterOperation->getReleaseJikoku(),
							aRessyaProperty,
							iLevel,
							iValidSyuuchakuEkiOrder,
							iEkiOrderTable[iValidSyuuchakuEkiOrder][iRessyahoukou],
							iReleaseTrackIndex);

						contOperationElement.push_back(aOperationElement);
						contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());

						iLevelAdd++;
					}

				}

				if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_In ||
					pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
				{
					pLastOperation->clearOperationNumber();
					vector<int> iLevel;
					iLevel.push_back(iLevelAdd);
					contOperationElement.push_back(OperationElement(
						pLastOperation, iLevel, iValidSyuuchakuEkiOrder));
				}
				else if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Junction)
				{
					/**
						後列車接続の場合、最後にどの番線にいるのかと、終点となる時刻を調べる
						番線は、発着番線を初期値とし、AfterContを降順に見て、入換番線を取得します。
						ただし、同じホームへの入換がある場合は、最も前の物のみが有効となる

						終点時刻は、pOperationNoneに終点時刻が設定されている場合はそれを用います。
						NULLの場合は、AfterContを降順に全て見て、時刻が見つかればそれを用います。
						このとき、入換作業が有効かどうかのチェックが必要です。
						AfterContを見てもNULLの場合は、BeforeContを昇順にみて、時刻が見つかればそこで終了です。
						このとき、入換作業が有効かどうかのチェックが必要です。
						それでもNULLの場合は、当駅着時刻を用います。
					*/
					pLastOperation->clearOperationNumber();

					int iRessyaTrackIndex = pEkiJikokuSyuuchaku->getRessyaTrackIndex();

					CdDedJikoku aTerminalJikoku;
					CdDedJikoku aJunctionJikoku;
					int iPrevRessyahoukou = 0;

					for (int idxa = 0; idxa < pAfterCont->size() - 1; idxa++)
					{
						CentDedAfterOperation* pAfterOperation = pAfterCont->getMuPtr()->get(idxa);
						if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
						{
							/**
								同じ番線への入換は、最も前の物のみが有効
							*/
							if (iRessyaTrackIndex == pAfterOperation->getShuntTrackIndex())
							{
								continue;
							}
							aTerminalJikoku = pAfterOperation->getOperationChakuJikoku(true);
							aJunctionJikoku = pAfterOperation->getOperationChakuJikoku(true);
							if ((iRessyaTrackIndex > pAfterOperation->getShuntTrackIndex() &&
								pCentDedRessya->getRessyahoukou() == Ressyahoukou_Kudari) ||
								(iRessyaTrackIndex < pAfterOperation->getShuntTrackIndex() &&
									pCentDedRessya->getRessyahoukou() == Ressyahoukou_Nobori))
							{
								iPrevRessyahoukou = 2;
							}
							else
							{
								iPrevRessyahoukou = -2;
							}
							iRessyaTrackIndex = pAfterOperation->getShuntTrackIndex();
						}
						else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
						{
							aTerminalJikoku = pAfterOperation->getConnectJikoku();
						}
						else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
						{
							aTerminalJikoku = pAfterOperation->getReleaseJikoku();
						}
					}
					if (!pLastOperation->getTerminalJikoku().isNull())
					{
						aTerminalJikoku = pLastOperation->getTerminalJikoku();
					}

					int iRessyaTrackIndexTemp = pEkiJikokuSyuuchaku->getRessyaTrackIndex();
					for (int idxb = pBeforeCont->size() - 1; idxb >= 0; idxb--)
					{
						CentDedBeforeOperation* pBeforeOperation = pBeforeCont->getMuPtr()->get(idxb);
						if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
						{
							/**
								同じ番線への入換は、最も後の物のみが有効
							*/
							if (iRessyaTrackIndexTemp == pBeforeOperation->getShuntTrackIndex())
							{
								continue;
							}
							if (aTerminalJikoku.isNull())
							{
								aTerminalJikoku = pBeforeOperation->getOperationChakuJikoku(true);
							}
							if (aJunctionJikoku.isNull())
							{
								aJunctionJikoku = pBeforeOperation->getOperationChakuJikoku(true);
								if ((pEkiJikokuSyuuchaku->getRessyaTrackIndex() > pBeforeOperation->getShuntTrackIndex() &&
									pCentDedRessya->getRessyahoukou() == Ressyahoukou_Kudari) ||
									(pEkiJikokuSyuuchaku->getRessyaTrackIndex() < pBeforeOperation->getShuntTrackIndex() &&
										pCentDedRessya->getRessyahoukou() == Ressyahoukou_Nobori))
								{
									iPrevRessyahoukou = -2;
								}
								else
								{
									iPrevRessyahoukou = 2;
								}
							}
						}
						else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
						{
							if (aTerminalJikoku.isNull())
							{
								aTerminalJikoku = pBeforeOperation->getConnectJikoku();
							}
						}
						else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
						{
							if (aTerminalJikoku.isNull())
							{
								aTerminalJikoku = pBeforeOperation->getReleaseJikoku();
							}
						}
					}
					if (aTerminalJikoku.isNull())
					{
						aTerminalJikoku = pEkiJikokuSyuuchaku->getChakujikoku();
					}
					if (aJunctionJikoku.isNull())
					{
						aJunctionJikoku = pEkiJikokuSyuuchaku->getChakujikoku();
						iPrevRessyahoukou = -1;
					}

					pLastOperation->setPrevRessyahoukou(iPrevRessyahoukou);
					pLastOperation->setJunctionJikoku(aJunctionJikoku);


					vector<int> iLevel;
					iLevel.push_back(iLevelAdd);

					int iEkiIndexofContExist = iEkiOrderTable[iValidSyuuchakuEkiOrder][iRessyahoukou];

					aRessyaProperty.setJikoku(aTerminalJikoku);
					RessyaElement aRessyaElement(pLastOperation, aRessyaProperty);

					contOperationElement.push_back(
						OperationElement(pLastOperation,
							iLevel,
							iValidSyuuchakuEkiOrder,
							iEkiIndexofContExist,
							iRessyaTrackIndex));

#pragma omp critical(RessyaExist)
					InsertRessyaElement(
						iEkiIndexofContExist,
						iRessyaTrackIndex,
						aRessyaElement);

#pragma omp critical(JunctionList)
					m_contJunctionList.push_back(aRessyaElement);

					for (int iShiftSecond = m_iPatternDiagramPreviewCycleSecond; iShiftSecond <= m_iPatternDiagramPreviewRange; iShiftSecond += m_iPatternDiagramPreviewCycleSecond)
					{
						CdDedJikoku aTerminalJikokuPlus = aTerminalJikoku;
						aTerminalJikokuPlus.addSeconds(iShiftSecond);
						aRessyaElement.sRessyaProperty.setJikoku(aTerminalJikokuPlus);
						aRessyaElement.iShiftSecond = iShiftSecond;
#pragma omp critical(RessyaExist)
						InsertRessyaElement(
							iEkiIndexofContExist,
							iRessyaTrackIndex,
							aRessyaElement);

#pragma omp critical(JunctionList)
						m_contJunctionList.push_back(aRessyaElement);

						CdDedJikoku aTerminalJikokuMinus = aTerminalJikoku;
						aTerminalJikokuMinus.addSeconds(-iShiftSecond);
						aRessyaElement.sRessyaProperty.setJikoku(aTerminalJikokuMinus);
						aRessyaElement.iShiftSecond = -iShiftSecond;
#pragma omp critical(RessyaExist)
						InsertRessyaElement(
							iEkiIndexofContExist,
							iRessyaTrackIndex,
							aRessyaElement);

#pragma omp critical(JunctionList)
						m_contJunctionList.push_back(aRessyaElement);
					}
				}
			}

#pragma omp critical(RessyaOperationElement)
			m_contRessyaOperationElement[iRessyahoukou][idxRessya] = contOperationElement;
		}
	}

	/**
		Step2
		m_contJunctionListに収められた次列車接続を取り出し、
		SearchRessyaElementを用いて、接続可能な前列車接続(aRessyaElementNext)があるかどうかを調べる
		前列車接続が見つかったら、在線表表示に必要な情報(前列車方向や時刻)の書き込み、
		種別変更・分割・併合等の処理を行う

	*/
	int iSizeJ = m_contJunctionList.size();
#pragma omp parallel for schedule(dynamic)
	for (int idxAJunc = 0; idxAJunc < iSizeJ; idxAJunc++)
	{

		//CdDedRessyaProperty aRessyaPropertyOut = contOutOuter[idxOut];
		RessyaElement aAfterJunctionOperation = m_contJunctionList[idxAJunc];

		CdDedRessyaProperty aRessyaPropertyCurr = aAfterJunctionOperation.sRessyaProperty;
		vector<OperationElement>& contOperationElementCurr = m_contRessyaOperationElement
			[(int)aRessyaPropertyCurr.getRessyahoukou()][aRessyaPropertyCurr.getRessyaIndex()];
		int iOperationIndex = 0;
		for (; iOperationIndex < (int)contOperationElementCurr.size(); iOperationIndex++)
		{
			if (contOperationElementCurr[iOperationIndex].AfterOperation == aAfterJunctionOperation.AfterOperation)
			{
				break;
			}
		}

		CentDedAfterOperation* pAfterOperation = contOperationElementCurr[iOperationIndex].AfterOperation;
		CdDedJikoku aTerminalJikoku;
		RessyaElement aRessyaElementNext =
			SearchRessyaElement(
				&m_contRessyaExist[contOperationElementCurr[iOperationIndex].iEkiIndexofContExist][contOperationElementCurr[iOperationIndex].iRessyaTrackIndex],
				pAfterOperation,
				aTerminalJikoku,
				aAfterJunctionOperation.iShiftSecond);

		//前接続、次接続が共にコピーされたRessyaElementなら、以下省略します
		if (aAfterJunctionOperation.iShiftSecond != 0 && aRessyaElementNext.iShiftSecond != 0)
		{
			continue;
		}

		CentDedBeforeOperation* pBeforeOperationNext = aRessyaElementNext.BeforeOperation;
		if (pBeforeOperationNext == NULL)
		{
			continue;
		}

		EBeforeAfterType eBeforeAfterType = EBeforeAfterType::BeforeAfterType_Unrelated;
		if (pAfterOperation->getNextJunctionType() == 1)
		{
			eBeforeAfterType = EBeforeAfterType::BeforeAfterType_ClassChange;
		}
		else if (pAfterOperation->getNextJunctionType() == 2)
		{
			eBeforeAfterType = EBeforeAfterType::BeforeAfterType_PropertyChange;
		}
		else if (pAfterOperation->getNextJunctionType() == 3)
		{
			eBeforeAfterType = EBeforeAfterType::BeforeAfterType_PropertySame;
		}

		//表示省略種別がある場合は、該当するかどうかを確かめ、前後いずれかが表示省略なら、別列車とします
		if (m_bHiddenExist && eBeforeAfterType != EBeforeAfterType::BeforeAfterType_Unrelated)
		{
			const CentDedRessya* pRessya =
				m_pDedDia->getCentDedRessyaCont(aRessyaPropertyCurr.getRessyahoukou())->getMuPtr()
				->get(aRessyaPropertyCurr.getRessyaIndex());
			const CentDedRessya* pRessyaNext =
				m_pDedDia->getCentDedRessyaCont(aRessyaElementNext.sRessyaProperty.getRessyahoukou())->getMuPtr()
				->get(aRessyaElementNext.sRessyaProperty.getRessyaIndex());
			if (m_contHidden[pRessya->getRessyasyubetsuIndex()] != m_contHidden[pRessyaNext->getRessyasyubetsuIndex()])
			{
				eBeforeAfterType = EBeforeAfterType::BeforeAfterType_Unrelated;
			}
		}

		//次列車のcontOperationElementNextの中から、当該前列車接続作業を探します。
		vector<OperationElement>& contOperationElementNext = m_contRessyaOperationElement
			[(int)aRessyaElementNext.sRessyaProperty.getRessyahoukou()][aRessyaElementNext.sRessyaProperty.getRessyaIndex()];

		int iOperationIndexNext = -1;
		for (int idxoi = 0;
			idxoi < (int)contOperationElementNext.size(); idxoi++)
		{
			if (contOperationElementNext[idxoi].BeforeOperation == pBeforeOperationNext &&
				pBeforeOperationNext->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Junction)
			{
				iOperationIndexNext = idxoi;
				break;
			}
		}
		if (iOperationIndexNext == -1)
		{
			continue;
		}
		const CentDedRessya* pRessya =
			m_pDedDia->getCentDedRessyaCont(aRessyaPropertyCurr.getRessyahoukou())->getMuPtr()
			->get(aRessyaPropertyCurr.getRessyaIndex());
		//const CentDedRessya* pRessyaNext =
		//	m_pDedDia->getCentDedRessyaCont(aRessyaListNext.sRessyaProperty.getRessyahoukou())->getMuPtr()
		//	->get(aRessyaListNext.sRessyaProperty.getRessyaIndex());

		//pAfterOperationへの書き込みは、コピー元列車の場合のみ
		if (aAfterJunctionOperation.iShiftSecond == 0)
		{
#pragma omp critical(Operation)
			pAfterOperation->setJunctionSucceed(true);
		}

		//pBeforeOperationNextへの書き込みは、コピー元列車の場合のみ
		if (aRessyaElementNext.iShiftSecond == 0)
		{
			/**
				EkiOrderOfPrevSyuuchakuEki
				前列車の有効終着駅Orderを、次列車の方向に合わせたものです。
				ダイヤグラム描写において、反転駅設定の確認に用います。
			*/
			int iValidSyuuchakuEki = pRessya->getValidSyuuchakuEki();
			int iEkiIndexOfPrevSyuuchakuEki =
				pRessya->EkiIndexOfEkiOrder(iValidSyuuchakuEki);
#pragma omp critical(Operation)
			pBeforeOperationNext->setEkiOrderOfPrevSyuuchakuEki(
				m_pDedDia->getCentDedRessyaCont(aRessyaElementNext.sRessyaProperty.getRessyahoukou())
				->EkiOrderOfEkiIndex(iEkiIndexOfPrevSyuuchakuEki));

			/**
				iPrevRessyahoukou,JunctionJikoku
				在線表表示駅でダイヤグラムを描写する際に用います。
				前列車と次列車が繋がる番線の横線は、
				次列車の責任で描写を行いますが、
				描写の開始X座標(JunctionJikoku)および、左端の形状(iPrevRessyahoukou)をここで求めておきます。
				iPrevRessyahoukouは、前列車の列車方向に基づいて求められているので、
				前列車と次列車の列車方向が異なる場合は、符号を反転する必要があります。
				iPrevRessyahoukouが+1または-1の場合は、反転駅設定により向きが変わる場合があります。
				前列車が、解結編成の場合は、iPrevRessyahoukouは0になります。

				PatternDiagramでは、JunctionJikokuを求めるときに、前列車のiShiftSecondを足します。
				前列車のもつJunctionJikokuは、コピー元のものだからです。
			*/
			CdDedJikoku aJunctionJikoku = pAfterOperation->getJunctionJikoku();
			aJunctionJikoku.addSeconds(aAfterJunctionOperation.iShiftSecond);

#pragma omp critical(Operation)
			pBeforeOperationNext->setJunctionJikoku(aJunctionJikoku);
			int iPrevRessyahoukou = pAfterOperation->getPrevRessyahoukou();
			if (aRessyaPropertyCurr.getRessyahoukou() != aRessyaElementNext.sRessyaProperty.getRessyahoukou())
			{
				iPrevRessyahoukou *= -1;
			}
#pragma omp critical(Operation)
			pBeforeOperationNext->setPrevRessyahoukou(iPrevRessyahoukou);

			/**
				PrevRessyahoukouNoDisplay
				在線表非表示駅における、列車を接続する円弧は、
				接続する両列車が、主編成の場合(増結編成・解結編成でない場合)のみ行います。
				主編成は、iLevelのsizeが1であるかどうかで判定できます。
				また、前列車と後列車が種別変更・列車情報変更・同一列車扱いの場合、円弧の描写は行いません。
				実際の円弧の向き・形状は、反転駅設定により変化します。

				PatternDiagramでは、JunctionJikokuNoDisplayを求めるときに、前列車のiShiftSecondを足します。
				前列車のもつJunctionJikokuNoDisplayは、コピー元のものだからです。
			*/
			if (contOperationElementCurr[iOperationIndex].iLevel.size() == 1 &&
				contOperationElementNext[iOperationIndexNext].iLevel.size() == 1 &&
				eBeforeAfterType == EBeforeAfterType::BeforeAfterType_Unrelated)
			{
				if (aRessyaPropertyCurr.getRessyahoukou() == aRessyaElementNext.sRessyaProperty.getRessyahoukou())
				{
#pragma omp critical(Operation)
					pBeforeOperationNext->setPrevRessyahoukouNoDisplay(-1);
				}
				else
				{
#pragma omp critical(Operation)
					pBeforeOperationNext->setPrevRessyahoukouNoDisplay(+1);
				}
				const CentDedEkiJikoku* pEkiJikoku = pRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iValidSyuuchakuEki);
				CdDedJikoku aJunctionJikokuNoDisplay = pEkiJikoku->getChakujikoku();
				aJunctionJikokuNoDisplay.addSeconds(aAfterJunctionOperation.iShiftSecond);
#pragma omp critical(Operation)
				pBeforeOperationNext->setJunctionJikokuNoDisplay(aJunctionJikokuNoDisplay);
			}
		}

		/**
			種別変更・列車情報変更・同一列車扱いの処理
			iRessyaType
			0:主編成
			1:解結・増結編成
			2:その他

			パターンダイヤプレビュー機能が有効な場合は、前列車と次列車、主編成と解結増結編成がともに、
			元列車(ishiftSecond==0)の場合のみ、一体化と並べ替えを行います
		*/
		//他の工程は残っていないので、元列車じゃない場合はcontinueで飛ばす
		if (aAfterJunctionOperation.iShiftSecond != 0 || aRessyaElementNext.iShiftSecond != 0)
		{
			continue;
		}

		int iPrevRessyaType = 2;
		if (contOperationElementCurr[iOperationIndex].iLevel.size() == 1)
		{
			iPrevRessyaType = 0;
		}
		else
		{
			/**
				この作業が主編成から解結されている(解結の繰り返しは可)かどうかを確認します。
			*/
			vector<int> iLevelParent = contOperationElementCurr[iOperationIndex].iLevel;
			bool bReleaseValid = true;
			while (iLevelParent.size() > 1)
			{
				iLevelParent.pop_back();
				for (int iOperationIndexParent = 0;
					iOperationIndexParent < (int)contOperationElementCurr.size(); iOperationIndexParent++)
				{
					if (contOperationElementCurr[iOperationIndexParent].iLevel != iLevelParent)
					{
						continue;
					}
					/**
						親作業が、増結(BeforeConnectかAfterConnect)だった場合は、
						bReleaseValidをfalseにして終了。
					*/
					if ((contOperationElementCurr[iOperationIndexParent].BeforeOperation != NULL &&
						contOperationElementCurr[iOperationIndexParent].BeforeOperation->getBOperation()
						== CentDedBeforeOperation::EBOperation::BOperation_Connect) ||
						(contOperationElementCurr[iOperationIndexParent].AfterOperation != NULL &&
							contOperationElementCurr[iOperationIndexParent].AfterOperation->getAOperation()
							== CentDedAfterOperation::EAOperation::AOperation_Connect))
					{
						bReleaseValid = false;
						break;
					}
				}
			}
			if (bReleaseValid)
			{
				iPrevRessyaType = 1;
			}
		}
		int iNextRessyaType = 2;
		if (contOperationElementNext[iOperationIndexNext].iLevel.size() == 1)
		{
			iNextRessyaType = 0;
		}
		else
		{
			/**
				次作業が主編成に増結している(増結の繰り返しは可)かどうかの確認を行います。
			*/
			vector<int> iLevelParent = contOperationElementNext[iOperationIndexNext].iLevel;
			bool bConnectValid = true;
			while (iLevelParent.size() > 1)
			{
				iLevelParent.pop_back();
				for (int iOperationIndexParent = 0;
					iOperationIndexParent < (int)contOperationElementNext.size(); iOperationIndexParent++)
				{
					if (contOperationElementNext[iOperationIndexParent].iLevel != iLevelParent)
					{
						continue;
					}
					/**
						親作業が、解結(BeforeReleaseかAfterRelease)だった場合は、
						bConnectValidをfalseにして終了。
					*/
					if ((contOperationElementNext[iOperationIndexParent].BeforeOperation != NULL &&
						contOperationElementNext[iOperationIndexParent].BeforeOperation->getBOperation()
						== CentDedBeforeOperation::EBOperation::BOperation_Release) ||
						(contOperationElementNext[iOperationIndexParent].AfterOperation != NULL &&
							contOperationElementNext[iOperationIndexParent].AfterOperation->getAOperation()
							== CentDedAfterOperation::EAOperation::AOperation_Release))
					{
						bConnectValid = false;
						break;
					}
				}
			}
			if (bConnectValid)
			{
				iNextRessyaType = 1;
			}
		}

		/**
			列車一体化、増結、解結の処理
			ここでは、列車位置の移動および、ReleaseEkiOrder・ConnectEkiOrderの設定と、
			m_contBeforeContinueList、m_contAfterContinueListへの格納を行います。
			同方向順並び
				両方主編成：一本化(前の列車に統合)
				前列車主編成・次列車増結編成：前列車はConnectEkiOrderの設定と、次列車の左への移動
				前列車解結編成・次列車主編成：次列車はReleaseEkiOrderの設定と、前列車の右への移動
			同方向逆並び・逆方向
				カスタマイズ時刻表では、前列車始発駅・次列車終着駅の表示は行わない


			Unrelated、前列車・次列車のいずれかが、主編成・解結編成・増結編成ではない場合：
				一体化等の作業は無し、前列車側のCustomizeJikokuhyouContentをreplaceに入れ、新たなCustomizeJikokuhyouContentを作り、次に送る
			前列車が解結・次列車が増結の場合：暫定で上と同じ扱い
			前列車と次列車が逆方向の場合：前列車が主編成の場合は路線外扱い、解結編成の場合は↴+路線外表示を追加する。
				次列車が主編成の場合は路線外扱い、増結編成の場合は路線外表示+↳を追加する。
				ただし、ここでは両列車のCdDedRessyaPropertyを配列状にしてから、m_contContinueListに収める作業のみを行い、
				実際に各列車のCustomizeJikokuhyouContentに始発駅・終着駅を書き込むのは、後で実施します。

		*/
		/**
			除外対象
			次列車接続タイプが別列車
			列車方向が異なる
			前列車もしくは次列車が"その他"である
			前列車が解結編成かつ次列車が増結編成
		*/
		if (eBeforeAfterType != EBeforeAfterType::BeforeAfterType_Unrelated &&
			aRessyaPropertyCurr.getRessyahoukou() == aRessyaElementNext.sRessyaProperty.getRessyahoukou() &&
			iPrevRessyaType != 2 && iNextRessyaType != 2 &&
			!(iPrevRessyaType == 1 && iNextRessyaType == 1))
		{
			if (contOperationElementCurr[iOperationIndex].iEkiOrder <= contOperationElementNext[iOperationIndexNext].iEkiOrder)
			{
				//同方向順並び
				if (iPrevRessyaType == 1)
				{
					//解結
					//☆5 分割列車の位置変更
#pragma omp critical(contReleaseMoveList)
					{
						m_contReleaseMoveList[aRessyaPropertyCurr.getRessyahoukou()][contOperationElementCurr[iOperationIndex].iEkiOrder].
							insert(make_pair(aRessyaPropertyCurr.getRessyaIndex(), aRessyaElementNext.sRessyaProperty.getRessyaIndex()));

					}
					//実処理は後で行うのでコメントアウト
					//解結
//#pragma omp critical(CustomizeRessyaIndex)
//					{
//						//まずは、前列車と次列車それぞれのCustomizeJikokuhyouContentを探す。
//						vector<CustomizeJikokuhyouContent>& contCustomizeJikokuhyouContent =
//							m_pDedDia->getcontCustomizeRessyaIndex(aRessyaPropertyCurr.getRessyahoukou());
//						int iCustomizeIndexPrev = -1;
//						int iCustomizeIndexNext = -1;
//						for (int idx = 0; idx < (int)contCustomizeJikokuhyouContent.size(); idx++)
//						{
//							for (int idxc = 0; idxc < (int)contCustomizeJikokuhyouContent[idx].iRessyaIndexCont.size(); idxc++)
//							{
//								if (contCustomizeJikokuhyouContent[idx].iRessyaIndexCont[idxc] ==
//									aRessyaPropertyCurr.getRessyaIndex())
//								{
//									iCustomizeIndexPrev = idx;
//								}
//								if (contCustomizeJikokuhyouContent[idx].iRessyaIndexCont[idxc] ==
//									aRessyaElementNext.sRessyaProperty.getRessyaIndex())
//								{
//									iCustomizeIndexNext = idx;
//								}
//
//							}
//						}
//						if (iCustomizeIndexPrev != -1 &&
//							iCustomizeIndexNext != -1)
//						{
//							//次列車にReleaseEkiOrderの設定をします
//							contCustomizeJikokuhyouContent[iCustomizeIndexNext].iReleaseEkiOrder =
//								contOperationElementCurr[iOperationIndex].iEkiOrder;
//
//							//次列車を前列車の右に移動します
//							if (iCustomizeIndexPrev > iCustomizeIndexNext)
//							{
//								contCustomizeJikokuhyouContent.insert(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexPrev + 1,
//									contCustomizeJikokuhyouContent[iCustomizeIndexNext]);
//								contCustomizeJikokuhyouContent.erase(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexNext);
//							}
//							else if (iCustomizeIndexPrev < iCustomizeIndexNext)
//							{
//								CustomizeJikokuhyouContent temp = contCustomizeJikokuhyouContent[iCustomizeIndexNext];
//								contCustomizeJikokuhyouContent.erase(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexNext);
//								contCustomizeJikokuhyouContent.insert(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexPrev + 1,
//									temp);
//							}
//						}
//					}

				}
				else if (iNextRessyaType == 1)
				{
					//増結
					//☆6 併合列車の位置変更

#pragma omp critical(contConnectMoveList)
					{
						m_contConnectMoveList[aRessyaPropertyCurr.getRessyahoukou()][contOperationElementNext[iOperationIndexNext].iEkiOrder].
							insert(make_pair(aRessyaElementNext.sRessyaProperty.getRessyaIndex(), aRessyaPropertyCurr.getRessyaIndex()));

					}
					//実処理は後で行うのでコメントアウト

//#pragma omp critical(CustomizeRessyaIndex)
//					{
//						//まずは、前列車と次列車それぞれのCustomizeJikokuhyouContentを探す。
//						vector<CustomizeJikokuhyouContent>& contCustomizeJikokuhyouContent =
//							m_pDedDia->getcontCustomizeRessyaIndex(aRessyaPropertyCurr.getRessyahoukou());
//						int iCustomizeIndexPrev = -1;
//						int iCustomizeIndexNext = -1;
//						for (int idx = 0; idx < (int)contCustomizeJikokuhyouContent.size(); idx++)
//						{
//							for (int idxc = 0; idxc < (int)contCustomizeJikokuhyouContent[idx].iRessyaIndexCont.size(); idxc++)
//							{
//								if (contCustomizeJikokuhyouContent[idx].iRessyaIndexCont[idxc] ==
//									aRessyaPropertyCurr.getRessyaIndex())
//								{
//									iCustomizeIndexPrev = idx;
//								}
//								if (contCustomizeJikokuhyouContent[idx].iRessyaIndexCont[idxc] ==
//									aRessyaElementNext.sRessyaProperty.getRessyaIndex())
//								{
//									iCustomizeIndexNext = idx;
//								}
//
//							}
//						}
//						if (iCustomizeIndexPrev != -1 &&
//							iCustomizeIndexNext != -1)
//						{
//							//前列車にConnectEkiOrderの設定をします
//							contCustomizeJikokuhyouContent[iCustomizeIndexPrev].iConnectEkiOrder =
//								contOperationElementNext[iOperationIndexNext].iEkiOrder;
//
//							//前列車を次列車の左に移動します
//							if (iCustomizeIndexPrev > iCustomizeIndexNext)
//							{
//								CustomizeJikokuhyouContent temp = contCustomizeJikokuhyouContent[iCustomizeIndexPrev];
//								contCustomizeJikokuhyouContent.erase(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexPrev);
//								contCustomizeJikokuhyouContent.insert(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexNext,
//									temp);
//							}
//							else if (iCustomizeIndexPrev < iCustomizeIndexNext)
//							{
//								contCustomizeJikokuhyouContent.insert(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexNext,
//									contCustomizeJikokuhyouContent[iCustomizeIndexPrev]);
//								contCustomizeJikokuhyouContent.erase(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexPrev);
//							}
//						}
//					}
				}
				else
				{
					//一本化
#pragma omp critical(CustomizeRessyaIndex)
					{
						//まずは、前列車と次列車それぞれのCustomizeJikokuhyouContentを探す。
						vector<CustomizeJikokuhyouContent>& contCustomizeJikokuhyouContent =
							m_pDedDia->getcontCustomizeRessyaIndex(aRessyaPropertyCurr.getRessyahoukou());
						int iCustomizeIndexPrev = -1;
						int iCustomizeIndexNext = -1;
						for (int idx = 0; idx < (int)contCustomizeJikokuhyouContent.size(); idx++)
						{
							for (int idxc = 0; idxc < (int)contCustomizeJikokuhyouContent[idx].iRessyaIndexCont.size(); idxc++)
							{
								if (contCustomizeJikokuhyouContent[idx].iRessyaIndexCont[idxc] ==
									aRessyaPropertyCurr.getRessyaIndex())
								{
									iCustomizeIndexPrev = idx;
								}
								if (contCustomizeJikokuhyouContent[idx].iRessyaIndexCont[idxc] ==
									aRessyaElementNext.sRessyaProperty.getRessyaIndex())
								{
									iCustomizeIndexNext = idx;
								}

							}
						}
						if (iCustomizeIndexPrev != -1 &&
							iCustomizeIndexNext != -1)
						{
							//次列車のiRessyaIndexContを前列車のiRessyaIndexContの後ろに挿入します。
							//また、次列車のConnectEkiOrderで、前列車のConnectEkiOrderを上書きします。
							//次列車のcontCustomizeJikokuhyouContentは削除します。
							contCustomizeJikokuhyouContent[iCustomizeIndexPrev].iRessyaIndexCont.insert(
								contCustomizeJikokuhyouContent[iCustomizeIndexPrev].iRessyaIndexCont.end(),
								contCustomizeJikokuhyouContent[iCustomizeIndexNext].iRessyaIndexCont.begin(),
								contCustomizeJikokuhyouContent[iCustomizeIndexNext].iRessyaIndexCont.end());
							contCustomizeJikokuhyouContent[iCustomizeIndexPrev].iConnectEkiOrder =
								contCustomizeJikokuhyouContent[iCustomizeIndexNext].iConnectEkiOrder;
							contCustomizeJikokuhyouContent.erase(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexNext);
						}
					}
					//一本化の列車の組について、後列車はダイヤグラムビューで、既に列車情報を一回以上表示したものとして扱います。
					if (eBeforeAfterType == EBeforeAfterType::BeforeAfterType_PropertySame)
					{
#pragma omp critical(Operation)
						pBeforeOperationNext->setRessyajouhouOmit(true);
					}
				}
			}
		}
	}

	const CentDedEkiCont* pCentDedEkiCont = m_pDedRosen->getCentDedEkiCont();
	for (int iRessyahoukou = Ressyahoukou_Kudari; iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
	{
		//Before+Connectは下位の駅から遡っていく
		for (int iEkiOrder = pCentDedEkiCont->size() - 1; iEkiOrder >= 0; iEkiOrder--)
		{
			//(1)併合で同方向順並びのパターン(☆6)
			unordered_multimap<int, int> contConnectMoveList = m_contConnectMoveList[iRessyahoukou][iEkiOrder];
			auto itrConnectMoveList = contConnectMoveList.begin();
			for (; itrConnectMoveList != contConnectMoveList.end(); itrConnectMoveList++)
			{
				//itrConnectMoveList->first : 併合先の列車Index
				//itrConnectMoveList->second : 併合列車の列車Index

				//まずは、前列車と次列車それぞれのCustomizeJikokuhyouContentを探す。
				vector<CustomizeJikokuhyouContent>& contCustomizeJikokuhyouContent =
					m_pDedDia->getcontCustomizeRessyaIndex((ERessyahoukou)iRessyahoukou);
				int iCustomizeIndexPrev = -1;
				int iCustomizeIndexNext = -1;
				for (int idx = 0; idx < (int)contCustomizeJikokuhyouContent.size(); idx++)
				{
					for (int idxc = 0; idxc < (int)contCustomizeJikokuhyouContent[idx].iRessyaIndexCont.size(); idxc++)
					{
						if (contCustomizeJikokuhyouContent[idx].iRessyaIndexCont[idxc] ==
							itrConnectMoveList->second)
						{
							iCustomizeIndexPrev = idx;
						}
						if (contCustomizeJikokuhyouContent[idx].iRessyaIndexCont[idxc] ==
							itrConnectMoveList->first)
						{
							iCustomizeIndexNext = idx;
						}

					}
				}
				if (iCustomizeIndexPrev != -1 &&
					iCustomizeIndexNext != -1)
				{
					//前列車にConnectEkiOrderの設定をします
					contCustomizeJikokuhyouContent[iCustomizeIndexPrev].iConnectEkiOrder = iEkiOrder;

					//前列車を次列車の左に移動します
					if (iCustomizeIndexPrev > iCustomizeIndexNext)
					{
						CustomizeJikokuhyouContent temp = contCustomizeJikokuhyouContent[iCustomizeIndexPrev];
						contCustomizeJikokuhyouContent.erase(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexPrev);
						contCustomizeJikokuhyouContent.insert(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexNext,
							temp);
					}
					else if (iCustomizeIndexPrev < iCustomizeIndexNext)
					{
						contCustomizeJikokuhyouContent.insert(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexNext,
							contCustomizeJikokuhyouContent[iCustomizeIndexPrev]);
						contCustomizeJikokuhyouContent.erase(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexPrev);
					}
				}
			}
		}

		//After+Releaseは上位の駅から順に行う
		for (int iEkiOrder = 0; iEkiOrder < pCentDedEkiCont->size(); iEkiOrder++)
		{
			//(4)分割で同方向順並びのパターン(☆5)
			unordered_multimap<int, int> contReleaseMoveList = m_contReleaseMoveList[iRessyahoukou][iEkiOrder];
			auto itrReleaseMoveList = contReleaseMoveList.begin();
			for (; itrReleaseMoveList != contReleaseMoveList.end(); itrReleaseMoveList++)
			{
				//itrReleaseMoveList->first : 分割元の列車Index
				//itrReleaseMoveList->second : 分割列車の列車Index

				//まずは、前列車と次列車それぞれのCustomizeJikokuhyouContentを探す。
				vector<CustomizeJikokuhyouContent>& contCustomizeJikokuhyouContent =
					m_pDedDia->getcontCustomizeRessyaIndex((ERessyahoukou)iRessyahoukou);
				int iCustomizeIndexPrev = -1;
				int iCustomizeIndexNext = -1;
				for (int idx = 0; idx < (int)contCustomizeJikokuhyouContent.size(); idx++)
				{
					for (int idxc = 0; idxc < (int)contCustomizeJikokuhyouContent[idx].iRessyaIndexCont.size(); idxc++)
					{
						if (contCustomizeJikokuhyouContent[idx].iRessyaIndexCont[idxc] ==
							itrReleaseMoveList->first)
						{
							iCustomizeIndexPrev = idx;
						}
						if (contCustomizeJikokuhyouContent[idx].iRessyaIndexCont[idxc] ==
							itrReleaseMoveList->second)
						{
							iCustomizeIndexNext = idx;
						}

					}
				}
				if (iCustomizeIndexPrev != -1 &&
					iCustomizeIndexNext != -1)
				{
					//次列車にReleaseEkiOrderの設定をします
					contCustomizeJikokuhyouContent[iCustomizeIndexNext].iReleaseEkiOrder = iEkiOrder;

					//次列車を前列車の右に移動します
					if (iCustomizeIndexPrev > iCustomizeIndexNext)
					{
						contCustomizeJikokuhyouContent.insert(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexPrev + 1,
							contCustomizeJikokuhyouContent[iCustomizeIndexNext]);
						contCustomizeJikokuhyouContent.erase(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexNext);
					}
					else if (iCustomizeIndexPrev < iCustomizeIndexNext)
					{
						CustomizeJikokuhyouContent temp = contCustomizeJikokuhyouContent[iCustomizeIndexNext];
						contCustomizeJikokuhyouContent.erase(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexNext);
						contCustomizeJikokuhyouContent.insert(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexPrev + 1,
							temp);
					}
				}
			}
		}
	}


	//隠し種別が存在する場合、隠し種別の列車を削除します
	if (m_bHiddenExist)
	{
		for (int iRessyahoukou = Ressyahoukou_Kudari;
			iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
		{
			int iSize = pRessyaCont[iRessyahoukou]->size();
			const Mu<CentDedRessya*>* pCentDedRessyaCont = m_pDedDia->getCentDedRessyaCont((ERessyahoukou)iRessyahoukou)->getMuPtr();
#pragma omp parallel for schedule(dynamic)
			for (int idxRessya = 0; idxRessya < iSize; idxRessya++)
			{
				const CentDedRessya* pRessya =
					pCentDedRessyaCont->get(idxRessya);
				if (!m_contHidden[pRessya->getRessyasyubetsuIndex()])
				{
					continue;
				}
#pragma omp critical(CustomizeRessyaIndex)
				{
					vector<CustomizeJikokuhyouContent>& contCustomizeRessyaIndex =
						m_pDedDia->getcontCustomizeRessyaIndex((ERessyahoukou)iRessyahoukou);
					int iCustomizeIndex = -1;
					for (int idx = 0; idx < (int)contCustomizeRessyaIndex.size(); idx++)
					{
						for (int idxc = 0; idxc < (int)contCustomizeRessyaIndex[idx].iRessyaIndexCont.size(); idxc++)
						{
							if (contCustomizeRessyaIndex[idx].iRessyaIndexCont[idxc] == idxRessya)
							{
								iCustomizeIndex = idx;
							}
						}
						if (iCustomizeIndex != -1)
						{
							contCustomizeRessyaIndex.erase(contCustomizeRessyaIndex.begin() + iCustomizeIndex);
							break;
						}
					}
				}
			}
		}
	}

	//パターンダイヤプレビュー用に、contCustomizeRessyaIndexを前後6時間分コピーする。

	for (int iRessyahoukou = Ressyahoukou_Kudari;
		iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
	{
		vector<CustomizeJikokuhyouContent>& contCustomizeRessyaIndex =
			m_pDedDia->getcontCustomizeRessyaIndex((ERessyahoukou)iRessyahoukou);

		deque<CustomizeJikokuhyouContent> contCustomizeRessyaIndexTemp;
		contCustomizeRessyaIndexTemp.insert(contCustomizeRessyaIndexTemp.begin(),contCustomizeRessyaIndex.begin(), contCustomizeRessyaIndex.end());

		deque<CustomizeJikokuhyouContent> contCustomizeRessyaIndexShift = contCustomizeRessyaIndexTemp;

		for (int iShiftSecond = m_iPatternDiagramPreviewCycleSecond; iShiftSecond <= m_iPatternDiagramPreviewRange; iShiftSecond += m_iPatternDiagramPreviewCycleSecond)
		{
			for (int idx = 0; idx < (int)contCustomizeRessyaIndexShift.size(); idx++)
			{
				contCustomizeRessyaIndexShift[idx].iShiftSecond = iShiftSecond;
			}

			contCustomizeRessyaIndexTemp.insert(contCustomizeRessyaIndexTemp.end(), contCustomizeRessyaIndexShift.begin(),contCustomizeRessyaIndexShift.end());

			for (int idx = 0; idx < (int)contCustomizeRessyaIndexShift.size(); idx++)
			{
				contCustomizeRessyaIndexShift[idx].iShiftSecond = -iShiftSecond;
			}

			contCustomizeRessyaIndexTemp.insert(contCustomizeRessyaIndexTemp.begin(), contCustomizeRessyaIndexShift.begin(), contCustomizeRessyaIndexShift.end());
		}
		contCustomizeRessyaIndex.assign(contCustomizeRessyaIndexTemp.begin(), contCustomizeRessyaIndexTemp.end());
//
//
//
//		int iSize = pRessyaCont[iRessyahoukou]->size();
//		const Mu<CentDedRessya*>* pCentDedRessyaCont = m_pDedDia->getCentDedRessyaCont((ERessyahoukou)iRessyahoukou)->getMuPtr();
//#pragma omp parallel for schedule(dynamic)
//		for (int idxRessya = 0; idxRessya < iSize; idxRessya++)
//		{
//			const CentDedRessya* pRessya =
//				pCentDedRessyaCont->get(idxRessya);
//			if (!m_contHidden[pRessya->getRessyasyubetsuIndex()])
//			{
//				continue;
//			}
//#pragma omp critical(CustomizeRessyaIndex)
//			{
//				vector<CustomizeJikokuhyouContent>& contCustomizeRessyaIndex =
//					m_pDedDia->getcontCustomizeRessyaIndex((ERessyahoukou)iRessyahoukou);
//				int iCustomizeIndex = -1;
//				for (int idx = 0; idx < (int)contCustomizeRessyaIndex.size(); idx++)
//				{
//					for (int idxc = 0; idxc < (int)contCustomizeRessyaIndex[idx].iRessyaIndexCont.size(); idxc++)
//					{
//						if (contCustomizeRessyaIndex[idx].iRessyaIndexCont[idxc] == idxRessya)
//						{
//							iCustomizeIndex = idx;
//						}
//					}
//					if (iCustomizeIndex != -1)
//					{
//						contCustomizeRessyaIndex.erase(contCustomizeRessyaIndex.begin() + iCustomizeIndex);
//						break;
//					}
//				}
//			}
//		}
	}
}

void CDedOperationConnecter::operationConnect()
{
	const CentDedEkiCont* pEkiCont = m_pDedRosen->getCentDedEkiCont();
	CentDedRessyaCont* pRessyaCont[2];
	for (int iRessyahoukou = Ressyahoukou_Kudari;
		iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
	{
		pRessyaCont[iRessyahoukou] = m_pDedDia->getCentDedRessyaCont((ERessyahoukou)iRessyahoukou);
	}
	//駅・番線別ホーム使用状態リスト
	//vector<vector<list<RessyaList2Mini>>> contRessyaExist;
	m_contRessyaExist.resize(pEkiCont->size());

	/**
		iEkiOrder->iEkiIndex対応表(分岐・環状対応)
		下り・上りの2方面×駅数のコンテナ
		[iEkiOrder][iRessyahoukou]でアクセスすると、contRessyaExistに対応するiEkiIndexを返します
		また、分岐環状駅については、iEkiIndexLoop[0]駅に集約します。従って、上り列車の場合はiEkiOrderLoop.back()に当たります
	*/
	vector<vector<int>> iEkiOrderTable;
	iEkiOrderTable.resize(pEkiCont->size());

	for (int iEki = 0; iEki < (int)m_contRessyaExist.size(); iEki++)
	{
		const CentDedEki aEki = pEkiCont->get(iEki);
		m_contRessyaExist[iEki].assign(aEki.getEkiTrack2Cont()->size(), list<RessyaElement>());

		if (aEki.getBrunchLoopPosition() == -1)
		{
			iEkiOrderTable[iEki].insert(iEkiOrderTable[iEki].begin(), iEki);
			iEkiOrderTable[m_contRessyaExist.size() - 1 - iEki].push_back(iEki);
		}
		else
		{
			deque<int> iEkiIndexLoop = aEki.getEkiIndexLoop();
			iEkiOrderTable[iEki].insert(iEkiOrderTable[iEki].begin(), iEkiIndexLoop[0]);
			iEkiOrderTable[m_contRessyaExist.size() - 1 - iEki].push_back(iEkiIndexLoop[0]);
		}
	}

	//作業抽出リスト、運用表情報リストを作成
	m_contRessyaOperationElement.resize(2);
	m_contOperationTableContentBuffer.resize(2);
	for (int iRessyahoukou = Ressyahoukou_Kudari;
		iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
	{
		m_contRessyaOperationElement[iRessyahoukou].assign(pRessyaCont[iRessyahoukou]->size(), vector<OperationElement>());
		m_contOperationTableContentBuffer[iRessyahoukou].assign(pRessyaCont[iRessyahoukou]->size(), unordered_map<tstring, OperationTableContent>());
	}

	//接続元となる各種スタックを初期化
	m_contOutOuter.clear();
	m_contNumberChange.clear();
	m_contJunctionList.clear();
	m_contConnectWaitList.clear();

	//カスタム表示モード用RessyaIndex初期化
	m_pDedDia->getcontCustomizeRessyaIndexKudari().clear();
	for (int idx = 0; idx < pRessyaCont[0]->size(); idx++)
	{
		m_pDedDia->getcontCustomizeRessyaIndexKudari().push_back(
			CustomizeJikokuhyouContent({ idx }));
	}

	m_pDedDia->getcontCustomizeRessyaIndexNobori().clear();
	for (int idx = 0; idx < pRessyaCont[1]->size(); idx++)
	{
		m_pDedDia->getcontCustomizeRessyaIndexNobori().push_back(
			CustomizeJikokuhyouContent({ idx }));
	}

	//運用表表示用、OperationTableContent初期化
	m_pDedDia->clearOperationTableContent();

	//路線外扱いの表示構築用、m_contBeforeContinueList、m_contAfterContinueList、m_contOuterConnectInsertList、m_contOuterReleaseInsertList、m_contOuterConnectInsertList、m_contOuterReleaseInsertList初期化
	m_contBeforeContinueList.resize(2);//列車方向
	m_contAfterContinueList.resize(2);
	m_contOuterConnectInsertList.resize(2);
	m_contOuterReleaseInsertList.resize(2);
	m_contConnectMoveList.resize(2);
	m_contReleaseMoveList.resize(2);
	for (int iRessyahoukou = Ressyahoukou_Kudari;
		iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
	{
		m_contBeforeContinueList[iRessyahoukou].resize(pEkiCont->size());
		m_contAfterContinueList[iRessyahoukou].resize(pEkiCont->size());
		m_contOuterConnectInsertList[iRessyahoukou].resize(pEkiCont->size());
		m_contOuterReleaseInsertList[iRessyahoukou].resize(pEkiCont->size());
		m_contConnectMoveList[iRessyahoukou].resize(pEkiCont->size());
		m_contReleaseMoveList[iRessyahoukou].resize(pEkiCont->size());
	}

	//入出区連携コード用
	m_pDedDia->clearInOutLinkCodeContent();

	//m_contHidden初期化、bDisableHiddenSyubetsuがTrueの場合は、全値をfalseとする。

	m_contHidden.assign(m_pDedRosen->getCentDedRessyasyubetsuCont()->size(), false);
	m_bHiddenExist = false;
	if (!m_pDedRosen->getDisableHiddenSyubetsu())
	{
		const CentDedRessyasyubetsuCont* pCentDedRessyasyubetsuCont = m_pDedRosen->getCentDedRessyasyubetsuCont();

		for (int iRessyaSyubetsuIndex = 0; iRessyaSyubetsuIndex < pCentDedRessyasyubetsuCont->size(); iRessyaSyubetsuIndex++)
		{
			bool bHidden = pCentDedRessyasyubetsuCont->get(iRessyaSyubetsuIndex).getHidden();
			if (bHidden)
			{
				m_contHidden[iRessyaSyubetsuIndex] = true;
				m_bHiddenExist = true;
			}
		}
	}

	/*
	Step1 全列車について
			始発駅前作業から終着駅後作業まで順番に見ながら、作業抽出リストを作成します
			リストには開始作業・終了作業・増結・解結・運用番号変更が収められます
			出区・路線外始発の場合はm_contOutOuterに、
			運用番号変更の場合はm_contNumberChangeに、
			前列車接続の場合はm_contJunctionListに、RessyaElementが収められ、
			接続を行う元とします。

			Ver2.05
			入出区及び路線外始発終着の場合は、入出区連携コードが入力されている場合、
			m_pDedDiaのcontInOutLinkCodeContentに収めて、入出区連携が有効かをチェックします。

			また、各作業に以前書き込まれた運用番号をクリアしておきます。
	*/
	for (int iRessyahoukou = Ressyahoukou_Kudari;
		iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
	{
		int iSize = pRessyaCont[iRessyahoukou]->size();
#pragma omp parallel for schedule(guided)
		for (int idxRessya = 0; idxRessya < iSize; idxRessya++)
		{
			/*const */CentDedRessya* pCentDedRessya = pRessyaCont[iRessyahoukou]->getMuPtr()->get(idxRessya);

			//列車が運休状態のときは、運用探索の対象に入れず、contRessyaIndexからも削除する
			if (pCentDedRessya->isCanceled())
			{
#pragma omp critical(CustomizeRessyaIndex)
				{
					vector<CustomizeJikokuhyouContent>& contCustomizeRessyaIndex =
						m_pDedDia->getcontCustomizeRessyaIndex((ERessyahoukou)iRessyahoukou);
					int iCustomizeIndex = -1;
					for (int idx = 0; idx < (int)contCustomizeRessyaIndex.size(); idx++)
					{
						for (int idxc = 0; idxc < (int)contCustomizeRessyaIndex[idx].iRessyaIndexCont.size(); idxc++)
						{
							if (contCustomizeRessyaIndex[idx].iRessyaIndexCont[idxc] == idxRessya)
							{
								iCustomizeIndex = idx;
							}
						}
						if (iCustomizeIndex != -1)
						{
							contCustomizeRessyaIndex.erase(contCustomizeRessyaIndex.begin() + iCustomizeIndex);
							break;
						}
					}
				}
				continue;

			}

			if (pCentDedRessya->isNull())
			{
				continue;
			}
				
			int iValidSihatsuEkiOrder = pCentDedRessya->getValidSihatsuEki();
			int iValidSyuuchakuEkiOrder = pCentDedRessya->getValidSyuuchakuEki();
			//有効な始発駅もしくは有効な終着駅が無い場合は、運用探索の対象に入れず、contRessyaIndexからも削除する
			//また、始発駅が終着駅と同一かそれ以降にある場合も除外
			if (iValidSihatsuEkiOrder < 0 || iValidSyuuchakuEkiOrder <0 || iValidSihatsuEkiOrder >= iValidSyuuchakuEkiOrder)
			{
#pragma omp critical(CustomizeRessyaIndex)
				{
					vector<CustomizeJikokuhyouContent>& contCustomizeRessyaIndex =
						m_pDedDia->getcontCustomizeRessyaIndex((ERessyahoukou)iRessyahoukou);
					int iCustomizeIndex = -1;
					for (int idx = 0; idx < (int)contCustomizeRessyaIndex.size(); idx++)
					{
						for (int idxc = 0; idxc < (int)contCustomizeRessyaIndex[idx].iRessyaIndexCont.size(); idxc++)
						{
							if (contCustomizeRessyaIndex[idx].iRessyaIndexCont[idxc] == idxRessya)
							{
								iCustomizeIndex = idx;
							}
						}
						if (iCustomizeIndex != -1)
						{
							contCustomizeRessyaIndex.erase(contCustomizeRessyaIndex.begin() + iCustomizeIndex);
							break;
						}
					}
				}
				continue;
			}

			vector<OperationElement> contOperationElement;
			CdDedRessyaProperty aRessyaProperty(
				(ERessyahoukou)iRessyahoukou,
				idxRessya);
			int iLevelAdd = 0;
			/**
				始発駅
				・出区・路線外始発の場合は、contOutOuterに入れる。
				・前列車接続の場合は、前作業を後方に見て、番線と時刻を取得して、contRessyaExistに入れる

				・増結・解結・運用番号変更はcontOperationElementに収める
			*/
			{
				CentDedEkiJikoku* pEkiJikokuSihatsu =
					pCentDedRessya->getCentDedEkiJikokuCont()->getMuPtr()->get(iValidSihatsuEkiOrder);
				CentDedBeforeOperationCont* pBeforeCont =
					pEkiJikokuSihatsu->getCentDedBeforeOperationCont();
				CentDedAfterOperationCont* pAfterCont =
					pEkiJikokuSihatsu->getCentDedAfterOperationCont();

				CentDedBeforeOperation* pFirstOperation = pBeforeCont->getMuPtr()->get(0);
				if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Out)
				{
					pFirstOperation->clearOperationNumber();

					aRessyaProperty.setJikoku(pFirstOperation->getOutJikoku());
					RessyaElement aRessyaElement(pFirstOperation, aRessyaProperty);
					vector<int> iLevel;
					iLevel.push_back(iLevelAdd);
#pragma omp critical(OutOuter)
					m_contOutOuter.push_back(aRessyaElement);
					contOperationElement.push_back(OperationElement(
						pFirstOperation, iLevel, iValidSihatsuEkiOrder));
					if (!pFirstOperation->getInOutLinkCode().empty())
					{
#pragma omp critical(InOutLink)
						insertInOutLinkCodeElement(
							pFirstOperation->getInOutLinkCode(),
							aRessyaElement);
					}

					iLevelAdd++;
				}
				else if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
				{
					pFirstOperation->clearOperationNumber();

					aRessyaProperty.setJikoku(pFirstOperation->getOuterShihatsuJikoku());
					RessyaElement aRessyaElement(pFirstOperation, aRessyaProperty);
					vector<int> iLevel;
					iLevel.push_back(iLevelAdd);
#pragma omp critical(OutOuter)
					m_contOutOuter.push_back(aRessyaElement);
					contOperationElement.push_back(OperationElement(
						pFirstOperation, iLevel, iValidSihatsuEkiOrder));
					if (!pFirstOperation->getInOutLinkCode().empty())
					{
#pragma omp critical(InOutLink)
						insertInOutLinkCodeElement(
							pFirstOperation->getInOutLinkCode(),
							aRessyaElement);
					}

					iLevelAdd++;
				}
				else if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Junction)
				{
					/**
						前列車接続の場合、最初にどの番線にいるのか、起点となる時刻を調べる。
						番線は、発着番線を初期値とし、BeforeContを逆順に見て、入換番線を取得します。
						ただし、同じホームへの入換がある場合は、最も後の物のみが有効となる

						起点時刻は、pFirstOperationに起点時刻が設定されている場合はそれを用います。
						NULLの場合は、BeforeContを昇順に全て見て、時刻が見つかればそれを用います。
						このとき、入換作業が有効かどうかのチェックが必要です。
						BeforeContを見てもNULLの場合は、AfterContを降順にみて、時刻が見つかればそこで終了です。
						このとき、入換作業が有効かどうかのチェックが必要です。
						それでもNULLの場合は、当駅発時刻を用います。

						m_contJunctionListに作業を収めておく
					*/

					pFirstOperation->clearOperationNumber();

					int iRessyaTrackIndex = pEkiJikokuSihatsu->getRessyaTrackIndex();
					for (int idxb = pBeforeCont->size() - 1; idxb > 0; idxb--)
					{
						CentDedBeforeOperation* pBeforeOperation = pBeforeCont->getMuPtr()->get(idxb);
						if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
						{
							/**
								同じ番線への入換は、最も後の物のみが有効
							*/
							if (iRessyaTrackIndex != pBeforeOperation->getShuntTrackIndex())
							{
								iRessyaTrackIndex = pBeforeOperation->getShuntTrackIndex();
							}
						}
					}

					CdDedJikoku aOriginJikoku = pFirstOperation->getOriginJikoku();
					if (aOriginJikoku.isNull())
					{
						int iRessyaTrackIndexTemp = pEkiJikokuSihatsu->getRessyaTrackIndex();
						for (int idxb = pBeforeCont->size() - 1; idxb > 0; idxb--)
						{
							CentDedBeforeOperation* pBeforeOperation = pBeforeCont->getMuPtr()->get(idxb);
							if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
							{
								/**
									同じ番線への入換は、最も後の物のみが有効
								*/
								if (iRessyaTrackIndexTemp != pBeforeOperation->getShuntTrackIndex())
								{
									aOriginJikoku = pBeforeOperation->getOperationHatsuJikoku();
									iRessyaTrackIndexTemp = pBeforeOperation->getShuntTrackIndex();
								}
							}
							else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
							{
								aOriginJikoku = pBeforeOperation->getConnectJikoku();
							}
							else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
							{
								aOriginJikoku = pBeforeOperation->getReleaseJikoku();
							}
						}
					}
					if (aOriginJikoku.isNull())
					{
						int iRessyaTrackIndexTemp = pEkiJikokuSihatsu->getRessyaTrackIndex();
						for (int idxa = 0; idxa < pAfterCont->size(); idxa++)
						{
							CentDedAfterOperation* pAfterOperation = pAfterCont->getMuPtr()->get(idxa);
							if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
							{
								/**
									同じ番線への入換は、最も前の物のみが有効
								*/
								if (iRessyaTrackIndexTemp != pAfterOperation->getShuntTrackIndex())
								{
									aOriginJikoku = pAfterOperation->getOperationHatsuJikoku();
									break;
								}
							}
							else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
							{
								aOriginJikoku = pAfterOperation->getConnectJikoku();
								break;
							}
							else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
							{
								aOriginJikoku = pAfterOperation->getReleaseJikoku();
								break;
							}
						}
					}
					if (aOriginJikoku.isNull())
					{
						aOriginJikoku = pEkiJikokuSihatsu->getHatsujikoku();
					}
					vector<int> iLevel;
					iLevel.push_back(iLevelAdd);

					int iEkiIndexofContExist = iEkiOrderTable[iValidSihatsuEkiOrder][iRessyahoukou];

					contOperationElement.push_back(
						OperationElement(pFirstOperation, 
							iLevel,
							iValidSihatsuEkiOrder,
							iEkiIndexofContExist,
							iRessyaTrackIndex));

					aRessyaProperty.setJikoku(aOriginJikoku);
					RessyaElement aRessyaElement(pFirstOperation, aRessyaProperty);

#pragma omp critical(RessyaExist)
					InsertRessyaElement(
						iEkiIndexofContExist,
						iRessyaTrackIndex,
						aRessyaElement);

#pragma omp critical(JunctionList)
					m_contJunctionList.push_back(aRessyaElement);

					iLevelAdd++;
				}
				/**
					bTsuukaOuterJikokuNull
					始発駅の駅扱いが通過で、路線外始発かつ当駅着時刻がNULLの場合は、
					路線外始発作業以外は無効になります。
					したがって、下記の前作業・後作業検索はスキップします。
				*/
				bool bTsuukaOuterJikokuNull =
					pEkiJikokuSihatsu->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka &&
					pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer &&
					pFirstOperation->getChakuJikoku().isNull();

				for (int idxb = 1; idxb < (int)pBeforeCont->size() && !bTsuukaOuterJikokuNull; idxb++)
				{
					CentDedBeforeOperation* pBeforeOperation = pBeforeCont->getMuPtr()->get(idxb);
					if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
					{
						pBeforeOperation->clearOperationNumber();

						int iConnectTrackIndex = pEkiJikokuSihatsu->getRessyaTrackIndex();
						for (int idxb2 = pBeforeCont->size() - 1; idxb2 > idxb; idxb2--)
						{
							CentDedBeforeOperation* pBeforeOperation2 = pBeforeCont->getMuPtr()->get(idxb2);
							if (pBeforeOperation2->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
							{
								iConnectTrackIndex = pBeforeOperation2->getShuntTrackIndex();
							}
						}
						vector<int> iLevel;
						iLevel.push_back(iLevelAdd);
						OperationElement aOperationElement(
							pBeforeOperation, iLevel, iValidSihatsuEkiOrder);
						vector<OperationElement> contTemp = searchBeforeOperationElement(
							pBeforeOperation->getCentDedBeforeOperationCont(),
							pBeforeOperation->getConnectJikoku(),
							aRessyaProperty,
							iLevel,
							iValidSihatsuEkiOrder,
							iEkiOrderTable[iValidSihatsuEkiOrder][iRessyahoukou],
							iConnectTrackIndex);

						contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());
						contOperationElement.push_back(aOperationElement);

						iLevelAdd++;
					}
					else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
					{
						pBeforeOperation->clearOperationNumber();

						int iReleaseTrackIndex = pEkiJikokuSihatsu->getRessyaTrackIndex();
						for (int idxb2 = pBeforeCont->size() - 1; idxb2 > idxb; idxb2--)
						{
							CentDedBeforeOperation* pBeforeOperation2 = pBeforeCont->getMuPtr()->get(idxb2);
							if (pBeforeOperation2->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
							{
								iReleaseTrackIndex = pBeforeOperation2->getShuntTrackIndex();
							}
						}
						vector<int> iLevel;
						iLevel.push_back(iLevelAdd);
						OperationElement aOperationElement(
							pBeforeOperation, iLevel, iValidSihatsuEkiOrder);
						vector<OperationElement> contTemp = searchAfterOperationElement(
							pBeforeOperation->getCentDedAfterOperationCont(),
							pBeforeOperation->getReleaseJikoku(),
							aRessyaProperty,
							iLevel,
							iValidSihatsuEkiOrder,
							iEkiOrderTable[iValidSihatsuEkiOrder][iRessyahoukou], 
							iReleaseTrackIndex);

						contOperationElement.push_back(aOperationElement);
						contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());

						iLevelAdd++;
					}
					else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_NumberChange)
					{
						pBeforeOperation->clearOperationNumber();

						//暫定措置、当駅発時刻を入れておく
						//この時刻は、運用表のどの位置に入れるかを決めるのに使う
						aRessyaProperty.setJikoku(pEkiJikokuSihatsu->getHatsujikoku());
						RessyaElement aRessyaElement(pBeforeOperation, aRessyaProperty);
						vector<int> iLevel;
						iLevel.push_back(iLevelAdd);
						//Ver2.06.05 運用番号順反転の場合は、m_contNumberChangeに入れる必要は無い。
						if (!pBeforeOperation->getOperationNumberReverse())
						{
#pragma omp critical(NumberChange)
							m_contNumberChange.push_back(aRessyaElement);
						}
						OperationElement aOperationElement(
							pBeforeOperation, iLevel, iValidSihatsuEkiOrder);

						contOperationElement.push_back(aOperationElement);

						iLevelAdd++;
					}

				}

				for (int idxa = 0; idxa < (int)pAfterCont->size() && !bTsuukaOuterJikokuNull; idxa++)
				{
					CentDedAfterOperation* pAfterOperation = pAfterCont->getMuPtr()->get(idxa);
					if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
					{
						pAfterOperation->clearOperationNumber();

						int iConnectTrackIndex = pEkiJikokuSihatsu->getRessyaTrackIndex();
						for (int idxa2 = 0; idxa2 < idxa; idxa2++)
						{
							CentDedAfterOperation* pAfterOperation2 = pAfterCont->getMuPtr()->get(idxa2);
							if (pAfterOperation2->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
							{
								iConnectTrackIndex = pAfterOperation2->getShuntTrackIndex();
							}
						}
						vector<int> iLevel;
						iLevel.push_back(iLevelAdd);
						OperationElement aOperationElement(
							pAfterOperation, iLevel, iValidSihatsuEkiOrder);
						vector<OperationElement> contTemp = searchBeforeOperationElement(
							pAfterOperation->getCentDedBeforeOperationCont(),
							pAfterOperation->getConnectJikoku(),
							aRessyaProperty,
							iLevel,
							iValidSihatsuEkiOrder,
							iEkiOrderTable[iValidSihatsuEkiOrder][iRessyahoukou], 
							iConnectTrackIndex);

						contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());
						contOperationElement.push_back(aOperationElement);

						iLevelAdd++;
					}
					else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
					{
						pAfterOperation->clearOperationNumber();

						int iReleaseTrackIndex = pEkiJikokuSihatsu->getRessyaTrackIndex();
						for (int idxa2 = 0; idxa2 < idxa; idxa2++)
						{
							CentDedAfterOperation* pAfterOperation2 = pAfterCont->getMuPtr()->get(idxa2);
							if (pAfterOperation2->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
							{
								iReleaseTrackIndex = pAfterOperation2->getShuntTrackIndex();
							}
						}
						vector<int> iLevel;
						iLevel.push_back(iLevelAdd);
						OperationElement aOperationElement(
							pAfterOperation, iLevel, iValidSihatsuEkiOrder);
						vector<OperationElement> contTemp = searchAfterOperationElement(
							pAfterOperation->getCentDedAfterOperationCont(),
							pAfterOperation->getReleaseJikoku(),
							aRessyaProperty,
							iLevel,
							iValidSihatsuEkiOrder,
							iEkiOrderTable[iValidSihatsuEkiOrder][iRessyahoukou],
							iReleaseTrackIndex);

						contOperationElement.push_back(aOperationElement);
						contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());

						iLevelAdd++;
					}
					else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_NumberChange)
					{
						pAfterOperation->clearOperationNumber();
						//暫定措置、当駅発時刻を入れておく
						//この時刻は、運用表のどの位置に入れるかを決めるのに使う
						aRessyaProperty.setJikoku(pEkiJikokuSihatsu->getHatsujikoku());
						RessyaElement aRessyaElement(pAfterOperation, aRessyaProperty);
						vector<int> iLevel;
						iLevel.push_back(iLevelAdd);
						//Ver2.06.05 運用番号順反転の場合は、m_contNumberChangeに入れる必要は無い。
						if (!pAfterOperation->getOperationNumberReverse())
						{
#pragma omp critical(NumberChange)
							m_contNumberChange.push_back(aRessyaElement);
						}
						OperationElement aOperationElement(
							pAfterOperation, iLevel, iValidSihatsuEkiOrder);

						contOperationElement.push_back(aOperationElement);

						iLevelAdd++;
					}

				}
			}

			/**
				中間駅
				増結・解結・運用番号変更を抜き出しcontOperationElementに収める
				増結・解結編成の前後作業も参照して、作業を抜き出す
			*/
			for (int iEkiOrder = iValidSihatsuEkiOrder + 1; iEkiOrder < iValidSyuuchakuEkiOrder; iEkiOrder++)
			{
				CentDedEkiJikoku* pEkiJikoku =
					pCentDedRessya->getCentDedEkiJikokuCont()->getMuPtr()->get(iEkiOrder);
				CentDedBeforeOperationCont* pBeforeCont =
					pEkiJikoku->getCentDedBeforeOperationCont();
				CentDedAfterOperationCont* pAfterCont =
					pEkiJikoku->getCentDedAfterOperationCont();

				for (int idxb = 0; idxb < (int)pBeforeCont->size(); idxb++)
				{
					CentDedBeforeOperation* pBeforeOperation = pBeforeCont->getMuPtr()->get(idxb);
					if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
					{
						pBeforeOperation->clearOperationNumber();

						int iConnectTrackIndex = pEkiJikoku->getRessyaTrackIndex();
						for (int idxb2 = pBeforeCont->size() - 1; idxb2 > idxb; idxb2--)
						{
							CentDedBeforeOperation* pBeforeOperation2 = pBeforeCont->getMuPtr()->get(idxb2);
							if (pBeforeOperation2->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
							{
								iConnectTrackIndex = pBeforeOperation2->getShuntTrackIndex();
							}
						}
						vector<int> iLevel;
						iLevel.push_back(iLevelAdd);
						OperationElement aOperationElement(
							pBeforeOperation, iLevel, iEkiOrder);
						vector<OperationElement> contTemp = searchBeforeOperationElement(
							pBeforeOperation->getCentDedBeforeOperationCont(),
							pBeforeOperation->getConnectJikoku(),
							aRessyaProperty,
							iLevel,
							iEkiOrder,
							iEkiOrderTable[iEkiOrder][iRessyahoukou],
							iConnectTrackIndex);

						contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());
						contOperationElement.push_back(aOperationElement);

						iLevelAdd++;
					}
					else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
					{
						pBeforeOperation->clearOperationNumber();

						int iReleaseTrackIndex = pEkiJikoku->getRessyaTrackIndex();
						for (int idxb2 = pBeforeCont->size() - 1; idxb2 > idxb; idxb2--)
						{
							CentDedBeforeOperation* pBeforeOperation2 = pBeforeCont->getMuPtr()->get(idxb2);
							if (pBeforeOperation2->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
							{
								iReleaseTrackIndex = pBeforeOperation2->getShuntTrackIndex();
							}
						}
						vector<int> iLevel;
						iLevel.push_back(iLevelAdd);
						OperationElement aOperationElement(
							pBeforeOperation, iLevel, iEkiOrder);
						vector<OperationElement> contTemp = searchAfterOperationElement(
							pBeforeOperation->getCentDedAfterOperationCont(),
							pBeforeOperation->getReleaseJikoku(),
							aRessyaProperty,
							iLevel,
							iEkiOrder,
							iEkiOrderTable[iEkiOrder][iRessyahoukou],
							iReleaseTrackIndex);

						contOperationElement.push_back(aOperationElement);
						contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());

						iLevelAdd++;
					}
					else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_NumberChange)
					{
						pBeforeOperation->clearOperationNumber();
						//暫定措置、当駅着時刻を入れておく
						aRessyaProperty.setJikoku(pEkiJikoku->getChakujikoku());
						RessyaElement aRessyaElement(pBeforeOperation, aRessyaProperty);
						vector<int> iLevel;
						iLevel.push_back(iLevelAdd);
						//Ver2.06.05 運用番号順反転の場合は、m_contNumberChangeに入れる必要は無い。
						if (!pBeforeOperation->getOperationNumberReverse())
						{
#pragma omp critical(NumberChange)
							m_contNumberChange.push_back(aRessyaElement);
						}
						OperationElement aOperationElement(
							pBeforeOperation, iLevel, iEkiOrder);

						contOperationElement.push_back(aOperationElement);

						iLevelAdd++;
					}

				}

				for (int idxa = 0; idxa < (int)pAfterCont->size(); idxa++)
				{
					CentDedAfterOperation* pAfterOperation = pAfterCont->getMuPtr()->get(idxa);
					if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
					{
						pAfterOperation->clearOperationNumber();

						int iConnectTrackIndex = pEkiJikoku->getRessyaTrackIndex();
						for (int idxa2 = 0; idxa2 < idxa; idxa2++)
						{
							CentDedAfterOperation* pAfterOperation2 = pAfterCont->getMuPtr()->get(idxa2);
							if (pAfterOperation2->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
							{
								iConnectTrackIndex = pAfterOperation2->getShuntTrackIndex();
							}
						}
						vector<int> iLevel;
						iLevel.push_back(iLevelAdd);
						OperationElement aOperationElement(
							pAfterOperation, iLevel, iEkiOrder);
						vector<OperationElement> contTemp = searchBeforeOperationElement(
							pAfterOperation->getCentDedBeforeOperationCont(),
							pAfterOperation->getConnectJikoku(),
							aRessyaProperty,
							iLevel,
							iEkiOrder,
							iEkiOrderTable[iEkiOrder][iRessyahoukou],
							iConnectTrackIndex);

						contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());
						contOperationElement.push_back(aOperationElement);

						iLevelAdd++;
					}
					else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
					{
						pAfterOperation->clearOperationNumber();

						int iReleaseTrackIndex = pEkiJikoku->getRessyaTrackIndex();
						for (int idxa2 = 0; idxa2 < idxa; idxa2++)
						{
							CentDedAfterOperation* pAfterOperation2 = pAfterCont->getMuPtr()->get(idxa2);
							if (pAfterOperation2->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
							{
								iReleaseTrackIndex = pAfterOperation2->getShuntTrackIndex();
							}
						}
						vector<int> iLevel;
						iLevel.push_back(iLevelAdd);
						OperationElement aOperationElement(
							pAfterOperation, iLevel, iEkiOrder);
						vector<OperationElement> contTemp = searchAfterOperationElement(
							pAfterOperation->getCentDedAfterOperationCont(),
							pAfterOperation->getReleaseJikoku(),
							aRessyaProperty,
							iLevel,
							iEkiOrder,
							iEkiOrderTable[iEkiOrder][iRessyahoukou],
							iReleaseTrackIndex);

						contOperationElement.push_back(aOperationElement);
						contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());

						iLevelAdd++;
					}
					else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_NumberChange)
					{
						pAfterOperation->clearOperationNumber();

						//暫定措置、当駅発時刻を入れておく
						aRessyaProperty.setJikoku(pEkiJikoku->getHatsujikoku());
						RessyaElement aRessyaElement(pAfterOperation, aRessyaProperty);
						vector<int> iLevel;
						iLevel.push_back(iLevelAdd);
						//Ver2.06.05 運用番号順反転の場合は、m_contNumberChangeに入れる必要は無い。
						if (!pAfterOperation->getOperationNumberReverse())
						{
#pragma omp critical(NumberChange)
							m_contNumberChange.push_back(aRessyaElement);
						}
						OperationElement aOperationElement(
							pAfterOperation, iLevel, iEkiOrder);

						contOperationElement.push_back(aOperationElement);

						iLevelAdd++;
					}

				}
			}

			/**
				終着駅
				・次列車始発の場合は、後作業を見て、番線と時刻を取得して、contRessyaExistに入れる

			*/
			{
				CentDedEkiJikoku* pEkiJikokuSyuuchaku =
					pCentDedRessya->getCentDedEkiJikokuCont()->getMuPtr()->get(iValidSyuuchakuEkiOrder);
				CentDedBeforeOperationCont* pBeforeCont =
					pEkiJikokuSyuuchaku->getCentDedBeforeOperationCont();
				CentDedAfterOperationCont* pAfterCont =
					pEkiJikokuSyuuchaku->getCentDedAfterOperationCont();

				CentDedAfterOperation* pLastOperation = pAfterCont->getMuPtr()->get(INT_MAX);
				/**
					bTsuukaOuterJikokuNull
					終着駅の駅扱いが通過で、路線外終着かつ当駅発時刻がNULLの場合は、
					路線外終着作業以外は無効になります。
					したがって、下記の前作業・後作業検索はスキップします。
				*/
				bool bTsuukaOuterJikokuNull =
					pEkiJikokuSyuuchaku->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka &&
					pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer &&
					pLastOperation->getHatsuJikoku().isNull();

				for (int idxb = 0; idxb < (int)pBeforeCont->size() && !bTsuukaOuterJikokuNull; idxb++)
				{
					CentDedBeforeOperation* pBeforeOperation = pBeforeCont->getMuPtr()->get(idxb);
					if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
					{
						pBeforeOperation->clearOperationNumber();

						int iConnectTrackIndex = pEkiJikokuSyuuchaku->getRessyaTrackIndex();
						for (int idxb2 = pBeforeCont->size() - 1; idxb2 > idxb; idxb2--)
						{
							CentDedBeforeOperation* pBeforeOperation2 = pBeforeCont->getMuPtr()->get(idxb2);
							if (pBeforeOperation2->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
							{
								iConnectTrackIndex = pBeforeOperation2->getShuntTrackIndex();
							}
						}
						vector<int> iLevel;
						iLevel.push_back(iLevelAdd);
						OperationElement aOperationElement(
							pBeforeOperation, iLevel, iValidSyuuchakuEkiOrder);
						vector<OperationElement> contTemp = searchBeforeOperationElement(
							pBeforeOperation->getCentDedBeforeOperationCont(),
							pBeforeOperation->getConnectJikoku(),
							aRessyaProperty,
							iLevel,
							iValidSyuuchakuEkiOrder,
							iEkiOrderTable[iValidSyuuchakuEkiOrder][iRessyahoukou],
							iConnectTrackIndex);

						contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());
						contOperationElement.push_back(aOperationElement);

						iLevelAdd++;
					}
					else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
					{
						pBeforeOperation->clearOperationNumber();

						int iReleaseTrackIndex = pEkiJikokuSyuuchaku->getRessyaTrackIndex();
						for (int idxb2 = pBeforeCont->size() - 1; idxb2 > idxb; idxb2--)
						{
							CentDedBeforeOperation* pBeforeOperation2 = pBeforeCont->getMuPtr()->get(idxb2);
							if (pBeforeOperation2->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
							{
								iReleaseTrackIndex = pBeforeOperation2->getShuntTrackIndex();
							}
						}
						vector<int> iLevel;
						iLevel.push_back(iLevelAdd);
						OperationElement aOperationElement(
							pBeforeOperation, iLevel, iValidSyuuchakuEkiOrder);
						vector<OperationElement> contTemp = searchAfterOperationElement(
							pBeforeOperation->getCentDedAfterOperationCont(),
							pBeforeOperation->getReleaseJikoku(),
							aRessyaProperty,
							iLevel,
							iValidSyuuchakuEkiOrder,
							iEkiOrderTable[iValidSyuuchakuEkiOrder][iRessyahoukou],
							iReleaseTrackIndex);

						contOperationElement.push_back(aOperationElement);
						contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());

						iLevelAdd++;
					}
					else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_NumberChange)
					{
						pBeforeOperation->clearOperationNumber();

						//暫定措置、当駅着時刻を入れておく
						aRessyaProperty.setJikoku(pEkiJikokuSyuuchaku->getChakujikoku());
						RessyaElement aRessyaElement(pBeforeOperation, aRessyaProperty);
						vector<int> iLevel;
						iLevel.push_back(iLevelAdd);
						//Ver2.06.05 運用番号順反転の場合は、m_contNumberChangeに入れる必要は無い。
						if (!pBeforeOperation->getOperationNumberReverse())
						{
#pragma omp critical(NumberChange)
							m_contNumberChange.push_back(aRessyaElement);
						}
						OperationElement aOperationElement(
							pBeforeOperation, iLevel, iValidSyuuchakuEkiOrder);
						contOperationElement.push_back(aOperationElement);

						iLevelAdd++;
					}

				}

				for (int idxa = 0; idxa < (int)pAfterCont->size() - 1 && !bTsuukaOuterJikokuNull; idxa++)
				{
					CentDedAfterOperation* pAfterOperation = pAfterCont->getMuPtr()->get(idxa);
					if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
					{
						pAfterOperation->clearOperationNumber();

						int iConnectTrackIndex = pEkiJikokuSyuuchaku->getRessyaTrackIndex();
						for (int idxa2 = 0; idxa2 < idxa; idxa2++)
						{
							CentDedAfterOperation* pAfterOperation2 = pAfterCont->getMuPtr()->get(idxa2);
							if (pAfterOperation2->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
							{
								iConnectTrackIndex = pAfterOperation2->getShuntTrackIndex();
							}
						}
						vector<int> iLevel;
						iLevel.push_back(iLevelAdd);
						OperationElement aOperationElement(
							pAfterOperation, iLevel, iValidSyuuchakuEkiOrder);
						vector<OperationElement> contTemp = searchBeforeOperationElement(
							pAfterOperation->getCentDedBeforeOperationCont(),
							pAfterOperation->getConnectJikoku(),
							aRessyaProperty,
							iLevel,
							iValidSyuuchakuEkiOrder,
							iEkiOrderTable[iValidSyuuchakuEkiOrder][iRessyahoukou],
							iConnectTrackIndex);

						contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());
						contOperationElement.push_back(aOperationElement);

						iLevelAdd++;
					}
					else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
					{
						pAfterOperation->clearOperationNumber();

						int iReleaseTrackIndex = pEkiJikokuSyuuchaku->getRessyaTrackIndex();
						for (int idxa2 = 0; idxa2 < idxa; idxa2++)
						{
							CentDedAfterOperation* pAfterOperation2 = pAfterCont->getMuPtr()->get(idxa2);
							if (pAfterOperation2->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
							{
								iReleaseTrackIndex = pAfterOperation2->getShuntTrackIndex();
							}
						}
						vector<int> iLevel;
						iLevel.push_back(iLevelAdd);
						OperationElement aOperationElement(
							pAfterOperation, iLevel, iValidSyuuchakuEkiOrder);
						vector<OperationElement> contTemp = searchAfterOperationElement(
							pAfterOperation->getCentDedAfterOperationCont(),
							pAfterOperation->getReleaseJikoku(),
							aRessyaProperty,
							iLevel,
							iValidSyuuchakuEkiOrder,
							iEkiOrderTable[iValidSyuuchakuEkiOrder][iRessyahoukou],
							iReleaseTrackIndex);

						contOperationElement.push_back(aOperationElement);
						contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());

						iLevelAdd++;
					}
					else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_NumberChange)
					{
						pAfterOperation->clearOperationNumber();

						//暫定措置、当駅着時刻を入れておく
						aRessyaProperty.setJikoku(pEkiJikokuSyuuchaku->getChakujikoku());
						RessyaElement aRessyaElement(pAfterOperation, aRessyaProperty);
						vector<int> iLevel;
						iLevel.push_back(iLevelAdd);
						//Ver2.06.05 運用番号順反転の場合は、m_contNumberChangeに入れる必要は無い。
						if (!pAfterOperation->getOperationNumberReverse())
						{
#pragma omp critical(NumberChange)
							m_contNumberChange.push_back(aRessyaElement);
						}
						OperationElement aOperationElement(
							pAfterOperation, iLevel, iValidSyuuchakuEkiOrder);

						contOperationElement.push_back(aOperationElement);

						iLevelAdd++;
					}

				}

				if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_In ||
					pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
				{
					pLastOperation->clearOperationNumber();
					vector<int> iLevel;
					iLevel.push_back(iLevelAdd);
					contOperationElement.push_back(OperationElement(
						pLastOperation, iLevel, iValidSyuuchakuEkiOrder));
					if (!pLastOperation->getInOutLinkCode().empty())
					{
						if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_In)
						{
							aRessyaProperty.setJikoku(pLastOperation->getInJikoku());
						}
						else
						{
							aRessyaProperty.setJikoku(pLastOperation->getOuterShuchakuJikoku());
						}
						RessyaElement aRessyaElement(pLastOperation, aRessyaProperty);
#pragma omp critical(InOutLink)
						insertInOutLinkCodeElement(
							pLastOperation->getInOutLinkCode(),
							aRessyaElement);
					}
				}
				else if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Junction)
				{
					/**
						後列車接続の場合、最後にどの番線にいるのかと、終点となる時刻を調べる
						番線は、発着番線を初期値とし、AfterContを降順に見て、入換番線を取得します。
						ただし、同じホームへの入換がある場合は、最も前の物のみが有効となる

						終点時刻は、pLastOperationに終点時刻が設定されている場合はそれを用います。
						NULLの場合は、AfterContを降順に全て見て、時刻が見つかればそれを用います。
						このとき、入換作業が有効かどうかのチェックが必要です。
						AfterContを見てもNULLの場合は、BeforeContを昇順にみて、時刻が見つかればそこで終了です。
						このとき、入換作業が有効かどうかのチェックが必要です。
						それでもNULLの場合は、当駅着時刻を用います。
					*/
					pLastOperation->clearOperationNumber();

					int iRessyaTrackIndex = pEkiJikokuSyuuchaku->getRessyaTrackIndex();
					
					CdDedJikoku aTerminalJikoku;/* = pOperationNone->getTerminalJikoku();*/
					CdDedJikoku aJunctionJikoku;
					int iPrevRessyahoukou = 0;

					for (int idxa = 0; idxa < pAfterCont->size() - 1; idxa++)
					{
						CentDedAfterOperation* pAfterOperation = pAfterCont->getMuPtr()->get(idxa);
						if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
						{
							/**
								同じ番線への入換は、最も前の物のみが有効
							*/
							if (iRessyaTrackIndex == pAfterOperation->getShuntTrackIndex())
							{
								continue;
							}
							aTerminalJikoku = pAfterOperation->getOperationChakuJikoku(true);
							aJunctionJikoku = pAfterOperation->getOperationChakuJikoku(true);
							if ((iRessyaTrackIndex > pAfterOperation->getShuntTrackIndex() &&
								pCentDedRessya->getRessyahoukou() == Ressyahoukou_Kudari) ||
								(iRessyaTrackIndex < pAfterOperation->getShuntTrackIndex() &&
									pCentDedRessya->getRessyahoukou() == Ressyahoukou_Nobori))
							{
								iPrevRessyahoukou = 2;
							}
							else
							{
								iPrevRessyahoukou = -2;
							}
							iRessyaTrackIndex = pAfterOperation->getShuntTrackIndex();
						}
						else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
						{
							aTerminalJikoku = pAfterOperation->getConnectJikoku();
						}
						else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
						{
							aTerminalJikoku = pAfterOperation->getReleaseJikoku();
						}
					}
					if (!pLastOperation->getTerminalJikoku().isNull())
					{
						aTerminalJikoku = pLastOperation->getTerminalJikoku();
					}

					int iRessyaTrackIndexTemp = pEkiJikokuSyuuchaku->getRessyaTrackIndex();
					for (int idxb = pBeforeCont->size() - 1; idxb >= 0; idxb--)
					{
						CentDedBeforeOperation* pBeforeOperation = pBeforeCont->getMuPtr()->get(idxb);
						if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
						{
							/**
								同じ番線への入換は、最も後の物のみが有効
							*/
							if (iRessyaTrackIndexTemp == pBeforeOperation->getShuntTrackIndex())
							{
								continue;
							}
							if (aTerminalJikoku.isNull())
							{
								aTerminalJikoku = pBeforeOperation->getOperationChakuJikoku(true);
							}
							if (aJunctionJikoku.isNull())
							{
								aJunctionJikoku = pBeforeOperation->getOperationChakuJikoku(true);
								if ((pEkiJikokuSyuuchaku->getRessyaTrackIndex() > pBeforeOperation->getShuntTrackIndex() &&
									pCentDedRessya->getRessyahoukou() == Ressyahoukou_Kudari) ||
									(pEkiJikokuSyuuchaku->getRessyaTrackIndex() < pBeforeOperation->getShuntTrackIndex() &&
										pCentDedRessya->getRessyahoukou() == Ressyahoukou_Nobori))
								{
									iPrevRessyahoukou = -2;
								}
								else
								{
									iPrevRessyahoukou = 2;
								}
							}
						}
						else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
						{
							if (aTerminalJikoku.isNull())
							{
								aTerminalJikoku = pBeforeOperation->getConnectJikoku();
							}
							//break;
						}
						else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
						{
							if (aTerminalJikoku.isNull())
							{
								aTerminalJikoku = pBeforeOperation->getReleaseJikoku();
							}
							//break;
						}
					}
					if (aTerminalJikoku.isNull())
					{
						aTerminalJikoku = pEkiJikokuSyuuchaku->getChakujikoku();
					}
					if (aJunctionJikoku.isNull())
					{
						aJunctionJikoku = pEkiJikokuSyuuchaku->getChakujikoku();
						iPrevRessyahoukou = -1;
					}

					pLastOperation->setPrevRessyahoukou(iPrevRessyahoukou);
					pLastOperation->setJunctionJikoku(aJunctionJikoku);


					vector<int> iLevel;
					iLevel.push_back(iLevelAdd);

					int iEkiIndexofContExist = iEkiOrderTable[iValidSyuuchakuEkiOrder][iRessyahoukou];

					contOperationElement.push_back(
						OperationElement(pLastOperation,
							iLevel,
							iValidSyuuchakuEkiOrder,
							iEkiIndexofContExist,
							iRessyaTrackIndex));

					aRessyaProperty.setJikoku(aTerminalJikoku);
					RessyaElement aRessyaElement(pLastOperation, aRessyaProperty);

#pragma omp critical(RessyaExist)
					InsertRessyaElement(
						iEkiIndexofContExist,
						iRessyaTrackIndex,
						aRessyaElement);
				}
			}

#pragma omp critical(RessyaOperationElement)
			m_contRessyaOperationElement[iRessyahoukou][idxRessya] = contOperationElement;
		}
	}

	/**
		Step2
		m_contOutOuterを見て、出区・路線外始発から運用を探索していく、
		始発側の情報を入れたOperationTableContentを作り、Bufferに収めて、次の作業へ進む。

		ただし、出区・路線外始発作業に入出区連携コードが入力されている場合は、
		contInOutLinkCodeContentからInOutLinkCodeElementを取得し、
		iStatusが"2"の場合は、入出区連携が有効なので、スキップします。
	*/
	int iSizeO = m_contOutOuter.size();
#pragma omp parallel for schedule(guided)
	for (int idxOut = 0; idxOut < iSizeO; idxOut++)
	{

		RessyaElement aOutOuterOperation = m_contOutOuter[idxOut];

		if (!aOutOuterOperation.BeforeOperation->getInOutLinkCode().empty())
		{
			const map<tstring, InOutLinkCodeContent>* contInOutLinkCodeContent =
				&m_pDedDia->getcontInOutLinkCodeContent();
			auto aInOutLinkCodeItr = contInOutLinkCodeContent->find(aOutOuterOperation.BeforeOperation->getInOutLinkCode());
			if (aInOutLinkCodeItr != contInOutLinkCodeContent->end() &&
				aInOutLinkCodeItr->second.iStatus == 2)
			{
				continue;
			}
		}
		CdDedRessyaProperty aRessyaPropertyCurr = aOutOuterOperation.sRessyaProperty;
		vector<OperationElement>& contOperationElementCurr = m_contRessyaOperationElement
			[(int)aRessyaPropertyCurr.getRessyahoukou()][aRessyaPropertyCurr.getRessyaIndex()];
		int iOperationIndex = 0;
		for (; iOperationIndex < (int)contOperationElementCurr.size(); iOperationIndex++)
		{
			if (contOperationElementCurr[iOperationIndex].BeforeOperation == aOutOuterOperation.BeforeOperation)
			{
				break;
			}
		}

		vector<tstring> strOperationNumber;

		CentDedBeforeOperation* pBeforeOperation = contOperationElementCurr[iOperationIndex].BeforeOperation;
		if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Out)
		{
			strOperationNumber = pBeforeOperation->getOperationNumberOriginal();
			if (strOperationNumber.empty())
			{
				//tstring strTemp = _T("Tmp");
				//strTemp += to_tstring(aRessyaPropertyCurr.getRessyaIndex());
				//strOperationNumber.push_back(strTemp);
				strOperationNumber.push_back(tstring());
			}
			else
			{
#pragma omp critical(OperationTableContentBuffer)
				insertOperationTableContentToBuffer(
					aRessyaPropertyCurr,
					strOperationNumber,
					contOperationElementCurr[iOperationIndex].iEkiOrder,
					pBeforeOperation,
					NULL,
					EBeforeAfterType::BeforeAfterType_OutIn);
			}
		}
		else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
		{
			strOperationNumber = pBeforeOperation->getOperationNumberOriginal();
			if (strOperationNumber.empty())
			{
				//tstring strTemp = _T("Tmp");
				//strTemp += to_tstring(aRessyaPropertyCurr.getRessyaIndex());
				//strOperationNumber.push_back(strTemp);
				strOperationNumber.push_back(tstring());
			}
			else
			{
				/**
					この作業が増結編成の場合は、列車の左側に路線外始発相当+↳の表示を追加します。
					まず、この作業が主編成に増結している(増結の繰り返しは可)かどうかの確認を行います。
					☆1 路線外始発増結列車の挿入
				*/
				bool bConnectValid = false;
				if (contOperationElementCurr[iOperationIndex].iLevel.size() > 1)
				{
					/**
						次作業が主編成に増結している(増結の繰り返しは可)かどうかの確認を行います。
					*/
					vector<int> iLevelParent = contOperationElementCurr[iOperationIndex].iLevel;
					bConnectValid = true;
					while (iLevelParent.size() > 1)
					{
						iLevelParent.pop_back();
						for (int iOperationIndexParent = 0;
							iOperationIndexParent < (int)contOperationElementCurr.size(); iOperationIndexParent++)
						{
							if (contOperationElementCurr[iOperationIndexParent].iLevel != iLevelParent)
							{
								continue;
							}
							/**
								親作業が、解結(BeforeReleaseかAfterRelease)だった場合は、
								bConnectValidをfalseにして終了。
							*/
							if ((contOperationElementCurr[iOperationIndexParent].BeforeOperation != NULL &&
								contOperationElementCurr[iOperationIndexParent].BeforeOperation->getBOperation()
								== CentDedBeforeOperation::EBOperation::BOperation_Release) ||
								(contOperationElementCurr[iOperationIndexParent].AfterOperation != NULL &&
									contOperationElementCurr[iOperationIndexParent].AfterOperation->getAOperation()
									== CentDedAfterOperation::EAOperation::AOperation_Release))
							{
								bConnectValid = false;
								break;
							}
						}
					}
				}
				if (bConnectValid)
				{
#pragma omp critical(contOuterConnectInsertList)
					{
						const CentDedRessya* pCentDedRessya =
							m_pDedDia->getCentDedRessyaCont(aRessyaPropertyCurr.getRessyahoukou())->getMuPtr()
							->get(aRessyaPropertyCurr.getRessyaIndex());
						const CentDedEkiJikoku aCentDedEkiJikoku =
							pCentDedRessya->getCentDedEkiJikoku(contOperationElementCurr[iOperationIndex].iEkiOrder);
						CustomizeJikokuhyouContent aCustomizeJikokuhyouContent(pCentDedRessya,true);
						aCustomizeJikokuhyouContent.iConnectEkiOrder = contOperationElementCurr[iOperationIndex].iEkiOrder;
						aCustomizeJikokuhyouContent.ChakuJikoku = pBeforeOperation->getChakuJikoku();
						if (aCustomizeJikokuhyouContent.ChakuJikoku.isNull())
						{
							aCustomizeJikokuhyouContent.ChakuJikoku = aCentDedEkiJikoku.getHatsujikoku();
						}
						aCustomizeJikokuhyouContent.OuterShihatsuJikoku = pBeforeOperation->getOuterShihatsuJikoku();
						aCustomizeJikokuhyouContent.iSihatsuEkiOrder = contOperationElementCurr[iOperationIndex].iEkiOrder;
						aCustomizeJikokuhyouContent.iOuterShihatsuEkiIndex = pBeforeOperation->getOuterShihatsuekiIndex();;
						aCustomizeJikokuhyouContent.ePrevEkiatsukai = aCentDedEkiJikoku.getEkiatsukai();
						aCustomizeJikokuhyouContent.iPrevRessyaTrackIndex = aCentDedEkiJikoku.getRessyaTrackIndex();
						aCustomizeJikokuhyouContent.strPrevOperationNumber = strOperationNumber;
						aCustomizeJikokuhyouContent.eEBeforeType = EBeforeAfterType::BeforeAfterType_Outer;

						m_contOuterConnectInsertList[aRessyaPropertyCurr.getRessyahoukou()][contOperationElementCurr[iOperationIndex].iEkiOrder].
							insert(make_pair(aRessyaPropertyCurr.getRessyaIndex(), aCustomizeJikokuhyouContent));
					}
					//実処理はcompleteCustomizeJikokuhyouContentで行うのでコメントアウト
//#pragma omp critical(CustomizeRessyaIndex)
//					{
//						vector<CustomizeJikokuhyouContent>& contCustomizeJikokuhyouContent =
//							m_pDedDia->getcontCustomizeRessyaIndex(aRessyaPropertyCurr.getRessyahoukou());
//						for (int CustomizeJikokuhyouContentIndex = 0; CustomizeJikokuhyouContentIndex < (int)contCustomizeJikokuhyouContent.size(); CustomizeJikokuhyouContentIndex++)
//						{
//							if (contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].iRessyaIndexCont.empty())
//							{
//								continue;
//							}
//							if (contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].iRessyaIndexCont.front() == aRessyaPropertyCurr.getRessyaIndex())
//							{
//								const CentDedRessya* pCentDedRessya =
//									m_pDedDia->getCentDedRessyaCont(aRessyaPropertyCurr.getRessyahoukou())->getMuPtr()
//									->get(aRessyaPropertyCurr.getRessyaIndex());
//								const CentDedEkiJikoku aCentDedEkiJikoku =
//									pCentDedRessya->getCentDedEkiJikoku(contOperationElementCurr[iOperationIndex].iEkiOrder);
//								CustomizeJikokuhyouContent aCustomizeJikokuhyouContent(pCentDedRessya);
//								aCustomizeJikokuhyouContent.iConnectEkiOrder = contOperationElementCurr[iOperationIndex].iEkiOrder;
//								aCustomizeJikokuhyouContent.ChakuJikoku = pBeforeOperation->getChakuJikoku();
//								if (aCustomizeJikokuhyouContent.ChakuJikoku.isNull())
//								{
//									aCustomizeJikokuhyouContent.ChakuJikoku = aCentDedEkiJikoku.getHatsujikoku();
//								}
//								aCustomizeJikokuhyouContent.OuterShihatsuJikoku = pBeforeOperation->getOuterShihatsuJikoku();
//								aCustomizeJikokuhyouContent.iSihatsuEkiOrder = contOperationElementCurr[iOperationIndex].iEkiOrder;
//								aCustomizeJikokuhyouContent.iOuterShihatsuEkiIndex = pBeforeOperation->getOuterShihatsuekiIndex();;
//								aCustomizeJikokuhyouContent.eEkiatsukai = aCentDedEkiJikoku.getEkiatsukai();
//								aCustomizeJikokuhyouContent.iRessyaTrackIndex = aCentDedEkiJikoku.getRessyaTrackIndex();
//								aCustomizeJikokuhyouContent.strOperationNumber = strOperationNumber;
//
//								contCustomizeJikokuhyouContent.insert(contCustomizeJikokuhyouContent.begin() + CustomizeJikokuhyouContentIndex,
//									aCustomizeJikokuhyouContent);
//								break;
//							}
//						}
//					}
				}

#pragma omp critical(OperationTableContentBuffer)
				insertOperationTableContentToBuffer(
					aRessyaPropertyCurr,
					strOperationNumber,
					contOperationElementCurr[iOperationIndex].iEkiOrder,
					pBeforeOperation,
					NULL,
					EBeforeAfterType::BeforeAfterType_Outer);
			}
		}

		vector<int> iLevelNext = contOperationElementCurr[iOperationIndex].iLevel;
		iLevelNext.back()++;

		junctionOperationElement(
			aRessyaPropertyCurr,
			contOperationElementCurr,
			iLevelNext,
			strOperationNumber);

		//if (contOperationElementCurr[iOperationIndex].iLevel.size() == 1)
		//{
		//	CustomizeJikokuhyouContent aCustomizeJikokuhyouContent(aRessyaPropertyCurr.getRessyaIndex());

		//	junctionOperationElement(
		//		aRessyaPropertyCurr,
		//		contOperationElementCurr,
		//		iLevelNext,
		//		strOperationNumber,
		//		&aCustomizeJikokuhyouContent);
		//}
		//else
		//{
		//	junctionOperationElement(
		//		aRessyaPropertyCurr,
		//		contOperationElementCurr,
		//		iLevelNext,
		//		strOperationNumber,
		//		NULL);
		//}
	}

	/**
		Step3
		出区・路線外始発の次は、運用番号変更から接続を始めます。
	*/
	int iSizeNC = m_contNumberChange.size();
#pragma omp parallel for schedule(guided)
	for (int idxNumberChange = 0; idxNumberChange < iSizeNC; idxNumberChange++)
	{

		RessyaElement aNumberChangeOperation = m_contNumberChange[idxNumberChange];

		CdDedRessyaProperty aRessyaPropertyCurr = aNumberChangeOperation.sRessyaProperty;
		vector<OperationElement>& contOperationElementCurr = m_contRessyaOperationElement
			[(int)aRessyaPropertyCurr.getRessyahoukou()][aRessyaPropertyCurr.getRessyaIndex()];
		if (aNumberChangeOperation.BeforeOperation != NULL)
		{
			int iOperationIndex = 0;
			for (; iOperationIndex < (int)contOperationElementCurr.size(); iOperationIndex++)
			{
				if (contOperationElementCurr[iOperationIndex].BeforeOperation == aNumberChangeOperation.BeforeOperation)
				{
					break;
				}
			}

			CentDedBeforeOperation* pBeforeOperation = contOperationElementCurr[iOperationIndex].BeforeOperation;
			if (pBeforeOperation->getBOperation() != CentDedBeforeOperation::EBOperation::BOperation_NumberChange)
			{
				continue;
			}
			vector<tstring> strOperationNumber = pBeforeOperation->getOperationNumber();
			if (strOperationNumber.empty())
			{
				//tstring strTemp = _T("Tmp");
				//strTemp += to_tstring(aRessyaPropertyCurr.getRessyaIndex());
				//strOperationNumber.push_back(strTemp);
				strOperationNumber.push_back(tstring());
			}
			else
			{
#pragma omp critical(OperationTableContentBuffer)
				insertOperationTableContentToBuffer(
					aRessyaPropertyCurr,
					strOperationNumber,
					contOperationElementCurr[iOperationIndex].iEkiOrder,
					NULL,
					NULL,
					EBeforeAfterType::BeforeAfterType_OperationNumberChange);
			}

			vector<int> iLevelNext = contOperationElementCurr[iOperationIndex].iLevel;
			iLevelNext.back()++;
			junctionOperationElement(
				aRessyaPropertyCurr,
				contOperationElementCurr,
				iLevelNext,
				strOperationNumber);
		}
		else if (aNumberChangeOperation.AfterOperation != NULL)
		{
			int iOperationIndex = 0;
			for (; iOperationIndex < (int)contOperationElementCurr.size(); iOperationIndex++)
			{
				if (contOperationElementCurr[iOperationIndex].AfterOperation == aNumberChangeOperation.AfterOperation)
				{
					break;
				}
			}

			CentDedAfterOperation* AfterOperation = contOperationElementCurr[iOperationIndex].AfterOperation;
			if (AfterOperation->getAOperation() != CentDedAfterOperation::EAOperation::AOperation_NumberChange)
			{
				continue;
			}
			vector<tstring> strOperationNumber = AfterOperation->getOperationNumber();
			if (strOperationNumber.empty())
			{
				//tstring strTemp = _T("Tmp");
				//strTemp += to_tstring(aRessyaPropertyCurr.getRessyaIndex());
				//strOperationNumber.push_back(strTemp);
				strOperationNumber.push_back(tstring());
			}
			else
			{
#pragma omp critical(OperationTableContentBuffer)
				insertOperationTableContentToBuffer(
					aRessyaPropertyCurr,
					strOperationNumber,
					contOperationElementCurr[iOperationIndex].iEkiOrder,
					NULL,
					NULL,
					EBeforeAfterType::BeforeAfterType_OperationNumberChange);
			}

			vector<int> iLevelNext = contOperationElementCurr[iOperationIndex].iLevel;
			iLevelNext.back()++;
			junctionOperationElement(
				aRessyaPropertyCurr,
				contOperationElementCurr,
				iLevelNext,
				strOperationNumber);
		}
	}

	/**
		出区・路線外始発の次は、"前列車が無い"前列車接続から接続を始めます。
		SearchRessyaElementRevを使い、前列車がないことを確かめます。
		仮運用番号がある場合はそれを用い、ない場合は空白運番を割り当てる
	*/
	int iSizeJ = m_contJunctionList.size();
#pragma omp parallel for schedule(guided)
	for (int idxJunction = 0; idxJunction < iSizeJ; idxJunction++)
	{
		RessyaElement aBeforeJunctionOperation = m_contJunctionList[idxJunction];

		CdDedRessyaProperty aRessyaPropertyCurr = aBeforeJunctionOperation.sRessyaProperty;
		vector<OperationElement>& contOperationElementCurr = m_contRessyaOperationElement
			[(int)aRessyaPropertyCurr.getRessyahoukou()][aRessyaPropertyCurr.getRessyaIndex()];
		int iOperationIndex = 0;
		for (; iOperationIndex < (int)contOperationElementCurr.size(); iOperationIndex++)
		{
			if (contOperationElementCurr[iOperationIndex].BeforeOperation == aBeforeJunctionOperation.BeforeOperation)
			{
				break;
			}
		}

		if (SearchRessyaElementRev(
			&m_contRessyaExist[contOperationElementCurr[iOperationIndex].iEkiIndexofContExist][contOperationElementCurr[iOperationIndex].iRessyaTrackIndex],
			contOperationElementCurr[iOperationIndex].BeforeOperation))
		{
			continue;
		}
		vector<tstring> strOperationNumber;
		CentDedBeforeOperation* pBeforeOperation = contOperationElementCurr[iOperationIndex].BeforeOperation;
		if (pBeforeOperation->getBOperation() != CentDedBeforeOperation::EBOperation::BOperation_Junction)
		{
			continue;
		}
		strOperationNumber = pBeforeOperation->getOperationNumberTemp();
		if (strOperationNumber.empty())
		{
			//tstring strTemp = _T("TmpN");
			//strTemp += to_tstring(aRessyaPropertyCurr.getRessyaIndex());
			//strOperationNumber.push_back(strTemp);
			strOperationNumber.push_back(tstring());
#pragma omp critical(Operation)
			pBeforeOperation->setOperationNumber(strOperationNumber);
		}
		else
		{
#pragma omp critical(Operation)
			pBeforeOperation->setOperationNumber(strOperationNumber);

#pragma omp critical(OperationTableContentBuffer)
			insertOperationTableContentToBuffer(
				aRessyaPropertyCurr,
				strOperationNumber,
				contOperationElementCurr[iOperationIndex].iEkiOrder,
				NULL,
				NULL,
				EBeforeAfterType::BeforeAfterType_Unrelated);
		}

		vector<int> iLevelNext = contOperationElementCurr[iOperationIndex].iLevel;
		iLevelNext.back()++;

		junctionOperationElement(
			aRessyaPropertyCurr,
			contOperationElementCurr,
			iLevelNext,
			strOperationNumber);

		//if (contOperationElementCurr[iOperationIndex].iLevel.size() == 1)
		//{
		//	CustomizeJikokuhyouContent aCustomizeJikokuhyouContent(aRessyaPropertyCurr.getRessyaIndex());

		//	junctionOperationElement(
		//		aRessyaPropertyCurr,
		//		contOperationElementCurr,
		//		iLevelNext,
		//		strOperationNumber,
		//		&aCustomizeJikokuhyouContent);
		//}
		//else
		//{
		//	junctionOperationElement(
		//		aRessyaPropertyCurr,
		//		contOperationElementCurr,
		//		iLevelNext,
		//		strOperationNumber,
		//		NULL);
		//}
	}
	/**
		出区・路線外始発、運番変更、接続無し前列車接続からの、運用接続が完了した後は、
		ConnectWaitListについて探索を行います。
		ONSubが割り当て済みなら、そこから先の探索を行います。

		まず、m_contConnectWaitListをcontConnectWaitListTempにまるごとコピーしてから、
		contConnectWaitListTempについて探索を行います。
		その時、m_contConnectWaitListは一度クリアします。

		これは、contConnectWaitListTempに収められたいた作業から繋がる先に、別の増結作業があり、
		それらが待機状態になることが考えられるため、m_contConnectWaitListを受け入れ先として開けるためです。

		割り当てされていない場合は、m_contConnectWaitListに再度追加して、Subの割り当てを再度待ちます
		一回のループで、一作業も変化が起きなかった場合は、終了となります。
		(前列車接続から始まるが、接続されなかった場合など)
	*/
	bool bChanged;
	do
	{
		bChanged = false;
		vector< RessyaElement> contConnectWaitListTemp = m_contConnectWaitList;
		m_contConnectWaitList.clear();
		int iSizeCW = contConnectWaitListTemp.size();

#pragma omp parallel for schedule(guided)
		for (int idxConnect = 0;idxConnect<iSizeCW;idxConnect++  )
		{
			const RessyaElement& aRessyaElement = contConnectWaitListTemp[idxConnect];
			CdDedRessyaProperty aRessyaPropertyCurr = aRessyaElement.sRessyaProperty;
			vector<OperationElement>& contOperationElementCurr = m_contRessyaOperationElement
				[(int)aRessyaPropertyCurr.getRessyahoukou()][aRessyaPropertyCurr.getRessyaIndex()];
			bool bErase = false;
			if (aRessyaElement.BeforeOperation != NULL)
			{
				int iOperationIndex = 0;
				for (;iOperationIndex < (int)contOperationElementCurr.size(); iOperationIndex++)
				{
					if (contOperationElementCurr[iOperationIndex].BeforeOperation == aRessyaElement.BeforeOperation)
					{
						break;
					}
				}
				CentDedBeforeOperation* pBeforeOperation = contOperationElementCurr[iOperationIndex].BeforeOperation;
				if (pBeforeOperation->getBOperation() != CentDedBeforeOperation::EBOperation::BOperation_Connect)
				{
					continue;
				}
				/**
					増結編成の運番が割り当てられていない場合は、
					m_contConnectWaitListにaRessyaElementを格納して、次要素に進みます。
				*/
				if (!pBeforeOperation->getOperationNumberSubAssigned())
				{
#pragma omp critical(ConnectWaitList)
					m_contConnectWaitList.push_back(aRessyaElement);
					continue;
				}
#pragma omp critical(Operation)
				pBeforeOperation->mergeOperationNumber();

				vector<int> iLevelNext = contOperationElementCurr[iOperationIndex].iLevel;
				iLevelNext.back()++;
				junctionOperationElement(
					aRessyaPropertyCurr,
					contOperationElementCurr,
					iLevelNext,
					pBeforeOperation->getOperationNumberAfter());

				//同名被り区別用に付けられた印を削除します
#pragma omp critical(Operation)
				pBeforeOperation->trimSuffixOperationNumber();

				bChanged = true;
			}
			else if (aRessyaElement.AfterOperation != NULL)
			{
				int iOperationIndex = 0;
				for (; iOperationIndex < (int)contOperationElementCurr.size(); iOperationIndex++)
				{
					if (contOperationElementCurr[iOperationIndex].AfterOperation == aRessyaElement.AfterOperation)
					{
						break;
					}
				}
				CentDedAfterOperation* pAfterOperation = contOperationElementCurr[iOperationIndex].AfterOperation;
				if (pAfterOperation->getAOperation() != CentDedAfterOperation::EAOperation::AOperation_Connect)
				{
					continue;
				}
				if (!pAfterOperation->getOperationNumberSubAssigned())
				{
#pragma omp critical(ConnectWaitList)
					m_contConnectWaitList.push_back(aRessyaElement);
					continue;
				}
#pragma omp critical(Operation)
				pAfterOperation->mergeOperationNumber();

				vector<int> iLevelNext = contOperationElementCurr[iOperationIndex].iLevel;
				iLevelNext.back()++;
				junctionOperationElement(
					aRessyaPropertyCurr,
					contOperationElementCurr,
					iLevelNext,
					pAfterOperation->getOperationNumberAfter());
				
				//同名被り区別用に付けられた印を削除します
#pragma omp critical(Operation)
				pAfterOperation->trimSuffixOperationNumber();

				bChanged = true;
			}
		}
	} while (bChanged);

	//隠し種別が存在する場合、隠し種別の列車を削除します
	if (m_bHiddenExist)
	{
		for (int iRessyahoukou = Ressyahoukou_Kudari;
			iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
		{
			int iSize = pRessyaCont[iRessyahoukou]->size();
			const Mu<CentDedRessya*>* pCentDedRessyaCont = m_pDedDia->getCentDedRessyaCont((ERessyahoukou)iRessyahoukou)->getMuPtr();
#pragma omp parallel for schedule(dynamic)
			for (int idxRessya = 0; idxRessya < iSize; idxRessya++)
			{
				const CentDedRessya* pRessya =
					pCentDedRessyaCont->get(idxRessya);
				if (!m_contHidden[pRessya->getRessyasyubetsuIndex()])
				{
					continue;
				}
#pragma omp critical(CustomizeRessyaIndex)
				{
					vector<CustomizeJikokuhyouContent>& contCustomizeRessyaIndex =
						m_pDedDia->getcontCustomizeRessyaIndex((ERessyahoukou)iRessyahoukou);
					int iCustomizeIndex = -1;
					for (int idx = 0; idx < (int)contCustomizeRessyaIndex.size(); idx++)
					{
						for (int idxc = 0; idxc < (int)contCustomizeRessyaIndex[idx].iRessyaIndexCont.size(); idxc++)
						{
							if (contCustomizeRessyaIndex[idx].iRessyaIndexCont[idxc] == idxRessya)
							{
								iCustomizeIndex = idx;
							}
						}
						if (iCustomizeIndex != -1)
						{
							contCustomizeRessyaIndex.erase(contCustomizeRessyaIndex.begin() + iCustomizeIndex);
							break;
						}
					}
				}
			}
		}
	}

	completeCustomizeJikokuhyouContent();
}
	

vector<OperationElement> CDedOperationConnecter::searchBeforeOperationElement(
	CentDedBeforeOperationCont * pBeforeCont, 
	const CdDedJikoku ConnectJikoku,
	const CdDedRessyaProperty aRessyaProperty,
	const vector<int> iLevelParent,
	const int iEkiOrder,
	const int iEkiIndexofContExist,
	const int iRessyaTrackConnect)
{
		
	/**
		増結前作業
		・出区・路線外始発の場合は、contOutOuterに入れる。
		・前列車接続の場合は、前作業を後方に見て、番線と時刻を取得して、contRessyaExistに入れる

		・それ以外の作業に、増解結がある場合も
		・ここでは、路線外始発に当駅着時刻がなくても、入換や増解結等は有効とする。
	*/
	vector<OperationElement> contOperationElement;
	CentDedBeforeOperation* pFirstOperation = pBeforeCont->getMuPtr()->get(0);
	if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Out)
	{
		pFirstOperation->clearOperationNumber();
		CdDedRessyaProperty aRessyaPropertyTemp = aRessyaProperty;
		aRessyaPropertyTemp.setJikoku(pFirstOperation->getOutJikoku());
		RessyaElement aRessyaElement(pFirstOperation, aRessyaPropertyTemp);
		vector<int> iLevel = iLevelParent;
		iLevel.push_back(0);
#pragma omp critical(OutOuter)
		m_contOutOuter.push_back(aRessyaElement);
		contOperationElement.push_back(OperationElement(
			pFirstOperation, iLevel, iEkiOrder));
		if (!pFirstOperation->getInOutLinkCode().empty())
		{
#pragma omp critical(InOutLink)
			insertInOutLinkCodeElement(
				pFirstOperation->getInOutLinkCode(),
				aRessyaElement);
		}
	}
	else if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
	{
		pFirstOperation->clearOperationNumber();
		CdDedRessyaProperty aRessyaPropertyTemp = aRessyaProperty;
		aRessyaPropertyTemp.setJikoku(pFirstOperation->getOuterShihatsuJikoku());
		RessyaElement aRessyaElement(pFirstOperation, aRessyaPropertyTemp);
		vector<int> iLevel = iLevelParent;
		iLevel.push_back(0);
#pragma omp critical(OutOuter)
		m_contOutOuter.push_back(aRessyaElement);
		contOperationElement.push_back(OperationElement(
			pFirstOperation, iLevel, iEkiOrder));
		if (!pFirstOperation->getInOutLinkCode().empty())
		{
#pragma omp critical(InOutLink)
			insertInOutLinkCodeElement(
				pFirstOperation->getInOutLinkCode(),
				aRessyaElement);
		}
	}
	else if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Junction)
	{
		/**
			前列車接続の場合、最初にどの番線にいるのかを調べる。

			初期値は、発着番線・当駅発時刻を充てる。
			番線は、最も前にある入換作業の入換番線を取得する。
			時刻は、起点時刻が設定されている場合はそれを用い、
			NULLの場合は最も前にある、入換発・増結・解結のいずれを取得する。
			ただし、同じホームへの入換がある場合は、最も後の物のみが有効となる
		*/
		pFirstOperation->clearOperationNumber();

		int iRessyaTrackIndex = iRessyaTrackConnect;
		CdDedJikoku aOriginJikoku = ConnectJikoku;
		for (int idxb = pBeforeCont->size() - 1; idxb > 0; idxb--)
		{
			CentDedBeforeOperation* pBeforeOperation = pBeforeCont->getMuPtr()->get(idxb);
			if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
			{
				/**
					同じ番線への入換は、最も後の物のみが有効
				*/
				if (iRessyaTrackIndex != pBeforeOperation->getShuntTrackIndex())
				{
					aOriginJikoku = pBeforeOperation->getOperationHatsuJikoku();
					iRessyaTrackIndex = pBeforeOperation->getShuntTrackIndex();
				}
			}
			else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
			{
				aOriginJikoku = pBeforeOperation->getConnectJikoku();
			}
			else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
			{
				aOriginJikoku = pBeforeOperation->getReleaseJikoku();
			}
		}
		if (!pFirstOperation->getOriginJikoku().isNull())
		{
			aOriginJikoku = pFirstOperation->getOriginJikoku();
		}

		vector<int> iLevel = iLevelParent;
		iLevel.push_back(0);

		CdDedRessyaProperty aRessyaPropertyTemp = aRessyaProperty;
		aRessyaPropertyTemp.setJikoku(aOriginJikoku);
		contOperationElement.push_back(
			OperationElement(pFirstOperation,
				iLevel,
				iEkiOrder,
				iEkiIndexofContExist,
				iRessyaTrackIndex));
		RessyaElement aRessyaElement(pFirstOperation, aRessyaPropertyTemp);

#pragma omp critical(RessyaExist)
		InsertRessyaElement(
			iEkiIndexofContExist,
			iRessyaTrackIndex,
			aRessyaElement);

#pragma omp critical(JunctionList)
		m_contJunctionList.push_back(aRessyaElement);
	}

	int iLevelAdd = 1;
	for (int idxb = 1; idxb < (int)pBeforeCont->size(); idxb++)
	{
		CentDedBeforeOperation* pBeforeOperation = pBeforeCont->getMuPtr()->get(idxb);
		if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
		{
			pBeforeOperation->clearOperationNumber();

			int iConnectTrackIndex = iRessyaTrackConnect;
			for (int idxb2 = pBeforeCont->size() - 1; idxb2 > idxb; idxb2--)
			{
				CentDedBeforeOperation* pBeforeOperation2 = pBeforeCont->getMuPtr()->get(idxb2);
				if (pBeforeOperation2->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
				{
					iConnectTrackIndex = pBeforeOperation2->getShuntTrackIndex();
				}
			}
			vector<int> iLevel = iLevelParent;
			iLevel.push_back(iLevelAdd);
			OperationElement aOperationElement(
				pBeforeOperation, iLevel, iEkiOrder);
			vector<OperationElement> contTemp = searchBeforeOperationElement(
				pBeforeOperation->getCentDedBeforeOperationCont(),
				pBeforeOperation->getConnectJikoku(),
				aRessyaProperty,
				iLevel,
				iEkiOrder,
				iEkiIndexofContExist,
				iConnectTrackIndex);

			contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());
			contOperationElement.push_back(aOperationElement);

			iLevelAdd++;
		}
		else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
		{
			pBeforeOperation->clearOperationNumber();

			int iReleaseTrackIndex = iRessyaTrackConnect;
			for (int idxb2 = pBeforeCont->size() - 1; idxb2 > idxb; idxb2--)
			{
				CentDedBeforeOperation* pBeforeOperation2 = pBeforeCont->getMuPtr()->get(idxb2);
				if (pBeforeOperation2->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
				{
					iReleaseTrackIndex = pBeforeOperation2->getShuntTrackIndex();
				}
			}

			vector<int> iLevel = iLevelParent;
			iLevel.push_back(iLevelAdd);
			OperationElement aOperationElement(
				pBeforeOperation, iLevel, iEkiOrder);
			vector<OperationElement> contTemp = searchAfterOperationElement(
				pBeforeOperation->getCentDedAfterOperationCont(),
				pBeforeOperation->getReleaseJikoku(),
				aRessyaProperty,
				iLevel,
				iEkiOrder,
				iEkiIndexofContExist,
				iReleaseTrackIndex);

			contOperationElement.push_back(aOperationElement);
			contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());

			iLevelAdd++;
		}
		else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_NumberChange)
		{
			pBeforeOperation->clearOperationNumber();

			//暫定措置、増結時刻を入れておく
			CdDedRessyaProperty aRessyaPropertyTemp = aRessyaProperty;
			aRessyaPropertyTemp.setJikoku(ConnectJikoku);
			RessyaElement aRessyaElement(pBeforeOperation, aRessyaPropertyTemp);
			vector<int> iLevel = iLevelParent;
			iLevel.push_back(iLevelAdd);
			//Ver2.06.05 運用番号順反転の場合は、m_contNumberChangeに入れる必要は無い。
			if (!pBeforeOperation->getOperationNumberReverse())
			{
#pragma omp critical(NumberChange)
				m_contNumberChange.push_back(aRessyaElement);
			}
			OperationElement aOperationElement(
				pBeforeOperation, iLevel, iEkiOrder);

			contOperationElement.push_back(aOperationElement);

			iLevelAdd++;
		}

	}
	return contOperationElement;
}
vector<OperationElement> CDedOperationConnecter::searchBeforeOperationElementLight(
	CentDedBeforeOperationCont* pBeforeCont,
	const CdDedJikoku ConnectJikoku,
	const CdDedRessyaProperty aRessyaProperty,
	const vector<int> iLevelParent,
	const int iEkiOrder,
	const int iEkiIndexofContExist,
	const int iRessyaTrackConnect)
{

	/**
		増結前作業
		・出区・路線外始発の場合は、contOutOuterに入れる。
		・前列車接続の場合は、前作業を後方に見て、番線と時刻を取得して、contRessyaExistに入れる

		・それ以外の作業に、増解結がある場合も
		・ここでは、路線外始発に当駅着時刻がなくても、入換や増解結等は有効とする。
	*/
	vector<OperationElement> contOperationElement;
	CentDedBeforeOperation* pFirstOperation = pBeforeCont->getMuPtr()->get(0);
	if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Out ||
		pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
	{
		vector<int> iLevel = iLevelParent;
		iLevel.push_back(0);
		contOperationElement.push_back(OperationElement(
			pFirstOperation, iLevel, iEkiOrder));
	}
	else if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Junction)
	{
		/**
			前列車接続の場合、最初にどの番線にいるのかを調べる。

			初期値は、発着番線・当駅発時刻を充てる。
			番線は、最も前にある入換作業の入換番線を取得する。
			時刻は、起点時刻が設定されている場合はそれを用い、
			NULLの場合は最も前にある、入換発・増結・解結のいずれを取得する。
			ただし、同じホームへの入換がある場合は、最も後の物のみが有効となる
		*/
		pFirstOperation->clearOperationNumber();

		int iRessyaTrackIndex = iRessyaTrackConnect;
		CdDedJikoku aOriginJikoku = ConnectJikoku;
		for (int idxb = pBeforeCont->size() - 1; idxb > 0; idxb--)
		{
			CentDedBeforeOperation* pBeforeOperation = pBeforeCont->getMuPtr()->get(idxb);
			if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
			{
				/**
					同じ番線への入換は、最も後の物のみが有効
				*/
				if (iRessyaTrackIndex != pBeforeOperation->getShuntTrackIndex())
				{
					aOriginJikoku = pBeforeOperation->getOperationHatsuJikoku();
					iRessyaTrackIndex = pBeforeOperation->getShuntTrackIndex();
				}
			}
			else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
			{
				aOriginJikoku = pBeforeOperation->getConnectJikoku();
			}
			else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
			{
				aOriginJikoku = pBeforeOperation->getReleaseJikoku();
			}
		}
		if (!pFirstOperation->getOriginJikoku().isNull())
		{
			aOriginJikoku = pFirstOperation->getOriginJikoku();
		}

		vector<int> iLevel = iLevelParent;
		iLevel.push_back(0);

		CdDedRessyaProperty aRessyaPropertyTemp = aRessyaProperty;
		aRessyaPropertyTemp.setJikoku(aOriginJikoku);
		contOperationElement.push_back(
			OperationElement(pFirstOperation,
				iLevel,
				iEkiOrder,
				iEkiIndexofContExist,
				iRessyaTrackIndex));
		RessyaElement aRessyaElement(pFirstOperation, aRessyaPropertyTemp);
#pragma omp critical(RessyaExist)
		InsertRessyaElement(
			iEkiIndexofContExist,
			iRessyaTrackIndex,
			aRessyaElement);
		if (m_iPatternDiagramPreviewCycleSecond > 0)
		{
			for (int iShiftSecond = m_iPatternDiagramPreviewCycleSecond; iShiftSecond <= m_iPatternDiagramPreviewRange; iShiftSecond += m_iPatternDiagramPreviewCycleSecond)
			{
				CdDedJikoku aOriginJikokuPlus = aOriginJikoku;
				aOriginJikokuPlus.addSeconds(iShiftSecond);
				aRessyaElement.sRessyaProperty.setJikoku(aOriginJikokuPlus);
				aRessyaElement.iShiftSecond = iShiftSecond;
#pragma omp critical(RessyaExist)
				InsertRessyaElement(
					iEkiIndexofContExist,
					iRessyaTrackIndex,
					aRessyaElement);

				CdDedJikoku aOriginJikokuMinus = aOriginJikoku;
				aOriginJikokuMinus.addSeconds(-iShiftSecond);
				aRessyaElement.sRessyaProperty.setJikoku(aOriginJikokuMinus);
				aRessyaElement.iShiftSecond = -iShiftSecond;
#pragma omp critical(RessyaExist)
				InsertRessyaElement(
					iEkiIndexofContExist,
					iRessyaTrackIndex,
					aRessyaElement);
			}
		}
	}

	int iLevelAdd = 1;
	for (int idxb = 1; idxb < (int)pBeforeCont->size(); idxb++)
	{
		CentDedBeforeOperation* pBeforeOperation = pBeforeCont->getMuPtr()->get(idxb);
		if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
		{
			pBeforeOperation->clearOperationNumber();

			int iConnectTrackIndex = iRessyaTrackConnect;
			for (int idxb2 = pBeforeCont->size() - 1; idxb2 > idxb; idxb2--)
			{
				CentDedBeforeOperation* pBeforeOperation2 = pBeforeCont->getMuPtr()->get(idxb2);
				if (pBeforeOperation2->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
				{
					iConnectTrackIndex = pBeforeOperation2->getShuntTrackIndex();
				}
			}
			vector<int> iLevel = iLevelParent;
			iLevel.push_back(iLevelAdd);
			OperationElement aOperationElement(
				pBeforeOperation, iLevel, iEkiOrder);
			vector<OperationElement> contTemp = searchBeforeOperationElementLight(
				pBeforeOperation->getCentDedBeforeOperationCont(),
				pBeforeOperation->getConnectJikoku(),
				aRessyaProperty,
				iLevel,
				iEkiOrder,
				iEkiIndexofContExist,
				iConnectTrackIndex);

			contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());
			contOperationElement.push_back(aOperationElement);

			iLevelAdd++;
		}
		else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
		{
			pBeforeOperation->clearOperationNumber();

			int iReleaseTrackIndex = iRessyaTrackConnect;
			for (int idxb2 = pBeforeCont->size() - 1; idxb2 > idxb; idxb2--)
			{
				CentDedBeforeOperation* pBeforeOperation2 = pBeforeCont->getMuPtr()->get(idxb2);
				if (pBeforeOperation2->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
				{
					iReleaseTrackIndex = pBeforeOperation2->getShuntTrackIndex();
				}
			}

			vector<int> iLevel = iLevelParent;
			iLevel.push_back(iLevelAdd);
			OperationElement aOperationElement(
				pBeforeOperation, iLevel, iEkiOrder);
			vector<OperationElement> contTemp = searchAfterOperationElementLight(
				pBeforeOperation->getCentDedAfterOperationCont(),
				pBeforeOperation->getReleaseJikoku(),
				aRessyaProperty,
				iLevel,
				iEkiOrder,
				iEkiIndexofContExist,
				iReleaseTrackIndex);

			contOperationElement.push_back(aOperationElement);
			contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());

			iLevelAdd++;
		}

	}
	return contOperationElement;
}


vector<OperationElement> CDedOperationConnecter::searchAfterOperationElement(
	CentDedAfterOperationCont * pAfterCont, 
	const CdDedJikoku ReleaseJikoku,
	const CdDedRessyaProperty aRessyaProperty,
	const vector<int> iLevelParent,
	const int iEkiOrder,
	const int iEkiIndexofContExist,
	const int iRessyaTrackRelease)
{
	/**
		解結後作業
		・次列車接続の場合は、後作業を前方に見て、番線と時刻を取得して、contRessyaExistに入れる

		・それ以外の作業に、増解結がある場合も
		・ここでは、路線外終着に当駅発時刻がなくても、入換や増解結等は有効とする。

		JunctionJikokuとPrevRessyahoukouを導出する。
	*/
	vector<OperationElement> contOperationElement;
	int iLevelAdd = 0;
	for (int idxa = 0; idxa < (int)pAfterCont->size() - 1; idxa++)
	{
		CentDedAfterOperation* pAfterOperation = pAfterCont->getMuPtr()->get(idxa);
		if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
		{
			pAfterOperation->clearOperationNumber();

			int iConnectTrackIndex = iRessyaTrackRelease;
			for (int idxa2 = 0; idxa2 < idxa; idxa2++)
			{
				CentDedAfterOperation* pAfterOperation2 = pAfterCont->getMuPtr()->get(idxa2);
				if (pAfterOperation2->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
				{
					iConnectTrackIndex = pAfterOperation2->getShuntTrackIndex();
				}
			}
			vector<int> iLevel = iLevelParent;
			iLevel.push_back(iLevelAdd);
			OperationElement aOperationElement(
				pAfterOperation, iLevel, iEkiOrder);
			vector<OperationElement> contTemp = searchBeforeOperationElement(
				pAfterOperation->getCentDedBeforeOperationCont(),
				pAfterOperation->getConnectJikoku(),
				aRessyaProperty,
				iLevel,
				iEkiOrder,
				iEkiIndexofContExist,
				iConnectTrackIndex);

			contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());
			contOperationElement.push_back(aOperationElement);

			iLevelAdd++;
		}
		else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
		{
			pAfterOperation->clearOperationNumber();

			int iReleaseTrackIndex = iRessyaTrackRelease;
			for (int idxa2 = 0; idxa2 < idxa; idxa2++)
			{
				CentDedAfterOperation* pAfterOperation2 = pAfterCont->getMuPtr()->get(idxa2);
				if (pAfterOperation2->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
				{
					iReleaseTrackIndex = pAfterOperation2->getShuntTrackIndex();
				}
			}
			vector<int> iLevel = iLevelParent;
			iLevel.push_back(iLevelAdd);
			OperationElement aOperationElement(
				pAfterOperation, iLevel, iEkiOrder);
			vector<OperationElement> contTemp = searchAfterOperationElement(
				pAfterOperation->getCentDedAfterOperationCont(),
				pAfterOperation->getReleaseJikoku(),
				aRessyaProperty,
				iLevel,
				iEkiOrder,
				iEkiIndexofContExist,
				iReleaseTrackIndex);

			contOperationElement.push_back(aOperationElement);
			contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());

			iLevelAdd++;
		}
		else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_NumberChange)
		{
			pAfterOperation->clearOperationNumber();

			//暫定措置、解結時刻を入れておく
			CdDedRessyaProperty aRessyaPropertyTemp = aRessyaProperty;
			aRessyaPropertyTemp.setJikoku(ReleaseJikoku);
			RessyaElement aRessyaElement(pAfterOperation, aRessyaPropertyTemp);
			vector<int> iLevel = iLevelParent;
			iLevel.push_back(iLevelAdd);
			//Ver2.06.05 運用番号順反転の場合は、m_contNumberChangeに入れる必要は無い。
			if (!pAfterOperation->getOperationNumberReverse())
			{
#pragma omp critical(NumberChange)
				m_contNumberChange.push_back(aRessyaElement);
			}
			OperationElement aOperationElement(
				pAfterOperation, iLevel, iEkiOrder);

			contOperationElement.push_back(aOperationElement);

			iLevelAdd++;
		}
	}

	CentDedAfterOperation* pLastOperation = pAfterCont->getMuPtr()->get(pAfterCont->size() - 1);

	if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_In ||
		pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
	{
		pLastOperation->clearOperationNumber();
		vector<int> iLevel = iLevelParent;
		iLevel.push_back(iLevelAdd);
		contOperationElement.push_back(OperationElement(
			pLastOperation, iLevel, iEkiOrder));
		if (!pLastOperation->getInOutLinkCode().empty())
		{
			CdDedRessyaProperty aRessyaPropertyTemp = aRessyaProperty;
			if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_In)
			{
				aRessyaPropertyTemp.setJikoku(pLastOperation->getInJikoku());
			}
			else
			{
				aRessyaPropertyTemp.setJikoku(pLastOperation->getOuterShuchakuJikoku());
			}
			RessyaElement aRessyaElement(pLastOperation, aRessyaPropertyTemp);
#pragma omp critical(InOutLink)
			insertInOutLinkCodeElement(
				pLastOperation->getInOutLinkCode(),
				aRessyaElement);
		}
	}
	else if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Junction)
	{
		/**
			後列車接続の場合、最後にどの番線にいるのかを調べる
		*/
		int iRessyaTrackIndex = iRessyaTrackRelease;
		CdDedJikoku aTerminalJikoku = ReleaseJikoku;
		CdDedJikoku aJunctionJikoku = ReleaseJikoku;
		int iPrevRessyahoukou = 0;

		for (int idxa = 0; idxa < pAfterCont->size() - 1; idxa++)
		{
			CentDedAfterOperation* pAfterOperation = pAfterCont->getMuPtr()->get(idxa);
			if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
			{
				/**
					同じ番線への入換は、最も前の物のみが有効
				*/
				if (iRessyaTrackIndex == pAfterOperation->getShuntTrackIndex())
				{
					continue;
				}
				aTerminalJikoku = pAfterOperation->getOperationChakuJikoku(true);
				aJunctionJikoku = pAfterOperation->getOperationChakuJikoku(true);
				if ((iRessyaTrackIndex > pAfterOperation->getShuntTrackIndex() &&
					aRessyaProperty.getRessyahoukou() == Ressyahoukou_Kudari) ||
					(iRessyaTrackIndex < pAfterOperation->getShuntTrackIndex() &&
						aRessyaProperty.getRessyahoukou() == Ressyahoukou_Nobori))
				{
					iPrevRessyahoukou = 2;
				}
				else
				{
					iPrevRessyahoukou = -2;
				}
				iRessyaTrackIndex = pAfterOperation->getShuntTrackIndex();
			}
			else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
			{
				aTerminalJikoku = pAfterOperation->getConnectJikoku();
			}
			else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
			{
				aTerminalJikoku = pAfterOperation->getReleaseJikoku();
			}
		}
		if (!pLastOperation->getTerminalJikoku().isNull())
		{
			aTerminalJikoku = pLastOperation->getTerminalJikoku();
		}
		pLastOperation->setPrevRessyahoukou(iPrevRessyahoukou);
		pLastOperation->setJunctionJikoku(aJunctionJikoku);

		vector<int> iLevel = iLevelParent;
		iLevel.push_back(iLevelAdd);
		contOperationElement.push_back(
			OperationElement(pLastOperation, 
				iLevel,
				iEkiOrder,
				iEkiIndexofContExist,
				iRessyaTrackIndex));

		CdDedRessyaProperty aRessyaPropertyTemp = aRessyaProperty;
		aRessyaPropertyTemp.setJikoku(aTerminalJikoku);
		RessyaElement aRessyaElement(pLastOperation, aRessyaPropertyTemp);
#pragma omp critical(RessyaExist)
		InsertRessyaElement(
			iEkiIndexofContExist,
			iRessyaTrackIndex,
			aRessyaElement);
	}
	return contOperationElement;
}

vector<OperationElement> CDedOperationConnecter::searchAfterOperationElementLight(
	CentDedAfterOperationCont* pAfterCont,
	const CdDedJikoku ReleaseJikoku,
	const CdDedRessyaProperty aRessyaProperty,
	const vector<int> iLevelParent,
	const int iEkiOrder,
	const int iEkiIndexofContExist,
	const int iRessyaTrackRelease)
{
	/**
		解結後作業
		・次列車接続の場合は、後作業を前方に見て、番線と時刻を取得して、contRessyaExistに入れる

		・それ以外の作業に、増解結がある場合も
		・ここでは、路線外終着に当駅発時刻がなくても、入換や増解結等は有効とする。

		JunctionJikokuとPrevRessyahoukouを導出する。
	*/
	vector<OperationElement> contOperationElement;
	int iLevelAdd = 0;
	for (int idxa = 0; idxa < (int)pAfterCont->size() - 1; idxa++)
	{
		CentDedAfterOperation* pAfterOperation = pAfterCont->getMuPtr()->get(idxa);
		if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
		{
			pAfterOperation->clearOperationNumber();

			int iConnectTrackIndex = iRessyaTrackRelease;
			for (int idxa2 = 0; idxa2 < idxa; idxa2++)
			{
				CentDedAfterOperation* pAfterOperation2 = pAfterCont->getMuPtr()->get(idxa2);
				if (pAfterOperation2->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
				{
					iConnectTrackIndex = pAfterOperation2->getShuntTrackIndex();
				}
			}
			vector<int> iLevel = iLevelParent;
			iLevel.push_back(iLevelAdd);
			OperationElement aOperationElement(
				pAfterOperation, iLevel, iEkiOrder);
			vector<OperationElement> contTemp = searchBeforeOperationElementLight(
				pAfterOperation->getCentDedBeforeOperationCont(),
				pAfterOperation->getConnectJikoku(),
				aRessyaProperty,
				iLevel,
				iEkiOrder,
				iEkiIndexofContExist,
				iConnectTrackIndex);

			contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());
			contOperationElement.push_back(aOperationElement);

			iLevelAdd++;
		}
		else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
		{
			pAfterOperation->clearOperationNumber();

			int iReleaseTrackIndex = iRessyaTrackRelease;
			for (int idxa2 = 0; idxa2 < idxa; idxa2++)
			{
				CentDedAfterOperation* pAfterOperation2 = pAfterCont->getMuPtr()->get(idxa2);
				if (pAfterOperation2->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
				{
					iReleaseTrackIndex = pAfterOperation2->getShuntTrackIndex();
				}
			}
			vector<int> iLevel = iLevelParent;
			iLevel.push_back(iLevelAdd);
			OperationElement aOperationElement(
				pAfterOperation, iLevel, iEkiOrder);
			vector<OperationElement> contTemp = searchAfterOperationElementLight(
				pAfterOperation->getCentDedAfterOperationCont(),
				pAfterOperation->getReleaseJikoku(),
				aRessyaProperty,
				iLevel,
				iEkiOrder,
				iEkiIndexofContExist,
				iReleaseTrackIndex);

			contOperationElement.push_back(aOperationElement);
			contOperationElement.insert(contOperationElement.end(), contTemp.begin(), contTemp.end());

			iLevelAdd++;
		}
	}

	CentDedAfterOperation* pLastOperation = pAfterCont->getMuPtr()->get(pAfterCont->size() - 1);

	if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_In ||
		pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
	{
		pLastOperation->clearOperationNumber();
		vector<int> iLevel = iLevelParent;
		iLevel.push_back(iLevelAdd);
		contOperationElement.push_back(OperationElement(
			pLastOperation, iLevel, iEkiOrder));
	}
	else if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Junction)
	{
		/**
			後列車接続の場合、最後にどの番線にいるのかを調べる
		*/
		int iRessyaTrackIndex = iRessyaTrackRelease;
		CdDedJikoku aTerminalJikoku = ReleaseJikoku;
		CdDedJikoku aJunctionJikoku = ReleaseJikoku;
		int iPrevRessyahoukou = 0;

		for (int idxa = 0; idxa < pAfterCont->size() - 1; idxa++)
		{
			CentDedAfterOperation* pAfterOperation = pAfterCont->getMuPtr()->get(idxa);
			if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
			{
				/**
					同じ番線への入換は、最も前の物のみが有効
				*/
				if (iRessyaTrackIndex == pAfterOperation->getShuntTrackIndex())
				{
					continue;
				}
				aTerminalJikoku = pAfterOperation->getOperationChakuJikoku(true);
				aJunctionJikoku = pAfterOperation->getOperationChakuJikoku(true);
				if ((iRessyaTrackIndex > pAfterOperation->getShuntTrackIndex() &&
					aRessyaProperty.getRessyahoukou() == Ressyahoukou_Kudari) ||
					(iRessyaTrackIndex < pAfterOperation->getShuntTrackIndex() &&
						aRessyaProperty.getRessyahoukou() == Ressyahoukou_Nobori))
				{
					iPrevRessyahoukou = 2;
				}
				else
				{
					iPrevRessyahoukou = -2;
				}
				iRessyaTrackIndex = pAfterOperation->getShuntTrackIndex();
			}
			else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
			{
				aTerminalJikoku = pAfterOperation->getConnectJikoku();
			}
			else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
			{
				aTerminalJikoku = pAfterOperation->getReleaseJikoku();
			}
		}
		if (!pLastOperation->getTerminalJikoku().isNull())
		{
			aTerminalJikoku = pLastOperation->getTerminalJikoku();
		}
		pLastOperation->setPrevRessyahoukou(iPrevRessyahoukou);
		pLastOperation->setJunctionJikoku(aJunctionJikoku);

		vector<int> iLevel = iLevelParent;
		iLevel.push_back(iLevelAdd);
		CdDedRessyaProperty aRessyaPropertyTemp = aRessyaProperty;
		aRessyaPropertyTemp.setJikoku(aTerminalJikoku);
		RessyaElement aRessyaElement(pLastOperation, aRessyaPropertyTemp); 
		contOperationElement.push_back(
			OperationElement(pLastOperation,
				iLevel,
				iEkiOrder,
				iEkiIndexofContExist,
				iRessyaTrackIndex));

#pragma omp critical(RessyaExist)
		InsertRessyaElement(
			iEkiIndexofContExist,
			iRessyaTrackIndex,
			aRessyaElement);

#pragma omp critical(JunctionList)
		m_contJunctionList.push_back(aRessyaElement);

		if (m_iPatternDiagramPreviewCycleSecond > 0)
		{
			for (int iShiftSecond = m_iPatternDiagramPreviewCycleSecond; iShiftSecond <= m_iPatternDiagramPreviewRange; iShiftSecond += m_iPatternDiagramPreviewCycleSecond)
			{
				CdDedJikoku aTerminalJikokuPlus = aTerminalJikoku;
				aTerminalJikokuPlus.addSeconds(iShiftSecond);
				aRessyaElement.sRessyaProperty.setJikoku(aTerminalJikokuPlus);
				aRessyaElement.iShiftSecond = iShiftSecond;
#pragma omp critical(RessyaExist)
				InsertRessyaElement(
					iEkiIndexofContExist,
					iRessyaTrackIndex,
					aRessyaElement);

#pragma omp critical(JunctionList)
				m_contJunctionList.push_back(aRessyaElement);

				CdDedJikoku aTerminalJikokuMinus = aTerminalJikoku;
				aTerminalJikokuMinus.addSeconds(-iShiftSecond);
				aRessyaElement.sRessyaProperty.setJikoku(aTerminalJikokuMinus);
				aRessyaElement.iShiftSecond = -iShiftSecond;
#pragma omp critical(RessyaExist)
				InsertRessyaElement(
					iEkiIndexofContExist,
					iRessyaTrackIndex,
					aRessyaElement);

#pragma omp critical(JunctionList)
				m_contJunctionList.push_back(aRessyaElement);
			}
		}
	}
	return contOperationElement;
}

void CDedOperationConnecter::junctionOperationElement(
	const CdDedRessyaProperty aRessyaPropertyCurr, 
	const vector<OperationElement>& contOperationElementCurr,
	const vector<int>& iLevelSearch,
	//const int iOperationIndexPrev,
	const vector<tstring>& strOperationNumber/*,
	CustomizeJikokuhyouContent* pCustomizeJikokuhyouContent*/)
{
	/**
		まずはiLevelSearchをもとに、contOperationElementCurrの中から、次作業を探します。
	*/
	bool bFoundNext = false;
	int iOperationIndex = 0;
	for (;iOperationIndex < (int)contOperationElementCurr.size() && !bFoundNext; iOperationIndex++)
	{
		if (contOperationElementCurr[iOperationIndex].iLevel == iLevelSearch)
		{
			bFoundNext = true;
			break;
		}
	}

	/**
		見つからなかった場合は、呼び出し元の作業が、増結前作業の最後の作業だと考え、
		その親作業を探索します。
		親作業が見つかったら、その作業の増結編成運用番号にstrOperationNumberを入れて終了します。
		見つからなかった場合も同じく終了です。
	*/
	if (!bFoundNext)
	{
		vector<int> iLevelParent = iLevelSearch;
		iLevelParent.pop_back();
		for (int iOperationIndexParent = 0;
			iOperationIndexParent < (int)contOperationElementCurr.size(); iOperationIndexParent++)
		{
			CentDedBeforeOperation* pBeforeOperationParent = contOperationElementCurr[iOperationIndexParent].BeforeOperation;
			CentDedAfterOperation* pAfterOperationParent = contOperationElementCurr[iOperationIndexParent].AfterOperation;
			if (contOperationElementCurr[iOperationIndexParent].iLevel != iLevelParent)
			{
				continue;
			}
			if (pBeforeOperationParent != NULL &&
				pBeforeOperationParent->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
			{
#pragma omp critical(Operation)
				pBeforeOperationParent->setOperationNumberSub(
					strOperationNumber);
			}
			else if (pAfterOperationParent != NULL &&
				pAfterOperationParent->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
			{
#pragma omp critical(Operation)
				pAfterOperationParent->setOperationNumberSub(
					strOperationNumber);
			}
			break;
		}
		return;
	}

	if (contOperationElementCurr[iOperationIndex].BeforeOperation != NULL)
	{
		CentDedBeforeOperation* pBeforeOperation = contOperationElementCurr[iOperationIndex].BeforeOperation;
		if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
		{
			/**
				増結の場合
				(1)strOperationNumberをOperationNumberMainにセット
				(2)ONSubが入力済みの場合、二つの運番を合体して、Afterへ入れる
					入力されてない場合、m_contConnectWaitListに、この作業と列車情報を格納して終了。
				(3)Afterへ入れた後、次の作業の検索を行う、
					iLevelの末尾がこの作業よりも+1のものをiLevelNextとし
					iLevelNextと運用番号をjunctionOperationElementに渡し、次作業を探索します。

			*/
#pragma omp critical(Operation)
			pBeforeOperation->setOperationNumberMain(strOperationNumber);
			if (pBeforeOperation->getOperationNumberSubAssigned())
			{
#pragma omp critical(Operation)
				pBeforeOperation->mergeOperationNumber();

				vector<int> iLevelNext = iLevelSearch;
				iLevelNext.back()++;
				junctionOperationElement(
					aRessyaPropertyCurr,
					contOperationElementCurr,
					iLevelNext,
					pBeforeOperation->getOperationNumberAfter()/*,
					pCustomizeJikokuhyouContent*/);

#pragma omp critical(Operation)
				pBeforeOperation->trimSuffixOperationNumber();
			}
			else
			{
				RessyaElement aRessyaElement(
					pBeforeOperation, aRessyaPropertyCurr);
#pragma omp critical(ConnectWaitList)
				m_contConnectWaitList.push_back(aRessyaElement);
			}
		}
		else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
		{
			/**
				解結の場合
				(1)strOperationNumberをONBeforeにセット。
				(2)splitでONMainとSubに分割
				(3)主編成と解結編成それぞれの次作業に移る
					iLevelの末尾がこの作業よりも+1のものをiLevelNextとし
					iLevelNextと運用番号をjunctionOperationElementに渡し、主編成の次作業を探索します。
					iLevelに0を一つ加えたものををiLevelSubとし
					iLevelSubと運用番号をjunctionOperationElementに渡し、解結編成の次作業を探索します。
			*/
#pragma omp critical(Operation)
			pBeforeOperation->setOperationNumberBefore(strOperationNumber);

			vector<int> iLevelNext = iLevelSearch;
			iLevelNext.back()++;
			junctionOperationElement(
				aRessyaPropertyCurr,
				contOperationElementCurr,
				iLevelNext,
				pBeforeOperation->getOperationNumberMain()/*,
				pCustomizeJikokuhyouContent*/);

			vector<int> iLevelSub = iLevelSearch;
			iLevelSub.push_back(0);
			junctionOperationElement(
				aRessyaPropertyCurr,
				contOperationElementCurr,
				iLevelSub,
				pBeforeOperation->getOperationNumberSub()/*,
				NULL*/);
#pragma omp critical(Operation)
			pBeforeOperation->trimSuffixOperationNumber();
		}
		else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_NumberChange)
		{
			if (pBeforeOperation->getOperationNumberReverse())
			{
				/**
					運番変更(反転)の場合
					(1)strOperationNumberをAssignedにセット、m_OperationNumber3には運用番号が反転して入力される。
					(2)iLevelSearchの末尾に1を加えたものをiLevelNextとし、次の作業の探索を行う、次作業に渡す運用番号はgetOperationNumberで取得、反転済みなのでそのまま渡す。
				*/
#pragma omp critical(Operation)
				pBeforeOperation->setOperationNumberAssigned(strOperationNumber);

				vector<int> iLevelNext = iLevelSearch;
				iLevelNext.back()++;
				junctionOperationElement(
					aRessyaPropertyCurr,
					contOperationElementCurr,
					iLevelNext,
					pBeforeOperation->getOperationNumber());
			}
			else
			{
				/**
					運番変更(非反転)の場合
					(1)strOperationNumberをAssignedにセット。
					(2)この作業を終点として、OperationTableListに書き込む
					※これ以降の運番探索は、別に行う。→Ver2.05 ここで行うように変更(取りやめ)
				*/
				vector<tstring> strOperationNumberTemp = strOperationNumber;
				addOperationTableContent(
					aRessyaPropertyCurr,
					strOperationNumberTemp,
					contOperationElementCurr[iOperationIndex].iEkiOrder,
					NULL,
					EBeforeAfterType::BeforeAfterType_OperationNumberChange);
#pragma omp critical(Operation)
				pBeforeOperation->setOperationNumberAssigned(strOperationNumberTemp);
			}
			//ここから、運番変更後の処理

//			vector<tstring> strOperationNumber = pBeforeOperation->getOperationNumber();
//			if (strOperationNumber.empty())
//			{
//				//tstring strTemp = _T("Tmp");
//				//strTemp += to_tstring(aRessyaPropertyCurr.getRessyaIndex());
//				//strOperationNumber.push_back(strTemp);
//				strOperationNumber.push_back(tstring());
//			}
//			else
//			{
//#pragma omp critical(OperationTableContentBuffer)
//				insertOperationTableContentToBuffer(
//					aRessyaPropertyCurr,
//					strOperationNumber,
//					contOperationElementCurr[iOperationIndex].iEkiOrder,
//					NULL,
//					NULL,
//					EBeforeAfterType::BeforeAfterType_OperationNumberChange);
//			}
//
//			vector<int> iLevelNext = iLevelSearch;
//			iLevelNext.back()++;
//			junctionOperationElement(
//				aRessyaPropertyCurr,
//				contOperationElementCurr,
//				iLevelNext,
//				strOperationNumber,
//				pCustomizeJikokuhyouContent);

		}
		/**
			BeforeJunctionの処理は、前列車AfterJunctionの処理の後部に移管
		*/
	}
	else
	{
		CentDedAfterOperation* pAfterOperation = contOperationElementCurr[iOperationIndex].AfterOperation;
		if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
		{
			/**
				増結の場合
				(1)strOperationNumberをOperationNumberMainにセット
				(2)ONSubが入力済みの場合、二つの運番を合体して、Afterへ入れる
					入力されてない場合、m_contConnectWaitListに、この作業と列車情報を格納して終了。
				(3)Afterへ入れた後、次の作業の検索を行う、
					iLevelの末尾がこの作業よりも+1のものをiLevelNextとし
					iLevelNextと運用番号をjunctionOperationElementに渡し、次作業を探索します。
			*/
#pragma omp critical(Operation)
			pAfterOperation->setOperationNumberMain(strOperationNumber);
			if (pAfterOperation->getOperationNumberSubAssigned())
			{
#pragma omp critical(Operation)
				pAfterOperation->mergeOperationNumber();

				vector<int> iLevelNext = iLevelSearch;
				iLevelNext.back()++;
				junctionOperationElement(
					aRessyaPropertyCurr,
					contOperationElementCurr,
					iLevelNext,
					pAfterOperation->getOperationNumberAfter()/*,
					pCustomizeJikokuhyouContent*/);

#pragma omp critical(Operation)
				pAfterOperation->trimSuffixOperationNumber();
			}
			else
			{
				RessyaElement aRessyaElement(
					contOperationElementCurr[iOperationIndex].AfterOperation, aRessyaPropertyCurr);
#pragma omp critical(ConnectWaitList)
				m_contConnectWaitList.push_back(aRessyaElement);
			}
		}
		else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
		{
			/**
				解結の場合
				(1)strOperationNumberをONBeforeにセット。
				(2)splitでONMainとSubに分割
				(3)主編成と解結編成それぞれの次作業に移る
					iLevelの末尾がこの作業よりも+1のものをiLevelNextとし
					iLevelNextと運用番号をjunctionOperationElementに渡し、主編成の次作業を探索します。
					iLevelに0を一つ加えたものををiLevelSubとし
					iLevelSubと運用番号をjunctionOperationElementに渡し、解結編成の次作業を探索します。
			*/
#pragma omp critical(Operation)
			pAfterOperation->setOperationNumberBefore(strOperationNumber);

			vector<int> iLevelNext = iLevelSearch;
			iLevelNext.back()++;
			junctionOperationElement(
				aRessyaPropertyCurr,
				contOperationElementCurr,
				iLevelNext,
				pAfterOperation->getOperationNumberMain()/*,
				pCustomizeJikokuhyouContent*/);

			vector<int> iLevelSub = iLevelSearch;
			iLevelSub.push_back(0);
			junctionOperationElement(
				aRessyaPropertyCurr,
				contOperationElementCurr,
				iLevelSub,
				pAfterOperation->getOperationNumberSub()/*,
				NULL*/);
#pragma omp critical(Operation)
			pAfterOperation->trimSuffixOperationNumber();
		}
		else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_NumberChange)
		{
			if (pAfterOperation->getOperationNumberReverse())
			{
				/**
					運番変更(反転)の場合
					(1)strOperationNumberをAssignedにセット、m_OperationNumber3には運用番号が反転して入力される。
					(2)iLevelSearchの末尾に1を加えたものをiLevelNextとし、次の作業の探索を行う、次作業に渡す運用番号はgetOperationNumberで取得、反転済みなのでそのまま渡す。
				*/
#pragma omp critical(Operation)
				pAfterOperation->setOperationNumberAssigned(strOperationNumber);

				vector<int> iLevelNext = iLevelSearch;
				iLevelNext.back()++;
				junctionOperationElement(
					aRessyaPropertyCurr,
					contOperationElementCurr,
					iLevelNext,
					pAfterOperation->getOperationNumber());
			}
			else
			{
				/**
					運番変更の場合
					(1)strOperationNumberをAssignedにセット。
					(2)この作業を終点として、OperationTableListに書き込む
					※これ以降の運番探索は、別に行う。→Ver2.05 ここで行うように変更(取りやめ)
				*/
				vector<tstring> strOperationNumberTemp = strOperationNumber;
				addOperationTableContent(
					aRessyaPropertyCurr,
					strOperationNumberTemp,
					contOperationElementCurr[iOperationIndex].iEkiOrder,
					NULL,
					EBeforeAfterType::BeforeAfterType_OperationNumberChange);
#pragma omp critical(Operation)
				pAfterOperation->setOperationNumberAssigned(strOperationNumberTemp);
			}

			//ここから、運番変更後の処理

//			vector<tstring> strOperationNumber = pAfterOperation->getOperationNumber();
//			if (strOperationNumber.empty())
//			{
//				//tstring strTemp = _T("Tmp");
//				//strTemp += to_tstring(aRessyaPropertyCurr.getRessyaIndex());
//				//strOperationNumber.push_back(strTemp);
//				strOperationNumber.push_back(tstring());
//			}
//			else
//			{
//#pragma omp critical(OperationTableContentBuffer)
//				insertOperationTableContentToBuffer(
//					aRessyaPropertyCurr,
//					strOperationNumber,
//					contOperationElementCurr[iOperationIndex].iEkiOrder,
//					NULL,
//					NULL,
//					EBeforeAfterType::BeforeAfterType_OperationNumberChange);
//			}
//
//			vector<int> iLevelNext = iLevelSearch;
//			iLevelNext.back()++;
//			junctionOperationElement(
//				aRessyaPropertyCurr,
//				contOperationElementCurr,
//				iLevelNext,
//				strOperationNumber,
//				pCustomizeJikokuhyouContent);
		}
		else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_In)
		{
			/**
				入区の場合
				(1)contOperationTableContentBufferから運用番号をキーとして先端側入力済みのOperationTableContentを取得。
				(2)OperationTableContentから検索用後作業を取得してから、この作業と駅Orderを入力。
				(3)運用番号に接尾辞がある場合は削除する。
				(4)検索用後作業を元に、DiaのcontOperationTableContentのどの位置に挿入するかを求める。
					contOperationTableContentが空の場合→そのまま書き込む
					検索用後作業と一致するOperationTableContentがある場合→そのOperationTableContentの次に挿入
					一致しなかったが、OperationTableContentのRessyaPropertyに時刻が設定されている場合(出区・路線外始発)
						→その時刻をもとに、他のOperationTableContentと比較し、時刻順になるように並べる
					(例)
					作業B→作業A(この作業)→作業Cの時間順で、作業B→作業Bから続く作業・・・→作業C→作業Cから続く作業と並んでいた場合、
					作業Cの前に、作業Aを挿入する。
					一致しなくて、時刻が無い場合→この作業が繋がる出区路線外始発が無いので、運用表に含めない(contOperationTableContentに入れない)
				※(1)-(4)はaddOperationTableContentで行う
				(5)strOperationNumberをセットする
				****Ver2.05から****
				(6)入出区連携コードが入力されている場合は、contInOutLinkCodeContentを検索し、当該InOutLinkCodeElementの
					iStatusが"2"の場合は、出区・路線外始発作業に運用番号を引き継ぐ


			*/
			vector<tstring> strOperationNumberTemp = strOperationNumber;
			addOperationTableContent(
				aRessyaPropertyCurr,
				strOperationNumberTemp,
				contOperationElementCurr[iOperationIndex].iEkiOrder,
				pAfterOperation,
				EBeforeAfterType::BeforeAfterType_OutIn);
#pragma omp critical(Operation)
			pAfterOperation->setOperationNumber(strOperationNumberTemp);

			if (!pAfterOperation->getInOutLinkCode().empty())
			{
				map<tstring, InOutLinkCodeContent>* contInOutLinkCodeContent =
					&m_pDedDia->getcontInOutLinkCodeContent();
				auto aInOutLinkCodeItr = contInOutLinkCodeContent->find(pAfterOperation->getInOutLinkCode());
				if (aInOutLinkCodeItr != contInOutLinkCodeContent->end() &&
					aInOutLinkCodeItr->second.iStatus == 2)
				{
					CentDedBeforeOperation* pBeforeOperationNext = aInOutLinkCodeItr->second.BeforeOperation;
					CdDedRessyaProperty aRessyaPropertyNext = aInOutLinkCodeItr->second.contOutRessyaProperty.front();
					aInOutLinkCodeItr->second.strOperationNumber = strOperationNumberTemp;

					vector<OperationElement>& contOperationElementNext = m_contRessyaOperationElement
						[(int)aRessyaPropertyNext.getRessyahoukou()][aRessyaPropertyNext.getRessyaIndex()];
					int iOperationIndexNext = 0;
					for (; iOperationIndexNext < (int)contOperationElementNext.size(); iOperationIndexNext++)
					{
						if (contOperationElementNext[iOperationIndexNext].BeforeOperation == pBeforeOperationNext)
						{
							break;
						}
					}

					/**
						運用番号反転
						運用番号反転設定が有効、前列車と次列車の列車方向が逆、
						の条件を満たした場合、運用番号を反転して、pBeforeOperationNextにつなぐ。
					*/
					if (m_bOperationNumberReverse &&
						aRessyaPropertyCurr.getRessyahoukou() != aRessyaPropertyNext.getRessyahoukou() &&
						strOperationNumberTemp.size() > 1)
					{
						std::reverse(strOperationNumberTemp.begin(), strOperationNumberTemp.end());
					}
					/**
						strOperationNumberTempが空、もしくは空白運番のみの場合、
						strOperationNumberTempを次出区/路線外始発の運用番号で置き換える。
					*/
					if (strOperationNumberTemp.empty() ||
						(strOperationNumberTemp.size() == 1 && strOperationNumberTemp.front() == _T("")))
					{
						strOperationNumberTemp = pBeforeOperationNext->getOperationNumberTemp();
					}

#pragma omp critical(Operation)
					pBeforeOperationNext->setOperationNumberAssignedByLinkCode(strOperationNumberTemp);

					if (pBeforeOperationNext->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
					{
						/**
							この作業が増結編成の場合は、列車の左側に路線外始発相当+↳の表示を追加します。
							まず、この作業が主編成に増結している(増結の繰り返しは可)かどうかの確認を行います。
							☆2 路線外始発増結列車の挿入(入出区連携から)
						*/
						bool bConnectValid = false;
						if (contOperationElementNext[iOperationIndexNext].iLevel.size() > 1)
						{
							/**
								次作業が主編成に増結している(増結の繰り返しは可)かどうかの確認を行います。
							*/
							vector<int> iLevelParent = contOperationElementNext[iOperationIndexNext].iLevel;
							bConnectValid = true;
							while (iLevelParent.size() > 1)
							{
								iLevelParent.pop_back();
								for (int iOperationIndexParent = 0;
									iOperationIndexParent < (int)contOperationElementNext.size(); iOperationIndexParent++)
								{
									if (contOperationElementNext[iOperationIndexParent].iLevel != iLevelParent)
									{
										continue;
									}
									/**
										親作業が、解結(BeforeReleaseかAfterRelease)だった場合は、
										bConnectValidをfalseにして終了。
									*/
									if ((contOperationElementNext[iOperationIndexParent].BeforeOperation != NULL &&
										contOperationElementNext[iOperationIndexParent].BeforeOperation->getBOperation()
										== CentDedBeforeOperation::EBOperation::BOperation_Release) ||
										(contOperationElementNext[iOperationIndexParent].AfterOperation != NULL &&
											contOperationElementNext[iOperationIndexParent].AfterOperation->getAOperation()
											== CentDedAfterOperation::EAOperation::AOperation_Release))
									{
										bConnectValid = false;
										break;
									}
								}
							}
						}
						if (bConnectValid)
						{
#pragma omp critical(contOuterConnectInsertList)
							{
								const CentDedRessya* pCentDedRessya =
									m_pDedDia->getCentDedRessyaCont(aRessyaPropertyNext.getRessyahoukou())->getMuPtr()
									->get(aRessyaPropertyNext.getRessyaIndex());
								const CentDedEkiJikoku aCentDedEkiJikoku =
									pCentDedRessya->getCentDedEkiJikoku(contOperationElementNext[iOperationIndexNext].iEkiOrder);
								CustomizeJikokuhyouContent aCustomizeJikokuhyouContent(pCentDedRessya,true);
								aCustomizeJikokuhyouContent.iConnectEkiOrder = contOperationElementNext[iOperationIndexNext].iEkiOrder;
								aCustomizeJikokuhyouContent.ChakuJikoku = pBeforeOperationNext->getChakuJikoku();
								if (aCustomizeJikokuhyouContent.ChakuJikoku.isNull())
								{
									aCustomizeJikokuhyouContent.ChakuJikoku = aCentDedEkiJikoku.getHatsujikoku();
								}
								aCustomizeJikokuhyouContent.OuterShihatsuJikoku = pBeforeOperationNext->getOuterShihatsuJikoku();
								aCustomizeJikokuhyouContent.iSihatsuEkiOrder = contOperationElementNext[iOperationIndexNext].iEkiOrder;
								aCustomizeJikokuhyouContent.iOuterShihatsuEkiIndex = pBeforeOperationNext->getOuterShihatsuekiIndex();;
								aCustomizeJikokuhyouContent.ePrevEkiatsukai = aCentDedEkiJikoku.getEkiatsukai();
								aCustomizeJikokuhyouContent.iPrevRessyaTrackIndex = aCentDedEkiJikoku.getRessyaTrackIndex();
								aCustomizeJikokuhyouContent.strPrevOperationNumber = strOperationNumberTemp;
								aCustomizeJikokuhyouContent.eEBeforeType = EBeforeAfterType::BeforeAfterType_Outer;

								m_contOuterConnectInsertList[aRessyaPropertyNext.getRessyahoukou()][contOperationElementNext[iOperationIndexNext].iEkiOrder].
									insert(make_pair(aRessyaPropertyNext.getRessyaIndex(), aCustomizeJikokuhyouContent));
							}
							//実処理はcompleteCustomizeJikokuhyouContentで行うのでコメントアウト
//#pragma omp critical(CustomizeRessyaIndex)
//							{
//								vector<CustomizeJikokuhyouContent>& contCustomizeJikokuhyouContent =
//									m_pDedDia->getcontCustomizeRessyaIndex(aRessyaPropertyNext.getRessyahoukou());
//								for (int CustomizeJikokuhyouContentIndex = 0; CustomizeJikokuhyouContentIndex < (int)contCustomizeJikokuhyouContent.size(); CustomizeJikokuhyouContentIndex++)
//								{
//									if (contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].iRessyaIndexCont.empty())
//									{
//										continue;
//									}
//									if (contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].iRessyaIndexCont.front() == aRessyaPropertyNext.getRessyaIndex())
//									{
//										const CentDedRessya* pCentDedRessya =
//											m_pDedDia->getCentDedRessyaCont(aRessyaPropertyNext.getRessyahoukou())->getMuPtr()
//											->get(aRessyaPropertyNext.getRessyaIndex());
//										const CentDedEkiJikoku aCentDedEkiJikoku =
//											pCentDedRessya->getCentDedEkiJikoku(contOperationElementNext[iOperationIndexNext].iEkiOrder);
//										CustomizeJikokuhyouContent aCustomizeJikokuhyouContent(pCentDedRessya);
//										aCustomizeJikokuhyouContent.iConnectEkiOrder = contOperationElementNext[iOperationIndexNext].iEkiOrder;
//										aCustomizeJikokuhyouContent.ChakuJikoku = pBeforeOperationNext->getChakuJikoku();
//										if (aCustomizeJikokuhyouContent.ChakuJikoku.isNull())
//										{
//											aCustomizeJikokuhyouContent.ChakuJikoku = aCentDedEkiJikoku.getHatsujikoku();
//										}
//										aCustomizeJikokuhyouContent.OuterShihatsuJikoku = pBeforeOperationNext->getOuterShihatsuJikoku();
//										aCustomizeJikokuhyouContent.iSihatsuEkiOrder = contOperationElementNext[iOperationIndexNext].iEkiOrder;
//										aCustomizeJikokuhyouContent.iOuterShihatsuEkiIndex = pBeforeOperationNext->getOuterShihatsuekiIndex();;
//										aCustomizeJikokuhyouContent.eEkiatsukai = aCentDedEkiJikoku.getEkiatsukai();
//										aCustomizeJikokuhyouContent.iRessyaTrackIndex = aCentDedEkiJikoku.getRessyaTrackIndex();
//										aCustomizeJikokuhyouContent.strOperationNumber = strOperationNumberTemp;
//
//										contCustomizeJikokuhyouContent.insert(contCustomizeJikokuhyouContent.begin() + CustomizeJikokuhyouContentIndex,
//											aCustomizeJikokuhyouContent);
//										break;
//									}
//								}
//							}
						}
					}

					/**
						insertOperationTableContentToBufferには、pAfterOperation(検索用後作業)を渡します。
						addで運用表を組み立てる際に、pAfterOperationの後に入れることで、順番が定まります。
					*/
#pragma omp critical(OperationTableContentBuffer)
					insertOperationTableContentToBuffer(
						aRessyaPropertyNext,
						strOperationNumberTemp,
						contOperationElementNext[iOperationIndexNext].iEkiOrder,
						pBeforeOperationNext,
						pAfterOperation,
						EBeforeAfterType::BeforeAfterType_OutIn);

				
					vector<int> iLevelNext = contOperationElementNext[iOperationIndexNext].iLevel;
					iLevelNext.back()++;
					junctionOperationElement(
						aRessyaPropertyNext,
						contOperationElementNext,
						iLevelNext,
						strOperationNumberTemp);

					//if (contOperationElementNext[iOperationIndex].iLevel.size() == 1)
					//{
					//	CustomizeJikokuhyouContent aCustomizeJikokuhyouContent(aRessyaPropertyNext.getRessyaIndex());

					//	junctionOperationElement(
					//		aRessyaPropertyNext,
					//		contOperationElementNext,
					//		iLevelNext,
					//		strOperationNumberTemp,
					//		&aCustomizeJikokuhyouContent);
					//}
					//else
					//{
					//	junctionOperationElement(
					//		aRessyaPropertyNext,
					//		contOperationElementNext,
					//		iLevelNext,
					//		strOperationNumberTemp,
					//		NULL);
					//}
				}
			}
		}
		else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
		{
			/**
				路線外終着の場合
				(1)contOperationTableContentBufferから運用番号をキーとして先端側入力済みのOperationTableContentを取得。
				(2)OperationTableContentから検索用後作業を取得してから、この作業と駅Order、路線外終着駅indexと路線外終着駅着時刻を入力。
				(3)運用番号に接尾辞がある場合は削除する。
				(4)検索用後作業を元に、DiaのcontOperationTableContentのどの位置に挿入するかを求める。
					contOperationTableContentが空の場合→そのまま書き込む
					検索用後作業と一致するOperationTableContentがある場合→そのOperationTableContentの次に挿入
					一致しなかったが、OperationTableContentのRessyaPropertyに時刻が設定されている場合(出区・路線外始発)
						→その時刻をもとに、他のOperationTableContentと比較し、時刻順になるように並べる
					(例)
					作業B→作業A(この作業)→作業Cの時間順で、作業B→作業Bから続く作業・・・→作業C→作業Cから続く作業と並んでいた場合、
					作業Cの前に、作業Aを挿入する。
					一致しなくて、時刻が無い場合→この作業が繋がる出区路線外始発が無いので、運用表に含めない(contOperationTableContentに入れない)
				※(1)-(4)はaddOperationTableContentで行う
				(5)strOperationNumberをセットして終了
			*/
			vector<tstring> strOperationNumberTemp = strOperationNumber;
			addOperationTableContent(
				aRessyaPropertyCurr,
				strOperationNumberTemp,
				contOperationElementCurr[iOperationIndex].iEkiOrder,
				pAfterOperation,
				EBeforeAfterType::BeforeAfterType_Outer);
#pragma omp critical(Operation)
			pAfterOperation->setOperationNumber(strOperationNumberTemp);

			if (iLevelSearch.size() > 1)
			{
				/**
					この作業が主編成から解結されている(解結の繰り返しは可)かどうかを確認します。
					☆3 路線外終着解結編成の挿入
				*/
				vector<int> iLevelParent = iLevelSearch;
				bool bReleaseValid = true;
				while (iLevelParent.size() > 1)
				{
					iLevelParent.pop_back();
					for (int iOperationIndexParent = 0;
						iOperationIndexParent < (int)contOperationElementCurr.size(); iOperationIndexParent++)
					{
						if (contOperationElementCurr[iOperationIndexParent].iLevel != iLevelParent)
						{
							continue;
						}
						/**
							親作業が、増結(BeforeConnectかAfterConnect)だった場合は、
							bReleaseValidをfalseにして終了。
						*/
						if ((contOperationElementCurr[iOperationIndexParent].BeforeOperation != NULL &&
							contOperationElementCurr[iOperationIndexParent].BeforeOperation->getBOperation()
							== CentDedBeforeOperation::EBOperation::BOperation_Connect) ||
							(contOperationElementCurr[iOperationIndexParent].AfterOperation != NULL &&
								contOperationElementCurr[iOperationIndexParent].AfterOperation->getAOperation()
								== CentDedAfterOperation::EAOperation::AOperation_Connect))
						{
							bReleaseValid = false;
							break;
						}
					}
				}
				if (bReleaseValid)
				{
#pragma omp critical(contOuterReleaseInsertList)
					{
						const CentDedRessya* pCentDedRessya =
							m_pDedDia->getCentDedRessyaCont(aRessyaPropertyCurr.getRessyahoukou())->getMuPtr()
							->get(aRessyaPropertyCurr.getRessyaIndex());
						const CentDedEkiJikoku aCentDedEkiJikoku =
							pCentDedRessya->getCentDedEkiJikoku(contOperationElementCurr[iOperationIndex].iEkiOrder);
						CustomizeJikokuhyouContent aCustomizeJikokuhyouContent(pCentDedRessya,false);
						aCustomizeJikokuhyouContent.iReleaseEkiOrder = contOperationElementCurr[iOperationIndex].iEkiOrder;
						aCustomizeJikokuhyouContent.HatsuJikoku = pAfterOperation->getHatsuJikoku();
						if (aCustomizeJikokuhyouContent.HatsuJikoku.isNull())
						{
							aCustomizeJikokuhyouContent.HatsuJikoku = aCentDedEkiJikoku.getChakujikoku();
						}
						aCustomizeJikokuhyouContent.OuterShuchakuJikoku = pAfterOperation->getOuterShuchakuJikoku();
						aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder = contOperationElementCurr[iOperationIndex].iEkiOrder;
						aCustomizeJikokuhyouContent.iOuterShuchakuEkiIndex = pAfterOperation->getOuterShuchakuekiIndex();
						aCustomizeJikokuhyouContent.eEkiatsukai = aCentDedEkiJikoku.getEkiatsukai();
						aCustomizeJikokuhyouContent.iRessyaTrackIndex = aCentDedEkiJikoku.getRessyaTrackIndex();
						aCustomizeJikokuhyouContent.strOperationNumber = strOperationNumberTemp;
						aCustomizeJikokuhyouContent.eEAfterType = EBeforeAfterType::BeforeAfterType_Outer;

						m_contOuterReleaseInsertList[aRessyaPropertyCurr.getRessyahoukou()][contOperationElementCurr[iOperationIndex].iEkiOrder].
							insert(make_pair(aRessyaPropertyCurr.getRessyaIndex(), aCustomizeJikokuhyouContent));
					}
					//実処理はcompleteCustomizeJikokuhyouContentで行うのでコメントアウト
//#pragma omp critical(CustomizeRessyaIndex)
//					{
//						vector<CustomizeJikokuhyouContent>& contCustomizeJikokuhyouContent =
//							m_pDedDia->getcontCustomizeRessyaIndex(aRessyaPropertyCurr.getRessyahoukou());
//						for (int CustomizeJikokuhyouContentIndex = 0; CustomizeJikokuhyouContentIndex < (int)contCustomizeJikokuhyouContent.size(); CustomizeJikokuhyouContentIndex++)
//						{
//							if (contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].iRessyaIndexCont.empty())
//							{
//								continue;
//							}
//							if (contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].iRessyaIndexCont.back() == aRessyaPropertyCurr.getRessyaIndex())
//							{
//								const CentDedRessya* pCentDedRessya =
//									m_pDedDia->getCentDedRessyaCont(aRessyaPropertyCurr.getRessyahoukou())->getMuPtr()
//									->get(aRessyaPropertyCurr.getRessyaIndex());
//								const CentDedEkiJikoku aCentDedEkiJikoku =
//									pCentDedRessya->getCentDedEkiJikoku(contOperationElementCurr[iOperationIndex].iEkiOrder);
//								CustomizeJikokuhyouContent aCustomizeJikokuhyouContent(pCentDedRessya);
//								aCustomizeJikokuhyouContent.iReleaseEkiOrder = contOperationElementCurr[iOperationIndex].iEkiOrder;
//								aCustomizeJikokuhyouContent.HatsuJikoku = pAfterOperation->getHatsuJikoku();
//								if (aCustomizeJikokuhyouContent.HatsuJikoku.isNull())
//								{
//									aCustomizeJikokuhyouContent.HatsuJikoku = aCentDedEkiJikoku.getChakujikoku();
//								}
//								aCustomizeJikokuhyouContent.OuterShuchakuJikoku = pAfterOperation->getOuterShuchakuJikoku();
//								aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder = contOperationElementCurr[iOperationIndex].iEkiOrder;
//								aCustomizeJikokuhyouContent.iOuterShuchakuEkiIndex = pAfterOperation->getOuterShuchakuekiIndex();
//								aCustomizeJikokuhyouContent.eEkiatsukai = aCentDedEkiJikoku.getEkiatsukai();
//								aCustomizeJikokuhyouContent.iRessyaTrackIndex = aCentDedEkiJikoku.getRessyaTrackIndex();
//								aCustomizeJikokuhyouContent.strOperationNumber = strOperationNumberTemp;
//
//								contCustomizeJikokuhyouContent.insert(contCustomizeJikokuhyouContent.begin() + CustomizeJikokuhyouContentIndex + 1,
//									aCustomizeJikokuhyouContent);
//								break;
//							}
//						}
//					}
				}
			}

			if (!pAfterOperation->getInOutLinkCode().empty())
			{
				map<tstring, InOutLinkCodeContent>* contInOutLinkCodeContent =
					&m_pDedDia->getcontInOutLinkCodeContent();
				auto aInOutLinkCodeItr = contInOutLinkCodeContent->find(pAfterOperation->getInOutLinkCode());
				if (aInOutLinkCodeItr != contInOutLinkCodeContent->end() &&
					aInOutLinkCodeItr->second.iStatus == 2)
				{
					CentDedBeforeOperation* pBeforeOperationNext = aInOutLinkCodeItr->second.BeforeOperation;
					CdDedRessyaProperty aRessyaPropertyNext = aInOutLinkCodeItr->second.contOutRessyaProperty.front();
					aInOutLinkCodeItr->second.strOperationNumber = strOperationNumberTemp;

					vector<OperationElement>& contOperationElementNext = m_contRessyaOperationElement
						[(int)aRessyaPropertyNext.getRessyahoukou()][aRessyaPropertyNext.getRessyaIndex()];
					int iOperationIndexNext = 0;
					for (; iOperationIndexNext < (int)contOperationElementNext.size(); iOperationIndexNext++)
					{
						if (contOperationElementNext[iOperationIndexNext].BeforeOperation == pBeforeOperationNext)
						{
							break;
						}
					}

					/**
						運用番号反転
						運用番号反転設定が有効、前列車と次列車の列車方向が逆、
						の条件を満たした場合、運用番号を反転して、pBeforeOperationNextにつなぐ。
					*/
					if (m_bOperationNumberReverse &&
						aRessyaPropertyCurr.getRessyahoukou() != aRessyaPropertyNext.getRessyahoukou() &&
						strOperationNumberTemp.size() > 1)
					{
						std::reverse(strOperationNumberTemp.begin(), strOperationNumberTemp.end());
					}
					/**
						strOperationNumberTempが空、もしくは空白運番のみの場合、
						strOperationNumberTempを次出区/路線外始発の運用番号で置き換える。
					*/
					if (strOperationNumberTemp.empty() ||
						(strOperationNumberTemp.size() == 1 && strOperationNumberTemp.front() == _T("")))
					{
						strOperationNumberTemp = pBeforeOperationNext->getOperationNumberTemp();
					}

#pragma omp critical(Operation)
					pBeforeOperationNext->setOperationNumberAssignedByLinkCode(strOperationNumberTemp);

					if (pBeforeOperationNext->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
					{
						/**
							この作業が増結編成の場合は、列車の左側に路線外始発相当+↳の表示を追加します。
							まず、この作業が主編成に増結している(増結の繰り返しは可)かどうかの確認を行います。
							☆4 路線外始発増結列車の挿入(入出区連携から)
						*/
						bool bConnectValid = false;
						if (contOperationElementNext[iOperationIndexNext].iLevel.size() > 1)
						{
							/**
								次作業が主編成に増結している(増結の繰り返しは可)かどうかの確認を行います。
							*/
							vector<int> iLevelParent = contOperationElementNext[iOperationIndexNext].iLevel;
							bConnectValid = true;
							while (iLevelParent.size() > 1)
							{
								iLevelParent.pop_back();
								for (int iOperationIndexParent = 0;
									iOperationIndexParent < (int)contOperationElementNext.size(); iOperationIndexParent++)
								{
									if (contOperationElementNext[iOperationIndexParent].iLevel != iLevelParent)
									{
										continue;
									}
									/**
										親作業が、解結(BeforeReleaseかAfterRelease)だった場合は、
										bConnectValidをfalseにして終了。
									*/
									if ((contOperationElementNext[iOperationIndexParent].BeforeOperation != NULL &&
										contOperationElementNext[iOperationIndexParent].BeforeOperation->getBOperation()
										== CentDedBeforeOperation::EBOperation::BOperation_Release) ||
										(contOperationElementNext[iOperationIndexParent].AfterOperation != NULL &&
											contOperationElementNext[iOperationIndexParent].AfterOperation->getAOperation()
											== CentDedAfterOperation::EAOperation::AOperation_Release))
									{
										bConnectValid = false;
										break;
									}
								}
							}
						}
						if (bConnectValid)
						{
#pragma omp critical(contOuterConnectInsertList)
							{
								const CentDedRessya* pCentDedRessya =
									m_pDedDia->getCentDedRessyaCont(aRessyaPropertyNext.getRessyahoukou())->getMuPtr()
									->get(aRessyaPropertyNext.getRessyaIndex());
								const CentDedEkiJikoku aCentDedEkiJikoku =
									pCentDedRessya->getCentDedEkiJikoku(contOperationElementNext[iOperationIndexNext].iEkiOrder);
								CustomizeJikokuhyouContent aCustomizeJikokuhyouContent(pCentDedRessya,true);
								aCustomizeJikokuhyouContent.iConnectEkiOrder = contOperationElementNext[iOperationIndexNext].iEkiOrder;
								aCustomizeJikokuhyouContent.ChakuJikoku = pBeforeOperationNext->getChakuJikoku();
								if (aCustomizeJikokuhyouContent.ChakuJikoku.isNull())
								{
									aCustomizeJikokuhyouContent.ChakuJikoku = aCentDedEkiJikoku.getHatsujikoku();
								}
								aCustomizeJikokuhyouContent.OuterShihatsuJikoku = pBeforeOperationNext->getOuterShihatsuJikoku();
								aCustomizeJikokuhyouContent.iSihatsuEkiOrder = contOperationElementNext[iOperationIndexNext].iEkiOrder;
								aCustomizeJikokuhyouContent.iOuterShihatsuEkiIndex = pBeforeOperationNext->getOuterShihatsuekiIndex();;
								aCustomizeJikokuhyouContent.ePrevEkiatsukai = aCentDedEkiJikoku.getEkiatsukai();
								aCustomizeJikokuhyouContent.iPrevRessyaTrackIndex = aCentDedEkiJikoku.getRessyaTrackIndex();
								aCustomizeJikokuhyouContent.strPrevOperationNumber = strOperationNumberTemp;
								aCustomizeJikokuhyouContent.eEBeforeType = EBeforeAfterType::BeforeAfterType_Outer;

								m_contOuterConnectInsertList[aRessyaPropertyNext.getRessyahoukou()][contOperationElementNext[iOperationIndexNext].iEkiOrder].
									insert(make_pair(aRessyaPropertyNext.getRessyaIndex(), aCustomizeJikokuhyouContent));
							}
							//実処理はcompleteCustomizeJikokuhyouContentで行うのでコメントアウト
//#pragma omp critical(CustomizeRessyaIndex)
//							{
//								vector<CustomizeJikokuhyouContent>& contCustomizeJikokuhyouContent =
//									m_pDedDia->getcontCustomizeRessyaIndex(aRessyaPropertyNext.getRessyahoukou());
//								for (int CustomizeJikokuhyouContentIndex = 0; CustomizeJikokuhyouContentIndex < (int)contCustomizeJikokuhyouContent.size(); CustomizeJikokuhyouContentIndex++)
//								{
//									if (contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].iRessyaIndexCont.empty())
//									{
//										continue;
//									}
//									if (contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].iRessyaIndexCont.front() == aRessyaPropertyNext.getRessyaIndex())
//									{
//										const CentDedRessya* pCentDedRessya =
//											m_pDedDia->getCentDedRessyaCont(aRessyaPropertyNext.getRessyahoukou())->getMuPtr()
//											->get(aRessyaPropertyNext.getRessyaIndex());
//										const CentDedEkiJikoku aCentDedEkiJikoku =
//											pCentDedRessya->getCentDedEkiJikoku(contOperationElementNext[iOperationIndexNext].iEkiOrder);
//										CustomizeJikokuhyouContent aCustomizeJikokuhyouContent(pCentDedRessya);
//										aCustomizeJikokuhyouContent.iConnectEkiOrder = contOperationElementNext[iOperationIndexNext].iEkiOrder;
//										aCustomizeJikokuhyouContent.ChakuJikoku = pBeforeOperationNext->getChakuJikoku();
//										if (aCustomizeJikokuhyouContent.ChakuJikoku.isNull())
//										{
//											aCustomizeJikokuhyouContent.ChakuJikoku = aCentDedEkiJikoku.getHatsujikoku();
//										}
//										aCustomizeJikokuhyouContent.OuterShihatsuJikoku = pBeforeOperationNext->getOuterShihatsuJikoku();
//										aCustomizeJikokuhyouContent.iSihatsuEkiOrder = contOperationElementNext[iOperationIndexNext].iEkiOrder;
//										aCustomizeJikokuhyouContent.iOuterShihatsuEkiIndex = pBeforeOperationNext->getOuterShihatsuekiIndex();;
//										aCustomizeJikokuhyouContent.eEkiatsukai = aCentDedEkiJikoku.getEkiatsukai();
//										aCustomizeJikokuhyouContent.iRessyaTrackIndex = aCentDedEkiJikoku.getRessyaTrackIndex();
//										aCustomizeJikokuhyouContent.strOperationNumber = strOperationNumberTemp;
//
//										contCustomizeJikokuhyouContent.insert(contCustomizeJikokuhyouContent.begin() + CustomizeJikokuhyouContentIndex,
//											aCustomizeJikokuhyouContent);
//										break;
//									}
//								}
//							}
						}
					}

					/**
						insertOperationTableContentToBufferには、pAfterOperation(検索用後作業)を渡します。
						addで運用表を組み立てる際に、pAfterOperationの後に入れることで、順番が定まります。
					*/
#pragma omp critical(OperationTableContentBuffer)
					insertOperationTableContentToBuffer(
						aRessyaPropertyNext,
						strOperationNumberTemp,
						contOperationElementNext[iOperationIndexNext].iEkiOrder,
						pBeforeOperationNext,
						pAfterOperation,
						EBeforeAfterType::BeforeAfterType_Outer);

					vector<int> iLevelNext = contOperationElementNext[iOperationIndexNext].iLevel;
					iLevelNext.back()++;
					junctionOperationElement(
						aRessyaPropertyNext,
						contOperationElementNext,
						iLevelNext,
						strOperationNumberTemp);
					//if (contOperationElementNext[iOperationIndex].iLevel.size() == 1)
					//{
					//	CustomizeJikokuhyouContent aCustomizeJikokuhyouContent(aRessyaPropertyNext.getRessyaIndex());

					//	junctionOperationElement(
					//		aRessyaPropertyNext,
					//		contOperationElementNext,
					//		iLevelNext,
					//		strOperationNumberTemp,
					//		&aCustomizeJikokuhyouContent);
					//}
					//else
					//{
					//	junctionOperationElement(
					//		aRessyaPropertyNext,
					//		contOperationElementNext,
					//		iLevelNext,
					//		strOperationNumberTemp,
					//		NULL);
					//}
				}
			}
		}
		else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Junction)
		{
			/**
				次列車接続の場合
				(1)contOperationTableContentBufferから運用番号をキーとして先端側入力済みのOperationTableContentを取得。
				(2)OperationTableContentから検索用後作業を取得してから、この作業と駅Orderを入力。
				(3)運用番号に接尾辞がある場合は削除する。
				(4)検索用後作業と列車プロパティの時刻を元に、DiaのcontOperationTableContentのどの位置に挿入するかを求める。
					検索用後作業がある場合(前列車接続)
					検索用後作業と一致するOperationTableContentを探し、そのOperationTableContentの次に挿入
					列車プロパティの時刻がある場合(出区・路線外始発)
					contOperationTableContentが空の場合→そのまま書き込む
					contOperationTableContentに他の要素がある場合→他の要素のうち、時刻が設定されているものと比較し、時刻順になるように並べる
					(例)
					ContentB→ContentA(このContent)→ContentCの時間順で、ContentB→ContentBから続くContent・・・→ContentC→ContentCから続くContentと並んでいた場合、
					ContentCの直前に、ContentAを挿入する。
					一致しなくて、時刻が無い場合→この作業が繋がる出区路線外始発が無いので、運用表に含めない(contOperationTableContentに入れない)
				※(1)-(4)はaddOperationTableContentで行う
				(5)strOperationNumberをセット

				SearchRessyaElementで、m_contRessyaExistから次の列車を検索する
				次列車の、前列車接続作業に、EkiOrderOfPrevSyuuchakuEki(前列車の有効終着駅を、次列車の方向に合わせたもの)
					iPrevRessyahoukou,JunctionJikoku,PrevRessyahoukouNoDisplay,setJunctionJikokuNoDisplay(ダイヤグラムで列車接続を描写するときに使用)
					をセットする

				この作業のiLevel.size()が1のとき(この列車の主編成の末端作業に相当するとき)は
				種別変更の確認を行う。
				種別変更が有効になる条件は、
					(1)この列車の種別変更が有効
					(2)この作業と次作業がともに主編成作業である
					(3)この列車と次列車の方向が同じ
					(4)この列車のValidSyuchakuEki<=次列車のValidSihatsuEki
				種別変更が有効な場合は、
					(1)contCustomizeRessyaIndexからNextの列車Indexが含まれた列を探し、
						Prevの列の末尾に組み込む。

				また、この作業のiLevel.size()が2以上の時は、解結の判定を行う。
				size()が2以上でも、必ず解結ではない
				(具体的には主編成の増結作業の前作業内に、解結がある場合は、主編成から解結したとは言えないから。)
				親作業をチェックし、それが全て解結なら、この作業は主編成から解決したと判断できる。
				解結が有効になる条件は
					(1)この列車と次列車の方向が同じ
					(2)この作業が主編成から解結されている(解結の繰り返しは可)
					(3)この作業のiEkiOrder<=次作業のiEkiOrder(ValidSihatsuEki)
					(4)次作業が主編成に相当する
					(5)次作業の「分割先列車にしない」が無効
				解結が有効な場合は、
					(1)次作業のReleaseEkiOrderに、この作業があるEkiOrderを書き込む
					(2)contCustomizeRessyaIndexのNextの列車を、Prevの直後に移動する(ここの実装は今後行う)


				また、次作業のiLevel.size()が2以上の時は、増結の判定を行う。
				size()が2以上でも、必ず増結ではない
				(具体的には主編成の解結作業の後作業内に、増結がある場合は、主編成に増結したとは言えないから。)
				親作業をチェックし、それが全て増結なら、この作業は主編成に増結すると判断できる。
				増結が有効になる条件は
					(1)この列車と次列車の方向が同じ
					(2)次作業が主編成に増結している(増結の繰り返しは可)
					(3)この作業のiEkiOrder(iValidSyuchakuEkiOrder)<=次作業のiEkiOrder
					(4)この作業が主編成に相当する
					(5)この作業の「併合元列車にしない」が無効
				増結が有効な場合は、
					(1)この作業のConnectEkiOrderに、次作業があるEkiOrderを書き込む
					(2)contCustomizeRessyaIndexのNextの列車を、Prevの直後に移動する(ここの実装は今後行う

				次に、次列車の先端作業BeforeNoneからの次作業探索へ進む。
				contOperationTableContentBuffer(次列車)へ、前作業+検索用後作業を収める。
			*/
			vector<tstring> strOperationNumberTemp = strOperationNumber;

			CdDedJikoku aTerminalJikoku;
			RessyaElement aRessyaElementNext =
				SearchRessyaElement(
					&m_contRessyaExist[contOperationElementCurr[iOperationIndex].iEkiIndexofContExist][contOperationElementCurr[iOperationIndex].iRessyaTrackIndex],
					pAfterOperation,
					aTerminalJikoku);
			CentDedBeforeOperation* pBeforeOperationNext = aRessyaElementNext.BeforeOperation;
			if (pBeforeOperationNext == NULL)
			{
				/**
					Ver2.05 addOperationTableContentの実行を、SearchRessyaElement実行後(次列車が存在するかどうかを確認後)に変更
						(eAfterTypeを確定させるため)
						pBeforeOperationNext == NULL(次列車無し)の場合は、eAfterTypeは常にUnrelated
				*/
				addOperationTableContent(
					aRessyaPropertyCurr,
					strOperationNumberTemp,
					contOperationElementCurr[iOperationIndex].iEkiOrder,
					pAfterOperation,
					EBeforeAfterType::BeforeAfterType_Unrelated);
				return;
			}

			/**
				Ver2.05 addOperationTableContentの実行を、SearchRessyaElement実行後(次列車が存在するかどうかを確認後)に変更
					(eAfterTypeを確定させるため)
					pBeforeOperationNext != NULL(次列車有り)の場合、pAfterOperationの次列車接続タイプがeAfterTypeとなる。
			*/
			EBeforeAfterType eBeforeAfterType = EBeforeAfterType::BeforeAfterType_Unrelated;
			if (pAfterOperation->getNextJunctionType() == 1)
			{
				eBeforeAfterType = EBeforeAfterType::BeforeAfterType_ClassChange;
			}
			else if (pAfterOperation->getNextJunctionType() == 2)
			{
				eBeforeAfterType = EBeforeAfterType::BeforeAfterType_PropertyChange;
			}
			else if (pAfterOperation->getNextJunctionType() == 3)
			{
				eBeforeAfterType = EBeforeAfterType::BeforeAfterType_PropertySame;
			}

			if (m_bHiddenExist && eBeforeAfterType != EBeforeAfterType::BeforeAfterType_Unrelated)
			{
				const CentDedRessya* pRessya =
					m_pDedDia->getCentDedRessyaCont(aRessyaPropertyCurr.getRessyahoukou())->getMuPtr()
					->get(aRessyaPropertyCurr.getRessyaIndex());
				const CentDedRessya* pRessyaNext =
					m_pDedDia->getCentDedRessyaCont(aRessyaElementNext.sRessyaProperty.getRessyahoukou())->getMuPtr()
					->get(aRessyaElementNext.sRessyaProperty.getRessyaIndex());
				if (m_contHidden[pRessya->getRessyasyubetsuIndex()] != m_contHidden[pRessyaNext->getRessyasyubetsuIndex()])
				{
					eBeforeAfterType = EBeforeAfterType::BeforeAfterType_Unrelated;
				}
			}

			addOperationTableContent(
				aRessyaPropertyCurr,
				strOperationNumberTemp,
				contOperationElementCurr[iOperationIndex].iEkiOrder,
				pAfterOperation,
				eBeforeAfterType);
#pragma omp critical(Operation)
			pAfterOperation->setOperationNumber(strOperationNumberTemp);



			vector<OperationElement>& contOperationElementNext = m_contRessyaOperationElement
				[(int)aRessyaElementNext.sRessyaProperty.getRessyahoukou()][aRessyaElementNext.sRessyaProperty.getRessyaIndex()];
			
			int iOperationIndexNext = -1;
			for (int idxoi = 0;
				idxoi < (int)contOperationElementNext.size(); idxoi++)
			{
				if (contOperationElementNext[idxoi].BeforeOperation == pBeforeOperationNext &&
					pBeforeOperationNext->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Junction)
				{
					iOperationIndexNext = idxoi;
					break;
				}
			}
			if (iOperationIndexNext == -1)
			{
				return;
			}
			const CentDedRessya* pRessya =
				m_pDedDia->getCentDedRessyaCont(aRessyaPropertyCurr.getRessyahoukou())->getMuPtr()
				->get(aRessyaPropertyCurr.getRessyaIndex());
			//const CentDedRessya* pRessyaNext =
			//	m_pDedDia->getCentDedRessyaCont(aRessyaListNext.sRessyaProperty.getRessyahoukou())->getMuPtr()
			//	->get(aRessyaListNext.sRessyaProperty.getRessyaIndex());

#pragma omp critical(Operation)
			pAfterOperation->setJunctionSucceed(true);

			/**
				EkiOrderOfPrevSyuuchakuEki
				前列車の有効終着駅Orderを、次列車の方向に合わせたものです。
				ダイヤグラム描写において、反転駅設定の確認に用います。
			*/
			int iValidSyuuchakuEki = pRessya->getValidSyuuchakuEki();
			int iEkiIndexOfPrevSyuuchakuEki = 
				pRessya->EkiIndexOfEkiOrder(iValidSyuuchakuEki);
#pragma omp critical(Operation)
			pBeforeOperationNext->setEkiOrderOfPrevSyuuchakuEki(
				m_pDedDia->getCentDedRessyaCont(aRessyaElementNext.sRessyaProperty.getRessyahoukou())
				->EkiOrderOfEkiIndex(iEkiIndexOfPrevSyuuchakuEki));
							
			/**
				iPrevRessyahoukou,JunctionJikoku
				在線表表示駅でダイヤグラムを描写する際に用います。
				前列車と次列車が繋がる番線の横線は、
				次列車の責任で描写を行いますが、
				描写の開始X座標(JunctionJikoku)および、左端の形状(iPrevRessyahoukou)をここで求めておきます。
				iPrevRessyahoukouは、前列車の列車方向に基づいて求められているので、
				前列車と次列車の列車方向が異なる場合は、符号を反転する必要があります。
				iPrevRessyahoukouが+1または-1の場合は、反転駅設定により向きが変わる場合があります。
				前列車が、解結編成の場合は、iPrevRessyahoukouは0になります。
			*/
#pragma omp critical(Operation)
			pBeforeOperationNext->setJunctionJikoku(pAfterOperation->getJunctionJikoku());
			int iPrevRessyahoukou = pAfterOperation->getPrevRessyahoukou();
			if (aRessyaPropertyCurr.getRessyahoukou() != aRessyaElementNext.sRessyaProperty.getRessyahoukou())
			{
				iPrevRessyahoukou *= -1;
			}
#pragma omp critical(Operation)
			pBeforeOperationNext->setPrevRessyahoukou(iPrevRessyahoukou);

			/**
				PrevRessyahoukouNoDisplay
				在線表非表示駅における、列車を接続する円弧は、
				接続する両列車が、主編成の場合(増結編成・解結編成でない場合)のみ行います。
				主編成は、iLevelが1であるかどうかで判定できます。
				また、前列車と後列車が種別変更・列車情報変更・同一列車扱いの場合、円弧の描写は行いません。
				実際の円弧の向き・形状は、反転駅設定により変化します。
			*/
			if (contOperationElementCurr[iOperationIndex].iLevel.size() == 1 &&
				contOperationElementNext[iOperationIndexNext].iLevel.size() == 1 &&
				eBeforeAfterType == EBeforeAfterType::BeforeAfterType_Unrelated)
			{
				if (aRessyaPropertyCurr.getRessyahoukou() == aRessyaElementNext.sRessyaProperty.getRessyahoukou())
				{
#pragma omp critical(Operation)
					pBeforeOperationNext->setPrevRessyahoukouNoDisplay(-1);
				}
				else
				{
#pragma omp critical(Operation)
					pBeforeOperationNext->setPrevRessyahoukouNoDisplay(+1);
				}
				const CentDedEkiJikoku* pEkiJikoku = pRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iValidSyuuchakuEki);
#pragma omp critical(Operation)
				pBeforeOperationNext->setJunctionJikokuNoDisplay(pEkiJikoku->getChakujikoku());
			}

			/**
				種別変更・列車情報変更・同一列車扱いの処理
				iRessyaType
				0:主編成
				1:解結・増結編成
				2:その他
			*/
			int iPrevRessyaType = 2;
			if (contOperationElementCurr[iOperationIndex].iLevel.size() == 1)
			{
				iPrevRessyaType = 0;
			}
			else
			{
				/**
					この作業が主編成から解結されている(解結の繰り返しは可)かどうかを確認します。
				*/
				vector<int> iLevelParent = contOperationElementCurr[iOperationIndex].iLevel;
				bool bReleaseValid = true;
				while (iLevelParent.size() > 1)
				{
					iLevelParent.pop_back();
					for (int iOperationIndexParent = 0;
						iOperationIndexParent < (int)contOperationElementCurr.size(); iOperationIndexParent++)
					{
						if (contOperationElementCurr[iOperationIndexParent].iLevel != iLevelParent)
						{
							continue;
						}
						/**
							親作業が、増結(BeforeConnectかAfterConnect)だった場合は、
							bReleaseValidをfalseにして終了。
						*/
						if ((contOperationElementCurr[iOperationIndexParent].BeforeOperation != NULL &&
							contOperationElementCurr[iOperationIndexParent].BeforeOperation->getBOperation() 
							== CentDedBeforeOperation::EBOperation::BOperation_Connect) ||
							(contOperationElementCurr[iOperationIndexParent].AfterOperation != NULL &&
								contOperationElementCurr[iOperationIndexParent].AfterOperation->getAOperation() 
								== CentDedAfterOperation::EAOperation::AOperation_Connect))
						{
							bReleaseValid = false;
							break;
						}
					}
				}
				if (bReleaseValid)
				{
					iPrevRessyaType = 1;
				}
			}
			int iNextRessyaType = 2;
			if (contOperationElementNext[iOperationIndexNext].iLevel.size() == 1)
			{
				iNextRessyaType = 0;
			}
			else
			{
				/**
					次作業が主編成に増結している(増結の繰り返しは可)かどうかの確認を行います。
				*/
				vector<int> iLevelParent = contOperationElementNext[iOperationIndexNext].iLevel;
				bool bConnectValid = true;
				while (iLevelParent.size() > 1)
				{
					iLevelParent.pop_back();
					for (int iOperationIndexParent = 0;
						iOperationIndexParent < (int)contOperationElementNext.size(); iOperationIndexParent++)
					{
						if (contOperationElementNext[iOperationIndexParent].iLevel != iLevelParent)
						{
							continue;
						}
						/**
							親作業が、解結(BeforeReleaseかAfterRelease)だった場合は、
							bConnectValidをfalseにして終了。
						*/
						if ((contOperationElementNext[iOperationIndexParent].BeforeOperation != NULL &&
							contOperationElementNext[iOperationIndexParent].BeforeOperation->getBOperation()
							== CentDedBeforeOperation::EBOperation::BOperation_Release) ||
							(contOperationElementNext[iOperationIndexParent].AfterOperation != NULL &&
								contOperationElementNext[iOperationIndexParent].AfterOperation->getAOperation()
								== CentDedAfterOperation::EAOperation::AOperation_Release))
						{
							bConnectValid = false;
							break;
						}
					}
				}
				if (bConnectValid)
				{
					iNextRessyaType = 1;
				}
			}

			/**
				列車一体化、増結、解結の処理
				ここでは、列車位置の移動および、ReleaseEkiOrder・ConnectEkiOrderの設定と、
				m_contBeforeContinueList、m_contAfterContinueListへの格納を行います。
				同方向順並び
					両方主編成：一本化(前の列車に統合)
					前列車主編成・次列車増結編成：前列車はConnectEkiOrderの設定と、次列車の左への移動
					前列車解結編成・次列車主編成：次列車はReleaseEkiOrderの設定と、前列車の右への移動
				同方向逆並び・逆方向
					前列車・次列車ともに主編成の場合：路線外相当の表示（m_contBeforeContinueList、m_contAfterContinueListへの格納）
					前列車が解結編成の場合：前列車の右側に↴+路線外相当の表示を追加(ReleaseEkiOrder付きのm_contAfterContinueListへの格納）
					次列車が増結編成の場合：次列車の左側に路線外相当+↳の表示を追加(ConnectEkiOrder付きのm_contBeforeContinueListへの格納）


				Unrelated、前列車・次列車のいずれかが、主編成・解結編成・増結編成ではない場合：
					一体化等の作業は無し、前列車側のCustomizeJikokuhyouContentをreplaceに入れ、新たなCustomizeJikokuhyouContentを作り、次に送る
				前列車が解結・次列車が増結の場合：暫定で上と同じ扱い
				前列車と次列車が逆方向の場合：前列車が主編成の場合は路線外扱い、解結編成の場合は↴+路線外表示を追加する。
					次列車が主編成の場合は路線外扱い、増結編成の場合は路線外表示+↳を追加する。
					ただし、ここでは両列車のCdDedRessyaPropertyを配列状にしてから、m_contContinueListに収める作業のみを行い、
					実際に各列車のCustomizeJikokuhyouContentに始発駅・終着駅を書き込むのは、後で実施します。

			*/
			/**
				除外対象
				次列車接続タイプが別列車
				前列車もしくは次列車が"その他"である
				前列車が解結編成かつ次列車が増結編成
			*/
			if (eBeforeAfterType != EBeforeAfterType::BeforeAfterType_Unrelated &&
				iPrevRessyaType != 2 && iNextRessyaType != 2 &&
				!(iPrevRessyaType == 1 && iNextRessyaType == 1))
			{
				if (aRessyaPropertyCurr.getRessyahoukou() == aRessyaElementNext.sRessyaProperty.getRessyahoukou() &&
					contOperationElementCurr[iOperationIndex].iEkiOrder <= contOperationElementNext[iOperationIndexNext].iEkiOrder)
				{
					//同方向順並び
					if (iPrevRessyaType == 1)
					{
						//解結
						//☆5 分割列車の位置変更
#pragma omp critical(contReleaseMoveList)
						{
							m_contReleaseMoveList[aRessyaPropertyCurr.getRessyahoukou()][contOperationElementCurr[iOperationIndex].iEkiOrder].
								insert(make_pair(aRessyaPropertyCurr.getRessyaIndex(), aRessyaElementNext.sRessyaProperty.getRessyaIndex()));

						}
						//実処理はcompleteCustomizeJikokuhyouContentで行うのでコメントアウト
	//#pragma omp critical(CustomizeRessyaIndex)
	//					{
	//						//まずは、前列車と次列車それぞれのCustomizeJikokuhyouContentを探す。
	//						vector<CustomizeJikokuhyouContent>& contCustomizeJikokuhyouContent =
	//							m_pDedDia->getcontCustomizeRessyaIndex(aRessyaPropertyCurr.getRessyahoukou());
	//						int iCustomizeIndexPrev = -1;
	//						int iCustomizeIndexNext = -1;
	//						for (int idx = 0; idx < (int)contCustomizeJikokuhyouContent.size(); idx++)
	//						{
	//							for (int idxc = 0; idxc < (int)contCustomizeJikokuhyouContent[idx].iRessyaIndexCont.size(); idxc++)
	//							{
	//								if (contCustomizeJikokuhyouContent[idx].iRessyaIndexCont[idxc] == 
	//									aRessyaPropertyCurr.getRessyaIndex())
	//								{
	//									iCustomizeIndexPrev = idx;
	//								}
	//								if (contCustomizeJikokuhyouContent[idx].iRessyaIndexCont[idxc] == 
	//									aRessyaElementNext.sRessyaProperty.getRessyaIndex())
	//								{
	//									iCustomizeIndexNext = idx;
	//								}
	//					
	//							}
	//						}
	//						if (iCustomizeIndexPrev != -1 &&
	//							iCustomizeIndexNext != -1)
	//						{
	//							//次列車にReleaseEkiOrderの設定をします
	//							contCustomizeJikokuhyouContent[iCustomizeIndexNext].iReleaseEkiOrder = 
	//								contOperationElementCurr[iOperationIndex].iEkiOrder;

	//							//次列車を前列車の右に移動します
	//							if (iCustomizeIndexPrev > iCustomizeIndexNext)
	//							{
	//								contCustomizeJikokuhyouContent.insert(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexPrev + 1,
	//									contCustomizeJikokuhyouContent[iCustomizeIndexNext]);
	//								contCustomizeJikokuhyouContent.erase(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexNext);
	//							}
	//							else if (iCustomizeIndexPrev < iCustomizeIndexNext)
	//							{
	//								CustomizeJikokuhyouContent temp = contCustomizeJikokuhyouContent[iCustomizeIndexNext];
	//								contCustomizeJikokuhyouContent.erase(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexNext);
	//								contCustomizeJikokuhyouContent.insert(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexPrev + 1,
	//									temp);
	//							}
	//						}
	//					}

					}
					else if (iNextRessyaType == 1)
					{
						//増結
						//☆6 併合列車の位置変更

#pragma omp critical(contConnectMoveList)
						{
							m_contConnectMoveList[aRessyaPropertyCurr.getRessyahoukou()][contOperationElementNext[iOperationIndexNext].iEkiOrder].
								insert(make_pair(aRessyaElementNext.sRessyaProperty.getRessyaIndex(), aRessyaPropertyCurr.getRessyaIndex()));

						}
						//実処理はcompleteCustomizeJikokuhyouContentで行うのでコメントアウト
//#pragma omp critical(CustomizeRessyaIndex)
//						{
//							//まずは、前列車と次列車それぞれのCustomizeJikokuhyouContentを探す。
//							vector<CustomizeJikokuhyouContent>& contCustomizeJikokuhyouContent =
//								m_pDedDia->getcontCustomizeRessyaIndex(aRessyaPropertyCurr.getRessyahoukou());
//							int iCustomizeIndexPrev = -1;
//							int iCustomizeIndexNext = -1;
//							for (int idx = 0; idx < (int)contCustomizeJikokuhyouContent.size(); idx++)
//							{
//								for (int idxc = 0; idxc < (int)contCustomizeJikokuhyouContent[idx].iRessyaIndexCont.size(); idxc++)
//								{
//									if (contCustomizeJikokuhyouContent[idx].iRessyaIndexCont[idxc] ==
//										aRessyaPropertyCurr.getRessyaIndex())
//									{
//										iCustomizeIndexPrev = idx;
//									}
//									if (contCustomizeJikokuhyouContent[idx].iRessyaIndexCont[idxc] ==
//										aRessyaElementNext.sRessyaProperty.getRessyaIndex())
//									{
//										iCustomizeIndexNext = idx;
//									}
//
//								}
//							}
//							if (iCustomizeIndexPrev != -1 &&
//								iCustomizeIndexNext != -1)
//							{
//								//前列車にConnectEkiOrderの設定をします
//								contCustomizeJikokuhyouContent[iCustomizeIndexPrev].iConnectEkiOrder =
//									contOperationElementNext[iOperationIndexNext].iEkiOrder;
//
//								//前列車を次列車の左に移動します
//								if (iCustomizeIndexPrev > iCustomizeIndexNext)
//								{
//									CustomizeJikokuhyouContent temp = contCustomizeJikokuhyouContent[iCustomizeIndexPrev];
//									contCustomizeJikokuhyouContent.erase(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexPrev);
//									contCustomizeJikokuhyouContent.insert(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexNext,
//										temp);
//								}
//								else if (iCustomizeIndexPrev < iCustomizeIndexNext)
//								{
//									contCustomizeJikokuhyouContent.insert(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexNext,
//										contCustomizeJikokuhyouContent[iCustomizeIndexPrev]);
//									contCustomizeJikokuhyouContent.erase(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexPrev);
//								}
//							}
//						}
					}
					else
					{
						//一本化
#pragma omp critical(CustomizeRessyaIndex)
						{
							//まずは、前列車と次列車それぞれのCustomizeJikokuhyouContentを探す。
							vector<CustomizeJikokuhyouContent>& contCustomizeJikokuhyouContent =
								m_pDedDia->getcontCustomizeRessyaIndex(aRessyaPropertyCurr.getRessyahoukou());
							int iCustomizeIndexPrev = -1;
							int iCustomizeIndexNext = -1;
							for (int idx = 0; idx < (int)contCustomizeJikokuhyouContent.size(); idx++)
							{
								for (int idxc = 0; idxc < (int)contCustomizeJikokuhyouContent[idx].iRessyaIndexCont.size(); idxc++)
								{
									if (contCustomizeJikokuhyouContent[idx].iRessyaIndexCont[idxc] ==
										aRessyaPropertyCurr.getRessyaIndex())
									{
										iCustomizeIndexPrev = idx;
									}
									if (contCustomizeJikokuhyouContent[idx].iRessyaIndexCont[idxc] ==
										aRessyaElementNext.sRessyaProperty.getRessyaIndex())
									{
										iCustomizeIndexNext = idx;
									}

								}
							}
							if (iCustomizeIndexPrev != -1 &&
								iCustomizeIndexNext != -1)
							{
								//次列車のiRessyaIndexContを前列車のiRessyaIndexContの後ろに挿入します。
								//また、次列車のConnectEkiOrderで、前列車のConnectEkiOrderを上書きします。
								//次列車のcontCustomizeJikokuhyouContentは削除します。
								contCustomizeJikokuhyouContent[iCustomizeIndexPrev].iRessyaIndexCont.insert(
									contCustomizeJikokuhyouContent[iCustomizeIndexPrev].iRessyaIndexCont.end(),
									contCustomizeJikokuhyouContent[iCustomizeIndexNext].iRessyaIndexCont.begin(),
									contCustomizeJikokuhyouContent[iCustomizeIndexNext].iRessyaIndexCont.end());
								contCustomizeJikokuhyouContent[iCustomizeIndexPrev].iConnectEkiOrder =
									contCustomizeJikokuhyouContent[iCustomizeIndexNext].iConnectEkiOrder;
								contCustomizeJikokuhyouContent.erase(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexNext);
							}
						}
#pragma omp critical(Operation)
						pBeforeOperationNext->setIsSyubetsuChange(true);
						//一本化の列車の組について、後列車はダイヤグラムビューで、既に列車情報を一回以上表示したものとして扱います。
						if (eBeforeAfterType == EBeforeAfterType::BeforeAfterType_PropertySame)
						{
#pragma omp critical(Operation)
							pBeforeOperationNext->setRessyajouhouOmit(true);
						}
					}
				}
				else
				{
					//同方向逆並びまたは逆方向 ☆7
					{
						//主編成の場合は、路線外終着相当の表示を、解結編成の場合は、前列車の右側に↴+路線外終着相当の表示を追加します。
						OuterSearchElement aOuterSearchElement(
							aRessyaPropertyCurr,
							strOperationNumberTemp,
							contOperationElementCurr[iOperationIndex].iEkiOrder,
							iPrevRessyaType == 1);

//#pragma omp critical(AfterContinueList)
//						m_contAfterContinueList.push_back(aOuterSearchElement);

#pragma omp critical(AfterContinueList)
						m_contAfterContinueList[aRessyaPropertyCurr.getRessyahoukou()][contOperationElementCurr[iOperationIndex].iEkiOrder].push_back(aOuterSearchElement);
					}
					{
						//主編成の場合は、路線外始発相当の表示を、増結編成の場合は、次列車の左側に路線外始発相当+↳の表示を追加します。
						OuterSearchElement aOuterSearchElement(
							aRessyaElementNext.sRessyaProperty,
							strOperationNumberTemp,
							contOperationElementNext[iOperationIndexNext].iEkiOrder,
							iNextRessyaType == 1);

//#pragma omp critical(BeforeContinueList)
//						m_contBeforeContinueList.push_back(aOuterSearchElement);

#pragma omp critical(BeforeContinueList)
						m_contBeforeContinueList[aRessyaElementNext.sRessyaProperty.getRessyahoukou()][contOperationElementNext[iOperationIndexNext].iEkiOrder].push_back(aOuterSearchElement);
					}
				}
			}

			/**
				運用番号反転
				運用番号反転設定が有効、前列車と次列車の列車方向が逆、
				の条件を満たした場合、運用番号を反転して、pBeforeOperationNextにつなぐ。
			*/
			if (m_bOperationNumberReverse &&
				aRessyaPropertyCurr.getRessyahoukou() != aRessyaElementNext.sRessyaProperty.getRessyahoukou()&&
				strOperationNumberTemp.size()>1)
			{
				std::reverse(strOperationNumberTemp.begin(), strOperationNumberTemp.end());
			}
			/**
				strOperationNumberTempが空、もしくは空白運番のみの場合、
				strOperationNumberTempを前列車接続の仮運用番号で置き換える。
			*/
			if ((strOperationNumberTemp.empty() ||
				(strOperationNumberTemp.size() == 1 && strOperationNumberTemp.front() == _T("")))&&
				pBeforeOperationNext->getOperationNumberTempCount() > 0)
			{
				strOperationNumberTemp = pBeforeOperationNext->getOperationNumberTemp();
			}


#pragma omp critical(Operation)
			pBeforeOperationNext->setOperationNumber(strOperationNumberTemp);

			/**
				insertOperationTableContentToBufferには、pAfterOperation(検索用後作業)を渡します。
				addで運用表を組み立てる際に、pAfterOperationの後に入れることで、順番が定まります。
			*/
#pragma omp critical(OperationTableContentBuffer)
			insertOperationTableContentToBuffer(
				aRessyaElementNext.sRessyaProperty,
				strOperationNumberTemp,
				contOperationElementNext[iOperationIndexNext].iEkiOrder,
				NULL,
				pAfterOperation,
				eBeforeAfterType);

			vector<int> iLevelNext = contOperationElementNext[iOperationIndexNext].iLevel;
			iLevelNext.back()++;
			junctionOperationElement(
				aRessyaElementNext.sRessyaProperty,
				contOperationElementNext,
				iLevelNext,
				strOperationNumberTemp);
		}
	}
}

void CDedOperationConnecter::insertOperationTableContentToBuffer(
	const CdDedRessyaProperty aRessyaProperty, 
	vector<tstring>& strOperationNumber, 
	const int iSihatsuEkiOrder, 
	const CentDedBeforeOperation* pBeforeOperation,
	const CentDedAfterOperation* pAfterOperation,
	const EBeforeAfterType eBeforeType)
{
	unordered_map<tstring, OperationTableContent>& contOperationTableContentBuffer
		= m_contOperationTableContentBuffer[(int)aRessyaProperty.getRessyahoukou()]
		[aRessyaProperty.getRessyaIndex()];
	for (int idxon = 0; idxon < (int)strOperationNumber.size(); idxon++)
	{
		if (strOperationNumber[idxon].empty())
		{
			continue;
		}
		auto itr = contOperationTableContentBuffer.find(strOperationNumber[idxon]);
		if (itr != contOperationTableContentBuffer.end())
		{
			int iTemp = 0;
			do
			{
				tstring strOperationNumberTemp = strOperationNumber[idxon] + _T(";") + to_tstring(iTemp);
				auto itrt = contOperationTableContentBuffer.find(strOperationNumberTemp);
				if (itrt == contOperationTableContentBuffer.end())
				{
					strOperationNumber[idxon] = strOperationNumberTemp;
					break;
				}
				iTemp++;

			} while (1);
		}
		if (pBeforeOperation != NULL &&
			pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
		{
			OperationTableContent aOperationTableContent(
				aRessyaProperty,
				iSihatsuEkiOrder,
				pBeforeOperation->getOuterShihatsuekiIndex(),
				pBeforeOperation->getOuterShihatsuJikoku(),
				pBeforeOperation->getChakuJikoku());
			if (pAfterOperation != NULL)
			{
				aOperationTableContent.AfterOperation = pAfterOperation;
			}
			contOperationTableContentBuffer[strOperationNumber[idxon]] = aOperationTableContent;
		}
		else if (pBeforeOperation != NULL &&
			pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Out)
		{
			OperationTableContent aOperationTableContent(
				aRessyaProperty,
				iSihatsuEkiOrder,
				EBeforeAfterType::BeforeAfterType_OutIn);
			if (pAfterOperation != NULL)
			{
				aOperationTableContent.AfterOperation = pAfterOperation;
			}
			contOperationTableContentBuffer[strOperationNumber[idxon]] = aOperationTableContent;
		}
		else if(pAfterOperation != NULL)
		{
			OperationTableContent aOperationTableContent(
				aRessyaProperty,
				iSihatsuEkiOrder,
				pAfterOperation,
				eBeforeType);
			contOperationTableContentBuffer[strOperationNumber[idxon]] = aOperationTableContent;
		}
		else
		{
			OperationTableContent aOperationTableContent(
				aRessyaProperty,
				iSihatsuEkiOrder,
				eBeforeType);
			contOperationTableContentBuffer[strOperationNumber[idxon]] = aOperationTableContent;
		}
	}
}

void CDedOperationConnecter::addOperationTableContent(
	const CdDedRessyaProperty aRessyaProperty, 
	vector<tstring>& strOperationNumber, 
	const int iSyuuchakuEkiOrder, 
	const CentDedAfterOperation* pAfterOperation,
	const EBeforeAfterType eAfterType)
{
	unordered_map<tstring, OperationTableContent>& contOperationTableContentBuffer
		= m_contOperationTableContentBuffer[(int)aRessyaProperty.getRessyahoukou()]
		[aRessyaProperty.getRessyaIndex()];
	for (int idxon = 0; idxon < (int)strOperationNumber.size(); idxon++)
	{
		if (strOperationNumber[idxon].empty())
		{
			continue;
		}
		auto itr = contOperationTableContentBuffer.find(strOperationNumber[idxon]);
		if (itr != contOperationTableContentBuffer.end())
		{
			OperationTableContent aOperationTableContent =
				contOperationTableContentBuffer[strOperationNumber[idxon]];

			/**
				(この運番における)始発駅と終着駅が同一駅か否かを調べます。
				iSihatsuEkiOrderとiSyuuchakuEkiOrderが同値→同一駅
				異なる場合は、
					isRunBetweenNextEki(iSihatsuEkiOrder)またはisRunBetweenNextEki(iSyuuchakuEkiOrder-1)
					のいずれかがtrue→別駅
					共にfalseの場合、getRunBetweenEkiForward(iSihatsuEkiOrder)がiSyuuchakuEkiOrderになる場合は同駅
			*/
			if (aOperationTableContent.iSihatsuEkiOrder == iSyuuchakuEkiOrder)
			{
				continue;
			}

			const CentDedRessya* pRessya =
				m_pDedDia->getCentDedRessyaCont(aRessyaProperty.getRessyahoukou())->getMuPtr()
				->get(aRessyaProperty.getRessyaIndex());
			if (!pRessya->isRunBetweenNextEki(aOperationTableContent.iSihatsuEkiOrder) &&
				!pRessya->isRunBetweenNextEki(iSyuuchakuEkiOrder - 1))
			{
				if (pRessya->getRunBetweenEkiForward(aOperationTableContent.iSihatsuEkiOrder) == iSyuuchakuEkiOrder)
				{
					continue;
				}
			}

			/**
				(この運番における)始発駅が分岐駅や環状線によって、着側と発側が別々になっており、始発となる作業が着側にある場合は、
				始発駅Orderを発側に上書きします。
			*/
			if (!pRessya->isRunBetweenNextEki(aOperationTableContent.iSihatsuEkiOrder))
			{
				aOperationTableContent.iSihatsuEkiOrder = pRessya->getRunBetweenEkiForward(aOperationTableContent.iSihatsuEkiOrder);
			}

			/**
				(この運番における)終着駅が分岐駅や環状線によって、着側と発側が別々になっており、終着となる作業が発側にある場合は、
				終着駅Orderを着側に上書きします。
			*/
			int iSyuuchakuEkiOrderTemp = iSyuuchakuEkiOrder;
			if (!pRessya->isRunBetweenNextEki(iSyuuchakuEkiOrder - 1))
			{
				iSyuuchakuEkiOrderTemp = pRessya->getRunBetweenEkiBackward(iSyuuchakuEkiOrder);
			}

			const CentDedAfterOperation* pAfterOperationForSearch = aOperationTableContent.AfterOperation;
			if (pAfterOperation != NULL/* &&
				pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Junction*/)
			{
				//Ver2.05仮対応(入区路線外終着の場合、aOperationTableContent.AfterOperationがNULL以外だと不具合があるかは要検証)
				aOperationTableContent.AfterOperation = pAfterOperation;
			}
			else 
			{
				aOperationTableContent.AfterOperation = NULL;
			}
			aOperationTableContent.iSyuuchakuEkiOrder = iSyuuchakuEkiOrderTemp;
			aOperationTableContent.eAfterType = eAfterType;

			if (pAfterOperation != NULL &&
				pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
			{
				aOperationTableContent.iOuterShuchakuekiIndex = pAfterOperation->getOuterShuchakuekiIndex();
				aOperationTableContent.HatsuJikoku = pAfterOperation->getHatsuJikoku();
				aOperationTableContent.OuterShuchakuJikoku = pAfterOperation->getOuterShuchakuJikoku();
			}
			//else if (pAfterOperation != NULL &&
			//	pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_In)
			//{
			//	aOperationTableContent.eAfterType = EBeforeAfterType::BeforeAfterType_OutIn;
			//}

			tstring::size_type pos = 0;
			pos = strOperationNumber[idxon].find(';');
			if (pos != tstring::npos)
			{
				strOperationNumber[idxon] = strOperationNumber[idxon].substr(0, pos);
			}

#pragma omp critical(OperationTableContent)
			{
				list< OperationTableContent>* contOperationTableContent =
					&m_pDedDia->getcontOperationTableContent()[strOperationNumber[idxon]];
				/**
					検索用後作業ポインタが収められている場合、contOperationTableContentの中から、
					AfterOperationが一致するものを探し、その次に挿入します。
					挿入先が見つかった場合は、RessyaPropertyに格納されている時刻をNULLにします。
					(以前はBeforeJunctionでBuffer格納時にNULLにしていたのを止め、ここで処理する)
					挿入先が見つからなかった場合、RessyaPropertyの時刻を参照し、挿入場所を求めます。
				*/
				bool bSuccessInsert = false;
				if (pAfterOperationForSearch != NULL)
				{
					for (auto itrList = contOperationTableContent->begin();
						itrList != contOperationTableContent->end(); itrList++)
					{
						if (itrList->AfterOperation == pAfterOperationForSearch)
						{
							itrList++;
							aOperationTableContent.aRessyaProperty.setJikoku(CdDedJikoku());
							contOperationTableContent->insert(itrList, aOperationTableContent);
							bSuccessInsert = true;
							break;
						}
					}
				}
				
				/**
					検索用後作業がない場合・挿入先が見つからなかった場合は、RessyaPropertyの時刻を参照し、順に並べます。
				*/
				if (!bSuccessInsert &&
					!aOperationTableContent.aRessyaProperty.getJikoku().isNull())
				{
					if (contOperationTableContent->empty())
					{
						contOperationTableContent->push_back(aOperationTableContent);
					}
					else
					{
						for (auto itrList = contOperationTableContent->begin();
							itrList != contOperationTableContent->end(); itrList++)
						{
							if (!itrList->aRessyaProperty.getJikoku().isNull() &&
								aOperationTableContent.aRessyaProperty.getJikoku().compare(
									itrList->aRessyaProperty.getJikoku(), m_KitenJikoku) < 0)
							{
								contOperationTableContent->insert(itrList, aOperationTableContent);
								bSuccessInsert = true;
								break;
							}
						}
						//他の時刻あり要素と比較した結果、どれよりも後だった場合は、最後部に追加する。
						if (!bSuccessInsert)
						{
							m_pDedDia->getcontOperationTableContent()[strOperationNumber[idxon]].push_back(aOperationTableContent);
						}
					}
				}
			}
		}
	}
}

void CDedOperationConnecter::insertInOutLinkCodeElement(
	const tstring strInOutLinkCode, 
	const RessyaElement aRessyaElement)
{
	map<tstring, InOutLinkCodeContent>* contInOutLinkCodeContent = 
		&m_pDedDia->getcontInOutLinkCodeContent();
	auto aInOutLinkCodeItr = contInOutLinkCodeContent->find(strInOutLinkCode);
	if (aRessyaElement.BeforeOperation != NULL)
	{
		/**
			aRessyaElementが出区・路線外始発の場合
			(1)contInOutLinkCodeContent内にstrInOutLinkCodeをキーとする要素があるかを確認
			(2.1)ない場合は、iStatus=0でInOutLinkCodeContentを作成し、contOutRessyaPropertyにaRessyaElementのRessyaPropertyを格納し、
					BeforeOperationにaRessyaElementのBeforeOperationを書き込み、strInOutLinkCodeをキーにcontInOutLinkCodeContentに格納する
			(2.2)ある場合は、iStatusの値により処理が変わります
				1:既に格納済みの入区作業とベアとなります。ただし、起点時刻跨ぎが無効な場合は、時刻チェックが必要です
					aInOutLinkCodeItrのiStatusを2に、contOutRessyaPropertyにaRessyaElementのRessyaPropertyを格納し、
					BeforeOperationにaRessyaElementのBeforeOperationを書き込みます
				0,2:出区作業が被るので、無効になります。この場合はStatusを3に書き換え、
					contOutRessyaPropertyにaRessyaElementのRessyaPropertyを追加し、
					BeforeOperationを初期化（NULL) します。
				3:出区作業が被るので、無効になります。この場合は既にStatusが3なので,
				contOutRessyaPropertyにaRessyaElementのRessyaPropertyを追加のみを実行します
		*/
		if (aInOutLinkCodeItr == contInOutLinkCodeContent->end())
		{
			/**
				該当するものがない場合は、aRessyaElementをInOutLinkCodeElementに収めて、contInOutLinkCodeContentに加えます。
			*/
			InOutLinkCodeContent aInOutLinkCodeContent(0);
			aInOutLinkCodeContent.contOutRessyaProperty.push_back(aRessyaElement.sRessyaProperty);
			aInOutLinkCodeContent.BeforeOperation = aRessyaElement.BeforeOperation;
			contInOutLinkCodeContent->insert(std::make_pair(strInOutLinkCode,aInOutLinkCodeContent));
		}
		else
		{
			if (aInOutLinkCodeItr->second.iStatus == 1)
			{
				bool bJikokuSatisfy = true;
				if (!m_bOperationCrossKitenJikoku)
				{
					bJikokuSatisfy =
						aRessyaElement.sRessyaProperty.getJikoku().compare(
							aInOutLinkCodeItr->second.contInRessyaProperty.front().getJikoku(), m_KitenJikoku) >= 0;
				}
				if (bJikokuSatisfy)
				{
					aInOutLinkCodeItr->second.iStatus = 2;
					aInOutLinkCodeItr->second.contOutRessyaProperty.push_back(aRessyaElement.sRessyaProperty);
					aInOutLinkCodeItr->second.BeforeOperation = aRessyaElement.BeforeOperation;
				}
				else
				{
					aInOutLinkCodeItr->second.iStatus = 3;
				}
			}
			else if (aInOutLinkCodeItr->second.iStatus == 0 ||
				aInOutLinkCodeItr->second.iStatus == 2)
			{
				aInOutLinkCodeItr->second.iStatus = 3;
				aInOutLinkCodeItr->second.contOutRessyaProperty.push_back(aRessyaElement.sRessyaProperty);
				aInOutLinkCodeItr->second.BeforeOperation = NULL;
			}
			else if (aInOutLinkCodeItr->second.iStatus == 3)
			{
				aInOutLinkCodeItr->second.contOutRessyaProperty.push_back(aRessyaElement.sRessyaProperty);
			}
		}
	}
	else if (aRessyaElement.AfterOperation != NULL)
	{
		/**
			aRessyaElementが入区・路線外終着の場合
			(1)contInOutLinkCodeContent内にstrInOutLinkCodeをキーとする要素があるかを確認
			(2.1)ない場合は、iStatus=1でInOutLinkCodeElementを作成し、contInOutLinkCodeContentに格納する
			(2.2)ある場合は、iStatusの値により処理が変わります
				0:既に格納済みの出区作業とベアとなります。ただし、起点時刻跨ぎが無効な場合は、時刻チェックが必要です
					aInOutLinkCodeItrのiStatusを2に書き換えます
				1,2:入区作業が被るので、無効になります。この場合はStatusを3に書き換えます
				3:入区作業が被るので、無効になります。この場合は既にStatusが3なので特に処理はありません。
		*/
		if (aInOutLinkCodeItr == contInOutLinkCodeContent->end())
		{
			/**
				該当するものがない場合は、aRessyaElementをInOutLinkCodeElementに収めて、contInOutLinkCodeContentに加えます。
			*/
			InOutLinkCodeContent aInOutLinkCodeContent(1);
			aInOutLinkCodeContent.contInRessyaProperty.push_back(aRessyaElement.sRessyaProperty);
			contInOutLinkCodeContent->insert(std::make_pair(strInOutLinkCode, aInOutLinkCodeContent));
		}
		else
		{
			if (aInOutLinkCodeItr->second.iStatus == 0)
			{
				bool bJikokuSatisfy = true;
				if (!m_bOperationCrossKitenJikoku)
				{
					bJikokuSatisfy =
						aRessyaElement.sRessyaProperty.getJikoku().compare(
							aInOutLinkCodeItr->second.contOutRessyaProperty.front().getJikoku(), m_KitenJikoku) <= 0;
				}
				if (bJikokuSatisfy)
				{
					aInOutLinkCodeItr->second.iStatus = 2;
					aInOutLinkCodeItr->second.contInRessyaProperty.push_back(aRessyaElement.sRessyaProperty);
				}
				else
				{
					aInOutLinkCodeItr->second.iStatus = 3;
					aInOutLinkCodeItr->second.BeforeOperation = NULL;
				}
			}
			else if (aInOutLinkCodeItr->second.iStatus == 1 ||
				aInOutLinkCodeItr->second.iStatus == 2)
			{
				aInOutLinkCodeItr->second.iStatus = 3;
				aInOutLinkCodeItr->second.contInRessyaProperty.push_back(aRessyaElement.sRessyaProperty);
				aInOutLinkCodeItr->second.BeforeOperation = NULL;
			}
			else if (aInOutLinkCodeItr->second.iStatus == 3)
			{
				aInOutLinkCodeItr->second.contInRessyaProperty.push_back(aRessyaElement.sRessyaProperty);
			}
		}

	}
}

void CDedOperationConnecter::completeCustomizeJikokuhyouContent()
{
	Mu<CentDedRessya*>* pCentDedRessyaConts[2];
	for (int iRessyahoukou = Ressyahoukou_Kudari;
		iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
	{
		pCentDedRessyaConts[iRessyahoukou] = m_pDedDia->getCentDedRessyaCont((ERessyahoukou)iRessyahoukou)->getMuPtr();
	}
	unordered_map<tstring, list<OperationTableContent>> contOperationTableContent =
		m_pDedDia->getcontOperationTableContent();
	const CentDedEkiCont* pCentDedEkiCont = m_pDedRosen->getCentDedEkiCont();

	/**
		iEkiOrder->iEkiIndex対応表(分岐・環状対応)
		下り・上りの2方面×駅数のコンテナ
		[iEkiOrder][iRessyahoukou]でアクセスすると、contRessyaExistに対応するiEkiIndexを返します
		また、分岐環状駅については、iEkiIndexLoop[0]駅に集約します。従って、上り列車の場合はiEkiOrderLoop.back()に当たります
	*/
	vector<vector<int>> iEkiOrderTable;
	iEkiOrderTable.resize(pCentDedEkiCont->size());

	for (int iEki = 0; iEki < pCentDedEkiCont->size(); iEki++)
	{
		const CentDedEki aEki = pCentDedEkiCont->get(iEki);

		if (aEki.getBrunchLoopPosition() == -1)
		{
			iEkiOrderTable[iEki].insert(iEkiOrderTable[iEki].begin(), iEki);
			iEkiOrderTable[pCentDedEkiCont->size() - 1 - iEki].push_back(iEki);
		}
		else
		{
			deque<int> iEkiIndexLoop = aEki.getEkiIndexLoop();
			iEkiOrderTable[iEki].insert(iEkiOrderTable[iEki].begin(), iEkiIndexLoop[0]);
			iEkiOrderTable[pCentDedEkiCont->size() - 1 - iEki].push_back(iEkiIndexLoop[0]);
		}
	}

	for (int iRessyahoukou = Ressyahoukou_Kudari; iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
	{
		//Before+Connectは下位の駅から遡っていく
		for (int iEkiOrder = pCentDedEkiCont->size() - 1; iEkiOrder >= 0; iEkiOrder--)
		{
			//(1)併合で同方向順並びのパターン(☆6)
			unordered_multimap<int, int> contConnectMoveList = m_contConnectMoveList[iRessyahoukou][iEkiOrder];
			auto itrConnectMoveList = contConnectMoveList.begin();
			for (; itrConnectMoveList != contConnectMoveList.end(); itrConnectMoveList++)
			{
				//itrConnectMoveList->first : 併合先の列車Index
				//itrConnectMoveList->second : 併合列車の列車Index
				
				//まずは、前列車と次列車それぞれのCustomizeJikokuhyouContentを探す。
				vector<CustomizeJikokuhyouContent>& contCustomizeJikokuhyouContent =
					m_pDedDia->getcontCustomizeRessyaIndex((ERessyahoukou)iRessyahoukou);
				int iCustomizeIndexPrev = -1;
				int iCustomizeIndexNext = -1;
				for (int idx = 0; idx < (int)contCustomizeJikokuhyouContent.size(); idx++)
				{
					for (int idxc = 0; idxc < (int)contCustomizeJikokuhyouContent[idx].iRessyaIndexCont.size(); idxc++)
					{
						if (contCustomizeJikokuhyouContent[idx].iRessyaIndexCont[idxc] ==
							itrConnectMoveList->second)
						{
							iCustomizeIndexPrev = idx;
						}
						if (contCustomizeJikokuhyouContent[idx].iRessyaIndexCont[idxc] ==
							itrConnectMoveList->first)
						{
							iCustomizeIndexNext = idx;
						}

					}
				}
				if (iCustomizeIndexPrev != -1 &&
					iCustomizeIndexNext != -1)
				{
					//前列車にConnectEkiOrderの設定をします
					contCustomizeJikokuhyouContent[iCustomizeIndexPrev].iConnectEkiOrder = iEkiOrder;

					//前列車を次列車の左に移動します
					if (iCustomizeIndexPrev > iCustomizeIndexNext)
					{
						CustomizeJikokuhyouContent temp = contCustomizeJikokuhyouContent[iCustomizeIndexPrev];
						contCustomizeJikokuhyouContent.erase(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexPrev);
						contCustomizeJikokuhyouContent.insert(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexNext,
							temp);
					}
					else if (iCustomizeIndexPrev < iCustomizeIndexNext)
					{
						contCustomizeJikokuhyouContent.insert(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexNext,
							contCustomizeJikokuhyouContent[iCustomizeIndexPrev]);
						contCustomizeJikokuhyouContent.erase(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexPrev);
					}
				}
			}

			//(2)分割・併合・一本化で、逆方向または同方向逆並びのパターン(☆7-1)
			vector<OuterSearchElement>& contBeforeContinueList = m_contBeforeContinueList[iRessyahoukou][iEkiOrder];
			int iBeforeSize = contBeforeContinueList.size();
			for (int iBeforeIndex = 0; iBeforeIndex < iBeforeSize; iBeforeIndex++)
			{
				OuterSearchElement& aOuterSearchElement = contBeforeContinueList[iBeforeIndex];

				CdDedRessyaProperty aRessyaProperty = aOuterSearchElement.aRessyaProperty;
				//const CentDedRessya* pCentDedRessya =
				//	pCentDedRessyaConts[aRessyaProperty.getRessyahoukou()]
				//	->get(aRessyaProperty.getRessyaIndex());
				///**
				//	次に、各運用番号に対して行き先を取得する。
				//	その際、主編成の終点から、種別変更・分割で先の列車につながっている場合、
				//	終点で解結して路線外終着になる場合は、上で獲得した主編成の終着駅を置き換える。
				//	なお、主編成が路線外終着の場合は置き換えは起こらない。
				//*/

				unordered_map<tstring, vector<RessyaPropertyBuffer>> MapContRessyaPropertyBuffer;
				unordered_map<tstring, OuterDisplayContent> MapOuterDisplayContentBuffer;
				for (int idx = 0; idx < (int)aOuterSearchElement.strContOperationNumber.size(); idx++)
				{
					tstring strOperationNumber = aOuterSearchElement.strContOperationNumber[idx];

					if (strOperationNumber.empty())
					{
						continue;
					}
					list<OperationTableContent>& ListOperationTableContent = contOperationTableContent[strOperationNumber];
					auto itrListOperationTableContent = ListOperationTableContent.begin();
					for (; itrListOperationTableContent != ListOperationTableContent.end(); itrListOperationTableContent++)
					{
						if (!itrListOperationTableContent->aRessyaProperty.isEqualTo(aRessyaProperty, false))
						{
							continue;
						}
						if (itrListOperationTableContent->iOuterShihatsuekiIndex < 0)
						{
							itrListOperationTableContent--;//最後に一回デクリメントして、当該列車の"前"に移動する。
						}
						break;
					}
					if (itrListOperationTableContent == ListOperationTableContent.end())
					{
						//aRessyaPropertyが一致するものが見つからなかったらこの運番に対しての表示は無しにする
						continue;
					}
					vector<RessyaPropertyBuffer > ContRessyaPropertyBuffer;

					OuterDisplayContent aOuterDisplayContent;

					/**
						この列車のルートを調べる、ルートに輪ができ、輪の始点が当駅なら、この列車の始発駅は"環状"になる。
						輪の始点が当駅以外なら、この列車の始発駅は"環状線"になる。
					*/
					vector<int> RouteEkiIndex;
					bool bLoop = false;
					bool bFirst = true;

					for (; /*itrListOperationTableContent != ListOperationTableContent.end()*/; itrListOperationTableContent--)
					{

						const CentDedRessya* pCentDedRessyaSearch =
							pCentDedRessyaConts[itrListOperationTableContent->aRessyaProperty.getRessyahoukou()]
							->get(itrListOperationTableContent->aRessyaProperty.getRessyaIndex());

						if (bFirst)
						{
							//最初の列車(当該列車の前の列車)の場合、列車種別、当該列車終着駅の発時刻、駅扱い、aRessyaProperty、前列車との接続タイプ、前列車の終着駅Orderを取得します
							aOuterDisplayContent.iRessyaSyubetsu = pCentDedRessyaSearch->getRessyasyubetsuIndex();
							aOuterDisplayContent.ChakuJikoku = pCentDedRessyaSearch->getCentDedEkiJikoku(
								itrListOperationTableContent->iSyuuchakuEkiOrder).getVirtualChakujikoku();
							aOuterDisplayContent.eEkiatsukai = pCentDedRessyaSearch->getCentDedEkiJikoku(
								itrListOperationTableContent->iSyuuchakuEkiOrder).getEkiatsukai();
							aOuterDisplayContent.iRessyaTrackIndex = pCentDedRessyaSearch->getCentDedEkiJikoku(
								itrListOperationTableContent->iSyuuchakuEkiOrder).getRessyaTrackIndex();
							aOuterDisplayContent.aRessyaProperty = itrListOperationTableContent->aRessyaProperty;

							aOuterDisplayContent.eEBeforeAfterType = itrListOperationTableContent->eAfterType;
							aOuterDisplayContent.iJunctionEkiOrder = itrListOperationTableContent->iSyuuchakuEkiOrder;

							bFirst = false;
						}
						//始発駅をitrListOperationTableContentで上書きする。
						//終着駅Orderは、一度駅Indexに直してから、元々の列車方向に合わせたOrderに変更しなおす。
						int iSihatsuEkiIndexSearch = pCentDedRessyaSearch->EkiIndexOfEkiOrder(itrListOperationTableContent->iSihatsuEkiOrder);
						aOuterDisplayContent.iEkiOrder = pCentDedEkiCont->EkiOrderOfEkiIndex(aRessyaProperty.getRessyahoukou(), iSihatsuEkiIndexSearch);
						aOuterDisplayContent.iOuterEkiIndex = itrListOperationTableContent->iOuterShihatsuekiIndex;
						if (aOuterDisplayContent.iOuterEkiIndex >= 0)
						{
							aOuterDisplayContent.HatsuJikoku = itrListOperationTableContent->OuterShihatsuJikoku;
						}
						else
						{
							aOuterDisplayContent.HatsuJikoku = pCentDedRessyaSearch->getCentDedEkiJikoku(itrListOperationTableContent->iSihatsuEkiOrder).getVirtualHatsujikoku();
						}

						RessyaPropertyBuffer aRessyaPropertyBuffer;
						//aRessyaPropertyBufferの始発駅Orderはその列車基準でおｋとする(同じ列車同士で比較し、始発駅の遠さを見る必要があるので)
						aRessyaPropertyBuffer.iEkiOrder = itrListOperationTableContent->iSihatsuEkiOrder;
						aRessyaPropertyBuffer.iOuterEkiIndex = itrListOperationTableContent->iOuterShihatsuekiIndex;
						aRessyaPropertyBuffer.aRessyaProperty = itrListOperationTableContent->aRessyaProperty;

						int iEkiOrder = itrListOperationTableContent->iSyuuchakuEkiOrder;
						for (; iEkiOrder > itrListOperationTableContent->iSihatsuEkiOrder; iEkiOrder--)
						{
							if (!pCentDedRessyaSearch->isRunBetweenNextEki(iEkiOrder - 1))
							{
								/**
									iEkiOrderと前の駅間を運転していない場合は、
									運行なし区間を飛ばし、次に運行ありになる区間へ移る、
									その際、運行なしの前後が同一駅(分岐・環状関係)であることを確認する。
								*/
								int iEkiOrderPrev = pCentDedRessyaSearch->getRunBetweenEkiBackward(iEkiOrder);
								if (iEkiOrderPrev >= 0 &&
									iEkiOrderPrev > itrListOperationTableContent->iSihatsuEkiOrder &&
									pCentDedEkiCont->isSameBrunchLoopGroup(iEkiOrder, iEkiOrderPrev, pCentDedRessyaSearch->getRessyahoukou()))
								{
									iEkiOrder = iEkiOrderPrev;
								}
								else
								{
									break;
								}
							}

							int iEkiIndexPrev = iEkiOrderTable[iEkiOrder - 1][(int)pCentDedRessyaSearch->getRessyahoukou()];
							int iEkiIndexNext = iEkiOrderTable[iEkiOrder][(int)pCentDedRessyaSearch->getRessyahoukou()];
							int iPosition = -1;
							for (int iSearchIndex = 0; iSearchIndex < (int)RouteEkiIndex.size(); iSearchIndex++)
							{
								if (RouteEkiIndex[iSearchIndex] == iEkiIndexPrev)
								{
									iPosition = iSearchIndex;
									break;
								}
							}
							if (iPosition == -1)
							{
								/**
									iPositionが-1の場合は、RouteEkiIndexに前駅のIndexを追加して次へ
								*/
								RouteEkiIndex.push_back(iEkiIndexNext);
							}
							else if (iPosition == RouteEkiIndex.size() - 1)
							{
								/**
									iPositionが末尾の場合は、折り返している状態なので、RouteEkiIndexの末尾要素を削除して次へ。
								*/
								RouteEkiIndex.pop_back();
							}
							else if (iPosition == 0)
							{
								/**
									iPositionが先頭(かつ末尾ではない)の場合は、この列車の始発駅は"環状"になる。
								*/
								bLoop = true;
								aOuterDisplayContent.iEkiOrder = -1;
								aOuterDisplayContent.HatsuJikoku.setNull();
								//aRessyaPropertyBufferの駅Orderはその列車基準でおｋとする(同じ列車同士での比較が原則だから)
								aRessyaPropertyBuffer.iEkiOrder = iEkiOrder - 1;
								aRessyaPropertyBuffer.bLoop = true;
								break;
							}
							else
							{
								/**
									iPositionが中間の場合は、この列車の始発駅は"環状線"になる。(表示は環状)
								*/
								bLoop = true;
								aOuterDisplayContent.iEkiOrder = -2;
								aOuterDisplayContent.HatsuJikoku.setNull();
								//aRessyaPropertyBufferの駅Orderはその列車基準でおｋとする(同じ列車同士での比較が原則だから)
								aRessyaPropertyBuffer.iEkiOrder = iEkiOrder - 1;
								aRessyaPropertyBuffer.bLoop = true;
								break;
							}
						}
						ContRessyaPropertyBuffer.push_back(aRessyaPropertyBuffer);
						/**
							itrの終着駅まで検索しても、環状にならなかった場合は、
							前列車接続タイプを見て、前列車探索に入るかここで終了するかを決める
						*/
						if (bLoop)
						{
							break;
						}
						if (itrListOperationTableContent != ListOperationTableContent.begin())
						{
							auto itrListOperationTableContentPrev = itrListOperationTableContent;
							itrListOperationTableContentPrev--;
							if ((itrListOperationTableContent->eBeforeType == EBeforeAfterType::BeforeAfterType_ClassChange ||
								itrListOperationTableContent->eBeforeType == EBeforeAfterType::BeforeAfterType_PropertyChange ||
								itrListOperationTableContent->eBeforeType == EBeforeAfterType::BeforeAfterType_PropertySame) &&
								itrListOperationTableContentPrev->eAfterType == itrListOperationTableContent->eBeforeType)
							{
								//この列車が先頭ではなく、前タイプが種別変更・列車情報変更・同一列車扱いのいずれかで、
								//前の列車と一致しているのなら、前の列車の検索を行う。
								continue;
							}
							else
							{
								//この列車が先頭ではないが、前タイプが別列車、または前列車の後タイプと一致しない場合、
								//この列車が一体化の先頭となる
								break;
							}
						}
						else
						{
							//この列車が先頭なので、この列車が一体化の先頭となる
							break;
						}
					}

					/**
						ListEkiJikokuhyouContentTempPerONが組みあがったら、
						ContRessyaPropertyBufferとMapContRessyaPropertyBufferを突き合わせて
						必要に応じて置き換える
						また、この運番を内包するものがあったら、追加を行わない(bAddをfalseにする)
					*/
					bool bAdd = true;
					tstring strReplace = _T("");
					for (auto itr = MapContRessyaPropertyBuffer.begin(); itr != MapContRessyaPropertyBuffer.end()
						&& strReplace.empty() && bAdd; itr++)
					{
						vector<RessyaPropertyBuffer>& contRessyaPropertyBufferSearch = itr->second;
						for (int idxRPB = 0; idxRPB < (int)ContRessyaPropertyBuffer.size(); idxRPB++)
						{
							if (!ContRessyaPropertyBuffer[idxRPB].aRessyaProperty.isEqualTo(
								contRessyaPropertyBufferSearch[idxRPB].aRessyaProperty, false))
							{
								//idxRPB番目の列車自体が異なる場合は、異なる始発駅(具体的には、次列車の始発駅で分割しているパターン)なので、
								//置き換え対象にはならない。
								break;
							}
							else if (ContRessyaPropertyBuffer[idxRPB].iEkiOrder <
								contRessyaPropertyBufferSearch[idxRPB].iEkiOrder)
							{
								/**
									この運番の方が長い区間で運行されている場合、
									探索運番が路線外始発ではないかつ、
									探索運番の前列車がない場合(idxRPBが末尾の場合)
									(完全に探索運番がiEkiOrderで終了している場合)
									この運番で探索運番を置き換えます
									探索の前列車がある場合・探索運番が路線外始発の場合は、次運用の探索に映る
								*/
								if (contRessyaPropertyBufferSearch[idxRPB].iOuterEkiIndex < 0 &&
									contRessyaPropertyBufferSearch.size() == idxRPB + 1)
								{
									strReplace = itr->first;
								}
								break;
							}
							else if (ContRessyaPropertyBuffer[idxRPB].iEkiOrder >
								contRessyaPropertyBufferSearch[idxRPB].iEkiOrder)
							{
								/**
									この運番の方が短い区間で運行されている場合、
									この運番の前列車がない場合(idxRPBが末尾の場合)、路線外始発でもない場合は
									この運番は置き換えも追加も行いません
									この運番の前列車がある場合・この運番が路線外始発の場合は、次運用の探索に映る

								*/
								if (ContRessyaPropertyBuffer[idxRPB].iOuterEkiIndex < 0 &&
									ContRessyaPropertyBuffer.size() == idxRPB + 1)
								{
									bAdd = false;
								}
								break;
							}
							//この運番と探索運番の終着駅が同じ場合
							else if (ContRessyaPropertyBuffer[idxRPB].iOuterEkiIndex < 0 &&
								ContRessyaPropertyBuffer.size() == idxRPB + 1)
							{
								/**
									この運番の最初の列車の場合(除く路線外始発)は、
									この運番は探索運番に内包されている、もしくは一致しているので、
									置き換えも追加も行いません
								*/
								bAdd = false;
								break;
							}
							else if (contRessyaPropertyBufferSearch[idxRPB].iOuterEkiIndex < 0 &&
								contRessyaPropertyBufferSearch.size() == idxRPB + 1)
							{
								/**
									探索運番の最初の列車の場合(除く路線外始発)は、
									探索運番はこの運番に内包されているので、
									置き換えます
								*/
								strReplace = itr->first;
								break;
							}
							//この運番と探索運番が前列車ありと路線外始発のいずれか
							else if (ContRessyaPropertyBuffer[idxRPB].iOuterEkiIndex >= 0)
							{
								/**
									この運番が路線外始発の場合、
									探索運番も路線外始発で、始発駅が同じ場合は、一致しているの置き換えも追加も行いません
									それ以外の場合は、分岐しているので、次運用の探索に移ります
								*/
								if (ContRessyaPropertyBuffer[idxRPB].iOuterEkiIndex ==
									contRessyaPropertyBufferSearch[idxRPB].iOuterEkiIndex)
								{
									bAdd = false;
								}
								break;
							}
							else if (contRessyaPropertyBufferSearch[idxRPB].iOuterEkiIndex >= 0)
							{
								/**
									この運番が、前列車につながっていて、
									かつ探索運番が路線外始発の場合は、分岐しているので、次運用の探索に移ります
								*/
								break;
							}
							/**
								この運番と探索運番が共に前列車につながっている場合は、
								前列車同士での比較になります。
							*/
						}
					}

					if (!strReplace.empty())
					{
						MapOuterDisplayContentBuffer.erase(strReplace);
						MapContRessyaPropertyBuffer.erase(strReplace);
					}
					if (bAdd)
					{
						MapOuterDisplayContentBuffer[strOperationNumber] = aOuterDisplayContent;
						MapContRessyaPropertyBuffer[strOperationNumber] = ContRessyaPropertyBuffer;
					}
				}

				int iInsertPosition = 1;
				if (aOuterSearchElement.bIsConnectOrRelease)
				{
					iInsertPosition = 0;
				}
				for (auto itrOuterDisplayContent = MapOuterDisplayContentBuffer.begin();
					itrOuterDisplayContent != MapOuterDisplayContentBuffer.end(); itrOuterDisplayContent++, iInsertPosition--)
				{
#pragma omp critical(CustomizeRessyaIndex)
					{
						vector<CustomizeJikokuhyouContent>& contCustomizeJikokuhyouContent =
							m_pDedDia->getcontCustomizeRessyaIndex(aRessyaProperty.getRessyahoukou());
						for (int CustomizeJikokuhyouContentIndex = 0; CustomizeJikokuhyouContentIndex < (int)contCustomizeJikokuhyouContent.size(); CustomizeJikokuhyouContentIndex++)
						{
							if (contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].iRessyaIndexCont.empty())
							{
								continue;
							}
							if (iInsertPosition == 1)
							{
								if (contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].iRessyaIndexCont.front() == aRessyaProperty.getRessyaIndex())
								{
									//主編成の場合かつMapEkiJikokuhyouContentBufferの頭にあるものは、当該列車のCustomizeJikokuhyouContentを読み込み、そこに書き込みます。
									contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].ChakuJikoku = itrOuterDisplayContent->second.ChakuJikoku;
									contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].OuterShihatsuJikoku = itrOuterDisplayContent->second.HatsuJikoku;
									contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].iSihatsuEkiOrder = itrOuterDisplayContent->second.iEkiOrder;
									contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].iOuterShihatsuEkiIndex = itrOuterDisplayContent->second.iOuterEkiIndex;
									contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].eEBeforeType = itrOuterDisplayContent->second.eEBeforeAfterType;

									const CentDedRessya* pCentDedRessya =
										pCentDedRessyaConts[itrOuterDisplayContent->second.aRessyaProperty.getRessyahoukou()]
										->get(itrOuterDisplayContent->second.aRessyaProperty.getRessyaIndex());
									contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].iPrevRessyasyubetsuIndex = pCentDedRessya->getRessyasyubetsuIndex();
									contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].strPrevRessyabangou = pCentDedRessya->getRessyabangou();
									contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].strPrevRessyamei = pCentDedRessya->getRessyamei();
									contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].strPrevGousuu = pCentDedRessya->getGousuu();
									//contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].strPrevOperationNumber = aOuterSearchElement.strContOperationNumber;
									contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].strPrevOperationNumber = 
										pCentDedRessya->getOperationNumber(itrOuterDisplayContent->second.iJunctionEkiOrder - 1);

									break;
								}
							}
							else
							{
								bool bFound = false;
								for (int iRessyaIndex = 0; iRessyaIndex < (int)contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].iRessyaIndexCont.size(); iRessyaIndex++)
								{
									if (contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].iRessyaIndexCont[iRessyaIndex] == aRessyaProperty.getRessyaIndex())
									{
										//MapEkiJikokuhyouContentBufferの二番目以降、もしくは併合編成の場合は、当該列車のCustomizeJikokuhyouContentの直前に、併合列車として挿入します
										const CentDedRessya* pCentDedRessya =
											pCentDedRessyaConts[itrOuterDisplayContent->second.aRessyaProperty.getRessyahoukou()]
											->get(itrOuterDisplayContent->second.aRessyaProperty.getRessyaIndex());
										CustomizeJikokuhyouContent aCustomizeJikokuhyouContent(pCentDedRessya,true);
										aCustomizeJikokuhyouContent.iConnectEkiOrder = aOuterSearchElement.iEkiOrder;
										aCustomizeJikokuhyouContent.ChakuJikoku = itrOuterDisplayContent->second.ChakuJikoku;
										aCustomizeJikokuhyouContent.OuterShihatsuJikoku = itrOuterDisplayContent->second.HatsuJikoku;
										aCustomizeJikokuhyouContent.iSihatsuEkiOrder = itrOuterDisplayContent->second.iEkiOrder;
										aCustomizeJikokuhyouContent.iOuterShihatsuEkiIndex = itrOuterDisplayContent->second.iOuterEkiIndex;
										aCustomizeJikokuhyouContent.ePrevEkiatsukai = itrOuterDisplayContent->second.eEkiatsukai;
										aCustomizeJikokuhyouContent.iPrevRessyaTrackIndex = itrOuterDisplayContent->second.iRessyaTrackIndex;
										aCustomizeJikokuhyouContent.strPrevOperationNumber = aOuterSearchElement.strContOperationNumber;
										aCustomizeJikokuhyouContent.eEBeforeType = itrOuterDisplayContent->second.eEBeforeAfterType;

										contCustomizeJikokuhyouContent.insert(contCustomizeJikokuhyouContent.begin() + CustomizeJikokuhyouContentIndex + iInsertPosition,
											aCustomizeJikokuhyouContent);

										bFound = true;
										break;
									}
								}
								if (bFound)
								{
									break;
								}

							}

							//if (contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].iRessyaIndexCont.front() == aRessyaProperty.getRessyaIndex())
							//{
							//	if (iInsertPosition == -1)
							//	{
							//		//主編成の場合かつMapEkiJikokuhyouContentBufferの頭にあるものは、当該列車のCustomizeJikokuhyouContentを読み込み、そこに書き込みます。
							//		contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].ChakuJikoku = itrOuterDisplayContent->second.ChakuJikoku;
							//		contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].OuterShihatsuJikoku = itrOuterDisplayContent->second.HatsuJikoku;
							//		contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].iSihatsuEkiOrder = itrOuterDisplayContent->second.iEkiOrder;
							//		contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].iOuterShihatsuEkiIndex = itrOuterDisplayContent->second.iOuterEkiIndex;
							//	}
							//	else
							//	{
							//		//MapEkiJikokuhyouContentBufferの二番目以降、もしくは併合編成の場合は、当該列車のCustomizeJikokuhyouContentの直前に、併合列車として挿入します
							//		const CentDedRessya* pCentDedRessya =
							//			pCentDedRessyaConts[itrOuterDisplayContent->second.aRessyaProperty.getRessyahoukou()]
							//			->get(itrOuterDisplayContent->second.aRessyaProperty.getRessyaIndex());
							//		CustomizeJikokuhyouContent aCustomizeJikokuhyouContent(pCentDedRessya);
							//		aCustomizeJikokuhyouContent.iConnectEkiOrder = aOuterSearchElement.iEkiOrder;
							//		aCustomizeJikokuhyouContent.ChakuJikoku = itrOuterDisplayContent->second.ChakuJikoku;
							//		aCustomizeJikokuhyouContent.OuterShihatsuJikoku = itrOuterDisplayContent->second.HatsuJikoku;
							//		aCustomizeJikokuhyouContent.iSihatsuEkiOrder = itrOuterDisplayContent->second.iEkiOrder;
							//		aCustomizeJikokuhyouContent.iOuterShihatsuEkiIndex = itrOuterDisplayContent->second.iOuterEkiIndex;
							//		aCustomizeJikokuhyouContent.eEkiatsukai = itrOuterDisplayContent->second.eEkiatsukai;
							//		aCustomizeJikokuhyouContent.iRessyaTrackIndex = itrOuterDisplayContent->second.iRessyaTrackIndex;
							//		aCustomizeJikokuhyouContent.strOperationNumber = aOuterSearchElement.strContOperationNumber;

							//		contCustomizeJikokuhyouContent.insert(contCustomizeJikokuhyouContent.begin() + CustomizeJikokuhyouContentIndex + iInsertPosition,
							//			aCustomizeJikokuhyouContent);
							//	}
							//	break;
							//}
						}
					}
				}
			}

			//(3)路線外始発の列車を併合するパターン(☆1,2,4)
			unordered_multimap<int, CustomizeJikokuhyouContent> contOuterConnectInsertList = m_contOuterConnectInsertList[iRessyahoukou][iEkiOrder];
			auto itrOuterConnectInsertList = contOuterConnectInsertList.begin();
			for (; itrOuterConnectInsertList != contOuterConnectInsertList.end(); itrOuterConnectInsertList++)
			{
				//itrOuterConnectInsertList->first : 併合先(挿入位置)の列車Index
				//itrOuterConnectInsertList->second : 挿入するCustomizeJikokuhyouContent

				vector<CustomizeJikokuhyouContent>& contCustomizeJikokuhyouContent =
					m_pDedDia->getcontCustomizeRessyaIndex((ERessyahoukou)iRessyahoukou);
				bool bInserted = false;
				for (int CustomizeJikokuhyouContentIndex = 0; CustomizeJikokuhyouContentIndex < (int)contCustomizeJikokuhyouContent.size() && !bInserted; CustomizeJikokuhyouContentIndex++)
				{
					for (int idxc = 0; idxc < (int)contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].iRessyaIndexCont.size() && !bInserted; idxc++)
					{
						if (contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].iRessyaIndexCont[idxc] == itrOuterConnectInsertList->first)
						{
							contCustomizeJikokuhyouContent.insert(contCustomizeJikokuhyouContent.begin() + CustomizeJikokuhyouContentIndex,
								itrOuterConnectInsertList->second);
							bInserted = true;
						}
					}
				}
			}
		}



		//After+Releaseは上位の駅から順に行う
		for (int iEkiOrder = 0; iEkiOrder < pCentDedEkiCont->size(); iEkiOrder++)
		{
			//(4)分割で同方向順並びのパターン(☆5)
			unordered_multimap<int, int> contReleaseMoveList = m_contReleaseMoveList[iRessyahoukou][iEkiOrder];
			auto itrReleaseMoveList = contReleaseMoveList.begin();
			for (; itrReleaseMoveList != contReleaseMoveList.end(); itrReleaseMoveList++)
			{
				//itrReleaseMoveList->first : 分割元の列車Index
				//itrReleaseMoveList->second : 分割列車の列車Index

				//まずは、前列車と次列車それぞれのCustomizeJikokuhyouContentを探す。
				vector<CustomizeJikokuhyouContent>& contCustomizeJikokuhyouContent =
					m_pDedDia->getcontCustomizeRessyaIndex((ERessyahoukou)iRessyahoukou);
				int iCustomizeIndexPrev = -1;
				int iCustomizeIndexNext = -1;
				for (int idx = 0; idx < (int)contCustomizeJikokuhyouContent.size(); idx++)
				{
					for (int idxc = 0; idxc < (int)contCustomizeJikokuhyouContent[idx].iRessyaIndexCont.size(); idxc++)
					{
						if (contCustomizeJikokuhyouContent[idx].iRessyaIndexCont[idxc] ==
							itrReleaseMoveList->first)
						{
							iCustomizeIndexPrev = idx;
						}
						if (contCustomizeJikokuhyouContent[idx].iRessyaIndexCont[idxc] ==
							itrReleaseMoveList->second)
						{
							iCustomizeIndexNext = idx;
						}

					}
				}
				if (iCustomizeIndexPrev != -1 &&
					iCustomizeIndexNext != -1)
				{
					//次列車にReleaseEkiOrderの設定をします
					contCustomizeJikokuhyouContent[iCustomizeIndexNext].iReleaseEkiOrder = iEkiOrder;

					//次列車を前列車の右に移動します
					if (iCustomizeIndexPrev > iCustomizeIndexNext)
					{
						contCustomizeJikokuhyouContent.insert(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexPrev + 1,
							contCustomizeJikokuhyouContent[iCustomizeIndexNext]);
						contCustomizeJikokuhyouContent.erase(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexNext);
					}
					else if (iCustomizeIndexPrev < iCustomizeIndexNext)
					{
						CustomizeJikokuhyouContent temp = contCustomizeJikokuhyouContent[iCustomizeIndexNext];
						contCustomizeJikokuhyouContent.erase(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexNext);
						contCustomizeJikokuhyouContent.insert(contCustomizeJikokuhyouContent.begin() + iCustomizeIndexPrev + 1,
							temp);
					}
				}
			}

			//(5)分割・併合・一本化で、逆方向または同方向逆並びのパターン(☆7-2)
			vector<OuterSearchElement>& contAfterContinueList = m_contAfterContinueList[iRessyahoukou][iEkiOrder];
			int iAfterSize = contAfterContinueList.size();
			for (int iAfterIndex = 0; iAfterIndex < iAfterSize; iAfterIndex++)
			{
				OuterSearchElement& aOuterSearchElement = contAfterContinueList[iAfterIndex];

				CdDedRessyaProperty aRessyaProperty = aOuterSearchElement.aRessyaProperty;
				//const CentDedRessya* pCentDedRessya =
				//	pCentDedRessyaConts[aRessyaProperty.getRessyahoukou()]
				//	->get(aRessyaProperty.getRessyaIndex());
				///**
				//	次に、各運用番号に対して行き先を取得する。
				//	その際、主編成の終点から、種別変更・分割で先の列車につながっている場合、
				//	終点で解結して路線外終着になる場合は、上で獲得した主編成の終着駅を置き換える。
				//	なお、主編成が路線外終着の場合は置き換えは起こらない。
				//*/

				unordered_map<tstring, vector<RessyaPropertyBuffer>> MapContRessyaPropertyBuffer;
				unordered_map<tstring, OuterDisplayContent> MapOuterDisplayContentBuffer;
				for (int idx = 0; idx < (int)aOuterSearchElement.strContOperationNumber.size(); idx++)
				{
					tstring strOperationNumber = aOuterSearchElement.strContOperationNumber[idx];

					if (strOperationNumber.empty())
					{
						continue;
					}
					list<OperationTableContent>& ListOperationTableContent = contOperationTableContent[strOperationNumber];
					auto itrListOperationTableContent = ListOperationTableContent.begin();
					for (; itrListOperationTableContent != ListOperationTableContent.end(); itrListOperationTableContent++)
					{
						if (!itrListOperationTableContent->aRessyaProperty.isEqualTo(aRessyaProperty, false))
						{
							continue;
						}
						if (itrListOperationTableContent->iOuterShuchakuekiIndex < 0)
						{
							itrListOperationTableContent++;//最後に一回インクリメントして、当該列車の"次"に移動する。
						}
						break;
					}
					if (itrListOperationTableContent == ListOperationTableContent.end())
					{
						//aRessyaPropertyが一致するものが見つからなかったらこの運番に対しての表示は無しにする
						continue;
					}
					vector<RessyaPropertyBuffer > ContRessyaPropertyBuffer;

					OuterDisplayContent aOuterDisplayContent;

					/**
						この列車のルートを調べる、ルートに輪ができ、輪の終点が当駅なら、この列車の行き先は"環状"になる。
						輪の終点が当駅以外なら、この列車の行き先は"環状線"になる。
					*/
					vector<int> RouteEkiIndex;
					bool bLoop = false;
					bool bFirst = true;

					for (; itrListOperationTableContent != ListOperationTableContent.end(); itrListOperationTableContent++)
					{

						const CentDedRessya* pCentDedRessyaSearch =
							pCentDedRessyaConts[itrListOperationTableContent->aRessyaProperty.getRessyahoukou()]
							->get(itrListOperationTableContent->aRessyaProperty.getRessyaIndex());

						if (bFirst)
						{
							//最初の列車(当該列車の次の列車)の場合、列車種別、当該列車終着駅の発時刻、駅扱い、aRessyaPropertyを取得します
							aOuterDisplayContent.iRessyaSyubetsu = pCentDedRessyaSearch->getRessyasyubetsuIndex();
							aOuterDisplayContent.HatsuJikoku = pCentDedRessyaSearch->getCentDedEkiJikoku(
								itrListOperationTableContent->iSihatsuEkiOrder).getVirtualHatsujikoku();
							aOuterDisplayContent.eEkiatsukai = pCentDedRessyaSearch->getCentDedEkiJikoku(
								itrListOperationTableContent->iSihatsuEkiOrder).getEkiatsukai();
							aOuterDisplayContent.iRessyaTrackIndex = pCentDedRessyaSearch->getCentDedEkiJikoku(
								itrListOperationTableContent->iSihatsuEkiOrder).getRessyaTrackIndex();
							aOuterDisplayContent.aRessyaProperty = itrListOperationTableContent->aRessyaProperty;

							aOuterDisplayContent.eEBeforeAfterType = itrListOperationTableContent->eBeforeType;
							aOuterDisplayContent.iJunctionEkiOrder = itrListOperationTableContent->iSihatsuEkiOrder;

							bFirst = false;
						}
						//行き先をitrで上書きする。
						//終着駅Orderは、一度駅Indexに直してから、元々の列車方向に合わせたOrderに変更しなおす。
						int iSyuuchakuEkiIndexSearch = pCentDedRessyaSearch->EkiIndexOfEkiOrder(itrListOperationTableContent->iSyuuchakuEkiOrder);
						aOuterDisplayContent.iEkiOrder = pCentDedEkiCont->EkiOrderOfEkiIndex(aRessyaProperty.getRessyahoukou(), iSyuuchakuEkiIndexSearch);
						aOuterDisplayContent.iOuterEkiIndex = itrListOperationTableContent->iOuterShuchakuekiIndex;
						if (aOuterDisplayContent.iOuterEkiIndex >= 0)
						{
							aOuterDisplayContent.ChakuJikoku = itrListOperationTableContent->OuterShuchakuJikoku;
						}
						else
						{
							aOuterDisplayContent.ChakuJikoku = pCentDedRessyaSearch->getCentDedEkiJikoku(itrListOperationTableContent->iSyuuchakuEkiOrder).getVirtualChakujikoku();
						}

						RessyaPropertyBuffer aRessyaPropertyBuffer;
						//aRessyaPropertyBufferの終着駅Orderはその列車基準でおｋとする(同じ列車同士で比較し、終着駅の遠さを見る必要があるので)
						aRessyaPropertyBuffer.iEkiOrder = itrListOperationTableContent->iSyuuchakuEkiOrder;
						aRessyaPropertyBuffer.iOuterEkiIndex = itrListOperationTableContent->iOuterShuchakuekiIndex;
						aRessyaPropertyBuffer.aRessyaProperty = itrListOperationTableContent->aRessyaProperty;

						int iEkiOrder = itrListOperationTableContent->iSihatsuEkiOrder;
						for (; iEkiOrder < itrListOperationTableContent->iSyuuchakuEkiOrder; iEkiOrder++)
						{
							if (!pCentDedRessyaSearch->isRunBetweenNextEki(iEkiOrder))
							{
								/**
									iEkiOrderと次の駅間を運転していない場合は、
									運行なし区間を飛ばし、次に運行ありになる区間へ移る、
									その際、運行なしの前後が同一駅(分岐・環状関係)であることを確認する。
								*/
								int iEkiOrderNext = pCentDedRessyaSearch->getRunBetweenEkiForward(iEkiOrder);
								if (iEkiOrderNext >= 0 &&
									iEkiOrderNext < itrListOperationTableContent->iSyuuchakuEkiOrder &&
									pCentDedEkiCont->isSameBrunchLoopGroup(iEkiOrder, iEkiOrderNext, pCentDedRessyaSearch->getRessyahoukou()))
								{
									iEkiOrder = iEkiOrderNext;
								}
								else
								{
									break;
								}
							}

							int iEkiIndexPrev = iEkiOrderTable[iEkiOrder][(int)pCentDedRessyaSearch->getRessyahoukou()];
							int iEkiIndexNext = iEkiOrderTable[iEkiOrder + 1][(int)pCentDedRessyaSearch->getRessyahoukou()];
							int iPosition = -1;
							for (int iSearchIndex = 0; iSearchIndex < (int)RouteEkiIndex.size(); iSearchIndex++)
							{
								if (RouteEkiIndex[iSearchIndex] == iEkiIndexNext)
								{
									iPosition = iSearchIndex;
									break;
								}
							}
							if (iPosition == -1)
							{
								/**
									iPositionが-1の場合は、RouteEkiIndexに前駅のIndexを追加して次へ
								*/
								RouteEkiIndex.push_back(iEkiIndexPrev);
							}
							else if (iPosition == RouteEkiIndex.size() - 1)
							{
								/**
									iPositionが末尾の場合は、折り返している状態なので、RouteEkiIndexの末尾要素を削除して次へ。
								*/
								RouteEkiIndex.pop_back();
							}
							else if (iPosition == 0)
							{
								/**
									iPositionが先頭(かつ末尾ではない)の場合は、この列車の行き先は"環状"になる。
								*/
								bLoop = true;
								aOuterDisplayContent.iEkiOrder = -1;
								aOuterDisplayContent.ChakuJikoku.setNull();
								//aRessyaPropertyBufferの駅Orderはその列車基準でおｋとする(同じ列車同士での比較が原則だから)
								aRessyaPropertyBuffer.iEkiOrder = iEkiOrder + 1;
								aRessyaPropertyBuffer.bLoop = true;
								break;
							}
							else
							{
								/**
									iPositionが中間の場合は、この列車の行き先は"環状線"になる。(表示は環状)
								*/
								bLoop = true;
								aOuterDisplayContent.iEkiOrder = -2;
								aOuterDisplayContent.ChakuJikoku.setNull();
								//aRessyaPropertyBufferの駅Orderはその列車基準でおｋとする(同じ列車同士での比較が原則だから)
								aRessyaPropertyBuffer.iEkiOrder = iEkiOrder + 1;
								aRessyaPropertyBuffer.bLoop = true;
								break;
							}
						}
						ContRessyaPropertyBuffer.push_back(aRessyaPropertyBuffer);
						/**
							itrの終着駅まで検索しても、環状にならなかった場合は、
							次列車接続タイプを見て、次列車探索に入るかここで終了するかを決める
						*/
						if (bLoop)
						{
							break;
						}
						auto itrListOperationTableContentNext = itrListOperationTableContent;
						itrListOperationTableContentNext++;
						if (itrListOperationTableContentNext != ListOperationTableContent.end() &&
							(itrListOperationTableContent->eAfterType == EBeforeAfterType::BeforeAfterType_ClassChange ||
								itrListOperationTableContent->eAfterType == EBeforeAfterType::BeforeAfterType_PropertyChange ||
								itrListOperationTableContent->eAfterType == EBeforeAfterType::BeforeAfterType_PropertySame) &&
							itrListOperationTableContentNext->eBeforeType == itrListOperationTableContent->eAfterType)
						{
							//この列車が末尾ではなく、後タイプが種別変更・列車情報変更・同一列車扱いのいずれかで、
							//次の列車と一致しているのなら、次の列車の検索を行う。
							continue;
						}
						else
						{
							//この列車が末尾、または後タイプが別列車、または次列車の前タイプと一致しない場合、
							//この列車が一体化の末尾となる
							break;
						}
					}

					/**
						ListEkiJikokuhyouContentTempPerONが組みあがったら、
						ContRessyaPropertyBufferとMapContRessyaPropertyBufferを突き合わせて
						必要に応じて置き換える
						また、この運番を内包するものがあったら、追加を行わない(bAddをfalseにする)
					*/
					bool bAdd = true;
					tstring strReplace = _T("");
					for (auto itr = MapContRessyaPropertyBuffer.begin(); itr != MapContRessyaPropertyBuffer.end()
						&& strReplace.empty() && bAdd; itr++)
					{
						vector<RessyaPropertyBuffer>& contRessyaPropertyBufferSearch = itr->second;
						for (int idxRPB = 0; idxRPB < (int)ContRessyaPropertyBuffer.size(); idxRPB++)
						{
							if (!ContRessyaPropertyBuffer[idxRPB].aRessyaProperty.isEqualTo(
								contRessyaPropertyBufferSearch[idxRPB].aRessyaProperty, false))
							{
								//idxRPB番目の列車自体が異なる場合は、異なる行き先(具体的には、前列車の終着駅で分割しているパターン)なので、
								//置き換え対象にはならない。
								break;
							}
							else if (ContRessyaPropertyBuffer[idxRPB].iEkiOrder >
								contRessyaPropertyBufferSearch[idxRPB].iEkiOrder)
							{
								/**
									この運番の方が長い区間で運行されている場合、
									探索運番が路線外終着ではないかつ、
									探索運番の次列車がない場合(idxRPBが末尾の場合)
									(完全に探索運番がiSyuuchakuEkiOrderで終了している場合)
									この運番で探索運番を置き換えます
									探索の次列車がある場合・探索運番が路線外終着の場合は、次運用の探索に映る
								*/
								if (contRessyaPropertyBufferSearch[idxRPB].iOuterEkiIndex < 0 &&
									contRessyaPropertyBufferSearch.size() == idxRPB + 1)
								{
									strReplace = itr->first;
								}
								break;
							}
							else if (ContRessyaPropertyBuffer[idxRPB].iEkiOrder <
								contRessyaPropertyBufferSearch[idxRPB].iEkiOrder)
							{
								/**
									この運番の方が短い区間で運行されている場合、
									この運番の次列車がない場合(idxRPBが末尾の場合)、路線外終着でもない場合は
									この運番は置き換えも追加も行いません
									この運番の次列車がある場合・この運番が路線外終着の場合は、次運用の探索に映る

								*/
								if (ContRessyaPropertyBuffer[idxRPB].iOuterEkiIndex < 0 &&
									ContRessyaPropertyBuffer.size() == idxRPB + 1)
								{
									bAdd = false;
								}
								break;
							}
							//この運番と探索運番の終着駅が同じ場合
							else if (ContRessyaPropertyBuffer[idxRPB].iOuterEkiIndex < 0 &&
								ContRessyaPropertyBuffer.size() == idxRPB + 1)
							{
								/**
									この運番の最終列車の場合(除く路線外終着)は、
									この運番は探索運番に内包されている、もしくは一致しているので、
									置き換えも追加も行いません
								*/
								bAdd = false;
								break;
							}
							else if (contRessyaPropertyBufferSearch[idxRPB].iOuterEkiIndex < 0 &&
								contRessyaPropertyBufferSearch.size() == idxRPB + 1)
							{
								/**
									探索運番の最終列車の場合(除く路線外終着)は、
									探索運番はこの運番に内包されているので、
									置き換えます
								*/
								strReplace = itr->first;
								break;
							}
							//この運番と探索運番が次列車ありと路線外終着のいずれか
							else if (ContRessyaPropertyBuffer[idxRPB].iOuterEkiIndex >= 0)
							{
								/**
									この運番が路線外終着の場合、
									探索運番も路線外終着で、終着駅が同じ場合は、一致しているの置き換えも追加も行いません
									それ以外の場合は、分岐しているので、次運用の探索に移ります
								*/
								if (ContRessyaPropertyBuffer[idxRPB].iOuterEkiIndex ==
									contRessyaPropertyBufferSearch[idxRPB].iOuterEkiIndex)
								{
									bAdd = false;
								}
								break;
							}
							else if (contRessyaPropertyBufferSearch[idxRPB].iOuterEkiIndex >= 0)
							{
								/**
									この運番が、次列車につながっていて、
									かつ探索運番が路線外終着の場合は、分岐しているので、次運用の探索に移ります
								*/
								break;
							}
							/**
								この運番と探索運番が共に次列車につながっている場合は、
								次列車同士での比較になります。
							*/
						}
					}

					if (!strReplace.empty())
					{
						MapOuterDisplayContentBuffer.erase(strReplace);
						MapContRessyaPropertyBuffer.erase(strReplace);
					}
					if (bAdd)
					{
						MapOuterDisplayContentBuffer[strOperationNumber] = aOuterDisplayContent;
						MapContRessyaPropertyBuffer[strOperationNumber] = ContRessyaPropertyBuffer;
					}
				}

				int iInsertPosition = 0;
				if (aOuterSearchElement.bIsConnectOrRelease)
				{
					iInsertPosition = 1;
				}
				for (auto itrOuterDisplayContent = MapOuterDisplayContentBuffer.begin();
					itrOuterDisplayContent != MapOuterDisplayContentBuffer.end(); itrOuterDisplayContent++, iInsertPosition++)
				{
#pragma omp critical(CustomizeRessyaIndex)
					{
						vector<CustomizeJikokuhyouContent>& contCustomizeJikokuhyouContent =
							m_pDedDia->getcontCustomizeRessyaIndex(aRessyaProperty.getRessyahoukou());
						for (int CustomizeJikokuhyouContentIndex = 0; CustomizeJikokuhyouContentIndex < (int)contCustomizeJikokuhyouContent.size(); CustomizeJikokuhyouContentIndex++)
						{
							if (contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].iRessyaIndexCont.empty())
							{
								continue;
							}
							if (iInsertPosition == 0)
							{
								if (contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].iRessyaIndexCont.back() == aRessyaProperty.getRessyaIndex())
								{
									//主編成の場合かつMapEkiJikokuhyouContentBufferの頭にあるものは、当該列車のCustomizeJikokuhyouContentを読み込み、そこに書き込みます。
									contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].HatsuJikoku = itrOuterDisplayContent->second.HatsuJikoku;
									contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].OuterShuchakuJikoku = itrOuterDisplayContent->second.ChakuJikoku;
									contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].iSyuuchakuEkiOrder = itrOuterDisplayContent->second.iEkiOrder;
									contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].iOuterShuchakuEkiIndex = itrOuterDisplayContent->second.iOuterEkiIndex;
									contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].eEAfterType = itrOuterDisplayContent->second.eEBeforeAfterType;

									const CentDedRessya* pCentDedRessya =
										pCentDedRessyaConts[itrOuterDisplayContent->second.aRessyaProperty.getRessyahoukou()]
										->get(itrOuterDisplayContent->second.aRessyaProperty.getRessyaIndex());
									contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].iRessyasyubetsuIndex = pCentDedRessya->getRessyasyubetsuIndex();
									contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].strRessyabangou = pCentDedRessya->getRessyabangou();
									contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].strRessyamei = pCentDedRessya->getRessyamei();
									contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].strGousuu = pCentDedRessya->getGousuu();
									//contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].strOperationNumber = aOuterSearchElement.strContOperationNumber;
									contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].strOperationNumber = 
										pCentDedRessya->getOperationNumber(itrOuterDisplayContent->second.iJunctionEkiOrder);

									break;
								}
							}
							else
							{
								bool bFound = false;
								for (int iRessyaIndex = 0; iRessyaIndex < (int)contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].iRessyaIndexCont.size(); iRessyaIndex++)
								{
									if (contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].iRessyaIndexCont[iRessyaIndex] == aRessyaProperty.getRessyaIndex())
									{
										//MapEkiJikokuhyouContentBufferの二番目以降、もしくは解結編成の場合は、当該列車のCustomizeJikokuhyouContentの直後に、分割列車として挿入します
										const CentDedRessya* pCentDedRessya =
											pCentDedRessyaConts[itrOuterDisplayContent->second.aRessyaProperty.getRessyahoukou()]
											->get(itrOuterDisplayContent->second.aRessyaProperty.getRessyaIndex());
										CustomizeJikokuhyouContent aCustomizeJikokuhyouContent(pCentDedRessya,false);
										aCustomizeJikokuhyouContent.iReleaseEkiOrder = aOuterSearchElement.iEkiOrder;
										aCustomizeJikokuhyouContent.HatsuJikoku = itrOuterDisplayContent->second.HatsuJikoku;
										aCustomizeJikokuhyouContent.OuterShuchakuJikoku = itrOuterDisplayContent->second.ChakuJikoku;
										aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder = itrOuterDisplayContent->second.iEkiOrder;
										aCustomizeJikokuhyouContent.iOuterShuchakuEkiIndex = itrOuterDisplayContent->second.iOuterEkiIndex;
										aCustomizeJikokuhyouContent.eEkiatsukai = itrOuterDisplayContent->second.eEkiatsukai;
										aCustomizeJikokuhyouContent.iRessyaTrackIndex = itrOuterDisplayContent->second.iRessyaTrackIndex;
										aCustomizeJikokuhyouContent.strOperationNumber = aOuterSearchElement.strContOperationNumber;
										aCustomizeJikokuhyouContent.eEAfterType = itrOuterDisplayContent->second.eEBeforeAfterType;

										contCustomizeJikokuhyouContent.insert(contCustomizeJikokuhyouContent.begin() + CustomizeJikokuhyouContentIndex + iInsertPosition,
											aCustomizeJikokuhyouContent);

										bFound = true;
										break;
									}
								}
								if (bFound)
								{
									break;
								}
							}
							//if (contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].iRessyaIndexCont.back() == aRessyaProperty.getRessyaIndex())
							//{
							//	if (iInsertPosition == 0)
							//	{
							//		//主編成の場合かつMapEkiJikokuhyouContentBufferの頭にあるものは、当該列車のCustomizeJikokuhyouContentを読み込み、そこに書き込みます。
							//		contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].HatsuJikoku = itrOuterDisplayContent->second.HatsuJikoku;
							//		contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].OuterShuchakuJikoku = itrOuterDisplayContent->second.ChakuJikoku;
							//		contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].iSyuuchakuEkiOrder = itrOuterDisplayContent->second.iEkiOrder;
							//		contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].iOuterShuchakuEkiIndex = itrOuterDisplayContent->second.iOuterEkiIndex;
							//	}
							//	else
							//	{
							//		//MapEkiJikokuhyouContentBufferの二番目以降、もしくは解結編成の場合は、当該列車のCustomizeJikokuhyouContentの直後に、分割列車として挿入します
							//		const CentDedRessya* pCentDedRessya =
							//			pCentDedRessyaConts[itrOuterDisplayContent->second.aRessyaProperty.getRessyahoukou()]
							//			->get(itrOuterDisplayContent->second.aRessyaProperty.getRessyaIndex());
							//		CustomizeJikokuhyouContent aCustomizeJikokuhyouContent(pCentDedRessya);
							//		aCustomizeJikokuhyouContent.iReleaseEkiOrder = aOuterSearchElement.iEkiOrder;
							//		aCustomizeJikokuhyouContent.HatsuJikoku = itrOuterDisplayContent->second.HatsuJikoku;
							//		aCustomizeJikokuhyouContent.OuterShuchakuJikoku = itrOuterDisplayContent->second.ChakuJikoku;
							//		aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder = itrOuterDisplayContent->second.iEkiOrder;
							//		aCustomizeJikokuhyouContent.iOuterShuchakuEkiIndex = itrOuterDisplayContent->second.iOuterEkiIndex;
							//		aCustomizeJikokuhyouContent.eEkiatsukai = itrOuterDisplayContent->second.eEkiatsukai;
							//		aCustomizeJikokuhyouContent.iRessyaTrackIndex = itrOuterDisplayContent->second.iRessyaTrackIndex;
							//		aCustomizeJikokuhyouContent.strOperationNumber = aOuterSearchElement.strContOperationNumber;

							//		contCustomizeJikokuhyouContent.insert(contCustomizeJikokuhyouContent.begin() + CustomizeJikokuhyouContentIndex + iInsertPosition,
							//			aCustomizeJikokuhyouContent);
							//	}
							//	break;
							//}
						}
					}
				}
			}

			//(6)路線外終着の列車を分割するパターン(☆3)
			unordered_multimap<int, CustomizeJikokuhyouContent> contOuterReleaseInsertList = m_contOuterReleaseInsertList[iRessyahoukou][iEkiOrder];
			auto itrOuterReleaseInsertList = contOuterReleaseInsertList.begin();
			for (; itrOuterReleaseInsertList != contOuterReleaseInsertList.end(); itrOuterReleaseInsertList++)
			{
				//itrOuterConnectInsertList->first : 分割元(挿入位置)の列車Index
				//itrOuterConnectInsertList->second : 挿入するCustomizeJikokuhyouContent

				vector<CustomizeJikokuhyouContent>& contCustomizeJikokuhyouContent =
					m_pDedDia->getcontCustomizeRessyaIndex((ERessyahoukou)iRessyahoukou);
				bool bInserted = false;
				for (int CustomizeJikokuhyouContentIndex = 0; CustomizeJikokuhyouContentIndex < (int)contCustomizeJikokuhyouContent.size() && !bInserted; CustomizeJikokuhyouContentIndex++)
				{
					for (int idxc = 0; idxc < (int)contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].iRessyaIndexCont.size() && !bInserted; idxc++)
					{
						if (contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].iRessyaIndexCont[idxc] == itrOuterReleaseInsertList->first)
						{
							contCustomizeJikokuhyouContent.insert(contCustomizeJikokuhyouContent.begin() + CustomizeJikokuhyouContentIndex + 1,
								itrOuterReleaseInsertList->second);
							bInserted = true;
						}
					}
				}
			}
		}
	}






//
//	int iBeforeSize = m_contBeforeContinueList.size();
//	for (int iBeforeIndex = 0; iBeforeIndex < iBeforeSize; iBeforeIndex++)
//	{
//		OuterSearchElement& aOuterSearchElement = m_contBeforeContinueList[iBeforeIndex];
//
//		CdDedRessyaProperty aRessyaProperty = aOuterSearchElement.aRessyaProperty;
//		//const CentDedRessya* pCentDedRessya =
//		//	pCentDedRessyaConts[aRessyaProperty.getRessyahoukou()]
//		//	->get(aRessyaProperty.getRessyaIndex());
//		///**
//		//	次に、各運用番号に対して行き先を取得する。
//		//	その際、主編成の終点から、種別変更・分割で先の列車につながっている場合、
//		//	終点で解結して路線外終着になる場合は、上で獲得した主編成の終着駅を置き換える。
//		//	なお、主編成が路線外終着の場合は置き換えは起こらない。
//		//*/
//
//		unordered_map<tstring, vector<RessyaPropertyBuffer>> MapContRessyaPropertyBuffer;
//		unordered_map<tstring, OuterDisplayContent> MapOuterDisplayContentBuffer;
//		for (int idx = 0; idx < (int)aOuterSearchElement.strContOperationNumber.size(); idx++)
//		{
//			tstring strOperationNumber = aOuterSearchElement.strContOperationNumber[idx];
//
//			if (strOperationNumber.empty())
//			{
//				continue;
//			}
//			list<OperationTableContent>& ListOperationTableContent = contOperationTableContent[strOperationNumber];
//			auto itrListOperationTableContent = ListOperationTableContent.begin();
//			for (; itrListOperationTableContent != ListOperationTableContent.end(); itrListOperationTableContent++)
//			{
//				if (!itrListOperationTableContent->aRessyaProperty.isEqualTo(aRessyaProperty, false))
//				{
//					continue;
//				}
//				if (itrListOperationTableContent->iOuterShihatsuekiIndex < 0)
//				{
//					itrListOperationTableContent--;//最後に一回デクリメントして、当該列車の"前"に移動する。
//				}
//				break;
//			}
//			if (itrListOperationTableContent == ListOperationTableContent.end())
//			{
//				//aRessyaPropertyが一致するものが見つからなかったらこの運番に対しての表示は無しにする
//				continue;
//			}
//			vector<RessyaPropertyBuffer > ContRessyaPropertyBuffer;
//
//			OuterDisplayContent aOuterDisplayContent;
//
//			/**
//				この列車のルートを調べる、ルートに輪ができ、輪の始点が当駅なら、この列車の始発駅は"環状"になる。
//				輪の始点が当駅以外なら、この列車の始発駅は"環状線"になる。
//			*/
//			vector<int> RouteEkiIndex;
//			bool bLoop = false;
//			bool bFirst = true;
//
//			for (; /*itrListOperationTableContent != ListOperationTableContent.end()*/; itrListOperationTableContent--)
//			{
//
//				const CentDedRessya* pCentDedRessyaSearch =
//					pCentDedRessyaConts[itrListOperationTableContent->aRessyaProperty.getRessyahoukou()]
//					->get(itrListOperationTableContent->aRessyaProperty.getRessyaIndex());
//
//				if (bFirst)
//				{
//					//最初の列車(当該列車の前の列車)の場合、列車種別、当該列車終着駅の発時刻、駅扱い、aRessyaPropertyを取得します
//					aOuterDisplayContent.iRessyaSyubetsu = pCentDedRessyaSearch->getRessyasyubetsuIndex();
//					aOuterDisplayContent.ChakuJikoku = pCentDedRessyaSearch->getCentDedEkiJikoku(
//						itrListOperationTableContent->iSyuuchakuEkiOrder).getVirtualChakujikoku();
//					aOuterDisplayContent.eEkiatsukai = pCentDedRessyaSearch->getCentDedEkiJikoku(
//						itrListOperationTableContent->iSyuuchakuEkiOrder).getEkiatsukai();
//					aOuterDisplayContent.iRessyaTrackIndex = pCentDedRessyaSearch->getCentDedEkiJikoku(
//						itrListOperationTableContent->iSyuuchakuEkiOrder).getRessyaTrackIndex();
//					aOuterDisplayContent.aRessyaProperty = itrListOperationTableContent->aRessyaProperty;
//					bFirst = false;
//				}
//				//始発駅をitrListOperationTableContentで上書きする。
//				//終着駅Orderは、一度駅Indexに直してから、元々の列車方向に合わせたOrderに変更しなおす。
//				int iSihatsuEkiIndexSearch = pCentDedRessyaSearch->EkiIndexOfEkiOrder(itrListOperationTableContent->iSihatsuEkiOrder);
//				aOuterDisplayContent.iEkiOrder = pCentDedEkiCont->EkiOrderOfEkiIndex(aRessyaProperty.getRessyahoukou(), iSihatsuEkiIndexSearch);
//				aOuterDisplayContent.iOuterEkiIndex = itrListOperationTableContent->iOuterShihatsuekiIndex;
//				if (aOuterDisplayContent.iOuterEkiIndex >= 0)
//				{
//					aOuterDisplayContent.HatsuJikoku = itrListOperationTableContent->OuterShihatsuJikoku;
//				}
//				else
//				{
//					aOuterDisplayContent.HatsuJikoku = pCentDedRessyaSearch->getCentDedEkiJikoku(itrListOperationTableContent->iSihatsuEkiOrder).getVirtualHatsujikoku();
//				}
//
//				RessyaPropertyBuffer aRessyaPropertyBuffer;
//				//aRessyaPropertyBufferの始発駅Orderはその列車基準でおｋとする(同じ列車同士で比較し、始発駅の遠さを見る必要があるので)
//				aRessyaPropertyBuffer.iEkiOrder = itrListOperationTableContent->iSihatsuEkiOrder;
//				aRessyaPropertyBuffer.iOuterEkiIndex = itrListOperationTableContent->iOuterShihatsuekiIndex;
//				aRessyaPropertyBuffer.aRessyaProperty = itrListOperationTableContent->aRessyaProperty;
//
//				int iEkiOrder = itrListOperationTableContent->iSyuuchakuEkiOrder;
//				for (; iEkiOrder > itrListOperationTableContent->iSihatsuEkiOrder; iEkiOrder--)
//				{
//					if (!pCentDedRessyaSearch->isRunBetweenNextEki(iEkiOrder - 1))
//					{
//						/**
//							iEkiOrderと前の駅間を運転していない場合は、
//							運行なし区間を飛ばし、次に運行ありになる区間へ移る、
//							その際、運行なしの前後が同一駅(分岐・環状関係)であることを確認する。
//						*/
//						int iEkiOrderPrev = pCentDedRessyaSearch->getRunBetweenEkiBackward(iEkiOrder);
//						if (iEkiOrderPrev >= 0 &&
//							iEkiOrderPrev > itrListOperationTableContent->iSihatsuEkiOrder &&
//							pCentDedEkiCont->isSameBrunchLoopGroup(iEkiOrder, iEkiOrderPrev, pCentDedRessyaSearch->getRessyahoukou()))
//						{
//							iEkiOrder = iEkiOrderPrev;
//						}
//						else
//						{
//							break;
//						}
//					}
//
//					int iEkiIndexPrev = iEkiOrderTable[iEkiOrder - 1][(int)pCentDedRessyaSearch->getRessyahoukou()];
//					int iEkiIndexNext = iEkiOrderTable[iEkiOrder][(int)pCentDedRessyaSearch->getRessyahoukou()];
//					int iPosition = -1;
//					for (int iSearchIndex = 0; iSearchIndex < (int)RouteEkiIndex.size(); iSearchIndex++)
//					{
//						if (RouteEkiIndex[iSearchIndex] == iEkiIndexPrev)
//						{
//							iPosition = iSearchIndex;
//							break;
//						}
//					}
//					if (iPosition == -1)
//					{
//						/**
//							iPositionが-1の場合は、RouteEkiIndexに前駅のIndexを追加して次へ
//						*/
//						RouteEkiIndex.push_back(iEkiIndexNext);
//					}
//					else if (iPosition == RouteEkiIndex.size() - 1)
//					{
//						/**
//							iPositionが末尾の場合は、折り返している状態なので、RouteEkiIndexの末尾要素を削除して次へ。
//						*/
//						RouteEkiIndex.pop_back();
//					}
//					else if (iPosition == 0)
//					{
//						/**
//							iPositionが先頭(かつ末尾ではない)の場合は、この列車の始発駅は"環状"になる。
//						*/
//						bLoop = true;
//						aOuterDisplayContent.iEkiOrder = -1;
//						aOuterDisplayContent.HatsuJikoku.setNull();
//						//aRessyaPropertyBufferの駅Orderはその列車基準でおｋとする(同じ列車同士での比較が原則だから)
//						aRessyaPropertyBuffer.iEkiOrder = iEkiOrder - 1;
//						aRessyaPropertyBuffer.bLoop = true;
//						break;
//					}
//					else
//					{
//						/**
//							iPositionが中間の場合は、この列車の始発駅は"環状線"になる。(表示は環状)
//						*/
//						bLoop = true;
//						aOuterDisplayContent.iEkiOrder = -2;
//						aOuterDisplayContent.HatsuJikoku.setNull();
//						//aRessyaPropertyBufferの駅Orderはその列車基準でおｋとする(同じ列車同士での比較が原則だから)
//						aRessyaPropertyBuffer.iEkiOrder = iEkiOrder - 1;
//						aRessyaPropertyBuffer.bLoop = true;
//						break;
//					}
//				}
//				ContRessyaPropertyBuffer.push_back(aRessyaPropertyBuffer);
//				/**
//					itrの終着駅まで検索しても、環状にならなかった場合は、
//					前列車接続タイプを見て、前列車探索に入るかここで終了するかを決める
//				*/
//				if (bLoop)
//				{
//					break;
//				}
//				if (itrListOperationTableContent != ListOperationTableContent.begin())
//				{
//					auto itrListOperationTableContentPrev = itrListOperationTableContent;
//					itrListOperationTableContentPrev--;
//					if ((itrListOperationTableContent->eBeforeType == EBeforeAfterType::BeforeAfterType_ClassChange ||
//							itrListOperationTableContent->eBeforeType == EBeforeAfterType::BeforeAfterType_PropertyChange ||
//							itrListOperationTableContent->eBeforeType == EBeforeAfterType::BeforeAfterType_PropertySame) &&
//						itrListOperationTableContentPrev->eAfterType == itrListOperationTableContent->eBeforeType)
//					{
//						//この列車が先頭ではなく、前タイプが種別変更・列車情報変更・同一列車扱いのいずれかで、
//						//前の列車と一致しているのなら、前の列車の検索を行う。
//						continue;
//					}
//					else
//					{
//						//この列車が先頭ではないが、前タイプが別列車、または前列車の後タイプと一致しない場合、
//						//この列車が一体化の先頭となる
//						break;
//					}
//				}
//				else
//				{
//					//この列車が先頭なので、この列車が一体化の先頭となる
//					break;
//				}
//			}
//
//			/**
//				ListEkiJikokuhyouContentTempPerONが組みあがったら、
//				ContRessyaPropertyBufferとMapContRessyaPropertyBufferを突き合わせて
//				必要に応じて置き換える
//				また、この運番を内包するものがあったら、追加を行わない(bAddをfalseにする)
//			*/
//			bool bAdd = true;
//			tstring strReplace = _T("");
//			for (auto itr = MapContRessyaPropertyBuffer.begin(); itr != MapContRessyaPropertyBuffer.end()
//				&& strReplace.empty() && bAdd; itr++)
//			{
//				vector<RessyaPropertyBuffer>& contRessyaPropertyBufferSearch = itr->second;
//				for (int idxRPB = 0; idxRPB < (int)ContRessyaPropertyBuffer.size(); idxRPB++)
//				{
//					if (!ContRessyaPropertyBuffer[idxRPB].aRessyaProperty.isEqualTo(
//						contRessyaPropertyBufferSearch[idxRPB].aRessyaProperty, false))
//					{
//						//idxRPB番目の列車自体が異なる場合は、異なる始発駅(具体的には、次列車の始発駅で分割しているパターン)なので、
//						//置き換え対象にはならない。
//						break;
//					}
//					else if (ContRessyaPropertyBuffer[idxRPB].iEkiOrder <
//						contRessyaPropertyBufferSearch[idxRPB].iEkiOrder)
//					{
//						/**
//							この運番の方が長い区間で運行されている場合、
//							探索運番が路線外始発ではないかつ、
//							探索運番の前列車がない場合(idxRPBが末尾の場合)
//							(完全に探索運番がiEkiOrderで終了している場合)
//							この運番で探索運番を置き換えます
//							探索の前列車がある場合・探索運番が路線外始発の場合は、次運用の探索に映る
//						*/
//						if (contRessyaPropertyBufferSearch[idxRPB].iOuterEkiIndex < 0 &&
//							contRessyaPropertyBufferSearch.size() == idxRPB + 1)
//						{
//							strReplace = itr->first;
//						}
//						break;
//					}
//					else if (ContRessyaPropertyBuffer[idxRPB].iEkiOrder >
//						contRessyaPropertyBufferSearch[idxRPB].iEkiOrder)
//					{
//						/**
//							この運番の方が短い区間で運行されている場合、
//							この運番の前列車がない場合(idxRPBが末尾の場合)、路線外始発でもない場合は
//							この運番は置き換えも追加も行いません
//							この運番の前列車がある場合・この運番が路線外始発の場合は、次運用の探索に映る
//
//						*/
//						if (ContRessyaPropertyBuffer[idxRPB].iOuterEkiIndex < 0 &&
//							ContRessyaPropertyBuffer.size() == idxRPB + 1)
//						{
//							bAdd = false;
//						}
//						break;
//					}
//					//この運番と探索運番の終着駅が同じ場合
//					else if (ContRessyaPropertyBuffer[idxRPB].iOuterEkiIndex < 0 &&
//						ContRessyaPropertyBuffer.size() == idxRPB + 1)
//					{
//						/**
//							この運番の最初の列車の場合(除く路線外始発)は、
//							この運番は探索運番に内包されている、もしくは一致しているので、
//							置き換えも追加も行いません
//						*/
//						bAdd = false;
//						break;
//					}
//					else if (contRessyaPropertyBufferSearch[idxRPB].iOuterEkiIndex < 0 &&
//						contRessyaPropertyBufferSearch.size() == idxRPB + 1)
//					{
//						/**
//							探索運番の最初の列車の場合(除く路線外始発)は、
//							探索運番はこの運番に内包されているので、
//							置き換えます
//						*/
//						strReplace = itr->first;
//						break;
//					}
//					//この運番と探索運番が前列車ありと路線外始発のいずれか
//					else if (ContRessyaPropertyBuffer[idxRPB].iOuterEkiIndex >= 0)
//					{
//						/**
//							この運番が路線外始発の場合、
//							探索運番も路線外始発で、始発駅が同じ場合は、一致しているの置き換えも追加も行いません
//							それ以外の場合は、分岐しているので、次運用の探索に移ります
//						*/
//						if (ContRessyaPropertyBuffer[idxRPB].iOuterEkiIndex ==
//							contRessyaPropertyBufferSearch[idxRPB].iOuterEkiIndex)
//						{
//							bAdd = false;
//						}
//						break;
//					}
//					else if (contRessyaPropertyBufferSearch[idxRPB].iOuterEkiIndex >= 0)
//					{
//						/**
//							この運番が、前列車につながっていて、
//							かつ探索運番が路線外始発の場合は、分岐しているので、次運用の探索に移ります
//						*/
//						break;
//					}
//					/**
//						この運番と探索運番が共に前列車につながっている場合は、
//						前列車同士での比較になります。
//					*/
//				}
//			}
//
//			if (!strReplace.empty())
//			{
//				MapOuterDisplayContentBuffer.erase(strReplace);
//				MapContRessyaPropertyBuffer.erase(strReplace);
//			}
//			if (bAdd)
//			{
//				MapOuterDisplayContentBuffer[strOperationNumber] = aOuterDisplayContent;
//				MapContRessyaPropertyBuffer[strOperationNumber] = ContRessyaPropertyBuffer;
//			}
//		}
//
//		int iInsertPosition = -1;
//		if (aOuterSearchElement.bIsConnectOrRelease)
//		{
//			iInsertPosition = 0;
//		}
//		for (auto itrOuterDisplayContent = MapOuterDisplayContentBuffer.begin();
//			itrOuterDisplayContent != MapOuterDisplayContentBuffer.end(); itrOuterDisplayContent++, iInsertPosition--)
//		{
//#pragma omp critical(CustomizeRessyaIndex)
//			{
//				vector<CustomizeJikokuhyouContent>& contCustomizeJikokuhyouContent =
//					m_pDedDia->getcontCustomizeRessyaIndex(aRessyaProperty.getRessyahoukou());
//				for (int CustomizeJikokuhyouContentIndex = 0; CustomizeJikokuhyouContentIndex < (int)contCustomizeJikokuhyouContent.size(); CustomizeJikokuhyouContentIndex++)
//				{
//					if (contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].iRessyaIndexCont.empty())
//					{
//						continue;
//					}
//					if (contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].iRessyaIndexCont.front() == aRessyaProperty.getRessyaIndex())
//					{
//						if (iInsertPosition == -1)
//						{
//							//主編成の場合かつMapEkiJikokuhyouContentBufferの頭にあるものは、当該列車のCustomizeJikokuhyouContentを読み込み、そこに書き込みます。
//							contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].ChakuJikoku = itrOuterDisplayContent->second.ChakuJikoku;
//							contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].OuterShihatsuJikoku = itrOuterDisplayContent->second.HatsuJikoku;
//							contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].iSihatsuEkiOrder = itrOuterDisplayContent->second.iEkiOrder;
//							contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].iOuterShihatsuEkiIndex = itrOuterDisplayContent->second.iOuterEkiIndex;
//						}
//						else
//						{
//							//MapEkiJikokuhyouContentBufferの二番目以降、もしくは併合編成の場合は、当該列車のCustomizeJikokuhyouContentの直前に、併合列車として挿入します
//							const CentDedRessya* pCentDedRessya =
//								pCentDedRessyaConts[itrOuterDisplayContent->second.aRessyaProperty.getRessyahoukou()]
//								->get(itrOuterDisplayContent->second.aRessyaProperty.getRessyaIndex());
//							CustomizeJikokuhyouContent aCustomizeJikokuhyouContent(pCentDedRessya);
//							aCustomizeJikokuhyouContent.iConnectEkiOrder = aOuterSearchElement.iEkiOrder;
//							aCustomizeJikokuhyouContent.ChakuJikoku = itrOuterDisplayContent->second.ChakuJikoku;
//							aCustomizeJikokuhyouContent.OuterShihatsuJikoku = itrOuterDisplayContent->second.HatsuJikoku;
//							aCustomizeJikokuhyouContent.iSihatsuEkiOrder = itrOuterDisplayContent->second.iEkiOrder;
//							aCustomizeJikokuhyouContent.iOuterShihatsuEkiIndex = itrOuterDisplayContent->second.iOuterEkiIndex;
//							aCustomizeJikokuhyouContent.eEkiatsukai = itrOuterDisplayContent->second.eEkiatsukai;
//							aCustomizeJikokuhyouContent.iRessyaTrackIndex = itrOuterDisplayContent->second.iRessyaTrackIndex;
//							aCustomizeJikokuhyouContent.strOperationNumber = aOuterSearchElement.strContOperationNumber;
//
//							contCustomizeJikokuhyouContent.insert(contCustomizeJikokuhyouContent.begin() + CustomizeJikokuhyouContentIndex + iInsertPosition,
//								aCustomizeJikokuhyouContent);
//						}
//						break;
//					}
//				}
//			}
//		}
//	}


//
//	int iAfterSize = m_contAfterContinueList.size();
//	for (int iAfterIndex = 0; iAfterIndex < iAfterSize; iAfterIndex++)
//	{
//		OuterSearchElement& aOuterSearchElement = m_contAfterContinueList[iAfterIndex];
//
//		CdDedRessyaProperty aRessyaProperty = aOuterSearchElement.aRessyaProperty;
//		//const CentDedRessya* pCentDedRessya =
//		//	pCentDedRessyaConts[aRessyaProperty.getRessyahoukou()]
//		//	->get(aRessyaProperty.getRessyaIndex());
//		///**
//		//	次に、各運用番号に対して行き先を取得する。
//		//	その際、主編成の終点から、種別変更・分割で先の列車につながっている場合、
//		//	終点で解結して路線外終着になる場合は、上で獲得した主編成の終着駅を置き換える。
//		//	なお、主編成が路線外終着の場合は置き換えは起こらない。
//		//*/
//
//		unordered_map<tstring, vector<RessyaPropertyBuffer>> MapContRessyaPropertyBuffer;
//		unordered_map<tstring, OuterDisplayContent> MapOuterDisplayContentBuffer;
//		for (int idx = 0; idx < (int)aOuterSearchElement.strContOperationNumber.size(); idx++)
//		{
//			tstring strOperationNumber = aOuterSearchElement.strContOperationNumber[idx];
//
//			if (strOperationNumber.empty())
//			{
//				continue;
//			}
//			list<OperationTableContent>& ListOperationTableContent = contOperationTableContent[strOperationNumber];
//			auto itrListOperationTableContent = ListOperationTableContent.begin();
//			for (; itrListOperationTableContent != ListOperationTableContent.end(); itrListOperationTableContent++)
//			{
//				if (!itrListOperationTableContent->aRessyaProperty.isEqualTo(aRessyaProperty, false))
//				{
//					continue;
//				}
//				if (itrListOperationTableContent->iOuterShuchakuekiIndex < 0)
//				{
//					itrListOperationTableContent++;//最後に一回インクリメントして、当該列車の"次"に移動する。
//				}
//				break;
//			}
//			if (itrListOperationTableContent == ListOperationTableContent.end())
//			{
//				//aRessyaPropertyが一致するものが見つからなかったらこの運番に対しての表示は無しにする
//				continue;
//			}
//			vector<RessyaPropertyBuffer > ContRessyaPropertyBuffer;
//
//			OuterDisplayContent aOuterDisplayContent;
//
//			/**
//				この列車のルートを調べる、ルートに輪ができ、輪の終点が当駅なら、この列車の行き先は"環状"になる。
//				輪の終点が当駅以外なら、この列車の行き先は"環状線"になる。
//			*/
//			vector<int> RouteEkiIndex;
//			bool bLoop = false;
//			bool bFirst = true;
//
//			for (; itrListOperationTableContent != ListOperationTableContent.end(); itrListOperationTableContent++)
//			{
//
//				const CentDedRessya* pCentDedRessyaSearch =
//					pCentDedRessyaConts[itrListOperationTableContent->aRessyaProperty.getRessyahoukou()]
//					->get(itrListOperationTableContent->aRessyaProperty.getRessyaIndex());
//
//				if (bFirst)
//				{
//					//最初の列車(当該列車の次の列車)の場合、列車種別、当該列車終着駅の発時刻、駅扱い、aRessyaPropertyを取得します
//					aOuterDisplayContent.iRessyaSyubetsu = pCentDedRessyaSearch->getRessyasyubetsuIndex();
//					aOuterDisplayContent.HatsuJikoku = pCentDedRessyaSearch->getCentDedEkiJikoku(
//						itrListOperationTableContent->iSihatsuEkiOrder).getVirtualHatsujikoku();
//					aOuterDisplayContent.eEkiatsukai = pCentDedRessyaSearch->getCentDedEkiJikoku(
//						itrListOperationTableContent->iSihatsuEkiOrder).getEkiatsukai();
//					aOuterDisplayContent.iRessyaTrackIndex = pCentDedRessyaSearch->getCentDedEkiJikoku(
//						itrListOperationTableContent->iSihatsuEkiOrder).getRessyaTrackIndex();
//					aOuterDisplayContent.aRessyaProperty = itrListOperationTableContent->aRessyaProperty;
//					bFirst = false;
//				}
//				//行き先をitrで上書きする。
//				//終着駅Orderは、一度駅Indexに直してから、元々の列車方向に合わせたOrderに変更しなおす。
//				int iSyuuchakuEkiIndexSearch = pCentDedRessyaSearch->EkiIndexOfEkiOrder(itrListOperationTableContent->iSyuuchakuEkiOrder);
//				aOuterDisplayContent.iEkiOrder = pCentDedEkiCont->EkiOrderOfEkiIndex(aRessyaProperty.getRessyahoukou(),iSyuuchakuEkiIndexSearch);
//				aOuterDisplayContent.iOuterEkiIndex = itrListOperationTableContent->iOuterShuchakuekiIndex;
//				if (aOuterDisplayContent.iOuterEkiIndex >= 0)
//				{
//					aOuterDisplayContent.ChakuJikoku = itrListOperationTableContent->OuterShuchakuJikoku;
//				}
//				else
//				{
//					aOuterDisplayContent.ChakuJikoku = pCentDedRessyaSearch->getCentDedEkiJikoku(itrListOperationTableContent->iSyuuchakuEkiOrder).getVirtualChakujikoku();
//				}
//
//				RessyaPropertyBuffer aRessyaPropertyBuffer;
//				//aRessyaPropertyBufferの終着駅Orderはその列車基準でおｋとする(同じ列車同士で比較し、終着駅の遠さを見る必要があるので)
//				aRessyaPropertyBuffer.iEkiOrder = itrListOperationTableContent->iSyuuchakuEkiOrder;
//				aRessyaPropertyBuffer.iOuterEkiIndex = itrListOperationTableContent->iOuterShuchakuekiIndex;
//				aRessyaPropertyBuffer.aRessyaProperty = itrListOperationTableContent->aRessyaProperty;
//				
//				int iEkiOrder = itrListOperationTableContent->iSihatsuEkiOrder;
//				for (; iEkiOrder < itrListOperationTableContent->iSyuuchakuEkiOrder; iEkiOrder++)
//				{
//					if (!pCentDedRessyaSearch->isRunBetweenNextEki(iEkiOrder))
//					{
//						/**
//							iEkiOrderと次の駅間を運転していない場合は、
//							運行なし区間を飛ばし、次に運行ありになる区間へ移る、
//							その際、運行なしの前後が同一駅(分岐・環状関係)であることを確認する。
//						*/
//						int iEkiOrderNext = pCentDedRessyaSearch->getRunBetweenEkiForward(iEkiOrder);
//						if (iEkiOrderNext >= 0 &&
//							iEkiOrderNext < itrListOperationTableContent->iSyuuchakuEkiOrder &&
//							pCentDedEkiCont->isSameBrunchLoopGroup(iEkiOrder, iEkiOrderNext, pCentDedRessyaSearch->getRessyahoukou()))
//						{
//							iEkiOrder = iEkiOrderNext;
//						}
//						else
//						{
//							break;
//						}
//					}
//
//					int iEkiIndexPrev = iEkiOrderTable[iEkiOrder][(int)pCentDedRessyaSearch->getRessyahoukou()];
//					int iEkiIndexNext = iEkiOrderTable[iEkiOrder + 1][(int)pCentDedRessyaSearch->getRessyahoukou()];
//					int iPosition = -1;
//					for (int iSearchIndex = 0; iSearchIndex < (int)RouteEkiIndex.size(); iSearchIndex++)
//					{
//						if (RouteEkiIndex[iSearchIndex] == iEkiIndexNext)
//						{
//							iPosition = iSearchIndex;
//							break;
//						}
//					}
//					if (iPosition == -1)
//					{
//						/**
//							iPositionが-1の場合は、RouteEkiIndexに前駅のIndexを追加して次へ
//						*/
//						RouteEkiIndex.push_back(iEkiIndexPrev);
//					}
//					else if (iPosition == RouteEkiIndex.size() - 1)
//					{
//						/**
//							iPositionが末尾の場合は、折り返している状態なので、RouteEkiIndexの末尾要素を削除して次へ。
//						*/
//						RouteEkiIndex.pop_back();
//					}
//					else if (iPosition == 0)
//					{
//						/**
//							iPositionが先頭(かつ末尾ではない)の場合は、この列車の行き先は"環状"になる。
//						*/
//						bLoop = true;
//						aOuterDisplayContent.iEkiOrder = -1;
//						aOuterDisplayContent.ChakuJikoku.setNull();
//						//aRessyaPropertyBufferの駅Orderはその列車基準でおｋとする(同じ列車同士での比較が原則だから)
//						aRessyaPropertyBuffer.iEkiOrder = iEkiOrder + 1;
//						aRessyaPropertyBuffer.bLoop = true;
//						break;
//					}
//					else
//					{
//						/**
//							iPositionが中間の場合は、この列車の行き先は"環状線"になる。(表示は環状)
//						*/
//						bLoop = true;
//						aOuterDisplayContent.iEkiOrder = -2;
//						aOuterDisplayContent.ChakuJikoku.setNull();
//						//aRessyaPropertyBufferの駅Orderはその列車基準でおｋとする(同じ列車同士での比較が原則だから)
//						aRessyaPropertyBuffer.iEkiOrder = iEkiOrder + 1;
//						aRessyaPropertyBuffer.bLoop = true;
//						break;
//					}
//				}
//				ContRessyaPropertyBuffer.push_back(aRessyaPropertyBuffer);
//				/**
//					itrの終着駅まで検索しても、環状にならなかった場合は、
//					次列車接続タイプを見て、次列車探索に入るかここで終了するかを決める
//				*/
//				if (bLoop)
//				{
//					break;
//				}
//				auto itrListOperationTableContentNext = itrListOperationTableContent;
//				itrListOperationTableContentNext++;
//				if (itrListOperationTableContentNext != ListOperationTableContent.end() &&
//					(itrListOperationTableContent->eAfterType == EBeforeAfterType::BeforeAfterType_ClassChange ||
//						itrListOperationTableContent->eAfterType == EBeforeAfterType::BeforeAfterType_PropertyChange ||
//						itrListOperationTableContent->eAfterType == EBeforeAfterType::BeforeAfterType_PropertySame) &&
//					itrListOperationTableContentNext->eBeforeType == itrListOperationTableContent->eAfterType)
//				{
//					//この列車が末尾ではなく、後タイプが種別変更・列車情報変更・同一列車扱いのいずれかで、
//					//次の列車と一致しているのなら、次の列車の検索を行う。
//					continue;
//				}
//				else
//				{
//					//この列車が末尾、または後タイプが別列車、または次列車の前タイプと一致しない場合、
//					//この列車が一体化の末尾となる
//					break;
//				}
//			}
//
//			/**
//				ListEkiJikokuhyouContentTempPerONが組みあがったら、
//				ContRessyaPropertyBufferとMapContRessyaPropertyBufferを突き合わせて
//				必要に応じて置き換える
//				また、この運番を内包するものがあったら、追加を行わない(bAddをfalseにする)
//			*/
//			bool bAdd = true;
//			tstring strReplace = _T("");
//			for (auto itr = MapContRessyaPropertyBuffer.begin(); itr != MapContRessyaPropertyBuffer.end()
//				&& strReplace.empty() && bAdd; itr++)
//			{
//				vector<RessyaPropertyBuffer>& contRessyaPropertyBufferSearch = itr->second;
//				for (int idxRPB = 0; idxRPB < (int)ContRessyaPropertyBuffer.size(); idxRPB++)
//				{
//					if (!ContRessyaPropertyBuffer[idxRPB].aRessyaProperty.isEqualTo(
//						contRessyaPropertyBufferSearch[idxRPB].aRessyaProperty, false))
//					{
//						//idxRPB番目の列車自体が異なる場合は、異なる行き先(具体的には、前列車の終着駅で分割しているパターン)なので、
//						//置き換え対象にはならない。
//						break;
//					}
//					else if (ContRessyaPropertyBuffer[idxRPB].iEkiOrder >
//						contRessyaPropertyBufferSearch[idxRPB].iEkiOrder)
//					{
//						/**
//							この運番の方が長い区間で運行されている場合、
//							探索運番が路線外終着ではないかつ、
//							探索運番の次列車がない場合(idxRPBが末尾の場合)
//							(完全に探索運番がiSyuuchakuEkiOrderで終了している場合)
//							この運番で探索運番を置き換えます
//							探索の次列車がある場合・探索運番が路線外終着の場合は、次運用の探索に映る
//						*/
//						if (contRessyaPropertyBufferSearch[idxRPB].iOuterEkiIndex < 0 &&
//							contRessyaPropertyBufferSearch.size() == idxRPB + 1)
//						{
//							strReplace = itr->first;
//						}
//						break;
//					}
//					else if (ContRessyaPropertyBuffer[idxRPB].iEkiOrder <
//						contRessyaPropertyBufferSearch[idxRPB].iEkiOrder)
//					{
//						/**
//							この運番の方が短い区間で運行されている場合、
//							この運番の次列車がない場合(idxRPBが末尾の場合)、路線外終着でもない場合は
//							この運番は置き換えも追加も行いません
//							この運番の次列車がある場合・この運番が路線外終着の場合は、次運用の探索に映る
//
//						*/
//						if (ContRessyaPropertyBuffer[idxRPB].iOuterEkiIndex < 0 &&
//							ContRessyaPropertyBuffer.size() == idxRPB + 1)
//						{
//							bAdd = false;
//						}
//						break;
//					}
//					//この運番と探索運番の終着駅が同じ場合
//					else if (ContRessyaPropertyBuffer[idxRPB].iOuterEkiIndex < 0 &&
//						ContRessyaPropertyBuffer.size() == idxRPB + 1)
//					{
//						/**
//							この運番の最終列車の場合(除く路線外終着)は、
//							この運番は探索運番に内包されている、もしくは一致しているので、
//							置き換えも追加も行いません
//						*/
//						bAdd = false;
//						break;
//					}
//					else if (contRessyaPropertyBufferSearch[idxRPB].iOuterEkiIndex < 0 &&
//						contRessyaPropertyBufferSearch.size() == idxRPB + 1)
//					{
//						/**
//							探索運番の最終列車の場合(除く路線外終着)は、
//							探索運番はこの運番に内包されているので、
//							置き換えます
//						*/
//						strReplace = itr->first;
//						break;
//					}
//					//この運番と探索運番が次列車ありと路線外終着のいずれか
//					else if (ContRessyaPropertyBuffer[idxRPB].iOuterEkiIndex >= 0)
//					{
//						/**
//							この運番が路線外終着の場合、
//							探索運番も路線外終着で、終着駅が同じ場合は、一致しているの置き換えも追加も行いません
//							それ以外の場合は、分岐しているので、次運用の探索に移ります
//						*/
//						if (ContRessyaPropertyBuffer[idxRPB].iOuterEkiIndex ==
//							contRessyaPropertyBufferSearch[idxRPB].iOuterEkiIndex)
//						{
//							bAdd = false;
//						}
//						break;
//					}
//					else if (contRessyaPropertyBufferSearch[idxRPB].iOuterEkiIndex >= 0)
//					{
//						/**
//							この運番が、次列車につながっていて、
//							かつ探索運番が路線外終着の場合は、分岐しているので、次運用の探索に移ります
//						*/
//						break;
//					}
//					/**
//						この運番と探索運番が共に次列車につながっている場合は、
//						次列車同士での比較になります。
//					*/
//				}
//			}
//
//			if (!strReplace.empty())
//			{
//				MapOuterDisplayContentBuffer.erase(strReplace);
//				MapContRessyaPropertyBuffer.erase(strReplace);
//			}
//			if (bAdd)
//			{
//				MapOuterDisplayContentBuffer[strOperationNumber] = aOuterDisplayContent;
//				MapContRessyaPropertyBuffer[strOperationNumber] = ContRessyaPropertyBuffer;
//			}
//		}
//
//		int iInsertPosition = 0;
//		if (aOuterSearchElement.bIsConnectOrRelease)
//		{
//			iInsertPosition = 1;
//		}
//		for (auto itrOuterDisplayContent = MapOuterDisplayContentBuffer.begin(); 
//			itrOuterDisplayContent != MapOuterDisplayContentBuffer.end(); itrOuterDisplayContent++, iInsertPosition++)
//		{
//#pragma omp critical(CustomizeRessyaIndex)
//			{
//				vector<CustomizeJikokuhyouContent>& contCustomizeJikokuhyouContent =
//					m_pDedDia->getcontCustomizeRessyaIndex(aRessyaProperty.getRessyahoukou());
//				for (int CustomizeJikokuhyouContentIndex = 0; CustomizeJikokuhyouContentIndex < (int)contCustomizeJikokuhyouContent.size(); CustomizeJikokuhyouContentIndex++)
//				{
//					if (contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].iRessyaIndexCont.empty())
//					{
//						continue;
//					}
//					if (contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].iRessyaIndexCont.back() == aRessyaProperty.getRessyaIndex())
//					{
//						if (iInsertPosition == 0)
//						{
//							//主編成の場合かつMapEkiJikokuhyouContentBufferの頭にあるものは、当該列車のCustomizeJikokuhyouContentを読み込み、そこに書き込みます。
//							contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].HatsuJikoku = itrOuterDisplayContent->second.HatsuJikoku;
//							contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].OuterShuchakuJikoku = itrOuterDisplayContent->second.ChakuJikoku;
//							contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].iSyuuchakuEkiOrder = itrOuterDisplayContent->second.iEkiOrder;
//							contCustomizeJikokuhyouContent[CustomizeJikokuhyouContentIndex].iOuterShuchakuEkiIndex = itrOuterDisplayContent->second.iOuterEkiIndex;
//						}
//						else
//						{
//							//MapEkiJikokuhyouContentBufferの二番目以降、もしくは解結編成の場合は、当該列車のCustomizeJikokuhyouContentの直後に、分割列車として挿入します
//							const CentDedRessya* pCentDedRessya =
//								pCentDedRessyaConts[itrOuterDisplayContent->second.aRessyaProperty.getRessyahoukou()]
//								->get(itrOuterDisplayContent->second.aRessyaProperty.getRessyaIndex());
//							CustomizeJikokuhyouContent aCustomizeJikokuhyouContent(pCentDedRessya);
//							aCustomizeJikokuhyouContent.iReleaseEkiOrder = aOuterSearchElement.iEkiOrder;
//							aCustomizeJikokuhyouContent.HatsuJikoku = itrOuterDisplayContent->second.HatsuJikoku;
//							aCustomizeJikokuhyouContent.OuterShuchakuJikoku = itrOuterDisplayContent->second.ChakuJikoku;
//							aCustomizeJikokuhyouContent.iSyuuchakuEkiOrder = itrOuterDisplayContent->second.iEkiOrder;
//							aCustomizeJikokuhyouContent.iOuterShuchakuEkiIndex = itrOuterDisplayContent->second.iOuterEkiIndex;
//							aCustomizeJikokuhyouContent.eEkiatsukai = itrOuterDisplayContent->second.eEkiatsukai;
//							aCustomizeJikokuhyouContent.iRessyaTrackIndex = itrOuterDisplayContent->second.iRessyaTrackIndex;
//							aCustomizeJikokuhyouContent.strOperationNumber = aOuterSearchElement.strContOperationNumber;
//
//							contCustomizeJikokuhyouContent.insert(contCustomizeJikokuhyouContent.begin() + CustomizeJikokuhyouContentIndex + iInsertPosition,
//								aCustomizeJikokuhyouContent);
//						}
//						break;
//					}
//				}
//			}
//		}
//	}
}

;

} //namespace entDgr
