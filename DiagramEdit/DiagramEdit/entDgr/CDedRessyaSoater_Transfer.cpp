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
//	CDedRessyaSoater_Transfer.cpp
// ****************************************************************
*/
/** @file */
#include "stdafx.h"
#include <algorithm>
#include "CDedRessyaSoater_Transfer.h"
#include "NsMu\CaMui.h"
#include "NsMu\CMup_vector.h"
#include "NsMu\CaMup_vector.h"
#include "CentDedDgrRessya.h"



namespace entDgr{
using namespace std ;

// ****************************************************************
//	CDedRessyaSoater_Transfer
// ****************************************************************
	// --------------------------------
	//@name 下請関数
	// --------------------------------
bool CDedRessyaSoater_Transfer::sortRessyaIndex_TransferFromSortedRessyaAtEki( 
		const CentDedRessyaCont* pEstimateRessyaCont ,
		std::vector<int>* pcontRessyaIndexBeforeSort , 
		std::vector<int>* pcontRessyaIndexAfterSort , 
		int iEkiOrder , 
		int iMaxTransferSec ,
		IfProgress* pIfProgress )
{
	bool bAbort = false ;
	const CentDedRessyaCont* pRessyaCont = pEstimateRessyaCont ;
	const CentDedEkiCont* pEkiCont = m_pDedRosen->getCentDedEkiCont() ;

	//　　　　　　○全ソート前列車のループ(時刻の遅いほう→早いほう)
	//　　　　　　　　○全ソート後列車のループ(時刻の遅いほう→早いほう)
	//　　　　　　　　　　○[乗換駅Indexで、ソート後列車→ソート前列車の
	//　　　　　　　　　　　　乗継が10分以内で可能]
	//　　　　　　　　　　　　○ソート前列車をソート前列車コンテナから削除し、
	//　　　　　　　　　　　　　ソート後列車コンテナの、対象となったソート後列車の直後に、
	//　　　　　　　　　　　　　挿入
	for ( int idxRessyaIndexBeforeSort = (int)pcontRessyaIndexBeforeSort->size() - 1 ; 
		!bAbort && idxRessyaIndexBeforeSort >= 0 ;
		idxRessyaIndexBeforeSort -- )
	{
		int iRessyaIndexBeforeSort = pcontRessyaIndexBeforeSort->at( idxRessyaIndexBeforeSort ) ;
		const CentDedRessya*	pRessyaBeforeSort = pRessyaCont->getMuPtr()->get( iRessyaIndexBeforeSort ) ;

		CentDedEkiJikoku	aEkiJikokuBeforeSort = pRessyaBeforeSort->getCentDedEkiJikoku( iEkiOrder ) ;

		int idxRessyaIndexAfterSort = -1 ;
		for ( idxRessyaIndexAfterSort = (int)pcontRessyaIndexAfterSort->size() - 1 ;
			idxRessyaIndexAfterSort >= 0 ; 
			idxRessyaIndexAfterSort -- )
		{
			int iRessyaIndexAfterSort = pcontRessyaIndexAfterSort->at( idxRessyaIndexAfterSort ) ;
			const CentDedRessya*	pRessyaAfterSort = pRessyaCont->getMuPtr()->get( iRessyaIndexAfterSort ) ;
			CentDedEkiJikoku	aEkiJikokuAfterSort = pRessyaAfterSort->getCentDedEkiJikoku( iEkiOrder ) ;

			//	乗継可能の判定
			int iNorikaeSec = calcNorikaeSec( 
				aEkiJikokuAfterSort , 
				aEkiJikokuBeforeSort ,
				m_pDedRosen->getKitenJikoku() ) ;
			//iNorikaeSec = 乗り換え時間(秒数)
			//	乗り換え不可能なら、-1 ;

			if ( iNorikaeSec >= 0 && iNorikaeSec <= iMaxTransferSec )
			{
				//	乗り換え可能
				break ;
			}
		}
		//idxRessyaIndexAfterSort =
		//	乗り換え元となる、ソート後列車
		//	見つからない場合は、idxRessyaIndexAfterSort=-1 ; 

		if ( 0 <= idxRessyaIndexAfterSort )
		{
			//　　　　　　　　　　　　○ソート前列車をソート前列車コンテナから削除し、
			//　　　　　　　　　　　　　ソート後列車コンテナの、対象となったソート後列車の直後に、
			//　　　　　　　　　　　　　挿入
			pcontRessyaIndexBeforeSort->erase( 
					pcontRessyaIndexBeforeSort->begin() + idxRessyaIndexBeforeSort ) ;

			//	ソート後列車の直後以降で、挿入先を検索
			for ( idxRessyaIndexAfterSort ++ ;
				idxRessyaIndexAfterSort < (int)pcontRessyaIndexAfterSort->size() ;
				idxRessyaIndexAfterSort ++ )
			{
				int iRessyaIndexAfterSort = pcontRessyaIndexAfterSort->at( idxRessyaIndexAfterSort ) ;
				const CentDedRessya*	pRessyaAfterSort = pRessyaCont->getMuPtr()->get( iRessyaIndexAfterSort ) ;
				CentDedEkiJikoku	aEkiJikokuAfterSort = pRessyaAfterSort->getCentDedEkiJikoku( iEkiOrder ) ;

				if ( aEkiJikokuAfterSort.getHatsujikoku().isNull() || 
					aEkiJikokuBeforeSort.getHatsujikoku( true ).compare(
						aEkiJikokuAfterSort.getHatsujikoku( true ) ,
						m_pDedRosen->getKitenJikoku() ) <= 0 )
				{
					break ;
				}
			}
			//idxRessyaIndexAfterSort = 列車の挿入先

			pcontRessyaIndexAfterSort->insert( 
				pcontRessyaIndexAfterSort->begin() + idxRessyaIndexAfterSort ,
				iRessyaIndexBeforeSort ) ;
		}

		// --------------------------------
		if ( pIfProgress != NULL )
		{
			int iResult = pIfProgress->onNotifyProgress( 
				pcontRessyaIndexAfterSort->size() ,
				pRessyaCont->size() ) ;
			if ( iResult != 0 )
			{
				bAbort = true ;
			}

		}

	}

	return bAbort ;
}


bool CDedRessyaSoater_Transfer::sortRessyaIndex_TransferToSortedRessyaAtEki( 
		const CentDedRessyaCont* pEstimateRessyaCont ,
		std::vector<int>* pcontRessyaIndexBeforeSort , 
		std::vector<int>* pcontRessyaIndexAfterSort , 
		int iEkiOrder , 
		int iMaxTransferSec ,
		IfProgress* pIfProgress )
{
	bool bAbort = false ;
	const CentDedRessyaCont* pRessyaCont = pEstimateRessyaCont ;
	const CentDedEkiCont* pEkiCont = m_pDedRosen->getCentDedEkiCont() ;

	//　　　　　　○全ソート前列車のループ
	//　　　　　　　　○全ソート後列車のループ(時刻の早いほう→遅いほう)
	//　　　　　　　　　　○[乗換駅Indexで、ソート前列車→ソート後列車の
	//　　　　　　　　　　　　乗継が指定分以内で可能]
	//　　　　　　　　　　　　○ソート前列車をソート前列車コンテナから削除し、
	//　　　　　　　　　　　　　ソート後列車コンテナの、対象となったソート後列車の直前に、
	//　　　　　　　　　　　　　挿入
	for ( int idxRessyaIndexBeforeSort = 0 ; 
		!bAbort && idxRessyaIndexBeforeSort < (int)pcontRessyaIndexBeforeSort->size() ;
		idxRessyaIndexBeforeSort ++ )
	{
		const CentDedRessya*	pRessyaBeforeSort = pRessyaCont->getMuPtr()->get( 
			pcontRessyaIndexBeforeSort->at( idxRessyaIndexBeforeSort ) ) ;
		CentDedEkiJikoku	aEkiJikokuBeforeSort = pRessyaBeforeSort->getCentDedEkiJikoku( iEkiOrder ) ;

		int idxRessyaIndexAfterSort = -1 ;
		for ( idxRessyaIndexAfterSort = 0 ;
			idxRessyaIndexAfterSort < (int)pcontRessyaIndexAfterSort->size()  ; 
			idxRessyaIndexAfterSort ++ )
		{
			const CentDedRessya*	pRessyaAfterSort = pRessyaCont->getMuPtr()->get( 
				pcontRessyaIndexAfterSort->at( idxRessyaIndexAfterSort ) ) ;
			CentDedEkiJikoku	aEkiJikokuAfterSort = pRessyaAfterSort->getCentDedEkiJikoku( iEkiOrder ) ;

			//	乗継可能の判定
			int iNorikaeSec = calcNorikaeSec( 
				aEkiJikokuBeforeSort , 
				aEkiJikokuAfterSort ,
				m_pDedRosen->getKitenJikoku() ) ;
			//iNorikaeSec = 乗り換え時間(秒数)
			//	乗り換え不可能なら、-1 ;

			if ( iNorikaeSec >= 0 && iNorikaeSec <= iMaxTransferSec )
			{
				//	乗り換え可能
				break ;
			}
		}
		//idxRessyaIndexAfterSort =
		//	乗り換え先となる、ソート後列車
		//	見つからない場合は、idxRessyaIndexAfterSort=pcontRessyaIndexAfterSort->size() ; 

		if ( idxRessyaIndexAfterSort < (int)pcontRessyaIndexAfterSort->size() )
		{
			//　　　　　　　　　　　　○ソート前列車をソート前列車コンテナから削除し、
			//　　　　　　　　　　　　　ソート後列車コンテナの、対象となったソート後列車の直後に、
			//　　　　　　　　　　　　　挿入
			int iRessyaIndexBeforeSort = pcontRessyaIndexBeforeSort->at( idxRessyaIndexBeforeSort ) ;
			pcontRessyaIndexBeforeSort->erase( 
					pcontRessyaIndexBeforeSort->begin() + idxRessyaIndexBeforeSort ) ;
			idxRessyaIndexBeforeSort -- ;



			//	ソート後列車の直前以前で、挿入先を検索
			for ( idxRessyaIndexAfterSort -- ;
				idxRessyaIndexAfterSort >= 0 ;
				idxRessyaIndexAfterSort -- )
			{
				int iRessyaIndexAfterSort = pcontRessyaIndexAfterSort->at( idxRessyaIndexAfterSort ) ;
				const CentDedRessya*	pRessyaAfterSort = pRessyaCont->getMuPtr()->get( iRessyaIndexAfterSort ) ;
				CentDedEkiJikoku	aEkiJikokuAfterSort = pRessyaAfterSort->getCentDedEkiJikoku( iEkiOrder ) ;

				if ( aEkiJikokuAfterSort.getChakujikoku().isNull() || 
					aEkiJikokuAfterSort.getChakujikoku( true ).compare(
						aEkiJikokuBeforeSort.getChakujikoku( true ) ,
						m_pDedRosen->getKitenJikoku() ) <= 0 )
				{
					break ;
				}
			}
			idxRessyaIndexAfterSort ++ ;
			//idxRessyaIndexAfterSort = 列車の挿入先

			pcontRessyaIndexAfterSort->insert( 
				pcontRessyaIndexAfterSort->begin() + idxRessyaIndexAfterSort ,
				iRessyaIndexBeforeSort ) ;
		}

		// --------------------------------
		if ( pIfProgress != NULL )
		{
			int iResult = pIfProgress->onNotifyProgress( 
				pcontRessyaIndexAfterSort->size() ,
				pRessyaCont->size() ) ;
			if ( iResult != 0 )
			{
				bAbort = true ;
			}

		}

	}

	return bAbort ;
}

bool CDedRessyaSoater_Transfer::sortRessyaIndex_TransferFromSortedRessya( 
		const CentDedRessyaCont* pEstimateRessyaCont ,
		std::vector<int>* pcontRessyaIndexBeforeSort , 
		std::vector<int>* pcontRessyaIndexAfterSort , 
		CdDedJikokuOrder aEkijikokuOrder  , 
		IfProgress* pIfProgress ) 
{
	bool bAbort = false ;
	ERessyahoukou	eRessyahoukou = pEstimateRessyaCont->getRessyahoukou() ;
	const CentDedRessyaCont* pRessyaCont = pEstimateRessyaCont ;
	const CentDedEkiCont* pEkiCont = m_pDedRosen->getCentDedEkiCont() ;

	//◎ソート前列車を、ソート対象駅(F)よりあとの停車駅で10分以内に乗り換えのできるソート後列車の後ろに配置
	//　　○乗り換え駅Orderのループ(ソート対象駅+1～終着駅)
	//　　　　○[その駅が主要駅]
	//　　　　　　○全ソート前列車のループ
	//　　　　　　　　○全ソート後列車のループ(時刻の遅いほう→早いほう)
	//　　　　　　　　　　○[乗換駅Indexで、ソート後列車→ソート前列車の
	//　　　　　　　　　　　　乗継が10分以内で可能]
	//　　　　　　　　　　　　○ソート前列車をソート前列車コンテナから削除し、
	//　　　　　　　　　　　　　ソート後列車コンテナの、対象となったソート後列車の直後に、
	//　　　　　　　　　　　　　挿入
	//　　○ソート前列車が1本でも減少したら、このループを再実行
	int iRessyaIndexBeforSortCount ;
	do{
		iRessyaIndexBeforSortCount = pcontRessyaIndexBeforeSort->size() ;

		for ( int iEkiOrder = aEkijikokuOrder.getEkiOrder() ; 
			!bAbort && iEkiOrder <= pEkiCont->size() - 1 ;
			iEkiOrder ++ )
		{
			CentDedEkiCont::CdDedEki	aEki = pEkiCont->getMuPtr(eRessyahoukou)->get( iEkiOrder ) ;
			if ( aEki.getEkikibo() == CentDedEki::EEkikibo::Ekikibo_Syuyou )
			{
				//◎ソート前列車を、ソート対象駅(F)よりあとの停車駅で
				//	10分以内に乗り換えのできるソート後列車の後ろに配置
				bAbort = sortRessyaIndex_TransferFromSortedRessyaAtEki( 
					pEstimateRessyaCont ,
					pcontRessyaIndexBeforeSort , 
					pcontRessyaIndexAfterSort , 
					iEkiOrder , 
					10 * 60 , 
					pIfProgress ) ; 
			}
		}

	} while( !bAbort && iRessyaIndexBeforSortCount > (int)pcontRessyaIndexBeforeSort->size() ) ;
	



	//
	//　　○乗り換え駅Orderのループ(ソート対象駅+1～終着駅)
	//　　　　○[その駅がNOT(主要駅)]
	//　　　　　　○全ソート前列車のループ
	//　　　　　　　　○全ソート後列車のループ(時刻の遅いほう→早いほう)
	//　　　　　　　　　　○[乗換駅Indexで、ソート後列車→ソート前列車の
	//　　　　　　　　　　　　乗継が10分以内で可能]
	//　　　　　　　　　　　　○ソート前列車をソート前列車コンテナから削除し、
	//　　　　　　　　　　　　　ソート後列車コンテナの、対象となったソート後列車の直後に、
	//　　　　　　　　　　　　　挿入
	//　　○ソート前列車が1本でも減少したら、このループを再実行

	do{
		iRessyaIndexBeforSortCount = pcontRessyaIndexBeforeSort->size() ;

		for ( int iEkiOrder = aEkijikokuOrder.getEkiOrder() ; 
			!bAbort && iEkiOrder <= pEkiCont->size() - 1 ;
			iEkiOrder ++ )
		{
			CentDedEkiCont::CdDedEki	aEki = pEkiCont->getMuPtr(eRessyahoukou)->get( iEkiOrder ) ;
			if ( aEki.getEkikibo() != CentDedEki::EEkikibo::Ekikibo_Syuyou )
			{
				//◎ソート前列車を、ソート対象駅(F)よりあとの停車駅で
				//	10分以内に乗り換えのできるソート後列車の後ろに配置
				bAbort = sortRessyaIndex_TransferFromSortedRessyaAtEki( 
					pEstimateRessyaCont ,
					pcontRessyaIndexBeforeSort , 
					pcontRessyaIndexAfterSort , 
					iEkiOrder , 
					10 * 60 , 
					pIfProgress ) ; 
			}
		}

	} while( !bAbort && iRessyaIndexBeforSortCount > (int)pcontRessyaIndexBeforeSort->size() ) ;




	//◎ソート前列車を、ソート対象駅(F)よりあとの停車駅で乗り換えのできるソート後列車を探す。
	//　　○乗り換え駅Orderのループ(ソート対象駅+1～終着駅)
	//　　　　　　○全ソート前列車のループ
	//　　　　　　　　○全ソート後列車のループ(時刻の遅いほう→早いほう)
	//　　　　　　　　　　○[乗換駅Indexで、ソート後列車→ソート前列車の乗継が可能]
	//　　　　　　　　　　　　○ソート前列車の「並べ替え用駅時刻」に、
	//　　　　　　　　　　　　　ソート後列車の「並べ替え用駅時刻」の駅時刻・着発をコピー。
	//　　　　　　　　　　　　○ソート前列車をソート前列車コンテナから削除し、
	//　　　　　　　　　　　　　ソート後列車コンテナの、対象となったソート後列車の直後に、
	//　　　　　　　　　　　　　挿入
	//　　○ソート前列車が1本でも減少したら、このループを再実行

	do{
		iRessyaIndexBeforSortCount = pcontRessyaIndexBeforeSort->size() ;

		for ( int iEkiOrder = aEkijikokuOrder.getEkiOrder()  ; 
			!bAbort && iEkiOrder <= pEkiCont->size() - 1 ;
			iEkiOrder ++ )
		{
			CentDedEkiCont::CdDedEki	aEki = pEkiCont->getMuPtr(eRessyahoukou)->get( iEkiOrder ) ;
			{
				//◎ソート前列車を、ソート対象駅(F)よりあとの停車駅で
				//	乗り換えのできるソート後列車の後ろに配置
				bAbort = sortRessyaIndex_TransferFromSortedRessyaAtEki( 
					pEstimateRessyaCont ,
					pcontRessyaIndexBeforeSort , 
					pcontRessyaIndexAfterSort , 
					iEkiOrder , 
					INT_MAX , 
					pIfProgress ) ; 
			}
		}

	} while( !bAbort && iRessyaIndexBeforSortCount > (int)pcontRessyaIndexBeforeSort->size() ) ;

	return bAbort ;
}


bool CDedRessyaSoater_Transfer::sortRessyaIndex_TransferToSortedRessya( 
		const CentDedRessyaCont* pEstimateRessyaCont ,
		std::vector<int>* pcontRessyaIndexBeforeSort , 
		std::vector<int>* pcontRessyaIndexAfterSort , 
		CdDedJikokuOrder aEkijikokuOrder  , 
		IfProgress* pIfProgress ) 
{
	bool bAbort = false ;
	ERessyahoukou	eRessyahoukou = pEstimateRessyaCont->getRessyahoukou() ;
	const CentDedRessyaCont* pRessyaCont = pEstimateRessyaCont ;
	const CentDedEkiCont* pEkiCont = m_pDedRosen->getCentDedEkiCont() ;
	//◎ソート前列車を、ソート対象駅(F)より前の停車駅で10分以内に乗り換えのできるソート後列車の前に配置
	//　　○乗り換え駅Orderのループ(ソート対象駅-1～起点駅)
	//　　　　○[その駅が終着駅or主要駅]
	//　　　　　　○全ソート前列車のループ
	//　　　　　　　　○全ソート後列車のループ(時刻の早いほう→遅いほう)
	//　　　　　　　　　　○[乗換駅Indexで、ソート前列車→ソート後列車の
	//　　　　　　　　　　　　乗継が10分以内で可能]
	//　　　　　　　　　　　　○ソート前列車をソート前列車コンテナから削除し、
	//　　　　　　　　　　　　　ソート後列車コンテナの、対象となったソート後列車の直前に、
	//　　　　　　　　　　　　　挿入
	//　　○ソート前列車が1本でも減少したら、このループを再実行

	int iRessyaIndexBeforSortCount ;
	do{
		iRessyaIndexBeforSortCount = pcontRessyaIndexBeforeSort->size() ;

		for ( int iEkiOrder = aEkijikokuOrder.getEkiOrder()  ; 
			!bAbort && iEkiOrder >= 0 ;
			iEkiOrder -- )
		{
			CentDedEkiCont::CdDedEki	aEki = pEkiCont->getMuPtr(eRessyahoukou)->get( iEkiOrder ) ;
			if ( aEki.getEkikibo() == CentDedEki::EEkikibo::Ekikibo_Syuyou )
			{
				bAbort = sortRessyaIndex_TransferToSortedRessyaAtEki( 
					pEstimateRessyaCont ,
					pcontRessyaIndexBeforeSort , 
					pcontRessyaIndexAfterSort , 
					iEkiOrder , 
					10 * 60 , 
					pIfProgress ) ; 
			}
		}

	} while( !bAbort && iRessyaIndexBeforSortCount > (int)pcontRessyaIndexBeforeSort->size() ) ;


	//
	//　　○乗り換え駅Orderのループ(ソート対象駅-1～起点駅)
	//　　　　○[その駅がNOT(終着駅or主要駅)]
	//　　　　　　○全ソート前列車のループ
	//　　　　　　　　○全ソート後列車のループ(時刻の早いほう→遅いほう)
	//　　　　　　　　　　○[乗換駅Indexで、ソート前列車→ソート後列車の
	//　　　　　　　　　　　　乗継が10分以内で可能]
	//　　　　　　　　　　　　○ソート前列車をソート前列車コンテナから削除し、
	//　　　　　　　　　　　　　ソート後列車コンテナの、対象となったソート後列車の直前に、
	//　　　　　　　　　　　　　挿入
	//　　○ソート前列車が1本でも減少したら、このループを再実行
	do{
		iRessyaIndexBeforSortCount = pcontRessyaIndexBeforeSort->size() ;

		for ( int iEkiOrder = aEkijikokuOrder.getEkiOrder()  ; 
			!bAbort && iEkiOrder >= 0 ;
			iEkiOrder -- )
		{
			CentDedEkiCont::CdDedEki	aEki = pEkiCont->getMuPtr(eRessyahoukou)->get( iEkiOrder ) ;
			if ( aEki.getEkikibo() != CentDedEki::EEkikibo::Ekikibo_Syuyou )
			{
				bAbort = sortRessyaIndex_TransferToSortedRessyaAtEki( 
					pEstimateRessyaCont ,
					pcontRessyaIndexBeforeSort , 
					pcontRessyaIndexAfterSort , 
					iEkiOrder , 
					10 * 60 , 
					pIfProgress ) ; 
			}
		}

	} while( !bAbort && iRessyaIndexBeforSortCount > (int)pcontRessyaIndexBeforeSort->size() ) ;

	//◎ソート前列車を、ソート対象駅(F)より前の停車駅で乗り換えのできるソート後列車を探す。
	//　　○乗り換え駅Orderのループ(ソート対象駅-1～起点駅)
	//　　　　　　○全ソート前列車のループ
	//　　　　　　　　○全ソート後列車のループ(時刻の遅いほう→早いほう)
	//　　　　　　　　　　○[乗換駅Indexで、ソート前列車→ソート後列車の乗継が可能]
	//　　　　　　　　　　　　○ソート前列車をソート前列車コンテナから削除し、
	//　　　　　　　　　　　　　ソート後列車コンテナの、対象となったソート後列車の直前に、
	//　　　　　　　　　　　　　挿入
	//　　○ソート前列車が1本でも減少したら、このループを再実行
	//
	do{
		iRessyaIndexBeforSortCount = pcontRessyaIndexBeforeSort->size() ;

		for ( int iEkiOrder = aEkijikokuOrder.getEkiOrder() ; 
			!bAbort && iEkiOrder >= 0 ;
			iEkiOrder -- )
		{
			CentDedEkiCont::CdDedEki	aEki = pEkiCont->getMuPtr(eRessyahoukou)->get( iEkiOrder ) ;
			{
				bAbort = sortRessyaIndex_TransferToSortedRessyaAtEki( 
					pEstimateRessyaCont ,
					pcontRessyaIndexBeforeSort , 
					pcontRessyaIndexAfterSort , 
					iEkiOrder , 
					INT_MAX , 
					pIfProgress ) ; 
			}
		}

	} while( !bAbort && iRessyaIndexBeforSortCount > (int)pcontRessyaIndexBeforeSort->size() ) ;

	return bAbort ;
}


	// ********************************
	//	コンストラクタ
	// ********************************
CDedRessyaSoater_Transfer::CDedRessyaSoater_Transfer(
	const CentDedRosen* pDedRosen , 
	const CentDedDia* pDedDia ,
	CdDedJikokuOrder  aCdDedJikokuOrder,
	const int iIndexDst,
	const int iSizeDst) :
	m_bIsValid( false ) ,
	m_pDedRosen( pDedRosen ) ,
	m_pDedDia( pDedDia ) ,
	m_JikokuOrder( aCdDedJikokuOrder ),
	m_iIndexDst(iIndexDst),
	m_iSizeDst(iSizeDst)
{
}

CDedRessyaSoater_Transfer::~CDedRessyaSoater_Transfer() 
{
	invalidate() ;
}
	


int CDedRessyaSoater_Transfer::validate()  
{
	if ( isValid() )
	{
		return 0 ;
	}
	// --------------------------------
	int iRv = 1 ;
	//◎ソート対象の列車コンテナから、推定時刻つき列車を保持した列車を生成
	//　◎ソート対象の列車コンテナを包含する CentDedDia から、CentDedDgrDia を生成
	//　◎ソート対象の列車の推定時刻CentDedRessyaContを生成
	//　　	○ソート対象の全列車のループ
	//　　　　	○CentDedDgrRessyaから、推定時刻つきのCentDedRessyaを生成し、コンテナに追加
	if ( iRv >= 1 )
	{
		m_CentDedDgrDia.readCentDedRosen(
			m_pDedRosen , 
			m_pDedDia );

	}


	// --------------------------------
	if ( iRv >= 1 )
	{
		m_bIsValid = true ;
	}
	else
	{
		invalidate() ;
	}
	return iRv ;
}
	
void CDedRessyaSoater_Transfer::invalidate() 
{
	m_bIsValid = false ;
}
	
bool CDedRessyaSoater_Transfer::isValid() 
{
	return m_bIsValid ;
}
	// ********************************
	//@name 操作
	// ********************************


/**
	列車Indexを、指定された駅時刻Orderの時刻で比較する関数オブジェクトです。
*/
class CCompareRessyaIndex_Ekijikoku
{
private:
	// ********************************
	///@name 関連
	// ********************************
	///@{
	/**
		列車コンテナ。
	*/
	const CentDedRessyaCont* m_pRessyaCont ;

	///@}
	// ********************************
	///@name 属性
	// ********************************
	///@{
	/**
		『時刻Order』を指定してください。
	*/
	CdDedJikokuOrder m_JikokuOrder ;

	/**
		ダイヤグラム起点時刻を指定してください。
		この関数は、ソート時に、この値を最も小さい時刻と
		みなします。
		(例：この時刻に5:00が指定された場合は、5:00<23:59<0:00<4:59 として比較を行います)
	*/
	CdDedJikoku m_jikokuKitenJikoku ;
	///@}
public:
	/**
	@param pRessyaCont [in]
		列車コンテナ。
	@param iJikokuOrder [in]
		『時刻Order』を指定してください。
	@param jikokuKitenJikoku [in]
		ダイヤグラム起点時刻を指定してください。
		この関数は、ソート時に、この値を最も小さい時刻と
		みなします。
		(例：この時刻に5:00が指定された場合は、5:00<23:59<0:00<4:59 として比較を行います)
	*/
	CCompareRessyaIndex_Ekijikoku( 
		const CentDedRessyaCont* pRessyaCont ,
		const CdDedJikokuOrder& aJikokuOrder ,
		CdDedJikoku jikokuKitenJikoku )
		: 
		m_pRessyaCont( pRessyaCont ) ,
		m_JikokuOrder( aJikokuOrder ) ,
		m_jikokuKitenJikoku( jikokuKitenJikoku )
	{
	};
	/**
	@return
		left < right なら真です。

	@note
	  比較基準は、
			- 駅時刻がNULLでないものとNULLのものとでは、NULLでないものが先。
			- Ekijikokuの小さいほうが先。
			- Ekijikokuが同じなら、着時刻が先。
			- Ekijikokuも着/発も同じならRessyaIdxの小さいほうが先。
	*/
	bool operator()( int left , int right )
	{
		const CentDedRessya*	pRessyaLeft = m_pRessyaCont->getMuPtr()->get( left ) ;
		const CentDedRessya*	pRessyaRight = m_pRessyaCont->getMuPtr()->get( right ) ;
		CentDedEkiJikoku	aEkiJikokuLeft = pRessyaLeft->getCentDedEkiJikoku( m_JikokuOrder.getEkiOrder()  ) ;
		CentDedEkiJikoku	aEkiJikokuRight = pRessyaRight->getCentDedEkiJikoku( m_JikokuOrder.getEkiOrder() ) ;
		CdDedJikoku aJikokuLeft ;
		bool bLeftIsHatsu = false ;
		CdDedJikoku aJikokuRight ;
		bool bRightIsHatsu = false ;

		if ( m_JikokuOrder.getEkiJikokuItem() == CdDedJikokuOrder::EkiJikokuItem_Chaku )
		{
			//	着時刻で優先して比較
			aJikokuLeft = aEkiJikokuLeft.getChakujikoku() ;	
			bLeftIsHatsu = false ;
			if ( aEkiJikokuLeft.getChakujikoku().isNull() &&
				!aEkiJikokuLeft.getHatsujikoku().isNull() )
			{
				aJikokuLeft = aEkiJikokuLeft.getHatsujikoku() ;
				bLeftIsHatsu = true ;
			}
			aJikokuRight = aEkiJikokuRight.getChakujikoku() ;
			bRightIsHatsu = false ;
			if ( aEkiJikokuRight.getChakujikoku().isNull() &&
				!aEkiJikokuRight.getHatsujikoku().isNull() )
			{
				aJikokuRight = aEkiJikokuRight.getHatsujikoku() ;
				bRightIsHatsu = true ;
			}
		}
		else
		{
			//	発時刻で優先して比較

			aJikokuLeft = aEkiJikokuLeft.getHatsujikoku() ;	
			bLeftIsHatsu = true ;
			if ( !aEkiJikokuLeft.getChakujikoku().isNull() &&
				  aEkiJikokuLeft.getHatsujikoku().isNull() )
			{
				aJikokuLeft = aEkiJikokuLeft.getChakujikoku() ;
				bLeftIsHatsu = false ;
			}
			aJikokuRight = aEkiJikokuRight.getHatsujikoku() ;
			bRightIsHatsu = true ;
			if ( !aEkiJikokuRight.getChakujikoku().isNull() &&
				  aEkiJikokuRight.getHatsujikoku().isNull() )
			{
				aJikokuRight = aEkiJikokuRight.getChakujikoku() ;
				bRightIsHatsu = false ;
			}

		}
		// --------------------------------
		//	片方がNULLの場合の比較
		// --------------------------------
		if ( !aJikokuLeft.isNull() && aJikokuRight.isNull() )
		{
			//	leftはNULLで、rightは非NULL
			return true ;
		}
		else if ( aJikokuLeft.isNull() && !aJikokuRight.isNull() )
		{
			//	leftは非NULLで、rightはNULL
			return false ;
		}
		// --------------------------------
		//	m_Jikoku はどちらもNULLではない・もしくはどちらもNULL
		//	時刻の比較
		// --------------------------------
		int iResult = aJikokuLeft.compare( aJikokuRight , m_jikokuKitenJikoku ) ;
		if ( iResult == -1 )
		{
			return true ;
		}
		else if ( iResult == 1 )
		{
			return false ;
		}
		// --------------------------------
		// 	Ekijikokuが同じなら、着時刻が先。
		// --------------------------------
		if ( !bLeftIsHatsu && bRightIsHatsu )
		{
			return true ;
		}
		else if ( bLeftIsHatsu && !bRightIsHatsu )
		{
			return false ;
		}

		// --------------------------------
		// 時刻・着発ともに等しい場合は、列車Indexが小さいほうが先
		// --------------------------------
		if ( left < right )
		{
			return true ;
		}
		return false ;
	}

};


void CDedRessyaSoater_Transfer::sortRessyaIndex( 
		const CentDedRessyaCont* pRessyaCont , 
		Mui<int>* muRessyaIndexOrder , 
		IfProgress* pIfProgress ) 
{
	bool bAbort = false ;
	const CentDedEkiCont* pEkiCont = m_pDedRosen->getCentDedEkiCont() ;
	CdDedJikokuOrder aEkijikokuOrder = m_JikokuOrder ;
	ERessyahoukou eRessyahoukou = pRessyaCont->getRessyahoukou() ;

	//◎pRessyaContから、推定時刻つき列車コンテナを作成
	//	validate() で、m_pDedRosenと m_pDedDia に含まれる全列車の
	//	推定時刻 CentDedRessya を生成し、その内容を保持します。

	CentDedRessyaCont aEstimateRessyaCont = pRessyaCont->createEmptyCont() ;
	for ( int idxRessya = 0 ; idxRessya < pRessyaCont->size() ; idxRessya ++ )
	{
		const CentDedRessya* pCentDedRessya = pRessyaCont->getMuPtr()->get( idxRessya ) ;
		CentDedDgrRessya	aCentDedDgrRessya( 
			m_pDedRosen , 
			m_pDedDia,
			&m_CentDedDgrDia , 
			pCentDedRessya ) ;

		CentDedRessya aEstimateRessya( aEstimateRessyaCont.createNullRessya() ) ; 
		m_CentDedDgrDia.createEstimateRessya2( 
			&aCentDedDgrRessya ,
			&aEstimateRessya ,
			pEkiCont) ;
		aEstimateRessyaCont.insert( aEstimateRessya ) ;
	}
	//aEstimateRessyaCont = pRessyaCont に推定時刻を追加しました。
	CentDedRessyaCont*	pEstimateRessyaCont = &aEstimateRessyaCont ;

	////◎ソート前駅インデクスコンテナを生成
	vector<int>	contRessyaIndexBeforSort ;
	vector<int>	contRessyaIndexAfterSort ;
	{
		contRessyaIndexBeforSort.reserve( muRessyaIndexOrder->size() ) ;
		contRessyaIndexAfterSort.reserve( muRessyaIndexOrder->size() ) ; 
		CaMui<int>( &CaMup_vector<vector<int>>( &contRessyaIndexBeforSort ) ).insert( muRessyaIndexOrder ) ; ;
	}

	list<vector<int>> contRessyaIndexOrder;
	//list<vector<int>> contRessyaIndexAfterSort2;
	//Ver2.06.18 パターンダイヤプレビュー機能が有効な場合は、この探索は無効にする。
	if (m_pDedRosen->getEnableOperation() > 0 && !m_pDedDia->getPatternDiagramPreviewEnable())
	{
		const vector<CustomizeJikokuhyouContent>& contCustomizeJikokuhyouContent = m_pDedDia->getcontCustomizeRessyaIndex(eRessyahoukou);
		vector<int> contConnectRessyaIndex;
		for (int idx = 0; idx < (int)contCustomizeJikokuhyouContent.size(); idx++)
		{
			const CustomizeJikokuhyouContent& aCustomizeJikokuhyouContent = contCustomizeJikokuhyouContent[idx];
			if (aCustomizeJikokuhyouContent.iRessyaIndexCont.empty())
			{
				continue;
			}
			if (aCustomizeJikokuhyouContent.iConnectEkiOrder >= 0)
			{
				/**
					この列が、次の列へ併合している場合、この2列はソート後も並び順を維持するようにします。
					ここでは、contConnectRessyaIndexにこの列のiRessyaIndexContを収めて、次の列に移ります
					このとき、複数列が併合している可能性を考慮し、insertを用います。
				*/
				contConnectRessyaIndex.insert(
					contConnectRessyaIndex.end(),
					aCustomizeJikokuhyouContent.iRessyaIndexCont.begin(), aCustomizeJikokuhyouContent.iRessyaIndexCont.end());
			}
			else if (aCustomizeJikokuhyouContent.iReleaseEkiOrder >= 0)
			{
				/**
					この列が、前の列から分割している場合、この2列はソート後も並び順を維持するようにします。
					contRessyaIndexOrderの末尾要素に、この列のiRessyaIndexContを付け加えます。
				*/

				//contRessyaIndexOrderの末尾要素を取り出す
				contConnectRessyaIndex = contRessyaIndexOrder.back();
				contRessyaIndexOrder.pop_back();

				//contConnectRessyaIndexの末尾要素を取り出す(軸列車Index)
				int iMainRessyaIndex = contConnectRessyaIndex.back();
				contConnectRessyaIndex.pop_back();

				contConnectRessyaIndex.insert(
					contConnectRessyaIndex.end(),
					aCustomizeJikokuhyouContent.iRessyaIndexCont.begin(), aCustomizeJikokuhyouContent.iRessyaIndexCont.end());

				//contConnectRessyaIndexの末尾に軸列車Indexを付与する。
				contConnectRessyaIndex.emplace_back(iMainRessyaIndex);

				contRessyaIndexOrder.emplace_back(contConnectRessyaIndex);
				contConnectRessyaIndex.clear();
			}
			else
			{
				/**
					それ以外の場合、contConnectRessyaIndexに値がある場合は、その後ろにこの列のiRessyaIndexContをつなげてからcontRessyaIndexOrderに収めます。
				*/

				//iMainRessyaIndex contConnectRessyaIndex内で軸となる列車のcontConnectRessyaIndexにおけるインデクス
				int iMainRessyaPos = contConnectRessyaIndex.size();
				contConnectRessyaIndex.insert(
					contConnectRessyaIndex.end(),
					aCustomizeJikokuhyouContent.iRessyaIndexCont.begin(), aCustomizeJikokuhyouContent.iRessyaIndexCont.end());
				//contConnectRessyaIndexの末尾に軸列車Indexを付与する。
				contConnectRessyaIndex.emplace_back(iMainRessyaPos);

				contRessyaIndexOrder.emplace_back(contConnectRessyaIndex);
				contConnectRessyaIndex.clear();
			}
		}

		for (auto itrOrder = contRessyaIndexOrder.begin(); itrOrder != contRessyaIndexOrder.end(); )
		{
			bool bErased = false;
			if (itrOrder->size() <= 2)
			{
				//サイズが2の場合は、列車Indexと軸列車Indexのみ(つまり1列車のみ)なので、削除します。
				itrOrder = contRessyaIndexOrder.erase(itrOrder);
				bErased = true;
			}
			else
			{
				//サイズが3以上の場合、軸列車と連続している列車のみ残します。
				//まず、軸列車より後方、次に前方を見ます
				//Ver2.06.18 一部列車のみを選択した状態で実行された場合の補正を追加
				//(1)選択範囲以外が含まれている場合は削除
				//(2)選択範囲内の場合、選択開始位置の分を補正する

				for (int itrIndex = 0; itrIndex < (int)itrOrder->size() - 1; itrIndex++)
				{
					if (itrOrder->at(itrIndex) < m_iIndexDst || itrOrder->at(itrIndex) >= m_iIndexDst + m_iSizeDst)
					{
						itrOrder = contRessyaIndexOrder.erase(itrOrder);
						bErased = true;
						break;
					}
					else
					{
						itrOrder->at(itrIndex) = itrOrder->at(itrIndex) - m_iIndexDst;
					}
				}

				if (!bErased)
				{
					int iMainRessyaPos = itrOrder->back();
					itrOrder->pop_back();
					int iMainRessyaIndex = itrOrder->at(iMainRessyaPos);
					for (int iOffset = 1; iOffset + iMainRessyaPos < (int)itrOrder->size(); iOffset++)
					{
						if (itrOrder->at(iOffset + iMainRessyaPos) != iMainRessyaIndex + iOffset)
						{
							itrOrder->erase(itrOrder->begin() + iOffset + iMainRessyaPos, itrOrder->end());
							break;
						}
					}

					for (int iOffset = 1; iMainRessyaPos - iOffset >= 0; iOffset++)
					{
						if (itrOrder->at(iMainRessyaPos - iOffset) != iMainRessyaIndex - iOffset)
						{
							itrOrder->erase(itrOrder->begin(), itrOrder->begin() + iMainRessyaPos - iOffset + 1);
							iMainRessyaPos = iOffset - 1;
							break;
						}
					}

					//前後を削除した結果、サイズが1になった場合は、軸列車のみなので削除します。
					//サイズが2以上の場合は、軸列車位置Indexを付与して終了します。
					if (itrOrder->size() == 1)
					{
						itrOrder = contRessyaIndexOrder.erase(itrOrder);
						bErased = true;
					}
					else
					{
						itrOrder->push_back(iMainRessyaPos);
					}
				}
			}

			if (!bErased)
			{
				itrOrder++;
			}
		}
	}

	//◎駅時刻のある(停車)ものを、ソート後コンテナに移す
	if ( !bAbort )
	{
		for ( int idx = 0 ; idx < (int)contRessyaIndexBeforSort.size() ; idx++ )
		{
			int iRessyaIndex = contRessyaIndexBeforSort[idx] ;

			const CentDedRessya* pRessya = pEstimateRessyaCont->getMuPtr()->get( iRessyaIndex ) ;
			CentDedEkiJikoku aEkiJikoku = pRessya->getCentDedEkiJikoku( aEkijikokuOrder.getEkiOrder() ) ;
			CdDedJikoku	aJikoku = pRessya->getEkiJikoku( aEkijikokuOrder ) ;

			//if ( aEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya )
			if ( aEkiJikoku.getEkiatsukai() != CentDedEkiJikoku::Ekiatsukai_None )
			{
				contRessyaIndexAfterSort.push_back( iRessyaIndex ) ;
				contRessyaIndexBeforSort.erase(	contRessyaIndexBeforSort.begin() + idx ) ;
				idx -- ;
			}
		}
	}

	if ( !bAbort )
	{
		if ( pIfProgress != NULL )
		{
			int iResult = pIfProgress->onNotifyProgress( 
				contRessyaIndexAfterSort.size() ,
				pEstimateRessyaCont->size() ) ;
			if ( iResult != 0 )
			{
				bAbort = true ;
			}
		}
	}	

	//◎ソート後コンテナを、駅時刻でソートする。
	//
	//@code
	//ソート後
	//RessyaIdx │2   │5   │
	//G         │0012│0020│
	//着/発 　　│発　│発  │
	//@endcode	        
	//
	//@code
	//ソート前
	//RessyaIdx │0   │1   │3   │4   │6   │
	//G         │NULL│NULL│NULL│NULL│NULL│
	//着/発 　　│着  │着  │着  │着  │着  │
	//@endcode	        
	if ( !bAbort )
	{
		std::sort( 
			contRessyaIndexAfterSort.begin() , 
			contRessyaIndexAfterSort.end() ,
			CCompareRessyaIndex_Ekijikoku( 
				pEstimateRessyaCont , 
				aEkijikokuOrder , 
				m_pDedRosen->getKitenJikoku() ) 
			) ;
	}



	if ( aEkijikokuOrder.getEkiJikokuItem() == CdDedJikokuOrder::EkiJikokuItem_Chaku)
	{
		//	着時刻でソートの場合

		//◎ソート前列車を、ソート対象駅より前の停車駅で乗り換えのできるソート後列車の前に配置
		if ( !bAbort )
		{
			bAbort = sortRessyaIndex_TransferToSortedRessya( 
				pEstimateRessyaCont ,
				&contRessyaIndexBeforSort , 
				&contRessyaIndexAfterSort , 
				aEkijikokuOrder , 
				pIfProgress ) ; 
		}

		//◎ソート前列車を、ソート対象駅よりあとの停車駅で乗り換えのできるソート後列車の後ろに配置
		if ( !bAbort )
		{
			bAbort = sortRessyaIndex_TransferFromSortedRessya( 
				pEstimateRessyaCont ,
				&contRessyaIndexBeforSort , 
				&contRessyaIndexAfterSort , 
				aEkijikokuOrder , 
				pIfProgress ) ; 
		}

		//◎ソート前列車を、すべての停車駅で乗り換えのできるソート後列車の後ろに配置
		if ( !bAbort )
		{
			bAbort = sortRessyaIndex_TransferFromSortedRessya( 
				pEstimateRessyaCont ,
				&contRessyaIndexBeforSort , 
				&contRessyaIndexAfterSort , 
				CdDedJikokuOrder( 0 , CdDedJikokuOrder::EkiJikokuItem_Chaku )  , 
				pIfProgress ) ; 
		}
	}
	else
	{
		//	発時刻でソート

		//◎ソート前列車を、ソート対象駅よりあとの停車駅で乗り換えのできるソート後列車の後ろに配置
		if ( !bAbort )
		{
			bAbort = sortRessyaIndex_TransferFromSortedRessya( 
				pEstimateRessyaCont ,
				&contRessyaIndexBeforSort , 
				&contRessyaIndexAfterSort , 
				aEkijikokuOrder , 
				pIfProgress ) ; 
		}

		//◎ソート前列車を、ソート対象駅より前の停車駅で乗り換えのできるソート後列車の前に配置
		if ( !bAbort )
		{
			bAbort = sortRessyaIndex_TransferToSortedRessya( 
				pEstimateRessyaCont ,
				&contRessyaIndexBeforSort , 
				&contRessyaIndexAfterSort , 
				aEkijikokuOrder , 
				pIfProgress ) ; 
		}
		//◎ソート前列車を、すべての停車駅で乗り換えのできるソート後列車の前に配置
		if ( !bAbort )
		{
			bAbort = sortRessyaIndex_TransferToSortedRessya( 
				pEstimateRessyaCont ,
				&contRessyaIndexBeforSort , 
				&contRessyaIndexAfterSort , 
				CdDedJikokuOrder( pEkiCont->size() - 1 , CdDedJikokuOrder::EkiJikokuItem_Hatsu) , 
				pIfProgress ) ; 
		}

	}


	//◎残ったソート前列車(ソート対象駅(F)からの利用が不可能な列車)をソート後列車に移動
	//　　　　　　○全ソート前列車のループ
	//　　　　　　　　○[終着駅がソート対象駅より後]ソート前列車をソート前列車コンテナから削除し、
	//　　　　　　　　　　　　　ソート後列車コンテナの先頭に挿入
	//　　　　　　　　○[else]ソート前列車をソート前列車コンテナから削除し、
	//　　　　　　　　　　　　　ソート後列車コンテナの末尾に挿入
	if ( !bAbort )
	{
		int idxTo = 0 ;
		for ( int idx = 0 ; idx < (int)contRessyaIndexBeforSort.size() ; idx ++ )
		{
			int iRessyaIndex = contRessyaIndexBeforSort[idx] ;

			const CentDedRessya* pRessya = pRessyaCont->getMuPtr()->get( iRessyaIndex ) ;
			if ( !pRessya->isNull() && pRessya->getSyuuchakuEki() > aEkijikokuOrder.getEkiOrder() )
			{
				contRessyaIndexBeforSort.erase(
					contRessyaIndexBeforSort.begin() + idx ) ;
				idx -- ;

				contRessyaIndexAfterSort.insert( 
					contRessyaIndexAfterSort.begin() + idxTo , 
					iRessyaIndex ) ;
				idxTo ++ ;

			}
		}
	}
	


	//最終的にソートできなかった列車Indexは、末尾に追加
	{
		contRessyaIndexAfterSort.insert( 
			contRessyaIndexAfterSort.end() ,
			contRessyaIndexBeforSort.begin() ,
			contRessyaIndexBeforSort.end() ) ;
		contRessyaIndexBeforSort.clear() ;
	}

	//contRessyaIndexOrderに基づき、並び替えを行います。
	//(1)軸列車の位置を探す(itrAfter)
	//(2)contRessyaIndexAfterSortから、軸列車以外を削除する
	//(3)軸列車の位置に、contRessyaIndexTemp(contRessyaIndexOrderの各要素から、末尾の軸列車Posを削除したもの)を挿入する
	//(4)軸列車が重複しているので、元からある方を削除する
	{
		for (auto itrOrder = contRessyaIndexOrder.begin(); itrOrder != contRessyaIndexOrder.end(); itrOrder++)
		{
			int iMainRessyaIndex = itrOrder->at(itrOrder->back());
			vector<int> contRessyaIndexTemp = *itrOrder;
			contRessyaIndexTemp.pop_back();

			//auto itrAfter = contRessyaIndexAfterSort.begin();
			//for (; itrAfter != contRessyaIndexAfterSort.end(); itrAfter++)
			//{
			//	if (*itrAfter == iMainRessyaIndex)
			//	{
			//		break;
			//	}
			//}
			//if (itrAfter == contRessyaIndexAfterSort.end())
			//{
			//	continue;
			//}



			for (int idxErase = 0; idxErase<(int)contRessyaIndexTemp.size(); idxErase++)
			{
				if (contRessyaIndexTemp[idxErase] == iMainRessyaIndex)
				{
					continue;
				}
				for (auto itrAfterSearch = contRessyaIndexAfterSort.begin(); itrAfterSearch != contRessyaIndexAfterSort.end(); itrAfterSearch++)
				{
					if (*itrAfterSearch == contRessyaIndexTemp[idxErase])
					{
						contRessyaIndexAfterSort.erase(itrAfterSearch);
						break;
					}
				}
			}

			int iMainRessyaPos = 0;
			for (; iMainRessyaPos < (int)contRessyaIndexAfterSort.size(); iMainRessyaPos++)
			{
				if(contRessyaIndexAfterSort[iMainRessyaPos] == iMainRessyaIndex)
				{
					break;
				}
			}

			contRessyaIndexAfterSort.erase(contRessyaIndexAfterSort.begin() + iMainRessyaPos);
			contRessyaIndexAfterSort.insert(contRessyaIndexAfterSort.begin() + iMainRessyaPos, contRessyaIndexTemp.begin(), contRessyaIndexTemp.end());
		}
	}

	//ソート結果を muRessyaIndexOrder に格納
	{
		muRessyaIndexOrder->erase( 0 , INT_MAX ) ;
		CaMui<int>( muRessyaIndexOrder ).insert( &CaMup_vector<vector<int>>( &contRessyaIndexAfterSort ) ) ; ;
	}
};


int CDedRessyaSoater_Transfer::calcNorikaeSec( 
	const CentDedEkiJikoku& aEkiJikokuFrom , 
	const CentDedEkiJikoku& aEkiJikokuTo ,
	const CdDedJikoku& jikokuKitenJikoku ) 
{
	int iNorikaeSec = -1 ;
	//if ( aEkiJikokuFrom.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya &&
	//	aEkiJikokuTo.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya )
	if ( aEkiJikokuFrom.getEkiatsukai() != CentDedEkiJikoku::Ekiatsukai_None &&
		aEkiJikokuTo.getEkiatsukai() != CentDedEkiJikoku::Ekiatsukai_None )
	{

		//	乗り換え元列車着時刻→乗り換え先列車発時刻
		CdDedJikoku	jikokuFrom = aEkiJikokuFrom.getChakujikoku() ;
		CdDedJikoku	jikokuTo = aEkiJikokuTo.getHatsujikoku() ;
		// --------------------------------
		if ( !jikokuFrom.isNull() && !jikokuTo.isNull() )
		{
			int iComp = jikokuTo.compare( jikokuFrom , jikokuKitenJikoku ) ;
			if ( iComp >= 0 )
			{
				//	発時刻は着時刻よりあと(ダイヤグラム起点時刻をまたいでいない)

				iNorikaeSec = jikokuTo.subJikoku( jikokuFrom ) ;
				if ( iNorikaeSec < 0 )
				{
					iNorikaeSec = -1 ;
				}
			}
		}
	}
		//iNorikaeSec = 乗り換え時間(秒数)
		//	乗り換え不可能なら、-1 ;

	return iNorikaeSec ;
}

} //namespace entDgr
