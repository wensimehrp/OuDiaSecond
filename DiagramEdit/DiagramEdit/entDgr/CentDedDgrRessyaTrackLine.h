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
//	CentDedDgrRessyaTrackLine.h
// ****************************************************************
*/
/** @file */
#ifndef  CentDedDgrRessyaTrackLine_h
#define  CentDedDgrRessyaTrackLine_h
#include <deque>
#include "Str/tstring.h"

namespace entDgr {

	// ****************************************************************
	//	CentDedDgrRessyaTrackLine
	// ****************************************************************
	/**
	@brief
	【概要】
	『ダイヤグラムエンティティクラス群』の『列車在線線』クラスです。
	『ダイヤグラム』上での『列車在線線』（在線表上の直線）
	１つを表します。

	このクラスは、『列車在線線コンテナ』 (CentDedDgrRessyaTrackLineCont) に
	包含されます。多重度は、

	『列車』 (CentDedDgrRessya):『列車在線線コンテナ』CentDedDgrRessyaTrackLineCont
	=1:1

	『列車在線線コンテナ』CentDedDgrRessyaTrackLineCont :『列車在線線』CentDedDgrRessyaTrackLine
	=1:（0以上複数）

	です。

	【使い方】

	原則では、このクラスのオブジェクトを生成するのは、
	『ダイヤグラム列車』(CentDedDgrRessya) クラスのメソッドです。
	クラスユーザーはこのクラスのオブジェクトを直接生成する用事は
	ありません。『ダイヤグラム列車』(CentDedDgrRessya) クラスによって
	生成されたオブジェクトの属性を参照するだけです。
	*/
	struct Zaisen {
		int iRessyaTrack;
		int iDgrXPosChaku;
		int iDgrXPosHatsu;
		tstring strOperationNumber;
		
		Zaisen()
			:iRessyaTrack(0)
			, iDgrXPosChaku(0)
			, iDgrXPosHatsu(0)
			, strOperationNumber(tstring())
		{}

		Zaisen(
			int iRessyaTrack,
			int iDgrXPosChaku,
			int iDgrXPosHatsu)
			:iRessyaTrack(iRessyaTrack)
			, iDgrXPosChaku(iDgrXPosChaku)
			, iDgrXPosHatsu(iDgrXPosHatsu)
			, strOperationNumber(tstring())
		{}

		Zaisen(
			int iRessyaTrack,
			int iDgrXPosChaku,
			int iDgrXPosHatsu,
			tstring strOperationNumber)
			:iRessyaTrack(iRessyaTrack)
			, iDgrXPosChaku(iDgrXPosChaku)
			, iDgrXPosHatsu(iDgrXPosHatsu)
			, strOperationNumber(strOperationNumber)
		{}

	};
	class CentDedDgrRessyaTrackLine
	{
	private:
		// ********************************
		///@name 属性
		// ********************************
		///@{
		/**
		駅Order
		在線線の描写対象駅の駅Orderです。

		既定値は-1です。これは、値が無効であることを示します。*/
		int m_iEkiOrder;

		/**
			停車・運転停車・通過
		*/
		int m_iTsuukaTeisya;

		/**
			列車の着側作業
			-5:運行あり、この駅に到着します。
				ただし、ダイヤグラムの直上の路線ではなく、分岐方向から到着します。
				加えて、分岐方向が逆方向なので、列車の発側から到着します。
				また、環状線の(列車方向に依る)起点駅なので、補助列車線の描写は行いません
			-4:運行あり、この駅に到着します。
				ただし、ダイヤグラムの直上の路線ではなく、分岐方向から到着します。
				加えて、分岐方向が逆方向なので、列車の発側から到着します。
				補助列車線も発側に描写します。
			-3:運行あり、この駅に到着します。
				ただし、環状線の(列車方向に依る)起点駅なので、補助列車線の描写は行いません
			-2:運行あり、この駅に到着します。
				ただし、ダイヤグラムの直上の路線ではなく、分岐方向から到着します
				ダイヤグラムに、補助列車線を描写します
			-1:運行あり、この駅に到着します。
			0:接続なし
			1:空き
			2:解結
			3:出区、○記号を描写します
			4:路線外始発、データ上ではこの駅始発です。
			5:前列車接続、接続方向は、m_iPrevRessyahoukouで決まります

			Ver2.06.18
			分岐駅での在線表表示可能化、及び環状線の起点・終点駅での表示変更に伴う変更
			-5:該当なし
			-4:運行あり、この駅に到着します。
				ただし、ダイヤグラムの直上の路線ではなく、分岐方向から到着します。
				加えて、分岐方向が逆方向なので、列車の発側から到着します。
				補助列車線も発側に描写します。
			-3:運行あり、この駅に到着します。
				ただし、単独駅なので、補助列車線の描写は行いません
			-2:運行あり、この駅に到着します。
				ただし、ダイヤグラムの直上の路線ではなく、分岐方向から到着します
				ダイヤグラムに、補助列車線を描写します
			-1:運行あり、この駅に到着します。
		*/
		int m_iChakuOperation;

		/**
			列車の発側作業
			-5:運行あり、この駅に出発します。
				ただし、ダイヤグラムの直上の路線ではなく、分岐方向へ発車します。
				加えて、分岐方向が逆方向なので、列車の着側から到着します。
				また、環状線の(列車方向に依る)終点駅なので、補助列車線の描写は行いません
			-4:運行あり、この駅から出発します。
				ただし、ダイヤグラムの直上の路線ではなく、分岐方向へ発車します。
				加えて、分岐方向が逆方向なので、列車の着側から到着します。
				補助列車線も着側に描写します。
			-3:運行あり、この駅から出発します。
				ただし、環状線の(列車方向に依る)終点駅なので、補助列車線の描写は行いません
			-2:運行あり、この駅から出発します。
				ただし、ダイヤグラムの直下の路線ではなく、分岐方向へ発車します
				ダイヤグラムに、補助列車線を描写します
			-1:運行あり、この駅から出発します。
			0:接続なし
			1:増結
			2:空き
			3:入区、△記号を描写します
			4:路線外終着、データ上ではこの駅止まりです。
			5:次列車接続、この場合、最後の番線の横線は描写しません。

			Ver2.06.18
			分岐駅での在線表表示可能化、及び環状線の起点・終点駅での表示変更に伴う変更
			-5:該当なし
			-4:運行あり、この駅から出発します。
				ただし、ダイヤグラムの直上の路線ではなく、分岐方向へ発車します。
				加えて、分岐方向が逆方向なので、列車の着側から到着します。
				補助列車線も着側に描写します。
			-3:運行あり、この駅から出発します。
				ただし、単独駅なので、補助列車線の描写は行いません
			-2:運行あり、この駅から出発します。
				ただし、ダイヤグラムの直下の路線ではなく、分岐方向へ発車します
				ダイヤグラムに、補助列車線を描写します
			-1:運行あり、この駅から出発します。
		*/
		int m_iHatsuOperation;
		
		/**
			補助パラメータ
			前列車方向(前列車接続)もしくは
			路線外発着駅Index(路線外発着)を格納します。
		*/
		int m_iSubParameter;

		/**
			在線表表示駅か否か
			描写での振り分けに使用します。
		*/
		bool m_bIsTrackDisplay;

		std::deque<Zaisen> m_contZaisen;
		///@}
	public:
		// ********************************
		//	コンストラクタ
		// ********************************
		/**
		@param iRessyasenKitenEkiOrder [in]
		列車線起点駅Order。
		『駅Order』で表します。
		@param iRessyasenSyuutenEkiOrder [in]
		列車線終点駅Order。
		『駅Order』で表します。
		*/
		CentDedDgrRessyaTrackLine(
			int iEkiOrder,
			int iTsuukaTeisya,
			int iChakuOperation,
			int iHatsuOperation,
			bool bIsTrackDisplay);
		CentDedDgrRessyaTrackLine();

		virtual ~CentDedDgrRessyaTrackLine();

	public:
		// ********************************
		///@name CentDedDgrRessyaTrackLine-属性
		// ********************************
		///@{
		int getEkiOrder()const
		{
			return m_iEkiOrder;
		};
		int getTsuukaTeisya()const
		{
			return m_iTsuukaTeisya;
		};

		int getChakuOperation()const
		{
			return m_iChakuOperation;
		};

		int getHatsuOperation()const
		{
			return m_iHatsuOperation;
		};

		bool getIsTrackDisplay()const
		{
			return m_bIsTrackDisplay;
		};

		void setChakuOperation(const int& value)
		{
			m_iChakuOperation = value;
		};

		void setHatsuOperation(const int& value)
		{
			 m_iHatsuOperation = value;
		};

		Zaisen getZaisen(const int& iIndex)const
		{
			if (iIndex == INT_MAX)
			{
				return m_contZaisen[getZaisenCount() - 1];
			}
			return m_contZaisen[iIndex];
		};
		int getZaisenCount()const
		{
			return (int)m_contZaisen.size();
		};
		
		void setZaisen(const deque<Zaisen>& value)
		{
			m_contZaisen = value;
		};
		void addZaisen(const Zaisen& value,const bool bPushBack)
		{
			if (bPushBack)
			{
				m_contZaisen.push_back(value);
			}
			else
			{
				m_contZaisen.push_front(value);
			}
		};

		void setPrevRessyahoukou(const int& value)
		{
			m_iSubParameter = value;
		};

		int getPrevRessyahoukou()const
		{
			return m_iSubParameter;
		};

		void setOuterEkiIndex(const int& value)
		{
			m_iSubParameter = value;
		};

		int getOuterEkiIndex()const
		{
			return m_iSubParameter;
		};
		///@}
	//public:
		// ********************************
		///@name CentDedDgrRessyaTrackLine-操作
		// ********************************
		///@{

		virtual void modifyDgrXPos(int iSeconds);

		///@}

	};


} //namespace entDgr

#endif /*CentDedDgrRessyaTrackLine_h*/
