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
#ifndef  entDed_CentDedEkiTrack2_h
#define  entDed_CentDedEkiTrack2_h

#include <string>
#include "NsMu\CChildBase.h"

namespace entDed {

	using namespace std;
	using namespace OuLib::NsMu;

class CentDedEkiTrack2 : public CChildBase
{
	typedef CChildBase	super;

	/**
	このクラスがスローする例外
	*/
	class LException
	{
	};

private:
	/**
		番線名
	*/
	tstring m_strTrackName;
	/**
		番線略称(共通or下り)
	*/
	tstring m_strTrackRyakusyou;
	/**
		番線略称(上り)
		この要素は空白も可能です。
		空白の場合、m_strTrackRyakusyouが上下両方に対応します。
	*/
	tstring m_strTrackNoboriRyakusyou;

public:
	CentDedEkiTrack2(
		const tstring& strTrackName,
		const tstring& strTrackRyakusyou,
		const tstring& strTrackNoboriRyakusyou);

	CentDedEkiTrack2();

	/**
	このオブジェクトが、親オブジェクトCentDedEkiTrack2Cont の
	子である場合で、代入元が CentDedEkiTrack2Cont::set() でエラーに
	なる場合、例外スローになります。
	@param value
	代入元
	@exception LException
	*/
	CentDedEkiTrack2& operator=(const CentDedEkiTrack2& value);

public:
	// ********************************
	///@name CParentBase-操作
	// ********************************
	///@{
	/** ○親オブジェクトの変更(setParent()):  adjust()を実行する */
	virtual void setParent(CParentBase* pParent);
	///@}

public:
	tstring getTrackName()const { return m_strTrackName; };
	CentDedEkiTrack2& setTrackName(const tstring& value);

	tstring getTrackRyakusyou()const { return m_strTrackRyakusyou; };
	CentDedEkiTrack2& setTrackRyakusyou(const tstring& value)
	{	m_strTrackRyakusyou = value; return *this; };

	tstring getTrackNoboriRyakusyou()const { return m_strTrackNoboriRyakusyou; };
	CentDedEkiTrack2& setTrackNoboriRyakusyou(const tstring& value)
	{
		m_strTrackNoboriRyakusyou = value; return *this;
	};

	tstring getTrackRyakusyou(const ERessyahoukou eRessyahoukou)const 
	{ 
		if (eRessyahoukou == Ressyahoukou_Kudari ||
			m_strTrackNoboriRyakusyou.empty())
		{
			return m_strTrackRyakusyou;
		}
		else
		{
			return m_strTrackNoboriRyakusyou;
		}
	};
	//CentDedEkiTrack2& setTrackRyakusyou(
	//	const ERessyahoukou eRessyahoukou,
	//	const tstring& value)
	//{
	//	if (eRessyahoukou == Ressyahoukou_Kudari)
	//	{
	//		m_strTrackKudariRyakusyou = value;
	//	}
	//	else
	//	{
	//		m_strTrackNoboriRyakusyou = value;
	//	}
	//	return *this;
	//};

	bool isNull()const { return m_strTrackName.empty(); };
};

}

#endif