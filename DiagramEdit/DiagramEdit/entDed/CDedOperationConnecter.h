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
//	CDedOperationConnecter.h
// $Id: CDedOperationConnecter.h 241 2016-01-05 06:14:33Z okm $
// ****************************************************************
*/
/** @file */
#ifndef  CDedOperationConnecter_h
#define  CDedOperationConnecter_h

//#include "..¥entDed¥CentDedRosen.h"
//#include "..¥entDgr¥CentDedDgrDia.h"
#include "entDed.h"
#include <unordered_map>

namespace entDed {

	// ****************************************************************
	//	CDedOperationConnecter
	// ****************************************************************
	/**
	@brief
		【概要】
		CentDedDia 内の列車の『運用接続』処理を行うクラス。

		【使い方】

		1.  コンストラクタでオブジェクトを生成します。
		必要に応じて、OperationConnectもしくは
		OperationUpdateのどちらかを使い分けてください。

	*/
//struct RessyaList {
//	CdDedJikoku ChakuJikoku;
//	CdDedJikoku HatsuJikoku;
//
//	/**
//		この構造体が持つ意味を表す
//		-1:列車終端
//			列車プロパティが有効
//		0:ホーム占有
//			この時間帯は、当駅を通り抜ける列車、
//			作業が入換の場合の主発着番線を使用する列車が存在するため
//			運用接続の範囲外であることを示す。
//		1:列車先端
//			列車プロパティが有効
//		出区の場合は0
//		入区の場合も0
//	*/
//	int iType;
//	CdDedRessyaProperty sRessyaProperty;
//
//	RessyaList()
//		:ChakuJikoku(CdDedJikoku())
//		, HatsuJikoku(CdDedJikoku())
//		, iType(0)
//		, sRessyaProperty(CdDedRessyaProperty())
//	{}
//
//	RessyaList(
//		CdDedJikoku ChakuJikoku,
//		CdDedJikoku HatsuJikoku,
//		int iType)
//		:ChakuJikoku(ChakuJikoku)
//		, HatsuJikoku(HatsuJikoku)
//		, iType(iType)
//		, sRessyaProperty(CdDedRessyaProperty())
//	{}
//
//	RessyaList(
//		CdDedJikoku ChakuJikoku,
//		CdDedJikoku HatsuJikoku,
//		int iType,
//		CdDedRessyaProperty sRessyaProperty)
//		:ChakuJikoku(ChakuJikoku)
//		, HatsuJikoku(HatsuJikoku)
//		, iType(iType)
//		, sRessyaProperty(sRessyaProperty)
//	{}
//
//};

	/**
		RessyaPropertyと前作業もしくは後作業のいずれかの組み合わせで、
		列車の一点を示します。
		iShiftSecondは、パターンダイヤプレビュー有効時のみ使用し、元列車との時間差を保持します
	*/
struct RessyaElement {
	CentDedBeforeOperation* BeforeOperation;
	CentDedAfterOperation* AfterOperation;
	CdDedRessyaProperty sRessyaProperty;
	int iShiftSecond;

	RessyaElement()
		:BeforeOperation(NULL)
		, AfterOperation(NULL)
		, sRessyaProperty(CdDedRessyaProperty())
		, iShiftSecond(0)
	{}

	RessyaElement(
		CentDedBeforeOperation* BeforeOperation,
		CdDedRessyaProperty sRessyaProperty)
		:BeforeOperation(BeforeOperation)
		, AfterOperation(NULL)
		, sRessyaProperty(sRessyaProperty)
		, iShiftSecond(0)
	{}

	RessyaElement(
		CentDedAfterOperation* AfterOperation,
		CdDedRessyaProperty sRessyaProperty)
		:BeforeOperation(NULL)
		, AfterOperation(AfterOperation)
		, sRessyaProperty(sRessyaProperty)
		, iShiftSecond(0)
	{}
};


struct OperationElement {
	CentDedBeforeOperation* BeforeOperation;
	CentDedAfterOperation* AfterOperation;
	vector<int> iLevel;
	int iEkiIndexofContExist;
	int iRessyaTrackIndex;
	int iEkiOrder;
	//vector< OperationSimple> OperationChildren;
	//vector< OperationSimple>* OperationChildren;

	//CdDedRessyaProperty sRessyaProperty;

	OperationElement()
		:BeforeOperation(NULL)
		, AfterOperation(NULL)
		, iLevel(vector<int>())
		, iEkiOrder(0)
		, iEkiIndexofContExist(0)
		, iRessyaTrackIndex(0)
		//, OperationChildren(NULL)
	{}

	OperationElement(
		CentDedBeforeOperation* BeforeOperation,
		vector<int> iLevel,
		int iEkiOrder)
		:BeforeOperation(BeforeOperation)
		, AfterOperation(NULL)
		, iLevel(iLevel)
		, iEkiOrder(iEkiOrder)
		, iEkiIndexofContExist(0)
		, iRessyaTrackIndex(0)
		//, OperationChildren(NULL)
	{}

	OperationElement(
		CentDedAfterOperation* AfterOperation,
		vector<int> iLevel,
		int iEkiOrder)
		:BeforeOperation(NULL)
		, AfterOperation(AfterOperation)
		, iLevel(iLevel)
		, iEkiOrder(iEkiOrder)
		, iEkiIndexofContExist(0)
		, iRessyaTrackIndex(0)
		//, OperationChildren(NULL)
	{}

	OperationElement(
		CentDedBeforeOperation* BeforeOperation,
		vector<int> iLevel,
		int iEkiOrder,
		int iEkiIndexofContExist,
		int iRessyaTrackIndex)
		:BeforeOperation(BeforeOperation)
		, AfterOperation(NULL)
		, iLevel(iLevel)
		, iEkiOrder(iEkiOrder)
		, iEkiIndexofContExist(iEkiIndexofContExist)
		, iRessyaTrackIndex(iRessyaTrackIndex)
		//, OperationChildren(NULL)
	{}

	OperationElement(
		CentDedAfterOperation* AfterOperation,
		vector<int> iLevel,
		int iEkiOrder,
		int iEkiIndexofContExist,
		int iRessyaTrackIndex)
		:BeforeOperation(NULL)
		, AfterOperation(AfterOperation)
		, iLevel(iLevel)
		, iEkiOrder(iEkiOrder)
		, iEkiIndexofContExist(iEkiIndexofContExist)
		, iRessyaTrackIndex(iRessyaTrackIndex)
		//, OperationChildren(NULL)
	{}

	//OperationSimple(
	//	Ou<CentDedOperationBefore>OperationBefore,
	//	vector< OperationSimple> OperationChildren)
	//	//vector< OperationSimple>* OperationChildren)
	//	:OperationBefore(OperationBefore)
	//	, OperationAfter(Ou<CentDedOperationAfter>())
	//	, OperationChildren(OperationChildren)
	//{}

	//OperationSimple(
	//	Ou<CentDedOperationAfter> OperationAfter,
	//	vector< OperationSimple> OperationChildren)
	//	//vector< OperationSimple>* OperationChildren)
	//	:OperationBefore(Ou<CentDedOperationBefore>())
	//	, OperationAfter(OperationAfter)
	//	, OperationChildren(OperationChildren)
	//{}
};

/**
	入出区連携コードによる運用接続を行うために用います。
	入出区連携コードをキーとし、この構造体を要素として管理します。
	iStatus:キーとなる入出区連携コードに対し、どの種類の列車が存在するのかと有効性を示します。
		0:出区(路線外始発)列車のみが存在します。
			最終的にこの状況な場合、入出区連携は無効となります。(出区作業に設定されている運番を使用して運用接続を行う)
		1:入区(路線外終着)列車のみが存在します。
			最終的にこの状況な場合、入出区連携は無効となります。
		2:出区と入区がペアになっています。
			最終的にこの状況な場合、入出区連携は有効となります。
		3:出区もしくは入区の片方または両方の列車が、2本以上存在します。
			最終的にこの状況な場合、入出区連携は無効となります。
	aRessyaElement:
		出区側列車の場合、そのRessyaProperty及びBeforeOperationを収めます。
		RessyaPropertyには出区時刻も収められ、時刻比較に用います。
		入区側列車の場合、RessyaPropertyのみ収められます。
		RessyaPropertyのうち、入区時刻のみが用いられ、それ以外の情報は特に意味を持ちません。
*/
//struct InOutLinkCodeElement {
//	int iStatus;
//	RessyaElement aRessyaElement;
//	//CdDedJikoku InOutJikoku;
//
//	InOutLinkCodeElement()
//		:iStatus(3)
//		, aRessyaElement(RessyaElement())
//	{}
//
//	InOutLinkCodeElement(
//		int iStatus,
//		RessyaElement aRessyaElement)
//		:iStatus(iStatus)
//		, aRessyaElement(aRessyaElement)
//	{}
//
//	//InOutLinkCodeElement()
//	//	:iStatus(3)
//	//	, aOutRessyaElement(RessyaElement())
//	//	, InOutJikoku(CdDedJikoku())
//	//{}
//
//	//InOutLinkCodeElement(
//	//	RessyaElement aOutRessyaElement,
//	//	CdDedJikoku OutJikoku)
//	//	:iStatus(0)
//	//	, aOutRessyaElement(aOutRessyaElement)
//	//	, InOutJikoku(OutJikoku)
//	//{}
//
//	//InOutLinkCodeElement(
//	//	CdDedJikoku InJikoku)
//	//	:iStatus(1)
//	//	, aOutRessyaElement(RessyaElement())
//	//	, InOutJikoku(InJikoku)
//	//{}
//
//};

struct OuterSearchElement {
	CdDedRessyaProperty aRessyaProperty;
	vector<tstring> strContOperationNumber;
	int iEkiOrder;
	bool bIsConnectOrRelease;
	//int iStatus;
	//RessyaElement aRessyaElement;
	//CdDedJikoku InOutJikoku;

	OuterSearchElement()
		:aRessyaProperty(CdDedRessyaProperty())
		, strContOperationNumber(vector<tstring>())
		, iEkiOrder(-1)
		, bIsConnectOrRelease(false)
	{}

	OuterSearchElement(
		CdDedRessyaProperty aRessyaProperty,
		vector<tstring> strContOperationNumber,
		int iEkiOrder)
		:aRessyaProperty(aRessyaProperty)
		, strContOperationNumber(strContOperationNumber)
		, iEkiOrder(iEkiOrder)
		, bIsConnectOrRelease(false)
	{}

	OuterSearchElement(
		CdDedRessyaProperty aRessyaProperty,
		vector<tstring> strContOperationNumber,
		int iEkiOrder,
		bool bIsConnectOrRelease)
		:aRessyaProperty(aRessyaProperty)
		, strContOperationNumber(strContOperationNumber)
		, iEkiOrder(iEkiOrder)
		, bIsConnectOrRelease(bIsConnectOrRelease)
	{}

};

/**
	カスタマイズ時刻表組立に用います。駅時刻表ビューからの借りものです。

	駅時刻表一マスに表示する内容です。
	iMinute:分
	iRessyaSyubetsu:列車種別Index
	iSyuuchakuEkiOrder:終着駅Order
		ただし、この値が-1の場合は、環状運転であることを意味します。
		また、この値が-2の場合は、行き先が環状線であることを意味します。
	iOuterShuchakuekiIndex:路線外終着の場合、路線外終着駅Index
	iRessyaTrackIndex:発車番線
	aRessyaProperty:列車プロパティ

	種別変更表示の場合
	iMinute:ここには"-1"が入ります。種別変更表示であることを意味します
	iRessyaSyubetsu:種別変更後の列車種別Index
	iSyuuchakuEkiOrder:"種別変更を行う"駅Order(元の列車基準)
	aRessyaProperty:種別変更後の列車プロパティ
	iOuterShuchakuekiIndexとiRessyaTrackIndexは未使用です
*/

struct OuterDisplayContent {
	CdDedJikoku HatsuJikoku;
	CdDedJikoku ChakuJikoku;
	int iRessyaSyubetsu;
	CentDedEkiJikoku::EEkiatsukai eEkiatsukai;
	int iRessyaTrackIndex;
	int iEkiOrder;
	int iOuterEkiIndex;
	CdDedRessyaProperty aRessyaProperty;

	OuterDisplayContent()
		: HatsuJikoku(CdDedJikoku())
		, ChakuJikoku(CdDedJikoku())
		, iRessyaSyubetsu(0)
		, eEkiatsukai(CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya)
		, iRessyaTrackIndex(0)
		, iEkiOrder(INT_MIN)
		, iOuterEkiIndex(INT_MIN)
		, aRessyaProperty(CdDedRessyaProperty())
	{}
};

struct RessyaPropertyBuffer {
	int iEkiOrder;
	int iOuterEkiIndex;
	bool bLoop;
	CdDedRessyaProperty aRessyaProperty;

	RessyaPropertyBuffer()
		:iEkiOrder(INT_MIN)
		, iOuterEkiIndex(INT_MIN)
		, bLoop(false)
		, aRessyaProperty(CdDedRessyaProperty())
	{}
};

class CDedOperationConnecter
{
private:
	// ********************************
	///@name 関連
	// ********************************
	///@{
	/**
		運用接続の対象となる列車を集約する路線オブジェクト。
	*/
	const CentDedRosen* m_pDedRosen;

	/**
		運用接続の対象となる列車を集約するダイヤ。
	*/
	CentDedDia* m_pDedDia;

	///@}
	// ********************************
	///@name 属性
	// ********************************
	///@{

	/**
		ダイヤグラム起点時刻
		コンストラクタで決まります
	*/
	CdDedJikoku m_KitenJikoku;

	/**
		折り返し時に運用番号を反転させるか否か
		この値がtrueの時、運用探索で下り⇔上りの接続が行われると、
		運用番号の並びを反転させます。
		(例)折り返し前が "01A","21B"の場合、
		折り返し後は"21B","01A"になります
		コンストラクタで決まります
	*/
	bool m_bOperationNumberReverse;

	/**
		運用接続時に起点時刻を跨ぐか否か
		コンストラクタで決まります
	*/
	bool m_bOperationCrossKitenJikoku;

	/**
		パターンダイヤプレビュー機能における、1サイクルの秒数。
		最小は60、最大は10800(3時間)とします。
	*/
	int m_iPatternDiagramPreviewCycleSecond = 0;

	/**
		パターンダイヤプレビュー機能における、前後各方向へのコピー範囲。
	*/
	int m_iPatternDiagramPreviewRange;


	vector<vector<list<RessyaElement>>> m_contRessyaExist;

	/**
		出区及び路線外始発作業の一覧です。
		運用接続の最初は、ここに詰められた作業から順に行います。
	*/
	vector<RessyaElement> m_contOutOuter;
	/**
		運用番号変更作業の一覧です。
		m_contOutOuterに続き、ここに詰められた作業から探索を行います。
	*/
	vector<RessyaElement> m_contNumberChange;

	/**
		列車方向×列車数分の、運用要素配列です。
		各列車のうち、先端作業・終端作業・増解結のみを抜き取り、駅Orderなどと共にここに収めておきます。
		これにより、この配列を順に辿っていくことで、運用接続を行うことができます。
	*/
	vector<vector<vector<OperationElement>>> m_contRessyaOperationElement;

	/**
		作業接続中に、増結編成側の運番が未入力の増結作業が見つかった場合、
		このリストに収め、一度作業接続を中断します。
		その後、このリストの増結作業を順に参照して、増結編成側運番が割り当てられた場合は、
		作業接続を続行します。
	*/
	//list< RessyaElement> m_contConnectWaitList;
	vector< RessyaElement> m_contConnectWaitList;

	/**
		OperationConnectでは、前列車接続作業を格納します。
		SearchRessyaElementRevと組み合わせて使い、
		前列車が見つからない場合に、空白運番で運用接続を強制的に行います。
		OperationConnectLightでは、次列車接続を格納します。
		SearchRessyaElementと組み合わせて使い、次列車接続と前列車接続の組をつなぎ、種別変更や増解結の処理も行います。
	*/
	vector< RessyaElement> m_contJunctionList;

	/**
		列車方向×列車数分の運用番号→運用表用表示情報の連想配列です。
		ここには、出区・路線外始発・前列車接続探索時に、運番をキーとして始発作業・駅Orderなどを収めておき、
		入区・路線insertOperationTableContentToBuffer外終着・次列車接続探索時に、運番をキーとして上記始発情報を獲得し、
		その運番が、この列車において、どの駅のどの作業を先端とし、どの駅のどの作業を終端としているのかを求めます。
		求まったものは、CentDedDiaにあるcontに、運番別に収納していき、運用表を表示するための材料とします。
	*/
	vector<vector<unordered_map<tstring,OperationTableContent>>> m_contOperationTableContentBuffer;

	/**
		入出区連携コードをキーとする連想配列です。
		入出区・路線外始発終着のうち、入出区連携コードが入力されているものを、
		ここに収めておき、ペアになるかどうか、(起点時刻跨ぎが有効な場合は)時刻要件を満たしているかをチェックします。
	*/
	//unordered_map<tstring,InOutLinkCodeElement> m_contInOutLinkList;

	/**
		[列車方向][始発/終着駅Order]でアクセスします。
		カスタマイズ時刻表において、路線外扱い表示を行う列車のRessyaPropertyおよび対象運番を、
		ここに一時保存して、completeCustomizeJikokuhyouContentにて、路線外表示を組み立てます。
		m_contBeforeContinueListは始発側を行う列車、
		m_contAfterContinueListは終点側を行う列車です。
	*/
	vector<vector<vector<OuterSearchElement>>> m_contBeforeContinueList;
	vector<vector<vector<OuterSearchElement>>> m_contAfterContinueList;

	/**
		[列車方向][併合駅Order]でアクセスします。
		key1のintは、当該列車のRessyaIndexを、
		key2のCustomizeJikokuhyouContentは、実際に挿入するものを入れます。
		☆1,2,4において、路線外始発で併合する列車の表示を追加するのを、
		一回ストックしておいて最後にまとめてCustomizeJikokuhyouContentを挿入します。
	*/
	vector<vector<unordered_multimap<int,CustomizeJikokuhyouContent>>> m_contOuterConnectInsertList;

	/**
		[列車方向][併合駅Order]でアクセスします。
		key1のintは、当該列車のRessyaIndexを、
		key2のCustomizeJikokuhyouContentは、実際に挿入するものを入れます。
		☆3において、路線外終着で分割する列車の表示を追加するのを、
		一回ストックしておいて最後にまとめてCustomizeJikokuhyouContentを挿入します。
	*/
	vector<vector<unordered_multimap<int, CustomizeJikokuhyouContent>>> m_contOuterReleaseInsertList;

	/**
		[列車方向][併合駅Order]でアクセスします。
		key1のintは、併合先の列車Indexを、
		key2のintは、併合列車の列車Indexを入れます。
		(key2の列車を、key1の直前に移す)
	*/
	vector<vector<unordered_multimap<int, int>>> m_contConnectMoveList;
	/**
		[列車方向][分割駅Order]でアクセスします。
		key1のintは、分割元の列車Indexを、
		key2のintは、分割列車の列車Indexを入れます。
		(key2の列車を、key1の直後に移す)
	*/
	vector<vector<unordered_multimap<int, int>>> m_contReleaseMoveList;


	/**
		各種別が、隠し種別であるかどうか。
		隠し種別はカスタマイズ時刻表で非表示とします。
		また、隠し種別と非隠し種別間では次列車接続タイプは全て「別列車」とみなします。
	*/
	vector<bool> m_contHidden;

	/**
		隠し種別が存在するか否か、「隠し種別を表示する」が有効な場合には、必ずfalseにします。
	*/
	bool m_bHiddenExist;
	///@}
	// ********************************
	///@name 集約
	// ********************************
	///@{
	/**
		運用接続の対象となるダイヤのオブジェクト。
		コンストラクタで作成されます
	*/
	//CentDedDgrDia m_CentDedDgrDia;

	///@}

	// ********************************
	///@name 状態
	// ********************************
	///@{
	///@}
protected:
	// --------------------------------
	///@name 下請関数
	// --------------------------------
	///@{

	///@}

protected:
	/**
		m_contRessyaExistにRessyaElementを挿入します
		m_contRessyaExistは駅数×番線数の配列になっていて、
		前列車接続または次列車接続とRessyaPropertyをまとめた、RessyaElementを、
		その作業がある駅と番線の箇所に時刻順に並べます。
		iEkiIndexofContExist:挿入する駅番号です。
		iRessyaTrackIndex:挿入する番線Indexです
		aRessyaElement:挿入するRessyaElementです。
	*/
	virtual void InsertRessyaElement(
		const int iEkiIndexofContExist,
		const int iRessyaTrackIndex,
		const RessyaElement aRessyaElement);

	/**
		m_contRessyaExistにRessyaElementを挿入します
		m_contRessyaExistは駅数×番線数の配列になっていて、
		前列車接続または次列車接続とRessyaPropertyをまとめた、RessyaElementを、
		その作業がある駅と番線の箇所に時刻順に並べます。
		iEkiIndexofContExist:挿入する駅番号です。
		iRessyaTrackIndex:挿入する番線Indexです
		aRessyaElement:挿入するRessyaElementです。
	*/
	//virtual void InsertRessyaElementPatternDiagram(
	//	const int iEkiIndexofContExist,
	//	const int iRessyaTrackIndex,
	//	const RessyaElement aRessyaElement);

	/**
		pRessyaExistからaAfterOperationを基に、そこから繋がるRessyaElement(BeforeOperationを含む)を返します
		pRessyaExist:検索対象となるm_contRessyaExistの一コンテナ
		aAfterOperation:検索元となる後作業(次列車接続)
		pTerminalJikoku:aAfterOperationを含むRessyaElementのRessyaPropertyに含まれる時刻を返します。
		iShiftSecond:パターンダイヤプレビュー時の元列車からのシフト秒数。aAfterOperationに加えて、この値も比較します。
	*/
	virtual RessyaElement SearchRessyaElement(
		list<RessyaElement>* pRessyaExist,
		CentDedAfterOperation* aAfterOperation,
		CdDedJikoku& pTerminalJikoku,
		const int iShiftSecond = 0);

	/**
		pRessyaExistからaBeforeOperationをもとに、そこから前につながるRessyaElementがあるかどうかを返します
		pRessyaExist:検索対象となるm_contRessyaExistの一コンテナ
		aBeforeOperation:検索元となる前作業(前列車接続)
	*/
	virtual bool SearchRessyaElementRev(
		list<RessyaElement>* pRessyaExist,
		CentDedBeforeOperation* aBeforeOperation);
		
	/**
		簡易モード時の処理です
	*/
	virtual void operationConnectLight();

	/**
		パターンダイヤプレビュー有効時の処理です
	*/
	virtual void operationConnectPatternDiagram();

	/**
		通常モード時の処理です
	*/
	virtual void operationConnect();

	/**
		前作業コンテナを読み取り、列車作業の簡略図を作成します。

		pBeforeCont:読み取り対象となる前作業コンテナです
		ConnectJikoku:pBeforeContの親作業である増結作業の増結時刻です。
			このコンテナの最初の作業が前列車接続の場合、起点時刻導出に用います。
		aRessyaProperty:pBeforeContを含む列車です。
		iLevelParent:pBeforeContの親作業である増結作業のiLevelです。
			この前作業コンテナ内の作業のilevelはこの値に桁を増やしたものになります
		iEkiOrder:pBeforeContが存在する駅Orderです
		iEkiIndexofContExist:m_contRessyaExistにアクセスする際のIndexです。
		iRessyaTrackConnect::pBeforeContの親作業である増結作業が行われた番線Indexです
			このコンテナの最初の作業が前列車接続の場合、番線導出に用います。
	*/
	vector<OperationElement> searchBeforeOperationElement(
		CentDedBeforeOperationCont* pBeforeCont,
		const CdDedJikoku ConnectJikoku,
		const CdDedRessyaProperty aRessyaProperty,
		const vector<int> iLevelParent,
		const int iEkiOrder,
		const int iEkiIndexofContExist,
		const int iRessyaTrackConnect);

	/**
		OperationConnectLight向けです。

	*/
	vector<OperationElement> searchBeforeOperationElementLight(
		CentDedBeforeOperationCont* pBeforeCont,
		const CdDedJikoku ConnectJikoku,
		const CdDedRessyaProperty aRessyaProperty,
		const vector<int> iLevelParent,
		const int iEkiOrder,
		const int iEkiIndexofContExist,
		const int iRessyaTrackConnect);

	/**
		後作業コンテナを読み取り、列車作業の簡略図を作成します。

		pAfterCont:読み取り対象となる後作業コンテナです
		ReleaseJikoku:pAfterContの親作業である解結作業の解結時刻です。
			このコンテナの最後の作業が次列車接続の場合、終点時刻導出に用います。
		aRessyaProperty:pAfterContを含む列車です。
		iLevelParent:pAfterContの親作業である解結作業のiLevelです。
			この後作業コンテナ内の作業のilevelはこの値に桁を増やしたものになります
		iEkiOrder:pAfterContが存在する駅Orderです
		iEkiIndexofContExist:m_contRessyaExistにアクセスする際のIndexです。
		iRessyaTrackRelease::pAfterContの親作業である解結作業が行われた番線Indexです
			このコンテナの最初の作業が次列車接続の場合、番線導出に用います。
	*/
	vector<OperationElement> searchAfterOperationElement(
		CentDedAfterOperationCont* pAfterCont,
		const CdDedJikoku ReleaseJikoku,
		const CdDedRessyaProperty aRessyaProperty,
		const vector<int> iLevelParent,
		const int iEkiOrder,
		const int iEkiIndexofContExist,
		const int iRessyaTrackRelease);

	vector<OperationElement> searchAfterOperationElementLight(
		CentDedAfterOperationCont* pAfterCont,
		const CdDedJikoku ReleaseJikoku,
		const CdDedRessyaProperty aRessyaProperty,
		const vector<int> iLevelParent,
		const int iEkiOrder,
		const int iEkiIndexofContExist,
		const int iRessyaTrackRelease);

	/**
		運用番号の割り当てを行います。
		iLevelSearchをもとに、次の作業を見つけ、運用番号の割り当てを行います。
		次の作業が次列車接続なら、SearchRessyaElementで次列車を見つけ、接続します。

		aRessyaPropertyCurr:割り当て中の列車のRessyaProperty
		contOperationElementCurr:割り当て中の列車のOperationElementが集められたコンテナです。
		iLevelSearch:このiLevelを持つ作業を、contOperationElementCurrから探して、接続します。
		strOperationNumber:割り当てる運用番号です。
		pCustomizeJikokuhyouContent:カスタマイズ時刻表の構成要素です、
			複数列車を一行に表示する場合や、増解結の矢印表示、路線外発着相当の表示など、
			カスタマイズ時刻表での表示に用いるデータを、ここで構成します。
			pCustomizeJikokuhyouContentは、各列車の開始作業(出区・路線外始発・前列車接続)で作成したものを、
			ポインタとして後ろの作業に送っていきます。
	*/
	void junctionOperationElement(
		const CdDedRessyaProperty aRessyaPropertyCurr,
		const vector<OperationElement>& contOperationElementCurr,
		const vector<int>& iLevelSearch,
		const vector<tstring>& strOperationNumber/*,
		CustomizeJikokuhyouContent* pCustomizeJikokuhyouContent*/);

	/**
		開始作業に運用番号が割り当てられたときに、始発側の情報を収めたOperationTableContentを
		Bufferに収めておきます。収めたものはaddOperationTableContentで抜き出されます。
		aRessyaProperty:探索中の列車のプロパティです。OperationTableContentToBufferにアクセスするのに用います。
		strOperationNumber:割り当てられた運用番号です。この運用番号一つづつ、Bufferに収めていきます
		iSihatsuEkiOrder:OperationTableContentに収める始発駅Orderです。
		pBeforeOperation:前作業のポインタです。開始作業が路線外始発の時にのみ用い、
			路線外始発駅Indexと時刻を取得してOperationTableContentに収めます。
		pAfterOperation:後作業のポインタです。検索用後作業とします。
			検索用後作業は、この関数が前列車接続の探索で呼び出されたときのみ渡され、
			addOperationTableContentで運用表を組み立てるとき、
			OperationTableContentをどの位置に挿入するかを求めるのに使います。
		bContinue:この開始作業(前列車接続に限る)が、前の列車から一続きの列車であるか否かを示します。
			一続きの定義は、種別変更・分割・併合です。
	*/
	void insertOperationTableContentToBuffer(
		const CdDedRessyaProperty aRessyaProperty,
		vector<tstring>& strOperationNumber,
		const int iSihatsuEkiOrder,
		const CentDedBeforeOperation* pBeforeOperation,
		const CentDedAfterOperation* pAfterOperation,
		const EBeforeAfterType eBeforeType);

	/**
		insertOperationTableContentToBufferで収められたOperationTableContentを取り出し、
		終着側の情報を収めた上で、CentDedDiaのcontOperationTableContentに入れ、運用表の元とします。
		aRessyaProperty:探索中の列車のプロパティです。OperationTableContentToBufferにアクセスするのに用います。
		strOperationNumber:割り当てられた運用番号です。この運用番号一つづつ、Bufferに収めていきます
		iSyuuchakuEkiOrder:OperationTableContentに収める終着駅Orderです。
		pAfterOperation:後作業のポインタです。終了作業が路線外終着の時にのみ用い、
			路線外終着駅Indexと時刻を取得してOperationTableContentに収めます。
	*/
	void addOperationTableContent(
		const CdDedRessyaProperty aRessyaProperty,
		vector<tstring>& strOperationNumber,
		const int iSyuuchakuEkiOrder,
		const CentDedAfterOperation* pAfterOperation,
		const EBeforeAfterType eAfterType);

	void insertInOutLinkCodeElement(
		const tstring strInOutLinkCode,
		const RessyaElement aRessyaElement);

	void completeCustomizeJikokuhyouContent();

public:
	// ********************************
	//	コンストラクタ
	// ********************************
	/**
	　	@param pDedRosen [in]
			ソートの対象となる列車を集約する路線オブジェクト。
	*/
	CDedOperationConnecter(
		const CentDedRosen* pDedRosen,
		CentDedDia* pDedDia);

	CDedOperationConnecter(
		const CentDedRosen* pDedRosen,
		CentDedDia* pDedDia,
		const CdDedJikoku aCdDedJikokuMin,
		const CdDedJikoku aCdDedJikokuMax,
		const ERessyahoukou eRessyahoukouEdit,
		const int iIndexDst,
		const int iSizeDst,
		const int iAddSize);

	virtual ‾CDedOperationConnecter();


};

} //namespace entDgr


#endif /*CDedRessyaSoater_Transfer_h*/
