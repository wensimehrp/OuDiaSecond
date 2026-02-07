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
//	CentDedRosen.cpp
// ****************************************************************
*/
#include "stdafx.h"
#include <assert.h>
#include <vector>
#include <algorithm>

#include "NsMu/CaMui.h" 
#include "CentDedRosen.h"
//#include "../entDgr/CDedOperationConnecter.h"
#include "CDedOperationConnecter.h"
#include "NsOu/dynamic_castOu.h"
#include "NsOu/OuNew.h"

using namespace std ;


#ifdef _MFC_VER 
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

namespace entDed{

const TCHAR nameRessyasyubetsuDefault[] = _T("普通") ; 

// ----------------------------------------------------------------
//	CentDedRosen::CXCentDedEkiCont
// ----------------------------------------------------------------
	// ********************************
	//	コンストラクタ
	// ********************************

	// ********************************
	//	Mui
	// ********************************

int CentDedRosen::CXCentDedEkiCont::insert( const CentDedEki& element , int iIndex )
{
	int iRv = 0 ;
	if ( iRv >= 0 ){
		if ( iIndex == INT_MAX ){
			iIndex = size() ;
		}
		if ( !( 0 <= iIndex && iIndex <= size() ) ){
			iRv = -1 ;
		}
	}	
	if ( iRv >= 0 ){
		iRv = super::insert( element , iIndex ) ;
	}
	return ( iRv ) ;
}
int CentDedRosen::CXCentDedEkiCont::erase( int iIndex  , int iSize ) 
{
	int iRv = 0 ;
	
	if ( iRv >= 0 ){
		if ( iIndex == INT_MAX && iSize == INT_MAX ){
			iRv = -1 ;
		}	else if ( iIndex == INT_MAX ){
			iIndex = size() - iSize ;
		}	else if ( iSize == INT_MAX ){
			iSize = size() - iIndex ;
		}
		if ( !( 0 <= iIndex && iIndex + iSize <= size() ) ){
			iRv = -1 ;
		}
	}	
	
	if ( iRv >= 0 ){
		iRv = super::erase( iIndex , iSize ) ;
	}

	return ( iRv ) ;
};
		// ********************************
		//@name CentDedEkiCont-関連
		// ********************************
CentDedRosen*  CentDedRosen::CXCentDedEkiCont::getRosen()
{
	CentDedRosen* pOuter = (CentDedRosen*)( ((char*)this) - offsetof( CentDedRosen , m_CentDedEkiCont ) ) ;
	return pOuter ;
}
const CentDedRosen*  CentDedRosen::CXCentDedEkiCont::getRosen()const 
{
	const CentDedRosen* pOuter = (const CentDedRosen*)( ((char*)this) - offsetof( CentDedRosen , m_CentDedEkiCont ) ) ;
	return pOuter ;
}

// ----------------------------------------------------------------
//	CentDedRosen::CXCentDedRessyasyubetsuCont
// ----------------------------------------------------------------
	// ********************************
	//	コンストラクタ
	// ********************************
CentDedRosen::CXCentDedRessyasyubetsuCont::	CXCentDedRessyasyubetsuCont() 
{
	//既定の列車種別の追加は、CentDedRosen::CentDedRosen で行います。
}
	// ********************************
	//	Mui
	// ********************************


		// ********************************
		//@name CentDedEkiCont-関連
		// ********************************
CentDedRosen* CentDedRosen::CXCentDedRessyasyubetsuCont::getRosen()
{
	CentDedRosen* pOuter = (CentDedRosen*)( ((char*)this) - offsetof( CentDedRosen , m_CentDedRessyasyubetsuCont ) ) ;
	return pOuter ;
}
const CentDedRosen* CentDedRosen::CXCentDedRessyasyubetsuCont:: getRosen()const 
{
	const CentDedRosen* pOuter = (const CentDedRosen*)( ((char*)this) - offsetof( CentDedRosen , m_CentDedRessyasyubetsuCont ) ) ;
	return pOuter ;
}

// ----------------------------------------------------------------
//	CentDedRosen::CXCentDedDiaCont
// ----------------------------------------------------------------
		// ********************************
		//	コンストラクタ
		// ********************************

		// ********************************
		//@name CentDedDiaCont-関連
		// ********************************
CentDedRosen* CentDedRosen::CXCentDedDiaCont::getRosen()
{
	CentDedRosen* pOuter = (CentDedRosen*)( ((char*)this) - offsetof( CentDedRosen , m_CentDedDiaCont ) ) ;
	return pOuter ;
}
const CentDedRosen* CentDedRosen::CXCentDedDiaCont::getRosen()const 
{
	const CentDedRosen* pOuter = (const CentDedRosen*)( ((char*)this) - offsetof( CentDedRosen , m_CentDedDiaCont ) ) ;
	return pOuter ;
}
		

// ****************************************************************
//	CentDedRosen
// ****************************************************************

// ********************************
//	コンストラクタ
// ********************************
CentDedRosen::CentDedRosen() 
	: m_jikokuKitenJikoku( 0 , 0 , 0 ) 
	, m_iDiagramDgrYZahyouKyoriDefault( 60 )
	, m_iEnableOperation(0)
	, m_bOperationNumberReverse(false)
	, m_bOperationCrossKitenJikoku(true)
	, m_iKijunDiaIndex(0)
	, m_bDisableHiddenSyubetsu(false)
{
	//	デフォルトの『列車種別』の名前を設定します。
	m_CentDedRessyasyubetsuCont.insert( 
		CentDedRessyasyubetsu( nameRessyasyubetsuDefault , _T("")  ) , 
		INT_MAX ) ;
}
	

CentDedRosen::CentDedRosen( const CentDedRosen& value )
	: m_CentDedRessyasyubetsuCont( value.m_CentDedRessyasyubetsuCont ) 
{
	m_strName = value.m_strName ;
	m_jikokuKitenJikoku = value.m_jikokuKitenJikoku ;
	m_iDiagramDgrYZahyouKyoriDefault = value.m_iDiagramDgrYZahyouKyoriDefault ;
	m_strComment = value.m_strComment ;
	m_iEnableOperation = value.m_iEnableOperation;
	m_strKudariDiaAlias = value.m_strKudariDiaAlias;
	m_strNoboriDiaAlias = value.m_strNoboriDiaAlias;
	m_bOperationNumberReverse = value.m_bOperationNumberReverse;
	m_bOperationCrossKitenJikoku = value.m_bOperationCrossKitenJikoku;
	m_iKijunDiaIndex = value.m_iKijunDiaIndex;
	m_bDisableHiddenSyubetsu = value.m_bDisableHiddenSyubetsu;

	CaMui<CentDedEki>( &m_CentDedEkiCont ).insert( &value.m_CentDedEkiCont , 0 , INT_MAX , 0 ) ;
	m_CentDedDiaCont = value.m_CentDedDiaCont ;
}
	
CentDedRosen& CentDedRosen::operator=( const CentDedRosen& value )
{
	// --------------------------------
	//	それまでの値を破棄
	// --------------------------------

	m_CentDedDiaCont.erase( 0 , INT_MAX ) ;

	//	デフォルト列車のみにします。
	m_CentDedRessyasyubetsuCont.erase( 1 , INT_MAX ) ;
	m_CentDedRessyasyubetsuCont.set( 
		CentDedRessyasyubetsu( nameRessyasyubetsuDefault , _T("")  ) , 
		INT_MAX ) ;

	m_CentDedEkiCont.erase( 0 , INT_MAX ) ;

	// --------------------------------
	//	値をコピー
	// --------------------------------
	
	m_strName = value.m_strName ;
	m_jikokuKitenJikoku = value.m_jikokuKitenJikoku ;
	m_iDiagramDgrYZahyouKyoriDefault = value.m_iDiagramDgrYZahyouKyoriDefault ;
	m_strComment = value.m_strComment ;
	m_iEnableOperation = value.m_iEnableOperation;
	m_CentDedEkiCont = value.m_CentDedEkiCont ;
	m_CentDedEkiCont.adjustBrunchLoopCont();
	m_CentDedRessyasyubetsuCont = value.m_CentDedRessyasyubetsuCont ;
	m_strKudariDiaAlias = value.m_strKudariDiaAlias;
	m_strNoboriDiaAlias = value.m_strNoboriDiaAlias;
	m_bOperationNumberReverse = value.m_bOperationNumberReverse;
	m_bOperationCrossKitenJikoku = value.m_bOperationCrossKitenJikoku;
	m_iKijunDiaIndex = value.m_iKijunDiaIndex;
	m_bDisableHiddenSyubetsu = value.m_bDisableHiddenSyubetsu;

	m_CentDedDiaCont = value.m_CentDedDiaCont ;

	return ( *this ) ;
}

	
// ********************************
//	CentDedRosen
// ********************************
	// ********************************
	//@name 属性
	// ********************************
	// ********************************
	//@name 包含-CentDedEki
	// ********************************
	
	// ********************************
	//@name 包含-CentDedRessyasyubetsu
	// ********************************

	
	// ********************************
	//@name 包含-CentDedDia
	// ********************************

	// ********************************
	//@name 操作
	// ********************************
void CentDedRosen::insert( 
	const CentDedRosen& rosenToAdd_enter ,
	int iEkiIndexToInsert ) 
{
	CentDedRosen rosenToAdd = rosenToAdd_enter ;
	//○組入れ先駅Index小(起点側)・組入れ先Index大(終点側)を決定
	//	○[組入れ先が始発駅]
	//　　	○組入れ先駅Index小=-1
	//　　	○組入れ先駅Index大=入力された組入れ先の駅Index
	//	○[組入れ先が中間駅]
	//　　	○組入れ先駅Index小=入力された組入れ先の駅Index
	//　　	○組入れ先駅Index大=入力された組入れ先の駅Index
	//	○[組入れ先が終着駅]
	//　　	○組入れ先駅Index小=駅数-1
	//　　	○組入れ先駅Index大=駅数
	int iEkiIndexToInsertMin = -1 ;
	int iEkiIndexToInsertMax = -1 ;
	{
		//○[組入れ先が始発駅]
		if ( iEkiIndexToInsert == 0 )
		{
			iEkiIndexToInsertMin = -1 ;
			iEkiIndexToInsertMax = iEkiIndexToInsert ;
		}
		//○[組入れ先が中間駅]
		//	○組入れ先駅Index小=入力された組入れ先の駅Index
		//	○組入れ先駅Index大=入力された組入れ先の駅Index
		else if ( 0 < iEkiIndexToInsert &&
			iEkiIndexToInsert < getCentDedEkiCont()->size() - 1 )
		{
			iEkiIndexToInsertMin = iEkiIndexToInsert ;
			iEkiIndexToInsertMax = iEkiIndexToInsert ;
		}
		//○[組入れ先が終着駅]
		//	○組入れ先駅Index小=駅数-1
		//	○組入れ先駅Index大=駅数
		else
		{
			iEkiIndexToInsertMin = getCentDedEkiCont()->size() - 1 ;
			iEkiIndexToInsertMax = getCentDedEkiCont()->size() ;
		}
	}
	//○[組入れ先が中間駅]なら、その駅を分割
	if ( 0 < iEkiIndexToInsertMin &&
			iEkiIndexToInsertMax < getCentDedEkiCont()->size() - 1 )
	{
		//　○組入れ先駅Index小=入力された組入れ先の駅Index
		//　│組入れ先駅Index大=入力された組入れ先の駅Index+1
		iEkiIndexToInsertMax = iEkiIndexToInsertMin + 1 ;

		//　○組入れ先駅Index小と同名駅を、組入れ先駅Index+1の位置に追加
		//　│組入れ先駅Index小の駅は下り着時刻
		//　│組入れ先駅Index大の駅は上り着時刻
		{
			CentDedEkiCont* pCentDedEkiCont = getCentDedEkiCont();

			//組み入れ駅が、派生駅の場合　・下り着or上り着
			//	分岐駅設定を解除
			//基幹駅の場合　・発着
			//	被分岐駅設定を解除
			//起点駅の場合　・上り着or発着
			//	終点側の設定を、追加された側(下側)に設定変更。
			//終点駅の場合　・下り着or発着
			//	追加された側(下側)の、環状線設定は解除
			//基幹駅かつ起点駅の場合　・発着
			//	被分岐駅設定を解除、終点側の設定を、追加された側(下側)に設定変更。
			//起点駅かつ終点駅の場合　・発着
			//	追加された側(下側)の、環状線設定は解除、終点側の設定を、追加された側(下側)に設定変更。
			//終点駅かつ基幹駅の場合　・発着
			//	被分岐駅設定を解除、追加された側(下側)の、環状線設定は解除

			//→まず、分岐駅設定・被分岐駅設定は解除
			//→追加後、下側の環状線設定は解除
			//→上側の駅を起点駅とする終点駅の環状線設定を、下側の駅にずらす。

			//組み入れ駅を基幹駅とする派生駅が有ったら、分岐駅設定を解除する。
			CentDedEki*	pDedEkiInsertMin = pCentDedEkiCont->getMuPtr()->get(iEkiIndexToInsertMin);
			if (pDedEkiInsertMin->getBrunchCoreEkiIndex() >= 0)
			{
				pDedEkiInsertMin->setBrunchCoreEkiIndex(-1);
			}
			else if (pDedEkiInsertMin->getEkikibo() == CentDedEki::EEkikibo::Ekikibo_Syuyou &&
				pDedEkiInsertMin->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku)
			{
				for (int idx = 0; idx < pCentDedEkiCont->size(); idx++)
				{
					CentDedEki*	pCentDedEkiSearch = pCentDedEkiCont->getMuPtr()->get(idx);
					if (pCentDedEkiSearch->getBrunchCoreEkiIndex() == iEkiIndexToInsertMin)
					{
						pCentDedEkiSearch->setBrunchCoreEkiIndex(-1);
					}
				}
			}

			pCentDedEkiCont->insert(*pDedEkiInsertMin, iEkiIndexToInsertMax);
			CentDedEki*	pDedEkiInsertMax = pCentDedEkiCont->getMuPtr()->get(iEkiIndexToInsertMax);
			pDedEkiInsertMin->setEkijikokukeisiki(CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku);
			pDedEkiInsertMax->setEkijikokukeisiki(CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku);

			if (pDedEkiInsertMax->getLoopOriginEkiIndex() >= 0)
			{
				pDedEkiInsertMax->setLoopOriginEkiIndex(-1);
			}
			for (int idx = iEkiIndexToInsertMax + 1; idx < pCentDedEkiCont->size(); idx++)
			{
				CentDedEki*	pCentDedEkiSearch = pCentDedEkiCont->getMuPtr()->get(idx);
				if (pCentDedEkiSearch->getLoopOriginEkiIndex() == iEkiIndexToInsertMin)
				{
					pCentDedEkiSearch->setLoopOriginEkiIndex(iEkiIndexToInsertMax);
				}
			}

			//組入れ先駅Index小の駅は、次駅が組み入れた駅になるので、次駅までの距離を初期化しておく。
			pDedEkiInsertMin->setNextEkiDistance(0);
		}

		//○全ダイヤのループ
		CentDedDiaCont* pCentDedDiaCont = &m_CentDedDiaCont ;
		int idxDia ;
		for ( idxDia = 0 ; idxDia < pCentDedDiaCont->size() ; idxDia ++ )
		{
			CentDedDia* pCentDedDia = pCentDedDiaCont->getMuPtr()->get( idxDia ) ;
			//○下り列車全列車のループ
			//│　○組入れ先駅Order小・組入れ先駅Order大を求める
			{
				CentDedRessyaCont* pCentDedRessyaCont = pCentDedDia->getCentDedRessyaCont( Ressyahoukou_Kudari ) ;
				int iEkiOrderToInsertMin = -1 ;
				int iEkiOrderToInsertMax = -1 ;
				{
					int iEkiOrder1 = pCentDedRessyaCont->EkiOrderOfEkiIndex( iEkiIndexToInsertMin ) ;
					int iEkiOrder2 = pCentDedRessyaCont->EkiOrderOfEkiIndex( iEkiIndexToInsertMax ) ;
					iEkiOrderToInsertMin = min( iEkiOrder1 , iEkiOrder2 ) ;
					iEkiOrderToInsertMax = max( iEkiOrder1 , iEkiOrder2 ) ;
				}

				for ( int idxRessya = 0 ; idxRessya < pCentDedRessyaCont->size() ; idxRessya ++ )
				{
					CentDedRessya* pCentDedRessya = pCentDedRessyaCont->getMuPtr()->get( idxRessya ) ;
					CentDedEkiJikoku aEkiJikokuToInserMin = pCentDedRessya->getCentDedEkiJikoku( iEkiOrderToInsertMin ) ;
					CentDedEkiJikoku aEkiJikokuToInserMax = pCentDedRessya->getCentDedEkiJikoku( iEkiOrderToInsertMax ) ;

					//│　○[組入れ先駅Order小が始発駅の列車]
					//│　│組入れ先駅Order大に、組入れ先Order小をコピー
					//│　↓組入れ先駅Order小は、運行なしとする。
					if ( pCentDedRessya->getSihatsuEki() == iEkiOrderToInsertMin )
					{
						aEkiJikokuToInserMax = aEkiJikokuToInserMin ;
						aEkiJikokuToInserMin.setEkiatsukai( CentDedEkiJikoku::Ekiatsukai_None ) ;
					}
					//│　○[組入れ先駅Index小が中間駅の列車]
					//│　│　○組入れ先駅Order大に、組入れ先駅Order小の駅時刻をコピー
					//			(1.04.06追加)Index小の発時刻と、Index大の着時刻を削除
					else if ( pCentDedRessya->getSihatsuEki() < iEkiOrderToInsertMin && 
						iEkiOrderToInsertMin < pCentDedRessya->getSyuuchakuEki() ) 
					{
						aEkiJikokuToInserMax = aEkiJikokuToInserMin ;
						if (!aEkiJikokuToInserMin.getChakujikoku().isNull())
						{
							aEkiJikokuToInserMin.setHatsujikoku(CdDedJikoku());
						}
						if (!aEkiJikokuToInserMax.getHatsujikoku().isNull())
						{
							aEkiJikokuToInserMax.setChakujikoku(CdDedJikoku());
						}
					}
					//│　○[組入れ先駅Order小が終着駅の列車]
					//│　　組入れ先駅Order小は、そのままとする。
					//│　　組入れ先駅Order大は、運行なしとする。
					else if ( pCentDedRessya->getSyuuchakuEki() == iEkiOrderToInsertMin )
					{
						aEkiJikokuToInserMax.setEkiatsukai( CentDedEkiJikoku::Ekiatsukai_None ) ;
					}

					pCentDedRessya->setCentDedEkiJikoku( iEkiOrderToInsertMin , aEkiJikokuToInserMin ) ;
					pCentDedRessya->setCentDedEkiJikoku( iEkiOrderToInsertMax , aEkiJikokuToInserMax ) ;
				}
			}

			//○上り列車全列車のループ
			//  　○組入れ先駅Order小・組入れ先駅Order大を求める
			{
				CentDedRessyaCont* pCentDedRessyaCont = pCentDedDia->getCentDedRessyaCont(Ressyahoukou_Nobori);
				int iEkiOrderToInsertMin = pCentDedRessyaCont->EkiOrderOfEkiIndex(iEkiIndexToInsertMax);
				int iEkiOrderToInsertMax = pCentDedRessyaCont->EkiOrderOfEkiIndex(iEkiIndexToInsertMin);

				for (int idxRessya = 0; idxRessya < pCentDedRessyaCont->size(); idxRessya++)
				{
					CentDedRessya* pCentDedRessya = pCentDedRessyaCont->getMuPtr()->get(idxRessya);

					CentDedEkiJikoku aEkiJikokuToInserMin = pCentDedRessya->getCentDedEkiJikoku(iEkiOrderToInsertMin);
					CentDedEkiJikoku aEkiJikokuToInserMax = pCentDedRessya->getCentDedEkiJikoku(iEkiOrderToInsertMax);

					//○[組入れ先駅Order大が始発駅の列車]
					//│組入れ先駅Order大は、そのままとする。
					//↓組入れ先駅Order小は、運行なしとする。
					if (pCentDedRessya->getSihatsuEki() == iEkiOrderToInsertMax)
					{
						aEkiJikokuToInserMin.setEkiatsukai(CentDedEkiJikoku::Ekiatsukai_None);
					}
					//○[組入れ先駅Index大が中間駅の列車]
					//│　○組入れ先駅Index小に、組入れ先駅Index大の駅時刻をコピー
					//│　○組入れ先駅Index小の駅時刻を駅時刻形式(着時刻のみ)に合わせて補正
					//│　○(組入れ先駅Index小の発時刻をNULLに変更)
					//│　○組入れ先駅Index大の駅時刻を駅時刻形式(発時刻のみ)に合わせて補正
					//↓　○(組入れ先駅Index大の着時刻をNULLに変更)
					//			(1.04.06追加)Index小の発時刻と、Index大の着時刻を条件付きで削除
					else if (pCentDedRessya->getSihatsuEki() < iEkiOrderToInsertMax &&
						iEkiOrderToInsertMax < pCentDedRessya->getSyuuchakuEki())
					{
						aEkiJikokuToInserMin = aEkiJikokuToInserMax;
						//aRessyaTrackToInserMin = aRessyaTrackToInserMax;
						if (!aEkiJikokuToInserMin.getChakujikoku().isNull())
						{
							aEkiJikokuToInserMin.setHatsujikoku(CdDedJikoku());
						}
						if (!aEkiJikokuToInserMax.getHatsujikoku().isNull())
						{
							aEkiJikokuToInserMax.setChakujikoku(CdDedJikoku());
						}
					}
					//○[組入れ先駅Index大が終着駅の列車]
					//│組入れ先駅Index小に、駅時刻をコピー
					//↓組入れ先駅Index大は、運行なしとする。
					else if (pCentDedRessya->getSyuuchakuEki() == iEkiOrderToInsertMax)
					{
						aEkiJikokuToInserMin = aEkiJikokuToInserMax;
						aEkiJikokuToInserMax.setEkiatsukai(CentDedEkiJikoku::Ekiatsukai_None);
					}

					pCentDedRessya->setCentDedEkiJikoku(iEkiOrderToInsertMin, aEkiJikokuToInserMin);
					pCentDedRessya->setCentDedEkiJikoku(iEkiOrderToInsertMax, aEkiJikokuToInserMax);
				}

			}
		}
		//○組入れ先駅Index小の駅時刻を駅時刻形式に合わせて補正
		//│　◎駅時刻を駅時刻形式に合わせて補正
		//│　　　○[駅時刻形式に着時刻あり・発時刻なし、
		//│　  　│駅時刻に着時刻なし、発時刻あり]
		//│　  　↓着時刻には発時刻をコピー、発時刻はNULL。
		//│　  　○[駅時刻形式に着時刻なし・発時刻あり
		//│　  　│駅時刻に着時刻あり、発時刻なし]
		//│　  　↓発時刻には着時刻をコピー、着時刻はNULL。
		//│　  　○[駅が始発駅・
		//│　  　│駅時刻形式に着時刻あり・発時刻あり、
		//│　  　│駅時刻に着時刻あり、発時刻なし]
		//│　  　↓発時刻には着時刻をコピー、着時刻はNULL。
		//│　  　○[駅が終着駅・
		//│　  　　駅時刻形式に着時刻あり・発時刻あり
		//│　  　　駅時刻に着時刻なし、発時刻あり]
		//│　  　　着時刻には発時刻をコピー、発時刻はNULL。
		//○組入れ先駅Index大の駅時刻を駅時刻形式に合わせて補正
		adjustByEkijikokukeisiki( iEkiIndexToInsertMin ) ;
		adjustByEkijikokukeisiki( iEkiIndexToInsertMax ) ;
	}
	//○[組入れ先が起点駅]なら、その駅の駅時刻形式は[上り着時刻]とする
	//　　○[組入れ先駅Index小=-1,組入れ先駅Index大=0]
	//　　　　組入れ先駅Index大を上り着時刻とする
	//  　○組入れ先駅Index大の駅時刻を駅時刻形式に合わせて補正
	else if ( iEkiIndexToInsertMin == -1 &&
			iEkiIndexToInsertMax == 0 )
	{
		CentDedEkiCont* pCentDedEkiCont = getCentDedEkiCont() ;
		CentDedEki*	pDedEkiInsert = pCentDedEkiCont->getMuPtr()->get( iEkiIndexToInsertMax ) ;
		pDedEkiInsert->setEkijikokukeisiki( CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ) ;
		adjustByEkijikokukeisiki( iEkiIndexToInsertMax ) ;
	}
	//○[組入れ先が終点駅]なら、その駅の駅時刻形式は[下り着時刻]とする
	//　　○[組入れ先がIndex小=駅数-1 AND 組入れ先駅Index大=駅数]
	//　　　　組入れ先駅Index小を下り着時刻とする
	//  　○組入れ先駅Index小の駅時刻を駅時刻形式に合わせて補正
	//次駅までの距離を初期化しておく。
	else if ( iEkiIndexToInsertMin == getCentDedEkiCont()->size() - 1 &&
			iEkiIndexToInsertMax == getCentDedEkiCont()->size() ) 
	{
		CentDedEkiCont* pCentDedEkiCont = getCentDedEkiCont() ;
		CentDedEki*	pDedEkiInsert = pCentDedEkiCont->getMuPtr()->get( iEkiIndexToInsertMin ) ;
		pDedEkiInsert->setEkijikokukeisiki( CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ) ;
		adjustByEkijikokukeisiki( iEkiIndexToInsertMin ) ;
		pDedEkiInsert->setNextEkiDistance(0);
	}




	//○駅を追加
	//　　○組入れる路線ファイルの駅をすべて追加する。
	//　　　追加する駅Indexは、組入れ先駅Index小+1。
	//		○[組入れる路線ファイルの起点駅の駅時刻形式が発着以外]
	//		  その駅の駅時刻形式は[上り着時刻]とする
	//		○[組入れる路線ファイルの終点駅の駅時刻形式が発着以外]
	//		  その駅の駅時刻形式は[下り着時刻]とする
	//　　○組入れ先駅Index大に、追加した駅数を加算
	//	組み入れる終点駅の「次駅までの距離」を初期化する
	{
		CentDedEkiCont* pCentDedEkiCont = &m_CentDedEkiCont ;
		const CentDedEkiCont* pCentDedEkiContToAdd = rosenToAdd.getCentDedEkiCont() ;
		for ( int idxEki = 0 ; idxEki < pCentDedEkiContToAdd->size() ; idxEki ++ )
		{
			CentDedEki aEki = *pCentDedEkiContToAdd->getMuPtr()->get( idxEki ) ;
			if ( idxEki == 0 && aEki.getEkijikokukeisiki() != CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku )
			{
				aEki.setEkijikokukeisiki( CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ) ;
			}
			else if ( idxEki == pCentDedEkiContToAdd->size() - 1 && 
				aEki.getEkijikokukeisiki() != CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku )
			{
				aEki.setEkijikokukeisiki( CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ) ;
			}
			/*if (aEki.getBrunchCoreEkiIndex() >= 0 &&
				aEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku)
			{
				aEki.setBrunchCoreEkiIndex(
					aEki.getBrunchCoreEkiIndex()+ iEkiIndexToInsertMin+1 -
				(pCentDedEkiContToAdd->size()- idxEki));
			}
			else */if (aEki.getBrunchCoreEkiIndex() >= 0 &&
				aEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku)
			{
				aEki.setBrunchCoreEkiIndex(aEki.getBrunchCoreEkiIndex() + iEkiIndexToInsertMin + 1);
			}
			if (aEki.getLoopOriginEkiIndex() >= 0)
			{
				aEki.setLoopOriginEkiIndex(aEki.getLoopOriginEkiIndex() + iEkiIndexToInsertMin+1);
			}
			if (idxEki == pCentDedEkiContToAdd->size() - 1)
			{
				aEki.setNextEkiDistance(0);
			}

			pCentDedEkiCont->insert( 
				aEki ,
				iEkiIndexToInsertMin + 1 + idxEki ) ;


			iEkiIndexToInsertMax ++ ;

		}
		/**
			組み入れる路線の中に、下り着の派生駅(基幹駅が終点方向にある)がある場合は、
			BrunchCoreEkiIndexを修正します。
			これは、CentDedEki内のonEkiInsertで、本来不要なインクリメントが発生するからです。
			(onEkiInsertでは、BrunchCoreEkiIndexと駅数の関係性により、インクリメントを抑制する仕組みがあるが、
			組み入れの場合は、組み入れ先駅よりも下に、既存の駅があるため、末尾への組み入れ以外では不都合になる。)

		*/
		for (int idxEki = 0; idxEki < pCentDedEkiContToAdd->size(); idxEki++)
		{
			CentDedEki aEki = *pCentDedEkiContToAdd->getMuPtr()->get(idxEki);
			if (aEki.getBrunchCoreEkiIndex() >= 0 &&
				aEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku)
			{
				CentDedEki aEkiNew = *pCentDedEkiCont->getMuPtr()->get(iEkiIndexToInsertMin + 1 + idxEki);
				aEkiNew.setBrunchCoreEkiIndex(aEki.getBrunchCoreEkiIndex() + iEkiIndexToInsertMin + 1);

				pCentDedEkiCont->set(
					aEkiNew,
					iEkiIndexToInsertMin + 1 + idxEki);
			}
		}
	}

	//○[組入れ先が中間駅]なら、組入れ先駅Indexが途中駅となる列車は、
	//　　　　　　　　　　追加された駅の駅時刻を経由なしにする。
	if ( 0 < iEkiIndexToInsertMin &&
			iEkiIndexToInsertMax < getCentDedEkiCont()->size() - 1 )
	{
		//　　○全列車のループ
		//　　　　○下り・上りのループ
		//　　　　  　○組入れ先駅Order小・組入れ先駅Order大を求める
		//　　　　　　○[始発駅が組入れ先駅Order小より前 AND 
		//　　　　　　　終着駅が組入れ先駅Order大より後]
		//　　　　　　　組入れ先駅Order小+1～組入れ先駅Order大-1の駅扱いを
		//　　　　　　　経由なしにする。
		CentDedDiaCont* pCentDedDiaCont = &m_CentDedDiaCont ;
		int idxDia ;
		for ( idxDia = 0 ; idxDia < pCentDedDiaCont->size() ; idxDia ++ )
		{
			CentDedDia* pCentDedDia = pCentDedDiaCont->getMuPtr()->get( idxDia ) ;
			//○下り列車全列車のループ
			//│　○組入れ先駅Order小・組入れ先駅Order大を求める
			for ( int iRessyahoukou = Ressyahoukou_Kudari ;
				iRessyahoukou <= Ressyahoukou_Nobori ;
				iRessyahoukou ++ )
			{
				ERessyahoukou eRessyahoukou = (ERessyahoukou)iRessyahoukou ;

				CentDedRessyaCont* pCentDedRessyaCont = pCentDedDia->getCentDedRessyaCont( eRessyahoukou ) ;
				int iEkiOrderToInsertMin = -1 ;
				int iEkiOrderToInsertMax = -1 ;
				{
					int iEkiOrder1 = pCentDedRessyaCont->EkiOrderOfEkiIndex( iEkiIndexToInsertMin ) ;
					int iEkiOrder2 = pCentDedRessyaCont->EkiOrderOfEkiIndex( iEkiIndexToInsertMax ) ;
					iEkiOrderToInsertMin = min( iEkiOrder1 , iEkiOrder2 ) ;
					iEkiOrderToInsertMax = max( iEkiOrder1 , iEkiOrder2 ) ;
				}

				for ( int idxRessya = 0 ; idxRessya < pCentDedRessyaCont->size() ; idxRessya ++ )
				{
					//　　　　　　○[始発駅が組入れ先駅Order小より前 AND 
					//　　　　　　　終着駅が組入れ先駅Order大より後]
					//　　　　　　　組入れ先駅Order小+1～組入れ先駅Order大-1の駅扱いを
					//　　　　　　　運行なしにする。
					CentDedRessya* pCentDedRessya = pCentDedRessyaCont->getMuPtr()->get( idxRessya ) ;
					if ( pCentDedRessya->getSihatsuEki() < iEkiOrderToInsertMin && 
						iEkiOrderToInsertMax < pCentDedRessya->getSyuuchakuEki() )
					{

						CentDedEkiJikoku aEkijikokuNone( 
							CentDedEkiJikoku::Ekiatsukai_None ,
							CdDedJikoku() , CdDedJikoku() ) ;
						for ( int iEkiOrder = iEkiOrderToInsertMin + 1 ;
							iEkiOrder <= iEkiOrderToInsertMax - 1 ;
							iEkiOrder ++ )
						{
							pCentDedRessya->setCentDedEkiJikoku( iEkiOrder ,aEkijikokuNone ) ; 
						}
					}
				}
			}
		}
	}
	//○列車種別のマージ
	//　　○組入れる路線ファイルの列車種別によるループ
	//　　　　○[同名の列車種別が編集中の路線ファイルに存在しない]列車種別を
	//　　　　　編集中の路線ファイルに追加
	//　　　　○列車種別対照表(組入れる路線ファイルの列車種別Index→
	//　　　　　組入れる路線ファイルの列車種別Index の対照表を作成
	deque<int>	arRessyasyubetsuIdx_AddedToThis ;
	{
		CentDedRessyasyubetsuCont* pCentDedRessyasyubetsuCont = this->getCentDedRessyasyubetsuCont() ;
		const CentDedRessyasyubetsuCont* pCentDedRessyasyubetsuContToAdd = rosenToAdd.getCentDedRessyasyubetsuCont() ;
		

		const Mu<const CentDedRessyasyubetsu*>* muCentDedRessyasyubetsuToAdd =
				pCentDedRessyasyubetsuContToAdd->getMuPtr() ;
		Mu<CentDedRessyasyubetsu*>* muCentDedRessyasyubetsuThis =
			pCentDedRessyasyubetsuCont->getMuPtr();
		int iSizeThis = muCentDedRessyasyubetsuThis->size();
		for ( int idxToAdd = 0 ; idxToAdd < muCentDedRessyasyubetsuToAdd->size() ; idxToAdd ++ )
		{
			const CentDedRessyasyubetsu* pCentDedRessyasyubetsuToAdd = 
				muCentDedRessyasyubetsuToAdd->get( idxToAdd ) ;

			int idxThis = 0 ;
			for ( idxThis = 0 ; idxThis < muCentDedRessyasyubetsuThis->size() ; idxThis ++ )
			{
				const CentDedRessyasyubetsu* pCentDedRessyasyubetsuThis = muCentDedRessyasyubetsuThis->get( idxThis ) ;
				if ( pCentDedRessyasyubetsuThis->getSyubetsumei() == 
					pCentDedRessyasyubetsuToAdd->getSyubetsumei() )
				{
					break ;
				}
			}
			//idxThis = 『追加する路線ファイル』の列車種別[idxToAdd] と同名の
			//	thisの列車種別のインデクス。
			//	なければ、  muCentDedRessyasyubetsuThis->size()

			if ( idxThis == muCentDedRessyasyubetsuThis->size() )
			{
				//	同名の種別がない場合は、
				//	this に追加します。
				pCentDedRessyasyubetsuCont->insert( *pCentDedRessyasyubetsuToAdd ) ;
			}
			arRessyasyubetsuIdx_AddedToThis.push_back( idxThis ) ;
		}

		/**
			親種別の修整
			pCentDedRessyasyubetsuContに追加された種別に親種別が設定されている場合、
			その親種別が、pCentDedRessyasyubetsuContのどこにあるかを、arRessyasyubetsuIdx_AddedToThisをもとに調整します。
		*/
		for (int idxAdded = iSizeThis; idxAdded < muCentDedRessyasyubetsuThis->size(); idxAdded++)
		{
			CentDedRessyasyubetsu* pCentDedRessyasyubetsuAdded =
				muCentDedRessyasyubetsuThis->get(idxAdded);
			if (pCentDedRessyasyubetsuAdded->getParentSyubetsuIndex() >= 0 &&
				pCentDedRessyasyubetsuAdded->getParentSyubetsuIndex() < (int)arRessyasyubetsuIdx_AddedToThis.size())
			{
				pCentDedRessyasyubetsuAdded->setParentSyubetsuIndex(
					arRessyasyubetsuIdx_AddedToThis[pCentDedRessyasyubetsuAdded->getParentSyubetsuIndex()]);
			}
		}
	}
	//arRessyasyubetsuIdx_AddedToThis[追加する路線ファイル』の列車種別インデクス] = 
	//	thisの列車種別インデクス

	//○ダイヤのマージ
	//　　○組入れる路線ファイルのダイヤによるループ
	//　　　　○[同名のダイヤが編集中の路線ファイルに存在しない]空のダイヤを
	//　　　　　編集中の路線ファイルに追加
	//　　　　○ダイヤ対照表(組入れる路線ファイルのダイヤIndex→
	//　　　　　組入れる路線ファイルのダイヤIndex の対照表を作成

	deque<int>	arDiaIdx_AddedToThis ;
	{
		CentDedDiaCont* pCentDedDiaCont = this->getCentDedDiaCont() ;
		const CentDedDiaCont* pCentDedDiaContToAdd = rosenToAdd.getCentDedDiaCont() ;
		
		const Mu<const CentDedDia*>* muCentDedDiaToAdd =
				pCentDedDiaContToAdd->getMuPtr() ;
		for ( int idxToAdd = 0 ; idxToAdd < muCentDedDiaToAdd->size() ; idxToAdd ++ )
		{
			const CentDedDia* pCentDedDiaToAdd = 
				muCentDedDiaToAdd->get( idxToAdd ) ;

			Mu<CentDedDia*>* muCentDedDiaThis =
				pCentDedDiaCont->getMuPtr() ;
			int idxThis = 0 ;
			for ( idxThis = 0 ; idxThis < muCentDedDiaThis->size() ; idxThis ++ )
			{
				const CentDedDia* pCentDedDiaThis = muCentDedDiaThis->get( idxThis ) ;
				if ( pCentDedDiaThis->getName() == 
					pCentDedDiaToAdd->getName() )
				{
					break ;
				}
			}
			//idxThis = 『追加する路線ファイル』のダイヤと同名の
			//	thisのダイヤのインデクス。
			//	なければ、  muCentDedDiaThis->size()

			if ( idxThis == muCentDedDiaThis->size() )
			{
				//	同名のダイヤがない場合は、
				//	this に
				//	列車が空のダイヤを追加します。
				//	（ダイヤオブジェクトを直接追加すると、列車も追加されるため、
				//	うまくいきません) 
				CentDedEkiCont* pCentDedEkiCont = this->getCentDedEkiCont() ;
				CentDedRessyasyubetsuCont* pCentDedRessyasyubetsuCont = this->getCentDedRessyasyubetsuCont() ;
				CentDedDia	diaNew( pCentDedEkiCont->size() ) ;
				diaNew.setName( pCentDedDiaToAdd->getName() ) ;
				pCentDedDiaCont->insert( diaNew ) ;
			}
			arDiaIdx_AddedToThis.push_back( idxThis ) ;
		}

	}
	//arDiaIdx_AddedToThis[追加する路線ファイル』のダイヤインデクス] = 
	//	thisのダイヤインデクス

	//○組入れる路線ファイルの列車を、編集中の路線ファイルに追加
	//　　○組入れる路線ファイルのダイヤによるループ
	//　　　　○全列車のループ
	//　　　　　　○列車を追加。
	//　　　　　　　追加するダイヤは、ダイヤ対照表にしたがって変換
	//　　　　　　　列車種別Indexは、列車種別対照表に従って変換
	//
	{
		const Mu<const CentDedDia*>* muCentDedDiaToAdd =
			((const CentDedDiaCont*)rosenToAdd.getCentDedDiaCont())->getMuPtr() ;

		for ( int idxDiaToAdd = 0 ; idxDiaToAdd < muCentDedDiaToAdd->size() ; idxDiaToAdd ++ )
		{
			const CentDedDia* pCentDedDiaToAdd = muCentDedDiaToAdd->get( idxDiaToAdd ) ;

			Mu<CentDedDia*>* muCentDedDiaThis =	this->getCentDedDiaCont()->getMuPtr() ;
			CentDedDia* pCentDedDiaThis = muCentDedDiaThis->get( arDiaIdx_AddedToThis[idxDiaToAdd] ) ;
			//pCentDedDiaThis = 列車のコピー先となる CentDedDia ;

			//下り列車→上り列車
			for ( int idxRessyahoukou = (int)Ressyahoukou_Kudari ;
				idxRessyahoukou <= (int)Ressyahoukou_Nobori ;
				idxRessyahoukou ++ )
			{

				ERessyahoukou eRessyahoukou = (ERessyahoukou)idxRessyahoukou ;
				const CentDedRessyaCont* pCentDedRessyaContToAdd = pCentDedDiaToAdd->getCentDedRessyaCont( eRessyahoukou ) ;
				const Mu<const CentDedRessya*>* muCentDedRessyaToAdd = pCentDedRessyaContToAdd->getMuPtr() ;
				CentDedRessyaCont* pCentDedRessyaContThis = pCentDedDiaThis->getCentDedRessyaCont( eRessyahoukou ) ;

				int iEkiOrderToInsert = -1 ;
				if ( eRessyahoukou == Ressyahoukou_Kudari )
				{
					iEkiOrderToInsert = pCentDedRessyaContThis->EkiOrderOfEkiIndex( iEkiIndexToInsertMin + 1 ) ;
				}
				else
				{
					iEkiOrderToInsert = pCentDedRessyaContThis->EkiOrderOfEkiIndex( iEkiIndexToInsertMax - 1 ) ;
				}
				//iEkiOrderToInsert = 組入れる路線ファイルの駅Order0の列車を挿入する、
				//	thisの駅Order

				for ( int idxRessyaToAdd = 0 ; idxRessyaToAdd < muCentDedRessyaToAdd->size() ; idxRessyaToAdd ++ )
				{
					//	現在編集中の路線ファイルに、組入れる路線ファイルの列車を挿入
					//	列車種別・駅時刻は、このあとに修正
					const CentDedRessya* pRessyaToAdd = muCentDedRessyaToAdd->get( idxRessyaToAdd ) ;
					pCentDedRessyaContThis->insert( *pRessyaToAdd ) ;
					CentDedRessya* pRessyaAdded = pCentDedRessyaContThis->getMuPtr()->get( INT_MAX ) ;
					//pRessyaAdded = 組入れる路線ファイルに追加された列車
					//	列車種別・駅時刻は、このあとに修正

					//	列車種別インデクスを、
					//	現在編集中の路線ファイルに合わせて更新。
					pRessyaAdded->setRessyasyubetsuIndex( 
						arRessyasyubetsuIdx_AddedToThis[ pRessyaToAdd->getRessyasyubetsuIndex() ] ) ;

					//	駅時刻を修正
					for ( int iEkiOrder = 0 ; iEkiOrder < pCentDedRessyaContThis->getEkiCount() ; iEkiOrder ++ )
					{
						int iEkiOrderToAdd = iEkiOrder - iEkiOrderToInsert ;
						//iEkiOrderToAdd = thisのiEkiOrderに対応する、
						//	組入れる路線ファイルの駅Order

						if ( 0 <= iEkiOrderToAdd && iEkiOrderToAdd < pCentDedRessyaContToAdd->getEkiCount() )
						{
							//	組入れる路線ファイルの駅Orderに対応する場合は、
							//	組入れる路線ファイルの駅時刻をコピー
							CentDedEkiJikoku aEkiJikokuToAdd = pRessyaToAdd->getCentDedEkiJikoku( iEkiOrderToAdd ) ; 
							pRessyaAdded->setCentDedEkiJikoku( iEkiOrder , aEkiJikokuToAdd ) ;

						}
						else
						{
							//	組入れる路線ファイルの駅Orderに対応しない駅に対しては、
							//	運行なしを設定
							pRessyaAdded->setCentDedEkiJikoku( iEkiOrder , CentDedEkiJikoku() ) ;
						}
					}


				}
			}	
		}
	}


	/**
		路線外始発終着駅名の調整について
		組入れ先駅Index小と組入れ先駅Index小+1について、組入れ先駅Index小+1の駅名を、小の中から検索して、
		無かった場合は小に追加、全て確認した後、小+1側の駅作業の調整を行う
		組入れ先駅Index大と組入れ先駅Index大-1についても同様
		adjustBrunchLoopを行ったのち、mergeOuterTerminalを行う
	*/
	//○[組入れ先駅Index小と組入れ先駅Index小+1で、駅名が同一]駅を併合
	if ( 0 <= iEkiIndexToInsertMin )
	{
		CentDedEkiCont* pCentDedEkiContThis = getCentDedEkiCont() ;
		CentDedEki*	pEkiToInsertMin = pCentDedEkiContThis->getMuPtr()->get( iEkiIndexToInsertMin ) ;
		CentDedEki*	pEkiToInsertMin_1 = pCentDedEkiContThis->getMuPtr()->get( iEkiIndexToInsertMin + 1 ) ;
		if ( pEkiToInsertMin->getEkimei() == pEkiToInsertMin_1->getEkimei() )
		{
			//　　○組入れ先駅Index小の駅時刻形式を発着に変更 駅時刻形式に依存する値を変更
			pEkiToInsertMin->setEkijikokukeisiki( CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ) ;

			pEkiToInsertMin->setBrunchCoreEkiIndex(-1);
			pEkiToInsertMin->setBrunchOpposite(false);
			pEkiToInsertMin->setJikokuhyouTrackOmit(false);


			//駅番線の調整を行う。組入れ先駅Index小より組入れ先駅Index小+1の番線数が多い場合は
			//超過する分を、組入れ先駅Index小に追加する。
			//在線表表示省略設定も、組入れ先駅Index小+1から組入れ先駅Index小に追加する

			//if (pEkiToInsertMin->getEkiTrack2Cont()->size() < pEkiToInsertMin_1->getEkiTrack2Cont()->size())
			//{//上のif文が偽の時は、下のfor文に入らないので、省略可
			for (int iEkiTrack2Index = pEkiToInsertMin->getEkiTrack2Cont()->size();
				iEkiTrack2Index < pEkiToInsertMin_1->getEkiTrack2Cont()->size();
				iEkiTrack2Index++)
			{
				pEkiToInsertMin->getEkiTrack2Cont()->insert(
					pEkiToInsertMin_1->getEkiTrack2Cont()->get(iEkiTrack2Index), INT_MAX);
				pEkiToInsertMin->addDiagramTrackOmit(pEkiToInsertMin_1->getDiagramTrackOmit(iEkiTrack2Index));
			}

			//路線外発着駅名の調整
			vector<int> iOuterTerminalMap;
			//iOuterTerminalMapContの初期化
			for (int idxot = 0; idxot < pEkiToInsertMin_1->getOuterTerminalEkimeiCount(); idxot++)
			{
				iOuterTerminalMap.push_back(idxot);
			}
			int iCompareResultOuterTerminal = pEkiToInsertMin_1->compareOuterTerminal(pEkiToInsertMin);
			//比較結果が-1,2,3だった場合は、CoreになくてTargetにあるものを、Coreに追加していく
			for (int idxot = 0; idxot < pEkiToInsertMin_1->getOuterTerminalEkimeiCount() &&
				(iCompareResultOuterTerminal >= 2 || iCompareResultOuterTerminal <= -1); idxot++)
			{
				OuterTerminal sOuterTerminal = pEkiToInsertMin_1->getOuterTerminal(idxot);
				int iOuterTerminalExsit = pEkiToInsertMin->searchOuterTerminalEkimei(sOuterTerminal.OuterTerminalEkimei);
				if (iOuterTerminalExsit < 0)
				{
					iOuterTerminalMap[idxot] = pEkiToInsertMin->addOuterTerminalEkimei(sOuterTerminal);
					//pEkiToInsertMin->insertOuterTerminalEkimei(sOuterTerminal, INT_MAX);
					//iOuterTerminalMap[idxot] = pEkiToInsertMin->getOuterTerminalEkimeiCount() - 1;
				}
				else
				{
					iOuterTerminalMap[idxot] = iOuterTerminalExsit;
				}
			}

			m_CentDedDiaCont.adjustBrunchLoopOuterTerminal(
				{ iEkiIndexToInsertMin + 1 },
				iOuterTerminalMap);

			//組入れ先駅Index小+1の次駅までの距離および個別背景色を、組入れ先駅Index小に書き込み
			pEkiToInsertMin->setNextEkiDistance(pEkiToInsertMin_1->getNextEkiDistance());
			pEkiToInsertMin->setDiagramColorNextEki(pEkiToInsertMin_1->getDiagramColorNextEki());

			//駅規模、組入れ先駅Index小+1が主要駅で、組入れ先駅Index小が一般駅なら、組入れ先駅Index小を主要駅に
			if (pEkiToInsertMin->getEkikibo() == CentDedEki::EEkikibo::Ekikibo_Ippan &&
				pEkiToInsertMin_1->getEkikibo() == CentDedEki::EEkikibo::Ekikibo_Syuyou)
			{
				pEkiToInsertMin->setEkikibo(CentDedEki::EEkikibo::Ekikibo_Syuyou);
			}

			//作業欄数の変更 組入れ先駅Index小+1と組入れ先駅Index小の大きい方を設定
			pEkiToInsertMin->setJikokuhyouOperationOrigin(
				max(pEkiToInsertMin->getJikokuhyouOperationOrigin(),
					pEkiToInsertMin_1->getJikokuhyouOperationOrigin()));
			pEkiToInsertMin->setJikokuhyouOperationTerminal(
				max(pEkiToInsertMin->getJikokuhyouOperationTerminal(),
					pEkiToInsertMin_1->getJikokuhyouOperationTerminal()));

			//駅名略称 組入れ先駅Index小+1に設定があり、組入れ先駅Index小が空の場合は、小にコピー
			if (pEkiToInsertMin->getEkimeiJikokuhyouRyaku().empty() &&
				!pEkiToInsertMin_1->getEkimeiJikokuhyouRyaku().empty())
			{
				pEkiToInsertMin->setEkimeiJikokuhyouRyaku(pEkiToInsertMin_1->getEkimeiJikokuhyouRyaku());
			}

			//駅名ダイヤ(運用一覧)略称 組入れ先駅Index小+1に設定があり、組入れ先駅Index小が空の場合は、小にコピー
			if (pEkiToInsertMin->getEkimeiDiagramRyaku().empty() &&
				!pEkiToInsertMin_1->getEkimeiDiagramRyaku().empty())
			{
				pEkiToInsertMin->setEkimeiDiagramRyaku(pEkiToInsertMin_1->getEkimeiDiagramRyaku());
			}

			/**
				カスタマイズ時刻表表示設定 時刻・番線とも、どちらかの駅で有効なら、表示を有効にする。
				種別変更絡みは、必要なし(組入れ先駅Index小+1は元の路線の始発駅なので、基本表示なしなので)
			*/
			if (!pEkiToInsertMin->getJikokuhyouChakuJikokuDisplayKudari() &&
				pEkiToInsertMin_1->getJikokuhyouChakuJikokuDisplayKudari())
			{
				pEkiToInsertMin->setJikokuhyouChakuJikokuDisplayKudari(true);
			}
			if (!pEkiToInsertMin->getJikokuhyouHatsuJikokuDisplayKudari() &&
				pEkiToInsertMin_1->getJikokuhyouHatsuJikokuDisplayKudari())
			{
				pEkiToInsertMin->setJikokuhyouHatsuJikokuDisplayKudari(true);
			}

			if (!pEkiToInsertMin->getJikokuhyouChakuJikokuDisplayNobori() &&
				pEkiToInsertMin_1->getJikokuhyouChakuJikokuDisplayNobori())
			{
				pEkiToInsertMin->setJikokuhyouChakuJikokuDisplayNobori(true);
			}
			if (!pEkiToInsertMin->getJikokuhyouHatsuJikokuDisplayNobori() &&
				pEkiToInsertMin_1->getJikokuhyouHatsuJikokuDisplayNobori())
			{
				pEkiToInsertMin->setJikokuhyouHatsuJikokuDisplayNobori(true);
			}



			//　　○全ダイヤのループ
			//        ○全下り列車のループ
			//　　　　　　○[組入れ先駅Index小が運行なし]
			//　　　　　　　組入れ先駅Index小+1の駅時刻を組入れ先駅Index小にコピー
			//　　　　○全上り列車のループ
			//　　　　　　○[組入れ先駅Index小が運行なし]
			//　　　　　　　組入れ先駅Index小+1の駅時刻を組入れ先駅Index小にコピー
			//組入れ先駅Index小と組入れ先駅Index小+1の主本線が異なる場合に、
			//組入れ先駅Index小+1の駅時刻を組入れ先駅Index小にコピーする場合は、
			CentDedDiaCont* pCentDedDiaCont = this->getCentDedDiaCont() ;
			for ( int idxDia = 0 ; idxDia < pCentDedDiaCont->size() ; idxDia ++ )
			{
				CentDedDia* pDia = pCentDedDiaCont->getMuPtr()->get( idxDia ) ;
				for ( int iRessyahoukou = Ressyahoukou_Kudari ;
					iRessyahoukou <= Ressyahoukou_Nobori ;
					iRessyahoukou ++ )
				{
					ERessyahoukou eRessyahoukou = (ERessyahoukou)iRessyahoukou ;
					
					CentDedRessyaCont* pRessyaCont = pDia->getCentDedRessyaCont( eRessyahoukou ) ;
					int iEkiOrderToInsertMin = pRessyaCont->EkiOrderOfEkiIndex( iEkiIndexToInsertMin ) ;
					int iEkiOrderToInsertMin_1 = pRessyaCont->EkiOrderOfEkiIndex( iEkiIndexToInsertMin + 1 ) ;
					for ( int idxRessya = 0 ; idxRessya < pRessyaCont->size() ; idxRessya ++ )
					{
						CentDedRessya* pRessya = pRessyaCont->getMuPtr()->get( idxRessya ) ;
						
						CentDedEkiJikoku aEkijikoku = pRessya->getCentDedEkiJikoku( iEkiOrderToInsertMin ) ;
						if ( aEkijikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_None )
						{
							aEkijikoku = pRessya->getCentDedEkiJikoku( iEkiOrderToInsertMin_1 ) ;
							pRessya->setCentDedEkiJikoku( iEkiOrderToInsertMin ,aEkijikoku ) ;
						}
					}
				}
			}
			//分岐・環状線設定の修整
			for (int idx = iEkiIndexToInsertMin + 2; idx < pCentDedEkiContThis->size(); idx++)
			{
				CentDedEki* pEki = pCentDedEkiContThis->getMuPtr()->get(idx);
				if (pEki->getBrunchCoreEkiIndex() == iEkiIndexToInsertMin + 1)
				{
					pEki->setBrunchCoreEkiIndex(iEkiIndexToInsertMin);
				}
				if (pEki->getLoopOriginEkiIndex() == iEkiIndexToInsertMin + 1)
				{
					pEki->setLoopOriginEkiIndex(iEkiIndexToInsertMin);
				}
			}
			
			//　　○組入れ先駅Index小+1の駅を削除
			pCentDedEkiContThis->erase( iEkiIndexToInsertMin + 1 ) ;
			iEkiIndexToInsertMax -- ;
		}
	}

	//○[組入れ先駅Index大と組入れ先駅Index大-1で、駅名が同一]駅を併合
	if ( iEkiIndexToInsertMax < getCentDedEkiCont()->size() - 1 )
	{
		CentDedEkiCont* pCentDedEkiContThis = getCentDedEkiCont() ;
		CentDedEki*	pEkiToInsertMax = pCentDedEkiContThis->getMuPtr()->get( iEkiIndexToInsertMax ) ;
		CentDedEki*	pEkiToInsertMax_1 = pCentDedEkiContThis->getMuPtr()->get( iEkiIndexToInsertMax - 1 ) ;
		if ( pEkiToInsertMax->getEkimei() == pEkiToInsertMax_1->getEkimei() )
		{
			//○組入れ先駅Index大の駅時刻形式を発着に変更 駅時刻形式に依存する値を変更
			pEkiToInsertMax->setEkijikokukeisiki( CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku ) ;

			pEkiToInsertMax->setBrunchCoreEkiIndex(-1);
			pEkiToInsertMax->setBrunchOpposite(false);
			pEkiToInsertMax->setJikokuhyouTrackOmit(false);

			//駅番線の調整を行う。組入れ先駅Index大より組入れ先駅Index大-1の番線数が多い場合は
			//超過する分を、組入れ先駅Index大に追加する。
			//在線表表示省略設定も、組入れ先駅Index大-1から組入れ先駅Index大に追加する
			for (int iEkiTrack2Index = pEkiToInsertMax->getEkiTrack2Cont()->size();
				iEkiTrack2Index < pEkiToInsertMax_1->getEkiTrack2Cont()->size();
				iEkiTrack2Index++)
			{
				pEkiToInsertMax->getEkiTrack2Cont()->insert(
					pEkiToInsertMax_1->getEkiTrack2Cont()->get(iEkiTrack2Index), INT_MAX);
				pEkiToInsertMax->addDiagramTrackOmit(pEkiToInsertMax_1->getDiagramTrackOmit(iEkiTrack2Index));
			}

			//路線外発着駅名の調整
			vector<int> iOuterTerminalMap;
			//iOuterTerminalMapContの初期化
			for (int idxot = 0; idxot < pEkiToInsertMax_1->getOuterTerminalEkimeiCount(); idxot++)
			{
				iOuterTerminalMap.push_back(idxot);
			}
			int iCompareResultOuterTerminal = pEkiToInsertMax_1->compareOuterTerminal(pEkiToInsertMax);
			//比較結果が-1,2,3だった場合は、CoreになくてTargetにあるものを、Coreに追加していく
			for (int idxot = 0; idxot < pEkiToInsertMax_1->getOuterTerminalEkimeiCount() &&
				(iCompareResultOuterTerminal >= 2 || iCompareResultOuterTerminal <= -1); idxot++)
			{
				OuterTerminal sOuterTerminal = pEkiToInsertMax_1->getOuterTerminal(idxot);
				int iOuterTerminalExsit = pEkiToInsertMax->searchOuterTerminalEkimei(sOuterTerminal.OuterTerminalEkimei);
				if (iOuterTerminalExsit < 0)
				{
					iOuterTerminalMap[idxot] = pEkiToInsertMax->addOuterTerminalEkimei(sOuterTerminal);
					//pEkiToInsertMin->insertOuterTerminalEkimei(sOuterTerminal, INT_MAX);
					//iOuterTerminalMap[idxot] = pEkiToInsertMin->getOuterTerminalEkimeiCount() - 1;
				}
				else
				{
					iOuterTerminalMap[idxot] = iOuterTerminalExsit;
				}
			}

			m_CentDedDiaCont.adjustBrunchLoopOuterTerminal(
				{ iEkiIndexToInsertMax - 1 },
				iOuterTerminalMap);

			//駅規模、組入れ先駅Index大-1が主要駅で、組入れ先駅Index大が一般駅なら、組入れ先駅Index大を主要駅に
			if (pEkiToInsertMax->getEkikibo() == CentDedEki::EEkikibo::Ekikibo_Ippan &&
				pEkiToInsertMax_1->getEkikibo() == CentDedEki::EEkikibo::Ekikibo_Syuyou)
			{
				pEkiToInsertMax->setEkikibo(CentDedEki::EEkikibo::Ekikibo_Syuyou);
			}

			//作業欄数の変更 組入れ先駅Index大-1と組入れ先駅Index大の大きい方を設定
			pEkiToInsertMax->setJikokuhyouOperationOrigin(
				max(pEkiToInsertMax->getJikokuhyouOperationOrigin(),
					pEkiToInsertMax_1->getJikokuhyouOperationOrigin()));
			pEkiToInsertMax->setJikokuhyouOperationTerminal(
				max(pEkiToInsertMax->getJikokuhyouOperationTerminal(),
					pEkiToInsertMax_1->getJikokuhyouOperationTerminal()));

			//駅名略称 組入れ先駅Index大-1に設定があり、組入れ先駅Index大が空の場合は、大にコピー
			if (pEkiToInsertMax->getEkimeiJikokuhyouRyaku().empty() &&
				!pEkiToInsertMax_1->getEkimeiJikokuhyouRyaku().empty())
			{
				pEkiToInsertMax->setEkimeiJikokuhyouRyaku(pEkiToInsertMax_1->getEkimeiJikokuhyouRyaku());
			}

			//駅名ダイヤ(運用一覧)略称 組入れ先駅Index大-1に設定があり、組入れ先駅Index大が空の場合は、大にコピー
			if (pEkiToInsertMax->getEkimeiDiagramRyaku().empty() &&
				!pEkiToInsertMax_1->getEkimeiDiagramRyaku().empty())
			{
				pEkiToInsertMax->setEkimeiDiagramRyaku(pEkiToInsertMax_1->getEkimeiDiagramRyaku());
			}

			/**
				カスタマイズ時刻表表示設定 時刻・番線とも、どちらかの駅で有効なら、表示を有効にする。
				種別変更絡みは、必要なし(組入れ先駅Index大-1は元の路線の始発駅なので、基本表示なしなので)
			*/
			if (!pEkiToInsertMax->getJikokuhyouChakuJikokuDisplayKudari() &&
				pEkiToInsertMax_1->getJikokuhyouChakuJikokuDisplayKudari())
			{
				pEkiToInsertMax->setJikokuhyouChakuJikokuDisplayKudari(true);
			}
			if (!pEkiToInsertMax->getJikokuhyouHatsuJikokuDisplayKudari() &&
				pEkiToInsertMax_1->getJikokuhyouHatsuJikokuDisplayKudari())
			{
				pEkiToInsertMax->setJikokuhyouHatsuJikokuDisplayKudari(true);
			}

			if (!pEkiToInsertMax->getJikokuhyouChakuJikokuDisplayNobori() &&
				pEkiToInsertMax_1->getJikokuhyouChakuJikokuDisplayNobori())
			{
				pEkiToInsertMax->setJikokuhyouChakuJikokuDisplayNobori(true);
			}
			if (!pEkiToInsertMax->getJikokuhyouHatsuJikokuDisplayNobori() &&
				pEkiToInsertMax_1->getJikokuhyouHatsuJikokuDisplayNobori())
			{
				pEkiToInsertMax->setJikokuhyouHatsuJikokuDisplayNobori(true);
			}


			//○全ダイヤのループ
			//　　○全下り列車のループぴ
			//　　　　○[組入れ先駅Index大が運行なし]
			//　　　　　組入れ先駅Index大-1の駅時刻を組入れ先駅Index大にコピー
			//　　○全上り列車のループぴ
			//　　　　○[組入れ先駅Index大が運行なし]
			//　　　　　組入れ先駅Index大-1の駅時刻を組入れ先駅Index大にコピー
			//組入れ先駅Index大と組入れ先駅Index大+1の主本線が異なる場合に、
			//組入れ先駅Index大-1の駅時刻を組入れ先駅Index大にコピーする場合は、
			//組入れ先駅Index大での列車番線を「組入れ先駅Index大-1での主本線を個別指定」に変更する
			CentDedDiaCont* pCentDedDiaCont = this->getCentDedDiaCont() ;
			for ( int idxDia = 0 ; idxDia < pCentDedDiaCont->size() ; idxDia ++ )
			{
				CentDedDia* pDia = pCentDedDiaCont->getMuPtr()->get( idxDia ) ;
				for ( int iRessyahoukou = Ressyahoukou_Kudari ;
					iRessyahoukou <= Ressyahoukou_Nobori ;
					iRessyahoukou ++ )
				{
					ERessyahoukou eRessyahoukou = (ERessyahoukou)iRessyahoukou ;
					
					CentDedRessyaCont* pRessyaCont = pDia->getCentDedRessyaCont( eRessyahoukou ) ;
					int iEkiOrderToInsertMax = pRessyaCont->EkiOrderOfEkiIndex( iEkiIndexToInsertMax ) ;
					int iEkiOrderToInsertMax_1 = pRessyaCont->EkiOrderOfEkiIndex( iEkiIndexToInsertMax - 1 ) ;
					for ( int idxRessya = 0 ; idxRessya < pRessyaCont->size() ; idxRessya ++ )
					{
						CentDedRessya* pRessya = pRessyaCont->getMuPtr()->get( idxRessya ) ;
						
						CentDedEkiJikoku aEkijikoku = pRessya->getCentDedEkiJikoku( iEkiOrderToInsertMax ) ;
						if ( aEkijikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_None )
						{
							aEkijikoku = pRessya->getCentDedEkiJikoku( iEkiOrderToInsertMax_1 ) ;
							pRessya->setCentDedEkiJikoku( iEkiOrderToInsertMax ,aEkijikoku ) ;
						}
					}
				}
			}
			//　　○組入れ先駅Index大-1の駅を削除
			pCentDedEkiContThis->erase( iEkiIndexToInsertMax - 1 ) ;
			iEkiIndexToInsertMax -- ;
		}
	}

	//路線外発着駅名のmergeを行う
	{
		m_CentDedEkiCont.adjustBrunchLoopCont();

		this->mergeOuterTerminal();
	}
	//○、『追加する路線ファイル』のコメントを、『現在編集している路線ファイル』のコメントの末尾に追加。
	{
		tstring strComment = this->getComment() ;
		strComment += _T("\n\n") ;
		strComment += rosenToAdd.getComment() ;
		this->setComment( strComment ) ;
	}
}

CentDedRosen CentDedRosen::createSubRosen( 
		int iEkiIndex , int iEkiCount ,bool bEnableOuter)const 
{
	CentDedRosen rosenNew = *this ;
	/*
	(0) 路線外発着の設定
		駅Indexが0からiEkiIndex-1およびiEkiIndex + iEkiCountから駅数-1の間に始発終着駅がある場合、その駅を路線外発着とします。
	
	*/
	if(bEnableOuter)
	{
		Mu<CentDedDia*>* muCentDedDia = rosenNew.getCentDedDiaCont()->getMuPtr();

		for (int idxDia = 0; idxDia < muCentDedDia->size(); idxDia++)
		{
			CentDedDia* pCentDedDia = muCentDedDia->get(idxDia);
			//pCentDedDia = 対象となるダイヤ

			//下り列車→上り列車
			for (int idxRessyahoukou = (int)Ressyahoukou_Kudari;
				idxRessyahoukou <= (int)Ressyahoukou_Nobori;
				idxRessyahoukou++)
			{
				ERessyahoukou eRessyahoukou = (ERessyahoukou)idxRessyahoukou;
				CentDedRessyaCont* pCentDedRessyaCont = pCentDedDia->getCentDedRessyaCont(eRessyahoukou);
				int iEkiOrderO;	//新しい路線の起点(列車方向に依る)
				int iEkiOrderT;	//新しい路線の終点(列車方向に依る)
				if (eRessyahoukou == Ressyahoukou_Kudari)
				{
					iEkiOrderO = pCentDedRessyaCont->EkiOrderOfEkiIndex(iEkiIndex);
					iEkiOrderT = pCentDedRessyaCont->EkiOrderOfEkiIndex(iEkiIndex + iEkiCount - 1);
				}
				else
				{
					iEkiOrderO = pCentDedRessyaCont->EkiOrderOfEkiIndex(iEkiIndex + iEkiCount - 1);
					iEkiOrderT = pCentDedRessyaCont->EkiOrderOfEkiIndex(iEkiIndex);
				}
				for (int idxRessya = 0; idxRessya < pCentDedRessyaCont->size(); idxRessya++)
				{
					CentDedRessya* pRessya = pCentDedRessyaCont->getMuPtr()->get(idxRessya);
					if (pRessya->isNull())
					{
						continue;
					}
					int iValidSihatsuEki = pRessya->getValidSihatsuEki();
					int iValidSyuuchakuEki = pRessya->getValidSyuuchakuEki();
					if (iValidSihatsuEki == -1 ||
						iValidSyuuchakuEki == -1)
					{
						continue;
					}
					if (iValidSyuuchakuEki <= iEkiOrderO)
					{
						//この列車の運行されている区間が、iEkiOrderOまでなら、対象ではありません。
						continue;
					}
					if (iValidSihatsuEki >= iEkiOrderT)
					{
						//この列車の運行されている区間が、iEkiOrderT以遠なら、対象ではありません。
						continue;
					}

					if (iValidSihatsuEki < iEkiOrderO)
					{
						//この列車の始発駅がiEkiOrderOより前の場合
						for (int ord = iEkiOrderO; ord < iEkiOrderT; ord++)
						{
							if(pRessya->isRunBetweenNextEki(ord) &&
								!pRessya->getCentDedEkiJikoku(ord).getHatsujikoku().isNull())
							//if (pRessya->getCentDedEkiJikoku(ord).getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya ||
							//	pRessya->getCentDedEkiJikoku(ord).getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka)
							{
								/**
									Ver2.0 
									iEkiOrderOより前に有効始発駅があり、ordが新たな有効始発駅になる場合は、
									有効始発駅とordの間は、運行なし（経由なし相当）で埋め尽くされているわけではないので、
									環状線を回っていると推測し、路線外発着に設定する。
								*/
								//if (getCentDedEkiCont()->isSameBrunchLoopGroup(
								//		pRessya->getSihatsuEki(),
								//		ord,
								//		eRessyahoukou))
								//{
								//	//この列車の始発駅と、切り出し区間内での最初の停車・通過駅が分岐・環状で同一グループなら、
								//	//路線外発着設定は行いません。
								//	break;
								//}
								//切り出し区間内の最初の停車または通過駅を新たな始発駅にします。
								CentDedEkiJikoku aCentDedEkiJikokuOld = pRessya->getCentDedEkiJikoku(iValidSihatsuEki);
								//始発駅の駅時刻を取得し、NULL時刻ではない場合のみ、先の処理を行います。
								//これは、路線外始発にする場合、始発駅時刻を設定する必要があるからです。
								//Ver2.0有効始発駅なので、発時刻は必ず存在する
								//if (!aCentDedEkiJikokuOld.getHatsujikoku(true).isNull())
								//{
									const CentDedBeforeOperation aFirstOperation = pRessya->getFirstOperation();

									vector<tstring> strOperationNumber;
									tstring strInOutLinkCode;
									//tstring strOuterEkimei = _T("");
									OuterTerminal aOuterTerminal;
									CdDedJikoku aJikoku;
									//この列車の始発駅作業が路線外始発の場合は、その作業から路線外始発駅名、路線外始発駅時刻、運用番号、入出区連携コードを引き継ぎます。
									//それ以外の場合は、始発駅の駅名、発時刻、運用番号を取得します。(出区の場合は、入出区連携コードも取得)
									if (aFirstOperation.getBOperation()== CentDedBeforeOperation::EBOperation::BOperation_Outer)
									{
										int iEkiIndexSihatsu = getCentDedEkiCont()->EkiIndexOfEkiOrder(eRessyahoukou, iValidSihatsuEki);
										//strOuterEkimei = getCentDedEkiCont()->get(iEkiIndexSihatsu).getOuterTerminalEkimei(
										//	aFirstOperation.getOuterShihatsuekiIndex());
										aOuterTerminal = getCentDedEkiCont()->get(iEkiIndexSihatsu).getOuterTerminal(
											aFirstOperation.getOuterShihatsuekiIndex());
										aJikoku = aFirstOperation.getOuterShihatsuJikoku();
										strOperationNumber = aFirstOperation.getOperationNumberOriginal();
										strInOutLinkCode = aFirstOperation.getInOutLinkCode();
									}
									else
									{
										int iEkiIndexSihatsu = getCentDedEkiCont()->EkiIndexOfEkiOrder(eRessyahoukou, iValidSihatsuEki);
										aOuterTerminal.OuterTerminalEkimei = getCentDedEkiCont()->get(iEkiIndexSihatsu).getEkimei();
										aOuterTerminal.OuterTerminalJikokuRyaku = getCentDedEkiCont()->get(iEkiIndexSihatsu).getEkimeiJikokuhyouRyaku();
										aOuterTerminal.OuterTerminalDiaRyaku = getCentDedEkiCont()->get(iEkiIndexSihatsu).getEkimeiDiagramRyaku();
										//strOuterEkimei = getCentDedEkiCont()->get(iEkiIndexSihatsu).getEkimei();
										aJikoku = aCentDedEkiJikokuOld.getHatsujikoku(true);
										if (aFirstOperation.getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Out)
										{
											strOperationNumber = aFirstOperation.getOperationNumberOriginal();
											strInOutLinkCode = aFirstOperation.getInOutLinkCode();
										}
										else
										{
											strOperationNumber = aFirstOperation.getOperationNumberTemp();
											//前列車接続始まりの場合は、入出区連携コードは空のまま
										}
									}

									//取得した始発駅名が、新しい始発駅に登録されているかを調べます。
									//見つからない場合は登録します。
									CentDedEki* pCentDedEki = rosenNew.getCentDedEkiCont()->getMuPtr()->get(
										getCentDedEkiCont()->EkiIndexOfEkiOrder(eRessyahoukou, ord));
									int iOuterTerminalIndex = pCentDedEki->searchOuterTerminalEkimei(aOuterTerminal.OuterTerminalEkimei);
									if (iOuterTerminalIndex == -1)
									{
										//OuterTerminal sOuterTerminal;
										//sOuterTerminal.OuterTerminalEkimei = strOuterEkimei;
										//iOuterTerminalIndex = pCentDedEki->addOuterTerminalEkimei(aOuterTerminal);
										deque<int> iEkiIndexBrunchLoop;
										int iSize = getCentDedEkiCont()->getEkiIndexBrunchLoop(
											getCentDedEkiCont()->EkiIndexOfEkiOrder(eRessyahoukou, ord), iEkiIndexBrunchLoop);
										for (int idx = 0; idx < iSize; idx++)
										{
											CentDedEki* pCentDedEkiTarget = rosenNew.getCentDedEkiCont()->getMuPtr()->get(
												iEkiIndexBrunchLoop[idx]);
											iOuterTerminalIndex = pCentDedEkiTarget->addOuterTerminalEkimei(aOuterTerminal);
										}
									}

									//aCentDedRessyaTrackNewに作業を設定、
									//列車の始発駅を新しくし、RessyaTrackをsetします

									CentDedBeforeOperation	aOperationNewOuter(
										CentDedBeforeOperation::EBOperation::BOperation_Outer,
										iOuterTerminalIndex,
										aJikoku,
										pRessya->getCentDedEkiJikoku(ord).getChakujikoku(true),
										strOperationNumber,
										strInOutLinkCode);
									pRessya->setSihatsuEki(ord);
									CentDedBeforeOperationCont* pBeforeOperationCont = pRessya->getCentDedEkiJikokuCont()
										->getMuPtr()->get(ord)->getCentDedBeforeOperationCont();
									if (pRessya->getFirstOperation().isFirstOperation())
									{
										pBeforeOperationCont->set(aOperationNewOuter, 0);
									}
									else
									{
										pBeforeOperationCont->insert(aOperationNewOuter, 0);
									}
								//}
								break;
							}
						}
					}

					if (iValidSyuuchakuEki > iEkiOrderT)
					{
						//この列車の終着駅がiEkiOrderTより後ろの場合
						for (int ord = iEkiOrderT; ord > iEkiOrderO; ord--)
						{
							if (pRessya->isRunBetweenNextEki(ord-1) &&
								!pRessya->getCentDedEkiJikoku(ord).getChakujikoku().isNull())
							//if (pRessya->getCentDedEkiJikoku(ord).getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya ||
							//	pRessya->getCentDedEkiJikoku(ord).getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka)
							{
								/**
									Ver2.0
									iEkiOrderTより後に有効終着駅があり、ordが新たな有効始発駅になる場合は、
									有効終着駅とordの間は、運行なし（経由なし相当）で埋め尽くされているわけではないので、
									環状線を回っていると推測し、路線外発着に設定する。
								*/
								//if (getCentDedEkiCont()->isSameBrunchLoopGroup(
								//	pRessya->getSyuuchakuEki(),
								//	ord,
								//	eRessyahoukou))
								//{
								//	//この列車の終着駅と、切り出し区間内での最後の停車・通過駅が分岐・環状で同一グループなら、
								//	//路線外発着設定は行いません。
								//	break;
								//}
								//切り出し区間内の最後の停車または通過駅を新たな終着駅にします。
								CentDedEkiJikoku aCentDedEkiJikokuOld = pRessya->getCentDedEkiJikoku(iValidSyuuchakuEki);
								//終着駅の駅時刻を取得し、NULL時刻ではない場合のみ、先の処理を行います。
								//これは、路線外終着にする場合、終着駅時刻を設定する必要があるからです。
								//Ver2.0有効終着駅なので、着時刻は必ず存在する
								//if (!aCentDedEkiJikokuOld.getChakujikoku(true).isNull())
								//{
									const CentDedAfterOperation aLastOperation = pRessya->getLastOperation();

									//tstring strOuterEkimei = _T("");
									OuterTerminal aOuterTerminal;
									CdDedJikoku aJikoku;
									tstring strInOutLinkCode;
									//この列車の終着駅作業が路線外終着の場合は、その作業から路線外終着駅名、路線外終着駅時刻、入出区連携コードを引き継ぎます。
									//それ以外の場合は、終着駅の駅名、着時刻を取得します。(入区の場合は、入出区連携コードも取得)
									if (aLastOperation.getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
									{
										int iEkiIndexSyuuchaku = getCentDedEkiCont()->EkiIndexOfEkiOrder(eRessyahoukou, iValidSyuuchakuEki);
										//strOuterEkimei = getCentDedEkiCont()->get(iEkiIndexSyuuchaku).getOuterTerminalEkimei(
										//	aLastOperation.getOuterShuchakuekiIndex());
										aOuterTerminal = getCentDedEkiCont()->get(iEkiIndexSyuuchaku).getOuterTerminal(
											aLastOperation.getOuterShuchakuekiIndex());
										aJikoku = aLastOperation.getOuterShuchakuJikoku();
										strInOutLinkCode = aLastOperation.getInOutLinkCode();
									}
									else
									{
										int iEkiIndexSyuuchaku = getCentDedEkiCont()->EkiIndexOfEkiOrder(eRessyahoukou, iValidSyuuchakuEki);
										//strOuterEkimei = getCentDedEkiCont()->get(iEkiIndexSyuuchaku).getEkimei();
										aOuterTerminal.OuterTerminalEkimei = getCentDedEkiCont()->get(iEkiIndexSyuuchaku).getEkimei();
										aOuterTerminal.OuterTerminalJikokuRyaku = getCentDedEkiCont()->get(iEkiIndexSyuuchaku).getEkimeiJikokuhyouRyaku();
										aOuterTerminal.OuterTerminalDiaRyaku = getCentDedEkiCont()->get(iEkiIndexSyuuchaku).getEkimeiDiagramRyaku();
										aJikoku = aCentDedEkiJikokuOld.getChakujikoku(true);
										if (aLastOperation.getAOperation() == CentDedAfterOperation::EAOperation::AOperation_In)
										{
											strInOutLinkCode = aLastOperation.getInOutLinkCode();
										}
									}

									//取得した終着駅名が、新しい終着駅に登録されているかを調べます。
									//見つからない場合は登録します。
									CentDedEki* pCentDedEki = rosenNew.getCentDedEkiCont()->getMuPtr()->get(
										getCentDedEkiCont()->EkiIndexOfEkiOrder(eRessyahoukou, ord));
									int iOuterTerminalIndex = pCentDedEki->searchOuterTerminalEkimei(aOuterTerminal.OuterTerminalEkimei);
									if (iOuterTerminalIndex == -1)
									{
										//OuterTerminal sOuterTerminal;
										//sOuterTerminal.OuterTerminalEkimei = strOuterEkimei;
										//iOuterTerminalIndex = pCentDedEki->addOuterTerminalEkimei(sOuterTerminal);
										deque<int> iEkiIndexBrunchLoop;
										int iSize = getCentDedEkiCont()->getEkiIndexBrunchLoop(
											getCentDedEkiCont()->EkiIndexOfEkiOrder(eRessyahoukou, ord), iEkiIndexBrunchLoop);
										for (int idx = 0; idx < iSize; idx++)
										{
											CentDedEki* pCentDedEkiTarget = rosenNew.getCentDedEkiCont()->getMuPtr()->get(
												iEkiIndexBrunchLoop[idx]);
											iOuterTerminalIndex = pCentDedEkiTarget->addOuterTerminalEkimei(aOuterTerminal);
										}
									}

									//aCentDedRessyaTrackNewに作業を設定、
									//列車の終着駅を新しくし、RessyaTrackをsetします

									CentDedAfterOperation	aOperationNewOuter(
										CentDedAfterOperation::EAOperation::AOperation_Outer,
										iOuterTerminalIndex,
										pRessya->getCentDedEkiJikoku(ord).getHatsujikoku(true),
										aJikoku,
										strInOutLinkCode);

									pRessya->setSyuuchakuEki(ord);
									CentDedAfterOperationCont* pAfterOperationCont = pRessya->getCentDedEkiJikokuCont()
										->getMuPtr()->get(ord)->getCentDedAfterOperationCont();
									if (pRessya->getLastOperation().isLastOperation())
									{
										pAfterOperationCont->set(aOperationNewOuter, INT_MAX);
									}
									else
									{
										pAfterOperationCont->insert(aOperationNewOuter);
									};
								//}
								break;
							}
						}
					}
				}
			}

		}
	}
	/*	
	(1)　新しく生成される路線ファイルは、
	『現在編集している路線ファイル』から、
	指定された範囲以外の駅を削除したものになります。
	削除される駅を、基幹駅・起点駅とする、分岐駅設定・環状線設定は解除します
	*/
	{
		for (int idx = iEkiIndex; idx < iEkiIndex + iEkiCount; idx++)
		{
			CentDedEki* pCentDedEki = rosenNew.getCentDedEkiCont()->getMuPtr()->get(idx);
			if (pCentDedEki->getBrunchCoreEkiIndex() < iEkiIndex ||
				pCentDedEki->getBrunchCoreEkiIndex() >= iEkiIndex + iEkiCount)
			{
				pCentDedEki->setBrunchCoreEkiIndex(-1);
			}
			if (pCentDedEki->getLoopOriginEkiIndex() < iEkiIndex)
			{
				pCentDedEki->setLoopOriginEkiIndex(-1);
			}
		}
		//	『新しく生成される路線ファイル』の終点側の駅を削除
		rosenNew.getCentDedEkiCont()->erase( iEkiIndex + iEkiCount , INT_MAX ) ;
		//	『新しく生成される路線ファイル』の起点側の駅を削除
		rosenNew.getCentDedEkiCont()->erase( 0 , iEkiIndex ) ;
		//　『新しく生成される路線ファイル』の末尾の駅の、「次駅までの距離」を初期化します。
		CentDedEki* pCentDedEkiBottom = rosenNew.getCentDedEkiCont()->getMuPtr()->get(INT_MAX);
		pCentDedEkiBottom->setNextEkiDistance(0);
	}
	/*
	(2)　新しく生成される路線が運転区間に含まれない列車は、削除します。
	*/
	{
		Mu<CentDedDia*>* muCentDedDia = rosenNew.getCentDedDiaCont()->getMuPtr() ;

		for ( int idxDia = 0 ; idxDia < muCentDedDia->size() ; idxDia ++ )
		{
			CentDedDia* pCentDedDia = muCentDedDia->get( idxDia ) ;
			//pCentDedDia = 対象となるダイヤ

			//下り列車→上り列車
			for ( int idxRessyahoukou = (int)Ressyahoukou_Kudari ;
				idxRessyahoukou <= (int)Ressyahoukou_Nobori ;
				idxRessyahoukou ++ )
			{
				ERessyahoukou eRessyahoukou = (ERessyahoukou)idxRessyahoukou ;
				CentDedRessyaCont* pCentDedRessyaCont = pCentDedDia->getCentDedRessyaCont( eRessyahoukou ) ;

				for ( int idxRessya = 0 ; idxRessya < pCentDedRessyaCont->size() ; idxRessya ++ )
				{
					bool bErase = false ;
					CentDedRessya* pRessya = pCentDedRessyaCont->getMuPtr()->get( idxRessya ) ;

					//	列車が運行している区間が一つもない列車は、
					//	削除します。
					if ( !bErase )
					{

						//	列車が運行している区間の最初の駅Orderを
						//	検索します。
						int iEkiOrder = 0 ;
						for ( iEkiOrder = 0 ; 
							iEkiOrder < pRessya->getCentDedEkiJikokuCount() ;
							iEkiOrder ++ )
						{
							if ( pRessya->isRunBetweenNextEki( iEkiOrder ) )
							{
								break ;
							}
						}
						//iEkiOrder = 列車が運行している区間の最初の駅Order
						//	見つからなかった場合は、
						//	pRessya->getCentDedEkiJikokuCount() と等しくなります。
						if ( iEkiOrder == pRessya->getCentDedEkiJikokuCount() )
						{
							bErase = true ;	
						}
					}


					//	列車を削除
					if ( bErase )
					{
						pCentDedRessyaCont->erase( idxRessya ) ;
						idxRessya -- ;
					}
				}
			}

		}
	}


	return rosenNew ;
}

void CentDedRosen::adjustByEkijikokukeisiki( int iEkiIndex ) 
{
	//○全ダイヤのループ
	for ( int idxDia = 0 ; idxDia < m_CentDedDiaCont.size() ; idxDia ++ )
	{
		CentDedDia* pCentDedDia = m_CentDedDiaCont.getMuPtr()->get( idxDia ) ;
		pCentDedDia->adjustByEkijikokukeisiki(
			&m_CentDedEkiCont ,
			iEkiIndex ) ;
	}
}

void CentDedRosen::invert()
{
	//(0)　路線オブジェクトのコピーを作成
	CentDedRosen	aRosenBefore = *this ;


	//(1)　路線ファイルの駅の順序の並び順を逆にします。
	//	最初の状態の路線ファイルのコピーから、駅属性をコピーします。
	{
		for ( int idxEki = 0 ;idxEki < m_CentDedEkiCont.size() ; idxEki ++ )
		{
			CentDedEki	aEki = aRosenBefore.getCentDedEkiCont()->get( 
				m_CentDedEkiCont.size() - idxEki - 1 ) ;

			m_CentDedEkiCont.set( aEki , idxEki ) ;
		}
	}
	//(2)　駅のプロパティは、以下の変換を行います。
	//【補足】
	//	this の駅の属性を変更すると、含まれている列車の着時刻・発時刻は
	//	『始発駅・終着駅の駅時刻形式変更に伴う、着時刻・発時刻の修正』
	//	により、駅時刻が変更されます。
	//	aRosenBefore は、この変更を受ける前の駅時刻を保持します。
	{
		vector<int> iLoopOrigin(m_CentDedEkiCont.size(), -1);
		for ( int idxEki = 0 ; idxEki < m_CentDedEkiCont.size() ; idxEki ++ )  
		{
			CentDedEki*	pEki = m_CentDedEkiCont.getMuPtr()->get( idxEki ) ;

			//(2.1)駅名はそのまま

			//(2.2)駅時刻形式
			//	- 下り着時刻→上り着時刻
			//	- 上り着時刻→下り着時刻
			//	- 下り発着→上り発着 17.4.14 add_by_d_mania
			//	- 上り発着→下り発着 17.4.14 add_by_d_mania
			{
				CentDedEki::EEkijikokukeisiki eEkijikokukeisiki = pEki->getEkijikokukeisiki() ;
				if ( eEkijikokukeisiki == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku )
				{
					eEkijikokukeisiki = CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku ;
				}
				else if ( eEkijikokukeisiki == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku )
				{
					eEkijikokukeisiki = CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku ;
				}
				else if ( eEkijikokukeisiki == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku )
				{
					eEkijikokukeisiki = CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku ;
				}
				else if ( eEkijikokukeisiki == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriHatsuchaku )
				{
					eEkijikokukeisiki = CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariHatsuchaku ;
				}
				pEki->setEkijikokukeisiki( eEkijikokukeisiki ) ;
			}

			//(2.4)ダイヤグラム列車情報
			//	  下りの内容と上りの内容を入れ替えます。
			{
				CentDedEki::EDiagramRessyajouhouHyouji eRessyajouhouHyoujiKudari = pEki->getDiagramRessyajouhouHyoujiKudari() ;
				CentDedEki::EDiagramRessyajouhouHyouji eRessyajouhouHyoujiNobori = pEki->getDiagramRessyajouhouHyoujiNobori() ;
				pEki->setDiagramRessyajouhouHyoujiKudari( eRessyajouhouHyoujiNobori ) ;
				pEki->setDiagramRessyajouhouHyoujiNobori( eRessyajouhouHyoujiKudari ) ;
			}

			//(2.5)分岐駅・環状線設定
			//BrunchCoreIndexが0以上の場合、反転したIndexに変更します
			//LoopOriginIndexが0以上の場合、この駅は-1にし、起点駅だった駅から、この駅に対し環状線を設定します
			//この作業は他の駅の変更なので、安全に行うため
			//iLoopOrigin配列の、[新たな終点駅]番目に、[新たな起点駅]のIndexを入れておき、
			//一度全駅ループを終えてから、再度のループで設定します。
			{

				if (pEki->getBrunchCoreEkiIndex() >= 0)
				{
					pEki->setBrunchCoreEkiIndex(m_CentDedEkiCont.size() - pEki->getBrunchCoreEkiIndex() - 1);
				}
				if (pEki->getLoopOriginEkiIndex() >= 0)
				{
					//新たな終点駅のIndexは、以前の起点駅Indexの反転になります。
					//新たな起点駅のIndexは、探索中の駅Index(idxEki)がそのまま使えます。
					iLoopOrigin[m_CentDedEkiCont.size() - pEki->getLoopOriginEkiIndex() - 1]
						= idxEki;
					//探索中の駅のLoopOriginEkiIndexは、-1にセットしておきます
					pEki->setLoopOriginEkiIndex(-1);
				}
			}
			//(2.6)主本線設定
			//下りと上りの主本線を入れ替えます
			{
				int iDownMain = pEki->getDownMain();
				int iUpMain = pEki->getUpMain();
				pEki->setDownMain(iUpMain);
				pEki->setUpMain(iDownMain);
			}
			//(2.7)カスタム表示モード表示設定
			//下りと上りの表示有無を入れ替えます
			{
				bool bTempKudari = pEki->getJikokuhyouChakuJikokuDisplayKudari();
				bool bTempNobori = pEki->getJikokuhyouChakuJikokuDisplayNobori();
				pEki->setJikokuhyouChakuJikokuDisplayKudari(bTempNobori);
				pEki->setJikokuhyouChakuJikokuDisplayNobori(bTempKudari);
				bTempKudari = pEki->getJikokuhyouHatsuJikokuDisplayKudari();
				bTempNobori = pEki->getJikokuhyouHatsuJikokuDisplayNobori();
				pEki->setJikokuhyouHatsuJikokuDisplayKudari(bTempNobori);
				pEki->setJikokuhyouHatsuJikokuDisplayNobori(bTempKudari);
				bTempKudari = pEki->getJikokuhyouTrackDisplayKudari();
				bTempNobori = pEki->getJikokuhyouTrackDisplayNobori();
				pEki->setJikokuhyouTrackDisplayKudari(bTempNobori);
				pEki->setJikokuhyouTrackDisplayNobori(bTempKudari);

				int iTempKudari = pEki->getJikokuhyouRessyabangouDisplayKudari();
				int iTempNobori = pEki->getJikokuhyouRessyabangouDisplayNobori();
				pEki->setJikokuhyouRessyabangouDisplayKudari(iTempNobori);
				pEki->setJikokuhyouRessyabangouDisplayNobori(iTempKudari); 
				iTempKudari = pEki->getJikokuhyouOperationNumberDisplayKudari();
				iTempNobori = pEki->getJikokuhyouOperationNumberDisplayNobori();
				pEki->setJikokuhyouOperationNumberDisplayKudari(iTempNobori);
				pEki->setJikokuhyouOperationNumberDisplayNobori(iTempKudari);
				iTempKudari = pEki->getJikokuhyouOperationNumberDisplayRowsKudari();
				iTempNobori = pEki->getJikokuhyouOperationNumberDisplayRowsNobori();
				pEki->setJikokuhyouOperationNumberDisplayRowsKudari(iTempNobori);
				pEki->setJikokuhyouOperationNumberDisplayRowsNobori(iTempKudari);
				iTempKudari = pEki->getJikokuhyouRessyaSyubetsuDisplayKudari();
				iTempNobori = pEki->getJikokuhyouRessyaSyubetsuDisplayNobori();
				pEki->setJikokuhyouRessyaSyubetsuDisplayKudari(iTempNobori);
				pEki->setJikokuhyouRessyaSyubetsuDisplayNobori(iTempKudari);
				iTempKudari = pEki->getJikokuhyouRessyameiDisplayKudari();
				iTempNobori = pEki->getJikokuhyouRessyameiDisplayNobori();
				pEki->setJikokuhyouRessyameiDisplayKudari(iTempNobori);
				pEki->setJikokuhyouRessyameiDisplayNobori(iTempKudari);
				bTempKudari = pEki->getJikokuhyouOuterSihatsuDisplayKudari();
				bTempNobori = pEki->getJikokuhyouOuterSihatsuDisplayNobori();
				pEki->setJikokuhyouOuterSihatsuDisplayKudari(bTempNobori);
				pEki->setJikokuhyouOuterSihatsuDisplayNobori(bTempKudari);
				bTempKudari = pEki->getJikokuhyouOuterShuchakuDisplayKudari();
				bTempNobori = pEki->getJikokuhyouOuterShuchakuDisplayNobori();
				pEki->setJikokuhyouOuterShuchakuDisplayKudari(bTempNobori);
				pEki->setJikokuhyouOuterShuchakuDisplayNobori(bTempKudari);
			}
			//(2.8)
			//次の駅までの距離および個別背景色を、反転後基準で一つ先の駅からコピーします。
			//(例)A-B-Cを元の路線とすると、A-B間の距離はA駅、B-C間の距離はB駅が保持しており、
			//C駅における値は、特に意味のないものとなります。
			//反転後は、A-B間の距離はB駅、B-C間の距離はC駅が保持する必要があるため、
			//B駅の値をC駅に、A駅の値をB駅にコピーします。
			//A駅の値は、そのままでも問題ないですが、混乱防止のため0にします。
			if (idxEki == m_CentDedEkiCont.size() - 1)
			{
				pEki->setNextEkiDistance(0);
				pEki->setDiagramColorNextEki(0);
			}
			else
			{
				const CentDedEki*	pEkiNext = m_CentDedEkiCont.getMuPtr()->get(idxEki + 1);

				pEki->setNextEkiDistance(pEkiNext->getNextEkiDistance());
				pEki->setDiagramColorNextEki(pEkiNext->getDiagramColorNextEki());
			}
			//(2.9)番線の下り略称・上り略称の入れ替え
			{
				CentDedEkiTrack2Cont* pEkiTrack2Cont = pEki->getEkiTrack2Cont();
				for (int iEkiTrack2Index = 0; iEkiTrack2Index < pEkiTrack2Cont->size(); iEkiTrack2Index++)
				{
					//上り略称が空の場合は、入れ替えを行いません。
					CentDedEkiTrack2Cont* pEkiTrack2Cont = pEki->getEkiTrack2Cont();
					CentDedEkiTrack2* pEkiTrack2 = pEkiTrack2Cont->getMuPtr()->get(iEkiTrack2Index);
					if (!pEkiTrack2->getTrackNoboriRyakusyou().empty())
					{
						tstring strKudariRyakusyou = pEkiTrack2->getTrackRyakusyou();
						tstring strNoboriRyakusyou = pEkiTrack2->getTrackNoboriRyakusyou();

						pEkiTrack2->setTrackRyakusyou(strNoboriRyakusyou);
						pEkiTrack2->setTrackNoboriRyakusyou(strKudariRyakusyou);
					}
				}
			}
			//(2.10)前後作業表示数・増解結編成作業欄の入れ替え
			{
				int iOperationOrigin = pEki->getJikokuhyouOperationOrigin();
				int iOperationTerminal = pEki->getJikokuhyouOperationTerminal();
				pEki->setJikokuhyouOperationOrigin(iOperationTerminal);
				pEki->setJikokuhyouOperationTerminal(iOperationOrigin);
				bool bOperationOrigin = pEki->getJikokuhyouOperationOriginDownBeforeUpAfter();
				bool bOperationTerminal = pEki->getJikokuhyouOperationTerminalDownAfterUpBefore();
				pEki->setJikokuhyouOperationOriginDownBeforeUpAfter(bOperationTerminal);
				pEki->setJikokuhyouOperationTerminalDownAfterUpBefore(bOperationOrigin);
				bOperationOrigin = pEki->getJikokuhyouOperationOriginDownAfterUpBefore();
				bOperationTerminal = pEki->getJikokuhyouOperationTerminalDownBeforeUpAfter();
				pEki->setJikokuhyouOperationOriginDownAfterUpBefore(bOperationTerminal);
				pEki->setJikokuhyouOperationTerminalDownBeforeUpAfter(bOperationOrigin);
			}
			//(2.11)交差支障チェックルールの入れ替え
			{
				int iEkiCount = m_CentDedEkiCont.size() - 1;
				for (int iRuleIndex = 0; iRuleIndex < pEki->getCrossingCheckRuleSize(); iRuleIndex++)
				{
					CrossingCheckRule aCrossingCheckRule = pEki->getCrossingCheckRule(iRuleIndex);
					for (int i = 0; i < aCrossingCheckRule.BeforeFromTrackContentCont.size(); i++)
					{
						if (aCrossingCheckRule.BeforeFromTrackContentCont[i].eTrackType == ETrackType::TrackType_Origin)
						{
							aCrossingCheckRule.BeforeFromTrackContentCont[i].eTrackType = ETrackType::TrackType_Terminal;
							aCrossingCheckRule.BeforeFromTrackContentCont[i].iTrackIndex = iEkiCount - aCrossingCheckRule.BeforeFromTrackContentCont[i].iTrackIndex;
						}
						else if (aCrossingCheckRule.BeforeFromTrackContentCont[i].eTrackType == ETrackType::TrackType_Terminal)
						{
							aCrossingCheckRule.BeforeFromTrackContentCont[i].eTrackType = ETrackType::TrackType_Origin;
							aCrossingCheckRule.BeforeFromTrackContentCont[i].iTrackIndex = iEkiCount - aCrossingCheckRule.BeforeFromTrackContentCont[i].iTrackIndex;
						}
					}

					for (int i = 0; i < aCrossingCheckRule.BeforeToTrackContentCont.size(); i++)
					{
						if (aCrossingCheckRule.BeforeToTrackContentCont[i].eTrackType == ETrackType::TrackType_Origin)
						{
							aCrossingCheckRule.BeforeToTrackContentCont[i].eTrackType = ETrackType::TrackType_Terminal;
							aCrossingCheckRule.BeforeToTrackContentCont[i].iTrackIndex = iEkiCount - aCrossingCheckRule.BeforeToTrackContentCont[i].iTrackIndex;
						}
						else if (aCrossingCheckRule.BeforeToTrackContentCont[i].eTrackType == ETrackType::TrackType_Terminal)
						{
							aCrossingCheckRule.BeforeToTrackContentCont[i].eTrackType = ETrackType::TrackType_Origin;
							aCrossingCheckRule.BeforeToTrackContentCont[i].iTrackIndex = iEkiCount - aCrossingCheckRule.BeforeToTrackContentCont[i].iTrackIndex;
						}
					}

					for (int i = 0; i < aCrossingCheckRule.AfterFromTrackContentCont.size(); i++)
					{
						if (aCrossingCheckRule.AfterFromTrackContentCont[i].eTrackType == ETrackType::TrackType_Origin)
						{
							aCrossingCheckRule.AfterFromTrackContentCont[i].eTrackType = ETrackType::TrackType_Terminal;
							aCrossingCheckRule.AfterFromTrackContentCont[i].iTrackIndex = iEkiCount - aCrossingCheckRule.AfterFromTrackContentCont[i].iTrackIndex;
						}
						else if (aCrossingCheckRule.AfterFromTrackContentCont[i].eTrackType == ETrackType::TrackType_Terminal)
						{
							aCrossingCheckRule.AfterFromTrackContentCont[i].eTrackType = ETrackType::TrackType_Origin;
							aCrossingCheckRule.AfterFromTrackContentCont[i].iTrackIndex = iEkiCount - aCrossingCheckRule.AfterFromTrackContentCont[i].iTrackIndex;
						}
					}

					for (int i = 0; i < aCrossingCheckRule.AfterToTrackContentCont.size(); i++)
					{
						if (aCrossingCheckRule.AfterToTrackContentCont[i].eTrackType == ETrackType::TrackType_Origin)
						{
							aCrossingCheckRule.AfterToTrackContentCont[i].eTrackType = ETrackType::TrackType_Terminal;
							aCrossingCheckRule.AfterToTrackContentCont[i].iTrackIndex = iEkiCount - aCrossingCheckRule.AfterToTrackContentCont[i].iTrackIndex;
						}
						else if (aCrossingCheckRule.AfterToTrackContentCont[i].eTrackType == ETrackType::TrackType_Terminal)
						{
							aCrossingCheckRule.AfterToTrackContentCont[i].eTrackType = ETrackType::TrackType_Origin;
							aCrossingCheckRule.AfterToTrackContentCont[i].iTrackIndex = iEkiCount - aCrossingCheckRule.AfterToTrackContentCont[i].iTrackIndex;
						}
					}
					pEki->setCrossingCheckRule(aCrossingCheckRule, iRuleIndex);
				}
			}
		}
		for (int idxEki = 0; idxEki < m_CentDedEkiCont.size(); idxEki++)
		{
			if (iLoopOrigin[idxEki] >= 0)
			{
				CentDedEki*	pEki = m_CentDedEkiCont.getMuPtr()->get(idxEki);
				pEki->setLoopOriginEkiIndex(iLoopOrigin[idxEki]);
			}
		}
	}

	//(3)すべてのダイヤについて、下り列車と上り列車を入れ替えます。
	//	このとき、下り列車を一旦空にしたうえで、
	//	最初の状態(駅の順序の入れ替えを行う前に)の路線オブジェクトのコピーから
	//	列車を挿入します。上りも同様です。
	//【補足】
	//	this の駅の属性を変更すると、含まれている列車の着時刻・発時刻は
	//	『始発駅・終着駅の駅時刻形式変更に伴う、着時刻・発時刻の修正』
	//	により、駅時刻が変更されます。
	//	aRosenBefore は、この変更を受ける前の駅時刻を保持します。
	//	これをコピー元とすることにより、駅時刻の変更を避けることができます。
	{
		for ( int idxDia = 0 ; idxDia < m_CentDedDiaCont.size() ; idxDia ++ )
		{
			CentDedDia* pDia = m_CentDedDiaCont.getMuPtr()->get( idxDia ) ;

			//	下り・上りの列車コンテナにアダプタを付加
			CaMui<CentDedRessya>	aRessyaContKudariAdapter( pDia->getCentDedRessyaCont( Ressyahoukou_Kudari ) ) ;
			CaMui<CentDedRessya>	aRessyaContNoboriAdapter( pDia->getCentDedRessyaCont( Ressyahoukou_Nobori ) ) ;

			//	下り列車コンテナの内容を削除後、
			//	かつての上り列車のコピーを追加
			aRessyaContKudariAdapter.getAdaptee()->erase( 0 , INT_MAX ) ;
			aRessyaContKudariAdapter.insert( 
				aRosenBefore.getCentDedDiaCont()->getMuPtr()->get( idxDia )->getCentDedRessyaCont( Ressyahoukou_Nobori ) );

			//	上り列車コンテナの内容を削除後、
			//	かつての上り列車のコピーを追加
			aRessyaContNoboriAdapter.getAdaptee()->erase( 0 , INT_MAX ) ;
			aRessyaContNoboriAdapter.insert( 
				aRosenBefore.getCentDedDiaCont()->getMuPtr()->get( idxDia )->getCentDedRessyaCont( Ressyahoukou_Kudari ) );

		}
	}

	//下り・上りダイヤ別名を入れ替えます
	{
		setKudariDiaAlias(aRosenBefore.getNoboriDiaAlias());
		setNoboriDiaAlias(aRosenBefore.getKudariDiaAlias());
	}


}
int CentDedRosen::swapRessyasyubetsu( int iRessyasyubetsuIndexA ,
		int iRessyasyubetsuSizeA,
		int iRessyasyubetsuIndexB ) 
{
	int iRv = 0 ;
	// --------------------------------
	if ( iRv >= 0 ){
		if ( iRessyasyubetsuIndexA == INT_MAX )
		{
			iRessyasyubetsuIndexA = m_CentDedRessyasyubetsuCont.size() - 1 ;
			iRessyasyubetsuSizeA = 1;
		}
		if ( !( 0 <= iRessyasyubetsuIndexA && 
				iRessyasyubetsuIndexA < m_CentDedRessyasyubetsuCont.size() ) )
		{
			iRv = -1 ;	//	インデクスが不正

		}
		if (iRessyasyubetsuSizeA == INT_MAX)
		{
			iRessyasyubetsuSizeA = m_CentDedRessyasyubetsuCont.size() - iRessyasyubetsuIndexA;
		}
	}
	if ( iRv >= 0 ){
		if ( iRessyasyubetsuIndexB == INT_MAX )
		{
			iRessyasyubetsuIndexB = m_CentDedRessyasyubetsuCont.size() - 1 ;
		}
		if ( !( 0 <= iRessyasyubetsuIndexB && 
				iRessyasyubetsuIndexB < m_CentDedRessyasyubetsuCont.size() ) )
		{
			iRv = -1 ;	//	インデクスが不正

		}
	}
	if ( iRv >= 0 )
	{
		//二つの選択範囲が重複していないかを確かめます。
		if (iRessyasyubetsuIndexB >= iRessyasyubetsuIndexA &&
			iRessyasyubetsuIndexB < iRessyasyubetsuIndexA + iRessyasyubetsuSizeA)
		{
			iRv = -1;
		}
	}
	// --------------------------------
	//m_CentDedRessyasyubetsuCont の入れ替え
	if ( iRv >= 0 )
	{
		Mu<CentDedRessyasyubetsu*>*	pIfContGet = m_CentDedRessyasyubetsuCont.getMuPtr() ;
		if (iRessyasyubetsuIndexA < iRessyasyubetsuIndexB)
		{
			//前方にあるAを取得し、Tempに入れる。
			vector<CentDedRessyasyubetsu> aRessyasyubetsuTempA;
			for (int iOffset = 0; iOffset < iRessyasyubetsuSizeA; iOffset++)
			{
				aRessyasyubetsuTempA.emplace_back(*pIfContGet->get(iRessyasyubetsuIndexA + iOffset));
			}

			//後方にあるBをAの先頭位置に上書きする
			*pIfContGet->get(iRessyasyubetsuIndexA) =
				*pIfContGet->get(iRessyasyubetsuIndexB);

			//AとBの間にある要素を、移動したBの後方にシフトしていく
			int iShift = iRessyasyubetsuSizeA - 1;
			for (int idx = iRessyasyubetsuIndexA + iRessyasyubetsuSizeA; idx < iRessyasyubetsuIndexB && iShift != 0; idx++)
			{
				*pIfContGet->get(idx- iShift) =
					*pIfContGet->get(idx);
			}
			//TempのAをBを末尾に合わせて上書きする。
			for (int iOffset = 0; iOffset < iRessyasyubetsuSizeA; iOffset++)
			{
				*pIfContGet->get(iRessyasyubetsuIndexB - iRessyasyubetsuSizeA + 1 + iOffset) =
					aRessyasyubetsuTempA[iOffset];
			}
		}
		else
		{
			//後方にあるAを取得し、Tempに入れる。
			vector<CentDedRessyasyubetsu> aRessyasyubetsuTempA;
			for (int iOffset = 0; iOffset < iRessyasyubetsuSizeA; iOffset++)
			{
				aRessyasyubetsuTempA.emplace_back(*pIfContGet->get(iRessyasyubetsuIndexA + iOffset));
			}

			//前方にあるBをAの末尾位置に上書きする
			*pIfContGet->get(iRessyasyubetsuIndexA+ iRessyasyubetsuSizeA-1) =
				*pIfContGet->get(iRessyasyubetsuIndexB);

			//BとAの間にある要素を、移動したBの前方にシフトしていく
			int iShift = iRessyasyubetsuSizeA - 1;
			for (int idx = iRessyasyubetsuIndexA - 1; idx > iRessyasyubetsuIndexB && iShift != 0; idx--)
			{
				*pIfContGet->get(idx + iShift) =
					*pIfContGet->get(idx);
			}
			//TempのAをBスタートで上書きする。
			for (int iOffset = 0; iOffset < iRessyasyubetsuSizeA; iOffset++)
			{
				*pIfContGet->get(iRessyasyubetsuIndexB + iOffset) =
					aRessyasyubetsuTempA[iOffset];
			}
		}
		//ParentSyubetsuIndexの修正。
		//ParentSyubetsuIndexがiRessyasyubetsuIndexA～iRessyasyubetsuIndexA+iRessyasyubetsuSizeA-1なら、iParentSyubetsuShiftAをParentSyubetsuIndexに加算、
		//
		if (iRessyasyubetsuIndexA < iRessyasyubetsuIndexB)
		{
			int iParentSyubetsuShiftA = iRessyasyubetsuIndexB - iRessyasyubetsuSizeA + 1 - iRessyasyubetsuIndexA;
			int iParentSyubetsuShiftB = iRessyasyubetsuIndexA - iRessyasyubetsuIndexB;
			int iParentSyubetsuShiftC = 1 - iRessyasyubetsuSizeA;
			for (int idx = 0; idx < pIfContGet->size(); idx++)
			{
				CentDedRessyasyubetsu* pCentDedRessyasyubetsu = pIfContGet->get(idx);
				if (pCentDedRessyasyubetsu->getParentSyubetsuIndex() >= iRessyasyubetsuIndexA &&
					pCentDedRessyasyubetsu->getParentSyubetsuIndex() < iRessyasyubetsuIndexA + iRessyasyubetsuSizeA)
				{
					pCentDedRessyasyubetsu->setParentSyubetsuIndex(pCentDedRessyasyubetsu->getParentSyubetsuIndex() + iParentSyubetsuShiftA);
				}
				else if (pCentDedRessyasyubetsu->getParentSyubetsuIndex() == iRessyasyubetsuIndexB)
				{
					pCentDedRessyasyubetsu->setParentSyubetsuIndex(pCentDedRessyasyubetsu->getParentSyubetsuIndex() + iParentSyubetsuShiftB);
				}
				else if (pCentDedRessyasyubetsu->getParentSyubetsuIndex() >= iRessyasyubetsuIndexA + iRessyasyubetsuSizeA &&
					pCentDedRessyasyubetsu->getParentSyubetsuIndex() < iRessyasyubetsuIndexB)
				{
					pCentDedRessyasyubetsu->setParentSyubetsuIndex(pCentDedRessyasyubetsu->getParentSyubetsuIndex() + iParentSyubetsuShiftC);
				}
			}
		}
		else
		{
			int iParentSyubetsuShiftA = iRessyasyubetsuIndexB - iRessyasyubetsuIndexA ;
			int iParentSyubetsuShiftB = iRessyasyubetsuIndexA  + iRessyasyubetsuSizeA - 1 - iRessyasyubetsuIndexB;
			int iParentSyubetsuShiftC = iRessyasyubetsuSizeA - 1;
			for (int idx = 0; idx < pIfContGet->size(); idx++)
			{
				CentDedRessyasyubetsu* pCentDedRessyasyubetsu = pIfContGet->get(idx);
				if (pCentDedRessyasyubetsu->getParentSyubetsuIndex() >= iRessyasyubetsuIndexA &&
					pCentDedRessyasyubetsu->getParentSyubetsuIndex() < iRessyasyubetsuIndexA + iRessyasyubetsuSizeA)
				{
					pCentDedRessyasyubetsu->setParentSyubetsuIndex(pCentDedRessyasyubetsu->getParentSyubetsuIndex() + iParentSyubetsuShiftA);
				}
				else if (pCentDedRessyasyubetsu->getParentSyubetsuIndex() == iRessyasyubetsuIndexB)
				{
					pCentDedRessyasyubetsu->setParentSyubetsuIndex(pCentDedRessyasyubetsu->getParentSyubetsuIndex() + iParentSyubetsuShiftB);
				}
				else if (pCentDedRessyasyubetsu->getParentSyubetsuIndex() > iRessyasyubetsuIndexB &&
					pCentDedRessyasyubetsu->getParentSyubetsuIndex() < iRessyasyubetsuIndexA)
				{
					pCentDedRessyasyubetsu->setParentSyubetsuIndex(pCentDedRessyasyubetsu->getParentSyubetsuIndex() + iParentSyubetsuShiftC);
				}
			}
		}

		// --------------------------------
		//	列車の入れ替え
		// --------------------------------
		if (iRessyasyubetsuIndexA < iRessyasyubetsuIndexB)
		{
			int iParentSyubetsuShiftA = iRessyasyubetsuIndexB - iRessyasyubetsuSizeA + 1 - iRessyasyubetsuIndexA;
			int iParentSyubetsuShiftB = iRessyasyubetsuIndexA - iRessyasyubetsuIndexB;
			int iParentSyubetsuShiftC = 1 - iRessyasyubetsuSizeA;

			int iDiaIndex;
			for (iDiaIndex = 0; iDiaIndex < m_CentDedDiaCont.size(); iDiaIndex++) {
				CentDedDia* pCentDedDia = m_CentDedDiaCont.getMuPtr()->get(iDiaIndex);
				int iRessyahoukou = 0;
				for (iRessyahoukou = Ressyahoukou_Kudari;
					iRessyahoukou <= Ressyahoukou_Nobori;
					iRessyahoukou++)
				{
					ERessyahoukou	eRessyahoukou = (ERessyahoukou)iRessyahoukou;

					CentDedRessyaCont* pCentDedRessyaCont = pCentDedDia->getCentDedRessyaCont(eRessyahoukou);
					Mu< CentDedRessya* >* pCentDedRessyaContGet = pCentDedRessyaCont->getMuPtr();

					int iRessyaCount = pCentDedRessyaContGet->size();

					int iRessyaIndex;

					for (iRessyaIndex = 0;
						iRessyaIndex < iRessyaCount;
						iRessyaIndex++) 
					{
						CentDedRessya* pCentDedRessya = pCentDedRessyaContGet->get(iRessyaIndex);
						int iRessyasyubetsuIndexCurr = pCentDedRessya->getRessyasyubetsuIndex();

						if (iRessyasyubetsuIndexCurr >= iRessyasyubetsuIndexA &&
							iRessyasyubetsuIndexCurr < iRessyasyubetsuIndexA + iRessyasyubetsuSizeA)
						{

							iRessyasyubetsuIndexCurr += iParentSyubetsuShiftA;
						}
						else if (iRessyasyubetsuIndexCurr == iRessyasyubetsuIndexB)
						{
							iRessyasyubetsuIndexCurr += iParentSyubetsuShiftB;
						}
						else if (iRessyasyubetsuIndexCurr >= iRessyasyubetsuIndexA + iRessyasyubetsuSizeA &&
							iRessyasyubetsuIndexCurr < iRessyasyubetsuIndexB)
						{
							iRessyasyubetsuIndexCurr += iParentSyubetsuShiftC;
						}

						pCentDedRessya->setRessyasyubetsuIndex(iRessyasyubetsuIndexCurr);
					}
				}
			}
		}
		else
		{
			int iParentSyubetsuShiftA = iRessyasyubetsuIndexB - iRessyasyubetsuIndexA;
			int iParentSyubetsuShiftB = iRessyasyubetsuIndexA + iRessyasyubetsuSizeA - 1 - iRessyasyubetsuIndexB;
			int iParentSyubetsuShiftC = iRessyasyubetsuSizeA - 1;

			int iDiaIndex;
			for (iDiaIndex = 0; iDiaIndex < m_CentDedDiaCont.size(); iDiaIndex++) {
				CentDedDia* pCentDedDia = m_CentDedDiaCont.getMuPtr()->get(iDiaIndex);
				int iRessyahoukou = 0;
				for (iRessyahoukou = Ressyahoukou_Kudari;
					iRessyahoukou <= Ressyahoukou_Nobori;
					iRessyahoukou++)
				{
					ERessyahoukou	eRessyahoukou = (ERessyahoukou)iRessyahoukou;

					CentDedRessyaCont* pCentDedRessyaCont = pCentDedDia->getCentDedRessyaCont(eRessyahoukou);
					Mu< CentDedRessya* >* pCentDedRessyaContGet = pCentDedRessyaCont->getMuPtr();

					int iRessyaCount = pCentDedRessyaContGet->size();

					int iRessyaIndex;

					for (iRessyaIndex = 0;
						iRessyaIndex < iRessyaCount;
						iRessyaIndex++)
					{
						CentDedRessya* pCentDedRessya = pCentDedRessyaContGet->get(iRessyaIndex);
						int iRessyasyubetsuIndexCurr = pCentDedRessya->getRessyasyubetsuIndex();

						if (iRessyasyubetsuIndexCurr >= iRessyasyubetsuIndexA &&
							iRessyasyubetsuIndexCurr < iRessyasyubetsuIndexA + iRessyasyubetsuSizeA)
						{
							iRessyasyubetsuIndexCurr += iParentSyubetsuShiftA;
						}
						else if (iRessyasyubetsuIndexCurr == iRessyasyubetsuIndexB)
						{
							iRessyasyubetsuIndexCurr += iParentSyubetsuShiftB;
						}
						else if (iRessyasyubetsuIndexCurr > iRessyasyubetsuIndexB &&
							iRessyasyubetsuIndexCurr < iRessyasyubetsuIndexA)
						{
							iRessyasyubetsuIndexCurr += iParentSyubetsuShiftC;
						}

						pCentDedRessya->setRessyasyubetsuIndex(iRessyasyubetsuIndexCurr);
					}
				}
			}
		}
	}

	return ( iRv ) ;
}


void CentDedRosen::adjustOperation()
{
	//○全ダイヤのループ
	for (int idxDia = 0; idxDia < m_CentDedDiaCont.size(); idxDia++)
	{
		CentDedDia* pCentDedDia = m_CentDedDiaCont.getMuPtr()->get(idxDia);
		pCentDedDia->adjustOperation(
			&m_CentDedEkiCont);
	}
}

void CentDedRosen::clear()
{
	m_strName.erase() ;
	m_jikokuKitenJikoku.setTime( 0 , 0 , 0 ) ;
	m_strComment.erase() ;
	m_strKudariDiaAlias.erase();
	m_strNoboriDiaAlias.erase();
	m_bOperationNumberReverse = false;
	m_bOperationCrossKitenJikoku = true;
	m_iKijunDiaIndex = 0;
	m_bDisableHiddenSyubetsu = false;

	m_CentDedDiaCont.erase( 0 , INT_MAX ) ;
	m_CentDedRessyasyubetsuCont.erase( 1 , INT_MAX ) ;
	m_CentDedEkiCont.erase( 0 , INT_MAX ) ;

	// --------------------------------
	{
		//	『列車種別』は、少なくとも一つは存在しなくてはなりません。
		m_CentDedRessyasyubetsuCont.set( 
			CentDedRessyasyubetsu( nameRessyasyubetsuDefault , _T("")  ) , 0 ) ;
	}
};


	// ********************************
	//@name CentDedRosen-子オブジェクトの増減の通知
	// ********************************

void CentDedRosen::onEkiInsert( int iEkiIndex ,const vector<int>& iMainTrack)
{
	m_CentDedDiaCont.onEkiInsert( iEkiIndex , iMainTrack) ;
	m_CentDedEkiCont.onEkiInsert(iEkiIndex);
}
void CentDedRosen::onEkiErase( int iEkiIndex  )
{
	m_CentDedDiaCont.onEkiErase( iEkiIndex ) ;
	m_CentDedEkiCont.onEkiErase(iEkiIndex);
}

void CentDedRosen::onRessyasyubetsuInsert( int iRessyasyubetsuIndex )
{
	m_CentDedDiaCont.onRessyasyubetsuInsert( iRessyasyubetsuIndex ) ;
}

void CentDedRosen::onRessyasyubetsuErase( int iRessyasyubetsuIndex )
{
	m_CentDedDiaCont.onRessyasyubetsuErase( iRessyasyubetsuIndex ) ;
}

void CentDedRosen::adjustBrunchLoopByBrunchEdit(
	int iEkiIndex, int iBrunchCoreEkiIndex)
{
	//番線情報の統一
	deque<int> iEkiIndexBrunchOriginSide;
	deque<int> iEkiIndexLoop;
	deque<int> iEkiIndexBrunchTerminalSide;
	vector<int> iOuterTerminalEkimeiMap;

	bool bOriginSide = m_CentDedEkiCont.adjustBrunchLoopByBrunchEdit(
		iEkiIndex, iBrunchCoreEkiIndex,
		iEkiIndexBrunchOriginSide, iEkiIndexLoop, iEkiIndexBrunchTerminalSide,
		iOuterTerminalEkimeiMap);

	//列車側の調整
	m_CentDedDiaCont.adjustBrunchLoopByBrunchEdit(
		iEkiIndex, bOriginSide,iEkiIndexBrunchOriginSide,
		iEkiIndexLoop, iEkiIndexBrunchTerminalSide,
		iOuterTerminalEkimeiMap);
}

void CentDedRosen::adjustBrunchLoopByLoopEdit(
	int iEkiIndex, int iLoopOriginEkiIndex)
{
	//番線情報の統一
	deque<int> iEkiIndexBrunchOriginSide;
	deque<int> iEkiIndexLoop;
	deque<int> iEkiIndexBrunchTerminalSide;;
	vector<int> iOuterTerminalEkimeiMap;

	int iPosition = m_CentDedEkiCont.adjustBrunchLoopByLoopEdit(
		iEkiIndex, iLoopOriginEkiIndex,
		iEkiIndexBrunchOriginSide, iEkiIndexLoop, iEkiIndexBrunchTerminalSide,
		iOuterTerminalEkimeiMap);

	//列車側の調整
	m_CentDedDiaCont.adjustBrunchLoopByLoopEdit(
		iEkiIndex, iPosition, iEkiIndexBrunchOriginSide,
		iEkiIndexLoop, iEkiIndexBrunchTerminalSide,
		iOuterTerminalEkimeiMap);
}

void CentDedRosen::OperationConnect(int iDiaIndex)
{
	if (getEnableOperation()>0)
	{
		CDedOperationConnecter aCDedOperationConnecter(
			this,
			getCentDedDiaCont()->getMuPtr()->get(iDiaIndex));
		getCentDedDiaCont()->getMuPtr()->get(iDiaIndex)->setWaitOperationUpdate(false);
	}
	else
	{
		vector<bool> contHidden;
		if (m_bDisableHiddenSyubetsu)
		{
			contHidden.assign(getCentDedRessyasyubetsuCont()->size(), false);
		}
		else
		{
			CentDedRessyasyubetsuCont* pCentDedRessyasyubetsuCont = this->getCentDedRessyasyubetsuCont();
			for (int iRessyaSyubetsuIndex = 0; iRessyaSyubetsuIndex < pCentDedRessyasyubetsuCont->size(); iRessyaSyubetsuIndex++)
			{
				contHidden.push_back(pCentDedRessyasyubetsuCont->get(iRessyaSyubetsuIndex).getHidden());
			}
		}

		getCentDedDiaCont()->getMuPtr()->get(iDiaIndex)
			->omitInvalidRessyaFromCustomizeRessyaIndex(contHidden);

		getCentDedDiaCont()->getMuPtr()->get(iDiaIndex)->copyCustomizeRessyaIndexByPatternDiagramPreview();
	}
}

void CentDedRosen::StandardRessyaTrackIndexSearch(
	const int iRessyasyubetsuIndex,
	const ERessyahoukou eRessyahoukou,
	const int iEkiOrder, 
	int iRessyaTrackIndex[])const
{
	//Ver2.0 列車側の主本線設定撤廃に伴い、最初に駅から主本線を取得するように変更
	const CentDedEki aEki = getCentDedEkiCont()->get(getCentDedEkiCont()
		->EkiIndexOfEkiOrder(eRessyahoukou, iEkiOrder));
	iRessyaTrackIndex[0] = aEki.getMainTrack(eRessyahoukou);
	iRessyaTrackIndex[1] = aEki.getMainTrack(eRessyahoukou);
	//Ver2.06.07 基準運転時分ダイヤ変更機能追加
	if (m_iKijunDiaIndex < 0)
	{
		return;
	}

	const CentDedRessyaCont* pKijunCentDedRessyaCont =
		getCentDedDiaCont()->getMuPtr()->get(m_iKijunDiaIndex)
		->getCentDedRessyaCont(eRessyahoukou);

	bool bFoundTeisya = false;
	bool bFoundTsuuka = false;

	//対象列車と同じ種別を基準側で探索
	for (int iKijunRessyaIndex = 0;
		iKijunRessyaIndex < pKijunCentDedRessyaCont->size() && (!bFoundTeisya || !bFoundTsuuka);
		iKijunRessyaIndex++)
	{
		//対象列車と同じ種別かどうか確認
		if (pKijunCentDedRessyaCont->getMuPtr()->get(iKijunRessyaIndex)->getRessyasyubetsuIndex() != iRessyasyubetsuIndex)
		{
			continue; //次列車に移行
		}
		//同じ種別
		//基準側列車コンテナ取得
		const CentDedRessya* pCentDedRessyaStandard = pKijunCentDedRessyaCont->getMuPtr()->get(iKijunRessyaIndex);
		
		const CentDedEkiJikoku aCentDedEkiJikoku = pCentDedRessyaStandard->getCentDedEkiJikoku(iEkiOrder);
		if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya && !bFoundTeisya)
		{
			iRessyaTrackIndex[0] = pCentDedRessyaStandard->getCentDedEkiJikoku(iEkiOrder).getRessyaTrackIndex();
			bFoundTeisya = true;
		}
		else if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka && !bFoundTsuuka)
		{
			iRessyaTrackIndex[1] = pCentDedRessyaStandard->getCentDedEkiJikoku(iEkiOrder).getRessyaTrackIndex();
			bFoundTsuuka = true;
		}
	}
}

void CentDedRosen::StandardShuntTrackIndexSearch(
	const int iRessyasyubetsuIndex,
	const ERessyahoukou eRessyahoukou,
	const int iChakuEkiOrder,
	const int iHatsuEkiOrder,
	int iShuntTrackIndex[])const
{
	iShuntTrackIndex[0] = 0;
	iShuntTrackIndex[1] = 0;
	//Ver2.06.07 基準運転時分ダイヤ変更機能追加
	if (m_iKijunDiaIndex < 0)
	{
		return;
	}

	const CentDedRessyaCont* pKijunCentDedRessyaCont =
		getCentDedDiaCont()->getMuPtr()->get(m_iKijunDiaIndex)
		->getCentDedRessyaCont(eRessyahoukou);

	bool bFoundBefore = false;
	bool bFoundAfter = false;

	//対象列車と同じ種別を基準側で探索
	for (int iKijunRessyaIndex = 0;
		iKijunRessyaIndex < pKijunCentDedRessyaCont->size() && (!bFoundBefore || !bFoundAfter);
		iKijunRessyaIndex++)
	{
		//対象列車と同じ種別かどうか確認
		if (pKijunCentDedRessyaCont->getMuPtr()->get(iKijunRessyaIndex)->getRessyasyubetsuIndex() != iRessyasyubetsuIndex)
		{
			continue; //次列車に移行
		}
		//同じ種別
		//基準側列車コンテナ取得
		const CentDedRessya* pCentDedRessyaStandard = pKijunCentDedRessyaCont->getMuPtr()->get(iKijunRessyaIndex);

		/**
			前作業をiChakuEkiOrderから取得するのは、iHatsuEkiOrderが-1のとき、有効終着駅とiChakuEkiOrderが一致する場合、
				iChakuEkiOrder、iHatsuEkiOrderがともに-1以外の場合
			前作業をiHatsuEkiOrderから取得するのは、iChakuEkiOrderが-1のとき、有効始発駅とiHatsuEkiOrderが一致する場合
		*/
		if (!bFoundBefore)
		{
			if (iChakuEkiOrder != -1 && 
				(iHatsuEkiOrder != -1 || (iHatsuEkiOrder == -1 && iChakuEkiOrder == pCentDedRessyaStandard->getValidSyuuchakuEki())))
			{
				const CentDedEkiJikoku aCentDedEkiJikoku = pCentDedRessyaStandard->getCentDedEkiJikoku(iChakuEkiOrder);
				const CentDedBeforeOperationCont* pBeforeOperationCont = aCentDedEkiJikoku.getCentDedBeforeOperationCont();
				for (int idx = pBeforeOperationCont->size() - 1; idx >= 0 && !bFoundBefore; idx--)
				{
					const CentDedBeforeOperation aBeforeOperation = pBeforeOperationCont->get(idx);
					if (aBeforeOperation.getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
					{
						iShuntTrackIndex[0] = aBeforeOperation.getShuntTrackIndex();
						bFoundBefore = true;
					}
				}
			}

			if (iChakuEkiOrder == -1 && iHatsuEkiOrder != -1 && iHatsuEkiOrder == pCentDedRessyaStandard->getValidSihatsuEki())
			{
				const CentDedEkiJikoku aCentDedEkiJikoku = pCentDedRessyaStandard->getCentDedEkiJikoku(iHatsuEkiOrder);
				const CentDedBeforeOperationCont* pBeforeOperationCont = aCentDedEkiJikoku.getCentDedBeforeOperationCont();
				for (int idx = pBeforeOperationCont->size() - 1; idx >= 0 && !bFoundBefore; idx--)
				{
					const CentDedBeforeOperation aBeforeOperation = pBeforeOperationCont->get(idx);
					if (aBeforeOperation.getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
					{
						iShuntTrackIndex[0] = aBeforeOperation.getShuntTrackIndex();
						bFoundBefore = true;
					}
				}
			}
		}
		/**
			後作業をiHatsuEkiOrderから取得するのは、iChakuEkiOrderが-1のとき、有効始発駅とiHatsuEkiOrderが一致する場合、
				iChakuEkiOrder、iHatsuEkiOrderがともに-1以外の場合
			後作業をiHatsuEkiOrderから取得するのは、iHatsuEkiOrderが-1のとき、有効終着駅とiChakuEkiOrderが一致する場合
		*/
		if (!bFoundAfter)
		{
			if (iHatsuEkiOrder != -1 &&
				(iChakuEkiOrder != -1 || (iChakuEkiOrder == -1 && iHatsuEkiOrder == pCentDedRessyaStandard->getValidSihatsuEki())))
			{
				const CentDedEkiJikoku aCentDedEkiJikoku = pCentDedRessyaStandard->getCentDedEkiJikoku(iHatsuEkiOrder);
				const CentDedAfterOperationCont* pAfterOperationCont = aCentDedEkiJikoku.getCentDedAfterOperationCont();
				for (int idx = 0; idx < pAfterOperationCont->size() && !bFoundAfter; idx++)
				{
					const CentDedAfterOperation aAfterOperation = pAfterOperationCont->get(idx);
					if (aAfterOperation.getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
					{
						iShuntTrackIndex[1] = aAfterOperation.getShuntTrackIndex();
						bFoundAfter = true;
					}
				}
			}

			if (iHatsuEkiOrder == -1 && iChakuEkiOrder != -1 && iChakuEkiOrder == pCentDedRessyaStandard->getValidSyuuchakuEki())
			{
				const CentDedEkiJikoku aCentDedEkiJikoku = pCentDedRessyaStandard->getCentDedEkiJikoku(iChakuEkiOrder);
				const CentDedAfterOperationCont* pAfterOperationCont = aCentDedEkiJikoku.getCentDedAfterOperationCont();
				for (int idx = 0; idx < pAfterOperationCont->size() && !bFoundAfter; idx++)
				{
					const CentDedAfterOperation aAfterOperation = pAfterOperationCont->get(idx);
					if (aAfterOperation.getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
					{
						iShuntTrackIndex[1] = aAfterOperation.getShuntTrackIndex();
						bFoundAfter = true;
					}
				}
			}
		}
	}
}

void CentDedRosen::StandardOuterTerminalJikanSearch(
	const int iRessyasyubetsuIndex,
	const ERessyahoukou eRessyahoukou,
	const int iChakuEkiOrder,
	const int iHatsuEkiOrder,
	vector<vector<int>>& iOuterTerminalJikan)const
{
	if (iChakuEkiOrder != -1 && iHatsuEkiOrder != -1)
	{
		if (!getCentDedEkiCont()->isSameBrunchLoopGroup(iChakuEkiOrder, iHatsuEkiOrder, eRessyahoukou))
		{
			return;
		}
	}
	vector<bool> bFound;
	if (iChakuEkiOrder != -1)
	{
		int iCount = getCentDedEkiCont()->get(getCentDedEkiCont()
			->EkiIndexOfEkiOrder(eRessyahoukou, iChakuEkiOrder)).getOuterTerminalEkimeiCount();
		iOuterTerminalJikan.assign(iCount, { 0,0 });
		bFound.assign(iCount, false);
	}
	else if (iHatsuEkiOrder != -1)
	{
		int iCount = getCentDedEkiCont()->get(getCentDedEkiCont()
			->EkiIndexOfEkiOrder(eRessyahoukou, iHatsuEkiOrder)).getOuterTerminalEkimeiCount();
		iOuterTerminalJikan.assign(iCount, { 0,0 });
		bFound.assign(iCount, false);
	}
	else
	{
		return;
	}

	//Ver2.06.07 基準運転時分ダイヤ変更機能追加
	if (m_iKijunDiaIndex < 0)
	{
		return;
	}

	const CentDedRessyaCont* pKijunCentDedRessyaCont =
		getCentDedDiaCont()->getMuPtr()->get(m_iKijunDiaIndex)
		->getCentDedRessyaCont(eRessyahoukou);

	//対象列車と同じ種別を基準側で探索
	for (int iKijunRessyaIndex = 0;
		iKijunRessyaIndex < pKijunCentDedRessyaCont->size();
		iKijunRessyaIndex++)
	{
		//対象列車と同じ種別かどうか確認
		if (pKijunCentDedRessyaCont->getMuPtr()->get(iKijunRessyaIndex)->getRessyasyubetsuIndex() != iRessyasyubetsuIndex)
		{
			continue; //次列車に移行
		}
		//同じ種別
		//基準側列車コンテナ取得
		const CentDedRessya* pCentDedRessyaStandard = pKijunCentDedRessyaCont->getMuPtr()->get(iKijunRessyaIndex);

		if (iHatsuEkiOrder != -1 &&
			iHatsuEkiOrder == pCentDedRessyaStandard->getValidSihatsuEki())
		{
			const CentDedBeforeOperation aBeforeOperation = pCentDedRessyaStandard->getFirstOperation();
			if (aBeforeOperation.getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer &&
				!aBeforeOperation.getChakuJikoku().isNull())
			{
				CdDedJikoku aHatsujikoku = pCentDedRessyaStandard->getCentDedEkiJikoku(pCentDedRessyaStandard->getValidSihatsuEki()).getHatsujikoku();
				iOuterTerminalJikan[aBeforeOperation.getOuterShihatsuekiIndex()][0] =
					aHatsujikoku.subJikoku(aBeforeOperation.getOuterShihatsuJikoku());
				iOuterTerminalJikan[aBeforeOperation.getOuterShihatsuekiIndex()][1] =
					aHatsujikoku.subJikoku(aBeforeOperation.getChakuJikoku());
				bFound[aBeforeOperation.getOuterShihatsuekiIndex()] = true;
			}
		}

		if (iChakuEkiOrder != -1 &&
			iChakuEkiOrder == pCentDedRessyaStandard->getValidSyuuchakuEki())
		{
			const CentDedAfterOperation aAfterOperation = pCentDedRessyaStandard->getLastOperation();
			if (aAfterOperation.getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer &&
				!aAfterOperation.getHatsuJikoku().isNull())
			{
				CdDedJikoku aChakujikoku = pCentDedRessyaStandard->getCentDedEkiJikoku(pCentDedRessyaStandard->getValidSyuuchakuEki()).getChakujikoku();
				iOuterTerminalJikan[aAfterOperation.getOuterShuchakuekiIndex()][0] =
					aAfterOperation.getOuterShuchakuJikoku().subJikoku(aChakujikoku);
				iOuterTerminalJikan[aAfterOperation.getOuterShuchakuekiIndex()][1] =
					aAfterOperation.getHatsuJikoku().subJikoku(aChakujikoku);
				bFound[aAfterOperation.getOuterShuchakuekiIndex()] = true;
			}
		}

		bool bAllFound = true;
		for (int idxb = 0; idxb < (int)bFound.size() && bAllFound; idxb++)
		{
			if (!bFound[idxb])
			{
				bAllFound = false;
			}
		}
		if (bAllFound)
		{
			return;
		}
	}
}

void CentDedRosen::adjustBrunchLoopEkiTrack2OuterTerminal(
	const int iEkiIndex, 
	const deque<int>& iEkiIndexBrunchLoopOld,
	const vector<int>& iEkiTrack2Map,
	const vector<int>& iOuterTerminalEkimeiMap)
{
	/**
		iEkiIndexBrunchLoopNew(iEkiIndexと同一扱い駅群)を求めます。
		次に、iEkiIndexBrunchLoopOld(駅編集が行われる前の、iEkiIndexと同一扱い駅群)と共通するものを、
		iEkiIndexBrunchLoopに収めます。
	*/
	deque<int> iEkiIndexBrunchLoopNew;
	deque<int> iEkiIndexBrunchLoop;
	int iSize = m_CentDedEkiCont.getEkiIndexBrunchLoop(
		iEkiIndex,
		iEkiIndexBrunchLoopNew);
	for (int idxo = 0; idxo < (int)iEkiIndexBrunchLoopOld.size(); idxo++)
	{
		for (int idxn = 0; idxn < iSize; idxn++)
		{
			if (iEkiIndexBrunchLoopOld[idxo] == iEkiIndexBrunchLoopNew[idxn])
			{
				iEkiIndexBrunchLoop.push_back(iEkiIndexBrunchLoopOld[idxo]);
				break;
			}
		}
	}
	//iEkiIndexBrunchLoopには自身のIndex及び、駅編集前後いずれでも分岐・環状線設定が繋がっている駅のIndex
	if ((int)iEkiIndexBrunchLoop.size() > 1)
	{
		/**
			駅番線側の編集を行います。
			iEkiIndexで行われた編集(駅番線の変更・主本線の変更・路線外発着駅の変更)を
			iEkiIndexBrunchLoopに収められている、同一駅扱いの駅群に適用します。
			この作業は、iEkiIndexBrunchLoopのサイズが2以上
			(iEkiIndex以外の駅が含まれている)場合のみ実行します。
			Ver2.06.18 iEkiTrack2Mapを引数に追加(DiagramTrackOmitの修正のため)
		*/
		m_CentDedEkiCont.adjustBrunchLoopEkiTrack2OuterTerminal(
			iEkiIndex,
			iEkiIndexBrunchLoop,
			iEkiTrack2Map);

	}

	if ((int)iEkiIndexBrunchLoop.size() > 0)
	{
		m_CentDedEkiCont.adjustBrunchLoopCrossingCheckRule(
			iEkiIndex,
			iEkiIndexBrunchLoop,
			iEkiTrack2Map,
			iOuterTerminalEkimeiMap);
	}
	if ((int)iEkiIndexBrunchLoop.size() > 0)
	{
		//iEkiTrack2Mapの中を確認、各要素内の値がそのidxと異なるものが一つでもある場合(除く-1=削除)は、
		//m_CentDedDiaCont.adjustBrunchLoopEkiTrack2を行う。
		bool bDoAdjust = false;
		for (int idx = 0; idx < (int)iEkiTrack2Map.size(); idx++)
		{
			if (iEkiTrack2Map[idx] != idx &&
				iEkiTrack2Map[idx] != -1)
			{
				bDoAdjust = true;
				break;
			}
		}
		if (bDoAdjust)
		{
			m_CentDedDiaCont.adjustBrunchLoopEkiTrack2(
				iEkiIndexBrunchLoop,
				iEkiTrack2Map);
		}
		//続いてiOuterTerminalEkimeiMapを確認、同様に各要素内の値がそのidxと異なるものが一つでもある場合(除く-1=削除)は、
		//m_CentDedDiaCont.adjustBrunchLoopOuterEkimeiを行う。
		bDoAdjust = false;
		for (int idx = 0; idx < (int)iOuterTerminalEkimeiMap.size(); idx++)
		{
			if (iOuterTerminalEkimeiMap[idx] != idx &&
				iOuterTerminalEkimeiMap[idx] != -1)
			{
				bDoAdjust = true;
				break;
			}
		}
		if (bDoAdjust)
		{
			m_CentDedDiaCont.adjustBrunchLoopOuterTerminal(
				iEkiIndexBrunchLoop,
				iOuterTerminalEkimeiMap);
		}
	}
}

void CentDedRosen::mergeOuterTerminal()
{
	vector<bool> bChecked;
	bChecked.resize(m_CentDedEkiCont.size(), false);
	for (int idxEki = 0; idxEki < m_CentDedEkiCont.size(); idxEki++)
	{
		if (bChecked[idxEki])
		{
			continue;
		}
		deque<int> iEkiIndexBrunchOriginSide;
		deque<int> iEkiIndexLoop;
		deque<int> iEkiIndexBrunchTerminalSide;
		int iPosition = m_CentDedEkiCont.getEkiIndexBrunchLoop(
			idxEki,
			iEkiIndexBrunchOriginSide,
			iEkiIndexLoop,
			iEkiIndexBrunchTerminalSide);
		if (iPosition == -1)
		{
			bChecked[idxEki] = true;
		}
		else
		{
			vector<vector<int>> iOuterTerminalMapCont;
			iOuterTerminalMapCont.resize(m_CentDedEkiCont.size());
			/**
				iPosition=0の駅を軸として、路線外発着駅名をまとめていく。
				(1)loop->origin->terminalの順に、軸駅と比較していく、
					まず、比較対象駅番目のiOuterTerminalMapContを初期化、
					比較して軸駅にないものがあったら軸駅に追加していく。
				(2)軸駅以外に路線外発着駅名をコピー
				(3)iOuterTerminalMapContをもとに作業の修正を行う
			*/
			m_CentDedEkiCont.mergeOuterTerminal(
				iEkiIndexBrunchOriginSide, iEkiIndexLoop, iEkiIndexBrunchTerminalSide,
				iOuterTerminalMapCont);

			m_CentDedDiaCont.mergeOuterTerminal(
				iEkiIndexBrunchOriginSide, iEkiIndexLoop, iEkiIndexBrunchTerminalSide,
				iOuterTerminalMapCont);

		}
	}
}

} //namespace entDed
