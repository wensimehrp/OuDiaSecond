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
// DiagramEdit.cpp : アプリケーション用クラスの機能定義を行います。
//$Id: DiagramEdit.cpp 418 2017-01-21 05:00:05Z okm $ 
/** @file */
#include "stdafx.h"


#include "str¥strToInt.h"
#include "str¥strToWstr.h"
#include "str¥tstring.h"
#include "str¥strprintf.h"
#include "dir¥Directries.h"
#include "MfcUtil¥MfcUtil.h"

#include "DiagramEdit.h"
#include "resource.h"
#include "CAboutBoxGpl.h"

#include "CDiagramEditDoc.h"
#include "CDiagramEditDoctmpl.h"

#include "entDed¥CdDedJikoku.h"
#include "entDed¥CdDedJikan.h"

#include "ViewEki¥CEkiDoc.h"
#include "ViewEki¥CEkiView.h"
#include "ViewRessyasyubetsu¥CRessyasyubetsuDoc.h"
#include "ViewRessyasyubetsu¥CRessyasyubetsuView.h"
#include "ViewJikokuhyou¥CJikokuhyouDoc.h"
#include "ViewJikokuhyou¥CJikokuhyouView.h"
#include "ViewDiagram¥CDedDiagramDoc.h"
#include "ViewDiagram¥CDedDiagramView.h"
#include "ViewComment¥CDedCommentView.h"
//#include "ViewEkiTrack2¥CEkiTrack2Doc.h"
//#include "ViewEkiTrack2¥CEkiTrack2View.h"
#include "ViewOperationTable¥COperationTableDoc.h"
#include "ViewOperationTable¥COperationTableView.h"
#include "ViewAllOperationTable¥CAllOperationTableDoc.h"
#include "ViewAllOperationTable¥CAllOperationTableView.h"
#include "ViewEkiJikokuhyou¥CEkiJikokuhyouDoc.h"
#include "ViewEkiJikokuhyou¥CEkiJikokuhyouView.h"
#include "ViewInOutLinkCodeList¥CInOutLinkCodeListDoc.h"
#include "ViewInOutLinkCodeList¥CInOutLinkCodeListView.h"
#include "ViewCrossingCheck¥CCrossingCheckDoc.h"
#include "ViewCrossingCheck¥CCrossingCheckView.h"

#include "Print¥CDlgPrintPageProp.h"
#include "ConvJikokuhyouCsv¥CconvJikokuhyouCsv.h"
#include "ViewOperationTable¥CconvOperationTableCsv.h"

using namespace std ;
using namespace OuMfc;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CDiagramEditApp
const TCHAR nameSection[] = _T( "AppProp" ) ;
const TCHAR namePrintPageProp[] = _T( "PrintPageProp" ) ;
const TCHAR nameLogLevel[] = _T( "LogLevel" ) ;

	// ================================
	//	下請関数
	// ================================
void CDiagramEditApp::readVersionResource( 
		tstring* pstrFileVersion , 
		tstring* pstrLegalCopyright )
{

	vector<TCHAR>	szInfo ;
	{
		TCHAR	szExeName[MAX_PATH] ;
		GetModuleFileName( NULL , szExeName , 
			sizeof(szExeName)/sizeof(szExeName[0]) ) ;
		DWORD	dwValue = 0 ;
		DWORD dwSize = GetFileVersionInfoSize( szExeName , &dwValue ) ;
		if ( dwSize > 0 )
		{ 
			szInfo.resize( dwSize ) ; 
			GetFileVersionInfo( szExeName , NULL , dwSize , &szInfo[0] ) ;
		}
	}
	tstring strFileVersion ;
	if ( szInfo.size() > 0 )
	{
		WORD	awVersion[4] = { 0 , 0 , 0 , 0 } ;
		VS_FIXEDFILEINFO*	pVS_FIXEDFILEINFO = NULL ;
		UINT uiLen = 0 ;
		VerQueryValue( &szInfo[0] , _T( "¥¥" ) , 
			(void**)&pVS_FIXEDFILEINFO , 
			&uiLen ) ;
		awVersion[0] = HIWORD( pVS_FIXEDFILEINFO->dwFileVersionMS ) ;
		awVersion[1] = LOWORD( pVS_FIXEDFILEINFO->dwFileVersionMS ) ;
		awVersion[2] = HIWORD( pVS_FIXEDFILEINFO->dwFileVersionLS ) ;
		awVersion[3] = LOWORD( pVS_FIXEDFILEINFO->dwFileVersionLS ) ;

		//	バージョンを文字列化
		int idxLength = 0 ;
		for ( idxLength = sizeof(awVersion) / sizeof(awVersion[0]) ;
			idxLength > 2 && awVersion[idxLength-1] == 0 ;
			idxLength -- ){}
		//idxLength = awVersion[] から、末尾の0を除いた要素数
		//	バージョンが 1.2.3.4 なら、 idxLength = 4
		//	バージョンが 1.2.3.0 なら、 idxLength = 3
		for ( int idx = 0 ; idx < idxLength ; idx ++ )
		{
			if ( !strFileVersion.empty() )
			{
				strFileVersion += _T(".") ;
			}

			if ( idx == 0 )
			{
				strFileVersion += strprintf(_T("%d") , awVersion[idx] ) ;
			}
			else
			{
				strFileVersion += strprintf(_T("%02d") , awVersion[idx] ) ;
			}
		}
	}
	tstring strLegalCopyright ;
	if ( szInfo.size() > 0 )
	{
		UINT uiLen = 0 ;
		const TCHAR* lpszLegalCopyright ;
		VerQueryValue( &szInfo[0] , _T( "¥¥StringFileInfo¥¥041104b0¥¥LegalCopyright" ) 
			, (void**)&lpszLegalCopyright , &uiLen ) ; 
		if ( uiLen > 0 )
		{
			strLegalCopyright = lpszLegalCopyright ;
		}
	}
	if ( pstrFileVersion != NULL ){	*pstrFileVersion = strFileVersion ;}
	if ( pstrLegalCopyright != NULL ){ *pstrLegalCopyright = strLegalCopyright ;}

}
	// ********************************
	//@name CDiagramEditApp-属性
	// ********************************
tstring CDiagramEditApp::getProgramVer()const 
{
	tstring strFileVersion ;
	readVersionResource( &strFileVersion , NULL  ) ; 
	return strFileVersion ;
}


// ********************************
//	CDiagramEditApp
// ********************************
CMainFrame*	CDiagramEditApp::getCMainFrame() 
{
	return ( (CMainFrame*)m_pMainWnd ) ;
}

CDlgRosenView*	CDiagramEditApp::getCDlgRosenView() 
{
	return ( getCMainFrame()->getCDlgRosenView() ) ;
}

CEkiDoc* CDiagramEditApp::openCEkiDoc( CEkiView** ppEkiView )
{
	if ( ppEkiView != NULL )
	{
		*ppEkiView = NULL ;
	}
	// --------------------------------
	CEkiDoc* pEkiDoc = (CEkiDoc*)m_pdoctmplEki->OpenDocumentFile( NULL ) ;

	if ( pEkiDoc != NULL && ppEkiView != NULL )
	{

		POSITION aPOSITION = pEkiDoc->GetFirstViewPosition() ;
		if ( aPOSITION != NULL ){
			*ppEkiView = (CEkiView*)pEkiDoc->GetNextView( aPOSITION ) ;
		}
	}
	return pEkiDoc ;
}

CRessyasyubetsuDoc* CDiagramEditApp::openCRessyasyubetsuDoc() 
{
	return (CRessyasyubetsuDoc*)m_pdoctmplResssyasyubetsu->OpenDocumentFile( NULL ) ;
}

CJikokuhyouDoc* CDiagramEditApp::openCJikokuhyouDoc( 
	const CentDedDia* pCentDedDia , 
	ERessyahoukou eRessyahoukou ,
	bool bCustomizeDisplayMode,
	CJikokuhyouView** ppJikokuhyouView ) 
{
	int iRv = 0 ;
	CJikokuhyouDoc*	pCJikokuhyouDoc = NULL ;
	if ( ppJikokuhyouView != NULL )
	{
		*ppJikokuhyouView = NULL ;
	}
	// --------------------------------
	if ( iRv >= 0 )
	{
		const CentDedRosen* pCentDedRosen = 
			getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen() ;
		int idx = pCentDedRosen->getCentDedDiaCont()->findCentDedDiaByName( pCentDedDia->getName() ) ;
		if ( idx < 0 )
		{
			iRv = -1 ;	//	pCentDedDia が見つかりません。
		}
	}
	if ( iRv >= 0 )
	{
		CString	strDocument ;
		strDocument.Format(_T("%s¥n%d¥n%d"), pCentDedDia->getName().c_str(),
			(int)eRessyahoukou, bCustomizeDisplayMode ? 1 : 0);
		//strDocument= pCentDedDia に対応する"<ダイヤ名>¥n<列車方向>¥n<カスタマイズ時刻表>"
		
		CDocument*	pCDocument = m_pdoctmplJikokuhyou->OpenDocumentFile( strDocument ) ;
		if ( pCDocument != NULL )
		{
			pCJikokuhyouDoc = (CJikokuhyouDoc*)pCDocument ;
		}
		else
		{
			iRv = -2 ; //	pCentDedDia に対応する時刻表ビューが開けません。
		}
	}
	//pCJikokuhyouDoc = CJikokuhyouDocへのポインタ
	if ( iRv >= 0 && ppJikokuhyouView != NULL )
	{
		POSITION aPOSITION = pCJikokuhyouDoc->GetFirstViewPosition() ;
		if ( aPOSITION != NULL ){
			*ppJikokuhyouView = (CJikokuhyouView*)pCJikokuhyouDoc
				->GetNextView( aPOSITION ) ;
		}
	}

	return ( pCJikokuhyouDoc ) ;
}

CDedDiagramDoc* CDiagramEditApp::openCDedDiagramDoc( const CentDedDia* pCentDedDia )
{
	const CentDedRosen* pCentDedRosen = 
		getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen() ;

	int idx = pCentDedRosen->getCentDedDiaCont()->findCentDedDiaByName( pCentDedDia->getName() ) ;
	if ( idx < 0 ){
		return NULL ;
	}

	CString	strDocument = pCentDedDia->getName().c_str() ;
	CDocument*	pCDocument = m_pdoctmplDiagram->OpenDocumentFile( strDocument ) ;
	
	return ( (CDedDiagramDoc*)pCDocument ) ;

}

CDedCommentDoc* CDiagramEditApp::openCDedCommentDoc() 
{
	return (CDedCommentDoc*)m_pdoctmplComment->OpenDocumentFile( NULL ) ;
}

COperationTableDoc* CDiagramEditApp::openCOperationTableDoc(
	const CentDedDia* pCentDedDia,
	const tstring strOperationNumber)
{
	int iRv = 0;
	COperationTableDoc*	pCOperationTableDoc = NULL;

	if (strOperationNumber.empty())
	{
		return NULL;
	}

	if (pCentDedDia->getcontOperationTableContent().find(strOperationNumber) ==
		pCentDedDia->getcontOperationTableContent().end())
	{
		return NULL;
	}

	CString	strDocument;
	strDocument.Format(_T("%s¥n%s"), pCentDedDia->getName().c_str(),
		strOperationNumber.c_str());
	//strDocument= pCentDedDia に対応する"<ダイヤ名>¥n<運用番号>"

	CDocument*	pCDocument = m_pdoctmplOperationTable->OpenDocumentFile(strDocument);
	return ((COperationTableDoc*)pCDocument);
}

CAllOperationTableDoc* CDiagramEditApp::openCAllOperationTableDoc(
	const CentDedDia* pCentDedDia)
{
	int iRv = 0;
	CAllOperationTableDoc* pCAllOperationTableDoc = NULL;

	if (pCentDedDia->getcontOperationTableContent().empty())
	{
		return NULL;
	}

	CString	strDocument;
	strDocument.Format(_T("%s"), pCentDedDia->getName().c_str());
	//strDocument= pCentDedDia に対応する"<ダイヤ名>"

	CDocument* pCDocument = m_pdoctmplAllOperationTable->OpenDocumentFile(strDocument);
	return ((CAllOperationTableDoc*)pCDocument);
}

CDedAllOperationTable2Doc* CDiagramEditApp::openCDedAllOperationTable2Doc(const CentDedDia* pCentDedDia)
{
	const CentDedRosen* pCentDedRosen =
		getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen();

	int idx = pCentDedRosen->getCentDedDiaCont()->findCentDedDiaByName(pCentDedDia->getName());
	if (idx < 0) {
		return NULL;
	}

	if (pCentDedDia->getcontOperationTableContent().empty())
	{
		return NULL;
	}

	CString	strDocument = pCentDedDia->getName().c_str();
	CDocument* pCDocument = m_pdoctmplAllOperationTable2->OpenDocumentFile(strDocument);

	return ((CDedAllOperationTable2Doc*)pCDocument);

}


CEkiJikokuhyouDoc* CDiagramEditApp::openCEkiJikokuhyouDoc(
	const CentDedDia* pCentDedDia,
	ERessyahoukou eRessyahoukou,
	int iEkiIndex,
	CEkiJikokuhyouView** ppEkiJikokuhyouView)
{
	int iRv = 0;
	CEkiJikokuhyouDoc* pCEkiJikokuhyouDoc = NULL;
	if (ppEkiJikokuhyouView != NULL)
	{
		*ppEkiJikokuhyouView = NULL;
	}
	// --------------------------------
	if (iRv >= 0)
	{
		const CentDedRosen* pCentDedRosen =
			getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen();
		int idx = pCentDedRosen->getCentDedDiaCont()->findCentDedDiaByName(pCentDedDia->getName());
		if (idx < 0)
		{
			iRv = -1;	//	pCentDedDia が見つかりません。
		}
	}
	if (iRv >= 0)
	{
		const CentDedEkiCont* pCentDedEkiCont =
			getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont();
		if (iEkiIndex < 0 || iEkiIndex >= pCentDedEkiCont->size())
		{
			iRv = -2;	//	iEkiIndexが範囲外です。
		}
		if (iRv >= 0)
		{
			const CentDedEki aEki = pCentDedEkiCont->get(iEkiIndex);
			if (eRessyahoukou == ERessyahoukou::Ressyahoukou_Kudari &&
				aEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku)
			{
				iRv = -3; //下りの下り着時刻駅は不可
			}
			else if (eRessyahoukou == ERessyahoukou::Ressyahoukou_Nobori &&
				aEki.getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku)
			{
				iRv = -4; //上りの上り着時刻駅は不可
			}

		}
	}
	if (iRv >= 0)
	{
		const CentDedEkiCont* pCentDedEkiCont =
			getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont();
		const CentDedEki aEki = pCentDedEkiCont->get(iEkiIndex);
		CString	strDocument;
		strDocument.Format(_T("%s¥n%d¥n%d"), pCentDedDia->getName().c_str(),
			(int)eRessyahoukou, aEki.getID());
		//strDocument= pCentDedDia に対応する"<ダイヤ名>¥n<列車方向>¥n<駅ID>"

		CDocument* pCDocument = m_pdoctmplEkiJikokuhyou->OpenDocumentFile(strDocument);
		if (pCDocument != NULL)
		{
			pCEkiJikokuhyouDoc = (CEkiJikokuhyouDoc*)pCDocument;
		}
		else
		{
			iRv = -5; //	pCentDedDia に対応する駅時刻表ビューが開けません。
		}
	}
	//pCEkiJikokuhyouDoc = CEkiJikokuhyouDocへのポインタ
	if (iRv >= 0 && ppEkiJikokuhyouView != NULL)
	{
		POSITION aPOSITION = pCEkiJikokuhyouDoc->GetFirstViewPosition();
		if (aPOSITION != NULL) {
			*ppEkiJikokuhyouView = (CEkiJikokuhyouView*)pCEkiJikokuhyouDoc
				->GetNextView(aPOSITION);
		}
	}

	return (pCEkiJikokuhyouDoc);
}

CEkiJikokuhyouListDoc* CDiagramEditApp::openCEkiJikokuhyouListDoc(
	const CentDedDia* pCentDedDia,
	CEkiJikokuhyouListView** ppEkiJikokuhyouListView)
{
	int iRv = 0;
	CEkiJikokuhyouListDoc* pCEkiJikokuhyouListDoc = NULL;
	if (ppEkiJikokuhyouListView != NULL)
	{
		*ppEkiJikokuhyouListView = NULL;
	}
	// --------------------------------
	if (iRv >= 0)
	{
		const CentDedRosen* pCentDedRosen =
			getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen();
		int idx = pCentDedRosen->getCentDedDiaCont()->findCentDedDiaByName(pCentDedDia->getName());
		if (idx < 0)
		{
			iRv = -1;	//	pCentDedDia が見つかりません。
		}
	}
	if (iRv >= 0)
	{
		CDocument* pCDocument = m_pdoctmplEkiJikokuhyouList->OpenDocumentFile(pCentDedDia->getName().c_str());
		if (pCDocument != NULL)
		{
			pCEkiJikokuhyouListDoc = (CEkiJikokuhyouListDoc*)pCDocument;
		}
		else
		{
			iRv = -5; //	pCentDedDia に対応する駅時刻表ビューが開けません。
		}
	}
	//pCEkiJikokuhyouListDoc = CEkiJikokuhyouListDocへのポインタ
	if (iRv >= 0 && ppEkiJikokuhyouListView != NULL)
	{
		POSITION aPOSITION = pCEkiJikokuhyouListDoc->GetFirstViewPosition();
		if (aPOSITION != NULL) {
			*ppEkiJikokuhyouListView = (CEkiJikokuhyouListView*)pCEkiJikokuhyouListDoc
				->GetNextView(aPOSITION);
		}
	}

	return (pCEkiJikokuhyouListDoc);
}

CInOutLinkCodeListDoc* CDiagramEditApp::openCInOutLinkCodeListDoc(
	const CentDedDia* pCentDedDia)
{
	int iRv = 0;
	CInOutLinkCodeListDoc* pCInOutLinkCodeListDoc = NULL;

	if (pCentDedDia->getcontInOutLinkCodeContent().empty())
	{
		return NULL;
	}

	CString	strDocument;
	strDocument.Format(_T("%s"), pCentDedDia->getName().c_str());
	//strDocument= pCentDedDia に対応する"<ダイヤ名>"

	CDocument* pCDocument = m_pdoctmplInOutLinkCodeList->OpenDocumentFile(strDocument);
	return ((CInOutLinkCodeListDoc*)pCDocument);
}

CCrossingCheckDoc* CDiagramEditApp::openCCrossingCheckDoc(
	const CentDedDia* pCentDedDia,
	int iEkiIndex)
{
	int iRv = 0;
	CCrossingCheckDoc* pCCrossingCheckDoc = NULL;

	if (iRv >= 0)
	{
		const CentDedRosen* pCentDedRosen =
			getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen();
		int idx = pCentDedRosen->getCentDedDiaCont()->findCentDedDiaByName(pCentDedDia->getName());
		if (idx < 0)
		{
			iRv = -1;	//	pCentDedDia が見つかりません。
		}
	}
	if (iRv >= 0)
	{
		const CentDedEkiCont* pCentDedEkiCont =
			getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont();
		if (iEkiIndex < 0 || iEkiIndex >= pCentDedEkiCont->size())
		{
			iRv = -2;	//	iEkiIndexが範囲外です。
		}
	}
	if (iRv >= 0)
	{
		const CentDedEkiCont* pCentDedEkiCont =
			getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont();
		const CentDedEki aEki = pCentDedEkiCont->get(iEkiIndex);
		CString	strDocument;
		strDocument.Format(_T("%s¥n%d¥n%d"), pCentDedDia->getName().c_str(),
			aEki.getID());
		//strDocument= pCentDedDia に対応する"<ダイヤ名>¥n<駅ID>"

		CDocument* pCDocument = m_pdoctmplCrossingCheck->OpenDocumentFile(strDocument);
		if (pCDocument != NULL)
		{
			pCCrossingCheckDoc = (CCrossingCheckDoc*)pCDocument;
		}
		else
		{
			iRv = -5; //	pCentDedDia に対応する駅時刻表ビューが開けません。
		}
	}
	//pCEkiJikokuhyouDoc = CEkiJikokuhyouDocへのポインタ
	//if (iRv >= 0 && ppEkiJikokuhyouView != NULL)
	//{
	//	POSITION aPOSITION = pCEkiJikokuhyouDoc->GetFirstViewPosition();
	//	if (aPOSITION != NULL) {
	//		*ppEkiJikokuhyouView = (CEkiJikokuhyouView*)pCEkiJikokuhyouDoc
	//			->GetNextView(aPOSITION);
	//	}
	//}

	return (pCCrossingCheckDoc);
}

CString CDiagramEditApp::getCFileDialogFilterOpen()
{
	//CString	strWinDIAFilter;
	//strWinDIAFilter.LoadString(IDS_WinDIAFilter);

	//OuDia
	//CString	strOriginalOuDiaFilter ;
	//strOriginalOuDiaFilter.LoadString( IDS_OriginalOuDiaFilter ) ;

	CString	strFilter;
	//OuDiaSecond
	//{
	//	CString	strFilterName;
	//	pRootDoctmpl()->GetDocString(strFilterName, CDocTemplate::filterName);
	//	CString	strExt;
	//	pRootDoctmpl()->GetDocString(strExt, CDocTemplate::filterExt);
	//	strFilter += strFilterName;
	//	strFilter += _T("|*");
	//	strFilter += strExt;
	//	strFilter += _T("|");

	//}
	//OuDia
	//{
	//	strFilter += strOriginalOuDiaFilter ;
	//}
	//OuDiaSecond&OuDia
	{
	//	CString	strFilterName;
	//	pRootDoctmpl()->GetDocString(strFilterName, CDocTemplate::filterName);
	//	CString	strExt;
	//	pRootDoctmpl()->GetDocString(strExt, CDocTemplate::filterExt);
	//	strFilter += strFilterName;
	//	strFilter += _T("|*");
	//	strFilter += strExt;
	//	strFilter += _T("|");
		strFilter = _T("OuDiaSecond ﾌｧｲﾙ (*.oud2;*.oud)|*.oud2;*.oud||");
	}
	//WinDIA
	//{
	//	strFilter += strWinDIAFilter;
	//}
	//all
	{
		CString allFilter;
		VERIFY(allFilter.LoadString(AFX_IDS_ALLFILTER));
		strFilter += allFilter;
		strFilter += _T("|");
		strFilter += _T("*.*");
		strFilter += _T("||");
	}
	return (strFilter);
}

CString CDiagramEditApp::getCFileDialogFilterSave()
{
	//OuDia
	CString	strOriginalOuDiaFilter;
	strOriginalOuDiaFilter.LoadString(IDS_OriginalOuDiaFilter);

	CString	strFilter;
	//OuDiaSecond
	{
		CString	strFilterName;
		pRootDoctmpl()->GetDocString(strFilterName, CDocTemplate::filterName);
		CString	strExt;
		pRootDoctmpl()->GetDocString(strExt, CDocTemplate::filterExt);
		strFilter += strFilterName;
		strFilter += _T("|*");
		strFilter += strExt;
		strFilter += _T("|");
	}
	//OuDia
	{
		strFilter += strOriginalOuDiaFilter;
	}
	//all
	{
		CString allFilter;
		VERIFY(allFilter.LoadString(AFX_IDS_ALLFILTER));
		strFilter += allFilter;
		strFilter += _T("|");
		strFilter += _T("*.*");
		strFilter += _T("||");
	}
	return (strFilter);
}


CString CDiagramEditApp::getCFileDialogFilterCsv() 
{
	CString	strWinDIAFilter ;
	strWinDIAFilter.LoadString( IDS_WinDIAFilter ) ;

	CString	strFilter ;
	//CSV
	{
		strFilter += MfcUtil::LoadCString( IDS_CSVFilter )  ;
	}
	//all
	{
		CString allFilter;
		VERIFY(allFilter.LoadString(AFX_IDS_ALLFILTER));
		strFilter += allFilter;
		strFilter += _T( "|" ) ;
		strFilter += _T("*.*");
		strFilter += _T( "||" ) ;
	}
	return ( strFilter ) ;
}

CconvJikokuhyouCsv CDiagramEditApp::createCconvJikokuhyouCsv() 
{
	return	CconvJikokuhyouCsv( 
		(LPCTSTR)MfcUtil::LoadCString( IDS_WORD_Kudari ) , 
		(LPCTSTR)MfcUtil::LoadCString( IDS_WORD_Nobori ) , 
		(LPCTSTR)MfcUtil::LoadCString( IDS_WORD_Ressyabangou ) , 
		(LPCTSTR)MfcUtil::LoadCString( IDS_WORD_RESSYASYUBETSU ) ,
		(LPCTSTR)MfcUtil::LoadCString( IDS_WORD_Ressyamei ) ,
		(LPCTSTR)MfcUtil::LoadCString( IDS_WORD_Gousuu ) ,
		(LPCTSTR)MfcUtil::LoadCString( IDS_WORD_GOUSUU2 ) ,
		(LPCTSTR)MfcUtil::LoadCString( IDS_WORD_Bikou ) ,
		(LPCTSTR)MfcUtil::LoadCString( IDS_WORD_Chaku ) ,
		(LPCTSTR)MfcUtil::LoadCString( IDS_WORD_Hatsu ) ,
		(LPCTSTR)MfcUtil::LoadCString( IDS_WORD_JIKOKUHYOU_TSUUKA ) , 
		(LPCTSTR)MfcUtil::LoadCString( IDS_WORD_JIKOKUHYOU_KEIYUNASI ),
		(LPCTSTR)MfcUtil::LoadCString( IDS_WORD_Track ),
		(LPCTSTR)MfcUtil::LoadCString(IDS_WORD_OperationNumber),
		(LPCTSTR)MfcUtil::LoadCString(IDS_WORD_ShuchakuEkimei),
		(LPCTSTR)MfcUtil::LoadCString(IDS_WORD_ShihatsuOperation),
		(LPCTSTR)MfcUtil::LoadCString(IDS_WORD_ShuchakuEkimei),
		(LPCTSTR)MfcUtil::LoadCString(IDS_WORD_ShuchakuOperation),
		(LPCTSTR)MfcUtil::LoadCString(IDS_WORD_Jikoku),
		(LPCTSTR)MfcUtil::LoadCString(IDS_WORD_BeforeOperation),
		(LPCTSTR)MfcUtil::LoadCString(IDS_WORD_AfterOperation)
	);	

}

CconvJikokuhyouCustomizeCsv CDiagramEditApp::createCconvJikokuhyouCustomizeCsv()
{
	return	CconvJikokuhyouCustomizeCsv(
		(LPCTSTR)MfcUtil::LoadCString(IDS_WORD_Kudari),
		(LPCTSTR)MfcUtil::LoadCString(IDS_WORD_Nobori),
		(LPCTSTR)MfcUtil::LoadCString(IDS_WORD_Ressyabangou),
		(LPCTSTR)MfcUtil::LoadCString(IDS_WORD_RESSYASYUBETSU),
		(LPCTSTR)MfcUtil::LoadCString(IDS_WORD_Ressyamei),
		(LPCTSTR)MfcUtil::LoadCString(IDS_WORD_Gousuu),
		(LPCTSTR)MfcUtil::LoadCString(IDS_WORD_GOUSUU2),
		(LPCTSTR)MfcUtil::LoadCString(IDS_WORD_Bikou),
		(LPCTSTR)MfcUtil::LoadCString(IDS_WORD_Chaku),
		(LPCTSTR)MfcUtil::LoadCString(IDS_WORD_Hatsu),
		(LPCTSTR)MfcUtil::LoadCString(IDS_WORD_JIKOKUHYOU_TSUUKA),
		(LPCTSTR)MfcUtil::LoadCString(IDS_WORD_JIKOKUHYOU_KEIYUNASI),
		(LPCTSTR)MfcUtil::LoadCString(IDS_WORD_Track),
		(LPCTSTR)MfcUtil::LoadCString(IDS_WORD_OperationNumber),
		(LPCTSTR)MfcUtil::LoadCString(IDS_WORD_ShuchakuEkimei),
		(LPCTSTR)MfcUtil::LoadCString(IDS_WORD_ShihatsuOperation),
		(LPCTSTR)MfcUtil::LoadCString(IDS_WORD_ShuchakuEkimei),
		(LPCTSTR)MfcUtil::LoadCString(IDS_WORD_ShuchakuOperation),
		(LPCTSTR)MfcUtil::LoadCString(IDS_WORD_Jikoku),
		(LPCTSTR)MfcUtil::LoadCString(IDS_WORD_BeforeOperation),
		(LPCTSTR)MfcUtil::LoadCString(IDS_WORD_AfterOperation)
	);

}

CconvOperationTableCsv CDiagramEditApp::createCconvOperationTableCsv()
{
	return	CconvOperationTableCsv(
		(LPCTSTR)MfcUtil::LoadCString(IDS_WORD_Ressyabangou),
		(LPCTSTR)MfcUtil::LoadCString(IDS_WORD_RESSYASYUBETSU),
		(LPCTSTR)MfcUtil::LoadCString(IDS_WORD_Ressyamei),
		(LPCTSTR)MfcUtil::LoadCString(IDS_WORD_Gousuu),
		(LPCTSTR)MfcUtil::LoadCString(IDS_WORD_GOUSUU2),
		(LPCTSTR)MfcUtil::LoadCString(IDS_WORD_Ekimei),
		(LPCTSTR)MfcUtil::LoadCString(IDS_WORD_Ekijikoku),
		(LPCTSTR)MfcUtil::LoadCString(IDS_WORD_KudariArrow),
		(LPCTSTR)MfcUtil::LoadCString(IDS_WORD_NoboriArrow)
	);

}
	// ********************************
	//@name	操作 - ファイル名
	// ********************************
CString CDiagramEditApp::makeProgramDirFilename( const CString& strFilename ) 
{
	CString	strProgramDir ;
	{
		TCHAR	szExe[MAX_PATH] ;
		GetModuleFileName(NULL, szExe, sizeof(szExe) / sizeof(TCHAR));
		strProgramDir = szExe ;
		int idx = strProgramDir.ReverseFind( _T( '¥¥' ) ) ;
		strProgramDir = strProgramDir.Left( idx + 1 ) ;
	}
	//strProgramDir = .exe ファイルのあるディレクトリ(例:"c:¥program files¥oudia¥" )。

	if ( strFilename.GetLength() > 0 )
	{
		strProgramDir += strFilename ;
	}
	return strProgramDir ;
}

CString CDiagramEditApp::makeLocalAppdataFilename( const CString& strFilename ) 
{
	CString	strLocalAppdataFolder ;
	{
		TCHAR	szPath[MAX_PATH] ;
		BOOL bResult = SHGetSpecialFolderPath( 
			NULL , 
			szPath , 
			CSIDL_LOCAL_APPDATA , 
			TRUE ) ;
		if ( bResult )
		{
			strLocalAppdataFolder = szPath ;
		}
		else
		{
			GetTempPath( sizeof(szPath) / sizeof(szPath[0] ) , szPath ) ;
			strLocalAppdataFolder = szPath ;
		}
		//	末尾に '¥¥' がある場合は、これを削除
		if ( strLocalAppdataFolder.GetLength() > 0 && 
			strLocalAppdataFolder[ strLocalAppdataFolder.GetLength() - 1 ] 
				== _T( '¥¥' ) )
		{
			strLocalAppdataFolder.Delete( 
				strLocalAppdataFolder.GetLength() - 1 ) ;
		}
	}
	//strLocalAppdataFolder = LocalAppData(取得できなければテンポラリディレクトリ)
	//	末尾には '¥' はありません。

	strLocalAppdataFolder += _T( "¥¥OuDiaSecondV2¥¥" ) ; //edit_by_d_mania
	//strLocalAppdataFolder = OuDiaのLocalAppDataフォルダ。
	//	末尾には '¥¥' があります。
	//	このディレクトリは、作成されています。

	if ( strFilename.GetLength() > 0 )
	{
		strLocalAppdataFolder += strFilename ;
	}
	return strLocalAppdataFolder ;
}


CString CDiagramEditApp::makeHtmlHelpUrl( const CString& strTopic ) 
{
	CString strHtmlHelpUrl = makeProgramDirFilename( _T( "oudia.chm" ) ) ;
	if ( !strTopic.IsEmpty() )
	{
		strHtmlHelpUrl += _T( "::" ) ;
		strHtmlHelpUrl += strTopic ;
	}
	return strHtmlHelpUrl ;
}


	// ********************************
	//@name	操作- .ini ファイル
	// ********************************
const TCHAR nameCWndDiagram_DiagramPosDgr[] = _T("DiagramPosDgr") ;
const TCHAR nameCWndDiagram_DcdPerDgrX[] = _T("DcdPerDgrX") ;
const TCHAR nameCWndDiagram_DcdPerDgrY[] = _T("DcdPerDgrY") ;

const TCHAR nameCWndDiagram_VlineMode[] = _T("DiagramVlineMode") ;
const TCHAR nameCWndDiagram_DisplayRessyabangou[] = 
	_T("DiagramDisplayRessyabangou") ;
const TCHAR nameCWndDiagram_DisplayRessyamei[] = 
	_T("DiagramDisplayRessyamei") ;
const TCHAR nameCWndDiagram_DisplayRessyasen[] = 
	_T("DiagramDisplayRessyasen") ;
const TCHAR nameCWndDiagram_HideIppanekiEkimei[] = 
	_T("DiagramHideIppanekiEkimei") ;
const TCHAR nameCWndDiagram_StopMarkDraw[] = 
	_T("DiagramStopMarkDraw") ;
const TCHAR nameCWndDiagram_KeepZoneDgrOnSize[] = 
	_T("DiagramKeepZoneDgrOnSize") ;
const TCHAR nameDisplayParentSyubetsu[] =
_T("DisplayParentSyubetsu");
const TCHAR nameDisplayBackColorNextEki[] =
_T("DisplayBackColorNextEki");

int CDiagramEditApp::writeCWndDiagramViewProp( const CWndDiagram* pCWndDiagram )
{
	int iRv = 0 ;
	
	//属性を取得
	CdDcdPosXy	posPosDgr = pCWndDiagram->getPosDgr() ;
	double	dDcdPerDgrX = pCWndDiagram->getDcdPerDgrX() ;
	double	dDcdPerDgrY = pCWndDiagram->getDcdPerDgrY() ;

	int idxVlineMode = pCWndDiagram->getVlineMode() ;
	bool	bDisplayRessyabangou = pCWndDiagram->getDisplayRessyabangou() ;
	bool	bDisplayRessyamei = pCWndDiagram->getDisplayRessyamei() ;
	bool bDisplayRessyasenKudari = 
		pCWndDiagram->getDisplayRessyasen( Ressyahoukou_Kudari ) ;
	bool bDisplayRessyasenNobori = 
		pCWndDiagram->getDisplayRessyasen( Ressyahoukou_Nobori ) ;
	bool bHideIppanekiEkimei = 
		pCWndDiagram->getHideIppanekiEkimei() ;
	CDcdDiagram::EStopMarkDraw eStopMarkDraw = pCWndDiagram->getStopMarkDraw() ;
	bool bKeepZoneDgrOnSize = pCWndDiagram->getKeepZoneDgrOnSize() ;
	bool bDisplayParentSyubetsu = pCWndDiagram->getDisplayParentSyubetsu();
	bool bDisplayBackColorNextEki = pCWndDiagram->getDisplayBackColorNextEki();
	// --------------------------------
	//DiagramPosDgr
	if ( iRv >= 0 )
	{
		tstring	strValue ;
		strValue += stringOf( posPosDgr.getX() ) ;
		strValue += ',' ;
		strValue += stringOf( posPosDgr.getY() ) ;
		WriteProfileString( 
			nameSection , 
			nameCWndDiagram_DiagramPosDgr , 
			strValue.c_str() ) ;
	}
	//"DcdPerDgrX" ;
	{
		tstring	strValue ;
		strValue += stringOf( dDcdPerDgrX ) ;
		WriteProfileString( 
			nameSection , 
			nameCWndDiagram_DcdPerDgrX , 
			strValue.c_str() ) ;
	}

	//"DcdPerDgrY" ;
	{
		tstring	strValue ;
		strValue += stringOf( dDcdPerDgrY ) ;
		WriteProfileString( 
			nameSection , 
			nameCWndDiagram_DcdPerDgrY , 
			strValue.c_str() ) ;
	}


	//DiagramVlineMode
	if ( iRv >= 0 ){
		tstring	strValue ;
		strValue += stringOf( idxVlineMode ) ;
		WriteProfileString( nameSection , nameCWndDiagram_VlineMode , 
			strValue.c_str() ) ;
	}
	
	//DisplayRessyabangou
	if ( iRv >= 0 ){
		tstring	strValue ;
		strValue += stringOf( bDisplayRessyabangou ) ;
		WriteProfileString( nameSection , nameCWndDiagram_DisplayRessyabangou ,
			strValue.c_str() ) ;
	}
	
	//DisplayRessyamei
	if ( iRv >= 0 ){
		tstring	strValue ;
		strValue += stringOf( bDisplayRessyamei ) ;
		WriteProfileString( nameSection , nameCWndDiagram_DisplayRessyamei ,
			strValue.c_str() ) ;
	}
	
	//DisplayRessyasen
	if ( iRv >= 0 ){
		tstring	strValue ;
		strValue += ( bDisplayRessyasenKudari ? _T("1") : _T("0") ) ;
		strValue += ',' ;
		strValue += ( bDisplayRessyasenNobori ? _T("1") : _T("0") ) ;
		WriteProfileString( nameSection , nameCWndDiagram_DisplayRessyasen ,
			strValue.c_str() ) ;
	}
	//DiagramHideIppanekiEkimei
	if ( iRv >= 0 )
	{
		tstring	strValue = ( bHideIppanekiEkimei ? _T("1") : _T("0") ) ;
		WriteProfileString( nameSection , nameCWndDiagram_HideIppanekiEkimei ,
			strValue.c_str() ) ;
	}
	//DiagramStopMarkDraw
	if ( iRv >= 0 )
	{
		tstring strValue = stringOf( (int)eStopMarkDraw ) ;
		WriteProfileString( nameSection , nameCWndDiagram_StopMarkDraw , 
			strValue.c_str() ) ;
	}
	//DiagramKeepZoneDgrOnSize
	if ( iRv >= 0 )
	{
		tstring strValue = ( bKeepZoneDgrOnSize ? _T("1") : _T("0") ) ;
		WriteProfileString( nameSection , nameCWndDiagram_KeepZoneDgrOnSize ,
			strValue.c_str() ) ;
	}
	//DisplayParentSyubetsu
	if (iRv >= 0)
	{
		tstring strValue = (bDisplayParentSyubetsu ? _T("1") : _T("0"));
		WriteProfileString(nameSection, nameDisplayParentSyubetsu,
			strValue.c_str());
	}
	//DisplayBackColorNextEki
	if (iRv >= 0)
	{
		tstring strValue = (bDisplayParentSyubetsu ? _T("1") : _T("0"));
		WriteProfileString(nameSection, nameDisplayBackColorNextEki,
			strValue.c_str());
	}
	return ( iRv ) ;
}

int CDiagramEditApp::readCWndDiagramViewProp( CWndDiagram* pCWndDiagram ) 
{
	int iRv = 0 ;

	CdDcdPosXy	posPosDgr( 0 , 0 ) ;
	double	dDcdPerDgrX = CDcdDiagram::DEFAULT_DCD_PER_DGR_X() ;
	double	dDcdPerDgrY = CDcdDiagram::DEFAULT_DCD_PER_DGR_Y() ;

	int idxVlineMode = 1 ;
	bool bDisplayRessyabangou = false ;
	bool bDisplayRessyamei = false ;
	bool bDisplayRessyasenKudari = true ;
	bool bDisplayRessyasenNobori = true ;
	bool bHideIppanekiEkimei = false ;
	CDcdDiagram::EStopMarkDraw eStopMarkDraw = CDcdDiagram::EStopMarkDraw_Nothing ;
	bool bKeepZoneDgrOnSize = false ;
	bool bDisplayParentSyubetsu = false;
	bool bDisplayBackColorNextEki = false;
	// --------------------------------
	//DiagramPosDgr
	if ( iRv >= 0 )
	{
		tstring	strValue = GetProfileString( nameSection , 
			nameCWndDiagram_DiagramPosDgr ) ;
		deque<tstring>	contstrValue = 
			splitc< deque< tstring > >( ',' , strValue ) ;
		if ( contstrValue.size() != 2 )
		{
			iRv = -1 ;	//	DiagramPosDgr が指定されていません。
		}
		else
		{
			int iXPos  = intOf( contstrValue[0] ) ;
			int iYPos  = intOf( contstrValue[1] ) ;
			posPosDgr.setX( iXPos ).setY( iYPos ) ;
		}
	}
	//DcdPerDgrX
	if ( iRv >= 0 ){
		tstring	strValue = GetProfileString( nameSection , 
			nameCWndDiagram_DcdPerDgrX ) ;
		if ( strValue.empty() ){
			iRv = -2 ;	//	DcdPerDgrX が指定されていません。
		}	else	{
			dDcdPerDgrX = doubleOf( strValue ) ; 
		}
	}
	//DcdPerDgrY
	if ( iRv >= 0 ){
		tstring	strValue = GetProfileString( nameSection , 
			nameCWndDiagram_DcdPerDgrY ) ;
		if ( strValue.empty() ){
			iRv = -2 ;	//	DcdPerDgrY が指定されていません。
		}	else	{
			dDcdPerDgrY = doubleOf( strValue ) ; 
		}
	}



	//DiagramVlineMode
	if ( iRv >= 0 ){
		tstring	strValue = GetProfileString( nameSection , 
			nameCWndDiagram_VlineMode ) ;
		if ( strValue.empty() ){
			iRv = -2 ;	//	DiagramVlineMode が指定されていません。
		}	else	{
			idxVlineMode = intOf( strValue ) ; 
		}
	}

	//DisplayRessyabangou
	if ( iRv >= 0 )
	{
		tstring	strValue = GetProfileString( nameSection , 
			nameCWndDiagram_DisplayRessyabangou ) ;
		if ( strValue.empty() )
		{
			iRv = -3 ;	//	DisplayRessyabangou が指定されていません。
		}
		else
		{
			bDisplayRessyabangou = ( intOf( strValue ) != 0 ); 
		}
	}

	//DisplayRessyamei
	if ( iRv >= 0 ){
		tstring	strValue = GetProfileString( nameSection , 
			nameCWndDiagram_DisplayRessyamei ) ;
		if ( strValue.empty() ){
			iRv = -4 ;	//	DisplayRessyamei が指定されていません。
		}	else	{
			bDisplayRessyamei = ( intOf( strValue ) != 0 ); 
		}
	}
	//DisplayRessyasen
	if ( iRv >= 0 )
	{
		tstring	strValue = GetProfileString( 
			nameSection , nameCWndDiagram_DisplayRessyasen ) ;
		deque<tstring>	contstrValue = 
			splitc< deque< tstring > >( ',' , strValue ) ;
		if ( contstrValue.size() != 2 )
		{
			iRv = -5 ;	//	DisplayRessyasen が指定されていません。
		}
		else
		{
			bDisplayRessyasenKudari = ( contstrValue[0] == _T("1") ) ;
			bDisplayRessyasenNobori = ( contstrValue[1] == _T("1") ) ;
		}
	}
	//DiagramHideIppanekiEkimei
	if ( iRv >= 0 )
	{
		tstring	strValue = GetProfileString( 
			nameSection , nameCWndDiagram_HideIppanekiEkimei ) ;
		if ( strValue.empty() )
		{
			iRv = -6 ;	//	HideIppanekiEkimei が指定されていません。
		}
		else
		{
			bHideIppanekiEkimei = ( intOf( strValue ) != 0 ) ;
		}
	}
	//DiagramStopMarkDraw
	if ( iRv >= 0 )
	{
		tstring	strValue = GetProfileString( 
			nameSection , nameCWndDiagram_StopMarkDraw ) ;
		if ( strValue.empty() )
		{
			iRv = -7 ;	//	StopMarkDraw が指定されていません。
		}
		else
		{
			eStopMarkDraw = (CDcdDiagram::EStopMarkDraw)intOf( strValue ) ;
		}
	}
	//DiagramKeepZoneDgrOnSize
	if ( iRv >= 0 )
	{
		tstring	strValue = GetProfileString( 
			nameSection , nameCWndDiagram_KeepZoneDgrOnSize ) ;
		if ( strValue.empty() )
		{
			iRv = -8 ;	//	KeepZoneDgrOnSize が指定されていません。
		}
		else
		{
			bKeepZoneDgrOnSize = (intOf( strValue )!=0) ;
		}
	}
	//DisplayParentSyubetsu
	if (iRv >= 0)
	{
		tstring	strValue = GetProfileString(
			nameSection, nameDisplayParentSyubetsu);
		if (strValue.empty())
		{
			iRv = -9;	//	DisplayParentSyubetsu が指定されていません。
		}
		else
		{
			bDisplayParentSyubetsu = (intOf(strValue) != 0);
		}
	}
	//DisplayBackColorNextEki
	if (iRv >= 0)
	{
		tstring	strValue = GetProfileString(
			nameSection, nameDisplayBackColorNextEki);
		if (strValue.empty())
		{
			iRv = -9;	//	DisplayBackColorNextEki が指定されていません。
		}
		else
		{
			bDisplayBackColorNextEki = (intOf(strValue) != 0);
		}
	}
	// --------------------------------
	if ( iRv >= 0 )
	{
		pCWndDiagram->setPosDgr( posPosDgr ) ;
		pCWndDiagram->setDcdPerDgrX( dDcdPerDgrX ) ;
		pCWndDiagram->setDcdPerDgrY( dDcdPerDgrY ) ;

		pCWndDiagram->setVlineMode( idxVlineMode ) ;
		pCWndDiagram->setDisplayRessyabangou( bDisplayRessyabangou ) ;
		pCWndDiagram->setDisplayRessyamei( bDisplayRessyamei ) ;
		pCWndDiagram->setDisplayRessyasen( Ressyahoukou_Kudari , 
			 bDisplayRessyasenKudari ) ;
		pCWndDiagram->setDisplayRessyasen( Ressyahoukou_Nobori , 
			 bDisplayRessyasenNobori ) ;
		pCWndDiagram->setHideIppanekiEkimei( bHideIppanekiEkimei ) ;
		pCWndDiagram->setStopMarkDraw( eStopMarkDraw ) ;
		pCWndDiagram->setKeepZoneDgrOnSize( bKeepZoneDgrOnSize ) ;
		pCWndDiagram->setDisplayParentSyubetsu(bDisplayParentSyubetsu);
		pCWndDiagram->setDisplayBackColorNextEki(bDisplayBackColorNextEki);
	}
	
	return ( iRv ) ;
}

const TCHAR nameCWndJikokuhyou_DisplayTsuukaEkiJikoku[] = 
	_T( "Jikokuhyou_DisplayTsuukaEkiJikoku" ) ;
const TCHAR nameCWndJikokuhyou_DisplayAllEkiJikoku[] = 
	_T( "Jikokuhyou_DisplayAllEkiJikoku" ) ;
const TCHAR nameCWndJikokuhyou_EkijikokuSort[] = 
	_T( "Jikokuhyou_EkijikokuSort" );
const TCHAR nameCWndJikokuhyou_ModifyEkijikoku[] = 
	_T( "Jikokuhyou_ModifyEkiJikoku" );
//add_by_d_mania
const TCHAR nameCWndJikokuhyou_DisplaySecondEkiJikoku[] = 
	_T( "Jikokuhyou_DisplaySecondEkiJikoku" ) ;
const TCHAR nameCWndJikokuhyou_StandardOperationTimeFunction[] = 
	_T( "Jikokuhyou_StandardOperationTimeFunction" ) ;
const TCHAR nameCWndJikokuhyou_DisplayShihatsuShuchakuEkimei[] =
	_T("Jikokuhyou_DisplayShihatsuShuchakuEkimei");
const TCHAR nameCWndJikokuhyou_DisplayColonEkiJikoku[] =
_T("Jikokuhyou_DisplayColonEkiJikoku");
const TCHAR nameCWndJikokuhyou_CompareBottom[] =
_T("Jikokuhyou_CompareBottom");
const TCHAR nameCWndJikokuhyou_DisplayTsuukaFontPerSyubetsu[] =
_T("Jikokuhyou_DisplayTsuukaFontPerSyubetsu");

int CDiagramEditApp::writeCWndJikokuhyouViewProp( const CWndJikokuhyou* pCWndJikokuhyou ) 
{
	int iRv = 0 ;
	
	//属性を取得
	bool	bDisplayTsuukaEkiJikoku = pCWndJikokuhyou->getDisplayTsuukaEkiJikoku() ;
	bool	bDisplayAllEkiJikoku = pCWndJikokuhyou->getDisplayAllEkiJikoku() ;
	CWndJikokuhyou::EEkijikokuSort	eEkijikokuSort = pCWndJikokuhyou->getEkijikokuSort() ;
	bool bModifyEkijikoku = pCWndJikokuhyou->getModifyEkijikoku() ;
	//add_by_d_mania
	bool	bDisplaySecondEkiJikoku = pCWndJikokuhyou->getDisplaySecondEkiJikoku( );
	bool	bStandardOperationTimeFunction = pCWndJikokuhyou->getStandardOperationTimeFunction() ;
	//bool	bDisplayAllTrack = pCWndJikokuhyou->getCustomizeDisplayMode();
	bool	bDisplayShihatsuShuchakuEkimei = pCWndJikokuhyou->getDisplayShihatsuShuchakuEkimei();
	bool	bDisplayColonEkiJikoku = pCWndJikokuhyou->getDisplayColonEkiJikoku();
	bool	bDisplayParentSyubetsu = pCWndJikokuhyou->getDisplayParentSyubetsu();
	bool	bCompareBottom = pCWndJikokuhyou->getCompareBottom();
	bool	bDisplayTsuukaFontPerSyubetsu = pCWndJikokuhyou->getDisplayTsuukaFontPerSyubetsu();
	// --------------------------------

	//DisplayTsuukaEkiJikoku
	if ( iRv >= 0 )
	{
		tstring	strValue ;
		strValue += stringOf( bDisplayTsuukaEkiJikoku ? 1 : 0 ) ;
		WriteProfileString( nameSection , nameCWndJikokuhyou_DisplayTsuukaEkiJikoku ,
			tstringOf( strValue ).c_str() ) ;
	}
	//DisplayAllEkiJikoku
	{
		tstring	strValue ;
		strValue += stringOf( bDisplayAllEkiJikoku ) ;
		WriteProfileString( nameSection , nameCWndJikokuhyou_DisplayAllEkiJikoku ,
			tstringOf( strValue ).c_str() ) ;
	}
	//EkijikokuSort
	if ( iRv >= 0 )
	{
		tstring strValue ;
		strValue += stringOf( (int)eEkijikokuSort ) ;
		WriteProfileString( nameSection , nameCWndJikokuhyou_EkijikokuSort ,
			tstringOf( strValue ).c_str() ) ;
	}

	//ModifyEkijikoku
	if ( iRv >= 0 )
	{
		tstring strValue ;
		strValue = ( bModifyEkijikoku ? _T( "1" ) : _T( "0" ) ) ;
		WriteProfileString( nameSection , nameCWndJikokuhyou_ModifyEkijikoku ,
			tstringOf( strValue ).c_str() ) ;
	}
	//DisplaySecondEkiJikoku//add_by_d_mania
	if ( iRv >= 0 )
	{
		tstring	strValue ;
		strValue += stringOf( bDisplaySecondEkiJikoku ? 1 : 0 ) ;
		WriteProfileString( nameSection , nameCWndJikokuhyou_DisplaySecondEkiJikoku ,
			tstringOf( strValue ).c_str() ) ;
	}
	//StandardOperationTimeFunction//add_by_d_mania
	if ( iRv >= 0 )
	{
		tstring	strValue ;
		strValue += stringOf( bStandardOperationTimeFunction ? 1 : 0 ) ;
		WriteProfileString( nameSection , nameCWndJikokuhyou_StandardOperationTimeFunction ,
			tstringOf( strValue ).c_str() ) ;
	}
	//DisplayAllTrack
	//{
	//	tstring	strValue;
	//	strValue += stringOf(bDisplayAllTrack);
	//	WriteProfileString(nameSection, nameCWndJikokuhyou_DisplayAllTrack,
	//		tstringOf(strValue).c_str());
	//}
	//DisplayShihatsuShuchakuEkimei
	{
		tstring	strValue;
		strValue += stringOf(bDisplayShihatsuShuchakuEkimei);
		WriteProfileString(nameSection, nameCWndJikokuhyou_DisplayShihatsuShuchakuEkimei,
			tstringOf(strValue).c_str());
	}
	//DisplayColonEkiJikoku
	if (iRv >= 0)
	{
		tstring	strValue;
		strValue += stringOf(bDisplayColonEkiJikoku ? 1 : 0);
		WriteProfileString(nameSection, nameCWndJikokuhyou_DisplayColonEkiJikoku,
			tstringOf(strValue).c_str());
	}
	//DisplayParentSyubetsu
	if (iRv >= 0)
	{
		tstring	strValue;
		strValue += stringOf(bDisplayParentSyubetsu ? 1 : 0);
		WriteProfileString(nameSection, nameDisplayParentSyubetsu,
			tstringOf(strValue).c_str());
	}
	//CompareBottom
	if (iRv >= 0)
	{
		tstring	strValue;
		strValue += stringOf(bCompareBottom ? 1 : 0);
		WriteProfileString(nameSection, nameCWndJikokuhyou_CompareBottom,
			tstringOf(strValue).c_str());
	}
	//Jikokuhyou_DisplayTsuukaFontPerSyubetsu
	if (iRv >= 0)
	{
		tstring	strValue;
		strValue += stringOf(bDisplayTsuukaFontPerSyubetsu ? 1 : 0);
		WriteProfileString(nameSection, nameCWndJikokuhyou_DisplayTsuukaFontPerSyubetsu,
			tstringOf(strValue).c_str());
	}
	return ( iRv ) ;
}
int CDiagramEditApp::readCWndJikokuhyouViewProp(CWndJikokuhyou* pCWndJikokuhyou)
{
	int iRv = 0;
	bool	bDisplayTsuukaEkiJikoku = true;
	bool 	bDisplayAllEkiJikoku = false;
	CWndJikokuhyou::EEkijikokuSort	eEkijikokuSort = CWndJikokuhyou::EEkijikokuSort_Ekiatsukai;
	bool	bModifyEkijikoku = true;
	bool	bDisplaySecondEkiJikoku = false;
	bool	bStandardOperationTimeFunction = false;
	//bool 	bDisplayAllTrack = false;
	bool 	bDisplayShihatsuShuchakuEkimei = false;
	bool	bDisplayColonEkiJikoku = false;
	bool	bDisplayParentSyubetsu = false;
	bool	bCompareBottom = false;
	bool	bDisplayTsuukaFontPerSyubetsu = false;


	// --------------------------------
	//DisplayTsuukaEkiJikoku
	if (iRv >= 0)
	{
		tstring	strValue = tstringOf((LPCTSTR)GetProfileString(
			nameSection, nameCWndJikokuhyou_DisplayTsuukaEkiJikoku));
		if (strValue.empty())
		{
			iRv = -1;	//	DisplayTsuukaEkiJikoku が指定されていません。
		}
		else
		{
			bDisplayTsuukaEkiJikoku = (intOf(strValue) != 0);
		}
	}
	//DisplayAllEkiJikoku
	{
		tstring	strValue = tstringOf((LPCTSTR)GetProfileString(
			nameSection, nameCWndJikokuhyou_DisplayAllEkiJikoku));
		if (strValue.empty())
		{
			iRv = -1;	//	DisplayAllEkiJikoku が指定されていません。
		}
		else
		{
			bDisplayAllEkiJikoku = (intOf(strValue) != 0);
		}
	}
	//EkijikokuSort
	if (iRv >= 0)
	{
		tstring	strValue = tstringOf((LPCTSTR)GetProfileString(
			nameSection, nameCWndJikokuhyou_EkijikokuSort));
		if (strValue.empty())
		{
			iRv = -1;	//	EkijikokuSort が指定されていません。
		}
		else
		{
			int iValue = intOf(strValue);
			switch (iValue)
			{
			case (int)CWndJikokuhyou::EEkijikokuSort_Ekiatsukai:
				eEkijikokuSort = CWndJikokuhyou::EEkijikokuSort_Ekiatsukai;
				break;
			case (int)CWndJikokuhyou::EEkijikokuSort_Transfer:
				eEkijikokuSort = CWndJikokuhyou::EEkijikokuSort_Transfer;
				break;
			}
		}
	}
	//ModifyEkijikoku
	if (iRv >= 0)
	{
		tstring	strValue = GetProfileString(
			nameSection, nameCWndJikokuhyou_ModifyEkijikoku);
		if (strValue.empty())
		{
			iRv = -1;	//	ModifyEkijikoku が指定されていません。
		}
		else
		{
			int iValue = intOf(strValue);
			bModifyEkijikoku = (iValue != 0);
		}
	}
	//DisplaySecondEkiJikoku//add_by_d_mania
	if (iRv >= 0)
	{
		tstring	strValue = tstringOf((LPCTSTR)GetProfileString(
			nameSection, nameCWndJikokuhyou_DisplaySecondEkiJikoku));
		if (strValue.empty())
		{
			iRv = -1;	//	DisplaySecondEkiJikoku が指定されていません。
		}
		else
		{
			bDisplaySecondEkiJikoku = (intOf(strValue) != 0);
		}
	}
	//StandardOperationTimeFunction//add_by_d_mania
	if (iRv >= 0)
	{
		tstring	strValue = tstringOf((LPCTSTR)GetProfileString(
			nameSection, nameCWndJikokuhyou_StandardOperationTimeFunction));
		if (strValue.empty())
		{
			iRv = -1;	//	StandardOperationTimeFunction が指定されていません。
		}
		else
		{
			bStandardOperationTimeFunction = (intOf(strValue) != 0);
		}
	}
	//DisplayAllTrack
	//if (iRv >= 0)
	//{
	//	tstring	strValue = tstringOf((LPCTSTR)GetProfileString(
	//		nameSection, nameCWndJikokuhyou_DisplayAllTrack));
	//	if (strValue.empty())
	//	{
	//		iRv = -1;	//	DisplayAllTrack が指定されていません。
	//	}
	//	else
	//	{
	//		bDisplayAllTrack = (intOf(strValue) != 0);
	//	}
	//}
	//DisplayShihatsuShuchakuEkimei
	if (iRv >= 0)
	{
		tstring	strValue = tstringOf((LPCTSTR)GetProfileString(
			nameSection, nameCWndJikokuhyou_DisplayShihatsuShuchakuEkimei));
		if (strValue.empty())
		{
			iRv = -1;	//	DisplayAllTrack が指定されていません。
		}
		else
		{
			bDisplayShihatsuShuchakuEkimei = (intOf(strValue) != 0);
		}
	}
	//DisplayColonEkiJikoku
	if (iRv >= 0)
	{
		tstring	strValue = tstringOf((LPCTSTR)GetProfileString(
			nameSection, nameCWndJikokuhyou_DisplayColonEkiJikoku));
		if (strValue.empty())
		{
			iRv = -1;	//	DisplayColonEkiJikoku が指定されていません。
		}
		else
		{
			bDisplayColonEkiJikoku = (intOf(strValue) != 0);
		}
	}
	//DisplayParentSyubetsu
	if (iRv >= 0)
	{
		tstring	strValue = tstringOf((LPCTSTR)GetProfileString(
			nameSection, nameDisplayParentSyubetsu));
		if (strValue.empty())
		{
			iRv = -1;	//	DisplayColonEkiJikoku が指定されていません。
		}
		else
		{
			bDisplayParentSyubetsu = (intOf(strValue) != 0);
		}
	}
	//CompareBottom
	if (iRv >= 0)
	{
		tstring	strValue = tstringOf((LPCTSTR)GetProfileString(
			nameSection, nameCWndJikokuhyou_CompareBottom));
		if (strValue.empty())
		{
			iRv = -1;	//	CompareBottom が指定されていません。
		}
		else
		{
			bCompareBottom = (intOf(strValue) != 0);
		}
	}
	//DisplayTsuukaFontPerSyubetsu
	if (iRv >= 0)
	{
		tstring	strValue = tstringOf((LPCTSTR)GetProfileString(
			nameSection, nameCWndJikokuhyou_DisplayTsuukaFontPerSyubetsu));
		if (strValue.empty())
		{
			iRv = -1;	//	DisplayTsuukaFontPerSyubetsu が指定されていません。
		}
		else
		{
			bDisplayTsuukaFontPerSyubetsu = (intOf(strValue) != 0);
		}
	}
	// --------------------------------
	if (iRv >= 0)
	{
		pCWndJikokuhyou->setDisplayTsuukaEkiJikoku(bDisplayTsuukaEkiJikoku);
		pCWndJikokuhyou->setDisplayAllEkiJikoku(bDisplayAllEkiJikoku);
		pCWndJikokuhyou->setEkijikokuSort(eEkijikokuSort);
		pCWndJikokuhyou->setModifyEkijikoku(bModifyEkijikoku);
		pCWndJikokuhyou->setDisplaySecondEkiJikoku(bDisplaySecondEkiJikoku);
		pCWndJikokuhyou->setStandardOperationTimeFunction(bStandardOperationTimeFunction);
		//pCWndJikokuhyou->setCustomizeDisplayMode(bDisplayAllTrack);
		pCWndJikokuhyou->setDisplayShihatsuShuchakuEkimei(bDisplayShihatsuShuchakuEkimei);
		pCWndJikokuhyou->setDisplayColonEkiJikoku(bDisplayColonEkiJikoku);
		pCWndJikokuhyou->setDisplayParentSyubetsu(bDisplayParentSyubetsu);
		pCWndJikokuhyou->setCompareBottom(bCompareBottom);
		pCWndJikokuhyou->setDisplayTsuukaFontPerSyubetsu(bDisplayTsuukaFontPerSyubetsu);
	}


	return (iRv);
}

const TCHAR nameCWndDcdGridOperationTable_DisplayNoboriLeftToRight[] =
_T("OperationTable_DisplayNoboriLeftToRight");
const TCHAR nameCWndDcdGridOperationTable_DisplayExtensionOperationTable[] =
_T("OperationTable_DisplayExtensionOperationTable");
const TCHAR nameCWndDcdGridOperationTable_DisplayTrackName[] =
_T("OperationTable_DisplayTrackName");

int CDiagramEditApp::writeCWndDcdGridOperationTableViewProp(const CWndDcdGridOperationTable* pCWndDcdGridOperationTable)
{
	int iRv = 0;

	//属性を取得
	bool	bDisplaySecondEkiJikoku = pCWndDcdGridOperationTable->getDisplaySecondEkiJikoku();
	bool	bDisplayColonEkiJikoku = pCWndDcdGridOperationTable->getDisplayColonEkiJikoku();
	bool	bDisplayParentSyubetsu = pCWndDcdGridOperationTable->getDisplayParentSyubetsu();
	bool	bDisplayNoboriLeftToRight = pCWndDcdGridOperationTable->getDisplayNoboriLeftToRight();
	bool	bDisplayExtensionOperationTable = pCWndDcdGridOperationTable->getDisplayExtensionOperationTable();
	bool	bDisplayTrackName = pCWndDcdGridOperationTable->getDisplayTrackName();
	bool	bDisplayTsuukaEkiJikoku = pCWndDcdGridOperationTable->getDisplayTsuukaEkiJikoku();
	// --------------------------------


	//DisplaySecondEkiJikoku//add_by_d_mania
	if (iRv >= 0)
	{
		tstring	strValue;
		strValue += stringOf(bDisplaySecondEkiJikoku ? 1 : 0);
		WriteProfileString(nameSection, nameCWndJikokuhyou_DisplaySecondEkiJikoku,
			tstringOf(strValue).c_str());
	}
	//DisplayColonEkiJikoku
	if (iRv >= 0)
	{
		tstring	strValue;
		strValue += stringOf(bDisplayColonEkiJikoku ? 1 : 0);
		WriteProfileString(nameSection, nameCWndJikokuhyou_DisplayColonEkiJikoku,
			tstringOf(strValue).c_str());
	}
	//DisplayParentSyubetsu
	if (iRv >= 0)
	{
		tstring	strValue;
		strValue += stringOf(bDisplayParentSyubetsu ? 1 : 0);
		WriteProfileString(nameSection, nameDisplayParentSyubetsu,
			tstringOf(strValue).c_str());
	}
	//DisplayNoboriLeftToRight
	if (iRv >= 0)
	{
		tstring	strValue;
		strValue += stringOf(bDisplayNoboriLeftToRight ? 1 : 0);
		WriteProfileString(nameSection, nameCWndDcdGridOperationTable_DisplayNoboriLeftToRight,
			tstringOf(strValue).c_str());
	}
	//DisplayExtensionOperationTable
	if (iRv >= 0)
	{
		tstring	strValue;
		strValue += stringOf(bDisplayExtensionOperationTable ? 1 : 0);
		WriteProfileString(nameSection, nameCWndDcdGridOperationTable_DisplayExtensionOperationTable,
			tstringOf(strValue).c_str());
	}
	//DisplayTrackName
	if (iRv >= 0)
	{
		tstring	strValue;
		strValue += stringOf(bDisplayTrackName ? 1 : 0);
		WriteProfileString(nameSection, nameCWndDcdGridOperationTable_DisplayTrackName,
			tstringOf(strValue).c_str());
	}
	//DisplayTsuukaEkiJikoku
	if (iRv >= 0)
	{
		tstring	strValue;
		strValue += stringOf(bDisplayTsuukaEkiJikoku ? 1 : 0);
		WriteProfileString(nameSection, nameCWndJikokuhyou_DisplayTsuukaEkiJikoku,
			tstringOf(strValue).c_str());
	}
	return (iRv);
}
int CDiagramEditApp::readCWndDcdGridOperationTableViewProp(CWndDcdGridOperationTable* pCWndDcdGridOperationTable)
{
	int iRv = 0;
	bool	bDisplaySecondEkiJikoku = false;
	bool	bDisplayColonEkiJikoku = false;
	bool	bDisplayParentSyubetsu = false;
	bool	bDisplayNoboriLeftToRight = false;
	bool	bDisplayExtensionOperationTable = false;
	bool	bDisplayTrackName = false;
	bool	bDisplayTsuukaEkiJikoku = true;


	// --------------------------------

	//DisplaySecondEkiJikoku//add_by_d_mania
	if (iRv >= 0)
	{
		tstring	strValue = tstringOf((LPCTSTR)GetProfileString(
			nameSection, nameCWndJikokuhyou_DisplaySecondEkiJikoku));
		if (strValue.empty())
		{
			iRv = -1;	//	DisplaySecondEkiJikoku が指定されていません。
		}
		else
		{
			bDisplaySecondEkiJikoku = (intOf(strValue) != 0);
		}
	}

	//DisplayColonEkiJikoku
	if (iRv >= 0)
	{
		tstring	strValue = tstringOf((LPCTSTR)GetProfileString(
			nameSection, nameCWndJikokuhyou_DisplayColonEkiJikoku));
		if (strValue.empty())
		{
			iRv = -1;	//	DisplayColonEkiJikoku が指定されていません。
		}
		else
		{
			bDisplayColonEkiJikoku = (intOf(strValue) != 0);
		}
	}
	//DisplayParentSyubetsu
	if (iRv >= 0)
	{
		tstring	strValue = tstringOf((LPCTSTR)GetProfileString(
			nameSection, nameDisplayParentSyubetsu));
		if (strValue.empty())
		{
			iRv = -1;	//	DisplayColonEkiJikoku が指定されていません。
		}
		else
		{
			bDisplayParentSyubetsu = (intOf(strValue) != 0);
		}
	}
	//DisplayNoboriLeftToRight
	if (iRv >= 0)
	{
		tstring	strValue = tstringOf((LPCTSTR)GetProfileString(
			nameSection, nameCWndDcdGridOperationTable_DisplayNoboriLeftToRight));
		if (strValue.empty())
		{
			iRv = -1;	//	DisplayNoboriLeftToRight が指定されていません。
		}
		else
		{
			bDisplayNoboriLeftToRight = (intOf(strValue) != 0);
		}
	}
	//DisplayExtensionOperationTable
	if (iRv >= 0)
	{
		tstring	strValue = tstringOf((LPCTSTR)GetProfileString(
			nameSection, nameCWndDcdGridOperationTable_DisplayExtensionOperationTable));
		if (strValue.empty())
		{
			iRv = -1;	//	DisplayExtensionOperationTable が指定されていません。
		}
		else
		{
			bDisplayExtensionOperationTable = (intOf(strValue) != 0);
		}
	}
	//DisplayTrackName
	if (iRv >= 0)
	{
		tstring	strValue = tstringOf((LPCTSTR)GetProfileString(
			nameSection, nameCWndDcdGridOperationTable_DisplayTrackName));
		if (strValue.empty())
		{
			iRv = -1;	//	DisplayTrackName が指定されていません。
		}
		else
		{
			bDisplayTrackName = (intOf(strValue) != 0);
		}
	}
	//DisplayTsuukaEkiJikoku
	if (iRv >= 0)
	{
		tstring	strValue = tstringOf((LPCTSTR)GetProfileString(
			nameSection, nameCWndJikokuhyou_DisplayTsuukaEkiJikoku));
		if (strValue.empty())
		{
			iRv = -1;	//	DisplayTsuukaEkiJikoku が指定されていません。
		}
		else
		{
			bDisplayTsuukaEkiJikoku = (intOf(strValue) != 0);
		}
	}
	// --------------------------------
	if (iRv >= 0)
	{
		pCWndDcdGridOperationTable->setDisplaySecondEkiJikoku(bDisplaySecondEkiJikoku);
		pCWndDcdGridOperationTable->setDisplayColonEkiJikoku(bDisplayColonEkiJikoku);
		pCWndDcdGridOperationTable->setDisplayParentSyubetsu(bDisplayParentSyubetsu);
		pCWndDcdGridOperationTable->setDisplayNoboriLeftToRight(bDisplayNoboriLeftToRight);
		pCWndDcdGridOperationTable->setDisplayExtensionOperationTable(bDisplayExtensionOperationTable);
		pCWndDcdGridOperationTable->setDisplayTrackName(bDisplayTrackName);
		pCWndDcdGridOperationTable->setDisplayTsuukaEkiJikoku(bDisplayTsuukaEkiJikoku);
	}


	return (iRv);
}

const TCHAR nameCWndDcdGridAllOperationTable_OperationSort[] =
_T("AllOperationTable_OperationSort");
const TCHAR nameCWndDcdGridAllOperationTable_DisplayAllRessya[] =
_T("AllOperationTable_DisplayAllRessya");

int CDiagramEditApp::writeCWndDcdGridAllOperationTableViewProp(
	const CWndDcdGridAllOperationTable* pCWndDcdGridAllOperationTable)
{
	int iRv = 0;

	//属性を取得
	bool	bDisplaySecondEkiJikoku = pCWndDcdGridAllOperationTable->getDisplaySecondEkiJikoku();
	bool	bDisplayColonEkiJikoku = pCWndDcdGridAllOperationTable->getDisplayColonEkiJikoku();
	bool	bDisplayParentSyubetsu = pCWndDcdGridAllOperationTable->getDisplayParentSyubetsu();
	bool	bDisplayAllRessya = pCWndDcdGridAllOperationTable->getDisplayAllRessya();
	CWndDcdGridAllOperationTable::EOperationSort eOperationSort = pCWndDcdGridAllOperationTable->getOperationSort();
	bool	bCompareBottom = pCWndDcdGridAllOperationTable->getCompareBottom();
	// --------------------------------


	//DisplaySecondEkiJikoku//add_by_d_mania
	if (iRv >= 0)
	{
		tstring	strValue;
		strValue += stringOf(bDisplaySecondEkiJikoku ? 1 : 0);
		WriteProfileString(nameSection, nameCWndJikokuhyou_DisplaySecondEkiJikoku,
			tstringOf(strValue).c_str());
	}
	//DisplayColonEkiJikoku
	if (iRv >= 0)
	{
		tstring	strValue;
		strValue += stringOf(bDisplayColonEkiJikoku ? 1 : 0);
		WriteProfileString(nameSection, nameCWndJikokuhyou_DisplayColonEkiJikoku,
			tstringOf(strValue).c_str());
	}
	//DisplayParentSyubetsu
	if (iRv >= 0)
	{
		tstring	strValue;
		strValue += stringOf(bDisplayParentSyubetsu ? 1 : 0);
		WriteProfileString(nameSection, nameDisplayParentSyubetsu,
			tstringOf(strValue).c_str());
	}
	//DisplayAllRessya
	if (iRv >= 0)
	{
		tstring	strValue;
		strValue += stringOf(bDisplayAllRessya ? 1 : 0);
		WriteProfileString(nameSection, nameCWndDcdGridAllOperationTable_DisplayAllRessya,
			tstringOf(strValue).c_str());
	}
	//OperationSort
	if (iRv >= 0)
	{
		tstring strValue;
		strValue += stringOf((int)eOperationSort);
		WriteProfileString(nameSection, nameCWndDcdGridAllOperationTable_OperationSort,
			tstringOf(strValue).c_str());
	}
	//CompareBottom
	if (iRv >= 0)
	{
		tstring	strValue;
		strValue += stringOf(bCompareBottom ? 1 : 0);
		WriteProfileString(nameSection, nameCWndJikokuhyou_CompareBottom,
			tstringOf(strValue).c_str());
	}
	return (iRv);
}
int CDiagramEditApp::readCWndDcdGridAllOperationTableViewProp(
	CWndDcdGridAllOperationTable* pCWndDcdGridAllOperationTable)
{
	int iRv = 0;
	bool	bDisplaySecondEkiJikoku = false;
	bool	bDisplayColonEkiJikoku = false;
	bool	bDisplayParentSyubetsu = false;
	bool	bDisplayAllRessya = false;
	CWndDcdGridAllOperationTable::EOperationSort eOperationSort = CWndDcdGridAllOperationTable::EOperationSort_OperationNumber;
	bool	bCompareBottom = false;
	bool	bDisplayNoboriLeftToRight = false;
	bool	bDisplayExtensionOperationTable = false;
	bool	bDisplayTrackName = false;
	bool	bDisplayTsuukaEkiJikoku = false;

	// --------------------------------

	//DisplaySecondEkiJikoku//add_by_d_mania
	if (iRv >= 0)
	{
		tstring	strValue = tstringOf((LPCTSTR)GetProfileString(
			nameSection, nameCWndJikokuhyou_DisplaySecondEkiJikoku));
		if (strValue.empty())
		{
			iRv = -1;	//	DisplaySecondEkiJikoku が指定されていません。
		}
		else
		{
			bDisplaySecondEkiJikoku = (intOf(strValue) != 0);
		}
	}

	//DisplayColonEkiJikoku
	if (iRv >= 0)
	{
		tstring	strValue = tstringOf((LPCTSTR)GetProfileString(
			nameSection, nameCWndJikokuhyou_DisplayColonEkiJikoku));
		if (strValue.empty())
		{
			iRv = -1;	//	DisplayColonEkiJikoku が指定されていません。
		}
		else
		{
			bDisplayColonEkiJikoku = (intOf(strValue) != 0);
		}
	}
	//DisplayParentSyubetsu
	if (iRv >= 0)
	{
		tstring	strValue = tstringOf((LPCTSTR)GetProfileString(
			nameSection, nameDisplayParentSyubetsu));
		if (strValue.empty())
		{
			iRv = -1;	//	DisplayParentSyubetsu が指定されていません。
		}
		else
		{
			bDisplayParentSyubetsu = (intOf(strValue) != 0);
		}
	}
	//DisplayAllRessya
	if (iRv >= 0)
	{
		tstring	strValue = tstringOf((LPCTSTR)GetProfileString(
			nameSection, nameCWndDcdGridAllOperationTable_DisplayAllRessya));
		if (strValue.empty())
		{
			iRv = -1;	//	DisplayAllRessya が指定されていません。
		}
		else
		{
			bDisplayAllRessya = (intOf(strValue) != 0);
		}
	}
	//OperationSort
	if (iRv >= 0)
	{
		tstring	strValue = tstringOf((LPCTSTR)GetProfileString(
			nameSection, nameCWndDcdGridAllOperationTable_OperationSort));
		if (strValue.empty())
		{
			iRv = -1;	//	OperationSort が指定されていません。
		}
		else
		{
			int iValue = intOf(strValue);
			switch (iValue)
			{
			case (int)CWndDcdGridAllOperationTable::EOperationSort_OperationNumber:
				eOperationSort = CWndDcdGridAllOperationTable::EOperationSort_OperationNumber;
				break;
			case (int)CWndDcdGridAllOperationTable::EOperationSort_OutEki:
				eOperationSort = CWndDcdGridAllOperationTable::EOperationSort_OutEki;
				break;
			case (int)CWndDcdGridAllOperationTable::EOperationSort_OutJikoku:
				eOperationSort = CWndDcdGridAllOperationTable::EOperationSort_OutJikoku;
				break;
			case (int)CWndDcdGridAllOperationTable::EOperationSort_InEki:
				eOperationSort = CWndDcdGridAllOperationTable::EOperationSort_InEki;
				break;
			case (int)CWndDcdGridAllOperationTable::EOperationSort_InJikoku:
				eOperationSort = CWndDcdGridAllOperationTable::EOperationSort_InJikoku;
				break;
			}
		}
	}
	//CompareBottom
	if (iRv >= 0)
	{
		tstring	strValue = tstringOf((LPCTSTR)GetProfileString(
			nameSection, nameCWndJikokuhyou_CompareBottom));
		if (strValue.empty())
		{
			iRv = -1;	//	CompareBottom が指定されていません。
		}
		else
		{
			bCompareBottom = (intOf(strValue) != 0);
		}
	}
	//DisplayNoboriLeftToRight
	if (iRv >= 0)
	{
		tstring	strValue = tstringOf((LPCTSTR)GetProfileString(
			nameSection, nameCWndDcdGridOperationTable_DisplayNoboriLeftToRight));
		if (strValue.empty())
		{
			iRv = -1;	//	DisplayNoboriLeftToRight が指定されていません。
		}
		else
		{
			bDisplayNoboriLeftToRight = (intOf(strValue) != 0);
		}
	}
	//DisplayExtensionOperationTable
	if (iRv >= 0)
	{
		tstring	strValue = tstringOf((LPCTSTR)GetProfileString(
			nameSection, nameCWndDcdGridOperationTable_DisplayExtensionOperationTable));
		if (strValue.empty())
		{
			iRv = -1;	//	DisplayExtensionOperationTable が指定されていません。
		}
		else
		{
			bDisplayExtensionOperationTable = (intOf(strValue) != 0);
		}
	}
	//DisplayTrackName
	if (iRv >= 0)
	{
		tstring	strValue = tstringOf((LPCTSTR)GetProfileString(
			nameSection, nameCWndDcdGridOperationTable_DisplayTrackName));
		if (strValue.empty())
		{
			iRv = -1;	//	DisplayTrackName が指定されていません。
		}
		else
		{
			bDisplayTrackName = (intOf(strValue) != 0);
		}
	}
	//DisplayTsuukaEkiJikoku
	if (iRv >= 0)
	{
		tstring	strValue = tstringOf((LPCTSTR)GetProfileString(
			nameSection, nameCWndJikokuhyou_DisplayTsuukaEkiJikoku));
		if (strValue.empty())
		{
			iRv = -1;	//	DisplayTsuukaEkiJikoku が指定されていません。
		}
		else
		{
			bDisplayTsuukaEkiJikoku = (intOf(strValue) != 0);
		}
	}
	// --------------------------------
	if (iRv >= 0)
	{
		pCWndDcdGridAllOperationTable->setDisplaySecondEkiJikoku(bDisplaySecondEkiJikoku);
		pCWndDcdGridAllOperationTable->setDisplayColonEkiJikoku(bDisplayColonEkiJikoku);
		pCWndDcdGridAllOperationTable->setDisplayParentSyubetsu(bDisplayParentSyubetsu);
		pCWndDcdGridAllOperationTable->setDisplayAllRessya(bDisplayAllRessya);
		pCWndDcdGridAllOperationTable->setOperationSort(eOperationSort);
		pCWndDcdGridAllOperationTable->setCompareBottom(bCompareBottom);
		pCWndDcdGridAllOperationTable->setDisplayNoboriLeftToRight(bDisplayNoboriLeftToRight);
		pCWndDcdGridAllOperationTable->setDisplayExtensionOperationTable(bDisplayExtensionOperationTable);
		pCWndDcdGridAllOperationTable->setDisplayTrackName(bDisplayTrackName);
		pCWndDcdGridAllOperationTable->setDisplayTsuukaEkiJikoku(bDisplayTsuukaEkiJikoku);
	}

	return (iRv);
}

const TCHAR nameCWndDcdGridEkiProp_AdjustByEkijikokukeisiki[] = 
	_T( "EkiProp_AdjustByEkijikokukeisiki" ) ;
const TCHAR nameCWndDcdGridEki_DisplaySettingMode[] =
_T("Eki_DisplaySettingMode");


int CDiagramEditApp::writeCWndDcdGridEkiProp( 
		const CWndDcdGridEki* pCWndDcdGridEki ) 
{
	int iRv = 0 ;

	//属性を取得
	bool bAdjustByEkijikokukeisiki = pCWndDcdGridEki->getAdjustByEkijikokukeisiki() ;
	bool bDisplaySettingMode = pCWndDcdGridEki->getDisplaySettingMode();
	// --------------------------------

	//EkiProp_AdjustByEkijikokukeisiki
	if ( iRv >= 0 )
	{
		tstring strValue ;
		strValue += stringOf( bAdjustByEkijikokukeisiki ? 1:0 ) ;
		WriteProfileString( nameSection , nameCWndDcdGridEkiProp_AdjustByEkijikokukeisiki ,
			tstringOf( strValue ).c_str() ) ;
	}

	//Eki_DisplaySettingMode
	if (iRv >= 0)
	{
		tstring strValue;
		strValue += stringOf(bDisplaySettingMode ? 1 : 0);
		WriteProfileString(nameSection, nameCWndDcdGridEki_DisplaySettingMode,
			tstringOf(strValue).c_str());
	}


	return iRv ;
}
int CDiagramEditApp::readCWndDcdGridEkiProp( 
		CWndDcdGridEki* pCWndDcdGridEki ) 
{
	int iRv = 0 ;
	bool	bAdjustByEkijikokukeisiki = true  ;
	bool bDisplaySettingMode = false;

	//EkiProp_AdjustByEkijikokukeisiki
	if ( iRv >= 0 )
	{
		tstring	strValue = tstringOf( (LPCTSTR)GetProfileString( 
			nameSection , nameCWndDcdGridEkiProp_AdjustByEkijikokukeisiki ) ) ;
		if ( strValue.empty() )
		{
			iRv = -1 ;	//	EkiProp_AdjustByEkijikokukeisiki が指定されていません。
		}
		else
		{
			bAdjustByEkijikokukeisiki = ( intOf( strValue ) != 0 ) ;
		}
	}
	//Eki_DisplaySettingMode
	if (iRv >= 0)
	{
		tstring	strValue = tstringOf((LPCTSTR)GetProfileString(
			nameSection, nameCWndDcdGridEki_DisplaySettingMode));
		if (strValue.empty())
		{
			iRv = -2;	//	Eki_DisplaySettingMode が指定されていません。
		}
		else
		{
			bDisplaySettingMode = (intOf(strValue) != 0);
		}
	}
	// --------------------------------
	if ( iRv >= 0 )
	{
		pCWndDcdGridEki->setAdjustByEkijikokukeisiki( bAdjustByEkijikokukeisiki ) ;
		pCWndDcdGridEki->setDisplaySettingMode(bDisplaySettingMode);
	}
	return iRv ;
}

const TCHAR nameDisplayTrack[] =
_T("DisplayTrack");
const TCHAR nameDisplayIsShihatsu[] =
_T("DisplayIsShihatsu");
const TCHAR nameDisplayClassChange[] =
_T("DisplayClassChange");

int CDiagramEditApp::writeCWndDcdGridEkiJikokuhyouProp(
	const CWndDcdGridEkiJikokuhyou* pCWndDcdGridEkiJikokuhyou)
{
	int iRv = 0;

	//属性を取得
	bool	bDisplayParentSyubetsu = pCWndDcdGridEkiJikokuhyou->getDisplayParentSyubetsu();
	bool	bDisplayTrack = pCWndDcdGridEkiJikokuhyou->getDisplayTrack();
	bool	bDisplayIsShihatsu = pCWndDcdGridEkiJikokuhyou->getDisplayIsShihatsu();
	bool	bDisplayClassChange = pCWndDcdGridEkiJikokuhyou->getDisplayClassChange();
	// --------------------------------

	//DisplayParentSyubetsu
	if (iRv >= 0)
	{
		tstring	strValue;
		strValue += stringOf(bDisplayParentSyubetsu ? 1 : 0);
		WriteProfileString(nameSection, nameDisplayParentSyubetsu,
			tstringOf(strValue).c_str());
	}
	//DisplayTrack
	if (iRv >= 0)
	{
		tstring	strValue;
		strValue += stringOf(bDisplayTrack ? 1 : 0);
		WriteProfileString(nameSection, nameDisplayTrack,
			tstringOf(strValue).c_str());
	}
	//DisplayIsShihatsu
	if (iRv >= 0)
	{
		tstring	strValue;
		strValue += stringOf(bDisplayIsShihatsu ? 1 : 0);
		WriteProfileString(nameSection, nameDisplayIsShihatsu,
			tstringOf(strValue).c_str());
	}
	//DisplayClassChange
	if (iRv >= 0)
	{
		tstring	strValue;
		strValue += stringOf(bDisplayClassChange ? 1 : 0);
		WriteProfileString(nameSection, nameDisplayClassChange,
			tstringOf(strValue).c_str());
	}


	return iRv;
}
int CDiagramEditApp::readCWndDcdGridEkiJikokuhyouProp(
	CWndDcdGridEkiJikokuhyou* pCWndDcdGridEkiJikokuhyou)
{
	int iRv = 0;
	bool bDisplayParentSyubetsu = false;
	bool bDisplayTrack = false;
	bool bDisplayIsShihatsu = false;
	bool bDisplayClassChange = false;

	//DisplayParentSyubetsu
	if (iRv >= 0)
	{
		tstring	strValue = tstringOf((LPCTSTR)GetProfileString(
			nameSection, nameDisplayParentSyubetsu));
		if (strValue.empty())
		{
			iRv = -1;	//	DisplayParentSyubetsu が指定されていません。
		}
		else
		{
			bDisplayParentSyubetsu = (intOf(strValue) != 0);
		}
	}
	//DisplayTrack
	if (iRv >= 0)
	{
		tstring	strValue = tstringOf((LPCTSTR)GetProfileString(
			nameSection, nameDisplayTrack));
		if (strValue.empty())
		{
			iRv = -1;	//	DisplayTrack が指定されていません。
		}
		else
		{
			bDisplayTrack = (intOf(strValue) != 0);
		}
	}
	//DisplayIsShihatsu
	if (iRv >= 0)
	{
		tstring	strValue = tstringOf((LPCTSTR)GetProfileString(
			nameSection, nameDisplayIsShihatsu));
		if (strValue.empty())
		{
			iRv = -1;	//	DisplayIsShihatsu が指定されていません。
		}
		else
		{
			bDisplayIsShihatsu = (intOf(strValue) != 0);
		}
	}
	//DisplayClassChange
	if (iRv >= 0)
	{
		tstring	strValue = tstringOf((LPCTSTR)GetProfileString(
			nameSection, nameDisplayClassChange));
		if (strValue.empty())
		{
			iRv = -1;	//	DisplayClassChange が指定されていません。
		}
		else
		{
			bDisplayClassChange = (intOf(strValue) != 0);
		}
	}
	// --------------------------------
	if (iRv >= 0)
	{
		pCWndDcdGridEkiJikokuhyou->setDisplayParentSyubetsu(bDisplayParentSyubetsu);
		pCWndDcdGridEkiJikokuhyou->setDisplayTrack(bDisplayTrack);
		pCWndDcdGridEkiJikokuhyou->setDisplayIsShihatsu(bDisplayIsShihatsu);
		pCWndDcdGridEkiJikokuhyou->setDisplayClassChange(bDisplayClassChange);
	}
	return iRv;
}

int CDiagramEditApp::readCWndDcdGridEkiJikokuhyouListProp(
	CWndDcdGridEkiJikokuhyouList* pCWndDcdGridEkiJikokuhyouList)
{
	int iRv = 0;
	bool bDisplayParentSyubetsu = false;
	bool bDisplayTrack = false;
	bool bDisplayIsShihatsu = false;
	bool bDisplayClassChange = false;

	//DisplayParentSyubetsu
	if (iRv >= 0)
	{
		tstring	strValue = tstringOf((LPCTSTR)GetProfileString(
			nameSection, nameDisplayParentSyubetsu));
		if (strValue.empty())
		{
			iRv = -1;	//	DisplayParentSyubetsu が指定されていません。
		}
		else
		{
			bDisplayParentSyubetsu = (intOf(strValue) != 0);
		}
	}
	//DisplayTrack
	if (iRv >= 0)
	{
		tstring	strValue = tstringOf((LPCTSTR)GetProfileString(
			nameSection, nameDisplayTrack));
		if (strValue.empty())
		{
			iRv = -1;	//	DisplayTrack が指定されていません。
		}
		else
		{
			bDisplayTrack = (intOf(strValue) != 0);
		}
	}
	//DisplayIsShihatsu
	if (iRv >= 0)
	{
		tstring	strValue = tstringOf((LPCTSTR)GetProfileString(
			nameSection, nameDisplayIsShihatsu));
		if (strValue.empty())
		{
			iRv = -1;	//	DisplayIsShihatsu が指定されていません。
		}
		else
		{
			bDisplayIsShihatsu = (intOf(strValue) != 0);
		}
	}
	//DisplayClassChange
	if (iRv >= 0)
	{
		tstring	strValue = tstringOf((LPCTSTR)GetProfileString(
			nameSection, nameDisplayClassChange));
		if (strValue.empty())
		{
			iRv = -1;	//	DisplayClassChange が指定されていません。
		}
		else
		{
			bDisplayClassChange = (intOf(strValue) != 0);
		}
	}
	// --------------------------------
	if (iRv >= 0)
	{
		pCWndDcdGridEkiJikokuhyouList->setDisplayParentSyubetsu(bDisplayParentSyubetsu);
		pCWndDcdGridEkiJikokuhyouList->setDisplayTrack(bDisplayTrack);
		pCWndDcdGridEkiJikokuhyouList->setDisplayIsShihatsu(bDisplayIsShihatsu);
		pCWndDcdGridEkiJikokuhyouList->setDisplayClassChange(bDisplayClassChange);
	}
	return iRv;
}

const TCHAR nameCDiagramEdit_BackupEnable[] =
_T("BackupEnable");
const TCHAR nameCDiagramEdit_WindowPlacementRestore[] =
_T("WindowPlacementRestore");

int CDiagramEditApp::writeCDiagramEditProp()
{
	int iRv = 0;

	//属性を取得
	bool	bBackupEnable = getCDiagramEditDoc()->getBackupEnable();
	bool	bWindowPlacementRestore = getCDiagramEditDoc()->getWindowPlacementRestore();
	// --------------------------------


	//BackupEnable
	if (iRv >= 0)
	{
		tstring	strValue;
		strValue += stringOf(bBackupEnable ? 1 : 0);
		WriteProfileString(nameSection, nameCDiagramEdit_BackupEnable,
			tstringOf(strValue).c_str());
	}
	//WindowPlacementRestore
	if (iRv >= 0)
	{
		tstring	strValue;
		strValue += stringOf(bWindowPlacementRestore ? 1 : 0);
		WriteProfileString(nameSection, nameCDiagramEdit_WindowPlacementRestore,
			tstringOf(strValue).c_str());
	}
	return (iRv);
}

int CDiagramEditApp::readCDiagramEditProp()
{
	int iRv = 0;
	bool	bBackupEnable = false;
	bool	bWindowPlacementRestore = false;
	//BackupEnable
	if (iRv >= 0)
	{
		tstring	strValue = tstringOf((LPCTSTR)GetProfileString(
			nameSection, nameCDiagramEdit_BackupEnable));
		if (strValue.empty())
		{
			iRv = -1;	//	BackupEnable が指定されていません。
		}
		else
		{
			bBackupEnable = (intOf(strValue) != 0);
		}
	}
	//WindowPlacementRestore
	if (iRv >= 0)
	{
		tstring	strValue = tstringOf((LPCTSTR)GetProfileString(
			nameSection, nameCDiagramEdit_WindowPlacementRestore));
		if (strValue.empty())
		{
			iRv = -1;	//	WindowPlacementRestore が指定されていません。
		}
		else
		{
			bWindowPlacementRestore = (intOf(strValue) != 0);
		}
	}
	// --------------------------------
	if (iRv >= 0)
	{
		getCDiagramEditDoc()->setBackupEnable(bBackupEnable);
		getCDiagramEditDoc()->setWindowPlacementRestore(bWindowPlacementRestore);
	}


	return (iRv);
}

const TCHAR nameCWndAllOperationTable2_AllOperationTable2PosDgr[] = _T("AllOperationTable2PosDgr");
const TCHAR nameCWndAllOperationTable2_DcdPerDgrX[] = _T("AllOperationTable2DcdPerDgrX");
//const TCHAR nameCWndAllOperationTable2_DcdPerDgrY[] = _T("AllOperationTable2DcdPerDgrY");

const TCHAR nameCWndAllOperationTable2_VlineMode[] = _T("AllOperationTable2VlineMode");
const TCHAR nameCWndAllOperationTable2_DisplayEkimeiJikoku[] =
_T("AllOperationTable2DisplayEkimeiJikoku");
const TCHAR nameCWndAllOperationTable2_DisplayRessyabangou[] =
_T("AllOperationTable2DisplayRessyabangou");
const TCHAR nameCWndAllOperationTable2_DisplaySyubetsuRyakusyou[] =
_T("AllOperationTable2DisplaySyubetsuRyakusyou");
const TCHAR nameCWndAllOperationTable2_DisplayRessyamei[] =
_T("AllOperationTable2DisplayRessyamei");
const TCHAR nameCWndAllOperationTable2_DisplayJikokuMinute[] =
_T("AllOperationTable2DisplayJikokuMinute");
const TCHAR nameCWndAllOperationTable2_KeepZoneDgrOnSize[] =
_T("AllOperationTable2KeepZoneDgrOnSize");
//const TCHAR nameDisplayParentSyubetsu[] =
//_T("AllOperationTable2DisplayParentSyubetsu");

int CDiagramEditApp::writeCWndAllOperationTable2ViewProp(const CWndAllOperationTable2* pCWndAllOperationTable2)
{
	return -1;
	int iRv = 0;

	//属性を取得
	CdDcdPosXy	posPosDgr = pCWndAllOperationTable2->getPosDgr();
	double	dDcdPerDgrX = pCWndAllOperationTable2->getDcdPerDgrX();
	//double	dDcdPerDgrY = pCWndAllOperationTable2->getDcdPerDgrY();

	int idxVlineMode = pCWndAllOperationTable2->getVlineMode();
	bool	bDisplayEkimeiJikoku = pCWndAllOperationTable2->getDisplayEkimeiJikoku();
	bool	bDisplayRessyabangou = pCWndAllOperationTable2->getDisplayRessyabangou();
	bool	bDisplaySyubetsuRyakusyou = pCWndAllOperationTable2->getDisplaySyubetsuRyakusyou();
	bool	bDisplayRessyamei = pCWndAllOperationTable2->getDisplayRessyamei();
	bool	bDisplayJikokuMinute = pCWndAllOperationTable2->getDisplayJikokuMinute();
	bool bKeepZoneDgrOnSize = pCWndAllOperationTable2->getKeepZoneDgrOnSize();
	bool bDisplayParentSyubetsu = pCWndAllOperationTable2->getDisplayParentSyubetsu();
	// --------------------------------
	//DiagramPosDgr
	if (iRv >= 0)
	{
		tstring	strValue;
		strValue += stringOf(posPosDgr.getX());
		strValue += ',';
		strValue += stringOf(posPosDgr.getY());
		WriteProfileString(
			nameSection,
			nameCWndAllOperationTable2_AllOperationTable2PosDgr,
			strValue.c_str());
	}
	//"DcdPerDgrX" ;
	{
		tstring	strValue;
		strValue += stringOf(dDcdPerDgrX);
		WriteProfileString(
			nameSection,
			nameCWndAllOperationTable2_DcdPerDgrX,
			strValue.c_str());
	}

	//"DcdPerDgrY" ;
	//{
	//	tstring	strValue;
	//	strValue += stringOf(dDcdPerDgrY);
	//	WriteProfileString(
	//		nameSection,
	//		nameCWndDiagram_DcdPerDgrY,
	//		strValue.c_str());
	//}


	//DiagramVlineMode
	if (iRv >= 0) {
		tstring	strValue;
		strValue += stringOf(idxVlineMode);
		WriteProfileString(nameSection, nameCWndAllOperationTable2_VlineMode,
			strValue.c_str());
	}

	//DisplayEkimeiJikoku
	if (iRv >= 0) {
		tstring	strValue;
		strValue += stringOf(bDisplayRessyabangou);
		WriteProfileString(nameSection, nameCWndAllOperationTable2_DisplayEkimeiJikoku,
			strValue.c_str());
	}

	//DisplayRessyabangou
	if (iRv >= 0) {
		tstring	strValue;
		strValue += stringOf(bDisplayRessyabangou);
		WriteProfileString(nameSection, nameCWndAllOperationTable2_DisplayRessyabangou,
			strValue.c_str());
	}

	//DisplaySyubetsuRyakusyou
	if (iRv >= 0) {
		tstring	strValue;
		strValue += stringOf(bDisplaySyubetsuRyakusyou);
		WriteProfileString(nameSection, nameCWndAllOperationTable2_DisplaySyubetsuRyakusyou,
			strValue.c_str());
	}

	//DisplayRessyamei
	if (iRv >= 0) {
		tstring	strValue;
		strValue += stringOf(bDisplayRessyamei);
		WriteProfileString(nameSection, nameCWndAllOperationTable2_DisplayRessyamei,
			strValue.c_str());
	}

	//DisplayJikokuMinute
	if (iRv >= 0) {
		tstring	strValue;
		strValue += stringOf(bDisplayJikokuMinute);
		WriteProfileString(nameSection, nameCWndAllOperationTable2_DisplayJikokuMinute,
			strValue.c_str());
	}

	//DiagramKeepZoneDgrOnSize
	if (iRv >= 0)
	{
		tstring strValue = (bKeepZoneDgrOnSize ? _T("1") : _T("0"));
		WriteProfileString(nameSection, nameCWndDiagram_KeepZoneDgrOnSize,
			strValue.c_str());
	}
	//DisplayParentSyubetsu
	if (iRv >= 0)
	{
		tstring strValue = (bDisplayParentSyubetsu ? _T("1") : _T("0"));
		WriteProfileString(nameSection, nameDisplayParentSyubetsu,
			strValue.c_str());
	}
	return (iRv);
}

int CDiagramEditApp::readCWndAllOperationTable2ViewProp(CWndAllOperationTable2* pCWndAllOperationTable2)
{
	return -1;
	int iRv = 0;

	CdDcdPosXy	posPosDgr(0, 0);
	double	dDcdPerDgrX = CDcdAllOperationTable::DEFAULT_DCD_PER_DGR_X();
	double	dDcdPerDgrY = CDcdAllOperationTable::DEFAULT_DCD_PER_DGR_Y();

	int idxVlineMode = 1;
	bool bDisplayEkimeiJikoku= false;
	bool bDisplayRessyabangou = false;
	bool bDisplaySyubetsuRyakusyou = false;
	bool bDisplayRessyamei = false;
	bool bDisplayJikokuMinute = false;
	bool bKeepZoneDgrOnSize = false;
	bool bDisplayParentSyubetsu = false;
	// --------------------------------
	//DiagramPosDgr
	if (iRv >= 0)
	{
		tstring	strValue = GetProfileString(nameSection,
			nameCWndAllOperationTable2_AllOperationTable2PosDgr);
		deque<tstring>	contstrValue =
			splitc< deque< tstring > >(',', strValue);
		if (contstrValue.size() != 2)
		{
			iRv = -1;	//	DiagramPosDgr が指定されていません。
		}
		else
		{
			int iXPos = intOf(contstrValue[0]);
			int iYPos = intOf(contstrValue[1]);
			posPosDgr.setX(iXPos).setY(iYPos);
		}
	}
	//DcdPerDgrX
	if (iRv >= 0) {
		tstring	strValue = GetProfileString(nameSection,
			nameCWndAllOperationTable2_DcdPerDgrX);
		if (strValue.empty()) {
			iRv = -2;	//	DcdPerDgrX が指定されていません。
		}
		else {
			dDcdPerDgrX = doubleOf(strValue);
		}
	}
	//DcdPerDgrY
	//if (iRv >= 0) {
	//	tstring	strValue = GetProfileString(nameSection,
	//		nameCWndDiagram_DcdPerDgrY);
	//	if (strValue.empty()) {
	//		iRv = -2;	//	DcdPerDgrY が指定されていません。
	//	}
	//	else {
	//		dDcdPerDgrY = doubleOf(strValue);
	//	}
	//}



	//DiagramVlineMode
	if (iRv >= 0) {
		tstring	strValue = GetProfileString(nameSection,
			nameCWndAllOperationTable2_VlineMode);
		if (strValue.empty()) {
			iRv = -2;	//	DiagramVlineMode が指定されていません。
		}
		else {
			idxVlineMode = intOf(strValue);
		}
	}

	//DisplayEkimeiJikoku
	if (iRv >= 0)
	{
		tstring	strValue = GetProfileString(nameSection,
			nameCWndAllOperationTable2_DisplayEkimeiJikoku);
		if (strValue.empty())
		{
			iRv = -3;	//	DisplayEkimeiJikoku が指定されていません。
		}
		else
		{
			bDisplayEkimeiJikoku = (intOf(strValue) != 0);
		}
	}

	//DisplayRessyabangou
	if (iRv >= 0)
	{
		tstring	strValue = GetProfileString(nameSection,
			nameCWndAllOperationTable2_DisplayRessyabangou);
		if (strValue.empty())
		{
			iRv = -3;	//	DisplayRessyabangou が指定されていません。
		}
		else
		{
			bDisplayRessyabangou = (intOf(strValue) != 0);
		}
	}

	//DisplaySyubetsuRyakusyou
	if (iRv >= 0) {
		tstring	strValue = GetProfileString(nameSection,
			nameCWndAllOperationTable2_DisplaySyubetsuRyakusyou);
		if (strValue.empty()) {
			iRv = -10;	//	DisplaySyubetsuRyakusyou が指定されていません。
		}
		else {
			bDisplaySyubetsuRyakusyou = (intOf(strValue) != 0);
		}
	}

	//DisplayRessyamei
	if (iRv >= 0) {
		tstring	strValue = GetProfileString(nameSection,
			nameCWndAllOperationTable2_DisplayRessyamei);
		if (strValue.empty()) {
			iRv = -4;	//	DisplayRessyamei が指定されていません。
		}
		else {
			bDisplayRessyamei = (intOf(strValue) != 0);
		}
	}

	//DisplayJikokuMinute
	if (iRv >= 0) {
		tstring	strValue = GetProfileString(nameSection,
			nameCWndAllOperationTable2_DisplayJikokuMinute);
		if (strValue.empty()) {
			iRv = -11;	//	DisplayJikokuMinute が指定されていません。
		}
		else {
			bDisplayJikokuMinute = (intOf(strValue) != 0);
		}
	}
	//DiagramKeepZoneDgrOnSize
	if (iRv >= 0)
	{
		tstring	strValue = GetProfileString(
			nameSection, nameCWndDiagram_KeepZoneDgrOnSize);
		if (strValue.empty())
		{
			iRv = -8;	//	KeepZoneDgrOnSize が指定されていません。
		}
		else
		{
			bKeepZoneDgrOnSize = (intOf(strValue) != 0);
		}
	}
	//DisplayParentSyubetsu
	if (iRv >= 0)
	{
		tstring	strValue = GetProfileString(
			nameSection, nameDisplayParentSyubetsu);
		if (strValue.empty())
		{
			iRv = -9;	//	DisplayParentSyubetsu が指定されていません。
		}
		else
		{
			bDisplayParentSyubetsu = (intOf(strValue) != 0);
		}
	}
	// --------------------------------
	if (iRv >= 0)
	{
		pCWndAllOperationTable2->setPosDgr(posPosDgr);
		pCWndAllOperationTable2->setDcdPerDgrX(dDcdPerDgrX);
		//pCWndAllOperationTable2->setDcdPerDgrY(dDcdPerDgrY);

		pCWndAllOperationTable2->setVlineMode(idxVlineMode);
		pCWndAllOperationTable2->setDisplayEkimeiJikoku(bDisplayEkimeiJikoku);
		pCWndAllOperationTable2->setDisplayRessyabangou(bDisplayRessyabangou);
		pCWndAllOperationTable2->setDisplaySyubetsuRyakusyou(bDisplaySyubetsuRyakusyou);
		pCWndAllOperationTable2->setDisplayRessyamei(bDisplayRessyamei);
		pCWndAllOperationTable2->setDisplayJikokuMinute(bDisplayJikokuMinute);
		pCWndAllOperationTable2->setKeepZoneDgrOnSize(bKeepZoneDgrOnSize);
		pCWndAllOperationTable2->setDisplayParentSyubetsu(bDisplayParentSyubetsu);
	}

	return (iRv);
}

// ----------------------------------------------------------------
//	MFC
// ----------------------------------------------------------------


BEGIN_MESSAGE_MAP(CDiagramEditApp, CHidemdiApp)
	//{{AFX_MSG_MAP(CDiagramEditApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_COMMAND(ID_FILE_PrintPageProp, OnFILEPrintPageProp)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_HELP, OnHelp)
//	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
//	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	//}}AFX_MSG_MAP
	// 標準のファイル基本ドキュメント コマンド
	ON_COMMAND(ID_FILE_NEW, CHidemdiApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CHidemdiApp::OnFileOpen)
	// 標準の印刷セットアップ コマンド
	ON_COMMAND(ID_FILE_PRINT_SETUP, CHidemdiApp::OnFilePrintSetup)
//	ON_COMMAND(ID_EDIT_REDO, &CDiagramEditApp::OnEditRedo)
//	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, &CDiagramEditApp::OnUpdateEditRedo)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiagramEditApp クラスの構築

CDiagramEditApp::CDiagramEditApp()
{
	m_pdoctmplEki = NULL ;
	m_pdoctmplResssyasyubetsu = NULL ;
	m_pdoctmplJikokuhyou = NULL ;
	m_pdoctmplDiagram = NULL ;
	m_pdoctmplComment = NULL ;
	m_pdoctmplOperationTable = NULL;
	m_pdoctmplAllOperationTable = NULL;
	m_pdoctmplAllOperationTable2 = NULL;
	m_pdoctmplEkiJikokuhyou = NULL;
	m_pdoctmplEkiJikokuhyouList = NULL;
	m_pdoctmplInOutLinkCodeList = NULL;
	m_pdoctmplCrossingCheck = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CDiagramEditApp オブジェクト

CDiagramEditApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDiagramEditApp クラスの初期化

BOOL CDiagramEditApp::InitInstance()
{
	// 標準的な初期化処理
	// もしこれらの機能を使用せず、実行ファイルのサイズを小さく
	// したければ以下の特定の初期化ルーチンの中から不必要なもの
	// を削除してください。

#ifdef _AFXDLL
	//VisualStudio 2008
	//	warning C4996: 'CWinApp::Enable3dControls': 
	//	CWinApp::Enable3dControlsStatic is no longer needed. 
	//	You should remove this call.
	//Enable3dControls();		// 共有 DLL の中で MFC を使用する場合にはここを呼び出してください。
#else
	//VisualStudio 2008
	//	warning C4996: 'CWinApp::Enable3dControlsStatic': 
	//	CWinApp::Enable3dControlsStatic is no longer needed. 
	//	You should remove this call.
	//Enable3dControlsStatic();	// MFC と静的にリンクしている場合にはここを呼び出してください。
#endif

	// --------------------------------
	//	LocalAppData ディレクトリを作成
	// --------------------------------
	//ベータ版ではコメントアウト
	{
		CString	strLocalAppdataOudiaFolder ;
		strLocalAppdataOudiaFolder = makeLocalAppdataFilename( _T( "" ) ) ;

		//strLocalAppdataOudiaFolder = OuDiaのLocalAppDataフォルダ。
		//	末尾には '¥' はありません。
		//	このディレクトリは、作成されています。

		OuLib::Dir::mkdirs( tstringOf( (LPCTSTR)strLocalAppdataOudiaFolder ) );
	}
	//
	


	// --------------------------------
	//	LogMsg() ファイルのファイル名設定
	// --------------------------------
	{
		logmsg_setFilename(makeLocalAppdataFilename(_T("OuDiaSecond.log")));
		//logmsg_setFilename( makeProgramDirFilename( _T("OuDiaSecond.log") ) ) ; //ベータ版ではこれを使用

		//	LogLevel は、このあとに 
		//	.ini ファイルの[AppProp]LogLevel から読み出します。
		logmsg_setLogLevel( 2 ) ;
	}

	// --------------------------------
	//	.Iniファイルのファイル名設定
	// --------------------------------
	//SetRegistryKey(_T("DiagramEdit"));
	{
		free((void*)m_pszProfileName);
		m_pszProfileName = _tcsdup(makeLocalAppdataFilename(_T("OuDiaSecondV2.ini")));
		//m_pszProfileName=_tcsdup( makeProgramDirFilename( _T("OuDiaSecondV2.ini") ) ); //ベータ版ではこれを使用
	}
	LoadStdProfileSettings();  // 標準の INI ファイルのオプションをローﾄﾞします (MRU を含む)

	// --------------------------------
	//	.Iniファイルの読み込み
	// --------------------------------
	{
		//	印刷ページ設定
		CString aStr = GetProfileString( nameSection , namePrintPageProp ) ;
		m_CdPrintPageProp.decode( (LPCTSTR)aStr ) ;

		//	LogLevel設定
		logmsg_setLogLevel( GetProfileInt( nameSection , nameLogLevel , 0 ) );
		
	}

	// ----------------------------------------------------------------
	// アプリケーション用のドキュメント テンプレートを登録します。ドキュメント テンプレート
	//  はドキュメント、フレーム ウィンドウとビューを結合するために機能します。

	{
		CHidemdiRootDoctmpl* pDocTemplate;
		pDocTemplate = new CDiagramEditDoctmpl(
			IDR_DIATYPE,
			RUNTIME_CLASS(CDiagramEditDoc));
		AddDocTemplate(pDocTemplate);
		RegisterRootDoctmpl( pDocTemplate ) ;
	}

	{
		CHidemdiSubDoctmpl* pNewDocTemplate = new CHidemdiDoctmplDocstrAlone(
			IDR_DOCVIEW_Eki,
			RUNTIME_CLASS(CEkiDoc),		// ドキュメント クラス
			RUNTIME_CLASS(CMDIChildWnd),		// フレーム クラス
			RUNTIME_CLASS(CEkiView));	// ビュー クラス
		AddDocTemplate(pNewDocTemplate);
		
		m_pdoctmplEki = pNewDocTemplate ;
			//	このドキュメントテンプレートを、アプリケーションクラスの
			//	メンバ変数に保存
	}

	{
		CHidemdiSubDoctmpl* pNewDocTemplate = new CHidemdiDoctmplDocstrAlone(
			IDR_DOCVIEW_Ressyasyubetsu,
			RUNTIME_CLASS(CRessyasyubetsuDoc),		// ドキュメント クラス
			RUNTIME_CLASS(CMDIChildWnd),		// フレーム クラス
			RUNTIME_CLASS(CRessyasyubetsuView));	// ビュー クラス
		AddDocTemplate(pNewDocTemplate);
		
		m_pdoctmplResssyasyubetsu = pNewDocTemplate ;
			//	このドキュメントテンプレートを、アプリケーションクラスの
			//	メンバ変数に保存
	}


	{
		CHidemdiSubDoctmpl* pNewDocTemplate = new CHidemdiDoctmplDocstrAlone(
			IDR_DOCVIEW_Jikokuhyou,
			RUNTIME_CLASS(CJikokuhyouDoc),		// ドキュメント クラス
			RUNTIME_CLASS(CMDIChildWnd),		// フレーム クラス
			RUNTIME_CLASS(CJikokuhyouView));	// ビュー クラス
		AddDocTemplate(pNewDocTemplate);
		
		m_pdoctmplJikokuhyou = pNewDocTemplate ;
			//	このドキュメントテンプレートを、アプリケーションクラスの
			//	メンバ変数に保存
	}
	{
		CHidemdiSubDoctmpl* pNewDocTemplate = new CHidemdiDoctmplDocstrAlone(
			IDR_DOCVIEW_Diagram,
			RUNTIME_CLASS(CDedDiagramDoc),		// ドキュメント クラス
			RUNTIME_CLASS(CMDIChildWnd),		// フレーム クラス
			RUNTIME_CLASS(CDedDiagramView));	// ビュー クラス
		AddDocTemplate(pNewDocTemplate);
		
		m_pdoctmplDiagram = pNewDocTemplate ;
			//	このドキュメントテンプレートを、アプリケーションクラスの
			//	メンバ変数に保存
	}
	{
		CHidemdiSubDoctmpl* pNewDocTemplate = new CHidemdiDoctmplDocstrAlone(
			IDR_DOCVIEW_Comment,
			RUNTIME_CLASS(CDedCommentDoc),		// ドキュメント クラス
			RUNTIME_CLASS(CMDIChildWnd),		// フレーム クラス
			RUNTIME_CLASS(CDedCommentView));	// ビュー クラス
		AddDocTemplate(pNewDocTemplate);
		
		m_pdoctmplComment = pNewDocTemplate ;
			//	このドキュメントテンプレートを、アプリケーションクラスの
			//	メンバ変数に保存
	}
	{
		CHidemdiSubDoctmpl* pNewDocTemplate = new CHidemdiDoctmplDocstrAlone(
			IDR_DOCVIEW_OperationTable,
			RUNTIME_CLASS(COperationTableDoc),		// ドキュメント クラス
			RUNTIME_CLASS(CMDIChildWnd),		// フレーム クラス
			RUNTIME_CLASS(COperationTableView));	// ビュー クラス
		AddDocTemplate(pNewDocTemplate);

		m_pdoctmplOperationTable = pNewDocTemplate;
		//	このドキュメントテンプレートを、アプリケーションクラスの
		//	メンバ変数に保存
	}
	{
		CHidemdiSubDoctmpl* pNewDocTemplate = new CHidemdiDoctmplDocstrAlone(
			IDR_DOCVIEW_AllOperationTable,
			RUNTIME_CLASS(CAllOperationTableDoc),		// ドキュメント クラス
			RUNTIME_CLASS(CMDIChildWnd),		// フレーム クラス
			RUNTIME_CLASS(CAllOperationTableView));	// ビュー クラス
		AddDocTemplate(pNewDocTemplate);

		m_pdoctmplAllOperationTable = pNewDocTemplate;
		//	このドキュメントテンプレートを、アプリケーションクラスの
		//	メンバ変数に保存
	}
	{
		CHidemdiSubDoctmpl* pNewDocTemplate = new CHidemdiDoctmplDocstrAlone(
			IDR_DOCVIEW_AllOperationTable2,
			RUNTIME_CLASS(CDedAllOperationTable2Doc),		// ドキュメント クラス
			RUNTIME_CLASS(CMDIChildWnd),		// フレーム クラス
			RUNTIME_CLASS(CDedAllOperationTable2View));	// ビュー クラス
		AddDocTemplate(pNewDocTemplate);

		m_pdoctmplAllOperationTable2 = pNewDocTemplate;
		//	このドキュメントテンプレートを、アプリケーションクラスの
		//	メンバ変数に保存
	}
	{
		CHidemdiSubDoctmpl* pNewDocTemplate = new CHidemdiDoctmplDocstrAlone(
			IDR_DOCVIEW_EkiJikokuhyou,
			RUNTIME_CLASS(CEkiJikokuhyouDoc),		// ドキュメント クラス
			RUNTIME_CLASS(CMDIChildWnd),		// フレーム クラス
			RUNTIME_CLASS(CEkiJikokuhyouView));	// ビュー クラス
		AddDocTemplate(pNewDocTemplate);

		m_pdoctmplEkiJikokuhyou = pNewDocTemplate;
		//	このドキュメントテンプレートを、アプリケーションクラスの
		//	メンバ変数に保存
	}
	{
		CHidemdiSubDoctmpl* pNewDocTemplate = new CHidemdiDoctmplDocstrAlone(
			IDR_DOCVIEW_EkiJikokuhyouList,
			RUNTIME_CLASS(CEkiJikokuhyouListDoc),		// ドキュメント クラス
			RUNTIME_CLASS(CMDIChildWnd),		// フレーム クラス
			RUNTIME_CLASS(CEkiJikokuhyouListView));	// ビュー クラス
		AddDocTemplate(pNewDocTemplate);

		m_pdoctmplEkiJikokuhyouList = pNewDocTemplate;
		//	このドキュメントテンプレートを、アプリケーションクラスの
		//	メンバ変数に保存
	}
	{
		CHidemdiSubDoctmpl* pNewDocTemplate = new CHidemdiDoctmplDocstrAlone(
			IDR_DOCVIEW_InOutLinkCodeList,
			RUNTIME_CLASS(CInOutLinkCodeListDoc),		// ドキュメント クラス
			RUNTIME_CLASS(CMDIChildWnd),		// フレーム クラス
			RUNTIME_CLASS(CInOutLinkCodeListView));	// ビュー クラス
		AddDocTemplate(pNewDocTemplate);

		m_pdoctmplInOutLinkCodeList = pNewDocTemplate;
		//	このドキュメントテンプレートを、アプリケーションクラスの
		//	メンバ変数に保存
	}
	{
		CHidemdiSubDoctmpl* pNewDocTemplate = new CHidemdiDoctmplDocstrAlone(
			IDR_DOCVIEW_CrossingCheck,
			RUNTIME_CLASS(CCrossingCheckDoc),		// ドキュメント クラス
			RUNTIME_CLASS(CMDIChildWnd),		// フレーム クラス
			RUNTIME_CLASS(CCrossingCheckView));	// ビュー クラス
		AddDocTemplate(pNewDocTemplate);

		m_pdoctmplCrossingCheck = pNewDocTemplate;
		//	このドキュメントテンプレートを、アプリケーションクラスの
		//	メンバ変数に保存
	}


	// メイン MDI フレーム ウィンドウを作成
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// ドラッグ/ドロップ のオープンを許可します
	m_pMainWnd->DragAcceptFiles();

	// DDE Execute open を使用可能にします。
	EnableShellOpen();
	
	//	(このアプリケーションからは、ファイルタイプのレジストリへの登録は
	//	行いません。
	//	登録は、VisualStudioInstaller で行います）
	// --------------------------------
	//	RegisterShellFileTypes(TRUE);

	// DDE、file open など標準のシェル コマンドのコマンドラインを解析します。
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// コマンドラインでディスパッチ コマンドを指定します。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// メイン ウィンドウが初期化されたので、表示と更新を行います。
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

//memo: 現在は、IDD_AboutBoxGpl に代替されました。
///////////////////////////////////////////////////////////////////////////////
//// アプリケーションのバージョン情報で使われる CAboutDlg ダイアログ
//
///**
// @brief
//	バージョン情報のダイアログのクラスです。
//*/
//class CAboutDlg : public CDialog
//{
//public:
//	CAboutDlg( const string& strProgramVer );
//
//// ダイアログ データ
//	//{{AFX_DATA(CAboutDlg)
//	enum { IDD = IDD_ABOUTBOX };
//	CString	m_strSTATIC_VERSION;
//	//}}AFX_DATA
//
//	// ClassWizard 仮想関数のオーバーライドを生成します。
//	//{{AFX_VIRTUAL(CAboutDlg)
//	protected:
//	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV のサポート
//	//}}AFX_VIRTUAL
//
//// インプリメンテーション
//protected:
//	//{{AFX_MSG(CAboutDlg)
//		// メッセージ ハンドラはありません。
//	//}}AFX_MSG
//	DECLARE_MESSAGE_MAP()
//};
//
//CAboutDlg::CAboutDlg( const string& strProgramVer ) : CDialog(CAboutDlg::IDD)
//{
//	//{{AFX_DATA_INIT(CAboutDlg)
//	m_strSTATIC_VERSION = "Ver. " ;
//	//}}AFX_DATA_INIT
//	m_strSTATIC_VERSION += strProgramVer.c_str() ;
//}
//
//void CAboutDlg::DoDataExchange(CDataExchange* pDX)
//{
//	CDialog::DoDataExchange(pDX);
//	//{{AFX_DATA_MAP(CAboutDlg)
//	DDX_Text(pDX, IDC_STATIC_VERSION, m_strSTATIC_VERSION);
//	//}}AFX_DATA_MAP
//}
//
//BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//	//{{AFX_MSG_MAP(CAboutDlg)
//		// メッセージ ハンドラはありません。
//	//}}AFX_MSG_MAP
//END_MESSAGE_MAP()
//



// ダイアログを実行するためのアプリケーション コマンド
void CDiagramEditApp::OnAppAbout()
{
	tstring strProgramVer ;
	tstring strLegalCopyright ;
	readVersionResource( &strProgramVer , &strLegalCopyright ) ;


	CAboutBoxGpl aboutDlg( strProgramVer , strLegalCopyright ) ;

	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CDiagramEditApp メッセージ ハンドラ

void CDiagramEditApp::OnVIEWEki() 
{
	openCEkiDoc() ;
	
}

void CDiagramEditApp::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
	CDocument*	pCDocument = getCDiagramEditDoc() ;
	BOOL	bIsModified = FALSE ;
	if ( pCDocument != NULL ){
		bIsModified = pCDocument->IsModified() ;
	}
	pCmdUI->Enable( bIsModified ) ;

	
}

int CDiagramEditApp::ExitInstance() 
{
	tstring	strPrintPageProp = m_CdPrintPageProp.encode() ;
	WriteProfileString( nameSection , namePrintPageProp , strPrintPageProp.c_str() ) ;

	return CHidemdiApp::ExitInstance();
}

void CDiagramEditApp::OnFILEPrintPageProp() 
{
	CDlgPrintPageProp	aDlg( m_CdPrintPageProp  ) ;
	if ( aDlg.DoModal() == IDOK ){
		m_CdPrintPageProp = aDlg.getCdPrintPageProp() ;
	}
	
}



void CDiagramEditApp::OnFileOpen() 
{
	CString	strExt ;
	pRootDoctmpl()->GetDocString( strExt , CDocTemplate::filterExt ) ;

	CFileDialog	aDlg( TRUE , strExt , NULL , 
	  OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, getCFileDialogFilterOpen() , NULL ) ;
	if ( aDlg.DoModal() != IDOK ){
		return ;
	}	
	// --------------------------------

	AfxGetApp()->OpenDocumentFile(aDlg.GetPathName() );
		// if returns NULL, the user has already been alerted
	
}

#include <htmlhelp.h>

void CDiagramEditApp::OnHelp() 
{
	CString	strUrl = makeHtmlHelpUrl( _T( "" ) )  ;

	//	第一引数をアプリケーションのメインウインドウにすると、
	//	メインウインドウは常にHTMLHelpウインドウの上になります。
	HWND hwndCaller = NULL ;
	HWND hwnd =
		::HtmlHelp(
			hwndCaller ,
				strUrl , 
				 HH_DISPLAY_TOPIC,
	             NULL) ;
}
