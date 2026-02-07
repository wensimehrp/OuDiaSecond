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
// $Id: CconvJikokuhyouCustomizeCsv.h 
// ****************************************************************
#ifndef  CconvJikokuhyouCustomizeCsv_h
#define  CconvJikokuhyouCustomizeCsv_h
/** @file */
#include "..\DedRosenFileData\CDedRosenFileData.h"
#include "Str\CsvDocument\CdCsvDocument.h"
#include "..\ViewJikokuhyou\JikokuhyouColSpec\CdYColSpecCont.h"

namespace ConvJikokuhyouCsv{
using namespace entDed ;
using namespace OuLib::Str::CsvDocument;
using ViewJikokuhyou::JikokuhyouColSpec::CdYColSpecCont;
using ViewJikokuhyou::JikokuhyouColSpec::CdYColSpec;

/**
@brief
	時刻表形式CSVファイルとの間のデータ変換を行います。

	CentDedRosenと、時刻表形式のCSVファイルを生成します。

	反対に、CentDedRosenに、時刻表形式のCSVファイルの内容を取り込む
	こともできます。
*/
class CconvJikokuhyouCustomizeCsv
{
private:
	/// CSV上の固定文字列「下り」
	tstring m_nameKudari ;
	/// CSV上の固定文字列「上り」
	tstring m_nameNobori ;
	/// CSV上の固定文字列「列車番号」
	tstring m_nameRessyabangou ;
	/// CSV上の固定文字列「列車種別」
	tstring m_nameRessyasyubetsu ;
	/// CSV上の固定文字列「列車名」
	tstring m_nameRessyamei ;
	/// CSV上の固定文字列「号数」
	tstring m_nameGousuu ;
	/// CSV上の固定文字列「号」
	tstring m_nameGou ;
	/// CSV上の固定文字列「備考」
	tstring m_nameBikou ;
	/// CSV上の固定文字列「着」
	tstring m_nameChaku ;
	/// CSV上の固定文字列「発」
	tstring m_nameHatsu ;
	/// CSV上の固定文字列「レ」
	tstring m_nameTsuuka ;
	/// CSV上の固定文字列「||」
	tstring m_nameKeiyunasi ;
	/// CSV上の固定文字列「番線」
	tstring m_nameTrack;
	/// CSV上の固定文字列「運用番号」
	tstring m_nameOperationNumber;
	/// CSV上の固定文字列「始発駅」
	tstring m_nameShihatsuEkimei ;
	/// CSV上の固定文字列「始発駅作業」
	tstring m_nameOperation_Shihatsu;
	/// CSV上の固定文字列「終着駅」
	tstring m_nameShuchakuEkimei;
	/// CSV上の固定文字列「終着駅作業」
	tstring m_nameOperation_Shuchaku;
	/// CSV上の固定文字列「時刻」
	tstring m_nameJikoku;
	/// CSV上の固定文字列「前作業」
	tstring m_nameBeforeOperation;
	/// CSV上の固定文字列「後作業」
	tstring m_nameAfterOperation;


	tstring m_nameConnect = _T("↳");
	tstring m_nameRelease = _T("↴");
	tstring m_nameContinue = _T("↓");
	tstring m_nameLoop = _T("環状");

	CdYColSpecCont m_CdYColSpecCont;
protected:
	// --------------------------------
	///@name	駅時刻セルの文字列の解釈
	// --------------------------------
	///@{
	/**
		駅扱と時刻をもとに、時刻をCSV向けに文字列化します。
		
	@param eEkiatsukai [in]
		駅扱を指定してください。
	@param aCdDedJikoku [in]
		時刻を指定してください。
		
		eEkiatsukai が
		CentDedEkiJikoku::Ekiatsukai_None,
		CentDedEkiJikoku::Ekiatsukai_Keiyunasi 
		である場合は、aCdDedJikoku は評価されません。
		
		eEkiatsukaiが
		CentDedEkiJikoku::Ekiatsukai_Teisya, 
		の場合は、通常に時刻を出力します。
		
		eEkiatsukaiが
		CentDedEkiJikoku::Ekiatsukai_Tsuuka, 
		で、aCdDedJikoku が Null でない場合は、
		時刻の末尾に "?" を付与します。
	@param bDisplaySecondEkiJikoku [in] 
		駅時刻の秒単位を出力するかどうかを指定してください。
	@param bDisplayColonEkiJikoku [in] 
		駅時刻にコロンを付けてを出力するかどうかを指定してください。
	@return
		変換された文字列を返します。
	*/
	tstring encode_Ekijikoku( 
		CentDedEkiJikoku::EEkiatsukai eEkiatsukai , 
		const CdDedJikoku& aCdDedJikoku ,
		const bool bDisplaySecondEkiJikoku,
		const bool bDisplayColonEkiJikoku,
		const int iSecondRoundChaku,
		const int iSecondRoundHatsu,
		const bool bDisplay2400,
		const bool bIsChakuJikoku = false,
		const CdDedJikoku& ReferJikoku = CdDedJikoku()) ;

	// --------------------------------
	///@name encode() の下請関数	
	// --------------------------------
	///@{


	/**
		CdCsvDocument に、Nullでない列車を追加します。

	@param pCentDedRessyasyubetsuContGet [in]
		列車種別コンテナを指定してください。
	@param contiJikokuOrderOfJikokuhyouIndex [in] 
		時刻表Index-時刻Order対照配列を指定してください。
	@param pCentDedRessya [in]
		列車を指定してください。
	@param pCdCsvDocument [in,out]
		この関数はこのCSVドキュメントに列車情報を追加します。
	@param bDisplayTsuukaEkiJikoku [in] 
		通過駅の時刻を表示するかどうかを指定してください。
	@param bDisplaySecondEkiJikoku [in] 
		駅時刻の秒単位を出力するかどうかを指定してください。
	@param bDisplayColonEkiJikoku [in] 
		駅時刻にコロンを付けてを出力するかどうかを指定してください。
	@param bDisplayShihatsuShuchakuEkimei [in] 
		始発終着駅名欄を出力するかどうかを指定してください。
	@param bDisplayParentSyubetsu [in] 
		親種別を有効にしてを出力するかどうかを指定してください。
	@param bDisplayRessyamei [in] 
		列車名・号数を出力するかどうかを指定してください。
	@param iEnableOperation [in] 
		運用機能の状態を指定してください。
	@param bDisplayOuterTerminalShihatsu [in] 
		起点側の路線外発着欄を出力するかどうかを指定してください。
	@param bDisplayOuterTerminalShuchaku [in] 
		終点側の路線外発着欄を出力するかどうかを指定してください。
	@return
		成功したら 0 以上、エラーなら負の数です。
		-	-1 ;	//	この列車はNULLです。
	*/
	int encode_AddRessya( 
		const Mu<const CentDedRessyasyubetsu*>* 
			pCentDedRessyasyubetsuContGet ,
		const Mu<const CentDedRessya*>* pCentDedRessyaCont,
		const CustomizeJikokuhyouContent& aCustomizeJikokuhyouContent,
		CdCsvDocument* pCdCsvDocument ,
		const CentDedEkiCont* pCentDedEkiCont,
		const Mu<CentDedEkiCont::CdDedEki>* pCdDedEkiCont,
		const bool bDisplayTsuukaEkiJikoku,
		const bool bDisplaySecondEkiJikoku,
		const bool bDisplayColonEkiJikoku,
		const bool bDisplayShihatsuShuchakuEkimei,
		const bool bDisplayParentSyubetsu,
		const bool bDisplayRessyamei,
		const int iEnableOperation,
		const int iSecondRoundChaku,
		const int iSecondRoundHatsu,
		const bool bDisplay2400,
		const int iOperationNumberRows,
		const deque<int> m_iOuterShihatsuDisplayEkiOrder,
		const deque<int> m_iOuterShuchakuDisplayEkiOrder) ;

	/**
		CdCsvDocument に、Null列車を追加します。
	@param pCdCsvDocument [in,out]
		この関数はこのCSVドキュメントに列車情報を追加します。
	@param bDisplayShihatsuShuchakuEkimei [in] 
		始発終着駅名欄を出力するかどうかを指定してください。
	@param bDisplayRessyamei [in] 
		列車名・号数を出力するかどうかを指定してください。
	@param iEnableOperation [in] 
		運用機能の状態を指定してください。
	@param bDisplayOuterTerminalShihatsu [in] 
		起点側の路線外発着欄を出力するかどうかを指定してください。
	@param bDisplayOuterTerminalShuchaku [in] 
		終点側の路線外発着欄を出力するかどうかを指定してください。
	@return
		成功したら 0 以上、エラーなら負の数です。
		-	常に0
	*/
	int encode_AddRessyaNull( 
		CdCsvDocument* pCdCsvDocument,
		const bool bDisplayShihatsuShuchakuEkimei,
		const bool bDisplayRessyamei,
		const int iEnableOperation) ;

	///@}
public:
	// ********************************
	//	コンストラクタ
	// ********************************
	CconvJikokuhyouCustomizeCsv(
		const tstring& nameKudari ,
		const tstring& nameNobori ,
		const tstring& nameRessyabangou ,
		const tstring& nameRessyasyubetsu ,
		const tstring& nameRessyamei ,
		const tstring& nameGousuu ,
		const tstring& nameGou ,
		const tstring& nameBikou ,
		const tstring& nameChaku ,
		const tstring& nameHatsu ,
		const tstring& nameTsuuka ,
		const tstring& nameKeiyunasi,
		const tstring& nameTrack,
		const tstring& nameOperationNumber,
		const tstring& nameShihatsuEkimei,
		const tstring& nameOperation_Shihatsu,
		const tstring& nameShuchakuEkimei,
		const tstring& nameOperation_Shuchaku,
		const tstring& nameJikoku,
		const tstring& nameBeforeOperation,
		const tstring& nameAfterOperation) ;



public:
	// ********************************
	///@name	CconvJikokuhyouCustomizeCsv
	// ********************************
	///@{
	/**
		指定の路線ファイルデータ・ダイヤ・列車方向の
		時刻表を、CSVドキュメントに出力します。

		*pCdCsvDocument がそれまで保持していたデータは破棄します。
	@param aCentDedRosen [in]
		路線を指定してください。
	@param iDiaIndex [in]
		ダイヤのインデクスを指定してください。
	@param eRessyahoukou [in]
		列車方向を指定してください。
	@param iRessyaIndex [in]
		出力する先頭の列車のインデクス(0起点)
		を指定してください。
	@param iRessyaCount [in] 
		出力する列車の本数を指定してください。
		INT_MAX は、末尾の列車までを指定したことになります。
	@param bDisplayTsuukaEkiJikoku [in] 
		通過駅の時刻を表示するかどうかを指定してください。
	@param bDisplaySecondEkiJikoku [in] 
		駅時刻の秒単位を出力するかどうかを指定してください。
	@param bDisplayColonEkiJikoku [in] 
		駅時刻にコロンを付けてを出力するかどうかを指定してください。
	@param bDisplayShihatsuShuchakuEkimei [in] 
		始発終着駅名欄を出力するかどうかを指定してください。
	@param bDisplayParentSyubetsu [in] 
		親種別を有効にしてを出力するかどうかを指定してください。
	@param bDisplayRessyamei [in] 
		列車名・号数を出力するかどうかを指定してください。
	@param iEnableOperation [in] 
		運用機能の状態を指定してください。
	@param pCdCsvDocument [out]
		この関数はこの CdCsvDocument オブジェクトに、
		時刻表データを書き込みます。
	@return
		成功したら 0 以上、エラーなら負の数です。
		-	-1 ;	//	iDiaIndex が不正です。
		-	-2 ;	//	iRessyaIndex が不正です。
		-	-3 ;	//	iRessyaCount が不正です。
	*/
	int encode( 
		const CentDedRosen& aCentDedRosen , 
		int iDiaIndex , 
		ERessyahoukou eRessyahoukou ,
		int iRessyaIndex , int iRessyaCount ,
		const bool bDisplayTsuukaEkiJikoku,
		const bool bDisplaySecondEkiJikoku,
		const bool bDisplayColonEkiJikoku,
		const bool bDisplayShihatsuShuchakuEkimei,
		const bool bDisplayParentSyubetsu,
		const bool bDisplayRessyamei,
		const int iEnableOperation,
		const int iSecondRoundChaku,
		const int iSecondRoundHatsu,
		const bool bDisplay2400,
		const int iOperationNumberRows,
		CdCsvDocument* pCdCsvDocument ) ;

	///@}
};
} //namespace ConvJikokuhyouCsv

#endif //CconvJikokuhyouCustomizeCsv_h

