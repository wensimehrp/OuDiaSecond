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
//	CentDedDia.h
// ****************************************************************
*/
/** @file */
#ifndef  CentDedDia_h
#define  CentDedDia_h

#include <deque>
#include <unordered_map>
#include <list>
#include <map>

#include "CentDed.h"
#include "CentDedRessya.h"
#include "CentDedRessyaCont.h"
#include "CdDedRessyaProperty.h"
#include "Str/tstring.h"

namespace entDed{

class CentDedEkiCont ;

// ****************************************************************
//	CentDedDia
// ****************************************************************
/**
@brief
 DiagramEdit の、路線で設定されている『ダイヤ』１件を表します。

このクラスのインスタンスは、通常は『路線』 ( CentDedRosen ) に包含
されます。

実際には、

- 『路線』 (CentDedRosen) が『ダイヤ』 ( CentDedDia ) を
０以上複数包含
- 各『ダイヤ』 ( CentDedDia ) が『列車』 (CentDedRessya ) を
０以上複数包含

という関係になっています。

  このクラスは、『列車』 ( CentDedRessya ) を、下り・上りの別で
保持します。

　このクラスは、属性として『駅の数』・『列車種別数』を保持します。
ただし、これらは派生属性となっています。

<h5>int EkiCount</h5>
このダイヤに存在する『駅の数』です。
この属性は、 m_CentDedRessyaCont[]->m_iEkiCount をもとに決まります。

<h5>int RessyasyubetsuCount</h5>
『列車種別数』。列車種別の種類の数です。
この属性は、 m_CentDedRessyaCont[]->m_iRessyasyubetsuCount をもとに
決まります。

制約
 -------------------------------- 

操作のエラー検査・修正
 -------------------------------- 


△上書き(operator=): このオブジェクトが親オブジェクト CentDedDiaCont の子である場合で、代入元のダイヤ名が空文字列である場合、もしくは同じ名前のダイヤが CentDedDiaCont にある場合は例外スロー。
　(代入元が、CentDedDiaCont::set()に渡すとエラーになるようなオブジェクトである場合は、代入は例外スローとします)

△setName:このオブジェクトが親オブジェクト CentDedDiaCont の子である場合で、代入元のダイヤ名が空文字列である場合、もしくは同じ名前のダイヤが CentDedDiaCont にある場合は例外スローとします。
　(属性変更後のオブジェクトが、CentDedDiaCont::set()に渡すとエラーになるようなオブジェクトである場合は、エラーとします)

△setParent:adjustを実行する

 制約に合うように属性を修正(adjust)
 -------------------------------- 

○列車コンテナ(CentDedRessyaCont)にadjust()を委譲します。


*/
	/**
		OperationTableContentのiBeforeTypeおよびiAfterTypeに用います。
	*/
enum class EBeforeAfterType
{
	/**
		前列車接続及び次列車接続で、前後の列車と別列車である場合
	*/
	BeforeAfterType_Unrelated = 0,

	/**
		前列車接続及び次列車接続で、前後の列車と種別変更である場合
	*/
	BeforeAfterType_ClassChange,

	/**
		前列車接続及び次列車接続で、前後の列車と列車情報変更である場合
	*/
	BeforeAfterType_PropertyChange,

	/**
		前列車接続及び次列車接続で、前後の列車と同一列車扱いである場合
	*/
	BeforeAfterType_PropertySame,

	/**
		出入区の場合
	*/
	BeforeAfterType_OutIn,

	/**
		路線外始発・終着の場合
	*/
	BeforeAfterType_Outer,

	/**
		運用番号変更の場合
	*/
	BeforeAfterType_OperationNumberChange,

};
/**
	運用探索により、運用番号を割り当てる際に、
	運用表表示用に、運用番号別に列車を割り振るために使用します
	一つのOperationTableContentは、
	ある列車内での一つの運用番号の、開始作業と終了作業の組を表します
	aRessyaProperty:列車方向とIndex及び出区等時刻
	iSihatsuEkiOrder:開始作業のある駅Order
	iOuterShihatsuekiIndex:路線外始発駅Index,開始作業が路線外始発の場合のみ有効
	OuterShihatsuJikoku:路線外始発駅発時刻,開始作業が路線外始発の場合のみ有効
	iSyuuchakuEkiOrder:終了作業のある駅Order
	iOuterShuchakuekiIndex:路線外終着駅Index,終了作業が路線外終着の場合のみ有効
	OuterShuchakuJikoku:路線外終着駅着時刻,終了作業が路線外終着の場合のみ有効
	AfterOperation:検索用後作業、運用探索でOperationTableContentの並び順を決めるとき、
		次列車接続→前列車接続がつながっているところは、この後作業の次に挿入することで、
		並び順を確定させます。
	iBeforeType,iAfterType
		この列車の開始作業・終了作業の種類を表します。
		0-3:前列車接続・次列車接続の場合です、値は次列車接続タイプに準じ、
		0:別列車(および接続が切れている)
		1:種別変更
		2:列車情報変更
		3:同一列車扱い
		4:出区・入区
		5:路線外始発・終着
		6:運用番号変更
*/
struct OperationTableContent {
	CdDedRessyaProperty aRessyaProperty;
	int iSihatsuEkiOrder;
	EBeforeAfterType eBeforeType;
	int iOuterShihatsuekiIndex;
	CdDedJikoku OuterShihatsuJikoku;
	CdDedJikoku ChakuJikoku;
	int iSyuuchakuEkiOrder;
	EBeforeAfterType eAfterType;
	int iOuterShuchakuekiIndex;
	CdDedJikoku HatsuJikoku;
	CdDedJikoku OuterShuchakuJikoku;
	const CentDedAfterOperation* AfterOperation;

	OperationTableContent()
		: aRessyaProperty(CdDedRessyaProperty())
		, iSihatsuEkiOrder(0)
		, eBeforeType(EBeforeAfterType::BeforeAfterType_Unrelated)
		, iOuterShihatsuekiIndex(INT_MIN)
		, OuterShihatsuJikoku(CdDedJikoku())
		, ChakuJikoku(CdDedJikoku())
		, iSyuuchakuEkiOrder(0)
		, eAfterType(EBeforeAfterType::BeforeAfterType_Unrelated)
		, iOuterShuchakuekiIndex(INT_MIN)
		, HatsuJikoku(CdDedJikoku())
		, OuterShuchakuJikoku(CdDedJikoku())
		, AfterOperation(NULL)
	{}

	OperationTableContent(
		CdDedRessyaProperty aRessyaProperty)
		: aRessyaProperty(aRessyaProperty)
		, iSihatsuEkiOrder(0)
		, eBeforeType(EBeforeAfterType::BeforeAfterType_Unrelated)
		, iOuterShihatsuekiIndex(INT_MIN)
		, OuterShihatsuJikoku(CdDedJikoku())
		, ChakuJikoku(CdDedJikoku())
		, iSyuuchakuEkiOrder(0)
		, eAfterType(EBeforeAfterType::BeforeAfterType_Unrelated)
		, iOuterShuchakuekiIndex(INT_MIN)
		, HatsuJikoku(CdDedJikoku())
		, OuterShuchakuJikoku(CdDedJikoku())
		, AfterOperation(NULL)
	{}

	//出区作業から始まるとき、および
	//"前列車のない"前列車接続作業から始まるときに使います
	//eBeforeTypeで区別をつけます
	OperationTableContent(
		CdDedRessyaProperty aRessyaProperty,
		int iSihatsuEkiOrder,
		EBeforeAfterType eBeforeType)
		: aRessyaProperty(aRessyaProperty)
		, iSihatsuEkiOrder(iSihatsuEkiOrder)
		, eBeforeType(eBeforeType)
		, iOuterShihatsuekiIndex(INT_MIN)
		, OuterShihatsuJikoku(CdDedJikoku())
		, ChakuJikoku(CdDedJikoku())
		, iSyuuchakuEkiOrder(0)
		, eAfterType(EBeforeAfterType::BeforeAfterType_Unrelated)
		, iOuterShuchakuekiIndex(INT_MIN)
		, HatsuJikoku(CdDedJikoku())
		, OuterShuchakuJikoku(CdDedJikoku())
		, AfterOperation(NULL)
	{}

	//前列車接続作業から始まるときに使います
	//AfterOperationは前列車の終端(次列車接続)作業で、
	//運用表組立の際の位置決めに用います。
	OperationTableContent(
		CdDedRessyaProperty aRessyaProperty,
		int iSihatsuEkiOrder,
		const CentDedAfterOperation * AfterOperation,
		EBeforeAfterType eBeforeType)
		: aRessyaProperty(aRessyaProperty)
		, iSihatsuEkiOrder(iSihatsuEkiOrder)
		, eBeforeType(eBeforeType)
		, iOuterShihatsuekiIndex(INT_MIN)
		, OuterShihatsuJikoku(CdDedJikoku())
		, ChakuJikoku(CdDedJikoku())
		, iSyuuchakuEkiOrder(0)
		, eAfterType(EBeforeAfterType::BeforeAfterType_Unrelated)
		, iOuterShuchakuekiIndex(INT_MIN)
		, HatsuJikoku(CdDedJikoku())
		, OuterShuchakuJikoku(CdDedJikoku())
		, AfterOperation(AfterOperation)
	{}

	//路線外始発作業から始まるときに使います
	OperationTableContent(
		CdDedRessyaProperty aRessyaProperty,
		int iSihatsuEkiOrder,
		int iOuterShihatsuekiIndex,
		CdDedJikoku OuterShihatsuJikoku,
		CdDedJikoku ChakuJikoku)
		: aRessyaProperty(aRessyaProperty)
		, iSihatsuEkiOrder(iSihatsuEkiOrder)
		, eBeforeType(EBeforeAfterType::BeforeAfterType_Outer)
		, iOuterShihatsuekiIndex(iOuterShihatsuekiIndex)
		, OuterShihatsuJikoku(OuterShihatsuJikoku)
		, ChakuJikoku(ChakuJikoku)
		, iSyuuchakuEkiOrder(0)
		, eAfterType(EBeforeAfterType::BeforeAfterType_Unrelated)
		, iOuterShuchakuekiIndex(INT_MIN)
		, HatsuJikoku(CdDedJikoku())
		, OuterShuchakuJikoku(CdDedJikoku())
		, AfterOperation(NULL)
	{}

	////出区作業から始まるときに使います
	//OperationTableContent(
	//	CdDedRessyaProperty aRessyaProperty,
	//	int iSihatsuEkiOrder,
	//	bool bIsOut)
	//	: aRessyaProperty(aRessyaProperty)
	//	, iSihatsuEkiOrder(iSihatsuEkiOrder)
	//	, bIsOut(bIsOut)
	//	, iOuterShihatsuekiIndex(INT_MIN)
	//	, OuterShihatsuJikoku(CdDedJikoku())
	//	, ChakuJikoku(CdDedJikoku())
	//	, iSyuuchakuEkiOrder(0)
	//	, bIsIn(false)
	//	, iOuterShuchakuekiIndex(INT_MIN)
	//	, HatsuJikoku(CdDedJikoku())
	//	, OuterShuchakuJikoku(CdDedJikoku())
	//	, AfterOperation(NULL)
	//	, bContinue(false)
	//{}
};

/**
	カスタマイズ時刻表の一列に表示する内容を表します。
	iRessyaIndexCont:この列に表示する列車のインデクスです。

	iSihatsuEkiOrder:この列の起点側を路線外始発状に表示するとき(スイッチバックなど)、
		この変数に、実際の始発駅(実際の始発駅からさらに路線外始発になっている場合含む)の駅Orderを入れます
		また、始発側が環状運転の場合は、-1または-2を入れます(-2の場合は"環状線"だが、現時点では同じ扱い)
		通常の表示の場合はINT_MINを入れます(規定値)。
	iOuterShihatsuEkiIndex:上記iSihatsuEkiOrderが0以上の場合に、その始発駅からさらに路線外始発になっている時は、
		この変数に、路線外始発駅インデクスを入れます(規定値は-1)
		なお、通常の路線外始発(iRessyaIndexContの先頭列車の開始作業が路線外始発)の場合は、この値は用いません。
	OuterShihatsuJikoku:上記iSihatsuEkiOrderが-1以外の場合に、
		この変数に、路線外始発欄に表示する発車時刻を入れます(規定値はNULL時刻)
		なお、通常の路線外始発(iRessyaIndexContの先頭列車の開始作業が路線外始発)の場合は、この値は用いません。
		(例)A,B,Cの3列車が一続きで、この列にはB,Cの2列車を表示する場合、
		(1)A列車が前列車接続または出区の場合、始発駅発時刻をこの変数に入れます。
		(2)A列車が路線外始発の場合、路線外始発駅発時刻をこの変数に入れます。
	ChakuJikoku:上記iSihatsuEkiOrderが-1以外の場合に、
		この変数に、"この列の最初に表示する列車の始発駅の"着時刻を入れます(規定値はNULL時刻)
		なお、通常の路線外始発(iRessyaIndexContの先頭列車の開始作業が路線外始発)の場合は、この値は用いません。
		(例)A,B,Cの3列車が一続きで、この列にはB,Cの2列車を表示する場合、
		A列車の終着駅着時刻をこの変数に入れます。

	iSyuuchakuEkiOrder:この列の終点側を路線外終着状に表示するとき(スイッチバックなど)、
		この変数に、実際の終着駅(実際の終着駅からさらに路線外終着になっている場合含む)の駅Orderを入れます
		また、終着側が環状運転の場合は、-1または-2を入れます(-2の場合は"環状線"だが、現時点では同じ扱い)
		通常の表示の場合はINT_MINを入れます(規定値)。
	iOuterShuchakuEkiIndex:上記iSyuuchakuEkiOrderが0以上の場合に、その終着駅からさらに路線外終着になっている時は、
		この変数に、路線外終着駅インデクスを入れます(規定値は-1)
		なお、通常の路線外終着(iRessyaIndexContの先頭列車の開始作業が路線外終着)の場合は、この値は用いません。
	OuterShuchakuJikoku:上記iSyuuchakuEkiOrderが-1以外の場合に、
		この変数に、路線外始発欄に表示する発車時刻を入れます(規定値はNULL時刻)
		なお、通常の路線外終着(iRessyaIndexContの末尾列車の終了作業が路線外終着)の場合は、この値は用いません。
		(例)A,B,Cの3列車が一続きで、この列にはA,Bの2列車を表示する場合、
		(1)C列車が次列車接続または入区の場合、終着駅着時刻をこの変数に入れます。
		(2)C列車が路線外終着の場合、路線外終着駅着時刻をこの変数に入れます。
	HatsuJikoku:上記iSyuuchakuEkiOrderが-1以外の場合に、
		この変数に、"この列の最後に表示する列車の終着駅の"発時刻を入れます(規定値はNULL時刻)
		なお、通常の路線外終着(iRessyaIndexContの末尾列車の終了作業が路線外終着)の場合は、この値は用いません。
		(例)A,B,Cの3列車が一続きで、この列にはA,Bの2列車を表示する場合、
		C列車の始発駅発時刻をこの変数に入れます。
	iRessyasyubetsuIndex:iRessyaIndexContが空の時は、この列の全列車を、この種別で表示します。
	strRessyabangou、strRessyamei、strGousuu,strOperationNumber:iRessyaIndexContが空の時は、この列の列車情報をこの値で表示します。
	eEkiatsukai,iRessyaTrackIndex:iRessyaIndexContが空の時、iReleaseEkiOrderまたはiConnectEkiOrder駅の描写の時に用います。
	iShiftSecond:パターンダイヤプレビュー機能が有効な時、ここに元列車との時刻差(秒)を入れ、表示の時にその分だけ時刻をシフトします
*/
struct CustomizeJikokuhyouContent {
	vector<int> iRessyaIndexCont;
	int iSihatsuEkiOrder;
	int iOuterShihatsuEkiIndex;
	CdDedJikoku OuterShihatsuJikoku;
	CdDedJikoku ChakuJikoku;
	int iSyuuchakuEkiOrder;
	int iOuterShuchakuEkiIndex;
	CdDedJikoku HatsuJikoku;
	CdDedJikoku OuterShuchakuJikoku;
	int iReleaseEkiOrder;
	int iConnectEkiOrder;
	int	iRessyasyubetsuIndex;
	tstring strRessyabangou;
	tstring strRessyamei;
	tstring strGousuu;
	vector<tstring> strOperationNumber;
	CentDedEkiJikoku::EEkiatsukai eEkiatsukai;
	int iRessyaTrackIndex;
	EBeforeAfterType eEAfterType;
	int	iPrevRessyasyubetsuIndex;
	tstring strPrevRessyabangou;
	tstring strPrevRessyamei;
	tstring strPrevGousuu;
	vector<tstring> strPrevOperationNumber;
	CentDedEkiJikoku::EEkiatsukai ePrevEkiatsukai;
	int iPrevRessyaTrackIndex;
	EBeforeAfterType eEBeforeType;
	int iShiftSecond;

	CustomizeJikokuhyouContent()
		: iRessyaIndexCont(vector<int>())
		, iSihatsuEkiOrder(INT_MIN)
		, iOuterShihatsuEkiIndex(-1)
		, OuterShihatsuJikoku(CdDedJikoku())
		, ChakuJikoku(CdDedJikoku())
		, iSyuuchakuEkiOrder(INT_MIN)
		, iOuterShuchakuEkiIndex(-1)
		, HatsuJikoku(CdDedJikoku())
		, OuterShuchakuJikoku(CdDedJikoku())
		, iReleaseEkiOrder(-1)
		, iConnectEkiOrder(-1)
		, iRessyasyubetsuIndex(-1)
		, strRessyabangou(tstring())
		, strRessyamei(tstring())
		, strGousuu(tstring())
		, strOperationNumber(vector<tstring>())
		, eEkiatsukai(CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya)
		, iRessyaTrackIndex(0)
		, eEAfterType(EBeforeAfterType::BeforeAfterType_Unrelated)
		, iPrevRessyasyubetsuIndex(-1)
		, strPrevRessyabangou(tstring())
		, strPrevRessyamei(tstring())
		, strPrevGousuu(tstring())
		, strPrevOperationNumber(vector<tstring>())
		, ePrevEkiatsukai(CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya)
		, iPrevRessyaTrackIndex(0)
		, eEBeforeType(EBeforeAfterType::BeforeAfterType_Unrelated)
		, iShiftSecond(0)
	{}

	CustomizeJikokuhyouContent(
		vector<int> iRessyaIndexCont)
		: iRessyaIndexCont(iRessyaIndexCont)
		, iSihatsuEkiOrder(INT_MIN)
		, iOuterShihatsuEkiIndex(-1)
		, OuterShihatsuJikoku(CdDedJikoku())
		, ChakuJikoku(CdDedJikoku())
		, iSyuuchakuEkiOrder(INT_MIN)
		, iOuterShuchakuEkiIndex(-1)
		, HatsuJikoku(CdDedJikoku())
		, OuterShuchakuJikoku(CdDedJikoku())
		, iReleaseEkiOrder(-1)
		, iConnectEkiOrder(-1)
		, iRessyasyubetsuIndex(-1)
		, strRessyabangou(tstring())
		, strRessyamei(tstring())
		, strGousuu(tstring())
		, strOperationNumber(vector<tstring>())
		, eEkiatsukai(CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya)
		, iRessyaTrackIndex(0)
		, eEAfterType(EBeforeAfterType::BeforeAfterType_Unrelated)
		, iPrevRessyasyubetsuIndex(-1)
		, strPrevRessyabangou(tstring())
		, strPrevRessyamei(tstring())
		, strPrevGousuu(tstring())
		, strPrevOperationNumber(vector<tstring>())
		, ePrevEkiatsukai(CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya)
		, iPrevRessyaTrackIndex(0)
		, eEBeforeType(EBeforeAfterType::BeforeAfterType_Unrelated)
		, iShiftSecond(0)
	{}

	CustomizeJikokuhyouContent(
		int iRessyaIndex)
		: iRessyaIndexCont({ iRessyaIndex })
		, iSihatsuEkiOrder(INT_MIN)
		, iOuterShihatsuEkiIndex(-1)
		, OuterShihatsuJikoku(CdDedJikoku())
		, ChakuJikoku(CdDedJikoku())
		, iSyuuchakuEkiOrder(INT_MIN)
		, iOuterShuchakuEkiIndex(-1)
		, HatsuJikoku(CdDedJikoku())
		, OuterShuchakuJikoku(CdDedJikoku())
		, iReleaseEkiOrder(-1)
		, iConnectEkiOrder(-1)
		, iRessyasyubetsuIndex(-1)
		, strRessyabangou(tstring())
		, strRessyamei(tstring())
		, strGousuu(tstring())
		, strOperationNumber(vector<tstring>())
		, eEkiatsukai(CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya)
		, iRessyaTrackIndex(0)
		, eEAfterType(EBeforeAfterType::BeforeAfterType_Unrelated)
		, iPrevRessyasyubetsuIndex(-1)
		, strPrevRessyabangou(tstring())
		, strPrevRessyamei(tstring())
		, strPrevGousuu(tstring())
		, strPrevOperationNumber(vector<tstring>())
		, ePrevEkiatsukai(CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya)
		, iPrevRessyaTrackIndex(0)
		, eEBeforeType(EBeforeAfterType::BeforeAfterType_Unrelated)
		, iShiftSecond(0)
	{}

	CustomizeJikokuhyouContent(
		const CentDedRessya* pCentDedRessya,
		const bool bIsPrev = false)
		: iRessyaIndexCont(vector<int>())
		, iSihatsuEkiOrder(INT_MIN)
		, iOuterShihatsuEkiIndex(-1)
		, OuterShihatsuJikoku(CdDedJikoku())
		, ChakuJikoku(CdDedJikoku())
		, iSyuuchakuEkiOrder(INT_MIN)
		, iOuterShuchakuEkiIndex(-1)
		, HatsuJikoku(CdDedJikoku())
		, OuterShuchakuJikoku(CdDedJikoku())
		, iReleaseEkiOrder(-1)
		, iConnectEkiOrder(-1)
		, strOperationNumber(vector<tstring>())
		, eEkiatsukai(CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya)
		, iRessyaTrackIndex(0)
		, eEAfterType(EBeforeAfterType::BeforeAfterType_Unrelated)
		, strPrevOperationNumber(vector<tstring>())
		, ePrevEkiatsukai(CentDedEkiJikoku::EEkiatsukai::Ekiatsukai_Teisya)
		, iPrevRessyaTrackIndex(0)
		, eEBeforeType(EBeforeAfterType::BeforeAfterType_Unrelated)
		, iShiftSecond(0)
		//, iRessyasyubetsuIndex(-1)
		//, strRessyabangou(tstring())
		//, strRessyamei(tstring())
		//, strGousuu(tstring())
	{
		if (bIsPrev)
		{
			iPrevRessyasyubetsuIndex = pCentDedRessya->getRessyasyubetsuIndex();
			strPrevRessyabangou = pCentDedRessya->getRessyabangou();
			strPrevRessyamei = pCentDedRessya->getRessyamei();
			strPrevGousuu = pCentDedRessya->getGousuu();
			iRessyasyubetsuIndex = -1;
			strRessyabangou = tstring();
			strRessyamei = tstring();
			strGousuu = tstring();

		}
		else
		{
			iRessyasyubetsuIndex = pCentDedRessya->getRessyasyubetsuIndex();
			strRessyabangou = pCentDedRessya->getRessyabangou();
			strRessyamei = pCentDedRessya->getRessyamei();
			strGousuu = pCentDedRessya->getGousuu();
			iPrevRessyasyubetsuIndex = -1;
			strPrevRessyabangou = tstring();
			strPrevRessyamei = tstring();
			strPrevGousuu = tstring();
		}
	}

	//todo ケースに応じたコンストラクタ作成
};

/**
	ダイヤ中にある入出区連携コードをまとめるために用います。
	一つの入出区連携コード(=任意の文字列)をキーとし、このInOutLinkCodeContentがペアになっており、
	運用接続及び入出区連携コード一覧に用います。

	contInRessyaProperty:当該コードを入区または路線外終着に持つ列車のCdDedRessyaPropertyを保持します
	contOutRessyaProperty:当該コードを出区または路線外始発に持つ列車のCdDedRessyaPropertyを保持します
	iStatus:キーとなる入出区連携コードに対し、どの種類の列車が存在するのかと有効性を示します。
		0:出区(路線外始発)列車のみが存在します。
			最終的にこの状況な場合、入出区連携は無効となります。(出区作業に設定されている運番を使用して運用接続を行う)
		1:入区(路線外終着)列車のみが存在します。
			最終的にこの状況な場合、入出区連携は無効となります。
		2:出区と入区がペアになっています。
			最終的にこの状況な場合、入出区連携は有効となります。
		3:出区もしくは入区の片方または両方の列車が、2本以上存在します。
			もしくは、出区と入区がペアになっているが、起点時刻を跨いでいます(起点時刻を跨いでの列車接続無効時)
			最終的にこの状況な場合、入出区連携は無効となります。
	BeforeOperation:運用接続時に用います。出区列車が一本のときに、ここに当該出区作業のポインタを格納しておき、
		contOutRessyaPropertyと組み合わせて、運用接続を進めます。
*/
struct InOutLinkCodeContent {
	vector<CdDedRessyaProperty> contInRessyaProperty;
	vector<CdDedRessyaProperty> contOutRessyaProperty;
	int iStatus;
	CentDedBeforeOperation* BeforeOperation;
	vector<tstring> strOperationNumber;

	InOutLinkCodeContent()
		: contInRessyaProperty(vector<CdDedRessyaProperty>())
		, contOutRessyaProperty(vector<CdDedRessyaProperty>())
		, iStatus(0)
		, BeforeOperation(NULL)
		, strOperationNumber(vector<tstring>())
	{}

	InOutLinkCodeContent(
		int iStatus)
		: contInRessyaProperty(vector<CdDedRessyaProperty>())
		, contOutRessyaProperty(vector<CdDedRessyaProperty>())
		, iStatus(iStatus)
		, BeforeOperation(NULL)
		, strOperationNumber(vector<tstring>())
	{}
	//OperationTableContent(
	//	CdDedRessyaProperty aRessyaProperty)
	//	: aRessyaProperty(aRessyaProperty)
	//	, iSihatsuEkiOrder(0)
	//	, eBeforeType(EBeforeAfterType::BeforeAfterType_Unrelated)
	//	, iOuterShihatsuekiIndex(INT_MIN)
	//	, OuterShihatsuJikoku(CdDedJikoku())
	//	, ChakuJikoku(CdDedJikoku())
	//	, iSyuuchakuEkiOrder(0)
	//	, eAfterType(EBeforeAfterType::BeforeAfterType_Unrelated)
	//	, iOuterShuchakuekiIndex(INT_MIN)
	//	, HatsuJikoku(CdDedJikoku())
	//	, OuterShuchakuJikoku(CdDedJikoku())
	//	, AfterOperation(NULL)
	//{}

};

class CentDedDia : public CChildBase
{
	typedef CChildBase	super ;
public:

	///**
	//	OperationTableContentのiBeforeTypeおよびiAfterTypeに用います。
	//*/
	//enum class EBeforeAfterType
	//{
	//	/**
	//		前列車接続及び次列車接続で、前後の列車と別列車である場合
	//	*/
	//	BeforeAfterType_Unrelated = 0,

	//	/**
	//		前列車接続及び次列車接続で、前後の列車と種別変更である場合
	//	*/
	//	BeforeAfterType_ClassChange,

	//	/**
	//		前列車接続及び次列車接続で、前後の列車と列車情報変更である場合
	//	*/
	//	BeforeAfterType_PropertyChange,

	//	/**
	//		前列車接続及び次列車接続で、前後の列車と同一列車扱いである場合
	//	*/
	//	BeforeAfterType_PropertySame,

	//	/**
	//		出入区の場合
	//	*/
	//	BeforeAfterType_OutIn,

	//	/**
	//		路線外始発・終着の場合
	//	*/
	//	BeforeAfterType_Outer,

	//	/**
	//		運用番号変更の場合
	//	*/
	//	BeforeAfterType_OperationNumberChange,

	//};
	// ****************************************************************
	//	インナータイプ
	// ****************************************************************
	/**
	　CentDedDia に包含されている『列車』コンテナです。
	*/
	class CXRessyaCont : public CentDedRessyaCont
	{
		typedef CentDedRessyaCont super ;
	 public:
		// ********************************
		///@name 関連
		// ********************************
		///@{
		/**
			親オブジェクトへのポインタです。コンストラクタで決まります。
		*/
		CentDedDia* m_pDia ;
	public:
		// ********************************
		//	コンストラクタ
		// ********************************
		CXRessyaCont( 
			CentDedDia* pCentDedDia , 
			ERessyahoukou m_eRessyahoukou ) 
			: 
			super( 0 ,
				m_eRessyahoukou ) ,
		  	m_pDia( pCentDedDia )
		{}
		CXRessyaCont( 
			CentDedDia* pCentDedDia , 
			int iEkiCount ,
			ERessyahoukou m_eRessyahoukou ) 
			: 
			super( iEkiCount ,
				m_eRessyahoukou ) ,
		  	m_pDia( pCentDedDia )
		{}


		CXRessyaCont( 
			CentDedDia* pCentDedDia , 
			const CentDedRessyaCont& value )
			: 
			super( value ) ,
		  	m_pDia( pCentDedDia )
		{}

	 public:
		// ********************************
		///@name CentDedRessyaCont-関連
		// ********************************
		///@{
		/**
		@return
			このコンテナが CentDedDia に包含されている場合は、
			CentDedDia のアドレス。
			そうでないならNULL。
		*/
		virtual CentDedDia* getDia(){ return m_pDia ;}
		/**
		@return
			このコンテナが CentDedRessya に包含されている場合は、
			CentDedRessya のアドレス。
			そうでないならNULL。
		*/
		virtual const CentDedDia* getDia()const{ return m_pDia ;}
	};
	/**
		代入演算子や、set...() でスローされる例外です。
	*/
	class LException
	{
	};


public:
	/**
	時刻表画面背景色の数。
	*/
	static const int JIKOKUHYOUCOLOR_COUNT = 4;

	// ****************************************************************
private:
	// ********************************
	///@name 属性
	// ********************************
	///@{
	/**
	  	ダイヤの名称です。
	  
	  	（例） "平日ダイヤ" など
	  
	   @see CentDedRosen
	  	 CentDedRosen は、この属性を限定子として扱います。
	  	CentDedRosen に包含される CentDedDia では、
	  	この属性は一意でなくてはなりません。
	 */
	tstring	m_strName ;

	/**
		時刻表画面における基本背景色のIndexです
		単色時、種別色時の空行、縦縞・横縞・市松模様時
		および、基準運転時分機能有効時に用います。
		範囲は0以上JIKOKUHYOUCOLOR_COUNT未満です。
	*/
	int m_iJikokuhyouMainBackColorIndex;

	/**
		時刻表画面における補助背景色のIndexです
		縦縞・横縞・市松模様時に用います。
		範囲は0以上JIKOKUHYOUCOLOR_COUNT未満です。
	*/
	int m_iJikokuhyouSubBackColorIndex;

	/**
		時刻表画面における背景色パターンのIndexです
		0:単色
		1:種別色
		2:縦縞
		3:横縞
		4:市松模様
	*/
	int m_iJikokuhyouBackPatternIndex;

	/**
	時刻表ビューの列車編集において、bWaitOperationUpdateがtrueの場合、
	(運用更新抑止がONの状態)この値をtrueにします。
	この値がtrueの場合、ダイヤグラムビューの全更新は抑止、
	ダイヤグラムビューを開く場合は、運用一時OFFの状態で開きます。
	デフォルト値はfalseです。
	*/
	bool m_bWaitOperationUpdate;

	/**
		パターンダイヤプレビュー機能が有効か否か
	
	*/
	bool m_bPatternDiagramPreviewEnable = false;

	/**
		パターンダイヤプレビュー機能における、1サイクルの秒数。
		最小は60、最大は10800(3時間)とします。
		デフォルト値は600(10分)とします。
	*/
	int m_iPatternDiagramPreviewCycleSecond = 600;

	/**
		パターンダイヤプレビュー機能における、前後各方向へのコピー範囲。
		6時間と、1サイクルの秒数×60のいずれか小さい方になります。
		setPatternDiagramPreviewCycleSecondを実行した際に自動的に求められます。
	*/
	int m_iPatternDiagramPreviewRange = 21600;

	/**
		カスタム表示モードにおける、列車の並び順
		カスタム表示モードでは、種別変更・増解結により、
		列車の並び替えおよび同じ列に複数の列車を表示する場合があります。
		その表示順を保存します。
	*/
	//vector<vector<int>> m_contCustomizeRessyaIndexKudari;
	//vector<vector<int>> m_contCustomizeRessyaIndexNobori;
	vector<CustomizeJikokuhyouContent> m_contCustomizeRessyaIndexKudari;
	vector<CustomizeJikokuhyouContent> m_contCustomizeRessyaIndexNobori;

	/**
		運用表要素コンテナ
		運用番号をキーとする配列で、各運用番号が割り当てられた列車情報を格納します。
	*/
	unordered_map<tstring, list<OperationTableContent>> m_contOperationTableContent;

	/**
		入出区連携コード要素コンテナ
		入出区連携コードをキーとする配列で、各入出区連携コードを持つ列車情報を格納します。
	*/
	map<tstring, InOutLinkCodeContent> m_contInOutLinkCodeContent;
	///@}
private:
	// ********************************
	///@name 包含
	// ********************************
	///@{
	/**
		この『ダイヤ』内で運行されている列車の
		『列車』 ( CentDedRessya ) を保持します。
	
		この変数は、要素数 2 の配列です。

		- [0] は	下り ( Ressyahoukou_Kudari ) 列車	
		- [1] は	上り ( Ressyahoukou_Nobori ) 列車	
	
		このコンテナ内の CentDedRessya オブジェクトの
		生成・破棄の責務はthisにあります。
	
		初期状態では、要素数は 0 となります。
	*/
	CXRessyaCont*	m_CentDedRessyaCont[2] ;
	
	///@}


public:
	// ********************************
	//	コンストラクタ
	// ********************************
	/**
	   @param strName [in]
	  	ダイヤの名称です。	\n
	  	（例） "平日ダイヤ" など
	*/
	CentDedDia( const tstring& strName = _T("") ) ;

	/**
	  	このコンストラクタは、 
	  	CentDedDia_From_CdConnectedString() で
	  	ファイルの内容を取得するときに、
	  	読み取り先として指定するオブジェクトの生成に使います。
	   @param iEkiCount [in]
	  	ダイヤに含まれる駅の数。
	 */
	CentDedDia( int iEkiCount ) ;

	/**
	   @param strName [in]
	  	ダイヤの名称です。	\n
	  	（例） "平日ダイヤ" など
	   @param iEkiCount [in]]
	  	ダイヤに含まれる駅の数。
	 */
	CentDedDia( 
		const tstring& strName  ,
		int iEkiCount ) ;

	/**
	@param strName [in]
	ダイヤの名称です。	\n
	（例） "平日ダイヤ" など
	@param iEkiCount [in]]
	ダイヤに含まれる駅の数。
	*/
	CentDedDia(
		const tstring& strName,
		const int& iJikokuhyouMainBackColorIndex,
		const int& iJikokuhyouSubBackColorIndex,
		const int& iJikokuhyouBackPatternIndex,
		const bool& bPatternDiagramPreviewEnable,
		const int& iPatternDiagramPreviewCycleSecond,
		int iEkiCount);


	CentDedDia( const CentDedDia& value );
	
	/**
	  	このクラスへの代入を行いますが、
	  	this の『駅』の数 ( m_iEkiCount ) は変更しません。
	  
		△上書き(operator=): このオブジェクトが親オブジェクト CentDedDiaCont 
		の子である場合で、代入元のダイヤ名が空文字列である場合、
		もしくは同じ名前のダイヤが CentDedDiaCont にある場合は例外スロー。
		　(代入元が、CentDedDiaCont::set()に渡すとエラーになるような
		　オブジェクトである場合は、代入は例外スローとします)

	 */
	CentDedDia& operator=( const CentDedDia& value );

	virtual ~CentDedDia();

public:
	// ********************************
	///@name CChildBase-操作
	// ********************************
	///@{
	/**
	　△setParent:adjustを実行する
	*/
	virtual void setParent( CParentBase* pParent );
	///@}
public:
	// ********************************
	///@name CentDedDia-属性
	// ********************************
	///@{
	tstring	getName()const{	return m_strName ;};

	int	getMainBackColorIndex()const { return m_iJikokuhyouMainBackColorIndex; };

	int	getSubBackColorIndex()const { return m_iJikokuhyouSubBackColorIndex; };;

	int	getBackPatternIndex()const { return m_iJikokuhyouBackPatternIndex; };
	
	/**
	△setName:このオブジェクトが親オブジェクト CentDedDiaCont の子である
	場合で、代入元のダイヤ名が空文字列である場合、もしくは同じ名前のダイヤが
	 CentDedDiaCont にある場合は例外スローとします。
	　(属性変更後のオブジェクトが、CentDedDiaCont::set()に渡すとエラーに
	　なるようなオブジェクトである場合は、エラーとします)
	*/
	void setName( const tstring& value );

	void setMainBackColorIndex(const int& value)
	{
		m_iJikokuhyouMainBackColorIndex = value;
	};

	void setSubBackColorIndex(const int& value)
	{
		m_iJikokuhyouSubBackColorIndex = value;
	};

	void setBackPatternIndex(const int& value)
	{
		m_iJikokuhyouBackPatternIndex = value;
	};

	bool getWaitOperationUpdate()const { return m_bWaitOperationUpdate; };
	void setWaitOperationUpdate(const bool& value)
	{
		m_bWaitOperationUpdate = value;
	};

	bool getPatternDiagramPreviewEnable()const { return m_bPatternDiagramPreviewEnable; };

	void setPatternDiagramPreviewEnable(const bool& value)
	{
		m_bPatternDiagramPreviewEnable = value;
	};

	int	getPatternDiagramPreviewCycleSecond()const { return m_iPatternDiagramPreviewCycleSecond; };

	void setPatternDiagramPreviewCycleSecond(const int& value);

	int	getPatternDiagramPreviewRange()const { return m_iPatternDiagramPreviewRange; };

	int getEkiCount()const
	{
		return m_CentDedRessyaCont[ Ressyahoukou_Kudari ]->
			getEkiCount() ;
	};

	vector<CustomizeJikokuhyouContent>& getcontCustomizeRessyaIndexKudari()
	{
		return m_contCustomizeRessyaIndexKudari;
	};
	vector<CustomizeJikokuhyouContent>& getcontCustomizeRessyaIndexNobori()
	{
		return m_contCustomizeRessyaIndexNobori;
	};
	vector<CustomizeJikokuhyouContent>& getcontCustomizeRessyaIndex(
		ERessyahoukou eRessyahoukou)
	{
		if (eRessyahoukou == ERessyahoukou::Ressyahoukou_Nobori)
		{
			return m_contCustomizeRessyaIndexNobori;
		}
		return m_contCustomizeRessyaIndexKudari;
	};
	const vector<CustomizeJikokuhyouContent>& getcontCustomizeRessyaIndex(
		ERessyahoukou eRessyahoukou)const
	{
		if (eRessyahoukou == ERessyahoukou::Ressyahoukou_Nobori)
		{
			return m_contCustomizeRessyaIndexNobori;
		}
		return m_contCustomizeRessyaIndexKudari;
	};

	const CustomizeJikokuhyouContent getcontCustomizeRessyaIndex(
		ERessyahoukou eRessyahoukou,
		int iIndex)const;

	unordered_map<tstring, list<OperationTableContent>>& getcontOperationTableContent()
	{
		return m_contOperationTableContent;
	};
	const unordered_map<tstring, list<OperationTableContent>>& getcontOperationTableContent()const
	{
		return m_contOperationTableContent;
	};

	map<tstring, InOutLinkCodeContent>& getcontInOutLinkCodeContent()
	{
		return m_contInOutLinkCodeContent;
	};
	const map<tstring, InOutLinkCodeContent>& getcontInOutLinkCodeContent()const
	{
		return m_contInOutLinkCodeContent;
	};
	///@}
	// ********************************
	///@name CentDedDia-包含
	// ********************************
	///@{
	/**
	   @param eRessyahoukou [in]
	  	列車方向を指定してください。
	  	-	下り :	Ressyahoukou_Kudari 
	  	-	上り : 	Ressyahoukou_Nobori 
	 */
	CentDedRessyaCont* getCentDedRessyaCont( 
			ERessyahoukou eRessyahoukou )
	{
		return m_CentDedRessyaCont[ eRessyahoukou ] ;
	};
	/**
	   @param eRessyahoukou [in]
	  	列車方向を指定してください。
	  	-	下り :	Ressyahoukou_Kudari 
	  	-	上り : 	Ressyahoukou_Nobori 
	 */
	const CentDedRessyaCont* getCentDedRessyaCont( 
			ERessyahoukou eRessyahoukou )const
	{
		return m_CentDedRessyaCont[ eRessyahoukou ] ;
	};
	///@}
	// ********************************
	///@name CentDedDia-操作
	// ********************************
	///@{

	/**
		指定の駅 Order の駅時刻を、
		駅時刻形式・始発・終着に合わせて変更します。

		変更内容は、 CentDedEkiJikoku::adjustByEkijikokukeisiki 
		の説明を参照してください。

	@see CentDedEkiJikoku::adjustByEkijikokukeisiki 

	@param pCentDedEkiCont [in]
		駅コンテナを指定してください。
	@param iEkiIndex [in]
		駅Indexを指定してください。
		INT_MAX は、末尾を指定したことになります。
	*/
	void adjustByEkijikokukeisiki(
		const CentDedEkiCont* pCentDedEkiCont ,
		int iEkiIndex );

	/**
		列車情報が変更になったときに、前後作業を修正します。
		実作業は、CentDedEkiJikokuへ委譲します。
		(1)有効な始発駅以前・有効な終着駅以降の作業をクリア
		(2)有効な始発駅の前作業先頭を、先端作業(前列車接続etc)にする、
			有効な終着駅の後作業末尾を、終端作業(次列車接続etc)にする
		(3)その他の先端作業、終端作業を削除
		(4)増解結作業の前後作業に、先端・終端作業があるかチェック
		駅設定を見て、作業の有効・無効を変更します
	*/
	void adjustOperation(
		const CentDedEkiCont* pCentDedEkiCont);
	///@}

	/**
		this の属性が制約に反している場合、制約に合うように、属性を
		修正します。

		○列車コンテナ(CentDedRessyaCont)にadjust()を委譲します。

	*/
	void adjust() ;

	/**
		m_contCustomizeRessyaIndexKudariとm_contCustomizeRessyaIndexNoboriを初期化します
		各配列のindex番目にindexが入ります。
	*/
	void clearCustomizeRessyaIndex();

	void omitInvalidRessyaFromCustomizeRessyaIndex(
		const vector<bool> contHidden);

	/**
		運用機能が無効な場合に、カスタマイズ時刻表のパターンダイヤプレビュー機能への対応をここで行います。
	*/
	void copyCustomizeRessyaIndexByPatternDiagramPreview();


	//m_contOperationTableContentをすべて消去します
	void clearOperationTableContent();

	//m_contInOutLinkCodeContentをすべて消去します
	void clearInOutLinkCodeContent();
public:
	// ********************************
	///@name CentDedDia-駅数・列車種別数の変更
	// ********************************
	///@{

	/**
	  	このコンテナに、指定された『列車種別』の列車があるか否かを調べます。
	   @param iRessyasyubetsuIndex [in]
	  	『列車種別Index』を指定してください。
	  	範囲は、 0 以上 列車種別の数未満です。
	  	INT_MAX は、末尾の列車種別を指定したものとみなします。
	   @param peRessyahoukou [out]
	  	この関数はこの変数に、『列車種別』の列車が見つかった
	  	ダイヤの列車方向を書き込みます。
	  	不要なら NULL でもかまいません。
	   @param piRessyaIndex [out]
	  	この関数はこの変数に、『列車種別』の列車が見つかった
	  	列車Index を書き込みます。
	  	不要なら NULL でもかまいません。
	   @return 
	  	-	1; //	指定の列車種別の列車が存在します。
	  	-	0; //	指定の列車種別の列車は存在しません。
	  	-	-1 ;	//	インデクスが不正
	 */
	int isExistRessyaOfRessyasyubetsu( 
		int iRessyasyubetsuIndex ,
		ERessyahoukou* peRessyahoukou ,
		int* piRessyaIndex ) const ;

	/**
	このコンテナに、指定された『駅の番線』を使用する列車があるか否かを調べます。
	@param iEkiIndex [in]
	『駅Index』を指定してください。
	範囲は、 0 以上 駅の数未満です。
	INT_MAX は、末尾の駅を指定したものとみなします。
	@param iEkiTrack2Index [in]
	『番線Index』を指定してください。
	範囲は、 0 以上 番線の数未満です。
	INT_MAX は、末尾の番線を指定したものとみなします。
	なお、列車における番線指定は1から始まるので、調整が必要となります
	@param peRessyahoukou [out]
	この関数はこの変数に、『列車種別』の列車が見つかった
	ダイヤの列車方向を書き込みます。
	不要なら NULL でもかまいません。
	@param piRessyaIndex [out]
	この関数はこの変数に、『列車種別』の列車が見つかった
	列車Index を書き込みます。
	不要なら NULL でもかまいません。
	@return
	-	1; //	指定の駅の番線を使用する列車が存在します。
	-	0; //	指定の駅の番線を使用する列車は存在しません。
	-	-1 ;	//	インデクスが不正
	*/
	int isExistRessyaOfEkiTrack2(
		int iEkiIndex,
		int iEkiTrack2Index,
		ERessyahoukou* peRessyahoukou,
		int* piRessyaIndex) const;

	/**
	このコンテナに、指定された『路線外発着駅』を使用する列車があるか否かを調べます。
	@param iEkiIndex [in]
	『駅Index』を指定してください。
	範囲は、 0 以上 駅の数未満です。
	INT_MAX は、末尾の駅を指定したものとみなします。
	@param iOuterTerminalIndex [in]
	『路線外発着駅Index』を指定してください。
	範囲は、 0 以上 路線外発着駅の数未満です。
	INT_MAX は、末尾の路線外発着駅を指定したものとみなします。
	@param peRessyahoukou [out]
	この関数はこの変数に、『路線外発着駅』を使用する列車が見つかった
	ダイヤの列車方向を書き込みます。
	不要なら NULL でもかまいません。
	@param piRessyaIndex [out]
	この関数はこの変数に、『路線外発着駅』を使用する列車が見つかった
	列車Index を書き込みます。
	不要なら NULL でもかまいません。
	@return
	-	1; //	指定の駅の番線を使用する列車が存在します。
	-	0; //	指定の駅の番線を使用する列車は存在しません。
	-	-1 ;	//	インデクスが不正
	*/
	int isExistRessyaOfOuterTerminal(
		int iEkiIndex,
		int iOuterTerminalIndex,
		ERessyahoukou* peRessyahoukou,
		int* piRessyaIndex) const;
	///@}
public:
	// ********************************
	///@name CentDedRosen-子オブジェクトの増減の通知
	// ********************************
	///@{
	/**
		m_CentDedEkiCont に CentDedEki が追加された直後、
		m_CentDedEkiCont から呼び出されます。
	@param iEkiIndex
		追加された CentDedEki のインデクス。
	*/
	virtual void onEkiInsert( int iEkiIndex, const vector<int>& iMainTrack);

	/**
		m_CentDedEkiCont から CentDedEki が削除された直後、
		m_CentDedEkiCont から呼び出されます。
	@param iEkiIndex
		削除された CentDedEki のインデクス。
	*/
	virtual void onEkiErase( int iEkiIndex  );
		
	/**
		CentDedRessyasyubetsuCont に CentDedRessyasyubetsu が追加された直後、
		CentDedRessyasyubetsuCont から呼び出されます。
	@param iRessyasyubetsuIndex
		追加された CentDedRessyasyubetsu  のインデクス。
	*/
	virtual void onRessyasyubetsuInsert( int iRessyasyubetsuIndex );

	/**
		CentDedRessyasyubetsuCont から CentDedRessyasyubetsu が削除された直後、
		CentDedRessyasyubetsuCont から呼び出されます。
	@param iRessyasyubetsuIndex
		削除された CentDedRessyasyubetsu  のインデクス。
	*/
	virtual void onRessyasyubetsuErase( int iRessyasyubetsuIndex );

	/**
	CentDedEkiが変更された結果、新たに分岐駅を設定した、
	もしくは基幹駅を変更した場合に、呼び出されます。
	必要に応じて、駅扱い・番線を変更します。
	@param iEkiIndex
	変更された駅Index
	@param iBrunchCoreEkiIndex
	編集対象駅の、iBrunchCoreEkiIndex(基幹駅Index)の値です。
	@param iEkiIndexBrunchThisSide
	基幹駅の駅Index及び、変更された駅と、基幹駅から見て
	同じ側にある派生駅の駅Indexの集合です。
	@param iEkiIndexLoop
	基幹駅が環状線の起点・終点になっている場合、対応する終点・起点の駅Indexが入ります。
	環状線が複数連なっている場合、その数だけ、駅Indexが格納されます
	@param iEkiIndexBrunchOtherSide
	基幹駅から見て、変更された駅と反対側にある派生駅の駅Indexの集合です。
	ただし、間に環状線が挟まる場合は、その先端を基幹駅とする、派生駅の集合になります
	@param iOuterTerminalEkimeiMap
	派生駅と基幹駅で路線外発着駅名を融合したことにより、
	派生駅にもともと存在していた路線外発着駅が、新しい並びのどこに位置するかを示したマップです。
	このマップに基づき、派生駅を起終点とし路線外発着に指定された列車の補正を行います。
	*/
	virtual void adjustBrunchLoopByBrunchEdit(
		int iEkiIndex, bool bOriginSide, 
		deque<int> &iEkiIndexBrunchOriginSide,
		deque<int> &iEkiIndexLoop, 
		deque<int> &iEkiIndexBrunchTerminalSide,
		vector<int> &iOuterTerminalEkimeiMap);

	/**
	CentDedEkiが変更された結果、新たに環状線を設定した、
	もしくは起点駅を変更した場合に、呼び出されます。
	必要に応じて、駅扱い・番線を変更します。
	@param iEkiIndex
	変更された駅Index
	@param iLoopOriginEkiIndex
	編集対象駅の、iLoopOriginEkiIndex(起点駅Index)の値です。
	@param iEkiIndexLoop
	変更された駅及び起点駅を含む、環状線設定により繋がっている駅の駅Indexが入ります。
	駅Indexは起点方(若い数字)が前になるように、入れられます。
	@param iEkiIndexBrunchUpSide
	上記環状線駅のうち最も起点方の駅を基幹駅とする、派生駅の駅Indexが入ります。
	分岐駅・環状線の設定規則より、派生駅Indexは必ず基幹駅よりも起点方になります。
	@param iEkiIndexBrunchDownSide
	上記環状線駅のうち最も終点方の駅を基幹駅とする、派生駅の駅Indexが入ります。
	分岐駅・環状線の設定規則より、派生駅Indexは必ず基幹駅よりも終点方になります。
	@param iOuterTerminalEkimeiMap
	起点駅側と終点駅側で路線外発着駅名を融合したことにより、
	起点駅側にもともと存在していた路線外発着駅が、新しい並びのどこに位置するかを示したマップです。
	このマップに基づき、起点駅側を起終点とし路線外発着に指定された列車の補正を行います。
	*/
	virtual void adjustBrunchLoopByLoopEdit(
		int iEkiIndex, int iPosition,
		deque<int> &iEkiIndexBrunchOriginSide, 
		deque<int> &iEkiIndexLoop,
		deque<int> &iEkiIndexBrunchTerminalSide,
		vector<int> &iOuterTerminalEkimeiMap);

	/**
		CentDedEkiが変更された結果、番線の順序が変わった場合に呼び出されます。
		変更対象の駅及び、分岐駅・環状線設定で結ばれた駅の列車番線を調整します
		@param iEkiIndexBrunchLoop
		調整の対象となる駅群の駅Indexです。
		@param iEkiTrack2Map
		駅番線の移動先です。
		idx番線の移動先はiEkiTrack2Map[idx]番線となります。
		調整する列車番線はidxが1始まりなので注意が必要です
	*/
	virtual void adjustBrunchLoopEkiTrack2(
		const deque<int> &iEkiIndexBrunchLoop,
		const std::vector<int>& iEkiTrack2Map);


	/**
	CentDedEkiが変更された結果、路線外発着駅が変更された場合に呼び出されます。
	変更対象の駅及び、分岐駅・環状線設定で結ばれた駅の始発終着駅作業を調整します
		@param iEkiIndexBrunchLoop
		調整の対象となる駅群の駅Indexです。
	@param iOuterTerminalEkimeiMap
	路線外発着駅の移動先です。
	idx駅の移動先はiOuterTerminalEkimeiMap[idx]番目となります。
	*/
	virtual void adjustBrunchLoopOuterTerminal(
		const deque<int> &iEkiIndexBrunchLoop,
		const std::vector<int>& iOuterTerminalEkimeiMap);

	/**
		Ver2.0以前のファイルを読み込むとき、分岐・環状線設定で繋がった駅間で、
		路線外発着駅名がそれぞれ独立していたものを、統一して共有するために用います。
	*/
	virtual void mergeOuterTerminal(
		const deque<int> &iEkiIndexBrunchOriginSide,
		const deque<int> &iEkiIndexLoop,
		const deque<int> &iEkiIndexBrunchTerminalSide,
		const vector<vector<int>> &iOuterTerminalMapCont);
	///@}
};

} //namespace entDed

#endif /*CentDedDia_h*/


