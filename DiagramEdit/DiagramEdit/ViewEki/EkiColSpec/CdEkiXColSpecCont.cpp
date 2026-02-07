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
// ****************************************************************
// $Id: CdEkiXColSpecCont.cpp 261 2016-01-23 03:59:53Z okm $
// ****************************************************************
#include "stdafx.h"
#include "CdEkiXColSpecCont.h"

namespace ViewEki{ namespace EkiColSpec{


	// ********************************
	//	コンストラクタ
	// ********************************
CdEkiXColSpecCont::CdEkiXColSpecCont( 
		const CentDedEkiCont* pCentDedEkiCont,
	bool bDisplaySettingMode)
{
	scan(pCentDedEkiCont,
		bDisplaySettingMode);
}
CdEkiXColSpecCont::CdEkiXColSpecCont() 
{
}

	// ********************************
	//@name CdEkiXColSpecc-属性
	// ********************************

	// ********************************
	//@name CWndJikokuhyou_CdXColSpecCont-操作
	// ********************************
void CdEkiXColSpecCont::scan( 
		const CentDedEkiCont* pCentDedEkiCont,
		bool bDisplaySettingMode)
{
	m_bDisplaySettingMode = bDisplaySettingMode;
}

int CdEkiXColSpecCont::size() 
{
	if (getDisplaySettingMode())
	{
		return 38;
	}
	else
	{
		return 7;
	}
}

CdEkiXColSpec CdEkiXColSpecCont::ColumnNumberToSpec( 
		int iColumnNumber ) 
{
	CdEkiXColSpec	aSpec ;
	
	//	駅Index
	if ( iColumnNumber == 0 )
	{
		aSpec.set( CdEkiXColSpec::EColumnType::ColumnType_EkiIndex ) ;
	}
	//	駅名
	else if ( iColumnNumber == 1 )
	{
		aSpec.set( CdEkiXColSpec::EColumnType::ColumnType_Ekimei) ;
	}
	//	駅時刻形式
	else if ( iColumnNumber == 2 )
	{
		aSpec.set( CdEkiXColSpec::EColumnType::ColumnType_Ekijikokukeisiki) ;
	}
	//	駅規模
	else if (iColumnNumber == 3)
	{
		aSpec.set(CdEkiXColSpec::EColumnType::ColumnType_Ekikibo);
	}
	//	番線数
	else if (iColumnNumber == 4)
	{
		aSpec.set(CdEkiXColSpec::EColumnType::ColumnType_EkiTrack2Count);
	}
	else if (getDisplaySettingMode())
	{
		//	起点側下り増結上り解結作業欄
		if (iColumnNumber == 5)
		{
			aSpec.set(CdEkiXColSpec::EColumnType::ColumnType_OperationOriginDownBeforeUpAfter);
		}
		//	前後作業欄(起点側)
		else if (iColumnNumber == 6)
		{
			aSpec.set(CdEkiXColSpec::EColumnType::ColumnType_OperationOrigin);
		}
		//	起点側下り解結上り増結作業欄
		else if (iColumnNumber == 7)
		{
			aSpec.set(CdEkiXColSpec::EColumnType::ColumnType_OperationOriginDownAfterUpBefore);
		}
		//	終点側下り増結上り解結作業欄
		else if (iColumnNumber == 8)
		{
			aSpec.set(CdEkiXColSpec::EColumnType::ColumnType_OperationTerminalDownBeforeUpAfter);
		}
		//	前後作業欄(終点側)
		else if (iColumnNumber == 9)
		{
			aSpec.set(CdEkiXColSpec::EColumnType::ColumnType_OperationTerminal);
		}
		//	終点側下り解結上り増結作業欄
		else if (iColumnNumber == 10)
		{
			aSpec.set(CdEkiXColSpec::EColumnType::ColumnType_OperationTerminalDownAfterUpBefore);
		}
		//	番線表示省略設定
		else if (iColumnNumber == 11)
		{
			aSpec.set(CdEkiXColSpec::EColumnType::ColumnType_TrackOmit);
		}
		//	下りカスタマイズ時刻表ビューでの着時刻表示設定
		else if (iColumnNumber == 12)
		{
			aSpec.set(CdEkiXColSpec::EColumnType::ColumnType_ChakuJikokuDisplayKudari);
		}
		//	下りカスタマイズ時刻表ビューでの発着番線表示設定
		else if (iColumnNumber == 13)
		{
			aSpec.set(CdEkiXColSpec::EColumnType::ColumnType_TrackDisplayKudari);
		}
		//	 下りカスタマイズ時刻表ビューでの発時刻表示設定
		else if (iColumnNumber == 14)
		{
			aSpec.set(CdEkiXColSpec::EColumnType::ColumnType_HatsuJikokuDisplayKudari);
		}
		//	下りカスタマイズ時刻表ビューでの列車番号表示設定
		else if (iColumnNumber == 15)
		{
			aSpec.set(CdEkiXColSpec::EColumnType::ColumnType_RessyabangouDisplayKudari);
		}
		//	下りカスタマイズ時刻表ビューでの運用番号表示設定
		else if (iColumnNumber == 16)
		{
			aSpec.set(CdEkiXColSpec::EColumnType::ColumnType_OperationNumberDisplayKudari);
		}
		//	下りカスタマイズ時刻表ビューでの運用番号表示段数設定
		else if (iColumnNumber == 17)
		{
			aSpec.set(CdEkiXColSpec::EColumnType::ColumnType_OperationNumberDisplayRowsKudari);
		}
		//	下りカスタマイズ時刻表ビューでの列車種別表示設定
		else if (iColumnNumber == 18)
		{
			aSpec.set(CdEkiXColSpec::EColumnType::ColumnType_RessyaSyubetsuDisplayKudari);
		}
		//	下りカスタマイズ時刻表ビューでの列車名・号数表示設定
		else if (iColumnNumber == 19)
		{
			aSpec.set(CdEkiXColSpec::EColumnType::ColumnType_RessyameiDisplayKudari);
		}
		//	下りカスタマイズ時刻表ビューでの路線外・前列車始発駅表示設定
		else if (iColumnNumber == 20)
		{
			aSpec.set(CdEkiXColSpec::EColumnType::ColumnType_OuterSihatsuDisplayKudari);
		}
		//	下りカスタマイズ時刻表ビューでの路線外・次列車終着駅表示設定
		else if (iColumnNumber == 21)
		{
			aSpec.set(CdEkiXColSpec::EColumnType::ColumnType_OuterShuchakuDisplayKudari);
		}
		//	上りカスタマイズ時刻表ビューでの着時刻表示設定 
		else if (iColumnNumber == 22)
		{
			aSpec.set(CdEkiXColSpec::EColumnType::ColumnType_ChakuJikokuDisplayNobori);
		}
		//	上りカスタマイズ時刻表ビューでの発着番線表示設定
		else if (iColumnNumber == 23)
		{
			aSpec.set(CdEkiXColSpec::EColumnType::ColumnType_TrackDisplayNobori);
		}
		//	上りカスタマイズ時刻表ビューでの発時刻表示設定
		else if (iColumnNumber == 24)
		{
			aSpec.set(CdEkiXColSpec::EColumnType::ColumnType_HatsuJikokuDisplayNobori);
		}
		//	上りカスタマイズ時刻表ビューでの列車番号表示設定
		else if (iColumnNumber == 25)
		{
			aSpec.set(CdEkiXColSpec::EColumnType::ColumnType_RessyabangouDisplayNobori);
		}
		//	上りカスタマイズ時刻表ビューでの運用番号表示設定
		else if (iColumnNumber == 26)
		{
			aSpec.set(CdEkiXColSpec::EColumnType::ColumnType_OperationNumberDisplayNobori);
		}
		//	上りカスタマイズ時刻表ビューでの運用番号表示段数設定
		else if (iColumnNumber == 27)
		{
			aSpec.set(CdEkiXColSpec::EColumnType::ColumnType_OperationNumberDisplayRowsNobori);
		}
		//	上りカスタマイズ時刻表ビューでの列車種別表示設定
		else if (iColumnNumber == 28)
		{
			aSpec.set(CdEkiXColSpec::EColumnType::ColumnType_RessyaSyubetsuDisplayNobori);
		}
		//	上りカスタマイズ時刻表ビューでの列車名・号数表示設定
		else if (iColumnNumber == 29)
		{
			aSpec.set(CdEkiXColSpec::EColumnType::ColumnType_RessyameiDisplayNobori);
		}
		//	上りカスタマイズ時刻表ビューでの路線外・前列車始発駅表示設定
		else if (iColumnNumber == 30)
		{
			aSpec.set(CdEkiXColSpec::EColumnType::ColumnType_OuterSihatsuDisplayNobori);
		}
		//	上りカスタマイズ時刻表ビューでの路線外・次列車終着駅表示設定
		else if (iColumnNumber == 31)
		{
			aSpec.set(CdEkiXColSpec::EColumnType::ColumnType_OuterShuchakuDisplayNobori);
		}
		//	ダイヤグラムビューでの在線表表示設定
		else if (iColumnNumber == 32)
		{
			aSpec.set(CdEkiXColSpec::EColumnType::ColumnType_DiagramTrackDisplay);
		}
		//	ダイヤグラム列車情報表示（下り）
		else if (iColumnNumber == 33)
		{
			aSpec.set(CdEkiXColSpec::EColumnType::ColumnType_DiagramRessyajouhouHyoujiKudari);
		}
		//	ダイヤグラム列車情報表示（上り）
		else if (iColumnNumber == 34)
		{
			aSpec.set(CdEkiXColSpec::EColumnType::ColumnType_DiagramRessyajouhouHyoujiNobori);
		}
		//	この駅から次の駅までの距離
		else if (iColumnNumber == 35)
		{
			aSpec.set(CdEkiXColSpec::EColumnType::ColumnType_NextEkiDistance);
		}
		//	この駅から次の駅までの背景色設定
		else if (iColumnNumber == 36)
		{
			aSpec.set(CdEkiXColSpec::EColumnType::ColumnType_DiagramColorNextEki);
		}
		//	箱ダイヤで表示するか否か
		else if (iColumnNumber == 37)
		{
			aSpec.set(CdEkiXColSpec::EColumnType::ColumnType_OperationTableDisplayJikoku);
		}

	}
	else
	{
		//	分岐駅設定
		if (iColumnNumber == 5)
		{
		aSpec.set(CdEkiXColSpec::EColumnType::ColumnType_EkiBrunch);
		}
		//	環状線設定
		else if (iColumnNumber == 6)
		{
		aSpec.set(CdEkiXColSpec::EColumnType::ColumnType_EkiLoop);
		}
	}
	return aSpec ;
}

int CdEkiXColSpecCont::ColumnNumberFromSpec( 
		const CdEkiXColSpec& aSpec ) 
{
	int iColumnNumber= -1 ;
	//	駅Index
	if ( aSpec.getColumnType() == 
		CdEkiXColSpec::EColumnType::ColumnType_EkiIndex)
	{
		iColumnNumber = 0 ;
	}
	//	駅名
	else if ( aSpec.getColumnType() == 
		CdEkiXColSpec::EColumnType::ColumnType_Ekimei)
	{
		iColumnNumber = 1 ;
	}
	//	駅時刻形式
	else if ( aSpec.getColumnType() == 
		CdEkiXColSpec::EColumnType::ColumnType_Ekijikokukeisiki)
	{
		iColumnNumber = 2 ;
	}
	//	駅規模
	else if (aSpec.getColumnType() ==
		CdEkiXColSpec::EColumnType::ColumnType_Ekikibo)
	{
		iColumnNumber = 3;
	}
	//	番線数
	else if (aSpec.getColumnType() ==
		CdEkiXColSpec::EColumnType::ColumnType_EkiTrack2Count)
	{
		iColumnNumber = 4;
	}
	else if (getDisplaySettingMode())
	{
		//	起点側下り増結上り解結作業欄
		if (aSpec.getColumnType() ==
			CdEkiXColSpec::EColumnType::ColumnType_OperationOriginDownBeforeUpAfter)
		{
			iColumnNumber = 5;
		}
		//	前後作業欄(起点側)
		else if (aSpec.getColumnType() ==
			CdEkiXColSpec::EColumnType::ColumnType_OperationOrigin)
		{
			iColumnNumber = 6;
		}
		//	起点側下り解結上り増結解結作業欄
		else if (aSpec.getColumnType() ==
			CdEkiXColSpec::EColumnType::ColumnType_OperationOriginDownAfterUpBefore)
		{
			iColumnNumber = 7;
		}
		//	終点側下り増結上り解結作業欄
		else if (aSpec.getColumnType() ==
			CdEkiXColSpec::EColumnType::ColumnType_OperationTerminalDownBeforeUpAfter)
		{
			iColumnNumber = 8;
		}
		//	前後作業欄(終点側)
		else if (aSpec.getColumnType() ==
			CdEkiXColSpec::EColumnType::ColumnType_OperationTerminal)
		{
			iColumnNumber = 9;
		}
		//	終点側下り解結上り増結作業欄
		else if (aSpec.getColumnType() ==
			CdEkiXColSpec::EColumnType::ColumnType_OperationTerminalDownAfterUpBefore)
		{
			iColumnNumber = 10;
		}
		//	番線表示省略設定
		else if (aSpec.getColumnType() ==
			CdEkiXColSpec::EColumnType::ColumnType_TrackOmit)
		{
			iColumnNumber = 11;
		}
		//	下りカスタマイズ時刻表ビューでの着時刻表示設定
		else if (aSpec.getColumnType() ==
			CdEkiXColSpec::EColumnType::ColumnType_ChakuJikokuDisplayKudari)
		{
			iColumnNumber = 12;
		}
		//	下りカスタマイズ時刻表ビューでの発着番線表示設定
		else if (aSpec.getColumnType() ==
			CdEkiXColSpec::EColumnType::ColumnType_TrackDisplayKudari)
		{
			iColumnNumber = 13;
		}
		//	下りカスタマイズ時刻表ビューでの発時刻表示設定
		else if (aSpec.getColumnType() ==
			CdEkiXColSpec::EColumnType::ColumnType_HatsuJikokuDisplayKudari)
		{
			iColumnNumber = 14;
		}
		//	下りカスタマイズ時刻表ビューでの列車番号表示設定
		else if (aSpec.getColumnType() ==
			CdEkiXColSpec::EColumnType::ColumnType_RessyabangouDisplayKudari)
		{
			iColumnNumber = 15;
		}
		//	下りカスタマイズ時刻表ビューでの運用番号表示設定
		else if (aSpec.getColumnType() ==
			CdEkiXColSpec::EColumnType::ColumnType_OperationNumberDisplayKudari)
		{
			iColumnNumber = 16;
		}
		//	下りカスタマイズ時刻表ビューでの運用番号表示段数設定
		else if (aSpec.getColumnType() ==
			CdEkiXColSpec::EColumnType::ColumnType_OperationNumberDisplayRowsKudari)
		{
			iColumnNumber = 17;
		}
		//	下りカスタマイズ時刻表ビューでの列車種別表示設定
		else if (aSpec.getColumnType() ==
			CdEkiXColSpec::EColumnType::ColumnType_RessyaSyubetsuDisplayKudari)
		{
			iColumnNumber = 18;
		}
		//	下りカスタマイズ時刻表ビューでの列車名・号数表示設定
		else if (aSpec.getColumnType() ==
			CdEkiXColSpec::EColumnType::ColumnType_RessyameiDisplayKudari)
		{
			iColumnNumber = 19;
		}
		//	下りカスタマイズ時刻表ビューでの路線外・前列車始発駅表示設定
		else if (aSpec.getColumnType() ==
			CdEkiXColSpec::EColumnType::ColumnType_OuterSihatsuDisplayKudari)
		{
			iColumnNumber = 20;
		}
		//	下りカスタマイズ時刻表ビューでの路線外・次列車終着駅表示設定
		else if (aSpec.getColumnType() ==
			CdEkiXColSpec::EColumnType::ColumnType_OuterShuchakuDisplayKudari)
		{
			iColumnNumber = 21;
		}
		//	上りカスタマイズ時刻表ビューでの着時刻表示設定
		else if (aSpec.getColumnType() ==
			CdEkiXColSpec::EColumnType::ColumnType_ChakuJikokuDisplayNobori)
		{
			iColumnNumber = 22;
		}
		//	上りカスタマイズ時刻表ビューでの発着番線表示設定
		else if (aSpec.getColumnType() ==
			CdEkiXColSpec::EColumnType::ColumnType_TrackDisplayNobori)
		{
			iColumnNumber = 23;
		}
		//	上りカスタマイズ時刻表ビューでの発時刻表示設定
		else if (aSpec.getColumnType() ==
			CdEkiXColSpec::EColumnType::ColumnType_HatsuJikokuDisplayNobori)
		{
			iColumnNumber = 24;
		}
		//	上りカスタマイズ時刻表ビューでの列車番号表示設定
		else if (aSpec.getColumnType() ==
			CdEkiXColSpec::EColumnType::ColumnType_RessyabangouDisplayNobori)
		{
			iColumnNumber = 25;
		}
		//	上りカスタマイズ時刻表ビューでの運用番号表示設定
		else if (aSpec.getColumnType() ==
			CdEkiXColSpec::EColumnType::ColumnType_OperationNumberDisplayNobori)
		{
			iColumnNumber = 26;
		}
		//	上りカスタマイズ時刻表ビューでの運用番号表示段数設定
		else if (aSpec.getColumnType() ==
			CdEkiXColSpec::EColumnType::ColumnType_OperationNumberDisplayRowsNobori)
		{
			iColumnNumber = 27;
		}
		//	上りカスタマイズ時刻表ビューでの列車種別表示設定
		else if (aSpec.getColumnType() ==
			CdEkiXColSpec::EColumnType::ColumnType_RessyaSyubetsuDisplayNobori)
		{
			iColumnNumber = 28;
		}
		//	上りカスタマイズ時刻表ビューでの列車名・号数表示設定
		else if (aSpec.getColumnType() ==
			CdEkiXColSpec::EColumnType::ColumnType_RessyameiDisplayNobori)
		{
			iColumnNumber = 29;
		}
		//	上りカスタマイズ時刻表ビューでの路線外・前列車始発駅表示設定
		else if (aSpec.getColumnType() ==
			CdEkiXColSpec::EColumnType::ColumnType_OuterSihatsuDisplayNobori)
		{
			iColumnNumber = 30;
		}
		//	上りカスタマイズ時刻表ビューでの路線外・次列車終着駅表示設定
		else if (aSpec.getColumnType() ==
			CdEkiXColSpec::EColumnType::ColumnType_OuterShuchakuDisplayNobori)
		{
			iColumnNumber = 31;
		}
		//	ダイヤグラムビューでの在線表表示設定
		else if (aSpec.getColumnType() ==
			CdEkiXColSpec::EColumnType::ColumnType_DiagramTrackDisplay)
		{
			iColumnNumber = 32;
		}
		//	ダイヤグラム列車情報表示（下り）
		else if (aSpec.getColumnType() ==
			CdEkiXColSpec::EColumnType::ColumnType_DiagramRessyajouhouHyoujiKudari)
		{
			iColumnNumber = 33;
		}
		//	ダイヤグラム列車情報表示（上り）
		else if (aSpec.getColumnType() ==
			CdEkiXColSpec::EColumnType::ColumnType_DiagramRessyajouhouHyoujiNobori)
		{
			iColumnNumber = 34;
		}
		//	この駅から次の駅までの距離
		else if (aSpec.getColumnType() ==
			CdEkiXColSpec::EColumnType::ColumnType_NextEkiDistance)
		{
			iColumnNumber = 35;
		}
		//	この駅から次の駅までの背景色設定
		else if (aSpec.getColumnType() ==
			CdEkiXColSpec::EColumnType::ColumnType_DiagramColorNextEki)
		{
			iColumnNumber = 36;
		}
		//	箱ダイヤで表示するか否か
		else if (aSpec.getColumnType() ==
			CdEkiXColSpec::EColumnType::ColumnType_OperationTableDisplayJikoku)
		{
			iColumnNumber = 37;
		}
	}
	else
	{
		//	分岐駅設定
		if (aSpec.getColumnType() ==
			CdEkiXColSpec::EColumnType::ColumnType_EkiBrunch)
		{
			iColumnNumber = 5;
		}
		//	環状線設定
		else if (aSpec.getColumnType() ==
			CdEkiXColSpec::EColumnType::ColumnType_EkiLoop)
		{
			iColumnNumber = 6;
		}
	}
	return iColumnNumber ;
}

void CdEkiXColSpecCont::clear() 
{
	*this = CdEkiXColSpecCont() ;
};

} } //namespace EkiColSpec namespace ViewEki
