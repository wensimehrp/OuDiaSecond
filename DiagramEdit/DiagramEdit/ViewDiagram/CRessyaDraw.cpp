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
//	CRessyaDraw.cpp
// $Id: CRessyaDraw.cpp 
// ****************************************************************
*/
#include "stdafx.h"
#include "CRessyaDraw.h"
#include <chrono>
#include "..¥entDed¥CconvCentDed.h"
#include "DcDraw/CDcdText.h"
#include "DcDraw/CConverter_WinGdi.h"

namespace ViewDiagram {
	
// ****************************************************************
//	CEnumRessyasen
// ****************************************************************
	//*******************************
	//	コンストラクタ
	//*******************************
//	CRessyaDraw::CRessyaDraw(
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
	CRessyaDraw::CRessyaDraw(CDcdDiagram* pCDcdDiagram,
		IfDcdTarget* pIfDcdTarget,
		bool bDisplayRessyasenKudari,
		bool bDisplayRessyasenNobori,
		bool bDisplayParentSyubetsu) :
		//super(
		//	pCDcdDiagram->getCentDedDgrDia(),
		//	pCDcdDiagram->DgrFromDcd(pIfDcdTarget, pIfDcdTarget->getZone()),
		//	bDisplayRessyasenKudari,
		//	bDisplayRessyasenNobori),
		m_pCDcdDiagram(pCDcdDiagram),
		m_pIfDcdTarget(pIfDcdTarget),
		m_bDisplayRessyasenKudari(bDisplayRessyasenKudari),
		m_bDisplayRessyasenNobori(bDisplayRessyasenNobori),
		m_bDisplayParentSyubetsu(bDisplayParentSyubetsu),
		m_pCentDedDgrDia(pCDcdDiagram->getCentDedDgrDia()),
		m_zonexyDgrZone(pCDcdDiagram->DgrFromDcd(pIfDcdTarget, pIfDcdTarget->getZone()))
	{
	};
	CRessyaDraw::‾CRessyaDraw()
{
}

	// --------------------------------
	//@name CRessyaDraw
	// --------------------------------
void CRessyaDraw::onCentDedDgrRessya(
		ERessyahoukou eRessyahoukou ,
		int iRessyaIdx ,
		const CentDedDgrRessya* pCentDedDgrRessya ,
		const int& iShiftSecond)
{
	//	対象となる描画領域を、
	//	『ダイヤグラムエンティティ座標系』で保持します。
	//	これは、今回描画を行う範囲を表しています。
	CdDcdZoneXy	zonexyDgrZone = m_zonexyDgrZone ;

	const Mu<const CentDedDgrRessyasen*>* pMuCentDedDgrRessyasen = 
		pCentDedDgrRessya->getCentDedDgrRessyasenCont() ;
	int iRessyasenSize = pMuCentDedDgrRessyasen->size();
	for ( int iRessyasenIdx = 0 ; 
			iRessyasenIdx < iRessyasenSize;
			iRessyasenIdx ++ )
	{
		// --------------------------------
		//	列車線毎の処理
		// --------------------------------
		const CentDedDgrRessyasen*	pCentDedDgrRessyasen = 	
			pMuCentDedDgrRessyasen->get( iRessyasenIdx ) ;

		// --------------------------------
		//	列車線のY領域が描写範囲内にあるかチェック
		// --------------------------------

		int iEkiOrderRessyasenKiten = pCentDedDgrRessyasen->getRessyasenKitenEkiOrder();
		int iEkiOrderRessyasenSyuuten = pCentDedDgrRessyasen->getRessyasenSyuutenEkiOrder();

		if (iEkiOrderRessyasenKiten >= getDisplayTerminalSideEkiOrder(eRessyahoukou) ||
			iEkiOrderRessyasenSyuuten <= getDisplayOriginSideEkiOrder(eRessyahoukou))
		{
			continue;
		}

		// --------------------------------
		//	列車線のX領域を求める
		// --------------------------------
		CentDedDgrEkiJikoku	aEkiJikokuKiten =
			*pCentDedDgrRessya->getMuCentDedDgrEkiJikoku()->get(iEkiOrderRessyasenKiten);
		CentDedDgrEkiJikoku	aEkiJikokuSyuuten =
			*pCentDedDgrRessya->getMuCentDedDgrEkiJikoku()->get(iEkiOrderRessyasenSyuuten);

		DcdPos posxDgrKiten = aEkiJikokuKiten.getDgrXPosHatsu(true) + iShiftSecond;
		DcdPos posxDgrSyuuten = aEkiJikokuSyuuten.getDgrXPosChaku(true) + iShiftSecond;

		if (zonexDgrPosOnDgrZone(posxDgrKiten, posxDgrSyuuten))
		{
			//	この列車線は、描画可能な時間帯にあります。

			CdDcdPosXy	posDcdRessyasenKiten ;
			CdDcdPosXy	posDcdRessyasenSyuuten ;
			posDcdRessyasenKiten.setX(XDgrToDcd(posxDgrKiten));
			posDcdRessyasenSyuuten.setX(XDgrToDcd(posxDgrSyuuten));

			posDcdRessyasenKiten.setY(
				YDgrToDcd(iEkiOrderRessyasenKiten, eRessyahoukou, false));
			posDcdRessyasenSyuuten.setY(
				YDgrToDcd(iEkiOrderRessyasenSyuuten, eRessyahoukou, true));

			RessyasenDraw(
				pCentDedDgrRessya,
				posDcdRessyasenKiten,
				posDcdRessyasenSyuuten);

			onCentDedDgrRessyasen(
				eRessyahoukou,
				iRessyaIdx,
				pCentDedDgrRessya,
				iRessyasenIdx,
				pCentDedDgrRessyasen,
				iShiftSecond);
		}
	}

	RessyaTrackLineDraw(
		eRessyahoukou,
		pCentDedDgrRessya,
		iShiftSecond);
}

void CRessyaDraw::onCentDedDgrRessyasen(
		ERessyahoukou eRessyahoukou ,
		int iRessyaIdx ,
		const CentDedDgrRessya* pCentDedDgrRessya ,
		int iRessyasenIdx ,
		const CentDedDgrRessyasen* pCentDedDgrRessyasen,
		const int& iShiftSecond)
{
	int iEkiOrderRessyasenKiten = pCentDedDgrRessyasen->getRessyasenKitenEkiOrder() ;
	int iEkiOrderRessyasenSyuuten = pCentDedDgrRessyasen->getRessyasenSyuutenEkiOrder() ;

	const Mu<const CentDedDgrEkiJikoku*>* pMuCentDedDgrEkiJikoku = 
		pCentDedDgrRessya->getMuCentDedDgrEkiJikoku() ;
	
	for ( int iEkiOrder = iEkiOrderRessyasenKiten ;
		iEkiOrder <= iEkiOrderRessyasenSyuuten ;
		iEkiOrder ++ )
	{
		const CentDedDgrEkiJikoku* pCentDedDgrEkiJikoku = 
			pCentDedDgrRessya->getMuCentDedDgrEkiJikoku()->get( iEkiOrder ) ;

		RessyajouhouDraw(
			eRessyahoukou,
			iRessyaIdx,
			pCentDedDgrRessya,
			iRessyasenIdx,
			pCentDedDgrRessyasen,
			iEkiOrder,
			pCentDedDgrEkiJikoku,
			iShiftSecond);

		StopMarkDraw(
			eRessyahoukou,
			iRessyaIdx,
			pCentDedDgrRessya,
			iRessyasenIdx,
			pCentDedDgrRessyasen,
			iEkiOrder,
			pCentDedDgrEkiJikoku,
			iShiftSecond);

		//onCentDedDgrEkiJikoku( 
		//	eRessyahoukou , 
		//	iRessyaIdx , 
		//	pCentDedDgrRessya ,
		//	iRessyasenIdx ,
		//	pCentDedDgrRessyasen ,
		//	iEkiOrder ,
		//	pCentDedDgrEkiJikoku ) ;
		//auto p2 = std::chrono::system_clock::now();
		//m_ds1 += std::chrono::duration_cast<std::chrono::milliseconds>(p2 - p1).count();
	}


}
//void CRessyaDraw::onCentDedDgrEkiJikoku(
//		ERessyahoukou eRessyahoukou ,
//		int iRessyaIdx ,
//		const CentDedDgrRessya* pCentDedDgrRessya ,
//		int iRessyasenIdx ,
//		const CentDedDgrRessyasen* pCentDedDgrRessyasen ,
//		int iEkiOrder , 
//		const CentDedDgrEkiJikoku* pCentDedDgrEkiJikoku ) 
//{
//}

	// ********************************
	//@name CRessyaDraw-関連
	// ********************************
const CentDedDgrDia*	CRessyaDraw::getCentDedDgrDia()
{	
		return m_pCentDedDgrDia ; 
} ;
	// ********************************
	//@name CRessyaDraw-属性
	// ********************************
CdDcdZoneXy	CRessyaDraw::getDgrZone()
{
	return m_zonexyDgrZone ;
};

bool CRessyaDraw::getDisplayRessyasen(  ERessyahoukou eRessyahoukou )const
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
	//@name CRessyaDraw-操作
	// ********************************
void CRessyaDraw::execute()
{
	//キャッシュの初期化
	ReadYDcdCache();
	m_DcdXCache.clear();

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
		if ( !getDisplayRessyasen( eRessyahoukou ) ) 
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
				pMuCentDedDgrRessya->get(iRessyaIdx);
			if (pCentDedDgrRessya->getIsNull() ||
				pCentDedDgrRessya->getCentDedDgrRessyasenCont()->size() <= 0)
			{
				//	NULL列車・列車線の全くない列車は対象外
				continue;
			}
			// --------------------------------

			//CentDedDgrRessya	aCentDedDgrRessya(*pCentDedDgrRessya);
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
			int iShiftSecond = 0;
			while (!(pCentDedDgrRessya->getDgrXZone().getEndPos() + iShiftSecond <
				zonexyDgrZone.getX().getPos()))
			{
				iShiftSecond -= CdDedJikoku::TOTALSECONDS_A_DAY;
			}

			//	ここで、24時間加算します。これにより、列車時刻は
			//	-01:00→01:00 
			//	となります。
			iShiftSecond += CdDedJikoku::TOTALSECONDS_A_DAY;

			for (; pCentDedDgrRessya->getDgrXZone().getPos() + iShiftSecond <
				zonexyDgrZone.getX().getEndPos();
				iShiftSecond += CdDedJikoku::TOTALSECONDS_A_DAY)
			{
				// --------------------------------
				//	列車の表示位置（２４時間間隔）毎の処理
				// --------------------------------
				CdDcdZone DgrXZoneShift(pCentDedDgrRessya->getDgrXZone().getPos() + iShiftSecond,
					pCentDedDgrRessya->getDgrXZone().getSize());
				CdDcdZone	zoneDgrXCross = zonexyDgrZone.getX().CrossZone(
					DgrXZoneShift);
				if (zoneDgrXCross.getSize() > 0)
				{
					//	この列車は、対象となる描画領域内にあります。
					onCentDedDgrRessya(
						eRessyahoukou,
						iRessyaIdx,
						pCentDedDgrRessya,
						iShiftSecond);
				}
			}
		}
	}
};

void CRessyaDraw::RessyasenDraw(
	const CentDedDgrRessya* pCentDedDgrRessya,
	CdDcdPosXy posDcdRessyasenKiten,
	CdDcdPosXy posDcdRessyasenSyuuten)
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
			if (m_bDisplayParentSyubetsu && pCentDedDgrRessyasyubetsu->getParentSyubetsuIndex() >= 0)
			{
				pCentDedDgrRessyasyubetsu = getCentDedDgrDia()
					->getMuCentDedDgrRessyasyubetsu()->get(pCentDedDgrRessyasyubetsu->getParentSyubetsuIndex());
			}
			CentDedRessyasyubetsu::CdDiagramLineStyle	aCdDiagramLineStyle =
				pCentDedDgrRessyasyubetsu->getCdDiagramLineStyle();

			CconvCentDed aCconvCentDed;
			aCconvCentDed.CentDedRessyasyubetsu_to_CDcdFreeLineProp(
				aCdDiagramLineStyle,
				&aCdLineProp);
		}
	}

	// --------------------------------
	//	直線の描画位置を決定
	// --------------------------------
	CDcdFreeLine	aCDcdFreeLine(aCdLineProp);
	aCDcdFreeLine.setOrg(posDcdRessyasenKiten);
	aCDcdFreeLine.setDst(posDcdRessyasenSyuuten);
#pragma omp critical
	{
		aCDcdFreeLine.DcDraw(m_pIfDcdTarget);
	}

}

///	円周率
const double Pi = 3.14159265;

/**
	角度の単位を、度からラジアンへ変換します。

	180 度 = 1π ラジアン
	@param value [in]
	変換対象の値。
	@return
	変換後の値。
*/
static double DegToRad(double value)
{
	return value * Pi / 180;
}

/**
	角度の単位を、ラジアンから度へ変換します。

	180 度 = 1π ラジアン
	@param value [in]
	変換対象の値。
	@return
変換後の値。
*/
static double RadToDeg(double value)
{
	return value * 180 / Pi;
}

void CRessyaDraw::RessyajouhouDraw(
	ERessyahoukou eRessyahoukou,
	int iRessyaIdx,
	const CentDedDgrRessya* pCentDedDgrRessya,
	int iRessyasenIdx,
	const CentDedDgrRessyasen* pCentDedDgrRessyasen,
	int iEkiOrder,
	const CentDedDgrEkiJikoku* pCentDedDgrEkiJikoku,
	const int& iShiftSecond)
{
	if (iEkiOrder == pCentDedDgrRessyasen->getRessyasenSyuutenEkiOrder())
	{
		//	列車線終点には、テキストの描画を行いません
		return;
	}
	if (!pCentDedDgrEkiJikoku->getShouldRessyajouhouDraw())
	{
		//	この駅時刻の位置には、テキストの描画を行いません。
		return;
	}
	// --------------------------------
	//	テキストの色を選択
	// --------------------------------
	CdColorProp	colorText;
	{
		int idxRessyasyubetsu = pCentDedDgrRessya->getRessyasyubetsuIndex();
		if (0 <= idxRessyasyubetsu &&
			idxRessyasyubetsu < getCentDedDgrDia()->getMuCentDedDgrRessyasyubetsu()->size())
		{
			const CentDedDgrRessyasyubetsu* pCentDedDgrRessyasyubetsu =
				getCentDedDgrDia()->getMuCentDedDgrRessyasyubetsu()->get(idxRessyasyubetsu);
			if (m_bDisplayParentSyubetsu && pCentDedDgrRessyasyubetsu->getParentSyubetsuIndex() >= 0)
			{
				pCentDedDgrRessyasyubetsu = getCentDedDgrDia()
					->getMuCentDedDgrRessyasyubetsu()->get(pCentDedDgrRessyasyubetsu->getParentSyubetsuIndex());
			}
			colorText = pCentDedDgrRessyasyubetsu->getJikokuhyouMojiColor();
		}
	}
	//colorText = テキストの色

	// --------------------------------
	//	列車情報テキストの内容を作成し
	//	大きさを計測
	// --------------------------------
	tstring	strRessyajouhou;
	if (m_pCDcdDiagram->getDisplayRessyabangou())
	{
		if (!pCentDedDgrRessya->getRessyabangou().empty())
		{
			if (!strRessyajouhou.empty())
			{
				strRessyajouhou += ' ';
			}
			strRessyajouhou += pCentDedDgrRessya->getRessyabangou();
		}
	}
	if (m_pCDcdDiagram->getDisplayRessyamei())
	{
		if (!pCentDedDgrRessya->getRessyamei().empty())
		{
			if (!strRessyajouhou.empty())
			{
				strRessyajouhou += ' ';
			}
			strRessyajouhou += pCentDedDgrRessya->getRessyamei();
		}
		if (!pCentDedDgrRessya->getGousuu().empty())
		{
			if (!strRessyajouhou.empty())
			{
				strRessyajouhou += ' ';
			}
			strRessyajouhou += pCentDedDgrRessya->getGousuu();
			CString	aStr;
			aStr.LoadString(IDS_WORD_GOUSUU2);
			strRessyajouhou += (LPCTSTR)aStr;
		}
	}
	if (strRessyajouhou.empty())
	{
		return;
	}
	//strRessyajouhou = 表示する列車情報の文字列
	CdDcdSizeXy	sizexyText_Dcd;
#pragma omp critical
	{
		CDcdText	dcdText(strRessyajouhou,
			m_pCDcdDiagram->getDiaRessyaFont());
		dcdText.getItemSize(m_pIfDcdTarget, &sizexyText_Dcd);
	}
		//sizexyText_Dcd = 列車情報テキストの幅と高さ
		//	（水平に描画した場合の寸法です）
	// --------------------------------
	//	列車情報の描画される直線を算出
	// --------------------------------
	CdDcdPosXy	posRessyasen_Pos1_Dcd;
	CdDcdPosXy	posRessyasen_Pos2_Dcd;
	{
		CdDcdPosXy	posDgrPosRessyasenKiten =
			getCentDedDgrDia()->calcDgrPosRessyasenKiten(
				pCentDedDgrRessya,
				pCentDedDgrRessyasen,
				iShiftSecond);
		CdDcdPosXy	posDgrPosRessyasenSyuuten =
			getCentDedDgrDia()->calcDgrPosRessyasenSyuuten(
				pCentDedDgrRessya,
				pCentDedDgrRessyasen,
				iShiftSecond);
		//posDgrPosRessyasenKiten,posDgrPosRessyasenSyuuten = 
		//	『ダイヤグラムエンティティ列車線』の起点と終点の座標
		//	単位は、『ダイヤグラムエンティティ座標系』

		posRessyasen_Pos1_Dcd = m_pCDcdDiagram->DgrToDcd(
			m_pIfDcdTarget,
			posDgrPosRessyasenKiten);
		posRessyasen_Pos2_Dcd = m_pCDcdDiagram->DgrToDcd(
			m_pIfDcdTarget,
			posDgrPosRessyasenSyuuten);
	}
	//posRessyasen_Pos1_Dcd,posRessyasen_Pos2_Dcd = 
	//	『ダイヤグラムエンティティ列車線』の起点と終点の座標
	//	単位は、 IfDcdTarget の座標

	// --------------------------------
	//	列車情報の描画される駅の列車線上での位置を算出
	// --------------------------------
	int iX_Dcd = 0;
	int iY_Dcd = 0;
	{
		int iX_Dgr = 0;
		int iResult = pCentDedDgrRessya->getDgrXPosOfEkiOrder(
			iEkiOrder, &iX_Dgr);
		if (iResult < 0) {
			return;
		}
		iX_Dgr += iShiftSecond;
		//iX_Dgr,iY_Dgr = 列車情報を表示する駅の発時刻の座標
		//	単位は、『ダイヤグラムエンティティ座標系』

		iX_Dcd = XDgrToDcd(iX_Dgr);
		iY_Dcd = YDgrToDcd(iEkiOrder, pCentDedDgrRessya->getRessyahoukou(), false);
	}
	//iX_Dcd,iY_Dcd = 列車情報を表示する駅の発時刻の座標
	//	単位は、 IfDcdTarget の座標系

	// --------------------------------
	//	テキストの位置と角度を計算
	// --------------------------------
	CdDcdPosXy	posText_Dcd;
	int iDeg = 0;
	{
		double d = sizexyText_Dcd.getY() + 2;
		if (pCentDedDgrRessya->getRessyahoukou() ==
			Ressyahoukou_Kudari)
		{
			double a = posRessyasen_Pos2_Dcd.getX() -
				posRessyasen_Pos1_Dcd.getX();
			double b = posRessyasen_Pos2_Dcd.getY() -
				posRessyasen_Pos1_Dcd.getY();
			double a_b = a / b;
			int c = (int)(RadToDeg(atan(a_b)));
			int e = (int)(d / cos(DegToRad(c)));
			posText_Dcd = CdDcdPosXy(iX_Dcd + e, iY_Dcd);
			iDeg = 270 + c;
		}
		else
		{
			double a = posRessyasen_Pos2_Dcd.getX() -
				posRessyasen_Pos1_Dcd.getX();
			double b = posRessyasen_Pos1_Dcd.getY() -
				posRessyasen_Pos2_Dcd.getY();
			double a_b = a / b;
			int c = (int)(RadToDeg(atan(a_b)));
			int e = (int)(d * cos(DegToRad(c)));
			int f = (int)(d * sin(DegToRad(c)));
			posText_Dcd = CdDcdPosXy(iX_Dcd - e, iY_Dcd - f);
			iDeg = 90 - c;
		}
	}
	//posText_Dcd = テキストの左上座標
	//iDeg = テキストの角度（単位は度）

#pragma omp critical
	{
	// --------------------------------
	//	テキストの描画
	// --------------------------------
		
		//	フォントの属性
		//	角度指定を追加します。
		CdFontProp	aCdFontProp = m_pCDcdDiagram->getDiaRessyaFont();
		aCdFontProp.setEscapement(iDeg * 10);

		//	フォントの生成
		Ou<CGdiHFontHolder>	pHFontHolder = m_pIfDcdTarget->createGdiHFontHolder(
			aCdFontProp);

		// --------------------------------
		//	フォント・色・背景モードの選択
		HFONT	hFontPrev = NULL;
		hFontPrev = (HFONT)SelectObject(m_pIfDcdTarget->getHdc(),
			pHFontHolder->getHFont());

		CConverter_WinGdi	aCConverter_WinGdi;
		COLORREF	colorTextPrev = SetTextColor(
			m_pIfDcdTarget->getHdc(),
			aCConverter_WinGdi.COLORREFOf(colorText));
		int iBkModePrev = SetBkMode(m_pIfDcdTarget->getHdc(),
			TRANSPARENT);
		// --------------------------------
		TextOut(m_pIfDcdTarget->getHdc(),
			posText_Dcd.getX(), posText_Dcd.getY(),
			strRessyajouhou.c_str(), strRessyajouhou.size());

		// --------------------------------
		//	フォント・色・背景モードの選択を解除

		{
			SetBkMode(m_pIfDcdTarget->getHdc(), iBkModePrev);
			SetTextColor(m_pIfDcdTarget->getHdc(), colorTextPrev);
		}
		if (hFontPrev != NULL) {
			SelectObject(m_pIfDcdTarget->getHdc(), hFontPrev);
			hFontPrev = NULL;
		}
		// --------------------------------
		//	フォントを破棄
		if (pHFontHolder != NULL)
		{
			pHFontHolder = Ou<CGdiHFontHolder>();
		}
	}
}

void CRessyaDraw::StopMarkDraw(
	ERessyahoukou eRessyahoukou,
	int iRessyaIdx,
	const CentDedDgrRessya* pCentDedDgrRessya,
	int iRessyasenIdx,
	const CentDedDgrRessyasen* pCentDedDgrRessyasen,
	int iEkiOrder,
	const CentDedDgrEkiJikoku* pCentDedDgrEkiJikoku,
	const int& iShiftSecond)
{
	if (m_pCDcdDiagram->getStopMarkDraw() !=
		CDcdDiagram::EStopMarkDraw_DrawOnBriefStop)
	{
		//	現在のモードでは、停車マークの描画を行いません。
		return;
	}
	if (iEkiOrder == pCentDedDgrRessyasen->getRessyasenSyuutenEkiOrder())
	{
		//	列車線終点には、テキストの描画を行いません
		return;
	}
	// --------------------------------
	//	この列車種別で描画を行うか否かを判定
	// --------------------------------
	CentDedRessyasyubetsu::EStopMarkDrawType	eStopMarkDrawType =
		CentDedRessyasyubetsu::EStopMarkDrawType_DrawOnStop;
	{
		int idxRessyasyubetsu = pCentDedDgrRessya->getRessyasyubetsuIndex();
		if (0 <= idxRessyasyubetsu &&
			idxRessyasyubetsu < getCentDedDgrDia()->getMuCentDedDgrRessyasyubetsu()->size())
		{
			const CentDedDgrRessyasyubetsu* pCentDedDgrRessyasyubetsu =
				getCentDedDgrDia()->getMuCentDedDgrRessyasyubetsu()->get(idxRessyasyubetsu);
			if (m_bDisplayParentSyubetsu && pCentDedDgrRessyasyubetsu->getParentSyubetsuIndex() >= 0)
			{
				pCentDedDgrRessyasyubetsu = getCentDedDgrDia()
					->getMuCentDedDgrRessyasyubetsu()->get(pCentDedDgrRessyasyubetsu->getParentSyubetsuIndex());
			}
			eStopMarkDrawType = pCentDedDgrRessyasyubetsu->getStopMarkDrawType();
		}
	}
	//eStopMarkDrawType = 停車駅描画モード


	// --------------------------------
	//	停車マークを描画する位置を算出
	// --------------------------------
	int iX_Dcd = 0;
	int iY_Dcd = 0;
	{
		int iX_Dgr = 0;
		int iResult = pCentDedDgrRessya->getDgrXPosOfEkiOrder(
			iEkiOrder, &iX_Dgr);
		if (iResult < 0) {
			return;
		}
		iX_Dgr += iShiftSecond;
		//iX_Dgr,iY_Dgr = 列車情報を表示する駅の発時刻の座標
		//	単位は、『ダイヤグラムエンティティ座標系』

		iX_Dcd = XDgrToDcd(iX_Dgr);
		iY_Dcd = YDgrToDcd(iEkiOrder, pCentDedDgrRessya->getRessyahoukou(), false);
	}
	//iX_Dcd,iY_Dcd = 列車情報を表示する駅の発時刻の座標
	//	単位は、 IfDcdTarget の座標系

	// --------------------------------
	//	停車時間を算出
	// --------------------------------
	int iStopSeconds = 0;
	{
		if (pCentDedDgrEkiJikoku->getDgrXPosChaku() != INT_MIN &&
			pCentDedDgrEkiJikoku->getDgrXPosHatsu() != INT_MIN)
		{
			iStopSeconds = pCentDedDgrEkiJikoku->getDgrXPosHatsu() -
				pCentDedDgrEkiJikoku->getDgrXPosChaku();
		}
	}

	// --------------------------------
	//	当駅が始発駅でも終着駅でもない
	//	列車種別が停車駅を明示 AND 当駅が短時間停車(60秒未満)
	//	であれば、停車マークを描画
	// --------------------------------
	if (pCentDedDgrRessya->getSihatsuEki() < iEkiOrder &&
		iEkiOrder < pCentDedDgrRessya->getSyuuchakuEki() &&
		eStopMarkDrawType ==
		CentDedRessyasyubetsu::EStopMarkDrawType_DrawOnStop &&
		pCentDedDgrEkiJikoku->getEkiatsukai() ==
		CentDedEkiJikoku::Ekiatsukai_Teisya &&
		iStopSeconds < 60)
	{
		// --------------------------------
		//	停車マークの描画(○)
		// --------------------------------
#pragma omp critical
		{
			CdPenProp	aCdPenProp(1, CdColorProp(0, 0, 0), CdPenProp::SOLID);
			Ou<CGdiHPenHolder>	pHPenHolder = m_pIfDcdTarget->createGdiHPenHolder(aCdPenProp);
			HPEN hPenPrev = (HPEN)SelectObject(m_pIfDcdTarget->getHdc(), pHPenHolder->getHPen());

			CdBrushProp	aCdBrushProp(CdColorProp(0, 0, 0), CdBrushProp::NULLBRUSH);
			Ou<CGdiHBrushHolder> pHBrushHolder = m_pIfDcdTarget->createGdiHBrushHolder(aCdBrushProp);
			HBRUSH hBrushPrev = (HBRUSH)SelectObject(m_pIfDcdTarget->getHdc(), pHBrushHolder->getHBrush());
			Ellipse(
				m_pIfDcdTarget->getHdc(),
				iX_Dcd - 2,
				iY_Dcd - 2,
				iX_Dcd + 3,
				iY_Dcd + 3);
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
void CRessyaDraw::RessyaTrackLineDraw(
	ERessyahoukou eRessyahoukou,
	const CentDedDgrRessya* pCentDedDgrRessya,
	const int& iShiftSecond)
{
	//	対象となる描画領域を、
	//	『ダイヤグラムエンティティ座標系』で保持します。
	//	これは、今回描画を行う範囲を表しています。
	CdDcdZoneXy	zonexyDgrZone = m_zonexyDgrZone;

	const Mu<const CentDedDgrRessyaTrackLine*>* pMuCentDedDgrRessyaTrackLine =
		pCentDedDgrRessya->getCentDedDgrRessyaTrackLineCont();
	int iRessyaTrackLineSize = pMuCentDedDgrRessyaTrackLine->size();
	for (int idx = 0; idx < iRessyaTrackLineSize; idx++)
	{
		const CentDedDgrRessyaTrackLine* pCentDedDgrRessyaTrackLine =
			pMuCentDedDgrRessyaTrackLine->get(idx);
		if (pCentDedDgrRessyaTrackLine->getEkiOrder() > getDisplayTerminalSideEkiOrder(eRessyahoukou) ||
			pCentDedDgrRessyaTrackLine->getEkiOrder() < getDisplayOriginSideEkiOrder(eRessyahoukou))
		{
			continue;
		}
		if (pCentDedDgrRessyaTrackLine->getIsTrackDisplay() && 
			pCentDedDgrRessyaTrackLine->getZaisenCount()>0)
		{
			/**
				各番線への在線を示す横線です。
				前列車接続や入出区等を含む、全ての横線をここで描写します
				また、停車時間が短い・通過の場合の、○×印も描写します
			*/
			for (int idxz = 0; idxz < pCentDedDgrRessyaTrackLine->getZaisenCount(); idxz++)
			{
				//在線の横太線を描写します
				// --------------------------------
				//	在線線の座標を求めます
				// --------------------------------
				Zaisen aZaisen = pCentDedDgrRessyaTrackLine->getZaisen(idxz);

				if (!getEkiTrackExsit(
					pCentDedDgrRessya->getRessyahoukou(),
					pCentDedDgrRessyaTrackLine->getEkiOrder(),
					aZaisen.iRessyaTrack))
				{
					continue;
				}

				DcdPos posxDgrKiten = aZaisen.iDgrXPosChaku + iShiftSecond;
				DcdPos posxDgrSyuuten = aZaisen.iDgrXPosHatsu + iShiftSecond;

				if (zonexDgrPosOnDgrZone(posxDgrKiten, posxDgrSyuuten))
				{
					//iX_Dcd,iY_Dcd = 列車情報を表示する駅の発時刻の座標
					//	単位は、 IfDcdTarget の座標系
					int iX_Left_Dcd = XDgrToDcd(posxDgrKiten);
					int iX_Right_Dcd = XDgrToDcd(posxDgrSyuuten);
					int iY_Dcd = YEkiTrackDgrToDcd(
						pCentDedDgrRessya->getRessyahoukou(),
						pCentDedDgrRessyaTrackLine->getEkiOrder(),
						aZaisen.iRessyaTrack);
					/**
						iY_Dcd < 0 の場合は、当該番線が非表示なので、この横線は非表示です。
					*/
					int iChamferLeft = 0;
					int iChamferRight = 0;
					if (idxz == 0)
					{
						if (pCentDedDgrRessyaTrackLine->getChakuOperation() == -1 ||
							pCentDedDgrRessyaTrackLine->getChakuOperation() == -2 ||
							pCentDedDgrRessyaTrackLine->getChakuOperation() == -3 ||
							pCentDedDgrRessyaTrackLine->getChakuOperation() == 4)
						{
							iChamferLeft = -1;
						}
						else if (pCentDedDgrRessyaTrackLine->getChakuOperation() == -4 ||
							pCentDedDgrRessyaTrackLine->getChakuOperation() == -5)
						{
							iChamferLeft = +1;
						}
						else if (pCentDedDgrRessyaTrackLine->getChakuOperation() == 0 ||
							pCentDedDgrRessyaTrackLine->getChakuOperation() == 2 ||
							pCentDedDgrRessyaTrackLine->getChakuOperation() == 3)
						{
							iChamferLeft = 0;
						}
						else if (pCentDedDgrRessyaTrackLine->getChakuOperation() == 5)
						{
							iChamferLeft = pCentDedDgrRessyaTrackLine->getPrevRessyahoukou();
						}
					}
					else
					{
						Zaisen aZaisenPrev = pCentDedDgrRessyaTrackLine->getZaisen(idxz-1);
						if ((aZaisen.iRessyaTrack > aZaisenPrev.iRessyaTrack &&
							pCentDedDgrRessya->getRessyahoukou() == Ressyahoukou_Kudari) ||
							(aZaisen.iRessyaTrack < aZaisenPrev.iRessyaTrack &&
								pCentDedDgrRessya->getRessyahoukou() == Ressyahoukou_Nobori))
						{
							iChamferLeft = -1;
						}
						else
						{
							iChamferLeft = +1;
						}
					}
					if (idxz == pCentDedDgrRessyaTrackLine->getZaisenCount() - 1)
					{
						if (pCentDedDgrRessyaTrackLine->getHatsuOperation() == -1 ||
							pCentDedDgrRessyaTrackLine->getHatsuOperation() == -2 ||
							pCentDedDgrRessyaTrackLine->getHatsuOperation() == -3 ||
							pCentDedDgrRessyaTrackLine->getHatsuOperation() == 4)
						{
							iChamferRight = +1;
						}
						else if (pCentDedDgrRessyaTrackLine->getHatsuOperation() == -4 ||
							pCentDedDgrRessyaTrackLine->getHatsuOperation() == -5)
						{
							iChamferRight = -1;
						}
						else if (pCentDedDgrRessyaTrackLine->getHatsuOperation() == 0 ||
							pCentDedDgrRessyaTrackLine->getHatsuOperation() == 1 ||
							pCentDedDgrRessyaTrackLine->getHatsuOperation() == 3)
						{
							iChamferRight = 0;
						}
						/**
							次列車が存在する場合、次列車接続作業を行う番線の横線は、次列車に委任するので、ここでは描写しません。
						*/
						else if (pCentDedDgrRessyaTrackLine->getHatsuOperation() == 5)
						{
							continue;
						}
					}
					else
					{
						Zaisen aZaisenNext = pCentDedDgrRessyaTrackLine->getZaisen(idxz + 1);
						if ((aZaisen.iRessyaTrack > aZaisenNext.iRessyaTrack &&
							pCentDedDgrRessya->getRessyahoukou() == Ressyahoukou_Kudari) ||
							(aZaisen.iRessyaTrack < aZaisenNext.iRessyaTrack &&
								pCentDedDgrRessya->getRessyahoukou() == Ressyahoukou_Nobori))
						{
							iChamferRight = -1;
						}
						else
						{
							iChamferRight = +1;
						}
					}

					RessyaTrackHorizontalLineDraw(
						iX_Left_Dcd,
						iX_Right_Dcd,
						iY_Dcd,
						pCentDedDgrRessya,
						iChamferLeft,
						iChamferRight);

					if (!aZaisen.strOperationNumber.empty() &&
						pCentDedDgrRessyaTrackLine->getChakuOperation() != 3 &&
						pCentDedDgrRessyaTrackLine->getChakuOperation() != 4 &&
						pCentDedDgrRessyaTrackLine->getHatsuOperation() != 3 &&
						pCentDedDgrRessyaTrackLine->getHatsuOperation() != 4)
					{
						int iYShift;
						if (pCentDedDgrRessya->getRessyahoukou() == Ressyahoukou_Kudari)
						{
							iYShift = -1;
						}
						else
						{
							iYShift = 1;
						}
						OperationNumberDraw(
							pCentDedDgrRessya,
							aZaisen.strOperationNumber,
							(iX_Left_Dcd+ iX_Right_Dcd)/2,
							iY_Dcd,
							0,
							iYShift);
					}

					if (iX_Left_Dcd == iX_Right_Dcd &&
						!(idxz == 0 && pCentDedDgrRessyaTrackLine->getChakuOperation() == 3) &&
						!(idxz == pCentDedDgrRessyaTrackLine->getZaisenCount() - 1
							&& pCentDedDgrRessyaTrackLine->getHatsuOperation() == 3))
					{
						//if (pCentDedDgrRessyaTrackLine->getIsTeisya()) {
						if (pCentDedDgrRessyaTrackLine->getTsuukaTeisya() > 0)
						{
							CdPenProp	aCdPenProp(1, CdColorProp(0, 0, 0), CdPenProp::SOLID);
							CdBrushProp	aCdBrushProp(CdColorProp(0, 0, 0), CdBrushProp::SOLID);
							int idxRessyasyubetsu = pCentDedDgrRessya->getRessyasyubetsuIndex();
							if (0 <= idxRessyasyubetsu &&
								idxRessyasyubetsu < getCentDedDgrDia()->getMuCentDedDgrRessyasyubetsu()->size())
							{
								const CentDedDgrRessyasyubetsu* pCentDedDgrRessyasyubetsu =
									getCentDedDgrDia()->getMuCentDedDgrRessyasyubetsu()->get(idxRessyasyubetsu);
								if (m_bDisplayParentSyubetsu && pCentDedDgrRessyasyubetsu->getParentSyubetsuIndex() >= 0)
								{
									pCentDedDgrRessyasyubetsu = getCentDedDgrDia()
										->getMuCentDedDgrRessyasyubetsu()->get(pCentDedDgrRessyasyubetsu->getParentSyubetsuIndex());
								}
								CentDedRessyasyubetsu::CdDiagramLineStyle	aCdDiagramLineStyle =
									pCentDedDgrRessyasyubetsu->getCdDiagramLineStyle();

								aCdPenProp.setColor(aCdDiagramLineStyle.getDiagramSenColor());
								if (pCentDedDgrRessyaTrackLine->getTsuukaTeisya() == 1) 
								{
									aCdBrushProp.setColor(aCdDiagramLineStyle.getDiagramSenColor());
								}
								else
								{
									aCdBrushProp.setStyle(CdBrushProp::NULLBRUSH);
								}
							}
#pragma omp critical
							{
								Ou<CGdiHPenHolder>	pHPenHolder = m_pIfDcdTarget->createGdiHPenHolder(aCdPenProp);
								HPEN hPenPrev = (HPEN)SelectObject(m_pIfDcdTarget->getHdc(), pHPenHolder->getHPen());

								//CdBrushProp	aCdBrushProp(CdColorProp(0, 0, 0), CdBrushProp::NULLBRUSH);
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
						}
						else/* if (iX_Left_Dcd == iX_Right_Dcd)*/
						{
							CdPenProp	aCdPenProp(1, CdColorProp(0, 0, 0), CdPenProp::SOLID);
							int idxRessyasyubetsu = pCentDedDgrRessya->getRessyasyubetsuIndex();
							if (0 <= idxRessyasyubetsu &&
								idxRessyasyubetsu < getCentDedDgrDia()->getMuCentDedDgrRessyasyubetsu()->size())
							{
								const CentDedDgrRessyasyubetsu* pCentDedDgrRessyasyubetsu =
									getCentDedDgrDia()->getMuCentDedDgrRessyasyubetsu()->get(idxRessyasyubetsu);
								if (m_bDisplayParentSyubetsu && pCentDedDgrRessyasyubetsu->getParentSyubetsuIndex() >= 0)
								{
									pCentDedDgrRessyasyubetsu = getCentDedDgrDia()
										->getMuCentDedDgrRessyasyubetsu()->get(pCentDedDgrRessyasyubetsu->getParentSyubetsuIndex());
								}
								CentDedRessyasyubetsu::CdDiagramLineStyle	aCdDiagramLineStyle =
									pCentDedDgrRessyasyubetsu->getCdDiagramLineStyle();

								aCdPenProp.setColor(aCdDiagramLineStyle.getDiagramSenColor());
							}
#pragma omp critical
							{
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
				}

			}

			/**
				入換作業を含む場合の、番線間移動の縦線です。
			*/
			for (int idxz = 1; idxz < pCentDedDgrRessyaTrackLine->getZaisenCount(); idxz++)
			{
				//入換作業の縦線を描写します
				// --------------------------------
				//	番線線を囲む矩形領域を求める
				// --------------------------------
				Zaisen aZaisenPrev = pCentDedDgrRessyaTrackLine->getZaisen(idxz - 1);
				Zaisen aZaisen = pCentDedDgrRessyaTrackLine->getZaisen(idxz);

				DcdPos posxDgrKiten = aZaisenPrev.iDgrXPosHatsu + iShiftSecond;
				DcdPos posxDgrSyuuten = aZaisen.iDgrXPosChaku + iShiftSecond;

				if (zonexDgrPosOnDgrZone(posxDgrKiten, posxDgrSyuuten))
				{

					CdDcdPosXy	posDcdRessyaTrackKiten;
					CdDcdPosXy	posDcdRessyaTrackSyuuten;
					/**
						番線が非表示の場合は、表示形式が変わります。
						両方非表示の場合は縦線自体が非表示、片方非表示の場合は、番線間の間隔*0.5だけ"垂直の"縦線を表示します。
						(入換発時刻と入換着時刻が異なり、線が斜めになる場合も、垂直にする)
					*/
					if (getEkiTrackExsit(pCentDedDgrRessya->getRessyahoukou(),
						pCentDedDgrRessyaTrackLine->getEkiOrder(),
						aZaisenPrev.iRessyaTrack) &&
						getEkiTrackExsit(pCentDedDgrRessya->getRessyahoukou(),
							pCentDedDgrRessyaTrackLine->getEkiOrder(),
							aZaisen.iRessyaTrack))
					{
						posDcdRessyaTrackKiten.setX(XDgrToDcd(posxDgrKiten));
						posDcdRessyaTrackSyuuten.setX(XDgrToDcd(posxDgrSyuuten));
						posDcdRessyaTrackKiten.setY(
							YEkiTrackDgrToDcd(pCentDedDgrRessya->getRessyahoukou(),
								pCentDedDgrRessyaTrackLine->getEkiOrder(),
								aZaisenPrev.iRessyaTrack));
						posDcdRessyaTrackSyuuten.setY(
							YEkiTrackDgrToDcd(pCentDedDgrRessya->getRessyahoukou(),
								pCentDedDgrRessyaTrackLine->getEkiOrder(),
								aZaisen.iRessyaTrack));
					}
					else if (getEkiTrackExsit(pCentDedDgrRessya->getRessyahoukou(),
						pCentDedDgrRessyaTrackLine->getEkiOrder(),
						aZaisenPrev.iRessyaTrack))
					{
						posDcdRessyaTrackKiten.setX(XDgrToDcd(posxDgrKiten));
						posDcdRessyaTrackKiten.setY(
							YEkiTrackDgrToDcd(pCentDedDgrRessya->getRessyahoukou(),
								pCentDedDgrRessyaTrackLine->getEkiOrder(),
								aZaisenPrev.iRessyaTrack));

						posDcdRessyaTrackSyuuten.setX(posDcdRessyaTrackKiten.getX());
						if (aZaisenPrev.iRessyaTrack < aZaisen.iRessyaTrack)
						{
							posDcdRessyaTrackSyuuten.setY(posDcdRessyaTrackKiten.getY() + m_iYDcdDiagramDefaultSecondLength * 0.5);
						}
						else
						{
							posDcdRessyaTrackSyuuten.setY(posDcdRessyaTrackKiten.getY() - m_iYDcdDiagramDefaultSecondLength * 0.5);
						}
					}
					else if (getEkiTrackExsit(pCentDedDgrRessya->getRessyahoukou(),
						pCentDedDgrRessyaTrackLine->getEkiOrder(),
						aZaisen.iRessyaTrack))
					{
						posDcdRessyaTrackSyuuten.setX(XDgrToDcd(posxDgrSyuuten));
						posDcdRessyaTrackSyuuten.setY(
							YEkiTrackDgrToDcd(pCentDedDgrRessya->getRessyahoukou(),
								pCentDedDgrRessyaTrackLine->getEkiOrder(),
								aZaisen.iRessyaTrack));

						posDcdRessyaTrackKiten.setX(posDcdRessyaTrackSyuuten.getX());
						if (aZaisenPrev.iRessyaTrack < aZaisen.iRessyaTrack)
						{
							posDcdRessyaTrackKiten.setY(posDcdRessyaTrackSyuuten.getY() - m_iYDcdDiagramDefaultSecondLength * 0.5);
						}
						else
						{
							posDcdRessyaTrackKiten.setY(posDcdRessyaTrackSyuuten.getY() + m_iYDcdDiagramDefaultSecondLength * 0.5);
						}
					}
					else
					{
						continue;
					}

					//#pragma omp critical
					RessyaTrackVerticalLineDraw(
						posDcdRessyaTrackKiten,
						posDcdRessyaTrackSyuuten,
						pCentDedDgrRessya);
				}
			}
			
			/**
				当駅に到着した列車の、到着→最初の番線の縦線および、補助列車線です。
			*/
			if (pCentDedDgrRessyaTrackLine->getChakuOperation() < 0)
			{
				// --------------------------------
				//	番線線を囲む矩形領域を求める
				// --------------------------------
				Zaisen aZaisen = pCentDedDgrRessyaTrackLine->getZaisen(0);

				DcdPos posxDgrKiten = aZaisen.iDgrXPosChaku + iShiftSecond;

				/**
					到着番線が非表示の場合は、縦線は表示されません。また補助列車線も表示されません。
				*/
				if (zonexDgrPosOnDgrZone(posxDgrKiten, posxDgrKiten) && 
					getEkiTrackExsit(pCentDedDgrRessya->getRessyahoukou(),
						pCentDedDgrRessyaTrackLine->getEkiOrder(),
						aZaisen.iRessyaTrack))
				{
					CdDcdPosXy	posDcdRessyaTrackKiten;
					CdDcdPosXy	posDcdRessyaTrackSyuuten;
					posDcdRessyaTrackKiten.setX(XDgrToDcd(posxDgrKiten));
					posDcdRessyaTrackSyuuten.setX(XDgrToDcd(posxDgrKiten));

					if (pCentDedDgrRessyaTrackLine->getChakuOperation() == -4 ||
						pCentDedDgrRessyaTrackLine->getChakuOperation() == -5)
					{
						posDcdRessyaTrackKiten.setY(
							YDgrToDcd(pCentDedDgrRessyaTrackLine->getEkiOrder(),
								pCentDedDgrRessya->getRessyahoukou(),
								false));
					}
					else
					{
						posDcdRessyaTrackKiten.setY(
							YDgrToDcd(pCentDedDgrRessyaTrackLine->getEkiOrder(),
								pCentDedDgrRessya->getRessyahoukou(),
								true));
					}
					posDcdRessyaTrackSyuuten.setY(
						YEkiTrackDgrToDcd(pCentDedDgrRessya->getRessyahoukou(),
							pCentDedDgrRessyaTrackLine->getEkiOrder(),
							aZaisen.iRessyaTrack));

					//#pragma omp critical
					RessyaTrackVerticalLineDraw(
						posDcdRessyaTrackKiten,
						posDcdRessyaTrackSyuuten,
						pCentDedDgrRessya);

					//ChakuOperationが-2の場合は、列車の着側に補助列車線を描写します(通常)
					//ChakuOperationが-4の場合は、列車の発側に補助列車線を描写します(反転)
					if (pCentDedDgrRessyaTrackLine->getChakuOperation() == -2 ||
						pCentDedDgrRessyaTrackLine->getChakuOperation() == -4)
					{
						DcdPos posxDgrKitenShift = aZaisen.iDgrXPosChaku + iShiftSecond - 30;

						if (zonexDgrPosOnDgrZone(posxDgrKitenShift, posxDgrKiten))
						{
							CdDcdPosXy	posDcdRessyaTrackKitenShift;
							posDcdRessyaTrackKitenShift.setX(XDgrToDcd(posxDgrKitenShift));
							if ((pCentDedDgrRessya->getRessyahoukou() == Ressyahoukou_Kudari &&
								pCentDedDgrRessyaTrackLine->getChakuOperation() == -2) ||
								(pCentDedDgrRessya->getRessyahoukou() == Ressyahoukou_Nobori &&
									pCentDedDgrRessyaTrackLine->getChakuOperation() == -4))
							{
								posDcdRessyaTrackKitenShift.setY(posDcdRessyaTrackKiten.getY() - m_iYDcd30SecondLength);
							}
							else
							{
								posDcdRessyaTrackKitenShift.setY(posDcdRessyaTrackKiten.getY() + m_iYDcd30SecondLength);
							}
							//#pragma omp critical
							RessyaTrackVerticalLineDraw(
								posDcdRessyaTrackKiten,
								posDcdRessyaTrackKitenShift,
								pCentDedDgrRessya);
						}
					}
				}
			}

			/**
				出区の丸印および運用番号の描写です。
			*/
			if (pCentDedDgrRessyaTrackLine->getChakuOperation() == 3)
			{
				// --------------------------------
				//	出区マークを描画する位置を算出
				// --------------------------------

				Zaisen aZaisen = pCentDedDgrRessyaTrackLine->getZaisen(0);

				/**
					出区番線が非表示の場合は、○印は表示されません。
				*/
				if (getEkiTrackExsit(pCentDedDgrRessya->getRessyahoukou(),
						pCentDedDgrRessyaTrackLine->getEkiOrder(),
						aZaisen.iRessyaTrack))
				{
					int iYShift;
					if (pCentDedDgrRessyaTrackLine->getZaisenCount() == 1)
					{
						if (pCentDedDgrRessyaTrackLine->getHatsuOperation() == -4 ||
							pCentDedDgrRessyaTrackLine->getHatsuOperation() == -5)
						{
							iYShift = 1;
						}
						else
						{
							iYShift = -1;
						}
					}
					else
					{
						Zaisen aZaisenNext = pCentDedDgrRessyaTrackLine->getZaisen(1);
						if (aZaisen.iRessyaTrack > aZaisenNext.iRessyaTrack)
						{
							if (pCentDedDgrRessya->getRessyahoukou() == Ressyahoukou_Kudari)
							{
								iYShift = 1;
							}
							else
							{
								iYShift = -1;
							}
						}
						else
						{
							if (pCentDedDgrRessya->getRessyahoukou() == Ressyahoukou_Kudari)
							{
								iYShift = -1;
							}
							else
							{
								iYShift = 1;
							}
						}

					}

					DcdPos posxDgrKiten = aZaisen.iDgrXPosChaku + iShiftSecond;

					if (zonexDgrPosOnDgrZone(posxDgrKiten, posxDgrKiten))
					{
						int iY_DcdDown = YEkiTrackDgrToDcd(
							pCentDedDgrRessya->getRessyahoukou(),
							pCentDedDgrRessyaTrackLine->getEkiOrder(),
							aZaisen.iRessyaTrack);
						int iY_DcdUp = iY_DcdDown;
						if (pCentDedDgrRessya->getRessyahoukou() == Ressyahoukou_Kudari)
						{
							iY_DcdUp += iYShift * m_iYDcdDiagramDefaultSecondLength;
						}
						else
						{
							iY_DcdUp -= iYShift * m_iYDcdDiagramDefaultSecondLength;
						}
						int iX_DcdLeft = XDgrToDcd(posxDgrKiten)
							- m_iYDcdDiagramDefaultSecondLength / 2;
						int iX_DcdRight = XDgrToDcd(posxDgrKiten)
							+ m_iYDcdDiagramDefaultSecondLength / 2;

#pragma omp critical
						{
							CdPenProp	aCdPenProp(1, CdColorProp(0, 0, 0), CdPenProp::SOLID);
							int idxRessyasyubetsu = pCentDedDgrRessya->getRessyasyubetsuIndex();
							if (0 <= idxRessyasyubetsu &&
								idxRessyasyubetsu < getCentDedDgrDia()->getMuCentDedDgrRessyasyubetsu()->size())
							{
								const CentDedDgrRessyasyubetsu* pCentDedDgrRessyasyubetsu =
									getCentDedDgrDia()->getMuCentDedDgrRessyasyubetsu()->get(idxRessyasyubetsu);
								if (m_bDisplayParentSyubetsu && pCentDedDgrRessyasyubetsu->getParentSyubetsuIndex() >= 0)
								{
									pCentDedDgrRessyasyubetsu = getCentDedDgrDia()
										->getMuCentDedDgrRessyasyubetsu()->get(pCentDedDgrRessyasyubetsu->getParentSyubetsuIndex());
								}
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
								iX_DcdLeft,
								iY_DcdUp,
								iX_DcdRight,
								iY_DcdDown);

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
						if (!aZaisen.strOperationNumber.empty())
						{
							//int iYShift = -1;
							//if (pCentDedDgrRessyaTrackLine->getHatsuOperation() == -4 ||
							//	pCentDedDgrRessyaTrackLine->getHatsuOperation() == -5)
							//{
							//	iYShift = 1;
							//}
							OperationNumberDraw(
								pCentDedDgrRessya,
								aZaisen.strOperationNumber,
								iX_DcdLeft,
								iY_DcdDown,
								-1,
								iYShift);
						}
					}
				}
			}

			/**
				路線外始発における斜め線および駅名・運用番号の描写
			*/
			if (pCentDedDgrRessyaTrackLine->getChakuOperation() == 4)
			{
				Zaisen aZaisen = pCentDedDgrRessyaTrackLine->getZaisen(0);

				/**
					到着番線が非表示の場合は、路線外始発は表示されません。
				*/
				if (getEkiTrackExsit(pCentDedDgrRessya->getRessyahoukou(),
					pCentDedDgrRessyaTrackLine->getEkiOrder(),
					aZaisen.iRessyaTrack))
				{
					DcdPos posxDgrKiten = aZaisen.iDgrXPosChaku + iShiftSecond - (m_pCentDedDgrDia->getDgrYSizeEkikanDefault() * 0.7);
					DcdPos posxDgrSyuuten = aZaisen.iDgrXPosChaku + iShiftSecond;

					if (zonexDgrPosOnDgrZone(posxDgrKiten, posxDgrSyuuten))
					{
						CdDcdPosXy	posDcdRessyaTrackKiten;
						CdDcdPosXy	posDcdRessyaTrackSyuuten;
						posDcdRessyaTrackKiten.setX(XDgrToDcd(posxDgrKiten));
						posDcdRessyaTrackSyuuten.setX(XDgrToDcd(posxDgrSyuuten));
						posDcdRessyaTrackSyuuten.setY(
							YEkiTrackDgrToDcd(pCentDedDgrRessya->getRessyahoukou(),
								pCentDedDgrRessyaTrackLine->getEkiOrder(),
								aZaisen.iRessyaTrack));
						if (pCentDedDgrRessyaTrackLine->getHatsuOperation() == -4 ||
							pCentDedDgrRessyaTrackLine->getHatsuOperation() == -5)
						{
							if (pCentDedDgrRessya->getRessyahoukou() == Ressyahoukou_Kudari)
							{
								posDcdRessyaTrackKiten.setY(posDcdRessyaTrackSyuuten.getY() +
									m_iYDcdDiagramDefaultSecondLength * 0.7);
							}
							else
							{
								posDcdRessyaTrackKiten.setY(posDcdRessyaTrackSyuuten.getY() -
									m_iYDcdDiagramDefaultSecondLength * 0.7);
							}
						}
						else
						{
							if (pCentDedDgrRessya->getRessyahoukou() == Ressyahoukou_Kudari)
							{
								posDcdRessyaTrackKiten.setY(posDcdRessyaTrackSyuuten.getY() -
									m_iYDcdDiagramDefaultSecondLength * 0.7);
							}
							else
							{
								posDcdRessyaTrackKiten.setY(posDcdRessyaTrackSyuuten.getY() +
									m_iYDcdDiagramDefaultSecondLength * 0.7);
							}
						}

						//#pragma omp critical
						RessyaTrackVerticalLineDraw(
							posDcdRessyaTrackKiten,
							posDcdRessyaTrackSyuuten,
							pCentDedDgrRessya);

						tstring strOuterEkimeiAndOperationNumber;

						int iEkiIndex = getCentDedDgrDia()->EkiIndexOfEkiOrder(
							pCentDedDgrRessya->getRessyahoukou(),
							pCentDedDgrRessyaTrackLine->getEkiOrder());
						const CentDedDgrEki aCentDedDgrEki = getCentDedDgrDia()
							->getCentDedDgrEkiCont()->get(iEkiIndex);
						strOuterEkimeiAndOperationNumber = aCentDedDgrEki.getOuterTerminalEkimei(
							pCentDedDgrRessyaTrackLine->getOuterEkiIndex());

						if (!aZaisen.strOperationNumber.empty())
						{
							strOuterEkimeiAndOperationNumber += _T(" ");
							strOuterEkimeiAndOperationNumber += aZaisen.strOperationNumber;
						}

						if (!strOuterEkimeiAndOperationNumber.empty())
						{
							int iYShift = -1;
							if (pCentDedDgrRessyaTrackLine->getHatsuOperation() == -4 ||
								pCentDedDgrRessyaTrackLine->getHatsuOperation() == -5)
							{
								iYShift = 1;
							}
							OuterEkimeiAndOperationNumberDraw(
								pCentDedDgrRessya/*->getOperationNumber()*/,
								strOuterEkimeiAndOperationNumber,
								posDcdRessyaTrackKiten.getX(),
								posDcdRessyaTrackSyuuten.getY(),
								-1,
								iYShift);
						}
					}
				}
			}

			/**
				解結作業における、△または▽印の描写です。
			*/
			if (pCentDedDgrRessyaTrackLine->getChakuOperation() == 2)
			{
				// --------------------------------
				//	解結マークを描画する位置を算出
				// --------------------------------
				Zaisen aZaisen = pCentDedDgrRessyaTrackLine->getZaisen(0);
				/**
					解結番線が非表示の場合は、○印は表示されません。
				*/
				if (getEkiTrackExsit(pCentDedDgrRessya->getRessyahoukou(),
					pCentDedDgrRessyaTrackLine->getEkiOrder(),
					aZaisen.iRessyaTrack))
				{
					CdDcdPosXy	posTriangle_Dcd[3];

					DcdPos posxDgrKiten = aZaisen.iDgrXPosChaku + iShiftSecond;

					if (zonexDgrPosOnDgrZone(posxDgrKiten, posxDgrKiten))
					{
						//iX_Dcd,iY_Dcd = 列車情報を表示する駅の発時刻の座標
						//	単位は、 IfDcdTarget の座標系
						// --------------------------------
						int iY_DcdUp = YEkiTrackDgrToDcd(
							pCentDedDgrRessya->getRessyahoukou(),
							pCentDedDgrRessyaTrackLine->getEkiOrder(),
							aZaisen.iRessyaTrack);
						int iY_DcdDown = iY_DcdUp;
						if (pCentDedDgrRessya->getRessyahoukou() == Ressyahoukou_Kudari)
						{
							iY_DcdDown += m_iYDcdDiagramDefaultSecondLength;
						}
						else
						{
							iY_DcdDown -= m_iYDcdDiagramDefaultSecondLength;
						}
						int iX_DcdCenter = XDgrToDcd(posxDgrKiten);
						int iX_DcdLeft = iX_DcdCenter
							- m_iYDcdDiagramDefaultSecondLength / 2;
						int iX_DcdRight = iX_DcdCenter
							+ m_iYDcdDiagramDefaultSecondLength / 2;

						posTriangle_Dcd[0].setX((DcdPos)iX_DcdCenter);
						posTriangle_Dcd[0].setY((DcdPos)iY_DcdUp);
						posTriangle_Dcd[1].setX((DcdPos)iX_DcdLeft);
						posTriangle_Dcd[1].setY((DcdPos)iY_DcdDown);
						posTriangle_Dcd[2].setX((DcdPos)iX_DcdRight);
						posTriangle_Dcd[2].setY((DcdPos)iY_DcdDown);

#pragma omp critical
						{
							CdPenProp	aCdPenProp(1, CdColorProp(0, 0, 0), CdPenProp::SOLID);
							CdBrushProp	aCdBrushProp(CdColorProp(0, 0, 0), CdBrushProp::SOLID);
							int idxRessyasyubetsu = pCentDedDgrRessya->getRessyasyubetsuIndex();
							if (0 <= idxRessyasyubetsu &&
								idxRessyasyubetsu < getCentDedDgrDia()->getMuCentDedDgrRessyasyubetsu()->size())
							{
								const CentDedDgrRessyasyubetsu* pCentDedDgrRessyasyubetsu =
									getCentDedDgrDia()->getMuCentDedDgrRessyasyubetsu()->get(idxRessyasyubetsu);
								if (m_bDisplayParentSyubetsu && pCentDedDgrRessyasyubetsu->getParentSyubetsuIndex() >= 0)
								{
									pCentDedDgrRessyasyubetsu = getCentDedDgrDia()
										->getMuCentDedDgrRessyasyubetsu()->get(pCentDedDgrRessyasyubetsu->getParentSyubetsuIndex());
								}
								CentDedRessyasyubetsu::CdDiagramLineStyle	aCdDiagramLineStyle =
									pCentDedDgrRessyasyubetsu->getCdDiagramLineStyle();

								aCdPenProp.setColor(aCdDiagramLineStyle.getDiagramSenColor());
								aCdBrushProp.setColor(aCdDiagramLineStyle.getDiagramSenColor());
							}
							Ou<CGdiHPenHolder>	pHPenHolder = m_pIfDcdTarget->createGdiHPenHolder(aCdPenProp);
							HPEN hPenPrev = (HPEN)SelectObject(m_pIfDcdTarget->getHdc(), pHPenHolder->getHPen());

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
				}
			}

			/**
				当駅を出発する列車の、最後の番線→出発の縦線および、補助列車線です。
			*/
			if (pCentDedDgrRessyaTrackLine->getHatsuOperation() < 0)
			{
				// --------------------------------
				//	番線線を囲む矩形領域を求める
				// --------------------------------
				Zaisen aZaisen = pCentDedDgrRessyaTrackLine->getZaisen(INT_MAX);

				DcdPos posxDgrKiten = aZaisen.iDgrXPosHatsu + iShiftSecond;

				/**
					出発番線が非表示の場合は、縦線は表示されません。また補助列車線も表示されません。
				*/
				if (zonexDgrPosOnDgrZone(posxDgrKiten, posxDgrKiten) &&
					getEkiTrackExsit(pCentDedDgrRessya->getRessyahoukou(),
						pCentDedDgrRessyaTrackLine->getEkiOrder(),
						aZaisen.iRessyaTrack))
				{

					CdDcdPosXy	posDcdRessyaTrackKiten;
					CdDcdPosXy	posDcdRessyaTrackSyuuten;
					posDcdRessyaTrackKiten.setX(XDgrToDcd(posxDgrKiten));
					posDcdRessyaTrackSyuuten.setX(XDgrToDcd(posxDgrKiten));
					posDcdRessyaTrackKiten.setY(
						YEkiTrackDgrToDcd(pCentDedDgrRessya->getRessyahoukou(),
							pCentDedDgrRessyaTrackLine->getEkiOrder(),
							aZaisen.iRessyaTrack));
					if (pCentDedDgrRessyaTrackLine->getHatsuOperation() == -4 ||
						pCentDedDgrRessyaTrackLine->getHatsuOperation() == -5)
					{
						posDcdRessyaTrackSyuuten.setY(
							YDgrToDcd(pCentDedDgrRessyaTrackLine->getEkiOrder(),
								pCentDedDgrRessya->getRessyahoukou(),
								true));
					}
					else
					{
						posDcdRessyaTrackSyuuten.setY(
							YDgrToDcd(pCentDedDgrRessyaTrackLine->getEkiOrder(),
								pCentDedDgrRessya->getRessyahoukou(),
								false));
					}
					//#pragma omp critical
					RessyaTrackVerticalLineDraw(
						posDcdRessyaTrackKiten,
						posDcdRessyaTrackSyuuten,
						pCentDedDgrRessya);

					//HatsuOperationが-2の場合は、列車の発側に補助列車線を描写します(通常)
					//HatsuOperationが-4の場合は、列車の着側に補助列車線を描写します(反転)
					if (pCentDedDgrRessyaTrackLine->getHatsuOperation() == -2 ||
						pCentDedDgrRessyaTrackLine->getHatsuOperation() == -4)
					{
						DcdPos posxDgrSyuutenShift = aZaisen.iDgrXPosHatsu + iShiftSecond + 30;

						if (zonexDgrPosOnDgrZone(posxDgrKiten, posxDgrSyuutenShift))
						{
							CdDcdPosXy	posDcdRessyaTrackSyuutenShift;
							posDcdRessyaTrackSyuutenShift.setX(XDgrToDcd(posxDgrSyuutenShift));
							if ((pCentDedDgrRessya->getRessyahoukou() == Ressyahoukou_Kudari &&
								pCentDedDgrRessyaTrackLine->getHatsuOperation() == -2) ||
								(pCentDedDgrRessya->getRessyahoukou() == Ressyahoukou_Nobori &&
									pCentDedDgrRessyaTrackLine->getHatsuOperation() == -4))
							{
								posDcdRessyaTrackSyuutenShift.setY(posDcdRessyaTrackSyuuten.getY() + m_iYDcd30SecondLength);
							}
							else
							{
								posDcdRessyaTrackSyuutenShift.setY(posDcdRessyaTrackSyuuten.getY() - m_iYDcd30SecondLength);
							}
							//#pragma omp critical
							RessyaTrackVerticalLineDraw(
								posDcdRessyaTrackSyuuten,
								posDcdRessyaTrackSyuutenShift,
								pCentDedDgrRessya);
						}
					}
				}
			}
			/**
				入区作業における、△または▽印の描写です。
			*/
			if (pCentDedDgrRessyaTrackLine->getHatsuOperation() == 3)
			{
				// --------------------------------
				//	入区マークを描画する位置を算出
				// --------------------------------
				Zaisen aZaisen = pCentDedDgrRessyaTrackLine->getZaisen(INT_MAX);

				/**
					入区番線が非表示の場合は、△印は表示されません。
				*/
				if (getEkiTrackExsit(pCentDedDgrRessya->getRessyahoukou(),
					pCentDedDgrRessyaTrackLine->getEkiOrder(),
					aZaisen.iRessyaTrack))
				{
					CdDcdPosXy	posTriangle_Dcd[3];
					int iYShift;
					if (pCentDedDgrRessyaTrackLine->getZaisenCount() == 1)
					{
						if (pCentDedDgrRessyaTrackLine->getChakuOperation() == -4 ||
							pCentDedDgrRessyaTrackLine->getChakuOperation() == -5)
						{
							iYShift = -1;
						}
						else
						{
							iYShift = 1;
						}
					}
					else
					{
						Zaisen aZaisenPrev = pCentDedDgrRessyaTrackLine->getZaisen(
							pCentDedDgrRessyaTrackLine->getZaisenCount() - 2);
						if (aZaisen.iRessyaTrack > aZaisenPrev.iRessyaTrack)
						{
							if (pCentDedDgrRessya->getRessyahoukou() == Ressyahoukou_Kudari)
							{
								iYShift = 1;
							}
							else
							{
								iYShift = -1;
							}
						}
						else
						{
							if (pCentDedDgrRessya->getRessyahoukou() == Ressyahoukou_Kudari)
							{
								iYShift = -1;
							}
							else
							{
								iYShift = 1;
							}
						}

					}

					DcdPos posxDgrKiten = aZaisen.iDgrXPosHatsu + iShiftSecond;
					if (zonexDgrPosOnDgrZone(posxDgrKiten, posxDgrKiten))
					{
						//iX_Dcd,iY_Dcd = 列車情報を表示する駅の発時刻の座標
						//	単位は、 IfDcdTarget の座標系
						// --------------------------------
						int iY_DcdUp = YEkiTrackDgrToDcd(
							pCentDedDgrRessya->getRessyahoukou(),
							pCentDedDgrRessyaTrackLine->getEkiOrder(),
							aZaisen.iRessyaTrack);
						int iY_DcdDown = iY_DcdUp;
						if (pCentDedDgrRessya->getRessyahoukou() == Ressyahoukou_Kudari)
						{
							iY_DcdDown += iYShift * m_iYDcdDiagramDefaultSecondLength;
						}
						else
						{
							iY_DcdDown -= iYShift * m_iYDcdDiagramDefaultSecondLength;
						}
						int iX_DcdCenter = XDgrToDcd(posxDgrKiten);
						int iX_DcdLeft = iX_DcdCenter
							- m_iYDcdDiagramDefaultSecondLength / 2;
						int iX_DcdRight = iX_DcdCenter
							+ m_iYDcdDiagramDefaultSecondLength / 2;

						posTriangle_Dcd[0].setX((DcdPos)iX_DcdCenter);
						posTriangle_Dcd[0].setY((DcdPos)iY_DcdUp);
						posTriangle_Dcd[1].setX((DcdPos)iX_DcdLeft);
						posTriangle_Dcd[1].setY((DcdPos)iY_DcdDown);
						posTriangle_Dcd[2].setX((DcdPos)iX_DcdRight);
						posTriangle_Dcd[2].setY((DcdPos)iY_DcdDown);

#pragma omp critical
						{
							CdPenProp	aCdPenProp(1, CdColorProp(0, 0, 0), CdPenProp::SOLID);
							int idxRessyasyubetsu = pCentDedDgrRessya->getRessyasyubetsuIndex();
							if (0 <= idxRessyasyubetsu &&
								idxRessyasyubetsu < getCentDedDgrDia()->getMuCentDedDgrRessyasyubetsu()->size())
							{
								const CentDedDgrRessyasyubetsu* pCentDedDgrRessyasyubetsu =
									getCentDedDgrDia()->getMuCentDedDgrRessyasyubetsu()->get(idxRessyasyubetsu);
								if (m_bDisplayParentSyubetsu && pCentDedDgrRessyasyubetsu->getParentSyubetsuIndex() >= 0)
								{
									pCentDedDgrRessyasyubetsu = getCentDedDgrDia()
										->getMuCentDedDgrRessyasyubetsu()->get(pCentDedDgrRessyasyubetsu->getParentSyubetsuIndex());
								}
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

						if (!aZaisen.strOperationNumber.empty())
						{
							OperationNumberDraw(
								pCentDedDgrRessya,
								aZaisen.strOperationNumber,
								iX_DcdRight,
								iY_DcdUp,
								1,
								iYShift);
						}
					}
				}
			}

			/**
				路線外終着における斜め線の描写および、駅名・運番の描写です
			*/
			if (pCentDedDgrRessyaTrackLine->getHatsuOperation() == 4)
			{
				//路線外終着における斜め線の描写
				Zaisen aZaisen = pCentDedDgrRessyaTrackLine->getZaisen(INT_MAX);

				/**
					出発番線が非表示の場合は、路線外終着は表示されません。
				*/
				if (getEkiTrackExsit(pCentDedDgrRessya->getRessyahoukou(),
					pCentDedDgrRessyaTrackLine->getEkiOrder(),
					aZaisen.iRessyaTrack))
				{
					DcdPos posxDgrKiten = aZaisen.iDgrXPosHatsu + iShiftSecond;
					DcdPos posxDgrSyuuten = aZaisen.iDgrXPosHatsu + iShiftSecond + (m_pCentDedDgrDia->getDgrYSizeEkikanDefault() * 0.7);

					if (zonexDgrPosOnDgrZone(posxDgrKiten, posxDgrSyuuten))
					{
						CdDcdPosXy	posDcdRessyaTrackKiten;
						CdDcdPosXy	posDcdRessyaTrackSyuuten;
						posDcdRessyaTrackKiten.setX(XDgrToDcd(posxDgrKiten));
						posDcdRessyaTrackSyuuten.setX(XDgrToDcd(posxDgrSyuuten));
						posDcdRessyaTrackKiten.setY(
							YEkiTrackDgrToDcd(pCentDedDgrRessya->getRessyahoukou(),
								pCentDedDgrRessyaTrackLine->getEkiOrder(),
								aZaisen.iRessyaTrack));
						if (pCentDedDgrRessyaTrackLine->getChakuOperation() == -4 ||
							pCentDedDgrRessyaTrackLine->getChakuOperation() == -5)
						{
							if (pCentDedDgrRessya->getRessyahoukou() == Ressyahoukou_Kudari)
							{
								posDcdRessyaTrackSyuuten.setY(posDcdRessyaTrackKiten.getY() -
									m_iYDcdDiagramDefaultSecondLength * 0.7);
							}
							else
							{
								posDcdRessyaTrackSyuuten.setY(posDcdRessyaTrackKiten.getY() +
									m_iYDcdDiagramDefaultSecondLength * 0.7);
							}
						}
						else
						{
							if (pCentDedDgrRessya->getRessyahoukou() == Ressyahoukou_Kudari)
							{
								posDcdRessyaTrackSyuuten.setY(posDcdRessyaTrackKiten.getY() +
									m_iYDcdDiagramDefaultSecondLength * 0.7);
							}
							else
							{
								posDcdRessyaTrackSyuuten.setY(posDcdRessyaTrackKiten.getY() -
									m_iYDcdDiagramDefaultSecondLength * 0.7);
							}
						}
						//#pragma omp critical
						RessyaTrackVerticalLineDraw(
							posDcdRessyaTrackKiten,
							posDcdRessyaTrackSyuuten,
							pCentDedDgrRessya);

						tstring strOuterEkimeiAndOperationNumber;
						int iEkiIndex = getCentDedDgrDia()->EkiIndexOfEkiOrder(
							pCentDedDgrRessya->getRessyahoukou(),
							pCentDedDgrRessyaTrackLine->getEkiOrder());
						const CentDedDgrEki aCentDedDgrEki = getCentDedDgrDia()
							->getCentDedDgrEkiCont()->get(iEkiIndex);
						strOuterEkimeiAndOperationNumber = aCentDedDgrEki.getOuterTerminalEkimei(
							pCentDedDgrRessyaTrackLine->getOuterEkiIndex());

						if (!aZaisen.strOperationNumber.empty())
						{
							strOuterEkimeiAndOperationNumber += _T(" ");
							strOuterEkimeiAndOperationNumber += aZaisen.strOperationNumber;
						}

						if (!strOuterEkimeiAndOperationNumber.empty())
						{
							int iYShift = 1;
							if (pCentDedDgrRessyaTrackLine->getChakuOperation() == -4 ||
								pCentDedDgrRessyaTrackLine->getChakuOperation() == -5)
							{
								iYShift = -1;
							}
							OuterEkimeiAndOperationNumberDraw(
								pCentDedDgrRessya/*->getOperationNumber()*/,
								strOuterEkimeiAndOperationNumber,
								posDcdRessyaTrackSyuuten.getX(),
								posDcdRessyaTrackKiten.getY(),
								1,
								iYShift);
						}
					}
				}
			}

			/**
				増結の丸印の描写です。
			*/
			if (pCentDedDgrRessyaTrackLine->getHatsuOperation() == 1)
			{
				// --------------------------------
				//	増結マークを描画する位置を算出
				// --------------------------------

				Zaisen aZaisen = pCentDedDgrRessyaTrackLine->getZaisen(INT_MAX);
				/**
					増結番線が非表示の場合は、○印は表示されません。
				*/
				if (getEkiTrackExsit(pCentDedDgrRessya->getRessyahoukou(),
					pCentDedDgrRessyaTrackLine->getEkiOrder(),
					aZaisen.iRessyaTrack))
				{

					DcdPos posxDgrKiten = aZaisen.iDgrXPosHatsu + iShiftSecond;

					if (zonexDgrPosOnDgrZone(posxDgrKiten, posxDgrKiten))
					{
						int iY_DcdDown = YEkiTrackDgrToDcd(
							pCentDedDgrRessya->getRessyahoukou(),
							pCentDedDgrRessyaTrackLine->getEkiOrder(),
							aZaisen.iRessyaTrack);
						int iY_DcdUp = iY_DcdDown;
						if (pCentDedDgrRessya->getRessyahoukou() == Ressyahoukou_Kudari)
						{
							iY_DcdUp -= m_iYDcdDiagramDefaultSecondLength;
						}
						else
						{
							iY_DcdUp += m_iYDcdDiagramDefaultSecondLength;
						}
						int iX_DcdLeft = XDgrToDcd(posxDgrKiten)
							- m_iYDcdDiagramDefaultSecondLength / 2;
						int iX_DcdRight = XDgrToDcd(posxDgrKiten)
							+ m_iYDcdDiagramDefaultSecondLength / 2;

#pragma omp critical
						{
							CdPenProp	aCdPenProp(1, CdColorProp(0, 0, 0), CdPenProp::SOLID);
							CdBrushProp	aCdBrushProp(CdColorProp(0, 0, 0), CdBrushProp::SOLID);
							int idxRessyasyubetsu = pCentDedDgrRessya->getRessyasyubetsuIndex();
							if (0 <= idxRessyasyubetsu &&
								idxRessyasyubetsu < getCentDedDgrDia()->getMuCentDedDgrRessyasyubetsu()->size())
							{
								const CentDedDgrRessyasyubetsu* pCentDedDgrRessyasyubetsu =
									getCentDedDgrDia()->getMuCentDedDgrRessyasyubetsu()->get(idxRessyasyubetsu);
								if (m_bDisplayParentSyubetsu && pCentDedDgrRessyasyubetsu->getParentSyubetsuIndex() >= 0)
								{
									pCentDedDgrRessyasyubetsu = getCentDedDgrDia()
										->getMuCentDedDgrRessyasyubetsu()->get(pCentDedDgrRessyasyubetsu->getParentSyubetsuIndex());
								}
								CentDedRessyasyubetsu::CdDiagramLineStyle	aCdDiagramLineStyle =
									pCentDedDgrRessyasyubetsu->getCdDiagramLineStyle();

								aCdPenProp.setColor(aCdDiagramLineStyle.getDiagramSenColor());
								aCdBrushProp.setColor(aCdDiagramLineStyle.getDiagramSenColor());
							}
							Ou<CGdiHPenHolder>	pHPenHolder = m_pIfDcdTarget->createGdiHPenHolder(aCdPenProp);
							HPEN hPenPrev = (HPEN)SelectObject(m_pIfDcdTarget->getHdc(), pHPenHolder->getHPen());

							Ou<CGdiHBrushHolder> pHBrushHolder = m_pIfDcdTarget->createGdiHBrushHolder(aCdBrushProp);
							HBRUSH hBrushPrev = (HBRUSH)SelectObject(m_pIfDcdTarget->getHdc(), pHBrushHolder->getHBrush());


							Ellipse(
								m_pIfDcdTarget->getHdc(),
								iX_DcdLeft,
								iY_DcdUp,
								iX_DcdRight,
								iY_DcdDown);

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
		}
//================================================================================================================
//================================================================================================================
//================================================================================================================
		else if(!pCentDedDgrRessyaTrackLine->getIsTrackDisplay() &&
			pCentDedDgrRessyaTrackLine->getZaisenCount() > 0)//ここから在線表表示なし駅の場合。
		{
			/**
				当駅に到着した列車の補助列車線です。
			*/
			if (pCentDedDgrRessyaTrackLine->getChakuOperation() == -2)
			{
				Zaisen aZaisen = pCentDedDgrRessyaTrackLine->getZaisen(0);

				DcdPos posxDgrKiten = aZaisen.iDgrXPosChaku + iShiftSecond - 30;
				DcdPos posxDgrSyuuten = aZaisen.iDgrXPosChaku + iShiftSecond;

				if (zonexDgrPosOnDgrZone(posxDgrKiten, posxDgrSyuuten))
				{
					CdDcdPosXy	posDcdRessyaTrackKiten;
					CdDcdPosXy	posDcdRessyaTrackSyuuten;
					posDcdRessyaTrackKiten.setX(XDgrToDcd(posxDgrKiten));
					posDcdRessyaTrackSyuuten.setX(XDgrToDcd(posxDgrSyuuten));
					posDcdRessyaTrackSyuuten.setY(
						YDgrToDcd(pCentDedDgrRessyaTrackLine->getEkiOrder(),
							pCentDedDgrRessya->getRessyahoukou(),
							true));

					if (pCentDedDgrRessya->getRessyahoukou() == Ressyahoukou_Kudari)
					{
						posDcdRessyaTrackKiten.setY(posDcdRessyaTrackSyuuten.getY() - m_iYDcd30SecondLength);
					}
					else
					{
						posDcdRessyaTrackKiten.setY(posDcdRessyaTrackSyuuten.getY() + m_iYDcd30SecondLength);
					}
					RessyaTrackVerticalLineDraw(
						posDcdRessyaTrackKiten,
						posDcdRessyaTrackSyuuten,
						pCentDedDgrRessya);
				}
			}
			if (pCentDedDgrRessyaTrackLine->getChakuOperation() == -4)
			{
				Zaisen aZaisen = pCentDedDgrRessyaTrackLine->getZaisen(0);

				DcdPos posxDgrKiten = aZaisen.iDgrXPosChaku + iShiftSecond - 30;
				DcdPos posxDgrSyuuten = aZaisen.iDgrXPosChaku + iShiftSecond;

				if (zonexDgrPosOnDgrZone(posxDgrKiten, posxDgrSyuuten))
				{
					CdDcdPosXy	posDcdRessyaTrackKiten;
					CdDcdPosXy	posDcdRessyaTrackSyuuten;
					posDcdRessyaTrackKiten.setX(XDgrToDcd(posxDgrKiten));
					posDcdRessyaTrackSyuuten.setX(XDgrToDcd(posxDgrSyuuten));
					posDcdRessyaTrackSyuuten.setY(
						YDgrToDcd(pCentDedDgrRessyaTrackLine->getEkiOrder(),
							pCentDedDgrRessya->getRessyahoukou(),
							false));
					if (pCentDedDgrRessya->getRessyahoukou() == Ressyahoukou_Kudari)
					{
						posDcdRessyaTrackKiten.setY(posDcdRessyaTrackSyuuten.getY() + m_iYDcd30SecondLength);
					}
					else
					{
						posDcdRessyaTrackKiten.setY(posDcdRessyaTrackSyuuten.getY() - m_iYDcd30SecondLength);
					}
					RessyaTrackVerticalLineDraw(
						posDcdRessyaTrackKiten,
						posDcdRessyaTrackSyuuten,
						pCentDedDgrRessya);
				}
			}

			/**
				当駅を出発する列車の補助列車線です。
			*/
			if (pCentDedDgrRessyaTrackLine->getHatsuOperation() == -2)
			{
				Zaisen aZaisen = pCentDedDgrRessyaTrackLine->getZaisen(INT_MAX);

				DcdPos posxDgrKiten = aZaisen.iDgrXPosHatsu + iShiftSecond;
				DcdPos posxDgrSyuuten = aZaisen.iDgrXPosHatsu + iShiftSecond + 30;

				if (zonexDgrPosOnDgrZone(posxDgrKiten, posxDgrSyuuten))
				{
					CdDcdPosXy	posDcdRessyaTrackKiten;
					CdDcdPosXy	posDcdRessyaTrackSyuuten;
					posDcdRessyaTrackKiten.setX(XDgrToDcd(posxDgrKiten));
					posDcdRessyaTrackSyuuten.setX(XDgrToDcd(posxDgrSyuuten));
					posDcdRessyaTrackKiten.setY(
						YDgrToDcd(pCentDedDgrRessyaTrackLine->getEkiOrder(),
							pCentDedDgrRessya->getRessyahoukou(),
							false));
					if (pCentDedDgrRessya->getRessyahoukou() == Ressyahoukou_Kudari)
					{
						posDcdRessyaTrackSyuuten.setY(posDcdRessyaTrackKiten.getY() + m_iYDcd30SecondLength);
					}
					else
					{
						posDcdRessyaTrackSyuuten.setY(posDcdRessyaTrackKiten.getY() - m_iYDcd30SecondLength);
					}
					RessyaTrackVerticalLineDraw(
						posDcdRessyaTrackKiten,
						posDcdRessyaTrackSyuuten,
						pCentDedDgrRessya);
				}
			}
			if (pCentDedDgrRessyaTrackLine->getHatsuOperation() == -4)
			{
				Zaisen aZaisen = pCentDedDgrRessyaTrackLine->getZaisen(INT_MAX);

				DcdPos posxDgrKiten = aZaisen.iDgrXPosHatsu + iShiftSecond;
				DcdPos posxDgrSyuuten = aZaisen.iDgrXPosHatsu + iShiftSecond + 30;

				if (zonexDgrPosOnDgrZone(posxDgrKiten, posxDgrSyuuten))
				{
					CdDcdPosXy	posDcdRessyaTrackKiten;
					CdDcdPosXy	posDcdRessyaTrackSyuuten;
					posDcdRessyaTrackKiten.setX(XDgrToDcd(posxDgrKiten));
					posDcdRessyaTrackSyuuten.setX(XDgrToDcd(posxDgrSyuuten));
					posDcdRessyaTrackKiten.setY(
						YDgrToDcd(pCentDedDgrRessyaTrackLine->getEkiOrder(),
							pCentDedDgrRessya->getRessyahoukou(),
							true));
					if (pCentDedDgrRessya->getRessyahoukou() == Ressyahoukou_Kudari)
					{
						posDcdRessyaTrackSyuuten.setY(posDcdRessyaTrackKiten.getY() - m_iYDcd30SecondLength);
					}
					else
					{
						posDcdRessyaTrackSyuuten.setY(posDcdRessyaTrackKiten.getY() + m_iYDcd30SecondLength);
					}
					RessyaTrackVerticalLineDraw(
						posDcdRessyaTrackKiten,
						posDcdRessyaTrackSyuuten,
						pCentDedDgrRessya);
				}
			}

			/**
				前列車接続がある場合の、前列車までの円弧を描写します
			*/
			if (pCentDedDgrRessyaTrackLine->getChakuOperation() == 5)
			{
				// --------------------------------
				//	在線線の座標を求めます
				// --------------------------------
				{
					Zaisen aZaisen = pCentDedDgrRessyaTrackLine->getZaisen(0);

					DcdPos posxDgrKiten = aZaisen.iDgrXPosChaku + iShiftSecond;
					DcdPos posxDgrSyuuten = aZaisen.iDgrXPosHatsu + iShiftSecond;

					if (zonexDgrPosOnDgrZone(posxDgrKiten, posxDgrSyuuten))
					{
						CdDcdPosXy	posDcdRessyaTrackKiten;
						CdDcdPosXy	posDcdRessyaTrackSyuuten;
						posDcdRessyaTrackKiten.setX(XDgrToDcd(posxDgrKiten));
						posDcdRessyaTrackSyuuten.setX(XDgrToDcd(posxDgrSyuuten));
						posDcdRessyaTrackKiten.setY(
							YDgrToDcd(pCentDedDgrRessyaTrackLine->getEkiOrder(), 
								pCentDedDgrRessya->getRessyahoukou(),
								false));
						posDcdRessyaTrackSyuuten.setY(posDcdRessyaTrackKiten.getY());
						int iLeftShape = pCentDedDgrRessyaTrackLine->getPrevRessyahoukou();
						int iRightShape = 1;
						if (pCentDedDgrRessyaTrackLine->getHatsuOperation() == -4 ||
							pCentDedDgrRessyaTrackLine->getHatsuOperation() == -5)
						{
							iRightShape = -1;
						}
						ConnectNextNoDisplayDraw(
							pCentDedDgrRessya,
							aZaisen.strOperationNumber,
							posDcdRessyaTrackKiten,
							posDcdRessyaTrackSyuuten,
							iLeftShape,
							iRightShape);
					}
				}
			}

			/**
				出区の丸印および運用番号の描写です。
			*/
			if (pCentDedDgrRessyaTrackLine->getChakuOperation() == 3)
			{
				// --------------------------------
				//	出区マークを描画する位置を算出
				// --------------------------------

				Zaisen aZaisen = pCentDedDgrRessyaTrackLine->getZaisen(0);
				DcdPos posxDgrKiten = aZaisen.iDgrXPosChaku + iShiftSecond;

				if (zonexDgrPosOnDgrZone(posxDgrKiten, posxDgrKiten))
				{
					int iY_DcdDown = 0;
					int iY_DcdUp = 0;
					if (pCentDedDgrRessyaTrackLine->getHatsuOperation() == -4 ||
						pCentDedDgrRessyaTrackLine->getHatsuOperation() == -5)
					{
						iY_DcdDown = YDgrToDcd(
							pCentDedDgrRessyaTrackLine->getEkiOrder(),
							pCentDedDgrRessya->getRessyahoukou(),
							false);
						if (pCentDedDgrRessya->getRessyahoukou() == Ressyahoukou_Kudari)
						{
							iY_DcdUp = iY_DcdDown + m_iYDcdDiagramDefaultSecondLength;
						}
						else
						{
							iY_DcdUp = iY_DcdDown - m_iYDcdDiagramDefaultSecondLength;
						}
					}
					else
					{
						iY_DcdDown = YDgrToDcd(
							pCentDedDgrRessyaTrackLine->getEkiOrder(),
							pCentDedDgrRessya->getRessyahoukou(),
							true);
						if (pCentDedDgrRessya->getRessyahoukou() == Ressyahoukou_Kudari)
						{
							iY_DcdUp = iY_DcdDown - m_iYDcdDiagramDefaultSecondLength;
						}
						else
						{
							iY_DcdUp = iY_DcdDown + m_iYDcdDiagramDefaultSecondLength;
						}
					}
					int iX_DcdLeft = XDgrToDcd(posxDgrKiten)
						- m_iYDcdDiagramDefaultSecondLength / 2;
					int iX_DcdRight = XDgrToDcd(posxDgrKiten)
						+ m_iYDcdDiagramDefaultSecondLength / 2;

#pragma omp critical
					{
						CdPenProp	aCdPenProp(1, CdColorProp(0, 0, 0), CdPenProp::SOLID);
						int idxRessyasyubetsu = pCentDedDgrRessya->getRessyasyubetsuIndex();
						if (0 <= idxRessyasyubetsu &&
							idxRessyasyubetsu < getCentDedDgrDia()->getMuCentDedDgrRessyasyubetsu()->size())
						{
							const CentDedDgrRessyasyubetsu* pCentDedDgrRessyasyubetsu =
								getCentDedDgrDia()->getMuCentDedDgrRessyasyubetsu()->get(idxRessyasyubetsu);
							if (m_bDisplayParentSyubetsu && pCentDedDgrRessyasyubetsu->getParentSyubetsuIndex() >= 0)
							{
								pCentDedDgrRessyasyubetsu = getCentDedDgrDia()
									->getMuCentDedDgrRessyasyubetsu()->get(pCentDedDgrRessyasyubetsu->getParentSyubetsuIndex());
							}
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
							iX_DcdLeft,
							iY_DcdUp,
							iX_DcdRight,
							iY_DcdDown);

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
					if (!aZaisen.strOperationNumber.empty())
					{
						int iYShift = -1;
						if (pCentDedDgrRessyaTrackLine->getHatsuOperation() == -4 ||
							pCentDedDgrRessyaTrackLine->getHatsuOperation() == -5)
						{
							iYShift = 1;
						}
						OperationNumberDraw(
							pCentDedDgrRessya,
							aZaisen.strOperationNumber,
							iX_DcdLeft,
							iY_DcdDown,
							-1,
							iYShift);
					}
				}
			}

			/**
				路線外始発における斜め線および駅名・運用番号の描写
			*/
			if (pCentDedDgrRessyaTrackLine->getChakuOperation() == 4)
			{
				Zaisen aZaisen = pCentDedDgrRessyaTrackLine->getZaisen(0);
				DcdPos posxDgrKiten = aZaisen.iDgrXPosChaku + iShiftSecond - (m_pCentDedDgrDia->getDgrYSizeEkikanDefault() * 0.7);
				DcdPos posxDgrSyuuten = aZaisen.iDgrXPosChaku + iShiftSecond;

				if (zonexDgrPosOnDgrZone(posxDgrKiten, posxDgrSyuuten))
				{
					CdDcdPosXy	posDcdRessyaTrackKiten;
					CdDcdPosXy	posDcdRessyaTrackSyuuten;
					posDcdRessyaTrackKiten.setX(XDgrToDcd(posxDgrKiten));
					posDcdRessyaTrackSyuuten.setX(XDgrToDcd(posxDgrSyuuten));
					if (pCentDedDgrRessyaTrackLine->getHatsuOperation() == -4 ||
						pCentDedDgrRessyaTrackLine->getHatsuOperation() == -5)
					{
						posDcdRessyaTrackSyuuten.setY( YDgrToDcd(
							pCentDedDgrRessyaTrackLine->getEkiOrder(),
							pCentDedDgrRessya->getRessyahoukou(),
							false));
						if (pCentDedDgrRessya->getRessyahoukou() == Ressyahoukou_Kudari)
						{
							posDcdRessyaTrackKiten.setY(posDcdRessyaTrackSyuuten.getY() +
								m_iYDcdDiagramDefaultSecondLength * 0.7);
						}
						else
						{
							posDcdRessyaTrackKiten.setY(posDcdRessyaTrackSyuuten.getY() -
								m_iYDcdDiagramDefaultSecondLength * 0.7);
						}
					}
					else
					{
						posDcdRessyaTrackSyuuten.setY(YDgrToDcd(
							pCentDedDgrRessyaTrackLine->getEkiOrder(),
							pCentDedDgrRessya->getRessyahoukou(),
							true));
						if (pCentDedDgrRessya->getRessyahoukou() == Ressyahoukou_Kudari)
						{
							posDcdRessyaTrackKiten.setY(posDcdRessyaTrackSyuuten.getY() -
								m_iYDcdDiagramDefaultSecondLength * 0.7);
						}
						else
						{
							posDcdRessyaTrackKiten.setY(posDcdRessyaTrackSyuuten.getY() +
								m_iYDcdDiagramDefaultSecondLength * 0.7);
						}
					}
					//#pragma omp critical
					RessyaTrackVerticalLineDraw(
						posDcdRessyaTrackKiten,
						posDcdRessyaTrackSyuuten,
						pCentDedDgrRessya);

					int iX_Dcd = posDcdRessyaTrackKiten.getX();
					int iY_Dcd = posDcdRessyaTrackSyuuten.getY();

					tstring strOuterEkimeiAndOperationNumber;
					if (m_pCDcdDiagram->getDiagramDisplayOuterTerminal() == 0 ||
						m_pCDcdDiagram->getDiagramDisplayOuterTerminal() == 1)
					{
						int iEkiIndex = getCentDedDgrDia()->EkiIndexOfEkiOrder(
							pCentDedDgrRessya->getRessyahoukou(),
							pCentDedDgrRessyaTrackLine->getEkiOrder());
						const CentDedDgrEki aCentDedDgrEki = getCentDedDgrDia()
							->getCentDedDgrEkiCont()->get(iEkiIndex);
						strOuterEkimeiAndOperationNumber = aCentDedDgrEki.getOuterTerminalEkimei(
							pCentDedDgrRessyaTrackLine->getOuterEkiIndex());
					}

					if ((m_pCDcdDiagram->getDiagramDisplayOuterTerminal() == 0 ||
						m_pCDcdDiagram->getDiagramDisplayOuterTerminal() == 2) &&
						!aZaisen.strOperationNumber.empty())
					{
						if (m_pCDcdDiagram->getDiagramDisplayOuterTerminal() == 0)
						{
							strOuterEkimeiAndOperationNumber += _T(" ");
						}
						strOuterEkimeiAndOperationNumber += aZaisen.strOperationNumber;
					}

					if (!strOuterEkimeiAndOperationNumber.empty())
					{
						int iYShift = -1;
						if (pCentDedDgrRessyaTrackLine->getHatsuOperation() == -4 ||
							pCentDedDgrRessyaTrackLine->getHatsuOperation() == -5)
						{
							iYShift = 1;
						}
						OuterEkimeiAndOperationNumberDraw(
							pCentDedDgrRessya/*->getOperationNumber()*/,
							strOuterEkimeiAndOperationNumber,
							iX_Dcd,
							iY_Dcd,
							-1,
							iYShift);
					}
				}
			}

			/**
				解結作業における、△または▽印の描写です。
			*/
			if (pCentDedDgrRessyaTrackLine->getChakuOperation() == 2)
			{
				// --------------------------------
				//	解結マークを描画する位置を算出
				// --------------------------------
				Zaisen aZaisen = pCentDedDgrRessyaTrackLine->getZaisen(0);
				CdDcdPosXy	posTriangle_Dcd[3];
				DcdPos posxDgrKiten = aZaisen.iDgrXPosChaku + iShiftSecond;

				if (zonexDgrPosOnDgrZone(posxDgrKiten, posxDgrKiten))
				{
					//iX_Dcd,iY_Dcd = 列車情報を表示する駅の発時刻の座標
					//	単位は、 IfDcdTarget の座標系
					// --------------------------------
					int iY_DcdUp = YDgrToDcd(
							pCentDedDgrRessyaTrackLine->getEkiOrder(),
							pCentDedDgrRessya->getRessyahoukou(),
							true);
					int iY_DcdDown = iY_DcdUp;
					if (pCentDedDgrRessya->getRessyahoukou() == Ressyahoukou_Kudari)
					{
						iY_DcdDown += m_iYDcdDiagramDefaultSecondLength;
					}
					else
					{
						iY_DcdDown -= m_iYDcdDiagramDefaultSecondLength;
					}

					int iX_DcdCenter = XDgrToDcd(posxDgrKiten);
					int iX_DcdLeft = iX_DcdCenter
						- m_iYDcdDiagramDefaultSecondLength / 2;
					int iX_DcdRight = iX_DcdCenter
						+ m_iYDcdDiagramDefaultSecondLength / 2;

					posTriangle_Dcd[0].setX((DcdPos)iX_DcdCenter);
					posTriangle_Dcd[0].setY((DcdPos)iY_DcdUp);
					posTriangle_Dcd[1].setX((DcdPos)iX_DcdLeft);
					posTriangle_Dcd[1].setY((DcdPos)iY_DcdDown);
					posTriangle_Dcd[2].setX((DcdPos)iX_DcdRight);
					posTriangle_Dcd[2].setY((DcdPos)iY_DcdDown);

#pragma omp critical
					{
						CdPenProp	aCdPenProp(1, CdColorProp(0, 0, 0), CdPenProp::SOLID);
						CdBrushProp	aCdBrushProp(CdColorProp(0, 0, 0), CdBrushProp::SOLID);
						int idxRessyasyubetsu = pCentDedDgrRessya->getRessyasyubetsuIndex();
						if (0 <= idxRessyasyubetsu &&
							idxRessyasyubetsu < getCentDedDgrDia()->getMuCentDedDgrRessyasyubetsu()->size())
						{
							const CentDedDgrRessyasyubetsu* pCentDedDgrRessyasyubetsu =
								getCentDedDgrDia()->getMuCentDedDgrRessyasyubetsu()->get(idxRessyasyubetsu);
							if (m_bDisplayParentSyubetsu && pCentDedDgrRessyasyubetsu->getParentSyubetsuIndex() >= 0)
							{
								pCentDedDgrRessyasyubetsu = getCentDedDgrDia()
									->getMuCentDedDgrRessyasyubetsu()->get(pCentDedDgrRessyasyubetsu->getParentSyubetsuIndex());
							}
							CentDedRessyasyubetsu::CdDiagramLineStyle	aCdDiagramLineStyle =
								pCentDedDgrRessyasyubetsu->getCdDiagramLineStyle();

							aCdPenProp.setColor(aCdDiagramLineStyle.getDiagramSenColor());
							aCdBrushProp.setColor(aCdDiagramLineStyle.getDiagramSenColor());
						}
						Ou<CGdiHPenHolder>	pHPenHolder = m_pIfDcdTarget->createGdiHPenHolder(aCdPenProp);
						HPEN hPenPrev = (HPEN)SelectObject(m_pIfDcdTarget->getHdc(), pHPenHolder->getHPen());

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
			}
			/**
				入区作業における、△または▽印の描写です。
			*/
			if (pCentDedDgrRessyaTrackLine->getHatsuOperation() == 3)
			{
				// --------------------------------
				//	入区マークを描画する位置を算出
				// --------------------------------
				Zaisen aZaisen = pCentDedDgrRessyaTrackLine->getZaisen(INT_MAX);
				CdDcdPosXy	posTriangle_Dcd[3];
				DcdPos posxDgrKiten = aZaisen.iDgrXPosHatsu + iShiftSecond;
				if (zonexDgrPosOnDgrZone(posxDgrKiten, posxDgrKiten))
				{
					//iX_Dcd,iY_Dcd = 列車情報を表示する駅の発時刻の座標
					//	単位は、 IfDcdTarget の座標系
					// --------------------------------
					int iY_DcdUp = 0;
					int iY_DcdDown = 0;
					if (pCentDedDgrRessyaTrackLine->getHatsuOperation() == -4 ||
						pCentDedDgrRessyaTrackLine->getHatsuOperation() == -5)
					{
						iY_DcdUp = YDgrToDcd(
							pCentDedDgrRessyaTrackLine->getEkiOrder(),
							pCentDedDgrRessya->getRessyahoukou(),
							true);
						if (pCentDedDgrRessya->getRessyahoukou() == Ressyahoukou_Kudari)
						{
							iY_DcdDown = iY_DcdUp - m_iYDcdDiagramDefaultSecondLength;
						}
						else
						{
							iY_DcdDown = iY_DcdUp + m_iYDcdDiagramDefaultSecondLength;
						}
					}
					else
					{
						iY_DcdUp = YDgrToDcd(
							pCentDedDgrRessyaTrackLine->getEkiOrder(),
							pCentDedDgrRessya->getRessyahoukou(),
							false);
						if (pCentDedDgrRessya->getRessyahoukou() == Ressyahoukou_Kudari)
						{
							iY_DcdDown = iY_DcdUp + m_iYDcdDiagramDefaultSecondLength;
						}
						else
						{
							iY_DcdDown = iY_DcdUp - m_iYDcdDiagramDefaultSecondLength;
						}
					}
					int iX_DcdCenter = XDgrToDcd(posxDgrKiten);
					int iX_DcdLeft = iX_DcdCenter
						- m_iYDcdDiagramDefaultSecondLength / 2;
					int iX_DcdRight = iX_DcdCenter
						+ m_iYDcdDiagramDefaultSecondLength / 2;

					posTriangle_Dcd[0].setX((DcdPos)iX_DcdCenter);
					posTriangle_Dcd[0].setY((DcdPos)iY_DcdUp);
					posTriangle_Dcd[1].setX((DcdPos)iX_DcdLeft);
					posTriangle_Dcd[1].setY((DcdPos)iY_DcdDown);
					posTriangle_Dcd[2].setX((DcdPos)iX_DcdRight);
					posTriangle_Dcd[2].setY((DcdPos)iY_DcdDown);

#pragma omp critical
					{
						CdPenProp	aCdPenProp(1, CdColorProp(0, 0, 0), CdPenProp::SOLID);
						int idxRessyasyubetsu = pCentDedDgrRessya->getRessyasyubetsuIndex();
						if (0 <= idxRessyasyubetsu &&
							idxRessyasyubetsu < getCentDedDgrDia()->getMuCentDedDgrRessyasyubetsu()->size())
						{
							const CentDedDgrRessyasyubetsu* pCentDedDgrRessyasyubetsu =
								getCentDedDgrDia()->getMuCentDedDgrRessyasyubetsu()->get(idxRessyasyubetsu);
							if (m_bDisplayParentSyubetsu && pCentDedDgrRessyasyubetsu->getParentSyubetsuIndex() >= 0)
							{
								pCentDedDgrRessyasyubetsu = getCentDedDgrDia()
									->getMuCentDedDgrRessyasyubetsu()->get(pCentDedDgrRessyasyubetsu->getParentSyubetsuIndex());
							}
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

					if (!aZaisen.strOperationNumber.empty())
					{
						int iYShift = 1;
						if (pCentDedDgrRessyaTrackLine->getChakuOperation() == -4 ||
							pCentDedDgrRessyaTrackLine->getChakuOperation() == -5)
						{
							iYShift = -1;
						}
						OperationNumberDraw(
							pCentDedDgrRessya,
							aZaisen.strOperationNumber,
							iX_DcdRight,
							iY_DcdUp,
							1,
							iYShift);
					}
				}
			}

			/**
				路線外終着における斜め線の描写および、駅名・運番の描写です
			*/
			if (pCentDedDgrRessyaTrackLine->getHatsuOperation() == 4)
			{
				Zaisen aZaisen = pCentDedDgrRessyaTrackLine->getZaisen(INT_MAX);

				DcdPos posxDgrKiten = aZaisen.iDgrXPosHatsu + iShiftSecond;
				DcdPos posxDgrSyuuten = aZaisen.iDgrXPosHatsu + iShiftSecond + (m_pCentDedDgrDia->getDgrYSizeEkikanDefault() * 0.7);

				if (zonexDgrPosOnDgrZone(posxDgrKiten, posxDgrSyuuten))
				{
					CdDcdPosXy	posDcdRessyaTrackKiten;
					CdDcdPosXy	posDcdRessyaTrackSyuuten;
					posDcdRessyaTrackKiten.setX(XDgrToDcd(posxDgrKiten));
					posDcdRessyaTrackSyuuten.setX(XDgrToDcd(posxDgrSyuuten));
					if (pCentDedDgrRessyaTrackLine->getChakuOperation() == -4 ||
						pCentDedDgrRessyaTrackLine->getChakuOperation() == -5)
					{
						posDcdRessyaTrackKiten.setY(YDgrToDcd(
							pCentDedDgrRessyaTrackLine->getEkiOrder(),
							pCentDedDgrRessya->getRessyahoukou(),
							false));
						if (pCentDedDgrRessya->getRessyahoukou() == Ressyahoukou_Kudari)
						{
							posDcdRessyaTrackSyuuten.setY(posDcdRessyaTrackKiten.getY() -
								m_iYDcdDiagramDefaultSecondLength * 0.7);
						}
						else
						{
							posDcdRessyaTrackSyuuten.setY(posDcdRessyaTrackKiten.getY() +
								m_iYDcdDiagramDefaultSecondLength * 0.7);
						}
					}
					else
					{
						posDcdRessyaTrackKiten.setY(YDgrToDcd(
							pCentDedDgrRessyaTrackLine->getEkiOrder(),
							pCentDedDgrRessya->getRessyahoukou(),
							true));
						if (pCentDedDgrRessya->getRessyahoukou() == Ressyahoukou_Kudari)
						{
							posDcdRessyaTrackSyuuten.setY(posDcdRessyaTrackKiten.getY() +
								m_iYDcdDiagramDefaultSecondLength * 0.7);
						}
						else
						{
							posDcdRessyaTrackSyuuten.setY(posDcdRessyaTrackKiten.getY() -
								m_iYDcdDiagramDefaultSecondLength * 0.7);
						}
					}
					//#pragma omp critical
					RessyaTrackVerticalLineDraw(
						posDcdRessyaTrackKiten,
						posDcdRessyaTrackSyuuten,
						pCentDedDgrRessya);

					int iX_Dcd = posDcdRessyaTrackSyuuten.getX();
					int iY_Dcd = posDcdRessyaTrackKiten.getY();

					tstring strOuterEkimeiAndOperationNumber;
					if (m_pCDcdDiagram->getDiagramDisplayOuterTerminal() == 0 ||
						m_pCDcdDiagram->getDiagramDisplayOuterTerminal() == 1)
					{
						int iEkiIndex = getCentDedDgrDia()->EkiIndexOfEkiOrder(
							pCentDedDgrRessya->getRessyahoukou(),
							pCentDedDgrRessyaTrackLine->getEkiOrder());
						const CentDedDgrEki aCentDedDgrEki = getCentDedDgrDia()
							->getCentDedDgrEkiCont()->get(iEkiIndex);
						strOuterEkimeiAndOperationNumber = aCentDedDgrEki.getOuterTerminalEkimei(
							pCentDedDgrRessyaTrackLine->getOuterEkiIndex());
					}

					if ((m_pCDcdDiagram->getDiagramDisplayOuterTerminal() == 0 ||
						m_pCDcdDiagram->getDiagramDisplayOuterTerminal() == 2) &&
						!aZaisen.strOperationNumber.empty())
					{
						if (m_pCDcdDiagram->getDiagramDisplayOuterTerminal() == 0)
						{
							strOuterEkimeiAndOperationNumber += _T(" ");
						}
						strOuterEkimeiAndOperationNumber += aZaisen.strOperationNumber;
					}

					if (!strOuterEkimeiAndOperationNumber.empty())
					{
						int iYShift = 1;
						if (pCentDedDgrRessyaTrackLine->getChakuOperation() == -4 ||
							pCentDedDgrRessyaTrackLine->getChakuOperation() == -5)
						{
							iYShift = -1;
						}
						OuterEkimeiAndOperationNumberDraw(
							pCentDedDgrRessya/*->getOperationNumber()*/,
							strOuterEkimeiAndOperationNumber,
							iX_Dcd,
							iY_Dcd,
							1,
							iYShift);
					}
				}
			}

			/**
				増結の丸印の描写です。
			*/
			if (pCentDedDgrRessyaTrackLine->getHatsuOperation() == 1)
			{
				// --------------------------------
				//	増結マークを描画する位置を算出
				// --------------------------------

				Zaisen aZaisen = pCentDedDgrRessyaTrackLine->getZaisen(INT_MAX);

				DcdPos posxDgrKiten = aZaisen.iDgrXPosHatsu + iShiftSecond;

				if (zonexDgrPosOnDgrZone(posxDgrKiten, posxDgrKiten))
				{
					int iY_DcdDown = YDgrToDcd(pCentDedDgrRessyaTrackLine->getEkiOrder(),
						pCentDedDgrRessya->getRessyahoukou(),false);
					int iY_DcdUp = iY_DcdDown;
					if (pCentDedDgrRessya->getRessyahoukou() == Ressyahoukou_Kudari)
					{
						iY_DcdUp -= m_iYDcdDiagramDefaultSecondLength;
					}
					else
					{
						iY_DcdUp += m_iYDcdDiagramDefaultSecondLength;
					}
					int iX_DcdLeft = XDgrToDcd(posxDgrKiten)
						- m_iYDcdDiagramDefaultSecondLength / 2;
					int iX_DcdRight = XDgrToDcd(posxDgrKiten)
						+ m_iYDcdDiagramDefaultSecondLength / 2;

#pragma omp critical
					{
						CdPenProp	aCdPenProp(1, CdColorProp(0, 0, 0), CdPenProp::SOLID);
						CdBrushProp	aCdBrushProp(CdColorProp(0, 0, 0), CdBrushProp::SOLID);
						int idxRessyasyubetsu = pCentDedDgrRessya->getRessyasyubetsuIndex();
						if (0 <= idxRessyasyubetsu &&
							idxRessyasyubetsu < getCentDedDgrDia()->getMuCentDedDgrRessyasyubetsu()->size())
						{
							const CentDedDgrRessyasyubetsu* pCentDedDgrRessyasyubetsu =
								getCentDedDgrDia()->getMuCentDedDgrRessyasyubetsu()->get(idxRessyasyubetsu);
							if (m_bDisplayParentSyubetsu && pCentDedDgrRessyasyubetsu->getParentSyubetsuIndex() >= 0)
							{
								pCentDedDgrRessyasyubetsu = getCentDedDgrDia()
									->getMuCentDedDgrRessyasyubetsu()->get(pCentDedDgrRessyasyubetsu->getParentSyubetsuIndex());
							}
							CentDedRessyasyubetsu::CdDiagramLineStyle	aCdDiagramLineStyle =
								pCentDedDgrRessyasyubetsu->getCdDiagramLineStyle();

							aCdPenProp.setColor(aCdDiagramLineStyle.getDiagramSenColor());
							aCdBrushProp.setColor(aCdDiagramLineStyle.getDiagramSenColor());
						}
						Ou<CGdiHPenHolder>	pHPenHolder = m_pIfDcdTarget->createGdiHPenHolder(aCdPenProp);
						HPEN hPenPrev = (HPEN)SelectObject(m_pIfDcdTarget->getHdc(), pHPenHolder->getHPen());

						Ou<CGdiHBrushHolder> pHBrushHolder = m_pIfDcdTarget->createGdiHBrushHolder(aCdBrushProp);
						HBRUSH hBrushPrev = (HBRUSH)SelectObject(m_pIfDcdTarget->getHdc(), pHBrushHolder->getHBrush());


						Ellipse(
							m_pIfDcdTarget->getHdc(),
							iX_DcdLeft,
							iY_DcdUp,
							iX_DcdRight,
							iY_DcdDown);

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
	}
}

bool CRessyaDraw::zonexyDgrRessyasenOnDgrZone(
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

bool CRessyaDraw::zonexDgrPosOnDgrZone(
	const DcdPos& posxDgrKiten,
	const DcdPos& posxDgrSyuuten)const
{
	CdDcdZone zoneTemp(posxDgrKiten);
	zoneTemp.setEndPos(posxDgrSyuuten);
	if (zoneTemp.getSize() == 0)
	{
		zoneTemp.setSize(1);
	}
	CdDcdZone	zonexDgrZoneOnDgrZone = m_zonexyDgrZone.getX().CrossZone(zoneTemp);

	if (zonexDgrZoneOnDgrZone.getSize() > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CRessyaDraw::RessyaTrackVerticalLineDraw(
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
			if (m_bDisplayParentSyubetsu && pCentDedDgrRessyasyubetsu->getParentSyubetsuIndex() >= 0)
			{
				pCentDedDgrRessyasyubetsu = getCentDedDgrDia()
					->getMuCentDedDgrRessyasyubetsu()->get(pCentDedDgrRessyasyubetsu->getParentSyubetsuIndex());
			}
			CentDedRessyasyubetsu::CdDiagramLineStyle	aCdDiagramLineStyle =
				pCentDedDgrRessyasyubetsu->getCdDiagramLineStyle();

			aCdLineProp.setColor(aCdDiagramLineStyle.getDiagramSenColor());
		}
	}

	// --------------------------------
	//	直線の描画位置を決定
	// --------------------------------
	CDcdFreeLine	aCDcdFreeLine(aCdLineProp);
	//CdDcdPosXy posKitenDcd = m_pCDcdDiagram->DgrToDcd(
	//	m_pIfDcdTarget, posRessyaTrackKiten);
	//CdDcdPosXy posSyuutenDcd = m_pCDcdDiagram->DgrToDcd(
	//	m_pIfDcdTarget, posRessyaTrackSyuuten);
	//if (posKitenDcd.getY() < posSyuutenDcd.getY())
	//{
	//	if (iYShiftKiten != 0)
	//	{
	//		posKitenDcd.setY(posKitenDcd.getY() - iYShiftKiten);
	//	}
	//	if (iYShiftSyuuten != 0)
	//	{
	//		posSyuutenDcd.setY(posSyuutenDcd.getY() + iYShiftSyuuten);
	//	}
	//}
	//else
	//{
	//	if (iYShiftKiten != 0)
	//	{
	//		posKitenDcd.setY(posKitenDcd.getY() + iYShiftKiten);
	//	}
	//	if (iYShiftSyuuten != 0)
	//	{
	//		posSyuutenDcd.setY(posSyuutenDcd.getY() - iYShiftSyuuten);
	//	}
	//}
		aCDcdFreeLine.setOrg(posRessyaTrackKiten);
		aCDcdFreeLine.setDst(posRessyaTrackSyuuten);
#pragma omp critical
		{
		aCDcdFreeLine.DcDraw(m_pIfDcdTarget);
	}
}

void CRessyaDraw::RessyaTrackHorizontalLineDraw(
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
			if (m_bDisplayParentSyubetsu && pCentDedDgrRessyasyubetsu->getParentSyubetsuIndex() >= 0)
			{
				pCentDedDgrRessyasyubetsu = getCentDedDgrDia()
					->getMuCentDedDgrRessyasyubetsu()->get(pCentDedDgrRessyasyubetsu->getParentSyubetsuIndex());
			}
			CentDedRessyasyubetsu::CdDiagramLineStyle	aCdDiagramLineStyle =
				pCentDedDgrRessyasyubetsu->getCdDiagramLineStyle();

			aCdPenProp.setColor(aCdDiagramLineStyle.getDiagramSenColor());
			aCdBrushProp.setColor(aCdDiagramLineStyle.getDiagramSenColor());
			aCdLineProp.setColor(aCdDiagramLineStyle.getDiagramSenColor());
		}
#pragma omp critical
		{
			Ou<CGdiHPenHolder>	pHPenHolder = m_pIfDcdTarget->createGdiHPenHolder(aCdPenProp);
			HPEN hPenPrev = (HPEN)SelectObject(m_pIfDcdTarget->getHdc(), pHPenHolder->getHPen());

			Ou<CGdiHBrushHolder> pHBrushHolder = m_pIfDcdTarget->createGdiHBrushHolder(aCdBrushProp);
			HBRUSH hBrushPrev = (HBRUSH)SelectObject(m_pIfDcdTarget->getHdc(), pHBrushHolder->getHBrush());

			if (iX_Left_Dcd == iX_Right_Dcd) {
				CDcdFreeLine	aCDcdFreeLine(aCdLineProp);
				CdDcdPosXy posKitenDcd;
				CdDcdPosXy posSyuutenDcd;
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
				if (iYChamferRight == 0)
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
}

void CRessyaDraw::OperationNumberDraw(
	const CentDedDgrRessya* pCentDedDgrRessya,
	const tstring strOperationNumber,
	const int iX_Dcd_Center,
	const int iY_Dcd_Line,
	const int iXShift,
	const int iYShift)
{
	CdColorProp	colorText = m_pCDcdDiagram->getDiaMojiColor();
	//tstring strOperationNumber = pCentDedDgrRessya->getOperationNumber();
	CdDcdSizeXy	sizexyText_Dcd;
#pragma omp critical
	{
		CDcdText	dcdText(strOperationNumber,
			m_pCDcdDiagram->getDiaRessyaFont());
		dcdText.getItemSize(m_pIfDcdTarget, &sizexyText_Dcd);
	}
	int iX_Dcd;
	int iY_Dcd;
	if (iXShift < 0)
	{
		iX_Dcd = iX_Dcd_Center - sizexyText_Dcd.getX();
	}
	else if (iXShift > 0)
	{
		iX_Dcd = iX_Dcd_Center;
	}
	else
	{
		iX_Dcd = iX_Dcd_Center - (sizexyText_Dcd.getX() / 2);
	}
	if (iYShift < 0)
	{
		if (pCentDedDgrRessya->getRessyahoukou() == Ressyahoukou_Kudari)
		{
			iY_Dcd = iY_Dcd_Line - sizexyText_Dcd.getY();
		}
		else
		{
			iY_Dcd = iY_Dcd_Line;
		}
	}
	else if (iYShift > 0)
	{
		if (pCentDedDgrRessya->getRessyahoukou() == Ressyahoukou_Kudari)
		{
			iY_Dcd = iY_Dcd_Line;
		}
		else
		{
			iY_Dcd = iY_Dcd_Line - sizexyText_Dcd.getY();
		}
	}
	else
	{
		iY_Dcd = iY_Dcd_Line - sizexyText_Dcd.getY();
	}
#pragma omp critical
	{
		// --------------------------------
		//	テキストの描画
		// --------------------------------

		//	フォントの属性
		CdFontProp	aCdFontProp = m_pCDcdDiagram->getDiaRessyaFont();

		//	フォントの生成
		Ou<CGdiHFontHolder>	pHFontHolder = m_pIfDcdTarget->createGdiHFontHolder(
			aCdFontProp);

		// --------------------------------
		//	フォント・色・背景モードの選択
		HFONT	hFontPrev = NULL;
		hFontPrev = (HFONT)SelectObject(m_pIfDcdTarget->getHdc(),
			pHFontHolder->getHFont());

		CConverter_WinGdi	aCConverter_WinGdi;
		COLORREF	colorTextPrev = SetTextColor(
			m_pIfDcdTarget->getHdc(),
			aCConverter_WinGdi.COLORREFOf(colorText));
		int iBkModePrev = SetBkMode(m_pIfDcdTarget->getHdc(),
			TRANSPARENT);
		// --------------------------------
		TextOut(m_pIfDcdTarget->getHdc(),
			iX_Dcd, iY_Dcd,
			//posText_Dcd.getX(), posText_Dcd.getY(),
			strOperationNumber.c_str(), strOperationNumber.size());

		// --------------------------------
		//	フォント・色・背景モードの選択を解除

		{
			SetBkMode(m_pIfDcdTarget->getHdc(), iBkModePrev);
			SetTextColor(m_pIfDcdTarget->getHdc(), colorTextPrev);
		}
		if (hFontPrev != NULL) {
			SelectObject(m_pIfDcdTarget->getHdc(), hFontPrev);
			hFontPrev = NULL;
		}
		// --------------------------------
		//	フォントを破棄
		if (pHFontHolder != NULL)
		{
			pHFontHolder = Ou<CGdiHFontHolder>();
		}
	}
}

void CRessyaDraw::ConnectNextNoDisplayDraw(
	const CentDedDgrRessya * pCentDedDgrRessya,
	const tstring strOperationNumber,
	CdDcdPosXy posRessyaTrackKiten,
	CdDcdPosXy posRessyaTrackSyuuten,
	int iLeftShape,
	int iRightShape)
{
	CdPenProp	aCdPenProp(1, CdColorProp(0, 0, 0), CdPenProp::SOLID);
	int idxRessyasyubetsu = pCentDedDgrRessya->getRessyasyubetsuIndex();
	if (0 <= idxRessyasyubetsu &&
		idxRessyasyubetsu < getCentDedDgrDia()->getMuCentDedDgrRessyasyubetsu()->size())
	{
		const CentDedDgrRessyasyubetsu* pCentDedDgrRessyasyubetsu =
			getCentDedDgrDia()->getMuCentDedDgrRessyasyubetsu()->get(idxRessyasyubetsu);
		if (m_bDisplayParentSyubetsu && pCentDedDgrRessyasyubetsu->getParentSyubetsuIndex() >= 0)
		{
			pCentDedDgrRessyasyubetsu = getCentDedDgrDia()
				->getMuCentDedDgrRessyasyubetsu()->get(pCentDedDgrRessyasyubetsu->getParentSyubetsuIndex());
		}
		CentDedRessyasyubetsu::CdDiagramLineStyle	aCdDiagramLineStyle =
			pCentDedDgrRessyasyubetsu->getCdDiagramLineStyle();

		aCdPenProp.setColor(aCdDiagramLineStyle.getDiagramSenColor());

	}
	if (iLeftShape == iRightShape)
	{
		//CdDcdPosXy posRessyaTrackKitenDown = posRessyaTrackKiten;
		int iY_DcdUp = posRessyaTrackKiten.getY();
		int iY_DcdDown = iY_DcdUp;
		if (pCentDedDgrRessya->getRessyahoukou() == Ressyahoukou_Kudari)
		{
			iY_DcdDown -= 1.5 * m_iYDcd30SecondLength * iLeftShape;
		}
		else
		{
			iY_DcdDown += 1.5 * m_iYDcd30SecondLength * iLeftShape;
		}
		int iX_DcdLeft = posRessyaTrackKiten.getX();
		int iX_DcdRight = posRessyaTrackSyuuten.getX();

		CdDcdPosXy	posBezier_Dcd[4];
		posBezier_Dcd[0].setX((DcdPos)iX_DcdLeft);
		posBezier_Dcd[0].setY((DcdPos)iY_DcdUp);
		posBezier_Dcd[1].setX((DcdPos)iX_DcdLeft);
		posBezier_Dcd[1].setY((DcdPos)iY_DcdDown);
		posBezier_Dcd[2].setX((DcdPos)iX_DcdRight);
		posBezier_Dcd[2].setY((DcdPos)iY_DcdDown);
		posBezier_Dcd[3].setX((DcdPos)iX_DcdRight);
		posBezier_Dcd[3].setY((DcdPos)iY_DcdUp);
#pragma omp critical
		{
			Ou<CGdiHPenHolder>	pHPenHolder = m_pIfDcdTarget->createGdiHPenHolder(aCdPenProp);
			HPEN hPenPrev = (HPEN)SelectObject(m_pIfDcdTarget->getHdc(), pHPenHolder->getHPen());

			CdBrushProp	aCdBrushProp(CdColorProp(0, 0, 0), CdBrushProp::NULLBRUSH);
			Ou<CGdiHBrushHolder> pHBrushHolder = m_pIfDcdTarget->createGdiHBrushHolder(aCdBrushProp);
			HBRUSH hBrushPrev = (HBRUSH)SelectObject(m_pIfDcdTarget->getHdc(), pHBrushHolder->getHBrush());

			POINT pointBezier[4];
			CConverter_WinGdi aConv;
			pointBezier[0] = aConv.POINTOf(posBezier_Dcd[0]);
			pointBezier[1] = aConv.POINTOf(posBezier_Dcd[1]);
			pointBezier[2] = aConv.POINTOf(posBezier_Dcd[2]);
			pointBezier[3] = aConv.POINTOf(posBezier_Dcd[3]);
			PolyBezier(
				m_pIfDcdTarget->getHdc(),
				pointBezier,
				4);
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
		if (!strOperationNumber.empty())
		{
			OperationNumberDraw(
				pCentDedDgrRessya,
				strOperationNumber,
				(iX_DcdLeft + iX_DcdRight) / 2,
				iY_DcdDown,
				0,
				-iLeftShape
			/*1*/);
		}
	}
	else/* if (pCentDedDgrRessya->getNexthoukouNoDisplay() > 0)*/
	{
		//CdDcdPosXy posRessyaTrackKitenDown1 = posRessyaTrackKiten;
		//CdDcdPosXy posRessyaTrackKitenDown2 = posRessyaTrackKiten;
		//if (pCentDedDgrRessya->getRessyahoukou() == Ressyahoukou_Kudari)
		//{
		//	posRessyaTrackKitenDown1 = posRessyaTrackKitenDown1.setY(posRessyaTrackKitenDown1.getY() - (45 * iLeftShape));
		//	posRessyaTrackKitenDown2 = posRessyaTrackKitenDown2.setY(posRessyaTrackKitenDown2.getY() - (45 * iRightShape));
		//}
		//else
		//{
		//	posRessyaTrackKitenDown1 = posRessyaTrackKitenDown1.setY(posRessyaTrackKitenDown1.getY() + (45 * iLeftShape));
		//	posRessyaTrackKitenDown2 = posRessyaTrackKitenDown2.setY(posRessyaTrackKitenDown2.getY() + (45 * iRightShape));
		//}
		int iY_DcdUp = posRessyaTrackKiten.getY();
		int iY_DcdDown1 = iY_DcdUp;
		int iY_DcdDown2 = iY_DcdUp;
		if (pCentDedDgrRessya->getRessyahoukou() == Ressyahoukou_Kudari)
		{
			iY_DcdDown1 -= 1.5 * m_iYDcd30SecondLength * iLeftShape;
			iY_DcdDown2 -= 1.5 * m_iYDcd30SecondLength * iRightShape;
		}
		else
		{
			iY_DcdDown1 += 1.5 * m_iYDcd30SecondLength * iLeftShape;
			iY_DcdDown2 += 1.5 * m_iYDcd30SecondLength * iRightShape;
		}
		int iX_DcdLeft = posRessyaTrackKiten.getX();
		int iX_DcdRight = posRessyaTrackSyuuten.getX();
		int iX_DcdCenter = (iX_DcdLeft + iX_DcdRight) / 2;

		CdDcdPosXy	posBezierLeft_Dcd[4];
		CdDcdPosXy	posBezierRight_Dcd[4];
		posBezierLeft_Dcd[0].setX((DcdPos)iX_DcdLeft);
		posBezierLeft_Dcd[0].setY((DcdPos)iY_DcdUp);
		posBezierLeft_Dcd[1].setX((DcdPos)iX_DcdLeft);
		posBezierLeft_Dcd[1].setY((DcdPos)iY_DcdDown1);
		posBezierLeft_Dcd[2].setX((DcdPos)iX_DcdCenter);
		posBezierLeft_Dcd[2].setY((DcdPos)iY_DcdDown1);
		posBezierLeft_Dcd[3].setX((DcdPos)iX_DcdCenter);
		posBezierLeft_Dcd[3].setY((DcdPos)iY_DcdUp);
		posBezierRight_Dcd[0].setX((DcdPos)iX_DcdCenter);
		posBezierRight_Dcd[0].setY((DcdPos)iY_DcdUp);
		posBezierRight_Dcd[1].setX((DcdPos)iX_DcdCenter);
		posBezierRight_Dcd[1].setY((DcdPos)iY_DcdDown2);
		posBezierRight_Dcd[2].setX((DcdPos)iX_DcdRight);
		posBezierRight_Dcd[2].setY((DcdPos)iY_DcdDown2);
		posBezierRight_Dcd[3].setX((DcdPos)iX_DcdRight);
		posBezierRight_Dcd[3].setY((DcdPos)iY_DcdUp);
#pragma omp critical 
		{
			Ou<CGdiHPenHolder>	pHPenHolder = m_pIfDcdTarget->createGdiHPenHolder(aCdPenProp);
			HPEN hPenPrev = (HPEN)SelectObject(m_pIfDcdTarget->getHdc(), pHPenHolder->getHPen());

			CdBrushProp	aCdBrushProp(CdColorProp(0, 0, 0), CdBrushProp::NULLBRUSH);
			Ou<CGdiHBrushHolder> pHBrushHolder = m_pIfDcdTarget->createGdiHBrushHolder(aCdBrushProp);
			HBRUSH hBrushPrev = (HBRUSH)SelectObject(m_pIfDcdTarget->getHdc(), pHBrushHolder->getHBrush());

			POINT pointBezier[6];
			CConverter_WinGdi aConv;
			pointBezier[0] = aConv.POINTOf(posBezierLeft_Dcd[0]);
			pointBezier[1] = aConv.POINTOf(posBezierLeft_Dcd[1]);
			pointBezier[2] = aConv.POINTOf(posBezierLeft_Dcd[2]);
			pointBezier[3] = aConv.POINTOf(posBezierLeft_Dcd[3]);
			PolyBezier(
				m_pIfDcdTarget->getHdc(),
				pointBezier,
				4);
			pointBezier[0] = aConv.POINTOf(posBezierRight_Dcd[0]);
			pointBezier[1] = aConv.POINTOf(posBezierRight_Dcd[1]);
			pointBezier[2] = aConv.POINTOf(posBezierRight_Dcd[2]);
			pointBezier[3] = aConv.POINTOf(posBezierRight_Dcd[3]);
			PolyBezier(
				m_pIfDcdTarget->getHdc(),
				pointBezier,
				4);
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
		if (!strOperationNumber.empty())
		{
			OperationNumberDraw(
				pCentDedDgrRessya,
				strOperationNumber,
				iX_DcdCenter,
				iY_DcdDown1,
				0,
				-iLeftShape
			/*1*/);

		}
	}

}

void CRessyaDraw::OuterEkimeiAndOperationNumberDraw(
	const CentDedDgrRessya* pCentDedDgrRessya,
	const tstring strOuterEkimeiAndOperationNumber,
	const int iX_Dcd_Center,
	const int iY_Dcd_Line,
	const int iXShift,
	const int iYShift)
{
	CdColorProp	colorText(0, 0, 0);
	int idxRessyasyubetsu = pCentDedDgrRessya->getRessyasyubetsuIndex();
	if (0 <= idxRessyasyubetsu &&
		idxRessyasyubetsu < getCentDedDgrDia()->getMuCentDedDgrRessyasyubetsu()->size())
	{
		const CentDedDgrRessyasyubetsu* pCentDedDgrRessyasyubetsu =
			getCentDedDgrDia()->getMuCentDedDgrRessyasyubetsu()->get(idxRessyasyubetsu);
		if (m_bDisplayParentSyubetsu && pCentDedDgrRessyasyubetsu->getParentSyubetsuIndex() >= 0)
		{
			pCentDedDgrRessyasyubetsu = getCentDedDgrDia()
				->getMuCentDedDgrRessyasyubetsu()->get(pCentDedDgrRessyasyubetsu->getParentSyubetsuIndex());
		}
		//CentDedRessyasyubetsu::CdDiagramLineStyle	aCdDiagramLineStyle =
		//	pCentDedDgrRessyasyubetsu->getCdDiagramLineStyle();

		//colorText= aCdDiagramLineStyle.getDiagramSenColor();
		colorText = pCentDedDgrRessyasyubetsu->getJikokuhyouMojiColor();
	}

	CdDcdSizeXy	sizexyText_Dcd;
#pragma omp critical
	{
		CDcdText	dcdText(strOuterEkimeiAndOperationNumber,
			m_pCDcdDiagram->getDiaRessyaFont());
		dcdText.getItemSize(m_pIfDcdTarget, &sizexyText_Dcd);
	}
	int iX_Dcd;
	int iY_Dcd;
	if (iXShift < 0)
	{
		iX_Dcd = iX_Dcd_Center - sizexyText_Dcd.getX();
	}
	else if (iXShift > 0)
	{
		iX_Dcd = iX_Dcd_Center;
	}
	else
	{
		iX_Dcd = iX_Dcd_Center - (sizexyText_Dcd.getX() / 2);
	}
	if (iYShift < 0)
	{
		if (pCentDedDgrRessya->getRessyahoukou() == Ressyahoukou_Kudari)
		{
			iY_Dcd = iY_Dcd_Line - sizexyText_Dcd.getY();
		}
		else
		{
			iY_Dcd = iY_Dcd_Line;
		}
	}
	else if (iYShift > 0)
	{
		if (pCentDedDgrRessya->getRessyahoukou() == Ressyahoukou_Kudari)
		{
			iY_Dcd = iY_Dcd_Line;
		}
		else
		{
			iY_Dcd = iY_Dcd_Line - sizexyText_Dcd.getY();
		}
	}
	else
	{
		iY_Dcd = iY_Dcd_Line - sizexyText_Dcd.getY();
	}
#pragma omp critical
	{
		// --------------------------------
		//	テキストの描画
		// --------------------------------

		//	フォントの属性
		CdFontProp	aCdFontProp = m_pCDcdDiagram->getDiaRessyaFont();

		//	フォントの生成
		Ou<CGdiHFontHolder>	pHFontHolder = m_pIfDcdTarget->createGdiHFontHolder(
			aCdFontProp);

		// --------------------------------
		//	フォント・色・背景モードの選択
		HFONT	hFontPrev = NULL;
		hFontPrev = (HFONT)SelectObject(m_pIfDcdTarget->getHdc(),
			pHFontHolder->getHFont());

		CConverter_WinGdi	aCConverter_WinGdi;
		COLORREF	colorTextPrev = SetTextColor(
			m_pIfDcdTarget->getHdc(),
			aCConverter_WinGdi.COLORREFOf(colorText));
		int iBkModePrev = SetBkMode(m_pIfDcdTarget->getHdc(),
			TRANSPARENT);
		// --------------------------------
		TextOut(m_pIfDcdTarget->getHdc(),
			iX_Dcd, iY_Dcd,
			//posText_Dcd.getX(), posText_Dcd.getY(),
			strOuterEkimeiAndOperationNumber.c_str(), strOuterEkimeiAndOperationNumber.size());

		// --------------------------------
		//	フォント・色・背景モードの選択を解除

		{
			SetBkMode(m_pIfDcdTarget->getHdc(), iBkModePrev);
			SetTextColor(m_pIfDcdTarget->getHdc(), colorTextPrev);
		}
		if (hFontPrev != NULL) {
			SelectObject(m_pIfDcdTarget->getHdc(), hFontPrev);
			hFontPrev = NULL;
		}
		// --------------------------------
		//	フォントを破棄
		if (pHFontHolder != NULL)
		{
			pHFontHolder = Ou<CGdiHFontHolder>();
		}
	}
}

void CRessyaDraw::ReadYDcdCache()
{
	m_DcdYCache.clear();
	m_iDisplayOriginSideEkiOrder[0] = INT_MIN;
	m_iDisplayTerminalSideEkiOrder[0] = INT_MIN;
	const CentDedDgrEkiCont* pCentDedDgrEkiCont = m_pCentDedDgrDia->getCentDedDgrEkiCont();
	for (int iEkiIndex = 0; iEkiIndex < pCentDedDgrEkiCont->size(); iEkiIndex++)
	{
		vector<DcdPos> Temp;
		int iTemp = m_pCentDedDgrDia->getDgrYPosOfEkiOrg(iEkiIndex);
		Temp.push_back(m_pCDcdDiagram->YDgrToDcd(m_pIfDcdTarget, iTemp)); 

		if (m_iDisplayOriginSideEkiOrder[0] == INT_MIN)
		{
			if (iTemp >= m_zonexyDgrZone.getY().getPos())
			{
				m_iDisplayOriginSideEkiOrder[0] = iEkiIndex - 1;
				m_iDisplayTerminalSideEkiOrder[1] = pCentDedDgrEkiCont->EkiOrderOfEkiIndex(
					ERessyahoukou::Ressyahoukou_Nobori, iEkiIndex - 1);
			}
		}
		if (m_iDisplayTerminalSideEkiOrder[0] == INT_MIN)
		{
			if (iTemp >= m_zonexyDgrZone.getY().getEndPos())
			{
				m_iDisplayTerminalSideEkiOrder[0] = iEkiIndex;
				m_iDisplayOriginSideEkiOrder[1] = pCentDedDgrEkiCont->EkiOrderOfEkiIndex(
					ERessyahoukou::Ressyahoukou_Nobori, iEkiIndex);
			}
		}

		int iTemp2 = m_pCentDedDgrDia->getDgrYPosOfEkiTer(iEkiIndex);
		Temp.push_back(m_pCDcdDiagram->YDgrToDcd(m_pIfDcdTarget, iTemp2));

		if (m_iDisplayOriginSideEkiOrder[0] == INT_MIN)
		{
			if (iTemp2 >= m_zonexyDgrZone.getY().getPos())
			{
				m_iDisplayOriginSideEkiOrder[0] = iEkiIndex;
				m_iDisplayTerminalSideEkiOrder[1] = pCentDedDgrEkiCont->EkiOrderOfEkiIndex(
					ERessyahoukou::Ressyahoukou_Nobori, iEkiIndex);
			}
		}
		if (m_iDisplayTerminalSideEkiOrder[0] == INT_MIN)
		{
			if (iTemp2 > m_zonexyDgrZone.getY().getEndPos())
			{
				m_iDisplayTerminalSideEkiOrder[0] = iEkiIndex;
				m_iDisplayOriginSideEkiOrder[1] = pCentDedDgrEkiCont->EkiOrderOfEkiIndex(
					ERessyahoukou::Ressyahoukou_Nobori, iEkiIndex);
			}
			else if (iTemp2 == m_zonexyDgrZone.getY().getEndPos())
			{
				m_iDisplayTerminalSideEkiOrder[0] = iEkiIndex + 1;
				m_iDisplayOriginSideEkiOrder[1] = pCentDedDgrEkiCont->EkiOrderOfEkiIndex(
					ERessyahoukou::Ressyahoukou_Nobori, iEkiIndex + 1);
			}
		}

		m_DcdYCache.push_back(Temp);

		vector<DcdPos> Temp2;
		if (pCentDedDgrEkiCont->get(iEkiIndex).getDiagramTrackDisplay() > 0)
		{
			int iEkiTrackCount = pCentDedDgrEkiCont->get(iEkiIndex).getCentDedDgrEkiTrack2Cont().size();
			for (int iEkiTrackIndex = 0; iEkiTrackIndex < iEkiTrackCount; iEkiTrackIndex++)
			{
				int iTemp2 = m_pCentDedDgrDia->getDgrYPosOfEkiTrack(
					ERessyahoukou::Ressyahoukou_Kudari,
					iEkiIndex,
					iEkiTrackIndex);
				if (iTemp2 < 0)
				{
					Temp2.push_back(INT_MIN);
				}
				else
				{
					Temp2.push_back(m_pCDcdDiagram->YDgrToDcd(m_pIfDcdTarget, iTemp2));
				}
			}
		}
		m_DcdYEkiTrackCache.push_back(Temp2);

	}

	if (m_iDisplayTerminalSideEkiOrder[0] == INT_MIN)
	{
			m_iDisplayTerminalSideEkiOrder[0] = pCentDedDgrEkiCont->size();
			m_iDisplayOriginSideEkiOrder[1] = -1;
	}

	m_iYDcd30SecondLength = 30 * m_pCDcdDiagram->getDcdPerDgrY(m_pIfDcdTarget);
	m_iYDcdDiagramDefaultSecondLength = m_pCentDedDgrDia->getDgrYSizeEkikanDefault() * m_pCDcdDiagram->getDcdPerDgrY(m_pIfDcdTarget);
}

DcdPos CRessyaDraw::XDgrToDcd(DcdPos XDgrPos)
{
	DcdPos XDcdPos = 0;
//#pragma omp critical
//	{
//		if (m_DcdXCache.find(XDgrPos) != m_DcdXCache.end())
//		{
//			return m_DcdXCache[XDgrPos];
//		}
//		else
//		{
			XDcdPos = m_pCDcdDiagram->XDgrToDcd(m_pIfDcdTarget, XDgrPos);
	//		m_DcdXCache[XDgrPos] = XDcdPos;
	//	}
	//}
	return XDcdPos;
}

DcdPos CRessyaDraw::YDgrToDcd(int iEkiOrder, ERessyahoukou eRessyahoukou, bool bIsOrigin)
{
	if (eRessyahoukou == ERessyahoukou::Ressyahoukou_Kudari)
	{
		if (bIsOrigin)
		{
			return m_DcdYCache[iEkiOrder][0];
		}
		else
		{
			return m_DcdYCache[iEkiOrder][1];
		}
	}
	else
	{
		int iEkiIndex = m_pCentDedDgrDia->EkiIndexOfEkiOrder(
			eRessyahoukou, iEkiOrder);
		if (bIsOrigin)
		{
			return m_DcdYCache[iEkiIndex][1];
		}
		else
		{
			return m_DcdYCache[iEkiIndex][0];
		}
	}
	return DcdPos();
}

DcdPos CRessyaDraw::YEkiTrackDgrToDcd(ERessyahoukou eRessyahoukou, int iEkiOrder,int iEkiTrackIndex )
{
	if (eRessyahoukou == ERessyahoukou::Ressyahoukou_Kudari)
	{
		return m_DcdYEkiTrackCache[iEkiOrder][iEkiTrackIndex];
	}
	else
	{
		int iEkiIndex = m_pCentDedDgrDia->EkiIndexOfEkiOrder(
			eRessyahoukou, iEkiOrder);
		return m_DcdYEkiTrackCache[iEkiIndex][iEkiTrackIndex];
	}
	return DcdPos();
}

bool CRessyaDraw::getEkiTrackExsit(ERessyahoukou eRessyahoukou, int iEkiOrder, int iEkiTrackIndex)
{
	if (eRessyahoukou == ERessyahoukou::Ressyahoukou_Kudari)
	{
		//return m_DcdYEkiTrackCache[iEkiOrder][iEkiTrackIndex] >= 0;
		return m_DcdYEkiTrackCache[iEkiOrder][iEkiTrackIndex] != INT_MIN;
	}
	else
	{
		int iEkiIndex = m_pCentDedDgrDia->EkiIndexOfEkiOrder(
			eRessyahoukou, iEkiOrder);
		//return m_DcdYEkiTrackCache[iEkiIndex][iEkiTrackIndex] >= 0;
		return m_DcdYEkiTrackCache[iEkiIndex][iEkiTrackIndex] != INT_MIN;
	}
	return false;
}

} //namespace entDgr
