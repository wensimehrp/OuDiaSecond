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
//	CentDedBeforeOperation.h
//	$Id: CentDedBeforeOperation.h  $
// ****************************************************************
*/
/** @file */
#ifndef  CentDedBeforeOperation_h
#define  CentDedBeforeOperation_h

#include "CdDedJikoku.h"
//#include "CentDedBeforeOperationCont.h"

namespace entDed{
	using namespace OuLib::NsMu ;
	using namespace std ;

// ****************************************************************
//	CentDedBeforeOperation
// ****************************************************************
/**
@brief
  DiagramEdit の、１列車の一つの前作業を表します。
 */
class CentDedBeforeOperation : public CChildBase
{
	typedef CChildBase	super ;
public:
	// ****************************************************************
	//	インナータイプ
	// ****************************************************************
	/**
		代入演算子でスローされる例外です。
	*/
	class LException
	{
	};
	/**
	  このクラスに包含される『前作業』(CentDedBeforeOperation) オブジェクト
	のコンテナです。
	*/
	class CXBeforeOperationCont : public CentDedBeforeOperationCont
	{
	public:
		// ********************************
		///@name CentDedBeforeOperationCont-関連
		// ********************************
		///@{
		/**
		@return
			このコンテナが CentDedBeforeOperation に包含されている場合は、
			CentDedBeforeOperation のアドレス。
			そうでないならNULL。
		*/
		virtual CentDedBeforeOperation* getBeforeOperation()
		{
			CentDedBeforeOperation* pOuter = (CentDedBeforeOperation*)(((char*)this) - offsetof(CentDedBeforeOperation, m_CentDedBeforeOperationCont));
			return pOuter;
		};
		/**
		@return
			このコンテナが CentDedBeforeOperation に包含されている場合は、
			CentDedBeforeOperation のアドレス。
			そうでないならNULL。
		*/
		virtual const CentDedBeforeOperation* getBeforeOperation()const
		{
			const CentDedBeforeOperation* pOuter = (const CentDedBeforeOperation*)(((char*)this) - offsetof(CentDedBeforeOperation, m_CentDedBeforeOperationCont));
			return pOuter;
		};
		///@}
	};

	/**
	  このクラスに包含される『後作業』(CentDedOperationAfter) オブジェクト
	のコンテナです。
	*/
	class CXAfterOperationCont : public CentDedAfterOperationCont
	{
	public:
		// ********************************
		///@name CentDedAfterOperationCont-関連
		// ********************************
		///@{
		/**
		@return
			このコンテナが CentDedBeforeOperation に包含されている場合は、
			CentDedBeforeOperation のアドレス。
			そうでないならNULL。
		*/
		virtual CentDedBeforeOperation* getBeforeOperation()
		{
			CentDedBeforeOperation* pOuter = (CentDedBeforeOperation*)(((char*)this) - offsetof(CentDedBeforeOperation, m_CentDedAfterOperationCont));
			return pOuter;
		};
		/**
		@return
			このコンテナが CentDedEkiJikoku に包含されている場合は、
			CentDedEkiJikoku のアドレス。
			そうでないならNULL。
		*/
		virtual const CentDedBeforeOperation* getBeforeOperation()const
		{
			const CentDedBeforeOperation* pOuter = (const CentDedBeforeOperation*)(((char*)this) - offsetof(CentDedBeforeOperation, m_CentDedAfterOperationCont));
			return pOuter;
		};
		///@}
	};
	/**
		『作業』を表す列挙です。
	 */
	enum class EBOperation
	{
		/**
			 入換(規定値)
			 番線間の移動を表します。
			 この作業が保持する番線から、
			 列車の発着番線・より後にある入換番線・増結が行われる番線への移動を意味します。
		 */
		BOperation_Shunt,
		/**
			増結、他の編成の増結を表します。
			この作業は、増結相手の編成の前作業も保持します。

		*/
		BOperation_Connect,
		/**
			解結、編成の一部の解結を表します。
			この作業は、解結対象の編成の後作業も保持します。
		*/
		BOperation_Release,
		/**
			 出区、始発駅/増結編成の最初の作業でのみ使用可能
		 */
		BOperation_Out,
		/**
			路線外始発、始発駅/増結編成の最初の作業でのみ使用可能
		*/
		BOperation_Outer,
		/**
			前列車接続 。
			始発駅/増結編成の最初の作業でのみ使用可能
			出区・路線外発着以外は全てこれになります。
		 */
		BOperation_Junction,
		/**
			運用番号変更 。
			編成はそのままに、割り当てられる運用番号だけを変更します
		 */
		BOperation_NumberChange
	};


private:
	// ********************************
	///@name 属性
	// ********************************
	///@{
	/**
		作業種類です。
	*/
	EBOperation m_eBOperation;

	//※印が付いた属性は、運用探索によって割り当てられるものです
	/**
		入換:この作業の入換着時刻を、時刻表の表示モードにおける
			当駅の着時刻とみなすか否かを表す値です。
			false(規定値):着時刻として扱いません。
			true:着時刻として扱います。
			なお、前作業内に複数の入換が存在し、二つ以上の入換作業において、
			この値がtrueの場合、前作業コンテナ内で最もIndexが大きいもの(時系列で後ろの物)が有効になります。
		増結:増結編成を、運用番号基準で親編成の前後どちらに接続するかを表します
			(例)親編成が01A、増結編成が03Aの運用番号の場合、
			true:増結編成を親編成よりも前に連結します。例の運用番号は[03A],[01A]となります
			false(規定値):増結編成を親編成よりも後ろに連結します。例の運用番号は[01A],[03A]となります
		解結:未使用
		※出区:割り当て運用番号が有効か否か(Ver2.05から)
			true:運用番号に割り当て運番を用います。入出区連携コードにより入区から運番を引き継いだ場合です。
			false(規定値):手動入力の運用番号を用います。
		※路線外始発:割り当て運用番号が有効か否か(Ver2.05から)
			出区時と同様です。
		※前列車接続:種別変更(列車情報変更・同一列車)(booldata1から変更になりました(Ver2.00.05) Data2から再変更Ver2.05
			この作業が、別列車から種別変更により繋がっている場合、
			この値はtrueになります
			(注)この値がtrueの時は種別変更、ではなく種別変更が決まった場合に、この値がtrueになります
		運用番号変更:運用番号順反転
	*/
	bool m_bBoolData1;

	/**
		入換:未使用
		※増結:増結前増結編成運用番号が、割り当て済みか否かを表します
		解結:未使用
		出区:未使用
		路線外始発:未使用
		※前列車接続:列車情報表示省略(Ver2.05.01～)
			true:ダイヤグラムビューにおいて、この作業から始まる列車では、既に列車情報(列車番号等)の表示を済ませたものとして扱います。
				この値がtrueになるのは、カスタマイズ時刻表において、同一行に表示するような列車の組の次列車側かつ、次列車接続タイプが同一列車扱いの場合です。
			false(規定値):通常通りの処理
		運用番号変更:未使用
	*/
	bool m_bBoolData2;

	/**
		入換:入換前の番線
		増結:未使用
		解結:運用番号上での、解結する編成位置を表します。
			0:後方の任意数の編成を解結します(規定値) 。
				指定数が編成数以上の場合は、編成数-1編成を解結します。
				ただし、前運用番号が一つの場合は、前運用番号を主編成に、空白運番を解結編成に充てます。
			1:前方の任意数の編成を解結します。
				指定数が編成数以上の場合、編成数-1編成を解結します。
				ただし、前運用番号が一つの場合は、前運用番号を主編成に、空白運番を解結編成に充てます。
			2:前方の任意数の編成"以外"を解結します。
				指定数が編成数以上の場合は、前運番の末尾を解結します。
				ただし、前運用番号が一つの場合は、前運用番号を主編成に、空白運番を解結編成に充てます。

			従って、前運用番号が一つの場合は、必ずそれを主編成に充て、解結編成は空白運番となります。
			また、前運用番号が二つの場合は、片方が主編成、もう片方が解結編成となります。
		出区:未使用
		路線外始発:路線外発着駅のIndex
		※前列車接続:解結駅Order
			この作業が、別列車の解結編成から繋がっている場合、
			解結が行われた駅の駅Orderが割り当てられます。
			カスタム表示モードにおける↴マークの表示位置になります。
			デフォルト値は-1です。
		※前列車接続:前列車方向(在線表あり駅)(Ver2.05 解結駅Orderより変更・解結駅OrderはCustomizeJikokuhyouContentに移行)
			運用機能により、この作業が別の作業から接続された場合、
			この作業が行われる番線に移動する縦線が、どちらの方向から延びているかを示します。

			-2:この列車の列車方向の起点方から(入換があるので確定)
			-1:この列車の列車方向の起点方から(反転駅設定により変化する)
			0:接続なし,デフォルト値
			1:この列車の列車方向の終点方から(反転駅設定により変化する)
			2:この列車の列車方向の終点方から(入換があるので確定)
		運用番号変更:未使用
	*/
	int m_iIntData1;

	/**
		入換:未使用
		増結:未使用
		解結:運用番号上での、解結する編成数もしくは残す編成数です。
			m_bBoolData1の値により意味が変わります。
			0:この値の編成数だけ後方から解結します。
			1:この値の編成数だけ前方から解結します。
			2:この値の編成数を除き、後方から解結します。
			(例)元編成が[01A],[03A],[05A],[07A],[09A]の場合
			0,2の場合、解結編成は[07A],[09A]
			1,2の場合、解結編成は[01A],[03A]
			2,2の場合、解結編成は[05A],[07A],[09A]
			規定値は1です。
		出区:未使用
		路線外始発:未使用
		※前列車接続:前列車方向(在線表無し駅)(Ver2.05 IntData3→2に変更)
			運用機能により、この作業が別の作業から接続された場合、前列車の方向がここに入ります。
			1:この列車の列車方向と同方向(反転駅設定により変化する)
			0:接続なし,デフォルト値
			-1:この列車の列車方向と逆方向(反転駅設定により変化する)
		運用番号変更:未使用
	*/
	int m_iIntData2;

	/**
		入換:未使用
		増結:未使用
		解結:未使用
		出区:未使用
		路線外始発:未使用
		※前列車接続:前列車の終着駅Orderを、この列車の列車方向に合わせた、EkiOrderに変換したものです
			反転駅設定の判定に用います。(Ver2.05 IntData4→3に変更)
		運用番号変更:未使用
	*/
	int m_iIntData3;

	/**
		入換:列車の入換発時刻
		増結:増結を行う時刻、ダイヤグラムにおける、増結マークの表示位置になるほか、
			増結編成の前作業の作業時刻の原点になります。
			NULL時刻の場合は、列車の着時刻・直前の入換着時刻・
			出区時刻・路線外始発列車の当駅着時刻が、適用されます。
		解結:解結を行う時刻、ダイヤグラムにおける、解結マークの表示位置になるほか、
			解結編成の後作業の作業時刻の原点になります。
			NULL時刻の場合は、列車の発時刻・直後の入換発時刻・
			入区時刻・路線外終着列車の当駅発時刻が、適用されます。
		出区:出区時刻、ダイヤグラムビューにおける丸印の位置を示します。
		路線外始発:路線外始発駅の発車時刻
		前列車接続:起点時刻、前列車からのの接続を探索する際、この時刻を基準とします。
			デフォルト値はNULL時刻です。
		運用番号変更:未使用
	*/
	CdDedJikoku m_JikokuData1;

	/**
		入換:列車の入換着時刻
			この値がNULL時刻の場合、入換発時刻と同一とみなします。
		増結:未使用
		解結:未使用
		出区:未使用
		路線外始発:当駅の着時刻です。
			従来は、CentDedEkijikokuにおける着時刻を用いていましたが、作業側に移動します。
			これは、(データ上の)始発駅における時刻形式を統一させるためです。
			この値が空の時は、当駅の発時刻と同時刻とみなします。
		※前列車接続:前列車接続時刻(在線表有り駅)
			運用機能により、この作業が別の作業から接続された場合、前の作業の終点時刻がここに入ります。
			デフォルト値はNULL時刻です。
		運用番号変更:未使用
	*/
	CdDedJikoku m_JikokuData2;

	/**
		入換:未使用
		増結:未使用
		解結:未使用
		出区:未使用
		路線外始発:未使用
		※前列車接続:前列車接続時刻(在線表無し駅)
			運用機能により、この作業が別の作業から接続された場合、前の列車の終点着時刻がここに入ります。
			デフォルト値はNULL時刻です。
		運用番号変更:未使用
	*/
	CdDedJikoku m_JikokuData3;

	/**
		入換:未使用
		※増結:増結後運用番号
			複数編成が連結した状態では、各編成に対して一つづつ運用番号を割り当て、
			それを配列形式で保持します。
			出区・路線外始発以外の運用番号は、運用探索によって求まります。
		※解結:解結前運用番号
			複数編成が連結した状態では、各編成に対して一つづつ運用番号を割り当て、
			それを配列形式で保持します。
			出区・路線外始発以外の運用番号は、運用探索によって求まります。
		出区:運用番号
			複数編成が連結した状態で出区する場合、各編成に対して一つづつ運用番号を割り当て、
			それを配列形式で保持します。
		路線外始発:運用番号
			複数編成が連結した状態で路線外始発駅を出発する場合、各編成に対して一つづつ運用番号を割り当て、
			それを配列形式で保持します
		前列車接続:仮運用番号
			運用探索でこの作業に接続する作業がない場合、
			空・空白の運用番号でこの作業に接続された場合、
			この運用番号を新たな運用番号とし、探索を続けます。
			なお、有効な運用番号が割り当てられた場合は、意味を持ちません。
		運用番号変更:新運用番号
			ダイアログで指定された、この作業以降に割り当てられる運用番号です
			Ver2.06.05より、空が可能となります。
	*/
	vector<tstring> m_strOperationNumber1;

	/**
		入換:未使用
		※増結:増結前主編成運用番号
			複数編成が連結した状態では、各編成に対して一つづつ運用番号を割り当て、
			それを配列形式で保持します。
			出区・路線外始発以外の運用番号は、運用探索によって求まります。
		※解結:解結後主編成運用番号
			複数編成が連結した状態では、各編成に対して一つづつ運用番号を割り当て、
			それを配列形式で保持します。
			出区・路線外始発以外の運用番号は、運用探索によって求まります。
		※出区:割り当て運用番号(Ver2.05から)
			入出区連携コード機能により、入区から運用番号を引き継いだ場合に、
			このパラメータで運用番号を保持します。
		※路線外始発:割り当て運用番号(Ver2.05から)
		※前列車接続:割り当て運用番号(Ver2.00.05 Number1から変更)
			複数編成が連結した状態の場合、各編成に対して一つづつ運用番号を割り当て、
			それを配列形式で保持します。
			この作業の運用番号は、運用探索によって求まります。
			ただし、運用探索で空・空白の運用番号が割り当てられた場合、
			m_strOperationNumber2(仮運用番号)で置き換えます。
		※運用番号変更:旧運用番号
			運用探索で割り当てられた、この作業までの運用番号です
	*/
	vector<tstring> m_strOperationNumber2;

	/**
		入換:未使用
		※増結:増結前増結編成運用番号
			複数編成が連結した状態では、各編成に対して一つづつ運用番号を割り当て、
			それを配列形式で保持します。
			出区・路線外始発以外の運用番号は、運用探索によって求まります。
		※解結:解結後解結編成運用番号
			複数編成が連結した状態では、各編成に対して一つづつ運用番号を割り当て、
			それを配列形式で保持します。
			出区・路線外始発以外の運用番号は、運用探索によって求まります。
		出区:未使用
		路線外始発:未使用
		前列車接続:未使用
		※運用番号変更:反転後運用番号(Ver2.06.05～)
			運用番号反転が有効な場合は、ここに新しい運用番号を割り当てます
	*/
	vector<tstring> m_strOperationNumber3;

	/**
		入換:未使用
		増結:未使用
		解結:未使用
		出区:入出区連携コード(Ver2.05から)
			入区・路線外終着と出区・路線外始発に同じコードが設定されている場合、
			運用接続時に、入区側に割り当てられた運用番号が、出区側に自動で割り当てられます。
		路線外始発:入出区連携コード(Ver2.05から)
		前列車接続:未使用
		運用番号変更:未使用
	*/
	tstring m_strInOutLinkCode;

	/**
		増結編成の前作業
		増結編成の増結前の入換・出区等を保持します。
		前作業内での増解結も可能です。
	*/
	CXBeforeOperationCont 	m_CentDedBeforeOperationCont;

	/**
		解結編成の後作業
		解結編成の解結後の入換・入区等を保持します。
		後作業内での増解結も可能です。
	*/
	CXAfterOperationCont 	m_CentDedAfterOperationCont;

	
	///@}

public:
	// ********************************
	//	コンストラクタ
	// ********************************
	/** デフォルトコンストラクタ */
	CentDedBeforeOperation() ;
	
	/**
	 @param iRessyaTrackIndex [in]
		列車番線Indexが入ります。
	 @param eOperation [in]
		始発・終着駅作業を表します。
	 @param iShuntTrackIndex [in]
		入換番線/路線外発着駅Indexを表します。
		作業が入換・路線外発着以外の場合は、この値は意味がありません。
	 @param OperationHatsuJikoku [in]
		作業発時刻・路線外発着時刻を表します。
		作業が入換・路線外発着以外の場合は、この値は意味がありません。
	 @param OperationChakuJikoku [in]
		作業着時刻時刻を表します。
		作業が入換以外の場合は、この値は意味がありません。
	 @param strOperationNumber [in]
		運用番号を表します。
		作業が出区・路線外発以外の場合は、この値は意味がありません。

	 */
	CentDedBeforeOperation( 
		EBOperation eBOperation,
		bool bBoolData1,
		bool bBoolData2,
		int iIntData1,
		int iIntData2,
		int iIntData3,
		CdDedJikoku JikokuData1,
		CdDedJikoku JikokuData2,
		CdDedJikoku JikokuData3,
		vector<tstring> strOperationNumber1) ;

	//入換
	/**
		@param iShuntTrackIndex [in]
		入換前の番線Indexを表します。
		@param OperationHatsuJikoku [in]
		列車の入換発時刻を表します。
		@param OperationChakuJikoku [in]
		列車の入換着時刻を表します。
		@param bIsDisplayChakuJikoku [in]
		入換着時刻を着時刻とみなすか否かを表します。
		*/
	CentDedBeforeOperation(
		EBOperation eBOperation,
		int iShuntTrackIndex,
		CdDedJikoku	OperationHatsuJikoku,
		CdDedJikoku	OperationChakuJikoku,
		bool bIsDisplayChakuJikoku);

	//増結
	/**
		@param bIsConnectToFront [in]
		増結位置の前後を表します。
		@param ConnectJikoku [in]
		増結時刻を表します。
		*/
	CentDedBeforeOperation(
		EBOperation eBOperation,
		bool bIsConnectToFront,
		CdDedJikoku	ConnectJikoku);

	//解結
	/**
		@param eBReleasePos [in]
		解結する編成位置を表します。
		@param iReleaseIndexCount [in]
		解結する編成数または基準位置を表します。
		@param ReleaseJikoku [in]
		解結を行う時刻を表します。
		*/
	CentDedBeforeOperation(
		EBOperation eBOperation,
		int iReleasePos,
		int iReleaseIndexCount,
		CdDedJikoku	ReleaseJikoku);

	//出区
	/**
	 @param OutJikoku [in]
		出区時刻を表します。
	 @param strOperationNumber [in]
		運用番号を表します。
	 */
	CentDedBeforeOperation(
		EBOperation eBOperation,
		CdDedJikoku	OutJikoku,
		vector<tstring> strOperationNumber,
		tstring strInOutLinkCode);

	//路線外始発
	/**
	 @param iOuterShihatsuekiIndex [in]
		路線外発着駅Indexを表します。
	 @param OuterShihatsuJikoku [in]
		路線外始発駅の発車時刻を表します。
	 @param ChakuJikoku [in]
		当駅の着時刻を表します。
	 @param strOperationNumber [in]
		運用番号を表します。
	 */
	CentDedBeforeOperation(
		EBOperation eBOperation,
		int iOuterShihatsuekiIndex,
		CdDedJikoku	OuterShihatsuJikoku,
		CdDedJikoku	ChakuJikoku,
		vector<tstring> strOperationNumber,
		tstring strInOutLinkCode);

	//前列車接続
	/**
		@param OriginJikoku [in]
			起点時刻を表します。
		@param bDisableReleaseDisplay [in]
			解結表示省略設定を表します
			(Ver2.05削除)
		*/
	CentDedBeforeOperation(
		EBOperation eBOperation,
		CdDedJikoku	OriginJikoku,
		//bool bDisableReleaseDisplay,
		vector<tstring> strOperationNumberTemp);

	//運用番号変更
	/**
	 @param strOperationNumber [in]
		運用番号を表します。
	 @param bOperationNumberReverse [in]
		運用番号順反転の有効無効を表します。
	 */
	CentDedBeforeOperation(
		EBOperation eBOperation,
		vector<tstring> strOperationNumber,
		bool bOperationNumberReverse);
	/** 
	
	@exception LException 
	*/
	CentDedBeforeOperation& operator=( const CentDedBeforeOperation& value ) ;
public:
	// ********************************
	///@name CChildBase-操作
	// ********************************
	///@{
	virtual void setParent( CParentBase* pParent );

	//virtual void modifyOperationJikoku(int iSecond);
	///@}

	// ********************************
	///@name CentDedBeforeOperation-包含
	// ********************************
	///@{
	/** @see m_CentDedBeforeOperationCont */
	CentDedBeforeOperationCont* getCentDedBeforeOperationCont()
	{
		return &m_CentDedBeforeOperationCont;
	}
	/** @see m_CentDedBeforeOperationCont */
	const CentDedBeforeOperationCont*	getCentDedBeforeOperationCont()const
	{
		return &m_CentDedBeforeOperationCont;
	}

	/** @see m_CentDedAfterOperationCont */
	CentDedAfterOperationCont* getCentDedAfterOperationCont()
	{
		return &m_CentDedAfterOperationCont;
	}
	/** @see m_CentDedAfterOperationCont */
	const CentDedAfterOperationCont*	getCentDedAfterOperationCont()const
	{
		return &m_CentDedAfterOperationCont;
	}
	///@}

public:
	// ********************************
	///@name CentDedBeforeOperation-属性
	// ********************************
	///@{

		/**
		作業種類を参照することができます。
		m_eBOperationを返します
		*/
	EBOperation getBOperation()const
	{
		return m_eBOperation;
	}

	/**
	m_eBOperationに代入します。
	*/
	//CentDedBeforeOperation& setBOperation(const EBOperation value);

	/**
		この作業が、BOperation_Out,BOperation_Outer,BOperation_Junctionの
		いずれかの場合に、Trueを返します。
		つまり、この作業を含む列車(および増結前作業)の、最初の作業であるということです。
	*/
	bool isFirstOperation()const;

	//入換用

		/**
		入換前の番線Indexを参照することができます。
		m_iIntData1を返します
		*/
	int getShuntTrackIndex()const
	{
		return m_iIntData1;
	}

	/**
	m_iIntData1に代入します。
	*/
	CentDedBeforeOperation& setShuntTrackIndex(const int value)
	{
		m_iIntData1 = value;
		return *this;
	}

	/**
		入換発時刻を参照することができます。
		m_JikokuData1を返します
	*/
	CdDedJikoku	getOperationHatsuJikoku()const
	{
		return m_JikokuData1;
	}

	/**
		m_JikokuData1に代入します。
	*/
	CentDedBeforeOperation& setOperationHatsuJikoku(const CdDedJikoku& value)
	{
		m_JikokuData1 = value;
		return *this;
	}

	/**
	入換着時刻を参照することができます。
	bHatsuIfNullがtrueかつ、m_JikokuData2がNULL時刻の場合は、
	入換発時刻を返し、
	それ以外の場合は、m_JikokuData2を返します
	*/
	CdDedJikoku	getOperationChakuJikoku(bool bHatsuIfNull = false)const
	{
		if (bHatsuIfNull && m_JikokuData2.isNull())
		{
			return m_JikokuData1;
		}
		return m_JikokuData2;
	}

	/**
	m_JikokuData2に代入します。
	*/
	CentDedBeforeOperation& setOperationChakuJikoku(const CdDedJikoku& value)
	{
		m_JikokuData2 = value;
		return *this;
	}

	/**
	m_bBoolData1を参照することができます。
	*/
	bool	getIsDisplayChakuJikoku()const
	{
		return m_bBoolData1;
	}

	/**
	m_bBoolData1に代入します。
	*/
	CentDedBeforeOperation& setIsDisplayChakuJikoku(const bool& value)
	{
		m_bBoolData1 = value;
		return *this;
	}

	//増結用

		/**
		増結編成を、運用番号基準で親編成の前後どちらに接続するかを取得します。
		m_bBoolData1を返します
		*/
	bool getIsConnectToFront()const
	{
		return m_bBoolData1;
	}

	/**
	m_bBoolData1に代入します。
	*/
	CentDedBeforeOperation& setIsConnectToFront(const bool value)
	{
		m_bBoolData1 = value;
		return *this;
	}

	/**
		増結を行う時刻を参照することができます。
		m_JikokuData1を返します
	 */
	CdDedJikoku	getConnectJikoku()const
	{
		return m_JikokuData1;
	}

	/**
		m_JikokuData1に代入します。
	*/
	CentDedBeforeOperation& setConnectJikoku(const CdDedJikoku& value)
	{
		m_JikokuData1 = value;
		return *this;
	}

	/**
	増結後運用番号全体を参照することができます。
	m_strOperationNumber1を返します
	*/
	vector<tstring> getOperationNumberAfter()const
	{
		return m_strOperationNumber1;
	};

	/**
	m_strOperationNumberAfterに代入します。
	*/
	CentDedBeforeOperation& setOperationNumberAfter(const vector<tstring>& value)
	{
		m_strOperationNumber1 = value; return *this;
	};

	int getOperationNumberAfterCount() const
	{
		return m_strOperationNumber1.size();
	}

	bool getOperationNumberSubAssigned() const
	{
		return m_bBoolData2;
	}

	void mergeOperationNumber();

	//増結・解結兼用
	/**
	増結前主編成/解結後主編成の運用番号全体を参照することができます。
	m_strOperationNumber2を返します
	*/
	vector<tstring> getOperationNumberMain()const
	{
		return m_strOperationNumber2;
	};
	/**
	増結編成/解結編成の運用番号全体を参照することができます。
	m_strOperationNumber3を返します
	*/
	vector<tstring> getOperationNumberSub()const
	{
		return m_strOperationNumber3;
	};
	/**
		m_strOperationNumber2に代入します。
	*/
	CentDedBeforeOperation& setOperationNumberMain(const vector<tstring>& value)
	{
		m_strOperationNumber2 = value;
		return *this;
	};
	/**
		m_strOperationNumber3に代入します。
		作業が増結の場合は、増結運番割り当て済みフラグを立てます。
	*/
	CentDedBeforeOperation& setOperationNumberSub(const vector<tstring>& value)
	{
		m_strOperationNumber3 = value;
		if (m_eBOperation == EBOperation::BOperation_Connect)
		{
			m_bBoolData2 = true;
		}
		return *this;
	};

	/**
		増結前主編成/解結後主編成の運用番号の個数を返します
	*/
	int getOperationNumberMainCount() const
	{
		return m_strOperationNumber2.size();
	}

	/**
		増結編成/解結編成の運用番号の個数を返します
	*/
	int getOperationNumberSubCount() const
	{
		return m_strOperationNumber3.size();
	}
	//解結用
	/**
		解結編成が、運用番号基準で元編成のどこに位置するかを取得します。
		m_iIntData1を返します
		*/
	int getReleasePos()const
	{
		return m_iIntData1;
	}

	/**
	m_iIntData1に代入します。
	*/
	CentDedBeforeOperation& setReleasePos(const int value)
	{
		m_iIntData1 = value;
		return *this;
	}

	/**
	解結編成が、運用番号基準で元編成のどこに位置するかを取得します。
	m_iIntData2を返します
	*/
	int getReleaseIndexCount()const
	{
		return m_iIntData2;
	}

	/**
	m_iIntData2に代入します。
	*/
	CentDedBeforeOperation& setReleaseIndexCount(const int value)
	{
		m_iIntData2 = value;
		return *this;
	}

	/**
		解結を行う時刻を参照することができます。
		m_JikokuData1を返します
	 */
	CdDedJikoku	getReleaseJikoku()const
	{
		return m_JikokuData1;
	}

	/**
		m_JikokuData1に代入します。
	*/
	CentDedBeforeOperation& setReleaseJikoku(const CdDedJikoku& value)
	{
		m_JikokuData1 = value;
		return *this;
	}

	/**
	解結前の運用番号全体を参照することができます。
	m_strOperationNumber1を返します
	*/
	vector<tstring> getOperationNumberBefore()const
	{
		return m_strOperationNumber1;
	};
	/**
	   解結前の運用番号の個数を返します
	*/
	int getOperationNumberBeforeCount() const
	{
		return m_strOperationNumber1.size();
	}

	/**
	   引数の運用番号を、m_strOperationNumber1に収めたのち、m_eBRelease、m_iReleaseIndexCountに基づいて、
	   m_strOperationNumberMain、m_strOperationNumberSubに分割します。
	*/
	CentDedBeforeOperation& setOperationNumberBefore(const vector<tstring>& value)
	{
		m_strOperationNumber1 = value;
		splitOperationNumber();
		return *this;
	}

	void splitOperationNumber();

	//出区・路線外始発・前列車接続・運用番号変更共用
	/**
	運用番号全体を参照することができます。
	前列車接続以外は、
	m_strOperationNumber1を返します
	前列車接続は
	m_strOperationNumber2を返します
		(ver2.05から)
		出区・路線外始発の場合、getOperationNumberAssignedByLinkCodeが
			trueの場合は　m_strOperationNumber2を
			falseの場合は m_strOperationNumber1を返します
		Ver2.06.05 運用番号変更の場合、運用番号順反転設定によって返す値が変わります
		運用番号順反転無効の場合は、m_strOperationNumber1を、
		運用番号順反転有効の場合は、m_strOperationNumber3を返します。
	*/
	vector<tstring> getOperationNumber()const
	{
		if (m_eBOperation == EBOperation::BOperation_Junction)
		{
			return m_strOperationNumber2;
		}
		else if (m_eBOperation == EBOperation::BOperation_Out ||
			m_eBOperation == EBOperation::BOperation_Outer)
		{
			if (getOperationNumberAssignedByLinkCode())
			{
				return m_strOperationNumber2;
			}
		}
		else if (m_eBOperation == EBOperation::BOperation_NumberChange &&
			m_bBoolData1)
		{
			return m_strOperationNumber3;
		}
		return m_strOperationNumber1;
	};

	//出区・路線外始発・運用番号変更共用
	/**
		ユーザーによって入力された、運用番号全体を参照することができます。
		常にm_strOperationNumber1を返します
	*/
	vector<tstring> getOperationNumberOriginal()const
	{
		return m_strOperationNumber1;
	};
	/**
		前列車接続以外は、
		m_strOperationNumber1に代入します。
		前列車接続は
		m_strOperationNumber2に代入します。
	*/
	CentDedBeforeOperation& setOperationNumber(const vector<tstring>& value)
	{
		if (m_eBOperation == EBOperation::BOperation_Junction)
		{
			m_strOperationNumber2 = value;
			return *this;
		}
		m_strOperationNumber1 = value;
		return *this;
	};

	/**
		Ver2.05から
		入出区連携コードにより割り当てられる運用番号を
		m_strOperationNumber2に代入します。同時にOperationNumberAssignedByLinkCodeをtrueにします。
		(よって、割り当て運番をクリアする目的では利用できません)
	*/
	CentDedBeforeOperation& setOperationNumberAssignedByLinkCode(const vector<tstring>& value)
	{
		m_strOperationNumber2 = value;
		setOperationNumberAssignedByLinkCode(true);
		return *this;
	};

	int getOperationNumberCount() const
	{
		if (m_eBOperation == EBOperation::BOperation_Junction)
		{
			return m_strOperationNumber2.size();
		}
		return m_strOperationNumber1.size();
	}

	//出区用
	/**
		出区時刻を参照することができます。
		m_OutJikokuを返します
		*/
	CdDedJikoku	getOutJikoku()const
	{
		return m_JikokuData1;
	}

	/**
		m_OutJikokuに代入します。
	*/
	CentDedBeforeOperation& setOutJikoku(const CdDedJikoku& value)
	{
		m_JikokuData1 = value;
		return *this;
	}

	//出区・路線外始発共用
	/**
			入出区連携コードを参照することができます。
			m_strInOutLinkCodeを返します
		*/
	tstring	getInOutLinkCode()const
	{
		return m_strInOutLinkCode;
	}

	/**
		m_strInOutLinkCodeに代入します。
	*/
	CentDedBeforeOperation& setInOutLinkCode(const tstring& value)
	{
		m_strInOutLinkCode = value;
		return *this;
	}

	/**
			入出区連携コード機能により運用番号が割り当てられたか否かを参照することができます。
			m_bBoolData1を返します
		*/
	bool	getOperationNumberAssignedByLinkCode()const
	{
		return m_bBoolData1;
	}

	/**
		m_bBoolData1に代入します。
	*/
	CentDedBeforeOperation& setOperationNumberAssignedByLinkCode(const bool& value)
	{
		m_bBoolData1 = value;
		return *this;
	}

	//路線外始発用
	/**
		路線外発着駅のIndexを参照することができます。
		m_iIntData1を返します
		*/
	int getOuterShihatsuekiIndex()const
	{
		return m_iIntData1;
	}

	/**
	m_iIntData1に代入します。
	*/
	CentDedBeforeOperation& setOuterShihatsuekiIndex(const int value)
	{
		m_iIntData1 = value;
		return *this;
	}

	/**
		路線外始発駅の発車時刻を参照することができます。
		m_JikokuData1を返します
		*/
	CdDedJikoku	getOuterShihatsuJikoku()const
	{
		return m_JikokuData1;
	}

	/**
		m_JikokuData1に代入します。
	*/
	CentDedBeforeOperation& setOuterShihatsuJikoku(const CdDedJikoku& value)
	{
		m_JikokuData1 = value;
		return *this;
	}

	/**
	当駅の着時刻を参照することができます。
	m_JikokuData2を返します
	*/
	CdDedJikoku	getChakuJikoku()const
	{
		return m_JikokuData2;
	}

	/**
	m_JikokuData2に代入します。
	*/
	CentDedBeforeOperation& setChakuJikoku(const CdDedJikoku& value)
	{
		m_JikokuData2 = value;
		return *this;
	}

	//前列車接続用
	/**
		起点時刻を参照することができます。
		m_JikokuData1を返します
		*/
	CdDedJikoku	getOriginJikoku()const
	{
		return m_JikokuData1;
	}

	/**
		m_JikokuData1に代入します。
	*/
	CentDedBeforeOperation& setOriginJikoku(const CdDedJikoku& value)
	{
		m_JikokuData1 = value;
		return *this;
	}

	//Ver2.05削除
	//CentDedBeforeOperation& setDisableReleaseDisplay(const bool& value)
	//{
	//	//Ver2.00.05 追加
	//	m_bBoolData1 = value;
	//	return *this;
	//};

	//Ver2.05削除
	//bool getDisableReleaseDisplay()const
	//{
	//	//Ver2.00.05 追加
	//	return m_bBoolData1;
	//}

	/**
	仮運用番号全体を参照することができます。
	m_strOperationNumber1を返します
	*/
	vector<tstring> getOperationNumberTemp()const
	{
		return m_strOperationNumber1;
	};

	/**
	m_strOperationNumber1に代入します。
	*/
	CentDedBeforeOperation& setOperationNumberTemp(const vector<tstring>& value)
	{
		m_strOperationNumber1 = value;
		return *this;
	};

	int getOperationNumberTempCount() const
	{
		return m_strOperationNumber1.size();
	}
	
	CentDedBeforeOperation& setIsSyubetsuChange(const bool& value)
	{
		//Ver2.00.05 BoolData2に変更
		//Ver2.05 BoolData1に再変更
		m_bBoolData1 = value;
		return *this;
	};

	bool getIsSyubetsuChange()const
	{
		//Ver2.00.05 BoolData2に変更
		//Ver2.05 BoolData1に再変更
		return m_bBoolData1;
	}

	CentDedBeforeOperation& setRessyajouhouOmit(const bool& value)
	{
		//Ver2.05.01 追加
		m_bBoolData2 = value;
		return *this;
	};

	bool getRessyajouhouOmit()const
	{
		//Ver2.05.01 追加
		return m_bBoolData2;
	}

	/**
		前列車接続時刻を参照することができます。
		m_JikokuData2を返します
	 */
	CdDedJikoku	getJunctionJikoku()const
	{
		return m_JikokuData2;
	}

	/**
		m_JikokuData2に代入します。
	*/
	CentDedBeforeOperation& setJunctionJikoku(const CdDedJikoku& value)
	{
		m_JikokuData2 = value;
		return *this;
	}

	/**
		前列車接続時刻を参照することができます。
		m_JikokuData3を返します
	 */
	CdDedJikoku	getJunctionJikokuNoDisplay()const
	{
		return m_JikokuData3;
	}

	/**
		m_JikokuData3に代入します。
	*/
	CentDedBeforeOperation& setJunctionJikokuNoDisplay(const CdDedJikoku& value)
	{
		m_JikokuData3 = value;
		return *this;
	}


	//Ver2.05 m_iIntData1に変更
	int getPrevRessyahoukou()const
	{
		return m_iIntData1;
	}

	CentDedBeforeOperation& setPrevRessyahoukou(const int& value)
	{
		m_iIntData1 = value;
		return *this;
	};

	//Ver2.05 m_iIntData2に変更
	int getPrevRessyahoukouNoDisplay()const
	{
		return m_iIntData2;
	}

	CentDedBeforeOperation& setPrevRessyahoukouNoDisplay(const int& value)
	{
		m_iIntData2 = value;
		return *this;
	};

	//Ver2.05 m_iIntData3に変更
	int getEkiOrderOfPrevSyuuchakuEki()const
	{
		return m_iIntData3;
	}

	CentDedBeforeOperation& setEkiOrderOfPrevSyuuchakuEki(const int& value)
	{
		m_iIntData3 = value;
		return *this;
	};

	//運用番号変更
	/**
		割り当てられた運用番号全体を参照することができます。
		m_strOperationNumber2を返します
	*/
	vector<tstring> getOperationNumberAssigned()const
	{
		return m_strOperationNumber2;
	};

	/**
		m_strOperationNumber2に代入します。
		Ver2.06.05
		運用番号順反転が有効な場合は、運用番号順反転を行ったものを、m_strOperationNumber3に代入します
	*/
	CentDedBeforeOperation& setOperationNumberAssigned(const vector<tstring>& value)
	{
		m_strOperationNumber2 = value;
		if (m_bBoolData1)
		{
			if (value.size() > 1)
			{
				vector<tstring> strOperationNumberTemp = value;
				std::reverse(strOperationNumberTemp.begin(), strOperationNumberTemp.end());
				m_strOperationNumber3 = strOperationNumberTemp;
			}
			else
			{
				m_strOperationNumber3 = value;
			}
		}
		return *this;
	};

	int getOperationNumberAssignedCount() const
	{
		return m_strOperationNumber2.size();
	}

	/**
		Ver2.06.05追加
		運用番号順反転を表します
	*/
	CentDedBeforeOperation& setOperationNumberReverse(const bool& value)
	{
		m_bBoolData1 = value;
		return *this;
	};

	bool getOperationNumberReverse()const
	{
		return m_bBoolData1;
	}

	//共通

	/**
		この作業及び増結前・解結後作業に設定された時刻を、iSecond秒だけ変更します。

	*/
	virtual void modifyOperationJikoku(int iSecond);

	/**
		この作業の属性のうち、運用探索時に割り当てられる要素について、
		その値を初期値に戻します。
	*/
	virtual void clearOperationNumber();

	/**
		この作業に割り当てられた運用番号について、
		運用探索時に付与された接尾辞(;セミコロン+数字)を除去します
	*/
	virtual void trimSuffixOperationNumber();

	/**
		この作業の増結前・解結後作業を、正規化します
		正規化は、前作業なら、開始作業は先頭のみ、
		後作業なら、終了作業は末尾のみ、になるように、調整することです。
	*/
	virtual void adjustOperation();

	/**
		この作業及び増結前・解結後作業にある入換作業について、
		番線データの変更を反映させます・
		元の入換番線が i の場合は、iEkiTrack2Map[i]が新たな入換番線Indexになります。
	*/
	virtual void adjustEkiTrack2(const std::vector<int>& iEkiTrack2Map);

	/**
		この作業及び増結前・解結後作業にある路線外発着作業について、
		路線外発着駅名データの変更を反映させます・
		元の路線外発着駅Indexが i の場合は、iOuterTerminalEkimeiMap[i]が新たな路線外発着駅Indexになります。
	*/
	virtual void adjustOuterTerminal(const std::vector<int>& iOuterTerminalEkimeiMap);

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
		駅番線の削除が誤って行われないように、
		iEkiTrack2Indexを入換番線にもつ作業があるかどうかを調べます。
	*/
	virtual int isExistRessyaOfEkiTrack2(int iEkiTrack2Index);

	/**
		路線外発着駅名の削除が誤って行われないように、
		iOuterTerminalIndexを路線外発着駅Indexにもつ作業があるかどうかを調べます。
	*/
	virtual int isExistRessyaOfOuterTerminal(int iOuterTerminalIndex);

	/**
	 */
	CentDedBeforeOperation& set(
		EBOperation eBOperation,
		bool bBoolData1,
		int iIntData1,
		int iIntData2,
		CdDedJikoku JikokuData1,
		CdDedJikoku JikokuData2,
		vector<tstring> strOperationNumber1,
		tstring strInOutLinkCode);

		
		///@}
};


} //namespace entDed


#endif /*CentDedBeforeOperation_h*/
