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
//	entDed¥CRessyaContUnifier.cpp
// $Id: CRessyaContUnifier.cpp 378 2016-11-16 21:10:54Z okm $
// ****************************************************************
*/
/** @file */
#include "stdafx.h"
#include <vector>
#include "CRessyaContUnifier.h"
#include "str¥tstring.h"
#include "CentDedAfterOperation.h"
#include "CentDedBeforeOperation.h"

namespace entDed{
	//using std::string ;

// ****************************************************************
//	CRessyaContUnifier
// ****************************************************************
	// ********************************
	//@name CRessyaContUnifier-static 操作
	// ********************************
void CRessyaContUnifier::unify( 
		Mui<CentDedRessya>* pMuiRessya ,
		int iRessyaIndex ,
		int iRessyaIndex2 ) 
{
	CentDedRessya	aRessya = pMuiRessya->get( iRessyaIndex ) ;
	CentDedRessya	aRessya2 = pMuiRessya->get( iRessyaIndex2 ) ;
	// ================================	
	//	駅時刻を結合
	// ================================	
	int iValidSihatsuEkiOrder1 = aRessya.getValidSihatsuEki();
	int iValidSyuuchakuEkiOrder1 = aRessya.getValidSyuuchakuEki();
	int iValidSihatsuEkiOrder2 = aRessya2.getValidSihatsuEki();
	int iValidSyuuchakuEkiOrder2 = aRessya2.getValidSyuuchakuEki();
	for ( int iEkiOrder = iValidSihatsuEkiOrder2; iEkiOrder <= iValidSyuuchakuEkiOrder2; iEkiOrder ++ )
	{
		CentDedEkiJikoku	aJikoku = aRessya.getCentDedEkiJikoku( iEkiOrder ) ;
		CentDedEkiJikoku	aJikoku2 = aRessya2.getCentDedEkiJikoku( iEkiOrder ) ;

		//	iRessyaIndex2 が停車・通過なら、駅扱はコピーします。
		//	駅時刻は、NULL以外の場合はコピーします。
		//　番線もコピーします
		if ( aJikoku2.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya ||
			aJikoku2.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka )
		{
			aJikoku.setEkiatsukai( aJikoku2.getEkiatsukai() ) ;
			if ( !aJikoku2.getChakujikoku().isNull() )
			{
				aJikoku.setChakujikoku( aJikoku2.getChakujikoku() ) ;
			}
			if ( !aJikoku2.getHatsujikoku().isNull() )
			{
				aJikoku.setHatsujikoku( aJikoku2.getHatsujikoku() ) ;
			}
			aJikoku.setRessyaTrackIndex(aJikoku2.getRessyaTrackIndex());

			//駅作業のコピー、aRessya2がaRessyaよりも終点方にある場合、aRessya2の始発駅前作業はコピーしません
			if (!(iEkiOrder == iValidSihatsuEkiOrder2 &&
				iValidSihatsuEkiOrder1 < iValidSihatsuEkiOrder2))
			{
				aJikoku.setCentDedBeforeOperationCont(*aJikoku2.getCentDedBeforeOperationCont());
			}
			//aRessya2がaRessyaよりも起点方にある場合、aRessya2の終着駅後作業はコピーしません
			if (!(iEkiOrder == iValidSyuuchakuEkiOrder2 &&
				iValidSyuuchakuEkiOrder1 > iValidSyuuchakuEkiOrder2))
			{
				aJikoku.setCentDedAfterOperationCont(*aJikoku2.getCentDedAfterOperationCont());
			}

			aRessya.setCentDedEkiJikoku( iEkiOrder , aJikoku ) ;
		}
	}

	aRessya.adjustOperation();

	// ================================	
	//	1番目の列車に駅時刻を設定
	//	2番目の列車は削除
	// ================================	
	pMuiRessya->set( aRessya , iRessyaIndex ) ;
	pMuiRessya->erase( iRessyaIndex2 ) ;
}

	// ********************************
	//	コンストラクタ・デストラクタ
	// ********************************
CRessyaContUnifier::CRessyaContUnifier()
{
}
CRessyaContUnifier::‾CRessyaContUnifier() 
{
}

	// ********************************
	//@name 操作
	// ********************************
void CRessyaContUnifier::unify( 
	Mui<CentDedRessya>* pMuiRessya ,
	const CentDedEkiCont* pCentDedEkiCont,
	IfProgress* pIfProgress ) 
{
	int iRv = 0 ; 

	// 列車番号と種別Indexのキャッシュを作成する
	//	これは、pMuiRessya->get()が遅い(より詳しくは、CentDedRessyaのコピーコンストラクタが遅い)
	//	ためです。
	vector<tstring>	arstrRessyabangou ;
	vector<int>	ariRessyaSyubetsu;
	arstrRessyabangou.reserve( pMuiRessya->size() ) ;
	ariRessyaSyubetsu.reserve(pMuiRessya->size());
	for ( int iRessyaIndex = 0 ; iRessyaIndex < pMuiRessya->size() ; iRessyaIndex ++ )
	{
		arstrRessyabangou.push_back( pMuiRessya->get( iRessyaIndex ).getRessyabangou() ) ;
		ariRessyaSyubetsu.push_back(pMuiRessya->get(iRessyaIndex).getRessyasyubetsuIndex());
	}

	//	列車番号の同じものを一本化
	for ( int iRessyaIndex = 0 ; 
		iRv == 0 && iRessyaIndex < pMuiRessya->size() - 1 ; 
		iRessyaIndex ++ )
	{
		tstring	strRessyabangou = arstrRessyabangou[iRessyaIndex] ;

		//	列車番号が空文字列でない場合にだけ、一本化を行います
		if ( strRessyabangou.length() > 0 )
		{
			//	一本化対象の列車を検索
			for ( int iRessyaIndex2 = iRessyaIndex + 1 ;
				iRessyaIndex2 <  pMuiRessya->size() ;
				iRessyaIndex2 ++ )
			{
				//	列車番号が同一なら、一本化を行います。
				//	18/1/7 種別も同一の場合のみ、一本化を行います。
				/**
					V2 駅作業及び発着駅を要件に加える
				*/
				if (strRessyabangou == arstrRessyabangou[iRessyaIndex2] &&
					ariRessyaSyubetsu[iRessyaIndex] == ariRessyaSyubetsu[iRessyaIndex2])
				{
					const CentDedRessya aRessya1 = pMuiRessya->get(iRessyaIndex);
					int iValidSihatsuEkiOrder1 = aRessya1.getValidSihatsuEki();
					int iValidSyuuchakuEkiOrder1 = aRessya1.getValidSyuuchakuEki();
					if (iValidSihatsuEkiOrder1 == -1 ||
						iValidSyuuchakuEkiOrder1 == -1)
					{
						continue;
					}
					const CentDedRessya	aRessya2 = pMuiRessya->get(iRessyaIndex2);
					int iValidSihatsuEkiOrder2 = aRessya2.getValidSihatsuEki();
					int iValidSyuuchakuEkiOrder2 = aRessya2.getValidSyuuchakuEki();
					if (iValidSihatsuEkiOrder2 == -1 ||
						iValidSyuuchakuEkiOrder2 == -1)
					{
						continue;
					}
					if (iValidSyuuchakuEkiOrder1 <= iValidSihatsuEkiOrder2)
					{
						//aRessya1の下に、aRessya2がつながる形になります
						//aRessya1の終着駅と、aRessya2の始発駅が同一駅かどうかを確認
						if (iValidSyuuchakuEkiOrder1 != iValidSihatsuEkiOrder2 &&
							!pCentDedEkiCont->isSameBrunchLoopGroup(
								iValidSyuuchakuEkiOrder1, iValidSihatsuEkiOrder2, aRessya1.getRessyahoukou()))
						{
							continue;
						}
						//各列車の作業を確認
						//Ver2.05仮処理
						if (aRessya1.getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_In/* ||
							(aRessya1.getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Junction &&
								aRessya1.getSyubetsuChange())*/)
						{
							continue;
						}
						if (aRessya2.getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Out)
						{
							continue;
						}
					}
					else if (iValidSyuuchakuEkiOrder2 <= iValidSihatsuEkiOrder1)
					{
						//aRessya2の下に、aRessya1がつながる形になります
						//aRessya2の終着駅と、aRessya1の始発駅が同一駅かどうかを確認
						if (iValidSyuuchakuEkiOrder2 != iValidSihatsuEkiOrder1 &&
							!pCentDedEkiCont->isSameBrunchLoopGroup(
								iValidSyuuchakuEkiOrder2, iValidSihatsuEkiOrder1, aRessya1.getRessyahoukou()))
						{
							continue;
						}
						//各列車の作業を確認
						//Ver2.05仮処理
						if (aRessya2.getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_In /*||
							(aRessya2.getLastOperation().getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Junction &&
								aRessya2.getSyubetsuChange())*/)
						{
							continue;
						}
						if (aRessya1.getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Out)
						{
							continue;
						}
					}

					unify(pMuiRessya, iRessyaIndex, iRessyaIndex2);

					//キャッシュの更新
					arstrRessyabangou.erase(arstrRessyabangou.begin() + iRessyaIndex2);
					ariRessyaSyubetsu.erase(ariRessyaSyubetsu.begin() + iRessyaIndex2);

					iRessyaIndex2--;
				}
			}
		}


		// ================================
		//	処理進捗表示
		// ================================
		if ( pIfProgress != NULL )
		{
			int iProgressResult = pIfProgress->onNotifyProgress( 
				iRessyaIndex , pMuiRessya->size() ) ;
			if ( iProgressResult != 0 )
			{
				iRv = iProgressResult ;
			}
		}
	}
	/*
	//	列車番号の同じものを一本化
	for ( int iRessyaIndex = 0 ; 
		iRv == 0 && iRessyaIndex < pMuiRessya->size() - 1 ; 
		iRessyaIndex ++ )
	{
		CentDedRessya	aRessya = pMuiRessya->get( iRessyaIndex ) ;
		//TODO:Muからconst CentDedRessya* を取得するように変更
		tstring	strRessyabangou = aRessya.getRessyabangou() ;

		//	列車番号が空文字列でない場合にだけ、一本化を行います
		if ( strRessyabangou.length() > 0 )
		{
			CentDedRessya	aRessya2( aRessya.getCentDedEkiJikokuCount() , 
				aRessya.getRessyahoukou() ) ;
			
			int iRessyaIndex2 ;
			// ================================
			//	一本化対象の列車を検索
			// ================================
			for ( iRessyaIndex2 = iRessyaIndex + 1 ;
				iRessyaIndex2 <  pMuiRessya->size() ;
				iRessyaIndex2 ++ )
			{
				aRessya2 = pMuiRessya->get( iRessyaIndex2 ) ;
				//TODO:Muからconst CentDedRessya* を取得するように変更

				// ================================
				//	列車番号が同一なら、一本化を行います。
				// ================================
				if ( strRessyabangou == aRessya2.getRessyabangou() )
				{
					unify( pMuiRessya , iRessyaIndex , iRessyaIndex2 ) ;
					iRessyaIndex2 -- ;
				}
			}
		}


		// ================================
		//	処理進捗表示
		// ================================
		if ( pIfProgress != NULL )
		{
			int iProgressResult = pIfProgress->onNotifyProgress( 
				iRessyaIndex , pMuiRessya->size() ) ;
			if ( iProgressResult != 0 )
			{
				iRv = iProgressResult ;
			}
		}
	}
	*/
}

} //namespace entDed


