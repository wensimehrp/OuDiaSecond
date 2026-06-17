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
#if !defined(AFX_CDLGOPERATIONTABLECSVEXPORT_H__A3C4DA85_B17C_473C_9692_578C72A74830__INCLUDED_)
#define AFX_CDLGOPERATIONTABLECSVEXPORT_H__A3C4DA85_B17C_473C_9692_578C72A74830__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CDlgOuJikokuhyouCsvExport.h : ヘッダー ファイル
// $Id: CDlgOuJikokuhyouCsvExport.h 261 2016-01-23 03:59:53Z okm $
/** @file */

namespace ViewAllOperationTable{

#include "..\entDed\CentDedRosen.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgOperationTableExport ダイアログ
/**
@brief
	時刻表ビューの内容をCSVファイルにエクスポートするダイアログです。
*/
class CDlgOperationTableCsvExport : public CDialog
{
private:
	// ********************************
	///@name 関連
	// ********************************
	///@{
	/**
		時刻データを保持している CentDedRosen オブジェクトへの関連です。

		このオブジェクトの破棄の責務は、クラスユーザーにあります。
		このオブジェクトは、this が生存している間は
		生存しなくてはなりません。
	*/
	const CentDedRosen* m_pCentDedRosen ;

	/**
		抽出対象となるダイヤオブジェクト
	*/
	const CentDedDia* m_pCentDedDia;


	const CdDedDispProp m_aCdDedDispProp;
	///@}
	// ********************************
	///@name 属性
	// ********************************
	///@{
	/**
		運用一覧でフォーカスがある運用番号。
		コンストラクタで決まります。
	*/
	tstring  m_strOperationNumber ;

	/**
		最後にユーザーが入力したCSVファイル名
	*/
	CString	m_strCsvFilename ;

	/**
		駅時刻の秒単位を表示するかどうか。
		コンストラクタで決まります。
	*/
	bool m_bDisplaySecondEkiJikoku;

	/**
	駅時刻をコロン付きで表示するかどうか。
	コンストラクタで決まります。
	*/
	bool m_bDisplayColonEkiJikoku;

	/**
	列車の表示を親種別で行うか否かの指定
	コンストラクタで決まります。
	*/
	bool m_bDisplayParentSyubetsu;

	/**
	上り列車の始発駅を左側にして描写するの初期値
	コンストラクタで決まります。
	*/
	//bool m_bDisplayNoboriLeftToRight;

	bool m_bCompareBottom;
	///@}
	// ********************************
	///@name 操作
	// ********************************
	///@{
	///@}
// ----------------------------------------------------------------
// コンストラクション
	/**
		strOperationNumber:
			運用番号エディットにデフォルトで表示する運番
		iStationIndex:
			駅選択コンボボタンのデフォルト値
			eOperationSortが入区駅・入区時刻順の場合は、運用一覧でのフォーカス列の入区駅、それ以外の場合は出区駅
		eOperationSort
			並び順コンボボタンのデフォルト値
		bCompareBottom
			運用番号の並び替えルール、このダイアログ中では変更できません

	*/
public:
	CDlgOperationTableCsvExport(
		const CentDedRosen* pCentDedRosen ,
		const CentDedDia* pCentDedDia,
		const CdDedDispProp aCdDedDispProp,
		tstring  strOperationNumber,
		int iStationIndex,
		bool bDisplaySecondEkiJikoku,
		bool bDisplayColonEkiJikoku,
		bool bDisplayParentSyubetsu,
		bool bDisplayNoboriLeftToRight,
		bool bCompareBottom,
		CWndDcdGridAllOperationTable::EOperationSort eOperationSort,
		bool bDisplayExtensionOperationTable,
		bool bDisplayTrackName,
		bool bDisplayTsuukaEkiJikoku,
		CWnd* pParent = NULL);   // 標準のコンストラクタ

private:
	/**
		運用番号を数字の塊と数字以外の塊に分割します。
	*/
	void splitOperationNumber(
		const tstring strOperationNumberIn,
		vector<int>& iOperationNumber,
		vector<tstring>& strOperationNumberOut)const;

	/**
		二つの運用番号の並び順を返します。
	*/
	bool SortOperationNumber(
		const tstring strOperationNumber1,
		const tstring strOperationNumber2);

	bool SortOperation(
		const tstring strOperationNumber1,
		const int& iEkiIndex1,
		const int& iOuterIndex1,
		const CdDedJikoku& Jikoku1,
		const tstring strOperationNumber2,
		const int& iEkiIndex2,
		const int& iOuterIndex2,
		const CdDedJikoku& Jikoku2,
		const CdDedJikoku& KitenJikoku);


	bool CheckSatisfyConditions(
		const tstring& strOperationNumber,
		list< OperationTableContent> ListOperationTableContent,
		const deque<int>& iEkiIndexGroup);

// ダイアログ データ
	//{{AFX_DATA(CDlgOuJikokuhyouCsvExport)
	enum { IDD = IDD_OperationTable_CsvExport };
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDlgOuJikokuhyouCsvExport)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CDlgOuJikokuhyouCsvExport)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
  	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_iRadioOperationTarget;
	CString m_strOperationNumberInput;
	int m_iTypeOfSearch;
	int m_iStationIndex;
	int m_iInOrOut;
	int m_iOperationOrder;
	int m_iIncludeOuterTerminal;
	int m_iNoboriLeftToRight;
	int m_iExtensionOperationTable;
	int m_iTrackName;
	int m_iTsuukaEkiJikoku;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

} //namespace ViewAllOperationTable

#endif // !defined(AFX_CDLGOPERATIONTABLECSVEXPORT_H__A3C4DA85_B17C_473C_9692_578C72A74830__INCLUDED_)
