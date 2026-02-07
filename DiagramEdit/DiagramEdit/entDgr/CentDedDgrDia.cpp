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
//	CentDedDgrDia.cpp
// ****************************************************************
*/
#include "stdafx.h"

#include "CentDedDgrEki.h"
#include "CentDedDgrRessya.h"
#include "CentDedDgrDia.h"
#include "DcdCd\Pos\CLineFunc.h"
#include "logmsg/LogMsg.h"
#include <deque>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


namespace entDgr {
using namespace std;

// ****************************************************************
//	CentDedDgrDia
// ****************************************************************
// --------------------------------
//@name readCentDedRosen() の下請関数
// --------------------------------
CentDedDgrEki::EDiagramRessyajouhouHyouji
	CentDedDgrDia::CentDedEki_to_CentDedDgrEki_EDiagramRessyajouhouHyouji(
		CentDedEki::EDiagramRessyajouhouHyouji eValue)
{
	CentDedDgrEki::EDiagramRessyajouhouHyouji eRessyajouhouHyouji =
		CentDedDgrEki::DiagramRessyajouhouHyouji_Origin;
	switch (eValue)
	{
	case CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Anytime:
		eRessyajouhouHyouji = CentDedDgrEki::DiagramRessyajouhouHyouji_Anytime;
		break;
	case CentDedEki::EDiagramRessyajouhouHyouji::DiagramRessyajouhouHyouji_Not:
		eRessyajouhouHyouji = CentDedDgrEki::DiagramRessyajouhouHyouji_Not;
		break;
	}
	return eRessyajouhouHyouji;
}

/*
	readCentDedRosen() の下請関数です。
	(1)CentDedDgrDiaの属性を設定
*/
void CentDedDgrDia::readCentDedRosen_01_updateCentDedDgrDiaProp(
	const CentDedRosen* pCentDedRosen,
	const CentDedDia* pCentDedDia)
{
	m_strName = pCentDedDia->getName();
	m_iDgrXPosMin = pCentDedRosen->getKitenJikoku().getTotalSeconds();
	m_iDgrYSizeEkikanDefault = pCentDedRosen->getDiagramDgrYZahyouKyoriDefault();
	m_iEnableOperation = pCentDedRosen->getEnableOperation();

	//パターンダイヤプレビュー機能対応
	//有効な場合は、m_iPatternDiagramPreviewCycleSecondに秒数を代入しておく
	if (pCentDedDia->getPatternDiagramPreviewEnable())
	{
		m_iPatternDiagramPreviewCycleSecond = pCentDedDia->getPatternDiagramPreviewCycleSecond();
		m_iPatternDiagramPreviewRange = pCentDedDia->getPatternDiagramPreviewRange();
	}
	else
	{
		m_iPatternDiagramPreviewCycleSecond = 0;
	}
}

void CentDedDgrDia::readCentDedRosen_02_updateEkiCont(
	const CentDedEkiCont* pCentDedEkiCont,
	//const Mu< const CentDedEki* >* pCentDedEkiCont , 
	const CentDedDia* pCentDedDia)
{
	LogMsg(_T("CentDedDgrDia::readCentDedRosen_updateEkiCont()"));

	int iRv = 0;
	// --------------------------------
	//	それまでの
	//	『ダイヤグラム駅』
	//	『ダイヤグラム列車』
	//	オブジェクトは破棄します。
	// --------------------------------
	if (iRv >= 0)
	{
		m_CentDedDgrEkiCont.erase(0, INT_MAX);
		m_CentDedDgrRessyaCont[0].erase(0, INT_MAX);
		m_CentDedDgrRessyaCont[1].erase(0, INT_MAX);
	}

	// --------------------------------
	//	各駅の『ダイヤグラム駅』
	//	オブジェクトを生成
	// --------------------------------
	int iEkiIndex = 0;
	for (iEkiIndex = 0;
		iRv >= 0 && iEkiIndex < pCentDedEkiCont->size();
		iEkiIndex++)
	{
		LogMsg(_T("\tEkiIndex[%d]%s"),
			iEkiIndex,
			pCentDedEkiCont->getMuPtr()->get(iEkiIndex)->getEkimei().c_str());

		const CentDedEki* pCentDedEki = pCentDedEkiCont->getMuPtr()->get(iEkiIndex);

		// --------------------------------
		//	下り列車の検索(終点は除く)
		// --------------------------------
		int iEkikanSaisyouSecKudari = 0;
		if (pCentDedEki->getNextEkiDistanceIsDefault())
		{
			const CentDedRessyaCont* pCentDedRessyaCont =
				pCentDedDia->getCentDedRessyaCont(Ressyahoukou_Kudari);
			int iEkiOrder = pCentDedRessyaCont->EkiOrderOfEkiIndex(iEkiIndex);
			if (0 <= iEkiOrder && iEkiOrder < pCentDedEkiCont->size() - 1)
			{
				iEkikanSaisyouSecKudari =
					pCentDedRessyaCont->findEkikanSaisyouSec(
						iEkiOrder, NULL);
			}
		}
		else
		{
			iEkikanSaisyouSecKudari = pCentDedEki->getNextEkiDistance();
		}
		// --------------------------------
		//	上り列車の検索(終点は除く)
		// --------------------------------
		int iEkikanSaisyouSecNobori = 0;

		if (pCentDedEki->getNextEkiDistanceIsDefault())
		{
			const CentDedRessyaCont* pCentDedRessyaCont =
				pCentDedDia->getCentDedRessyaCont(Ressyahoukou_Nobori);
			int iEkiOrder = pCentDedRessyaCont->EkiOrderOfEkiIndex(iEkiIndex) - 1;
			if (0 <= iEkiOrder && iEkiOrder < pCentDedEkiCont->size() - 1)
			{
				iEkikanSaisyouSecNobori =
					pCentDedRessyaCont->findEkikanSaisyouSec(
						iEkiOrder, NULL);
			}
		}
		else
		{
			iEkikanSaisyouSecNobori = pCentDedEki->getNextEkiDistance();
		}

		// --------------------------------
		LogMsg(_T("\tiEkikanSaisyouSecKudari=%d iEkikanSaisyouSecNobori=%d"),
			iEkikanSaisyouSecKudari, iEkikanSaisyouSecNobori);


		//暫定処置として、途中駅の上り・下り着時刻の場合、前後に分岐派生駅が無くても、在線表を表示する
		//Ver2.06.18 在線表仕様変更
		//発着→変わらず1
		//下り着時刻　分岐駅→1、終点駅→1、それ以外→2
		//上り着時刻　分岐駅→1、起点駅→1、それ以外→3
		int iDiagramTrackDisplay = 0;
		if (pCentDedEki->getDiagramTrackDisplay() &&
			pCentDedEki->getEkikibo() == CentDedEki::EEkikibo::Ekikibo_Syuyou)
		{
			if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku)
			{
				iDiagramTrackDisplay = 1;
			}
			else if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku)
			{
				if (pCentDedEki->getBrunchLoopPosition() != -1)
				{
					iDiagramTrackDisplay = 1;
				}
				else
				{
					iDiagramTrackDisplay = 2;
				}
			}
			else if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku)
			{
				if (pCentDedEki->getBrunchLoopPosition() != -1)
				{
					iDiagramTrackDisplay = 1;
				}
				else
				{
					iDiagramTrackDisplay = 3;
				}
			}
		}
		//iDiagramTrackIndexを、bDiagramTrackOmitを元に導出する。
		//省略される番線にはINT_MINを入れ、それ以外の番線には、0から順に番号を振る
		//もし、全ての番線が省略ならば、iDiagramTrackDisplay = 0(在線表非表示駅)とみなす、(仮措置)
		vector<int>iDiagramTrackIndex;
		int iTemp = 0;
		if (iDiagramTrackDisplay > 0)
		{
			for (int iEkiTrack2Index = 0; iEkiTrack2Index < pCentDedEki->getEkiTrack2Cont()->size(); iEkiTrack2Index++)
			{
				if (pCentDedEki->getDiagramTrackOmit(iEkiTrack2Index))
				{
					iDiagramTrackIndex.push_back(INT_MIN);
				}
				else
				{
					iDiagramTrackIndex.push_back(iTemp);
					iTemp++;
				}
			}
		}
		if (iTemp == 0)
		{
			iDiagramTrackDisplay = 0;
		}
		
		//bLoopOppositeを導出する。
		//(1)上り着駅の場合、終点方にこの駅を起点駅とする駅が存在するかを調べる、
		//	存在する場合は、駅扱いが発着の場合は、その駅(終点駅)のLoopOppositeがそのままこの駅のLoopOppositeになり、
		//	駅扱いが下り着の場合は、その駅のLoopOppositeに依らず、この駅のLoopOppositeはfalseになる。
		//(2)下り着駅の場合、LoopOppositeがそのままこの駅のLoopOppositeになる。
		//	(厳密には、この駅が終点駅であることをチェックする必要はあるが、終点駅ではない場合は、LoopOppositeがfalseなので省略可)
		//(3)それ以外の場合、LoopOppositeは常にfalseになる。発着駅で終点駅でLoopOppositeがtrueの場合でも、ここではfalseになる。
		bool bLoopOpposite = false;
		if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku)
		{
			for (int idx = iEkiIndex + 1; idx < pCentDedEkiCont->size(); idx++)
			{
				if (pCentDedEkiCont->getMuPtr()->get(idx)->getLoopOriginEkiIndex() == iEkiIndex)
				{
					if (pCentDedEkiCont->getMuPtr()->get(idx)->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_Hatsuchaku)
					{
						bLoopOpposite = pCentDedEkiCont->getMuPtr()->get(idx)->getLoopOpposite();
					}
					break;
				}
			}
		}
		else if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku)
		{
			bLoopOpposite = pCentDedEki->getLoopOpposite();
		}
		//bIncludeOppositeは、分岐・環状線設定で繋がっている駅の中に、BrunchOppositeまたはLoopOppositeが
		//Trueの駅が含まれているかどうかを示す値です。
		//導出済みのiDiagramTrackDisplayが1以上(在線表表示駅)の場合のみ有効な値です。
		//1.04.08変更　在線表非表示駅でも導出する
		bool bIncludeOpposite = false;
		deque<int> iEkiIndexBrunchOriginSide;
		deque<int> iEkiIndexLoop;
		deque<int> iEkiIndexBrunchTerminalSide;
		int iResult = pCentDedEkiCont->getEkiIndexBrunchLoop(
			iEkiIndex,
			iEkiIndexBrunchOriginSide,
			iEkiIndexLoop,
			iEkiIndexBrunchTerminalSide);
		//在線表表示駅のiResultは、-1(単独駅)と0以上のいずれかです。
		//INT_MIN、INT_MAX(派生駅)にはなりません。
		if (iResult != -1)
		{
			//iEkiIndexBrunchOriginSide及びiEkiIndexBrunchTerminalSideの駅中にBrunchOppositeがtrue
			//の駅が見つかったら、bIncludeOppositeをtrueにします。
			//一つでも見つかれば、それ以上の探索は不要です。
			for (int idxo = 0; idxo < (int)iEkiIndexBrunchOriginSide.size(); idxo++)
			{
				if (pCentDedEkiCont->getMuPtr()->get(iEkiIndexBrunchOriginSide[idxo])
					->getBrunchOpposite())
				{
					bIncludeOpposite = true;
					break;
				}
			}
			for (int idxt = 0;
				idxt < (int)iEkiIndexBrunchTerminalSide.size() && !bIncludeOpposite; idxt++)
			{
				if (pCentDedEkiCont->getMuPtr()->get(iEkiIndexBrunchTerminalSide[idxt])
					->getBrunchOpposite())
				{
					bIncludeOpposite = true;
					break;
				}
			}
			//iEkiIndexLoopに値が二つ以上あるときは、環状線があるので、
			//もっとも終点側の駅(iEkiIndexLoop.back())のLoopOppositeを確認し、
			//trueの場合はbIncludeOppositeをtrueにします。
			if (iEkiIndexLoop.size() >= 2 && !bIncludeOpposite)
			{
				if (pCentDedEkiCont->getMuPtr()->get(iEkiIndexLoop.back())
					->getLoopOpposite())
				{
					bIncludeOpposite = true;
				}
			}
			//iEkiIndexLoopに値が三つ以上あるときは、環状線が2つ以上あるので、
			//iEkiIndexLoopの2番目の駅(一番起点側の環状線の終点駅)のLoopOppositeを確認し、
			//trueの場合はbIncludeOppositeをtrueにします。
			if (iEkiIndexLoop.size() >= 3 && !bIncludeOpposite)
			{
				if (pCentDedEkiCont->getMuPtr()->get(iEkiIndexLoop[1])
					->getLoopOpposite())
				{
					bIncludeOpposite = true;
				}
			}
		}
		vector<tstring> strOuterTerminalEkimei;
		for (int idx = 0; idx < pCentDedEki->getOuterTerminalEkimeiCount(); idx++)
		{
			//strOuterTerminalEkimei.push_back(
			//	pCentDedEki->getOuterTerminalEkimei(idx));
			strOuterTerminalEkimei.push_back(
				pCentDedEki->getOuterTerminalDiaRyaku(idx,true));
		}

		CentDedDgrEki	aCentDedDgrEki(
			pCentDedEki->getEkimei(),
			pCentDedEki->getEkikibo() ==
			CentDedEki::EEkikibo::Ekikibo_Syuyou,
			iEkikanSaisyouSecKudari, iEkikanSaisyouSecNobori,
			m_iDgrYSizeEkikanDefault,
			CentDedEki_to_CentDedDgrEki_EDiagramRessyajouhouHyouji(
				pCentDedEki->getDiagramRessyajouhouHyoujiKudari()),
			CentDedEki_to_CentDedDgrEki_EDiagramRessyajouhouHyouji(
				pCentDedEki->getDiagramRessyajouhouHyoujiNobori()),
			//pCentDedEki->getDownMain(),
			//pCentDedEki->getUpMain(),
			pCentDedEki->getBrunchCoreEkiIndex(),
			pCentDedEki->getBrunchOpposite(),
			pCentDedEki->getLoopOriginEkiIndex(),
			bLoopOpposite,
			iDiagramTrackDisplay,
			iDiagramTrackIndex,
			strOuterTerminalEkimei,
			pCentDedEki->getDiagramColorNextEki(),
			pCentDedEki->getEkiTrack2Cont()
		);

		m_CentDedDgrEkiCont.insert(aCentDedDgrEki);


	}


	LogMsg(_T("CentDedDgrDia::readCentDedRosen_updateEkiCont()="));

}

void CentDedDgrDia::readCentDedRosen_06_updateEkiContForOperation(
	const Mu<const CentDedEki*>* pCentDedEkiCont,
	const CentDedDia * pCentDedDia)
{
	Mu<CentDedDgrEki*>* pCentDedDgrEkiCont = getCentDedDgrEkiCont()->getMuPtr();

	if (pCentDedDgrEkiCont->size() > 0)
	{
		if (pCentDedDgrEkiCont->get(0)->getDiagramTrackDisplay() == 0)
		{
			if (getEnableOperation() > 1)
			{
				m_iOriginExtraDisplaySpace = getDgrYSizeEkikanDefault() * 2;
			}
			else
			{
				m_iOriginExtraDisplaySpace = getDgrYSizeEkikanDefault();
			}
		}
		else if(pCentDedDgrEkiCont->get(0)->getDiagramTrackDisplay() == 1)
		{
			m_iOriginExtraDisplaySpace = getDgrYSizeEkikanDefault();
		}
		else
		{
			m_iOriginExtraDisplaySpace = 0;
		}
		if (pCentDedDgrEkiCont->get(INT_MAX)->getDiagramTrackDisplay() == 0)
		{
			if (getEnableOperation() > 1)
			{
				m_iTerminalExtraDisplaySpace = getDgrYSizeEkikanDefault() * 2;
			}
			else
			{
				m_iTerminalExtraDisplaySpace = getDgrYSizeEkikanDefault();
			}
		}
		else if (pCentDedDgrEkiCont->get(INT_MAX)->getDiagramTrackDisplay() == 1)
		{
			m_iTerminalExtraDisplaySpace = getDgrYSizeEkikanDefault();
		}
		else
		{
			m_iTerminalExtraDisplaySpace = 0;
		}
	}

	//途中駅で下り着→上り着時刻の並びの駅がある場合、どちらかが在線表表示無しなら、
	//駅間距離を、デフォルト値の2倍にします
	for (int idx = 1; idx < pCentDedDgrEkiCont->size() - 1 && getEnableOperation() > 1; idx++)
	{
		//CentDedDgrEki* pCentDedDgrEki = pCentDedDgrEkiCont->get(idx);
		//if (pCentDedDgrEki->getDiagramTrackDisplay() != 0)
		//{
		//	continue;
		//}
		const CentDedEki* pCentDedEki = pCentDedEkiCont->get(idx);
		if (pCentDedEki->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_KudariChaku)
		{
			const CentDedEki* pCentDedEkiNext = pCentDedEkiCont->get(idx + 1);
			if (pCentDedEkiNext->getEkijikokukeisiki() == CentDedEki::EEkijikokukeisiki::Jikokukeisiki_NoboriChaku)
			{
				if (!pCentDedEki->getDiagramTrackDisplay() ||
					!pCentDedEkiNext->getDiagramTrackDisplay())
				{
					pCentDedDgrEkiCont->get(idx)->setDgrYSizeEkikanDefault(getDgrYSizeEkikanDefault() * 2);
				}
			}
		}
	}
}

void CentDedDgrDia::readCentDedRosen_03_updateMuRessyasyubetsu(
	const Mu< const CentDedRessyasyubetsu* >* pMuRessyasyubetsu)
{
	// --------------------------------
	//	『列車種別』オブジェクトを破棄
	// --------------------------------
	m_MuCentDedDgrRessyasyubetsu.erase(0, INT_MAX);

	// --------------------------------
	//	『列車種別』オブジェクトを
	//	生成
	// --------------------------------
	for (int idx = 0; idx < pMuRessyasyubetsu->size(); idx++)
	{
		const CentDedRessyasyubetsu* pCentDedRessyasyubetsu =
			pMuRessyasyubetsu->get(idx);
		CentDedDgrRessyasyubetsu	aCentDedDgrRessyasyubetsu(
			pCentDedRessyasyubetsu->getJikokuhyouMojiColor(),
			pCentDedRessyasyubetsu->getCdDiagramLineStyle(),
			pCentDedRessyasyubetsu->getStopMarkDrawType(),
			pCentDedRessyasyubetsu->getParentSyubetsuIndex());
		m_MuCentDedDgrRessyasyubetsu.insert(aCentDedDgrRessyasyubetsu);
	}
}

void CentDedDgrDia::readCentDedRosen_04_updateRessyaCont(
	const CentDedRosen* pCentDedRosen,
	const CentDedDia* pCentDedDia,
	bool bSimplifyRead)
{
	LogMsg(_T("CentDedDgrDia::readCentDedRosen_updateRessyaCont()"));


	// --------------------------------
	//	各列車の『ダイヤグラム列車』オブジェクトを
	//	生成
	// --------------------------------
	for (int iRessyahoukou = Ressyahoukou_Kudari;
		iRessyahoukou <= Ressyahoukou_Nobori;
		iRessyahoukou++)

	{
		ERessyahoukou eRessyahoukou = (ERessyahoukou)iRessyahoukou;

		const CentDedRessyaCont* pCentDedRessyaCont =
			pCentDedDia->getCentDedRessyaCont(eRessyahoukou);
		const Mu<const CentDedRessya*>* pCentDedRessyaContGet =
			pCentDedDia->getCentDedRessyaCont(eRessyahoukou)->getMuPtr();

		Mui< CentDedDgrRessya >*	pCentDedDgrRessyaCont =
			getCentDedDgrRessyaCont(eRessyahoukou);

		// --------------------------------
		//	列車を一旦クリア
		// --------------------------------
		pCentDedDgrRessyaCont->erase(0, INT_MAX);

		// --------------------------------
		//	列車オブジェクトを生成・追加
		// --------------------------------
		bool bWaitOperationUpdate = pCentDedDia->getWaitOperationUpdate();
		int iSize = pCentDedRessyaContGet->size();
#pragma omp parallel for ordered schedule(dynamic) 
		for (int iRessyaIdx = 0;
			iRessyaIdx < iSize;
			iRessyaIdx++)
		{
			const CentDedRessya* pCentDedRessya = pCentDedRessyaContGet->get(iRessyaIdx);
			CentDedDgrRessya	aCentDedDgrRessya(
				pCentDedRosen, pCentDedDia,
				this, pCentDedRessya, bSimplifyRead, bWaitOperationUpdate);

#pragma omp ordered 	
			pCentDedDgrRessyaCont->insert(aCentDedDgrRessya);
		}
		if (m_iPatternDiagramPreviewCycleSecond > 0)
		{
			for (int iShiftSecond = m_iPatternDiagramPreviewCycleSecond; iShiftSecond <= m_iPatternDiagramPreviewRange; iShiftSecond += m_iPatternDiagramPreviewCycleSecond)
			{

#pragma omp parallel for ordered schedule(dynamic) 
				for (int iRessyaIdx = 0;
					iRessyaIdx < iSize;
					iRessyaIdx++)
				{
					//const CentDedRessya* pCentDedRessya = pCentDedRessyaContGet->get(iRessyaIdx);
					CentDedRessya aCentDedRessya = *pCentDedRessyaContGet->get(iRessyaIdx);
					aCentDedRessya.modifyRessyaJikoku(
						iShiftSecond,
						CdDedJikokuOrder(0, CdDedJikokuOrder::EkiJikokuItem_Chaku));
					CentDedDgrRessya	aCentDedDgrRessya(
						pCentDedRosen, pCentDedDia,
						this, &aCentDedRessya, bSimplifyRead, bWaitOperationUpdate);

#pragma omp ordered 	
					pCentDedDgrRessyaCont->insert(aCentDedDgrRessya);
				}

			}

			for (int iShiftSecond = -m_iPatternDiagramPreviewCycleSecond; iShiftSecond >= -m_iPatternDiagramPreviewRange; iShiftSecond -= m_iPatternDiagramPreviewCycleSecond)
			{

#pragma omp parallel for ordered schedule(dynamic) 
				for (int iRessyaIdx = 0;
					iRessyaIdx < iSize;
					iRessyaIdx++)
				{
					//const CentDedRessya* pCentDedRessya = pCentDedRessyaContGet->get(iRessyaIdx);
					CentDedRessya aCentDedRessya = *pCentDedRessyaContGet->get(iRessyaIdx);
					aCentDedRessya.modifyRessyaJikoku(
						iShiftSecond,
						CdDedJikokuOrder(0, CdDedJikokuOrder::EkiJikokuItem_Chaku));
					CentDedDgrRessya	aCentDedDgrRessya(
						pCentDedRosen, pCentDedDia,
						this, &aCentDedRessya, bSimplifyRead, bWaitOperationUpdate);

#pragma omp ordered 	
					pCentDedDgrRessyaCont->insert(aCentDedDgrRessya);
				}

			}
		}
	}

	LogMsg(_T("CentDedDgrDia::readCentDedRosen_updateRessyaCont()="));
}

// ********************************
//	コンストラクタ
// ********************************
CentDedDgrDia::CentDedDgrDia() :
	m_iDgrXPosMin(0),
	m_iDgrYSizeEkikanDefault(60),
	m_iOriginExtraDisplaySpace(0),
	m_iTerminalExtraDisplaySpace(0)
{
}
CentDedDgrDia::~CentDedDgrDia()
{
}

// ********************************
//	CentDedDgrDia
// ********************************


	// ********************************
	//@name 属性
	// ********************************
tstring	CentDedDgrDia::getName()const
{
	return m_strName;
};
int CentDedDgrDia::getDgrXPosMin()const
{
	return m_iDgrXPosMin;
}
CentDedDgrDia& CentDedDgrDia::setDgrXPosMin(int value)
{
	m_iDgrXPosMin = value;
	return *this;
}

int CentDedDgrDia::getDgrYSizeEkikanDefault()const
{
	return m_iDgrYSizeEkikanDefault;
}
int CentDedDgrDia::getEnableOperation() const
{
	return m_iEnableOperation;
}
int CentDedDgrDia::getOriginExtraDisplaySpace()const
{
	return m_iOriginExtraDisplaySpace;
}
int CentDedDgrDia::getTerminalExtraDisplaySpace()const
{
	return m_iTerminalExtraDisplaySpace;
}
int CentDedDgrDia::getPatternDiagramPreviewCycleSecond() const
{
	return m_iPatternDiagramPreviewCycleSecond;
}
int CentDedDgrDia::getPatternDiagramPreviewRange() const
{
	return m_iPatternDiagramPreviewRange;
}
;

// ********************************
//@name 包含
// ********************************
CentDedDgrEkiCont*	CentDedDgrDia::getCentDedDgrEkiCont()
{
	return &m_CentDedDgrEkiCont;
}
const CentDedDgrEkiCont* CentDedDgrDia::getCentDedDgrEkiCont()const
{
	return &m_CentDedDgrEkiCont;
}

Mui< CentDedDgrRessyasyubetsu >*
	CentDedDgrDia::getMuCentDedDgrRessyasyubetsu()
{
	return &m_MuCentDedDgrRessyasyubetsu;
};

const Mu< const CentDedDgrRessyasyubetsu* >*
	CentDedDgrDia::getMuCentDedDgrRessyasyubetsu()const
{
	return m_MuCentDedDgrRessyasyubetsu.getMuPtr();
};

Mui< CentDedDgrRessya >*	CentDedDgrDia::getCentDedDgrRessyaCont(
	ERessyahoukou eRessyahoukou)
{
	Mui< CentDedDgrRessya >*	pRv = NULL;
	if (eRessyahoukou == Ressyahoukou_Kudari) {
		pRv = &m_CentDedDgrRessyaCont[0];
	}
	else {
		pRv = &m_CentDedDgrRessyaCont[1];
	}
	return (pRv);
}


const Mu< const CentDedDgrRessya* >*
	CentDedDgrDia::getCentDedDgrRessyaCont(
		ERessyahoukou eRessyahoukou)const
{
	const Mu< const CentDedDgrRessya* >*	pRv = NULL;
	if (eRessyahoukou == Ressyahoukou_Kudari) {
		pRv = m_CentDedDgrRessyaCont[0].getMuPtr();
	}
	else {
		pRv = m_CentDedDgrRessyaCont[1].getMuPtr();
	}
	return (pRv);
}


// ********************************
//@name 操作
// ********************************
void CentDedDgrDia::readCentDedRosen(
	const CentDedRosen* pCentDedRosen,
	const CentDedDia* pCentDedDia,
	bool bSimplifyRead)
{
	int iRv = 0;

	//	(1)CentDedDgrDiaの属性を設定
	if (iRv >= 0)
	{
		readCentDedRosen_01_updateCentDedDgrDiaProp(
			pCentDedRosen,
			pCentDedDia);
	}
	//(2)CentDedDgrEkiを生成
	//　CentDedDgrEkiの以下の属性を、CentDedEkiの属性から生成。
	if (iRv >= 0)
	{
		readCentDedRosen_02_updateEkiCont(
			pCentDedRosen->getCentDedEkiCont()/*->getMuPtr()*/,
			pCentDedDia);
	}
	//(6)CentDedDgrEkiの調整
	//　運用機能有効時、CentDedDgrEkiの駅間距離、の属性を、CentDedEkiの属性から生成。
	//bSimplifyReadがtrueの場合は省略
	//Ver1.02.92 運用機能がOFFの場合も、路線の始終着駅のみ属性変更を行うため、条件からgetEnableOperationを削除
	if (iRv >= 0 && !bSimplifyRead)
	{
		readCentDedRosen_06_updateEkiContForOperation(
			pCentDedRosen->getCentDedEkiCont()->getMuPtr(),
			pCentDedDia);
	}
	//	(3)CentDedDgrRessyasyubetsuを生成
	if (iRv >= 0)
	{
		readCentDedRosen_03_updateMuRessyasyubetsu(
			pCentDedRosen->getCentDedRessyasyubetsuCont()->getMuPtr());
	}
	//	(4)CentDedDgrRessya,CentDedDgrEkiJikokuを生成
	if (iRv >= 0)
	{
		readCentDedRosen_04_updateRessyaCont(
			pCentDedRosen,
			pCentDedDia,
			bSimplifyRead);
	}
}

int CentDedDgrDia::EkiIndexOfEkiOrder(
	ERessyahoukou eRessyahoukou, int iEkiOrder)const
{
	int iEkiIndex = iEkiOrder;
	if (eRessyahoukou == Ressyahoukou_Nobori) {
		iEkiIndex = m_CentDedDgrEkiCont.size() - 1 - iEkiOrder;
	}
	return (iEkiIndex);
}

int CentDedDgrDia::EkiOrderOfEkiIndex(ERessyahoukou eRessyahoukou,
	int iEkiIndex)const
{
	int iEkiOrder = iEkiIndex;
	if (eRessyahoukou == Ressyahoukou_Nobori) {
		iEkiOrder = m_CentDedDgrEkiCont.size() - 1 - iEkiIndex;
	}
	return (iEkiOrder);
}

CdDcdZoneXy	CentDedDgrDia::getZone()const
{
	int iYSize = getDgrYPosOfEkiTer(INT_MAX);
	iYSize += getTerminalExtraDisplaySpace();
	if (iYSize < 0) {
		iYSize = 0;
	}
	return (CdDcdZoneXy(
		CdDcdZone(m_iDgrXPosMin, CdDedJikoku::TOTALSECONDS_A_DAY),
		CdDcdZone(0, iYSize)));
}

int CentDedDgrDia::getDgrYPosOfEkiOrg(int iEkiIndex)const
{
	int iRv = getOriginExtraDisplaySpace();
	iRv += getDgrYSizeEkikanOrg(
		Ressyahoukou_Kudari,
		0,
		iEkiIndex);
	return iRv;
}
int CentDedDgrDia::getDgrYPosOfEkiOrg(ERessyahoukou eRessyahoukou,
	int iEkiOrder)const
{
	if (eRessyahoukou == ERessyahoukou::Ressyahoukou_Kudari)
	{
		return getDgrYPosOfEkiOrg(
			EkiIndexOfEkiOrder(eRessyahoukou, iEkiOrder));
	}
	else
	{
		return getDgrYPosOfEkiTer(
			EkiIndexOfEkiOrder(eRessyahoukou, iEkiOrder));
	}
}
int CentDedDgrDia::getDgrYPosOfEkiTer(int iEkiIndex)const
{
	int iRv = getOriginExtraDisplaySpace();
	iRv += getDgrYSizeEkikanOrg(
		Ressyahoukou_Kudari,
		0,
		iEkiIndex);

	iRv = iRv + getDgrEkiTrackDisplaySpace(iEkiIndex);
	return iRv;
}
int CentDedDgrDia::getDgrYPosOfEkiTer(ERessyahoukou eRessyahoukou,
	int iEkiOrder)const
{
	if (eRessyahoukou == ERessyahoukou::Ressyahoukou_Kudari)
	{
		return getDgrYPosOfEkiTer(
			EkiIndexOfEkiOrder(eRessyahoukou, iEkiOrder));
	}
	else
	{
		return getDgrYPosOfEkiOrg(
			EkiIndexOfEkiOrder(eRessyahoukou, iEkiOrder));
	}
}
int CentDedDgrDia::getDgrYSizeEkikanOrg(
	ERessyahoukou eRessyahoukou,
	int iEkiOrderOrg,
	int iEkiOrderDst)const
{
	int iRv = 0;
	// --------------------------------
	if (iEkiOrderOrg == INT_MAX) {
		iEkiOrderOrg = m_CentDedDgrEkiCont.size() - 1;
	}
	if (iEkiOrderDst == INT_MAX) {
		iEkiOrderDst = m_CentDedDgrEkiCont.size() - 1;
	}
	// --------------------------------
	if (!(0 <= iEkiOrderOrg && iEkiOrderOrg < m_CentDedDgrEkiCont.size())) {
		return (-1);	//		『駅Order』が不正
	}
	if (!(0 <= iEkiOrderDst && iEkiOrderDst < m_CentDedDgrEkiCont.size())) {
		return (-1);	//		『駅Order』が不正
	}
	int iEkiIndexOrg = EkiIndexOfEkiOrder(eRessyahoukou, iEkiOrderOrg);
	int iEkiIndexDst = EkiIndexOfEkiOrder(eRessyahoukou, iEkiOrderDst);
	if (iEkiIndexOrg > iEkiIndexDst) {
		int i = iEkiIndexOrg;	iEkiIndexOrg = iEkiIndexDst; iEkiIndexDst = i;
	}
	// --------------------------------	
	const Mu<CentDedDgrEki>* pCentDedDgrEkiCont = getCentDedDgrEkiCont();

	int idx;
	for (idx = iEkiIndexOrg; idx < iEkiIndexDst; idx++) {
		iRv += pCentDedDgrEkiCont->get(idx).getDgrYZahyouKyoriOrg();
	}

	return (iRv);
}
int CentDedDgrDia::getDgrYSizeEkikanTer(
	ERessyahoukou eRessyahoukou,
	int iEkiOrderOrg,
	int iEkiOrderDst)const
{
	int iRv = 0;
	// --------------------------------
	if (iEkiOrderOrg == INT_MAX) {
		iEkiOrderOrg = m_CentDedDgrEkiCont.size() - 1;
	}
	if (iEkiOrderDst == INT_MAX) {
		iEkiOrderDst = m_CentDedDgrEkiCont.size() - 1;
	}
	// --------------------------------
	if (!(0 <= iEkiOrderOrg && iEkiOrderOrg < m_CentDedDgrEkiCont.size())) {
		return (-1);	//		『駅Order』が不正
	}
	if (!(0 <= iEkiOrderDst && iEkiOrderDst < m_CentDedDgrEkiCont.size())) {
		return (-1);	//		『駅Order』が不正
	}
	int iEkiIndexOrg = EkiIndexOfEkiOrder(eRessyahoukou, iEkiOrderOrg);
	int iEkiIndexDst = EkiIndexOfEkiOrder(eRessyahoukou, iEkiOrderDst);
	if (iEkiIndexOrg > iEkiIndexDst) {
		int i = iEkiIndexOrg;	iEkiIndexOrg = iEkiIndexDst; iEkiIndexDst = i;
	}
	// --------------------------------	
	const Mu<CentDedDgrEki>* pCentDedDgrEkiCont = getCentDedDgrEkiCont();

	int idx;
	for (idx = iEkiIndexOrg; idx < iEkiIndexDst; idx++) {
		if (idx == iEkiIndexOrg)
		{
			iRv += pCentDedDgrEkiCont->get(idx).getDgrYZahyouKyoriTer();
		}
		else
		{
			iRv += pCentDedDgrEkiCont->get(idx).getDgrYZahyouKyoriOrg();
		}
	}

	return (iRv);
}




int CentDedDgrDia::getDgrYPosOfEkiTrack(ERessyahoukou eRessyahoukou,
	int iEkiOrder, int iEkiTrackIndex) const
{
	int iEkiIndex = EkiIndexOfEkiOrder(eRessyahoukou, iEkiOrder);
	CentDedDgrEki aCentDedDgrEki = getCentDedDgrEkiCont()->get(iEkiIndex);
	if (aCentDedDgrEki.getDiagramTrackDisplay() == 0)
	{
		return -1;
	}
	if (iEkiTrackIndex < 0 ||
		iEkiTrackIndex >= aCentDedDgrEki.getCentDedDgrEkiTrack2Cont().size())
	{
		return -1;
	}
	if (aCentDedDgrEki.getDiagramTrackIndex(iEkiTrackIndex) == INT_MIN)
	{
		return -1;
	}
	int iRv = getDgrYPosOfEkiOrg(
		iEkiIndex);
	iRv += (aCentDedDgrEki.getDiagramTrackIndex(iEkiTrackIndex) + 1) * m_iDgrYSizeEkikanDefault;

	return iRv;
}

int CentDedDgrDia::getEkikanSaisyouSec(
	ERessyahoukou eRessyahoukou,
	int iEkiOrderOrg,
	int iEkiOrderDst)const
{
	int iRv = 0;
	// --------------------------------
	if (iEkiOrderOrg == INT_MAX) {
		iEkiOrderOrg = m_CentDedDgrEkiCont.size() - 1;
	}
	if (iEkiOrderDst == INT_MAX) {
		iEkiOrderDst = m_CentDedDgrEkiCont.size() - 1;
	}
	// --------------------------------
	if (!(0 <= iEkiOrderOrg && iEkiOrderOrg < m_CentDedDgrEkiCont.size())) {
		return (-1);	//		『駅Order』が不正
	}
	if (!(0 <= iEkiOrderDst && iEkiOrderDst < m_CentDedDgrEkiCont.size())) {
		return (-1);	//		『駅Order』が不正
	}
	int iEkiIndexOrg = EkiIndexOfEkiOrder(eRessyahoukou, iEkiOrderOrg);
	int iEkiIndexDst = EkiIndexOfEkiOrder(eRessyahoukou, iEkiOrderDst);
	if (iEkiIndexOrg > iEkiIndexDst) {
		int i = iEkiIndexOrg;	iEkiIndexOrg = iEkiIndexDst; iEkiIndexDst = i;
	}
	// --------------------------------	
	const Mu<CentDedDgrEki>* pCentDedDgrEkiCont = getCentDedDgrEkiCont();

	int idx;
	for (idx = iEkiIndexOrg; idx < iEkiIndexDst; idx++) {
		if (eRessyahoukou == Ressyahoukou_Kudari) {
			iRv += pCentDedDgrEkiCont->get(idx).getEkikanSaisyouSecKudari();
		}
		else if (eRessyahoukou == Ressyahoukou_Nobori) {
			iRv += pCentDedDgrEkiCont->get(idx).getEkikanSaisyouSecNobori();
		}
	}

	return (iRv);
}


CdDcdPosXy CentDedDgrDia::calcDgrPosRessyasenKiten(
	const CentDedDgrRessya* pCentDedDgrRessya,
	const CentDedDgrRessyasen* pCentDedDgrRessyasen,
	const int& iShiftSecond)const
{
	int iEkiOrderRessyasenKiten = pCentDedDgrRessyasen->getRessyasenKitenEkiOrder();
	CentDedDgrEkiJikoku	aEkiJikokuKiten =
		*pCentDedDgrRessya->getMuCentDedDgrEkiJikoku()->get(iEkiOrderRessyasenKiten);
	int iDgrXPosKiten = aEkiJikokuKiten.getDgrXPosHatsu(true) + iShiftSecond;
	int iDgrYPosKiten = this->getDgrYPosOfEkiTer(
		pCentDedDgrRessya->getRessyahoukou(),
		iEkiOrderRessyasenKiten);
	return CdDcdPosXy(iDgrXPosKiten, iDgrYPosKiten);
}

CdDcdPosXy CentDedDgrDia::calcDgrPosRessyasenSyuuten(
	const CentDedDgrRessya* pCentDedDgrRessya,
	const CentDedDgrRessyasen* pCentDedDgrRessyasen,
	const int& iShiftSecond)const
{
	int iEkiOrderRessyasenSyuuten = pCentDedDgrRessyasen->getRessyasenSyuutenEkiOrder();
	CentDedDgrEkiJikoku	aEkiJikokuSyuuten =
		*pCentDedDgrRessya->getMuCentDedDgrEkiJikoku()->get(iEkiOrderRessyasenSyuuten);
	int iDgrXPosSyuuten = aEkiJikokuSyuuten.getDgrXPosChaku(true) + iShiftSecond;
	int iDgrYPosSyuuten = this->getDgrYPosOfEkiOrg(
		pCentDedDgrRessya->getRessyahoukou(),
		iEkiOrderRessyasenSyuuten);
	return CdDcdPosXy(iDgrXPosSyuuten, iDgrYPosSyuuten);
}

int CentDedDgrDia::getDgrEkiTrackDisplaySpace(const int iEkiIndex) const
{
	int iEkiIndexModify = iEkiIndex;
	if (iEkiIndexModify == INT_MAX)
	{
		iEkiIndexModify = getCentDedDgrEkiCont()->size() - 1;
	}
	if (iEkiIndexModify < 0 || iEkiIndexModify >= getCentDedDgrEkiCont()->size())
	{
		return 0;
	}
	return getCentDedDgrEkiCont()->get(iEkiIndexModify).getDgrEkiTrackDisplaySpace();
}

void CentDedDgrDia::createEstimateRessya(
	const CentDedDgrRessya* pCentDedDgrRessya,
	CentDedRessya* pCentDedRessya)const
{


	CentDedRessya	aCentDedRessya(
		m_CentDedDgrEkiCont.size(),
		pCentDedDgrRessya->getRessyahoukou());

	// --------------------------------
	//	属性の設定
	// --------------------------------
	{
		aCentDedRessya.setRessyabangou(
			pCentDedDgrRessya->getRessyabangou());
		aCentDedRessya.setRessyamei(
			pCentDedDgrRessya->getRessyamei());
		aCentDedRessya.setGousuu(
			pCentDedDgrRessya->getGousuu());

	}
	// --------------------------------
	//	駅時刻の設定
	// --------------------------------
	{
		const Mu<const CentDedDgrEkiJikoku*>*	pMuCentDedDgrEkiJikoku = pCentDedDgrRessya->getMuCentDedDgrEkiJikoku();
		//const Mu<const CentDedDgrRessyaTrack*>*	pMuCentDedDgrRessyaTrack = pCentDedDgrRessya->getMuCentDedDgrRessyaTrack();
		for (int iEkiOrder = 0;
			iEkiOrder < pMuCentDedDgrEkiJikoku->size();
			iEkiOrder++)
		{
			CentDedDgrEkiJikoku	aCentDedDgrEkiJikoku = *pMuCentDedDgrEkiJikoku->get(iEkiOrder);

			CentDedEkiJikoku	aEkiJikoku = aCentDedRessya.getCentDedEkiJikoku(iEkiOrder);

			// --------------------------------
			//	駅扱を設定
			// --------------------------------
			aEkiJikoku.setEkiatsukai(aCentDedDgrEkiJikoku.getEkiatsukai());

			// --------------------------------
			//	この駅を端点とする列車線を検索
			// --------------------------------
			int idxRessyasenChaku = INT_MIN;
			int idxRessyasenHatsu = INT_MIN;
			const Mu<const CentDedDgrRessyasen*>* pMuRessyasen = pCentDedDgrRessya->getCentDedDgrRessyasenCont();
			for (int idxRessyasen = 0;
				idxRessyasen < pMuRessyasen->size();
				idxRessyasen++)
			{
				const CentDedDgrRessyasen*	pCentDedDgrRessyasen = pMuRessyasen->get(idxRessyasen);
				if (pCentDedDgrRessyasen->getRessyasenSyuutenEkiOrder() == iEkiOrder)
				{
					idxRessyasenChaku = idxRessyasen;
				}
				if (pCentDedDgrRessyasen->getRessyasenKitenEkiOrder() == iEkiOrder)
				{
					idxRessyasenHatsu = idxRessyasen;
				}
			}
			//idxRessyasenChaku = 
			//	この駅Orderが列車線終点なら、その列車線Order、そうでないならINT_MIN 
			//idxRessyasenHatsu = 
			//	この駅Orderが列車線起点なら、その列車線Order、そうでないならINT_MIN 

			// --------------------------------
			//	駅時刻を設定
			// --------------------------------
			if (idxRessyasenChaku != INT_MIN && aCentDedDgrEkiJikoku.getDgrXPosChaku(true) != INT_MIN)
			{
				//	列車線の終点なら、着時刻DgrXPosをもとに着時刻を設定
				aEkiJikoku.setChakujikoku(CdDedJikoku(aCentDedDgrEkiJikoku.getDgrXPosChaku(true)));
			}
			if (idxRessyasenHatsu != INT_MIN && aCentDedDgrEkiJikoku.getDgrXPosHatsu(true) != INT_MIN)
			{
				//	列車線の起点なら、発時刻DgrXPosをもとに発時刻を設定
				aEkiJikoku.setHatsujikoku(CdDedJikoku(aCentDedDgrEkiJikoku.getDgrXPosHatsu(true)));
			}
			if (idxRessyasenChaku == INT_MIN &&
				idxRessyasenHatsu == INT_MIN &&
				aCentDedDgrEkiJikoku.getDgrXPosRessyasen() != INT_MIN)
			{
				//	列車線起点・終点でない && 駅時刻に DgrXPosRessyasen がある場合は、
				//	DgrXPosRessyasen を着・発に設定
				aEkiJikoku.setChakujikoku(CdDedJikoku(aCentDedDgrEkiJikoku.getDgrXPosRessyasen()));
				aEkiJikoku.setHatsujikoku(CdDedJikoku(aCentDedDgrEkiJikoku.getDgrXPosRessyasen()));
			}
			// --------------------------------
			// 列車番線を設定
			// --------------------------------
			//CentDedDgrRessyaTrack	aCentDedDgrRessyaTrack = *pMuCentDedDgrRessyaTrack->get(iEkiOrder);
			aEkiJikoku.setRessyaTrackIndex(aCentDedDgrEkiJikoku.getRessyaTrackIndex());

			aCentDedRessya.setCentDedEkiJikoku(iEkiOrder, aEkiJikoku);



			//CentDedRessyaTrack	aRessyaTrack = aCentDedRessya.getCentDedRessyaTrack(iEkiOrder);
			//if (iEkiOrder == pCentDedDgrRessya->getSihatsuEki() ||
			//	iEkiOrder == pCentDedDgrRessya->getSyuuchakuEki())
			//{
			//	aRessyaTrack.setRessyaTrackIndex(aCentDedDgrRessyaTrack.getRessyaTrackIndex());
			//	aRessyaTrack.setOperation(aCentDedDgrRessyaTrack.getOperation());
			//	aRessyaTrack.setShuntTrackIndex(aCentDedDgrRessyaTrack.getShuntTrackIndex());
			//	aRessyaTrack.setOperationHatsuJikoku(aCentDedDgrRessyaTrack.getDgrXPosOperationHatsu());
			//	aRessyaTrack.setOperationChakuJikoku(aCentDedDgrRessyaTrack.getDgrXPosOperationChaku());
			//	aRessyaTrack.setOperationNumber(aCentDedDgrRessyaTrack.getOperationNumber());
			//}
			//else if (iEkiOrder > pCentDedDgrRessya->getSihatsuEki() &&
			//	iEkiOrder < pCentDedDgrRessya->getSyuuchakuEki())
			//{
			//	aRessyaTrack.setRessyaTrackIndex(aCentDedDgrRessyaTrack.getRessyaTrackIndex());
			//}
			//aCentDedRessya.setCentDedRessyaTrack(iEkiOrder, aRessyaTrack);
		}
	}
	// --------------------------------

	if (pCentDedRessya != NULL)
	{
		*pCentDedRessya = aCentDedRessya;
	}
}

void CentDedDgrDia::createEstimateRessya2(
	const CentDedDgrRessya* pCentDedDgrRessya,
	CentDedRessya* pCentDedRessya,
	const CentDedEkiCont* pCentDedEkiCont)const
{
	// --------------------------------
	CentDedRessya	aCentDedRessya(
		m_CentDedDgrEkiCont.size(),
		pCentDedDgrRessya->getRessyahoukou());
	if (pCentDedRessya == NULL)
	{
		pCentDedRessya = &aCentDedRessya;
	}
	// --------------------------------
	{
		//	推定時刻つき列車オブジェクトを生成
		createEstimateRessya(
			pCentDedDgrRessya,
			pCentDedRessya);
	}
	{
		//	駅情報にアクセスする Mu を生成
		//const Mu< CentDedDgrEkiCont::CdDedDgrEki >* muEki =	getCentDedDgrEkiCont()->getMuPtr( pCentDedRessya->getRessyahoukou())  ;


		// --------------------------------
		//	支線分岐駅の場合は、同名駅に
		//	同一駅時刻をコピーする
		//	(支線内列車のソートの精度を上げるため)
		// --------------------------------

		//	全同名駅に、駅時刻をコピーします。
		//
		//	この仕様は、A-B-C|B-D形式の支線つき路線の
		//	TransferSort(乗継ソート)の精度を上げるためのものです。
		//	B-D間列車のB駅の駅時刻を
		//	A-B-Cの間の B にも設定することにより、乗継ソートの
		//	精度が高まります。

		//{
		//	for ( int iEkiOrderSrc = 0 ; iEkiOrderSrc < muEki->size() ; iEkiOrderSrc ++ )
		//	{
		//		CentDedDgrEkiCont::CdDedDgrEki	aEkiSrc = muEki->get(iEkiOrderSrc) ;

		//		CentDedEkiJikoku	aEkiJikokuSrc = 
		//			pCentDedRessya->getCentDedEkiJikoku( iEkiOrderSrc ) ;
		//		if ( aEkiJikokuSrc.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Teisya ||
		//			aEkiJikokuSrc.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Tsuuka )
		//		{
		//			for ( int iEkiOrder = 0 ; 
		//				iEkiOrder <  muEki->size() ;
		//				iEkiOrder ++ )
		//			{
		//				if ( iEkiOrderSrc != iEkiOrder )
		//				{
		//					CentDedDgrEkiCont::CdDedDgrEki aEki = muEki->get(iEkiOrder) ;

		//					if ( aEkiSrc.getEkimei() == aEki.getEkimei() )
		//					{
		//						CentDedEkiJikoku	aEkiJikoku = 
		//							pCentDedRessya->getCentDedEkiJikoku( iEkiOrder ) ;
		//						if ( aEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_None ||
		//							aEkiJikoku.getEkiatsukai() == CentDedEkiJikoku::Ekiatsukai_Keiyunasi )
		//						{
		//							pCentDedRessya->setCentDedEkiJikoku( iEkiOrder , aEkiJikokuSrc ) ;
		//						}
		//					}
		//				}
		//			}
		//		}
		//	}
		//}

		{
			int iEkiCount = pCentDedEkiCont->size();
			deque<bool> bEkiChecked(iEkiCount, false);
			for (int ord = 0; ord < iEkiCount; ord++)
			{
				deque<int> iEkiOrderBrunchOriginSide;
				deque<int> iEkiOrderLoop;
				deque<int> iEkiOrderBrunchTerminalSide;

				if (bEkiChecked[ord])
				{
					continue;
				}
				int iResult = pCentDedEkiCont->getEkiOrderBrunchLoop(
					ord,
					pCentDedRessya->getRessyahoukou(),
					iEkiOrderBrunchOriginSide,
					iEkiOrderLoop,
					iEkiOrderBrunchTerminalSide);

				if (iResult != -1)
				{
					pCentDedRessya->adjustBrunchLoopForTransferSort(
						iEkiOrderBrunchOriginSide,
						iEkiOrderLoop,
						iEkiOrderBrunchTerminalSide);
					for (int idxo = 0; idxo < (int)iEkiOrderBrunchOriginSide.size(); idxo++)
					{
						bEkiChecked[iEkiOrderBrunchOriginSide[idxo]] = true;
					}
					for (int idxl = 0; idxl < (int)iEkiOrderLoop.size(); idxl++)
					{
						bEkiChecked[iEkiOrderLoop[idxl]] = true;
					}
					for (int idxt = 0; idxt < (int)iEkiOrderBrunchTerminalSide.size(); idxt++)
					{
						bEkiChecked[iEkiOrderBrunchTerminalSide[idxt]] = true;
					}
				}
			}
		}

	}


}
} //namespace entDgr
