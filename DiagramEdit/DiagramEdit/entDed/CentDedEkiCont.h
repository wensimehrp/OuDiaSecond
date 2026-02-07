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
//	CentDedEkiCont.h
//	$Id: CentDedEkiCont.h 378 2016-11-16 21:10:54Z okm $
// ****************************************************************
*/
/** @file */
#ifndef  CentDedEkiCont_h
#define  CentDedEkiCont_h

#include "NsMu/CMuiCopiedParent.h"

#include "CentDed.h"
#include "CentDedEki.h"
#include "CdDedjikokuOrder.h"

namespace entDed{
	using namespace OuLib::NsMu;
	using namespace entDed ;
	
//	前方参照
class CentDedRosen ;
	
// ****************************************************************
//	CentDedEkiCont
// ****************************************************************
/**
@brief
  『駅』(CentDedEki) オブジェクトのコンテナです。

  このクラス自体は、 Mui< CentDedEki > インターフェースを
サポートします。このインターフェースにより、 CentDedEki オブジェクトを
追加・変更・削除することができます。

  引数なしの getMuPtr() メソッドにより、 Mu< const CentDedEki* >
インターフェースを取得することができます。
 このインターフェースを使うと、コンテナ内の CentDedEki 
オブジェクトに直接アクセスすることができますが、
CentDedEki オブジェクトの属性を変更することはできません。
属性の変更は、 set() メソッドを使わなくてはなりません。

  また、列車方向( ERessyahoukou )の引数をとる getMuPtr() 
メソッドにより、 列車方向別の
  Mu< CentDedEkiCont::CdDedEki >
インターフェースを取得することができます。
  この方法で、『駅Order』に対応する駅の情報を取得することもできます。
  	
@attention
  this の get() メソッドは、 CentDedEki オブジェクトのコピーを返します。
get() メソッドで返されたオブジェクトに対して、
CentDedEki オブジェクトを更新するメソッドを呼び出しても、
コンテナ内の駅オブジェクトを更新することはできません。
コンテナ内の駅オブジェクトのメソッドを呼び出す場合は、
getMuPtr() で Mu<const CentDedEki*>* を取得してから、
そのインターフェース経由で CentDedEki* を取得し、そのポインタに
メソッドを呼び出してください。
  

【駅Index と 駅Order , 時刻Order】
 -------------------------------- 

  『路線』 ( CentDedRosen ) オブジェクト内の特定の
『駅』 ( CentDedEki )オブジェクトを指定する方法、及び
『列車』 ( CentDedRessya )オブジェクト内の特定の
『駅時刻』 ( CentDedEkiJikoku ) オブジェクトを指定する方法には、
『駅Index』・『駅Order』の２つがあります。どちらも、
0 以上 ( 駅の数) 未満 の整数で、『駅』を指定します。

  『駅Index』は、路線の下り列車の始発駅（上り列車の終着駅）が 0 ・ 
下り列車の終着駅（上り列車の始発駅） が ( 駅の数 - 1 ) となります。

  『駅Oeder』は、列車の方向別のインデクスです。下り列車・上り列車
ともに始発駅が 0 ・ 終着駅が ( 駅の数 - 1 ) と
なります。

  従って、『駅Index』が 0 の駅は、下り列車にとっては『駅Oeder』 も
 0 ですが、上り列車にとっては『駅Order』 は （駅の数 - 1 ）となります。 

  『路線』 ( CentDedRosen ) クラスでは、原則として
『駅』( CentDedEki ) オブジェクトを指定するのに『駅Index』を使います。
『駅』を保持するコンテナ CentDedRosen::m_CentDedEkiCont の添え字も
『駅Index』になっています。@n
  これとは対照的に、『列車』(クラスでは、原則として
『駅時刻』 ( CentDedEkiJikoku ) オブジェクトを指定するのには
『駅Order』を使います。『駅時刻』 ( CentDedEkiJikoku ) を保持するコンテナ
  CentDedRessya::m_CentDedEkiJikokuCont の添え字も、『駅Order』 
となります。
  どちらのクラスにおいても、『駅Index』と『駅Order』の相互変換を行う
メソッド EkiIndexOfEkiOrder() , EkiOrderOfEkiIndex() を提供しています。

『時刻Order』は、『列車』オブジェクト内で、特定の時刻
（ある駅の着・発のいずれか）を指定する順序数です。
『時刻Order』は、以下の法則を持ちます。
値の範囲は、0 以上 駅の数*2 未満です。

- 『駅Order』*2 + 0 ・・・『駅Order』の駅の着時刻(とそれ以降)
を変更します。
- 『駅Order』*2 + 1 ・・・『駅Order』の駅の発時刻(とそれ以降)
を変更します。

制約
 -------------------------------- 


操作のエラー検査・修正
 -------------------------------- 

(△)駅の追加(insert)：　全ての列車の駅時刻コンテナに駅時刻を追加
　(onEkiInsert)CentDedRosen→CentDedEkiJikokuCont

(△)駅の削除(erase):　全ての列車の駅時刻コンテナから駅時刻を削除



制約に合うように属性を修正(adjust)
 -------------------------------- 
○すべてのCentDedEki(駅)に、adjust()を委譲する

*/
class CentDedEkiCont : public CMuiCopiedParent< CentDedEki >
{
	typedef  CMuiCopiedParent<CentDedEki>	super ;

public:
	// ****************************************************************
	//	CentDedEkiCont::CdDedEki
	// ****************************************************************
	/**
	@brief
		駅の情報を保持する、単純データクラスです。

	  CentDedEkiCont::getMuPtr(ERessyahoukou) メソッドにより、 
	 Mu< CentDedEkiCont::CdDedEki > インターフェースを取得すると、
	コンテナ内の駅の属性を、この形式で取得することができます。

	この単純データクラスで取得する情報は、列車方向{下り,上り}に合わせた
	形式になっています。
	例えば、駅時刻形式が[下り着時刻]となっている駅があった場合、

	その駅の CentDedEkiCont::CdDedEki オブジェクトを下り方向で取得すると
		- m_bChakujikokuHyouji = true ;
		- m_bHatsujikokuHyouji = false ;

	同じ駅の CentDedEkiCont::CdDedEki オブジェクトを上り方向で取得すると
		- m_bChakujikokuHyouji = false ;
		- m_bHatsujikokuHyouji = true ;

	となります。
	 */
	class CdDedEki
	{
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
		  	着時刻表示あり。
		 */
		bool m_bChakujikokuHyouji ;
	
		/**
		  	駅時刻形式。
		  	発時刻表示あり。
		 */
		bool m_bHatsujikokuHyouji ;
		
		/**
		  	『駅規模』を表す列挙です。
		  
		  	規定値は、 Ekikibo_Ippan 
		 */
		CentDedEki::EEkikibo	m_eEkikibo ;
	
		/**
		  	この駅の下（終着駅より）に、境界線あり。
		  
		   	この属性が true の駅では、時刻表画面の駅欄の下側に
		  	太い境界線を描画します。
		   	この属性は、駅ビューと時刻表ビューに適用されます。
		 */
		bool m_bKyoukaisen ;

		/**
			ダイヤグラム列車情報表示
		
			この属性が true の駅では、ダイヤグラムビューにおいて、
			列車の列車情報を描画します。

			既定値は false です。
		*/	
		CentDedEki::EDiagramRessyajouhouHyouji m_eDiagramRessyajouhouHyouji ;

		/**
			主本線設定

			番線設定の初期値になります。
		*/
		int m_iMainTrack;

		/**
			時刻表番線表示
			この属性がtrueの駅では時刻表ビューで
			列車番線を表示します。
			下り発着・上り発着の場合は、それぞれ下り・上りのみ
			trueとします。
		*/
		bool m_bJikokuhyouTrackDisplay;

		/**
			ダイヤグラム番線表示
			この属性がtrueの駅ではダイヤグラムビューで
			在線表を表示します。
		*/
		bool m_bDiagramTrackDisplay;
		//Mu<CentDedEkiTrack2*>* m_pCentDedEkiTrack2;
		CentDedEkiTrack2Cont m_CentDedEkiTrack2;

		//vector<tstring> m_strOuterTerminalEkimei;
		vector<OuterTerminal> m_OuterTerminalCont;

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
			基本時刻表において、前作業欄・後作業欄がいくつ表示されるかを表します
		*/
		int m_iJikokuhyouBeforeOperation;
		int m_iJikokuhyouAfterOperation;

		/**
			基本時刻表において、前作業欄・後作業欄へ解結編成・増結編成作業欄を表示するか否かです
			(ver2.05から)
		*/
		bool m_bJikokuhyouBeforeOperationBefore;
		bool m_bJikokuhyouBeforeOperationAfter;
		bool m_bJikokuhyouAfterOperationBefore;
		bool m_bJikokuhyouAfterOperationAfter;

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
			カスタマイズ時刻表ビューでの着時刻表示設定

			true:この駅で着時刻を表示します
			false:この駅では着時刻を表示しません。
		*/
		bool m_bJikokuhyouChakuJikokuDisplay;

		/**
			カスタマイズ時刻表ビューでの発時刻表示設定

			true:この駅で発時刻を表示します
			false:この駅では発時刻を表示しません。
		*/
		bool m_bJikokuhyouHatsuJikokuDisplay;

		/**
			カスタマイズ時刻表ビューでの列車番号表示設定
			
			3:この駅で全列車の列車番号を表示します
			2:この駅で種別変更・列車番号変更を行った列車のみ列車番号を表示します
			1:この駅で種別変更を行った列車のみ列車番号を表示します
			0:この駅では列車番号を表示しません。
		*/
		int m_iJikokuhyouRessyabangouDisplay;

		/**
			カスタマイズ時刻表ビューでの運用番号表示設定
			
			4:この駅で全列車の運用番号を表示します
			3:この駅で運用番号が変わった列車のみ表示します
			2:この駅で種別変更・列車番号変更を行った列車のみ運用番号を表示します
			1:この駅で種別変更を行った列車のみ運用番号を表示します
			0:この駅では列車番号を表示しません。
		*/
		int m_iJikokuhyouOperationNumberDisplay;

		/**
			カスタマイズ時刻表ビューでの運用番号表示段数設定(ver2.05から)
			値の範囲は1-5です(規定値は1)
		*/
		int m_iJikokuhyouOperationNumberDisplayRows;

		/**
			カスタマイズ時刻表ビューでの列車種別表示設定
			
			3:この駅で全列車の列車種別を表示します
			2:この駅で種別変更・列車番号変更を行った列車のみ列車種別を表示します
			1:この駅で種別変更を行った列車のみ列車種別を表示します
			0:この駅では列車種別を表示しません。
		*/
		int m_iJikokuhyouRessyaSyubetsuDisplay;

		/**
			カスタマイズ時刻表ビューでの列車名・号数表示設定
			
			3:この駅で全列車の列車名・号数を表示します
			2:この駅で種別変更・列車番号変更を行った列車のみ列車名・号数を表示します
			1:この駅で種別変更を行った列車のみ列車名・号数を表示します
			0:この駅では列車名・号数を表示しません。
		*/
		int m_iJikokuhyouRessyameiDisplay;

		/**
			カスタマイズ時刻表ビューでの路線外・前列車始発駅表示設定

			true:この駅で路線外・前列車始発駅を表示します
			false:この駅では路線外・前列車始発駅を表示しません。
		*/
		bool m_bJikokuhyouOuterSihatsuDisplay;

		/**
			カスタマイズ時刻表ビューでの路線外・次列車終着駅表示設定

			true:この駅で路線外・次列車終着駅を表示します
			false:この駅では路線外・次列車終着駅を表示しません。
		*/
		bool m_bJikokuhyouOuterShuchakuDisplay;

		///@}
	 public:
		// ********************************
		//	コンストラクタ
		// ********************************
		CdDedEki() :
			m_strEkimei(_T("")),
			m_bChakujikokuHyouji( false ) , 
			m_bHatsujikokuHyouji( false ) ,
			m_eEkikibo( CentDedEki::EEkikibo::Ekikibo_Ippan ) ,
			m_bKyoukaisen( false ) , 
			m_eDiagramRessyajouhouHyouji( CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Origin ),
			m_iMainTrack(0),
			m_bJikokuhyouTrackDisplay(false),
			m_bDiagramTrackDisplay(false)/*,
			m_CentDedEkiTrack2(pCentDedEkiTrack2Cont)*/,
			m_OuterTerminalCont(vector<OuterTerminal>()),
			m_bJikokuhyouTrackOmit(false),
			m_iJikokuhyouBeforeOperation(0),
			m_iJikokuhyouAfterOperation(0),
			m_bJikokuhyouBeforeOperationBefore(false),
			m_bJikokuhyouBeforeOperationAfter(false),
			m_bJikokuhyouAfterOperationBefore(false),
			m_bJikokuhyouAfterOperationAfter(false),
			m_strEkimeiJikokuhyouRyaku(_T("")),
			m_strEkimeiDiagramRyaku(_T("")),
			m_bJikokuhyouChakuJikokuDisplay(false),
			m_bJikokuhyouHatsuJikokuDisplay(false),
			m_iJikokuhyouRessyabangouDisplay(0),
			m_iJikokuhyouOperationNumberDisplay(0),
			m_iJikokuhyouOperationNumberDisplayRows(1),
			m_iJikokuhyouRessyaSyubetsuDisplay(0),
			m_iJikokuhyouRessyameiDisplay(0),
			m_bJikokuhyouOuterSihatsuDisplay(false),
			m_bJikokuhyouOuterShuchakuDisplay(false) {};
		
		CdDedEki(
			const tstring&	strEkimei ,
			bool bChakujikokuHyouji ,
			bool bHatsujikokuHyouji ,
			CentDedEki::EEkikibo	eEkikibo ,
			bool bKyoukaisen , 
			CentDedEki::EDiagramRessyajouhouHyouji eDiagramRessyajouhouHyouji ,
			int iMainTrack,
			bool bJikokuhyouTrackDisplay,
			bool bDiagramTrackDisplay,
			CentDedEkiTrack2Cont* pCentDedEkiTrack2Cont,
			//vector<tstring> strOuterTerminalEkimei,
			vector<OuterTerminal> OuterTerminalCont,
			bool bJikokuhyouTrackOmit,
			int iJikokuhyouBeforeOperation,
			int iJikokuhyouAfterOperation,
			bool bJikokuhyouBeforeOperationBefore,
			bool bJikokuhyouBeforeOperationAfter,
			bool bJikokuhyouAfterOperationBefore,
			bool bJikokuhyouAfterOperationAfter,
			const tstring&	strEkimeiJikokuhyouRyaku,
			const tstring& strEkimeiDiagramRyaku,
			bool bJikokuhyouChakuJikokuDisplay,
			bool bJikokuhyouHatsuJikokuDisplay,
			int iJikokuhyouRessyabangouDisplay,
			int iJikokuhyouOperationNumberDisplay,
			int iJikokuhyouOperationNumberDisplayRows,
			int iJikokuhyouRessyaSyubetsuDisplay,
			int iJikokuhyouRessyameiDisplay,
			bool bJikokuhyouOuterSihatsuDisplay,
			bool bJikokuhyouOuterShuchakuDisplay):
			//Mu<CentDedEkiTrack2*>* pCentDedEkiTrack2):
			m_strEkimei( strEkimei ),
			m_bChakujikokuHyouji( bChakujikokuHyouji ) ,
			m_bHatsujikokuHyouji( bHatsujikokuHyouji ) ,
			m_eEkikibo( eEkikibo ) ,
			m_bKyoukaisen( bKyoukaisen ), 
			m_eDiagramRessyajouhouHyouji( eDiagramRessyajouhouHyouji ) ,
			m_iMainTrack(iMainTrack),
			m_bJikokuhyouTrackDisplay(bJikokuhyouTrackDisplay),
			m_bDiagramTrackDisplay(bDiagramTrackDisplay)/*,
			m_CentDedEkiTrack2(pCentDedEkiTrack2Cont)*/,
			m_OuterTerminalCont(OuterTerminalCont),
			m_bJikokuhyouTrackOmit(bJikokuhyouTrackOmit),
			m_iJikokuhyouBeforeOperation(iJikokuhyouBeforeOperation),
			m_iJikokuhyouAfterOperation(iJikokuhyouAfterOperation),
				m_bJikokuhyouBeforeOperationBefore(bJikokuhyouBeforeOperationBefore),
				m_bJikokuhyouBeforeOperationAfter(bJikokuhyouBeforeOperationAfter),
				m_bJikokuhyouAfterOperationBefore(bJikokuhyouAfterOperationBefore),
				m_bJikokuhyouAfterOperationAfter(bJikokuhyouAfterOperationAfter),
			m_strEkimeiJikokuhyouRyaku(strEkimeiJikokuhyouRyaku),
			m_strEkimeiDiagramRyaku(strEkimeiDiagramRyaku),
			m_bJikokuhyouChakuJikokuDisplay(bJikokuhyouChakuJikokuDisplay),
			m_bJikokuhyouHatsuJikokuDisplay(bJikokuhyouHatsuJikokuDisplay),
			m_iJikokuhyouRessyabangouDisplay(iJikokuhyouRessyabangouDisplay),
			m_iJikokuhyouOperationNumberDisplay(iJikokuhyouOperationNumberDisplay),
				m_iJikokuhyouOperationNumberDisplayRows(iJikokuhyouOperationNumberDisplayRows),
			m_iJikokuhyouRessyaSyubetsuDisplay(iJikokuhyouRessyaSyubetsuDisplay),
			m_iJikokuhyouRessyameiDisplay(iJikokuhyouRessyameiDisplay),
				m_bJikokuhyouOuterSihatsuDisplay(bJikokuhyouOuterSihatsuDisplay),
				m_bJikokuhyouOuterShuchakuDisplay(bJikokuhyouOuterShuchakuDisplay)
		{
			//CentDedEkiTrack2Cont* pCentDedEkiTrack2Cont = aCentDedEki.getEkiTrack2Cont();
			for (int idx = 0; idx < pCentDedEkiTrack2Cont->size(); idx++)
			{
				m_CentDedEkiTrack2.insert(pCentDedEkiTrack2Cont->get(idx), idx);
			}
		};

	 public:
		// ********************************
		///@name CentDedEkiCont::CdDedEki-属性
		// ********************************
		///@{
		tstring	getEkimei()const{	return m_strEkimei ;};
		CdDedEki& setEkimei( const tstring& value ){	
			m_strEkimei = value ;return *this ; } ;
		bool getChakujikokuHyouji()const{	return m_bChakujikokuHyouji ;};
		CdDedEki& setChakujikokuHyouji( bool value ){	
			m_bChakujikokuHyouji = value ; return *this ; } ;
		bool getHatsujikokuHyouji()const{ return m_bHatsujikokuHyouji ;};
		CdDedEki& setHatsujikokuHyouji( bool value ){
			m_bHatsujikokuHyouji = value ; return *this ; } ;
		CentDedEki::EEkikibo	getEkikibo()const{ return m_eEkikibo ;};
		CdDedEki& setEkikibo( CentDedEki::EEkikibo value ){
			m_eEkikibo = value ; return *this ; } ;
		bool getKyoukaisen()const{ return m_bKyoukaisen ;};
		CdDedEki& setKyoukaisen( bool value ){
			m_bKyoukaisen = value ; return *this ; } ;
		CentDedEki::EDiagramRessyajouhouHyouji getDiagramRessyajouhouHyouji()const
		{	return m_eDiagramRessyajouhouHyouji ;};
		CdDedEki& setDiagramRessyajouhouHyouji( CentDedEki::EDiagramRessyajouhouHyouji value )
		{	m_eDiagramRessyajouhouHyouji = value ; return *this ;};
		int getMainTrack()const { return m_iMainTrack; };
		CdDedEki& setMainTrack(int value) {
			m_iMainTrack = value; return *this;
		};
		CdDedEki& setJikokuhyouTrackDisplay(bool value) {
			m_bJikokuhyouTrackDisplay = value; return *this;
		};
		bool getJikokuhyouTrackDisplay()const { return m_bJikokuhyouTrackDisplay; };
		CdDedEki& setDiagramTrackDisplay(bool value) {
			m_bDiagramTrackDisplay = value; return *this;
		};
		bool getDiagramTrackDisplay()const { return m_bDiagramTrackDisplay; };


		CentDedEkiTrack2Cont getCentDedEkiTrack2Cont()const { return m_CentDedEkiTrack2; };
		//Mu<CentDedEkiTrack2*>* getCentDedEkiTrack2Cont()const { return m_pCentDedEkiTrack2; };
		CdDedEki& setCentDedEkiTrack2Cont(CentDedEkiTrack2Cont value) {
			m_CentDedEkiTrack2 = value; return *this;
		};

		//tstring getOuterTerminalEkimei(int iIndex)const {
		//	return m_strOuterTerminalEkimei[iIndex];
		//}
		tstring getOuterTerminalEkimei(int iIndex)const {
			return m_OuterTerminalCont[iIndex].OuterTerminalEkimei;
		}
		tstring getOuterTerminalJikokuRyaku(int iIndex,bool bEkimeiIfNull)const {
			if (bEkimeiIfNull && m_OuterTerminalCont[iIndex].OuterTerminalJikokuRyaku.empty())
			{
				return m_OuterTerminalCont[iIndex].OuterTerminalEkimei;
			}
			else
			{
				return m_OuterTerminalCont[iIndex].OuterTerminalJikokuRyaku;
			}
		}
		tstring getOuterTerminalDiaRyaku(int iIndex, bool bEkimeiIfNull)const {
			if (bEkimeiIfNull && m_OuterTerminalCont[iIndex].OuterTerminalDiaRyaku.empty())
			{
				return m_OuterTerminalCont[iIndex].OuterTerminalEkimei.substr(0,1);
			}
			else
			{
				return m_OuterTerminalCont[iIndex].OuterTerminalDiaRyaku;
			}
		}
		//int getOuterTerminalEkimeiCount()const {
		//	return m_strOuterTerminalEkimei.size();
		//}
		int getOuterTerminalEkimeiCount()const {
			return m_OuterTerminalCont.size();
		}

		CdDedEki& setJikokuhyouTrackOmit(bool value) {
			m_bJikokuhyouTrackOmit = value; return *this;
		};
		bool getJikokuhyouTrackOmit()const { return m_bJikokuhyouTrackOmit; };

		CdDedEki& setJikokuhyouBeforeOperation(int value) {
			m_iJikokuhyouBeforeOperation = value; return *this;
		};
		int getJikokuhyouBeforeOperation()const { return m_iJikokuhyouBeforeOperation; };

		CdDedEki& setJikokuhyouAfterOperation(int value) {
			m_iJikokuhyouAfterOperation = value; return *this;
		};
		int getJikokuhyouAfterOperation()const { return m_iJikokuhyouAfterOperation; };

		CdDedEki& setJikokuhyouBeforeOperationBefore(bool value) {
			m_bJikokuhyouBeforeOperationBefore = value; return *this;
		};
		bool getJikokuhyouBeforeOperationBefore()const { return m_bJikokuhyouBeforeOperationBefore; };

		CdDedEki& setJikokuhyouBeforeOperationAfter(bool value) {
			m_bJikokuhyouBeforeOperationAfter = value; return *this;
		};
		bool getJikokuhyouBeforeOperationAfter()const { return m_bJikokuhyouBeforeOperationAfter; };

		CdDedEki& setJikokuhyouAfterOperationBefore(bool value) {
			m_bJikokuhyouAfterOperationBefore = value; return *this;
		};
		bool getJikokuhyouAfterOperationBefore()const { return m_bJikokuhyouAfterOperationBefore; };

		CdDedEki& setJikokuhyouAfterOperationAfter(bool value) {
			m_bJikokuhyouAfterOperationAfter = value; return *this;
		};
		bool getJikokuhyouAfterOperationAfter()const { return m_bJikokuhyouAfterOperationAfter; };

		tstring	getEkimeiJikokuhyouRyaku(bool bEkimeiIfNull)const {
			if (bEkimeiIfNull && m_strEkimeiJikokuhyouRyaku.empty())
			{
				return m_strEkimei;
			}
			else
			{
				return m_strEkimeiJikokuhyouRyaku;
			}
		};
		CdDedEki& setEkimeiJikokuhyouRyaku(const tstring& value) {
			m_strEkimeiJikokuhyouRyaku = value; return *this;
		};

		tstring	getEkimeiDiagramRyaku(bool bEkimeiIfNull)const {
			if (bEkimeiIfNull && m_strEkimeiDiagramRyaku.empty())
			{
				return m_strEkimei.substr(0, 1);
			}
			else
			{
				return m_strEkimeiDiagramRyaku;
			}
		};
		CdDedEki& setEkimeiDiagramRyaku(const tstring& value) {
			m_strEkimeiDiagramRyaku = value; return *this;
		};

		CdDedEki& setJikokuhyouChakuJikokuDisplay(bool value) {
			m_bJikokuhyouChakuJikokuDisplay = value; return *this;
		};
		bool getJikokuhyouChakuJikokuDisplay()const { return m_bJikokuhyouChakuJikokuDisplay; };
		CdDedEki& setJikokuhyouHatsuJikokuDisplay(bool value) {
			m_bJikokuhyouHatsuJikokuDisplay = value; return *this;
		};
		bool getJikokuhyouHatsuJikokuDisplay()const { return m_bJikokuhyouHatsuJikokuDisplay; };

		CdDedEki& setJikokuhyouRessyabangouDisplay(int value) {
			m_iJikokuhyouRessyabangouDisplay = value; return *this;
		};
		int getJikokuhyouRessyabangouDisplay()const { return m_iJikokuhyouRessyabangouDisplay; };
		CdDedEki& setJikokuhyouOperationNumberDisplay(int value) {
			m_iJikokuhyouOperationNumberDisplay = value; return *this;
		};
		int getJikokuhyouOperationNumberDisplay()const { return m_iJikokuhyouOperationNumberDisplay; };
		CdDedEki& setJikokuhyouOperationNumberDisplayRows(int value) {
			m_iJikokuhyouOperationNumberDisplayRows = value; return *this;
		};
		int getJikokuhyouOperationNumberDisplayRows()const { return m_iJikokuhyouOperationNumberDisplayRows; };
		CdDedEki& setJikokuhyouRessyaSyubetsuDisplay(int value) {
			m_iJikokuhyouRessyaSyubetsuDisplay = value; return *this;
		};
		int getJikokuhyouRessyaSyubetsuDisplay()const { return m_iJikokuhyouRessyaSyubetsuDisplay; };
		CdDedEki& setJikokuhyouRessyameiDisplay(int value) {
			m_iJikokuhyouRessyameiDisplay = value; return *this;
		};
		int getJikokuhyouRessyameiDisplay()const { return m_iJikokuhyouRessyameiDisplay; };
		CdDedEki& setJikokuhyouOuterSihatsuDisplay(bool value) {
			m_bJikokuhyouOuterSihatsuDisplay = value; return *this;
		};
		bool getJikokuhyouOuterSihatsuDisplay()const { return m_bJikokuhyouOuterSihatsuDisplay; };
		CdDedEki& setJikokuhyouOuterShuchakuDisplay(bool value) {
			m_bJikokuhyouOuterShuchakuDisplay = value; return *this;
		};
		bool getJikokuhyouOuterShuchakuDisplay()const { return m_bJikokuhyouOuterShuchakuDisplay; };
		/**
		   @return 
		  	着発の両方の時刻を表示する駅では真です。
		 */
		bool isHatsuChakuHyouji()const
		{	return m_bChakujikokuHyouji && m_bHatsujikokuHyouji;};
	
		///@}
	};

private:
	// ----------------------------------------------------------------
	//	CentDedEkiCont::ContKudari
	// ----------------------------------------------------------------
	/**
	   @brief
	  	下りの『駅Order』 をインデクスとした、
	  		 Mu< CentDedEkiCont::CdDedEki > 
	  	を作成するためのアダプタです。
	 */
	class ContKudari : public Mu< CdDedEki >
	{
	public:
		// ********************************
		//	Mu< CentDedEkiCont::CdDedEki >
		// ********************************
		/**
		   @return 
		  	コンテナに格納されているデータの個数を返します。 
 		 */
		virtual int  size()const ; 
		/**
		  	コンテナ内の、インデクスで指定された場所に格納されている 
		  	データを返します。 
		   @param iEkiOrder [in] 
		  	下りり方向の『駅Order』を指定してください。 
		  	範囲は０以上 size() 未満です。
		  	 INT_MAX は、末尾を指定したものとみなします。
		 */
		virtual CdDedEki get(int iEkiOrder )const ;
	
		
	} m_xContKudari ;
	friend class ContKudari ;
	// ----------------------------------------------------------------
	//	CentDedEkiCont::ContNobori
	// ----------------------------------------------------------------
	/**
	   @brief
	  	上りの『駅Order』 をインデクスとした、	
	  		 Mu< CentDedEkiCont::CdDedEki > 
	  	を作成するためのアダプタです。
	 */
	class ContNobori : public Mu< CdDedEki >
	{
	public:
		// ********************************
		//	Mu< CentDedEkiCont::CdDedEki >
		// ********************************
		/**
		   @return 
		  	コンテナに格納されているデータの個数を返します。 
 		 */
		virtual int  size()const ; 
		/**
		  	コンテナ内の、インデクスで指定された場所に格納されている 
		  	データを返します。 
		   @param iEkiOrder [in] 
		  	上り方向の『駅Order』を指定してください。 
		  	範囲は０以上 size() 未満です。
		  	 INT_MAX は、末尾を指定したものとみなします。
		 */
		virtual CdDedEki get(int iEkiOrder )const ;
	
	} m_xContNobori ;
	friend class ContNobori ;
	



public:
	// ********************************
	//	コンストラクタ
	// ********************************

public:
	// ********************************
	///@name Mui
	// ********************************
	///@{

	/**
		駅オブジェクトを追加します。

	(△)駅の追加(insert)：　全ての列車の駅時刻コンテナに駅時刻を追加
	　(onEkiInsert)CentDedRosen→CentDedEkiJikokuCont


	@param element
		要素を指定してください。 
	@param iIndex
		0 から始まるインデクスを指定してください。 
		範囲は０以上 size() 以下です。 ０は、先頭・size()なら末尾への
		追加になります。 但し、INT_MAX は、末尾を指定したものとみなします。 
	@return
		0以上は成功、負の数はエラーです。
		-	-1 ;	//	インデクスが範囲外です。
		-	-11 ;	//	本線を追加することは出来ません。

	*/
	virtual int insert( const CentDedEki& element ,  int iIndex=INT_MAX) ;
	/**
		駅オブジェクトを追加します。

	(△)駅の削除(erase):　全ての列車の駅時刻コンテナから駅時刻を削除

	 @param iIndex [in]
	 	０から始まるインデクスを指定してください。
	 	範囲は０以上 size() 未満です。
	 	但し、INT_MAX は、末尾を指定したものとみなします。
	 @param iSize [in]
	 	削除する要素の数を指定してください。
	 	但し、INT_MAX は、 iIndex から末尾までを表します。
	 @attention
		iIndex と iSize の両方を INT_MAX にすることはできません。
	 @return
	 	0以上は成功、負の数はエラーです
		-	-1 ;	//	インデクスが範囲外です。
		-	-11 ;	//	本線を削除することは出来ません。
	*/
	virtual int erase( int iIndex  , int iSize = 1 ) ;

	/**
		コンテナ内の、インデクスで指定された場所に、 要素を上書きします。 
		上書き後の要素の CChildItem::m_pParent には、this を登録します。

		番線種別の異なるオブジェクトを上書きすることはできません。		

	@param element
		要素を指定してください。 
	@param iIndex
		０から始まるインデクスを指定してください。 範囲は０以上 size() 
		未満です。 但し、INT_MAX は、末尾を指定したものとみなします。 
	@return
		成功したら0以上、エラーなら負の数です。
		-	-11 ;	//	番線種別の異なるオブジェクトを上書きすることはできません。
	*/
	virtual int set( const CentDedEki& element , int iIndex ) ;
	///@}

public:
	// ********************************
	///@name	CMuiCopied<CentDedEki>
	// ********************************
	///@{

	/**
		基本クラスの Mu<CentDedEki*>* getMuPtr() は、
		このクラスのオーバーロード
		Mu<CdDedEki>* getMuPtr( ERessyahoukou eRessyahoukou )
		によって隠蔽されます。
		この隠蔽を解除するため、以下の宣言を行っています。
		これは、以下のコードと等価です。
	@code
	Mu<CentDedEki*>* getMuPtr()
	{	
		return super::getMuPtr() ;
	};
	const Mu<const CentDedEki*>* getMuPtr()const
	{
		return super::getMuPtr() ;
	};
	@endcode
	*/
	super::getMuPtr ;
	///@}


public:
	// ********************************
	///@name CentDedEkiCont-関連
	// ********************************
	///@{
	/**
	@return
		このコンテナが CentDedRosen に包含されている場合は、
		CentDedRosen のアドレス。
		そうでないならNULL。
	*/
	virtual CentDedRosen* getRosen(){ return NULL ;}
	/**
	@return
		このコンテナが CentDedRosen に包含されている場合は、
		CentDedRosen のアドレス。
		そうでないならNULL。
	*/
	virtual const CentDedRosen* getRosen()const { return NULL ;}
	///@}


	// ********************************
	///@name CentDedEkiCont-操作
	// ********************************
	///@{
	/**
		set() が可能か否かを判断します。

		番線種別の異なるオブジェクトを上書きすることはできません。		
	@param element
		要素を指定してください。 
	@param iIndex
		０から始まるインデクスを指定してください。 範囲は０以上 size() 
		未満です。 但し、INT_MAX は、末尾を指定したものとみなします。 
	@return
		-	0以上: set() が可能。
		-	負の数: set()は、この戻り値で失敗します。
		-	-11 ;	//	番線種別の異なるオブジェクトを上書きすることはできません。
	 */
	virtual int  setable(  const CentDedEki& element , int iIndex )const ;

	/**
		element がこのコンテナの子である場合は、インデクスを返します。
	@param element
		要素を指定してください。 
	@return
		element がこのコンテナの子である場合は、インデクスを返します。
		そうでない場合は、 -1 です。
	*/
	virtual int  getIndex( const CentDedEki* element )const ;




	/**
		『駅Order』 をインデクスにして、コンテナ内の駅オブジェクトの
		情報を取得するためのインターフェースを返します。
	
		このインターフェースをつかうと、『駅Order』をインデクスに指定して、
		対応する駅の情報を CentDedEkiCont::CdDedEki 形式で
		取得することができます。
	 @param eRessyahoukou [in]
		列車方向を指定してください。
	 @return 
		コンテナ内の駅オブジェクト CentDedEki オブジェクトの属性を返す
		インターフェースを返します。
	 */
	const Mu<CdDedEki>* getMuPtr( ERessyahoukou eRessyahoukou )const
	{
		if ( eRessyahoukou == Ressyahoukou_Nobori ){
			return &m_xContNobori ;	
		}
		return &m_xContKudari ;	
	};
	
	/**
		『駅Order(駅方向別Index)』を、『駅Index』に変換します。
	 @param eRessyahoukou [in]
		列車方向を指定してください。
		- Ressyahoukou_Kudari
		- Ressyahoukou_Nobori
		のいずれかです。
	 @param iEkiOrder [in]
		『駅Order』を指定してください。
	 @return 
		0以上の『駅Index』を返します。
		引数が不正な場合は、 -1 を返します。
	 */
	int EkiIndexOfEkiOrder( ERessyahoukou eRessyahoukou , int iEkiOrder )const ;
	
	/**
		『駅Index』を『駅Order(駅方向別Index)』に変換します。
	 @param eRessyahoukou [in]
		列車方向を指定してください。
		- Ressyahoukou_Kudari
		- Ressyahoukou_Nobori
		のいずれかです。
	 @param iEkiIndex [in]
		『駅Index』を指定してください。
	 @return 
		0以上の『駅Order』を返します。
		引数が不正な場合は、 -1 を返します。
	 */
	int EkiOrderOfEkiIndex( ERessyahoukou eRessyahoukou , int iEkiIndex )const;

	int EkiIndexOfEkiID(int iEkiID)const;
	///@}

	/**
	CentDedEkiCont に CentDedEki が追加された直後、
	CentDedEkiCont から呼び出されます。
	@param iEkiIndex
	追加された CentDedEki のインデクス。
	*/
	virtual void onEkiInsert(int iEkiIndex);
	/**
	CentDedEkiCont から CentDedEki が削除された直後、
	CentDedEkiCont から呼び出されます。
	@param iEkiIndex
	削除された CentDedEki の先頭のインデクス。
	*/
	virtual void onEkiErase(int iEkiIndex);


	/**
	CentDedEkiが変更された結果、新たに分岐駅を設定した、
	もしくは基幹駅を変更した場合に、呼び出されます。
	必要に応じて、番線情報・主本線設定を変更します。
	@param iEkiIndex
	変更された駅Index
	@param iBrunchCoreEkiIndex
	編集対象駅の、iBrunchCoreEkiIndex(基幹駅Index)の値です。
	この値を基に、番線統合、主本線設定を変更します。
	-番線情報の統一
		主本線設定は基幹駅優先。
		番線設定は、基幹駅側が優先となりますが、
		変更された駅の番線数が、基幹駅よりも多い場合、超過分を基幹駅及び
		他の繋がっている駅に追加します。
	-路線外発着駅リストの融合
		基幹駅側をベースとし、基幹駅には無く派生駅にのみあるものをリストの後ろに追加していきます
		なお、路線外発着駅名が一致すれば、略称が一致しなくても同一とみなします。
		その時、iOuterTerminalEkimeiMapに新たなリストにおけるindexを格納し、
		列車側の修正に用います。
	@param iEkiIndexBrunchOriginSide
		基幹駅の駅Index及び、変更された駅と、基幹駅から見て
		同じ側にある派生駅の駅Indexの集合です。
	@param iEkiIndexLoop
		基幹駅が環状線の起点・終点になっている場合、対応する終点・起点の駅Indexが入ります。
		環状線が複数連なっている場合、その数だけ、駅Indexが格納されます
	@param iEkiIndexBrunchTerminalSide
		基幹駅から見て、変更された駅と反対側にある派生駅の駅Indexの集合です。
		ただし、間に環状線が挟まる場合は、その先端を基幹駅とする、派生駅の集合になります
	@param iOuterTerminalEkimeiMap
		路線外発着駅の移動を示すマップです。
		分岐駅設定により、基幹側と派生駅との間で、路線外発着駅を融合するとき、
		派生側にもともと存在していた路線外始発駅の、融合後のindexを保存し、列車側の修正に用います
	*/
	virtual bool adjustBrunchLoopByBrunchEdit(int iEkiIndex,
		int iBrunchCoreEkiIndex, deque<int> &iEkiIndexBrunchOriginSide,
		deque<int> &iEkiIndexLoop, deque<int> &iEkiIndexBrunchTerminalSide,
		vector<int> &iOuterTerminalEkimeiMap);

	/**
	CentDedEkiが変更された結果、新たに環状線を設定した、
	もしくは起点駅を変更した場合に、呼び出されます。
	必要に応じて、番線情報・主本線設定を変更します。
	@param iEkiIndex
	変更された駅Index
	@param iLoopOriginEkiIndex
	編集対象駅の、iLoopOriginEkiIndex(起点駅Index)の値です。
	この値を基に、番線統合、主本線設定を変更します。
	-番線情報の統一
		主本線設定は起点駅優先。
		番線設定は、起点駅側が優先となりますが、
		変更された駅の番線数が、起点駅よりも多い場合、超過分を起点駅及び
		他の繋がっている駅に追加します。
	-路線外発着駅リストの融合
		起点駅側をベースとし、起点駅には無く終点駅にのみあるものをリストの後ろに追加していきます
		なお、路線外発着駅名が一致すれば、略称が一致しなくても同一とみなします。
		その時、iOuterTerminalEkimeiMapに新たなリストにおけるindexを格納し、
		列車側の修正に用います。
	@param iEkiIndexLoop
		変更された駅及び起点駅を含む、環状線設定により繋がっている駅の駅Indexが入ります。
		駅Indexは起点方(若い数字)が前になるように、入れられます。
	@param iEkiIndexBrunchOriginSide
		上記環状線駅のうち最も起点方の駅を基幹駅とする、派生駅の駅Indexが入ります。
		分岐駅・環状線の設定規則より、派生駅Indexは必ず基幹駅よりも起点方になります。
	@param iEkiIndexBrunchTerminalSide
		上記環状線駅のうち最も終点方の駅を基幹駅とする、派生駅の駅Indexが入ります。
		分岐駅・環状線の設定規則より、派生駅Indexは必ず基幹駅よりも終点方になります。
	@param iOuterTerminalEkimeiMap
		路線外発着駅の移動を示すマップです。
		環状線設定により、起点側と終点駅との間で、路線外発着駅を融合するとき、
		派生側にもともと存在していた路線外始発駅の、融合後のindexを保存し、列車側の修正に用います
	*/
	virtual int adjustBrunchLoopByLoopEdit(int iEkiIndex,
		int iLoopOriginEkiIndex, deque<int> &iEkiIndexBrunchOriginSide,
		deque<int> &iEkiIndexLoop, deque<int> &iEkiIndexBrunchTerminalSide,
		vector<int> &iOuterTerminalEkimeiMap);
	
	/**
	iEkiIndexを基に、分岐駅設定・環状線設定で連なる駅のIndexを検索し、返します
	番線プロパティの変更、番線の入換時に、用いられます。
	@param iEkiIndex
		探索起点Index
	@param iEkiIndexBrunchLoop
		連なる駅のIndexを、ここに格納されます
	@return
		iEkiIndexBrunchLoopのサイズを返します
	*/
	virtual int getEkiIndexBrunchLoop(
		int iEkiIndex, deque<int> &iEkiIndexBrunchLoop)const;

	/**
	iEkiIndexを基に、分岐駅設定・環状線設定で連なる駅のIndexを検索し、返します
	@param iEkiIndex
		探索起点Index
	@param iEkiIndexBrunchOriginSide
		起点方派生駅がある場合、ここに格納されます
	@param iEkiIndexLoop
		基幹駅及び起点駅・終点駅がある場合、ここに格納されます。
	@param iEkiIndexBrunchTerminalSide
		終点方派生駅がある場合、ここに格納されます
	@return
		INT_MIN:iEkiIndexが起点方派生駅の場合、この値が返されます
		-1:iEkiIndexが単独駅(分岐駅及び環状線と無関係)の場合、この値が返されます
		0以上:iEkiIndexが基幹駅及び起点駅・終点駅の場合、
			iEkiIndexLoop内におけるIndexを返します。
		INT_MAX:iEkiIndexが終点方派生駅の場合、この値が返されます
	*/
	virtual int searchEkiIndexBrunchLoop(
		int iEkiIndex, 
		deque<int> &iEkiIndexBrunchOriginSide,
		deque<int> &iEkiIndexLoop, 
		deque<int> &iEkiIndexBrunchTerminalSide)const;

	/**
	iEkiIndexを基に、分岐駅設定・環状線設定で連なる駅のIndexを検索し、返します
	@param iEkiIndex
		探索起点Index
	@param iEkiIndexBrunchOriginSide
		起点方派生駅がある場合、ここに格納されます
	@param iEkiIndexLoop
		基幹駅及び起点駅・終点駅がある場合、ここに格納されます。
	@param iEkiIndexBrunchTerminalSide
		終点方派生駅がある場合、ここに格納されます
	@return
		INT_MIN:iEkiIndexが起点方派生駅の場合、この値が返されます
		-1:iEkiIndexが単独駅(分岐駅及び環状線と無関係)の場合、この値が返されます
		0以上:iEkiIndexが基幹駅及び起点駅・終点駅の場合、
			iEkiIndexLoop内におけるIndexを返します。
		INT_MAX:iEkiIndexが終点方派生駅の場合、この値が返されます
	*/
	virtual int getEkiIndexBrunchLoop(
		int iEkiIndex,
		deque<int> &iEkiIndexBrunchOriginSide,
		deque<int> &iEkiIndexLoop,
		deque<int> &iEkiIndexBrunchTerminalSide)const;


	/**
	iEkiOrderを基に、分岐駅設定・環状線設定で連なる駅のOrderを検索し、返します
	@param iEkiOrder
		探索起点Order
	@param eRessyahoukou
		求める列車方向です。
	@param iEkiOrderBrunchOriginSide
		起点方派生駅がある場合、ここに格納されます
		上り列車の場合は、列車に対する起点方(路線の終点方)が入ります。
	@param iEkiOrderLoop
		基幹駅及び起点駅・終点駅がある場合、ここに格納されます。
		上り列車の場合は、列車の起点方から順に格納されます。
	@param iEkiOrderBrunchTerminalSide
		終点方派生駅がある場合、ここに格納されます
		上り列車の場合は、列車に対する終点方(路線の起点方)が入ります。
	@return
		INT_MIN:iEkiOrderが起点方派生駅の場合、この値が返されます
			上り列車の場合は、列車の起点方(路線の終点方)の場合です
		-1:iEkiOrderが単独駅(分岐駅及び環状線と無関係)の場合、この値が返されます
		0以上:iEkiOrderが基幹駅及び起点駅・終点駅の場合、
			iEkiOrderLoop内におけるOrderを返します。
		INT_MAX:iEkiOrderが終点方派生駅の場合、この値が返されます
			上り列車の場合は、列車の終点方(路線の起点方)の場合です
	*/
	virtual int getEkiOrderBrunchLoop(
		int iEkiOrder, 
		ERessyahoukou eRessyahoukou,
		deque<int> &iEkiOrderBrunchOriginSide,
		deque<int> &iEkiOrderLoop, 
		deque<int> &iEkiOrderBrunchTerminalSide)const;

	/**
	iEkiIndexを基に、分岐駅設定・環状線設定で連なる駅のIndexを検索し、返します
	旧形式ファイルを読み込む際、分岐駅設定を自動解釈しますが、
	その際、最低限の停車・通過だけの摺り合わせを行います
	@param iEkiIndex
	探索起点Index
	@param iEkiIndexBrunchGroup
	基幹駅及び派生駅がある場合、ここに格納されます
	@return
	-1:iEkiIndexが単独駅(分岐駅及び環状線と無関係)の場合、この値が返されます
	0以上:iEkiIndexが基幹駅及び派生駅の場合、
	基幹駅のIndexを返します。
	*/
	virtual int getEkiIndexBrunchConvert(
		int iEkiIndex,
		deque<int> &iEkiIndexBrunchGroup)const;


	/**
	iEkiOrderを基に、分岐駅設定・環状線設定で連なる駅のOrderを検索し、返します
	旧形式ファイルを読み込む際、分岐駅設定を自動解釈しますが、
	その際、最低限の停車・通過だけの摺り合わせを行います
	@param iEkiOrder
	探索起点Order
	@param eRessyahoukou
	求める列車方向です。
	@param iEkiIOrderBrunchGroup
	基幹駅及び派生駅がある場合、ここに格納されます
	@return
	-1:iEkiOrderが単独駅(分岐駅及び環状線と無関係)の場合、この値が返されます
	0以上:iEkiOrderが基幹駅及び起点駅・終点駅の場合、
	基幹駅のOrderを返します。
	*/
	virtual int getEkiOrderBrunchConvert(
		int iEkiOrder,
		ERessyahoukou eRessyahoukou,
		deque<int> &iEkiIOrderBrunchGroup)const;

	/**
		駅編集がなされた際、駅番線・主本線・路線外発着駅の変更を、分岐駅・環状線設定で繋がれた同一駅へ反映します
		@param iEkiIndex[in]
		編集が行われた駅です。この駅から他の駅に反映します。
		@param iEkiIndexBrunchLoop[in]
		編集が行われた駅と、同一駅扱いの駅群です。
		iEkiIndex自体も含まれているので注意してください。
	*/
	virtual void adjustBrunchLoopEkiTrack2OuterTerminal(
		const int iEkiIndex,
		const deque<int> &iEkiIndexBrunchLoop,
		const vector<int>& iEkiTrack2Map);

	/**
		二つの駅が、分岐・環状設定で接続された同じグループに属するか否かを返します。
		駅Indexで指定します。
		@param iEkiIndexA
		探索対象の一つ目の駅Indexです。
		@param iEkiIndexB
		探索対象の二つ目の駅Indexです。
	*/
	virtual bool isSameBrunchLoopGroup(
		const int iEkiIndexA,
		const int iEkiIndexB)const;

	/**
	二つの駅が、分岐・環状設定で接続された同じグループに属するか否かを返します。
	駅Orderと列車方向で指定します。
	@param iEkiOrderA
	探索対象の一つ目の駅Indexです。
	@param iEkiOrderB
	探索対象の二つ目の駅Indexです。
	*/
	virtual bool isSameBrunchLoopGroup(
		const int iEkiOrderA,
		const int iEkiOrderB,
		ERessyahoukou eRessyahoukou)const;

	/**
		駅の編集が行われたときなどに呼び出され、
		分岐・環状線設定に依る駅の繋がり情報を更新します。
	*/
	virtual void adjustBrunchLoopCont();

	/**
		Ver2.0以前のファイルを読み込むとき、分岐・環状線設定で繋がった駅間で、
		路線外発着駅名がそれぞれ独立していたものを、統一して共有するために用います。
	*/
	virtual void mergeOuterTerminal(
		deque<int> &iEkiIndexBrunchOriginSide,
		deque<int> &iEkiIndexLoop,
		deque<int> &iEkiIndexBrunchTerminalSide,
		vector<vector<int>> &iOuterTerminalMapCont);

	/**
		交差支障チェックルールの編集を行ったとき、編集状態を分岐・環状線設定で繋がった他駅に反映します。
	*/
	virtual void adjustCrossingCheckRule(
		const int iEkiIndex,
		const deque<int>& iEkiIndexBrunchLoop);

	/**
		番線・路線外発着駅の編集を、交差支障チェックルールに反映します。
		番線：番線Indexが変わったものは補正、削除された番線については削除
		//発着：iEkiIndexBrunchLoopにないものは削除します→全体で行う(分岐設定が切れた駅を考慮して)
		路線外発着：路線外発着駅Indexが変わったものは補正し、削除された駅については削除
	*/
	virtual void adjustBrunchLoopCrossingCheckRule(
		const int iEkiIndex,
		const deque<int>& iEkiIndexBrunchLoop,
		const vector<int>& iEkiTrack2Map,
		const vector<int>& iOuterTerminalEkimeiMap);

	/**
		駅の編集を行った後に、交差支障チェックルールの調整を行います。
		具体的には、(1)分岐・環状線関係の変更によって、不適切になったTrackContentの削除
		(2)駅時刻形式の変更によって、不適切になったTrackContentの削除です。
	*/
	virtual void adjustCrossingCheckRuleByEkiEdit();
};

} //namespace entDed


#endif /*CentDedEkiCont_h*/

