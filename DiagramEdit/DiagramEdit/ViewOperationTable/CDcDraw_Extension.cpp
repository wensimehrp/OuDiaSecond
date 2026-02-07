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
//	CDcDraw_Extension.cpp
// ****************************************************************
*/
#include "stdafx.h"
#include "CDcDraw_Extension.h"
#include "DcDraw\CDcdFillrect.h"
#include "DcDraw\CConverter_WinGdi.h"
#include "DcDraw\CaDcdTargetItemPosition.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace ViewOperationTable {

// ****************************************************************
//	CDcDraw_Extension
// ****************************************************************
// ********************************
//	コンストラクタ
// ********************************
//CDcDraw_Extension::
//	CDcDraw_Extension( 
//		const CdDcdFreeLineProp& aCdLineProp ,
//		const int iLineType)
//	: m_CdLineProp( aCdLineProp ) 
//	, m_iLineType(iLineType)
//{
//}
CDcDraw_Extension::CDcDraw_Extension(
	const EDrawType eDrawType,
	const CdColorProp aCdColorProp)
	:m_eDrawType(eDrawType)
	,m_CdColorProp(aCdColorProp)
{
}
CDcDraw_Extension::CDcDraw_Extension() 
{
}

// ********************************
//@name	IfDcDraw
// ********************************
bool CDcDraw_Extension::DcDraw( IfDcdTarget* pIfDcdTarget ) 
{
	CdDcdZoneXy	zoneTarget = pIfDcdTarget->getZone() ;
	
	// --------------------------------
	//	背景の描画
	// --------------------------------
	CDcdFillrect aCDcdFillrect( CConverter_WinGdi().CdBrushPropOf( WHITE_BRUSH ) ) ;
	aCDcdFillrect.DcDraw( pIfDcdTarget ) ;

	// --------------------------------
	//	線の描画
	// --------------------------------
	bool bRv = false;
	if (m_eDrawType == EDrawType::DrawType_HorizontalLine)
	{

		//zoneTarget.setY(CdDcdZone(zoneTarget.getY().getPos() + zoneTarget.getY().getSize() / 2 - 1, 3));

		CaDcdTargetItemPosition	targetitempos(pIfDcdTarget, zoneTarget);

		CdBrushProp	aCdBrushProp(m_CdColorProp);
		CDcdFillrect aCDcdFillrectLine(aCdBrushProp);

		bRv = aCDcdFillrectLine.DcDraw(&targetitempos);
	}
	else if (m_eDrawType == EDrawType::DrawType_HorizontalRightLine)
	{
		zoneTarget.setX(CdDcdZone(zoneTarget.getX().getPos() + zoneTarget.getX().getSize() / 2 - 1, 
			zoneTarget.getX().getSize() / 2 + 1));
		//zoneTarget.setY(CdDcdZone(zoneTarget.getY().getPos() + zoneTarget.getY().getSize() / 2 - 1, 3));

		CaDcdTargetItemPosition	targetitempos(pIfDcdTarget, zoneTarget);

		CdBrushProp	aCdBrushProp(m_CdColorProp);
		CDcdFillrect aCDcdFillrectLine(aCdBrushProp);

		bRv = aCDcdFillrectLine.DcDraw(&targetitempos);
	}
	else if (m_eDrawType == EDrawType::DrawType_HorizontalLeftLine)
	{
		zoneTarget.setX(CdDcdZone(zoneTarget.getX().getPos(),
			zoneTarget.getX().getSize() / 2 + 2));
		//zoneTarget.setY(CdDcdZone(zoneTarget.getY().getPos() + zoneTarget.getY().getSize() / 2 - 1, 3));

		CaDcdTargetItemPosition	targetitempos(pIfDcdTarget, zoneTarget);

		CdBrushProp	aCdBrushProp(m_CdColorProp);
		CDcdFillrect aCDcdFillrectLine(aCdBrushProp);

		bRv = aCDcdFillrectLine.DcDraw(&targetitempos);
	}
	else if (m_eDrawType == EDrawType::DrawType_VerticalLine)
	{
		zoneTarget.setX(CdDcdZone(zoneTarget.getX().getPos() + zoneTarget.getX().getSize() / 2 - 1, 3));

		CaDcdTargetItemPosition	targetitempos(pIfDcdTarget, zoneTarget);

		CdBrushProp	aCdBrushProp(m_CdColorProp);
		CDcdFillrect aCDcdFillrectLine(aCdBrushProp);

		bRv = aCDcdFillrectLine.DcDraw(&targetitempos);
	}
	else if (m_eDrawType == EDrawType::DrawType_HorizontalDotLine)
	{
		CdDcdZoneXy	zoneTarget1(CdDcdZone(zoneTarget.getX().getPos(), zoneTarget.getX().getSize() / 16), zoneTarget.getY());
		CdDcdZoneXy	zoneTarget2(CdDcdZone(zoneTarget.getX().getPos()+ zoneTarget.getX().getSize()*(3/16.0) , zoneTarget.getX().getSize() / 8), zoneTarget.getY());
		CdDcdZoneXy	zoneTarget3(CdDcdZone(zoneTarget.getX().getPos() + zoneTarget.getX().getSize() * (7 / 16.0), zoneTarget.getX().getSize() / 8), zoneTarget.getY());
		CdDcdZoneXy	zoneTarget4(CdDcdZone(zoneTarget.getX().getPos() + zoneTarget.getX().getSize() * (11 / 16.0), zoneTarget.getX().getSize() / 8), zoneTarget.getY());
		CdDcdZone zoneTarget5X(zoneTarget.getX().getPos() + zoneTarget.getX().getSize() * (15 / 16.0));
		zoneTarget5X.setEndPos(zoneTarget.getX().getEndPos());
		CdDcdZoneXy	zoneTarget5(zoneTarget5X, zoneTarget.getY());


		CdBrushProp	aCdBrushProp(m_CdColorProp);

		CDcdFillrect aCDcdFillrectLine1(aCdBrushProp);
		CaDcdTargetItemPosition	targetitempos1(pIfDcdTarget, zoneTarget1);
		bRv = aCDcdFillrectLine1.DcDraw(&targetitempos1);

		CDcdFillrect aCDcdFillrectLine2(aCdBrushProp);
		CaDcdTargetItemPosition	targetitempos2(pIfDcdTarget, zoneTarget2);
		bRv = aCDcdFillrectLine2.DcDraw(&targetitempos2);

		CDcdFillrect aCDcdFillrectLine3(aCdBrushProp);
		CaDcdTargetItemPosition	targetitempos3(pIfDcdTarget, zoneTarget3);
		bRv = aCDcdFillrectLine3.DcDraw(&targetitempos3);

		CDcdFillrect aCDcdFillrectLine4(aCdBrushProp);
		CaDcdTargetItemPosition	targetitempos4(pIfDcdTarget, zoneTarget4);
		bRv = aCDcdFillrectLine4.DcDraw(&targetitempos4);

		CDcdFillrect aCDcdFillrectLine5(aCdBrushProp);
		CaDcdTargetItemPosition	targetitempos5(pIfDcdTarget, zoneTarget5);
		bRv = aCDcdFillrectLine5.DcDraw(&targetitempos5);



		//CdDcdPosXy	posOrg(zoneTarget.getX().getPos(), zoneTarget.getY().getPos() + 1);
		//CdDcdPosXy	posDst(zoneTarget.getX().getEndPos(), zoneTarget.getY().getPos() + 1);

		//CDcdFreeLine	aCDcdFreeLine(posOrg, posDst, 
		//	CdDcdFreeLineProp(3,m_CdColorProp, LINESTYLE_DASH));
		//bRv = aCDcdFreeLine.DcDraw(pIfDcdTarget);
	}
	else if (m_eDrawType == EDrawType::DrawType_UpperCircle)
	{
		DcdPos DcdPosUp = zoneTarget.getY().getPos() + zoneTarget.getY().getSize() * 0.2;
		DcdPos DcdPosDown = zoneTarget.getY().getEndPos();
		DcdSize VerticalSize = DcdPosDown - DcdPosUp;
		DcdPos DcdPosLeft = zoneTarget.getX().getPos() + zoneTarget.getX().getSize() / 2 - VerticalSize / 2;
		DcdPos DcdPosRight = DcdPosLeft + VerticalSize;

		{
			CdPenProp	aCdPenProp(2, m_CdColorProp, CdPenProp::SOLID);

			Ou<CGdiHPenHolder>	pHPenHolder = pIfDcdTarget->createGdiHPenHolder(aCdPenProp);
			HPEN hPenPrev = (HPEN)SelectObject(pIfDcdTarget->getHdc(), pHPenHolder->getHPen());

			CdBrushProp	aCdBrushProp(CdColorProp(0, 0, 0), CdBrushProp::NULLBRUSH);
			Ou<CGdiHBrushHolder> pHBrushHolder = pIfDcdTarget->createGdiHBrushHolder(aCdBrushProp);
			HBRUSH hBrushPrev = (HBRUSH)SelectObject(pIfDcdTarget->getHdc(), pHBrushHolder->getHBrush());


			Ellipse(
				pIfDcdTarget->getHdc(),
				DcdPosLeft,
				DcdPosUp,
				DcdPosRight,
				DcdPosDown);

			// --------------------------------
			//	GDIオブジェクトの選択を解除
			if (hPenPrev != NULL)
			{
				SelectObject(pIfDcdTarget->getHdc(), hPenPrev);
				hPenPrev = NULL;
			}
			if (hBrushPrev != NULL)
			{
				SelectObject(pIfDcdTarget->getHdc(), hBrushPrev);
				hBrushPrev = NULL;
			}
		}
	}
	else if (m_eDrawType == EDrawType::DrawType_LowerTriangle)
	{
		DcdPos DcdPosUp = zoneTarget.getY().getPos();
		DcdPos DcdPosDown = zoneTarget.getY().getEndPos() - zoneTarget.getY().getSize() * 0.2;
		DcdSize VerticalSize = DcdPosDown - DcdPosUp;
		DcdPos DcdPosCenter = zoneTarget.getX().getPos() + zoneTarget.getX().getSize() / 2 ;
		DcdPos DcdPosLeft = DcdPosCenter - VerticalSize / 2;
		DcdPos DcdPosRight = DcdPosCenter + VerticalSize / 2;

		CdDcdPosXy	DcdPosTriangle[3];
		DcdPosTriangle[0].setX(DcdPosCenter);
		DcdPosTriangle[0].setY(DcdPosUp);
		DcdPosTriangle[1].setX(DcdPosLeft);
		DcdPosTriangle[1].setY(DcdPosDown);
		DcdPosTriangle[2].setX(DcdPosRight);
		DcdPosTriangle[2].setY(DcdPosDown);
		{
			CdPenProp	aCdPenProp(2, m_CdColorProp, CdPenProp::SOLID);

			Ou<CGdiHPenHolder>	pHPenHolder = pIfDcdTarget->createGdiHPenHolder(aCdPenProp);
			HPEN hPenPrev = (HPEN)SelectObject(pIfDcdTarget->getHdc(), pHPenHolder->getHPen());

			CdBrushProp	aCdBrushProp(CdColorProp(0, 0, 0), CdBrushProp::NULLBRUSH);

			Ou<CGdiHBrushHolder> pHBrushHolder = pIfDcdTarget->createGdiHBrushHolder(aCdBrushProp);
			HBRUSH hBrushPrev = (HBRUSH)SelectObject(pIfDcdTarget->getHdc(), pHBrushHolder->getHBrush());

			POINT pointTriangle[3];
			CConverter_WinGdi aConv;
			pointTriangle[0] = aConv.POINTOf(DcdPosTriangle[0]);
			pointTriangle[1] = aConv.POINTOf(DcdPosTriangle[1]);
			pointTriangle[2] = aConv.POINTOf(DcdPosTriangle[2]);
			Polygon(
				pIfDcdTarget->getHdc(),
				pointTriangle,
				3);
			// --------------------------------
			//	GDIオブジェクトの選択を解除
			if (hPenPrev != NULL)
			{
				SelectObject(pIfDcdTarget->getHdc(), hPenPrev);
				hPenPrev = NULL;
			}
			if (hBrushPrev != NULL)
			{
				SelectObject(pIfDcdTarget->getHdc(), hBrushPrev);
				hBrushPrev = NULL;
			}
		}
	}

	//CDcdFreeLine	aCDcdFreeLine( posOrg , posDst ,  m_CdLineProp ) ;
	//bool bRv = aCDcdFreeLine.DcDraw( pIfDcdTarget ) ;

	return ( bRv ) ;
}
	
bool CDcDraw_Extension::getItemSize( IfDcdTarget* pIfDcdTarget , 
							CdDcdSizeXy* pCdDcdSizeXy ) 
{
	pCdDcdSizeXy->setX( 3 ) ;
	pCdDcdSizeXy->setY( 3 ) ;
	return ( true ) ;
}
// ********************************
//	CDcDraw_Extension
// ********************************
	// ********************************
	//@name 属性
	// ********************************
//CdDcdFreeLineProp CDcDraw_Extension::getCdLineProp()const 
//{
//	return m_CdLineProp ;
//}
//CDcDraw_Extension& CDcDraw_Extension::setCdLineProp( 
//		const CdDcdFreeLineProp& value )
//{
//	m_CdLineProp = value ;
//	return *this ;
//};

} //namespace ViewOperationTable
