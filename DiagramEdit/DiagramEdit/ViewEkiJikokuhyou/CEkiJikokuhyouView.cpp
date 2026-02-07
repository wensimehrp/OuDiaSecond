/*
OuDiaSecond Copyright (C) 2017-2025 diagram_mania

このプログラムは、take-okm氏が作成したOuDiaを改造したソフトウェアです。
このプログラム利用については、take-okm氏記載の下記文書に準拠します。
*/
#include "stdafx.h"

#include "NsOu/OuNew.h"

#include "..\diagramedit.h"
#include "CEkiJikokuhyouView.h"

#include "logmsg/LogMsg.h"
#include "str/strToInt.h"
#include "DcDraw/print/CaDcdTargetZoomDisplay.h"
#include "DcDraw\CaDcdTargetItemPosition.h"
#include "DcDrawMfc\CDcdTargetMfcPrintInfo.h"
#include "DcdGrid\CaDcdGrid_PageSelector.h"
#include "..\Print\CconvCdPrintPageProp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace ViewEkiJikokuhyou {

	using namespace DcDrawLib::DcDraw::Print;
	using namespace DcDrawLib::DcDrawMfc;
	/////////////////////////////////////////////////////////////////////////////
	// CEkiJikokuhyouView

	// ----------------------------------------------------------------

	IMPLEMENT_DYNCREATE(CEkiJikokuhyouView, CView)

		CEkiJikokuhyouView::CEkiJikokuhyouView()
		: m_pCWndDcdGrid(NULL)
	{
	}

	CEkiJikokuhyouView::~CEkiJikokuhyouView()
	{
	}


	BEGIN_MESSAGE_MAP(CEkiJikokuhyouView, CView)
		//{{AFX_MSG_MAP(CEkiJikokuhyouView)
		ON_WM_CREATE()
		ON_WM_DESTROY()
		ON_WM_SIZE()
		ON_WM_SETFOCUS()
		//}}AFX_MSG_MAP
	// 標準印刷コマンド
		ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	END_MESSAGE_MAP()

	/////////////////////////////////////////////////////////////////////////////
	// CEkiJikokuhyouView 描画

	void CEkiJikokuhyouView::OnDraw(CDC* pDC)
	{
		CDocument* pDoc = GetDocument();
		// TODO: この位置に描画用のコードを追加してください
	}

	/////////////////////////////////////////////////////////////////////////////
	// CEkiJikokuhyouView 診断

#ifdef _DEBUG
	void CEkiJikokuhyouView::AssertValid() const
	{
		CView::AssertValid();
	}

	void CEkiJikokuhyouView::Dump(CDumpContext& dc) const
	{
		CView::Dump(dc);
	}
#endif //_DEBUG

	/////////////////////////////////////////////////////////////////////////////
	// CEkiJikokuhyouView メッセージ ハンドラ

	int CEkiJikokuhyouView::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		if (CView::OnCreate(lpCreateStruct) == -1)
			return -1;

		// --------------------------------	
		m_pCWndDcdGrid = new CWndDcdGridEkiJikokuhyou();
		m_pCWndDcdGrid->Create(this);
		m_pCWndDcdGrid->ShowWindow(SW_SHOW);


		return 0;
	}

	void CEkiJikokuhyouView::OnDestroy()
	{
		m_pCWndDcdGrid->DestroyWindow();
		delete m_pCWndDcdGrid;
		m_pCWndDcdGrid = NULL;

		CView::OnDestroy();
	}

	void CEkiJikokuhyouView::OnSize(UINT nType, int cx, int cy)
	{
		if (nType == SIZE_MAXIMIZED   //ウィンドウは最大表示されます。
			|| nType == SIZE_RESTORED  // ウィンドウはサイズ変更されますが、SIZE_MINIMIZED と SIZE_MAXIMIZED は適用されません。
			) {
			m_pCWndDcdGrid->MoveWindow(0, 0, cx, cy, TRUE);
			return;
		}

		CView::OnSize(nType, cx, cy);

	}

	void CEkiJikokuhyouView::OnSetFocus(CWnd* pOldWnd)
	{
		//CView::OnSetFocus(pOldWnd);

		CWnd*	pControl = GetNextDlgTabItem((CWnd*)NULL, FALSE);
		pControl->SetFocus();

	}

	BOOL CEkiJikokuhyouView::OnPreparePrinting(CPrintInfo* pInfo)
	{
		// デフォルトの印刷準備
		return DoPreparePrinting(pInfo);
	}

	void CEkiJikokuhyouView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
	{
		m_pCWndDcdGrid->OnUpdate(NULL, 0, NULL);

		CView::OnBeginPrinting(pDC, pInfo);
	}


	void CEkiJikokuhyouView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
	{
		if (pInfo != NULL) {
			//	印刷に関する処理
			LogMsg(_T("CEkiJikokuhyouView::OnPrepareDC() "));
			LogMsg(CDcdTargetMfcPrintInfo::stringOf(pInfo).c_str());
		}
		else {
			CView::OnPrepareDC(pDC, pInfo);
		}
	}

	static CdDrawTextProp	getCdDrawTextPropStandard()
	{
		return CdDrawTextProp(
			getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp().getOperationTableFont(),
			//CdFontProp(9, _T("Meiryo UI")),
			//CConverter_WinGdi().CdFontPropOf( DEFAULT_GUI_FONT ) ,
			getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp().getOperationStringColor());
			//CdColorProp(0, 0, 0));
	}


	void CEkiJikokuhyouView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
	{
		LogMsg(_T("CEkiJikokuhyouView::OnPrint() "));
		LogMsg(CDcdTargetMfcPrintInfo::stringOf(pInfo).c_str());

		// --------------------------------
		//	描画面を作成
		// --------------------------------
		CDcdTargetMfcPrintInfo	aCDcdTargetMfcPrintInfo(pDC, pInfo);

		// --------------------------------
		//	余白を除いた領域を作成
		// --------------------------------
		CaDcdTargetItemPosition	aTargetInnerMargin(&aCDcdTargetMfcPrintInfo,
			CdDcdZoneXy());
		{
			LogMsg(DeviceCapsToString(
				aCDcdTargetMfcPrintInfo.getPrinterHdc()).c_str());

			CconvCdPrintPageProp aCconvCdPrintPageProp;
			CdDcdZoneXy	zonexyInneraMargin =
				aCconvCdPrintPageProp.calcZoneInnerMargin(
					getCDiagramEditApp()->getCdPrintPageProp(),
					aCDcdTargetMfcPrintInfo.getPrinterHdc());
			if (zonexyInneraMargin.getX().getSize() <= 0) {
				zonexyInneraMargin.setX(
					aCDcdTargetMfcPrintInfo.getZone().getX());
			}
			if (zonexyInneraMargin.getY().getSize() <= 0) {
				zonexyInneraMargin.setY(
					aCDcdTargetMfcPrintInfo.getZone().getY());
			}

			aTargetInnerMargin.setZone(zonexyInneraMargin);

		}

		//aTargetInnerMargin = 余白部分を除いた描画領域。
		//	単位はプリンタのピクセルです。

		// --------------------------------
		//	論理座標を設定
		// --------------------------------
		CaDcdTargetZoomDisplay	aCaDcdTargetZoomDisplay(
			&aTargetInnerMargin,
			aCDcdTargetMfcPrintInfo.getPrinterHdc());
		//aCaDcdTargetZoomDisplay = 余白部分を除いた描画領域。
		//	単位は、画面上の１ピクセル相当になりました。

		// --------------------------------
		//	キャプションとページ番号の部品を作成
		// --------------------------------
		//Ou<CDcdText>	pdcdCaption;
		Ou<CDcdText>	pdcdPage;
		//{
		//	const CentDedRosen* pCentDedRosen =
		//		getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen();
		//	CEkiJikokuhyouDoc* pCEkiJikokuhyouDoc = (CEkiJikokuhyouDoc*)GetDocument();

		//	tstring	strText;
		//	//	路線名
		//	if (!pCentDedRosen->getName().empty())
		//	{
		//		strText += pCentDedRosen->getName();
		//		strText += _T(" ");
		//	}
		//	strText += pCEkiJikokuhyouDoc->getDiaName();
		//	strText += _T(" ");

		//	CString	aString;
		//	aString.LoadString(IDS_WORD_ALLOPERATIONTABLE);
		//	strText += (LPCTSTR)aString;

		//	pdcdCaption = OuNew<CDcdText>(new CDcdText(
		//		(LPCTSTR)pCEkiJikokuhyouDoc->GetTitle(), getCdDrawTextPropStandard()));
		//}
		// --------------------------------
		{
			CdDrawTextProp	aProp = getCdDrawTextPropStandard();
			CdDrawTextFormat	aFormat = aProp.getCdDrawTextFormat();
			aFormat.setHorizontal(aFormat.H_CENTER);
			aProp.setCdDrawTextFormat(aFormat);
			pdcdPage = OuNew<CDcdText>(new CDcdText(_T(""), aProp, _T("99")));
		}

		// --------------------------------
		//	キャプションとページ番号の部品・
		//	グリッドのレイアウトを決める	
		// --------------------------------
		//Ou<IfDcdTarget>	pTargetCaption;
		Ou<IfDcdTarget>	pTargetGrid;
		Ou<IfDcdTarget>	pTargetPage;
		{
			CdDcdZoneXy	zoneGrid = aCaDcdTargetZoomDisplay.getZone();
			CdDcdSizeXy	aSize;

			//pdcdCaption->getItemSize(&aCaDcdTargetZoomDisplay, &aSize);
			//CdDcdZoneXy zoneCaption(zoneGrid.getX(),
			//	CdDcdZone(zoneGrid.getY().getPos(), aSize.getY()));
			//if (getCDiagramEditApp()->getCdPrintPageProp().getPrintHeader() > 0)
			//{
			//	zoneGrid.setY(CdDcdZone().setBeginEndPos(
			//		zoneCaption.getY().getEndPos(), zoneGrid.getY().getEndPos()));
			//	//zoneCaption = 全領域の上部を、キャプション用に割り当てています。
			//	//zoneGrid = 全領域から、上部のキャプション領域を除いた領域です。
			//}

			pdcdPage->getItemSize(&aCaDcdTargetZoomDisplay, &aSize);
			CdDcdZoneXy zonePage(zoneGrid.getX(),
				CdDcdZone(zoneGrid.getY().getEndPos() - aSize.getY(), aSize.getY()));
			if (getCDiagramEditApp()->getCdPrintPageProp().getPrintFooter() > 0)
			{
				zoneGrid.setY(CdDcdZone().setBeginEndPos(
					zoneGrid.getY().getPos(), zonePage.getY().getPos()));
				//zoneCaption.getY().getEndPos(), zonePage.getY().getPos()));
			//zonePage = 全領域の下部を、ページ用に割り当てています。
			//zoneGrid = 上部のキャプションに続いて、下部のページ領域も除いた領域です。
			}


			//pTargetCaption = OuNew<CaDcdTargetItemPosition>(
			//	new CaDcdTargetItemPosition(&aCaDcdTargetZoomDisplay, zoneCaption));
			pTargetGrid = OuNew<CaDcdTargetItemPosition>(
				new CaDcdTargetItemPosition(&aCaDcdTargetZoomDisplay, zoneGrid));
			pTargetPage = OuNew<CaDcdTargetItemPosition>(
				new CaDcdTargetItemPosition(&aCaDcdTargetZoomDisplay, zonePage));
		}
		// --------------------------------
		//	グリッドを描画
		// --------------------------------
		int iPage = 0;
		{
			//	印刷時には、スクロールバーが動作しないようにします。
			//	スクロールと再描画を抑止します。
			CPropStack	aPropStack(m_pCWndDcdGrid);
			aPropStack.CDcdGrid_setUpdateCWndDcdGrid(false)
				.CFocus_setFixafterColumnNumberChange(false);

			CDcdGrid* pCDcdGrid = m_pCWndDcdGrid->getCXDcdGrid();
			CaDcdGrid_PageSelector	aCaDcdGrid_PageSelector(pCDcdGrid, pTargetGrid);
			aCaDcdGrid_PageSelector.setPage(pInfo->m_nCurPage - 1);
			aCaDcdGrid_PageSelector.DcDraw();

			if ((int)pInfo->m_nCurPage >= aCaDcdGrid_PageSelector.getPageCount()) {
				//最終ページを印刷したら、印刷ループを終わります。
				//OnPrint() で 
				//pInfo->SetMaxPage( aCaDcdGrid_PageSelector.getPageCount() ) ;
				//	をしても効果はありません。

				pInfo->m_bContinuePrinting = false;
			}
			else {
				pInfo->m_bContinuePrinting = true;
			}

			iPage = aCaDcdGrid_PageSelector.getPage();
		}
		// --------------------------------
		//	キャプションとページ番号のテキストを作成
		// --------------------------------
		{
			//ページ番号を決定
			{
				tstring	strPage = stringOf(iPage + 1);
				pdcdPage->setText(strPage);
			}
		}
		// --------------------------------
		//	キャプションとページ番号を描画
		// --------------------------------
		{
			//if (getCDiagramEditApp()->getCdPrintPageProp().getPrintHeader() > 0)
			//{
			//	pdcdCaption->DcDraw(pTargetCaption);
			//}
			if (getCDiagramEditApp()->getCdPrintPageProp().getPrintFooter() > 0)
			{
				pdcdPage->DcDraw(pTargetPage);
			}
		}
	}


	void CEkiJikokuhyouView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
	{
		//	印刷終了後に画面表示が崩れる問題を回避。
		//
		//	このクラスは、印刷中はグリッドのスクロール位置を
		//	一時的に変更します。
		//	このときに m_pCWndDcdGrid に再描画が発生すると、
		//	画面には一時的に位置の変更されたグリッドが
		//	描画されるため、画面が崩れます。
		m_pCWndDcdGrid->InvalidateGrid();

		CView::OnEndPrinting(pDC, pInfo);
	}

	void CEkiJikokuhyouView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
	{
		m_pCWndDcdGrid->OnUpdate(pSender, lHint, pHint);
	}
	void CEkiJikokuhyouView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
	{
		if (m_pCWndDcdGrid != NULL)
		{
			m_pCWndDcdGrid->OnActivateView(bActivate, pActivateView, pDeactiveView);
		}
	}

	BOOL CEkiJikokuhyouView::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
	{
		if (m_pCWndDcdGrid->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		{
			return TRUE;
		}

		return CView::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
	}
} //namespace ViewEkiJikokuhyou
