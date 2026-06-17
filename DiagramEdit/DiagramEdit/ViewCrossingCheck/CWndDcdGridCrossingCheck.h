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
//	CWndDcdGridCrossingCheck.h
//	$Id: CWndDcdGridCrossingCheck.h $
// ****************************************************************
*/
/** @file */
#ifndef  CWndDcdGridCrossingCheck_h
#define  CWndDcdGridCrossingCheck_h

#include "DcdGrid/WndDcdGrid3/WndDcdGrid3.h"

//#include "..\entDed\CconvCentDed.h"
#include "CrossingCheckColSpec\CrossingCheckColSpec.h"
//#include "..\entDed\CdDedRessyaProperty.h"
#include "CCrossingCheckDoc.h"

namespace ViewCrossingCheck {

	using namespace CrossingCheckColSpec ;
	using namespace DcDrawLib::DcdGrid::WndDcdGrid3 ;
// ****************************************************************
//	CWndDcdGridCrossingCheck
// ****************************************************************

/**
	交差支障チェック1行に表示する内容です
	BeforeRessyaProperty:前動作の列車プロパティ
	iBeforeEkiIndex:前動作が行われている駅Indexです(分岐・環状を区別するため)
	BeforeFromTrackContent:前動作の移動元番線です。
	BeforeToTrackContent:前動作の移動先番線です。
	AfterRessyaProperty:後動作の列車プロパティ
	iAfterEkiIndex:後動作が行われている駅Indexです(分岐・環状を区別するため)
	AfterFromTrackContent:後動作の移動元番線です。
	AfterToTrackContent:後動作の移動先番線です。

	iHeadway: 前動作と後動作間の時隔です。
*/

struct CrossingCheckContent {
	CdDedRessyaProperty BeforeRessyaProperty;
	int iBeforeEkiIndex;
	TrackContent BeforeFromTrackContent;
	TrackContent BeforeToTrackContent;
	CdDedRessyaProperty AfterRessyaProperty;
	int iAfterEkiIndex;
	TrackContent AfterFromTrackContent;
	TrackContent AfterToTrackContent;
	int iHeadway;

	CrossingCheckContent()
		: BeforeRessyaProperty(CdDedRessyaProperty())
		, iBeforeEkiIndex(0)
		, BeforeFromTrackContent(TrackContent())
		, BeforeToTrackContent(TrackContent())
		, AfterRessyaProperty(CdDedRessyaProperty())
		, iAfterEkiIndex(0)
		, AfterFromTrackContent(TrackContent())
		, AfterToTrackContent(TrackContent())
		, iHeadway(0)
	{}
};
/**
	交差支障チェック1行に表示する内容です
	BeforeRessyaProperty:前動作の列車プロパティ
	iBeforeEkiIndex:前動作が行われている駅Indexです(分岐・環状を区別するため)
	BeforeFromTrackContent:前動作の移動元番線です。
	BeforeToTrackContent:前動作の移動先番線です。
	AfterRessyaProperty:後動作の列車プロパティ
	iAfterEkiIndex:後動作が行われている駅Indexです(分岐・環状を区別するため)
	AfterFromTrackContent:後動作の移動元番線です。
	AfterToTrackContent:後動作の移動先番線です。

	iHeadway: 前動作と後動作間の時隔です。
*/

struct CrossingCheckSearch {
	//CdDedJikoku aJikoku;
	CdDedRessyaProperty aRessyaProperty;
	int iEkiIndex;
	TrackContent FromTrackContent;
	TrackContent ToTrackContent;
	int iShiftSecond;

	CrossingCheckSearch()
		: /*aJikoku(CdDedJikoku())
		,*/aRessyaProperty(CdDedRessyaProperty())
		, iEkiIndex(0)
		, FromTrackContent(TrackContent())
		, ToTrackContent(TrackContent())
		, iShiftSecond(0)
	{}
};
//
//struct RessyaPropertyBuffer {
//	int iSyuuchakuEkiOrder;
//	int iOuterShuchakuekiIndex;
//	bool bLoop;
//	CdDedRessyaProperty aRessyaProperty;
//
//	RessyaPropertyBuffer()
//		:iSyuuchakuEkiOrder(INT_MIN)
//		, iOuterShuchakuekiIndex(INT_MIN)
//		, bLoop(false)
//		, aRessyaProperty(CdDedRessyaProperty())
//	{}
//};
/**
@brief
 【概要】 CCrossingCheckView で用いる、グリッドウインドウです。
 */
class CWndDcdGridCrossingCheck : public CWndDcdGrid
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
	CdCrossingCheckXColSpecCont createXColSpecCont();


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
	CdCrossingCheckYColSpecCont createYColSpecCont();

	/**
	@return 
		フォーカスセルの列の表示内容を返します。
	*/
	CdCrossingCheckXColSpec getXColSpecOfFocus();

	/**
	@return 
		フォーカスセルの列の表示内容を返します。
	*/
	CdCrossingCheckYColSpec getYColSpecOfFocus() ;
	
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

	void InsertCrossingCheckSearch(
		const int iFromTrackContentIndex,
		const int iToTrackContentIndex,
		const CrossingCheckSearch aCrossingCheckSearch,
		const int iType);

	void SearchBeforeOperationCont(
		const CentDedBeforeOperationCont* pBeforeCont,
		const CdDedRessyaProperty aRessyaProperty,
		const CentDedRessya* pCentDedRessya,
		const int iRessyaTrackIndex,
		const int iEkiIndex,
		const CdDedJikoku aCdDedJikoku
	);

	void SearchAfterOperationCont(
		const CentDedAfterOperationCont* pAfterCont,
		const CdDedRessyaProperty aRessyaProperty,
		const CentDedRessya* pCentDedRessya,
		const int iRessyaTrackIndex,
		const int iEkiIndex,
		const CdDedJikoku aCdDedJikoku
	);

	/**
		CrossingCheckSearchContAにCrossingCheckSearchContBの中身を挿入します。
	*/
	void MergeCrossingCheckSearchCont(
		list<CrossingCheckSearch>* CrossingCheckSearchContA,
		list<CrossingCheckSearch>* CrossingCheckSearchContB
	);

	/**
	 グリッドの 指定のY列に、
	『運用』の内容を設定します。
	設定を行ったセルは、更新領域とします。
	@param iYColumnNumber [in]
		Y列番号を指定してください。
	@param aCentDedRessya [in]
		『運用』オブジェクトを指定してください。
	*/
	void OnUpdate_setCrossingCheckContent_To_Column(
		int iRuleIndex,
		int iRessyaIndex,
		const CrossingCheckContent& aCrossingCheckContent);

	void OnUpdate_setCrossingCheckRule_To_Column(
		int iRuleIndex,
		const CrossingCheckRule& aCrossingCheckRule);

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

	//時刻表へ移動
	int OnCrossingCheckMovetojikokuhyou_Process(BOOL bQueryEnable);

	//ダイヤグラムへ移動
	int OnCrossingCheckMovetodiagram_Process(BOOL bQueryEnable);
	///@}

public:
	// ********************************
	//	コンストラクタ
	// ********************************
	CWndDcdGridCrossingCheck();
	virtual ~CWndDcdGridCrossingCheck();

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
	///@name CWndDcdGridCrossingCheck-操作
	// ********************************
	///@{
	///@}
	
protected:
	CCrossingCheckDoc* GetDocument();

	const CentDedDia* getCentDedDia();

	const CentDedRessyaCont* getCentDedRessyaCont(
		ERessyahoukou eRessyahoukou);
	
private:

	CdDedJikoku m_KitenJikoku;
	/**
		TrackContentをListに並べるときの対照表です
		[eTrackType][iTrackIndex]でアクセスすると、rossingCheckSearchContでのIndexを返します。
	*/
	vector<vector<int>> m_MapTrackContentToList;

	unordered_map<int, TrackContent> m_MapListToTrackContent;

	vector<tstring> m_strTrackNameCont;

	/**
		CrossingCheckSearchを移動元番線と移動先番線のTrackContent基づき、Listに入れます。
		TrackContentからvectorのindexへの変換には、m_MapTrackContentToListを用います
		List内は時刻順に並べます。

		[m_MapTrackContentToList[(int)FromTrackContent.eTrackType][FromTrackContent.iTrackIndex]]
			[m_MapTrackContentToList[(int)ToTrackContent.eTrackType][ToTrackContent.iTrackIndex]]でListにアクセスします。

		m_CrossingCheckSearchContArrivalは、停車・到着時刻に
		m_CrossingCheckSearchContDepartureは、停車・発車時刻に
		m_CrossingCheckSearchContTsuukaは、通過に用います。
		通過の場合、到着は駅構外・路線外→番線、出発はその逆に限られているので、一つで両対応します。
	*/
	vector<vector<list<CrossingCheckSearch>>> m_CrossingCheckSearchContArrival;

	vector<vector<list<CrossingCheckSearch>>> m_CrossingCheckSearchContDeparture;

	vector<vector<list<CrossingCheckSearch>>> m_CrossingCheckSearchContTsuuka;

	vector<vector< CrossingCheckContent>> m_CrossingCheckContentCont;


	/**
		パターンダイヤプレビュー機能における、1サイクルの秒数。
		0の場合は機能が無効
	*/
	int m_iPatternDiagramPreviewCycleSecond;

	/**
		パターンダイヤプレビュー機能における、前後各方向へのコピー範囲。
	*/
	int m_iPatternDiagramPreviewRange;

protected:

public:

		CdPenProp  getCdPenPropBoldLine()const
		{
			return CdPenProp(2, CdColorProp(0, 0, 0), CdPenProp::SOLID);
		}

		CdPenProp getCdPenPropNarrowLine()const
		{
			return CdPenProp(1, CdColorProp(0, 0, 0), CdPenProp::SOLID);
		}

		CdPenProp getCdPenPropNullLine()const
		{
			return CdPenProp(1, CdColorProp(0, 0, 0), CdPenProp::NULLPEN);
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
	//{{AFX_VIRTUAL(CWndDcdGridCrossingCheck)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CWndDcdGridCrossingCheck)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//[編集]
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:	
	afx_msg void OnCrossingCheckMovetojikokuhyou();
	afx_msg void OnUpdateCrossingCheckMovetojikokuhyou(CCmdUI *pCmdUI);
	afx_msg void OnCrossingCheckMovetodiagram();
	afx_msg void OnUpdateCrossingCheckMovetodiagram(CCmdUI *pCmdUI);
};

} //namespace ViewCrossingCheck

#endif /*CWndDcdGridCrossingCheck_h*/
