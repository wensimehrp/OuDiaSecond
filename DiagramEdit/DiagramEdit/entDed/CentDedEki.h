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
//	CentDedEki.h
// ****************************************************************
*/
/** @file */
#ifndef  CentDedEki_h
#define  CentDedEki_h

#include <string>
#include "str\tstring.h"
#include "NsMu\CChildBase.h"
#include "CentDedEkiTrack2Cont.h"
#include <vector>
#include <tchar.h>

namespace entDed{
	using namespace OuLib::NsMu;

	using OuLib::NsMu::CChildBase ;

// ****************************************************************
//	CentDedEki
// ****************************************************************
/**
@brief
  DiagramEdit の、路線にある駅ひとつを表します。

  属性として、『駅名』・『駅時刻形式』・『駅規模』を保持します。
  また、CentDedEkiTrackCont を包含します。

制約
 -------------------------------- 


操作のエラー検査・修正
 -------------------------------- 

○親オブジェクトの変更(setParent()):  adjust()を実行する

△上書き(operator=) : このオブジェクトが、親オブジェクトCentDedEkiCont の子である場合で、代入元が CentDedEkiCont::set() でエラーになる場合、例外スローになります。

制約に合うように属性を修正(adjust)
 -------------------------------- 
○CentDedEkiTrackCont(番線コンテナ)に、adjust()を委譲する。

*/
struct OuterTerminal
{

	/**
		路線外発着駅名です。
		作業設定画面で用います。
	*/
	tstring OuterTerminalEkimei;

	/**
		路線外発着駅名の時刻表ビューにおける略称です。
		空の場合は、OuterTerminalEkimeiをそのまま用います。
		文字数制限は当面ありません
	*/
	tstring OuterTerminalJikokuRyaku;

	/**
		路線外発着駅名のダイアグラムビューにおける略称です。
		空の場合は、OuterTerminalEkimeiの頭文字になります。
		文字数制限は当面ありません
	*/
	tstring OuterTerminalDiaRyaku;


	OuterTerminal()
		: OuterTerminalEkimei(_T(""))
		, OuterTerminalJikokuRyaku(_T(""))
		, OuterTerminalDiaRyaku(_T(""))
	{
	}

	OuterTerminal(tstring strA,
		tstring strB,
		tstring strC)
		: OuterTerminalEkimei(strA)
		, OuterTerminalJikokuRyaku(strB)
		, OuterTerminalDiaRyaku(strC)
	{
	}
};

/**
	平面交差チェックルールにおいて、番線属性を表すために用います
*/
enum class ETrackType
{
	/**
		駅の番線
		TrackIndexはEkiTrackIndexをそのまま用います。
	*/
	TrackType_Track = 0,

	/**
		路線の起点側
		TrackIndexは駅Indexが入ります
	*/
	TrackType_Origin,

	/**
		路線の終点側
		TrackIndexは駅Indexが入ります
	*/
	TrackType_Terminal,

	/**
		路線外発着
		TrackIndexはOuterEkiIndexをそのまま用います
	*/
	TrackType_Outer,

};
struct TrackContent
{

	/**
		番線属性
	*/
	ETrackType eTrackType;

	/**
		番線インデクス
		番線属性により異なります。

	*/
	int iTrackIndex;

	TrackContent()
		: eTrackType(ETrackType::TrackType_Track)
		, iTrackIndex(0)
	{
	}

	TrackContent(ETrackType eTrackType,
		int iTrackIndex)
		: eTrackType(eTrackType)
		, iTrackIndex(iTrackIndex)
	{
	}

	bool equal(TrackContent& value)const
	{
		return(eTrackType == value.eTrackType &&
			iTrackIndex == value.iTrackIndex);
	}
};
struct CrossingCheckRule
{
	/**
		有効・無効
		このルールが有効が(一時的に)無効かを表します。
	*/
	bool bEnable;

	/**
		前動作の移動前番線
	*/
	vector< TrackContent> BeforeFromTrackContentCont;

	/**
		前動作の移動後番線
	*/
	vector< TrackContent> BeforeToTrackContentCont;

	/**
		到着・出発
		前動作が到着時刻か出発時刻かを表します
		false:出発
		true:到着
	*/
	bool bBeforeIsArrival;

	/**
		通過・停車
		前動作が通過か停車かを表します
		false:停車
		true:通過
	*/
	bool bBeforeIsTsuuka;

	/**
		後動作の移動前番線
	*/
	vector< TrackContent> AfterFromTrackContentCont;

	/**
		後動作の移動後番線
	*/
	vector< TrackContent> AfterToTrackContentCont;

	/**
		到着・出発
		後動作が到着時刻か出発時刻かを表します
		false:出発
		true:到着
	*/
	bool bAfterIsArrival;

	/**
		通過・停車
		後動作が通過か停車かを表します
		false:停車
		true:通過
	*/
	bool bAfterIsTsuuka;

	/**
		時隔上限(秒)
		この値未満の時に、交差支障が起こっているとみなします。
		Ver2.06.05より、マイナスの値を指定できるようにします。
	*/
	int iHeadwaySecond;

	/**
		Ver2.06.05追加
		時隔下限(秒)
		この値以上の時に、交差支障が起こっているとみなします
		iHeadwaySecondMinimum < iHeadwaySecond である必要があります。
	*/
	int iHeadwaySecondMinimum;

	/**
		説明文
	*/
	tstring strCaption;

	CrossingCheckRule()
		: bEnable(true)
		, BeforeFromTrackContentCont(vector<TrackContent>())
		, BeforeToTrackContentCont(vector<TrackContent>())
		, bBeforeIsArrival(false)
		, bBeforeIsTsuuka(false)
		, AfterFromTrackContentCont(vector<TrackContent>())
		, AfterToTrackContentCont(vector<TrackContent>())
		, bAfterIsArrival(false)
		, bAfterIsTsuuka(false)
		, iHeadwaySecond(60)
		, iHeadwaySecondMinimum(0)
		, strCaption(tstring())
	{
	}

	CrossingCheckRule(bool bEnable,
		vector<TrackContent> BeforeFromTrackContentCont,
		vector<TrackContent> BeforeToTrackContentCont,
		bool bBeforeIsDeparture,
		bool bBeforeIsTsuuka,
		vector<TrackContent> AfterFromTrackContentCont,
		vector<TrackContent> AfterToTrackContentCont,
		bool bAfterIsDeparture,
		bool bAfterIsTsuuka,
		int iHeadwaySecond,
		int iHeadwaySecondMinimum,
		tstring strCaption)
		: bEnable(bEnable)
		, BeforeFromTrackContentCont(BeforeFromTrackContentCont)
		, BeforeToTrackContentCont(BeforeToTrackContentCont)
		, bBeforeIsArrival(bBeforeIsDeparture)
		, bBeforeIsTsuuka(bBeforeIsTsuuka)
		, AfterFromTrackContentCont(AfterFromTrackContentCont)
		, AfterToTrackContentCont(AfterToTrackContentCont)
		, bAfterIsArrival(bAfterIsDeparture)
		, bAfterIsTsuuka(bAfterIsTsuuka)
		, iHeadwaySecond(iHeadwaySecond)
		, iHeadwaySecondMinimum(iHeadwaySecondMinimum)
		, strCaption(strCaption)
	{
	}
};

class CentDedEki : public CChildBase
{
	typedef CChildBase	super ;
public:
	// ****************************************************************
	//	インナータイプ
	// ****************************************************************
	/**
		『駅時刻形式』を表す列挙です。
	 */
	enum class EEkijikokukeisiki
	{
		/**
			発時刻のみの表示。(規定値)
		
			(ただし、終着駅では着時刻のみを表示します)
		 */
		Jikokukeisiki_Hatsu = 0 ,
		
		/**
			発着表示。
		
			下り・上りとも、発着両方の時刻を表示。
			(始発駅・終着駅でも発着両方を表示)
		 */
		Jikokukeisiki_Hatsuchaku ,

		/**
			下り着表示。
		
			-	下り列車では、着時刻のみの表示。
			-	上り列車では、発時刻のみの表示。
			(ただし、終着駅では着時刻のみを表示します)
		 */
		Jikokukeisiki_KudariChaku ,
		
		/**
			上り着表示。
		
			-	下り列車では、発時刻のみの表示。
			(ただし、終着駅では着時刻のみを表示します)
			-	上り列車では、着時刻のみの表示。
		 */
		Jikokukeisiki_NoboriChaku ,
		
		/**
			下り発着表示。17.4.14_add_by_d_mania
		
			-	下り列車では、発着両方の時刻を表示。
			-	上り列車では、発時刻のみの表示。
			(ただし、終着駅では着時刻のみを表示します)
		 */
		Jikokukeisiki_KudariHatsuchaku ,
		
		/**
			上り発着表示。17.4.14_add_by_d_mania
		
			-	下り列車では、発時刻のみの表示。
			(ただし、終着駅では着時刻のみを表示します)
			-	上り列車では、発着両方の時刻を表示。
		 */
		Jikokukeisiki_NoboriHatsuchaku ,

	};
	
	/**
		『駅規模』を表す列挙です。
	 */
	enum class EEkikibo
	{
		/**
			一般駅。(規定値)
		 */
		Ekikibo_Ippan = 0 ,
		/**
			主要駅。
		
			主要駅では、ダイヤグラムの罫線が太線になります。
		 */
		Ekikibo_Syuyou ,
	};
	
	/**
		ダイヤグラム列車情報表示
	*/
	enum class EDiagramRessyajouhouHyouji
	{
		/**
			始発駅の場合には表示(既定値)
		*/
		DiagramRessyajouhouHyouji_Origin ,
		/**
			常に表示する。
		*/
		DiagramRessyajouhouHyouji_Anytime ,
		/**
			表示しない。
		*/
		DiagramRessyajouhouHyouji_Not ,
	};

public:
	// ****************************************************************
	//	インナータイプ
	// ****************************************************************
	/**
	このクラスに包含される『番線』(CentDedEkiTrack2) オブジェクト
	のコンテナです。
	*/
	class CXEkiTrack2Cont : public CentDedEkiTrack2Cont
	{
	public:
		// ********************************
		///@name CentDedEkiTrack2Cont-関連
		// ********************************
		///@{
		/**
		@return
		このコンテナが CentDedEki に包含されている場合は、
		CentDedEki のアドレス。
		そうでないならNULL。
		*/
		virtual CentDedEki* getEki();
		/**
		@return
		このコンテナが CentDedEki に包含されている場合は、
		CentDedEki のアドレス。
		そうでないならNULL。
		*/
		virtual const CentDedEki* getEki()const;
		///@}
	};

	/**
		このクラスがスローする例外
	*/
	class LException
	{
	};
	

public:
	/**
		ダイヤグラム背景色の数。
	*/
	static const int DIAGRAMBACKCOLOR_COUNT = 5;

private:
	// ********************************
	///@name 属性
	// ********************************
	///@{
	/**
		駅名
	
		規定値は、空文字列。
	 */
	tstring	m_strEkimei ;
	
	/**
		駅時刻形式。
	
		規定値は、 Jikokukeisiki_Hatsuhyouji 
	 */
	EEkijikokukeisiki	m_eEkijikokukeisiki ;
	
	/**
		『駅規模』を表す列挙です。
	
		規定値は、 Ekikibo_Ippan 
	 */
	EEkikibo	m_eEkikibo ;
	
	/**
		境界線あり。
	
	  この属性が true の駅では、時刻表画面の
		下り方向の下に、太い境界線を描画します。
	  この属性は、駅ビューと時刻表ビューに適用されます。
	  なおSecond1.02(FileType1.01)からは、分岐駅設定から
	  境界線位置を特定するため、このパラメータは大きな意味を持ちません。
	  ただし、旧ファイル形式を読み込むとき、一度この値を設定してから、
	  分岐駅設定の解読を行うため、残しておきます
	 */
	bool m_bKyoukaisen ;

	/**
		ダイヤグラム列車情報表示（下り）
	
		既定値は DiagramRessyajouhouHyouji_Origin です。
	*/	
	EDiagramRessyajouhouHyouji m_eDiagramRessyajouhouHyoujiKudari ;
	
	/**
		ダイヤグラム列車情報表示（上り）
	
		この属性が true の駅では、ダイヤグラムビューにおいて、
		下り列車の列車情報を描画します。

		既定値は DiagramRessyajouhouHyouji_Origin です。
	*/
	EDiagramRessyajouhouHyouji m_eDiagramRessyajouhouHyoujiNobori ;

	/**
		下り主本線
		0以上、番線数未満を指定。
		列車に番線を設定する場合の、初期値になります。
		Ver2.0 列車側の主本線指定撤廃により、-1が不要になります
	*/
	int m_iDownMain;

	/**
		上り主本線
		0以上、番線数未満を指定。
		列車に番線を設定する場合の、初期値になります。
		Ver2.0 列車側の主本線指定撤廃により、-1が不要になります
	*/
	int m_iUpMain;

	/**
		駅ID
		同名駅が存在する場合、これを区別するために使用します。
		駅がContにset,insertされるとき、空いている番号が付与されます。
	*/
	int m_iID;


	/**
		分岐駅設定の基幹駅駅Index
		-1:分岐駅設定は無効
		0以上:基幹駅のEkiIndex
	*/
	int m_iBrunchCoreEkiIndex;

	/**
		分岐駅設定が有効な時、通常とは反対向きに合流しているとみなします。
		具体的には、下り着時刻駅から下方の駅に対し、分岐駅指定している場合、
		通常は[Y]型の路線を意味しますが、この値がtrueの場合、
		[u]の右が下に伸びた感じの路線形状イメージになります。
	*/
	bool m_bBrunchOpposite;

	/**
		環状線設定の起点駅駅Index
		-1:環状線設定は無効
		0以上:起点駅のEkiIndex
	*/
	int m_iLoopOriginEkiIndex;

	/**
		環状駅設定が有効な時、通常とは反対向きに合流しているとみなします。
		この値が有効の時は環状線が○ではなく雫型の路線イメージになります。
	*/
	bool m_bLoopOpposite;

	/**
		下りカスタマイズ時刻表ビューでの発着番線表示設定
		駅時刻形式が発時刻表示・上り発着以外の時のみ有効となります

		true:この駅で発着番線を表示します
		false:この駅では発着番線を表示しません。
	*/
	bool m_bJikokuhyouTrackDisplayKudari;

	/**
		上りカスタマイズ時刻表ビューでの発着番線表示設定
		駅時刻形式が発時刻表示・下り発着以外の時のみ有効となります

		true:この駅で発着番線を表示します
		false:この駅では発着番線を表示しません。
	*/
	bool m_bJikokuhyouTrackDisplayNobori;

	/**
	ダイヤグラムビューでの発着番線表示設定
	分岐駅設定が有効の場合、この設定は無効となります。
	駅時刻形式が発着・下り着時刻・上り着時刻の時のみ有効となります、
	ただし、下り着時刻の場合は、当駅が境界線ありもしくは、路線の始発駅の場合のみ有効、
	上り着時刻の場合は一つ上の駅が境界線有もしくは、路線の終着駅の場合のみ有効となります。

	true:この駅で発着番線を表示します
	false:この駅では発着番線を表示しません。
	*/
	bool m_bDiagramTrackDisplay;

	/**
		ダイヤグラムビューで在線表を表示するときに、各番線を省略するか否か
		true:在線表で省略
		false:非省略(デフォルト)
	*/
	vector<bool> m_bDiagramTrackOmit;

	/**
		この駅から繋がる路線外始発終着駅名
		列車の始発終着駅設定で、「路線外発着」を選択した時に、
		この中から駅名を選択します。
	
	*/
	//vector<tstring> m_strOuterTerminalEkimei;
	vector<OuterTerminal> m_OuterTerminalCont;
	
	/**
		この駅から次の駅までの距離(秒)
		デフォルト値は0で、0の場合は、「ダイヤグラムの既定の駅間幅」
		を用います。
		値の範囲は0以上です。
	*/
	int m_iNextEkiDistance;

	/**
		番線編集モード時の番線表示省略設定
		駅時刻形式が発時刻表示・上り発着・下り発着の時のみ有効となります
		上り発着の場合は、下り時刻表でのみ省略、
		下り発着の場合は、上り時刻表でのみ省略されます。

		true:この駅で番線表示を省略します
		false:この駅で番線表示を省略しません。
	*/
	bool m_bJikokuhyouTrackOmit;

	/**
		分岐駅設定・環状線設定による、駅の繋がりをマッピングしたものです。
		iEkiIndexLoopに、分岐の基幹駅及び環状線の起点駅・終点駅がekiindexの降順に収まります。
		iEkiIndexBrunchOriginSideには、iEkiIndexLoopの先頭の駅を基幹駅とする派生駅がekiindexの降順に収まります。
		iEkiIndexBrunchTerminalSideには、iEkiIndexLoopの末尾の駅を基幹駅とする派生駅がekiindexの降順に収まります。
		iBrunchLoopPositionは、これらの中における、当駅の位置を表します。
		INT_MIN:当駅が起点方派生駅の場合、この値が返されます
		-1:当駅が単独駅(分岐駅及び環状線と無関係)の場合、この値が返されます
		0以上:当駅が基幹駅及び起点駅・終点駅の場合、
			iEkiIndexLoop内におけるIndexを返します。
		INT_MAX:当駅が終点方派生駅の場合、この値が返されます

		これらの要素は、駅編集及びより上位の編集が行われるたびに更新されます。
	*/
	int m_iBrunchLoopPosition;
	deque<int> m_iEkiIndexBrunchOriginSide;
	deque<int> m_iEkiIndexLoop;
	deque<int> m_iEkiIndexBrunchTerminalSide;

	/**
		起点側作業表示欄設定
		この変数で指定された数だけ、時刻表のこの駅の欄に、
		下り前作業・上り後作業表示欄が設けられます。
		0-3の間で設定されます。
	*/
	int m_iJikokuhyouOperationOrigin;
	/**
		終点側作業表示欄設定
		この変数で指定された数だけ、時刻表のこの駅の欄に、
		下り後作業・上り前作業表示欄が設けられます。
		0-3の間で設定されます。
	*/
	int m_iJikokuhyouOperationTerminal;

	/**
		(ver2.05から)
		路線起点側作業欄(下り前・上り後)において、下り増結編成開始作業・上り解結編成終了作業欄を表示するか否かの設定です。

		true:増結編成開始作業・解結編成終了作業欄を表示します。ただし、起点側作業表示欄設定が0の場合は、
			この値がtrueの場合でも表示しません。
		false:増結編成開始作業・解結編成終了作業欄を表示しません。
	*/
	bool m_bJikokuhyouOperationOriginDownBeforeUpAfter;

	/**
		(ver2.05から)
		路線起点側作業欄(下り前・上り後)において、下り解結編成終了作業・上り増結編成開始作業欄を表示するか否かの設定です。

		true:増結編成開始作業・解結編成終了作業欄を表示します。ただし、起点側作業表示欄設定が0の場合は、
			この値がtrueの場合でも表示しません。
		false:増結編成開始作業・解結編成終了作業欄を表示しません。
	*/
	bool m_bJikokuhyouOperationOriginDownAfterUpBefore;

	/**
		(ver2.05から)
		路線終点側作業欄(下り後・上り前)において、下り増結編成開始作業・上り解結編成終了作業欄を表示するか否かの設定です。

		true:増結編成開始作業・解結編成終了作業欄を表示します。ただし、終点側作業表示欄設定0の場合は、
			この値がtrueの場合でも表示しません。
		false:増結編成開始作業・解結編成終了作業欄を表示しません。
	*/
	bool m_bJikokuhyouOperationTerminalDownBeforeUpAfter;

	/**
		(ver2.05から)
		路線終点側作業欄(下り後・上り前)において、下り解結編成終了作業・上り増結編成開始作業欄を表示するか否かの設定です。

		true:増結編成開始作業・解結編成終了作業欄を表示します。ただし、終点側作業表示欄設定0の場合は、
			この値がtrueの場合でも表示しません。
		false:増結編成開始作業・解結編成終了作業欄を表示しません。
	*/
	bool m_bJikokuhyouOperationTerminalDownAfterUpBefore;

	/**
		駅名の時刻表ビュー用略称
		始発終着駅欄に用いられます
		空の場合は、駅名をそのまま使います

		規定値は、空文字列。
	 */
	tstring	m_strEkimeiJikokuhyouRyaku;

	/**
		駅名の運用一覧図ビュー用略称
		各列車線の駅名添え字に用いられます
		空の場合は、駅名の頭文字を使います

		規定値は、空文字列。
	 */
	tstring	m_strEkimeiDiagramRyaku;

	/**
		下りカスタマイズ時刻表ビューでの着時刻表示設定
		駅時刻形式が発着・下り着・下り発着の時のみ有効となります
		(ver2.06.21　駅形式の条件を整理)
		発時刻(発)：無し
		発着(発着)：あり
		下り着(着)：あり
		上り着(発)：無し→路線外始発欄がある場合のみ、例外的にありにする
		下り発着(発着)：あり
		上り発着(発)：無し

		true:この駅で着時刻を表示します
		false:この駅では着時刻を表示しません。
	*/
	bool m_bJikokuhyouChakuJikokuDisplayKudari;

	/**
		上りカスタマイズ時刻表ビューでの着時刻表示設定
		駅時刻形式が発着・上り着・上り発着の時のみ有効となります
		(ver2.06.21　駅形式の条件を整理)
		発時刻(発)：無し
		発着(発着)：あり
		下り着(発)：無し→路線外始発欄がある場合のみ、例外的にありにする
		上り着(着)：あり
		下り発着(発)：無し
		上り発着(発着)：あり

		true:この駅で着時刻を表示します
		false:この駅では着時刻を表示しません。
	*/
	bool m_bJikokuhyouChakuJikokuDisplayNobori;

	/**
		下りカスタマイズ時刻表ビューでの発時刻表示設定
		駅時刻形式が下り着以外の時のみ有効となります
		(ver2.06.21　駅形式の条件を整理)
		発時刻(発)：あり
		発着(発着)：あり
		下り着(着)：無し→路線外終着欄がある場合のみ、例外的にありにする
		上り着(発)：あり
		下り発着(発着)：あり
		上り発着(発)：あり

		true:この駅で発時刻を表示します
		false:この駅では発時刻を表示しません。
	*/
	bool m_bJikokuhyouHatsuJikokuDisplayKudari;

	/**
		上りカスタマイズ時刻表ビューでの発時刻表示設定
		駅時刻形式が上り着以外の時のみ有効となります
		(ver2.06.21　駅形式の条件を整理)
		発時刻(発)：あり
		発着(発着)：あり
		下り着(発)：あり
		上り着(着)：無し→路線外終着欄がある場合のみ、例外的にありにする
		下り発着(発)：あり
		上り発着(発着)：あり

		true:この駅で発時刻を表示します
		false:この駅では発時刻を表示しません。
	*/
	bool m_bJikokuhyouHatsuJikokuDisplayNobori;

	/**
		下りカスタマイズ時刻表ビューでの列車番号表示設定
		駅時刻形式が発着・上り着・下り発着の時のみ有効となります
		(ver2.06.21　駅形式の条件を整理)
		発時刻(発)：無し
		発着(発着)：種別変更・路線外終着ともにあり
		下り着(着)：無し→路線外終着欄がある場合のみ、例外的にありにする
		上り着(発)：種別変更のみあり(分岐駅)
		下り発着(発着)：種別変更・路線外終着ともにあり
		上り発着(発)：無し

		3:この駅で全列車の列車番号を表示します
		2:この駅で種別変更・列車番号変更を行った列車のみ列車番号を表示します
		1:この駅で種別変更を行った列車のみ列車番号を表示します
		0:この駅では列車番号を表示しません。
	*/
	int m_iJikokuhyouRessyabangouDisplayKudari;

	/**
		上りカスタマイズ時刻表ビューでの列車番号表示設定
		駅時刻形式が発着・下り着・上り発着の時のみ有効となります
		(ver2.06.21　駅形式の条件を整理)
		発時刻(発)：無し
		発着(発着)：種別変更・路線外終着ともにあり
		下り着(発)：種別変更のみあり(分岐駅)
		上り着(着)：無し→路線外終着欄がある場合のみ、例外的にありにする
		下り発着(発)：無し
		上り発着(発着)：種別変更・路線外終着ともにあり

		3:この駅で全列車の列車番号を表示します
		2:この駅で種別変更・列車番号変更を行った列車のみ列車番号を表示します
		1:この駅で種別変更を行った列車のみ列車番号を表示します
		0:この駅では列車番号を表示しません。
	*/
	int m_iJikokuhyouRessyabangouDisplayNobori;

	/**
		下りカスタマイズ時刻表ビューでの運用番号表示設定
		駅時刻形式が発着・上り着・下り発着の時のみ有効となります

		4:この駅で全列車の運用番号を表示します
		3:この駅で種別変更・列車番号変更を行った列車のみ運用番号を表示します
		2:この駅で種別変更を行った列車のみ運用番号を表示します
		1:この駅で運用番号が変わった列車のみ表示します
		0:この駅では列車番号を表示しません。
	*/
	int m_iJikokuhyouOperationNumberDisplayKudari;

	/**
		上りカスタマイズ時刻表ビューでの運用番号表示設定
		駅時刻形式が発着・下り着・上り発着の時のみ有効となります

		4:この駅で全列車の運用番号を表示します
		3:この駅で種別変更・列車番号変更を行った列車のみ運用番号を表示します
		2:この駅で種別変更を行った列車のみ運用番号を表示します
		1:この駅で運用番号が変わった列車のみ表示します
		0:この駅では列車番号を表示しません。
	*/
	int m_iJikokuhyouOperationNumberDisplayNobori;

	/**
		下りカスタマイズ時刻表ビューでの運用番号表示段数設定(ver2.05から)
		値の範囲は1-5です(規定値は1)
	*/
	int m_iJikokuhyouOperationNumberDisplayRowsKudari;

	/**
		上りカスタマイズ時刻表ビューでの運用番号表示段数設定(ver2.05から)
		値の範囲は1-5です(規定値は1)
	*/
	int m_iJikokuhyouOperationNumberDisplayRowsNobori;

	/**
		下りカスタマイズ時刻表ビューでの列車種別表示設定
		駅時刻形式が発着・上り着・下り発着の時のみ有効となります

		3:この駅で全列車の列車種別を表示します
		2:この駅で種別変更・列車番号変更を行った列車のみ列車種別を表示します
		1:この駅で種別変更を行った列車のみ列車種別を表示します
		0:この駅では列車種別を表示しません。
	*/
	int m_iJikokuhyouRessyaSyubetsuDisplayKudari;

	/**
		上りカスタマイズ時刻表ビューでの列車種別表示設定
		駅時刻形式が発着・下り着・上り発着の時のみ有効となります

		3:この駅で全列車の列車種別を表示します
		2:この駅で種別変更・列車番号変更を行った列車のみ列車種別を表示します
		1:この駅で種別変更を行った列車のみ列車種別を表示します
		0:この駅では列車種別を表示しません。
	*/
	int m_iJikokuhyouRessyaSyubetsuDisplayNobori;

	/**
		下りカスタマイズ時刻表ビューでの列車名・号数表示設定
		駅時刻形式が発着・上り着・下り発着の時のみ有効となります

		3:この駅で全列車の列車名・号数を表示します
		2:この駅で種別変更・列車番号変更を行った列車のみ列車名・号数を表示します
		1:この駅で種別変更を行った列車のみ列車名・号数を表示します
		0:この駅では列車名・号数を表示しません。
	*/
	int m_iJikokuhyouRessyameiDisplayKudari;

	/**
		上りカスタマイズ時刻表ビューでの列車名・号数表示設定
		駅時刻形式が発着・下り着・上り発着の時のみ有効となります

		3:この駅で全列車の列車名・号数を表示します
		2:この駅で種別変更・列車番号変更を行った列車のみ列車名・号数を表示します
		1:この駅で種別変更を行った列車のみ列車名・号数を表示します
		0:この駅では列車名・号数を表示しません。
	*/
	int m_iJikokuhyouRessyameiDisplayNobori;

	/**
		下りカスタマイズ時刻表ビューでの路線外・前列車始発駅表示設定
		駅時刻形式が発着・上り着・下り発着の時のみ有効となります

		true:この駅で路線外・前列車始発駅を表示します
		false:この駅では路線外・前列車始発駅を表示しません。
	*/
	bool m_bJikokuhyouOuterSihatsuDisplayKudari;

	/**
		下りカスタマイズ時刻表ビューでの路線外・次列車終着駅表示設定
		駅時刻形式が発着・下り着・下り発着の時のみ有効となります

		true:この駅で路線外・次列車終着駅を表示します
		false:この駅では路線外・次列車終着駅を表示しません。
	*/
	bool m_bJikokuhyouOuterShuchakuDisplayKudari;

	/**
		上りカスタマイズ時刻表ビューでの路線外・前列車始発駅表示設定
		駅時刻形式が発着・下り着・上り発着の時のみ有効となります

		true:この駅で路線外・前列車始発駅を表示します
		false:この駅では路線外・前列車始発駅を表示しません。
	*/
	bool m_bJikokuhyouOuterSihatsuDisplayNobori;

	/**
		上りカスタマイズ時刻表ビューでの路線外・次列車終着駅表示設定
		駅時刻形式が発着・上り着・上り発着の時のみ有効となります

		true:この駅で路線外・次列車終着駅を表示します
		false:この駅では路線外・次列車終着駅を表示しません。
	*/
	bool m_bJikokuhyouOuterShuchakuDisplayNobori;

	/**
		ダイヤグラムビューにおける、この駅から次の駅までの背景色設定です
		0:基本色を使用
		1-4:個別色を使用
	*/
	int m_iDiagramColorNextEki;

	/**
		箱ダイヤにおいて、この駅の時刻を表示するか否か
	*/
	bool m_bOperationTableDisplayJikoku;


	/**
		下りカスタマイズ時刻表ビューでの入線時刻表示設定
		駅時刻形式が発着・上り着・下り発着の時のみ有効となります

		true:この駅で入線時刻を表示します
		false:この駅では入線時刻を表示しません。
	*/
	bool m_bJikokuhyouNyuusenJikokuDisplayKudari;

	/**
		上りカスタマイズ時刻表ビューでの入線時刻表示設定
		駅時刻形式が発着・下り着・上り発着の時のみ有効となります

		true:この駅で入線時刻を表示します
		false:この駅では入線時刻を表示しません。
	*/
	bool m_bJikokuhyouNyuusenJikokuDisplayNobori;

	/**
		下りカスタマイズ時刻表ビューでの前列車列車番号表示設定
		路線外始発状に表示される列車の前列車での列車情報を表示します。
		路線外・前列車始発駅表示設定が非表示の場合、この項も表示されません。
		駅時刻形式が発着・上り着・下り発着の時のみ有効となります

		3:この駅で路線外始発状の全列車の列車番号を表示します
		2:この駅で路線外始発状の内、種別変更・列車番号変更を行った列車のみ列車番号を表示します
		1:この駅で路線外始発状の内、種別変更を行った列車のみ列車番号を表示します
		0:この駅では列車番号を表示しません。
	*/
	int m_iJikokuhyouPrevRessyabangouDisplayKudari;

	/**
		上りカスタマイズ時刻表ビューでの前列車列車番号表示設定
		路線外始発状に表示される列車の前列車での列車情報を表示します。
		路線外・前列車始発駅表示設定が非表示の場合、この項も表示されません。
		駅時刻形式が発着・下り着・上り発着の時のみ有効となります

		3:この駅で路線外始発状の全列車の列車番号を表示します
		2:この駅で路線外始発状の内、種別変更・列車番号変更を行った列車のみ列車番号を表示します
		1:この駅で路線外始発状の内、種別変更を行った列車のみ列車番号を表示します
		0:この駅では列車番号を表示しません。
	*/
	int m_iJikokuhyouPrevRessyabangouDisplayNobori;

	/**
		下りカスタマイズ時刻表ビューでの前列車運用番号表示設定
		路線外始発状に表示される列車の前列車での列車情報を表示します。
		路線外・前列車始発駅表示設定が非表示の場合、この項も表示されません。
		駅時刻形式が発着・上り着・下り発着の時のみ有効となります

		4:この駅で路線外始発状の全列車の運用番号を表示します
		3:この駅で路線外始発状の内、種別変更・列車番号変更を行った列車のみ運用番号を表示します
		2:この駅で路線外始発状の内、種別変更を行った列車のみ運用番号を表示します
		1:この駅で路線外始発状の内、運用番号が変わった列車のみ表示します
		0:この駅では列車番号を表示しません。
	*/
	int m_iJikokuhyouPrevOperationNumberDisplayKudari;

	/**
		上りカスタマイズ時刻表ビューでの前列車運用番号表示設定
		路線外始発状に表示される列車の前列車での列車情報を表示します。
		路線外・前列車始発駅表示設定が非表示の場合、この項も表示されません。
		駅時刻形式が発着・下り着・上り発着の時のみ有効となります

		4:この駅で路線外始発状の全列車の運用番号を表示します
		3:この駅で路線外始発状の内、種別変更・列車番号変更を行った列車のみ運用番号を表示します
		2:この駅で路線外始発状の内、種別変更を行った列車のみ運用番号を表示します
		1:この駅で路線外始発状の内、運用番号が変わった列車のみ表示します
		0:この駅では列車番号を表示しません。
	*/
	int m_iJikokuhyouPrevOperationNumberDisplayNobori;

	/**
		下りカスタマイズ時刻表ビューでの前列車運用番号表示段数設定
		値の範囲は1-5です(規定値は1)
	*/
	int m_iJikokuhyouPrevOperationNumberDisplayRowsKudari;

	/**
		上りカスタマイズ時刻表ビューでの前列車運用番号表示段数設定
		値の範囲は1-5です(規定値は1)
	*/
	int m_iJikokuhyouPrevOperationNumberDisplayRowsNobori;

	/**
		下りカスタマイズ時刻表ビューでの前列車列車種別表示設定
		路線外始発状に表示される列車の前列車での列車情報を表示します。
		路線外・前列車始発駅表示設定が非表示の場合、この項も表示されません。
		駅時刻形式が発着・上り着・下り発着の時のみ有効となります

		3:この駅で路線外始発状の全列車の列車種別を表示します
		2:この駅で路線外始発状の内、種別変更・列車番号変更を行った列車のみ列車種別を表示します
		1:この駅で路線外始発状の内、種別変更を行った列車のみ列車種別を表示します
		0:この駅では列車種別を表示しません。
	*/
	int m_iJikokuhyouPrevRessyaSyubetsuDisplayKudari;

	/**
		上りカスタマイズ時刻表ビューでの前列車列車種別表示設定
		路線外始発状に表示される列車の前列車での列車情報を表示します。
		路線外・前列車始発駅表示設定が非表示の場合、この項も表示されません。
		駅時刻形式が発着・下り着・上り発着の時のみ有効となります

		3:この駅で路線外始発状の全列車の列車種別を表示します
		2:この駅で路線外始発状の内、種別変更・列車番号変更を行った列車のみ列車種別を表示します
		1:この駅で路線外始発状の内、種別変更を行った列車のみ列車種別を表示します
		0:この駅では列車種別を表示しません。
	*/
	int m_iJikokuhyouPrevRessyaSyubetsuDisplayNobori;

	/**
		下りカスタマイズ時刻表ビューでの前列車列車名・号数表示設定
		路線外始発状に表示される列車の前列車での列車情報を表示します。
		路線外・前列車始発駅表示設定が非表示の場合、この項も表示されません。
		駅時刻形式が発着・上り着・下り発着の時のみ有効となります

		3:この駅で路線外始発状の全列車の列車名・号数を表示します
		2:この駅で路線外始発状の内、種別変更・列車番号変更を行った列車のみ列車名・号数を表示します
		1:この駅で路線外始発状の内、種別変更を行った列車のみ列車名・号数を表示します
		0:この駅では列車名・号数を表示しません。
	*/
	int m_iJikokuhyouPrevRessyameiDisplayKudari;

	/**
		上りカスタマイズ時刻表ビューでの前列車列車名・号数表示設定
		路線外始発状に表示される列車の前列車での列車情報を表示します。
		路線外・前列車始発駅表示設定が非表示の場合、この項も表示されません。
		駅時刻形式が発着・下り着・上り発着の時のみ有効となります

		3:この駅で路線外始発状の全列車の列車名・号数を表示します
		2:この駅で路線外始発状の内、種別変更・列車番号変更を行った列車のみ列車名・号数を表示します
		1:この駅で路線外始発状の内、種別変更を行った列車のみ列車名・号数を表示します
		0:この駅では列車名・号数を表示しません。
	*/
	int m_iJikokuhyouPrevRessyameiDisplayNobori;

	/**
		交差支障チェックルール
	*/
	vector<CrossingCheckRule> m_CrossingCheckRuleCont;
	
	///@}
private:
	// ********************************
	///@name 包含
	// ********************************
	///@{
	///@}

	CXEkiTrack2Cont m_CentDedEkiTrack2Cont;

// ********************************
//	コンストラクタ
// ********************************
 public:
	CentDedEki() ;
	
	/**
	 @param strEkimei [in]
		駅名
	 @param eEkijikokukeisiki [in]
		駅時刻形式。
	 @param eEkikibo [in]
		『駅規模』を表す列挙です。
	 @param bKyoukaisen [in]
		境界線あり。
	  この属性が true の駅では、時刻表画面の
		下り方向の下に、太い境界線を描画します。
	  この属性は、駅ビューと時刻表ビューに適用されます。
	  
	@param eDiagramRessyajouhouHyoujiKudari
		ダイヤグラム列車情報表示（下り）
	@param eDiagramRessyajouhouHyoujiNobori
		ダイヤグラム列車情報表示（上り）
	*/
	CentDedEki( const tstring& strEkimei , 
			EEkijikokukeisiki	eEkijikokukeisiki ,
			EEkikibo	eEkikibo , 
			bool bKyoukaisen , 
			EDiagramRessyajouhouHyouji eDiagramRessyajouhouHyoujiKudari 
				= EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Origin ,
			EDiagramRessyajouhouHyouji eDiagramRessyajouhouHyoujiNobori 
				= EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Origin ) ;

	/** 
		このオブジェクトが、親オブジェクトCentDedEkiCont の
		子である場合で、代入元が CentDedEkiCont::set() でエラーに
		なる場合、例外スローになります。
	@param value 
		代入元
	@exception LException 
	*/
	CentDedEki& operator=( const CentDedEki& value ) ;


	

public:
	// ********************************
	///@name CParentBase-操作
	// ********************************
	///@{
	/** ○親オブジェクトの変更(setParent()):  adjust()を実行する */
	virtual void setParent( CParentBase* pParent ) ;
	///@}

public:
	// ********************************
	///@name CentDedEki-属性
	// ********************************
	///@{
	/** @see m_strEkimei */
	tstring	getEkimei()const{	return m_strEkimei ;};
	/** @see m_strEkimei */
	void setEkimei( const tstring& value ){
		m_strEkimei = value ; } ;
	/** @see m_eEkijikokukeisiki */
	EEkijikokukeisiki	getEkijikokukeisiki()const{
		return 	m_eEkijikokukeisiki ;};
	/** @see m_eEkijikokukeisiki */
	void setEkijikokukeisiki( EEkijikokukeisiki	value ){
		m_eEkijikokukeisiki = value ; } ;
	/** @see m_eEkikibo */
	EEkikibo	getEkikibo()const{	return 	m_eEkikibo ;};
	/** @see m_eEkikibo */
	void setEkikibo( EEkikibo value ){
		m_eEkikibo = value ; } ;
	/** @see m_bKyoukaisen */
	bool getKyoukaisen()const{	return m_bKyoukaisen ; };
	/** @see m_bKyoukaisen */
	void setKyoukaisen( bool value ){	m_bKyoukaisen = value ; } ;

	/** @see m_eDiagramRessyajouhouHyoujiKudari */
	EDiagramRessyajouhouHyouji getDiagramRessyajouhouHyoujiKudari()const
	{	return m_eDiagramRessyajouhouHyoujiKudari ;};
	/** @see m_eDiagramRessyajouhouHyoujiKudari */
	void setDiagramRessyajouhouHyoujiKudari( EDiagramRessyajouhouHyouji value )
	{	m_eDiagramRessyajouhouHyoujiKudari = value ;};
	/** @see m_eDiagramRessyajouhouHyoujiNobori */
	EDiagramRessyajouhouHyouji getDiagramRessyajouhouHyoujiNobori()const
	{	return m_eDiagramRessyajouhouHyoujiNobori ;};
	/** @see m_eDiagramRessyajouhouHyoujiNobori */
	void setDiagramRessyajouhouHyoujiNobori( EDiagramRessyajouhouHyouji value )
	{	m_eDiagramRessyajouhouHyoujiNobori = value ;};

	/** @see m_iDownMain */
	int getDownMain()const
	{
		return m_iDownMain;
	};
	/** @see m_iDownMain */
	void setDownMain(int value)
	{
		m_iDownMain = value;
	};
	/** @see m_iUpMain */
	int getUpMain()const
	{
		return m_iUpMain;
	};
	/** @see m_iUpMain */
	void setUpMain(int value)
	{
		m_iUpMain = value;
	};
	/** @see m_iUpMain,m_iDownMain */
	int getMainTrack(ERessyahoukou eRessyahoukou)const
	{
		if (eRessyahoukou == Ressyahoukou_Kudari)
		{
			return m_iDownMain;
		}
		else 
		{
			return m_iUpMain;
		}
	};
	/** @see m_iID */
	int getID()const
	{
		return m_iID;
	};
	/** @see m_iID */
	void setID(int value)
	{
		m_iID = value;
	};
	
	/** @see m_iBrunchCoreEkiIndex */
	int getBrunchCoreEkiIndex()const
	{
		return m_iBrunchCoreEkiIndex;
	};
	/** @see m_iBrunchCoreEkiIndex */
	void setBrunchCoreEkiIndex(int value)
	{
		m_iBrunchCoreEkiIndex = value;
	};
	/** @see m_bBrunchOpposite */
	bool getBrunchOpposite()const { return m_bBrunchOpposite; };
	/** @see m_bBrunchOpposite */
	void setBrunchOpposite(bool value) { m_bBrunchOpposite = value; };
	/** @see m_iLoopOriginEkiIndex */
	int getLoopOriginEkiIndex()const
	{
		return m_iLoopOriginEkiIndex;
	};
	/** @see m_iLoopOriginEkiIndex */
	void setLoopOriginEkiIndex(int value)
	{
		m_iLoopOriginEkiIndex = value;
	};
	/** @see m_bLoopOpposite */
	bool getLoopOpposite()const { return m_bLoopOpposite; };
	/** @see m_bLoopOpposite */
	void setLoopOpposite(bool value) { m_bLoopOpposite = value; };

	/** @see m_bJikokuhyouTrackDisplayKudari */
	bool getJikokuhyouTrackDisplayKudari()const { return m_bJikokuhyouTrackDisplayKudari; };
	/** @see m_bJikokuhyouTrackDisplayKudari */
	void setJikokuhyouTrackDisplayKudari(bool value) { m_bJikokuhyouTrackDisplayKudari = value; };
	/** @see m_bJikokuhyouTrackDisplayNobori */
	bool getJikokuhyouTrackDisplayNobori()const { return m_bJikokuhyouTrackDisplayNobori; };
	/** @see m_bJikokuhyouTrackDisplayNobori */
	void setJikokuhyouTrackDisplayNobori(bool value) { m_bJikokuhyouTrackDisplayNobori = value; };

	/** @see m_bDiagramTrackDisplay */
	bool getDiagramTrackDisplay()const { return m_bDiagramTrackDisplay; };
	/** @see m_bDiagramTrackDisplay */
	void setDiagramTrackDisplay(bool value) { m_bDiagramTrackDisplay = value; };

	/** @see m_bDiagramTrackOmit */
	vector<bool> getDiagramTrackOmit()const { return m_bDiagramTrackOmit; };
	/** @see m_bDiagramTrackOmit */
	bool getDiagramTrackOmit(int iIndex)const;
	/** @see m_bDiagramTrackOmit */
	void setDiagramTrackOmit(vector<bool> value) { m_bDiagramTrackOmit = value; };
	/** @see m_bDiagramTrackOmit */
	void addDiagramTrackOmit(bool value) { m_bDiagramTrackOmit.push_back(value); };

	OuterTerminal getOuterTerminal(int iIndex)const;
	tstring getOuterTerminalEkimei(int iIndex)const;
	tstring getOuterTerminalJikokuRyaku(int iIndex, bool bEkimeiIfEmpty = false)const;
	tstring getOuterTerminalDiaRyaku(int iIndex, bool bEkimeiIfEmpty = false)const;
	void setOuterTerminalEkimei(const OuterTerminal& value, int iIndex);
	void insertOuterTerminalEkimei(const OuterTerminal& value, int iIndex = INT_MAX);
	void eraseOuterTerminalEkimei(int iIndex ,int iSize);
	int getOuterTerminalEkimeiCount()const;
	vector<OuterTerminal> getOuterTerminalEkimeiCont()const;
	/**
		路線外発着駅名の中から、strEkimeiと一致するものを探し、そのIndexを返します。
		見つからなかった場合は、-1を返します。
	*/
	int searchOuterTerminalEkimei(const tstring& strEkimei);

	/**
		路線外発着駅名に新しい値を追加します。
		追加に成功した場合、そのIndexを返します。
	*/
	int addOuterTerminalEkimei(const OuterTerminal& strEkimei);

	/** @see m_iNextEkiDistance */
	int getNextEkiDistance()const
	{
		return m_iNextEkiDistance;
	};
	/** @see m_iNextEkiDistance */
	void setNextEkiDistance(int value)
	{
		if (value < 0)
		{
			m_iNextEkiDistance = 0;
		}
		else
		{
			m_iNextEkiDistance = value;
		}
	};
	/** @see m_iNextEkiDistance */
	bool getNextEkiDistanceIsDefault()const
	{
		return m_iNextEkiDistance <= 0;
	};

	/** @see m_bJikokuhyouTrackOmit */
	bool getJikokuhyouTrackOmit()const { return m_bJikokuhyouTrackOmit; };
	/** @see m_bJikokuhyouTrackOmit */
	void setJikokuhyouTrackOmit(bool value) { m_bJikokuhyouTrackOmit = value; };

	/** @see m_iBrunchLoopPosition */
	int getBrunchLoopPosition()const
	{
		return m_iBrunchLoopPosition;
	};
	/** @see m_iBrunchLoopPosition */
	void setBrunchLoopPosition(int value)
	{
		m_iBrunchLoopPosition = value;
	};
	/** @see m_iEkiIndexBrunchOriginSide */
	deque<int> getEkiIndexBrunchOriginSide()const
	{
		return m_iEkiIndexBrunchOriginSide;
	};
	/** @see m_iEkiIndexBrunchOriginSide */
	void setEkiIndexBrunchOriginSide(deque<int> value)
	{
		m_iEkiIndexBrunchOriginSide = value;
	};
	/** @see m_iEkiIndexBrunchOriginSide */
	void clearEkiIndexBrunchOriginSide()
	{
		m_iEkiIndexBrunchOriginSide.clear();
	};
	/** @see m_iEkiIndexLoop */
	deque<int> getEkiIndexLoop()const
	{
		return m_iEkiIndexLoop;
	};
	/** @see m_iEkiIndexLoop */
	void setEkiIndexLoop(deque<int> value)
	{
		m_iEkiIndexLoop = value;
	};
	/** @see m_iEkiIndexLoop */
	void clearEkiIndexLoop()
	{
		m_iEkiIndexLoop.clear();
	};
	/** @see m_iEkiIndexBrunchTerminalSide */
	deque<int> getEkiIndexBrunchTerminalSide()const
	{
		return m_iEkiIndexBrunchTerminalSide;
	};
	/** @see m_iEkiIndexBrunchTerminalSide */
	void setEkiIndexBrunchTerminalSide(deque<int> value)
	{
		m_iEkiIndexBrunchTerminalSide = value;
	};
	/** @see m_iEkiIndexBrunchTerminalSide */
	void clearEkiIndexBrunchTerminalSide()
	{
		m_iEkiIndexBrunchTerminalSide.clear();
	};

	/** @see m_iJikokuhyouOperationOrigin */
	int getJikokuhyouOperationOrigin()const
	{
		return m_iJikokuhyouOperationOrigin;
	};
	/** @see m_iJikokuhyouOperationOrigin */
	void setJikokuhyouOperationOrigin(int value)
	{
		m_iJikokuhyouOperationOrigin = value;
	};

	/** @see m_iJikokuhyouOperationTerminal */
	int getJikokuhyouOperationTerminal()const
	{
		return m_iJikokuhyouOperationTerminal;
	};
	/** @see m_iJikokuhyouOperationTerminal */
	void setJikokuhyouOperationTerminal(int value)
	{
		m_iJikokuhyouOperationTerminal = value;
	};

	/** @see m_bJikokuhyouOperationOriginDownBeforeUpAfter */
	bool getJikokuhyouOperationOriginDownBeforeUpAfter()const
	{
		return m_bJikokuhyouOperationOriginDownBeforeUpAfter;
	};
	/** @see m_bJikokuhyouOperationOriginDownBeforeUpAfter */
	void setJikokuhyouOperationOriginDownBeforeUpAfter(bool value)
	{
		m_bJikokuhyouOperationOriginDownBeforeUpAfter = value;
	};

	/** @see m_bJikokuhyouOperationOriginDownAfterUpBefore */
	bool getJikokuhyouOperationOriginDownAfterUpBefore()const
	{
		return m_bJikokuhyouOperationOriginDownAfterUpBefore;
	};
	/** @see m_bJikokuhyouOperationOriginDownAfterUpBefore */
	void setJikokuhyouOperationOriginDownAfterUpBefore(bool value)
	{
		m_bJikokuhyouOperationOriginDownAfterUpBefore = value;
	};

	/** @see m_bJikokuhyouOperationTerminalDownBeforeUpAfter */
	bool getJikokuhyouOperationTerminalDownBeforeUpAfter()const
	{
		return m_bJikokuhyouOperationTerminalDownBeforeUpAfter;
	};
	/** @see m_bJikokuhyouOperationTerminalDownBeforeUpAfter */
	void setJikokuhyouOperationTerminalDownBeforeUpAfter(bool value)
	{
		m_bJikokuhyouOperationTerminalDownBeforeUpAfter = value;
	};

	/** @see m_bJikokuhyouOperationTerminalDownAfterUpBefore */
	bool getJikokuhyouOperationTerminalDownAfterUpBefore()const
	{
		return m_bJikokuhyouOperationTerminalDownAfterUpBefore;
	};
	/** @see m_bJikokuhyouOperationTerminalDownAfterUpBefore */
	void setJikokuhyouOperationTerminalDownAfterUpBefore(bool value)
	{
		m_bJikokuhyouOperationTerminalDownAfterUpBefore = value;
	};

	/** @see m_strEkimeiJikokuhyouRyaku */
	tstring	getEkimeiJikokuhyouRyaku(bool bEkimeiIfEmpty=false)const;
	/** @see m_strEkimeiJikokuhyouRyaku */
	void setEkimeiJikokuhyouRyaku(const tstring& value) {
		m_strEkimeiJikokuhyouRyaku = value;
	};
	/** @see m_strEkimeiDiagramRyaku */
	tstring	getEkimeiDiagramRyaku(bool bEkimeiIfEmpty = false)const;
	/** @see m_strEkimeiDiagramRyaku */
	void setEkimeiDiagramRyaku(const tstring& value) {
		m_strEkimeiDiagramRyaku = value;
	};

	/** @see m_bJikokuhyouChakuJikokuDisplayKudari */
	bool getJikokuhyouChakuJikokuDisplayKudari()const { return m_bJikokuhyouChakuJikokuDisplayKudari; };
	/** @see m_bJikokuhyouChakuJikokuDisplayKudari */
	void setJikokuhyouChakuJikokuDisplayKudari(bool value) { m_bJikokuhyouChakuJikokuDisplayKudari = value; };
	/** @see m_bJikokuhyouChakuJikokuDisplayNobori */
	bool getJikokuhyouChakuJikokuDisplayNobori()const { return m_bJikokuhyouChakuJikokuDisplayNobori; };
	/** @see m_bJikokuhyouChakuJikokuDisplayNobori */
	void setJikokuhyouChakuJikokuDisplayNobori(bool value) { m_bJikokuhyouChakuJikokuDisplayNobori = value; };
	/** @see m_bJikokuhyouChakuJikokuDisplay */
	bool getJikokuhyouChakuJikokuDisplay(ERessyahoukou eRessyahoukou)const 
	{ 
		if (eRessyahoukou == ERessyahoukou::Ressyahoukou_Nobori)
		{
			return m_bJikokuhyouChakuJikokuDisplayNobori;
		}
		return m_bJikokuhyouChakuJikokuDisplayKudari; 
	};

	/** @see m_bJikokuhyouHatsuJikokuDisplayKudari */
	bool getJikokuhyouHatsuJikokuDisplayKudari()const { return m_bJikokuhyouHatsuJikokuDisplayKudari; };
	/** @see m_bJikokuhyouHatsuJikokuDisplayKudari */
	void setJikokuhyouHatsuJikokuDisplayKudari(bool value) { m_bJikokuhyouHatsuJikokuDisplayKudari = value; };
	/** @see m_bJikokuhyouHatsuJikokuDisplayNobori */
	bool getJikokuhyouHatsuJikokuDisplayNobori()const { return m_bJikokuhyouHatsuJikokuDisplayNobori; };
	/** @see m_bJikokuhyouHatsuJikokuDisplayNobori */
	void setJikokuhyouHatsuJikokuDisplayNobori(bool value) { m_bJikokuhyouHatsuJikokuDisplayNobori = value; };
	/** @see m_bJikokuhyouHatsuJikokuDisplay */
	bool getJikokuhyouHatsuJikokuDisplay(ERessyahoukou eRessyahoukou)const
	{
		if (eRessyahoukou == ERessyahoukou::Ressyahoukou_Nobori)
		{
			return m_bJikokuhyouHatsuJikokuDisplayNobori;
		}
		return m_bJikokuhyouHatsuJikokuDisplayKudari;
	};

	/** @see m_iJikokuhyouRessyabangouDisplayKudari */
	int getJikokuhyouRessyabangouDisplayKudari()const { return m_iJikokuhyouRessyabangouDisplayKudari; };
	/** @see m_iJikokuhyouRessyabangouDisplayKudari */
	void setJikokuhyouRessyabangouDisplayKudari(int value) { m_iJikokuhyouRessyabangouDisplayKudari = value; };
	/** @see m_iJikokuhyouRessyabangouDisplayNobori */
	int getJikokuhyouRessyabangouDisplayNobori()const { return m_iJikokuhyouRessyabangouDisplayNobori; };
	/** @see m_iJikokuhyouRessyabangouDisplayNobori */
	void setJikokuhyouRessyabangouDisplayNobori(int value) { m_iJikokuhyouRessyabangouDisplayNobori = value; };
	/** @see m_iJikokuhyouRessyabangouDisplayNobori */
	int getJikokuhyouRessyabangouDisplay(ERessyahoukou eRessyahoukou)const
	{
		if (eRessyahoukou == ERessyahoukou::Ressyahoukou_Nobori)
		{
			return m_iJikokuhyouRessyabangouDisplayNobori;
		}
		return m_iJikokuhyouRessyabangouDisplayKudari;
	};

	/** @see m_iJikokuhyouOperationNumberDisplayKudari */
	int getJikokuhyouOperationNumberDisplayKudari()const { return m_iJikokuhyouOperationNumberDisplayKudari; };
	/** @see m_iJikokuhyouOperationNumberDisplayKudari */
	void setJikokuhyouOperationNumberDisplayKudari(int value) { m_iJikokuhyouOperationNumberDisplayKudari = value; };
	/** @see m_iJikokuhyouOperationNumberDisplayNobori */
	int getJikokuhyouOperationNumberDisplayNobori()const { return m_iJikokuhyouOperationNumberDisplayNobori; };
	/** @see m_iJikokuhyouOperationNumberDisplayNobori */
	void setJikokuhyouOperationNumberDisplayNobori(int value) { m_iJikokuhyouOperationNumberDisplayNobori = value; };
	/** @see m_iJikokuhyouOperationNumberDisplayNobori */
	int getJikokuhyouOperationNumberDisplay(ERessyahoukou eRessyahoukou)const
	{
		if (eRessyahoukou == ERessyahoukou::Ressyahoukou_Nobori)
		{
			return m_iJikokuhyouOperationNumberDisplayNobori;
		}
		return m_iJikokuhyouOperationNumberDisplayKudari;
	};

	/** @see m_iJikokuhyouOperationNumberDisplayRowsKudari */
	int getJikokuhyouOperationNumberDisplayRowsKudari()const { return m_iJikokuhyouOperationNumberDisplayRowsKudari; };
	/** @see m_iJikokuhyouOperationNumberDisplayRowsKudari */
	void setJikokuhyouOperationNumberDisplayRowsKudari(int value) { m_iJikokuhyouOperationNumberDisplayRowsKudari = value; };
	/** @see m_iJikokuhyouOperationNumberDisplayRowsNobori */
	int getJikokuhyouOperationNumberDisplayRowsNobori()const { return m_iJikokuhyouOperationNumberDisplayRowsNobori; };
	/** @see m_iJikokuhyouOperationNumberDisplayRowsNobori */
	void setJikokuhyouOperationNumberDisplayRowsNobori(int value) { m_iJikokuhyouOperationNumberDisplayRowsNobori = value; };
	int getJikokuhyouOperationNumberDisplayRows(ERessyahoukou eRessyahoukou)const
	{
		if (eRessyahoukou == ERessyahoukou::Ressyahoukou_Nobori)
		{
			return m_iJikokuhyouOperationNumberDisplayRowsNobori;
		}
		return m_iJikokuhyouOperationNumberDisplayRowsKudari;
	};

	/** @see m_iJikokuhyouRessyaSyubetsuDisplayKudari */
	int getJikokuhyouRessyaSyubetsuDisplayKudari()const { return m_iJikokuhyouRessyaSyubetsuDisplayKudari; };
	/** @see m_iJikokuhyouRessyaSyubetsuDisplayKudari */
	void setJikokuhyouRessyaSyubetsuDisplayKudari(int value) { m_iJikokuhyouRessyaSyubetsuDisplayKudari = value; };
	/** @see m_iJikokuhyouRessyaSyubetsuDisplayNobori */
	int getJikokuhyouRessyaSyubetsuDisplayNobori()const { return m_iJikokuhyouRessyaSyubetsuDisplayNobori; };
	/** @see m_iJikokuhyouRessyaSyubetsuDisplayNobori */
	void setJikokuhyouRessyaSyubetsuDisplayNobori(int value) { m_iJikokuhyouRessyaSyubetsuDisplayNobori = value; };
	/** @see m_iJikokuhyouRessyaSyubetsuDisplayNobori */
	int getJikokuhyouRessyaSyubetsuDisplay(ERessyahoukou eRessyahoukou)const
	{
		if (eRessyahoukou == ERessyahoukou::Ressyahoukou_Nobori)
		{
			return m_iJikokuhyouRessyaSyubetsuDisplayNobori;
		}
		return m_iJikokuhyouRessyaSyubetsuDisplayKudari;
	};

	/** @see m_iJikokuhyouRessyameiDisplayKudari */
	int getJikokuhyouRessyameiDisplayKudari()const { return m_iJikokuhyouRessyameiDisplayKudari; };
	/** @see m_iJikokuhyouRessyameiDisplayKudari */
	void setJikokuhyouRessyameiDisplayKudari(int value) { m_iJikokuhyouRessyameiDisplayKudari = value; };
	/** @see m_iJikokuhyouRessyameiDisplayNobori */
	int getJikokuhyouRessyameiDisplayNobori()const { return m_iJikokuhyouRessyameiDisplayNobori; };
	/** @see m_iJikokuhyouRessyameiDisplayNobori */
	void setJikokuhyouRessyameiDisplayNobori(int value) { m_iJikokuhyouRessyameiDisplayNobori = value; };
	/** @see m_iJikokuhyouRessyameiDisplayNobori */
	int getJikokuhyouRessyameiDisplay(ERessyahoukou eRessyahoukou)const
	{
		if (eRessyahoukou == ERessyahoukou::Ressyahoukou_Nobori)
		{
			return m_iJikokuhyouRessyameiDisplayNobori;
		}
		return m_iJikokuhyouRessyameiDisplayKudari;
	};

	/** @see m_bJikokuhyouOuterSihatsuDisplayKudari */
	bool getJikokuhyouOuterSihatsuDisplayKudari()const { return m_bJikokuhyouOuterSihatsuDisplayKudari; };
	/** @see m_bJikokuhyouOuterSihatsuDisplayKudari */
	void setJikokuhyouOuterSihatsuDisplayKudari(bool value) { m_bJikokuhyouOuterSihatsuDisplayKudari = value; };

	/** @see m_bJikokuhyouOuterShuchakuDisplayKudari */
	bool getJikokuhyouOuterShuchakuDisplayKudari()const { return m_bJikokuhyouOuterShuchakuDisplayKudari; };
	/** @see m_bJikokuhyouOuterShuchakuDisplayKudari */
	void setJikokuhyouOuterShuchakuDisplayKudari(bool value) { m_bJikokuhyouOuterShuchakuDisplayKudari = value; };

	/** @see m_bJikokuhyouOuterSihatsuDisplayNobori */
	bool getJikokuhyouOuterSihatsuDisplayNobori()const { return m_bJikokuhyouOuterSihatsuDisplayNobori; };
	/** @see m_bJikokuhyouOuterSihatsuDisplayNobori */
	void setJikokuhyouOuterSihatsuDisplayNobori(bool value) { m_bJikokuhyouOuterSihatsuDisplayNobori = value; };

	/** @see m_bJikokuhyouOuterShuchakuDisplayNobori */
	bool getJikokuhyouOuterShuchakuDisplayNobori()const { return m_bJikokuhyouOuterShuchakuDisplayNobori; };
	/** @see m_bJikokuhyouOuterShuchakuDisplayNobori */
	void setJikokuhyouOuterShuchakuDisplayNobori(bool value) { m_bJikokuhyouOuterShuchakuDisplayNobori = value; };

	/** @see m_iDiagramColorNextEki */
	int getDiagramColorNextEki()const
	{
		return m_iDiagramColorNextEki;
	};
	/** @see m_iDiagramColorNextEki */
	void setDiagramColorNextEki(int value)
	{
		m_iDiagramColorNextEki = value;
	};

	/** @see m_bOperationTableDisplayJikoku */
	bool getOperationTableDisplayJikoku()const { return m_bOperationTableDisplayJikoku; };
	/** @see m_bOperationTableDisplayJikoku */
	void setOperationTableDisplayJikoku(bool value) { m_bOperationTableDisplayJikoku = value; };

	/** @see m_bJikokuhyouNyuusenJikokuDisplayKudari */
	bool getJikokuhyouNyuusenJikokuDisplayKudari()const { return m_bJikokuhyouNyuusenJikokuDisplayKudari; };
	/** @see m_bJikokuhyouNyuusenJikokuDisplayKudari */
	void setJikokuhyouNyuusenJikokuDisplayKudari(bool value) { m_bJikokuhyouNyuusenJikokuDisplayKudari = value; };
	/** @see m_bJikokuhyouNyuusenJikokuDisplayNobori */
	bool getJikokuhyouNyuusenJikokuDisplayNobori()const { return m_bJikokuhyouNyuusenJikokuDisplayNobori; };
	/** @see m_bJikokuhyouNyuusenJikokuDisplayNobori */
	void setJikokuhyouNyuusenJikokuDisplayNobori(bool value) { m_bJikokuhyouNyuusenJikokuDisplayNobori = value; };
	/** @see m_bJikokuhyouNyuusenJikokuDisplay */
	bool getJikokuhyouNyuusenJikokuDisplay(ERessyahoukou eRessyahoukou)const
	{
		if (eRessyahoukou == ERessyahoukou::Ressyahoukou_Nobori)
		{
			return m_bJikokuhyouNyuusenJikokuDisplayNobori;
		}
		return m_bJikokuhyouNyuusenJikokuDisplayKudari;
	};

	/** @see m_iJikokuhyouPrevRessyabangouDisplayKudari */
	int getJikokuhyouPrevRessyabangouDisplayKudari()const { return m_iJikokuhyouPrevRessyabangouDisplayKudari; };
	/** @see m_iJikokuhyouPrevRessyabangouDisplayKudari */
	void setJikokuhyouPrevRessyabangouDisplayKudari(int value) { m_iJikokuhyouPrevRessyabangouDisplayKudari = value; };
	/** @see m_iJikokuhyouPrevRessyabangouDisplayNobori */
	int getJikokuhyouPrevRessyabangouDisplayNobori()const { return m_iJikokuhyouPrevRessyabangouDisplayNobori; };
	/** @see m_iJikokuhyouPrevRessyabangouDisplayNobori */
	void setJikokuhyouPrevRessyabangouDisplayNobori(int value) { m_iJikokuhyouPrevRessyabangouDisplayNobori = value; };
	/** @see m_iJikokuhyouPrevRessyabangouDisplay */
	int getJikokuhyouPrevRessyabangouDisplay(ERessyahoukou eRessyahoukou)const
	{
		if (eRessyahoukou == ERessyahoukou::Ressyahoukou_Nobori)
		{
			return m_iJikokuhyouPrevRessyabangouDisplayNobori;
		}
		return m_iJikokuhyouPrevRessyabangouDisplayKudari;
	};

	/** @see m_iJikokuhyouPrevOperationNumberDisplayKudari */
	int getJikokuhyouPrevOperationNumberDisplayKudari()const { return m_iJikokuhyouPrevOperationNumberDisplayKudari; };
	/** @see m_iJikokuhyouPrevOperationNumberDisplayKudari */
	void setJikokuhyouPrevOperationNumberDisplayKudari(int value) { m_iJikokuhyouPrevOperationNumberDisplayKudari = value; };
	/** @see m_iJikokuhyouPrevOperationNumberDisplayNobori */
	int getJikokuhyouPrevOperationNumberDisplayNobori()const { return m_iJikokuhyouPrevOperationNumberDisplayNobori; };
	/** @see m_iJikokuhyouPrevOperationNumberDisplayNobori */
	void setJikokuhyouPrevOperationNumberDisplayNobori(int value) { m_iJikokuhyouPrevOperationNumberDisplayNobori = value; };
	/** @see m_iJikokuhyouPrevOperationNumberDisplay */
	int getJikokuhyouPrevOperationNumberDisplay(ERessyahoukou eRessyahoukou)const
	{
		if (eRessyahoukou == ERessyahoukou::Ressyahoukou_Nobori)
		{
			return m_iJikokuhyouPrevOperationNumberDisplayNobori;
		}
		return m_iJikokuhyouPrevOperationNumberDisplayKudari;
	};

	/** @see m_iJikokuhyouPrevOperationNumberDisplayRowsKudari */
	int getJikokuhyouPrevOperationNumberDisplayRowsKudari()const { return m_iJikokuhyouPrevOperationNumberDisplayRowsKudari; };
	/** @see m_iJikokuhyouPrevOperationNumberDisplayRowsKudari */
	void setJikokuhyouPrevOperationNumberDisplayRowsKudari(int value) { m_iJikokuhyouPrevOperationNumberDisplayRowsKudari = value; };
	/** @see m_iJikokuhyouPrevOperationNumberDisplayRowsNobori */
	int getJikokuhyouPrevOperationNumberDisplayRowsNobori()const { return m_iJikokuhyouPrevOperationNumberDisplayRowsNobori; };
	/** @see m_iJikokuhyouPrevOperationNumberDisplayRowsNobori */
	void setJikokuhyouPrevOperationNumberDisplayRowsNobori(int value) { m_iJikokuhyouPrevOperationNumberDisplayRowsNobori = value; };
	int getJikokuhyouPrevOperationNumberDisplayRows(ERessyahoukou eRessyahoukou)const
	{
		if (eRessyahoukou == ERessyahoukou::Ressyahoukou_Nobori)
		{
			return m_iJikokuhyouPrevOperationNumberDisplayRowsNobori;
		}
		return m_iJikokuhyouPrevOperationNumberDisplayRowsKudari;
	};

	/** @see m_iJikokuhyouPrevRessyaSyubetsuDisplayKudari */
	int getJikokuhyouPrevRessyaSyubetsuDisplayKudari()const { return m_iJikokuhyouPrevRessyaSyubetsuDisplayKudari; };
	/** @see m_iJikokuhyouPrevRessyaSyubetsuDisplayKudari */
	void setJikokuhyouPrevRessyaSyubetsuDisplayKudari(int value) { m_iJikokuhyouPrevRessyaSyubetsuDisplayKudari = value; };
	/** @see m_iJikokuhyouPrevRessyaSyubetsuDisplayNobori */
	int getJikokuhyouPrevRessyaSyubetsuDisplayNobori()const { return m_iJikokuhyouPrevRessyaSyubetsuDisplayNobori; };
	/** @see m_iJikokuhyouPrevRessyaSyubetsuDisplayNobori */
	void setJikokuhyouPrevRessyaSyubetsuDisplayNobori(int value) { m_iJikokuhyouPrevRessyaSyubetsuDisplayNobori = value; };
	/** @see m_iJikokuhyouPrevRessyaSyubetsuDisplay */
	int getJikokuhyouPrevRessyaSyubetsuDisplay(ERessyahoukou eRessyahoukou)const
	{
		if (eRessyahoukou == ERessyahoukou::Ressyahoukou_Nobori)
		{
			return m_iJikokuhyouPrevRessyaSyubetsuDisplayNobori;
		}
		return m_iJikokuhyouPrevRessyaSyubetsuDisplayKudari;
	};

	/** @see m_iJikokuhyouPrevRessyameiDisplayKudari */
	int getJikokuhyouPrevRessyameiDisplayKudari()const { return m_iJikokuhyouPrevRessyameiDisplayKudari; };
	/** @see m_iJikokuhyouPrevRessyameiDisplayKudari */
	void setJikokuhyouPrevRessyameiDisplayKudari(int value) { m_iJikokuhyouPrevRessyameiDisplayKudari = value; };
	/** @see m_iJikokuhyouPrevRessyameiDisplayNobori */
	int getJikokuhyouPrevRessyameiDisplayNobori()const { return m_iJikokuhyouPrevRessyameiDisplayNobori; };
	/** @see m_iJikokuhyouPrevRessyameiDisplayNobori */
	void setJikokuhyouPrevRessyameiDisplayNobori(int value) { m_iJikokuhyouPrevRessyameiDisplayNobori = value; };
	/** @see m_iJikokuhyouPrevRessyameiDisplay */
	int getJikokuhyouPrevRessyameiDisplay(ERessyahoukou eRessyahoukou)const
	{
		if (eRessyahoukou == ERessyahoukou::Ressyahoukou_Nobori)
		{
			return m_iJikokuhyouPrevRessyameiDisplayNobori;
		}
		return m_iJikokuhyouPrevRessyameiDisplayKudari;
	};

	vector< CrossingCheckRule> getCrossingCheckRuleCont()const
	{
		return m_CrossingCheckRuleCont;
	}
	int getCrossingCheckRuleSize()const
	{
		return m_CrossingCheckRuleCont.size();
	}
	CrossingCheckRule getCrossingCheckRule(int idx)const
	{
		if (idx >= 0 && idx < (int)m_CrossingCheckRuleCont.size())
		{
			return m_CrossingCheckRuleCont[idx];
		}
		return CrossingCheckRule();
	}
	void setCrossingCheckRule(vector< CrossingCheckRule> value)
	{
		m_CrossingCheckRuleCont = value;
	}
	void addCrossingCheckRule(CrossingCheckRule value)
	{
		m_CrossingCheckRuleCont.push_back(value);
	}
	void setCrossingCheckRule(CrossingCheckRule value,int idx)
	{
		if (idx >= 0 && idx < (int)m_CrossingCheckRuleCont.size())
		{
			m_CrossingCheckRuleCont[idx] = value;
		}
	}
	void eraseCrossingCheckRule( int idx)
	{
		if (idx >= 0 && idx < (int)m_CrossingCheckRuleCont.size())
		{
			m_CrossingCheckRuleCont.erase(m_CrossingCheckRuleCont.begin() + idx);
		}
	}
	void addCrossingCheckRule(vector< CrossingCheckRule> value)
	{
		m_CrossingCheckRuleCont.insert(
			m_CrossingCheckRuleCont.end(),
			value.begin(), value.end());
	}
	///@}
	// ********************************
	///@name CentDedEki-包含
	// ********************************
	///@{

	/** @see m_CentDedEkiTrack2Cont  */
	CentDedEkiTrack2Cont* getEkiTrack2Cont() { return &m_CentDedEkiTrack2Cont; }
	/** @see m_CentDedEkiTrack2Cont */
	const CentDedEkiTrack2Cont* getEkiTrack2Cont()const
	{
		return &m_CentDedEkiTrack2Cont;
	}
	///@}
	
	// ********************************
	///@name CentDedEki-操作
	// ********************************
	///@{
	///@}

	/**
	CentDedEkiCont に CentDedEki が追加された直後、
	CentDedEkiCont から呼び出されます。
	@param iEkiIndex
	追加された CentDedEki のインデクス。
	*/
	virtual void onEkiInsert(int iEkiIndex,int size);
	/**
	CentDedEkiCont から CentDedEki が削除された直後、
	CentDedEkiCont から呼び出されます。
	@param iEkiIndex
	削除された CentDedEki の先頭のインデクス。
	*/
	virtual void onEkiErase(int iEkiIndex);

	//thisと指定されたCentDedEkiの主本線比較します
	// 3:Down,Upともに不一致
	// 2:UpMainが不一致
	// 1:DownMainが不一致
	// 0:完全一致
	virtual int compareMainTrack(const CentDedEki* pCentDedEki);
		
	/**
		この駅と、pCentDedEkiの路線外発着駅名の比較を行います

		3:thisの方が駅名数が多い
		2:駅名数は同じで、OuterTerminalEkimei要素に差異がある
		1:駅名数は同じで、OuterTerminalEkimei要素が一致しているが
			略称要素に差異がある
		0:完全一致
		-1:pCentDedEkiの方が番線数が多い
	*/
	virtual int compareOuterTerminal(const CentDedEki* pCentDedEki)const;
};

} //namespace entDed

#endif /*CentDedEki_h*/
