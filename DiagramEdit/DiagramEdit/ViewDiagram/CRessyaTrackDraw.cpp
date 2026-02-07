/*
OuDiaSecond Copyright (C) 2017 diagram_mania

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
//	CRessyaTrackDraw.cpp
// $Id: CERessyaTrackDraw.cpp 
// ****************************************************************
*/
#include "stdafx.h"
#include "CRessyaTrackDraw.h"
#include "DcDraw\CDcdLine.h"
#include "DcDraw\CaDcdTargetItemPosition.h"

//namespace entDgr{
namespace ViewDiagram {
	
// ****************************************************************
//	CRessyaTrackDraw
// ****************************************************************
	//*******************************
	//	コンストラクタ
	//*******************************
//CRessyaTrackDraw::CRessyaTrackDraw(
//		const CentDedDgrDia* pCentDedDgrDia ,
//		const CdDcdZoneXy& zonexyDgrZone ,
//		bool bDisplayRessyasenKudari ,
//		bool bDisplayRessyasenNobori ) :
//	m_pCentDedDgrDia( pCentDedDgrDia ) ,
//	m_zonexyDgrZone( zonexyDgrZone ) ,
//	m_bDisplayRessyasenKudari( bDisplayRessyasenKudari ) ,
//	m_bDisplayRessyasenNobori( bDisplayRessyasenNobori )
//{
//}
CRessyaTrackDraw::CRessyaTrackDraw(CDcdDiagram* pCDcdDiagram,
	IfDcdTarget* pIfDcdTarget,
	bool bDisplayRessyasenKudari,
	bool bDisplayRessyasenNobori) :
	//super(
	//	pCDcdDiagram->getCentDedDgrDia(),
	//	pCDcdDiagram->DgrFromDcd(pIfDcdTarget, pIfDcdTarget->getZone()),
	//	bDisplayRessyasenKudari,
	//	bDisplayRessyasenNobori),
	m_pCDcdDiagram(pCDcdDiagram),
	m_pIfDcdTarget(pIfDcdTarget),
	m_bDisplayRessyasenKudari(bDisplayRessyasenKudari),
	m_bDisplayRessyasenNobori(bDisplayRessyasenNobori),
	m_pCentDedDgrDia(pCDcdDiagram->getCentDedDgrDia()) ,
	m_zonexyDgrZone(pCDcdDiagram->DgrFromDcd(pIfDcdTarget, pIfDcdTarget->getZone())) 
{
};
CRessyaTrackDraw::~CRessyaTrackDraw()
{
}

	// --------------------------------
	//@name CRessyaTrackDraw
	// --------------------------------
void CRessyaTrackDraw::onCentDedDgrRessya(
		ERessyahoukou eRessyahoukou ,
		int iRessyaIdx ,
		const CentDedDgrRessya* pCentDedDgrRessya ) 
{
	//	対象となる描画領域を、
	//	『ダイヤグラムエンティティ座標系』で保持します。
	//	これは、今回描画を行う範囲を表しています。
	CdDcdZoneXy	zonexyDgrZone = m_zonexyDgrZone ;

	for (int idx = 0; idx < pCentDedDgrRessya->getCentDedDgrRessyaTrackLineCont()->size(); idx++)
	{
		const CentDedDgrRessyaTrackLine* pCentDedDgrRessyaTrackLine =
			pCentDedDgrRessya->getCentDedDgrRessyaTrackLineCont()->get(idx);
		if (pCentDedDgrRessyaTrackLine->getChakuOperation() < 0)
		{
			//到着列車の、駅線から番線線までの縦線を描写します
			// --------------------------------
			//	番線線を囲む矩形領域を求める
			// --------------------------------
			{
				CdDcdPosXy	posRessyaTrackKiten;
				CdDcdPosXy	posRessyaTrackSyuuten;
				posRessyaTrackKiten =
					m_pCentDedDgrDia->calcDgrPosRessyaTrackChaku(
						pCentDedDgrRessya,
						pCentDedDgrRessyaTrackLine,
						false);
				posRessyaTrackSyuuten =
					m_pCentDedDgrDia->calcDgrPosRessyaTrackChaku(
						pCentDedDgrRessya,
						pCentDedDgrRessyaTrackLine,
						true);
				if (zonexyDgrRessyasenOnDgrZone(
					posRessyaTrackKiten,
					posRessyaTrackSyuuten))
				{
					onCentDedDgrRessyaTrack(
						posRessyaTrackKiten,
						posRessyaTrackSyuuten,
						pCentDedDgrRessya,
						0,
						-1);
				}
			}
			if (pCentDedDgrRessyaTrackLine->getChakuOperation() == -2)
			{
				CdDcdPosXy	posRessyaTrackKiten;
				CdDcdPosXy	posRessyaTrackSyuuten;
				posRessyaTrackKiten =
					m_pCentDedDgrDia->calcDgrPosRessyaTrackChaku(
						pCentDedDgrRessya,
						pCentDedDgrRessyaTrackLine,
						false);
				posRessyaTrackSyuuten =
					m_pCentDedDgrDia->calcDgrPosRessyaTrackChaku(
						pCentDedDgrRessya,
						pCentDedDgrRessyaTrackLine,
						false,
						-30,
						-30);
				if (zonexyDgrRessyasenOnDgrZone(
					posRessyaTrackKiten,
					posRessyaTrackSyuuten))
				{
					onCentDedDgrRessyaTrack(
						posRessyaTrackKiten,
						posRessyaTrackSyuuten,
						pCentDedDgrRessya);
				}
			}
		}
		if (pCentDedDgrRessyaTrackLine->getHatsuOperation() < 0)
		{
			//出発列車の、番線線から駅線までの縦線を描写します
			// --------------------------------
			//	番線線を囲む矩形領域を求める
			// --------------------------------
			{
				CdDcdPosXy	posRessyaTrackKiten;
				CdDcdPosXy	posRessyaTrackSyuuten;
				posRessyaTrackKiten =
					m_pCentDedDgrDia->calcDgrPosRessyaTrackHatsu(
						pCentDedDgrRessya,
						pCentDedDgrRessyaTrackLine,
						true);
				posRessyaTrackSyuuten =
					m_pCentDedDgrDia->calcDgrPosRessyaTrackHatsu(
						pCentDedDgrRessya,
						pCentDedDgrRessyaTrackLine,
						false);
				if (zonexyDgrRessyasenOnDgrZone(
					posRessyaTrackKiten,
					posRessyaTrackSyuuten))
				{
					onCentDedDgrRessyaTrack(
						posRessyaTrackKiten,
						posRessyaTrackSyuuten,
						pCentDedDgrRessya,
						-1,
						0);
				}
			}
			if (pCentDedDgrRessyaTrackLine->getHatsuOperation() == -2)
			{
				CdDcdPosXy	posRessyaTrackKiten;
				CdDcdPosXy	posRessyaTrackSyuuten;
				posRessyaTrackKiten =
					m_pCentDedDgrDia->calcDgrPosRessyaTrackHatsu(
						pCentDedDgrRessya,
						pCentDedDgrRessyaTrackLine,
						false);
				posRessyaTrackSyuuten =
					m_pCentDedDgrDia->calcDgrPosRessyaTrackHatsu(
						pCentDedDgrRessya,
						pCentDedDgrRessyaTrackLine,
						false,
						30,
						30);
				if (zonexyDgrRessyasenOnDgrZone(
					posRessyaTrackKiten,
					posRessyaTrackSyuuten))
				{
					onCentDedDgrRessyaTrack(
						posRessyaTrackKiten,
						posRessyaTrackSyuuten,
						pCentDedDgrRessya);
				}
			}
		}
		if (pCentDedDgrRessyaTrackLine->getChakuOperation() < 0 &&
			pCentDedDgrRessyaTrackLine->getHatsuOperation() < 0)
		{
			//当駅が中間駅の列車の、在線を示す横線を描写します
			// --------------------------------
			//	在線線の座標を求めます
			// --------------------------------
			CdDcdPosXy	posRessyaTrackKiten;
			CdDcdPosXy	posRessyaTrackSyuuten;
			CdDcdPosXy	posRessyaTrackDummy;

			posRessyaTrackKiten =
				m_pCentDedDgrDia->calcDgrPosRessyaTrackChaku(
					pCentDedDgrRessya,
					pCentDedDgrRessyaTrackLine,
					true);
			posRessyaTrackSyuuten =
				m_pCentDedDgrDia->calcDgrPosRessyaTrackHatsu(
					pCentDedDgrRessya,
					pCentDedDgrRessyaTrackLine,
					true);
			posRessyaTrackDummy = posRessyaTrackSyuuten;
			if (posRessyaTrackKiten == posRessyaTrackSyuuten)
			{
				posRessyaTrackDummy.setX(posRessyaTrackSyuuten.getX() + 1);
			}

			if (zonexyDgrRessyasenOnDgrZone(
				posRessyaTrackKiten,
				posRessyaTrackDummy))
			{
				//iX_Dcd,iY_Dcd = 列車情報を表示する駅の発時刻の座標
				//	単位は、 IfDcdTarget の座標系
				int iX_Left_Dcd = m_pCDcdDiagram->XDgrToDcd(m_pIfDcdTarget,
					posRessyaTrackKiten.getX());
				int iX_Right_Dcd = m_pCDcdDiagram->XDgrToDcd(m_pIfDcdTarget,
					posRessyaTrackSyuuten.getX());
				int iY_Dcd = m_pCDcdDiagram->YDgrToDcd(m_pIfDcdTarget,
					posRessyaTrackKiten.getY());

				onCentDedDgrRessyaTrackHorizontal(
					iX_Left_Dcd,
					iX_Right_Dcd,
					iY_Dcd,
					pCentDedDgrRessya,
					-1,
					1);

				if (iX_Left_Dcd == iX_Right_Dcd &&
					pCentDedDgrRessyaTrackLine->getIsTeisya())
				{
					CdPenProp	aCdPenProp(1, CdColorProp(0, 0, 0), CdPenProp::SOLID);
					int idxRessyasyubetsu = pCentDedDgrRessya->getRessyasyubetsuIndex();
					if (0 <= idxRessyasyubetsu &&
						idxRessyasyubetsu < getCentDedDgrDia()->getMuCentDedDgrRessyasyubetsu()->size())
					{
						const CentDedDgrRessyasyubetsu* pCentDedDgrRessyasyubetsu =
							getCentDedDgrDia()->getMuCentDedDgrRessyasyubetsu()->get(idxRessyasyubetsu);
						CentDedRessyasyubetsu::CdDiagramLineStyle	aCdDiagramLineStyle =
							pCentDedDgrRessyasyubetsu->getCdDiagramLineStyle();

						aCdPenProp.setColor(aCdDiagramLineStyle.getDiagramSenColor());
					}
					Ou<CGdiHPenHolder>	pHPenHolder = m_pIfDcdTarget->createGdiHPenHolder(aCdPenProp);
					HPEN hPenPrev = (HPEN)SelectObject(m_pIfDcdTarget->getHdc(), pHPenHolder->getHPen());

					CdBrushProp	aCdBrushProp(CdColorProp(0, 0, 0), CdBrushProp::NULLBRUSH);
					Ou<CGdiHBrushHolder> pHBrushHolder = m_pIfDcdTarget->createGdiHBrushHolder(aCdBrushProp);
					HBRUSH hBrushPrev = (HBRUSH)SelectObject(m_pIfDcdTarget->getHdc(), pHBrushHolder->getHBrush());


					Ellipse(
						m_pIfDcdTarget->getHdc(),
						iX_Left_Dcd - 3,
						iY_Dcd - 3,
						iX_Right_Dcd + 4,
						iY_Dcd + 4);
					// --------------------------------
					//	GDIオブジェクトの選択を解除
					if (hPenPrev != NULL)
					{
						SelectObject(m_pIfDcdTarget->getHdc(), hPenPrev);
						hPenPrev = NULL;
					}
					if (hBrushPrev != NULL)
					{
						SelectObject(m_pIfDcdTarget->getHdc(), hBrushPrev);
						hBrushPrev = NULL;
					}
				}
				else if (iX_Left_Dcd == iX_Right_Dcd)
				{
					CdPenProp	aCdPenProp(1, CdColorProp(0, 0, 0), CdPenProp::SOLID);
					int idxRessyasyubetsu = pCentDedDgrRessya->getRessyasyubetsuIndex();
					if (0 <= idxRessyasyubetsu &&
						idxRessyasyubetsu < getCentDedDgrDia()->getMuCentDedDgrRessyasyubetsu()->size())
					{
						const CentDedDgrRessyasyubetsu* pCentDedDgrRessyasyubetsu =
							getCentDedDgrDia()->getMuCentDedDgrRessyasyubetsu()->get(idxRessyasyubetsu);
						CentDedRessyasyubetsu::CdDiagramLineStyle	aCdDiagramLineStyle =
							pCentDedDgrRessyasyubetsu->getCdDiagramLineStyle();

						aCdPenProp.setColor(aCdDiagramLineStyle.getDiagramSenColor());
					}
					Ou<CGdiHPenHolder>	pHPenHolder = m_pIfDcdTarget->createGdiHPenHolder(aCdPenProp);
					HPEN hPenPrev = (HPEN)SelectObject(m_pIfDcdTarget->getHdc(), pHPenHolder->getHPen());

					CdBrushProp	aCdBrushProp(CdColorProp(0, 0, 0), CdBrushProp::NULLBRUSH);
					Ou<CGdiHBrushHolder> pHBrushHolder = m_pIfDcdTarget->createGdiHBrushHolder(aCdBrushProp);
					HBRUSH hBrushPrev = (HBRUSH)SelectObject(m_pIfDcdTarget->getHdc(), pHBrushHolder->getHBrush());

					MoveToEx(
						m_pIfDcdTarget->getHdc(),
						iX_Left_Dcd - 3,
						iY_Dcd - 3,
						NULL);
					LineTo(
						m_pIfDcdTarget->getHdc(),
						iX_Right_Dcd + 4,
						iY_Dcd + 4);
					MoveToEx(
						m_pIfDcdTarget->getHdc(),
						iX_Left_Dcd - 3,
						iY_Dcd + 3,
						NULL);
					LineTo(
						m_pIfDcdTarget->getHdc(),
						iX_Right_Dcd + 4,
						iY_Dcd - 4);
					// --------------------------------
					//	GDIオブジェクトの選択を解除
					if (hPenPrev != NULL)
					{
						SelectObject(m_pIfDcdTarget->getHdc(), hPenPrev);
						hPenPrev = NULL;
					}
					if (hBrushPrev != NULL)
					{
						SelectObject(m_pIfDcdTarget->getHdc(), hBrushPrev);
						hBrushPrev = NULL;
					}
				}
			}
		}
		if (pCentDedDgrRessyaTrackLine->getChakuOperation() < 0 &&
			pCentDedDgrRessyaTrackLine->getHatsuOperation() == 1)
		{
			int iCompareTrack = 0;
			int iRessyaTrack = pCentDedDgrRessya->getMuCentDedDgrRessyaTrack()
				->get(pCentDedDgrRessyaTrackLine->getChakuEkiOrder())
				->getRessyaTrackIndex();
			int iShuntTrack = pCentDedDgrRessya->getMuCentDedDgrRessyaTrack()
				->get(pCentDedDgrRessyaTrackLine->getHatsuEkiOrder())
				->getShuntTrackIndex();
			if ((iRessyaTrack > iShuntTrack &&
				pCentDedDgrRessya->getRessyahoukou() == ERessyahoukou::Ressyahoukou_Kudari) ||
				(iRessyaTrack < iShuntTrack &&
					pCentDedDgrRessya->getRessyahoukou() == ERessyahoukou::Ressyahoukou_Nobori))
			{
				iCompareTrack = -1;
			}
			else
			{
				iCompareTrack = 1;
			}
			//終着駅・入換における、着時刻から入換発時刻までの横線
			// --------------------------------
			//	在線線の座標を求めます
			// --------------------------------
			{
				CdDcdPosXy	posRessyaTrackKiten;
				CdDcdPosXy	posRessyaTrackSyuuten;
				CdDcdPosXy	posRessyaTrackDummy;

				posRessyaTrackKiten =
					m_pCentDedDgrDia->calcDgrPosRessyaTrackChaku(
						pCentDedDgrRessya,
						pCentDedDgrRessyaTrackLine,
						true);
				posRessyaTrackSyuuten =
					m_pCentDedDgrDia->calcDgrPosRessyaTrackOperationHatsu(
						pCentDedDgrRessya,
						pCentDedDgrRessyaTrackLine,
						true,
						false);

				posRessyaTrackDummy = posRessyaTrackSyuuten;
				if (posRessyaTrackKiten == posRessyaTrackSyuuten)
				{
					posRessyaTrackDummy.setX(posRessyaTrackSyuuten.getX() + 1);
				}

				if (zonexyDgrRessyasenOnDgrZone(
					posRessyaTrackKiten,
					posRessyaTrackDummy))
				{
					int iX_Left_Dcd = m_pCDcdDiagram->XDgrToDcd(m_pIfDcdTarget,
						posRessyaTrackKiten.getX());
					int iX_Right_Dcd = m_pCDcdDiagram->XDgrToDcd(m_pIfDcdTarget,
						posRessyaTrackSyuuten.getX());
					int iY_Dcd = m_pCDcdDiagram->YDgrToDcd(m_pIfDcdTarget,
						posRessyaTrackKiten.getY());

					onCentDedDgrRessyaTrackHorizontal(
						iX_Left_Dcd,
						iX_Right_Dcd,
						iY_Dcd,
						pCentDedDgrRessya,
						-1,
						iCompareTrack);
				}
			}

			//入換における、番線移動の縦線
			{
				// --------------------------------
				//	番線線を囲む矩形領域を求める
				// --------------------------------
				CdDcdPosXy	posRessyaTrackKiten;
				CdDcdPosXy	posRessyaTrackSyuuten;
				{
					posRessyaTrackKiten =
						m_pCentDedDgrDia->calcDgrPosRessyaTrackOperationHatsu(
							pCentDedDgrRessya,
							pCentDedDgrRessyaTrackLine,
							true,
							false);
					posRessyaTrackSyuuten =
						m_pCentDedDgrDia->calcDgrPosRessyaTrackOperationChaku(
							pCentDedDgrRessya,
							pCentDedDgrRessyaTrackLine,
							false,
							false);
				}

				if (zonexyDgrRessyasenOnDgrZone(
					posRessyaTrackKiten,
					posRessyaTrackSyuuten))
				{
					CdDcdFreeLineProp	aCdLineProp;
					onCentDedDgrRessyaTrack(
						posRessyaTrackKiten,
						posRessyaTrackSyuuten,
						pCentDedDgrRessya,
						-1,
						-1);
				}
			}

			//終着駅・入換における、入換時刻から1分後までの横線
			// --------------------------------
			//	在線線の座標を求めます
			// --------------------------------
			{
				CdDcdPosXy	posRessyaTrackKiten;
				CdDcdPosXy	posRessyaTrackSyuuten;

				posRessyaTrackKiten =
					m_pCentDedDgrDia->calcDgrPosRessyaTrackOperationChaku(
						pCentDedDgrRessya,
						pCentDedDgrRessyaTrackLine,
						false,
						false);
				posRessyaTrackSyuuten =
					m_pCentDedDgrDia->calcDgrPosRessyaTrackOperationChaku(
						pCentDedDgrRessya,
						pCentDedDgrRessyaTrackLine,
						false,
						false,
						60);

				if (zonexyDgrRessyasenOnDgrZone(
					posRessyaTrackKiten,
					posRessyaTrackSyuuten))
				{
					int iX_Left_Dcd = m_pCDcdDiagram->XDgrToDcd(m_pIfDcdTarget,
						posRessyaTrackKiten.getX());
					int iX_Right_Dcd = m_pCDcdDiagram->XDgrToDcd(m_pIfDcdTarget,
						posRessyaTrackSyuuten.getX());
					int iY_Dcd = m_pCDcdDiagram->YDgrToDcd(m_pIfDcdTarget,
						posRessyaTrackKiten.getY());

					onCentDedDgrRessyaTrackHorizontal(
						iX_Left_Dcd,
						iX_Right_Dcd,
						iY_Dcd,
						pCentDedDgrRessya,
						-iCompareTrack,
						0);
				}
			}
		}
		if (pCentDedDgrRessyaTrackLine->getChakuOperation() < 0 &&
			(pCentDedDgrRessyaTrackLine->getHatsuOperation() == 0 ||
				pCentDedDgrRessyaTrackLine->getHatsuOperation() == 2))
		{
			//終着駅・作業なしor入庫における、到着時刻から1分後までの横線
			// --------------------------------
			//	在線線の座標を求めます
			// --------------------------------
			{
				CdDcdPosXy	posRessyaTrackKiten;
				CdDcdPosXy	posRessyaTrackSyuuten;

				posRessyaTrackKiten =
					m_pCentDedDgrDia->calcDgrPosRessyaTrackChaku(
						pCentDedDgrRessya,
						pCentDedDgrRessyaTrackLine,
						true);
				posRessyaTrackSyuuten =
					m_pCentDedDgrDia->calcDgrPosRessyaTrackChaku(
						pCentDedDgrRessya,
						pCentDedDgrRessyaTrackLine,
						true,
						60);

				if (zonexyDgrRessyasenOnDgrZone(
					posRessyaTrackKiten,
					posRessyaTrackSyuuten))
				{
					int iX_Left_Dcd = m_pCDcdDiagram->XDgrToDcd(m_pIfDcdTarget,
						posRessyaTrackKiten.getX());
					int iX_Right_Dcd = m_pCDcdDiagram->XDgrToDcd(m_pIfDcdTarget,
						posRessyaTrackSyuuten.getX());
					int iY_Dcd = m_pCDcdDiagram->YDgrToDcd(m_pIfDcdTarget,
						posRessyaTrackKiten.getY());

					onCentDedDgrRessyaTrackHorizontal(
						iX_Left_Dcd,
						iX_Right_Dcd,
						iY_Dcd,
						pCentDedDgrRessya,
						-1,
						0);
				}
			}
		}
		if (pCentDedDgrRessyaTrackLine->getChakuOperation() < 0 &&
			pCentDedDgrRessyaTrackLine->getHatsuOperation() == 2)
		{
			//終着駅・入庫における、△または▽印の描写
			// --------------------------------
			//	入庫マークを描画する位置を算出
			// --------------------------------
			CdDcdPosXy	posTriangle_Dcd[3];

			CdDcdPosXy	posRessyaTrackUp;
			CdDcdPosXy	posRessyaTrackDown;

			posRessyaTrackUp =
				m_pCentDedDgrDia->calcDgrPosRessyaTrackChaku(
					pCentDedDgrRessya,
					pCentDedDgrRessyaTrackLine,
					true,
					60);

			posRessyaTrackDown =
				m_pCentDedDgrDia->calcDgrPosRessyaTrackChaku(
					pCentDedDgrRessya,
					pCentDedDgrRessyaTrackLine,
					true,
					60,
					m_pCentDedDgrDia->getDgrYSizeEkikanDefault());

			if (zonexyDgrRessyasenOnDgrZone(
				posRessyaTrackUp,
				posRessyaTrackDown))
			{
				//iX_Dcd,iY_Dcd = 列車情報を表示する駅の発時刻の座標
				//	単位は、 IfDcdTarget の座標系
				// --------------------------------
				int iY_DcdUp = m_pCDcdDiagram->YDgrToDcd(m_pIfDcdTarget,
					posRessyaTrackUp.getY());
				int iY_DcdDown = m_pCDcdDiagram->YDgrToDcd(m_pIfDcdTarget,
					posRessyaTrackDown.getY());
				int iX_DcdCenter = m_pCDcdDiagram->XDgrToDcd(m_pIfDcdTarget,
					posRessyaTrackUp.getX());
				int iX_DcdLeft = iX_DcdCenter
					- (iY_DcdDown - iY_DcdUp) / 2;
				int iX_DcdRight = iX_DcdCenter
					+ (iY_DcdDown - iY_DcdUp) / 2;

				posTriangle_Dcd[0].setX((DcdPos)iX_DcdCenter);
				posTriangle_Dcd[0].setY((DcdPos)iY_DcdUp);
				posTriangle_Dcd[1].setX((DcdPos)iX_DcdLeft);
				posTriangle_Dcd[1].setY((DcdPos)iY_DcdDown);
				posTriangle_Dcd[2].setX((DcdPos)iX_DcdRight);
				posTriangle_Dcd[2].setY((DcdPos)iY_DcdDown);

				CdPenProp	aCdPenProp(1, CdColorProp(0, 0, 0), CdPenProp::SOLID);
				int idxRessyasyubetsu = pCentDedDgrRessya->getRessyasyubetsuIndex();
				if (0 <= idxRessyasyubetsu &&
					idxRessyasyubetsu < getCentDedDgrDia()->getMuCentDedDgrRessyasyubetsu()->size())
				{
					const CentDedDgrRessyasyubetsu* pCentDedDgrRessyasyubetsu =
						getCentDedDgrDia()->getMuCentDedDgrRessyasyubetsu()->get(idxRessyasyubetsu);
					CentDedRessyasyubetsu::CdDiagramLineStyle	aCdDiagramLineStyle =
						pCentDedDgrRessyasyubetsu->getCdDiagramLineStyle();

					aCdPenProp.setColor(aCdDiagramLineStyle.getDiagramSenColor());
				}
				Ou<CGdiHPenHolder>	pHPenHolder = m_pIfDcdTarget->createGdiHPenHolder(aCdPenProp);
				HPEN hPenPrev = (HPEN)SelectObject(m_pIfDcdTarget->getHdc(), pHPenHolder->getHPen());

				CdBrushProp	aCdBrushProp(CdColorProp(0, 0, 0), CdBrushProp::NULLBRUSH);
				Ou<CGdiHBrushHolder> pHBrushHolder = m_pIfDcdTarget->createGdiHBrushHolder(aCdBrushProp);
				HBRUSH hBrushPrev = (HBRUSH)SelectObject(m_pIfDcdTarget->getHdc(), pHBrushHolder->getHBrush());

				POINT pointTriangle[3];
				CConverter_WinGdi aConv;
				pointTriangle[0] = aConv.POINTOf(posTriangle_Dcd[0]);
				pointTriangle[1] = aConv.POINTOf(posTriangle_Dcd[1]);
				pointTriangle[2] = aConv.POINTOf(posTriangle_Dcd[2]);
				Polygon(
					m_pIfDcdTarget->getHdc(),
					pointTriangle,
					3);
				// --------------------------------
				//	GDIオブジェクトの選択を解除
				if (hPenPrev != NULL)
				{
					SelectObject(m_pIfDcdTarget->getHdc(), hPenPrev);
					hPenPrev = NULL;
				}
				if (hBrushPrev != NULL)
				{
					SelectObject(m_pIfDcdTarget->getHdc(), hBrushPrev);
					hBrushPrev = NULL;
				}
			}
		}

		if (pCentDedDgrRessyaTrackLine->getChakuOperation() == 1 &&
			pCentDedDgrRessyaTrackLine->getHatsuOperation() < 0)
		{
			int iCompareTrack = 0;
			int iRessyaTrack = pCentDedDgrRessya->getMuCentDedDgrRessyaTrack()
				->get(pCentDedDgrRessyaTrackLine->getHatsuEkiOrder())
				->getRessyaTrackIndex();
			int iShuntTrack = pCentDedDgrRessya->getMuCentDedDgrRessyaTrack()
				->get(pCentDedDgrRessyaTrackLine->getChakuEkiOrder())
				->getShuntTrackIndex();
			if ((iRessyaTrack > iShuntTrack &&
				pCentDedDgrRessya->getRessyahoukou() == ERessyahoukou::Ressyahoukou_Kudari) ||
				(iRessyaTrack < iShuntTrack &&
					pCentDedDgrRessya->getRessyahoukou() == ERessyahoukou::Ressyahoukou_Nobori))
			{
				iCompareTrack = -1;
			}
			else
			{
				iCompareTrack = 1;
			}
			//始発駅・入換における、入換時刻から発時刻までの横線
			// --------------------------------
			//	在線線の座標を求めます
			// --------------------------------
			{
				CdDcdPosXy	posRessyaTrackKiten;
				CdDcdPosXy	posRessyaTrackSyuuten;
				CdDcdPosXy	posRessyaTrackDummy;

				posRessyaTrackKiten =
					m_pCentDedDgrDia->calcDgrPosRessyaTrackOperationChaku(
						pCentDedDgrRessya,
						pCentDedDgrRessyaTrackLine,
						true,
						true);
				posRessyaTrackSyuuten =
					m_pCentDedDgrDia->calcDgrPosRessyaTrackHatsu(
						pCentDedDgrRessya,
						pCentDedDgrRessyaTrackLine,
						true);

				posRessyaTrackDummy = posRessyaTrackSyuuten;
				if (posRessyaTrackKiten == posRessyaTrackSyuuten)
				{
					posRessyaTrackDummy.setX(posRessyaTrackSyuuten.getX() + 1);
				}

				if (zonexyDgrRessyasenOnDgrZone(
					posRessyaTrackKiten,
					posRessyaTrackDummy))
				{
					int iX_Left_Dcd = m_pCDcdDiagram->XDgrToDcd(m_pIfDcdTarget,
						posRessyaTrackKiten.getX());
					int iX_Right_Dcd = m_pCDcdDiagram->XDgrToDcd(m_pIfDcdTarget,
						posRessyaTrackSyuuten.getX());
					int iY_Dcd = m_pCDcdDiagram->YDgrToDcd(m_pIfDcdTarget,
						posRessyaTrackKiten.getY());

					onCentDedDgrRessyaTrackHorizontal(
						iX_Left_Dcd,
						iX_Right_Dcd,
						iY_Dcd,
						pCentDedDgrRessya,
						iCompareTrack,
						1);
				}
			}
			//入換における、番線移動の縦線
			{
				// --------------------------------
				//	番線線を囲む矩形領域を求める
				// --------------------------------
				CdDcdPosXy	posRessyaTrackKiten;
				CdDcdPosXy	posRessyaTrackSyuuten;
				{
					posRessyaTrackKiten =
						m_pCentDedDgrDia->calcDgrPosRessyaTrackOperationHatsu(
							pCentDedDgrRessya,
							pCentDedDgrRessyaTrackLine,
							false,
							true);
					posRessyaTrackSyuuten =
						m_pCentDedDgrDia->calcDgrPosRessyaTrackOperationChaku(
							pCentDedDgrRessya,
							pCentDedDgrRessyaTrackLine,
							true,
							true);
				}

				if (zonexyDgrRessyasenOnDgrZone(
					posRessyaTrackKiten,
					posRessyaTrackSyuuten))
				{
					onCentDedDgrRessyaTrack(
						posRessyaTrackKiten,
						posRessyaTrackSyuuten,
						pCentDedDgrRessya,
						-1,
						-1);
				}
			}

			//始発駅・入換における、1分前から入換時刻までの横線
			// --------------------------------
			//	在線線の座標を求めます
			// --------------------------------
			{
				CdDcdPosXy	posRessyaTrackKiten;
				CdDcdPosXy	posRessyaTrackSyuuten;

				posRessyaTrackKiten =
					m_pCentDedDgrDia->calcDgrPosRessyaTrackOperationHatsu(
						pCentDedDgrRessya,
						pCentDedDgrRessyaTrackLine,
						false,
						true,
						-60);
				posRessyaTrackSyuuten =
					m_pCentDedDgrDia->calcDgrPosRessyaTrackOperationHatsu(
						pCentDedDgrRessya,
						pCentDedDgrRessyaTrackLine,
						false,
						true);

				if (zonexyDgrRessyasenOnDgrZone(
					posRessyaTrackKiten,
					posRessyaTrackSyuuten))
				{
					int iX_Left_Dcd = m_pCDcdDiagram->XDgrToDcd(m_pIfDcdTarget,
						posRessyaTrackKiten.getX());
					int iX_Right_Dcd = m_pCDcdDiagram->XDgrToDcd(m_pIfDcdTarget,
						posRessyaTrackSyuuten.getX());
					int iY_Dcd = m_pCDcdDiagram->YDgrToDcd(m_pIfDcdTarget,
						posRessyaTrackKiten.getY());

					onCentDedDgrRessyaTrackHorizontal(
						iX_Left_Dcd,
						iX_Right_Dcd,
						iY_Dcd,
						pCentDedDgrRessya,
						0,
						-iCompareTrack);
				}
			}
		}
		if ((pCentDedDgrRessyaTrackLine->getChakuOperation() == 0 ||
			pCentDedDgrRessyaTrackLine->getChakuOperation() == 2 )&&
			pCentDedDgrRessyaTrackLine->getHatsuOperation() < 0)
		{
			//始発駅・作業なしor出区における、1分前から発車時刻までの横線
			// --------------------------------
			//	在線線の座標を求めます
			// --------------------------------
			{
				CdDcdPosXy	posRessyaTrackKiten;
				CdDcdPosXy	posRessyaTrackSyuuten;

				posRessyaTrackKiten =
					m_pCentDedDgrDia->calcDgrPosRessyaTrackHatsu(
						pCentDedDgrRessya,
						pCentDedDgrRessyaTrackLine,
						true,
						-60);
				posRessyaTrackSyuuten =
					m_pCentDedDgrDia->calcDgrPosRessyaTrackHatsu(
						pCentDedDgrRessya,
						pCentDedDgrRessyaTrackLine,
						true);

				if (zonexyDgrRessyasenOnDgrZone(
					posRessyaTrackKiten,
					posRessyaTrackSyuuten))
				{
					int iX_Left_Dcd = m_pCDcdDiagram->XDgrToDcd(m_pIfDcdTarget,
						posRessyaTrackKiten.getX());
					int iX_Right_Dcd = m_pCDcdDiagram->XDgrToDcd(m_pIfDcdTarget,
						posRessyaTrackSyuuten.getX());
					int iY_Dcd = m_pCDcdDiagram->YDgrToDcd(m_pIfDcdTarget,
						posRessyaTrackKiten.getY());

					onCentDedDgrRessyaTrackHorizontal(
						iX_Left_Dcd,
						iX_Right_Dcd,
						iY_Dcd,
						pCentDedDgrRessya,
						0,
						1);
				}
			}
		}
		if (pCentDedDgrRessyaTrackLine->getChakuOperation() == 2 &&
			pCentDedDgrRessyaTrackLine->getHatsuOperation() < 0)
		{
			// --------------------------------
			//	出庫マークを描画する位置を算出
			// --------------------------------

			CdDcdPosXy	posRessyaTrackUp;
			CdDcdPosXy	posRessyaTrackDown;

			posRessyaTrackUp =
				m_pCentDedDgrDia->calcDgrPosRessyaTrackHatsu(
					pCentDedDgrRessya,
					pCentDedDgrRessyaTrackLine,
					true,
					-60,
					-(m_pCentDedDgrDia->getDgrYSizeEkikanDefault()));

			posRessyaTrackDown =
				m_pCentDedDgrDia->calcDgrPosRessyaTrackHatsu(
					pCentDedDgrRessya,
					pCentDedDgrRessyaTrackLine,
					true,
					-60);

			//iX_Dcd,iY_Dcd = 列車情報を表示する駅の発時刻の座標
			//	単位は、 IfDcdTarget の座標系
			// --------------------------------
			if (zonexyDgrRessyasenOnDgrZone(
				posRessyaTrackUp,
				posRessyaTrackDown))
			{
				int iY_DcdUp = m_pCDcdDiagram->YDgrToDcd(m_pIfDcdTarget,
					posRessyaTrackUp.getY());
				int iY_DcdDown = m_pCDcdDiagram->YDgrToDcd(m_pIfDcdTarget,
					posRessyaTrackDown.getY());
				int iX_DcdLeft = m_pCDcdDiagram->XDgrToDcd(m_pIfDcdTarget,
					posRessyaTrackUp.getX())
					- (iY_DcdDown - iY_DcdUp) / 2;
				int iX_DcdRight = m_pCDcdDiagram->XDgrToDcd(m_pIfDcdTarget,
					posRessyaTrackUp.getX())
					+ (iY_DcdDown - iY_DcdUp) / 2;

				CdPenProp	aCdPenProp(1, CdColorProp(0, 0, 0), CdPenProp::SOLID);
				int idxRessyasyubetsu = pCentDedDgrRessya->getRessyasyubetsuIndex();
				if (0 <= idxRessyasyubetsu &&
					idxRessyasyubetsu < getCentDedDgrDia()->getMuCentDedDgrRessyasyubetsu()->size())
				{
					const CentDedDgrRessyasyubetsu* pCentDedDgrRessyasyubetsu =
						getCentDedDgrDia()->getMuCentDedDgrRessyasyubetsu()->get(idxRessyasyubetsu);
					CentDedRessyasyubetsu::CdDiagramLineStyle	aCdDiagramLineStyle =
						pCentDedDgrRessyasyubetsu->getCdDiagramLineStyle();

					aCdPenProp.setColor(aCdDiagramLineStyle.getDiagramSenColor());
				}
				Ou<CGdiHPenHolder>	pHPenHolder = m_pIfDcdTarget->createGdiHPenHolder(aCdPenProp);
				HPEN hPenPrev = (HPEN)SelectObject(m_pIfDcdTarget->getHdc(), pHPenHolder->getHPen());

				CdBrushProp	aCdBrushProp(CdColorProp(0, 0, 0), CdBrushProp::NULLBRUSH);
				Ou<CGdiHBrushHolder> pHBrushHolder = m_pIfDcdTarget->createGdiHBrushHolder(aCdBrushProp);
				HBRUSH hBrushPrev = (HBRUSH)SelectObject(m_pIfDcdTarget->getHdc(), pHBrushHolder->getHBrush());

				{
					Ellipse(
						m_pIfDcdTarget->getHdc(),
						iX_DcdLeft,
						iY_DcdUp,
						iX_DcdRight,
						iY_DcdDown);
				}
				// --------------------------------
				//	GDIオブジェクトの選択を解除
				if (hPenPrev != NULL)
				{
					SelectObject(m_pIfDcdTarget->getHdc(), hPenPrev);
					hPenPrev = NULL;
				}
				if (hBrushPrev != NULL)
				{
					SelectObject(m_pIfDcdTarget->getHdc(), hBrushPrev);
					hBrushPrev = NULL;
				}
			}
		}
	}
}

bool CRessyaTrackDraw::zonexyDgrRessyasenOnDgrZone(
	CdDcdPosXy posRessyaTrackKiten,
	CdDcdPosXy posRessyaTrackSyuuten)
{
	CdDcdZoneXy	zonexyDgrRessyaTrack;
	{
		CdDcdZone	zoneDgrX;
		zoneDgrX.setBeginEndPos(
			posRessyaTrackKiten.getX(),
			posRessyaTrackSyuuten.getX());
		CdDcdZone	zoneDgrY;
		zoneDgrY.setBeginEndPos(
			posRessyaTrackKiten.getY(),
			posRessyaTrackSyuuten.getY());

		if (!(zoneDgrX.getSize() == 0 && zoneDgrY.getSize() == 0))
		{
			if (zoneDgrX.getSize() == 0)
			{
				//	始点と終点のX座標が同一の場合(垂直線)は、例外的に幅を1とします
				//	(0としてしまうと、線が描画されません)
				zoneDgrX.setSize(1);
			}
			if (zoneDgrY.getSize() == 0)
			{
				//	始点と終点のY座標が同一の場合(水平線)は、例外的に幅を1とします
				//	(0としてしまうと、線が描画されません)
				zoneDgrY.setSize(1);
			}
		}

		zonexyDgrRessyaTrack.setX(zoneDgrX).setY(zoneDgrY);

	}
	CdDcdZoneXy	zonexyDgrRessyaTrackOnDgrZone = m_zonexyDgrZone.CrossZone(zonexyDgrRessyaTrack);
	//zonexyDgrRessyasenOnDgrZone
	//	列車線と描画領域の、交差領域
	//	この値のサイズが0なら、この列車線は描画可能な領域にはありません。

	if (zonexyDgrRessyaTrackOnDgrZone.getX().getSize() > 0 &&
		zonexyDgrRessyaTrackOnDgrZone.getY().getSize() > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CRessyaTrackDraw::onCentDedDgrRessyaTrack(
	CdDcdPosXy posRessyaTrackKiten,
	CdDcdPosXy posRessyaTrackSyuuten,
	const CentDedDgrRessya* pCentDedDgrRessya,
	int iYShiftKiten,
	int iYShiftSyuuten)
{
	// --------------------------------
	//	直線の形状を決定
	// --------------------------------
	CdDcdFreeLineProp	aCdLineProp;
	{
		int idxRessyasyubetsu = pCentDedDgrRessya->getRessyasyubetsuIndex();
		if (0 <= idxRessyasyubetsu &&
			idxRessyasyubetsu < getCentDedDgrDia()->getMuCentDedDgrRessyasyubetsu()->size())
		{
			const CentDedDgrRessyasyubetsu* pCentDedDgrRessyasyubetsu =
				getCentDedDgrDia()->getMuCentDedDgrRessyasyubetsu()->get(idxRessyasyubetsu);
			CentDedRessyasyubetsu::CdDiagramLineStyle	aCdDiagramLineStyle =
				pCentDedDgrRessyasyubetsu->getCdDiagramLineStyle();

			aCdLineProp.setColor(aCdDiagramLineStyle.getDiagramSenColor());
		}
	}

	// --------------------------------
	//	直線の描画位置を決定
	// --------------------------------
	CDcdFreeLine	aCDcdFreeLine(aCdLineProp);
	CdDcdPosXy posKitenDcd = m_pCDcdDiagram->DgrToDcd(
		m_pIfDcdTarget, posRessyaTrackKiten);
	CdDcdPosXy posSyuutenDcd = m_pCDcdDiagram->DgrToDcd(
		m_pIfDcdTarget, posRessyaTrackSyuuten);
	if (posKitenDcd.getY() < posSyuutenDcd.getY())
	{
		if (iYShiftKiten != 0)
		{
			posKitenDcd.setY(posKitenDcd.getY() - iYShiftKiten);
		}
		if (iYShiftSyuuten != 0)
		{
			posSyuutenDcd.setY(posSyuutenDcd.getY() + iYShiftSyuuten);
		}
	}
	else
	{
		if (iYShiftKiten != 0)
		{
			posKitenDcd.setY(posKitenDcd.getY() + iYShiftKiten);
		}
		if (iYShiftSyuuten != 0)
		{
			posSyuutenDcd.setY(posSyuutenDcd.getY() - iYShiftSyuuten);
		}
	}

	aCDcdFreeLine.setOrg(posKitenDcd);
	aCDcdFreeLine.setDst(posSyuutenDcd);
	aCDcdFreeLine.DcDraw(m_pIfDcdTarget);
}

void CRessyaTrackDraw::onCentDedDgrRessyaTrackHorizontal(
	int iX_Left_Dcd,
	int iX_Right_Dcd,
	int iY_Dcd,
	const CentDedDgrRessya* pCentDedDgrRessya,
	int iYChamferLeft,
	int iYChamferRight)
{
	// --------------------------------
	//	直線の形状を決定
	// --------------------------------
	CdDcdFreeLineProp	aCdLineProp;
	{
		CdPenProp	aCdPenProp(1, CdColorProp(0, 0, 0), CdPenProp::SOLID);

		CdBrushProp	aCdBrushProp(CdColorProp(0, 0, 0), CdBrushProp::SOLID);

		int idxRessyasyubetsu = pCentDedDgrRessya->getRessyasyubetsuIndex();
		if (0 <= idxRessyasyubetsu &&
			idxRessyasyubetsu < getCentDedDgrDia()->getMuCentDedDgrRessyasyubetsu()->size())
		{
			const CentDedDgrRessyasyubetsu* pCentDedDgrRessyasyubetsu =
				getCentDedDgrDia()->getMuCentDedDgrRessyasyubetsu()->get(idxRessyasyubetsu);
			CentDedRessyasyubetsu::CdDiagramLineStyle	aCdDiagramLineStyle =
				pCentDedDgrRessyasyubetsu->getCdDiagramLineStyle();

			aCdPenProp.setColor(aCdDiagramLineStyle.getDiagramSenColor());
			aCdBrushProp.setColor(aCdDiagramLineStyle.getDiagramSenColor());
			aCdLineProp.setColor(aCdDiagramLineStyle.getDiagramSenColor());
		}
		Ou<CGdiHPenHolder>	pHPenHolder = m_pIfDcdTarget->createGdiHPenHolder(aCdPenProp);
		HPEN hPenPrev = (HPEN)SelectObject(m_pIfDcdTarget->getHdc(), pHPenHolder->getHPen());

		Ou<CGdiHBrushHolder> pHBrushHolder = m_pIfDcdTarget->createGdiHBrushHolder(aCdBrushProp);
		HBRUSH hBrushPrev = (HBRUSH)SelectObject(m_pIfDcdTarget->getHdc(), pHBrushHolder->getHBrush());

		//int iX_Left_Dcd_Fix = iX_Left_Dcd;
		//int iX_Right_Dcd_Fix = iX_Right_Dcd;
		//if (iYChamferLeft != 0 && iX_Right_Dcd != iX_Left_Dcd)
		//{
		//	CdDcdPosXy	posTriangle_Dcd[3];
		//	posTriangle_Dcd[0].setX(iX_Left_Dcd_Fix);
		//	if ((iYChamferLeft > 0 &&
		//		pCentDedDgrRessya->getRessyahoukou() == ERessyahoukou::Ressyahoukou_Kudari) ||
		//		(iYChamferLeft < 0 &&
		//			pCentDedDgrRessya->getRessyahoukou() == ERessyahoukou::Ressyahoukou_Nobori)){
		//		posTriangle_Dcd[0].setY(iY_Dcd + 1);
		//		if (iX_Right_Dcd - iX_Left_Dcd < 2) {
		//			posTriangle_Dcd[1].setX(iX_Left_Dcd_Fix + 1);
		//			posTriangle_Dcd[1].setY(iY_Dcd );
		//			posTriangle_Dcd[2].setX(iX_Left_Dcd_Fix + 1);
		//			posTriangle_Dcd[2].setY(iY_Dcd + 1);

		//		}
		//		else {
		//			posTriangle_Dcd[1].setX(iX_Left_Dcd_Fix + 2);
		//			posTriangle_Dcd[1].setY(iY_Dcd - 1);
		//			posTriangle_Dcd[2].setX(iX_Left_Dcd_Fix + 2);
		//			posTriangle_Dcd[2].setY(iY_Dcd + 1);
		//		}
		//	}
		//	else{
		//		posTriangle_Dcd[0].setY(iY_Dcd - 1);
		//		if (iX_Right_Dcd - iX_Left_Dcd < 2) {
		//			posTriangle_Dcd[1].setX(iX_Left_Dcd_Fix + 1);
		//			posTriangle_Dcd[1].setY(iY_Dcd - 1);
		//			posTriangle_Dcd[2].setX(iX_Left_Dcd_Fix + 1);
		//			posTriangle_Dcd[2].setY(iY_Dcd );

		//		}
		//		else {
		//			posTriangle_Dcd[1].setX(iX_Left_Dcd_Fix + 2);
		//			posTriangle_Dcd[1].setY(iY_Dcd - 1);
		//			posTriangle_Dcd[2].setX(iX_Left_Dcd_Fix + 2);
		//			posTriangle_Dcd[2].setY(iY_Dcd + 1);
		//		}
		//	}

		//	POINT pointTriangle[3];
		//	CConverter_WinGdi aConv;
		//	pointTriangle[0] = aConv.POINTOf(posTriangle_Dcd[0]);
		//	pointTriangle[1] = aConv.POINTOf(posTriangle_Dcd[1]);
		//	pointTriangle[2] = aConv.POINTOf(posTriangle_Dcd[2]);
		//	Polygon(
		//		m_pIfDcdTarget->getHdc(),
		//		pointTriangle,
		//		3);

		//	iX_Left_Dcd_Fix = iX_Left_Dcd_Fix + 2;
		//}
		//if (iYChamferRight != 0 && iX_Right_Dcd != iX_Left_Dcd)
		//{
		//	CdDcdPosXy	posTriangle_Dcd[3];
		//	posTriangle_Dcd[0].setX(iX_Right_Dcd_Fix);
		//	if ((iYChamferRight > 0 &&
		//		pCentDedDgrRessya->getRessyahoukou() == ERessyahoukou::Ressyahoukou_Kudari) ||
		//		(iYChamferRight < 0 &&
		//			pCentDedDgrRessya->getRessyahoukou() == ERessyahoukou::Ressyahoukou_Nobori)) {
		//		posTriangle_Dcd[0].setY(iY_Dcd + 1);
		//		if (iX_Right_Dcd - iX_Left_Dcd < 2) {
		//			posTriangle_Dcd[1].setX(iX_Right_Dcd_Fix - 1);
		//			posTriangle_Dcd[1].setY(iY_Dcd );
		//			posTriangle_Dcd[2].setX(iX_Right_Dcd_Fix - 1);
		//			posTriangle_Dcd[2].setY(iY_Dcd + 1);
		//		}
		//		else {
		//			posTriangle_Dcd[1].setX(iX_Right_Dcd_Fix - 2);
		//			posTriangle_Dcd[1].setY(iY_Dcd - 1);
		//			posTriangle_Dcd[2].setX(iX_Right_Dcd_Fix - 2);
		//			posTriangle_Dcd[2].setY(iY_Dcd + 1);
		//		}
		//	}
		//	else {
		//		posTriangle_Dcd[0].setY(iY_Dcd - 1);
		//		if (iX_Right_Dcd - iX_Left_Dcd < 2) {
		//			posTriangle_Dcd[1].setX(iX_Right_Dcd_Fix - 1);
		//			posTriangle_Dcd[1].setY(iY_Dcd - 1);
		//			posTriangle_Dcd[2].setX(iX_Right_Dcd_Fix - 1);
		//			posTriangle_Dcd[2].setY(iY_Dcd );
		//		}
		//		else {
		//			posTriangle_Dcd[1].setX(iX_Right_Dcd_Fix - 2);
		//			posTriangle_Dcd[1].setY(iY_Dcd - 1);
		//			posTriangle_Dcd[2].setX(iX_Right_Dcd_Fix - 2);
		//			posTriangle_Dcd[2].setY(iY_Dcd + 1);
		//		}
		//	}


		//	POINT pointTriangle[3];
		//	CConverter_WinGdi aConv;
		//	pointTriangle[0] = aConv.POINTOf(posTriangle_Dcd[0]);
		//	pointTriangle[1] = aConv.POINTOf(posTriangle_Dcd[1]);
		//	pointTriangle[2] = aConv.POINTOf(posTriangle_Dcd[2]);
		//	Polygon(
		//		m_pIfDcdTarget->getHdc(),
		//		pointTriangle,
		//		3);
		//	iX_Right_Dcd_Fix = iX_Right_Dcd_Fix - 2;
		//}
		//if (iX_Left_Dcd_Fix <= iX_Right_Dcd_Fix){
		//	Rectangle(
		//		m_pIfDcdTarget->getHdc(),
		//		iX_Left_Dcd_Fix,
		//		iY_Dcd - 1,
		//		iX_Right_Dcd_Fix + 1,
		//		iY_Dcd + 2);
		//}

		if (iX_Left_Dcd == iX_Right_Dcd){
			CDcdFreeLine	aCDcdFreeLine(aCdLineProp);
			CdDcdPosXy posKitenDcd ;
			CdDcdPosXy posSyuutenDcd ;
			posKitenDcd.setX(iX_Left_Dcd);
			posKitenDcd.setY(iY_Dcd - 2);
			posSyuutenDcd.setX(iX_Left_Dcd);
			posSyuutenDcd.setY(iY_Dcd + 2);
			aCDcdFreeLine.setOrg(posKitenDcd);
			aCDcdFreeLine.setDst(posSyuutenDcd);
			aCDcdFreeLine.DcDraw(m_pIfDcdTarget);
		}
		else
		{
			//左上、左下、右下、右上の順で設定します
			CdDcdPosXy	posQuadrilateral_Dcd[4];
			if (iYChamferLeft == 0)
			{
				posQuadrilateral_Dcd[0].setX(iX_Left_Dcd);
				posQuadrilateral_Dcd[0].setY(iY_Dcd - 1);
				posQuadrilateral_Dcd[1].setX(iX_Left_Dcd);
				posQuadrilateral_Dcd[1].setY(iY_Dcd + 1);
			}
			else if ((iYChamferLeft > 0 &&
				pCentDedDgrRessya->getRessyahoukou() == ERessyahoukou::Ressyahoukou_Kudari) ||
				(iYChamferLeft < 0 &&
					pCentDedDgrRessya->getRessyahoukou() == ERessyahoukou::Ressyahoukou_Nobori))
			{
				posQuadrilateral_Dcd[0].setX(iX_Left_Dcd + 2);
				posQuadrilateral_Dcd[0].setY(iY_Dcd - 1);
				posQuadrilateral_Dcd[1].setX(iX_Left_Dcd);
				posQuadrilateral_Dcd[1].setY(iY_Dcd + 1);
			}
			else
			{
				posQuadrilateral_Dcd[0].setX(iX_Left_Dcd);
				posQuadrilateral_Dcd[0].setY(iY_Dcd - 1);
				posQuadrilateral_Dcd[1].setX(iX_Left_Dcd + 2);
				posQuadrilateral_Dcd[1].setY(iY_Dcd + 1);
			}
			if(iYChamferRight == 0)
			{
				posQuadrilateral_Dcd[2].setX(iX_Right_Dcd);
				posQuadrilateral_Dcd[2].setY(iY_Dcd + 1);
				posQuadrilateral_Dcd[3].setX(iX_Right_Dcd);
				posQuadrilateral_Dcd[3].setY(iY_Dcd - 1);
			}
			else if ((iYChamferRight > 0 &&
				pCentDedDgrRessya->getRessyahoukou() == ERessyahoukou::Ressyahoukou_Kudari) ||
				(iYChamferRight < 0 &&
					pCentDedDgrRessya->getRessyahoukou() == ERessyahoukou::Ressyahoukou_Nobori))
			{
				posQuadrilateral_Dcd[2].setX(iX_Right_Dcd);
				posQuadrilateral_Dcd[2].setY(iY_Dcd + 1);
				posQuadrilateral_Dcd[3].setX(iX_Right_Dcd - 2);
				posQuadrilateral_Dcd[3].setY(iY_Dcd - 1);
			}
			else
			{
				posQuadrilateral_Dcd[2].setX(iX_Right_Dcd - 2);
				posQuadrilateral_Dcd[2].setY(iY_Dcd + 1);
				posQuadrilateral_Dcd[3].setX(iX_Right_Dcd);
				posQuadrilateral_Dcd[3].setY(iY_Dcd - 1);
			}

			POINT pointQuadrilateral[4];
			CConverter_WinGdi aConv;
			pointQuadrilateral[0] = aConv.POINTOf(posQuadrilateral_Dcd[0]);
			pointQuadrilateral[1] = aConv.POINTOf(posQuadrilateral_Dcd[1]);
			pointQuadrilateral[2] = aConv.POINTOf(posQuadrilateral_Dcd[2]);
			pointQuadrilateral[3] = aConv.POINTOf(posQuadrilateral_Dcd[3]);
			Polygon(
				m_pIfDcdTarget->getHdc(),
				pointQuadrilateral,
				4);

		}
		// --------------------------------
		//	GDIオブジェクトの選択を解除
		if (hPenPrev != NULL)
		{
			SelectObject(m_pIfDcdTarget->getHdc(), hPenPrev);
			hPenPrev = NULL;
		}
		if (hBrushPrev != NULL)
		{
			SelectObject(m_pIfDcdTarget->getHdc(), hBrushPrev);
			hBrushPrev = NULL;
		}
	}
}

	// ********************************
	//@name CEnumRessyasen-関連
	// ********************************
const CentDedDgrDia*	CRessyaTrackDraw::getCentDedDgrDia()
{	
		return m_pCentDedDgrDia ; 
} ;
	// ********************************
	//@name CEnumRessyasen-属性
	// ********************************
CdDcdZoneXy	CRessyaTrackDraw::getDgrZone()
{
	return m_zonexyDgrZone ;
};

bool CRessyaTrackDraw::getDisplayRessyaTrack(  ERessyahoukou eRessyahoukou )const
{
	bool bRv = false ;
	if ( eRessyahoukou == Ressyahoukou_Kudari ){
		bRv = m_bDisplayRessyasenKudari ;
	}	else if ( eRessyahoukou == Ressyahoukou_Nobori ) {
		bRv = m_bDisplayRessyasenNobori ;
	}
	return ( bRv ) ;
}
	// ********************************
	//@name CEnumRessyasen-操作
	// ********************************
void CRessyaTrackDraw::execute()
{
	//	対象となる描画領域を、
	//	『ダイヤグラムエンティティ座標系』で保持します。
	//	これは、今回描画を行う範囲を表しています。
	CdDcdZoneXy	zonexyDgrZone = m_zonexyDgrZone ;


	for ( int iRessyahoukou = Ressyahoukou_Kudari ;
		iRessyahoukou <= Ressyahoukou_Nobori ;
		iRessyahoukou ++ )
	{
		// --------------------------------
		//	列車方向の処理を実行するか否かの判定
		// --------------------------------
		ERessyahoukou	eRessyahoukou = (ERessyahoukou)iRessyahoukou ;
		if ( !getDisplayRessyaTrack( eRessyahoukou ) ) 
		{
			//	この方向の処理は行いません。
			continue ;
		}
		// --------------------------------
		//	列車方向毎の処理
		// --------------------------------
		const Mu<const CentDedDgrRessya*>*	pMuCentDedDgrRessya = 
			m_pCentDedDgrDia->getCentDedDgrRessyaCont( eRessyahoukou );
		int iSize = pMuCentDedDgrRessya->size();
#ifdef _OPENMP
#pragma omp parallel for schedule(guided)
#endif
		for (int iRessyaIdx = 0;
			iRessyaIdx < iSize;
			iRessyaIdx++)
		{
			// --------------------------------
			//	列車毎の処理
			// --------------------------------
			const CentDedDgrRessya* pCentDedDgrRessya = 
				pMuCentDedDgrRessya->get( iRessyaIdx ) ;
			if ( pCentDedDgrRessya->getIsNull() ||
				pCentDedDgrRessya->getCentDedDgrRessyaTrackLineCont()->size() <= 0)
				//pCentDedDgrRessya->getCentDedDgrRessyasenCont()->size() <= 0 )
			{
				//	NULL列車・列車在線線の全くない列車は対象外
				continue ;
			}
			// --------------------------------

			CentDedDgrRessya	aCentDedDgrRessya( *pCentDedDgrRessya ) ;
			//	列車の最大のDgrX座標＜ダイヤグラムの
			//	左端のDgrX座標になるまで、
			//	列車全体のDgrX座標を24時間ずつ減算する。
			//
			//	この処理は、列車がダイヤグラム左端を
			//	跨いでいる場合に、必要です。
			//	たとえば、ダイヤグラムの左端が 00:00:00
			//	になっているダイヤの場合、
			//	23:00 から 01:00 に向かって走っている列車は
			//	-01:00→01:00 
			//	 23:00→25:00
			//	の２箇所に列車線を描画しなくてはなりません。
			//	このループでは、一旦列車の時刻を
			//	-25:00→-23:00 
			//	にします。
			while ( !( aCentDedDgrRessya.getDgrXZone().getEndPos() < 
				zonexyDgrZone.getX().getPos() ) )
			{
				aCentDedDgrRessya.modifyDgrXPos( - CdDedJikoku::TOTALSECONDS_A_DAY ) ;
			}

			//	ここで、24時間加算します。これにより、列車時刻は
			//	-01:00→01:00 
			//	となります。
			aCentDedDgrRessya.modifyDgrXPos( + CdDedJikoku::TOTALSECONDS_A_DAY ) ;
			
			for ( ; aCentDedDgrRessya.getDgrXZone().getPos() < 
					zonexyDgrZone.getX().getEndPos() ;
				aCentDedDgrRessya.modifyDgrXPos( + CdDedJikoku::TOTALSECONDS_A_DAY ) )
			{
				// --------------------------------
				//	列車の表示位置（２４時間間隔）毎の処理
				// --------------------------------
				CdDcdZone	zoneDgrXCross = zonexyDgrZone.getX().CrossZone(
					aCentDedDgrRessya.getDgrXZone() ) ;
				if ( zoneDgrXCross.getSize() > 0 )
				{
					//	この列車は、対象となる描画領域内にあります。
					onCentDedDgrRessya( 
						eRessyahoukou ,
						iRessyaIdx ,
						&aCentDedDgrRessya ) ;
				}
			}
		}
	}
};

} //namespace entDgr
