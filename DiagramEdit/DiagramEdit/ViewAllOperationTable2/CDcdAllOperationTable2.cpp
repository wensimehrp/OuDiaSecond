#include "CDcdAllOperationTable2.h"
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
//	CDcdAllOperationTable2.cpp
// ****************************************************************
*/
/** @file */
#include "stdafx.h"

#include "str\StrToInt.h"
#include "DcDraw\CDcdText.h"
#include "DcDraw\CDcdTargetGetDC.h"
#include "DcDraw\CDcdLine.h"
#include "DcDraw\CaDcdTargetItemPosition.h"
#include "DcDraw\CaDcdTargetClip.h"
#include "DcdCd\DcDrawProp/CdPenProp.h"
#include "LogMsg\LogMsg.h"
#include "DcDraw\CConverter_WinGdi.h"
#include "DcDraw\CDcdFillrect.h"

#include "CDcdAllOperationTable2.h"
#include "..\DiagramEdit.h"

namespace ViewAllOperationTable2 {

using namespace std ;
using namespace OuLib::Str;
// ****************************************************************
//	CDcdAllOperationTable2
// ****************************************************************
	// --------------------------------
	//@name 下請関数
	// --------------------------------
CdDcdFreeLineProp	CDcdAllOperationTable2::getCdLinePropGridNormal()const
{
	return CdDcdFreeLineProp(1, getGridColor());
};

CdDcdFreeLineProp	CDcdAllOperationTable2::getCdLinePropGridBold()const
{
	return CdDcdFreeLineProp(2, getGridColor());
};

CdDcdFreeLineProp	CDcdAllOperationTable2::getCdLinePropDiaJikuNormal()const
{
	return CdDcdFreeLineProp(1, getDiaJikuColor());
};

CdDcdFreeLineProp	CDcdAllOperationTable2::getCdLinePropDiaJikuBold()const
{
	return CdDcdFreeLineProp(2, getDiaJikuColor());
};

CDcdText	CDcdAllOperationTable2::getCDcdTextJikoku()const
{
	return CDcdText(_T("") ,
		CdDrawTextProp( m_fontpropDiaJikokuFont , getStringColor()) ,
		_T("00") ) ;
};

vector<CDcdText>	CDcdAllOperationTable2::getCDcdTextHeader()const
{
	//tstring strExtent;
	vector<CDcdText> CDcdTextCont;
	{
		//列番号
		tstring strExtent = _T("000");
		CDcdTextCont.push_back(
			CDcdText(_T(""),
				CdDrawTextProp(getOperationTableFont(), getStringColor()),
				strExtent));
	}
	{
		//運用番号
		tstring strExtent(
			getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp().getJikokuhyouRessyaWidth(), '0');
		if (strExtent.length() < 8)
		{
			strExtent = tstring(8, '0');
		}
		CDcdTextCont.push_back(
			CDcdText(_T(""),
				CdDrawTextProp(getOperationTableFont(), getStringColor()),
				strExtent));
	}
	if (getDisplayEkimeiJikoku())
	{
		//駅名の目安文字列
		tstring strExtentEkimei;
		for (int idx = 0; idx < m_iEkimeiLength; idx++) {
			strExtentEkimei += _T("岡");
		}
		//時刻の目安文字列
		tstring strExtentJikoku(
			getCDiagramEditDoc()->getCDedRosenFileData()->getCdDedDispProp().getJikokuhyouRessyaWidth(), '0');
		if (strExtentJikoku.length() < 6)
		{
			strExtentJikoku = tstring(6, '0');
		}

		//出区駅名
		CDcdTextCont.push_back(
			CDcdText(_T(""),
				CdDrawTextProp(getOperationTableFont(), getStringColor()),
				strExtentEkimei));

		//出区時刻
		CDcdTextCont.push_back(
			CDcdText(_T(""),
				CdDrawTextProp(getOperationTableFont(), getStringColor()),
				strExtentJikoku));

		//矢印
		CDcdTextCont.push_back(
			CDcdText(_T(""),
				CdDrawTextProp(getOperationTableFont(), getStringColor()),
				_T("→")));

		//入区駅名
		CDcdTextCont.push_back(
			CDcdText(_T(""),
				CdDrawTextProp(getOperationTableFont(), getStringColor()),
				strExtentEkimei));

		//入区時刻
		CDcdTextCont.push_back(
			CDcdText(_T(""),
				CdDrawTextProp(getOperationTableFont(), getStringColor()),
				strExtentJikoku));
	}

	return CDcdTextCont;
}

void	CDcdAllOperationTable2::setCdDcdZone_X(IfDcdTarget* pIfDcdTarget)
{
	CdDcdFreeLineProp	linepropBold(getCdLinePropGridBold());
	CdDcdFreeLineProp	linepropNormal(getCdLinePropGridNormal());
	vector< CDcdText> CDcdTextCont = getCDcdTextHeader();

	DcdPos aDcdPosTemp = linepropNormal.getLogicalunitWidth();

	//列番号
	CdDcdSizeXy	sizeTemp;
	CDcdTextCont[0].getItemSize(pIfDcdTarget, &sizeTemp);

	m_CdDcdZone_X_Left[0] = CdDcdZone(aDcdPosTemp, sizeTemp.getX());
	aDcdPosTemp += sizeTemp.getX();

	aDcdPosTemp += linepropNormal.getLogicalunitWidth();

	//運用番号
	CDcdTextCont[1].getItemSize(pIfDcdTarget, &sizeTemp);
	m_CdDcdZone_X_Left[1] = CdDcdZone(aDcdPosTemp, sizeTemp.getX());
	aDcdPosTemp += sizeTemp.getX();

	if (getDisplayEkimeiJikoku())
	{
		aDcdPosTemp += linepropNormal.getLogicalunitWidth();

		//出区駅名
		CDcdTextCont[2].getItemSize(pIfDcdTarget, &sizeTemp);
		m_CdDcdZone_X_Left[2] = CdDcdZone(aDcdPosTemp, sizeTemp.getX());
		aDcdPosTemp += sizeTemp.getX();

		aDcdPosTemp += linepropNormal.getLogicalunitWidth();
		//出区時刻
		CDcdTextCont[3].getItemSize(pIfDcdTarget, &sizeTemp);
		m_CdDcdZone_X_Left[3] = CdDcdZone(aDcdPosTemp, sizeTemp.getX());
		aDcdPosTemp += sizeTemp.getX();

		aDcdPosTemp += linepropNormal.getLogicalunitWidth();


		DcdPos aDcdPosTempRight = linepropBold.getLogicalunitWidth();
		//入区駅名
		CDcdTextCont[5].getItemSize(pIfDcdTarget, &sizeTemp);
		m_CdDcdZone_X_Right[0] = CdDcdZone(aDcdPosTempRight, sizeTemp.getX());
		aDcdPosTempRight += sizeTemp.getX();

		aDcdPosTempRight += linepropNormal.getLogicalunitWidth();

		//入区時刻
		CDcdTextCont[6].getItemSize(pIfDcdTarget, &sizeTemp);
		m_CdDcdZone_X_Right[1] = CdDcdZone(aDcdPosTempRight, sizeTemp.getX());
		aDcdPosTempRight += sizeTemp.getX();

		aDcdPosTempRight += linepropNormal.getLogicalunitWidth();

		//DcdSize sizeShift = pIfDcdTarget->getZone().getX().getEndPos() - aDcdPosTempRight;
		//m_CdDcdZone_X_Right[0] = m_CdDcdZone_X_Right[0].setPos(
		//	m_CdDcdZone_X_Right[0].getPos() + sizeShift);
		//m_CdDcdZone_X_Right[1] = m_CdDcdZone_X_Right[1].setPos(
		//	m_CdDcdZone_X_Right[1].getPos() + sizeShift);

	}

	aDcdPosTemp += linepropBold.getLogicalunitWidth();
}

	// ********************************
	//	コンストラクタ
	// ********************************
CDcdAllOperationTable2::CDcdAllOperationTable2( 
		tstring strName,
		vector<tstring>* strOperationNumber,
		CdDcdZoneXy* aCdDcdZone,
		const CdDedDispProp& aCdDedDispProp )
	//: m_fontpropDiaJikokuFont(9, _T("ＭＳ ゴシック"))
	: m_fontpropDiaJikokuFont( 9 , _T("Meiryo UI")  )
	, m_iEkimeiLength( 6 )
	, m_bDisplayEkimeiJikoku(true)
	, m_bNoDisplayLeftSpace(false)
	, m_bNoDisplayAllOperationTableSpace(false)
	, m_bNoDisplayRightSpace(false)
{
	m_pCDcdAllOperationTable = new CDcdAllOperationTable( 
		strName,
		strOperationNumber,
		aCdDcdZone,
		aCdDedDispProp ) ;
	m_fontpropDiaJikokuFont = aCdDedDispProp.getDiaJikokuFont() ;
}


CDcdAllOperationTable2::CDcdAllOperationTable2() 
	//: m_fontpropDiaJikokuFont( 9 , _T("ＭＳ ゴシック")  )
	: m_fontpropDiaJikokuFont(9, _T("Meiryo UI"))
	, m_iEkimeiLength( 6 )
	, m_bDisplayEkimeiJikoku(true)
	, m_bNoDisplayLeftSpace(false)
	, m_bNoDisplayAllOperationTableSpace(false)
	, m_bNoDisplayRightSpace(false)
{
	m_pCDcdAllOperationTable = new CDcdAllOperationTable() ;
}
CDcdAllOperationTable2::~CDcdAllOperationTable2() 
{
	if ( m_pCDcdAllOperationTable != NULL ){
		delete m_pCDcdAllOperationTable ;
		m_pCDcdAllOperationTable = NULL ;
	}
}
	
	// ********************************
	//@name IfDcDraw
	// ********************************

bool CDcdAllOperationTable2::DcDraw(IfDcdTarget* pIfDcdTarget)
{
	bool bRv = false;
	setCdDcdZone_X(pIfDcdTarget);



	// --------------------------------
	//	ダイヤグラムの各構成要素のサイズを計算
	// --------------------------------
	CdDcdFreeLineProp	linepropGridNormal(getCdLinePropGridNormal());
	CdDcdFreeLineProp	linepropGridBold(getCdLinePropGridBold());
	CdDcdFreeLineProp	linepropDiaJikuNormal(getCdLinePropDiaJikuNormal());
	CdDcdFreeLineProp	linepropDiaJikuBold(getCdLinePropDiaJikuBold());

	//DcdPerDgrYを設定します。Dgr座標では一行の高さがDEFAULT_YSIZE_PER_ONEOPERATION()になっていますが、
	//実表示するときの比率を求めておきます。
	{
		CDcdText dcdText(_T(""),
			CdDrawTextProp(getOperationTableFont(), 
				getStringColor()),
			_T("岡"));
		CdDcdSizeXy	sizeTemp;
		dcdText.getItemSize(pIfDcdTarget, &sizeTemp);

		//上下の文字スペース
		DcdSize Size_Y = sizeTemp.getY() * 2;

		//列車線の太さ
		Size_Y += linepropGridBold.getLogicalunitWidth() + 1;
		//下部罫線の太さ
		Size_Y += linepropGridNormal.getLogicalunitWidth();
		m_pCDcdAllOperationTable->setDcdPerDgrY(pIfDcdTarget, (double)Size_Y / (double)DEFAULT_YSIZE_PER_ONEOPERATION());
	}


	CdDcdZoneXy	zonexyDiagram = calcDiagramZoneDcd(pIfDcdTarget);

	//zonexyDiagram = ダイヤグラムの描画を行う領域（論理座標）
	// --------------------------------
	CaDcdTargetItemPosition	targetDiagram(pIfDcdTarget, zonexyDiagram);
	//targetDiagram = ダイヤグラムの描画を行う領域のDcDrawオブジェクト




// --------------------------------
//	描画を行う領域の計算	
// --------------------------------
	CdDcdZoneXy	zonexyAllOperationTable = *getCdDcdZone();

	//起点時刻から24時間を丸々表示するために必要な領域
	CdDcdZone zoneDcdAllOperationTable = XDgrToDcd(pIfDcdTarget, zonexyAllOperationTable.getX());
	//zoneDcdAllOperationTableの右端が、zonexyDiagramの右端よりも左側(内側)にある場合は、
	//ヘッダー・運用情報部(右側)の位置を調整して、空白スペースが無くなるようにします。
	//その際、DIAGRAM_SIZE_MARGIN_DCDを考慮します。
	DcdSize SizeShiftRightZone = 0;
	if (getNoDisplayAllOperationTableSpace())
	{
		CdDcdZoneXy	zonexyHeaderRightDcd = calcHeaderRightZoneDcd(pIfDcdTarget);
		SizeShiftRightZone = zonexyHeaderRightDcd.getX().getPos();
	}
	else if (zonexyDiagram.getX().getEndPos() > zoneDcdAllOperationTable.getEndPos() + 2)
	{
		SizeShiftRightZone = zonexyDiagram.getX().getEndPos() - zoneDcdAllOperationTable.getEndPos() - 2;
	}
	//まず、運用一覧図表示領域のトリミングを行います。
	CdDcdZone	zoneXDiagramDcd(
		zonexyDiagram.getX().getPos(),
		zonexyDiagram.getX().getSize() - SizeShiftRightZone);
	zonexyDiagram.setX(zoneXDiagramDcd);

	//zonexyAllOperationTable = 運用一覧図の範囲を、
	//	『ダイヤグラムエンティティ座標系』で保持します。
	//	X座標は24時間分、Y座標は全運用分の表示スペースを表します。

	// --------------------------------
	//	ヘッダー部(左側)の描画
	// --------------------------------
	if (!getNoDisplayLeftSpace())
	{
		CdDcdZoneXy	zonexyHeaderLeftDcd = calcHeaderLeftZoneDcd(pIfDcdTarget);
		//zonexyOperationLeftDcd = 時表示部分のDcDraw座標による範囲

		CaDcdTargetItemPosition	targetitemposHeaderLeft(pIfDcdTarget, zonexyHeaderLeftDcd);
		CaDcdTargetClip targetHeaderLeft(&targetitemposHeaderLeft, zonexyHeaderLeftDcd);

		// --------------------------------
		//	ヘッダー部の背景色設定
		// --------------------------------
		CConverter_WinGdi aCConverter_WinGdi;
		CdBrushProp	aCdBrushProp(
			aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENU));
		CDcdFillrect aCDcdFillrect(aCdBrushProp);
		aCDcdFillrect.DcDraw(&targetHeaderLeft);

		// --------------------------------
		//	ヘッダー上下の横線
		// --------------------------------
		CDcdFreeLine	aCDcdFreeLine;
		aCDcdFreeLine.setCdLineProp(linepropGridNormal);

		{
			aCDcdFreeLine.setOrg(CdDcdPosXy(
				zonexyHeaderLeftDcd.getX().getPos(),
				zonexyHeaderLeftDcd.getY().getPos()));
			aCDcdFreeLine.setDst(CdDcdPosXy(
				zonexyHeaderLeftDcd.getX().getEndPos() - linepropGridNormal.getLogicalunitWidth(),
				zonexyHeaderLeftDcd.getY().getPos()));
			aCDcdFreeLine.DcDraw(&targetHeaderLeft);
		}
		{
			aCDcdFreeLine.setOrg(CdDcdPosXy(
				zonexyHeaderLeftDcd.getX().getPos(),
				zonexyHeaderLeftDcd.getY().getEndPos() - linepropGridNormal.getLogicalunitWidth()));
			aCDcdFreeLine.setDst(CdDcdPosXy(
				zonexyHeaderLeftDcd.getX().getEndPos() - linepropGridNormal.getLogicalunitWidth(),
				zonexyHeaderLeftDcd.getY().getEndPos() - linepropGridNormal.getLogicalunitWidth()));
			aCDcdFreeLine.DcDraw(&targetHeaderLeft);
		}

		// --------------------------------
		//CDcdLine を使った縦罫線描画
		// --------------------------------
		{
			CDcdLine	aCDcdLine(
				CdPenProp(
					linepropGridBold.getLogicalunitWidth(),
					linepropGridBold.getColor()));
			{
				CaDcdTargetItemPosition	aTargetItemPosition(
					&targetHeaderLeft,
					CdDcdZoneXy(
						CdDcdZone(
							zonexyHeaderLeftDcd.getX().getEndPos() - linepropGridBold.getLogicalunitWidth(),
							linepropGridBold.getLogicalunitWidth()),
						zonexyHeaderLeftDcd.getY()
					));
				if (aTargetItemPosition.isDrawable())
				{
					aCDcdLine.DcDraw(&aTargetItemPosition);
					bRv = true;
				}
			}

			CDcdLine	aCDcdNormalLine(
				CdPenProp(
					linepropGridNormal.getLogicalunitWidth(),
					linepropGridNormal.getColor()));
			{
				CaDcdTargetItemPosition	aTargetItemPosition(
					&targetHeaderLeft,
					CdDcdZoneXy(
						CdDcdZone(
							zonexyHeaderLeftDcd.getX().getPos(),
							linepropGridNormal.getLogicalunitWidth()),
						zonexyHeaderLeftDcd.getY()
					));
				if (aTargetItemPosition.isDrawable())
				{
					aCDcdNormalLine.DcDraw(&aTargetItemPosition);
					bRv = true;
				}
			}
			{
				CaDcdTargetItemPosition	aTargetItemPosition(
					&targetHeaderLeft,
					CdDcdZoneXy(
						CdDcdZone(
							zonexyHeaderLeftDcd.getX().getPos() + m_CdDcdZone_X_Left[0].getEndPos(),
							linepropGridNormal.getLogicalunitWidth()),
						zonexyHeaderLeftDcd.getY()
					));
				if (aTargetItemPosition.isDrawable())
				{
					aCDcdNormalLine.DcDraw(&aTargetItemPosition);
					bRv = true;
				}
			}
			if (getDisplayEkimeiJikoku())
			{
				{
					CaDcdTargetItemPosition	aTargetItemPosition(
						&targetHeaderLeft,
						CdDcdZoneXy(
							CdDcdZone(
								zonexyHeaderLeftDcd.getX().getPos() + m_CdDcdZone_X_Left[1].getEndPos(),
								linepropGridNormal.getLogicalunitWidth()),
							zonexyHeaderLeftDcd.getY()
						));
					if (aTargetItemPosition.isDrawable())
					{
						aCDcdNormalLine.DcDraw(&aTargetItemPosition);
						bRv = true;
					}
				}

				CDcdLine	aCDcdDotLine(
					CdPenProp(
						linepropGridNormal.getLogicalunitWidth(),
						linepropGridNormal.getColor(),
						CdPenProp::DOT));
				{
					CaDcdTargetItemPosition	aTargetItemPosition(
						&targetHeaderLeft,
						CdDcdZoneXy(
							CdDcdZone(
								zonexyHeaderLeftDcd.getX().getPos() + m_CdDcdZone_X_Left[2].getEndPos(),
								linepropGridNormal.getLogicalunitWidth()),
							zonexyHeaderLeftDcd.getY()
						));
					if (aTargetItemPosition.isDrawable())
					{
						aCDcdDotLine.DcDraw(&aTargetItemPosition);
						bRv = true;
					}
				}
			}
		}


		// --------------------------------
		// ヘッダー(左)の項目名描写
		// --------------------------------
		CdDrawTextFormat aCdDrawTextFormat;
		aCdDrawTextFormat.setHorizontal(CdDrawTextFormat::H_CENTER);
		{
			//運用番号
			CDcdText dcdText(_T("運用番号"),
				CdDrawTextProp(getOperationTableFont(), getStringColor(), aCdDrawTextFormat),
				_T("運用番号"));

			CdDcdZoneXy	zonexyDcdZoneXy(
				CdDcdZone(zonexyHeaderLeftDcd.getX().getPos() + m_CdDcdZone_X_Left[1].getPos(),
					m_CdDcdZone_X_Left[1].getSize()),
				targetHeaderLeft.getZone().getY());
			CaDcdTargetItemPosition	aTarget(&targetHeaderLeft, zonexyDcdZoneXy);
			if (aTarget.isDrawable())
			{
				dcdText.DcDraw(&aTarget);
				bRv = true;
			}
		}

		if (m_bDisplayEkimeiJikoku)
		{
			{
				//出区駅名
				CDcdText dcdText(_T("出区駅名"),
					CdDrawTextProp(getOperationTableFont(), getStringColor(), aCdDrawTextFormat),
					_T("出区駅名"));

				CdDcdZoneXy	zonexyDcdZoneXy(
					CdDcdZone(zonexyHeaderLeftDcd.getX().getPos() + m_CdDcdZone_X_Left[2].getPos(),
						m_CdDcdZone_X_Left[2].getSize()),
					targetHeaderLeft.getZone().getY());
				CaDcdTargetItemPosition	aTarget(&targetHeaderLeft, zonexyDcdZoneXy);
				if (aTarget.isDrawable())
				{
					dcdText.DcDraw(&aTarget);
					bRv = true;
				}
			}

			{
				//発時刻
				CDcdText dcdText(_T("発時刻"),
					CdDrawTextProp(getOperationTableFont(), getStringColor(), aCdDrawTextFormat),
					_T("発時刻"));

				CdDcdZoneXy	zonexyDcdZoneXy(
					CdDcdZone(zonexyHeaderLeftDcd.getX().getPos() + m_CdDcdZone_X_Left[3].getPos(),
						m_CdDcdZone_X_Left[3].getSize()),
					targetHeaderLeft.getZone().getY());
				CaDcdTargetItemPosition	aTarget(&targetHeaderLeft, zonexyDcdZoneXy);
				if (aTarget.isDrawable())
				{
					dcdText.DcDraw(&aTarget);
					bRv = true;
				}
			}
		}
	}
	// --------------------------------
	//	ヘッダー部(右側)の描画
	// --------------------------------
	if (!getNoDisplayRightSpace())
	{
		CdDcdZoneXy	zonexyHeaderRightDcd = calcHeaderRightZoneDcd(pIfDcdTarget);
		CdDcdZone	zoneXHeaderRightDcd(
			zonexyHeaderRightDcd.getX().getPos() - SizeShiftRightZone, 
			zonexyHeaderRightDcd.getX().getSize());
		zonexyHeaderRightDcd.setX(zoneXHeaderRightDcd);
		//zonexyOperationLeftDcd = 時表示部分のDcDraw座標による範囲

		CaDcdTargetItemPosition	targetitemposHeaderRight(pIfDcdTarget, zonexyHeaderRightDcd);
		CaDcdTargetClip targetHeaderRight(&targetitemposHeaderRight, zonexyHeaderRightDcd);

		// --------------------------------
		//	ヘッダー部の背景色設定
		// --------------------------------
		CConverter_WinGdi aCConverter_WinGdi;
		CdBrushProp	aCdBrushProp(
			aCConverter_WinGdi.CdColorPropOfSysColor(COLOR_MENU));
		CDcdFillrect aCDcdFillrect(aCdBrushProp);
		aCDcdFillrect.DcDraw(&targetHeaderRight);

		// --------------------------------
		//	ヘッダー上下の横線
		// --------------------------------
		CDcdFreeLine	aCDcdFreeLine;
		aCDcdFreeLine.setCdLineProp(linepropGridNormal);

		if (getDisplayEkimeiJikoku())
		{
			aCDcdFreeLine.setOrg(CdDcdPosXy(
				zonexyHeaderRightDcd.getX().getPos(),
				zonexyHeaderRightDcd.getY().getPos()));
			aCDcdFreeLine.setDst(CdDcdPosXy(
				zonexyHeaderRightDcd.getX().getEndPos() - linepropGridNormal.getLogicalunitWidth(),
				zonexyHeaderRightDcd.getY().getPos()));
			aCDcdFreeLine.DcDraw(&targetHeaderRight);
		}
		if (getDisplayEkimeiJikoku())
		{
			aCDcdFreeLine.setOrg(CdDcdPosXy(
				zonexyHeaderRightDcd.getX().getPos(),
				zonexyHeaderRightDcd.getY().getEndPos() - linepropGridNormal.getLogicalunitWidth()));
			aCDcdFreeLine.setDst(CdDcdPosXy(
				zonexyHeaderRightDcd.getX().getEndPos() - linepropGridNormal.getLogicalunitWidth(),
				zonexyHeaderRightDcd.getY().getEndPos() - linepropGridNormal.getLogicalunitWidth()));
			aCDcdFreeLine.DcDraw(&targetHeaderRight);
		}

		// --------------------------------
		//CDcdLine を使った縦罫線描画
		// --------------------------------
		{
			CDcdLine	aCDcdLine(
			CdPenProp(
				linepropGridBold.getLogicalunitWidth(),
				linepropGridBold.getColor()));
			if (getDisplayEkimeiJikoku())
			{
				CaDcdTargetItemPosition	aTargetItemPosition(
					&targetHeaderRight,
					CdDcdZoneXy(
						CdDcdZone(
							zonexyHeaderRightDcd.getX().getPos(),
							linepropGridBold.getLogicalunitWidth()),
						zonexyHeaderRightDcd.getY()
					));
				if (aTargetItemPosition.isDrawable())
				{
					aCDcdLine.DcDraw(&aTargetItemPosition);
					bRv = true;
				}
			}

			CDcdLine	aCDcdDotLine(
				CdPenProp(
					linepropGridNormal.getLogicalunitWidth(),
					linepropGridNormal.getColor(),
					CdPenProp::DOT));
			if (getDisplayEkimeiJikoku())
			{
				CaDcdTargetItemPosition	aTargetItemPosition(
					&targetHeaderRight,
					CdDcdZoneXy(
						CdDcdZone(
							zonexyHeaderRightDcd.getX().getPos() + m_CdDcdZone_X_Right[0].getEndPos(),
							linepropGridNormal.getLogicalunitWidth()),
						zonexyHeaderRightDcd.getY()
					));
				if (aTargetItemPosition.isDrawable())
				{
					aCDcdDotLine.DcDraw(&aTargetItemPosition);
					bRv = true;
				}
			}

			CDcdLine	aCDcdNormalLine(
				CdPenProp(
					linepropGridNormal.getLogicalunitWidth(),
					linepropGridNormal.getColor()));
			{
				CaDcdTargetItemPosition	aTargetItemPosition(
					&targetHeaderRight,
					CdDcdZoneXy(
						CdDcdZone(
							zonexyHeaderRightDcd.getX().getEndPos() - linepropGridNormal.getLogicalunitWidth(),
							linepropGridNormal.getLogicalunitWidth()),
						zonexyHeaderRightDcd.getY()
					));
				if (aTargetItemPosition.isDrawable())
				{
					aCDcdNormalLine.DcDraw(&aTargetItemPosition);
					bRv = true;
				}
			}
		}


		// --------------------------------
		// ヘッダー(右)の項目名描写
		// --------------------------------
		CdDrawTextFormat aCdDrawTextFormat;
		aCdDrawTextFormat.setHorizontal(CdDrawTextFormat::H_CENTER);

		if (getDisplayEkimeiJikoku())
		{
			{
				//入区駅名
				CDcdText dcdText(_T("入区駅名"),
					CdDrawTextProp(getOperationTableFont(), getStringColor(), aCdDrawTextFormat),
					_T("入区駅名"));

				CdDcdZoneXy	zonexyDcdZoneXy(
					CdDcdZone(zonexyHeaderRightDcd.getX().getPos() + m_CdDcdZone_X_Right[0].getPos(),
						m_CdDcdZone_X_Right[0].getSize()),
					//m_CdDcdZone_X_Right[0],
					targetHeaderRight.getZone().getY());
				CaDcdTargetItemPosition	aTarget(&targetHeaderRight, zonexyDcdZoneXy);
				if (aTarget.isDrawable())
				{
					dcdText.DcDraw(&aTarget);
					bRv = true;
				}
			}

			{
				//着時刻
				CDcdText dcdText(_T("着時刻"),
					CdDrawTextProp(getOperationTableFont(), getStringColor(), aCdDrawTextFormat),
					_T("着時刻"));

				CdDcdZoneXy	zonexyDcdZoneXy(
					CdDcdZone(zonexyHeaderRightDcd.getX().getPos() + m_CdDcdZone_X_Right[1].getPos(),
						m_CdDcdZone_X_Right[1].getSize()),
					//m_CdDcdZone_X_Right[1],
					targetHeaderRight.getZone().getY());
				CaDcdTargetItemPosition	aTarget(&targetHeaderRight, zonexyDcdZoneXy);
				if (aTarget.isDrawable())
				{
					dcdText.DcDraw(&aTarget);
					bRv = true;
				}
			}
		}
	}
	// --------------------------------
	//	時の描画
	// --------------------------------
	if (!getNoDisplayAllOperationTableSpace())
	{
		CdDcdZoneXy	zonexyJikokuDcd = calcJikokuZoneDcd(pIfDcdTarget);
		CdDcdZone	zoneXJikokuDcd(
			zonexyJikokuDcd.getX().getPos(),
			zonexyJikokuDcd.getX().getSize() - SizeShiftRightZone);
		zonexyJikokuDcd.setX(zoneXJikokuDcd);
		//zonexyOperationLeftDcd = 時表示部分のDcDraw座標による範囲

		CaDcdTargetItemPosition	targetitemposJikoku(pIfDcdTarget, zonexyJikokuDcd);
		CaDcdTargetClip targetJikoku(&targetitemposJikoku, zonexyJikokuDcd);
		targetJikoku.validate();

		// --------------------------------
		//	時部上下の横線
		// --------------------------------
		CDcdFreeLine	aCDcdFreeLine;
		aCDcdFreeLine.setCdLineProp(linepropGridNormal);

		//DcdPos posDgrXRight = zonexyAllOperationTable.getX().getEndPos();
		//DcdPos posDcdXRight = XDgrToDcd(pIfDcdTarget, posDgrXRight);
		{
			aCDcdFreeLine.setOrg(CdDcdPosXy(
				zonexyJikokuDcd.getX().getPos(),
				zonexyJikokuDcd.getY().getPos()));
			aCDcdFreeLine.setDst(CdDcdPosXy(
				zonexyJikokuDcd.getX().getEndPos(),
				zonexyJikokuDcd.getY().getPos()));
			aCDcdFreeLine.DcDraw(&targetJikoku);
		}
		{
			aCDcdFreeLine.setOrg(CdDcdPosXy(
				zonexyJikokuDcd.getX().getPos(),
				zonexyJikokuDcd.getY().getEndPos() - linepropGridNormal.getLogicalunitWidth()));
			aCDcdFreeLine.setDst(CdDcdPosXy(
				zonexyJikokuDcd.getX().getEndPos(),
				zonexyJikokuDcd.getY().getEndPos() - linepropGridNormal.getLogicalunitWidth()));
			aCDcdFreeLine.DcDraw(&targetJikoku);
		}

		//	時刻表示は、ダイヤグラム起点時刻の次の正時から開始(4:59なら5:00、5:00なら5:00)
		DcdPos posDgrXJikokuhyoujiOrg = zonexyAllOperationTable.getX().getPos();
		{
			int iMod = zonexyAllOperationTable.getX().getPos() % (60 * 60);
			if (iMod > 0)
			{
				posDgrXJikokuhyoujiOrg += (60 * 60) - iMod;
			}
		}
		//posDgrXJikokuhyoujiOrg = 時刻表示の開始位置
		//	ダイヤグラム起点時刻の次の正時から開始(4:59なら5:00、5:00なら5:00)

		DcdPos posDcdX_Left = XDgrToDcd(pIfDcdTarget, zonexyAllOperationTable.getX().getPos());
		DcdPos posDcdX_Right = XDgrToDcd(pIfDcdTarget, zonexyAllOperationTable.getX().getEndPos());
		for (DcdPos posDgrX = posDgrXJikokuhyoujiOrg;
			posDgrX <= zonexyAllOperationTable.getX().getEndPos();
			posDgrX += 60 * 60)
		{
			//posDgrX = ダイヤグラムエンティティ座標での、
			//	時刻表示の位置

			//	時刻のテキストを設定
			CDcdText textJikoku(stringOf(CdDedJikoku(posDgrX).getHour()),
				CdDrawTextProp(m_fontpropDiaJikokuFont, getStringColor()),
				stringOf(CdDedJikoku(posDgrX).getHour()));
			CdDcdSizeXy	sizetextJikoku;
			textJikoku.getItemSize(pIfDcdTarget, &sizetextJikoku);


			//	座標を、Dgr→Dcdに変換
			DcdPos posDcdX = XDgrToDcd(pIfDcdTarget, posDgrX);
			{
				CdDcdZoneXy	zonexyDcdZoneXy(
					CdDcdZone(posDcdX - (sizetextJikoku.getX() / 2), sizetextJikoku.getX()),
					zonexyJikokuDcd.getY());
				if (zonexyDcdZoneXy.getX().getPos() < posDcdX_Left)
				{
					zonexyDcdZoneXy.setX(CdDcdZone(posDcdX_Left, sizetextJikoku.getX()));
				}
				if (zonexyDcdZoneXy.getX().getEndPos() > posDcdX_Right)
				{
					zonexyDcdZoneXy.setX(CdDcdZone(posDcdX_Right - sizetextJikoku.getX(), sizetextJikoku.getX()));
				}
				CaDcdTargetItemPosition	aTarget(&targetJikoku, zonexyDcdZoneXy);
				if (aTarget.isDrawable())
				{
					textJikoku.DcDraw(&aTarget);
					bRv = true;
				}
			}
		}
	}
	// --------------------------------
	//	運用情報部(左側)の罫線
	// --------------------------------
	if (!getNoDisplayLeftSpace())
	{

		CdDcdZoneXy	zonexyOperationLeftDcd = calcOperationLeftZoneDcd(pIfDcdTarget);
		//zonexyOperationLeftDcd = 駅名表示部分のDcDraw座標による範囲

		CaDcdTargetItemPosition	targetitemposOperationLeft(pIfDcdTarget, zonexyOperationLeftDcd);
		CaDcdTargetClip targetOperationLeft(&targetitemposOperationLeft, zonexyOperationLeftDcd);
		targetOperationLeft.validate();

		CdDcdZoneXy	zonexyZone_Dgr = getZone_Dgr(pIfDcdTarget);
		// --------------------------------
		//CDcdLine を使った罫線描画
		// --------------------------------
		{
			CdDcdZone	zoneDcdY;
			{
				DcdPos posDgrY = zonexyZone_Dgr.getY().getPos();
				CdDcdZone	zoneDgrY(posDgrY,getOperationNumber()->size() * m_pCDcdAllOperationTable->DEFAULT_YSIZE_PER_ONEOPERATION()- posDgrY);
				//zoneDgrY = 全運用分のダイヤグラム座標によるY座標範囲
				if (getClippingCount()>0)
				{ 
					DcdSize YSize = getClippingCount() * m_pCDcdAllOperationTable->DEFAULT_YSIZE_PER_ONEOPERATION();
					zoneDgrY.setEndPos(min(zoneDgrY.getPos() + YSize, zonexyAllOperationTable.getY().getEndPos()));
				}
				else if(zoneDgrY.getEndPos() > zonexyAllOperationTable.getY().getEndPos())
				{
					zoneDgrY.setEndPos(zonexyAllOperationTable.getY().getEndPos());
				}
				zoneDcdY = YDgrToDcd(pIfDcdTarget, zoneDgrY);

				//zoneDcdY = 全運用分のDcDrawe座標によるY座標範囲
				zoneDcdY = zonexyOperationLeftDcd.getY().CrossZone(zoneDcdY);
				//zoneDcdY =	縦線を描画する範囲の DcDraw座標
			}
			//zoneDcdY =	縦線を描画する範囲の DcDraw座標

			CDcdLine	aCDcdLine(
				CdPenProp(
					linepropGridBold.getLogicalunitWidth(),
					linepropGridBold.getColor()));
			{
				CaDcdTargetItemPosition	aTargetItemPosition(
					&targetOperationLeft,
					CdDcdZoneXy(
						CdDcdZone(
							zonexyOperationLeftDcd.getX().getEndPos() - linepropGridBold.getLogicalunitWidth(),
							linepropGridBold.getLogicalunitWidth()),
						CdDcdZone(zoneDcdY.getPos(),
							zoneDcdY.getSize() - (linepropGridBold.getLogicalunitWidth() - 1))
					));
				if (aTargetItemPosition.isDrawable())
				{
					aCDcdLine.DcDraw(&aTargetItemPosition);
					bRv = true;
				}
			}

			CDcdLine	aCDcdNormalLine(
				CdPenProp(
					linepropGridNormal.getLogicalunitWidth(),
					linepropGridNormal.getColor()));
			{
				CaDcdTargetItemPosition	aTargetItemPosition(
					&targetOperationLeft,
					CdDcdZoneXy(
						CdDcdZone(
							zonexyOperationLeftDcd.getX().getPos(),
							linepropGridNormal.getLogicalunitWidth()),
						zoneDcdY
					));
				if (aTargetItemPosition.isDrawable())
				{
					aCDcdNormalLine.DcDraw(&aTargetItemPosition);
					bRv = true;
				}
			}
			{
				CaDcdTargetItemPosition	aTargetItemPosition(
					&targetOperationLeft,
					CdDcdZoneXy(
						CdDcdZone(
							zonexyOperationLeftDcd.getX().getPos() + m_CdDcdZone_X_Left[0].getEndPos(),
							linepropGridNormal.getLogicalunitWidth()),
						zoneDcdY
					));
				if (aTargetItemPosition.isDrawable())
				{
					aCDcdNormalLine.DcDraw(&aTargetItemPosition);
					bRv = true;
				}
			}
			if (getDisplayEkimeiJikoku())
			{
				{
					CaDcdTargetItemPosition	aTargetItemPosition(
						&targetOperationLeft,
						CdDcdZoneXy(
							CdDcdZone(
								zonexyOperationLeftDcd.getX().getPos() + m_CdDcdZone_X_Left[1].getEndPos(),
								linepropGridNormal.getLogicalunitWidth()),
							zoneDcdY
						));
					if (aTargetItemPosition.isDrawable())
					{
						aCDcdNormalLine.DcDraw(&aTargetItemPosition);
						bRv = true;
					}
				}

				CDcdLine	aCDcdDotLine(
					CdPenProp(
						linepropGridNormal.getLogicalunitWidth(),
						linepropGridNormal.getColor(),
						CdPenProp::DOT));
				{
					CaDcdTargetItemPosition	aTargetItemPosition(
						&targetOperationLeft,
						CdDcdZoneXy(
							CdDcdZone(
								zonexyOperationLeftDcd.getX().getPos() + m_CdDcdZone_X_Left[2].getEndPos(),
								linepropGridNormal.getLogicalunitWidth()),
							zoneDcdY
						));
					if (aTargetItemPosition.isDrawable())
					{
						aCDcdDotLine.DcDraw(&aTargetItemPosition);
						bRv = true;
					}
				}
			}
		}

		// --------------------------------
		//	運用情報下の罫線
		// --------------------------------
		int iOperationCount = m_pCDcdAllOperationTable->getOperationNumber()->size();
		DcdSize iOneOperationSize = DEFAULT_YSIZE_PER_ONEOPERATION();

		for (int iOperationIndex = 1;
			iOperationIndex <= iOperationCount;
			iOperationIndex++)
		{
			DcdPos posDgrY = iOneOperationSize * iOperationIndex;

			if (getClippingCount() <= 0 || (posDgrY >= zonexyZone_Dgr.getY().getPos() && posDgrY <= zonexyZone_Dgr.getY().getEndPos()))
			{
				CDcdFreeLine	aCDcdFreeLine;
				aCDcdFreeLine.setCdLineProp(linepropGridNormal);

				//	座標を、Dgr→Dcdに変換
				DcdPos	posDcdY = YDgrToDcd(pIfDcdTarget, posDgrY);
				posDcdY -= linepropGridNormal.getLogicalunitWidth();
				CdDcdZone	zoneDcdX = zonexyOperationLeftDcd.getX();

				//	下罫線描画
				if (targetOperationLeft.getZone().getY().getPos() - 1 <= posDcdY &&
					posDcdY < targetOperationLeft.getZone().getY().getEndPos() + 1)
				{
					aCDcdFreeLine.setOrg(CdDcdPosXy(
						zoneDcdX.getPos(),
						posDcdY));
					aCDcdFreeLine.setDst(CdDcdPosXy(
						zoneDcdX.getEndPos(),
						posDcdY));
					aCDcdFreeLine.DcDraw(&targetOperationLeft);
				}
			}
		}
		// --------------------------------
		//	運用番号
		// --------------------------------


		const Mu<const CentDedRessya*>* pCentDedRessyaConts[2];
		int iDiaIndex = getCDiagramEditDoc()->
			getCDedRosenFileData()->getCentDedRosen()->getCentDedDiaCont()
			->findCentDedDiaByName(getName());
		const CentDedDia* pCentDedDia =
			getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
			->getCentDedDiaCont()->getMuPtr()->get(iDiaIndex);
		for (int iRessyahoukou = Ressyahoukou_Kudari;
			iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
		{
			pCentDedRessyaConts[iRessyahoukou] =
				pCentDedDia->getCentDedRessyaCont((ERessyahoukou)iRessyahoukou)->getMuPtr();
		}
		unordered_map<tstring, list<OperationTableContent>> contOperationTableContent =
			pCentDedDia->getcontOperationTableContent();
		const Mu<CentDedEkiCont::CdDedEki>* pCdDedEkiConts[2];
		for (int iRessyahoukou = Ressyahoukou_Kudari;
			iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
		{
			pCdDedEkiConts[iRessyahoukou] =
				getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont()->getMuPtr((ERessyahoukou)iRessyahoukou);
		}

		DcdPos posDgrY = 0;
		DcdPos posClipping = zonexyZone_Dgr.getY().getEndPos() - zonexyZone_Dgr.getY().getEndPos() % m_pCDcdAllOperationTable->DEFAULT_YSIZE_PER_ONEOPERATION();
		for (int iOperationIndex = 0;
			iOperationIndex < iOperationCount;
			iOperationIndex++, posDgrY += iOneOperationSize)
		{
			if (getClippingCount() > 0 && posDgrY >= posClipping)
			{
				break;
			}
			CdDrawTextFormat aCdDrawTextFormat;
			aCdDrawTextFormat.setHorizontal(CdDrawTextFormat::H_CENTER);
			aCdDrawTextFormat.setVertical(CdDrawTextFormat::V_SINGLELINT_CENTER);

			CdDcdZone aCdDcdZone_Dgr(posDgrY, iOneOperationSize);

			//	座標を、Dgr→Dcdに変換
			CdDcdZone aCdDcdZone_Dcd = YDgrToDcd(pIfDcdTarget, aCdDcdZone_Dgr);
			{
				//通し番号
				CDcdText dcdText(to_tstring(iOperationIndex + 1),
					CdDrawTextProp(getOperationTableFont(), getStringColor(), aCdDrawTextFormat),
					to_tstring(iOperationIndex + 1));

				CdDcdZoneXy	zonexyDcdZoneXy(
					CdDcdZone(zonexyOperationLeftDcd.getX().getPos() + m_CdDcdZone_X_Left[0].getPos(),
						m_CdDcdZone_X_Left[0].getSize()),
					aCdDcdZone_Dcd);
				CaDcdTargetItemPosition	aTarget(&targetOperationLeft, zonexyDcdZoneXy);
				if (aTarget.isDrawable())
				{
					dcdText.DcDraw(&aTarget);
					bRv = true;
				}
			}
			tstring strOperationNumber = getOperationNumber()->at(iOperationIndex);
			if (contOperationTableContent[strOperationNumber].empty())
			{
				continue;
			}
			{
				//運用番号
				CDcdText dcdText(strOperationNumber,
					CdDrawTextProp(getOperationTableFont(), getStringColor(), aCdDrawTextFormat),
					strOperationNumber);

				CdDcdZoneXy	zonexyDcdZoneXy(
					CdDcdZone(zonexyOperationLeftDcd.getX().getPos() + m_CdDcdZone_X_Left[1].getPos(),
						m_CdDcdZone_X_Left[1].getSize()),
					aCdDcdZone_Dcd);
				CaDcdTargetItemPosition	aTarget(&targetOperationLeft, zonexyDcdZoneXy);
				if (aTarget.isDrawable())
				{
					dcdText.DcDraw(&aTarget);
					bRv = true;
				}
			}
			if (getDisplayEkimeiJikoku())
			{
				const list<OperationTableContent>& ListOperationTableContent = contOperationTableContent[strOperationNumber];
				const OperationTableContent aOperationTableContentOut = ListOperationTableContent.front();
				const OperationTableContent aOperationTableContentIn = ListOperationTableContent.back();

				const CentDedRessya* pCentDedRessyaOut =
					pCentDedRessyaConts[aOperationTableContentOut.aRessyaProperty.getRessyahoukou()]
					->get(aOperationTableContentOut.aRessyaProperty.getRessyaIndex());
				const CentDedRessya* pCentDedRessyaIn =
					pCentDedRessyaConts[aOperationTableContentIn.aRessyaProperty.getRessyahoukou()]
					->get(aOperationTableContentIn.aRessyaProperty.getRessyaIndex());

				CdDedJikoku::CConv aConv(
					false,
					CdDedJikoku::CConv::EHour_ZeroToSpace,
					CdDedJikoku::CConv::ESecond_NoSecond,
					CdDedJikoku::CConv::ESecondRound_RoundDown,
					CdDedJikoku::CConv::ESecondRound_RoundDown,
					false);

				//	出区駅名&出区駅時刻
				tstring strOutEkimei;
				CdDedJikoku aOutJikoku;
				if (ListOperationTableContent.front().iOuterShihatsuekiIndex != INT_MIN)
				{
					int iOuterTerminalIndex = aOperationTableContentOut.iOuterShihatsuekiIndex;
					strOutEkimei = pCdDedEkiConts[aOperationTableContentOut.aRessyaProperty.getRessyahoukou()]
						->get(aOperationTableContentOut.iSihatsuEkiOrder).getOuterTerminalEkimei(iOuterTerminalIndex);
					aOutJikoku = aOperationTableContentOut.OuterShihatsuJikoku;
				}
				else
				{
					int iSihatsuEkiOrder = aOperationTableContentOut.iSihatsuEkiOrder;
					if (!pCentDedRessyaOut->isRunBetweenNextEki(iSihatsuEkiOrder))
					{
						iSihatsuEkiOrder = pCentDedRessyaOut->getRunBetweenEkiForward(iSihatsuEkiOrder);
					}

					strOutEkimei = pCdDedEkiConts[aOperationTableContentOut.aRessyaProperty.getRessyahoukou()]
						->get(iSihatsuEkiOrder).getEkimei();
					aOutJikoku = pCentDedRessyaOut->getCentDedEkiJikoku(iSihatsuEkiOrder).getHatsujikoku();
				}

				CDcdText dcdText_OutEkimei(strOutEkimei,
					CdDrawTextProp(getOperationTableFont(), getStringColor(), aCdDrawTextFormat),
					strOutEkimei);

				CdDcdZoneXy	zonexyDcdZoneXy(
					CdDcdZone(zonexyOperationLeftDcd.getX().getPos() + m_CdDcdZone_X_Left[2].getPos(),
						m_CdDcdZone_X_Left[2].getSize()),
					aCdDcdZone_Dcd);
				CaDcdTargetItemPosition	aTarget(&targetOperationLeft, zonexyDcdZoneXy);
				if (aTarget.isDrawable())
				{
					dcdText_OutEkimei.DcDraw(&aTarget);
					bRv = true;
				}

				CDcdText dcdText_OutEkiJikoku(aConv.encode(aOutJikoku, false),
					CdDrawTextProp(getOperationTableFont(), getStringColor(), aCdDrawTextFormat),
					aConv.encode(aOutJikoku, false));

				zonexyDcdZoneXy.setX(CdDcdZone(zonexyOperationLeftDcd.getX().getPos() + m_CdDcdZone_X_Left[3].getPos(),
					m_CdDcdZone_X_Left[3].getSize()));
				aTarget = CaDcdTargetItemPosition(&targetOperationLeft, zonexyDcdZoneXy);
				if (aTarget.isDrawable())
				{
					dcdText_OutEkiJikoku.DcDraw(&aTarget);
					bRv = true;
				}


				//CDcdText dcdText_Arrow(_T("→"),
				//	CdDrawTextProp(getOperationTableFont(), getStringColor(), aCdDrawTextFormat),
				//	_T("→"));

				//zonexyDcdZoneXy.setX(m_CdDcdZone_X[4]);
				//aTarget = CaDcdTargetItemPosition(&targetOperationLeft, zonexyDcdZoneXy);
				//if (aTarget.isDrawable())
				//{
				//	dcdText_Arrow.DcDraw(&aTarget);
				//	bRv = true;
				//}
			}
		}
	}
	// --------------------------------
	//	運用情報部(右側)の罫線
	// --------------------------------
	if (!getNoDisplayRightSpace())
	{
		CdDcdZoneXy	zonexyOperationRightDcd = calcOperationRightZoneDcd(pIfDcdTarget);
		CdDcdZone	zoneXOperationRightDcd(
			zonexyOperationRightDcd.getX().getPos() - SizeShiftRightZone,
			zonexyOperationRightDcd.getX().getSize());
		zonexyOperationRightDcd.setX(zoneXOperationRightDcd);
		//zonexyOperationLeftDcd = 駅名表示部分のDcDraw座標による範囲

		CaDcdTargetItemPosition	targetitemposOperationRight(pIfDcdTarget, zonexyOperationRightDcd);
		CaDcdTargetClip targetOperationRight(&targetitemposOperationRight, zonexyOperationRightDcd);
		targetOperationRight.validate();

		CdDcdZoneXy	zonexyZone_Dgr = getZone_Dgr(pIfDcdTarget);
		// --------------------------------
		//CDcdLine を使った罫線描画
		// --------------------------------
		{
			CdDcdZone	zoneDcdY;
			{
				DcdPos posDgrY = zonexyZone_Dgr.getY().getPos();
				CdDcdZone	zoneDgrY(posDgrY, getOperationNumber()->size()* m_pCDcdAllOperationTable->DEFAULT_YSIZE_PER_ONEOPERATION() - posDgrY);
				//zoneDgrY = 全運用分のダイヤグラム座標によるY座標範囲
				if (getClippingCount() > 0)
				{
					DcdSize YSize = getClippingCount() * m_pCDcdAllOperationTable->DEFAULT_YSIZE_PER_ONEOPERATION();
					zoneDgrY.setEndPos(min(zoneDgrY.getPos() + YSize, zonexyAllOperationTable.getY().getEndPos()));
				}
				else if (zoneDgrY.getEndPos() > zonexyAllOperationTable.getY().getEndPos())
				{
					zoneDgrY.setEndPos(zonexyAllOperationTable.getY().getEndPos());
				}
				zoneDcdY = YDgrToDcd(pIfDcdTarget, zoneDgrY);

				//zoneDcdY = 全運用分のDcDrawe座標によるY座標範囲
				zoneDcdY = zonexyOperationRightDcd.getY().CrossZone(zoneDcdY);
				//zoneDcdY =	縦線を描画する範囲の DcDraw座標
			}
			//zoneDcdY =	縦線を描画する範囲の DcDraw座標

			CDcdLine	aCDcdLine(
				CdPenProp(
					linepropGridBold.getLogicalunitWidth(),
					linepropGridBold.getColor()));
			if(getDisplayEkimeiJikoku())
			{
				CaDcdTargetItemPosition	aTargetItemPosition(
					&targetOperationRight,
					CdDcdZoneXy(
						CdDcdZone(
							zonexyOperationRightDcd.getX().getPos(),
							linepropGridBold.getLogicalunitWidth()),
						CdDcdZone(zoneDcdY.getPos(),
							zoneDcdY.getSize() - (linepropGridBold.getLogicalunitWidth() - 1))
					));
				if (aTargetItemPosition.isDrawable())
				{
					aCDcdLine.DcDraw(&aTargetItemPosition);
					bRv = true;
				}
			}

			CDcdLine	aCDcdDotLine(
				CdPenProp(
					linepropGridNormal.getLogicalunitWidth(),
					linepropGridNormal.getColor(),
					CdPenProp::DOT));
			if (getDisplayEkimeiJikoku())
			{
				CaDcdTargetItemPosition	aTargetItemPosition(
					&targetOperationRight,
					CdDcdZoneXy(
						CdDcdZone(
							zonexyOperationRightDcd.getX().getPos() + m_CdDcdZone_X_Right[0].getEndPos(),
							linepropGridNormal.getLogicalunitWidth()),
						zoneDcdY
					));
				if (aTargetItemPosition.isDrawable())
				{
					aCDcdDotLine.DcDraw(&aTargetItemPosition);
					bRv = true;
				}
			}

			CDcdLine	aCDcdNormalLine(
				CdPenProp(
					linepropGridNormal.getLogicalunitWidth(),
					linepropGridNormal.getColor()));
			{
				CaDcdTargetItemPosition	aTargetItemPosition(
					&targetOperationRight,
					CdDcdZoneXy(
						CdDcdZone(
							zonexyOperationRightDcd.getX().getEndPos() - linepropGridNormal.getLogicalunitWidth(),
							linepropGridNormal.getLogicalunitWidth()),
						zoneDcdY
					));
				if (aTargetItemPosition.isDrawable())
				{
					aCDcdNormalLine.DcDraw(&aTargetItemPosition);
					bRv = true;
				}
			}
		}

		// --------------------------------
		//	運用情報下の罫線
		// --------------------------------
		int iOperationCount = m_pCDcdAllOperationTable->getOperationNumber()->size();
		DcdSize iOneOperationSize = DEFAULT_YSIZE_PER_ONEOPERATION();

		for (int iOperationIndex = 1;
			iOperationIndex <= iOperationCount;
			iOperationIndex++)
		{
			DcdPos posDgrY = iOneOperationSize * iOperationIndex;

			if (getClippingCount() <= 0 || posDgrY >= zonexyZone_Dgr.getY().getPos() && posDgrY <= zonexyZone_Dgr.getY().getEndPos())
			{
				CDcdFreeLine	aCDcdFreeLine;
				aCDcdFreeLine.setCdLineProp(linepropGridNormal);

				//	座標を、Dgr→Dcdに変換
				DcdPos	posDcdY = YDgrToDcd(pIfDcdTarget, posDgrY);
				posDcdY -= linepropGridNormal.getLogicalunitWidth();
				CdDcdZone	zoneDcdX = zonexyOperationRightDcd.getX();

				//	下罫線描画
				if (targetOperationRight.getZone().getY().getPos() - 1 <= posDcdY &&
					posDcdY < targetOperationRight.getZone().getY().getEndPos() + 1)
				{
					aCDcdFreeLine.setOrg(CdDcdPosXy(
						zoneDcdX.getPos(),
						posDcdY));
					aCDcdFreeLine.setDst(CdDcdPosXy(
						zoneDcdX.getEndPos(),
						posDcdY));
					aCDcdFreeLine.DcDraw(&targetOperationRight);
				}
			}
		}
		// --------------------------------
		//	駅名
		// --------------------------------


		const Mu<const CentDedRessya*>* pCentDedRessyaConts[2];
		int iDiaIndex = getCDiagramEditDoc()->
			getCDedRosenFileData()->getCentDedRosen()->getCentDedDiaCont()
			->findCentDedDiaByName(getName());
		const CentDedDia* pCentDedDia =
			getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()
			->getCentDedDiaCont()->getMuPtr()->get(iDiaIndex);
		for (int iRessyahoukou = Ressyahoukou_Kudari;
			iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
		{
			pCentDedRessyaConts[iRessyahoukou] =
				pCentDedDia->getCentDedRessyaCont((ERessyahoukou)iRessyahoukou)->getMuPtr();
		}
		unordered_map<tstring, list<OperationTableContent>> contOperationTableContent =
			pCentDedDia->getcontOperationTableContent();
		const Mu<CentDedEkiCont::CdDedEki>* pCdDedEkiConts[2];
		for (int iRessyahoukou = Ressyahoukou_Kudari;
			iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
		{
			pCdDedEkiConts[iRessyahoukou] =
				getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont()->getMuPtr((ERessyahoukou)iRessyahoukou);
		}

		DcdPos posDgrY = 0;
		DcdPos posClipping = zonexyZone_Dgr.getY().getEndPos() - zonexyZone_Dgr.getY().getEndPos() % m_pCDcdAllOperationTable->DEFAULT_YSIZE_PER_ONEOPERATION();
		for (int iOperationIndex = 0;
			iOperationIndex < iOperationCount;
			iOperationIndex++, posDgrY += iOneOperationSize)
		{
			if (getClippingCount() > 0 && posDgrY >= posClipping)
			{
				break;
			}
			CdDrawTextFormat aCdDrawTextFormat;
			aCdDrawTextFormat.setHorizontal(CdDrawTextFormat::H_CENTER);
			aCdDrawTextFormat.setVertical(CdDrawTextFormat::V_SINGLELINT_CENTER);

			CdDcdZone aCdDcdZone_Dgr(posDgrY, iOneOperationSize);

			//	座標を、Dgr→Dcdに変換
			CdDcdZone aCdDcdZone_Dcd = YDgrToDcd(pIfDcdTarget, aCdDcdZone_Dgr);
			tstring strOperationNumber = getOperationNumber()->at(iOperationIndex);
			if (contOperationTableContent[strOperationNumber].empty())
			{
				continue;
			}
			if (getDisplayEkimeiJikoku())
			{
				const list<OperationTableContent>& ListOperationTableContent = contOperationTableContent[strOperationNumber];
				const OperationTableContent aOperationTableContentOut = ListOperationTableContent.front();
				const OperationTableContent aOperationTableContentIn = ListOperationTableContent.back();

				const CentDedRessya* pCentDedRessyaOut =
					pCentDedRessyaConts[aOperationTableContentOut.aRessyaProperty.getRessyahoukou()]
					->get(aOperationTableContentOut.aRessyaProperty.getRessyaIndex());
				const CentDedRessya* pCentDedRessyaIn =
					pCentDedRessyaConts[aOperationTableContentIn.aRessyaProperty.getRessyahoukou()]
					->get(aOperationTableContentIn.aRessyaProperty.getRessyaIndex());

				CdDedJikoku::CConv aConv(
					false,
					CdDedJikoku::CConv::EHour_ZeroToSpace,
					CdDedJikoku::CConv::ESecond_NoSecond,
					CdDedJikoku::CConv::ESecondRound_RoundDown,
					CdDedJikoku::CConv::ESecondRound_RoundDown,
					false);

				//	入区列車始終着駅名&入区列車駅時刻

				tstring strInEkimei;
				CdDedJikoku aInJikoku;
				if (aOperationTableContentIn.iOuterShuchakuekiIndex != INT_MIN)
				{
					int iOuterTerminalIndex = aOperationTableContentIn.iOuterShuchakuekiIndex;
					strInEkimei = pCdDedEkiConts[aOperationTableContentIn.aRessyaProperty.getRessyahoukou()]
						->get(aOperationTableContentIn.iSyuuchakuEkiOrder).getOuterTerminalEkimei(iOuterTerminalIndex);
					aInJikoku = aOperationTableContentIn.OuterShuchakuJikoku;
				}
				else
				{
					int iSyuuchakuEkiOrder = aOperationTableContentIn.iSyuuchakuEkiOrder;
					if (!pCentDedRessyaIn->isRunBetweenNextEki(iSyuuchakuEkiOrder - 1))
					{
						iSyuuchakuEkiOrder = pCentDedRessyaIn->getRunBetweenEkiBackward(iSyuuchakuEkiOrder);
					}

					strInEkimei = pCdDedEkiConts[aOperationTableContentIn.aRessyaProperty.getRessyahoukou()]
						->get(iSyuuchakuEkiOrder).getEkimei();
					aInJikoku = pCentDedRessyaIn->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getChakujikoku();
				}

				CDcdText dcdText_InEkimei(strInEkimei,
					CdDrawTextProp(getOperationTableFont(), getStringColor(), aCdDrawTextFormat),
					strInEkimei);

				CdDcdZoneXy	zonexyDcdZoneXy(
					CdDcdZone(zonexyOperationRightDcd.getX().getPos() + m_CdDcdZone_X_Right[0].getPos(),
						m_CdDcdZone_X_Right[0].getSize()),
					//m_CdDcdZone_X_Right[0],
					aCdDcdZone_Dcd);
				CaDcdTargetItemPosition	aTarget(&targetOperationRight, zonexyDcdZoneXy);
				if (aTarget.isDrawable())
				{
					dcdText_InEkimei.DcDraw(&aTarget);
					bRv = true;
				}

				CDcdText dcdText_InEkiJikoku(aConv.encode(aInJikoku, true),
					CdDrawTextProp(getOperationTableFont(), getStringColor(), aCdDrawTextFormat),
					aConv.encode(aInJikoku, true));

				zonexyDcdZoneXy.setX(CdDcdZone(zonexyOperationRightDcd.getX().getPos() + m_CdDcdZone_X_Right[1].getPos(),
					m_CdDcdZone_X_Right[1].getSize()));
				//zonexyDcdZoneXy.setX(m_CdDcdZone_X_Right[1]);
				aTarget = CaDcdTargetItemPosition(&targetOperationRight, zonexyDcdZoneXy);
				if (aTarget.isDrawable())
				{
					dcdText_InEkiJikoku.DcDraw(&aTarget);
					bRv = true;
				}
			}
		}
	}

	// --------------------------------
	//	ダイヤの描画
	// --------------------------------
	if (!getNoDisplayAllOperationTableSpace())
	{
		bRv |= m_pCDcdAllOperationTable->DcDraw(&targetDiagram);
	}
	return (bRv);
}
	
bool CDcdAllOperationTable2::getItemSize( IfDcdTarget* pIfDcdTarget , 
							CdDcdSizeXy* pCdDcdSizeXy ) 
{
	return ( false ) ;
}
	
// ********************************
//	CDcdAllOperationTable
// ********************************
	// ********************************
	//@name CDcdAllOperationTable-関連
	// ********************************
CdDcdZoneXy* CDcdAllOperationTable2::getCdDcdZone()const
{
	return m_pCDcdAllOperationTable->getCdDcdZone();
}
CDcdAllOperationTable2& CDcdAllOperationTable2::setCdDcdZone(CdDcdZoneXy* value )
{
	m_pCDcdAllOperationTable->setCdDcdZone( value ) ; 
	return *this ;
}
vector<tstring>* CDcdAllOperationTable2::getOperationNumber()const
{
	return m_pCDcdAllOperationTable->getOperationNumber();
}
CDcdAllOperationTable2& CDcdAllOperationTable2::setOperationNumber(vector<tstring>* value)
{
	m_pCDcdAllOperationTable->setOperationNumber(value);
	return *this;
}
tstring CDcdAllOperationTable2::getName()const
{
	return m_pCDcdAllOperationTable->getName();
}
CDcdAllOperationTable2& CDcdAllOperationTable2::setName(tstring value)
{
	m_pCDcdAllOperationTable->setName(value);
	return *this;
}

int CDcdAllOperationTable2::getClippingCount()const
{
	return m_pCDcdAllOperationTable->getClippingCount();
}
CDcdAllOperationTable2& CDcdAllOperationTable2::setClippingCount(int value)
{
	m_pCDcdAllOperationTable->setClippingCount(value);
	return *this;
}
	// ********************************
	//@name CDcdAllOperationTable-属性-CdDedDispProp から読み込み可能
	// ********************************
//CdFontProp	CDcdAllOperationTable2::getDiaRessyaFont()const 
//{
//	return m_pCDcdAllOperationTable->getDiaRessyaFont() ;
//}
//CDcdAllOperationTable2& CDcdAllOperationTable2::setDiaRessyaFont( const CdFontProp& value ) 
//{
//	m_pCDcdAllOperationTable->setDiaRessyaFont( value ) ;
//	return *this ;
//}

CdFontProp	CDcdAllOperationTable2::getOperationTableFont()const
{
	return m_pCDcdAllOperationTable->getOperationTableFont();
}
CDcdAllOperationTable2& CDcdAllOperationTable2::setOperationTableFont(const CdFontProp& value)
{
	m_pCDcdAllOperationTable->setOperationTableFont(value);
	return *this;
}

CdFontProp	CDcdAllOperationTable2::getAllOperationTableJikokuFont()const
{
	return m_pCDcdAllOperationTable->getAllOperationTableJikokuFont();
}
CDcdAllOperationTable2& CDcdAllOperationTable2::setAllOperationTableJikokuFont(const CdFontProp& value)
{
	m_pCDcdAllOperationTable->setAllOperationTableJikokuFont(value);
	return *this;
}

CdColorProp	CDcdAllOperationTable2::getDiaJikuColor()const 
{
	return m_pCDcdAllOperationTable->getDiaJikuColor() ;
}
CDcdAllOperationTable2& CDcdAllOperationTable2::setDiaJikuColor( CdColorProp value ) 
{
	m_pCDcdAllOperationTable->setDiaJikuColor( value ) ;
	return *this ;
}

CdColorProp	CDcdAllOperationTable2::getGridColor()const
{
	return m_pCDcdAllOperationTable->getGridColor();
}
CDcdAllOperationTable2& CDcdAllOperationTable2::setGridColor(CdColorProp value)
{
	m_pCDcdAllOperationTable->setGridColor(value);
	return *this;
}

CdColorProp	CDcdAllOperationTable2::getStringColor()const
{
	return m_pCDcdAllOperationTable->getStringColor();
}
CDcdAllOperationTable2& CDcdAllOperationTable2::setStringColor(CdColorProp value)
{
	m_pCDcdAllOperationTable->setStringColor(value);
	return *this;
}
	// ********************************
	//@name CDcdAllOperationTable-属性-CdDedDispProp にはないもの
	// ********************************
bool	CDcdAllOperationTable2::getDisplayRessyabangou()const 
{
	return m_pCDcdAllOperationTable->getDisplayRessyabangou() ;
}
CDcdAllOperationTable2& CDcdAllOperationTable2::setDisplayRessyabangou( bool value ) 
{
	m_pCDcdAllOperationTable->setDisplayRessyabangou( value ) ;
	return *this ;
}
bool	CDcdAllOperationTable2::getDisplaySyubetsuRyakusyou()const
{
	return m_pCDcdAllOperationTable->getDisplaySyubetsuRyakusyou();
}
CDcdAllOperationTable2& CDcdAllOperationTable2::setDisplaySyubetsuRyakusyou(bool value)
{
	m_pCDcdAllOperationTable->setDisplaySyubetsuRyakusyou(value);
	return *this;
}
bool	CDcdAllOperationTable2::getDisplayRessyamei()const 
{
	return m_pCDcdAllOperationTable->getDisplayRessyamei() ;
}
CDcdAllOperationTable2& CDcdAllOperationTable2::setDisplayRessyamei( bool value ) 
{
	m_pCDcdAllOperationTable->setDisplayRessyamei( value ) ;
	return *this ;
}
bool	CDcdAllOperationTable2::getDisplayJikokuMinute()const
{
	return m_pCDcdAllOperationTable->getDisplayJikokuMinute();
}
CDcdAllOperationTable2& CDcdAllOperationTable2::setDisplayJikokuMinute(bool value)
{
	m_pCDcdAllOperationTable->setDisplayJikokuMinute(value);
	return *this;
}

double CDcdAllOperationTable2::getDcdPerDgrX( IfDcdTarget* pIfDcdTarget ) 
{
	return m_pCDcdAllOperationTable->getDcdPerDgrX( pIfDcdTarget ) ;
}

void CDcdAllOperationTable2::setDcdPerDgrX(  IfDcdTarget* pIfDcdTarget , double dDcdPerDgr ) 
{
	m_pCDcdAllOperationTable->setDcdPerDgrX( pIfDcdTarget , dDcdPerDgr ) ;
}

//double CDcdAllOperationTable2::getDcdPerDgrY() 
//{
//	return m_pCDcdAllOperationTable->getDcdPerDgrY() ;
//}

double CDcdAllOperationTable2::getDcdPerDgrY( IfDcdTarget* pIfDcdTarget ) 
{
	return m_pCDcdAllOperationTable->getDcdPerDgrY( pIfDcdTarget ) ;
}

void CDcdAllOperationTable2::setDcdPerDgrY( IfDcdTarget* pIfDcdTarget , double dDcdPerDgr ) 
{
	m_pCDcdAllOperationTable->setDcdPerDgrY( pIfDcdTarget , dDcdPerDgr ) ;
}

int	CDcdAllOperationTable2::getVlineMode()const 
{
	return m_pCDcdAllOperationTable->getVlineMode() ;
}

CDcdAllOperationTable2& CDcdAllOperationTable2::setVlineMode( int value ) 
{
	m_pCDcdAllOperationTable->setVlineMode( value ) ;
	return *this ;
}

int CDcdAllOperationTable2::getVlinePitch()const 
{
	return m_pCDcdAllOperationTable->getVlinePitch() ;
}

int CDcdAllOperationTable2::getVlineMiddlePitch()const 
{
	return m_pCDcdAllOperationTable->getVlineMiddlePitch() ;
}

int CDcdAllOperationTable2::getVlineBoldPitch()const 
{
	return m_pCDcdAllOperationTable->getVlineBoldPitch() ;
}

int CDcdAllOperationTable2::getVlineChoices( 
		Mui<CDcdAllOperationTable::VLINE>* pContVLINE )const 
{
	return m_pCDcdAllOperationTable->getVlineChoices( pContVLINE ) ;
}

bool CDcdAllOperationTable2::getDisplayParentSyubetsu() const
{
	return m_pCDcdAllOperationTable->getDisplayParentSyubetsu();
}
CDcdAllOperationTable2 & CDcdAllOperationTable2::setDisplayParentSyubetsu(bool value)
{
	m_pCDcdAllOperationTable->setDisplayParentSyubetsu(value);
	return *this;
}
	// ********************************
	//@name CDcdAllOperationTable-操作
	// ********************************

CDcdAllOperationTable2& CDcdAllOperationTable2::readCdDedDispProp( const CdDedDispProp& value ) 
{
	m_pCDcdAllOperationTable->readCdDedDispProp( value ) ;
	//m_fontpropDiaEkimeiFont = value.getDiaEkimeiFont() ;
	m_fontpropDiaJikokuFont = value.getDiaJikokuFont() ;
	//m_colorDiaMojiColor = value.getDiaMojiColor() ;
	m_iEkimeiLength = value.getEkimeiLength() ;
	//m_bDisplayEkimeiJikoku = value.getDisplayEkimeiJikoku();
	return *this ;
}


CdDcdZoneXy	CDcdAllOperationTable2::getZone_Dgr( IfDcdTarget* pIfDcdTarget )const 
{
	CaDcdTargetItemPosition	aTarget( 
		pIfDcdTarget , 
		calcDiagramZoneDcd( pIfDcdTarget ) ) ;

	return m_pCDcdAllOperationTable->getZone_Dgr( &aTarget ) ;
}
CdDcdZoneXy	CDcdAllOperationTable2::getZone_Dgr(
	IfDcdTarget* pIfDcdTarget,
	const int iType)const
{
	CaDcdTargetItemPosition	aTarget(
		pIfDcdTarget,
		calcDiagramZoneDcd(pIfDcdTarget, iType));

	return m_pCDcdAllOperationTable->getZone_Dgr(&aTarget);
}
CDcdAllOperationTable2& CDcdAllOperationTable2::setZone_Dgr( 
	IfDcdTarget* pIfDcdTarget , const CdDcdZoneXy& value ) 
{
	CaDcdTargetItemPosition	aTarget( 
		pIfDcdTarget , 
		calcDiagramZoneDcd( pIfDcdTarget ) ) ;

	m_pCDcdAllOperationTable->setZone_Dgr( &aTarget , value ) ;

	return *this ;
}


int CDcdAllOperationTable2::calcCentDedRessyaOfPoint(
		IfDcdTarget* pIfDcdTarget ,
		const CdDcdPosXy& aCdDcdPosXy ,  
		//int iMerginPixels ,
		ERessyahoukou *pERessyahoukou , 
		int *piRessyaIdx /*, 
		int *piRessyasenIdx */) 
{
	LogMsg(_T("CDcdAllOperationTable2::calcCentDedDgrRessyasenOfPoint(,(%d,%d)) ") ,
		aCdDcdPosXy.getX() , aCdDcdPosXy.getY() ) ;
 
	CdDcdZoneXy	zonexyDiagram = calcDiagramZoneDcd( pIfDcdTarget ) ;
	if ( zonexyDiagram.getX().getSize() <= 0 || zonexyDiagram.getY().getSize() <= 0 ){
		return 0 ;
	}

	CaDcdTargetItemPosition	targetDiagram( pIfDcdTarget , zonexyDiagram ) ;
	//targetDiagram = ダイヤグラムの描画を行う領域
	//zonexyDiagram = ダイヤグラムの描画を行う領域

	return m_pCDcdAllOperationTable->calcCentDedRessyaOfPoint(
		&targetDiagram ,
		aCdDcdPosXy ,  
		//iMerginPixels , 
		pERessyahoukou , 
		piRessyaIdx/* , 
		piRessyasenIdx*/ ) ;
}

int CDcdAllOperationTable2::calcOperationIndexOfPoint(
		IfDcdTarget* pIfDcdTarget ,
		DcdPos posY_Dcd ) 
{
	int iRv = -1 ;

	CdDcdZoneXy	zonexyDiagram = calcDiagramZoneDcd(pIfDcdTarget);
	if (zonexyDiagram.getX().getSize() <= 0 || zonexyDiagram.getY().getSize() <= 0) {
		return -1;
	}

	CaDcdTargetItemPosition	targetDiagram(pIfDcdTarget, zonexyDiagram);
	//targetDiagram = ダイヤグラムの描画を行う領域
	//zonexyDiagram = ダイヤグラムの描画を行う領域

	return m_pCDcdAllOperationTable->calcOperationIndexOfPoint(
		&targetDiagram,
		posY_Dcd);

	return iRv ;
}

	// ********************************
	//@name CDcdAllOperationTable-ダイヤグラム座標と、IfDcdTarget 上の座標を変換
	// ********************************
DcdPos CDcdAllOperationTable2::XDgrToDcd( IfDcdTarget* pIfDcdTarget , DcdPos posSrc ) 
{
	CdDcdZoneXy	zonexyDiagramZoneDcd = calcDiagramZoneDcd( pIfDcdTarget ) ;
	CaDcdTargetItemPosition	aTarget( 
		pIfDcdTarget , 
		zonexyDiagramZoneDcd ) ;
	return m_pCDcdAllOperationTable->XDgrToDcd( &aTarget , posSrc ) ;
}

DcdPos CDcdAllOperationTable2::YDgrToDcd( IfDcdTarget* pIfDcdTarget , DcdPos posSrc ) 
{
	CdDcdZoneXy	zonexyDiagramZoneDcd = calcDiagramZoneDcd( pIfDcdTarget ) ;
	CaDcdTargetItemPosition	aTarget( 
		pIfDcdTarget , 
		zonexyDiagramZoneDcd ) ;
	return m_pCDcdAllOperationTable->YDgrToDcd( &aTarget , posSrc ) ;
}

DcdPos CDcdAllOperationTable2::XDgrFromDcd( IfDcdTarget* pIfDcdTarget , DcdPos posSrc ) 
{
	CdDcdZoneXy	zonexyDiagramZoneDcd = calcDiagramZoneDcd( pIfDcdTarget ) ;
	CaDcdTargetItemPosition	aTarget( 
		pIfDcdTarget , 
		zonexyDiagramZoneDcd ) ;
	return m_pCDcdAllOperationTable->XDgrFromDcd( &aTarget , posSrc ) ;
}

DcdPos CDcdAllOperationTable2::YDgrFromDcd( IfDcdTarget* pIfDcdTarget , DcdPos posSrc ) 
{
	CdDcdZoneXy	zonexyDiagramZoneDcd = calcDiagramZoneDcd( pIfDcdTarget ) ;
	CaDcdTargetItemPosition	aTarget( 
		pIfDcdTarget , 
		zonexyDiagramZoneDcd ) ;
	return m_pCDcdAllOperationTable->YDgrFromDcd( &aTarget , posSrc ) ;
}

CdDcdZone CDcdAllOperationTable2::XDgrToDcd( IfDcdTarget* pIfDcdTarget ,
		const CdDcdZone& zoneSrc ) 
{
	CdDcdZoneXy	zonexyDiagramZoneDcd = calcDiagramZoneDcd( pIfDcdTarget ) ;
	CaDcdTargetItemPosition	aTarget( 
		pIfDcdTarget , 
		zonexyDiagramZoneDcd ) ;
	return m_pCDcdAllOperationTable->XDgrToDcd( &aTarget , zoneSrc ) ;
}

CdDcdZone CDcdAllOperationTable2::YDgrToDcd( IfDcdTarget* pIfDcdTarget , 
		const CdDcdZone& zoneSrc ) 
{
	CdDcdZoneXy	zonexyDiagramZoneDcd = calcDiagramZoneDcd( pIfDcdTarget ) ;
	CaDcdTargetItemPosition	aTarget( 
		pIfDcdTarget , 
		zonexyDiagramZoneDcd ) ;
	return m_pCDcdAllOperationTable->YDgrToDcd( &aTarget , zoneSrc ) ;
}

CdDcdZone CDcdAllOperationTable2::XDgrFromDcd( IfDcdTarget* pIfDcdTarget , 
		const CdDcdZone& zoneSrc ) 
{
	CdDcdZoneXy	zonexyDiagramZoneDcd = calcDiagramZoneDcd( pIfDcdTarget ) ;
	CaDcdTargetItemPosition	aTarget( 
		pIfDcdTarget , 
		zonexyDiagramZoneDcd ) ;
	return m_pCDcdAllOperationTable->XDgrFromDcd( &aTarget , zoneSrc ) ;
}

CdDcdZone CDcdAllOperationTable2::YDgrFromDcd( IfDcdTarget* pIfDcdTarget , 
		const CdDcdZone& zoneSrc ) 
{
	CdDcdZoneXy	zonexyDiagramZoneDcd = calcDiagramZoneDcd( pIfDcdTarget ) ;
	CaDcdTargetItemPosition	aTarget( 
		pIfDcdTarget , 
		zonexyDiagramZoneDcd ) ;
	return m_pCDcdAllOperationTable->XDgrFromDcd( &aTarget , zoneSrc ) ;
}

CdDcdPosXy CDcdAllOperationTable2::DgrToDcd( IfDcdTarget* pIfDcdTarget , 
		const CdDcdPosXy& posSrc ) 
{
	CdDcdZoneXy	zonexyDiagramZoneDcd = calcDiagramZoneDcd( pIfDcdTarget ) ;
	CaDcdTargetItemPosition	aTarget( 
		pIfDcdTarget , 
		zonexyDiagramZoneDcd ) ;
	return m_pCDcdAllOperationTable->DgrToDcd( &aTarget , posSrc ) ;
}

CdDcdPosXy CDcdAllOperationTable2::DgrFromDcd( IfDcdTarget* pIfDcdTarget , 
		const CdDcdPosXy& posSrc ) 
{
	CdDcdZoneXy	zonexyDiagramZoneDcd = calcDiagramZoneDcd( pIfDcdTarget ) ;
	CaDcdTargetItemPosition	aTarget( 
		pIfDcdTarget , 
		zonexyDiagramZoneDcd ) ;
	return m_pCDcdAllOperationTable->DgrFromDcd( &aTarget , posSrc ) ;
}


CdDcdZoneXy CDcdAllOperationTable2::DgrToDcd( IfDcdTarget* pIfDcdTarget , 
		const CdDcdZoneXy& zoneSrc ) 
{
	CdDcdZoneXy	zonexyDiagramZoneDcd = calcDiagramZoneDcd( pIfDcdTarget ) ;
	CaDcdTargetItemPosition	aTarget( 
		pIfDcdTarget , 
		zonexyDiagramZoneDcd ) ;
	return m_pCDcdAllOperationTable->DgrToDcd( &aTarget , zoneSrc ) ;
}

CdDcdZoneXy CDcdAllOperationTable2::DgrFromDcd( IfDcdTarget* pIfDcdTarget , 
		const CdDcdZoneXy& zoneSrc ) 
{
	CdDcdZoneXy	zonexyDiagramZoneDcd = calcDiagramZoneDcd( pIfDcdTarget ) ;
	CaDcdTargetItemPosition	aTarget( 
		pIfDcdTarget , 
		zonexyDiagramZoneDcd ) ;
	return m_pCDcdAllOperationTable->DgrFromDcd( &aTarget , zoneSrc ) ;
};



	// ********************************
	//@name CDcdAllOperationTable2-属性
	// ********************************
//CdFontProp	CDcdAllOperationTable2::getDiaEkimeiFont()const 
//{
//	return m_fontpropDiaEkimeiFont ;
//}
//CDcdAllOperationTable2& CDcdAllOperationTable2::setDiaEkimeiFont( const CdFontProp& value ) 
//{
//	m_fontpropDiaEkimeiFont = value ;
//	return *this ;
//}
CdFontProp	CDcdAllOperationTable2::getDiaJikokuFont()const 
{
	return m_fontpropDiaJikokuFont ;
}
CDcdAllOperationTable2& CDcdAllOperationTable2::setDiaJikokuFont( const CdFontProp& value ) 
{
	m_fontpropDiaJikokuFont = value ;
	return *this ;
}
//CdColorProp	CDcdAllOperationTable2::getDiaMojiColor()const 
//{
//	return m_colorDiaMojiColor ;
//}
//CDcdAllOperationTable2& CDcdAllOperationTable2::setDiaMojiColor( CdColorProp value ) 
//{
//	m_colorDiaMojiColor = value ;
//	return *this ;
//}
CDcdAllOperationTable2& CDcdAllOperationTable2::setEkimeiLength( int value ) 
{
	m_iEkimeiLength = value ;
	return *this ;
}
CDcdAllOperationTable2& CDcdAllOperationTable2::setDisplayEkimeiJikoku(bool value)
{
	m_bDisplayEkimeiJikoku = value;
	return *this;
}
CDcdAllOperationTable2& CDcdAllOperationTable2::setNoDisplayLeftSpace(bool value)
{
	m_bNoDisplayLeftSpace = value;
	return *this;
}
CDcdAllOperationTable2& CDcdAllOperationTable2::setNoDisplayAllOperationTableSpace(bool value)
{
	m_bNoDisplayAllOperationTableSpace = value;
	return *this;
}
CDcdAllOperationTable2& CDcdAllOperationTable2::setNoDisplayRightSpace(bool value)
{
	m_bNoDisplayRightSpace = value;
	return *this;
}


	
	// ********************************
	//@name CDcdAllOperationTable2-操作
	// ********************************


CdDcdZoneXy CDcdAllOperationTable2::calcHeaderLeftZoneDcd(
	IfDcdTarget* pIfDcdTarget)const
{
	// --------------------------------
	//	ヘッダー表示の幅
	// --------------------------------
	DcdSize	sizeHeaderX = 0;
	DcdSize	sizeHeaderY = 0;
	{
		CdDcdFreeLineProp	linepropBold(getCdLinePropGridBold());
		CdDcdFreeLineProp	linepropNormal(getCdLinePropGridNormal());


		// --------------------------------
		//	テキストの幅
		CdDcdSizeXy	sizeTextHeader;
		vector<CDcdText>	dcdtextHeader(getCDcdTextHeader());
		dcdtextHeader[0].getItemSize(pIfDcdTarget, &sizeTextHeader);
		//dcdtextEkimei = ヘッダーの描画を行う DcDraw オブジェクト
		//sizeTextHeaderRight = ヘッダーの描画を行う DcDraw オブジェクトの大きさ

		if (!getNoDisplayLeftSpace())
		{
			if (getDisplayEkimeiJikoku())
			{
				sizeHeaderX = m_CdDcdZone_X_Left[3].getEndPos();
			}
			else
			{
				sizeHeaderX = m_CdDcdZone_X_Left[1].getEndPos();
			}
			// --------------------------------
			//	テキストの右の太線
			sizeHeaderX += linepropBold.getLogicalunitWidth();
		}

		CdDcdSizeXy	sizeTextJikoku;
		CDcdText	dcdtextJikoku(getCDcdTextJikoku());
		dcdtextJikoku.getItemSize(pIfDcdTarget, &sizeTextJikoku);

		//上側罫線
		sizeHeaderY += linepropNormal.getLogicalunitWidth();
		//ヘッダー部と時部でフォントが異なるため、大きい方に高さを合わせます。
		sizeHeaderY += max(sizeTextHeader.getY(), sizeTextJikoku.getY());
		//下側罫線
		sizeHeaderY += linepropNormal.getLogicalunitWidth();
	}
	//sizeHeaderRightX = 駅名欄の幅

	// --------------------------------
	CdDcdZoneXy	zonexyHeader;
	zonexyHeader.setX(CdDcdZone(
		pIfDcdTarget->getZone().getX().getPos(),
		sizeHeaderX));
	zonexyHeader.setY(CdDcdZone(
		pIfDcdTarget->getZone().getY().getPos(),
		sizeHeaderY));

	if (zonexyHeader.getX().getSize() < 0)
	{
		zonexyHeader.setX(CdDcdZone(zonexyHeader.getX().getPos(), 0));
	}
	if (zonexyHeader.getY().getSize() < 0)
	{
		zonexyHeader.setY(CdDcdZone(zonexyHeader.getY().getPos(), 0));
	}


	return zonexyHeader;
}

CdDcdZoneXy CDcdAllOperationTable2::calcHeaderRightZoneDcd(
	IfDcdTarget* pIfDcdTarget)const
{
	CdDcdZoneXy	zonexyHeaderLeft = calcHeaderLeftZoneDcd(pIfDcdTarget);
	// --------------------------------
	//	ヘッダー表示の幅
	// --------------------------------
	DcdSize	sizeHeaderRightX = 0;
	if (!getNoDisplayRightSpace())
	{
		CdDcdFreeLineProp	linepropBold(getCdLinePropGridBold());
		CdDcdFreeLineProp	linepropNormal(getCdLinePropGridNormal());

		// --------------------------------
		//	テキストの幅
		CdDcdSizeXy	sizeTextHeaderRight;
		vector<CDcdText>	dcdtextHeader(getCDcdTextHeader());
		dcdtextHeader[0].getItemSize(pIfDcdTarget, &sizeTextHeaderRight);
		//dcdtextEkimei = ヘッダーの描画を行う DcDraw オブジェクト
		//sizeTextHeaderRight = ヘッダーの描画を行う DcDraw オブジェクトの大きさ

		if (getDisplayEkimeiJikoku())
		{
			sizeHeaderRightX = linepropBold.getLogicalunitWidth();
			sizeHeaderRightX += m_CdDcdZone_X_Right[0].getSize();
			sizeHeaderRightX += linepropNormal.getLogicalunitWidth();
			sizeHeaderRightX += m_CdDcdZone_X_Right[1].getSize();
			sizeHeaderRightX += linepropNormal.getLogicalunitWidth();
		}
		else
		{
			sizeHeaderRightX = linepropNormal.getLogicalunitWidth();
		}
	}
	//sizeHeaderRightX = 駅名欄の幅

	// --------------------------------
	CdDcdZoneXy	zonexyHeaderRight;
	zonexyHeaderRight.setX(CdDcdZone(
		pIfDcdTarget->getZone().getX().getEndPos() - sizeHeaderRightX,
		sizeHeaderRightX));
	zonexyHeaderRight.setY(zonexyHeaderLeft.getY());

	if (zonexyHeaderRight.getX().getSize() < 0)
	{
		zonexyHeaderRight.setX(CdDcdZone(zonexyHeaderRight.getX().getPos(), 0));
	}
	if (zonexyHeaderRight.getY().getSize() < 0)
	{
		zonexyHeaderRight.setY(CdDcdZone(zonexyHeaderRight.getY().getPos(), 0));
	}


	return zonexyHeaderRight;
}

CdDcdZoneXy CDcdAllOperationTable2::calcJikokuZoneDcd(
	IfDcdTarget* pIfDcdTarget)const
{
	//
	CdDcdZoneXy	zonexyHeader = calcHeaderLeftZoneDcd(pIfDcdTarget);
	CdDcdZoneXy	zonexyHeaderRight = calcHeaderRightZoneDcd(pIfDcdTarget);

	// --------------------------------
	//X軸は、全体からヘッダー部の横幅を抜いたもの
	//Y軸は、ヘッダー部と同じ縦幅
	CdDcdZoneXy	zonexyJikoku;
	if (!getNoDisplayAllOperationTableSpace())
	{
		zonexyJikoku.setX(CdDcdZone(
			pIfDcdTarget->getZone().getX().getPos() + zonexyHeader.getX().getSize(),
			pIfDcdTarget->getZone().getX().getSize() - zonexyHeader.getX().getSize() - zonexyHeaderRight.getX().getSize()));
	}
	zonexyJikoku.setY(zonexyHeader.getY());

	if (zonexyJikoku.getX().getSize() < 0)
	{
		zonexyJikoku.setX(CdDcdZone(zonexyJikoku.getX().getPos(), 0));
	}
	if (zonexyJikoku.getY().getSize() < 0)
	{
		zonexyJikoku.setY(CdDcdZone(zonexyJikoku.getY().getPos(), 0));
	}


	return zonexyJikoku;
}

CdDcdZoneXy CDcdAllOperationTable2::calcOperationLeftZoneDcd( 
			IfDcdTarget* pIfDcdTarget )const 
{
	// --------------------------------
	//	ヘッダーの高さ
	// --------------------------------
	CdDcdZoneXy	zonexyHeader = calcHeaderLeftZoneDcd(pIfDcdTarget);

	// --------------------------------
	CdDcdZoneXy	zonexyOperationLeft ;
	zonexyOperationLeft.setX(zonexyHeader.getX());
	//ヘッダー部分を独立させるために、ヘッダーの高さ分だけ上をトリミングする
	zonexyOperationLeft.setY(CdDcdZone(
		pIfDcdTarget->getZone().getY().getPos() + zonexyHeader.getY().getSize(),
		pIfDcdTarget->getZone().getY().getSize() - zonexyHeader.getY().getSize()));

	if ( zonexyOperationLeft.getX().getSize() < 0 )
	{
		zonexyOperationLeft.setX( CdDcdZone( zonexyOperationLeft.getX().getPos() , 0 ) ) ;
	}
	if ( zonexyOperationLeft.getY().getSize() < 0 )
	{
		zonexyOperationLeft.setY( CdDcdZone( zonexyOperationLeft.getY().getPos() , 0 ) ) ;
	}


	return zonexyOperationLeft ;
}

CdDcdZoneXy CDcdAllOperationTable2::calcOperationRightZoneDcd(
	IfDcdTarget* pIfDcdTarget)const
{
	// --------------------------------
	//	ヘッダーの高さ
	// --------------------------------
	CdDcdZoneXy	zonexyHeaderRight = calcHeaderRightZoneDcd(pIfDcdTarget);

	// --------------------------------
	CdDcdZoneXy	zonexyOperationRight;
	zonexyOperationRight.setX(zonexyHeaderRight.getX());
	//ヘッダー部分を独立させるために、ヘッダーの高さ分だけ上をトリミングする
	zonexyOperationRight.setY(CdDcdZone(
		pIfDcdTarget->getZone().getY().getPos() + zonexyHeaderRight.getY().getSize(),
		pIfDcdTarget->getZone().getY().getSize() - zonexyHeaderRight.getY().getSize()));

	if (zonexyOperationRight.getX().getSize() < 0)
	{
		zonexyOperationRight.setX(CdDcdZone(zonexyOperationRight.getX().getPos(), 0));
	}
	if (zonexyOperationRight.getY().getSize() < 0)
	{
		zonexyOperationRight.setY(CdDcdZone(zonexyOperationRight.getY().getPos(), 0));
	}


	return zonexyOperationRight;
}

CdDcdZoneXy CDcdAllOperationTable2::calcDiagramZoneDcd(
	IfDcdTarget* pIfDcdTarget)const
{
	// --------------------------------
	//	駅名表示・時刻の領域
	// --------------------------------
	CdDcdZoneXy	zonexyJikoku = calcJikokuZoneDcd(pIfDcdTarget);

	// --------------------------------
	CdDcdZoneXy	zonexyDiagram;
	zonexyDiagram.setX(zonexyJikoku.getX());
	zonexyDiagram.setY(CdDcdZone(
		pIfDcdTarget->getZone().getY().getPos() + zonexyJikoku.getY().getSize(),
		pIfDcdTarget->getZone().getY().getSize() - zonexyJikoku.getY().getSize()));
	if (zonexyDiagram.getX().getSize() < 0)
	{
		zonexyDiagram.setX(CdDcdZone(zonexyDiagram.getX().getPos(), 0));
	}
	if (zonexyDiagram.getY().getSize() < 0)
	{
		zonexyDiagram.setY(CdDcdZone(zonexyDiagram.getY().getPos(), 0));
	}

	return zonexyDiagram;
}

CdDcdZoneXy CDcdAllOperationTable2::calcDiagramZoneDcd(
	IfDcdTarget* pIfDcdTarget,
	const int iType)const
{
	// --------------------------------
	//	駅名表示・時刻の領域
	// --------------------------------
	CdDcdZoneXy	zonexyJikoku = calcJikokuZoneDcd(pIfDcdTarget);

	// --------------------------------
	CdDcdZoneXy	zonexyDiagram;
	if (iType < 0)
	{
		CdDcdZoneXy	zonexyHeaderLeft = calcHeaderLeftZoneDcd(pIfDcdTarget);
		zonexyDiagram.setX(CdDcdZone(
			pIfDcdTarget->getZone().getX().getPos() + zonexyHeaderLeft.getX().getSize(),
			pIfDcdTarget->getZone().getX().getSize() - zonexyHeaderLeft.getX().getSize()));

	}
	else if (iType == 0)
	{
		zonexyDiagram.setX(pIfDcdTarget->getZone().getX());
	}
	else if (iType > 0)
	{
		CdDcdZoneXy	zonexyHeaderRight = calcHeaderRightZoneDcd(pIfDcdTarget);
		zonexyDiagram.setX(CdDcdZone(
			pIfDcdTarget->getZone().getX().getPos(),
			pIfDcdTarget->getZone().getX().getSize() - zonexyHeaderRight.getX().getSize()));
	}

	zonexyDiagram.setY(CdDcdZone(
		pIfDcdTarget->getZone().getY().getPos() + zonexyJikoku.getY().getSize(),
		pIfDcdTarget->getZone().getY().getSize() - zonexyJikoku.getY().getSize()));
	if (zonexyDiagram.getX().getSize() < 0)
	{
		zonexyDiagram.setX(CdDcdZone(zonexyDiagram.getX().getPos(), 0));
	}
	if (zonexyDiagram.getY().getSize() < 0)
	{
		zonexyDiagram.setY(CdDcdZone(zonexyDiagram.getY().getPos(), 0));
	}

	return zonexyDiagram;
}

} //namespace ViewAllOperationTable2



