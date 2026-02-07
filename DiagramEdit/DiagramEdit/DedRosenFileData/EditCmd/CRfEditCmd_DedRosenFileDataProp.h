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
//	CRfEditCmd_DedRosenFileDataProp.h
//	$Id: CRfEditCmd_DedRosenFileDataProp.h 141 2012-10-20 08:03:25Z okm $
// ****************************************************************
*/
/** @file */
#ifndef  CRfEditCmd_DedRosenFileDataProp_h
#define  CRfEditCmd_DedRosenFileDataProp_h

#include "..\EditCmd\CRfEditCmd.h"
#include "Str\tstring.h"

namespace DedRosenFileData{ namespace EditCmd{

// ****************************************************************
//	CRfEditCmd_DedRosenFileDataProp
// ****************************************************************
/**
 * @brief
  CDedRosenFileData オブジェクトの属性
『路線ファイルのプロパティ』ダイアログで更新できる属性
を上書きする編集動作です。

 */
class CRfEditCmd_DedRosenFileDataProp :
	public CRfEditCmd
{
private:
	// ********************************
	///@name 属性
	// ********************************
	///@{
	/**
	 *	新しい
	 *	路線名。
	 *	コンストラクタで決まります。
	 */
	tstring	m_strRosenName ;

	/**
	 *	新しい
	 *	ダイヤの起点時刻です。
	 *	コンストラクタで決まります。
	 */
	CdDedJikoku	m_jikokuKitenJikoku ;

	/**
		ダイヤグラムの既定の駅間幅。

		列車設定のない駅間の、ダイヤグラムビュー上での
		縦方向の幅を『ダイヤグラムエンティティY座標』単位(秒)で指定します。
	
		既定値は 60 です。
		コンストラクタで初期化されます。この値は、ダイアログ表示時に
		初期値として使われます。
		OnOK() は、ダイアログの値で上書きします。クラスユーザーは、
		 DoModal() がリターンした後に、この値を参照することができます。
	*/
	int	m_iDiagramDgrYZahyouKyoriDefault ;

	/**
	運用機能の有効無効
		0:運用機能は無効です
		1:運用機能は通常モードです
		2:運用機能は軽量モードです
		規定値は0です
	*/
	int m_iEnableOperation;
	/**
	*	新しい
	*	下りダイヤ別名
	*	コンストラクタで決まります。
	*/
	tstring	m_strKudariDiaAlias;
	/**
	*	新しい
	*	上りダイヤ別名
	*	コンストラクタで決まります。
	*/
	tstring	m_strNoboriDiaAlias;

	/**
		折り返し時に運用番号を反転させるか否か
		この値がtrueの時、運用探索で下り⇔上りの接続が行われると、
		運用番号の並びを反転させます。
		(例)折り返し前が "01A","21B"の場合、
		折り返し後は"21B","01A"になります
	*/
	bool m_bOperationNumberReverse;

	/**
		運用接続時に起点時刻を跨ぐか否か
		規定値はtrueです。
	*/
	bool m_bOperationCrossKitenJikoku;

	/**
		基準運転時分を取得するダイヤのIndexです。
		規定値は0です。
	*/
	int m_iKijunDiaIndex;

	/**
		隠し種別をカスタマイズ時刻表・駅時刻表で表示するか否か
		規定値はtrueです。
	*/
	bool m_bDisableHiddenSyubetsu;

	/**
	 *	新しい
	 *	DiagramEdit の表示に関係するプロパティを保持する
	 *	単純データクラスです。
	 *	コンストラクタで決まります。
	 */
	CdDedDispProp	m_CdDedDispProp ;
	///@}
private:
	// --------------------------------
	///@name 内部データ
	// --------------------------------
	///@{
	/**
	 *	初期状態では空。
	 *	execute() を行った後は、execute() を行う直前の値となります。
	 */
	tstring	m_strRosenNameOld ;

	/**
	 *	初期状態では空。
	 *	execute() を行った後は、execute() を行う直前の値となります。
	 */
	CdDedJikoku	m_jikokuKitenJikokuOld ;

	/**
	 *	初期状態では空。
	 *	execute() を行った後は、execute() を行う直前の値となります。
	 */
	int m_iDiagramDgrYZahyouKyoriDefaultOld ;

	/**
	 *	初期状態では空。
	 *	execute() を行った後は、execute() を行う直前の値となります。
	*/
	int m_iEnableOperationOld;
	/**
	 *	初期状態では空。
	 *	execute() を行った後は、execute() を行う直前の値となります。
	*/
	tstring	m_strKudariDiaAliasOld;
	/**
	 *	初期状態では空。
	 *	execute() を行った後は、execute() を行う直前の値となります。
	*/
	tstring	m_strNoboriDiaAliasOld;
	/**
	 *	初期状態では空。
	 *	execute() を行った後は、execute() を行う直前の値となります。
	*/
	bool	m_bOperationNumberReverseOld;
	/**
	 *	初期状態では空。
	 *	execute() を行った後は、execute() を行う直前の値となります。
	*/
	bool m_bOperationCrossKitenJikokuOld;;

	/**
	 *	初期状態では空。
	 *	execute() を行った後は、execute() を行う直前の値となります。
	*/
	int m_iKijunDiaIndexOld;
	/**
	 *	初期状態では空。
	 *	execute() を行った後は、execute() を行う直前の値となります。
	*/
	bool m_bDisableHiddenSyubetsuOld;;

	/**
	 *	初期状態では空。
	 *	execute() を行った後は、execute() を行う直前の値となります。
	 */
	CdDedDispProp	m_CdDedDispPropOld ;
	///@}

public:
	// ********************************
	//	コンストラクタ
	// ********************************
	/**
	 @param strRosenName [in]
		新しい
		路線名。
		コンストラクタで決まります。
	 @param jikokuKitenJikoku [in]
		新しい
		ダイヤの起点時刻です。
		コンストラクタで決まります。
	 @param iDiagramDgrYZahyouKyoriDefault [in]
		ダイヤグラムの既定の駅間幅。
	 @param iEnableOperation [in]
		運用機能のモード設定
	 @param strKudariDiaAlias [in]
		下りダイヤの別名
	 @param strNoboriDiaAlias [in]
		上りダイヤの別名
	 @param bOperationNumberReverse [in]
		折り返しで運用番号を反転させるかどうかの設定
	 @param iOperationNumberRows [in]
		運用番号欄の段数
	 @param bOperationCrossKitenJikoku [in]
		運用接続時に起点時刻を跨ぐか否か
	 @param iKijunDiaIndex [in]
		基準運転時分を取得するダイヤのIndex
	 @param bDisableHiddenSyubetsu [in]
		隠し種別をカスタマイズ時刻表・駅時刻表で表示するか否か
	 @param aCdDedDispProp [in]
		新しい
		DiagramEdit の表示に関係するプロパティを保持する
		単純データクラスです。
		コンストラクタで決まります。
	*/
	CRfEditCmd_DedRosenFileDataProp( 
		const tstring& strRosenName ,
		const CdDedJikoku& jikokuKitenJikoku , 
		int	iDiagramDgrYZahyouKyoriDefault ,
		int iEnableOperation,
		const tstring& strKudariDiaAlias,
		const tstring& strNoboriDiaAlias,
		bool bOperationNumberReverse,
		bool bOperationCrossKitenJikoku,
		int iKijunDiaIndex,
		bool bDisableHiddenSyubetsu,
		const CdDedDispProp& aCdDedDispProp ) ;
	virtual ~CRfEditCmd_DedRosenFileDataProp() ;
	
public:
	// ********************************
	///@name	CRfEditCmd-操作
	// ********************************
	///@{
	/**
	 *	CDedRosenFileData オブジェクトに対して、編集操作を実行します。
	 *	　また、編集動作に成功した場合、 this は、undo
	 *	（編集動作の取り消し）を行うのに必要なデータを、
	 *	メンバ変数に保持します。
	 * @param pCDedRosenFileData [in,out]
	 *	この関数はこのオブジェクトに対して、編集操作を実行します。
	 * @return
	 *	成功したら 0 以上、エラーなら負の数です。
	 *	<H4>
	 *	【オーバライド】
	 *	</H4>
	 *	pCDedRosenFileData オブジェクトに対して、編集動作を実行してください。
	 */
	virtual int execute( CDedRosenFileData* pCDedRosenFileData ) ;
	
	/**
	 *	「 this->execute() で行った編集操作を取り消す
	 *	（ this->execute() で編集動作を行った直後の CDedRosenFileData 
	 *	オブジェクトを、 this->execute() を行う直前の状態に
	 *	する）」ための編集コマンドオブジェクトを生成します。
	 *
	 *	このメンバ関数が返したオブジェクトを使って execute() を
	 *	呼び出すことにより、 this->execute() 直後の状態の CentDedRosen
	 *	 オブジェクトを、 this->execute() 直前の状態に戻すことができます。
	 * @return
	 *	execute() で行った編集操作を取り消し、
	 *	 CDedRosenFileData オブジェクトを execute() を行う直前の状態に
	 *	するためのコマンドオブジェクトを生成します。
	 *	<H4>
	 *	【オーバライド】
	 *	</H4>
	 *	execute() で実行した編集内容を元に戻すようなオブジェクトを
	 *	生成して返してください。
	 */
	virtual Ou<CRfEditCmd> createUndoCmd()  ;
	
	///@}
public:
	// ********************************
	///@name CRfEditCmd_DedRosenFileDataProp-属性
	// ********************************
	///@{
	tstring	getRosenName()const{	return m_strRosenName ;};
	CRfEditCmd_DedRosenFileDataProp& 
		setRosenName( const tstring& value )
	{
		m_strRosenName = value ; return *this ; 
	};
	CdDedJikoku	getKitenJikoku()const{	return m_jikokuKitenJikoku ;};
	CRfEditCmd_DedRosenFileDataProp& 
		setKitenJikoku( const CdDedJikoku& value )
	{
		m_jikokuKitenJikoku = value ; return *this ;
	};

	int	getDiagramDgrYZahyouKyoriDefault()const
	{	return m_iDiagramDgrYZahyouKyoriDefault ;};
	CRfEditCmd_DedRosenFileDataProp&
		setDiagramDgrYZahyouKyoriDefault( int value )
	{	m_iDiagramDgrYZahyouKyoriDefault = value ; return *this ;}

	int getEnableOperation()const
	{
		return m_iEnableOperation;
	};
	CRfEditCmd_DedRosenFileDataProp&
		setEnableOperation(int value)
	{
		m_iEnableOperation = value; return *this;
	}

	tstring	geKudariDiaAlias()const { return m_strKudariDiaAlias; };
	CRfEditCmd_DedRosenFileDataProp&
		setKudariDiaAlias(const tstring& value)
	{
		m_strKudariDiaAlias = value; return *this;
	};

	tstring	getNoboriDiaAlias()const { return m_strNoboriDiaAlias; };
	CRfEditCmd_DedRosenFileDataProp&
		setNoboriDiaAlias(const tstring& value)
	{
		m_strNoboriDiaAlias = value; return *this;
	};

	bool getOperationNumberReverse()const
	{
		return m_bOperationNumberReverse;
	};
	CRfEditCmd_DedRosenFileDataProp&
		setOperationNumberReverse(bool value)
	{
		m_bOperationNumberReverse = value; return *this;
	}

	bool getOperationCrossKitenJikoku()const
	{
		return m_bOperationCrossKitenJikoku;
	};
	CRfEditCmd_DedRosenFileDataProp&
		setOperationCrossKitenJikoku(bool value)
	{
		m_bOperationCrossKitenJikoku = value; return *this;
	}

	int getKijunDiaIndex()const
	{
		return m_iKijunDiaIndex;
	};
	CRfEditCmd_DedRosenFileDataProp&
		setKijunDiaIndex(int value)
	{
		m_iKijunDiaIndex = value; return *this;
	}

	bool getDisableHiddenSyubetsu()const
	{
		return m_bDisableHiddenSyubetsu;
	};
	CRfEditCmd_DedRosenFileDataProp&
		setDisableHiddenSyubetsu(bool value)
	{
		m_bDisableHiddenSyubetsu = value; return *this;
	}
	
	
	CdDedDispProp	getCdDedDispProp()const{ return m_CdDedDispProp ;};
	CRfEditCmd_DedRosenFileDataProp& 
		setCdDedDispProp( const CdDedDispProp& value )
	{
		m_CdDedDispProp = value ;return *this ; 
	};
	///@}
};

} } // namespace EditCmd namespace DedRosenFileData

#endif /*CRfEditCmd_DedRosenFileDataProp_h*/
