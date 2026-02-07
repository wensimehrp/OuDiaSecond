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
//	CentDedAfterOperation.h
//	$Id: CentDedAfterOperation.h  $
// ****************************************************************
*/
/** @file */
#ifndef  CentDedAfterOperation_h
#define  CentDedAfterOperation_h

#include "CdDedJikoku.h"
//#include "CentDedBeforeOperationCont.h"

namespace entDed{
	using namespace OuLib::NsMu ;
	using namespace std ;

//class CentDedBeforeOperationCont;
//class CentDedAfterOperationCont;

// ****************************************************************
//	CentDedAfterOperation
// ****************************************************************
/**
@brief
  DiagramEdit の、１列車の一つの後作業を表します。

 */
class CentDedAfterOperation : public CChildBase
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
		virtual CentDedAfterOperation* getAfterOperation()
		{
			CentDedAfterOperation* pOuter = (CentDedAfterOperation*)(((char*)this) - offsetof(CentDedAfterOperation, m_CentDedBeforeOperationCont));
			return pOuter;
		};
		/**
		@return
			このコンテナが CentDedBeforeOperation に包含されている場合は、
			CentDedBeforeOperation のアドレス。
			そうでないならNULL。
		*/
		virtual const CentDedAfterOperation* getAfterOperation()const
		{
			const CentDedAfterOperation* pOuter = (const CentDedAfterOperation*)(((char*)this) - offsetof(CentDedAfterOperation, m_CentDedBeforeOperationCont));
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
		virtual CentDedAfterOperation* getAfterOperation()
		{
			CentDedAfterOperation* pOuter = (CentDedAfterOperation*)(((char*)this) - offsetof(CentDedAfterOperation, m_CentDedAfterOperationCont));
			return pOuter;
		};
		/**
		@return
			このコンテナが CentDedEkiJikoku に包含されている場合は、
			CentDedEkiJikoku のアドレス。
			そうでないならNULL。
		*/
		virtual const CentDedAfterOperation* getAfterOperation()const
		{
			const CentDedAfterOperation* pOuter = (const CentDedAfterOperation*)(((char*)this) - offsetof(CentDedAfterOperation, m_CentDedAfterOperationCont));
			return pOuter;
		};
		///@}
	};
	/**
		『作業』を表す列挙です。
	 */
	enum class EAOperation
	{
		/**
			 入換(規定値)
			 番線間の移動を表します。
			 この作業が保持する番線へ、
			 列車の発着番線・より前にある入換番線・解結が行われた番線からの移動を意味します。
		 */
		AOperation_Shunt,
		/**
			増結、他の編成の増結を表します。
			この作業は、増結相手の編成の前作業も保持します。
		*/
		AOperation_Connect,
		/**
			解結、編成の一部の解結を表します。
			この作業は、解結対象の編成の後作業も保持します。
		*/
		AOperation_Release,
		/**
			 入区、終着駅/解結編成の最後の作業でのみ使用可能
		 */
		AOperation_In,
		/**
			路線外終着、終着駅/解結編成の最後の作業でのみ使用可能
		*/
		AOperation_Outer,
		/**
			次列車接続 。
			終着駅/解結編成の最後の作業でのみ使用可能
			入区・路線外終着以外は全てこれになります。
		 */
		AOperation_Junction,
		/**
			運用番号変更 。
			編成はそのままに、割り当てられる運用番号だけを変更します
		 */
		AOperation_NumberChange
	};


private:
	// ********************************
	///@name 属性
	// ********************************
	///@{
	/**
		作業種類です。
	*/
	EAOperation m_eAOperation;

	//※印が付いた属性は、運用探索によって割り当てられるものです
	/**
		入換:この作業の入換発時刻を、時刻表の表示モードにおける
			当駅の発時刻とみなすか否かを表す値です。
			false(規定値):発時刻として扱いません。
			true:発時刻として扱います。
			なお、後作業内に複数の入換が存在し、二つ以上の入換作業において、
			この値がtrueの場合、後作業コンテナ内で最もIndexが若いもの(時系列で前の物)が有効になります。
		増結:増結編成を、運用番号基準で親編成の前後どちらに接続するかを表します
			(例)親編成が01A、増結編成が03Aの運用番号の場合、
			true:増結編成を親編成よりも前に連結します。例の運用番号は[03A],[01A]となります
			false(規定値):増結編成を親編成よりも後ろに連結します。例の運用番号は[01A],[03A]となります
		解結:未使用
		入区:未使用
		路線外終着:未使用
		※次列車接続:後列車接続成功(Ver2.05 BoolData2から再変更)
			この値がtrueの時は、運用探索において、後列車が見つかったことを示します。
			その場合、在線表表示駅において、この作業がある番線の在線横線は表示せず、
			後列車に委任します。
			次列車接続:増結表示省略//Ver2.05まで
				この値はtrueの時、
				カスタマイズ時刻表で、増結矢印「↳」が表示され、並び順が変化する処理を行いません
		運用番号変更:運用番号順反転
	*/
	bool m_bBoolData1;

	/**
		入換:未使用
		※増結:増結前増結編成運用番号が、割り当て済みか否かを表します
		解結:未使用
		入区:未使用
		路線外終着:未使用
		次列車接続:未使用(Ver2.05から)
		運用番号変更:未使用
	*/
	bool m_bBoolData2;

	/**
		入換:入換前の番線
		増結:未使用
		解結:解結編成位置
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
		入区:未使用
		路線外終着:路線外終着駅のIndex
		次列車接続:次列車接続タイプ
			この作業で終わる列車と次の列車との関係性を示します、
			0:別列車(規定値
				この列車と次の列車が特段関係がないことを表します。
			1:種別変更
				この列車と次の列車が種別変更の関係にあることを表します。
				ここでの種別変更とは、種別が変わることを明示することを意味します。
			2:列車情報変更
				この列車と次の列車との間で、何らかの列車情報(列車番号など)が変わる場合に用います
			3:同一列車扱い
				この列車と次の列車が完全に同一列車である場合に用います。
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
		入区:未使用
		路線外終着:未使用
		※次列車接続:列車方向
			運用機能により、この作業から別に作業に接続する場合、
			この作業が行われる番線に移動する縦線が、どちらの方向から延びているかを示します。
			junctionOperationの時に、この値を次作業(BeforeJunction)に書き込みます。
			なお、この作業を含む列車と、次作業を含む列車の列車方向が異なる場合は、値が反転します。
				-2:この列車の列車方向の起点方から(入換があるので確定)
				-1:この列車の列車方向の起点方から(反転駅設定により変化する)
				0:解結後に入換無しで接続(デフォルト値)
				1:(この値にはなりません)
				2:この列車の列車方向の終点方から(入換があるので確定)
			この値は、実表示に使われるわけではなく、接続相手の前列車接続に書き込む前の仮置きです。
			(Ver2.05 一度、IntData3に移動したが、増結駅OrderをCustomizeJikokuhyouContentに移したので、IntData2に戻した)
		運用番号変更:未使用
	*/
	int m_iIntData2;

	/**
		入換:列車の入換発時刻
		増結:増結を行う時刻、ダイヤグラムにおける、増結マークの表示位置になるほか、
			増結編成の前作業の作業時刻の原点になります。
			NULL時刻の場合は、列車の着時刻・直前の入換着時刻・
			出区時刻・路線外終着列車の当駅着時刻が、適用されます。
		解結:解結を行う時刻、ダイヤグラムにおける、解結マークの表示位置になるほか、
			解結編成の後作業の作業時刻の原点になります。
			NULL時刻の場合は、列車の発時刻・直後の入換発時刻・
			入区時刻・路線外終着列車の当駅発時刻が、適用されます。
		入区:入区時刻、ダイヤグラムビューにおける丸印の位置を示します。
		路線外終着:当駅の発時刻です。
			従来は、CentDedEkijikokuにおける発時刻を用いていましたが、作業側に移動します。
			これは、(データ上の)終着駅における時刻形式を統一させるためです。
			この値が空の時は、当駅の着時刻と同時刻とみなします。
		次列車接続:終点時刻、次列車への接続を探索する際、この時刻を基準とします。
			デフォルト値はNULL時刻です。
		運用番号変更:未使用
	*/
	CdDedJikoku m_JikokuData1;

	/**
		入換:列車の入換着時刻
			この値がNULL時刻の場合、入換発時刻と同一とみなします。
		増結:未使用
		解結:未使用
		入区:未使用
		路線外終着:路線外終着駅の到着時刻
		※次列車接続:列車接続時刻(在線表有り駅)
			運用機能により、この作業から別の作業に接続する場合、予めこの作業の接続時刻を求めておき、
			junctionOperationの時に、この値を次作業(BeforeJunction)に書き込みます。
			デフォルト値はNULL時刻です。
			この値は、実表示に使われるわけではなく、接続相手の前列車接続に書き込む前の仮置きです。
		運用番号変更:未使用
	*/
	CdDedJikoku m_JikokuData2;
	
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
		※入区:運用番号
			複数編成が連結した状態で入区する場合、各編成に対して一つづつ運用番号を割り当て、
			それを配列形式で保持します。
			この作業の運用番号は、運用探索によって求まります。
		※路線外終着:運用番号
			複数編成が連結した状態で路線外終着駅に到着する場合、各編成に対して一つづつ運用番号を割り当て、
			それを配列形式で保持します。
		※次列車接続:運用番号
			複数編成が連結した状態の場合、各編成に対して一つづつ運用番号を割り当て、
			それを配列形式で保持します。
			この作業の運用番号は、運用探索によって求まります。
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
		入区:未使用
		路線外終着:未使用
		次列車接続:未使用
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
		入区:未使用
		路線外終着:未使用
		次列車接続:未使用
		※運用番号変更:反転後運用番号(Ver2.06.05～)
			運用番号反転が有効な場合は、ここに新しい運用番号を割り当てます
	*/
	vector<tstring> m_strOperationNumber3;

	/**
		入換:未使用
		増結:未使用
		解結:未使用
		入区:入出区連携コード(Ver2.05から)
			入区・路線外終着と出区・路線外始発に同じコードが設定されている場合、
			運用接続時に、入区側に割り当てられた運用番号が、出区側に自動で割り当てられます。
		路線外終着:入出区連携コード(Ver2.05から)
		次列車接続:未使用
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
	CentDedAfterOperation() ;
	
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
	CentDedAfterOperation( 
		EAOperation EAOperation,
		bool bBoolData1,
		int iIntData1,
		int iIntData2,
		CdDedJikoku JikokuData1,
		CdDedJikoku JikokuData2) ;

	//入換
	/**
		 @param iShuntTrackIndex [in]
			入換後の番線Indexを表します。
		 @param OperationHatsuJikoku [in]
			列車の入換発時刻を表します。
		 @param OperationChakuJikoku [in]
			列車の入換着時刻を表します。
		 @param bIsDisplayHatsuJikoku [in]
			入換発時刻を発時刻とみなすか否かを表します。
		*/
	CentDedAfterOperation(
		EAOperation EAOperation,
		int iShuntTrackIndex,
		CdDedJikoku	OperationHatsuJikoku,
		CdDedJikoku	OperationChakuJikoku,
		bool bIsDisplayHatsuJikoku);

	//増結
	/**
		@param bIsConnectToFront [in]
		増結位置の前後を表します。
		@param ConnectJikoku [in]
		増結時刻を表します。
		*/
	CentDedAfterOperation(
		EAOperation EAOperation,
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
	CentDedAfterOperation(
		EAOperation EAOperation,
		int iReleasePos,
		int iReleaseIndexCount,
		CdDedJikoku	ReleaseJikoku);

	//入区
	/**
		 @param Jikoku [in]
			入区時刻を表します。
		運用番号を表します。
	 */
	CentDedAfterOperation(
		EAOperation EAOperation,
		CdDedJikoku	InJikoku,
		tstring strInOutLinkCode);

	//路線外終着
	/**
		 @param iOuterShuchakuekiIndex [in]
			路線外終着駅Indexを表します。
		 @param HatsuJikoku [in]
			当駅の発時刻を表します。
		 @param OuterShuchakuJikoku [in]
			路線外終着駅の到着時刻を表します。
	 */
	CentDedAfterOperation(
		EAOperation EAOperation,
		int iOuterShuchakuekiIndex,
		CdDedJikoku	HatsuJikoku,
		CdDedJikoku	OuterShuchakuJikoku,
		tstring strInOutLinkCode);

	//次列車接続
	/**
		 @param TerminalJikoku [in]
			終点時刻を表します。
		 @param bDisableConnectDisplay [in]
			増結表示省略設定を表します。
			(Ver2.05削除)
		@param iNextJunctionType[in]
			Ver2.05から
			次列車との関係性を表します。
		運用番号を表します。
	 */
	CentDedAfterOperation(
		EAOperation EAOperation,
		CdDedJikoku	TerminalJikoku,
		int iNextJunctionType);
		//bool bDisableConnectDisplay);

	//運用番号変更
	/**
	 @param strOperationNumber [in]
		運用番号を表します。
	 @param bOperationNumberReverse [in]
		運用番号順反転の有効無効を表します。
	 */
	CentDedAfterOperation(
		EAOperation EAOperation,
		vector<tstring> strOperationNumber,
		bool bOperationNumberReverse);
		
	/** 
	
	@exception LException 
	*/
	CentDedAfterOperation& operator=( const CentDedAfterOperation& value ) ;
public:
	// ********************************
	///@name CChildBase-操作
	// ********************************
	///@{
	virtual void setParent( CParentBase* pParent );

	//virtual void modifyOperationJikoku(int iSecond);
	///@}

	// ********************************
	///@name CentDedAfterOperation-包含
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
	///@name CentDedAfterOperation-属性
	// ********************************
	///@{

		/**
		作業種類を参照することができます。
		m_EAOperationを返します
		*/
	EAOperation getAOperation()const
	{
		return m_eAOperation;
	}

	/**
	m_EAOperationに代入します。
	*/
	//CentDedAfterOperation& setAOperation(const EAOperation value);

	/**
		この作業が、AOperation_In,AOperation_Outer,AOperation_Junctionの
		いずれかの場合に、Trueを返します。
		つまり、この作業を含む列車(および解結後作業)の、最後の作業であるということです。
	*/
	bool isLastOperation()const;

	//入換用

		/**
		入換後の番線Indexを参照することができます。
		m_iIntData1を返します
		*/
	int getShuntTrackIndex()const
	{
		return m_iIntData1;
	}

	/**
	m_iIntData1に代入します。
	*/
	CentDedAfterOperation& setShuntTrackIndex(const int value)
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
	CentDedAfterOperation& setOperationHatsuJikoku(const CdDedJikoku& value)
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
	CentDedAfterOperation& setOperationChakuJikoku(const CdDedJikoku& value)
	{
		m_JikokuData2 = value;
		return *this;
	}

	/**
	m_bBoolData1を参照することができます。
	*/
	bool	getIsDisplayHatsuJikoku()const
	{
		return m_bBoolData1;
	}

	/**
	m_bBoolData1に代入します。
	*/
	CentDedAfterOperation& setIsDisplayHatsuJikoku(const bool& value)
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
	CentDedAfterOperation& setIsConnectToFront(const bool value)
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
	CentDedAfterOperation& setConnectJikoku(const CdDedJikoku& value)
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
	CentDedAfterOperation& setOperationNumberAfter(const vector<tstring>& value)
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
	CentDedAfterOperation& setOperationNumberMain(const vector<tstring>& value)
	{
		m_strOperationNumber2 = value;
		return *this;
	};
	/**
		m_strOperationNumber3に代入します。
		作業が増結の場合は、増結運番割り当て済みフラグを立てます。
	*/
	CentDedAfterOperation& setOperationNumberSub(const vector<tstring>& value)
	{
		m_strOperationNumber3 = value;
		if (m_eAOperation == EAOperation::AOperation_Connect)
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
	CentDedAfterOperation& setReleasePos(const int value)
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
	CentDedAfterOperation& setReleaseIndexCount(const int value)
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
	CentDedAfterOperation& setReleaseJikoku(const CdDedJikoku& value)
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
	CentDedAfterOperation& setOperationNumberBefore(const vector<tstring>& value)
	{
		m_strOperationNumber1 = value;
		splitOperationNumber();
		return *this;
	}

	void splitOperationNumber();

	//入区・路線外終着・次列車接続・運用番号変更共用
	/**
		運用番号全体を参照することができます。
		m_strOperationNumber1を返します
		Ver2.06.05 運用番号変更の場合、運用番号順反転設定によって返す値が変わります
		運用番号順反転無効の場合は、m_strOperationNumber1を、
		運用番号順反転有効の場合は、m_strOperationNumber3を返します。
	*/
	vector<tstring> getOperationNumber()const
	{
		if (m_eAOperation == EAOperation::AOperation_NumberChange &&
			m_bBoolData1)
		{
			return m_strOperationNumber3;
		}
		return m_strOperationNumber1;
	};

	/**
	m_strOperationNumber1に代入します。
	*/
	CentDedAfterOperation& setOperationNumber(const vector<tstring>& value)
	{
		m_strOperationNumber1 = value;
		return *this;
	};

	int getOperationNumberCount() const
	{
		return m_strOperationNumber1.size();
	}

	//入区・路線外終着共用
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
	CentDedAfterOperation& setInOutLinkCode(const tstring& value)
	{
		m_strInOutLinkCode = value;
		return *this;
	}

	//入区用
	/**
			入区時刻を参照することができます。
			m_JikokuData1を返します
		*/
	CdDedJikoku	getInJikoku()const
	{
		return m_JikokuData1;
	}

	/**
		m_JikokuData1に代入します。
	*/
	CentDedAfterOperation& setInJikoku(const CdDedJikoku& value)
	{
		m_JikokuData1 = value;
		return *this;
	}


	//路線外終着用
	/**
		路線外終着駅のIndexを参照することができます。
		m_iIntData1を返します
		*/
	int getOuterShuchakuekiIndex()const
	{
		return m_iIntData1;
	}

	/**
	m_iIntData1に代入します。
	*/
	CentDedAfterOperation& setOuterShuchakuekiIndex(const int value)
	{
		m_iIntData1 = value;
		return *this;
	}

	/**
		当駅の発時刻を参照することができます。
		m_JikokuData1を返します
		*/
	CdDedJikoku	getHatsuJikoku()const
	{
		return m_JikokuData1;
	}

	/**
		m_JikokuData1に代入します。
	*/
	CentDedAfterOperation& setHatsuJikoku(const CdDedJikoku& value)
	{
		m_JikokuData1 = value;
		return *this;
	}

	/**
	路線外終着駅の到着時刻を参照することができます。
	m_JikokuData2を返します
	*/
	CdDedJikoku	getOuterShuchakuJikoku()const
	{
		return m_JikokuData2;
	}

	/**
	m_JikokuData2に代入します。
	*/
	CentDedAfterOperation& setOuterShuchakuJikoku(const CdDedJikoku& value)
	{
		m_JikokuData2 = value;
		return *this;
	}

	//次列車接続用
	/**
			終点時刻を参照することができます。
		m_JikokuData1を返します
		*/
	CdDedJikoku	getTerminalJikoku()const
	{
		return m_JikokuData1;
	}

	/**
		m_JikokuData1に代入します。
	*/
	CentDedAfterOperation& setTerminalJikoku(const CdDedJikoku& value)
	{
		m_JikokuData1 = value;
		return *this;
	}

	/**
		増結表示省略設定
		Ver2.00.05 追加
		Ver2.05 削除
	*/
	//CentDedAfterOperation& setDisableConnectDisplay(const bool& value)
	//{
	//	m_bBoolData1 = value;
	//	return *this;
	//};

	//bool getDisableConnectDisplay()const
	//{
	//	return m_bBoolData1;
	//}
	/**
		後列車あり(列車接続成功)を表します
		Ver2.00.05 BoolData2に変更
		Ver2.05 BoolData1に再変更
	*/
	CentDedAfterOperation& setJunctionSucceed(const bool& value)
	{
		m_bBoolData1 = value;
		return *this;
	};

	bool getJunctionSucceed()const
	{
		return m_bBoolData1;
	}

	/**
		次列車接続タイプを表します
		Ver2.05 追加
	*/
	CentDedAfterOperation& setNextJunctionType(const int& value)
	{
		m_iIntData1 = value;
		return *this;
	};

	int getNextJunctionType()const
	{
		return m_iIntData1;
	}

	/**
		前列車接続時刻(仮置き)を参照することができます。
		m_JikokuData2を返します
	 */
	CdDedJikoku	getJunctionJikoku()const
	{
		return m_JikokuData2;
	}

	/**
		m_JikokuData2に代入します。
	*/
	CentDedAfterOperation& setJunctionJikoku(const CdDedJikoku& value)
	{
		m_JikokuData2 = value;
		return *this;
	}

	/**
		前列車方向(仮置き)を表します
		Ver2.05 IntData3に変更
			→IntData2に再変更
	*/
	int getPrevRessyahoukou()const
	{
		return m_iIntData2;
	}

	CentDedAfterOperation& setPrevRessyahoukou(const int& value)
	{
		m_iIntData2 = value;
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
	CentDedAfterOperation& setOperationNumberAssigned(const vector<tstring>& value)
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
		ユーザーによって入力された、運用番号全体を参照することができます。
		常にm_strOperationNumber1を返します
	*/
	vector<tstring> getOperationNumberOriginal()const
	{
		return m_strOperationNumber1;
	};
	/**
		m_strOperationNumber1に代入します。
	*/
	//CentDedAfterOperation& setOperationNumber(const vector<tstring>& value)
	//{
	//	m_strOperationNumber1 = value;
	//	return *this;
	//};

	/**
		Ver2.06.05追加
		運用番号順反転を表します
	*/
	CentDedAfterOperation& setOperationNumberReverse(const bool& value)
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
	CentDedAfterOperation& set(
		EAOperation EAOperation,
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


#endif /*CentDedAfterOperation_h*/
