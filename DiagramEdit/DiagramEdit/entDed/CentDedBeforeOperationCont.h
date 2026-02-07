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
//$Id: CentDedBeforeOperationCont.h  $
/** @file */
#ifndef  entDed_CentDedBeforeOperationCont_h
#define  entDed_CentDedBeforeOperationCont_h

#include "NsMu\CMuiCopiedParent.h"
//#include "CentDedBeforeOperation.h"
//#include "CentDedAfterOperation.h"

namespace entDed{

//	前方参照宣言
//class CentDedRessya ;
class CentDedEkiJikoku;
class CentDedBeforeOperation;
class CentDedAfterOperation;
	

/**
@brief
  『列車番線』オブジェクトのコンテナです。


*/
class CentDedBeforeOperationCont : public CMuiCopiedParent< CentDedBeforeOperation >
{
public:
	typedef  public CMuiCopiedParent< CentDedBeforeOperation > super ;
	
public:
	// ********************************
	//	コンストラクタ
	// ********************************
	/**
		要素数0で初期化します。
	*/
	CentDedBeforeOperationCont() ;

	/**
	△operator=: this が路線の一部である場合は、駅時刻の数は変更しません
	*/
	CentDedBeforeOperationCont& operator=( const CentDedBeforeOperationCont& value ) ;

public:
	// ********************************
	///@name Mui
	// ********************************
	///@{
	/**
	 	コンテナ内の、インデクスで指定された場所に、
	 	要素を追加します。

		△駅時刻の追加(insert)：　列車が路線の一部である場合はエラー。

	 @param element [in]
	 	要素を指定してください。
	 @param iIndex [in]
	 	０から始まるインデクスを指定してください。
	 	範囲は０以上 size() 以下です。
	 	０は、先頭・size()なら末尾への追加になります。
		但し、INT_MAX は、末尾を指定したものとみなします。
	 @return
	 	0以上は成功、負の数はエラーです
		-	-11 ;	//	列車が路線の一部である場合、駅時刻の追加はできません。
	*/
	virtual int insert( const CentDedBeforeOperation& element , int iIndex = INT_MAX );
	
	/**
	 	コンテナ内の、インデクスで指定された場所の
	 	要素を削除します。

		△駅時刻の削除(erase):　列車が路線の一部である場合はエラー。

	 @param iIndex [in]
	 	０から始まるインデクスを指定してください。
	 	範囲は０以上 size() 未満です。
	 	但し、INT_MAX は、末尾を指定したものとみなします。
	 @param iSize [in]
	 	削除する要素の数を指定してください。
	 	但し、INT_MAX は、 iIndex から末尾までを表します。
	 @attention
		iIndex と iSize の両方を INT_MAX にすることはできません。
	 @return
	 	0以上は成功、負の数はエラーです
		-	-11 ;	//	列車が路線の一部である場合、駅時刻の削除はできません。
	*/
	virtual int erase( int iIndex  , int iSize = 1 ) ;
	
	/**
	 	コンテナ内の、インデクスで指定された場所に、
	 	要素を上書きします。

	@param element [in]
	 	要素を指定してください。
	 @param iIndex [in]
	 	０から始まるインデクスを指定してください。
	 	範囲は０以上 size() 未満です。
		但し、INT_MAX は、末尾を指定したものとみなします。
	 @return
	 	0以上は成功、負の数はエラーです
		-	-11; //番線指定子が『番線コンテナ』CentDedEkiTrackCont の要素に対応していません
	*/
	virtual int set( const CentDedBeforeOperation& element , int iIndex ) ;
	///@}

 public:
	// ********************************
	///@name CentDedBeforeOperationCont-関連
	// ********************************
	///@{
	/**
	@return
		このコンテナが CentDedEkiJikoku に包含されている場合は、
		CentDedEkiJikoku のアドレス。
		そうでないならNULL。
	*/
	 virtual CentDedEkiJikoku* getEkiJikoku() { return NULL; }
	 /**
	 @return
		 このコンテナが CentDedEkiJikoku に包含されている場合は、
		 CentDedEkiJikoku のアドレス。
		 そうでないならNULL。
	 */
	 virtual const CentDedEkiJikoku* getEkiJikoku()const { return NULL; }

	 /**
	 @return
		 このコンテナが CentDedBeforeOperation に包含されている場合は、
		 CentDedBeforeOperation のアドレス。
		 そうでないならNULL。
	 */
	 virtual CentDedBeforeOperation* getBeforeOperation() { return NULL; }
	 /**
	 @return
		 このコンテナが CentDedBeforeOperationに包含されている場合は、
		 CentDedBeforeOperation のアドレス。
		 そうでないならNULL。
	 */
	 virtual const CentDedBeforeOperation* getBeforeOperation()const { return NULL; }

	 /**
	 @return
		 このコンテナが CentDedAfterOperation に包含されている場合は、
		 CentDedAfterOperation のアドレス。
		 そうでないならNULL。
	 */
	 virtual CentDedAfterOperation* getAfterOperation() { return NULL; }
	 /**
	 @return
		 このコンテナが CentDedAfterOperation に包含されている場合は、
		 CentDedAfterOperation のアドレス。
		 そうでないならNULL。
	 */
	 virtual const CentDedAfterOperation* getAfterOperation()const { return NULL; }
	/**
	@return
		このコンテナが CentDedRessya に包含されている場合は、
		CentDedRessya のアドレス。
		そうでないならNULL。
	*/
	 //virtual CentDedRessya* getRessya(){ return NULL ;}
	/**
	@return
		このコンテナが CentDedRessya に包含されている場合は、
		CentDedRessya のアドレス。
		そうでないならNULL。
	*/
	//virtual const CentDedRessya* getRessya()const{ return NULL ;}

	/**
	@return
		このコンテナが CentDedRosen に包含されている場合は、
		CentDedRosen のアドレス。
		そうでないならNULL。
	*/
	//CentDedRosen* getRosen() ;
	/**
	@return
		このコンテナが CentDedRosen に包含されている場合は、
		CentDedRosen のアドレス。
		そうでないならNULL。
	*/
	//const CentDedRosen* getRosen()const ;
	///@}
public:
	// ********************************
	///@name CentDedBeforeOperationCont-操作
	// ********************************
	///@{

	/**
		set() が可能か否かを判断します。
		このクラスでは、常に0を返します。

	@param element
		要素を指定してください。 
	@param iIndex
		０から始まるインデクスを指定してください。 範囲は０以上 size() 
		未満です。 但し、INT_MAX は、末尾を指定したものとみなします。 
	@return
		-	0以上: set() が可能。
		-	負の数: set()は、この戻り値で失敗します。
	 */
	//virtual int  setable(  const CentDedBeforeOperation& element , int iIndex )const ;

	/**
		element がこのコンテナの子である場合は、インデクスを返します。
	@param element
		要素を指定してください。 
	@return
		element がこのコンテナの子である場合は、インデクスを返します。
		そうでない場合は、 -1 です。
	*/
	virtual int  getIndex( const CentDedBeforeOperation* element )const ;
	/**
		this の属性が制約に反している場合、制約に合うように、属性を
		修正します。


		△駅時刻(CentDedEkiJikoku)の要素数が駅コンテナ(CentDedEkiCont)と異なる場合は、駅時刻を追加・削除します。

		○CentDedEkiJikoku(駅時刻)に、adjust()を委譲します。


	*/
	void adjust() ;

	/**
		このコンテナ内の作業に設定された時刻を、iSecond秒だけ変更します。
	*/
	void modifyOperationJikoku(int iSecond);

	/**
		作業の正規化を行います。
		iTypeにより、作業内容が変わります。
		INT_MIN:作業をすべて削除します
		0:作業に増解結が含まれる場合、それらの正規化を行います。
			また、先端作業(前列車接続etc)が含まれる場合は、削除します。
		-1:作業の先頭が、先端作業(前列車接続etc)であるかを調べ、そうでない場合は、前列車接続を付与します。
			加えて、iType=0の動作も実施します
	*/
	void adjustOperation(int iType);

	/**
		CentDedEkiが変更された結果、番線の順序が変わった場合に呼び出されます。
		コンテナ内作業の列車番線を調整します
		@param iEkiTrack2Map
		駅番線の移動先です。
		idx番線の移動先はiEkiTrack2Map[idx]番線となります。
	*/
	void adjustEkiTrack2(
		const std::vector<int>& iEkiTrack2Map);
	/**
		CentDedEkiが変更された結果、路線外発着駅が変更された場合に呼び出されます。
		コンテナ内作業の始発終着駅作業を調整します
		@param iOuterTerminalEkimeiMap
		路線外発着駅の移動先です。
		idx駅の移動先はiOuterTerminalEkimeiMap[idx]番目となります。
	*/
	void adjustOuterTerminal(
		const std::vector<int>& iOuterTerminalEkimeiMap);

	/**
		クリップボードから駅作業の貼り付けを行うときに、
		入換番線Indexおよび路線外発着駅Indexが、
		貼り付け先の駅に合致しているか確認し、必要なら修正を行います。
		(入換)入換番線がiEkiTrackCount以上の場合、0に変更
		(路線外)iOuterTerminalCountが0の場合は、入出区に作業を変更。
			路線外発着駅IndexがiOuterTerminalCount以上の場合は、0に変更
	*/
	void fixOperation(
		const int iEkiTrackCount,
		const int iOuterTerminalCount);
	/**
		駅の編集で番線を削除する前に、その番線を使用している列車があるかどうかを確認します。
		@param iEkiTrack2Index
			駅番線Index
			この値を入換番線にもつ作業があるかを調べます。
	*/
	int isExistRessyaOfEkiTrack2(int iEkiTrack2Index);

	/**
		駅の編集で路線外発着駅名を削除する前に、
		その路線外発着駅名を使用している列車があるかどうかを確認します。
		@param iOuterTerminalIndex
			路線外発着駅名Index
			この値を路線外始発・終着駅Indexにもつ作業があるかを調べます。
	*/
	int isExistRessyaOfOuterTerminal(int iOuterTerminalIndex);

	///@}
public:
	// ********************************
	///@name CentDedRosen-子オブジェクトの増減の通知
	// ********************************
	///@{
	
	///@}

};

} //namespace entDed


#endif //entDed_CentDedBeforeOperationCont_h
