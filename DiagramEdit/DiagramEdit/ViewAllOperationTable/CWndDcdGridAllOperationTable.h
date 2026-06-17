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
//	CWndDcdGridAllOperationTable.h
//	$Id: CWndDcdGridAllOperationTable.h $
// ****************************************************************
*/
/** @file */
#ifndef  CWndDcdGridAllOperationTable_h
#define  CWndDcdGridAllOperationTable_h

#include "DcdGrid/WndDcdGrid3/WndDcdGrid3.h"

//#include "..\entDed\CconvCentDed.h"
#include "AllOperationTableColSpec\AllOperationTableColSpec.h"
//#include "..\entDed\CdDedRessyaProperty.h"

namespace ViewAllOperationTable {

	using namespace AllOperationTableColSpec ;
	using namespace DcDrawLib::DcdGrid::WndDcdGrid3 ;
// ****************************************************************
//	CWndDcdGridAllOperationTable
// ****************************************************************
/**
@brief
 【概要】 CAllOperationTableView で用いる、グリッドウインドウです。
 */
class CWndDcdGridAllOperationTable : public CWndDcdGrid
{
public:
	// ********************************
	//	インナータイプ
	// ********************************
	typedef CWndDcdGrid super ;

	/** 運用一覧での「並べ替え」のモードを表す列挙です。 */
	enum EOperationSort
	{
		EOperationSort_OperationNumber = 0,	///< 運用番号でのソート
		EOperationSort_OutEki,	///< 出区駅ソート
		EOperationSort_OutJikoku,	///< 出区時刻ソート
		EOperationSort_InEki,	///< 入区駅ソート
		EOperationSort_InJikoku,	///< 入区時刻ソート
	};

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
	CdAllOperationTableXColSpecCont createXColSpecCont();


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
	CdAllOperationTableYColSpecCont createYColSpecCont();

	/**
	@return 
		フォーカスセルの列の表示内容を返します。
	*/
	CdAllOperationTableXColSpec getXColSpecOfFocus();

	/**
	@return 
		フォーカスセルの列の表示内容を返します。
	*/
	CdAllOperationTableYColSpec getYColSpecOfFocus() ;
	
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
	『運用』の内容を設定します。
	設定を行ったセルは、更新領域とします。
	@param iYColumnNumber [in]
		Y列番号を指定してください。
	@param aCentDedRessya [in]
		『運用』オブジェクトを指定してください。
	*/
	void OnUpdate_setOperationTableContent_To_Column(
		int iYColumnNumber,
		const tstring strOperationNumber,
		const list<OperationTableContent>& ListOperationTableContent);
	

	/**
		列車番号を数字の塊と数字以外の塊に分割します。
		CentDedRessya内にあるものと同様の動作です。
	*/
	void splitOperationNumber(
		const tstring strOperationNumberIn,
		vector<int>& iOperationNumber,
		vector<tstring>& strOperationNumberOut)const;

	/**
		二つの運用番号について、その並び順を調べます
		trueを返した場合は、strOperationNumber1が先、falseの場合は2が先を意味します。
	*/
	bool SortOperationNumber(
		const tstring strOperationNumber1,
		const tstring strOperationNumber2);

	/**
		二つの運用について、m_eOperationSortをもとに、その並び順を調べます
		trueを返した場合は、strOperationNumber1が先、falseの場合はstrOperationNumber2が先を意味します。
		strOperationNumber:比較対象となる運用番号です
		iEkiIndex:比較対象となるの出区駅・入区駅Indexです。予め求めておきます。
		iOuterIndex:比較対象となるの路線外始発・終着駅のIndexです。予め求めておきます。
			路線外発着でない場合はINT_MINが入ります。
		Jikoku:比較対象となるの出区駅発時刻・入区駅着時刻です。

		KitenJikoku:ダイヤグラムの起点時刻です。時刻順での比較に用います。
	*/
	bool SortOperation(
		const tstring strOperationNumber1,
		const int& iEkiIndex1,
		const int& iOuterIndex1,
		const CdDedJikoku& Jikoku1,
		const tstring strOperationNumber2,
		const int& iEkiIndex2,
		const int& iOuterIndex2,
		const CdDedJikoku& Jikoku2,
		const CdDedJikoku& KitenJikoku);

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

	//運用表へ移動
	int OnAllOperationtableMovetoOperationTable_Process(BOOL bQueryEnable);

	//時刻表へ移動
	int OnAllOperationtableMovetojikokuhyou_Process(BOOL bQueryEnable);

	//時刻表へ移動して出区駅作業編集を開く
	int OnAllOperationtableMovetojikokuhyouOpenOperationDlg_Process(BOOL bQueryEnable);

	//ダイヤグラムへ移動
	int OnAllOperationtableMovetodiagram_Process(BOOL bQueryEnable);

	//運用表CSVエクスポート
	int OnFileExportOperationTableCsv_Process(BOOL bQueryEnable);

	//運用一覧CSVエクスポート
	int OnFileExportAllOperationTableCsv_Process(BOOL bQueryEnable);
	///@}

public:
	// ********************************
	//	コンストラクタ
	// ********************************
	CWndDcdGridAllOperationTable();
	virtual ~CWndDcdGridAllOperationTable();

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
	///@name  CAllOperationTableView からの委譲
	// ********************************
	///@{
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	///@}
public:
	// ********************************
	///@name CWndDcdGridAllOperationTable-操作
	// ********************************
	///@{
	///@}
	
protected:
	CAllOperationTableDoc* GetDocument();

	const CentDedDia* getCentDedDia();

	const CentDedRessyaCont* getCentDedRessyaCont(
		ERessyahoukou eRessyahoukou);
	
private:

	/**
		運用番号を、m_eOperationSortとm_bCompareBottomに基づいて並び替えたものです
		この順番で運用一覧に表示します
	*/
	vector<tstring> m_strOperationNumber;

	/**
		各運用の全列車を表示するか否か
		false:出区列車と入区列車情報のみ表示します
		true:全列車を表示します。
	*/
	bool m_bDisplayAllRessya;

	/**
		最も列車本数が多い運用の列車本数。
		m_bDisplayAllRessyaがtrueの時のみ有効です
	*/
	int m_iMaxRessyaCount;

	/**
		運用の並び順です、運用一覧のプロパティで設定します。
	*/
	EOperationSort m_eOperationSort;

	/**
		運用番号を並び替えるときのルールです。運用一覧のプロパティで設定します。
	*/
	bool m_bCompareBottom;

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
		運用表CSVエクスポートで、上り列車を左から右へ表示するか否かの設定です
		この値は、運用一覧の表示では使用しません。運用表CSVエクスポートへ渡すためだけに存在します。
	*/
	bool m_bDisplayNoboriLeftToRight;

	/**
		運用表CSVエクスポートで、箱ダイヤ形式で表示するか否かの設定です
		この値は、運用一覧の表示では使用しません。運用表CSVエクスポートへ渡すためだけに存在します。
	*/
	bool m_bDisplayExtensionOperationTable;

	/**
		運用表CSVエクスポートで、着発番線名を表示するです
		この値は、運用一覧の表示では使用しません。運用表CSVエクスポートへ渡すためだけに存在します。
	*/
	bool m_bDisplayTrackName;

	/**
		運用表CSVエクスポートで、通過駅の駅時刻を表示するか否かの指定です
		この値は、運用一覧の表示では使用しません。運用表CSVエクスポートへ渡すためだけに存在します。
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

	/** [表示]-[運用一覧ビューのプロパティ]
	@param bQueryEnable [in]
		- TRUE ;	コマンドが現在実行できるか否かの判定だけを行います。@n
					エラーメッセージの表示は行いません。
		- FALSE ;	コマンドを実行します。 @n
				 エラーが発生した場合は、エラーメッセージボックスを表示します。
	@return
		0以上は成功、エラーなら負の数です。
		-	1 ;	//	ダイアログボックスでの入力が適用されました。
		-	0 ;	//	ダイアログボックスでの入力がキャンセルされました。
	*/
	int OnAllOperationTableProp_Process(BOOL bQueryEnable);

	/**[表示] - [全列車を表示]
		@return
		0以上は成功、エラーなら負の数です。
		- 1 	(bQueryEnable == TRUEの場合)[全列車を表示]が有効です。
		- 0 	(bQueryEnable == TRUEの場合)[全列車を表示]が無効です。
		*/
	int OnViewDisplayAllRessya_Process(BOOL bQueryEnable);

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

public:
	EOperationSort getOperationSort()const;
	/**
	@return
	- 1 ;	設定を変更して、ウインドウを再描画しました。
	- 0 ;	表示内容は変化しませんでした。
	*/
	int setOperationSort(EOperationSort value);

	bool getCompareBottom()const;
	/**
	@return
	- 1 ;	設定を変更して、ウインドウを再描画しました。
	- 0 ;	表示内容は変化しませんでした。
	*/
	int setCompareBottom(bool value);

	bool getDisplayAllRessya()const;
	/**
	@return
	- 1 ;	設定を変更して、ウインドウを再描画しました。
	- 0 ;	表示内容は変化しませんでした。
	*/
	int setDisplayAllRessya(bool value);

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
		- 0 ;	表示内容は変化しませんでした。
		*/
		int setDisplayNoboriLeftToRight(bool value);

		bool getDisplayExtensionOperationTable()const;
		/**
		@return
		- 0 ;	表示内容は変化しませんでした。
		*/
		int setDisplayExtensionOperationTable(bool value);

		bool getDisplayTrackName()const;
		/**
		@return
		- 0 ;	表示内容は変化しませんでした。
		*/
		int setDisplayTrackName(bool value);

		bool getDisplayTsuukaEkiJikoku()const;
		/**
		@return
		- 0 ;	表示内容は変化しませんでした。
		*/
		int setDisplayTsuukaEkiJikoku(bool value);



		CdPenProp  getCdPenPropBoldLine()const
		{
			return CdPenProp(2, CdColorProp(0, 0, 0), CdPenProp::SOLID);
		}

		CdPenProp getCdPenPropNarrowLine()const
		{
			return CdPenProp(1, CdColorProp(0, 0, 0), CdPenProp::SOLID);
		}

		CdPenProp getCdPenPropDotLine()const
		{
			return CdPenProp(2, CdColorProp(0, 0, 0), CdPenProp::DOT);
		}




// ----------------------------------------------------------------
//	MFC
// ----------------------------------------------------------------
// アトリビュート
public:

// オペレーション
public:
	//{{AFX_VIRTUAL(CWndDcdGridAllOperationTable)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CWndDcdGridAllOperationTable)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//[編集]
	afx_msg void OnAllOperationtableProp();
	afx_msg void OnUpdateAllOperationtableProp(CCmdUI* pCmdUI);
	afx_msg void OnViewDisplayAllRessya();
	afx_msg void OnUpdateViewDisplayAllRessya(CCmdUI* pCmdUI);
	afx_msg void OnViewDisplaySecondEkijikoku();
	afx_msg void OnUpdateViewDisplaySecondEkijikoku(CCmdUI *pCmdUI);
	afx_msg void OnViewDisplayColonEkijikoku();
	afx_msg void OnUpdateViewDisplayColonEkijikoku(CCmdUI *pCmdUI);
	afx_msg void OnViewDisplayParentSyubetsu();
	afx_msg void OnUpdateViewDisplayParentSyubetsu(CCmdUI *pCmdUI);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:	
	afx_msg void OnAllOperationtableMovetoOperationTable();
	afx_msg void OnUpdateAllOperationtableMovetoOperationTable(CCmdUI* pCmdUI);
	afx_msg void OnAllOperationtableMovetojikokuhyou();
	afx_msg void OnUpdateAllOperationtableMovetojikokuhyou(CCmdUI *pCmdUI);
	afx_msg void OnAllOperationtableMovetojikokuhyouOpenOperationDlg();
	afx_msg void OnUpdateAllOperationtableMovetojikokuhyouOpenOperationDlg(CCmdUI* pCmdUI);
	afx_msg void OnAllOperationtableMovetodiagram();
	afx_msg void OnUpdateAllOperationtableMovetodiagram(CCmdUI *pCmdUI);
	afx_msg void OnFileExportOperationtablecsv();
	afx_msg void OnFileExportAllOperationtablecsv();
};

} //namespace ViewAllOperationTable

#endif /*CWndDcdGridAllOperationTable_h*/
