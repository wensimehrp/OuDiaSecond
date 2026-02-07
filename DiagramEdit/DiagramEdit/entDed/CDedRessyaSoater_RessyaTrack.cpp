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
//	CDedRessyaSoater_RessyaTrack.cpp
// $Id: CDedRessyaSoater_RessyaTrack.cpp 
// ****************************************************************
*/
/** @file */
#include "stdafx.h"
#include <algorithm>

#include "str\strtoint.h"
#include "NsMu\CMup_vector.h"
#include "NsMu\CaMui.h"
#include "CDedRessyaSoater_RessyaTrack.h"

namespace entDed{

// ****************************************************************
//	CdRessyaForSort_RessyaTrack
// ****************************************************************
	/**
		Mu<CentDedRessyaCont*> 内の列車(のIndex)を、
		運用番号で比較する関数オブジェクトです。
	*/
	class CentDedRessyaIdxCompare_RessyaTrack
	{
		// ********************************
		///@name 関連
		// ********************************
		///@{
		/**
			列車コンテナ。
		*/
		const Mu<const CentDedRessya*>* m_pCentDedRessyaCont  ;

		int m_iEkiOrder;

		/**
		ダイヤグラム起点時刻を指定してください。
		この関数は、ソート時に、この値を最も小さい時刻と
		みなします。
		(例：この時刻に5:00が指定された場合は、5:00<23:59<0:00<4:59 として比較を行います)
		*/
		CdDedJikoku m_jikokuKitenJikoku;
		///@}
		/**
		駅扱を、並び順を示す整数値に変換します。
		@param eEkiatsukai [in]
		駅扱を指定してください。
		@return
		駅扱の並び順を表す整数値を返します。
		停車・通過・運行なしの順となります。
		*/
		int sortOrderOfEEkiatsukai(CentDedEkiJikoku::EEkiatsukai eEkiatsukai)
		{
			int iRv = 0;
			switch (eEkiatsukai)
			{
			case CentDedEkiJikoku::Ekiatsukai_Teisya:	iRv = 0;	break;
			case CentDedEkiJikoku::Ekiatsukai_Tsuuka:	iRv = 0;	break;
			case CentDedEkiJikoku::Ekiatsukai_None:	iRv = 1;	break;
			}
			return iRv;
		}

	public:
		CentDedRessyaIdxCompare_RessyaTrack(
			const Mu<const CentDedRessya*>* pCentDedRessyaCont,
			const int iEkiOrder,
			const CdDedJikoku& jikokuKitenJikoku)
			: m_pCentDedRessyaCont( pCentDedRessyaCont )
			, m_iEkiOrder(iEkiOrder)
			, m_jikokuKitenJikoku(jikokuKitenJikoku)
		{
		};
		/**
		@return
			*m_pCentDedRessyaCont->get(idxleft ) < *m_pCentDedRessyaCont->get(idxright ) 
			なら真です。

		@note
		  比較基準は、
			- 指定駅Indexの駅扱は、(停車・通過)・運行なしの順
			- 列車番線Indexが若い物が先
			- 駅時刻がNULLでないものとNULLのものとでは、NULLでないものが先。
			- 駅時刻の小さいものが先
			- 駅時刻が同じならRessyaIdxの小さいほうが先。
		*/
		bool operator()( 
			int idxleft , 
			int idxright )
		{
			const CentDedRessya& left  = *m_pCentDedRessyaCont->get(idxleft ) ;
			const CentDedRessya& right = *m_pCentDedRessyaCont->get(idxright ) ;
			CentDedEkiJikoku	aEkiJikokuLeft = left.getCentDedEkiJikoku(m_iEkiOrder);
			CentDedEkiJikoku	aEkiJikokuRight = right.getCentDedEkiJikoku(m_iEkiOrder);

			// --------------------------------
			//	- 指定駅Indexの駅扱は、(停車・通過)・運行なしの順
			// --------------------------------
			{
				int iEkiatsukaiLeft = sortOrderOfEEkiatsukai(aEkiJikokuLeft.getEkiatsukai());
				int iEkiatsukaiRight = sortOrderOfEEkiatsukai(aEkiJikokuRight.getEkiatsukai());
				if (iEkiatsukaiLeft < iEkiatsukaiRight)
				{
					return true;
				}
				else if (iEkiatsukaiLeft > iEkiatsukaiRight)
				{
					return false;
				}
			}

			// --------------------------------
			//	列車番線Indexが若い方が先
			//	- NULLでないものとNULLのものとでは、NULLでないものが先。
			// --------------------------------
			if (aEkiJikokuLeft.getRessyaTrackIndex() < aEkiJikokuRight.getRessyaTrackIndex())
			{
				//	aRessyaTrackLeftの方がaRessyaTrackRightよりも若い
				return true ;
			}
			else if (aEkiJikokuLeft.getRessyaTrackIndex() > aEkiJikokuRight.getRessyaTrackIndex())
			{
				//	aRessyaTrackRightの方がaRessyaTrackLeftよりも若い
				return false ;
			}

			// --------------------------------
			//	ソート対象の駅の発時刻を取得します。
			//	NULLの場合は、着で代替
			// --------------------------------
			//	ソート対象の駅の発時刻を取得します。
			CdDedJikokuOrder	aJikokuOrderLeft = 
				CdDedJikokuOrder(m_iEkiOrder, CdDedJikokuOrder::EkiJikokuItem_Hatsu);
			CdDedJikoku	aJikokuLeft = left.getEkiJikoku(aJikokuOrderLeft);
			CdDedJikokuOrder	aJikokuOrderRight = 
				CdDedJikokuOrder(m_iEkiOrder, CdDedJikokuOrder::EkiJikokuItem_Hatsu);
			CdDedJikoku	aJikokuRight = right.getEkiJikoku(aJikokuOrderRight);

			//	列車の着時刻がNULLの場合は、発時刻を取得します。
			if (aJikokuLeft.isNull())
			{
				aJikokuOrderLeft.EkiJikokuItemInvert();

				aJikokuLeft = left.getEkiJikoku(aJikokuOrderLeft);
			}
			if (aJikokuRight.isNull())
			{
				aJikokuOrderRight.EkiJikokuItemInvert();

				aJikokuRight = right.getEkiJikoku(aJikokuOrderRight);
			}
			// --------------------------------
			//	- 駅時刻がNULLでないものとNULLのものとでは、NULLでないものが先。
			// --------------------------------
			if (!aJikokuLeft.isNull() && aJikokuRight.isNull())
			{
				//	leftは非NULLで、rightはNULL
				return true;
			}
			else if (aJikokuLeft.isNull() && !aJikokuRight.isNull())
			{
				//	leftはNULLで、rightは非NULL
				return false;
			}


			// --------------------------------
			//	- 駅時刻の小さいものが先
			// --------------------------------
			int iResult = aJikokuLeft.compare(aJikokuRight, m_jikokuKitenJikoku);
			if (iResult == -1)
			{
				return true;
			}
			else if (iResult == 1)
			{
				return false;
			}

			// --------------------------------
			//	着時刻と発時刻では、着時刻が先
			// --------------------------------
			if (aJikokuOrderLeft.getEkiJikokuItem() == CdDedJikokuOrder::EkiJikokuItem_Chaku &&
				aJikokuOrderRight.getEkiJikokuItem() == CdDedJikokuOrder::EkiJikokuItem_Hatsu)
			{
				return true;
			}
			else if (aJikokuOrderLeft.getEkiJikokuItem() == CdDedJikokuOrder::EkiJikokuItem_Hatsu &&
				aJikokuOrderRight.getEkiJikokuItem() == CdDedJikokuOrder::EkiJikokuItem_Chaku)
			{
				return false;
			}

			// --------------------------------
			//	- 列車Indexの小さいほうが先。
			// --------------------------------
			if ( idxleft < idxright )
			{
				return true ;
			}
			return false ;
		}
	};



// ****************************************************************
//	CDedRessyaSoater_RessyaTrack
// ****************************************************************
	// ********************************
	//@name 集約
	// ********************************

	// ********************************
	//@name 状態
	// ********************************
	// --------------------------------
	//@name 下請関数
	// --------------------------------
	// ********************************
	//	コンストラクタ
	// ********************************
CDedRessyaSoater_RessyaTrack::CDedRessyaSoater_RessyaTrack(
	const int iEkiOrder,
	const CdDedJikoku&  jikokuKitenJikoku)
	: m_iEkiOrder(iEkiOrder)
	,m_jikokuKitenJikoku(jikokuKitenJikoku)
{
}

CDedRessyaSoater_RessyaTrack::~CDedRessyaSoater_RessyaTrack()
{
}
	
	// --------------------------------
	//@name sort の下請関数(templateパターン)
	// --------------------------------
void CDedRessyaSoater_RessyaTrack::sortRessyaIndex(
		const CentDedRessyaCont* pRessyaCont , 
		Mui<int>* muRessyaIndexOrder , 
		IfProgress* pIfProgress ) 
{
	bool bAbort = false ;

	const Mu<const CentDedRessya*>* pCentDedRessyaCont = pRessyaCont->getMuPtr() ; 
	//pCentDedRessyaCont = CentDedRessyaCont オブジェクトへのポインタを保持する
	//	コンテナです。

	// --------------------------------
	//	ソート用駅時刻のコンテナの内容に従い、
	//	インデクスをソート
	// --------------------------------
	{
		//	ソートは std::sort を使うため、
		//	インデクスコンテナを std::vector に一旦コピーする
		CMup_vector<int>	contiRessyaIndexOrder ;
		CaMui<int>( &contiRessyaIndexOrder ).insert( muRessyaIndexOrder , 0 , INT_MAX ) ;

		//	std::vector の内容をソート
		std::sort( 
			contiRessyaIndexOrder.getAdaptee()->begin() ,
			contiRessyaIndexOrder.getAdaptee()->end() ,
			CentDedRessyaIdxCompare_RessyaTrack(
					pCentDedRessyaCont ,
					m_iEkiOrder,
					m_jikokuKitenJikoku) ) ;


		//	ソート結果を、元のコンテナに戻す
		muRessyaIndexOrder->erase( 0 , INT_MAX ) ;
		CaMui<int>( muRessyaIndexOrder ).insert( &contiRessyaIndexOrder , 0 , INT_MAX ) ;
	}

}

} //namespace entDed


