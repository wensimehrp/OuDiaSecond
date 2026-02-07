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
// ****************************************************************
//	$Id: CPropEditUi_Eki.h 357 2016-08-18 16:59:16Z okm $
// ****************************************************************

/** @file */
#ifndef  CPropEditUi_Eki_h
#define  CPropEditUi_Eki_h
#include <string>
#include "NsPropEditUi2¥CPropEditUi2.h"
#include "..¥entDed¥CentDedEkiCont.h"
#include <vector>
#include <tchar.h>

namespace ViewEki {

	using namespace std ;
	using namespace entDed ;
	using namespace OuLib::NsPropEditUi2 ;

/**
@brief
	CPropEditUi_Eki で編集する UIDATA 構造体です
*/
struct EkiTrack2
{
	tstring strTrackName;
	tstring strTrackRyakusyou;
	tstring strTrackNoboriRyakusyou;

	/**
		主本線設定
		0:副本線/側線
		1:下り主本線
		2:上り主本線
		3:上下主本線
	*/
	int iMainTrack;

	EkiTrack2()
		:strTrackName(_T(""))
		, strTrackRyakusyou(_T(""))
		, strTrackNoboriRyakusyou(_T(""))
		,iMainTrack(0)
	{}
};

struct OuterTerminalEkimei
{
	tstring strOuterTerminalEkimei;
	tstring strOuterTerminalJikokuRyaku;
	tstring strOuterTerminalDiaRyaku;


	OuterTerminalEkimei()
		:strOuterTerminalEkimei(_T(""))
		, strOuterTerminalJikokuRyaku(_T(""))
		, strOuterTerminalDiaRyaku(_T(""))
	{}

	OuterTerminalEkimei(
		tstring strA,
		tstring strB,
		tstring strC)
		:strOuterTerminalEkimei(strA)
		, strOuterTerminalJikokuRyaku(strB)
		, strOuterTerminalDiaRyaku(strC)
	{}
};

struct UIData_Eki
{
	/** 駅名 */
	tstring strEkimei ;
	
	/** 駅時刻形式 
	-	0以上: CentDedEki::EEkijikokukeisiki 
	-	-1 : 不定
	*/
	int iEkijikokukeisiki ;
	
	/** 駅規模 
	-	0以上: CentDedEki::EEkikibo
	-	-1 : 不定
	*/
	int iEkikibo ;

	/** 境界線あり 
	-	1: 境界線あり
	-	0: 境界線なし
	-	-1: 不定
	*/
	//int  iKyoukaisen ;

	/** ダイヤグラム列車情報表示（下り） 
	- 0以上: CentDedEki::EDiagramRessyajouhouHyouji 
	-	-1: 不定
	*/
	int iDiagramRessyajouhouHyoujiKudari ;

	/** ダイヤグラム列車情報表示（上り） 
	- 0以上: CentDedEki::EDiagramRessyajouhouHyouji 
	-	-1: 不定
	*/
	int iDiagramRessyajouhouHyoujiNobori ;

	/**
		[駅時刻を駅時刻形式で正規化]の設定です。
	*/
	bool bAdjustByEkijikokukeisiki ;
	
	/**分岐駅設定
	複数選択不可
	false:無効
	true:有効
	*/
	bool bBrunch;

	/**分岐駅設定自体の有効無効
	false:無効、複数選択時、自身が対象になっているとき
	true:有効
	*/
	bool bBrunchFunctionEnable;

	/**分岐駅設定基幹駅Index
	複数選択不可
	分岐駅設定がTrueの時のみ有効及びダイアログが機能
	0以上:EkiIndex
	-1:無効
	*/
	int iBrunchCoreEkiIndex;

	/**
		分岐の反対側接続設定
	*/
	bool bBrunchOpposite;

	/**環状線設定
	複数選択不可
	false:無効
	true:有効
	*/
	bool bLoop;

	/**環状線設定自体の有効無効
	false:無効、複数選択時、自身が対象になっているとき
	true:有効
	*/
	bool bLoopFunctionEnable;

	/*環状線設定起点駅Index
	複数選択不可
	環状線設定がTrueの時のみ有効及びダイアログが機能
	0以上:EkiIndex
	-1:無効
	*/
	int iLoopOriginEkiIndex;
	/**
	分岐の反対側接続設定
	*/
	bool bLoopOpposite;

	/**下り時刻表ビュー番線表示
	発時刻表示・上り発着"以外"の時有効
	複数選択時、上記条件を満たしているときのみ有効
	0:表示なし
	1:表示有
	*/
	int iJikokuhyouTrackDisplayKudari;

	/**上り時刻表ビュー番線表示
	発時刻表示・下り発着"以外"の時有効
	複数選択時、上記条件を満たしているときのみ有効
	0:表示なし
	1:表示有
	*/
	int iJikokuhyouTrackDisplayNobori;

	/**時刻表ビュー番線表示の有効無効

	発時刻表示"以外"の時有効
	複数選択時、上記条件を満たしているときのみ有効
	true:有効、単数選択
	*/
	bool bJikokuhyouTrackDisplayKudariEnable;

	/**時刻表ビュー番線表示の有効無効

	発時刻表示"以外"の時有効
	複数選択時、上記条件を満たしているときのみ有効
	true:有効、単数選択
	*/
	bool bJikokuhyouTrackDisplayNoboriEnable;

	/**ダイヤグラムビュー番線表示
	主要駅は必須、発着駅・下り着時刻・上り着時刻時有効
	番線設定統合有効時は無効
	複数選択時は無効
	0:表示なし
	1:表示有
	*/
	int iDiagramTrackDisplay;
	/**ダイヤグラムビュー番線表示の有効無効
	主要駅は必須、発着駅・下り着時刻・上り着時刻時有効
	番線設定統合有効時は無効
	複数選択時は無効
	true:有効、単数選択
	*/
	bool bDiagramTrackDisplayEnable;

	vector<bool> bDiagramTrackOmit;

	/*
		駅時刻形式・駅規模のロック
		target駅の中に、ほかの駅から共有の対象となった
		駅があった場合、この値をfalseとします、
		その場合、駅時刻形式と駅規模を変更できないようにします
		*/
	bool bEkijikokukeisikiAndEkikiboEnable;

	vector<EkiTrack2> sEkiTrack2;

	vector<OuterTerminalEkimei> sOuterTerminalEkimei;

	/**
		この駅から次の駅までの距離(秒)
		デフォルト値は0で、0の場合は、「ダイヤグラムの既定の駅間幅」
		を用います。
		値の範囲は0以上です。
	*/
	int iNextEkiDistance;

	/**
		番線編集モードにおける、番線表示省略設定です。
		この値がTrueの場合、番線表示モードでも番線欄が表示されません
		ただし、駅時刻形式が発時刻・下り発着の上り・上り発着の下りの場合に限られます。
	*/
	int iJikokuhyouTrackOmit;

	/**番線表示省略設定の有効無効

	発時刻表示、下り発着、上り発着の時有効
	複数選択時、上記条件を満たしているときのみ有効
	true:有効、単数選択
	*/
	bool bJikokuhyouTrackOmitEnable;

	/**
		駅作業欄表示設定
	*/
	int iJikokuhyouOperationOrigin;
	int iJikokuhyouOperationTerminal;
	bool bJikokuhyouOperationOriginDownBeforeUpAfter;
	bool bJikokuhyouOperationOriginDownAfterUpBefore;
	bool bJikokuhyouOperationTerminalDownBeforeUpAfter;
	bool bJikokuhyouOperationTerminalDownAfterUpBefore;
	bool bJikokuhyouOperationEnable;

	/** 駅名略称 */
	tstring strEkimeiJikokuhyouRyaku;

	/** 駅名略称(運用一覧) */
	tstring strEkimeiDiagramRyaku;

	/**
		カスタム表示モードにおける下り時刻表ビューでの着時刻表示設定
		駅時刻形式が発着・下り着・下り発着の時のみ有効となります

		true:この駅で着時刻を表示します
		false:この駅では着時刻を表示しません。
	*/
	bool bJikokuhyouChakuJikokuDisplayKudari;
	bool bJikokuhyouChakuJikokuDisplayKudariEnable;

	/**
		カスタム表示モードにおける上り時刻表ビューでの着時刻表示設定
		駅時刻形式が発着・上り着・上り発着の時のみ有効となります

		true:この駅で着時刻を表示します
		false:この駅では着時刻を表示しません。
	*/
	bool bJikokuhyouChakuJikokuDisplayNobori;
	bool bJikokuhyouChakuJikokuDisplayNoboriEnable;

	/**
		カスタム表示モードにおける下り時刻表ビューでの発時刻表示設定
		駅時刻形式が下り着以外の時のみ有効となります

		true:この駅で発時刻を表示します
		false:この駅では発時刻を表示しません。
	*/
	bool bJikokuhyouHatsuJikokuDisplayKudari;
	bool bJikokuhyouHatsuJikokuDisplayKudariEnable;

	/**
		カスタム表示モードにおける上り時刻表ビューでの発時刻表示設定
		駅時刻形式が上り着以外の時のみ有効となります

		true:この駅で発時刻を表示します
		false:この駅では発時刻を表示しません。
	*/
	bool bJikokuhyouHatsuJikokuDisplayNobori;
	bool bJikokuhyouHatsuJikokuDisplayNoboriEnable;

	/**
		カスタム表示モードにおける下り時刻表ビューでの列車番号表示設定
		駅時刻形式が発着・上り着・下り発着の時のみ有効となります

		2:この駅で全列車の列車番号を表示します
		1:この駅で種別変更を行った列車のみ列車番号を表示します
		0:この駅では列車番号を表示しません。
	*/
	int iJikokuhyouRessyabangouDisplayKudari;
	bool bJikokuhyouSyubetsuChangeDisplayKudariEnable;

	/**
		カスタム表示モードにおける上り時刻表ビューでの列車番号表示設定
		駅時刻形式が発着・下り着・上り発着の時のみ有効となります

		2:この駅で全列車の列車番号を表示します
		1:この駅で種別変更を行った列車のみ列車番号を表示します
		0:この駅では列車番号を表示しません。
	*/
	int iJikokuhyouRessyabangouDisplayNobori;
	bool bJikokuhyouSyubetsuChangeDisplayNoboriEnable;

	/**
		カスタム表示モードにおける下り時刻表ビューでの運用番号表示設定
		駅時刻形式が発着・上り着・下り発着の時のみ有効となります

		2:この駅で全列車の運用番号を表示します
		1:この駅で種別変更を行った列車のみ運用番号を表示します
		0:この駅では運用番号を表示しません。
	*/
	int iJikokuhyouOperationNumberDisplayKudari;

	/**
		カスタム表示モードにおける上り時刻表ビューでの運用番号表示設定
		駅時刻形式が発着・下り着・上り発着の時のみ有効となります

		2:この駅で全列車の運用番号を表示します
		1:この駅で種別変更を行った列車のみ運用番号を表示します
		0:この駅では運用番号を表示しません。
	*/
	int iJikokuhyouOperationNumberDisplayNobori;

	/**
		下りカスタマイズ時刻表ビューでの運用番号表示段数設定(ver2.05から)
		コンボボックスに合わせるため。値の範囲は0-4です(規定値は0)
	*/
	int iJikokuhyouOperationNumberDisplayRowsKudari;

	/**
		上りカスタマイズ時刻表ビューでの運用番号表示段数設定(ver2.05から)
		コンボボックスに合わせるため。値の範囲は0-4です(規定値は0)
	*/
	int iJikokuhyouOperationNumberDisplayRowsNobori;

	/**
		カスタム表示モードにおける下り時刻表ビューでの列車種別表示設定
		駅時刻形式が発着・上り着・下り発着の時のみ有効となります

		2:この駅で全列車の列車種別を表示します
		1:この駅で種別変更を行った列車のみ列車種別を表示します
		0:この駅では列車種別を表示しません。
	*/
	int iJikokuhyouRessyaSyubetsuDisplayKudari;

	/**
		カスタム表示モードにおける上り時刻表ビューでの列車種別表示設定
		駅時刻形式が発着・下り着・上り発着の時のみ有効となります

		2:この駅で全列車の列車種別を表示します
		1:この駅で種別変更を行った列車のみ列車種別を表示します
		0:この駅では列車種別を表示しません。
	*/
	int iJikokuhyouRessyaSyubetsuDisplayNobori;

	/**
		カスタム表示モードにおける下り時刻表ビューでの列車名・号数表示設定
		駅時刻形式が発着・上り着・下り発着の時のみ有効となります

		2:この駅で全列車の列車名・号数を表示します
		1:この駅で種別変更を行った列車のみ列車名・号数を表示します
		0:この駅では列車名・号数を表示しません。
	*/
	int iJikokuhyouRessyameiDisplayKudari;

	/**
		カスタム表示モードにおける上り時刻表ビューでの列車名・号数表示設定
		駅時刻形式が発着・下り着・上り発着の時のみ有効となります

		2:この駅で全列車の列車名・号数を表示します
		1:この駅で種別変更を行った列車のみ列車名・号数を表示します
		0:この駅では列車名・号数を表示しません。
	*/
	int iJikokuhyouRessyameiDisplayNobori;

	/**
		下りカスタマイズ時刻表ビューでの路線外・前列車始発駅表示設定
		駅時刻形式が発着・上り着・下り発着の時のみ有効となります

		true:この駅で路線外・前列車始発駅を表示します
		false:この駅では路線外・前列車始発駅を表示しません。
	*/
	bool bJikokuhyouOuterSihatsuDisplayKudari;
	bool bJikokuhyouOuterSihatsuDisplayKudariEnable;

	/**
		下りカスタマイズ時刻表ビューでの路線外・次列車終着駅表示設定
		駅時刻形式が発着・下り着・下り発着の時のみ有効となります

		true:この駅で路線外・次列車終着駅を表示します
		false:この駅では路線外・次列車終着駅を表示しません。
	*/
	bool bJikokuhyouOuterShuchakuDisplayKudari;
	bool bJikokuhyouOuterShuchakuDisplayKudariEnable;

	/**
		上りカスタマイズ時刻表ビューでの路線外・前列車始発駅表示設定
		駅時刻形式が発着・下り着・上り発着の時のみ有効となります

		true:この駅で路線外・前列車始発駅を表示します
		false:この駅では路線外・前列車始発駅を表示しません。
	*/
	bool bJikokuhyouOuterSihatsuDisplayNobori;
	bool bJikokuhyouOuterSihatsuDisplayNoboriEnable;

	/**
		上りカスタマイズ時刻表ビューでの路線外・次列車終着駅表示設定
		駅時刻形式が発着・上り着・上り発着の時のみ有効となります

		true:この駅で路線外・次列車終着駅を表示します
		false:この駅では路線外・次列車終着駅を表示しません。
	*/
	bool bJikokuhyouOuterShuchakuDisplayNobori;
	bool bJikokuhyouOuterShuchakuDisplayNoboriEnable;

	/**
		ダイヤグラムビューにおける、この駅と自駅の間の背景色です

		0:基本色を使用
		1-4:個別色1-4を使用
	*/
	int iDiagramColorNextEki;

	/** 
		箱ダイヤで表示するか否か 
		true:箱ダイヤで当駅を常時表示します
		false:箱ダイヤで表示しません
	*/
	int bOperationTableDisplayJikoku;

	/**
		箱ダイヤで表示するか否か の設定が有効か否か
	*/
	bool bOperationTableDisplayJikokuEnable;
	
	UIData_Eki()
		: iEkijikokukeisiki( (int)CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsu )
		, iEkikibo( (int)CentDedEki::EEkikibo::Ekikibo_Ippan ) 
		//, iKyoukaisen( 0 ) // 境界線なし
		, iDiagramRessyajouhouHyoujiKudari( (int)CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Origin )
		, iDiagramRessyajouhouHyoujiNobori( (int)CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Origin )
		, bAdjustByEkijikokukeisiki( true )
		//, iDownMain(1)
		//, iUpMain(2)
		, bBrunch(false)
		, bBrunchFunctionEnable(true)
		, iBrunchCoreEkiIndex(-1)
		, bBrunchOpposite(false)
		, bLoop(false)
		, bLoopFunctionEnable(true)
		, iLoopOriginEkiIndex(-1)
		, bLoopOpposite(false)
		, iJikokuhyouTrackDisplayKudari(0)
		, iJikokuhyouTrackDisplayNobori(0)
		, bJikokuhyouTrackDisplayKudariEnable(true)
		, bJikokuhyouTrackDisplayNoboriEnable(true)
		, iDiagramTrackDisplay(0)
		, bDiagramTrackDisplayEnable(true)
		, bEkijikokukeisikiAndEkikiboEnable(true)
		, iNextEkiDistance(0)
		, iJikokuhyouTrackOmit(1)
		, bJikokuhyouTrackOmitEnable(true)
		, iJikokuhyouOperationOrigin(0)
		, iJikokuhyouOperationTerminal(0)
		, bJikokuhyouOperationEnable(true)
		, bJikokuhyouOperationOriginDownBeforeUpAfter(false)
		, bJikokuhyouOperationOriginDownAfterUpBefore(false)
		, bJikokuhyouOperationTerminalDownBeforeUpAfter(false)
		, bJikokuhyouOperationTerminalDownAfterUpBefore(false)
		, strEkimeiJikokuhyouRyaku(_T(""))
		, strEkimeiDiagramRyaku(_T(""))
		, bJikokuhyouChakuJikokuDisplayKudari(false)
		, bJikokuhyouChakuJikokuDisplayKudariEnable(false)
		, bJikokuhyouChakuJikokuDisplayNobori(false)
		, bJikokuhyouChakuJikokuDisplayNoboriEnable(false)
		, bJikokuhyouHatsuJikokuDisplayKudari(true)
		, bJikokuhyouHatsuJikokuDisplayKudariEnable(true)
		, bJikokuhyouHatsuJikokuDisplayNobori(true)
		, bJikokuhyouHatsuJikokuDisplayNoboriEnable(true)
		, iJikokuhyouRessyabangouDisplayKudari(0)
		, bJikokuhyouSyubetsuChangeDisplayKudariEnable(true)
		, iJikokuhyouRessyabangouDisplayNobori(0)
		, bJikokuhyouSyubetsuChangeDisplayNoboriEnable(true)
		, iJikokuhyouOperationNumberDisplayKudari(0)
		, iJikokuhyouOperationNumberDisplayNobori(0)
		, iJikokuhyouOperationNumberDisplayRowsKudari(0)
		, iJikokuhyouOperationNumberDisplayRowsNobori(0)
		, iJikokuhyouRessyaSyubetsuDisplayKudari(0)
		, iJikokuhyouRessyaSyubetsuDisplayNobori(0)
		, iJikokuhyouRessyameiDisplayKudari(0)
		, iJikokuhyouRessyameiDisplayNobori(0)
		, iDiagramColorNextEki(0)
		, bOperationTableDisplayJikoku(false)
		, bOperationTableDisplayJikokuEnable(true)
		, bJikokuhyouOuterSihatsuDisplayKudari(false)
		, bJikokuhyouOuterSihatsuDisplayKudariEnable(false)
		, bJikokuhyouOuterShuchakuDisplayNobori(false)
		, bJikokuhyouOuterShuchakuDisplayNoboriEnable(false)
		, bJikokuhyouOuterSihatsuDisplayNobori(false)
		, bJikokuhyouOuterSihatsuDisplayNoboriEnable(false)
		, bJikokuhyouOuterShuchakuDisplayKudari(false)
		, bJikokuhyouOuterShuchakuDisplayKudariEnable(false)
	{
		sEkiTrack2.clear();
		sOuterTerminalEkimei.clear();
		bDiagramTrackOmit.clear();
	}
};



/**
@brief
  駅プロパティの編集を行うクラスです。
  
  このクラスは抽象クラスです。
  このクラスは、使用するUI環境(例：Windows,MFC)には依存しません。
　クラスユーザーは、このクラスを継承して、
 『オーバーライトの必要なメソッド2-UIに依存する処理』の仮想関数に、
 UI環境に依存した処理を実装してください。


*/
class CPropEditUi_Eki : public CPropEditUi2< UIData_Eki >
{
public:
	// ********************************
	///@name エラーメッセージ
	// ********************************
	///@{
	/// 駅名が長すぎます
	static const TCHAR* const ERRMSG_EKIMEI_TOO_LONG ;
	/// 分岐駅設定ONの時は、基幹駅を選択してください
	static const TCHAR* const ERRMSG_BRUNCH_EKIINDEX;
	/// 分岐駅設定ONの時は、駅規模を主要駅にしてください
	static const TCHAR* const ERRMSG_BRUNCH_EKIKIBO;
	/// 分岐駅設定ONかつ基幹駅が終点方の場合は、駅時刻形式を下り着時刻にしてください
	static const TCHAR* const ERRMSG_BRUNCH_EKIJIKOKUKEISIKI_DOWNCHAKU;
	/// 分岐駅設定ONかつ基幹駅が起点方の場合は、駅時刻形式を上り着時刻にしてください
	static const TCHAR* const ERRMSG_BRUNCH_EKIJIKOKUKEISIKI_UPCHAKU;
	/// 環状線設定ONの時は、起点駅を選択してください
	static const TCHAR* const ERRMSG_LOOP_EKIINDEX;
	/// 環状線設定ONの時は、駅規模を主要駅にしてください
	static const TCHAR* const ERRMSG_LOOP_EKIKIBO;
	/// 環状線設定ONの時は、駅時刻形式を発着または下り着時刻にしてください
	static const TCHAR* const ERRMSG_LOOP_EKIJIKOKUKEISIKI_HATSUCHAKU_DOWNCHAKU;
	/// 駅名が長すぎます
	static const TCHAR* const ERRMSG_EKIMEI_EMPTY;
	/// 駅名略称が長すぎます
	static const TCHAR* const ERRMSG_EKIMEIJIKOKUHYOURYAKU_TOO_LONG;
	/// 駅名略称(運用一覧)が長すぎます
	static const TCHAR* const ERRMSG_EKIMEIDIAGRAMRYAKU_TOO_LONG;
	///@}
	

private:
	// ********************************
	///@name 関連
	// ********************************
	///@{
	/**
	　Target(編集対象のプロパティを保持する変数へのポインタ)。 
	　コンストラクタで決まります。
	*/
	Mu<CentDedEki*>* m_pTarget ;

	/**
		Target(編集対象のプロパティを保持する変数へのポインタ)。
		[駅時刻を駅時刻形式で正規化]の設定です。
		コンストラクタで決まります。
	*/
	bool* m_pbAdjustByEkijikokukeisiki ;
	/**
	駅時刻形式・駅規模のロック
	target駅の中に、ほかの駅から共有の対象となった
	駅があった場合、この値をfalseとします、
	その場合、駅時刻形式と駅規模を変更できないようにします
	*/
	bool m_bEkijikokukeisikiAndEkikiboEnable;

	/**
	複数選択、選択駅が始点駅・終点駅の場合、falseになります
	この値がfalseの場合、
	分岐駅設定を無効にします。
	*/
	int m_bBrunchFunctionEnable;

	/**
	番線共有の対象になっている駅がtargetに含まれている時、
	この値がfalseの場合、
	環状線設定を無効にします。
	*/
	int m_bLoopFunctionEnable;

	///@}

private:
	// ********************************
	///@name 属性
	// ********************************
	///@{
	/**
	主本線設定のダイアログの設定に使用します
	0以上　駅Index、このIndexの番線コンテナを参照します
	-1　NewItem、1番線と2番線をデフォルト指定します
	-2　複数選択、ダイアログを無効or非表示にします
	*/
	int m_iEkiIndex;
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
	virtual void InitUiData( UIDATA* pUiData ) ;

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
		UiData の内容を検証し、問題があればエラーメッセージを表示します。
		
		CPropEditUi2::EndEdit()
		から呼び出されます。
		
		クラスユーザーは、この関数をオーバーライドして、
		UiDataのメンバの内容を検証する処理を実装してください。
		入力内容に問題があれば、ShowError()でエラーメッセージを表示し、
		SetFocus()で、フォーカスを問題のあるUIに設定してください。
		
		新規オブジェクトに対するプロパティの編集の場合は、
		UiDataのすべてのメンバーを検証する必要があります。
		また、必須のメンバーがブランクである場合は、
		エラーメッセージを表示するべきです。

		既存オブジェクトに対するプロパティ編集の場合は、
		ユーザーによって値の変更されたメンバーのみを検証してください。
		pUiData と pUiDataStartEdit との間で違いのあるデータメンバーが、
		ユーザーによって値の変更されたメンバーです。
		
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
				SetFocus( offsetof( UIDATA , メンバー名 ) );
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
		SetFocus( offsetof(UIDATA,strNumber ) ) ;
	@endcode
	*/
	virtual void SetFocus( int iOffsetofUiDataMember ) =0 ;
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
	　Target(編集対象のプロパティを保持する変数へのポインタ)。 
	　コンストラクタで決まります。
	@param pbAdjustBuEkijikokukeisiki [in,out]
		編集対象。コンストラクタで決まります。
		[駅時刻を駅時刻形式で正規化]です。
	@param iEkiIndex [in]
		編集対象の駅の駅Indexです。
	*/
	CPropEditUi_Eki( 
		bool bNewItem , 
		Mu<CentDedEki*>* pTarget ,
		bool* pbAdjustBuEkijikokukeisiki,
		int iEkiIndex,
		bool bEkijikokukeisikiAndEkikiboEnable,
		bool bBrunchFunctionEnable,
		bool bLoopFunctionEnable);
};

} //namespace ViewEki 



#endif /*CPropEditUi_Eki_h*/
