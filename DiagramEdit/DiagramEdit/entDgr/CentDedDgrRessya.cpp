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
//	CentDedDgrRessya.cpp
// ****************************************************************
*/
#include "stdafx.h"

#include "CentDedDgrRessya.h"
#include "logmsg/LogMsg.h"
#include "CentDedDgrDia.h"
#include "NsOu/dynamic_castOu.h"
#include "..\entDed\entDed.h"
#include "Str/stringSplit.h"

using namespace std;

#ifndef _CONSOLE
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif //_CONSOLE

namespace entDgr {

/** 時刻の書式を保持します。 */
const CdDedJikoku::CConv	g_CdDedJikokuConv(
	true,		//	NoColon 
	// 時が 00 から 09 の場合、10の位の "0" を削除します。
	CdDedJikoku::CConv::EHour_ZeroToNone,
	CdDedJikoku::CConv::ESecond_NoSecond 	// 秒を常に出力しません。 
);
// ****************************************************************
//	CentDedDgrRessya
// ****************************************************************
	// --------------------------------
	//@name readCentDedRessya() の下請関数
	// --------------------------------
	/*
		readCentDedRessya() の下請関数
		(01)CentDedDgrRessyaの属性のうち、CentDedRessya のみで決定する属性を設定
	*/
void CentDedDgrRessya::readCentDedRessya_01_readProp(
	const CentDedRessya* pCentDedRessya/*,
	const bool bWaitOperationConnect*/)
{
	m_bIsNull = pCentDedRessya->isNull();
	m_eRessyahoukou = pCentDedRessya->getRessyahoukou();
	m_iRessyasyubetsuIndex = pCentDedRessya->getRessyasyubetsuIndex();
	m_strRessyabangou = pCentDedRessya->getRessyabangou();
	m_strRessyamei = pCentDedRessya->getRessyamei();
	m_strGousuu = pCentDedRessya->getGousuu();
	//if (m_pCentDedDgrDia->getEnableOperation() > 1 && !bWaitOperationConnect)
	//{
		//m_strOperationNumber = pCentDedRessya->getOperationNumber();
		//m_bExistBefore = pCentDedRessya->getRessyaidxOut() != INT_MIN;
	//}

	m_DgrXZone = CdDcdZone();
}
/*
	readCentDedRessya() の下請関数
	(02)CentDedDgrEkiJikoku を生成し、 CentDedEkiJikoku で決まる属性を決定。
*/
void CentDedDgrRessya::readCentDedRessya_02_CreateCentDedEkiJikoku(
	const CentDedRessya* pCentDedRessya)
{
	//	直前の駅の駅時刻。
	CdDedJikoku	aCdDedJikokuLastStation;


	//	直前の駅の駅時刻でのX座標。aCdDedJikokuLastStation がNULLの場合は
	//	無効です。
	//	最初の「NULLでない駅時刻」を見つかった場合は、その駅時刻から導出された
	//	X座標になります。
	//	2箇所目以降の「NULLでない駅時刻」以降は、
	//	前の駅時刻からの経過時間を加算します。
	//
	//	iXZahyouLastStation = iXZahyouLastStation 
	//		+ ( その駅の駅時刻 - aCdDedJikokuLastStation ) 
	//
	//	これにより、24:00をまたがって走る列車では、
	//	24:00以降の駅時刻に対応する X座標は 24:00 相当(24*60*60=86400) 以上
	//	になります。
	int	iXZahyouLastStation = 0;
	int iDgrXMin = INT_MIN;
	int iDgrXMax = INT_MIN;

	for (int iEkiOrder = 0;
		iEkiOrder < pCentDedRessya->getCentDedEkiJikokuCount();
		iEkiOrder++)
	{
		CentDedEkiJikoku aCentDedEkiJikoku
			= pCentDedRessya->getCentDedEkiJikoku(iEkiOrder);

		//	駅時刻から、X座標を計算	
		int iDgrXZahyou[2] = { INT_MIN , INT_MIN };
		for (int iChakuHatsu = 0; iChakuHatsu < 2; iChakuHatsu++)
		{
			int iX = INT_MIN;
			CdDedJikokuOrder::EEkiJikokuItem eEkiJikokuItem = CdDedJikokuOrder::EkiJikokuItem_Chaku;
			if (iChakuHatsu == 1)
			{
				eEkiJikokuItem = CdDedJikokuOrder::EkiJikokuItem_Hatsu;
			}


			CdDedJikokuOrder	aCdDedJikokuOrder;
			aCdDedJikokuOrder.setEkiOrder(iEkiOrder,
				eEkiJikokuItem);
			CdDedJikoku	aCdDedJikoku
				= pCentDedRessya->getEkiJikoku(aCdDedJikokuOrder);

			if (aCdDedJikoku.isNull())
			{
				//	NULL 時刻なら、処理なし
			}
			else if (aCdDedJikokuLastStation.isNull())
			{
				//	1回目以降の、非NULL時刻
				iX = shiftDgrXPos(aCdDedJikoku.getTotalSeconds(), iXZahyouLastStation);	//	最初の、非NULL時刻
			}
			else
			{
				//	2回目以降の、非NULL時刻
				CdDedJikan	aCdDedJikan
					= aCdDedJikoku.subJikoku(aCdDedJikokuLastStation);
				iX = iXZahyouLastStation + aCdDedJikan.getTotalSeconds();
			}
			// --------------------------------
			if (iX != INT_MIN)
			{
				aCdDedJikokuLastStation = aCdDedJikoku;
				iXZahyouLastStation = iX;
			}
			iDgrXZahyou[iChakuHatsu] = iX;
		}

		//Ver2.0 通過駅の片時刻駅において、NULL時刻側を非NULL時刻で補完し、長時間停車の補正が働かないようにするテスト
		if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka)
		{
			if (iDgrXZahyou[0] == INT_MIN &&
				iDgrXZahyou[1] != INT_MIN)
			{
				iDgrXZahyou[0] = iDgrXZahyou[1];
			}
			else if (iDgrXZahyou[0] != INT_MIN &&
				iDgrXZahyou[1] == INT_MIN)
			{
				iDgrXZahyou[1] = iDgrXZahyou[0];
			}
		}

		CentDedDgrEkiJikoku	aCentDedDgrEkiJikoku(
			aCentDedEkiJikoku.getEkiatsukai(),
			iDgrXZahyou[0],
			iDgrXZahyou[1],
			aCentDedEkiJikoku.getRessyaTrackIndex());

		m_MuCentDedDgrEkiJikoku.insert(aCentDedDgrEkiJikoku);

		if (iDgrXZahyou[0] != INT_MIN)
		{
			if (iDgrXMin == INT_MIN ||
				iDgrXMin > iDgrXZahyou[0])
			{
				iDgrXMin = iDgrXZahyou[0];
			}
			if (iDgrXMax == INT_MIN ||
				iDgrXMax < iDgrXZahyou[0])
			{
				iDgrXMax = iDgrXZahyou[0];
			}
		}
		if (iDgrXZahyou[1] != INT_MIN)
		{
			if (iDgrXMin == INT_MIN ||
				iDgrXMin > iDgrXZahyou[1])
			{
				iDgrXMin = iDgrXZahyou[1];
			}
			if (iDgrXMax == INT_MIN ||
				iDgrXMax < iDgrXZahyou[1])
			{
				iDgrXMax = iDgrXZahyou[1];
			}
		}
	}

	if (iDgrXMin != INT_MIN && iDgrXMax != INT_MIN)
	{
		m_DgrXZone.setBeginEndPos(iDgrXMin, iDgrXMax);

		//	iDgrXMinとiDgrXMaxが同一の場合は、例外的にサイズは1とします
		if (m_DgrXZone.getSize() == 0)
		{
			m_DgrXZone.setSize(1);
		}
	}
}
//void CentDedDgrRessya::readCentDedRessya_10_updateXPosNext(
//	const CentDedDia * pCentDedDia,
//	const CentDedRessya * pCentDedRessya,
//	const Mu<CentDedDgrEkiCont::CdDedDgrEki>* pMuCdDedDgrEki,
//	const CentDedEkiCont* pCentDedEkiCont)
//{
//	if (pCentDedRessya->getRessyaidxNext() == INT_MIN)
//	{
//		return;
//	}
//
//	const CentDedRessya* pCentDedRessyaNext =
//		pCentDedDia->getCentDedRessyaCont(pCentDedRessya->getRessyahoukouNext())
//		->getMuPtr()->get(pCentDedRessya->getRessyaidxNext());
//
//	m_iDgrXPosNextNoDisplay = pCentDedRessyaNext->getCentDedEkiJikoku(pCentDedRessyaNext->getSihatsuEki()).
//		getHatsujikoku(true).getTotalSeconds();
//
//	/**
//		この列車の終着駅を見て、getIncludeOppositeがfalseの場合
//			(単独駅、または分岐・環状線設定で反転駅を有効にしている駅が無い)は、
//		NoDisplayの方向は、この列車と次列車の列車方向だけで求まります。
//		ただし、在線表有の場合は、入換に注意が必要です。
//		getIncludeOppositeがtrueの場合、
//			Display側	Nextの始発作業が入換の場合は、旧処理のまま。無しの場合はOpposite確認
//			NoDisplay側	Opposite確認
//		Opposite確認作業について
//			この列車の終着駅、および次列車の始発駅について、同一駅時刻グループの駅を探します。
//			そのうち最も起点方の駅がこの列車の真の終着駅、最も終点方の駅が、次列車の真の始発駅となるので、
//			両駅のOpposite、及び両列車の列車方向を基に、路線概念上で、この運用接続が、
//			同方向なのか逆方向なのかを求めます
//			(例、ダイヤ上では、上り列車から下り列車の接続でも、上り列車が反転ONの分岐側から到着しているのなら、
//				同方向へ進んでいることになる。)
//			ただし、最終的に表示するときに、円弧が上に凸になるか下に凸になるか、
//			または、～型の左右向きがどちらになるかは、表示する駅のOppositeに依ります。
//	*/
//	if (!pMuCdDedDgrEki->get(getSyuuchakuEki()).getIncludeOpposite())
//	{
//		if (getRessyahoukou() == pCentDedRessyaNext->getRessyahoukou())
//		{
//			m_iNexthoukouNoDisplay = 1;
//		}
//		else
//		{
//			m_iNexthoukouNoDisplay = -1;
//		}
//	}
//	else
//	{
//		deque<int> iEkiOrderBrunchOriginSideChaku;
//		deque<int> iEkiOrderLoopChaku;
//		deque<int> iEkiOrderBrunchTerminalSideChaku;
//		int iResultChaku = pCentDedEkiCont->getEkiOrderBrunchLoop(
//			getSyuuchakuEki(),
//			getRessyahoukou(),
//			iEkiOrderBrunchOriginSideChaku,
//			iEkiOrderLoopChaku,
//			iEkiOrderBrunchTerminalSideChaku);
//
//		if (iResultChaku != -1)
//		{
//			const Mu<CentDedDgrEkiCont::CdDedDgrEki>* pMuCdDedDgrEkiHatsu =
//				m_pCentDedDgrDia->getCentDedDgrEkiCont()->getMuPtr(pCentDedRessya->getRessyahoukouNext());
//
//			deque<int> iEkiOrderBrunchOriginSideHatsu;
//			deque<int> iEkiOrderLoopHatsu;
//			deque<int> iEkiOrderBrunchTerminalSideHatsu;
//			int iResultHatsu = pCentDedEkiCont->getEkiOrderBrunchLoop(
//				pCentDedRessyaNext->getSihatsuEki(),
//				pCentDedRessyaNext->getRessyahoukou(),
//				iEkiOrderBrunchOriginSideHatsu,
//				iEkiOrderLoopHatsu,
//				iEkiOrderBrunchTerminalSideHatsu);
//
//			int idxl = iEkiOrderLoopChaku.size() - 1;
//			while (idxl > 0 && iEkiOrderLoopChaku[idxl] > pCentDedRessya->getSyuuchakuEki())
//			{
//				idxl--;
//			}
//			deque<int> iSameEkiOrderChaku;
//			//iEkiOrderLoopの末尾なら、終点方派生駅のチェックを行う。
//			if (idxl == 0)
//			{
//				for (int idxt = iEkiOrderBrunchTerminalSideChaku.size() - 1; idxt >= 0; idxt--)
//				{
//					CentDedDgrEkiJikoku* pCentDedDgrEkiJikokuBrunch =
//						getMuCentDedDgrEkiJikoku()->get(iEkiOrderBrunchTerminalSideChaku[idxt]);
//					if (pCentDedDgrEkiJikokuBrunch->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya ||
//						pCentDedDgrEkiJikokuBrunch->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka)
//					{
//						iSameEkiOrderChaku.push_front(iEkiOrderBrunchTerminalSideChaku[idxt]);
//						break;
//					}
//				}
//			}
//			//次に、idxl駅の駅扱いを確認
//			bool bContinueSearch = true;
//			int iLoopTerminal = iEkiOrderLoopChaku[idxl];
//			CentDedDgrEkiJikoku* pCentDedDgrEkiJikoku =
//				getMuCentDedDgrEkiJikoku()->get(iLoopTerminal);
//			if (pCentDedDgrEkiJikoku->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya ||
//				pCentDedDgrEkiJikoku->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka)
//			{
//				iSameEkiOrderChaku.push_front(iEkiOrderLoopChaku[idxl]);
//			}
//			else if (pCentDedDgrEkiJikoku->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_None)
//			{
//				bContinueSearch = false;
//			}
//			//運行無し以外なら、iLoopOrderの前駅までチェックを行う、
//			for (idxl--; idxl >= 0 && bContinueSearch; idxl--)
//			{
//				for (int ord = iLoopTerminal - 1; ord > iEkiOrderLoopChaku[idxl]; ord--)
//				{
//					CentDedDgrEkiJikoku* pCentDedDgrEkiJikokuLoop =
//						getMuCentDedDgrEkiJikoku()->get(ord);
//					if (pCentDedDgrEkiJikokuLoop->getEkiatsukai() != CentDedEkiJikoku::Ekiatsukai_Keiyunasi)
//					{
//						bContinueSearch = false;
//						break;
//
//					}
//				}
//				//終点駅の駅扱いを確認
//				if (!bContinueSearch)
//				{
//					break;
//				}
//				CentDedDgrEkiJikoku* pCentDedDgrEkiJikokuTerminal =
//					getMuCentDedDgrEkiJikoku()->get(iEkiOrderLoopChaku[idxl]);
//				if (pCentDedDgrEkiJikokuTerminal->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya ||
//					pCentDedDgrEkiJikokuTerminal->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka)
//				{
//					iSameEkiOrderChaku.push_front(iEkiOrderLoopChaku[idxl]);
//				}
//				else if (pCentDedDgrEkiJikokuTerminal->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_None)
//				{
//					break;
//				}
//				iLoopTerminal = iEkiOrderLoopChaku[idxl];
//			}
//			//iEkiOrderLoopの先頭駅にたどり着いたら、起点側派生駅のチェック
//			//ここのチェックには入れるのは、
//			//基幹駅が停車通過・経由無し
//			//基幹駅が運行無しかつiSameEkiOrderがempty
//			if (iLoopTerminal == iEkiOrderLoopChaku.front() &&
//				(bContinueSearch || iSameEkiOrderChaku.empty()))
//			{
//				for (int idxo = iEkiOrderBrunchOriginSideChaku.size() - 1; idxo >= 0; idxo--)
//				{
//					CentDedDgrEkiJikoku* pCentDedDgrEkiJikokuBrunch =
//						getMuCentDedDgrEkiJikoku()->get(iEkiOrderBrunchOriginSideChaku[idxo]);
//					if (pCentDedDgrEkiJikokuBrunch->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya ||
//						pCentDedDgrEkiJikokuBrunch->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka)
//					{
//						iSameEkiOrderChaku.push_back(iEkiOrderBrunchOriginSideChaku[idxo]);
//						break;
//					}
//				}
//			}
//
//
//			idxl = 0;
//			while (idxl < (int)iEkiOrderLoopHatsu.size() - 1 && iEkiOrderLoopHatsu[idxl] < pCentDedRessyaNext->getSihatsuEki())
//			{
//				idxl++;
//			}
//			deque<int> iSameEkiOrderHatsu;
//			//iEkiOrderLoopの頭なら、起点方派生駅のチェックを行う。
//			if (idxl == 0)
//			{
//				for (int idxo = 0; idxo < (int)iEkiOrderBrunchOriginSideHatsu.size(); idxo++)
//				{
//					CentDedEkiJikoku aCentDedEkiJikokuBrunch =
//						pCentDedRessyaNext->getCentDedEkiJikoku(iEkiOrderBrunchOriginSideHatsu[idxo]);
//					if (aCentDedEkiJikokuBrunch.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya ||
//						aCentDedEkiJikokuBrunch.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka)
//					{
//						iSameEkiOrderHatsu.push_back(iEkiOrderBrunchOriginSideHatsu[idxo]);
//						break;
//					}
//				}
//			}
//			//次に、idxl駅の駅扱いを確認
//			bContinueSearch = true;
//			int iLoopOrigin = iEkiOrderLoopHatsu[idxl];
//			CentDedEkiJikoku aCentDedEkiJikoku =
//				pCentDedRessyaNext->getCentDedEkiJikoku(iLoopOrigin);
//			if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya ||
//				aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka)
//			{
//				iSameEkiOrderHatsu.push_back(iEkiOrderLoopHatsu[idxl]);
//			}
//			else if (aCentDedEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_None)
//			{
//				bContinueSearch = false;
//				//idx駅が運行無しの場合、次ループの検索箇所はidx+1なので、idxを操作する必要なし
//			}
//			//運行無し以外なら、iLoopOrderの次駅までチェックを行う、
//			for (idxl++; idxl < (int)iEkiOrderLoopHatsu.size() && bContinueSearch; idxl++)
//			{
//				for (int ord = iLoopOrigin + 1; ord < iEkiOrderLoopHatsu[idxl]; ord++)
//				{
//					CentDedEkiJikoku aCentDedEkiJikokuLoop =
//						pCentDedRessyaNext->getCentDedEkiJikoku(ord);
//					if (aCentDedEkiJikokuLoop.getEkiatsukai() != CentDedEkiJikoku::Ekiatsukai_Keiyunasi)
//					{
//						bContinueSearch = false;
//						//idxl-1駅と、idxl駅の間で、経由無しが途切れている場合、次の大ループの検索箇所は、
//						//idxl駅になる。通常工程のインクリメントだけでよい。
//						break;
//
//					}
//				}
//				//終点駅の駅扱いを確認
//				if (!bContinueSearch)
//				{
//					break;
//				}
//				CentDedEkiJikoku aCentDedEkiJikokuTerminal =
//					pCentDedRessyaNext->getCentDedEkiJikoku(iEkiOrderLoopHatsu[idxl]);
//				if (aCentDedEkiJikokuTerminal.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya ||
//					aCentDedEkiJikokuTerminal.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka)
//				{
//					iSameEkiOrderHatsu.push_back(iEkiOrderLoopHatsu[idxl]);
//				}
//				else if (aCentDedEkiJikokuTerminal.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_None)
//				{
//					break;
//				}
//				iLoopOrigin = iEkiOrderLoopHatsu[idxl];
//			}
//			//iEkiOrderLoopの最後尾駅にたどり着いたら、終点側派生駅のチェック
//			//個々のチェックには入れるのは、
//			//基幹駅が停車通過・経由無し
//			//基幹駅が運行無しかつiSameEkiOrderがempty
//			if (iLoopOrigin == iEkiOrderLoopHatsu.back() &&
//				(bContinueSearch || iSameEkiOrderHatsu.empty()))
//			{
//				for (int idxt = 0; idxt < (int)iEkiOrderBrunchTerminalSideHatsu.size(); idxt++)
//				{
//					CentDedEkiJikoku aCentDedEkiJikokuBrunch =
//						pCentDedRessyaNext->getCentDedEkiJikoku(iEkiOrderBrunchTerminalSideHatsu[idxt]);
//					if (aCentDedEkiJikokuBrunch.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya ||
//						aCentDedEkiJikokuBrunch.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka)
//					{
//						iSameEkiOrderHatsu.push_back(iEkiOrderBrunchTerminalSideHatsu[idxt]);
//						break;
//					}
//				}
//			}
//
//			if (pMuCdDedDgrEkiHatsu->get(iSameEkiOrderHatsu.back()).getBrunchOpposite() ||
//				pMuCdDedDgrEkiHatsu->get(iSameEkiOrderHatsu.back()).getLoopOpposite())
//			{
//				if (pMuCdDedDgrEki->get(iSameEkiOrderChaku.front()).getBrunchOpposite() ||
//					pMuCdDedDgrEki->get(iSameEkiOrderChaku.front()).getLoopOpposite())
//				{
//					if (getRessyahoukou() == pCentDedRessyaNext->getRessyahoukou())
//					{
//						m_iNexthoukouNoDisplay = 1;
//					}
//					else
//					{
//						m_iNexthoukouNoDisplay = -1;
//					}
//				}
//				else
//				{
//					if (getRessyahoukou() == pCentDedRessyaNext->getRessyahoukou())
//					{
//						m_iNexthoukouNoDisplay = -1;
//					}
//					else
//					{
//						m_iNexthoukouNoDisplay = 1;
//					}
//				}
//			}
//			else
//			{
//				if (pMuCdDedDgrEki->get(iSameEkiOrderChaku.front()).getBrunchOpposite() ||
//					pMuCdDedDgrEki->get(iSameEkiOrderChaku.front()).getLoopOpposite())
//				{
//					if (getRessyahoukou() == pCentDedRessyaNext->getRessyahoukou())
//					{
//						m_iNexthoukouNoDisplay = -1;
//					}
//					else
//					{
//						m_iNexthoukouNoDisplay = 1;
//					}
//				}
//				else
//				{
//					if (getRessyahoukou() == pCentDedRessyaNext->getRessyahoukou())
//					{
//						m_iNexthoukouNoDisplay = 1;
//					}
//					else
//					{
//						m_iNexthoukouNoDisplay = -1;
//					}
//				}
//			}
//		}
//	}
//
//	//Ver2.0 当面保留
//	//CentDedRessyaTrack aCentDedRessyaTrack =
//	//	pCentDedRessyaNext->getCentDedRessyaTrack(pCentDedRessyaNext->getSihatsuEki());
//	//if (aCentDedRessyaTrack.getOperation() == CentDedRessyaTrack::Operation_Shunt)
//	//{
//	//	if (aCentDedRessyaTrack.getOperationHatsuJikoku().isNull())
//	//	{
//	//		CdDedJikoku aJikoku =
//	//			pCentDedRessyaNext->getCentDedEkiJikoku(pCentDedRessyaNext->getSihatsuEki()).getHatsujikoku(true);
//	//		m_iDgrXPosNext = aJikoku.addSeconds(-60).getTotalSeconds();
//	//	}
//	//	else
//	//	{
//	//		m_iDgrXPosNext = aCentDedRessyaTrack.getOperationHatsuJikoku().getTotalSeconds();
//	//	}
//	//	if ((getRessyahoukou() == Ressyahoukou_Kudari &&
//	//		aCentDedRessyaTrack.getRessyaTrackIndex() > aCentDedRessyaTrack.getShuntTrackIndex()) ||
//	//		(getRessyahoukou() == Ressyahoukou_Nobori &&
//	//			aCentDedRessyaTrack.getRessyaTrackIndex() < aCentDedRessyaTrack.getShuntTrackIndex()))
//	//	{
//	//		m_iNexthoukou = 2;
//
//	//	}
//	//	else
//	//	{
//	//		m_iNexthoukou = -2;
//	//	}
//	//}
//	//else
//	//{
//		m_iDgrXPosNext = m_iDgrXPosNextNoDisplay;
//		m_iNexthoukou = m_iNexthoukouNoDisplay;
//	//}
//
//	int iDgrXPosTer;
//	//if (getMuCentDedDgrRessyaTrack()->get(getSyuuchakuEki())->getOperation() == CentDedRessyaTrack::Operation_Shunt)
//	//{
//	//	iDgrXPosTer = getMuCentDedDgrRessyaTrack()->get(getSyuuchakuEki())->getDgrXPosOperationChaku();
//	//}
//	//else
//	//{
//	//	iDgrXPosTer = getMuCentDedDgrEkiJikoku()->get(getSyuuchakuEki())->getDgrXPosChaku(true);
//	//}
//	//int iDgrXPosTer = this->getMuCentDedDgrEkiJikoku()->get(this->getSyuuchakuEki())->getDgrXPosChaku(true);
//	while (m_iDgrXPosNext < iDgrXPosTer)
//	{
//		m_iDgrXPosNext += CdDedJikoku::TOTALSECONDS_A_DAY;
//		m_iDgrXPosNextNoDisplay += CdDedJikoku::TOTALSECONDS_A_DAY;
//	}
//}

//void CentDedDgrRessya::readCentDedRessya_03_updateDgrXZone()
//{
//	int iDgrXMin = INT_MIN;
//	int iDgrXMax = INT_MIN;
//	for (int idx = 0; idx < m_MuCentDedDgrEkiJikoku.size(); idx++)
//	{
//		CentDedDgrEkiJikoku	aCentDedDgrEkiJikoku
//			= m_MuCentDedDgrEkiJikoku.get(idx);
//		if (aCentDedDgrEkiJikoku.getDgrXPosChaku() != INT_MIN)
//		{
//			if (iDgrXMin == INT_MIN ||
//				iDgrXMin > aCentDedDgrEkiJikoku.getDgrXPosChaku())
//			{
//				iDgrXMin = aCentDedDgrEkiJikoku.getDgrXPosChaku();
//			}
//			if (iDgrXMax == INT_MIN ||
//				iDgrXMax < aCentDedDgrEkiJikoku.getDgrXPosChaku())
//			{
//				iDgrXMax = aCentDedDgrEkiJikoku.getDgrXPosChaku();
//			}
//		}
//
//		if (aCentDedDgrEkiJikoku.getDgrXPosHatsu() != INT_MIN)
//		{
//			if (iDgrXMin == INT_MIN ||
//				iDgrXMin > aCentDedDgrEkiJikoku.getDgrXPosHatsu())
//			{
//				iDgrXMin = aCentDedDgrEkiJikoku.getDgrXPosHatsu();
//			}
//			if (iDgrXMax == INT_MIN ||
//				iDgrXMax < aCentDedDgrEkiJikoku.getDgrXPosHatsu())
//			{
//				iDgrXMax = aCentDedDgrEkiJikoku.getDgrXPosHatsu();
//			}
//		}
//
//		//if (idx == getSihatsuEki())
//		//{
//		//	if (aCentDedDgrRessyaTrack.getOperation() == CentDedRessyaTrack::Operation_Shunt)
//		//	{
//		//		if (aCentDedDgrRessyaTrack.getDgrXPosOperationHatsu() != INT_MIN)
//		//		{
//		//			int iDgrXPosOperationHatsu = aCentDedDgrRessyaTrack.getDgrXPosOperationHatsu();
//		//			if (!m_bExistBefore)
//		//			{
//		//				iDgrXPosOperationHatsu -= 60;
//		//			}
//		//			if (iDgrXMin == INT_MIN || iDgrXMin > iDgrXPosOperationHatsu)
//		//			{
//		//				iDgrXMin = iDgrXPosOperationHatsu;
//		//			}
//		//		}
//		//	}
//		//	else//作業なしor出区or路線外始発
//		//	{
//		//		if (aCentDedDgrEkiJikoku.getDgrXPosHatsu() != INT_MIN)
//		//		{
//		//			int iDgrXPosHatsu = aCentDedDgrEkiJikoku.getDgrXPosHatsu();
//		//			if (!m_bExistBefore)
//		//			{
//		//				iDgrXPosHatsu -= 60;
//		//			}
//		//			if (iDgrXMin > iDgrXPosHatsu)
//		//			{
//		//				iDgrXMin = iDgrXPosHatsu;
//		//			}
//		//		}
//		//	}
//		//}
//
//		//if (idx == getSyuuchakuEki())
//		//{
//		//	if (aCentDedDgrRessyaTrack.getOperation() == CentDedRessyaTrack::Operation_Shunt)
//		//	{
//		//		if (aCentDedDgrRessyaTrack.getDgrXPosOperationChaku() != INT_MIN)
//		//		{
//		//			int iDgrXPosOperationChaku = aCentDedDgrRessyaTrack.getDgrXPosOperationChaku() + 60;
//		//			if (m_iDgrXPosNextNoDisplay != INT_MIN)
//		//			{
//		//				iDgrXPosOperationChaku = m_iDgrXPosNextNoDisplay;
//		//			}
//
//		//			if (iDgrXMax == INT_MIN || iDgrXMax < iDgrXPosOperationChaku)
//		//			{
//		//				iDgrXMax = iDgrXPosOperationChaku;
//		//			}
//		//		}
//		//	}
//		//	else//作業なしor入区or路線外終着
//		//	{
//		//		if (aCentDedDgrEkiJikoku.getDgrXPosChaku() != INT_MIN)
//		//		{
//		//			int iDgrXPosChaku = aCentDedDgrEkiJikoku.getDgrXPosChaku() + 60;
//		//			if (m_iDgrXPosNextNoDisplay != INT_MIN)
//		//			{
//		//				iDgrXPosChaku = m_iDgrXPosNextNoDisplay;
//		//			}
//
//		//			if (iDgrXMax < iDgrXPosChaku)
//		//			{
//		//				iDgrXMax = iDgrXPosChaku;
//		//			}
//		//		}
//		//	}
//		//}
//	}
//	if (iDgrXMin != INT_MIN && iDgrXMax != INT_MIN)
//	{
//		m_DgrXZone.setBeginEndPos(iDgrXMin, iDgrXMax);
//
//		//	iDgrXMinとiDgrXMaxが同一の場合は、例外的にサイズは1とします
//		if (m_DgrXZone.getSize() == 0)
//		{
//			m_DgrXZone.setSize(1);
//		}
//	}
//}

void CentDedDgrRessya::readCentDedRessya_04_updateShouldRessyajouhouDraw(
	const Mu<CentDedDgrEkiCont::CdDedDgrEki>* pMuCdDedDgrEki,
	const bool bRessyajouhouOmit)
{
	bool	bFirstRessyajouhouHyoujiIsSet = bRessyajouhouOmit;
	for (int iEkiOrder = 0;
		iEkiOrder < m_MuCentDedDgrEkiJikoku.size();
		iEkiOrder++)
	{
		bool	bShouldRessyajouhouDraw = false;

		CentDedDgrEkiJikoku*	pCentDedDgrEkiJikoku =
			m_MuCentDedDgrEkiJikoku.getMuPtr()->get(iEkiOrder);

		CentDedDgrEkiCont::CdDedDgrEki	aCdDedDgrEki =
			pMuCdDedDgrEki->get(iEkiOrder);

		if (isRunBetweenNextEki(iEkiOrder))
		{
			//	列車線の存在する駅間、
			CentDedDgrEki::EDiagramRessyajouhouHyouji
				eDiagramRessyajouhouHyouji =
				aCdDedDgrEki.getDiagramRessyajouhouHyouji();

			//	(1)  [この列車の列車情報がまだ1箇所も描画されていない]
			//		列車情報描画が「表示しない」以外の駅間。
			if (!bFirstRessyajouhouHyoujiIsSet &&
				eDiagramRessyajouhouHyouji !=
				CentDedDgrEki::DiagramRessyajouhouHyouji_Not)
			{
				bShouldRessyajouhouDraw = true;
			}

			//	(2)  列車情報描画が「常に表示」の駅間
			if (eDiagramRessyajouhouHyouji ==
				CentDedDgrEki::DiagramRessyajouhouHyouji_Anytime)
			{
				bShouldRessyajouhouDraw = true;

			}

		}

		pCentDedDgrEkiJikoku->setShouldRessyajouhouDraw(
			bShouldRessyajouhouDraw);
		if (bShouldRessyajouhouDraw)
		{
			bFirstRessyajouhouHyoujiIsSet = true;
		}

		//その駅の駅扱いが停車・または通過で、RessyaTrackIndexが0なら、
		//主本線に書き換えます。
		//if (pCentDedDgrEkiJikoku->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya ||
		//	pCentDedDgrEkiJikoku->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka)
		//{
		//	CentDedDgrRessyaTrack*	pCentDedDgrRessyaTrack =
		//		m_MuCentDedDgrRessyaTrack.getMuPtr()->get(iEkiOrder);
		//	if (pCentDedDgrRessyaTrack->getRessyaTrackIndex() == 0)
		//	{
		//		pCentDedDgrRessyaTrack->setRessyaTrackIndex(
		//			aCdDedDgrEki.getMainTrack());
		//	}
		//}

	}

	//	1箇所も列車情報描画位置がない場合は、
	//	最初の列車線位置に描画します。
	for (int iEkiOrder = 0;
		!bFirstRessyajouhouHyoujiIsSet
		&& iEkiOrder < m_MuCentDedDgrEkiJikoku.size();
		iEkiOrder++)
	{
		bool	bShouldRessyajouhouDraw = false;

		CentDedDgrEkiJikoku*	pCentDedDgrEkiJikoku =
			m_MuCentDedDgrEkiJikoku.getMuPtr()->get(iEkiOrder);

		CentDedDgrEkiCont::CdDedDgrEki	aCdDedDgrEki =
			pMuCdDedDgrEki->get(iEkiOrder);

		if (isRunBetweenNextEki(iEkiOrder))
		{
			//	列車線の存在する駅間、
			bShouldRessyajouhouDraw = true;
		}

		pCentDedDgrEkiJikoku->setShouldRessyajouhouDraw(
			bShouldRessyajouhouDraw);
		if (bShouldRessyajouhouDraw)
		{
			bFirstRessyajouhouHyoujiIsSet = true;
		}

	}

}


//	(05)経由なしの前後の着発時刻を補う Ver2.0運行なしの前後補完に変更
void CentDedDgrRessya::readCentDedRessya_05_complementKeiyunasiSide()
{
	for (int iEkiOrderBefore = 0;
		iEkiOrderBefore < m_MuCentDedDgrEkiJikoku.size();
		iEkiOrderBefore++)
	{
		// --------------------------------
		//	iEkiOrderBefore 以降で、以下の駅時刻の並びを探します。
		//	(1)駅扱={停車,通過}のいずれか
		//	(2)「駅扱={運行なし}」の1個以上の並び
		//	(3)駅扱={停車,通過}のいずれか
		// --------------------------------
		//	(1)駅扱={停車,通過}のいずれか の駅を探す
		CentDedDgrEkiJikoku	ekijikokuBefore =
			m_MuCentDedDgrEkiJikoku.get(iEkiOrderBefore);
		if (!(
			(ekijikokuBefore.getEkiatsukai() ==
				CentDedEkiJikoku::Ekiatsukai_Teisya ||
				ekijikokuBefore.getEkiatsukai() ==
				CentDedEkiJikoku::Ekiatsukai_Tsuuka)
			))
		{
			continue;
		}
		//iEkiOrderBefore,ekijikokuBefore = (1)駅扱={停車,通過}のいずれか

		int iEkiOrderAfter = INT_MIN;
		CentDedDgrEkiJikoku	ekijikokuAfter;
		for (iEkiOrderAfter = iEkiOrderBefore + 1;
			iEkiOrderAfter < m_MuCentDedDgrEkiJikoku.size();
			iEkiOrderAfter++)
		{
			ekijikokuAfter =
				m_MuCentDedDgrEkiJikoku.get(iEkiOrderAfter);
			if (ekijikokuAfter.getEkiatsukai() ==
				CentDedEkiJikoku::Ekiatsukai_None)
			{
				//	(2)「駅扱={運行なし}」
				//		の並び
				continue;
			}
			else if (ekijikokuBefore.getEkiatsukai() ==
				CentDedEkiJikoku::Ekiatsukai_Teisya ||
				ekijikokuBefore.getEkiatsukai() ==
				CentDedEkiJikoku::Ekiatsukai_Tsuuka)
			{
				//	(3)駅扱={停車,通過}のいずれか
				break;
			}
			else
			{
				//	条件にあてはまらない駅時刻
				//(例：着時刻ありの駅)
				iEkiOrderAfter = INT_MIN;
				break;
			}
		}
		if (iEkiOrderAfter == INT_MIN
			|| iEkiOrderAfter == m_MuCentDedDgrEkiJikoku.size())
		{
			//	条件を満たす駅が見つかりません
			continue;
		}
		//iEkiOrderAfter,ekijikokuAfter = (3)駅扱={停車,通過}のいずれか
		if (iEkiOrderBefore + 1 == iEkiOrderAfter)
		{
			//	(2)「駅扱={運行なし}」が含まれていません。
			continue;
		}

		//- 連続した経由なしの直前に着時刻がない 
		//		AND 経由なしの直後に着時刻がある場合
		//	直前の着時刻を補います。
		if (ekijikokuBefore.getDgrXPosChaku() == INT_MIN &&
			ekijikokuAfter.getDgrXPosChaku() != INT_MIN)
		{
			ekijikokuBefore.setDgrXPosChaku(ekijikokuAfter.getDgrXPosChaku());
		}

		//- 連続した経由なしの直前に発時刻がない 
		//		AND 経由なしの直後に発時刻がある場合
		//	直前の発時刻を補います。
		if (ekijikokuBefore.getDgrXPosHatsu() == INT_MIN &&
			ekijikokuAfter.getDgrXPosHatsu() != INT_MIN)
		{
			ekijikokuBefore.setDgrXPosHatsu(ekijikokuAfter.getDgrXPosHatsu());
		}

		//- 連続した経由なしの直前に着時刻がある 
		//		AND 経由なしの直後に着時刻がない場合は、
		//	直後の着時刻を補います。
		if (ekijikokuBefore.getDgrXPosChaku() != INT_MIN &&
			ekijikokuAfter.getDgrXPosChaku() == INT_MIN)
		{
			ekijikokuAfter.setDgrXPosChaku(ekijikokuBefore.getDgrXPosChaku());
		}
		//- 連続した経由なしの直前に発時刻がある 
		//		AND 経由なしの直後に発時刻がない場合は、
		//	直後の発時刻を補います。
		if (ekijikokuBefore.getDgrXPosHatsu() != INT_MIN &&
			ekijikokuAfter.getDgrXPosHatsu() == INT_MIN)
		{
			ekijikokuAfter.setDgrXPosHatsu(ekijikokuBefore.getDgrXPosHatsu());
		}


		m_MuCentDedDgrEkiJikoku.set(
			ekijikokuBefore,
			iEkiOrderBefore);
		m_MuCentDedDgrEkiJikoku.set(
			ekijikokuAfter,
			iEkiOrderAfter);
		// --------------------------------
		//	次の検索開始位置を決める
		// --------------------------------
		{
			//	(1)駅扱={停車,通過}のいずれか
			//	(3)駅扱={停車,通過}のいずれか
			//	の両方が見つかった場合は、
			//	次の検索は (3)駅扱={停車,通過}のいずれか
			//	から始めます。
			iEkiOrderBefore = iEkiOrderAfter - 1;
		}
	}
}

void CentDedDgrRessya::readCentDedRessya_06_complementLongStop_01(
	const Mu<CentDedDgrEkiCont::CdDedDgrEki>* pMuCdDedDgrEki)
{
	// --------------------------------
	//	長時間停車の着時刻を補う
	// --------------------------------
	for (int iEkiOrderBefore = 0;
		iEkiOrderBefore < m_MuCentDedDgrEkiJikoku.size();
		iEkiOrderBefore++)
	{
		// --------------------------------
		//	iEkiOrderBefore 以降で、以下の駅時刻の並びを探します。
		//	(1)(着時刻=あり or 発時刻=あり) AND 駅扱={停車,通過}のいずれか
		//	(2)「着時刻=なし、発時刻=なし、駅扱={通過,経由なし}のいずれか」
		//		の0個以上の並び
		//	(3)着時刻=なし、発時刻=あり AND 列車の終着駅でない
		// --------------------------------
		//	(1)(着時刻=あり or 発時刻=あり) AND 駅扱={停車,通過}のいずれか
		//	の駅を探す
		CentDedDgrEkiJikoku	ekijikokuBefore =
			m_MuCentDedDgrEkiJikoku.get(iEkiOrderBefore);
		if (!(
			(ekijikokuBefore.getDgrXPosChaku() != INT_MIN ||
				ekijikokuBefore.getDgrXPosHatsu() != INT_MIN) &&
				(ekijikokuBefore.getEkiatsukai() ==
					CentDedEkiJikoku::Ekiatsukai_Teisya ||
					ekijikokuBefore.getEkiatsukai() ==
					CentDedEkiJikoku::Ekiatsukai_Tsuuka)
			))
		{
			continue;
		}
		//iEkiOrderBefore,ekijikokuBefore = 
		//	(1)(着時刻=あり or 発時刻=あり) AND 駅扱={停車,通過}のいずれか

		int iEkiOrderAfter = INT_MIN;
		CentDedDgrEkiJikoku	ekijikokuAfter;
		for (iEkiOrderAfter = iEkiOrderBefore + 1;
			iEkiOrderAfter < m_MuCentDedDgrEkiJikoku.size();
			iEkiOrderAfter++)
		{

			ekijikokuAfter =
				m_MuCentDedDgrEkiJikoku.get(iEkiOrderAfter);
			if (ekijikokuAfter.getDgrXPosChaku() == INT_MIN &&
				ekijikokuAfter.getDgrXPosHatsu() == INT_MIN/* &&
				(ekijikokuAfter.getEkiatsukai() ==
					CentDedEkiJikoku::Ekiatsukai_Teisya ||
					ekijikokuAfter.getEkiatsukai() ==
					CentDedEkiJikoku::Ekiatsukai_Tsuuka ||
					ekijikokuAfter.getEkiatsukai() ==
					CentDedEkiJikoku::Ekiatsukai_Keiyunasi)*/)
			{
				//	(2)「着時刻=なし、発時刻=なし、駅扱={停車,通過,経由なし}の
				//		いずれか」の0個以上の並び
				//V2.0 暫定措置(駅扱い条件をコメントアウト)
				continue;
			}
			else if (ekijikokuAfter.getDgrXPosChaku() == INT_MIN &&
				ekijikokuAfter.getDgrXPosHatsu() != INT_MIN &&
				iEkiOrderAfter < getSyuuchakuEki())
			{
				//	(3)着時刻=なし、発時刻=あり AND 列車の終着駅でない
				break;
			}
			else
			{
				//	条件にあてはまらない駅時刻
				//(例：着時刻ありの駅・運行なしの駅)
				iEkiOrderAfter = INT_MIN;
				break;
			}
		}
		if (iEkiOrderAfter == INT_MIN
			|| iEkiOrderAfter == m_MuCentDedDgrEkiJikoku.size())
		{
			//	条件を満たす駅が見つかりません
			continue;
		}
		//iEkiOrderAfter,ekijikokuAfter = 
		//	(3)着時刻=なし、発時刻=あり AND 列車の終着駅でない

		// --------------------------------
		//	(1)の発時刻{なければ着時刻}+(1)～(3)間の駅間最小所要秒数
		//		＜(3)の発時刻-60秒なら、
		//	(3)の着時刻=(1)の発時刻+(1)～(3)間の駅間最小所要秒数
		//	とします。
		// --------------------------------

		int iDgrXPos = ekijikokuBefore.getDgrXPosHatsu();
		if (iDgrXPos == INT_MIN)
		{
			iDgrXPos = ekijikokuBefore.getDgrXPosChaku();
		}
		iDgrXPos += calcEkikanSaisyouSec(
			pMuCdDedDgrEki,
			iEkiOrderBefore,
			iEkiOrderAfter);
		//iDgrXPos = (1)の発時刻(なければ着時刻)+(1)～(3)間の駅間最小所要秒数

		if (iDgrXPos < ekijikokuAfter.getDgrXPosHatsu() - 60)
		{
			//	(1)の発時刻(なければ着時刻)+(1)～(3)間の駅間最小所要秒数
			//		＜(3)の発時刻-60秒なら、
			//	(3)の着時刻=(1)の発時刻+(1)～(3)間の駅間最小所要秒数
			//	とします。
			ekijikokuAfter.setDgrXPosChaku(iDgrXPos);
			m_MuCentDedDgrEkiJikoku.set(ekijikokuAfter, iEkiOrderAfter);
		}
		// --------------------------------
		//	次の検索開始位置を決める
		// --------------------------------
		{
			//	(1)(着時刻=あり or 発時刻=あり) AND 駅扱={停車,通過}のいずれか
			//	(3)着時刻=なし、発時刻=あり
			//	の両方が見つかった場合は、
			//	次の検索は (3)着時刻=なし、発時刻=あり
			//	から始めます。
			iEkiOrderBefore = iEkiOrderAfter - 1;
		}
	}
}

//	(06_02)長時間停車を解決
//		(長時間停車の着時刻=あり・発時刻=なし の駅に、発時刻を補う)
void CentDedDgrRessya::readCentDedRessya_06_complementLongStop_02(
	const Mu<CentDedDgrEkiCont::CdDedDgrEki>* pMuCdDedDgrEki)
{
	// --------------------------------
	//	長時間停車の着時刻を補う
	// --------------------------------
	for (int iEkiOrderBefore = 0;
		iEkiOrderBefore < m_MuCentDedDgrEkiJikoku.size();
		iEkiOrderBefore++)
	{
		// --------------------------------
		//	iEkiOrderBefore 以降で、以下の駅時刻の並びを探します。
		//	(1)着時刻=あり、発時刻=なし
		//	(2)「着時刻=なし、発時刻=なし、駅扱={通過,運行なし}のいずれか」
		//		の0個以上の並び
		//	(3)着時刻=あり、駅扱={停車,通過}のいずれか
		// --------------------------------
		//	(1)着時刻=あり、発時刻=なし
		//	の駅を探す
		CentDedDgrEkiJikoku	ekijikokuBefore =
			m_MuCentDedDgrEkiJikoku.get(iEkiOrderBefore);
		if (!(
			ekijikokuBefore.getDgrXPosChaku() != INT_MIN &&
			ekijikokuBefore.getDgrXPosHatsu() == INT_MIN
			))
		{
			continue;
		}
		//iEkiOrderBefore,ekijikokuBefore = (1)着時刻=あり、発時刻=なし

		int iEkiOrderAfter = INT_MIN;
		CentDedDgrEkiJikoku	ekijikokuAfter;
		for (iEkiOrderAfter = iEkiOrderBefore + 1;
			iEkiOrderAfter < m_MuCentDedDgrEkiJikoku.size();
			iEkiOrderAfter++)
		{
			ekijikokuAfter =
				m_MuCentDedDgrEkiJikoku.get(iEkiOrderAfter);
			if (ekijikokuAfter.getDgrXPosChaku() == INT_MIN &&
				ekijikokuAfter.getDgrXPosHatsu() == INT_MIN/* &&
				(ekijikokuAfter.getEkiatsukai() ==
					CentDedEkiJikoku::Ekiatsukai_Teisya ||
					ekijikokuAfter.getEkiatsukai() ==
					CentDedEkiJikoku::Ekiatsukai_Tsuuka ||
					ekijikokuAfter.getEkiatsukai() ==
					CentDedEkiJikoku::Ekiatsukai_Keiyunasi)*/)
			{
				//	(2)「着時刻=なし、発時刻=なし、
				//		駅扱={停車,通過,経由なし}のいずれか」
				//		の0個以上の並び
				//V2.0 暫定措置(駅扱い条件をコメントアウト)
				continue;
			}
			else if (ekijikokuAfter.getDgrXPosChaku() != INT_MIN &&
				(ekijikokuAfter.getEkiatsukai() ==
					CentDedEkiJikoku::Ekiatsukai_Teisya ||
					ekijikokuAfter.getEkiatsukai() ==
					CentDedEkiJikoku::Ekiatsukai_Tsuuka))
			{
				//	(3)着時刻=あり、駅扱={停車,通過}のいずれか
				break;
			}
			else
			{
				//	条件にあてはまらない駅時刻
				//(例：着時刻ありの駅・運行なしの駅)
				iEkiOrderAfter = INT_MIN;
				break;
			}
		}
		if (iEkiOrderAfter == INT_MIN
			|| iEkiOrderAfter == m_MuCentDedDgrEkiJikoku.size())
		{
			//	条件を満たす駅が見つかりません
			continue;
		}
		//iEkiOrderAfter,ekijikokuAfter = (3)着時刻=あり、
		//		駅扱={停車,通過}のいずれか

		// --------------------------------
		//	(1)の着時刻＜(3)の着時刻-(1)～(3)間の駅間最小所要秒数-60秒なら、
		//	(1)の発時刻=(3)の着時刻-(1)～(3)間の駅間最小所要秒数
		//	とします。
		// --------------------------------
		int iDgrXPos = ekijikokuAfter.getDgrXPosChaku();
		iDgrXPos -= calcEkikanSaisyouSec(
			pMuCdDedDgrEki,
			iEkiOrderBefore,
			iEkiOrderAfter);
		//iDgrXPos = (3)の着時刻-(1)～(3)間の駅間最小所要秒数

		if (ekijikokuBefore.getDgrXPosChaku() < iDgrXPos - 60)
		{
			//	(1)の着時刻＜(3)の着時刻-(1)～(3)間の駅間最小所要秒数-60秒なら、
			//	(1)の発時刻=(3)の着時刻-(1)～(3)間の駅間最小所要秒数
			//	とします。
			ekijikokuBefore.setDgrXPosHatsu(iDgrXPos);
			m_MuCentDedDgrEkiJikoku.set(ekijikokuBefore, iEkiOrderBefore);
		}
		// --------------------------------
		//	次の検索開始位置を決める
		// --------------------------------
		{
			//	(1)発時刻=あり、駅扱={停車,通過}のいずれか
			//	(3)着時刻=なし、発時刻=あり
			//	の両方が見つかった場合は、
			//	次の検索は (3)着時刻=なし、発時刻=あり
			//	から始めます。
			iEkiOrderBefore = iEkiOrderAfter - 1;
		}
	}
}

//(08)CentDedDgrRessyasenのコンテナを生成し、
//  CentDedDgrEkijikoku::m_iDgrXPosOnRessyasen
//を修正
void CentDedDgrRessya::readCentDedRessya_08_updateRessyasenCont(
	const Mu<CentDedDgrEkiCont::CdDedDgrEki>* pMuCdDedDgrEki)
{
	m_pCentDedDgrRessyasenCont->erase(0, INT_MAX);

	Mu<CentDedDgrEkiJikoku*>*	pMuCentDedDgrEkiJikoku
		= this->getMuCentDedDgrEkiJikoku();

	int iRessyasenKitenEkiOrder = 0;
	int iResult = 0;
	//(01)
	//『列車線起点駅Order』を探します。
	while ((iResult = updateRessyasenCont_01_calcRessyasenKiten(
		iRessyasenKitenEkiOrder,
		&iRessyasenKitenEkiOrder)) >= 0)
	{
		//iRessyasenKitenEkiOrder = 『列車線起点駅Order』


		// --------------------------------
		int iRessyasenSyuutenEkiOrder = INT_MIN;

		//(02)『列車線起点駅Order』に対応する『列車線終点駅Order』を検索します。
		//	
		//	  (1)　『列車線終点駅Order』の条件は、
		//「着時刻・発時刻の両方が指定されている」 OR
		//「 次の駅の駅扱いが『運行なし』 」 OR
		//「「『駅Order』が、その列車におけるの終着駅」 
		//	  対象駅がみつからなければ、列車線終点駅Orderの決定は失敗となります
		//  (経由なしの直前は、列車線の終点にはなりません
		//  　(この時点での列車線起点と終点は、経由なしをまたぐことがあります。)
		//
		//	  (2)　この時点で、『列車線終点駅Order』に着時刻も発時刻も
		//設定されていない場合は、
		//始発駅方向に向かって、着時刻・発時刻のいずれかが指定されている
		//駅を検索します。
		//	  この結果『列車線終点駅Order』に相当する駅がない場合は、
		//列車線終点駅Orderの決定は失敗となります。
		{
			int iResult = updateRessyasenCont_02_calcRessyasenSyuuten(
				iRessyasenKitenEkiOrder,
				&iRessyasenSyuutenEkiOrder);

			//iResult = 
			//	-	0 ;	//	『列車線終点駅Order』がみつかりました。
			//	-	-1 ;	//	列車線終点駅がありません。
			//				//	この区間に関しては、列車線を作成できません。
			if (iResult == -1)
			{
				iRessyasenKitenEkiOrder++;
				continue;
			}
			//iRessyasenSyuutenEkiOrder = 『列車線終点駅Order』（補正前）
		}
		//(04)
		//	『ダイヤグラム列車線』オブジェクト内の
		//	『列車線起点駅Order』と『列車線終点駅Order』の間の
		//	途中駅で、着時刻・発時刻のいずれかが指定されている主要駅があれば、
		//	それを
		//	『列車線終点駅Order』と『列車線終点時刻』にします。
		updateRessyasenCont_04_adjustRessyasenSyuuten4(
			pMuCdDedDgrEki,
			iRessyasenKitenEkiOrder,
			&iRessyasenSyuutenEkiOrder);
		LogMsgL(3, _T("updateRessyasenCont_adjustRessyasenSyuuten4()4")
			_T(" Kiten=%d Syuuten=%d"),
			iRessyasenKitenEkiOrder, iRessyasenSyuutenEkiOrder);

		// --------------------------------
		{
			bool	bRetryRequested = false;
			do {
				bRetryRequested = false;

				//	『列車線起点』と『列車線終点』の間に、列車線を生成
				CentDedDgrRessyasen	aRessyasen(
					iRessyasenKitenEkiOrder, iRessyasenSyuutenEkiOrder);
				m_pCentDedDgrRessyasenCont->insert(aRessyasen);

				//(05)
				//『列車線コンテナ CentDedDgrRessyasenCont 』の末尾の
				//『列車線 CentDedDgrRessyasen』の途中駅の中で、
				//列車線の位置(CentDedDgrEkiJikoku::m_iDgrXPosRessyasen)と
				//着時刻・発時刻
				//(CentDedDgrEkiJikoku::m_iDgrXPosChaku,m_iDgrXPosHatsu)の
				//差が60 秒以上ある場合は、その駅を『列車線終点駅Order』と
				//	します。
				{
					int iResult = updateRessyasenCont_05_adjustRessyasenSyuuten5(
						&iRessyasenSyuutenEkiOrder);
					//iResult = 
					//-	0 ;	//	『列車線終点駅Order』の補正の必要はありません
					//		//	でした。
					//-	1 ;	//	『列車線終点駅Order』の補正を行いました。
					if (iResult == 1)
					{
						//iRessyasenSyuutenEkiOrder = 
						//	『列車線終点駅Order』は修正されました。

						//	末尾の列車線を削除
						m_pCentDedDgrRessyasenCont->erase(INT_MAX);

						bRetryRequested = true;
					}
				}
			} while (bRetryRequested);
		}


		//(06)	コンテナ末尾の列車線が途中に「経由なし」を含む場合、
		//	その列車線を「経由なし」までに短縮します。
		//	(1)「経由なし」直前の駅・直後の駅の着・発時刻を「列車線駅時刻」に
		//	置き換えます。
		//	(2)列車線は「経由なし」直前までに短縮します。
		//	(3)列車線終点を「経由なし」の直前とします。
		{
			int iResult = updateRessyasenCont_06_reduceToKeiyunasi(
				&iRessyasenSyuutenEkiOrder);
		}
		//(07)コンテナ末尾の列車線が途中に「在線表表示駅」を含む場合、
		//	その列車線を「在線表表示駅」までに短縮します。
		//	(1)「在線表表示駅」の着・発時刻を「列車線駅時刻」に
		//	置き換えます。
		//	(2)列車線は「在線表表示駅」までに短縮します。
		//	(3)列車線終点を「在線表表示駅」とします。
		{
			int iResult = updateRessyasenCont_07_reduceToTrackDisplay(
				pMuCdDedDgrEki,
				&iRessyasenSyuutenEkiOrder);

		}

		//	列車線起点駅は、直前の終点駅とします。
		iRessyasenKitenEkiOrder = iRessyasenSyuutenEkiOrder;

	}
}

void CentDedDgrRessya::readCentDedRessya_11_updateRessyaTrackLineCont(
	const CentDedRessya * pCentDedRessya, 
	const Mu<CentDedDgrEkiCont::CdDedDgrEki>* pMuCdDedDgrEki, 
	const CentDedEkiCont * pCentDedEkiCont)
{
	int iValidSihatsuEki = pCentDedRessya->getValidSihatsuEki();
	int iValidSyuuchakuEki = pCentDedRessya->getValidSyuuchakuEki();
	if (iValidSihatsuEki == -1 || iValidSyuuchakuEki == -1 || iValidSihatsuEki >= iValidSyuuchakuEki)
	{
		return;
	}
	//========================================================================================================================================================================================================================================================
	//ここから始発駅
	/**
		始発駅
		Zaisenの生成は、後作業→発着番線→前作業の順に行います。
		ただし、発着番線の着時刻は前作業を、発時刻は後作業を見ないと確定できないので、
		後作業の探索で、発時刻を保持しておく必要があります
	*/
	{
		deque<Zaisen> contZaisen;
		deque<Zaisen> contZaisenNoDisplay;

		const CentDedEkiJikoku* pEkiJikoku = pCentDedRessya->getCentDedEkiJikokuCont()
			->getMuPtr()->get(iValidSihatsuEki);
		const CentDedBeforeOperationCont* pBeforeCont =
			pEkiJikoku->getCentDedBeforeOperationCont();
		const CentDedAfterOperationCont* pAfterCont =
			pEkiJikoku->getCentDedAfterOperationCont();
		int iRessyaTrack = pEkiJikoku->getRessyaTrackIndex();
		int iDgrXPosBase = getMuCentDedDgrEkiJikoku()->get(iValidSihatsuEki)->getDgrXPosHatsu();
		int iTsuukaTeisya = 2;
		if (pEkiJikoku->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka)
		{
			iTsuukaTeisya = 1;
		}

		/**
			この駅の発着番線および前作業に対するZaisenの、発時刻になります。
			まずは、発着番線に対する発時刻を後作業探索で求めます。
			有効な入換作業がある場合は、その入換発時刻(複数ある場合は最も手前の物)
			無い場合は、当駅発時刻になります。

			前作業探索で、最初に有効な入換が見つかった場合は、この値を基に、発着番線に対するZaisenを作成します、
			その後は、前作業探索において、一つ後ろの入換発時刻を保持する変数として使用します。

		*/
		int iDgrXPosHatsu = INT_MIN;
		/**
			後作業探索において、一つ前の入換着時刻を保持するための変数です。
		*/
		int iDgrXPosChaku = INT_MIN;
		/**
			この列車の起点時刻です。
			この列車の先端作業が、出区・路線外始発の場合は、それらの作業から起点時刻をとりますが、
			前列車接続で起点時刻未設定かつ、運用無効もしくは前列車が無い場合は、
			他作業及び当駅発時刻から、起点時刻を導く必要があります。
		*/
		int iDgrXPosOrigin = INT_MIN;

		/**
			bTsuukaOuterJikokuNull
			始発駅の駅扱いが通過で、路線外始発かつ当駅着時刻がNULLの場合は、
			路線外始発作業以外は無効になります。
			したがって、下記の前作業・後作業検索はスキップします。
		*/
		bool bTsuukaOuterJikokuNull =
			pEkiJikoku->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka &&
			pBeforeCont->getMuPtr()->get(0)->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer &&
			pBeforeCont->getMuPtr()->get(0)->getChakuJikoku().isNull();
		if (bTsuukaOuterJikokuNull)
		{
			iTsuukaTeisya = 0;
		}

		for (int idxa = 0; idxa < (int)pAfterCont->size() && !bTsuukaOuterJikokuNull; idxa++)
		{
			const CentDedAfterOperation* pAfterOperation = pAfterCont->getMuPtr()->get(idxa);
			if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
			{
				if (pAfterOperation->getShuntTrackIndex() != iRessyaTrack)
				{
					/**
						iDgrXPosChakuMainが初期値の場合は、
						この作業の入換着時刻が、発着番線の着時刻になります。
						それ以外の場合は、一つ先の入換番線の着時刻となります。
					*/
					if (iDgrXPosHatsu == INT_MIN)
					{
						iDgrXPosHatsu = pAfterOperation->getOperationHatsuJikoku().getTotalSeconds();
						iDgrXPosChaku = pAfterOperation->getOperationChakuJikoku(true).getTotalSeconds();
						iRessyaTrack = pAfterOperation->getShuntTrackIndex();
					}
					else
					{
						Zaisen aZaisen(iRessyaTrack,
							shiftDgrXPos(iDgrXPosChaku, iDgrXPosBase,true),
							shiftDgrXPos(pAfterOperation->getOperationHatsuJikoku().getTotalSeconds(), iDgrXPosBase, true));
						contZaisen.push_back(aZaisen);

						iDgrXPosChaku = pAfterOperation->getOperationChakuJikoku(true).getTotalSeconds();
						iRessyaTrack = pAfterOperation->getShuntTrackIndex();
					}
					if (iDgrXPosOrigin == INT_MIN)
					{
						iDgrXPosOrigin = pAfterOperation->getOperationHatsuJikoku().getTotalSeconds();
					}
				}
			}
			else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
			{
				updateRessyaTrackLineBeforeCont(
					pAfterOperation->getCentDedBeforeOperationCont(),
					iValidSihatsuEki,
					iRessyaTrack,
					shiftDgrXPos(pAfterOperation->getConnectJikoku().getTotalSeconds(), iDgrXPosBase, true),
					iTsuukaTeisya,
					true,
					pMuCdDedDgrEki,
					pCentDedEkiCont);
				if (iDgrXPosOrigin == INT_MIN)
				{
					iDgrXPosOrigin = pAfterOperation->getConnectJikoku().getTotalSeconds();
				}
			}
			else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
			{
				updateRessyaTrackLineAfterCont(
					pAfterOperation->getCentDedAfterOperationCont(),
					iValidSihatsuEki,
					iRessyaTrack,
					shiftDgrXPos(pAfterOperation->getReleaseJikoku().getTotalSeconds(), iDgrXPosBase, true),
					iTsuukaTeisya,
					true,
					pMuCdDedDgrEki,
					pCentDedEkiCont);
				if (iDgrXPosOrigin == INT_MIN)
				{
					iDgrXPosOrigin = pAfterOperation->getReleaseJikoku().getTotalSeconds();
				}
			}

		}
		if (iDgrXPosChaku != INT_MIN)
		{
			Zaisen aZaisen(iRessyaTrack,
				shiftDgrXPos(iDgrXPosChaku, iDgrXPosBase, true),
				shiftDgrXPos(pEkiJikoku->getHatsujikoku().getTotalSeconds(), iDgrXPosBase, true));
			contZaisen.push_back(aZaisen);
		}
		if (iDgrXPosHatsu == INT_MIN)
		{
			iDgrXPosHatsu = pEkiJikoku->getHatsujikoku().getTotalSeconds();
		}
		if (iDgrXPosOrigin == INT_MIN)
		{
			iDgrXPosOrigin = pEkiJikoku->getHatsujikoku().getTotalSeconds();
		}

		iRessyaTrack = pEkiJikoku->getRessyaTrackIndex();

		/**
			前作業探索において、一つ後ろの入換発時刻を保持するための変数です。
		*/
		for (int idxb = (int)pBeforeCont->size() - 1; idxb > 0 && !bTsuukaOuterJikokuNull; idxb--)
		{
			const CentDedBeforeOperation* pBeforeOperation = pBeforeCont->getMuPtr()->get(idxb);
			if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
			{
				if (pBeforeOperation->getShuntTrackIndex() != iRessyaTrack)
				{
					Zaisen aZaisen(iRessyaTrack,
						shiftDgrXPos(pBeforeOperation->getOperationChakuJikoku(true).getTotalSeconds(), iDgrXPosBase, true),
						shiftDgrXPos(iDgrXPosHatsu, iDgrXPosBase, true));
					contZaisen.push_front(aZaisen);

					iDgrXPosHatsu = pBeforeOperation->getOperationHatsuJikoku().getTotalSeconds();
					iRessyaTrack= pBeforeOperation->getShuntTrackIndex();
					iDgrXPosOrigin = pBeforeOperation->getOperationHatsuJikoku().getTotalSeconds();
				}
			}
			else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
			{
				updateRessyaTrackLineBeforeCont(
					pBeforeOperation->getCentDedBeforeOperationCont(),
					iValidSihatsuEki,
					iRessyaTrack,
					shiftDgrXPos(pBeforeOperation->getConnectJikoku().getTotalSeconds(), iDgrXPosBase, true),
					iTsuukaTeisya,
					true,
					pMuCdDedDgrEki,
					pCentDedEkiCont);
				iDgrXPosOrigin = pBeforeOperation->getConnectJikoku().getTotalSeconds();
			}
			else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
			{
				updateRessyaTrackLineAfterCont(
					pBeforeOperation->getCentDedAfterOperationCont(),
					iValidSihatsuEki,
					iRessyaTrack,
					shiftDgrXPos(pBeforeOperation->getReleaseJikoku().getTotalSeconds(), iDgrXPosBase, true),
					iTsuukaTeisya,
					true,
					pMuCdDedDgrEki,
					pCentDedEkiCont);
				iDgrXPosOrigin = pBeforeOperation->getReleaseJikoku().getTotalSeconds();
			}
		}

		int iChakuOperation = 0;
		int iChakuOperationNoDisplay = 0;
		int iPrevRessyahoukou = 0;
		int iPrevRessyahoukouNoDisplay = 0;
		int iEkiOrderOfPrevSyuuchakuEki = iValidSihatsuEki;
		int iOuterEkiIndex;

		const CentDedBeforeOperation* pFirstOperation = pBeforeCont->getMuPtr()->get(0);
		if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Out)
		{
			tstring strOperationNumber;
			if (getCentDedDgrDia()->getEnableOperation() > 1)
			{
				strOperationNumber = joinc('+', pFirstOperation->getOperationNumber(), true);
			}
			Zaisen aZaisen(iRessyaTrack,
				shiftDgrXPos(pFirstOperation->getOutJikoku().getTotalSeconds(), iDgrXPosBase, true),
				shiftDgrXPos(iDgrXPosHatsu, iDgrXPosBase, true),
				strOperationNumber);
			contZaisen.push_front(aZaisen);
			Zaisen aZaisenNoDisplay(
				0,
				shiftDgrXPos(pEkiJikoku->getHatsujikoku().getTotalSeconds(), iDgrXPosBase, true),
				shiftDgrXPos(pEkiJikoku->getHatsujikoku().getTotalSeconds(), iDgrXPosBase, true),
				strOperationNumber);
			contZaisenNoDisplay.push_front(aZaisenNoDisplay);

			iChakuOperation = 3;
			iChakuOperationNoDisplay = 3;

			int iDgrXPosOut = shiftDgrXPos(pFirstOperation->getOutJikoku().getTotalSeconds(), iDgrXPosBase, true) - 120;
			if (m_DgrXZone.getPos() > iDgrXPosOut)
			{
				m_DgrXZone.setBeginEndPos(iDgrXPosOut, m_DgrXZone.getEndPos());
			}
		}
		else if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
		{
			iOuterEkiIndex = pFirstOperation->getOuterShihatsuekiIndex();
			tstring strOperationNumber;

			if (getCentDedDgrDia()->getEnableOperation() > 1)
			{
				strOperationNumber = joinc('+', pFirstOperation->getOperationNumber(), true);
			}
			int iDgrXPosChakuTemp = pFirstOperation->getChakuJikoku().getTotalSeconds();
			if (iDgrXPosChakuTemp == INT_MIN)
			{
				iDgrXPosChakuTemp = iDgrXPosHatsu;
			}
			Zaisen aZaisen(iRessyaTrack,
				shiftDgrXPos(iDgrXPosChakuTemp, iDgrXPosBase, true),
				shiftDgrXPos(iDgrXPosHatsu, iDgrXPosBase, true),
				strOperationNumber);
			contZaisen.push_front(aZaisen);
			Zaisen aZaisenNoDisplay(
				0,
				shiftDgrXPos(iDgrXPosChakuTemp, iDgrXPosBase, true),
				shiftDgrXPos(pEkiJikoku->getHatsujikoku().getTotalSeconds(), iDgrXPosBase, true),
				strOperationNumber);
			contZaisenNoDisplay.push_front(aZaisenNoDisplay);

			iChakuOperation = 4;
			iChakuOperationNoDisplay = 4;

			int iDgrXPosOuter = shiftDgrXPos(iDgrXPosChakuTemp, iDgrXPosBase, true) - 120;
			if (m_DgrXZone.getPos() > iDgrXPosOuter)
			{
				m_DgrXZone.setBeginEndPos(iDgrXPosOuter, m_DgrXZone.getEndPos());
			}
		}
		else if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Junction)
		{
			tstring strOperationNumber;
			if (!pFirstOperation->getIsSyubetsuChange()&&
				getCentDedDgrDia()->getEnableOperation() > 0)
			{
				strOperationNumber = joinc('+', pFirstOperation->getOperationNumber(), true);
			}
			int iDgrXPosJunction = INT_MIN;
			if (!pFirstOperation->getJunctionJikoku().isNull() &&
				getCentDedDgrDia()->getEnableOperation() > 0)
			{
				iChakuOperation = 5;
				iDgrXPosOrigin = pFirstOperation->getJunctionJikoku().getTotalSeconds();
				iPrevRessyahoukou = pFirstOperation->getPrevRessyahoukou();

				iDgrXPosJunction = shiftDgrXPos(pFirstOperation->getJunctionJikoku().getTotalSeconds(), iDgrXPosBase, true);
			}
			else if (!pFirstOperation->getOriginJikoku().isNull())
			{
				iDgrXPosOrigin = pFirstOperation->getOriginJikoku().getTotalSeconds();

				iDgrXPosJunction = shiftDgrXPos(pFirstOperation->getOriginJikoku().getTotalSeconds(), iDgrXPosBase, true);
			}
			else if ((iDgrXPosHatsu - iDgrXPosOrigin) < 60)
			{
				iDgrXPosOrigin = iDgrXPosHatsu - 60;

				iDgrXPosJunction = shiftDgrXPos(iDgrXPosHatsu - 60, iDgrXPosBase, true);
			}
			
			if (getCentDedDgrDia()->getEnableOperation() > 0)
			{
				iEkiOrderOfPrevSyuuchakuEki = pFirstOperation->getEkiOrderOfPrevSyuuchakuEki();
			}

			Zaisen aZaisen(iRessyaTrack,
				shiftDgrXPos(iDgrXPosOrigin, iDgrXPosBase, true),
				shiftDgrXPos(iDgrXPosHatsu, iDgrXPosBase, true),
				strOperationNumber);
			contZaisen.push_front(aZaisen);

			int iDgrXPosJunctionND = INT_MIN;
			if (!pFirstOperation->getJunctionJikokuNoDisplay().isNull() &&
				getCentDedDgrDia()->getEnableOperation() > 0)
			{
				iChakuOperationNoDisplay = 5;
				iPrevRessyahoukouNoDisplay = pFirstOperation->getPrevRessyahoukouNoDisplay();
				Zaisen aZaisenNoDisplay(
					0,
					shiftDgrXPos(pFirstOperation->getJunctionJikokuNoDisplay().getTotalSeconds(), iDgrXPosBase, true),
					shiftDgrXPos(pEkiJikoku->getHatsujikoku().getTotalSeconds(), iDgrXPosBase, true),
					strOperationNumber);
				contZaisenNoDisplay.push_front(aZaisenNoDisplay);

				iDgrXPosJunctionND = shiftDgrXPos(pFirstOperation->getJunctionJikokuNoDisplay().getTotalSeconds(), iDgrXPosBase, true);
			}
			else
			{
				Zaisen aZaisenNoDisplay(
					0,
					shiftDgrXPos(pEkiJikoku->getHatsujikoku().getTotalSeconds(), iDgrXPosBase, true),
					shiftDgrXPos(pEkiJikoku->getHatsujikoku().getTotalSeconds(), iDgrXPosBase, true));
				contZaisenNoDisplay.push_front(aZaisenNoDisplay);
			}

			if (iDgrXPosJunction != INT_MIN && m_DgrXZone.getPos() > iDgrXPosJunction)
			{
				m_DgrXZone.setBeginEndPos(iDgrXPosJunction, m_DgrXZone.getEndPos());
			}

			if (iDgrXPosJunctionND != INT_MIN && m_DgrXZone.getPos() > iDgrXPosJunctionND)
			{
				m_DgrXZone.setBeginEndPos(iDgrXPosJunctionND, m_DgrXZone.getEndPos());
			}
		}
		/**
			Zaisenコンテナが完成したら、RessyaTrackLine形式に仕立てる。
			分岐・環状線で関係する駅全ての分を、ここで生成します。
			なお、先端作業が前列車接続で、運用無効or前列車が無い場合かつ、発側に補助列車線が無い場合は、描写するものが無いので、

			iPosition:-1
				単独駅、自駅分の生成のみを行う
			iPosition:INT_MIN
				起点側派生駅
				基幹駅群、分岐駅群全てで生成を行います。
			iPosition:0-
				基幹駅・起点駅・終点駅
				基幹駅群、分岐駅群全てで生成を行います。
			iPosition:INT_MAX
				終点側派生駅
				基幹駅群、分岐駅群全てで生成を行います。
		*/
		deque<int> iEkiOrderBrunchOriginSide;
		deque<int> iEkiOrderLoop;
		deque<int> iEkiOrderBrunchTerminalSide;
		int iPosition = pCentDedEkiCont->getEkiOrderBrunchLoop(
			iValidSihatsuEki,
			getRessyahoukou(),
			iEkiOrderBrunchOriginSide,
			iEkiOrderLoop,
			iEkiOrderBrunchTerminalSide);
		CentDedDgrEkiCont::CdDedDgrEki aEki = pMuCdDedDgrEki->get(iValidSihatsuEki);
		if (iPosition == -1)
		{
			if (aEki.getDiagramTrackDisplay())
			{
				CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
					iValidSihatsuEki,
					iTsuukaTeisya,
					iChakuOperation,
					-1,
					true);
				aCentDedDgrRessyaTrackLine.setZaisen(contZaisen);
				aCentDedDgrRessyaTrackLine.setPrevRessyahoukou(iPrevRessyahoukou);
				if (iChakuOperation == 4)
				{
					aCentDedDgrRessyaTrackLine.setOuterEkiIndex(iOuterEkiIndex);
				}
				m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
			}
			else if(iChakuOperationNoDisplay != 0)
			{
				/**
					前列車の終着駅の反転駅設定と、表示駅の反転駅設定を見て、
					片方のみtrueの場合は、前列車方向が変化します。
				*/
				int iPrevRessyahoukouNoDisplayThis = iPrevRessyahoukouNoDisplay;
				if (iPrevRessyahoukouNoDisplayThis != 0 &&
					iValidSihatsuEki != iEkiOrderOfPrevSyuuchakuEki)
				{
					CentDedDgrEkiCont::CdDedDgrEki aEkiSyuuchaku = pMuCdDedDgrEki->get(iEkiOrderOfPrevSyuuchakuEki);
					if (aEki.getBrunchOpposite() !=
						(aEkiSyuuchaku.getBrunchOpposite() ||
							aEkiSyuuchaku.getLoopOpposite()))
					{
						iPrevRessyahoukouNoDisplayThis *= -1;
					}
				}
				CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
					iValidSihatsuEki,
					iTsuukaTeisya,
					iChakuOperationNoDisplay,
					-1,
					false);
				aCentDedDgrRessyaTrackLine.setZaisen(contZaisenNoDisplay);
				aCentDedDgrRessyaTrackLine.setPrevRessyahoukou(iPrevRessyahoukouNoDisplayThis);
				if (iChakuOperation == 4)
				{
					aCentDedDgrRessyaTrackLine.setOuterEkiIndex(iOuterEkiIndex);
				}
				m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
			}
		}
		else //if (iPosition != -1)
		{
			for (int idxo = 0; idxo < (int)iEkiOrderBrunchOriginSide.size(); idxo++)
			{
				CentDedDgrEkiCont::CdDedDgrEki aEkiOrigin = pMuCdDedDgrEki->get(iEkiOrderBrunchOriginSide[idxo]);
				//const CentDedEki* pEkiLoop = pCentDedEkiCont->getMuPtr()->get(
				//	pCentDedEkiCont->EkiIndexOfEkiOrder(getRessyahoukou(), iEkiOrderBrunchOriginSide[idxo]));
				int iHatsuOperation = -1;
				/**
					iHatsuOperationを決定する。
					iEkiOrderBrunchOriginSide[idxo]がiValidSihatsuEkiの場合は、-1
					それ以外の場合は、
					(1)iValidSihatsuEkiとiEkiOrderBrunchOriginSide[idxo]が共に反転、もしくはともに無反転の場合は、-2(終点方)
						どちらかのみ反転の場合は-4(起点方へ発車)
				*/
				if (iEkiOrderBrunchOriginSide[idxo] != iValidSihatsuEki)
				{
					if ((aEki.getBrunchOpposite() || aEki.getLoopOpposite()) ==
						aEkiOrigin.getBrunchOpposite())
					{
						iHatsuOperation = -2;
					}
					else
					{
						iHatsuOperation = -4;
					}
				}
				if (aEkiOrigin.getDiagramTrackDisplay())
				{
					/**
						iPrevRessyahoukouが2,-2の場合は反転駅設定は影響なし
						表示駅と前列車終着駅が同じ場合も、反転駅設定は影響なし
					*/
					int iPrevRessyahoukouThis = iPrevRessyahoukou;
					if ((iPrevRessyahoukouThis == 1 ||
						iPrevRessyahoukouThis == -1) &&
						iEkiOrderBrunchOriginSide[idxo] != iEkiOrderOfPrevSyuuchakuEki)
					{
						CentDedDgrEkiCont::CdDedDgrEki aEkiSyuuchaku = pMuCdDedDgrEki->get(iEkiOrderOfPrevSyuuchakuEki);
						if (aEkiOrigin.getBrunchOpposite() !=
							(aEkiSyuuchaku.getBrunchOpposite() ||
								aEkiSyuuchaku.getLoopOpposite()))
						{
							iPrevRessyahoukouThis *= -1;
						}

					}
					CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
						iEkiOrderBrunchOriginSide[idxo],
						iTsuukaTeisya,
						iChakuOperation,
						iHatsuOperation,
						true);
					aCentDedDgrRessyaTrackLine.setZaisen(contZaisen);
					aCentDedDgrRessyaTrackLine.setPrevRessyahoukou(iPrevRessyahoukouThis);
					if (iChakuOperation == 4)
					{
						aCentDedDgrRessyaTrackLine.setOuterEkiIndex(iOuterEkiIndex);
					}
					m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
				}
				//起点側分岐駅では、在線表非表示の場合表示するものはありません
				// 
				// 
				//else if (iEkiOrderBrunchOriginSide[idxo] == iValidSihatsuEki &&
				//	iChakuOperationNoDisplay != 0 ||
				//	iHatsuOperation == -2 || iHatsuOperation == -4)
				//{
				//	/**
				//		前列車の終着駅の反転駅設定と、表示駅の反転駅設定を見て、
				//		片方のみtrueの場合は、前列車方向が変化します。
				//	*/
				//	int iPrevRessyahoukouNoDisplayThis = iPrevRessyahoukouNoDisplay;
				//	if (iPrevRessyahoukouNoDisplayThis != 0 &&
				//		iEkiOrderBrunchOriginSide[idxo] != iEkiOrderOfPrevSyuuchakuEki)
				//	{
				//		CentDedDgrEkiCont::CdDedDgrEki aEkiSyuuchaku = pMuCdDedDgrEki->get(iEkiOrderOfPrevSyuuchakuEki);
				//		if ((aEkiOrigin.getBrunchOpposite() ||
				//			aEkiOrigin.getLoopOpposite()) !=
				//			(aEkiSyuuchaku.getBrunchOpposite() ||
				//				aEkiSyuuchaku.getLoopOpposite()))
				//		{
				//			iPrevRessyahoukouNoDisplayThis *= -1;
				//		}
				//	}
				//	CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
				//		iEkiOrderBrunchOriginSide[idxo],
				//		iTsuukaTeisya,
				//		iChakuOperationNoDisplay,
				//		iHatsuOperation,
				//		false);
				//	aCentDedDgrRessyaTrackLine.setZaisen(contZaisenNoDisplay);
				//	aCentDedDgrRessyaTrackLine.setPrevRessyahoukou(iPrevRessyahoukouNoDisplayThis);
				//	if (iChakuOperation == 4)
				//	{
				//		aCentDedDgrRessyaTrackLine.setOuterEkiIndex(iOuterEkiIndex);
				//	}
				//	m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
				//}
			}

			for (int idxl = 0; idxl < (int)iEkiOrderLoop.size(); idxl++)
			{
				CentDedDgrEkiCont::CdDedDgrEki aEkiLoop = pMuCdDedDgrEki->get(iEkiOrderLoop[idxl]);
				int iHatsuOperation = -1;
				/**
					iHatsuOperationを決定する。
					iEkiOrderLoop[idxl]がiValidSihatsuEkiの場合は、-1
					それ以外の場合は、
					(1)iValidSihatsuEkiとiEkiOrderLoop[idxl]が共に反転、もしくはともに無反転の場合は、-2(終点方)
						どちらかのみ反転の場合は-4(起点方へ発車)
				*/
				if (iEkiOrderLoop[idxl] != iValidSihatsuEki)
				{
					if ((aEki.getBrunchOpposite() || aEki.getLoopOpposite()) ==
						aEkiLoop.getLoopOpposite())
					{
						iHatsuOperation = -2;
					}
					else
					{
						iHatsuOperation = -4;
					}
				}
				if (aEkiLoop.getDiagramTrackDisplay())
				{
					/**
						iPrevRessyahoukouが2,-2の場合は反転駅設定は影響なし
						表示駅と前列車終着駅が同じ場合も、反転駅設定は影響なし
					*/
					int iPrevRessyahoukouThis = iPrevRessyahoukou;
					if ((iPrevRessyahoukouThis == 1 ||
						iPrevRessyahoukouThis == -1) &&
						iEkiOrderLoop[idxl] != iEkiOrderOfPrevSyuuchakuEki)
					{
						CentDedDgrEkiCont::CdDedDgrEki aEkiSyuuchaku = pMuCdDedDgrEki->get(iEkiOrderOfPrevSyuuchakuEki);
						if ((aEkiLoop.getBrunchOpposite() ||
							aEkiLoop.getLoopOpposite()) !=
							(aEkiSyuuchaku.getBrunchOpposite() ||
								aEkiSyuuchaku.getLoopOpposite()))
						{
							iPrevRessyahoukouThis *= -1;
						}

					}
					CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
						iEkiOrderLoop[idxl],
						iTsuukaTeisya,
						iChakuOperation,
						iHatsuOperation,
						true);
					aCentDedDgrRessyaTrackLine.setZaisen(contZaisen);
					aCentDedDgrRessyaTrackLine.setPrevRessyahoukou(iPrevRessyahoukouThis);
					if (iChakuOperation == 4)
					{
						aCentDedDgrRessyaTrackLine.setOuterEkiIndex(iOuterEkiIndex);
					}
					m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
				}
				else if (iChakuOperationNoDisplay != 0 ||
					iHatsuOperation == -2 || iHatsuOperation == -4)
				{
					/**
						前列車の終着駅の反転駅設定と、表示駅の反転駅設定を見て、
						片方のみtrueの場合は、前列車方向が変化します。
					*/
					int iPrevRessyahoukouNoDisplayThis = iPrevRessyahoukouNoDisplay;
					if (iPrevRessyahoukouNoDisplayThis != 0 &&
						iEkiOrderLoop[idxl] != iEkiOrderOfPrevSyuuchakuEki)
					{
						CentDedDgrEkiCont::CdDedDgrEki aEkiSyuuchaku = pMuCdDedDgrEki->get(iEkiOrderOfPrevSyuuchakuEki);
						if ((aEkiLoop.getBrunchOpposite() ||
							aEkiLoop.getLoopOpposite()) !=
							(aEkiSyuuchaku.getBrunchOpposite() ||
								aEkiSyuuchaku.getLoopOpposite()))
						{
							iPrevRessyahoukouNoDisplayThis *= -1;
						}
					}
					CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
						iEkiOrderLoop[idxl],
						iTsuukaTeisya,
						iChakuOperationNoDisplay,
						iHatsuOperation,
						false);
					aCentDedDgrRessyaTrackLine.setZaisen(contZaisenNoDisplay);
					aCentDedDgrRessyaTrackLine.setPrevRessyahoukou(iPrevRessyahoukouNoDisplayThis);
					if (iChakuOperation == 4)
					{
						aCentDedDgrRessyaTrackLine.setOuterEkiIndex(iOuterEkiIndex);
					}
					m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
				}
			}

			for (int idxt = 0; idxt < (int)iEkiOrderBrunchTerminalSide.size(); idxt++)
			{
				CentDedDgrEkiCont::CdDedDgrEki aEkiTerminal = pMuCdDedDgrEki->get(iEkiOrderBrunchTerminalSide[idxt]);
				int iHatsuOperation = -1;
				/**
					iHatsuOperationを決定する。
					iEkiOrderLoop[idxl]がiValidSihatsuEkiの場合は、-1
					それ以外の場合は、
					(1)iValidSihatsuEkiとiEkiOrderLoop[idxl]が共に反転、もしくはともに無反転の場合は、-2(終点方)
						どちらかのみ反転の場合は-4(起点方へ発車)
				*/
				if (iEkiOrderBrunchTerminalSide[idxt] != iValidSihatsuEki)
				{
					if ((aEki.getBrunchOpposite() || aEki.getLoopOpposite()) ==
						aEkiTerminal.getBrunchOpposite())
					{
						iHatsuOperation = -2;
					}
					else
					{
						iHatsuOperation = -4;
					}
				}
				if (aEkiTerminal.getDiagramTrackDisplay())
				{
					/**
						iPrevRessyahoukouが2,-2の場合は反転駅設定は影響なし
						表示駅と前列車終着駅が同じ場合も、反転駅設定は影響なし
					*/
					int iPrevRessyahoukouThis = iPrevRessyahoukou;
					if ((iPrevRessyahoukouThis == 1 ||
						iPrevRessyahoukouThis == -1) &&
						iEkiOrderBrunchTerminalSide[idxt] != iEkiOrderOfPrevSyuuchakuEki)
					{
						CentDedDgrEkiCont::CdDedDgrEki aEkiSyuuchaku = pMuCdDedDgrEki->get(iEkiOrderOfPrevSyuuchakuEki);
						if (aEkiTerminal.getBrunchOpposite() !=
							(aEkiSyuuchaku.getBrunchOpposite() ||
								aEkiSyuuchaku.getLoopOpposite()))
						{
							iPrevRessyahoukouThis *= -1;
						}

					}
					CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
						iEkiOrderBrunchTerminalSide[idxt],
						iTsuukaTeisya,
						iChakuOperation,
						iHatsuOperation,
						true);
					aCentDedDgrRessyaTrackLine.setZaisen(contZaisen);
					aCentDedDgrRessyaTrackLine.setPrevRessyahoukou(iPrevRessyahoukouThis);
					if (iChakuOperation == 4)
					{
						aCentDedDgrRessyaTrackLine.setOuterEkiIndex(iOuterEkiIndex);
					}
					m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
				}
				/**
					在線表非表示の分岐駅では、始発駅自身でのみ、出区や路線外始発の表示を行います。
				*/
				else if (iEkiOrderBrunchTerminalSide[idxt] == iValidSihatsuEki &&
					iChakuOperationNoDisplay != 0)
				{
					/**
						前列車の終着駅の反転駅設定と、表示駅の反転駅設定を見て、
						片方のみtrueの場合は、前列車方向が変化します。
					*/
					int iPrevRessyahoukouNoDisplayThis = iPrevRessyahoukouNoDisplay;
					if (iPrevRessyahoukouNoDisplayThis != 0 &&
						iEkiOrderBrunchTerminalSide[idxt] != iEkiOrderOfPrevSyuuchakuEki)
					{
						CentDedDgrEkiCont::CdDedDgrEki aEkiSyuuchaku = pMuCdDedDgrEki->get(iEkiOrderOfPrevSyuuchakuEki);
						if (aEkiTerminal.getBrunchOpposite() !=
							(aEkiSyuuchaku.getBrunchOpposite() ||
								aEkiSyuuchaku.getLoopOpposite()))
						{
							iPrevRessyahoukouNoDisplayThis *= -1;
						}
					}
					CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
						iEkiOrderBrunchTerminalSide[idxt],
						iTsuukaTeisya,
						iChakuOperationNoDisplay,
						iHatsuOperation,
						false);
					aCentDedDgrRessyaTrackLine.setZaisen(contZaisenNoDisplay);
					aCentDedDgrRessyaTrackLine.setPrevRessyahoukou(iPrevRessyahoukouNoDisplayThis);
					if (iChakuOperation == 4)
					{
						aCentDedDgrRessyaTrackLine.setOuterEkiIndex(iOuterEkiIndex);
					}
					m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
				}
			}
		}

	}
	//========================================================================================================================================================================================================================================================
	//ここから中間駅
	/**
		途中駅においては、分岐等による、経由無しの存在を確認する必要があります。
		iEkiOrderとその次の駅の間を、列車が走行していない場合は、
		次にisRunBetweenNextEkiがtrueとなる駅(iHatsuEkiOrder)を探し、
		前作業・着時刻をiEkiOrderから、後作業・発時刻をiHatsuEkiOrderから取得します。
		ただし、iEkiOrderとiHatsuEkiOrderが、同一駅群ではない場合は、
		iEkiOrderの着時刻から1分分の線、iHatsuEkiOrderの発時刻への1分分の線のみを引きます(在線表表示駅の場合)

		この駅での生成後は、iEkiOrderをiHatsuEkiOrderまで進めます(次のループではiHatsuEkiOrder+1を実行する)
	*/
	int iEkiOrder = iValidSihatsuEki + 1;
	for (; iEkiOrder < iValidSyuuchakuEki; iEkiOrder++)
	{
		//前提条件 isRunBetweenNextEki(iEkiOrder-1) == true
		/**
			trueの場合は着発同一駅
		*/
		if (pCentDedRessya->isRunBetweenNextEki(iEkiOrder))
		{
			deque<Zaisen> contZaisen;
			deque<Zaisen> contZaisenNoDisplay;
			int iTsuukaTeisya = 0;

			const CentDedEkiJikoku* pEkiJikoku = pCentDedRessya->getCentDedEkiJikokuCont()
				->getMuPtr()->get(iEkiOrder);
			if (pEkiJikoku->getChakujikoku().isNull() &&
				pEkiJikoku->getHatsujikoku().isNull())
			{
				int iRessyaTrack = pEkiJikoku->getRessyaTrackIndex();
				const CentDedDgrEkiJikoku* pDgrEkiJikoku =
					this->getMuCentDedDgrEkiJikoku()->get(iEkiOrder);
				int iDgrXPos = pDgrEkiJikoku->getDgrXPosRessyasen();
				if (iDgrXPos == INT_MIN)
				{
					iDgrXPos = pDgrEkiJikoku->getDgrXPosChaku();
				}
				Zaisen aZaisen(iRessyaTrack,
					iDgrXPos,
					iDgrXPos);
				contZaisen.push_back(aZaisen);
				contZaisenNoDisplay.push_back(aZaisen);
			}
			else if (!pEkiJikoku->getChakujikoku().isNull() &&
				!pEkiJikoku->getHatsujikoku().isNull())
			{
				const CentDedBeforeOperationCont* pBeforeCont =
					pEkiJikoku->getCentDedBeforeOperationCont();
				const CentDedAfterOperationCont* pAfterCont =
					pEkiJikoku->getCentDedAfterOperationCont();
				int iRessyaTrack = pEkiJikoku->getRessyaTrackIndex();
				int iDgrXPosBase = getMuCentDedDgrEkiJikoku()->get(iEkiOrder)->getDgrXPosChaku();
				if (pEkiJikoku->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya)
				{
					iTsuukaTeisya = 2;
				}
				else
				{
					iTsuukaTeisya = 1;
				}
				/**
					この駅の発着番線および前作業に対するZaisenの、発時刻になります。
					まずは、発着番線に対する発時刻を後作業探索で求めます。
					有効な入換作業がある場合は、その入換発時刻(複数ある場合は最も手前の物)
					無い場合は、当駅発時刻になります。

					前作業探索で、最初に有効な入換が見つかった場合は、この値を基に、発着番線に対するZaisenを作成します、
					その後は、前作業探索において、一つ後ろの入換発時刻を保持する変数として使用します。

				*/
				int iDgrXPosHatsu = INT_MIN;
				/**
					後作業探索において、一つ前の入換着時刻を保持するための変数です。
				*/
				int iDgrXPosChaku = INT_MIN;
				for (int idxa = 0; idxa < (int)pAfterCont->size(); idxa++)
				{
					const CentDedAfterOperation* pAfterOperation = pAfterCont->getMuPtr()->get(idxa);
					if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
					{
						if (pAfterOperation->getShuntTrackIndex() != iRessyaTrack)
						{
							/**
								iDgrXPosChakuMainが初期値の場合は、
								この作業の入換着時刻が、発着番線の着時刻になります。
								それ以外の場合は、一つ先の入換番線の着時刻となります。
							*/
							if (iDgrXPosHatsu == INT_MIN)
							{
								iDgrXPosHatsu = pAfterOperation->getOperationHatsuJikoku().getTotalSeconds();
								iDgrXPosChaku = pAfterOperation->getOperationChakuJikoku(true).getTotalSeconds();
								iRessyaTrack = pAfterOperation->getShuntTrackIndex();
							}
							else
							{
								Zaisen aZaisen(iRessyaTrack,
									shiftDgrXPos(iDgrXPosChaku, iDgrXPosBase),
									shiftDgrXPos(pAfterOperation->getOperationHatsuJikoku().getTotalSeconds(), iDgrXPosBase));
								contZaisen.push_back(aZaisen);

								iDgrXPosChaku = pAfterOperation->getOperationChakuJikoku(true).getTotalSeconds();
								iRessyaTrack = pAfterOperation->getShuntTrackIndex();
							}
						}
					}
					else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
					{
						updateRessyaTrackLineBeforeCont(
							pAfterOperation->getCentDedBeforeOperationCont(),
							iEkiOrder,
							iRessyaTrack,
							shiftDgrXPos(pAfterOperation->getConnectJikoku().getTotalSeconds(), iDgrXPosBase),
							iTsuukaTeisya,
							true,
							pMuCdDedDgrEki,
							pCentDedEkiCont);
					}
					else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
					{
						updateRessyaTrackLineAfterCont(
							pAfterOperation->getCentDedAfterOperationCont(),
							iEkiOrder,
							iRessyaTrack,
							shiftDgrXPos(pAfterOperation->getReleaseJikoku().getTotalSeconds(), iDgrXPosBase),
							iTsuukaTeisya,
							true,
							pMuCdDedDgrEki,
							pCentDedEkiCont);
					}

				}
				if (iDgrXPosChaku != INT_MIN)
				{
					Zaisen aZaisen(iRessyaTrack,
						shiftDgrXPos(iDgrXPosChaku, iDgrXPosBase),
						shiftDgrXPos(pEkiJikoku->getHatsujikoku().getTotalSeconds(), iDgrXPosBase));
					contZaisen.push_back(aZaisen);
				}
				if (iDgrXPosHatsu == INT_MIN)
				{
					iDgrXPosHatsu = pEkiJikoku->getHatsujikoku().getTotalSeconds();
				}

				iRessyaTrack = pEkiJikoku->getRessyaTrackIndex();

				/**
					前作業探索において、一つ後ろの入換発時刻を保持するための変数です。
				*/
				for (int idxb = (int)pBeforeCont->size() - 1; idxb >= 0; idxb--)
				{
					const CentDedBeforeOperation* pBeforeOperation = pBeforeCont->getMuPtr()->get(idxb);
					if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
					{
						if (pBeforeOperation->getShuntTrackIndex() != iRessyaTrack)
						{
							Zaisen aZaisen(iRessyaTrack,
								shiftDgrXPos(pBeforeOperation->getOperationChakuJikoku(true).getTotalSeconds(), iDgrXPosBase),
								shiftDgrXPos(iDgrXPosHatsu, iDgrXPosBase));
							contZaisen.push_front(aZaisen);

							iDgrXPosHatsu = pBeforeOperation->getOperationHatsuJikoku().getTotalSeconds();
							iRessyaTrack = pBeforeOperation->getShuntTrackIndex();
						}
					}
					else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
					{
						updateRessyaTrackLineBeforeCont(
							pBeforeOperation->getCentDedBeforeOperationCont(),
							iEkiOrder,
							iRessyaTrack,
							shiftDgrXPos(pBeforeOperation->getConnectJikoku().getTotalSeconds(), iDgrXPosBase),
							iTsuukaTeisya,
							true,
							pMuCdDedDgrEki,
							pCentDedEkiCont);
					}
					else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
					{
						updateRessyaTrackLineAfterCont(
							pBeforeOperation->getCentDedAfterOperationCont(),
							iEkiOrder,
							iRessyaTrack,
							shiftDgrXPos(pBeforeOperation->getReleaseJikoku().getTotalSeconds(), iDgrXPosBase),
							iTsuukaTeisya,
							true,
							pMuCdDedDgrEki,
							pCentDedEkiCont);
					}
				}
				Zaisen aZaisen(iRessyaTrack,
					shiftDgrXPos(pEkiJikoku->getChakujikoku().getTotalSeconds(), iDgrXPosBase),
					shiftDgrXPos(iDgrXPosHatsu, iDgrXPosBase));
				contZaisen.push_front(aZaisen);

				Zaisen aZaisenNoDisplay(0,
					shiftDgrXPos(pEkiJikoku->getChakujikoku().getTotalSeconds(), iDgrXPosBase),
					shiftDgrXPos(pEkiJikoku->getHatsujikoku().getTotalSeconds(), iDgrXPosBase));
				contZaisenNoDisplay.push_front(aZaisen);

			}
			else
			{
				int iRessyaTrack = pEkiJikoku->getRessyaTrackIndex();
				const CentDedDgrEkiJikoku* pDgrEkiJikoku =
					this->getMuCentDedDgrEkiJikoku()->get(iEkiOrder);
				int iDgrXPos = pDgrEkiJikoku->getDgrXPosChaku(true);

				Zaisen aZaisen(iRessyaTrack,
					iDgrXPos,
					iDgrXPos);
				contZaisen.push_back(aZaisen);
				contZaisenNoDisplay.push_back(aZaisen);

			}

			/**
				Zaisenコンテナが完成したら、RessyaTrackLine形式に仕立てる。
				分岐・環状線で関係する駅全ての分を、ここで生成します。
				iPosition:-1
					単独駅、自駅分の生成のみを行う
				iPosition:INT_MIN
					起点側派生駅、この駅では在線表表示はありません
					自駅と基幹駅群で生成を行います。
				iPosition:0-
					基幹駅・起点駅・終点駅
					自駅を含む基幹駅群で生成を行います。
				iPosition:INT_MAX
					終点側派生駅、この駅では在線表表示はありません
					自駅と基幹駅群で生成を行います。
			*/
			deque<int> iEkiOrderBrunchOriginSide;
			deque<int> iEkiOrderLoop;
			deque<int> iEkiOrderBrunchTerminalSide;
			int iPosition = pCentDedEkiCont->getEkiOrderBrunchLoop(
				iEkiOrder,
				getRessyahoukou(),
				iEkiOrderBrunchOriginSide,
				iEkiOrderLoop,
				iEkiOrderBrunchTerminalSide);
			CentDedDgrEkiCont::CdDedDgrEki aEki = pMuCdDedDgrEki->get(iEkiOrder);
			if (iPosition == -1)
			{
				if (aEki.getDiagramTrackDisplay())
				{
					CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
						iEkiOrder,
						iTsuukaTeisya,
						-1,
						-1,
						true);
					aCentDedDgrRessyaTrackLine.setZaisen(contZaisen);
					m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
				}
				/**
					前後ともisRunBetweenNextEkiがtrueの場合、自身の駅が在線表非表示駅なら、
					描写するものはありません。
				*/
				//else
				//{
				//	CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
				//		iEkiOrder,
				//		pEkiJikoku->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya,
				//		-1,
				//		-1,
				//		false);
				//	aCentDedDgrRessyaTrackLine.setZaisen(contZaisenNoDisplay);
				//	m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
				//}
			}
			else//if (iPosition != -1)
			{
				/**
					分岐駅の場合
					※本来は想定外(分岐駅で途中駅なら、前後に経由無しがあるはずなので)
					一応在線表には普通に表示する
				*/
				for (int idxo = 0; idxo < (int)iEkiOrderBrunchOriginSide.size(); idxo++)
				{
					CentDedDgrEkiCont::CdDedDgrEki aEkiOrigin = pMuCdDedDgrEki->get(iEkiOrderBrunchOriginSide[idxo]);
					
					if (!aEkiOrigin.getDiagramTrackDisplay())
					{
						continue;
					}

					int iChakuOperation = -1;
					int iHatsuOperation = -1;
					/**
						iChakuOperationと
						iHatsuOperationを決定する。
						iEkiOrderLoop[idxl]がiValidSihatsuEkiの場合は、-1
						それ以外の場合は、
						(1)iValidSihatsuEkiとiEkiOrderLoop[idxl]が共に反転、もしくはともに無反転の場合は、-2(終点方)
							どちらかのみ反転の場合は-4(起点方へ発車)
					*/
					if (iEkiOrderBrunchOriginSide[idxo] != iEkiOrder)
					{
						if ((aEki.getBrunchOpposite() || aEki.getLoopOpposite()) ==
							aEkiOrigin.getBrunchOpposite())
						{
							iChakuOperation = -2;
							iHatsuOperation = -2;
						}
						else
						{
							iChakuOperation = -4;
							iHatsuOperation = -4;
						}
					}
					CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
						iEkiOrderBrunchOriginSide[idxo],
						iTsuukaTeisya,
						iChakuOperation,
						iHatsuOperation,
						true);
					aCentDedDgrRessyaTrackLine.setZaisen(contZaisen);
					m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
				}

				for (int idxl = 0; idxl < (int)iEkiOrderLoop.size(); idxl++)
				{
					CentDedDgrEkiCont::CdDedDgrEki aEkiLoop = pMuCdDedDgrEki->get(iEkiOrderLoop[idxl]);
					int iChakuOperation = -1;
					int iHatsuOperation = -1;
					/**
						iChakuOperationと
						iHatsuOperationを決定する。
						iEkiOrderLoop[idxl]がiValidSihatsuEkiの場合は、-1
						それ以外の場合は、
						(1)iValidSihatsuEkiとiEkiOrderLoop[idxl]が共に反転、もしくはともに無反転の場合は、-2(終点方)
							どちらかのみ反転の場合は-4(起点方へ発車)
					*/
					if (iEkiOrderLoop[idxl] != iEkiOrder)
					{
						if ((aEki.getBrunchOpposite() || aEki.getLoopOpposite()) ==
							aEkiLoop.getLoopOpposite())
						{
							iChakuOperation = -2;
							iHatsuOperation = -2;
						}
						else
						{
							iChakuOperation = -4;
							iHatsuOperation = -4;
						}
					}
					if (aEkiLoop.getDiagramTrackDisplay())
					{
						CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
							iEkiOrderLoop[idxl],
							iTsuukaTeisya,
							iChakuOperation,
							iHatsuOperation,
							true);
						aCentDedDgrRessyaTrackLine.setZaisen(contZaisen);
						m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
					}
					else if (iEkiOrderLoop[idxl] != iEkiOrder)
					{
						CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
							iEkiOrderLoop[idxl],
							iTsuukaTeisya,
							iChakuOperation,
							iHatsuOperation,
							false);
						aCentDedDgrRessyaTrackLine.setZaisen(contZaisenNoDisplay);
						m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
					}
				}

				for (int idxt = 0; idxt < (int)iEkiOrderBrunchTerminalSide.size(); idxt++)
				{
					CentDedDgrEkiCont::CdDedDgrEki aEkiTerminal = pMuCdDedDgrEki->get(iEkiOrderBrunchTerminalSide[idxt]);

					if (!aEkiTerminal.getDiagramTrackDisplay())
					{
						continue;
					}

					int iChakuOperation = -1;
					int iHatsuOperation = -1;
					/**
						iChakuOperationと
						iHatsuOperationを決定する。
						iEkiOrderLoop[idxl]がiValidSihatsuEkiの場合は、-1
						それ以外の場合は、
						(1)iValidSihatsuEkiとiEkiOrderLoop[idxl]が共に反転、もしくはともに無反転の場合は、-2(終点方)
							どちらかのみ反転の場合は-4(起点方へ発車)
					*/
					if (iEkiOrderBrunchTerminalSide[idxt] != iEkiOrder)
					{
						if ((aEki.getBrunchOpposite() || aEki.getLoopOpposite()) ==
							aEkiTerminal.getBrunchOpposite())
						{
							iChakuOperation = -2;
							iHatsuOperation = -2;
						}
						else
						{
							iChakuOperation = -4;
							iHatsuOperation = -4;
						}
					}
					CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
						iEkiOrderBrunchTerminalSide[idxt],
						iTsuukaTeisya,
						iChakuOperation,
						iHatsuOperation,
						true);
					aCentDedDgrRessyaTrackLine.setZaisen(contZaisen);
					m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
				}
			}
		}
		else//if(!pCentDedRessya->isRunBetweenNextEki(iEkiOrder))(経由なしの前後の場合)
		{
			int iHatsuEkiOrder = pCentDedRessya->getRunBetweenEkiForward(iEkiOrder);
			if (pCentDedEkiCont->isSameBrunchLoopGroup(iEkiOrder, iHatsuEkiOrder, getRessyahoukou()))
			{
				deque<Zaisen> contZaisen;
				deque<Zaisen> contZaisenNoDisplay;
				int iTsuukaTeisya = 0;
				const CentDedEkiJikoku* pEkiJikokuChaku = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iEkiOrder);
				const CentDedEkiJikoku* pEkiJikokuHatsu = pCentDedRessya->getCentDedEkiJikokuCont()
					->getMuPtr()->get(iHatsuEkiOrder);

				if (pEkiJikokuChaku->getChakujikoku().isNull() &&
					pEkiJikokuHatsu->getHatsujikoku().isNull())
				{
					int iRessyaTrack = pEkiJikokuChaku->getRessyaTrackIndex();
					const CentDedDgrEkiJikoku* pDgrEkiJikoku =
						this->getMuCentDedDgrEkiJikoku()->get(iEkiOrder);
					int iDgrXPos = pDgrEkiJikoku->getDgrXPosRessyasen();
					if (iDgrXPos == INT_MIN)
					{
						iDgrXPos = pDgrEkiJikoku->getDgrXPosChaku();
					}
					Zaisen aZaisen(iRessyaTrack,
						iDgrXPos,
						iDgrXPos);
					contZaisen.push_back(aZaisen);
					contZaisenNoDisplay.push_back(aZaisen);
				}
				else if (!pEkiJikokuChaku->getChakujikoku().isNull() &&
					!pEkiJikokuHatsu->getHatsujikoku().isNull())
				{
					const CentDedBeforeOperationCont* pBeforeCont =
						pEkiJikokuChaku->getCentDedBeforeOperationCont();
					const CentDedAfterOperationCont* pAfterCont =
						pEkiJikokuHatsu->getCentDedAfterOperationCont();
					int iRessyaTrack = pEkiJikokuChaku->getRessyaTrackIndex();
					int iDgrXPosBase = getMuCentDedDgrEkiJikoku()->get(iEkiOrder)->getDgrXPosChaku();
					if (pEkiJikokuChaku->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya)
					{
						iTsuukaTeisya = 2;
					}
					else
					{
						iTsuukaTeisya = 1;
					}
					//発着番線の着時刻です。前作業探索で確定します。
					/**
						この駅の発着番線および前作業に対するZaisenの、発時刻になります。
						まずは、発着番線に対する発時刻を後作業探索で求めます。
						有効な入換作業がある場合は、その入換発時刻(複数ある場合は最も手前の物)
						無い場合は、当駅発時刻になります。

						前作業探索で、最初に有効な入換が見つかった場合は、この値を基に、発着番線に対するZaisenを作成します、
						その後は、前作業探索において、一つ後ろの入換発時刻を保持する変数として使用します。

					*/
					int iDgrXPosHatsu = INT_MIN;
					/**
						後作業探索において、一つ前の入換着時刻を保持するための変数です。
					*/
					int iDgrXPosChaku = INT_MIN;
					for (int idxa = 0; idxa < (int)pAfterCont->size(); idxa++)
					{
						const CentDedAfterOperation* pAfterOperation = pAfterCont->getMuPtr()->get(idxa);
						if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
						{
							if (pAfterOperation->getShuntTrackIndex() != iRessyaTrack)
							{
								/**
									iDgrXPosChakuMainが初期値の場合は、
									この作業の入換着時刻が、発着番線の着時刻になります。
									それ以外の場合は、一つ先の入換番線の着時刻となります。
								*/
								if (iDgrXPosHatsu == INT_MIN)
								{
									iDgrXPosHatsu = pAfterOperation->getOperationHatsuJikoku().getTotalSeconds();
									iDgrXPosChaku = pAfterOperation->getOperationChakuJikoku(true).getTotalSeconds();
									iRessyaTrack = pAfterOperation->getShuntTrackIndex();
								}
								else
								{
									Zaisen aZaisen(iRessyaTrack,
										shiftDgrXPos(iDgrXPosChaku, iDgrXPosBase), 
										shiftDgrXPos(pAfterOperation->getOperationHatsuJikoku().getTotalSeconds(), iDgrXPosBase));
									contZaisen.push_back(aZaisen);

									iDgrXPosChaku = pAfterOperation->getOperationChakuJikoku(true).getTotalSeconds();
									iRessyaTrack = pAfterOperation->getShuntTrackIndex();
								}
							}
						}
						else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
						{
							updateRessyaTrackLineBeforeCont(
								pAfterOperation->getCentDedBeforeOperationCont(),
								iHatsuEkiOrder,
								iRessyaTrack,
								shiftDgrXPos(pAfterOperation->getConnectJikoku().getTotalSeconds(), iDgrXPosBase),
								iTsuukaTeisya,
								true,
								pMuCdDedDgrEki,
								pCentDedEkiCont);
						}
						else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
						{
							updateRessyaTrackLineAfterCont(
								pAfterOperation->getCentDedAfterOperationCont(),
								iHatsuEkiOrder,
								iRessyaTrack,
								shiftDgrXPos(pAfterOperation->getReleaseJikoku().getTotalSeconds(), iDgrXPosBase),
								iTsuukaTeisya,
								true,
								pMuCdDedDgrEki,
								pCentDedEkiCont);
						}

					}
					if (iDgrXPosChaku != INT_MIN)
					{
						Zaisen aZaisen(iRessyaTrack,
							shiftDgrXPos(iDgrXPosChaku, iDgrXPosBase),
							shiftDgrXPos(pEkiJikokuHatsu->getHatsujikoku().getTotalSeconds(), iDgrXPosBase));
						contZaisen.push_back(aZaisen);
					}
					if (iDgrXPosHatsu == INT_MIN)
					{
						iDgrXPosHatsu = pEkiJikokuHatsu->getHatsujikoku().getTotalSeconds();
					}

					iRessyaTrack = pEkiJikokuChaku->getRessyaTrackIndex();

					/**
						前作業探索において、一つ後ろの入換発時刻を保持するための変数です。
					*/
					for (int idxb = (int)pBeforeCont->size() - 1; idxb >= 0; idxb--)
					{
						const CentDedBeforeOperation* pBeforeOperation = pBeforeCont->getMuPtr()->get(idxb);
						if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
						{
							if (pBeforeOperation->getShuntTrackIndex() != iRessyaTrack)
							{
								Zaisen aZaisen(iRessyaTrack,
									shiftDgrXPos(pBeforeOperation->getOperationChakuJikoku(true).getTotalSeconds(), iDgrXPosBase),
									shiftDgrXPos(iDgrXPosHatsu, iDgrXPosBase));
								contZaisen.push_front(aZaisen);

								iDgrXPosHatsu = pBeforeOperation->getOperationHatsuJikoku().getTotalSeconds();
								iRessyaTrack = pBeforeOperation->getShuntTrackIndex();
							}
						}
						else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
						{
							updateRessyaTrackLineBeforeCont(
								pBeforeOperation->getCentDedBeforeOperationCont(),
								iEkiOrder,
								iRessyaTrack,
								shiftDgrXPos(pBeforeOperation->getConnectJikoku().getTotalSeconds(), iDgrXPosBase),
								iTsuukaTeisya,
								true,
								pMuCdDedDgrEki,
								pCentDedEkiCont);
						}
						else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
						{
							updateRessyaTrackLineAfterCont(
								pBeforeOperation->getCentDedAfterOperationCont(),
								iEkiOrder,
								iRessyaTrack,
								shiftDgrXPos(pBeforeOperation->getReleaseJikoku().getTotalSeconds(), iDgrXPosBase),
								iTsuukaTeisya,
								true,
								pMuCdDedDgrEki,
								pCentDedEkiCont);
						}
					}
					Zaisen aZaisen(iRessyaTrack,
						shiftDgrXPos(pEkiJikokuChaku->getChakujikoku().getTotalSeconds(), iDgrXPosBase),
						shiftDgrXPos(iDgrXPosHatsu, iDgrXPosBase));
					contZaisen.push_front(aZaisen);

					Zaisen aZaisenNoDisplay(0,
						shiftDgrXPos(pEkiJikokuChaku->getChakujikoku().getTotalSeconds(), iDgrXPosBase),
						shiftDgrXPos(pEkiJikokuHatsu->getHatsujikoku().getTotalSeconds(), iDgrXPosBase));
					contZaisenNoDisplay.push_front(aZaisen);

				}
				else
				{
					int iRessyaTrack = pEkiJikokuChaku->getRessyaTrackIndex();
					const CentDedDgrEkiJikoku* pDgrEkiJikokuChaku =
						this->getMuCentDedDgrEkiJikoku()->get(iEkiOrder);
					const CentDedDgrEkiJikoku* pDgrEkiJikokuHatsu =
						this->getMuCentDedDgrEkiJikoku()->get(iHatsuEkiOrder);
					int iDgrXPos;
					if (pDgrEkiJikokuChaku->getDgrXPosChaku() != INT_MIN)
					{
						iDgrXPos = pDgrEkiJikokuChaku->getDgrXPosChaku();
					}
					if (pDgrEkiJikokuHatsu->getDgrXPosHatsu() != INT_MIN)
					{
						iDgrXPos = pDgrEkiJikokuHatsu->getDgrXPosHatsu();
					}
					Zaisen aZaisen(iRessyaTrack,
						iDgrXPos,
						iDgrXPos);
					contZaisen.push_back(aZaisen);
					contZaisenNoDisplay.push_back(aZaisen);

				}

				/**
					Zaisenコンテナが完成したら、RessyaTrackLine形式に仕立てる。
					分岐・環状線で関係する駅全ての分を、ここで生成します。
					iPosition:-1
						単独駅、自駅分の生成のみを行う
					iPosition:INT_MIN
						起点側派生駅、この駅では在線表表示はありません
						自駅と基幹駅群で生成を行います。
					iPosition:0-
						基幹駅・起点駅・終点駅
						自駅を含む基幹駅群で生成を行います。
					iPosition:INT_MAX
						終点側派生駅、この駅では在線表表示はありません
						自駅と基幹駅群で生成を行います。
				*/
				deque<int> iEkiOrderBrunchOriginSide;
				deque<int> iEkiOrderLoop;
				deque<int> iEkiOrderBrunchTerminalSide;
				int iPositionChaku = pCentDedEkiCont->getEkiOrderBrunchLoop(
					iEkiOrder,
					getRessyahoukou(),
					iEkiOrderBrunchOriginSide,
					iEkiOrderLoop,
					iEkiOrderBrunchTerminalSide);
				int iPositionHatsu = pCentDedEkiCont->get(
					pCentDedEkiCont->EkiIndexOfEkiOrder(getRessyahoukou(), iHatsuEkiOrder)).getBrunchLoopPosition();
				CentDedDgrEkiCont::CdDedDgrEki aEkiChaku = pMuCdDedDgrEki->get(iEkiOrder);
				CentDedDgrEkiCont::CdDedDgrEki aEkiHatsu = pMuCdDedDgrEki->get(iHatsuEkiOrder);
				//if (iPositionChaku == INT_MIN || iPositionChaku == INT_MAX)
				//{
				//	//const CentDedEki* pEkiChaku = pCentDedEkiCont->getMuPtr()->get(
				//	//	pCentDedEkiCont->EkiIndexOfEkiOrder(getRessyahoukou(), iEkiOrder));
				//	int iHatsuOperation = -1;
				//	/**
				//		iChakuOperationと
				//		iHatsuOperationを決定する。
				//		iEkiOrderLoop[idxl]がiValidSihatsuEkiの場合は、-1
				//		それ以外の場合は、
				//		(1)iValidSihatsuEkiとiEkiOrderLoop[idxl]が共に反転、もしくはともに無反転の場合は、-2(終点方)
				//			どちらかのみ反転の場合は-4(起点方へ発車)
				//	*/
				//	if ((aEkiHatsu.getBrunchOpposite() || aEkiHatsu.getLoopOpposite()) ==
				//		aEkiChaku.getBrunchOpposite())
				//	{
				//		iHatsuOperation = -2;
				//	}
				//	else
				//	{
				//		iHatsuOperation = -4;
				//	}
				//	CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
				//		iEkiOrder,
				//		iTsuukaTeisya,
				//		-1,
				//		iHatsuOperation,
				//		false);
				//	aCentDedDgrRessyaTrackLine.setZaisen(contZaisenNoDisplay);
				//	m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
				//}
				//if (iPositionHatsu == INT_MIN || iPositionHatsu == INT_MAX)
				//{
				//	int iChakuOperation = -1;
				//	/**
				//		iChakuOperationと
				//		iHatsuOperationを決定する。
				//		iEkiOrderLoop[idxl]がiValidSihatsuEkiの場合は、-1
				//		それ以外の場合は、
				//		(1)iValidSihatsuEkiとiEkiOrderLoop[idxl]が共に反転、もしくはともに無反転の場合は、-2か-3(終点方)
				//			どちらかのみ反転の場合は-4か-5(起点方へ発車)
				//		(2)-2か-3の選択は、iEkiOrderLoop[idxl]の駅時刻形式をみて、着時刻駅の場合は-3
				//			(着時刻駅の場合、列車の終点方向への補助列車線は描写しない)
				//		(3)-4か-5の選択は、iEkiOrderLoop[idxl]の駅時刻形式をみて、発時刻駅の場合は-5
				//			(発時刻駅の場合、列車の起点方向への補助列車線は描写しない)
				//	*/
				//	if ((aEkiChaku.getBrunchOpposite() || aEkiChaku.getLoopOpposite()) ==
				//		aEkiHatsu.getBrunchOpposite())
				//	{
				//		iChakuOperation = -2;
				//	}
				//	else
				//	{
				//		iChakuOperation = -4;
				//	}
				//	CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
				//		iHatsuEkiOrder,
				//		iTsuukaTeisya,
				//		iChakuOperation,
				//		-1,
				//		false);
				//	aCentDedDgrRessyaTrackLine.setZaisen(contZaisenNoDisplay);
				//	m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
				//}

				for (int idxo = 0; idxo < (int)iEkiOrderBrunchOriginSide.size(); idxo++)
				{
					CentDedDgrEkiCont::CdDedDgrEki aEkiOrigin = pMuCdDedDgrEki->get(iEkiOrderBrunchOriginSide[idxo]);
					int iChakuOperation = -1;
					int iHatsuOperation = -1;
					/**
						iChakuOperationと
						iHatsuOperationを決定する。
						iEkiOrderLoop[idxl]がiValidSihatsuEkiの場合は、-1
						それ以外の場合は、
						(1)iValidSihatsuEkiとiEkiOrderLoop[idxl]が共に反転、もしくはともに無反転の場合は、-2(終点方)
							どちらかのみ反転の場合は-4(起点方へ発車)
					*/
					if (iEkiOrderBrunchOriginSide[idxo] != iEkiOrder)
					{
						//着側
						//表示駅aEkiOriginの反転設定と時刻元駅aEkiChakuの反転設定が同じ場合は、iChakuOperationを-2に、
						//異なる場合は-4にします。
						if ((aEkiChaku.getBrunchOpposite() || aEkiChaku.getLoopOpposite()) ==
							aEkiOrigin.getBrunchOpposite())
						{
							iChakuOperation = -2;
						}
						else
						{
							iChakuOperation = -4;
						}
					}
					if (iEkiOrderBrunchOriginSide[idxo] != iHatsuEkiOrder)
					{
						//発側
						//表示駅aEkiOriginの反転設定と時刻元駅aEkiHatsuの反転設定が同じ場合は、iHatsuOperationを-2に、
						//異なる場合は-4にします。
						if ((aEkiHatsu.getBrunchOpposite() || aEkiHatsu.getLoopOpposite()) ==
							aEkiOrigin.getBrunchOpposite())
						{
							iHatsuOperation = -2;
						}
						else
						{
							iHatsuOperation = -4;
						}
					}
					if (aEkiOrigin.getDiagramTrackDisplay())
					{
						CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
							iEkiOrderBrunchOriginSide[idxo],
							iTsuukaTeisya,
							iChakuOperation,
							iHatsuOperation,
							true);
						aCentDedDgrRessyaTrackLine.setZaisen(contZaisen);
						m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
					}
					/**
						在線表非表示の分岐駅(起点側)では、iEkiOrderBrunchOriginSide[idxo]が着側駅(iEkiOrder)の場合のみ、補助列車線を表示します
					*/
					else if(iEkiOrderBrunchOriginSide[idxo] == iEkiOrder)
					{
						CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
							iEkiOrderBrunchOriginSide[idxo],
							iTsuukaTeisya,
							iChakuOperation,
							iHatsuOperation,
							false);
						aCentDedDgrRessyaTrackLine.setZaisen(contZaisenNoDisplay);
						m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
					}
				}

				for (int idxl = 0; idxl < (int)iEkiOrderLoop.size(); idxl++)
				{
					CentDedDgrEkiCont::CdDedDgrEki aEkiLoop = pMuCdDedDgrEki->get(iEkiOrderLoop[idxl]);
					const CentDedEki* pEkiLoop = pCentDedEkiCont->getMuPtr()->get(
						pCentDedEkiCont->EkiIndexOfEkiOrder(getRessyahoukou(), iEkiOrderLoop[idxl]));
					int iChakuOperation = -1;
					int iHatsuOperation = -1;
					/**
						iChakuOperationと
						iHatsuOperationを決定する。
						iEkiOrderLoop[idxl]がiValidSihatsuEkiの場合は、-1
						それ以外の場合は、
						(1)iValidSihatsuEkiとiEkiOrderLoop[idxl]が共に反転、もしくはとも
					*/
					if (iEkiOrderLoop[idxl] != iEkiOrder)
					{
						//着側
						//表示駅aEkiLoopの反転設定と時刻元駅aEkiChakuの反転設定が同じ場合は、iChakuOperationを-2に、
						//異なる場合は-4にします。
						if ((aEkiChaku.getBrunchOpposite() || aEkiChaku.getLoopOpposite()) ==
							aEkiLoop.getLoopOpposite())
						{
							iChakuOperation = -2;
						}
						else
						{
							iChakuOperation = -4;
						}
					}
					if (iEkiOrderLoop[idxl] != iHatsuEkiOrder)
					{
						//発側
						//表示駅aEkiLoopの反転設定と時刻元駅aEkiHatsuの反転設定が同じ場合は、iHatsuOperationを-2に、
						//異なる場合は-4にします。
						if ((aEkiHatsu.getBrunchOpposite() || aEkiHatsu.getLoopOpposite()) ==
							aEkiLoop.getLoopOpposite())
						{
							iHatsuOperation = -2;
						}
						else
						{
							iHatsuOperation = -4;
						}
					}
					if (aEkiLoop.getDiagramTrackDisplay())
					{
						CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
							iEkiOrderLoop[idxl],
							iTsuukaTeisya,
							iChakuOperation,
							iHatsuOperation,
							true);
						aCentDedDgrRessyaTrackLine.setZaisen(contZaisen);
						m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
					}
					else
					{
						CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
							iEkiOrderLoop[idxl],
							iTsuukaTeisya,
							iChakuOperation,
							iHatsuOperation,
							false);
						aCentDedDgrRessyaTrackLine.setZaisen(contZaisenNoDisplay);
						m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
					}
				}

				for (int idxt = 0; idxt < (int)iEkiOrderBrunchTerminalSide.size(); idxt++)
				{
					CentDedDgrEkiCont::CdDedDgrEki aEkiTerminal = pMuCdDedDgrEki->get(iEkiOrderBrunchTerminalSide[idxt]);
					int iChakuOperation = -1;
					int iHatsuOperation = -1;
					/**
						iChakuOperationと
						iHatsuOperationを決定する。
						iEkiOrderLoop[idxl]がiValidSihatsuEkiの場合は、-1
						それ以外の場合は、
						(1)iValidSihatsuEkiとiEkiOrderLoop[idxl]が共に反転、もしくはともに無反転の場合は、-2(終点方)
							どちらかのみ反転の場合は-4(起点方へ発車)
					*/
					if (iEkiOrderBrunchTerminalSide[idxt] != iEkiOrder)
					{
						//着側
						//表示駅aEkiTerminalの反転設定と時刻元駅aEkiChakuの反転設定が同じ場合は、iChakuOperationを-2に、
						//異なる場合は-4にします。
						if ((aEkiChaku.getBrunchOpposite() || aEkiChaku.getLoopOpposite()) ==
							aEkiTerminal.getBrunchOpposite())
						{
							iChakuOperation = -2;
						}
						else
						{
							iChakuOperation = -4;
						}
					}
					if (iEkiOrderBrunchTerminalSide[idxt] != iHatsuEkiOrder)
					{
						//発側
						//表示駅aEkiTerminalの反転設定と時刻元駅aEkiHatsuの反転設定が同じ場合は、iHatsuOperationを-2に、
						//異なる場合は-4にします。
						if ((aEkiHatsu.getBrunchOpposite() || aEkiHatsu.getLoopOpposite()) ==
							aEkiTerminal.getBrunchOpposite())
						{
							iHatsuOperation = -2;
						}
						else
						{
							iHatsuOperation = -4;
						}
					}
					if (aEkiTerminal.getDiagramTrackDisplay())
					{
						CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
							iEkiOrderBrunchTerminalSide[idxt],
							iTsuukaTeisya,
							iChakuOperation,
							iHatsuOperation,
							true);
						aCentDedDgrRessyaTrackLine.setZaisen(contZaisen);
						m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
					}
					/**
						在線表非表示の分岐駅(終点側)では、iEkiOrderBrunchTerminalSide[idxt]が発側駅(iHatsuEkiOrder)の場合のみ、補助列車線を表示します
					*/
					else if (iEkiOrderBrunchTerminalSide[idxt] == iHatsuEkiOrder)
					{
						CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
							iEkiOrderBrunchTerminalSide[idxt],
							iTsuukaTeisya,
							iChakuOperation,
							iHatsuOperation,
							false);
						aCentDedDgrRessyaTrackLine.setZaisen(contZaisenNoDisplay);
						m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
					}
				}
			}
			/**
				経由無し・運行無しの連続の前後の駅が、分岐駅グループではない場合は、
				それぞれに1分分の在線線を描写する。
			*/
			else
			{
				//着側
				{
					deque<Zaisen> contZaisenChaku;
					int iDgrXPosChaku;
					const CentDedEkiJikoku* pEkiJikokuChaku = pCentDedRessya->getCentDedEkiJikokuCont()
						->getMuPtr()->get(iEkiOrder);
					int iTsuukaTeisya = 2;
					if (pEkiJikokuChaku->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka)
					{
						iTsuukaTeisya = 1;
					}
					if (pEkiJikokuChaku->getChakujikoku().isNull())
					{
						const CentDedDgrEkiJikoku* pDgrEkiJikoku =
							this->getMuCentDedDgrEkiJikoku()->get(iEkiOrder);
						iDgrXPosChaku = pDgrEkiJikoku->getDgrXPosRessyasen();
					}
					else
					{
						iDgrXPosChaku = pEkiJikokuChaku->getChakujikoku().getTotalSeconds();
					}
					Zaisen aZaisenChaku(pEkiJikokuChaku->getRessyaTrackIndex(),
						iDgrXPosChaku,
						iDgrXPosChaku + 60);
					contZaisenChaku.push_back(aZaisenChaku);

					deque<int> iEkiOrderBrunchOriginSide;
					deque<int> iEkiOrderLoop;
					deque<int> iEkiOrderBrunchTerminalSide;
					int iPositionChaku = pCentDedEkiCont->getEkiOrderBrunchLoop(
						iEkiOrder,
						getRessyahoukou(),
						iEkiOrderBrunchOriginSide,
						iEkiOrderLoop,
						iEkiOrderBrunchTerminalSide);
					CentDedDgrEkiCont::CdDedDgrEki aEkiChaku = pMuCdDedDgrEki->get(iEkiOrder);
					if (iPositionChaku == -1)
					{
						if (aEkiChaku.getDiagramTrackDisplay())
						{
							CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLineChaku(
								iEkiOrder,
								iTsuukaTeisya,
								-1,
								0,
								true);
							aCentDedDgrRessyaTrackLineChaku.setZaisen(contZaisenChaku);
							m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLineChaku);
						}
					}
					else //if (iPositionChaku != -1)
					{
						for (int idxo = 0; idxo < (int)iEkiOrderBrunchOriginSide.size(); idxo++)
						{
							CentDedDgrEkiCont::CdDedDgrEki aEkiOrigin = pMuCdDedDgrEki->get(iEkiOrderBrunchOriginSide[idxo]);

							//在線表非表示の場合、表示するものは無し
							if (!aEkiOrigin.getDiagramTrackDisplay())
							{
								continue;
							}

							int iChakuOperation = -1;
							/**
								iChakuOperationと
								iHatsuOperationを決定する。
								iEkiOrderLoop[idxl]がiValidSihatsuEkiの場合は、-1
								それ以外の場合は、
								(1)iValidSihatsuEkiとiEkiOrderLoop[idxl]が共に反転、もしくはともに無反転の場合は、-2(終点方)
									どちらかのみ反転の場合は-4(起点方へ発車)
							*/
							if (iEkiOrderBrunchOriginSide[idxo] != iEkiOrder)
							{
								if ((aEkiChaku.getBrunchOpposite() || aEkiChaku.getLoopOpposite()) ==
									aEkiOrigin.getBrunchOpposite())
								{
									iChakuOperation = -2;
								}
								else
								{
									iChakuOperation = -4;
								}
							}

							CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLineChaku(
								iEkiOrderBrunchOriginSide[idxo],
								iTsuukaTeisya,
								iChakuOperation,
								0,
								true);
							aCentDedDgrRessyaTrackLineChaku.setZaisen(contZaisenChaku);
							m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLineChaku);
						}

						for (int idxl = 0; idxl < (int)iEkiOrderLoop.size(); idxl++)
						{
							CentDedDgrEkiCont::CdDedDgrEki aEkiLoop = pMuCdDedDgrEki->get(iEkiOrderLoop[idxl]);
							int iChakuOperation = -1;
							/**
								iChakuOperationと
								iHatsuOperationを決定する。
								iEkiOrderLoop[idxl]がiValidSihatsuEkiの場合は、-1
								それ以外の場合は、
								(1)iValidSihatsuEkiとiEkiOrderLoop[idxl]が共に反転、もしくはともに無反転の場合は、-2(終点方)
									どちらかのみ反転の場合は-4(起点方へ発車)
							*/
							if (iEkiOrderLoop[idxl] != iEkiOrder)
							{
								if ((aEkiChaku.getBrunchOpposite() || aEkiChaku.getLoopOpposite()) ==
									aEkiLoop.getLoopOpposite())
								{
									iChakuOperation = -2;
								}
								else
								{
									iChakuOperation = -4;
								}
							}
							if (aEkiLoop.getDiagramTrackDisplay())
							{
								CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLineChaku(
									iEkiOrderLoop[idxl],
									iTsuukaTeisya,
									iChakuOperation,
									0,
									true);
								aCentDedDgrRessyaTrackLineChaku.setZaisen(contZaisenChaku);
								m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLineChaku);
							}
							else if(iEkiOrderLoop[idxl] != iEkiOrder)
							{
								CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLineChaku(
									iEkiOrderLoop[idxl],
									iTsuukaTeisya,
									iChakuOperation,
									0,
									false);
								aCentDedDgrRessyaTrackLineChaku.setZaisen(contZaisenChaku);
								m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLineChaku);
							}
						}

						for (int idxt = 0; idxt < (int)iEkiOrderBrunchTerminalSide.size(); idxt++)
						{
							CentDedDgrEkiCont::CdDedDgrEki aEkiTerminal = pMuCdDedDgrEki->get(iEkiOrderBrunchTerminalSide[idxt]);
							//在線表非表示の場合、表示するものは無し
							if (!aEkiTerminal.getDiagramTrackDisplay())
							{
								continue;
							}

							int iChakuOperation = -1;
							/**
								iChakuOperationと
								iHatsuOperationを決定する。
								iEkiOrderLoop[idxl]がiValidSihatsuEkiの場合は、-1
								それ以外の場合は、
								(1)iValidSihatsuEkiとiEkiOrderLoop[idxl]が共に反転、もしくはともに無反転の場合は、-2(終点方)
									どちらかのみ反転の場合は-4(起点方へ発車)
							*/
							if (iEkiOrderBrunchTerminalSide[idxt] != iEkiOrder)
							{
								if ((aEkiChaku.getBrunchOpposite() || aEkiChaku.getLoopOpposite()) ==
									aEkiTerminal.getBrunchOpposite())
								{
									iChakuOperation = -2;
								}
								else
								{
									iChakuOperation = -4;
								}
							}

							CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLineChaku(
								iEkiOrderBrunchTerminalSide[idxt],
								iTsuukaTeisya,
								iChakuOperation,
								0,
								true);
							aCentDedDgrRessyaTrackLineChaku.setZaisen(contZaisenChaku);
							m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLineChaku);
						}
					}
				}
				//発側
				{
					deque<Zaisen> contZaisenHatsu;
					int iDgrXPosHatsu;
					const CentDedEkiJikoku* pEkiJikokuHatsu = pCentDedRessya->getCentDedEkiJikokuCont()
						->getMuPtr()->get(iHatsuEkiOrder);
					int iTsuukaTeisya = 2;
					if (pEkiJikokuHatsu->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka)
					{
						iTsuukaTeisya = 1;
					}
					if (pEkiJikokuHatsu->getHatsujikoku().isNull())
					{
						const CentDedDgrEkiJikoku* pDgrEkiJikoku =
							this->getMuCentDedDgrEkiJikoku()->get(iHatsuEkiOrder);
						iDgrXPosHatsu = pDgrEkiJikoku->getDgrXPosRessyasen();
					}
					else
					{
						iDgrXPosHatsu = pEkiJikokuHatsu->getHatsujikoku().getTotalSeconds();
					}
					Zaisen aZaisenHatsu(pEkiJikokuHatsu->getRessyaTrackIndex(),
						iDgrXPosHatsu - 60,
						iDgrXPosHatsu);
					contZaisenHatsu.push_back(aZaisenHatsu);

					deque<int> iEkiOrderBrunchOriginSide;
					deque<int> iEkiOrderLoop;
					deque<int> iEkiOrderBrunchTerminalSide;
					int iPositionHatsu = pCentDedEkiCont->getEkiOrderBrunchLoop(
						iHatsuEkiOrder,
						getRessyahoukou(),
						iEkiOrderBrunchOriginSide,
						iEkiOrderLoop,
						iEkiOrderBrunchTerminalSide);
					CentDedDgrEkiCont::CdDedDgrEki aEkiHatsu = pMuCdDedDgrEki->get(iHatsuEkiOrder);
					if (iPositionHatsu == -1)
					{
						if (aEkiHatsu.getDiagramTrackDisplay())
						{
							CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLineHatsu(
								iHatsuEkiOrder,
								iTsuukaTeisya,
								0,
								-1,
								true);
							aCentDedDgrRessyaTrackLineHatsu.setZaisen(contZaisenHatsu);
							m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLineHatsu);
						}
					}
					else//if (iPositionHatsu != -1)
					{
						for (int idxo = 0; idxo < (int)iEkiOrderBrunchOriginSide.size(); idxo++)
						{
							CentDedDgrEkiCont::CdDedDgrEki aEkiOrigin = pMuCdDedDgrEki->get(iEkiOrderBrunchOriginSide[idxo]);

							//在線表非表示の場合、表示するものは無し
							if (!aEkiOrigin.getDiagramTrackDisplay())
							{
								continue;
							}

							int iHatsuOperation = -1;
							/**
								iChakuOperationと
								iHatsuOperationを決定する。
								iEkiOrderLoop[idxl]がiValidSihatsuEkiの場合は、-1
								それ以外の場合は、
								(1)iValidSihatsuEkiとiEkiOrderLoop[idxl]が共に反転、もしくはともに無反転の場合は、-2(終点方)
									どちらかのみ反転の場合は-4(起点方へ発車)
							*/
							if (iEkiOrderBrunchOriginSide[idxo] != iHatsuEkiOrder)
							{
								if ((aEkiHatsu.getBrunchOpposite() || aEkiHatsu.getLoopOpposite()) ==
									aEkiOrigin.getBrunchOpposite())
								{
									iHatsuOperation = -2;
								}
								else
								{
									iHatsuOperation = -4;
								}
							}

							CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLineHatsu(
								iEkiOrderBrunchOriginSide[idxo],
								iTsuukaTeisya,
								0,
								iHatsuOperation,
								true);
							aCentDedDgrRessyaTrackLineHatsu.setZaisen(contZaisenHatsu);
							m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLineHatsu);
						}

						for (int idxl = 0; idxl < (int)iEkiOrderLoop.size(); idxl++)
						{
							CentDedDgrEkiCont::CdDedDgrEki aEkiLoop = pMuCdDedDgrEki->get(iEkiOrderLoop[idxl]);
							int iHatsuOperation = -1;
							/**
								iChakuOperationと
								iHatsuOperationを決定する。
								iEkiOrderLoop[idxl]がiValidSihatsuEkiの場合は、-1
								それ以外の場合は、
								(1)iValidSihatsuEkiとiEkiOrderLoop[idxl]が共に反転、もしくはともに無反転の場合は、-2(終点方)
									どちらかのみ反転の場合は-4(起点方へ発車)
							*/
							if (iEkiOrderLoop[idxl] != iHatsuEkiOrder)
							{
								if ((aEkiHatsu.getBrunchOpposite() || aEkiHatsu.getLoopOpposite()) ==
									aEkiLoop.getLoopOpposite())
								{
									iHatsuOperation = -2;
								}
								else
								{
									iHatsuOperation = -4;
								}
							}
							if (aEkiHatsu.getDiagramTrackDisplay())
							{
								CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLineHatsu(
									iEkiOrderLoop[idxl],
									iTsuukaTeisya,
									0,
									iHatsuOperation,
									true);
								aCentDedDgrRessyaTrackLineHatsu.setZaisen(contZaisenHatsu);
								m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLineHatsu);
							}
							else if (iEkiOrderLoop[idxl] != iHatsuEkiOrder)
							{
								CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLineHatsu(
									iEkiOrderLoop[idxl],
									iTsuukaTeisya,
									0,
									iHatsuOperation,
									false);
								aCentDedDgrRessyaTrackLineHatsu.setZaisen(contZaisenHatsu);
								m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLineHatsu);
							}
						}

						for (int idxt = 0; idxt < (int)iEkiOrderBrunchTerminalSide.size(); idxt++)
						{
							CentDedDgrEkiCont::CdDedDgrEki aEkiTerminal = pMuCdDedDgrEki->get(iEkiOrderBrunchTerminalSide[idxt]);

							//在線表非表示の場合、表示するものは無し
							if (!aEkiTerminal.getDiagramTrackDisplay())
							{
								continue;
							}

							int iHatsuOperation = -1;
							/**
								iChakuOperationと
								iHatsuOperationを決定する。
								iEkiOrderLoop[idxl]がiValidSihatsuEkiの場合は、-1
								それ以外の場合は、
								(1)iValidSihatsuEkiとiEkiOrderLoop[idxl]が共に反転、もしくはともに無反転の場合は、-2(終点方)
									どちらかのみ反転の場合は-4(起点方へ発車)
							*/
							if (iEkiOrderBrunchTerminalSide[idxt] != iHatsuEkiOrder)
							{
								if ((aEkiHatsu.getBrunchOpposite() || aEkiHatsu.getLoopOpposite()) ==
									aEkiTerminal.getBrunchOpposite())
								{
									iHatsuOperation = -2;
								}
								else
								{
									iHatsuOperation = -4;
								}
							}

							CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLineHatsu(
								iEkiOrderBrunchTerminalSide[idxt],
								iTsuukaTeisya,
								0,
								iHatsuOperation,
								true);
							aCentDedDgrRessyaTrackLineHatsu.setZaisen(contZaisenHatsu);
							m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLineHatsu);
						}
					}
				}
			}
			iEkiOrder = iHatsuEkiOrder;
		}
	}
	//========================================================================================================================================================================================================================================================
	//ここから終着駅
	{
		deque<Zaisen> contZaisen;
		deque<Zaisen> contZaisenNoDisplay;
		const CentDedEkiJikoku* pEkiJikoku = pCentDedRessya->getCentDedEkiJikokuCont()
			->getMuPtr()->get(iValidSyuuchakuEki);
		const CentDedBeforeOperationCont* pBeforeCont =
			pEkiJikoku->getCentDedBeforeOperationCont();
		const CentDedAfterOperationCont* pAfterCont =
			pEkiJikoku->getCentDedAfterOperationCont();
		int iRessyaTrack = pEkiJikoku->getRessyaTrackIndex();
		int iDgrXPosBase = getMuCentDedDgrEkiJikoku()->get(iEkiOrder)->getDgrXPosChaku();
		int iTsuukaTeisya = 2;
		if (pEkiJikoku->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka)
		{
			iTsuukaTeisya = 1;
		}

		/**
			この駅の発着番線および後作業に対するZaisenの、着時刻になります。
			まずは、発着番線に対する着時刻を前作業探索で求めます。
			有効な入換作業がある場合は、その入換着時刻(複数ある場合は最も後ろの物)
			無い場合は、当駅着時刻になります。

			後作業探索で、最初に有効な入換が見つかった場合は、この値を基に、発着番線に対するZaisenを作成します、
			その後は、後作業探索において、一つ前の入換着時刻を保持する変数として使用します。

		*/
		int iDgrXPosChaku = INT_MIN;
		/**
			前作業探索において、一つ後の入換発時刻を保持するための変数です。
		*/
		int iDgrXPosHatsu = INT_MIN;
		/**
			この列車の終点時刻です。
			この列車の終端作業が、入区・路線外終着の場合は、それらの作業から終点時刻をとりますが、
			次列車接続で終点時刻未設定の場合は、
			他作業及び当駅着時刻から、終点時刻を導く必要があります。
		*/
		int iDgrXPosTerminal = INT_MIN;

		/**
			bTsuukaOuterJikokuNull
			終着駅の駅扱いが通過で、路線外終着かつ当駅発時刻がNULLの場合は、
			路線外終着作業以外は無効になります。
			したがって、下記の前作業・後作業検索はスキップします。
		*/
		bool bTsuukaOuterJikokuNull =
			pEkiJikoku->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka &&
			pAfterCont->getMuPtr()->get(INT_MAX)->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer &&
			pAfterCont->getMuPtr()->get(INT_MAX)->getHatsuJikoku().isNull();
		if (bTsuukaOuterJikokuNull)
		{
			iTsuukaTeisya = 0;
		}

		for (int idxb = (int)pBeforeCont->size() - 1; idxb >= 0 && !bTsuukaOuterJikokuNull; idxb--)
		{
			const CentDedBeforeOperation* pBeforeOperation = pBeforeCont->getMuPtr()->get(idxb);
			if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
			{
				if (pBeforeOperation->getShuntTrackIndex() != iRessyaTrack)
				{
					/**
						iDgrXPosChakuが初期値の場合は、
						この作業の入換着時刻が、発着番線の着時刻になります。
						それ以外の場合は、一つ先の入換番線の着時刻となります。
					*/
					if (iDgrXPosChaku == INT_MIN)
					{
						iDgrXPosChaku = pBeforeOperation->getOperationChakuJikoku(true).getTotalSeconds();
						iDgrXPosHatsu = pBeforeOperation->getOperationHatsuJikoku().getTotalSeconds();
						iRessyaTrack = pBeforeOperation->getShuntTrackIndex();
					}
					else
					{
						Zaisen aZaisen(iRessyaTrack,
							shiftDgrXPos(pBeforeOperation->getOperationChakuJikoku(true).getTotalSeconds(), iDgrXPosBase),
							shiftDgrXPos(iDgrXPosHatsu, iDgrXPosBase));
						contZaisen.push_front(aZaisen);

						iDgrXPosHatsu = pBeforeOperation->getOperationHatsuJikoku().getTotalSeconds();
						iRessyaTrack = pBeforeOperation->getShuntTrackIndex();
					}
					if (iDgrXPosTerminal == INT_MIN)
					{
						iDgrXPosTerminal = pBeforeOperation->getOperationChakuJikoku(true).getTotalSeconds();
					}
				}
			}
			else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
			{
				updateRessyaTrackLineBeforeCont(
					pBeforeOperation->getCentDedBeforeOperationCont(),
					iValidSyuuchakuEki,
					iRessyaTrack,
					shiftDgrXPos(pBeforeOperation->getConnectJikoku().getTotalSeconds(), iDgrXPosBase),
					iTsuukaTeisya,
					true,
					pMuCdDedDgrEki,
					pCentDedEkiCont);
				if (iDgrXPosTerminal == INT_MIN)
				{
					iDgrXPosTerminal = pBeforeOperation->getConnectJikoku().getTotalSeconds();
				}
			}
			else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
			{
				updateRessyaTrackLineAfterCont(
					pBeforeOperation->getCentDedAfterOperationCont(),
					iValidSyuuchakuEki,
					iRessyaTrack,
					shiftDgrXPos(pBeforeOperation->getReleaseJikoku().getTotalSeconds(), iDgrXPosBase),
					iTsuukaTeisya,
					true,
					pMuCdDedDgrEki,
					pCentDedEkiCont);
				if (iDgrXPosTerminal == INT_MIN)
				{
					iDgrXPosTerminal = pBeforeOperation->getReleaseJikoku().getTotalSeconds();
				}
			}

		}
		if (iDgrXPosHatsu != INT_MIN)
		{
			Zaisen aZaisen(iRessyaTrack,
				shiftDgrXPos(pEkiJikoku->getChakujikoku().getTotalSeconds(), iDgrXPosBase),
				shiftDgrXPos(iDgrXPosHatsu, iDgrXPosBase));
			contZaisen.push_front(aZaisen);
		}
		if (iDgrXPosChaku == INT_MIN)
		{
			iDgrXPosChaku = pEkiJikoku->getChakujikoku().getTotalSeconds();
		}
		if (iDgrXPosTerminal == INT_MIN)
		{
			iDgrXPosTerminal = pEkiJikoku->getChakujikoku().getTotalSeconds();
		}

		iRessyaTrack = pEkiJikoku->getRessyaTrackIndex();

		for (int idxa = 0; idxa < (int)pAfterCont->size()-1 && !bTsuukaOuterJikokuNull; idxa++)
		{
			const CentDedAfterOperation* pAfterOperation = pAfterCont->getMuPtr()->get(idxa);
			if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
			{
				if (pAfterOperation->getShuntTrackIndex() != iRessyaTrack)
				{
					Zaisen aZaisen(iRessyaTrack,
						shiftDgrXPos(iDgrXPosChaku, iDgrXPosBase),
						shiftDgrXPos(pAfterOperation->getOperationHatsuJikoku().getTotalSeconds(), iDgrXPosBase));
					contZaisen.push_back(aZaisen);

					iDgrXPosChaku = pAfterOperation->getOperationChakuJikoku(true).getTotalSeconds();
					iRessyaTrack = pAfterOperation->getShuntTrackIndex();
					iDgrXPosTerminal = pAfterOperation->getOperationChakuJikoku(true).getTotalSeconds();
				}
			}
			else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
			{
				updateRessyaTrackLineBeforeCont(
					pAfterOperation->getCentDedBeforeOperationCont(),
					iValidSyuuchakuEki,
					iRessyaTrack,
					shiftDgrXPos(pAfterOperation->getConnectJikoku().getTotalSeconds(), iDgrXPosBase),
					iTsuukaTeisya,
					true,
					pMuCdDedDgrEki,
					pCentDedEkiCont);
				iDgrXPosTerminal = pAfterOperation->getConnectJikoku().getTotalSeconds();
			}
			else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
			{
				updateRessyaTrackLineAfterCont(
					pAfterOperation->getCentDedAfterOperationCont(),
					iValidSyuuchakuEki,
					iRessyaTrack,
					shiftDgrXPos(pAfterOperation->getReleaseJikoku().getTotalSeconds(), iDgrXPosBase),
					iTsuukaTeisya,
					true,
					pMuCdDedDgrEki,
					pCentDedEkiCont);
				iDgrXPosTerminal = pAfterOperation->getReleaseJikoku().getTotalSeconds();
			}
		}

		int iHatsuOperation = 0;
		int iOuterEkiIndex;
		const CentDedAfterOperation* pLastOperation = pAfterCont->getMuPtr()->get(INT_MAX);
		if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_In)
		{
			tstring strOperationNumber;
			if (getCentDedDgrDia()->getEnableOperation() > 1)
			{
				strOperationNumber = joinc('+', pLastOperation->getOperationNumber(), true);
			}
			Zaisen aZaisen(iRessyaTrack,
				shiftDgrXPos(iDgrXPosChaku, iDgrXPosBase),
				shiftDgrXPos(pLastOperation->getInJikoku().getTotalSeconds(), iDgrXPosBase),
				strOperationNumber);
			contZaisen.push_back(aZaisen);
			Zaisen aZaisenNoDisplay(0,
				shiftDgrXPos(pEkiJikoku->getChakujikoku().getTotalSeconds(), iDgrXPosBase),
				shiftDgrXPos(pEkiJikoku->getChakujikoku().getTotalSeconds(), iDgrXPosBase),
				strOperationNumber);
			contZaisenNoDisplay.push_back(aZaisenNoDisplay);
			iHatsuOperation = 3;

			int iDgrXPosIn = shiftDgrXPos(pLastOperation->getInJikoku().getTotalSeconds(), iDgrXPosBase) + 120;
			if (m_DgrXZone.getEndPos() < iDgrXPosIn)
			{
				m_DgrXZone.setBeginEndPos(m_DgrXZone.getPos(), iDgrXPosIn);
			}
		}
		else if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
		{
			iOuterEkiIndex = pLastOperation->getOuterShuchakuekiIndex();
			tstring strOperationNumber;
			if (getCentDedDgrDia()->getEnableOperation() > 1)
			{
				strOperationNumber = joinc('+', pLastOperation->getOperationNumber(), true);
			}
			int iDgrXPosHatsuTemp = pLastOperation->getHatsuJikoku().getTotalSeconds();
			if (iDgrXPosHatsuTemp == INT_MIN)
			{
				iDgrXPosHatsuTemp = iDgrXPosChaku;
			}
			Zaisen aZaisen(iRessyaTrack,
				shiftDgrXPos(iDgrXPosChaku, iDgrXPosBase),
				shiftDgrXPos(iDgrXPosHatsuTemp, iDgrXPosBase),
				strOperationNumber);
			contZaisen.push_back(aZaisen);
			Zaisen aZaisenNoDisplay(
				0,
				shiftDgrXPos(pEkiJikoku->getChakujikoku().getTotalSeconds(), iDgrXPosBase),
				shiftDgrXPos(iDgrXPosHatsuTemp, iDgrXPosBase),
				strOperationNumber);
			contZaisenNoDisplay.push_back(aZaisenNoDisplay);

			iHatsuOperation = 4;

			int iDgrXPosOuter = shiftDgrXPos(iDgrXPosHatsuTemp, iDgrXPosBase) + 120;
			if (m_DgrXZone.getEndPos() < iDgrXPosOuter)
			{
				m_DgrXZone.setBeginEndPos(m_DgrXZone.getPos(), iDgrXPosOuter);
			}
		}
		else if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Junction)
		{
			int iDgrXPosJunction = INT_MIN;
			if (pLastOperation->getJunctionSucceed() &&
				getCentDedDgrDia()->getEnableOperation() > 0)
			{
				iHatsuOperation = 5;
				iDgrXPosTerminal = pLastOperation->getJunctionJikoku().getTotalSeconds();

				iDgrXPosJunction = shiftDgrXPos(pLastOperation->getJunctionJikoku().getTotalSeconds(), iDgrXPosBase);
			}
			else if (!pLastOperation->getTerminalJikoku().isNull())
			{
				iDgrXPosTerminal = pLastOperation->getTerminalJikoku().getTotalSeconds();

				iDgrXPosJunction = shiftDgrXPos(pLastOperation->getTerminalJikoku().getTotalSeconds(), iDgrXPosBase);
			}
			else if ((iDgrXPosTerminal - iDgrXPosChaku) < 60)
			{
				iDgrXPosTerminal = iDgrXPosChaku + 60;

				iDgrXPosJunction = shiftDgrXPos(iDgrXPosChaku + 60, iDgrXPosBase);
			}

			Zaisen aZaisen(iRessyaTrack,
				shiftDgrXPos(iDgrXPosChaku, iDgrXPosBase),
				shiftDgrXPos(iDgrXPosTerminal, iDgrXPosBase));
			contZaisen.push_back(aZaisen);
			Zaisen aZaisenNoDisplay(
				0,
				shiftDgrXPos(pEkiJikoku->getChakujikoku().getTotalSeconds(), iDgrXPosBase),
				shiftDgrXPos(pEkiJikoku->getChakujikoku().getTotalSeconds(), iDgrXPosBase));
			contZaisenNoDisplay.push_front(aZaisenNoDisplay);

			if (iDgrXPosJunction != INT_MIN && m_DgrXZone.getEndPos() < iDgrXPosJunction)
			{
				m_DgrXZone.setBeginEndPos(m_DgrXZone.getPos(), iDgrXPosJunction);
			}
		}

		/**
			Zaisenコンテナが完成したら、RessyaTrackLine形式に仕立てる。
			分岐・環状線で関係する駅全ての分を、ここで生成します。
			iPosition:-1
				単独駅、自駅分の生成のみを行う
			iPosition:INT_MIN
				起点側派生駅
				基幹駅群、分岐駅群全てで生成を行います。
			iPosition:0-
				基幹駅・起点駅・終点駅
				基幹駅群、分岐駅群全てで生成を行います。
			iPosition:INT_MAX
				終点側派生駅
				基幹駅群、分岐駅群全てで生成を行います。
		*/
		deque<int> iEkiOrderBrunchOriginSide;
		deque<int> iEkiOrderLoop;
		deque<int> iEkiOrderBrunchTerminalSide;
		int iPosition = pCentDedEkiCont->getEkiOrderBrunchLoop(
			iValidSyuuchakuEki,
			getRessyahoukou(),
			iEkiOrderBrunchOriginSide,
			iEkiOrderLoop,
			iEkiOrderBrunchTerminalSide);
		CentDedDgrEkiCont::CdDedDgrEki aEki = pMuCdDedDgrEki->get(iValidSyuuchakuEki);
		if (iPosition == -1)
		{
			if (aEki.getDiagramTrackDisplay())
			{
				CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
					iValidSyuuchakuEki,
					iTsuukaTeisya,
					-1,
					iHatsuOperation,
					true);
				aCentDedDgrRessyaTrackLine.setZaisen(contZaisen);
				if (iHatsuOperation == 4)
				{
					aCentDedDgrRessyaTrackLine.setOuterEkiIndex(iOuterEkiIndex);
				}
				m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
			}
			else if(iHatsuOperation != 0 && iHatsuOperation != 5)
			{
				CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
					iValidSyuuchakuEki,
					iTsuukaTeisya,
					-1,
					iHatsuOperation,
					false);
				aCentDedDgrRessyaTrackLine.setZaisen(contZaisenNoDisplay);
				if (iHatsuOperation == 4)
				{
					aCentDedDgrRessyaTrackLine.setOuterEkiIndex(iOuterEkiIndex);
				}
				m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
			}
		}
		else //if (iPosition != -1)
		{
			for (int idxo = 0; idxo < (int)iEkiOrderBrunchOriginSide.size(); idxo++)
			{
				CentDedDgrEkiCont::CdDedDgrEki aEkiOrigin = pMuCdDedDgrEki->get(iEkiOrderBrunchOriginSide[idxo]);
				int iChakuOperation = -1;
				/**
					iChakuOperationを決定する。
					iEkiOrderLoop[idxl]がiValidSyuuchakuEkiの場合は、-1
					それ以外の場合は、
					(1)iValidSyuuchakuEkiとiEkiOrderLoop[idxl]が共に反転、もしくはともに無反転の場合は、-2(起点方)
						どちらかのみ反転の場合は-4(終点方から到着)
				*/
				if (iEkiOrderBrunchOriginSide[idxo] != iValidSyuuchakuEki)
				{
					if ((aEki.getBrunchOpposite() || aEki.getLoopOpposite()) ==
						aEkiOrigin.getBrunchOpposite())
					{
						iChakuOperation = -2;
					}
					else
					{
						iChakuOperation = -4;
					}
				}
				if (aEkiOrigin.getDiagramTrackDisplay())
				{
					CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
						iEkiOrderBrunchOriginSide[idxo],
						iTsuukaTeisya,
						iChakuOperation,
						iHatsuOperation,
						true);
					aCentDedDgrRessyaTrackLine.setZaisen(contZaisen);
					if (iHatsuOperation == 4)
					{
						aCentDedDgrRessyaTrackLine.setOuterEkiIndex(iOuterEkiIndex);
					}
					m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
				}
				/**
					在線表非表示の分岐駅では、終着駅自身でのみ、入区や路線外終着の表示を行います。
				*/
				else if (iEkiOrderBrunchOriginSide[idxo] == iValidSyuuchakuEki &&
					(iHatsuOperation != 0 && iHatsuOperation != 5))
				{
					CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
						iEkiOrderBrunchOriginSide[idxo],
						iTsuukaTeisya,
						iChakuOperation,
						iHatsuOperation,
						false);
					aCentDedDgrRessyaTrackLine.setZaisen(contZaisenNoDisplay);
					if (iHatsuOperation == 4)
					{
						aCentDedDgrRessyaTrackLine.setOuterEkiIndex(iOuterEkiIndex);
					}
					m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
				}
			}

			for (int idxl = 0; idxl < (int)iEkiOrderLoop.size(); idxl++)
			{
				CentDedDgrEkiCont::CdDedDgrEki aEkiLoop = pMuCdDedDgrEki->get(iEkiOrderLoop[idxl]);
				int iChakuOperation = -1;
				/**
					iChakuOperationを決定する。
					iEkiOrderLoop[idxl]がiValidSyuuchakuEkiの場合は、-1
					それ以外の場合は、
					(1)iValidSyuuchakuEkiとiEkiOrderLoop[idxl]が共に反転、もしくはともに無反転の場合は、-2(起点方)
						どちらかのみ反転の場合は-4(終点方から到着)
				*/
				if (iEkiOrderLoop[idxl] != iValidSyuuchakuEki)
				{
					if ((aEki.getBrunchOpposite() || aEki.getLoopOpposite()) ==
						aEkiLoop.getLoopOpposite())
					{
						iChakuOperation = -2;
					}
					else
					{
						iChakuOperation = -4;
					}
				}
				if (aEkiLoop.getDiagramTrackDisplay())
				{
					CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
						iEkiOrderLoop[idxl],
						iTsuukaTeisya,
						iChakuOperation,
						iHatsuOperation,
						true);
					aCentDedDgrRessyaTrackLine.setZaisen(contZaisen);
					if (iHatsuOperation == 4)
					{
						aCentDedDgrRessyaTrackLine.setOuterEkiIndex(iOuterEkiIndex);
					}
					m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
				}
				else if ((iHatsuOperation != 0 && iHatsuOperation != 5 )||
					iChakuOperation == -2 || iChakuOperation == -4)
				{
					CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
						iEkiOrderLoop[idxl],
						iTsuukaTeisya,
						iChakuOperation,
						iHatsuOperation,
						false);
					aCentDedDgrRessyaTrackLine.setZaisen(contZaisenNoDisplay);
					if (iHatsuOperation == 4)
					{
						aCentDedDgrRessyaTrackLine.setOuterEkiIndex(iOuterEkiIndex);
					}
					m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
				}
			}

			for (int idxt = 0; idxt < (int)iEkiOrderBrunchTerminalSide.size(); idxt++)
			{
				CentDedDgrEkiCont::CdDedDgrEki aEkiTerminal = pMuCdDedDgrEki->get(iEkiOrderBrunchTerminalSide[idxt]);
				int iChakuOperation = -1;
				/**
					iChakuOperationを決定する。
					iEkiOrderLoop[idxl]がiValidSyuuchakuEkiの場合は、-1
					それ以外の場合は、
					(1)iValidSyuuchakuEkiとiEkiOrderLoop[idxl]が共に反転、もしくはともに無反転の場合は、-2(起点方)
						どちらかのみ反転の場合は-4(終点方から到着)
				*/
				if (iEkiOrderBrunchTerminalSide[idxt] != iValidSyuuchakuEki)
				{
					if ((aEki.getBrunchOpposite() || aEki.getLoopOpposite()) ==
						aEkiTerminal.getBrunchOpposite())
					{
						iChakuOperation = -2;
					}
					else
					{
						iChakuOperation = -4;
					}
				}
				if (aEkiTerminal.getDiagramTrackDisplay())
				{
					CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
						iEkiOrderBrunchTerminalSide[idxt],
						iTsuukaTeisya,
						iChakuOperation,
						iHatsuOperation,
						true);
					aCentDedDgrRessyaTrackLine.setZaisen(contZaisen);
					if (iHatsuOperation == 4)
					{
						aCentDedDgrRessyaTrackLine.setOuterEkiIndex(iOuterEkiIndex);
					}
					m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
				}
				/**
					在線表非表示の分岐駅では、駅自身でのみ、出区や路線外始発の表示を行います。
				*/
			}
		}
	}
}

void CentDedDgrRessya::updateRessyaTrackLineBeforeCont(
	const CentDedBeforeOperationCont * pBeforeCont,
	const int iEkiOrder,
	const int iConnectTrack,
	const int iDgrXPosConnect,
	const int iTsuukaTeisya,
	const bool bParentIsMain,
	const Mu<CentDedDgrEkiCont::CdDedDgrEki>* pMuCdDedDgrEki, 
	const CentDedEkiCont * pCentDedEkiCont)
{
	//int iHatsuOperation = 1;
	deque<Zaisen> contZaisen;
	deque<Zaisen> contZaisenNoDisplay;
	int iRessyaTrack = iConnectTrack;
	/**
		この駅の発着番線および前作業に対するZaisenの、発時刻になります。
		まずは、発着番線に対する発時刻を後作業探索で求めます。
		有効な入換作業がある場合は、その入換発時刻(複数ある場合は最も手前の物)
		無い場合は、当駅発時刻になります。

		前作業探索で、最初に有効な入換が見つかった場合は、この値を基に、発着番線に対するZaisenを作成します、
		その後は、前作業探索において、一つ後ろの入換発時刻を保持する変数として使用します。

	*/
	int iDgrXPosHatsu = iDgrXPosConnect;
	/**
		この列車の起点時刻です。
		この列車の先端作業が、出区・路線外始発の場合は、それらの作業から起点時刻をとりますが、
		前列車接続で起点時刻未設定かつ、運用無効もしくは前列車が無い場合は、
		他作業及び当駅発時刻から、起点時刻を導く必要があります。
	*/
	int iDgrXPosOrigin = iDgrXPosConnect;
	for (int idxb = (int)pBeforeCont->size() - 1; idxb > 0; idxb--)
	{
		const CentDedBeforeOperation* pBeforeOperation = pBeforeCont->getMuPtr()->get(idxb);
		if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Shunt)
		{
			if (pBeforeOperation->getShuntTrackIndex() != iRessyaTrack)
			{
				Zaisen aZaisen(iRessyaTrack,
					shiftDgrXPos(pBeforeOperation->getOperationChakuJikoku(true).getTotalSeconds(), iDgrXPosConnect, true),
					shiftDgrXPos(iDgrXPosHatsu, iDgrXPosConnect, true));
				contZaisen.push_front(aZaisen);

				iDgrXPosHatsu = pBeforeOperation->getOperationHatsuJikoku().getTotalSeconds();
				iRessyaTrack = pBeforeOperation->getShuntTrackIndex();
				iDgrXPosOrigin = pBeforeOperation->getOperationHatsuJikoku().getTotalSeconds();
			}
		}
		else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Connect)
		{
			updateRessyaTrackLineBeforeCont(
				pBeforeOperation->getCentDedBeforeOperationCont(),
				iEkiOrder,
				iRessyaTrack,
				shiftDgrXPos(pBeforeOperation->getConnectJikoku().getTotalSeconds(), iDgrXPosConnect,true),
				iTsuukaTeisya,
				false,
				pMuCdDedDgrEki,
				pCentDedEkiCont);
			iDgrXPosOrigin = pBeforeOperation->getConnectJikoku().getTotalSeconds();
		}
		else if (pBeforeOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Release)
		{
			updateRessyaTrackLineAfterCont(
				pBeforeOperation->getCentDedAfterOperationCont(),
				iEkiOrder,
				iRessyaTrack,
				shiftDgrXPos(pBeforeOperation->getReleaseJikoku().getTotalSeconds(), iDgrXPosConnect, true),
				iTsuukaTeisya,
				false,
				pMuCdDedDgrEki,
				pCentDedEkiCont);
			iDgrXPosOrigin = pBeforeOperation->getReleaseJikoku().getTotalSeconds();
		}
	}

	int iChakuOperation = 0;
	int iChakuOperationNoDisplay = 0;
	int iPrevRessyahoukou = 0;
	//int iPrevRessyahoukouNoDisplay = 0;
	int iEkiOrderOfPrevSyuuchakuEki = iEkiOrder;
	int iOuterEkiIndex;

	const CentDedBeforeOperation* pFirstOperation = pBeforeCont->getMuPtr()->get(0);
	if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Out)
	{
		tstring strOperationNumber;
		if (getCentDedDgrDia()->getEnableOperation() > 1)
		{
			strOperationNumber = joinc('+', pFirstOperation->getOperationNumber(), true);
		}
		Zaisen aZaisen(iRessyaTrack,
			shiftDgrXPos(pFirstOperation->getOutJikoku().getTotalSeconds(), iDgrXPosConnect, true),
			shiftDgrXPos(iDgrXPosHatsu, iDgrXPosConnect, true),
			strOperationNumber);
		contZaisen.push_front(aZaisen);
		if (bParentIsMain)
		{
			Zaisen aZaisenNoDisplay(0,
				iDgrXPosConnect,
				iDgrXPosConnect);
			contZaisenNoDisplay.push_front(aZaisenNoDisplay);
		}
		iChakuOperation = 3;

		int iDgrXPosOut = shiftDgrXPos(pFirstOperation->getOutJikoku().getTotalSeconds(), iDgrXPosConnect, true) - 120;
		if (m_DgrXZone.getPos() > iDgrXPosOut)
		{
			m_DgrXZone.setBeginEndPos(iDgrXPosOut, m_DgrXZone.getEndPos());
		}
	}
	else if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Outer)
	{
		iOuterEkiIndex = pFirstOperation->getOuterShihatsuekiIndex();
		tstring strOperationNumber;
		if (getCentDedDgrDia()->getEnableOperation() > 1)
		{
			strOperationNumber = joinc('+', pFirstOperation->getOperationNumber(), true);
		}
		int iDgrXPosChakuTemp = pFirstOperation->getChakuJikoku().getTotalSeconds();
		if (iDgrXPosChakuTemp == INT_MIN)
		{
			iDgrXPosChakuTemp = iDgrXPosHatsu;
		}
		Zaisen aZaisen(iRessyaTrack,
			shiftDgrXPos(iDgrXPosChakuTemp, iDgrXPosConnect, true),
			shiftDgrXPos(iDgrXPosHatsu, iDgrXPosConnect, true),
			strOperationNumber);
		contZaisen.push_front(aZaisen);
		Zaisen aZaisenNoDisplay(0,
			shiftDgrXPos(iDgrXPosChakuTemp, iDgrXPosConnect, true),
			iDgrXPosConnect,
			strOperationNumber);
		contZaisenNoDisplay.push_front(aZaisenNoDisplay);
		iChakuOperation = 4;
		iChakuOperationNoDisplay = 4;

		int iDgrXPosOuter = shiftDgrXPos(iDgrXPosChakuTemp, iDgrXPosConnect, true) - 120;
		if (m_DgrXZone.getPos() > iDgrXPosOuter)
		{
			m_DgrXZone.setBeginEndPos(iDgrXPosOuter, m_DgrXZone.getEndPos());
		}
	}
	else if (pFirstOperation->getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Junction)
	{
		tstring strOperationNumber;
		if (getCentDedDgrDia()->getEnableOperation() > 0)
		{
			strOperationNumber = joinc('+', pFirstOperation->getOperationNumber(), true);
		}

		int iDgrXPosJunction = INT_MIN;
		if (!pFirstOperation->getJunctionJikoku().isNull() &&
			getCentDedDgrDia()->getEnableOperation() > 0)
		{
			iChakuOperation = 5;
			iDgrXPosOrigin = pFirstOperation->getJunctionJikoku().getTotalSeconds();
			iPrevRessyahoukou = pFirstOperation->getPrevRessyahoukou();

			iDgrXPosJunction = shiftDgrXPos(pFirstOperation->getJunctionJikoku().getTotalSeconds(), iDgrXPosConnect, true);
		}
		else if (!pFirstOperation->getOriginJikoku().isNull())
		{
			iDgrXPosOrigin = pFirstOperation->getOriginJikoku().getTotalSeconds();

			iDgrXPosJunction = shiftDgrXPos(pFirstOperation->getOriginJikoku().getTotalSeconds(), iDgrXPosConnect, true);
		}
		else if ((iDgrXPosHatsu - iDgrXPosOrigin) < 60)
		{
			iDgrXPosOrigin = iDgrXPosHatsu - 60;

			iDgrXPosJunction = shiftDgrXPos(iDgrXPosHatsu - 60, iDgrXPosConnect, true);
		}

		if (getCentDedDgrDia()->getEnableOperation() > 0)
		{
			iEkiOrderOfPrevSyuuchakuEki = pFirstOperation->getEkiOrderOfPrevSyuuchakuEki();
		}

		Zaisen aZaisen(iRessyaTrack,
			shiftDgrXPos(iDgrXPosOrigin, iDgrXPosConnect, true),
			shiftDgrXPos(iDgrXPosHatsu, iDgrXPosConnect, true),
			strOperationNumber);
		contZaisen.push_front(aZaisen);
		if (bParentIsMain)
		{
			Zaisen aZaisenNoDisplay(0,
				iDgrXPosConnect,
				iDgrXPosConnect);
			contZaisenNoDisplay.push_front(aZaisenNoDisplay);
		}

		if (iDgrXPosJunction != INT_MIN && m_DgrXZone.getPos() > iDgrXPosJunction)
		{
			m_DgrXZone.setBeginEndPos(iDgrXPosJunction, m_DgrXZone.getEndPos());
		}
	}

	/**
		Zaisenコンテナが完成したら、RessyaTrackLine形式に仕立てる。
		分岐・環状線で関係する駅全ての分を、ここで生成します。
		iPosition:-1
			単独駅、自駅分の生成のみを行う
		iPosition:INT_MIN
			起点側派生駅、この駅では在線表表示はありません
			自駅と基幹駅群で生成を行います。
		iPosition:0-
			基幹駅・起点駅・終点駅
			自駅を含む基幹駅群で生成を行います。
		iPosition:INT_MAX
			終点側派生駅、この駅では在線表表示はありません
			自駅と基幹駅群で生成を行います。
	*/
	deque<int> iEkiOrderBrunchOriginSide;
	deque<int> iEkiOrderLoop;
	deque<int> iEkiOrderBrunchTerminalSide;
	int iPosition = pCentDedEkiCont->getEkiOrderBrunchLoop(
		iEkiOrder,
		getRessyahoukou(),
		iEkiOrderBrunchOriginSide,
		iEkiOrderLoop,
		iEkiOrderBrunchTerminalSide);
	CentDedDgrEkiCont::CdDedDgrEki aEki = pMuCdDedDgrEki->get(iEkiOrder);
	if (iPosition == -1)
	{
		if (aEki.getDiagramTrackDisplay()) 
		{
			CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
				iEkiOrder,
				iTsuukaTeisya,
				iChakuOperation,
				1,
				true);
			aCentDedDgrRessyaTrackLine.setZaisen(contZaisen);
			aCentDedDgrRessyaTrackLine.setPrevRessyahoukou(iPrevRessyahoukou);
			if (iChakuOperation == 4)
			{
				aCentDedDgrRessyaTrackLine.setOuterEkiIndex(iOuterEkiIndex);
			}
			m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
		}
		else if (bParentIsMain)
		{
			CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
				iEkiOrder,
				iTsuukaTeisya,
				iChakuOperationNoDisplay,
				1,
				false);
			aCentDedDgrRessyaTrackLine.setZaisen(contZaisenNoDisplay);
			if (iChakuOperationNoDisplay == 4)
			{
				aCentDedDgrRessyaTrackLine.setOuterEkiIndex(iOuterEkiIndex);
			}
			m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
		}
		else if(contZaisenNoDisplay.size() >0)
		{
			CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
				iEkiOrder,
				iTsuukaTeisya,
				iChakuOperationNoDisplay,
				0,
				false);
			aCentDedDgrRessyaTrackLine.setZaisen(contZaisenNoDisplay);
			if (iChakuOperationNoDisplay == 4)
			{
				aCentDedDgrRessyaTrackLine.setOuterEkiIndex(iOuterEkiIndex);
			}
			m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
		}
	}
	else//if (iPosition != -1)
	{
		for (int idxo = 0; idxo < (int)iEkiOrderBrunchOriginSide.size(); idxo++)
		{
			CentDedDgrEkiCont::CdDedDgrEki aEkiOrigin = pMuCdDedDgrEki->get(iEkiOrderBrunchOriginSide[idxo]);

			if (aEkiOrigin.getDiagramTrackDisplay())
			{
				/**
					iPrevRessyahoukouが2,-2の場合は反転駅設定は影響なし
					表示駅と前列車終着駅が同じ場合も、反転駅設定は影響なし
				*/
				int iPrevRessyahoukouThis = iPrevRessyahoukou;
				if ((iPrevRessyahoukouThis == 1 ||
					iPrevRessyahoukouThis == -1) &&
					iEkiOrderBrunchOriginSide[idxo] != iEkiOrderOfPrevSyuuchakuEki)
				{
					CentDedDgrEkiCont::CdDedDgrEki aEkiSyuuchaku = pMuCdDedDgrEki->get(iEkiOrderOfPrevSyuuchakuEki);
					if (aEkiOrigin.getBrunchOpposite() !=
						(aEkiSyuuchaku.getBrunchOpposite() ||
							aEkiSyuuchaku.getLoopOpposite()))
					{
						iPrevRessyahoukouThis *= -1;
					}

				}
				CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
					iEkiOrderBrunchOriginSide[idxo],
					iTsuukaTeisya,
					iChakuOperation,
					1,
					true);
				aCentDedDgrRessyaTrackLine.setZaisen(contZaisen);
				aCentDedDgrRessyaTrackLine.setPrevRessyahoukou(iPrevRessyahoukouThis);
				if (iChakuOperation == 4)
				{
					aCentDedDgrRessyaTrackLine.setOuterEkiIndex(iOuterEkiIndex);
				}
				m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
			}
			/**
				在線表非表示の場合、iEkiOrder == iEkiOrderBrunchOriginSide[idxo]の時のみ表示する。
			*/
			else if (iEkiOrder == iEkiOrderBrunchOriginSide[idxo] && bParentIsMain)
			{
				CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
					iEkiOrderBrunchOriginSide[idxo],
					iTsuukaTeisya,
					iChakuOperationNoDisplay,
					1,
					false);
				aCentDedDgrRessyaTrackLine.setZaisen(contZaisenNoDisplay);
				if (iChakuOperationNoDisplay == 4)
				{
					aCentDedDgrRessyaTrackLine.setOuterEkiIndex(iOuterEkiIndex);
				}
				m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
			}
			else if (iEkiOrder == iEkiOrderBrunchOriginSide[idxo] && contZaisenNoDisplay.size() > 0)
			{
				CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
					iEkiOrderBrunchOriginSide[idxo],
					iTsuukaTeisya,
					iChakuOperationNoDisplay,
					0,
					false);
				aCentDedDgrRessyaTrackLine.setZaisen(contZaisenNoDisplay);
				if (iChakuOperationNoDisplay == 4)
				{
					aCentDedDgrRessyaTrackLine.setOuterEkiIndex(iOuterEkiIndex);
				}
				m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
			}
		}

		for (int idxl = 0; idxl < (int)iEkiOrderLoop.size(); idxl++)
		{
			CentDedDgrEkiCont::CdDedDgrEki aEkiLoop = pMuCdDedDgrEki->get(iEkiOrderLoop[idxl]);
			const CentDedEki* pEkiLoop = pCentDedEkiCont->getMuPtr()->get(
				pCentDedEkiCont->EkiIndexOfEkiOrder(getRessyahoukou(), iEkiOrderLoop[idxl]));

			if (aEkiLoop.getDiagramTrackDisplay())
			{
				/**
					iPrevRessyahoukouが2,-2の場合は反転駅設定は影響なし
					表示駅と前列車終着駅が同じ場合も、反転駅設定は影響なし
				*/
				int iPrevRessyahoukouThis = iPrevRessyahoukou;
				if ((iPrevRessyahoukouThis == 1 ||
					iPrevRessyahoukouThis == -1) &&
					iEkiOrderLoop[idxl] != iEkiOrderOfPrevSyuuchakuEki)
				{
					CentDedDgrEkiCont::CdDedDgrEki aEkiSyuuchaku = pMuCdDedDgrEki->get(iEkiOrderOfPrevSyuuchakuEki);
					if ((aEkiLoop.getBrunchOpposite() ||
						aEkiLoop.getLoopOpposite()) !=
						(aEkiSyuuchaku.getBrunchOpposite() ||
							aEkiSyuuchaku.getLoopOpposite()))
					{
						iPrevRessyahoukouThis *= -1;
					}

				}
				CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
					iEkiOrderLoop[idxl],
					iTsuukaTeisya,
					iChakuOperation,
					1,
					true);
				aCentDedDgrRessyaTrackLine.setZaisen(contZaisen);
				aCentDedDgrRessyaTrackLine.setPrevRessyahoukou(iPrevRessyahoukouThis);
				if (iChakuOperation == 4)
				{
					aCentDedDgrRessyaTrackLine.setOuterEkiIndex(iOuterEkiIndex);
				}
				m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
			}
			else if (bParentIsMain)
			{
				CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
					iEkiOrderLoop[idxl],
					iTsuukaTeisya,
					iChakuOperationNoDisplay,
					1,
					false);
				aCentDedDgrRessyaTrackLine.setZaisen(contZaisenNoDisplay);
				if (iChakuOperationNoDisplay == 4)
				{
					aCentDedDgrRessyaTrackLine.setOuterEkiIndex(iOuterEkiIndex);
				}
				m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
			}
			else if (contZaisenNoDisplay.size() > 0)
			{
				CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
					iEkiOrderLoop[idxl],
					iTsuukaTeisya,
					iChakuOperationNoDisplay,
					0,
					false);
				aCentDedDgrRessyaTrackLine.setZaisen(contZaisenNoDisplay);
				if (iChakuOperationNoDisplay == 4)
				{
					aCentDedDgrRessyaTrackLine.setOuterEkiIndex(iOuterEkiIndex);
				}
				m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
			}
		}

		for (int idxt = 0; idxt < (int)iEkiOrderBrunchTerminalSide.size(); idxt++)
		{
			CentDedDgrEkiCont::CdDedDgrEki aEkiTerminal = pMuCdDedDgrEki->get(iEkiOrderBrunchTerminalSide[idxt]);

			if (aEkiTerminal.getDiagramTrackDisplay())
			{
				/**
					iPrevRessyahoukouが2,-2の場合は反転駅設定は影響なし
					表示駅と前列車終着駅が同じ場合も、反転駅設定は影響なし
				*/
				int iPrevRessyahoukouThis = iPrevRessyahoukou;
				if ((iPrevRessyahoukouThis == 1 ||
					iPrevRessyahoukouThis == -1) &&
					iEkiOrderBrunchTerminalSide[idxt] != iEkiOrderOfPrevSyuuchakuEki)
				{
					CentDedDgrEkiCont::CdDedDgrEki aEkiSyuuchaku = pMuCdDedDgrEki->get(iEkiOrderOfPrevSyuuchakuEki);
					if (aEkiTerminal.getBrunchOpposite() !=
						(aEkiSyuuchaku.getBrunchOpposite() ||
							aEkiSyuuchaku.getLoopOpposite()))
					{
						iPrevRessyahoukouThis *= -1;
					}

				}
				CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
					iEkiOrderBrunchTerminalSide[idxt],
					iTsuukaTeisya,
					iChakuOperation,
					1,
					true);
				aCentDedDgrRessyaTrackLine.setZaisen(contZaisen);
				aCentDedDgrRessyaTrackLine.setPrevRessyahoukou(iPrevRessyahoukouThis);
				if (iChakuOperation == 4)
				{
					aCentDedDgrRessyaTrackLine.setOuterEkiIndex(iOuterEkiIndex);
				}
				m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
			}
			/**
				在線表非表示の場合、iEkiOrder == iEkiOrderBrunchTerminalSide[idxt]の時のみ表示する。
			*/
			else if (iEkiOrder == iEkiOrderBrunchTerminalSide[idxt] && bParentIsMain)
			{
				CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
					iEkiOrderBrunchTerminalSide[idxt],
					iTsuukaTeisya,
					iChakuOperationNoDisplay,
					1,
					false);
				aCentDedDgrRessyaTrackLine.setZaisen(contZaisenNoDisplay);
				if (iChakuOperationNoDisplay == 4)
				{
					aCentDedDgrRessyaTrackLine.setOuterEkiIndex(iOuterEkiIndex);
				}
				m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
			}
			else if (iEkiOrder == iEkiOrderBrunchTerminalSide[idxt] && contZaisenNoDisplay.size() > 0)
			{
				CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
					iEkiOrderBrunchTerminalSide[idxt],
					iTsuukaTeisya,
					iChakuOperationNoDisplay,
					0,
					false);
				aCentDedDgrRessyaTrackLine.setZaisen(contZaisenNoDisplay);
				if (iChakuOperationNoDisplay == 4)
				{
					aCentDedDgrRessyaTrackLine.setOuterEkiIndex(iOuterEkiIndex);
				}
				m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
			}
		}
	}
}

void CentDedDgrRessya::updateRessyaTrackLineAfterCont(
	const CentDedAfterOperationCont * pAfterCont, 
	const int iEkiOrder, const int iReleaseTrack, 
	const int iDgrXPosRelease, 
	const int iTsuukaTeisya,
	const bool bParentIsMain,
	const Mu<CentDedDgrEkiCont::CdDedDgrEki>* pMuCdDedDgrEki, 
	const CentDedEkiCont * pCentDedEkiCont)
{

	deque<Zaisen> contZaisen;
	deque<Zaisen> contZaisenNoDisplay;
	int iRessyaTrack = iReleaseTrack;

	/**
		この駅の発着番線および後作業に対するZaisenの、着時刻になります。
		まずは、発着番線に対する着時刻を前作業探索で求めます。
		有効な入換作業がある場合は、その入換着時刻(複数ある場合は最も後ろの物)
		無い場合は、当駅着時刻になります。

		後作業探索で、最初に有効な入換が見つかった場合は、この値を基に、発着番線に対するZaisenを作成します、
		その後は、後作業探索において、一つ前の入換着時刻を保持する変数として使用します。

	*/
	int iDgrXPosChaku = iDgrXPosRelease;
	/**
		この列車の終点時刻です。
		この列車の終端作業が、入区・路線外終着の場合は、それらの作業から終点時刻をとりますが、
		次列車接続で終点時刻未設定の場合は、
		他作業及び当駅着時刻から、終点時刻を導く必要があります。
	*/
	int iDgrXPosTerminal = iDgrXPosRelease;
	for (int idxa = 0; idxa < (int)pAfterCont->size() - 1; idxa++)
	{
		const CentDedAfterOperation* pAfterOperation = pAfterCont->getMuPtr()->get(idxa);
		if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Shunt)
		{
			if (pAfterOperation->getShuntTrackIndex() != iRessyaTrack)
			{
				Zaisen aZaisen(iRessyaTrack,
					shiftDgrXPos(iDgrXPosChaku, iDgrXPosRelease),
					shiftDgrXPos(pAfterOperation->getOperationHatsuJikoku().getTotalSeconds(), iDgrXPosRelease));
				contZaisen.push_back(aZaisen);

				iDgrXPosChaku = pAfterOperation->getOperationChakuJikoku(true).getTotalSeconds();
				iRessyaTrack = pAfterOperation->getShuntTrackIndex();
				iDgrXPosTerminal = pAfterOperation->getOperationChakuJikoku(true).getTotalSeconds();
			}
		}
		else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Connect)
		{
			updateRessyaTrackLineBeforeCont(
				pAfterOperation->getCentDedBeforeOperationCont(),
				iEkiOrder,
				iRessyaTrack,
				shiftDgrXPos(pAfterOperation->getConnectJikoku().getTotalSeconds(), iDgrXPosRelease),
				iTsuukaTeisya,
				false,
				pMuCdDedDgrEki,
				pCentDedEkiCont);
			iDgrXPosTerminal = pAfterOperation->getConnectJikoku().getTotalSeconds();
		}
		else if (pAfterOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Release)
		{
			updateRessyaTrackLineAfterCont(
				pAfterOperation->getCentDedAfterOperationCont(),
				iEkiOrder,
				iRessyaTrack,
				shiftDgrXPos(pAfterOperation->getReleaseJikoku().getTotalSeconds(), iDgrXPosRelease),
				iTsuukaTeisya,
				false,
				pMuCdDedDgrEki,
				pCentDedEkiCont);
			iDgrXPosTerminal = pAfterOperation->getReleaseJikoku().getTotalSeconds();
		}
	}

	int iHatsuOperation = 0;
	int iOuterEkiIndex;
	const CentDedAfterOperation* pLastOperation = pAfterCont->getMuPtr()->get(INT_MAX);
	if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_In)
	{
		tstring strOperationNumber;
		if (getCentDedDgrDia()->getEnableOperation() > 1)
		{
			strOperationNumber = joinc('+', pLastOperation->getOperationNumber(), true);
		}
		Zaisen aZaisen(iRessyaTrack,
			shiftDgrXPos(iDgrXPosChaku, iDgrXPosRelease),
			shiftDgrXPos(pLastOperation->getInJikoku().getTotalSeconds(), iDgrXPosRelease),
			strOperationNumber);
		contZaisen.push_back(aZaisen);
		if (bParentIsMain)
		{
			Zaisen aZaisenNoDisplay(0,
				iDgrXPosRelease,
				iDgrXPosRelease);
			contZaisenNoDisplay.push_back(aZaisenNoDisplay);
		}
		iHatsuOperation = 3;

		int iDgrXPosIn = shiftDgrXPos(pLastOperation->getInJikoku().getTotalSeconds(), iDgrXPosRelease) + 120;
		if (m_DgrXZone.getEndPos() < iDgrXPosIn)
		{
			m_DgrXZone.setBeginEndPos(m_DgrXZone.getPos(), iDgrXPosIn);
		}
	}
	else if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Outer)
	{
		iOuterEkiIndex = pLastOperation->getOuterShuchakuekiIndex();
		tstring strOperationNumber;
		if (getCentDedDgrDia()->getEnableOperation() > 1)
		{
			strOperationNumber = joinc('+', pLastOperation->getOperationNumber(), true);
		}
		int iDgrXPosHatsuTemp = pLastOperation->getHatsuJikoku().getTotalSeconds();
		if (iDgrXPosHatsuTemp == INT_MIN)
		{
			iDgrXPosHatsuTemp = iDgrXPosChaku;
		}
		Zaisen aZaisen(iRessyaTrack,
			shiftDgrXPos(iDgrXPosChaku, iDgrXPosRelease),
			shiftDgrXPos(iDgrXPosHatsuTemp, iDgrXPosRelease),
			strOperationNumber);
		contZaisen.push_back(aZaisen);
		Zaisen aZaisenNoDisplay(0,
			iDgrXPosRelease,
			shiftDgrXPos(iDgrXPosHatsuTemp, iDgrXPosRelease),
			strOperationNumber);
		contZaisenNoDisplay.push_back(aZaisenNoDisplay);
		iHatsuOperation = 4;

		int iDgrXPosOuter = shiftDgrXPos(iDgrXPosHatsuTemp, iDgrXPosRelease) + 120;
		if (m_DgrXZone.getEndPos() < iDgrXPosOuter)
		{
			m_DgrXZone.setBeginEndPos(m_DgrXZone.getPos(), iDgrXPosOuter);
		}
	}
	else if (pLastOperation->getAOperation() == CentDedAfterOperation::EAOperation::AOperation_Junction)
	{
		int iDgrXPosJunction = INT_MIN;

		if (pLastOperation->getJunctionSucceed() &&
			getCentDedDgrDia()->getEnableOperation() > 0)
		{
			iHatsuOperation = 5;
			iDgrXPosTerminal = pLastOperation->getJunctionJikoku().getTotalSeconds();

			iDgrXPosJunction = shiftDgrXPos(pLastOperation->getJunctionJikoku().getTotalSeconds(), iDgrXPosRelease);
		}
		else if (!pLastOperation->getTerminalJikoku().isNull())
		{
			iDgrXPosTerminal = pLastOperation->getTerminalJikoku().getTotalSeconds();

			iDgrXPosJunction = shiftDgrXPos(pLastOperation->getTerminalJikoku().getTotalSeconds(), iDgrXPosRelease);
		}
		else if ((iDgrXPosTerminal - iDgrXPosChaku) < 60)
		{
			iDgrXPosTerminal = iDgrXPosChaku + 60;

			iDgrXPosJunction = shiftDgrXPos(iDgrXPosChaku + 60, iDgrXPosRelease);
		}

		Zaisen aZaisen(iRessyaTrack,
			shiftDgrXPos(iDgrXPosChaku, iDgrXPosRelease),
			shiftDgrXPos(iDgrXPosTerminal, iDgrXPosRelease));
		contZaisen.push_back(aZaisen);
		if (bParentIsMain)
		{
			Zaisen aZaisenNoDisplay(0,
				iDgrXPosRelease,
				iDgrXPosRelease);
			contZaisenNoDisplay.push_back(aZaisenNoDisplay);
		}

		if (iDgrXPosJunction != INT_MIN && m_DgrXZone.getEndPos() < iDgrXPosJunction)
		{
			m_DgrXZone.setBeginEndPos(m_DgrXZone.getPos(), iDgrXPosJunction);
		}
	}

	/**
		Zaisenコンテナが完成したら、RessyaTrackLine形式に仕立てる。
		分岐・環状線で関係する駅全ての分を、ここで生成します。
		iPosition:-1
			単独駅、自駅分の生成のみを行う
		iPosition:INT_MIN
			起点側派生駅、この駅では在線表表示はありません
			自駅と基幹駅群で生成を行います。
		iPosition:0-
			基幹駅・起点駅・終点駅
			自駅を含む基幹駅群で生成を行います。
		iPosition:INT_MAX
			終点側派生駅、この駅では在線表表示はありません
			自駅と基幹駅群で生成を行います。
	*/
	deque<int> iEkiOrderBrunchOriginSide;
	deque<int> iEkiOrderLoop;
	deque<int> iEkiOrderBrunchTerminalSide;
	int iPosition = pCentDedEkiCont->getEkiOrderBrunchLoop(
		iEkiOrder,
		getRessyahoukou(),
		iEkiOrderBrunchOriginSide,
		iEkiOrderLoop,
		iEkiOrderBrunchTerminalSide);
	CentDedDgrEkiCont::CdDedDgrEki aEki = pMuCdDedDgrEki->get(iEkiOrder);
	if (iPosition == -1 )
	{
		if (aEki.getDiagramTrackDisplay())
		{
			CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
				iEkiOrder,
				iTsuukaTeisya,
				2,
				iHatsuOperation,
				true);
			aCentDedDgrRessyaTrackLine.setZaisen(contZaisen);
			if (iHatsuOperation == 4)
			{
				aCentDedDgrRessyaTrackLine.setOuterEkiIndex(iOuterEkiIndex);
			}
			m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
		}
		else if (bParentIsMain)
		{
			CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
				iEkiOrder,
				iTsuukaTeisya,
				2,
				iHatsuOperation,
				false);
			aCentDedDgrRessyaTrackLine.setZaisen(contZaisenNoDisplay);
			if (iHatsuOperation == 4)
			{
				aCentDedDgrRessyaTrackLine.setOuterEkiIndex(iOuterEkiIndex);
			}
			m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
		}
		else if (contZaisenNoDisplay.size() > 0)
		{
			CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
				iEkiOrder,
				iTsuukaTeisya,
				0,
				iHatsuOperation,
				false);
			aCentDedDgrRessyaTrackLine.setZaisen(contZaisenNoDisplay);
			if (iHatsuOperation == 4)
			{
				aCentDedDgrRessyaTrackLine.setOuterEkiIndex(iOuterEkiIndex);
			}
			m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
		}
	}
	else//if (iPosition != -1)
	{
		for (int idxo = 0; idxo < (int)iEkiOrderBrunchOriginSide.size(); idxo++)
		{
			CentDedDgrEkiCont::CdDedDgrEki aEkiOrigin = pMuCdDedDgrEki->get(iEkiOrderBrunchOriginSide[idxo]);

			if (aEkiOrigin.getDiagramTrackDisplay())
			{
				CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
					iEkiOrderBrunchOriginSide[idxo],
					iTsuukaTeisya,
					2,
					iHatsuOperation,
					true);
				aCentDedDgrRessyaTrackLine.setZaisen(contZaisen);
				if (iHatsuOperation == 4)
				{
					aCentDedDgrRessyaTrackLine.setOuterEkiIndex(iOuterEkiIndex);
				}
				m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
			}
			/**
				在線表非表示の場合、iEkiOrder == iEkiOrderBrunchOriginSide[idxo]の時のみ表示する。
			*/
			else if (iEkiOrder == iEkiOrderBrunchOriginSide[idxo] && bParentIsMain)
			{
				CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
					iEkiOrderBrunchOriginSide[idxo],
					iTsuukaTeisya,
					2,
					iHatsuOperation,
					false);
				aCentDedDgrRessyaTrackLine.setZaisen(contZaisenNoDisplay);
				if (iHatsuOperation == 4)
				{
					aCentDedDgrRessyaTrackLine.setOuterEkiIndex(iOuterEkiIndex);
				}
				m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
			}
			else if (iEkiOrder == iEkiOrderBrunchOriginSide[idxo] && contZaisenNoDisplay.size() > 0)
			{
				CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
					iEkiOrderBrunchOriginSide[idxo],
					iTsuukaTeisya,
					0,
					iHatsuOperation,
					false);
				aCentDedDgrRessyaTrackLine.setZaisen(contZaisenNoDisplay);
				if (iHatsuOperation == 4)
				{
					aCentDedDgrRessyaTrackLine.setOuterEkiIndex(iOuterEkiIndex);
				}
				m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
			}
		}

		for (int idxl = 0; idxl < (int)iEkiOrderLoop.size(); idxl++)
		{
			CentDedDgrEkiCont::CdDedDgrEki aEkiLoop = pMuCdDedDgrEki->get(iEkiOrderLoop[idxl]);
			if (aEkiLoop.getDiagramTrackDisplay())
			{
				CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
					iEkiOrderLoop[idxl],
					iTsuukaTeisya,
					2,
					iHatsuOperation,
					true);
				aCentDedDgrRessyaTrackLine.setZaisen(contZaisen);
				if (iHatsuOperation == 4)
				{
					aCentDedDgrRessyaTrackLine.setOuterEkiIndex(iOuterEkiIndex);
				}
				m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
			}
			else if (bParentIsMain)
			{
				CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
					iEkiOrderLoop[idxl],
					iTsuukaTeisya,
					2,
					iHatsuOperation,
					false);
				aCentDedDgrRessyaTrackLine.setZaisen(contZaisenNoDisplay);
				if (iHatsuOperation == 4)
				{
					aCentDedDgrRessyaTrackLine.setOuterEkiIndex(iOuterEkiIndex);
				}
				m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
			}
			else if (contZaisenNoDisplay.size() > 0)
			{
				CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
					iEkiOrderLoop[idxl],
					iTsuukaTeisya,
					0,
					iHatsuOperation,
					false);
				aCentDedDgrRessyaTrackLine.setZaisen(contZaisenNoDisplay);
				if (iHatsuOperation == 4)
				{
					aCentDedDgrRessyaTrackLine.setOuterEkiIndex(iOuterEkiIndex);
				}
				m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
			}
		}

		for (int idxt = 0; idxt < (int)iEkiOrderBrunchTerminalSide.size(); idxt++)
		{
			CentDedDgrEkiCont::CdDedDgrEki aEkiTerminal = pMuCdDedDgrEki->get(iEkiOrderBrunchTerminalSide[idxt]);

			if (aEkiTerminal.getDiagramTrackDisplay())
			{
				CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
					iEkiOrderBrunchTerminalSide[idxt],
					iTsuukaTeisya,
					2,
					iHatsuOperation,
					true);
				aCentDedDgrRessyaTrackLine.setZaisen(contZaisen);
				if (iHatsuOperation == 4)
				{
					aCentDedDgrRessyaTrackLine.setOuterEkiIndex(iOuterEkiIndex);
				}
				m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
			}
			/**
				在線表非表示の場合、iEkiOrder == iEkiOrderBrunchTerminalSide[idxt]の時のみ表示する。
			*/
			else if (iEkiOrder == iEkiOrderBrunchTerminalSide[idxt] && bParentIsMain)
			{
				CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
					iEkiOrderBrunchTerminalSide[idxt],
					iTsuukaTeisya,
					2,
					iHatsuOperation,
					false);
				aCentDedDgrRessyaTrackLine.setZaisen(contZaisenNoDisplay);
				if (iHatsuOperation == 4)
				{
					aCentDedDgrRessyaTrackLine.setOuterEkiIndex(iOuterEkiIndex);
				}
				m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
			}
			else if (iEkiOrder == iEkiOrderBrunchTerminalSide[idxt] && contZaisenNoDisplay.size() > 0)
			{
				CentDedDgrRessyaTrackLine aCentDedDgrRessyaTrackLine(
					iEkiOrderBrunchTerminalSide[idxt],
					iTsuukaTeisya,
					0,
					iHatsuOperation,
					false);
				aCentDedDgrRessyaTrackLine.setZaisen(contZaisenNoDisplay);
				if (iHatsuOperation == 4)
				{
					aCentDedDgrRessyaTrackLine.setOuterEkiIndex(iOuterEkiIndex);
				}
				m_pCentDedDgrRessyaTrackLineCont->insert(aCentDedDgrRessyaTrackLine);
			}
		}
	}
}

int CentDedDgrRessya::updateRessyasenCont_01_calcRessyasenKiten(
	int iEkiOrder,
	int* piRessyasenKitenEkiOrder)
{
	//	『列車線起点駅Order』の条件は、
	//	「着時刻・発時刻のいずれかが指定されている AND 
	//	次の『駅Order』の駅扱が『停車』か『通過』」
	Mu<CentDedDgrEkiJikoku*>*	pMuCentDedDgrEkiJikoku
		= this->getMuCentDedDgrEkiJikoku();

	for (; iEkiOrder < pMuCentDedDgrEkiJikoku->size() - 1;
		iEkiOrder++)
	{
		CentDedDgrEkiJikoku*	pEkiJikokuCurr =
			pMuCentDedDgrEkiJikoku->get(iEkiOrder);
		CentDedDgrEkiJikoku*	pEkiJikokuNext =
			pMuCentDedDgrEkiJikoku->get(iEkiOrder + 1);

		int iDgrXPosHatsu = pEkiJikokuCurr->getDgrXPosHatsu(true);
		if (iDgrXPosHatsu != INT_MIN &&
			(pEkiJikokuNext->getEkiatsukai() ==
				CentDedEkiJikoku::Ekiatsukai_Teisya ||
				pEkiJikokuNext->getEkiatsukai() ==
				CentDedEkiJikoku::Ekiatsukai_Tsuuka)) {
			*piRessyasenKitenEkiOrder = iEkiOrder;
			return (0);
		}
	}
	return -1;	//	iEkiOrder 以降で、列車線起点駅がありません。
}

int CentDedDgrRessya::updateRessyasenCont_02_calcRessyasenSyuuten(
	int iRessyasenKitenEkiOrder,
	int* piRessyasenSyuutenEkiOrder)
{
	int iRv = 0;
	Mu<CentDedDgrEkiJikoku*>*	pMuCentDedDgrEkiJikoku
		= this->getMuCentDedDgrEkiJikoku();

	int iSyuuchakuEki = getSyuuchakuEki();
	int iRessyasenSyuutenEkiOrder = -1;

	//	  (1)　『列車線終点駅Order』の条件は、
	//「着時刻・発時刻の両方が指定されている」 OR
	//「 次の駅の駅扱いが『運行なし』 」 OR
	//「「『駅Order』が、その列車におけるの終着駅」 
	//	  対象駅がみつからなければ、列車線終点駅Orderの決定は失敗となります
	//  (経由なしの直前は、列車線の終点にはなりません
	//  　(この時点での列車線起点と終点は、経由なしをまたぐことがあります。)

	if (iRv >= 0)
	{
		for (int iEkiOrder = iRessyasenKitenEkiOrder + 1;
			iRessyasenSyuutenEkiOrder < 0 &&
			iEkiOrder <= iSyuuchakuEki;
			iEkiOrder++)
		{
			CentDedDgrEkiJikoku	aEkiJikokuCurr =
				*pMuCentDedDgrEkiJikoku->get(iEkiOrder);
			CentDedDgrEkiJikoku	aEkiJikokuNext;
			if (iEkiOrder + 1 < pMuCentDedDgrEkiJikoku->size())
			{
				aEkiJikokuNext =
					*pMuCentDedDgrEkiJikoku->get(iEkiOrder + 1);
			}
			//aEkijikokuCurr = iEkiOrder の駅時刻
			//aEkiJikokuNext = iEkiOder の次の駅の駅時刻。
			//	iEkiOrderが終着駅の場合は、NULLとなります。


			int jikokuChaku = aEkiJikokuCurr.getDgrXPosChaku(false);
			int	jikokuHatsu = aEkiJikokuCurr.getDgrXPosHatsu(false);
			if (jikokuChaku != INT_MIN && jikokuHatsu != INT_MIN)
			{
				//「着時刻・発時刻の両方が指定されている」 
				iRessyasenSyuutenEkiOrder = iEkiOrder;
			}
			//else if (aEkiJikokuNext.getEkiatsukai() ==
			//	CentDedEkiJikoku::Ekiatsukai_None)
			//{
			//	//	「次の駅の駅扱いが『運行なし』」  
			//	iRessyasenSyuutenEkiOrder = iEkiOrder;
			//}
			else if (iEkiOrder == iSyuuchakuEki)
			{
				//	「「『駅Order』が、その列車におけるの終着駅」 
				iRessyasenSyuutenEkiOrder = iEkiOrder;
			}
		}
		if (iRessyasenSyuutenEkiOrder < 0)
		{
			iRv = -1;	//	列車線終点が決定できません。(通常は発生しません)
		}
	}
	// iRessyasenSyuutenEkiOrder = 仮決定した列車線終点駅Order

	//	(2)　この時点で、『列車線終点駅Order』に着時刻も発時刻も
	//	設定されていない場合は、
	//	始発駅方向に向かって、着時刻・発時刻のいずれかが指定されている
	//	駅を検索します。
	//	  この結果『列車線終点駅Order』に相当する駅がない場合は、
	//	列車線終点駅Orderの決定は失敗となります。
	if (iRv >= 0)
	{
		for (; iRessyasenSyuutenEkiOrder > iRessyasenKitenEkiOrder;
			iRessyasenSyuutenEkiOrder--)
		{
			CentDedDgrEkiJikoku	aEkiJikokuCurr =
				*pMuCentDedDgrEkiJikoku->get(iRessyasenSyuutenEkiOrder);
			int jikokuChaku = aEkiJikokuCurr.getDgrXPosChaku(false);
			int	jikokuHatsu = aEkiJikokuCurr.getDgrXPosHatsu(false);
			if (jikokuChaku != INT_MIN || jikokuHatsu != INT_MIN)
			{
				//「着時刻・発時刻のどちらかが指定されている」 
				break;
			}
		}
		if (iRessyasenSyuutenEkiOrder == iRessyasenKitenEkiOrder)
		{
			iRv = -1;	//	列車線終点が決定できません。
		}
		//iRessyasenSyuutenEkiOrder = 
		//	着時刻・発時刻のいずれかが指定された、『列車線終点駅Order』
	}
	// --------------------------------
	if (iRv >= 0)
	{
		*piRessyasenSyuutenEkiOrder = iRessyasenSyuutenEkiOrder;
	}
	return (iRv);
}

int CentDedDgrRessya::updateRessyasenCont_04_adjustRessyasenSyuuten4(
	const Mu<CentDedDgrEkiCont::CdDedDgrEki>* pMuCdDedDgrEki,
	int iRessyasenKitenEkiOrder,
	int* piRessyasenSyuutenEkiOrder)
{
	int iRessyasenSyuutenEkiOrder = *piRessyasenSyuutenEkiOrder;
	// --------------------------------
	//	『主要駅』を探します。
	// --------------------------------
	Mu<CentDedDgrEkiJikoku*>*	pMuCentDedDgrEkiJikoku
		= this->getMuCentDedDgrEkiJikoku();
	for (int iEkiOrder = iRessyasenKitenEkiOrder + 1;
		iEkiOrder < iRessyasenSyuutenEkiOrder;
		iEkiOrder++)
	{
		CentDedDgrEkiCont::CdDedDgrEki aCdDedDgrEki =
			pMuCdDedDgrEki->get(iEkiOrder);
		CentDedDgrEkiJikoku aCentDedDgrEkiJikoku =
			*pMuCentDedDgrEkiJikoku->get(iEkiOrder);
		int jikokuToueki = aCentDedDgrEkiJikoku.getDgrXPosChaku(true);

		if (jikokuToueki != INT_MIN &&
			aCdDedDgrEki.getIsSyuyoueki())
		{
			//	『列車線起点駅Order』と『列車線終点駅Order』の間の
			//	途中駅で、着時刻・発時刻のいずれかが指定されている主要駅
			//	があれば、それを
			//	『列車線終点駅Order』とします。
			*piRessyasenSyuutenEkiOrder = iEkiOrder;
			return 	1;	//	『列車線終点駅Order』の補正を行いました。
		}
		if (aCentDedDgrEkiJikoku.getEkiatsukai() ==
			CentDedEkiJikoku::Ekiatsukai_Tsuuka &&
			(jikokuToueki != INT_MIN))
		{
			//「通過駅で、
			//着時刻か発時刻のいずれかが指定されている」 
			*piRessyasenSyuutenEkiOrder = iEkiOrder;
			return 	1;	//	『列車線終点駅Order』の補正を行いました。
		}


	}
	return 0;
}


int CentDedDgrRessya::updateRessyasenCont_05_adjustRessyasenSyuuten5(
	int* piRessyasenSyuutenEkiOrder)
{
	int iRv = 0;
	CentDedDgrRessyasen aCentDedDgrRessyasen
		= m_pCentDedDgrRessyasenCont->get(INT_MAX);

	for (int iEkiOrder = *piRessyasenSyuutenEkiOrder - 1;
		iRv == 0 && iEkiOrder > aCentDedDgrRessyasen.getRessyasenKitenEkiOrder();
		iEkiOrder--)
	{
		CentDedDgrEkiJikoku	aEkiJikoku = m_MuCentDedDgrEkiJikoku.get(
			iEkiOrder);

		//列車線の位置(CentDedDgrEkiJikoku::m_iDgrXPosRessyasen)と
		//着時刻・発時刻(CentDedDgrEkiJikoku::m_iDgrXPosChaku,m_iDgrXPosHatsu)の
		//差が60 秒以上ある
		//場合は、その駅を『列車線終点駅Order』とします。
		int iDgrXPosChakuHatsu = aEkiJikoku.getDgrXPosHatsu(true);
		int iDgrXPosRessyasen = aEkiJikoku.getDgrXPosRessyasen();
		if (iDgrXPosChakuHatsu != INT_MIN &&
			abs(iDgrXPosChakuHatsu - iDgrXPosRessyasen) >= 60)
		{
			*piRessyasenSyuutenEkiOrder = iEkiOrder;
			iRv = 1;	//	『列車線終点駅Order』の補正を行いました。
		}
	}
	return iRv;
}



int CentDedDgrRessya::updateRessyasenCont_06_reduceToKeiyunasi(
	int* piRessyasenSyuutenEkiOrder)
{
	int iRv = 0;
	CentDedDgrRessyasen aCentDedDgrRessyasen = m_pCentDedDgrRessyasenCont->get(
		INT_MAX);
	// --------------------------------
	//	列車線内に含まれる、
	//	運行なし(経由なし相当)の始点と終点を検索
	// --------------------------------
	int iEkiOrderBeforeKeiyunasi = INT_MIN;
	int iEkiOrderAfterKeiyunasi = INT_MIN;
	for (int iEkiOrder = aCentDedDgrRessyasen.getRessyasenKitenEkiOrder() + 1;
		iEkiOrderBeforeKeiyunasi == INT_MIN
		&& iEkiOrder < *piRessyasenSyuutenEkiOrder;
		iEkiOrder++)
	{
		CentDedDgrEkiJikoku	aEkiJikokuNext = m_MuCentDedDgrEkiJikoku.get(
			iEkiOrder + 1);

		if (aEkiJikokuNext.getEkiatsukai()
			== CentDedEkiJikoku::Ekiatsukai_None)
		{
			iEkiOrderBeforeKeiyunasi = iEkiOrder;
		}
	}
	if (iEkiOrderBeforeKeiyunasi != INT_MIN)
	{
		int iEkiOrder = 0;
		for (iEkiOrder = iEkiOrderBeforeKeiyunasi + 1;
			iEkiOrderAfterKeiyunasi == INT_MIN
			&& iEkiOrder < *piRessyasenSyuutenEkiOrder;
			iEkiOrder++)
		{
			CentDedDgrEkiJikoku	aEkiJikoku = m_MuCentDedDgrEkiJikoku.get(
				iEkiOrder);

			//駅扱が『運行なし』の終端地点を探します。
			if (aEkiJikoku.getEkiatsukai()
				!= CentDedEkiJikoku::Ekiatsukai_None)
			{
				iEkiOrderAfterKeiyunasi = iEkiOrder;
			}
		}
		//iEkiOrderAfterKeiyunasi = iEkiOrderBeforeKeiyunasi 以後で最初の
		//	「駅扱が『運行なし』以外の駅」の駅Order。
		//	但し、これが「列車線終点駅Orderの場合」は、INT_MINとなります。
	}

	//iEkiOrderBeforeKeiyunasi = 『運行なし』直前の駅Order
	//iEkiOrderAfterKeiyunasi = 『運行なし』直後の駅Order
	//	但し、「『運行なし』直後の駅Order」が
	//	「列車線終点駅Orderの場合」は、INT_MINとなります。

	if (iEkiOrderBeforeKeiyunasi != INT_MIN)
	{
		//	『運行なし』直前の駅Orderの
		//	発着時刻を、列車線上の時刻に変更します
		CentDedDgrEkiJikoku aCentDedDgrEkiJikoku =
			m_MuCentDedDgrEkiJikoku.get(iEkiOrderBeforeKeiyunasi);
		aCentDedDgrEkiJikoku.setDgrXPosChaku(
			aCentDedDgrEkiJikoku.getDgrXPosRessyasen());
		aCentDedDgrEkiJikoku.setDgrXPosHatsu(
			aCentDedDgrEkiJikoku.getDgrXPosRessyasen());
		m_MuCentDedDgrEkiJikoku.set(
			aCentDedDgrEkiJikoku, iEkiOrderBeforeKeiyunasi);

		if (iEkiOrderAfterKeiyunasi != INT_MIN)
		{
			//	『運行なし』直後の駅Orderの
			//	発着時刻を、列車線上の時刻に変更します
			CentDedDgrEkiJikoku aCentDedDgrEkiJikoku =
				m_MuCentDedDgrEkiJikoku.get(iEkiOrderAfterKeiyunasi);
			aCentDedDgrEkiJikoku.setDgrXPosChaku(
				aCentDedDgrEkiJikoku.getDgrXPosRessyasen());
			aCentDedDgrEkiJikoku.setDgrXPosHatsu(
				aCentDedDgrEkiJikoku.getDgrXPosRessyasen());
			m_MuCentDedDgrEkiJikoku.set(
				aCentDedDgrEkiJikoku, iEkiOrderAfterKeiyunasi);
		}

		//	末尾の列車線を置きかえます。
		m_pCentDedDgrRessyasenCont->erase(INT_MAX);
		aCentDedDgrRessyasen.setSyuuten(iEkiOrderBeforeKeiyunasi);
		m_pCentDedDgrRessyasenCont->insert(aCentDedDgrRessyasen);

		//駅扱が『運行なし』の駅時刻がある場合は、
		//その直前を『列車線終点駅Order』とします。
		*piRessyasenSyuutenEkiOrder = iEkiOrderBeforeKeiyunasi;

		iRv = 1;
	}
	return iRv;
}


int CentDedDgrRessya::updateRessyasenCont_07_reduceToTrackDisplay(
	const Mu<CentDedDgrEkiCont::CdDedDgrEki>* pMuCdDedDgrEki,
	int* piRessyasenSyuutenEkiOrder)
{
	int iRv = 0;
	CentDedDgrRessyasen aCentDedDgrRessyasen = m_pCentDedDgrRessyasenCont->get(
		INT_MAX);
	// --------------------------------
	//	列車線内に含まれる、
	//	在線表表示駅を検索
	// --------------------------------
	int iEkiOrderTrackDisplay = INT_MIN;
	for (int iEkiOrder = aCentDedDgrRessyasen.getRessyasenKitenEkiOrder() + 1;
		iEkiOrderTrackDisplay == INT_MIN
		&& iEkiOrder < *piRessyasenSyuutenEkiOrder;
		iEkiOrder++)
	{
		CentDedDgrEkiCont::CdDedDgrEki	aCdDedDgrEki =
			pMuCdDedDgrEki->get(iEkiOrder);
		if (aCdDedDgrEki.getDiagramTrackDisplay() > 0)
		{
			iEkiOrderTrackDisplay = iEkiOrder;
		}
	}


	if (iEkiOrderTrackDisplay != INT_MIN)
	{
		//	『在線表表示駅』の駅Orderの
		//	発着時刻を、列車線上の時刻に変更します
		CentDedDgrEkiJikoku aCentDedDgrEkiJikoku =
			m_MuCentDedDgrEkiJikoku.get(iEkiOrderTrackDisplay);
		aCentDedDgrEkiJikoku.setDgrXPosChaku(
			aCentDedDgrEkiJikoku.getDgrXPosRessyasen());
		aCentDedDgrEkiJikoku.setDgrXPosHatsu(
			aCentDedDgrEkiJikoku.getDgrXPosRessyasen());
		m_MuCentDedDgrEkiJikoku.set(
			aCentDedDgrEkiJikoku, iEkiOrderTrackDisplay);

		//	末尾の列車線を置きかえます。
		m_pCentDedDgrRessyasenCont->erase(INT_MAX);
		aCentDedDgrRessyasen.setSyuuten(iEkiOrderTrackDisplay);
		m_pCentDedDgrRessyasenCont->insert(aCentDedDgrRessyasen);

		//『在線表表示駅』の駅がある場合は、
		//『在線表表示駅』を『列車線終点駅Order』とします。
		*piRessyasenSyuutenEkiOrder = iEkiOrderTrackDisplay;

		iRv = 1;
	}
	return iRv;
}

// --------------------------------
//@name 下請関数
// --------------------------------



// ********************************
//	コンストラクタ
// ********************************
CentDedDgrRessya::CentDedDgrRessya(
	const CentDedRosen* pCentDedRosen,
	const CentDedDia* pCentDedDia,
	const CentDedDgrDia* pCentDedDgrDia,
	const CentDedRessya* pCentDedRessya,
	const bool bSimplifyRead,
	const bool bWaitOperationConnect)
	: m_bIsNull(true)
	, m_eRessyahoukou(pCentDedRessya->getRessyahoukou())
	, m_iRessyasyubetsuIndex(0)
	, m_pCentDedDgrDia(pCentDedDgrDia)
	, m_pCentDedDgrRessyasenCont(NULL)
	, m_pCentDedDgrRessyaTrackLineCont(NULL)
{
	m_pCentDedDgrRessyasenCont = new CentDedDgrRessyasenCont(
		this);
	m_pCentDedDgrRessyaTrackLineCont = new CentDedDgrRessyaTrackLineCont(
		this);

	readCentDedRessya(pCentDedRosen,
		pCentDedDia,
		pCentDedDgrDia,
		pCentDedRessya,
		bSimplifyRead,
		bWaitOperationConnect);

}

CentDedDgrRessya::CentDedDgrRessya(
	const CentDedDgrDia* pCentDedDgrDia)
	: m_bIsNull(true)
	, m_eRessyahoukou(Ressyahoukou_Kudari)
	, m_iRessyasyubetsuIndex(0)
	, m_pCentDedDgrDia(pCentDedDgrDia)
	, m_pCentDedDgrRessyasenCont(NULL)
	, m_pCentDedDgrRessyaTrackLineCont(NULL)
{
	m_pCentDedDgrRessyasenCont = new CentDedDgrRessyasenCont(
		this);
	m_pCentDedDgrRessyaTrackLineCont = new CentDedDgrRessyaTrackLineCont(
		this);
}

CentDedDgrRessya::CentDedDgrRessya(const CentDedDgrRessya& value)
	: m_bIsNull(value.m_bIsNull)
	, m_eRessyahoukou(value.m_eRessyahoukou)
	, m_iRessyasyubetsuIndex(value.m_iRessyasyubetsuIndex)
	, m_strRessyabangou(value.m_strRessyabangou)
	, m_strRessyamei(value.m_strRessyamei)
	, m_strGousuu(value.m_strGousuu)
	, m_DgrXZone(value.m_DgrXZone)
	, m_pCentDedDgrDia(value.m_pCentDedDgrDia)
	, m_MuCentDedDgrEkiJikoku(value.m_MuCentDedDgrEkiJikoku)
	, m_pCentDedDgrRessyasenCont(NULL)
	, m_pCentDedDgrRessyaTrackLineCont(NULL)
{
	m_pCentDedDgrRessyasenCont = new CentDedDgrRessyasenCont(
		this);
	m_pCentDedDgrRessyaTrackLineCont = new CentDedDgrRessyaTrackLineCont(
		this);

	*m_pCentDedDgrRessyasenCont = *value.m_pCentDedDgrRessyasenCont;
	*m_pCentDedDgrRessyaTrackLineCont = *value.m_pCentDedDgrRessyaTrackLineCont;
}


CentDedDgrRessya& CentDedDgrRessya::operator=(const CentDedDgrRessya& value)
{
	m_bIsNull = value.m_bIsNull;
	m_eRessyahoukou = value.m_eRessyahoukou;
	m_iRessyasyubetsuIndex = value.m_iRessyasyubetsuIndex;
	m_strRessyabangou = value.m_strRessyabangou;
	m_strRessyamei = value.m_strRessyamei;
	m_strGousuu = value.m_strGousuu;
	m_DgrXZone = value.m_DgrXZone;
	m_MuCentDedDgrEkiJikoku = value.m_MuCentDedDgrEkiJikoku;
	*m_pCentDedDgrRessyasenCont = *value.m_pCentDedDgrRessyasenCont;
	*m_pCentDedDgrRessyaTrackLineCont = *value.m_pCentDedDgrRessyaTrackLineCont;

	return *this;
}

CentDedDgrRessya::~CentDedDgrRessya()
{
	delete m_pCentDedDgrRessyasenCont;	m_pCentDedDgrRessyasenCont = NULL;
	delete m_pCentDedDgrRessyaTrackLineCont;	m_pCentDedDgrRessyaTrackLineCont = NULL;
}

// ********************************
//	CentDedDgrRessya
// ********************************
	// ********************************
	//@name 属性
	// ********************************
bool CentDedDgrRessya::getIsNull()const
{
	return m_bIsNull;
}
ERessyahoukou	CentDedDgrRessya::getRessyahoukou()const
{
	return m_eRessyahoukou;
}
CentDedDgrRessya& CentDedDgrRessya::setRessyahoukou(ERessyahoukou value)
{
	m_eRessyahoukou = value;
	return *this;
}

int	CentDedDgrRessya::getRessyasyubetsuIndex()const
{
	return m_iRessyasyubetsuIndex;
};
void CentDedDgrRessya::setRessyasyubetsuIndex(int value)
{
	m_iRessyasyubetsuIndex = value;
};


tstring CentDedDgrRessya::getRessyabangou()const
{
	return m_strRessyabangou;
};
CentDedDgrRessya& CentDedDgrRessya::setRessyabangou(const tstring& value)
{
	m_bIsNull = false;
	m_strRessyabangou = value;
	return *this;
};
tstring CentDedDgrRessya::getRessyamei()const
{
	return m_strRessyamei;
};
CentDedDgrRessya& CentDedDgrRessya::setRessyamei(const tstring& value)
{
	m_bIsNull = false;
	m_strRessyamei = value;
	return *this;
};
tstring CentDedDgrRessya::getGousuu()const
{
	return m_strGousuu;
};
CentDedDgrRessya& CentDedDgrRessya::setGousuu(const tstring& value)
{
	m_bIsNull = false;
	m_strGousuu = value;
	return *this;
};
CdDcdZone	CentDedDgrRessya::getDgrXZone()const
{
	return m_DgrXZone;
};

// ********************************
//@name 包含
// ********************************
Mu< CentDedDgrEkiJikoku* >*
	CentDedDgrRessya::getMuCentDedDgrEkiJikoku()
{
	return m_MuCentDedDgrEkiJikoku.getMuPtr();
}
const Mu< const CentDedDgrEkiJikoku* >*
	CentDedDgrRessya::getMuCentDedDgrEkiJikoku()const
{
	return m_MuCentDedDgrEkiJikoku.getMuPtr();
}

Mu< CentDedDgrRessyasen* >* CentDedDgrRessya::
	getCentDedDgrRessyasenCont()
{
	return m_pCentDedDgrRessyasenCont->getMuPtr();
}
const Mu< const CentDedDgrRessyasen* >* CentDedDgrRessya::
	getCentDedDgrRessyasenCont()const
{
	return ((const CentDedDgrRessyasenCont*)m_pCentDedDgrRessyasenCont)->getMuPtr();
}

Mu< CentDedDgrRessyaTrackLine* >* CentDedDgrRessya::
	getCentDedDgrRessyaTrackLineCont()
{
	return m_pCentDedDgrRessyaTrackLineCont->getMuPtr();
}
const Mu< const CentDedDgrRessyaTrackLine* >* CentDedDgrRessya::
	getCentDedDgrRessyaTrackLineCont()const
{
	return ((const CentDedDgrRessyaTrackLineCont*)m_pCentDedDgrRessyaTrackLineCont)->getMuPtr();
}


// ********************************
//@name 操作
// ********************************
void CentDedDgrRessya::clear()
{
	m_bIsNull = NULL;
	m_eRessyahoukou = Ressyahoukou_Kudari;
	m_iRessyasyubetsuIndex = 0;
	m_strRessyabangou.erase();
	m_strRessyamei.erase();
	m_strGousuu.erase();
	m_DgrXZone.setPos(0).setSize(0);
	m_MuCentDedDgrEkiJikoku.erase(0, INT_MAX);
	m_pCentDedDgrRessyasenCont->erase(0, INT_MAX);
	m_pCentDedDgrRessyaTrackLineCont->erase(0, INT_MAX);
}
int CentDedDgrRessya::readCentDedRessya(
	const CentDedRosen* pCentDedRosen,
	const CentDedDia* pCentDedDia,
	const CentDedDgrDia* pCentDedDgrDia,
	const CentDedRessya* pCentDedRessya,
	const bool bSimplifyRead,
	const bool bWaitOperationConnect)
{
	int iRv = 0;
	//	包含するオブジェクトを全てクリアし、NULL状態にします
	clear();

	//(01)CentDedDgrRessyaの属性のうち、CentDedRessya のみで決定する属性を設定
	readCentDedRessya_01_readProp(pCentDedRessya/*, bWaitOperationConnect*/);

	if (pCentDedRessya->isCanceled())
	{
		return (iRv);
	}

	//(02)CentDedDgrEkiJikoku を生成し、 CentDedEkiJikoku で決まる属性を決定。
	//また、始発駅作業を元に、m_zoneDgrXZahyouの更新を行います。
	readCentDedRessya_02_CreateCentDedEkiJikoku(pCentDedRessya);
	
	//(10)m_iDgrXPosNextを決定する
	//if (!bSimplifyRead && !bWaitOperationConnect &&  m_pCentDedDgrDia->getEnableOperation())
	//{
	//	readCentDedRessya_10_updateXPosNext(pCentDedDia, pCentDedRessya,
	//		pCentDedDgrDia->getCentDedDgrEkiCont()->getMuPtr(m_eRessyahoukou),
	//		pCentDedRosen->getCentDedEkiCont());
	//}

	//(03)CentDedDgrRessyaの以下の属性を、CentDedDgrEkiJikokuの属性を
	//	もとに生成。
	//	CdDcdZone	m_zoneDgrXZahyou
	//if (!bSimplifyRead)
	//{
	//	readCentDedRessya_03_updateDgrXZone();
	//}

	//(04)CentDedDgrEkijikokuの以下の属性を、CentDedDgrEki の属性をもとに決定。
	//	m_bShouldRessyajouhouDraw //列車情報をこの駅の場所に描画するなら真です。
	//CentDedDgrRessyaTrackのm_iRessyaTrackIndexが主本線の場合
	//CentDedDgrEkiを基に番線番号に変更。
	bool bRessyajouhouOmit = pCentDedRessya->getFirstOperation().getBOperation() == CentDedBeforeOperation::EBOperation::BOperation_Junction &&
		pCentDedRessya->getFirstOperation().getRessyajouhouOmit();
	readCentDedRessya_04_updateShouldRessyajouhouDraw(
		pCentDedDgrDia->getCentDedDgrEkiCont()->getMuPtr(m_eRessyahoukou),
		bRessyajouhouOmit);

	//	(05)経由なしの前後の着発時刻を補う
	readCentDedRessya_05_complementKeiyunasiSide();

	//	(06_01)長時間停車を解決
	//		(長時間停車の着時刻=なし・発時刻=あり の駅に、着時刻を補う)
	readCentDedRessya_06_complementLongStop_01(
		pCentDedDgrDia->getCentDedDgrEkiCont()->getMuPtr(m_eRessyahoukou));

	//	(06_02)長時間停車を解決
	//		(長時間停車の着時刻=あり・発時刻=なし の駅に、発時刻を補う)
	readCentDedRessya_06_complementLongStop_02(
		pCentDedDgrDia->getCentDedDgrEkiCont()->getMuPtr(m_eRessyahoukou));

	//(08)CentDedDgrRessyasenのコンテナを生成し、
	//  CentDedDgrEkijikoku::m_iDgrXPosOnRessyasen
	//を修正
	readCentDedRessya_08_updateRessyasenCont(
		pCentDedDgrDia->getCentDedDgrEkiCont()->getMuPtr(m_eRessyahoukou));

	/**
		CentDedBefore,AfterOperationContを元に、RessyaTrackLineContを生成します。
		また、終着駅作業を元に、m_zoneDgrXZahyouの更新を行います。
	*/
	readCentDedRessya_11_updateRessyaTrackLineCont(pCentDedRessya,
		pCentDedDgrDia->getCentDedDgrEkiCont()->getMuPtr(m_eRessyahoukou),
		pCentDedRosen->getCentDedEkiCont());
	return (iRv);
}

int CentDedDgrRessya::getSihatsuEki()const
{
	int	iRv = -1;
	// --------------------------------
	int iEkiOrder = 0;
	for (iEkiOrder = 0;
		iRv == -1 &&
		iEkiOrder < (int)m_MuCentDedDgrEkiJikoku.size();
		iEkiOrder++)
	{
		const CentDedDgrEkiJikoku*	pCentDedDgrEkiJikoku =
			m_MuCentDedDgrEkiJikoku.getMuPtr()->get(iEkiOrder);
		if (pCentDedDgrEkiJikoku->getEkiatsukai() !=
			CentDedEkiJikoku::Ekiatsukai_None)
		{
			iRv = iEkiOrder;
		}
	}
	// --------------------------------
	return (iRv);
}

int CentDedDgrRessya::getSyuuchakuEki()const
{
	int	iRv = -1;
	// --------------------------------
	int iEkiOrder = 0;
	for (iEkiOrder = (int)m_MuCentDedDgrEkiJikoku.size() - 1;
		iRv == -1 &&
		iEkiOrder >= 0;
		iEkiOrder--)
	{
		const CentDedDgrEkiJikoku*	pCentDedDgrEkiJikoku =
			m_MuCentDedDgrEkiJikoku.getMuPtr()->get(iEkiOrder);
		if (pCentDedDgrEkiJikoku->getEkiatsukai() !=
			CentDedEkiJikoku::Ekiatsukai_None)
		{
			iRv = iEkiOrder;
		}
	}
	// --------------------------------
	return (iRv);
}

bool CentDedDgrRessya::isRunBetweenNextEki(int iEkiOrder)const
{
	bool bRv = false;
	if (!(0 <= iEkiOrder && iEkiOrder < (int)m_MuCentDedDgrEkiJikoku.size() - 1))
	{
		bRv = false;	//	『駅Index』が不正です。
	}
	else
	{
		const CentDedDgrEkiJikoku* pEkijikoku
			= m_MuCentDedDgrEkiJikoku.getMuPtr()->get(iEkiOrder);
		const CentDedDgrEkiJikoku* pEkijikokuNext
			= m_MuCentDedDgrEkiJikoku.getMuPtr()->get(iEkiOrder + 1);
		if (
			(pEkijikoku->getEkiatsukai()
				== CentDedEkiJikoku::Ekiatsukai_Teisya
				|| pEkijikoku->getEkiatsukai()
				== CentDedEkiJikoku::Ekiatsukai_Tsuuka)
			&& (pEkijikokuNext->getEkiatsukai()
				== CentDedEkiJikoku::Ekiatsukai_Teisya
				|| pEkijikokuNext->getEkiatsukai()
				== CentDedEkiJikoku::Ekiatsukai_Tsuuka)
			)
		{
			bRv = true;
		}

	}
	return bRv;
}

int CentDedDgrRessya::calcEkikanSaisyouSec(
	const Mu<CentDedDgrEkiCont::CdDedDgrEki>* pMuCdDedDgrEki,
	int iEkiOrderBefore,
	int iEkiOrderAfter)const
{
	int iRv = 0;
	for (int iEkiOrder = iEkiOrderBefore;
		iEkiOrder < iEkiOrderAfter;
		iEkiOrder++)
	{
		if (isRunBetweenNextEki(iEkiOrder))
		{
			CentDedDgrEkiCont::CdDedDgrEki	aCdDedDgrEki =
				pMuCdDedDgrEki->get(iEkiOrder);
			iRv += aCdDedDgrEki.getEkikanSaisyouSec();
		}
	}
	return iRv;
}

int CentDedDgrRessya::calcDgrYEkikanSize(
	const Mu<CentDedDgrEkiCont::CdDedDgrEki>* pMuCdDedDgrEki,
	int iEkiOrderBefore,
	int iEkiOrderAfter)const
{
	int iRv = 0;
	for (int iEkiOrder = iEkiOrderBefore;
		iEkiOrder < iEkiOrderAfter;
		iEkiOrder++)
	{
		if (isRunBetweenNextEki(iEkiOrder))
		{
			CentDedDgrEkiCont::CdDedDgrEki	aCdDedDgrEki =
				pMuCdDedDgrEki->get(iEkiOrder);
			iRv += aCdDedDgrEki.getDgrYSizeEkikan();
		}
	}
	return iRv;
}


void CentDedDgrRessya::modifyDgrXPos(int iSeconds)
{
	int idx;
	for (idx = 0; idx < m_MuCentDedDgrEkiJikoku.size(); idx++)
	{
		CentDedDgrEkiJikoku	aCentDedDgrEkiJikoku
			= m_MuCentDedDgrEkiJikoku.get(idx);
		aCentDedDgrEkiJikoku.modifyDgrXPos(iSeconds);
		m_MuCentDedDgrEkiJikoku.set(aCentDedDgrEkiJikoku, idx);
		
	}
	for (idx = 0; idx < getCentDedDgrRessyaTrackLineCont()->size(); idx++)
	{
		getCentDedDgrRessyaTrackLineCont()->get(idx)->modifyDgrXPos(iSeconds);
	}

	{
		m_DgrXZone.setPos(m_DgrXZone.getPos() + iSeconds);
	}
}

int CentDedDgrRessya::getDgrXPosOfJikokuOrder(
	CdDedJikokuOrder aCdDedJikokuOrder,
	int* piDgrXPos)const
{
	int iRv = 0;
	int iDgrXPos = INT_MIN;

	const Mu<const CentDedDgrEkiJikoku*>* muCentDedDgrEkiJikoku = this->getMuCentDedDgrEkiJikoku();

	const CentDedDgrEkiJikoku*	pCentDedDgrEkiJikoku = muCentDedDgrEkiJikoku->get(aCdDedJikokuOrder.getEkiOrder());
	if (!(pCentDedDgrEkiJikoku->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya ||
		pCentDedDgrEkiJikoku->getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka))
	{
		iRv = -1;	//	この駅の座標を取得できません。
	}
	else if (pCentDedDgrEkiJikoku->getDgrXPosRessyasen() != INT_MIN)
	{
		//	この駅に列車線X座標がある(列車線の途中)なら、
		//	そのX座標を採用
		iDgrXPos = pCentDedDgrEkiJikoku->getDgrXPosRessyasen();
	}
	else if (aCdDedJikokuOrder.getEkiJikokuItem() == CdDedJikokuOrder::EkiJikokuItem_Chaku)
	{
		//	指定の駅時刻Orderが着時刻
		//	着時刻の座標を取得(なければ発)
		iDgrXPos = pCentDedDgrEkiJikoku->getDgrXPosChaku(true);
		if (iDgrXPos == INT_MIN)
		{
			iRv = -1;	//	この駅の座標を取得できません。
		}
	}
	else
	{
		//	指定の駅時刻Orderが発時刻
		//	発時刻の座標を取得(なければ着)
		iDgrXPos = pCentDedDgrEkiJikoku->getDgrXPosHatsu(true);
		if (iDgrXPos == INT_MIN)
		{
			iRv = -1;	//	この駅の座標を取得できません。
		}
	}
	// --------------------------------
	if (piDgrXPos != NULL)
	{
		*piDgrXPos = iDgrXPos;
	}
	return iRv;
}


int CentDedDgrRessya::getDgrXPosOfEkiOrder(
	int iEkiOrder,
	int* piDgrXPos)const
{
	int iDgrXPos = 0;
	int iRv = -1;
	if (iRv == -1)
	{
		iRv = this->getDgrXPosOfJikokuOrder(
			CdDedJikokuOrder(iEkiOrder, CdDedJikokuOrder::EkiJikokuItem_Hatsu),
			&iDgrXPos);

	}
	if (iRv == -1)
	{
		//	駅Orderの着時刻の座標を取得
		iRv = this->getDgrXPosOfJikokuOrder(
			CdDedJikokuOrder(iEkiOrder, CdDedJikokuOrder::EkiJikokuItem_Chaku),
			&iDgrXPos);

	}
	// --------------------------------
	if (piDgrXPos != NULL) {
		*piDgrXPos = iDgrXPos;
	}
	return (iRv);

	// ----------------------------------------------------------------
}

int CentDedDgrRessya::shiftDgrXPos(int iDgrXPosIn, int iDgrXPosBase, bool bShiftPrev) const
{
	int iDgrXPosTemp = iDgrXPosIn;
	if(bShiftPrev)
	{
		while (iDgrXPosTemp > iDgrXPosBase ||
			iDgrXPosTemp <= iDgrXPosBase - CdDedJikoku::TOTALSECONDS_A_DAY)
		{
			if (iDgrXPosTemp > iDgrXPosBase)
			{
				iDgrXPosTemp -= CdDedJikoku::TOTALSECONDS_A_DAY;
			}
			else
			{
				iDgrXPosTemp += CdDedJikoku::TOTALSECONDS_A_DAY;
			}
		}
	}
	else
	{
		while (iDgrXPosTemp < iDgrXPosBase ||
			iDgrXPosTemp >= iDgrXPosBase + CdDedJikoku::TOTALSECONDS_A_DAY)
		{
			if (iDgrXPosTemp < iDgrXPosBase)
			{
				iDgrXPosTemp += CdDedJikoku::TOTALSECONDS_A_DAY;
			}
			else
			{
				iDgrXPosTemp -= CdDedJikoku::TOTALSECONDS_A_DAY;
			}
		}
	}
	return iDgrXPosTemp;
}

} //namespace entDgr
