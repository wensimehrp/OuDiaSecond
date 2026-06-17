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
//	CDedRessyaSoater_OperationNumber.cpp
// $Id: CDedRessyaSoater_OperationNumber.cpp 
// ****************************************************************
*/
/** @file */
#include "stdafx.h"
#include <algorithm>

#include "str\strtoint.h"
#include "NsMu\CMup_vector.h"
#include "NsMu\CaMui.h"
#include "CDedRessyaSoater_OperationNumber.h"

namespace entDed{

// ****************************************************************
//	CdRessyaForSort_OperationNumber
// ****************************************************************
	/**
		Mu<CentDedRessyaCont*> 内の列車(のIndex)を、
		運用番号で比較する関数オブジェクトです。
	*/
	class CentDedRessyaIdxCompare_OperationNumber
	{
		// ********************************
		///@name 関連
		// ********************************
		///@{
		/**
			列車コンテナ。
		*/
		const Mu<const CentDedRessya*>* m_pCentDedRessyaCont  ; 

		/**
		ダイヤグラム起点時刻を指定してください。
		この関数は、ソート時に、この値を最も小さい時刻と
		みなします。
		(例：この時刻に5:00が指定された場合は、5:00<23:59<0:00<4:59 として比較を行います)
		*/
		CdDedJikoku m_jikokuKitenJikoku;

		/**
			列車番号を比較するとき、末尾側の要素から比較するかどうかを指定します

		*/
		bool m_bCompareBottom;
		///@}
	public:
		CentDedRessyaIdxCompare_OperationNumber(
			const Mu<const CentDedRessya*>* pCentDedRessyaCont,
			const CdDedJikoku& jikokuKitenJikoku,
			const bool bCompareBottom)
			: m_pCentDedRessyaCont( pCentDedRessyaCont )
			, m_jikokuKitenJikoku(jikokuKitenJikoku)
			, m_bCompareBottom(bCompareBottom)
		{
		};
		/**
		@return
			*m_pCentDedRessyaCont->get(idxleft ) < *m_pCentDedRessyaCont->get(idxright ) 
			なら真です。

		@note
		  比較基準は、
			- NULLでないものとNULLのものとでは、NULLでないものが先。
				- 両方がNULL列車の場合は、列車Indexの小さいほうが先。
			- 有効始発駅がないものとあるものとでは、あるものが先。
				- 両方が有効始発駅がない場合は、列車Indexの小さいほうが先。
			- 運用番号がないものとあるものとでは、あるものが先。
				- 両方が運用番号がない場合は、列車Indexの小さいほうが先。
			- 運用番号が辞書順で早い方が先。空白のものは後。
			- 始発駅時刻が早い方が先。
			- 列車Indexの小さい方が先。
		*/
		bool operator()( 
			int idxleft , 
			int idxright )
		{
			const CentDedRessya& left  = *m_pCentDedRessyaCont->get(idxleft ) ;
			const CentDedRessya& right = *m_pCentDedRessyaCont->get(idxright ) ;
			// --------------------------------
			//	片方がNULLの場合の比較
			//	- NULLでないものとNULLのものとでは、NULLでないものが先。
			// --------------------------------
			if ( !left.isNull() && right.isNull() )
			{
				//	leftは非NULLで、rightはNULL
				return true ;
			}
			else if ( left.isNull() && !right.isNull() )
			{
				//	leftはNULLで、rightは非NULL
				return false ;
			}
			else if (left.isNull() && right.isNull())
			{
				// --------------------------------
				//	- 両方がNULL列車の場合は、列車Indexの小さいほうが先。
				// --------------------------------
				if (idxleft < idxright)
				{
					return true;
				}
				return false;
			}

			//有効始発駅が存在するかどうか
			int iLeftValidSihatsuEki = left.getValidSihatsuEki();
			int iRightValidSihatsuEki = right.getValidSihatsuEki();
			// --------------------------------
			//	片方の有効始発駅がない場合の比較
			//	- 有効始発駅がないものとあるものとでは、あるものが先。
			// --------------------------------
			if (iLeftValidSihatsuEki != -1 && iRightValidSihatsuEki == -1)
			{
				//	leftは有効始発駅ありで、rightは有効始発駅なし
				return true;
			}
			else if (iLeftValidSihatsuEki == -1 && iRightValidSihatsuEki == -1)
			{
				//	leftは有効始発駅なしで、rightは有効始発駅あり
				return false;
			}
			else if (iLeftValidSihatsuEki == -1 && iRightValidSihatsuEki == -1)
			{
				// --------------------------------
				//	- 両方の有効始発駅がない場合は、列車Indexの小さいほうが先。
				// --------------------------------
				if (idxleft < idxright)
				{
					return true;
				}
				return false;
			}

			// --------------------------------
			//	運用番号があるかないかでの比較
			//	- 運用番号がないものとあるものとでは、あるものが先。
			// --------------------------------
			if (!left.getOperationNumber(iLeftValidSihatsuEki).empty() && right.getOperationNumber(iRightValidSihatsuEki).empty())
			{
				//	leftは運用番号ありで、rightは運用番号なし
				return true;
			}
			else if (left.getOperationNumber(iLeftValidSihatsuEki).empty() && !right.getOperationNumber(iRightValidSihatsuEki).empty())
			{
				//	leftは運用番号なしで、rightは運用番号あり
				return false;
			}
			else if (left.getOperationNumber(iLeftValidSihatsuEki).empty() && right.getOperationNumber(iRightValidSihatsuEki).empty())
			{
				// --------------------------------
				//	- 両方の運用番号がない場合は、列車Indexの小さいほうが先。
				// --------------------------------
				if (idxleft < idxright)
				{
					return true;
				}
				return false;
			}

			tstring strLeftOperationNumberFront = left.getOperationNumber(left.getValidSihatsuEki()).front();
			tstring strRightOperationNumberFront = right.getOperationNumber(right.getValidSihatsuEki()).front();
			// --------------------------------
			//	片方の運用番号が空白の場合の比較
			//	- 空白でないものと空白のものとでは、空白でないものが先。
			// --------------------------------
			if (!strLeftOperationNumberFront.empty() && strRightOperationNumberFront.empty())
			{
				//	leftは非空白で、rightは空白
				return true;
			}
			else if (strLeftOperationNumberFront.empty() && !strRightOperationNumberFront.empty())
			{
				//	leftは空白で、rightは非空白
				return false;
			}
			else if (strLeftOperationNumberFront.empty() && strRightOperationNumberFront.empty())
			{
				// --------------------------------
				//	- 両方の運用番号が空白の場合は、列車Indexの小さいほうが先。
				// --------------------------------
				if (idxleft < idxright)
				{
					return true;
				}
				return false;
			}


			vector<int> iLeftOperationNumber;
			vector<int> iRightOperationNumber;
			vector<tstring> strLeftOperationNumberPart;
			vector<tstring> strRightOperationNumberPart;
			left.splitOperationNumber(iLeftOperationNumber, strLeftOperationNumberPart);
			right.splitOperationNumber(iRightOperationNumber, strRightOperationNumberPart);

			if (m_bCompareBottom)
			{
				int iLeftSize = iLeftOperationNumber.size();
				int iRightSize = iRightOperationNumber.size();
				int iMin = min(iLeftSize, iRightSize);
				for (int idx = 1; idx <= iMin; idx++)
				{
					// --------------------------------
					//	- 数字とそれ以外では数字の方が先
					// --------------------------------
					{
						if (iLeftOperationNumber[iLeftSize - idx] != INT_MIN && iRightOperationNumber[iRightSize - idx] == INT_MIN)
						{
							return true;
						}
						else if (iLeftOperationNumber[iLeftSize - idx] == INT_MIN && iRightOperationNumber[iRightSize - idx] != INT_MIN)
						{
							return false;
						}
					}

					if (iLeftOperationNumber[iLeftSize - idx] == INT_MIN)
					{
						//共に数字以外の場合、文字数→辞書順
						// --------------------------------
						//	- 文字部の長さが短い方が先
						// --------------------------------
						{
							if (strLeftOperationNumberPart[iLeftSize - idx].length() < strRightOperationNumberPart[iRightSize - idx].length())
							{
								return true;
							}
							else if (strLeftOperationNumberPart[iLeftSize - idx].length() > strRightOperationNumberPart[iRightSize - idx].length())
							{
								return false;
							}
						}
						// --------------------------------
						//	- 文字部が辞書順で早い方が先。
						// --------------------------------
						{
							if (strLeftOperationNumberPart[iLeftSize - idx] < strRightOperationNumberPart[iRightSize - idx])
							{
								return true;
							}
							else if (strLeftOperationNumberPart[iLeftSize - idx] > strRightOperationNumberPart[iRightSize - idx])
							{
								return false;
							}
						}
					}
					else
					{
						//共に数字の場合、数字の大小
						// --------------------------------
						//	- 数字が小さいものが先
						// --------------------------------
						{
							if (iLeftOperationNumber[iLeftSize - idx] < iRightOperationNumber[iRightSize - idx])
							{
								return true;
							}
							else if (iLeftOperationNumber[iLeftSize - idx] > iRightOperationNumber[iRightSize - idx])
							{
								return false;
							}
						}
					}

				}
			}
			else
			{
				int iMin = min(iLeftOperationNumber.size(), iRightOperationNumber.size());
				for (int idx = 0; idx < iMin; idx++)
				{
					// --------------------------------
					//	- 数字とそれ以外では数字の方が先
					// --------------------------------
					{
						if (iLeftOperationNumber[idx] != INT_MIN && iRightOperationNumber[idx] == INT_MIN)
						{
							return true;
						}
						else if (iLeftOperationNumber[idx] == INT_MIN && iRightOperationNumber[idx] != INT_MIN)
						{
							return false;
						}
					}

					if (iLeftOperationNumber[idx] == INT_MIN)
					{
						//共に数字以外の場合、文字数→辞書順
						// --------------------------------
						//	- 文字部の長さが短い方が先
						// --------------------------------
						{
							if (strLeftOperationNumberPart[idx].length() < strRightOperationNumberPart[idx].length())
							{
								return true;
							}
							else if (strLeftOperationNumberPart[idx].length() > strRightOperationNumberPart[idx].length())
							{
								return false;
							}
						}
						// --------------------------------
						//	- 文字部が辞書順で早い方が先。
						// --------------------------------
						{
							if (strLeftOperationNumberPart[idx] < strRightOperationNumberPart[idx])
							{
								return true;
							}
							else if (strLeftOperationNumberPart[idx] > strRightOperationNumberPart[idx])
							{
								return false;
							}
						}
					}
					else
					{
						//共に数字の場合、数字の大小
						// --------------------------------
						//	- 数字が小さいものが先
						// --------------------------------
						{
							if (iLeftOperationNumber[idx] < iRightOperationNumber[idx])
							{
								return true;
							}
							else if (iLeftOperationNumber[idx] > iRightOperationNumber[idx])
							{
								return false;
							}
						}
					}

				}
			}
			// --------------------------------
			//	- 要素数が少ないものが先
			// --------------------------------
			{
				if (iLeftOperationNumber.size() < iRightOperationNumber.size())
				{
					return true;
				}
				else if (iLeftOperationNumber.size() > iRightOperationNumber.size())
				{
					return false;
				}
			}
			
			// --------------------------------
			//	- 始発駅発時刻が早い方が先。
			// --------------------------------
			CdDedJikoku aJikokuLeft = left.getCentDedEkiJikoku(iLeftValidSihatsuEki).getHatsujikoku(true);
			CdDedJikoku aJikokuRight = right.getCentDedEkiJikoku(iRightValidSihatsuEki).getHatsujikoku(true);
			//有効始発駅の発時刻がNULLになることはない。
			//if (!aJikokuLeft.isNull() && aJikokuRight.isNull())
			//{
			//	//	aJikokuLeftは非NULLで、aJikokuRightはNULL
			//	return true;
			//}
			//else if (aJikokuLeft.isNull() && !aJikokuRight.isNull())
			//{
			//	//	aJikokuLeftはNULLで、aJikokuRightは非NULL
			//	return false;
			//}

			if (aJikokuLeft.compare(aJikokuRight, m_jikokuKitenJikoku) < 0)
			{
				//	aJikokuLeftの方がaJikokuRightよりも前
				return true;
			}
			else if (aJikokuLeft.compare(aJikokuRight, m_jikokuKitenJikoku) > 0)
			{
				//	aJikokuRightの方がaJikokuLeftよりも前
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
//	CDedRessyaSoater_OperationNumber
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
CDedRessyaSoater_OperationNumber::CDedRessyaSoater_OperationNumber(
	const CdDedJikoku&  jikokuKitenJikoku,
	const bool bCompareBottom)
	: m_jikokuKitenJikoku(jikokuKitenJikoku)
	, m_bCompareBottom(bCompareBottom)
{
}

CDedRessyaSoater_OperationNumber::~CDedRessyaSoater_OperationNumber()
{
}
	
	// --------------------------------
	//@name sort の下請関数(templateパターン)
	// --------------------------------
void CDedRessyaSoater_OperationNumber::sortRessyaIndex(
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
			CentDedRessyaIdxCompare_OperationNumber( 
					pCentDedRessyaCont ,
					m_jikokuKitenJikoku,
				m_bCompareBottom) ) ;


		//	ソート結果を、元のコンテナに戻す
		muRessyaIndexOrder->erase( 0 , INT_MAX ) ;
		CaMui<int>( muRessyaIndexOrder ).insert( &contiRessyaIndexOrder , 0 , INT_MAX ) ;
	}

}

} //namespace entDed


