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
//	CdDedDispProp.cpp
// ****************************************************************
*/
/** @file */
#include "stdafx.h"
#include "..¥DedRosenFileData¥CdDedDispProp.h"

namespace DedRosenFileData{

// ****************************************************************
//	CdDedDispProp
// ****************************************************************

	// ********************************
	//	コンストラクタ
	// ********************************
CdDedDispProp::CdDedDispProp() :
		m_fontpropJikokuhyouVFont( 9 , _T("@メイリオ") ) ,
		m_fontpropDiaEkimeiFont( 9 , _T("Meiryo UI")  ) ,
		m_fontpropDiaJikokuFont( 9 , _T("Meiryo UI")  ) ,
		m_fontpropDiaRessyaFont( 9 , _T("Meiryo UI")  ) ,
		m_fontpropOperationTableFont(9, _T("Meiryo UI")),
		m_fontpropAllOperationTableJikokuFont(8, _T("Meiryo UI")),
		m_fontpropViewComment( 9 , _T("Meiryo UI")  ) ,
	//m_fontpropJikokuhyouVFont(9, _T("@ＭＳ ゴシック")),
	//m_fontpropDiaEkimeiFont(9, _T("ＭＳ ゴシック")),
	//m_fontpropDiaJikokuFont(9, _T("ＭＳ ゴシック")),
	//m_fontpropDiaRessyaFont(9, _T("ＭＳ ゴシック")),
	//m_fontpropOperationTableFont(9, _T("ＭＳ ゴシック")),
	//m_fontpropAllOperationTableJikokuFont(8, _T("ＭＳ ゴシック")),
	//m_fontpropViewComment(9, _T("ＭＳ ゴシック")),
		m_colorDiaMojiColor( CdColorProp( 0 , 0 , 0 ) ) ,
		//m_colorDiaHaikeiColor( CdColorProp( 255 , 255 , 255 ) ) ,
		m_colorDiaRessyaColor( CdColorProp( 0 , 0 , 0 ) ) ,
		m_colorDiaJikuColor( CdColorProp(192 , 192 , 192 ) ) ,
		m_colorStdOpeTimeLowerColor(CdColorProp(255, 224, 224)),//CdColorProp(255, 128, 128)
		m_colorStdOpeTimeHigherColor(CdColorProp(224, 255, 255)),//CdColorProp(128, 255, 255)
		m_colorStdOpeTimeUndefColor(CdColorProp(255, 255, 128)),
		m_colorStdOpeTimeIllegalColor(CdColorProp(160, 160, 160)),//CdColorProp(128, 128, 128)
		m_colorOperationStringColor(CdColorProp(0, 0, 0)),
		m_colorOperationGridColor(CdColorProp(0, 0, 0)),
		m_iEkimeiLength( 6 ) ,
		m_iJikokuhyouRessyaWidth( 5 ) ,
		m_iAnySecondIncDec1( 5 ) ,
		m_iAnySecondIncDec2( 15 ) ,
		m_bDisplayRessyamei(true),
		m_bDisplayOuterTerminalO(false),
		m_bDisplayOuterTerminalT(false),
		m_iDiagramDisplayOuterTerminal(0),
		m_iSecondRoundChaku(0),
		m_iSecondRoundHatsu(0),
		m_bDisplay2400(false),
		m_iOperationNumberRows(1),
		m_bDisplayInOutLinkCode(false)
{
	for ( int idx = 0 ; 
		idx < sizeof(m_arJikokuhyouFont) / sizeof(m_arJikokuhyouFont[0]) ;
		idx ++ )
	{
		m_arJikokuhyouFont[idx].setPointTextHeight( 9 )
			.setFacename(_T("Meiryo UI") ) ;
		//m_arJikokuhyouFont[idx].setPointTextHeight(9)
		//	.setFacename(_T("ＭＳ ゴシック"));
		if ( idx == 1 )
		{
			m_arJikokuhyouFont[idx].setBold( true ) ;
		}
		else if ( idx == 2 )
		{
			m_arJikokuhyouFont[idx].setItaric( true ) ;
		}
		else if ( idx == 3 )
		{
			m_arJikokuhyouFont[idx].setBold( true ).setItaric( true ) ;
		}

	}
	for (int idx = 0;
		idx < sizeof(m_arColorDiaBackColor) / sizeof(m_arColorDiaBackColor[0]);
		idx++)
	{
		m_arColorDiaBackColor[idx] = CdColorProp(255, 255, 255);
	}

	m_colorJikokuhyouBackColor[0] = CdColorProp(255, 255, 255);
	m_colorJikokuhyouBackColor[1] = CdColorProp(240, 240, 240);
	m_colorJikokuhyouBackColor[2] = CdColorProp(255, 255, 255);
	m_colorJikokuhyouBackColor[3] = CdColorProp(255, 255, 255);
};
	
	
// ********************************
//@name CdDedDispProp-属性
// ********************************
CdFontProp	CdDedDispProp::getJikokuhyouFont(int idx )const
{
	return 	m_arJikokuhyouFont[idx] ;
};
CdDedDispProp& CdDedDispProp::setJikokuhyouFont( 
	int idx , 
	const CdFontProp& value )
{
	m_arJikokuhyouFont[idx] = value ; 
	return *this ;
};

CdFontProp	CdDedDispProp::getJikokuhyouVFont()const
{	return m_fontpropJikokuhyouVFont ;}
CdDedDispProp& CdDedDispProp::setJikokuhyouVFont( const CdFontProp& value )
{	 m_fontpropJikokuhyouVFont = value ; return *this ;}


CdFontProp	CdDedDispProp::getDiaEkimeiFont()const
{
	return 	m_fontpropDiaEkimeiFont ;
};
CdDedDispProp& CdDedDispProp::setDiaEkimeiFont( const CdFontProp& value )
{
	m_fontpropDiaEkimeiFont = value ; return *this ;
};
CdFontProp	CdDedDispProp::getDiaJikokuFont()const
{
	return 	m_fontpropDiaJikokuFont ;
};
CdDedDispProp& CdDedDispProp::setDiaJikokuFont( const CdFontProp& value )
{
	m_fontpropDiaJikokuFont = value ; return *this ;
};
CdFontProp	CdDedDispProp::getDiaRessyaFont()const
{
	return 	m_fontpropDiaRessyaFont ;
};
CdDedDispProp& CdDedDispProp::setDiaRessyaFont( const CdFontProp& value )
{
	m_fontpropDiaRessyaFont = value ; return *this ;
};
CdFontProp	CdDedDispProp::getOperationTableFont()const
{
	return 	m_fontpropOperationTableFont;
};
CdDedDispProp& CdDedDispProp::setOperationTableFont(const CdFontProp& value)
{
	m_fontpropOperationTableFont = value; return *this;
};
CdFontProp	CdDedDispProp::getAllOperationTableJikokuFont()const
{
	return 	m_fontpropAllOperationTableJikokuFont;
};
CdDedDispProp& CdDedDispProp::setAllOperationTableJikokuFont(const CdFontProp& value)
{
	m_fontpropAllOperationTableJikokuFont = value; return *this;
};
CdFontProp	CdDedDispProp::getViewCommentFont()const
{	return m_fontpropViewComment ;};
CdDedDispProp& CdDedDispProp::setViewCommentFont( const CdFontProp& value )
{
	m_fontpropViewComment = value ; return *this ; 
};
		
		
CdColorProp	CdDedDispProp::getDiaMojiColor()const
{
	return m_colorDiaMojiColor ;
};
CdDedDispProp& CdDedDispProp::setDiaMojiColor( const CdColorProp& value )
{
	m_colorDiaMojiColor = value ; return *this ;
};
CdColorProp	CdDedDispProp::getDiaBackColor(int idx)const
{
	return m_arColorDiaBackColor[idx];
};
CdDedDispProp& CdDedDispProp::setDiaBackColor(int idx,const CdColorProp& value )
{
	m_arColorDiaBackColor[idx] = value ; return *this ;
};
CdColorProp	CdDedDispProp::getDiaRessyaColor()const
{
	return m_colorDiaRessyaColor ;
};
CdDedDispProp& CdDedDispProp::setDiaRessyaColor( const CdColorProp& value )
{
	m_colorDiaRessyaColor = value ; return *this ;
};
CdColorProp	CdDedDispProp::getDiaJikuColor()const
{
	return m_colorDiaJikuColor ;
};
CdDedDispProp& CdDedDispProp::setDiaJikuColor( const CdColorProp& value )
{
	m_colorDiaJikuColor = value ; return *this ;
};
// ********************************
CdColorProp	CdDedDispProp::getJikokuhyouBackColor(int idx)const
{
	return 	m_colorJikokuhyouBackColor[idx];
};
CdDedDispProp& CdDedDispProp::setJikokuhyouBackColor(
	int idx,
	const CdColorProp& value)
{
	m_colorJikokuhyouBackColor[idx] = value;
	return *this;
};

CdColorProp	CdDedDispProp::getStdOpeTimeLowerColor()const
{
	return m_colorStdOpeTimeLowerColor;
};
CdDedDispProp& CdDedDispProp::setStdOpeTimeLowerColor(const CdColorProp& value)
{
	m_colorStdOpeTimeLowerColor = value; return *this;
};
CdColorProp	CdDedDispProp::getStdOpeTimeHigherColor()const
{
	return m_colorStdOpeTimeHigherColor;
};
CdDedDispProp& CdDedDispProp::setStdOpeTimeHigherColor(const CdColorProp& value)
{
	m_colorStdOpeTimeHigherColor = value; return *this;
};
CdColorProp	CdDedDispProp::getStdOpeTimeUndefColor()const
{
	return m_colorStdOpeTimeUndefColor;
};
CdDedDispProp& CdDedDispProp::setStdOpeTimeUndefColor(const CdColorProp& value)
{
	m_colorStdOpeTimeUndefColor = value; return *this;
};
CdColorProp	CdDedDispProp::getStdOpeTimeIllegalColor()const
{
	return m_colorStdOpeTimeIllegalColor;
};
CdDedDispProp& CdDedDispProp::setStdOpeTimeIllegalColor(const CdColorProp& value)
{
	m_colorStdOpeTimeIllegalColor = value; return *this;
};

CdColorProp	CdDedDispProp::getOperationStringColor()const
{
	return m_colorOperationStringColor;
};
CdDedDispProp& CdDedDispProp::setOperationStringColor(const CdColorProp& value)
{
	m_colorOperationStringColor = value; return *this;
};
CdColorProp	CdDedDispProp::getOperationGridColor()const
{
	return m_colorOperationGridColor;
};
CdDedDispProp& CdDedDispProp::setOperationGridColor(const CdColorProp& value)
{
	m_colorOperationGridColor = value; return *this;
};

int CdDedDispProp::getEkimeiLength()const
{ return m_iEkimeiLength ;};
CdDedDispProp& CdDedDispProp::setEkimeiLength( int value )
{
	m_iEkimeiLength = value ;
	if ( m_iEkimeiLength < 1 ){
		m_iEkimeiLength = 1 ;
	}
	if ( m_iEkimeiLength > 29 ){
		m_iEkimeiLength = 29 ;
	}
	return *this ;
};

int CdDedDispProp::getJikokuhyouRessyaWidth()const
{	return m_iJikokuhyouRessyaWidth ; };
CdDedDispProp& CdDedDispProp::setJikokuhyouRessyaWidth( int value )
{	
	m_iJikokuhyouRessyaWidth = value ;	
	if ( m_iJikokuhyouRessyaWidth < 4 )
	{
		m_iJikokuhyouRessyaWidth = 4 ;
	}
	if ( m_iJikokuhyouRessyaWidth > 255 )
	{
		m_iJikokuhyouRessyaWidth = 255 ;
	}
	return *this ;
};

//add_by_d_mania
int CdDedDispProp::getAnySecondIncDec1()const
{	return m_iAnySecondIncDec1 ; };
CdDedDispProp& CdDedDispProp::setAnySecondIncDec1( int value )
{	
	m_iAnySecondIncDec1 = value ;	
	if ( m_iAnySecondIncDec1 < -60 )
	{
		m_iAnySecondIncDec1 = -60 ;
	}
	if ( m_iAnySecondIncDec1 > 60 )
	{
		m_iAnySecondIncDec1 = 60 ;
	}
	return *this ;
};

//add_by_d_mania
int CdDedDispProp::getAnySecondIncDec2()const
{	return m_iAnySecondIncDec2 ; };
CdDedDispProp& CdDedDispProp::setAnySecondIncDec2( int value )
{	
	m_iAnySecondIncDec2 = value ;	
	if ( m_iAnySecondIncDec2 < -60 )
	{
		m_iAnySecondIncDec2 = -60 ;
	}
	if ( m_iAnySecondIncDec2 > 60 )
	{
		m_iAnySecondIncDec2 = 60 ;
	}
	return *this ;
};

bool	CdDedDispProp::getDisplayRessyamei()const
{
	return m_bDisplayRessyamei;
};
CdDedDispProp& CdDedDispProp::setDisplayRessyamei(bool value)
{
	m_bDisplayRessyamei = value; return *this;
}
bool CdDedDispProp::getDisplayOuterTerminalO() const
{
	return m_bDisplayOuterTerminalO;
}
bool CdDedDispProp::getDisplayOuterTerminalT() const
{
	return m_bDisplayOuterTerminalT;
}
bool CdDedDispProp::getDisplayOuterTerminalShihatsu(ERessyahoukou eRessyahoukou) const
{
	if (eRessyahoukou == Ressyahoukou_Kudari)
	{
		return m_bDisplayOuterTerminalO;
	}
	return m_bDisplayOuterTerminalT;
}
bool CdDedDispProp::getDisplayOuterTerminalShuchaku(ERessyahoukou eRessyahoukou) const
{
	if (eRessyahoukou == Ressyahoukou_Kudari)
	{
		return m_bDisplayOuterTerminalT;
	}
	return m_bDisplayOuterTerminalO;
}
bool CdDedDispProp::getDisplayOuterTerminalShihatsu(bool IsKudari) const
{
	if (IsKudari)
	{
		return m_bDisplayOuterTerminalO;
	}
	return m_bDisplayOuterTerminalT;
}
bool CdDedDispProp::getDisplayOuterTerminalShuchaku(bool IsKudari) const
{
	if (IsKudari)
	{
		return m_bDisplayOuterTerminalT;
	}
	return m_bDisplayOuterTerminalO;
}
CdDedDispProp & CdDedDispProp::setDisplayOuterTerminalO(bool value)
{
	m_bDisplayOuterTerminalO = value; return *this;
}
CdDedDispProp & CdDedDispProp::setDisplayOuterTerminalT(bool value)
{
	m_bDisplayOuterTerminalT = value; return *this;
}
;

int CdDedDispProp::getDiagramDisplayOuterTerminal()const
{
	return m_iDiagramDisplayOuterTerminal;
};
CdDedDispProp& CdDedDispProp::setDiagramDisplayOuterTerminal(int value)
{
	m_iDiagramDisplayOuterTerminal = value;
	if (m_iDiagramDisplayOuterTerminal < 0)
	{
		m_iDiagramDisplayOuterTerminal = 0;
	}
	if (m_iDiagramDisplayOuterTerminal > 3)
	{
		m_iDiagramDisplayOuterTerminal = 3;
	}
	return *this;
};

int CdDedDispProp::getSecondRoundChaku()const
{
	return m_iSecondRoundChaku;
};
CdDedDispProp& CdDedDispProp::setSecondRoundChaku(int value)
{
	m_iSecondRoundChaku = value;
	if (m_iSecondRoundChaku < 0)
	{
		m_iSecondRoundChaku = 0;
	}
	if (m_iSecondRoundChaku > 2)
	{
		m_iSecondRoundChaku = 2;
	}
	return *this;
};

int CdDedDispProp::getSecondRoundHatsu()const
{
	return m_iSecondRoundHatsu;
};
CdDedDispProp& CdDedDispProp::setSecondRoundHatsu(int value)
{
	m_iSecondRoundHatsu = value;
	if (m_iSecondRoundHatsu < 0)
	{
		m_iSecondRoundHatsu = 0;
	}
	if (m_iSecondRoundHatsu > 2)
	{
		m_iSecondRoundHatsu = 2;
	}
	return *this;
};

bool	CdDedDispProp::getDisplay2400()const
{
	return m_bDisplay2400;
};
CdDedDispProp& CdDedDispProp::setDisplay2400(bool value)
{
	m_bDisplay2400 = value; return *this;
}

int CdDedDispProp::getOperationNumberRows()const
{
	return m_iOperationNumberRows;
};
CdDedDispProp& CdDedDispProp::setOperationNumberRows(int value)
{
	m_iOperationNumberRows = value;
	if (m_iOperationNumberRows < 1)
	{
		m_iOperationNumberRows = 1;
	}
	if (m_iOperationNumberRows > 5)
	{
		m_iOperationNumberRows = 5;
	}
	return *this;
};

bool	CdDedDispProp::getDisplayInOutLinkCode()const
{
	return m_bDisplayInOutLinkCode;
};
CdDedDispProp& CdDedDispProp::setDisplayInOutLinkCode(bool value)
{
	m_bDisplayInOutLinkCode = value; return *this;
}

tstring CdDedDispProp::createEkimeiExtentString()const 
{
	tstring	strRv ;
	for ( int idx = 0 ; idx < m_iEkimeiLength ; idx ++ )
	{
		strRv += _T("国") ;
	}
	return strRv ;
};


void CdDedDispProp::clear()
{
	*this = CdDedDispProp() ; 
} ;

} //namespace DedRosenFileData
