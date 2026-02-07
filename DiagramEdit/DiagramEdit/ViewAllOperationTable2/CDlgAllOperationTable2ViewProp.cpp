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
// CDlgAllOperationTable2ViewProp.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "str/strToInt.h"
#include "str/CStrCharSizeMb.h"
#include "Str\strToWstr.h"

#include "..\diagramedit.h"
#include "..\entDed\entDed.h"
#include "DcdCd/Pos/CLineFunc.h"
#include "CDlgAllOperationTable2ViewProp.h"

using namespace std ;


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace ViewAllOperationTable2 {

/** 時刻の書式を保持します。 */
const CdDedJikoku::CConv	g_CdDedJikokuConv(
	false ,		//	NoColon 
	CdDedJikoku::CConv::EHour_Zero ,	// 時が 00 から 09 の場合、10の位を "0" とします
	CdDedJikoku::CConv::ESecond_NoSecond 	// 秒を常に出力しません。 
	) ;

/** 時間の書式を保持します。 */
const CdDedJikan::CConv	g_CdDedJikanConv(
	true ,		//	NoSecond
	false ,		//	PlusDisplay 
	false ) ;	//	PlusToSpace 

/////////////////////////////////////////////////////////////////////////////
// CDlgAllOperationTable2ViewProp ダイアログ


CDlgAllOperationTable2ViewProp::CDlgAllOperationTable2ViewProp(
		const CdDcdZone&	zonexyCentDedDiaZone_Dgr ,
		BOOL bEnableYokojiku ,
		const CdDcdZoneXy&	zonexyCWndDiagramZone_Dgr ,
		int idxVlineMode ,
		const CDedAllOperationTable2View::EOperationSort eOperationSort,
		const bool bCompareBottom,
		CWnd* pParent )
	: CDialog(CDlgAllOperationTable2ViewProp::IDD, pParent)
	, m_zonexyCentDedDiaZone_Dgr( zonexyCentDedDiaZone_Dgr )
	, m_bEnableYokojiku(bEnableYokojiku)
	, m_zonexyCWndDiagramZone_Dgr( zonexyCWndDiagramZone_Dgr )
	, m_idxVlineMode( idxVlineMode )
	, m_eOperationSort(eOperationSort)
	, m_iEDIT_CompareBottom(bCompareBottom)
{
	//{{AFX_DATA_INIT(CDlgAllOperationTable2ViewProp)
	m_strEDIT_YokojikuPos = _T("");
	m_strEDIT_YokojikuSize = _T("");
	m_iCOMBO_Jikanmemori = -1;
	//}}AFX_DATA_INIT

	if ( m_bEnableYokojiku )
	{
		m_strEDIT_YokojikuPos = g_CdDedJikokuConv.encode( CdDedJikoku( m_zonexyCWndDiagramZone_Dgr.getPos().getX()) ).c_str() ;
		m_strEDIT_YokojikuSize = g_CdDedJikanConv.encode( CdDedJikan( m_zonexyCWndDiagramZone_Dgr.getSize().getX() ) ).c_str() ;
	}
	m_iCOMBO_Jikanmemori = m_idxVlineMode ;
	m_iRADIO_OPERATIONSORT = (int)m_eOperationSort;


}


void CDlgAllOperationTable2ViewProp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAllOperationTable2ViewProp)
	DDX_Text(pDX, IDC_EDIT_YokojikuPos, m_strEDIT_YokojikuPos);
	DDX_Text(pDX, IDC_EDIT_YokojikuSize, m_strEDIT_YokojikuSize);
	DDX_CBIndex(pDX, IDC_COMBO_Jikanmemori, m_iCOMBO_Jikanmemori);
	DDX_Radio(pDX, IDC_RADIO_OPERATIONSORT_0, m_iRADIO_OPERATIONSORT);
	DDX_Check(pDX, IDC_CHECK_CompareBottom, m_iEDIT_CompareBottom);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAllOperationTable2ViewProp, CDialog)
	//{{AFX_MSG_MAP(CDlgAllOperationTable2ViewProp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAllOperationTable2ViewProp メッセージ ハンドラ

void CDlgAllOperationTable2ViewProp::OnOK() 
{
	int iRv = 0 ;
	
	if ( !UpdateData() )
	{
		return ;
	}
	
	if ( m_bEnableYokojiku )	//横軸のエディットボックスを有効
	{
		CdDedJikoku	jikokuYokojikuPos ;
		CdDedJikan	jikanYokojikuSize ;


		if ( iRv >= 0 )
		{
			if ( jikokuYokojikuPos.decode( 
				tstringOf(CStrCharSizeMb::strToSingleByte( stringOf((LPCTSTR)m_strEDIT_YokojikuPos) ) )
				) < 0 )
			{
				iRv = -1 ;	//	横軸表示範囲の起点が、時刻として解釈できません。
			}
		}
		if ( iRv >= 0 )
		{
			if ( jikanYokojikuSize.decode( 
				tstringOf(CStrCharSizeMb::strToSingleByte(stringOf((LPCTSTR)m_strEDIT_YokojikuSize)) )
				) < 0 )
			{
				iRv = -2 ;	//	横軸表示範囲が、時間として解釈できません。
			}
			else if ( jikanYokojikuSize.getTotalSeconds() > 24*60*60 )
			{
				iRv = -3 ;	//	横軸表示範囲が大きすぎます。24時間以下の値を設定してください。
			}
			else if ( jikanYokojikuSize.getTotalSeconds() <= 0 )
			{
				iRv = -6 ;	//	横軸表示範囲が小さすぎます。1分以上の値を設定してください。
			}
		}
		if ( iRv >= 0 )
		{
			CdDcdZone	zoneX( 
				jikokuYokojikuPos.getTotalSeconds() ,
				jikanYokojikuSize.getTotalSeconds() ) ;
			if ( zoneX.getPos() < m_zonexyCentDedDiaZone_Dgr.getPos() )
			{
				//	横軸表示範囲の起点が、
				//	『ダイヤグラムエンティティ座標系』の起点より小さいなら、
				//	24時間を加算
				zoneX.setPos( zoneX.getPos() + 24*60*60 ) ;
			}
			if ( m_zonexyCentDedDiaZone_Dgr.getEndPos() < zoneX.getEndPos() )
			{
				iRv = -4 ;	//	横軸表示範囲が、ダイヤグラムの起点時刻を越えています。
							//	%s を越えないように設定してください。
			}
			else
			{
				m_zonexyCWndDiagramZone_Dgr.setX( zoneX ) ;
			}
			
		}	
		
	}
	if ( iRv >= 0 )
	{
		m_idxVlineMode = m_iCOMBO_Jikanmemori ;
		if ( m_idxVlineMode < 0 ){
			m_idxVlineMode = 0 ;
		}
	}
	// --------------------------------
	if (iRv >= 0)
	{
		switch (m_iRADIO_OPERATIONSORT)
		{
		case 0:
			m_eOperationSort = CDedAllOperationTable2View::EOperationSort_OperationNumber;
			break;
		case 1:
			m_eOperationSort = CDedAllOperationTable2View::EOperationSort_OutEki;
			break;
		case 2:
			m_eOperationSort = CDedAllOperationTable2View::EOperationSort_OutJikoku;
			break;
		case 3:
			m_eOperationSort = CDedAllOperationTable2View::EOperationSort_InEki;
			break;
		case 4:
			m_eOperationSort = CDedAllOperationTable2View::EOperationSort_InJikoku;
			break;
		}

	}
		//iRv = 
		//		-1 ;	//	横軸表示範囲の起点が、時刻として解釈できません。
		//		-2 ;	//	横軸表示範囲が、時間として解釈できません。
		//		-3 ;	//	横軸表示範囲が大きすぎます。24時間以下の値を設定してください。
		//		-4 ;	//	横軸表示範囲が、ダイヤグラムの起点時刻を越えています。
		//				//	%s を越えないように設定してください。
		//		-6 ;	//	横軸表示範囲が小さすぎます。1分以上の値を設定してください。
		//		-8 ;	//	縦軸表示範囲の上端が範囲内にありません
		//				//	0%以上100%以下の値を指定してください。
		//		-9 ;	//	縦軸表示範囲の幅が範囲内にありません
		//				//	1%以上1000%以下の値を指定してください。
	if ( iRv >= 0 )
	{
		CDialog::OnOK();
	}
	else
	{
		CString	strError ;
		switch( iRv ){
		 case -1 :	
			{
				GetDlgItem(IDC_ERR_1)->GetWindowText( strError ) ;
			}
			break ;
		 case -2 :	
			{
				GetDlgItem(IDC_ERR_2)->GetWindowText( strError ) ;
			}
			break ;
		 case -3 :	
			{
				GetDlgItem(IDC_ERR_3)->GetWindowText( strError ) ;
			}
			break ;
		 case -4 :	
			{
				tstring	strJikoku = g_CdDedJikokuConv.encode( CdDedJikoku( m_zonexyCentDedDiaZone_Dgr.getPos() ) ) ;
				CString	strFmt ;
				GetDlgItem(IDC_ERR_4)->GetWindowText( strFmt ) ;
				strError.Format( strFmt , strJikoku.c_str() ) ;
			}
			break ;
		 case -6 :	
			{
				GetDlgItem(IDC_ERR_6)->GetWindowText( strError ) ;
			}
			break ;
		 case -8 :	
			{
				GetDlgItem(IDC_ERR_8)->GetWindowText( strError ) ;
			}
			break ;
		 case -9 :	
			{
				GetDlgItem(IDC_ERR_9)->GetWindowText( strError ) ;
			}
			break ;
		 default :	
			{
				CString	strFmt ;
				GetDlgItem(IDC_ERR_X)->GetWindowText( strFmt ) ;
				strError.Format( strFmt , iRv ) ;
			}
			break ;
		}
		MessageBox( strError , NULL , MB_ICONEXCLAMATION | MB_OK ) ;
	}

}

BOOL CDlgAllOperationTable2ViewProp::OnInitDialog() 
{

	// コンボボックス
	{
		CComboBox*	pCComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_Jikanmemori);

		tstring strTemp = _T("1分目");
		pCComboBox->AddString(strTemp.c_str());
		strTemp = _T("2分目");
		pCComboBox->AddString(strTemp.c_str());
		strTemp = _T("5分目");
		pCComboBox->AddString(strTemp.c_str());
		strTemp = _T("10分目");
		pCComboBox->AddString(strTemp.c_str());
		strTemp = _T("15分目");
		pCComboBox->AddString(strTemp.c_str());
		strTemp = _T("20分目");
		pCComboBox->AddString(strTemp.c_str());
		strTemp = _T("30分目");
		pCComboBox->AddString(strTemp.c_str());
		strTemp = _T("60分目");
		pCComboBox->AddString(strTemp.c_str());
		//1分目;2分目;5分目;10分目;15分目;20分目;30分目;60分目;
	}

	CDialog::OnInitDialog();
	
	if( !m_bEnableYokojiku )
	{
		GetDlgItem(IDC_EDIT_YokojikuPos)->EnableWindow(FALSE) ;
		GetDlgItem(IDC_EDIT_YokojikuSize)->EnableWindow(FALSE) ;
	}

	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}
} //namespace ViewAllOperationTable2
