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
#if !defined(AFX_CDLGDIAPROP_H__04DF9123_8977_4FE4_A5BA_765D423F9E39__INCLUDED_)
#define AFX_CDLGDIAPROP_H__04DF9123_8977_4FE4_A5BA_765D423F9E39__INCLUDED_
/** @file */
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CDlgDiaProp.h : ヘッダー ファイル
//


namespace ViewRosen{

/////////////////////////////////////////////////////////////////////////////
// CDlgDiaProp ダイアログ

/**
 * @brief
 *	『ダイヤのプロパティ』ダイアログです。
 */
class CDlgDiaProp : public CDialog
{
// ********************************
///@name 属性
// ********************************
///@{
 private:
	/**
	 *	ダイヤの名称です。
	 *	（例） "平日" など
	 *
	 *	コンストラクタで設定されます。
	 *	this はこの値を、ダイアログ起動時にコントロールに設定します。
	 *	また、ダイアログ終了時に、コントロールの内容をこの値に設定します。
	 */
	 tstring	m_strName ;

	/**
		時刻表画面における基本背景色のIndexです
		0-3
	*/
	 int m_iJikokuhyouMainBackColorIndex;

	 /**
	 時刻表画面における補助背景色のIndexです
		0-3
	 */
	 int m_iJikokuhyouSubBackColorIndex;

	 /**
	 時刻表画面における背景色パターンのIndexです
		0-4
	 */
	 int m_iJikokuhyouBackPatternIndex;

	 /**
	 既定の背景色。

	 コンストラクタで決まります。
	 */
	 CdColorProp m_ColorpropJikokuhyouColor[CentDedDia::JIKOKUHYOUCOLOR_COUNT];

	 /**
	 色のサンプルを描画する DcDraw オブジェクト
	 OnInitDialog() で生成・OnDestroy() で破棄します。
	 */
	 CDcdRectangle*	m_pdcdrawMainBackColor;
	 /**
	 色のサンプルを描画する DcDraw オブジェクト
	 OnInitDialog() で生成・OnDestroy() で破棄します。
	 */
	 CDcdRectangle*	m_pdcdrawSubBackColor;

	 /**
		 パターンダイヤプレビュー機能が有効か否か

	 */
	 //bool m_bPatternDiagramPreviewEnable;

	 /**
		 パターンダイヤプレビュー機能における、1サイクルの秒数。
		 最小は60、最大は10800(3時間)とします。
	 */
	 int m_iPatternDiagramPreviewCycleSecond;
///@}

// ********************************
//	CDlgDiaProp
// ********************************
protected:
	/**
	UIの状態を更新する(例:コントロールの有効・無効、入力値の正規化)
	*/
	virtual void updateUIState();
 public:
	// ********************************
	///@name 属性
	// ********************************
	///@{
	 tstring	getName(){	return m_strName ;};

	 int getMainBackColorIndex()const { return m_iJikokuhyouMainBackColorIndex; };

	 int getSubBackColorIndex()const { return m_iJikokuhyouSubBackColorIndex; };

	 int getBackPatternIndex()const { return m_iJikokuhyouBackPatternIndex; };

	 bool getPatternDiagramPreviewEnable()const { return m_iEDIT_PatternDiagramPreviewEnable; };

	 int getPatternDiagramPreviewCycleSecond()const { return m_iPatternDiagramPreviewCycleSecond; };

	 //int getPatternDiagramPreviewCycleMinute()const { return m_iPatternDiagramPreviewCycleMinute; };
	///@}

// ----------------------------------------------------------------
// コンストラクション
public:
	CDlgDiaProp(
		const tstring& strName ,
		const int& iJikokuhyouMainBackColorIndex,
		const int& iJikokuhyouSubBackColorIndex,
		const int& iJikokuhyouBackPatternIndex,
		const bool& bPatternDiagramPreviewEnable,
		const int& iPatternDiagramPreviewCycleSecond,
		const CdDedDispProp&	aCdDedDispProp,
		CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CDlgDiaProp)
	enum { IDD = IDD_DiaProp };
	CString	m_strEDIT_Name;
	int m_iEDIT_PatternDiagramPreviewEnable;
	int m_iEDIT_PatternDiagramPreviewCycleSecond;
	int m_iEDIT_PatternDiagramPreviewCycleMinute;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDlgDiaProp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CDlgDiaProp)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeComboJikokuhyoumainbackcolorindex();
	afx_msg void OnCbnSelchangeComboJikokuhyousubbackcolorindex();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。
} //namespace ViewRosen

#endif // !defined(AFX_CDLGDIAPROP_H__04DF9123_8977_4FE4_A5BA_765D423F9E39__INCLUDED_)
