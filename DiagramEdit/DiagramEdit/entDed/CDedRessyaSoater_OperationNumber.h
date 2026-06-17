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
//	CDedRessyaSoater_OperationNumber.h
// $Id: CDedRessyaSoater_OperationNumber.h 
// ****************************************************************
*/
/** @file */
#ifndef  CDedRessyaSoater_OperationNumber_h
#define  CDedRessyaSoater_OperationNumber_h

#include "CDedRessyaSoater.h"

namespace entDed{

// ****************************************************************
//	CDedRessyaSoater_OperationNumber
// ****************************************************************
/**
@brief
	【概要】
	CentDedRessyaCont 内の列車を、運用番号に従って並べ替えます。

	
	【使い方】
	
	1.  コンストラクタでオブジェクトを生成してください。
	
	2.　sort() メソッドを呼び出すと、thisは、指定された列車コンテナのすべての列車をソートします。

	比較基準は、以下のとおりです。
			- NULLでないものとNULLのものとでは、NULLでないものが先。
			- 運用番号が辞書順で早い方が先。空白のものは後。
			- 始発駅時刻が早い方が先。
			- 列車Indexの小さい方が先。

*/
class CDedRessyaSoater_OperationNumber : public CDedRessyaSoater
{
private:
	/**
	ダイヤグラム起点時刻を指定してください。
	this は、ソート時に、この値を最も小さい時刻と みなします。
	(例：この時刻に5:00が指定された場合は、
	@code
	5:00<23:59<0:00<4:59
	@endcode
	として比較を行います)
	*/
	CdDedJikoku  m_jikokuKitenJikoku;

	/**
		運用番号を比較するとき、末尾側の要素から比較するかどうかを指定します
		（例）
		12ABとCD34を比較するとき、
		m_bCompareBottomがfalseの場合、先頭から比較するので
		"12"と"CD"の比較により、12ABが先になります。
		m_bCompareBottomがtrueの場合、末尾から比較するので、
		"AB"と"34"の比較により、CD34が先になります。
	*/
	bool m_bCompareBottom;

public:
	// ********************************
	//	コンストラクタ
	// ********************************
	/**
	*/
	CDedRessyaSoater_OperationNumber(
		const CdDedJikoku&  jikokuKitenJikoku,
		const bool bCompareBottom) ;

	virtual ~CDedRessyaSoater_OperationNumber() ;
	
protected:
	// --------------------------------
	///@name sort の下請関数(templateパターン)
	// --------------------------------
	///@{
	/**
		指定された列車Indexの列車を、
	@param pRessyaCont [in]
		ソート対象の列車コンテナを指定してください。
	@param muRessyaIndexOrder [in,out]
		ソートを行う列車Indexを保持したコンテナを指定してください。
		(例：列車Index0～4をソートしたい場合は、
		{0,1,2,3,4} の5つの要素を持つコンテナを指定してください。
		この関数はこの配列を、駅時刻Order順の早い列車Index順にソートします。
	@param pIfProgress [in]
		進捗状態の通知を受けたい場合は、進捗状態通知を受け取る
		インスタンスへのポインタを指定してください。
		NULLなら、この関数は進捗状態の通知を行いません。
	@note 
		この関数で得たソート結果を
		sortWithSortedRessyaIndex() に渡すことにより、
		列車コンテナをソートすることができます。
	*/
	virtual void sortRessyaIndex( 
		const CentDedRessyaCont* pRessyaCont , 
		Mui<int>* muRessyaIndexOrder , 
		IfProgress* pIfProgress ) ;

	///@}

};

} //namespace entDed


#endif /*CDedRessyaSoater_OperationNumber_h*/
