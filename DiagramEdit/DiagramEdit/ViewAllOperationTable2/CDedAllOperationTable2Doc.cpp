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
// CDedAllOperationTable2Doc.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "..\DiagramEdit.h"
#include "CDedAllOperationTable2Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace ViewAllOperationTable2 {

/////////////////////////////////////////////////////////////////////////////
// CDedAllOperationTable2Doc
// ********************************
//@name CDocument
// ********************************
void CDedAllOperationTable2Doc::SetTitle( LPCTSTR lpszTitle )
{
	/*
	 *	このドキュメントが生成されたときに呼び出されます。
	 *
	 *	strDocument= "<ダイヤ名>"
	 */
	m_strDiaName = lpszTitle ;
	
	// --------------------------------
	//	タイトル文字列の作成
	// --------------------------------
	{
		CString	strDiamei =m_strDiaName.c_str() ;
		CString	strAllOperationTable;
		strAllOperationTable.LoadString(IDS_WORD_ALLOPERATIONTABLE2) ;

		strDiamei += " " ;
		strDiamei += strAllOperationTable;
		super::SetTitle( strDiamei ) ;
	}
}
int CDedAllOperationTable2Doc::getDiaIndex()
{
	return ( getCDiagramEditDoc()->getCDedRosenFileData()->
		getCentDedRosen()->getCentDedDiaCont()->
		findCentDedDiaByName( getDiaName() ) ) ;
}


// ----------------------------------------------------------------
IMPLEMENT_DYNCREATE(CDedAllOperationTable2Doc, CHidemdiSubDoc)

CDedAllOperationTable2Doc::CDedAllOperationTable2Doc()
{
}

BOOL CDedAllOperationTable2Doc::OnNewDocument()
{
	if (!CHidemdiSubDoc::OnNewDocument())
		return FALSE;
	return TRUE;
}

CDedAllOperationTable2Doc::~CDedAllOperationTable2Doc()
{
}


BEGIN_MESSAGE_MAP(CDedAllOperationTable2Doc, CHidemdiSubDoc)
	//{{AFX_MSG_MAP(CDedAllOperationTable2Doc)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDedAllOperationTable2Doc 診断

#ifdef _DEBUG
void CDedAllOperationTable2Doc::AssertValid() const
{
	CHidemdiSubDoc::AssertValid();
}

void CDedAllOperationTable2Doc::Dump(CDumpContext& dc) const
{
	CHidemdiSubDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDedAllOperationTable2Doc シリアライズ

void CDedAllOperationTable2Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: この位置に保存用のコードを追加してください
	}
	else
	{
		// TODO: この位置に読み込み用のコードを追加してください
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDedAllOperationTable2Doc コマンド

} // namespace ViewAllOperationTable2
