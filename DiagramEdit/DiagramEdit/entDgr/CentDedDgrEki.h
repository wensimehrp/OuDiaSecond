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
//	CentDedDgrEki.h
// ****************************************************************
*/
/** @file */
#ifndef  CentDedDgrEki_h
#define  CentDedDgrEki_h

//#include "CentDedEkiTrack2Cont.h"
//#include "CentDedEkiTrack2.h"
#include "CentDedDgrEkiTrack2.h"

#include <string>
#include "str\tstring.h"
#include <vector>

namespace entDgr{

// ****************************************************************
//	CentDedDgrEki
// ****************************************************************
/**
@brief
【概要】
『ダイヤグラムエンティティクラス群』の『ダイヤグラム駅』クラスです。
『ダイヤ』 (CentDedDgrDia) に含まれる『駅』１つを表します。

このクラスは、『ダイヤグラムダイヤ』 (CentDedDgrDia) に包含されます。

CentDedDgrDia : CentDedDgrEki の多重度は、

１：（『駅』の数） 

となります。

これは、

（『路線』(CentDedRosen)）：（『駅』（CentDedEki））

の多重度と同じです。

このクラスの属性として、『次駅までの駅間最小秒数』があります。
『次駅までの駅間最小秒数』から、『ダイヤグラムエンティティY座標』を導出します。

【使い方】

  原則では、このクラスのオブジェクトを生成するのは、
『ダイヤグラムダイヤ』 (CentDedDgrDia) クラスにのメソッドだけです。
クラスユーザーはこのクラスのオブジェクトを直接生成する用事はなく、
『ダイヤグラムダイヤ』 (CentDedDgrDia) クラスによって生成された
オブジェクトの属性を参照するだけです。


 */
class CentDedDgrEki
{
public:
	/**
		ダイヤグラム列車情報表示
	*/
	enum EDiagramRessyajouhouHyouji
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

private:	
	// ********************************
	///@name	属性
	// ********************************
	///@{
	/**
	 	駅名。
	 */
	tstring  m_strEkimei ;
	
	/**
	 	主要駅なら真です。
	 */
	bool  m_bIsSyuyoueki ;
	
	/**
	 	下り列車の駅間最小秒数。
	 
	 	この属性は、この駅と次の駅Indexまでの間の、
		下り列車の最小所要秒数です。
	 
	 	この値は、『ダイヤグラムY座標』での、駅間幅として
	 	使います。『ダイヤグラム』での駅間幅（Y座標）は、
	 	m_iEkikanSaisyouSecKudari,m_iEkikanSaisyouSecNoboriのうち
	 	小さいほうの値となります。
	 
	 	下り列車から見ての終点駅では、この値は 0 です。
	 
	 	また、この駅間での駅間最小所要秒数が計算不能（データなし）の場合は、
	 	 0 です。
	 */
	int m_iEkikanSaisyouSecKudari ;
	/**
	 	上り列車の駅間最小秒数。
	 
	 	この属性は、この駅と次の駅Indexまでの間の、
		上り列車の最小所要秒数です。
	 
	 	下り列車から見ての終点駅では、この値は 0 です。
	 
	 	また、この駅間での駅間最小所要秒数が計算不能（データなし）の場合は、
	 	 0 です。
	 */
	int m_iEkikanSaisyouSecNobori ;

	/**
		ダイヤグラムの既定の駅間幅。

		列車設定のない駅間の、ダイヤグラムビュー上での
		縦方向の幅を『ダイヤグラムエンティティY座標』単位(秒)で指定します。
	
		既定値は 60 です。
	*/
	int	m_iDgrYSizeEkikanDefault ;

	/**
		ダイヤグラム列車情報表示（下り）
	
		既定値は DiagramRessyajouhouHyouji_Origin です。
	*/	
	EDiagramRessyajouhouHyouji m_eDiagramRessyajouhouHyoujiKudari ;
	
	/**
		ダイヤグラム列車情報表示（上り）
	
		既定値は DiagramRessyajouhouHyouji_Origin です。
	*/
	EDiagramRessyajouhouHyouji m_eDiagramRessyajouhouHyoujiNobori ;

	/**
		この駅のY座標の高さ。
		当面は、0です。
	*/
	int m_iDgrYSize ;

	/**
		分岐駅設定
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
	環状線設定
	-1:環状線設定は無効
	0以上:起点駅のEkiIndex
	*/
	int m_iLoopOriginEkiIndex;

	/**
		環状駅設定が有効な時、通常とは反対向きに合流しているとみなします。
		この値が有効の時は環状線が○ではなく雫型の路線イメージになります。
		なお、CentDedDgrEkiにおけるこの値は、CentDedEkiにおける値と意味が異なります。
		CentDedEki:終点駅(環状線設定を行う側)で、LoopOppositeが有効な場合にTrue
		CentDedDgrEki:ダイヤを描写する工程において、便利なように値を変更しています。
			起点駅・終点駅ともに発着の場合は、原則としてLoopOppositeがfalseになります。
			起点駅が上り着で終点駅が下り着の場合、終点駅のみがTrueになります。
			起点駅が上り着で終点駅が発着の場合、起点駅のみがTrueになります。
			起点駅が発着で終点駅が下り着の場合、終点駅のみがTrueになります。
			つまり上り着～発着・・・発着～下り着と連なる環状線のうち、LoopOppositeが有効なのは一番上と一番下の環状線のみです。
			また、上り着～下り着と環状線が一つで完結している場合は、下り着がLoopOppositeがTrueになります。
			これは、発着駅でLoopOppositeを有効にすると、路線のつじつまが合わなくなるからです。
	*/
	bool m_bLoopOpposite;

	/**
		在線表表示設定
		分岐駅設定が有効の場合、この設定は無効となります。
		(暫定処置、可能にするかどうかは今後検討)

		CentDedEkiの駅時刻形式が発着・下り着時刻・上り着時刻の時のみ有効となります、
		ただし、下り着時刻の場合は、一つ下の駅が派生駅の場合もしくは、路線の終着駅の場合のみ有効、
		上り着時刻の場合は一つ上の駅が派生駅の場合もしくは、路線の始発駅の場合のみ有効となります。

		0:在線表を表示しません
		1:発着時刻駅として、在線表を表示します。
			この場合は、駅の横罫線は、在線表の上下、起点方用と終点方用を表示します
		2:下リ着時刻駅として、在線表を表示します
			在線表は、駅の横罫線の下方に表示します
		3:上り着時刻駅として、在線表を表示します
			在線表は、駅の横罫線の上方に表示します
	*/
	int m_iDiagramTrackDisplay;

	/**
		ダイヤグラムビューで在線表を表示するときに、表示を省略する番線を除いたインデクス
		省略する番線にはINT_MINが入ります
		(例)0、１，2の三つの番線があり、1番線が省略の場合。ここには、「0、INT_MIN、1」が入ります
	*/
	vector<int> m_iDiagramTrackIndex;

	/**
		駅の幅です。駅の最上部の線と最下部の線との幅を示します。
	*/
	int m_iEkiTrackDisplaySpace;

	/**
		この駅から次の駅までの背景色です
		0:基本色を使用
		1-4:個別色を使用
	*/
	int m_iDiagramColorNextEki;

	vector<tstring> m_strOuterTerminalEkimei;
	
	///@}	

private:
	// ********************************
	///@name 包含
	// ********************************
	///@{

	/**
	『ダイヤグラム駅番線』オブジェクトを保持します。

	*/
	CMuiCopied< CentDedDgrEkiTrack2 >	m_MuCentDedDgrEkiTrack2;

	///@}

// ********************************
//	コンストラクタ
// ********************************
 public:
	/**
	 @param strEkimei [in]
		駅名。
	 @param bIsSyuyoueki [in]
		主要駅なら真
	 @param iEkikanSaisyouSecKudari [in]
		下り列車の駅間最小秒数。
	 @param iEkikanSaisyouSecNobori [in]
		上り列車の駅間最小秒数。
	 @param iDiagramDgrYZahyouKyoriDefault [in]
		ダイヤグラムの既定の駅間幅。
	 @param eDiagramRessyajouhouHyoujiKudari [in]
		ダイヤグラム列車情報表示（下り）
	 @param eDiagramRessyajouhouHyoujiNobori [in]
		ダイヤグラム列車情報表示（上り）
	 @param iBrunchCoreEkiIndex [in]
		分駅駅設定の基幹駅駅Index
	 @param bBrunchOpposite [in]
		分駅駅設定の反転駅設定
	 @param iLoopOriginEkiIndex [in]
		環状線設定の起点駅駅Index
	 @param iBrunchCoreEkiIndex [in]
		環状線設定の反転駅設定
	 @param bLoopOpposite [in]
		在線表表示設定
	 @param strOuterTerminalEkimei [in]
		路線外発着駅名(ダイヤ略称)
	 @param pCentDedEkiTrack2Cont [in]
		駅番線コンテナ。これを基にCentDedDgrEkiTrack2を初期化します
	*/
	CentDedDgrEki( const tstring&  strEkimei ,
		bool bIsSyuyoueki , 
		int iEkikanSaisyouSecKudari ,
		int iEkikanSaisyouSecNobori , 
		int	iDiagramDgrYZahyouKyoriDefault , 
		EDiagramRessyajouhouHyouji eDiagramRessyajouhouHyoujiKudari ,
		EDiagramRessyajouhouHyouji eDiagramRessyajouhouHyoujiNobori,
		int iBrunchCoreEkiIndex,
		bool bBrunchOpposite,
		int iLoopOriginEkiIndex,
		bool bLoopOpposite,
		int iDiagramTrackDisplay,
		vector<int> m_iDiagramTrackIndex,
		vector<tstring> strOuterTerminalEkimei,
		int iDiagramColorNextEki,
		const CentDedEkiTrack2Cont* pCentDedEkiTrack2Cont
		) ;
	

	CentDedDgrEki() ;
	
	virtual ~CentDedDgrEki();
	
// ********************************
//	CentDedDgrEki
// ********************************
 public:
	// ********************************
	///@name	CentDedDgrEki-属性
	// ********************************
	///@{
	tstring  getEkimei()const{ return m_strEkimei ;};
	bool getIsSyuyoueki()const{	return m_bIsSyuyoueki ; } ;
	int getEkikanSaisyouSecKudari()const
	{	return m_iEkikanSaisyouSecKudari ; };
	int getEkikanSaisyouSecNobori()const
	{	return m_iEkikanSaisyouSecNobori ; };
	int	getDgrYSizeEkikanDefault()const
	{	return m_iDgrYSizeEkikanDefault ;};

	EDiagramRessyajouhouHyouji getDiagramRessyajouhouHyoujiKudari()const
	{	return m_eDiagramRessyajouhouHyoujiKudari ;};
	EDiagramRessyajouhouHyouji getDiagramRessyajouhouHyoujiNobori()const
	{	return m_eDiagramRessyajouhouHyoujiNobori ;};
	int getDgrYSize()const{	return m_iDgrYSize ;};
	int getBrunchCoreEkiIndex()const { return m_iBrunchCoreEkiIndex; };
	int getLoopOriginEkiIndex()const { return m_iLoopOriginEkiIndex; };
	bool getBrunchOpposite()const { return m_bBrunchOpposite; };
	bool getLoopOpposite()const { return m_bLoopOpposite; };
	int getDiagramTrackDisplay()const { return m_iDiagramTrackDisplay; };
	tstring getOuterTerminalEkimei(const int iIndex)const { return m_strOuterTerminalEkimei[iIndex]; };
	int getDiagramColorNextEki()const { return m_iDiagramColorNextEki; };

	vector<int> getDiagramTrackIndex()const { return m_iDiagramTrackIndex; };
	int getDiagramTrackIndex(int iIndex)const;
	void setDiagramTrackIndex(vector<int> value) { m_iDiagramTrackIndex = value; };

	CMuiCopied< CentDedDgrEkiTrack2 > getCentDedDgrEkiTrack2Cont()const
	{	return m_MuCentDedDgrEkiTrack2;	};
	///@}
	// ********************************
	///@name	CentDedDgrEki-操作
	// ********************************
	///@{
	/**
		@param bIsOrigin [in]
		true:返り値に在線表の表示スペース分を加算して返します。
			m_iDiagramTrackDisplay>0の時は、在線表表示駅なので、
			起点方の駅線・番線別在線線、終点方の駅線が必要となります。
			従って、m_iDgrYSizeEkikanDefault*(番線数+1)の空間が加算されます。
		false:従来通りの挙動、この駅と次の駅の間の距離を返します。
		m_iDiagramTrackDisplay==0の時は、true,falseとも同じ値を返します。
	  @return
		この駅の在線表表示スぺースと、
	 	この駅から下り方向の次の駅（『駅Index』が次の駅）までの、
	 	『ダイヤグラムエンティティY座標』での距離の合計を返します。
	 
	 	  この値は、『下り列車の駅間最小秒数』と『上り列車の駅間最小秒数』の
	 	うちの小さいほうです。
	 
	 	  但し、『下り列車の駅間最小秒数』が 0 以下・『上り列車の駅間最小秒数』
	 	が 1 以上の場合は、この値は『上り列車の駅間最小秒数』となります。
	 	反対に、『上り列車の駅間最小秒数』が 0 以下・
	 	『下り列車の駅間最小秒数』が 1 以上の場合は、この値は
	 	『下り列車の駅間最小秒数』となります。
	 
	 	  この値の最小値は60です。
	 */
	int getDgrYZahyouKyoriOrg()const;
	/**
		@param bIsOrigin [in]
		true:返り値に在線表の表示スペース分を加算して返します。
			m_iDiagramTrackDisplay>0の時は、在線表表示駅なので、
			起点方の駅線・番線別在線線、終点方の駅線が必要となります。
			従って、m_iDgrYSizeEkikanDefault*(番線数+1)の空間が加算されます。
		false:従来通りの挙動、この駅と次の駅の間の距離を返します。
		m_iDiagramTrackDisplay==0の時は、true,falseとも同じ値を返します。
	  @return
		この駅から下り方向の次の駅（『駅Index』が次の駅）までの、
		『ダイヤグラムエンティティY座標』での距離を返します。

		  この値は、『下り列車の駅間最小秒数』と『上り列車の駅間最小秒数』の
		うちの小さいほうです。

		  但し、『下り列車の駅間最小秒数』が 0 以下・『上り列車の駅間最小秒数』
		が 1 以上の場合は、この値は『上り列車の駅間最小秒数』となります。
		反対に、『上り列車の駅間最小秒数』が 0 以下・
		『下り列車の駅間最小秒数』が 1 以上の場合は、この値は
		『下り列車の駅間最小秒数』となります。

		  この値の最小値は60です。
	 */
	int getDgrYZahyouKyoriTer()const;

	/**
		駅の在線表表示スペースの表示範囲距離を返します。
			m_iDiagramTrackDisplay>0の時は、在線表表示駅なので、
			起点方の駅線・番線別在線線、終点方の駅線が必要となります。
			従って、m_iDgrYSizeEkikanDefault*(番線数+1)の空間が加算されます。
			m_iDiagramTrackDisplay=0の時は0を返します
	*/
	int getDgrEkiTrackDisplaySpace()const;
	void setEkiTrackDisplaySpace(int value)
	{
		m_iEkiTrackDisplaySpace = value;
	};
	void setDgrYSizeEkikanDefault(int value)
	{
		m_iDgrYSizeEkikanDefault = value;
	};
	///@}

};

} //namespace entDgr
#endif /*CentDedDgrEki_h*/
