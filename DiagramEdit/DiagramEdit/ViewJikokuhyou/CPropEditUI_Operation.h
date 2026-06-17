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
// ****************************************************************
//	$Id: CPropEditUI_Operation.h$
// ****************************************************************

/** @file */
#ifndef  ViewJikokuhyou_CPropEditUI_Operation_h
#define  ViewJikokuhyou_CPropEditUI_Operation_h
#pragma once

#include <string>
#include "..\entDed\CentDedRessyaCont.h"
#include "NsMu\Mu.h"
#include "NsPropEditUi2\CPropEditUi2.h"
//#include "Str\tstring.h"
#include <tchar.h>

namespace ViewJikokuhyou{
	using namespace entDed;
	using namespace OuLib::NsMu ;
	using namespace OuLib::NsPropEditUi2 ;
	using namespace std ;
	


// ********************************
//	UIDATA_Operation
// ********************************
/**
	CPropEditUI_Operation で編集するプロパティの UIDATA 構造体です。
*/
struct Operation
{
	/**
	作業種類
		0:	入換
		1:	増結
		2:	解結
		3:	入区(後作業)・出区(前作業)
		4:	路線外始発(前作業)・路線外終着(後作業)
		5:	次列車接続(後作業)・前列車接続(前作業)
		6:  運用番号変更
		7:	(作業を追加・作業が一つもない場合、これを入れておく)
	*/
	int iOperation;

	/**
		設定データ(int)1
		入換:番線Index
		増結:増結位置
		解結:解結位置種類
		路線外発着:発着駅Index
		次列車接続:次列車接続タイプ(Ver2.05から)
	*/
	int iComboData1;

	/**
		設定データ(文字列)1
		入換:入換発時刻
		増結:増結時刻(入力省略可・自動補完)
		解結:解結位置Index
		出区:出区時刻(入力省略可・自動補完)
		入区:入区時刻(入力省略可・自動補完)
		路線外始発:始発駅発時刻
		路線外終着:当駅発時刻(入力省略可・自動補完)
		前列車接続:起点時刻(省略可)
		次列車接続:終点時刻(省略可)
	*/
	tstring strEditData1;

	/**
		設定データ(文字列)2
		入換:入換着時刻(省略可)
		解結:解結時刻(入力省略可・自動補完)
		路線外始発:当駅着時刻(入力省略可・自動補完)
		路線外終着:終着駅着時刻(省略可)

	*/
	tstring strEditData2;

	/**
		設定データ(bool)1
		入換:入換着/発時刻を、当駅の着/発時刻にする
		前列車接続:解結表示省略(Ver2.05削除)
		次列車接続:増結表示省略(Ver2.05削除)
		運用番号変更:運用番号順反転(Ver2.06.05～)
	*/
	bool bCheckData1;

	/**
		設定データ(文字列配列)
		出区・路線外始発・前列車接続・運用番号変更:運用番号
	*/
	vector<tstring> strOperationNumber;

	/**
		設定データ(文字列)3
		出区・路線外始発・入区・路線外終着:入出区連携コード

	*/
	tstring strInOutLinkCode;

	/**
		UIData内における、当該作業の階層位置を表します。
		最上層(CentDedEkijikoku直下のCentDedOperationxxxCont)は
		要素数1で、Cont内のIndexが入ります
		その中に増解結がある場合、その増解結作業傘下のOperationContは
		まず1要素目に親作業(増解結)のIndexが入り、その次の要素で、
		増解結作業傘下のOperationContにおけるIndexが入ります。
		そのCont内にさらに増解結がある場合も、同様です
		(例)
		Ekijikoku
		┗入換A、解結A、入換B、入区A
				　┗入換C、増結A、路線外終着A
			　  出区A、入換D┛

		┃		0		入換A
		┣┓	1		解結A
		┃┃	1,0		入換C
		┃┃┃	1,1,0	出区A
		┃┃┃	1,1,1	入換D
		┃┣┛	1,1		増結A
		┃┃	1,2		路線外終着A
		┃		2		入換B
		┃		3		入区A
		ダイアログのリストに表示する場合はこの順番になります。
		リストに表示する文字列の頭にも、この要素に基づく文字列が付与されます
		(1.1.1 入換～　のように表示)
	*/
	vector<int> iLevel;

	Operation()
		: iOperation(0)	
		, iComboData1(0)
		, strEditData1(_T(""))
		, strEditData2(_T(""))
		, bCheckData1(false)
		,strOperationNumber(vector<tstring>())
		, strInOutLinkCode(_T(""))
	{
	}
};

struct UIDATA_Operation
{
	/**
		前作業
		この配列には、時系列順で作業の情報が格納されます。
	*/
	vector <Operation> sOperationA;

	/**
		後作業
	*/
	vector <Operation> sOperationB;

	//Ver2.05削除
	//bool bSyubetsuChange;

	/**
		現在のリストクリック位置
		追加の場合は、追加された作業位置
		削除の場合は、削除された作業があった位置
	*/
	int iListSelected;

	/**
		前作業と後作業のどちらのリストをクリックしたか
		true:後作業
		false:前作業
	*/
	bool bSelectedAfter;

	/**
		Uiでどのような作業を行ったか
		0:詳細変更(時刻の書換、番線の変更etc)
		1:選択変更(リストをクリック)
		2:追加
		3:削除

	*/
	int iUiOperation;
	
	/**
		着時刻
	*/
	tstring strChakujikoku ;
	
	/**
	 strChakujikoku の編集の有効・無効。
	 true なら有効です 
	*/
	//bool bChakujikokuIsEnable ;

	/**
		発時刻
	*/
	tstring strHatsujikoku ;
	
	/**
	 strHatsujikoku の編集の有効・無効。
	 true なら有効です 
	*/
	//bool bHatsujikokuIsEnable ;


	UIDATA_Operation() 
		: sOperationA(vector<Operation>())
		, sOperationB(vector<Operation>())
		, iListSelected(INT_MIN)
		, bSelectedAfter(false)
		, iUiOperation(1)
		, strChakujikoku(tstring())
		, strHatsujikoku(tstring())
	{
	}
};
		

/**
@brief
  列車の駅時刻のプロパティ編集を行うクラスです。

  このクラスは抽象クラスです。
  このクラスは、使用するUI環境(例：Windows,MFC)には依存しません。
　クラスユーザーは、このクラスを継承して、
 『オーバーライトの必要なメソッド2-UIに依存する処理』の仮想関数に、
 UI環境に依存した処理を実装してください。
*/
class CPropEditUI_Operation : public CPropEditUi2<UIDATA_Operation>
{

public:
	// ********************************
	///@name エラーメッセージ
	// ********************************
	///@{
	///// 着時刻の入力が正しくありません
	//static const TCHAR* const ERRMSG_INVALID_CHAKUJIKOKU ;

	///// 発時刻の入力が正しくありません
	//static const TCHAR* const ERRMSG_INVALID_HATSUJIKOKU ;

	///// 入換番線の指定が正しくありません
	//static const TCHAR* const ERRMSG_INVALID_SHUNTTRACK;

	///// 入換発時刻の入力が正しくありません
	//static const TCHAR* const ERRMSG_INVALID_OPERATIONHATSUJIKOKU;

	///// 入換着時刻の入力が正しくありません
	//static const TCHAR* const ERRMSG_INVALID_OPERATIONCHAKUJIKOKU;

	///// 路線外発着駅時刻の入力が正しくありません
	//static const TCHAR* const ERRMSG_INVALID_OUTERHATSUCHAKUJIKOKU;


	/// 入換発時刻の入力が正しくありません
	static const TCHAR* const ERRMSG_INVALID_SHUNTHATSUJIKOKU;

	/// 入換着時刻の入力が正しくありません
	static const TCHAR* const ERRMSG_INVALID_SHUNTCHAKUJIKOKU;

	/// 入換発時刻が規定範囲外です
	//static const TCHAR* const ERRMSG_OUTOFRANGE_SHUNTHATSUJIKOKU;

	/// 入換着時刻が規定範囲外です
	//static const TCHAR* const ERRMSG_OUTOFRANGE_SHUNTCHAKUJIKOKU;

	/// 増結時刻の入力が正しくありません
	static const TCHAR* const ERRMSG_INVALID_CONNECTJIKOKU;

	/// 増結時刻が規定範囲外です
	//static const TCHAR* const ERRMSG_OUTOFRANGE_CONNECTJIKOKU;

	/// 解結時刻の入力が正しくありません
	static const TCHAR* const ERRMSG_INVALID_RELEASEJIKOKU;

	/// 解結時刻が規定範囲外です
	//static const TCHAR* const ERRMSG_OUTOFRANGE_RELEASEJIKOKU;

	/// 解結編成数の入力が正しくありません
	static const TCHAR* const ERRMSG_INVALID_RELEASEINDEX;

	/// 解結編成数は1以上10以下の整数を入力してください
	static const TCHAR* const ERRMSG_OUTOFRANGE_RELEASEINDEX;

	/// 出区時刻の入力が正しくありません
	static const TCHAR* const ERRMSG_INVALID_OUTJIKOKU;

	/// 出区時刻が規定範囲外です
	//static const TCHAR* const ERRMSG_OUTOFRANGE_OUTJIKOKU;

	/// 入区時刻の入力が正しくありません
	static const TCHAR* const ERRMSG_INVALID_INJIKOKU;

	/// 入区時刻が規定範囲外です
	//static const TCHAR* const ERRMSG_OUTOFRANGE_INJIKOKU;

	/// 路線外始発駅発時刻の入力が正しくありません
	static const TCHAR* const ERRMSG_INVALID_OUTERHATSUJIKOKU;

	/// 当駅着時刻の入力が正しくありません
	static const TCHAR* const ERRMSG_INVALID_CHAKUJIKOKU;

	/// 当駅着時刻が規定範囲外です
	//static const TCHAR* const ERRMSG_OUTOFRANGE_CHAKUJIKOKU;

	/// 路線外始発駅発時刻を入力してください
	static const TCHAR* const ERRMSG_EMPTY_OUTERHATSUJIKOKU;

	/// 当駅発時刻の入力が正しくありません
	static const TCHAR* const ERRMSG_INVALID_HATSUJIKOKU;

	/// 路線外終着駅着時刻の入力が正しくありません
	static const TCHAR* const ERRMSG_INVALID_OUTERCHAKUJIKOKU;

	/// 当駅発時刻が規定範囲外です
	//static const TCHAR* const ERRMSG_OUTOFRANGE_HATSUJIKOKU;

	/// 路線外終着駅着時刻を入力してください
	static const TCHAR* const ERRMSG_EMPTY_OUTERCHAKUJIKOKU;

	/// 起点時刻の入力が正しくありません
	static const TCHAR* const ERRMSG_INVALID_ORIGINJIKOKU;

	/// 終点時刻の入力が正しくありません
	static const TCHAR* const ERRMSG_INVALID_TERMINALJIKOKU;

	/// 運用番号にカンマ(,)は使用できません
	static const TCHAR* const ERRMSG_UNUSABLE_COMMA;

	/// 路線外始発駅発時刻を入力してください
	static const TCHAR* const ERRMSG_EMPTY_OPERATIONNUMBER;

	/// 入出区連携コードにカンマ(,)は使用できません
	static const TCHAR* const ERRMSG_UNUSABLE_COMMA_INOUTLINKCODE;

	/// 入出区連携コードにスラッシュ(/)は使用できません
	static const TCHAR* const ERRMSG_UNUSABLE_SLASH;

	/// 入出区連携コードにドル記号($)は使用できません
	static const TCHAR* const ERRMSG_UNUSABLE_DOLLAR;
	///@}

private:
	// ********************************
	///@name 関連
	// ********************************
	///@{
	/**
	　Target(編集対象のプロパティを保持する変数へのポインタ)。 
	　コンストラクタで決まります。

	 　列車を格納したコンテナです。
	*/
	Mu<CentDedRessya*>* m_pTarget ;

private:
	// ********************************
	///@name 属性
	// ********************************
	///@{
	/**
		編集対象の駅時刻の着駅Orderです。
		コンストラクタで決まります。
	*/
	int m_iChakuEkiOrder ;
	/**
		編集対象の駅時刻の発駅Orderです。
		コンストラクタで決まります。
	*/
	int m_iHatsuEkiOrder;

	bool m_bFocusAfter;

	int m_iFocusIndex;

	bool m_bFocusChild;

	int m_iStandardShuntTrackIndex[2];

	vector<vector<int>> m_iStandardOuterTerminalJikan;
	///@}


protected:
	// ================================
	/** @name オーバーライトの必要なメソッド1-Targetに依存する処理
		Target と UiData との間のデータ交換のためのメソッドです。
		このグループのメソッドは、 Ui の環境には依存しません。
	*/
	// ================================
	///@{
	
	/**
		UiData を、新規Targetのプロパティの編集のために
		初期化します。
		
		m_bNewItem が true の場合にだけ、 CPropEditUi2::StartEdit() 
		から呼び出されます。
	
		通常、 UiData は、UIDATAのデフォルトコンストラクタで初期化されます。
		クラスユーザーは、UiData に、デフォルトコンストラクタと異なる
		初期値を与えたい場合は、このメンバ関数をオーバーライドしてください。

	@param pUiData [out]
		UiData のオブジェクト。
	*/
	//virtual void InitUiData( UIDATA* pUiData ) ;

	/**
		UiDataFromTargetの補助
		前作業の読み込みを行います
		pCentDedBeforeOperationCont
			読み込み対象となるBeforeContです。
		iLevel
			呼び出し元の階層です。
			ここで読み込まれた作業のiLevelには、引数iLevel+pCentDedBeforeOperationCont内のIndexが付与されます
		return vector<Operation>
			pCentDedBeforeOperationContから読み込んだOperation配列を返します。
			戻り先では、受け取ったOperation配列を、増解結の前後に挿入します。
	*/
	virtual vector<Operation> BeforeOperationFromTarget(
		const CentDedBeforeOperationCont* pCentDedBeforeOperationCont,
		const vector<int> iLevel);

	/**
		UiDataFromTargetの補助
		後作業の読み込みを行います
		pCentDedAfterOperationCont
			読み込み対象となるAfterContです。
		iLevel
			呼び出し元の階層です。
			ここで読み込まれた作業のiLevelには、引数iLevel+pCentDedAfterOperationCont内のIndexが付与されます
		return vector<Operation>
			pCentDedAfterOperationContから読み込んだOperation配列を返します。
			戻り先では、受け取ったOperation配列を、増解結の前後に挿入します。
	*/
	virtual vector<Operation> AfterOperationFromTarget(
		const CentDedAfterOperationCont* pCentDedAfterOperationCont,
		const vector<int> iLevel);

	/**
		UiData に、Targetの属性を反映します。
		
		m_bNewItem が false の場合にだけ、 CPropEditUi2::StartEdit() 
		から呼び出されます。
		
		クラスユーザーは、この関数をオーバーライドして、
		Target の内容をUiData に反映する処理を実装してください。

	@param pUiData [out]
		UiData のオブジェクト。
	*/
	virtual void UiDataFromTarget( UIDATA* pUiData ) ; 

	/**
		UiData の内容を正規化します。
		
		CPropEditUi2::StartEdit(),CPropEditUi2::OnUiChanged(),
		CPropEditUi2::OnUiDataChanged(),CPropEditUi2::EndEdit()
		から呼び出されます。
		
		クラスユーザーは、この関数をオーバーライドして、
		UiDataのメンバの内容を正規化する処理を実装してください。
		
		この関数では、入力内容に対するエラーメッセージの表示はお勧めしません。
		エラーメッセージの表示は、CheckUiData() で行ってください。
	
	正規化の例
	 --------------------------------
	-	テキストボックスに全角で入力されたテキストを、半角に変換する。
	-	あるチェックボックスがONのときにはテキストボックスを有効、
		OFFの時には無効(グレー)にする

	@param pUiData [in,out]
		UiData のオブジェクト。
	@param pUiDataPrev [in]
		前回の AdjustUiData() 終了後の UiData のコピーです。
		この関数では、 pUiDataPrev と pUiData の値を比較することにより、
		「今回ユーザーによって変更されたUiDataメンバー」を判断することが
		できます。
		この関数が CPropEditUi2::StartEdit() から呼び出された場合は、
		この引数はNULLとなります。
	@param bStartEdit [in]
		- true: この関数は、 CPropEditUi2::StartEdit() から呼び出されています。
			この場合は、pUiDataPrev は無効です。
			関数では、 UiData のすべてのデータの正規化を行ってください。
		- false: この関数は、 CPropEditUi2::StartEdit() 以外から
			呼び出されています。
			pUiData と pUiDataPrev を比較することにより
			今回変化した UiData メンバー変数を判断することが出来ます。
			この関数では、UiData のうち、今回変化したデータメンバーだけを
			正規化してください。
	
	
	この関数のコーディングの例
	 --------------------------------
	@code
	virtual void AdjustUiData( 
		UIDATA* pUiData , 
		const UIDATA* pUiDataPrev , 
		bool bStartEdit )
	{
		if ( bStartEdit || pUiDataPrev->メンバー名 != pUiData->メンバー名)
		{
			// pUiData->メンバー名 の正規化を行うコード。
		}
	}
	@endcode
	*/
	virtual void AdjustUiData( 
		UIDATA* pUiData , 
		const UIDATA* pUiDataPrev , 
		bool bStartEdit );

	/**
		CheckUiDataの補助関数です。
		UiDataのひと塊の前作業について、
		時刻入力に不正がないか、作業の時刻が指定の範囲に収まっているかチェックします。
		sOperationB[in]
			チェック対象となる前作業です
		iLevelSearch[in]
			チェック対象となる前作業群を指定するために用います。
		iListErrorPos[out]
			エラーが発生した場合、エラーが発生した作業のindexを代入します。
		iLevelErrorPos[out]
			エラーが発生した場合、エラーが発生した作業のiLevelを代入します。
		return エラーが発生した場合、負の数のエラーコードを返します
	*/
	virtual int CheckBeforeOperation(
		const vector<Operation>& sOperationB,
		const vector<int> iLevelSearch,
		int& iListErrorPos,
		vector<int>& iLevelErrorPos);

	/**
		CheckUiDataの補助関数です。
		UiDataのひと塊の前作業について、
		時刻入力に不正がないか、作業の時刻が指定の範囲に収まっているかチェックします。
		sOperationB[in]
			チェック対象となる前作業です
		iLevelSearch[in]
			チェック対象となる前作業群を指定するために用います。
		iListErrorPos[out]
			エラーが発生した場合、エラーが発生した作業のindexを代入します。
		iLevelErrorPos[out]
			エラーが発生した場合、エラーが発生した作業のiLevelを代入します。
		return エラーが発生した場合、負の数のエラーコードを返します
	*/
	virtual int CheckAfterOperation(
		const vector<Operation>& sOperationA,
		const vector<int> iLevelSearch,
		int& iListErrorPos,
		vector<int>& iLevelErrorPos);
	/**
		UiData の内容を検証し、問題があればエラーメッセージを表示します。
		
		CPropEditUi2::EndEdit()
		から呼び出されます。
		
		クラスユーザーは、この関数をオーバーライドして、
		UiDataのメンバの内容を検証する処理を実装してください。
		入力内容に問題があれば、ShowError()でエラーメッセージを表示し、
		SetFocus2()で、フォーカスを問題のあるUIに設定してください。
		
		新規オブジェクトに対するプロパティの編集の場合は、
		UiDataのすべてのメンバーを検証する必要があります。
		また、必須のメンバーがブランクである場合は、
		エラーメッセージを表示するべきです。

		既存オブジェクトに対するプロパティ編集の場合は、
		ユーザーによって値の変更されたメンバーのみを検証してください。
		pUiData と pUiDataStartEdit との間で違いのあるデータメンバーが、
		ユーザーによって値の変更されたメンバーです。
		
	@param bNewItem
		-true: 新規オブジェクトに対する、プロパティの編集
		-false: 既存オブジェクトに対する、プロパティの編集
	@param pUiData [in]
		UiData のオブジェクト。
	@param pUiDataStartEdit [in]
		StartEdit()終了後の UiData のコピーです。
		この関数では、 pUiDataStartEdit と pUiData の値を比較することにより、
		「ユーザーによって変更されたUiDataメンバー」を判断することが
		できます。
	@return
		成功したら0以上、エラーなら負の数です。
		0以外を返した場合、戻り値は、CPropEditUi2::EndEdit() の
		戻り値となります。
		
	この関数のコーディングの例
	 --------------------------------
	@code
	virtual int CheckUiData( 
		bool bNewItem , 
		const UIDATA* pUiData , 
		const UIDATA* pUiDataStartEdit ) 
	{
		int iRv = 0 ; 
		
		if ( bNewItem || pUiDataStartEdit->メンバー名 != pUiData->メンバー名)
		{
			//	pUiData->メンバー名 の検証を行うコード。
			
			if ( pUiData->メンバー名 にエラーがあり )
			{
				ShowError( エラーの理由を示す文字列 );
				SetFocus2( offsetof( UIDATA , メンバー名 ) );
				iRv = -1 ;
			}
		}
		return iRv ;
	}
	@endcode
	*/
	virtual int CheckUiData( 
		bool bNewItem , 
		const UIDATA* pUiData , 
		const UIDATA* pUiDataStartEdit ) ;

	/**
		UiDataToTargetの補助
		前作業の時刻補完を行います
		sOperationB
			補完を行うデータです。
		iLevelTarget
			呼び出し元の階層です。
			このiLevelの子作業に相当する作業にのみ、補完を行います
		pSourceJikoku
			空時刻を補完するための基準時刻です、必要に応じ書換も行います
		bSupplyFromFront
			時刻のチェックを、作業の前後どちらから行うかを指定します。
		bIsTeisya
			駅扱いが停車か否か。駅扱いが停車の場合のみ、路線外発着の当駅着・発時刻の補完を行います。
	*/
	virtual void BeforeOperationComplement(
		vector<Operation>& sOperationB,
		const vector<int> iLevelTarget,
		CdDedJikoku& pSourceJikoku,
		const bool bSupplyFromFront,
		const bool bIsTeisya);

	/**
		UiDataToTargetの補助
		前作業の反映を行います
		pCentDedBeforeOperationCont
			反映先となるBeforeContです。
		sOperationB
			反映元となる作業データです。
	*/
	virtual void BeforeOperationToTarget(
		CentDedBeforeOperationCont* pCentDedBeforeOperationCont,
		const vector<Operation> sOperationB);

	/**
		UiDataToTargetの補助
		後作業の時刻補完を行います
		sOperationA
			補完を行うデータです。
		iLevelTarget
			呼び出し元の階層です。
			このiLevelの子作業に相当する作業にのみ、補完を行います
		pSourceJikoku
			空時刻を補完するための基準時刻です、必要に応じ書換も行います
		bSupplyFromFront
			時刻のチェックを、作業の前後どちらから行うかを指定します。
		bIsTeisya
			駅扱いが停車か否か。駅扱いが停車の場合のみ、路線外発着の当駅着・発時刻の補完を行います。
	*/
	virtual void AfterOperationComplement(
		vector<Operation>& sOperationA,
		const vector<int> iLevelTarget,
		CdDedJikoku& pSourceJikoku,
		const bool bSupplyFromFront,
		const bool bIsTeisya);

	/**
		UiDataToTargetの補助
		後作業の反映を行います
		pCentDedAfterOperationCont
			反映対象となるAfterContです。
		sOperationA
			反映元となる作業データです。
	*/
	virtual void AfterOperationToTarget(
		CentDedAfterOperationCont* pCentDedAfterOperationCont,
		const vector<Operation> sOperationA);
	/**
		UiData の内容を、Targetに反映します。
		
		CPropEditUi2::EndEdit()
		から呼び出されます。
		
		クラスユーザーは、この関数をオーバーライドして、
		UiDataのメンバの内容を、Target のプロパティに反映する処理を
		実装してください。
		
		新規オブジェクトに対するプロパティの編集の場合は、
		UiDataのすべてのメンバーを、Targetに反映する必要があります。

		既存オブジェクトに対するプロパティ編集の場合は、
		ユーザーによって値の変更されたメンバーのみを
		Targetに反映してください。
		pUiData と pUiDataStartEdit との間で違いのあるデータメンバーが、
		ユーザーによって値の変更されたメンバーです。
		
		CPropEditUi2 は、 CheckUiData() が正常終了した後にだけ
		UiDataToTarget() を呼び出します。
		従いまして、この関数では、CheckUiData() でやっているような
		値の検証を行う必要はありません。
		
	@param bNewItem [in]
		-true: 新規オブジェクトに対する、プロパティの編集
		-false: 既存オブジェクトに対する、プロパティの編集
	@param pUiData [in]
		UiData のオブジェクト。
	@param pUiDataStartEdit [in]
		StartEdit()終了後の UiData のコピーです。
		この関数では、 pUiDataStartEdit と pUiData の値を比較することにより、
		「ユーザーによって変更されたUiDataメンバー」を判断することが
		できます。
	@return
		成功したら0以上、エラーなら負の数です。
		0以外を返した場合、戻り値は、CPropEditUi2::EndEdit() の
		戻り値となります。
		
		
	この関数のコーディングの例
	 --------------------------------
	@code
	virtual int UiDataToTarget( 
		bool bNewItem , 
		const UIDATA* pUiData , 
		const UIDATA* pUiDataStartEdit ) 
	{
		int iRv = 0 ; 
		
		if ( bNewItem || pUiDataStartEdit->メンバー名 != pUiData->メンバー名)
		{
			//	pUiData->メンバー名 を、Target に反映するコード
		}
		return iRv ;
	}
	@endcode
	*/
	virtual int UiDataToTarget( 
		bool bNewItem , 
		const UIDATA* pUiData , 
		const UIDATA* pUiDataStartEdit ) ;
	///@}
protected:
	// ================================
	/** @name オーバーライトの必要なメソッド2-UIに依存する処理
		UiData と Ui との間のデータ交換のためのメソッドです。
		このグループのメソッドは、 Ui の環境(Windows,MFCなど)
		に依存する処理だけを実装します。
	*/
	// ================================
	///@{
	/**
		UiDataの内容をUiに反映します。
		
		CPropEditUi2::StartEdit(),CPropEditUi2::OnUiChanged(),
		CPropEditUi2::OnUiDataChanged(),CPropEditUi2::EndEdit()
		から呼び出されます。
		
		クラスユーザーは、この関数をオーバーライドして、
		UiDataのメンバの内容をUiに表示する処理を実装してください。
	@param pUiData [in]
		UiData のオブジェクト。
	*/
	virtual void UiDataToUi( const UIDATA* pUiData )=0 ;
	
	
	/**
		Uiの入力内容をUiDataに反映します。
		
		CPropEditUi2::OnUiChanged(),
		CPropEditUi2::OnUiDataChanged(),CPropEditUi2::EndEdit()
		から呼び出されます。
		
		クラスユーザーは、この関数をオーバーライドして、
		Ui への変更内容をUiData に反映する処理を実装してください。
	@param pUiData [out]
		UiData のオブジェクト。
	*/
	virtual void UiDataFromUi( UIDATA* pUiData ) =0 ;
	
	/**
		画面上にエラーメッセージを表示します。

		クラスユーザーは、この関数をオーバーライドして、
		エラーメッセージを表示する処理を実装してください。
		
		MFCアプリケーションでは、通常は、メッセージボックスを表示します。
	@param strErrorReason [in]
		エラーの内容を示す文字列
	@param strInfo [in]
        エラーの補助情報を示す文字列。不要であれば、空文字列を
        指定してください。
	*/
	virtual void ShowError( 
		const tstring& strErrorReason ,
		const tstring& strInfo = _T("") ) =0 ;
	
	/**
		Ui 上の特定のコントロールに、フォーカスを設定します。

		クラスユーザーは、この関数をオーバーライドして、
		指定されたコントロールにフォーカスを設定する処理を実装してください。
		
	@param iOffsetofUiDataMember [in]
		フォーカスを設定する編集項目を指定してください。
		UiData内の対象となるデータメンバの、構造体の先頭アドレスからの
		オフセットを指定してください。

	例:フォーカスを、UiDataのメンバ strNumber を入力するコントロールに設定
		する場合は、以下のようにしてください。
	@code
		SetFocus2( offsetof(UIDATA,strNumber ) ) ;
	@endcode
	*/
	virtual void SetFocus(int iOffsetofUiDataMember) = 0;
	//virtual void SetFocus2( int iOffsetofUiDataMember,
	//	int iListSelect = -1,
	//	bool bSelectedAfter = false,
	//	int iOperation = 0) =0 ;
	///@}

public:
	// ********************************
	//	コンストラクタ
	// ********************************
	/**
	@param bNewItem [in]
		編集対象を指定してください。
		- true: 新規オブジェクトに対する、プロパティの編集
		- false: 既存オブジェクトに対する、プロパティの編集
	@param pTarget [in,out]
	 編集対象。コンストラクタで決まります。
	 列車を格納したコンテナです。
	@param pbModifyHatsujikoku [in,out]
	 時刻の繰上げ・繰り下げのON/OFFを保持する変数へのポインタ。
	@param iEkiOrder [in]
		編集対象の駅時刻の駅Orderです。
	*/
	CPropEditUI_Operation( 
		bool bNewItem , 
		Mu<CentDedRessya*>* pTarget , 
		int iChakuEkiOrder,
		int iHatsuEkiOrder,
		bool bFocusAfter,
		int iFocusIndex,
		bool bFocusChild,
		int iStandardShuntTrackIndex[],
		vector<vector<int>> iStandardOuterTerminalJikan) ;

};

} //namespace ViewJikokuhyou

#endif /*ViewJikokuhyou_CPropEditUI_Operation_h*/
