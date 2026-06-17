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
//	CRfEditCmd_RessyaSwap.h
//	$Id: CRfEditCmd_RessyaSwap.h $
// ****************************************************************
*/
#ifndef  CRfEditCmd_RessyaSwap_h
#define  CRfEditCmd_RessyaSwap_h
/** @file */

#include "CRfEditCmd.h"
#include "..\..\entDed\CentDedRessya.h"

namespace DedRosenFileData{ namespace EditCmd{
	//using namespace entDed;

// ****************************************************************
//	CRfEditCmd_RessyaSwap
// ****************************************************************
/**
@brief
 	  CDedRosenFileData オブジェクト内の CentDedRessya オブジェクトの
 	入れ替えの編集動作です。
 	
  このクラスは、 CDedRosenFileData オブジェクト内の
指定のダイヤ・指定の列車方向の複数の列車の入れ替えを
行います。

 */
class CRfEditCmd_RessyaSwap :
	public CRfEditCmd
{
private:
	// ********************************
	///@name 属性
	// ********************************
	///@{
	/**
 	編集対象のダイヤのインデクス。
 
 	コンストラクタで決まります。
	 */
	int m_iDiaIndex ;
	
	
	/**
	 	編集対象の列車方向。
	 
	 	コンストラクタで決まります。
	 */
	ERessyahoukou m_ERessyahoukou ;
	
	/**
	 	CentDedRosen オブジェクトの
	 	ダイヤインデクス m_iDiaIndex ・
	 	編集対象の列車方向 m_ERessyahoukou 内での、
	 	追加・削除対象となる列車インデクス。
	 
	 	INT_MAX は末尾を指定したものとみなします。
	 */
	int m_iIndexA ;
	
	/**
	 	CentDedRosen オブジェクトのダイヤインデクス m_iDiaIndex ・
	 	編集対象の列車方向 m_ERessyahoukou 内での、
	 	削除対象となる列車の数を指定してください。
	 	この値が0の場合は、execute() は 
	 	m_CentDedRessyaContSrc.size() 個の
	 	列車の追加だけを行います。
	 
	 	INT_MAX は、m_iDiaIndex から末尾までを指定したものとみなします。
		m_iIndexSrc と m_iDiaIndex を両方 INT_MAX にすることはできません。
	 */
	int m_iSizeA ;

	/**
		CentDedRosen オブジェクトの
		ダイヤインデクス m_iDiaIndex ・
		編集対象の列車方向 m_ERessyahoukou 内での、
		追加・削除対象となる列車インデクス。

		INT_MAX は末尾を指定したものとみなします。
	 */
	int m_iIndexB;
	
	/**
		運用機能有効時に、運用探索を行わない場合は、この値をtrueにします。
		連続入力時に、随時運用探索を行うと、処理時間が長くなるのでこの値をtrueにします。
	*/
	bool m_bWaitOperationConnect;
	///@}
private:
	// --------------------------------
	///@name 内部データ
	// --------------------------------
	///@{
	///@}
public:
	// ********************************
	//	コンストラクタ
	// ********************************

	/**
	 すべての属性を、引数で指定します。
	  @param iDiaIndex [in]
	 	編集対象のダイヤのインデクス。
	  @param eERessyahoukou [in]
	 	編集対象の列車方向。
	  @param iIndexA [in]
	 	CentDedRosen オブジェクトの
	 	ダイヤインデクス m_iDiaIndex ・
	 	編集対象の列車方向 m_ERessyahoukou 内での、
	 	入れ替え対象となる列車インデクス。
	  @param iSizeA [in]
	 	CentDedRosen オブジェクトのダイヤインデクス m_iDiaIndex ・
	 	編集対象の列車方向 m_ERessyahoukou 内での、
	 	iIndexAを先頭として、入れ替え対象となる列車の数を指定してください。
	  @param iIndexB [in]
	 	CentDedRosen オブジェクトの
	 	ダイヤインデクス m_iDiaIndex ・
	 	編集対象の列車方向 m_ERessyahoukou 内での、
	 	入れ替え対象となる列車インデクス。
		こちらは、列車本数は1本で固定となります。
	 */
	CRfEditCmd_RessyaSwap(
		int iDiaIndex ,
		ERessyahoukou eERessyahoukou ,
		int iIndexA,
		int iSizeA,
		int iIndexB) ;

	virtual ~CRfEditCmd_RessyaSwap() ;

 public:
	// ********************************
	///@name CRfEditCmd-操作
	// ********************************
	///@{
	/**
	 CDedRosenFileData オブジェクトに対して、編集操作を実行します。
	 また、編集動作に成功した場合、 this は、undo
	（編集動作の取り消し）を行うのに必要なデータを、
	メンバ変数に保持します。

	@param pCDedRosenFileData [in,out]
	 	この関数はこのオブジェクトに対して、編集操作を実行します。
	@return
	 	成功したら 0 以上、エラーなら負の数です。
	 	-	-1 ;	//	m_iDiaIndex の値が不正です。
	 	-	-2 ;	//	m_iDiaIndex の値が不正です。
	 	-	-11 ;	//	要素の削除に失敗しました。
	 	-	-12 ;	//	要素の追加に失敗しました。
	 
	<H4>
	【オーバライド】
	</H4>
	 	pCDedRosenFileData オブジェクトに対して、編集動作を実行してください。
	 */
	virtual int execute( CDedRosenFileData* pCDedRosenFileData ) ;
	
	/**
	「 this->execute() で行った編集操作を取り消す
	（ this->execute() で編集動作を行った直後の CDedRosenFileData 
	オブジェクトを、 this->execute() を行う直前の状態に
	する）」ための編集コマンドオブジェクトを生成します。

	このメンバ関数が返したオブジェクトを使って execute() を
	呼び出すことにより、 this->execute() 直後の状態の CentDedRosen
	 オブジェクトを、 this->execute() 直前の状態に戻すことができます。

	 @return
	 	execute() で行った編集操作を取り消し、
	 	 CDedRosenFileData オブジェクトを execute() を行う直前の状態に
	 	するためのコマンドオブジェクトを生成します。

	<H4>
	【オーバライド】
	</H4>
	execute() で実行した編集内容を元に戻すようなオブジェクトを
	生成してください。
	 */
	virtual Ou<CRfEditCmd> createUndoCmd()  ;
	
	///@}



public:
	// ********************************
	///@name CRfEditCmd_RessyaSwap-属性
	// ********************************
	///@{
	
	int getDiaIndex()const{	return m_iDiaIndex ;};

	ERessyahoukou getRessyahoukou()const{ return m_ERessyahoukou ;};
	int getIndexA()const{	return m_iIndexA ;};
	CRfEditCmd_RessyaSwap& setIndexA( int value )
	{
		m_iIndexA = value ;	return *this ; 
	};
	int getSizeA()const{	return m_iSizeA ;};
	CRfEditCmd_RessyaSwap& setSizeA( int value )
	{
		m_iSizeA = value ;	return *this ; 
	};

	int getIndexB()const { return m_iIndexB; };
	CRfEditCmd_RessyaSwap& setIndexB(int value)
	{
		m_iIndexB = value;	return *this;
	};

	CRfEditCmd_RessyaSwap& setWaitOperationConnect(bool value)
	{
		m_bWaitOperationConnect = value;	return *this;
	};
	const bool getWaitOperationConnect()const
	{
		return m_bWaitOperationConnect;
	}

	///@}
};

} } // namespace EditCmd namespace DedRosenFileData


#endif /*CRfEditCmd_RessyaSwap_h*/
