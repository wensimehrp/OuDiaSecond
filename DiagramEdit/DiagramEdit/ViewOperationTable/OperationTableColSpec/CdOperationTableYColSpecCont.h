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
// $Id: CdOperationTableYColSpecCont.h
// ****************************************************************
/** @file */
#pragma once

#ifndef ViewOperationTable_CdOperationTableYColSpecCont_h
#define ViewOperationTable_CdOperationTableYColSpecCont_h

#include "NsMu\CMup_vector.h"

#include "CdOperationTableYColSpec.h"
//#include "..\..\entDed\CdDedRessyaProperty.h"
#include <list>
#include "..\..\entDed\CentDedDia.h"


namespace ViewOperationTable { namespace OperationTableColSpec{
	using namespace entDed ;
/**
@brief
  運用表ビューの CWndDcdGridOperationTable の各列番号と表示内容の相互変換の
  機能を提供します。
  
  このクラスは、内部に全てのY列についての 『列番号-表示内容』の対応表を
保持します。 この対応表は、 CentDedEkiCont・CentDedEki に変更が発生
したら無効になります。このため、 CentDedEkiCont・CentDedEki に変更の
可能性がある状況では、対応表を更新する必要があります。

【使い方】

(1)  デフォルトコンストラクタでインスタンスを生成したあとは、 scan() で
『列番号-表示内容』の対応表を更新してください。

(2)  対応表更新後は、ColumnNumberToSpec(),ColumnNumberFromSpec() で、
列番号と表示内容の相互変換ができます。

*/
class CdOperationTableYColSpecCont
{
private:
	// ********************************
	///@name 関連
	// ********************************
	///@{
	///@}

	// ********************************
	///@name 属性
	// ********************************
	///@{
	/**
		同一運用の行数。scan() で決まります。
	*/
	int m_iRowCount ;
	/**
	- true ;[箱ダイヤを有効にする] モード
	*/
	bool m_bDisplayExtensionOperationTable;

	///@}

	// ********************************
	///@name 集約
	// ********************************
	///@{
	/**
		『列番号-表示内容』の対応表。
		インデクスが列番号に相当します。
		要素数が時刻表ビューのY列数に相当します。
	*/
	CMup_vector<CdOperationTableYColSpec>	m_contColumnSpec ;
	///@}

public:
	// ********************************
	//	コンストラクタ
	// ********************************
	/**
		scan() と等価です。
	@param pCentDedEkiCont
		駅コンテナ。
		このオブジェクトは、関数終了後は破棄できます。
	@param eRessyahoukou 
		列車方向
	@param bDisplayAllJikoku 
		- true ;[全時刻を表示] モード
	*/
	CdOperationTableYColSpecCont(
		int iRowCount,
		bool bDisplayExtensionOperationTable);
	CdOperationTableYColSpecCont() ;
 
public:
	// ********************************
	///@name CdYColSpec-関連
	// ********************************
	///@{
	///@}
	// ********************************
	///@name CdYColSpec-属性
	// ********************************
	///@{
	bool getDisplayExtensionOperationTable()const;
	int getRessyaCount()const ;

	///@}
	// ********************************
	///@name CdYColSpecCont-操作
	// ********************************
	///@{
	/**
		駅コンテナを走査して、 『列番号-表示内容』の対応表を更新します。
		this がそれまで保持していた内容はすべて失われます。 
	@param pCentDedEkiCont
		駅コンテナ。
		このオブジェクトは、関数終了後は破棄できます。
	@param eRessyahoukou 
		列車方向
	@param bDisplayAllJikoku 
		- true ;[全時刻を表示] モード
	*/
	void scan( 
		int iRowCount,
		bool bDisplayExtensionOperationTable);


	/**
	@return 
		列数を返します。
	*/
	int size() ;

	/**
		列番号から、表示するべき内容を導出します。
	@param iYColumnNumber 
		列番号を指定してください。
	@return
		表示すべき内容を返します。
		列番号が正しくない場合は、NULL状態のオブジェクトを返します。
	*/
	CdOperationTableYColSpec ColumnNumberToSpec(
		int iYColumnNumber ) ;

	/**
		表示内容に対する列番号を導出します。
	@param aCdYColSpec 
		表示内容を指定してください。
	@param bResolveSameStation
		- true ; 対応する表示項目が非表示である場合、代わりの列番号を返します。
		- false ;	対応する表示項目が非表示である場合、-1を返します。
	@return
		表示すべき内容を返します。
		対応する列番号がない場合(非表示を含む)は、-1を返します。

	 対応する表示項目が非表示で、 bResolveSameStation が true の場合、
	 以下のように動作します。

		- aCdYColSpec が、ColumnType_Ressyabangou
		(列車番号)～ColumnType_Gou(「号」表示) までなら、
		ColumnType_Ressyabangou～ColumnType_Gou のうちのいずれかが見つかった
		最初の列番号を返します。
		- aCdYColSpec が	ColumnType_Ekijikoku_Chaku
		(着時刻)ならば、同じ駅Orderの ColumnType_Ekijikoku_Hatsu(発時刻)
		を返します。その列も非表示なら、
		駅Orderが aCdYColSpec 未満で、
		ColumnType_Ekijikoku_Chaku か 
		ColumnType_Ekijikoku_Hatsu の列のうち、一番大きい列番号を返します。
		- aCdYColSpec が	
		ColumnType_Ekijikoku_Hatsu(発時刻)の場合も、
		ColumnType_Ekijikoku_Chaku の場合と同様です。
		- aCdYColSpec が	
		ColumnType_Bikou(備考)の場合、一番下の列を返します。

	*/
	int ColumnNumberFromSpec( 
		const CdOperationTableYColSpec&
			aCdOperationTableYColSpec  ) ;

	/**
		『列番号-表示内容』の対応表を削除します。
	*/
	void clear() ;
	///@}
};

} } //namespace OperationTableColSpec namespace ViewOperationTable

#endif/* ViewOperationTable_CdOperationTableYColSpecCont_h*/
