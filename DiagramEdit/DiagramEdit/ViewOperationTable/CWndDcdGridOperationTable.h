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
//	CWndDcdGridOperationTable.h
//	$Id: CWndDcdGridOperationTable.h $
// ****************************************************************
*/
/** @file */
#ifndef  CWndDcdGridOperationTable_h
#define  CWndDcdGridOperationTable_h

#include "DcdGrid/WndDcdGrid3/WndDcdGrid3.h"

#include "..¥entDed¥CconvCentDed.h"
#include "OperationTableColSpec¥OperationTableColSpec.h"
#include "..¥entDed¥CdDedRessyaProperty.h"
#include "CDcDraw_Extension.h"

namespace ViewOperationTable {

	using namespace OperationTableColSpec ;
	using namespace DcDrawLib::DcdGrid::WndDcdGrid3 ;
// ****************************************************************
//	CWndDcdGridOperationTable
// ****************************************************************

	/**
		OperationTableContentを基に、実際に表示する形式に組み替えます。
		具体的には、次列車接続タイプが"同一列車扱い"の場合に、前後列車をまとめて表示します。
		eRessyahoukou:列車方向です。その行に表示するiCombineCountが一つの場合はその列車の列車方向がそのまま入ります。
			複数の場合は、始発駅と終着駅のIndexの大小関係を見て、列車方向を定めます。
		iCombineCount:その行に表示する列車が、何列車結合したかを示します。
		bIsContinue:箱ダイヤ表示時に、同一列車扱いにもかかわらず別行に表示する場合、下の行のこの値をtrueにしておき、
			描写時にこの値がtrueなら、列車番号欄等に下矢印を表示します。
	*/
	struct OperationTable {
		ERessyahoukou eRessyahoukou;
		int iCombineCount;
		bool bIsContinue;

		OperationTable()
			: eRessyahoukou(ERessyahoukou::Ressyahoukou_Kudari)
			, iCombineCount(1)
			, bIsContinue(false)
		{}

		OperationTable(
			ERessyahoukou eRessyahoukou)
			: eRessyahoukou(eRessyahoukou)
			, iCombineCount(1)
			, bIsContinue(false)
		{}

		OperationTable(
			ERessyahoukou eRessyahoukou,
			bool bIsContinue)
			: eRessyahoukou(eRessyahoukou)
			, iCombineCount(1)
			, bIsContinue(bIsContinue)
		{}

	};

/**
@brief
 【概要】 COperationTableView で用いる、グリッドウインドウです。
 */
class CWndDcdGridOperationTable : public CWndDcdGrid
{
public:
	// ********************************
	//	インナータイプ
	// ********************************
	typedef CWndDcdGrid super ;

private:
	// ********************************
	///@name	包含
	// ********************************
	///@{
	/**
	  親ウインドウへのキー入力を契機に ModalDialog を開く場合、
	 モーダルダイアログの特定のエディットコントロールに、
	 キー入力メッセージ（ WM_KEYDOWN , WM_KEYUP ）を転送します。
	
		このオブジェクトの破棄の責務は、クラスユーザー（『転送元ウインドウ』）
		にあります。
		このオブジェクトは、 this より長く生存しなくてはなりません。
		不要であれば NULL でもかまいません。
		コンストラクタで決まります。
	 */
	//CKeyinputSenderToModalDlg	m_CKeyinputSenderToModalDlg ;
	///@}

	// --------------------------------
	///@name 内部データ
	// --------------------------------
	///@{
	/**
	 通常は false 。
	このビューがアクティブでないときに 
	全更新（ OnUpdate_All() を呼び出す）が必要になってから、
	ビューがアクティブになるまでの間だけ true になります。

	 この変数が true のときは、
	ビューの更新を、次にビューがアクティブ化されるまで
	保留していることを示します。

	 ビューがアクティブでないときに OnUpdate_All() が
	要求されたら、この変数を true にし、
	OnUpdate_All() は実行しません。

	 この値が true のときに、ビューがアクティブ化されたら、
	OnUpdate_All() を実行します。
	 */
	bool m_bUpdate_All_Requested ;

	/**
	初期値はfalse、初回の OnUpdate() が終了したら true になります。
	*/
	bool m_bInitialUpdateComplete;
	///@}
	
protected:
	// --------------------------------
	///@name	下請関数
	// --------------------------------
	///@{


	/**
		全てのX列についての 『列番号-表示内容』の対応表を生成します。
		生成された CdXColSpecCont() から
		CdXColSpec オブジェクトを
		取得することにより、各列毎に必要な表示内容を取得することができます。
	@return 
		全てのX列についての 『列番号-表示内容』の対応表である
		 CdXColSpecCont オブジェクトを返します。
		
	@attention
	 	この関数を OnCreate() ・及びそれ以前に
	 	呼び出したときは、戻り値はNULL状態になります。
	 	呼び出し時期に注意してください。

	@attention
		この対応表は、 CentDedEkiCont に変更が発生
		したら無効になります。このため、CentDedEkiCont  に
		変更の可能性がある状況では、対応表を再作成する必要があります。	
	*/
	CdOperationTableXColSpecCont createXColSpecCont();


	/**
		全てのY列についての 『列番号-表示内容』の対応表を生成します。
		生成された CdYColSpecCont() から
		CdYColSpec オブジェクトを
		取得することにより、各列毎に必要な表示内容を取得することができます。
	@return 
		全てのY列についての 『列番号-表示内容』の対応表である
		 CdYColSpecCont オブジェクトを返します。
		
	@attention
	 	この関数を OnCreate() ・及びそれ以前に
	 	呼び出したときは、戻り値はNULL状態になります。
	 	呼び出し時期に注意してください。

	@attention
		この対応表は、 CentDedEkiCont に変更が発生
		したら無効になります。このため、CentDedEkiCont  に
		変更の可能性がある状況では、対応表を再作成する必要があります。	
	*/
	CdOperationTableYColSpecCont createYColSpecCont();

	/**
	@return 
		フォーカスセルの列の表示内容を返します。
	*/
	CdOperationTableXColSpec getXColSpecOfFocus();

	/**
	@return 
		フォーカスセルの列の表示内容を返します。
	*/
	CdOperationTableYColSpec getYColSpecOfFocus() ;
	
	/**
	DcdGridでの選択内容に応じた、編集コマンドオブジェクト
	(CRfEditCmd_Ressyasyubetsu)を生成します。
	@param eCreateCmd [in]
		生成するコマンドの種類を指定してください。
	@param ppCmd [out] 
		生成したコマンドを返します。
		NULL を指定することもできます。この場合、この関数は
		コマンドを生成せずに、コマンドの生成が可能か否かだけを返します。
	@return
		ppCmdが有効なOuである場合は、コマンドの生成に成功したら trueを返します。
		ppCmd=NULL の場合は、コマンドの生成が可能であればtrueを返します。
		コマンドが生成できない場合は false を返します。
		フォーカスセルや選択セルが列車の位置にない場合は、falseとなります。
	*/
	//bool createCmd( ECreateCmd eCreateCmd , Ou<DedRosenFileData::EditCmd::CRfEditCmd_EkiTrack2>* ppCmd );


	///@}
	// --------------------------------
	///@name OnUpdate の下請関数
	// --------------------------------
	///@{
	/**
	@return
	駅時刻を表示形式に変換するオブジェクトを返します。
	@note static メンバ関数にすることができます。
	*/
	const CdDedJikoku::CConv	getCdDedJikokuConv()const;

	/**
	 グリッドの 指定のY列に、
	『列車』の内容を設定します。
	設定を行ったセルは、更新領域とします。
	@attention
		グリッドの 列車種別番号の X列は更新しません。
		この処理のためには、各Y列に対してこの関数を呼び出した後に、
		グリッド全体に対して
		OnUpdate_setRessyasyubetsuNoXColumn() を
		呼び出す必要があります。
	@param iYColumnNumber [in]
		Y列番号を指定してください。
	@param aCentDedRessya [in]
		『列車』オブジェクトを指定してください。
	*/
	void OnUpdate_setCentDedRessya_To_Column(
		int iYColumnNumber , 
		const CentDedRessya& aShihatsuRessya,
		const CentDedRessya& aShuchakuRessya,
		const OperationTableContent& aSihatsuOperationTableContent,
		const OperationTableContent& aShuchakuOperationTableContent,
		const ERessyahoukou eRessyahoukou) ;

	/**
	 グリッドの 指定のY列に、
	『列車』の内容を設定します。
	設定を行ったセルは、更新領域とします。
	@attention
		グリッドの 列車種別番号の X列は更新しません。
		この処理のためには、各Y列に対してこの関数を呼び出した後に、
		グリッド全体に対して
		OnUpdate_setRessyasyubetsuNoXColumn() を
		呼び出す必要があります。
	@param iYColumnNumber [in]
		Y列番号を指定してください。
	@param aCentDedRessya [in]
		『列車』オブジェクトを指定してください。
	return:終着駅分岐元インデクスを返します。
		一行に複数列車を表示する場合、2列車目以降は前の列車が返した駅インデクス移行のみ描写します。
	*/
	void OnUpdate_setCentDedRessya_To_Column_Extension(
		int iYColumnNumber,
		const CentDedRessya& aCentDedRessya,
		const OperationTableContent& aOperationTableContent,
		const int iPrevShuchakuEkiIndex,
		const int iNextShihatsuEkiIndex,
		const int iPrevContinueEkiIndex = -1,
		const int iNextContinueEkiIndex = -1,
		const bool bIsContinue = false);
	
	/**
	 OnUpdate() の下請関数です。
	関連するドキュメントの内容を、このウインドウに完全に
	反映します。

	 OnUpdate() で pHint が NULL の際の動作です。

	 このとき、ウインドウの更新再描画も発生します。
	 */
	virtual void  OnUpdate_All() ;

	void OnCreate_Header();
	///@}
protected:
	// --------------------------------
	///@name メニューコマンドの下請関数
	// --------------------------------
	///@{
	/**	[編集]-[コピー]	
	@return
		成功したら0以上、エラーなら負の数です。
		-	-1 ;	//	フォーカスセルの位置が不正です。
		-	-2 :	//本線に指定されている番線です
	*/
	int OnEditCopy_Process( BOOL bQueryEnable );

	int OnOperationtableMovetojikokuhyou_Process(BOOL bQueryEnable);

	int OnOperationtableMovetojikokuhyouOpenDlg_Process(BOOL bQueryEnable);

	int OnOperationtableMovetodiagram_Process(BOOL bQueryEnable);

	int OnFileExportOperationTableCsv_Process(BOOL bQueryEnable);
	///@}

public:
	// ********************************
	//	コンストラクタ
	// ********************************
	CWndDcdGridOperationTable();
	virtual ‾CWndDcdGridOperationTable();

	// ********************************
	///@name	CDcdGrid
	// ********************************
	///@{
	///@}
protected:
	// ********************************
	///@name	CWndDcdGrid
	// ********************************
	///@{

	// --------------------------------
	///@name	イベント処理のための仮想関数
	// --------------------------------
	///@{
	///@}
 public:
	// ********************************
	///@name  COperationTableView からの委譲
	// ********************************
	///@{
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	///@}
public:
	// ********************************
	///@name CWndDcdGridOperationTable-操作
	// ********************************
	///@{
	///@}
	
protected:
	COperationTableDoc* GetDocument();

	const CentDedDia* getCentDedDia();

	const CentDedRessyaCont* getCentDedRessyaCont(
		ERessyahoukou eRessyahoukou);
	
private:
	//deque<CdDedRessyaProperty> m_aRessyaProperty;

	const list<OperationTableContent>* m_ListOperationTableContent = NULL;

	vector<OperationTable> m_contOperationTable;
	/**
		箱ダイヤが有効な時に、表示する駅の駅Index
		先頭にINT_MINがある場合は、起点側拡張スペースが有効
		終端にINT_MAXがある場合は、終点側拡張スペースが有効
	*/
	deque<int> m_iDisplayJikokuEkiIndex;

	/**
	箱ダイヤ形式で表示するか否かの指定

	-true ; 箱ダイヤ形式で表示します。
	-false ; (default)
	*/
	bool m_bDisplayExtensionOperationTable;

	/**
	駅時刻の秒単位を表示するか否かの指定

	-true ; 運用表ビューで秒単位まで時刻を表示します。
	-false ; (default)
	*/
	bool m_bDisplaySecondEkiJikoku;

	/**
	駅時刻をコロン付きで表示するか否かの指定

	-true ; 運用表ビューでコロン付きで時刻を表示します。
	-false ; (default)
	*/
	bool m_bDisplayColonEkiJikoku;

	/**
	列車の表示を親種別で行うか否かの指定

	-true ; 運用表ビューで列車の表示を親種別で表示します。
	-false ; (default)
	*/
	bool m_bDisplayParentSyubetsu;

	/**
	上り列車の始発駅を左側にして描写する(従来形式時)

	-true ; 運用表ビューで上り列車の始発駅を左側にして描写します。
	-false ; (default)
	*/
	bool m_bDisplayNoboriLeftToRight;

	/**
	着発番線名を表示する(箱ダイヤ時)

	-true ; 着発番線名を表示します。
	-false ; (default)
	*/
	bool m_bDisplayTrackName;
	/**
		通過駅の駅時刻を表示するか否かの指定です。

		- true ; 通過駅の駅時刻を表示します。(default)
		- false ; 通過駅の駅時刻を表示せずに、通過マーク "ﾚ" を表示します。
	 */
	bool m_bDisplayTsuukaEkiJikoku;

	/**
		最後にユーザーが入力したCSVファイル名
	*/
	CString	m_strCsvFilename;

	/**
	秒単位表示OFF時の秒単位処理方法の指定(着時刻)

	0:秒単位を切り捨てて表示します(デフォルト)
	1:30秒以上は切り上げ、それ未満は切り捨てて表示します。
	2:秒単位を切り上げて表示します
	*/
	int m_iSecondRoundChaku;

	/**
	秒単位表示OFF時の秒単位処理方法の指定(発時刻)

	0:秒単位を切り捨てて表示します(デフォルト)
	1:30秒以上は切り上げ、それ未満は切り捨てて表示します。
	2:秒単位を切り上げて表示します
	*/
	int m_iSecondRoundHatsu;

	/**
	着時刻が0時0分の時に、2400と表記するか否かの指定

	- true ; 2400表記を行います
	- false ; 000表記のままです(default)
	*/
	bool m_bDisplay2400;


protected:
	/**[表示] - [箱ダイヤを有効にする]
		@return
		0以上は成功、エラーなら負の数です。
		- 1 	(bQueryEnable == TRUEの場合)[箱ダイヤを有効にする]が有効です。
		- 0 	(bQueryEnable == TRUEの場合)[箱ダイヤを有効にする]が無効です。
		*/
	int OnViewDisplayExtensionOperationTable_Process(BOOL bQueryEnable);

	/**[表示] - [秒単位の時刻を表示]
		@return
		0以上は成功、エラーなら負の数です。
		- 1 	(bQueryEnable == TRUEの場合)[秒単位の時刻を表示]が有効です。
		- 0 	(bQueryEnable == TRUEの場合)[秒単位の時刻を表示]が無効です。
		*/
		int OnViewDisplaySecondEkijikoku_Process(BOOL bQueryEnable);


		/**[表示] - [コロン付き時刻表示]
		@return
		0以上は成功、エラーなら負の数です。
		- 1 	(bQueryEnable == TRUEの場合)[コロン付き時刻表示]が有効です。
		- 0 	(bQueryEnable == TRUEの場合)[コロン付き時刻表示]が無効です。
		*/
		int OnViewDisplayColonEkijikoku_Process(BOOL bQueryEnable);

		/**
		[表示] - [親種別を有効にする]
		@return
		0以上は成功、エラーなら負の数です。
		- 1 	(bQueryEnable == TRUEの場合)[親種別による表示]が有効です。
		- 0 	(bQueryEnable == TRUEの場合)[親種別によるを表示]が無効です。
		*/
		int OnViewDisplayParentSyubetsu_Process(BOOL bQueryEnable);

		/**
		[表示] - [上り列車の始発駅を左側にする]
		@return
		0以上は成功、エラーなら負の数です。
		- 1 	(bQueryEnable == TRUEの場合)[上り列車の始発駅を左側にする]が有効です。
		- 0 	(bQueryEnable == TRUEの場合)[上り列車の始発駅を左側にする]が無効です。
		*/
		int OnViewDisplayNoboriLeftToRight_Process(BOOL bQueryEnable);

		/**
		[表示] - [着発番線名を表示する]
		@return
		0以上は成功、エラーなら負の数です。
		- 1 	(bQueryEnable == TRUEの場合)[着発番線名を表示する]が有効です。
		- 0 	(bQueryEnable == TRUEの場合)[着発番線名を表示する]が無効です。
		*/
		int OnViewDisplayTrackName_Process(BOOL bQueryEnable);

		/** [表示]-[通過駅の駅時刻を表示]
		@return
			0以上は成功、エラーなら負の数です。
			-	1 	(bQueryEnable==TRUEの場合)[全時刻を表示]が有効です。
			-	0 	(bQueryEnable==TRUEの場合)[全時刻を表示]が無効です。
		*/
		int OnViewDisplayTsuukaEkiJikoku_Process(BOOL bQueryEnable);

public:
	bool getDisplayExtensionOperationTable()const;
	/**
	@return
	- 1 ;	設定を変更して、ウインドウを再描画しました。
	- 0 ;	表示内容は変化しませんでした。
	*/
	int setDisplayExtensionOperationTable(bool value);

		bool getDisplaySecondEkiJikoku()const;
		/**
		@return
		- 1 ;	設定を変更して、ウインドウを再描画しました。
		- 0 ;	表示内容は変化しませんでした。
		*/
		int setDisplaySecondEkiJikoku(bool value);

		bool getDisplayColonEkiJikoku()const;
		/**
		@return
		- 1 ;	設定を変更して、ウインドウを再描画しました。
		- 0 ;	表示内容は変化しませんでした。
		*/
		int setDisplayColonEkiJikoku(bool value);

		bool getDisplayParentSyubetsu()const;
		/**
		@return
		- 1 ;	設定を変更して、ウインドウを再描画しました。
		- 0 ;	表示内容は変化しませんでした。
		*/
		int setDisplayParentSyubetsu(bool value);

		bool getDisplayNoboriLeftToRight()const;
		/**
		@return
		- 1 ;	設定を変更して、ウインドウを再描画しました。
		- 0 ;	表示内容は変化しませんでした。
		*/
		int setDisplayNoboriLeftToRight(bool value);

		bool getDisplayTrackName()const;
		/**
		@return
		- 1 ;	設定を変更して、ウインドウを再描画しました。
		- 0 ;	表示内容は変化しませんでした。
		*/
		int setDisplayTrackName(bool value);
		
		bool getDisplayTsuukaEkiJikoku()const;
		/**
		 @return
			- 1 ;	設定を変更して、ウインドウを再描画しました。
			- 0 ;	表示内容は変化しませんでした。
		*/
		int setDisplayTsuukaEkiJikoku(bool value);




// ----------------------------------------------------------------
//	MFC
// ----------------------------------------------------------------
// アトリビュート
public:

// オペレーション
public:
	//{{AFX_VIRTUAL(CWndDcdGridOperationTable)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CWndDcdGridOperationTable)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//[編集]
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnViewDisplayExtensionOperationTable();
	afx_msg void OnUpdateViewDisplayExtensionOperationTable(CCmdUI* pCmdUI);
	afx_msg void OnViewDisplaySecondEkijikoku();
	afx_msg void OnUpdateViewDisplaySecondEkijikoku(CCmdUI *pCmdUI);
	afx_msg void OnViewDisplayColonEkijikoku();
	afx_msg void OnUpdateViewDisplayColonEkijikoku(CCmdUI *pCmdUI);
	afx_msg void OnViewDisplayParentSyubetsu();
	afx_msg void OnUpdateViewDisplayParentSyubetsu(CCmdUI *pCmdUI);
	afx_msg void OnViewDisplayNoboriLeftToRight();
	afx_msg void OnUpdateViewDisplayNoboriLeftToRight(CCmdUI* pCmdUI);
	afx_msg void OnViewDisplayTrackName();
	afx_msg void OnUpdateViewDisplayTrackName(CCmdUI* pCmdUI);
	afx_msg void OnViewDisplayTsuukaEkiJikoku();
	afx_msg void OnUpdateViewDisplayTsuukaEkiJikoku(CCmdUI* pCmdUI);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnOperationtableMovetojikokuhyou();
	afx_msg void OnUpdateOperationtableMovetojikokuhyou(CCmdUI *pCmdUI);
	afx_msg void OnOperationtableMovetojikokuhyouOpenDlg();
	afx_msg void OnUpdateOperationtableMovetojikokuhyouOpenDlg(CCmdUI *pCmdUI);
	afx_msg void OnOperationtableMovetodiagram();
	afx_msg void OnUpdateOperationtableMovetodiagram(CCmdUI *pCmdUI);
	afx_msg void OnFileExportOperationtablecsv();
};

} //namespace ViewOperationTable

#endif /*CWndDcdGridOperationTable_h*/
