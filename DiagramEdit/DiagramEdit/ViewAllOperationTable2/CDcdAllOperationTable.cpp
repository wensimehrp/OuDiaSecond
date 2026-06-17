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
/*
// ****************************************************************
//	CDcdAllOperationTable.cpp
// ****************************************************************
*/
/** @file */
#include "stdafx.h"
#include <chrono>

#include "DcDraw/CaDcdTargetClip.h"
#include "DcdCd/Pos/CLineFunc.h"
#include "DcdCd/Pos/CconvDcdPosOnZone_PosOrgAndRate.h"
#include "LogMsg\LogMsg.h"
#include "DcDraw\CaDcdTargetItemPosition.h"
#include "str/strprintf.h"

#include "CDcdAllOperationTable.h"
#include "..\resource.h"
#include "..\DiagramEdit.h"

namespace ViewAllOperationTable2 {

// ****************************************************************
//	CDcdAllOperationTable
// ****************************************************************
/**
	ダイヤグラムビューの、EndPosを表示するための
	右・下側の余裕領域を、
	DcDraw座標系で指定します。
	
	この値が0の場合は
	終着駅(ダイヤグラム座標のX.EndPos)と、
	一日の最後の時刻(ダイヤグラム座標のY.EndPos)
	が、画面外になり、表示されません。
*/
const int DIAGRAM_SIZE_MARGIN_DCD=2 ;


	// ********************************
	//@name 定数
	// ********************************
/**
*	ダイヤグラムの
*	縦罫の間隔の選択肢を保持するテーブルです。
*/
const CDcdAllOperationTable::VLINE	CDcdAllOperationTable::m_arVline[8] =
{
	{  1 * 60  ,  5 * 60  , 30 * 60  } ,
	{  2 * 60  , 10 * 60  , 60 * 60  } ,
	{  5 * 60  , 10 * 60  , 60 * 60  } ,
	{ 10 * 60  , 30 * 60  , 60 * 60  } ,
	{ 15 * 60  , 15 * 60  , 60 * 60  } ,
	{ 20 * 60  , 20 * 60  , 60 * 60  } ,
	{ 30 * 60  , 30 * 60  , 60 * 60  } ,
	{ 60 * 60  , 60 * 60  , 60 * 60  } ,
};


// --------------------------------
//@name 下請関数
// --------------------------------
void CDcdAllOperationTable::adjustProp() 
{
	// --------------------------------
	//DcdPerDgrX,DcdPerDgrY の値正規化
	// --------------------------------

	CconvContentPosToDcdTarget::CaConvX* pConvX = 
		m_CconvContentPosToDcdTarget.getX() ;
	// m_dwDcdPerDgrX<0.0001 なら、0.0001
	// m_dwDcdPerDgrX は、10で制限
	if ( pConvX->getTargetPosPerContent() < 0.0001 )
	{
		pConvX->setTargetPosPerContent( 0.0001 , NULL ) ;
	}
	else if ( pConvX->getTargetPosPerContent() > 10 )
	{
		pConvX->setTargetPosPerContent( 10 , NULL ) ;
	}

	CconvContentPosToDcdTarget::CaConvY* pConvY = 
		m_CconvContentPosToDcdTarget.getY() ;
	if ( pConvY->getTargetPosPerContent() < 0.0001 )
	{
		pConvY->setTargetPosPerContent( 0.0001 , NULL ) ;
	}
	else if ( pConvY->getTargetPosPerContent() > 10 )
	{
		pConvY->setTargetPosPerContent( 10 , NULL ) ;
	}
}

// ********************************
//	コンストラクタ
// ********************************
CDcdAllOperationTable::CDcdAllOperationTable( 
		tstring strName,
		vector<tstring>* strOperationNumber,
		CdDcdZoneXy* CdDcdZone_Operation,
		const CdDedDispProp& aCdDedDispProp ) :
	m_fontpropOperationTableFont(9, _T("Meiryo UI")),
	m_fontpropAllOperationTableJikokuFont(8, _T("Meiryo UI")),
	//m_fontpropOperationTableFont(9, _T("ＭＳ ゴシック")),
	//m_fontpropAllOperationTableJikokuFont(8, _T("ＭＳ ゴシック")),
	m_colorDiaJikuColor( CdColorProp( 0 , 0 , 0 ) ) ,
	m_colorGridColor(CdColorProp(0, 0, 0)),
	m_colorStringColor(CdColorProp(0, 0, 0)),
	m_bDisplayRessyabangou( true ) ,
	m_bDisplayRessyamei( true ) ,
	m_CconvContentPosToDcdTarget( 
		0 , DEFAULT_DCD_PER_DGR_X() , 0 , DEFAULT_DCD_PER_DGR_Y() ,
		DIAGRAM_SIZE_MARGIN_DCD , DIAGRAM_SIZE_MARGIN_DCD ) ,
	m_idxVlineMode( 3 ),
	m_strName(strName),
	m_strOperationNumber(strOperationNumber),
	m_CdDcdZone(CdDcdZone_Operation),
	m_iClippingCount(0)
{
	readCdDedDispProp( aCdDedDispProp ) ;

	adjustProp() ;
}

CDcdAllOperationTable::CDcdAllOperationTable() :
	m_fontpropOperationTableFont(9, _T("Meiryo UI")),
	m_fontpropAllOperationTableJikokuFont(8, _T("Meiryo UI")),
	//m_fontpropOperationTableFont(9, _T("ＭＳ ゴシック")),
	//m_fontpropAllOperationTableJikokuFont(8, _T("ＭＳ ゴシック")),
	m_colorDiaJikuColor( CdColorProp( 0 , 0 , 0 ) ) ,
	m_colorGridColor(CdColorProp(0, 0, 0)),
	m_colorStringColor(CdColorProp(0, 0, 0)),
	m_bDisplayRessyabangou( true ) ,
	m_bDisplayRessyamei( true ) ,
	m_CconvContentPosToDcdTarget( 
		0 , DEFAULT_DCD_PER_DGR_X() , 0 , DEFAULT_DCD_PER_DGR_Y() ,
		DIAGRAM_SIZE_MARGIN_DCD , DIAGRAM_SIZE_MARGIN_DCD ) ,
	m_idxVlineMode( 3 ),
	m_strName(_T("")),
	m_strOperationNumber(NULL),
	m_CdDcdZone(NULL),
	m_iClippingCount(0)
{
}

CDcdAllOperationTable::~CDcdAllOperationTable() 
{
}
	
// ********************************
//@name IfDcDraw
// ********************************
bool CDcdAllOperationTable::DcDraw(IfDcdTarget* pIfDcdTarget)
{
	bool bRv = false;

	CdDcdFreeLineProp	linepropDiaJikuDot(1, m_colorDiaJikuColor, LINESTYLE_DOT2);
	CdDcdFreeLineProp	linepropDiaJikuNormal(1, m_colorDiaJikuColor);
	CdDcdFreeLineProp	linepropDiaJikuBold(2, m_colorDiaJikuColor);
	CdDcdFreeLineProp	linepropGridNormal(1, m_colorGridColor);
	CdDcdFreeLineProp	linepropGridBold(2, m_colorGridColor);

	// --------------------------------
	//	DcdTargetの領域に
	//	クリッピングを行います。			
	// --------------------------------
	CaDcdTargetClip*	pTargetClip = NULL;
	{
		//CdDcdZoneXy	zonexyAllOperationTable = getCentDedDgrDia()->getZone();
		//CdDcdZoneXy	zonexyAllOperationTable = *m_CdDcdZoneXy;
		//zonexyAllOperationTable = ダイヤグラムの範囲を、
		//	『ダイヤグラムエンティティ座標系』で保持します。
		//	X座標は24時間分、Y座標は起点から終点までを表します。

		CdDcdZoneXy	zonexyDcd_CentDedDgrDia =
			DgrToDcd(pIfDcdTarget, *m_CdDcdZone);
		//zonexyDcd_CentDedDgrDia = 
		//	ダイヤグラムの範囲を、『DcDraw座標系』で保持します。
		//	但し、この値をクリップ領域にすると、
		//	EndPosはクリップ領域に含まれません。
		zonexyDcd_CentDedDgrDia.setX(
			CdDcdZone(
				zonexyDcd_CentDedDgrDia.getX().getPos(),
				zonexyDcd_CentDedDgrDia.getX().getSize()
				+ DIAGRAM_SIZE_MARGIN_DCD));
		zonexyDcd_CentDedDgrDia.setY(
			CdDcdZone(
				zonexyDcd_CentDedDgrDia.getY().getPos(),
				zonexyDcd_CentDedDgrDia.getY().getSize()
				+ DIAGRAM_SIZE_MARGIN_DCD));
		//zonexyDcd_CentDedDgrDia = ダイヤグラムの範囲を
		//	『DcDraw座標系』で保持します。

		//クリップ領域は、
		//	IfDcdTargetの領域と
		//	ダイヤグラムの範囲の交差領域です。
		CdDcdZoneXy	zonexyClip =
			pIfDcdTarget->getZone().CrossZone(zonexyDcd_CentDedDgrDia);

		pTargetClip = new CaDcdTargetClip(pIfDcdTarget, zonexyClip);
		pTargetClip->validate();
	}
	// --------------------------------
	//	描画を行う領域の計算	
	// --------------------------------
	CdDcdZoneXy	zonexyAllOperationTable = *m_CdDcdZone;
	//zonexyAllOperationTable = ダイヤグラムの範囲を、
	//	『ダイヤグラムエンティティ座標系』で保持します。
	//	X座標は24時間分、Y座標は起点から終点までを表します。
	CdDcdZoneXy	zonexyZone_Dgr = getZone_Dgr(pIfDcdTarget);
//#pragma omp parallel sections
	{
		// --------------------------------
		//	縦罫線を描画します。
		// --------------------------------
//#pragma omp section
		{

			//	縦罫線は、ダイヤグラム起点時刻の次の、縦罫線描画時刻から開始
			//	(4:01で2分目なら4:02、1分目なら4:01、10分目なら4:10)
			DcdPos posDgrXVlineOrg = m_CdDcdZone->getX().getPos();
			{
				int iMod = zonexyAllOperationTable.getX().getPos() % getVlinePitch();
				if (iMod > 0)
				{
					posDgrXVlineOrg += getVlinePitch() - iMod;
				}
			}
			//posDgrXVlineOrg = 時刻表示の開始位置
			//	ダイヤグラム起点時刻の次の正時から開始(4:59なら5:00、5:00なら5:00)


			DcdPos iXEndPos = zonexyAllOperationTable.getX().getEndPos();
			DcdPos iIncrement = getVlinePitch();
#pragma omp parallel for schedule(guided)
			for (DcdPos posDgrX = posDgrXVlineOrg;
				posDgrX <= iXEndPos;
				posDgrX += iIncrement)
			{
				//posDgrX = ダイヤグラムエンティティ座標での、
				//	縦罫線の位置
				CDcdFreeLine	aCDcdFreeLine;
				if (posDgrX % getVlineBoldPitch() == 0)
				{
					aCDcdFreeLine.setCdLineProp(linepropDiaJikuBold);
				}
				else if (posDgrX % getVlineMiddlePitch() == 0)
				{
					aCDcdFreeLine.setCdLineProp(linepropDiaJikuNormal);
				}
				else
				{
					aCDcdFreeLine.setCdLineProp(linepropDiaJikuDot);
				}
				//	座標を、Dgr→Dcdに変換
				DcdPos posDcdX = XDgrToDcd(pTargetClip, posDgrX);

				DcdPos posDgrY = zonexyZone_Dgr.getY().getPos();
				CdDcdZone	zoneDgrY(posDgrY, getOperationNumber()->size() * DEFAULT_YSIZE_PER_ONEOPERATION() - posDgrY);
				if (getClippingCount() > 0)
				{
					DcdSize YSize = getClippingCount() * DEFAULT_YSIZE_PER_ONEOPERATION();
					zoneDgrY.setEndPos(min(zoneDgrY.getPos() + YSize, zonexyAllOperationTable.getY().getEndPos()));
				}
				else if (zoneDgrY.getEndPos() > zonexyAllOperationTable.getY().getEndPos())
				{
					zoneDgrY.setEndPos(zonexyAllOperationTable.getY().getEndPos());
				}
				CdDcdZone	zoneDcdY =
					YDgrToDcd(pTargetClip, zoneDgrY);
				//CdDcdZone	zoneDcdY(zonexyAllOperationTable.getY().getPos() * getDcdPerDgrY() + pTargetClip->getZone().getY().getPos(),
				//	zonexyAllOperationTable.getY().getSize() * getDcdPerDgrY());
				if (aCDcdFreeLine.getCdLineProp().getLogicalunitWidth() > 1)
				{
					zoneDcdY.setSize(zoneDcdY.getSize() - (aCDcdFreeLine.getCdLineProp().getLogicalunitWidth() - 1));
				}
				if (pTargetClip->getZone().getX().getPos() - 1 <= posDcdX &&
					posDcdX < pTargetClip->getZone().getX().getEndPos() + 1)
				{
					//罫線の上下が、表示領域外に出ている場合は、表示領域の外1ピクセルまで、線の描写範囲を縮める。
					if (pTargetClip->getZone().getY().getPos() > zoneDcdY.getPos())
					{
						//zoneDcdY.setPos(pTargetClip->getZone().getY().getPos() - 1);
						zoneDcdY.setBeginEndPos(pTargetClip->getZone().getY().getPos() - 1, zoneDcdY.getEndPos());
					}
					if (pTargetClip->getZone().getY().getEndPos() < zoneDcdY.getEndPos())
					{
						zoneDcdY.setEndPos(pTargetClip->getZone().getY().getEndPos() + 1);
					}
					aCDcdFreeLine.setOrg(CdDcdPosXy(
						posDcdX,
						zoneDcdY.getPos()));
					aCDcdFreeLine.setDst(CdDcdPosXy(
						posDcdX,
						zoneDcdY.getEndPos()));
#pragma omp critical
					aCDcdFreeLine.DcDraw(pTargetClip);

					bRv = true;
				}
			}
		}
		// --------------------------------
		//	横罫線を描画します。
		// --------------------------------
//#pragma omp section
		{
			int iOperationCount = getOperationNumber()->size();
			DcdSize iOneOperationSize = DEFAULT_YSIZE_PER_ONEOPERATION();
			//DcdSize iOneOperationSize = m_YOperationZone->getSize();
//#pragma omp parallel for schedule(guided)
			for (int iOperationIndex = 1;
				iOperationIndex <= iOperationCount;
				iOperationIndex++)
			{
				DcdPos posDgrY = iOneOperationSize * iOperationIndex;

				if (getClippingCount() <= 0|| (posDgrY >= zonexyZone_Dgr.getY().getPos() && posDgrY <= zonexyZone_Dgr.getY().getEndPos()))
				{
					CDcdFreeLine	aCDcdFreeLine;
					aCDcdFreeLine.setCdLineProp(linepropGridNormal);

					//	座標を、Dgr→Dcdに変換
					//DcdPos	posDcdY = /*posDcdYOffset +*/ (posDgrY * getDcdPerDgrY() + pTargetClip->getZone().getY().getPos());
					DcdPos	posDcdY = YDgrToDcd(pTargetClip, posDgrY);
					posDcdY -= linepropGridNormal.getLogicalunitWidth();
					CdDcdZone	zoneDcdX =
						XDgrToDcd(pTargetClip, zonexyAllOperationTable.getX());
					if (pTargetClip->getZone().getY().getPos() - 1 <= posDcdY &&
						posDcdY < pTargetClip->getZone().getY().getEndPos() + 1)
					{
						//罫線の左右が、表示領域外に出ている場合は、表示領域の外1ピクセルまで、線の描写範囲を縮める。
						if (pTargetClip->getZone().getX().getPos() > zoneDcdX.getPos())
						{
							//zoneDcdX.setPos(pTargetClip->getZone().getX().getPos() - 1);
							zoneDcdX.setBeginEndPos(pTargetClip->getZone().getX().getPos() - 1, zoneDcdX.getEndPos());
						}
						if (pTargetClip->getZone().getX().getEndPos() < zoneDcdX.getEndPos())
						{
							zoneDcdX.setEndPos(pTargetClip->getZone().getX().getEndPos() + 1);
						}
						aCDcdFreeLine.setOrg(CdDcdPosXy(
							zoneDcdX.getPos(),
							posDcdY));
						aCDcdFreeLine.setDst(CdDcdPosXy(
							zoneDcdX.getEndPos() + DIAGRAM_SIZE_MARGIN_DCD,
							posDcdY));
#pragma omp critical
						aCDcdFreeLine.DcDraw(pTargetClip);
					}
				}
			}
		}
	}
	//列車表示

	int iOperationCount = getOperationNumber()->size();
	DcdSize iOneOperationSize = DEFAULT_YSIZE_PER_ONEOPERATION();
	CdDedJikoku KitenJikoku = getCDiagramEditDoc()->
		getCDedRosenFileData()->getCentDedRosen()->getKitenJikoku();
	int SecondOfKitenJikoku = KitenJikoku.getTotalSeconds();

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
	const CentDedRessyasyubetsuCont* pCentDedRessyasyubetsuCont =
		getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedRessyasyubetsuCont();

	unordered_map<tstring, list<OperationTableContent>> contOperationTableContent =
		pCentDedDia->getcontOperationTableContent();
	const CentDedEkiCont* pCentDedEkiCont = getCDiagramEditDoc()->getCDedRosenFileData()->getCentDedRosen()->getCentDedEkiCont();
	const Mu<CentDedEkiCont::CdDedEki>* pCdDedEkiConts[2];
	for (int iRessyahoukou = Ressyahoukou_Kudari;
		iRessyahoukou <= Ressyahoukou_Nobori; iRessyahoukou++)
	{
		pCdDedEkiConts[iRessyahoukou] =
			pCentDedEkiCont->getMuPtr((ERessyahoukou)iRessyahoukou);
	}


	DcdPos posDgrY = iOneOperationSize / 2;
	DcdPos posClipping = zonexyZone_Dgr.getY().getEndPos() - zonexyZone_Dgr.getY().getEndPos() % DEFAULT_YSIZE_PER_ONEOPERATION();
	for (int iOperationIndex = 0;
		iOperationIndex < iOperationCount;
		iOperationIndex++, posDgrY += iOneOperationSize)
	{
		if (getClippingCount() > 0&& posDgrY >= posClipping)
		{
			break;
		}
		bool bCompleteSihatsuEkimeiDisplay = false;
		bool bCompleteSihatsuMinuteDisplay = false;
		const list<OperationTableContent>& ListOperationTableContent = contOperationTableContent[getOperationNumber()->at(iOperationIndex)];
		CdDedJikoku SyuuchakuJikokuPrev;
		CdDedJikoku OutJikoku;
		bool bClassPropertyChange = false;
		for (auto itr = ListOperationTableContent.begin(); itr != ListOperationTableContent.end(); itr++)
		{
			const CentDedRessya* pCentDedRessya =
				pCentDedRessyaConts[itr->aRessyaProperty.getRessyahoukou()]
				->get(itr->aRessyaProperty.getRessyaIndex());

			const CentDedRessyasyubetsu* pCentDedRessyasyubetsu = pCentDedRessyasyubetsuCont
				->getMuPtr()->get(pCentDedRessya->getRessyasyubetsuIndex());
			if (m_bDisplayParentSyubetsu && pCentDedRessyasyubetsu->getParentSyubetsuIndex() >= 0)
			{
				pCentDedRessyasyubetsu = pCentDedRessyasyubetsuCont
					->getMuPtr()->get(pCentDedRessyasyubetsu->getParentSyubetsuIndex());
			}

			tstring strSihatsuEkimei;
			CdDedJikoku SihatsuJikoku;
			int SecondOfSihatsuJikoku;
			if (itr->iOuterShihatsuekiIndex != INT_MIN)
			{
				int iOuterTerminalIndex = itr->iOuterShihatsuekiIndex;
				strSihatsuEkimei = pCdDedEkiConts[itr->aRessyaProperty.getRessyahoukou()]
					->get(itr->iSihatsuEkiOrder).getOuterTerminalDiaRyaku(iOuterTerminalIndex, true);
				SihatsuJikoku = itr->OuterShihatsuJikoku;
				SecondOfSihatsuJikoku = SihatsuJikoku.getTotalSeconds();
			}
			else
			{
				int iSihatsuEkiOrder = itr->iSihatsuEkiOrder;
				if (!pCentDedRessya->isRunBetweenNextEki(iSihatsuEkiOrder))
				{
					iSihatsuEkiOrder = pCentDedRessya->getRunBetweenEkiForward(iSihatsuEkiOrder);
				}

				strSihatsuEkimei = pCdDedEkiConts[itr->aRessyaProperty.getRessyahoukou()]
					->get(iSihatsuEkiOrder).getEkimeiDiagramRyaku(true);
				/**
					種別変更・列車情報変更の場合は、前列車の終点時刻を線の始点にします。
				*/
				if (bClassPropertyChange)
				{
					SihatsuJikoku = SyuuchakuJikokuPrev;
				}
				else
				{
					SihatsuJikoku = pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getHatsujikoku();
				}
				SecondOfSihatsuJikoku = SihatsuJikoku.getTotalSeconds();
			}
			if (SecondOfSihatsuJikoku < SecondOfKitenJikoku)
			{
				SecondOfSihatsuJikoku += CdDedJikoku::TOTALSECONDS_A_DAY;
			}

			/**
				SyuuchakuJikokuPrev
				運用の一列車目の場合は、OutJikokuとTempJikokuに始発時刻を代入して終了
				二列車目以降の場合、TempJikokuには前列車の終着時刻が入っているので、
				TempJikokuからOutJikokuの間に、始発時刻があるか否かを確認。
				間にある場合はTempJikokuに始発時刻を代入して描写へ、
				無い場合、ここで終了とする。
			*/
			if (SyuuchakuJikokuPrev.isNull())
			{
				OutJikoku = SihatsuJikoku;
				//SyuuchakuJikokuPrev = SihatsuJikoku;
			}
			else if(SihatsuJikoku.compare(SyuuchakuJikokuPrev, OutJikoku)<0)
			{
			//	SyuuchakuJikokuPrev = SihatsuJikoku;
			//}
			//else 
			//{
				break;
			}


			tstring strSyuuchakuEkimei;
			CdDedJikoku SyuuchakuJikoku;
			int SecondOfSyuuchakuJikoku;
			if (itr->iOuterShuchakuekiIndex != INT_MIN)
			{
				int iOuterTerminalIndex = itr->iOuterShuchakuekiIndex;
				strSyuuchakuEkimei = pCdDedEkiConts[itr->aRessyaProperty.getRessyahoukou()]
					->get(itr->iSyuuchakuEkiOrder).getOuterTerminalDiaRyaku(iOuterTerminalIndex, true);
				SyuuchakuJikoku = itr->OuterShuchakuJikoku;
				SecondOfSyuuchakuJikoku = SyuuchakuJikoku.getTotalSeconds();
			}
			else if (itr->eAfterType == EBeforeAfterType::BeforeAfterType_PropertySame)
			{
				//int iSihatsuEkiIndex = pCentDedRessya->EkiIndexOfEkiOrder(itr->iSihatsuEkiOrder);

				//int iSyuuchakuEkiIndex = pCentDedRessya->EkiIndexOfEkiOrder(itr->iSyuuchakuEkiOrder);
				auto itrNext = itr;
				do {
					itrNext++;
					if (itrNext == ListOperationTableContent.end() ||
						itrNext->eBeforeType != EBeforeAfterType::BeforeAfterType_PropertySame)
					{
						//次の列車が末尾を超えた場合、もしくは
						//次の列車の前タイプが同一列車扱い以外なら、一体化は無効その前の列車で終了します。
						break;
					}
					else/* if (itrNext->eBeforeType == EBeforeAfterType::BeforeAfterType_PropertySame)*/
					{
						//次の列車の前タイプが同一列車扱いの場合、通常時および箱ダイヤで列車方向一致、終着→始発が駅順の場合は、次の列車は一体化が確定する。

						itr++;


						if (itrNext->iOuterShuchakuekiIndex != INT_MIN)
						{
							int iOuterTerminalIndex = itrNext->iOuterShuchakuekiIndex;
							strSyuuchakuEkimei = pCdDedEkiConts[itrNext->aRessyaProperty.getRessyahoukou()]
								->get(itrNext->iSyuuchakuEkiOrder).getOuterTerminalDiaRyaku(iOuterTerminalIndex, true);
							SyuuchakuJikoku = itrNext->OuterShuchakuJikoku;
							SecondOfSyuuchakuJikoku = SyuuchakuJikoku.getTotalSeconds();
						}
						else
						{
							const CentDedRessya* pCentDedRessyaNext =
								pCentDedRessyaConts[itrNext->aRessyaProperty.getRessyahoukou()]
								->get(itrNext->aRessyaProperty.getRessyaIndex());

							int iSyuuchakuEkiOrder = itrNext->iSyuuchakuEkiOrder;
							if (!pCentDedRessyaNext->isRunBetweenNextEki(iSyuuchakuEkiOrder - 1))
							{
								iSyuuchakuEkiOrder = pCentDedRessyaNext->getRunBetweenEkiBackward(iSyuuchakuEkiOrder);
							}

							strSyuuchakuEkimei = pCdDedEkiConts[itrNext->aRessyaProperty.getRessyahoukou()]
								->get(iSyuuchakuEkiOrder).getEkimeiDiagramRyaku(true);
							SyuuchakuJikoku = pCentDedRessyaNext->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getChakujikoku();
							SecondOfSyuuchakuJikoku = SyuuchakuJikoku.getTotalSeconds();
						}

						if (itrNext->eAfterType == EBeforeAfterType::BeforeAfterType_PropertySame)
						{
							//次の列車の後タイプが同一列車扱いなら、さらに次の列車の検索を行う。
							continue;
						}
						else
						{
							//次の列車の後タイプが同一列車扱い以外なら、この列車が一体化の末尾となる
							break;
						}
					}
				} while (itrNext != ListOperationTableContent.end());

			}
			else
			{
				int iSyuuchakuEkiOrder = itr->iSyuuchakuEkiOrder;
				if (!pCentDedRessya->isRunBetweenNextEki(iSyuuchakuEkiOrder - 1))
				{
					iSyuuchakuEkiOrder = pCentDedRessya->getRunBetweenEkiBackward(iSyuuchakuEkiOrder);
				}

				strSyuuchakuEkimei = pCdDedEkiConts[itr->aRessyaProperty.getRessyahoukou()]
					->get(iSyuuchakuEkiOrder).getEkimeiDiagramRyaku(true);
				SyuuchakuJikoku = pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getChakujikoku();
				SecondOfSyuuchakuJikoku = SyuuchakuJikoku.getTotalSeconds();
			}
			if (SecondOfSyuuchakuJikoku < SecondOfKitenJikoku)
			{
				SecondOfSyuuchakuJikoku += CdDedJikoku::TOTALSECONDS_A_DAY;
			}
			SyuuchakuJikokuPrev = SyuuchakuJikoku;
			/**
				この時点で、始発時刻は有効範囲(出区から丸一日経過していない)にあることは確実。
				まず、終着時刻が有効範囲にあるかのチェックと
				始発時刻と終着時刻の間に起点時刻があるかを確認(始発時刻および終着時刻が起点時刻の場合は除く)
				起点時刻を挟んでいる場合は、線を二分割して描写する必要がある。
			*/
			bool bLineSplit = false;
			if (OutJikoku == SihatsuJikoku ||
				SyuuchakuJikoku.compare(OutJikoku, SihatsuJikoku) < 0)
			{
				if (KitenJikoku.compare(SihatsuJikoku, SyuuchakuJikoku) > 0)
				{
					bLineSplit = true;
				}
				else if (KitenJikoku == SyuuchakuJikoku)
				{
					SecondOfSyuuchakuJikoku += CdDedJikoku::TOTALSECONDS_A_DAY;
				}
			}
			else
			{
				break;
			}


			//始発駅名を表示する、ただし、前列車の段階で、終着・始発駅名をまとめて表示した場合は省略
			if (!bCompleteSihatsuEkimeiDisplay)
			{
				CDcdText textSihatsuEkimei(strSihatsuEkimei,
					CdDrawTextProp(getOperationTableFont(), getStringColor()),
					strSihatsuEkimei);
				CdDcdSizeXy	sizeSihatsuEkimei;
				textSihatsuEkimei.getItemSize(pIfDcdTarget, &sizeSihatsuEkimei);


				//	座標を、Dgr→Dcdに変換
				DcdPos posDcdX = XDgrToDcd(pIfDcdTarget, SecondOfSihatsuJikoku);
				DcdPos posDcdY = YDgrToDcd(pIfDcdTarget, posDgrY) + linepropDiaJikuBold.getLogicalunitWidth();

				{
					CdDcdZoneXy	zonexyDcdZoneXy(
						CdDcdZone(posDcdX - (sizeSihatsuEkimei.getX() / 2), sizeSihatsuEkimei.getX()),
						CdDcdZone(posDcdY, sizeSihatsuEkimei.getY()));
					CaDcdTargetItemPosition	aTarget(pIfDcdTarget, zonexyDcdZoneXy);
					if (aTarget.isDrawable())
					{
						textSihatsuEkimei.DcDraw(&aTarget);
						bRv = true;
					}
				}
			}
			//始発駅時刻を表示する、ただし、前列車の段階で、終着・始発駅時刻をまとめて表示した場合は省略、
			//また、種別変更・列車情報変更の場合も省略
			if (!bCompleteSihatsuMinuteDisplay && getDisplayJikokuMinute() && !bClassPropertyChange)
			{
				tstring strTemp = strprintf(_T("%02d"), SihatsuJikoku.getMinute());
				CDcdText textSihatsuMinute(strTemp,
					CdDrawTextProp(getAllOperationTableJikokuFont(), getStringColor()),
					strTemp);
				CdDcdSizeXy	sizeSihatsuMinute;
				textSihatsuMinute.getItemSize(pIfDcdTarget, &sizeSihatsuMinute);


				//	座標を、Dgr→Dcdに変換
				DcdPos posDcdX = XDgrToDcd(pIfDcdTarget, SecondOfSihatsuJikoku);
				DcdPos posDcdY = YDgrToDcd(pIfDcdTarget, posDgrY);

				CdDcdZoneXy	zonexyDcdZoneXy(
					CdDcdZone(posDcdX - (sizeSihatsuMinute.getX() / 2), sizeSihatsuMinute.getX()),
					CdDcdZone(posDcdY - sizeSihatsuMinute.getY() - 1, sizeSihatsuMinute.getY()));

				CaDcdTargetItemPosition	aTarget(pIfDcdTarget, zonexyDcdZoneXy);
				if (aTarget.isDrawable())
				{
					textSihatsuMinute.DcDraw(&aTarget);
					bRv = true;
				}
			}



			// --------------------------------
			//	直線の形状を決定
			// --------------------------------
			CdDcdFreeLineProp	aCdLineProp;
			{
				CentDedRessyasyubetsu::CdDiagramLineStyle	aCdDiagramLineStyle =
					pCentDedRessyasyubetsu->getCdDiagramLineStyle();

				CconvCentDed aCconvCentDed;
				aCconvCentDed.CentDedRessyasyubetsu_to_CDcdFreeLineProp(
					aCdDiagramLineStyle,
					&aCdLineProp);
			}
			aCdLineProp.setLogicalunitWidth(aCdLineProp.getLogicalunitWidth() +1);


			// --------------------------------
			//	直線の描画位置を決定
			// --------------------------------
			CDcdFreeLine	aCDcdFreeLine(aCdLineProp);
			if (bLineSplit)
			{
				aCDcdFreeLine.setOrg(DgrToDcd(pTargetClip, CdDcdPosXy(SecondOfSihatsuJikoku, posDgrY)));
				aCDcdFreeLine.setDst(DgrToDcd(pTargetClip, CdDcdPosXy(SecondOfKitenJikoku + CdDedJikoku::TOTALSECONDS_A_DAY, posDgrY)));
#pragma omp critical
				{
					aCDcdFreeLine.DcDraw(pTargetClip);
				}
				aCDcdFreeLine.setOrg(DgrToDcd(pTargetClip, CdDcdPosXy(SecondOfKitenJikoku , posDgrY)));
				aCDcdFreeLine.setDst(DgrToDcd(pTargetClip, CdDcdPosXy(SecondOfSyuuchakuJikoku, posDgrY)));
#pragma omp critical
				{
					aCDcdFreeLine.DcDraw(pTargetClip);
				}

			}
			else
			{
				aCDcdFreeLine.setOrg(DgrToDcd(pTargetClip, CdDcdPosXy(SecondOfSihatsuJikoku, posDgrY)));
				aCDcdFreeLine.setDst(DgrToDcd(pTargetClip, CdDcdPosXy(SecondOfSyuuchakuJikoku, posDgrY)));
#pragma omp critical
				{
					aCDcdFreeLine.DcDraw(pTargetClip);
				}
			}


			//列車番号表示
			tstring strRessyaInformation;
			if (getDisplayRessyabangou() && !pCentDedRessya->getRessyabangou().empty())
			{
				strRessyaInformation += pCentDedRessya->getRessyabangou();
			}
			if (getDisplaySyubetsuRyakusyou() && !pCentDedRessyasyubetsu->getRyakusyou().empty())
			{
				if (!strRessyaInformation.empty())
				{
					strRessyaInformation += _T(" ");
				}
				strRessyaInformation += pCentDedRessyasyubetsu->getRyakusyou();
			}
			if (getDisplayRessyamei())
			{
				if (!pCentDedRessya->getRessyamei().empty())
				{
					if (!strRessyaInformation.empty())
					{
						strRessyaInformation += _T(" ");
					}
					strRessyaInformation += pCentDedRessya->getRessyamei();
				}
				if (!pCentDedRessya->getGousuu().empty())
				{
					if (!strRessyaInformation.empty())
					{
						strRessyaInformation += _T(" ");
					}
					strRessyaInformation += pCentDedRessya->getGousuu();
					strRessyaInformation += _T("号");
				}
			}
			if(!strRessyaInformation.empty())
			{

				if (bLineSplit)
				{
					CDcdText textRessyaInformation(strRessyaInformation,
						CdDrawTextProp(getOperationTableFont(), getStringColor()),
						strRessyaInformation);
					CdDcdSizeXy	sizeRessyaInformation;
					textRessyaInformation.getItemSize(pIfDcdTarget, &sizeRessyaInformation);


					DcdPos posDcdX = XDgrToDcd(pIfDcdTarget, (SecondOfSihatsuJikoku + SecondOfKitenJikoku + CdDedJikoku::TOTALSECONDS_A_DAY) / 2);
					DcdPos posDcdY = YDgrToDcd(pIfDcdTarget, posDgrY);

					CdDcdZoneXy	zonexyDcdZoneXy(
						CdDcdZone(posDcdX - (sizeRessyaInformation.getX() / 2), sizeRessyaInformation.getX()),
						CdDcdZone(posDcdY - sizeRessyaInformation.getY() - 1, sizeRessyaInformation.getY()));
					CaDcdTargetItemPosition	aTarget(pIfDcdTarget, zonexyDcdZoneXy);
					if (aTarget.isDrawable())
					{
						textRessyaInformation.DcDraw(&aTarget);
						bRv = true;
					}

					posDcdX = XDgrToDcd(pIfDcdTarget, (SecondOfKitenJikoku + SecondOfSyuuchakuJikoku) / 2);

					zonexyDcdZoneXy = CdDcdZoneXy(
						CdDcdZone(posDcdX - (sizeRessyaInformation.getX() / 2), sizeRessyaInformation.getX()),
						CdDcdZone(posDcdY - sizeRessyaInformation.getY() - 1, sizeRessyaInformation.getY()));
					aTarget = CaDcdTargetItemPosition(pIfDcdTarget, zonexyDcdZoneXy);
					if (aTarget.isDrawable())
					{
						textRessyaInformation.DcDraw(&aTarget);
						bRv = true;
					}
				}
				else
				{
					CDcdText textRessyaInformation(strRessyaInformation,
						CdDrawTextProp(getOperationTableFont(), getStringColor()),
						strRessyaInformation);
					CdDcdSizeXy	sizeRessyaInformation;
					textRessyaInformation.getItemSize(pIfDcdTarget, &sizeRessyaInformation);


					DcdPos posDcdX = XDgrToDcd(pIfDcdTarget, (SecondOfSihatsuJikoku + SecondOfSyuuchakuJikoku) / 2);
					DcdPos posDcdY = YDgrToDcd(pIfDcdTarget, posDgrY);

					CdDcdZoneXy	zonexyDcdZoneXy(
						CdDcdZone(posDcdX - (sizeRessyaInformation.getX() / 2), sizeRessyaInformation.getX()),
						CdDcdZone(posDcdY - sizeRessyaInformation.getY() - 1, sizeRessyaInformation.getY()));
					CaDcdTargetItemPosition	aTarget(pIfDcdTarget, zonexyDcdZoneXy);
					if (aTarget.isDrawable())
					{
						textRessyaInformation.DcDraw(&aTarget);
						bRv = true;
					}
				}
			}



			//終着駅名表示
			{
				CDcdText textSyuuchakuEkimei(strSyuuchakuEkimei,
					CdDrawTextProp(getOperationTableFont(), getStringColor()),
					strSyuuchakuEkimei);
				CdDcdSizeXy	sizeSyuuchakuEkimei;
				textSyuuchakuEkimei.getItemSize(pIfDcdTarget, &sizeSyuuchakuEkimei);


				//	座標を、Dgr→Dcdに変換
				DcdPos posDcdX = XDgrToDcd(pIfDcdTarget, SecondOfSyuuchakuJikoku);
				DcdPos posDcdY = YDgrToDcd(pIfDcdTarget, posDgrY) + linepropDiaJikuBold.getLogicalunitWidth();

				//この列車が運用最後の列車ではない場合、次列車を読み込み、以下の判定を行います
				//(1)次列車の始発駅とこの列車の終着駅が同じか否か、異なる場合は、両方を表示する
				//(2)同じ場合、それぞれの表示位置を計算し、その間隔が文字列サイズ二つ分より小さい場合は、一つにまとめて表示する。
				//(3)違う場合もそれぞれの表示位置を計算し、その間隔が文字列サイズの半分より小さい場合は、
				//	間隔を文字列サイズの半分確保するように調整する。

				//Ver2.05 次列車接続タイプが種別変更・列車情報変更の場合は、次列車の線の始点を終着駅時刻まで延ばす。
				//駅名は常に一つのみとなる。時刻は表示しない。
				//同一列車扱いの場合は、駅名時刻共に表示せず、次列車の線の始点を終着駅時刻まで延ばす。
				//

				bClassPropertyChange = false;
				auto itrNext = itr;
				itrNext++;
				if (itrNext != ListOperationTableContent.end())
				{
					const CentDedRessya* pCentDedRessyaNext =
						pCentDedRessyaConts[itrNext->aRessyaProperty.getRessyahoukou()]
						->get(itrNext->aRessyaProperty.getRessyaIndex());

					if ((itr->eAfterType == EBeforeAfterType::BeforeAfterType_ClassChange &&
						itrNext->eBeforeType == EBeforeAfterType::BeforeAfterType_ClassChange) ||
						(itr->eAfterType == EBeforeAfterType::BeforeAfterType_PropertyChange &&
							itrNext->eBeforeType == EBeforeAfterType::BeforeAfterType_PropertyChange))
					{
						bClassPropertyChange = true;
					}
					//else if (itr->eAfterType == EBeforeAfterType::BeforeAfterType_PropertySame &&
					//	itrNext->eBeforeType == EBeforeAfterType::BeforeAfterType_PropertySame)
					//{
					//	bClassPropertyChange = 2;
					//}

					tstring strSihatsuEkimeiNext;
					CdDedJikoku SihatsuJikokuNext;
					int SecondOfSihatsuJikokuNext;
					if (itrNext->iOuterShihatsuekiIndex != INT_MIN)
					{
						int iOuterTerminalIndex = itrNext->iOuterShihatsuekiIndex;
						strSihatsuEkimeiNext = pCdDedEkiConts[itrNext->aRessyaProperty.getRessyahoukou()]
							->get(itrNext->iSihatsuEkiOrder).getOuterTerminalDiaRyaku(iOuterTerminalIndex, true);
						SihatsuJikokuNext = itrNext->OuterShihatsuJikoku;
						SecondOfSihatsuJikokuNext = SihatsuJikokuNext.getTotalSeconds();
					}
					else if (bClassPropertyChange)
					{
						//種別変更・列車情報変更の場合、次列車の始発駅時刻は、この列車の終着駅時刻とみなします。
						strSihatsuEkimeiNext = strSyuuchakuEkimei;
						SihatsuJikokuNext = SyuuchakuJikoku;
						SecondOfSihatsuJikokuNext = SihatsuJikokuNext.getTotalSeconds();
					}
					else
					{
						int iSihatsuEkiOrderNext = itrNext->iSihatsuEkiOrder;
						if (!pCentDedRessyaNext->isRunBetweenNextEki(iSihatsuEkiOrderNext))
						{
							iSihatsuEkiOrderNext = pCentDedRessyaNext->getRunBetweenEkiForward(iSihatsuEkiOrderNext);
						}

						strSihatsuEkimeiNext = pCdDedEkiConts[itrNext->aRessyaProperty.getRessyahoukou()]
							->get(iSihatsuEkiOrderNext).getEkimeiDiagramRyaku(true);
						SihatsuJikokuNext = pCentDedRessyaNext->getCentDedEkiJikoku(iSihatsuEkiOrderNext).getHatsujikoku();
						SecondOfSihatsuJikokuNext = SihatsuJikokuNext.getTotalSeconds();
					}
					if (SecondOfSihatsuJikokuNext < SecondOfKitenJikoku)
					{
						SecondOfSihatsuJikokuNext += CdDedJikoku::TOTALSECONDS_A_DAY;
					}

					/**
						次列車始発時刻が終着時刻から出区時刻の間にあるか否かをまず確認。
						無い場合は終着駅名＆時刻を単独表記して終了
						ある場合は、終着時刻と次列車始発時刻の間に起点時刻があるかを確認。
						無い場合は、必要に応じて駅名表示の併合を行い、ある場合は駅名＆時刻は個々の表記となる
					*/

					if (SihatsuJikokuNext.compare(SyuuchakuJikoku, OutJikoku) >= 0)
					{
						if (SihatsuJikokuNext.compare(KitenJikoku, SyuuchakuJikoku) >= 0)
						{
							//終着時刻と次列車始発時刻の間に起点時刻があるので、次列車描写は別個実施。単独で駅名・時刻描写を行う。
							bCompleteSihatsuEkimeiDisplay = false;
							bCompleteSihatsuMinuteDisplay = false;
						}
						else
						{
							//まず、次列車の終着時刻を取得する
							CdDedJikoku SyuuchakuJikokuNext;
							//int SecondOfSyuuchakuJikokuNext;
							if (itrNext->iOuterShuchakuekiIndex != INT_MIN)
							{
								int iOuterTerminalIndex = itrNext->iOuterShuchakuekiIndex;
								SyuuchakuJikokuNext = itrNext->OuterShuchakuJikoku;
							}
							else
							{
								int iSyuuchakuEkiOrderNext = itrNext->iSyuuchakuEkiOrder;
								if (!pCentDedRessyaNext->isRunBetweenNextEki(iSyuuchakuEkiOrderNext - 1))
								{
									iSyuuchakuEkiOrderNext = pCentDedRessyaNext->getRunBetweenEkiBackward(iSyuuchakuEkiOrderNext);
								}

								SyuuchakuJikokuNext = pCentDedRessyaNext->getCentDedEkiJikoku(iSyuuchakuEkiOrderNext).getChakujikoku();
							}
							/**
								次列車終着時刻が、次列車始発時刻と出区時刻の間にあるかどうかを調べる
								ある場合は、必要に応じて駅名表示の併合を行い、無い場合は次列車の描写自体が無くなる
							*/
							if (SyuuchakuJikokuNext.compare(SihatsuJikokuNext, OutJikoku) >= 0)
							{
								//ここにたどり着く条件
								//(1)終着時刻の後、出区時刻の前までに、次列車が収まっている
								//(2)終着時刻と次列車始発時刻の間に、起点時刻がない


								DcdPos posDcdX_Next = XDgrToDcd(pIfDcdTarget, SecondOfSihatsuJikokuNext);
								int iSyuuchakuEkiIndex = pCentDedEkiCont->EkiIndexOfEkiOrder(
									itr->aRessyaProperty.getRessyahoukou(), itr->iSyuuchakuEkiOrder);
								int iSihatsuEkiIndex = pCentDedEkiCont->EkiIndexOfEkiOrder(
									itrNext->aRessyaProperty.getRessyahoukou(), itrNext->iSihatsuEkiOrder);
								if (pCentDedEkiCont->isSameBrunchLoopGroup(iSyuuchakuEkiIndex, iSihatsuEkiIndex) &&
									itr->iOuterShuchakuekiIndex == itrNext->iOuterShihatsuekiIndex)
								{
									//終着駅と始発駅が同一で、路線外発着も一致した場合(どちらも路線外発着でない場合含む)
									//二つの駅名表示を統合するが、間隔が文字列一つ分よりも広い場合は別個表示する

									//posDcdXとposDcdX_Nextは、線の起終点位置を表しているので、文字列の中間位置に相当する
									//なので、文字列同士の間隔が文字列一つ分＝posDcdXとposDcdX_Nextの間隔が文字列二つ分となる
									if (posDcdX + (sizeSyuuchakuEkimei.getX() * 3) > posDcdX_Next)
									{
										CdDcdZoneXy	zonexyDcdZoneXy(
											CdDcdZone((posDcdX + posDcdX_Next) / 2 - (sizeSyuuchakuEkimei.getX() / 2), sizeSyuuchakuEkimei.getX()),
											CdDcdZone(posDcdY, sizeSyuuchakuEkimei.getY()));

										CaDcdTargetItemPosition	aTarget(pIfDcdTarget, zonexyDcdZoneXy);
										if (aTarget.isDrawable())
										{
											textSyuuchakuEkimei.DcDraw(&aTarget);
											bRv = true;
										}
										//終着駅名と次列車始発駅名を併合して表示完了
										bCompleteSihatsuEkimeiDisplay = true;
									}
									else
									{
										//終着駅名と次列車始発駅名が離れているので、次列車描写は別個実施。単独で駅名描写を行う。
										bCompleteSihatsuEkimeiDisplay = false;
									}
								}
								else
								{
									//終着駅と次列車始発駅が異なる場合

									CDcdText textSihatsuEkimeiNext(strSihatsuEkimeiNext,
										CdDrawTextProp(getOperationTableFont(), getStringColor()),
										strSihatsuEkimeiNext);
									CdDcdSizeXy	sizeSihatsuEkimeiNext;
									textSihatsuEkimeiNext.getItemSize(pIfDcdTarget, &sizeSihatsuEkimeiNext);

									//posDcdXとposDcdX_Nextは、線の起終点位置を表しているので、文字列の中間位置に相当する
									//posDcdX + sizeSyuuchakuEkimei.getX() は、終着駅名の右端からさらに文字列半分右の位置を、
									//posDcdX_Next - (sizeSihatsuEkimeiNext.getX() /2) は、始発駅名の左端位置を示す
									if (posDcdX + sizeSyuuchakuEkimei.getX() > posDcdX_Next - (sizeSihatsuEkimeiNext.getX() / 2))
									{
										//二つの差分を求め、その半分が補正値になる
										DcdSize SizeCorrection = ((posDcdX + sizeSyuuchakuEkimei.getX()) - (posDcdX_Next - (sizeSihatsuEkimeiNext.getX() / 2))) / 2;
										
										CdDcdZoneXy	zonexyDcdZoneXySyuuchaku(
											CdDcdZone(posDcdX - (sizeSyuuchakuEkimei.getX() / 2) - SizeCorrection, sizeSyuuchakuEkimei.getX()),
											CdDcdZone(posDcdY, sizeSyuuchakuEkimei.getY()));

										CaDcdTargetItemPosition	aTargetSyuuchaku(pIfDcdTarget, zonexyDcdZoneXySyuuchaku);
										if (aTargetSyuuchaku.isDrawable())
										{
											textSyuuchakuEkimei.DcDraw(&aTargetSyuuchaku);
											bRv = true;
										}

										CdDcdZoneXy	zonexyDcdZoneXySihatsu(
											CdDcdZone(posDcdX_Next - (sizeSihatsuEkimeiNext.getX() / 2) + SizeCorrection, sizeSihatsuEkimeiNext.getX()),
											CdDcdZone(posDcdY, sizeSihatsuEkimeiNext.getY()));

										CaDcdTargetItemPosition	aTargetSihatsu(pIfDcdTarget, zonexyDcdZoneXySihatsu);
										if (aTargetSihatsu.isDrawable())
										{
											textSihatsuEkimeiNext.DcDraw(&aTargetSihatsu);
											bRv = true;
										}
										//終着駅名と次列車始発駅名を間隔を調整した上で別個での表示完了
										bCompleteSihatsuEkimeiDisplay = true;
									}
									else
									{
										//終着駅名と次列車始発駅名が離れているので、次列車描写は別個実施。単独で駅名描写を行う。
										bCompleteSihatsuEkimeiDisplay = false;
									}

								}

								/**
									種別変更・列車情報変更の場合は時刻表示は行わない
								*/
								if (getDisplayJikokuMinute() &&
									!bClassPropertyChange)
								{
									tstring strTemp = strprintf(_T("%02d"), SyuuchakuJikoku.getMinute());
									CDcdText textSyuuchakuMinute(strTemp,
										CdDrawTextProp(getAllOperationTableJikokuFont(), getStringColor()),
										strTemp);
									CdDcdSizeXy	sizeSyuuchakuMinute;
									textSyuuchakuMinute.getItemSize(pIfDcdTarget, &sizeSyuuchakuMinute);

									tstring strTempNext = strprintf(_T("%02d"), SihatsuJikokuNext.getMinute());
									CDcdText textSihatsuMinuteNext(strTempNext,
										CdDrawTextProp(getAllOperationTableJikokuFont(), getStringColor()),
										strTempNext);
									CdDcdSizeXy	sizeSihatsuMinuteNext;
									textSihatsuMinuteNext.getItemSize(pIfDcdTarget, &sizeSihatsuMinuteNext);


									//	座標を、Dgr→Dcdに変換
									DcdPos posDcdX_Next = XDgrToDcd(pIfDcdTarget, SecondOfSihatsuJikokuNext);
									DcdPos posDcdYJikoku = YDgrToDcd(pIfDcdTarget, posDgrY);

									if (posDcdX + sizeSyuuchakuMinute.getX() > posDcdX_Next - (sizeSihatsuMinuteNext.getX() / 2))
									{
										//二つの差分を求め、その半分が補正値になる
										DcdSize SizeCorrection = ((posDcdX + sizeSyuuchakuMinute.getX()) - (posDcdX_Next - (sizeSihatsuMinuteNext.getX() / 2))) / 2;
										CdDcdZoneXy	zonexyDcdZoneXy(
											CdDcdZone(posDcdX - (sizeSyuuchakuMinute.getX() / 2) - SizeCorrection, sizeSyuuchakuMinute.getX()),
											CdDcdZone(posDcdYJikoku - sizeSyuuchakuMinute.getY() - 1, sizeSyuuchakuMinute.getY()));

										CaDcdTargetItemPosition	aTarget(pIfDcdTarget, zonexyDcdZoneXy);
										if (aTarget.isDrawable())
										{
											textSyuuchakuMinute.DcDraw(&aTarget);
											bRv = true;
										}

										CdDcdZoneXy	zonexyDcdZoneXyNext(
											CdDcdZone(posDcdX_Next - (sizeSihatsuMinuteNext.getX() / 2) + SizeCorrection, sizeSihatsuMinuteNext.getX()),
											CdDcdZone(posDcdYJikoku - sizeSihatsuMinuteNext.getY() - 1, sizeSihatsuMinuteNext.getY()));

										CaDcdTargetItemPosition	aTargetNext(pIfDcdTarget, zonexyDcdZoneXyNext);
										if (aTargetNext.isDrawable())
										{
											textSihatsuMinuteNext.DcDraw(&aTargetNext);
											bRv = true;
										}
										//終着時刻と次列車始発時刻を間隔を調整した上で別個での表示完了
										bCompleteSihatsuMinuteDisplay = true;
									}
									else
									{
										//終着時刻と次列車始発時刻が離れているので、次列車描写は別個実施。単独で駅名描写を行う。
										bCompleteSihatsuMinuteDisplay = false;
									}
								}
							}
							else
							{
								//次列車始発時刻と次列車終着時刻の間に出区時刻があるので、次列車描写は無し。単独で駅名・時刻描写を行う。
								bCompleteSihatsuEkimeiDisplay = false;
								bCompleteSihatsuMinuteDisplay = false;
							}
						}
					}

				}
				else
				{
					//この列車が入区列車なので、次列車描写は無し。単独で駅名・時刻描写を行う。
					bCompleteSihatsuEkimeiDisplay = false;
					bCompleteSihatsuMinuteDisplay = false;
				}
				
				//(次列車の)始発駅名表示が住んでいる場合は、終着駅名も済んでいるので、飛ばしてよい
				if(!bCompleteSihatsuEkimeiDisplay)
				{
					CdDcdZoneXy	zonexyDcdZoneXy(
						CdDcdZone(posDcdX - (sizeSyuuchakuEkimei.getX() / 2), sizeSyuuchakuEkimei.getX()),
						CdDcdZone(posDcdY, sizeSyuuchakuEkimei.getY()));
					CaDcdTargetItemPosition	aTarget(pIfDcdTarget, zonexyDcdZoneXy);
					if (aTarget.isDrawable())
					{
						textSyuuchakuEkimei.DcDraw(&aTarget);
						bRv = true;
					}
				}
				/**
					種別変更・列車情報変更の場合は時刻表示は行わない
				*/
				if (!bCompleteSihatsuMinuteDisplay && getDisplayJikokuMinute() && !bClassPropertyChange)
				{
					tstring strTemp = strprintf(_T("%02d"), SyuuchakuJikoku.getMinute());
					CDcdText textSyuuchakuMinute(strTemp,
						CdDrawTextProp(getAllOperationTableJikokuFont(), getStringColor()),
						strTemp);
					CdDcdSizeXy	sizeSyuuchakuMinute;
					textSyuuchakuMinute.getItemSize(pIfDcdTarget, &sizeSyuuchakuMinute);


					//	座標を、Dgr→Dcdに変換
					DcdPos posDcdYJikoku = YDgrToDcd(pIfDcdTarget, posDgrY);

					CdDcdZoneXy	zonexyDcdZoneXy(
						CdDcdZone(posDcdX - (sizeSyuuchakuMinute.getX() / 2), sizeSyuuchakuMinute.getX()),
						CdDcdZone(posDcdYJikoku - sizeSyuuchakuMinute.getY() - 1, sizeSyuuchakuMinute.getY()));

					CaDcdTargetItemPosition	aTarget(pIfDcdTarget, zonexyDcdZoneXy);
					if (aTarget.isDrawable())
					{
						textSyuuchakuMinute.DcDraw(&aTarget);
						bRv = true;
					}
				}

			}

		}
	}
	// --------------------------------
	if (pTargetClip != NULL)
	{
		delete pTargetClip;
		pTargetClip = NULL;
	}
	return (bRv);
}
bool CDcdAllOperationTable::getItemSize( IfDcdTarget* pIfDcdTarget , 
							CdDcdSizeXy* pCdDcdSizeXy ) 
{
	bool bRv = false ;
	*pCdDcdSizeXy = CdDcdSizeXy() ;
	return ( bRv ) ;
}
	
// ********************************
//	CdDedDispProp
// ********************************
	// ********************************
	//@name CDcdAllOperationTable-関連
	// ********************************
vector<tstring>* CDcdAllOperationTable::getOperationNumber()
{
	return m_strOperationNumber;
}
CDcdAllOperationTable& CDcdAllOperationTable::setOperationNumber(vector<tstring>* value)
{
	m_strOperationNumber = value;
	return *this;
}
CdDcdZoneXy* CDcdAllOperationTable::getCdDcdZone()
{
	return m_CdDcdZone;
}
CDcdAllOperationTable& CDcdAllOperationTable::setCdDcdZone(CdDcdZoneXy* value)
{
	m_CdDcdZone = value;
	m_CconvContentPosToDcdTarget.setContentPosAndRate(
		CdDcdPosXy(
			m_CdDcdZone->getX().getPos(),
			m_CdDcdZone->getY().getPos()),
		DEFAULT_DCD_PER_DGR_X(),
		DEFAULT_DCD_PER_DGR_Y(),
		NULL);
	return *this;
}
tstring CDcdAllOperationTable::getName()
{
	return m_strName;
}
CDcdAllOperationTable& CDcdAllOperationTable::setName(tstring value)
{
	m_strName = value;
	return *this;
}
;

	// ********************************
	//@name CDcdAllOperationTable-属性-CdDedDispProp から読み込み可能
	// ********************************
CdFontProp	CDcdAllOperationTable::getOperationTableFont()const {
	return 	m_fontpropOperationTableFont;
};
CDcdAllOperationTable& CDcdAllOperationTable::setOperationTableFont(const CdFontProp& value) {
	m_fontpropOperationTableFont = value; return *this;
};

CdFontProp	CDcdAllOperationTable::getAllOperationTableJikokuFont()const {
	return 	m_fontpropAllOperationTableJikokuFont;
};
CDcdAllOperationTable& CDcdAllOperationTable::setAllOperationTableJikokuFont(const CdFontProp& value) {
	m_fontpropAllOperationTableJikokuFont = value; return *this;
};

CdColorProp	CDcdAllOperationTable::getDiaJikuColor()const{
		return m_colorDiaJikuColor ;};
CDcdAllOperationTable& CDcdAllOperationTable::setDiaJikuColor( CdColorProp value ){
		m_colorDiaJikuColor = value ; return *this ;}

CdColorProp	CDcdAllOperationTable::getGridColor()const {
	return m_colorGridColor;
};
CDcdAllOperationTable& CDcdAllOperationTable::setGridColor(CdColorProp value) {
	m_colorGridColor = value; return *this;
}

CdColorProp	CDcdAllOperationTable::getStringColor()const {
	return m_colorStringColor;
};
CDcdAllOperationTable& CDcdAllOperationTable::setStringColor(CdColorProp value) {
	m_colorStringColor = value; return *this;
}

	// ********************************
	//@name CDcdAllOperationTable-属性-CdDedDispProp にはないもの
	// ********************************
bool	CDcdAllOperationTable::getDisplayRessyabangou()const{
		return m_bDisplayRessyabangou ;};
CDcdAllOperationTable& CDcdAllOperationTable::setDisplayRessyabangou( bool value ){
		m_bDisplayRessyabangou = value ; return *this ;};
bool	CDcdAllOperationTable::getDisplaySyubetsuRyakusyou()const {
	return m_bDisplaySyubetsuRyakusyou;
};
CDcdAllOperationTable& CDcdAllOperationTable::setDisplaySyubetsuRyakusyou(bool value)
{
	m_bDisplaySyubetsuRyakusyou = value;
	return *this;
};
bool	CDcdAllOperationTable::getDisplayRessyamei()const{
		return m_bDisplayRessyamei ;};
CDcdAllOperationTable& CDcdAllOperationTable::setDisplayRessyamei( bool value )
{
		m_bDisplayRessyamei = value ; 
		return *this ;
};
bool	CDcdAllOperationTable::getDisplayJikokuMinute()const {
	return m_bDisplayJikokuMinute;
};
CDcdAllOperationTable& CDcdAllOperationTable::setDisplayJikokuMinute(bool value)
{
	m_bDisplayJikokuMinute = value;
	return *this;
};

CdDcdPosXy	CDcdAllOperationTable::getPosDgr()const 
{
	return CdDcdPosXy( 
		m_CconvContentPosToDcdTarget.getContentPos() ) ; 
}
void	CDcdAllOperationTable::setPosDgr(CdDcdPosXy posPosDgr ) 
{
	m_CconvContentPosToDcdTarget.setContentPos( posPosDgr ) ;

	adjustProp() ;
}
double CDcdAllOperationTable::getDcdPerDgrX( IfDcdTarget* pIfDcdTarget ) 
{
	return m_CconvContentPosToDcdTarget.getX()
		->getTargetPosPerContent( pIfDcdTarget ) ;
}
void CDcdAllOperationTable::setDcdPerDgrX( IfDcdTarget* pIfDcdTarget , double dDcdPerDgr ) 
{
	m_CconvContentPosToDcdTarget.getX()->setTargetPosPerContent(
		dDcdPerDgr , pIfDcdTarget ) ;
	adjustProp() ;
}

double CDcdAllOperationTable::getDcdPerDgrY(IfDcdTarget* pIfDcdTarget) 
{
	return m_CconvContentPosToDcdTarget.getY()
		->getTargetPosPerContent(pIfDcdTarget) ;
}

void CDcdAllOperationTable::setDcdPerDgrY( 
	IfDcdTarget* pIfDcdTarget , 
	double dDcdPerDgr ) 
{
	m_CconvContentPosToDcdTarget.getY()->setTargetPosPerContent(
		dDcdPerDgr , pIfDcdTarget ) ;
	adjustProp() ;
}

	

int	CDcdAllOperationTable::getVlineMode()const{	return m_idxVlineMode ;};
CDcdAllOperationTable& CDcdAllOperationTable::setVlineMode( int value )
{
	if ( value >= sizeof(m_arVline) / sizeof(m_arVline[0]) ){
		value = sizeof(m_arVline) / sizeof(m_arVline[0]) - 1 ;
	}
	if ( value < 0 ){
		value = 0 ;
	}
	m_idxVlineMode = value ; 
	return *this ; 
} ;

int CDcdAllOperationTable::getVlinePitch()const 
{
	return ( m_arVline[m_idxVlineMode].m_iVlinePitch ) ;
}
int CDcdAllOperationTable::getVlineMiddlePitch()const 
{
	return ( m_arVline[m_idxVlineMode].m_iVlineMiddlePitch ) ;
}
int CDcdAllOperationTable::getVlineBoldPitch()const 
{
	return ( m_arVline[m_idxVlineMode].m_iVlineBoldPitch ) ;
}

int CDcdAllOperationTable::
	getVlineChoices( Mui<VLINE>* pContVLINE )const 
{
	if ( pContVLINE != NULL ){
		pContVLINE->erase( 0 , INT_MAX ) ;
		for ( int idx = 0 ; idx < sizeof(m_arVline) / sizeof(m_arVline[0]) ; 
				idx ++ ){
			pContVLINE->insert( m_arVline[idx] ) ;
		}
	}
	return sizeof(m_arVline) / sizeof(m_arVline[0]) ;
}

bool CDcdAllOperationTable::getDisplayParentSyubetsu() const
{
	return m_bDisplayParentSyubetsu;
}
CDcdAllOperationTable & CDcdAllOperationTable::setDisplayParentSyubetsu(bool value)
{
	m_bDisplayParentSyubetsu = value;
	return *this;
}
CDcdAllOperationTable& CDcdAllOperationTable::setClippingCount(int value)
{
	m_iClippingCount = value;
	return *this;
}
;
	// ********************************
	//@name CDcdAllOperationTable-操作
	// ********************************

CDcdAllOperationTable& CDcdAllOperationTable::readCdDedDispProp( const CdDedDispProp& value ) 
{
	m_fontpropOperationTableFont = value.getOperationTableFont();
	m_fontpropAllOperationTableJikokuFont = value.getAllOperationTableJikokuFont();
	m_colorDiaJikuColor = value.getDiaJikuColor() ;
	m_colorGridColor = value.getOperationGridColor();
	m_colorStringColor = value.getOperationStringColor();
	return *this ;
}

CdDcdZoneXy	CDcdAllOperationTable::getZone_Dgr( IfDcdTarget* pIfDcdTarget )
{
	return m_CconvContentPosToDcdTarget.getContentZone(pIfDcdTarget) ;
};

void CDcdAllOperationTable::setZone_Dgr( 
	IfDcdTarget* pIfDcdTarget , 
	const CdDcdZoneXy& value )
{
	m_CconvContentPosToDcdTarget.setContentZone(value , pIfDcdTarget) ;

	adjustProp() ;

} ;

bool CDcdAllOperationTable::getKeepZoneDgrOnSize()const
{
	return ( m_CconvContentPosToDcdTarget.getMode() == 
		CconvContentPosToTarget::EModeZone ) ;
}		

void CDcdAllOperationTable::setKeepZoneDgrOnSize( bool bRv )
{
	CconvContentPosToTarget::EMode	eMode = 
		CconvContentPosToTarget::EModePosAndRate ;
	if ( bRv )
	{
		eMode = CconvContentPosToTarget::EModeZone ;
	}
	m_CconvContentPosToDcdTarget.setMode( eMode ) ;
}		



int CDcdAllOperationTable::calcCentDedRessyaOfPoint( 
		IfDcdTarget* pIfDcdTarget ,
		const CdDcdPosXy& aCdDcdPosXy ,  
		//int iMerginPixels ,
		ERessyahoukou *pERessyahoukou , 
		int *piRessyaIdx/* , 
		int *piRessyasenIdx */) 
{
	LogMsg(_T("CDcdAllOperationTable::calcCentDedDgrRessyasenOfPoint(,(%d,%d)) ") ,
		aCdDcdPosXy.getX() , aCdDcdPosXy.getY() ) ;
 

	int iRv = 0 ;
	int iOperationIndex = calcOperationIndexOfPoint(pIfDcdTarget, aCdDcdPosXy.getY());
	if (iOperationIndex == -1)
	{
		return iRv;
	}
	CdDedJikoku KitenJikoku = getCDiagramEditDoc()->
		getCDedRosenFileData()->getCentDedRosen()->getKitenJikoku();
	DcdPos posX_Dgr = XDgrFromDcd(pIfDcdTarget, aCdDcdPosXy.getX());
	if (posX_Dgr < KitenJikoku.getTotalSeconds() || posX_Dgr >= (KitenJikoku.getTotalSeconds() + CdDedJikoku::TOTALSECONDS_A_DAY))
	{
		return iRv;
	}
	CdDedJikoku SearchJikoku(posX_Dgr);

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

	const list<OperationTableContent>& ListOperationTableContent = 
		pCentDedDia->getcontOperationTableContent().at(getOperationNumber()->at(iOperationIndex));

	if (ListOperationTableContent.size() == 1)
	{
		//列車本数が一本の場合は、その列車を返す
		*pERessyahoukou = ListOperationTableContent.begin()->aRessyaProperty.getRessyahoukou();
		*piRessyaIdx = ListOperationTableContent.begin()->aRessyaProperty.getRessyaIndex();
		iRv = 1;
		return iRv;
	}
	CdDedJikoku OutJikoku;
	CdDedJikoku PrevSyuuchakuJikoku;
	for (auto itr = ListOperationTableContent.begin(); itr != ListOperationTableContent.end(); itr++)
	{
		const CentDedRessya* pCentDedRessya =
			pCentDedRessyaConts[itr->aRessyaProperty.getRessyahoukou()]
			->get(itr->aRessyaProperty.getRessyaIndex());
		CdDedJikoku SihatsuJikoku;
		if (itr->iOuterShihatsuekiIndex != INT_MIN)
		{
			SihatsuJikoku = itr->OuterShihatsuJikoku;
		}
		else
		{
			int iSihatsuEkiOrder = itr->iSihatsuEkiOrder;
			if (!pCentDedRessya->isRunBetweenNextEki(iSihatsuEkiOrder))
			{
				iSihatsuEkiOrder = pCentDedRessya->getRunBetweenEkiForward(iSihatsuEkiOrder);
			}
			SihatsuJikoku = pCentDedRessya->getCentDedEkiJikoku(iSihatsuEkiOrder).getHatsujikoku();
		}
		CdDedJikoku SyuuchakuJikoku;
		if (itr->iOuterShuchakuekiIndex != INT_MIN)
		{
			SyuuchakuJikoku = itr->OuterShuchakuJikoku;
		}
		else
		{
			int iSyuuchakuEkiOrder = itr->iSyuuchakuEkiOrder;
			if (!pCentDedRessya->isRunBetweenNextEki(iSyuuchakuEkiOrder - 1))
			{
				iSyuuchakuEkiOrder = pCentDedRessya->getRunBetweenEkiBackward(iSyuuchakuEkiOrder);
			}

			SyuuchakuJikoku = pCentDedRessya->getCentDedEkiJikoku(iSyuuchakuEkiOrder).getChakujikoku();
		}
		//列車の始発・終着時刻を取得した後は、まず列車が表示範囲にあるかどうかを確認します
		//(出区列車である、もしくは、出区時刻から24時間を超えていない)

		if (PrevSyuuchakuJikoku.isNull())
		{
			/**
				前列車終着時刻がNULLの場合は、SihatsuJikokuとSyuuchakuJikokuの間(含むSihatsuJikokuとSyuuchakuJikoku)に
				SearchJikokuがあるかどうかを調べる。
				ある場合は、この列車を返す。
				無い場合は出区時刻に始発時刻を、前列車終着時刻に終着時刻を代入して次へ
			*/
			if (SearchJikoku.compare(SyuuchakuJikoku, SihatsuJikoku) <= 0)
			{
				//この列車を返す
				*pERessyahoukou = itr->aRessyaProperty.getRessyahoukou();
				*piRessyaIdx = itr->aRessyaProperty.getRessyaIndex();
				iRv = 1;
				return iRv;
			}
			else
			{
				OutJikoku = SihatsuJikoku;
				PrevSyuuchakuJikoku = SyuuchakuJikoku;
			}
		}
		else
		{
			/**
				前列車終着時刻が非NULLの場合は、
				(1)PrevSyuuchakuJikokuとSihatsuJikokuの間(含むSihatsuJikoku)にOutJikokuがあるかどうかを調べる
				(2)無い場合はSihatsuJikokuとSyuuchakuJikokuの間(含むSyuuchakuJikoku)にOutJikokuがあるかどうかを調べる
					※PrevSyuuchakuJikokuとSyuuchakuJikokuの間でチェックを行うと、24時間を超える可能性があるので、必ず別々に行う
				どちらかが当てはまれば、この列車は図中で非表示なので、ジャンプ対象からも除外となる、
				その場合は、出区列車と前列車のいずれかを返すことになる
				どちらも当てはまらなかった場合は、
				(1)PrevSyuuchakuJikokuとSihatsuJikokuの間(除くSihatsuJikoku)にSearchJikokuがあるかどうかを調べる
					当てはまる場合、前列車とこの列車のいずれかを返すことになる
				(2)SihatsuJikokuとSyuuchakuJikokuの間(含むSyuuchakuJikoku)にSearchJikokuがあるかどうかを調べる
					当てはまる場合、この列車を返す
				どちらも当てはまらなかった場合は、
				(1)この列車が入区列車の場合、出区列車とこの列車のいずれかを返すことになる
				(2)次列車がある場合、PrevSyuuchakuJikokuをSyuuchakuJikokuで上書きし、次列車へ。
			*/
			if (OutJikoku.compare(SihatsuJikoku, PrevSyuuchakuJikoku) <= 0 ||
				OutJikoku.compare(SyuuchakuJikoku, SihatsuJikoku) <= 0)
			{
				if (KitenJikoku.compare(OutJikoku, PrevSyuuchakuJikoku) <= 0)
				{
					if (KitenJikoku.compare(SearchJikoku, PrevSyuuchakuJikoku) <= 0)
					{
						//出区列車を返す
						*pERessyahoukou = ListOperationTableContent.begin()->aRessyaProperty.getRessyahoukou();
						*piRessyaIdx = ListOperationTableContent.begin()->aRessyaProperty.getRessyaIndex();
						iRv = 1;
						return iRv;
					}
					else
					{
						//一つ前の列車を返す
						auto itrPrev = itr;
						itrPrev--;
						*pERessyahoukou = itrPrev->aRessyaProperty.getRessyahoukou();
						*piRessyaIdx = itrPrev->aRessyaProperty.getRessyaIndex();
						iRv = 1;
						return iRv;
					}
				}
				else
				{
					int iDifOut = OutJikoku.getTotalSeconds() - SearchJikoku.getTotalSeconds();
					if (iDifOut < 0)
					{
						iDifOut += CdDedJikoku::TOTALSECONDS_A_DAY;
					}
					int iDifPrevSyuuchaku = SearchJikoku.getTotalSeconds() - PrevSyuuchakuJikoku.getTotalSeconds();
					if (iDifPrevSyuuchaku < 0)
					{
						iDifPrevSyuuchaku += CdDedJikoku::TOTALSECONDS_A_DAY;
					}
					if (iDifOut <= iDifPrevSyuuchaku)
					{
						//出区列車を返す
						*pERessyahoukou = ListOperationTableContent.begin()->aRessyaProperty.getRessyahoukou();
						*piRessyaIdx = ListOperationTableContent.begin()->aRessyaProperty.getRessyaIndex();
						iRv = 1;
						return iRv;
					}
					else
					{
						//一つ前の列車を返す
						auto itrPrev = itr;
						itrPrev--;
						*pERessyahoukou = itrPrev->aRessyaProperty.getRessyahoukou();
						*piRessyaIdx = itrPrev->aRessyaProperty.getRessyaIndex();
						iRv = 1;
						return iRv;
					}
				}

			}
			else
			{
				if (SearchJikoku.compare(SihatsuJikoku, PrevSyuuchakuJikoku) < 0)
				{
					if (KitenJikoku.compare(SihatsuJikoku, PrevSyuuchakuJikoku) < 0)
					{
						if (KitenJikoku.compare(SearchJikoku, PrevSyuuchakuJikoku) <= 0)
						{
							//この列車を返す
							*pERessyahoukou = itr->aRessyaProperty.getRessyahoukou();
							*piRessyaIdx = itr->aRessyaProperty.getRessyaIndex();
							iRv = 1;
							return iRv;
						}
						else
						{
							//一つ前の列車を返す
							auto itrPrev = itr;
							itrPrev--;
							*pERessyahoukou = itrPrev->aRessyaProperty.getRessyahoukou();
							*piRessyaIdx = itrPrev->aRessyaProperty.getRessyaIndex();
							iRv = 1;
							return iRv;
						}
					}
					else
					{
						int iDifSihatsu = SihatsuJikoku.getTotalSeconds() - SearchJikoku.getTotalSeconds();
						if (iDifSihatsu < 0)
						{
							iDifSihatsu += CdDedJikoku::TOTALSECONDS_A_DAY;
						}
						int iDifPrevSyuuchaku = SearchJikoku.getTotalSeconds() - PrevSyuuchakuJikoku.getTotalSeconds();
						if (iDifPrevSyuuchaku < 0)
						{
							iDifPrevSyuuchaku += CdDedJikoku::TOTALSECONDS_A_DAY;
						}
						if (iDifSihatsu <= iDifPrevSyuuchaku)
						{
							//この列車を返す
							*pERessyahoukou = itr->aRessyaProperty.getRessyahoukou();
							*piRessyaIdx = itr->aRessyaProperty.getRessyaIndex();
							iRv = 1;
							return iRv;
						}
						else
						{
							//一つ前の列車を返す
							auto itrPrev = itr;
							itrPrev--;
							*pERessyahoukou = itrPrev->aRessyaProperty.getRessyahoukou();
							*piRessyaIdx = itrPrev->aRessyaProperty.getRessyaIndex();
							iRv = 1;
							return iRv;
						}
					}
				}
				else if (SearchJikoku.compare(SyuuchakuJikoku, SihatsuJikoku) <= 0)
				{
					//この列車を返す
					*pERessyahoukou = itr->aRessyaProperty.getRessyahoukou();
					*piRessyaIdx = itr->aRessyaProperty.getRessyaIndex();
					iRv = 1;
					return iRv;
				}
				else
				{
					auto itrNext = itr;
					itrNext++;
					if (itrNext == ListOperationTableContent.end())
					{
						if (KitenJikoku.compare(OutJikoku, SyuuchakuJikoku) < 0)
						{
							if (KitenJikoku.compare(SearchJikoku, SyuuchakuJikoku) <= 0)
							{
								//出区列車を返す
								*pERessyahoukou = ListOperationTableContent.begin()->aRessyaProperty.getRessyahoukou();
								*piRessyaIdx = ListOperationTableContent.begin()->aRessyaProperty.getRessyaIndex();
								iRv = 1;
								return iRv;
							}
							else
							{
								//この列車を返す
								*pERessyahoukou = itr->aRessyaProperty.getRessyahoukou();
								*piRessyaIdx = itr->aRessyaProperty.getRessyaIndex();
								iRv = 1;
								return iRv;
							}
						}
						else
						{
							int iDifOut = OutJikoku.getTotalSeconds() - SearchJikoku.getTotalSeconds();
							if (iDifOut < 0)
							{
								iDifOut += CdDedJikoku::TOTALSECONDS_A_DAY;
							}
							int iDifSyuuchaku = SearchJikoku.getTotalSeconds() - SyuuchakuJikoku.getTotalSeconds();
							if (iDifSyuuchaku < 0)
							{
								iDifSyuuchaku += CdDedJikoku::TOTALSECONDS_A_DAY;
							}
							if (iDifOut <= iDifSyuuchaku)
							{
								//出区列車を返す
								*pERessyahoukou = ListOperationTableContent.begin()->aRessyaProperty.getRessyahoukou();
								*piRessyaIdx = ListOperationTableContent.begin()->aRessyaProperty.getRessyaIndex();
								iRv = 1;
								return iRv;
							}
							else
							{
								//この列車を返す
								*pERessyahoukou = itr->aRessyaProperty.getRessyahoukou();
								*piRessyaIdx = itr->aRessyaProperty.getRessyaIndex();
								iRv = 1;
								return iRv;
							}
						}
					}
					else
					{
						PrevSyuuchakuJikoku = SyuuchakuJikoku;
					}
				}
			}
		}
	}
	return ( iRv ) ;
}


int CDcdAllOperationTable::calcOperationIndexOfPoint(
		IfDcdTarget* pIfDcdTarget ,
		DcdPos posY_Dcd )  
{
	DcdPos posY_Dgr = YDgrFromDcd(pIfDcdTarget, posY_Dcd);
	int iOperationIndex = posY_Dgr / DEFAULT_YSIZE_PER_ONEOPERATION();
	if (iOperationIndex >= 0 && iOperationIndex < (int)getOperationNumber()->size())
	{
		return (iOperationIndex);
	}
	return -1;
}


	// ********************************
	//@name CDcdAllOperationTable-ダイヤグラム座標と、IfDcdTarget 上の座標を変換
	// ********************************
DcdPos CDcdAllOperationTable::XDgrToDcd( IfDcdTarget* pIfDcdTarget , DcdPos posSrc ) 
{
	return m_CconvContentPosToDcdTarget.getX()->ContentPosToTarget(
		posSrc , pIfDcdTarget ) ;
}

DcdPos CDcdAllOperationTable::YDgrToDcd( IfDcdTarget* pIfDcdTarget , DcdPos posSrc ) 
{
	return m_CconvContentPosToDcdTarget.getY()->ContentPosToTarget(
		posSrc , pIfDcdTarget ) ;
}

DcdPos CDcdAllOperationTable::XDgrFromDcd( IfDcdTarget* pIfDcdTarget , DcdPos posSrc ) 
{
	return m_CconvContentPosToDcdTarget.getX()->ContentPosFromTarget(
		posSrc , pIfDcdTarget ) ;
}

DcdPos CDcdAllOperationTable::YDgrFromDcd( IfDcdTarget* pIfDcdTarget , DcdPos posSrc ) 
{
	return m_CconvContentPosToDcdTarget.getY()->ContentPosFromTarget(
		posSrc , pIfDcdTarget ) ;
}

CdDcdZone CDcdAllOperationTable::XDgrToDcd( IfDcdTarget* pIfDcdTarget , 
		const CdDcdZone& zoneSrc ) 
{
	return m_CconvContentPosToDcdTarget.getX()->ContentZoneToTarget(
		zoneSrc , pIfDcdTarget ) ;

}

CdDcdZone CDcdAllOperationTable::YDgrToDcd( IfDcdTarget* pIfDcdTarget , 
		const CdDcdZone& zoneSrc ) 
{
	return m_CconvContentPosToDcdTarget.getY()->ContentZoneToTarget(
		zoneSrc , pIfDcdTarget ) ;
}

CdDcdZone CDcdAllOperationTable::XDgrFromDcd( IfDcdTarget* pIfDcdTarget , 
		const CdDcdZone& zoneSrc ) 
{
	return m_CconvContentPosToDcdTarget.getX()->ContentZoneFromTarget(
		zoneSrc , pIfDcdTarget ) ;
}

CdDcdZone CDcdAllOperationTable::YDgrFromDcd( IfDcdTarget* pIfDcdTarget , 
		const CdDcdZone& zoneSrc ) 
{
	return m_CconvContentPosToDcdTarget.getY()->ContentZoneFromTarget(
		zoneSrc , pIfDcdTarget ) ;
}



CdDcdPosXy CDcdAllOperationTable::DgrToDcd( IfDcdTarget* pIfDcdTarget , 
		const CdDcdPosXy& posSrc ) 
{
	return m_CconvContentPosToDcdTarget.ContentPosToTarget( 
		posSrc , 
		pIfDcdTarget ) ;
}
CdDcdPosXy CDcdAllOperationTable::DgrFromDcd( IfDcdTarget* pIfDcdTarget , 
		const CdDcdPosXy& posSrc ) 
{
	return m_CconvContentPosToDcdTarget.ContentPosFromTarget( 
		posSrc , 
		pIfDcdTarget ) ;
}


CdDcdZoneXy CDcdAllOperationTable::DgrToDcd( IfDcdTarget* pIfDcdTarget , 
		const CdDcdZoneXy& zoneSrc ) 
{
	return m_CconvContentPosToDcdTarget.ContentZoneToTarget( 
		zoneSrc , 
		pIfDcdTarget ) ;
}

CdDcdZoneXy CDcdAllOperationTable::DgrFromDcd( IfDcdTarget* pIfDcdTarget , 
		const CdDcdZoneXy& zoneSrc ) 
{
	return m_CconvContentPosToDcdTarget.ContentZoneFromTarget( 
		zoneSrc , 
		pIfDcdTarget ) ;
}
} //namespace ViewAllOperationTable2
