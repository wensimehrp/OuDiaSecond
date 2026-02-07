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
// $Id: CconvOperationTableCsv.h
// ****************************************************************
#ifndef  CconvOperationTableCsv_h
#define  CconvOperationTableCsv_h
/** @file */
#include "..¥DedRosenFileData¥CDedRosenFileData.h"
#include "Str¥CsvDocument¥CdCsvDocument.h"
#include "..¥entDed¥CdDedRessyaProperty.h"
#include "..¥entDed¥entDed.h"

namespace ViewOperationTable{
using namespace OuLib::Str::CsvDocument;
using namespace entDed;

/**
@brief
	時刻表形式CSVファイルとの間のデータ変換を行います。

	CentDedRosenと、時刻表形式のCSVファイルを生成します。

	反対に、CentDedRosenに、時刻表形式のCSVファイルの内容を取り込む
	こともできます。
*/
class CconvOperationTableCsv
{
private:
	/// CSV上の固定文字列「列車番号」
	tstring m_nameRessyabangou;
	/// CSV上の固定文字列「列車種別」
	tstring m_nameRessyasyubetsu;
	/// CSV上の固定文字列「列車名」
	tstring m_nameRessyamei;
	/// CSV上の固定文字列「号数」
	tstring m_nameGousuu;
	/// CSV上の固定文字列「号」
	tstring m_nameGou;
	/// CSV上の固定文字列「駅名」
	tstring m_nameEkimei;
	/// CSV上の固定文字列「駅時刻」
	tstring m_nameEkiJikoku;
	/// CSV上の固定文字列「→」
	tstring m_nameKudariArrow;
	/// CSV上の固定文字列「←」
	tstring m_nameNoboriArrow;

protected:
	// --------------------------------
	///@name	駅時刻セルの文字列の解釈
	// --------------------------------
	///@{
	/**
	@return
	駅時刻を表示形式に変換するオブジェクトを返します。
	@note static メンバ関数にすることができます。
	*/
	const CdDedJikoku::CConv	getCdDedJikokuConv()const;

	/**
		駅扱と時刻をもとに、時刻をCSV向けに文字列化します。
		
	@param aCdDedJikoku [in]
		時刻を指定してください。
		
		eEkiatsukai が
		CentDedEkiJikoku::Ekiatsukai_None,
		CentDedEkiJikoku::Ekiatsukai_Keiyunasi 
		である場合は、aCdDedJikoku は評価されません。
		
	@param bDisplaySecondEkiJikoku [in] 
		駅時刻の秒単位を出力するかどうかを指定してください。
	@param bDisplayColonEkiJikoku [in] 
		時刻をコロン付きで出力するかどうかを指定してください。
	@return
		変換された文字列を返します。
	*/
	tstring encode_Ekijikoku( 
		const CdDedJikoku& aCdDedJikoku ,
		const bool bDisplaySecondEkiJikoku,
		const bool bDisplayColonEkiJikoku) ;

	///@}
	// --------------------------------
	///@name encode() の下請関数	
	// --------------------------------
	///@{


	///@}
	// --------------------------------
	///@name decode() の下請関数	
	// --------------------------------
	///@{



	///@}

	bool m_bDisplaySecondEkiJikoku;
	bool m_bDisplayColonEkiJikoku;
	int m_iSecondRoundChaku;
	int m_iSecondRoundHatsu;
	bool m_bDisplay2400;

public:
	// ********************************
	//	コンストラクタ
	// ********************************
	CconvOperationTableCsv(
		const tstring& nameRessyabangou ,
		const tstring& nameRessyasyubetsu ,
		const tstring& nameRessyamei ,
		const tstring& nameGousuu ,
		const tstring& nameGou ,
		const tstring& nameEkimei,
		const tstring& nameEkiJikoku,
		const tstring& nameKudariArrow,
		const tstring& nameNoboriArrow) ;



public:
	// ********************************
	///@name	CconvOperationTableCsv
	// ********************************
	///@{
	/**
		指定の路線ファイルデータ・ダイヤ・列車方向の
		時刻表を、CSVドキュメントに出力します。

		*pCdCsvDocument がそれまで保持していたデータは破棄します。
	@param aCentDedRosen [in]
		路線を指定してください。
	@param aCentDedDia [in]
		ダイヤを指定してください。
	@param strOperationNumberCont [in]
		出力対象となる運用番号を含む配列を指定してください


	@param bDisplaySecondEkiJikoku [in] 
		駅時刻の秒単位を出力するかどうかを指定してください。
	@param bDisplayColonEkiJikoku [in] 
		駅時刻をコロン付きで出力するかどうかを指定してください。
	@param pCdCsvDocument [out]
		この関数はこの CdCsvDocument オブジェクトに、
		時刻表データを書き込みます。
	@return
		成功したら 0 以上、エラーなら負の数です。
	*/
	int encode( 
		const CentDedRosen& aCentDedRosen ,
		const CentDedDia& aCentDedDia,
		const CdDedDispProp& aCdDedDispProp,
		const vector<tstring>& strOperationNumberCont,
		const bool bDisplayExtensionOperationTable,
		const bool bDisplaySecondEkiJikoku,
		const bool bDisplayColonEkiJikoku,
		const bool bDisplayParentSyubetsu,
		const bool bDisplayNoboriLeftToRight,
		const bool bDisplayTrackName,
		const bool bDisplayTsuukaEkiJikoku,
		CdCsvDocument* pCdCsvDocument ) ;
	
	///@}
};
} //namespace ConvJikokuhyouCsv

#endif //CconvJikokuhyouCsv_h

