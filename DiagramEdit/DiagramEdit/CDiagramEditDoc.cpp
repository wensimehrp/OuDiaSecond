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
// CDiagramEditDoc.cpp : CDiagramEditDoc クラスの動作の定義を行います。
// $Id: CDiagramEditDoc.cpp 
/** @file */
#include "stdafx.h"

#include "logmsg/LogMsg.h"
#include "str/vectorToFile.h"
#include "str/CdFilenameStr.h"
#include "str/OuPropertiesText\CConvNodeContainer.h"
#include "str/OuPropertiesText\ErrorInfo\COuErrorInfoContainer.h"
#include "str/strprintf.h"
#include "str/strToVector.h"
#include "str/strToWstr.h"
#include "str/tstring.h"
#include "str/strLf.h"
#include "NsOu/dynamic_castOu.h"
#include "NsOu/OuNew.h"
#include "MfcUtil/MfcUtil.h"

#include "DiagramEdit.h"
#include "CDiagramEditDoc.h"
#include "DedRosenFileData\CconvCDedRosenFileData.h"
#include "DedRosenFileData\CconvCDedRosenFileDataOud.h"
#include "entDed\CconvCentDed.h"
//#include "WinDia\CconvWinDia.h"
#include "CRfEditCmdHolder.h"
//#include "WinDia\CDlgDiaSaveSelect.h"
//#include "ConvFile\CConvFileDll.h"
//#include "ConvFile\CaByteBuffer_vector.h"
//#include "ConvFile\CaByteBuffer_string.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std ;
using namespace OuLib::Str ;
using namespace OuLib::Str::OuPropertiesText ;
using namespace OuLib::Str::OuPropertiesText::ErrorInfo ;
using namespace OuMfc;

/////////////////////////////////////////////////////////////////////////////
// CDiagramEditDoc

/**	Undo の最大回数です。 */
const int iUndoLevel = 8 ;
// --------------------------------
//@name	下請関数-WinDia形式
// --------------------------------
//BOOL CDiagramEditDoc::OnOpenDocument_WinDia( LPCTSTR lpszPathName ) 
//{
//	LogMsg( "CDiagramEditDoc::OnOpenDocument_WinDia(%s)" , lpszPathName ) ;
//	int iRv = 0 ;
//
//	// --------------------------------
//	//	ファイルの内容を、stringに保存
//	// --------------------------------
//	string	aString ;
//	CString	strError ;
//	if ( iRv >= 0 ){
//		int iResult = stringFromFile( &aString , lpszPathName ) ;
//		//iResult = 
//		//	-1: ファイルがオープンできません。
//		//	-2 ; 読み込みに失敗しました。
//		//	-3 ; ファイルには "\0" が含まれます(バイナリファイルであると 
//		//	思われます)。
//		//	 この場合、pString には、 "\0" の直前までのデータが格納されて 
//		//	います。 
//		if ( iResult < 0 ){
//			iRv = iResult ;
//			switch( iResult ){
//			 case -1 :	// ファイルがオープンできません。
//				{
//					CString	strFmt ;
//					strFmt.LoadString( IDS_ERR_FILENOTFOUND ) ;
//					strError.Format( strFmt , lpszPathName ) ;
//				}
//				break ;
//			 case -2 :	//; 読み込みに失敗しました。
//				{
//					CString	strFmt ;
//					strFmt.LoadString( IDS_ERR_FILEREAD ) ;
//					strError.Format( strFmt , lpszPathName ) ;
//				}
//				break ;
//			 case -3 :	// ファイルには "\0" が含まれます
//				{
//					CString	strFmt ;
//					strFmt.LoadString( IDS_ERR_FILEFORMAT ) ;
//					strError.Format( strFmt , lpszPathName ) ;
//				}
//				break ;
//			}
//			//iRv = 
//			//	-1: ファイルがオープンできません。
//			//	-2 ; 読み込みに失敗しました。
//			//	-3 ; ファイルには "\0" が含まれます(バイナリファイルであると 
//			//	思われます)。
//			//	 この場合、pString には、 "\0" の直前までのデータが格納されて 
//			//	います。 
//		}
//	}
//	//aString = ファイルの内容を保持します。
//
//	LogMsg( "CDiagramEditDoc::OnOpenDocument_WinDia()1" ) ;
//
//	// --------------------------------
//	//	ファイルの内容の文字列を解釈
//	// --------------------------------
//	if ( iRv >= 0 ){
//		CDedRosenFileData	aCDedRosenFileData ;
//		CconvWinDia aCconvWinDia ;
//		int iResult = aCconvWinDia.CDedRosenFileData_From_WinDiaFileString( 
//			&aCDedRosenFileData , aString ) ;
//		if ( iResult < 0 ){
//			iRv = iResult ;
//		}	else	{
//			m_CDedRosenFileData = aCDedRosenFileData ;
//		}
//	}	
//
//	// --------------------------------
//	//	路線ビューを更新
//	// --------------------------------
//	getCDiagramEditApp()->getCDlgRosenView()->OnUpdate( NULL , 0 , NULL ) ;
//
//	// --------------------------------
//	LogMsg( "CDiagramEditDoc::OnOpenDocument_WinDia()=%d" , iRv ) ;
//	if ( iRv < 0 ){
//		if ( strError.IsEmpty() ){
//			CString	strFmt ;
//			strFmt.LoadString( IDS_ERR_ERRORCODE ) ;
//			strError.Format( strFmt , iRv ) ;
//		}
//		AfxMessageBox( strError , MB_ICONSTOP ) ; 
//		return ( FALSE ) ;
//	}
//	//	ドキュメントのファイル名は、
//	//	CDiagramEditDoc::SetPathName()でチェックされます。
//	//	拡張子 .dia は、ドキュメントの有効なファイル名とは
//	//	しません(.dia への上書き保存はしません)
//	return TRUE;
//
//}

	
//BOOL CDiagramEditDoc::OnSaveDocument_WinDia(  LPCTSTR lpszPathName ) 
//{
//	/*
//	 *	OnSaveDocument() の下請関数です。
//	 *	ドキュメントの内容を、WinDia 形式のファイルに保存します。
//	 * @param lpszPathName [in]
//	 * 	保存するファイル名を指定して下さい。
//	 * @return
//	 *	成功したら TRUE ・ エラーなら FALSE です。
//	 *
//	 *	この関数は、エラーの場合はメッセージボックスを表示します。
//	 */
//	// --------------------------------
//	int iRv = 0 ;
//
//	CString	strError ;
//	string	aString ;
//
//	// --------------------------------
//	//	保存するダイヤを選択
//	// --------------------------------
//	int idxDia = -1 ;
//	if ( iRv >= 0 ){
//		CentDedRosen* pCentDedRosen = m_CDedRosenFileData.getCentDedRosen();
//		if ( pCentDedRosen->getCentDedDiaCont()->getMuPtr()->size() == 0 )
//		{
//			iRv = -101 ;	//	ダイヤが存在しません。
//			CString strFmt ;
//			strFmt.LoadString( IDS_ERR_NoDia ) ;
//			strError.Format( strFmt , lpszPathName ) ;
//		}
//		else if ( pCentDedRosen->getCentDedDiaCont()->getMuPtr()->size() == 1 )
//		{
//			idxDia = 0 ;
//		}	else	{
//			Mu<CentDedDia*>* pCentDedDiaContGet = 
//				pCentDedRosen->getCentDedDiaCont()->getMuPtr() ;
//
//			CMup_deque< string > contstrDiaName ;
//			for ( int idxDiaName = 0 ; 
//				idxDiaName < pCentDedDiaContGet->size() ; 
//				idxDiaName ++ ){
//				contstrDiaName.insert( pCentDedDiaContGet->get( idxDiaName )->getName() ) ;
//			}
//			CDlgDiaSaveSelect	aDlg( contstrDiaName , NULL ) ;
//			if ( aDlg.DoModal() == IDOK ){
//				idxDia = aDlg.getDiaIndex() ;
//			}	else	{
//				return FALSE ;
//			}
//		}
//	}
//	//idxDia = 選択されたダイヤのインデクス
//	// --------------------------------
//	//	WinDIA形式のファイルの文字列を作成
//	// --------------------------------
//	if ( iRv >= 0 ){
//		CconvWinDia aCconvWinDia ;
//		int iResult = aCconvWinDia.CDedRosenFileData_To_WinDiaFileString( &m_CDedRosenFileData ,idxDia , &aString ) ;
//		//iResult = 
//		//	-21 ;	//	WinDIA 形式では、列車種別は24種類までに制限されています。
//		//	-22 ;	//	略称の長さが半角５文字を超える列車種別があります。
//		//			//	WinDIA 形式に保存するためには、すべての列車種別略称は
//		//			//	全角２文字以内でなくてはなりません。
//		//	-1 ;	//	idxDia の指定が不正です。
//		if ( iResult < 0 ){
//			iRv = iResult ;
//			switch( iResult ){
//			 case -21 : //	WinDIA 形式では、列車種別は24種類までに制限されています。
//				{
//					CString	strFmt ;
//					strFmt.LoadString( IDS_ERR_RessyasyubetsuTooMany ) ;
//					strError.Format( strFmt , lpszPathName ) ;
//				}
//				break ;
//			 case -22 :	//	略称の長さが半角５文字を超える列車種別があります。
//				 {
//					CString	strFmt ;
//					strFmt.LoadString( IDS_ERR_RyakusyouTooLong ) ;
//					strError.Format( strFmt , lpszPathName ) ;
//				 }
//			}
//			//iRv = 
//			//	-	-21 ;	//	WinDIA 形式では、列車種別は24種類までに制限されています。
//			//	-	-22 :	//	略称の長さが半角５文字を超える列車種別があります。
//			//	-	-1 ;	//	idxDia の指定が不正です。
//		}
//	}	
//	//aString = ファイルに書き込む『路線ファイル』形式の文字列を保持します。
//
//	// --------------------------------
//	//	ファイルの保存
//	// --------------------------------
//	LogMsg( "CDiagramEditDoc::OnSaveDocument()1" ) ;
//	if ( iRv >= 0 ){
//		int iResult = stringToFile( aString , lpszPathName ) ;
//		//iResult = 
//		//	-1: ファイルがオープンできません。
//		//	-2 ; // 書き込みに失敗しました。 
//		if ( iResult < 0 ){
//			switch( iResult ){
//			 case -1 :	// ファイルがオープンできません。
//				{
//					CString	strFmt ;
//					strFmt.LoadString( IDS_ERR_FILECREATE ) ;
//					strError.Format( strFmt , lpszPathName ) ;
//				}
//				break ;
//			 case -2 :	//;書き込みに失敗しました
//				{
//					CString	strFmt ;
//					strFmt.LoadString( IDS_ERR_FILEWRITE ) ;
//					strError.Format( strFmt , lpszPathName ) ;
//				}
//				break ;
//			}
//			//iRv = 
//			//	-1: ファイルがオープンできません。
//			//	-2 ; 書き込みに失敗しました
//			iRv = iResult - 100 ;
//		}
//	}
//
//	// --------------------------------
//	LogMsg( "CDiagramEditDoc::OnSaveDocument()=%d" , iRv ) ;
//
//	if ( iRv < 0 ){
//		if ( strError.IsEmpty() ){
//			CString	strFmt ;
//			strFmt.LoadString( IDS_ERR_ERRORCODE ) ;
//			strError.Format( strFmt , iRv ) ;
//		}
//		AfxMessageBox( strError , MB_ICONSTOP ) ; 
//		return ( FALSE ) ;
//	}
//
//	//	WinDIA 形式の保存は、正式なドキュメントの保存とはしません。
//	//	WinDIA 形式の保存に成功しても、ドキュメントファイル名は
//	//	WinDIA ファイルのファイル名にはしません。
//	//	ドキュメントの変更フラグも、クリアしません。
//	//	（WinDIAファイルは、ドキュメント全体を保持することが
//	//	できないためです。）
//	//	このため、以下の処理は行いません
//	// --------------------------------
//	//	SetModifiedFlag( FALSE ) ;
//	//	return TRUE;
//	// --------------------------------
//	
//	//iRv = 
//	//	-	-101 ;	//	ダイヤが存在しません。
//	//	-	-21 ;	//	WinDIA 形式では、列車種別は24種類までに制限されています。
//	//	-	-22 :	//	略称の長さが半角５文字を超える列車種別があります。
//	//	-	-1 ;	//	idxDia の指定が不正です。
//	//	-	-201: ファイルがオープンできません。
//	//	-	-202 ; 書き込みに失敗しました
//	return FALSE ;
//}
	

// ********************************
//	CHidemdiRootDoc
// ********************************
void CDiagramEditDoc::UpdateAllSubDocviews( CView* pSender
							, LPARAM lHint , CObject* pHint )
{
	// --------------------------------
	//	時刻表・ダイヤグラム・運用表ビューに対応する
	//	ダイヤが削除されていたら、
	//  または、駅番線ビューに対応する駅が削除されていたら、
	//	対応するサブViewを閉じます。
	//	運用機能がOFFになった場合、運用表ビューを閉じます。
	//  パターンダイヤプレビュー機能が有効になった場合、運用関係のビューを閉じます
	// --------------------------------
	POSITION	LPosition = AfxGetApp()->GetFirstDocTemplatePosition() ;
	while( LPosition != NULL ){
		CDocTemplate*	pLDocTemplate = AfxGetApp()
						->GetNextDocTemplate( LPosition ) ;
		{
			POSITION	LPosition = pLDocTemplate->GetFirstDocPosition() ;
			while( LPosition != NULL ){
				CDocument*	pLDocument = 
					pLDocTemplate->GetNextDoc( LPosition ) ;
				
				if ( pLDocument != NULL && 
						pLDocument->IsKindOf( RUNTIME_CLASS( CJikokuhyouDoc ) ) ){
					CJikokuhyouDoc*	pCJikokuhyouDoc = 
						(CJikokuhyouDoc*)pLDocument ;
					
					const CentDedRosen*	pCentDedRosen = 
						getCDiagramEditDoc()->getCDedRosenFileData()->
						getCentDedRosen() ;
					CentDedDia*	pCentDedDia = NULL ;
					int idxDia = pCentDedRosen->getCentDedDiaCont()->findCentDedDiaByName( 
						pCJikokuhyouDoc->getDiaName() ) ;
					if ( idxDia < 0 ){
						//	このドキュメントに対応するダイヤは削除されました
						pCJikokuhyouDoc->OnCloseDocument() ;
						pLDocument = NULL ;
					}
				}
				if (  pLDocument != NULL && 
						pLDocument->IsKindOf( RUNTIME_CLASS( CDedDiagramDoc ) ) ){
					CDedDiagramDoc*	pCDedDiagramDoc = 
						(CDedDiagramDoc*)pLDocument ;
					
					const CentDedRosen*	pCentDedRosen = 
						getCDiagramEditDoc()->getCDedRosenFileData()->
						getCentDedRosen() ;
					CentDedDia*	pCentDedDia = NULL ;
					int idxDia = pCentDedRosen->getCentDedDiaCont()->findCentDedDiaByName( 
						pCDedDiagramDoc->getDiaName() ) ;
					if ( idxDia < 0 ){
						//	このドキュメントに対応するダイヤは削除されました
						pCDedDiagramDoc->OnCloseDocument() ;
						pLDocument = NULL ;
					}
				}
				if (pLDocument != NULL &&
					pLDocument->IsKindOf(RUNTIME_CLASS(COperationTableDoc))) {
					COperationTableDoc*	pCOperationTableDoc =
						(COperationTableDoc*)pLDocument;

					bool bClosed = false;
					const CentDedRosen*	pCentDedRosen =
						getCDiagramEditDoc()->getCDedRosenFileData()->
						getCentDedRosen();
					if (pCentDedRosen->getEnableOperation() < 2)
					{
						//	運用機能がOFFになりました
						pCOperationTableDoc->OnCloseDocument();
						pLDocument = NULL;
						bClosed = true;
					}

					if (!bClosed)
					{
						//CentDedDia* pCentDedDia = NULL;
						int idxDia = pCentDedRosen->getCentDedDiaCont()->findCentDedDiaByName(
							pCOperationTableDoc->getDiaName());
						if (idxDia < 0) {
							//	このドキュメントに対応するダイヤは削除されました
							pCOperationTableDoc->OnCloseDocument();
							pLDocument = NULL;
							bClosed = true;
						}
					}
					if (!bClosed)
					{
						int idxDia = pCentDedRosen->getCentDedDiaCont()->findCentDedDiaByName(
							pCOperationTableDoc->getDiaName());
						if (pCentDedRosen->getCentDedDiaCont()->getMuPtr()->get(idxDia)->getPatternDiagramPreviewEnable()) {
							//	このドキュメントに対応するダイヤの、パターンダイヤプレビュー機能が有効になりました。
							pCOperationTableDoc->OnCloseDocument();
							pLDocument = NULL;
							bClosed = true;
						}
					}

					if (!bClosed)
					{
						int idxDia = pCentDedRosen->getCentDedDiaCont()->findCentDedDiaByName(
							pCOperationTableDoc->getDiaName());
						tstring strOperationNumber = pCOperationTableDoc->getOperationNumber();
						auto itr = pCentDedRosen->getCentDedDiaCont()->getMuPtr()->get(idxDia)->
							getcontOperationTableContent().find(strOperationNumber);
						if (itr == pCentDedRosen->getCentDedDiaCont()->getMuPtr()->get(idxDia)->
							getcontOperationTableContent().end())
						{
							pCOperationTableDoc->OnCloseDocument();
							pLDocument = NULL;
							bClosed = true;
						}
					}
				}
				if (pLDocument != NULL &&
					pLDocument->IsKindOf(RUNTIME_CLASS(CAllOperationTableDoc))) {
					CAllOperationTableDoc* pCAllOperationTableDoc =
						(CAllOperationTableDoc*)pLDocument;

					bool bClosed = false;
					const CentDedRosen* pCentDedRosen =
						getCDiagramEditDoc()->getCDedRosenFileData()->
						getCentDedRosen();
					if (pCentDedRosen->getEnableOperation() < 2)
					{
						//	運用機能がOFFになりました
						pCAllOperationTableDoc->OnCloseDocument();
						pLDocument = NULL;
						bClosed = true;
					}

					if (!bClosed)
					{
						int idxDia = pCentDedRosen->getCentDedDiaCont()->findCentDedDiaByName(
							pCAllOperationTableDoc->getDiaName());
						if (idxDia < 0) {
							//	このドキュメントに対応するダイヤは削除されました
							pCAllOperationTableDoc->OnCloseDocument();
							pLDocument = NULL;
							bClosed = true;
						}
					}

					if (!bClosed)
					{
						int idxDia = pCentDedRosen->getCentDedDiaCont()->findCentDedDiaByName(
							pCAllOperationTableDoc->getDiaName());
						if (pCentDedRosen->getCentDedDiaCont()->getMuPtr()->get(idxDia)->getPatternDiagramPreviewEnable()) {
							//	このドキュメントに対応するダイヤの、パターンダイヤプレビュー機能が有効になりました。
							pCAllOperationTableDoc->OnCloseDocument();
							pLDocument = NULL;
							bClosed = true;
						}
					}

					if (!bClosed)
					{
						int idxDia = pCentDedRosen->getCentDedDiaCont()->findCentDedDiaByName(
							pCAllOperationTableDoc->getDiaName());
						if (pCentDedRosen->getCentDedDiaCont()->getMuPtr()->get(idxDia)->
							getcontOperationTableContent().empty())
						{
							//ダイヤ内に運用が一つもありません
							pCAllOperationTableDoc->OnCloseDocument();
							pLDocument = NULL;
							bClosed = true;
						}
					}
				}
				if (pLDocument != NULL &&
					pLDocument->IsKindOf(RUNTIME_CLASS(CDedAllOperationTable2Doc))) {
					CDedAllOperationTable2Doc* pCDedAllOperationTable2Doc =
						(CDedAllOperationTable2Doc*)pLDocument;

					bool bClosed = false;
					const CentDedRosen* pCentDedRosen =
						getCDiagramEditDoc()->getCDedRosenFileData()->
						getCentDedRosen();
					if (pCentDedRosen->getEnableOperation() < 2)
					{
						//	運用機能がOFFになりました
						pCDedAllOperationTable2Doc->OnCloseDocument();
						pLDocument = NULL;
						bClosed = true;
					}

					if (!bClosed) 
					{
						int idxDia = pCentDedRosen->getCentDedDiaCont()->findCentDedDiaByName(
							pCDedAllOperationTable2Doc->getDiaName());
						if (idxDia < 0) {
							//	このドキュメントに対応するダイヤは削除されました
							pCDedAllOperationTable2Doc->OnCloseDocument();
							pLDocument = NULL;
							bClosed = true;
						}
					}

					if (!bClosed)
					{
						int idxDia = pCentDedRosen->getCentDedDiaCont()->findCentDedDiaByName(
							pCDedAllOperationTable2Doc->getDiaName());
						if (pCentDedRosen->getCentDedDiaCont()->getMuPtr()->get(idxDia)->getPatternDiagramPreviewEnable()) {
							//	このドキュメントに対応するダイヤの、パターンダイヤプレビュー機能が有効になりました。
							pCDedAllOperationTable2Doc->OnCloseDocument();
							pLDocument = NULL;
							bClosed = true;
						}
					}

					if (!bClosed)
					{
						int idxDia = pCentDedRosen->getCentDedDiaCont()->findCentDedDiaByName(
							pCDedAllOperationTable2Doc->getDiaName());
						if (pCentDedRosen->getCentDedDiaCont()->getMuPtr()->get(idxDia)->
							getcontOperationTableContent().empty())
						{
							//ダイヤ内に運用が一つもありません
							pCDedAllOperationTable2Doc->OnCloseDocument();
							pLDocument = NULL;
							bClosed = true;
						}
					}
				}
				if (pLDocument != NULL &&
					pLDocument->IsKindOf(RUNTIME_CLASS(CEkiJikokuhyouDoc))) {
					CEkiJikokuhyouDoc* pCEkiJikokuhyouDoc =
						(CEkiJikokuhyouDoc*)pLDocument;

					bool bClosed = false;
					const CentDedRosen* pCentDedRosen =
						getCDiagramEditDoc()->getCDedRosenFileData()->
						getCentDedRosen();
					if (!bClosed)
					{
						int idxDia = pCentDedRosen->getCentDedDiaCont()->findCentDedDiaByName(
							pCEkiJikokuhyouDoc->getDiaName());
						if (idxDia < 0) {
							//	このドキュメントに対応するダイヤは削除されました
							pCEkiJikokuhyouDoc->OnCloseDocument();
							pLDocument = NULL;
							bClosed = true;
						}
					}

					if (!bClosed)
					{
						const CentDedEkiCont* pCentDedEkiCont = pCentDedRosen->getCentDedEkiCont();
						int iEkiID = pCEkiJikokuhyouDoc->getEkiID();
						bool bExist = false;
						for (int idx = 0; idx < pCentDedEkiCont->size() && !bExist; idx++)
						{
							if (pCentDedEkiCont->get(idx).getID() == iEkiID)
							{
								bExist = true;
							}
						}
						if (!bExist)
						{
							//	このドキュメントに対応する駅は削除されました
							pCEkiJikokuhyouDoc->OnCloseDocument();
							pLDocument = NULL;
							bClosed = true;
						}
					}
				}
				if (pLDocument != NULL &&
					pLDocument->IsKindOf(RUNTIME_CLASS(CEkiJikokuhyouListDoc))) {
					CEkiJikokuhyouListDoc* pCEkiJikokuhyouListDoc =
						(CEkiJikokuhyouListDoc*)pLDocument;

					bool bClosed = false;
					const CentDedRosen* pCentDedRosen =
						getCDiagramEditDoc()->getCDedRosenFileData()->
						getCentDedRosen();
					if (!bClosed)
					{
						int idxDia = pCentDedRosen->getCentDedDiaCont()->findCentDedDiaByName(
							pCEkiJikokuhyouListDoc->getDiaName());
						if (idxDia < 0) {
							//	このドキュメントに対応するダイヤは削除されました
							pCEkiJikokuhyouListDoc->OnCloseDocument();
							pLDocument = NULL;
							bClosed = true;
						}
					}
				}
				if (pLDocument != NULL &&
					pLDocument->IsKindOf(RUNTIME_CLASS(CInOutLinkCodeListDoc))) {
					CInOutLinkCodeListDoc* pCInOutLinkCodeListDoc =
						(CInOutLinkCodeListDoc*)pLDocument;

					bool bClosed = false;
					const CentDedRosen* pCentDedRosen =
						getCDiagramEditDoc()->getCDedRosenFileData()->
						getCentDedRosen();
					if (pCentDedRosen->getEnableOperation() < 2)
					{
						//	運用機能がOFFになりました
						pCInOutLinkCodeListDoc->OnCloseDocument();
						pLDocument = NULL;
						bClosed = true;
					}

					if (!bClosed)
					{
						int idxDia = pCentDedRosen->getCentDedDiaCont()->findCentDedDiaByName(
							pCInOutLinkCodeListDoc->getDiaName());
						if (idxDia < 0) {
							//	このドキュメントに対応するダイヤは削除されました
							pCInOutLinkCodeListDoc->OnCloseDocument();
							pLDocument = NULL;
							bClosed = true;
						}
					}

					if (!bClosed)
					{
						int idxDia = pCentDedRosen->getCentDedDiaCont()->findCentDedDiaByName(
							pCInOutLinkCodeListDoc->getDiaName());
						if (pCentDedRosen->getCentDedDiaCont()->getMuPtr()->get(idxDia)->getPatternDiagramPreviewEnable()) {
							//	このドキュメントに対応するダイヤの、パターンダイヤプレビュー機能が有効になりました。
							pCInOutLinkCodeListDoc->OnCloseDocument();
							pLDocument = NULL;
							bClosed = true;
						}
					}

					if (!bClosed)
					{
						int idxDia = pCentDedRosen->getCentDedDiaCont()->findCentDedDiaByName(
							pCInOutLinkCodeListDoc->getDiaName());
						if (pCentDedRosen->getCentDedDiaCont()->getMuPtr()->get(idxDia)->
							getcontInOutLinkCodeContent().empty())
						{
							//ダイヤ内に入出区連携コードが一つもありません
							pCInOutLinkCodeListDoc->OnCloseDocument();
							pLDocument = NULL;
							bClosed = true;
						}
					}
				}
				if (pLDocument != NULL &&
					pLDocument->IsKindOf(RUNTIME_CLASS(CCrossingCheckDoc))) {
					CCrossingCheckDoc* pCCrossingCheckDoc =
						(CCrossingCheckDoc*)pLDocument;

					bool bClosed = false;
					const CentDedRosen* pCentDedRosen =
						getCDiagramEditDoc()->getCDedRosenFileData()->
						getCentDedRosen();
					if (!bClosed)
					{
						int idxDia = pCentDedRosen->getCentDedDiaCont()->findCentDedDiaByName(
							pCCrossingCheckDoc->getDiaName());
						if (idxDia < 0) {
							//	このドキュメントに対応するダイヤは削除されました
							pCCrossingCheckDoc->OnCloseDocument();
							pLDocument = NULL;
							bClosed = true;
						}
					}

					if (!bClosed)
					{
						const CentDedEkiCont* pCentDedEkiCont = pCentDedRosen->getCentDedEkiCont();
						int iEkiID = pCCrossingCheckDoc->getEkiID();
						bool bExist = false;
						for (int idx = 0; idx < pCentDedEkiCont->size() && !bExist; idx++)
						{
							if (pCentDedEkiCont->get(idx).getID() == iEkiID)
							{
								bExist = true;
							}
						}
						if (!bExist)
						{
							//	このドキュメントに対応する駅は削除されました
							pCCrossingCheckDoc->OnCloseDocument();
							pLDocument = NULL;
							bClosed = true;
						}
					}
				}
			}
		}
	}
	// --------------------------------
	//	すべてのサブViewを更新
	// --------------------------------
	super::UpdateAllSubDocviews( pSender , lHint , pHint );
	// --------------------------------
	//	路線Viewを更新
	// --------------------------------
	getCDiagramEditApp()->getCDlgRosenView()->OnUpdate(  pSender , lHint , pHint ) ;

}

// ********************************
//	CDiagramEditDoc
// ********************************
	// ********************************
	//@name 包含
	// ********************************
const CDedRosenFileData*	CDiagramEditDoc::getCDedRosenFileData()const 
{
	return &m_CDedRosenFileData ;
}



	// ********************************
	//@name クリップボード操作
	// ********************************

bool CDiagramEditDoc::UnicodeText_IsClipboardFormatAvailable()
{
	return (IsClipboardFormatAvailable(CF_UNICODETEXT) != 0);
}

UINT CDiagramEditDoc::getCF_CentDedEki()
{
	return RegisterClipboardFormat( _T("CF_CentDedEki") ) ;
} ;

/**
	string を、クリップボードにコピーします。
@param aHwnd [in]
	クリップボードのオーナーとなるウインドウを指定してください。
@param uiClipboardFormat [in]
	クリップボードフォーマットを指定してください。
@param strData [in]
	クリップボードにコピーする文字列を指定してください。
@return
	成功したら 0 以上、エラーなら負の数です。
	-	-2 ;	//	メモリの確保に失敗しました。
	-	-11 ;	//	クリップボードがオープンできません。
	-	-12 ;	//	クリップボードへのデータ設定が失敗
*/
static int stringToClipboard( 
		HWND aHwnd , 
		UINT uiClipboardFormat , 
		const tstring& strData ) 
{
	int iRv = 0 ;
	// --------------------------------
	//	クリップボードへの転送
	// --------------------------------
	HGLOBAL	hGlobal = NULL ;
	if ( iRv >= 0 )
	{	
		int iSize = (strData.length() * sizeof(TCHAR)) + sizeof(TCHAR);
		hGlobal = GlobalAlloc( GMEM_MOVEABLE, iSize);
		//hGlobal = GlobalAlloc(GMEM_MOVEABLE, strData.length() + 1);
		if ( hGlobal == NULL )
		{
			iRv = -2 ;	//	メモリの確保に失敗しました。
		}
		else
		{
			void*	pGlobal = GlobalLock( hGlobal ) ;
			memcpy( pGlobal , strData.c_str() , iSize) ;
			//memcpy(pGlobal, strData.c_str(), strData.length() + 1);
			GlobalUnlock( hGlobal ) ;
		}
	}
	//hGlobal = CentDedEki の内容を保持しています。
	
	bool	bIsOpen = false ;
	if ( iRv >= 0 )
	{	
		if ( !OpenClipboard( aHwnd ) )
		{
			iRv = -11 ;	//	クリップボードがオープンできません。
		}
		else
		{
			bIsOpen = true ;
		}
	}
	if ( iRv >= 0 ){	
		EmptyClipboard();
		HANDLE hResult = SetClipboardData( uiClipboardFormat , hGlobal);
		if ( hResult == NULL )
		{
			iRv = -12 ;	//	クリップボードへのデータ設定が失敗
		}
		else
		{
			//	クリップボードへの転送が成功しましたので、
			//	このアプリケーションは hGlobal を解放せずに放棄します。
			hGlobal = NULL ;
		}
	}
	if ( bIsOpen )
	{
		CloseClipboard();
	}
	if ( hGlobal != NULL )
	{
		GlobalFree( hGlobal ) ;
		hGlobal = NULL ;
	}
	return iRv ;
}



/**
	string を、クリップボードにコピーします。
@param aHwnd [in]
	クリップボードのオーナーとなるウインドウを指定してください。
@param uiClipboardFormat [in]
	クリップボードフォーマットを指定してください。
@param pstrData [out]
	この関数はこの文字列に、クリップボードの文字列をコピーします。
	不要なら NULL を指定してもかまいません。
@return
	成功したら 0 以上、エラーなら負の数です。
	-	-1 ;	//	クリップボードには有効なデータはありません。
	-	-11 ;	//	クリップボードがオープンできません。
*/
static int stringFromClipboard( 
		HWND aHwnd , 
		UINT uiClipboardFormat , 
		tstring* pstrData )
{
	int iRv = 0 ;
	// --------------------------------
	//	クリップボードからデータを取得
	// --------------------------------
	tstring	strData ;
	if ( iRv >= 0 )
	{	
		if ( !IsClipboardFormatAvailable(uiClipboardFormat) ) 
		{
			iRv = -1 ;	//	クリップボードには有効なデータはありません。
		}
	}
	bool	bIsOpen = false ;
	if ( iRv >= 0 )
	{ 
		if ( !OpenClipboard( aHwnd ) )
		{
			iRv = -11 ;	//	クリップボードがオープンできません。
		}
		else
		{
			bIsOpen = true ;
		}
	}
	if ( iRv >= 0 )
	{
		HGLOBAL	hGlobal = NULL ;
        hGlobal = GetClipboardData(uiClipboardFormat);
		if ( hGlobal != NULL )
		{
			const TCHAR* lpszData = (const TCHAR*)GlobalLock( hGlobal ) ;
			strData = lpszData ;
			GlobalUnlock( hGlobal ) ;
		}
	}
	if ( bIsOpen )
	{
        CloseClipboard();
	} 
	// --------------------------------
	if ( pstrData != NULL )
	{
		*pstrData = strData ;
	}
	// --------------------------------
	return iRv ;
}


int CDiagramEditDoc::CentDedEki_To_Cliboard( 
	const Mu<CentDedEki>* pMuCentDedEki ) 
{
	int iRv = 0 ;

	// --------------------------------
	//	Mu から EkiCont に変換
	// --------------------------------
	CentDedEkiCont	aEkiCont ;
	if ( iRv >= 0 )
	{
		CaMui<CentDedEki> aCaMui( &aEkiCont ) ;
		aCaMui.insert( pMuCentDedEki ) ;
	}

	// --------------------------------
	//	データを文字列化
	// --------------------------------
	tstring	strData ;
	if ( iRv >= 0 )
	{
		CNodeContainer aCNodeContainer ;
		CconvCentDed aCconvCentDed ;
		int iResult = aCconvCentDed.CentDedEkiCont_To_OuPropertiesText( 
			aEkiCont , 
			&aCNodeContainer ) ;
		if ( iRv < 0 )
		{
			iRv = -1 ;	//	CentDedEki の内容が不正です。
		}
		else
		{
			CConvNodeContainer	aCConvNodeContainer ;
			strData = aCConvNodeContainer.encode( &aCNodeContainer ) ;
			if ( strData.length() == 0 )
			{
				iRv = -1 ;	//	CentDedEki の内容が不正です。
			}
		}
	}
	//strData = CentDedEki の内容

	// --------------------------------
	//	クリップボードへの転送
	// --------------------------------
	if ( iRv >= 0 )
	{
		int iResult = stringToClipboard(  
			AfxGetMainWnd()->GetSafeHwnd() ,
			getCF_CentDedEki() , 
			strData ) ;
		if ( iResult < 0 )
		{
			iRv = -11 ;	//	クリップボードへのデータ設定が失敗
		}
	}
	return iRv ;
}

int CDiagramEditDoc::CentDedEki_From_Cliboard( 
		Mui<CentDedEki>* pCentDedEki ) 
{
	int iRv = 0 ;
	// --------------------------------
	//	クリップボードからデータを取得
	// --------------------------------
	tstring	strData ;
	bool bIsUnicodeText = false;
	if ( iRv >= 0 )
	{	
		if (!IsClipboardFormatAvailable(getCF_CentDedEki())) 
		{
			if (UnicodeText_IsClipboardFormatAvailable())
			{
				bIsUnicodeText = true;
			}
			else
			{
				iRv = -1;	//	クリップボードには有効なデータはありません。
			}
		}
	}
	if ( iRv >= 0 && !bIsUnicodeText)
	{
		int iResult = stringFromClipboard( 
			AfxGetMainWnd()->GetSafeHwnd() , 
			getCF_CentDedEki() , 
			&strData ) ;
		if ( iResult < 0 )
		{
			iRv = -2 ;	//	クリップボードからの読み込みに失敗しました。	
		}
	}
	else if (iRv >= 0 && bIsUnicodeText)
	{
		int iResult = stringFromClipboard(
			AfxGetMainWnd()->GetSafeHwnd(),
			CF_UNICODETEXT,
			&strData);
		if (iResult < 0)
		{
			iRv = -3;	//	クリップボードからの読み込みに失敗しました。	
		}
		strData = strLfOf(strData);
	}
	//strData = CentDedEki の内容
	// --------------------------------
	//	文字列から駅データを作成
	// --------------------------------
	CNodeContainer aCNodeContainer ;
	if ( iRv >= 0 )
	{
		CConvNodeContainer aCConvNodeContainer ;
		int iResult = aCConvNodeContainer.decode( 
			strData , 
			&aCNodeContainer ) ;
		if ( iResult < 0 )
		{
			iRv = -4 ;	//	クリップボードの内容が不正です。
		}
	}
	CentDedEkiCont	aCentDedEkiCont ;
	if ( iRv >= 0 )
	{
		CconvCentDed aCconvCentDed ;
		COuErrorInfoContainer aCOuErrorInfoContainer ;
		int iResult = aCconvCentDed.CentDedEkiCont_From_OuPropertiesText( 
			&aCentDedEkiCont , 
			aCNodeContainer.getIfNodeContainerConst() , 
			&aCOuErrorInfoContainer ) ;
		//iResult = 
		//	-22 ; // Ekijikokukeisiki の値が不正です。
		//	-32 ; // Ekikibo の値が不正です。 
		if ( iRv < 0 )
		{
			iRv = -5 ;	//	CentDedEki の内容が不正です。
		}
	}

	// --------------------------------
	//	Mu から EkiCont に変換
	// --------------------------------
	if ( iRv >= 0 )
	{
		CaMui<CentDedEki> aCaMui( pCentDedEki ) ;
		aCaMui.insert( &aCentDedEkiCont ) ;
	}
	// --------------------------------
	return ( iRv ) ;
}



bool CDiagramEditDoc::CentDedEki_IsClipboardFormatAvailable() 
{
	return ( IsClipboardFormatAvailable( getCF_CentDedEki() ) != 0 );
}

UINT CDiagramEditDoc::getCF_CentDedRessyasyubetsu()
{
	return RegisterClipboardFormat( _T("CF_CentDedRessyasyubetsu") ) ;
} ;

int CDiagramEditDoc::CentDedRessyasyubetsu_To_Cliboard( 
		const Mu<CentDedRessyasyubetsu>* pMuCentDedRessyasyubetsu ) 
{
	int iRv = 0 ;

	// --------------------------------
	//	Mu から CentDedRessyasyubetsuCont に変換
	// --------------------------------
	CentDedRessyasyubetsuCont	aRessyasyubetsuCont ;
	if ( iRv >= 0 )
	{
		CaMui<CentDedRessyasyubetsu> aCaMui( &aRessyasyubetsuCont ) ;
		aCaMui.insert( pMuCentDedRessyasyubetsu ) ;
	}
	// --------------------------------
	//	データを文字列化
	// --------------------------------
	tstring	strData ;
	if ( iRv >= 0 )
	{
		CNodeContainer aCNodeContainer ;
		CconvCentDed aCconvCentDed ;
		int iResult = aCconvCentDed.CentDedRessyasyubetsuCont_To_OuPropertiesText( 
			aRessyasyubetsuCont , 
			&aCNodeContainer ) ;
		//iResult = 
		//	-	-11 ;	//	Syubetsumei が指定されていません。
		//	-	-52 ;	//	DiagramSenStyle の値が不正です。
		if ( iRv < 0 )
		{
			iRv = -1 ;	//	CentDedRessyasyubetsuCont の内容が不正です。
		}
		else
		{
			CConvNodeContainer	aCConvNodeContainer ;
			strData = aCConvNodeContainer.encode( &aCNodeContainer ) ;
			if ( strData.length() == 0 )
			{
				iRv = -1 ;	//	CentDedRessyasyubetsu の内容が不正です。
			}
		}
	}
	//strData = CentDedRessyasyubetsu の内容	return iRv ;
	// --------------------------------
	//	クリップボードへの転送
	// --------------------------------
	if ( iRv >= 0 )
	{
		int iResult = stringToClipboard(  
			AfxGetMainWnd()->GetSafeHwnd() ,
			getCF_CentDedRessyasyubetsu() , 
			strData ) ;
		if ( iResult < 0 )
		{
			iRv = -11 ;	//	クリップボードへのデータ設定が失敗
		}
	}
	return iRv ;
}

int CDiagramEditDoc::CentDedRessyasyubetsu_From_Cliboard( 
	Mui<CentDedRessyasyubetsu>* pMuCentDedRessyasyubetsu ) 
{
	int iRv = 0 ;
	// --------------------------------
	//	クリップボードからデータを取得
	// --------------------------------
	tstring	strData ;
	bool bIsUnicodeText = false;
	if ( iRv >= 0 )
	{	
		if (!IsClipboardFormatAvailable(getCF_CentDedRessyasyubetsu())) 
		{
			if (UnicodeText_IsClipboardFormatAvailable())
			{
				bIsUnicodeText = true;
			}
			else
			{
				iRv = -1;	//	クリップボードには有効なデータはありません。
			}
		}
	}
	if ( iRv >= 0 && !bIsUnicodeText)
	{
		int iResult = stringFromClipboard( 
			AfxGetMainWnd()->GetSafeHwnd() , 
			getCF_CentDedRessyasyubetsu() , 
			&strData ) ;
		if ( iResult < 0 )
		{
			iRv = -2 ;	//	クリップボードからの読み込みに失敗しました。	
		}
	}
	else if (iRv >= 0 && bIsUnicodeText)
	{
		int iResult = stringFromClipboard(
			AfxGetMainWnd()->GetSafeHwnd(),
			CF_UNICODETEXT,
			&strData);
		if (iResult < 0)
		{
			iRv = -3;	//	クリップボードからの読み込みに失敗しました。	
		}
		strData = strLfOf(strData);
	}
	//strData = CentDedEki の内容
	// --------------------------------
	//	文字列から列車種別データを作成
	// --------------------------------
	CNodeContainer aCNodeContainer ;
	if ( iRv >= 0 )
	{
		CConvNodeContainer aCConvNodeContainer ;
		int iResult = aCConvNodeContainer.decode( 
			strData , 
			&aCNodeContainer ) ;
		if ( iResult < 0 )
		{
			iRv = -4 ;	//	クリップボードの内容が不正です。
		}
	}
	CentDedRessyasyubetsuCont	aCentDedRessyasyubetsuCont ;
	if ( iRv >= 0 )
	{
		CconvCentDed aCconvCentDed ;
		COuErrorInfoContainer aCOuErrorInfoContainer ;
		int iResult = aCconvCentDed.CentDedRessyasyubetsuCont_From_OuPropertiesText( 
			&aCentDedRessyasyubetsuCont , 
			aCNodeContainer.getIfNodeContainerConst() , 
			&aCOuErrorInfoContainer ) ;
		//iResult = 
		//-	-11 ;	//	Syubetsumei が指定されていません。
		//-	-52 ;	//	DiagramSenStyle の値が不正です。
		//-	-101 ;	//	値の形式が正しくありません。
		if ( iRv < 0 )
		{
			iRv = -5 ;	//	CentDedEki の内容が不正です。
		}
	}
	// --------------------------------
	//	Mu から EkiCont に変換
	// --------------------------------
	if ( iRv >= 0 )
	{
		CaMui<CentDedRessyasyubetsu> aCaMui( pMuCentDedRessyasyubetsu ) ;
		aCaMui.insert( &aCentDedRessyasyubetsuCont ) ;
	}
	// --------------------------------

	return iRv ;
}


bool CDiagramEditDoc::CentDedRessyasyubetsu_IsClipboardFormatAvailable() 
{
	return ( IsClipboardFormatAvailable( getCF_CentDedRessyasyubetsu() ) != 0 );
}

UINT CDiagramEditDoc::getCF_CentDedRessyaCont() 
{
	return RegisterClipboardFormat( _T("CF_CentDedRessyaCont") ) ;
}

int CDiagramEditDoc::CentDedRessyaCont_To_Cliboard( 
		const CentDedRessyaCont& aCentDedRessyaCont ) 
{
	int iRv = 0 ;

	// --------------------------------
	//	データを文字列化
	// --------------------------------
	tstring	strData ;
	if ( iRv >= 0 )
	{
		CNodeContainer aCNodeContainer ;
		CconvCentDed aCconvCentDed ;
		int iResult = aCconvCentDed.CentDedRessyaCont_To_OuPropertiesText(
			&aCentDedRessyaCont,
			false,
			&aCNodeContainer ) ;
		if ( iRv < 0 )
		{
			iRv = -1 ;	//	aCentDedRessyaCont の内容が不正です。
		}
		else
		{
			CConvNodeContainer	aCConvNodeContainer ;
			strData = aCConvNodeContainer.encode( &aCNodeContainer ) ;
			if ( strData.length() == 0 )
			{
				iRv = -1 ;	//	aCentDedRessyaCont の内容が不正です。
			}
		}
	}
	//string = aCentDedRessyaCont の内容

	// --------------------------------
	//	クリップボードへの転送
	// --------------------------------
	if ( iRv >= 0 )
	{
		int iResult = stringToClipboard(  
			AfxGetMainWnd()->GetSafeHwnd() ,
			getCF_CentDedRessyaCont() , 
			strData ) ;
		if ( iResult < 0 )
		{
			iRv = -11 ;	//	クリップボードへのデータ設定が失敗
		}
	}
	// --------------------------------
	return ( iRv ) ;
}

int CDiagramEditDoc::CentDedRessyaCont_From_Cliboard( 
		CentDedRessyaCont* pCentDedRessyaCont ) 
{
	int iRv = 0 ;
	// --------------------------------
	//	クリップボードからデータを取得
	// --------------------------------
	tstring	strData ;
	bool bIsUnicodeText = false;
	if ( iRv >= 0 ){	
		if (!IsClipboardFormatAvailable(getCF_CentDedRessyaCont())) {
			if (UnicodeText_IsClipboardFormatAvailable())
			{
				bIsUnicodeText = true;
			}
			else
			{
				iRv = -1;	//	クリップボードには有効なデータはありません。
			}
		}
	}
	if ( iRv >= 0 && !bIsUnicodeText)
	{
		int iResult = stringFromClipboard( 
			AfxGetMainWnd()->GetSafeHwnd() , 
			getCF_CentDedRessyaCont() , 
			&strData ) ;
		if ( iResult < 0 )
		{
			iRv = -2 ;	//	クリップボードからの読み込みに失敗しました。	
		}
	}
	else if (iRv >= 0 && bIsUnicodeText)
	{
		int iResult = stringFromClipboard(
			AfxGetMainWnd()->GetSafeHwnd(),
			CF_UNICODETEXT,
			&strData);
		if (iResult < 0)
		{
			iRv = -3;	//	クリップボードからの読み込みに失敗しました。	
		}
		strData = strLfOf(strData);
	}
	//strData = CentDedRessyaCont の内容
	// --------------------------------
	//	文字列から列車データを作成
	// --------------------------------
	const Mu<CentDedEkiCont::CdDedEki>*	pCdDedEkiCont =
		getCDiagramEditDoc()->getCDedRosenFileData()->
		getCentDedRosen()->getCentDedEkiCont()->getMuPtr(pCentDedRessyaCont->getRessyahoukou());
	vector<int> iEkiTrack2CountCont;
	vector<int> iMainTrackCont;
	vector<int> iOuterTerminalCountCont;
	for (int idxEki = 0; idxEki < pCdDedEkiCont->size(); idxEki++)
	{
		const CentDedEkiCont::CdDedEki aCdDedEki = pCdDedEkiCont->get(idxEki);
		iEkiTrack2CountCont.push_back(aCdDedEki.getCentDedEkiTrack2Cont().size());
		iMainTrackCont.push_back(aCdDedEki.getMainTrack());
		iOuterTerminalCountCont.push_back(aCdDedEki.getOuterTerminalEkimeiCount());
	}

	CNodeContainer aCNodeContainer ;
	if ( iRv >= 0 )
	{
		CConvNodeContainer aCConvNodeContainer ;
		int iResult = aCConvNodeContainer.decode( 
			strData , 
			&aCNodeContainer ) ;
		if ( iResult < 0 )
		{
			iRv = -4 ;	//	クリップボードの内容が不正です。
		}
	}

	if ( iRv >= 0 )
	{
		CconvCentDed aCconvCentDed ;
		COuErrorInfoContainer aCOuErrorInfoContainer ;
		int iResult = aCconvCentDed.CentDedRessyaCont_From_OuPropertiesText( 
			pCentDedRessyaCont , 
			iEkiTrack2CountCont,
			iMainTrackCont,
			iOuterTerminalCountCont,
			aCNodeContainer.getIfNodeContainerConst() , 
			&aCOuErrorInfoContainer ) ;
		if ( iResult < 0 )
		{
			iRv = -5 ;	//	CentDedRessyaCont の内容が不正です。
		}
	}
	//pCentDedRessyaCont = CentDedRessyaCont の内容

	// --------------------------------
	return ( iRv ) ;
}

bool CDiagramEditDoc::CentDedRessyaCont_IsClipboardFormatAvailable() 
{
	return ( IsClipboardFormatAvailable( getCF_CentDedRessyaCont() ) != 0 );
}

const tstring nameEkiOrder = _T("EkiOrder");
const tstring nameEkiJikoku = _T("EkiJikoku");
const tstring nameSyubetsuChange = _T("SyubetsuChange");

UINT CDiagramEditDoc::getCF_CentDedOperation()
{
	return RegisterClipboardFormat(_T("CF_CentDedOperation"));
}

int CDiagramEditDoc::CentDedOperation_To_Cliboard(
	const CentDedEkiJikoku& aCentDedEkiJikoku,
	const bool bSyubetsuChange,
	const int iEkiOrder)
{
	int iRv = 0;

	// --------------------------------
	//	データを文字列化
	// --------------------------------
	tstring	strData;
	if (iRv >= 0)
	{
		CNodeContainer aCNodeContainer;
		CconvCentDed aCconvCentDed;
		aCNodeContainer.setValue(nameEkiOrder, to_tstring(iEkiOrder));

		tstring	strEkijikoku = aCconvCentDed.CentDedEkiJikoku_To_string(
			&aCentDedEkiJikoku);
		aCNodeContainer.setValue(nameEkiJikoku, strEkijikoku);

		if (aCentDedEkiJikoku.getCentDedBeforeOperationCont()->size() > 0)
		{
			tstring strBefore = to_tstring(iEkiOrder) + _T('B');
			vector<vector<tstring>> strBeforeOperation =
				aCconvCentDed.CentDedBeforeOperationCont_To_string(
					aCentDedEkiJikoku.getCentDedBeforeOperationCont(),
					strBefore);
			for (int idxb = 0; idxb < (int)strBeforeOperation.size(); idxb++)
			{
				aCNodeContainer.setValue(strBeforeOperation[idxb][0],
					strBeforeOperation[idxb][1]);
			}
		}

		if (aCentDedEkiJikoku.getCentDedAfterOperationCont()->size() > 0)
		{
			tstring strAfter = to_tstring(iEkiOrder) + _T('A');
			vector<vector<tstring>> strAfterOperation =
				aCconvCentDed.CentDedAfterOperationCont_To_string(
					aCentDedEkiJikoku.getCentDedAfterOperationCont(),
					strAfter);
			for (int idxa = 0; idxa < (int)strAfterOperation.size(); idxa++)
			{
				aCNodeContainer.setValue(strAfterOperation[idxa][0],
					strAfterOperation[idxa][1]);
			}

			if (aCentDedEkiJikoku.getCentDedAfterOperationCont()->get(INT_MAX).
					getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Junction &&
				bSyubetsuChange)
			{
				aCNodeContainer.setValue(nameSyubetsuChange, _T("1"));
			}
		}
		if (iRv < 0)
		{
			iRv = -1;	//	aCentDedRessyaCont の内容が不正です。
		}
		else
		{
			CConvNodeContainer	aCConvNodeContainer;
			strData = aCConvNodeContainer.encode(&aCNodeContainer);
			if (strData.length() == 0)
			{
				iRv = -1;	//	aCentDedRessyaCont の内容が不正です。
			}
		}
	}
	//string = aCentDedRessyaCont の内容

	// --------------------------------
	//	クリップボードへの転送
	// --------------------------------
	if (iRv >= 0)
	{
		int iResult = stringToClipboard(
			AfxGetMainWnd()->GetSafeHwnd(),
			getCF_CentDedOperation(),
			strData);
		if (iResult < 0)
		{
			iRv = -11;	//	クリップボードへのデータ設定が失敗
		}
	}
	// --------------------------------
	return (iRv);
}

int CDiagramEditDoc::CentDedOperation_From_Cliboard(
	CentDedEkiJikoku& aCentDedEkiJikoku,
	bool& bSyubetsuChange,
	int& iEkiOrder)
{
	int iRv = 0;
	// --------------------------------
	//	クリップボードからデータを取得
	// --------------------------------
	tstring	strData;
	if (iRv >= 0) {
		if (!IsClipboardFormatAvailable(getCF_CentDedOperation())) {
			iRv = -1;	//	クリップボードには有効なデータはありません。
		}
	}
	if (iRv >= 0)
	{
		int iResult = stringFromClipboard(
			AfxGetMainWnd()->GetSafeHwnd(),
			getCF_CentDedOperation(),
			&strData);
		if (iResult < 0)
		{
			iRv = -2;	//	クリップボードからの読み込みに失敗しました。	
		}
	}
	//strData = CentDedOperation の内容
	// --------------------------------
	//	文字列から列車データを作成
	// --------------------------------
	//const Mu<CentDedEkiCont::CdDedEki>* pCdDedEkiCont =
	//	getCDiagramEditDoc()->getCDedRosenFileData()->
	//	getCentDedRosen()->getCentDedEkiCont()->getMuPtr(pCentDedRessya->getRessyahoukou());
	//deque<int> iEkiTrack2SizeCont;
	//for (int idxEki = 0; idxEki < pCdDedEkiCont->size(); idxEki++)
	//{
		//const CentDedEkiCont::CdDedEki aCdDedEki = pCdDedEkiCont->get(idxEki);
		//iEkiTrack2SizeCont.push_back(aCdDedEki.getCentDedEkiTrack2Cont().size());
	//}

	CNodeContainer aCNodeContainer;
	if (iRv >= 0)
	{
		CConvNodeContainer aCConvNodeContainer;
		int iResult = aCConvNodeContainer.decode(
			strData,
			&aCNodeContainer);
		if (iResult < 0)
		{
			iRv = -3;	//	クリップボードの内容が不正です。
		}
	}

	//int iEkiOrderTemp;
	if (iRv >= 0)
	{
		iEkiOrder = _ttoi(aCNodeContainer.getValue(nameEkiOrder).c_str());
		if (iEkiOrder < 0 || iEkiOrder >= getCDiagramEditDoc()->getCDedRosenFileData()->
			getCentDedRosen()->getCentDedEkiCont()->size())
		{
			iRv = -4;//iEkiOrderが範囲外です。
		}

	}

	if (iRv >= 0)
	{
		CconvCentDed aCconvCentDed;
		COuErrorInfoContainer aCOuErrorInfoContainer;

		tstring strEkijikoku = aCNodeContainer.getValue(nameEkiJikoku);
		//CentDedEkiJikoku aCentDedEkiJikokuBefore;
		//iEkiTrack2Countには、INT_MAXを指定しておき、番線数を超過しているかどうかのチェックは、貼り付け時に行う
		int iResult = aCconvCentDed.CentDedEkiJikoku_From_string(
			&aCentDedEkiJikoku,
			INT_MAX,
			0,
			strEkijikoku);

		//CentDedEkiJikoku aCentDedEkiJikokuAfter(aCentDedEkiJikokuBefore);
		if (iResult < 0)
		{
			iRv = -5;
		}
		else
		{
			//番線数同様、路線外発着駅数もINT_MAXを指定しておき、貼り付け時にチェックを行う
			tstring strParentIndex = to_tstring(iEkiOrder) + _T('B');
			iResult = aCconvCentDed.CentDedBeforeOperationCont_From_string(
				aCentDedEkiJikoku.getCentDedBeforeOperationCont(),
				strParentIndex,
				INT_MAX,
				INT_MAX,
				aCNodeContainer.getIfNodeContainerConst());
		}

		if (iResult < 0)
		{
			iRv = -6;
		}
		else
		{
			tstring strParentIndex = to_tstring(iEkiOrder) + _T('A');
			iResult = aCconvCentDed.CentDedAfterOperationCont_From_string(
				aCentDedEkiJikoku.getCentDedAfterOperationCont(),
				strParentIndex,
				INT_MAX,
				INT_MAX,
				aCNodeContainer.getIfNodeContainerConst());
		}

		if (iResult < 0)
		{
			iRv = -7;
		}
		else
		{
			bSyubetsuChange = aCNodeContainer.getValue(nameSyubetsuChange) == _T("1");
		}
	}

	// --------------------------------
	return (iRv);
}
bool CDiagramEditDoc::CentDedOperation_IsClipboardFormatAvailable()
{
	return (IsClipboardFormatAvailable(getCF_CentDedOperation()) != 0);
}

UINT CDiagramEditDoc::getCF_RessyaJouhou()
{
	return RegisterClipboardFormat(_T("CF_CentDedRessyaJouhou"));
}

int CDiagramEditDoc::RessyaJouhou_To_Cliboard(
	const CentDedRessya* pCentDedRessya)
{
	int iRv = 0;

	// --------------------------------
	//	データを文字列化
	// --------------------------------
	tstring	strData;
	if (iRv >= 0)
	{
		CNodeContainer aCNodeContainer;
		CconvCentDed aCconvCentDed;
		int iResult = aCconvCentDed.CentDedRessya_To_OuPropertiesText(
			pCentDedRessya,
			false,
			&aCNodeContainer);
		if (iRv < 0)
		{
			iRv = -1;	//	aCentDedRessya の内容が不正です。
		}
		else
		{
			CConvNodeContainer	aCConvNodeContainer;
			strData = aCConvNodeContainer.encode(&aCNodeContainer);
			if (strData.length() == 0)
			{
				iRv = -1;	//	aCentDedRessya の内容が不正です。
			}
		}
	}
	//string = aCentDedRessyaCont の内容

	// --------------------------------
	//	クリップボードへの転送
	// --------------------------------
	if (iRv >= 0)
	{
		int iResult = stringToClipboard(
			AfxGetMainWnd()->GetSafeHwnd(),
			getCF_RessyaJouhou(),
			strData);
		if (iResult < 0)
		{
			iRv = -11;	//	クリップボードへのデータ設定が失敗
		}
	}
	// --------------------------------
	return (iRv);
}

int CDiagramEditDoc::RessyaJouhou_From_Cliboard(
	CentDedRessya* pCentDedRessya)
{
	int iRv = 0;
	// --------------------------------
	//	クリップボードからデータを取得
	// --------------------------------
	tstring	strData;
	if (iRv >= 0) {
		if (!IsClipboardFormatAvailable(getCF_RessyaJouhou())) {
			iRv = -1;	//	クリップボードには有効なデータはありません。
		}
	}
	if (iRv >= 0)
	{
		int iResult = stringFromClipboard(
			AfxGetMainWnd()->GetSafeHwnd(),
			getCF_RessyaJouhou(),
			&strData);
		if (iResult < 0)
		{
			iRv = -2;	//	クリップボードからの読み込みに失敗しました。	
		}
	}
	// --------------------------------
	//	文字列から列車データを作成
	// --------------------------------
	const Mu<CentDedEkiCont::CdDedEki>* pCdDedEkiCont =
		getCDiagramEditDoc()->getCDedRosenFileData()->
		getCentDedRosen()->getCentDedEkiCont()->getMuPtr(pCentDedRessya->getRessyahoukou());
	vector<int> iEkiTrack2CountCont;
	vector<int> iMainTrackCont;
	vector<int> iOuterTerminalCountCont;
	for (int idxEki = 0; idxEki < pCdDedEkiCont->size(); idxEki++)
	{
		const CentDedEkiCont::CdDedEki aCdDedEki = pCdDedEkiCont->get(idxEki);
		iEkiTrack2CountCont.push_back(aCdDedEki.getCentDedEkiTrack2Cont().size());
		iMainTrackCont.push_back(aCdDedEki.getMainTrack());
		iOuterTerminalCountCont.push_back(aCdDedEki.getOuterTerminalEkimeiCount());
	}

	CNodeContainer aCNodeContainer;
	if (iRv >= 0)
	{
		CConvNodeContainer aCConvNodeContainer;
		int iResult = aCConvNodeContainer.decode(
			strData,
			&aCNodeContainer);
		if (iResult < 0)
		{
			iRv = -3;	//	クリップボードの内容が不正です。
		}
	}

	if (iRv >= 0)
	{
		CconvCentDed aCconvCentDed;
		COuErrorInfoContainer aCOuErrorInfoContainer;

		int iResult = aCconvCentDed.CentDedRessya_From_OuPropertiesText(
			pCentDedRessya,
			iEkiTrack2CountCont,
			iMainTrackCont,
			iOuterTerminalCountCont,
			aCNodeContainer.getIfNodeContainerConst(),
			&aCOuErrorInfoContainer);
		if (iResult < 0)
		{
			iRv = -5;	//	CentDedRessya の内容が不正です。
		}
	}

	// --------------------------------
	return (iRv);
}
bool CDiagramEditDoc::RessyaJouhou_IsClipboardFormatAvailable()
{
	return (IsClipboardFormatAvailable(getCF_RessyaJouhou()) != 0);
}

// ********************************
	//@name 操作
	// ********************************
int CDiagramEditDoc::executeEditCmd( Ou< CRfEditCmd > pCmd ) 
{
	int iRv = 0 ;
	// --------------------------------
	//	コマンドを実行
	// --------------------------------
	if ( iRv >= 0 )
	{
		iRv = pCmd->execute( &m_CDedRosenFileData ) ;
	}
	// --------------------------------
	//	ビューの更新
	// --------------------------------
	if ( iRv >= 0 )
	{
		UpdateAllSubDocviews( NULL , 0 , 
			&CRfEditCmdHolder( pCmd ) ) ;
	}
	// --------------------------------
	//	Undo,Redo関係内部データ を更新
	//	Undo情報の保存/Redo情報はクリア
	// --------------------------------
	if ( iRv >= 0 )
	{
		m_contUndo.insert( pCmd ) ;
		while ( m_contUndo.size() > iUndoLevel )
		{
			m_contUndo.erase( 0 ) ;
		}

		m_contRedo.erase( 0 , INT_MAX ) ;
		
		if ( m_iModifyCountFromDoc != INT_MAX )
		{
			if ( m_iModifyCountFromDoc < 0 )
			{
				m_iModifyCountFromDoc = INT_MAX ;
			}
			else
			{
				m_iModifyCountFromDoc ++ ;
			}
		}
	}
	// --------------------------------
	//	ModifiedFlag を更新
	// --------------------------------
	SetModifiedFlag( m_iModifyCountFromDoc != 0 ) ;

	// backupを実施
	if(m_bBackupEnable)
	{
		backup();
	}

	return ( iRv ) ;
}

/** 時刻の書式を保持します。 */
//const CdDedJikoku::CConv	g_CdDedJikokuConv(
//	true,		//	NoColon 
//				// 時が 00 から 09 の場合、10の位の "0" を削除します。
//	CdDedJikoku::CConv::EHour_ZeroToNone,
//	CdDedJikoku::CConv::ESecond_NoSecond 	// 秒を常に出力しません。 
//);
//
//const CdDedJikoku::CConv	g_CdDedJikokuConvSecond(
//	true,		//	NoColon 
//				// 時が 00 から 09 の場合、10の位の "0" を削除します。
//	CdDedJikoku::CConv::EHour_ZeroToNone,
//	CdDedJikoku::CConv::ESecond_Output
//);
//const CdDedJikoku::CConv	g_CdDedJikokuConvColon(
//	false,		//	コロンあり
//				// 時が 00 から 09 の場合、10の位の "0" を削除します。
//	CdDedJikoku::CConv::EHour_ZeroToNone,
//	CdDedJikoku::CConv::ESecond_NoSecond 	// 秒を常に出力しません。 
//);
//
//const CdDedJikoku::CConv	g_CdDedJikokuConvSecondColon(
//	false,		//	コロンあり
//				// 時が 00 から 09 の場合、10の位の "0" を削除します。
//	CdDedJikoku::CConv::EHour_ZeroToNone,
//	CdDedJikoku::CConv::ESecond_Output
//);
int CDiagramEditDoc::CentDedOperationTable_To_Cliboard(
	const tstring& strData)
{
	int iRv = 0;

	// --------------------------------
	//	クリップボードへの転送
	// --------------------------------
	if (iRv >= 0)
	{
		int iResult = stringToClipboard(
			AfxGetMainWnd()->GetSafeHwnd(),
			CF_UNICODETEXT,
			strData);
		if (iResult < 0)
		{
			iRv = -11;	//	クリップボードへのデータ設定が失敗
		}
	}
	return iRv;
}
//int CDiagramEditDoc::CentDedOperationTable_To_Cliboard(
//	const int iDiaIndex,
//	const list<OperationTableContent>* ListOperationTableContent,
//	const bool bDisplaySecondEkiJikoku,
//	const bool bDisplayColonEkiJikoku,
//	const bool bDisplayParentSyubetsu,
//	const bool bDisplayNoboriLeftToRight)
//{
//	int iRv = 0;
//	
//	// --------------------------------
//	//	データを文字列化
//	// --------------------------------
//	tstring	strData;
//	if (iRv >= 0)
//	{
//		const CentDedDia* pCentDedDia = 
//			getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
//			->getCentDedDiaCont()->getMuPtr()->get(iDiaIndex);
//		const CentDedRessyaCont* pCentDedRessyaCont[2];
//		for (int iRessyahoukou = Ressyahoukou_Kudari;
//			iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
//		{
//			pCentDedRessyaCont[iRessyahoukou] = 
//				pCentDedDia->getCentDedRessyaCont((ERessyahoukou)iRessyahoukou);
//		}
//		const CentDedRessyasyubetsuCont* pCentDedRessyasyubetsuCont =
//			getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedRessyasyubetsuCont();
//		const CentDedEkiCont* pCentDedEkiCont =
//			getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont();
//
//		for (auto itr = ListOperationTableContent->begin();
//			itr != ListOperationTableContent->end(); itr++)
//		{
//			const CentDedRessya aShihatsuRessya =
//				pCentDedRessyaCont[itr->aRessyaProperty.getRessyahoukou()]
//				->get(itr->aRessyaProperty.getRessyaIndex());
//			const CentDedRessya* pCentDedRessyaLast;// = pCentDedRessya;
//
//			auto itrLast = itr;
//			do {
//				pCentDedRessyaLast =
//					pCentDedRessyaCont[itrLast->aRessyaProperty.getRessyahoukou()]->getMuPtr()
//					->get(itrLast->aRessyaProperty.getRessyaIndex());
//				if (itrLast->eAfterType != EBeforeAfterType::BeforeAfterType_PropertySame)
//				{
//					break;
//				}
//				itrLast++;
//			} while (itrLast != ListOperationTableContent->end());
//
//			const CentDedRessya aShuchakuRessya = *pCentDedRessyaLast;
//			const OperationTableContent aSihatsuOperationTableContent = *itr;
//			const OperationTableContent aShuchakuOperationTableContent = *itrLast;
//			ERessyahoukou eRessyahoukou;
//
//
//
//			const CentDedRessyasyubetsu* pCentDedRessyasyubetsu = pCentDedRessyasyubetsuCont
//				->getMuPtr()->get(aShihatsuRessya.getRessyasyubetsuIndex());
//			if (bDisplayParentSyubetsu && pCentDedRessyasyubetsu->getParentSyubetsuIndex() >= 0)
//			{
//				pCentDedRessyasyubetsu = pCentDedRessyasyubetsuCont
//					->getMuPtr()->get(pCentDedRessyasyubetsu->getParentSyubetsuIndex());
//			}
//
//			int iSihatsuEkiOrder = aSihatsuOperationTableContent.iSihatsuEkiOrder;
//			if (!aShihatsuRessya.isRunBetweenNextEki(iSihatsuEkiOrder))
//			{
//				iSihatsuEkiOrder = aShihatsuRessya.getRunBetweenEkiForward(iSihatsuEkiOrder);
//			}
//			int iSihatsuEkiIndex = aShihatsuRessya.EkiIndexOfEkiOrder(iSihatsuEkiOrder);
//
//			int iSyuuchakuEkiOrder = aShuchakuOperationTableContent.iSyuuchakuEkiOrder;
//			if (!aShuchakuRessya.isRunBetweenNextEki(iSyuuchakuEkiOrder - 1))
//			{
//				iSyuuchakuEkiOrder = aShuchakuRessya.getRunBetweenEkiBackward(iSyuuchakuEkiOrder);
//			}
//			int iSyuuchakuEkiIndex = aShuchakuRessya.EkiIndexOfEkiOrder(iSyuuchakuEkiOrder);
//
//			if (iSihatsuEkiIndex < iSyuuchakuEkiIndex)
//			{
//				eRessyahoukou = ERessyahoukou::Ressyahoukou_Kudari;
//			}
//			else if (iSihatsuEkiIndex > iSyuuchakuEkiIndex)
//			{
//				eRessyahoukou = ERessyahoukou::Ressyahoukou_Nobori;
//			}
//			else
//			{
//				eRessyahoukou = aShihatsuRessya.getRessyahoukou();
//			}
//
//			tstring strDataTemp;
//			/**
//				複数列車を一本化している場合は、列車情報(列車番号等)は、aShihatsuRessya(先頭列車)からとります
//			*/
//
//			//列車番号
//			strDataTemp += aShihatsuRessya.getRessyabangou();
//			strDataTemp += _T("");
//
//			//	種別
//			strDataTemp += pCentDedRessyasyubetsu->getSyubetsumei();
//			strDataTemp += _T("");
//
//			if (getCDiagramEditDoc()->getCDedRosenFileData()
//				->getCdDedDispProp().getDisplayRessyamei())
//			{
//				//	列車名
//
//				//列車名のテキスト
//				tstring strRessyamei = aShihatsuRessya.getRessyamei();
//				if (!aShihatsuRessya.getGousuu().empty())
//				{
//					strRessyamei += _T(" ");
//					strRessyamei += aShihatsuRessya.getGousuu();
//					strRessyamei += _T("号");
//				}
//				strDataTemp += strRessyamei;
//				strDataTemp += _T("");
//			}
//
//			/**
//				始発終着駅の駅名と時刻取得について
//				・路線外始発の場合は、ほぼ従来通り。
//					Before,AfterOperationから路線外始発/終着駅Indexを取得、駅Orderと合わせて、駅名を取得
//				・入出区・前次列車接続の場合
//					iEkiOrderをもとに、その駅の発/着時刻を取得するが、isRunBetweenNextEkiを見るようにする
//			*/
//			{
//				//	始発駅名&始発駅時刻
//				int iXColumnNumber1;
//				int iXColumnNumber2;
//				//bool bIsHatsuJikoku = eRessyahoukou == Ressyahoukou_Kudari ||
//				//	getDisplayNoboriLeftToRight();
//				if (eRessyahoukou == Ressyahoukou_Kudari ||
//					bDisplayNoboriLeftToRight)
//				{
//					tstring strEkimei;
//					CdDedJikoku aCdDedJikoku;
//					//if (bIsHatsuJikoku)
//					//{
//					if (aSihatsuOperationTableContent.iOuterShihatsuekiIndex != INT_MIN)
//					{
//						int iOuterTerminalIndex = aSihatsuOperationTableContent.iOuterShihatsuekiIndex;
//						strEkimei = pCentDedEkiCont->get(iSihatsuEkiIndex).getOuterTerminalEkimei(iOuterTerminalIndex);
//						aCdDedJikoku = aSihatsuOperationTableContent.OuterShihatsuJikoku;
//					}
//					else
//					{
//						int iValidSihatsuEkiOrder = iSihatsuEkiOrder;
//						if (!aShihatsuRessya.isRunBetweenNextEki(iSihatsuEkiOrder))
//						{
//							iValidSihatsuEkiOrder = aShihatsuRessya.getRunBetweenEkiForward(iSihatsuEkiOrder);
//						}
//
//						strEkimei = pCentDedEkiCont->get(iSihatsuEkiIndex).getEkimei();
//						aCdDedJikoku = aShihatsuRessya.getCentDedEkiJikoku(iValidSihatsuEkiOrder).getHatsujikoku();
//					}
//					strDataTemp += strEkimei;
//					strDataTemp += getCdDedJikokuConv().encode(aCdDedJikoku, false);
//
//					tstring strArrow = _T("→");
//
//					if (aShuchakuOperationTableContent.iOuterShuchakuekiIndex != INT_MIN)
//					{
//						int iOuterTerminalIndex = aShuchakuOperationTableContent.iOuterShuchakuekiIndex;
//						strEkimei = pCentDedEkiCont->get(iSyuuchakuEkiIndex).getOuterTerminalEkimei(iOuterTerminalIndex);
//						aCdDedJikoku = aShuchakuOperationTableContent.OuterShuchakuJikoku;
//					}
//					else
//					{
//						int iValidSyuuchakuEkiOrder = iSyuuchakuEkiOrder;
//						if (!aShuchakuRessya.isRunBetweenNextEki(iSyuuchakuEkiOrder - 1))
//						{
//							iValidSyuuchakuEkiOrder = aShuchakuRessya.getRunBetweenEkiBackward(iSyuuchakuEkiOrder);
//						}
//
//						strEkimei = pCentDedEkiCont->get(iSyuuchakuEkiIndex).getEkimei();
//						aCdDedJikoku = aShuchakuRessya.getCentDedEkiJikoku(iValidSyuuchakuEkiOrder).getChakujikoku();
//					}
//					pCDcdTextbox1->setText(strEkimei);
//					pCDcdTextbox2->
//						setText(getCdDedJikokuConv().encode(aCdDedJikoku, true));
//				}
//				else
//				{
//
//					tstring strEkimei;
//					CdDedJikoku aCdDedJikoku;
//					if (aShuchakuOperationTableContent.iOuterShuchakuekiIndex != INT_MIN)
//					{
//						int iOuterTerminalIndex = aShuchakuOperationTableContent.iOuterShuchakuekiIndex;
//						strEkimei = pCentDedEkiCont->get(iSyuuchakuEkiIndex).getOuterTerminalEkimei(iOuterTerminalIndex);
//						aCdDedJikoku = aShuchakuOperationTableContent.OuterShuchakuJikoku;
//					}
//					else
//					{
//						int iValidSyuuchakuEkiOrder = iSyuuchakuEkiOrder;
//						if (!aShuchakuRessya.isRunBetweenNextEki(iSyuuchakuEkiOrder - 1))
//						{
//							iValidSyuuchakuEkiOrder = aShuchakuRessya.getRunBetweenEkiBackward(iSyuuchakuEkiOrder);
//						}
//
//						strEkimei = pCentDedEkiCont->get(iSyuuchakuEkiIndex).getEkimei();
//						aCdDedJikoku = aShuchakuRessya.getCentDedEkiJikoku(iValidSyuuchakuEkiOrder).getChakujikoku();
//					}
//					pCDcdTextbox1->setText(strEkimei);
//					pCDcdTextbox2->
//						setText(getCdDedJikokuConv().encode(aCdDedJikoku, true));
//
//					strArrow = _T("←");
//
//
//					tstring strEkimei;
//					CdDedJikoku aCdDedJikoku;
//					//if (bIsHatsuJikoku)
//					//{
//					if (aSihatsuOperationTableContent.iOuterShihatsuekiIndex != INT_MIN)
//					{
//						int iOuterTerminalIndex = aSihatsuOperationTableContent.iOuterShihatsuekiIndex;
//						strEkimei = pCentDedEkiCont->get(iSihatsuEkiIndex).getOuterTerminalEkimei(iOuterTerminalIndex);
//						aCdDedJikoku = aSihatsuOperationTableContent.OuterShihatsuJikoku;
//					}
//					else
//					{
//						int iValidSihatsuEkiOrder = iSihatsuEkiOrder;
//						if (!aShihatsuRessya.isRunBetweenNextEki(iSihatsuEkiOrder))
//						{
//							iValidSihatsuEkiOrder = aShihatsuRessya.getRunBetweenEkiForward(iSihatsuEkiOrder);
//						}
//
//						strEkimei = pCentDedEkiCont->get(iSihatsuEkiIndex).getEkimei();
//						aCdDedJikoku = aShihatsuRessya.getCentDedEkiJikoku(iValidSihatsuEkiOrder).getHatsujikoku();
//					}
//					pCDcdTextbox1->setText(strEkimei);
//					pCDcdTextbox2->
//						setText(getCdDedJikokuConv().encode(aCdDedJikoku, false));
//				}
//				Ou<CDcdTextbox> pCDcdTextbox1 =
//					getCXDcdGrid()->getCell(iXColumnNumber1, iYColumnNumber)->getIfDcDraw();
//				Ou<CDcdTextbox> pCDcdTextbox2 =
//					getCXDcdGrid()->getCell(iXColumnNumber2, iYColumnNumber)->getIfDcDraw();
//
//				tstring strEkimei;
//				CdDedJikoku aCdDedJikoku;
//				//if (bIsHatsuJikoku)
//				//{
//				if (aSihatsuOperationTableContent.iOuterShihatsuekiIndex != INT_MIN)
//				{
//					int iOuterTerminalIndex = aSihatsuOperationTableContent.iOuterShihatsuekiIndex;
//					strEkimei = pCentDedEkiCont->get(iSihatsuEkiIndex).getOuterTerminalEkimei(iOuterTerminalIndex);
//					aCdDedJikoku = aSihatsuOperationTableContent.OuterShihatsuJikoku;
//				}
//				else
//				{
//					int iValidSihatsuEkiOrder = iSihatsuEkiOrder;
//					if (!aShihatsuRessya.isRunBetweenNextEki(iSihatsuEkiOrder))
//					{
//						iValidSihatsuEkiOrder = aShihatsuRessya.getRunBetweenEkiForward(iSihatsuEkiOrder);
//					}
//
//					strEkimei = pCentDedEkiCont->get(iSihatsuEkiIndex).getEkimei();
//					aCdDedJikoku = aShihatsuRessya.getCentDedEkiJikoku(iValidSihatsuEkiOrder).getHatsujikoku();
//				}
//				//}
//				//else
//				//{
//				//	if (aShuchakuOperationTableContent.iOuterShuchakuekiIndex != INT_MIN)
//				//	{
//				//		int iOuterTerminalIndex = aSihatsuOperationTableContent.iOuterShuchakuekiIndex;
//				//		strEkimei = pCentDedEkiCont->get(iSyuuchakuEkiIndex).getOuterTerminalEkimei(iOuterTerminalIndex);
//				//		aCdDedJikoku = aShuchakuOperationTableContent.OuterShuchakuJikoku;
//				//	}
//				//	else
//				//	{
//				//		int iValidSyuuchakuEkiOrder = aShuchakuOperationTableContent.iSyuuchakuEkiOrder;
//				//		if (!aShuchakuRessya.isRunBetweenNextEki(iSyuuchakuEkiOrder - 1))
//				//		{
//				//			iValidSyuuchakuEkiOrder = aShuchakuRessya.getRunBetweenEkiBackward(iSyuuchakuEkiOrder);
//				//		}
//
//				//		strEkimei = pCentDedEkiCont->get(iSyuuchakuEkiIndex).getEkimei();
//				//		aCdDedJikoku = aShuchakuRessya.getCentDedEkiJikoku(iValidSyuuchakuEkiOrder).getChakujikoku();
//				//	}
//				//}
//				pCDcdTextbox1->setText(strEkimei);
//				pCDcdTextbox2->
//					setText(getCdDedJikokuConv().encode(aCdDedJikoku, false));
//
//				//	フォント属性
//				CdDrawTextProp	aCdDrawTextProp1 =
//					pCDcdTextbox1->getCdDrawTextProp();
//				aCdDrawTextProp1.setCdFontProp(fontpropDefault);
//				aCdDrawTextProp1.setTextColor(colorpropDefault);
//				aCdDrawTextProp1.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
//				pCDcdTextbox1->setCdDrawTextProp(aCdDrawTextProp1);
//
//				CdDrawTextProp	aCdDrawTextProp2 =
//					pCDcdTextbox2->getCdDrawTextProp();
//				aCdDrawTextProp2.setCdFontProp(fontpropDefault);
//				aCdDrawTextProp2.setTextColor(colorpropDefault);
//				aCdDrawTextProp2.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
//				pCDcdTextbox2->setCdDrawTextProp(aCdDrawTextProp2);
//
//				getCXDcdGrid()->getCell(iXColumnNumber1, iYColumnNumber)->setAttachCellCount(1, 1);
//				getCXDcdGrid()->getCell(iXColumnNumber2, iYColumnNumber)->setAttachCellCount(1, 1);
//				//	セルを無効化
//				InvalidateCell(iXColumnNumber1, iYColumnNumber);
//				InvalidateCell(iXColumnNumber2, iYColumnNumber);
//			}
//			{
//				//	終着駅名&終着駅時刻
//				int iXColumnNumber1;
//				int iXColumnNumber2;
//				if (eRessyahoukou == Ressyahoukou_Kudari ||
//					getDisplayNoboriLeftToRight())
//				{
//					iXColumnNumber1 = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
//						CdOperationTableXColSpec::EColumnType::ColumnType_TerminalSideEkimei));
//					iXColumnNumber2 = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
//						CdOperationTableXColSpec::EColumnType::ColumnType_TerminalSideEkijikoku));
//				}
//				else
//				{
//					iXColumnNumber1 = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
//						CdOperationTableXColSpec::EColumnType::ColumnType_OriginSideEkimei));
//					iXColumnNumber2 = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
//						CdOperationTableXColSpec::EColumnType::ColumnType_OriginSideEkijikoku));
//				}
//				Ou<CDcdTextbox> pCDcdTextbox1 =
//					getCXDcdGrid()->getCell(iXColumnNumber1, iYColumnNumber)->getIfDcDraw();
//				Ou<CDcdTextbox> pCDcdTextbox2 =
//					getCXDcdGrid()->getCell(iXColumnNumber2, iYColumnNumber)->getIfDcDraw();
//
//				tstring strEkimei;
//				CdDedJikoku aCdDedJikoku;
//				//bool bIsChakuJikoku = aCentDedRessya.getRessyahoukou() == Ressyahoukou_Kudari ||
//				//	getDisplayNoboriLeftToRight();
//				//if (bIsChakuJikoku)
//				//{
//				if (aShuchakuOperationTableContent.iOuterShuchakuekiIndex != INT_MIN)
//				{
//					int iOuterTerminalIndex = aShuchakuOperationTableContent.iOuterShuchakuekiIndex;
//					strEkimei = pCentDedEkiCont->get(iSyuuchakuEkiIndex).getOuterTerminalEkimei(iOuterTerminalIndex);
//					aCdDedJikoku = aShuchakuOperationTableContent.OuterShuchakuJikoku;
//				}
//				else
//				{
//					int iValidSyuuchakuEkiOrder = iSyuuchakuEkiOrder;
//					if (!aShuchakuRessya.isRunBetweenNextEki(iSyuuchakuEkiOrder - 1))
//					{
//						iValidSyuuchakuEkiOrder = aShuchakuRessya.getRunBetweenEkiBackward(iSyuuchakuEkiOrder);
//					}
//
//					strEkimei = pCentDedEkiCont->get(iSyuuchakuEkiIndex).getEkimei();
//					aCdDedJikoku = aShuchakuRessya.getCentDedEkiJikoku(iValidSyuuchakuEkiOrder).getChakujikoku();
//				}
//				//}
//				//else
//				//{
//				//	if (aOperationTableContent.iOuterShihatsuekiIndex != INT_MIN)
//				//	{
//				//		int iOuterTerminalIndex = aOperationTableContent.iOuterShihatsuekiIndex;
//				//		strEkimei = pCdDedEkiCont->get(aOperationTableContent.iSihatsuEkiOrder).getOuterTerminalEkimei(iOuterTerminalIndex);
//				//		aCdDedJikoku = aOperationTableContent.OuterShihatsuJikoku;
//				//	}
//				//	//if (aOperationTableContent.BeforeOperation->getBOperation()
//				//	//	== CentDedBeforeOperation::BOperation_Outer)
//				//	//{
//				//	//	int iOuterTerminalIndex = aOperationTableContent.BeforeOperation->getOuterShihatsuekiIndex();
//				//	//	strEkimei = pCdDedEkiCont->get(aOperationTableContent.iSihatsuEkiOrder).getOuterTerminalEkimei(iOuterTerminalIndex);
//				//	//	aCdDedJikoku = aOperationTableContent.BeforeOperation->getOuterShihatsuJikoku();
//				//	//}
//				//	else
//				//	{
//				//		int iSihatsuEkiOrder = aOperationTableContent.iSihatsuEkiOrder;
//				//		if (!aCentDedRessya.isRunBetweenNextEki(iSihatsuEkiOrder))
//				//		{
//				//			iSihatsuEkiOrder = aCentDedRessya.getRunBetweenEkiForward(iSihatsuEkiOrder);
//				//		}
//
//				//		strEkimei = pCdDedEkiCont->get(iSihatsuEkiOrder).getEkimei();
//				//		aCdDedJikoku = aCentDedRessya.getCentDedEkiJikoku(iSihatsuEkiOrder).getHatsujikoku();
//				//	}
//				//}
//				pCDcdTextbox1->setText(strEkimei);
//				pCDcdTextbox2->
//					setText(getCdDedJikokuConv().encode(aCdDedJikoku, true));
//
//				//	フォント属性
//				CdDrawTextProp	aCdDrawTextProp1 =
//					pCDcdTextbox1->getCdDrawTextProp();
//				aCdDrawTextProp1.setCdFontProp(fontpropDefault);
//				aCdDrawTextProp1.setTextColor(colorpropDefault);
//				aCdDrawTextProp1.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
//				pCDcdTextbox1->setCdDrawTextProp(aCdDrawTextProp1);
//
//				CdDrawTextProp	aCdDrawTextProp2 =
//					pCDcdTextbox2->getCdDrawTextProp();
//				aCdDrawTextProp2.setTextColor(colorpropDefault);
//				aCdDrawTextProp2.setCdFontProp(fontpropDefault);
//				aCdDrawTextProp2.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
//				pCDcdTextbox2->setCdDrawTextProp(aCdDrawTextProp2);
//
//				getCXDcdGrid()->getCell(iXColumnNumber1, iYColumnNumber)->setAttachCellCount(1, 1);
//				getCXDcdGrid()->getCell(iXColumnNumber2, iYColumnNumber)->setAttachCellCount(1, 1);
//				//	セルを無効化
//				InvalidateCell(iXColumnNumber1, iYColumnNumber);
//				InvalidateCell(iXColumnNumber2, iYColumnNumber);
//			}
//			{
//				//	列車方向(矢印)
//				int iXColumnNumber = aXColSpecCont.ColumnNumberFromSpec(CdOperationTableXColSpec(
//					CdOperationTableXColSpec::EColumnType::ColumnType_Ressyahoukou));
//				Ou<CDcdTextbox> pCDcdTextbox =
//					getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->getIfDcDraw();
//
//				tstring strArrow = _T("→");
//				if (eRessyahoukou == Ressyahoukou_Nobori &&
//					!getDisplayNoboriLeftToRight())
//				{
//					strArrow = _T("←");
//				}
//				pCDcdTextbox->setText(strArrow);
//
//				//	フォント属性
//				CdDrawTextProp	aCdDrawTextProp =
//					pCDcdTextbox->getCdDrawTextProp();
//				aCdDrawTextProp.setCdFontProp(fontpropDefault);
//				aCdDrawTextProp.setTextColor(colorpropDefault);
//				aCdDrawTextProp.setCdDrawTextFormat(CdDrawTextFormat(CdDrawTextFormat::H_CENTER));
//				pCDcdTextbox->setCdDrawTextProp(aCdDrawTextProp);
//
//				getCXDcdGrid()->getCell(iXColumnNumber, iYColumnNumber)->setAttachCellCount(1, 1);
//				//	セルを無効化
//				InvalidateCell(iXColumnNumber, iYColumnNumber);
//			}
//
//			strData += strDataTemp;
//			//strData += _T("\n");
//			strData += _T("\r\n");
//			itr = itrLast;
//		}
//
//		if (iRv < 0)
//		{
//			iRv = -1;	//	ListOperationTableContent の内容が不正です。
//		}
//		else
//		{
//			if (strData.length() == 0)
//			{
//				iRv = -1;	//	ListOperationTableContent の内容が不正です。
//			}
//		}
//	}
//	//strData = CentDedEkiTrack2 の内容
//
//	// --------------------------------
//	//	クリップボードへの転送
//	// --------------------------------
//	if (iRv >= 0)
//	{
//		int iResult = stringToClipboard(
//			AfxGetMainWnd()->GetSafeHwnd(),
//			CF_UNICODETEXT,
//			strData);
//		if (iResult < 0)
//		{
//			iRv = -11;	//	クリップボードへのデータ設定が失敗
//		}
//	}
//	return iRv;
//}


bool CDiagramEditDoc::canUndo() 
{
	return ( m_contUndo.size() > 0 ) ; 
}
int CDiagramEditDoc::undo() 
{
	LogMsg(_T("CDiagramEditDoc::undo()") ) ;
	int iRv = 0 ;

	Ou< CRfEditCmd >	pCmd ;
	// --------------------------------
	//	コマンドをキューから取得
	// --------------------------------
	if ( iRv >= 0 ){
		if ( m_contUndo.size() >= 1 ){
			pCmd = m_contUndo.get( INT_MAX ) ;
		}	else	{
			iRv = -1 ;	//	undo 情報がありません。
		}
	}
	//pcmdUndo = undo のためのコマンド
	// --------------------------------
	//	コマンドを実行
	// --------------------------------
	Ou< CRfEditCmd >	pUndoCmd ;
	if ( iRv >= 0 ){
		pUndoCmd = pCmd->createUndoCmd() ;
		if ( pUndoCmd == NULL ){
			iRv = -2 ;	//	undo の実行に失敗
		}
	}
	if ( iRv >= 0 ){
		int iResult  = pUndoCmd->execute( &m_CDedRosenFileData ) ;
		if ( iResult < 0 ){
			iRv = -2 ;	//	undo の実行に失敗
		}
	}
	// --------------------------------
	//	ビューの更新
	// --------------------------------
	if ( iRv >= 0 ){
		UpdateAllSubDocviews( NULL , 0 , 
			&CRfEditCmdHolder( pUndoCmd ) ) ;
	}
	// --------------------------------
	//	Undo,Redo関係内部データ を更新
	//	Undo情報をRedo情報に移動
	// --------------------------------
	if ( iRv >= 0 )
	{
		m_contUndo.erase( INT_MAX ) ;
		m_contRedo.insert( pCmd ) ;

		if ( m_iModifyCountFromDoc != INT_MAX )
		{
				m_iModifyCountFromDoc -- ;
		}
	}

	// --------------------------------
	//	ModifiedFlag を更新
	// --------------------------------
	SetModifiedFlag( m_iModifyCountFromDoc != 0 ) ;
	LogMsg(_T("CDiagramEditDoc::undo()=") ) ;


	return ( iRv ) ;
}

bool CDiagramEditDoc::canRedo() 
{
	return ( m_contRedo.size() > 0 ) ; 
}

int CDiagramEditDoc::redo() 
{
	LogMsg(_T("CDiagramEditDoc::redo()") ) ;
	int iRv = 0 ;

	Ou< CRfEditCmd >	pCmd ;
	// --------------------------------
	//	コマンドをキューから取得
	// --------------------------------
	if ( iRv >= 0 ){
		if ( m_contRedo.size() >= 1 ){
			pCmd = m_contRedo.get( INT_MAX ) ;
		}	else	{
			iRv = -1 ;	//	redo 情報がありません。
		}
	}
	//pcmdUndo = undo のためのコマンド
	// --------------------------------
	//	コマンドを実行
	// --------------------------------
	if ( iRv >= 0 )
	{
		int iResult  = pCmd->execute( &m_CDedRosenFileData ) ;
		if ( iResult < 0 ){
			iRv = -2 ;	//	redo の実行に失敗
		}
	}
	// --------------------------------
	//	ビューの更新
	// --------------------------------
	if ( iRv >= 0 ){
		UpdateAllSubDocviews( NULL , 0 , 
			&CRfEditCmdHolder( pCmd ) ) ;
	}
	// --------------------------------
	//	Undo,Redo関係内部データ を更新
	//	Redo情報をUndo情報に移動
	// --------------------------------
	if ( iRv >= 0 ){
		m_contRedo.erase( INT_MAX ) ;
		m_contUndo.insert( pCmd ) ;

		if ( m_iModifyCountFromDoc != INT_MAX )
		{
				m_iModifyCountFromDoc ++ ;
		}
	}

	// --------------------------------
	//	ModifiedFlag を更新
	// --------------------------------
	SetModifiedFlag( m_iModifyCountFromDoc != 0 ) ;

	LogMsg(_T("CDiagramEditDoc::redo()=") ) ;
	return ( iRv ) ;
}

const int iBackupIntervalSecond = 60;

int CDiagramEditDoc::backup()
{
	//backupの流れ、
	//(1)前backupからの経過時間を確認。
	//(2)経過時間が一定以上なら、新しくバックアップファイルを保存する
	//(3)古いバックアップファイルを削除する。
	if (m_ttPrevBackup < 0)
	{
		return -1; //前回のバックアップ時刻が不正です。
	}

	time_t ttNow = time(NULL);

	int iElapsedTime = (int)difftime(ttNow, m_ttPrevBackup);

	if (iElapsedTime < iBackupIntervalSecond)
	{
		return -2;//前回のバックアップから一定時間が経過していません。
	}

	struct tm tmNow;
	errno_t err;
	err = localtime_s(&tmNow, &ttNow);
	if (err)
	{
		return -3;//現在時刻修得時にエラーが発生しました・
	}
	CString strTimestamp;
	//strTimestamp.Format(_T("%04d%02d%02d%02d%02d%02d"),
	//	tmNow->tm_year + 1900,
	//	tmNow->tm_mon + 1,
	//	tmNow->tm_mday,
	//	tmNow->tm_hour,
	//	tmNow->tm_min,
	//	tmNow->tm_sec);
	strTimestamp.Format(_T("%04d%02d%02d%02d%02d"),
		tmNow.tm_year + 1900,
		tmNow.tm_mon + 1,
		tmNow.tm_mday,
		tmNow.tm_hour,
		tmNow.tm_min);

	CString strNewBackupPathName = GetPathName();
	if (strNewBackupPathName.IsEmpty())
	{
		return -4; //まだファイル名が定まっていないファイルです。
	}

	//バックアップファイル名を生成する。
	//命名規則は、元のファイル名(拡張子は除く) + _(アンダーバー) + 現在の日時(yyyymmddhhmm) + 仮拡張子(.oud2backup)
	strNewBackupPathName = strNewBackupPathName.Left(strNewBackupPathName.ReverseFind(_T('.')));
	strNewBackupPathName += _T("_");
	strNewBackupPathName += strTimestamp;
	strNewBackupPathName += _T(".oud2backup");

	DoSave(strNewBackupPathName, FALSE);

	//以前のバックアップファイルが存在する場合は、それを削除する。
	if (PathFileExists(m_strBackupPathName) && !PathIsDirectory(m_strBackupPathName))
	{
		DeleteFile(m_strBackupPathName);
	}

	//バックアップ時刻と、ファイルパスを更新する。
	m_strBackupPathName = strNewBackupPathName;
	m_ttPrevBackup = ttNow;

	return 1;

}


// ----------------------------------------------------------------
//	MFC
// ----------------------------------------------------------------

IMPLEMENT_DYNCREATE(CDiagramEditDoc, CHidemdiRootDoc)

BEGIN_MESSAGE_MAP(CDiagramEditDoc, CHidemdiRootDoc)
	//{{AFX_MSG_MAP(CDiagramEditDoc)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, &CDiagramEditDoc::OnUpdateEditUndo)
	ON_COMMAND(ID_EDIT_UNDO, &CDiagramEditDoc::OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, &CDiagramEditDoc::OnUpdateEditRedo)
	ON_COMMAND(ID_EDIT_REDO, &CDiagramEditDoc::OnEditRedo)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, &CDiagramEditDoc::OnUpdateFileSaveAs)
	//ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, &CDiagramEditDoc::OnUpdateFileSave)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiagramEditDoc クラスの構築/消滅

CDiagramEditDoc::CDiagramEditDoc()
	: m_iModifyCountFromDoc( 0 ) 
	, m_ttPrevBackup(time_t())
	, m_strBackupPathName(CString())
	, m_bBackupEnable(true)
	, m_bWindowPlacementRestore(true)
	, m_iRosenViewWidth(-1)
{
	m_contChildWindow.clear();
}

CDiagramEditDoc::~CDiagramEditDoc()
{
}

BOOL CDiagramEditDoc::OnNewDocument()
{
	if (!CHidemdiRootDoc::OnNewDocument())
		return FALSE;

	// TODO: この位置に再初期化処理を追加してください。
	// (SDI ドキュメントはこのドキュメントを再利用します。)

	//閉じる前のバックアップがあったら、それを削除しておく

	//backup関係の処理
	//(1)iniファイルからバックアップの有効無効を読み込み。
	//(2)バックアップ有効なら、時刻を初期化。
	//backup用に時刻を初期化
	getCDiagramEditApp()->readCDiagramEditProp();
	if (m_bBackupEnable)
	{
		m_ttPrevBackup = time(NULL);
		m_strBackupPathName.Empty();
	}

	return TRUE;
}




/////////////////////////////////////////////////////////////////////////////
// CDiagramEditDoc クラスの診断

#ifdef _DEBUG
void CDiagramEditDoc::AssertValid() const
{
	CHidemdiRootDoc::AssertValid();
}

void CDiagramEditDoc::Dump(CDumpContext& dc) const
{
	CHidemdiRootDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDiagramEditDoc コマンド

void CDiagramEditDoc::DeleteContents() 
{
	m_CDedRosenFileData.clear() ;
	// --------------------------------
	//	Undo,Redo関係内部データ を更新
	// --------------------------------
	m_contUndo.erase( 0 , INT_MAX ) ;
	m_contRedo.erase( 0 , INT_MAX ) ;
	m_iModifyCountFromDoc = 0 ;

	// --------------------------------
	//	路線ビューを更新
	// --------------------------------
	getCDiagramEditApp()->getCDlgRosenView()->OnUpdate( NULL , 0 , NULL ) ;
	// --------------------------------

	//　バックアップファイルを削除
	if (PathFileExists(m_strBackupPathName) && !PathIsDirectory(m_strBackupPathName))
	{
		DeleteFile(m_strBackupPathName);
		m_strBackupPathName.Empty();
	}

	CHidemdiRootDoc::DeleteContents();
}

//int CDiagramEditDoc::OnOpenDocument_ConvFile( 
//	LPCTSTR lpszDllFilename , 
//	std::vector< char >* pbinFileContent , 
//	CString* pstrError ) 
//{
//	int iRv = 0 ;
//	CString	strError ;
//
//		if ( iRv >= 0 )
//		{
//			IfConvFile* pIfConvFile = NULL ;
//			CConvFileDll	aCConvFileDll( lpszDllFilename ) ;
//			if ( iRv >= 0 )
//			{
//				int iResult = aCConvFileDll.validate() ;
//				if ( iResult < 0 )
//				{
//					strError = MfcUtil::LoadCString( IDS_ERR_DLLNOTFOUND ) ;
//					strError += "\n" ;
//					strError += aCConvFileDll.getDllFilename().c_str()  ;
//					iRv = -101 ;
//				}
//				else
//				{
//					pIfConvFile = aCConvFileDll.getIfConvFile() ;
//				}
//			}
//			//aCConvFileDll = DLLをロードしました。
//	
//			LogMsg( "CDiagramEditDoc::OnOpenDocument()31" ) ;
//			if ( iRv >= 0 )
//			{
//				std::vector<char>	binFileContentNew ;
//				int iResult = pIfConvFile->isLeftFormat( 
//					&CaByteBuffer_vector< std::vector< char > >( pbinFileContent ) ) ;
//				LogMsg( "CDiagramEditDoc::OnOpenDocument()32" ) ;
//				if ( iResult >= 0 )
//				{
//					//	FileFormat が、このDLLであることが確認できました。
//					string strErrorInfoString ;
//					int iResult = pIfConvFile->LeftToRight( 
//						&CaByteBuffer_vector< std::vector< char > >( pbinFileContent ) , 
//						&CaByteBuffer_vector< std::vector< char > >( &binFileContentNew ) , 
//						&CaByteBuffer_string( &strErrorInfoString )  ) ;
//					if ( iResult >= 0 )
//					{
//						*pbinFileContent = binFileContentNew ;
//					}
//					else
//					{
//						
//						strError = MfcUtil::LoadCString( IDS_ERR_FILECONVERT_FAILED ) ;
//						strError += "\n" ;
//						//strError += aCConvFileDll.getDllFilename().c_str()  ;
//						if ( strErrorInfoString.size() > 0 )
//						{
//							strError += strErrorInfoString.c_str() ;
//							strError += "\n" ;
//						}
//						iRv = -102 ;	//	ファイルの変換に失敗しました。
//					}
//				}
//				else	
//				{
//					iRv = -1 ;	//このDLLがサポートするファイル形式ではありませんでした。
//				}
//			}
//			LogMsg( "CDiagramEditDoc::OnOpenDocument()33" ) ;
//		}
//	// --------------------------------
//	if ( pstrError != NULL )
//	{
//		*pstrError = strError ;
//	}
//	return iRv ;
//}


BOOL CDiagramEditDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	CWaitCursor	aCWaitCursor ;

	LogMsg(_T("CDiagramEditDoc::OnOpenDocument(%s)") , lpszPathName ) ;
	//	Serialize は使いません。
	//
	//if (!CHidemdiRootDoc::OnOpenDocument(lpszPathName))
	//	return FALSE;

	// --------------------------------
	//	拡張子が .dia なら、
	//	WinDIA の処理
	// --------------------------------
	//CdFilenameStr	aCdFilenameStr( lpszPathName ) ;
	//if ( _stricmp( "dia" , aCdFilenameStr.Extension().c_str() ) == 0 )
	//{
	//	return OnOpenDocument_WinDia( lpszPathName ) ;
	//}
	// --------------------------------
	int iRv = 0 ;
	CString	strError ;

	//(1)iniファイルからバックアップ及びウインドウ位置の復元の有効無効を読み込み。
	getCDiagramEditApp()->readCDiagramEditProp();

	// --------------------------------
	//	ファイルの内容を、stringに保存
	// --------------------------------
	tstring	strFile ;
	if ( iRv >= 0 )
	{
		int iResult = stringFromFile( &strFile , lpszPathName ) ;
		//iResult = 
		//	-1: ファイルがオープンできません。
		//	-2 ; 読み込みに失敗しました。
		//	-3 ; ファイルには "\0" が含まれます(バイナリファイルであると 
		//	思われます)。
		//	 この場合、pString には、 "\0" の直前までのデータが格納されて 
		//	います。 
		if ( iResult < 0 ){
			iRv = iResult ;
			switch( iResult ){
			 case -1 :	// ファイルがオープンできません。
				{
					CString	strFmt ;
					strFmt.LoadString( IDS_ERR_FILENOTFOUND ) ;
					strError.Format( strFmt , lpszPathName ) ;
				}
				break ;
			 case -2 :	//; 読み込みに失敗しました。
				{
					CString	strFmt ;
					strFmt.LoadString( IDS_ERR_FILEREAD ) ;
					strError.Format( strFmt , lpszPathName ) ;
				}
				break ;
			 case -3 :	// ファイルには "\0" が含まれます
				{
					CString	strFmt ;
					strFmt.LoadString( IDS_ERR_FILEFORMAT ) ;
					strError.Format( strFmt , lpszPathName ) ;
				}
				break ;
			}
			//iRv = 
			//	-1: ファイルがオープンできません。
			//	-2 ; 読み込みに失敗しました。
			//	-3 ; ファイルには "\0" が含まれます(バイナリファイルであると 
			//	思われます)。
			//	 この場合、pString には、 "\0" の直前までのデータが格納されて 
			//	います。 
		}
	}
	//strFile = ファイルの内容

	tstring strOudFile = strFile ;
	//strOudFile = ファイルの内容を保持します。
	//	但し、このファイルのフォーマットが古い場合は、
	//	今後の処理で内容が代わります。


	LogMsg( _T("CDiagramEditDoc::OnOpenDocument()1") ) ;



	// --------------------------------
	//	ファイルが解釈不能の場合は
	//	変換を試みます。
	// --------------------------------
	//CconvCDedRosenFileData	aConv ;

	//if ( iRv >= 0 && aConv.isEncodeAbleFormat( strOudFile ) < 0 )
	//{
	//	LogMsg( "CDiagramEditDoc::OnOpenDocument()2" ) ;
	//	
	//	bool	bFileTypeDetected = false ;
	//	std::vector<char>	binFileContent ;
	//	binFileContent = vectorCharOf( strCrlfOf( strOudFile ) ) ;

	//	LogMsg( "CDiagramEditDoc::OnOpenDocument()3" ) ;

	//	// --------------------------------
	//	//	ファイル変換を順次実行
	//	// --------------------------------
	//	const TCHAR* const arstrConvFileDllFilename[] = 
	//	{
	//		_T("ConvFileOudia02To03.dll" ),		//	Ver01,Ver02 → Ver03 に変換
	//		_T(  "ConvFileOudia03To05.dll"  ) , //	Ver03 → Ver05 に変換
	//		_T( "ConvFileOudia05To06.dll"  ) ,	//	Ver05 → Ver06 に変換
	//		_T( "ConvFileOudia06To101.dll" ) ,	//	Ver06 → Ver1.01 に変換
	//		_T( "ConvFileOudia101To102.dll" ) ,	//	Ver1.01 → Ver1.02 に変換
 //		};
	//	for ( int idx = 0 ;
	//		iRv >= 0 && idx < sizeof(arstrConvFileDllFilename)/sizeof(arstrConvFileDllFilename[0]);
	//		idx ++ )
	//	{
	//		iRv = OnOpenDocument_ConvFile( 
	//			arstrConvFileDllFilename[idx], 
	//			&binFileContent , 
	//			&strError ) ;
	//		if ( iRv == -1 )
	//		{
	//			//	フォーマットが認識できない場合は、
	//			//	他のフォーマット変換を試行するため、
	//			//	エラーにはしません。
	//			iRv = 0 ;	
	//		}
	//		else
	//		{
	//			bFileTypeDetected = true ;
	//		}
	//	}

	//	// --------------------------------
	//	if ( iRv >= 0 && !bFileTypeDetected )
	//	{
	//		strError.Format( MfcUtil::LoadCString( IDS_ERR_FILEFORMAT ) , 
	//				lpszPathName ) ;
	//		iRv = -31 ;	// FileTypeが認識できません。
	//			//iRv = 
	//			//	-31 ; // FileTypeが認識できません。
	//	}
	//	if ( iRv >= 0 )
	//	{
	//		strOudFile = strLfOf( stringOf( binFileContent ) ) ;
	//	}
	//	LogMsg( "CDiagramEditDoc::OnOpenDocument()101" ) ;
	//}
	//strOudFile = 旧バージョンファイルから変換後の内容に変わりました。

	// --------------------------------
	//	CDedRosenFileData
	//	カレントバージョンファイル
	//	aString ファイルの内容を解釈します。
	// --------------------------------
	if ( iRv >= 0 )
	{
		CDedRosenFileData	aCDedRosenFileData ;
		CconvCDedRosenFileData aConv ;
		COuErrorInfoContainer aCOuErrorInfoContainer ;
		int iFileType = aConv.isEncodeAbleFormat(strOudFile);
		int iResult = aConv.CDedRosenFileData_from_string( 
			&aCDedRosenFileData , 
			strOudFile , 
			&aCOuErrorInfoContainer ) ;
		//iResult = 
		//	-	-1 ;	//	ディレクトリが途中で閉じています。	
		//	-	-1001 ;	//	FileType が正しくありません。
		//	-	-1002 ;	//	Rosen Directoryが見つかりません。
		//	-	-1022 ;	//	Ekijikokukeisiki の値が不正です。
		//	-	-1032 ;	//	Ekikibo の値が不正です。
		//	-	-1101 ;	//	Eki がディレクトリではありません。
		//	-	-1111 ;	//	Syubetsumei が指定されていません。
		//	-	-1152 ;	//	DiagramSenStyle の値が不正です。
		//	-	-1201 ;	//	Ressyasyubetsu がディレクトリではありません。
		//	-	-1211 ;	//	DiaName が指定されていません。
		//	-	-1212 ;	//	RessyaContが見つかりません。
		//	-	-1352 ;	//	起点時刻の設定が不適切です。
		//	-	-1003 ;	//	DispProp Directoryが見つかりません。
		//	-	-1512 ;	//	JikokuhyouFont の内容が不正です。
		//	-	-1522 ;	//	DiaEkimeiFont の内容が不正です。
		//	-	-1532 ;	//	DiaJikokuFont の内容が不正です。
		//	-	-1582 ;	//	DisplayRessyabangou が不正です。
		//	-	-1592 ;	//	DisplayRessyamei が不正です。
		//	-	-1602 ;	//	DiaRessyajouhouHyoujiEkiOrderKudari が不正です。
		//	-	-1612 ;	//	DiaRessyajouhouHyoujiEkiOrderNobori が不正です。
		if ( iResult < 0 )
		{
			iRv = iResult ;
			//iRv = 
			//	-	-1 ;	//	ディレクトリが途中で閉じています。	
			//	-	-1001 ;	//	FileType が正しくありません。
			//	-	-1002 ;	//	Rosen Directoryが見つかりません。
			//	-	-1022 ;	//	Ekijikokukeisiki の値が不正です。
			//	-	-1032 ;	//	Ekikibo の値が不正です。
			//	-	-1101 ;	//	Eki がディレクトリではありません。
			//	-	-1111 ;	//	Syubetsumei が指定されていません。
			//	-	-1152 ;	//	DiagramSenStyle の値が不正です。
			//	-	-1201 ;	//	Ressyasyubetsu がディレクトリではありません。
			//	-	-1211 ;	//	DiaName が指定されていません。
			//	-	-1212 ;	//	RessyaContが見つかりません。
			//	-	-1352 ;	//	起点時刻の設定が不適切です。
			//	-	-1003 ;	//	DispProp Directoryが見つかりません。
			//	-	-1512 ;	//	JikokuhyouFont の内容が不正です。
			//	-	-1522 ;	//	DiaEkimeiFont の内容が不正です。
			//	-	-1532 ;	//	DiaJikokuFont の内容が不正です。
			//	-	-1582 ;	//	DisplayRessyabangou が不正です。
			//	-	-1592 ;	//	DisplayRessyamei が不正です。
			//	-	-1602 ;	//	DiaRessyajouhouHyoujiEkiOrderKudari が不正です。
			//	-	-1612 ;	//	DiaRessyajouhouHyoujiEkiOrderNobori が不正です。

			{
				CString	strFmt ;
				strFmt.LoadString( IDS_ERR_FILEFORMAT_ERRORCODE ) ;
				strError.Format( strFmt , lpszPathName , iRv ) ;
			}

			tstring strOuErrorInfoText = aCOuErrorInfoContainer.toOuErrorInfoText() ;
			if ( !strOuErrorInfoText.empty() )
			{
				strError += _T("\n\n") ;
				strError += _T("(") ;
				strError += strOuErrorInfoText.c_str() ;
				strError += _T(")") ;
			}

		}
		else
		{
			m_CDedRosenFileData = aCDedRosenFileData ;
		}
	}


	// --------------------------------
	//	路線ビューを更新
	// --------------------------------
	getCDiagramEditApp()->getCDlgRosenView()->OnUpdate( NULL , 0 , NULL ) ;
	// --------------------------------
	//	エラーメッセージの表示
	// --------------------------------
	LogMsg( _T("CDiagramEditDoc::OnOpenDocument()=%d") , iRv ) ;
	if ( iRv < 0 )
	{
		tstring strFileTypeAppComment ;
		//	strFileTypeAppComment を取得
		CNodeContainer aCNodeContainer ;
		CConvNodeContainer aCConvNodeContainer ;
		int iResult = aCConvNodeContainer.decode( 
			strFile , 
			&aCNodeContainer ) ;
		if ( iResult >= 0 )
		{
			strFileTypeAppComment = aCNodeContainer.getValue( nameFileTypeAppComment );
		}
		//strFileTypeAppComment = 項目名 FileTypeAppComment の内容

		
		if ( strError.IsEmpty() )
		{
			CString	strFmt ;
			strFmt.LoadString( IDS_ERR_ERRORCODE ) ;
			strError.Format( strFmt , iRv ) ;
		}
		if ( !strFileTypeAppComment.empty() )
		{
			CString strFmt ;
			strFmt.LoadString( IDS_ERR_FileTypeAppComment ) ;
			CString strLs ;
			strLs.Format( strFmt , strFileTypeAppComment.c_str() ) ;
			strError += _T("\n\n(") ;
			strError += strLs ;
			strError += _T(")") ;

		}
		AfxMessageBox( strError , MB_ICONSTOP ) ; 
	}

	//backup関係の処理
	//(2)バックアップ有効なら、時刻を初期化。
	if (m_bBackupEnable)
	{
		m_ttPrevBackup = time(NULL);
	}

	//ウインドウ位置の復元
	if (m_bWindowPlacementRestore &&
		m_contChildWindow.size() > 0)
	{
		getCDiagramEditApp()->getCMainFrame()->getCDlgRosenView()->SetWindowPos(/*&CWnd::wndBottom*/NULL, 0, 0, m_iRosenViewWidth, INT_MAX, SWP_NOMOVE);
		//getCDiagramEditApp()->getCMainFrame()->getCDlgRosenView()->MoveWindow(0, 0, m_iRosenViewWidth, 100);

		RECT rectMainFlame{};
		getCDiagramEditApp()->getCMainFrame()->GetWindowRect((LPRECT)&rectMainFlame);

		for (int idx = 0; idx < (int)m_contChildWindow.size(); idx++)
		{
			if (m_contChildWindow[idx].iWindowType == 2)
			{
				CDedDiagramDoc* pCDedDiagramDoc = NULL;
				CDedDiagramView* pCDedDiagramView = NULL;
				pCDedDiagramDoc = getCDiagramEditApp()->openCDedDiagramDoc(
					m_CDedRosenFileData.getCentDedRosen()->getCentDedDiaCont()->getMuPtr()->get(m_contChildWindow[idx].iDiaIndex));

				//pCJikokuhyouDoc = CJikokuhyouDocへのポインタ
				if (pCDedDiagramDoc != NULL)
				{
					POSITION aPOSITION = pCDedDiagramDoc->GetFirstViewPosition();
					if (aPOSITION != NULL) {
						pCDedDiagramView = (CDedDiagramView*)pCDedDiagramDoc
							->GetNextView(aPOSITION);
					}
				}

				if (pCDedDiagramView != NULL)
				{

					pCDedDiagramView->GetParent()->MoveWindow(
						/*rectMainFlame.left +*/ m_contChildWindow[idx].iXPos,
						/*rectMainFlame.top + */m_contChildWindow[idx].iYPos,
						m_contChildWindow[idx].iXSize,
						m_contChildWindow[idx].iYSize);
				}

			}
			else if (m_contChildWindow[idx].iWindowType == 5)
			{
				CAllOperationTableDoc* pCAllOperationTableDoc = NULL;
				CAllOperationTableView* pCAllOperationTableView = NULL;
				pCAllOperationTableDoc = getCDiagramEditApp()->openCAllOperationTableDoc(
					m_CDedRosenFileData.getCentDedRosen()->getCentDedDiaCont()->getMuPtr()->get(m_contChildWindow[idx].iDiaIndex));

				//pCJikokuhyouDoc = CJikokuhyouDocへのポインタ
				if (pCAllOperationTableDoc != NULL)
				{
					POSITION aPOSITION = pCAllOperationTableDoc->GetFirstViewPosition();
					if (aPOSITION != NULL) {
						pCAllOperationTableView = (CAllOperationTableView*)pCAllOperationTableDoc
							->GetNextView(aPOSITION);
					}
				}

				if (pCAllOperationTableView != NULL)
				{

					pCAllOperationTableView->GetParent()->MoveWindow(
						/*rectMainFlame.left + */m_contChildWindow[idx].iXPos,
						/*rectMainFlame.top + */m_contChildWindow[idx].iYPos,
						m_contChildWindow[idx].iXSize,
						m_contChildWindow[idx].iYSize);
				}

			}
			else if (m_contChildWindow[idx].iWindowType == 6)
			{
				CDedAllOperationTable2Doc* pCDedAllOperationTable2Doc = NULL;
				CDedAllOperationTable2View* pCDedAllOperationTable2View = NULL;
				pCDedAllOperationTable2Doc = getCDiagramEditApp()->openCDedAllOperationTable2Doc(
					m_CDedRosenFileData.getCentDedRosen()->getCentDedDiaCont()->getMuPtr()->get(m_contChildWindow[idx].iDiaIndex));

				//pCJikokuhyouDoc = CJikokuhyouDocへのポインタ
				if (pCDedAllOperationTable2Doc != NULL)
				{
					POSITION aPOSITION = pCDedAllOperationTable2Doc->GetFirstViewPosition();
					if (aPOSITION != NULL) {
						pCDedAllOperationTable2View = (CDedAllOperationTable2View*)pCDedAllOperationTable2Doc
							->GetNextView(aPOSITION);
					}
				}

				if (pCDedAllOperationTable2View != NULL)
				{

					pCDedAllOperationTable2View->GetParent()->MoveWindow(
						/*rectMainFlame.left + */m_contChildWindow[idx].iXPos,
						/*rectMainFlame.top + */m_contChildWindow[idx].iYPos,
						m_contChildWindow[idx].iXSize,
						m_contChildWindow[idx].iYSize);
				}

			}
			else
			{
				ERessyahoukou eRessyahoukou = ERessyahoukou::Ressyahoukou_Kudari;
				if (m_contChildWindow[idx].iWindowType == 1 ||
					m_contChildWindow[idx].iWindowType == 4)
				{
					eRessyahoukou = ERessyahoukou::Ressyahoukou_Nobori;
				}
				CJikokuhyouView* pJikokuhyouView = NULL;
				getCDiagramEditApp()->openCJikokuhyouDoc(
					m_CDedRosenFileData.getCentDedRosen()->getCentDedDiaCont()->getMuPtr()->get(m_contChildWindow[idx].iDiaIndex),
					eRessyahoukou,
					m_contChildWindow[idx].iWindowType > 1,
					& pJikokuhyouView);
				if (pJikokuhyouView != NULL)
				{
					//pJikokuhyouView->GetParent()->SetWindowPos(&CWnd::wndBottom,
					//	/*rectMainFlame.left +*/ m_contChildWindow[idx].iXPos,
					//	/*rectMainFlame.top + */m_contChildWindow[idx].iYPos,
					//	m_contChildWindow[idx].iXSize,
					//	m_contChildWindow[idx].iYSize,
					//	SWP_SHOWWINDOW);
					//pJikokuhyouView->GetParent()->SetWindowPos(&CWnd::wndBottom,
					//	20,
					//	20,
					//	m_contChildWindow[idx].iXSize,
					//	m_contChildWindow[idx].iYSize,
					//	SWP_SHOWWINDOW);
					pJikokuhyouView->GetParent()->MoveWindow(
						/*rectMainFlame.left +*/ m_contChildWindow[idx].iXPos,
						/*rectMainFlame.top + */m_contChildWindow[idx].iYPos,
						m_contChildWindow[idx].iXSize, 
						m_contChildWindow[idx].iYSize);
				}
			}
		}
	}
	return ( iRv >= 0 ) ;
}
BOOL CDiagramEditDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	CWaitCursor	aCWaitCursor ;

	
	LogMsg( _T("CDiagramEditDoc::OnSaveDocument(%s)") , lpszPathName ) ;
	//Serialize() は使いません。
	//
	//return CHidemdiRootDoc::OnSaveDocument(lpszPathName);


	// --------------------------------
	//	拡張子が .dia なら、
	//	WinDIA の処理
	// --------------------------------
	CdFilenameStr	aCdFilenameStr( lpszPathName ) ;
	//if ( _stricmp( "dia" , aCdFilenameStr.Extension().c_str() ) == 0 )
	//{
	//	return OnSaveDocument_WinDia( lpszPathName ) ;
	//}
	// --------------------------------
	int iRv = 0 ;

	CString strError ;

	bool bWriteANSI = false;

	// --------------------------------
	//	ファイルの内容のCdConnectedString2を作成
	// --------------------------------
	CNodeContainer aCNodeContainer ;
	// --------------------------------
	//	拡張子が .oud なら、Oudiaver1.02に変換して出力する
	//	メッセージボックスを出し、注意喚起する。
	// --------------------------------
	if (_tcsicmp(_T("oud"), aCdFilenameStr.Extension().c_str()) == 0)
	{
		CString strErrorMsg =
			_T("拡張子「.oud」で保存すると、一部の情報が失われます。\nよろしいですか。");
			//"拡張子「.oud」には上書き保存ができません。\n名前を付けて保存を選んでください。";
		if (AfxMessageBox(strErrorMsg, MB_OKCANCEL | MB_ICONWARNING) != IDOK)
		{
			return FALSE;
		}
		//AfxMessageBox(strErrorMsg, MB_OK | MB_ICONEXCLAMATION);

		if (iRv >= 0)
		{
			CconvCDedRosenFileDataOud aConv;
			int iResult = aConv.CDedRosenFileData_to_OuPropertiesText(
				&m_CDedRosenFileData,
				&aCNodeContainer);
			//iResult = 
			//		-	-22 ;	//	Ekijikokukeisiki の値が不正です。
			//		-	-32 ;	//	Ekikibo の値が不正です。
			//		-	-111 ;	//	Syubetsumei が指定されていません。
			//		-	-152 ;	//	DiagramSenStyle の値が不正です。
			//		-	-212 ;	//	DiagramEkiatsukai の値が不正です。
			if (iResult < 0)
			{
				iRv = iResult;
				strError.Format(IDS_ERR_FILEFORMAT, lpszPathName);
				//iRv = 
				//		-	-22 ;	//	Ekijikokukeisiki の値が不正です。
				//		-	-32 ;	//	Ekikibo の値が不正です。
				//		-	-111 ;	//	Syubetsumei が指定されていません。
				//		-	-152 ;	//	DiagramSenStyle の値が不正です。
				//		-	-212 ;	//	DiagramEkiatsukai の値が不正です。
			}
			bWriteANSI = true;
		}
	}
	else
	{
		if (iRv >= 0)
		{
			CconvCDedRosenFileData aConv;
			int iResult = aConv.CDedRosenFileData_to_OuPropertiesText(
				&m_CDedRosenFileData,
				&aCNodeContainer);
			//iResult = 
			//		-	-22 ;	//	Ekijikokukeisiki の値が不正です。
			//		-	-32 ;	//	Ekikibo の値が不正です。
			//		-	-111 ;	//	Syubetsumei が指定されていません。
			//		-	-152 ;	//	DiagramSenStyle の値が不正です。
			//		-	-212 ;	//	DiagramEkiatsukai の値が不正です。
			if (iResult < 0)
			{
				iRv = iResult;
				strError.Format(IDS_ERR_FILEFORMAT, lpszPathName);
				//iRv = 
				//		-	-22 ;	//	Ekijikokukeisiki の値が不正です。
				//		-	-32 ;	//	Ekikibo の値が不正です。
				//		-	-111 ;	//	Syubetsumei が指定されていません。
				//		-	-152 ;	//	DiagramSenStyle の値が不正です。
				//		-	-212 ;	//	DiagramEkiatsukai の値が不正です。
			}
		}
	}
		//aString = ファイルに書き込む『路線ファイル』形式の文字列を保持します。

	LogMsg( _T("CDiagramEditDoc::OnSaveDocument()1") ) ;

	// --------------------------------
	//	FileTypeAppComment を付与
	// --------------------------------
	if ( iRv >= 0 )
	{
		tstring strFileTypeAppComment ;
		strFileTypeAppComment += AfxGetAppName() ;
		strFileTypeAppComment += _T(" Ver. ") ;
		strFileTypeAppComment += getCDiagramEditApp()->getProgramVer() ;
		aCNodeContainer.setValue( nameFileTypeAppComment , strFileTypeAppComment );
	}
	
	// --------------------------------
	//	aCNodeContainer の内容を
	//	文字列に格納
	// --------------------------------
	tstring aString ;
	if ( iRv >= 0 ){
		//	CConnectedStringCompress による圧縮
		CConvNodeContainer aCConvNodeContainer ;
		aString = aCConvNodeContainer.encode( &aCNodeContainer ) ;
	}
	//	aString = ファイルに出力する文字列

	// --------------------------------
	//	stringの内容を、ファイルに書き込み
	// --------------------------------
	if ( iRv >= 0 ){
		int iResult = 0;
		if (bWriteANSI) 
		{
			iResult = stringToFileANSI(aString, lpszPathName);
		}
		else
		{
			iResult = stringToFile(aString, lpszPathName);
		}
		//iResult = 
		//	-1: ファイルがオープンできません。
		//	-2 ; // 書き込みに失敗しました。 
		if ( iResult < 0 ){
			iRv = iResult ;
			switch( iResult ){
			 case -1 :	// ファイルがオープンできません。
				{
					CString	strFmt ;
					strError.Format( IDS_ERR_FILECREATE , lpszPathName ) ;
				}
				break ;
			 case -2 :	//;書き込みに失敗しました
				{
					CString	strFmt ;
					strError.Format( IDS_ERR_FILEWRITE , lpszPathName ) ;
				}
				break ;
			}
			//iRv = 
			//	-1: ファイルがオープンできません。
			//	-2 ; 書き込みに失敗しました。
		}
	}

	// --------------------------------
	LogMsg( _T("CDiagramEditDoc::OnSaveDocument()=%d") , iRv ) ;

	if ( iRv < 0 )
	{
		if ( strError.IsEmpty() )
		{
			CString	strFmt ;
			strFmt.LoadString( IDS_ERR_ERRORCODE ) ;
			strError.Format( strFmt , iRv ) ;
		}
		AfxMessageBox( strError , MB_ICONSTOP ) ; 
		return ( FALSE ) ;
	}
	//	保存に成功したら、明示的に
	//	変更フラグを解除しなくてはなりません。
	//  ただし、バックアップ時(拡張子がoud2backup)は、変更フラグを解除しません。
	//  また、バックアップ時以外は、バックアップファイルを削除し、ファイルパスを初期化、
	//	バックアップ時刻をリセットします。

	// --------------------------------
	//	Undo,Redo関係内部データ を更新
	//	Undo情報をRedo情報に移動
	// --------------------------------
	if ( iRv >= 0 && _tcsicmp(_T("oud2backup"), aCdFilenameStr.Extension().c_str()) != 0)
	{
		m_iModifyCountFromDoc = 0 ;

		{
			if (PathFileExists(m_strBackupPathName) && !PathIsDirectory(m_strBackupPathName))
			{
				DeleteFile(m_strBackupPathName);
				m_strBackupPathName.Empty();
			}
			m_ttPrevBackup = time(NULL);
		}
	}

	// --------------------------------
	//	ModifiedFlag を更新
	// --------------------------------
	SetModifiedFlag( m_iModifyCountFromDoc != 0 ) ;
	return TRUE;
}

void CDiagramEditDoc::OnFileSaveAs() 
{
	CString	strExt ;
	getCDiagramEditApp()->pRootDoctmpl()->GetDocString( strExt , CDocTemplate::filterExt ) ;
	CString strBuf = GetPathName() ;
	if (_tcsncicmp(_tcsrev(_tcsdup( GetPathName() ) ) , _T("duo") , 3 ) == 0 )
	{
	CFileDialog	aDlg( FALSE , strExt , GetPathName()+ _T("2" ) ,
	  OFN_HIDEREADONLY | OFN_PATHMUSTEXIST
	  | OFN_OVERWRITEPROMPT , 
		getCDiagramEditApp()->getCFileDialogFilterSave() , NULL ) ;//edit_by_d_mania
		if ( aDlg.DoModal() != IDOK )
		{
			return ;
		}	
		// --------------------------------
		DoSave(aDlg.GetPathName(), TRUE ) ;
	}
	else
	{
	CFileDialog	aDlg( FALSE , strExt , GetPathName()  , 
	  OFN_HIDEREADONLY | OFN_PATHMUSTEXIST
	  | OFN_OVERWRITEPROMPT , 
		getCDiagramEditApp()->getCFileDialogFilterSave() , NULL ) ;//reedit_by_d_mania
		if ( aDlg.DoModal() != IDOK )
		{
			return ;
		}	
		// --------------------------------
		DoSave(aDlg.GetPathName(), TRUE ) ;
	}
}



void CDiagramEditDoc::OnUpdateFileSaveAs(CCmdUI *pCmdUI)
{
	//	名前を付けて保存 は、常時有効にしました。
	pCmdUI->Enable( TRUE ) ;
}

void CDiagramEditDoc::SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU) 
{
	CdFilenameStr	aCdFilenameStr( lpszPathName ) ;
	//if ( _stricmp( "dia" , aCdFilenameStr.Extension().c_str() ) == 0 )
	//{
	//	//	拡張子 .dia は、ドキュメントの有効なファイル名とは
	//	//	認めません。
	//	//	ただし、ドキュメントのタイトルとして、
	//	//	拡張子を取り除いた主ファイル名を設定します。
	//	CString a = GetTitle();
	//	//if ( GetTitle().IsEmpty() )
	//	//{
	//		SetTitle(aCdFilenameStr.BaseFilename().c_str() );
	//	//}
	//	return ;
	//}
	
	CHidemdiRootDoc::SetPathName(aCdFilenameStr.FullpathFilename().c_str() , bAddToMRU);
}

void CDiagramEditDoc::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	BOOL bEnable = FALSE ;
	{
		bEnable = this->canUndo() ;
	}
	pCmdUI->Enable( bEnable ) ;	
}

void CDiagramEditDoc::OnEditUndo()
{
	this->undo() ;
}

void CDiagramEditDoc::OnUpdateEditRedo(CCmdUI *pCmdUI)
{
	BOOL bEnable = FALSE ;
	{
		bEnable = this->canRedo() ;
	}
	pCmdUI->Enable( bEnable ) ;	
}

void CDiagramEditDoc::OnEditRedo()
{
	this->redo() ;
}